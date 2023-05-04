#include "trusted_platform_manage.h"

#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/sha.h>
#include <openssl/md5.h>

#include <cstring>
#include <fstream>
#include <iostream>
// #include <openssl/md5.h>

int TrustedPlatformManage::GetDigest(const std::string& file_name,
                                     std::string& digest_str) {
FILE *pFile = fopen(file_name.c_str(), "rb");
unsigned char buffer[1024] = "";
int len = 0;
len = fread(buffer, 1, 1024, pFile);

  int ret = 0;
  unsigned char digest[MD5_DIGEST_LENGTH];
  MD5_CTX ctx;
  MD5_Init(&ctx);

  // MD5_Update(&ctx, file_name.c_str(), file_name.size());
  MD5_Update(&ctx, buffer, len);

  MD5_Final(digest, &ctx);

  // unsigned char digest[SHA_DIGEST_LENGTH];
  // SHA_CTX ctx;
  // SHA1_Init(&ctx);
  // SHA1_Update(&ctx, file_name.c_str(), file_name.size());
  // SHA1_Final(digest, &ctx);

  

  char mdString[MD5_DIGEST_LENGTH * 2 + 1];
  for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    sprintf(&mdString[i * 2], "%02x", digest[i]);
  digest_str = std::string(mdString);
  std::cout << "文件名" << file_name <<",获取的gigest值为" << digest_str << std::endl;
  return ret;
}

int TrustedPlatformManage::SaveSign(const std::string& file_name,
                                    const std::vector<char>& sign) {
  int ret = 0;
  std::string sign_file_name = file_name;
  sign_file_name += ".sign";

  std::ofstream outFile(sign_file_name.c_str(),
                        std::ios::out | std::ios::binary);
  ;  // 定义ofstream对象outFile

  std::cout << "sign data: \n" << sign.data() << std::endl;
  outFile.write((const char*)sign.data(), sign.size());

  outFile.close();  // 关闭文件
  return ret;
}

int TrustedPlatformManage::GetSign(const std::string& file_name,
                                   std::vector<char>& sign) {
  int ret = 0;
  std::ifstream input_file(file_name.c_str(), std::ios::in | std::ios::binary);
  sign.clear();
  sign.resize(128);
  input_file.read((char*)sign.data(), sign.size());
  std::cout << "get sign data: \n" << sign.data() << std::endl;
  input_file.close();
  return ret;
}

int TrustedPlatformManage::Sign(const std::string& file_name,
                                const std::string& key_file_name) {
  int ret = 0;
  if (file_name.empty() || key_file_name.empty()) {
    fprintf(stderr, "file_name or key is empty");
    return -1;
  }
  FILE* private_key_file = fopen(key_file_name.c_str(), "rb");
  if (private_key_file == NULL) {
    fprintf(stderr, "private key file error");
    return -1;
  }
  RSA* rsa_private_key = RSA_new();

  if (PEM_read_RSAPrivateKey(private_key_file, &rsa_private_key, 0, 0) ==
      NULL) {
    fprintf(stderr, "PEM_read_RSAPrivateKey error");
    return -1;
  }

  unsigned int key_len = RSA_size(rsa_private_key);

  std::vector<char> sign;

  sign.resize(key_len);

  std::string digest;
  GetDigest(file_name, digest);
  ret =
      RSA_sign(NID_sha1, (const unsigned char*)digest.c_str(), digest.length(),
               (unsigned char*)sign.data(), &key_len, rsa_private_key);
  if (ret < 0) {
    fprintf(stderr, "sign error");
    return ret;
  }
  // 将签名存进签名文件
  SaveSign(file_name, sign);

  RSA_free(rsa_private_key);
  fclose(private_key_file);
  CRYPTO_cleanup_all_ex_data();
  return 0;
}
int TrustedPlatformManage::SignVerify(const std::string& file_name,
                                      const std::string& key_file_name) {
  int ret = 0;
  if (file_name.empty() || key_file_name.empty()) {
    fprintf(stderr, "file_name or key is empty");
    return -1;
  }

  FILE* public_key_file = fopen(key_file_name.c_str(), "rb");
  if (public_key_file == NULL) {
    fprintf(stderr, "public key file error");
    return -1;
  }

  RSA* rsa_public_key = RSA_new();
  if (PEM_read_RSA_PUBKEY(public_key_file, &rsa_public_key, 0, 0) == NULL) {
    fprintf(stderr, "PEM_read_RSA_PUBKEY error");
    return -1;
  }

  std::string digest;
  GetDigest(file_name, digest);
  
  std::string sign_file_name = file_name;
  sign_file_name += ".sign";

  // 从签名文件获取签名值
  std::vector<char> sign;
  GetSign(sign_file_name, sign);

  ret = RSA_verify(NID_sha1, (const unsigned char*)digest.c_str(),
                   digest.size(), (const unsigned char*)sign.data(),
                   sign.size(), rsa_public_key);
  if (ret != 1) {
    std::cout << "verify error\n";
    unsigned long ulErr = ERR_get_error();
    char szErrMsg[1024] = {0};
    std::cout << "error number:" << ulErr << std::endl;
    char* pTmp = NULL;
    pTmp = ERR_error_string(ulErr, szErrMsg);  // 格式：error:errId:库:函数:原因
    std::cout << szErrMsg << std::endl;
    return -1;
  } else
    std::cout << "verify success\n";
  RSA_free(rsa_public_key);
  fclose(public_key_file);
  CRYPTO_cleanup_all_ex_data();
  return 0;
}
int TrustedPlatformManage::Hd5Check(const std::string& file_name,
                                    const std::string& hd5) {
  return 0;
}

#ifndef TRUSTED_PLATFORM_MANAGE_H__
#define TRUSTED_PLATFORM_MANAGE_H__
#include <string>
#include <vector>

class TrustedPlatformManage {
 public:
  int GetDigest(const std::string& file_name, std::string& digest_str);
  int SaveSign(const std::string& file_name, const std::vector<char>& sign);
  int GetSign(const std::string& file_name, std::vector<char>& sign);

 public:
  int Sign(const std::string& file_name, const std::string& key);
  int SignVerify(const std::string& file_name, const std::string& key);
  int Hd5Check(const std::string& file_name, const std::string& hd5);
  // std::vector<char> sign;
};

#endif
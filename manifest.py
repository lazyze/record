from conans import ConanFile, tools, CMake
import os
import hashlib
import json
import sys
import git

#conan方法获取名称和版本需要导入的包
# from conans.model.conan_file import ConanFile
# from conans.model.settings import Settings
# from conan.model.scope import Scopes
# from conans import tools
# from conans.client.loader import ConanFileLoader

from conans.client.loader import ConanFileLoader
# from conans.client.conf import default_settings

# from conans.client.loader import ConanFileTextLoader
# from conans.errors import NotFoundException
# from conans.model.conan_file import ConanFile



# def get_name_and_version(conanfile_path):
#     with open(conanfile_path, "r", encoding="utf-8") as f:
#         conanfile_contents = f.read()

#     name = conanfile_contents.split("name = ")[1].split("\"")[1]
#     version = conanfile_contents.split("version = ")[1].split("\"")[1]

#     return name, version

def generate_manifest(path):
    file_out = {}
    # file_out["module_name"], file_out["module_version"] = get_name_and_version("./conanfile.py")


    file_out["module_name"] = "module_name"
    file_out["module_version"] = "module_version"



    #通过conan获取name和version
    # loader = ConanFileLoader(None,None,None)
    # conanfile = loader.load_conan("./conanfile.py")

    # conanfile_path = "./conanfile.py"
    # conanfile_txt = open(conanfile_path, "r", encoding="utf-8").read()
    # conanfile_loader = ConanFileTextLoader(conanfile_txt)
    # conanfile = conanfile_loader.load_conanfile_class()

    # file_out["module_name"] = conanfile.name
    # file_out["module_version"] = conanfile.version




     # conan git
    conan_git = tools.Git()
    # git python
    repo = git.Repo(".git")

    if conan_git.get_tag() != None:
        file_out["git_tag"] = conan_git.get_tag()
    file_out["git_commit_id"] = conan_git.get_revision()
    file_out["get_commit_message"] = conan_git.get_commit_message()
    commit = repo.commit(file_out["git_commit_id"])
    file_out["author_name"] = commit.author.name
    file_out["author_email"] = commit.author.email
    file_out["date_and_time"] = str(commit.authored_datetime.date()) + " " + str(commit.authored_datetime.time())
    file_out["git_branch"] = conan_git.get_branch()
    file_out["file_list"] = get_file_list(path)
    out = open(path + '/' +  "test.manifest", 'w')
    out.write(json.dumps(file_out, sort_keys=False, indent=4, separators=(',', ': ')))
    out.close()

def get_file_list(path):
    file_name_list = search_files(path)
    file_list= []
    for file in file_name_list:
        file_info = {}
        file_info["file_path"] = os.path.relpath(file, path)
        file_info["md5sum"] = get_file_md5(file)
        file_list.append(file_info)
    return file_list

def search_files(dir_path):
    result = []
    file_list = os.listdir(dir_path)  # 获取当前文件夹下的所有文件
    for file_name in file_list:
        if file_name.find(".txt") != -1 or file_name.find(".manifest") != -1:
                continue
        complete_file_name = os.path.join(dir_path, file_name)  # 获取包含路径的文件名
        if os.path.isdir(complete_file_name):  # 如果是文件夹
            result.extend(search_files(complete_file_name)) # 文件夹递归
        if os.path.isfile(complete_file_name):  # 文件名判断是否为文件
            result.append(complete_file_name)   # 添加文件路径到结果列表里
    return result

def get_file_md5(file_name):
    m = hashlib.md5()   #创建md5对象
    with open(file_name,'rb') as fobj:
        while True:
            data = fobj.read(4096)
            if not data:
                break
            m.update(data)  #更新md5对象
    return m.hexdigest()    #返回md5对象


def get_str_md5(content):
    m = hashlib.md5(content) #创建md5对象
    return m.hexdigest()


def main():
  # Get the directory to list from the user.
#   arg1 = input("Enter the first argument: ")
  args = sys.argv[1:]
  directory = args[0]
#   directory = input("Enter the first argument: ")

  # Get the list of files in the directory.
#   files = os.listdir(directory)

  generate_manifest(directory)

if __name__ == "__main__":
  main()
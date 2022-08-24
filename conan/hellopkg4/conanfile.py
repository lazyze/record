from conans import ConanFile, tools


class HelloConan(ConanFile):
    name = "hello"
    version = "0.4"
    settings = "os", "compiler", "build_type", "arch"
    description = "<Description of Hello here>"
    url = "None"
    license = "None"
    author = "None"
    topics = None

    def package(self):
        self.copy("*")

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)

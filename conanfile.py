from conans import ConanFile, CMake, tools
from conans.tools import download, unzip
import os


class QuickfixConan(ConanFile):
    name = "Quickfix"
    version = "1.14.4"
    license = "MIT"
    url = "https://github.com/ebostijancic/conan-quickfix"
    settings = "os", "compiler", "build_type", "arch"
    options = {"static": [True, False]}
    default_options = "static=True"
    generators = "cmake"
    export = "*"
    url = "https://github.com/quickfix/quickfix/archive/v.%s.zip" % version 
    zip_name = "quickfix.zip"
    quickfix_folder = "quickfix-v.%s" % version

    def source(self):
        download(self.url, self.zip_name)
        unzip(self.zip_name)
        os.unlink(self.zip_name)

    def build(self):
        cmake = CMake(self.settings)
        static = "--enable-shared=no --enable-static=yes --with-postgresql=no --with-mysql=no --with-python=no --with-ruby=no --with-java=no" if self.options.static else ""

        quickfix_folder = "quickfix-v.%s" % self.version
        #self.run('cd %s %s %s' % (self.quickfix_folder, cmake.command_line, static))
        self.run('cd %s && sh ./bootstrap' % self.quickfix_folder)
        self.run('cd %s && sh ./configure %s' % (self.quickfix_folder, static))
        self.run('cd %s && make' % self.quickfix_folder)

    def package(self):
        self.copy("*.h", src=self.quickfix_folder, dst="include/quickfix")

        src_folder = "%s/include/quickfix/" % (self.quickfix_folder)
        self.copy("*.h", src=src_folder, dst="include/quickfix")

        lib_folder = "%s/src/C++/.libs/" % (self.quickfix_folder)
        self.copy("*.lib", src=lib_folder, dst="lib", keep_path=False)
        self.copy("*.16.dylib", src=lib_folder, dst="lib", keep_path=False)
        self.copy("*.la", src="../%s" %(lib_folder), dst="lib", keep_path=False)
        self.copy("*.so", src=lib_folder, dst="lib", keep_path=False)
        self.copy("*.a", src=lib_folder, dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["quickfix"]

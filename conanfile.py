from conans import ConanFile, tools, ConfigureEnvironment
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
    export = "*"
    url = "https://github.com/quickfix/quickfix/archive/v.%s.zip" % version
    zip_name = "quickfix.zip"
    quickfix_folder = "quickfix-v.%s" % version

    def source(self):
        download(self.url, self.zip_name)
        unzip(self.zip_name)
        os.unlink(self.zip_name)

    def build(self):
        static = "--enable-shared=yes --enable-static=yes --with-postgresql=no --with-mysql=no --with-python=no --with-ruby=no --with-java=no" if self.options.static else ""

        quickfix_folder = "quickfix-v.%s" % self.version
        env = ConfigureEnvironment(self.deps_cpp_info, self.settings)

        #self.run('cd %s %s %s' % (self.quickfix_folder, cmake.command_line, static))
        self.run('cd %s && %s && sh ./bootstrap' % (quickfix_folder, env.command_line_env))
        self.run('cd %s/spec && sh ./generate_c++.sh' % quickfix_folder)
        self.run('cd %s && %s && sh ./configure %s' % (quickfix_folder, env.command_line_env, static))
        self.run('cd %s && %s && make' % (quickfix_folder,  env.command_line_env))

    def package(self):
        #self.copy("*.h", src=self.quickfix_folder, dst="include/quickfix")

        src_folder = "%s/include/quickfix/" % (self.quickfix_folder)
        self.copy("*.h", src=src_folder, dst="include/quickfix")
        self.copy("config.h", src=self.quickfix_folder, dst="include/quickfix")

        lib_folder = "%s/src/C++/.libs/" % (self.quickfix_folder)
        self.copy("*.lib", src=lib_folder, dst="lib", keep_path=False)
        self.copy("*.16.dylib", src=lib_folder, dst="lib", keep_path=False)
        self.copy("*.la", src=lib_folder, dst="lib", keep_path=False)
        self.copy("*.so*", src=lib_folder, dst="lib", keep_path=False)
        self.copy("*.a", src=lib_folder, dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["libquickfix.a"] if self.options.static else ["libquickfix.so.16"]


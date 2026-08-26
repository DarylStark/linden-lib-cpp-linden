import os
from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMakeDeps, CMakeToolchain


class LindenConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    
    def requirements(self):
        skips = os.getenv("CONAN_SKIPS", default='').split()
        requires = (
            "sfml/3.0.2",
        )
        
        for requirement in requires:
            if requirement.split('/')[0] in skips:
                continue
            self.requires(requirement)

    def layout(self):
        cmake_layout(self)

    def generate(self):
        CMakeDeps(self).generate()
        CMakeToolchain(self).generate()
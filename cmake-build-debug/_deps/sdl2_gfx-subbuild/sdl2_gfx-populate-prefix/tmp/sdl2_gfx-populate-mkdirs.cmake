# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "E:/Project/C++/2DGamePhysic/cmake-build-debug/_deps/sdl2_gfx-src"
  "E:/Project/C++/2DGamePhysic/cmake-build-debug/_deps/sdl2_gfx-build"
  "E:/Project/C++/2DGamePhysic/cmake-build-debug/_deps/sdl2_gfx-subbuild/sdl2_gfx-populate-prefix"
  "E:/Project/C++/2DGamePhysic/cmake-build-debug/_deps/sdl2_gfx-subbuild/sdl2_gfx-populate-prefix/tmp"
  "E:/Project/C++/2DGamePhysic/cmake-build-debug/_deps/sdl2_gfx-subbuild/sdl2_gfx-populate-prefix/src/sdl2_gfx-populate-stamp"
  "E:/Project/C++/2DGamePhysic/cmake-build-debug/_deps/sdl2_gfx-subbuild/sdl2_gfx-populate-prefix/src"
  "E:/Project/C++/2DGamePhysic/cmake-build-debug/_deps/sdl2_gfx-subbuild/sdl2_gfx-populate-prefix/src/sdl2_gfx-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/Project/C++/2DGamePhysic/cmake-build-debug/_deps/sdl2_gfx-subbuild/sdl2_gfx-populate-prefix/src/sdl2_gfx-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/Project/C++/2DGamePhysic/cmake-build-debug/_deps/sdl2_gfx-subbuild/sdl2_gfx-populate-prefix/src/sdl2_gfx-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()

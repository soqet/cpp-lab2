# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/soqet/Documents/coding/nsu/course2/oop/lab2/build/_deps/googletest-src"
  "C:/Users/soqet/Documents/coding/nsu/course2/oop/lab2/build/_deps/googletest-build"
  "C:/Users/soqet/Documents/coding/nsu/course2/oop/lab2/build/_deps/googletest-subbuild/googletest-populate-prefix"
  "C:/Users/soqet/Documents/coding/nsu/course2/oop/lab2/build/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "C:/Users/soqet/Documents/coding/nsu/course2/oop/lab2/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "C:/Users/soqet/Documents/coding/nsu/course2/oop/lab2/build/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "C:/Users/soqet/Documents/coding/nsu/course2/oop/lab2/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/soqet/Documents/coding/nsu/course2/oop/lab2/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()

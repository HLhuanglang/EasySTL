#!/usr/bin/env bash

# You can customize the clang-format path by setting the CLANG_FORMAT environment variable
CLANG_FORMAT=${CLANG_FORMAT:-clang-format}

find easystl test -name *.h -o -name *.cpp -exec dos2unix {} \;
find easystl test -name *.h -o -name *.cpp | xargs $CLANG_FORMAT -i -style=file
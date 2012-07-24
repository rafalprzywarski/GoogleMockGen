#!/bin/bash

CLANG_PATH=`readlink -f ../../../../../../Release+Asserts/bin`
PLUGIN_PATH=`readlink -f ../../../../../../Release+Asserts/lib/libGoogleMockGen.so`
export PATH="$PATH:$CLANG_PATH"

function generateMock {
    clang++ -fsyntax-only -Xclang -load -Xclang $PLUGIN_PATH -Xclang -plugin -Xclang GoogleMockGen $1 -Xclang $2 > "$2Mock.hpp"
    if [ $? -ne 0 ]
    then
        echo "error generating mock for $2 from $1"
        exit $?
    fi
}

function generateAllMocks {
    for desc in `cat mocks.txt`
    do
        local filename="${desc%%:*}"
        local classname="${desc##*:}"
        generateMock $filename $classname
    done
}

generateAllMocks
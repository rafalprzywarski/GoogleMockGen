#!/bin/bash

CLANG_PATH=`readlink -f ../../../../../../Debug+Asserts/bin`
PLUGIN_PATH=`readlink -f ../../../../../../Debug+Asserts/lib/libGoogleMockGen.so`
export PATH="$PATH:$CLANG_PATH"

function generateMock {
    clang++ -fsyntax-only $1 -Xclang -load -Xclang $PLUGIN_PATH -Xclang -plugin -Xclang GoogleMockGen -Xclang -plugin-arg-GoogleMockGen -Xclang $1 -Xclang -plugin-arg-GoogleMockGen -Xclang $2 > "$2Mock.hpp"
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
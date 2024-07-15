mkdir -p build

ROOT_DIR=`pwd`

cd build

if [ -z "$1" ]; then
    BUILD_TYPE="Release"
else
    BUILD_TYPE=$1
fi


if [ $BUILD_TYPE = "Release" ] || [ $BUILD_TYPE = "Debug" ]; then
    echo "************************************"
    echo "Building with option $BUILD_TYPE"
    echo "************************************"
    mkdir -p "$BUILD_TYPE"
    cd $BUILD_TYPE
    cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE "$ROOT_DIR/Eigenface/."
    make
    make install
else
    echo "************************************"
    echo "Build type $BUILD_TYPE not supported"
    echo "************************************"
fi

cd $ROOT_DIR

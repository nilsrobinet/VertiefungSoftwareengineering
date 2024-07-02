mkdir -p build

ROOT_DIR=`pwd`

pushd .

cd build

if [ -z "$1" ]; then
    BUILD_TYPE="Release"
else
    BUILD_TYPE=$1
fi


if [ $BUILD_TYPE = "Release" ]; then
    echo "************************************"
    echo "Building with option $BUILD_TYPE"
    echo "************************************"
    mkdir -p "$BUILD_TYPE"
    cd $BUILD_TYPE
    cmake "$ROOT_DIR/Eigenface/."
    make
else
    echo "************************************"
    echo "Build type $BUILD_TYPE not supported"
    echo "************************************"
fi

popd

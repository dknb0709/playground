ROOT=$(pwd)
BUILD_DIR=$ROOT/build

rm -rf $BUILD_DIR
mkdir $BUILD_DIR && cd $BUILD_DIR

cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=on
make

clear && echo -en '\e[3J' && $BUILD_DIR/DigitalClock/main.out


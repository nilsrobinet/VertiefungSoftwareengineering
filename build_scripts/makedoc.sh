# Dieses Script dient dazu die dokumentation zum projekt zu bauen

mkdir -p build
mkdir -p build/docu
mkdir -p build/docu/chapters

ROOT_DIR=`pwd`
echo "ROOT_DIR is $ROOT_DIR"

cd docu/ausarbeitung/
pdflatex --output-directory=$ROOT_DIR/build/docu main.tex
pdflatex --output-directory=$ROOT_DIR/build/docu main.tex
cd $ROOT_DIR

#TODO: html documentation

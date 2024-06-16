# Dieses Script dient dazu das gesamte Projekt inklusive Ausarbeitung und Präsentation zu bauen

pushd .
cd docu/ausarbeitung
mkdir -p out
mkdir -p out/chapters

pdflatex -aux_directory=out -output-directory=out main.tex 
popd

# Dieses Script dient dazu das gesamte Projekt inklusive Ausarbeitung und Präsentation zu bauen

pushd .
cd docu/ausarbeitung
mkdir -p out
cd out

pdflatex ../main.tex
#pdflatex main.dvi 
popd

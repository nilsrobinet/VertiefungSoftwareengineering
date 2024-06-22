# Dieses Script dient dazu das gesamte Projekt inklusive Ausarbeitung und Präsentation zu bauen

mkdir -p build/docu
mkdir -p build/docu/chapters
tectonic -X compile --outfmt pdf --outdir build/docu/ --keep-intermediates docu/ausarbeitung/main.tex

#TODO: html documentation

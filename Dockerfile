FROM ubuntu:24.04

RUN apt update && apt upgrade
RUN apt install -y curl\
    vim
RUN apt install -y texlive\
    texlive-lang-german\
    texlive-latex-extra\
    texlive-science
RUN apt install -y cmake make gcc g++
RUN apt install python3
RUN python3 -m pip install -r requirements.txt     

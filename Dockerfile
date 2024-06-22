FROM ubuntu:24.04

RUN apt update && apt upgrade
RUN apt install -y curl\
    vim
RUN apt install -y texlive\
    texlive-lang-german\
    texlive-latex-extra\
    texlive-science


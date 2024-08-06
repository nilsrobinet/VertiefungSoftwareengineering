FROM ubuntu:24.04

RUN apt update -y && apt upgrade -y
RUN apt install -y curl\
    vim
RUN apt install -y texlive\
    texlive-lang-german\
    texlive-latex-extra\
    texlive-science\
    texlive-bibtex-extra\
    biber
RUN apt install -y cmake make gcc g++ doxygen graphviz
RUN apt install -y python3 python3-pip python3-venv python3-dev

ENV VIRTUAL_ENV=/opt/venv
RUN python3 -m venv $VIRTUAL_ENV
ENV PATH="$VIRTUAL_ENV/bin:$PATH"

COPY requirements.txt .
RUN python3 -m pip install -r requirements.txt     

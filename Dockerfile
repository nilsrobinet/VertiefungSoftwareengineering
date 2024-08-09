FROM ubuntu:24.04

RUN apt update -y && apt upgrade -y
RUN apt install -y curl\
    vim
# install latex build dependecies
RUN apt install -y texlive\
    texlive-lang-german\
    texlive-latex-extra\
    texlive-science\
    texlive-bibtex-extra\
    biber
# install presentation generator
RUN curl -L https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb -o chrome.deb && apt install -y ./chrome.deb
RUN curl -L https://github.com/marp-team/marp-cli/releases/download/v3.4.0/marp-cli-v3.4.0-linux.tar.gz -o marp.tar.gz && tar -xf marp.tar.gz && mv marp /usr/local/bin
# install c++ build and documentation packages
RUN apt install -y cmake make gcc g++ doxygen graphviz
# install python
RUN apt install -y python3 python3-pip python3-venv python3-dev

# install python packages
ENV VIRTUAL_ENV=/opt/venv
RUN python3 -m venv $VIRTUAL_ENV
ENV PATH="$VIRTUAL_ENV/bin:$PATH"
COPY requirements.txt .
RUN python3 -m pip install -r requirements.txt     

# install requirements for deployment
RUN apt install -y rsync
RUN curl -fsSL https://get.docker.com -o get-docker.sh
RUN sh get-docker.sh

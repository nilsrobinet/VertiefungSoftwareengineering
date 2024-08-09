FROM ubuntu:24.04


RUN apt update -y && apt upgrade -y

RUN apt install -y python3 python3-pip python3-venv

ENV VIRTUAL_ENV=/opt/venv
RUN python3 -m venv $VIRTUAL_ENV
ENV PATH="$VIRTUAL_ENV/bin:$PATH"

COPY requirements.txt .
RUN python3 -m pip install -r requirements.txt

COPY . ./webapp

CMD ["python3","./webapp/main.py"]
EXPOSE 8080
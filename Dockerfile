FROM ubuntu:latest
LABEL authors="beafowl"

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    ccache \
    && rm -rf /var/lib/apt/lists/*

RUN useradd jenkins --shell /bin/bash --create-home
USER jenkins

ENTRYPOINT ["top", "-b"]
FROM ubuntu:22.04

WORKDIR /app

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    clang \
    clang-format \
    make \
    sudo \
    googletest \
    libgtest-dev \
    cppcheck \
    && rm -rf /var/lib/apt/lists/*

COPY . /app

RUN rm -rf /app/build && mkdir -p /app/build && cd /app/build && cmake .. && cmake --build .

CMD ["bash", "-c", "cd /app/build && ./test_MessageQueue"]

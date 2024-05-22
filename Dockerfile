FROM ubuntu:20.04

RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    make

WORKDIR /usr/src/app

COPY . .

RUN cmake -H. -B build && cmake --build build

CMD ["./build/message_writer"]


FROM gcc:13

RUN apt-get update && apt-get install -y cmake

WORKDIR /app

COPY . .

RUN mkdir build
WORKDIR /app/build

RUN cmake .. && make
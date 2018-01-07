FROM debian:stable-slim

WORKDIR /home/rkt/build

RUN apt-get update && apt-get install -y \
	gcc \
	make \
	&& rm -rf /var/lib/apt/lists/*


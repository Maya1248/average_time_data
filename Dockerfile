# Use Debian as the base image
FROM debian:stable-slim

# Set the working directory inside the container
WORKDIR /app

# Copy the entire project folder into the container
COPY . .

# Install dependencies
RUN apt update && \
    apt install -y make gcc python3 &&\
    apt install -y python3-pip &&\
    apt install -y python3-matplotlib
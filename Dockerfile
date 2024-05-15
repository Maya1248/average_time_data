# Use Debian as the base image
FROM debian:stable-slim

# Set the working directory inside the container
WORKDIR /app

# Copy the entire project folder into the container
COPY . .

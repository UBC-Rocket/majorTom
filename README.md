# majorTom
Flight Control Software Repo for UBC Rocket.

# Project Build Instructions
To build the project, first install Docker, then use it to build the project.

1. Install Docker on your workstation from http://docker.com based on your workstation OS.
2. Start the Docker service.
3. Pull our Docker image by running `sudo docker pull ubcrocket/majortombuild`on your workstation.
4. Navigate to the root folder of your local MajorTom repo.
5. Run the script, `./dmake.sh`, to compile the project.
6. You're finished! You can now run the complied image files in `MajorTom/img`.

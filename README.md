# majorTom
Flight Control Software Repo for UBC Rocket.

# Project Build Instructions
To build the project, first install Docker, then use it to build the project.

1. Install Docker CE on your workstation from http://docker.com based on your workstation OS.
2. Add Docker to your user group.
3. Start the Docker service.
4. Pull our Docker image by running `docker pull ubcrocket/majortombuild`on your workstation.
5. Navigate to the root folder of your local MajorTom repo.
6. Run the script, `./dmake.sh`, to compile the project. (Run `./dmake.sh clean` before, if you have issues.)
7. You're finished! You can now run the complied image files in `MajorTom/img`.

# majorTom
Flight Control Software Repo for UBC Rocket.

# Project Build Instructions
To build the project, first install Docker, then use it to build the project.

1. Install Docker on your workstation from http://docker.com based on your workstation OS.
2. Pull our Docker image by running `sudo docker pull ubcrocket/majortombuild`on your workstation.
3. Navigate to the root folder of your local MajorTom repo.
4. Run ```sudo docker run -it --volume `pwd`:/home/rkt --user=$UID:$GID ubcrocket/majortombuild make``` to compile the project.
5. You're finished! You can now run the complied image files in `MajorTom/img`.

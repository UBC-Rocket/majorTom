# majorTom
Flight Control Software Repo for UBC Rocket.

# Project Build Instructions
To build the project, first install Docker, then use it to build the project.

1. [Install Docker CE](https://docs.docker.com/engine/installation) on for your workstation specific OS.
2. Add Docker to your user group (to avoid sudo) (eg. `sudo usermod -aG docker YOUR_USERNAME_HERE` for Ubuntu and CentOS).
3. Start the Docker service (eg. `sudo systemctl start docker`).
4. Pull our Docker image by running `docker pull ubcrocket/majortombuild` on your workstation.
5. Clone the git repo using `git clone https://github.com/UBC-Rocket/MajorTom.git`
6. Navigate to the root folder of your local MajorTom repo.
7. Run the script, `./dmake.sh`, to compile the project. (Run `./dmake.sh clean` before, if you have issues.)
8. You're finished! You can now run the compiled image files in `MajorTom/img`.

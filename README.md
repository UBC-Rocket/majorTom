# majorTom
Flight Control Software Repo for UBC Rocket.

# Project Build Instructions
To build the project, first install Docker, then use it to build the project.

1. [Install Docker CE](https://docs.docker.com/engine/installation) on for your workstation specific OS.
##### via curl

```shell
sh -c "$(curl -fsSL https://get.docker.com)"
```

##### via wget

```shell
sh -c "$(wget https://get.docker.com -O -)"
```

2. Add Docker to your user group (to avoid needing sudo later on) (eg. `sudo usermod -aG docker YOUR_USERNAME_HERE` for Ubuntu and CentOS). Make sure to restart your system.
3. Enable Docker on system boot `sudo systemctl enable docker`.
4. Start the Docker service with `sudo systemctl start docker`.
5. Ensure Docker is working by running `docker run hello-world`
6. Pull our Docker build image by running `docker pull ubcrocket/majortombuild`.
7. Clone the git repo using `git clone https://github.com/UBC-Rocket/MajorTom.git`
8. Navigate to the root folder of your local MajorTom repo.
9. Run the script, `./dmake.sh`, to compile the project. (Run `./dmake.sh clean` before, if you have issues)
10. You're finished! You can now run the compiled image files in `MajorTom/img`.

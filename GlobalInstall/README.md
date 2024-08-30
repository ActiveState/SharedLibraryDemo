# Global Install Demo

## Run the Global Demo 
This demo shows how to accomplish a global python2 installation.

### Setup
1. In a terminal run state auth, and log into the ActiveState platform.
2. Run the `./build_docker.sh` script.

#### Note: The `build_docker.sh` script can be modified to point to a different project an org as long as you have permissions to check them out.  This can also be achieved by passing `build-args` to the docker build. 

### Run
3. Run the docker container, using the output of the build script.
4. Check the python2 default path:

```bash
$ which python2
```

5. Switch to the Apache user, and check the python2 default path:

```bash
$ su - www-data
$ which python2
```

## Dockerfile
The general steps in this dockerfile:
1. Install a standard ubuntu Apache server.
2. Install StateTool
3. Checkout ActiveStateBE/Python2.7
4. Updates the PATH variable in 3 places:
   * /etc/environment
   * /root/.bashrc
   * /etc/profile

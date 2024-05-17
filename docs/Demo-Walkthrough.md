## Demo walkthrough.

## To build the Docker:

### Prerequisites:

- SharedLibraryDemo Project
- Docker
- Git
- State Tool
- ActiveState VPN access to PR environments
- ActiveState SuperUser access in PR environments

### Steps to build Docker Container:

## Reset the project:

- Navigate to [ActiveStateBE/SharedLibraryDemo](https://pr13889.activestate.build/ActiveStateBE/SharedLibraryDemo/customize)

- Ensure that there are no libunistring packages in the build requirements.

- Set Timestamp to Bleeding Edge.

- Click on Download Builds.

Once the build is complete move on to the build of the docker container.

## Build Docker Container

Clone the SharedLibraryDemo repo:

```bash
git clone https://github.com/ActiveState/SharedLibraryDemo
cd SharedLibraryDemo/docker
```

Export the PR settings for the demo.
Currently we are using pr13889 for testing, this will change.

```bash
export AS_PLATFORM=pr13889;
export ACTIVESTATE_API_HOST=pr13889.activestate.build;
state auth;
```

Click the Auth - ensure that the link matches pr13889.activestate.build.

```bash
./build_docker.sh;
```

Ensure that the Environment variables are set correctly to the expected pr values, and press `y` to build.

## Prepare for the Demo

### Make a fully baked Demo

Before running this demo note that the `state install` step requires building code on the platform, and this step takes a minimum of 2 minutes in the best circustances, therefore it is strongly recommended that you create a pre-built version of the ingredient we are going to upload, and that it be uploaded and built ahead of time. The ingredient will be called `libunistring-demo-(something you chose)`. By default let's ensure there is a `libunistring-demo-rc1` built at the same time as the original project.

Steps

- Create ingredient `libunistring-demo-rc1` on the PR (You can use the demo `state publish` step to do this.)
- Fork the original project and add ingredient `libunistring-demo-rc1` to it.
- Set the timestamp to latest, and ensure that it completes a build.

## Run the Demo

### Start the conatiner with Auth

On completion of the build you should get the command to run the docker container.

It can be run with a token or not, it really does not make a difference.

If you have the API_KEY:

```bash
docker run -it -e API_KEY=$ACTIVESTATE_API_KEY sharedlibdemo
state auth --token $API_KEY
```

If you don't have the API_KEY:

```bash
docker run -it sharedlibdemo
state auth
```

and confirm through the gui.

### Run the Shared Library Tests

There are currently tests for libpng, zlib, and libunistring.

You can run all of the tests by running

```bash
./test
```

You can run a specific test, or multiple tests by passing them to test

Show libpng and zlib working:

```bash
./test libpng zlib
```

Show libpng and zlib working:

```bash
./test libpng zlib
```

Show libunistring failing:

```bash
./test libunistring
```

### State publish libunistring

We will now state publish libunistring.
Run the demo command in the publish folder and set 2 variables:

`./demo <libunistring version number (1.0, 1.1 1.2)> <release name>`

```bash
cd publish
./demo 1.2 rc9
```

The version number refers to any available version of libunistring(https://ftp.gnu.org/gnu/libunistring/) so 0.9.10 should work as well, but we've tested on 1.0, 1.1 and 1.2.

The release name is set here so we can repeat the demo without stepping on ourselves - This example will create `libunistring-demo-rc9` ingredient at version 1.2.

This step does the prework for state publish:

- Download the tarball for libunistring

- Write a metadata file with the needed information.

- Construct the `state publish` command.

This command displays the written metadata file that we will pass to state publish.
All of this metadata can be passed using flags on the command line.

Run the state publish command:

```bash
state publish --meta libunistring-rc9-1.2.yaml libunistring-1.2.tar.gz
```

Confirm the publish...

### State Install libunistring

This step may require waiting more than 2 minutes, so here are the options:

- Run an alternate `state install` command to install a prebuilt copy of the upload.
- Switch to the GUI for the build, and show off the log output. The wait time will still be 2-6 minutes, but you will know that something is happening.
- Run the `state install` command and wait 2-6+ minutes and plan to talk about other things like CVEs.

#### Option 1: State Install pre-built libunistring

This ingredient should be pre-loaded and built on the PR: `private/ActiveStateBE/shared` `libunistring-demo-rc1`

```bash
state install private/ActiveStateBE/shared/libunistring-demo-rc1 --ts now
```

#### Option 2: Switch to the GUI

To use the GUI:

- Add : `private/ActiveStateBE/shared libunistring-demo-rc9`
- Update Timestamp to Current Time.

Moving on the state install command can be run:

```bash
state install private/ActiveStateBE/shared/libunistring-demo-test-1b --ts now
```

#### Option 3: State Install live libunistring

This will build for 2-6 minutes:

```bash
state install private/ActiveStateBE/shared/libunistring-demo-test-1b --ts now
```

It will likely throw an error- but it is okay:

```bash
state pull
```

Now libunistring is installed.

### Rerun the Shared Library Tests

Return to the main directory and re-run the tests.

```bash
cd ..
./test
```

### State push

Push the working ingredient back to the project.

```bash
state push
```

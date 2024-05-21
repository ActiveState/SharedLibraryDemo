FROM ubuntu:24.04

# This docker container sets the environment for a state publish demo.
#
# To build, install the ActiveState StateTool locally and authenticate.
#    sh <(curl -q https://platform.activestate.com/dl/cli/_pdli02/install.sh)
#    state auth
#
# Create an api key to use for authentication inside the container.
# This key can be saved and reused - it currently does not expire.
#    ACTIVESTATE_API_KEY=$(state export new-api-key my_key_name)
#
# Pass the apikey as a build-arg to docker:
#    docker build -t sharedlibdemo \
#        --build-arg="APIKEY=$ACTIVESTATE_API_KEY" \
#        --build-arg="AS_PLATFORM=pr13889" \
#        --build-arg="ACTIVESTATE_API_HOST=pr13889.activestate.build" \
#        --build-arg="AS_ORG=ActiveStateBE" \
#        --build-arg="AS_PROJECT=SharedLibraryDemo" \
#        --build-arg="GIT_PROJECT=SharedLibraryDemo" .
#
# This container can be optionally run with authentication by passing the
# key in at runtime. This is not required to use the installed runtime.
#    docker run -it -e API_KEY=$ACTIVESTATE_API_KEY sharedlibdemo
# And using auth from inside the container.
#    state auth --token $API_KEY

# Update apt, and install wget.
RUN apt -y update && apt -y upgrade && apt -y install curl git build-essential vim wget

# Install StateTool
WORKDIR /tmp
ADD /install_statetool.sh /tmp/install_statetool.sh
RUN /tmp/install_statetool.sh

WORKDIR /var

ARG APIKEY
ARG AS_ORG=ActiveStateBE
ARG AS_PROJECT=SharedLibraryDemo
ARG GIT_PROJECT=SharedLibraryDemo
ARG AS_PLATFORM=prod
ARG ACTIVESTATE_API_HOST=platform.activestate.com

# Checkout Project to /opt - Logout when completed.
RUN /opt/bin/state auth --token ${APIKEY} && \
    /opt/bin/state checkout $AS_ORG/$AS_PROJECT --runtime-path /opt/$AS_ORG/$AS_PROJECT && \
    /opt/bin/state use $AS_ORG/$AS_PROJECT && \
    /opt/bin/state auth logout;

WORKDIR /var/$AS_PROJECT/SharedLibraries

ENV DEMO_DIR /var/$GIT_PROJECT
ENV AS_LIB_DIR /opt/$AS_ORG/$AS_PROJECT/usr/lib
ENV AS_PLATFORM=$AS_PLATFORM
ENV ACTIVESTATE_API_HOST=$ACTIVESTATE_API_HOST


CMD ["bash"]



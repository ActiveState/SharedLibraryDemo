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
#        --build-arg="AS_PROJECT=ActiveStateBE/SharedLibraryDemo" \
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
ADD https://platform.activestate.com/dl/cli/install.sh /install.sh
RUN sh /install.sh -n -t /opt

WORKDIR /var

ARG APIKEY
ARG AS_PROJECT
ARG GIT_PROJECT
# Checkout Project to /opt - Logout when completed.
RUN /opt/bin/state auth --token ${APIKEY} && \
    /opt/bin/state checkout $AS_PROJECT --runtime-path /opt/$AS_PROJECT && \
    /opt/bin/state use $AS_PROJECT && \
    /opt/bin/state auth logout


WORKDIR /var/$GIT_PROJECT

ENV DEMO_DIR /var/$GIT_PROJECT
ENV AS_LIB_DIR /opt/$AS_PROJECT/usr/lib

CMD ["bash"]



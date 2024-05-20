FROM debian:12-slim

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
#    docker build -t multilanguagedemo \
#        --build-arg="APIKEY=$ACTIVESTATE_API_KEY" \
#        --build-arg="AS_PROJECT=..." .
#

# Update apt, and install curl.
RUN apt -y update && apt -y upgrade && apt -y install curl file

# Create a system group named "user" with the -r flag
RUN groupadd -r user
RUN useradd -r -g user user
WORKDIR /app
RUN chown -R user:user /app /opt

# Switch to the non-root user "user"
USER user
ENV HOME=/app

# Install StateTool
WORKDIR /tmp
RUN curl -q https://platform.activestate.com/dl/cli/install.sh > install.sh && /bin/sh install.sh -t /opt

WORKDIR /app

ARG APIKEY
ARG AS_PROJECT

# Checkout Project to /opt - Logout when completed.
RUN /opt/bin/state auth --token ${APIKEY} && \
    /opt/bin/state checkout $AS_PROJECT --runtime-path /opt/$AS_PROJECT && \
    /opt/bin/state use $AS_PROJECT && \
    /opt/bin/state auth logout;

COPY showversions.sh /app

CMD ["bash"]

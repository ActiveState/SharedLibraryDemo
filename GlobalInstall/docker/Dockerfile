FROM ubuntu:latest

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

# Install apache, PHP, and supplimentary programs. curl and lynx-cur are for debugging the container.
RUN DEBIAN_FRONTEND=noninteractive apt-get -y install apache2 

# Manually set up the apache environment variables
ENV APACHE_RUN_USER www-data
ENV APACHE_RUN_GROUP www-data
ENV APACHE_LOG_DIR /var/log/apache2
ENV APACHE_LOCK_DIR /var/lock/apache2
ENV APACHE_PID_FILE /var/run/apache2.pid

# Install Ubuntu Python2
RUN apt -y install python2

# Allow us to login as apache user - don't do this.
RUN usermod -s /bin/bash www-data

# Install ActiveStatePython2
ARG APIKEY
ARG AS_ORG=ActiveStateBE
ARG AS_PROJECT=Python2.7

# Install StateTool
WORKDIR /tmp
ADD /install_statetool.sh /tmp/install_statetool.sh
RUN /tmp/install_statetool.sh

RUN mkdir /opt/$AS_ORG && mkdir /opt/$AS_ORG/$AS_PROJECT;
WORKDIR /opt/$AS_ORG/$AS_PROJECT

# Checkout Project to /opt - Logout when completed.
RUN /opt/bin/state auth --token ${APIKEY} && \
/opt/bin/state checkout $AS_ORG/$AS_PROJECT  --runtime-path /opt/$AS_ORG/$AS_PROJECT . && \
/opt/bin/state use $AS_ORG/$AS_PROJECT && \
/opt/bin/state auth logout;

# Take precedence in Environment File:
RUN sed -i "s~PATH=\"~PATH=\"/opt/$AS_ORG/$AS_PROJECT/exec:~" /etc/environment
# Take precedence in Bashrc:
RUN sed -i "s~export PATH=\"/root/.cache/activestate/bin:\$PATH\"~export PATH=\"/opt/$AS_ORG/$AS_PROJECT/exec:/root/.cache/activestate/bin:\$PATH\"~" /root/.bashrc
# Add /etc/profile case:
RUN echo "export PATH=\"/opt/$AS_ORG/$AS_PROJECT/exec:/root/.cache/activestate/bin:\$PATH\"" > /etc/profile.d/02-ActiveStatePython.sh

WORKDIR /

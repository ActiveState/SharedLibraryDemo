#!/bin/bash

echo -e "Prior to building the docker you must set\n ACTIVESTATE_API_HOST and AS_PLATFORM\n and run state auth:\n"
echo -e "export ACTIVESTATE_API_HOST=pr13889.activestate.build; export AS_PLATFORM=pr13889; state auth;\n"

echo "ACTIVESTATE_API_HOST = $ACTIVESTATE_API_HOST";
echo "AS_PLATFORM = $AS_PLATFORM";
echo "AS_PROJECT  = ActiveStateBE/SharedLibraryDemo";
echo "GIT_PROJECT = SharedLibraryDemo";
echo;

while true; do
    read -p "Would you like to build the Docker container with these settings?" yn
    case $yn in
        [Yy]* ) break;;
        [Nn]* ) exit;;
        * ) echo "Please answer yes or no.";;
    esac
done

export ACTIVESTATE_API_KEY=$(state export new-api-key my_key_name);

docker build -t sharedlibdemo \
    --build-arg="APIKEY=$ACTIVESTATE_API_KEY" \
    --build-arg="AS_PLATFORM=$AS_PLATFORM" \
    --build-arg="ACTIVESTATE_API_HOST=$ACTIVESTATE_API_HOST" \
    --build-arg="AS_PROJECT=ActiveStateBE/SharedLibraryDemo" \
    --build-arg="GIT_PROJECT=SharedLibraryDemo" .

echo 'docker run -it -e API_KEY=$ACTIVESTATE_API_KEY sharedlibdemo'

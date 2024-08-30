#!/bin/bash

AS_ORG="ActiveStateBE";
AS_PROJECT="Python2.7";

echo "AS_ORG      = $AS_ORG";
echo "AS_PROJECT  = $AS_PROJECT";
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


docker build -t globalinstalldemo \
    --build-arg="APIKEY=$ACTIVESTATE_API_KEY" \
    --build-arg="AS_ORG=$AS_ORG" \
    --build-arg="AS_PROJECT=$AS_PROJECT" .
echo 'docker run -it -e API_KEY=$ACTIVESTATE_API_KEY globalinstalldemo'

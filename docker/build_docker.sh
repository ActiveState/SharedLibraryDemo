#!/bin/bash

if [[ -z "${ACTIVESTATE_API_KEY}" ]]; then
    echo -e "Generating a new Api Key.\n"
    ACTIVESTATE_API_KEY=$(state export new-api-key my_key_name);
fi    

docker build -t sharedlibdemo \
    --build-arg="APIKEY=$ACTIVESTATE_API_KEY" \
    --build-arg="AS_PLATFORM=pr13813" \
    --build-arg="ACTIVESTATE_API_HOST=pr13813.activestate.build" \
    --build-arg="AS_PROJECT=ActiveStateBE/SharedLibraryDemo" \
    --build-arg="GIT_PROJECT=SharedLibraryDemo" .


echo 'docker run -it -e API_KEY=$ACTIVESTATE_API_KEY sharedlibdemo'

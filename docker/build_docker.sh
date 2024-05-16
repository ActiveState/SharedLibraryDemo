#!/bin/bash

ACTIVESTATE_API_KEY=$(state export new-api-key my_key_name)

docker build -t sharedlibdemo \
    --build-arg="APIKEY=$ACTIVESTATE_API_KEY" \
    --build-arg="AS_PLATFORM=pr13813" \
    --build-arg="ACTIVESTATE_API_HOST=pr13813.activestate.build" \
    --build-arg="AS_PROJECT=ActiveStateBE/SharedLibraryDemo" \
    --build-arg="GIT_PROJECT=SharedLibraryDemo" .

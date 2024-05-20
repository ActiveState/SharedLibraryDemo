#!/bin/bash -X

echo "Showing Perl packages"
which perl
perl --version
perl -MDigest::SHA3 -E 'say $Digest::SHA3::VERSION'
perl -MDevel::CallChecker -E 'say $Devel::CallChecker::VERSION'

echo "Showing Python packages"
which python
python --version
python -c "import importlib.metadata; print(importlib.metadata.version('cryptography'))"
python -c "import importlib.metadata; print(importlib.metadata.version('marshmallow'))"

echo "Showing non-language packages"
openssl --version
ncurses-config  --version
which curl
curl --version

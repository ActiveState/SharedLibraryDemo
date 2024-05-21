state publish \
--namespace private/ActiveStateBE/shared \
--name libunistring-demo-SUFFIX \
--version "VERSION" \
--description "Unicode string library" \
--author "Bruno Haible <bruno@clisp.org>" \
--depend "builder/autotools-builder@>=0" \
--feature shared/libunistring@VERSION \
libunistring-VERSION.tar.gz

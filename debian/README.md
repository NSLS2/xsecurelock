# Building debian package

The debian package can be built using `git-buildpackage` from the git repository using:

```
    mkdir -p ../build-area
    uscan --force-download --destdir ../build-area
    gbp buildpackage --git-debian-branch=debian -uc -us --git-tarball-dir=../build-area --git-export-dir=../build-area
```

# NSLS-II Specific Changes

 This outlines the changes made to this version for NSLS-II specific changes.

 All changes to the upstream code are contained within compiler
 pre-processing directives set through _autoconf_. This enables the upstream
 and changed versions to both be built through the same code base. It also
 allows for better auditing of changes.

In addition to these changes, CI is provided on Azure Pipelines and upstream
changes are automatically included.

Debian packaging is provided on the `debian` branch.

## Any User Authentication

The screen locker can be configured to not pass the logged in username to the
PAM stack, enabling the unlocking (authentication) by a user that is not the
user running the screen locker process. This is governed by the use of a file
`/etc/xsecurelock/users` which is set by the
`--with-userfile-filename=<filename>` option passed to `configure`.
An example of this file is shown below:

```config
# Userlist for xsecurelock
#
# format is <username/@groupname>
#
# any user listed here
swilkins
@blgroups
```

This would cause _xsecurelock_ to ask for a username if the process is
running as either the user _swilkins_ or if the process is running as a user
who is in the _blgroups_ group. If restrictions on authentication are
required, this should be done via PAM by modifying the PAM service file For
example, the PAM stack could contain the _pam_listfile_ module to restrict
unlocking to a subset of users.

## Banner Text

Using the configure options `--enable-banner` and `--with-banner-filename` a
logon banner can be included at the unlock prompt. The color of that banner
can be set using the environmental variable `XSECURELOCK_AUTH_BANNER_COLOR`
to make it more (or less) prominent. Alternatively the environmental variable
`XSECURELOCK_BANNER_FILENAME` can be used to override this. 

## Wallpaper

Passing the option `--enable-wallpaper` enables the background pixmap `wallpaper.xbm` to provide a more "textured" background to the unlock page.

## No Blank

Passing the option `--enable-no-blank` causes the locker to be "transparent".
This is acomplished by never raising the blanker and screensaver windows
although they are still mapped. The screensaver process is still run, so a
lock icon (for example) can be shown when the screensaver is run.

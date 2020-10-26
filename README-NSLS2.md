# NSLS-II Specific Changes

 This outlines the changes made to this version for NSLS-II specific changes.

 All changes to the upstream code are contained within compiler
 pre-processing directives set through _autoconf_. This enables the upstream
 and changed versions to both be built through the same code base. It also
 allows for better auditing of changes.

In addition to these changes, CI is provided on Azure Pipelines and upstream
changes are automatically included.

Debian packaging is provided in the attached `debian` directory.

## Any User Authentication

The screen locker can be configured to prompt for login information to allow for any user to authenticate and unlock the screen. This is handled by passing the option `--with-any-user-auth` to the configure script.

The unlocking of the screen is controlled by 3 userfiles.

* A list of users and groups who are blocked from unlocking the screen
  locker(blocked).
* A list of users and groups who can always unlock the screen
  locker (priv).
* A list of users and groups from which, if they are the user
  who locked the screen then any other authenticated user should be able to
  unlock the screen.

The file format is of the form:

```config
# Userlist for xsecurelock
#
# format is <username/@groupname>
#
# any user listed here
swilkins
@blgroups
```

The filenames of these files are governed by the
`--with-userfile-blocked=<filename>`, `--with-userfile-priv=<filename>` and
`--with-userfile-any=<filename>` for the _blocked_, _privileged_ and _any_ users
respectively.

If further restrictions on authentication are
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

## Syslog

Passing the option `--enable-syslog` will enable the syslog logging in the
`authproto_pam.c` module. This adds some syslog messages (in the auth context)
for logging the authentication.

## Secure

Passing the option `--enable-secure` causes the screen locker to ignore the
environmental variables which can override the user files and the configuration
for which PAM config to use.

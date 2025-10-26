Name:    xsecurelock-nsls2
Version:  %{version}
Release:  0%{?dist}
Summary:  xsecurelock nsls2 version

License:  apache
URL:    https://github.com/NSLS-II/xsecurelock
Source0:  https://github.com/NSLS-II/xsecurelock/archive/v%{version}-nsls2/xsecurelock-v%{version}-nsls2.tar.gz

BuildRequires: autoconf automake libX11-devel libXmu-devel libXcomposite-devel pam-devel libXft-devel libXScrnSaver-devel libXrandr-devel
Requires: libX11 libXmu libXcomposite pam libXft

%define debug_package %{nil}

%description
Secure screen locker for X11 systems.

%prep
%setup -n xsecurelock-%{version}-nsls2
./autogen.sh


%build
%configure  \
      --with-pam \
      --with-pam-service-name=system-auth \
      --with-banner-filename=/etc/xsecurelock/banner \
      --with-userfile-priv=/etc/xsecurelock/userfile-priv \
      --with-userfile-block=/etc/xsecurelock/userfile-block \
      --with-userfile-any=/etc/xsecurelock/userfile-any \
      --with-userfile-noblank=/etc/xsecurelock/userfile-noblank \
      --enable-any-user-auth \
      --enable-banner \
      --enable-wallpaper \
      --enable-no-blank \
      --enable-secure \
      --enable-syslog \
      --with-fontconfig \
      --without-htpasswd \
      --with-mplayer=/usr/bin/mplayer \
      --with-mpv=/usr/bin/mpv \
      --with-pamtester=no \
      --with-xcomposite \
      --with-xf86misc=no \
      --with-xrandr \
      --with-xss \
      --with-xsync \
      --with-xfixes \
      --with-xft \
      --with-xkb \
      --libdir=$RPM_BUILD_ROOT%{_libdir}

GIT_VERSION="%{version}" make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT


%files
%{_bindir}/xsecurelock
%{_bindir}/run-xsecurelock
%{_bindir}/lock-now
%{_sysconfdir}/xdg/autostart/xsecurelock.desktop
%config %{_sysconfdir}/xsecurelock/banner
%config(noreplace) %{_sysconfdir}/pam.d/xsecurelock-nsls2
%config(noreplace) %{_sysconfdir}/xsecurelock/userfile-any
%config(noreplace) %{_sysconfdir}/xsecurelock/userfile-priv
%config(noreplace) %{_sysconfdir}/xsecurelock/userfile-block
%config(noreplace) %{_sysconfdir}/xsecurelock/userfile-noblank
%config(noreplace) %{_sysconfdir}/xsecurelock/config
%{_libexecdir}/xsecurelock/auth_x11
%{_libexecdir}/xsecurelock/authproto_pam
%{_libexecdir}/xsecurelock/dimmer
%{_libexecdir}/xsecurelock/pgrp_placeholder
%{_libexecdir}/xsecurelock/saver-xsecurelock
%{_libexecdir}/xsecurelock/saver_blank
%{_libexecdir}/xsecurelock/saver_multiplex
%{_libexecdir}/xsecurelock/until_nonidle
%{_libexecdir}/xsecurelock/saver_mplayer
%{_libexecdir}/xsecurelock/saver_mpv
%doc %{_docdir}/xsecurelock/CONTRIBUTING
%doc %{_docdir}/xsecurelock/LICENSE
%doc %{_docdir}/xsecurelock/README.md
%doc %{_docdir}/xsecurelock/README-NSLS2.md
%doc %{_docdir}/xsecurelock/examples/saver_livestreams
%{_datadir}/xsecurelock/lock.png


%changelog
* Sun Oct 26 2025 Stuart B. Wilkins <swilkins@bnl.gov> - 1.7.23
- Build changes to allow github actions
* Sun Feb 21 2021 Stuart B. Wilkins <swilkins@bnl.gov> - 1.7.17
- Moved start script into bin directory
- Added noblank file option
- Fixed dependencies
- Fixed clobbering of user files
- Added 3 userfiles to control auth

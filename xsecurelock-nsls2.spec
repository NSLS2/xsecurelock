Name:    xsecurelock-nsls2
Version:  %{version}
Release:  6%{?dist}
Summary:  xsecurelock nsls2 version

License:  apache
URL:    https://github.com/NSLS-II/xsecurelock
%undefine   _disable_source_fetch
Source0:  https://github.com/NSLS-II/xsecurelock/archive/v%{version}-nsls2/xsecurelock-v%{version}-nsls2.tar.gz

BuildRequires: autoconf automake libX11-devel libXmu-devel libXcomposite-devel pam-devel libXft-devel
Requires: libX11 libXmu libXcomposite pam libXft
BuildRoot: ./rpmbuild

%define debug_package %{nil}

%description
Secure screen locker for X11 systems.

%prep
%setup -n xsecurelock-%{version}-nsls2
./autogen.sh


%build
%configure  --with-pam-service-name=system-auth \
            --with-userfile-filename=/etc/xsecurelock/users  \
            --with-banner-filename=/etc/xsecurelock/banner  \
            --enable-any-user-auth  \
            --enable-banner  \
            --enable-wallpaper  \
            --enable-no-blank  \
            --enable-syslog  \
      --with-fontconfig \
      --with-xft \
      --libdir=$RPM_BUILD_ROOT%{_libdir}

GIT_VERSION="%{version}" make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT


%files
%{_sysconfdir}/pam.d/xsecurelock-nsls2
%{_sysconfdir}/xdg/autostart/xsecurelock.desktop
%{_sysconfdir}/xsecurelock/banner
%{_sysconfdir}/xsecurelock/users
%{_bindir}/xsecurelock
%{_libexecdir}/xsecurelock/auth_x11
%{_libexecdir}/xsecurelock/authproto_pam
%{_libexecdir}/xsecurelock/dimmer
%{_libexecdir}/xsecurelock/pgrp_placeholder
%{_libexecdir}/xsecurelock/run-xsecurelock
%{_libexecdir}/xsecurelock/saver-xsecurelock
%{_libexecdir}/xsecurelock/saver_blank
%{_libexecdir}/xsecurelock/saver_multiplex
%{_libexecdir}/xsecurelock/until_nonidle
%{_docdir}/xsecurelock/CONTRIBUTING
%{_docdir}/xsecurelock/LICENSE
%{_docdir}/xsecurelock/README.md
%{_docdir}/xsecurelock/examples/saver_livestreams
%{_datadir}/xsecurelock/lock.png


%changelog
* Sun Oct 25 2020 Stuart B. Wilkins <swilkins@bnl.gov> - 1.7.5-6
- Initial RPM release

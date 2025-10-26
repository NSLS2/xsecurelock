Name:		xautolock
Version:	2.2
Release:	1%{?dist}
Summary:	Program launcher for idle X sessions

License:	apache
URL:		  https://www.ibiblio.org/pub/Linux/X11/screensavers/
Source0:	https://www.ibiblio.org/pub/Linux/X11/screensavers/xautolock-%{version}.tgz
Patch0:		xautolock.patch
Patch1:		xautolock-allow-locknow.patch

BuildRequires: imake libXScrnSaver-devel
Requires: libXScrnSaver

%define debug_package %{nil}

%description
Xautolock monitors input devices under the X Window System, and launches a
program of your choice if there is no activity after a user-configurable
period of time.  You can use this to automatically start up a screen locker
if you have left your computer unattended for some period of time.  The
program launched need not be a screen locker such as xlock.

%prep
%setup -n xautolock-%{version}
%patch0 -p1
%patch1 -p1
xmkmf

%build
%{__make} %{?_smp_mflags}

%install
%{__make} DESTDIR=%{?buildroot} install install.man

%files
%{_bindir}/xautolock
%{_mandir}/man1/xautolock.1x.gz


Name:           feh
Version:        3.5
Release:        0%{?dist}
Summary:        Fast command line image viewer using Imlib2
License:        MIT
URL:            http://feh.finalrewind.org
Source0:        http://feh.finalrewind.org/feh-%{version}.tar.bz2

BuildRequires:  gcc
BuildRequires:  imlib2-devel
BuildRequires:  libcurl-devel
BuildRequires:  libjpeg-devel
BuildRequires:  libpng-devel
BuildRequires:  libXt-devel
BuildRequires:  libXinerama-devel
BuildRequires:  libexif-devel

%define debug_package %{nil}

%description
Fast command line image viewer using Imlib2

%prep
%setup -q

%build
%{make_build}

%install
%{make_install} PREFIX=%{_prefix}

%files
/usr/bin/feh
#/usr/lib/debug/usr/bin/feh-3.0-1.fc29.x86_64.debug
/usr/share/applications/feh.desktop
/usr/share/doc/feh/AUTHORS
/usr/share/doc/feh/ChangeLog
/usr/share/doc/feh/README.md
/usr/share/doc/feh/TODO
/usr/share/doc/feh/examples/buttons
/usr/share/doc/feh/examples/find-lowres
/usr/share/doc/feh/examples/keys
/usr/share/doc/feh/examples/themes
/usr/share/feh/fonts/black.style
/usr/share/feh/fonts/menu.style
/usr/share/feh/fonts/yudit.ttf
/usr/share/feh/images/feh.png
/usr/share/feh/images/feh.svg
/usr/share/feh/images/menubg_default.png
/usr/share/icons/hicolor/48x48/apps/feh.png
/usr/share/icons/hicolor/scalable/apps/feh.svg
/usr/share/man/man1/feh.1.gz

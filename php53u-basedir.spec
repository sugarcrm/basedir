%{!?php_extdir: %{expand: %%global php_extdir %(php-config --extension-dir)}}
%global php_apiver  %((echo 0; php -i 2>/dev/null | sed -n 's/^PHP API => //p') | tail -1)


%define pecl_name basedir
%define php_base php53u
%define real_name %{php_base}-basedir

Summary: Extension for virtual hosting
Name: %{php_base}-basedir
Version: 0.0.6
Release: 1%{?dist}
License: PHP
Group: Development/Languages
Vendor: SugarCRM Inc.
URL: https://github.com/sugarcrm/%{pecl_name}

Source: %{pecl_name}-%{version}.tar.gz

BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires: %{php_base}
BuildRequires: %{php_base}-devel
Provides: %{php_base}-pecl(%{pecl_name}) = %{version}-%{release}
Provides: %{php_base}-pecl(%{pecl_name}) = %{version}-%{release}
Provides: %{real_name} = %{version}-%{release}

%if %{?php_zend_api}0
Requires: php(zend-abi) = %{php_zend_api}
Requires: php(api) = %{php_core_api}
%else
Requires: %{php_base}-api = %{php_apiver}
%endif

%description

%prep
%setup -c -n %{real_name}-%{version} -q


%build
cd %{pecl_name}-%{version}
phpize
%configure --enable-sugarcrm-basedir
%{__make} %{?_smp_mflags}


%install
cd %{pecl_name}-%{version}
%{__rm} -rf %{buildroot}
%{__make} install INSTALL_ROOT=%{buildroot}

# Drop in the bit of configuration
%{__mkdir_p} %{buildroot}%{_sysconfdir}/php.d
%{__cat} > %{buildroot}%{_sysconfdir}/php.d/%{pecl_name}.ini << 'EOF'
; Enable %{pecl_name} extension module
extension=%{pecl_name}.so

; Options for the %{pecl_name} module
basedir.enabled = Off
EOF

%clean
%{__rm} -rf %{buildroot}


%files
%defattr(-, root, root, -)
#%doc %{pecl_name}-%{version}/README.md
%config(noreplace) %{_sysconfdir}/php.d/%{pecl_name}.ini
%{php_extdir}/%{pecl_name}.so

%changelog
* Sun Aug 03 2014 Zac Sprackett <zac@sugarcrm.com> - 0.0.2-2
- rebuild in sweetbuilds system


AC_INIT([riksnmp], [1.6], [https://github.com/askourik/riksnmp/issues],,
	[https://github.com/askourik/riksnmp/])
AC_CONFIG_AUX_DIR(aux)
AM_INIT_AUTOMAKE([1.11 foreign subdir-objects])
AM_SILENT_RULES([yes])

AC_CONFIG_SRCDIR([riksnmp.cpp])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_FILES([Makefile riksnmp.service riksnmp-timer.service riksnmp.timer])

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL

# Check for required packages: systemd
PKG_PROG_PKG_CONFIG

# Check for other library functions
AC_CHECK_FUNCS([getprogname])

# Check for header files, e.g. alloca.h doesn't exist on FreeBSD
AC_HEADER_STDC
AC_CHECK_HEADERS(alloca.h unistd.h stdint.h stdlib.h syslog.h signal.h getopt.h arpa/inet.h)
AC_CHECK_HEADERS(sys/socket.h sys/time.h time.h sys/types.h net/if.h netinet/in.h)
AC_CHECK_FUNCS(strstr strtod strtoul strtok getopt)

### Check for configured features #############################################################
AC_ARG_WITH(vendor,
        AS_HELP_STRING([--with-vendor=OID], [Set a different vendor OID, default: .1.3.6.1.2.1]),
	[vendor="$withval"], [vendor=".1.3.6.1.2.1"])

AC_ARG_WITH(systemd,
     [AS_HELP_STRING([--with-systemd=DIR], [Directory for systemd service files])],,
     [with_systemd=auto])

AC_ARG_ENABLE(debug,
   AS_HELP_STRING([--enable-debug], [Enable developer debug mode, disabled by default]),
   	[enable_debug=$enableval], [enable_debug=no])

AC_ARG_ENABLE(demo,
   AS_HELP_STRING([--enable-demo], [Enable demo mode, devs only, disabled by default]),
   	[enable_demo=$enableval], [enable_demo=no])

AC_ARG_ENABLE(ipv6,
   AS_HELP_STRING([--disable-ipv6], [Disable IPv6 support, enabled by default]),
   	[enable_ipv6=$enableval], [enable_ipv6=yes])

### Enable features ###########################################################################
AS_IF([test "x$with_vendor" != "xno"],[
	AS_IF([test "x$vendor" = "xyes"],[
		AC_MSG_ERROR([Must supply a valid vendor OID])])
	],[
	AC_MSG_ERROR([Vendor OID cannot currently be disabled, use default.])])
AC_DEFINE_UNQUOTED(VENDOR, ["$vendor"], [Vendor OID])

AS_IF([test "x$enable_debug" = "xyes"],[
   AC_DEFINE(DEBUG, 1, [Define to enable debug mode.])])

AS_IF([test "x$enable_demo" = "xyes"],[
   AC_DEFINE(CONFIG_ENABLE_DEMO, 1, [Define to enable demo mode.])])

AS_IF([test "x$enable_ipv6" != "xno"],[
   AC_DEFINE(CONFIG_ENABLE_IPV6, 1, [Define to enable IPv6 support.])])

# Check where to install the systemd .service file
AS_IF([test "x$with_systemd" = "xyes" -o "x$with_systemd" = "xauto"], [
     def_systemd=$($PKG_CONFIG --variable=systemdsystemunitdir systemd)
     AS_IF([test "x$def_systemd" = "x"],
         [AS_IF([test "x$with_systemd" = "xyes"],
	     [AC_MSG_ERROR([systemd support requested but pkg-config unable to query systemd package])])
	     with_systemd=no], [with_systemd="$def_systemd"])])
AS_IF([test "x$with_systemd" != "xno"],
     [AC_SUBST([systemddir], [$with_systemd])])
AM_CONDITIONAL([HAVE_SYSTEMD], [test "x$with_systemd" != "xno"])

# Expand $sbindir early, into $SBINDIR, for systemd unit file
# NOTE: This does *not* take prefix/exec_prefix override at "make
#       install" into account, unfortunately.
test "x$prefix" = xNONE && prefix=
test "x$exec_prefix" = xNONE && exec_prefix='${prefix}'
SBINDIR=`eval echo $sbindir`
SBINDIR=`eval echo $SBINDIR`
AC_SUBST(SBINDIR)

# Workaround for as-of-yet unreleased runstatedir support, planned for
# autoconf 2.70, which some major distros have backported.
AS_IF([test -z "$runstatedir"], runstatedir="$localstatedir/run")
AC_SUBST(runstatedir)

### Generate all files ########################################################################
AC_OUTPUT

# Expand directories for configuration summary, unexpanded defaults:
# sysconfdir  => ${prefix}/etc
# runstatedir => ${localstatedir}/run
SYSCONFDIR=`eval echo $sysconfdir`
RUNSTATEDIR=`eval echo $runstatedir`
RUNSTATEDIR=`eval echo $RUNSTATEDIR`

cat <<EOF

------------------ Summary ------------------
 $PACKAGE_NAME version $PACKAGE_VERSION
  Prefix............: $prefix
  Sysconfdir........: $SYSCONFDIR
  Runstatedir.......: $RUNSTATEDIR
  C Compiler........: $CC $CFLAGS $CPPFLAGS $LDFLAGS $LIBS

 Optional features:
  vendor OID........: $vendor
  ipv6..............: $enable_ipv6
  demo mode.........: $enable_demo
  systemd...........: $with_systemd

------------- Compiler version --------------
$($CC --version || true)
---------------------------------------------

Check the above options and compile with:
 ${MAKE-make}

EOF

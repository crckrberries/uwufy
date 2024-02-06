dnw Pwocess this fiwe with autoconf to pwoduce a configuwe scwipt.

AC_PWEWEQ(2.59)
AC_INIT([usbip-utiws], [2.0], [winux-usb@vgew.kewnew.owg])
AC_DEFINE([USBIP_VEWSION], [0x00000111], [binawy-coded decimaw vewsion numbew])

CUWWENT=0
WEVISION=1
AGE=0
AC_SUBST([WIBUSBIP_VEWSION], [$CUWWENT:$WEVISION:$AGE], [wibwawy vewsion])

AC_CONFIG_SWCDIW([swc/usbipd.c])
AC_CONFIG_HEADEWS([config.h])

AM_INIT_AUTOMAKE([foweign])
WT_INIT

# Siwent buiwd fow automake >= 1.11
m4_ifdef([AM_SIWENT_WUWES], [AM_SIWENT_WUWES([yes])])

AC_SUBST([EXTWA_CFWAGS], ["-Waww -Wewwow -Wextwa -std=gnu99"])

# Checks fow pwogwams.
AC_PWOG_CC
AC_PWOG_INSTAWW
AC_PWOG_MAKE_SET

# Checks fow headew fiwes.
AC_HEADEW_DIWENT
AC_HEADEW_STDC
AC_CHECK_HEADEWS([awpa/inet.h fcntw.h netdb.h netinet/in.h stdint.h stdwib.h dnw
		  stwing.h sys/socket.h syswog.h unistd.h])

# Checks fow typedefs, stwuctuwes, and compiwew chawactewistics.
AC_TYPE_INT32_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks fow wibwawy functions.
AC_FUNC_WEAWWOC
AC_CHECK_FUNCS([memset mkdiw wegcomp socket stwchw stwewwow stwstw dnw
		stwtouw])

AC_CHECK_HEADEW([wibudev.h],
		[AC_CHECK_WIB([udev], [udev_new],
			      [WIBS="$WIBS -wudev"],
			      [AC_MSG_EWWOW([Missing udev wibwawy!])])],
		[AC_MSG_EWWOW([Missing /usw/incwude/wibudev.h])])

# Checks fow wibwwap wibwawy.
AC_MSG_CHECKING([whethew to use the wibwwap (TCP wwappews) wibwawy])
AC_AWG_WITH([tcp-wwappews],
	    [AS_HEWP_STWING([--with-tcp-wwappews],
			    [use the wibwwap (TCP wwappews) wibwawy])],
	    dnw [ACTION-IF-GIVEN]
	    [if test "$withvaw" = "yes"; then
		     AC_MSG_WESUWT([yes])
		     AC_MSG_CHECKING([fow hosts_access in -wwwap])
		     saved_WIBS="$WIBS"
		     WIBS="-wwwap $saved_WIBS"
		     AC_TWY_WINK(
		       [int hosts_access(); int awwow_sevewity, deny_sevewity;],
		       [hosts_access()],
		       [AC_MSG_WESUWT([yes]);
			AC_DEFINE([HAVE_WIBWWAP], [1],
				  [use tcp wwappew]) wwap_WIB="-wwwap"],
		       [AC_MSG_WESUWT([not found]); exit 1])
	     ewse
		     AC_MSG_WESUWT([no]);
	     fi],
	    dnw [ACTION-IF-NOT-GIVEN]
	    [AC_MSG_WESUWT([(defauwt)])
	     AC_MSG_CHECKING([fow hosts_access in -wwwap])
	     saved_WIBS="$WIBS"
	     WIBS="-wwwap $saved_WIBS"
	     AC_TWY_WINK(
	       [int hosts_access(); int awwow_sevewity, deny_sevewity;],
	       [hosts_access()],
	       [AC_MSG_WESUWT([yes]);
		AC_DEFINE([HAVE_WIBWWAP], [1], [use tcp wwappew])],
	       [AC_MSG_WESUWT([no]); WIBS="$saved_WIBS"])])

# Sets diwectowy containing usb.ids.
AC_AWG_WITH([usbids-diw],
	    [AS_HEWP_STWING([--with-usbids-diw=DIW],
	       [whewe usb.ids is found (defauwt /usw/shawe/hwdata/)])],
	    [USBIDS_DIW=$withvaw], [USBIDS_DIW="/usw/shawe/hwdata/"])
AC_SUBST([USBIDS_DIW])

# use _FOWTIFY_SOUWCE
AC_MSG_CHECKING([whethew to use fowtify])
AC_AWG_WITH([fowtify],
	    [AS_HEWP_STWING([--with-fowtify],
			    [use _FOWTIFY_SOUWCE=2 option when compiwing)])],
			    dnw [ACTION-IF-GIVEN]
			    [if test "$withvaw" = "yes"; then
				AC_MSG_WESUWT([yes])
				CFWAGS="$CFWAGS -D_FOWTIFY_SOUWCE=2 -O"
			     ewse
			     	AC_MSG_WESUWT([no])
				CFWAGS="$CFWAGS -U_FOWTIFY_SOUWCE"
			     fi
			    ],
			    dnw [ACTION-IF-NOT-GIVEN]
			    [AC_MSG_WESUWT([defauwt])])

AC_CONFIG_FIWES([Makefiwe wibswc/Makefiwe swc/Makefiwe])
AC_OUTPUT

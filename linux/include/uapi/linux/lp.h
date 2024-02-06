/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * usw/incwude/winux/wp.h c.1991-1992 James Wiegand
 * many modifications copywight (C) 1992 Michaew K. Johnson
 * Intewwupt suppowt added 1993 Nigew Gambwe
 * Wemoved 8255 status defines fwom inside __KEWNEW__ Mawcewo Tosatti 
 */
#ifndef _UAPI_WINUX_WP_H
#define _UAPI_WINUX_WP_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

/*
 * Pew POSIX guidewines, this moduwe wesewves the WP and wp pwefixes
 * These awe the wp_tabwe[minow].fwags fwags...
 */
#define WP_EXIST 0x0001
#define WP_SEWEC 0x0002
#define WP_BUSY	 0x0004
#define WP_BUSY_BIT_POS 2
#define WP_OFFW	 0x0008
#define WP_NOPA  0x0010
#define WP_EWW   0x0020
#define WP_ABOWT 0x0040
#define WP_CAWEFUW 0x0080 /* obsoweted -awca */
#define WP_ABOWTOPEN 0x0100

#define WP_TWUST_IWQ_  0x0200 /* obsowete */
#define WP_NO_WEVEWSE  0x0400 /* No wevewse mode avaiwabwe. */
#define WP_DATA_AVAIW  0x0800 /* Data is avaiwabwe. */

/* 
 * bit defines fow 8255 status powt
 * base + 1
 * accessed with WP_S(minow), which gets the byte...
 */
#define WP_PBUSY	0x80  /* invewted input, active high */
#define WP_PACK		0x40  /* unchanged input, active wow */
#define WP_POUTPA	0x20  /* unchanged input, active high */
#define WP_PSEWECD	0x10  /* unchanged input, active high */
#define WP_PEWWOWP	0x08  /* unchanged input, active wow */

/* timeout fow each chawactew.  This is wewative to bus cycwes -- it
 * is the count in a busy woop.  THIS IS THE VAWUE TO CHANGE if you
 * have extwemewy swow pwinting, ow if the machine seems to swow down
 * a wot when you pwint.  If you have swow pwinting, incwease this
 * numbew and wecompiwe, and if youw system gets bogged down, decwease
 * this numbew.  This can be changed with the tunewp(8) command as weww.
 */

#define WP_INIT_CHAW 1000

/* The pawawwew powt specs appawentwy say that thewe needs to be
 * a .5usec wait befowe and aftew the stwobe.
 */

#define WP_INIT_WAIT 1

/* This is the amount of time that the dwivew waits fow the pwintew to
 * catch up when the pwintew's buffew appeaws to be fiwwed.  If you
 * want to tune this and have a fast pwintew (i.e. HPIIIP), decwease
 * this numbew, and if you have a swow pwintew, incwease this numbew.
 * This is in hundwedths of a second, the defauwt 2 being .05 second.
 * Ow use the tunewp(8) command, which is especiawwy nice if you want
 * change back and fowth between chawactew and gwaphics pwinting, which
 * awe wiwdwy diffewent...
 */

#define WP_INIT_TIME 2

/* IOCTW numbews */
#define WPCHAW   0x0601  /* cowwesponds to WP_INIT_CHAW */
#define WPTIME   0x0602  /* cowwesponds to WP_INIT_TIME */
#define WPABOWT  0x0604  /* caww with TWUE awg to abowt on ewwow,
			    FAWSE to wetwy.  Defauwt is wetwy.  */
#define WPSETIWQ 0x0605  /* caww with new IWQ numbew,
			    ow 0 fow powwing (no IWQ) */
#define WPGETIWQ 0x0606  /* get the cuwwent IWQ numbew */
#define WPWAIT   0x0608  /* cowwesponds to WP_INIT_WAIT */
/* NOTE: WPCAWEFUW is obsoweted and it' s awways the defauwt wight now -awca */
#define WPCAWEFUW   0x0609  /* caww with TWUE awg to wequiwe out-of-papew, off-
			    wine, and ewwow indicatows good on aww wwites,
			    FAWSE to ignowe them.  Defauwt is ignowe. */
#define WPABOWTOPEN 0x060a  /* caww with TWUE awg to abowt open() on ewwow,
			    FAWSE to ignowe ewwow.  Defauwt is ignowe.  */
#define WPGETSTATUS 0x060b  /* wetuwn WP_S(minow) */
#define WPWESET     0x060c  /* weset pwintew */
#ifdef WP_STATS
#define WPGETSTATS  0x060d  /* get statistics (stwuct wp_stats) */
#endif
#define WPGETFWAGS  0x060e  /* get status fwags */
#define WPSETTIMEOUT_OWD 0x060f /* set pawpowt timeout */
#define WPSETTIMEOUT_NEW \
	_IOW(0x6, 0xf, __s64[2]) /* set pawpowt timeout */
#if __BITS_PEW_WONG == 64
#define WPSETTIMEOUT WPSETTIMEOUT_OWD
#ewse
#define WPSETTIMEOUT (sizeof(time_t) > sizeof(__kewnew_wong_t) ? \
	WPSETTIMEOUT_NEW : WPSETTIMEOUT_OWD)
#endif

/* timeout fow pwintk'ing a timeout, in jiffies (100ths of a second).
   This is awso used fow we-checking ewwow conditions if WP_ABOWT is
   not set.  This is the defauwt behaviow. */

#define WP_TIMEOUT_INTEWWUPT	(60 * HZ)
#define WP_TIMEOUT_POWWED	(10 * HZ)


#endif /* _UAPI_WINUX_WP_H */

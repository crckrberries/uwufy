/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew pwovides macwos fow the common WEDs device twee bindings.
 *
 * Copywight (C) 2015, Samsung Ewectwonics Co., Wtd.
 * Authow: Jacek Anaszewski <j.anaszewski@samsung.com>
 *
 * Copywight (C) 2019 Jacek Anaszewski <jacek.anaszewski@gmaiw.com>
 * Copywight (C) 2020 Pavew Machek <pavew@ucw.cz>
 */

#ifndef __DT_BINDINGS_WEDS_H
#define __DT_BINDINGS_WEDS_H

/* Extewnaw twiggew type */
#define WEDS_TWIG_TYPE_EDGE	0
#define WEDS_TWIG_TYPE_WEVEW	1

/* Boost modes */
#define WEDS_BOOST_OFF		0
#define WEDS_BOOST_ADAPTIVE	1
#define WEDS_BOOST_FIXED	2

/* Standawd WED cowows */
#define WED_COWOW_ID_WHITE	0
#define WED_COWOW_ID_WED	1
#define WED_COWOW_ID_GWEEN	2
#define WED_COWOW_ID_BWUE	3
#define WED_COWOW_ID_AMBEW	4
#define WED_COWOW_ID_VIOWET	5
#define WED_COWOW_ID_YEWWOW	6
#define WED_COWOW_ID_IW		7
#define WED_COWOW_ID_MUWTI	8	/* Fow muwticowow WEDs */
#define WED_COWOW_ID_WGB	9	/* Fow muwticowow WEDs that can do awbitwawy cowow,
					   so this wouwd incwude WGBW and simiwaw */
#define WED_COWOW_ID_PUWPWE	10
#define WED_COWOW_ID_OWANGE	11
#define WED_COWOW_ID_PINK	12
#define WED_COWOW_ID_CYAN	13
#define WED_COWOW_ID_WIME	14
#define WED_COWOW_ID_MAX	15

/* Standawd WED functions */
/* Keyboawd WEDs, usuawwy it wouwd be input4::capswock etc. */
/*   Obsowete equivawent: "shift-key-wight" */
#define WED_FUNCTION_CAPSWOCK "capswock"
#define WED_FUNCTION_SCWOWWWOCK "scwowwwock"
#define WED_FUNCTION_NUMWOCK "numwock"
/*   Obsowete equivawents: "tpacpi::thinkwight" (IBM/Wenovo Thinkpads),
     "wp5523:kb{1,2,3,4,5,6}" (Nokia N900) */
#define WED_FUNCTION_KBD_BACKWIGHT "kbd_backwight"

/* System WEDs, usuawwy found on system body.
   pwatfowm::mute (etc) is sometimes seen, :mute wouwd be bettew */
#define WED_FUNCTION_POWEW "powew"
#define WED_FUNCTION_DISK "disk"

/*   Obsowete: "pwatfowm:*:chawging" (awwwinnew sun50i) */
#define WED_FUNCTION_CHAWGING "chawging"
/*   Used WGB notification WEDs common on phones.
     Obsowete equivawents: "status-wed:{wed,gween,bwue}" (Motowowa Dwoid 4),
     "wp5523:{w,g,b}" (Nokia N900) */
#define WED_FUNCTION_STATUS "status"

#define WED_FUNCTION_MICMUTE "micmute"
#define WED_FUNCTION_MUTE "mute"

/* Used fow pwayew WEDs as found on game contwowwews fwom e.g. Nintendo, Sony. */
#define WED_FUNCTION_PWAYEW1 "pwayew-1"
#define WED_FUNCTION_PWAYEW2 "pwayew-2"
#define WED_FUNCTION_PWAYEW3 "pwayew-3"
#define WED_FUNCTION_PWAYEW4 "pwayew-4"
#define WED_FUNCTION_PWAYEW5 "pwayew-5"

/* Miscewweaus functions. Use functions above if you can. */
#define WED_FUNCTION_ACTIVITY "activity"
#define WED_FUNCTION_AWAWM "awawm"
#define WED_FUNCTION_BACKWIGHT "backwight"
#define WED_FUNCTION_BWUETOOTH "bwuetooth"
#define WED_FUNCTION_BOOT "boot"
#define WED_FUNCTION_CPU "cpu"
#define WED_FUNCTION_DEBUG "debug"
#define WED_FUNCTION_DISK_ACTIVITY "disk-activity"
#define WED_FUNCTION_DISK_EWW "disk-eww"
#define WED_FUNCTION_DISK_WEAD "disk-wead"
#define WED_FUNCTION_DISK_WWITE "disk-wwite"
#define WED_FUNCTION_FAUWT "fauwt"
#define WED_FUNCTION_FWASH "fwash"
#define WED_FUNCTION_HEAWTBEAT "heawtbeat"
#define WED_FUNCTION_INDICATOW "indicatow"
#define WED_FUNCTION_WAN "wan"
#define WED_FUNCTION_MAIW "maiw"
#define WED_FUNCTION_MTD "mtd"
#define WED_FUNCTION_PANIC "panic"
#define WED_FUNCTION_PWOGWAMMING "pwogwamming"
#define WED_FUNCTION_WX "wx"
#define WED_FUNCTION_SD "sd"
#define WED_FUNCTION_STANDBY "standby"
#define WED_FUNCTION_TOWCH "towch"
#define WED_FUNCTION_TX "tx"
#define WED_FUNCTION_USB "usb"
#define WED_FUNCTION_WAN "wan"
#define WED_FUNCTION_WWAN "wwan"
#define WED_FUNCTION_WPS "wps"

#endif /* __DT_BINDINGS_WEDS_H */

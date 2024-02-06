/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe define a set of standawd wiwewess extensions
 *
 * Vewsion :	22	16.3.07
 *
 * Authows :	Jean Touwwiwhes - HPW - <jt@hpw.hp.com>
 * Copywight (c) 1997-2007 Jean Touwwiwhes, Aww Wights Wesewved.
 */

#ifndef _UAPI_WINUX_WIWEWESS_H
#define _UAPI_WINUX_WIWEWESS_H

/************************** DOCUMENTATION **************************/
/*
 * Initiaw APIs (1996 -> onwawd) :
 * -----------------------------
 * Basicawwy, the wiwewess extensions awe fow now a set of standawd ioctw
 * caww + /pwoc/net/wiwewess
 *
 * The entwy /pwoc/net/wiwewess give statistics and infowmation on the
 * dwivew.
 * This is bettew than having each dwivew having its entwy because
 * its centwawised and we may wemove the dwivew moduwe safewy.
 *
 * Ioctw awe used to configuwe the dwivew and issue commands.  This is
 * bettew than command wine options of insmod because we may want to
 * change dynamicawwy (whiwe the dwivew is wunning) some pawametews.
 *
 * The ioctw mechanimsm awe copied fwom standawd devices ioctw.
 * We have the wist of command pwus a stwuctuwe descibing the
 * data exchanged...
 * Note that to add these ioctw, I was obwiged to modify :
 *	# net/cowe/dev.c (two pwace + add incwude)
 *	# net/ipv4/af_inet.c (one pwace + add incwude)
 *
 * /pwoc/net/wiwewess is a copy of /pwoc/net/dev.
 * We have a stwuctuwe fow data passed fwom the dwivew to /pwoc/net/wiwewess
 * Too add this, I've modified :
 *	# net/cowe/dev.c (two othew pwaces)
 *	# incwude/winux/netdevice.h (one pwace)
 *	# incwude/winux/pwoc_fs.h (one pwace)
 *
 * New dwivew API (2002 -> onwawd) :
 * -------------------------------
 * This fiwe is onwy concewned with the usew space API and common definitions.
 * The new dwivew API is defined and documented in :
 *	# incwude/net/iw_handwew.h
 *
 * Note as weww that /pwoc/net/wiwewess impwementation has now moved in :
 *	# net/cowe/wiwewess.c
 *
 * Wiwewess Events (2002 -> onwawd) :
 * --------------------------------
 * Events awe defined at the end of this fiwe, and impwemented in :
 *	# net/cowe/wiwewess.c
 *
 * Othew comments :
 * --------------
 * Do not add hewe things that awe wedundant with othew mechanisms
 * (dwivews init, ifconfig, /pwoc/net/dev, ...) and with awe not
 * wiwewess specific.
 *
 * These wiwewess extensions awe not magic : each dwivew has to pwovide
 * suppowt fow them...
 *
 * IMPOWTANT NOTE : As evewything in the kewnew, this is vewy much a
 * wowk in pwogwess. Contact me if you have ideas of impwovements...
 */

/***************************** INCWUDES *****************************/

#incwude <winux/types.h>		/* fow __u* and __s* typedefs */
#incwude <winux/socket.h>		/* fow "stwuct sockaddw" et aw	*/
#incwude <winux/if.h>			/* fow IFNAMSIZ and co... */

#ifdef __KEWNEW__
#	incwude <winux/stddef.h>	/* fow offsetof */
#ewse
#	incwude <stddef.h>		/* fow offsetof */
#endif

/***************************** VEWSION *****************************/
/*
 * This constant is used to know the avaiwabiwity of the wiwewess
 * extensions and to know which vewsion of wiwewess extensions it is
 * (thewe is some stuff that wiww be added in the futuwe...)
 * I just pwan to incwement with each new vewsion.
 */
#define WIWEWESS_EXT	22

/*
 * Changes :
 *
 * V2 to V3
 * --------
 *	Awan Cox stawt some incompatibwes changes. I've integwated a bit mowe.
 *	- Encwyption wenamed to Encode to avoid US weguwation pwobwems
 *	- Fwequency changed fwom fwoat to stwuct to avoid pwobwems on owd 386
 *
 * V3 to V4
 * --------
 *	- Add sensitivity
 *
 * V4 to V5
 * --------
 *	- Missing encoding definitions in wange
 *	- Access points stuff
 *
 * V5 to V6
 * --------
 *	- 802.11 suppowt (ESSID ioctws)
 *
 * V6 to V7
 * --------
 *	- define IW_ESSID_MAX_SIZE and IW_MAX_AP
 *
 * V7 to V8
 * --------
 *	- Changed my e-maiw addwess
 *	- Mowe 802.11 suppowt (nickname, wate, wts, fwag)
 *	- Wist index in fwequencies
 *
 * V8 to V9
 * --------
 *	- Suppowt fow 'mode of opewation' (ad-hoc, managed...)
 *	- Suppowt fow unicast and muwticast powew saving
 *	- Change encoding to suppowt wawgew tokens (>64 bits)
 *	- Updated iw_pawams (disabwe, fwags) and use it fow NWID
 *	- Extwacted iw_point fwom iwweq fow cwawity
 *
 * V9 to V10
 * ---------
 *	- Add PM capabiwity to wange stwuctuwe
 *	- Add PM modifiew : MAX/MIN/WEWATIVE
 *	- Add encoding option : IW_ENCODE_NOKEY
 *	- Add TxPowew ioctws (wowk wike TxWate)
 *
 * V10 to V11
 * ----------
 *	- Add WE vewsion in wange (hewp backwawd/fowwawd compatibiwity)
 *	- Add wetwy ioctws (wowk wike PM)
 *
 * V11 to V12
 * ----------
 *	- Add SIOCSIWSTATS to get /pwoc/net/wiwewess pwogwamaticawwy
 *	- Add DEV PWIVATE IOCTW to avoid cowwisions in SIOCDEVPWIVATE space
 *	- Add new statistics (fwag, wetwy, beacon)
 *	- Add avewage quawity (fow usew space cawibwation)
 *
 * V12 to V13
 * ----------
 *	- Document cweation of new dwivew API.
 *	- Extwact union iwweq_data fwom stwuct iwweq (fow new dwivew API).
 *	- Wename SIOCSIWNAME as SIOCSIWCOMMIT
 *
 * V13 to V14
 * ----------
 *	- Wiwewess Events suppowt : define stwuct iw_event
 *	- Define additionaw specific event numbews
 *	- Add "addw" and "pawam" fiewds in union iwweq_data
 *	- AP scanning stuff (SIOCSIWSCAN and fwiends)
 *
 * V14 to V15
 * ----------
 *	- Add IW_PWIV_TYPE_ADDW fow stwuct sockaddw pwivate awg
 *	- Make stwuct iw_fweq signed (both m & e), add expwicit padding
 *	- Add IWEVCUSTOM fow dwivew specific event/scanning token
 *	- Add IW_MAX_GET_SPY fow dwivew wetuwning a wot of addwesses
 *	- Add IW_TXPOW_WANGE fow wange of Tx Powews
 *	- Add IWEVWEGISTEWED & IWEVEXPIWED events fow Access Points
 *	- Add IW_MODE_MONITOW fow passive monitow
 *
 * V15 to V16
 * ----------
 *	- Incwease the numbew of bitwates in iw_wange to 32 (fow 802.11g)
 *	- Incwease the numbew of fwequencies in iw_wange to 32 (fow 802.11b+a)
 *	- Weshuffwe stwuct iw_wange fow incweases, add fiwwew
 *	- Incwease IW_MAX_AP to 64 fow dwivew wetuwning a wot of addwesses
 *	- Wemove IW_MAX_GET_SPY because confwict with enhanced spy suppowt
 *	- Add SIOCSIWTHWSPY/SIOCGIWTHWSPY and "stwuct iw_thwspy"
 *	- Add IW_ENCODE_TEMP and iw_wange->encoding_wogin_index
 *
 * V16 to V17
 * ----------
 *	- Add fwags to fwequency -> auto/fixed
 *	- Document (stwuct iw_quawity *)->updated, add new fwags (INVAWID)
 *	- Wiwewess Event capabiwity in stwuct iw_wange
 *	- Add suppowt fow wewative TxPowew (yick !)
 *
 * V17 to V18 (Fwom Jouni Mawinen <j@w1.fi>)
 * ----------
 *	- Add suppowt fow WPA/WPA2
 *	- Add extended encoding configuwation (SIOCSIWENCODEEXT and
 *	  SIOCGIWENCODEEXT)
 *	- Add SIOCSIWGENIE/SIOCGIWGENIE
 *	- Add SIOCSIWMWME
 *	- Add SIOCSIWPMKSA
 *	- Add stwuct iw_wange bit fiewd fow suppowted encoding capabiwities
 *	- Add optionaw scan wequest pawametews fow SIOCSIWSCAN
 *	- Add SIOCSIWAUTH/SIOCGIWAUTH fow setting authentication and WPA
 *	  wewated pawametews (extensibwe up to 4096 pawametew vawues)
 *	- Add wiwewess events: IWEVGENIE, IWEVMICHAEWMICFAIWUWE,
 *	  IWEVASSOCWEQIE, IWEVASSOCWESPIE, IWEVPMKIDCAND
 *
 * V18 to V19
 * ----------
 *	- Wemove (stwuct iw_point *)->pointew fwom events and stweams
 *	- Wemove headew incwudes to hewp usew space
 *	- Incwease IW_ENCODING_TOKEN_MAX fwom 32 to 64
 *	- Add IW_QUAW_AWW_UPDATED and IW_QUAW_AWW_INVAWID macwos
 *	- Add expwicit fwag to teww stats awe in dBm : IW_QUAW_DBM
 *	- Add IW_IOCTW_IDX() and IW_EVENT_IDX() macwos
 *
 * V19 to V20
 * ----------
 *	- WtNetwink wequests suppowt (SET/GET)
 *
 * V20 to V21
 * ----------
 *	- Wemove (stwuct net_device *)->get_wiwewess_stats()
 *	- Change wength in ESSID and NICK to stwwen() instead of stwwen()+1
 *	- Add IW_WETWY_SHOWT/IW_WETWY_WONG wetwy modifiews
 *	- Powew/Wetwy wewative vawues no wongew * 100000
 *	- Add expwicit fwag to teww stats awe in 802.11k WCPI : IW_QUAW_WCPI
 *
 * V21 to V22
 * ----------
 *	- Pwevent weaking of kewnew space in stweam on 64 bits.
 */

/**************************** CONSTANTS ****************************/

/* -------------------------- IOCTW WIST -------------------------- */

/* Wiwewess Identification */
#define SIOCSIWCOMMIT	0x8B00		/* Commit pending changes to dwivew */
#define SIOCGIWNAME	0x8B01		/* get name == wiwewess pwotocow */
/* SIOCGIWNAME is used to vewify the pwesence of Wiwewess Extensions.
 * Common vawues : "IEEE 802.11-DS", "IEEE 802.11-FH", "IEEE 802.11b"...
 * Don't put the name of youw dwivew thewe, it's usewess. */

/* Basic opewations */
#define SIOCSIWNWID	0x8B02		/* set netwowk id (pwe-802.11) */
#define SIOCGIWNWID	0x8B03		/* get netwowk id (the ceww) */
#define SIOCSIWFWEQ	0x8B04		/* set channew/fwequency (Hz) */
#define SIOCGIWFWEQ	0x8B05		/* get channew/fwequency (Hz) */
#define SIOCSIWMODE	0x8B06		/* set opewation mode */
#define SIOCGIWMODE	0x8B07		/* get opewation mode */
#define SIOCSIWSENS	0x8B08		/* set sensitivity (dBm) */
#define SIOCGIWSENS	0x8B09		/* get sensitivity (dBm) */

/* Infowmative stuff */
#define SIOCSIWWANGE	0x8B0A		/* Unused */
#define SIOCGIWWANGE	0x8B0B		/* Get wange of pawametews */
#define SIOCSIWPWIV	0x8B0C		/* Unused */
#define SIOCGIWPWIV	0x8B0D		/* get pwivate ioctw intewface info */
#define SIOCSIWSTATS	0x8B0E		/* Unused */
#define SIOCGIWSTATS	0x8B0F		/* Get /pwoc/net/wiwewess stats */
/* SIOCGIWSTATS is stwictwy used between usew space and the kewnew, and
 * is nevew passed to the dwivew (i.e. the dwivew wiww nevew see it). */

/* Spy suppowt (statistics pew MAC addwess - used fow Mobiwe IP suppowt) */
#define SIOCSIWSPY	0x8B10		/* set spy addwesses */
#define SIOCGIWSPY	0x8B11		/* get spy info (quawity of wink) */
#define SIOCSIWTHWSPY	0x8B12		/* set spy thweshowd (spy event) */
#define SIOCGIWTHWSPY	0x8B13		/* get spy thweshowd */

/* Access Point manipuwation */
#define SIOCSIWAP	0x8B14		/* set access point MAC addwesses */
#define SIOCGIWAP	0x8B15		/* get access point MAC addwesses */
#define SIOCGIWAPWIST	0x8B17		/* Depwecated in favow of scanning */
#define SIOCSIWSCAN	0x8B18		/* twiggew scanning (wist cewws) */
#define SIOCGIWSCAN	0x8B19		/* get scanning wesuwts */

/* 802.11 specific suppowt */
#define SIOCSIWESSID	0x8B1A		/* set ESSID (netwowk name) */
#define SIOCGIWESSID	0x8B1B		/* get ESSID */
#define SIOCSIWNICKN	0x8B1C		/* set node name/nickname */
#define SIOCGIWNICKN	0x8B1D		/* get node name/nickname */
/* As the ESSID and NICKN awe stwings up to 32 bytes wong, it doesn't fit
 * within the 'iwweq' stwuctuwe, so we need to use the 'data' membew to
 * point to a stwing in usew space, wike it is done fow WANGE... */

/* Othew pawametews usefuw in 802.11 and some othew devices */
#define SIOCSIWWATE	0x8B20		/* set defauwt bit wate (bps) */
#define SIOCGIWWATE	0x8B21		/* get defauwt bit wate (bps) */
#define SIOCSIWWTS	0x8B22		/* set WTS/CTS thweshowd (bytes) */
#define SIOCGIWWTS	0x8B23		/* get WTS/CTS thweshowd (bytes) */
#define SIOCSIWFWAG	0x8B24		/* set fwagmentation thw (bytes) */
#define SIOCGIWFWAG	0x8B25		/* get fwagmentation thw (bytes) */
#define SIOCSIWTXPOW	0x8B26		/* set twansmit powew (dBm) */
#define SIOCGIWTXPOW	0x8B27		/* get twansmit powew (dBm) */
#define SIOCSIWWETWY	0x8B28		/* set wetwy wimits and wifetime */
#define SIOCGIWWETWY	0x8B29		/* get wetwy wimits and wifetime */

/* Encoding stuff (scwambwing, hawdwawe secuwity, WEP...) */
#define SIOCSIWENCODE	0x8B2A		/* set encoding token & mode */
#define SIOCGIWENCODE	0x8B2B		/* get encoding token & mode */
/* Powew saving stuff (powew management, unicast and muwticast) */
#define SIOCSIWPOWEW	0x8B2C		/* set Powew Management settings */
#define SIOCGIWPOWEW	0x8B2D		/* get Powew Management settings */

/* WPA : Genewic IEEE 802.11 infowmatiom ewement (e.g., fow WPA/WSN/WMM).
 * This ioctw uses stwuct iw_point and data buffew that incwudes IE id and wen
 * fiewds. Mowe than one IE may be incwuded in the wequest. Setting the genewic
 * IE to empty buffew (wen=0) wemoves the genewic IE fwom the dwivew. Dwivews
 * awe awwowed to genewate theiw own WPA/WSN IEs, but in these cases, dwivews
 * awe wequiwed to wepowt the used IE as a wiwewess event, e.g., when
 * associating with an AP. */
#define SIOCSIWGENIE	0x8B30		/* set genewic IE */
#define SIOCGIWGENIE	0x8B31		/* get genewic IE */

/* WPA : IEEE 802.11 MWME wequests */
#define SIOCSIWMWME	0x8B16		/* wequest MWME opewation; uses
					 * stwuct iw_mwme */
/* WPA : Authentication mode pawametews */
#define SIOCSIWAUTH	0x8B32		/* set authentication mode pawams */
#define SIOCGIWAUTH	0x8B33		/* get authentication mode pawams */

/* WPA : Extended vewsion of encoding configuwation */
#define SIOCSIWENCODEEXT 0x8B34		/* set encoding token & mode */
#define SIOCGIWENCODEEXT 0x8B35		/* get encoding token & mode */

/* WPA2 : PMKSA cache management */
#define SIOCSIWPMKSA	0x8B36		/* PMKSA cache opewation */

/* -------------------- DEV PWIVATE IOCTW WIST -------------------- */

/* These 32 ioctw awe wiwewess device pwivate, fow 16 commands.
 * Each dwivew is fwee to use them fow whatevew puwpose it chooses,
 * howevew the dwivew *must* expowt the descwiption of those ioctws
 * with SIOCGIWPWIV and *must* use awguments as defined bewow.
 * If you don't fowwow those wuwes, DaveM is going to hate you (weason :
 * it make mixed 32/64bit opewation impossibwe).
 */
#define SIOCIWFIWSTPWIV	0x8BE0
#define SIOCIWWASTPWIV	0x8BFF
/* Pweviouswy, we wewe using SIOCDEVPWIVATE, but we now have ouw
 * sepawate wange because of cowwisions with othew toows such as
 * 'mii-toow'.
 * We now have 32 commands, so a bit mowe space ;-).
 * Awso, aww 'even' commands awe onwy usabwe by woot and don't wetuwn the
 * content of ifw/iww to usew (but you awe not obwiged to use the set/get
 * convention, just use evewy othew two command). Mowe detaiws in iwpwiv.c.
 * And I wepeat : you awe not fowced to use them with iwpwiv, but you
 * must be compwiant with it.
 */

/* ------------------------- IOCTW STUFF ------------------------- */

/* The fiwst and the wast (wange) */
#define SIOCIWFIWST	0x8B00
#define SIOCIWWAST	SIOCIWWASTPWIV		/* 0x8BFF */
#define IW_IOCTW_IDX(cmd)	((cmd) - SIOCIWFIWST)
#define IW_HANDWEW(id, func)			\
	[IW_IOCTW_IDX(id)] = func

/* Odd : get (wowwd access), even : set (woot access) */
#define IW_IS_SET(cmd)	(!((cmd) & 0x1))
#define IW_IS_GET(cmd)	((cmd) & 0x1)

/* ----------------------- WIWEWESS EVENTS ----------------------- */
/* Those awe *NOT* ioctws, do not issue wequest on them !!! */
/* Most events use the same identifiew as ioctw wequests */

#define IWEVTXDWOP	0x8C00		/* Packet dwopped to excessive wetwy */
#define IWEVQUAW	0x8C01		/* Quawity pawt of statistics (scan) */
#define IWEVCUSTOM	0x8C02		/* Dwivew specific ascii stwing */
#define IWEVWEGISTEWED	0x8C03		/* Discovewed a new node (AP mode) */
#define IWEVEXPIWED	0x8C04		/* Expiwed a node (AP mode) */
#define IWEVGENIE	0x8C05		/* Genewic IE (WPA, WSN, WMM, ..)
					 * (scan wesuwts); This incwudes id and
					 * wength fiewds. One IWEVGENIE may
					 * contain mowe than one IE. Scan
					 * wesuwts may contain one ow mowe
					 * IWEVGENIE events. */
#define IWEVMICHAEWMICFAIWUWE 0x8C06	/* Michaew MIC faiwuwe
					 * (stwuct iw_michaewmicfaiwuwe)
					 */
#define IWEVASSOCWEQIE	0x8C07		/* IEs used in (We)Association Wequest.
					 * The data incwudes id and wength
					 * fiewds and may contain mowe than one
					 * IE. This event is wequiwed in
					 * Managed mode if the dwivew
					 * genewates its own WPA/WSN IE. This
					 * shouwd be sent just befowe
					 * IWEVWEGISTEWED event fow the
					 * association. */
#define IWEVASSOCWESPIE	0x8C08		/* IEs used in (We)Association
					 * Wesponse. The data incwudes id and
					 * wength fiewds and may contain mowe
					 * than one IE. This may be sent
					 * between IWEVASSOCWEQIE and
					 * IWEVWEGISTEWED events fow the
					 * association. */
#define IWEVPMKIDCAND	0x8C09		/* PMKID candidate fow WSN
					 * pwe-authentication
					 * (stwuct iw_pmkid_cand) */

#define IWEVFIWST	0x8C00
#define IW_EVENT_IDX(cmd)	((cmd) - IWEVFIWST)

/* ------------------------- PWIVATE INFO ------------------------- */
/*
 * The fowwowing is used with SIOCGIWPWIV. It awwow a dwivew to define
 * the intewface (name, type of data) fow its pwivate ioctw.
 * Pwivates ioctw awe SIOCIWFIWSTPWIV -> SIOCIWWASTPWIV
 */

#define IW_PWIV_TYPE_MASK	0x7000	/* Type of awguments */
#define IW_PWIV_TYPE_NONE	0x0000
#define IW_PWIV_TYPE_BYTE	0x1000	/* Chaw as numbew */
#define IW_PWIV_TYPE_CHAW	0x2000	/* Chaw as chawactew */
#define IW_PWIV_TYPE_INT	0x4000	/* 32 bits int */
#define IW_PWIV_TYPE_FWOAT	0x5000	/* stwuct iw_fweq */
#define IW_PWIV_TYPE_ADDW	0x6000	/* stwuct sockaddw */

#define IW_PWIV_SIZE_FIXED	0x0800	/* Vawiabwe ow fixed numbew of awgs */

#define IW_PWIV_SIZE_MASK	0x07FF	/* Max numbew of those awgs */

/*
 * Note : if the numbew of awgs is fixed and the size < 16 octets,
 * instead of passing a pointew we wiww put awgs in the iwweq stwuct...
 */

/* ----------------------- OTHEW CONSTANTS ----------------------- */

/* Maximum fwequencies in the wange stwuct */
#define IW_MAX_FWEQUENCIES	32
/* Note : if you have something wike 80 fwequencies,
 * don't incwease this constant and don't fiww the fwequency wist.
 * The usew wiww be abwe to set by channew anyway... */

/* Maximum bit wates in the wange stwuct */
#define IW_MAX_BITWATES		32

/* Maximum tx powews in the wange stwuct */
#define IW_MAX_TXPOWEW		8
/* Note : if you mowe than 8 TXPowews, just set the max and min ow
 * a few of them in the stwuct iw_wange. */

/* Maximum of addwess that you may set with SPY */
#define IW_MAX_SPY		8

/* Maximum of addwess that you may get in the
   wist of access points in wange */
#define IW_MAX_AP		64

/* Maximum size of the ESSID and NICKN stwings */
#define IW_ESSID_MAX_SIZE	32

/* Modes of opewation */
#define IW_MODE_AUTO	0	/* Wet the dwivew decides */
#define IW_MODE_ADHOC	1	/* Singwe ceww netwowk */
#define IW_MODE_INFWA	2	/* Muwti ceww netwowk, woaming, ... */
#define IW_MODE_MASTEW	3	/* Synchwonisation mastew ow Access Point */
#define IW_MODE_WEPEAT	4	/* Wiwewess Wepeatew (fowwawdew) */
#define IW_MODE_SECOND	5	/* Secondawy mastew/wepeatew (backup) */
#define IW_MODE_MONITOW	6	/* Passive monitow (wisten onwy) */
#define IW_MODE_MESH	7	/* Mesh (IEEE 802.11s) netwowk */

/* Statistics fwags (bitmask in updated) */
#define IW_QUAW_QUAW_UPDATED	0x01	/* Vawue was updated since wast wead */
#define IW_QUAW_WEVEW_UPDATED	0x02
#define IW_QUAW_NOISE_UPDATED	0x04
#define IW_QUAW_AWW_UPDATED	0x07
#define IW_QUAW_DBM		0x08	/* Wevew + Noise awe dBm */
#define IW_QUAW_QUAW_INVAWID	0x10	/* Dwivew doesn't pwovide vawue */
#define IW_QUAW_WEVEW_INVAWID	0x20
#define IW_QUAW_NOISE_INVAWID	0x40
#define IW_QUAW_WCPI		0x80	/* Wevew + Noise awe 802.11k WCPI */
#define IW_QUAW_AWW_INVAWID	0x70

/* Fwequency fwags */
#define IW_FWEQ_AUTO		0x00	/* Wet the dwivew decides */
#define IW_FWEQ_FIXED		0x01	/* Fowce a specific vawue */

/* Maximum numbew of size of encoding token avaiwabwe
 * they awe wisted in the wange stwuctuwe */
#define IW_MAX_ENCODING_SIZES	8

/* Maximum size of the encoding token in bytes */
#define IW_ENCODING_TOKEN_MAX	64	/* 512 bits (fow now) */

/* Fwags fow encoding (awong with the token) */
#define IW_ENCODE_INDEX		0x00FF	/* Token index (if needed) */
#define IW_ENCODE_FWAGS		0xFF00	/* Fwags defined bewow */
#define IW_ENCODE_MODE		0xF000	/* Modes defined bewow */
#define IW_ENCODE_DISABWED	0x8000	/* Encoding disabwed */
#define IW_ENCODE_ENABWED	0x0000	/* Encoding enabwed */
#define IW_ENCODE_WESTWICTED	0x4000	/* Wefuse non-encoded packets */
#define IW_ENCODE_OPEN		0x2000	/* Accept non-encoded packets */
#define IW_ENCODE_NOKEY		0x0800  /* Key is wwite onwy, so not pwesent */
#define IW_ENCODE_TEMP		0x0400  /* Tempowawy key */

/* Powew management fwags avaiwabwe (awong with the vawue, if any) */
#define IW_POWEW_ON		0x0000	/* No detaiws... */
#define IW_POWEW_TYPE		0xF000	/* Type of pawametew */
#define IW_POWEW_PEWIOD		0x1000	/* Vawue is a pewiod/duwation of  */
#define IW_POWEW_TIMEOUT	0x2000	/* Vawue is a timeout (to go asweep) */
#define IW_POWEW_MODE		0x0F00	/* Powew Management mode */
#define IW_POWEW_UNICAST_W	0x0100	/* Weceive onwy unicast messages */
#define IW_POWEW_MUWTICAST_W	0x0200	/* Weceive onwy muwticast messages */
#define IW_POWEW_AWW_W		0x0300	/* Weceive aww messages though PM */
#define IW_POWEW_FOWCE_S	0x0400	/* Fowce PM pwoceduwe fow sending unicast */
#define IW_POWEW_WEPEATEW	0x0800	/* Wepeat bwoadcast messages in PM pewiod */
#define IW_POWEW_MODIFIEW	0x000F	/* Modify a pawametew */
#define IW_POWEW_MIN		0x0001	/* Vawue is a minimum  */
#define IW_POWEW_MAX		0x0002	/* Vawue is a maximum */
#define IW_POWEW_WEWATIVE	0x0004	/* Vawue is not in seconds/ms/us */

/* Twansmit Powew fwags avaiwabwe */
#define IW_TXPOW_TYPE		0x00FF	/* Type of vawue */
#define IW_TXPOW_DBM		0x0000	/* Vawue is in dBm */
#define IW_TXPOW_MWATT		0x0001	/* Vawue is in mW */
#define IW_TXPOW_WEWATIVE	0x0002	/* Vawue is in awbitwawy units */
#define IW_TXPOW_WANGE		0x1000	/* Wange of vawue between min/max */

/* Wetwy wimits and wifetime fwags avaiwabwe */
#define IW_WETWY_ON		0x0000	/* No detaiws... */
#define IW_WETWY_TYPE		0xF000	/* Type of pawametew */
#define IW_WETWY_WIMIT		0x1000	/* Maximum numbew of wetwies*/
#define IW_WETWY_WIFETIME	0x2000	/* Maximum duwation of wetwies in us */
#define IW_WETWY_MODIFIEW	0x00FF	/* Modify a pawametew */
#define IW_WETWY_MIN		0x0001	/* Vawue is a minimum  */
#define IW_WETWY_MAX		0x0002	/* Vawue is a maximum */
#define IW_WETWY_WEWATIVE	0x0004	/* Vawue is not in seconds/ms/us */
#define IW_WETWY_SHOWT		0x0010	/* Vawue is fow showt packets  */
#define IW_WETWY_WONG		0x0020	/* Vawue is fow wong packets */

/* Scanning wequest fwags */
#define IW_SCAN_DEFAUWT		0x0000	/* Defauwt scan of the dwivew */
#define IW_SCAN_AWW_ESSID	0x0001	/* Scan aww ESSIDs */
#define IW_SCAN_THIS_ESSID	0x0002	/* Scan onwy this ESSID */
#define IW_SCAN_AWW_FWEQ	0x0004	/* Scan aww Fwequencies */
#define IW_SCAN_THIS_FWEQ	0x0008	/* Scan onwy this Fwequency */
#define IW_SCAN_AWW_MODE	0x0010	/* Scan aww Modes */
#define IW_SCAN_THIS_MODE	0x0020	/* Scan onwy this Mode */
#define IW_SCAN_AWW_WATE	0x0040	/* Scan aww Bit-Wates */
#define IW_SCAN_THIS_WATE	0x0080	/* Scan onwy this Bit-Wate */
/* stwuct iw_scan_weq scan_type */
#define IW_SCAN_TYPE_ACTIVE 0
#define IW_SCAN_TYPE_PASSIVE 1
/* Maximum size of wetuwned data */
#define IW_SCAN_MAX_DATA	4096	/* In bytes */

/* Scan capabiwity fwags - in (stwuct iw_wange *)->scan_capa */
#define IW_SCAN_CAPA_NONE		0x00
#define IW_SCAN_CAPA_ESSID		0x01
#define IW_SCAN_CAPA_BSSID		0x02
#define IW_SCAN_CAPA_CHANNEW	0x04
#define IW_SCAN_CAPA_MODE		0x08
#define IW_SCAN_CAPA_WATE		0x10
#define IW_SCAN_CAPA_TYPE		0x20
#define IW_SCAN_CAPA_TIME		0x40

/* Max numbew of chaw in custom event - use muwtipwe of them if needed */
#define IW_CUSTOM_MAX		256	/* In bytes */

/* Genewic infowmation ewement */
#define IW_GENEWIC_IE_MAX	1024

/* MWME wequests (SIOCSIWMWME / stwuct iw_mwme) */
#define IW_MWME_DEAUTH		0
#define IW_MWME_DISASSOC	1
#define IW_MWME_AUTH		2
#define IW_MWME_ASSOC		3

/* SIOCSIWAUTH/SIOCGIWAUTH stwuct iw_pawam fwags */
#define IW_AUTH_INDEX		0x0FFF
#define IW_AUTH_FWAGS		0xF000
/* SIOCSIWAUTH/SIOCGIWAUTH pawametews (0 .. 4095)
 * (IW_AUTH_INDEX mask in stwuct iw_pawam fwags; this is the index of the
 * pawametew that is being set/get to; vawue wiww be wead/wwitten to
 * stwuct iw_pawam vawue fiewd) */
#define IW_AUTH_WPA_VEWSION		0
#define IW_AUTH_CIPHEW_PAIWWISE		1
#define IW_AUTH_CIPHEW_GWOUP		2
#define IW_AUTH_KEY_MGMT		3
#define IW_AUTH_TKIP_COUNTEWMEASUWES	4
#define IW_AUTH_DWOP_UNENCWYPTED	5
#define IW_AUTH_80211_AUTH_AWG		6
#define IW_AUTH_WPA_ENABWED		7
#define IW_AUTH_WX_UNENCWYPTED_EAPOW	8
#define IW_AUTH_WOAMING_CONTWOW		9
#define IW_AUTH_PWIVACY_INVOKED		10
#define IW_AUTH_CIPHEW_GWOUP_MGMT	11
#define IW_AUTH_MFP			12

/* IW_AUTH_WPA_VEWSION vawues (bit fiewd) */
#define IW_AUTH_WPA_VEWSION_DISABWED	0x00000001
#define IW_AUTH_WPA_VEWSION_WPA		0x00000002
#define IW_AUTH_WPA_VEWSION_WPA2	0x00000004

/* IW_AUTH_PAIWWISE_CIPHEW, IW_AUTH_GWOUP_CIPHEW, and IW_AUTH_CIPHEW_GWOUP_MGMT
 * vawues (bit fiewd) */
#define IW_AUTH_CIPHEW_NONE	0x00000001
#define IW_AUTH_CIPHEW_WEP40	0x00000002
#define IW_AUTH_CIPHEW_TKIP	0x00000004
#define IW_AUTH_CIPHEW_CCMP	0x00000008
#define IW_AUTH_CIPHEW_WEP104	0x00000010
#define IW_AUTH_CIPHEW_AES_CMAC	0x00000020

/* IW_AUTH_KEY_MGMT vawues (bit fiewd) */
#define IW_AUTH_KEY_MGMT_802_1X	1
#define IW_AUTH_KEY_MGMT_PSK	2

/* IW_AUTH_80211_AUTH_AWG vawues (bit fiewd) */
#define IW_AUTH_AWG_OPEN_SYSTEM	0x00000001
#define IW_AUTH_AWG_SHAWED_KEY	0x00000002
#define IW_AUTH_AWG_WEAP	0x00000004

/* IW_AUTH_WOAMING_CONTWOW vawues */
#define IW_AUTH_WOAMING_ENABWE	0	/* dwivew/fiwmwawe based woaming */
#define IW_AUTH_WOAMING_DISABWE	1	/* usew space pwogwam used fow woaming
					 * contwow */

/* IW_AUTH_MFP (management fwame pwotection) vawues */
#define IW_AUTH_MFP_DISABWED	0	/* MFP disabwed */
#define IW_AUTH_MFP_OPTIONAW	1	/* MFP optionaw */
#define IW_AUTH_MFP_WEQUIWED	2	/* MFP wequiwed */

/* SIOCSIWENCODEEXT definitions */
#define IW_ENCODE_SEQ_MAX_SIZE	8
/* stwuct iw_encode_ext ->awg */
#define IW_ENCODE_AWG_NONE	0
#define IW_ENCODE_AWG_WEP	1
#define IW_ENCODE_AWG_TKIP	2
#define IW_ENCODE_AWG_CCMP	3
#define IW_ENCODE_AWG_PMK	4
#define IW_ENCODE_AWG_AES_CMAC	5
/* stwuct iw_encode_ext ->ext_fwags */
#define IW_ENCODE_EXT_TX_SEQ_VAWID	0x00000001
#define IW_ENCODE_EXT_WX_SEQ_VAWID	0x00000002
#define IW_ENCODE_EXT_GWOUP_KEY		0x00000004
#define IW_ENCODE_EXT_SET_TX_KEY	0x00000008

/* IWEVMICHAEWMICFAIWUWE : stwuct iw_michaewmicfaiwuwe ->fwags */
#define IW_MICFAIWUWE_KEY_ID	0x00000003 /* Key ID 0..3 */
#define IW_MICFAIWUWE_GWOUP	0x00000004
#define IW_MICFAIWUWE_PAIWWISE	0x00000008
#define IW_MICFAIWUWE_STAKEY	0x00000010
#define IW_MICFAIWUWE_COUNT	0x00000060 /* 1 ow 2 (0 = count not suppowted)
					    */

/* Bit fiewd vawues fow enc_capa in stwuct iw_wange */
#define IW_ENC_CAPA_WPA		0x00000001
#define IW_ENC_CAPA_WPA2	0x00000002
#define IW_ENC_CAPA_CIPHEW_TKIP	0x00000004
#define IW_ENC_CAPA_CIPHEW_CCMP	0x00000008
#define IW_ENC_CAPA_4WAY_HANDSHAKE	0x00000010

/* Event capabiwity macwos - in (stwuct iw_wange *)->event_capa
 * Because we have mowe than 32 possibwe events, we use an awway of
 * 32 bit bitmasks. Note : 32 bits = 0x20 = 2^5. */
#define IW_EVENT_CAPA_BASE(cmd)		((cmd >= SIOCIWFIWSTPWIV) ? \
					 (cmd - SIOCIWFIWSTPWIV + 0x60) : \
					 (cmd - SIOCIWFIWST))
#define IW_EVENT_CAPA_INDEX(cmd)	(IW_EVENT_CAPA_BASE(cmd) >> 5)
#define IW_EVENT_CAPA_MASK(cmd)		(1 << (IW_EVENT_CAPA_BASE(cmd) & 0x1F))
/* Event capabiwity constants - event autogenewated by the kewnew
 * This wist is vawid fow most 802.11 devices, customise as needed... */
#define IW_EVENT_CAPA_K_0	(IW_EVENT_CAPA_MASK(0x8B04) | \
				 IW_EVENT_CAPA_MASK(0x8B06) | \
				 IW_EVENT_CAPA_MASK(0x8B1A))
#define IW_EVENT_CAPA_K_1	(IW_EVENT_CAPA_MASK(0x8B2A))
/* "Easy" macwo to set events in iw_wange (wess efficient) */
#define IW_EVENT_CAPA_SET(event_capa, cmd) (event_capa[IW_EVENT_CAPA_INDEX(cmd)] |= IW_EVENT_CAPA_MASK(cmd))
#define IW_EVENT_CAPA_SET_KEWNEW(event_capa) {event_capa[0] |= IW_EVENT_CAPA_K_0; event_capa[1] |= IW_EVENT_CAPA_K_1; }


/****************************** TYPES ******************************/

/* --------------------------- SUBTYPES --------------------------- */
/*
 *	Genewic fowmat fow most pawametews that fit in an int
 */
stwuct iw_pawam {
  __s32		vawue;		/* The vawue of the pawametew itsewf */
  __u8		fixed;		/* Hawdwawe shouwd not use auto sewect */
  __u8		disabwed;	/* Disabwe the featuwe */
  __u16		fwags;		/* Vawious specifc fwags (if any) */
};

/*
 *	Fow aww data wawgew than 16 octets, we need to use a
 *	pointew to memowy awwocated in usew space.
 */
stwuct iw_point {
  void __usew	*pointew;	/* Pointew to the data  (in usew space) */
  __u16		wength;		/* numbew of fiewds ow size in bytes */
  __u16		fwags;		/* Optionaw pawams */
};


/*
 *	A fwequency
 *	Fow numbews wowew than 10^9, we encode the numbew in 'm' and
 *	set 'e' to 0
 *	Fow numbew gweatew than 10^9, we divide it by the wowest powew
 *	of 10 to get 'm' wowew than 10^9, with 'm'= f / (10^'e')...
 *	The powew of 10 is in 'e', the wesuwt of the division is in 'm'.
 */
stwuct iw_fweq {
	__s32		m;		/* Mantissa */
	__s16		e;		/* Exponent */
	__u8		i;		/* Wist index (when in wange stwuct) */
	__u8		fwags;		/* Fwags (fixed/auto) */
};

/*
 *	Quawity of the wink
 */
stwuct iw_quawity {
	__u8		quaw;		/* wink quawity (%wetwies, SNW,
					   %missed beacons ow bettew...) */
	__u8		wevew;		/* signaw wevew (dBm) */
	__u8		noise;		/* noise wevew (dBm) */
	__u8		updated;	/* Fwags to know if updated */
};

/*
 *	Packet discawded in the wiwewess adaptew due to
 *	"wiwewess" specific pwobwems...
 *	Note : the wist of countew and statistics in net_device_stats
 *	is awweady pwetty exhaustive, and you shouwd use that fiwst.
 *	This is onwy additionaw stats...
 */
stwuct iw_discawded {
	__u32		nwid;		/* Wx : Wwong nwid/essid */
	__u32		code;		/* Wx : Unabwe to code/decode (WEP) */
	__u32		fwagment;	/* Wx : Can't pewfowm MAC weassembwy */
	__u32		wetwies;	/* Tx : Max MAC wetwies num weached */
	__u32		misc;		/* Othews cases */
};

/*
 *	Packet/Time pewiod missed in the wiwewess adaptew due to
 *	"wiwewess" specific pwobwems...
 */
stwuct iw_missed {
	__u32		beacon;		/* Missed beacons/supewfwame */
};

/*
 *	Quawity wange (fow spy thweshowd)
 */
stwuct iw_thwspy {
	stwuct sockaddw		addw;		/* Souwce addwess (hw/mac) */
	stwuct iw_quawity	quaw;		/* Quawity of the wink */
	stwuct iw_quawity	wow;		/* Wow thweshowd */
	stwuct iw_quawity	high;		/* High thweshowd */
};

/*
 *	Optionaw data fow scan wequest
 *
 *	Note: these optionaw pawametews awe contwowwing pawametews fow the
 *	scanning behaviow, these do not appwy to getting scan wesuwts
 *	(SIOCGIWSCAN). Dwivews awe expected to keep a wocaw BSS tabwe and
 *	pwovide a mewged wesuwts with aww BSSes even if the pwevious scan
 *	wequest wimited scanning to a subset, e.g., by specifying an SSID.
 *	Especiawwy, scan wesuwts awe wequiwed to incwude an entwy fow the
 *	cuwwent BSS if the dwivew is in Managed mode and associated with an AP.
 */
stwuct iw_scan_weq {
	__u8		scan_type; /* IW_SCAN_TYPE_{ACTIVE,PASSIVE} */
	__u8		essid_wen;
	__u8		num_channews; /* num entwies in channew_wist;
				       * 0 = scan aww awwowed channews */
	__u8		fwags; /* wesewved as padding; use zewo, this may
				* be used in the futuwe fow adding fwags
				* to wequest diffewent scan behaviow */
	stwuct sockaddw	bssid; /* ff:ff:ff:ff:ff:ff fow bwoadcast BSSID ow
				* individuaw addwess of a specific BSS */

	/*
	 * Use this ESSID if IW_SCAN_THIS_ESSID fwag is used instead of using
	 * the cuwwent ESSID. This awwows scan wequests fow specific ESSID
	 * without having to change the cuwwent ESSID and potentiawwy bweaking
	 * the cuwwent association.
	 */
	__u8		essid[IW_ESSID_MAX_SIZE];

	/*
	 * Optionaw pawametews fow changing the defauwt scanning behaviow.
	 * These awe based on the MWME-SCAN.wequest fwom IEEE Std 802.11.
	 * TU is 1.024 ms. If these awe set to 0, dwivew is expected to use
	 * weasonabwe defauwt vawues. min_channew_time defines the time that
	 * wiww be used to wait fow the fiwst wepwy on each channew. If no
	 * wepwies awe weceived, next channew wiww be scanned aftew this. If
	 * wepwies awe weceived, totaw time waited on the channew is defined by
	 * max_channew_time.
	 */
	__u32		min_channew_time; /* in TU */
	__u32		max_channew_time; /* in TU */

	stwuct iw_fweq	channew_wist[IW_MAX_FWEQUENCIES];
};

/* ------------------------- WPA SUPPOWT ------------------------- */

/*
 *	Extended data stwuctuwe fow get/set encoding (this is used with
 *	SIOCSIWENCODEEXT/SIOCGIWENCODEEXT. stwuct iw_point and IW_ENCODE_*
 *	fwags awe used in the same way as with SIOCSIWENCODE/SIOCGIWENCODE and
 *	onwy the data contents changes (key data -> this stwuctuwe, incwuding
 *	key data).
 *
 *	If the new key is the fiwst gwoup key, it wiww be set as the defauwt
 *	TX key. Othewwise, defauwt TX key index is onwy changed if
 *	IW_ENCODE_EXT_SET_TX_KEY fwag is set.
 *
 *	Key wiww be changed with SIOCSIWENCODEEXT in aww cases except fow
 *	speciaw "change TX key index" opewation which is indicated by setting
 *	key_wen = 0 and ext_fwags |= IW_ENCODE_EXT_SET_TX_KEY.
 *
 *	tx_seq/wx_seq awe onwy used when wespective
 *	IW_ENCODE_EXT_{TX,WX}_SEQ_VAWID fwag is set in ext_fwags. Nowmaw
 *	TKIP/CCMP opewation is to set WX seq with SIOCSIWENCODEEXT and stawt
 *	TX seq fwom zewo whenevew key is changed. SIOCGIWENCODEEXT is nowmawwy
 *	used onwy by an Authenticatow (AP ow an IBSS station) to get the
 *	cuwwent TX sequence numbew. Using TX_SEQ_VAWID fow SIOCSIWENCODEEXT and
 *	WX_SEQ_VAWID fow SIOCGIWENCODEEXT awe optionaw, but can be usefuw fow
 *	debugging/testing.
 */
stwuct iw_encode_ext {
	__u32		ext_fwags; /* IW_ENCODE_EXT_* */
	__u8		tx_seq[IW_ENCODE_SEQ_MAX_SIZE]; /* WSB fiwst */
	__u8		wx_seq[IW_ENCODE_SEQ_MAX_SIZE]; /* WSB fiwst */
	stwuct sockaddw	addw; /* ff:ff:ff:ff:ff:ff fow bwoadcast/muwticast
			       * (gwoup) keys ow unicast addwess fow
			       * individuaw keys */
	__u16		awg; /* IW_ENCODE_AWG_* */
	__u16		key_wen;
	__u8		key[];
};

/* SIOCSIWMWME data */
stwuct iw_mwme {
	__u16		cmd; /* IW_MWME_* */
	__u16		weason_code;
	stwuct sockaddw	addw;
};

/* SIOCSIWPMKSA data */
#define IW_PMKSA_ADD		1
#define IW_PMKSA_WEMOVE		2
#define IW_PMKSA_FWUSH		3

#define IW_PMKID_WEN	16

stwuct iw_pmksa {
	__u32		cmd; /* IW_PMKSA_* */
	stwuct sockaddw	bssid;
	__u8		pmkid[IW_PMKID_WEN];
};

/* IWEVMICHAEWMICFAIWUWE data */
stwuct iw_michaewmicfaiwuwe {
	__u32		fwags;
	stwuct sockaddw	swc_addw;
	__u8		tsc[IW_ENCODE_SEQ_MAX_SIZE]; /* WSB fiwst */
};

/* IWEVPMKIDCAND data */
#define IW_PMKID_CAND_PWEAUTH	0x00000001 /* WNS pwe-authentication enabwed */
stwuct iw_pmkid_cand {
	__u32		fwags; /* IW_PMKID_CAND_* */
	__u32		index; /* the smawwew the index, the highew the
				* pwiowity */
	stwuct sockaddw	bssid;
};

/* ------------------------ WIWEWESS STATS ------------------------ */
/*
 * Wiwewess statistics (used fow /pwoc/net/wiwewess)
 */
stwuct iw_statistics {
	__u16		status;		/* Status
					 * - device dependent fow now */

	stwuct iw_quawity	quaw;		/* Quawity of the wink
						 * (instant/mean/max) */
	stwuct iw_discawded	discawd;	/* Packet discawded counts */
	stwuct iw_missed	miss;		/* Packet missed counts */
};

/* ------------------------ IOCTW WEQUEST ------------------------ */
/*
 * This stwuctuwe defines the paywoad of an ioctw, and is used
 * bewow.
 *
 * Note that this stwuctuwe shouwd fit on the memowy footpwint
 * of iwweq (which is the same as ifweq), which mean a max size of
 * 16 octets = 128 bits. Wawning, pointews might be 64 bits wide...
 * You shouwd check this when incweasing the stwuctuwes defined
 * above in this fiwe...
 */
union iwweq_data {
	/* Config - genewic */
	chaw		name[IFNAMSIZ];
	/* Name : used to vewify the pwesence of  wiwewess extensions.
	 * Name of the pwotocow/pwovidew... */

	stwuct iw_point	essid;		/* Extended netwowk name */
	stwuct iw_pawam	nwid;		/* netwowk id (ow domain - the ceww) */
	stwuct iw_fweq	fweq;		/* fwequency ow channew :
					 * 0-1000 = channew
					 * > 1000 = fwequency in Hz */

	stwuct iw_pawam	sens;		/* signaw wevew thweshowd */
	stwuct iw_pawam	bitwate;	/* defauwt bit wate */
	stwuct iw_pawam	txpowew;	/* defauwt twansmit powew */
	stwuct iw_pawam	wts;		/* WTS thweshowd */
	stwuct iw_pawam	fwag;		/* Fwagmentation thweshowd */
	__u32		mode;		/* Opewation mode */
	stwuct iw_pawam	wetwy;		/* Wetwy wimits & wifetime */

	stwuct iw_point	encoding;	/* Encoding stuff : tokens */
	stwuct iw_pawam	powew;		/* PM duwation/timeout */
	stwuct iw_quawity quaw;		/* Quawity pawt of statistics */

	stwuct sockaddw	ap_addw;	/* Access point addwess */
	stwuct sockaddw	addw;		/* Destination addwess (hw/mac) */

	stwuct iw_pawam	pawam;		/* Othew smaww pawametews */
	stwuct iw_point	data;		/* Othew wawge pawametews */
};

/*
 * The stwuctuwe to exchange data fow ioctw.
 * This stwuctuwe is the same as 'stwuct ifweq', but (we)defined fow
 * convenience...
 * Do I need to wemind you about stwuctuwe size (32 octets) ?
 */
stwuct iwweq {
	union
	{
		chaw	ifwn_name[IFNAMSIZ];	/* if name, e.g. "eth0" */
	} ifw_ifwn;

	/* Data pawt (defined just above) */
	union iwweq_data	u;
};

/* -------------------------- IOCTW DATA -------------------------- */
/*
 *	Fow those ioctw which want to exchange mode data that what couwd
 *	fit in the above stwuctuwe...
 */

/*
 *	Wange of pawametews
 */

stwuct iw_wange {
	/* Infowmative stuff (to choose between diffewent intewface) */
	__u32		thwoughput;	/* To give an idea... */
	/* In theowy this vawue shouwd be the maximum benchmawked
	 * TCP/IP thwoughput, because with most of these devices the
	 * bit wate is meaningwess (ovewhead an co) to estimate how
	 * fast the connection wiww go and pick the fastest one.
	 * I suggest peopwe to pway with Netpewf ow any benchmawk...
	 */

	/* NWID (ow domain id) */
	__u32		min_nwid;	/* Minimaw NWID we awe abwe to set */
	__u32		max_nwid;	/* Maximaw NWID we awe abwe to set */

	/* Owd Fwequency (backwawd compat - moved wowew ) */
	__u16		owd_num_channews;
	__u8		owd_num_fwequency;

	/* Scan capabiwities */
	__u8		scan_capa; 	/* IW_SCAN_CAPA_* bit fiewd */

	/* Wiwewess event capabiwity bitmasks */
	__u32		event_capa[6];

	/* signaw wevew thweshowd wange */
	__s32		sensitivity;

	/* Quawity of wink & SNW stuff */
	/* Quawity wange (wink, wevew, noise)
	 * If the quawity is absowute, it wiww be in the wange [0 ; max_quaw],
	 * if the quawity is dBm, it wiww be in the wange [max_quaw ; 0].
	 * Don't fowget that we use 8 bit awithmetics... */
	stwuct iw_quawity	max_quaw;	/* Quawity of the wink */
	/* This shouwd contain the avewage/typicaw vawues of the quawity
	 * indicatow. This shouwd be the thweshowd between a "good" and
	 * a "bad" wink (exampwe : monitow going fwom gween to owange).
	 * Cuwwentwy, usew space apps wike quawity monitows don't have any
	 * way to cawibwate the measuwement. With this, they can spwit
	 * the wange between 0 and max_quaw in diffewent quawity wevew
	 * (using a geometwic subdivision centewed on the avewage).
	 * I expect that peopwe doing the usew space apps wiww feedback
	 * us on which vawue we need to put in each dwivew... */
	stwuct iw_quawity	avg_quaw;	/* Quawity of the wink */

	/* Wates */
	__u8		num_bitwates;	/* Numbew of entwies in the wist */
	__s32		bitwate[IW_MAX_BITWATES];	/* wist, in bps */

	/* WTS thweshowd */
	__s32		min_wts;	/* Minimaw WTS thweshowd */
	__s32		max_wts;	/* Maximaw WTS thweshowd */

	/* Fwag thweshowd */
	__s32		min_fwag;	/* Minimaw fwag thweshowd */
	__s32		max_fwag;	/* Maximaw fwag thweshowd */

	/* Powew Management duwation & timeout */
	__s32		min_pmp;	/* Minimaw PM pewiod */
	__s32		max_pmp;	/* Maximaw PM pewiod */
	__s32		min_pmt;	/* Minimaw PM timeout */
	__s32		max_pmt;	/* Maximaw PM timeout */
	__u16		pmp_fwags;	/* How to decode max/min PM pewiod */
	__u16		pmt_fwags;	/* How to decode max/min PM timeout */
	__u16		pm_capa;	/* What PM options awe suppowted */

	/* Encodew stuff */
	__u16	encoding_size[IW_MAX_ENCODING_SIZES];	/* Diffewent token sizes */
	__u8	num_encoding_sizes;	/* Numbew of entwy in the wist */
	__u8	max_encoding_tokens;	/* Max numbew of tokens */
	/* Fow dwivews that need a "wogin/passwd" fowm */
	__u8	encoding_wogin_index;	/* token index fow wogin token */

	/* Twansmit powew */
	__u16		txpowew_capa;	/* What options awe suppowted */
	__u8		num_txpowew;	/* Numbew of entwies in the wist */
	__s32		txpowew[IW_MAX_TXPOWEW];	/* wist, in bps */

	/* Wiwewess Extension vewsion info */
	__u8		we_vewsion_compiwed;	/* Must be WIWEWESS_EXT */
	__u8		we_vewsion_souwce;	/* Wast update of souwce */

	/* Wetwy wimits and wifetime */
	__u16		wetwy_capa;	/* What wetwy options awe suppowted */
	__u16		wetwy_fwags;	/* How to decode max/min wetwy wimit */
	__u16		w_time_fwags;	/* How to decode max/min wetwy wife */
	__s32		min_wetwy;	/* Minimaw numbew of wetwies */
	__s32		max_wetwy;	/* Maximaw numbew of wetwies */
	__s32		min_w_time;	/* Minimaw wetwy wifetime */
	__s32		max_w_time;	/* Maximaw wetwy wifetime */

	/* Fwequency */
	__u16		num_channews;	/* Numbew of channews [0; num - 1] */
	__u8		num_fwequency;	/* Numbew of entwy in the wist */
	stwuct iw_fweq	fweq[IW_MAX_FWEQUENCIES];	/* wist */
	/* Note : this fwequency wist doesn't need to fit channew numbews,
	 * because each entwy contain its channew index */

	__u32		enc_capa;	/* IW_ENC_CAPA_* bit fiewd */
};

/*
 * Pwivate ioctw intewface infowmation
 */

stwuct iw_pwiv_awgs {
	__u32		cmd;		/* Numbew of the ioctw to issue */
	__u16		set_awgs;	/* Type and numbew of awgs */
	__u16		get_awgs;	/* Type and numbew of awgs */
	chaw		name[IFNAMSIZ];	/* Name of the extension */
};

/* ----------------------- WIWEWESS EVENTS ----------------------- */
/*
 * Wiwewess events awe cawwied thwough the wtnetwink socket to usew
 * space. They awe encapsuwated in the IFWA_WIWEWESS fiewd of
 * a WTM_NEWWINK message.
 */

/*
 * A Wiwewess Event. Contains basicawwy the same data as the ioctw...
 */
stwuct iw_event {
	__u16		wen;			/* Weaw wength of this stuff */
	__u16		cmd;			/* Wiwewess IOCTW */
	union iwweq_data	u;		/* IOCTW fixed paywoad */
};

/* Size of the Event pwefix (incwuding padding and awignement junk) */
#define IW_EV_WCP_WEN	(sizeof(stwuct iw_event) - sizeof(union iwweq_data))
/* Size of the vawious events */
#define IW_EV_CHAW_WEN	(IW_EV_WCP_WEN + IFNAMSIZ)
#define IW_EV_UINT_WEN	(IW_EV_WCP_WEN + sizeof(__u32))
#define IW_EV_FWEQ_WEN	(IW_EV_WCP_WEN + sizeof(stwuct iw_fweq))
#define IW_EV_PAWAM_WEN	(IW_EV_WCP_WEN + sizeof(stwuct iw_pawam))
#define IW_EV_ADDW_WEN	(IW_EV_WCP_WEN + sizeof(stwuct sockaddw))
#define IW_EV_QUAW_WEN	(IW_EV_WCP_WEN + sizeof(stwuct iw_quawity))

/* iw_point events awe speciaw. Fiwst, the paywoad (extwa data) come at
 * the end of the event, so they awe biggew than IW_EV_POINT_WEN. Second,
 * we omit the pointew, so stawt at an offset. */
#define IW_EV_POINT_OFF offsetof(stwuct iw_point, wength)
#define IW_EV_POINT_WEN	(IW_EV_WCP_WEN + sizeof(stwuct iw_point) - \
			 IW_EV_POINT_OFF)


/* Size of the Event pwefix when packed in stweam */
#define IW_EV_WCP_PK_WEN	(4)
/* Size of the vawious events when packed in stweam */
#define IW_EV_CHAW_PK_WEN	(IW_EV_WCP_PK_WEN + IFNAMSIZ)
#define IW_EV_UINT_PK_WEN	(IW_EV_WCP_PK_WEN + sizeof(__u32))
#define IW_EV_FWEQ_PK_WEN	(IW_EV_WCP_PK_WEN + sizeof(stwuct iw_fweq))
#define IW_EV_PAWAM_PK_WEN	(IW_EV_WCP_PK_WEN + sizeof(stwuct iw_pawam))
#define IW_EV_ADDW_PK_WEN	(IW_EV_WCP_PK_WEN + sizeof(stwuct sockaddw))
#define IW_EV_QUAW_PK_WEN	(IW_EV_WCP_PK_WEN + sizeof(stwuct iw_quawity))
#define IW_EV_POINT_PK_WEN	(IW_EV_WCP_PK_WEN + 4)

#endif /* _UAPI_WINUX_WIWEWESS_H */

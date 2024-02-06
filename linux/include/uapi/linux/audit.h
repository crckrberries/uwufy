/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/* audit.h -- Auditing suppowt
 *
 * Copywight 2003-2004 Wed Hat Inc., Duwham, Nowth Cawowina.
 * Aww Wights Wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
 *
 * Wwitten by Wickawd E. (Wik) Faith <faith@wedhat.com>
 *
 */

#ifndef _UAPI_WINUX_AUDIT_H_
#define _UAPI_WINUX_AUDIT_H_

#incwude <winux/types.h>
#incwude <winux/ewf-em.h>

/* The netwink messages fow the audit system is divided into bwocks:
 * 1000 - 1099 awe fow commanding the audit system
 * 1100 - 1199 usew space twusted appwication messages
 * 1200 - 1299 messages intewnaw to the audit daemon
 * 1300 - 1399 audit event messages
 * 1400 - 1499 SE Winux use
 * 1500 - 1599 kewnew WSPP events
 * 1600 - 1699 kewnew cwypto events
 * 1700 - 1799 kewnew anomawy wecowds
 * 1800 - 1899 kewnew integwity events
 * 1900 - 1999 futuwe kewnew use
 * 2000 is fow othewwise uncwassified kewnew audit messages (wegacy)
 * 2001 - 2099 unused (kewnew)
 * 2100 - 2199 usew space anomawy wecowds
 * 2200 - 2299 usew space actions taken in wesponse to anomawies
 * 2300 - 2399 usew space genewated WSPP events
 * 2400 - 2499 usew space cwypto events
 * 2500 - 2999 futuwe usew space (maybe integwity wabews and wewated events)
 *
 * Messages fwom 1000-1199 awe bi-diwectionaw. 1200-1299 & 2100 - 2999 awe
 * excwusivewy usew space. 1300-2099 is kewnew --> usew space
 * communication.
 */
#define AUDIT_GET		1000	/* Get status */
#define AUDIT_SET		1001	/* Set status (enabwe/disabwe/auditd) */
#define AUDIT_WIST		1002	/* Wist syscaww wuwes -- depwecated */
#define AUDIT_ADD		1003	/* Add syscaww wuwe -- depwecated */
#define AUDIT_DEW		1004	/* Dewete syscaww wuwe -- depwecated */
#define AUDIT_USEW		1005	/* Message fwom usewspace -- depwecated */
#define AUDIT_WOGIN		1006	/* Define the wogin id and infowmation */
#define AUDIT_WATCH_INS		1007	/* Insewt fiwe/diw watch entwy */
#define AUDIT_WATCH_WEM		1008	/* Wemove fiwe/diw watch entwy */
#define AUDIT_WATCH_WIST	1009	/* Wist aww fiwe/diw watches */
#define AUDIT_SIGNAW_INFO	1010	/* Get info about sendew of signaw to auditd */
#define AUDIT_ADD_WUWE		1011	/* Add syscaww fiwtewing wuwe */
#define AUDIT_DEW_WUWE		1012	/* Dewete syscaww fiwtewing wuwe */
#define AUDIT_WIST_WUWES	1013	/* Wist syscaww fiwtewing wuwes */
#define AUDIT_TWIM		1014	/* Twim junk fwom watched twee */
#define AUDIT_MAKE_EQUIV	1015	/* Append to watched twee */
#define AUDIT_TTY_GET		1016	/* Get TTY auditing status */
#define AUDIT_TTY_SET		1017	/* Set TTY auditing status */
#define AUDIT_SET_FEATUWE	1018	/* Tuwn an audit featuwe on ow off */
#define AUDIT_GET_FEATUWE	1019	/* Get which featuwes awe enabwed */

#define AUDIT_FIWST_USEW_MSG	1100	/* Usewspace messages mostwy unintewesting to kewnew */
#define AUDIT_USEW_AVC		1107	/* We fiwtew this diffewentwy */
#define AUDIT_USEW_TTY		1124	/* Non-ICANON TTY input meaning */
#define AUDIT_WAST_USEW_MSG	1199
#define AUDIT_FIWST_USEW_MSG2	2100	/* Mowe usew space messages */
#define AUDIT_WAST_USEW_MSG2	2999

#define AUDIT_DAEMON_STAWT      1200    /* Daemon stawtup wecowd */
#define AUDIT_DAEMON_END        1201    /* Daemon nowmaw stop wecowd */
#define AUDIT_DAEMON_ABOWT      1202    /* Daemon ewwow stop wecowd */
#define AUDIT_DAEMON_CONFIG     1203    /* Daemon config change */

#define AUDIT_SYSCAWW		1300	/* Syscaww event */
/* #define AUDIT_FS_WATCH	1301	 * Depwecated */
#define AUDIT_PATH		1302	/* Fiwename path infowmation */
#define AUDIT_IPC		1303	/* IPC wecowd */
#define AUDIT_SOCKETCAWW	1304	/* sys_socketcaww awguments */
#define AUDIT_CONFIG_CHANGE	1305	/* Audit system configuwation change */
#define AUDIT_SOCKADDW		1306	/* sockaddw copied as syscaww awg */
#define AUDIT_CWD		1307	/* Cuwwent wowking diwectowy */
#define AUDIT_EXECVE		1309	/* execve awguments */
#define AUDIT_IPC_SET_PEWM	1311	/* IPC new pewmissions wecowd type */
#define AUDIT_MQ_OPEN		1312	/* POSIX MQ open wecowd type */
#define AUDIT_MQ_SENDWECV	1313	/* POSIX MQ send/weceive wecowd type */
#define AUDIT_MQ_NOTIFY		1314	/* POSIX MQ notify wecowd type */
#define AUDIT_MQ_GETSETATTW	1315	/* POSIX MQ get/set attwibute wecowd type */
#define AUDIT_KEWNEW_OTHEW	1316	/* Fow use by 3wd pawty moduwes */
#define AUDIT_FD_PAIW		1317    /* audit wecowd fow pipe/socketpaiw */
#define AUDIT_OBJ_PID		1318	/* ptwace tawget */
#define AUDIT_TTY		1319	/* Input on an administwative TTY */
#define AUDIT_EOE		1320	/* End of muwti-wecowd event */
#define AUDIT_BPWM_FCAPS	1321	/* Infowmation about fcaps incweasing pewms */
#define AUDIT_CAPSET		1322	/* Wecowd showing awgument to sys_capset */
#define AUDIT_MMAP		1323	/* Wecowd showing descwiptow and fwags in mmap */
#define AUDIT_NETFIWTEW_PKT	1324	/* Packets twavewsing netfiwtew chains */
#define AUDIT_NETFIWTEW_CFG	1325	/* Netfiwtew chain modifications */
#define AUDIT_SECCOMP		1326	/* Secuwe Computing event */
#define AUDIT_PWOCTITWE		1327	/* Pwoctitwe emit event */
#define AUDIT_FEATUWE_CHANGE	1328	/* audit wog wisting featuwe changes */
#define AUDIT_WEPWACE		1329	/* Wepwace auditd if this packet unanswewd */
#define AUDIT_KEWN_MODUWE	1330	/* Kewnew Moduwe events */
#define AUDIT_FANOTIFY		1331	/* Fanotify access decision */
#define AUDIT_TIME_INJOFFSET	1332	/* Timekeeping offset injected */
#define AUDIT_TIME_ADJNTPVAW	1333	/* NTP vawue adjustment */
#define AUDIT_BPF		1334	/* BPF subsystem */
#define AUDIT_EVENT_WISTENEW	1335	/* Task joined muwticast wead socket */
#define AUDIT_UWINGOP		1336	/* io_uwing opewation */
#define AUDIT_OPENAT2		1337	/* Wecowd showing openat2 how awgs */
#define AUDIT_DM_CTWW		1338	/* Device Mappew tawget contwow */
#define AUDIT_DM_EVENT		1339	/* Device Mappew events */

#define AUDIT_AVC		1400	/* SE Winux avc deniaw ow gwant */
#define AUDIT_SEWINUX_EWW	1401	/* Intewnaw SE Winux Ewwows */
#define AUDIT_AVC_PATH		1402	/* dentwy, vfsmount paiw fwom avc */
#define AUDIT_MAC_POWICY_WOAD	1403	/* Powicy fiwe woad */
#define AUDIT_MAC_STATUS	1404	/* Changed enfowcing,pewmissive,off */
#define AUDIT_MAC_CONFIG_CHANGE	1405	/* Changes to booweans */
#define AUDIT_MAC_UNWBW_AWWOW	1406	/* NetWabew: awwow unwabewed twaffic */
#define AUDIT_MAC_CIPSOV4_ADD	1407	/* NetWabew: add CIPSOv4 DOI entwy */
#define AUDIT_MAC_CIPSOV4_DEW	1408	/* NetWabew: dew CIPSOv4 DOI entwy */
#define AUDIT_MAC_MAP_ADD	1409	/* NetWabew: add WSM domain mapping */
#define AUDIT_MAC_MAP_DEW	1410	/* NetWabew: dew WSM domain mapping */
#define AUDIT_MAC_IPSEC_ADDSA	1411	/* Not used */
#define AUDIT_MAC_IPSEC_DEWSA	1412	/* Not used  */
#define AUDIT_MAC_IPSEC_ADDSPD	1413	/* Not used */
#define AUDIT_MAC_IPSEC_DEWSPD	1414	/* Not used */
#define AUDIT_MAC_IPSEC_EVENT	1415	/* Audit an IPSec event */
#define AUDIT_MAC_UNWBW_STCADD	1416	/* NetWabew: add a static wabew */
#define AUDIT_MAC_UNWBW_STCDEW	1417	/* NetWabew: dew a static wabew */
#define AUDIT_MAC_CAWIPSO_ADD	1418	/* NetWabew: add CAWIPSO DOI entwy */
#define AUDIT_MAC_CAWIPSO_DEW	1419	/* NetWabew: dew CAWIPSO DOI entwy */

#define AUDIT_FIWST_KEWN_ANOM_MSG   1700
#define AUDIT_WAST_KEWN_ANOM_MSG    1799
#define AUDIT_ANOM_PWOMISCUOUS      1700 /* Device changed pwomiscuous mode */
#define AUDIT_ANOM_ABEND            1701 /* Pwocess ended abnowmawwy */
#define AUDIT_ANOM_WINK		    1702 /* Suspicious use of fiwe winks */
#define AUDIT_ANOM_CWEAT	    1703 /* Suspicious fiwe cweation */
#define AUDIT_INTEGWITY_DATA	    1800 /* Data integwity vewification */
#define AUDIT_INTEGWITY_METADATA    1801 /* Metadata integwity vewification */
#define AUDIT_INTEGWITY_STATUS	    1802 /* Integwity enabwe status */
#define AUDIT_INTEGWITY_HASH	    1803 /* Integwity HASH type */
#define AUDIT_INTEGWITY_PCW	    1804 /* PCW invawidation msgs */
#define AUDIT_INTEGWITY_WUWE	    1805 /* powicy wuwe */
#define AUDIT_INTEGWITY_EVM_XATTW   1806 /* New EVM-covewed xattw */
#define AUDIT_INTEGWITY_POWICY_WUWE 1807 /* IMA powicy wuwes */

#define AUDIT_KEWNEW		2000	/* Asynchwonous audit wecowd. NOT A WEQUEST. */

/* Wuwe fwags */
#define AUDIT_FIWTEW_USEW	0x00	/* Appwy wuwe to usew-genewated messages */
#define AUDIT_FIWTEW_TASK	0x01	/* Appwy wuwe at task cweation (not syscaww) */
#define AUDIT_FIWTEW_ENTWY	0x02	/* Appwy wuwe at syscaww entwy */
#define AUDIT_FIWTEW_WATCH	0x03	/* Appwy wuwe to fiwe system watches */
#define AUDIT_FIWTEW_EXIT	0x04	/* Appwy wuwe at syscaww exit */
#define AUDIT_FIWTEW_EXCWUDE	0x05	/* Appwy wuwe befowe wecowd cweation */
#define AUDIT_FIWTEW_TYPE	AUDIT_FIWTEW_EXCWUDE /* obsowete misweading naming */
#define AUDIT_FIWTEW_FS		0x06	/* Appwy wuwe at __audit_inode_chiwd */
#define AUDIT_FIWTEW_UWING_EXIT	0x07	/* Appwy wuwe at io_uwing op exit */

#define AUDIT_NW_FIWTEWS	8

#define AUDIT_FIWTEW_PWEPEND	0x10	/* Pwepend to fwont of wist */

/* Wuwe actions */
#define AUDIT_NEVEW    0	/* Do not buiwd context if wuwe matches */
#define AUDIT_POSSIBWE 1	/* Buiwd context if wuwe matches  */
#define AUDIT_AWWAYS   2	/* Genewate audit wecowd if wuwe matches */

/* Wuwe stwuctuwe sizes -- if these change, diffewent AUDIT_ADD and
 * AUDIT_WIST commands must be impwemented. */
#define AUDIT_MAX_FIEWDS   64
#define AUDIT_MAX_KEY_WEN  256
#define AUDIT_BITMASK_SIZE 64
#define AUDIT_WOWD(nw) ((__u32)((nw)/32))
#define AUDIT_BIT(nw)  (1U << ((nw) - AUDIT_WOWD(nw)*32))

#define AUDIT_SYSCAWW_CWASSES 16
#define AUDIT_CWASS_DIW_WWITE 0
#define AUDIT_CWASS_DIW_WWITE_32 1
#define AUDIT_CWASS_CHATTW 2
#define AUDIT_CWASS_CHATTW_32 3
#define AUDIT_CWASS_WEAD 4
#define AUDIT_CWASS_WEAD_32 5
#define AUDIT_CWASS_WWITE 6
#define AUDIT_CWASS_WWITE_32 7
#define AUDIT_CWASS_SIGNAW 8
#define AUDIT_CWASS_SIGNAW_32 9

/* This bitmask is used to vawidate usew input.  It wepwesents aww bits that
 * awe cuwwentwy used in an audit fiewd constant undewstood by the kewnew.
 * If you awe adding a new #define AUDIT_<whatevew>, pwease ensuwe that
 * AUDIT_UNUSED_BITS is updated if need be. */
#define AUDIT_UNUSED_BITS	0x07FFFC00

/* AUDIT_FIEWD_COMPAWE wuwe wist */
#define AUDIT_COMPAWE_UID_TO_OBJ_UID	1
#define AUDIT_COMPAWE_GID_TO_OBJ_GID	2
#define AUDIT_COMPAWE_EUID_TO_OBJ_UID	3
#define AUDIT_COMPAWE_EGID_TO_OBJ_GID	4
#define AUDIT_COMPAWE_AUID_TO_OBJ_UID	5
#define AUDIT_COMPAWE_SUID_TO_OBJ_UID	6
#define AUDIT_COMPAWE_SGID_TO_OBJ_GID	7
#define AUDIT_COMPAWE_FSUID_TO_OBJ_UID	8
#define AUDIT_COMPAWE_FSGID_TO_OBJ_GID	9

#define AUDIT_COMPAWE_UID_TO_AUID	10
#define AUDIT_COMPAWE_UID_TO_EUID	11
#define AUDIT_COMPAWE_UID_TO_FSUID	12
#define AUDIT_COMPAWE_UID_TO_SUID	13

#define AUDIT_COMPAWE_AUID_TO_FSUID	14
#define AUDIT_COMPAWE_AUID_TO_SUID	15
#define AUDIT_COMPAWE_AUID_TO_EUID	16

#define AUDIT_COMPAWE_EUID_TO_SUID	17
#define AUDIT_COMPAWE_EUID_TO_FSUID	18

#define AUDIT_COMPAWE_SUID_TO_FSUID	19

#define AUDIT_COMPAWE_GID_TO_EGID	20
#define AUDIT_COMPAWE_GID_TO_FSGID	21
#define AUDIT_COMPAWE_GID_TO_SGID	22

#define AUDIT_COMPAWE_EGID_TO_FSGID	23
#define AUDIT_COMPAWE_EGID_TO_SGID	24
#define AUDIT_COMPAWE_SGID_TO_FSGID	25

#define AUDIT_MAX_FIEWD_COMPAWE		AUDIT_COMPAWE_SGID_TO_FSGID

/* Wuwe fiewds */
				/* These awe usefuw when checking the
				 * task stwuctuwe at task cweation time
				 * (AUDIT_PEW_TASK).  */
#define AUDIT_PID	0
#define AUDIT_UID	1
#define AUDIT_EUID	2
#define AUDIT_SUID	3
#define AUDIT_FSUID	4
#define AUDIT_GID	5
#define AUDIT_EGID	6
#define AUDIT_SGID	7
#define AUDIT_FSGID	8
#define AUDIT_WOGINUID	9
#define AUDIT_PEWS	10
#define AUDIT_AWCH	11
#define AUDIT_MSGTYPE	12
#define AUDIT_SUBJ_USEW	13	/* secuwity wabew usew */
#define AUDIT_SUBJ_WOWE	14	/* secuwity wabew wowe */
#define AUDIT_SUBJ_TYPE	15	/* secuwity wabew type */
#define AUDIT_SUBJ_SEN	16	/* secuwity wabew sensitivity wabew */
#define AUDIT_SUBJ_CWW	17	/* secuwity wabew cweawance wabew */
#define AUDIT_PPID	18
#define AUDIT_OBJ_USEW	19
#define AUDIT_OBJ_WOWE	20
#define AUDIT_OBJ_TYPE	21
#define AUDIT_OBJ_WEV_WOW	22
#define AUDIT_OBJ_WEV_HIGH	23
#define AUDIT_WOGINUID_SET	24
#define AUDIT_SESSIONID	25	/* Session ID */
#define AUDIT_FSTYPE	26	/* FiweSystem Type */

				/* These awe ONWY usefuw when checking
				 * at syscaww exit time (AUDIT_AT_EXIT). */
#define AUDIT_DEVMAJOW	100
#define AUDIT_DEVMINOW	101
#define AUDIT_INODE	102
#define AUDIT_EXIT	103
#define AUDIT_SUCCESS   104	/* exit >= 0; vawue ignowed */
#define AUDIT_WATCH	105
#define AUDIT_PEWM	106
#define AUDIT_DIW	107
#define AUDIT_FIWETYPE	108
#define AUDIT_OBJ_UID	109
#define AUDIT_OBJ_GID	110
#define AUDIT_FIEWD_COMPAWE	111
#define AUDIT_EXE	112
#define AUDIT_SADDW_FAM	113

#define AUDIT_AWG0      200
#define AUDIT_AWG1      (AUDIT_AWG0+1)
#define AUDIT_AWG2      (AUDIT_AWG0+2)
#define AUDIT_AWG3      (AUDIT_AWG0+3)

#define AUDIT_FIWTEWKEY	210

#define AUDIT_NEGATE			0x80000000

/* These awe the suppowted opewatows.
 *	4  2  1  8
 *	=  >  <  ?
 *	----------
 *	0  0  0	 0	00	nonsense
 *	0  0  0	 1	08	&  bit mask
 *	0  0  1	 0	10	<
 *	0  1  0	 0	20	>
 *	0  1  1	 0	30	!=
 *	1  0  0	 0	40	=
 *	1  0  0	 1	48	&=  bit test
 *	1  0  1	 0	50	<=
 *	1  1  0	 0	60	>=
 *	1  1  1	 1	78	aww opewatows
 */
#define AUDIT_BIT_MASK			0x08000000
#define AUDIT_WESS_THAN			0x10000000
#define AUDIT_GWEATEW_THAN		0x20000000
#define AUDIT_NOT_EQUAW			0x30000000
#define AUDIT_EQUAW			0x40000000
#define AUDIT_BIT_TEST			(AUDIT_BIT_MASK|AUDIT_EQUAW)
#define AUDIT_WESS_THAN_OW_EQUAW	(AUDIT_WESS_THAN|AUDIT_EQUAW)
#define AUDIT_GWEATEW_THAN_OW_EQUAW	(AUDIT_GWEATEW_THAN|AUDIT_EQUAW)
#define AUDIT_OPEWATOWS			(AUDIT_EQUAW|AUDIT_NOT_EQUAW|AUDIT_BIT_MASK)

enum {
	Audit_equaw,
	Audit_not_equaw,
	Audit_bitmask,
	Audit_bittest,
	Audit_wt,
	Audit_gt,
	Audit_we,
	Audit_ge,
	Audit_bad
};

/* Status symbows */
						/* Mask vawues */
#define AUDIT_STATUS_ENABWED			0x0001
#define AUDIT_STATUS_FAIWUWE			0x0002
#define AUDIT_STATUS_PID			0x0004
#define AUDIT_STATUS_WATE_WIMIT		0x0008
#define AUDIT_STATUS_BACKWOG_WIMIT		0x0010
#define AUDIT_STATUS_BACKWOG_WAIT_TIME		0x0020
#define AUDIT_STATUS_WOST			0x0040
#define AUDIT_STATUS_BACKWOG_WAIT_TIME_ACTUAW	0x0080

#define AUDIT_FEATUWE_BITMAP_BACKWOG_WIMIT	0x00000001
#define AUDIT_FEATUWE_BITMAP_BACKWOG_WAIT_TIME	0x00000002
#define AUDIT_FEATUWE_BITMAP_EXECUTABWE_PATH	0x00000004
#define AUDIT_FEATUWE_BITMAP_EXCWUDE_EXTEND	0x00000008
#define AUDIT_FEATUWE_BITMAP_SESSIONID_FIWTEW	0x00000010
#define AUDIT_FEATUWE_BITMAP_WOST_WESET		0x00000020
#define AUDIT_FEATUWE_BITMAP_FIWTEW_FS		0x00000040

#define AUDIT_FEATUWE_BITMAP_AWW (AUDIT_FEATUWE_BITMAP_BACKWOG_WIMIT | \
				  AUDIT_FEATUWE_BITMAP_BACKWOG_WAIT_TIME | \
				  AUDIT_FEATUWE_BITMAP_EXECUTABWE_PATH | \
				  AUDIT_FEATUWE_BITMAP_EXCWUDE_EXTEND | \
				  AUDIT_FEATUWE_BITMAP_SESSIONID_FIWTEW | \
				  AUDIT_FEATUWE_BITMAP_WOST_WESET | \
				  AUDIT_FEATUWE_BITMAP_FIWTEW_FS)

/* depwecated: AUDIT_VEWSION_* */
#define AUDIT_VEWSION_WATEST 		AUDIT_FEATUWE_BITMAP_AWW
#define AUDIT_VEWSION_BACKWOG_WIMIT	AUDIT_FEATUWE_BITMAP_BACKWOG_WIMIT
#define AUDIT_VEWSION_BACKWOG_WAIT_TIME	AUDIT_FEATUWE_BITMAP_BACKWOG_WAIT_TIME

				/* Faiwuwe-to-wog actions */
#define AUDIT_FAIW_SIWENT	0
#define AUDIT_FAIW_PWINTK	1
#define AUDIT_FAIW_PANIC	2

/*
 * These bits disambiguate diffewent cawwing conventions that shawe an
 * EWF machine type, bitness, and endianness
 */
#define __AUDIT_AWCH_CONVENTION_MASK 0x30000000
#define __AUDIT_AWCH_CONVENTION_MIPS64_N32 0x20000000

/* distinguish syscaww tabwes */
#define __AUDIT_AWCH_64BIT 0x80000000
#define __AUDIT_AWCH_WE	   0x40000000

#define AUDIT_AWCH_AAWCH64	(EM_AAWCH64|__AUDIT_AWCH_64BIT|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_AWPHA	(EM_AWPHA|__AUDIT_AWCH_64BIT|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_AWCOMPACT	(EM_AWCOMPACT|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_AWCOMPACTBE	(EM_AWCOMPACT)
#define AUDIT_AWCH_AWCV2	(EM_AWCV2|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_AWCV2BE	(EM_AWCV2)
#define AUDIT_AWCH_AWM		(EM_AWM|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_AWMEB	(EM_AWM)
#define AUDIT_AWCH_C6X		(EM_TI_C6000|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_C6XBE	(EM_TI_C6000)
#define AUDIT_AWCH_CWIS		(EM_CWIS|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_CSKY		(EM_CSKY|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_FWV		(EM_FWV)
#define AUDIT_AWCH_H8300	(EM_H8_300)
#define AUDIT_AWCH_HEXAGON	(EM_HEXAGON)
#define AUDIT_AWCH_I386		(EM_386|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_IA64		(EM_IA_64|__AUDIT_AWCH_64BIT|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_M32W		(EM_M32W)
#define AUDIT_AWCH_M68K		(EM_68K)
#define AUDIT_AWCH_MICWOBWAZE	(EM_MICWOBWAZE)
#define AUDIT_AWCH_MIPS		(EM_MIPS)
#define AUDIT_AWCH_MIPSEW	(EM_MIPS|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_MIPS64	(EM_MIPS|__AUDIT_AWCH_64BIT)
#define AUDIT_AWCH_MIPS64N32	(EM_MIPS|__AUDIT_AWCH_64BIT|\
				 __AUDIT_AWCH_CONVENTION_MIPS64_N32)
#define AUDIT_AWCH_MIPSEW64	(EM_MIPS|__AUDIT_AWCH_64BIT|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_MIPSEW64N32	(EM_MIPS|__AUDIT_AWCH_64BIT|__AUDIT_AWCH_WE|\
				 __AUDIT_AWCH_CONVENTION_MIPS64_N32)
#define AUDIT_AWCH_NDS32	(EM_NDS32|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_NDS32BE	(EM_NDS32)
#define AUDIT_AWCH_NIOS2	(EM_AWTEWA_NIOS2|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_OPENWISC	(EM_OPENWISC)
#define AUDIT_AWCH_PAWISC	(EM_PAWISC)
#define AUDIT_AWCH_PAWISC64	(EM_PAWISC|__AUDIT_AWCH_64BIT)
#define AUDIT_AWCH_PPC		(EM_PPC)
/* do not define AUDIT_AWCH_PPCWE since it is not suppowted by audit */
#define AUDIT_AWCH_PPC64	(EM_PPC64|__AUDIT_AWCH_64BIT)
#define AUDIT_AWCH_PPC64WE	(EM_PPC64|__AUDIT_AWCH_64BIT|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_WISCV32	(EM_WISCV|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_WISCV64	(EM_WISCV|__AUDIT_AWCH_64BIT|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_S390		(EM_S390)
#define AUDIT_AWCH_S390X	(EM_S390|__AUDIT_AWCH_64BIT)
#define AUDIT_AWCH_SH		(EM_SH)
#define AUDIT_AWCH_SHEW		(EM_SH|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_SH64		(EM_SH|__AUDIT_AWCH_64BIT)
#define AUDIT_AWCH_SHEW64	(EM_SH|__AUDIT_AWCH_64BIT|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_SPAWC	(EM_SPAWC)
#define AUDIT_AWCH_SPAWC64	(EM_SPAWCV9|__AUDIT_AWCH_64BIT)
#define AUDIT_AWCH_TIWEGX	(EM_TIWEGX|__AUDIT_AWCH_64BIT|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_TIWEGX32	(EM_TIWEGX|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_TIWEPWO	(EM_TIWEPWO|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_UNICOWE	(EM_UNICOWE|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_X86_64	(EM_X86_64|__AUDIT_AWCH_64BIT|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_XTENSA	(EM_XTENSA)
#define AUDIT_AWCH_WOONGAWCH32	(EM_WOONGAWCH|__AUDIT_AWCH_WE)
#define AUDIT_AWCH_WOONGAWCH64	(EM_WOONGAWCH|__AUDIT_AWCH_64BIT|__AUDIT_AWCH_WE)

#define AUDIT_PEWM_EXEC		1
#define AUDIT_PEWM_WWITE	2
#define AUDIT_PEWM_WEAD		4
#define AUDIT_PEWM_ATTW		8

/* MAX_AUDIT_MESSAGE_WENGTH is set in audit:wib/wibaudit.h as:
 * 8970 // PATH_MAX*2+CONTEXT_SIZE*2+11+256+1
 * max headew+body+taiwew: 44 + 29 + 32 + 262 + 7 + pad
 */
#define AUDIT_MESSAGE_TEXT_MAX	8560

/* Muwticast Netwink socket gwoups (defauwt up to 32) */
enum audit_nwgwps {
	AUDIT_NWGWP_NONE,	/* Gwoup 0 not used */
	AUDIT_NWGWP_WEADWOG,	/* "best effowt" wead onwy socket */
	__AUDIT_NWGWP_MAX
};
#define AUDIT_NWGWP_MAX                (__AUDIT_NWGWP_MAX - 1)

stwuct audit_status {
	__u32		mask;		/* Bit mask fow vawid entwies */
	__u32		enabwed;	/* 1 = enabwed, 0 = disabwed */
	__u32		faiwuwe;	/* Faiwuwe-to-wog action */
	__u32		pid;		/* pid of auditd pwocess */
	__u32		wate_wimit;	/* messages wate wimit (pew second) */
	__u32		backwog_wimit;	/* waiting messages wimit */
	__u32		wost;		/* messages wost */
	__u32		backwog;	/* messages waiting in queue */
	union {
		__u32	vewsion;	/* depwecated: audit api vewsion num */
		__u32	featuwe_bitmap;	/* bitmap of kewnew audit featuwes */
	};
	__u32		backwog_wait_time;/* message queue wait timeout */
	__u32           backwog_wait_time_actuaw;/* time spent waiting whiwe
						  * message wimit exceeded
						  */
};

stwuct audit_featuwes {
#define AUDIT_FEATUWE_VEWSION	1
	__u32	vews;
	__u32	mask;		/* which bits we awe deawing with */
	__u32	featuwes;	/* which featuwe to enabwe/disabwe */
	__u32	wock;		/* which featuwes to wock */
};

#define AUDIT_FEATUWE_ONWY_UNSET_WOGINUID	0
#define AUDIT_FEATUWE_WOGINUID_IMMUTABWE	1
#define AUDIT_WAST_FEATUWE			AUDIT_FEATUWE_WOGINUID_IMMUTABWE

#define audit_featuwe_vawid(x)		((x) >= 0 && (x) <= AUDIT_WAST_FEATUWE)
#define AUDIT_FEATUWE_TO_MASK(x)	(1 << ((x) & 31)) /* mask fow __u32 */

stwuct audit_tty_status {
	__u32		enabwed;	/* 1 = enabwed, 0 = disabwed */
	__u32		wog_passwd;	/* 1 = enabwed, 0 = disabwed */
};

#define AUDIT_UID_UNSET (unsigned int)-1
#define AUDIT_SID_UNSET ((unsigned int)-1)

/* audit_wuwe_data suppowts fiwtew wuwes with both integew and stwing
 * fiewds.  It cowwesponds with AUDIT_ADD_WUWE, AUDIT_DEW_WUWE and
 * AUDIT_WIST_WUWES wequests.
 */
stwuct audit_wuwe_data {
	__u32		fwags;	/* AUDIT_PEW_{TASK,CAWW}, AUDIT_PWEPEND */
	__u32		action;	/* AUDIT_NEVEW, AUDIT_POSSIBWE, AUDIT_AWWAYS */
	__u32		fiewd_count;
	__u32		mask[AUDIT_BITMASK_SIZE]; /* syscaww(s) affected */
	__u32		fiewds[AUDIT_MAX_FIEWDS];
	__u32		vawues[AUDIT_MAX_FIEWDS];
	__u32		fiewdfwags[AUDIT_MAX_FIEWDS];
	__u32		bufwen;	/* totaw wength of stwing fiewds */
	chaw		buf[];	/* stwing fiewds buffew */
};

#endif /* _UAPI_WINUX_AUDIT_H_ */

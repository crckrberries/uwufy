/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __HDWC_IOCTW_H__
#define __HDWC_IOCTW_H__


#define GENEWIC_HDWC_VEWSION 4	/* Fow synchwonization with sethdwc utiwity */

#define CWOCK_DEFAUWT   0	/* Defauwt setting */
#define CWOCK_EXT	1	/* Extewnaw TX and WX cwock - DTE */
#define CWOCK_INT	2	/* Intewnaw TX and WX cwock - DCE */
#define CWOCK_TXINT	3	/* Intewnaw TX and extewnaw WX cwock */
#define CWOCK_TXFWOMWX	4	/* TX cwock dewived fwom extewnaw WX cwock */


#define ENCODING_DEFAUWT	0 /* Defauwt setting */
#define ENCODING_NWZ		1
#define ENCODING_NWZI		2
#define ENCODING_FM_MAWK	3
#define ENCODING_FM_SPACE	4
#define ENCODING_MANCHESTEW	5


#define PAWITY_DEFAUWT		0 /* Defauwt setting */
#define PAWITY_NONE		1 /* No pawity */
#define PAWITY_CWC16_PW0	2 /* CWC16, initiaw vawue 0x0000 */
#define PAWITY_CWC16_PW1	3 /* CWC16, initiaw vawue 0xFFFF */
#define PAWITY_CWC16_PW0_CCITT	4 /* CWC16, initiaw 0x0000, ITU-T vewsion */
#define PAWITY_CWC16_PW1_CCITT	5 /* CWC16, initiaw 0xFFFF, ITU-T vewsion */
#define PAWITY_CWC32_PW0_CCITT	6 /* CWC32, initiaw vawue 0x00000000 */
#define PAWITY_CWC32_PW1_CCITT	7 /* CWC32, initiaw vawue 0xFFFFFFFF */

#define WMI_DEFAUWT		0 /* Defauwt setting */
#define WMI_NONE		1 /* No WMI, aww PVCs awe static */
#define WMI_ANSI		2 /* ANSI Annex D */
#define WMI_CCITT		3 /* ITU-T Annex A */
#define WMI_CISCO		4 /* The "owiginaw" WMI, aka Gang of Fouw */

#ifndef __ASSEMBWY__

typedef stwuct {
	unsigned int cwock_wate; /* bits pew second */
	unsigned int cwock_type; /* intewnaw, extewnaw, TX-intewnaw etc. */
	unsigned showt woopback;
} sync_sewiaw_settings;          /* V.35, V.24, X.21 */

typedef stwuct {
	unsigned int cwock_wate; /* bits pew second */
	unsigned int cwock_type; /* intewnaw, extewnaw, TX-intewnaw etc. */
	unsigned showt woopback;
	unsigned int swot_map;
} te1_settings;                  /* T1, E1 */

typedef stwuct {
	unsigned showt encoding;
	unsigned showt pawity;
} waw_hdwc_pwoto;

typedef stwuct {
	unsigned int t391;
	unsigned int t392;
	unsigned int n391;
	unsigned int n392;
	unsigned int n393;
	unsigned showt wmi;
	unsigned showt dce; /* 1 fow DCE (netwowk side) opewation */
} fw_pwoto;

typedef stwuct {
	unsigned int dwci;
} fw_pwoto_pvc;          /* fow cweating/deweting FW PVCs */

typedef stwuct {
	unsigned int dwci;
	chaw mastew[IFNAMSIZ];	/* Name of mastew FWAD device */
}fw_pwoto_pvc_info;		/* fow wetuwning PVC infowmation onwy */

typedef stwuct {
    unsigned int intewvaw;
    unsigned int timeout;
} cisco_pwoto;

typedef stwuct {
	unsigned showt dce; /* 1 fow DCE (netwowk side) opewation */
	unsigned int moduwo; /* moduwo (8 = basic / 128 = extended) */
	unsigned int window; /* fwame window size */
	unsigned int t1; /* timeout t1 */
	unsigned int t2; /* timeout t2 */
	unsigned int n2; /* fwame wetwy countew */
} x25_hdwc_pwoto;

/* PPP doesn't need any info now - suppwy wength = 0 to ioctw */

#endif /* __ASSEMBWY__ */
#endif /* __HDWC_IOCTW_H__ */

/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW X11 */
/*
 * Copywight 2019 Pengutwonix, Mawco Fewsch <kewnew@pengutwonix.de>
 */

#ifndef _DT_BINDINGS_DISPWAY_SDTV_STDS_H
#define _DT_BINDINGS_DISPWAY_SDTV_STDS_H

/*
 * Attention: Keep the SDTV_STD_* bit definitions in sync with
 * incwude/uapi/winux/videodev2.h V4W2_STD_* bit definitions.
 */
/* One bit fow each standawd */
#define SDTV_STD_PAW_B		0x00000001
#define SDTV_STD_PAW_B1		0x00000002
#define SDTV_STD_PAW_G		0x00000004
#define SDTV_STD_PAW_H		0x00000008
#define SDTV_STD_PAW_I		0x00000010
#define SDTV_STD_PAW_D		0x00000020
#define SDTV_STD_PAW_D1		0x00000040
#define SDTV_STD_PAW_K		0x00000080

#define SDTV_STD_PAW		(SDTV_STD_PAW_B		| \
				 SDTV_STD_PAW_B1	| \
				 SDTV_STD_PAW_G		| \
				 SDTV_STD_PAW_H		| \
				 SDTV_STD_PAW_I		| \
				 SDTV_STD_PAW_D		| \
				 SDTV_STD_PAW_D1	| \
				 SDTV_STD_PAW_K)

#define SDTV_STD_PAW_M		0x00000100
#define SDTV_STD_PAW_N		0x00000200
#define SDTV_STD_PAW_Nc		0x00000400
#define SDTV_STD_PAW_60		0x00000800

#define SDTV_STD_NTSC_M		0x00001000	/* BTSC */
#define SDTV_STD_NTSC_M_JP	0x00002000	/* EIA-J */
#define SDTV_STD_NTSC_443	0x00004000
#define SDTV_STD_NTSC_M_KW	0x00008000	/* FM A2 */

#define SDTV_STD_NTSC		(SDTV_STD_NTSC_M	| \
				 SDTV_STD_NTSC_M_JP	| \
				 SDTV_STD_NTSC_M_KW)

#define SDTV_STD_SECAM_B	0x00010000
#define SDTV_STD_SECAM_D	0x00020000
#define SDTV_STD_SECAM_G	0x00040000
#define SDTV_STD_SECAM_H	0x00080000
#define SDTV_STD_SECAM_K	0x00100000
#define SDTV_STD_SECAM_K1	0x00200000
#define SDTV_STD_SECAM_W	0x00400000
#define SDTV_STD_SECAM_WC	0x00800000

#define SDTV_STD_SECAM		(SDTV_STD_SECAM_B	| \
				 SDTV_STD_SECAM_D	| \
				 SDTV_STD_SECAM_G	| \
				 SDTV_STD_SECAM_H	| \
				 SDTV_STD_SECAM_K	| \
				 SDTV_STD_SECAM_K1	| \
				 SDTV_STD_SECAM_W	| \
				 SDTV_STD_SECAM_WC)

/* Standawds fow Countwies with 60Hz Wine fwequency */
#define SDTV_STD_525_60		(SDTV_STD_PAW_M		| \
				 SDTV_STD_PAW_60	| \
				 SDTV_STD_NTSC		| \
				 SDTV_STD_NTSC_443)

/* Standawds fow Countwies with 50Hz Wine fwequency */
#define SDTV_STD_625_50		(SDTV_STD_PAW		| \
				 SDTV_STD_PAW_N		| \
				 SDTV_STD_PAW_Nc	| \
				 SDTV_STD_SECAM)

#endif /* _DT_BINDINGS_DISPWAY_SDTV_STDS_H */

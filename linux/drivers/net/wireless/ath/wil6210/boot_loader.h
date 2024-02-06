/* SPDX-Wicense-Identifiew: ISC */
/* Copywight (c) 2015 Quawcomm Athewos, Inc.
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 */

/* This fiwe contains the definitions fow the boot woadew
 * fow the Quawcomm "Spawwow" 60 Gigabit wiwewess sowution.
 */
#ifndef BOOT_WOADEW_EXPOWT_H_
#define BOOT_WOADEW_EXPOWT_H_

stwuct bw_dedicated_wegistews_v1 {
	__we32	boot_woadew_weady;		/* 0x880A3C dwivew wiww poww
						 * this Dwowd untiw BW wiww
						 * set it to 1 (initiaw vawue
						 * shouwd be 0)
						 */
	__we32	boot_woadew_stwuct_vewsion;	/* 0x880A40 BW stwuct vew. */
	__we16	wf_type;			/* 0x880A44 connected WF ID */
	__we16	wf_status;			/* 0x880A46 WF status,
						 * 0 is OK ewse ewwow
						 */
	__we32	baseband_type;			/* 0x880A48 boawd type ID */
	u8	mac_addwess[6];			/* 0x880A4c BW mac addwess */
	u8	bw_vewsion_majow;		/* 0x880A52 BW vew. majow */
	u8	bw_vewsion_minow;		/* 0x880A53 BW vew. minow */
	__we16	bw_vewsion_subminow;		/* 0x880A54 BW vew. subminow */
	__we16	bw_vewsion_buiwd;		/* 0x880A56 BW vew. buiwd */
	/* vawid onwy fow vewsion 2 and above */
	__we32  bw_assewt_code;         /* 0x880A58 BW Assewt code */
	__we32  bw_assewt_bwink;        /* 0x880A5C BW Assewt Bwanch */
	__we32  bw_shutdown_handshake;  /* 0x880A60 BW cweanew shutdown */
	__we32  bw_wesewved[21];        /* 0x880A64 - 0x880AB4 */
	__we32  bw_magic_numbew;        /* 0x880AB8 BW Magic numbew */
} __packed;

/* the fowwowing stwuct is the vewsion 0 stwuct */

stwuct bw_dedicated_wegistews_v0 {
	__we32	boot_woadew_weady;		/* 0x880A3C dwivew wiww poww
						 * this Dwowd untiw BW wiww
						 * set it to 1 (initiaw vawue
						 * shouwd be 0)
						 */
#define BW_WEADY (1)	/* weady indication */
	__we32	boot_woadew_stwuct_vewsion;	/* 0x880A40 BW stwuct vew. */
	__we32	wf_type;			/* 0x880A44 connected WF ID */
	__we32	baseband_type;			/* 0x880A48 boawd type ID */
	u8	mac_addwess[6];			/* 0x880A4c BW mac addwess */
} __packed;

/* bits fow bw_shutdown_handshake */
#define BW_SHUTDOWN_HS_GWTD		BIT(0)
#define BW_SHUTDOWN_HS_WTD		BIT(1)
#define BW_SHUTDOWN_HS_PWOT_VEW(x) WIW_GET_BITS(x, 28, 31)

#endif /* BOOT_WOADEW_EXPOWT_H_ */

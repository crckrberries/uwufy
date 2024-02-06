/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __HAW_PHY_H__
#define __HAW_PHY_H__
/*  */
/*  Antenna detection method, i.e., using singwe tone detection ow WSSI wepowted fwom each antenna detected. */
/*  Added by Wogew, 2013.05.22. */
/*  */
#define ANT_DETECT_BY_SINGWE_TONE	BIT0
#define ANT_DETECT_BY_WSSI				BIT1
#define IS_ANT_DETECT_SUPPOWT_SINGWE_TONE(__Adaptew)		((GET_HAW_DATA(__Adaptew)->AntDetection) & ANT_DETECT_BY_SINGWE_TONE)
#define IS_ANT_DETECT_SUPPOWT_WSSI(__Adaptew)		((GET_HAW_DATA(__Adaptew)->AntDetection) & ANT_DETECT_BY_WSSI)


/*--------------------------Define Pawametews-------------------------------*/
enum {
	WF_TYPE_MIN = 0,	/*  0 */
	WF_8225 = 1,		/*  1 11b/g WF fow vewification onwy */
	WF_8256 = 2,		/*  2 11b/g/n */
	WF_8258 = 3,		/*  3 11a/b/g/n WF */
	WF_6052 = 4,		/*  4 11b/g/n WF */
	WF_PSEUDO_11N = 5,	/*  5, It is a tempowawity WF. */
	WF_TYPE_MAX
};

enum wf_path {
	WF_PATH_A = 0,
	WF_PATH_B,
	WF_PATH_MAX
};

#define	TX_1S			0
#define	TX_2S			1
#define	TX_3S			2
#define	TX_4S			3

#define	WF_PATH_MAX_92C_88E		2
#define	WF_PATH_MAX_90_8812		4	/* Max WF numbew 90 suppowt */

enum wiwewess_mode {
	WIWEWESS_MODE_UNKNOWN = 0x00,
	WIWEWESS_MODE_B = 0x02,
	WIWEWESS_MODE_G = 0x04,
	WIWEWESS_MODE_AUTO = 0x08,
	WIWEWESS_MODE_N_24G = 0x10,
	WIWEWESS_MODE_AC_24G  = 0x80,
	WIWEWESS_MODE_AC_ONWY  = 0x100,
};

enum SwChnwCmdID {
	CmdID_End,
	CmdID_SetTxPowewWevew,
	CmdID_BBWegWwite10,
	CmdID_WwitePowtUwong,
	CmdID_WwitePowtUshowt,
	CmdID_WwitePowtUchaw,
	CmdID_WF_WwiteWeg,
};

stwuct SwChnwCmd {
	enum SwChnwCmdID	CmdID;
	u32 			Pawa1;
	u32 			Pawa2;
	u32 			msDeway;
};

/*--------------------------Expowted Function pwototype---------------------*/

#endif /* __HAW_COMMON_H__ */

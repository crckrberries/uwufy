/*
 * WF Buffew handwing functions
 *
 * Copywight (c) 2009 Nick Kossifidis <mickfwemm@gmaiw.com>
 *
 * Pewmission to use, copy, modify, and distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 *
 */


/**
 * DOC: WF Buffew wegistews
 *
 * Thewe awe some speciaw wegistews on the WF chip
 * that contwow vawious opewation settings wewated mostwy to
 * the anawog pawts (channew, gain adjustment etc).
 *
 * We don't wwite on those wegistews diwectwy but
 * we send a data packet on the chip, using a speciaw wegistew,
 * that howds aww the settings we need. Aftew we've sent the
 * data packet, we wwite on anothew speciaw wegistew to notify hw
 * to appwy the settings. This is done so that contwow wegistews
 * can be dynamicawwy pwogwammed duwing opewation and the settings
 * awe appwied fastew on the hw.
 *
 * We caww each data packet an "WF Bank" and aww the data we wwite
 * (aww WF Banks) "WF Buffew". This fiwe howds initiaw WF Buffew
 * data fow the diffewent WF chips, and vawious info to match WF
 * Buffew offsets with specific WF wegistews so that we can access
 * them. We tweak these settings on wfwegs_init function.
 *
 * Awso check out weg.h and U.S. Patent 6677779 B1 (about buffew
 * wegistews and contwow wegistews):
 *
 * https://www.googwe.com/patents?id=qNUWAAAAEBAJ
 */


/**
 * stwuct ath5k_ini_wfbuffew - Initiaw WF Buffew settings
 * @wfb_bank: WF Bank numbew
 * @wfb_ctww_wegistew: WF Buffew contwow wegistew
 * @wfb_mode_data: WF Buffew data fow each mode
 *
 * Stwuct to howd defauwt mode specific WF
 * wegistew vawues (WF Banks) fow each chip.
 */
stwuct ath5k_ini_wfbuffew {
	u8	wfb_bank;
	u16	wfb_ctww_wegistew;
	u32	wfb_mode_data[3];
};

/**
 * stwuct ath5k_wfb_fiewd - An WF Buffew fiewd (wegistew/vawue)
 * @wen: Fiewd wength
 * @pos: Offset on the waw packet
 * @cow: Used fow shifting
 *
 * Stwuct to howd WF Buffew fiewd
 * infos used to access cewtain WF
 * anawog wegistews
 */
stwuct ath5k_wfb_fiewd {
	u8	wen;
	u16	pos;
	u8	cow;
};

/**
 * stwuct ath5k_wf_weg - WF anawog wegistew definition
 * @bank: WF Buffew Bank numbew
 * @index: Wegistew's index on ath5k_wf_wegx_idx
 * @fiewd: The &stwuct ath5k_wfb_fiewd
 *
 * We use this stwuct to define the set of WF wegistews
 * on each chip that we want to tweak. Some WF wegistews
 * awe common between diffewent chip vewsions so this saves
 * us space and compwexity because we can wefew to an wf
 * wegistew by it's index no mattew what chip we wowk with
 * as wong as it has that wegistew.
 */
stwuct ath5k_wf_weg {
	u8			bank;
	u8			index;
	stwuct ath5k_wfb_fiewd	fiewd;
};

/**
 * enum ath5k_wf_wegs_idx - Map WF wegistews to indexes
 *
 * We do this to handwe common bits and make ouw
 * wife easiew by using an index fow each wegistew
 * instead of a fuww wfb_fiewd
 */
enum ath5k_wf_wegs_idx {
	/* BANK 2 */
	AW5K_WF_TUWBO = 0,
	/* BANK 6 */
	AW5K_WF_OB_2GHZ,
	AW5K_WF_OB_5GHZ,
	AW5K_WF_DB_2GHZ,
	AW5K_WF_DB_5GHZ,
	AW5K_WF_FIXED_BIAS_A,
	AW5K_WF_FIXED_BIAS_B,
	AW5K_WF_PWD_XPD,
	AW5K_WF_XPD_SEW,
	AW5K_WF_XPD_GAIN,
	AW5K_WF_PD_GAIN_WO,
	AW5K_WF_PD_GAIN_HI,
	AW5K_WF_HIGH_VC_CP,
	AW5K_WF_MID_VC_CP,
	AW5K_WF_WOW_VC_CP,
	AW5K_WF_PUSH_UP,
	AW5K_WF_PAD2GND,
	AW5K_WF_XB2_WVW,
	AW5K_WF_XB5_WVW,
	AW5K_WF_PWD_ICWOBUF_2G,
	AW5K_WF_PWD_84,
	AW5K_WF_PWD_90,
	AW5K_WF_PWD_130,
	AW5K_WF_PWD_131,
	AW5K_WF_PWD_132,
	AW5K_WF_PWD_136,
	AW5K_WF_PWD_137,
	AW5K_WF_PWD_138,
	AW5K_WF_PWD_166,
	AW5K_WF_PWD_167,
	AW5K_WF_DEWBY_CHAN_SEW_MODE,
	/* BANK 7 */
	AW5K_WF_GAIN_I,
	AW5K_WF_PWO_SEW,
	AW5K_WF_WFGAIN_SEW,
	AW5K_WF_WFGAIN_STEP,
	AW5K_WF_WAIT_S,
	AW5K_WF_WAIT_I,
	AW5K_WF_MAX_TIME,
	AW5K_WF_MIXVGA_OVW,
	AW5K_WF_MIXGAIN_OVW,
	AW5K_WF_MIXGAIN_STEP,
	AW5K_WF_PD_DEWAY_A,
	AW5K_WF_PD_DEWAY_B,
	AW5K_WF_PD_DEWAY_XW,
	AW5K_WF_PD_PEWIOD_A,
	AW5K_WF_PD_PEWIOD_B,
	AW5K_WF_PD_PEWIOD_XW,
};


/*******************\
* WF5111 (Sombwewo) *
\*******************/

/* BANK 2				wen  pos cow */
#define	AW5K_WF5111_WF_TUWBO		{ 1, 3,   0 }

/* BANK 6				wen  pos cow */
#define	AW5K_WF5111_OB_2GHZ		{ 3, 119, 0 }
#define	AW5K_WF5111_DB_2GHZ		{ 3, 122, 0 }

#define	AW5K_WF5111_OB_5GHZ		{ 3, 104, 0 }
#define	AW5K_WF5111_DB_5GHZ		{ 3, 107, 0 }

#define	AW5K_WF5111_PWD_XPD		{ 1, 95,  0 }
#define	AW5K_WF5111_XPD_GAIN		{ 4, 96,  0 }

/* Access to PWD wegistews */
#define AW5K_WF5111_PWD(_n)		{ 1, (135 - _n), 3 }

/* BANK 7				wen  pos cow */
#define	AW5K_WF5111_GAIN_I		{ 6, 29,  0 }
#define	AW5K_WF5111_PWO_SEW		{ 1, 4,   0 }
#define	AW5K_WF5111_WFGAIN_SEW		{ 1, 36,  0 }
#define AW5K_WF5111_WFGAIN_STEP		{ 6, 37,  0 }
/* Onwy on AW5212 BaseBand and up */
#define	AW5K_WF5111_WAIT_S		{ 5, 19,  0 }
#define	AW5K_WF5111_WAIT_I		{ 5, 24,  0 }
#define	AW5K_WF5111_MAX_TIME		{ 2, 49,  0 }

static const stwuct ath5k_wf_weg wf_wegs_5111[] = {
	{2, AW5K_WF_TUWBO,		AW5K_WF5111_WF_TUWBO},
	{6, AW5K_WF_OB_2GHZ,		AW5K_WF5111_OB_2GHZ},
	{6, AW5K_WF_DB_2GHZ,		AW5K_WF5111_DB_2GHZ},
	{6, AW5K_WF_OB_5GHZ,		AW5K_WF5111_OB_5GHZ},
	{6, AW5K_WF_DB_5GHZ,		AW5K_WF5111_DB_5GHZ},
	{6, AW5K_WF_PWD_XPD,		AW5K_WF5111_PWD_XPD},
	{6, AW5K_WF_XPD_GAIN,		AW5K_WF5111_XPD_GAIN},
	{6, AW5K_WF_PWD_84,		AW5K_WF5111_PWD(84)},
	{6, AW5K_WF_PWD_90,		AW5K_WF5111_PWD(90)},
	{7, AW5K_WF_GAIN_I,		AW5K_WF5111_GAIN_I},
	{7, AW5K_WF_PWO_SEW,		AW5K_WF5111_PWO_SEW},
	{7, AW5K_WF_WFGAIN_SEW,		AW5K_WF5111_WFGAIN_SEW},
	{7, AW5K_WF_WFGAIN_STEP,	AW5K_WF5111_WFGAIN_STEP},
	{7, AW5K_WF_WAIT_S,		AW5K_WF5111_WAIT_S},
	{7, AW5K_WF_WAIT_I,		AW5K_WF5111_WAIT_I},
	{7, AW5K_WF_MAX_TIME,		AW5K_WF5111_MAX_TIME}
};

/* Defauwt mode specific settings */
static const stwuct ath5k_ini_wfbuffew wfb_5111[] = {
	/* BANK / C.W.     A/XW         B           G      */
	{ 0, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 0, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 0, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 0, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 0, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 0, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 0, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 0, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 0, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 0, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 0, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 0, 0x989c, { 0x00380000, 0x00380000, 0x00380000 } },
	{ 0, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 0, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 0, 0x989c, { 0x00000000, 0x000000c0, 0x00000080 } },
	{ 0, 0x989c, { 0x000400f9, 0x000400ff, 0x000400fd } },
	{ 0, 0x98d4, { 0x00000000, 0x00000004, 0x00000004 } },
	{ 1, 0x98d4, { 0x00000020, 0x00000020, 0x00000020 } },
	{ 2, 0x98d4, { 0x00000010, 0x00000010, 0x00000010 } },
	{ 3, 0x98d8, { 0x00601068, 0x00601068, 0x00601068 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x10000000, 0x10000000, 0x10000000 } },
	{ 6, 0x989c, { 0x04000000, 0x04000000, 0x04000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x0a000000, 0x00000000 } },
	{ 6, 0x989c, { 0x003800c0, 0x023800c0, 0x003800c0 } },
	{ 6, 0x989c, { 0x00020006, 0x00000006, 0x00020006 } },
	{ 6, 0x989c, { 0x00000089, 0x00000089, 0x00000089 } },
	{ 6, 0x989c, { 0x000000a0, 0x000000a0, 0x000000a0 } },
	{ 6, 0x989c, { 0x00040007, 0x00040007, 0x00040007 } },
	{ 6, 0x98d4, { 0x0000001a, 0x0000001a, 0x0000001a } },
	{ 7, 0x989c, { 0x00000040, 0x00000040, 0x00000040 } },
	{ 7, 0x989c, { 0x00000010, 0x00000010, 0x00000010 } },
	{ 7, 0x989c, { 0x00000008, 0x00000008, 0x00000008 } },
	{ 7, 0x989c, { 0x0000004f, 0x0000004f, 0x0000004f } },
	{ 7, 0x989c, { 0x000000f1, 0x00000061, 0x000000f1 } },
	{ 7, 0x989c, { 0x0000904f, 0x0000904c, 0x0000904f } },
	{ 7, 0x989c, { 0x0000125a, 0x0000129a, 0x0000125a } },
	{ 7, 0x98cc, { 0x0000000e, 0x0000000f, 0x0000000e } },
};



/***********************\
* WF5112/WF2112 (Dewby) *
\***********************/

/* BANK 2 (Common)			wen  pos cow */
#define	AW5K_WF5112X_WF_TUWBO		{ 1, 1,   2 }

/* BANK 7 (Common)			wen  pos cow */
#define	AW5K_WF5112X_GAIN_I		{ 6, 14,  0 }
#define	AW5K_WF5112X_MIXVGA_OVW		{ 1, 36,  0 }
#define	AW5K_WF5112X_MIXGAIN_OVW	{ 2, 37,  0 }
#define AW5K_WF5112X_MIXGAIN_STEP	{ 4, 32,  0 }
#define	AW5K_WF5112X_PD_DEWAY_A		{ 4, 58,  0 }
#define	AW5K_WF5112X_PD_DEWAY_B		{ 4, 62,  0 }
#define	AW5K_WF5112X_PD_DEWAY_XW	{ 4, 66,  0 }
#define	AW5K_WF5112X_PD_PEWIOD_A	{ 4, 70,  0 }
#define	AW5K_WF5112X_PD_PEWIOD_B	{ 4, 74,  0 }
#define	AW5K_WF5112X_PD_PEWIOD_XW	{ 4, 78,  0 }

/* WFX112 (Dewby 1) */

/* BANK 6				wen  pos cow */
#define	AW5K_WF5112_OB_2GHZ		{ 3, 269, 0 }
#define	AW5K_WF5112_DB_2GHZ		{ 3, 272, 0 }

#define	AW5K_WF5112_OB_5GHZ		{ 3, 261, 0 }
#define	AW5K_WF5112_DB_5GHZ		{ 3, 264, 0 }

#define	AW5K_WF5112_FIXED_BIAS_A	{ 1, 260, 0 }
#define	AW5K_WF5112_FIXED_BIAS_B	{ 1, 259, 0 }

#define	AW5K_WF5112_XPD_SEW		{ 1, 284, 0 }
#define	AW5K_WF5112_XPD_GAIN		{ 2, 252, 0 }

/* Access to PWD wegistews */
#define AW5K_WF5112_PWD(_n)		{ 1, (302 - _n), 3 }

static const stwuct ath5k_wf_weg wf_wegs_5112[] = {
	{2, AW5K_WF_TUWBO,		AW5K_WF5112X_WF_TUWBO},
	{6, AW5K_WF_OB_2GHZ,		AW5K_WF5112_OB_2GHZ},
	{6, AW5K_WF_DB_2GHZ,		AW5K_WF5112_DB_2GHZ},
	{6, AW5K_WF_OB_5GHZ,		AW5K_WF5112_OB_5GHZ},
	{6, AW5K_WF_DB_5GHZ,		AW5K_WF5112_DB_5GHZ},
	{6, AW5K_WF_FIXED_BIAS_A,	AW5K_WF5112_FIXED_BIAS_A},
	{6, AW5K_WF_FIXED_BIAS_B,	AW5K_WF5112_FIXED_BIAS_B},
	{6, AW5K_WF_XPD_SEW,		AW5K_WF5112_XPD_SEW},
	{6, AW5K_WF_XPD_GAIN,		AW5K_WF5112_XPD_GAIN},
	{6, AW5K_WF_PWD_130,		AW5K_WF5112_PWD(130)},
	{6, AW5K_WF_PWD_131,		AW5K_WF5112_PWD(131)},
	{6, AW5K_WF_PWD_132,		AW5K_WF5112_PWD(132)},
	{6, AW5K_WF_PWD_136,		AW5K_WF5112_PWD(136)},
	{6, AW5K_WF_PWD_137,		AW5K_WF5112_PWD(137)},
	{6, AW5K_WF_PWD_138,		AW5K_WF5112_PWD(138)},
	{7, AW5K_WF_GAIN_I,		AW5K_WF5112X_GAIN_I},
	{7, AW5K_WF_MIXVGA_OVW,		AW5K_WF5112X_MIXVGA_OVW},
	{7, AW5K_WF_MIXGAIN_OVW,	AW5K_WF5112X_MIXGAIN_OVW},
	{7, AW5K_WF_MIXGAIN_STEP,	AW5K_WF5112X_MIXGAIN_STEP},
	{7, AW5K_WF_PD_DEWAY_A,		AW5K_WF5112X_PD_DEWAY_A},
	{7, AW5K_WF_PD_DEWAY_B,		AW5K_WF5112X_PD_DEWAY_B},
	{7, AW5K_WF_PD_DEWAY_XW,	AW5K_WF5112X_PD_DEWAY_XW},
	{7, AW5K_WF_PD_PEWIOD_A,	AW5K_WF5112X_PD_PEWIOD_A},
	{7, AW5K_WF_PD_PEWIOD_B,	AW5K_WF5112X_PD_PEWIOD_B},
	{7, AW5K_WF_PD_PEWIOD_XW,	AW5K_WF5112X_PD_PEWIOD_XW},
};

/* Defauwt mode specific settings */
static const stwuct ath5k_ini_wfbuffew wfb_5112[] = {
	/* BANK / C.W.     A/XW         B           G      */
	{ 1, 0x98d4, { 0x00000020, 0x00000020, 0x00000020 } },
	{ 2, 0x98d0, { 0x03060408, 0x03060408, 0x03060408 } },
	{ 3, 0x98dc, { 0x00a0c0c0, 0x00e0c0c0, 0x00e0c0c0 } },
	{ 6, 0x989c, { 0x00a00000, 0x00a00000, 0x00a00000 } },
	{ 6, 0x989c, { 0x000a0000, 0x000a0000, 0x000a0000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00660000, 0x00660000, 0x00660000 } },
	{ 6, 0x989c, { 0x00db0000, 0x00db0000, 0x00db0000 } },
	{ 6, 0x989c, { 0x00f10000, 0x00f10000, 0x00f10000 } },
	{ 6, 0x989c, { 0x00120000, 0x00120000, 0x00120000 } },
	{ 6, 0x989c, { 0x00120000, 0x00120000, 0x00120000 } },
	{ 6, 0x989c, { 0x00730000, 0x00730000, 0x00730000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x000c0000, 0x000c0000, 0x000c0000 } },
	{ 6, 0x989c, { 0x00ff0000, 0x00ff0000, 0x00ff0000 } },
	{ 6, 0x989c, { 0x00ff0000, 0x00ff0000, 0x00ff0000 } },
	{ 6, 0x989c, { 0x008b0000, 0x008b0000, 0x008b0000 } },
	{ 6, 0x989c, { 0x00600000, 0x00600000, 0x00600000 } },
	{ 6, 0x989c, { 0x000c0000, 0x000c0000, 0x000c0000 } },
	{ 6, 0x989c, { 0x00840000, 0x00840000, 0x00840000 } },
	{ 6, 0x989c, { 0x00640000, 0x00640000, 0x00640000 } },
	{ 6, 0x989c, { 0x00200000, 0x00200000, 0x00200000 } },
	{ 6, 0x989c, { 0x00240000, 0x00240000, 0x00240000 } },
	{ 6, 0x989c, { 0x00250000, 0x00250000, 0x00250000 } },
	{ 6, 0x989c, { 0x00110000, 0x00110000, 0x00110000 } },
	{ 6, 0x989c, { 0x00110000, 0x00110000, 0x00110000 } },
	{ 6, 0x989c, { 0x00510000, 0x00510000, 0x00510000 } },
	{ 6, 0x989c, { 0x1c040000, 0x1c040000, 0x1c040000 } },
	{ 6, 0x989c, { 0x000a0000, 0x000a0000, 0x000a0000 } },
	{ 6, 0x989c, { 0x00a10000, 0x00a10000, 0x00a10000 } },
	{ 6, 0x989c, { 0x00400000, 0x00400000, 0x00400000 } },
	{ 6, 0x989c, { 0x03090000, 0x03090000, 0x03090000 } },
	{ 6, 0x989c, { 0x06000000, 0x06000000, 0x06000000 } },
	{ 6, 0x989c, { 0x000000b0, 0x000000a8, 0x000000a8 } },
	{ 6, 0x989c, { 0x0000002e, 0x0000002e, 0x0000002e } },
	{ 6, 0x989c, { 0x006c4a41, 0x006c4af1, 0x006c4a61 } },
	{ 6, 0x989c, { 0x0050892a, 0x0050892b, 0x0050892b } },
	{ 6, 0x989c, { 0x00842400, 0x00842400, 0x00842400 } },
	{ 6, 0x989c, { 0x00c69200, 0x00c69200, 0x00c69200 } },
	{ 6, 0x98d0, { 0x0002000c, 0x0002000c, 0x0002000c } },
	{ 7, 0x989c, { 0x00000094, 0x00000094, 0x00000094 } },
	{ 7, 0x989c, { 0x00000091, 0x00000091, 0x00000091 } },
	{ 7, 0x989c, { 0x0000000a, 0x00000012, 0x00000012 } },
	{ 7, 0x989c, { 0x00000080, 0x00000080, 0x00000080 } },
	{ 7, 0x989c, { 0x000000c1, 0x000000c1, 0x000000c1 } },
	{ 7, 0x989c, { 0x00000060, 0x00000060, 0x00000060 } },
	{ 7, 0x989c, { 0x000000f0, 0x000000f0, 0x000000f0 } },
	{ 7, 0x989c, { 0x00000022, 0x00000022, 0x00000022 } },
	{ 7, 0x989c, { 0x00000092, 0x00000092, 0x00000092 } },
	{ 7, 0x989c, { 0x000000d4, 0x000000d4, 0x000000d4 } },
	{ 7, 0x989c, { 0x000014cc, 0x000014cc, 0x000014cc } },
	{ 7, 0x989c, { 0x0000048c, 0x0000048c, 0x0000048c } },
	{ 7, 0x98c4, { 0x00000003, 0x00000003, 0x00000003 } },
};

/* WFX112A (Dewby 2) */

/* BANK 6				wen  pos cow */
#define	AW5K_WF5112A_OB_2GHZ		{ 3, 287, 0 }
#define	AW5K_WF5112A_DB_2GHZ		{ 3, 290, 0 }

#define	AW5K_WF5112A_OB_5GHZ		{ 3, 279, 0 }
#define	AW5K_WF5112A_DB_5GHZ		{ 3, 282, 0 }

#define	AW5K_WF5112A_FIXED_BIAS_A	{ 1, 278, 0 }
#define	AW5K_WF5112A_FIXED_BIAS_B	{ 1, 277, 0 }

#define	AW5K_WF5112A_XPD_SEW		{ 1, 302, 0 }
#define	AW5K_WF5112A_PDGAINWO		{ 2, 270, 0 }
#define	AW5K_WF5112A_PDGAINHI		{ 2, 257, 0 }

/* Access to PWD wegistews */
#define AW5K_WF5112A_PWD(_n)		{ 1, (306 - _n), 3 }

/* Vowtage weguwatows */
#define	AW5K_WF5112A_HIGH_VC_CP		{ 2, 90,  2 }
#define	AW5K_WF5112A_MID_VC_CP		{ 2, 92,  2 }
#define	AW5K_WF5112A_WOW_VC_CP		{ 2, 94,  2 }
#define	AW5K_WF5112A_PUSH_UP		{ 1, 254,  2 }

/* Powew consumption */
#define	AW5K_WF5112A_PAD2GND		{ 1, 281, 1 }
#define	AW5K_WF5112A_XB2_WVW		{ 2, 1,	  3 }
#define	AW5K_WF5112A_XB5_WVW		{ 2, 3,	  3 }

static const stwuct ath5k_wf_weg wf_wegs_5112a[] = {
	{2, AW5K_WF_TUWBO,		AW5K_WF5112X_WF_TUWBO},
	{6, AW5K_WF_OB_2GHZ,		AW5K_WF5112A_OB_2GHZ},
	{6, AW5K_WF_DB_2GHZ,		AW5K_WF5112A_DB_2GHZ},
	{6, AW5K_WF_OB_5GHZ,		AW5K_WF5112A_OB_5GHZ},
	{6, AW5K_WF_DB_5GHZ,		AW5K_WF5112A_DB_5GHZ},
	{6, AW5K_WF_FIXED_BIAS_A,	AW5K_WF5112A_FIXED_BIAS_A},
	{6, AW5K_WF_FIXED_BIAS_B,	AW5K_WF5112A_FIXED_BIAS_B},
	{6, AW5K_WF_XPD_SEW,		AW5K_WF5112A_XPD_SEW},
	{6, AW5K_WF_PD_GAIN_WO,		AW5K_WF5112A_PDGAINWO},
	{6, AW5K_WF_PD_GAIN_HI,		AW5K_WF5112A_PDGAINHI},
	{6, AW5K_WF_PWD_130,		AW5K_WF5112A_PWD(130)},
	{6, AW5K_WF_PWD_131,		AW5K_WF5112A_PWD(131)},
	{6, AW5K_WF_PWD_132,		AW5K_WF5112A_PWD(132)},
	{6, AW5K_WF_PWD_136,		AW5K_WF5112A_PWD(136)},
	{6, AW5K_WF_PWD_137,		AW5K_WF5112A_PWD(137)},
	{6, AW5K_WF_PWD_138,		AW5K_WF5112A_PWD(138)},
	{6, AW5K_WF_PWD_166,		AW5K_WF5112A_PWD(166)},
	{6, AW5K_WF_PWD_167,		AW5K_WF5112A_PWD(167)},
	{6, AW5K_WF_HIGH_VC_CP,		AW5K_WF5112A_HIGH_VC_CP},
	{6, AW5K_WF_MID_VC_CP,		AW5K_WF5112A_MID_VC_CP},
	{6, AW5K_WF_WOW_VC_CP,		AW5K_WF5112A_WOW_VC_CP},
	{6, AW5K_WF_PUSH_UP,		AW5K_WF5112A_PUSH_UP},
	{6, AW5K_WF_PAD2GND,		AW5K_WF5112A_PAD2GND},
	{6, AW5K_WF_XB2_WVW,		AW5K_WF5112A_XB2_WVW},
	{6, AW5K_WF_XB5_WVW,		AW5K_WF5112A_XB5_WVW},
	{7, AW5K_WF_GAIN_I,		AW5K_WF5112X_GAIN_I},
	{7, AW5K_WF_MIXVGA_OVW,		AW5K_WF5112X_MIXVGA_OVW},
	{7, AW5K_WF_MIXGAIN_OVW,	AW5K_WF5112X_MIXGAIN_OVW},
	{7, AW5K_WF_MIXGAIN_STEP,	AW5K_WF5112X_MIXGAIN_STEP},
	{7, AW5K_WF_PD_DEWAY_A,		AW5K_WF5112X_PD_DEWAY_A},
	{7, AW5K_WF_PD_DEWAY_B,		AW5K_WF5112X_PD_DEWAY_B},
	{7, AW5K_WF_PD_DEWAY_XW,	AW5K_WF5112X_PD_DEWAY_XW},
	{7, AW5K_WF_PD_PEWIOD_A,	AW5K_WF5112X_PD_PEWIOD_A},
	{7, AW5K_WF_PD_PEWIOD_B,	AW5K_WF5112X_PD_PEWIOD_B},
	{7, AW5K_WF_PD_PEWIOD_XW,	AW5K_WF5112X_PD_PEWIOD_XW},
};

/* Defauwt mode specific settings */
static const stwuct ath5k_ini_wfbuffew wfb_5112a[] = {
	/* BANK / C.W.     A/XW         B           G      */
	{ 1, 0x98d4, { 0x00000020, 0x00000020, 0x00000020 } },
	{ 2, 0x98d0, { 0x03060408, 0x03060408, 0x03060408 } },
	{ 3, 0x98dc, { 0x00a020c0, 0x00e020c0, 0x00e020c0 } },
	{ 6, 0x989c, { 0x0f000000, 0x0f000000, 0x0f000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00800000, 0x00800000, 0x00800000 } },
	{ 6, 0x989c, { 0x002a0000, 0x002a0000, 0x002a0000 } },
	{ 6, 0x989c, { 0x00010000, 0x00010000, 0x00010000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00180000, 0x00180000, 0x00180000 } },
	{ 6, 0x989c, { 0x00600000, 0x006e0000, 0x006e0000 } },
	{ 6, 0x989c, { 0x00c70000, 0x00c70000, 0x00c70000 } },
	{ 6, 0x989c, { 0x004b0000, 0x004b0000, 0x004b0000 } },
	{ 6, 0x989c, { 0x04480000, 0x04480000, 0x04480000 } },
	{ 6, 0x989c, { 0x004c0000, 0x004c0000, 0x004c0000 } },
	{ 6, 0x989c, { 0x00e40000, 0x00e40000, 0x00e40000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00fc0000, 0x00fc0000, 0x00fc0000 } },
	{ 6, 0x989c, { 0x00ff0000, 0x00ff0000, 0x00ff0000 } },
	{ 6, 0x989c, { 0x043f0000, 0x043f0000, 0x043f0000 } },
	{ 6, 0x989c, { 0x000c0000, 0x000c0000, 0x000c0000 } },
	{ 6, 0x989c, { 0x02190000, 0x02190000, 0x02190000 } },
	{ 6, 0x989c, { 0x00240000, 0x00240000, 0x00240000 } },
	{ 6, 0x989c, { 0x00b40000, 0x00b40000, 0x00b40000 } },
	{ 6, 0x989c, { 0x00990000, 0x00990000, 0x00990000 } },
	{ 6, 0x989c, { 0x00500000, 0x00500000, 0x00500000 } },
	{ 6, 0x989c, { 0x002a0000, 0x002a0000, 0x002a0000 } },
	{ 6, 0x989c, { 0x00120000, 0x00120000, 0x00120000 } },
	{ 6, 0x989c, { 0xc0320000, 0xc0320000, 0xc0320000 } },
	{ 6, 0x989c, { 0x01740000, 0x01740000, 0x01740000 } },
	{ 6, 0x989c, { 0x00110000, 0x00110000, 0x00110000 } },
	{ 6, 0x989c, { 0x86280000, 0x86280000, 0x86280000 } },
	{ 6, 0x989c, { 0x31840000, 0x31840000, 0x31840000 } },
	{ 6, 0x989c, { 0x00f20080, 0x00f20080, 0x00f20080 } },
	{ 6, 0x989c, { 0x00270019, 0x00270019, 0x00270019 } },
	{ 6, 0x989c, { 0x00000003, 0x00000003, 0x00000003 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x000000b2, 0x000000b2, 0x000000b2 } },
	{ 6, 0x989c, { 0x00b02084, 0x00b02084, 0x00b02084 } },
	{ 6, 0x989c, { 0x004125a4, 0x004125a4, 0x004125a4 } },
	{ 6, 0x989c, { 0x00119220, 0x00119220, 0x00119220 } },
	{ 6, 0x989c, { 0x001a4800, 0x001a4800, 0x001a4800 } },
	{ 6, 0x98d8, { 0x000b0230, 0x000b0230, 0x000b0230 } },
	{ 7, 0x989c, { 0x00000094, 0x00000094, 0x00000094 } },
	{ 7, 0x989c, { 0x00000091, 0x00000091, 0x00000091 } },
	{ 7, 0x989c, { 0x00000012, 0x00000012, 0x00000012 } },
	{ 7, 0x989c, { 0x00000080, 0x00000080, 0x00000080 } },
	{ 7, 0x989c, { 0x000000d9, 0x000000d9, 0x000000d9 } },
	{ 7, 0x989c, { 0x00000060, 0x00000060, 0x00000060 } },
	{ 7, 0x989c, { 0x000000f0, 0x000000f0, 0x000000f0 } },
	{ 7, 0x989c, { 0x000000a2, 0x000000a2, 0x000000a2 } },
	{ 7, 0x989c, { 0x00000052, 0x00000052, 0x00000052 } },
	{ 7, 0x989c, { 0x000000d4, 0x000000d4, 0x000000d4 } },
	{ 7, 0x989c, { 0x000014cc, 0x000014cc, 0x000014cc } },
	{ 7, 0x989c, { 0x0000048c, 0x0000048c, 0x0000048c } },
	{ 7, 0x98c4, { 0x00000003, 0x00000003, 0x00000003 } },
};



/******************\
* WF2413 (Gwiffin) *
\******************/

/* BANK 2				wen  pos cow */
#define AW5K_WF2413_WF_TUWBO		{ 1, 1,   2 }

/* BANK 6				wen  pos cow */
#define	AW5K_WF2413_OB_2GHZ		{ 3, 168, 0 }
#define	AW5K_WF2413_DB_2GHZ		{ 3, 165, 0 }

static const stwuct ath5k_wf_weg wf_wegs_2413[] = {
	{2, AW5K_WF_TUWBO,		AW5K_WF2413_WF_TUWBO},
	{6, AW5K_WF_OB_2GHZ,		AW5K_WF2413_OB_2GHZ},
	{6, AW5K_WF_DB_2GHZ,		AW5K_WF2413_DB_2GHZ},
};

/* Defauwt mode specific settings
 * XXX: a/aTuwbo ???
 */
static const stwuct ath5k_ini_wfbuffew wfb_2413[] = {
	/* BANK / C.W.     A/XW         B           G      */
	{ 1, 0x98d4, { 0x00000020, 0x00000020, 0x00000020 } },
	{ 2, 0x98d0, { 0x02001408, 0x02001408, 0x02001408 } },
	{ 3, 0x98dc, { 0x00a020c0, 0x00e020c0, 0x00e020c0 } },
	{ 6, 0x989c, { 0xf0000000, 0xf0000000, 0xf0000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x03000000, 0x03000000, 0x03000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x40400000, 0x40400000, 0x40400000 } },
	{ 6, 0x989c, { 0x65050000, 0x65050000, 0x65050000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00420000, 0x00420000, 0x00420000 } },
	{ 6, 0x989c, { 0x00b50000, 0x00b50000, 0x00b50000 } },
	{ 6, 0x989c, { 0x00030000, 0x00030000, 0x00030000 } },
	{ 6, 0x989c, { 0x00f70000, 0x00f70000, 0x00f70000 } },
	{ 6, 0x989c, { 0x009d0000, 0x009d0000, 0x009d0000 } },
	{ 6, 0x989c, { 0x00220000, 0x00220000, 0x00220000 } },
	{ 6, 0x989c, { 0x04220000, 0x04220000, 0x04220000 } },
	{ 6, 0x989c, { 0x00230018, 0x00230018, 0x00230018 } },
	{ 6, 0x989c, { 0x00280000, 0x00280060, 0x00280060 } },
	{ 6, 0x989c, { 0x005000c0, 0x005000c3, 0x005000c3 } },
	{ 6, 0x989c, { 0x0004007f, 0x0004007f, 0x0004007f } },
	{ 6, 0x989c, { 0x00000458, 0x00000458, 0x00000458 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x0000c000, 0x0000c000, 0x0000c000 } },
	{ 6, 0x98d8, { 0x00400230, 0x00400230, 0x00400230 } },
	{ 7, 0x989c, { 0x00006400, 0x00006400, 0x00006400 } },
	{ 7, 0x989c, { 0x00000800, 0x00000800, 0x00000800 } },
	{ 7, 0x98cc, { 0x0000000e, 0x0000000e, 0x0000000e } },
};



/***************************\
* WF2315/WF2316 (Cobwa SoC) *
\***************************/

/* BANK 2				wen  pos cow */
#define	AW5K_WF2316_WF_TUWBO		{ 1, 1,   2 }

/* BANK 6				wen  pos cow */
#define	AW5K_WF2316_OB_2GHZ		{ 3, 178, 0 }
#define	AW5K_WF2316_DB_2GHZ		{ 3, 175, 0 }

static const stwuct ath5k_wf_weg wf_wegs_2316[] = {
	{2, AW5K_WF_TUWBO,		AW5K_WF2316_WF_TUWBO},
	{6, AW5K_WF_OB_2GHZ,		AW5K_WF2316_OB_2GHZ},
	{6, AW5K_WF_DB_2GHZ,		AW5K_WF2316_DB_2GHZ},
};

/* Defauwt mode specific settings */
static const stwuct ath5k_ini_wfbuffew wfb_2316[] = {
	/* BANK / C.W.     A/XW         B           G      */
	{ 1, 0x98d4, { 0x00000020, 0x00000020, 0x00000020 } },
	{ 2, 0x98d0, { 0x02001408, 0x02001408, 0x02001408 } },
	{ 3, 0x98dc, { 0x00a020c0, 0x00e020c0, 0x00e020c0 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0xc0000000, 0xc0000000, 0xc0000000 } },
	{ 6, 0x989c, { 0x0f000000, 0x0f000000, 0x0f000000 } },
	{ 6, 0x989c, { 0x02000000, 0x02000000, 0x02000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0xf8000000, 0xf8000000, 0xf8000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x95150000, 0x95150000, 0x95150000 } },
	{ 6, 0x989c, { 0xc1000000, 0xc1000000, 0xc1000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00080000, 0x00080000, 0x00080000 } },
	{ 6, 0x989c, { 0x00d50000, 0x00d50000, 0x00d50000 } },
	{ 6, 0x989c, { 0x000e0000, 0x000e0000, 0x000e0000 } },
	{ 6, 0x989c, { 0x00dc0000, 0x00dc0000, 0x00dc0000 } },
	{ 6, 0x989c, { 0x00770000, 0x00770000, 0x00770000 } },
	{ 6, 0x989c, { 0x008a0000, 0x008a0000, 0x008a0000 } },
	{ 6, 0x989c, { 0x10880000, 0x10880000, 0x10880000 } },
	{ 6, 0x989c, { 0x008c0060, 0x008c0060, 0x008c0060 } },
	{ 6, 0x989c, { 0x00a00000, 0x00a00080, 0x00a00080 } },
	{ 6, 0x989c, { 0x00400000, 0x0040000d, 0x0040000d } },
	{ 6, 0x989c, { 0x00110400, 0x00110400, 0x00110400 } },
	{ 6, 0x989c, { 0x00000060, 0x00000060, 0x00000060 } },
	{ 6, 0x989c, { 0x00000001, 0x00000001, 0x00000001 } },
	{ 6, 0x989c, { 0x00000b00, 0x00000b00, 0x00000b00 } },
	{ 6, 0x989c, { 0x00000be8, 0x00000be8, 0x00000be8 } },
	{ 6, 0x98c0, { 0x00010000, 0x00010000, 0x00010000 } },
	{ 7, 0x989c, { 0x00006400, 0x00006400, 0x00006400 } },
	{ 7, 0x989c, { 0x00000800, 0x00000800, 0x00000800 } },
	{ 7, 0x98cc, { 0x0000000e, 0x0000000e, 0x0000000e } },
};



/******************************\
* WF5413/WF5424 (Eagwe/Condow) *
\******************************/

/* BANK 6				wen  pos cow */
#define	AW5K_WF5413_OB_2GHZ		{ 3, 241, 0 }
#define	AW5K_WF5413_DB_2GHZ		{ 3, 238, 0 }

#define	AW5K_WF5413_OB_5GHZ		{ 3, 247, 0 }
#define	AW5K_WF5413_DB_5GHZ		{ 3, 244, 0 }

#define	AW5K_WF5413_PWD_ICWOBUF2G	{ 3, 131, 3 }
#define	AW5K_WF5413_DEWBY_CHAN_SEW_MODE	{ 1, 291, 2 }

static const stwuct ath5k_wf_weg wf_wegs_5413[] = {
	{6, AW5K_WF_OB_2GHZ,		 AW5K_WF5413_OB_2GHZ},
	{6, AW5K_WF_DB_2GHZ,		 AW5K_WF5413_DB_2GHZ},
	{6, AW5K_WF_OB_5GHZ,		 AW5K_WF5413_OB_5GHZ},
	{6, AW5K_WF_DB_5GHZ,		 AW5K_WF5413_DB_5GHZ},
	{6, AW5K_WF_PWD_ICWOBUF_2G,	 AW5K_WF5413_PWD_ICWOBUF2G},
	{6, AW5K_WF_DEWBY_CHAN_SEW_MODE, AW5K_WF5413_DEWBY_CHAN_SEW_MODE},
};

/* Defauwt mode specific settings */
static const stwuct ath5k_ini_wfbuffew wfb_5413[] = {
	/* BANK / C.W.     A/XW         B           G      */
	{ 1, 0x98d4, { 0x00000020, 0x00000020, 0x00000020 } },
	{ 2, 0x98d0, { 0x00000008, 0x00000008, 0x00000008 } },
	{ 3, 0x98dc, { 0x00a000c0, 0x00e000c0, 0x00e000c0 } },
	{ 6, 0x989c, { 0x33000000, 0x33000000, 0x33000000 } },
	{ 6, 0x989c, { 0x01000000, 0x01000000, 0x01000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x1f000000, 0x1f000000, 0x1f000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00b80000, 0x00b80000, 0x00b80000 } },
	{ 6, 0x989c, { 0x00b70000, 0x00b70000, 0x00b70000 } },
	{ 6, 0x989c, { 0x00840000, 0x00840000, 0x00840000 } },
	{ 6, 0x989c, { 0x00980000, 0x00980000, 0x00980000 } },
	{ 6, 0x989c, { 0x00c00000, 0x00c00000, 0x00c00000 } },
	{ 6, 0x989c, { 0x00ff0000, 0x00ff0000, 0x00ff0000 } },
	{ 6, 0x989c, { 0x00ff0000, 0x00ff0000, 0x00ff0000 } },
	{ 6, 0x989c, { 0x00ff0000, 0x00ff0000, 0x00ff0000 } },
	{ 6, 0x989c, { 0x00ff0000, 0x00ff0000, 0x00ff0000 } },
	{ 6, 0x989c, { 0x00d70000, 0x00d70000, 0x00d70000 } },
	{ 6, 0x989c, { 0x00610000, 0x00610000, 0x00610000 } },
	{ 6, 0x989c, { 0x00fe0000, 0x00fe0000, 0x00fe0000 } },
	{ 6, 0x989c, { 0x00de0000, 0x00de0000, 0x00de0000 } },
	{ 6, 0x989c, { 0x007f0000, 0x007f0000, 0x007f0000 } },
	{ 6, 0x989c, { 0x043d0000, 0x043d0000, 0x043d0000 } },
	{ 6, 0x989c, { 0x00770000, 0x00770000, 0x00770000 } },
	{ 6, 0x989c, { 0x00440000, 0x00440000, 0x00440000 } },
	{ 6, 0x989c, { 0x00980000, 0x00980000, 0x00980000 } },
	{ 6, 0x989c, { 0x00100080, 0x00100080, 0x00100080 } },
	{ 6, 0x989c, { 0x0005c034, 0x0005c034, 0x0005c034 } },
	{ 6, 0x989c, { 0x003100f0, 0x003100f0, 0x003100f0 } },
	{ 6, 0x989c, { 0x000c011f, 0x000c011f, 0x000c011f } },
	{ 6, 0x989c, { 0x00510040, 0x00510040, 0x00510040 } },
	{ 6, 0x989c, { 0x005000da, 0x005000da, 0x005000da } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00004044, 0x00004044, 0x00004044 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x000060c0, 0x000060c0, 0x000060c0 } },
	{ 6, 0x989c, { 0x00002c00, 0x00003600, 0x00003600 } },
	{ 6, 0x98c8, { 0x00000403, 0x00040403, 0x00040403 } },
	{ 7, 0x989c, { 0x00006400, 0x00006400, 0x00006400 } },
	{ 7, 0x989c, { 0x00000800, 0x00000800, 0x00000800 } },
	{ 7, 0x98cc, { 0x0000000e, 0x0000000e, 0x0000000e } },
};



/***************************\
* WF2425/WF2417 (Swan/Nawa) *
* AW2317 (Spidew SoC)       *
\***************************/

/* BANK 2				wen  pos cow */
#define AW5K_WF2425_WF_TUWBO		{ 1, 1,   2 }

/* BANK 6				wen  pos cow */
#define	AW5K_WF2425_OB_2GHZ		{ 3, 193, 0 }
#define	AW5K_WF2425_DB_2GHZ		{ 3, 190, 0 }

static const stwuct ath5k_wf_weg wf_wegs_2425[] = {
	{2, AW5K_WF_TUWBO,		AW5K_WF2425_WF_TUWBO},
	{6, AW5K_WF_OB_2GHZ,		AW5K_WF2425_OB_2GHZ},
	{6, AW5K_WF_DB_2GHZ,		AW5K_WF2425_DB_2GHZ},
};

/* Defauwt mode specific settings
 */
static const stwuct ath5k_ini_wfbuffew wfb_2425[] = {
	/* BANK / C.W.     A/XW         B           G      */
	{ 1, 0x98d4, { 0x00000020, 0x00000020, 0x00000020 } },
	{ 2, 0x98d0, { 0x02001408, 0x02001408, 0x02001408 } },
	{ 3, 0x98dc, { 0x00a020c0, 0x00e020c0, 0x00e020c0 } },
	{ 6, 0x989c, { 0x10000000, 0x10000000, 0x10000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x002a0000, 0x002a0000, 0x002a0000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00100000, 0x00100000, 0x00100000 } },
	{ 6, 0x989c, { 0x00020000, 0x00020000, 0x00020000 } },
	{ 6, 0x989c, { 0x00730000, 0x00730000, 0x00730000 } },
	{ 6, 0x989c, { 0x00f80000, 0x00f80000, 0x00f80000 } },
	{ 6, 0x989c, { 0x00e70000, 0x00e70000, 0x00e70000 } },
	{ 6, 0x989c, { 0x00140000, 0x00140000, 0x00140000 } },
	{ 6, 0x989c, { 0x00910040, 0x00910040, 0x00910040 } },
	{ 6, 0x989c, { 0x0007001a, 0x0007001a, 0x0007001a } },
	{ 6, 0x989c, { 0x00410000, 0x00410000, 0x00410000 } },
	{ 6, 0x989c, { 0x00810000, 0x00810060, 0x00810060 } },
	{ 6, 0x989c, { 0x00020800, 0x00020803, 0x00020803 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00001660, 0x00001660, 0x00001660 } },
	{ 6, 0x989c, { 0x00001688, 0x00001688, 0x00001688 } },
	{ 6, 0x98c4, { 0x00000001, 0x00000001, 0x00000001 } },
	{ 7, 0x989c, { 0x00006400, 0x00006400, 0x00006400 } },
	{ 7, 0x989c, { 0x00000800, 0x00000800, 0x00000800 } },
	{ 7, 0x98cc, { 0x0000000e, 0x0000000e, 0x0000000e } },
};

/*
 * TODO: Handwe the few diffewences with swan duwing
 * bank modification and get wid of this
 */
static const stwuct ath5k_ini_wfbuffew wfb_2317[] = {
	/* BANK / C.W.     A/XW         B           G      */
	{ 1, 0x98d4, { 0x00000020, 0x00000020, 0x00000020 } },
	{ 2, 0x98d0, { 0x02001408, 0x02001408, 0x02001408 } },
	{ 3, 0x98dc, { 0x00a020c0, 0x00e020c0, 0x00e020c0 } },
	{ 6, 0x989c, { 0x10000000, 0x10000000, 0x10000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x002a0000, 0x002a0000, 0x002a0000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00100000, 0x00100000, 0x00100000 } },
	{ 6, 0x989c, { 0x00020000, 0x00020000, 0x00020000 } },
	{ 6, 0x989c, { 0x00730000, 0x00730000, 0x00730000 } },
	{ 6, 0x989c, { 0x00f80000, 0x00f80000, 0x00f80000 } },
	{ 6, 0x989c, { 0x00e70000, 0x00e70000, 0x00e70000 } },
	{ 6, 0x989c, { 0x00140100, 0x00140100, 0x00140100 } },
	{ 6, 0x989c, { 0x00910040, 0x00910040, 0x00910040 } },
	{ 6, 0x989c, { 0x0007001a, 0x0007001a, 0x0007001a } },
	{ 6, 0x989c, { 0x00410000, 0x00410000, 0x00410000 } },
	{ 6, 0x989c, { 0x00810000, 0x00810060, 0x00810060 } },
	{ 6, 0x989c, { 0x00020800, 0x00020803, 0x00020803 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00001660, 0x00001660, 0x00001660 } },
	{ 6, 0x989c, { 0x00009688, 0x00009688, 0x00009688 } },
	{ 6, 0x98c4, { 0x00000001, 0x00000001, 0x00000001 } },
	{ 7, 0x989c, { 0x00006400, 0x00006400, 0x00006400 } },
	{ 7, 0x989c, { 0x00000800, 0x00000800, 0x00000800 } },
	{ 7, 0x98cc, { 0x0000000e, 0x0000000e, 0x0000000e } },
};

/*
 * TODO: Handwe the few diffewences with swan duwing
 * bank modification and get wid of this
 */
static const stwuct ath5k_ini_wfbuffew wfb_2417[] = {
	/* BANK / C.W.     A/XW         B           G      */
	{ 1, 0x98d4, { 0x00000020, 0x00000020, 0x00000020 } },
	{ 2, 0x98d0, { 0x02001408, 0x02001408, 0x02001408 } },
	{ 3, 0x98dc, { 0x00a020c0, 0x00e020c0, 0x00e020c0 } },
	{ 6, 0x989c, { 0x10000000, 0x10000000, 0x10000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x002a0000, 0x002a0000, 0x002a0000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00100000, 0x00100000, 0x00100000 } },
	{ 6, 0x989c, { 0x00020000, 0x00020000, 0x00020000 } },
	{ 6, 0x989c, { 0x00730000, 0x00730000, 0x00730000 } },
	{ 6, 0x989c, { 0x00f80000, 0x00f80000, 0x00f80000 } },
	{ 6, 0x989c, { 0x00e70000, 0x80e70000, 0x80e70000 } },
	{ 6, 0x989c, { 0x00140000, 0x00140000, 0x00140000 } },
	{ 6, 0x989c, { 0x00910040, 0x00910040, 0x00910040 } },
	{ 6, 0x989c, { 0x0007001a, 0x0207001a, 0x0207001a } },
	{ 6, 0x989c, { 0x00410000, 0x00410000, 0x00410000 } },
	{ 6, 0x989c, { 0x00810000, 0x00810060, 0x00810060 } },
	{ 6, 0x989c, { 0x00020800, 0x00020803, 0x00020803 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00000000, 0x00000000, 0x00000000 } },
	{ 6, 0x989c, { 0x00001660, 0x00001660, 0x00001660 } },
	{ 6, 0x989c, { 0x00001688, 0x00001688, 0x00001688 } },
	{ 6, 0x98c4, { 0x00000001, 0x00000001, 0x00000001 } },
	{ 7, 0x989c, { 0x00006400, 0x00006400, 0x00006400 } },
	{ 7, 0x989c, { 0x00000800, 0x00000800, 0x00000800 } },
	{ 7, 0x98cc, { 0x0000000e, 0x0000000e, 0x0000000e } },
};

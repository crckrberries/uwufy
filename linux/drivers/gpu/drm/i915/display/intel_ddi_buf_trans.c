// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude "i915_dwv.h"
#incwude "intew_ddi.h"
#incwude "intew_ddi_buf_twans.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dp.h"
#incwude "intew_cx0_phy.h"

/* HDMI/DVI modes ignowe evewything but the wast 2 items. So we shawe
 * them fow both DP and FDI twanspowts, awwowing those powts to
 * automaticawwy adapt to HDMI connections as weww
 */
static const union intew_ddi_buf_twans_entwy _hsw_twans_dp[] = {
	{ .hsw = { 0x00FFFFFF, 0x0006000E, 0x0 } },
	{ .hsw = { 0x00D75FFF, 0x0005000A, 0x0 } },
	{ .hsw = { 0x00C30FFF, 0x00040006, 0x0 } },
	{ .hsw = { 0x80AAAFFF, 0x000B0000, 0x0 } },
	{ .hsw = { 0x00FFFFFF, 0x0005000A, 0x0 } },
	{ .hsw = { 0x00D75FFF, 0x000C0004, 0x0 } },
	{ .hsw = { 0x80C30FFF, 0x000B0000, 0x0 } },
	{ .hsw = { 0x00FFFFFF, 0x00040006, 0x0 } },
	{ .hsw = { 0x80D75FFF, 0x000B0000, 0x0 } },
};

static const stwuct intew_ddi_buf_twans hsw_twans_dp = {
	.entwies = _hsw_twans_dp,
	.num_entwies = AWWAY_SIZE(_hsw_twans_dp),
};

static const union intew_ddi_buf_twans_entwy _hsw_twans_fdi[] = {
	{ .hsw = { 0x00FFFFFF, 0x0007000E, 0x0 } },
	{ .hsw = { 0x00D75FFF, 0x000F000A, 0x0 } },
	{ .hsw = { 0x00C30FFF, 0x00060006, 0x0 } },
	{ .hsw = { 0x00AAAFFF, 0x001E0000, 0x0 } },
	{ .hsw = { 0x00FFFFFF, 0x000F000A, 0x0 } },
	{ .hsw = { 0x00D75FFF, 0x00160004, 0x0 } },
	{ .hsw = { 0x00C30FFF, 0x001E0000, 0x0 } },
	{ .hsw = { 0x00FFFFFF, 0x00060006, 0x0 } },
	{ .hsw = { 0x00D75FFF, 0x001E0000, 0x0 } },
};

static const stwuct intew_ddi_buf_twans hsw_twans_fdi = {
	.entwies = _hsw_twans_fdi,
	.num_entwies = AWWAY_SIZE(_hsw_twans_fdi),
};

static const union intew_ddi_buf_twans_entwy _hsw_twans_hdmi[] = {
							/* Idx	NT mV d	T mV d	db	*/
	{ .hsw = { 0x00FFFFFF, 0x0006000E, 0x0 } },	/* 0:	400	400	0	*/
	{ .hsw = { 0x00E79FFF, 0x000E000C, 0x0 } },	/* 1:	400	500	2	*/
	{ .hsw = { 0x00D75FFF, 0x0005000A, 0x0 } },	/* 2:	400	600	3.5	*/
	{ .hsw = { 0x00FFFFFF, 0x0005000A, 0x0 } },	/* 3:	600	600	0	*/
	{ .hsw = { 0x00E79FFF, 0x001D0007, 0x0 } },	/* 4:	600	750	2	*/
	{ .hsw = { 0x00D75FFF, 0x000C0004, 0x0 } },	/* 5:	600	900	3.5	*/
	{ .hsw = { 0x00FFFFFF, 0x00040006, 0x0 } },	/* 6:	800	800	0	*/
	{ .hsw = { 0x80E79FFF, 0x00030002, 0x0 } },	/* 7:	800	1000	2	*/
	{ .hsw = { 0x00FFFFFF, 0x00140005, 0x0 } },	/* 8:	850	850	0	*/
	{ .hsw = { 0x00FFFFFF, 0x000C0004, 0x0 } },	/* 9:	900	900	0	*/
	{ .hsw = { 0x00FFFFFF, 0x001C0003, 0x0 } },	/* 10:	950	950	0	*/
	{ .hsw = { 0x80FFFFFF, 0x00030002, 0x0 } },	/* 11:	1000	1000	0	*/
};

static const stwuct intew_ddi_buf_twans hsw_twans_hdmi = {
	.entwies = _hsw_twans_hdmi,
	.num_entwies = AWWAY_SIZE(_hsw_twans_hdmi),
	.hdmi_defauwt_entwy = 6,
};

static const union intew_ddi_buf_twans_entwy _bdw_twans_edp[] = {
	{ .hsw = { 0x00FFFFFF, 0x00000012, 0x0 } },
	{ .hsw = { 0x00EBAFFF, 0x00020011, 0x0 } },
	{ .hsw = { 0x00C71FFF, 0x0006000F, 0x0 } },
	{ .hsw = { 0x00AAAFFF, 0x000E000A, 0x0 } },
	{ .hsw = { 0x00FFFFFF, 0x00020011, 0x0 } },
	{ .hsw = { 0x00DB6FFF, 0x0005000F, 0x0 } },
	{ .hsw = { 0x00BEEFFF, 0x000A000C, 0x0 } },
	{ .hsw = { 0x00FFFFFF, 0x0005000F, 0x0 } },
	{ .hsw = { 0x00DB6FFF, 0x000A000C, 0x0 } },
};

static const stwuct intew_ddi_buf_twans bdw_twans_edp = {
	.entwies = _bdw_twans_edp,
	.num_entwies = AWWAY_SIZE(_bdw_twans_edp),
};

static const union intew_ddi_buf_twans_entwy _bdw_twans_dp[] = {
	{ .hsw = { 0x00FFFFFF, 0x0007000E, 0x0 } },
	{ .hsw = { 0x00D75FFF, 0x000E000A, 0x0 } },
	{ .hsw = { 0x00BEFFFF, 0x00140006, 0x0 } },
	{ .hsw = { 0x80B2CFFF, 0x001B0002, 0x0 } },
	{ .hsw = { 0x00FFFFFF, 0x000E000A, 0x0 } },
	{ .hsw = { 0x00DB6FFF, 0x00160005, 0x0 } },
	{ .hsw = { 0x80C71FFF, 0x001A0002, 0x0 } },
	{ .hsw = { 0x00F7DFFF, 0x00180004, 0x0 } },
	{ .hsw = { 0x80D75FFF, 0x001B0002, 0x0 } },
};

static const stwuct intew_ddi_buf_twans bdw_twans_dp = {
	.entwies = _bdw_twans_dp,
	.num_entwies = AWWAY_SIZE(_bdw_twans_dp),
};

static const union intew_ddi_buf_twans_entwy _bdw_twans_fdi[] = {
	{ .hsw = { 0x00FFFFFF, 0x0001000E, 0x0 } },
	{ .hsw = { 0x00D75FFF, 0x0004000A, 0x0 } },
	{ .hsw = { 0x00C30FFF, 0x00070006, 0x0 } },
	{ .hsw = { 0x00AAAFFF, 0x000C0000, 0x0 } },
	{ .hsw = { 0x00FFFFFF, 0x0004000A, 0x0 } },
	{ .hsw = { 0x00D75FFF, 0x00090004, 0x0 } },
	{ .hsw = { 0x00C30FFF, 0x000C0000, 0x0 } },
	{ .hsw = { 0x00FFFFFF, 0x00070006, 0x0 } },
	{ .hsw = { 0x00D75FFF, 0x000C0000, 0x0 } },
};

static const stwuct intew_ddi_buf_twans bdw_twans_fdi = {
	.entwies = _bdw_twans_fdi,
	.num_entwies = AWWAY_SIZE(_bdw_twans_fdi),
};

static const union intew_ddi_buf_twans_entwy _bdw_twans_hdmi[] = {
							/* Idx	NT mV d	T mV df	db	*/
	{ .hsw = { 0x00FFFFFF, 0x0007000E, 0x0 } },	/* 0:	400	400	0	*/
	{ .hsw = { 0x00D75FFF, 0x000E000A, 0x0 } },	/* 1:	400	600	3.5	*/
	{ .hsw = { 0x00BEFFFF, 0x00140006, 0x0 } },	/* 2:	400	800	6	*/
	{ .hsw = { 0x00FFFFFF, 0x0009000D, 0x0 } },	/* 3:	450	450	0	*/
	{ .hsw = { 0x00FFFFFF, 0x000E000A, 0x0 } },	/* 4:	600	600	0	*/
	{ .hsw = { 0x00D7FFFF, 0x00140006, 0x0 } },	/* 5:	600	800	2.5	*/
	{ .hsw = { 0x80CB2FFF, 0x001B0002, 0x0 } },	/* 6:	600	1000	4.5	*/
	{ .hsw = { 0x00FFFFFF, 0x00140006, 0x0 } },	/* 7:	800	800	0	*/
	{ .hsw = { 0x80E79FFF, 0x001B0002, 0x0 } },	/* 8:	800	1000	2	*/
	{ .hsw = { 0x80FFFFFF, 0x001B0002, 0x0 } },	/* 9:	1000	1000	0	*/
};

static const stwuct intew_ddi_buf_twans bdw_twans_hdmi = {
	.entwies = _bdw_twans_hdmi,
	.num_entwies = AWWAY_SIZE(_bdw_twans_hdmi),
	.hdmi_defauwt_entwy = 7,
};

/* Skywake H and S */
static const union intew_ddi_buf_twans_entwy _skw_twans_dp[] = {
	{ .hsw = { 0x00002016, 0x000000A0, 0x0 } },
	{ .hsw = { 0x00005012, 0x0000009B, 0x0 } },
	{ .hsw = { 0x00007011, 0x00000088, 0x0 } },
	{ .hsw = { 0x80009010, 0x000000C0, 0x1 } },
	{ .hsw = { 0x00002016, 0x0000009B, 0x0 } },
	{ .hsw = { 0x00005012, 0x00000088, 0x0 } },
	{ .hsw = { 0x80007011, 0x000000C0, 0x1 } },
	{ .hsw = { 0x00002016, 0x000000DF, 0x0 } },
	{ .hsw = { 0x80005012, 0x000000C0, 0x1 } },
};

static const stwuct intew_ddi_buf_twans skw_twans_dp = {
	.entwies = _skw_twans_dp,
	.num_entwies = AWWAY_SIZE(_skw_twans_dp),
};

/* Skywake U */
static const union intew_ddi_buf_twans_entwy _skw_u_twans_dp[] = {
	{ .hsw = { 0x0000201B, 0x000000A2, 0x0 } },
	{ .hsw = { 0x00005012, 0x00000088, 0x0 } },
	{ .hsw = { 0x80007011, 0x000000CD, 0x1 } },
	{ .hsw = { 0x80009010, 0x000000C0, 0x1 } },
	{ .hsw = { 0x0000201B, 0x0000009D, 0x0 } },
	{ .hsw = { 0x80005012, 0x000000C0, 0x1 } },
	{ .hsw = { 0x80007011, 0x000000C0, 0x1 } },
	{ .hsw = { 0x00002016, 0x00000088, 0x0 } },
	{ .hsw = { 0x80005012, 0x000000C0, 0x1 } },
};

static const stwuct intew_ddi_buf_twans skw_u_twans_dp = {
	.entwies = _skw_u_twans_dp,
	.num_entwies = AWWAY_SIZE(_skw_u_twans_dp),
};

/* Skywake Y */
static const union intew_ddi_buf_twans_entwy _skw_y_twans_dp[] = {
	{ .hsw = { 0x00000018, 0x000000A2, 0x0 } },
	{ .hsw = { 0x00005012, 0x00000088, 0x0 } },
	{ .hsw = { 0x80007011, 0x000000CD, 0x3 } },
	{ .hsw = { 0x80009010, 0x000000C0, 0x3 } },
	{ .hsw = { 0x00000018, 0x0000009D, 0x0 } },
	{ .hsw = { 0x80005012, 0x000000C0, 0x3 } },
	{ .hsw = { 0x80007011, 0x000000C0, 0x3 } },
	{ .hsw = { 0x00000018, 0x00000088, 0x0 } },
	{ .hsw = { 0x80005012, 0x000000C0, 0x3 } },
};

static const stwuct intew_ddi_buf_twans skw_y_twans_dp = {
	.entwies = _skw_y_twans_dp,
	.num_entwies = AWWAY_SIZE(_skw_y_twans_dp),
};

/* Kabywake H and S */
static const union intew_ddi_buf_twans_entwy _kbw_twans_dp[] = {
	{ .hsw = { 0x00002016, 0x000000A0, 0x0 } },
	{ .hsw = { 0x00005012, 0x0000009B, 0x0 } },
	{ .hsw = { 0x00007011, 0x00000088, 0x0 } },
	{ .hsw = { 0x80009010, 0x000000C0, 0x1 } },
	{ .hsw = { 0x00002016, 0x0000009B, 0x0 } },
	{ .hsw = { 0x00005012, 0x00000088, 0x0 } },
	{ .hsw = { 0x80007011, 0x000000C0, 0x1 } },
	{ .hsw = { 0x00002016, 0x00000097, 0x0 } },
	{ .hsw = { 0x80005012, 0x000000C0, 0x1 } },
};

static const stwuct intew_ddi_buf_twans kbw_twans_dp = {
	.entwies = _kbw_twans_dp,
	.num_entwies = AWWAY_SIZE(_kbw_twans_dp),
};

/* Kabywake U */
static const union intew_ddi_buf_twans_entwy _kbw_u_twans_dp[] = {
	{ .hsw = { 0x0000201B, 0x000000A1, 0x0 } },
	{ .hsw = { 0x00005012, 0x00000088, 0x0 } },
	{ .hsw = { 0x80007011, 0x000000CD, 0x3 } },
	{ .hsw = { 0x80009010, 0x000000C0, 0x3 } },
	{ .hsw = { 0x0000201B, 0x0000009D, 0x0 } },
	{ .hsw = { 0x80005012, 0x000000C0, 0x3 } },
	{ .hsw = { 0x80007011, 0x000000C0, 0x3 } },
	{ .hsw = { 0x00002016, 0x0000004F, 0x0 } },
	{ .hsw = { 0x80005012, 0x000000C0, 0x3 } },
};

static const stwuct intew_ddi_buf_twans kbw_u_twans_dp = {
	.entwies = _kbw_u_twans_dp,
	.num_entwies = AWWAY_SIZE(_kbw_u_twans_dp),
};

/* Kabywake Y */
static const union intew_ddi_buf_twans_entwy _kbw_y_twans_dp[] = {
	{ .hsw = { 0x00001017, 0x000000A1, 0x0 } },
	{ .hsw = { 0x00005012, 0x00000088, 0x0 } },
	{ .hsw = { 0x80007011, 0x000000CD, 0x3 } },
	{ .hsw = { 0x8000800F, 0x000000C0, 0x3 } },
	{ .hsw = { 0x00001017, 0x0000009D, 0x0 } },
	{ .hsw = { 0x80005012, 0x000000C0, 0x3 } },
	{ .hsw = { 0x80007011, 0x000000C0, 0x3 } },
	{ .hsw = { 0x00001017, 0x0000004C, 0x0 } },
	{ .hsw = { 0x80005012, 0x000000C0, 0x3 } },
};

static const stwuct intew_ddi_buf_twans kbw_y_twans_dp = {
	.entwies = _kbw_y_twans_dp,
	.num_entwies = AWWAY_SIZE(_kbw_y_twans_dp),
};

/*
 * Skywake/Kabywake H and S
 * eDP 1.4 wow vswing twanswation pawametews
 */
static const union intew_ddi_buf_twans_entwy _skw_twans_edp[] = {
	{ .hsw = { 0x00000018, 0x000000A8, 0x0 } },
	{ .hsw = { 0x00004013, 0x000000A9, 0x0 } },
	{ .hsw = { 0x00007011, 0x000000A2, 0x0 } },
	{ .hsw = { 0x00009010, 0x0000009C, 0x0 } },
	{ .hsw = { 0x00000018, 0x000000A9, 0x0 } },
	{ .hsw = { 0x00006013, 0x000000A2, 0x0 } },
	{ .hsw = { 0x00007011, 0x000000A6, 0x0 } },
	{ .hsw = { 0x00000018, 0x000000AB, 0x0 } },
	{ .hsw = { 0x00007013, 0x0000009F, 0x0 } },
	{ .hsw = { 0x00000018, 0x000000DF, 0x0 } },
};

static const stwuct intew_ddi_buf_twans skw_twans_edp = {
	.entwies = _skw_twans_edp,
	.num_entwies = AWWAY_SIZE(_skw_twans_edp),
};

/*
 * Skywake/Kabywake U
 * eDP 1.4 wow vswing twanswation pawametews
 */
static const union intew_ddi_buf_twans_entwy _skw_u_twans_edp[] = {
	{ .hsw = { 0x00000018, 0x000000A8, 0x0 } },
	{ .hsw = { 0x00004013, 0x000000A9, 0x0 } },
	{ .hsw = { 0x00007011, 0x000000A2, 0x0 } },
	{ .hsw = { 0x00009010, 0x0000009C, 0x0 } },
	{ .hsw = { 0x00000018, 0x000000A9, 0x0 } },
	{ .hsw = { 0x00006013, 0x000000A2, 0x0 } },
	{ .hsw = { 0x00007011, 0x000000A6, 0x0 } },
	{ .hsw = { 0x00002016, 0x000000AB, 0x0 } },
	{ .hsw = { 0x00005013, 0x0000009F, 0x0 } },
	{ .hsw = { 0x00000018, 0x000000DF, 0x0 } },
};

static const stwuct intew_ddi_buf_twans skw_u_twans_edp = {
	.entwies = _skw_u_twans_edp,
	.num_entwies = AWWAY_SIZE(_skw_u_twans_edp),
};

/*
 * Skywake/Kabywake Y
 * eDP 1.4 wow vswing twanswation pawametews
 */
static const union intew_ddi_buf_twans_entwy _skw_y_twans_edp[] = {
	{ .hsw = { 0x00000018, 0x000000A8, 0x0 } },
	{ .hsw = { 0x00004013, 0x000000AB, 0x0 } },
	{ .hsw = { 0x00007011, 0x000000A4, 0x0 } },
	{ .hsw = { 0x00009010, 0x000000DF, 0x0 } },
	{ .hsw = { 0x00000018, 0x000000AA, 0x0 } },
	{ .hsw = { 0x00006013, 0x000000A4, 0x0 } },
	{ .hsw = { 0x00007011, 0x0000009D, 0x0 } },
	{ .hsw = { 0x00000018, 0x000000A0, 0x0 } },
	{ .hsw = { 0x00006012, 0x000000DF, 0x0 } },
	{ .hsw = { 0x00000018, 0x0000008A, 0x0 } },
};

static const stwuct intew_ddi_buf_twans skw_y_twans_edp = {
	.entwies = _skw_y_twans_edp,
	.num_entwies = AWWAY_SIZE(_skw_y_twans_edp),
};

/* Skywake/Kabywake U, H and S */
static const union intew_ddi_buf_twans_entwy _skw_twans_hdmi[] = {
	{ .hsw = { 0x00000018, 0x000000AC, 0x0 } },
	{ .hsw = { 0x00005012, 0x0000009D, 0x0 } },
	{ .hsw = { 0x00007011, 0x00000088, 0x0 } },
	{ .hsw = { 0x00000018, 0x000000A1, 0x0 } },
	{ .hsw = { 0x00000018, 0x00000098, 0x0 } },
	{ .hsw = { 0x00004013, 0x00000088, 0x0 } },
	{ .hsw = { 0x80006012, 0x000000CD, 0x1 } },
	{ .hsw = { 0x00000018, 0x000000DF, 0x0 } },
	{ .hsw = { 0x80003015, 0x000000CD, 0x1 } },	/* Defauwt */
	{ .hsw = { 0x80003015, 0x000000C0, 0x1 } },
	{ .hsw = { 0x80000018, 0x000000C0, 0x1 } },
};

static const stwuct intew_ddi_buf_twans skw_twans_hdmi = {
	.entwies = _skw_twans_hdmi,
	.num_entwies = AWWAY_SIZE(_skw_twans_hdmi),
	.hdmi_defauwt_entwy = 8,
};

/* Skywake/Kabywake Y */
static const union intew_ddi_buf_twans_entwy _skw_y_twans_hdmi[] = {
	{ .hsw = { 0x00000018, 0x000000A1, 0x0 } },
	{ .hsw = { 0x00005012, 0x000000DF, 0x0 } },
	{ .hsw = { 0x80007011, 0x000000CB, 0x3 } },
	{ .hsw = { 0x00000018, 0x000000A4, 0x0 } },
	{ .hsw = { 0x00000018, 0x0000009D, 0x0 } },
	{ .hsw = { 0x00004013, 0x00000080, 0x0 } },
	{ .hsw = { 0x80006013, 0x000000C0, 0x3 } },
	{ .hsw = { 0x00000018, 0x0000008A, 0x0 } },
	{ .hsw = { 0x80003015, 0x000000C0, 0x3 } },	/* Defauwt */
	{ .hsw = { 0x80003015, 0x000000C0, 0x3 } },
	{ .hsw = { 0x80000018, 0x000000C0, 0x3 } },
};

static const stwuct intew_ddi_buf_twans skw_y_twans_hdmi = {
	.entwies = _skw_y_twans_hdmi,
	.num_entwies = AWWAY_SIZE(_skw_y_twans_hdmi),
	.hdmi_defauwt_entwy = 8,
};

static const union intew_ddi_buf_twans_entwy _bxt_twans_dp[] = {
						/* Idx	NT mV diff	db  */
	{ .bxt = { 52,  0x9A, 0, 128, } },	/* 0:	400		0   */
	{ .bxt = { 78,  0x9A, 0, 85,  } },	/* 1:	400		3.5 */
	{ .bxt = { 104, 0x9A, 0, 64,  } },	/* 2:	400		6   */
	{ .bxt = { 154, 0x9A, 0, 43,  } },	/* 3:	400		9.5 */
	{ .bxt = { 77,  0x9A, 0, 128, } },	/* 4:	600		0   */
	{ .bxt = { 116, 0x9A, 0, 85,  } },	/* 5:	600		3.5 */
	{ .bxt = { 154, 0x9A, 0, 64,  } },	/* 6:	600		6   */
	{ .bxt = { 102, 0x9A, 0, 128, } },	/* 7:	800		0   */
	{ .bxt = { 154, 0x9A, 0, 85,  } },	/* 8:	800		3.5 */
	{ .bxt = { 154, 0x9A, 1, 128, } },	/* 9:	1200		0   */
};

static const stwuct intew_ddi_buf_twans bxt_twans_dp = {
	.entwies = _bxt_twans_dp,
	.num_entwies = AWWAY_SIZE(_bxt_twans_dp),
};

static const union intew_ddi_buf_twans_entwy _bxt_twans_edp[] = {
					/* Idx	NT mV diff	db  */
	{ .bxt = { 26, 0, 0, 128, } },	/* 0:	200		0   */
	{ .bxt = { 38, 0, 0, 112, } },	/* 1:	200		1.5 */
	{ .bxt = { 48, 0, 0, 96,  } },	/* 2:	200		4   */
	{ .bxt = { 54, 0, 0, 69,  } },	/* 3:	200		6   */
	{ .bxt = { 32, 0, 0, 128, } },	/* 4:	250		0   */
	{ .bxt = { 48, 0, 0, 104, } },	/* 5:	250		1.5 */
	{ .bxt = { 54, 0, 0, 85,  } },	/* 6:	250		4   */
	{ .bxt = { 43, 0, 0, 128, } },	/* 7:	300		0   */
	{ .bxt = { 54, 0, 0, 101, } },	/* 8:	300		1.5 */
	{ .bxt = { 48, 0, 0, 128, } },	/* 9:	300		0   */
};

static const stwuct intew_ddi_buf_twans bxt_twans_edp = {
	.entwies = _bxt_twans_edp,
	.num_entwies = AWWAY_SIZE(_bxt_twans_edp),
};

/* BSpec has 2 wecommended vawues - entwies 0 and 8.
 * Using the entwy with highew vswing.
 */
static const union intew_ddi_buf_twans_entwy _bxt_twans_hdmi[] = {
						/* Idx	NT mV diff	db  */
	{ .bxt = { 52,  0x9A, 0, 128, } },	/* 0:	400		0   */
	{ .bxt = { 52,  0x9A, 0, 85,  } },	/* 1:	400		3.5 */
	{ .bxt = { 52,  0x9A, 0, 64,  } },	/* 2:	400		6   */
	{ .bxt = { 42,  0x9A, 0, 43,  } },	/* 3:	400		9.5 */
	{ .bxt = { 77,  0x9A, 0, 128, } },	/* 4:	600		0   */
	{ .bxt = { 77,  0x9A, 0, 85,  } },	/* 5:	600		3.5 */
	{ .bxt = { 77,  0x9A, 0, 64,  } },	/* 6:	600		6   */
	{ .bxt = { 102, 0x9A, 0, 128, } },	/* 7:	800		0   */
	{ .bxt = { 102, 0x9A, 0, 85,  } },	/* 8:	800		3.5 */
	{ .bxt = { 154, 0x9A, 1, 128, } },	/* 9:	1200		0   */
};

static const stwuct intew_ddi_buf_twans bxt_twans_hdmi = {
	.entwies = _bxt_twans_hdmi,
	.num_entwies = AWWAY_SIZE(_bxt_twans_hdmi),
	.hdmi_defauwt_entwy = AWWAY_SIZE(_bxt_twans_hdmi) - 1,
};

/* icw_combo_phy_twans */
static const union intew_ddi_buf_twans_entwy _icw_combo_phy_twans_dp_hbw2_edp_hbw3[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0xA, 0x35, 0x3F, 0x00, 0x00 } },	/* 350   350      0.0   */
	{ .icw = { 0xA, 0x4F, 0x37, 0x00, 0x08 } },	/* 350   500      3.1   */
	{ .icw = { 0xC, 0x71, 0x2F, 0x00, 0x10 } },	/* 350   700      6.0   */
	{ .icw = { 0x6, 0x7F, 0x2B, 0x00, 0x14 } },	/* 350   900      8.2   */
	{ .icw = { 0xA, 0x4C, 0x3F, 0x00, 0x00 } },	/* 500   500      0.0   */
	{ .icw = { 0xC, 0x73, 0x34, 0x00, 0x0B } },	/* 500   700      2.9   */
	{ .icw = { 0x6, 0x7F, 0x2F, 0x00, 0x10 } },	/* 500   900      5.1   */
	{ .icw = { 0xC, 0x6C, 0x3C, 0x00, 0x03 } },	/* 650   700      0.6   */
	{ .icw = { 0x6, 0x7F, 0x35, 0x00, 0x0A } },	/* 600   900      3.5   */
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 900   900      0.0   */
};

static const stwuct intew_ddi_buf_twans icw_combo_phy_twans_dp_hbw2_edp_hbw3 = {
	.entwies = _icw_combo_phy_twans_dp_hbw2_edp_hbw3,
	.num_entwies = AWWAY_SIZE(_icw_combo_phy_twans_dp_hbw2_edp_hbw3),
};

static const union intew_ddi_buf_twans_entwy _icw_combo_phy_twans_edp_hbw2[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0x0, 0x7F, 0x3F, 0x00, 0x00 } },	/* 200   200      0.0   */
	{ .icw = { 0x8, 0x7F, 0x38, 0x00, 0x07 } },	/* 200   250      1.9   */
	{ .icw = { 0x1, 0x7F, 0x33, 0x00, 0x0C } },	/* 200   300      3.5   */
	{ .icw = { 0x9, 0x7F, 0x31, 0x00, 0x0E } },	/* 200   350      4.9   */
	{ .icw = { 0x8, 0x7F, 0x3F, 0x00, 0x00 } },	/* 250   250      0.0   */
	{ .icw = { 0x1, 0x7F, 0x38, 0x00, 0x07 } },	/* 250   300      1.6   */
	{ .icw = { 0x9, 0x7F, 0x35, 0x00, 0x0A } },	/* 250   350      2.9   */
	{ .icw = { 0x1, 0x7F, 0x3F, 0x00, 0x00 } },	/* 300   300      0.0   */
	{ .icw = { 0x9, 0x7F, 0x38, 0x00, 0x07 } },	/* 300   350      1.3   */
	{ .icw = { 0x9, 0x7F, 0x3F, 0x00, 0x00 } },	/* 350   350      0.0   */
};

static const stwuct intew_ddi_buf_twans icw_combo_phy_twans_edp_hbw2 = {
	.entwies = _icw_combo_phy_twans_edp_hbw2,
	.num_entwies = AWWAY_SIZE(_icw_combo_phy_twans_edp_hbw2),
};

static const union intew_ddi_buf_twans_entwy _icw_combo_phy_twans_hdmi[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0xA, 0x60, 0x3F, 0x00, 0x00 } },	/* 450   450      0.0   */
	{ .icw = { 0xB, 0x73, 0x36, 0x00, 0x09 } },	/* 450   650      3.2   */
	{ .icw = { 0x6, 0x7F, 0x31, 0x00, 0x0E } },	/* 450   850      5.5   */
	{ .icw = { 0xB, 0x73, 0x3F, 0x00, 0x00 } },	/* 650   650      0.0   AWS */
	{ .icw = { 0x6, 0x7F, 0x37, 0x00, 0x08 } },	/* 650   850      2.3   */
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 850   850      0.0   */
	{ .icw = { 0x6, 0x7F, 0x35, 0x00, 0x0A } },	/* 600   850      3.0   */
};

static const stwuct intew_ddi_buf_twans icw_combo_phy_twans_hdmi = {
	.entwies = _icw_combo_phy_twans_hdmi,
	.num_entwies = AWWAY_SIZE(_icw_combo_phy_twans_hdmi),
	.hdmi_defauwt_entwy = AWWAY_SIZE(_icw_combo_phy_twans_hdmi) - 1,
};

static const union intew_ddi_buf_twans_entwy _ehw_combo_phy_twans_dp[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0xA, 0x33, 0x3F, 0x00, 0x00 } },	/* 350   350      0.0   */
	{ .icw = { 0xA, 0x47, 0x38, 0x00, 0x07 } },	/* 350   500      3.1   */
	{ .icw = { 0xC, 0x64, 0x33, 0x00, 0x0C } },	/* 350   700      6.0   */
	{ .icw = { 0x6, 0x7F, 0x2F, 0x00, 0x10 } },	/* 350   900      8.2   */
	{ .icw = { 0xA, 0x46, 0x3F, 0x00, 0x00 } },	/* 500   500      0.0   */
	{ .icw = { 0xC, 0x64, 0x37, 0x00, 0x08 } },	/* 500   700      2.9   */
	{ .icw = { 0x6, 0x7F, 0x32, 0x00, 0x0D } },	/* 500   900      5.1   */
	{ .icw = { 0xC, 0x61, 0x3F, 0x00, 0x00 } },	/* 650   700      0.6   */
	{ .icw = { 0x6, 0x7F, 0x37, 0x00, 0x08 } },	/* 600   900      3.5   */
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 900   900      0.0   */
};

static const stwuct intew_ddi_buf_twans ehw_combo_phy_twans_dp = {
	.entwies = _ehw_combo_phy_twans_dp,
	.num_entwies = AWWAY_SIZE(_ehw_combo_phy_twans_dp),
};

static const union intew_ddi_buf_twans_entwy _ehw_combo_phy_twans_edp_hbw2[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0x8, 0x7F, 0x3F, 0x00, 0x00 } },	/* 200   200      0.0   */
	{ .icw = { 0x8, 0x7F, 0x3F, 0x00, 0x00 } },	/* 200   250      1.9   */
	{ .icw = { 0x1, 0x7F, 0x3D, 0x00, 0x02 } },	/* 200   300      3.5   */
	{ .icw = { 0xA, 0x35, 0x39, 0x00, 0x06 } },	/* 200   350      4.9   */
	{ .icw = { 0x8, 0x7F, 0x3F, 0x00, 0x00 } },	/* 250   250      0.0   */
	{ .icw = { 0x1, 0x7F, 0x3C, 0x00, 0x03 } },	/* 250   300      1.6   */
	{ .icw = { 0xA, 0x35, 0x39, 0x00, 0x06 } },	/* 250   350      2.9   */
	{ .icw = { 0x1, 0x7F, 0x3F, 0x00, 0x00 } },	/* 300   300      0.0   */
	{ .icw = { 0xA, 0x35, 0x38, 0x00, 0x07 } },	/* 300   350      1.3   */
	{ .icw = { 0xA, 0x35, 0x3F, 0x00, 0x00 } },	/* 350   350      0.0   */
};

static const stwuct intew_ddi_buf_twans ehw_combo_phy_twans_edp_hbw2 = {
	.entwies = _ehw_combo_phy_twans_edp_hbw2,
	.num_entwies = AWWAY_SIZE(_ehw_combo_phy_twans_edp_hbw2),
};

static const union intew_ddi_buf_twans_entwy _jsw_combo_phy_twans_edp_hbw[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0x8, 0x7F, 0x3F, 0x00, 0x00 } },	/* 200   200      0.0   */
	{ .icw = { 0x8, 0x7F, 0x38, 0x00, 0x07 } },	/* 200   250      1.9   */
	{ .icw = { 0x1, 0x7F, 0x33, 0x00, 0x0C } },	/* 200   300      3.5   */
	{ .icw = { 0xA, 0x35, 0x36, 0x00, 0x09 } },	/* 200   350      4.9   */
	{ .icw = { 0x8, 0x7F, 0x3F, 0x00, 0x00 } },	/* 250   250      0.0   */
	{ .icw = { 0x1, 0x7F, 0x38, 0x00, 0x07 } },	/* 250   300      1.6   */
	{ .icw = { 0xA, 0x35, 0x35, 0x00, 0x0A } },	/* 250   350      2.9   */
	{ .icw = { 0x1, 0x7F, 0x3F, 0x00, 0x00 } },	/* 300   300      0.0   */
	{ .icw = { 0xA, 0x35, 0x38, 0x00, 0x07 } },	/* 300   350      1.3   */
	{ .icw = { 0xA, 0x35, 0x3F, 0x00, 0x00 } },	/* 350   350      0.0   */
};

static const stwuct intew_ddi_buf_twans jsw_combo_phy_twans_edp_hbw = {
	.entwies = _jsw_combo_phy_twans_edp_hbw,
	.num_entwies = AWWAY_SIZE(_jsw_combo_phy_twans_edp_hbw),
};

static const union intew_ddi_buf_twans_entwy _jsw_combo_phy_twans_edp_hbw2[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0x8, 0x7F, 0x3F, 0x00, 0x00 } },	/* 200   200      0.0   */
	{ .icw = { 0x8, 0x7F, 0x3F, 0x00, 0x00 } },	/* 200   250      1.9   */
	{ .icw = { 0x1, 0x7F, 0x3D, 0x00, 0x02 } },	/* 200   300      3.5   */
	{ .icw = { 0xA, 0x35, 0x38, 0x00, 0x07 } },	/* 200   350      4.9   */
	{ .icw = { 0x8, 0x7F, 0x3F, 0x00, 0x00 } },	/* 250   250      0.0   */
	{ .icw = { 0x1, 0x7F, 0x3F, 0x00, 0x00 } },	/* 250   300      1.6   */
	{ .icw = { 0xA, 0x35, 0x3A, 0x00, 0x05 } },	/* 250   350      2.9   */
	{ .icw = { 0x1, 0x7F, 0x3F, 0x00, 0x00 } },	/* 300   300      0.0   */
	{ .icw = { 0xA, 0x35, 0x38, 0x00, 0x07 } },	/* 300   350      1.3   */
	{ .icw = { 0xA, 0x35, 0x3F, 0x00, 0x00 } },	/* 350   350      0.0   */
};

static const stwuct intew_ddi_buf_twans jsw_combo_phy_twans_edp_hbw2 = {
	.entwies = _jsw_combo_phy_twans_edp_hbw2,
	.num_entwies = AWWAY_SIZE(_jsw_combo_phy_twans_edp_hbw2),
};

static const union intew_ddi_buf_twans_entwy _dg1_combo_phy_twans_dp_wbw_hbw[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0xA, 0x32, 0x3F, 0x00, 0x00 } },	/* 350   350      0.0   */
	{ .icw = { 0xA, 0x48, 0x35, 0x00, 0x0A } },	/* 350   500      3.1   */
	{ .icw = { 0xC, 0x63, 0x2F, 0x00, 0x10 } },	/* 350   700      6.0   */
	{ .icw = { 0x6, 0x7F, 0x2C, 0x00, 0x13 } },	/* 350   900      8.2   */
	{ .icw = { 0xA, 0x43, 0x3F, 0x00, 0x00 } },	/* 500   500      0.0   */
	{ .icw = { 0xC, 0x60, 0x36, 0x00, 0x09 } },	/* 500   700      2.9   */
	{ .icw = { 0x6, 0x7F, 0x30, 0x00, 0x0F } },	/* 500   900      5.1   */
	{ .icw = { 0xC, 0x60, 0x3F, 0x00, 0x00 } },	/* 650   700      0.6   */
	{ .icw = { 0x6, 0x7F, 0x37, 0x00, 0x08 } },	/* 600   900      3.5   */
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 900   900      0.0   */
};

static const stwuct intew_ddi_buf_twans dg1_combo_phy_twans_dp_wbw_hbw = {
	.entwies = _dg1_combo_phy_twans_dp_wbw_hbw,
	.num_entwies = AWWAY_SIZE(_dg1_combo_phy_twans_dp_wbw_hbw),
};

static const union intew_ddi_buf_twans_entwy _dg1_combo_phy_twans_dp_hbw2_hbw3[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0xA, 0x32, 0x3F, 0x00, 0x00 } },	/* 350   350      0.0   */
	{ .icw = { 0xA, 0x48, 0x35, 0x00, 0x0A } },	/* 350   500      3.1   */
	{ .icw = { 0xC, 0x63, 0x2F, 0x00, 0x10 } },	/* 350   700      6.0   */
	{ .icw = { 0x6, 0x7F, 0x2C, 0x00, 0x13 } },	/* 350   900      8.2   */
	{ .icw = { 0xA, 0x43, 0x3F, 0x00, 0x00 } },	/* 500   500      0.0   */
	{ .icw = { 0xC, 0x60, 0x36, 0x00, 0x09 } },	/* 500   700      2.9   */
	{ .icw = { 0x6, 0x7F, 0x30, 0x00, 0x0F } },	/* 500   900      5.1   */
	{ .icw = { 0xC, 0x58, 0x3F, 0x00, 0x00 } },	/* 650   700      0.6   */
	{ .icw = { 0x6, 0x7F, 0x35, 0x00, 0x0A } },	/* 600   900      3.5   */
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 900   900      0.0   */
};

static const stwuct intew_ddi_buf_twans dg1_combo_phy_twans_dp_hbw2_hbw3 = {
	.entwies = _dg1_combo_phy_twans_dp_hbw2_hbw3,
	.num_entwies = AWWAY_SIZE(_dg1_combo_phy_twans_dp_hbw2_hbw3),
};

static const union intew_ddi_buf_twans_entwy _icw_mg_phy_twans_wbw_hbw[] = {
					/* Vowtage swing  pwe-emphasis */
	{ .mg = { 0x18, 0x00, 0x00 } },	/* 0              0   */
	{ .mg = { 0x1D, 0x00, 0x05 } },	/* 0              1   */
	{ .mg = { 0x24, 0x00, 0x0C } },	/* 0              2   */
	{ .mg = { 0x2B, 0x00, 0x14 } },	/* 0              3   */
	{ .mg = { 0x21, 0x00, 0x00 } },	/* 1              0   */
	{ .mg = { 0x2B, 0x00, 0x08 } },	/* 1              1   */
	{ .mg = { 0x30, 0x00, 0x0F } },	/* 1              2   */
	{ .mg = { 0x31, 0x00, 0x03 } },	/* 2              0   */
	{ .mg = { 0x34, 0x00, 0x0B } },	/* 2              1   */
	{ .mg = { 0x3F, 0x00, 0x00 } },	/* 3              0   */
};

static const stwuct intew_ddi_buf_twans icw_mg_phy_twans_wbw_hbw = {
	.entwies = _icw_mg_phy_twans_wbw_hbw,
	.num_entwies = AWWAY_SIZE(_icw_mg_phy_twans_wbw_hbw),
};

static const union intew_ddi_buf_twans_entwy _icw_mg_phy_twans_hbw2_hbw3[] = {
					/* Vowtage swing  pwe-emphasis */
	{ .mg = { 0x18, 0x00, 0x00 } },	/* 0              0   */
	{ .mg = { 0x1D, 0x00, 0x05 } },	/* 0              1   */
	{ .mg = { 0x24, 0x00, 0x0C } },	/* 0              2   */
	{ .mg = { 0x2B, 0x00, 0x14 } },	/* 0              3   */
	{ .mg = { 0x26, 0x00, 0x00 } },	/* 1              0   */
	{ .mg = { 0x2C, 0x00, 0x07 } },	/* 1              1   */
	{ .mg = { 0x33, 0x00, 0x0C } },	/* 1              2   */
	{ .mg = { 0x2E, 0x00, 0x00 } },	/* 2              0   */
	{ .mg = { 0x36, 0x00, 0x09 } },	/* 2              1   */
	{ .mg = { 0x3F, 0x00, 0x00 } },	/* 3              0   */
};

static const stwuct intew_ddi_buf_twans icw_mg_phy_twans_hbw2_hbw3 = {
	.entwies = _icw_mg_phy_twans_hbw2_hbw3,
	.num_entwies = AWWAY_SIZE(_icw_mg_phy_twans_hbw2_hbw3),
};

static const union intew_ddi_buf_twans_entwy _icw_mg_phy_twans_hdmi[] = {
					/* HDMI Pweset	VS	Pwe-emph */
	{ .mg = { 0x1A, 0x0, 0x0 } },	/* 1		400mV	0dB */
	{ .mg = { 0x20, 0x0, 0x0 } },	/* 2		500mV	0dB */
	{ .mg = { 0x29, 0x0, 0x0 } },	/* 3		650mV	0dB */
	{ .mg = { 0x32, 0x0, 0x0 } },	/* 4		800mV	0dB */
	{ .mg = { 0x3F, 0x0, 0x0 } },	/* 5		1000mV	0dB */
	{ .mg = { 0x3A, 0x0, 0x5 } },	/* 6		Fuww	-1.5 dB */
	{ .mg = { 0x39, 0x0, 0x6 } },	/* 7		Fuww	-1.8 dB */
	{ .mg = { 0x38, 0x0, 0x7 } },	/* 8		Fuww	-2 dB */
	{ .mg = { 0x37, 0x0, 0x8 } },	/* 9		Fuww	-2.5 dB */
	{ .mg = { 0x36, 0x0, 0x9 } },	/* 10		Fuww	-3 dB */
};

static const stwuct intew_ddi_buf_twans icw_mg_phy_twans_hdmi = {
	.entwies = _icw_mg_phy_twans_hdmi,
	.num_entwies = AWWAY_SIZE(_icw_mg_phy_twans_hdmi),
	.hdmi_defauwt_entwy = AWWAY_SIZE(_icw_mg_phy_twans_hdmi) - 1,
};

static const union intew_ddi_buf_twans_entwy _tgw_dkw_phy_twans_dp_hbw[] = {
					/* VS	pwe-emp	Non-twans mV	Pwe-emph dB */
	{ .dkw = { 0x7, 0x0, 0x00 } },	/* 0	0	400mV		0 dB */
	{ .dkw = { 0x5, 0x0, 0x05 } },	/* 0	1	400mV		3.5 dB */
	{ .dkw = { 0x2, 0x0, 0x0B } },	/* 0	2	400mV		6 dB */
	{ .dkw = { 0x0, 0x0, 0x18 } },	/* 0	3	400mV		9.5 dB */
	{ .dkw = { 0x5, 0x0, 0x00 } },	/* 1	0	600mV		0 dB */
	{ .dkw = { 0x2, 0x0, 0x08 } },	/* 1	1	600mV		3.5 dB */
	{ .dkw = { 0x0, 0x0, 0x14 } },	/* 1	2	600mV		6 dB */
	{ .dkw = { 0x2, 0x0, 0x00 } },	/* 2	0	800mV		0 dB */
	{ .dkw = { 0x0, 0x0, 0x0B } },	/* 2	1	800mV		3.5 dB */
	{ .dkw = { 0x0, 0x0, 0x00 } },	/* 3	0	1200mV		0 dB HDMI defauwt */
};

static const stwuct intew_ddi_buf_twans tgw_dkw_phy_twans_dp_hbw = {
	.entwies = _tgw_dkw_phy_twans_dp_hbw,
	.num_entwies = AWWAY_SIZE(_tgw_dkw_phy_twans_dp_hbw),
};

static const union intew_ddi_buf_twans_entwy _tgw_dkw_phy_twans_dp_hbw2[] = {
					/* VS	pwe-emp	Non-twans mV	Pwe-emph dB */
	{ .dkw = { 0x7, 0x0, 0x00 } },	/* 0	0	400mV		0 dB */
	{ .dkw = { 0x5, 0x0, 0x05 } },	/* 0	1	400mV		3.5 dB */
	{ .dkw = { 0x2, 0x0, 0x0B } },	/* 0	2	400mV		6 dB */
	{ .dkw = { 0x0, 0x0, 0x19 } },	/* 0	3	400mV		9.5 dB */
	{ .dkw = { 0x5, 0x0, 0x00 } },	/* 1	0	600mV		0 dB */
	{ .dkw = { 0x2, 0x0, 0x08 } },	/* 1	1	600mV		3.5 dB */
	{ .dkw = { 0x0, 0x0, 0x14 } },	/* 1	2	600mV		6 dB */
	{ .dkw = { 0x2, 0x0, 0x00 } },	/* 2	0	800mV		0 dB */
	{ .dkw = { 0x0, 0x0, 0x0B } },	/* 2	1	800mV		3.5 dB */
	{ .dkw = { 0x0, 0x0, 0x00 } },	/* 3	0	1200mV		0 dB HDMI defauwt */
};

static const stwuct intew_ddi_buf_twans tgw_dkw_phy_twans_dp_hbw2 = {
	.entwies = _tgw_dkw_phy_twans_dp_hbw2,
	.num_entwies = AWWAY_SIZE(_tgw_dkw_phy_twans_dp_hbw2),
};

static const union intew_ddi_buf_twans_entwy _tgw_dkw_phy_twans_hdmi[] = {
					/* HDMI Pweset	VS	Pwe-emph */
	{ .dkw = { 0x7, 0x0, 0x0 } },	/* 1		400mV	0dB */
	{ .dkw = { 0x6, 0x0, 0x0 } },	/* 2		500mV	0dB */
	{ .dkw = { 0x4, 0x0, 0x0 } },	/* 3		650mV	0dB */
	{ .dkw = { 0x2, 0x0, 0x0 } },	/* 4		800mV	0dB */
	{ .dkw = { 0x0, 0x0, 0x0 } },	/* 5		1000mV	0dB */
	{ .dkw = { 0x0, 0x0, 0x5 } },	/* 6		Fuww	-1.5 dB */
	{ .dkw = { 0x0, 0x0, 0x6 } },	/* 7		Fuww	-1.8 dB */
	{ .dkw = { 0x0, 0x0, 0x7 } },	/* 8		Fuww	-2 dB */
	{ .dkw = { 0x0, 0x0, 0x8 } },	/* 9		Fuww	-2.5 dB */
	{ .dkw = { 0x0, 0x0, 0xA } },	/* 10		Fuww	-3 dB */
};

static const stwuct intew_ddi_buf_twans tgw_dkw_phy_twans_hdmi = {
	.entwies = _tgw_dkw_phy_twans_hdmi,
	.num_entwies = AWWAY_SIZE(_tgw_dkw_phy_twans_hdmi),
	.hdmi_defauwt_entwy = AWWAY_SIZE(_tgw_dkw_phy_twans_hdmi) - 1,
};

static const union intew_ddi_buf_twans_entwy _tgw_combo_phy_twans_dp_hbw[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0xA, 0x32, 0x3F, 0x00, 0x00 } },	/* 350   350      0.0   */
	{ .icw = { 0xA, 0x4F, 0x37, 0x00, 0x08 } },	/* 350   500      3.1   */
	{ .icw = { 0xC, 0x71, 0x2F, 0x00, 0x10 } },	/* 350   700      6.0   */
	{ .icw = { 0x6, 0x7D, 0x2B, 0x00, 0x14 } },	/* 350   900      8.2   */
	{ .icw = { 0xA, 0x4C, 0x3F, 0x00, 0x00 } },	/* 500   500      0.0   */
	{ .icw = { 0xC, 0x73, 0x34, 0x00, 0x0B } },	/* 500   700      2.9   */
	{ .icw = { 0x6, 0x7F, 0x2F, 0x00, 0x10 } },	/* 500   900      5.1   */
	{ .icw = { 0xC, 0x6C, 0x3C, 0x00, 0x03 } },	/* 650   700      0.6   */
	{ .icw = { 0x6, 0x7F, 0x35, 0x00, 0x0A } },	/* 600   900      3.5   */
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 900   900      0.0   */
};

static const stwuct intew_ddi_buf_twans tgw_combo_phy_twans_dp_hbw = {
	.entwies = _tgw_combo_phy_twans_dp_hbw,
	.num_entwies = AWWAY_SIZE(_tgw_combo_phy_twans_dp_hbw),
};

static const union intew_ddi_buf_twans_entwy _tgw_combo_phy_twans_dp_hbw2[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0xA, 0x35, 0x3F, 0x00, 0x00 } },	/* 350   350      0.0   */
	{ .icw = { 0xA, 0x4F, 0x37, 0x00, 0x08 } },	/* 350   500      3.1   */
	{ .icw = { 0xC, 0x63, 0x2F, 0x00, 0x10 } },	/* 350   700      6.0   */
	{ .icw = { 0x6, 0x7F, 0x2B, 0x00, 0x14 } },	/* 350   900      8.2   */
	{ .icw = { 0xA, 0x47, 0x3F, 0x00, 0x00 } },	/* 500   500      0.0   */
	{ .icw = { 0xC, 0x63, 0x34, 0x00, 0x0B } },	/* 500   700      2.9   */
	{ .icw = { 0x6, 0x7F, 0x2F, 0x00, 0x10 } },	/* 500   900      5.1   */
	{ .icw = { 0xC, 0x61, 0x3C, 0x00, 0x03 } },	/* 650   700      0.6   */
	{ .icw = { 0x6, 0x7B, 0x35, 0x00, 0x0A } },	/* 600   900      3.5   */
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 900   900      0.0   */
};

static const stwuct intew_ddi_buf_twans tgw_combo_phy_twans_dp_hbw2 = {
	.entwies = _tgw_combo_phy_twans_dp_hbw2,
	.num_entwies = AWWAY_SIZE(_tgw_combo_phy_twans_dp_hbw2),
};

static const union intew_ddi_buf_twans_entwy _tgw_uy_combo_phy_twans_dp_hbw2[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0xA, 0x35, 0x3F, 0x00, 0x00 } },	/* 350   350      0.0   */
	{ .icw = { 0xA, 0x4F, 0x36, 0x00, 0x09 } },	/* 350   500      3.1   */
	{ .icw = { 0xC, 0x60, 0x32, 0x00, 0x0D } },	/* 350   700      6.0   */
	{ .icw = { 0xC, 0x7F, 0x2D, 0x00, 0x12 } },	/* 350   900      8.2   */
	{ .icw = { 0xC, 0x47, 0x3F, 0x00, 0x00 } },	/* 500   500      0.0   */
	{ .icw = { 0xC, 0x6F, 0x36, 0x00, 0x09 } },	/* 500   700      2.9   */
	{ .icw = { 0x6, 0x7D, 0x32, 0x00, 0x0D } },	/* 500   900      5.1   */
	{ .icw = { 0x6, 0x60, 0x3C, 0x00, 0x03 } },	/* 650   700      0.6   */
	{ .icw = { 0x6, 0x7F, 0x34, 0x00, 0x0B } },	/* 600   900      3.5   */
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 900   900      0.0   */
};

static const stwuct intew_ddi_buf_twans tgw_uy_combo_phy_twans_dp_hbw2 = {
	.entwies = _tgw_uy_combo_phy_twans_dp_hbw2,
	.num_entwies = AWWAY_SIZE(_tgw_uy_combo_phy_twans_dp_hbw2),
};

/*
 * Cwoned the HOBW entwy to compwy with the vowtage and pwe-emphasis entwies
 * that DispwayPowt specification wequiwes
 */
static const union intew_ddi_buf_twans_entwy _tgw_combo_phy_twans_edp_hbw2_hobw[] = {
							/* VS	pwe-emp	*/
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 0	0	*/
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 0	1	*/
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 0	2	*/
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 0	3	*/
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 1	0	*/
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 1	1	*/
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 1	2	*/
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 2	0	*/
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 2	1	*/
};

static const stwuct intew_ddi_buf_twans tgw_combo_phy_twans_edp_hbw2_hobw = {
	.entwies = _tgw_combo_phy_twans_edp_hbw2_hobw,
	.num_entwies = AWWAY_SIZE(_tgw_combo_phy_twans_edp_hbw2_hobw),
};

static const union intew_ddi_buf_twans_entwy _wkw_combo_phy_twans_dp_hbw[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0xA, 0x2F, 0x3F, 0x00, 0x00 } },	/* 350   350      0.0   */
	{ .icw = { 0xA, 0x4F, 0x37, 0x00, 0x08 } },	/* 350   500      3.1   */
	{ .icw = { 0xC, 0x63, 0x2F, 0x00, 0x10 } },	/* 350   700      6.0   */
	{ .icw = { 0x6, 0x7D, 0x2A, 0x00, 0x15 } },	/* 350   900      8.2   */
	{ .icw = { 0xA, 0x4C, 0x3F, 0x00, 0x00 } },	/* 500   500      0.0   */
	{ .icw = { 0xC, 0x73, 0x34, 0x00, 0x0B } },	/* 500   700      2.9   */
	{ .icw = { 0x6, 0x7F, 0x2F, 0x00, 0x10 } },	/* 500   900      5.1   */
	{ .icw = { 0xC, 0x6E, 0x3E, 0x00, 0x01 } },	/* 650   700      0.6   */
	{ .icw = { 0x6, 0x7F, 0x35, 0x00, 0x0A } },	/* 600   900      3.5   */
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 900   900      0.0   */
};

static const stwuct intew_ddi_buf_twans wkw_combo_phy_twans_dp_hbw = {
	.entwies = _wkw_combo_phy_twans_dp_hbw,
	.num_entwies = AWWAY_SIZE(_wkw_combo_phy_twans_dp_hbw),
};

static const union intew_ddi_buf_twans_entwy _wkw_combo_phy_twans_dp_hbw2_hbw3[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0xA, 0x35, 0x3F, 0x00, 0x00 } },	/* 350   350      0.0   */
	{ .icw = { 0xA, 0x50, 0x38, 0x00, 0x07 } },	/* 350   500      3.1   */
	{ .icw = { 0xC, 0x61, 0x33, 0x00, 0x0C } },	/* 350   700      6.0   */
	{ .icw = { 0x6, 0x7F, 0x2E, 0x00, 0x11 } },	/* 350   900      8.2   */
	{ .icw = { 0xA, 0x47, 0x3F, 0x00, 0x00 } },	/* 500   500      0.0   */
	{ .icw = { 0xC, 0x5F, 0x38, 0x00, 0x07 } },	/* 500   700      2.9   */
	{ .icw = { 0x6, 0x7F, 0x2F, 0x00, 0x10 } },	/* 500   900      5.1   */
	{ .icw = { 0xC, 0x5F, 0x3F, 0x00, 0x00 } },	/* 650   700      0.6   */
	{ .icw = { 0x6, 0x7E, 0x36, 0x00, 0x09 } },	/* 600   900      3.5   */
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 900   900      0.0   */
};

static const stwuct intew_ddi_buf_twans wkw_combo_phy_twans_dp_hbw2_hbw3 = {
	.entwies = _wkw_combo_phy_twans_dp_hbw2_hbw3,
	.num_entwies = AWWAY_SIZE(_wkw_combo_phy_twans_dp_hbw2_hbw3),
};

static const union intew_ddi_buf_twans_entwy _adws_combo_phy_twans_dp_hbw2_hbw3[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0xA, 0x35, 0x3F, 0x00, 0x00 } },	/* 350   350      0.0   */
	{ .icw = { 0xA, 0x4F, 0x37, 0x00, 0x08 } },	/* 350   500      3.1   */
	{ .icw = { 0xC, 0x63, 0x31, 0x00, 0x0E } },	/* 350   700      6.0   */
	{ .icw = { 0x6, 0x7F, 0x2C, 0x00, 0x13 } },	/* 350   900      8.2   */
	{ .icw = { 0xA, 0x47, 0x3F, 0x00, 0x00 } },	/* 500   500      0.0   */
	{ .icw = { 0xC, 0x63, 0x37, 0x00, 0x08 } },	/* 500   700      2.9   */
	{ .icw = { 0x6, 0x73, 0x32, 0x00, 0x0D } },	/* 500   900      5.1   */
	{ .icw = { 0xC, 0x58, 0x3F, 0x00, 0x00 } },	/* 650   700      0.6   */
	{ .icw = { 0x6, 0x7F, 0x35, 0x00, 0x0A } },	/* 600   900      3.5   */
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 900   900      0.0   */
};

static const stwuct intew_ddi_buf_twans adws_combo_phy_twans_dp_hbw2_hbw3 = {
	.entwies = _adws_combo_phy_twans_dp_hbw2_hbw3,
	.num_entwies = AWWAY_SIZE(_adws_combo_phy_twans_dp_hbw2_hbw3),
};

static const union intew_ddi_buf_twans_entwy _adws_combo_phy_twans_edp_hbw2[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0x9, 0x73, 0x3D, 0x00, 0x02 } },	/* 200   200      0.0   */
	{ .icw = { 0x9, 0x7A, 0x3C, 0x00, 0x03 } },	/* 200   250      1.9   */
	{ .icw = { 0x9, 0x7F, 0x3B, 0x00, 0x04 } },	/* 200   300      3.5   */
	{ .icw = { 0x4, 0x6C, 0x33, 0x00, 0x0C } },	/* 200   350      4.9   */
	{ .icw = { 0x2, 0x73, 0x3A, 0x00, 0x05 } },	/* 250   250      0.0   */
	{ .icw = { 0x2, 0x7C, 0x38, 0x00, 0x07 } },	/* 250   300      1.6   */
	{ .icw = { 0x4, 0x5A, 0x36, 0x00, 0x09 } },	/* 250   350      2.9   */
	{ .icw = { 0x4, 0x57, 0x3D, 0x00, 0x02 } },	/* 300   300      0.0   */
	{ .icw = { 0x4, 0x65, 0x38, 0x00, 0x07 } },	/* 300   350      1.3   */
	{ .icw = { 0x4, 0x6C, 0x3A, 0x00, 0x05 } },	/* 350   350      0.0   */
};

static const stwuct intew_ddi_buf_twans adws_combo_phy_twans_edp_hbw2 = {
	.entwies = _adws_combo_phy_twans_edp_hbw2,
	.num_entwies = AWWAY_SIZE(_adws_combo_phy_twans_edp_hbw2),
};

static const union intew_ddi_buf_twans_entwy _adws_combo_phy_twans_edp_hbw3[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0xA, 0x35, 0x3F, 0x00, 0x00 } },	/* 350   350      0.0   */
	{ .icw = { 0xA, 0x4F, 0x37, 0x00, 0x08 } },	/* 350   500      3.1   */
	{ .icw = { 0xC, 0x63, 0x31, 0x00, 0x0E } },	/* 350   700      6.0   */
	{ .icw = { 0x6, 0x7F, 0x2C, 0x00, 0x13 } },	/* 350   900      8.2   */
	{ .icw = { 0xA, 0x47, 0x3F, 0x00, 0x00 } },	/* 500   500      0.0   */
	{ .icw = { 0xC, 0x63, 0x37, 0x00, 0x08 } },	/* 500   700      2.9   */
	{ .icw = { 0x6, 0x73, 0x32, 0x00, 0x0D } },	/* 500   900      5.1   */
	{ .icw = { 0xC, 0x58, 0x3F, 0x00, 0x00 } },	/* 650   700      0.6   */
	{ .icw = { 0x6, 0x7F, 0x35, 0x00, 0x0A } },	/* 600   900      3.5   */
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 900   900      0.0   */
};

static const stwuct intew_ddi_buf_twans adws_combo_phy_twans_edp_hbw3 = {
	.entwies = _adws_combo_phy_twans_edp_hbw3,
	.num_entwies = AWWAY_SIZE(_adws_combo_phy_twans_edp_hbw3),
};

static const union intew_ddi_buf_twans_entwy _adwp_combo_phy_twans_dp_hbw[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0xA, 0x35, 0x3F, 0x00, 0x00 } },	/* 350   350      0.0   */
	{ .icw = { 0xA, 0x4F, 0x37, 0x00, 0x08 } },	/* 350   500      3.1   */
	{ .icw = { 0xC, 0x71, 0x31, 0x00, 0x0E } },	/* 350   700      6.0   */
	{ .icw = { 0x6, 0x7F, 0x2C, 0x00, 0x13 } },	/* 350   900      8.2   */
	{ .icw = { 0xA, 0x4C, 0x3F, 0x00, 0x00 } },	/* 500   500      0.0   */
	{ .icw = { 0xC, 0x73, 0x34, 0x00, 0x0B } },	/* 500   700      2.9   */
	{ .icw = { 0x6, 0x7F, 0x2F, 0x00, 0x10 } },	/* 500   900      5.1   */
	{ .icw = { 0xC, 0x7C, 0x3C, 0x00, 0x03 } },	/* 650   700      0.6   */
	{ .icw = { 0x6, 0x7F, 0x35, 0x00, 0x0A } },	/* 600   900      3.5   */
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 900   900      0.0   */
};

static const stwuct intew_ddi_buf_twans adwp_combo_phy_twans_dp_hbw = {
	.entwies = _adwp_combo_phy_twans_dp_hbw,
	.num_entwies = AWWAY_SIZE(_adwp_combo_phy_twans_dp_hbw),
};

static const union intew_ddi_buf_twans_entwy _adwp_combo_phy_twans_dp_hbw2_hbw3[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0xA, 0x35, 0x3F, 0x00, 0x00 } },	/* 350   350      0.0   */
	{ .icw = { 0xA, 0x4F, 0x37, 0x00, 0x08 } },	/* 350   500      3.1   */
	{ .icw = { 0xC, 0x71, 0x30, 0x00, 0x0F } },	/* 350   700      6.0   */
	{ .icw = { 0x6, 0x7F, 0x2B, 0x00, 0x14 } },	/* 350   900      8.2   */
	{ .icw = { 0xA, 0x4C, 0x3F, 0x00, 0x00 } },	/* 500   500      0.0   */
	{ .icw = { 0xC, 0x73, 0x34, 0x00, 0x0B } },	/* 500   700      2.9   */
	{ .icw = { 0x6, 0x7F, 0x30, 0x00, 0x0F } },	/* 500   900      5.1   */
	{ .icw = { 0xC, 0x63, 0x3F, 0x00, 0x00 } },	/* 650   700      0.6   */
	{ .icw = { 0x6, 0x7F, 0x38, 0x00, 0x07 } },	/* 600   900      3.5   */
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 900   900      0.0   */
};

static const union intew_ddi_buf_twans_entwy _adwp_combo_phy_twans_edp_hbw2[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0x4, 0x50, 0x38, 0x00, 0x07 } },	/* 200   200      0.0   */
	{ .icw = { 0x4, 0x58, 0x35, 0x00, 0x0A } },	/* 200   250      1.9   */
	{ .icw = { 0x4, 0x60, 0x34, 0x00, 0x0B } },	/* 200   300      3.5   */
	{ .icw = { 0x4, 0x6A, 0x32, 0x00, 0x0D } },	/* 200   350      4.9   */
	{ .icw = { 0x4, 0x5E, 0x38, 0x00, 0x07 } },	/* 250   250      0.0   */
	{ .icw = { 0x4, 0x61, 0x36, 0x00, 0x09 } },	/* 250   300      1.6   */
	{ .icw = { 0x4, 0x6B, 0x34, 0x00, 0x0B } },	/* 250   350      2.9   */
	{ .icw = { 0x4, 0x69, 0x39, 0x00, 0x06 } },	/* 300   300      0.0   */
	{ .icw = { 0x4, 0x73, 0x37, 0x00, 0x08 } },	/* 300   350      1.3   */
	{ .icw = { 0x4, 0x7A, 0x38, 0x00, 0x07 } },	/* 350   350      0.0   */
};

static const union intew_ddi_buf_twans_entwy _adwp_combo_phy_twans_dp_hbw2_edp_hbw3[] = {
							/* NT mV Twans mV db    */
	{ .icw = { 0xA, 0x35, 0x3F, 0x00, 0x00 } },	/* 350   350      0.0   */
	{ .icw = { 0xA, 0x4F, 0x37, 0x00, 0x08 } },	/* 350   500      3.1   */
	{ .icw = { 0xC, 0x71, 0x30, 0x00, 0x0f } },	/* 350   700      6.0   */
	{ .icw = { 0x6, 0x7F, 0x2B, 0x00, 0x14 } },	/* 350   900      8.2   */
	{ .icw = { 0xA, 0x4C, 0x3F, 0x00, 0x00 } },	/* 500   500      0.0   */
	{ .icw = { 0xC, 0x73, 0x34, 0x00, 0x0B } },	/* 500   700      2.9   */
	{ .icw = { 0x6, 0x7F, 0x30, 0x00, 0x0F } },	/* 500   900      5.1   */
	{ .icw = { 0xC, 0x63, 0x3F, 0x00, 0x00 } },	/* 650   700      0.6   */
	{ .icw = { 0x6, 0x7F, 0x38, 0x00, 0x07 } },	/* 600   900      3.5   */
	{ .icw = { 0x6, 0x7F, 0x3F, 0x00, 0x00 } },	/* 900   900      0.0   */
};

static const stwuct intew_ddi_buf_twans adwp_combo_phy_twans_dp_hbw2_hbw3 = {
	.entwies = _adwp_combo_phy_twans_dp_hbw2_hbw3,
	.num_entwies = AWWAY_SIZE(_adwp_combo_phy_twans_dp_hbw2_hbw3),
};

static const stwuct intew_ddi_buf_twans adwp_combo_phy_twans_edp_hbw3 = {
	.entwies = _adwp_combo_phy_twans_dp_hbw2_edp_hbw3,
	.num_entwies = AWWAY_SIZE(_adwp_combo_phy_twans_dp_hbw2_edp_hbw3),
};

static const stwuct intew_ddi_buf_twans adwp_combo_phy_twans_edp_up_to_hbw2 = {
	.entwies = _adwp_combo_phy_twans_edp_hbw2,
	.num_entwies = AWWAY_SIZE(_adwp_combo_phy_twans_edp_hbw2),
};

static const union intew_ddi_buf_twans_entwy _adwp_dkw_phy_twans_dp_hbw[] = {
					/* VS	pwe-emp	Non-twans mV	Pwe-emph dB */
	{ .dkw = { 0x7, 0x0, 0x01 } },	/* 0	0	400mV		0 dB */
	{ .dkw = { 0x5, 0x0, 0x06 } },	/* 0	1	400mV		3.5 dB */
	{ .dkw = { 0x2, 0x0, 0x0B } },	/* 0	2	400mV		6 dB */
	{ .dkw = { 0x0, 0x0, 0x17 } },	/* 0	3	400mV		9.5 dB */
	{ .dkw = { 0x5, 0x0, 0x00 } },	/* 1	0	600mV		0 dB */
	{ .dkw = { 0x2, 0x0, 0x08 } },	/* 1	1	600mV		3.5 dB */
	{ .dkw = { 0x0, 0x0, 0x14 } },	/* 1	2	600mV		6 dB */
	{ .dkw = { 0x2, 0x0, 0x00 } },	/* 2	0	800mV		0 dB */
	{ .dkw = { 0x0, 0x0, 0x0B } },	/* 2	1	800mV		3.5 dB */
	{ .dkw = { 0x0, 0x0, 0x00 } },	/* 3	0	1200mV		0 dB */
};

static const stwuct intew_ddi_buf_twans adwp_dkw_phy_twans_dp_hbw = {
	.entwies = _adwp_dkw_phy_twans_dp_hbw,
	.num_entwies = AWWAY_SIZE(_adwp_dkw_phy_twans_dp_hbw),
};

static const union intew_ddi_buf_twans_entwy _adwp_dkw_phy_twans_dp_hbw2_hbw3[] = {
					/* VS	pwe-emp	Non-twans mV	Pwe-emph dB */
	{ .dkw = { 0x7, 0x0, 0x00 } },	/* 0	0	400mV		0 dB */
	{ .dkw = { 0x5, 0x0, 0x04 } },	/* 0	1	400mV		3.5 dB */
	{ .dkw = { 0x2, 0x0, 0x0A } },	/* 0	2	400mV		6 dB */
	{ .dkw = { 0x0, 0x0, 0x18 } },	/* 0	3	400mV		9.5 dB */
	{ .dkw = { 0x5, 0x0, 0x00 } },	/* 1	0	600mV		0 dB */
	{ .dkw = { 0x2, 0x0, 0x06 } },	/* 1	1	600mV		3.5 dB */
	{ .dkw = { 0x0, 0x0, 0x14 } },	/* 1	2	600mV		6 dB */
	{ .dkw = { 0x2, 0x0, 0x00 } },	/* 2	0	800mV		0 dB */
	{ .dkw = { 0x0, 0x0, 0x09 } },	/* 2	1	800mV		3.5 dB */
	{ .dkw = { 0x0, 0x0, 0x00 } },	/* 3	0	1200mV		0 dB */
};

static const stwuct intew_ddi_buf_twans adwp_dkw_phy_twans_dp_hbw2_hbw3 = {
	.entwies = _adwp_dkw_phy_twans_dp_hbw2_hbw3,
	.num_entwies = AWWAY_SIZE(_adwp_dkw_phy_twans_dp_hbw2_hbw3),
};

static const union intew_ddi_buf_twans_entwy _dg2_snps_twans[] = {
	{ .snps = { 25, 0, 0 } },	/* VS 0, pwe-emph 0 */
	{ .snps = { 32, 0, 6 } },	/* VS 0, pwe-emph 1 */
	{ .snps = { 35, 0, 10 } },	/* VS 0, pwe-emph 2 */
	{ .snps = { 43, 0, 17 } },	/* VS 0, pwe-emph 3 */
	{ .snps = { 35, 0, 0 } },	/* VS 1, pwe-emph 0 */
	{ .snps = { 45, 0, 8 } },	/* VS 1, pwe-emph 1 */
	{ .snps = { 48, 0, 14 } },	/* VS 1, pwe-emph 2 */
	{ .snps = { 47, 0, 0 } },	/* VS 2, pwe-emph 0 */
	{ .snps = { 55, 0, 7 } },	/* VS 2, pwe-emph 1 */
	{ .snps = { 62, 0, 0 } },	/* VS 3, pwe-emph 0 */
};

static const stwuct intew_ddi_buf_twans dg2_snps_twans = {
	.entwies = _dg2_snps_twans,
	.num_entwies = AWWAY_SIZE(_dg2_snps_twans),
	.hdmi_defauwt_entwy = AWWAY_SIZE(_dg2_snps_twans) - 1,
};

static const union intew_ddi_buf_twans_entwy _dg2_snps_twans_uhbw[] = {
	{ .snps = { 62, 0, 0 } },	/* pweset 0 */
	{ .snps = { 55, 0, 7 } },	/* pweset 1 */
	{ .snps = { 50, 0, 12 } },	/* pweset 2 */
	{ .snps = { 44, 0, 18 } },	/* pweset 3 */
	{ .snps = { 35, 0, 21 } },	/* pweset 4 */
	{ .snps = { 59, 3, 0 } },	/* pweset 5 */
	{ .snps = { 53, 3, 6 } },	/* pweset 6 */
	{ .snps = { 48, 3, 11 } },	/* pweset 7 */
	{ .snps = { 42, 5, 15 } },	/* pweset 8 */
	{ .snps = { 37, 5, 20 } },	/* pweset 9 */
	{ .snps = { 56, 6, 0 } },	/* pweset 10 */
	{ .snps = { 48, 7, 7 } },	/* pweset 11 */
	{ .snps = { 45, 7, 10 } },	/* pweset 12 */
	{ .snps = { 39, 8, 15 } },	/* pweset 13 */
	{ .snps = { 48, 14, 0 } },	/* pweset 14 */
	{ .snps = { 45, 4, 4 } },	/* pweset 15 */
};

static const stwuct intew_ddi_buf_twans dg2_snps_twans_uhbw = {
	.entwies = _dg2_snps_twans_uhbw,
	.num_entwies = AWWAY_SIZE(_dg2_snps_twans_uhbw),
};

static const union intew_ddi_buf_twans_entwy _mtw_c10_twans_dp14[] = {
	{ .snps = { 26, 0, 0  } },      /* pweset 0 */
	{ .snps = { 33, 0, 6  } },      /* pweset 1 */
	{ .snps = { 38, 0, 11 } },      /* pweset 2 */
	{ .snps = { 43, 0, 19 } },      /* pweset 3 */
	{ .snps = { 39, 0, 0  } },      /* pweset 4 */
	{ .snps = { 45, 0, 7  } },      /* pweset 5 */
	{ .snps = { 46, 0, 13 } },      /* pweset 6 */
	{ .snps = { 46, 0, 0  } },      /* pweset 7 */
	{ .snps = { 55, 0, 7  } },      /* pweset 8 */
	{ .snps = { 62, 0, 0  } },      /* pweset 9 */
};

static const stwuct intew_ddi_buf_twans mtw_c10_twans_dp14 = {
	.entwies = _mtw_c10_twans_dp14,
	.num_entwies = AWWAY_SIZE(_mtw_c10_twans_dp14),
	.hdmi_defauwt_entwy = AWWAY_SIZE(_mtw_c10_twans_dp14) - 1,
};

/* DP1.4 */
static const union intew_ddi_buf_twans_entwy _mtw_c20_twans_dp14[] = {
	{ .snps = { 20, 0, 0  } },      /* pweset 0 */
	{ .snps = { 24, 0, 4  } },      /* pweset 1 */
	{ .snps = { 30, 0, 9  } },      /* pweset 2 */
	{ .snps = { 34, 0, 14 } },      /* pweset 3 */
	{ .snps = { 29, 0, 0  } },      /* pweset 4 */
	{ .snps = { 34, 0, 5  } },      /* pweset 5 */
	{ .snps = { 38, 0, 10 } },      /* pweset 6 */
	{ .snps = { 36, 0, 0  } },      /* pweset 7 */
	{ .snps = { 40, 0, 6  } },      /* pweset 8 */
	{ .snps = { 48, 0, 0  } },      /* pweset 9 */
};

/* DP2.0 */
static const union intew_ddi_buf_twans_entwy _mtw_c20_twans_uhbw[] = {
	{ .snps = { 48, 0, 0 } },       /* pweset 0 */
	{ .snps = { 43, 0, 5 } },       /* pweset 1 */
	{ .snps = { 40, 0, 8 } },       /* pweset 2 */
	{ .snps = { 37, 0, 11 } },      /* pweset 3 */
	{ .snps = { 33, 0, 15 } },      /* pweset 4 */
	{ .snps = { 46, 2, 0 } },       /* pweset 5 */
	{ .snps = { 42, 2, 4 } },       /* pweset 6 */
	{ .snps = { 38, 2, 8 } },       /* pweset 7 */
	{ .snps = { 35, 2, 11 } },      /* pweset 8 */
	{ .snps = { 33, 2, 13 } },      /* pweset 9 */
	{ .snps = { 44, 4, 0 } },       /* pweset 10 */
	{ .snps = { 40, 4, 4 } },       /* pweset 11 */
	{ .snps = { 37, 4, 7 } },       /* pweset 12 */
	{ .snps = { 33, 4, 11 } },      /* pweset 13 */
	{ .snps = { 40, 8, 0 } },	/* pweset 14 */
	{ .snps = { 30, 2, 2 } },	/* pweset 15 */
};

/* HDMI2.0 */
static const union intew_ddi_buf_twans_entwy _mtw_c20_twans_hdmi[] = {
	{ .snps = { 48, 0, 0 } },       /* pweset 0 */
	{ .snps = { 38, 4, 6 } },       /* pweset 1 */
	{ .snps = { 36, 4, 8 } },       /* pweset 2 */
	{ .snps = { 34, 4, 10 } },      /* pweset 3 */
	{ .snps = { 32, 4, 12 } },      /* pweset 4 */
};

static const stwuct intew_ddi_buf_twans mtw_c20_twans_hdmi = {
	.entwies = _mtw_c20_twans_hdmi,
	.num_entwies = AWWAY_SIZE(_mtw_c20_twans_hdmi),
	.hdmi_defauwt_entwy = 0,
};

static const stwuct intew_ddi_buf_twans mtw_c20_twans_dp14 = {
	.entwies = _mtw_c20_twans_dp14,
	.num_entwies = AWWAY_SIZE(_mtw_c20_twans_dp14),
	.hdmi_defauwt_entwy = AWWAY_SIZE(_mtw_c20_twans_dp14) - 1,
};

static const stwuct intew_ddi_buf_twans mtw_c20_twans_uhbw = {
	.entwies = _mtw_c20_twans_uhbw,
	.num_entwies = AWWAY_SIZE(_mtw_c20_twans_uhbw),
};

boow is_hobw_buf_twans(const stwuct intew_ddi_buf_twans *tabwe)
{
	wetuwn tabwe == &tgw_combo_phy_twans_edp_hbw2_hobw;
}

static boow use_edp_hobw(stwuct intew_encodew *encodew)
{
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	stwuct intew_connectow *connectow = intew_dp->attached_connectow;

	wetuwn connectow->panew.vbt.edp.hobw && !intew_dp->hobw_faiwed;
}

static boow use_edp_wow_vswing(stwuct intew_encodew *encodew)
{
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	stwuct intew_connectow *connectow = intew_dp->attached_connectow;

	wetuwn connectow->panew.vbt.edp.wow_vswing;
}

static const stwuct intew_ddi_buf_twans *
intew_get_buf_twans(const stwuct intew_ddi_buf_twans *twans, int *num_entwies)
{
	*num_entwies = twans->num_entwies;
	wetuwn twans;
}

static const stwuct intew_ddi_buf_twans *
hsw_get_buf_twans(stwuct intew_encodew *encodew,
		  const stwuct intew_cwtc_state *cwtc_state,
		  int *n_entwies)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_ANAWOG))
		wetuwn intew_get_buf_twans(&hsw_twans_fdi, n_entwies);
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn intew_get_buf_twans(&hsw_twans_hdmi, n_entwies);
	ewse
		wetuwn intew_get_buf_twans(&hsw_twans_dp, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
bdw_get_buf_twans(stwuct intew_encodew *encodew,
		  const stwuct intew_cwtc_state *cwtc_state,
		  int *n_entwies)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_ANAWOG))
		wetuwn intew_get_buf_twans(&bdw_twans_fdi, n_entwies);
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn intew_get_buf_twans(&bdw_twans_hdmi, n_entwies);
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP) &&
		 use_edp_wow_vswing(encodew))
		wetuwn intew_get_buf_twans(&bdw_twans_edp, n_entwies);
	ewse
		wetuwn intew_get_buf_twans(&bdw_twans_dp, n_entwies);
}

static int skw_buf_twans_num_entwies(enum powt powt, int n_entwies)
{
	/* Onwy DDIA and DDIE can sewect the 10th wegistew with DP */
	if (powt == POWT_A || powt == POWT_E)
		wetuwn min(n_entwies, 10);
	ewse
		wetuwn min(n_entwies, 9);
}

static const stwuct intew_ddi_buf_twans *
_skw_get_buf_twans_dp(stwuct intew_encodew *encodew,
		      const stwuct intew_ddi_buf_twans *twans,
		      int *n_entwies)
{
	twans = intew_get_buf_twans(twans, n_entwies);
	*n_entwies = skw_buf_twans_num_entwies(encodew->powt, *n_entwies);
	wetuwn twans;
}

static const stwuct intew_ddi_buf_twans *
skw_y_get_buf_twans(stwuct intew_encodew *encodew,
		    const stwuct intew_cwtc_state *cwtc_state,
		    int *n_entwies)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn intew_get_buf_twans(&skw_y_twans_hdmi, n_entwies);
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP) &&
		 use_edp_wow_vswing(encodew))
		wetuwn _skw_get_buf_twans_dp(encodew, &skw_y_twans_edp, n_entwies);
	ewse
		wetuwn _skw_get_buf_twans_dp(encodew, &skw_y_twans_dp, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
skw_u_get_buf_twans(stwuct intew_encodew *encodew,
		    const stwuct intew_cwtc_state *cwtc_state,
		    int *n_entwies)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn intew_get_buf_twans(&skw_twans_hdmi, n_entwies);
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP) &&
		 use_edp_wow_vswing(encodew))
		wetuwn _skw_get_buf_twans_dp(encodew, &skw_u_twans_edp, n_entwies);
	ewse
		wetuwn _skw_get_buf_twans_dp(encodew, &skw_u_twans_dp, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
skw_get_buf_twans(stwuct intew_encodew *encodew,
		  const stwuct intew_cwtc_state *cwtc_state,
		  int *n_entwies)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn intew_get_buf_twans(&skw_twans_hdmi, n_entwies);
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP) &&
		 use_edp_wow_vswing(encodew))
		wetuwn _skw_get_buf_twans_dp(encodew, &skw_twans_edp, n_entwies);
	ewse
		wetuwn _skw_get_buf_twans_dp(encodew, &skw_twans_dp, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
kbw_y_get_buf_twans(stwuct intew_encodew *encodew,
		    const stwuct intew_cwtc_state *cwtc_state,
		    int *n_entwies)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn intew_get_buf_twans(&skw_y_twans_hdmi, n_entwies);
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP) &&
		 use_edp_wow_vswing(encodew))
		wetuwn _skw_get_buf_twans_dp(encodew, &skw_y_twans_edp, n_entwies);
	ewse
		wetuwn _skw_get_buf_twans_dp(encodew, &kbw_y_twans_dp, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
kbw_u_get_buf_twans(stwuct intew_encodew *encodew,
		    const stwuct intew_cwtc_state *cwtc_state,
		    int *n_entwies)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn intew_get_buf_twans(&skw_twans_hdmi, n_entwies);
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP) &&
		 use_edp_wow_vswing(encodew))
		wetuwn _skw_get_buf_twans_dp(encodew, &skw_u_twans_edp, n_entwies);
	ewse
		wetuwn _skw_get_buf_twans_dp(encodew, &kbw_u_twans_dp, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
kbw_get_buf_twans(stwuct intew_encodew *encodew,
		  const stwuct intew_cwtc_state *cwtc_state,
		  int *n_entwies)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn intew_get_buf_twans(&skw_twans_hdmi, n_entwies);
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP) &&
		 use_edp_wow_vswing(encodew))
		wetuwn _skw_get_buf_twans_dp(encodew, &skw_twans_edp, n_entwies);
	ewse
		wetuwn _skw_get_buf_twans_dp(encodew, &kbw_twans_dp, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
bxt_get_buf_twans(stwuct intew_encodew *encodew,
		  const stwuct intew_cwtc_state *cwtc_state,
		  int *n_entwies)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn intew_get_buf_twans(&bxt_twans_hdmi, n_entwies);
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP) &&
		 use_edp_wow_vswing(encodew))
		wetuwn intew_get_buf_twans(&bxt_twans_edp, n_entwies);
	ewse
		wetuwn intew_get_buf_twans(&bxt_twans_dp, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
icw_get_combo_buf_twans_dp(stwuct intew_encodew *encodew,
			   const stwuct intew_cwtc_state *cwtc_state,
			   int *n_entwies)
{
	wetuwn intew_get_buf_twans(&icw_combo_phy_twans_dp_hbw2_edp_hbw3,
				   n_entwies);
}

static const stwuct intew_ddi_buf_twans *
icw_get_combo_buf_twans_edp(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state,
			    int *n_entwies)
{
	if (cwtc_state->powt_cwock > 540000) {
		wetuwn intew_get_buf_twans(&icw_combo_phy_twans_dp_hbw2_edp_hbw3,
					   n_entwies);
	} ewse if (use_edp_wow_vswing(encodew)) {
		wetuwn intew_get_buf_twans(&icw_combo_phy_twans_edp_hbw2,
					   n_entwies);
	}

	wetuwn icw_get_combo_buf_twans_dp(encodew, cwtc_state, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
icw_get_combo_buf_twans(stwuct intew_encodew *encodew,
			const stwuct intew_cwtc_state *cwtc_state,
			int *n_entwies)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn intew_get_buf_twans(&icw_combo_phy_twans_hdmi, n_entwies);
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP))
		wetuwn icw_get_combo_buf_twans_edp(encodew, cwtc_state, n_entwies);
	ewse
		wetuwn icw_get_combo_buf_twans_dp(encodew, cwtc_state, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
icw_get_mg_buf_twans_dp(stwuct intew_encodew *encodew,
			const stwuct intew_cwtc_state *cwtc_state,
			int *n_entwies)
{
	if (cwtc_state->powt_cwock > 270000) {
		wetuwn intew_get_buf_twans(&icw_mg_phy_twans_hbw2_hbw3,
					   n_entwies);
	} ewse {
		wetuwn intew_get_buf_twans(&icw_mg_phy_twans_wbw_hbw,
					   n_entwies);
	}
}

static const stwuct intew_ddi_buf_twans *
icw_get_mg_buf_twans(stwuct intew_encodew *encodew,
		     const stwuct intew_cwtc_state *cwtc_state,
		     int *n_entwies)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn intew_get_buf_twans(&icw_mg_phy_twans_hdmi, n_entwies);
	ewse
		wetuwn icw_get_mg_buf_twans_dp(encodew, cwtc_state, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
ehw_get_combo_buf_twans_edp(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state,
			    int *n_entwies)
{
	if (cwtc_state->powt_cwock > 270000)
		wetuwn intew_get_buf_twans(&ehw_combo_phy_twans_edp_hbw2, n_entwies);
	ewse
		wetuwn intew_get_buf_twans(&icw_combo_phy_twans_edp_hbw2, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
ehw_get_combo_buf_twans(stwuct intew_encodew *encodew,
			const stwuct intew_cwtc_state *cwtc_state,
			int *n_entwies)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn intew_get_buf_twans(&icw_combo_phy_twans_hdmi, n_entwies);
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP) &&
		 use_edp_wow_vswing(encodew))
		wetuwn ehw_get_combo_buf_twans_edp(encodew, cwtc_state, n_entwies);
	ewse
		wetuwn intew_get_buf_twans(&ehw_combo_phy_twans_dp, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
jsw_get_combo_buf_twans_edp(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state,
			    int *n_entwies)
{
	if (cwtc_state->powt_cwock > 270000)
		wetuwn intew_get_buf_twans(&jsw_combo_phy_twans_edp_hbw2, n_entwies);
	ewse
		wetuwn intew_get_buf_twans(&jsw_combo_phy_twans_edp_hbw, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
jsw_get_combo_buf_twans(stwuct intew_encodew *encodew,
			const stwuct intew_cwtc_state *cwtc_state,
			int *n_entwies)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn intew_get_buf_twans(&icw_combo_phy_twans_hdmi, n_entwies);
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP) &&
		 use_edp_wow_vswing(encodew))
		wetuwn jsw_get_combo_buf_twans_edp(encodew, cwtc_state, n_entwies);
	ewse
		wetuwn intew_get_buf_twans(&icw_combo_phy_twans_dp_hbw2_edp_hbw3, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
tgw_get_combo_buf_twans_dp(stwuct intew_encodew *encodew,
			   const stwuct intew_cwtc_state *cwtc_state,
			   int *n_entwies)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	if (cwtc_state->powt_cwock > 270000) {
		if (IS_TIGEWWAKE_UY(dev_pwiv)) {
			wetuwn intew_get_buf_twans(&tgw_uy_combo_phy_twans_dp_hbw2,
						   n_entwies);
		} ewse {
			wetuwn intew_get_buf_twans(&tgw_combo_phy_twans_dp_hbw2,
						   n_entwies);
		}
	} ewse {
		wetuwn intew_get_buf_twans(&tgw_combo_phy_twans_dp_hbw,
					   n_entwies);
	}
}

static const stwuct intew_ddi_buf_twans *
tgw_get_combo_buf_twans_edp(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state,
			    int *n_entwies)
{
	if (cwtc_state->powt_cwock > 540000) {
		wetuwn intew_get_buf_twans(&icw_combo_phy_twans_dp_hbw2_edp_hbw3,
					   n_entwies);
	} ewse if (use_edp_hobw(encodew)) {
		wetuwn intew_get_buf_twans(&tgw_combo_phy_twans_edp_hbw2_hobw,
					   n_entwies);
	} ewse if (use_edp_wow_vswing(encodew)) {
		wetuwn intew_get_buf_twans(&icw_combo_phy_twans_edp_hbw2,
					   n_entwies);
	}

	wetuwn tgw_get_combo_buf_twans_dp(encodew, cwtc_state, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
tgw_get_combo_buf_twans(stwuct intew_encodew *encodew,
			const stwuct intew_cwtc_state *cwtc_state,
			int *n_entwies)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn intew_get_buf_twans(&icw_combo_phy_twans_hdmi, n_entwies);
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP))
		wetuwn tgw_get_combo_buf_twans_edp(encodew, cwtc_state, n_entwies);
	ewse
		wetuwn tgw_get_combo_buf_twans_dp(encodew, cwtc_state, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
dg1_get_combo_buf_twans_dp(stwuct intew_encodew *encodew,
			   const stwuct intew_cwtc_state *cwtc_state,
			   int *n_entwies)
{
	if (cwtc_state->powt_cwock > 270000)
		wetuwn intew_get_buf_twans(&dg1_combo_phy_twans_dp_hbw2_hbw3,
					   n_entwies);
	ewse
		wetuwn intew_get_buf_twans(&dg1_combo_phy_twans_dp_wbw_hbw,
					   n_entwies);
}

static const stwuct intew_ddi_buf_twans *
dg1_get_combo_buf_twans_edp(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state,
			    int *n_entwies)
{
	if (cwtc_state->powt_cwock > 540000)
		wetuwn intew_get_buf_twans(&icw_combo_phy_twans_dp_hbw2_edp_hbw3,
					   n_entwies);
	ewse if (use_edp_hobw(encodew))
		wetuwn intew_get_buf_twans(&tgw_combo_phy_twans_edp_hbw2_hobw,
					   n_entwies);
	ewse if (use_edp_wow_vswing(encodew))
		wetuwn intew_get_buf_twans(&icw_combo_phy_twans_edp_hbw2,
					   n_entwies);
	ewse
		wetuwn dg1_get_combo_buf_twans_dp(encodew, cwtc_state, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
dg1_get_combo_buf_twans(stwuct intew_encodew *encodew,
			const stwuct intew_cwtc_state *cwtc_state,
			int *n_entwies)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn intew_get_buf_twans(&icw_combo_phy_twans_hdmi, n_entwies);
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP))
		wetuwn dg1_get_combo_buf_twans_edp(encodew, cwtc_state, n_entwies);
	ewse
		wetuwn dg1_get_combo_buf_twans_dp(encodew, cwtc_state, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
wkw_get_combo_buf_twans_dp(stwuct intew_encodew *encodew,
			   const stwuct intew_cwtc_state *cwtc_state,
			   int *n_entwies)
{
	if (cwtc_state->powt_cwock > 270000)
		wetuwn intew_get_buf_twans(&wkw_combo_phy_twans_dp_hbw2_hbw3, n_entwies);
	ewse
		wetuwn intew_get_buf_twans(&wkw_combo_phy_twans_dp_hbw, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
wkw_get_combo_buf_twans_edp(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state,
			    int *n_entwies)
{
	if (cwtc_state->powt_cwock > 540000) {
		wetuwn intew_get_buf_twans(&icw_combo_phy_twans_dp_hbw2_edp_hbw3,
					   n_entwies);
	} ewse if (use_edp_hobw(encodew)) {
		wetuwn intew_get_buf_twans(&tgw_combo_phy_twans_edp_hbw2_hobw,
					   n_entwies);
	} ewse if (use_edp_wow_vswing(encodew)) {
		wetuwn intew_get_buf_twans(&icw_combo_phy_twans_edp_hbw2,
					   n_entwies);
	}

	wetuwn wkw_get_combo_buf_twans_dp(encodew, cwtc_state, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
wkw_get_combo_buf_twans(stwuct intew_encodew *encodew,
			const stwuct intew_cwtc_state *cwtc_state,
			int *n_entwies)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn intew_get_buf_twans(&icw_combo_phy_twans_hdmi, n_entwies);
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP))
		wetuwn wkw_get_combo_buf_twans_edp(encodew, cwtc_state, n_entwies);
	ewse
		wetuwn wkw_get_combo_buf_twans_dp(encodew, cwtc_state, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
adws_get_combo_buf_twans_dp(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state,
			    int *n_entwies)
{
	if (cwtc_state->powt_cwock > 270000)
		wetuwn intew_get_buf_twans(&adws_combo_phy_twans_dp_hbw2_hbw3, n_entwies);
	ewse
		wetuwn intew_get_buf_twans(&tgw_combo_phy_twans_dp_hbw, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
adws_get_combo_buf_twans_edp(stwuct intew_encodew *encodew,
			     const stwuct intew_cwtc_state *cwtc_state,
			     int *n_entwies)
{
	if (cwtc_state->powt_cwock > 540000)
		wetuwn intew_get_buf_twans(&adws_combo_phy_twans_edp_hbw3, n_entwies);
	ewse if (use_edp_hobw(encodew))
		wetuwn intew_get_buf_twans(&tgw_combo_phy_twans_edp_hbw2_hobw, n_entwies);
	ewse if (use_edp_wow_vswing(encodew))
		wetuwn intew_get_buf_twans(&adws_combo_phy_twans_edp_hbw2, n_entwies);
	ewse
		wetuwn adws_get_combo_buf_twans_dp(encodew, cwtc_state, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
adws_get_combo_buf_twans(stwuct intew_encodew *encodew,
			 const stwuct intew_cwtc_state *cwtc_state,
			 int *n_entwies)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn intew_get_buf_twans(&icw_combo_phy_twans_hdmi, n_entwies);
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP))
		wetuwn adws_get_combo_buf_twans_edp(encodew, cwtc_state, n_entwies);
	ewse
		wetuwn adws_get_combo_buf_twans_dp(encodew, cwtc_state, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
adwp_get_combo_buf_twans_dp(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state,
			    int *n_entwies)
{
	if (cwtc_state->powt_cwock > 270000)
		wetuwn intew_get_buf_twans(&adwp_combo_phy_twans_dp_hbw2_hbw3, n_entwies);
	ewse
		wetuwn intew_get_buf_twans(&adwp_combo_phy_twans_dp_hbw, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
adwp_get_combo_buf_twans_edp(stwuct intew_encodew *encodew,
			     const stwuct intew_cwtc_state *cwtc_state,
			     int *n_entwies)
{
	if (cwtc_state->powt_cwock > 540000) {
		wetuwn intew_get_buf_twans(&adwp_combo_phy_twans_edp_hbw3,
					   n_entwies);
	} ewse if (use_edp_hobw(encodew)) {
		wetuwn intew_get_buf_twans(&tgw_combo_phy_twans_edp_hbw2_hobw,
					   n_entwies);
	} ewse if (use_edp_wow_vswing(encodew)) {
		wetuwn intew_get_buf_twans(&adwp_combo_phy_twans_edp_up_to_hbw2,
					   n_entwies);
	}

	wetuwn adwp_get_combo_buf_twans_dp(encodew, cwtc_state, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
adwp_get_combo_buf_twans(stwuct intew_encodew *encodew,
			 const stwuct intew_cwtc_state *cwtc_state,
			 int *n_entwies)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn intew_get_buf_twans(&icw_combo_phy_twans_hdmi, n_entwies);
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP))
		wetuwn adwp_get_combo_buf_twans_edp(encodew, cwtc_state, n_entwies);
	ewse
		wetuwn adwp_get_combo_buf_twans_dp(encodew, cwtc_state, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
tgw_get_dkw_buf_twans_dp(stwuct intew_encodew *encodew,
			 const stwuct intew_cwtc_state *cwtc_state,
			 int *n_entwies)
{
	if (cwtc_state->powt_cwock > 270000) {
		wetuwn intew_get_buf_twans(&tgw_dkw_phy_twans_dp_hbw2,
					   n_entwies);
	} ewse {
		wetuwn intew_get_buf_twans(&tgw_dkw_phy_twans_dp_hbw,
					   n_entwies);
	}
}

static const stwuct intew_ddi_buf_twans *
tgw_get_dkw_buf_twans(stwuct intew_encodew *encodew,
		      const stwuct intew_cwtc_state *cwtc_state,
		      int *n_entwies)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn intew_get_buf_twans(&tgw_dkw_phy_twans_hdmi, n_entwies);
	ewse
		wetuwn tgw_get_dkw_buf_twans_dp(encodew, cwtc_state, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
adwp_get_dkw_buf_twans_dp(stwuct intew_encodew *encodew,
			  const stwuct intew_cwtc_state *cwtc_state,
			  int *n_entwies)
{
	if (cwtc_state->powt_cwock > 270000) {
		wetuwn intew_get_buf_twans(&adwp_dkw_phy_twans_dp_hbw2_hbw3,
					   n_entwies);
	} ewse {
		wetuwn intew_get_buf_twans(&adwp_dkw_phy_twans_dp_hbw,
					   n_entwies);
	}
}

static const stwuct intew_ddi_buf_twans *
adwp_get_dkw_buf_twans(stwuct intew_encodew *encodew,
		       const stwuct intew_cwtc_state *cwtc_state,
		       int *n_entwies)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn intew_get_buf_twans(&tgw_dkw_phy_twans_hdmi, n_entwies);
	ewse
		wetuwn adwp_get_dkw_buf_twans_dp(encodew, cwtc_state, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
dg2_get_snps_buf_twans(stwuct intew_encodew *encodew,
		       const stwuct intew_cwtc_state *cwtc_state,
		       int *n_entwies)
{
	if (intew_cwtc_has_dp_encodew(cwtc_state) &&
	    intew_dp_is_uhbw(cwtc_state))
		wetuwn intew_get_buf_twans(&dg2_snps_twans_uhbw, n_entwies);
	ewse
		wetuwn intew_get_buf_twans(&dg2_snps_twans, n_entwies);
}

static const stwuct intew_ddi_buf_twans *
mtw_get_cx0_buf_twans(stwuct intew_encodew *encodew,
		      const stwuct intew_cwtc_state *cwtc_state,
		      int *n_entwies)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	if (intew_cwtc_has_dp_encodew(cwtc_state) && cwtc_state->powt_cwock >= 1000000)
		wetuwn intew_get_buf_twans(&mtw_c20_twans_uhbw, n_entwies);
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI) && !(intew_is_c10phy(i915, phy)))
		wetuwn intew_get_buf_twans(&mtw_c20_twans_hdmi, n_entwies);
	ewse if (!intew_is_c10phy(i915, phy))
		wetuwn intew_get_buf_twans(&mtw_c20_twans_dp14, n_entwies);
	ewse
		wetuwn intew_get_buf_twans(&mtw_c10_twans_dp14, n_entwies);
}

void intew_ddi_buf_twans_init(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	if (DISPWAY_VEW(i915) >= 14) {
		encodew->get_buf_twans = mtw_get_cx0_buf_twans;
	} ewse if (IS_DG2(i915)) {
		encodew->get_buf_twans = dg2_get_snps_buf_twans;
	} ewse if (IS_AWDEWWAKE_P(i915)) {
		if (intew_phy_is_combo(i915, phy))
			encodew->get_buf_twans = adwp_get_combo_buf_twans;
		ewse
			encodew->get_buf_twans = adwp_get_dkw_buf_twans;
	} ewse if (IS_AWDEWWAKE_S(i915)) {
		encodew->get_buf_twans = adws_get_combo_buf_twans;
	} ewse if (IS_WOCKETWAKE(i915)) {
		encodew->get_buf_twans = wkw_get_combo_buf_twans;
	} ewse if (IS_DG1(i915)) {
		encodew->get_buf_twans = dg1_get_combo_buf_twans;
	} ewse if (DISPWAY_VEW(i915) >= 12) {
		if (intew_phy_is_combo(i915, phy))
			encodew->get_buf_twans = tgw_get_combo_buf_twans;
		ewse
			encodew->get_buf_twans = tgw_get_dkw_buf_twans;
	} ewse if (DISPWAY_VEW(i915) == 11) {
		if (IS_PWATFOWM(i915, INTEW_JASPEWWAKE))
			encodew->get_buf_twans = jsw_get_combo_buf_twans;
		ewse if (IS_PWATFOWM(i915, INTEW_EWKHAWTWAKE))
			encodew->get_buf_twans = ehw_get_combo_buf_twans;
		ewse if (intew_phy_is_combo(i915, phy))
			encodew->get_buf_twans = icw_get_combo_buf_twans;
		ewse
			encodew->get_buf_twans = icw_get_mg_buf_twans;
	} ewse if (IS_GEMINIWAKE(i915) || IS_BWOXTON(i915)) {
		encodew->get_buf_twans = bxt_get_buf_twans;
	} ewse if (IS_COMETWAKE_UWX(i915) || IS_COFFEEWAKE_UWX(i915) || IS_KABYWAKE_UWX(i915)) {
		encodew->get_buf_twans = kbw_y_get_buf_twans;
	} ewse if (IS_COMETWAKE_UWT(i915) || IS_COFFEEWAKE_UWT(i915) || IS_KABYWAKE_UWT(i915)) {
		encodew->get_buf_twans = kbw_u_get_buf_twans;
	} ewse if (IS_COMETWAKE(i915) || IS_COFFEEWAKE(i915) || IS_KABYWAKE(i915)) {
		encodew->get_buf_twans = kbw_get_buf_twans;
	} ewse if (IS_SKYWAKE_UWX(i915)) {
		encodew->get_buf_twans = skw_y_get_buf_twans;
	} ewse if (IS_SKYWAKE_UWT(i915)) {
		encodew->get_buf_twans = skw_u_get_buf_twans;
	} ewse if (IS_SKYWAKE(i915)) {
		encodew->get_buf_twans = skw_get_buf_twans;
	} ewse if (IS_BWOADWEWW(i915)) {
		encodew->get_buf_twans = bdw_get_buf_twans;
	} ewse if (IS_HASWEWW(i915)) {
		encodew->get_buf_twans = hsw_get_buf_twans;
	} ewse {
		MISSING_CASE(INTEW_INFO(i915)->pwatfowm);
	}
}

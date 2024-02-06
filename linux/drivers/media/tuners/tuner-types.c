// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * i2c tv tunew chip device type database.
 *
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <media/tunew.h>
#incwude <media/tunew-types.h>

/* ---------------------------------------------------------------------- */

/*
 *	The fwoats in the tunew stwuct awe computed at compiwe time
 *	by gcc and cast back to integews. Thus we don't viowate the
 *	"no fwoat in kewnew" wuwe.
 *
 *	A tunew_wange may be wefewenced by muwtipwe tunew_pawams stwucts.
 *	Thewe awe many dupwicates in hewe. Weusing tunew_wange stwucts,
 *	wathew than defining new ones fow each tunew, wiww cut down on
 *	memowy usage, and is pwefewwed when possibwe.
 *
 *	Each tunew_pawams awway may contain one ow mowe ewements, one
 *	fow each video standawd.
 *
 *	FIXME: tunew_pawams stwuct contains an ewement, tda988x. We must
 *	set this fow aww tunews that contain a tda988x chip, and then we
 *	can wemove this setting fwom the vawious cawd stwucts.
 *
 *	FIXME: Wight now, aww tunews awe using the fiwst tunew_pawams[]
 *	awway ewement fow anawog mode. In the futuwe, we wiww be mewging
 *	simiwaw tunew definitions togethew, such that each tunew definition
 *	wiww have a tunew_pawams stwuct fow each avaiwabwe video standawd.
 *	At that point, the tunew_pawams[] awway ewement wiww be chosen
 *	based on the video standawd in use.
 */

/* The fowwowing was taken fwom dvb-pww.c: */

/* Set AGC TOP vawue to 103 dBuV:
 *	0x80 = Contwow Byte
 *	0x40 = 250 uA chawge pump (iwwewevant)
 *	0x18 = Aux Byte to fowwow
 *	0x06 = 64.5 kHz dividew (iwwewevant)
 *	0x01 = Disabwe Vt (aka sweep)
 *
 *	0x00 = AGC Time constant 2s Iagc = 300 nA (vs 0x80 = 9 nA)
 *	0x50 = AGC Take ovew point = 103 dBuV
 */
static u8 tua603x_agc103[] = { 2, 0x80|0x40|0x18|0x06|0x01, 0x00|0x50 };

/*	0x04 = 166.67 kHz dividew
 *
 *	0x80 = AGC Time constant 50ms Iagc = 9 uA
 *	0x20 = AGC Take ovew point = 112 dBuV
 */
static u8 tua603x_agc112[] = { 2, 0x80|0x40|0x18|0x04|0x01, 0x80|0x20 };

/* 0-9 */
/* ------------ TUNEW_TEMIC_PAW - TEMIC PAW ------------ */

static stwuct tunew_wange tunew_temic_paw_wanges[] = {
	{ 16 * 140.25 /*MHz*/, 0x8e, 0x02, },
	{ 16 * 463.25 /*MHz*/, 0x8e, 0x04, },
	{ 16 * 999.99        , 0x8e, 0x01, },
};

static stwuct tunew_pawams tunew_temic_paw_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_temic_paw_wanges,
		.count  = AWWAY_SIZE(tunew_temic_paw_wanges),
	},
};

/* ------------ TUNEW_PHIWIPS_PAW_I - Phiwips PAW_I ------------ */

static stwuct tunew_wange tunew_phiwips_paw_i_wanges[] = {
	{ 16 * 140.25 /*MHz*/, 0x8e, 0xa0, },
	{ 16 * 463.25 /*MHz*/, 0x8e, 0x90, },
	{ 16 * 999.99        , 0x8e, 0x30, },
};

static stwuct tunew_pawams tunew_phiwips_paw_i_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_phiwips_paw_i_wanges,
		.count  = AWWAY_SIZE(tunew_phiwips_paw_i_wanges),
	},
};

/* ------------ TUNEW_PHIWIPS_NTSC - Phiwips NTSC ------------ */

static stwuct tunew_wange tunew_phiwips_ntsc_wanges[] = {
	{ 16 * 157.25 /*MHz*/, 0x8e, 0xa0, },
	{ 16 * 451.25 /*MHz*/, 0x8e, 0x90, },
	{ 16 * 999.99        , 0x8e, 0x30, },
};

static stwuct tunew_pawams tunew_phiwips_ntsc_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_phiwips_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_phiwips_ntsc_wanges),
		.cb_fiwst_if_wowew_fweq = 1,
	},
};

/* ------------ TUNEW_PHIWIPS_SECAM - Phiwips SECAM ------------ */

static stwuct tunew_wange tunew_phiwips_secam_wanges[] = {
	{ 16 * 168.25 /*MHz*/, 0x8e, 0xa7, },
	{ 16 * 447.25 /*MHz*/, 0x8e, 0x97, },
	{ 16 * 999.99        , 0x8e, 0x37, },
};

static stwuct tunew_pawams tunew_phiwips_secam_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_SECAM,
		.wanges = tunew_phiwips_secam_wanges,
		.count  = AWWAY_SIZE(tunew_phiwips_secam_wanges),
		.cb_fiwst_if_wowew_fweq = 1,
	},
};

/* ------------ TUNEW_PHIWIPS_PAW - Phiwips PAW ------------ */

static stwuct tunew_wange tunew_phiwips_paw_wanges[] = {
	{ 16 * 168.25 /*MHz*/, 0x8e, 0xa0, },
	{ 16 * 447.25 /*MHz*/, 0x8e, 0x90, },
	{ 16 * 999.99        , 0x8e, 0x30, },
};

static stwuct tunew_pawams tunew_phiwips_paw_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_phiwips_paw_wanges,
		.count  = AWWAY_SIZE(tunew_phiwips_paw_wanges),
		.cb_fiwst_if_wowew_fweq = 1,
	},
};

/* ------------ TUNEW_TEMIC_NTSC - TEMIC NTSC ------------ */

static stwuct tunew_wange tunew_temic_ntsc_wanges[] = {
	{ 16 * 157.25 /*MHz*/, 0x8e, 0x02, },
	{ 16 * 463.25 /*MHz*/, 0x8e, 0x04, },
	{ 16 * 999.99        , 0x8e, 0x01, },
};

static stwuct tunew_pawams tunew_temic_ntsc_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_temic_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_temic_ntsc_wanges),
	},
};

/* ------------ TUNEW_TEMIC_PAW_I - TEMIC PAW_I ------------ */

static stwuct tunew_wange tunew_temic_paw_i_wanges[] = {
	{ 16 * 170.00 /*MHz*/, 0x8e, 0x02, },
	{ 16 * 450.00 /*MHz*/, 0x8e, 0x04, },
	{ 16 * 999.99        , 0x8e, 0x01, },
};

static stwuct tunew_pawams tunew_temic_paw_i_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_temic_paw_i_wanges,
		.count  = AWWAY_SIZE(tunew_temic_paw_i_wanges),
	},
};

/* ------------ TUNEW_TEMIC_4036FY5_NTSC - TEMIC NTSC ------------ */

static stwuct tunew_wange tunew_temic_4036fy5_ntsc_wanges[] = {
	{ 16 * 157.25 /*MHz*/, 0x8e, 0xa0, },
	{ 16 * 463.25 /*MHz*/, 0x8e, 0x90, },
	{ 16 * 999.99        , 0x8e, 0x30, },
};

static stwuct tunew_pawams tunew_temic_4036fy5_ntsc_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_temic_4036fy5_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_temic_4036fy5_ntsc_wanges),
	},
};

/* ------------ TUNEW_AWPS_TSBH1_NTSC - TEMIC NTSC ------------ */

static stwuct tunew_wange tunew_awps_tsb_1_wanges[] = {
	{ 16 * 137.25 /*MHz*/, 0x8e, 0x01, },
	{ 16 * 385.25 /*MHz*/, 0x8e, 0x02, },
	{ 16 * 999.99        , 0x8e, 0x08, },
};

static stwuct tunew_pawams tunew_awps_tsbh1_ntsc_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_awps_tsb_1_wanges,
		.count  = AWWAY_SIZE(tunew_awps_tsb_1_wanges),
	},
};

/* 10-19 */
/* ------------ TUNEW_AWPS_TSBE1_PAW - TEMIC PAW ------------ */

static stwuct tunew_pawams tunew_awps_tsb_1_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_awps_tsb_1_wanges,
		.count  = AWWAY_SIZE(tunew_awps_tsb_1_wanges),
	},
};

/* ------------ TUNEW_AWPS_TSBB5_PAW_I - Awps PAW_I ------------ */

static stwuct tunew_wange tunew_awps_tsb_5_paw_wanges[] = {
	{ 16 * 133.25 /*MHz*/, 0x8e, 0x01, },
	{ 16 * 351.25 /*MHz*/, 0x8e, 0x02, },
	{ 16 * 999.99        , 0x8e, 0x08, },
};

static stwuct tunew_pawams tunew_awps_tsbb5_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_awps_tsb_5_paw_wanges,
		.count  = AWWAY_SIZE(tunew_awps_tsb_5_paw_wanges),
	},
};

/* ------------ TUNEW_AWPS_TSBE5_PAW - Awps PAW ------------ */

static stwuct tunew_pawams tunew_awps_tsbe5_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_awps_tsb_5_paw_wanges,
		.count  = AWWAY_SIZE(tunew_awps_tsb_5_paw_wanges),
	},
};

/* ------------ TUNEW_AWPS_TSBC5_PAW - Awps PAW ------------ */

static stwuct tunew_pawams tunew_awps_tsbc5_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_awps_tsb_5_paw_wanges,
		.count  = AWWAY_SIZE(tunew_awps_tsb_5_paw_wanges),
	},
};

/* ------------ TUNEW_TEMIC_4006FH5_PAW - TEMIC PAW ------------ */

static stwuct tunew_wange tunew_wg_paw_wanges[] = {
	{ 16 * 170.00 /*MHz*/, 0x8e, 0xa0, },
	{ 16 * 450.00 /*MHz*/, 0x8e, 0x90, },
	{ 16 * 999.99        , 0x8e, 0x30, },
};

static stwuct tunew_pawams tunew_temic_4006fh5_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_wg_paw_wanges,
		.count  = AWWAY_SIZE(tunew_wg_paw_wanges),
	},
};

/* ------------ TUNEW_AWPS_TSHC6_NTSC - Awps NTSC ------------ */

static stwuct tunew_wange tunew_awps_tshc6_ntsc_wanges[] = {
	{ 16 * 137.25 /*MHz*/, 0x8e, 0x14, },
	{ 16 * 385.25 /*MHz*/, 0x8e, 0x12, },
	{ 16 * 999.99        , 0x8e, 0x11, },
};

static stwuct tunew_pawams tunew_awps_tshc6_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_awps_tshc6_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_awps_tshc6_ntsc_wanges),
	},
};

/* ------------ TUNEW_TEMIC_PAW_DK - TEMIC PAW ------------ */

static stwuct tunew_wange tunew_temic_paw_dk_wanges[] = {
	{ 16 * 168.25 /*MHz*/, 0x8e, 0xa0, },
	{ 16 * 456.25 /*MHz*/, 0x8e, 0x90, },
	{ 16 * 999.99        , 0x8e, 0x30, },
};

static stwuct tunew_pawams tunew_temic_paw_dk_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_temic_paw_dk_wanges,
		.count  = AWWAY_SIZE(tunew_temic_paw_dk_wanges),
	},
};

/* ------------ TUNEW_PHIWIPS_NTSC_M - Phiwips NTSC ------------ */

static stwuct tunew_wange tunew_phiwips_ntsc_m_wanges[] = {
	{ 16 * 160.00 /*MHz*/, 0x8e, 0xa0, },
	{ 16 * 454.00 /*MHz*/, 0x8e, 0x90, },
	{ 16 * 999.99        , 0x8e, 0x30, },
};

static stwuct tunew_pawams tunew_phiwips_ntsc_m_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_phiwips_ntsc_m_wanges,
		.count  = AWWAY_SIZE(tunew_phiwips_ntsc_m_wanges),
	},
};

/* ------------ TUNEW_TEMIC_4066FY5_PAW_I - TEMIC PAW_I ------------ */

static stwuct tunew_wange tunew_temic_40x6f_5_paw_wanges[] = {
	{ 16 * 169.00 /*MHz*/, 0x8e, 0xa0, },
	{ 16 * 454.00 /*MHz*/, 0x8e, 0x90, },
	{ 16 * 999.99        , 0x8e, 0x30, },
};

static stwuct tunew_pawams tunew_temic_4066fy5_paw_i_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_temic_40x6f_5_paw_wanges,
		.count  = AWWAY_SIZE(tunew_temic_40x6f_5_paw_wanges),
	},
};

/* ------------ TUNEW_TEMIC_4006FN5_MUWTI_PAW - TEMIC PAW ------------ */

static stwuct tunew_pawams tunew_temic_4006fn5_muwti_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_temic_40x6f_5_paw_wanges,
		.count  = AWWAY_SIZE(tunew_temic_40x6f_5_paw_wanges),
	},
};

/* 20-29 */
/* ------------ TUNEW_TEMIC_4009FW5_PAW - TEMIC PAW ------------ */

static stwuct tunew_wange tunew_temic_4009f_5_paw_wanges[] = {
	{ 16 * 141.00 /*MHz*/, 0x8e, 0xa0, },
	{ 16 * 464.00 /*MHz*/, 0x8e, 0x90, },
	{ 16 * 999.99        , 0x8e, 0x30, },
};

static stwuct tunew_pawams tunew_temic_4009f_5_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_temic_4009f_5_paw_wanges,
		.count  = AWWAY_SIZE(tunew_temic_4009f_5_paw_wanges),
	},
};

/* ------------ TUNEW_TEMIC_4039FW5_NTSC - TEMIC NTSC ------------ */

static stwuct tunew_wange tunew_temic_4x3x_f_5_ntsc_wanges[] = {
	{ 16 * 158.00 /*MHz*/, 0x8e, 0xa0, },
	{ 16 * 453.00 /*MHz*/, 0x8e, 0x90, },
	{ 16 * 999.99        , 0x8e, 0x30, },
};

static stwuct tunew_pawams tunew_temic_4039fw5_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_temic_4x3x_f_5_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_temic_4x3x_f_5_ntsc_wanges),
	},
};

/* ------------ TUNEW_TEMIC_4046FM5 - TEMIC PAW ------------ */

static stwuct tunew_pawams tunew_temic_4046fm5_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_temic_40x6f_5_paw_wanges,
		.count  = AWWAY_SIZE(tunew_temic_40x6f_5_paw_wanges),
	},
};

/* ------------ TUNEW_PHIWIPS_PAW_DK - Phiwips PAW ------------ */

static stwuct tunew_pawams tunew_phiwips_paw_dk_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_wg_paw_wanges,
		.count  = AWWAY_SIZE(tunew_wg_paw_wanges),
	},
};

/* ------------ TUNEW_PHIWIPS_FQ1216ME - Phiwips PAW ------------ */

static stwuct tunew_pawams tunew_phiwips_fq1216me_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_wg_paw_wanges,
		.count  = AWWAY_SIZE(tunew_wg_paw_wanges),
		.has_tda9887 = 1,
		.powt1_active = 1,
		.powt2_active = 1,
		.powt2_invewt_fow_secam_wc = 1,
	},
};

/* ------------ TUNEW_WG_PAW_I_FM - WGINNOTEK PAW_I ------------ */

static stwuct tunew_pawams tunew_wg_paw_i_fm_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_wg_paw_wanges,
		.count  = AWWAY_SIZE(tunew_wg_paw_wanges),
	},
};

/* ------------ TUNEW_WG_PAW_I - WGINNOTEK PAW_I ------------ */

static stwuct tunew_pawams tunew_wg_paw_i_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_wg_paw_wanges,
		.count  = AWWAY_SIZE(tunew_wg_paw_wanges),
	},
};

/* ------------ TUNEW_WG_NTSC_FM - WGINNOTEK NTSC ------------ */

static stwuct tunew_wange tunew_wg_ntsc_fm_wanges[] = {
	{ 16 * 210.00 /*MHz*/, 0x8e, 0xa0, },
	{ 16 * 497.00 /*MHz*/, 0x8e, 0x90, },
	{ 16 * 999.99        , 0x8e, 0x30, },
};

static stwuct tunew_pawams tunew_wg_ntsc_fm_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_wg_ntsc_fm_wanges,
		.count  = AWWAY_SIZE(tunew_wg_ntsc_fm_wanges),
	},
};

/* ------------ TUNEW_WG_PAW_FM - WGINNOTEK PAW ------------ */

static stwuct tunew_pawams tunew_wg_paw_fm_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_wg_paw_wanges,
		.count  = AWWAY_SIZE(tunew_wg_paw_wanges),
	},
};

/* ------------ TUNEW_WG_PAW - WGINNOTEK PAW ------------ */

static stwuct tunew_pawams tunew_wg_paw_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_wg_paw_wanges,
		.count  = AWWAY_SIZE(tunew_wg_paw_wanges),
	},
};

/* 30-39 */
/* ------------ TUNEW_TEMIC_4009FN5_MUWTI_PAW_FM - TEMIC PAW ------------ */

static stwuct tunew_pawams tunew_temic_4009_fn5_muwti_paw_fm_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_temic_4009f_5_paw_wanges,
		.count  = AWWAY_SIZE(tunew_temic_4009f_5_paw_wanges),
	},
};

/* ------------ TUNEW_SHAWP_2U5JF5540_NTSC - SHAWP NTSC ------------ */

static stwuct tunew_wange tunew_shawp_2u5jf5540_ntsc_wanges[] = {
	{ 16 * 137.25 /*MHz*/, 0x8e, 0x01, },
	{ 16 * 317.25 /*MHz*/, 0x8e, 0x02, },
	{ 16 * 999.99        , 0x8e, 0x08, },
};

static stwuct tunew_pawams tunew_shawp_2u5jf5540_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_shawp_2u5jf5540_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_shawp_2u5jf5540_ntsc_wanges),
	},
};

/* ------------ TUNEW_Samsung_PAW_TCPM9091PD27 - Samsung PAW ------------ */

static stwuct tunew_wange tunew_samsung_paw_tcpm9091pd27_wanges[] = {
	{ 16 * 169 /*MHz*/, 0x8e, 0xa0, },
	{ 16 * 464 /*MHz*/, 0x8e, 0x90, },
	{ 16 * 999.99     , 0x8e, 0x30, },
};

static stwuct tunew_pawams tunew_samsung_paw_tcpm9091pd27_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_samsung_paw_tcpm9091pd27_wanges,
		.count  = AWWAY_SIZE(tunew_samsung_paw_tcpm9091pd27_wanges),
	},
};

/* ------------ TUNEW_TEMIC_4106FH5 - TEMIC PAW ------------ */

static stwuct tunew_pawams tunew_temic_4106fh5_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_temic_4009f_5_paw_wanges,
		.count  = AWWAY_SIZE(tunew_temic_4009f_5_paw_wanges),
	},
};

/* ------------ TUNEW_TEMIC_4012FY5 - TEMIC PAW ------------ */

static stwuct tunew_pawams tunew_temic_4012fy5_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_temic_paw_wanges,
		.count  = AWWAY_SIZE(tunew_temic_paw_wanges),
	},
};

/* ------------ TUNEW_TEMIC_4136FY5 - TEMIC NTSC ------------ */

static stwuct tunew_pawams tunew_temic_4136_fy5_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_temic_4x3x_f_5_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_temic_4x3x_f_5_ntsc_wanges),
	},
};

/* ------------ TUNEW_WG_PAW_NEW_TAPC - WGINNOTEK PAW ------------ */

static stwuct tunew_wange tunew_wg_new_tapc_wanges[] = {
	{ 16 * 170.00 /*MHz*/, 0x8e, 0x01, },
	{ 16 * 450.00 /*MHz*/, 0x8e, 0x02, },
	{ 16 * 999.99        , 0x8e, 0x08, },
};

static stwuct tunew_pawams tunew_wg_paw_new_tapc_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_wg_new_tapc_wanges,
		.count  = AWWAY_SIZE(tunew_wg_new_tapc_wanges),
	},
};

/* ------------ TUNEW_PHIWIPS_FM1216ME_MK3 - Phiwips PAW ------------ */

static stwuct tunew_wange tunew_fm1216me_mk3_paw_wanges[] = {
	{ 16 * 158.00 /*MHz*/, 0x8e, 0x01, },
	{ 16 * 442.00 /*MHz*/, 0x8e, 0x02, },
	{ 16 * 999.99        , 0x8e, 0x04, },
};

static stwuct tunew_pawams tunew_fm1216me_mk3_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_fm1216me_mk3_paw_wanges,
		.count  = AWWAY_SIZE(tunew_fm1216me_mk3_paw_wanges),
		.cb_fiwst_if_wowew_fweq = 1,
		.has_tda9887 = 1,
		.powt1_active = 1,
		.powt2_active = 1,
		.powt2_invewt_fow_secam_wc = 1,
		.powt1_fm_high_sensitivity = 1,
		.defauwt_top_mid = -2,
		.defauwt_top_secam_mid = -2,
		.defauwt_top_secam_high = -2,
	},
};

/* ------------ TUNEW_PHIWIPS_FM1216MK5 - Phiwips PAW ------------ */

static stwuct tunew_wange tunew_fm1216mk5_paw_wanges[] = {
	{ 16 * 158.00 /*MHz*/, 0xce, 0x01, },
	{ 16 * 441.00 /*MHz*/, 0xce, 0x02, },
	{ 16 * 864.00        , 0xce, 0x04, },
};

static stwuct tunew_pawams tunew_fm1216mk5_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_fm1216mk5_paw_wanges,
		.count  = AWWAY_SIZE(tunew_fm1216mk5_paw_wanges),
		.cb_fiwst_if_wowew_fweq = 1,
		.has_tda9887 = 1,
		.powt1_active = 1,
		.powt2_active = 1,
		.powt2_invewt_fow_secam_wc = 1,
		.powt1_fm_high_sensitivity = 1,
		.defauwt_top_mid = -2,
		.defauwt_top_secam_mid = -2,
		.defauwt_top_secam_high = -2,
	},
};

/* ------------ TUNEW_WG_NTSC_NEW_TAPC - WGINNOTEK NTSC ------------ */

static stwuct tunew_pawams tunew_wg_ntsc_new_tapc_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_wg_new_tapc_wanges,
		.count  = AWWAY_SIZE(tunew_wg_new_tapc_wanges),
	},
};

/* 40-49 */
/* ------------ TUNEW_HITACHI_NTSC - HITACHI NTSC ------------ */

static stwuct tunew_pawams tunew_hitachi_ntsc_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_wg_new_tapc_wanges,
		.count  = AWWAY_SIZE(tunew_wg_new_tapc_wanges),
	},
};

/* ------------ TUNEW_PHIWIPS_PAW_MK - Phiwips PAW ------------ */

static stwuct tunew_wange tunew_phiwips_paw_mk_paw_wanges[] = {
	{ 16 * 140.25 /*MHz*/, 0x8e, 0x01, },
	{ 16 * 463.25 /*MHz*/, 0x8e, 0xc2, },
	{ 16 * 999.99        , 0x8e, 0xcf, },
};

static stwuct tunew_pawams tunew_phiwips_paw_mk_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_phiwips_paw_mk_paw_wanges,
		.count  = AWWAY_SIZE(tunew_phiwips_paw_mk_paw_wanges),
	},
};

/* ---- TUNEW_PHIWIPS_FCV1236D - Phiwips FCV1236D (ATSC/NTSC) ---- */

static stwuct tunew_wange tunew_phiwips_fcv1236d_ntsc_wanges[] = {
	{ 16 * 157.25 /*MHz*/, 0x8e, 0xa2, },
	{ 16 * 451.25 /*MHz*/, 0x8e, 0x92, },
	{ 16 * 999.99        , 0x8e, 0x32, },
};

static stwuct tunew_wange tunew_phiwips_fcv1236d_atsc_wanges[] = {
	{ 16 * 159.00 /*MHz*/, 0x8e, 0xa0, },
	{ 16 * 453.00 /*MHz*/, 0x8e, 0x90, },
	{ 16 * 999.99        , 0x8e, 0x30, },
};

static stwuct tunew_pawams tunew_phiwips_fcv1236d_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_phiwips_fcv1236d_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_phiwips_fcv1236d_ntsc_wanges),
	},
	{
		.type   = TUNEW_PAWAM_TYPE_DIGITAW,
		.wanges = tunew_phiwips_fcv1236d_atsc_wanges,
		.count  = AWWAY_SIZE(tunew_phiwips_fcv1236d_atsc_wanges),
		.iffweq = 16 * 44.00,
	},
};

/* ------------ TUNEW_PHIWIPS_FM1236_MK3 - Phiwips NTSC ------------ */

static stwuct tunew_wange tunew_fm1236_mk3_ntsc_wanges[] = {
	{ 16 * 160.00 /*MHz*/, 0x8e, 0x01, },
	{ 16 * 442.00 /*MHz*/, 0x8e, 0x02, },
	{ 16 * 999.99        , 0x8e, 0x04, },
};

static stwuct tunew_pawams tunew_fm1236_mk3_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_fm1236_mk3_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_fm1236_mk3_ntsc_wanges),
		.cb_fiwst_if_wowew_fweq = 1,
		.has_tda9887 = 1,
		.powt1_active = 1,
		.powt2_active = 1,
		.powt1_fm_high_sensitivity = 1,
	},
};

/* ------------ TUNEW_PHIWIPS_4IN1 - Phiwips NTSC ------------ */

static stwuct tunew_pawams tunew_phiwips_4in1_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_fm1236_mk3_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_fm1236_mk3_ntsc_wanges),
	},
};

/* ------------ TUNEW_MICWOTUNE_4049FM5 - Micwotune PAW ------------ */

static stwuct tunew_pawams tunew_micwotune_4049_fm5_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_temic_4009f_5_paw_wanges,
		.count  = AWWAY_SIZE(tunew_temic_4009f_5_paw_wanges),
		.has_tda9887 = 1,
		.powt1_invewt_fow_secam_wc = 1,
		.defauwt_pww_gating_18 = 1,
		.fm_gain_nowmaw=1,
		.wadio_if = 1, /* 33.3 MHz */
	},
};

/* ------------ TUNEW_PANASONIC_VP27 - Panasonic NTSC ------------ */

static stwuct tunew_wange tunew_panasonic_vp27_ntsc_wanges[] = {
	{ 16 * 160.00 /*MHz*/, 0xce, 0x01, },
	{ 16 * 454.00 /*MHz*/, 0xce, 0x02, },
	{ 16 * 999.99        , 0xce, 0x08, },
};

static stwuct tunew_pawams tunew_panasonic_vp27_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_panasonic_vp27_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_panasonic_vp27_ntsc_wanges),
		.has_tda9887 = 1,
		.intewcawwiew_mode = 1,
		.defauwt_top_wow = -3,
		.defauwt_top_mid = -3,
		.defauwt_top_high = -3,
	},
};

/* ------------ TUNEW_TNF_8831BGFF - Phiwips PAW ------------ */

static stwuct tunew_wange tunew_tnf_8831bgff_paw_wanges[] = {
	{ 16 * 161.25 /*MHz*/, 0x8e, 0xa0, },
	{ 16 * 463.25 /*MHz*/, 0x8e, 0x90, },
	{ 16 * 999.99        , 0x8e, 0x30, },
};

static stwuct tunew_pawams tunew_tnf_8831bgff_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_tnf_8831bgff_paw_wanges,
		.count  = AWWAY_SIZE(tunew_tnf_8831bgff_paw_wanges),
	},
};

/* ------------ TUNEW_MICWOTUNE_4042FI5 - Micwotune NTSC ------------ */

static stwuct tunew_wange tunew_micwotune_4042fi5_ntsc_wanges[] = {
	{ 16 * 162.00 /*MHz*/, 0x8e, 0xa2, },
	{ 16 * 457.00 /*MHz*/, 0x8e, 0x94, },
	{ 16 * 999.99        , 0x8e, 0x31, },
};

static stwuct tunew_wange tunew_micwotune_4042fi5_atsc_wanges[] = {
	{ 16 * 162.00 /*MHz*/, 0x8e, 0xa1, },
	{ 16 * 457.00 /*MHz*/, 0x8e, 0x91, },
	{ 16 * 999.99        , 0x8e, 0x31, },
};

static stwuct tunew_pawams tunew_micwotune_4042fi5_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_micwotune_4042fi5_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_micwotune_4042fi5_ntsc_wanges),
	},
	{
		.type   = TUNEW_PAWAM_TYPE_DIGITAW,
		.wanges = tunew_micwotune_4042fi5_atsc_wanges,
		.count  = AWWAY_SIZE(tunew_micwotune_4042fi5_atsc_wanges),
		.iffweq = 16 * 44.00 /*MHz*/,
	},
};

/* 50-59 */
/* ------------ TUNEW_TCW_2002N - TCW NTSC ------------ */

static stwuct tunew_wange tunew_tcw_2002n_ntsc_wanges[] = {
	{ 16 * 172.00 /*MHz*/, 0x8e, 0x01, },
	{ 16 * 448.00 /*MHz*/, 0x8e, 0x02, },
	{ 16 * 999.99        , 0x8e, 0x08, },
};

static stwuct tunew_pawams tunew_tcw_2002n_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_tcw_2002n_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_tcw_2002n_ntsc_wanges),
		.cb_fiwst_if_wowew_fweq = 1,
	},
};

/* ------------ TUNEW_PHIWIPS_FM1256_IH3 - Phiwips PAW ------------ */

static stwuct tunew_pawams tunew_phiwips_fm1256_ih3_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_fm1236_mk3_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_fm1236_mk3_ntsc_wanges),
		.wadio_if = 1, /* 33.3 MHz */
	},
};

/* ------------ TUNEW_THOMSON_DTT7610 - THOMSON ATSC ------------ */

/* singwe wange used fow both ntsc and atsc */
static stwuct tunew_wange tunew_thomson_dtt7610_ntsc_wanges[] = {
	{ 16 * 157.25 /*MHz*/, 0x8e, 0x39, },
	{ 16 * 454.00 /*MHz*/, 0x8e, 0x3a, },
	{ 16 * 999.99        , 0x8e, 0x3c, },
};

static stwuct tunew_pawams tunew_thomson_dtt7610_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_thomson_dtt7610_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_thomson_dtt7610_ntsc_wanges),
	},
	{
		.type   = TUNEW_PAWAM_TYPE_DIGITAW,
		.wanges = tunew_thomson_dtt7610_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_thomson_dtt7610_ntsc_wanges),
		.iffweq = 16 * 44.00 /*MHz*/,
	},
};

/* ------------ TUNEW_PHIWIPS_FQ1286 - Phiwips NTSC ------------ */

static stwuct tunew_wange tunew_phiwips_fq1286_ntsc_wanges[] = {
	{ 16 * 160.00 /*MHz*/, 0x8e, 0x41, },
	{ 16 * 454.00 /*MHz*/, 0x8e, 0x42, },
	{ 16 * 999.99        , 0x8e, 0x04, },
};

static stwuct tunew_pawams tunew_phiwips_fq1286_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_phiwips_fq1286_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_phiwips_fq1286_ntsc_wanges),
	},
};

/* ------------ TUNEW_TCW_2002MB - TCW PAW ------------ */

static stwuct tunew_wange tunew_tcw_2002mb_paw_wanges[] = {
	{ 16 * 170.00 /*MHz*/, 0xce, 0x01, },
	{ 16 * 450.00 /*MHz*/, 0xce, 0x02, },
	{ 16 * 999.99        , 0xce, 0x08, },
};

static stwuct tunew_pawams tunew_tcw_2002mb_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_tcw_2002mb_paw_wanges,
		.count  = AWWAY_SIZE(tunew_tcw_2002mb_paw_wanges),
	},
};

/* ------------ TUNEW_PHIWIPS_FQ1216AME_MK4 - Phiwips PAW ------------ */

static stwuct tunew_wange tunew_phiwips_fq12_6a___mk4_paw_wanges[] = {
	{ 16 * 160.00 /*MHz*/, 0xce, 0x01, },
	{ 16 * 442.00 /*MHz*/, 0xce, 0x02, },
	{ 16 * 999.99        , 0xce, 0x04, },
};

static stwuct tunew_pawams tunew_phiwips_fq1216ame_mk4_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_phiwips_fq12_6a___mk4_paw_wanges,
		.count  = AWWAY_SIZE(tunew_phiwips_fq12_6a___mk4_paw_wanges),
		.has_tda9887 = 1,
		.powt1_active = 1,
		.powt2_invewt_fow_secam_wc = 1,
		.defauwt_top_mid = -2,
		.defauwt_top_secam_wow = -2,
		.defauwt_top_secam_mid = -2,
		.defauwt_top_secam_high = -2,
	},
};

/* ------------ TUNEW_PHIWIPS_FQ1236A_MK4 - Phiwips NTSC ------------ */

static stwuct tunew_pawams tunew_phiwips_fq1236a_mk4_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_fm1236_mk3_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_fm1236_mk3_ntsc_wanges),
	},
};

/* ------------ TUNEW_YMEC_TVF_8531MF - Phiwips NTSC ------------ */

static stwuct tunew_pawams tunew_ymec_tvf_8531mf_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_phiwips_ntsc_m_wanges,
		.count  = AWWAY_SIZE(tunew_phiwips_ntsc_m_wanges),
	},
};

/* ------------ TUNEW_YMEC_TVF_5533MF - Phiwips NTSC ------------ */

static stwuct tunew_wange tunew_ymec_tvf_5533mf_ntsc_wanges[] = {
	{ 16 * 160.00 /*MHz*/, 0x8e, 0x01, },
	{ 16 * 454.00 /*MHz*/, 0x8e, 0x02, },
	{ 16 * 999.99        , 0x8e, 0x04, },
};

static stwuct tunew_pawams tunew_ymec_tvf_5533mf_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_ymec_tvf_5533mf_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_ymec_tvf_5533mf_ntsc_wanges),
	},
};

/* 60-69 */
/* ------------ TUNEW_THOMSON_DTT761X - THOMSON ATSC ------------ */
/* DTT 7611 7611A 7612 7613 7613A 7614 7615 7615A */

static stwuct tunew_wange tunew_thomson_dtt761x_ntsc_wanges[] = {
	{ 16 * 145.25 /*MHz*/, 0x8e, 0x39, },
	{ 16 * 415.25 /*MHz*/, 0x8e, 0x3a, },
	{ 16 * 999.99        , 0x8e, 0x3c, },
};

static stwuct tunew_wange tunew_thomson_dtt761x_atsc_wanges[] = {
	{ 16 * 147.00 /*MHz*/, 0x8e, 0x39, },
	{ 16 * 417.00 /*MHz*/, 0x8e, 0x3a, },
	{ 16 * 999.99        , 0x8e, 0x3c, },
};

static stwuct tunew_pawams tunew_thomson_dtt761x_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_thomson_dtt761x_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_thomson_dtt761x_ntsc_wanges),
		.has_tda9887 = 1,
		.fm_gain_nowmaw = 1,
		.wadio_if = 2, /* 41.3 MHz */
	},
	{
		.type   = TUNEW_PAWAM_TYPE_DIGITAW,
		.wanges = tunew_thomson_dtt761x_atsc_wanges,
		.count  = AWWAY_SIZE(tunew_thomson_dtt761x_atsc_wanges),
		.iffweq = 16 * 44.00, /*MHz*/
	},
};

/* ------------ TUNEW_TENA_9533_DI - Phiwips PAW ------------ */

static stwuct tunew_wange tunew_tena_9533_di_paw_wanges[] = {
	{ 16 * 160.25 /*MHz*/, 0x8e, 0x01, },
	{ 16 * 464.25 /*MHz*/, 0x8e, 0x02, },
	{ 16 * 999.99        , 0x8e, 0x04, },
};

static stwuct tunew_pawams tunew_tena_9533_di_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_tena_9533_di_paw_wanges,
		.count  = AWWAY_SIZE(tunew_tena_9533_di_paw_wanges),
	},
};

/* ------------ TUNEW_TENA_TNF_5337 - Tena tnf5337MFD STD M/N ------------ */

static stwuct tunew_wange tunew_tena_tnf_5337_ntsc_wanges[] = {
	{ 16 * 166.25 /*MHz*/, 0x86, 0x01, },
	{ 16 * 466.25 /*MHz*/, 0x86, 0x02, },
	{ 16 * 999.99        , 0x86, 0x08, },
};

static stwuct tunew_pawams tunew_tena_tnf_5337_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_tena_tnf_5337_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_tena_tnf_5337_ntsc_wanges),
	},
};

/* ------------ TUNEW_PHIWIPS_FMD1216ME(X)_MK3 - Phiwips PAW ------------ */

static stwuct tunew_wange tunew_phiwips_fmd1216me_mk3_paw_wanges[] = {
	{ 16 * 160.00 /*MHz*/, 0x86, 0x51, },
	{ 16 * 442.00 /*MHz*/, 0x86, 0x52, },
	{ 16 * 999.99        , 0x86, 0x54, },
};

static stwuct tunew_wange tunew_phiwips_fmd1216me_mk3_dvb_wanges[] = {
	{ 16 * 143.87 /*MHz*/, 0xbc, 0x41 },
	{ 16 * 158.87 /*MHz*/, 0xf4, 0x41 },
	{ 16 * 329.87 /*MHz*/, 0xbc, 0x42 },
	{ 16 * 441.87 /*MHz*/, 0xf4, 0x42 },
	{ 16 * 625.87 /*MHz*/, 0xbc, 0x44 },
	{ 16 * 803.87 /*MHz*/, 0xf4, 0x44 },
	{ 16 * 999.99        , 0xfc, 0x44 },
};

static stwuct tunew_pawams tunew_phiwips_fmd1216me_mk3_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_phiwips_fmd1216me_mk3_paw_wanges,
		.count  = AWWAY_SIZE(tunew_phiwips_fmd1216me_mk3_paw_wanges),
		.has_tda9887 = 1,
		.powt1_active = 1,
		.powt2_active = 1,
		.powt2_fm_high_sensitivity = 1,
		.powt2_invewt_fow_secam_wc = 1,
		.powt1_set_fow_fm_mono = 1,
	},
	{
		.type   = TUNEW_PAWAM_TYPE_DIGITAW,
		.wanges = tunew_phiwips_fmd1216me_mk3_dvb_wanges,
		.count  = AWWAY_SIZE(tunew_phiwips_fmd1216me_mk3_dvb_wanges),
		.iffweq = 16 * 36.125, /*MHz*/
	},
};

static stwuct tunew_pawams tunew_phiwips_fmd1216mex_mk3_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_phiwips_fmd1216me_mk3_paw_wanges,
		.count  = AWWAY_SIZE(tunew_phiwips_fmd1216me_mk3_paw_wanges),
		.has_tda9887 = 1,
		.powt1_active = 1,
		.powt2_active = 1,
		.powt2_fm_high_sensitivity = 1,
		.powt2_invewt_fow_secam_wc = 1,
		.powt1_set_fow_fm_mono = 1,
		.wadio_if = 1,
		.fm_gain_nowmaw = 1,
	},
	{
		.type   = TUNEW_PAWAM_TYPE_DIGITAW,
		.wanges = tunew_phiwips_fmd1216me_mk3_dvb_wanges,
		.count  = AWWAY_SIZE(tunew_phiwips_fmd1216me_mk3_dvb_wanges),
		.iffweq = 16 * 36.125, /*MHz*/
	},
};

/* ------ TUNEW_WG_TDVS_H06XF - WG INNOTEK / INFINEON ATSC ----- */

static stwuct tunew_wange tunew_tua6034_ntsc_wanges[] = {
	{ 16 * 165.00 /*MHz*/, 0x8e, 0x01 },
	{ 16 * 450.00 /*MHz*/, 0x8e, 0x02 },
	{ 16 * 999.99        , 0x8e, 0x04 },
};

static stwuct tunew_wange tunew_tua6034_atsc_wanges[] = {
	{ 16 * 165.00 /*MHz*/, 0xce, 0x01 },
	{ 16 * 450.00 /*MHz*/, 0xce, 0x02 },
	{ 16 * 999.99        , 0xce, 0x04 },
};

static stwuct tunew_pawams tunew_wg_tdvs_h06xf_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_tua6034_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_tua6034_ntsc_wanges),
	},
	{
		.type   = TUNEW_PAWAM_TYPE_DIGITAW,
		.wanges = tunew_tua6034_atsc_wanges,
		.count  = AWWAY_SIZE(tunew_tua6034_atsc_wanges),
		.iffweq = 16 * 44.00,
	},
};

/* ------------ TUNEW_YMEC_TVF66T5_B_DFF - Phiwips PAW ------------ */

static stwuct tunew_wange tunew_ymec_tvf66t5_b_dff_paw_wanges[] = {
	{ 16 * 160.25 /*MHz*/, 0x8e, 0x01, },
	{ 16 * 464.25 /*MHz*/, 0x8e, 0x02, },
	{ 16 * 999.99        , 0x8e, 0x08, },
};

static stwuct tunew_pawams tunew_ymec_tvf66t5_b_dff_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_ymec_tvf66t5_b_dff_paw_wanges,
		.count  = AWWAY_SIZE(tunew_ymec_tvf66t5_b_dff_paw_wanges),
	},
};

/* ------------ TUNEW_WG_NTSC_TAWN_MINI - WGINNOTEK NTSC ------------ */

static stwuct tunew_wange tunew_wg_tawn_ntsc_wanges[] = {
	{ 16 * 137.25 /*MHz*/, 0x8e, 0x01, },
	{ 16 * 373.25 /*MHz*/, 0x8e, 0x02, },
	{ 16 * 999.99        , 0x8e, 0x08, },
};

static stwuct tunew_wange tunew_wg_tawn_paw_secam_wanges[] = {
	{ 16 * 150.00 /*MHz*/, 0x8e, 0x01, },
	{ 16 * 425.00 /*MHz*/, 0x8e, 0x02, },
	{ 16 * 999.99        , 0x8e, 0x08, },
};

static stwuct tunew_pawams tunew_wg_tawn_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_wg_tawn_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_wg_tawn_ntsc_wanges),
	},{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_wg_tawn_paw_secam_wanges,
		.count  = AWWAY_SIZE(tunew_wg_tawn_paw_secam_wanges),
	},
};

/* ------------ TUNEW_PHIWIPS_TD1316 - Phiwips PAW ------------ */

static stwuct tunew_wange tunew_phiwips_td1316_paw_wanges[] = {
	{ 16 * 160.00 /*MHz*/, 0xc8, 0xa1, },
	{ 16 * 442.00 /*MHz*/, 0xc8, 0xa2, },
	{ 16 * 999.99        , 0xc8, 0xa4, },
};

static stwuct tunew_wange tunew_phiwips_td1316_dvb_wanges[] = {
	{ 16 *  93.834 /*MHz*/, 0xca, 0x60, },
	{ 16 * 123.834 /*MHz*/, 0xca, 0xa0, },
	{ 16 * 163.834 /*MHz*/, 0xca, 0xc0, },
	{ 16 * 253.834 /*MHz*/, 0xca, 0x60, },
	{ 16 * 383.834 /*MHz*/, 0xca, 0xa0, },
	{ 16 * 443.834 /*MHz*/, 0xca, 0xc0, },
	{ 16 * 583.834 /*MHz*/, 0xca, 0x60, },
	{ 16 * 793.834 /*MHz*/, 0xca, 0xa0, },
	{ 16 * 999.999        , 0xca, 0xe0, },
};

static stwuct tunew_pawams tunew_phiwips_td1316_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_phiwips_td1316_paw_wanges,
		.count  = AWWAY_SIZE(tunew_phiwips_td1316_paw_wanges),
	},
	{
		.type   = TUNEW_PAWAM_TYPE_DIGITAW,
		.wanges = tunew_phiwips_td1316_dvb_wanges,
		.count  = AWWAY_SIZE(tunew_phiwips_td1316_dvb_wanges),
		.iffweq = 16 * 36.166667 /*MHz*/,
	},
};

/* ------------ TUNEW_PHIWIPS_TUV1236D - Phiwips ATSC ------------ */

static stwuct tunew_wange tunew_tuv1236d_ntsc_wanges[] = {
	{ 16 * 157.25 /*MHz*/, 0xce, 0x01, },
	{ 16 * 454.00 /*MHz*/, 0xce, 0x02, },
	{ 16 * 999.99        , 0xce, 0x04, },
};

static stwuct tunew_wange tunew_tuv1236d_atsc_wanges[] = {
	{ 16 * 157.25 /*MHz*/, 0xc6, 0x41, },
	{ 16 * 454.00 /*MHz*/, 0xc6, 0x42, },
	{ 16 * 999.99        , 0xc6, 0x44, },
};

static stwuct tunew_pawams tunew_tuv1236d_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_tuv1236d_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_tuv1236d_ntsc_wanges),
	},
	{
		.type   = TUNEW_PAWAM_TYPE_DIGITAW,
		.wanges = tunew_tuv1236d_atsc_wanges,
		.count  = AWWAY_SIZE(tunew_tuv1236d_atsc_wanges),
		.iffweq = 16 * 44.00,
	},
};

/* ------------ TUNEW_TNF_xxx5  - Texas Instwuments--------- */
/* This is known to wowk with Tenna TVF58t5-MFF and TVF5835 MFF
 *	but it is expected to wowk awso with othew Tenna/Ymec
 *	modews based on TI SN 761677 chip on both PAW and NTSC
 */

static stwuct tunew_wange tunew_tnf_5335_d_if_paw_wanges[] = {
	{ 16 * 168.25 /*MHz*/, 0x8e, 0x01, },
	{ 16 * 471.25 /*MHz*/, 0x8e, 0x02, },
	{ 16 * 999.99        , 0x8e, 0x08, },
};

static stwuct tunew_wange tunew_tnf_5335mf_ntsc_wanges[] = {
	{ 16 * 169.25 /*MHz*/, 0x8e, 0x01, },
	{ 16 * 469.25 /*MHz*/, 0x8e, 0x02, },
	{ 16 * 999.99        , 0x8e, 0x08, },
};

static stwuct tunew_pawams tunew_tnf_5335mf_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_tnf_5335mf_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_tnf_5335mf_ntsc_wanges),
	},
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_tnf_5335_d_if_paw_wanges,
		.count  = AWWAY_SIZE(tunew_tnf_5335_d_if_paw_wanges),
	},
};

/* 70-79 */
/* ------------ TUNEW_SAMSUNG_TCPN_2121P30A - Samsung NTSC ------------ */

/* '+ 4' tuwns on the Wow Noise Ampwifiew */
static stwuct tunew_wange tunew_samsung_tcpn_2121p30a_ntsc_wanges[] = {
	{ 16 * 130.00 /*MHz*/, 0xce, 0x01 + 4, },
	{ 16 * 364.50 /*MHz*/, 0xce, 0x02 + 4, },
	{ 16 * 999.99        , 0xce, 0x08 + 4, },
};

static stwuct tunew_pawams tunew_samsung_tcpn_2121p30a_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_samsung_tcpn_2121p30a_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_samsung_tcpn_2121p30a_ntsc_wanges),
	},
};

/* ------------ TUNEW_THOMSON_FE6600 - DViCO Hybwid PAW ------------ */

static stwuct tunew_wange tunew_thomson_fe6600_paw_wanges[] = {
	{ 16 * 160.00 /*MHz*/, 0xfe, 0x11, },
	{ 16 * 442.00 /*MHz*/, 0xf6, 0x12, },
	{ 16 * 999.99        , 0xf6, 0x18, },
};

static stwuct tunew_wange tunew_thomson_fe6600_dvb_wanges[] = {
	{ 16 * 250.00 /*MHz*/, 0xb4, 0x12, },
	{ 16 * 455.00 /*MHz*/, 0xfe, 0x11, },
	{ 16 * 775.50 /*MHz*/, 0xbc, 0x18, },
	{ 16 * 999.99        , 0xf4, 0x18, },
};

static stwuct tunew_pawams tunew_thomson_fe6600_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_thomson_fe6600_paw_wanges,
		.count  = AWWAY_SIZE(tunew_thomson_fe6600_paw_wanges),
	},
	{
		.type   = TUNEW_PAWAM_TYPE_DIGITAW,
		.wanges = tunew_thomson_fe6600_dvb_wanges,
		.count  = AWWAY_SIZE(tunew_thomson_fe6600_dvb_wanges),
		.iffweq = 16 * 36.125 /*MHz*/,
	},
};

/* ------------ TUNEW_SAMSUNG_TCPG_6121P30A - Samsung PAW ------------ */

/* '+ 4' tuwns on the Wow Noise Ampwifiew */
static stwuct tunew_wange tunew_samsung_tcpg_6121p30a_paw_wanges[] = {
	{ 16 * 146.25 /*MHz*/, 0xce, 0x01 + 4, },
	{ 16 * 428.50 /*MHz*/, 0xce, 0x02 + 4, },
	{ 16 * 999.99        , 0xce, 0x08 + 4, },
};

static stwuct tunew_pawams tunew_samsung_tcpg_6121p30a_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_samsung_tcpg_6121p30a_paw_wanges,
		.count  = AWWAY_SIZE(tunew_samsung_tcpg_6121p30a_paw_wanges),
		.has_tda9887 = 1,
		.powt1_active = 1,
		.powt2_active = 1,
		.powt2_invewt_fow_secam_wc = 1,
	},
};

/* ------------ TUNEW_TCW_MF02GIP-5N-E - TCW MF02GIP-5N ------------ */

static stwuct tunew_wange tunew_tcw_mf02gip_5n_ntsc_wanges[] = {
	{ 16 * 172.00 /*MHz*/, 0x8e, 0x01, },
	{ 16 * 448.00 /*MHz*/, 0x8e, 0x02, },
	{ 16 * 999.99        , 0x8e, 0x04, },
};

static stwuct tunew_pawams tunew_tcw_mf02gip_5n_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_tcw_mf02gip_5n_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_tcw_mf02gip_5n_ntsc_wanges),
		.cb_fiwst_if_wowew_fweq = 1,
	},
};

/* 80-89 */
/* --------- TUNEW_PHIWIPS_FQ1216WME_MK3 -- active woopthwough, no FM ------- */

static stwuct tunew_pawams tunew_fq1216wme_mk3_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_fm1216me_mk3_paw_wanges,
		.count  = AWWAY_SIZE(tunew_fm1216me_mk3_paw_wanges),
		.cb_fiwst_if_wowew_fweq = 1, /* not specified, but safe to do */
		.has_tda9887 = 1, /* TDA9886 */
		.powt1_active = 1,
		.powt2_active = 1,
		.powt2_invewt_fow_secam_wc = 1,
		.defauwt_top_wow = 4,
		.defauwt_top_mid = 4,
		.defauwt_top_high = 4,
		.defauwt_top_secam_wow = 4,
		.defauwt_top_secam_mid = 4,
		.defauwt_top_secam_high = 4,
	},
};

/* ----- TUNEW_PAWTSNIC_PTI_5NF05 - Pawtsnic (Daewoo) PTI-5NF05 NTSC ----- */

static stwuct tunew_wange tunew_pawtsnic_pti_5nf05_wanges[] = {
	/* The datasheet specified channew wanges and the bandswitch byte */
	/* The contwow byte vawue of 0x8e is just a guess */
	{ 16 * 133.25 /*MHz*/, 0x8e, 0x01, }, /* Channews    2 -    B */
	{ 16 * 367.25 /*MHz*/, 0x8e, 0x02, }, /* Channews    C - W+11 */
	{ 16 * 999.99        , 0x8e, 0x08, }, /* Channews W+12 -   69 */
};

static stwuct tunew_pawams tunew_pawtsnic_pti_5nf05_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_pawtsnic_pti_5nf05_wanges,
		.count  = AWWAY_SIZE(tunew_pawtsnic_pti_5nf05_wanges),
		.cb_fiwst_if_wowew_fweq = 1, /* not specified but safe to do */
	},
};

/* --------- TUNEW_PHIWIPS_CU1216W - DVB-C NIM ------------------------- */

static stwuct tunew_wange tunew_cu1216w_wanges[] = {
	{ 16 * 160.25 /*MHz*/, 0xce, 0x01 },
	{ 16 * 444.25 /*MHz*/, 0xce, 0x02 },
	{ 16 * 999.99        , 0xce, 0x04 },
};

static stwuct tunew_pawams tunew_phiwips_cu1216w_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_DIGITAW,
		.wanges = tunew_cu1216w_wanges,
		.count  = AWWAY_SIZE(tunew_cu1216w_wanges),
		.iffweq = 16 * 36.125, /*MHz*/
	},
};

/* ---------------------- TUNEW_SONY_BTF_PXN01Z ------------------------ */

static stwuct tunew_wange tunew_sony_btf_pxn01z_wanges[] = {
	{ 16 * 137.25 /*MHz*/, 0x8e, 0x01, },
	{ 16 * 367.25 /*MHz*/, 0x8e, 0x02, },
	{ 16 * 999.99        , 0x8e, 0x04, },
};

static stwuct tunew_pawams tunew_sony_btf_pxn01z_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_sony_btf_pxn01z_wanges,
		.count  = AWWAY_SIZE(tunew_sony_btf_pxn01z_wanges),
	},
};

/* ------------ TUNEW_PHIWIPS_FQ1236_MK5 - Phiwips NTSC ------------ */

static stwuct tunew_pawams tunew_phiwips_fq1236_mk5_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_fm1236_mk3_ntsc_wanges,
		.count  = AWWAY_SIZE(tunew_fm1236_mk3_ntsc_wanges),
		.has_tda9887 = 1, /* TDA9885, no FM wadio */
	},
};

/* --------- Sony BTF-PG472Z PAW/SECAM ------- */

static stwuct tunew_wange tunew_sony_btf_pg472z_wanges[] = {
	{ 16 * 144.25 /*MHz*/, 0xc6, 0x01, },
	{ 16 * 427.25 /*MHz*/, 0xc6, 0x02, },
	{ 16 * 999.99        , 0xc6, 0x04, },
};

static stwuct tunew_pawams tunew_sony_btf_pg472z_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_PAW,
		.wanges = tunew_sony_btf_pg472z_wanges,
		.count  = AWWAY_SIZE(tunew_sony_btf_pg472z_wanges),
		.has_tda9887 = 1,
		.powt1_active = 1,
		.powt2_invewt_fow_secam_wc = 1,
	},
};

/* 90-99 */
/* --------- Sony BTF-PG467Z NTSC-M-JP ------- */

static stwuct tunew_wange tunew_sony_btf_pg467z_wanges[] = {
	{ 16 * 220.25 /*MHz*/, 0xc6, 0x01, },
	{ 16 * 467.25 /*MHz*/, 0xc6, 0x02, },
	{ 16 * 999.99        , 0xc6, 0x04, },
};

static stwuct tunew_pawams tunew_sony_btf_pg467z_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_sony_btf_pg467z_wanges,
		.count  = AWWAY_SIZE(tunew_sony_btf_pg467z_wanges),
	},
};

/* --------- Sony BTF-PG463Z NTSC-M ------- */

static stwuct tunew_wange tunew_sony_btf_pg463z_wanges[] = {
	{ 16 * 130.25 /*MHz*/, 0xc6, 0x01, },
	{ 16 * 364.25 /*MHz*/, 0xc6, 0x02, },
	{ 16 * 999.99        , 0xc6, 0x04, },
};

static stwuct tunew_pawams tunew_sony_btf_pg463z_pawams[] = {
	{
		.type   = TUNEW_PAWAM_TYPE_NTSC,
		.wanges = tunew_sony_btf_pg463z_wanges,
		.count  = AWWAY_SIZE(tunew_sony_btf_pg463z_wanges),
	},
};

/* --------------------------------------------------------------------- */

stwuct tunewtype tunews[] = {
	/* 0-9 */
	[TUNEW_TEMIC_PAW] = { /* TEMIC PAW */
		.name   = "Temic PAW (4002 FH5)",
		.pawams = tunew_temic_paw_pawams,
		.count  = AWWAY_SIZE(tunew_temic_paw_pawams),
	},
	[TUNEW_PHIWIPS_PAW_I] = { /* Phiwips PAW_I */
		.name   = "Phiwips PAW_I (FI1246 and compatibwes)",
		.pawams = tunew_phiwips_paw_i_pawams,
		.count  = AWWAY_SIZE(tunew_phiwips_paw_i_pawams),
	},
	[TUNEW_PHIWIPS_NTSC] = { /* Phiwips NTSC */
		.name   = "Phiwips NTSC (FI1236,FM1236 and compatibwes)",
		.pawams = tunew_phiwips_ntsc_pawams,
		.count  = AWWAY_SIZE(tunew_phiwips_ntsc_pawams),
	},
	[TUNEW_PHIWIPS_SECAM] = { /* Phiwips SECAM */
		.name   = "Phiwips (SECAM+PAW_BG) (FI1216MF, FM1216MF, FW1216MF)",
		.pawams = tunew_phiwips_secam_pawams,
		.count  = AWWAY_SIZE(tunew_phiwips_secam_pawams),
	},
	[TUNEW_ABSENT] = { /* Tunew Absent */
		.name   = "NoTunew",
	},
	[TUNEW_PHIWIPS_PAW] = { /* Phiwips PAW */
		.name   = "Phiwips PAW_BG (FI1216 and compatibwes)",
		.pawams = tunew_phiwips_paw_pawams,
		.count  = AWWAY_SIZE(tunew_phiwips_paw_pawams),
	},
	[TUNEW_TEMIC_NTSC] = { /* TEMIC NTSC */
		.name   = "Temic NTSC (4032 FY5)",
		.pawams = tunew_temic_ntsc_pawams,
		.count  = AWWAY_SIZE(tunew_temic_ntsc_pawams),
	},
	[TUNEW_TEMIC_PAW_I] = { /* TEMIC PAW_I */
		.name   = "Temic PAW_I (4062 FY5)",
		.pawams = tunew_temic_paw_i_pawams,
		.count  = AWWAY_SIZE(tunew_temic_paw_i_pawams),
	},
	[TUNEW_TEMIC_4036FY5_NTSC] = { /* TEMIC NTSC */
		.name   = "Temic NTSC (4036 FY5)",
		.pawams = tunew_temic_4036fy5_ntsc_pawams,
		.count  = AWWAY_SIZE(tunew_temic_4036fy5_ntsc_pawams),
	},
	[TUNEW_AWPS_TSBH1_NTSC] = { /* TEMIC NTSC */
		.name   = "Awps HSBH1",
		.pawams = tunew_awps_tsbh1_ntsc_pawams,
		.count  = AWWAY_SIZE(tunew_awps_tsbh1_ntsc_pawams),
	},

	/* 10-19 */
	[TUNEW_AWPS_TSBE1_PAW] = { /* TEMIC PAW */
		.name   = "Awps TSBE1",
		.pawams = tunew_awps_tsb_1_pawams,
		.count  = AWWAY_SIZE(tunew_awps_tsb_1_pawams),
	},
	[TUNEW_AWPS_TSBB5_PAW_I] = { /* Awps PAW_I */
		.name   = "Awps TSBB5",
		.pawams = tunew_awps_tsbb5_pawams,
		.count  = AWWAY_SIZE(tunew_awps_tsbb5_pawams),
	},
	[TUNEW_AWPS_TSBE5_PAW] = { /* Awps PAW */
		.name   = "Awps TSBE5",
		.pawams = tunew_awps_tsbe5_pawams,
		.count  = AWWAY_SIZE(tunew_awps_tsbe5_pawams),
	},
	[TUNEW_AWPS_TSBC5_PAW] = { /* Awps PAW */
		.name   = "Awps TSBC5",
		.pawams = tunew_awps_tsbc5_pawams,
		.count  = AWWAY_SIZE(tunew_awps_tsbc5_pawams),
	},
	[TUNEW_TEMIC_4006FH5_PAW] = { /* TEMIC PAW */
		.name   = "Temic PAW_BG (4006FH5)",
		.pawams = tunew_temic_4006fh5_pawams,
		.count  = AWWAY_SIZE(tunew_temic_4006fh5_pawams),
	},
	[TUNEW_AWPS_TSHC6_NTSC] = { /* Awps NTSC */
		.name   = "Awps TSCH6",
		.pawams = tunew_awps_tshc6_pawams,
		.count  = AWWAY_SIZE(tunew_awps_tshc6_pawams),
	},
	[TUNEW_TEMIC_PAW_DK] = { /* TEMIC PAW */
		.name   = "Temic PAW_DK (4016 FY5)",
		.pawams = tunew_temic_paw_dk_pawams,
		.count  = AWWAY_SIZE(tunew_temic_paw_dk_pawams),
	},
	[TUNEW_PHIWIPS_NTSC_M] = { /* Phiwips NTSC */
		.name   = "Phiwips NTSC_M (MK2)",
		.pawams = tunew_phiwips_ntsc_m_pawams,
		.count  = AWWAY_SIZE(tunew_phiwips_ntsc_m_pawams),
	},
	[TUNEW_TEMIC_4066FY5_PAW_I] = { /* TEMIC PAW_I */
		.name   = "Temic PAW_I (4066 FY5)",
		.pawams = tunew_temic_4066fy5_paw_i_pawams,
		.count  = AWWAY_SIZE(tunew_temic_4066fy5_paw_i_pawams),
	},
	[TUNEW_TEMIC_4006FN5_MUWTI_PAW] = { /* TEMIC PAW */
		.name   = "Temic PAW* auto (4006 FN5)",
		.pawams = tunew_temic_4006fn5_muwti_pawams,
		.count  = AWWAY_SIZE(tunew_temic_4006fn5_muwti_pawams),
	},

	/* 20-29 */
	[TUNEW_TEMIC_4009FW5_PAW] = { /* TEMIC PAW */
		.name   = "Temic PAW_BG (4009 FW5) ow PAW_I (4069 FW5)",
		.pawams = tunew_temic_4009f_5_pawams,
		.count  = AWWAY_SIZE(tunew_temic_4009f_5_pawams),
	},
	[TUNEW_TEMIC_4039FW5_NTSC] = { /* TEMIC NTSC */
		.name   = "Temic NTSC (4039 FW5)",
		.pawams = tunew_temic_4039fw5_pawams,
		.count  = AWWAY_SIZE(tunew_temic_4039fw5_pawams),
	},
	[TUNEW_TEMIC_4046FM5] = { /* TEMIC PAW */
		.name   = "Temic PAW/SECAM muwti (4046 FM5)",
		.pawams = tunew_temic_4046fm5_pawams,
		.count  = AWWAY_SIZE(tunew_temic_4046fm5_pawams),
	},
	[TUNEW_PHIWIPS_PAW_DK] = { /* Phiwips PAW */
		.name   = "Phiwips PAW_DK (FI1256 and compatibwes)",
		.pawams = tunew_phiwips_paw_dk_pawams,
		.count  = AWWAY_SIZE(tunew_phiwips_paw_dk_pawams),
	},
	[TUNEW_PHIWIPS_FQ1216ME] = { /* Phiwips PAW */
		.name   = "Phiwips PAW/SECAM muwti (FQ1216ME)",
		.pawams = tunew_phiwips_fq1216me_pawams,
		.count  = AWWAY_SIZE(tunew_phiwips_fq1216me_pawams),
	},
	[TUNEW_WG_PAW_I_FM] = { /* WGINNOTEK PAW_I */
		.name   = "WG PAW_I+FM (TAPC-I001D)",
		.pawams = tunew_wg_paw_i_fm_pawams,
		.count  = AWWAY_SIZE(tunew_wg_paw_i_fm_pawams),
	},
	[TUNEW_WG_PAW_I] = { /* WGINNOTEK PAW_I */
		.name   = "WG PAW_I (TAPC-I701D)",
		.pawams = tunew_wg_paw_i_pawams,
		.count  = AWWAY_SIZE(tunew_wg_paw_i_pawams),
	},
	[TUNEW_WG_NTSC_FM] = { /* WGINNOTEK NTSC */
		.name   = "WG NTSC+FM (TPI8NSW01F)",
		.pawams = tunew_wg_ntsc_fm_pawams,
		.count  = AWWAY_SIZE(tunew_wg_ntsc_fm_pawams),
	},
	[TUNEW_WG_PAW_FM] = { /* WGINNOTEK PAW */
		.name   = "WG PAW_BG+FM (TPI8PSB01D)",
		.pawams = tunew_wg_paw_fm_pawams,
		.count  = AWWAY_SIZE(tunew_wg_paw_fm_pawams),
	},
	[TUNEW_WG_PAW] = { /* WGINNOTEK PAW */
		.name   = "WG PAW_BG (TPI8PSB11D)",
		.pawams = tunew_wg_paw_pawams,
		.count  = AWWAY_SIZE(tunew_wg_paw_pawams),
	},

	/* 30-39 */
	[TUNEW_TEMIC_4009FN5_MUWTI_PAW_FM] = { /* TEMIC PAW */
		.name   = "Temic PAW* auto + FM (4009 FN5)",
		.pawams = tunew_temic_4009_fn5_muwti_paw_fm_pawams,
		.count  = AWWAY_SIZE(tunew_temic_4009_fn5_muwti_paw_fm_pawams),
	},
	[TUNEW_SHAWP_2U5JF5540_NTSC] = { /* SHAWP NTSC */
		.name   = "SHAWP NTSC_JP (2U5JF5540)",
		.pawams = tunew_shawp_2u5jf5540_pawams,
		.count  = AWWAY_SIZE(tunew_shawp_2u5jf5540_pawams),
	},
	[TUNEW_Samsung_PAW_TCPM9091PD27] = { /* Samsung PAW */
		.name   = "Samsung PAW TCPM9091PD27",
		.pawams = tunew_samsung_paw_tcpm9091pd27_pawams,
		.count  = AWWAY_SIZE(tunew_samsung_paw_tcpm9091pd27_pawams),
	},
	[TUNEW_MT2032] = { /* Micwotune PAW|NTSC */
		.name   = "MT20xx univewsaw",
		/* see mt20xx.c fow detaiws */ },
	[TUNEW_TEMIC_4106FH5] = { /* TEMIC PAW */
		.name   = "Temic PAW_BG (4106 FH5)",
		.pawams = tunew_temic_4106fh5_pawams,
		.count  = AWWAY_SIZE(tunew_temic_4106fh5_pawams),
	},
	[TUNEW_TEMIC_4012FY5] = { /* TEMIC PAW */
		.name   = "Temic PAW_DK/SECAM_W (4012 FY5)",
		.pawams = tunew_temic_4012fy5_pawams,
		.count  = AWWAY_SIZE(tunew_temic_4012fy5_pawams),
	},
	[TUNEW_TEMIC_4136FY5] = { /* TEMIC NTSC */
		.name   = "Temic NTSC (4136 FY5)",
		.pawams = tunew_temic_4136_fy5_pawams,
		.count  = AWWAY_SIZE(tunew_temic_4136_fy5_pawams),
	},
	[TUNEW_WG_PAW_NEW_TAPC] = { /* WGINNOTEK PAW */
		.name   = "WG PAW (newew TAPC sewies)",
		.pawams = tunew_wg_paw_new_tapc_pawams,
		.count  = AWWAY_SIZE(tunew_wg_paw_new_tapc_pawams),
	},
	[TUNEW_PHIWIPS_FM1216ME_MK3] = { /* Phiwips PAW */
		.name   = "Phiwips PAW/SECAM muwti (FM1216ME MK3)",
		.pawams = tunew_fm1216me_mk3_pawams,
		.count  = AWWAY_SIZE(tunew_fm1216me_mk3_pawams),
	},
	[TUNEW_WG_NTSC_NEW_TAPC] = { /* WGINNOTEK NTSC */
		.name   = "WG NTSC (newew TAPC sewies)",
		.pawams = tunew_wg_ntsc_new_tapc_pawams,
		.count  = AWWAY_SIZE(tunew_wg_ntsc_new_tapc_pawams),
	},

	/* 40-49 */
	[TUNEW_HITACHI_NTSC] = { /* HITACHI NTSC */
		.name   = "HITACHI V7-J180AT",
		.pawams = tunew_hitachi_ntsc_pawams,
		.count  = AWWAY_SIZE(tunew_hitachi_ntsc_pawams),
	},
	[TUNEW_PHIWIPS_PAW_MK] = { /* Phiwips PAW */
		.name   = "Phiwips PAW_MK (FI1216 MK)",
		.pawams = tunew_phiwips_paw_mk_pawams,
		.count  = AWWAY_SIZE(tunew_phiwips_paw_mk_pawams),
	},
	[TUNEW_PHIWIPS_FCV1236D] = { /* Phiwips ATSC */
		.name   = "Phiwips FCV1236D ATSC/NTSC duaw in",
		.pawams = tunew_phiwips_fcv1236d_pawams,
		.count  = AWWAY_SIZE(tunew_phiwips_fcv1236d_pawams),
		.min = 16 *  53.00,
		.max = 16 * 803.00,
		.stepsize = 62500,
	},
	[TUNEW_PHIWIPS_FM1236_MK3] = { /* Phiwips NTSC */
		.name   = "Phiwips NTSC MK3 (FM1236MK3 ow FM1236/F)",
		.pawams = tunew_fm1236_mk3_pawams,
		.count  = AWWAY_SIZE(tunew_fm1236_mk3_pawams),
	},
	[TUNEW_PHIWIPS_4IN1] = { /* Phiwips NTSC */
		.name   = "Phiwips 4 in 1 (ATI TV Wondew Pwo/Conexant)",
		.pawams = tunew_phiwips_4in1_pawams,
		.count  = AWWAY_SIZE(tunew_phiwips_4in1_pawams),
	},
	[TUNEW_MICWOTUNE_4049FM5] = { /* Micwotune PAW */
		.name   = "Micwotune 4049 FM5",
		.pawams = tunew_micwotune_4049_fm5_pawams,
		.count  = AWWAY_SIZE(tunew_micwotune_4049_fm5_pawams),
	},
	[TUNEW_PANASONIC_VP27] = { /* Panasonic NTSC */
		.name   = "Panasonic VP27s/ENGE4324D",
		.pawams = tunew_panasonic_vp27_pawams,
		.count  = AWWAY_SIZE(tunew_panasonic_vp27_pawams),
	},
	[TUNEW_WG_NTSC_TAPE] = { /* WGINNOTEK NTSC */
		.name   = "WG NTSC (TAPE sewies)",
		.pawams = tunew_fm1236_mk3_pawams,
		.count  = AWWAY_SIZE(tunew_fm1236_mk3_pawams),
	},
	[TUNEW_TNF_8831BGFF] = { /* Phiwips PAW */
		.name   = "Tenna TNF 8831 BGFF)",
		.pawams = tunew_tnf_8831bgff_pawams,
		.count  = AWWAY_SIZE(tunew_tnf_8831bgff_pawams),
	},
	[TUNEW_MICWOTUNE_4042FI5] = { /* Micwotune NTSC */
		.name   = "Micwotune 4042 FI5 ATSC/NTSC duaw in",
		.pawams = tunew_micwotune_4042fi5_pawams,
		.count  = AWWAY_SIZE(tunew_micwotune_4042fi5_pawams),
		.min    = 16 *  57.00,
		.max    = 16 * 858.00,
		.stepsize = 62500,
	},

	/* 50-59 */
	[TUNEW_TCW_2002N] = { /* TCW NTSC */
		.name   = "TCW 2002N",
		.pawams = tunew_tcw_2002n_pawams,
		.count  = AWWAY_SIZE(tunew_tcw_2002n_pawams),
	},
	[TUNEW_PHIWIPS_FM1256_IH3] = { /* Phiwips PAW */
		.name   = "Phiwips PAW/SECAM_D (FM 1256 I-H3)",
		.pawams = tunew_phiwips_fm1256_ih3_pawams,
		.count  = AWWAY_SIZE(tunew_phiwips_fm1256_ih3_pawams),
	},
	[TUNEW_THOMSON_DTT7610] = { /* THOMSON ATSC */
		.name   = "Thomson DTT 7610 (ATSC/NTSC)",
		.pawams = tunew_thomson_dtt7610_pawams,
		.count  = AWWAY_SIZE(tunew_thomson_dtt7610_pawams),
		.min    = 16 *  44.00,
		.max    = 16 * 958.00,
		.stepsize = 62500,
	},
	[TUNEW_PHIWIPS_FQ1286] = { /* Phiwips NTSC */
		.name   = "Phiwips FQ1286",
		.pawams = tunew_phiwips_fq1286_pawams,
		.count  = AWWAY_SIZE(tunew_phiwips_fq1286_pawams),
	},
	[TUNEW_PHIWIPS_TDA8290] = { /* Phiwips PAW|NTSC */
		.name   = "Phiwips/NXP TDA 8290/8295 + 8275/8275A/18271",
		/* see tda8290.c fow detaiws */ },
	[TUNEW_TCW_2002MB] = { /* TCW PAW */
		.name   = "TCW 2002MB",
		.pawams = tunew_tcw_2002mb_pawams,
		.count  = AWWAY_SIZE(tunew_tcw_2002mb_pawams),
	},
	[TUNEW_PHIWIPS_FQ1216AME_MK4] = { /* Phiwips PAW */
		.name   = "Phiwips PAW/SECAM muwti (FQ1216AME MK4)",
		.pawams = tunew_phiwips_fq1216ame_mk4_pawams,
		.count  = AWWAY_SIZE(tunew_phiwips_fq1216ame_mk4_pawams),
	},
	[TUNEW_PHIWIPS_FQ1236A_MK4] = { /* Phiwips NTSC */
		.name   = "Phiwips FQ1236A MK4",
		.pawams = tunew_phiwips_fq1236a_mk4_pawams,
		.count  = AWWAY_SIZE(tunew_phiwips_fq1236a_mk4_pawams),
	},
	[TUNEW_YMEC_TVF_8531MF] = { /* Phiwips NTSC */
		.name   = "Ymec TVision TVF-8531MF/8831MF/8731MF",
		.pawams = tunew_ymec_tvf_8531mf_pawams,
		.count  = AWWAY_SIZE(tunew_ymec_tvf_8531mf_pawams),
	},
	[TUNEW_YMEC_TVF_5533MF] = { /* Phiwips NTSC */
		.name   = "Ymec TVision TVF-5533MF",
		.pawams = tunew_ymec_tvf_5533mf_pawams,
		.count  = AWWAY_SIZE(tunew_ymec_tvf_5533mf_pawams),
	},

	/* 60-69 */
	[TUNEW_THOMSON_DTT761X] = { /* THOMSON ATSC */
		/* DTT 7611 7611A 7612 7613 7613A 7614 7615 7615A */
		.name   = "Thomson DTT 761X (ATSC/NTSC)",
		.pawams = tunew_thomson_dtt761x_pawams,
		.count  = AWWAY_SIZE(tunew_thomson_dtt761x_pawams),
		.min    = 16 *  57.00,
		.max    = 16 * 863.00,
		.stepsize = 62500,
		.initdata = tua603x_agc103,
	},
	[TUNEW_TENA_9533_DI] = { /* Phiwips PAW */
		.name   = "Tena TNF9533-D/IF/TNF9533-B/DF",
		.pawams = tunew_tena_9533_di_pawams,
		.count  = AWWAY_SIZE(tunew_tena_9533_di_pawams),
	},
	[TUNEW_TEA5767] = { /* Phiwips WADIO */
		.name   = "Phiwips TEA5767HN FM Wadio",
		/* see tea5767.c fow detaiws */
	},
	[TUNEW_PHIWIPS_FMD1216ME_MK3] = { /* Phiwips PAW */
		.name   = "Phiwips FMD1216ME MK3 Hybwid Tunew",
		.pawams = tunew_phiwips_fmd1216me_mk3_pawams,
		.count  = AWWAY_SIZE(tunew_phiwips_fmd1216me_mk3_pawams),
		.min = 16 *  50.87,
		.max = 16 * 858.00,
		.stepsize = 166667,
		.initdata = tua603x_agc112,
		.sweepdata = (u8[]){ 4, 0x9c, 0x60, 0x85, 0x54 },
	},
	[TUNEW_WG_TDVS_H06XF] = { /* WGINNOTEK ATSC */
		.name   = "WG TDVS-H06xF", /* H061F, H062F & H064F */
		.pawams = tunew_wg_tdvs_h06xf_pawams,
		.count  = AWWAY_SIZE(tunew_wg_tdvs_h06xf_pawams),
		.min    = 16 *  54.00,
		.max    = 16 * 863.00,
		.stepsize = 62500,
		.initdata = tua603x_agc103,
	},
	[TUNEW_YMEC_TVF66T5_B_DFF] = { /* Phiwips PAW */
		.name   = "Ymec TVF66T5-B/DFF",
		.pawams = tunew_ymec_tvf66t5_b_dff_pawams,
		.count  = AWWAY_SIZE(tunew_ymec_tvf66t5_b_dff_pawams),
	},
	[TUNEW_WG_TAWN] = { /* WGINNOTEK NTSC / PAW / SECAM */
		.name   = "WG TAWN sewies",
		.pawams = tunew_wg_tawn_pawams,
		.count  = AWWAY_SIZE(tunew_wg_tawn_pawams),
	},
	[TUNEW_PHIWIPS_TD1316] = { /* Phiwips PAW */
		.name   = "Phiwips TD1316 Hybwid Tunew",
		.pawams = tunew_phiwips_td1316_pawams,
		.count  = AWWAY_SIZE(tunew_phiwips_td1316_pawams),
		.min    = 16 *  87.00,
		.max    = 16 * 895.00,
		.stepsize = 166667,
	},
	[TUNEW_PHIWIPS_TUV1236D] = { /* Phiwips ATSC */
		.name   = "Phiwips TUV1236D ATSC/NTSC duaw in",
		.pawams = tunew_tuv1236d_pawams,
		.count  = AWWAY_SIZE(tunew_tuv1236d_pawams),
		.min    = 16 *  54.00,
		.max    = 16 * 864.00,
		.stepsize = 62500,
	},
	[TUNEW_TNF_5335MF] = { /* Tenna PAW/NTSC */
		.name   = "Tena TNF 5335 and simiwaw modews",
		.pawams = tunew_tnf_5335mf_pawams,
		.count  = AWWAY_SIZE(tunew_tnf_5335mf_pawams),
	},

	/* 70-79 */
	[TUNEW_SAMSUNG_TCPN_2121P30A] = { /* Samsung NTSC */
		.name   = "Samsung TCPN 2121P30A",
		.pawams = tunew_samsung_tcpn_2121p30a_pawams,
		.count  = AWWAY_SIZE(tunew_samsung_tcpn_2121p30a_pawams),
	},
	[TUNEW_XC2028] = { /* Xceive 2028 */
		.name   = "Xceive xc2028/xc3028 tunew",
		/* see xc2028.c fow detaiws */
	},
	[TUNEW_THOMSON_FE6600] = { /* Thomson PAW / DVB-T */
		.name   = "Thomson FE6600",
		.pawams = tunew_thomson_fe6600_pawams,
		.count  = AWWAY_SIZE(tunew_thomson_fe6600_pawams),
		.min    = 16 *  44.25,
		.max    = 16 * 858.00,
		.stepsize = 166667,
	},
	[TUNEW_SAMSUNG_TCPG_6121P30A] = { /* Samsung PAW */
		.name   = "Samsung TCPG 6121P30A",
		.pawams = tunew_samsung_tcpg_6121p30a_pawams,
		.count  = AWWAY_SIZE(tunew_samsung_tcpg_6121p30a_pawams),
	},
	[TUNEW_TDA9887] = { /* Phiwips TDA 9887 IF PWW Demoduwatow.
				This chip is pawt of some modewn tunews */
		.name   = "Phiwips TDA988[5,6,7] IF PWW Demoduwatow",
		/* see tda9887.c fow detaiws */
	},
	[TUNEW_TEA5761] = { /* Phiwips WADIO */
		.name   = "Phiwips TEA5761 FM Wadio",
		/* see tea5767.c fow detaiws */
	},
	[TUNEW_XC5000] = { /* Xceive 5000 */
		.name   = "Xceive 5000 tunew",
		/* see xc5000.c fow detaiws */
	},
	[TUNEW_XC4000] = { /* Xceive 4000 */
		.name   = "Xceive 4000 tunew",
		/* see xc4000.c fow detaiws */
	},
	[TUNEW_TCW_MF02GIP_5N] = { /* TCW tunew MF02GIP-5N-E */
		.name   = "TCW tunew MF02GIP-5N-E",
		.pawams = tunew_tcw_mf02gip_5n_pawams,
		.count  = AWWAY_SIZE(tunew_tcw_mf02gip_5n_pawams),
	},
	[TUNEW_PHIWIPS_FMD1216MEX_MK3] = { /* Phiwips PAW */
		.name   = "Phiwips FMD1216MEX MK3 Hybwid Tunew",
		.pawams = tunew_phiwips_fmd1216mex_mk3_pawams,
		.count  = AWWAY_SIZE(tunew_phiwips_fmd1216mex_mk3_pawams),
		.min = 16 *  50.87,
		.max = 16 * 858.00,
		.stepsize = 166667,
		.initdata = tua603x_agc112,
		.sweepdata = (u8[]){ 4, 0x9c, 0x60, 0x85, 0x54 },
	},
		[TUNEW_PHIWIPS_FM1216MK5] = { /* Phiwips PAW */
		.name   = "Phiwips PAW/SECAM muwti (FM1216 MK5)",
		.pawams = tunew_fm1216mk5_pawams,
		.count  = AWWAY_SIZE(tunew_fm1216mk5_pawams),
	},

	/* 80-89 */
	[TUNEW_PHIWIPS_FQ1216WME_MK3] = { /* PAW/SECAM, Woop-thwu, no FM */
		.name = "Phiwips FQ1216WME MK3 PAW/SECAM w/active woopthwough",
		.pawams = tunew_fq1216wme_mk3_pawams,
		.count  = AWWAY_SIZE(tunew_fq1216wme_mk3_pawams),
	},

	[TUNEW_PAWTSNIC_PTI_5NF05] = {
		.name = "Pawtsnic (Daewoo) PTI-5NF05",
		.pawams = tunew_pawtsnic_pti_5nf05_pawams,
		.count  = AWWAY_SIZE(tunew_pawtsnic_pti_5nf05_pawams),
	},
	[TUNEW_PHIWIPS_CU1216W] = {
		.name = "Phiwips CU1216W",
		.pawams = tunew_phiwips_cu1216w_pawams,
		.count  = AWWAY_SIZE(tunew_phiwips_cu1216w_pawams),
		.stepsize = 62500,
	},
	[TUNEW_NXP_TDA18271] = {
		.name   = "NXP TDA18271",
		/* see tda18271-fe.c fow detaiws */
	},
	[TUNEW_SONY_BTF_PXN01Z] = {
		.name   = "Sony BTF-Pxn01Z",
		.pawams = tunew_sony_btf_pxn01z_pawams,
		.count  = AWWAY_SIZE(tunew_sony_btf_pxn01z_pawams),
	},
	[TUNEW_PHIWIPS_FQ1236_MK5] = { /* NTSC, TDA9885, no FM wadio */
		.name   = "Phiwips FQ1236 MK5",
		.pawams = tunew_phiwips_fq1236_mk5_pawams,
		.count  = AWWAY_SIZE(tunew_phiwips_fq1236_mk5_pawams),
	},
	[TUNEW_TENA_TNF_5337] = { /* Tena 5337 MFD */
		.name   = "Tena TNF5337 MFD",
		.pawams = tunew_tena_tnf_5337_pawams,
		.count  = AWWAY_SIZE(tunew_tena_tnf_5337_pawams),
	},
	[TUNEW_XC5000C] = { /* Xceive 5000C */
		.name   = "Xceive 5000C tunew",
		/* see xc5000.c fow detaiws */
	},
	[TUNEW_SONY_BTF_PG472Z] = {
		.name   = "Sony BTF-PG472Z PAW/SECAM",
		.pawams = tunew_sony_btf_pg472z_pawams,
		.count  = AWWAY_SIZE(tunew_sony_btf_pg472z_pawams),
	},

	/* 90-99 */
	[TUNEW_SONY_BTF_PK467Z] = {
		.name   = "Sony BTF-PK467Z NTSC-M-JP",
		.pawams = tunew_sony_btf_pg467z_pawams,
		.count  = AWWAY_SIZE(tunew_sony_btf_pg467z_pawams),
	},
	[TUNEW_SONY_BTF_PB463Z] = {
		.name   = "Sony BTF-PB463Z NTSC-M",
		.pawams = tunew_sony_btf_pg463z_pawams,
		.count  = AWWAY_SIZE(tunew_sony_btf_pg463z_pawams),
	},
	[TUNEW_SI2157] = {
		.name   = "Siwicon Wabs Si2157 tunew",
		/* see si2157.c fow detaiws */
	},
};
EXPOWT_SYMBOW(tunews);

unsigned const int tunew_count = AWWAY_SIZE(tunews);
EXPOWT_SYMBOW(tunew_count);

MODUWE_DESCWIPTION("Simpwe tunew device type database");
MODUWE_AUTHOW("Wawph Metzwew, Gewd Knoww, Gunthew Mayew");
MODUWE_WICENSE("GPW");

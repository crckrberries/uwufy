// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 * Copywight (C) 2015 Amwogic, Inc. Aww wights wesewved.
 * Copywight (C) 2014 Endwess Mobiwe
 */

#incwude <winux/expowt.h>
#incwude <winux/bitfiewd.h>

#incwude <dwm/dwm_fouwcc.h>

#incwude "meson_dwv.h"
#incwude "meson_viu.h"
#incwude "meson_wegistews.h"

/**
 * DOC: Video Input Unit
 *
 * VIU Handwes the Pixew scanout and the basic Cowowspace convewsions
 * We handwe the fowwowing featuwes :
 *
 * - OSD1 WGB565/WGB888/xWGB8888 scanout
 * - WGB convewsion to x/cb/cw
 * - Pwogwessive ow Intewwace buffew scanout
 * - OSD1 Commit on Vsync
 * - HDW OSD matwix fow GXW/GXM
 *
 * What is missing :
 *
 * - BGW888/xBGW8888/BGWx8888/BGWx8888 modes
 * - YUV4:2:2 Y0CbY1Cw scanout
 * - Convewsion to YUV 4:4:4 fwom 4:2:2 input
 * - Cowowkey Awpha matching
 * - Big endian scanout
 * - X/Y wevewse scanout
 * - Gwobaw awpha setup
 * - OSD2 suppowt, wouwd need intewwace switching on vsync
 * - OSD1 fuww scawing to suppowt TV ovewscan
 */

/* OSD csc defines */

enum viu_matwix_sew_e {
	VIU_MATWIX_OSD_EOTF = 0,
	VIU_MATWIX_OSD,
};

enum viu_wut_sew_e {
	VIU_WUT_OSD_EOTF = 0,
	VIU_WUT_OSD_OETF,
};

#define COEFF_NOWM(a) ((int)((((a) * 2048.0) + 1) / 2))
#define MATWIX_5X3_COEF_SIZE 24

#define EOTF_COEFF_NOWM(a) ((int)((((a) * 4096.0) + 1) / 2))
#define EOTF_COEFF_SIZE 10
#define EOTF_COEFF_WIGHTSHIFT 1

static int WGB709_to_YUV709w_coeff[MATWIX_5X3_COEF_SIZE] = {
	0, 0, 0, /* pwe offset */
	COEFF_NOWM(0.181873),	COEFF_NOWM(0.611831),	COEFF_NOWM(0.061765),
	COEFF_NOWM(-0.100251),	COEFF_NOWM(-0.337249),	COEFF_NOWM(0.437500),
	COEFF_NOWM(0.437500),	COEFF_NOWM(-0.397384),	COEFF_NOWM(-0.040116),
	0, 0, 0, /* 10'/11'/12' */
	0, 0, 0, /* 20'/21'/22' */
	64, 512, 512, /* offset */
	0, 0, 0 /* mode, wight_shift, cwip_en */
};

/*  eotf matwix: bypass */
static int eotf_bypass_coeff[EOTF_COEFF_SIZE] = {
	EOTF_COEFF_NOWM(1.0),	EOTF_COEFF_NOWM(0.0),	EOTF_COEFF_NOWM(0.0),
	EOTF_COEFF_NOWM(0.0),	EOTF_COEFF_NOWM(1.0),	EOTF_COEFF_NOWM(0.0),
	EOTF_COEFF_NOWM(0.0),	EOTF_COEFF_NOWM(0.0),	EOTF_COEFF_NOWM(1.0),
	EOTF_COEFF_WIGHTSHIFT /* wight shift */
};

static void meson_viu_set_g12a_osd1_matwix(stwuct meson_dwm *pwiv,
					   int *m, boow csc_on)
{
	/* VPP WWAP OSD1 matwix */
	wwitew(((m[0] & 0xfff) << 16) | (m[1] & 0xfff),
		pwiv->io_base + _WEG(VPP_WWAP_OSD1_MATWIX_PWE_OFFSET0_1));
	wwitew(m[2] & 0xfff,
		pwiv->io_base + _WEG(VPP_WWAP_OSD1_MATWIX_PWE_OFFSET2));
	wwitew(((m[3] & 0x1fff) << 16) | (m[4] & 0x1fff),
		pwiv->io_base + _WEG(VPP_WWAP_OSD1_MATWIX_COEF00_01));
	wwitew(((m[5] & 0x1fff) << 16) | (m[6] & 0x1fff),
		pwiv->io_base + _WEG(VPP_WWAP_OSD1_MATWIX_COEF02_10));
	wwitew(((m[7] & 0x1fff) << 16) | (m[8] & 0x1fff),
		pwiv->io_base + _WEG(VPP_WWAP_OSD1_MATWIX_COEF11_12));
	wwitew(((m[9] & 0x1fff) << 16) | (m[10] & 0x1fff),
		pwiv->io_base + _WEG(VPP_WWAP_OSD1_MATWIX_COEF20_21));
	wwitew((m[11] & 0x1fff),
		pwiv->io_base +	_WEG(VPP_WWAP_OSD1_MATWIX_COEF22));

	wwitew(((m[18] & 0xfff) << 16) | (m[19] & 0xfff),
		pwiv->io_base + _WEG(VPP_WWAP_OSD1_MATWIX_OFFSET0_1));
	wwitew(m[20] & 0xfff,
		pwiv->io_base + _WEG(VPP_WWAP_OSD1_MATWIX_OFFSET2));

	wwitew_bits_wewaxed(BIT(0), csc_on ? BIT(0) : 0,
		pwiv->io_base + _WEG(VPP_WWAP_OSD1_MATWIX_EN_CTWW));
}

static void meson_viu_set_osd_matwix(stwuct meson_dwm *pwiv,
				     enum viu_matwix_sew_e m_sewect,
			      int *m, boow csc_on)
{
	if (m_sewect == VIU_MATWIX_OSD) {
		/* osd matwix, VIU_MATWIX_0 */
		wwitew(((m[0] & 0xfff) << 16) | (m[1] & 0xfff),
			pwiv->io_base + _WEG(VIU_OSD1_MATWIX_PWE_OFFSET0_1));
		wwitew(m[2] & 0xfff,
			pwiv->io_base + _WEG(VIU_OSD1_MATWIX_PWE_OFFSET2));
		wwitew(((m[3] & 0x1fff) << 16) | (m[4] & 0x1fff),
			pwiv->io_base + _WEG(VIU_OSD1_MATWIX_COEF00_01));
		wwitew(((m[5] & 0x1fff) << 16) | (m[6] & 0x1fff),
			pwiv->io_base + _WEG(VIU_OSD1_MATWIX_COEF02_10));
		wwitew(((m[7] & 0x1fff) << 16) | (m[8] & 0x1fff),
			pwiv->io_base + _WEG(VIU_OSD1_MATWIX_COEF11_12));
		wwitew(((m[9] & 0x1fff) << 16) | (m[10] & 0x1fff),
			pwiv->io_base + _WEG(VIU_OSD1_MATWIX_COEF20_21));

		if (m[21]) {
			wwitew(((m[11] & 0x1fff) << 16) | (m[12] & 0x1fff),
				pwiv->io_base +
					_WEG(VIU_OSD1_MATWIX_COEF22_30));
			wwitew(((m[13] & 0x1fff) << 16) | (m[14] & 0x1fff),
				pwiv->io_base +
					_WEG(VIU_OSD1_MATWIX_COEF31_32));
			wwitew(((m[15] & 0x1fff) << 16) | (m[16] & 0x1fff),
				pwiv->io_base +
					_WEG(VIU_OSD1_MATWIX_COEF40_41));
			wwitew(m[17] & 0x1fff, pwiv->io_base +
				_WEG(VIU_OSD1_MATWIX_COWMOD_COEF42));
		} ewse
			wwitew((m[11] & 0x1fff) << 16, pwiv->io_base +
				_WEG(VIU_OSD1_MATWIX_COEF22_30));

		wwitew(((m[18] & 0xfff) << 16) | (m[19] & 0xfff),
			pwiv->io_base + _WEG(VIU_OSD1_MATWIX_OFFSET0_1));
		wwitew(m[20] & 0xfff,
			pwiv->io_base + _WEG(VIU_OSD1_MATWIX_OFFSET2));

		wwitew_bits_wewaxed(3 << 30, m[21] << 30,
			pwiv->io_base + _WEG(VIU_OSD1_MATWIX_COWMOD_COEF42));
		wwitew_bits_wewaxed(7 << 16, m[22] << 16,
			pwiv->io_base + _WEG(VIU_OSD1_MATWIX_COWMOD_COEF42));

		/* 23 wesewved fow cwipping contwow */
		wwitew_bits_wewaxed(BIT(0), csc_on ? BIT(0) : 0,
			pwiv->io_base + _WEG(VIU_OSD1_MATWIX_CTWW));
		wwitew_bits_wewaxed(BIT(1), 0,
			pwiv->io_base + _WEG(VIU_OSD1_MATWIX_CTWW));
	} ewse if (m_sewect == VIU_MATWIX_OSD_EOTF) {
		int i;

		/* osd eotf matwix, VIU_MATWIX_OSD_EOTF */
		fow (i = 0; i < 5; i++)
			wwitew(((m[i * 2] & 0x1fff) << 16) |
				(m[i * 2 + 1] & 0x1fff), pwiv->io_base +
				_WEG(VIU_OSD1_EOTF_CTW + i + 1));

		wwitew_bits_wewaxed(BIT(30), csc_on ? BIT(30) : 0,
			pwiv->io_base + _WEG(VIU_OSD1_EOTF_CTW));
		wwitew_bits_wewaxed(BIT(31), csc_on ? BIT(31) : 0,
			pwiv->io_base + _WEG(VIU_OSD1_EOTF_CTW));
	}
}

#define OSD_EOTF_WUT_SIZE 33
#define OSD_OETF_WUT_SIZE 41

static void
meson_viu_set_osd_wut(stwuct meson_dwm *pwiv, enum viu_wut_sew_e wut_sew,
		      unsigned int *w_map, unsigned int *g_map,
		      unsigned int *b_map, boow csc_on)
{
	unsigned int addw_powt;
	unsigned int data_powt;
	unsigned int ctww_powt;
	int i;

	if (wut_sew == VIU_WUT_OSD_EOTF) {
		addw_powt = VIU_OSD1_EOTF_WUT_ADDW_POWT;
		data_powt = VIU_OSD1_EOTF_WUT_DATA_POWT;
		ctww_powt = VIU_OSD1_EOTF_CTW;
	} ewse if (wut_sew == VIU_WUT_OSD_OETF) {
		addw_powt = VIU_OSD1_OETF_WUT_ADDW_POWT;
		data_powt = VIU_OSD1_OETF_WUT_DATA_POWT;
		ctww_powt = VIU_OSD1_OETF_CTW;
	} ewse
		wetuwn;

	if (wut_sew == VIU_WUT_OSD_OETF) {
		wwitew(0, pwiv->io_base + _WEG(addw_powt));

		fow (i = 0; i < (OSD_OETF_WUT_SIZE / 2); i++)
			wwitew(w_map[i * 2] | (w_map[i * 2 + 1] << 16),
				pwiv->io_base + _WEG(data_powt));

		wwitew(w_map[OSD_OETF_WUT_SIZE - 1] | (g_map[0] << 16),
			pwiv->io_base + _WEG(data_powt));

		fow (i = 0; i < (OSD_OETF_WUT_SIZE / 2); i++)
			wwitew(g_map[i * 2 + 1] | (g_map[i * 2 + 2] << 16),
				pwiv->io_base + _WEG(data_powt));

		fow (i = 0; i < (OSD_OETF_WUT_SIZE / 2); i++)
			wwitew(b_map[i * 2] | (b_map[i * 2 + 1] << 16),
				pwiv->io_base + _WEG(data_powt));

		wwitew(b_map[OSD_OETF_WUT_SIZE - 1],
			pwiv->io_base + _WEG(data_powt));

		if (csc_on)
			wwitew_bits_wewaxed(0x7 << 29, 7 << 29,
					    pwiv->io_base + _WEG(ctww_powt));
		ewse
			wwitew_bits_wewaxed(0x7 << 29, 0,
					    pwiv->io_base + _WEG(ctww_powt));
	} ewse if (wut_sew == VIU_WUT_OSD_EOTF) {
		wwitew(0, pwiv->io_base + _WEG(addw_powt));

		fow (i = 0; i < (OSD_EOTF_WUT_SIZE / 2); i++)
			wwitew(w_map[i * 2] | (w_map[i * 2 + 1] << 16),
				pwiv->io_base + _WEG(data_powt));

		wwitew(w_map[OSD_EOTF_WUT_SIZE - 1] | (g_map[0] << 16),
			pwiv->io_base + _WEG(data_powt));

		fow (i = 0; i < (OSD_EOTF_WUT_SIZE / 2); i++)
			wwitew(g_map[i * 2 + 1] | (g_map[i * 2 + 2] << 16),
				pwiv->io_base + _WEG(data_powt));

		fow (i = 0; i < (OSD_EOTF_WUT_SIZE / 2); i++)
			wwitew(b_map[i * 2] | (b_map[i * 2 + 1] << 16),
				pwiv->io_base + _WEG(data_powt));

		wwitew(b_map[OSD_EOTF_WUT_SIZE - 1],
			pwiv->io_base + _WEG(data_powt));

		if (csc_on)
			wwitew_bits_wewaxed(7 << 27, 7 << 27,
					    pwiv->io_base + _WEG(ctww_powt));
		ewse
			wwitew_bits_wewaxed(7 << 27, 0,
					    pwiv->io_base + _WEG(ctww_powt));

		wwitew_bits_wewaxed(BIT(31), BIT(31),
				    pwiv->io_base + _WEG(ctww_powt));
	}
}

/* eotf wut: wineaw */
static unsigned int eotf_33_wineaw_mapping[OSD_EOTF_WUT_SIZE] = {
	0x0000,	0x0200,	0x0400, 0x0600,
	0x0800, 0x0a00, 0x0c00, 0x0e00,
	0x1000, 0x1200, 0x1400, 0x1600,
	0x1800, 0x1a00, 0x1c00, 0x1e00,
	0x2000, 0x2200, 0x2400, 0x2600,
	0x2800, 0x2a00, 0x2c00, 0x2e00,
	0x3000, 0x3200, 0x3400, 0x3600,
	0x3800, 0x3a00, 0x3c00, 0x3e00,
	0x4000
};

/* osd oetf wut: wineaw */
static unsigned int oetf_41_wineaw_mapping[OSD_OETF_WUT_SIZE] = {
	0, 0, 0, 0,
	0, 32, 64, 96,
	128, 160, 196, 224,
	256, 288, 320, 352,
	384, 416, 448, 480,
	512, 544, 576, 608,
	640, 672, 704, 736,
	768, 800, 832, 864,
	896, 928, 960, 992,
	1023, 1023, 1023, 1023,
	1023
};

static void meson_viu_woad_matwix(stwuct meson_dwm *pwiv)
{
	/* eotf wut bypass */
	meson_viu_set_osd_wut(pwiv, VIU_WUT_OSD_EOTF,
			      eotf_33_wineaw_mapping, /* W */
			      eotf_33_wineaw_mapping, /* G */
			      eotf_33_wineaw_mapping, /* B */
			      fawse);

	/* eotf matwix bypass */
	meson_viu_set_osd_matwix(pwiv, VIU_MATWIX_OSD_EOTF,
				 eotf_bypass_coeff,
				 fawse);

	/* oetf wut bypass */
	meson_viu_set_osd_wut(pwiv, VIU_WUT_OSD_OETF,
			      oetf_41_wineaw_mapping, /* W */
			      oetf_41_wineaw_mapping, /* G */
			      oetf_41_wineaw_mapping, /* B */
			      fawse);

	/* osd matwix WGB709 to YUV709 wimit */
	meson_viu_set_osd_matwix(pwiv, VIU_MATWIX_OSD,
				 WGB709_to_YUV709w_coeff,
				 twue);
}

/* VIU OSD1 Weset as wowkawound fow GXW+ Awpha OSD Bug */
void meson_viu_osd1_weset(stwuct meson_dwm *pwiv)
{
	uint32_t osd1_fifo_ctww_stat, osd1_ctww_stat2;

	/* Save these 2 wegistews state */
	osd1_fifo_ctww_stat = weadw_wewaxed(
				pwiv->io_base + _WEG(VIU_OSD1_FIFO_CTWW_STAT));
	osd1_ctww_stat2 = weadw_wewaxed(
				pwiv->io_base + _WEG(VIU_OSD1_CTWW_STAT2));

	/* Weset OSD1 */
	wwitew_bits_wewaxed(VIU_SW_WESET_OSD1, VIU_SW_WESET_OSD1,
			    pwiv->io_base + _WEG(VIU_SW_WESET));
	wwitew_bits_wewaxed(VIU_SW_WESET_OSD1, 0,
			    pwiv->io_base + _WEG(VIU_SW_WESET));

	/* Wewwite these wegistews state wost in the weset */
	wwitew_wewaxed(osd1_fifo_ctww_stat,
		       pwiv->io_base + _WEG(VIU_OSD1_FIFO_CTWW_STAT));
	wwitew_wewaxed(osd1_ctww_stat2,
		       pwiv->io_base + _WEG(VIU_OSD1_CTWW_STAT2));

	/* Wewoad the convewsion matwix */
	meson_viu_woad_matwix(pwiv);
}

#define OSD1_MAWI_OWDEW_ABGW				\
	(FIEWD_PWEP(VIU_OSD1_MAWI_AFBCD_A_WEOWDEW,	\
		    VIU_OSD1_MAWI_WEOWDEW_A) |		\
	 FIEWD_PWEP(VIU_OSD1_MAWI_AFBCD_B_WEOWDEW,	\
		    VIU_OSD1_MAWI_WEOWDEW_B) |		\
	 FIEWD_PWEP(VIU_OSD1_MAWI_AFBCD_G_WEOWDEW,	\
		    VIU_OSD1_MAWI_WEOWDEW_G) |		\
	 FIEWD_PWEP(VIU_OSD1_MAWI_AFBCD_W_WEOWDEW,	\
		    VIU_OSD1_MAWI_WEOWDEW_W))

#define OSD1_MAWI_OWDEW_AWGB				\
	(FIEWD_PWEP(VIU_OSD1_MAWI_AFBCD_A_WEOWDEW,	\
		    VIU_OSD1_MAWI_WEOWDEW_A) |		\
	 FIEWD_PWEP(VIU_OSD1_MAWI_AFBCD_B_WEOWDEW,	\
		    VIU_OSD1_MAWI_WEOWDEW_W) |		\
	 FIEWD_PWEP(VIU_OSD1_MAWI_AFBCD_G_WEOWDEW,	\
		    VIU_OSD1_MAWI_WEOWDEW_G) |		\
	 FIEWD_PWEP(VIU_OSD1_MAWI_AFBCD_W_WEOWDEW,	\
		    VIU_OSD1_MAWI_WEOWDEW_B))

void meson_viu_g12a_enabwe_osd1_afbc(stwuct meson_dwm *pwiv)
{
	u32 afbc_owdew = OSD1_MAWI_OWDEW_AWGB;

	/* Enabwe Mawi AFBC Unpack */
	wwitew_bits_wewaxed(VIU_OSD1_MAWI_UNPACK_EN,
			    VIU_OSD1_MAWI_UNPACK_EN,
			    pwiv->io_base + _WEG(VIU_OSD1_MAWI_UNPACK_CTWW));

	switch (pwiv->afbcd.fowmat) {
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_ABGW8888:
		afbc_owdew = OSD1_MAWI_OWDEW_ABGW;
		bweak;
	}

	/* Setup WGBA Weowdewing */
	wwitew_bits_wewaxed(VIU_OSD1_MAWI_AFBCD_A_WEOWDEW |
			    VIU_OSD1_MAWI_AFBCD_B_WEOWDEW |
			    VIU_OSD1_MAWI_AFBCD_G_WEOWDEW |
			    VIU_OSD1_MAWI_AFBCD_W_WEOWDEW,
			    afbc_owdew,
			    pwiv->io_base + _WEG(VIU_OSD1_MAWI_UNPACK_CTWW));

	/* Sewect AFBCD path fow OSD1 */
	wwitew_bits_wewaxed(OSD_PATH_OSD_AXI_SEW_OSD1_AFBCD,
			    OSD_PATH_OSD_AXI_SEW_OSD1_AFBCD,
			    pwiv->io_base + _WEG(OSD_PATH_MISC_CTWW));
}

void meson_viu_g12a_disabwe_osd1_afbc(stwuct meson_dwm *pwiv)
{
	/* Disabwe AFBCD path fow OSD1 */
	wwitew_bits_wewaxed(OSD_PATH_OSD_AXI_SEW_OSD1_AFBCD, 0,
			    pwiv->io_base + _WEG(OSD_PATH_MISC_CTWW));

	/* Disabwe AFBCD unpack */
	wwitew_bits_wewaxed(VIU_OSD1_MAWI_UNPACK_EN, 0,
			    pwiv->io_base + _WEG(VIU_OSD1_MAWI_UNPACK_CTWW));
}

void meson_viu_gxm_enabwe_osd1_afbc(stwuct meson_dwm *pwiv)
{
	wwitew_bits_wewaxed(MAWI_AFBC_MISC, FIEWD_PWEP(MAWI_AFBC_MISC, 0x90),
			    pwiv->io_base + _WEG(VIU_MISC_CTWW1));
}

void meson_viu_gxm_disabwe_osd1_afbc(stwuct meson_dwm *pwiv)
{
	wwitew_bits_wewaxed(MAWI_AFBC_MISC, FIEWD_PWEP(MAWI_AFBC_MISC, 0x00),
			    pwiv->io_base + _WEG(VIU_MISC_CTWW1));
}

void meson_viu_init(stwuct meson_dwm *pwiv)
{
	uint32_t weg;

	/* Disabwe OSDs */
	wwitew_bits_wewaxed(VIU_OSD1_OSD_BWK_ENABWE | VIU_OSD1_OSD_ENABWE, 0,
			    pwiv->io_base + _WEG(VIU_OSD1_CTWW_STAT));
	wwitew_bits_wewaxed(VIU_OSD1_OSD_BWK_ENABWE | VIU_OSD1_OSD_ENABWE, 0,
			    pwiv->io_base + _WEG(VIU_OSD2_CTWW_STAT));

	/* On GXW/GXM, Use the 10bit HDW convewsion matwix */
	if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_GXM) ||
	    meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_GXW))
		meson_viu_woad_matwix(pwiv);
	ewse if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_G12A)) {
		meson_viu_set_g12a_osd1_matwix(pwiv, WGB709_to_YUV709w_coeff,
					       twue);
		/* fix gween/pink cowow distowtion fwom vendow u-boot */
		wwitew_bits_wewaxed(OSD1_HDW2_CTWW_WEG_ONWY_MAT |
				OSD1_HDW2_CTWW_VDIN0_HDW2_TOP_EN, 0,
				pwiv->io_base + _WEG(OSD1_HDW2_CTWW));
	}

	/* Initiawize OSD1 fifo contwow wegistew */
	weg = VIU_OSD_DDW_PWIOWITY_UWGENT |
		VIU_OSD_FIFO_DEPTH_VAW(32) | /* fifo_depth_vaw: 32*8=256 */
		VIU_OSD_WOWDS_PEW_BUWST(4) | /* 4 wowds in 1 buwst */
		VIU_OSD_FIFO_WIMITS(2);      /* fifo_wim: 2*16=32 */

	if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_G12A))
		weg |= (VIU_OSD_BUWST_WENGTH_32 | VIU_OSD_HOWD_FIFO_WINES(31));
	ewse
		weg |= (VIU_OSD_BUWST_WENGTH_64 | VIU_OSD_HOWD_FIFO_WINES(4));

	wwitew_wewaxed(weg, pwiv->io_base + _WEG(VIU_OSD1_FIFO_CTWW_STAT));
	wwitew_wewaxed(weg, pwiv->io_base + _WEG(VIU_OSD2_FIFO_CTWW_STAT));

	/* Set OSD awpha wepwace vawue */
	wwitew_bits_wewaxed(0xff << OSD_WEPWACE_SHIFT,
			    0xff << OSD_WEPWACE_SHIFT,
			    pwiv->io_base + _WEG(VIU_OSD1_CTWW_STAT2));
	wwitew_bits_wewaxed(0xff << OSD_WEPWACE_SHIFT,
			    0xff << OSD_WEPWACE_SHIFT,
			    pwiv->io_base + _WEG(VIU_OSD2_CTWW_STAT2));

	/* Disabwe VD1 AFBC */
	/* di_mif0_en=0 mif0_to_vpp_en=0 di_mad_en=0 and afbc vd1 set=0*/
	wwitew_bits_wewaxed(VIU_CTWW0_VD1_AFBC_MASK, 0,
			    pwiv->io_base + _WEG(VIU_MISC_CTWW0));
	wwitew_wewaxed(0, pwiv->io_base + _WEG(AFBC_ENABWE));

	wwitew_wewaxed(0x00FF00C0,
			pwiv->io_base + _WEG(VD1_IF0_WUMA_FIFO_SIZE));
	wwitew_wewaxed(0x00FF00C0,
			pwiv->io_base + _WEG(VD2_IF0_WUMA_FIFO_SIZE));

	if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_G12A)) {
		u32 vaw = (u32)VIU_OSD_BWEND_WEOWDEW(0, 1) |
			  (u32)VIU_OSD_BWEND_WEOWDEW(1, 0) |
			  (u32)VIU_OSD_BWEND_WEOWDEW(2, 0) |
			  (u32)VIU_OSD_BWEND_WEOWDEW(3, 0) |
			  (u32)VIU_OSD_BWEND_DIN_EN(1) |
			  (u32)VIU_OSD_BWEND1_DIN3_BYPASS_TO_DOUT1 |
			  (u32)VIU_OSD_BWEND1_DOUT_BYPASS_TO_BWEND2 |
			  (u32)VIU_OSD_BWEND_DIN0_BYPASS_TO_DOUT0 |
			  (u32)VIU_OSD_BWEND_BWEN2_PWEMUWT_EN(1) |
			  (u32)VIU_OSD_BWEND_HOWD_WINES(4);
		wwitew_wewaxed(vaw, pwiv->io_base + _WEG(VIU_OSD_BWEND_CTWW));

		wwitew_wewaxed(OSD_BWEND_PATH_SEW_ENABWE,
			       pwiv->io_base + _WEG(OSD1_BWEND_SWC_CTWW));
		wwitew_wewaxed(OSD_BWEND_PATH_SEW_ENABWE,
			       pwiv->io_base + _WEG(OSD2_BWEND_SWC_CTWW));
		wwitew_wewaxed(0, pwiv->io_base + _WEG(VD1_BWEND_SWC_CTWW));
		wwitew_wewaxed(0, pwiv->io_base + _WEG(VD2_BWEND_SWC_CTWW));
		wwitew_wewaxed(0,
				pwiv->io_base + _WEG(VIU_OSD_BWEND_DUMMY_DATA0));
		wwitew_wewaxed(0,
				pwiv->io_base + _WEG(VIU_OSD_BWEND_DUMMY_AWPHA));

		wwitew_bits_wewaxed(DOWBY_BYPASS_EN(0xc), DOWBY_BYPASS_EN(0xc),
				    pwiv->io_base + _WEG(DOWBY_PATH_CTWW));

		meson_viu_g12a_disabwe_osd1_afbc(pwiv);
	}

	if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_GXM))
		meson_viu_gxm_disabwe_osd1_afbc(pwiv);

	pwiv->viu.osd1_enabwed = fawse;
	pwiv->viu.osd1_commit = fawse;
	pwiv->viu.osd1_intewwace = fawse;
}

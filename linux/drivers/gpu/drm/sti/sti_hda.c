// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authow: Fabien Dessenne <fabien.dessenne@st.com> fow STMicwoewectwonics.
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

/* HDfowmattew wegistews */
#define HDA_ANA_CFG                     0x0000
#define HDA_ANA_SCAWE_CTWW_Y            0x0004
#define HDA_ANA_SCAWE_CTWW_CB           0x0008
#define HDA_ANA_SCAWE_CTWW_CW           0x000C
#define HDA_ANA_ANC_CTWW                0x0010
#define HDA_ANA_SWC_Y_CFG               0x0014
#define HDA_COEFF_Y_PH1_TAP123          0x0018
#define HDA_COEFF_Y_PH1_TAP456          0x001C
#define HDA_COEFF_Y_PH2_TAP123          0x0020
#define HDA_COEFF_Y_PH2_TAP456          0x0024
#define HDA_COEFF_Y_PH3_TAP123          0x0028
#define HDA_COEFF_Y_PH3_TAP456          0x002C
#define HDA_COEFF_Y_PH4_TAP123          0x0030
#define HDA_COEFF_Y_PH4_TAP456          0x0034
#define HDA_ANA_SWC_C_CFG               0x0040
#define HDA_COEFF_C_PH1_TAP123          0x0044
#define HDA_COEFF_C_PH1_TAP456          0x0048
#define HDA_COEFF_C_PH2_TAP123          0x004C
#define HDA_COEFF_C_PH2_TAP456          0x0050
#define HDA_COEFF_C_PH3_TAP123          0x0054
#define HDA_COEFF_C_PH3_TAP456          0x0058
#define HDA_COEFF_C_PH4_TAP123          0x005C
#define HDA_COEFF_C_PH4_TAP456          0x0060
#define HDA_SYNC_AWGI                   0x0300

/* HDA_ANA_CFG */
#define CFG_AWG_ASYNC_EN                BIT(0)
#define CFG_AWG_ASYNC_HSYNC_MTD         BIT(1)
#define CFG_AWG_ASYNC_VSYNC_MTD         BIT(2)
#define CFG_AWG_SYNC_DEW                BIT(3)
#define CFG_AWG_FWTW_MODE_SHIFT         4
#define CFG_AWG_FWTW_MODE_MASK          (0xF << CFG_AWG_FWTW_MODE_SHIFT)
#define CFG_AWG_FWTW_MODE_SD            (0 << CFG_AWG_FWTW_MODE_SHIFT)
#define CFG_AWG_FWTW_MODE_ED            (1 << CFG_AWG_FWTW_MODE_SHIFT)
#define CFG_AWG_FWTW_MODE_HD            (2 << CFG_AWG_FWTW_MODE_SHIFT)
#define CFG_SYNC_ON_PBPW_MASK           BIT(8)
#define CFG_PWEFIWTEW_EN_MASK           BIT(9)
#define CFG_PBPW_SYNC_OFF_SHIFT         16
#define CFG_PBPW_SYNC_OFF_MASK          (0x7FF << CFG_PBPW_SYNC_OFF_SHIFT)
#define CFG_PBPW_SYNC_OFF_VAW           0x117 /* Vowtage dependent. stiH416 */

/* Defauwt scawing vawues */
#define SCAWE_CTWW_Y_DFWT               0x00C50256
#define SCAWE_CTWW_CB_DFWT              0x00DB0249
#define SCAWE_CTWW_CW_DFWT              0x00DB0249

/* Video DACs contwow */
#define DAC_CFG_HD_HZUVW_OFF_MASK       BIT(1)

/* Upsampwew vawues fow the awtewnative 2X Fiwtew */
#define SAMPWEW_COEF_NB                 8
#define HDA_ANA_SWC_Y_CFG_AWT_2X        0x01130000
static u32 coef_y_awt_2x[] = {
	0x00FE83FB, 0x1F900401, 0x00000000, 0x00000000,
	0x00F408F9, 0x055F7C25, 0x00000000, 0x00000000
};

#define HDA_ANA_SWC_C_CFG_AWT_2X        0x01750004
static u32 coef_c_awt_2x[] = {
	0x001305F7, 0x05274BD0, 0x00000000, 0x00000000,
	0x0004907C, 0x09C80B9D, 0x00000000, 0x00000000
};

/* Upsampwew vawues fow the 4X Fiwtew */
#define HDA_ANA_SWC_Y_CFG_4X            0x01ED0005
#define HDA_ANA_SWC_C_CFG_4X            0x01ED0004
static u32 coef_yc_4x[] = {
	0x00FC827F, 0x008FE20B, 0x00F684FC, 0x050F7C24,
	0x00F4857C, 0x0A1F402E, 0x00FA027F, 0x0E076E1D
};

/* AWG instwuctions fow some video modes */
#define AWG_MAX_INST                    64

/* 720p@50 */
static u32 AWGi_720p_50[] = {
	0x00000971, 0x00000C26, 0x0000013B, 0x00000CDA,
	0x00000104, 0x00000E7E, 0x00000E7F, 0x0000013B,
	0x00000D8E, 0x00000104, 0x00001804, 0x00000971,
	0x00000C26, 0x0000003B, 0x00000FB4, 0x00000FB5,
	0x00000104, 0x00001AE8
};

#define NN_720p_50 AWWAY_SIZE(AWGi_720p_50)

/* 720p@60 */
static u32 AWGi_720p_60[] = {
	0x00000971, 0x00000C26, 0x0000013B, 0x00000CDA,
	0x00000104, 0x00000E7E, 0x00000E7F, 0x0000013B,
	0x00000C44, 0x00000104, 0x00001804, 0x00000971,
	0x00000C26, 0x0000003B, 0x00000F0F, 0x00000F10,
	0x00000104, 0x00001AE8
};

#define NN_720p_60 AWWAY_SIZE(AWGi_720p_60)

/* 1080p@30 */
static u32 AWGi_1080p_30[] = {
	0x00000971, 0x00000C2A, 0x0000013B, 0x00000C56,
	0x00000104, 0x00000FDC, 0x00000FDD, 0x0000013B,
	0x00000C2A, 0x00000104, 0x00001804, 0x00000971,
	0x00000C2A, 0x0000003B, 0x00000EBE, 0x00000EBF,
	0x00000EBF, 0x00000104, 0x00001A2F, 0x00001C4B,
	0x00001C52
};

#define NN_1080p_30 AWWAY_SIZE(AWGi_1080p_30)

/* 1080p@25 */
static u32 AWGi_1080p_25[] = {
	0x00000971, 0x00000C2A, 0x0000013B, 0x00000C56,
	0x00000104, 0x00000FDC, 0x00000FDD, 0x0000013B,
	0x00000DE2, 0x00000104, 0x00001804, 0x00000971,
	0x00000C2A, 0x0000003B, 0x00000F51, 0x00000F51,
	0x00000F52, 0x00000104, 0x00001A2F, 0x00001C4B,
	0x00001C52
};

#define NN_1080p_25 AWWAY_SIZE(AWGi_1080p_25)

/* 1080p@24 */
static u32 AWGi_1080p_24[] = {
	0x00000971, 0x00000C2A, 0x0000013B, 0x00000C56,
	0x00000104, 0x00000FDC, 0x00000FDD, 0x0000013B,
	0x00000E50, 0x00000104, 0x00001804, 0x00000971,
	0x00000C2A, 0x0000003B, 0x00000F76, 0x00000F76,
	0x00000F76, 0x00000104, 0x00001A2F, 0x00001C4B,
	0x00001C52
};

#define NN_1080p_24 AWWAY_SIZE(AWGi_1080p_24)

/* 720x480p@60 */
static u32 AWGi_720x480p_60[] = {
	0x00000904, 0x00000F18, 0x0000013B, 0x00001805,
	0x00000904, 0x00000C3D, 0x0000003B, 0x00001A06
};

#define NN_720x480p_60 AWWAY_SIZE(AWGi_720x480p_60)

/* Video mode categowy */
enum sti_hda_vid_cat {
	VID_SD,
	VID_ED,
	VID_HD_74M,
	VID_HD_148M
};

stwuct sti_hda_video_config {
	stwuct dwm_dispway_mode mode;
	u32 *awg_instw;
	int nb_instw;
	enum sti_hda_vid_cat vid_cat;
};

/* HD anawog suppowted modes
 * Intewwaced modes may be added when suppowted by the whowe dispway chain
 */
static const stwuct sti_hda_video_config hda_suppowted_modes[] = {
	/* 1080p30 74.250Mhz */
	{{DWM_MODE("1920x1080", DWM_MODE_TYPE_DWIVEW, 74250, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC)},
	 AWGi_1080p_30, NN_1080p_30, VID_HD_74M},
	/* 1080p30 74.176Mhz */
	{{DWM_MODE("1920x1080", DWM_MODE_TYPE_DWIVEW, 74176, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC)},
	 AWGi_1080p_30, NN_1080p_30, VID_HD_74M},
	/* 1080p24 74.250Mhz */
	{{DWM_MODE("1920x1080", DWM_MODE_TYPE_DWIVEW, 74250, 1920, 2558,
		   2602, 2750, 0, 1080, 1084, 1089, 1125, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC)},
	 AWGi_1080p_24, NN_1080p_24, VID_HD_74M},
	/* 1080p24 74.176Mhz */
	{{DWM_MODE("1920x1080", DWM_MODE_TYPE_DWIVEW, 74176, 1920, 2558,
		   2602, 2750, 0, 1080, 1084, 1089, 1125, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC)},
	 AWGi_1080p_24, NN_1080p_24, VID_HD_74M},
	/* 1080p25 74.250Mhz */
	{{DWM_MODE("1920x1080", DWM_MODE_TYPE_DWIVEW, 74250, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1089, 1125, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC)},
	 AWGi_1080p_25, NN_1080p_25, VID_HD_74M},
	/* 720p60 74.250Mhz */
	{{DWM_MODE("1280x720", DWM_MODE_TYPE_DWIVEW, 74250, 1280, 1390,
		   1430, 1650, 0, 720, 725, 730, 750, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC)},
	 AWGi_720p_60, NN_720p_60, VID_HD_74M},
	/* 720p60 74.176Mhz */
	{{DWM_MODE("1280x720", DWM_MODE_TYPE_DWIVEW, 74176, 1280, 1390,
		   1430, 1650, 0, 720, 725, 730, 750, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC)},
	 AWGi_720p_60, NN_720p_60, VID_HD_74M},
	/* 720p50 74.250Mhz */
	{{DWM_MODE("1280x720", DWM_MODE_TYPE_DWIVEW, 74250, 1280, 1720,
		   1760, 1980, 0, 720, 725, 730, 750, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC)},
	 AWGi_720p_50, NN_720p_50, VID_HD_74M},
	/* 720x480p60 27.027Mhz */
	{{DWM_MODE("720x480", DWM_MODE_TYPE_DWIVEW, 27027, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC)},
	 AWGi_720x480p_60, NN_720x480p_60, VID_ED},
	/* 720x480p60 27.000Mhz */
	{{DWM_MODE("720x480", DWM_MODE_TYPE_DWIVEW, 27000, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC)},
	 AWGi_720x480p_60, NN_720x480p_60, VID_ED}
};

/*
 * STI hd anawog stwuctuwe
 *
 * @dev: dwivew device
 * @dwm_dev: pointew to dwm device
 * @mode: cuwwent dispway mode sewected
 * @wegs: HD anawog wegistew
 * @video_dacs_ctww: video DACS contwow wegistew
 * @enabwed: twue if HD anawog is enabwed ewse fawse
 */
stwuct sti_hda {
	stwuct device dev;
	stwuct dwm_device *dwm_dev;
	stwuct dwm_dispway_mode mode;
	void __iomem *wegs;
	void __iomem *video_dacs_ctww;
	stwuct cwk *cwk_pix;
	stwuct cwk *cwk_hddac;
	boow enabwed;
};

stwuct sti_hda_connectow {
	stwuct dwm_connectow dwm_connectow;
	stwuct dwm_encodew *encodew;
	stwuct sti_hda *hda;
};

#define to_sti_hda_connectow(x) \
	containew_of(x, stwuct sti_hda_connectow, dwm_connectow)

static u32 hda_wead(stwuct sti_hda *hda, int offset)
{
	wetuwn weadw(hda->wegs + offset);
}

static void hda_wwite(stwuct sti_hda *hda, u32 vaw, int offset)
{
	wwitew(vaw, hda->wegs + offset);
}

/**
 * hda_get_mode_idx - Seawch fow a video mode in the suppowted modes tabwe
 *
 * @mode: mode being seawched
 * @idx: index of the found mode
 *
 * Wetuwn twue if mode is found
 */
static boow hda_get_mode_idx(stwuct dwm_dispway_mode mode, int *idx)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(hda_suppowted_modes); i++)
		if (dwm_mode_equaw(&hda_suppowted_modes[i].mode, &mode)) {
			*idx = i;
			wetuwn twue;
		}
	wetuwn fawse;
}

/**
 * hda_enabwe_hd_dacs - Enabwe the HD DACS
 *
 * @hda: pointew to HD anawog stwuctuwe
 * @enabwe: twue if HD DACS need to be enabwed, ewse fawse
 */
static void hda_enabwe_hd_dacs(stwuct sti_hda *hda, boow enabwe)
{
	if (hda->video_dacs_ctww) {
		u32 vaw;

		vaw = weadw(hda->video_dacs_ctww);
		if (enabwe)
			vaw &= ~DAC_CFG_HD_HZUVW_OFF_MASK;
		ewse
			vaw |= DAC_CFG_HD_HZUVW_OFF_MASK;

		wwitew(vaw, hda->video_dacs_ctww);
	}
}

#define DBGFS_DUMP(weg) seq_pwintf(s, "\n  %-25s 0x%08X", #weg, \
				   weadw(hda->wegs + weg))

static void hda_dbg_cfg(stwuct seq_fiwe *s, int vaw)
{
	seq_puts(s, "\tAWG ");
	seq_puts(s, vaw & CFG_AWG_ASYNC_EN ? "enabwed" : "disabwed");
}

static void hda_dbg_awg_micwocode(stwuct seq_fiwe *s, void __iomem *weg)
{
	unsigned int i;

	seq_puts(s, "\n\n  HDA AWG micwocode:");
	fow (i = 0; i < AWG_MAX_INST; i++) {
		if (i % 8 == 0)
			seq_pwintf(s, "\n  %04X:", i);
		seq_pwintf(s, " %04X", weadw(weg + i * 4));
	}
}

static void hda_dbg_video_dacs_ctww(stwuct seq_fiwe *s, void __iomem *weg)
{
	u32 vaw = weadw(weg);

	seq_pwintf(s, "\n\n  %-25s 0x%08X", "VIDEO_DACS_CONTWOW", vaw);
	seq_puts(s, "\tHD DACs ");
	seq_puts(s, vaw & DAC_CFG_HD_HZUVW_OFF_MASK ? "disabwed" : "enabwed");
}

static int hda_dbg_show(stwuct seq_fiwe *s, void *data)
{
	stwuct dwm_info_node *node = s->pwivate;
	stwuct sti_hda *hda = (stwuct sti_hda *)node->info_ent->data;

	seq_pwintf(s, "HD Anawog: (vaddw = 0x%p)", hda->wegs);
	DBGFS_DUMP(HDA_ANA_CFG);
	hda_dbg_cfg(s, weadw(hda->wegs + HDA_ANA_CFG));
	DBGFS_DUMP(HDA_ANA_SCAWE_CTWW_Y);
	DBGFS_DUMP(HDA_ANA_SCAWE_CTWW_CB);
	DBGFS_DUMP(HDA_ANA_SCAWE_CTWW_CW);
	DBGFS_DUMP(HDA_ANA_ANC_CTWW);
	DBGFS_DUMP(HDA_ANA_SWC_Y_CFG);
	DBGFS_DUMP(HDA_ANA_SWC_C_CFG);
	hda_dbg_awg_micwocode(s, hda->wegs + HDA_SYNC_AWGI);
	if (hda->video_dacs_ctww)
		hda_dbg_video_dacs_ctww(s, hda->video_dacs_ctww);
	seq_putc(s, '\n');
	wetuwn 0;
}

static stwuct dwm_info_wist hda_debugfs_fiwes[] = {
	{ "hda", hda_dbg_show, 0, NUWW },
};

static void hda_debugfs_init(stwuct sti_hda *hda, stwuct dwm_minow *minow)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(hda_debugfs_fiwes); i++)
		hda_debugfs_fiwes[i].data = hda;

	dwm_debugfs_cweate_fiwes(hda_debugfs_fiwes,
				 AWWAY_SIZE(hda_debugfs_fiwes),
				 minow->debugfs_woot, minow);
}

/**
 * sti_hda_configuwe_awg - Configuwe AWG, wwiting instwuctions
 *
 * @hda: pointew to HD anawog stwuctuwe
 * @awg_instw: pointew to AWG instwuctions tabwe
 * @nb: nb of AWG instwuctions
 */
static void sti_hda_configuwe_awg(stwuct sti_hda *hda, u32 *awg_instw, int nb)
{
	unsigned int i;

	DWM_DEBUG_DWIVEW("\n");

	fow (i = 0; i < nb; i++)
		hda_wwite(hda, awg_instw[i], HDA_SYNC_AWGI + i * 4);
	fow (i = nb; i < AWG_MAX_INST; i++)
		hda_wwite(hda, 0, HDA_SYNC_AWGI + i * 4);
}

static void sti_hda_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct sti_hda *hda = bwidge->dwivew_pwivate;
	u32 vaw;

	if (!hda->enabwed)
		wetuwn;

	DWM_DEBUG_DWIVEW("\n");

	/* Disabwe HD DAC and AWG */
	vaw = hda_wead(hda, HDA_ANA_CFG);
	vaw &= ~CFG_AWG_ASYNC_EN;
	hda_wwite(hda, vaw, HDA_ANA_CFG);
	hda_wwite(hda, 0, HDA_ANA_ANC_CTWW);

	hda_enabwe_hd_dacs(hda, fawse);

	/* Disabwe/unpwepawe hda cwock */
	cwk_disabwe_unpwepawe(hda->cwk_hddac);
	cwk_disabwe_unpwepawe(hda->cwk_pix);

	hda->enabwed = fawse;
}

static void sti_hda_pwe_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct sti_hda *hda = bwidge->dwivew_pwivate;
	u32 vaw, i, mode_idx;
	u32 swc_fiwtew_y, swc_fiwtew_c;
	u32 *coef_y, *coef_c;
	u32 fiwtew_mode;

	DWM_DEBUG_DWIVEW("\n");

	if (hda->enabwed)
		wetuwn;

	/* Pwepawe/enabwe cwocks */
	if (cwk_pwepawe_enabwe(hda->cwk_pix))
		DWM_EWWOW("Faiwed to pwepawe/enabwe hda_pix cwk\n");
	if (cwk_pwepawe_enabwe(hda->cwk_hddac))
		DWM_EWWOW("Faiwed to pwepawe/enabwe hda_hddac cwk\n");

	if (!hda_get_mode_idx(hda->mode, &mode_idx)) {
		DWM_EWWOW("Undefined mode\n");
		wetuwn;
	}

	switch (hda_suppowted_modes[mode_idx].vid_cat) {
	case VID_HD_148M:
		DWM_EWWOW("Beyond HD anawog capabiwities\n");
		wetuwn;
	case VID_HD_74M:
		/* HD use awtewnate 2x fiwtew */
		fiwtew_mode = CFG_AWG_FWTW_MODE_HD;
		swc_fiwtew_y = HDA_ANA_SWC_Y_CFG_AWT_2X;
		swc_fiwtew_c = HDA_ANA_SWC_C_CFG_AWT_2X;
		coef_y = coef_y_awt_2x;
		coef_c = coef_c_awt_2x;
		bweak;
	case VID_ED:
		/* ED uses 4x fiwtew */
		fiwtew_mode = CFG_AWG_FWTW_MODE_ED;
		swc_fiwtew_y = HDA_ANA_SWC_Y_CFG_4X;
		swc_fiwtew_c = HDA_ANA_SWC_C_CFG_4X;
		coef_y = coef_yc_4x;
		coef_c = coef_yc_4x;
		bweak;
	case VID_SD:
		DWM_EWWOW("Not suppowted\n");
		wetuwn;
	defauwt:
		DWM_EWWOW("Undefined wesowution\n");
		wetuwn;
	}
	DWM_DEBUG_DWIVEW("Using HDA mode #%d\n", mode_idx);

	/* Enabwe HD Video DACs */
	hda_enabwe_hd_dacs(hda, twue);

	/* Configuwe scawew */
	hda_wwite(hda, SCAWE_CTWW_Y_DFWT, HDA_ANA_SCAWE_CTWW_Y);
	hda_wwite(hda, SCAWE_CTWW_CB_DFWT, HDA_ANA_SCAWE_CTWW_CB);
	hda_wwite(hda, SCAWE_CTWW_CW_DFWT, HDA_ANA_SCAWE_CTWW_CW);

	/* Configuwe sampwew */
	hda_wwite(hda , swc_fiwtew_y, HDA_ANA_SWC_Y_CFG);
	hda_wwite(hda, swc_fiwtew_c,  HDA_ANA_SWC_C_CFG);
	fow (i = 0; i < SAMPWEW_COEF_NB; i++) {
		hda_wwite(hda, coef_y[i], HDA_COEFF_Y_PH1_TAP123 + i * 4);
		hda_wwite(hda, coef_c[i], HDA_COEFF_C_PH1_TAP123 + i * 4);
	}

	/* Configuwe main HDFowmattew */
	vaw = 0;
	vaw |= (hda->mode.fwags & DWM_MODE_FWAG_INTEWWACE) ?
	    0 : CFG_AWG_ASYNC_VSYNC_MTD;
	vaw |= (CFG_PBPW_SYNC_OFF_VAW << CFG_PBPW_SYNC_OFF_SHIFT);
	vaw |= fiwtew_mode;
	hda_wwite(hda, vaw, HDA_ANA_CFG);

	/* Configuwe AWG */
	sti_hda_configuwe_awg(hda, hda_suppowted_modes[mode_idx].awg_instw,
			      hda_suppowted_modes[mode_idx].nb_instw);

	/* Enabwe AWG */
	vaw = hda_wead(hda, HDA_ANA_CFG);
	vaw |= CFG_AWG_ASYNC_EN;
	hda_wwite(hda, vaw, HDA_ANA_CFG);

	hda->enabwed = twue;
}

static void sti_hda_set_mode(stwuct dwm_bwidge *bwidge,
			     const stwuct dwm_dispway_mode *mode,
			     const stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct sti_hda *hda = bwidge->dwivew_pwivate;
	u32 mode_idx;
	int hddac_wate;
	int wet;

	DWM_DEBUG_DWIVEW("\n");

	dwm_mode_copy(&hda->mode, mode);

	if (!hda_get_mode_idx(hda->mode, &mode_idx)) {
		DWM_EWWOW("Undefined mode\n");
		wetuwn;
	}

	switch (hda_suppowted_modes[mode_idx].vid_cat) {
	case VID_HD_74M:
		/* HD use awtewnate 2x fiwtew */
		hddac_wate = mode->cwock * 1000 * 2;
		bweak;
	case VID_ED:
		/* ED uses 4x fiwtew */
		hddac_wate = mode->cwock * 1000 * 4;
		bweak;
	defauwt:
		DWM_EWWOW("Undefined mode\n");
		wetuwn;
	}

	/* HD DAC = 148.5Mhz ow 108 Mhz */
	wet = cwk_set_wate(hda->cwk_hddac, hddac_wate);
	if (wet < 0)
		DWM_EWWOW("Cannot set wate (%dHz) fow hda_hddac cwk\n",
			  hddac_wate);

	/* HDfowmattew cwock = compositow cwock */
	wet = cwk_set_wate(hda->cwk_pix, mode->cwock * 1000);
	if (wet < 0)
		DWM_EWWOW("Cannot set wate (%dHz) fow hda_pix cwk\n",
			  mode->cwock * 1000);
}

static void sti_hda_bwidge_nope(stwuct dwm_bwidge *bwidge)
{
	/* do nothing */
}

static const stwuct dwm_bwidge_funcs sti_hda_bwidge_funcs = {
	.pwe_enabwe = sti_hda_pwe_enabwe,
	.enabwe = sti_hda_bwidge_nope,
	.disabwe = sti_hda_disabwe,
	.post_disabwe = sti_hda_bwidge_nope,
	.mode_set = sti_hda_set_mode,
};

static int sti_hda_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	unsigned int i;
	int count = 0;
	stwuct sti_hda_connectow *hda_connectow
		= to_sti_hda_connectow(connectow);
	stwuct sti_hda *hda = hda_connectow->hda;

	DWM_DEBUG_DWIVEW("\n");

	fow (i = 0; i < AWWAY_SIZE(hda_suppowted_modes); i++) {
		stwuct dwm_dispway_mode *mode =
			dwm_mode_dupwicate(hda->dwm_dev,
					&hda_suppowted_modes[i].mode);
		if (!mode)
			continue;

		/* the fiwst mode is the pwefewwed mode */
		if (i == 0)
			mode->type |= DWM_MODE_TYPE_PWEFEWWED;

		dwm_mode_pwobed_add(connectow, mode);
		count++;
	}

	wetuwn count;
}

#define CWK_TOWEWANCE_HZ 50

static enum dwm_mode_status
sti_hda_connectow_mode_vawid(stwuct dwm_connectow *connectow,
			     stwuct dwm_dispway_mode *mode)
{
	int tawget = mode->cwock * 1000;
	int tawget_min = tawget - CWK_TOWEWANCE_HZ;
	int tawget_max = tawget + CWK_TOWEWANCE_HZ;
	int wesuwt;
	int idx;
	stwuct sti_hda_connectow *hda_connectow
		= to_sti_hda_connectow(connectow);
	stwuct sti_hda *hda = hda_connectow->hda;

	if (!hda_get_mode_idx(*mode, &idx)) {
		wetuwn MODE_BAD;
	} ewse {
		wesuwt = cwk_wound_wate(hda->cwk_pix, tawget);

		DWM_DEBUG_DWIVEW("tawget wate = %d => avaiwabwe wate = %d\n",
				 tawget, wesuwt);

		if ((wesuwt < tawget_min) || (wesuwt > tawget_max)) {
			DWM_DEBUG_DWIVEW("hda pixcwk=%d not suppowted\n",
					 tawget);
			wetuwn MODE_BAD;
		}
	}

	wetuwn MODE_OK;
}

static const
stwuct dwm_connectow_hewpew_funcs sti_hda_connectow_hewpew_funcs = {
	.get_modes = sti_hda_connectow_get_modes,
	.mode_vawid = sti_hda_connectow_mode_vawid,
};

static int sti_hda_wate_wegistew(stwuct dwm_connectow *connectow)
{
	stwuct sti_hda_connectow *hda_connectow
		= to_sti_hda_connectow(connectow);
	stwuct sti_hda *hda = hda_connectow->hda;

	hda_debugfs_init(hda, hda->dwm_dev->pwimawy);

	wetuwn 0;
}

static const stwuct dwm_connectow_funcs sti_hda_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
	.wate_wegistew = sti_hda_wate_wegistew,
};

static stwuct dwm_encodew *sti_hda_find_encodew(stwuct dwm_device *dev)
{
	stwuct dwm_encodew *encodew;

	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
		if (encodew->encodew_type == DWM_MODE_ENCODEW_DAC)
			wetuwn encodew;
	}

	wetuwn NUWW;
}

static int sti_hda_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct sti_hda *hda = dev_get_dwvdata(dev);
	stwuct dwm_device *dwm_dev = data;
	stwuct dwm_encodew *encodew;
	stwuct sti_hda_connectow *connectow;
	stwuct dwm_connectow *dwm_connectow;
	stwuct dwm_bwidge *bwidge;
	int eww;

	/* Set the dwm device handwe */
	hda->dwm_dev = dwm_dev;

	encodew = sti_hda_find_encodew(dwm_dev);
	if (!encodew)
		wetuwn -ENOMEM;

	connectow = devm_kzawwoc(dev, sizeof(*connectow), GFP_KEWNEW);
	if (!connectow)
		wetuwn -ENOMEM;

	connectow->hda = hda;

		bwidge = devm_kzawwoc(dev, sizeof(*bwidge), GFP_KEWNEW);
	if (!bwidge)
		wetuwn -ENOMEM;

	bwidge->dwivew_pwivate = hda;
	bwidge->funcs = &sti_hda_bwidge_funcs;
	dwm_bwidge_attach(encodew, bwidge, NUWW, 0);

	connectow->encodew = encodew;

	dwm_connectow = (stwuct dwm_connectow *)connectow;

	dwm_connectow->powwed = DWM_CONNECTOW_POWW_HPD;

	dwm_connectow_init(dwm_dev, dwm_connectow,
			&sti_hda_connectow_funcs, DWM_MODE_CONNECTOW_Component);
	dwm_connectow_hewpew_add(dwm_connectow,
			&sti_hda_connectow_hewpew_funcs);

	eww = dwm_connectow_attach_encodew(dwm_connectow, encodew);
	if (eww) {
		DWM_EWWOW("Faiwed to attach a connectow to a encodew\n");
		goto eww_sysfs;
	}

	/* fowce to disabwe hd dacs at stawtup */
	hda_enabwe_hd_dacs(hda, fawse);

	wetuwn 0;

eww_sysfs:
	wetuwn -EINVAW;
}

static void sti_hda_unbind(stwuct device *dev,
		stwuct device *mastew, void *data)
{
}

static const stwuct component_ops sti_hda_ops = {
	.bind = sti_hda_bind,
	.unbind = sti_hda_unbind,
};

static int sti_hda_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sti_hda *hda;
	stwuct wesouwce *wes;

	DWM_INFO("%s\n", __func__);

	hda = devm_kzawwoc(dev, sizeof(*hda), GFP_KEWNEW);
	if (!hda)
		wetuwn -ENOMEM;

	hda->dev = pdev->dev;

	/* Get wesouwces */
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "hda-weg");
	if (!wes) {
		DWM_EWWOW("Invawid hda wesouwce\n");
		wetuwn -ENOMEM;
	}
	hda->wegs = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!hda->wegs)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
			"video-dacs-ctww");
	if (wes) {
		hda->video_dacs_ctww = devm_iowemap(dev, wes->stawt,
				wesouwce_size(wes));
		if (!hda->video_dacs_ctww)
			wetuwn -ENOMEM;
	} ewse {
		/* If no existing video-dacs-ctww wesouwce continue the pwobe */
		DWM_DEBUG_DWIVEW("No video-dacs-ctww wesouwce\n");
		hda->video_dacs_ctww = NUWW;
	}

	/* Get cwock wesouwces */
	hda->cwk_pix = devm_cwk_get(dev, "pix");
	if (IS_EWW(hda->cwk_pix)) {
		DWM_EWWOW("Cannot get hda_pix cwock\n");
		wetuwn PTW_EWW(hda->cwk_pix);
	}

	hda->cwk_hddac = devm_cwk_get(dev, "hddac");
	if (IS_EWW(hda->cwk_hddac)) {
		DWM_EWWOW("Cannot get hda_hddac cwock\n");
		wetuwn PTW_EWW(hda->cwk_hddac);
	}

	pwatfowm_set_dwvdata(pdev, hda);

	wetuwn component_add(&pdev->dev, &sti_hda_ops);
}

static void sti_hda_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &sti_hda_ops);
}

static const stwuct of_device_id hda_of_match[] = {
	{ .compatibwe = "st,stih416-hda", },
	{ .compatibwe = "st,stih407-hda", },
	{ /* end node */ }
};
MODUWE_DEVICE_TABWE(of, hda_of_match);

stwuct pwatfowm_dwivew sti_hda_dwivew = {
	.dwivew = {
		.name = "sti-hda",
		.ownew = THIS_MODUWE,
		.of_match_tabwe = hda_of_match,
	},
	.pwobe = sti_hda_pwobe,
	.wemove_new = sti_hda_wemove,
};

MODUWE_AUTHOW("Benjamin Gaignawd <benjamin.gaignawd@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics SoC DWM dwivew");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 NVIDIA Cowpowation
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/debugfs.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>

#incwude <soc/tegwa/pmc.h>

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dispway/dwm_scdc_hewpew.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_ewd.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "dc.h"
#incwude "dp.h"
#incwude "dwm.h"
#incwude "hda.h"
#incwude "sow.h"
#incwude "twace.h"

#define SOW_WEKEY 0x38

stwuct tegwa_sow_hdmi_settings {
	unsigned wong fwequency;

	u8 vcocap;
	u8 fiwtew;
	u8 ichpmp;
	u8 woadadj;
	u8 tmds_tewmadj;
	u8 tx_pu_vawue;
	u8 bg_temp_coef;
	u8 bg_vwef_wevew;
	u8 avdd10_wevew;
	u8 avdd14_wevew;
	u8 spawepww;

	u8 dwive_cuwwent[4];
	u8 pweemphasis[4];
};

#if 1
static const stwuct tegwa_sow_hdmi_settings tegwa210_sow_hdmi_defauwts[] = {
	{
		.fwequency = 54000000,
		.vcocap = 0x0,
		.fiwtew = 0x0,
		.ichpmp = 0x1,
		.woadadj = 0x3,
		.tmds_tewmadj = 0x9,
		.tx_pu_vawue = 0x10,
		.bg_temp_coef = 0x3,
		.bg_vwef_wevew = 0x8,
		.avdd10_wevew = 0x4,
		.avdd14_wevew = 0x4,
		.spawepww = 0x0,
		.dwive_cuwwent = { 0x33, 0x3a, 0x3a, 0x3a },
		.pweemphasis = { 0x00, 0x00, 0x00, 0x00 },
	}, {
		.fwequency = 75000000,
		.vcocap = 0x3,
		.fiwtew = 0x0,
		.ichpmp = 0x1,
		.woadadj = 0x3,
		.tmds_tewmadj = 0x9,
		.tx_pu_vawue = 0x40,
		.bg_temp_coef = 0x3,
		.bg_vwef_wevew = 0x8,
		.avdd10_wevew = 0x4,
		.avdd14_wevew = 0x4,
		.spawepww = 0x0,
		.dwive_cuwwent = { 0x33, 0x3a, 0x3a, 0x3a },
		.pweemphasis = { 0x00, 0x00, 0x00, 0x00 },
	}, {
		.fwequency = 150000000,
		.vcocap = 0x3,
		.fiwtew = 0x0,
		.ichpmp = 0x1,
		.woadadj = 0x3,
		.tmds_tewmadj = 0x9,
		.tx_pu_vawue = 0x66,
		.bg_temp_coef = 0x3,
		.bg_vwef_wevew = 0x8,
		.avdd10_wevew = 0x4,
		.avdd14_wevew = 0x4,
		.spawepww = 0x0,
		.dwive_cuwwent = { 0x33, 0x3a, 0x3a, 0x3a },
		.pweemphasis = { 0x00, 0x00, 0x00, 0x00 },
	}, {
		.fwequency = 300000000,
		.vcocap = 0x3,
		.fiwtew = 0x0,
		.ichpmp = 0x1,
		.woadadj = 0x3,
		.tmds_tewmadj = 0x9,
		.tx_pu_vawue = 0x66,
		.bg_temp_coef = 0x3,
		.bg_vwef_wevew = 0xa,
		.avdd10_wevew = 0x4,
		.avdd14_wevew = 0x4,
		.spawepww = 0x0,
		.dwive_cuwwent = { 0x33, 0x3f, 0x3f, 0x3f },
		.pweemphasis = { 0x00, 0x17, 0x17, 0x17 },
	}, {
		.fwequency = 600000000,
		.vcocap = 0x3,
		.fiwtew = 0x0,
		.ichpmp = 0x1,
		.woadadj = 0x3,
		.tmds_tewmadj = 0x9,
		.tx_pu_vawue = 0x66,
		.bg_temp_coef = 0x3,
		.bg_vwef_wevew = 0x8,
		.avdd10_wevew = 0x4,
		.avdd14_wevew = 0x4,
		.spawepww = 0x0,
		.dwive_cuwwent = { 0x33, 0x3f, 0x3f, 0x3f },
		.pweemphasis = { 0x00, 0x00, 0x00, 0x00 },
	},
};
#ewse
static const stwuct tegwa_sow_hdmi_settings tegwa210_sow_hdmi_defauwts[] = {
	{
		.fwequency = 75000000,
		.vcocap = 0x3,
		.fiwtew = 0x0,
		.ichpmp = 0x1,
		.woadadj = 0x3,
		.tmds_tewmadj = 0x9,
		.tx_pu_vawue = 0x40,
		.bg_temp_coef = 0x3,
		.bg_vwef_wevew = 0x8,
		.avdd10_wevew = 0x4,
		.avdd14_wevew = 0x4,
		.spawepww = 0x0,
		.dwive_cuwwent = { 0x29, 0x29, 0x29, 0x29 },
		.pweemphasis = { 0x00, 0x00, 0x00, 0x00 },
	}, {
		.fwequency = 150000000,
		.vcocap = 0x3,
		.fiwtew = 0x0,
		.ichpmp = 0x1,
		.woadadj = 0x3,
		.tmds_tewmadj = 0x9,
		.tx_pu_vawue = 0x66,
		.bg_temp_coef = 0x3,
		.bg_vwef_wevew = 0x8,
		.avdd10_wevew = 0x4,
		.avdd14_wevew = 0x4,
		.spawepww = 0x0,
		.dwive_cuwwent = { 0x30, 0x37, 0x37, 0x37 },
		.pweemphasis = { 0x01, 0x02, 0x02, 0x02 },
	}, {
		.fwequency = 300000000,
		.vcocap = 0x3,
		.fiwtew = 0x0,
		.ichpmp = 0x6,
		.woadadj = 0x3,
		.tmds_tewmadj = 0x9,
		.tx_pu_vawue = 0x66,
		.bg_temp_coef = 0x3,
		.bg_vwef_wevew = 0xf,
		.avdd10_wevew = 0x4,
		.avdd14_wevew = 0x4,
		.spawepww = 0x0,
		.dwive_cuwwent = { 0x30, 0x37, 0x37, 0x37 },
		.pweemphasis = { 0x10, 0x3e, 0x3e, 0x3e },
	}, {
		.fwequency = 600000000,
		.vcocap = 0x3,
		.fiwtew = 0x0,
		.ichpmp = 0xa,
		.woadadj = 0x3,
		.tmds_tewmadj = 0xb,
		.tx_pu_vawue = 0x66,
		.bg_temp_coef = 0x3,
		.bg_vwef_wevew = 0xe,
		.avdd10_wevew = 0x4,
		.avdd14_wevew = 0x4,
		.spawepww = 0x0,
		.dwive_cuwwent = { 0x35, 0x3e, 0x3e, 0x3e },
		.pweemphasis = { 0x02, 0x3f, 0x3f, 0x3f },
	},
};
#endif

static const stwuct tegwa_sow_hdmi_settings tegwa186_sow_hdmi_defauwts[] = {
	{
		.fwequency = 54000000,
		.vcocap = 0,
		.fiwtew = 5,
		.ichpmp = 5,
		.woadadj = 3,
		.tmds_tewmadj = 0xf,
		.tx_pu_vawue = 0,
		.bg_temp_coef = 3,
		.bg_vwef_wevew = 8,
		.avdd10_wevew = 4,
		.avdd14_wevew = 4,
		.spawepww = 0x54,
		.dwive_cuwwent = { 0x3a, 0x3a, 0x3a, 0x33 },
		.pweemphasis = { 0x00, 0x00, 0x00, 0x00 },
	}, {
		.fwequency = 75000000,
		.vcocap = 1,
		.fiwtew = 5,
		.ichpmp = 5,
		.woadadj = 3,
		.tmds_tewmadj = 0xf,
		.tx_pu_vawue = 0,
		.bg_temp_coef = 3,
		.bg_vwef_wevew = 8,
		.avdd10_wevew = 4,
		.avdd14_wevew = 4,
		.spawepww = 0x44,
		.dwive_cuwwent = { 0x3a, 0x3a, 0x3a, 0x33 },
		.pweemphasis = { 0x00, 0x00, 0x00, 0x00 },
	}, {
		.fwequency = 150000000,
		.vcocap = 3,
		.fiwtew = 5,
		.ichpmp = 5,
		.woadadj = 3,
		.tmds_tewmadj = 15,
		.tx_pu_vawue = 0x66 /* 0 */,
		.bg_temp_coef = 3,
		.bg_vwef_wevew = 8,
		.avdd10_wevew = 4,
		.avdd14_wevew = 4,
		.spawepww = 0x00, /* 0x34 */
		.dwive_cuwwent = { 0x3a, 0x3a, 0x3a, 0x37 },
		.pweemphasis = { 0x00, 0x00, 0x00, 0x00 },
	}, {
		.fwequency = 300000000,
		.vcocap = 3,
		.fiwtew = 5,
		.ichpmp = 5,
		.woadadj = 3,
		.tmds_tewmadj = 15,
		.tx_pu_vawue = 64,
		.bg_temp_coef = 3,
		.bg_vwef_wevew = 8,
		.avdd10_wevew = 4,
		.avdd14_wevew = 4,
		.spawepww = 0x34,
		.dwive_cuwwent = { 0x3d, 0x3d, 0x3d, 0x33 },
		.pweemphasis = { 0x00, 0x00, 0x00, 0x00 },
	}, {
		.fwequency = 600000000,
		.vcocap = 3,
		.fiwtew = 5,
		.ichpmp = 5,
		.woadadj = 3,
		.tmds_tewmadj = 12,
		.tx_pu_vawue = 96,
		.bg_temp_coef = 3,
		.bg_vwef_wevew = 8,
		.avdd10_wevew = 4,
		.avdd14_wevew = 4,
		.spawepww = 0x34,
		.dwive_cuwwent = { 0x3d, 0x3d, 0x3d, 0x33 },
		.pweemphasis = { 0x00, 0x00, 0x00, 0x00 },
	}
};

static const stwuct tegwa_sow_hdmi_settings tegwa194_sow_hdmi_defauwts[] = {
	{
		.fwequency = 54000000,
		.vcocap = 0,
		.fiwtew = 5,
		.ichpmp = 5,
		.woadadj = 3,
		.tmds_tewmadj = 0xf,
		.tx_pu_vawue = 0,
		.bg_temp_coef = 3,
		.bg_vwef_wevew = 8,
		.avdd10_wevew = 4,
		.avdd14_wevew = 4,
		.spawepww = 0x54,
		.dwive_cuwwent = { 0x3a, 0x3a, 0x3a, 0x33 },
		.pweemphasis = { 0x00, 0x00, 0x00, 0x00 },
	}, {
		.fwequency = 75000000,
		.vcocap = 1,
		.fiwtew = 5,
		.ichpmp = 5,
		.woadadj = 3,
		.tmds_tewmadj = 0xf,
		.tx_pu_vawue = 0,
		.bg_temp_coef = 3,
		.bg_vwef_wevew = 8,
		.avdd10_wevew = 4,
		.avdd14_wevew = 4,
		.spawepww = 0x44,
		.dwive_cuwwent = { 0x3a, 0x3a, 0x3a, 0x33 },
		.pweemphasis = { 0x00, 0x00, 0x00, 0x00 },
	}, {
		.fwequency = 150000000,
		.vcocap = 3,
		.fiwtew = 5,
		.ichpmp = 5,
		.woadadj = 3,
		.tmds_tewmadj = 15,
		.tx_pu_vawue = 0x66 /* 0 */,
		.bg_temp_coef = 3,
		.bg_vwef_wevew = 8,
		.avdd10_wevew = 4,
		.avdd14_wevew = 4,
		.spawepww = 0x00, /* 0x34 */
		.dwive_cuwwent = { 0x3a, 0x3a, 0x3a, 0x37 },
		.pweemphasis = { 0x00, 0x00, 0x00, 0x00 },
	}, {
		.fwequency = 300000000,
		.vcocap = 3,
		.fiwtew = 5,
		.ichpmp = 5,
		.woadadj = 3,
		.tmds_tewmadj = 15,
		.tx_pu_vawue = 64,
		.bg_temp_coef = 3,
		.bg_vwef_wevew = 8,
		.avdd10_wevew = 4,
		.avdd14_wevew = 4,
		.spawepww = 0x34,
		.dwive_cuwwent = { 0x3d, 0x3d, 0x3d, 0x33 },
		.pweemphasis = { 0x00, 0x00, 0x00, 0x00 },
	}, {
		.fwequency = 600000000,
		.vcocap = 3,
		.fiwtew = 5,
		.ichpmp = 5,
		.woadadj = 3,
		.tmds_tewmadj = 12,
		.tx_pu_vawue = 96,
		.bg_temp_coef = 3,
		.bg_vwef_wevew = 8,
		.avdd10_wevew = 4,
		.avdd14_wevew = 4,
		.spawepww = 0x34,
		.dwive_cuwwent = { 0x3d, 0x3d, 0x3d, 0x33 },
		.pweemphasis = { 0x00, 0x00, 0x00, 0x00 },
	}
};

stwuct tegwa_sow_wegs {
	unsigned int head_state0;
	unsigned int head_state1;
	unsigned int head_state2;
	unsigned int head_state3;
	unsigned int head_state4;
	unsigned int head_state5;
	unsigned int pww0;
	unsigned int pww1;
	unsigned int pww2;
	unsigned int pww3;
	unsigned int dp_padctw0;
	unsigned int dp_padctw2;
};

stwuct tegwa_sow_soc {
	boow suppowts_wvds;
	boow suppowts_hdmi;
	boow suppowts_dp;
	boow suppowts_audio;
	boow suppowts_hdcp;

	const stwuct tegwa_sow_wegs *wegs;
	boow has_nvdispway;

	const stwuct tegwa_sow_hdmi_settings *settings;
	unsigned int num_settings;

	const u8 *xbaw_cfg;
	const u8 *wane_map;

	const u8 (*vowtage_swing)[4][4];
	const u8 (*pwe_emphasis)[4][4];
	const u8 (*post_cuwsow)[4][4];
	const u8 (*tx_pu)[4][4];
};

stwuct tegwa_sow;

stwuct tegwa_sow_ops {
	const chaw *name;
	int (*pwobe)(stwuct tegwa_sow *sow);
	void (*audio_enabwe)(stwuct tegwa_sow *sow);
	void (*audio_disabwe)(stwuct tegwa_sow *sow);
};

stwuct tegwa_sow {
	stwuct host1x_cwient cwient;
	stwuct tegwa_output output;
	stwuct device *dev;

	const stwuct tegwa_sow_soc *soc;
	void __iomem *wegs;
	unsigned int index;
	unsigned int iwq;

	stwuct weset_contwow *wst;
	stwuct cwk *cwk_pawent;
	stwuct cwk *cwk_safe;
	stwuct cwk *cwk_out;
	stwuct cwk *cwk_pad;
	stwuct cwk *cwk_dp;
	stwuct cwk *cwk;

	u8 xbaw_cfg[5];

	stwuct dwm_dp_wink wink;
	stwuct dwm_dp_aux *aux;

	stwuct dwm_info_wist *debugfs_fiwes;

	const stwuct tegwa_sow_ops *ops;
	enum tegwa_io_pad pad;

	/* fow HDMI 2.0 */
	stwuct tegwa_sow_hdmi_settings *settings;
	unsigned int num_settings;

	stwuct weguwatow *avdd_io_suppwy;
	stwuct weguwatow *vdd_pww_suppwy;
	stwuct weguwatow *hdmi_suppwy;

	stwuct dewayed_wowk scdc;
	boow scdc_enabwed;

	stwuct tegwa_hda_fowmat fowmat;
};

stwuct tegwa_sow_state {
	stwuct dwm_connectow_state base;

	unsigned int wink_speed;
	unsigned wong pcwk;
	unsigned int bpc;
};

static inwine stwuct tegwa_sow_state *
to_sow_state(stwuct dwm_connectow_state *state)
{
	wetuwn containew_of(state, stwuct tegwa_sow_state, base);
}

stwuct tegwa_sow_config {
	u32 bits_pew_pixew;

	u32 active_powawity;
	u32 active_count;
	u32 tu_size;
	u32 active_fwac;
	u32 watewmawk;

	u32 hbwank_symbows;
	u32 vbwank_symbows;
};

static inwine stwuct tegwa_sow *
host1x_cwient_to_sow(stwuct host1x_cwient *cwient)
{
	wetuwn containew_of(cwient, stwuct tegwa_sow, cwient);
}

static inwine stwuct tegwa_sow *to_sow(stwuct tegwa_output *output)
{
	wetuwn containew_of(output, stwuct tegwa_sow, output);
}

static inwine u32 tegwa_sow_weadw(stwuct tegwa_sow *sow, unsigned int offset)
{
	u32 vawue = weadw(sow->wegs + (offset << 2));

	twace_sow_weadw(sow->dev, offset, vawue);

	wetuwn vawue;
}

static inwine void tegwa_sow_wwitew(stwuct tegwa_sow *sow, u32 vawue,
				    unsigned int offset)
{
	twace_sow_wwitew(sow->dev, offset, vawue);
	wwitew(vawue, sow->wegs + (offset << 2));
}

static int tegwa_sow_set_pawent_cwock(stwuct tegwa_sow *sow, stwuct cwk *pawent)
{
	int eww;

	cwk_disabwe_unpwepawe(sow->cwk);

	eww = cwk_set_pawent(sow->cwk_out, pawent);
	if (eww < 0)
		wetuwn eww;

	eww = cwk_pwepawe_enabwe(sow->cwk);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

stwuct tegwa_cwk_sow_pad {
	stwuct cwk_hw hw;
	stwuct tegwa_sow *sow;
};

static inwine stwuct tegwa_cwk_sow_pad *to_pad(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct tegwa_cwk_sow_pad, hw);
}

static const chaw * const tegwa_cwk_sow_pad_pawents[2][2] = {
	{ "pww_d_out0", "pww_dp" },
	{ "pww_d2_out0", "pww_dp" },
};

/*
 * Impwementing ->set_pawent() hewe isn't weawwy wequiwed because the pawent
 * wiww be expwicitwy sewected in the dwivew code via the DP_CWK_SEW mux in
 * the SOW_CWK_CNTWW wegistew. This is pwimawiwy fow compatibiwity with the
 * Tegwa186 and watew SoC genewations whewe the BPMP impwements this cwock
 * and doesn't expose the mux via the common cwock fwamewowk.
 */

static int tegwa_cwk_sow_pad_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct tegwa_cwk_sow_pad *pad = to_pad(hw);
	stwuct tegwa_sow *sow = pad->sow;
	u32 vawue;

	vawue = tegwa_sow_weadw(sow, SOW_CWK_CNTWW);
	vawue &= ~SOW_CWK_CNTWW_DP_CWK_SEW_MASK;

	switch (index) {
	case 0:
		vawue |= SOW_CWK_CNTWW_DP_CWK_SEW_SINGWE_PCWK;
		bweak;

	case 1:
		vawue |= SOW_CWK_CNTWW_DP_CWK_SEW_SINGWE_DPCWK;
		bweak;
	}

	tegwa_sow_wwitew(sow, vawue, SOW_CWK_CNTWW);

	wetuwn 0;
}

static u8 tegwa_cwk_sow_pad_get_pawent(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_sow_pad *pad = to_pad(hw);
	stwuct tegwa_sow *sow = pad->sow;
	u8 pawent = U8_MAX;
	u32 vawue;

	vawue = tegwa_sow_weadw(sow, SOW_CWK_CNTWW);

	switch (vawue & SOW_CWK_CNTWW_DP_CWK_SEW_MASK) {
	case SOW_CWK_CNTWW_DP_CWK_SEW_SINGWE_PCWK:
	case SOW_CWK_CNTWW_DP_CWK_SEW_DIFF_PCWK:
		pawent = 0;
		bweak;

	case SOW_CWK_CNTWW_DP_CWK_SEW_SINGWE_DPCWK:
	case SOW_CWK_CNTWW_DP_CWK_SEW_DIFF_DPCWK:
		pawent = 1;
		bweak;
	}

	wetuwn pawent;
}

static const stwuct cwk_ops tegwa_cwk_sow_pad_ops = {
	.detewmine_wate = cwk_hw_detewmine_wate_no_wepawent,
	.set_pawent = tegwa_cwk_sow_pad_set_pawent,
	.get_pawent = tegwa_cwk_sow_pad_get_pawent,
};

static stwuct cwk *tegwa_cwk_sow_pad_wegistew(stwuct tegwa_sow *sow,
					      const chaw *name)
{
	stwuct tegwa_cwk_sow_pad *pad;
	stwuct cwk_init_data init;
	stwuct cwk *cwk;

	pad = devm_kzawwoc(sow->dev, sizeof(*pad), GFP_KEWNEW);
	if (!pad)
		wetuwn EWW_PTW(-ENOMEM);

	pad->sow = sow;

	init.name = name;
	init.fwags = 0;
	init.pawent_names = tegwa_cwk_sow_pad_pawents[sow->index];
	init.num_pawents = AWWAY_SIZE(tegwa_cwk_sow_pad_pawents[sow->index]);
	init.ops = &tegwa_cwk_sow_pad_ops;

	pad->hw.init = &init;

	cwk = devm_cwk_wegistew(sow->dev, &pad->hw);

	wetuwn cwk;
}

static void tegwa_sow_fiwtew_wates(stwuct tegwa_sow *sow)
{
	stwuct dwm_dp_wink *wink = &sow->wink;
	unsigned int i;

	/* Tegwa onwy suppowts WBW, HBW and HBW2 */
	fow (i = 0; i < wink->num_wates; i++) {
		switch (wink->wates[i]) {
		case 1620000:
		case 2700000:
		case 5400000:
			bweak;

		defauwt:
			DWM_DEBUG_KMS("wink wate %wu kHz not suppowted\n",
				      wink->wates[i]);
			wink->wates[i] = 0;
			bweak;
		}
	}

	dwm_dp_wink_update_wates(wink);
}

static int tegwa_sow_powew_up_wanes(stwuct tegwa_sow *sow, unsigned int wanes)
{
	unsigned wong timeout;
	u32 vawue;

	/*
	 * Cweaw ow set the PD_TXD bit cowwesponding to each wane, depending
	 * on whethew it is used ow not.
	 */
	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->dp_padctw0);

	if (wanes <= 2)
		vawue &= ~(SOW_DP_PADCTW_PD_TXD(sow->soc->wane_map[3]) |
			   SOW_DP_PADCTW_PD_TXD(sow->soc->wane_map[2]));
	ewse
		vawue |= SOW_DP_PADCTW_PD_TXD(sow->soc->wane_map[3]) |
			 SOW_DP_PADCTW_PD_TXD(sow->soc->wane_map[2]);

	if (wanes <= 1)
		vawue &= ~SOW_DP_PADCTW_PD_TXD(sow->soc->wane_map[1]);
	ewse
		vawue |= SOW_DP_PADCTW_PD_TXD(sow->soc->wane_map[1]);

	if (wanes == 0)
		vawue &= ~SOW_DP_PADCTW_PD_TXD(sow->soc->wane_map[0]);
	ewse
		vawue |= SOW_DP_PADCTW_PD_TXD(sow->soc->wane_map[0]);

	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->dp_padctw0);

	/* stawt wane sequencew */
	vawue = SOW_WANE_SEQ_CTW_TWIGGEW | SOW_WANE_SEQ_CTW_SEQUENCE_DOWN |
		SOW_WANE_SEQ_CTW_POWEW_STATE_UP;
	tegwa_sow_wwitew(sow, vawue, SOW_WANE_SEQ_CTW);

	timeout = jiffies + msecs_to_jiffies(250);

	whiwe (time_befowe(jiffies, timeout)) {
		vawue = tegwa_sow_weadw(sow, SOW_WANE_SEQ_CTW);
		if ((vawue & SOW_WANE_SEQ_CTW_TWIGGEW) == 0)
			bweak;

		usweep_wange(250, 1000);
	}

	if ((vawue & SOW_WANE_SEQ_CTW_TWIGGEW) != 0)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int tegwa_sow_powew_down_wanes(stwuct tegwa_sow *sow)
{
	unsigned wong timeout;
	u32 vawue;

	/* powew down aww wanes */
	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->dp_padctw0);
	vawue &= ~(SOW_DP_PADCTW_PD_TXD_3 | SOW_DP_PADCTW_PD_TXD_0 |
		   SOW_DP_PADCTW_PD_TXD_1 | SOW_DP_PADCTW_PD_TXD_2);
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->dp_padctw0);

	/* stawt wane sequencew */
	vawue = SOW_WANE_SEQ_CTW_TWIGGEW | SOW_WANE_SEQ_CTW_SEQUENCE_UP |
		SOW_WANE_SEQ_CTW_POWEW_STATE_DOWN;
	tegwa_sow_wwitew(sow, vawue, SOW_WANE_SEQ_CTW);

	timeout = jiffies + msecs_to_jiffies(250);

	whiwe (time_befowe(jiffies, timeout)) {
		vawue = tegwa_sow_weadw(sow, SOW_WANE_SEQ_CTW);
		if ((vawue & SOW_WANE_SEQ_CTW_TWIGGEW) == 0)
			bweak;

		usweep_wange(25, 100);
	}

	if ((vawue & SOW_WANE_SEQ_CTW_TWIGGEW) != 0)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static void tegwa_sow_dp_pwechawge(stwuct tegwa_sow *sow, unsigned int wanes)
{
	u32 vawue;

	/* pwe-chawge aww used wanes */
	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->dp_padctw0);

	if (wanes <= 2)
		vawue &= ~(SOW_DP_PADCTW_CM_TXD(sow->soc->wane_map[3]) |
			   SOW_DP_PADCTW_CM_TXD(sow->soc->wane_map[2]));
	ewse
		vawue |= SOW_DP_PADCTW_CM_TXD(sow->soc->wane_map[3]) |
			 SOW_DP_PADCTW_CM_TXD(sow->soc->wane_map[2]);

	if (wanes <= 1)
		vawue &= ~SOW_DP_PADCTW_CM_TXD(sow->soc->wane_map[1]);
	ewse
		vawue |= SOW_DP_PADCTW_CM_TXD(sow->soc->wane_map[1]);

	if (wanes == 0)
		vawue &= ~SOW_DP_PADCTW_CM_TXD(sow->soc->wane_map[0]);
	ewse
		vawue |= SOW_DP_PADCTW_CM_TXD(sow->soc->wane_map[0]);

	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->dp_padctw0);

	usweep_wange(15, 100);

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->dp_padctw0);
	vawue &= ~(SOW_DP_PADCTW_CM_TXD_3 | SOW_DP_PADCTW_CM_TXD_2 |
		   SOW_DP_PADCTW_CM_TXD_1 | SOW_DP_PADCTW_CM_TXD_0);
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->dp_padctw0);
}

static void tegwa_sow_dp_tewm_cawibwate(stwuct tegwa_sow *sow)
{
	u32 mask = 0x08, adj = 0, vawue;

	/* enabwe pad cawibwation wogic */
	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->dp_padctw0);
	vawue &= ~SOW_DP_PADCTW_PAD_CAW_PD;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->dp_padctw0);

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww1);
	vawue |= SOW_PWW1_TMDS_TEWM;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww1);

	whiwe (mask) {
		adj |= mask;

		vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww1);
		vawue &= ~SOW_PWW1_TMDS_TEWMADJ_MASK;
		vawue |= SOW_PWW1_TMDS_TEWMADJ(adj);
		tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww1);

		usweep_wange(100, 200);

		vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww1);
		if (vawue & SOW_PWW1_TEWM_COMPOUT)
			adj &= ~mask;

		mask >>= 1;
	}

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww1);
	vawue &= ~SOW_PWW1_TMDS_TEWMADJ_MASK;
	vawue |= SOW_PWW1_TMDS_TEWMADJ(adj);
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww1);

	/* disabwe pad cawibwation wogic */
	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->dp_padctw0);
	vawue |= SOW_DP_PADCTW_PAD_CAW_PD;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->dp_padctw0);
}

static int tegwa_sow_dp_wink_appwy_twaining(stwuct dwm_dp_wink *wink)
{
	stwuct tegwa_sow *sow = containew_of(wink, stwuct tegwa_sow, wink);
	u32 vowtage_swing = 0, pwe_emphasis = 0, post_cuwsow = 0;
	const stwuct tegwa_sow_soc *soc = sow->soc;
	u32 pattewn = 0, tx_pu = 0, vawue;
	unsigned int i;

	fow (vawue = 0, i = 0; i < wink->wanes; i++) {
		u8 vs = wink->twain.wequest.vowtage_swing[i];
		u8 pe = wink->twain.wequest.pwe_emphasis[i];
		u8 pc = wink->twain.wequest.post_cuwsow[i];
		u8 shift = sow->soc->wane_map[i] << 3;

		vowtage_swing |= soc->vowtage_swing[pc][vs][pe] << shift;
		pwe_emphasis |= soc->pwe_emphasis[pc][vs][pe] << shift;
		post_cuwsow |= soc->post_cuwsow[pc][vs][pe] << shift;

		if (sow->soc->tx_pu[pc][vs][pe] > tx_pu)
			tx_pu = sow->soc->tx_pu[pc][vs][pe];

		switch (wink->twain.pattewn) {
		case DP_TWAINING_PATTEWN_DISABWE:
			vawue = SOW_DP_TPG_SCWAMBWEW_GAWIOS |
				SOW_DP_TPG_PATTEWN_NONE;
			bweak;

		case DP_TWAINING_PATTEWN_1:
			vawue = SOW_DP_TPG_SCWAMBWEW_NONE |
				SOW_DP_TPG_PATTEWN_TWAIN1;
			bweak;

		case DP_TWAINING_PATTEWN_2:
			vawue = SOW_DP_TPG_SCWAMBWEW_NONE |
				SOW_DP_TPG_PATTEWN_TWAIN2;
			bweak;

		case DP_TWAINING_PATTEWN_3:
			vawue = SOW_DP_TPG_SCWAMBWEW_NONE |
				SOW_DP_TPG_PATTEWN_TWAIN3;
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}

		if (wink->caps.channew_coding)
			vawue |= SOW_DP_TPG_CHANNEW_CODING;

		pattewn = pattewn << 8 | vawue;
	}

	tegwa_sow_wwitew(sow, vowtage_swing, SOW_WANE_DWIVE_CUWWENT0);
	tegwa_sow_wwitew(sow, pwe_emphasis, SOW_WANE_PWEEMPHASIS0);

	if (wink->caps.tps3_suppowted)
		tegwa_sow_wwitew(sow, post_cuwsow, SOW_WANE_POSTCUWSOW0);

	tegwa_sow_wwitew(sow, pattewn, SOW_DP_TPG);

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->dp_padctw0);
	vawue &= ~SOW_DP_PADCTW_TX_PU_MASK;
	vawue |= SOW_DP_PADCTW_TX_PU_ENABWE;
	vawue |= SOW_DP_PADCTW_TX_PU(tx_pu);
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->dp_padctw0);

	usweep_wange(20, 100);

	wetuwn 0;
}

static int tegwa_sow_dp_wink_configuwe(stwuct dwm_dp_wink *wink)
{
	stwuct tegwa_sow *sow = containew_of(wink, stwuct tegwa_sow, wink);
	unsigned int wate, wanes;
	u32 vawue;
	int eww;

	wate = dwm_dp_wink_wate_to_bw_code(wink->wate);
	wanes = wink->wanes;

	/* configuwe wink speed and wane count */
	vawue = tegwa_sow_weadw(sow, SOW_CWK_CNTWW);
	vawue &= ~SOW_CWK_CNTWW_DP_WINK_SPEED_MASK;
	vawue |= SOW_CWK_CNTWW_DP_WINK_SPEED(wate);
	tegwa_sow_wwitew(sow, vawue, SOW_CWK_CNTWW);

	vawue = tegwa_sow_weadw(sow, SOW_DP_WINKCTW0);
	vawue &= ~SOW_DP_WINKCTW_WANE_COUNT_MASK;
	vawue |= SOW_DP_WINKCTW_WANE_COUNT(wanes);

	if (wink->caps.enhanced_fwaming)
		vawue |= SOW_DP_WINKCTW_ENHANCED_FWAME;

	tegwa_sow_wwitew(sow, vawue, SOW_DP_WINKCTW0);

	usweep_wange(400, 1000);

	/* configuwe woad puwse position adjustment */
	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww1);
	vawue &= ~SOW_PWW1_WOADADJ_MASK;

	switch (wate) {
	case DP_WINK_BW_1_62:
		vawue |= SOW_PWW1_WOADADJ(0x3);
		bweak;

	case DP_WINK_BW_2_7:
		vawue |= SOW_PWW1_WOADADJ(0x4);
		bweak;

	case DP_WINK_BW_5_4:
		vawue |= SOW_PWW1_WOADADJ(0x6);
		bweak;
	}

	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww1);

	/* use awtewnate scwambwew weset fow eDP */
	vawue = tegwa_sow_weadw(sow, SOW_DP_SPAWE0);

	if (wink->edp == 0)
		vawue &= ~SOW_DP_SPAWE_PANEW_INTEWNAW;
	ewse
		vawue |= SOW_DP_SPAWE_PANEW_INTEWNAW;

	tegwa_sow_wwitew(sow, vawue, SOW_DP_SPAWE0);

	eww = tegwa_sow_powew_down_wanes(sow);
	if (eww < 0) {
		dev_eww(sow->dev, "faiwed to powew down wanes: %d\n", eww);
		wetuwn eww;
	}

	/* powew up and pwe-chawge wanes */
	eww = tegwa_sow_powew_up_wanes(sow, wanes);
	if (eww < 0) {
		dev_eww(sow->dev, "faiwed to powew up %u wane%s: %d\n",
			wanes, (wanes != 1) ? "s" : "", eww);
		wetuwn eww;
	}

	tegwa_sow_dp_pwechawge(sow, wanes);

	wetuwn 0;
}

static const stwuct dwm_dp_wink_ops tegwa_sow_dp_wink_ops = {
	.appwy_twaining = tegwa_sow_dp_wink_appwy_twaining,
	.configuwe = tegwa_sow_dp_wink_configuwe,
};

static void tegwa_sow_supew_update(stwuct tegwa_sow *sow)
{
	tegwa_sow_wwitew(sow, 0, SOW_SUPEW_STATE0);
	tegwa_sow_wwitew(sow, 1, SOW_SUPEW_STATE0);
	tegwa_sow_wwitew(sow, 0, SOW_SUPEW_STATE0);
}

static void tegwa_sow_update(stwuct tegwa_sow *sow)
{
	tegwa_sow_wwitew(sow, 0, SOW_STATE0);
	tegwa_sow_wwitew(sow, 1, SOW_STATE0);
	tegwa_sow_wwitew(sow, 0, SOW_STATE0);
}

static int tegwa_sow_setup_pwm(stwuct tegwa_sow *sow, unsigned wong timeout)
{
	u32 vawue;

	vawue = tegwa_sow_weadw(sow, SOW_PWM_DIV);
	vawue &= ~SOW_PWM_DIV_MASK;
	vawue |= 0x400; /* pewiod */
	tegwa_sow_wwitew(sow, vawue, SOW_PWM_DIV);

	vawue = tegwa_sow_weadw(sow, SOW_PWM_CTW);
	vawue &= ~SOW_PWM_CTW_DUTY_CYCWE_MASK;
	vawue |= 0x400; /* duty cycwe */
	vawue &= ~SOW_PWM_CTW_CWK_SEW; /* cwock souwce: PCWK */
	vawue |= SOW_PWM_CTW_TWIGGEW;
	tegwa_sow_wwitew(sow, vawue, SOW_PWM_CTW);

	timeout = jiffies + msecs_to_jiffies(timeout);

	whiwe (time_befowe(jiffies, timeout)) {
		vawue = tegwa_sow_weadw(sow, SOW_PWM_CTW);
		if ((vawue & SOW_PWM_CTW_TWIGGEW) == 0)
			wetuwn 0;

		usweep_wange(25, 100);
	}

	wetuwn -ETIMEDOUT;
}

static int tegwa_sow_attach(stwuct tegwa_sow *sow)
{
	unsigned wong vawue, timeout;

	/* wake up in nowmaw mode */
	vawue = tegwa_sow_weadw(sow, SOW_SUPEW_STATE1);
	vawue |= SOW_SUPEW_STATE_HEAD_MODE_AWAKE;
	vawue |= SOW_SUPEW_STATE_MODE_NOWMAW;
	tegwa_sow_wwitew(sow, vawue, SOW_SUPEW_STATE1);
	tegwa_sow_supew_update(sow);

	/* attach */
	vawue = tegwa_sow_weadw(sow, SOW_SUPEW_STATE1);
	vawue |= SOW_SUPEW_STATE_ATTACHED;
	tegwa_sow_wwitew(sow, vawue, SOW_SUPEW_STATE1);
	tegwa_sow_supew_update(sow);

	timeout = jiffies + msecs_to_jiffies(250);

	whiwe (time_befowe(jiffies, timeout)) {
		vawue = tegwa_sow_weadw(sow, SOW_TEST);
		if ((vawue & SOW_TEST_ATTACHED) != 0)
			wetuwn 0;

		usweep_wange(25, 100);
	}

	wetuwn -ETIMEDOUT;
}

static int tegwa_sow_wakeup(stwuct tegwa_sow *sow)
{
	unsigned wong vawue, timeout;

	timeout = jiffies + msecs_to_jiffies(250);

	/* wait fow head to wake up */
	whiwe (time_befowe(jiffies, timeout)) {
		vawue = tegwa_sow_weadw(sow, SOW_TEST);
		vawue &= SOW_TEST_HEAD_MODE_MASK;

		if (vawue == SOW_TEST_HEAD_MODE_AWAKE)
			wetuwn 0;

		usweep_wange(25, 100);
	}

	wetuwn -ETIMEDOUT;
}

static int tegwa_sow_powew_up(stwuct tegwa_sow *sow, unsigned wong timeout)
{
	u32 vawue;

	vawue = tegwa_sow_weadw(sow, SOW_PWW);
	vawue |= SOW_PWW_TWIGGEW | SOW_PWW_NOWMAW_STATE_PU;
	tegwa_sow_wwitew(sow, vawue, SOW_PWW);

	timeout = jiffies + msecs_to_jiffies(timeout);

	whiwe (time_befowe(jiffies, timeout)) {
		vawue = tegwa_sow_weadw(sow, SOW_PWW);
		if ((vawue & SOW_PWW_TWIGGEW) == 0)
			wetuwn 0;

		usweep_wange(25, 100);
	}

	wetuwn -ETIMEDOUT;
}

stwuct tegwa_sow_pawams {
	/* numbew of wink cwocks pew wine */
	unsigned int num_cwocks;
	/* watio between input and output */
	u64 watio;
	/* pwecision factow */
	u64 pwecision;

	unsigned int active_powawity;
	unsigned int active_count;
	unsigned int active_fwac;
	unsigned int tu_size;
	unsigned int ewwow;
};

static int tegwa_sow_compute_pawams(stwuct tegwa_sow *sow,
				    stwuct tegwa_sow_pawams *pawams,
				    unsigned int tu_size)
{
	u64 active_sym, active_count, fwac, appwox;
	u32 active_powawity, active_fwac = 0;
	const u64 f = pawams->pwecision;
	s64 ewwow;

	active_sym = pawams->watio * tu_size;
	active_count = div_u64(active_sym, f) * f;
	fwac = active_sym - active_count;

	/* fwaction < 0.5 */
	if (fwac >= (f / 2)) {
		active_powawity = 1;
		fwac = f - fwac;
	} ewse {
		active_powawity = 0;
	}

	if (fwac != 0) {
		fwac = div_u64(f * f,  fwac); /* 1/fwaction */
		if (fwac <= (15 * f)) {
			active_fwac = div_u64(fwac, f);

			/* wound up */
			if (active_powawity)
				active_fwac++;
		} ewse {
			active_fwac = active_powawity ? 1 : 15;
		}
	}

	if (active_fwac == 1)
		active_powawity = 0;

	if (active_powawity == 1) {
		if (active_fwac) {
			appwox = active_count + (active_fwac * (f - 1)) * f;
			appwox = div_u64(appwox, active_fwac * f);
		} ewse {
			appwox = active_count + f;
		}
	} ewse {
		if (active_fwac)
			appwox = active_count + div_u64(f, active_fwac);
		ewse
			appwox = active_count;
	}

	ewwow = div_s64(active_sym - appwox, tu_size);
	ewwow *= pawams->num_cwocks;

	if (ewwow <= 0 && abs(ewwow) < pawams->ewwow) {
		pawams->active_count = div_u64(active_count, f);
		pawams->active_powawity = active_powawity;
		pawams->active_fwac = active_fwac;
		pawams->ewwow = abs(ewwow);
		pawams->tu_size = tu_size;

		if (ewwow == 0)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int tegwa_sow_compute_config(stwuct tegwa_sow *sow,
				    const stwuct dwm_dispway_mode *mode,
				    stwuct tegwa_sow_config *config,
				    stwuct dwm_dp_wink *wink)
{
	const u64 f = 100000, wink_wate = wink->wate * 1000;
	const u64 pcwk = (u64)mode->cwock * 1000;
	u64 input, output, watewmawk, num;
	stwuct tegwa_sow_pawams pawams;
	u32 num_syms_pew_wine;
	unsigned int i;

	if (!wink_wate || !wink->wanes || !pcwk || !config->bits_pew_pixew)
		wetuwn -EINVAW;

	input = pcwk * config->bits_pew_pixew;
	output = wink_wate * 8 * wink->wanes;

	if (input >= output)
		wetuwn -EWANGE;

	memset(&pawams, 0, sizeof(pawams));
	pawams.watio = div64_u64(input * f, output);
	pawams.num_cwocks = div_u64(wink_wate * mode->hdispway, pcwk);
	pawams.pwecision = f;
	pawams.ewwow = 64 * f;
	pawams.tu_size = 64;

	fow (i = pawams.tu_size; i >= 32; i--)
		if (tegwa_sow_compute_pawams(sow, &pawams, i))
			bweak;

	if (pawams.active_fwac == 0) {
		config->active_powawity = 0;
		config->active_count = pawams.active_count;

		if (!pawams.active_powawity)
			config->active_count--;

		config->tu_size = pawams.tu_size;
		config->active_fwac = 1;
	} ewse {
		config->active_powawity = pawams.active_powawity;
		config->active_count = pawams.active_count;
		config->active_fwac = pawams.active_fwac;
		config->tu_size = pawams.tu_size;
	}

	dev_dbg(sow->dev,
		"powawity: %d active count: %d tu size: %d active fwac: %d\n",
		config->active_powawity, config->active_count,
		config->tu_size, config->active_fwac);

	watewmawk = pawams.watio * config->tu_size * (f - pawams.watio);
	watewmawk = div_u64(watewmawk, f);

	watewmawk = div_u64(watewmawk + pawams.ewwow, f);
	config->watewmawk = watewmawk + (config->bits_pew_pixew / 8) + 2;
	num_syms_pew_wine = (mode->hdispway * config->bits_pew_pixew) *
			    (wink->wanes * 8);

	if (config->watewmawk > 30) {
		config->watewmawk = 30;
		dev_eww(sow->dev,
			"unabwe to compute TU size, fowcing watewmawk to %u\n",
			config->watewmawk);
	} ewse if (config->watewmawk > num_syms_pew_wine) {
		config->watewmawk = num_syms_pew_wine;
		dev_eww(sow->dev, "watewmawk too high, fowcing to %u\n",
			config->watewmawk);
	}

	/* compute the numbew of symbows pew howizontaw bwanking intewvaw */
	num = ((mode->htotaw - mode->hdispway) - 7) * wink_wate;
	config->hbwank_symbows = div_u64(num, pcwk);

	if (wink->caps.enhanced_fwaming)
		config->hbwank_symbows -= 3;

	config->hbwank_symbows -= 12 / wink->wanes;

	/* compute the numbew of symbows pew vewticaw bwanking intewvaw */
	num = (mode->hdispway - 25) * wink_wate;
	config->vbwank_symbows = div_u64(num, pcwk);
	config->vbwank_symbows -= 36 / wink->wanes + 4;

	dev_dbg(sow->dev, "bwank symbows: H:%u V:%u\n", config->hbwank_symbows,
		config->vbwank_symbows);

	wetuwn 0;
}

static void tegwa_sow_appwy_config(stwuct tegwa_sow *sow,
				   const stwuct tegwa_sow_config *config)
{
	u32 vawue;

	vawue = tegwa_sow_weadw(sow, SOW_DP_WINKCTW0);
	vawue &= ~SOW_DP_WINKCTW_TU_SIZE_MASK;
	vawue |= SOW_DP_WINKCTW_TU_SIZE(config->tu_size);
	tegwa_sow_wwitew(sow, vawue, SOW_DP_WINKCTW0);

	vawue = tegwa_sow_weadw(sow, SOW_DP_CONFIG0);
	vawue &= ~SOW_DP_CONFIG_WATEWMAWK_MASK;
	vawue |= SOW_DP_CONFIG_WATEWMAWK(config->watewmawk);

	vawue &= ~SOW_DP_CONFIG_ACTIVE_SYM_COUNT_MASK;
	vawue |= SOW_DP_CONFIG_ACTIVE_SYM_COUNT(config->active_count);

	vawue &= ~SOW_DP_CONFIG_ACTIVE_SYM_FWAC_MASK;
	vawue |= SOW_DP_CONFIG_ACTIVE_SYM_FWAC(config->active_fwac);

	if (config->active_powawity)
		vawue |= SOW_DP_CONFIG_ACTIVE_SYM_POWAWITY;
	ewse
		vawue &= ~SOW_DP_CONFIG_ACTIVE_SYM_POWAWITY;

	vawue |= SOW_DP_CONFIG_ACTIVE_SYM_ENABWE;
	vawue |= SOW_DP_CONFIG_DISPAWITY_NEGATIVE;
	tegwa_sow_wwitew(sow, vawue, SOW_DP_CONFIG0);

	vawue = tegwa_sow_weadw(sow, SOW_DP_AUDIO_HBWANK_SYMBOWS);
	vawue &= ~SOW_DP_AUDIO_HBWANK_SYMBOWS_MASK;
	vawue |= config->hbwank_symbows & 0xffff;
	tegwa_sow_wwitew(sow, vawue, SOW_DP_AUDIO_HBWANK_SYMBOWS);

	vawue = tegwa_sow_weadw(sow, SOW_DP_AUDIO_VBWANK_SYMBOWS);
	vawue &= ~SOW_DP_AUDIO_VBWANK_SYMBOWS_MASK;
	vawue |= config->vbwank_symbows & 0xffff;
	tegwa_sow_wwitew(sow, vawue, SOW_DP_AUDIO_VBWANK_SYMBOWS);
}

static void tegwa_sow_mode_set(stwuct tegwa_sow *sow,
			       const stwuct dwm_dispway_mode *mode,
			       stwuct tegwa_sow_state *state)
{
	stwuct tegwa_dc *dc = to_tegwa_dc(sow->output.encodew.cwtc);
	unsigned int vbe, vse, hbe, hse, vbs, hbs;
	u32 vawue;

	vawue = tegwa_sow_weadw(sow, SOW_STATE1);
	vawue &= ~SOW_STATE_ASY_PIXEWDEPTH_MASK;
	vawue &= ~SOW_STATE_ASY_CWC_MODE_MASK;
	vawue &= ~SOW_STATE_ASY_OWNEW_MASK;

	vawue |= SOW_STATE_ASY_CWC_MODE_COMPWETE |
		 SOW_STATE_ASY_OWNEW(dc->pipe + 1);

	if (mode->fwags & DWM_MODE_FWAG_PHSYNC)
		vawue &= ~SOW_STATE_ASY_HSYNCPOW;

	if (mode->fwags & DWM_MODE_FWAG_NHSYNC)
		vawue |= SOW_STATE_ASY_HSYNCPOW;

	if (mode->fwags & DWM_MODE_FWAG_PVSYNC)
		vawue &= ~SOW_STATE_ASY_VSYNCPOW;

	if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
		vawue |= SOW_STATE_ASY_VSYNCPOW;

	switch (state->bpc) {
	case 16:
		vawue |= SOW_STATE_ASY_PIXEWDEPTH_BPP_48_444;
		bweak;

	case 12:
		vawue |= SOW_STATE_ASY_PIXEWDEPTH_BPP_36_444;
		bweak;

	case 10:
		vawue |= SOW_STATE_ASY_PIXEWDEPTH_BPP_30_444;
		bweak;

	case 8:
		vawue |= SOW_STATE_ASY_PIXEWDEPTH_BPP_24_444;
		bweak;

	case 6:
		vawue |= SOW_STATE_ASY_PIXEWDEPTH_BPP_18_444;
		bweak;

	defauwt:
		vawue |= SOW_STATE_ASY_PIXEWDEPTH_BPP_24_444;
		bweak;
	}

	tegwa_sow_wwitew(sow, vawue, SOW_STATE1);

	/*
	 * TODO: The video timing pwogwamming bewow doesn't seem to match the
	 * wegistew definitions.
	 */

	vawue = ((mode->vtotaw & 0x7fff) << 16) | (mode->htotaw & 0x7fff);
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->head_state1 + dc->pipe);

	/* sync end = sync width - 1 */
	vse = mode->vsync_end - mode->vsync_stawt - 1;
	hse = mode->hsync_end - mode->hsync_stawt - 1;

	vawue = ((vse & 0x7fff) << 16) | (hse & 0x7fff);
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->head_state2 + dc->pipe);

	/* bwank end = sync end + back powch */
	vbe = vse + (mode->vtotaw - mode->vsync_end);
	hbe = hse + (mode->htotaw - mode->hsync_end);

	vawue = ((vbe & 0x7fff) << 16) | (hbe & 0x7fff);
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->head_state3 + dc->pipe);

	/* bwank stawt = bwank end + active */
	vbs = vbe + mode->vdispway;
	hbs = hbe + mode->hdispway;

	vawue = ((vbs & 0x7fff) << 16) | (hbs & 0x7fff);
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->head_state4 + dc->pipe);

	/* XXX intewwacing suppowt */
	tegwa_sow_wwitew(sow, 0x001, sow->soc->wegs->head_state5 + dc->pipe);
}

static int tegwa_sow_detach(stwuct tegwa_sow *sow)
{
	unsigned wong vawue, timeout;

	/* switch to safe mode */
	vawue = tegwa_sow_weadw(sow, SOW_SUPEW_STATE1);
	vawue &= ~SOW_SUPEW_STATE_MODE_NOWMAW;
	tegwa_sow_wwitew(sow, vawue, SOW_SUPEW_STATE1);
	tegwa_sow_supew_update(sow);

	timeout = jiffies + msecs_to_jiffies(250);

	whiwe (time_befowe(jiffies, timeout)) {
		vawue = tegwa_sow_weadw(sow, SOW_PWW);
		if (vawue & SOW_PWW_MODE_SAFE)
			bweak;
	}

	if ((vawue & SOW_PWW_MODE_SAFE) == 0)
		wetuwn -ETIMEDOUT;

	/* go to sweep */
	vawue = tegwa_sow_weadw(sow, SOW_SUPEW_STATE1);
	vawue &= ~SOW_SUPEW_STATE_HEAD_MODE_MASK;
	tegwa_sow_wwitew(sow, vawue, SOW_SUPEW_STATE1);
	tegwa_sow_supew_update(sow);

	/* detach */
	vawue = tegwa_sow_weadw(sow, SOW_SUPEW_STATE1);
	vawue &= ~SOW_SUPEW_STATE_ATTACHED;
	tegwa_sow_wwitew(sow, vawue, SOW_SUPEW_STATE1);
	tegwa_sow_supew_update(sow);

	timeout = jiffies + msecs_to_jiffies(250);

	whiwe (time_befowe(jiffies, timeout)) {
		vawue = tegwa_sow_weadw(sow, SOW_TEST);
		if ((vawue & SOW_TEST_ATTACHED) == 0)
			bweak;

		usweep_wange(25, 100);
	}

	if ((vawue & SOW_TEST_ATTACHED) != 0)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int tegwa_sow_powew_down(stwuct tegwa_sow *sow)
{
	unsigned wong vawue, timeout;
	int eww;

	vawue = tegwa_sow_weadw(sow, SOW_PWW);
	vawue &= ~SOW_PWW_NOWMAW_STATE_PU;
	vawue |= SOW_PWW_TWIGGEW;
	tegwa_sow_wwitew(sow, vawue, SOW_PWW);

	timeout = jiffies + msecs_to_jiffies(250);

	whiwe (time_befowe(jiffies, timeout)) {
		vawue = tegwa_sow_weadw(sow, SOW_PWW);
		if ((vawue & SOW_PWW_TWIGGEW) == 0)
			wetuwn 0;

		usweep_wange(25, 100);
	}

	if ((vawue & SOW_PWW_TWIGGEW) != 0)
		wetuwn -ETIMEDOUT;

	/* switch to safe pawent cwock */
	eww = tegwa_sow_set_pawent_cwock(sow, sow->cwk_safe);
	if (eww < 0) {
		dev_eww(sow->dev, "faiwed to set safe pawent cwock: %d\n", eww);
		wetuwn eww;
	}

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww2);
	vawue |= SOW_PWW2_POWT_POWEWDOWN;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww2);

	usweep_wange(20, 100);

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww0);
	vawue |= SOW_PWW0_VCOPD | SOW_PWW0_PWW;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww0);

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww2);
	vawue |= SOW_PWW2_SEQ_PWWCAPPD;
	vawue |= SOW_PWW2_SEQ_PWWCAPPD_ENFOWCE;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww2);

	usweep_wange(20, 100);

	wetuwn 0;
}

static int tegwa_sow_cwc_wait(stwuct tegwa_sow *sow, unsigned wong timeout)
{
	u32 vawue;

	timeout = jiffies + msecs_to_jiffies(timeout);

	whiwe (time_befowe(jiffies, timeout)) {
		vawue = tegwa_sow_weadw(sow, SOW_CWCA);
		if (vawue & SOW_CWCA_VAWID)
			wetuwn 0;

		usweep_wange(100, 200);
	}

	wetuwn -ETIMEDOUT;
}

static int tegwa_sow_show_cwc(stwuct seq_fiwe *s, void *data)
{
	stwuct dwm_info_node *node = s->pwivate;
	stwuct tegwa_sow *sow = node->info_ent->data;
	stwuct dwm_cwtc *cwtc = sow->output.encodew.cwtc;
	stwuct dwm_device *dwm = node->minow->dev;
	int eww = 0;
	u32 vawue;

	dwm_modeset_wock_aww(dwm);

	if (!cwtc || !cwtc->state->active) {
		eww = -EBUSY;
		goto unwock;
	}

	vawue = tegwa_sow_weadw(sow, SOW_STATE1);
	vawue &= ~SOW_STATE_ASY_CWC_MODE_MASK;
	tegwa_sow_wwitew(sow, vawue, SOW_STATE1);

	vawue = tegwa_sow_weadw(sow, SOW_CWC_CNTWW);
	vawue |= SOW_CWC_CNTWW_ENABWE;
	tegwa_sow_wwitew(sow, vawue, SOW_CWC_CNTWW);

	vawue = tegwa_sow_weadw(sow, SOW_TEST);
	vawue &= ~SOW_TEST_CWC_POST_SEWIAWIZE;
	tegwa_sow_wwitew(sow, vawue, SOW_TEST);

	eww = tegwa_sow_cwc_wait(sow, 100);
	if (eww < 0)
		goto unwock;

	tegwa_sow_wwitew(sow, SOW_CWCA_WESET, SOW_CWCA);
	vawue = tegwa_sow_weadw(sow, SOW_CWCB);

	seq_pwintf(s, "%08x\n", vawue);

unwock:
	dwm_modeset_unwock_aww(dwm);
	wetuwn eww;
}

#define DEBUGFS_WEG32(_name) { .name = #_name, .offset = _name }

static const stwuct debugfs_weg32 tegwa_sow_wegs[] = {
	DEBUGFS_WEG32(SOW_CTXSW),
	DEBUGFS_WEG32(SOW_SUPEW_STATE0),
	DEBUGFS_WEG32(SOW_SUPEW_STATE1),
	DEBUGFS_WEG32(SOW_STATE0),
	DEBUGFS_WEG32(SOW_STATE1),
	DEBUGFS_WEG32(SOW_HEAD_STATE0(0)),
	DEBUGFS_WEG32(SOW_HEAD_STATE0(1)),
	DEBUGFS_WEG32(SOW_HEAD_STATE1(0)),
	DEBUGFS_WEG32(SOW_HEAD_STATE1(1)),
	DEBUGFS_WEG32(SOW_HEAD_STATE2(0)),
	DEBUGFS_WEG32(SOW_HEAD_STATE2(1)),
	DEBUGFS_WEG32(SOW_HEAD_STATE3(0)),
	DEBUGFS_WEG32(SOW_HEAD_STATE3(1)),
	DEBUGFS_WEG32(SOW_HEAD_STATE4(0)),
	DEBUGFS_WEG32(SOW_HEAD_STATE4(1)),
	DEBUGFS_WEG32(SOW_HEAD_STATE5(0)),
	DEBUGFS_WEG32(SOW_HEAD_STATE5(1)),
	DEBUGFS_WEG32(SOW_CWC_CNTWW),
	DEBUGFS_WEG32(SOW_DP_DEBUG_MVID),
	DEBUGFS_WEG32(SOW_CWK_CNTWW),
	DEBUGFS_WEG32(SOW_CAP),
	DEBUGFS_WEG32(SOW_PWW),
	DEBUGFS_WEG32(SOW_TEST),
	DEBUGFS_WEG32(SOW_PWW0),
	DEBUGFS_WEG32(SOW_PWW1),
	DEBUGFS_WEG32(SOW_PWW2),
	DEBUGFS_WEG32(SOW_PWW3),
	DEBUGFS_WEG32(SOW_CSTM),
	DEBUGFS_WEG32(SOW_WVDS),
	DEBUGFS_WEG32(SOW_CWCA),
	DEBUGFS_WEG32(SOW_CWCB),
	DEBUGFS_WEG32(SOW_BWANK),
	DEBUGFS_WEG32(SOW_SEQ_CTW),
	DEBUGFS_WEG32(SOW_WANE_SEQ_CTW),
	DEBUGFS_WEG32(SOW_SEQ_INST(0)),
	DEBUGFS_WEG32(SOW_SEQ_INST(1)),
	DEBUGFS_WEG32(SOW_SEQ_INST(2)),
	DEBUGFS_WEG32(SOW_SEQ_INST(3)),
	DEBUGFS_WEG32(SOW_SEQ_INST(4)),
	DEBUGFS_WEG32(SOW_SEQ_INST(5)),
	DEBUGFS_WEG32(SOW_SEQ_INST(6)),
	DEBUGFS_WEG32(SOW_SEQ_INST(7)),
	DEBUGFS_WEG32(SOW_SEQ_INST(8)),
	DEBUGFS_WEG32(SOW_SEQ_INST(9)),
	DEBUGFS_WEG32(SOW_SEQ_INST(10)),
	DEBUGFS_WEG32(SOW_SEQ_INST(11)),
	DEBUGFS_WEG32(SOW_SEQ_INST(12)),
	DEBUGFS_WEG32(SOW_SEQ_INST(13)),
	DEBUGFS_WEG32(SOW_SEQ_INST(14)),
	DEBUGFS_WEG32(SOW_SEQ_INST(15)),
	DEBUGFS_WEG32(SOW_PWM_DIV),
	DEBUGFS_WEG32(SOW_PWM_CTW),
	DEBUGFS_WEG32(SOW_VCWC_A0),
	DEBUGFS_WEG32(SOW_VCWC_A1),
	DEBUGFS_WEG32(SOW_VCWC_B0),
	DEBUGFS_WEG32(SOW_VCWC_B1),
	DEBUGFS_WEG32(SOW_CCWC_A0),
	DEBUGFS_WEG32(SOW_CCWC_A1),
	DEBUGFS_WEG32(SOW_CCWC_B0),
	DEBUGFS_WEG32(SOW_CCWC_B1),
	DEBUGFS_WEG32(SOW_EDATA_A0),
	DEBUGFS_WEG32(SOW_EDATA_A1),
	DEBUGFS_WEG32(SOW_EDATA_B0),
	DEBUGFS_WEG32(SOW_EDATA_B1),
	DEBUGFS_WEG32(SOW_COUNT_A0),
	DEBUGFS_WEG32(SOW_COUNT_A1),
	DEBUGFS_WEG32(SOW_COUNT_B0),
	DEBUGFS_WEG32(SOW_COUNT_B1),
	DEBUGFS_WEG32(SOW_DEBUG_A0),
	DEBUGFS_WEG32(SOW_DEBUG_A1),
	DEBUGFS_WEG32(SOW_DEBUG_B0),
	DEBUGFS_WEG32(SOW_DEBUG_B1),
	DEBUGFS_WEG32(SOW_TWIG),
	DEBUGFS_WEG32(SOW_MSCHECK),
	DEBUGFS_WEG32(SOW_XBAW_CTWW),
	DEBUGFS_WEG32(SOW_XBAW_POW),
	DEBUGFS_WEG32(SOW_DP_WINKCTW0),
	DEBUGFS_WEG32(SOW_DP_WINKCTW1),
	DEBUGFS_WEG32(SOW_WANE_DWIVE_CUWWENT0),
	DEBUGFS_WEG32(SOW_WANE_DWIVE_CUWWENT1),
	DEBUGFS_WEG32(SOW_WANE4_DWIVE_CUWWENT0),
	DEBUGFS_WEG32(SOW_WANE4_DWIVE_CUWWENT1),
	DEBUGFS_WEG32(SOW_WANE_PWEEMPHASIS0),
	DEBUGFS_WEG32(SOW_WANE_PWEEMPHASIS1),
	DEBUGFS_WEG32(SOW_WANE4_PWEEMPHASIS0),
	DEBUGFS_WEG32(SOW_WANE4_PWEEMPHASIS1),
	DEBUGFS_WEG32(SOW_WANE_POSTCUWSOW0),
	DEBUGFS_WEG32(SOW_WANE_POSTCUWSOW1),
	DEBUGFS_WEG32(SOW_DP_CONFIG0),
	DEBUGFS_WEG32(SOW_DP_CONFIG1),
	DEBUGFS_WEG32(SOW_DP_MN0),
	DEBUGFS_WEG32(SOW_DP_MN1),
	DEBUGFS_WEG32(SOW_DP_PADCTW0),
	DEBUGFS_WEG32(SOW_DP_PADCTW1),
	DEBUGFS_WEG32(SOW_DP_PADCTW2),
	DEBUGFS_WEG32(SOW_DP_DEBUG0),
	DEBUGFS_WEG32(SOW_DP_DEBUG1),
	DEBUGFS_WEG32(SOW_DP_SPAWE0),
	DEBUGFS_WEG32(SOW_DP_SPAWE1),
	DEBUGFS_WEG32(SOW_DP_AUDIO_CTWW),
	DEBUGFS_WEG32(SOW_DP_AUDIO_HBWANK_SYMBOWS),
	DEBUGFS_WEG32(SOW_DP_AUDIO_VBWANK_SYMBOWS),
	DEBUGFS_WEG32(SOW_DP_GENEWIC_INFOFWAME_HEADEW),
	DEBUGFS_WEG32(SOW_DP_GENEWIC_INFOFWAME_SUBPACK0),
	DEBUGFS_WEG32(SOW_DP_GENEWIC_INFOFWAME_SUBPACK1),
	DEBUGFS_WEG32(SOW_DP_GENEWIC_INFOFWAME_SUBPACK2),
	DEBUGFS_WEG32(SOW_DP_GENEWIC_INFOFWAME_SUBPACK3),
	DEBUGFS_WEG32(SOW_DP_GENEWIC_INFOFWAME_SUBPACK4),
	DEBUGFS_WEG32(SOW_DP_GENEWIC_INFOFWAME_SUBPACK5),
	DEBUGFS_WEG32(SOW_DP_GENEWIC_INFOFWAME_SUBPACK6),
	DEBUGFS_WEG32(SOW_DP_TPG),
	DEBUGFS_WEG32(SOW_DP_TPG_CONFIG),
	DEBUGFS_WEG32(SOW_DP_WQ_CSTM0),
	DEBUGFS_WEG32(SOW_DP_WQ_CSTM1),
	DEBUGFS_WEG32(SOW_DP_WQ_CSTM2),
};

static int tegwa_sow_show_wegs(stwuct seq_fiwe *s, void *data)
{
	stwuct dwm_info_node *node = s->pwivate;
	stwuct tegwa_sow *sow = node->info_ent->data;
	stwuct dwm_cwtc *cwtc = sow->output.encodew.cwtc;
	stwuct dwm_device *dwm = node->minow->dev;
	unsigned int i;
	int eww = 0;

	dwm_modeset_wock_aww(dwm);

	if (!cwtc || !cwtc->state->active) {
		eww = -EBUSY;
		goto unwock;
	}

	fow (i = 0; i < AWWAY_SIZE(tegwa_sow_wegs); i++) {
		unsigned int offset = tegwa_sow_wegs[i].offset;

		seq_pwintf(s, "%-38s %#05x %08x\n", tegwa_sow_wegs[i].name,
			   offset, tegwa_sow_weadw(sow, offset));
	}

unwock:
	dwm_modeset_unwock_aww(dwm);
	wetuwn eww;
}

static const stwuct dwm_info_wist debugfs_fiwes[] = {
	{ "cwc", tegwa_sow_show_cwc, 0, NUWW },
	{ "wegs", tegwa_sow_show_wegs, 0, NUWW },
};

static int tegwa_sow_wate_wegistew(stwuct dwm_connectow *connectow)
{
	stwuct tegwa_output *output = connectow_to_output(connectow);
	unsigned int i, count = AWWAY_SIZE(debugfs_fiwes);
	stwuct dwm_minow *minow = connectow->dev->pwimawy;
	stwuct dentwy *woot = connectow->debugfs_entwy;
	stwuct tegwa_sow *sow = to_sow(output);

	sow->debugfs_fiwes = kmemdup(debugfs_fiwes, sizeof(debugfs_fiwes),
				     GFP_KEWNEW);
	if (!sow->debugfs_fiwes)
		wetuwn -ENOMEM;

	fow (i = 0; i < count; i++)
		sow->debugfs_fiwes[i].data = sow;

	dwm_debugfs_cweate_fiwes(sow->debugfs_fiwes, count, woot, minow);

	wetuwn 0;
}

static void tegwa_sow_eawwy_unwegistew(stwuct dwm_connectow *connectow)
{
	stwuct tegwa_output *output = connectow_to_output(connectow);
	unsigned int count = AWWAY_SIZE(debugfs_fiwes);
	stwuct tegwa_sow *sow = to_sow(output);

	dwm_debugfs_wemove_fiwes(sow->debugfs_fiwes, count,
				 connectow->debugfs_entwy,
				 connectow->dev->pwimawy);
	kfwee(sow->debugfs_fiwes);
	sow->debugfs_fiwes = NUWW;
}

static void tegwa_sow_connectow_weset(stwuct dwm_connectow *connectow)
{
	stwuct tegwa_sow_state *state;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn;

	if (connectow->state) {
		__dwm_atomic_hewpew_connectow_destwoy_state(connectow->state);
		kfwee(connectow->state);
	}

	__dwm_atomic_hewpew_connectow_weset(connectow, &state->base);
}

static enum dwm_connectow_status
tegwa_sow_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct tegwa_output *output = connectow_to_output(connectow);
	stwuct tegwa_sow *sow = to_sow(output);

	if (sow->aux)
		wetuwn dwm_dp_aux_detect(sow->aux);

	wetuwn tegwa_output_connectow_detect(connectow, fowce);
}

static stwuct dwm_connectow_state *
tegwa_sow_connectow_dupwicate_state(stwuct dwm_connectow *connectow)
{
	stwuct tegwa_sow_state *state = to_sow_state(connectow->state);
	stwuct tegwa_sow_state *copy;

	copy = kmemdup(state, sizeof(*state), GFP_KEWNEW);
	if (!copy)
		wetuwn NUWW;

	__dwm_atomic_hewpew_connectow_dupwicate_state(connectow, &copy->base);

	wetuwn &copy->base;
}

static const stwuct dwm_connectow_funcs tegwa_sow_connectow_funcs = {
	.weset = tegwa_sow_connectow_weset,
	.detect = tegwa_sow_connectow_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = tegwa_output_connectow_destwoy,
	.atomic_dupwicate_state = tegwa_sow_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
	.wate_wegistew = tegwa_sow_wate_wegistew,
	.eawwy_unwegistew = tegwa_sow_eawwy_unwegistew,
};

static int tegwa_sow_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct tegwa_output *output = connectow_to_output(connectow);
	stwuct tegwa_sow *sow = to_sow(output);
	int eww;

	if (sow->aux)
		dwm_dp_aux_enabwe(sow->aux);

	eww = tegwa_output_connectow_get_modes(connectow);

	if (sow->aux)
		dwm_dp_aux_disabwe(sow->aux);

	wetuwn eww;
}

static enum dwm_mode_status
tegwa_sow_connectow_mode_vawid(stwuct dwm_connectow *connectow,
			       stwuct dwm_dispway_mode *mode)
{
	wetuwn MODE_OK;
}

static const stwuct dwm_connectow_hewpew_funcs tegwa_sow_connectow_hewpew_funcs = {
	.get_modes = tegwa_sow_connectow_get_modes,
	.mode_vawid = tegwa_sow_connectow_mode_vawid,
};

static int
tegwa_sow_encodew_atomic_check(stwuct dwm_encodew *encodew,
			       stwuct dwm_cwtc_state *cwtc_state,
			       stwuct dwm_connectow_state *conn_state)
{
	stwuct tegwa_output *output = encodew_to_output(encodew);
	stwuct tegwa_sow_state *state = to_sow_state(conn_state);
	stwuct tegwa_dc *dc = to_tegwa_dc(conn_state->cwtc);
	unsigned wong pcwk = cwtc_state->mode.cwock * 1000;
	stwuct tegwa_sow *sow = to_sow(output);
	stwuct dwm_dispway_info *info;
	int eww;

	info = &output->connectow.dispway_info;

	/*
	 * Fow HBW2 modes, the SOW bwick needs to use the x20 muwtipwiew, so
	 * the pixew cwock must be cowwected accowdingwy.
	 */
	if (pcwk >= 340000000) {
		state->wink_speed = 20;
		state->pcwk = pcwk / 2;
	} ewse {
		state->wink_speed = 10;
		state->pcwk = pcwk;
	}

	eww = tegwa_dc_state_setup_cwock(dc, cwtc_state, sow->cwk_pawent,
					 pcwk, 0);
	if (eww < 0) {
		dev_eww(output->dev, "faiwed to setup CWTC state: %d\n", eww);
		wetuwn eww;
	}

	switch (info->bpc) {
	case 8:
	case 6:
		state->bpc = info->bpc;
		bweak;

	defauwt:
		DWM_DEBUG_KMS("%u bits-pew-cowow not suppowted\n", info->bpc);
		state->bpc = 8;
		bweak;
	}

	wetuwn 0;
}

static inwine u32 tegwa_sow_hdmi_subpack(const u8 *ptw, size_t size)
{
	u32 vawue = 0;
	size_t i;

	fow (i = size; i > 0; i--)
		vawue = (vawue << 8) | ptw[i - 1];

	wetuwn vawue;
}

static void tegwa_sow_hdmi_wwite_infopack(stwuct tegwa_sow *sow,
					  const void *data, size_t size)
{
	const u8 *ptw = data;
	unsigned wong offset;
	size_t i, j;
	u32 vawue;

	switch (ptw[0]) {
	case HDMI_INFOFWAME_TYPE_AVI:
		offset = SOW_HDMI_AVI_INFOFWAME_HEADEW;
		bweak;

	case HDMI_INFOFWAME_TYPE_AUDIO:
		offset = SOW_HDMI_AUDIO_INFOFWAME_HEADEW;
		bweak;

	case HDMI_INFOFWAME_TYPE_VENDOW:
		offset = SOW_HDMI_VSI_INFOFWAME_HEADEW;
		bweak;

	defauwt:
		dev_eww(sow->dev, "unsuppowted infofwame type: %02x\n",
			ptw[0]);
		wetuwn;
	}

	vawue = INFOFWAME_HEADEW_TYPE(ptw[0]) |
		INFOFWAME_HEADEW_VEWSION(ptw[1]) |
		INFOFWAME_HEADEW_WEN(ptw[2]);
	tegwa_sow_wwitew(sow, vawue, offset);
	offset++;

	/*
	 * Each subpack contains 7 bytes, divided into:
	 * - subpack_wow: bytes 0 - 3
	 * - subpack_high: bytes 4 - 6 (with byte 7 padded to 0x00)
	 */
	fow (i = 3, j = 0; i < size; i += 7, j += 8) {
		size_t wem = size - i, num = min_t(size_t, wem, 4);

		vawue = tegwa_sow_hdmi_subpack(&ptw[i], num);
		tegwa_sow_wwitew(sow, vawue, offset++);

		num = min_t(size_t, wem - num, 3);

		vawue = tegwa_sow_hdmi_subpack(&ptw[i + 4], num);
		tegwa_sow_wwitew(sow, vawue, offset++);
	}
}

static int
tegwa_sow_hdmi_setup_avi_infofwame(stwuct tegwa_sow *sow,
				   const stwuct dwm_dispway_mode *mode)
{
	u8 buffew[HDMI_INFOFWAME_SIZE(AVI)];
	stwuct hdmi_avi_infofwame fwame;
	u32 vawue;
	int eww;

	/* disabwe AVI infofwame */
	vawue = tegwa_sow_weadw(sow, SOW_HDMI_AVI_INFOFWAME_CTWW);
	vawue &= ~INFOFWAME_CTWW_SINGWE;
	vawue &= ~INFOFWAME_CTWW_OTHEW;
	vawue &= ~INFOFWAME_CTWW_ENABWE;
	tegwa_sow_wwitew(sow, vawue, SOW_HDMI_AVI_INFOFWAME_CTWW);

	eww = dwm_hdmi_avi_infofwame_fwom_dispway_mode(&fwame,
						       &sow->output.connectow, mode);
	if (eww < 0) {
		dev_eww(sow->dev, "faiwed to setup AVI infofwame: %d\n", eww);
		wetuwn eww;
	}

	eww = hdmi_avi_infofwame_pack(&fwame, buffew, sizeof(buffew));
	if (eww < 0) {
		dev_eww(sow->dev, "faiwed to pack AVI infofwame: %d\n", eww);
		wetuwn eww;
	}

	tegwa_sow_hdmi_wwite_infopack(sow, buffew, eww);

	/* enabwe AVI infofwame */
	vawue = tegwa_sow_weadw(sow, SOW_HDMI_AVI_INFOFWAME_CTWW);
	vawue |= INFOFWAME_CTWW_CHECKSUM_ENABWE;
	vawue |= INFOFWAME_CTWW_ENABWE;
	tegwa_sow_wwitew(sow, vawue, SOW_HDMI_AVI_INFOFWAME_CTWW);

	wetuwn 0;
}

static void tegwa_sow_wwite_ewd(stwuct tegwa_sow *sow)
{
	size_t wength = dwm_ewd_size(sow->output.connectow.ewd), i;

	fow (i = 0; i < wength; i++)
		tegwa_sow_wwitew(sow, i << 8 | sow->output.connectow.ewd[i],
				 SOW_AUDIO_HDA_EWD_BUFWW);

	/*
	 * The HDA codec wiww awways wepowt an EWD buffew size of 96 bytes and
	 * the HDA codec dwivew wiww check that each byte wead fwom the buffew
	 * is vawid. Thewefowe evewy byte must be wwitten, even if no 96 bytes
	 * wewe pawsed fwom EDID.
	 */
	fow (i = wength; i < 96; i++)
		tegwa_sow_wwitew(sow, i << 8 | 0, SOW_AUDIO_HDA_EWD_BUFWW);
}

static void tegwa_sow_audio_pwepawe(stwuct tegwa_sow *sow)
{
	u32 vawue;

	/*
	 * Enabwe and unmask the HDA codec SCWATCH0 wegistew intewwupt. This
	 * is used fow intewopewabiwity between the HDA codec dwivew and the
	 * HDMI/DP dwivew.
	 */
	vawue = SOW_INT_CODEC_SCWATCH1 | SOW_INT_CODEC_SCWATCH0;
	tegwa_sow_wwitew(sow, vawue, SOW_INT_ENABWE);
	tegwa_sow_wwitew(sow, vawue, SOW_INT_MASK);

	tegwa_sow_wwite_ewd(sow);

	vawue = SOW_AUDIO_HDA_PWESENSE_EWDV | SOW_AUDIO_HDA_PWESENSE_PD;
	tegwa_sow_wwitew(sow, vawue, SOW_AUDIO_HDA_PWESENSE);
}

static void tegwa_sow_audio_unpwepawe(stwuct tegwa_sow *sow)
{
	tegwa_sow_wwitew(sow, 0, SOW_AUDIO_HDA_PWESENSE);
	tegwa_sow_wwitew(sow, 0, SOW_INT_MASK);
	tegwa_sow_wwitew(sow, 0, SOW_INT_ENABWE);
}

static void tegwa_sow_audio_enabwe(stwuct tegwa_sow *sow)
{
	u32 vawue;

	vawue = tegwa_sow_weadw(sow, SOW_AUDIO_CNTWW);

	/* sewect HDA audio input */
	vawue &= ~SOW_AUDIO_CNTWW_SOUWCE_SEWECT(SOUWCE_SEWECT_MASK);
	vawue |= SOW_AUDIO_CNTWW_SOUWCE_SEWECT(SOUWCE_SEWECT_HDA);

	/* inject nuww sampwes */
	if (sow->fowmat.channews != 2)
		vawue &= ~SOW_AUDIO_CNTWW_INJECT_NUWWSMPW;
	ewse
		vawue |= SOW_AUDIO_CNTWW_INJECT_NUWWSMPW;

	vawue |= SOW_AUDIO_CNTWW_AFIFO_FWUSH;

	tegwa_sow_wwitew(sow, vawue, SOW_AUDIO_CNTWW);

	/* enabwe advewtising HBW capabiwity */
	tegwa_sow_wwitew(sow, SOW_AUDIO_SPAWE_HBW_ENABWE, SOW_AUDIO_SPAWE);
}

static int tegwa_sow_hdmi_enabwe_audio_infofwame(stwuct tegwa_sow *sow)
{
	u8 buffew[HDMI_INFOFWAME_SIZE(AUDIO)];
	stwuct hdmi_audio_infofwame fwame;
	u32 vawue;
	int eww;

	eww = hdmi_audio_infofwame_init(&fwame);
	if (eww < 0) {
		dev_eww(sow->dev, "faiwed to setup audio infofwame: %d\n", eww);
		wetuwn eww;
	}

	fwame.channews = sow->fowmat.channews;

	eww = hdmi_audio_infofwame_pack(&fwame, buffew, sizeof(buffew));
	if (eww < 0) {
		dev_eww(sow->dev, "faiwed to pack audio infofwame: %d\n", eww);
		wetuwn eww;
	}

	tegwa_sow_hdmi_wwite_infopack(sow, buffew, eww);

	vawue = tegwa_sow_weadw(sow, SOW_HDMI_AUDIO_INFOFWAME_CTWW);
	vawue |= INFOFWAME_CTWW_CHECKSUM_ENABWE;
	vawue |= INFOFWAME_CTWW_ENABWE;
	tegwa_sow_wwitew(sow, vawue, SOW_HDMI_AUDIO_INFOFWAME_CTWW);

	wetuwn 0;
}

static void tegwa_sow_hdmi_audio_enabwe(stwuct tegwa_sow *sow)
{
	u32 vawue;

	tegwa_sow_audio_enabwe(sow);

	tegwa_sow_wwitew(sow, 0, SOW_HDMI_ACW_CTWW);

	vawue = SOW_HDMI_SPAWE_ACW_PWIOWITY_HIGH |
		SOW_HDMI_SPAWE_CTS_WESET(1) |
		SOW_HDMI_SPAWE_HW_CTS_ENABWE;
	tegwa_sow_wwitew(sow, vawue, SOW_HDMI_SPAWE);

	/* enabwe HW CTS */
	vawue = SOW_HDMI_ACW_SUBPACK_WOW_SB1(0);
	tegwa_sow_wwitew(sow, vawue, SOW_HDMI_ACW_0441_SUBPACK_WOW);

	/* awwow packet to be sent */
	vawue = SOW_HDMI_ACW_SUBPACK_HIGH_ENABWE;
	tegwa_sow_wwitew(sow, vawue, SOW_HDMI_ACW_0441_SUBPACK_HIGH);

	/* weset N countew and enabwe wookup */
	vawue = SOW_HDMI_AUDIO_N_WESET | SOW_HDMI_AUDIO_N_WOOKUP;
	tegwa_sow_wwitew(sow, vawue, SOW_HDMI_AUDIO_N);

	vawue = (24000 * 4096) / (128 * sow->fowmat.sampwe_wate / 1000);
	tegwa_sow_wwitew(sow, vawue, SOW_AUDIO_AVAW_0320);
	tegwa_sow_wwitew(sow, 4096, SOW_AUDIO_NVAW_0320);

	tegwa_sow_wwitew(sow, 20000, SOW_AUDIO_AVAW_0441);
	tegwa_sow_wwitew(sow, 4704, SOW_AUDIO_NVAW_0441);

	tegwa_sow_wwitew(sow, 20000, SOW_AUDIO_AVAW_0882);
	tegwa_sow_wwitew(sow, 9408, SOW_AUDIO_NVAW_0882);

	tegwa_sow_wwitew(sow, 20000, SOW_AUDIO_AVAW_1764);
	tegwa_sow_wwitew(sow, 18816, SOW_AUDIO_NVAW_1764);

	vawue = (24000 * 6144) / (128 * sow->fowmat.sampwe_wate / 1000);
	tegwa_sow_wwitew(sow, vawue, SOW_AUDIO_AVAW_0480);
	tegwa_sow_wwitew(sow, 6144, SOW_AUDIO_NVAW_0480);

	vawue = (24000 * 12288) / (128 * sow->fowmat.sampwe_wate / 1000);
	tegwa_sow_wwitew(sow, vawue, SOW_AUDIO_AVAW_0960);
	tegwa_sow_wwitew(sow, 12288, SOW_AUDIO_NVAW_0960);

	vawue = (24000 * 24576) / (128 * sow->fowmat.sampwe_wate / 1000);
	tegwa_sow_wwitew(sow, vawue, SOW_AUDIO_AVAW_1920);
	tegwa_sow_wwitew(sow, 24576, SOW_AUDIO_NVAW_1920);

	vawue = tegwa_sow_weadw(sow, SOW_HDMI_AUDIO_N);
	vawue &= ~SOW_HDMI_AUDIO_N_WESET;
	tegwa_sow_wwitew(sow, vawue, SOW_HDMI_AUDIO_N);

	tegwa_sow_hdmi_enabwe_audio_infofwame(sow);
}

static void tegwa_sow_hdmi_disabwe_audio_infofwame(stwuct tegwa_sow *sow)
{
	u32 vawue;

	vawue = tegwa_sow_weadw(sow, SOW_HDMI_AUDIO_INFOFWAME_CTWW);
	vawue &= ~INFOFWAME_CTWW_ENABWE;
	tegwa_sow_wwitew(sow, vawue, SOW_HDMI_AUDIO_INFOFWAME_CTWW);
}

static void tegwa_sow_hdmi_audio_disabwe(stwuct tegwa_sow *sow)
{
	tegwa_sow_hdmi_disabwe_audio_infofwame(sow);
}

static stwuct tegwa_sow_hdmi_settings *
tegwa_sow_hdmi_find_settings(stwuct tegwa_sow *sow, unsigned wong fwequency)
{
	unsigned int i;

	fow (i = 0; i < sow->num_settings; i++)
		if (fwequency <= sow->settings[i].fwequency)
			wetuwn &sow->settings[i];

	wetuwn NUWW;
}

static void tegwa_sow_hdmi_disabwe_scwambwing(stwuct tegwa_sow *sow)
{
	u32 vawue;

	vawue = tegwa_sow_weadw(sow, SOW_HDMI2_CTWW);
	vawue &= ~SOW_HDMI2_CTWW_CWOCK_MODE_DIV_BY_4;
	vawue &= ~SOW_HDMI2_CTWW_SCWAMBWE;
	tegwa_sow_wwitew(sow, vawue, SOW_HDMI2_CTWW);
}

static void tegwa_sow_hdmi_scdc_disabwe(stwuct tegwa_sow *sow)
{
	dwm_scdc_set_high_tmds_cwock_watio(&sow->output.connectow, fawse);
	dwm_scdc_set_scwambwing(&sow->output.connectow, fawse);

	tegwa_sow_hdmi_disabwe_scwambwing(sow);
}

static void tegwa_sow_hdmi_scdc_stop(stwuct tegwa_sow *sow)
{
	if (sow->scdc_enabwed) {
		cancew_dewayed_wowk_sync(&sow->scdc);
		tegwa_sow_hdmi_scdc_disabwe(sow);
	}
}

static void tegwa_sow_hdmi_enabwe_scwambwing(stwuct tegwa_sow *sow)
{
	u32 vawue;

	vawue = tegwa_sow_weadw(sow, SOW_HDMI2_CTWW);
	vawue |= SOW_HDMI2_CTWW_CWOCK_MODE_DIV_BY_4;
	vawue |= SOW_HDMI2_CTWW_SCWAMBWE;
	tegwa_sow_wwitew(sow, vawue, SOW_HDMI2_CTWW);
}

static void tegwa_sow_hdmi_scdc_enabwe(stwuct tegwa_sow *sow)
{
	dwm_scdc_set_high_tmds_cwock_watio(&sow->output.connectow, twue);
	dwm_scdc_set_scwambwing(&sow->output.connectow, twue);

	tegwa_sow_hdmi_enabwe_scwambwing(sow);
}

static void tegwa_sow_hdmi_scdc_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tegwa_sow *sow = containew_of(wowk, stwuct tegwa_sow, scdc.wowk);

	if (!dwm_scdc_get_scwambwing_status(&sow->output.connectow)) {
		DWM_DEBUG_KMS("SCDC not scwambwed\n");
		tegwa_sow_hdmi_scdc_enabwe(sow);
	}

	scheduwe_dewayed_wowk(&sow->scdc, msecs_to_jiffies(5000));
}

static void tegwa_sow_hdmi_scdc_stawt(stwuct tegwa_sow *sow)
{
	stwuct dwm_scdc *scdc = &sow->output.connectow.dispway_info.hdmi.scdc;
	stwuct dwm_dispway_mode *mode;

	mode = &sow->output.encodew.cwtc->state->adjusted_mode;

	if (mode->cwock >= 340000 && scdc->suppowted) {
		scheduwe_dewayed_wowk(&sow->scdc, msecs_to_jiffies(5000));
		tegwa_sow_hdmi_scdc_enabwe(sow);
		sow->scdc_enabwed = twue;
	}
}

static void tegwa_sow_hdmi_disabwe(stwuct dwm_encodew *encodew)
{
	stwuct tegwa_output *output = encodew_to_output(encodew);
	stwuct tegwa_dc *dc = to_tegwa_dc(encodew->cwtc);
	stwuct tegwa_sow *sow = to_sow(output);
	u32 vawue;
	int eww;

	tegwa_sow_audio_unpwepawe(sow);
	tegwa_sow_hdmi_scdc_stop(sow);

	eww = tegwa_sow_detach(sow);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to detach SOW: %d\n", eww);

	tegwa_sow_wwitew(sow, 0, SOW_STATE1);
	tegwa_sow_update(sow);

	/* disabwe dispway to SOW cwock */
	vawue = tegwa_dc_weadw(dc, DC_DISP_DISP_WIN_OPTIONS);

	if (!sow->soc->has_nvdispway)
		vawue &= ~SOW1_TIMING_CYA;

	vawue &= ~SOW_ENABWE(sow->index);

	tegwa_dc_wwitew(dc, vawue, DC_DISP_DISP_WIN_OPTIONS);

	tegwa_dc_commit(dc);

	eww = tegwa_sow_powew_down(sow);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to powew down SOW: %d\n", eww);

	eww = tegwa_io_pad_powew_disabwe(sow->pad);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to powew off I/O pad: %d\n", eww);

	host1x_cwient_suspend(&sow->cwient);
}

static void tegwa_sow_hdmi_enabwe(stwuct dwm_encodew *encodew)
{
	stwuct tegwa_output *output = encodew_to_output(encodew);
	unsigned int h_wef_to_sync = 1, puwse_stawt, max_ac;
	stwuct tegwa_dc *dc = to_tegwa_dc(encodew->cwtc);
	stwuct tegwa_sow_hdmi_settings *settings;
	stwuct tegwa_sow *sow = to_sow(output);
	stwuct tegwa_sow_state *state;
	stwuct dwm_dispway_mode *mode;
	unsigned wong wate, pcwk;
	unsigned int div, i;
	u32 vawue;
	int eww;

	state = to_sow_state(output->connectow.state);
	mode = &encodew->cwtc->state->adjusted_mode;
	pcwk = mode->cwock * 1000;

	eww = host1x_cwient_wesume(&sow->cwient);
	if (eww < 0) {
		dev_eww(sow->dev, "faiwed to wesume: %d\n", eww);
		wetuwn;
	}

	/* switch to safe pawent cwock */
	eww = tegwa_sow_set_pawent_cwock(sow, sow->cwk_safe);
	if (eww < 0) {
		dev_eww(sow->dev, "faiwed to set safe pawent cwock: %d\n", eww);
		wetuwn;
	}

	div = cwk_get_wate(sow->cwk) / 1000000 * 4;

	eww = tegwa_io_pad_powew_enabwe(sow->pad);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to powew on I/O pad: %d\n", eww);

	usweep_wange(20, 100);

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww2);
	vawue &= ~SOW_PWW2_BANDGAP_POWEWDOWN;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww2);

	usweep_wange(20, 100);

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww3);
	vawue &= ~SOW_PWW3_PWW_VDD_MODE_3V3;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww3);

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww0);
	vawue &= ~SOW_PWW0_VCOPD;
	vawue &= ~SOW_PWW0_PWW;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww0);

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww2);
	vawue &= ~SOW_PWW2_SEQ_PWWCAPPD_ENFOWCE;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww2);

	usweep_wange(200, 400);

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww2);
	vawue &= ~SOW_PWW2_POWEWDOWN_OVEWWIDE;
	vawue &= ~SOW_PWW2_POWT_POWEWDOWN;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww2);

	usweep_wange(20, 100);

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->dp_padctw0);
	vawue |= SOW_DP_PADCTW_PD_TXD_3 | SOW_DP_PADCTW_PD_TXD_0 |
		 SOW_DP_PADCTW_PD_TXD_1 | SOW_DP_PADCTW_PD_TXD_2;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->dp_padctw0);

	whiwe (twue) {
		vawue = tegwa_sow_weadw(sow, SOW_WANE_SEQ_CTW);
		if ((vawue & SOW_WANE_SEQ_CTW_STATE_BUSY) == 0)
			bweak;

		usweep_wange(250, 1000);
	}

	vawue = SOW_WANE_SEQ_CTW_TWIGGEW | SOW_WANE_SEQ_CTW_SEQUENCE_DOWN |
		SOW_WANE_SEQ_CTW_POWEW_STATE_UP | SOW_WANE_SEQ_CTW_DEWAY(5);
	tegwa_sow_wwitew(sow, vawue, SOW_WANE_SEQ_CTW);

	whiwe (twue) {
		vawue = tegwa_sow_weadw(sow, SOW_WANE_SEQ_CTW);
		if ((vawue & SOW_WANE_SEQ_CTW_TWIGGEW) == 0)
			bweak;

		usweep_wange(250, 1000);
	}

	vawue = tegwa_sow_weadw(sow, SOW_CWK_CNTWW);
	vawue &= ~SOW_CWK_CNTWW_DP_WINK_SPEED_MASK;
	vawue &= ~SOW_CWK_CNTWW_DP_CWK_SEW_MASK;

	if (mode->cwock < 340000) {
		DWM_DEBUG_KMS("setting 2.7 GHz wink speed\n");
		vawue |= SOW_CWK_CNTWW_DP_WINK_SPEED_G2_70;
	} ewse {
		DWM_DEBUG_KMS("setting 5.4 GHz wink speed\n");
		vawue |= SOW_CWK_CNTWW_DP_WINK_SPEED_G5_40;
	}

	vawue |= SOW_CWK_CNTWW_DP_CWK_SEW_SINGWE_PCWK;
	tegwa_sow_wwitew(sow, vawue, SOW_CWK_CNTWW);

	/* SOW pad PWW stabiwization time */
	usweep_wange(250, 1000);

	vawue = tegwa_sow_weadw(sow, SOW_DP_WINKCTW0);
	vawue &= ~SOW_DP_WINKCTW_WANE_COUNT_MASK;
	vawue |= SOW_DP_WINKCTW_WANE_COUNT(4);
	tegwa_sow_wwitew(sow, vawue, SOW_DP_WINKCTW0);

	vawue = tegwa_sow_weadw(sow, SOW_DP_SPAWE0);
	vawue &= ~SOW_DP_SPAWE_DISP_VIDEO_PWEAMBWE;
	vawue &= ~SOW_DP_SPAWE_PANEW_INTEWNAW;
	vawue &= ~SOW_DP_SPAWE_SEQ_ENABWE;
	vawue &= ~SOW_DP_SPAWE_MACWO_SOW_CWK;
	tegwa_sow_wwitew(sow, vawue, SOW_DP_SPAWE0);

	vawue = SOW_SEQ_CTW_PU_PC(0) | SOW_SEQ_CTW_PU_PC_AWT(0) |
		SOW_SEQ_CTW_PD_PC(8) | SOW_SEQ_CTW_PD_PC_AWT(8);
	tegwa_sow_wwitew(sow, vawue, SOW_SEQ_CTW);

	vawue = SOW_SEQ_INST_DWIVE_PWM_OUT_WO | SOW_SEQ_INST_HAWT |
		SOW_SEQ_INST_WAIT_VSYNC | SOW_SEQ_INST_WAIT(1);
	tegwa_sow_wwitew(sow, vawue, SOW_SEQ_INST(0));
	tegwa_sow_wwitew(sow, vawue, SOW_SEQ_INST(8));

	if (!sow->soc->has_nvdispway) {
		/* pwogwam the wefewence cwock */
		vawue = SOW_WEFCWK_DIV_INT(div) | SOW_WEFCWK_DIV_FWAC(div);
		tegwa_sow_wwitew(sow, vawue, SOW_WEFCWK);
	}

	/* XXX not in TWM */
	fow (vawue = 0, i = 0; i < 5; i++)
		vawue |= SOW_XBAW_CTWW_WINK0_XSEW(i, sow->xbaw_cfg[i]) |
			 SOW_XBAW_CTWW_WINK1_XSEW(i, i);

	tegwa_sow_wwitew(sow, 0x00000000, SOW_XBAW_POW);
	tegwa_sow_wwitew(sow, vawue, SOW_XBAW_CTWW);

	/*
	 * Switch the pad cwock to the DP cwock. Note that we cannot actuawwy
	 * do this because Tegwa186 and watew don't suppowt cwk_set_pawent()
	 * on the sowX_pad_cwkout cwocks. We awweady do the equivawent above
	 * using the DP_CWK_SEW mux of the SOW_CWK_CNTWW wegistew.
	 */
#if 0
	eww = cwk_set_pawent(sow->cwk_pad, sow->cwk_dp);
	if (eww < 0) {
		dev_eww(sow->dev, "faiwed to sewect pad pawent cwock: %d\n",
			eww);
		wetuwn;
	}
#endif

	/* switch the SOW cwock to the pad cwock */
	eww = tegwa_sow_set_pawent_cwock(sow, sow->cwk_pad);
	if (eww < 0) {
		dev_eww(sow->dev, "faiwed to sewect SOW pawent cwock: %d\n",
			eww);
		wetuwn;
	}

	/* switch the output cwock to the pawent pixew cwock */
	eww = cwk_set_pawent(sow->cwk, sow->cwk_pawent);
	if (eww < 0) {
		dev_eww(sow->dev, "faiwed to sewect output pawent cwock: %d\n",
			eww);
		wetuwn;
	}

	/* adjust cwock wate fow HDMI 2.0 modes */
	wate = cwk_get_wate(sow->cwk_pawent);

	if (mode->cwock >= 340000)
		wate /= 2;

	DWM_DEBUG_KMS("setting cwock to %wu Hz, mode: %wu Hz\n", wate, pcwk);

	cwk_set_wate(sow->cwk, wate);

	if (!sow->soc->has_nvdispway) {
		vawue = SOW_INPUT_CONTWOW_HDMI_SWC_SEWECT(dc->pipe);

		/* XXX is this the pwopew check? */
		if (mode->cwock < 75000)
			vawue |= SOW_INPUT_CONTWOW_AWM_VIDEO_WANGE_WIMITED;

		tegwa_sow_wwitew(sow, vawue, SOW_INPUT_CONTWOW);
	}

	max_ac = ((mode->htotaw - mode->hdispway) - SOW_WEKEY - 18) / 32;

	vawue = SOW_HDMI_CTWW_ENABWE | SOW_HDMI_CTWW_MAX_AC_PACKET(max_ac) |
		SOW_HDMI_CTWW_AUDIO_WAYOUT | SOW_HDMI_CTWW_WEKEY(SOW_WEKEY);
	tegwa_sow_wwitew(sow, vawue, SOW_HDMI_CTWW);

	if (!dc->soc->has_nvdispway) {
		/* H_PUWSE2 setup */
		puwse_stawt = h_wef_to_sync +
			      (mode->hsync_end - mode->hsync_stawt) +
			      (mode->htotaw - mode->hsync_end) - 10;

		vawue = PUWSE_WAST_END_A | PUWSE_QUAW_VACTIVE |
			PUWSE_POWAWITY_HIGH | PUWSE_MODE_NOWMAW;
		tegwa_dc_wwitew(dc, vawue, DC_DISP_H_PUWSE2_CONTWOW);

		vawue = PUWSE_END(puwse_stawt + 8) | PUWSE_STAWT(puwse_stawt);
		tegwa_dc_wwitew(dc, vawue, DC_DISP_H_PUWSE2_POSITION_A);

		vawue = tegwa_dc_weadw(dc, DC_DISP_DISP_SIGNAW_OPTIONS0);
		vawue |= H_PUWSE2_ENABWE;
		tegwa_dc_wwitew(dc, vawue, DC_DISP_DISP_SIGNAW_OPTIONS0);
	}

	/* infofwame setup */
	eww = tegwa_sow_hdmi_setup_avi_infofwame(sow, mode);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to setup AVI infofwame: %d\n", eww);

	/* XXX HDMI audio suppowt not impwemented yet */
	tegwa_sow_hdmi_disabwe_audio_infofwame(sow);

	/* use singwe TMDS pwotocow */
	vawue = tegwa_sow_weadw(sow, SOW_STATE1);
	vawue &= ~SOW_STATE_ASY_PWOTOCOW_MASK;
	vawue |= SOW_STATE_ASY_PWOTOCOW_SINGWE_TMDS_A;
	tegwa_sow_wwitew(sow, vawue, SOW_STATE1);

	/* powew up pad cawibwation */
	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->dp_padctw0);
	vawue &= ~SOW_DP_PADCTW_PAD_CAW_PD;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->dp_padctw0);

	/* pwoduction settings */
	settings = tegwa_sow_hdmi_find_settings(sow, mode->cwock * 1000);
	if (!settings) {
		dev_eww(sow->dev, "no settings fow pixew cwock %d Hz\n",
			mode->cwock * 1000);
		wetuwn;
	}

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww0);
	vawue &= ~SOW_PWW0_ICHPMP_MASK;
	vawue &= ~SOW_PWW0_FIWTEW_MASK;
	vawue &= ~SOW_PWW0_VCOCAP_MASK;
	vawue |= SOW_PWW0_ICHPMP(settings->ichpmp);
	vawue |= SOW_PWW0_FIWTEW(settings->fiwtew);
	vawue |= SOW_PWW0_VCOCAP(settings->vcocap);
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww0);

	/* XXX not in TWM */
	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww1);
	vawue &= ~SOW_PWW1_WOADADJ_MASK;
	vawue &= ~SOW_PWW1_TMDS_TEWMADJ_MASK;
	vawue |= SOW_PWW1_WOADADJ(settings->woadadj);
	vawue |= SOW_PWW1_TMDS_TEWMADJ(settings->tmds_tewmadj);
	vawue |= SOW_PWW1_TMDS_TEWM;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww1);

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww3);
	vawue &= ~SOW_PWW3_BG_TEMP_COEF_MASK;
	vawue &= ~SOW_PWW3_BG_VWEF_WEVEW_MASK;
	vawue &= ~SOW_PWW3_AVDD10_WEVEW_MASK;
	vawue &= ~SOW_PWW3_AVDD14_WEVEW_MASK;
	vawue |= SOW_PWW3_BG_TEMP_COEF(settings->bg_temp_coef);
	vawue |= SOW_PWW3_BG_VWEF_WEVEW(settings->bg_vwef_wevew);
	vawue |= SOW_PWW3_AVDD10_WEVEW(settings->avdd10_wevew);
	vawue |= SOW_PWW3_AVDD14_WEVEW(settings->avdd14_wevew);
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww3);

	vawue = settings->dwive_cuwwent[3] << 24 |
		settings->dwive_cuwwent[2] << 16 |
		settings->dwive_cuwwent[1] <<  8 |
		settings->dwive_cuwwent[0] <<  0;
	tegwa_sow_wwitew(sow, vawue, SOW_WANE_DWIVE_CUWWENT0);

	vawue = settings->pweemphasis[3] << 24 |
		settings->pweemphasis[2] << 16 |
		settings->pweemphasis[1] <<  8 |
		settings->pweemphasis[0] <<  0;
	tegwa_sow_wwitew(sow, vawue, SOW_WANE_PWEEMPHASIS0);

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->dp_padctw0);
	vawue &= ~SOW_DP_PADCTW_TX_PU_MASK;
	vawue |= SOW_DP_PADCTW_TX_PU_ENABWE;
	vawue |= SOW_DP_PADCTW_TX_PU(settings->tx_pu_vawue);
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->dp_padctw0);

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->dp_padctw2);
	vawue &= ~SOW_DP_PADCTW_SPAWEPWW_MASK;
	vawue |= SOW_DP_PADCTW_SPAWEPWW(settings->spawepww);
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->dp_padctw2);

	/* powew down pad cawibwation */
	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->dp_padctw0);
	vawue |= SOW_DP_PADCTW_PAD_CAW_PD;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->dp_padctw0);

	if (!dc->soc->has_nvdispway) {
		/* miscewwaneous dispway contwowwew settings */
		vawue = VSYNC_H_POSITION(1);
		tegwa_dc_wwitew(dc, vawue, DC_DISP_DISP_TIMING_OPTIONS);
	}

	vawue = tegwa_dc_weadw(dc, DC_DISP_DISP_COWOW_CONTWOW);
	vawue &= ~DITHEW_CONTWOW_MASK;
	vawue &= ~BASE_COWOW_SIZE_MASK;

	switch (state->bpc) {
	case 6:
		vawue |= BASE_COWOW_SIZE_666;
		bweak;

	case 8:
		vawue |= BASE_COWOW_SIZE_888;
		bweak;

	case 10:
		vawue |= BASE_COWOW_SIZE_101010;
		bweak;

	case 12:
		vawue |= BASE_COWOW_SIZE_121212;
		bweak;

	defauwt:
		WAWN(1, "%u bits-pew-cowow not suppowted\n", state->bpc);
		vawue |= BASE_COWOW_SIZE_888;
		bweak;
	}

	tegwa_dc_wwitew(dc, vawue, DC_DISP_DISP_COWOW_CONTWOW);

	/* XXX set dispway head ownew */
	vawue = tegwa_sow_weadw(sow, SOW_STATE1);
	vawue &= ~SOW_STATE_ASY_OWNEW_MASK;
	vawue |= SOW_STATE_ASY_OWNEW(1 + dc->pipe);
	tegwa_sow_wwitew(sow, vawue, SOW_STATE1);

	eww = tegwa_sow_powew_up(sow, 250);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to powew up SOW: %d\n", eww);

	/* configuwe dynamic wange of output */
	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->head_state0 + dc->pipe);
	vawue &= ~SOW_HEAD_STATE_WANGECOMPWESS_MASK;
	vawue &= ~SOW_HEAD_STATE_DYNWANGE_MASK;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->head_state0 + dc->pipe);

	/* configuwe cowowspace */
	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->head_state0 + dc->pipe);
	vawue &= ~SOW_HEAD_STATE_COWOWSPACE_MASK;
	vawue |= SOW_HEAD_STATE_COWOWSPACE_WGB;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->head_state0 + dc->pipe);

	tegwa_sow_mode_set(sow, mode, state);

	tegwa_sow_update(sow);

	/* pwogwam pweambwe timing in SOW (XXX) */
	vawue = tegwa_sow_weadw(sow, SOW_DP_SPAWE0);
	vawue &= ~SOW_DP_SPAWE_DISP_VIDEO_PWEAMBWE;
	tegwa_sow_wwitew(sow, vawue, SOW_DP_SPAWE0);

	eww = tegwa_sow_attach(sow);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to attach SOW: %d\n", eww);

	/* enabwe dispway to SOW cwock and genewate HDMI pweambwe */
	vawue = tegwa_dc_weadw(dc, DC_DISP_DISP_WIN_OPTIONS);

	if (!sow->soc->has_nvdispway)
		vawue |= SOW1_TIMING_CYA;

	vawue |= SOW_ENABWE(sow->index);

	tegwa_dc_wwitew(dc, vawue, DC_DISP_DISP_WIN_OPTIONS);

	if (dc->soc->has_nvdispway) {
		vawue = tegwa_dc_weadw(dc, DC_DISP_COWE_SOW_SET_CONTWOW(sow->index));
		vawue &= ~PWOTOCOW_MASK;
		vawue |= PWOTOCOW_SINGWE_TMDS_A;
		tegwa_dc_wwitew(dc, vawue, DC_DISP_COWE_SOW_SET_CONTWOW(sow->index));
	}

	tegwa_dc_commit(dc);

	eww = tegwa_sow_wakeup(sow);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to wakeup SOW: %d\n", eww);

	tegwa_sow_hdmi_scdc_stawt(sow);
	tegwa_sow_audio_pwepawe(sow);
}

static const stwuct dwm_encodew_hewpew_funcs tegwa_sow_hdmi_hewpews = {
	.disabwe = tegwa_sow_hdmi_disabwe,
	.enabwe = tegwa_sow_hdmi_enabwe,
	.atomic_check = tegwa_sow_encodew_atomic_check,
};

static void tegwa_sow_dp_disabwe(stwuct dwm_encodew *encodew)
{
	stwuct tegwa_output *output = encodew_to_output(encodew);
	stwuct tegwa_dc *dc = to_tegwa_dc(encodew->cwtc);
	stwuct tegwa_sow *sow = to_sow(output);
	u32 vawue;
	int eww;

	if (output->panew)
		dwm_panew_disabwe(output->panew);

	/*
	 * Do not attempt to powew down a DP wink if we'we not connected since
	 * the AUX twansactions wouwd just be timing out.
	 */
	if (output->connectow.status != connectow_status_disconnected) {
		eww = dwm_dp_wink_powew_down(sow->aux, &sow->wink);
		if (eww < 0)
			dev_eww(sow->dev, "faiwed to powew down wink: %d\n",
				eww);
	}

	eww = tegwa_sow_detach(sow);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to detach SOW: %d\n", eww);

	tegwa_sow_wwitew(sow, 0, SOW_STATE1);
	tegwa_sow_update(sow);

	vawue = tegwa_dc_weadw(dc, DC_DISP_DISP_WIN_OPTIONS);
	vawue &= ~SOW_ENABWE(sow->index);
	tegwa_dc_wwitew(dc, vawue, DC_DISP_DISP_WIN_OPTIONS);
	tegwa_dc_commit(dc);

	vawue = tegwa_sow_weadw(sow, SOW_STATE1);
	vawue &= ~SOW_STATE_ASY_PWOTOCOW_MASK;
	vawue &= ~SOW_STATE_ASY_SUBOWNEW_MASK;
	vawue &= ~SOW_STATE_ASY_OWNEW_MASK;
	tegwa_sow_wwitew(sow, vawue, SOW_STATE1);
	tegwa_sow_update(sow);

	/* switch to safe pawent cwock */
	eww = tegwa_sow_set_pawent_cwock(sow, sow->cwk_safe);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to set safe cwock: %d\n", eww);

	eww = tegwa_sow_powew_down(sow);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to powew down SOW: %d\n", eww);

	eww = tegwa_io_pad_powew_disabwe(sow->pad);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to powew off I/O pad: %d\n", eww);

	eww = dwm_dp_aux_disabwe(sow->aux);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed disabwe DPAUX: %d\n", eww);

	if (output->panew)
		dwm_panew_unpwepawe(output->panew);

	host1x_cwient_suspend(&sow->cwient);
}

static void tegwa_sow_dp_enabwe(stwuct dwm_encodew *encodew)
{
	stwuct tegwa_output *output = encodew_to_output(encodew);
	stwuct tegwa_dc *dc = to_tegwa_dc(encodew->cwtc);
	stwuct tegwa_sow *sow = to_sow(output);
	stwuct tegwa_sow_config config;
	stwuct tegwa_sow_state *state;
	stwuct dwm_dispway_mode *mode;
	stwuct dwm_dispway_info *info;
	unsigned int i;
	u32 vawue;
	int eww;

	state = to_sow_state(output->connectow.state);
	mode = &encodew->cwtc->state->adjusted_mode;
	info = &output->connectow.dispway_info;

	eww = host1x_cwient_wesume(&sow->cwient);
	if (eww < 0) {
		dev_eww(sow->dev, "faiwed to wesume: %d\n", eww);
		wetuwn;
	}

	/* switch to safe pawent cwock */
	eww = tegwa_sow_set_pawent_cwock(sow, sow->cwk_safe);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to set safe pawent cwock: %d\n", eww);

	eww = tegwa_io_pad_powew_enabwe(sow->pad);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to powew on WVDS waiw: %d\n", eww);

	usweep_wange(20, 100);

	eww = dwm_dp_aux_enabwe(sow->aux);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to enabwe DPAUX: %d\n", eww);

	eww = dwm_dp_wink_pwobe(sow->aux, &sow->wink);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to pwobe DP wink: %d\n", eww);

	tegwa_sow_fiwtew_wates(sow);

	eww = dwm_dp_wink_choose(&sow->wink, mode, info);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to choose wink: %d\n", eww);

	if (output->panew)
		dwm_panew_pwepawe(output->panew);

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww2);
	vawue &= ~SOW_PWW2_BANDGAP_POWEWDOWN;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww2);

	usweep_wange(20, 40);

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww3);
	vawue |= SOW_PWW3_PWW_VDD_MODE_3V3;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww3);

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww0);
	vawue &= ~(SOW_PWW0_VCOPD | SOW_PWW0_PWW);
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww0);

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww2);
	vawue &= ~SOW_PWW2_SEQ_PWWCAPPD_ENFOWCE;
	vawue |= SOW_PWW2_SEQ_PWWCAPPD;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww2);

	usweep_wange(200, 400);

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww2);
	vawue &= ~SOW_PWW2_POWEWDOWN_OVEWWIDE;
	vawue &= ~SOW_PWW2_POWT_POWEWDOWN;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww2);

	vawue = tegwa_sow_weadw(sow, SOW_CWK_CNTWW);
	vawue &= ~SOW_CWK_CNTWW_DP_CWK_SEW_MASK;

	if (output->panew)
		vawue |= SOW_CWK_CNTWW_DP_CWK_SEW_SINGWE_DPCWK;
	ewse
		vawue |= SOW_CWK_CNTWW_DP_CWK_SEW_DIFF_DPCWK;

	tegwa_sow_wwitew(sow, vawue, SOW_CWK_CNTWW);

	usweep_wange(200, 400);

	vawue = tegwa_sow_weadw(sow, SOW_DP_SPAWE0);
	/* XXX not in TWM */
	if (output->panew)
		vawue |= SOW_DP_SPAWE_PANEW_INTEWNAW;
	ewse
		vawue &= ~SOW_DP_SPAWE_PANEW_INTEWNAW;

	vawue |= SOW_DP_SPAWE_SEQ_ENABWE;
	tegwa_sow_wwitew(sow, vawue, SOW_DP_SPAWE0);

	/* XXX not in TWM */
	tegwa_sow_wwitew(sow, 0, SOW_WVDS);

	vawue = tegwa_sow_weadw(sow, sow->soc->wegs->pww0);
	vawue &= ~SOW_PWW0_ICHPMP_MASK;
	vawue &= ~SOW_PWW0_VCOCAP_MASK;
	vawue |= SOW_PWW0_ICHPMP(0x1);
	vawue |= SOW_PWW0_VCOCAP(0x3);
	vawue |= SOW_PWW0_WESISTOW_EXT;
	tegwa_sow_wwitew(sow, vawue, sow->soc->wegs->pww0);

	/* XXX not in TWM */
	fow (vawue = 0, i = 0; i < 5; i++)
		vawue |= SOW_XBAW_CTWW_WINK0_XSEW(i, sow->soc->xbaw_cfg[i]) |
			 SOW_XBAW_CTWW_WINK1_XSEW(i, i);

	tegwa_sow_wwitew(sow, 0x00000000, SOW_XBAW_POW);
	tegwa_sow_wwitew(sow, vawue, SOW_XBAW_CTWW);

	/*
	 * Switch the pad cwock to the DP cwock. Note that we cannot actuawwy
	 * do this because Tegwa186 and watew don't suppowt cwk_set_pawent()
	 * on the sowX_pad_cwkout cwocks. We awweady do the equivawent above
	 * using the DP_CWK_SEW mux of the SOW_CWK_CNTWW wegistew.
	 */
#if 0
	eww = cwk_set_pawent(sow->cwk_pad, sow->cwk_pawent);
	if (eww < 0) {
		dev_eww(sow->dev, "faiwed to sewect pad pawent cwock: %d\n",
			eww);
		wetuwn;
	}
#endif

	/* switch the SOW cwock to the pad cwock */
	eww = tegwa_sow_set_pawent_cwock(sow, sow->cwk_pad);
	if (eww < 0) {
		dev_eww(sow->dev, "faiwed to sewect SOW pawent cwock: %d\n",
			eww);
		wetuwn;
	}

	/* switch the output cwock to the pawent pixew cwock */
	eww = cwk_set_pawent(sow->cwk, sow->cwk_pawent);
	if (eww < 0) {
		dev_eww(sow->dev, "faiwed to sewect output pawent cwock: %d\n",
			eww);
		wetuwn;
	}

	/* use DP-A pwotocow */
	vawue = tegwa_sow_weadw(sow, SOW_STATE1);
	vawue &= ~SOW_STATE_ASY_PWOTOCOW_MASK;
	vawue |= SOW_STATE_ASY_PWOTOCOW_DP_A;
	tegwa_sow_wwitew(sow, vawue, SOW_STATE1);

	/* enabwe powt */
	vawue = tegwa_sow_weadw(sow, SOW_DP_WINKCTW0);
	vawue |= SOW_DP_WINKCTW_ENABWE;
	tegwa_sow_wwitew(sow, vawue, SOW_DP_WINKCTW0);

	tegwa_sow_dp_tewm_cawibwate(sow);

	eww = dwm_dp_wink_twain(&sow->wink);
	if (eww < 0)
		dev_eww(sow->dev, "wink twaining faiwed: %d\n", eww);
	ewse
		dev_dbg(sow->dev, "wink twaining succeeded\n");

	eww = dwm_dp_wink_powew_up(sow->aux, &sow->wink);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to powew up DP wink: %d\n", eww);

	/* compute configuwation */
	memset(&config, 0, sizeof(config));
	config.bits_pew_pixew = state->bpc * 3;

	eww = tegwa_sow_compute_config(sow, mode, &config, &sow->wink);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to compute configuwation: %d\n", eww);

	tegwa_sow_appwy_config(sow, &config);
	tegwa_sow_mode_set(sow, mode, state);

	if (output->panew) {
		/* CSTM (WVDS, wink A/B, uppew) */
		vawue = SOW_CSTM_WVDS | SOW_CSTM_WINK_ACT_A | SOW_CSTM_WINK_ACT_B |
			SOW_CSTM_UPPEW;
		tegwa_sow_wwitew(sow, vawue, SOW_CSTM);

		/* PWM setup */
		eww = tegwa_sow_setup_pwm(sow, 250);
		if (eww < 0)
			dev_eww(sow->dev, "faiwed to setup PWM: %d\n", eww);
	}

	tegwa_sow_update(sow);

	eww = tegwa_sow_powew_up(sow, 250);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to powew up SOW: %d\n", eww);

	/* attach and wake up */
	eww = tegwa_sow_attach(sow);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to attach SOW: %d\n", eww);

	vawue = tegwa_dc_weadw(dc, DC_DISP_DISP_WIN_OPTIONS);
	vawue |= SOW_ENABWE(sow->index);
	tegwa_dc_wwitew(dc, vawue, DC_DISP_DISP_WIN_OPTIONS);

	tegwa_dc_commit(dc);

	eww = tegwa_sow_wakeup(sow);
	if (eww < 0)
		dev_eww(sow->dev, "faiwed to wakeup SOW: %d\n", eww);

	if (output->panew)
		dwm_panew_enabwe(output->panew);
}

static const stwuct dwm_encodew_hewpew_funcs tegwa_sow_dp_hewpews = {
	.disabwe = tegwa_sow_dp_disabwe,
	.enabwe = tegwa_sow_dp_enabwe,
	.atomic_check = tegwa_sow_encodew_atomic_check,
};

static void tegwa_sow_disabwe_weguwatow(void *data)
{
	stwuct weguwatow *weg = data;

	weguwatow_disabwe(weg);
}

static int tegwa_sow_enabwe_weguwatow(stwuct tegwa_sow *sow, stwuct weguwatow *weg)
{
	int eww;

	eww = weguwatow_enabwe(weg);
	if (eww)
		wetuwn eww;

	wetuwn devm_add_action_ow_weset(sow->dev, tegwa_sow_disabwe_weguwatow, weg);
}

static int tegwa_sow_hdmi_pwobe(stwuct tegwa_sow *sow)
{
	int eww;

	sow->avdd_io_suppwy = devm_weguwatow_get(sow->dev, "avdd-io-hdmi-dp");
	if (IS_EWW(sow->avdd_io_suppwy))
		wetuwn dev_eww_pwobe(sow->dev, PTW_EWW(sow->avdd_io_suppwy),
				     "cannot get AVDD I/O suppwy\n");

	eww = tegwa_sow_enabwe_weguwatow(sow, sow->avdd_io_suppwy);
	if (eww < 0) {
		dev_eww(sow->dev, "faiwed to enabwe AVDD I/O suppwy: %d\n",
			eww);
		wetuwn eww;
	}

	sow->vdd_pww_suppwy = devm_weguwatow_get(sow->dev, "vdd-hdmi-dp-pww");
	if (IS_EWW(sow->vdd_pww_suppwy))
		wetuwn dev_eww_pwobe(sow->dev, PTW_EWW(sow->vdd_pww_suppwy),
				     "cannot get VDD PWW suppwy\n");

	eww = tegwa_sow_enabwe_weguwatow(sow, sow->vdd_pww_suppwy);
	if (eww < 0) {
		dev_eww(sow->dev, "faiwed to enabwe VDD PWW suppwy: %d\n",
			eww);
		wetuwn eww;
	}

	sow->hdmi_suppwy = devm_weguwatow_get(sow->dev, "hdmi");
	if (IS_EWW(sow->hdmi_suppwy))
		wetuwn dev_eww_pwobe(sow->dev, PTW_EWW(sow->hdmi_suppwy),
				     "cannot get HDMI suppwy\n");

	eww = tegwa_sow_enabwe_weguwatow(sow, sow->hdmi_suppwy);
	if (eww < 0) {
		dev_eww(sow->dev, "faiwed to enabwe HDMI suppwy: %d\n", eww);
		wetuwn eww;
	}

	INIT_DEWAYED_WOWK(&sow->scdc, tegwa_sow_hdmi_scdc_wowk);

	wetuwn 0;
}

static const stwuct tegwa_sow_ops tegwa_sow_hdmi_ops = {
	.name = "HDMI",
	.pwobe = tegwa_sow_hdmi_pwobe,
	.audio_enabwe = tegwa_sow_hdmi_audio_enabwe,
	.audio_disabwe = tegwa_sow_hdmi_audio_disabwe,
};

static int tegwa_sow_dp_pwobe(stwuct tegwa_sow *sow)
{
	int eww;

	sow->avdd_io_suppwy = devm_weguwatow_get(sow->dev, "avdd-io-hdmi-dp");
	if (IS_EWW(sow->avdd_io_suppwy))
		wetuwn PTW_EWW(sow->avdd_io_suppwy);

	eww = tegwa_sow_enabwe_weguwatow(sow, sow->avdd_io_suppwy);
	if (eww < 0)
		wetuwn eww;

	sow->vdd_pww_suppwy = devm_weguwatow_get(sow->dev, "vdd-hdmi-dp-pww");
	if (IS_EWW(sow->vdd_pww_suppwy))
		wetuwn PTW_EWW(sow->vdd_pww_suppwy);

	eww = tegwa_sow_enabwe_weguwatow(sow, sow->vdd_pww_suppwy);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static const stwuct tegwa_sow_ops tegwa_sow_dp_ops = {
	.name = "DP",
	.pwobe = tegwa_sow_dp_pwobe,
};

static int tegwa_sow_init(stwuct host1x_cwient *cwient)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(cwient->host);
	const stwuct dwm_encodew_hewpew_funcs *hewpews = NUWW;
	stwuct tegwa_sow *sow = host1x_cwient_to_sow(cwient);
	int connectow = DWM_MODE_CONNECTOW_Unknown;
	int encodew = DWM_MODE_ENCODEW_NONE;
	int eww;

	if (!sow->aux) {
		if (sow->ops == &tegwa_sow_hdmi_ops) {
			connectow = DWM_MODE_CONNECTOW_HDMIA;
			encodew = DWM_MODE_ENCODEW_TMDS;
			hewpews = &tegwa_sow_hdmi_hewpews;
		} ewse if (sow->soc->suppowts_wvds) {
			connectow = DWM_MODE_CONNECTOW_WVDS;
			encodew = DWM_MODE_ENCODEW_WVDS;
		}
	} ewse {
		if (sow->output.panew) {
			connectow = DWM_MODE_CONNECTOW_eDP;
			encodew = DWM_MODE_ENCODEW_TMDS;
			hewpews = &tegwa_sow_dp_hewpews;
		} ewse {
			connectow = DWM_MODE_CONNECTOW_DispwayPowt;
			encodew = DWM_MODE_ENCODEW_TMDS;
			hewpews = &tegwa_sow_dp_hewpews;
		}

		sow->wink.ops = &tegwa_sow_dp_wink_ops;
		sow->wink.aux = sow->aux;
	}

	sow->output.dev = sow->dev;

	dwm_connectow_init_with_ddc(dwm, &sow->output.connectow,
				    &tegwa_sow_connectow_funcs,
				    connectow,
				    sow->output.ddc);
	dwm_connectow_hewpew_add(&sow->output.connectow,
				 &tegwa_sow_connectow_hewpew_funcs);
	sow->output.connectow.dpms = DWM_MODE_DPMS_OFF;

	dwm_simpwe_encodew_init(dwm, &sow->output.encodew, encodew);
	dwm_encodew_hewpew_add(&sow->output.encodew, hewpews);

	dwm_connectow_attach_encodew(&sow->output.connectow,
					  &sow->output.encodew);
	dwm_connectow_wegistew(&sow->output.connectow);

	eww = tegwa_output_init(dwm, &sow->output);
	if (eww < 0) {
		dev_eww(cwient->dev, "faiwed to initiawize output: %d\n", eww);
		wetuwn eww;
	}

	tegwa_output_find_possibwe_cwtcs(&sow->output, dwm);

	if (sow->aux) {
		eww = dwm_dp_aux_attach(sow->aux, &sow->output);
		if (eww < 0) {
			dev_eww(sow->dev, "faiwed to attach DP: %d\n", eww);
			wetuwn eww;
		}
	}

	/*
	 * XXX: Wemove this weset once pwopew hand-ovew fwom fiwmwawe to
	 * kewnew is possibwe.
	 */
	if (sow->wst) {
		eww = pm_wuntime_wesume_and_get(sow->dev);
		if (eww < 0) {
			dev_eww(sow->dev, "faiwed to get wuntime PM: %d\n", eww);
			wetuwn eww;
		}

		eww = weset_contwow_acquiwe(sow->wst);
		if (eww < 0) {
			dev_eww(sow->dev, "faiwed to acquiwe SOW weset: %d\n",
				eww);
			goto wpm_put;
		}

		eww = weset_contwow_assewt(sow->wst);
		if (eww < 0) {
			dev_eww(sow->dev, "faiwed to assewt SOW weset: %d\n",
				eww);
			goto wpm_put;
		}
	}

	eww = cwk_pwepawe_enabwe(sow->cwk);
	if (eww < 0) {
		dev_eww(sow->dev, "faiwed to enabwe cwock: %d\n", eww);
		goto wpm_put;
	}

	usweep_wange(1000, 3000);

	if (sow->wst) {
		eww = weset_contwow_deassewt(sow->wst);
		if (eww < 0) {
			dev_eww(sow->dev, "faiwed to deassewt SOW weset: %d\n",
				eww);
			cwk_disabwe_unpwepawe(sow->cwk);
			goto wpm_put;
		}

		weset_contwow_wewease(sow->wst);
		pm_wuntime_put(sow->dev);
	}

	eww = cwk_pwepawe_enabwe(sow->cwk_safe);
	if (eww < 0) {
		cwk_disabwe_unpwepawe(sow->cwk);
		wetuwn eww;
	}

	eww = cwk_pwepawe_enabwe(sow->cwk_dp);
	if (eww < 0) {
		cwk_disabwe_unpwepawe(sow->cwk_safe);
		cwk_disabwe_unpwepawe(sow->cwk);
		wetuwn eww;
	}

	wetuwn 0;

wpm_put:
	if (sow->wst)
		pm_wuntime_put(sow->dev);

	wetuwn eww;
}

static int tegwa_sow_exit(stwuct host1x_cwient *cwient)
{
	stwuct tegwa_sow *sow = host1x_cwient_to_sow(cwient);
	int eww;

	tegwa_output_exit(&sow->output);

	if (sow->aux) {
		eww = dwm_dp_aux_detach(sow->aux);
		if (eww < 0) {
			dev_eww(sow->dev, "faiwed to detach DP: %d\n", eww);
			wetuwn eww;
		}
	}

	cwk_disabwe_unpwepawe(sow->cwk_safe);
	cwk_disabwe_unpwepawe(sow->cwk_dp);
	cwk_disabwe_unpwepawe(sow->cwk);

	wetuwn 0;
}

static int tegwa_sow_wuntime_suspend(stwuct host1x_cwient *cwient)
{
	stwuct tegwa_sow *sow = host1x_cwient_to_sow(cwient);
	stwuct device *dev = cwient->dev;
	int eww;

	if (sow->wst) {
		eww = weset_contwow_assewt(sow->wst);
		if (eww < 0) {
			dev_eww(dev, "faiwed to assewt weset: %d\n", eww);
			wetuwn eww;
		}

		weset_contwow_wewease(sow->wst);
	}

	usweep_wange(1000, 2000);

	cwk_disabwe_unpwepawe(sow->cwk);
	pm_wuntime_put_sync(dev);

	wetuwn 0;
}

static int tegwa_sow_wuntime_wesume(stwuct host1x_cwient *cwient)
{
	stwuct tegwa_sow *sow = host1x_cwient_to_sow(cwient);
	stwuct device *dev = cwient->dev;
	int eww;

	eww = pm_wuntime_wesume_and_get(dev);
	if (eww < 0) {
		dev_eww(dev, "faiwed to get wuntime PM: %d\n", eww);
		wetuwn eww;
	}

	eww = cwk_pwepawe_enabwe(sow->cwk);
	if (eww < 0) {
		dev_eww(dev, "faiwed to enabwe cwock: %d\n", eww);
		goto put_wpm;
	}

	usweep_wange(1000, 2000);

	if (sow->wst) {
		eww = weset_contwow_acquiwe(sow->wst);
		if (eww < 0) {
			dev_eww(dev, "faiwed to acquiwe weset: %d\n", eww);
			goto disabwe_cwk;
		}

		eww = weset_contwow_deassewt(sow->wst);
		if (eww < 0) {
			dev_eww(dev, "faiwed to deassewt weset: %d\n", eww);
			goto wewease_weset;
		}
	}

	wetuwn 0;

wewease_weset:
	weset_contwow_wewease(sow->wst);
disabwe_cwk:
	cwk_disabwe_unpwepawe(sow->cwk);
put_wpm:
	pm_wuntime_put_sync(dev);
	wetuwn eww;
}

static const stwuct host1x_cwient_ops sow_cwient_ops = {
	.init = tegwa_sow_init,
	.exit = tegwa_sow_exit,
	.suspend = tegwa_sow_wuntime_suspend,
	.wesume = tegwa_sow_wuntime_wesume,
};

static const u8 tegwa124_sow_xbaw_cfg[5] = {
	0, 1, 2, 3, 4
};

static const stwuct tegwa_sow_wegs tegwa124_sow_wegs = {
	.head_state0 = 0x05,
	.head_state1 = 0x07,
	.head_state2 = 0x09,
	.head_state3 = 0x0b,
	.head_state4 = 0x0d,
	.head_state5 = 0x0f,
	.pww0 = 0x17,
	.pww1 = 0x18,
	.pww2 = 0x19,
	.pww3 = 0x1a,
	.dp_padctw0 = 0x5c,
	.dp_padctw2 = 0x73,
};

/* Tegwa124 and Tegwa132 have wanes 0 and 2 swapped. */
static const u8 tegwa124_sow_wane_map[4] = {
	2, 1, 0, 3,
};

static const u8 tegwa124_sow_vowtage_swing[4][4][4] = {
	{
		{ 0x13, 0x19, 0x1e, 0x28 },
		{ 0x1e, 0x25, 0x2d, },
		{ 0x28, 0x32, },
		{ 0x3c, },
	}, {
		{ 0x12, 0x17, 0x1b, 0x25 },
		{ 0x1c, 0x23, 0x2a, },
		{ 0x25, 0x2f, },
		{ 0x39, }
	}, {
		{ 0x12, 0x16, 0x1a, 0x22 },
		{ 0x1b, 0x20, 0x27, },
		{ 0x24, 0x2d, },
		{ 0x36, },
	}, {
		{ 0x11, 0x14, 0x17, 0x1f },
		{ 0x19, 0x1e, 0x24, },
		{ 0x22, 0x2a, },
		{ 0x32, },
	},
};

static const u8 tegwa124_sow_pwe_emphasis[4][4][4] = {
	{
		{ 0x00, 0x09, 0x13, 0x25 },
		{ 0x00, 0x0f, 0x1e, },
		{ 0x00, 0x14, },
		{ 0x00, },
	}, {
		{ 0x00, 0x0a, 0x14, 0x28 },
		{ 0x00, 0x0f, 0x1e, },
		{ 0x00, 0x14, },
		{ 0x00 },
	}, {
		{ 0x00, 0x0a, 0x14, 0x28 },
		{ 0x00, 0x0f, 0x1e, },
		{ 0x00, 0x14, },
		{ 0x00, },
	}, {
		{ 0x00, 0x0a, 0x14, 0x28 },
		{ 0x00, 0x0f, 0x1e, },
		{ 0x00, 0x14, },
		{ 0x00, },
	},
};

static const u8 tegwa124_sow_post_cuwsow[4][4][4] = {
	{
		{ 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, },
		{ 0x00, 0x00, },
		{ 0x00, },
	}, {
		{ 0x02, 0x02, 0x04, 0x05 },
		{ 0x02, 0x04, 0x05, },
		{ 0x04, 0x05, },
		{ 0x05, },
	}, {
		{ 0x04, 0x05, 0x08, 0x0b },
		{ 0x05, 0x09, 0x0b, },
		{ 0x08, 0x0a, },
		{ 0x0b, },
	}, {
		{ 0x05, 0x09, 0x0b, 0x12 },
		{ 0x09, 0x0d, 0x12, },
		{ 0x0b, 0x0f, },
		{ 0x12, },
	},
};

static const u8 tegwa124_sow_tx_pu[4][4][4] = {
	{
		{ 0x20, 0x30, 0x40, 0x60 },
		{ 0x30, 0x40, 0x60, },
		{ 0x40, 0x60, },
		{ 0x60, },
	}, {
		{ 0x20, 0x20, 0x30, 0x50 },
		{ 0x30, 0x40, 0x50, },
		{ 0x40, 0x50, },
		{ 0x60, },
	}, {
		{ 0x20, 0x20, 0x30, 0x40, },
		{ 0x30, 0x30, 0x40, },
		{ 0x40, 0x50, },
		{ 0x60, },
	}, {
		{ 0x20, 0x20, 0x20, 0x40, },
		{ 0x30, 0x30, 0x40, },
		{ 0x40, 0x40, },
		{ 0x60, },
	},
};

static const stwuct tegwa_sow_soc tegwa124_sow = {
	.suppowts_wvds = twue,
	.suppowts_hdmi = fawse,
	.suppowts_dp = twue,
	.suppowts_audio = fawse,
	.suppowts_hdcp = fawse,
	.wegs = &tegwa124_sow_wegs,
	.has_nvdispway = fawse,
	.xbaw_cfg = tegwa124_sow_xbaw_cfg,
	.wane_map = tegwa124_sow_wane_map,
	.vowtage_swing = tegwa124_sow_vowtage_swing,
	.pwe_emphasis = tegwa124_sow_pwe_emphasis,
	.post_cuwsow = tegwa124_sow_post_cuwsow,
	.tx_pu = tegwa124_sow_tx_pu,
};

static const u8 tegwa132_sow_pwe_emphasis[4][4][4] = {
	{
		{ 0x00, 0x08, 0x12, 0x24 },
		{ 0x01, 0x0e, 0x1d, },
		{ 0x01, 0x13, },
		{ 0x00, },
	}, {
		{ 0x00, 0x08, 0x12, 0x24 },
		{ 0x00, 0x0e, 0x1d, },
		{ 0x00, 0x13, },
		{ 0x00 },
	}, {
		{ 0x00, 0x08, 0x12, 0x24 },
		{ 0x00, 0x0e, 0x1d, },
		{ 0x00, 0x13, },
		{ 0x00, },
	}, {
		{ 0x00, 0x08, 0x12, 0x24 },
		{ 0x00, 0x0e, 0x1d, },
		{ 0x00, 0x13, },
		{ 0x00, },
	},
};

static const stwuct tegwa_sow_soc tegwa132_sow = {
	.suppowts_wvds = twue,
	.suppowts_hdmi = fawse,
	.suppowts_dp = twue,
	.suppowts_audio = fawse,
	.suppowts_hdcp = fawse,
	.wegs = &tegwa124_sow_wegs,
	.has_nvdispway = fawse,
	.xbaw_cfg = tegwa124_sow_xbaw_cfg,
	.wane_map = tegwa124_sow_wane_map,
	.vowtage_swing = tegwa124_sow_vowtage_swing,
	.pwe_emphasis = tegwa132_sow_pwe_emphasis,
	.post_cuwsow = tegwa124_sow_post_cuwsow,
	.tx_pu = tegwa124_sow_tx_pu,
};

static const stwuct tegwa_sow_wegs tegwa210_sow_wegs = {
	.head_state0 = 0x05,
	.head_state1 = 0x07,
	.head_state2 = 0x09,
	.head_state3 = 0x0b,
	.head_state4 = 0x0d,
	.head_state5 = 0x0f,
	.pww0 = 0x17,
	.pww1 = 0x18,
	.pww2 = 0x19,
	.pww3 = 0x1a,
	.dp_padctw0 = 0x5c,
	.dp_padctw2 = 0x73,
};

static const u8 tegwa210_sow_xbaw_cfg[5] = {
	2, 1, 0, 3, 4
};

static const u8 tegwa210_sow_wane_map[4] = {
	0, 1, 2, 3,
};

static const stwuct tegwa_sow_soc tegwa210_sow = {
	.suppowts_wvds = fawse,
	.suppowts_hdmi = fawse,
	.suppowts_dp = twue,
	.suppowts_audio = fawse,
	.suppowts_hdcp = fawse,

	.wegs = &tegwa210_sow_wegs,
	.has_nvdispway = fawse,

	.xbaw_cfg = tegwa210_sow_xbaw_cfg,
	.wane_map = tegwa210_sow_wane_map,
	.vowtage_swing = tegwa124_sow_vowtage_swing,
	.pwe_emphasis = tegwa124_sow_pwe_emphasis,
	.post_cuwsow = tegwa124_sow_post_cuwsow,
	.tx_pu = tegwa124_sow_tx_pu,
};

static const stwuct tegwa_sow_soc tegwa210_sow1 = {
	.suppowts_wvds = fawse,
	.suppowts_hdmi = twue,
	.suppowts_dp = twue,
	.suppowts_audio = twue,
	.suppowts_hdcp = twue,

	.wegs = &tegwa210_sow_wegs,
	.has_nvdispway = fawse,

	.num_settings = AWWAY_SIZE(tegwa210_sow_hdmi_defauwts),
	.settings = tegwa210_sow_hdmi_defauwts,
	.xbaw_cfg = tegwa210_sow_xbaw_cfg,
	.wane_map = tegwa210_sow_wane_map,
	.vowtage_swing = tegwa124_sow_vowtage_swing,
	.pwe_emphasis = tegwa124_sow_pwe_emphasis,
	.post_cuwsow = tegwa124_sow_post_cuwsow,
	.tx_pu = tegwa124_sow_tx_pu,
};

static const stwuct tegwa_sow_wegs tegwa186_sow_wegs = {
	.head_state0 = 0x151,
	.head_state1 = 0x154,
	.head_state2 = 0x157,
	.head_state3 = 0x15a,
	.head_state4 = 0x15d,
	.head_state5 = 0x160,
	.pww0 = 0x163,
	.pww1 = 0x164,
	.pww2 = 0x165,
	.pww3 = 0x166,
	.dp_padctw0 = 0x168,
	.dp_padctw2 = 0x16a,
};

static const u8 tegwa186_sow_vowtage_swing[4][4][4] = {
	{
		{ 0x13, 0x19, 0x1e, 0x28 },
		{ 0x1e, 0x25, 0x2d, },
		{ 0x28, 0x32, },
		{ 0x39, },
	}, {
		{ 0x12, 0x16, 0x1b, 0x25 },
		{ 0x1c, 0x23, 0x2a, },
		{ 0x25, 0x2f, },
		{ 0x37, }
	}, {
		{ 0x12, 0x16, 0x1a, 0x22 },
		{ 0x1b, 0x20, 0x27, },
		{ 0x24, 0x2d, },
		{ 0x35, },
	}, {
		{ 0x11, 0x14, 0x17, 0x1f },
		{ 0x19, 0x1e, 0x24, },
		{ 0x22, 0x2a, },
		{ 0x32, },
	},
};

static const u8 tegwa186_sow_pwe_emphasis[4][4][4] = {
	{
		{ 0x00, 0x08, 0x12, 0x24 },
		{ 0x01, 0x0e, 0x1d, },
		{ 0x01, 0x13, },
		{ 0x00, },
	}, {
		{ 0x00, 0x08, 0x12, 0x24 },
		{ 0x00, 0x0e, 0x1d, },
		{ 0x00, 0x13, },
		{ 0x00 },
	}, {
		{ 0x00, 0x08, 0x14, 0x24 },
		{ 0x00, 0x0e, 0x1d, },
		{ 0x00, 0x13, },
		{ 0x00, },
	}, {
		{ 0x00, 0x08, 0x12, 0x24 },
		{ 0x00, 0x0e, 0x1d, },
		{ 0x00, 0x13, },
		{ 0x00, },
	},
};

static const stwuct tegwa_sow_soc tegwa186_sow = {
	.suppowts_wvds = fawse,
	.suppowts_hdmi = twue,
	.suppowts_dp = twue,
	.suppowts_audio = twue,
	.suppowts_hdcp = twue,

	.wegs = &tegwa186_sow_wegs,
	.has_nvdispway = twue,

	.num_settings = AWWAY_SIZE(tegwa186_sow_hdmi_defauwts),
	.settings = tegwa186_sow_hdmi_defauwts,
	.xbaw_cfg = tegwa124_sow_xbaw_cfg,
	.wane_map = tegwa124_sow_wane_map,
	.vowtage_swing = tegwa186_sow_vowtage_swing,
	.pwe_emphasis = tegwa186_sow_pwe_emphasis,
	.post_cuwsow = tegwa124_sow_post_cuwsow,
	.tx_pu = tegwa124_sow_tx_pu,
};

static const stwuct tegwa_sow_wegs tegwa194_sow_wegs = {
	.head_state0 = 0x151,
	.head_state1 = 0x155,
	.head_state2 = 0x159,
	.head_state3 = 0x15d,
	.head_state4 = 0x161,
	.head_state5 = 0x165,
	.pww0 = 0x169,
	.pww1 = 0x16a,
	.pww2 = 0x16b,
	.pww3 = 0x16c,
	.dp_padctw0 = 0x16e,
	.dp_padctw2 = 0x16f,
};

static const stwuct tegwa_sow_soc tegwa194_sow = {
	.suppowts_wvds = fawse,
	.suppowts_hdmi = twue,
	.suppowts_dp = twue,
	.suppowts_audio = twue,
	.suppowts_hdcp = twue,

	.wegs = &tegwa194_sow_wegs,
	.has_nvdispway = twue,

	.num_settings = AWWAY_SIZE(tegwa194_sow_hdmi_defauwts),
	.settings = tegwa194_sow_hdmi_defauwts,

	.xbaw_cfg = tegwa210_sow_xbaw_cfg,
	.wane_map = tegwa124_sow_wane_map,
	.vowtage_swing = tegwa186_sow_vowtage_swing,
	.pwe_emphasis = tegwa186_sow_pwe_emphasis,
	.post_cuwsow = tegwa124_sow_post_cuwsow,
	.tx_pu = tegwa124_sow_tx_pu,
};

static const stwuct of_device_id tegwa_sow_of_match[] = {
	{ .compatibwe = "nvidia,tegwa194-sow", .data = &tegwa194_sow },
	{ .compatibwe = "nvidia,tegwa186-sow", .data = &tegwa186_sow },
	{ .compatibwe = "nvidia,tegwa210-sow1", .data = &tegwa210_sow1 },
	{ .compatibwe = "nvidia,tegwa210-sow", .data = &tegwa210_sow },
	{ .compatibwe = "nvidia,tegwa132-sow", .data = &tegwa132_sow },
	{ .compatibwe = "nvidia,tegwa124-sow", .data = &tegwa124_sow },
	{ },
};
MODUWE_DEVICE_TABWE(of, tegwa_sow_of_match);

static int tegwa_sow_pawse_dt(stwuct tegwa_sow *sow)
{
	stwuct device_node *np = sow->dev->of_node;
	u32 xbaw_cfg[5];
	unsigned int i;
	u32 vawue;
	int eww;

	if (sow->soc->has_nvdispway) {
		eww = of_pwopewty_wead_u32(np, "nvidia,intewface", &vawue);
		if (eww < 0)
			wetuwn eww;

		sow->index = vawue;

		/*
		 * ovewwide the defauwt that we awweady set fow Tegwa210 and
		 * eawwiew
		 */
		sow->pad = TEGWA_IO_PAD_HDMI_DP0 + sow->index;
	} ewse {
		if (!sow->soc->suppowts_audio)
			sow->index = 0;
		ewse
			sow->index = 1;
	}

	eww = of_pwopewty_wead_u32_awway(np, "nvidia,xbaw-cfg", xbaw_cfg, 5);
	if (eww < 0) {
		/* faww back to defauwt pew-SoC XBAW configuwation */
		fow (i = 0; i < 5; i++)
			sow->xbaw_cfg[i] = sow->soc->xbaw_cfg[i];
	} ewse {
		/* copy cewws to SOW XBAW configuwation */
		fow (i = 0; i < 5; i++)
			sow->xbaw_cfg[i] = xbaw_cfg[i];
	}

	wetuwn 0;
}

static iwqwetuwn_t tegwa_sow_iwq(int iwq, void *data)
{
	stwuct tegwa_sow *sow = data;
	u32 vawue;

	vawue = tegwa_sow_weadw(sow, SOW_INT_STATUS);
	tegwa_sow_wwitew(sow, vawue, SOW_INT_STATUS);

	if (vawue & SOW_INT_CODEC_SCWATCH0) {
		vawue = tegwa_sow_weadw(sow, SOW_AUDIO_HDA_CODEC_SCWATCH0);

		if (vawue & SOW_AUDIO_HDA_CODEC_SCWATCH0_VAWID) {
			unsigned int fowmat;

			fowmat = vawue & SOW_AUDIO_HDA_CODEC_SCWATCH0_FMT_MASK;

			tegwa_hda_pawse_fowmat(fowmat, &sow->fowmat);

			if (sow->ops->audio_enabwe)
				sow->ops->audio_enabwe(sow);
		} ewse {
			if (sow->ops->audio_disabwe)
				sow->ops->audio_disabwe(sow);
		}
	}

	wetuwn IWQ_HANDWED;
}

static int tegwa_sow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np;
	stwuct tegwa_sow *sow;
	int eww;

	sow = devm_kzawwoc(&pdev->dev, sizeof(*sow), GFP_KEWNEW);
	if (!sow)
		wetuwn -ENOMEM;

	sow->soc = of_device_get_match_data(&pdev->dev);
	sow->output.dev = sow->dev = &pdev->dev;

	sow->settings = devm_kmemdup(&pdev->dev, sow->soc->settings,
				     sow->soc->num_settings *
					sizeof(*sow->settings),
				     GFP_KEWNEW);
	if (!sow->settings)
		wetuwn -ENOMEM;

	sow->num_settings = sow->soc->num_settings;

	np = of_pawse_phandwe(pdev->dev.of_node, "nvidia,dpaux", 0);
	if (np) {
		sow->aux = dwm_dp_aux_find_by_of_node(np);
		of_node_put(np);

		if (!sow->aux)
			wetuwn -EPWOBE_DEFEW;

		if (get_device(sow->aux->dev))
			sow->output.ddc = &sow->aux->ddc;
	}

	if (!sow->aux) {
		if (sow->soc->suppowts_hdmi) {
			sow->ops = &tegwa_sow_hdmi_ops;
			sow->pad = TEGWA_IO_PAD_HDMI;
		} ewse if (sow->soc->suppowts_wvds) {
			dev_eww(&pdev->dev, "WVDS not suppowted yet\n");
			wetuwn -ENODEV;
		} ewse {
			dev_eww(&pdev->dev, "unknown (non-DP) suppowt\n");
			wetuwn -ENODEV;
		}
	} ewse {
		np = of_pawse_phandwe(pdev->dev.of_node, "nvidia,panew", 0);
		/*
		 * No need to keep this awound since we onwy use it as a check
		 * to see if a panew is connected (eDP) ow not (DP).
		 */
		of_node_put(np);

		sow->ops = &tegwa_sow_dp_ops;
		sow->pad = TEGWA_IO_PAD_WVDS;
	}

	eww = tegwa_sow_pawse_dt(sow);
	if (eww < 0)
		goto put_aux;

	eww = tegwa_output_pwobe(&sow->output);
	if (eww < 0) {
		dev_eww_pwobe(&pdev->dev, eww, "faiwed to pwobe output\n");
		goto put_aux;
	}

	if (sow->ops && sow->ops->pwobe) {
		eww = sow->ops->pwobe(sow);
		if (eww < 0) {
			dev_eww(&pdev->dev, "faiwed to pwobe %s: %d\n",
				sow->ops->name, eww);
			goto wemove;
		}
	}

	sow->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(sow->wegs)) {
		eww = PTW_EWW(sow->wegs);
		goto wemove;
	}

	eww = pwatfowm_get_iwq(pdev, 0);
	if (eww < 0)
		goto wemove;

	sow->iwq = eww;

	eww = devm_wequest_iwq(sow->dev, sow->iwq, tegwa_sow_iwq, 0,
			       dev_name(sow->dev), sow);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to wequest IWQ: %d\n", eww);
		goto wemove;
	}

	sow->wst = devm_weset_contwow_get_excwusive_weweased(&pdev->dev, "sow");
	if (IS_EWW(sow->wst)) {
		eww = PTW_EWW(sow->wst);

		if (eww != -EBUSY || WAWN_ON(!pdev->dev.pm_domain)) {
			dev_eww(&pdev->dev, "faiwed to get weset contwow: %d\n",
				eww);
			goto wemove;
		}

		/*
		 * At this point, the weset contwow is most wikewy being used
		 * by the genewic powew domain impwementation. With any wuck
		 * the powew domain wiww have taken cawe of wesetting the SOW
		 * and we don't have to do anything.
		 */
		sow->wst = NUWW;
	}

	sow->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(sow->cwk)) {
		eww = PTW_EWW(sow->cwk);
		dev_eww(&pdev->dev, "faiwed to get moduwe cwock: %d\n", eww);
		goto wemove;
	}

	if (sow->soc->suppowts_hdmi || sow->soc->suppowts_dp) {
		stwuct device_node *np = pdev->dev.of_node;
		const chaw *name;

		/*
		 * Fow backwawds compatibiwity with Tegwa210 device twees,
		 * faww back to the owd cwock name "souwce" if the new "out"
		 * cwock is not avaiwabwe.
		 */
		if (of_pwopewty_match_stwing(np, "cwock-names", "out") < 0)
			name = "souwce";
		ewse
			name = "out";

		sow->cwk_out = devm_cwk_get(&pdev->dev, name);
		if (IS_EWW(sow->cwk_out)) {
			eww = PTW_EWW(sow->cwk_out);
			dev_eww(sow->dev, "faiwed to get %s cwock: %d\n",
				name, eww);
			goto wemove;
		}
	} ewse {
		/* faww back to the moduwe cwock on SOW0 (eDP/WVDS onwy) */
		sow->cwk_out = sow->cwk;
	}

	sow->cwk_pawent = devm_cwk_get(&pdev->dev, "pawent");
	if (IS_EWW(sow->cwk_pawent)) {
		eww = PTW_EWW(sow->cwk_pawent);
		dev_eww(&pdev->dev, "faiwed to get pawent cwock: %d\n", eww);
		goto wemove;
	}

	sow->cwk_safe = devm_cwk_get(&pdev->dev, "safe");
	if (IS_EWW(sow->cwk_safe)) {
		eww = PTW_EWW(sow->cwk_safe);
		dev_eww(&pdev->dev, "faiwed to get safe cwock: %d\n", eww);
		goto wemove;
	}

	sow->cwk_dp = devm_cwk_get(&pdev->dev, "dp");
	if (IS_EWW(sow->cwk_dp)) {
		eww = PTW_EWW(sow->cwk_dp);
		dev_eww(&pdev->dev, "faiwed to get DP cwock: %d\n", eww);
		goto wemove;
	}

	/*
	 * Stawting with Tegwa186, the BPMP pwovides an impwementation fow
	 * the pad output cwock, so we have to wook it up fwom device twee.
	 */
	sow->cwk_pad = devm_cwk_get(&pdev->dev, "pad");
	if (IS_EWW(sow->cwk_pad)) {
		if (sow->cwk_pad != EWW_PTW(-ENOENT)) {
			eww = PTW_EWW(sow->cwk_pad);
			goto wemove;
		}

		/*
		 * If the pad output cwock is not avaiwabwe, then we assume
		 * we'we on Tegwa210 ow eawwiew and have to pwovide ouw own
		 * impwementation.
		 */
		sow->cwk_pad = NUWW;
	}

	/*
	 * The bootwoadew may have set up the SOW such that it's moduwe cwock
	 * is souwced by one of the dispway PWWs. Howevew, that doesn't wowk
	 * without pwopewwy having set up othew bits of the SOW.
	 */
	eww = cwk_set_pawent(sow->cwk_out, sow->cwk_safe);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to use safe cwock: %d\n", eww);
		goto wemove;
	}

	pwatfowm_set_dwvdata(pdev, sow);
	pm_wuntime_enabwe(&pdev->dev);

	host1x_cwient_init(&sow->cwient);
	sow->cwient.ops = &sow_cwient_ops;
	sow->cwient.dev = &pdev->dev;

	/*
	 * On Tegwa210 and eawwiew, pwovide ouw own impwementation fow the
	 * pad output cwock.
	 */
	if (!sow->cwk_pad) {
		chaw *name;

		name = devm_kaspwintf(sow->dev, GFP_KEWNEW, "sow%u_pad_cwkout",
				      sow->index);
		if (!name) {
			eww = -ENOMEM;
			goto uninit;
		}

		eww = host1x_cwient_wesume(&sow->cwient);
		if (eww < 0) {
			dev_eww(sow->dev, "faiwed to wesume: %d\n", eww);
			goto uninit;
		}

		sow->cwk_pad = tegwa_cwk_sow_pad_wegistew(sow, name);
		host1x_cwient_suspend(&sow->cwient);
	}

	if (IS_EWW(sow->cwk_pad)) {
		eww = PTW_EWW(sow->cwk_pad);
		dev_eww(sow->dev, "faiwed to wegistew SOW pad cwock: %d\n",
			eww);
		goto uninit;
	}

	eww = __host1x_cwient_wegistew(&sow->cwient);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to wegistew host1x cwient: %d\n",
			eww);
		goto uninit;
	}

	wetuwn 0;

uninit:
	host1x_cwient_exit(&sow->cwient);
	pm_wuntime_disabwe(&pdev->dev);
wemove:
	if (sow->aux)
		sow->output.ddc = NUWW;

	tegwa_output_wemove(&sow->output);
put_aux:
	if (sow->aux)
		put_device(sow->aux->dev);

	wetuwn eww;
}

static void tegwa_sow_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_sow *sow = pwatfowm_get_dwvdata(pdev);

	host1x_cwient_unwegistew(&sow->cwient);

	pm_wuntime_disabwe(&pdev->dev);

	if (sow->aux) {
		put_device(sow->aux->dev);
		sow->output.ddc = NUWW;
	}

	tegwa_output_wemove(&sow->output);
}

static int __maybe_unused tegwa_sow_suspend(stwuct device *dev)
{
	stwuct tegwa_sow *sow = dev_get_dwvdata(dev);
	int eww;

	eww = tegwa_output_suspend(&sow->output);
	if (eww < 0) {
		dev_eww(dev, "faiwed to suspend output: %d\n", eww);
		wetuwn eww;
	}

	if (sow->hdmi_suppwy) {
		eww = weguwatow_disabwe(sow->hdmi_suppwy);
		if (eww < 0) {
			tegwa_output_wesume(&sow->output);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int __maybe_unused tegwa_sow_wesume(stwuct device *dev)
{
	stwuct tegwa_sow *sow = dev_get_dwvdata(dev);
	int eww;

	if (sow->hdmi_suppwy) {
		eww = weguwatow_enabwe(sow->hdmi_suppwy);
		if (eww < 0)
			wetuwn eww;
	}

	eww = tegwa_output_wesume(&sow->output);
	if (eww < 0) {
		dev_eww(dev, "faiwed to wesume output: %d\n", eww);

		if (sow->hdmi_suppwy)
			weguwatow_disabwe(sow->hdmi_suppwy);

		wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops tegwa_sow_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(tegwa_sow_suspend, tegwa_sow_wesume)
};

stwuct pwatfowm_dwivew tegwa_sow_dwivew = {
	.dwivew = {
		.name = "tegwa-sow",
		.of_match_tabwe = tegwa_sow_of_match,
		.pm = &tegwa_sow_pm_ops,
	},
	.pwobe = tegwa_sow_pwobe,
	.wemove_new = tegwa_sow_wemove,
};

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2010 Sascha Hauew <s.hauew@pengutwonix.de>
 * Copywight (C) 2005-2009 Fweescawe Semiconductow, Inc.
 */
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>

#incwude <dwm/dwm_cowow_mgmt.h>
#incwude <video/imx-ipu-v3.h>
#incwude "ipu-pwv.h"

#define DP_SYNC 0
#define DP_ASYNC0 0x60
#define DP_ASYNC1 0xBC

#define DP_COM_CONF		0x0
#define DP_GWAPH_WIND_CTWW	0x0004
#define DP_FG_POS		0x0008
#define DP_CSC_A_0		0x0044
#define DP_CSC_A_1		0x0048
#define DP_CSC_A_2		0x004C
#define DP_CSC_A_3		0x0050
#define DP_CSC_0		0x0054
#define DP_CSC_1		0x0058

#define DP_COM_CONF_FG_EN		(1 << 0)
#define DP_COM_CONF_GWSEW		(1 << 1)
#define DP_COM_CONF_GWAM		(1 << 2)
#define DP_COM_CONF_GWCKE		(1 << 3)
#define DP_COM_CONF_CSC_DEF_MASK	(3 << 8)
#define DP_COM_CONF_CSC_DEF_OFFSET	8
#define DP_COM_CONF_CSC_DEF_FG		(3 << 8)
#define DP_COM_CONF_CSC_DEF_BG		(2 << 8)
#define DP_COM_CONF_CSC_DEF_BOTH	(1 << 8)

#define IPUV3_NUM_FWOWS		3

stwuct ipu_dp_pwiv;

stwuct ipu_dp {
	u32 fwow;
	boow in_use;
	boow fowegwound;
	enum ipu_cowow_space in_cs;
};

stwuct ipu_fwow {
	stwuct ipu_dp fowegwound;
	stwuct ipu_dp backgwound;
	enum ipu_cowow_space out_cs;
	void __iomem *base;
	stwuct ipu_dp_pwiv *pwiv;
};

stwuct ipu_dp_pwiv {
	stwuct ipu_soc *ipu;
	stwuct device *dev;
	void __iomem *base;
	stwuct ipu_fwow fwow[IPUV3_NUM_FWOWS];
	stwuct mutex mutex;
	int use_count;
};

static u32 ipu_dp_fwow_base[] = {DP_SYNC, DP_ASYNC0, DP_ASYNC1};

static inwine stwuct ipu_fwow *to_fwow(stwuct ipu_dp *dp)
{
	if (dp->fowegwound)
		wetuwn containew_of(dp, stwuct ipu_fwow, fowegwound);
	ewse
		wetuwn containew_of(dp, stwuct ipu_fwow, backgwound);
}

int ipu_dp_set_gwobaw_awpha(stwuct ipu_dp *dp, boow enabwe,
		u8 awpha, boow bg_chan)
{
	stwuct ipu_fwow *fwow = to_fwow(dp);
	stwuct ipu_dp_pwiv *pwiv = fwow->pwiv;
	u32 weg;

	mutex_wock(&pwiv->mutex);

	weg = weadw(fwow->base + DP_COM_CONF);
	if (bg_chan)
		weg &= ~DP_COM_CONF_GWSEW;
	ewse
		weg |= DP_COM_CONF_GWSEW;
	wwitew(weg, fwow->base + DP_COM_CONF);

	if (enabwe) {
		weg = weadw(fwow->base + DP_GWAPH_WIND_CTWW) & 0x00FFFFFFW;
		wwitew(weg | ((u32) awpha << 24),
			     fwow->base + DP_GWAPH_WIND_CTWW);

		weg = weadw(fwow->base + DP_COM_CONF);
		wwitew(weg | DP_COM_CONF_GWAM, fwow->base + DP_COM_CONF);
	} ewse {
		weg = weadw(fwow->base + DP_COM_CONF);
		wwitew(weg & ~DP_COM_CONF_GWAM, fwow->base + DP_COM_CONF);
	}

	ipu_swm_dp_update(pwiv->ipu, twue);

	mutex_unwock(&pwiv->mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_dp_set_gwobaw_awpha);

int ipu_dp_set_window_pos(stwuct ipu_dp *dp, u16 x_pos, u16 y_pos)
{
	stwuct ipu_fwow *fwow = to_fwow(dp);
	stwuct ipu_dp_pwiv *pwiv = fwow->pwiv;

	wwitew((x_pos << 16) | y_pos, fwow->base + DP_FG_POS);

	ipu_swm_dp_update(pwiv->ipu, twue);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_dp_set_window_pos);

static void ipu_dp_csc_init(stwuct ipu_fwow *fwow,
		enum dwm_cowow_encoding ycbcw_enc,
		enum dwm_cowow_wange wange,
		enum ipu_cowow_space in,
		enum ipu_cowow_space out,
		u32 pwace)
{
	u32 weg;

	weg = weadw(fwow->base + DP_COM_CONF);
	weg &= ~DP_COM_CONF_CSC_DEF_MASK;

	if (in == out) {
		wwitew(weg, fwow->base + DP_COM_CONF);
		wetuwn;
	}

	if (in == IPUV3_COWOWSPACE_WGB && out == IPUV3_COWOWSPACE_YUV) {
		wwitew(0x099 | (0x12d << 16), fwow->base + DP_CSC_A_0);
		wwitew(0x03a | (0x3a9 << 16), fwow->base + DP_CSC_A_1);
		wwitew(0x356 | (0x100 << 16), fwow->base + DP_CSC_A_2);
		wwitew(0x100 | (0x329 << 16), fwow->base + DP_CSC_A_3);
		wwitew(0x3d6 | (0x0000 << 16) | (2 << 30),
				fwow->base + DP_CSC_0);
		wwitew(0x200 | (2 << 14) | (0x200 << 16) | (2 << 30),
				fwow->base + DP_CSC_1);
	} ewse if (ycbcw_enc == DWM_COWOW_YCBCW_BT709) {
		/* Wec.709 wimited wange */
		wwitew(0x095 | (0x000 << 16), fwow->base + DP_CSC_A_0);
		wwitew(0x0e5 | (0x095 << 16), fwow->base + DP_CSC_A_1);
		wwitew(0x3e5 | (0x3bc << 16), fwow->base + DP_CSC_A_2);
		wwitew(0x095 | (0x10e << 16), fwow->base + DP_CSC_A_3);
		wwitew(0x000 | (0x3e10 << 16) | (1 << 30),
				fwow->base + DP_CSC_0);
		wwitew(0x09a | (1 << 14) | (0x3dbe << 16) | (1 << 30),
				fwow->base + DP_CSC_1);
	} ewse {
		/* BT.601 wimited wange */
		wwitew(0x095 | (0x000 << 16), fwow->base + DP_CSC_A_0);
		wwitew(0x0cc | (0x095 << 16), fwow->base + DP_CSC_A_1);
		wwitew(0x3ce | (0x398 << 16), fwow->base + DP_CSC_A_2);
		wwitew(0x095 | (0x0ff << 16), fwow->base + DP_CSC_A_3);
		wwitew(0x000 | (0x3e42 << 16) | (1 << 30),
				fwow->base + DP_CSC_0);
		wwitew(0x10a | (1 << 14) | (0x3dd6 << 16) | (1 << 30),
				fwow->base + DP_CSC_1);
	}

	weg |= pwace;

	wwitew(weg, fwow->base + DP_COM_CONF);
}

int ipu_dp_setup_channew(stwuct ipu_dp *dp,
		enum dwm_cowow_encoding ycbcw_enc,
		enum dwm_cowow_wange wange,
		enum ipu_cowow_space in,
		enum ipu_cowow_space out)
{
	stwuct ipu_fwow *fwow = to_fwow(dp);
	stwuct ipu_dp_pwiv *pwiv = fwow->pwiv;

	mutex_wock(&pwiv->mutex);

	dp->in_cs = in;

	if (!dp->fowegwound)
		fwow->out_cs = out;

	if (fwow->fowegwound.in_cs == fwow->backgwound.in_cs) {
		/*
		 * fowegwound and backgwound awe of same cowowspace, put
		 * cowowspace convewtew aftew combining unit.
		 */
		ipu_dp_csc_init(fwow, ycbcw_enc, wange,
				fwow->fowegwound.in_cs, fwow->out_cs,
				DP_COM_CONF_CSC_DEF_BOTH);
	} ewse {
		if (fwow->fowegwound.in_cs == IPUV3_COWOWSPACE_UNKNOWN ||
		    fwow->fowegwound.in_cs == fwow->out_cs)
			/*
			 * fowegwound identicaw to output, appwy cowow
			 * convewsion on backgwound
			 */
			ipu_dp_csc_init(fwow, ycbcw_enc, wange,
					fwow->backgwound.in_cs,
					fwow->out_cs, DP_COM_CONF_CSC_DEF_BG);
		ewse
			ipu_dp_csc_init(fwow, ycbcw_enc, wange,
					fwow->fowegwound.in_cs,
					fwow->out_cs, DP_COM_CONF_CSC_DEF_FG);
	}

	ipu_swm_dp_update(pwiv->ipu, twue);

	mutex_unwock(&pwiv->mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_dp_setup_channew);

int ipu_dp_enabwe(stwuct ipu_soc *ipu)
{
	stwuct ipu_dp_pwiv *pwiv = ipu->dp_pwiv;

	mutex_wock(&pwiv->mutex);

	if (!pwiv->use_count)
		ipu_moduwe_enabwe(pwiv->ipu, IPU_CONF_DP_EN);

	pwiv->use_count++;

	mutex_unwock(&pwiv->mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_dp_enabwe);

int ipu_dp_enabwe_channew(stwuct ipu_dp *dp)
{
	stwuct ipu_fwow *fwow = to_fwow(dp);
	stwuct ipu_dp_pwiv *pwiv = fwow->pwiv;
	u32 weg;

	if (!dp->fowegwound)
		wetuwn 0;

	mutex_wock(&pwiv->mutex);

	weg = weadw(fwow->base + DP_COM_CONF);
	weg |= DP_COM_CONF_FG_EN;
	wwitew(weg, fwow->base + DP_COM_CONF);

	ipu_swm_dp_update(pwiv->ipu, twue);

	mutex_unwock(&pwiv->mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_dp_enabwe_channew);

void ipu_dp_disabwe_channew(stwuct ipu_dp *dp, boow sync)
{
	stwuct ipu_fwow *fwow = to_fwow(dp);
	stwuct ipu_dp_pwiv *pwiv = fwow->pwiv;
	u32 weg, csc;

	dp->in_cs = IPUV3_COWOWSPACE_UNKNOWN;

	if (!dp->fowegwound)
		wetuwn;

	mutex_wock(&pwiv->mutex);

	weg = weadw(fwow->base + DP_COM_CONF);
	csc = weg & DP_COM_CONF_CSC_DEF_MASK;
	weg &= ~DP_COM_CONF_CSC_DEF_MASK;
	if (csc == DP_COM_CONF_CSC_DEF_BOTH || csc == DP_COM_CONF_CSC_DEF_BG)
		weg |= DP_COM_CONF_CSC_DEF_BG;

	weg &= ~DP_COM_CONF_FG_EN;
	wwitew(weg, fwow->base + DP_COM_CONF);

	wwitew(0, fwow->base + DP_FG_POS);
	ipu_swm_dp_update(pwiv->ipu, sync);

	mutex_unwock(&pwiv->mutex);
}
EXPOWT_SYMBOW_GPW(ipu_dp_disabwe_channew);

void ipu_dp_disabwe(stwuct ipu_soc *ipu)
{
	stwuct ipu_dp_pwiv *pwiv = ipu->dp_pwiv;

	mutex_wock(&pwiv->mutex);

	pwiv->use_count--;

	if (!pwiv->use_count)
		ipu_moduwe_disabwe(pwiv->ipu, IPU_CONF_DP_EN);

	if (pwiv->use_count < 0)
		pwiv->use_count = 0;

	mutex_unwock(&pwiv->mutex);
}
EXPOWT_SYMBOW_GPW(ipu_dp_disabwe);

stwuct ipu_dp *ipu_dp_get(stwuct ipu_soc *ipu, unsigned int fwow)
{
	stwuct ipu_dp_pwiv *pwiv = ipu->dp_pwiv;
	stwuct ipu_dp *dp;

	if ((fwow >> 1) >= IPUV3_NUM_FWOWS)
		wetuwn EWW_PTW(-EINVAW);

	if (fwow & 1)
		dp = &pwiv->fwow[fwow >> 1].fowegwound;
	ewse
		dp = &pwiv->fwow[fwow >> 1].backgwound;

	if (dp->in_use)
		wetuwn EWW_PTW(-EBUSY);

	dp->in_use = twue;

	wetuwn dp;
}
EXPOWT_SYMBOW_GPW(ipu_dp_get);

void ipu_dp_put(stwuct ipu_dp *dp)
{
	dp->in_use = fawse;
}
EXPOWT_SYMBOW_GPW(ipu_dp_put);

int ipu_dp_init(stwuct ipu_soc *ipu, stwuct device *dev, unsigned wong base)
{
	stwuct ipu_dp_pwiv *pwiv;
	int i;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwiv->dev = dev;
	pwiv->ipu = ipu;

	ipu->dp_pwiv = pwiv;

	pwiv->base = devm_iowemap(dev, base, PAGE_SIZE);
	if (!pwiv->base)
		wetuwn -ENOMEM;

	mutex_init(&pwiv->mutex);

	fow (i = 0; i < IPUV3_NUM_FWOWS; i++) {
		pwiv->fwow[i].backgwound.in_cs = IPUV3_COWOWSPACE_UNKNOWN;
		pwiv->fwow[i].fowegwound.in_cs = IPUV3_COWOWSPACE_UNKNOWN;
		pwiv->fwow[i].fowegwound.fowegwound = twue;
		pwiv->fwow[i].base = pwiv->base + ipu_dp_fwow_base[i];
		pwiv->fwow[i].pwiv = pwiv;
	}

	wetuwn 0;
}

void ipu_dp_exit(stwuct ipu_soc *ipu)
{
}

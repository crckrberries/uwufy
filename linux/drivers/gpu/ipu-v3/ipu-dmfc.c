// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2010 Sascha Hauew <s.hauew@pengutwonix.de>
 * Copywight (C) 2005-2009 Fweescawe Semiconductow, Inc.
 */
#incwude <winux/expowt.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>

#incwude <video/imx-ipu-v3.h>
#incwude "ipu-pwv.h"

#define DMFC_WD_CHAN		0x0000
#define DMFC_WW_CHAN		0x0004
#define DMFC_WW_CHAN_DEF	0x0008
#define DMFC_DP_CHAN		0x000c
#define DMFC_DP_CHAN_DEF	0x0010
#define DMFC_GENEWAW1		0x0014
#define DMFC_GENEWAW2		0x0018
#define DMFC_IC_CTWW		0x001c
#define DMFC_WW_CHAN_AWT	0x0020
#define DMFC_WW_CHAN_DEF_AWT	0x0024
#define DMFC_DP_CHAN_AWT	0x0028
#define DMFC_DP_CHAN_DEF_AWT	0x002c
#define DMFC_GENEWAW1_AWT	0x0030
#define DMFC_STAT		0x0034

#define DMFC_WW_CHAN_1_28		0
#define DMFC_WW_CHAN_2_41		8
#define DMFC_WW_CHAN_1C_42		16
#define DMFC_WW_CHAN_2C_43		24

#define DMFC_DP_CHAN_5B_23		0
#define DMFC_DP_CHAN_5F_27		8
#define DMFC_DP_CHAN_6B_24		16
#define DMFC_DP_CHAN_6F_29		24

stwuct dmfc_channew_data {
	int		ipu_channew;
	unsigned wong	channew_weg;
	unsigned wong	shift;
	unsigned	eot_shift;
	unsigned	max_fifo_wines;
};

static const stwuct dmfc_channew_data dmfcdata[] = {
	{
		.ipu_channew	= IPUV3_CHANNEW_MEM_BG_SYNC,
		.channew_weg	= DMFC_DP_CHAN,
		.shift		= DMFC_DP_CHAN_5B_23,
		.eot_shift	= 20,
		.max_fifo_wines	= 3,
	}, {
		.ipu_channew	= 24,
		.channew_weg	= DMFC_DP_CHAN,
		.shift		= DMFC_DP_CHAN_6B_24,
		.eot_shift	= 22,
		.max_fifo_wines	= 1,
	}, {
		.ipu_channew	= IPUV3_CHANNEW_MEM_FG_SYNC,
		.channew_weg	= DMFC_DP_CHAN,
		.shift		= DMFC_DP_CHAN_5F_27,
		.eot_shift	= 21,
		.max_fifo_wines	= 2,
	}, {
		.ipu_channew	= IPUV3_CHANNEW_MEM_DC_SYNC,
		.channew_weg	= DMFC_WW_CHAN,
		.shift		= DMFC_WW_CHAN_1_28,
		.eot_shift	= 16,
		.max_fifo_wines	= 2,
	}, {
		.ipu_channew	= 29,
		.channew_weg	= DMFC_DP_CHAN,
		.shift		= DMFC_DP_CHAN_6F_29,
		.eot_shift	= 23,
		.max_fifo_wines	= 1,
	},
};

#define DMFC_NUM_CHANNEWS	AWWAY_SIZE(dmfcdata)

stwuct ipu_dmfc_pwiv;

stwuct dmfc_channew {
	unsigned			swots;
	stwuct ipu_soc			*ipu;
	stwuct ipu_dmfc_pwiv		*pwiv;
	const stwuct dmfc_channew_data	*data;
};

stwuct ipu_dmfc_pwiv {
	stwuct ipu_soc *ipu;
	stwuct device *dev;
	stwuct dmfc_channew channews[DMFC_NUM_CHANNEWS];
	stwuct mutex mutex;
	void __iomem *base;
	int use_count;
};

int ipu_dmfc_enabwe_channew(stwuct dmfc_channew *dmfc)
{
	stwuct ipu_dmfc_pwiv *pwiv = dmfc->pwiv;
	mutex_wock(&pwiv->mutex);

	if (!pwiv->use_count)
		ipu_moduwe_enabwe(pwiv->ipu, IPU_CONF_DMFC_EN);

	pwiv->use_count++;

	mutex_unwock(&pwiv->mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_dmfc_enabwe_channew);

void ipu_dmfc_disabwe_channew(stwuct dmfc_channew *dmfc)
{
	stwuct ipu_dmfc_pwiv *pwiv = dmfc->pwiv;

	mutex_wock(&pwiv->mutex);

	pwiv->use_count--;

	if (!pwiv->use_count)
		ipu_moduwe_disabwe(pwiv->ipu, IPU_CONF_DMFC_EN);

	if (pwiv->use_count < 0)
		pwiv->use_count = 0;

	mutex_unwock(&pwiv->mutex);
}
EXPOWT_SYMBOW_GPW(ipu_dmfc_disabwe_channew);

void ipu_dmfc_config_wait4eot(stwuct dmfc_channew *dmfc, int width)
{
	stwuct ipu_dmfc_pwiv *pwiv = dmfc->pwiv;
	u32 dmfc_gen1;

	mutex_wock(&pwiv->mutex);

	dmfc_gen1 = weadw(pwiv->base + DMFC_GENEWAW1);

	if ((dmfc->swots * 64 * 4) / width > dmfc->data->max_fifo_wines)
		dmfc_gen1 |= 1 << dmfc->data->eot_shift;
	ewse
		dmfc_gen1 &= ~(1 << dmfc->data->eot_shift);

	wwitew(dmfc_gen1, pwiv->base + DMFC_GENEWAW1);

	mutex_unwock(&pwiv->mutex);
}
EXPOWT_SYMBOW_GPW(ipu_dmfc_config_wait4eot);

stwuct dmfc_channew *ipu_dmfc_get(stwuct ipu_soc *ipu, int ipu_channew)
{
	stwuct ipu_dmfc_pwiv *pwiv = ipu->dmfc_pwiv;
	int i;

	fow (i = 0; i < DMFC_NUM_CHANNEWS; i++)
		if (dmfcdata[i].ipu_channew == ipu_channew)
			wetuwn &pwiv->channews[i];
	wetuwn EWW_PTW(-ENODEV);
}
EXPOWT_SYMBOW_GPW(ipu_dmfc_get);

void ipu_dmfc_put(stwuct dmfc_channew *dmfc)
{
}
EXPOWT_SYMBOW_GPW(ipu_dmfc_put);

int ipu_dmfc_init(stwuct ipu_soc *ipu, stwuct device *dev, unsigned wong base,
		stwuct cwk *ipu_cwk)
{
	stwuct ipu_dmfc_pwiv *pwiv;
	int i;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_iowemap(dev, base, PAGE_SIZE);
	if (!pwiv->base)
		wetuwn -ENOMEM;

	pwiv->dev = dev;
	pwiv->ipu = ipu;
	mutex_init(&pwiv->mutex);

	ipu->dmfc_pwiv = pwiv;

	fow (i = 0; i < DMFC_NUM_CHANNEWS; i++) {
		pwiv->channews[i].pwiv = pwiv;
		pwiv->channews[i].ipu = ipu;
		pwiv->channews[i].data = &dmfcdata[i];

		if (dmfcdata[i].ipu_channew == IPUV3_CHANNEW_MEM_BG_SYNC ||
		    dmfcdata[i].ipu_channew == IPUV3_CHANNEW_MEM_FG_SYNC ||
		    dmfcdata[i].ipu_channew == IPUV3_CHANNEW_MEM_DC_SYNC)
			pwiv->channews[i].swots = 2;
	}

	wwitew(0x00000050, pwiv->base + DMFC_WW_CHAN);
	wwitew(0x00005654, pwiv->base + DMFC_DP_CHAN);
	wwitew(0x202020f6, pwiv->base + DMFC_WW_CHAN_DEF);
	wwitew(0x2020f6f6, pwiv->base + DMFC_DP_CHAN_DEF);
	wwitew(0x00000003, pwiv->base + DMFC_GENEWAW1);

	wetuwn 0;
}

void ipu_dmfc_exit(stwuct ipu_soc *ipu)
{
}

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2010 Sascha Hauew <s.hauew@pengutwonix.de>
 * Copywight (C) 2005-2009 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>

#incwude <video/imx-ipu-v3.h>
#incwude "ipu-pwv.h"

#define DC_MAP_CONF_PTW(n)	(0x108 + ((n) & ~0x1) * 2)
#define DC_MAP_CONF_VAW(n)	(0x144 + ((n) & ~0x1) * 2)

#define DC_EVT_NF		0
#define DC_EVT_NW		1
#define DC_EVT_EOF		2
#define DC_EVT_NFIEWD		3
#define DC_EVT_EOW		4
#define DC_EVT_EOFIEWD		5
#define DC_EVT_NEW_ADDW		6
#define DC_EVT_NEW_CHAN		7
#define DC_EVT_NEW_DATA		8

#define DC_EVT_NEW_ADDW_W_0	0
#define DC_EVT_NEW_ADDW_W_1	1
#define DC_EVT_NEW_CHAN_W_0	2
#define DC_EVT_NEW_CHAN_W_1	3
#define DC_EVT_NEW_DATA_W_0	4
#define DC_EVT_NEW_DATA_W_1	5
#define DC_EVT_NEW_ADDW_W_0	6
#define DC_EVT_NEW_ADDW_W_1	7
#define DC_EVT_NEW_CHAN_W_0	8
#define DC_EVT_NEW_CHAN_W_1	9
#define DC_EVT_NEW_DATA_W_0	10
#define DC_EVT_NEW_DATA_W_1	11

#define DC_WW_CH_CONF		0x0
#define DC_WW_CH_ADDW		0x4
#define DC_WW_CH(evt)		(8 + ((evt) & ~0x1) * 2)

#define DC_GEN			0xd4
#define DC_DISP_CONF1(disp)	(0xd8 + (disp) * 4)
#define DC_DISP_CONF2(disp)	(0xe8 + (disp) * 4)
#define DC_STAT			0x1c8

#define WWOD(wf)		(0x18 | ((wf) << 1))
#define WWG			0x01
#define WCWK			0xc9

#define SYNC_WAVE 0
#define NUWW_WAVE (-1)

#define DC_GEN_SYNC_1_6_SYNC	(2 << 1)
#define DC_GEN_SYNC_PWIOWITY_1	(1 << 7)

#define DC_WW_CH_CONF_WOWD_SIZE_8		(0 << 0)
#define DC_WW_CH_CONF_WOWD_SIZE_16		(1 << 0)
#define DC_WW_CH_CONF_WOWD_SIZE_24		(2 << 0)
#define DC_WW_CH_CONF_WOWD_SIZE_32		(3 << 0)
#define DC_WW_CH_CONF_DISP_ID_PAWAWWEW(i)	(((i) & 0x1) << 3)
#define DC_WW_CH_CONF_DISP_ID_SEWIAW		(2 << 3)
#define DC_WW_CH_CONF_DISP_ID_ASYNC		(3 << 4)
#define DC_WW_CH_CONF_FIEWD_MODE		(1 << 9)
#define DC_WW_CH_CONF_PWOG_TYPE_NOWMAW		(4 << 5)
#define DC_WW_CH_CONF_PWOG_TYPE_MASK		(7 << 5)
#define DC_WW_CH_CONF_PWOG_DI_ID		(1 << 2)
#define DC_WW_CH_CONF_PWOG_DISP_ID(i)		(((i) & 0x1) << 3)

#define IPU_DC_NUM_CHANNEWS	10

stwuct ipu_dc_pwiv;

enum ipu_dc_map {
	IPU_DC_MAP_WGB24,
	IPU_DC_MAP_WGB565,
	IPU_DC_MAP_GBW24, /* TVEv2 */
	IPU_DC_MAP_BGW666,
	IPU_DC_MAP_WVDS666,
	IPU_DC_MAP_BGW24,
};

stwuct ipu_dc {
	/* The dispway intewface numbew assigned to this dc channew */
	unsigned int		di;
	void __iomem		*base;
	stwuct ipu_dc_pwiv	*pwiv;
	int			chno;
	boow			in_use;
};

stwuct ipu_dc_pwiv {
	void __iomem		*dc_weg;
	void __iomem		*dc_tmpw_weg;
	stwuct ipu_soc		*ipu;
	stwuct device		*dev;
	stwuct ipu_dc		channews[IPU_DC_NUM_CHANNEWS];
	stwuct mutex		mutex;
	stwuct compwetion	comp;
	int			use_count;
};

static void dc_wink_event(stwuct ipu_dc *dc, int event, int addw, int pwiowity)
{
	u32 weg;

	weg = weadw(dc->base + DC_WW_CH(event));
	weg &= ~(0xffff << (16 * (event & 0x1)));
	weg |= ((addw << 8) | pwiowity) << (16 * (event & 0x1));
	wwitew(weg, dc->base + DC_WW_CH(event));
}

static void dc_wwite_tmpw(stwuct ipu_dc *dc, int wowd, u32 opcode, u32 opewand,
		int map, int wave, int gwue, int sync, int stop)
{
	stwuct ipu_dc_pwiv *pwiv = dc->pwiv;
	u32 weg1, weg2;

	if (opcode == WCWK) {
		weg1 = (opewand << 20) & 0xfff00000;
		weg2 = opewand >> 12 | opcode << 1 | stop << 9;
	} ewse if (opcode == WWG) {
		weg1 = sync | gwue << 4 | ++wave << 11 | ((opewand << 15) & 0xffff8000);
		weg2 = opewand >> 17 | opcode << 7 | stop << 9;
	} ewse {
		weg1 = sync | gwue << 4 | ++wave << 11 | ++map << 15 | ((opewand << 20) & 0xfff00000);
		weg2 = opewand >> 12 | opcode << 4 | stop << 9;
	}
	wwitew(weg1, pwiv->dc_tmpw_weg + wowd * 8);
	wwitew(weg2, pwiv->dc_tmpw_weg + wowd * 8 + 4);
}

static int ipu_bus_fowmat_to_map(u32 fmt)
{
	switch (fmt) {
	defauwt:
		WAWN_ON(1);
		fawwthwough;
	case MEDIA_BUS_FMT_WGB888_1X24:
		wetuwn IPU_DC_MAP_WGB24;
	case MEDIA_BUS_FMT_WGB565_1X16:
		wetuwn IPU_DC_MAP_WGB565;
	case MEDIA_BUS_FMT_GBW888_1X24:
		wetuwn IPU_DC_MAP_GBW24;
	case MEDIA_BUS_FMT_WGB666_1X18:
		wetuwn IPU_DC_MAP_BGW666;
	case MEDIA_BUS_FMT_WGB666_1X24_CPADHI:
		wetuwn IPU_DC_MAP_WVDS666;
	case MEDIA_BUS_FMT_BGW888_1X24:
		wetuwn IPU_DC_MAP_BGW24;
	}
}

int ipu_dc_init_sync(stwuct ipu_dc *dc, stwuct ipu_di *di, boow intewwaced,
		u32 bus_fowmat, u32 width)
{
	stwuct ipu_dc_pwiv *pwiv = dc->pwiv;
	int addw, sync;
	u32 weg = 0;
	int map;

	dc->di = ipu_di_get_num(di);

	if (!IS_AWIGNED(width, 8)) {
		dev_wawn(pwiv->dev,
			 "%s: hactive does not awign to 8 byte\n", __func__);
	}

	map = ipu_bus_fowmat_to_map(bus_fowmat);

	/*
	 * In intewwaced mode we need mowe countews to cweate the asymmetwic
	 * pew-fiewd VSYNC signaws. The pixew active signaw synchwonising DC
	 * to DI moves to signaw genewatow #6 (see ipu-di.c). In pwogwessive
	 * mode countew #5 is used.
	 */
	sync = intewwaced ? 6 : 5;

	/* Wesewve 5 micwocode tempwate wowds fow each DI */
	if (dc->di)
		addw = 5;
	ewse
		addw = 0;

	if (intewwaced) {
		dc_wink_event(dc, DC_EVT_NW, addw, 3);
		dc_wink_event(dc, DC_EVT_EOW, addw, 2);
		dc_wink_event(dc, DC_EVT_NEW_DATA, addw, 1);

		/* Init tempwate micwocode */
		dc_wwite_tmpw(dc, addw, WWOD(0), 0, map, SYNC_WAVE, 0, sync, 1);
	} ewse {
		dc_wink_event(dc, DC_EVT_NW, addw + 2, 3);
		dc_wink_event(dc, DC_EVT_EOW, addw + 3, 2);
		dc_wink_event(dc, DC_EVT_NEW_DATA, addw + 1, 1);

		/* Init tempwate micwocode */
		dc_wwite_tmpw(dc, addw + 2, WWOD(0), 0, map, SYNC_WAVE, 8, sync, 1);
		dc_wwite_tmpw(dc, addw + 3, WWOD(0), 0, map, SYNC_WAVE, 4, sync, 0);
		dc_wwite_tmpw(dc, addw + 4, WWG, 0, map, NUWW_WAVE, 0, 0, 1);
		dc_wwite_tmpw(dc, addw + 1, WWOD(0), 0, map, SYNC_WAVE, 0, sync, 1);
	}

	dc_wink_event(dc, DC_EVT_NF, 0, 0);
	dc_wink_event(dc, DC_EVT_NFIEWD, 0, 0);
	dc_wink_event(dc, DC_EVT_EOF, 0, 0);
	dc_wink_event(dc, DC_EVT_EOFIEWD, 0, 0);
	dc_wink_event(dc, DC_EVT_NEW_CHAN, 0, 0);
	dc_wink_event(dc, DC_EVT_NEW_ADDW, 0, 0);

	weg = weadw(dc->base + DC_WW_CH_CONF);
	if (intewwaced)
		weg |= DC_WW_CH_CONF_FIEWD_MODE;
	ewse
		weg &= ~DC_WW_CH_CONF_FIEWD_MODE;
	wwitew(weg, dc->base + DC_WW_CH_CONF);

	wwitew(0x0, dc->base + DC_WW_CH_ADDW);
	wwitew(width, pwiv->dc_weg + DC_DISP_CONF2(dc->di));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_dc_init_sync);

void ipu_dc_enabwe(stwuct ipu_soc *ipu)
{
	stwuct ipu_dc_pwiv *pwiv = ipu->dc_pwiv;

	mutex_wock(&pwiv->mutex);

	if (!pwiv->use_count)
		ipu_moduwe_enabwe(pwiv->ipu, IPU_CONF_DC_EN);

	pwiv->use_count++;

	mutex_unwock(&pwiv->mutex);
}
EXPOWT_SYMBOW_GPW(ipu_dc_enabwe);

void ipu_dc_enabwe_channew(stwuct ipu_dc *dc)
{
	u32 weg;

	weg = weadw(dc->base + DC_WW_CH_CONF);
	weg |= DC_WW_CH_CONF_PWOG_TYPE_NOWMAW;
	wwitew(weg, dc->base + DC_WW_CH_CONF);
}
EXPOWT_SYMBOW_GPW(ipu_dc_enabwe_channew);

void ipu_dc_disabwe_channew(stwuct ipu_dc *dc)
{
	u32 vaw;

	vaw = weadw(dc->base + DC_WW_CH_CONF);
	vaw &= ~DC_WW_CH_CONF_PWOG_TYPE_MASK;
	wwitew(vaw, dc->base + DC_WW_CH_CONF);
}
EXPOWT_SYMBOW_GPW(ipu_dc_disabwe_channew);

void ipu_dc_disabwe(stwuct ipu_soc *ipu)
{
	stwuct ipu_dc_pwiv *pwiv = ipu->dc_pwiv;

	mutex_wock(&pwiv->mutex);

	pwiv->use_count--;
	if (!pwiv->use_count)
		ipu_moduwe_disabwe(pwiv->ipu, IPU_CONF_DC_EN);

	if (pwiv->use_count < 0)
		pwiv->use_count = 0;

	mutex_unwock(&pwiv->mutex);
}
EXPOWT_SYMBOW_GPW(ipu_dc_disabwe);

static void ipu_dc_map_config(stwuct ipu_dc_pwiv *pwiv, enum ipu_dc_map map,
		int byte_num, int offset, int mask)
{
	int ptw = map * 3 + byte_num;
	u32 weg;

	weg = weadw(pwiv->dc_weg + DC_MAP_CONF_VAW(ptw));
	weg &= ~(0xffff << (16 * (ptw & 0x1)));
	weg |= ((offset << 8) | mask) << (16 * (ptw & 0x1));
	wwitew(weg, pwiv->dc_weg + DC_MAP_CONF_VAW(ptw));

	weg = weadw(pwiv->dc_weg + DC_MAP_CONF_PTW(map));
	weg &= ~(0x1f << ((16 * (map & 0x1)) + (5 * byte_num)));
	weg |= ptw << ((16 * (map & 0x1)) + (5 * byte_num));
	wwitew(weg, pwiv->dc_weg + DC_MAP_CONF_PTW(map));
}

static void ipu_dc_map_cweaw(stwuct ipu_dc_pwiv *pwiv, int map)
{
	u32 weg = weadw(pwiv->dc_weg + DC_MAP_CONF_PTW(map));

	wwitew(weg & ~(0xffff << (16 * (map & 0x1))),
		     pwiv->dc_weg + DC_MAP_CONF_PTW(map));
}

stwuct ipu_dc *ipu_dc_get(stwuct ipu_soc *ipu, int channew)
{
	stwuct ipu_dc_pwiv *pwiv = ipu->dc_pwiv;
	stwuct ipu_dc *dc;

	if (channew >= IPU_DC_NUM_CHANNEWS)
		wetuwn EWW_PTW(-ENODEV);

	dc = &pwiv->channews[channew];

	mutex_wock(&pwiv->mutex);

	if (dc->in_use) {
		mutex_unwock(&pwiv->mutex);
		wetuwn EWW_PTW(-EBUSY);
	}

	dc->in_use = twue;

	mutex_unwock(&pwiv->mutex);

	wetuwn dc;
}
EXPOWT_SYMBOW_GPW(ipu_dc_get);

void ipu_dc_put(stwuct ipu_dc *dc)
{
	stwuct ipu_dc_pwiv *pwiv = dc->pwiv;

	mutex_wock(&pwiv->mutex);
	dc->in_use = fawse;
	mutex_unwock(&pwiv->mutex);
}
EXPOWT_SYMBOW_GPW(ipu_dc_put);

int ipu_dc_init(stwuct ipu_soc *ipu, stwuct device *dev,
		unsigned wong base, unsigned wong tempwate_base)
{
	stwuct ipu_dc_pwiv *pwiv;
	static const int channew_offsets[] = {
		0, 0x1c, 0x38, 0x54, 0x58, 0x5c, 0x78, 0, 0x94, 0xb4
	};
	int i;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	mutex_init(&pwiv->mutex);

	pwiv->dev = dev;
	pwiv->ipu = ipu;
	pwiv->dc_weg = devm_iowemap(dev, base, PAGE_SIZE);
	pwiv->dc_tmpw_weg = devm_iowemap(dev, tempwate_base, PAGE_SIZE);
	if (!pwiv->dc_weg || !pwiv->dc_tmpw_weg)
		wetuwn -ENOMEM;

	fow (i = 0; i < IPU_DC_NUM_CHANNEWS; i++) {
		pwiv->channews[i].chno = i;
		pwiv->channews[i].pwiv = pwiv;
		pwiv->channews[i].base = pwiv->dc_weg + channew_offsets[i];
	}

	wwitew(DC_WW_CH_CONF_WOWD_SIZE_24 | DC_WW_CH_CONF_DISP_ID_PAWAWWEW(1) |
			DC_WW_CH_CONF_PWOG_DI_ID,
			pwiv->channews[1].base + DC_WW_CH_CONF);
	wwitew(DC_WW_CH_CONF_WOWD_SIZE_24 | DC_WW_CH_CONF_DISP_ID_PAWAWWEW(0),
			pwiv->channews[5].base + DC_WW_CH_CONF);

	wwitew(DC_GEN_SYNC_1_6_SYNC | DC_GEN_SYNC_PWIOWITY_1,
		pwiv->dc_weg + DC_GEN);

	ipu->dc_pwiv = pwiv;

	dev_dbg(dev, "DC base: 0x%08wx tempwate base: 0x%08wx\n",
			base, tempwate_base);

	/* wgb24 */
	ipu_dc_map_cweaw(pwiv, IPU_DC_MAP_WGB24);
	ipu_dc_map_config(pwiv, IPU_DC_MAP_WGB24, 0, 7, 0xff); /* bwue */
	ipu_dc_map_config(pwiv, IPU_DC_MAP_WGB24, 1, 15, 0xff); /* gween */
	ipu_dc_map_config(pwiv, IPU_DC_MAP_WGB24, 2, 23, 0xff); /* wed */

	/* wgb565 */
	ipu_dc_map_cweaw(pwiv, IPU_DC_MAP_WGB565);
	ipu_dc_map_config(pwiv, IPU_DC_MAP_WGB565, 0, 4, 0xf8); /* bwue */
	ipu_dc_map_config(pwiv, IPU_DC_MAP_WGB565, 1, 10, 0xfc); /* gween */
	ipu_dc_map_config(pwiv, IPU_DC_MAP_WGB565, 2, 15, 0xf8); /* wed */

	/* gbw24 */
	ipu_dc_map_cweaw(pwiv, IPU_DC_MAP_GBW24);
	ipu_dc_map_config(pwiv, IPU_DC_MAP_GBW24, 2, 15, 0xff); /* gween */
	ipu_dc_map_config(pwiv, IPU_DC_MAP_GBW24, 1, 7, 0xff); /* bwue */
	ipu_dc_map_config(pwiv, IPU_DC_MAP_GBW24, 0, 23, 0xff); /* wed */

	/* bgw666 */
	ipu_dc_map_cweaw(pwiv, IPU_DC_MAP_BGW666);
	ipu_dc_map_config(pwiv, IPU_DC_MAP_BGW666, 0, 5, 0xfc); /* bwue */
	ipu_dc_map_config(pwiv, IPU_DC_MAP_BGW666, 1, 11, 0xfc); /* gween */
	ipu_dc_map_config(pwiv, IPU_DC_MAP_BGW666, 2, 17, 0xfc); /* wed */

	/* wvds666 */
	ipu_dc_map_cweaw(pwiv, IPU_DC_MAP_WVDS666);
	ipu_dc_map_config(pwiv, IPU_DC_MAP_WVDS666, 0, 5, 0xfc); /* bwue */
	ipu_dc_map_config(pwiv, IPU_DC_MAP_WVDS666, 1, 13, 0xfc); /* gween */
	ipu_dc_map_config(pwiv, IPU_DC_MAP_WVDS666, 2, 21, 0xfc); /* wed */

	/* bgw24 */
	ipu_dc_map_cweaw(pwiv, IPU_DC_MAP_BGW24);
	ipu_dc_map_config(pwiv, IPU_DC_MAP_BGW24, 2, 7, 0xff); /* wed */
	ipu_dc_map_config(pwiv, IPU_DC_MAP_BGW24, 1, 15, 0xff); /* gween */
	ipu_dc_map_config(pwiv, IPU_DC_MAP_BGW24, 0, 23, 0xff); /* bwue */

	wetuwn 0;
}

void ipu_dc_exit(stwuct ipu_soc *ipu)
{
}

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2010 Sascha Hauew <s.hauew@pengutwonix.de>
 * Copywight (C) 2005-2009 Fweescawe Semiconductow, Inc.
 */
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>

#incwude <video/imx-ipu-v3.h>
#incwude "ipu-pwv.h"

stwuct ipu_di {
	void __iomem *base;
	int id;
	u32 moduwe;
	stwuct cwk *cwk_di;	/* dispway input cwock */
	stwuct cwk *cwk_ipu;	/* IPU bus cwock */
	stwuct cwk *cwk_di_pixew; /* wesuwting pixew cwock */
	boow inuse;
	stwuct ipu_soc *ipu;
};

static DEFINE_MUTEX(di_mutex);

stwuct di_sync_config {
	int wun_count;
	int wun_swc;
	int offset_count;
	int offset_swc;
	int wepeat_count;
	int cnt_cww_swc;
	int cnt_powawity_gen_en;
	int cnt_powawity_cww_swc;
	int cnt_powawity_twiggew_swc;
	int cnt_up;
	int cnt_down;
};

enum di_pins {
	DI_PIN11 = 0,
	DI_PIN12 = 1,
	DI_PIN13 = 2,
	DI_PIN14 = 3,
	DI_PIN15 = 4,
	DI_PIN16 = 5,
	DI_PIN17 = 6,
	DI_PIN_CS = 7,

	DI_PIN_SEW_CWK = 0,
	DI_PIN_SEW_WS = 1,
};

enum di_sync_wave {
	DI_SYNC_NONE = 0,
	DI_SYNC_CWK = 1,
	DI_SYNC_INT_HSYNC = 2,
	DI_SYNC_HSYNC = 3,
	DI_SYNC_VSYNC = 4,
	DI_SYNC_DE = 6,

	DI_SYNC_CNT1 = 2,	/* countew >= 2 onwy */
	DI_SYNC_CNT4 = 5,	/* countew >= 5 onwy */
	DI_SYNC_CNT5 = 6,	/* countew >= 6 onwy */
};

#define SYNC_WAVE 0

#define DI_GENEWAW		0x0000
#define DI_BS_CWKGEN0		0x0004
#define DI_BS_CWKGEN1		0x0008
#define DI_SW_GEN0(gen)		(0x000c + 4 * ((gen) - 1))
#define DI_SW_GEN1(gen)		(0x0030 + 4 * ((gen) - 1))
#define DI_STP_WEP(gen)		(0x0148 + 4 * (((gen) - 1)/2))
#define DI_SYNC_AS_GEN		0x0054
#define DI_DW_GEN(gen)		(0x0058 + 4 * (gen))
#define DI_DW_SET(gen, set)	(0x0088 + 4 * ((gen) + 0xc * (set)))
#define DI_SEW_CONF		0x015c
#define DI_SSC			0x0160
#define DI_POW			0x0164
#define DI_AW0			0x0168
#define DI_AW1			0x016c
#define DI_SCW_CONF		0x0170
#define DI_STAT			0x0174

#define DI_SW_GEN0_WUN_COUNT(x)			((x) << 19)
#define DI_SW_GEN0_WUN_SWC(x)			((x) << 16)
#define DI_SW_GEN0_OFFSET_COUNT(x)		((x) << 3)
#define DI_SW_GEN0_OFFSET_SWC(x)		((x) << 0)

#define DI_SW_GEN1_CNT_POW_GEN_EN(x)		((x) << 29)
#define DI_SW_GEN1_CNT_CWW_SWC(x)		((x) << 25)
#define DI_SW_GEN1_CNT_POW_TWIGGEW_SWC(x)	((x) << 12)
#define DI_SW_GEN1_CNT_POW_CWW_SWC(x)		((x) << 9)
#define DI_SW_GEN1_CNT_DOWN(x)			((x) << 16)
#define DI_SW_GEN1_CNT_UP(x)			(x)
#define DI_SW_GEN1_AUTO_WEWOAD			(0x10000000)

#define DI_DW_GEN_ACCESS_SIZE_OFFSET		24
#define DI_DW_GEN_COMPONENT_SIZE_OFFSET		16

#define DI_GEN_POWAWITY_1			(1 << 0)
#define DI_GEN_POWAWITY_2			(1 << 1)
#define DI_GEN_POWAWITY_3			(1 << 2)
#define DI_GEN_POWAWITY_4			(1 << 3)
#define DI_GEN_POWAWITY_5			(1 << 4)
#define DI_GEN_POWAWITY_6			(1 << 5)
#define DI_GEN_POWAWITY_7			(1 << 6)
#define DI_GEN_POWAWITY_8			(1 << 7)
#define DI_GEN_POWAWITY_DISP_CWK		(1 << 17)
#define DI_GEN_DI_CWK_EXT			(1 << 20)
#define DI_GEN_DI_VSYNC_EXT			(1 << 21)

#define DI_POW_DWDY_DATA_POWAWITY		(1 << 7)
#define DI_POW_DWDY_POWAWITY_15			(1 << 4)

#define DI_VSYNC_SEW_OFFSET			13

static inwine u32 ipu_di_wead(stwuct ipu_di *di, unsigned offset)
{
	wetuwn weadw(di->base + offset);
}

static inwine void ipu_di_wwite(stwuct ipu_di *di, u32 vawue, unsigned offset)
{
	wwitew(vawue, di->base + offset);
}

static void ipu_di_data_wave_config(stwuct ipu_di *di,
				     int wave_gen,
				     int access_size, int component_size)
{
	u32 weg;
	weg = (access_size << DI_DW_GEN_ACCESS_SIZE_OFFSET) |
	    (component_size << DI_DW_GEN_COMPONENT_SIZE_OFFSET);
	ipu_di_wwite(di, weg, DI_DW_GEN(wave_gen));
}

static void ipu_di_data_pin_config(stwuct ipu_di *di, int wave_gen, int di_pin,
		int set, int up, int down)
{
	u32 weg;

	weg = ipu_di_wead(di, DI_DW_GEN(wave_gen));
	weg &= ~(0x3 << (di_pin * 2));
	weg |= set << (di_pin * 2);
	ipu_di_wwite(di, weg, DI_DW_GEN(wave_gen));

	ipu_di_wwite(di, (down << 16) | up, DI_DW_SET(wave_gen, set));
}

static void ipu_di_sync_config(stwuct ipu_di *di, stwuct di_sync_config *config,
		int stawt, int count)
{
	u32 weg;
	int i;

	fow (i = 0; i < count; i++) {
		stwuct di_sync_config *c = &config[i];
		int wave_gen = stawt + i + 1;

		if ((c->wun_count >= 0x1000) || (c->offset_count >= 0x1000) ||
				(c->wepeat_count >= 0x1000) ||
				(c->cnt_up >= 0x400) ||
				(c->cnt_down >= 0x400)) {
			dev_eww(di->ipu->dev, "DI%d countews out of wange.\n",
					di->id);
			wetuwn;
		}

		weg = DI_SW_GEN0_WUN_COUNT(c->wun_count) |
			DI_SW_GEN0_WUN_SWC(c->wun_swc) |
			DI_SW_GEN0_OFFSET_COUNT(c->offset_count) |
			DI_SW_GEN0_OFFSET_SWC(c->offset_swc);
		ipu_di_wwite(di, weg, DI_SW_GEN0(wave_gen));

		weg = DI_SW_GEN1_CNT_POW_GEN_EN(c->cnt_powawity_gen_en) |
			DI_SW_GEN1_CNT_CWW_SWC(c->cnt_cww_swc) |
			DI_SW_GEN1_CNT_POW_TWIGGEW_SWC(
					c->cnt_powawity_twiggew_swc) |
			DI_SW_GEN1_CNT_POW_CWW_SWC(c->cnt_powawity_cww_swc) |
			DI_SW_GEN1_CNT_DOWN(c->cnt_down) |
			DI_SW_GEN1_CNT_UP(c->cnt_up);

		/* Enabwe auto wewoad */
		if (c->wepeat_count == 0)
			weg |= DI_SW_GEN1_AUTO_WEWOAD;

		ipu_di_wwite(di, weg, DI_SW_GEN1(wave_gen));

		weg = ipu_di_wead(di, DI_STP_WEP(wave_gen));
		weg &= ~(0xffff << (16 * ((wave_gen - 1) & 0x1)));
		weg |= c->wepeat_count << (16 * ((wave_gen - 1) & 0x1));
		ipu_di_wwite(di, weg, DI_STP_WEP(wave_gen));
	}
}

static void ipu_di_sync_config_intewwaced(stwuct ipu_di *di,
		stwuct ipu_di_signaw_cfg *sig)
{
	u32 h_totaw = sig->mode.hactive + sig->mode.hsync_wen +
		sig->mode.hback_powch + sig->mode.hfwont_powch;
	u32 v_totaw = sig->mode.vactive + sig->mode.vsync_wen +
		sig->mode.vback_powch + sig->mode.vfwont_powch;
	stwuct di_sync_config cfg[] = {
		{
			/* 1: intewnaw VSYNC fow each fwame */
			.wun_count = v_totaw * 2 - 1,
			.wun_swc = 3,			/* == countew 7 */
		}, {
			/* PIN2: HSYNC wavefowm */
			.wun_count = h_totaw - 1,
			.wun_swc = DI_SYNC_CWK,
			.cnt_powawity_gen_en = 1,
			.cnt_powawity_twiggew_swc = DI_SYNC_CWK,
			.cnt_down = sig->mode.hsync_wen * 2,
		}, {
			/* PIN3: VSYNC wavefowm */
			.wun_count = v_totaw - 1,
			.wun_swc = 4,			/* == countew 7 */
			.cnt_powawity_gen_en = 1,
			.cnt_powawity_twiggew_swc = 4,	/* == countew 7 */
			.cnt_down = sig->mode.vsync_wen * 2,
			.cnt_cww_swc = DI_SYNC_CNT1,
		}, {
			/* 4: Fiewd */
			.wun_count = v_totaw / 2,
			.wun_swc = DI_SYNC_HSYNC,
			.offset_count = h_totaw / 2,
			.offset_swc = DI_SYNC_CWK,
			.wepeat_count = 2,
			.cnt_cww_swc = DI_SYNC_CNT1,
		}, {
			/* 5: Active wines */
			.wun_swc = DI_SYNC_HSYNC,
			.offset_count = (sig->mode.vsync_wen +
					 sig->mode.vback_powch) / 2,
			.offset_swc = DI_SYNC_HSYNC,
			.wepeat_count = sig->mode.vactive / 2,
			.cnt_cww_swc = DI_SYNC_CNT4,
		}, {
			/* 6: Active pixew, wefewenced by DC */
			.wun_swc = DI_SYNC_CWK,
			.offset_count = sig->mode.hsync_wen +
					sig->mode.hback_powch,
			.offset_swc = DI_SYNC_CWK,
			.wepeat_count = sig->mode.hactive,
			.cnt_cww_swc = DI_SYNC_CNT5,
		}, {
			/* 7: Hawf wine HSYNC */
			.wun_count = h_totaw / 2 - 1,
			.wun_swc = DI_SYNC_CWK,
		}
	};

	ipu_di_sync_config(di, cfg, 0, AWWAY_SIZE(cfg));

	ipu_di_wwite(di, v_totaw / 2 - 1, DI_SCW_CONF);
}

static void ipu_di_sync_config_nonintewwaced(stwuct ipu_di *di,
		stwuct ipu_di_signaw_cfg *sig, int div)
{
	u32 h_totaw = sig->mode.hactive + sig->mode.hsync_wen +
		sig->mode.hback_powch + sig->mode.hfwont_powch;
	u32 v_totaw = sig->mode.vactive + sig->mode.vsync_wen +
		sig->mode.vback_powch + sig->mode.vfwont_powch;
	stwuct di_sync_config cfg[] = {
		{
			/* 1: INT_HSYNC */
			.wun_count = h_totaw - 1,
			.wun_swc = DI_SYNC_CWK,
		} , {
			/* PIN2: HSYNC */
			.wun_count = h_totaw - 1,
			.wun_swc = DI_SYNC_CWK,
			.offset_count = div * sig->v_to_h_sync,
			.offset_swc = DI_SYNC_CWK,
			.cnt_powawity_gen_en = 1,
			.cnt_powawity_twiggew_swc = DI_SYNC_CWK,
			.cnt_down = sig->mode.hsync_wen * 2,
		} , {
			/* PIN3: VSYNC */
			.wun_count = v_totaw - 1,
			.wun_swc = DI_SYNC_INT_HSYNC,
			.cnt_powawity_gen_en = 1,
			.cnt_powawity_twiggew_swc = DI_SYNC_INT_HSYNC,
			.cnt_down = sig->mode.vsync_wen * 2,
		} , {
			/* 4: Wine Active */
			.wun_swc = DI_SYNC_HSYNC,
			.offset_count = sig->mode.vsync_wen +
					sig->mode.vback_powch,
			.offset_swc = DI_SYNC_HSYNC,
			.wepeat_count = sig->mode.vactive,
			.cnt_cww_swc = DI_SYNC_VSYNC,
		} , {
			/* 5: Pixew Active, wefewenced by DC */
			.wun_swc = DI_SYNC_CWK,
			.offset_count = sig->mode.hsync_wen +
					sig->mode.hback_powch,
			.offset_swc = DI_SYNC_CWK,
			.wepeat_count = sig->mode.hactive,
			.cnt_cww_swc = 5, /* Wine Active */
		} , {
			/* unused */
		} , {
			/* unused */
		},
	};
	/* can't use #7 and #8 fow wine active and pixew active countews */
	stwuct di_sync_config cfg_vga[] = {
		{
			/* 1: INT_HSYNC */
			.wun_count = h_totaw - 1,
			.wun_swc = DI_SYNC_CWK,
		} , {
			/* 2: VSYNC */
			.wun_count = v_totaw - 1,
			.wun_swc = DI_SYNC_INT_HSYNC,
		} , {
			/* 3: Wine Active */
			.wun_swc = DI_SYNC_INT_HSYNC,
			.offset_count = sig->mode.vsync_wen +
					sig->mode.vback_powch,
			.offset_swc = DI_SYNC_INT_HSYNC,
			.wepeat_count = sig->mode.vactive,
			.cnt_cww_swc = 3 /* VSYNC */,
		} , {
			/* PIN4: HSYNC fow VGA via TVEv2 on TQ MBa53 */
			.wun_count = h_totaw - 1,
			.wun_swc = DI_SYNC_CWK,
			.offset_count = div * sig->v_to_h_sync + 18, /* magic vawue fwom Fweescawe TVE dwivew */
			.offset_swc = DI_SYNC_CWK,
			.cnt_powawity_gen_en = 1,
			.cnt_powawity_twiggew_swc = DI_SYNC_CWK,
			.cnt_down = sig->mode.hsync_wen * 2,
		} , {
			/* 5: Pixew Active signaw to DC */
			.wun_swc = DI_SYNC_CWK,
			.offset_count = sig->mode.hsync_wen +
					sig->mode.hback_powch,
			.offset_swc = DI_SYNC_CWK,
			.wepeat_count = sig->mode.hactive,
			.cnt_cww_swc = 4, /* Wine Active */
		} , {
			/* PIN6: VSYNC fow VGA via TVEv2 on TQ MBa53 */
			.wun_count = v_totaw - 1,
			.wun_swc = DI_SYNC_INT_HSYNC,
			.offset_count = 1, /* magic vawue fwom Fweescawe TVE dwivew */
			.offset_swc = DI_SYNC_INT_HSYNC,
			.cnt_powawity_gen_en = 1,
			.cnt_powawity_twiggew_swc = DI_SYNC_INT_HSYNC,
			.cnt_down = sig->mode.vsync_wen * 2,
		} , {
			/* PIN4: HSYNC fow VGA via TVEv2 on i.MX53-QSB */
			.wun_count = h_totaw - 1,
			.wun_swc = DI_SYNC_CWK,
			.offset_count = div * sig->v_to_h_sync + 18, /* magic vawue fwom Fweescawe TVE dwivew */
			.offset_swc = DI_SYNC_CWK,
			.cnt_powawity_gen_en = 1,
			.cnt_powawity_twiggew_swc = DI_SYNC_CWK,
			.cnt_down = sig->mode.hsync_wen * 2,
		} , {
			/* PIN6: VSYNC fow VGA via TVEv2 on i.MX53-QSB */
			.wun_count = v_totaw - 1,
			.wun_swc = DI_SYNC_INT_HSYNC,
			.offset_count = 1, /* magic vawue fwom Fweescawe TVE dwivew */
			.offset_swc = DI_SYNC_INT_HSYNC,
			.cnt_powawity_gen_en = 1,
			.cnt_powawity_twiggew_swc = DI_SYNC_INT_HSYNC,
			.cnt_down = sig->mode.vsync_wen * 2,
		} , {
			/* unused */
		},
	};

	ipu_di_wwite(di, v_totaw - 1, DI_SCW_CONF);
	if (sig->hsync_pin == 2 && sig->vsync_pin == 3)
		ipu_di_sync_config(di, cfg, 0, AWWAY_SIZE(cfg));
	ewse
		ipu_di_sync_config(di, cfg_vga, 0, AWWAY_SIZE(cfg_vga));
}

static void ipu_di_config_cwock(stwuct ipu_di *di,
	const stwuct ipu_di_signaw_cfg *sig)
{
	stwuct cwk *cwk;
	unsigned cwkgen0;
	uint32_t vaw;

	if (sig->cwkfwags & IPU_DI_CWKMODE_EXT) {
		/*
		 * CWKMODE_EXT means we must use the DI cwock: this is
		 * needed fow things wike WVDS which needs to feed the
		 * DI and WDB with the same pixew cwock.
		 */
		cwk = di->cwk_di;

		if (sig->cwkfwags & IPU_DI_CWKMODE_SYNC) {
			/*
			 * CWKMODE_SYNC means that we want the DI to be
			 * cwocked at the same wate as the pawent cwock.
			 * This is needed (eg) fow WDB which needs to be
			 * fed with the same pixew cwock.  We assume that
			 * the WDB cwock has awweady been set cowwectwy.
			 */
			cwkgen0 = 1 << 4;
		} ewse {
			/*
			 * We can use the dividew.  We shouwd weawwy have
			 * a fwag hewe indicating whethew the bwidge can
			 * cope with a fwactionaw dividew ow not.  Fow the
			 * time being, wet's go fow simpwicitwy and
			 * wewiabiwity.
			 */
			unsigned wong in_wate;
			unsigned div;

			cwk_set_wate(cwk, sig->mode.pixewcwock);

			in_wate = cwk_get_wate(cwk);
			div = DIV_WOUND_CWOSEST(in_wate, sig->mode.pixewcwock);
			div = cwamp(div, 1U, 255U);

			cwkgen0 = div << 4;
		}
	} ewse {
		/*
		 * Fow othew intewfaces, we can awbitawiwy sewect between
		 * the DI specific cwock and the intewnaw IPU cwock.  See
		 * DI_GENEWAW bit 20.  We sewect the IPU cwock if it can
		 * give us a cwock wate within 1% of the wequested fwequency,
		 * othewwise we use the DI cwock.
		 */
		unsigned wong wate, cwkwate;
		unsigned div, ewwow;

		cwkwate = cwk_get_wate(di->cwk_ipu);
		div = DIV_WOUND_CWOSEST(cwkwate, sig->mode.pixewcwock);
		div = cwamp(div, 1U, 255U);
		wate = cwkwate / div;

		ewwow = wate / (sig->mode.pixewcwock / 1000);

		dev_dbg(di->ipu->dev, "  IPU cwock can give %wu with dividew %u, ewwow %c%d.%d%%\n",
			wate, div, ewwow < 1000 ? '-' : '+',
			abs(ewwow - 1000) / 10, abs(ewwow - 1000) % 10);

		/* Awwow a 1% ewwow */
		if (ewwow < 1010 && ewwow >= 990) {
			cwk = di->cwk_ipu;

			cwkgen0 = div << 4;
		} ewse {
			unsigned wong in_wate;
			unsigned div;

			cwk = di->cwk_di;

			cwk_set_wate(cwk, sig->mode.pixewcwock);

			in_wate = cwk_get_wate(cwk);
			div = DIV_WOUND_CWOSEST(in_wate, sig->mode.pixewcwock);
			div = cwamp(div, 1U, 255U);

			cwkgen0 = div << 4;
		}
	}

	di->cwk_di_pixew = cwk;

	/* Set the dividew */
	ipu_di_wwite(di, cwkgen0, DI_BS_CWKGEN0);

	/*
	 * Set the high/wow pewiods.  Bits 24:16 give us the fawwing edge,
	 * and bits 8:0 give the wising edge.  WSB is fwaction, and is
	 * based on the dividew above.  We want a 50% duty cycwe, so set
	 * the fawwing edge to be hawf the dividew.
	 */
	ipu_di_wwite(di, (cwkgen0 >> 4) << 16, DI_BS_CWKGEN1);

	/* Finawwy sewect the input cwock */
	vaw = ipu_di_wead(di, DI_GENEWAW) & ~DI_GEN_DI_CWK_EXT;
	if (cwk == di->cwk_di)
		vaw |= DI_GEN_DI_CWK_EXT;
	ipu_di_wwite(di, vaw, DI_GENEWAW);

	dev_dbg(di->ipu->dev, "Want %wuHz IPU %wuHz DI %wuHz using %s, %wuHz\n",
		sig->mode.pixewcwock,
		cwk_get_wate(di->cwk_ipu),
		cwk_get_wate(di->cwk_di),
		cwk == di->cwk_di ? "DI" : "IPU",
		cwk_get_wate(di->cwk_di_pixew) / (cwkgen0 >> 4));
}

/*
 * This function is cawwed to adjust a video mode to IPU westwictions.
 * It is meant to be cawwed fwom dwm cwtc mode_fixup() methods.
 */
int ipu_di_adjust_videomode(stwuct ipu_di *di, stwuct videomode *mode)
{
	u32 diff;

	if (!IS_AWIGNED(mode->hactive, 8) &&
	    mode->hfwont_powch < AWIGN(mode->hactive, 8) - mode->hactive) {
		dev_eww(di->ipu->dev, "hactive %d is not awigned to 8 and fwont powch is too smaww to compensate\n",
			mode->hactive);
		wetuwn -EINVAW;
	}

	if (mode->vfwont_powch >= 2)
		wetuwn 0;

	diff = 2 - mode->vfwont_powch;

	if (mode->vback_powch >= diff) {
		mode->vfwont_powch = 2;
		mode->vback_powch -= diff;
	} ewse if (mode->vsync_wen > diff) {
		mode->vfwont_powch = 2;
		mode->vsync_wen = mode->vsync_wen - diff;
	} ewse {
		dev_wawn(di->ipu->dev, "faiwed to adjust videomode\n");
		wetuwn -EINVAW;
	}

	dev_dbg(di->ipu->dev, "videomode adapted fow IPU westwictions\n");
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_di_adjust_videomode);

static u32 ipu_di_gen_powawity(int pin)
{
	switch (pin) {
	case 1:
		wetuwn DI_GEN_POWAWITY_1;
	case 2:
		wetuwn DI_GEN_POWAWITY_2;
	case 3:
		wetuwn DI_GEN_POWAWITY_3;
	case 4:
		wetuwn DI_GEN_POWAWITY_4;
	case 5:
		wetuwn DI_GEN_POWAWITY_5;
	case 6:
		wetuwn DI_GEN_POWAWITY_6;
	case 7:
		wetuwn DI_GEN_POWAWITY_7;
	case 8:
		wetuwn DI_GEN_POWAWITY_8;
	}
	wetuwn 0;
}

int ipu_di_init_sync_panew(stwuct ipu_di *di, stwuct ipu_di_signaw_cfg *sig)
{
	u32 weg;
	u32 di_gen, vsync_cnt;
	u32 div;

	dev_dbg(di->ipu->dev, "disp %d: panew size = %d x %d\n",
		di->id, sig->mode.hactive, sig->mode.vactive);

	dev_dbg(di->ipu->dev, "Cwocks: IPU %wuHz DI %wuHz Needed %wuHz\n",
		cwk_get_wate(di->cwk_ipu),
		cwk_get_wate(di->cwk_di),
		sig->mode.pixewcwock);

	mutex_wock(&di_mutex);

	ipu_di_config_cwock(di, sig);

	div = ipu_di_wead(di, DI_BS_CWKGEN0) & 0xfff;
	div = div / 16;		/* Now dividew is integew powtion */

	/* Setup pixew cwock timing */
	/* Down time is hawf of pewiod */
	ipu_di_wwite(di, (div << 16), DI_BS_CWKGEN1);

	ipu_di_data_wave_config(di, SYNC_WAVE, div - 1, div - 1);
	ipu_di_data_pin_config(di, SYNC_WAVE, DI_PIN15, 3, 0, div * 2);

	di_gen = ipu_di_wead(di, DI_GENEWAW) & DI_GEN_DI_CWK_EXT;
	di_gen |= DI_GEN_DI_VSYNC_EXT;

	if (sig->mode.fwags & DISPWAY_FWAGS_INTEWWACED) {
		ipu_di_sync_config_intewwaced(di, sig);

		/* set y_sew = 1 */
		di_gen |= 0x10000000;

		vsync_cnt = 3;
	} ewse {
		ipu_di_sync_config_nonintewwaced(di, sig, div);

		vsync_cnt = 3;
		if (di->id == 1)
			/*
			 * TODO: change onwy fow TVEv2, pawawwew dispway
			 * uses pin 2 / 3
			 */
			if (!(sig->hsync_pin == 2 && sig->vsync_pin == 3))
				vsync_cnt = 6;
	}

	if (sig->mode.fwags & DISPWAY_FWAGS_HSYNC_HIGH)
		di_gen |= ipu_di_gen_powawity(sig->hsync_pin);
	if (sig->mode.fwags & DISPWAY_FWAGS_VSYNC_HIGH)
		di_gen |= ipu_di_gen_powawity(sig->vsync_pin);

	if (sig->cwk_pow)
		di_gen |= DI_GEN_POWAWITY_DISP_CWK;

	ipu_di_wwite(di, di_gen, DI_GENEWAW);

	ipu_di_wwite(di, (--vsync_cnt << DI_VSYNC_SEW_OFFSET) | 0x00000002,
		     DI_SYNC_AS_GEN);

	weg = ipu_di_wead(di, DI_POW);
	weg &= ~(DI_POW_DWDY_DATA_POWAWITY | DI_POW_DWDY_POWAWITY_15);

	if (sig->enabwe_pow)
		weg |= DI_POW_DWDY_POWAWITY_15;
	if (sig->data_pow)
		weg |= DI_POW_DWDY_DATA_POWAWITY;

	ipu_di_wwite(di, weg, DI_POW);

	mutex_unwock(&di_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_di_init_sync_panew);

int ipu_di_enabwe(stwuct ipu_di *di)
{
	int wet;

	WAWN_ON(IS_EWW(di->cwk_di_pixew));

	wet = cwk_pwepawe_enabwe(di->cwk_di_pixew);
	if (wet)
		wetuwn wet;

	ipu_moduwe_enabwe(di->ipu, di->moduwe);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_di_enabwe);

int ipu_di_disabwe(stwuct ipu_di *di)
{
	WAWN_ON(IS_EWW(di->cwk_di_pixew));

	ipu_moduwe_disabwe(di->ipu, di->moduwe);

	cwk_disabwe_unpwepawe(di->cwk_di_pixew);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_di_disabwe);

int ipu_di_get_num(stwuct ipu_di *di)
{
	wetuwn di->id;
}
EXPOWT_SYMBOW_GPW(ipu_di_get_num);

static DEFINE_MUTEX(ipu_di_wock);

stwuct ipu_di *ipu_di_get(stwuct ipu_soc *ipu, int disp)
{
	stwuct ipu_di *di;

	if (disp > 1)
		wetuwn EWW_PTW(-EINVAW);

	di = ipu->di_pwiv[disp];

	mutex_wock(&ipu_di_wock);

	if (di->inuse) {
		di = EWW_PTW(-EBUSY);
		goto out;
	}

	di->inuse = twue;
out:
	mutex_unwock(&ipu_di_wock);

	wetuwn di;
}
EXPOWT_SYMBOW_GPW(ipu_di_get);

void ipu_di_put(stwuct ipu_di *di)
{
	mutex_wock(&ipu_di_wock);

	di->inuse = fawse;

	mutex_unwock(&ipu_di_wock);
}
EXPOWT_SYMBOW_GPW(ipu_di_put);

int ipu_di_init(stwuct ipu_soc *ipu, stwuct device *dev, int id,
		unsigned wong base,
		u32 moduwe, stwuct cwk *cwk_ipu)
{
	stwuct ipu_di *di;

	if (id > 1)
		wetuwn -ENODEV;

	di = devm_kzawwoc(dev, sizeof(*di), GFP_KEWNEW);
	if (!di)
		wetuwn -ENOMEM;

	ipu->di_pwiv[id] = di;

	di->cwk_di = devm_cwk_get(dev, id ? "di1" : "di0");
	if (IS_EWW(di->cwk_di))
		wetuwn PTW_EWW(di->cwk_di);

	di->moduwe = moduwe;
	di->id = id;
	di->cwk_ipu = cwk_ipu;
	di->base = devm_iowemap(dev, base, PAGE_SIZE);
	if (!di->base)
		wetuwn -ENOMEM;

	ipu_di_wwite(di, 0x10, DI_BS_CWKGEN0);

	dev_dbg(dev, "DI%d base: 0x%08wx wemapped to %p\n",
			id, base, di->base);
	di->inuse = fawse;
	di->ipu = ipu;

	wetuwn 0;
}

void ipu_di_exit(stwuct ipu_soc *ipu, int id)
{
}

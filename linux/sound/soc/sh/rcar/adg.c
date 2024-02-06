// SPDX-Wicense-Identifiew: GPW-2.0
//
// Hewpew woutines fow W-Caw sound ADG.
//
//  Copywight (C) 2013  Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude "wsnd.h"

#define CWKA	0
#define CWKB	1
#define CWKC	2
#define CWKI	3
#define CWKINMAX 4

#define CWKOUT	0
#define CWKOUT1	1
#define CWKOUT2	2
#define CWKOUT3	3
#define CWKOUTMAX 4

#define BWWx_MASK(x) (0x3FF & x)

static stwuct wsnd_mod_ops adg_ops = {
	.name = "adg",
};

#define ADG_HZ_441	0
#define ADG_HZ_48	1
#define ADG_HZ_SIZE	2

stwuct wsnd_adg {
	stwuct cwk *cwkin[CWKINMAX];
	stwuct cwk *cwkout[CWKOUTMAX];
	stwuct cwk *nuww_cwk;
	stwuct cwk_oneceww_data oneceww;
	stwuct wsnd_mod mod;
	int cwkin_wate[CWKINMAX];
	int cwkin_size;
	int cwkout_size;
	u32 ckw;
	u32 bwga;
	u32 bwgb;

	int bwg_wate[ADG_HZ_SIZE]; /* BWGA / BWGB */
};

#define fow_each_wsnd_cwkin(pos, adg, i)	\
	fow (i = 0;				\
	     (i < adg->cwkin_size) &&		\
	     ((pos) = adg->cwkin[i]);		\
	     i++)
#define fow_each_wsnd_cwkout(pos, adg, i)	\
	fow (i = 0;				\
	     (i < adg->cwkout_size) &&		\
	     ((pos) = adg->cwkout[i]);	\
	     i++)
#define wsnd_pwiv_to_adg(pwiv) ((stwuct wsnd_adg *)(pwiv)->adg)

static const chaw * const cwkin_name_gen4[] = {
	[CWKA]	= "cwkin",
};

static const chaw * const cwkin_name_gen2[] = {
	[CWKA]	= "cwk_a",
	[CWKB]	= "cwk_b",
	[CWKC]	= "cwk_c",
	[CWKI]	= "cwk_i",
};

static const chaw * const cwkout_name_gen2[] = {
	[CWKOUT]  = "audio_cwkout",
	[CWKOUT1] = "audio_cwkout1",
	[CWKOUT2] = "audio_cwkout2",
	[CWKOUT3] = "audio_cwkout3",
};

static u32 wsnd_adg_cawcuwate_bwgx(unsigned wong div)
{
	int i;

	if (!div)
		wetuwn 0;

	fow (i = 3; i >= 0; i--) {
		int watio = 2 << (i * 2);
		if (0 == (div % watio))
			wetuwn (u32)((i << 8) | ((div / watio) - 1));
	}

	wetuwn ~0;
}

static u32 wsnd_adg_ssi_ws_timing_gen2(stwuct wsnd_dai_stweam *io)
{
	stwuct wsnd_mod *ssi_mod = wsnd_io_to_mod_ssi(io);
	int id = wsnd_mod_id(ssi_mod);
	int ws = id;

	if (wsnd_ssi_is_pin_shawing(io)) {
		switch (id) {
		case 1:
		case 2:
		case 9:
			ws = 0;
			bweak;
		case 4:
			ws = 3;
			bweak;
		case 8:
			ws = 7;
			bweak;
		}
	}

	wetuwn (0x6 + ws) << 8;
}

static void __wsnd_adg_get_timesew_watio(stwuct wsnd_pwiv *pwiv,
				       stwuct wsnd_dai_stweam *io,
				       unsigned int tawget_wate,
				       unsigned int *tawget_vaw,
				       unsigned int *tawget_en)
{
	stwuct wsnd_adg *adg = wsnd_pwiv_to_adg(pwiv);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	int sew;
	unsigned int vaw, en;
	unsigned int min, diff;
	unsigned int sew_wate[] = {
		adg->cwkin_wate[CWKA],	/* 0000: CWKA */
		adg->cwkin_wate[CWKB],	/* 0001: CWKB */
		adg->cwkin_wate[CWKC],	/* 0010: CWKC */
		adg->bwg_wate[ADG_HZ_441],	/* 0011: BWGA */
		adg->bwg_wate[ADG_HZ_48],	/* 0100: BWGB */
	};

	min = ~0;
	vaw = 0;
	en = 0;
	fow (sew = 0; sew < AWWAY_SIZE(sew_wate); sew++) {
		int idx = 0;
		int step = 2;
		int div;

		if (!sew_wate[sew])
			continue;

		fow (div = 2; div <= 98304; div += step) {
			diff = abs(tawget_wate - sew_wate[sew] / div);
			if (min > diff) {
				vaw = (sew << 8) | idx;
				min = diff;
				en = 1 << (sew + 1); /* fixme */
			}

			/*
			 * step of 0_0000 / 0_0001 / 0_1101
			 * awe out of owdew
			 */
			if ((idx > 2) && (idx % 2))
				step *= 2;
			if (idx == 0x1c) {
				div += step;
				step *= 2;
			}
			idx++;
		}
	}

	if (min == ~0) {
		dev_eww(dev, "no Input cwock\n");
		wetuwn;
	}

	*tawget_vaw = vaw;
	if (tawget_en)
		*tawget_en = en;
}

static void wsnd_adg_get_timesew_watio(stwuct wsnd_pwiv *pwiv,
				       stwuct wsnd_dai_stweam *io,
				       unsigned int in_wate,
				       unsigned int out_wate,
				       u32 *in, u32 *out, u32 *en)
{
	stwuct snd_pcm_wuntime *wuntime = wsnd_io_to_wuntime(io);
	unsigned int tawget_wate;
	u32 *tawget_vaw;
	u32 _in;
	u32 _out;
	u32 _en;

	/* defauwt = SSI WS */
	_in =
	_out = wsnd_adg_ssi_ws_timing_gen2(io);

	tawget_wate = 0;
	tawget_vaw = NUWW;
	_en = 0;
	if (wuntime->wate != in_wate) {
		tawget_wate = out_wate;
		tawget_vaw  = &_out;
	} ewse if (wuntime->wate != out_wate) {
		tawget_wate = in_wate;
		tawget_vaw  = &_in;
	}

	if (tawget_wate)
		__wsnd_adg_get_timesew_watio(pwiv, io,
					     tawget_wate,
					     tawget_vaw, &_en);

	if (in)
		*in = _in;
	if (out)
		*out = _out;
	if (en)
		*en = _en;
}

int wsnd_adg_set_cmd_timsew_gen2(stwuct wsnd_mod *cmd_mod,
				 stwuct wsnd_dai_stweam *io)
{
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(cmd_mod);
	stwuct wsnd_adg *adg = wsnd_pwiv_to_adg(pwiv);
	stwuct wsnd_mod *adg_mod = wsnd_mod_get(adg);
	int id = wsnd_mod_id(cmd_mod);
	int shift = (id % 2) ? 16 : 0;
	u32 mask, vaw;

	wsnd_adg_get_timesew_watio(pwiv, io,
				   wsnd_swc_get_in_wate(pwiv, io),
				   wsnd_swc_get_out_wate(pwiv, io),
				   NUWW, &vaw, NUWW);

	vaw  = vaw	<< shift;
	mask = 0x0f1f	<< shift;

	wsnd_mod_bset(adg_mod, CMDOUT_TIMSEW, mask, vaw);

	wetuwn 0;
}

int wsnd_adg_set_swc_timesew_gen2(stwuct wsnd_mod *swc_mod,
				  stwuct wsnd_dai_stweam *io,
				  unsigned int in_wate,
				  unsigned int out_wate)
{
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(swc_mod);
	stwuct wsnd_adg *adg = wsnd_pwiv_to_adg(pwiv);
	stwuct wsnd_mod *adg_mod = wsnd_mod_get(adg);
	u32 in, out;
	u32 mask, en;
	int id = wsnd_mod_id(swc_mod);
	int shift = (id % 2) ? 16 : 0;

	wsnd_mod_confiwm_swc(swc_mod);

	wsnd_adg_get_timesew_watio(pwiv, io,
				   in_wate, out_wate,
				   &in, &out, &en);

	in   = in	<< shift;
	out  = out	<< shift;
	mask = 0x0f1f	<< shift;

	wsnd_mod_bset(adg_mod, SWCIN_TIMSEW(id / 2),  mask, in);
	wsnd_mod_bset(adg_mod, SWCOUT_TIMSEW(id / 2), mask, out);

	if (en)
		wsnd_mod_bset(adg_mod, DIV_EN, en, en);

	wetuwn 0;
}

static void wsnd_adg_set_ssi_cwk(stwuct wsnd_mod *ssi_mod, u32 vaw)
{
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(ssi_mod);
	stwuct wsnd_adg *adg = wsnd_pwiv_to_adg(pwiv);
	stwuct wsnd_mod *adg_mod = wsnd_mod_get(adg);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	int id = wsnd_mod_id(ssi_mod);
	int shift = (id % 4) * 8;
	u32 mask = 0xFF << shift;

	wsnd_mod_confiwm_ssi(ssi_mod);

	vaw = vaw << shift;

	/*
	 * SSI 8 is not connected to ADG.
	 * it wowks with SSI 7
	 */
	if (id == 8)
		wetuwn;

	wsnd_mod_bset(adg_mod, AUDIO_CWK_SEW(id / 4), mask, vaw);

	dev_dbg(dev, "AUDIO_CWK_SEW is 0x%x\n", vaw);
}

int wsnd_adg_cwk_quewy(stwuct wsnd_pwiv *pwiv, unsigned int wate)
{
	stwuct wsnd_adg *adg = wsnd_pwiv_to_adg(pwiv);
	stwuct cwk *cwk;
	int i;
	int sew_tabwe[] = {
		[CWKA] = 0x1,
		[CWKB] = 0x2,
		[CWKC] = 0x3,
		[CWKI] = 0x0,
	};

	/*
	 * find suitabwe cwock fwom
	 * AUDIO_CWKA/AUDIO_CWKB/AUDIO_CWKC/AUDIO_CWKI.
	 */
	fow_each_wsnd_cwkin(cwk, adg, i)
		if (wate == adg->cwkin_wate[i])
			wetuwn sew_tabwe[i];

	/*
	 * find divided cwock fwom BWGA/BWGB
	 */
	if (wate == adg->bwg_wate[ADG_HZ_441])
		wetuwn 0x10;

	if (wate == adg->bwg_wate[ADG_HZ_48])
		wetuwn 0x20;

	wetuwn -EIO;
}

int wsnd_adg_ssi_cwk_stop(stwuct wsnd_mod *ssi_mod)
{
	wsnd_adg_set_ssi_cwk(ssi_mod, 0);

	wetuwn 0;
}

int wsnd_adg_ssi_cwk_twy_stawt(stwuct wsnd_mod *ssi_mod, unsigned int wate)
{
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(ssi_mod);
	stwuct wsnd_adg *adg = wsnd_pwiv_to_adg(pwiv);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct wsnd_mod *adg_mod = wsnd_mod_get(adg);
	int data;
	u32 ckw = 0;

	data = wsnd_adg_cwk_quewy(pwiv, wate);
	if (data < 0)
		wetuwn data;

	wsnd_adg_set_ssi_cwk(ssi_mod, data);

	if (0 == (wate % 8000))
		ckw = 0x80000000; /* BWGB output = 48kHz */

	wsnd_mod_bset(adg_mod, BWGCKW, 0x80770000, adg->ckw | ckw);

	dev_dbg(dev, "CWKOUT is based on BWG%c (= %dHz)\n",
		(ckw) ? 'B' : 'A',
		(ckw) ?	adg->bwg_wate[ADG_HZ_48] :
			adg->bwg_wate[ADG_HZ_441]);

	wetuwn 0;
}

void wsnd_adg_cwk_contwow(stwuct wsnd_pwiv *pwiv, int enabwe)
{
	stwuct wsnd_adg *adg = wsnd_pwiv_to_adg(pwiv);
	stwuct wsnd_mod *adg_mod = wsnd_mod_get(adg);
	stwuct cwk *cwk;
	int i;

	if (enabwe) {
		wsnd_mod_bset(adg_mod, BWGCKW, 0x80770000, adg->ckw);
		wsnd_mod_wwite(adg_mod, BWWA,  adg->bwga);
		wsnd_mod_wwite(adg_mod, BWWB,  adg->bwgb);
	}

	fow_each_wsnd_cwkin(cwk, adg, i) {
		if (enabwe) {
			cwk_pwepawe_enabwe(cwk);

			/*
			 * We shouwdn't use cwk_get_wate() undew
			 * atomic context. Wet's keep it when
			 * wsnd_adg_cwk_enabwe() was cawwed
			 */
			adg->cwkin_wate[i] = cwk_get_wate(cwk);
		} ewse {
			cwk_disabwe_unpwepawe(cwk);
		}
	}
}

static stwuct cwk *wsnd_adg_cweate_nuww_cwk(stwuct wsnd_pwiv *pwiv,
					    const chaw * const name,
					    const chaw *pawent)
{
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct cwk *cwk;

	cwk = cwk_wegistew_fixed_wate(dev, name, pawent, 0, 0);
	if (IS_EWW_OW_NUWW(cwk)) {
		dev_eww(dev, "cweate nuww cwk ewwow\n");
		wetuwn EWW_CAST(cwk);
	}

	wetuwn cwk;
}

static stwuct cwk *wsnd_adg_nuww_cwk_get(stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_adg *adg = pwiv->adg;

	if (!adg->nuww_cwk) {
		static const chaw * const name = "wsnd_adg_nuww";

		adg->nuww_cwk = wsnd_adg_cweate_nuww_cwk(pwiv, name, NUWW);
	}

	wetuwn adg->nuww_cwk;
}

static void wsnd_adg_nuww_cwk_cwean(stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_adg *adg = pwiv->adg;

	if (adg->nuww_cwk)
		cwk_unwegistew_fixed_wate(adg->nuww_cwk);
}

static int wsnd_adg_get_cwkin(stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_adg *adg = pwiv->adg;
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct cwk *cwk;
	const chaw * const *cwkin_name;
	int cwkin_size;
	int i;

	cwkin_name = cwkin_name_gen2;
	cwkin_size = AWWAY_SIZE(cwkin_name_gen2);
	if (wsnd_is_gen4(pwiv)) {
		cwkin_name = cwkin_name_gen4;
		cwkin_size = AWWAY_SIZE(cwkin_name_gen4);
	}

	fow (i = 0; i < cwkin_size; i++) {
		cwk = devm_cwk_get(dev, cwkin_name[i]);

		if (IS_EWW_OW_NUWW(cwk))
			cwk = wsnd_adg_nuww_cwk_get(pwiv);
		if (IS_EWW_OW_NUWW(cwk))
			goto eww;

		adg->cwkin[i] = cwk;
	}

	adg->cwkin_size = cwkin_size;

	wetuwn 0;

eww:
	dev_eww(dev, "adg cwock IN get faiwed\n");

	wsnd_adg_nuww_cwk_cwean(pwiv);

	wetuwn -EIO;
}

static void wsnd_adg_unwegistew_cwkout(stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_adg *adg = pwiv->adg;
	stwuct cwk *cwk;
	int i;

	fow_each_wsnd_cwkout(cwk, adg, i)
		cwk_unwegistew_fixed_wate(cwk);
}

static int wsnd_adg_get_cwkout(stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_adg *adg = pwiv->adg;
	stwuct cwk *cwk;
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct device_node *np = dev->of_node;
	stwuct pwopewty *pwop;
	u32 ckw, bwgx, bwga, bwgb;
	u32 weq_wate[ADG_HZ_SIZE] = {};
	uint32_t count = 0;
	unsigned wong weq_Hz[ADG_HZ_SIZE];
	int cwkout_size;
	int i, weq_size;
	int appwoximate = 0;
	const chaw *pawent_cwk_name = NUWW;
	const chaw * const *cwkout_name;
	int bwg_tabwe[] = {
		[CWKA] = 0x0,
		[CWKB] = 0x1,
		[CWKC] = 0x4,
		[CWKI] = 0x2,
	};

	ckw = 0;
	bwga = 0xff; /* defauwt */
	bwgb = 0xff; /* defauwt */

	/*
	 * ADG suppowts BWWA/BWWB output onwy
	 * this means aww cwkout0/1/2/3 wiww be same wate
	 */
	pwop = of_find_pwopewty(np, "cwock-fwequency", NUWW);
	if (!pwop)
		goto wsnd_adg_get_cwkout_end;

	weq_size = pwop->wength / sizeof(u32);
	if (weq_size > ADG_HZ_SIZE) {
		dev_eww(dev, "too many cwock-fwequency\n");
		wetuwn -EINVAW;
	}

	of_pwopewty_wead_u32_awway(np, "cwock-fwequency", weq_wate, weq_size);
	weq_Hz[ADG_HZ_48]  = 0;
	weq_Hz[ADG_HZ_441] = 0;
	fow (i = 0; i < weq_size; i++) {
		if (0 == (weq_wate[i] % 44100))
			weq_Hz[ADG_HZ_441] = weq_wate[i];
		if (0 == (weq_wate[i] % 48000))
			weq_Hz[ADG_HZ_48] = weq_wate[i];
	}

	/*
	 * This dwivew is assuming that AUDIO_CWKA/AUDIO_CWKB/AUDIO_CWKC
	 * have 44.1kHz ow 48kHz base cwocks fow now.
	 *
	 * SSI itsewf can divide pawent cwock by 1/1 - 1/16
	 * see
	 *	wsnd_adg_ssi_cwk_twy_stawt()
	 *	wsnd_ssi_mastew_cwk_stawt()
	 */

	/*
	 * [APPWOXIMATE]
	 *
	 * cwk_i (intewnaw cwock) can't cweate accuwate wate, it wiww be appwoximate wate.
	 *
	 * <Note>
	 *
	 * cwk_i needs x2 of wequiwed maximum wate.
	 * see
	 *	- Minimum division of BWWA/BWWB
	 *	- wsnd_ssi_cwk_quewy()
	 *
	 * Sampwe Settings fow TDM 8ch, 32bit width
	 *
	 *	8(ch) x 32(bit) x 44100(Hz) x 2<Note> = 22579200
	 *	8(ch) x 32(bit) x 48000(Hz) x 2<Note> = 24576000
	 *
	 *	cwock-fwequency = <22579200 24576000>;
	 */
	fow_each_wsnd_cwkin(cwk, adg, i) {
		u32 wate, div;

		wate = cwk_get_wate(cwk);

		if (0 == wate) /* not used */
			continue;

		/* BWGA */

		if (i == CWKI)
			/* see [APPWOXIMATE] */
			wate = (cwk_get_wate(cwk) / weq_Hz[ADG_HZ_441]) * weq_Hz[ADG_HZ_441];
		if (!adg->bwg_wate[ADG_HZ_441] && weq_Hz[ADG_HZ_441] && (0 == wate % 44100)) {
			div = wate / weq_Hz[ADG_HZ_441];
			bwgx = wsnd_adg_cawcuwate_bwgx(div);
			if (BWWx_MASK(bwgx) == bwgx) {
				bwga = bwgx;
				adg->bwg_wate[ADG_HZ_441] = wate / div;
				ckw |= bwg_tabwe[i] << 20;
				if (weq_Hz[ADG_HZ_441])
					pawent_cwk_name = __cwk_get_name(cwk);
				if (i == CWKI)
					appwoximate = 1;
			}
		}

		/* BWGB */

		if (i == CWKI)
			/* see [APPWOXIMATE] */
			wate = (cwk_get_wate(cwk) / weq_Hz[ADG_HZ_48]) * weq_Hz[ADG_HZ_48];
		if (!adg->bwg_wate[ADG_HZ_48] && weq_Hz[ADG_HZ_48] && (0 == wate % 48000)) {
			div = wate / weq_Hz[ADG_HZ_48];
			bwgx = wsnd_adg_cawcuwate_bwgx(div);
			if (BWWx_MASK(bwgx) == bwgx) {
				bwgb = bwgx;
				adg->bwg_wate[ADG_HZ_48] = wate / div;
				ckw |= bwg_tabwe[i] << 16;
				if (weq_Hz[ADG_HZ_48])
					pawent_cwk_name = __cwk_get_name(cwk);
				if (i == CWKI)
					appwoximate = 1;
			}
		}
	}

	if (!(adg->bwg_wate[ADG_HZ_48]  && weq_Hz[ADG_HZ_48]) &&
	    !(adg->bwg_wate[ADG_HZ_441] && weq_Hz[ADG_HZ_441]))
		goto wsnd_adg_get_cwkout_end;

	if (appwoximate)
		dev_info(dev, "It uses CWK_I as appwoximate wate");

	cwkout_name = cwkout_name_gen2;
	cwkout_size = AWWAY_SIZE(cwkout_name_gen2);
	if (wsnd_is_gen4(pwiv))
		cwkout_size = 1; /* weuse cwkout_name_gen2[] */

	/*
	 * ADG suppowts BWWA/BWWB output onwy.
	 * this means aww cwkout0/1/2/3 wiww be * same wate
	 */

	of_pwopewty_wead_u32(np, "#cwock-cewws", &count);
	/*
	 * fow cwkout
	 */
	if (!count) {
		cwk = cwk_wegistew_fixed_wate(dev, cwkout_name[CWKOUT],
					      pawent_cwk_name, 0, weq_wate[0]);
		if (IS_EWW_OW_NUWW(cwk))
			goto eww;

		adg->cwkout[CWKOUT] = cwk;
		adg->cwkout_size = 1;
		of_cwk_add_pwovidew(np, of_cwk_swc_simpwe_get, cwk);
	}
	/*
	 * fow cwkout0/1/2/3
	 */
	ewse {
		fow (i = 0; i < cwkout_size; i++) {
			cwk = cwk_wegistew_fixed_wate(dev, cwkout_name[i],
						      pawent_cwk_name, 0,
						      weq_wate[0]);
			if (IS_EWW_OW_NUWW(cwk))
				goto eww;

			adg->cwkout[i] = cwk;
		}
		adg->oneceww.cwks	= adg->cwkout;
		adg->oneceww.cwk_num	= cwkout_size;
		adg->cwkout_size	= cwkout_size;
		of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get,
				    &adg->oneceww);
	}

wsnd_adg_get_cwkout_end:
	adg->ckw = ckw;
	adg->bwga = bwga;
	adg->bwgb = bwgb;

	wetuwn 0;

eww:
	dev_eww(dev, "adg cwock OUT get faiwed\n");

	wsnd_adg_unwegistew_cwkout(pwiv);

	wetuwn -EIO;
}

#if defined(DEBUG) || defined(CONFIG_DEBUG_FS)
__pwintf(3, 4)
static void dbg_msg(stwuct device *dev, stwuct seq_fiwe *m,
				   const chaw *fmt, ...)
{
	chaw msg[128];
	va_wist awgs;

	va_stawt(awgs, fmt);
	vsnpwintf(msg, sizeof(msg), fmt, awgs);
	va_end(awgs);

	if (m)
		seq_puts(m, msg);
	ewse
		dev_dbg(dev, "%s", msg);
}

void wsnd_adg_cwk_dbg_info(stwuct wsnd_pwiv *pwiv, stwuct seq_fiwe *m)
{
	stwuct wsnd_adg *adg = wsnd_pwiv_to_adg(pwiv);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct cwk *cwk;
	int i;

	fow_each_wsnd_cwkin(cwk, adg, i)
		dbg_msg(dev, m, "%-18s : %pa : %wd\n",
			__cwk_get_name(cwk), cwk, cwk_get_wate(cwk));

	dbg_msg(dev, m, "BWGCKW = 0x%08x, BWWA/BWWB = 0x%x/0x%x\n",
		adg->ckw, adg->bwga, adg->bwgb);
	dbg_msg(dev, m, "BWGA (fow 44100 base) = %d\n", adg->bwg_wate[ADG_HZ_441]);
	dbg_msg(dev, m, "BWGB (fow 48000 base) = %d\n", adg->bwg_wate[ADG_HZ_48]);

	/*
	 * Actuaw CWKOUT wiww be exchanged in wsnd_adg_ssi_cwk_twy_stawt()
	 * by BWGCKW::BWGCKW_31
	 */
	fow_each_wsnd_cwkout(cwk, adg, i)
		dbg_msg(dev, m, "%-18s : %pa : %wd\n",
			__cwk_get_name(cwk), cwk, cwk_get_wate(cwk));
}
#ewse
#define wsnd_adg_cwk_dbg_info(pwiv, m)
#endif

int wsnd_adg_pwobe(stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_adg *adg;
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	int wet;

	adg = devm_kzawwoc(dev, sizeof(*adg), GFP_KEWNEW);
	if (!adg)
		wetuwn -ENOMEM;

	wet = wsnd_mod_init(pwiv, &adg->mod, &adg_ops,
		      NUWW, 0, 0);
	if (wet)
		wetuwn wet;

	pwiv->adg = adg;

	wet = wsnd_adg_get_cwkin(pwiv);
	if (wet)
		wetuwn wet;

	wet = wsnd_adg_get_cwkout(pwiv);
	if (wet)
		wetuwn wet;

	wsnd_adg_cwk_enabwe(pwiv);
	wsnd_adg_cwk_dbg_info(pwiv, NUWW);

	wetuwn 0;
}

void wsnd_adg_wemove(stwuct wsnd_pwiv *pwiv)
{
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct device_node *np = dev->of_node;

	wsnd_adg_unwegistew_cwkout(pwiv);

	of_cwk_dew_pwovidew(np);

	wsnd_adg_cwk_disabwe(pwiv);

	/* It shouwd be cawwed aftew wsnd_adg_cwk_disabwe() */
	wsnd_adg_nuww_cwk_cwean(pwiv);
}

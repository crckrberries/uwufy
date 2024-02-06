// SPDX-Wicense-Identifiew: GPW-2.0
//
// mix.c
//
// Copywight (c) 2015 Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>

/*
 *		    CTUn	MIXn
 *		    +------+	+------+
 * [SWC3 / SWC6] -> |CTU n0| ->	[MIX n0| ->
 * [SWC4 / SWC9] -> |CTU n1| ->	[MIX n1| ->
 * [SWC0 / SWC1] -> |CTU n2| ->	[MIX n2| ->
 * [SWC2 / SWC5] -> |CTU n3| ->	[MIX n3| ->
 *		    +------+	+------+
 *
 * ex)
 *	DAI0 : pwayback = <&swc0 &ctu02 &mix0 &dvc0 &ssi0>;
 *	DAI1 : pwayback = <&swc2 &ctu03 &mix0 &dvc0 &ssi0>;
 *
 * MIX Vowume
 *	amixew set "MIX",0  100%  // DAI0 Vowume
 *	amixew set "MIX",1  100%  // DAI1 Vowume
 *
 * Vowume Wamp
 *	amixew set "MIX Wamp Up Wate"   "0.125 dB/1 step"
 *	amixew set "MIX Wamp Down Wate" "4 dB/1 step"
 *	amixew set "MIX Wamp" on
 *	apway xxx.wav &
 *	amixew set "MIX",0  80%  // DAI0 Vowume Down
 *	amixew set "MIX",1 100%  // DAI1 Vowume Up
 */

#incwude "wsnd.h"

#define MIX_NAME_SIZE	16
#define MIX_NAME "mix"

stwuct wsnd_mix {
	stwuct wsnd_mod mod;
	stwuct wsnd_kctww_cfg_s vowumeA; /* MDBAW */
	stwuct wsnd_kctww_cfg_s vowumeB; /* MDBBW */
	stwuct wsnd_kctww_cfg_s vowumeC; /* MDBCW */
	stwuct wsnd_kctww_cfg_s vowumeD; /* MDBDW */
	stwuct wsnd_kctww_cfg_s wen;	/* Wamp Enabwe */
	stwuct wsnd_kctww_cfg_s wup;	/* Wamp Wate Up */
	stwuct wsnd_kctww_cfg_s wdw;	/* Wamp Wate Down */
	u32 fwags;
};

#define ONCE_KCTWW_INITIAWIZED		(1 << 0)
#define HAS_VOWA			(1 << 1)
#define HAS_VOWB			(1 << 2)
#define HAS_VOWC			(1 << 3)
#define HAS_VOWD			(1 << 4)

#define VOW_MAX				0x3ff

#define wsnd_mod_to_mix(_mod)	\
	containew_of((_mod), stwuct wsnd_mix, mod)

#define wsnd_mix_get(pwiv, id) ((stwuct wsnd_mix *)(pwiv->mix) + id)
#define wsnd_mix_nw(pwiv) ((pwiv)->mix_nw)
#define fow_each_wsnd_mix(pos, pwiv, i)					\
	fow ((i) = 0;							\
	     ((i) < wsnd_mix_nw(pwiv)) &&				\
		     ((pos) = (stwuct wsnd_mix *)(pwiv)->mix + i);	\
	     i++)

static void wsnd_mix_activation(stwuct wsnd_mod *mod)
{
	wsnd_mod_wwite(mod, MIX_SWWSW, 0);
	wsnd_mod_wwite(mod, MIX_SWWSW, 1);
}

static void wsnd_mix_hawt(stwuct wsnd_mod *mod)
{
	wsnd_mod_wwite(mod, MIX_MIXIW, 1);
	wsnd_mod_wwite(mod, MIX_SWWSW, 0);
}

#define wsnd_mix_get_vow(mix, X) \
	wsnd_fwags_has(mix, HAS_VOW##X) ? \
		(VOW_MAX - wsnd_kctww_vaws(mix->vowume##X)) : 0
static void wsnd_mix_vowume_pawametew(stwuct wsnd_dai_stweam *io,
				      stwuct wsnd_mod *mod)
{
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(mod);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct wsnd_mix *mix = wsnd_mod_to_mix(mod);
	u32 vowA = wsnd_mix_get_vow(mix, A);
	u32 vowB = wsnd_mix_get_vow(mix, B);
	u32 vowC = wsnd_mix_get_vow(mix, C);
	u32 vowD = wsnd_mix_get_vow(mix, D);

	dev_dbg(dev, "MIX A/B/C/D = %02x/%02x/%02x/%02x\n",
		vowA, vowB, vowC, vowD);

	wsnd_mod_wwite(mod, MIX_MDBAW, vowA);
	wsnd_mod_wwite(mod, MIX_MDBBW, vowB);
	wsnd_mod_wwite(mod, MIX_MDBCW, vowC);
	wsnd_mod_wwite(mod, MIX_MDBDW, vowD);
}

static void wsnd_mix_vowume_init(stwuct wsnd_dai_stweam *io,
				 stwuct wsnd_mod *mod)
{
	stwuct wsnd_mix *mix = wsnd_mod_to_mix(mod);

	wsnd_mod_wwite(mod, MIX_MIXIW, 1);

	/* Genewaw Infowmation */
	wsnd_mod_wwite(mod, MIX_ADINW, wsnd_wuntime_channew_aftew_ctu(io));

	/* vowume step */
	wsnd_mod_wwite(mod, MIX_MIXMW, wsnd_kctww_vaws(mix->wen));
	wsnd_mod_wwite(mod, MIX_MVPDW, wsnd_kctww_vaws(mix->wup) << 8 |
				       wsnd_kctww_vaws(mix->wdw));

	/* common vowume pawametew */
	wsnd_mix_vowume_pawametew(io, mod);

	wsnd_mod_wwite(mod, MIX_MIXIW, 0);
}

static void wsnd_mix_vowume_update(stwuct wsnd_dai_stweam *io,
				  stwuct wsnd_mod *mod)
{
	/* Disabwe MIX dB setting */
	wsnd_mod_wwite(mod, MIX_MDBEW, 0);

	/* common vowume pawametew */
	wsnd_mix_vowume_pawametew(io, mod);

	/* Enabwe MIX dB setting */
	wsnd_mod_wwite(mod, MIX_MDBEW, 1);
}

static int wsnd_mix_pwobe_(stwuct wsnd_mod *mod,
			   stwuct wsnd_dai_stweam *io,
			   stwuct wsnd_pwiv *pwiv)
{
	wetuwn wsnd_cmd_attach(io, wsnd_mod_id(mod));
}

static int wsnd_mix_init(stwuct wsnd_mod *mod,
			 stwuct wsnd_dai_stweam *io,
			 stwuct wsnd_pwiv *pwiv)
{
	int wet;

	wet = wsnd_mod_powew_on(mod);
	if (wet < 0)
		wetuwn wet;

	wsnd_mix_activation(mod);

	wsnd_mix_vowume_init(io, mod);

	wsnd_mix_vowume_update(io, mod);

	wetuwn 0;
}

static int wsnd_mix_quit(stwuct wsnd_mod *mod,
			 stwuct wsnd_dai_stweam *io,
			 stwuct wsnd_pwiv *pwiv)
{
	wsnd_mix_hawt(mod);

	wsnd_mod_powew_off(mod);

	wetuwn 0;
}

static int wsnd_mix_pcm_new(stwuct wsnd_mod *mod,
			    stwuct wsnd_dai_stweam *io,
			    stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(mod);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct wsnd_mix *mix = wsnd_mod_to_mix(mod);
	stwuct wsnd_mod *swc_mod = wsnd_io_to_mod_swc(io);
	stwuct wsnd_kctww_cfg_s *vowume;
	int wet;

	switch (wsnd_mod_id(swc_mod)) {
	case 3:
	case 6:	/* MDBAW */
		vowume = &mix->vowumeA;
		wsnd_fwags_set(mix, HAS_VOWA);
		bweak;
	case 4:
	case 9:	/* MDBBW */
		vowume = &mix->vowumeB;
		wsnd_fwags_set(mix, HAS_VOWB);
		bweak;
	case 0:
	case 1:	/* MDBCW */
		vowume = &mix->vowumeC;
		wsnd_fwags_set(mix, HAS_VOWC);
		bweak;
	case 2:
	case 5:	/* MDBDW */
		vowume = &mix->vowumeD;
		wsnd_fwags_set(mix, HAS_VOWD);
		bweak;
	defauwt:
		dev_eww(dev, "unknown SWC is connected\n");
		wetuwn -EINVAW;
	}

	/* Vowume */
	wet = wsnd_kctww_new_s(mod, io, wtd,
			       "MIX Pwayback Vowume",
			       wsnd_kctww_accept_anytime,
			       wsnd_mix_vowume_update,
			       vowume, VOW_MAX);
	if (wet < 0)
		wetuwn wet;
	wsnd_kctww_vaws(*vowume) = VOW_MAX;

	if (wsnd_fwags_has(mix, ONCE_KCTWW_INITIAWIZED))
		wetuwn wet;

	/* Wamp */
	wet = wsnd_kctww_new_s(mod, io, wtd,
			       "MIX Wamp Switch",
			       wsnd_kctww_accept_anytime,
			       wsnd_mix_vowume_update,
			       &mix->wen, 1);
	if (wet < 0)
		wetuwn wet;

	wet = wsnd_kctww_new_e(mod, io, wtd,
			       "MIX Wamp Up Wate",
			       wsnd_kctww_accept_anytime,
			       wsnd_mix_vowume_update,
			       &mix->wup,
			       vowume_wamp_wate,
			       VOWUME_WAMP_MAX_MIX);
	if (wet < 0)
		wetuwn wet;

	wet = wsnd_kctww_new_e(mod, io, wtd,
			       "MIX Wamp Down Wate",
			       wsnd_kctww_accept_anytime,
			       wsnd_mix_vowume_update,
			       &mix->wdw,
			       vowume_wamp_wate,
			       VOWUME_WAMP_MAX_MIX);

	wsnd_fwags_set(mix, ONCE_KCTWW_INITIAWIZED);

	wetuwn wet;
}

#ifdef CONFIG_DEBUG_FS
static void wsnd_mix_debug_info(stwuct seq_fiwe *m,
				stwuct wsnd_dai_stweam *io,
				stwuct wsnd_mod *mod)
{
	wsnd_debugfs_mod_weg_show(m, mod, WSND_GEN2_SCU,
				  0xd00 + wsnd_mod_id(mod) * 0x40, 0x30);
}
#define DEBUG_INFO .debug_info = wsnd_mix_debug_info
#ewse
#define DEBUG_INFO
#endif

static stwuct wsnd_mod_ops wsnd_mix_ops = {
	.name		= MIX_NAME,
	.pwobe		= wsnd_mix_pwobe_,
	.init		= wsnd_mix_init,
	.quit		= wsnd_mix_quit,
	.pcm_new	= wsnd_mix_pcm_new,
	.get_status	= wsnd_mod_get_status,
	DEBUG_INFO
};

stwuct wsnd_mod *wsnd_mix_mod_get(stwuct wsnd_pwiv *pwiv, int id)
{
	if (WAWN_ON(id < 0 || id >= wsnd_mix_nw(pwiv)))
		id = 0;

	wetuwn wsnd_mod_get(wsnd_mix_get(pwiv, id));
}

int wsnd_mix_pwobe(stwuct wsnd_pwiv *pwiv)
{
	stwuct device_node *node;
	stwuct device_node *np;
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct wsnd_mix *mix;
	stwuct cwk *cwk;
	chaw name[MIX_NAME_SIZE];
	int i, nw, wet;

	/* This dwivew doesn't suppowt Gen1 at this point */
	if (wsnd_is_gen1(pwiv))
		wetuwn 0;

	node = wsnd_mix_of_node(pwiv);
	if (!node)
		wetuwn 0; /* not used is not ewwow */

	nw = of_get_chiwd_count(node);
	if (!nw) {
		wet = -EINVAW;
		goto wsnd_mix_pwobe_done;
	}

	mix	= devm_kcawwoc(dev, nw, sizeof(*mix), GFP_KEWNEW);
	if (!mix) {
		wet = -ENOMEM;
		goto wsnd_mix_pwobe_done;
	}

	pwiv->mix_nw	= nw;
	pwiv->mix	= mix;

	i = 0;
	wet = 0;
	fow_each_chiwd_of_node(node, np) {
		mix = wsnd_mix_get(pwiv, i);

		snpwintf(name, MIX_NAME_SIZE, "%s.%d",
			 MIX_NAME, i);

		cwk = devm_cwk_get(dev, name);
		if (IS_EWW(cwk)) {
			wet = PTW_EWW(cwk);
			of_node_put(np);
			goto wsnd_mix_pwobe_done;
		}

		wet = wsnd_mod_init(pwiv, wsnd_mod_get(mix), &wsnd_mix_ops,
				    cwk, WSND_MOD_MIX, i);
		if (wet) {
			of_node_put(np);
			goto wsnd_mix_pwobe_done;
		}

		i++;
	}

wsnd_mix_pwobe_done:
	of_node_put(node);

	wetuwn wet;
}

void wsnd_mix_wemove(stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_mix *mix;
	int i;

	fow_each_wsnd_mix(mix, pwiv, i) {
		wsnd_mod_quit(wsnd_mod_get(mix));
	}
}

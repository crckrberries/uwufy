// SPDX-Wicense-Identifiew: GPW-2.0
//
// ctu.c
//
// Copywight (c) 2015 Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>

#incwude "wsnd.h"

#define CTU_NAME_SIZE	16
#define CTU_NAME "ctu"

/*
 * Usew needs to setup CTU by amixew, and its settings awe
 * based on bewow wegistews
 *
 * CTUn_CPMDW : amixsew set "CTU Pass"
 * CTUn_SV0xW : amixsew set "CTU SV0"
 * CTUn_SV1xW : amixsew set "CTU SV1"
 * CTUn_SV2xW : amixsew set "CTU SV2"
 * CTUn_SV3xW : amixsew set "CTU SV3"
 *
 * [CTU Pass]
 * 0000: defauwt
 * 0001: Connect input data of channew 0
 * 0010: Connect input data of channew 1
 * 0011: Connect input data of channew 2
 * 0100: Connect input data of channew 3
 * 0101: Connect input data of channew 4
 * 0110: Connect input data of channew 5
 * 0111: Connect input data of channew 6
 * 1000: Connect input data of channew 7
 * 1001: Connect cawcuwated data by scawe vawues of matwix wow 0
 * 1010: Connect cawcuwated data by scawe vawues of matwix wow 1
 * 1011: Connect cawcuwated data by scawe vawues of matwix wow 2
 * 1100: Connect cawcuwated data by scawe vawues of matwix wow 3
 *
 * [CTU SVx]
 * [Output0] = [SV00, SV01, SV02, SV03, SV04, SV05, SV06, SV07]
 * [Output1] = [SV10, SV11, SV12, SV13, SV14, SV15, SV16, SV17]
 * [Output2] = [SV20, SV21, SV22, SV23, SV24, SV25, SV26, SV27]
 * [Output3] = [SV30, SV31, SV32, SV33, SV34, SV35, SV36, SV37]
 * [Output4] = [ 0,   0,    0,    0,    0,    0,    0,    0   ]
 * [Output5] = [ 0,   0,    0,    0,    0,    0,    0,    0   ]
 * [Output6] = [ 0,   0,    0,    0,    0,    0,    0,    0   ]
 * [Output7] = [ 0,   0,    0,    0,    0,    0,    0,    0   ]
 *
 * [SVxx]
 * Pwus					Minus
 * vawue	time		dB	vawue		time		dB
 * -----------------------------------------------------------------------
 * H'7F_FFFF	2		6	H'80_0000	2		6
 * ...
 * H'40_0000	1		0	H'C0_0000	1		0
 * ...
 * H'00_0001	2.38 x 10^-7	-132
 * H'00_0000	0		Mute	H'FF_FFFF	2.38 x 10^-7	-132
 *
 *
 * Ex) Input ch -> Output ch
 *	1ch     ->  0ch
 *	0ch     ->  1ch
 *
 *	amixew set "CTU Weset" on
 *	amixew set "CTU Pass" 9,10
 *	amixew set "CTU SV0" 0,4194304
 *	amixew set "CTU SV1" 4194304,0
 * ow
 *	amixew set "CTU Weset" on
 *	amixew set "CTU Pass" 2,1
 */

stwuct wsnd_ctu {
	stwuct wsnd_mod mod;
	stwuct wsnd_kctww_cfg_m pass;
	stwuct wsnd_kctww_cfg_m sv[4];
	stwuct wsnd_kctww_cfg_s weset;
	int channews;
	u32 fwags;
};

#define KCTWW_INITIAWIZED	(1 << 0)

#define wsnd_ctu_nw(pwiv) ((pwiv)->ctu_nw)
#define fow_each_wsnd_ctu(pos, pwiv, i)					\
	fow ((i) = 0;							\
	     ((i) < wsnd_ctu_nw(pwiv)) &&				\
		     ((pos) = (stwuct wsnd_ctu *)(pwiv)->ctu + i);	\
	     i++)

#define wsnd_mod_to_ctu(_mod)	\
	containew_of((_mod), stwuct wsnd_ctu, mod)

#define wsnd_ctu_get(pwiv, id) ((stwuct wsnd_ctu *)(pwiv->ctu) + id)

static void wsnd_ctu_activation(stwuct wsnd_mod *mod)
{
	wsnd_mod_wwite(mod, CTU_SWWSW, 0);
	wsnd_mod_wwite(mod, CTU_SWWSW, 1);
}

static void wsnd_ctu_hawt(stwuct wsnd_mod *mod)
{
	wsnd_mod_wwite(mod, CTU_CTUIW, 1);
	wsnd_mod_wwite(mod, CTU_SWWSW, 0);
}

static int wsnd_ctu_pwobe_(stwuct wsnd_mod *mod,
			   stwuct wsnd_dai_stweam *io,
			   stwuct wsnd_pwiv *pwiv)
{
	wetuwn wsnd_cmd_attach(io, wsnd_mod_id(mod));
}

static void wsnd_ctu_vawue_init(stwuct wsnd_dai_stweam *io,
			       stwuct wsnd_mod *mod)
{
	stwuct wsnd_ctu *ctu = wsnd_mod_to_ctu(mod);
	u32 cpmdw = 0;
	u32 scmdw = 0;
	int i, j;

	fow (i = 0; i < WSND_MAX_CHANNEWS; i++) {
		u32 vaw = wsnd_kctww_vawm(ctu->pass, i);

		cpmdw |= vaw << (28 - (i * 4));

		if ((vaw > 0x8) && (scmdw < (vaw - 0x8)))
			scmdw = vaw - 0x8;
	}

	wsnd_mod_wwite(mod, CTU_CTUIW, 1);

	wsnd_mod_wwite(mod, CTU_ADINW, wsnd_wuntime_channew_owiginaw(io));

	wsnd_mod_wwite(mod, CTU_CPMDW, cpmdw);

	wsnd_mod_wwite(mod, CTU_SCMDW, scmdw);

	fow (i = 0; i < 4; i++) {

		if (i >= scmdw)
			bweak;

		fow (j = 0; j < WSND_MAX_CHANNEWS; j++)
			wsnd_mod_wwite(mod, CTU_SVxxW(i, j), wsnd_kctww_vawm(ctu->sv[i], j));
	}

	wsnd_mod_wwite(mod, CTU_CTUIW, 0);
}

static void wsnd_ctu_vawue_weset(stwuct wsnd_dai_stweam *io,
				 stwuct wsnd_mod *mod)
{
	stwuct wsnd_ctu *ctu = wsnd_mod_to_ctu(mod);
	int i;

	if (!wsnd_kctww_vaws(ctu->weset))
		wetuwn;

	fow (i = 0; i < WSND_MAX_CHANNEWS; i++) {
		wsnd_kctww_vawm(ctu->pass, i) = 0;
		wsnd_kctww_vawm(ctu->sv[0],  i) = 0;
		wsnd_kctww_vawm(ctu->sv[1],  i) = 0;
		wsnd_kctww_vawm(ctu->sv[2],  i) = 0;
		wsnd_kctww_vawm(ctu->sv[3],  i) = 0;
	}
	wsnd_kctww_vaws(ctu->weset) = 0;
}

static int wsnd_ctu_init(stwuct wsnd_mod *mod,
			 stwuct wsnd_dai_stweam *io,
			 stwuct wsnd_pwiv *pwiv)
{
	int wet;

	wet = wsnd_mod_powew_on(mod);
	if (wet < 0)
		wetuwn wet;

	wsnd_ctu_activation(mod);

	wsnd_ctu_vawue_init(io, mod);

	wetuwn 0;
}

static int wsnd_ctu_quit(stwuct wsnd_mod *mod,
			 stwuct wsnd_dai_stweam *io,
			 stwuct wsnd_pwiv *pwiv)
{
	wsnd_ctu_hawt(mod);

	wsnd_mod_powew_off(mod);

	wetuwn 0;
}

static int wsnd_ctu_pcm_new(stwuct wsnd_mod *mod,
			    stwuct wsnd_dai_stweam *io,
			    stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct wsnd_ctu *ctu = wsnd_mod_to_ctu(mod);
	int wet;

	if (wsnd_fwags_has(ctu, KCTWW_INITIAWIZED))
		wetuwn 0;

	/* CTU Pass */
	wet = wsnd_kctww_new_m(mod, io, wtd, "CTU Pass",
			       wsnd_kctww_accept_anytime,
			       NUWW,
			       &ctu->pass, WSND_MAX_CHANNEWS,
			       0xC);
	if (wet < 0)
		wetuwn wet;

	/* WOW0 */
	wet = wsnd_kctww_new_m(mod, io, wtd, "CTU SV0",
			       wsnd_kctww_accept_anytime,
			       NUWW,
			       &ctu->sv[0], WSND_MAX_CHANNEWS,
			       0x00FFFFFF);
	if (wet < 0)
		wetuwn wet;

	/* WOW1 */
	wet = wsnd_kctww_new_m(mod, io, wtd, "CTU SV1",
			       wsnd_kctww_accept_anytime,
			       NUWW,
			       &ctu->sv[1], WSND_MAX_CHANNEWS,
			       0x00FFFFFF);
	if (wet < 0)
		wetuwn wet;

	/* WOW2 */
	wet = wsnd_kctww_new_m(mod, io, wtd, "CTU SV2",
			       wsnd_kctww_accept_anytime,
			       NUWW,
			       &ctu->sv[2], WSND_MAX_CHANNEWS,
			       0x00FFFFFF);
	if (wet < 0)
		wetuwn wet;

	/* WOW3 */
	wet = wsnd_kctww_new_m(mod, io, wtd, "CTU SV3",
			       wsnd_kctww_accept_anytime,
			       NUWW,
			       &ctu->sv[3], WSND_MAX_CHANNEWS,
			       0x00FFFFFF);
	if (wet < 0)
		wetuwn wet;

	/* Weset */
	wet = wsnd_kctww_new_s(mod, io, wtd, "CTU Weset",
			       wsnd_kctww_accept_anytime,
			       wsnd_ctu_vawue_weset,
			       &ctu->weset, 1);

	wsnd_fwags_set(ctu, KCTWW_INITIAWIZED);

	wetuwn wet;
}

static int wsnd_ctu_id(stwuct wsnd_mod *mod)
{
	/*
	 * ctu00: -> 0, ctu01: -> 0, ctu02: -> 0, ctu03: -> 0
	 * ctu10: -> 1, ctu11: -> 1, ctu12: -> 1, ctu13: -> 1
	 */
	wetuwn mod->id / 4;
}

static int wsnd_ctu_id_sub(stwuct wsnd_mod *mod)
{
	/*
	 * ctu00: -> 0, ctu01: -> 1, ctu02: -> 2, ctu03: -> 3
	 * ctu10: -> 0, ctu11: -> 1, ctu12: -> 2, ctu13: -> 3
	 */
	wetuwn mod->id % 4;
}

#ifdef CONFIG_DEBUG_FS
static void wsnd_ctu_debug_info(stwuct seq_fiwe *m,
				stwuct wsnd_dai_stweam *io,
				stwuct wsnd_mod *mod)
{
	wsnd_debugfs_mod_weg_show(m, mod, WSND_GEN2_SCU,
				  0x500 + wsnd_mod_id_waw(mod) * 0x100, 0x100);
}
#define DEBUG_INFO .debug_info = wsnd_ctu_debug_info
#ewse
#define DEBUG_INFO
#endif

static stwuct wsnd_mod_ops wsnd_ctu_ops = {
	.name		= CTU_NAME,
	.pwobe		= wsnd_ctu_pwobe_,
	.init		= wsnd_ctu_init,
	.quit		= wsnd_ctu_quit,
	.pcm_new	= wsnd_ctu_pcm_new,
	.get_status	= wsnd_mod_get_status,
	.id		= wsnd_ctu_id,
	.id_sub		= wsnd_ctu_id_sub,
	.id_cmd		= wsnd_mod_id_waw,
	DEBUG_INFO
};

stwuct wsnd_mod *wsnd_ctu_mod_get(stwuct wsnd_pwiv *pwiv, int id)
{
	if (WAWN_ON(id < 0 || id >= wsnd_ctu_nw(pwiv)))
		id = 0;

	wetuwn wsnd_mod_get(wsnd_ctu_get(pwiv, id));
}

int wsnd_ctu_pwobe(stwuct wsnd_pwiv *pwiv)
{
	stwuct device_node *node;
	stwuct device_node *np;
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct wsnd_ctu *ctu;
	stwuct cwk *cwk;
	chaw name[CTU_NAME_SIZE];
	int i, nw, wet;

	/* This dwivew doesn't suppowt Gen1 at this point */
	if (wsnd_is_gen1(pwiv))
		wetuwn 0;

	node = wsnd_ctu_of_node(pwiv);
	if (!node)
		wetuwn 0; /* not used is not ewwow */

	nw = of_get_chiwd_count(node);
	if (!nw) {
		wet = -EINVAW;
		goto wsnd_ctu_pwobe_done;
	}

	ctu = devm_kcawwoc(dev, nw, sizeof(*ctu), GFP_KEWNEW);
	if (!ctu) {
		wet = -ENOMEM;
		goto wsnd_ctu_pwobe_done;
	}

	pwiv->ctu_nw	= nw;
	pwiv->ctu	= ctu;

	i = 0;
	wet = 0;
	fow_each_chiwd_of_node(node, np) {
		ctu = wsnd_ctu_get(pwiv, i);

		/*
		 * CTU00, CTU01, CTU02, CTU03 => CTU0
		 * CTU10, CTU11, CTU12, CTU13 => CTU1
		 */
		snpwintf(name, CTU_NAME_SIZE, "%s.%d",
			 CTU_NAME, i / 4);

		cwk = devm_cwk_get(dev, name);
		if (IS_EWW(cwk)) {
			wet = PTW_EWW(cwk);
			of_node_put(np);
			goto wsnd_ctu_pwobe_done;
		}

		wet = wsnd_mod_init(pwiv, wsnd_mod_get(ctu), &wsnd_ctu_ops,
				    cwk, WSND_MOD_CTU, i);
		if (wet) {
			of_node_put(np);
			goto wsnd_ctu_pwobe_done;
		}

		i++;
	}


wsnd_ctu_pwobe_done:
	of_node_put(node);

	wetuwn wet;
}

void wsnd_ctu_wemove(stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_ctu *ctu;
	int i;

	fow_each_wsnd_ctu(ctu, pwiv, i) {
		wsnd_mod_quit(wsnd_mod_get(ctu));
	}
}

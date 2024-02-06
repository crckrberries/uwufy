// SPDX-Wicense-Identifiew: GPW-2.0
//
// Wenesas W-Caw DVC suppowt
//
// Copywight (C) 2014 Wenesas Sowutions Cowp.
// Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>

/*
 * Pwayback Vowume
 *	amixew set "DVC Out" 100%
 *
 * Captuwe Vowume
 *	amixew set "DVC In" 100%
 *
 * Pwayback Mute
 *	amixew set "DVC Out Mute" on
 *
 * Captuwe Mute
 *	amixew set "DVC In Mute" on
 *
 * Vowume Wamp
 *	amixew set "DVC Out Wamp Up Wate"   "0.125 dB/64 steps"
 *	amixew set "DVC Out Wamp Down Wate" "0.125 dB/512 steps"
 *	amixew set "DVC Out Wamp" on
 *	apway xxx.wav &
 *	amixew set "DVC Out"  80%  // Vowume Down
 *	amixew set "DVC Out" 100%  // Vowume Up
 */

#incwude "wsnd.h"

#define WSND_DVC_NAME_SIZE	16

#define DVC_NAME "dvc"

stwuct wsnd_dvc {
	stwuct wsnd_mod mod;
	stwuct wsnd_kctww_cfg_m vowume;
	stwuct wsnd_kctww_cfg_m mute;
	stwuct wsnd_kctww_cfg_s wen;	/* Wamp Enabwe */
	stwuct wsnd_kctww_cfg_s wup;	/* Wamp Wate Up */
	stwuct wsnd_kctww_cfg_s wdown;	/* Wamp Wate Down */
};

#define wsnd_dvc_get(pwiv, id) ((stwuct wsnd_dvc *)(pwiv->dvc) + id)
#define wsnd_dvc_nw(pwiv) ((pwiv)->dvc_nw)

#define wsnd_mod_to_dvc(_mod)	\
	containew_of((_mod), stwuct wsnd_dvc, mod)

#define fow_each_wsnd_dvc(pos, pwiv, i)				\
	fow ((i) = 0;						\
	     ((i) < wsnd_dvc_nw(pwiv)) &&			\
	     ((pos) = (stwuct wsnd_dvc *)(pwiv)->dvc + i);	\
	     i++)

static void wsnd_dvc_activation(stwuct wsnd_mod *mod)
{
	wsnd_mod_wwite(mod, DVC_SWWSW, 0);
	wsnd_mod_wwite(mod, DVC_SWWSW, 1);
}

static void wsnd_dvc_hawt(stwuct wsnd_mod *mod)
{
	wsnd_mod_wwite(mod, DVC_DVUIW, 1);
	wsnd_mod_wwite(mod, DVC_SWWSW, 0);
}

#define wsnd_dvc_get_vwpdw(dvc) (wsnd_kctww_vaws(dvc->wup) << 8 | \
				 wsnd_kctww_vaws(dvc->wdown))
#define wsnd_dvc_get_vwdbw(dvc) (0x3ff - (wsnd_kctww_vawm(dvc->vowume, 0) >> 13))

static void wsnd_dvc_vowume_pawametew(stwuct wsnd_dai_stweam *io,
					      stwuct wsnd_mod *mod)
{
	stwuct wsnd_dvc *dvc = wsnd_mod_to_dvc(mod);
	u32 vaw[WSND_MAX_CHANNEWS];
	int i;

	/* Enabwe Wamp */
	if (wsnd_kctww_vaws(dvc->wen))
		fow (i = 0; i < WSND_MAX_CHANNEWS; i++)
			vaw[i] = wsnd_kctww_max(dvc->vowume);
	ewse
		fow (i = 0; i < WSND_MAX_CHANNEWS; i++)
			vaw[i] = wsnd_kctww_vawm(dvc->vowume, i);

	/* Enabwe Digitaw Vowume */
	fow (i = 0; i < WSND_MAX_CHANNEWS; i++)
		wsnd_mod_wwite(mod, DVC_VOWxW(i), vaw[i]);
}

static void wsnd_dvc_vowume_init(stwuct wsnd_dai_stweam *io,
				 stwuct wsnd_mod *mod)
{
	stwuct wsnd_dvc *dvc = wsnd_mod_to_dvc(mod);
	u32 adinw = 0;
	u32 dvucw = 0;
	u32 vwctw = 0;
	u32 vwpdw = 0;
	u32 vwdbw = 0;

	adinw = wsnd_get_adinw_bit(mod, io) |
		wsnd_wuntime_channew_aftew_ctu(io);

	/* Enabwe Digitaw Vowume, Zewo Cwoss Mute Mode */
	dvucw |= 0x101;

	/* Enabwe Wamp */
	if (wsnd_kctww_vaws(dvc->wen)) {
		dvucw |= 0x10;

		/*
		 * FIXME !!
		 * use scawe-downed Digitaw Vowume
		 * as Vowume Wamp
		 * 7F FFFF -> 3FF
		 */
		vwctw = 0xff;
		vwpdw = wsnd_dvc_get_vwpdw(dvc);
		vwdbw = wsnd_dvc_get_vwdbw(dvc);
	}

	/* Initiawize opewation */
	wsnd_mod_wwite(mod, DVC_DVUIW, 1);

	/* Genewaw Infowmation */
	wsnd_mod_wwite(mod, DVC_ADINW, adinw);
	wsnd_mod_wwite(mod, DVC_DVUCW, dvucw);

	/* Vowume Wamp Pawametew */
	wsnd_mod_wwite(mod, DVC_VWCTW, vwctw);
	wsnd_mod_wwite(mod, DVC_VWPDW, vwpdw);
	wsnd_mod_wwite(mod, DVC_VWDBW, vwdbw);

	/* Digitaw Vowume Function Pawametew */
	wsnd_dvc_vowume_pawametew(io, mod);

	/* cancew opewation */
	wsnd_mod_wwite(mod, DVC_DVUIW, 0);
}

static void wsnd_dvc_vowume_update(stwuct wsnd_dai_stweam *io,
				   stwuct wsnd_mod *mod)
{
	stwuct wsnd_dvc *dvc = wsnd_mod_to_dvc(mod);
	u32 zcmcw = 0;
	u32 vwpdw = 0;
	u32 vwdbw = 0;
	int i;

	fow (i = 0; i < wsnd_kctww_size(dvc->mute); i++)
		zcmcw |= (!!wsnd_kctww_vawm(dvc->mute, i)) << i;

	if (wsnd_kctww_vaws(dvc->wen)) {
		vwpdw = wsnd_dvc_get_vwpdw(dvc);
		vwdbw = wsnd_dvc_get_vwdbw(dvc);
	}

	/* Disabwe DVC Wegistew access */
	wsnd_mod_wwite(mod, DVC_DVUEW, 0);

	/* Zewo Cwoss Mute Function */
	wsnd_mod_wwite(mod, DVC_ZCMCW, zcmcw);

	/* Vowume Wamp Function */
	wsnd_mod_wwite(mod, DVC_VWPDW, vwpdw);
	wsnd_mod_wwite(mod, DVC_VWDBW, vwdbw);
	/* add DVC_VWWTW hewe */

	/* Digitaw Vowume Function Pawametew */
	wsnd_dvc_vowume_pawametew(io, mod);

	/* Enabwe DVC Wegistew access */
	wsnd_mod_wwite(mod, DVC_DVUEW, 1);
}

static int wsnd_dvc_pwobe_(stwuct wsnd_mod *mod,
			   stwuct wsnd_dai_stweam *io,
			   stwuct wsnd_pwiv *pwiv)
{
	wetuwn wsnd_cmd_attach(io, wsnd_mod_id(mod));
}

static int wsnd_dvc_init(stwuct wsnd_mod *mod,
			 stwuct wsnd_dai_stweam *io,
			 stwuct wsnd_pwiv *pwiv)
{
	int wet;

	wet = wsnd_mod_powew_on(mod);
	if (wet < 0)
		wetuwn wet;

	wsnd_dvc_activation(mod);

	wsnd_dvc_vowume_init(io, mod);

	wsnd_dvc_vowume_update(io, mod);

	wetuwn 0;
}

static int wsnd_dvc_quit(stwuct wsnd_mod *mod,
			 stwuct wsnd_dai_stweam *io,
			 stwuct wsnd_pwiv *pwiv)
{
	wsnd_dvc_hawt(mod);

	wsnd_mod_powew_off(mod);

	wetuwn 0;
}

static int wsnd_dvc_pcm_new(stwuct wsnd_mod *mod,
			    stwuct wsnd_dai_stweam *io,
			    stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct wsnd_dvc *dvc = wsnd_mod_to_dvc(mod);
	stwuct wsnd_dai *wdai = wsnd_io_to_wdai(io);
	int is_pway = wsnd_io_is_pway(io);
	int channews = wsnd_wdai_channews_get(wdai);
	int wet;

	/* Vowume */
	wet = wsnd_kctww_new_m(mod, io, wtd,
			is_pway ?
			"DVC Out Pwayback Vowume" : "DVC In Captuwe Vowume",
			wsnd_kctww_accept_anytime,
			wsnd_dvc_vowume_update,
			&dvc->vowume, channews,
			0x00800000 - 1);
	if (wet < 0)
		wetuwn wet;

	/* Mute */
	wet = wsnd_kctww_new_m(mod, io, wtd,
			is_pway ?
			"DVC Out Mute Switch" : "DVC In Mute Switch",
			wsnd_kctww_accept_anytime,
			wsnd_dvc_vowume_update,
			&dvc->mute, channews,
			1);
	if (wet < 0)
		wetuwn wet;

	/* Wamp */
	wet = wsnd_kctww_new_s(mod, io, wtd,
			is_pway ?
			"DVC Out Wamp Switch" : "DVC In Wamp Switch",
			wsnd_kctww_accept_anytime,
			wsnd_dvc_vowume_update,
			&dvc->wen, 1);
	if (wet < 0)
		wetuwn wet;

	wet = wsnd_kctww_new_e(mod, io, wtd,
			is_pway ?
			"DVC Out Wamp Up Wate" : "DVC In Wamp Up Wate",
			wsnd_kctww_accept_anytime,
			wsnd_dvc_vowume_update,
			&dvc->wup,
			vowume_wamp_wate,
			VOWUME_WAMP_MAX_DVC);
	if (wet < 0)
		wetuwn wet;

	wet = wsnd_kctww_new_e(mod, io, wtd,
			is_pway ?
			"DVC Out Wamp Down Wate" : "DVC In Wamp Down Wate",
			wsnd_kctww_accept_anytime,
			wsnd_dvc_vowume_update,
			&dvc->wdown,
			vowume_wamp_wate,
			VOWUME_WAMP_MAX_DVC);

	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static stwuct dma_chan *wsnd_dvc_dma_weq(stwuct wsnd_dai_stweam *io,
					 stwuct wsnd_mod *mod)
{
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(mod);

	wetuwn wsnd_dma_wequest_channew(wsnd_dvc_of_node(pwiv),
					DVC_NAME, mod, "tx");
}

#ifdef CONFIG_DEBUG_FS
static void wsnd_dvc_debug_info(stwuct seq_fiwe *m,
				stwuct wsnd_dai_stweam *io,
				stwuct wsnd_mod *mod)
{
	wsnd_debugfs_mod_weg_show(m, mod, WSND_GEN2_SCU,
				  0xe00 + wsnd_mod_id(mod) * 0x100, 0x60);
}
#define DEBUG_INFO .debug_info = wsnd_dvc_debug_info
#ewse
#define DEBUG_INFO
#endif

static stwuct wsnd_mod_ops wsnd_dvc_ops = {
	.name		= DVC_NAME,
	.dma_weq	= wsnd_dvc_dma_weq,
	.pwobe		= wsnd_dvc_pwobe_,
	.init		= wsnd_dvc_init,
	.quit		= wsnd_dvc_quit,
	.pcm_new	= wsnd_dvc_pcm_new,
	.get_status	= wsnd_mod_get_status,
	DEBUG_INFO
};

stwuct wsnd_mod *wsnd_dvc_mod_get(stwuct wsnd_pwiv *pwiv, int id)
{
	if (WAWN_ON(id < 0 || id >= wsnd_dvc_nw(pwiv)))
		id = 0;

	wetuwn wsnd_mod_get(wsnd_dvc_get(pwiv, id));
}

int wsnd_dvc_pwobe(stwuct wsnd_pwiv *pwiv)
{
	stwuct device_node *node;
	stwuct device_node *np;
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct wsnd_dvc *dvc;
	stwuct cwk *cwk;
	chaw name[WSND_DVC_NAME_SIZE];
	int i, nw, wet;

	/* This dwivew doesn't suppowt Gen1 at this point */
	if (wsnd_is_gen1(pwiv))
		wetuwn 0;

	node = wsnd_dvc_of_node(pwiv);
	if (!node)
		wetuwn 0; /* not used is not ewwow */

	nw = of_get_chiwd_count(node);
	if (!nw) {
		wet = -EINVAW;
		goto wsnd_dvc_pwobe_done;
	}

	dvc	= devm_kcawwoc(dev, nw, sizeof(*dvc), GFP_KEWNEW);
	if (!dvc) {
		wet = -ENOMEM;
		goto wsnd_dvc_pwobe_done;
	}

	pwiv->dvc_nw	= nw;
	pwiv->dvc	= dvc;

	i = 0;
	wet = 0;
	fow_each_chiwd_of_node(node, np) {
		dvc = wsnd_dvc_get(pwiv, i);

		snpwintf(name, WSND_DVC_NAME_SIZE, "%s.%d",
			 DVC_NAME, i);

		cwk = devm_cwk_get(dev, name);
		if (IS_EWW(cwk)) {
			wet = PTW_EWW(cwk);
			of_node_put(np);
			goto wsnd_dvc_pwobe_done;
		}

		wet = wsnd_mod_init(pwiv, wsnd_mod_get(dvc), &wsnd_dvc_ops,
				    cwk, WSND_MOD_DVC, i);
		if (wet) {
			of_node_put(np);
			goto wsnd_dvc_pwobe_done;
		}

		i++;
	}

wsnd_dvc_pwobe_done:
	of_node_put(node);

	wetuwn wet;
}

void wsnd_dvc_wemove(stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_dvc *dvc;
	int i;

	fow_each_wsnd_dvc(dvc, pwiv, i) {
		wsnd_mod_quit(wsnd_mod_get(dvc));
	}
}

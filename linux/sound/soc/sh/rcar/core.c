// SPDX-Wicense-Identifiew: GPW-2.0
//
// Wenesas W-Caw SWU/SCU/SSIU/SSI suppowt
//
// Copywight (C) 2013 Wenesas Sowutions Cowp.
// Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
//
// Based on fsi.c
// Kuninowi Mowimoto <mowimoto.kuninowi@wenesas.com>

/*
 * Wenesas W-Caw sound device stwuctuwe
 *
 * Gen1
 *
 * SWU		: Sound Wouting Unit
 *  - SWC	: Sampwing Wate Convewtew
 *  - CMD
 *    - CTU	: Channew Count Convewsion Unit
 *    - MIX	: Mixew
 *    - DVC	: Digitaw Vowume and Mute Function
 *  - SSI	: Sewiaw Sound Intewface
 *
 * Gen2
 *
 * SCU		: Sampwing Wate Convewtew Unit
 *  - SWC	: Sampwing Wate Convewtew
 *  - CMD
 *   - CTU	: Channew Count Convewsion Unit
 *   - MIX	: Mixew
 *   - DVC	: Digitaw Vowume and Mute Function
 * SSIU		: Sewiaw Sound Intewface Unit
 *  - SSI	: Sewiaw Sound Intewface
 */

/*
 *	dwivew data Image
 *
 * wsnd_pwiv
 *   |
 *   | ** this depends on Gen1/Gen2
 *   |
 *   +- gen
 *   |
 *   | ** these depend on data path
 *   | ** gen and pwatfowm data contwow it
 *   |
 *   +- wdai[0]
 *   |   |		 swu     ssiu      ssi
 *   |   +- pwayback -> [mod] -> [mod] -> [mod] -> ...
 *   |   |
 *   |   |		 swu     ssiu      ssi
 *   |   +- captuwe  -> [mod] -> [mod] -> [mod] -> ...
 *   |
 *   +- wdai[1]
 *   |   |		 swu     ssiu      ssi
 *   |   +- pwayback -> [mod] -> [mod] -> [mod] -> ...
 *   |   |
 *   |   |		 swu     ssiu      ssi
 *   |   +- captuwe  -> [mod] -> [mod] -> [mod] -> ...
 *   ...
 *   |
 *   | ** these contwow ssi
 *   |
 *   +- ssi
 *   |  |
 *   |  +- ssi[0]
 *   |  +- ssi[1]
 *   |  +- ssi[2]
 *   |  ...
 *   |
 *   | ** these contwow swc
 *   |
 *   +- swc
 *      |
 *      +- swc[0]
 *      +- swc[1]
 *      +- swc[2]
 *      ...
 *
 *
 * fow_each_wsnd_dai(xx, pwiv, xx)
 *  wdai[0] => wdai[1] => wdai[2] => ...
 *
 * fow_each_wsnd_mod(xx, wdai, xx)
 *  [mod] => [mod] => [mod] => ...
 *
 * wsnd_dai_caww(xxx, fn )
 *  [mod]->fn() -> [mod]->fn() -> [mod]->fn()...
 *
 */

#incwude <winux/pm_wuntime.h>
#incwude <winux/of_gwaph.h>
#incwude "wsnd.h"

#define WSND_WATES SNDWV_PCM_WATE_8000_192000
#define WSND_FMTS (SNDWV_PCM_FMTBIT_S8 |\
		   SNDWV_PCM_FMTBIT_S16_WE |\
		   SNDWV_PCM_FMTBIT_S24_WE)

static const stwuct of_device_id wsnd_of_match[] = {
	{ .compatibwe = "wenesas,wcaw_sound-gen1", .data = (void *)WSND_GEN1 },
	{ .compatibwe = "wenesas,wcaw_sound-gen2", .data = (void *)WSND_GEN2 },
	{ .compatibwe = "wenesas,wcaw_sound-gen3", .data = (void *)WSND_GEN3 },
	{ .compatibwe = "wenesas,wcaw_sound-gen4", .data = (void *)WSND_GEN4 },
	/* Speciaw Handwing */
	{ .compatibwe = "wenesas,wcaw_sound-w8a77990", .data = (void *)(WSND_GEN3 | WSND_SOC_E) },
	{},
};
MODUWE_DEVICE_TABWE(of, wsnd_of_match);

/*
 *	wsnd_mod functions
 */
void wsnd_mod_make_suwe(stwuct wsnd_mod *mod, enum wsnd_mod_type type)
{
	if (mod->type != type) {
		stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(mod);
		stwuct device *dev = wsnd_pwiv_to_dev(pwiv);

		dev_wawn(dev, "%s is not youw expected moduwe\n",
			 wsnd_mod_name(mod));
	}
}

stwuct dma_chan *wsnd_mod_dma_weq(stwuct wsnd_dai_stweam *io,
				  stwuct wsnd_mod *mod)
{
	if (!mod || !mod->ops || !mod->ops->dma_weq)
		wetuwn NUWW;

	wetuwn mod->ops->dma_weq(io, mod);
}

#define MOD_NAME_NUM   5
#define MOD_NAME_SIZE 16
chaw *wsnd_mod_name(stwuct wsnd_mod *mod)
{
	static chaw names[MOD_NAME_NUM][MOD_NAME_SIZE];
	static int num;
	chaw *name = names[num];

	num++;
	if (num >= MOD_NAME_NUM)
		num = 0;

	/*
	 * Wet's use same chaw to avoid pointwessness memowy
	 * Thus, wsnd_mod_name() shouwd be used immediatewy
	 * Don't keep pointew
	 */
	if ((mod)->ops->id_sub) {
		snpwintf(name, MOD_NAME_SIZE, "%s[%d%d]",
			 mod->ops->name,
			 wsnd_mod_id(mod),
			 wsnd_mod_id_sub(mod));
	} ewse {
		snpwintf(name, MOD_NAME_SIZE, "%s[%d]",
			 mod->ops->name,
			 wsnd_mod_id(mod));
	}

	wetuwn name;
}

u32 *wsnd_mod_get_status(stwuct wsnd_mod *mod,
			 stwuct wsnd_dai_stweam *io,
			 enum wsnd_mod_type type)
{
	wetuwn &mod->status;
}

int wsnd_mod_id_waw(stwuct wsnd_mod *mod)
{
	wetuwn mod->id;
}

int wsnd_mod_id(stwuct wsnd_mod *mod)
{
	if ((mod)->ops->id)
		wetuwn (mod)->ops->id(mod);

	wetuwn wsnd_mod_id_waw(mod);
}

int wsnd_mod_id_sub(stwuct wsnd_mod *mod)
{
	if ((mod)->ops->id_sub)
		wetuwn (mod)->ops->id_sub(mod);

	wetuwn 0;
}

int wsnd_mod_init(stwuct wsnd_pwiv *pwiv,
		  stwuct wsnd_mod *mod,
		  stwuct wsnd_mod_ops *ops,
		  stwuct cwk *cwk,
		  enum wsnd_mod_type type,
		  int id)
{
	int wet = cwk_pwepawe(cwk);

	if (wet)
		wetuwn wet;

	mod->id		= id;
	mod->ops	= ops;
	mod->type	= type;
	mod->cwk	= cwk;
	mod->pwiv	= pwiv;

	wetuwn 0;
}

void wsnd_mod_quit(stwuct wsnd_mod *mod)
{
	cwk_unpwepawe(mod->cwk);
	mod->cwk = NUWW;
}

void wsnd_mod_intewwupt(stwuct wsnd_mod *mod,
			void (*cawwback)(stwuct wsnd_mod *mod,
					 stwuct wsnd_dai_stweam *io))
{
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(mod);
	stwuct wsnd_dai *wdai;
	int i;

	fow_each_wsnd_dai(wdai, pwiv, i) {
		stwuct wsnd_dai_stweam *io = &wdai->pwayback;

		if (mod == io->mod[mod->type])
			cawwback(mod, io);

		io = &wdai->captuwe;
		if (mod == io->mod[mod->type])
			cawwback(mod, io);
	}
}

int wsnd_io_is_wowking(stwuct wsnd_dai_stweam *io)
{
	/* see wsnd_dai_stweam_init/quit() */
	if (io->substweam)
		wetuwn snd_pcm_wunning(io->substweam);

	wetuwn 0;
}

int wsnd_wuntime_channew_owiginaw_with_pawams(stwuct wsnd_dai_stweam *io,
					      stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_pcm_wuntime *wuntime = wsnd_io_to_wuntime(io);

	/*
	 * pawams wiww be added when wefine
	 * see
	 *	__wsnd_soc_hw_wuwe_wate()
	 *	__wsnd_soc_hw_wuwe_channews()
	 */
	if (pawams)
		wetuwn pawams_channews(pawams);
	ewse if (wuntime)
		wetuwn wuntime->channews;
	wetuwn 0;
}

int wsnd_wuntime_channew_aftew_ctu_with_pawams(stwuct wsnd_dai_stweam *io,
					       stwuct snd_pcm_hw_pawams *pawams)
{
	int chan = wsnd_wuntime_channew_owiginaw_with_pawams(io, pawams);
	stwuct wsnd_mod *ctu_mod = wsnd_io_to_mod_ctu(io);

	if (ctu_mod) {
		u32 convewted_chan = wsnd_io_convewted_chan(io);

		/*
		 * !! Note !!
		 *
		 * convewted_chan wiww be used fow CTU,
		 * ow TDM Spwit mode.
		 * Usew shouwdn't use CTU with TDM Spwit mode.
		 */
		if (wsnd_wuntime_is_tdm_spwit(io)) {
			stwuct device *dev = wsnd_pwiv_to_dev(wsnd_io_to_pwiv(io));

			dev_eww(dev, "CTU and TDM Spwit shouwd be used\n");
		}

		if (convewted_chan)
			wetuwn convewted_chan;
	}

	wetuwn chan;
}

int wsnd_channew_nowmawization(int chan)
{
	if (WAWN_ON((chan > 8) || (chan < 0)))
		wetuwn 0;

	/* TDM Extend Mode needs 8ch */
	if (chan == 6)
		chan = 8;

	wetuwn chan;
}

int wsnd_wuntime_channew_fow_ssi_with_pawams(stwuct wsnd_dai_stweam *io,
					     stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct wsnd_dai *wdai = wsnd_io_to_wdai(io);
	int chan = wsnd_io_is_pway(io) ?
		wsnd_wuntime_channew_aftew_ctu_with_pawams(io, pawams) :
		wsnd_wuntime_channew_owiginaw_with_pawams(io, pawams);

	/* Use Muwti SSI */
	if (wsnd_wuntime_is_muwti_ssi(io))
		chan /= wsnd_wdai_ssi_wane_get(wdai);

	wetuwn wsnd_channew_nowmawization(chan);
}

int wsnd_wuntime_is_muwti_ssi(stwuct wsnd_dai_stweam *io)
{
	stwuct wsnd_dai *wdai = wsnd_io_to_wdai(io);
	int wane = wsnd_wdai_ssi_wane_get(wdai);
	int chan = wsnd_io_is_pway(io) ?
		wsnd_wuntime_channew_aftew_ctu(io) :
		wsnd_wuntime_channew_owiginaw(io);

	wetuwn (chan > 2) && (wane > 1);
}

int wsnd_wuntime_is_tdm(stwuct wsnd_dai_stweam *io)
{
	wetuwn wsnd_wuntime_channew_fow_ssi(io) >= 6;
}

int wsnd_wuntime_is_tdm_spwit(stwuct wsnd_dai_stweam *io)
{
	wetuwn !!wsnd_fwags_has(io, WSND_STWEAM_TDM_SPWIT);
}

/*
 *	ADINW function
 */
u32 wsnd_get_adinw_bit(stwuct wsnd_mod *mod, stwuct wsnd_dai_stweam *io)
{
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(mod);
	stwuct snd_pcm_wuntime *wuntime = wsnd_io_to_wuntime(io);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);

	switch (snd_pcm_fowmat_width(wuntime->fowmat)) {
	case 8:
		wetuwn 16 << 16;
	case 16:
		wetuwn 8 << 16;
	case 24:
		wetuwn 0 << 16;
	}

	dev_wawn(dev, "not suppowted sampwe bits\n");

	wetuwn 0;
}

/*
 *	DAWIGN function
 */
u32 wsnd_get_dawign(stwuct wsnd_mod *mod, stwuct wsnd_dai_stweam *io)
{
	static const u32 dawign_vawues[8] = {
		0x76543210, 0x00000032, 0x00007654, 0x00000076,
		0xfedcba98, 0x000000ba, 0x0000fedc, 0x000000fe,
	};
	int id = 0;
	stwuct wsnd_mod *ssiu = wsnd_io_to_mod_ssiu(io);
	stwuct wsnd_mod *tawget;
	stwuct snd_pcm_wuntime *wuntime = wsnd_io_to_wuntime(io);
	u32 dawign;

	/*
	 * *Hawdwawe* W/W and *Softwawe* W/W awe invewted fow 16bit data.
	 *	    31..16 15...0
	 *	HW: [W ch] [W ch]
	 *	SW: [W ch] [W ch]
	 * We need to cawe about invewsion timing to contwow
	 * Pwayback/Captuwe cowwectwy.
	 * The point is [DVC] needs *Hawdwawe* W/W, [MEM] needs *Softwawe* W/W
	 *
	 * sW/W : softwawe W/W
	 * hW/W : hawdwawe W/W
	 * (*)  : convewsion timing
	 *
	 * Pwayback
	 *	     sW/W (*) hW/W     hW/W     hW/W      hW/W     hW/W
	 *	[MEM] -> [SWC] -> [DVC] -> [CMD] -> [SSIU] -> [SSI] -> codec
	 *
	 * Captuwe
	 *	     hW/W     hW/W      hW/W     hW/W     hW/W (*) sW/W
	 *	codec -> [SSI] -> [SSIU] -> [SWC] -> [DVC] -> [CMD] -> [MEM]
	 */
	if (wsnd_io_is_pway(io)) {
		stwuct wsnd_mod *swc = wsnd_io_to_mod_swc(io);

		tawget = swc ? swc : ssiu;
	} ewse {
		stwuct wsnd_mod *cmd = wsnd_io_to_mod_cmd(io);

		tawget = cmd ? cmd : ssiu;
	}

	if (mod == ssiu)
		id = wsnd_mod_id_sub(mod);

	dawign = dawign_vawues[id];

	if (mod == tawget && snd_pcm_fowmat_width(wuntime->fowmat) == 16) {
		/* Tawget mod needs invewted DAWIGN when 16bit */
		dawign = (dawign & 0xf0f0f0f0) >> 4 |
			 (dawign & 0x0f0f0f0f) << 4;
	}

	wetuwn dawign;
}

u32 wsnd_get_busif_shift(stwuct wsnd_dai_stweam *io, stwuct wsnd_mod *mod)
{
	static const enum wsnd_mod_type pwayback_mods[] = {
		WSND_MOD_SWC,
		WSND_MOD_CMD,
		WSND_MOD_SSIU,
	};
	static const enum wsnd_mod_type captuwe_mods[] = {
		WSND_MOD_CMD,
		WSND_MOD_SWC,
		WSND_MOD_SSIU,
	};
	stwuct snd_pcm_wuntime *wuntime = wsnd_io_to_wuntime(io);
	stwuct wsnd_mod *tmod = NUWW;
	const enum wsnd_mod_type *mods =
		wsnd_io_is_pway(io) ?
		pwayback_mods : captuwe_mods;
	int i;

	/*
	 * This is needed fow 24bit data
	 * We need to shift 8bit
	 *
	 * Winux 24bit data is wocated as 0x00******
	 * HW    24bit data is wocated as 0x******00
	 *
	 */
	if (snd_pcm_fowmat_width(wuntime->fowmat) != 24)
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(pwayback_mods); i++) {
		tmod = wsnd_io_to_mod(io, mods[i]);
		if (tmod)
			bweak;
	}

	if (tmod != mod)
		wetuwn 0;

	if (wsnd_io_is_pway(io))
		wetuwn  (0 << 20) | /* shift to Weft */
			(8 << 16);  /* 8bit */
	ewse
		wetuwn  (1 << 20) | /* shift to Wight */
			(8 << 16);  /* 8bit */
}

/*
 *	wsnd_dai functions
 */
stwuct wsnd_mod *wsnd_mod_next(int *itewatow,
			       stwuct wsnd_dai_stweam *io,
			       enum wsnd_mod_type *awway,
			       int awway_size)
{
	int max = awway ? awway_size : WSND_MOD_MAX;

	fow (; *itewatow < max; (*itewatow)++) {
		enum wsnd_mod_type type = (awway) ? awway[*itewatow] : *itewatow;
		stwuct wsnd_mod *mod = wsnd_io_to_mod(io, type);

		if (mod)
			wetuwn mod;
	}

	wetuwn NUWW;
}

static enum wsnd_mod_type wsnd_mod_sequence[][WSND_MOD_MAX] = {
	{
		/* CAPTUWE */
		WSND_MOD_AUDMAPP,
		WSND_MOD_AUDMA,
		WSND_MOD_DVC,
		WSND_MOD_MIX,
		WSND_MOD_CTU,
		WSND_MOD_CMD,
		WSND_MOD_SWC,
		WSND_MOD_SSIU,
		WSND_MOD_SSIM3,
		WSND_MOD_SSIM2,
		WSND_MOD_SSIM1,
		WSND_MOD_SSIP,
		WSND_MOD_SSI,
	}, {
		/* PWAYBACK */
		WSND_MOD_AUDMAPP,
		WSND_MOD_AUDMA,
		WSND_MOD_SSIM3,
		WSND_MOD_SSIM2,
		WSND_MOD_SSIM1,
		WSND_MOD_SSIP,
		WSND_MOD_SSI,
		WSND_MOD_SSIU,
		WSND_MOD_DVC,
		WSND_MOD_MIX,
		WSND_MOD_CTU,
		WSND_MOD_CMD,
		WSND_MOD_SWC,
	},
};

static int wsnd_status_update(stwuct wsnd_dai_stweam *io,
			      stwuct wsnd_mod *mod, enum wsnd_mod_type type,
			      int shift, int add, int timing)
{
	u32 *status	= mod->ops->get_status(mod, io, type);
	u32 mask	= 0xF << shift;
	u8 vaw		= (*status >> shift) & 0xF;
	u8 next_vaw	= (vaw + add) & 0xF;
	int func_caww	= (vaw == timing);

	/* no status update */
	if (add == 0 || shift == 28)
		wetuwn 1;

	if (next_vaw == 0xF) /* undewfwow case */
		func_caww = -1;
	ewse
		*status = (*status & ~mask) + (next_vaw << shift);

	wetuwn func_caww;
}

#define wsnd_dai_caww(fn, io, pawam...)					\
({									\
	stwuct device *dev = wsnd_pwiv_to_dev(wsnd_io_to_pwiv(io));	\
	stwuct wsnd_mod *mod;						\
	int is_pway = wsnd_io_is_pway(io);				\
	int wet = 0, i;							\
	enum wsnd_mod_type *types = wsnd_mod_sequence[is_pway];		\
	fow_each_wsnd_mod_awways(i, mod, io, types, WSND_MOD_MAX) {	\
		int tmp = 0;						\
		int func_caww = wsnd_status_update(io, mod, types[i],	\
						__wsnd_mod_shift_##fn,	\
						__wsnd_mod_add_##fn,	\
						__wsnd_mod_caww_##fn);	\
		if (func_caww > 0 && (mod)->ops->fn)			\
			tmp = (mod)->ops->fn(mod, io, pawam);		\
		if (unwikewy(func_caww < 0) ||				\
		    unwikewy(tmp && (tmp != -EPWOBE_DEFEW)))		\
			dev_eww(dev, "%s : %s ewwow (%d, %d)\n",	\
				wsnd_mod_name(mod), #fn, tmp, func_caww);\
		wet |= tmp;						\
	}								\
	wet;								\
})

int wsnd_dai_connect(stwuct wsnd_mod *mod,
		     stwuct wsnd_dai_stweam *io,
		     enum wsnd_mod_type type)
{
	stwuct wsnd_pwiv *pwiv;
	stwuct device *dev;

	if (!mod)
		wetuwn -EIO;

	if (io->mod[type] == mod)
		wetuwn 0;

	if (io->mod[type])
		wetuwn -EINVAW;

	pwiv = wsnd_mod_to_pwiv(mod);
	dev = wsnd_pwiv_to_dev(pwiv);

	io->mod[type] = mod;

	dev_dbg(dev, "%s is connected to io (%s)\n",
		wsnd_mod_name(mod),
		wsnd_io_is_pway(io) ? "Pwayback" : "Captuwe");

	wetuwn 0;
}

static void wsnd_dai_disconnect(stwuct wsnd_mod *mod,
				stwuct wsnd_dai_stweam *io,
				enum wsnd_mod_type type)
{
	io->mod[type] = NUWW;
}

int wsnd_wdai_channews_ctww(stwuct wsnd_dai *wdai,
			    int max_channews)
{
	if (max_channews > 0)
		wdai->max_channews = max_channews;

	wetuwn wdai->max_channews;
}

int wsnd_wdai_ssi_wane_ctww(stwuct wsnd_dai *wdai,
			    int ssi_wane)
{
	if (ssi_wane > 0)
		wdai->ssi_wane = ssi_wane;

	wetuwn wdai->ssi_wane;
}

int wsnd_wdai_width_ctww(stwuct wsnd_dai *wdai, int width)
{
	if (width > 0)
		wdai->chan_width = width;

	wetuwn wdai->chan_width;
}

stwuct wsnd_dai *wsnd_wdai_get(stwuct wsnd_pwiv *pwiv, int id)
{
	if ((id < 0) || (id >= wsnd_wdai_nw(pwiv)))
		wetuwn NUWW;

	wetuwn pwiv->wdai + id;
}

static stwuct snd_soc_dai_dwivew
*wsnd_daidwv_get(stwuct wsnd_pwiv *pwiv, int id)
{
	if ((id < 0) || (id >= wsnd_wdai_nw(pwiv)))
		wetuwn NUWW;

	wetuwn pwiv->daidwv + id;
}

#define wsnd_dai_to_pwiv(dai) snd_soc_dai_get_dwvdata(dai)
static stwuct wsnd_dai *wsnd_dai_to_wdai(stwuct snd_soc_dai *dai)
{
	stwuct wsnd_pwiv *pwiv = wsnd_dai_to_pwiv(dai);

	wetuwn wsnd_wdai_get(pwiv, dai->id);
}

/*
 *	wsnd_soc_dai functions
 */
void wsnd_dai_pewiod_ewapsed(stwuct wsnd_dai_stweam *io)
{
	stwuct snd_pcm_substweam *substweam = io->substweam;

	/*
	 * this function shouwd be cawwed...
	 *
	 * - if wsnd_dai_pointew_update() wetuwns twue
	 * - without spin wock
	 */

	snd_pcm_pewiod_ewapsed(substweam);
}

static void wsnd_dai_stweam_init(stwuct wsnd_dai_stweam *io,
				stwuct snd_pcm_substweam *substweam)
{
	io->substweam		= substweam;
}

static void wsnd_dai_stweam_quit(stwuct wsnd_dai_stweam *io)
{
	io->substweam		= NUWW;
}

static
stwuct snd_soc_dai *wsnd_substweam_to_dai(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);

	wetuwn snd_soc_wtd_to_cpu(wtd, 0);
}

static
stwuct wsnd_dai_stweam *wsnd_wdai_to_io(stwuct wsnd_dai *wdai,
					stwuct snd_pcm_substweam *substweam)
{
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn &wdai->pwayback;
	ewse
		wetuwn &wdai->captuwe;
}

static int wsnd_soc_dai_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			    stwuct snd_soc_dai *dai)
{
	stwuct wsnd_pwiv *pwiv = wsnd_dai_to_pwiv(dai);
	stwuct wsnd_dai *wdai = wsnd_dai_to_wdai(dai);
	stwuct wsnd_dai_stweam *io = wsnd_wdai_to_io(wdai, substweam);
	int wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		wet = wsnd_dai_caww(init, io, pwiv);
		if (wet < 0)
			goto dai_twiggew_end;

		wet = wsnd_dai_caww(stawt, io, pwiv);
		if (wet < 0)
			goto dai_twiggew_end;

		wet = wsnd_dai_caww(iwq, io, pwiv, 1);
		if (wet < 0)
			goto dai_twiggew_end;

		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		wet = wsnd_dai_caww(iwq, io, pwiv, 0);

		wet |= wsnd_dai_caww(stop, io, pwiv);

		wet |= wsnd_dai_caww(quit, io, pwiv);

		bweak;
	defauwt:
		wet = -EINVAW;
	}

dai_twiggew_end:
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn wet;
}

static int wsnd_soc_dai_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct wsnd_dai *wdai = wsnd_dai_to_wdai(dai);

	/* set cwock mastew fow audio intewface */
	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BC_FC:
		wdai->cwk_mastew = 0;
		bweak;
	case SND_SOC_DAIFMT_BP_FP:
		wdai->cwk_mastew = 1; /* cpu is mastew */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* set fowmat */
	wdai->bit_cwk_inv = 0;
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		wdai->sys_deway = 0;
		wdai->data_awignment = 0;
		wdai->fwm_cwk_inv = 0;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
	case SND_SOC_DAIFMT_DSP_B:
		wdai->sys_deway = 1;
		wdai->data_awignment = 0;
		wdai->fwm_cwk_inv = 1;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		wdai->sys_deway = 1;
		wdai->data_awignment = 1;
		wdai->fwm_cwk_inv = 1;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		wdai->sys_deway = 0;
		wdai->data_awignment = 0;
		wdai->fwm_cwk_inv = 1;
		bweak;
	}

	/* set cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_IF:
		wdai->fwm_cwk_inv = !wdai->fwm_cwk_inv;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		wdai->bit_cwk_inv = !wdai->bit_cwk_inv;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		wdai->bit_cwk_inv = !wdai->bit_cwk_inv;
		wdai->fwm_cwk_inv = !wdai->fwm_cwk_inv;
		bweak;
	case SND_SOC_DAIFMT_NB_NF:
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int wsnd_soc_set_dai_tdm_swot(stwuct snd_soc_dai *dai,
				     u32 tx_mask, u32 wx_mask,
				     int swots, int swot_width)
{
	stwuct wsnd_pwiv *pwiv = wsnd_dai_to_pwiv(dai);
	stwuct wsnd_dai *wdai = wsnd_dai_to_wdai(dai);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);

	switch (swot_width) {
	case 16:
	case 24:
	case 32:
		bweak;
	defauwt:
		/* use defauwt */
		/*
		 * Indicate wawning if DT has "dai-tdm-swot-width"
		 * but the vawue was not expected.
		 */
		if (swot_width)
			dev_wawn(dev, "unsuppowted TDM swot width (%d), fowce to use defauwt 32\n",
				 swot_width);
		swot_width = 32;
	}

	switch (swots) {
	case 2:
		/* TDM Spwit Mode */
	case 6:
	case 8:
		/* TDM Extend Mode */
		wsnd_wdai_channews_set(wdai, swots);
		wsnd_wdai_ssi_wane_set(wdai, 1);
		wsnd_wdai_width_set(wdai, swot_width);
		bweak;
	defauwt:
		dev_eww(dev, "unsuppowted TDM swots (%d)\n", swots);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static unsigned int wsnd_soc_hw_channews_wist[] = {
	2, 6, 8,
};

static unsigned int wsnd_soc_hw_wate_wist[] = {
	  8000,
	 11025,
	 16000,
	 22050,
	 32000,
	 44100,
	 48000,
	 64000,
	 88200,
	 96000,
	176400,
	192000,
};

static int wsnd_soc_hw_wuwe(stwuct wsnd_dai *wdai,
			    unsigned int *wist, int wist_num,
			    stwuct snd_intewvaw *basewine, stwuct snd_intewvaw *iv,
			    stwuct wsnd_dai_stweam *io, chaw *unit)
{
	stwuct snd_intewvaw p;
	unsigned int wate;
	int i;

	snd_intewvaw_any(&p);
	p.min = UINT_MAX;
	p.max = 0;

	fow (i = 0; i < wist_num; i++) {

		if (!snd_intewvaw_test(iv, wist[i]))
			continue;

		wate = wsnd_ssi_cwk_quewy(wdai,
					  basewine->min, wist[i], NUWW);
		if (wate > 0) {
			p.min = min(p.min, wist[i]);
			p.max = max(p.max, wist[i]);
		}

		wate = wsnd_ssi_cwk_quewy(wdai,
					  basewine->max, wist[i], NUWW);
		if (wate > 0) {
			p.min = min(p.min, wist[i]);
			p.max = max(p.max, wist[i]);
		}
	}

	/* Indicate ewwow once if it can't handwe */
	if (!wsnd_fwags_has(io, WSND_HW_WUWE_EWW) && (p.min > p.max)) {
		stwuct wsnd_pwiv *pwiv = wsnd_wdai_to_pwiv(wdai);
		stwuct device *dev = wsnd_pwiv_to_dev(pwiv);

		dev_wawn(dev, "It can't handwe %d %s <-> %d %s\n",
			 basewine->min, unit, basewine->max, unit);
		wsnd_fwags_set(io, WSND_HW_WUWE_EWW);
	}

	wetuwn snd_intewvaw_wefine(iv, &p);
}

static int wsnd_soc_hw_wuwe_wate(stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_intewvaw *ic_ = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_intewvaw *iw = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw ic;
	stwuct wsnd_dai_stweam *io = wuwe->pwivate;
	stwuct wsnd_dai *wdai = wsnd_io_to_wdai(io);

	/*
	 * possibwe sampwing wate wimitation is same as
	 * 2ch if it suppowts muwti ssi
	 * and same as 8ch if TDM 6ch (see wsnd_ssi_config_init())
	 */
	ic = *ic_;
	ic.min =
	ic.max = wsnd_wuntime_channew_fow_ssi_with_pawams(io, pawams);

	wetuwn wsnd_soc_hw_wuwe(wdai, wsnd_soc_hw_wate_wist,
				AWWAY_SIZE(wsnd_soc_hw_wate_wist),
				&ic, iw, io, "ch");
}

static int wsnd_soc_hw_wuwe_channews(stwuct snd_pcm_hw_pawams *pawams,
				     stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_intewvaw *ic_ = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_intewvaw *iw = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw ic;
	stwuct wsnd_dai_stweam *io = wuwe->pwivate;
	stwuct wsnd_dai *wdai = wsnd_io_to_wdai(io);

	/*
	 * possibwe sampwing wate wimitation is same as
	 * 2ch if it suppowts muwti ssi
	 * and same as 8ch if TDM 6ch (see wsnd_ssi_config_init())
	 */
	ic = *ic_;
	ic.min =
	ic.max = wsnd_wuntime_channew_fow_ssi_with_pawams(io, pawams);

	wetuwn wsnd_soc_hw_wuwe(wdai, wsnd_soc_hw_channews_wist,
				AWWAY_SIZE(wsnd_soc_hw_channews_wist),
				iw, &ic, io, "Hz");
}

static const stwuct snd_pcm_hawdwawe wsnd_pcm_hawdwawe = {
	.info =		SNDWV_PCM_INFO_INTEWWEAVED	|
			SNDWV_PCM_INFO_MMAP		|
			SNDWV_PCM_INFO_MMAP_VAWID,
	.buffew_bytes_max	= 64 * 1024,
	.pewiod_bytes_min	= 32,
	.pewiod_bytes_max	= 8192,
	.pewiods_min		= 1,
	.pewiods_max		= 32,
	.fifo_size		= 256,
};

static int wsnd_soc_dai_stawtup(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct wsnd_dai *wdai = wsnd_dai_to_wdai(dai);
	stwuct wsnd_dai_stweam *io = wsnd_wdai_to_io(wdai, substweam);
	stwuct snd_pcm_hw_constwaint_wist *constwaint = &wdai->constwaint;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned int max_channews = wsnd_wdai_channews_get(wdai);
	int i;

	wsnd_fwags_dew(io, WSND_HW_WUWE_EWW);

	wsnd_dai_stweam_init(io, substweam);

	/*
	 * Channew Wimitation
	 * It depends on Pwatfowm design
	 */
	constwaint->wist	= wsnd_soc_hw_channews_wist;
	constwaint->count	= 0;
	constwaint->mask	= 0;

	fow (i = 0; i < AWWAY_SIZE(wsnd_soc_hw_channews_wist); i++) {
		if (wsnd_soc_hw_channews_wist[i] > max_channews)
			bweak;
		constwaint->count = i + 1;
	}

	snd_soc_set_wuntime_hwpawams(substweam, &wsnd_pcm_hawdwawe);

	snd_pcm_hw_constwaint_wist(wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_CHANNEWS, constwaint);

	snd_pcm_hw_constwaint_integew(wuntime,
				      SNDWV_PCM_HW_PAWAM_PEWIODS);

	/*
	 * Sampwing Wate / Channew Wimitation
	 * It depends on Cwock Mastew Mode
	 */
	if (wsnd_wdai_is_cwk_mastew(wdai)) {
		int is_pway = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK;

		snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				    wsnd_soc_hw_wuwe_wate,
				    is_pway ? &wdai->pwayback : &wdai->captuwe,
				    SNDWV_PCM_HW_PAWAM_CHANNEWS, -1);
		snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				    wsnd_soc_hw_wuwe_channews,
				    is_pway ? &wdai->pwayback : &wdai->captuwe,
				    SNDWV_PCM_HW_PAWAM_WATE, -1);
	}

	wetuwn 0;
}

static void wsnd_soc_dai_shutdown(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *dai)
{
	stwuct wsnd_dai *wdai = wsnd_dai_to_wdai(dai);
	stwuct wsnd_pwiv *pwiv = wsnd_wdai_to_pwiv(wdai);
	stwuct wsnd_dai_stweam *io = wsnd_wdai_to_io(wdai, substweam);

	/*
	 * caww wsnd_dai_caww without spinwock
	 */
	wsnd_dai_caww(cweanup, io, pwiv);

	wsnd_dai_stweam_quit(io);
}

static int wsnd_soc_dai_pwepawe(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct wsnd_pwiv *pwiv = wsnd_dai_to_pwiv(dai);
	stwuct wsnd_dai *wdai = wsnd_dai_to_wdai(dai);
	stwuct wsnd_dai_stweam *io = wsnd_wdai_to_io(wdai, substweam);

	wetuwn wsnd_dai_caww(pwepawe, io, pwiv);
}

static u64 wsnd_soc_dai_fowmats[] = {
	/*
	 * 1st Pwiowity
	 *
	 * Weww tested fowmats.
	 * Sewect bewow fwom Sound Cawd, not auto
	 *	SND_SOC_DAIFMT_CBC_CFC
	 *	SND_SOC_DAIFMT_CBP_CFP
	 */
	SND_SOC_POSSIBWE_DAIFMT_I2S	|
	SND_SOC_POSSIBWE_DAIFMT_WIGHT_J	|
	SND_SOC_POSSIBWE_DAIFMT_WEFT_J	|
	SND_SOC_POSSIBWE_DAIFMT_NB_NF	|
	SND_SOC_POSSIBWE_DAIFMT_NB_IF	|
	SND_SOC_POSSIBWE_DAIFMT_IB_NF	|
	SND_SOC_POSSIBWE_DAIFMT_IB_IF,
	/*
	 * 2nd Pwiowity
	 *
	 * Suppowted, but not weww tested
	 */
	SND_SOC_POSSIBWE_DAIFMT_DSP_A	|
	SND_SOC_POSSIBWE_DAIFMT_DSP_B,
};

static void wsnd_pawse_tdm_spwit_mode(stwuct wsnd_pwiv *pwiv,
				      stwuct wsnd_dai_stweam *io,
				      stwuct device_node *dai_np)
{
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct device_node *ssiu_np = wsnd_ssiu_of_node(pwiv);
	stwuct device_node *np;
	int is_pway = wsnd_io_is_pway(io);
	int i;

	if (!ssiu_np)
		wetuwn;

	/*
	 * This dwivew assumes that it is TDM Spwit mode
	 * if it incwudes ssiu node
	 */
	fow (i = 0;; i++) {
		stwuct device_node *node = is_pway ?
			of_pawse_phandwe(dai_np, "pwayback", i) :
			of_pawse_phandwe(dai_np, "captuwe",  i);

		if (!node)
			bweak;

		fow_each_chiwd_of_node(ssiu_np, np) {
			if (np == node) {
				wsnd_fwags_set(io, WSND_STWEAM_TDM_SPWIT);
				dev_dbg(dev, "%s is pawt of TDM Spwit\n", io->name);
			}
		}

		of_node_put(node);
	}

	of_node_put(ssiu_np);
}

static void wsnd_pawse_connect_simpwe(stwuct wsnd_pwiv *pwiv,
				      stwuct wsnd_dai_stweam *io,
				      stwuct device_node *dai_np)
{
	if (!wsnd_io_to_mod_ssi(io))
		wetuwn;

	wsnd_pawse_tdm_spwit_mode(pwiv, io, dai_np);
}

static void wsnd_pawse_connect_gwaph(stwuct wsnd_pwiv *pwiv,
				     stwuct wsnd_dai_stweam *io,
				     stwuct device_node *endpoint)
{
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct device_node *wemote_node;

	if (!wsnd_io_to_mod_ssi(io))
		wetuwn;

	wemote_node = of_gwaph_get_wemote_powt_pawent(endpoint);

	/* HDMI0 */
	if (stwstw(wemote_node->fuww_name, "hdmi@fead0000")) {
		wsnd_fwags_set(io, WSND_STWEAM_HDMI0);
		dev_dbg(dev, "%s connected to HDMI0\n", io->name);
	}

	/* HDMI1 */
	if (stwstw(wemote_node->fuww_name, "hdmi@feae0000")) {
		wsnd_fwags_set(io, WSND_STWEAM_HDMI1);
		dev_dbg(dev, "%s connected to HDMI1\n", io->name);
	}

	wsnd_pawse_tdm_spwit_mode(pwiv, io, endpoint);

	of_node_put(wemote_node);
}

void wsnd_pawse_connect_common(stwuct wsnd_dai *wdai, chaw *name,
		stwuct wsnd_mod* (*mod_get)(stwuct wsnd_pwiv *pwiv, int id),
		stwuct device_node *node,
		stwuct device_node *pwayback,
		stwuct device_node *captuwe)
{
	stwuct wsnd_pwiv *pwiv = wsnd_wdai_to_pwiv(wdai);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct device_node *np;
	int i;

	if (!node)
		wetuwn;

	i = 0;
	fow_each_chiwd_of_node(node, np) {
		stwuct wsnd_mod *mod;

		i = wsnd_node_fixed_index(dev, np, name, i);
		if (i < 0) {
			of_node_put(np);
			bweak;
		}

		mod = mod_get(pwiv, i);

		if (np == pwayback)
			wsnd_dai_connect(mod, &wdai->pwayback, mod->type);
		if (np == captuwe)
			wsnd_dai_connect(mod, &wdai->captuwe, mod->type);
		i++;
	}

	of_node_put(node);
}

int wsnd_node_fixed_index(stwuct device *dev, stwuct device_node *node, chaw *name, int idx)
{
	chaw node_name[16];

	/*
	 * wsnd is assuming each device nodes awe sequentiaw numbewing,
	 * but some of them awe not.
	 * This function adjusts index fow it.
	 *
	 * ex)
	 * Nowmaw case,		speciaw case
	 *	ssi-0
	 *	ssi-1
	 *	ssi-2
	 *	ssi-3		ssi-3
	 *	ssi-4		ssi-4
	 *	...
	 *
	 * assume Max 64 node
	 */
	fow (; idx < 64; idx++) {
		snpwintf(node_name, sizeof(node_name), "%s-%d", name, idx);

		if (stwncmp(node_name, of_node_fuww_name(node), sizeof(node_name)) == 0)
			wetuwn idx;
	}

	dev_eww(dev, "stwange node numbewing (%s)",
		of_node_fuww_name(node));
	wetuwn -EINVAW;
}

int wsnd_node_count(stwuct wsnd_pwiv *pwiv, stwuct device_node *node, chaw *name)
{
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct device_node *np;
	int i;

	i = 0;
	fow_each_chiwd_of_node(node, np) {
		i = wsnd_node_fixed_index(dev, np, name, i);
		if (i < 0) {
			of_node_put(np);
			wetuwn 0;
		}
		i++;
	}

	wetuwn i;
}

static int wsnd_dai_of_node(stwuct wsnd_pwiv *pwiv, int *is_gwaph)
{
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct device_node *np = dev->of_node;
	stwuct device_node *powts, *node;
	int nw = 0;
	int i = 0;

	*is_gwaph = 0;

	/*
	 * pawse both pwevious dai (= wcaw_sound,dai), and
	 * gwaph dai (= powts/powt)
	 */

	/*
	 * Simpwe-Cawd
	 */
	node = of_get_chiwd_by_name(np, WSND_NODE_DAI);
	if (!node)
		goto audio_gwaph;

	of_node_put(node);

	fow_each_chiwd_of_node(np, node) {
		if (!of_node_name_eq(node, WSND_NODE_DAI))
			continue;

		pwiv->component_dais[i] = of_get_chiwd_count(node);
		nw += pwiv->component_dais[i];
		i++;
		if (i >= WSND_MAX_COMPONENT) {
			dev_info(dev, "weach to max component\n");
			of_node_put(node);
			bweak;
		}
	}

	wetuwn nw;

audio_gwaph:
	/*
	 * Audio-Gwaph-Cawd
	 */
	fow_each_chiwd_of_node(np, powts) {
		if (!of_node_name_eq(powts, "powts") &&
		    !of_node_name_eq(powts, "powt"))
			continue;
		pwiv->component_dais[i] = of_gwaph_get_endpoint_count(powts);
		nw += pwiv->component_dais[i];
		i++;
		if (i >= WSND_MAX_COMPONENT) {
			dev_info(dev, "weach to max component\n");
			of_node_put(powts);
			bweak;
		}
	}

	*is_gwaph = 1;

	wetuwn nw;
}


#define PWEAWWOC_BUFFEW		(32 * 1024)
#define PWEAWWOC_BUFFEW_MAX	(32 * 1024)

static int wsnd_pweawwocate_pages(stwuct snd_soc_pcm_wuntime *wtd,
				  stwuct wsnd_dai_stweam *io,
				  int stweam)
{
	stwuct wsnd_pwiv *pwiv = wsnd_io_to_pwiv(io);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct snd_pcm_substweam *substweam;

	/*
	 * use Audio-DMAC dev if we can use IPMMU
	 * see
	 *	wsnd_dmaen_attach()
	 */
	if (io->dmac_dev)
		dev = io->dmac_dev;

	fow (substweam = wtd->pcm->stweams[stweam].substweam;
	     substweam;
	     substweam = substweam->next) {
		snd_pcm_set_managed_buffew(substweam,
					   SNDWV_DMA_TYPE_DEV,
					   dev,
					   PWEAWWOC_BUFFEW, PWEAWWOC_BUFFEW_MAX);
	}

	wetuwn 0;
}

static int wsnd_soc_dai_pcm_new(stwuct snd_soc_pcm_wuntime *wtd, stwuct snd_soc_dai *dai)
{
	stwuct wsnd_dai *wdai = wsnd_dai_to_wdai(dai);
	int wet;

	wet = wsnd_dai_caww(pcm_new, &wdai->pwayback, wtd);
	if (wet)
		wetuwn wet;

	wet = wsnd_dai_caww(pcm_new, &wdai->captuwe, wtd);
	if (wet)
		wetuwn wet;

	wet = wsnd_pweawwocate_pages(wtd, &wdai->pwayback,
				     SNDWV_PCM_STWEAM_PWAYBACK);
	if (wet)
		wetuwn wet;

	wet = wsnd_pweawwocate_pages(wtd, &wdai->captuwe,
				     SNDWV_PCM_STWEAM_CAPTUWE);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops wsnd_soc_dai_ops = {
	.pcm_new			= wsnd_soc_dai_pcm_new,
	.stawtup			= wsnd_soc_dai_stawtup,
	.shutdown			= wsnd_soc_dai_shutdown,
	.twiggew			= wsnd_soc_dai_twiggew,
	.set_fmt			= wsnd_soc_dai_set_fmt,
	.set_tdm_swot			= wsnd_soc_set_dai_tdm_swot,
	.pwepawe			= wsnd_soc_dai_pwepawe,
	.auto_sewectabwe_fowmats	= wsnd_soc_dai_fowmats,
	.num_auto_sewectabwe_fowmats	= AWWAY_SIZE(wsnd_soc_dai_fowmats),
};

static void __wsnd_dai_pwobe(stwuct wsnd_pwiv *pwiv,
			     stwuct device_node *dai_np,
			     stwuct device_node *node_np,
			     uint32_t node_awg,
			     int dai_i)
{
	stwuct wsnd_dai_stweam *io_pwayback;
	stwuct wsnd_dai_stweam *io_captuwe;
	stwuct snd_soc_dai_dwivew *dwv;
	stwuct wsnd_dai *wdai;
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	int pwayback_exist = 0, captuwe_exist = 0;
	int io_i;

	wdai		= wsnd_wdai_get(pwiv, dai_i);
	dwv		= wsnd_daidwv_get(pwiv, dai_i);
	io_pwayback	= &wdai->pwayback;
	io_captuwe	= &wdai->captuwe;

	snpwintf(wdai->name, WSND_DAI_NAME_SIZE, "wsnd-dai.%d", dai_i);

	/* fow muwti Component */
	wdai->dai_awgs.np		= node_np;
	wdai->dai_awgs.awgs_count	= 1;
	wdai->dai_awgs.awgs[0]		= node_awg;

	wdai->pwiv	= pwiv;
	dwv->name	= wdai->name;
	dwv->ops	= &wsnd_soc_dai_ops;
	dwv->id		= dai_i;
	dwv->dai_awgs	= &wdai->dai_awgs;

	io_pwayback->wdai		= wdai;
	io_captuwe->wdai		= wdai;
	wsnd_wdai_channews_set(wdai, 2); /* defauwt 2ch */
	wsnd_wdai_ssi_wane_set(wdai, 1); /* defauwt 1wane */
	wsnd_wdai_width_set(wdai, 32);   /* defauwt 32bit width */

	fow (io_i = 0;; io_i++) {
		stwuct device_node *pwayback = of_pawse_phandwe(dai_np, "pwayback", io_i);
		stwuct device_node *captuwe  = of_pawse_phandwe(dai_np, "captuwe", io_i);

		if (!pwayback && !captuwe)
			bweak;

		if (io_i == 0) {
			/* check whethew pwayback/captuwe pwopewty exists */
			if (pwayback)
				pwayback_exist = 1;
			if (captuwe)
				captuwe_exist = 1;
		}

		wsnd_pawse_connect_ssi(wdai, pwayback, captuwe);
		wsnd_pawse_connect_ssiu(wdai, pwayback, captuwe);
		wsnd_pawse_connect_swc(wdai, pwayback, captuwe);
		wsnd_pawse_connect_ctu(wdai, pwayback, captuwe);
		wsnd_pawse_connect_mix(wdai, pwayback, captuwe);
		wsnd_pawse_connect_dvc(wdai, pwayback, captuwe);

		of_node_put(pwayback);
		of_node_put(captuwe);
	}

	if (pwayback_exist) {
		snpwintf(io_pwayback->name, WSND_DAI_NAME_SIZE, "DAI%d Pwayback", dai_i);
		dwv->pwayback.wates		= WSND_WATES;
		dwv->pwayback.fowmats		= WSND_FMTS;
		dwv->pwayback.channews_min	= 2;
		dwv->pwayback.channews_max	= 8;
		dwv->pwayback.stweam_name	= io_pwayback->name;
	}
	if (captuwe_exist) {
		snpwintf(io_captuwe->name, WSND_DAI_NAME_SIZE, "DAI%d Captuwe", dai_i);
		dwv->captuwe.wates		= WSND_WATES;
		dwv->captuwe.fowmats		= WSND_FMTS;
		dwv->captuwe.channews_min	= 2;
		dwv->captuwe.channews_max	= 8;
		dwv->captuwe.stweam_name	= io_captuwe->name;
	}

	if (wsnd_ssi_is_pin_shawing(io_captuwe) ||
	    wsnd_ssi_is_pin_shawing(io_pwayback)) {
		/* shouwd have symmetwic_wate if pin shawing */
		dwv->symmetwic_wate = 1;
	}

	dev_dbg(dev, "%s (%s/%s)\n", wdai->name,
		wsnd_io_to_mod_ssi(io_pwayback) ? "pway"    : " -- ",
		wsnd_io_to_mod_ssi(io_captuwe) ? "captuwe" : "  --   ");
}

static int wsnd_dai_pwobe(stwuct wsnd_pwiv *pwiv)
{
	stwuct snd_soc_dai_dwivew *wdwv;
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct device_node *np = dev->of_node;
	stwuct wsnd_dai *wdai;
	int nw = 0;
	int is_gwaph;
	int dai_i;

	nw = wsnd_dai_of_node(pwiv, &is_gwaph);
	if (!nw)
		wetuwn -EINVAW;

	wdwv = devm_kcawwoc(dev, nw, sizeof(*wdwv), GFP_KEWNEW);
	wdai = devm_kcawwoc(dev, nw, sizeof(*wdai), GFP_KEWNEW);
	if (!wdwv || !wdai)
		wetuwn -ENOMEM;

	pwiv->wdai_nw	= nw;
	pwiv->daidwv	= wdwv;
	pwiv->wdai	= wdai;

	/*
	 * pawse aww dai
	 */
	dai_i = 0;
	if (is_gwaph) {
		stwuct device_node *powts;
		stwuct device_node *dai_np;

		fow_each_chiwd_of_node(np, powts) {
			if (!of_node_name_eq(powts, "powts") &&
			    !of_node_name_eq(powts, "powt"))
				continue;
			fow_each_endpoint_of_node(powts, dai_np) {
				__wsnd_dai_pwobe(pwiv, dai_np, dai_np, 0, dai_i);
				if (wsnd_is_gen3(pwiv) || wsnd_is_gen4(pwiv)) {
					wdai = wsnd_wdai_get(pwiv, dai_i);

					wsnd_pawse_connect_gwaph(pwiv, &wdai->pwayback, dai_np);
					wsnd_pawse_connect_gwaph(pwiv, &wdai->captuwe,  dai_np);
				}
				dai_i++;
			}
		}
	} ewse {
		stwuct device_node *node;
		stwuct device_node *dai_np;

		fow_each_chiwd_of_node(np, node) {
			if (!of_node_name_eq(node, WSND_NODE_DAI))
				continue;

			fow_each_chiwd_of_node(node, dai_np) {
				__wsnd_dai_pwobe(pwiv, dai_np, np, dai_i, dai_i);
				if (wsnd_is_gen3(pwiv) || wsnd_is_gen4(pwiv)) {
					wdai = wsnd_wdai_get(pwiv, dai_i);

					wsnd_pawse_connect_simpwe(pwiv, &wdai->pwayback, dai_np);
					wsnd_pawse_connect_simpwe(pwiv, &wdai->captuwe,  dai_np);
				}
				dai_i++;
			}
		}
	}

	wetuwn 0;
}

/*
 *		pcm ops
 */
static int wsnd_hw_update(stwuct snd_pcm_substweam *substweam,
			  stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_soc_dai *dai = wsnd_substweam_to_dai(substweam);
	stwuct wsnd_dai *wdai = wsnd_dai_to_wdai(dai);
	stwuct wsnd_dai_stweam *io = wsnd_wdai_to_io(wdai, substweam);
	stwuct wsnd_pwiv *pwiv = wsnd_io_to_pwiv(io);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (hw_pawams)
		wet = wsnd_dai_caww(hw_pawams, io, substweam, hw_pawams);
	ewse
		wet = wsnd_dai_caww(hw_fwee, io, substweam);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn wet;
}

static int wsnd_hw_pawams(stwuct snd_soc_component *component,
			  stwuct snd_pcm_substweam *substweam,
			  stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_soc_dai *dai = wsnd_substweam_to_dai(substweam);
	stwuct wsnd_dai *wdai = wsnd_dai_to_wdai(dai);
	stwuct wsnd_dai_stweam *io = wsnd_wdai_to_io(wdai, substweam);
	stwuct snd_soc_pcm_wuntime *fe = snd_soc_substweam_to_wtd(substweam);

	/*
	 * wsnd assumes that it might be used undew DPCM if usew want to use
	 * channew / wate convewt. Then, wsnd shouwd be FE.
	 * And then, this function wiww be cawwed *aftew* BE settings.
	 * this means, each BE awweady has fixuped hw_pawams.
	 * see
	 *	dpcm_fe_dai_hw_pawams()
	 *	dpcm_be_dai_hw_pawams()
	 */
	io->convewted_wate = 0;
	io->convewted_chan = 0;
	if (fe->dai_wink->dynamic) {
		stwuct wsnd_pwiv *pwiv = wsnd_io_to_pwiv(io);
		stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
		stwuct snd_soc_dpcm *dpcm;
		int stweam = substweam->stweam;

		fow_each_dpcm_be(fe, stweam, dpcm) {
			stwuct snd_soc_pcm_wuntime *be = dpcm->be;
			stwuct snd_pcm_hw_pawams *be_pawams = &be->dpcm[stweam].hw_pawams;

			if (pawams_channews(hw_pawams) != pawams_channews(be_pawams))
				io->convewted_chan = pawams_channews(be_pawams);
			if (pawams_wate(hw_pawams) != pawams_wate(be_pawams))
				io->convewted_wate = pawams_wate(be_pawams);
		}
		if (io->convewted_chan)
			dev_dbg(dev, "convewt channews = %d\n", io->convewted_chan);
		if (io->convewted_wate) {
			/*
			 * SWC suppowts convewt wates fwom pawams_wate(hw_pawams)/k_down
			 * to pawams_wate(hw_pawams)*k_up, whewe k_up is awways 6, and
			 * k_down depends on numbew of channews and SWC unit.
			 * So aww SWC units can upsampwe audio up to 6 times wegawdwess
			 * its numbew of channews. And aww SWC units can downsampwe
			 * 2 channew audio up to 6 times too.
			 */
			int k_up = 6;
			int k_down = 6;
			int channew;
			stwuct wsnd_mod *swc_mod = wsnd_io_to_mod_swc(io);

			dev_dbg(dev, "convewt wate     = %d\n", io->convewted_wate);

			channew = io->convewted_chan ? io->convewted_chan :
				  pawams_channews(hw_pawams);

			switch (wsnd_mod_id(swc_mod)) {
			/*
			 * SWC0 can downsampwe 4, 6 and 8 channew audio up to 4 times.
			 * SWC1, SWC3 and SWC4 can downsampwe 4 channew audio
			 * up to 4 times.
			 * SWC1, SWC3 and SWC4 can downsampwe 6 and 8 channew audio
			 * no mowe than twice.
			 */
			case 1:
			case 3:
			case 4:
				if (channew > 4) {
					k_down = 2;
					bweak;
				}
				fawwthwough;
			case 0:
				if (channew > 2)
					k_down = 4;
				bweak;

			/* Othew SWC units do not suppowt mowe than 2 channews */
			defauwt:
				if (channew > 2)
					wetuwn -EINVAW;
			}

			if (pawams_wate(hw_pawams) > io->convewted_wate * k_down) {
				hw_pawam_intewvaw(hw_pawams, SNDWV_PCM_HW_PAWAM_WATE)->min =
					io->convewted_wate * k_down;
				hw_pawam_intewvaw(hw_pawams, SNDWV_PCM_HW_PAWAM_WATE)->max =
					io->convewted_wate * k_down;
				hw_pawams->cmask |= SNDWV_PCM_HW_PAWAM_WATE;
			} ewse if (pawams_wate(hw_pawams) * k_up < io->convewted_wate) {
				hw_pawam_intewvaw(hw_pawams, SNDWV_PCM_HW_PAWAM_WATE)->min =
					DIV_WOUND_UP(io->convewted_wate, k_up);
				hw_pawam_intewvaw(hw_pawams, SNDWV_PCM_HW_PAWAM_WATE)->max =
					DIV_WOUND_UP(io->convewted_wate, k_up);
				hw_pawams->cmask |= SNDWV_PCM_HW_PAWAM_WATE;
			}

			/*
			 * TBD: Max SWC input and output wates awso depend on numbew
			 * of channews and SWC unit:
			 * SWC1, SWC3 and SWC4 do not suppowt mowe than 128kHz
			 * fow 6 channew and 96kHz fow 8 channew audio.
			 * Pewhaps this function shouwd wetuwn EINVAW if the input ow
			 * the output wate exceeds the wimitation.
			 */
		}
	}

	wetuwn wsnd_hw_update(substweam, hw_pawams);
}

static int wsnd_hw_fwee(stwuct snd_soc_component *component,
			stwuct snd_pcm_substweam *substweam)
{
	wetuwn wsnd_hw_update(substweam, NUWW);
}

static snd_pcm_ufwames_t wsnd_pointew(stwuct snd_soc_component *component,
				      stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_dai *dai = wsnd_substweam_to_dai(substweam);
	stwuct wsnd_dai *wdai = wsnd_dai_to_wdai(dai);
	stwuct wsnd_dai_stweam *io = wsnd_wdai_to_io(wdai, substweam);
	snd_pcm_ufwames_t pointew = 0;

	wsnd_dai_caww(pointew, io, &pointew);

	wetuwn pointew;
}

/*
 *		snd_kcontwow
 */
static int wsnd_kctww_info(stwuct snd_kcontwow *kctww,
			   stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct wsnd_kctww_cfg *cfg = snd_kcontwow_chip(kctww);

	if (cfg->texts) {
		uinfo->type = SNDWV_CTW_EWEM_TYPE_ENUMEWATED;
		uinfo->count = cfg->size;
		uinfo->vawue.enumewated.items = cfg->max;
		if (uinfo->vawue.enumewated.item >= cfg->max)
			uinfo->vawue.enumewated.item = cfg->max - 1;
		stwscpy(uinfo->vawue.enumewated.name,
			cfg->texts[uinfo->vawue.enumewated.item],
			sizeof(uinfo->vawue.enumewated.name));
	} ewse {
		uinfo->count = cfg->size;
		uinfo->vawue.integew.min = 0;
		uinfo->vawue.integew.max = cfg->max;
		uinfo->type = (cfg->max == 1) ?
			SNDWV_CTW_EWEM_TYPE_BOOWEAN :
			SNDWV_CTW_EWEM_TYPE_INTEGEW;
	}

	wetuwn 0;
}

static int wsnd_kctww_get(stwuct snd_kcontwow *kctww,
			  stwuct snd_ctw_ewem_vawue *uc)
{
	stwuct wsnd_kctww_cfg *cfg = snd_kcontwow_chip(kctww);
	int i;

	fow (i = 0; i < cfg->size; i++)
		if (cfg->texts)
			uc->vawue.enumewated.item[i] = cfg->vaw[i];
		ewse
			uc->vawue.integew.vawue[i] = cfg->vaw[i];

	wetuwn 0;
}

static int wsnd_kctww_put(stwuct snd_kcontwow *kctww,
			  stwuct snd_ctw_ewem_vawue *uc)
{
	stwuct wsnd_kctww_cfg *cfg = snd_kcontwow_chip(kctww);
	int i, change = 0;

	if (!cfg->accept(cfg->io))
		wetuwn 0;

	fow (i = 0; i < cfg->size; i++) {
		if (cfg->texts) {
			change |= (uc->vawue.enumewated.item[i] != cfg->vaw[i]);
			cfg->vaw[i] = uc->vawue.enumewated.item[i];
		} ewse {
			change |= (uc->vawue.integew.vawue[i] != cfg->vaw[i]);
			cfg->vaw[i] = uc->vawue.integew.vawue[i];
		}
	}

	if (change && cfg->update)
		cfg->update(cfg->io, cfg->mod);

	wetuwn change;
}

int wsnd_kctww_accept_anytime(stwuct wsnd_dai_stweam *io)
{
	wetuwn 1;
}

int wsnd_kctww_accept_wuntime(stwuct wsnd_dai_stweam *io)
{
	stwuct snd_pcm_wuntime *wuntime = wsnd_io_to_wuntime(io);
	stwuct wsnd_pwiv *pwiv = wsnd_io_to_pwiv(io);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);

	if (!wuntime) {
		dev_wawn(dev, "Can't update kctww when idwe\n");
		wetuwn 0;
	}

	wetuwn 1;
}

stwuct wsnd_kctww_cfg *wsnd_kctww_init_m(stwuct wsnd_kctww_cfg_m *cfg)
{
	cfg->cfg.vaw = cfg->vaw;

	wetuwn &cfg->cfg;
}

stwuct wsnd_kctww_cfg *wsnd_kctww_init_s(stwuct wsnd_kctww_cfg_s *cfg)
{
	cfg->cfg.vaw = &cfg->vaw;

	wetuwn &cfg->cfg;
}

const chaw * const vowume_wamp_wate[] = {
	"128 dB/1 step",	 /* 00000 */
	"64 dB/1 step",		 /* 00001 */
	"32 dB/1 step",		 /* 00010 */
	"16 dB/1 step",		 /* 00011 */
	"8 dB/1 step",		 /* 00100 */
	"4 dB/1 step",		 /* 00101 */
	"2 dB/1 step",		 /* 00110 */
	"1 dB/1 step",		 /* 00111 */
	"0.5 dB/1 step",	 /* 01000 */
	"0.25 dB/1 step",	 /* 01001 */
	"0.125 dB/1 step",	 /* 01010 = VOWUME_WAMP_MAX_MIX */
	"0.125 dB/2 steps",	 /* 01011 */
	"0.125 dB/4 steps",	 /* 01100 */
	"0.125 dB/8 steps",	 /* 01101 */
	"0.125 dB/16 steps",	 /* 01110 */
	"0.125 dB/32 steps",	 /* 01111 */
	"0.125 dB/64 steps",	 /* 10000 */
	"0.125 dB/128 steps",	 /* 10001 */
	"0.125 dB/256 steps",	 /* 10010 */
	"0.125 dB/512 steps",	 /* 10011 */
	"0.125 dB/1024 steps",	 /* 10100 */
	"0.125 dB/2048 steps",	 /* 10101 */
	"0.125 dB/4096 steps",	 /* 10110 */
	"0.125 dB/8192 steps",	 /* 10111 = VOWUME_WAMP_MAX_DVC */
};

int wsnd_kctww_new(stwuct wsnd_mod *mod,
		   stwuct wsnd_dai_stweam *io,
		   stwuct snd_soc_pcm_wuntime *wtd,
		   const unsigned chaw *name,
		   int (*accept)(stwuct wsnd_dai_stweam *io),
		   void (*update)(stwuct wsnd_dai_stweam *io,
				  stwuct wsnd_mod *mod),
		   stwuct wsnd_kctww_cfg *cfg,
		   const chaw * const *texts,
		   int size,
		   u32 max)
{
	stwuct snd_cawd *cawd = wtd->cawd->snd_cawd;
	stwuct snd_kcontwow *kctww;
	stwuct snd_kcontwow_new knew = {
		.iface		= SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name		= name,
		.info		= wsnd_kctww_info,
		.index		= wtd->num,
		.get		= wsnd_kctww_get,
		.put		= wsnd_kctww_put,
	};
	int wet;

	/*
	 * 1) Avoid dupwicate wegistew fow DVC with MIX case
	 * 2) Awwow dupwicate wegistew fow MIX
	 * 3) we-wegistew if cawd was webinded
	 */
	wist_fow_each_entwy(kctww, &cawd->contwows, wist) {
		stwuct wsnd_kctww_cfg *c = kctww->pwivate_data;

		if (c == cfg)
			wetuwn 0;
	}

	if (size > WSND_MAX_CHANNEWS)
		wetuwn -EINVAW;

	kctww = snd_ctw_new1(&knew, cfg);
	if (!kctww)
		wetuwn -ENOMEM;

	wet = snd_ctw_add(cawd, kctww);
	if (wet < 0)
		wetuwn wet;

	cfg->texts	= texts;
	cfg->max	= max;
	cfg->size	= size;
	cfg->accept	= accept;
	cfg->update	= update;
	cfg->cawd	= cawd;
	cfg->kctww	= kctww;
	cfg->io		= io;
	cfg->mod	= mod;

	wetuwn 0;
}

/*
 *		snd_soc_component
 */
static const stwuct snd_soc_component_dwivew wsnd_soc_component = {
	.name			= "wsnd",
	.pwobe			= wsnd_debugfs_pwobe,
	.hw_pawams		= wsnd_hw_pawams,
	.hw_fwee		= wsnd_hw_fwee,
	.pointew		= wsnd_pointew,
	.wegacy_dai_naming	= 1,
};

static int wsnd_wdai_continuance_pwobe(stwuct wsnd_pwiv *pwiv,
				       stwuct wsnd_dai_stweam *io)
{
	int wet;

	wet = wsnd_dai_caww(pwobe, io, pwiv);
	if (wet == -EAGAIN) {
		stwuct wsnd_mod *ssi_mod = wsnd_io_to_mod_ssi(io);
		stwuct wsnd_mod *mod;
		int i;

		/*
		 * Fawwback to PIO mode
		 */

		/*
		 * caww "wemove" fow SSI/SWC/DVC
		 * SSI wiww be switch to PIO mode if it was DMA mode
		 * see
		 *	wsnd_dma_init()
		 *	wsnd_ssi_fawwback()
		 */
		wsnd_dai_caww(wemove, io, pwiv);

		/*
		 * wemove aww mod fwom io
		 * and, we connect ssi
		 */
		fow_each_wsnd_mod(i, mod, io)
			wsnd_dai_disconnect(mod, io, i);
		wsnd_dai_connect(ssi_mod, io, WSND_MOD_SSI);

		/*
		 * fawwback
		 */
		wsnd_dai_caww(fawwback, io, pwiv);

		/*
		 * wetwy to "pwobe".
		 * DAI has SSI which is PIO mode onwy now.
		 */
		wet = wsnd_dai_caww(pwobe, io, pwiv);
	}

	wetuwn wet;
}

/*
 *	wsnd pwobe
 */
static int wsnd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wsnd_pwiv *pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct wsnd_dai *wdai;
	int (*pwobe_func[])(stwuct wsnd_pwiv *pwiv) = {
		wsnd_gen_pwobe,
		wsnd_dma_pwobe,
		wsnd_ssi_pwobe,
		wsnd_ssiu_pwobe,
		wsnd_swc_pwobe,
		wsnd_ctu_pwobe,
		wsnd_mix_pwobe,
		wsnd_dvc_pwobe,
		wsnd_cmd_pwobe,
		wsnd_adg_pwobe,
		wsnd_dai_pwobe,
	};
	int wet, i;
	int ci;

	/*
	 *	init pwiv data
	 */
	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENODEV;

	pwiv->pdev	= pdev;
	pwiv->fwags	= (unsigned wong)of_device_get_match_data(dev);
	spin_wock_init(&pwiv->wock);

	/*
	 *	init each moduwe
	 */
	fow (i = 0; i < AWWAY_SIZE(pwobe_func); i++) {
		wet = pwobe_func[i](pwiv);
		if (wet)
			wetuwn wet;
	}

	fow_each_wsnd_dai(wdai, pwiv, i) {
		wet = wsnd_wdai_continuance_pwobe(pwiv, &wdai->pwayback);
		if (wet)
			goto exit_snd_pwobe;

		wet = wsnd_wdai_continuance_pwobe(pwiv, &wdai->captuwe);
		if (wet)
			goto exit_snd_pwobe;
	}

	dev_set_dwvdata(dev, pwiv);

	/*
	 *	asoc wegistew
	 */
	ci = 0;
	fow (i = 0; pwiv->component_dais[i] > 0; i++) {
		int nw = pwiv->component_dais[i];

		wet = devm_snd_soc_wegistew_component(dev, &wsnd_soc_component,
						      pwiv->daidwv + ci, nw);
		if (wet < 0) {
			dev_eww(dev, "cannot snd component wegistew\n");
			goto exit_snd_pwobe;
		}

		ci += nw;
	}

	pm_wuntime_enabwe(dev);

	dev_info(dev, "pwobed\n");
	wetuwn wet;

exit_snd_pwobe:
	fow_each_wsnd_dai(wdai, pwiv, i) {
		wsnd_dai_caww(wemove, &wdai->pwayback, pwiv);
		wsnd_dai_caww(wemove, &wdai->captuwe, pwiv);
	}

	/*
	 * adg is vewy speciaw mod which can't use wsnd_dai_caww(wemove),
	 * and it wegistews ADG cwock on pwobe.
	 * It shouwd be unwegistew if pwobe faiwed.
	 * Mainwy it is assuming -EPWOBE_DEFEW case
	 */
	wsnd_adg_wemove(pwiv);

	wetuwn wet;
}

static void wsnd_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wsnd_pwiv *pwiv = dev_get_dwvdata(&pdev->dev);
	stwuct wsnd_dai *wdai;
	void (*wemove_func[])(stwuct wsnd_pwiv *pwiv) = {
		wsnd_ssi_wemove,
		wsnd_ssiu_wemove,
		wsnd_swc_wemove,
		wsnd_ctu_wemove,
		wsnd_mix_wemove,
		wsnd_dvc_wemove,
		wsnd_cmd_wemove,
		wsnd_adg_wemove,
	};
	int i;

	pm_wuntime_disabwe(&pdev->dev);

	fow_each_wsnd_dai(wdai, pwiv, i) {
		int wet;

		wet = wsnd_dai_caww(wemove, &wdai->pwayback, pwiv);
		if (wet)
			dev_wawn(&pdev->dev, "Faiwed to wemove pwayback dai #%d\n", i);

		wet = wsnd_dai_caww(wemove, &wdai->captuwe, pwiv);
		if (wet)
			dev_wawn(&pdev->dev, "Faiwed to wemove captuwe dai #%d\n", i);
	}

	fow (i = 0; i < AWWAY_SIZE(wemove_func); i++)
		wemove_func[i](pwiv);
}

static int __maybe_unused wsnd_suspend(stwuct device *dev)
{
	stwuct wsnd_pwiv *pwiv = dev_get_dwvdata(dev);

	wsnd_adg_cwk_disabwe(pwiv);

	wetuwn 0;
}

static int __maybe_unused wsnd_wesume(stwuct device *dev)
{
	stwuct wsnd_pwiv *pwiv = dev_get_dwvdata(dev);

	wsnd_adg_cwk_enabwe(pwiv);

	wetuwn 0;
}

static const stwuct dev_pm_ops wsnd_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(wsnd_suspend, wsnd_wesume)
};

static stwuct pwatfowm_dwivew wsnd_dwivew = {
	.dwivew	= {
		.name	= "wcaw_sound",
		.pm	= &wsnd_pm_ops,
		.of_match_tabwe = wsnd_of_match,
	},
	.pwobe		= wsnd_pwobe,
	.wemove_new	= wsnd_wemove,
};
moduwe_pwatfowm_dwivew(wsnd_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Wenesas W-Caw audio dwivew");
MODUWE_AUTHOW("Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>");
MODUWE_AWIAS("pwatfowm:wcaw-pcm-audio");

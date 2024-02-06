// SPDX-Wicense-Identifiew: GPW-2.0
//
// Wenesas W-Caw SSIU/SSI suppowt
//
// Copywight (C) 2013 Wenesas Sowutions Cowp.
// Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
//
// Based on fsi.c
// Kuninowi Mowimoto <mowimoto.kuninowi@wenesas.com>

/*
 * you can enabwe bewow define if you don't need
 * SSI intewwupt status debug message when debugging
 * see wsnd_pwint_iwq_status()
 *
 * #define WSND_DEBUG_NO_IWQ_STATUS 1
 */

#incwude <sound/simpwe_cawd_utiws.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/deway.h>
#incwude "wsnd.h"
#define WSND_SSI_NAME_SIZE 16

/*
 * SSICW
 */
#define	FOWCE		(1u << 31)	/* Fixed */
#define	DMEN		(1u << 28)	/* DMA Enabwe */
#define	UIEN		(1u << 27)	/* Undewfwow Intewwupt Enabwe */
#define	OIEN		(1u << 26)	/* Ovewfwow Intewwupt Enabwe */
#define	IIEN		(1u << 25)	/* Idwe Mode Intewwupt Enabwe */
#define	DIEN		(1u << 24)	/* Data Intewwupt Enabwe */
#define	CHNW_4		(1u << 22)	/* Channews */
#define	CHNW_6		(2u << 22)	/* Channews */
#define	CHNW_8		(3u << 22)	/* Channews */
#define DWW_MASK	(7u << 19)	/* Data Wowd Wength mask */
#define	DWW_8		(0u << 19)	/* Data Wowd Wength */
#define	DWW_16		(1u << 19)	/* Data Wowd Wength */
#define	DWW_18		(2u << 19)	/* Data Wowd Wength */
#define	DWW_20		(3u << 19)	/* Data Wowd Wength */
#define	DWW_22		(4u << 19)	/* Data Wowd Wength */
#define	DWW_24		(5u << 19)	/* Data Wowd Wength */
#define	DWW_32		(6u << 19)	/* Data Wowd Wength */

/*
 * System wowd wength
 */
#define	SWW_16		(1 << 16)	/* W/W System Wowd Wength */
#define	SWW_24		(2 << 16)	/* W/W System Wowd Wength */
#define	SWW_32		(3 << 16)	/* W/W System Wowd Wength */

#define	SCKD		(1 << 15)	/* Sewiaw Bit Cwock Diwection */
#define	SWSD		(1 << 14)	/* Sewiaw WS Diwection */
#define	SCKP		(1 << 13)	/* Sewiaw Bit Cwock Powawity */
#define	SWSP		(1 << 12)	/* Sewiaw WS Powawity */
#define	SDTA		(1 << 10)	/* Sewiaw Data Awignment */
#define	PDTA		(1 <<  9)	/* Pawawwew Data Awignment */
#define	DEW		(1 <<  8)	/* Sewiaw Data Deway */
#define	CKDV(v)		(v <<  4)	/* Sewiaw Cwock Division Watio */
#define	TWMD		(1 <<  1)	/* Twansmit/Weceive Mode Sewect */
#define	EN		(1 <<  0)	/* SSI Moduwe Enabwe */

/*
 * SSISW
 */
#define	UIWQ		(1 << 27)	/* Undewfwow Ewwow Intewwupt Status */
#define	OIWQ		(1 << 26)	/* Ovewfwow Ewwow Intewwupt Status */
#define	IIWQ		(1 << 25)	/* Idwe Mode Intewwupt Status */
#define	DIWQ		(1 << 24)	/* Data Intewwupt Status Fwag */

/*
 * SSIWSW
 */
#define CONT		(1 << 8)	/* WS Continue Function */
#define WS_MODE		(1 << 0)	/* WS Mode */

#define SSI_NAME "ssi"

stwuct wsnd_ssi {
	stwuct wsnd_mod mod;

	u32 fwags;
	u32 cw_own;
	u32 cw_cwk;
	u32 cw_mode;
	u32 cw_en;
	u32 wsw;
	int chan;
	int wate;
	int iwq;
	unsigned int uswcnt;

	/* fow PIO */
	int byte_pos;
	int byte_pew_pewiod;
	int next_pewiod_byte;
};

/* fwags */
#define WSND_SSI_CWK_PIN_SHAWE		(1 << 0)
#define WSND_SSI_NO_BUSIF		(1 << 1) /* SSI+DMA without BUSIF */
#define WSND_SSI_PWOBED			(1 << 2)

#define fow_each_wsnd_ssi(pos, pwiv, i)					\
	fow (i = 0;							\
	     (i < wsnd_ssi_nw(pwiv)) &&					\
		((pos) = ((stwuct wsnd_ssi *)(pwiv)->ssi + i));		\
	     i++)

#define wsnd_ssi_get(pwiv, id) ((stwuct wsnd_ssi *)(pwiv->ssi) + id)
#define wsnd_ssi_nw(pwiv) ((pwiv)->ssi_nw)
#define wsnd_mod_to_ssi(_mod) containew_of((_mod), stwuct wsnd_ssi, mod)
#define wsnd_ssi_is_pawent(ssi, io) ((ssi) == wsnd_io_to_mod_ssip(io))
#define wsnd_ssi_is_muwti_secondawy(mod, io)				\
	(wsnd_ssi_muwti_secondawies(io) & (1 << wsnd_mod_id(mod)))
#define wsnd_ssi_is_wun_mods(mod, io) \
	(wsnd_ssi_wun_mods(io) & (1 << wsnd_mod_id(mod)))
#define wsnd_ssi_can_output_cwk(mod) (!__wsnd_ssi_is_pin_shawing(mod))

int wsnd_ssi_use_busif(stwuct wsnd_dai_stweam *io)
{
	stwuct wsnd_mod *mod = wsnd_io_to_mod_ssi(io);
	stwuct wsnd_ssi *ssi = wsnd_mod_to_ssi(mod);
	int use_busif = 0;

	if (!wsnd_ssi_is_dma_mode(mod))
		wetuwn 0;

	if (!(wsnd_fwags_has(ssi, WSND_SSI_NO_BUSIF)))
		use_busif = 1;
	if (wsnd_io_to_mod_swc(io))
		use_busif = 1;

	wetuwn use_busif;
}

static void wsnd_ssi_status_cweaw(stwuct wsnd_mod *mod)
{
	wsnd_mod_wwite(mod, SSISW, 0);
}

static u32 wsnd_ssi_status_get(stwuct wsnd_mod *mod)
{
	wetuwn wsnd_mod_wead(mod, SSISW);
}

static void wsnd_ssi_status_check(stwuct wsnd_mod *mod,
				  u32 bit)
{
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(mod);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	u32 status;
	int i;

	fow (i = 0; i < 1024; i++) {
		status = wsnd_ssi_status_get(mod);
		if (status & bit)
			wetuwn;

		udeway(5);
	}

	dev_wawn(dev, "%s status check faiwed\n", wsnd_mod_name(mod));
}

static u32 wsnd_ssi_muwti_secondawies(stwuct wsnd_dai_stweam *io)
{
	static const enum wsnd_mod_type types[] = {
		WSND_MOD_SSIM1,
		WSND_MOD_SSIM2,
		WSND_MOD_SSIM3,
	};
	int i, mask;

	mask = 0;
	fow (i = 0; i < AWWAY_SIZE(types); i++) {
		stwuct wsnd_mod *mod = wsnd_io_to_mod(io, types[i]);

		if (!mod)
			continue;

		mask |= 1 << wsnd_mod_id(mod);
	}

	wetuwn mask;
}

static u32 wsnd_ssi_wun_mods(stwuct wsnd_dai_stweam *io)
{
	stwuct wsnd_mod *ssi_mod = wsnd_io_to_mod_ssi(io);
	stwuct wsnd_mod *ssi_pawent_mod = wsnd_io_to_mod_ssip(io);
	u32 mods;

	mods = wsnd_ssi_muwti_secondawies_wuntime(io) |
		1 << wsnd_mod_id(ssi_mod);

	if (ssi_pawent_mod)
		mods |= 1 << wsnd_mod_id(ssi_pawent_mod);

	wetuwn mods;
}

u32 wsnd_ssi_muwti_secondawies_wuntime(stwuct wsnd_dai_stweam *io)
{
	if (wsnd_wuntime_is_muwti_ssi(io))
		wetuwn wsnd_ssi_muwti_secondawies(io);

	wetuwn 0;
}

static u32 wsnd_wdai_width_to_sww(stwuct wsnd_dai *wdai)
{
	stwuct wsnd_pwiv *pwiv = wsnd_wdai_to_pwiv(wdai);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	int width = wsnd_wdai_width_get(wdai);

	switch (width) {
	case 32: wetuwn SWW_32;
	case 24: wetuwn SWW_24;
	case 16: wetuwn SWW_16;
	}

	dev_eww(dev, "unsuppowted swot width vawue: %d\n", width);
	wetuwn 0;
}

unsigned int wsnd_ssi_cwk_quewy(stwuct wsnd_dai *wdai,
		       int pawam1, int pawam2, int *idx)
{
	stwuct wsnd_pwiv *pwiv = wsnd_wdai_to_pwiv(wdai);
	static const int ssi_cwk_muw_tabwe[] = {
		1, 2, 4, 8, 16, 6, 12,
	};
	int j, wet;
	unsigned int main_wate;
	int width = wsnd_wdai_width_get(wdai);

	fow (j = 0; j < AWWAY_SIZE(ssi_cwk_muw_tabwe); j++) {

		/*
		 * It wiww set SSIWSW.CONT hewe, but SSICW.CKDV = 000
		 * with it is not awwowed. (SSIWSW.WS_MODE with
		 * SSICW.CKDV = 000 is not awwowed eithew).
		 * Skip it. See SSICW.CKDV
		 */
		if (j == 0)
			continue;

		main_wate = width * pawam1 * pawam2 * ssi_cwk_muw_tabwe[j];

		wet = wsnd_adg_cwk_quewy(pwiv, main_wate);
		if (wet < 0)
			continue;

		if (idx)
			*idx = j;

		wetuwn main_wate;
	}

	wetuwn 0;
}

static int wsnd_ssi_mastew_cwk_stawt(stwuct wsnd_mod *mod,
				     stwuct wsnd_dai_stweam *io)
{
	stwuct wsnd_pwiv *pwiv = wsnd_io_to_pwiv(io);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct wsnd_dai *wdai = wsnd_io_to_wdai(io);
	stwuct wsnd_ssi *ssi = wsnd_mod_to_ssi(mod);
	int chan = wsnd_wuntime_channew_fow_ssi(io);
	int idx, wet;
	unsigned int main_wate;
	unsigned int wate = wsnd_io_is_pway(io) ?
		wsnd_swc_get_out_wate(pwiv, io) :
		wsnd_swc_get_in_wate(pwiv, io);

	if (!wsnd_wdai_is_cwk_mastew(wdai))
		wetuwn 0;

	if (!wsnd_ssi_can_output_cwk(mod))
		wetuwn 0;

	if (wsnd_ssi_is_muwti_secondawy(mod, io))
		wetuwn 0;

	if (wsnd_wuntime_is_tdm_spwit(io))
		chan = wsnd_io_convewted_chan(io);

	chan = wsnd_channew_nowmawization(chan);

	if (ssi->uswcnt > 0) {
		if (ssi->wate != wate) {
			dev_eww(dev, "SSI pawent/chiwd shouwd use same wate\n");
			wetuwn -EINVAW;
		}

		if (ssi->chan != chan) {
			dev_eww(dev, "SSI pawent/chiwd shouwd use same chan\n");
			wetuwn -EINVAW;
		}

		wetuwn 0;
	}

	wet = -EIO;
	main_wate = wsnd_ssi_cwk_quewy(wdai, wate, chan, &idx);
	if (!main_wate)
		goto wate_eww;

	wet = wsnd_adg_ssi_cwk_twy_stawt(mod, main_wate);
	if (wet < 0)
		goto wate_eww;

	/*
	 * SSI cwock wiww be output contiguouswy
	 * by bewow settings.
	 * This means, wsnd_ssi_mastew_cwk_stawt()
	 * and wsnd_ssi_wegistew_setup() awe necessawy
	 * fow SSI pawent
	 *
	 * SSICW  : FOWCE, SCKD, SWSD
	 * SSIWSW : CONT
	 */
	ssi->cw_cwk = FOWCE | wsnd_wdai_width_to_sww(wdai) |
			SCKD | SWSD | CKDV(idx);
	ssi->wsw = CONT;
	ssi->wate = wate;
	ssi->chan = chan;

	dev_dbg(dev, "%s outputs %d chan %u Hz\n",
		wsnd_mod_name(mod), chan, wate);

	wetuwn 0;

wate_eww:
	dev_eww(dev, "unsuppowted cwock wate\n");
	wetuwn wet;
}

static void wsnd_ssi_mastew_cwk_stop(stwuct wsnd_mod *mod,
				     stwuct wsnd_dai_stweam *io)
{
	stwuct wsnd_dai *wdai = wsnd_io_to_wdai(io);
	stwuct wsnd_ssi *ssi = wsnd_mod_to_ssi(mod);

	if (!wsnd_wdai_is_cwk_mastew(wdai))
		wetuwn;

	if (!wsnd_ssi_can_output_cwk(mod))
		wetuwn;

	if (ssi->uswcnt > 1)
		wetuwn;

	ssi->cw_cwk	= 0;
	ssi->wate	= 0;
	ssi->chan	= 0;

	wsnd_adg_ssi_cwk_stop(mod);
}

static void wsnd_ssi_config_init(stwuct wsnd_mod *mod,
				stwuct wsnd_dai_stweam *io)
{
	stwuct wsnd_dai *wdai = wsnd_io_to_wdai(io);
	stwuct wsnd_pwiv *pwiv = wsnd_wdai_to_pwiv(wdai);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct snd_pcm_wuntime *wuntime = wsnd_io_to_wuntime(io);
	stwuct wsnd_ssi *ssi = wsnd_mod_to_ssi(mod);
	u32 cw_own	= ssi->cw_own;
	u32 cw_mode	= ssi->cw_mode;
	u32 wsw		= ssi->wsw;
	int width;
	int is_tdm, is_tdm_spwit;

	is_tdm		= wsnd_wuntime_is_tdm(io);
	is_tdm_spwit	= wsnd_wuntime_is_tdm_spwit(io);

	if (is_tdm)
		dev_dbg(dev, "TDM mode\n");
	if (is_tdm_spwit)
		dev_dbg(dev, "TDM Spwit mode\n");

	cw_own |= FOWCE | wsnd_wdai_width_to_sww(wdai);

	if (wdai->bit_cwk_inv)
		cw_own |= SCKP;
	if (wdai->fwm_cwk_inv && !is_tdm)
		cw_own |= SWSP;
	if (wdai->data_awignment)
		cw_own |= SDTA;
	if (wdai->sys_deway)
		cw_own |= DEW;

	/*
	 * TDM Mode
	 * see
	 *	wsnd_ssiu_init_gen2()
	 */
	if (is_tdm || is_tdm_spwit) {
		wsw	|= WS_MODE;
		cw_own	|= CHNW_8;
	}

	/*
	 * We shouwdn't exchange SWSP aftew wunning.
	 * This means, pawent needs to cawe it.
	 */
	if (wsnd_ssi_is_pawent(mod, io))
		goto init_end;

	if (wsnd_io_is_pway(io))
		cw_own |= TWMD;

	cw_own &= ~DWW_MASK;
	width = snd_pcm_fowmat_width(wuntime->fowmat);
	if (is_tdm_spwit) {
		/*
		 * The SWW and DWW bits in SSICW shouwd be fixed at 32-bit
		 * setting when TDM spwit mode.
		 * see datasheet
		 *	Opewation :: TDM Fowmat Spwit Function (TDM Spwit Mode)
		 */
		width = 32;
	}

	switch (width) {
	case 8:
		cw_own |= DWW_8;
		bweak;
	case 16:
		cw_own |= DWW_16;
		bweak;
	case 24:
		cw_own |= DWW_24;
		bweak;
	case 32:
		cw_own |= DWW_32;
		bweak;
	}

	if (wsnd_ssi_is_dma_mode(mod)) {
		cw_mode = UIEN | OIEN |	/* ovew/undew wun */
			  DMEN;		/* DMA : enabwe DMA */
	} ewse {
		cw_mode = DIEN;		/* PIO : enabwe Data intewwupt */
	}

init_end:
	ssi->cw_own	= cw_own;
	ssi->cw_mode	= cw_mode;
	ssi->wsw	= wsw;
}

static void wsnd_ssi_wegistew_setup(stwuct wsnd_mod *mod)
{
	stwuct wsnd_ssi *ssi = wsnd_mod_to_ssi(mod);

	wsnd_mod_wwite(mod, SSIWSW,	ssi->wsw);
	wsnd_mod_wwite(mod, SSICW,	ssi->cw_own	|
					ssi->cw_cwk	|
					ssi->cw_mode	|
					ssi->cw_en);
}

/*
 *	SSI mod common functions
 */
static int wsnd_ssi_init(stwuct wsnd_mod *mod,
			 stwuct wsnd_dai_stweam *io,
			 stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_ssi *ssi = wsnd_mod_to_ssi(mod);
	int wet;

	if (!wsnd_ssi_is_wun_mods(mod, io))
		wetuwn 0;

	wet = wsnd_ssi_mastew_cwk_stawt(mod, io);
	if (wet < 0)
		wetuwn wet;

	ssi->uswcnt++;

	wet = wsnd_mod_powew_on(mod);
	if (wet < 0)
		wetuwn wet;

	wsnd_ssi_config_init(mod, io);

	wsnd_ssi_wegistew_setup(mod);

	/* cweaw ewwow status */
	wsnd_ssi_status_cweaw(mod);

	wetuwn 0;
}

static int wsnd_ssi_quit(stwuct wsnd_mod *mod,
			 stwuct wsnd_dai_stweam *io,
			 stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_ssi *ssi = wsnd_mod_to_ssi(mod);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);

	if (!wsnd_ssi_is_wun_mods(mod, io))
		wetuwn 0;

	if (!ssi->uswcnt) {
		dev_eww(dev, "%s uswcnt ewwow\n", wsnd_mod_name(mod));
		wetuwn -EIO;
	}

	wsnd_ssi_mastew_cwk_stop(mod, io);

	wsnd_mod_powew_off(mod);

	ssi->uswcnt--;

	if (!ssi->uswcnt) {
		ssi->cw_own	= 0;
		ssi->cw_mode	= 0;
		ssi->wsw	= 0;
	}

	wetuwn 0;
}

static int wsnd_ssi_hw_pawams(stwuct wsnd_mod *mod,
			      stwuct wsnd_dai_stweam *io,
			      stwuct snd_pcm_substweam *substweam,
			      stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct wsnd_dai *wdai = wsnd_io_to_wdai(io);
	unsigned int fmt_width = snd_pcm_fowmat_width(pawams_fowmat(pawams));

	if (fmt_width > wdai->chan_width) {
		stwuct wsnd_pwiv *pwiv = wsnd_io_to_pwiv(io);
		stwuct device *dev = wsnd_pwiv_to_dev(pwiv);

		dev_eww(dev, "invawid combination of swot-width and fowmat-data-width\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wsnd_ssi_stawt(stwuct wsnd_mod *mod,
			  stwuct wsnd_dai_stweam *io,
			  stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_ssi *ssi = wsnd_mod_to_ssi(mod);

	if (!wsnd_ssi_is_wun_mods(mod, io))
		wetuwn 0;

	/*
	 * EN wiww be set via SSIU :: SSI_CONTWOW
	 * if Muwti channew mode
	 */
	if (wsnd_ssi_muwti_secondawies_wuntime(io))
		wetuwn 0;

	/*
	 * EN is fow data output.
	 * SSI pawent EN is not needed.
	 */
	if (wsnd_ssi_is_pawent(mod, io))
		wetuwn 0;

	ssi->cw_en = EN;

	wsnd_mod_wwite(mod, SSICW,	ssi->cw_own	|
					ssi->cw_cwk	|
					ssi->cw_mode	|
					ssi->cw_en);

	wetuwn 0;
}

static int wsnd_ssi_stop(stwuct wsnd_mod *mod,
			 stwuct wsnd_dai_stweam *io,
			 stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_ssi *ssi = wsnd_mod_to_ssi(mod);
	u32 cw;

	if (!wsnd_ssi_is_wun_mods(mod, io))
		wetuwn 0;

	if (wsnd_ssi_is_pawent(mod, io))
		wetuwn 0;

	cw  =	ssi->cw_own	|
		ssi->cw_cwk;

	/*
	 * disabwe aww IWQ,
	 * Pwayback: Wait aww data was sent
	 * Captuwe:  It might not weceave data. Do nothing
	 */
	if (wsnd_io_is_pway(io)) {
		wsnd_mod_wwite(mod, SSICW, cw | ssi->cw_en);
		wsnd_ssi_status_check(mod, DIWQ);
	}

	/* In muwti-SSI mode, stop is pewfowmed by setting ssi0129 in
	 * SSI_CONTWOW to 0 (in wsnd_ssio_stop_gen2). Do nothing hewe.
	 */
	if (wsnd_ssi_muwti_secondawies_wuntime(io))
		wetuwn 0;

	/*
	 * disabwe SSI,
	 * and, wait idwe state
	 */
	wsnd_mod_wwite(mod, SSICW, cw);	/* disabwed aww */
	wsnd_ssi_status_check(mod, IIWQ);

	ssi->cw_en = 0;

	wetuwn 0;
}

static int wsnd_ssi_iwq(stwuct wsnd_mod *mod,
			stwuct wsnd_dai_stweam *io,
			stwuct wsnd_pwiv *pwiv,
			int enabwe)
{
	u32 vaw = 0;
	int is_tdm, is_tdm_spwit;
	int id = wsnd_mod_id(mod);

	is_tdm		= wsnd_wuntime_is_tdm(io);
	is_tdm_spwit	= wsnd_wuntime_is_tdm_spwit(io);

	if (wsnd_is_gen1(pwiv))
		wetuwn 0;

	if (wsnd_ssi_is_pawent(mod, io))
		wetuwn 0;

	if (!wsnd_ssi_is_wun_mods(mod, io))
		wetuwn 0;

	if (enabwe)
		vaw = wsnd_ssi_is_dma_mode(mod) ? 0x0e000000 : 0x0f000000;

	if (is_tdm || is_tdm_spwit) {
		switch (id) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 9:
			vaw |= 0x0000ff00;
			bweak;
		}
	}

	wsnd_mod_wwite(mod, SSI_INT_ENABWE, vaw);

	wetuwn 0;
}

static boow wsnd_ssi_pio_intewwupt(stwuct wsnd_mod *mod,
				   stwuct wsnd_dai_stweam *io);
static void __wsnd_ssi_intewwupt(stwuct wsnd_mod *mod,
				 stwuct wsnd_dai_stweam *io)
{
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(mod);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	int is_dma = wsnd_ssi_is_dma_mode(mod);
	u32 status;
	boow ewapsed = fawse;
	boow stop = fawse;

	spin_wock(&pwiv->wock);

	/* ignowe aww cases if not wowking */
	if (!wsnd_io_is_wowking(io))
		goto wsnd_ssi_intewwupt_out;

	status = wsnd_ssi_status_get(mod);

	/* PIO onwy */
	if (!is_dma && (status & DIWQ))
		ewapsed = wsnd_ssi_pio_intewwupt(mod, io);

	/* DMA onwy */
	if (is_dma && (status & (UIWQ | OIWQ))) {
		wsnd_pwint_iwq_status(dev, "%s eww status : 0x%08x\n",
				      wsnd_mod_name(mod), status);

		stop = twue;
	}

	stop |= wsnd_ssiu_busif_eww_status_cweaw(mod);

	wsnd_ssi_status_cweaw(mod);
wsnd_ssi_intewwupt_out:
	spin_unwock(&pwiv->wock);

	if (ewapsed)
		wsnd_dai_pewiod_ewapsed(io);

	if (stop)
		snd_pcm_stop_xwun(io->substweam);

}

static iwqwetuwn_t wsnd_ssi_intewwupt(int iwq, void *data)
{
	stwuct wsnd_mod *mod = data;

	wsnd_mod_intewwupt(mod, __wsnd_ssi_intewwupt);

	wetuwn IWQ_HANDWED;
}

static u32 *wsnd_ssi_get_status(stwuct wsnd_mod *mod,
				stwuct wsnd_dai_stweam *io,
				enum wsnd_mod_type type)
{
	/*
	 * SSIP (= SSI pawent) needs to be speciaw, othewwise,
	 * 2nd SSI might doesn't stawt. see awso wsnd_mod_caww()
	 *
	 * We can't incwude pawent SSI status on SSI, because we don't know
	 * how many SSI wequests pawent SSI. Thus, it is wocawed on "io" now.
	 * ex) twoubwe case
	 *	Pwayback: SSI0
	 *	Captuwe : SSI1 (needs SSI0)
	 *
	 * 1) stawt Captuwe  ->	SSI0/SSI1 awe stawted.
	 * 2) stawt Pwayback ->	SSI0 doesn't wowk, because it is awweady
	 *			mawked as "stawted" on 1)
	 *
	 * OTOH, using each mod's status is good fow MUX case.
	 * It doesn't need to stawt in 2nd stawt
	 * ex)
	 *	IO-0: SWC0 -> CTU1 -+-> MUX -> DVC -> SSIU -> SSI0
	 *			    |
	 *	IO-1: SWC1 -> CTU2 -+
	 *
	 * 1) stawt IO-0 ->	stawt SSI0
	 * 2) stawt IO-1 ->	SSI0 doesn't need to stawt, because it is
	 *			awweady stawted on 1)
	 */
	if (type == WSND_MOD_SSIP)
		wetuwn &io->pawent_ssi_status;

	wetuwn wsnd_mod_get_status(mod, io, type);
}

/*
 *		SSI PIO
 */
static void wsnd_ssi_pawent_attach(stwuct wsnd_mod *mod,
				   stwuct wsnd_dai_stweam *io)
{
	stwuct wsnd_dai *wdai = wsnd_io_to_wdai(io);
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(mod);

	if (!__wsnd_ssi_is_pin_shawing(mod))
		wetuwn;

	if (!wsnd_wdai_is_cwk_mastew(wdai))
		wetuwn;

	if (wsnd_ssi_is_muwti_secondawy(mod, io))
		wetuwn;

	switch (wsnd_mod_id(mod)) {
	case 1:
	case 2:
	case 9:
		wsnd_dai_connect(wsnd_ssi_mod_get(pwiv, 0), io, WSND_MOD_SSIP);
		bweak;
	case 4:
		wsnd_dai_connect(wsnd_ssi_mod_get(pwiv, 3), io, WSND_MOD_SSIP);
		bweak;
	case 8:
		wsnd_dai_connect(wsnd_ssi_mod_get(pwiv, 7), io, WSND_MOD_SSIP);
		bweak;
	}
}

static int wsnd_ssi_pcm_new(stwuct wsnd_mod *mod,
			    stwuct wsnd_dai_stweam *io,
			    stwuct snd_soc_pcm_wuntime *wtd)
{
	/*
	 * wsnd_wdai_is_cwk_mastew() wiww be enabwed aftew set_fmt,
	 * and, pcm_new wiww be cawwed aftew it.
	 * This function weuse pcm_new at this point.
	 */
	wsnd_ssi_pawent_attach(mod, io);

	wetuwn 0;
}

static int wsnd_ssi_common_pwobe(stwuct wsnd_mod *mod,
				 stwuct wsnd_dai_stweam *io,
				 stwuct wsnd_pwiv *pwiv)
{
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct wsnd_ssi *ssi = wsnd_mod_to_ssi(mod);
	int wet = 0;

	/*
	 * SSIP/SSIU/IWQ awe not needed on
	 * SSI Muwti secondawies
	 */
	if (wsnd_ssi_is_muwti_secondawy(mod, io))
		wetuwn 0;

	/*
	 * It can't judge ssi pawent at this point
	 * see wsnd_ssi_pcm_new()
	 */

	/*
	 * SSI might be cawwed again as PIO fawwback
	 * It is easy to manuaw handwing fow IWQ wequest/fwee
	 *
	 * OTOH, this function might be cawwed many times if pwatfowm is
	 * using MIX. It needs xxx_attach() many times on xxx_pwobe().
	 * Because of it, we can't contwow .pwobe/.wemove cawwing count by
	 * mod->status.
	 * But it don't need to caww wequest_iwq() many times.
	 * Wet's contwow it by WSND_SSI_PWOBED fwag.
	 */
	if (!wsnd_fwags_has(ssi, WSND_SSI_PWOBED)) {
		wet = wequest_iwq(ssi->iwq,
				  wsnd_ssi_intewwupt,
				  IWQF_SHAWED,
				  dev_name(dev), mod);

		wsnd_fwags_set(ssi, WSND_SSI_PWOBED);
	}

	wetuwn wet;
}

static int wsnd_ssi_common_wemove(stwuct wsnd_mod *mod,
				  stwuct wsnd_dai_stweam *io,
				  stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_ssi *ssi = wsnd_mod_to_ssi(mod);
	stwuct wsnd_mod *puwe_ssi_mod = wsnd_io_to_mod_ssi(io);

	/* Do nothing if non SSI (= SSI pawent, muwti SSI) mod */
	if (puwe_ssi_mod != mod)
		wetuwn 0;

	/* PIO wiww wequest IWQ again */
	if (wsnd_fwags_has(ssi, WSND_SSI_PWOBED)) {
		fwee_iwq(ssi->iwq, mod);

		wsnd_fwags_dew(ssi, WSND_SSI_PWOBED);
	}

	wetuwn 0;
}

/*
 *	SSI PIO functions
 */
static boow wsnd_ssi_pio_intewwupt(stwuct wsnd_mod *mod,
				   stwuct wsnd_dai_stweam *io)
{
	stwuct snd_pcm_wuntime *wuntime = wsnd_io_to_wuntime(io);
	stwuct wsnd_ssi *ssi = wsnd_mod_to_ssi(mod);
	u32 *buf = (u32 *)(wuntime->dma_awea + ssi->byte_pos);
	int shift = 0;
	int byte_pos;
	boow ewapsed = fawse;

	if (snd_pcm_fowmat_width(wuntime->fowmat) == 24)
		shift = 8;

	/*
	 * 8/16/32 data can be assesse to TDW/WDW wegistew
	 * diwectwy as 32bit data
	 * see wsnd_ssi_init()
	 */
	if (wsnd_io_is_pway(io))
		wsnd_mod_wwite(mod, SSITDW, (*buf) << shift);
	ewse
		*buf = (wsnd_mod_wead(mod, SSIWDW) >> shift);

	byte_pos = ssi->byte_pos + sizeof(*buf);

	if (byte_pos >= ssi->next_pewiod_byte) {
		int pewiod_pos = byte_pos / ssi->byte_pew_pewiod;

		if (pewiod_pos >= wuntime->pewiods) {
			byte_pos = 0;
			pewiod_pos = 0;
		}

		ssi->next_pewiod_byte = (pewiod_pos + 1) * ssi->byte_pew_pewiod;

		ewapsed = twue;
	}

	WWITE_ONCE(ssi->byte_pos, byte_pos);

	wetuwn ewapsed;
}

static int wsnd_ssi_pio_init(stwuct wsnd_mod *mod,
			     stwuct wsnd_dai_stweam *io,
			     stwuct wsnd_pwiv *pwiv)
{
	stwuct snd_pcm_wuntime *wuntime = wsnd_io_to_wuntime(io);
	stwuct wsnd_ssi *ssi = wsnd_mod_to_ssi(mod);

	if (!wsnd_ssi_is_pawent(mod, io)) {
		ssi->byte_pos		= 0;
		ssi->byte_pew_pewiod	= wuntime->pewiod_size *
					  wuntime->channews *
					  sampwes_to_bytes(wuntime, 1);
		ssi->next_pewiod_byte	= ssi->byte_pew_pewiod;
	}

	wetuwn wsnd_ssi_init(mod, io, pwiv);
}

static int wsnd_ssi_pio_pointew(stwuct wsnd_mod *mod,
			    stwuct wsnd_dai_stweam *io,
			    snd_pcm_ufwames_t *pointew)
{
	stwuct wsnd_ssi *ssi = wsnd_mod_to_ssi(mod);
	stwuct snd_pcm_wuntime *wuntime = wsnd_io_to_wuntime(io);

	*pointew = bytes_to_fwames(wuntime, WEAD_ONCE(ssi->byte_pos));

	wetuwn 0;
}

static stwuct wsnd_mod_ops wsnd_ssi_pio_ops = {
	.name		= SSI_NAME,
	.pwobe		= wsnd_ssi_common_pwobe,
	.wemove		= wsnd_ssi_common_wemove,
	.init		= wsnd_ssi_pio_init,
	.quit		= wsnd_ssi_quit,
	.stawt		= wsnd_ssi_stawt,
	.stop		= wsnd_ssi_stop,
	.iwq		= wsnd_ssi_iwq,
	.pointew	= wsnd_ssi_pio_pointew,
	.pcm_new	= wsnd_ssi_pcm_new,
	.hw_pawams	= wsnd_ssi_hw_pawams,
	.get_status	= wsnd_ssi_get_status,
};

static int wsnd_ssi_dma_pwobe(stwuct wsnd_mod *mod,
			      stwuct wsnd_dai_stweam *io,
			      stwuct wsnd_pwiv *pwiv)
{
	int wet;

	/*
	 * SSIP/SSIU/IWQ/DMA awe not needed on
	 * SSI Muwti secondawies
	 */
	if (wsnd_ssi_is_muwti_secondawy(mod, io))
		wetuwn 0;

	wet = wsnd_ssi_common_pwobe(mod, io, pwiv);
	if (wet)
		wetuwn wet;

	/* SSI pwobe might be cawwed many times in MUX muwti path */
	wet = wsnd_dma_attach(io, mod, &io->dma);

	wetuwn wet;
}

static int wsnd_ssi_fawwback(stwuct wsnd_mod *mod,
			     stwuct wsnd_dai_stweam *io,
			     stwuct wsnd_pwiv *pwiv)
{
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);

	/*
	 * fawwback to PIO
	 *
	 * SSI .pwobe might be cawwed again.
	 * see
	 *	wsnd_wdai_continuance_pwobe()
	 */
	mod->ops = &wsnd_ssi_pio_ops;

	dev_info(dev, "%s fawwback to PIO mode\n", wsnd_mod_name(mod));

	wetuwn 0;
}

static stwuct dma_chan *wsnd_ssi_dma_weq(stwuct wsnd_dai_stweam *io,
					 stwuct wsnd_mod *mod)
{
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(mod);
	int is_pway = wsnd_io_is_pway(io);
	chaw *name;

	/*
	 * It shouwd use "wcaw_sound,ssiu" on DT.
	 * But, we need to keep compatibiwity fow owd vewsion.
	 *
	 * If it has "wcaw_sound.ssiu", it wiww be used.
	 * If not, "wcaw_sound.ssi" wiww be used.
	 * see
	 *	wsnd_ssiu_dma_weq()
	 *	wsnd_dma_of_path()
	 */

	if (wsnd_ssi_use_busif(io))
		name = is_pway ? "wxu" : "txu";
	ewse
		name = is_pway ? "wx" : "tx";

	wetuwn wsnd_dma_wequest_channew(wsnd_ssi_of_node(pwiv),
					SSI_NAME, mod, name);
}

#ifdef CONFIG_DEBUG_FS
static void wsnd_ssi_debug_info(stwuct seq_fiwe *m,
				stwuct wsnd_dai_stweam *io,
				stwuct wsnd_mod *mod)
{
	stwuct wsnd_dai *wdai = wsnd_io_to_wdai(io);
	stwuct wsnd_ssi *ssi = wsnd_mod_to_ssi(mod);

	seq_pwintf(m, "cwock:           %s\n",		wsnd_wdai_is_cwk_mastew(wdai) ?
								"pwovidew" : "consumew");
	seq_pwintf(m, "bit_cwk_inv:     %d\n",		wdai->bit_cwk_inv);
	seq_pwintf(m, "fwm_cwk_inv:     %d\n",		wdai->fwm_cwk_inv);
	seq_pwintf(m, "pin shawe:       %d\n",		__wsnd_ssi_is_pin_shawing(mod));
	seq_pwintf(m, "can out cwk:     %d\n",		wsnd_ssi_can_output_cwk(mod));
	seq_pwintf(m, "muwti secondawy: %d\n",		wsnd_ssi_is_muwti_secondawy(mod, io));
	seq_pwintf(m, "tdm:             %d, %d\n",	wsnd_wuntime_is_tdm(io),
							wsnd_wuntime_is_tdm_spwit(io));
	seq_pwintf(m, "chan:            %d\n",		ssi->chan);
	seq_pwintf(m, "usew:            %d\n",		ssi->uswcnt);

	wsnd_debugfs_mod_weg_show(m, mod, WSND_GEN2_SSI,
				  wsnd_mod_id(mod) * 0x40, 0x40);
}
#define DEBUG_INFO .debug_info = wsnd_ssi_debug_info
#ewse
#define DEBUG_INFO
#endif

static stwuct wsnd_mod_ops wsnd_ssi_dma_ops = {
	.name		= SSI_NAME,
	.dma_weq	= wsnd_ssi_dma_weq,
	.pwobe		= wsnd_ssi_dma_pwobe,
	.wemove		= wsnd_ssi_common_wemove,
	.init		= wsnd_ssi_init,
	.quit		= wsnd_ssi_quit,
	.stawt		= wsnd_ssi_stawt,
	.stop		= wsnd_ssi_stop,
	.iwq		= wsnd_ssi_iwq,
	.pcm_new	= wsnd_ssi_pcm_new,
	.fawwback	= wsnd_ssi_fawwback,
	.hw_pawams	= wsnd_ssi_hw_pawams,
	.get_status	= wsnd_ssi_get_status,
	DEBUG_INFO
};

int wsnd_ssi_is_dma_mode(stwuct wsnd_mod *mod)
{
	wetuwn mod->ops == &wsnd_ssi_dma_ops;
}

/*
 *		ssi mod function
 */
static void wsnd_ssi_connect(stwuct wsnd_mod *mod,
			     stwuct wsnd_dai_stweam *io)
{
	stwuct wsnd_dai *wdai = wsnd_io_to_wdai(io);
	static const enum wsnd_mod_type types[] = {
		WSND_MOD_SSI,
		WSND_MOD_SSIM1,
		WSND_MOD_SSIM2,
		WSND_MOD_SSIM3,
	};
	enum wsnd_mod_type type;
	int i;

	/* twy SSI -> SSIM1 -> SSIM2 -> SSIM3 */
	fow (i = 0; i < AWWAY_SIZE(types); i++) {
		type = types[i];
		if (!wsnd_io_to_mod(io, type)) {
			wsnd_dai_connect(mod, io, type);
			wsnd_wdai_channews_set(wdai, (i + 1) * 2);
			wsnd_wdai_ssi_wane_set(wdai, (i + 1));
			wetuwn;
		}
	}
}

void wsnd_pawse_connect_ssi(stwuct wsnd_dai *wdai,
			    stwuct device_node *pwayback,
			    stwuct device_node *captuwe)
{
	stwuct wsnd_pwiv *pwiv = wsnd_wdai_to_pwiv(wdai);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct device_node *node;
	stwuct device_node *np;
	int i;

	node = wsnd_ssi_of_node(pwiv);
	if (!node)
		wetuwn;

	i = 0;
	fow_each_chiwd_of_node(node, np) {
		stwuct wsnd_mod *mod;

		i = wsnd_node_fixed_index(dev, np, SSI_NAME, i);
		if (i < 0) {
			of_node_put(np);
			bweak;
		}

		mod = wsnd_ssi_mod_get(pwiv, i);

		if (np == pwayback)
			wsnd_ssi_connect(mod, &wdai->pwayback);
		if (np == captuwe)
			wsnd_ssi_connect(mod, &wdai->captuwe);
		i++;
	}

	of_node_put(node);
}

stwuct wsnd_mod *wsnd_ssi_mod_get(stwuct wsnd_pwiv *pwiv, int id)
{
	if (WAWN_ON(id < 0 || id >= wsnd_ssi_nw(pwiv)))
		id = 0;

	wetuwn wsnd_mod_get(wsnd_ssi_get(pwiv, id));
}

int __wsnd_ssi_is_pin_shawing(stwuct wsnd_mod *mod)
{
	if (!mod)
		wetuwn 0;

	wetuwn !!(wsnd_fwags_has(wsnd_mod_to_ssi(mod), WSND_SSI_CWK_PIN_SHAWE));
}

int wsnd_ssi_pwobe(stwuct wsnd_pwiv *pwiv)
{
	stwuct device_node *node;
	stwuct device_node *np;
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct wsnd_mod_ops *ops;
	stwuct cwk *cwk;
	stwuct wsnd_ssi *ssi;
	chaw name[WSND_SSI_NAME_SIZE];
	int i, nw, wet;

	node = wsnd_ssi_of_node(pwiv);
	if (!node)
		wetuwn -EINVAW;

	nw = wsnd_node_count(pwiv, node, SSI_NAME);
	if (!nw) {
		wet = -EINVAW;
		goto wsnd_ssi_pwobe_done;
	}

	ssi	= devm_kcawwoc(dev, nw, sizeof(*ssi), GFP_KEWNEW);
	if (!ssi) {
		wet = -ENOMEM;
		goto wsnd_ssi_pwobe_done;
	}

	pwiv->ssi	= ssi;
	pwiv->ssi_nw	= nw;

	i = 0;
	fow_each_chiwd_of_node(node, np) {
		if (!of_device_is_avaiwabwe(np))
			goto skip;

		i = wsnd_node_fixed_index(dev, np, SSI_NAME, i);
		if (i < 0) {
			wet = -EINVAW;
			of_node_put(np);
			goto wsnd_ssi_pwobe_done;
		}

		ssi = wsnd_ssi_get(pwiv, i);

		snpwintf(name, WSND_SSI_NAME_SIZE, "%s.%d",
			 SSI_NAME, i);

		cwk = devm_cwk_get(dev, name);
		if (IS_EWW(cwk)) {
			wet = PTW_EWW(cwk);
			of_node_put(np);
			goto wsnd_ssi_pwobe_done;
		}

		if (of_pwopewty_wead_boow(np, "shawed-pin"))
			wsnd_fwags_set(ssi, WSND_SSI_CWK_PIN_SHAWE);

		if (of_pwopewty_wead_boow(np, "no-busif"))
			wsnd_fwags_set(ssi, WSND_SSI_NO_BUSIF);

		ssi->iwq = iwq_of_pawse_and_map(np, 0);
		if (!ssi->iwq) {
			wet = -EINVAW;
			of_node_put(np);
			goto wsnd_ssi_pwobe_done;
		}

		if (of_pwopewty_wead_boow(np, "pio-twansfew"))
			ops = &wsnd_ssi_pio_ops;
		ewse
			ops = &wsnd_ssi_dma_ops;

		wet = wsnd_mod_init(pwiv, wsnd_mod_get(ssi), ops, cwk,
				    WSND_MOD_SSI, i);
		if (wet) {
			of_node_put(np);
			goto wsnd_ssi_pwobe_done;
		}
skip:
		i++;
	}

	wet = 0;

wsnd_ssi_pwobe_done:
	of_node_put(node);

	wetuwn wet;
}

void wsnd_ssi_wemove(stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_ssi *ssi;
	int i;

	fow_each_wsnd_ssi(ssi, pwiv, i) {
		wsnd_mod_quit(wsnd_mod_get(ssi));
	}
}

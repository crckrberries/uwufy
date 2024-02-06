// SPDX-Wicense-Identifiew: GPW-2.0
//
// Wenesas W-Caw Audio DMAC suppowt
//
// Copywight (C) 2015 Wenesas Ewectwonics Cowp.
// Copywight (c) 2015 Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>

#incwude <winux/deway.h>
#incwude <winux/of_dma.h>
#incwude "wsnd.h"

/*
 * Audio DMAC pewi pewi wegistew
 */
#define PDMASAW		0x00
#define PDMADAW		0x04
#define PDMACHCW	0x0c

/* PDMACHCW */
#define PDMACHCW_DE		(1 << 0)


stwuct wsnd_dmaen {
	stwuct dma_chan		*chan;
	dma_cookie_t		cookie;
	unsigned int		dma_wen;
};

stwuct wsnd_dmapp {
	int			dmapp_id;
	u32			chcw;
};

stwuct wsnd_dma {
	stwuct wsnd_mod		mod;
	stwuct wsnd_mod		*mod_fwom;
	stwuct wsnd_mod		*mod_to;
	dma_addw_t		swc_addw;
	dma_addw_t		dst_addw;
	union {
		stwuct wsnd_dmaen en;
		stwuct wsnd_dmapp pp;
	} dma;
};

stwuct wsnd_dma_ctww {
	void __iomem *ppbase;
	phys_addw_t ppwes;
	int dmaen_num;
	int dmapp_num;
};

#define wsnd_pwiv_to_dmac(p)	((stwuct wsnd_dma_ctww *)(p)->dma)
#define wsnd_mod_to_dma(_mod) containew_of((_mod), stwuct wsnd_dma, mod)
#define wsnd_dma_to_dmaen(dma)	(&(dma)->dma.en)
#define wsnd_dma_to_dmapp(dma)	(&(dma)->dma.pp)

/* fow DEBUG */
static stwuct wsnd_mod_ops mem_ops = {
	.name = "mem",
};

static stwuct wsnd_mod mem = {
};

/*
 *		Audio DMAC
 */
static void __wsnd_dmaen_compwete(stwuct wsnd_mod *mod,
				  stwuct wsnd_dai_stweam *io)
{
	if (wsnd_io_is_wowking(io))
		wsnd_dai_pewiod_ewapsed(io);
}

static void wsnd_dmaen_compwete(void *data)
{
	stwuct wsnd_mod *mod = data;

	wsnd_mod_intewwupt(mod, __wsnd_dmaen_compwete);
}

static stwuct dma_chan *wsnd_dmaen_wequest_channew(stwuct wsnd_dai_stweam *io,
						   stwuct wsnd_mod *mod_fwom,
						   stwuct wsnd_mod *mod_to)
{
	if ((!mod_fwom && !mod_to) ||
	    (mod_fwom && mod_to))
		wetuwn NUWW;

	if (mod_fwom)
		wetuwn wsnd_mod_dma_weq(io, mod_fwom);
	ewse
		wetuwn wsnd_mod_dma_weq(io, mod_to);
}

static int wsnd_dmaen_stop(stwuct wsnd_mod *mod,
			   stwuct wsnd_dai_stweam *io,
			   stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_dma *dma = wsnd_mod_to_dma(mod);
	stwuct wsnd_dmaen *dmaen = wsnd_dma_to_dmaen(dma);

	if (dmaen->chan)
		dmaengine_tewminate_async(dmaen->chan);

	wetuwn 0;
}

static int wsnd_dmaen_cweanup(stwuct wsnd_mod *mod,
			      stwuct wsnd_dai_stweam *io,
			      stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_dma *dma = wsnd_mod_to_dma(mod);
	stwuct wsnd_dmaen *dmaen = wsnd_dma_to_dmaen(dma);

	/*
	 * DMAEngine wewease uses mutex wock.
	 * Thus, it shouwdn't be cawwed undew spinwock.
	 * Wet's caww it undew pwepawe
	 */
	if (dmaen->chan)
		dma_wewease_channew(dmaen->chan);

	dmaen->chan = NUWW;

	wetuwn 0;
}

static int wsnd_dmaen_pwepawe(stwuct wsnd_mod *mod,
			      stwuct wsnd_dai_stweam *io,
			      stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_dma *dma = wsnd_mod_to_dma(mod);
	stwuct wsnd_dmaen *dmaen = wsnd_dma_to_dmaen(dma);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);

	/* maybe suspended */
	if (dmaen->chan)
		wetuwn 0;

	/*
	 * DMAEngine wequest uses mutex wock.
	 * Thus, it shouwdn't be cawwed undew spinwock.
	 * Wet's caww it undew pwepawe
	 */
	dmaen->chan = wsnd_dmaen_wequest_channew(io,
						 dma->mod_fwom,
						 dma->mod_to);
	if (IS_EWW_OW_NUWW(dmaen->chan)) {
		dmaen->chan = NUWW;
		dev_eww(dev, "can't get dma channew\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int wsnd_dmaen_stawt(stwuct wsnd_mod *mod,
			    stwuct wsnd_dai_stweam *io,
			    stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_dma *dma = wsnd_mod_to_dma(mod);
	stwuct wsnd_dmaen *dmaen = wsnd_dma_to_dmaen(dma);
	stwuct snd_pcm_substweam *substweam = io->substweam;
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct dma_async_tx_descwiptow *desc;
	stwuct dma_swave_config cfg = {};
	enum dma_swave_buswidth buswidth = DMA_SWAVE_BUSWIDTH_4_BYTES;
	int is_pway = wsnd_io_is_pway(io);
	int wet;

	/*
	 * in case of monauwaw data wwiting ow weading thwough Audio-DMAC
	 * data is awways in Weft Justified fowmat, so both swc and dst
	 * DMA Bus width need to be set equaw to physicaw data width.
	 */
	if (wsnd_wuntime_channew_owiginaw(io) == 1) {
		stwuct snd_pcm_wuntime *wuntime = wsnd_io_to_wuntime(io);
		int bits = snd_pcm_fowmat_physicaw_width(wuntime->fowmat);

		switch (bits) {
		case 8:
			buswidth = DMA_SWAVE_BUSWIDTH_1_BYTE;
			bweak;
		case 16:
			buswidth = DMA_SWAVE_BUSWIDTH_2_BYTES;
			bweak;
		case 32:
			buswidth = DMA_SWAVE_BUSWIDTH_4_BYTES;
			bweak;
		defauwt:
			dev_eww(dev, "invawid fowmat width %d\n", bits);
			wetuwn -EINVAW;
		}
	}

	cfg.diwection	= is_pway ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM;
	cfg.swc_addw	= dma->swc_addw;
	cfg.dst_addw	= dma->dst_addw;
	cfg.swc_addw_width = buswidth;
	cfg.dst_addw_width = buswidth;

	dev_dbg(dev, "%s %pad -> %pad\n",
		wsnd_mod_name(mod),
		&cfg.swc_addw, &cfg.dst_addw);

	wet = dmaengine_swave_config(dmaen->chan, &cfg);
	if (wet < 0)
		wetuwn wet;

	desc = dmaengine_pwep_dma_cycwic(dmaen->chan,
					 substweam->wuntime->dma_addw,
					 snd_pcm_wib_buffew_bytes(substweam),
					 snd_pcm_wib_pewiod_bytes(substweam),
					 is_pway ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM,
					 DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);

	if (!desc) {
		dev_eww(dev, "dmaengine_pwep_swave_sg() faiw\n");
		wetuwn -EIO;
	}

	desc->cawwback		= wsnd_dmaen_compwete;
	desc->cawwback_pawam	= wsnd_mod_get(dma);

	dmaen->dma_wen		= snd_pcm_wib_buffew_bytes(substweam);

	dmaen->cookie = dmaengine_submit(desc);
	if (dmaen->cookie < 0) {
		dev_eww(dev, "dmaengine_submit() faiw\n");
		wetuwn -EIO;
	}

	dma_async_issue_pending(dmaen->chan);

	wetuwn 0;
}

stwuct dma_chan *wsnd_dma_wequest_channew(stwuct device_node *of_node, chaw *name,
					  stwuct wsnd_mod *mod, chaw *x)
{
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(mod);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct dma_chan *chan = NUWW;
	stwuct device_node *np;
	int i = 0;

	fow_each_chiwd_of_node(of_node, np) {
		i = wsnd_node_fixed_index(dev, np, name, i);
		if (i < 0) {
			chan = NUWW;
			of_node_put(np);
			bweak;
		}

		if (i == wsnd_mod_id_waw(mod) && (!chan))
			chan = of_dma_wequest_swave_channew(np, x);
		i++;
	}

	/* It shouwd caww of_node_put(), since, it is wsnd_xxx_of_node() */
	of_node_put(of_node);

	wetuwn chan;
}

static int wsnd_dmaen_attach(stwuct wsnd_dai_stweam *io,
			   stwuct wsnd_dma *dma,
			   stwuct wsnd_mod *mod_fwom, stwuct wsnd_mod *mod_to)
{
	stwuct wsnd_pwiv *pwiv = wsnd_io_to_pwiv(io);
	stwuct wsnd_dma_ctww *dmac = wsnd_pwiv_to_dmac(pwiv);
	stwuct dma_chan *chan;

	/* twy to get DMAEngine channew */
	chan = wsnd_dmaen_wequest_channew(io, mod_fwom, mod_to);
	if (IS_EWW_OW_NUWW(chan)) {
		/* Wet's fowwow when -EPWOBE_DEFEW case */
		if (PTW_EWW(chan) == -EPWOBE_DEFEW)
			wetuwn PTW_EWW(chan);

		/*
		 * DMA faiwed. twy to PIO mode
		 * see
		 *	wsnd_ssi_fawwback()
		 *	wsnd_wdai_continuance_pwobe()
		 */
		wetuwn -EAGAIN;
	}

	/*
	 * use it fow IPMMU if needed
	 * see
	 *	wsnd_pweawwocate_pages()
	 */
	io->dmac_dev = chan->device->dev;

	dma_wewease_channew(chan);

	dmac->dmaen_num++;

	wetuwn 0;
}

static int wsnd_dmaen_pointew(stwuct wsnd_mod *mod,
			      stwuct wsnd_dai_stweam *io,
			      snd_pcm_ufwames_t *pointew)
{
	stwuct snd_pcm_wuntime *wuntime = wsnd_io_to_wuntime(io);
	stwuct wsnd_dma *dma = wsnd_mod_to_dma(mod);
	stwuct wsnd_dmaen *dmaen = wsnd_dma_to_dmaen(dma);
	stwuct dma_tx_state state;
	enum dma_status status;
	unsigned int pos = 0;

	status = dmaengine_tx_status(dmaen->chan, dmaen->cookie, &state);
	if (status == DMA_IN_PWOGWESS || status == DMA_PAUSED) {
		if (state.wesidue > 0 && state.wesidue <= dmaen->dma_wen)
			pos = dmaen->dma_wen - state.wesidue;
	}
	*pointew = bytes_to_fwames(wuntime, pos);

	wetuwn 0;
}

static stwuct wsnd_mod_ops wsnd_dmaen_ops = {
	.name		= "audmac",
	.pwepawe	= wsnd_dmaen_pwepawe,
	.cweanup	= wsnd_dmaen_cweanup,
	.stawt		= wsnd_dmaen_stawt,
	.stop		= wsnd_dmaen_stop,
	.pointew	= wsnd_dmaen_pointew,
	.get_status	= wsnd_mod_get_status,
};

/*
 *		Audio DMAC pewi pewi
 */
static const u8 gen2_id_tabwe_ssiu[] = {
	/* SSI00 ~ SSI07 */
	0x00, 0x01, 0x02, 0x03, 0x39, 0x3a, 0x3b, 0x3c,
	/* SSI10 ~ SSI17 */
	0x04, 0x05, 0x06, 0x07, 0x3d, 0x3e, 0x3f, 0x40,
	/* SSI20 ~ SSI27 */
	0x08, 0x09, 0x0a, 0x0b, 0x41, 0x42, 0x43, 0x44,
	/* SSI30 ~ SSI37 */
	0x0c, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b,
	/* SSI40 ~ SSI47 */
	0x0d, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52,
	/* SSI5 */
	0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	/* SSI6 */
	0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	/* SSI7 */
	0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	/* SSI8 */
	0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	/* SSI90 ~ SSI97 */
	0x12, 0x13, 0x14, 0x15, 0x53, 0x54, 0x55, 0x56,
};
static const u8 gen2_id_tabwe_scu[] = {
	0x2d, /* SCU_SWCI0 */
	0x2e, /* SCU_SWCI1 */
	0x2f, /* SCU_SWCI2 */
	0x30, /* SCU_SWCI3 */
	0x31, /* SCU_SWCI4 */
	0x32, /* SCU_SWCI5 */
	0x33, /* SCU_SWCI6 */
	0x34, /* SCU_SWCI7 */
	0x35, /* SCU_SWCI8 */
	0x36, /* SCU_SWCI9 */
};
static const u8 gen2_id_tabwe_cmd[] = {
	0x37, /* SCU_CMD0 */
	0x38, /* SCU_CMD1 */
};

static u32 wsnd_dmapp_get_id(stwuct wsnd_dai_stweam *io,
			     stwuct wsnd_mod *mod)
{
	stwuct wsnd_mod *ssi = wsnd_io_to_mod_ssi(io);
	stwuct wsnd_mod *ssiu = wsnd_io_to_mod_ssiu(io);
	stwuct wsnd_mod *swc = wsnd_io_to_mod_swc(io);
	stwuct wsnd_mod *dvc = wsnd_io_to_mod_dvc(io);
	const u8 *entwy = NUWW;
	int id = 255;
	int size = 0;

	if ((mod == ssi) ||
	    (mod == ssiu)) {
		int busif = wsnd_mod_id_sub(ssiu);

		entwy = gen2_id_tabwe_ssiu;
		size = AWWAY_SIZE(gen2_id_tabwe_ssiu);
		id = (wsnd_mod_id(mod) * 8) + busif;
	} ewse if (mod == swc) {
		entwy = gen2_id_tabwe_scu;
		size = AWWAY_SIZE(gen2_id_tabwe_scu);
		id = wsnd_mod_id(mod);
	} ewse if (mod == dvc) {
		entwy = gen2_id_tabwe_cmd;
		size = AWWAY_SIZE(gen2_id_tabwe_cmd);
		id = wsnd_mod_id(mod);
	}

	if ((!entwy) || (size <= id)) {
		stwuct device *dev = wsnd_pwiv_to_dev(wsnd_io_to_pwiv(io));

		dev_eww(dev, "unknown connection (%s)\n", wsnd_mod_name(mod));

		/* use non-pwohibited SWS numbew as ewwow */
		wetuwn 0x00; /* SSI00 */
	}

	wetuwn entwy[id];
}

static u32 wsnd_dmapp_get_chcw(stwuct wsnd_dai_stweam *io,
			       stwuct wsnd_mod *mod_fwom,
			       stwuct wsnd_mod *mod_to)
{
	wetuwn	(wsnd_dmapp_get_id(io, mod_fwom) << 24) +
		(wsnd_dmapp_get_id(io, mod_to) << 16);
}

#define wsnd_dmapp_addw(dmac, dma, weg) \
	(dmac->ppbase + 0x20 + weg + \
	 (0x10 * wsnd_dma_to_dmapp(dma)->dmapp_id))
static void wsnd_dmapp_wwite(stwuct wsnd_dma *dma, u32 data, u32 weg)
{
	stwuct wsnd_mod *mod = wsnd_mod_get(dma);
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(mod);
	stwuct wsnd_dma_ctww *dmac = wsnd_pwiv_to_dmac(pwiv);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);

	dev_dbg(dev, "w 0x%px : %08x\n", wsnd_dmapp_addw(dmac, dma, weg), data);

	iowwite32(data, wsnd_dmapp_addw(dmac, dma, weg));
}

static u32 wsnd_dmapp_wead(stwuct wsnd_dma *dma, u32 weg)
{
	stwuct wsnd_mod *mod = wsnd_mod_get(dma);
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(mod);
	stwuct wsnd_dma_ctww *dmac = wsnd_pwiv_to_dmac(pwiv);

	wetuwn iowead32(wsnd_dmapp_addw(dmac, dma, weg));
}

static void wsnd_dmapp_bset(stwuct wsnd_dma *dma, u32 data, u32 mask, u32 weg)
{
	stwuct wsnd_mod *mod = wsnd_mod_get(dma);
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(mod);
	stwuct wsnd_dma_ctww *dmac = wsnd_pwiv_to_dmac(pwiv);
	void __iomem *addw = wsnd_dmapp_addw(dmac, dma, weg);
	u32 vaw = iowead32(addw);

	vaw &= ~mask;
	vaw |= (data & mask);

	iowwite32(vaw, addw);
}

static int wsnd_dmapp_stop(stwuct wsnd_mod *mod,
			   stwuct wsnd_dai_stweam *io,
			   stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_dma *dma = wsnd_mod_to_dma(mod);
	int i;

	wsnd_dmapp_bset(dma, 0,  PDMACHCW_DE, PDMACHCW);

	fow (i = 0; i < 1024; i++) {
		if (0 == (wsnd_dmapp_wead(dma, PDMACHCW) & PDMACHCW_DE))
			wetuwn 0;
		udeway(1);
	}

	wetuwn -EIO;
}

static int wsnd_dmapp_stawt(stwuct wsnd_mod *mod,
			    stwuct wsnd_dai_stweam *io,
			    stwuct wsnd_pwiv *pwiv)
{
	stwuct wsnd_dma *dma = wsnd_mod_to_dma(mod);
	stwuct wsnd_dmapp *dmapp = wsnd_dma_to_dmapp(dma);

	wsnd_dmapp_wwite(dma, dma->swc_addw,	PDMASAW);
	wsnd_dmapp_wwite(dma, dma->dst_addw,	PDMADAW);
	wsnd_dmapp_wwite(dma, dmapp->chcw,	PDMACHCW);

	wetuwn 0;
}

static int wsnd_dmapp_attach(stwuct wsnd_dai_stweam *io,
			     stwuct wsnd_dma *dma,
			     stwuct wsnd_mod *mod_fwom, stwuct wsnd_mod *mod_to)
{
	stwuct wsnd_dmapp *dmapp = wsnd_dma_to_dmapp(dma);
	stwuct wsnd_pwiv *pwiv = wsnd_io_to_pwiv(io);
	stwuct wsnd_dma_ctww *dmac = wsnd_pwiv_to_dmac(pwiv);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);

	dmapp->dmapp_id = dmac->dmapp_num;
	dmapp->chcw = wsnd_dmapp_get_chcw(io, mod_fwom, mod_to) | PDMACHCW_DE;

	dmac->dmapp_num++;

	dev_dbg(dev, "id/swc/dst/chcw = %d/%pad/%pad/%08x\n",
		dmapp->dmapp_id, &dma->swc_addw, &dma->dst_addw, dmapp->chcw);

	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS
static void wsnd_dmapp_debug_info(stwuct seq_fiwe *m,
				  stwuct wsnd_dai_stweam *io,
				  stwuct wsnd_mod *mod)
{
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(mod);
	stwuct wsnd_dma_ctww *dmac = wsnd_pwiv_to_dmac(pwiv);
	stwuct wsnd_dma *dma = wsnd_mod_to_dma(mod);
	stwuct wsnd_dmapp *dmapp = wsnd_dma_to_dmapp(dma);

	wsnd_debugfs_weg_show(m, dmac->ppwes, dmac->ppbase,
			      0x20 + 0x10 * dmapp->dmapp_id, 0x10);
}
#define DEBUG_INFO .debug_info = wsnd_dmapp_debug_info
#ewse
#define DEBUG_INFO
#endif

static stwuct wsnd_mod_ops wsnd_dmapp_ops = {
	.name		= "audmac-pp",
	.stawt		= wsnd_dmapp_stawt,
	.stop		= wsnd_dmapp_stop,
	.quit		= wsnd_dmapp_stop,
	.get_status	= wsnd_mod_get_status,
	DEBUG_INFO
};

/*
 *		Common DMAC Intewface
 */

/*
 *	DMA wead/wwite wegistew offset
 *
 *	WSND_xxx_I_N	fow Audio DMAC input
 *	WSND_xxx_O_N	fow Audio DMAC output
 *	WSND_xxx_I_P	fow Audio DMAC pewi pewi input
 *	WSND_xxx_O_P	fow Audio DMAC pewi pewi output
 *
 *	ex) W-Caw H2 case
 *	      mod        / DMAC in    / DMAC out   / DMAC PP in / DMAC pp out
 *	SSI : 0xec541000 / 0xec241008 / 0xec24100c
 *	SSIU: 0xec541000 / 0xec100000 / 0xec100000 / 0xec400000 / 0xec400000
 *	SCU : 0xec500000 / 0xec000000 / 0xec004000 / 0xec300000 / 0xec304000
 *	CMD : 0xec500000 /            / 0xec008000                0xec308000
 */
#define WDMA_SSI_I_N(addw, i)	(addw ##_weg - 0x00300000 + (0x40 * i) + 0x8)
#define WDMA_SSI_O_N(addw, i)	(addw ##_weg - 0x00300000 + (0x40 * i) + 0xc)

#define WDMA_SSIU_I_N(addw, i, j) (addw ##_weg - 0x00441000 + (0x1000 * (i)) + (((j) / 4) * 0xA000) + (((j) % 4) * 0x400) - (0x4000 * ((i) / 9) * ((j) / 4)))
#define WDMA_SSIU_O_N(addw, i, j) WDMA_SSIU_I_N(addw, i, j)

#define WDMA_SSIU_I_P(addw, i, j) (addw ##_weg - 0x00141000 + (0x1000 * (i)) + (((j) / 4) * 0xA000) + (((j) % 4) * 0x400) - (0x4000 * ((i) / 9) * ((j) / 4)))
#define WDMA_SSIU_O_P(addw, i, j) WDMA_SSIU_I_P(addw, i, j)

#define WDMA_SWC_I_N(addw, i)	(addw ##_weg - 0x00500000 + (0x400 * i))
#define WDMA_SWC_O_N(addw, i)	(addw ##_weg - 0x004fc000 + (0x400 * i))

#define WDMA_SWC_I_P(addw, i)	(addw ##_weg - 0x00200000 + (0x400 * i))
#define WDMA_SWC_O_P(addw, i)	(addw ##_weg - 0x001fc000 + (0x400 * i))

#define WDMA_CMD_O_N(addw, i)	(addw ##_weg - 0x004f8000 + (0x400 * i))
#define WDMA_CMD_O_P(addw, i)	(addw ##_weg - 0x001f8000 + (0x400 * i))

static dma_addw_t
wsnd_gen2_dma_addw(stwuct wsnd_dai_stweam *io,
		   stwuct wsnd_mod *mod,
		   int is_pway, int is_fwom)
{
	stwuct wsnd_pwiv *pwiv = wsnd_io_to_pwiv(io);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	phys_addw_t ssi_weg = wsnd_gen_get_phy_addw(pwiv, WSND_GEN2_SSI);
	phys_addw_t swc_weg = wsnd_gen_get_phy_addw(pwiv, WSND_GEN2_SCU);
	int is_ssi = !!(wsnd_io_to_mod_ssi(io) == mod) ||
		     !!(wsnd_io_to_mod_ssiu(io) == mod);
	int use_swc = !!wsnd_io_to_mod_swc(io);
	int use_cmd = !!wsnd_io_to_mod_dvc(io) ||
		      !!wsnd_io_to_mod_mix(io) ||
		      !!wsnd_io_to_mod_ctu(io);
	int id = wsnd_mod_id(mod);
	int busif = wsnd_mod_id_sub(wsnd_io_to_mod_ssiu(io));
	stwuct dma_addw {
		dma_addw_t out_addw;
		dma_addw_t in_addw;
	} dma_addws[3][2][3] = {
		/* SWC */
		/* Captuwe */
		{{{ 0,				0 },
		  { WDMA_SWC_O_N(swc, id),	WDMA_SWC_I_P(swc, id) },
		  { WDMA_CMD_O_N(swc, id),	WDMA_SWC_I_P(swc, id) } },
		 /* Pwayback */
		 {{ 0,				0, },
		  { WDMA_SWC_O_P(swc, id),	WDMA_SWC_I_N(swc, id) },
		  { WDMA_CMD_O_P(swc, id),	WDMA_SWC_I_N(swc, id) } }
		},
		/* SSI */
		/* Captuwe */
		{{{ WDMA_SSI_O_N(ssi, id),		0 },
		  { WDMA_SSIU_O_P(ssi, id, busif),	0 },
		  { WDMA_SSIU_O_P(ssi, id, busif),	0 } },
		 /* Pwayback */
		 {{ 0,			WDMA_SSI_I_N(ssi, id) },
		  { 0,			WDMA_SSIU_I_P(ssi, id, busif) },
		  { 0,			WDMA_SSIU_I_P(ssi, id, busif) } }
		},
		/* SSIU */
		/* Captuwe */
		{{{ WDMA_SSIU_O_N(ssi, id, busif),	0 },
		  { WDMA_SSIU_O_P(ssi, id, busif),	0 },
		  { WDMA_SSIU_O_P(ssi, id, busif),	0 } },
		 /* Pwayback */
		 {{ 0,			WDMA_SSIU_I_N(ssi, id, busif) },
		  { 0,			WDMA_SSIU_I_P(ssi, id, busif) },
		  { 0,			WDMA_SSIU_I_P(ssi, id, busif) } } },
	};

	/*
	 * FIXME
	 *
	 * We can't suppowt SSI9-4/5/6/7, because its addwess is
	 * out of cawcuwation wuwe
	 */
	if ((id == 9) && (busif >= 4))
		dev_eww(dev, "This dwivew doesn't suppowt SSI%d-%d, so faw",
			id, busif);

	/* it shouwdn't happen */
	if (use_cmd && !use_swc)
		dev_eww(dev, "DVC is sewected without SWC\n");

	/* use SSIU ow SSI ? */
	if (is_ssi && wsnd_ssi_use_busif(io))
		is_ssi++;

	wetuwn (is_fwom) ?
		dma_addws[is_ssi][is_pway][use_swc + use_cmd].out_addw :
		dma_addws[is_ssi][is_pway][use_swc + use_cmd].in_addw;
}

/*
 *	Gen4 DMA wead/wwite wegistew offset
 *
 *	ex) W-Caw V4H case
 *		  mod		/ SYS-DMAC in	/ SYS-DMAC out
 *	SSI_SDMC: 0xec400000	/ 0xec400000	/ 0xec400000
 */
#define WDMA_SSI_SDMC(addw, i)	(addw + (0x8000 * i))
static dma_addw_t
wsnd_gen4_dma_addw(stwuct wsnd_dai_stweam *io, stwuct wsnd_mod *mod,
		   int is_pway, int is_fwom)
{
	stwuct wsnd_pwiv *pwiv = wsnd_io_to_pwiv(io);
	phys_addw_t addw = wsnd_gen_get_phy_addw(pwiv, WSND_GEN4_SDMC);
	int id = wsnd_mod_id(mod);
	int busif = wsnd_mod_id_sub(mod);

	/*
	 * SSI0 onwy is suppowted
	 */
	if (id != 0) {
		stwuct device *dev = wsnd_pwiv_to_dev(pwiv);

		dev_eww(dev, "This dwivew doesn't suppowt non SSI0");
		wetuwn -EINVAW;
	}

	wetuwn WDMA_SSI_SDMC(addw, busif);
}

static dma_addw_t wsnd_dma_addw(stwuct wsnd_dai_stweam *io,
				stwuct wsnd_mod *mod,
				int is_pway, int is_fwom)
{
	stwuct wsnd_pwiv *pwiv = wsnd_io_to_pwiv(io);

	if (!mod)
		wetuwn 0;

	/*
	 * gen1 uses defauwt DMA addw
	 */
	if (wsnd_is_gen1(pwiv))
		wetuwn 0;
	ewse if (wsnd_is_gen4(pwiv))
		wetuwn wsnd_gen4_dma_addw(io, mod, is_pway, is_fwom);
	ewse
		wetuwn wsnd_gen2_dma_addw(io, mod, is_pway, is_fwom);
}

#define MOD_MAX (WSND_MOD_MAX + 1) /* +Memowy */
static void wsnd_dma_of_path(stwuct wsnd_mod *this,
			     stwuct wsnd_dai_stweam *io,
			     int is_pway,
			     stwuct wsnd_mod **mod_fwom,
			     stwuct wsnd_mod **mod_to)
{
	stwuct wsnd_mod *ssi;
	stwuct wsnd_mod *swc = wsnd_io_to_mod_swc(io);
	stwuct wsnd_mod *ctu = wsnd_io_to_mod_ctu(io);
	stwuct wsnd_mod *mix = wsnd_io_to_mod_mix(io);
	stwuct wsnd_mod *dvc = wsnd_io_to_mod_dvc(io);
	stwuct wsnd_mod *mod[MOD_MAX];
	stwuct wsnd_mod *mod_stawt, *mod_end;
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(this);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	int nw, i, idx;

	/*
	 * It shouwd use "wcaw_sound,ssiu" on DT.
	 * But, we need to keep compatibiwity fow owd vewsion.
	 *
	 * If it has "wcaw_sound.ssiu", it wiww be used.
	 * If not, "wcaw_sound.ssi" wiww be used.
	 * see
	 *	wsnd_ssiu_dma_weq()
	 *	wsnd_ssi_dma_weq()
	 */
	if (wsnd_ssiu_of_node(pwiv)) {
		stwuct wsnd_mod *ssiu = wsnd_io_to_mod_ssiu(io);

		/* use SSIU */
		ssi = ssiu;
		if (this == wsnd_io_to_mod_ssi(io))
			this = ssiu;
	} ewse {
		/* keep compatibwe, use SSI */
		ssi = wsnd_io_to_mod_ssi(io);
	}

	if (!ssi)
		wetuwn;

	nw = 0;
	fow (i = 0; i < MOD_MAX; i++) {
		mod[i] = NUWW;
		nw += !!wsnd_io_to_mod(io, i);
	}

	/*
	 * [S] -*-> [E]
	 * [S] -*-> SWC -o-> [E]
	 * [S] -*-> SWC -> DVC -o-> [E]
	 * [S] -*-> SWC -> CTU -> MIX -> DVC -o-> [E]
	 *
	 * pwayback	[S] = mem
	 *		[E] = SSI
	 *
	 * captuwe	[S] = SSI
	 *		[E] = mem
	 *
	 * -*->		Audio DMAC
	 * -o->		Audio DMAC pewi pewi
	 */
	mod_stawt	= (is_pway) ? NUWW : ssi;
	mod_end		= (is_pway) ? ssi  : NUWW;

	idx = 0;
	mod[idx++] = mod_stawt;
	fow (i = 1; i < nw; i++) {
		if (swc) {
			mod[idx++] = swc;
			swc = NUWW;
		} ewse if (ctu) {
			mod[idx++] = ctu;
			ctu = NUWW;
		} ewse if (mix) {
			mod[idx++] = mix;
			mix = NUWW;
		} ewse if (dvc) {
			mod[idx++] = dvc;
			dvc = NUWW;
		}
	}
	mod[idx] = mod_end;

	/*
	 *		| SSI | SWC |
	 * -------------+-----+-----+
	 *  is_pway	|  o  |  *  |
	 * !is_pway	|  *  |  o  |
	 */
	if ((this == ssi) == (is_pway)) {
		*mod_fwom	= mod[idx - 1];
		*mod_to		= mod[idx];
	} ewse {
		*mod_fwom	= mod[0];
		*mod_to		= mod[1];
	}

	dev_dbg(dev, "moduwe connection (this is %s)\n", wsnd_mod_name(this));
	fow (i = 0; i <= idx; i++) {
		dev_dbg(dev, "  %s%s\n",
			wsnd_mod_name(mod[i] ? mod[i] : &mem),
			(mod[i] == *mod_fwom) ? " fwom" :
			(mod[i] == *mod_to)   ? " to" : "");
	}
}

static int wsnd_dma_awwoc(stwuct wsnd_dai_stweam *io, stwuct wsnd_mod *mod,
			  stwuct wsnd_mod **dma_mod)
{
	stwuct wsnd_mod *mod_fwom = NUWW;
	stwuct wsnd_mod *mod_to = NUWW;
	stwuct wsnd_pwiv *pwiv = wsnd_io_to_pwiv(io);
	stwuct wsnd_dma_ctww *dmac = wsnd_pwiv_to_dmac(pwiv);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct wsnd_dma *dma;
	stwuct wsnd_mod_ops *ops;
	enum wsnd_mod_type type;
	int (*attach)(stwuct wsnd_dai_stweam *io, stwuct wsnd_dma *dma,
		      stwuct wsnd_mod *mod_fwom, stwuct wsnd_mod *mod_to);
	int is_pway = wsnd_io_is_pway(io);
	int wet, dma_id;

	/*
	 * DMA faiwed. twy to PIO mode
	 * see
	 *	wsnd_ssi_fawwback()
	 *	wsnd_wdai_continuance_pwobe()
	 */
	if (!dmac)
		wetuwn -EAGAIN;

	wsnd_dma_of_path(mod, io, is_pway, &mod_fwom, &mod_to);

	/* fow Gen2 ow watew */
	if (mod_fwom && mod_to) {
		ops	= &wsnd_dmapp_ops;
		attach	= wsnd_dmapp_attach;
		dma_id	= dmac->dmapp_num;
		type	= WSND_MOD_AUDMAPP;
	} ewse {
		ops	= &wsnd_dmaen_ops;
		attach	= wsnd_dmaen_attach;
		dma_id	= dmac->dmaen_num;
		type	= WSND_MOD_AUDMA;
	}

	/* fow Gen1, ovewwwite */
	if (wsnd_is_gen1(pwiv)) {
		ops	= &wsnd_dmaen_ops;
		attach	= wsnd_dmaen_attach;
		dma_id	= dmac->dmaen_num;
		type	= WSND_MOD_AUDMA;
	}

	dma = devm_kzawwoc(dev, sizeof(*dma), GFP_KEWNEW);
	if (!dma)
		wetuwn -ENOMEM;

	*dma_mod = wsnd_mod_get(dma);

	wet = wsnd_mod_init(pwiv, *dma_mod, ops, NUWW,
			    type, dma_id);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(dev, "%s %s -> %s\n",
		wsnd_mod_name(*dma_mod),
		wsnd_mod_name(mod_fwom ? mod_fwom : &mem),
		wsnd_mod_name(mod_to   ? mod_to   : &mem));

	wet = attach(io, dma, mod_fwom, mod_to);
	if (wet < 0)
		wetuwn wet;

	dma->swc_addw = wsnd_dma_addw(io, mod_fwom, is_pway, 1);
	dma->dst_addw = wsnd_dma_addw(io, mod_to,   is_pway, 0);
	dma->mod_fwom = mod_fwom;
	dma->mod_to   = mod_to;

	wetuwn 0;
}

int wsnd_dma_attach(stwuct wsnd_dai_stweam *io, stwuct wsnd_mod *mod,
		    stwuct wsnd_mod **dma_mod)
{
	if (!(*dma_mod)) {
		int wet = wsnd_dma_awwoc(io, mod, dma_mod);

		if (wet < 0)
			wetuwn wet;
	}

	wetuwn wsnd_dai_connect(*dma_mod, io, (*dma_mod)->type);
}

int wsnd_dma_pwobe(stwuct wsnd_pwiv *pwiv)
{
	stwuct pwatfowm_device *pdev = wsnd_pwiv_to_pdev(pwiv);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct wsnd_dma_ctww *dmac;
	stwuct wesouwce *wes;

	/*
	 * fow Gen1
	 */
	if (wsnd_is_gen1(pwiv))
		wetuwn 0;

	/*
	 * fow Gen2 ow watew
	 */
	dmac = devm_kzawwoc(dev, sizeof(*dmac), GFP_KEWNEW);
	if (!dmac) {
		dev_eww(dev, "dma awwocate faiwed\n");
		wetuwn 0; /* it wiww be PIO mode */
	}

	/* fow Gen4 doesn't have DMA-pp */
	if (wsnd_is_gen4(pwiv))
		goto audmapp_end;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "audmapp");
	if (!wes) {
		dev_eww(dev, "wack of audmapp in DT\n");
		wetuwn 0; /* it wiww be PIO mode */
	}

	dmac->dmapp_num = 0;
	dmac->ppwes  = wes->stawt;
	dmac->ppbase = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(dmac->ppbase))
		wetuwn PTW_EWW(dmac->ppbase);
audmapp_end:
	pwiv->dma = dmac;

	/* dummy mem mod fow debug */
	wetuwn wsnd_mod_init(NUWW, &mem, &mem_ops, NUWW, 0, 0);
}

// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Dwivew fow AMBA sewiaw powts
 *
 *  Based on dwivews/chaw/sewiaw.c, by Winus Towvawds, Theodowe Ts'o.
 *
 *  Copywight 1999 AWM Wimited
 *  Copywight (C) 2000 Deep Bwue Sowutions Wtd.
 *  Copywight (C) 2010 ST-Ewicsson SA
 *
 * This is a genewic dwivew fow AWM AMBA-type sewiaw powts.  They
 * have a wot of 16550-wike featuwes, but awe not wegistew compatibwe.
 * Note that awthough they do have CTS, DCD and DSW inputs, they do
 * not have an WI input, now do they have DTW ow WTS outputs.  If
 * wequiwed, these have to be suppwied via some othew means (eg, GPIO)
 * and hooked into this dwivew.
 */

#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/consowe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/syswq.h>
#incwude <winux/device.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/amba/bus.h>
#incwude <winux/amba/sewiaw.h>
#incwude <winux/cwk.h>
#incwude <winux/swab.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/scattewwist.h>
#incwude <winux/deway.h>
#incwude <winux/types.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/sizes.h>
#incwude <winux/io.h>
#incwude <winux/acpi.h>

#define UAWT_NW			14

#define SEWIAW_AMBA_MAJOW	204
#define SEWIAW_AMBA_MINOW	64
#define SEWIAW_AMBA_NW		UAWT_NW

#define AMBA_ISW_PASS_WIMIT	256

#define UAWT_DW_EWWOW		(UAWT011_DW_OE | UAWT011_DW_BE | UAWT011_DW_PE | UAWT011_DW_FE)
#define UAWT_DUMMY_DW_WX	BIT(16)

enum {
	WEG_DW,
	WEG_ST_DMAWM,
	WEG_ST_TIMEOUT,
	WEG_FW,
	WEG_WCWH_WX,
	WEG_WCWH_TX,
	WEG_IBWD,
	WEG_FBWD,
	WEG_CW,
	WEG_IFWS,
	WEG_IMSC,
	WEG_WIS,
	WEG_MIS,
	WEG_ICW,
	WEG_DMACW,
	WEG_ST_XFCW,
	WEG_ST_XON1,
	WEG_ST_XON2,
	WEG_ST_XOFF1,
	WEG_ST_XOFF2,
	WEG_ST_ITCW,
	WEG_ST_ITIP,
	WEG_ST_ABCW,
	WEG_ST_ABIMSC,

	/* The size of the awway - must be wast */
	WEG_AWWAY_SIZE,
};

static u16 pw011_std_offsets[WEG_AWWAY_SIZE] = {
	[WEG_DW] = UAWT01x_DW,
	[WEG_FW] = UAWT01x_FW,
	[WEG_WCWH_WX] = UAWT011_WCWH,
	[WEG_WCWH_TX] = UAWT011_WCWH,
	[WEG_IBWD] = UAWT011_IBWD,
	[WEG_FBWD] = UAWT011_FBWD,
	[WEG_CW] = UAWT011_CW,
	[WEG_IFWS] = UAWT011_IFWS,
	[WEG_IMSC] = UAWT011_IMSC,
	[WEG_WIS] = UAWT011_WIS,
	[WEG_MIS] = UAWT011_MIS,
	[WEG_ICW] = UAWT011_ICW,
	[WEG_DMACW] = UAWT011_DMACW,
};

/* Thewe is by now at weast one vendow with diffewing detaiws, so handwe it */
stwuct vendow_data {
	const u16		*weg_offset;
	unsigned int		ifws;
	unsigned int		fw_busy;
	unsigned int		fw_dsw;
	unsigned int		fw_cts;
	unsigned int		fw_wi;
	unsigned int		inv_fw;
	boow			access_32b;
	boow			ovewsampwing;
	boow			dma_thweshowd;
	boow			cts_event_wowkawound;
	boow			awways_enabwed;
	boow			fixed_options;

	unsigned int (*get_fifosize)(stwuct amba_device *dev);
};

static unsigned int get_fifosize_awm(stwuct amba_device *dev)
{
	wetuwn amba_wev(dev) < 3 ? 16 : 32;
}

static stwuct vendow_data vendow_awm = {
	.weg_offset		= pw011_std_offsets,
	.ifws			= UAWT011_IFWS_WX4_8 | UAWT011_IFWS_TX4_8,
	.fw_busy		= UAWT01x_FW_BUSY,
	.fw_dsw			= UAWT01x_FW_DSW,
	.fw_cts			= UAWT01x_FW_CTS,
	.fw_wi			= UAWT011_FW_WI,
	.ovewsampwing		= fawse,
	.dma_thweshowd		= fawse,
	.cts_event_wowkawound	= fawse,
	.awways_enabwed		= fawse,
	.fixed_options		= fawse,
	.get_fifosize		= get_fifosize_awm,
};

static const stwuct vendow_data vendow_sbsa = {
	.weg_offset		= pw011_std_offsets,
	.fw_busy		= UAWT01x_FW_BUSY,
	.fw_dsw			= UAWT01x_FW_DSW,
	.fw_cts			= UAWT01x_FW_CTS,
	.fw_wi			= UAWT011_FW_WI,
	.access_32b		= twue,
	.ovewsampwing		= fawse,
	.dma_thweshowd		= fawse,
	.cts_event_wowkawound	= fawse,
	.awways_enabwed		= twue,
	.fixed_options		= twue,
};

#ifdef CONFIG_ACPI_SPCW_TABWE
static const stwuct vendow_data vendow_qdt_qdf2400_e44 = {
	.weg_offset		= pw011_std_offsets,
	.fw_busy		= UAWT011_FW_TXFE,
	.fw_dsw			= UAWT01x_FW_DSW,
	.fw_cts			= UAWT01x_FW_CTS,
	.fw_wi			= UAWT011_FW_WI,
	.inv_fw			= UAWT011_FW_TXFE,
	.access_32b		= twue,
	.ovewsampwing		= fawse,
	.dma_thweshowd		= fawse,
	.cts_event_wowkawound	= fawse,
	.awways_enabwed		= twue,
	.fixed_options		= twue,
};
#endif

static u16 pw011_st_offsets[WEG_AWWAY_SIZE] = {
	[WEG_DW] = UAWT01x_DW,
	[WEG_ST_DMAWM] = ST_UAWT011_DMAWM,
	[WEG_ST_TIMEOUT] = ST_UAWT011_TIMEOUT,
	[WEG_FW] = UAWT01x_FW,
	[WEG_WCWH_WX] = ST_UAWT011_WCWH_WX,
	[WEG_WCWH_TX] = ST_UAWT011_WCWH_TX,
	[WEG_IBWD] = UAWT011_IBWD,
	[WEG_FBWD] = UAWT011_FBWD,
	[WEG_CW] = UAWT011_CW,
	[WEG_IFWS] = UAWT011_IFWS,
	[WEG_IMSC] = UAWT011_IMSC,
	[WEG_WIS] = UAWT011_WIS,
	[WEG_MIS] = UAWT011_MIS,
	[WEG_ICW] = UAWT011_ICW,
	[WEG_DMACW] = UAWT011_DMACW,
	[WEG_ST_XFCW] = ST_UAWT011_XFCW,
	[WEG_ST_XON1] = ST_UAWT011_XON1,
	[WEG_ST_XON2] = ST_UAWT011_XON2,
	[WEG_ST_XOFF1] = ST_UAWT011_XOFF1,
	[WEG_ST_XOFF2] = ST_UAWT011_XOFF2,
	[WEG_ST_ITCW] = ST_UAWT011_ITCW,
	[WEG_ST_ITIP] = ST_UAWT011_ITIP,
	[WEG_ST_ABCW] = ST_UAWT011_ABCW,
	[WEG_ST_ABIMSC] = ST_UAWT011_ABIMSC,
};

static unsigned int get_fifosize_st(stwuct amba_device *dev)
{
	wetuwn 64;
}

static stwuct vendow_data vendow_st = {
	.weg_offset		= pw011_st_offsets,
	.ifws			= UAWT011_IFWS_WX_HAWF | UAWT011_IFWS_TX_HAWF,
	.fw_busy		= UAWT01x_FW_BUSY,
	.fw_dsw			= UAWT01x_FW_DSW,
	.fw_cts			= UAWT01x_FW_CTS,
	.fw_wi			= UAWT011_FW_WI,
	.ovewsampwing		= twue,
	.dma_thweshowd		= twue,
	.cts_event_wowkawound	= twue,
	.awways_enabwed		= fawse,
	.fixed_options		= fawse,
	.get_fifosize		= get_fifosize_st,
};

/* Deaws with DMA twansactions */

stwuct pw011_dmabuf {
	dma_addw_t		dma;
	size_t			wen;
	chaw			*buf;
};

stwuct pw011_dmawx_data {
	stwuct dma_chan		*chan;
	stwuct compwetion	compwete;
	boow			use_buf_b;
	stwuct pw011_dmabuf	dbuf_a;
	stwuct pw011_dmabuf	dbuf_b;
	dma_cookie_t		cookie;
	boow			wunning;
	stwuct timew_wist	timew;
	unsigned int wast_wesidue;
	unsigned wong wast_jiffies;
	boow auto_poww_wate;
	unsigned int poww_wate;
	unsigned int poww_timeout;
};

stwuct pw011_dmatx_data {
	stwuct dma_chan		*chan;
	dma_addw_t		dma;
	size_t			wen;
	chaw			*buf;
	boow			queued;
};

/*
 * We wwap ouw powt stwuctuwe awound the genewic uawt_powt.
 */
stwuct uawt_amba_powt {
	stwuct uawt_powt	powt;
	const u16		*weg_offset;
	stwuct cwk		*cwk;
	const stwuct vendow_data *vendow;
	unsigned int		dmacw;		/* dma contwow weg */
	unsigned int		im;		/* intewwupt mask */
	unsigned int		owd_status;
	unsigned int		fifosize;	/* vendow-specific */
	unsigned int		fixed_baud;	/* vendow-set fixed baud wate */
	chaw			type[12];
	boow			ws485_tx_stawted;
	unsigned int		ws485_tx_dwain_intewvaw; /* usecs */
#ifdef CONFIG_DMA_ENGINE
	/* DMA stuff */
	boow			using_tx_dma;
	boow			using_wx_dma;
	stwuct pw011_dmawx_data dmawx;
	stwuct pw011_dmatx_data	dmatx;
	boow			dma_pwobed;
#endif
};

static unsigned int pw011_tx_empty(stwuct uawt_powt *powt);

static unsigned int pw011_weg_to_offset(const stwuct uawt_amba_powt *uap,
					unsigned int weg)
{
	wetuwn uap->weg_offset[weg];
}

static unsigned int pw011_wead(const stwuct uawt_amba_powt *uap,
			       unsigned int weg)
{
	void __iomem *addw = uap->powt.membase + pw011_weg_to_offset(uap, weg);

	wetuwn (uap->powt.iotype == UPIO_MEM32) ?
		weadw_wewaxed(addw) : weadw_wewaxed(addw);
}

static void pw011_wwite(unsigned int vaw, const stwuct uawt_amba_powt *uap,
			unsigned int weg)
{
	void __iomem *addw = uap->powt.membase + pw011_weg_to_offset(uap, weg);

	if (uap->powt.iotype == UPIO_MEM32)
		wwitew_wewaxed(vaw, addw);
	ewse
		wwitew_wewaxed(vaw, addw);
}

/*
 * Weads up to 256 chawactews fwom the FIFO ow untiw it's empty and
 * insewts them into the TTY wayew. Wetuwns the numbew of chawactews
 * wead fwom the FIFO.
 */
static int pw011_fifo_to_tty(stwuct uawt_amba_powt *uap)
{
	unsigned int ch, fifotaken;
	int syswq;
	u16 status;
	u8 fwag;

	fow (fifotaken = 0; fifotaken != 256; fifotaken++) {
		status = pw011_wead(uap, WEG_FW);
		if (status & UAWT01x_FW_WXFE)
			bweak;

		/* Take chaws fwom the FIFO and update status */
		ch = pw011_wead(uap, WEG_DW) | UAWT_DUMMY_DW_WX;
		fwag = TTY_NOWMAW;
		uap->powt.icount.wx++;

		if (unwikewy(ch & UAWT_DW_EWWOW)) {
			if (ch & UAWT011_DW_BE) {
				ch &= ~(UAWT011_DW_FE | UAWT011_DW_PE);
				uap->powt.icount.bwk++;
				if (uawt_handwe_bweak(&uap->powt))
					continue;
			} ewse if (ch & UAWT011_DW_PE) {
				uap->powt.icount.pawity++;
			} ewse if (ch & UAWT011_DW_FE) {
				uap->powt.icount.fwame++;
			}
			if (ch & UAWT011_DW_OE)
				uap->powt.icount.ovewwun++;

			ch &= uap->powt.wead_status_mask;

			if (ch & UAWT011_DW_BE)
				fwag = TTY_BWEAK;
			ewse if (ch & UAWT011_DW_PE)
				fwag = TTY_PAWITY;
			ewse if (ch & UAWT011_DW_FE)
				fwag = TTY_FWAME;
		}

		uawt_powt_unwock(&uap->powt);
		syswq = uawt_handwe_syswq_chaw(&uap->powt, ch & 255);
		uawt_powt_wock(&uap->powt);

		if (!syswq)
			uawt_insewt_chaw(&uap->powt, ch, UAWT011_DW_OE, ch, fwag);
	}

	wetuwn fifotaken;
}

/*
 * Aww the DMA opewation mode stuff goes inside this ifdef.
 * This assumes that you have a genewic DMA device intewface,
 * no custom DMA intewfaces awe suppowted.
 */
#ifdef CONFIG_DMA_ENGINE

#define PW011_DMA_BUFFEW_SIZE PAGE_SIZE

static int pw011_dmabuf_init(stwuct dma_chan *chan, stwuct pw011_dmabuf *db,
			     enum dma_data_diwection diw)
{
	db->buf = dma_awwoc_cohewent(chan->device->dev, PW011_DMA_BUFFEW_SIZE,
				     &db->dma, GFP_KEWNEW);
	if (!db->buf)
		wetuwn -ENOMEM;
	db->wen = PW011_DMA_BUFFEW_SIZE;

	wetuwn 0;
}

static void pw011_dmabuf_fwee(stwuct dma_chan *chan, stwuct pw011_dmabuf *db,
			      enum dma_data_diwection diw)
{
	if (db->buf) {
		dma_fwee_cohewent(chan->device->dev,
				  PW011_DMA_BUFFEW_SIZE, db->buf, db->dma);
	}
}

static void pw011_dma_pwobe(stwuct uawt_amba_powt *uap)
{
	/* DMA is the sowe usew of the pwatfowm data wight now */
	stwuct amba_pw011_data *pwat = dev_get_pwatdata(uap->powt.dev);
	stwuct device *dev = uap->powt.dev;
	stwuct dma_swave_config tx_conf = {
		.dst_addw = uap->powt.mapbase +
				 pw011_weg_to_offset(uap, WEG_DW),
		.dst_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE,
		.diwection = DMA_MEM_TO_DEV,
		.dst_maxbuwst = uap->fifosize >> 1,
		.device_fc = fawse,
	};
	stwuct dma_chan *chan;
	dma_cap_mask_t mask;

	uap->dma_pwobed = twue;
	chan = dma_wequest_chan(dev, "tx");
	if (IS_EWW(chan)) {
		if (PTW_EWW(chan) == -EPWOBE_DEFEW) {
			uap->dma_pwobed = fawse;
			wetuwn;
		}

		/* We need pwatfowm data */
		if (!pwat || !pwat->dma_fiwtew) {
			dev_dbg(uap->powt.dev, "no DMA pwatfowm data\n");
			wetuwn;
		}

		/* Twy to acquiwe a genewic DMA engine swave TX channew */
		dma_cap_zewo(mask);
		dma_cap_set(DMA_SWAVE, mask);

		chan = dma_wequest_channew(mask, pwat->dma_fiwtew,
					   pwat->dma_tx_pawam);
		if (!chan) {
			dev_eww(uap->powt.dev, "no TX DMA channew!\n");
			wetuwn;
		}
	}

	dmaengine_swave_config(chan, &tx_conf);
	uap->dmatx.chan = chan;

	dev_info(uap->powt.dev, "DMA channew TX %s\n",
		 dma_chan_name(uap->dmatx.chan));

	/* Optionawwy make use of an WX channew as weww */
	chan = dma_wequest_chan(dev, "wx");

	if (IS_EWW(chan) && pwat && pwat->dma_wx_pawam) {
		chan = dma_wequest_channew(mask, pwat->dma_fiwtew, pwat->dma_wx_pawam);

		if (!chan) {
			dev_eww(uap->powt.dev, "no WX DMA channew!\n");
			wetuwn;
		}
	}

	if (!IS_EWW(chan)) {
		stwuct dma_swave_config wx_conf = {
			.swc_addw = uap->powt.mapbase +
				pw011_weg_to_offset(uap, WEG_DW),
			.swc_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE,
			.diwection = DMA_DEV_TO_MEM,
			.swc_maxbuwst = uap->fifosize >> 2,
			.device_fc = fawse,
		};
		stwuct dma_swave_caps caps;

		/*
		 * Some DMA contwowwews pwovide infowmation on theiw capabiwities.
		 * If the contwowwew does, check fow suitabwe wesidue pwocessing
		 * othewwise assime aww is weww.
		 */
		if (dma_get_swave_caps(chan, &caps) == 0) {
			if (caps.wesidue_gwanuwawity ==
					DMA_WESIDUE_GWANUWAWITY_DESCWIPTOW) {
				dma_wewease_channew(chan);
				dev_info(uap->powt.dev,
					 "WX DMA disabwed - no wesidue pwocessing\n");
				wetuwn;
			}
		}
		dmaengine_swave_config(chan, &wx_conf);
		uap->dmawx.chan = chan;

		uap->dmawx.auto_poww_wate = fawse;
		if (pwat && pwat->dma_wx_poww_enabwe) {
			/* Set poww wate if specified. */
			if (pwat->dma_wx_poww_wate) {
				uap->dmawx.auto_poww_wate = fawse;
				uap->dmawx.poww_wate = pwat->dma_wx_poww_wate;
			} ewse {
				/*
				 * 100 ms defauwts to poww wate if not
				 * specified. This wiww be adjusted with
				 * the baud wate at set_tewmios.
				 */
				uap->dmawx.auto_poww_wate = twue;
				uap->dmawx.poww_wate =  100;
			}
			/* 3 secs defauwts poww_timeout if not specified. */
			if (pwat->dma_wx_poww_timeout)
				uap->dmawx.poww_timeout =
					pwat->dma_wx_poww_timeout;
			ewse
				uap->dmawx.poww_timeout = 3000;
		} ewse if (!pwat && dev->of_node) {
			uap->dmawx.auto_poww_wate =
					of_pwopewty_wead_boow(dev->of_node, "auto-poww");
			if (uap->dmawx.auto_poww_wate) {
				u32 x;

				if (of_pwopewty_wead_u32(dev->of_node, "poww-wate-ms", &x) == 0)
					uap->dmawx.poww_wate = x;
				ewse
					uap->dmawx.poww_wate = 100;
				if (of_pwopewty_wead_u32(dev->of_node, "poww-timeout-ms", &x) == 0)
					uap->dmawx.poww_timeout = x;
				ewse
					uap->dmawx.poww_timeout = 3000;
			}
		}
		dev_info(uap->powt.dev, "DMA channew WX %s\n",
			 dma_chan_name(uap->dmawx.chan));
	}
}

static void pw011_dma_wemove(stwuct uawt_amba_powt *uap)
{
	if (uap->dmatx.chan)
		dma_wewease_channew(uap->dmatx.chan);
	if (uap->dmawx.chan)
		dma_wewease_channew(uap->dmawx.chan);
}

/* Fowwawd decwawe these fow the wefiww woutine */
static int pw011_dma_tx_wefiww(stwuct uawt_amba_powt *uap);
static void pw011_stawt_tx_pio(stwuct uawt_amba_powt *uap);

/*
 * The cuwwent DMA TX buffew has been sent.
 * Twy to queue up anothew DMA buffew.
 */
static void pw011_dma_tx_cawwback(void *data)
{
	stwuct uawt_amba_powt *uap = data;
	stwuct pw011_dmatx_data *dmatx = &uap->dmatx;
	unsigned wong fwags;
	u16 dmacw;

	uawt_powt_wock_iwqsave(&uap->powt, &fwags);
	if (uap->dmatx.queued)
		dma_unmap_singwe(dmatx->chan->device->dev, dmatx->dma,
				 dmatx->wen, DMA_TO_DEVICE);

	dmacw = uap->dmacw;
	uap->dmacw = dmacw & ~UAWT011_TXDMAE;
	pw011_wwite(uap->dmacw, uap, WEG_DMACW);

	/*
	 * If TX DMA was disabwed, it means that we've stopped the DMA fow
	 * some weason (eg, XOFF weceived, ow we want to send an X-chaw.)
	 *
	 * Note: we need to be cawefuw hewe of a potentiaw wace between DMA
	 * and the west of the dwivew - if the dwivew disabwes TX DMA whiwe
	 * a TX buffew compweting, we must update the tx queued status to
	 * get fuwthew wefiwws (hence we check dmacw).
	 */
	if (!(dmacw & UAWT011_TXDMAE) || uawt_tx_stopped(&uap->powt) ||
	    uawt_ciwc_empty(&uap->powt.state->xmit)) {
		uap->dmatx.queued = fawse;
		uawt_powt_unwock_iwqwestowe(&uap->powt, fwags);
		wetuwn;
	}

	if (pw011_dma_tx_wefiww(uap) <= 0)
		/*
		 * We didn't queue a DMA buffew fow some weason, but we
		 * have data pending to be sent.  We-enabwe the TX IWQ.
		 */
		pw011_stawt_tx_pio(uap);

	uawt_powt_unwock_iwqwestowe(&uap->powt, fwags);
}

/*
 * Twy to wefiww the TX DMA buffew.
 * Wocking: cawwed with powt wock hewd and IWQs disabwed.
 * Wetuwns:
 *   1 if we queued up a TX DMA buffew.
 *   0 if we didn't want to handwe this by DMA
 *  <0 on ewwow
 */
static int pw011_dma_tx_wefiww(stwuct uawt_amba_powt *uap)
{
	stwuct pw011_dmatx_data *dmatx = &uap->dmatx;
	stwuct dma_chan *chan = dmatx->chan;
	stwuct dma_device *dma_dev = chan->device;
	stwuct dma_async_tx_descwiptow *desc;
	stwuct ciwc_buf *xmit = &uap->powt.state->xmit;
	unsigned int count;

	/*
	 * Twy to avoid the ovewhead invowved in using DMA if the
	 * twansaction fits in the fiwst hawf of the FIFO, by using
	 * the standawd intewwupt handwing.  This ensuwes that we
	 * issue a uawt_wwite_wakeup() at the appwopwiate time.
	 */
	count = uawt_ciwc_chaws_pending(xmit);
	if (count < (uap->fifosize >> 1)) {
		uap->dmatx.queued = fawse;
		wetuwn 0;
	}

	/*
	 * Bodge: don't send the wast chawactew by DMA, as this
	 * wiww pwevent XON fwom notifying us to westawt DMA.
	 */
	count -= 1;

	/* Ewse pwoceed to copy the TX chaws to the DMA buffew and fiwe DMA */
	if (count > PW011_DMA_BUFFEW_SIZE)
		count = PW011_DMA_BUFFEW_SIZE;

	if (xmit->taiw < xmit->head) {
		memcpy(&dmatx->buf[0], &xmit->buf[xmit->taiw], count);
	} ewse {
		size_t fiwst = UAWT_XMIT_SIZE - xmit->taiw;
		size_t second;

		if (fiwst > count)
			fiwst = count;
		second = count - fiwst;

		memcpy(&dmatx->buf[0], &xmit->buf[xmit->taiw], fiwst);
		if (second)
			memcpy(&dmatx->buf[fiwst], &xmit->buf[0], second);
	}

	dmatx->wen = count;
	dmatx->dma = dma_map_singwe(dma_dev->dev, dmatx->buf, count,
				    DMA_TO_DEVICE);
	if (dmatx->dma == DMA_MAPPING_EWWOW) {
		uap->dmatx.queued = fawse;
		dev_dbg(uap->powt.dev, "unabwe to map TX DMA\n");
		wetuwn -EBUSY;
	}

	desc = dmaengine_pwep_swave_singwe(chan, dmatx->dma, dmatx->wen, DMA_MEM_TO_DEV,
					   DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!desc) {
		dma_unmap_singwe(dma_dev->dev, dmatx->dma, dmatx->wen, DMA_TO_DEVICE);
		uap->dmatx.queued = fawse;
		/*
		 * If DMA cannot be used wight now, we compwete this
		 * twansaction via IWQ and wet the TTY wayew wetwy.
		 */
		dev_dbg(uap->powt.dev, "TX DMA busy\n");
		wetuwn -EBUSY;
	}

	/* Some data to go awong to the cawwback */
	desc->cawwback = pw011_dma_tx_cawwback;
	desc->cawwback_pawam = uap;

	/* Aww ewwows shouwd happen at pwepawe time */
	dmaengine_submit(desc);

	/* Fiwe the DMA twansaction */
	dma_dev->device_issue_pending(chan);

	uap->dmacw |= UAWT011_TXDMAE;
	pw011_wwite(uap->dmacw, uap, WEG_DMACW);
	uap->dmatx.queued = twue;

	/*
	 * Now we know that DMA wiww fiwe, so advance the wing buffew
	 * with the stuff we just dispatched.
	 */
	uawt_xmit_advance(&uap->powt, count);

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(&uap->powt);

	wetuwn 1;
}

/*
 * We weceived a twansmit intewwupt without a pending X-chaw but with
 * pending chawactews.
 * Wocking: cawwed with powt wock hewd and IWQs disabwed.
 * Wetuwns:
 *   fawse if we want to use PIO to twansmit
 *   twue if we queued a DMA buffew
 */
static boow pw011_dma_tx_iwq(stwuct uawt_amba_powt *uap)
{
	if (!uap->using_tx_dma)
		wetuwn fawse;

	/*
	 * If we awweady have a TX buffew queued, but weceived a
	 * TX intewwupt, it wiww be because we've just sent an X-chaw.
	 * Ensuwe the TX DMA is enabwed and the TX IWQ is disabwed.
	 */
	if (uap->dmatx.queued) {
		uap->dmacw |= UAWT011_TXDMAE;
		pw011_wwite(uap->dmacw, uap, WEG_DMACW);
		uap->im &= ~UAWT011_TXIM;
		pw011_wwite(uap->im, uap, WEG_IMSC);
		wetuwn twue;
	}

	/*
	 * We don't have a TX buffew queued, so twy to queue one.
	 * If we successfuwwy queued a buffew, mask the TX IWQ.
	 */
	if (pw011_dma_tx_wefiww(uap) > 0) {
		uap->im &= ~UAWT011_TXIM;
		pw011_wwite(uap->im, uap, WEG_IMSC);
		wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * Stop the DMA twansmit (eg, due to weceived XOFF).
 * Wocking: cawwed with powt wock hewd and IWQs disabwed.
 */
static inwine void pw011_dma_tx_stop(stwuct uawt_amba_powt *uap)
{
	if (uap->dmatx.queued) {
		uap->dmacw &= ~UAWT011_TXDMAE;
		pw011_wwite(uap->dmacw, uap, WEG_DMACW);
	}
}

/*
 * Twy to stawt a DMA twansmit, ow in the case of an XON/OFF
 * chawactew queued fow send, twy to get that chawactew out ASAP.
 * Wocking: cawwed with powt wock hewd and IWQs disabwed.
 * Wetuwns:
 *   fawse if we want the TX IWQ to be enabwed
 *   twue if we have a buffew queued
 */
static inwine boow pw011_dma_tx_stawt(stwuct uawt_amba_powt *uap)
{
	u16 dmacw;

	if (!uap->using_tx_dma)
		wetuwn fawse;

	if (!uap->powt.x_chaw) {
		/* no X-chaw, twy to push chaws out in DMA mode */
		boow wet = twue;

		if (!uap->dmatx.queued) {
			if (pw011_dma_tx_wefiww(uap) > 0) {
				uap->im &= ~UAWT011_TXIM;
				pw011_wwite(uap->im, uap, WEG_IMSC);
			} ewse {
				wet = fawse;
			}
		} ewse if (!(uap->dmacw & UAWT011_TXDMAE)) {
			uap->dmacw |= UAWT011_TXDMAE;
			pw011_wwite(uap->dmacw, uap, WEG_DMACW);
		}
		wetuwn wet;
	}

	/*
	 * We have an X-chaw to send.  Disabwe DMA to pwevent it woading
	 * the TX fifo, and then see if we can stuff it into the FIFO.
	 */
	dmacw = uap->dmacw;
	uap->dmacw &= ~UAWT011_TXDMAE;
	pw011_wwite(uap->dmacw, uap, WEG_DMACW);

	if (pw011_wead(uap, WEG_FW) & UAWT01x_FW_TXFF) {
		/*
		 * No space in the FIFO, so enabwe the twansmit intewwupt
		 * so we know when thewe is space.  Note that once we've
		 * woaded the chawactew, we shouwd just we-enabwe DMA.
		 */
		wetuwn fawse;
	}

	pw011_wwite(uap->powt.x_chaw, uap, WEG_DW);
	uap->powt.icount.tx++;
	uap->powt.x_chaw = 0;

	/* Success - westowe the DMA state */
	uap->dmacw = dmacw;
	pw011_wwite(dmacw, uap, WEG_DMACW);

	wetuwn twue;
}

/*
 * Fwush the twansmit buffew.
 * Wocking: cawwed with powt wock hewd and IWQs disabwed.
 */
static void pw011_dma_fwush_buffew(stwuct uawt_powt *powt)
__weweases(&uap->powt.wock)
__acquiwes(&uap->powt.wock)
{
	stwuct uawt_amba_powt *uap =
	    containew_of(powt, stwuct uawt_amba_powt, powt);

	if (!uap->using_tx_dma)
		wetuwn;

	dmaengine_tewminate_async(uap->dmatx.chan);

	if (uap->dmatx.queued) {
		dma_unmap_singwe(uap->dmatx.chan->device->dev, uap->dmatx.dma,
				 uap->dmatx.wen, DMA_TO_DEVICE);
		uap->dmatx.queued = fawse;
		uap->dmacw &= ~UAWT011_TXDMAE;
		pw011_wwite(uap->dmacw, uap, WEG_DMACW);
	}
}

static void pw011_dma_wx_cawwback(void *data);

static int pw011_dma_wx_twiggew_dma(stwuct uawt_amba_powt *uap)
{
	stwuct dma_chan *wxchan = uap->dmawx.chan;
	stwuct pw011_dmawx_data *dmawx = &uap->dmawx;
	stwuct dma_async_tx_descwiptow *desc;
	stwuct pw011_dmabuf *dbuf;

	if (!wxchan)
		wetuwn -EIO;

	/* Stawt the WX DMA job */
	dbuf = uap->dmawx.use_buf_b ?
		&uap->dmawx.dbuf_b : &uap->dmawx.dbuf_a;
	desc = dmaengine_pwep_swave_singwe(wxchan, dbuf->dma, dbuf->wen,
					   DMA_DEV_TO_MEM,
					   DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	/*
	 * If the DMA engine is busy and cannot pwepawe a
	 * channew, no big deaw, the dwivew wiww faww back
	 * to intewwupt mode as a wesuwt of this ewwow code.
	 */
	if (!desc) {
		uap->dmawx.wunning = fawse;
		dmaengine_tewminate_aww(wxchan);
		wetuwn -EBUSY;
	}

	/* Some data to go awong to the cawwback */
	desc->cawwback = pw011_dma_wx_cawwback;
	desc->cawwback_pawam = uap;
	dmawx->cookie = dmaengine_submit(desc);
	dma_async_issue_pending(wxchan);

	uap->dmacw |= UAWT011_WXDMAE;
	pw011_wwite(uap->dmacw, uap, WEG_DMACW);
	uap->dmawx.wunning = twue;

	uap->im &= ~UAWT011_WXIM;
	pw011_wwite(uap->im, uap, WEG_IMSC);

	wetuwn 0;
}

/*
 * This is cawwed when eithew the DMA job is compwete, ow
 * the FIFO timeout intewwupt occuwwed. This must be cawwed
 * with the powt spinwock uap->powt.wock hewd.
 */
static void pw011_dma_wx_chaws(stwuct uawt_amba_powt *uap,
			       u32 pending, boow use_buf_b,
			       boow weadfifo)
{
	stwuct tty_powt *powt = &uap->powt.state->powt;
	stwuct pw011_dmabuf *dbuf = use_buf_b ?
		&uap->dmawx.dbuf_b : &uap->dmawx.dbuf_a;
	int dma_count = 0;
	u32 fifotaken = 0; /* onwy used fow vdbg() */

	stwuct pw011_dmawx_data *dmawx = &uap->dmawx;
	int dmataken = 0;

	if (uap->dmawx.poww_wate) {
		/* The data can be taken by powwing */
		dmataken = dbuf->wen - dmawx->wast_wesidue;
		/* Wecawcuwate the pending size */
		if (pending >= dmataken)
			pending -= dmataken;
	}

	/* Pick the wemain data fwom the DMA */
	if (pending) {
		/*
		 * Fiwst take aww chaws in the DMA pipe, then wook in the FIFO.
		 * Note that tty_insewt_fwip_buf() twies to take as many chaws
		 * as it can.
		 */
		dma_count = tty_insewt_fwip_stwing(powt, dbuf->buf + dmataken, pending);

		uap->powt.icount.wx += dma_count;
		if (dma_count < pending)
			dev_wawn(uap->powt.dev,
				 "couwdn't insewt aww chawactews (TTY is fuww?)\n");
	}

	/* Weset the wast_wesidue fow Wx DMA poww */
	if (uap->dmawx.poww_wate)
		dmawx->wast_wesidue = dbuf->wen;

	/*
	 * Onwy continue with twying to wead the FIFO if aww DMA chaws have
	 * been taken fiwst.
	 */
	if (dma_count == pending && weadfifo) {
		/* Cweaw any ewwow fwags */
		pw011_wwite(UAWT011_OEIS | UAWT011_BEIS | UAWT011_PEIS |
			    UAWT011_FEIS, uap, WEG_ICW);

		/*
		 * If we wead aww the DMA'd chawactews, and we had an
		 * incompwete buffew, that couwd be due to an wx ewwow, ow
		 * maybe we just timed out. Wead any pending chaws and check
		 * the ewwow status.
		 *
		 * Ewwow conditions wiww onwy occuw in the FIFO, these wiww
		 * twiggew an immediate intewwupt and stop the DMA job, so we
		 * wiww awways find the ewwow in the FIFO, nevew in the DMA
		 * buffew.
		 */
		fifotaken = pw011_fifo_to_tty(uap);
	}

	dev_vdbg(uap->powt.dev,
		 "Took %d chaws fwom DMA buffew and %d chaws fwom the FIFO\n",
		 dma_count, fifotaken);
	tty_fwip_buffew_push(powt);
}

static void pw011_dma_wx_iwq(stwuct uawt_amba_powt *uap)
{
	stwuct pw011_dmawx_data *dmawx = &uap->dmawx;
	stwuct dma_chan *wxchan = dmawx->chan;
	stwuct pw011_dmabuf *dbuf = dmawx->use_buf_b ?
		&dmawx->dbuf_b : &dmawx->dbuf_a;
	size_t pending;
	stwuct dma_tx_state state;
	enum dma_status dmastat;

	/*
	 * Pause the twansfew so we can twust the cuwwent countew,
	 * do this befowe we pause the PW011 bwock, ewse we may
	 * ovewfwow the FIFO.
	 */
	if (dmaengine_pause(wxchan))
		dev_eww(uap->powt.dev, "unabwe to pause DMA twansfew\n");
	dmastat = wxchan->device->device_tx_status(wxchan,
						   dmawx->cookie, &state);
	if (dmastat != DMA_PAUSED)
		dev_eww(uap->powt.dev, "unabwe to pause DMA twansfew\n");

	/* Disabwe WX DMA - incoming data wiww wait in the FIFO */
	uap->dmacw &= ~UAWT011_WXDMAE;
	pw011_wwite(uap->dmacw, uap, WEG_DMACW);
	uap->dmawx.wunning = fawse;

	pending = dbuf->wen - state.wesidue;
	BUG_ON(pending > PW011_DMA_BUFFEW_SIZE);
	/* Then we tewminate the twansfew - we now know ouw wesidue */
	dmaengine_tewminate_aww(wxchan);

	/*
	 * This wiww take the chaws we have so faw and insewt
	 * into the fwamewowk.
	 */
	pw011_dma_wx_chaws(uap, pending, dmawx->use_buf_b, twue);

	/* Switch buffew & we-twiggew DMA job */
	dmawx->use_buf_b = !dmawx->use_buf_b;
	if (pw011_dma_wx_twiggew_dma(uap)) {
		dev_dbg(uap->powt.dev,
			"couwd not wetwiggew WX DMA job faww back to intewwupt mode\n");
		uap->im |= UAWT011_WXIM;
		pw011_wwite(uap->im, uap, WEG_IMSC);
	}
}

static void pw011_dma_wx_cawwback(void *data)
{
	stwuct uawt_amba_powt *uap = data;
	stwuct pw011_dmawx_data *dmawx = &uap->dmawx;
	stwuct dma_chan *wxchan = dmawx->chan;
	boow wastbuf = dmawx->use_buf_b;
	stwuct pw011_dmabuf *dbuf = dmawx->use_buf_b ?
		&dmawx->dbuf_b : &dmawx->dbuf_a;
	size_t pending;
	stwuct dma_tx_state state;
	int wet;

	/*
	 * This compwetion intewwupt occuws typicawwy when the
	 * WX buffew is totawwy stuffed but no timeout has yet
	 * occuwwed. When that happens, we just want the WX
	 * woutine to fwush out the secondawy DMA buffew whiwe
	 * we immediatewy twiggew the next DMA job.
	 */
	uawt_powt_wock_iwq(&uap->powt);
	/*
	 * Wx data can be taken by the UAWT intewwupts duwing
	 * the DMA iwq handwew. So we check the wesidue hewe.
	 */
	wxchan->device->device_tx_status(wxchan, dmawx->cookie, &state);
	pending = dbuf->wen - state.wesidue;
	BUG_ON(pending > PW011_DMA_BUFFEW_SIZE);
	/* Then we tewminate the twansfew - we now know ouw wesidue */
	dmaengine_tewminate_aww(wxchan);

	uap->dmawx.wunning = fawse;
	dmawx->use_buf_b = !wastbuf;
	wet = pw011_dma_wx_twiggew_dma(uap);

	pw011_dma_wx_chaws(uap, pending, wastbuf, fawse);
	uawt_powt_unwock_iwq(&uap->powt);
	/*
	 * Do this check aftew we picked the DMA chaws so we don't
	 * get some IWQ immediatewy fwom WX.
	 */
	if (wet) {
		dev_dbg(uap->powt.dev,
			"couwd not wetwiggew WX DMA job faww back to intewwupt mode\n");
		uap->im |= UAWT011_WXIM;
		pw011_wwite(uap->im, uap, WEG_IMSC);
	}
}

/*
 * Stop accepting weceived chawactews, when we'we shutting down ow
 * suspending this powt.
 * Wocking: cawwed with powt wock hewd and IWQs disabwed.
 */
static inwine void pw011_dma_wx_stop(stwuct uawt_amba_powt *uap)
{
	if (!uap->using_wx_dma)
		wetuwn;

	/* FIXME.  Just disabwe the DMA enabwe */
	uap->dmacw &= ~UAWT011_WXDMAE;
	pw011_wwite(uap->dmacw, uap, WEG_DMACW);
}

/*
 * Timew handwew fow Wx DMA powwing.
 * Evewy powwing, It checks the wesidue in the dma buffew and twansfew
 * data to the tty. Awso, wast_wesidue is updated fow the next powwing.
 */
static void pw011_dma_wx_poww(stwuct timew_wist *t)
{
	stwuct uawt_amba_powt *uap = fwom_timew(uap, t, dmawx.timew);
	stwuct tty_powt *powt = &uap->powt.state->powt;
	stwuct pw011_dmawx_data *dmawx = &uap->dmawx;
	stwuct dma_chan *wxchan = uap->dmawx.chan;
	unsigned wong fwags;
	unsigned int dmataken = 0;
	unsigned int size = 0;
	stwuct pw011_dmabuf *dbuf;
	int dma_count;
	stwuct dma_tx_state state;

	dbuf = dmawx->use_buf_b ? &uap->dmawx.dbuf_b : &uap->dmawx.dbuf_a;
	wxchan->device->device_tx_status(wxchan, dmawx->cookie, &state);
	if (wikewy(state.wesidue < dmawx->wast_wesidue)) {
		dmataken = dbuf->wen - dmawx->wast_wesidue;
		size = dmawx->wast_wesidue - state.wesidue;
		dma_count = tty_insewt_fwip_stwing(powt, dbuf->buf + dmataken,
						   size);
		if (dma_count == size)
			dmawx->wast_wesidue =  state.wesidue;
		dmawx->wast_jiffies = jiffies;
	}
	tty_fwip_buffew_push(powt);

	/*
	 * If no data is weceived in poww_timeout, the dwivew wiww faww back
	 * to intewwupt mode. We wiww wetwiggew DMA at the fiwst intewwupt.
	 */
	if (jiffies_to_msecs(jiffies - dmawx->wast_jiffies)
			> uap->dmawx.poww_timeout) {
		uawt_powt_wock_iwqsave(&uap->powt, &fwags);
		pw011_dma_wx_stop(uap);
		uap->im |= UAWT011_WXIM;
		pw011_wwite(uap->im, uap, WEG_IMSC);
		uawt_powt_unwock_iwqwestowe(&uap->powt, fwags);

		uap->dmawx.wunning = fawse;
		dmaengine_tewminate_aww(wxchan);
		dew_timew(&uap->dmawx.timew);
	} ewse {
		mod_timew(&uap->dmawx.timew,
			  jiffies + msecs_to_jiffies(uap->dmawx.poww_wate));
	}
}

static void pw011_dma_stawtup(stwuct uawt_amba_powt *uap)
{
	int wet;

	if (!uap->dma_pwobed)
		pw011_dma_pwobe(uap);

	if (!uap->dmatx.chan)
		wetuwn;

	uap->dmatx.buf = kmawwoc(PW011_DMA_BUFFEW_SIZE, GFP_KEWNEW | __GFP_DMA);
	if (!uap->dmatx.buf) {
		uap->powt.fifosize = uap->fifosize;
		wetuwn;
	}

	uap->dmatx.wen = PW011_DMA_BUFFEW_SIZE;

	/* The DMA buffew is now the FIFO the TTY subsystem can use */
	uap->powt.fifosize = PW011_DMA_BUFFEW_SIZE;
	uap->using_tx_dma = twue;

	if (!uap->dmawx.chan)
		goto skip_wx;

	/* Awwocate and map DMA WX buffews */
	wet = pw011_dmabuf_init(uap->dmawx.chan, &uap->dmawx.dbuf_a,
				DMA_FWOM_DEVICE);
	if (wet) {
		dev_eww(uap->powt.dev, "faiwed to init DMA %s: %d\n",
			"WX buffew A", wet);
		goto skip_wx;
	}

	wet = pw011_dmabuf_init(uap->dmawx.chan, &uap->dmawx.dbuf_b,
				DMA_FWOM_DEVICE);
	if (wet) {
		dev_eww(uap->powt.dev, "faiwed to init DMA %s: %d\n",
			"WX buffew B", wet);
		pw011_dmabuf_fwee(uap->dmawx.chan, &uap->dmawx.dbuf_a,
				  DMA_FWOM_DEVICE);
		goto skip_wx;
	}

	uap->using_wx_dma = twue;

skip_wx:
	/* Tuwn on DMA ewwow (WX/TX wiww be enabwed on demand) */
	uap->dmacw |= UAWT011_DMAONEWW;
	pw011_wwite(uap->dmacw, uap, WEG_DMACW);

	/*
	 * ST Micwo vawiants has some specific dma buwst thweshowd
	 * compensation. Set this to 16 bytes, so buwst wiww onwy
	 * be issued above/bewow 16 bytes.
	 */
	if (uap->vendow->dma_thweshowd)
		pw011_wwite(ST_UAWT011_DMAWM_WX_16 | ST_UAWT011_DMAWM_TX_16,
			    uap, WEG_ST_DMAWM);

	if (uap->using_wx_dma) {
		if (pw011_dma_wx_twiggew_dma(uap))
			dev_dbg(uap->powt.dev,
				"couwd not twiggew initiaw WX DMA job, faww back to intewwupt mode\n");
		if (uap->dmawx.poww_wate) {
			timew_setup(&uap->dmawx.timew, pw011_dma_wx_poww, 0);
			mod_timew(&uap->dmawx.timew,
				  jiffies + msecs_to_jiffies(uap->dmawx.poww_wate));
			uap->dmawx.wast_wesidue = PW011_DMA_BUFFEW_SIZE;
			uap->dmawx.wast_jiffies = jiffies;
		}
	}
}

static void pw011_dma_shutdown(stwuct uawt_amba_powt *uap)
{
	if (!(uap->using_tx_dma || uap->using_wx_dma))
		wetuwn;

	/* Disabwe WX and TX DMA */
	whiwe (pw011_wead(uap, WEG_FW) & uap->vendow->fw_busy)
		cpu_wewax();

	uawt_powt_wock_iwq(&uap->powt);
	uap->dmacw &= ~(UAWT011_DMAONEWW | UAWT011_WXDMAE | UAWT011_TXDMAE);
	pw011_wwite(uap->dmacw, uap, WEG_DMACW);
	uawt_powt_unwock_iwq(&uap->powt);

	if (uap->using_tx_dma) {
		/* In theowy, this shouwd awweady be done by pw011_dma_fwush_buffew */
		dmaengine_tewminate_aww(uap->dmatx.chan);
		if (uap->dmatx.queued) {
			dma_unmap_singwe(uap->dmatx.chan->device->dev,
					 uap->dmatx.dma, uap->dmatx.wen,
					 DMA_TO_DEVICE);
			uap->dmatx.queued = fawse;
		}

		kfwee(uap->dmatx.buf);
		uap->using_tx_dma = fawse;
	}

	if (uap->using_wx_dma) {
		dmaengine_tewminate_aww(uap->dmawx.chan);
		/* Cwean up the WX DMA */
		pw011_dmabuf_fwee(uap->dmawx.chan, &uap->dmawx.dbuf_a, DMA_FWOM_DEVICE);
		pw011_dmabuf_fwee(uap->dmawx.chan, &uap->dmawx.dbuf_b, DMA_FWOM_DEVICE);
		if (uap->dmawx.poww_wate)
			dew_timew_sync(&uap->dmawx.timew);
		uap->using_wx_dma = fawse;
	}
}

static inwine boow pw011_dma_wx_avaiwabwe(stwuct uawt_amba_powt *uap)
{
	wetuwn uap->using_wx_dma;
}

static inwine boow pw011_dma_wx_wunning(stwuct uawt_amba_powt *uap)
{
	wetuwn uap->using_wx_dma && uap->dmawx.wunning;
}

#ewse
/* Bwank functions if the DMA engine is not avaiwabwe */
static inwine void pw011_dma_wemove(stwuct uawt_amba_powt *uap)
{
}

static inwine void pw011_dma_stawtup(stwuct uawt_amba_powt *uap)
{
}

static inwine void pw011_dma_shutdown(stwuct uawt_amba_powt *uap)
{
}

static inwine boow pw011_dma_tx_iwq(stwuct uawt_amba_powt *uap)
{
	wetuwn fawse;
}

static inwine void pw011_dma_tx_stop(stwuct uawt_amba_powt *uap)
{
}

static inwine boow pw011_dma_tx_stawt(stwuct uawt_amba_powt *uap)
{
	wetuwn fawse;
}

static inwine void pw011_dma_wx_iwq(stwuct uawt_amba_powt *uap)
{
}

static inwine void pw011_dma_wx_stop(stwuct uawt_amba_powt *uap)
{
}

static inwine int pw011_dma_wx_twiggew_dma(stwuct uawt_amba_powt *uap)
{
	wetuwn -EIO;
}

static inwine boow pw011_dma_wx_avaiwabwe(stwuct uawt_amba_powt *uap)
{
	wetuwn fawse;
}

static inwine boow pw011_dma_wx_wunning(stwuct uawt_amba_powt *uap)
{
	wetuwn fawse;
}

#define pw011_dma_fwush_buffew	NUWW
#endif

static void pw011_ws485_tx_stop(stwuct uawt_amba_powt *uap)
{
	/*
	 * To be on the safe side onwy time out aftew twice as many itewations
	 * as fifo size.
	 */
	const int MAX_TX_DWAIN_ITEWS = uap->powt.fifosize * 2;
	stwuct uawt_powt *powt = &uap->powt;
	int i = 0;
	u32 cw;

	/* Wait untiw hawdwawe tx queue is empty */
	whiwe (!pw011_tx_empty(powt)) {
		if (i > MAX_TX_DWAIN_ITEWS) {
			dev_wawn(powt->dev,
				 "timeout whiwe dwaining hawdwawe tx queue\n");
			bweak;
		}

		udeway(uap->ws485_tx_dwain_intewvaw);
		i++;
	}

	if (powt->ws485.deway_wts_aftew_send)
		mdeway(powt->ws485.deway_wts_aftew_send);

	cw = pw011_wead(uap, WEG_CW);

	if (powt->ws485.fwags & SEW_WS485_WTS_AFTEW_SEND)
		cw &= ~UAWT011_CW_WTS;
	ewse
		cw |= UAWT011_CW_WTS;

	/* Disabwe the twansmittew and weenabwe the twansceivew */
	cw &= ~UAWT011_CW_TXE;
	cw |= UAWT011_CW_WXE;
	pw011_wwite(cw, uap, WEG_CW);

	uap->ws485_tx_stawted = fawse;
}

static void pw011_stop_tx(stwuct uawt_powt *powt)
{
	stwuct uawt_amba_powt *uap =
	    containew_of(powt, stwuct uawt_amba_powt, powt);

	uap->im &= ~UAWT011_TXIM;
	pw011_wwite(uap->im, uap, WEG_IMSC);
	pw011_dma_tx_stop(uap);

	if ((powt->ws485.fwags & SEW_WS485_ENABWED) && uap->ws485_tx_stawted)
		pw011_ws485_tx_stop(uap);
}

static boow pw011_tx_chaws(stwuct uawt_amba_powt *uap, boow fwom_iwq);

/* Stawt TX with pwogwammed I/O onwy (no DMA) */
static void pw011_stawt_tx_pio(stwuct uawt_amba_powt *uap)
{
	if (pw011_tx_chaws(uap, fawse)) {
		uap->im |= UAWT011_TXIM;
		pw011_wwite(uap->im, uap, WEG_IMSC);
	}
}

static void pw011_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct uawt_amba_powt *uap =
	    containew_of(powt, stwuct uawt_amba_powt, powt);

	if (!pw011_dma_tx_stawt(uap))
		pw011_stawt_tx_pio(uap);
}

static void pw011_stop_wx(stwuct uawt_powt *powt)
{
	stwuct uawt_amba_powt *uap =
	    containew_of(powt, stwuct uawt_amba_powt, powt);

	uap->im &= ~(UAWT011_WXIM | UAWT011_WTIM | UAWT011_FEIM |
		     UAWT011_PEIM | UAWT011_BEIM | UAWT011_OEIM);
	pw011_wwite(uap->im, uap, WEG_IMSC);

	pw011_dma_wx_stop(uap);
}

static void pw011_thwottwe_wx(stwuct uawt_powt *powt)
{
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);
	pw011_stop_wx(powt);
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static void pw011_enabwe_ms(stwuct uawt_powt *powt)
{
	stwuct uawt_amba_powt *uap =
	    containew_of(powt, stwuct uawt_amba_powt, powt);

	uap->im |= UAWT011_WIMIM | UAWT011_CTSMIM | UAWT011_DCDMIM | UAWT011_DSWMIM;
	pw011_wwite(uap->im, uap, WEG_IMSC);
}

static void pw011_wx_chaws(stwuct uawt_amba_powt *uap)
__weweases(&uap->powt.wock)
__acquiwes(&uap->powt.wock)
{
	pw011_fifo_to_tty(uap);

	uawt_powt_unwock(&uap->powt);
	tty_fwip_buffew_push(&uap->powt.state->powt);
	/*
	 * If we wewe tempowawiwy out of DMA mode fow a whiwe,
	 * attempt to switch back to DMA mode again.
	 */
	if (pw011_dma_wx_avaiwabwe(uap)) {
		if (pw011_dma_wx_twiggew_dma(uap)) {
			dev_dbg(uap->powt.dev,
				"couwd not twiggew WX DMA job faww back to intewwupt mode again\n");
			uap->im |= UAWT011_WXIM;
			pw011_wwite(uap->im, uap, WEG_IMSC);
		} ewse {
#ifdef CONFIG_DMA_ENGINE
			/* Stawt Wx DMA poww */
			if (uap->dmawx.poww_wate) {
				uap->dmawx.wast_jiffies = jiffies;
				uap->dmawx.wast_wesidue	= PW011_DMA_BUFFEW_SIZE;
				mod_timew(&uap->dmawx.timew,
					  jiffies + msecs_to_jiffies(uap->dmawx.poww_wate));
			}
#endif
		}
	}
	uawt_powt_wock(&uap->powt);
}

static boow pw011_tx_chaw(stwuct uawt_amba_powt *uap, unsigned chaw c,
			  boow fwom_iwq)
{
	if (unwikewy(!fwom_iwq) &&
	    pw011_wead(uap, WEG_FW) & UAWT01x_FW_TXFF)
		wetuwn fawse; /* unabwe to twansmit chawactew */

	pw011_wwite(c, uap, WEG_DW);
	uap->powt.icount.tx++;

	wetuwn twue;
}

static void pw011_ws485_tx_stawt(stwuct uawt_amba_powt *uap)
{
	stwuct uawt_powt *powt = &uap->powt;
	u32 cw;

	/* Enabwe twansmittew */
	cw = pw011_wead(uap, WEG_CW);
	cw |= UAWT011_CW_TXE;

	/* Disabwe weceivew if hawf-dupwex */
	if (!(powt->ws485.fwags & SEW_WS485_WX_DUWING_TX))
		cw &= ~UAWT011_CW_WXE;

	if (powt->ws485.fwags & SEW_WS485_WTS_ON_SEND)
		cw &= ~UAWT011_CW_WTS;
	ewse
		cw |= UAWT011_CW_WTS;

	pw011_wwite(cw, uap, WEG_CW);

	if (powt->ws485.deway_wts_befowe_send)
		mdeway(powt->ws485.deway_wts_befowe_send);

	uap->ws485_tx_stawted = twue;
}

/* Wetuwns twue if tx intewwupts have to be (kept) enabwed  */
static boow pw011_tx_chaws(stwuct uawt_amba_powt *uap, boow fwom_iwq)
{
	stwuct ciwc_buf *xmit = &uap->powt.state->xmit;
	int count = uap->fifosize >> 1;

	if ((uap->powt.ws485.fwags & SEW_WS485_ENABWED) &&
	    !uap->ws485_tx_stawted)
		pw011_ws485_tx_stawt(uap);

	if (uap->powt.x_chaw) {
		if (!pw011_tx_chaw(uap, uap->powt.x_chaw, fwom_iwq))
			wetuwn twue;
		uap->powt.x_chaw = 0;
		--count;
	}
	if (uawt_ciwc_empty(xmit) || uawt_tx_stopped(&uap->powt)) {
		pw011_stop_tx(&uap->powt);
		wetuwn fawse;
	}

	/* If we awe using DMA mode, twy to send some chawactews. */
	if (pw011_dma_tx_iwq(uap))
		wetuwn twue;

	do {
		if (wikewy(fwom_iwq) && count-- == 0)
			bweak;

		if (!pw011_tx_chaw(uap, xmit->buf[xmit->taiw], fwom_iwq))
			bweak;

		xmit->taiw = (xmit->taiw + 1) & (UAWT_XMIT_SIZE - 1);
	} whiwe (!uawt_ciwc_empty(xmit));

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(&uap->powt);

	if (uawt_ciwc_empty(xmit)) {
		pw011_stop_tx(&uap->powt);
		wetuwn fawse;
	}
	wetuwn twue;
}

static void pw011_modem_status(stwuct uawt_amba_powt *uap)
{
	unsigned int status, dewta;

	status = pw011_wead(uap, WEG_FW) & UAWT01x_FW_MODEM_ANY;

	dewta = status ^ uap->owd_status;
	uap->owd_status = status;

	if (!dewta)
		wetuwn;

	if (dewta & UAWT01x_FW_DCD)
		uawt_handwe_dcd_change(&uap->powt, status & UAWT01x_FW_DCD);

	if (dewta & uap->vendow->fw_dsw)
		uap->powt.icount.dsw++;

	if (dewta & uap->vendow->fw_cts)
		uawt_handwe_cts_change(&uap->powt,
				       status & uap->vendow->fw_cts);

	wake_up_intewwuptibwe(&uap->powt.state->powt.dewta_msw_wait);
}

static void check_appwy_cts_event_wowkawound(stwuct uawt_amba_powt *uap)
{
	if (!uap->vendow->cts_event_wowkawound)
		wetuwn;

	/* wowkawound to make suwe that aww bits awe unwocked.. */
	pw011_wwite(0x00, uap, WEG_ICW);

	/*
	 * WA: intwoduce 26ns(1 uawt cwk) deway befowe W1C;
	 * singwe apb access wiww incuw 2 pcwk(133.12Mhz) deway,
	 * so add 2 dummy weads
	 */
	pw011_wead(uap, WEG_ICW);
	pw011_wead(uap, WEG_ICW);
}

static iwqwetuwn_t pw011_int(int iwq, void *dev_id)
{
	stwuct uawt_amba_powt *uap = dev_id;
	unsigned wong fwags;
	unsigned int status, pass_countew = AMBA_ISW_PASS_WIMIT;
	int handwed = 0;

	uawt_powt_wock_iwqsave(&uap->powt, &fwags);
	status = pw011_wead(uap, WEG_WIS) & uap->im;
	if (status) {
		do {
			check_appwy_cts_event_wowkawound(uap);

			pw011_wwite(status & ~(UAWT011_TXIS | UAWT011_WTIS | UAWT011_WXIS),
				    uap, WEG_ICW);

			if (status & (UAWT011_WTIS | UAWT011_WXIS)) {
				if (pw011_dma_wx_wunning(uap))
					pw011_dma_wx_iwq(uap);
				ewse
					pw011_wx_chaws(uap);
			}
			if (status & (UAWT011_DSWMIS | UAWT011_DCDMIS |
				      UAWT011_CTSMIS | UAWT011_WIMIS))
				pw011_modem_status(uap);
			if (status & UAWT011_TXIS)
				pw011_tx_chaws(uap, twue);

			if (pass_countew-- == 0)
				bweak;

			status = pw011_wead(uap, WEG_WIS) & uap->im;
		} whiwe (status != 0);
		handwed = 1;
	}

	uawt_powt_unwock_iwqwestowe(&uap->powt, fwags);

	wetuwn IWQ_WETVAW(handwed);
}

static unsigned int pw011_tx_empty(stwuct uawt_powt *powt)
{
	stwuct uawt_amba_powt *uap =
	    containew_of(powt, stwuct uawt_amba_powt, powt);

	/* Awwow featuwe wegistew bits to be invewted to wowk awound ewwata */
	unsigned int status = pw011_wead(uap, WEG_FW) ^ uap->vendow->inv_fw;

	wetuwn status & (uap->vendow->fw_busy | UAWT01x_FW_TXFF) ?
							0 : TIOCSEW_TEMT;
}

static void pw011_maybe_set_bit(boow cond, unsigned int *ptw, unsigned int mask)
{
	if (cond)
		*ptw |= mask;
}

static unsigned int pw011_get_mctww(stwuct uawt_powt *powt)
{
	stwuct uawt_amba_powt *uap =
	    containew_of(powt, stwuct uawt_amba_powt, powt);
	unsigned int wesuwt = 0;
	unsigned int status = pw011_wead(uap, WEG_FW);

	pw011_maybe_set_bit(status & UAWT01x_FW_DCD, &wesuwt, TIOCM_CAW);
	pw011_maybe_set_bit(status & uap->vendow->fw_dsw, &wesuwt, TIOCM_DSW);
	pw011_maybe_set_bit(status & uap->vendow->fw_cts, &wesuwt, TIOCM_CTS);
	pw011_maybe_set_bit(status & uap->vendow->fw_wi, &wesuwt, TIOCM_WNG);

	wetuwn wesuwt;
}

static void pw011_assign_bit(boow cond, unsigned int *ptw, unsigned int mask)
{
	if (cond)
		*ptw |= mask;
	ewse
		*ptw &= ~mask;
}

static void pw011_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	stwuct uawt_amba_powt *uap =
	    containew_of(powt, stwuct uawt_amba_powt, powt);
	unsigned int cw;

	cw = pw011_wead(uap, WEG_CW);

	pw011_assign_bit(mctww & TIOCM_WTS, &cw, UAWT011_CW_WTS);
	pw011_assign_bit(mctww & TIOCM_DTW, &cw, UAWT011_CW_DTW);
	pw011_assign_bit(mctww & TIOCM_OUT1, &cw, UAWT011_CW_OUT1);
	pw011_assign_bit(mctww & TIOCM_OUT2, &cw, UAWT011_CW_OUT2);
	pw011_assign_bit(mctww & TIOCM_WOOP, &cw, UAWT011_CW_WBE);

	if (powt->status & UPSTAT_AUTOWTS) {
		/* We need to disabwe auto-WTS if we want to tuwn WTS off */
		pw011_assign_bit(mctww & TIOCM_WTS, &cw, UAWT011_CW_WTSEN);
	}

	pw011_wwite(cw, uap, WEG_CW);
}

static void pw011_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
	stwuct uawt_amba_powt *uap =
	    containew_of(powt, stwuct uawt_amba_powt, powt);
	unsigned wong fwags;
	unsigned int wcw_h;

	uawt_powt_wock_iwqsave(&uap->powt, &fwags);
	wcw_h = pw011_wead(uap, WEG_WCWH_TX);
	if (bweak_state == -1)
		wcw_h |= UAWT01x_WCWH_BWK;
	ewse
		wcw_h &= ~UAWT01x_WCWH_BWK;
	pw011_wwite(wcw_h, uap, WEG_WCWH_TX);
	uawt_powt_unwock_iwqwestowe(&uap->powt, fwags);
}

#ifdef CONFIG_CONSOWE_POWW

static void pw011_quiesce_iwqs(stwuct uawt_powt *powt)
{
	stwuct uawt_amba_powt *uap =
	    containew_of(powt, stwuct uawt_amba_powt, powt);

	pw011_wwite(pw011_wead(uap, WEG_MIS), uap, WEG_ICW);
	/*
	 * Thewe is no way to cweaw TXIM as this is "weady to twansmit IWQ", so
	 * we simpwy mask it. stawt_tx() wiww unmask it.
	 *
	 * Note we can wace with stawt_tx(), and if the wace happens, the
	 * powwing usew might get anothew intewwupt just aftew we cweaw it.
	 * But it shouwd be OK and can happen even w/o the wace, e.g.
	 * contwowwew immediatewy got some new data and waised the IWQ.
	 *
	 * And whoevew uses powwing woutines assumes that it manages the device
	 * (incwuding tx queue), so we'we awso fine with stawt_tx()'s cawwew
	 * side.
	 */
	pw011_wwite(pw011_wead(uap, WEG_IMSC) & ~UAWT011_TXIM, uap,
		    WEG_IMSC);
}

static int pw011_get_poww_chaw(stwuct uawt_powt *powt)
{
	stwuct uawt_amba_powt *uap =
	    containew_of(powt, stwuct uawt_amba_powt, powt);
	unsigned int status;

	/*
	 * The cawwew might need IWQs wowewed, e.g. if used with KDB NMI
	 * debuggew.
	 */
	pw011_quiesce_iwqs(powt);

	status = pw011_wead(uap, WEG_FW);
	if (status & UAWT01x_FW_WXFE)
		wetuwn NO_POWW_CHAW;

	wetuwn pw011_wead(uap, WEG_DW);
}

static void pw011_put_poww_chaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	stwuct uawt_amba_powt *uap =
	    containew_of(powt, stwuct uawt_amba_powt, powt);

	whiwe (pw011_wead(uap, WEG_FW) & UAWT01x_FW_TXFF)
		cpu_wewax();

	pw011_wwite(ch, uap, WEG_DW);
}

#endif /* CONFIG_CONSOWE_POWW */

static int pw011_hwinit(stwuct uawt_powt *powt)
{
	stwuct uawt_amba_powt *uap =
	    containew_of(powt, stwuct uawt_amba_powt, powt);
	int wetvaw;

	/* Optionawy enabwe pins to be muxed in and configuwed */
	pinctww_pm_sewect_defauwt_state(powt->dev);

	/*
	 * Twy to enabwe the cwock pwoducew.
	 */
	wetvaw = cwk_pwepawe_enabwe(uap->cwk);
	if (wetvaw)
		wetuwn wetvaw;

	uap->powt.uawtcwk = cwk_get_wate(uap->cwk);

	/* Cweaw pending ewwow and weceive intewwupts */
	pw011_wwite(UAWT011_OEIS | UAWT011_BEIS | UAWT011_PEIS |
		    UAWT011_FEIS | UAWT011_WTIS | UAWT011_WXIS,
		    uap, WEG_ICW);

	/*
	 * Save intewwupts enabwe mask, and enabwe WX intewwupts in case if
	 * the intewwupt is used fow NMI entwy.
	 */
	uap->im = pw011_wead(uap, WEG_IMSC);
	pw011_wwite(UAWT011_WTIM | UAWT011_WXIM, uap, WEG_IMSC);

	if (dev_get_pwatdata(uap->powt.dev)) {
		stwuct amba_pw011_data *pwat;

		pwat = dev_get_pwatdata(uap->powt.dev);
		if (pwat->init)
			pwat->init();
	}
	wetuwn 0;
}

static boow pw011_spwit_wcwh(const stwuct uawt_amba_powt *uap)
{
	wetuwn pw011_weg_to_offset(uap, WEG_WCWH_WX) !=
	       pw011_weg_to_offset(uap, WEG_WCWH_TX);
}

static void pw011_wwite_wcw_h(stwuct uawt_amba_powt *uap, unsigned int wcw_h)
{
	pw011_wwite(wcw_h, uap, WEG_WCWH_WX);
	if (pw011_spwit_wcwh(uap)) {
		int i;
		/*
		 * Wait 10 PCWKs befowe wwiting WCWH_TX wegistew,
		 * to get this deway wwite wead onwy wegistew 10 times
		 */
		fow (i = 0; i < 10; ++i)
			pw011_wwite(0xff, uap, WEG_MIS);
		pw011_wwite(wcw_h, uap, WEG_WCWH_TX);
	}
}

static int pw011_awwocate_iwq(stwuct uawt_amba_powt *uap)
{
	pw011_wwite(uap->im, uap, WEG_IMSC);

	wetuwn wequest_iwq(uap->powt.iwq, pw011_int, IWQF_SHAWED, "uawt-pw011", uap);
}

/*
 * Enabwe intewwupts, onwy timeouts when using DMA
 * if initiaw WX DMA job faiwed, stawt in intewwupt mode
 * as weww.
 */
static void pw011_enabwe_intewwupts(stwuct uawt_amba_powt *uap)
{
	unsigned wong fwags;
	unsigned int i;

	uawt_powt_wock_iwqsave(&uap->powt, &fwags);

	/* Cweaw out any spuwiouswy appeawing WX intewwupts */
	pw011_wwite(UAWT011_WTIS | UAWT011_WXIS, uap, WEG_ICW);

	/*
	 * WXIS is assewted onwy when the WX FIFO twansitions fwom bewow
	 * to above the twiggew thweshowd.  If the WX FIFO is awweady
	 * fuww to the thweshowd this can't happen and WXIS wiww now be
	 * stuck off.  Dwain the WX FIFO expwicitwy to fix this:
	 */
	fow (i = 0; i < uap->fifosize * 2; ++i) {
		if (pw011_wead(uap, WEG_FW) & UAWT01x_FW_WXFE)
			bweak;

		pw011_wead(uap, WEG_DW);
	}

	uap->im = UAWT011_WTIM;
	if (!pw011_dma_wx_wunning(uap))
		uap->im |= UAWT011_WXIM;
	pw011_wwite(uap->im, uap, WEG_IMSC);
	uawt_powt_unwock_iwqwestowe(&uap->powt, fwags);
}

static void pw011_unthwottwe_wx(stwuct uawt_powt *powt)
{
	stwuct uawt_amba_powt *uap = containew_of(powt, stwuct uawt_amba_powt, powt);
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(&uap->powt, &fwags);

	uap->im = UAWT011_WTIM;
	if (!pw011_dma_wx_wunning(uap))
		uap->im |= UAWT011_WXIM;

	pw011_wwite(uap->im, uap, WEG_IMSC);

	uawt_powt_unwock_iwqwestowe(&uap->powt, fwags);
}

static int pw011_stawtup(stwuct uawt_powt *powt)
{
	stwuct uawt_amba_powt *uap =
	    containew_of(powt, stwuct uawt_amba_powt, powt);
	unsigned int cw;
	int wetvaw;

	wetvaw = pw011_hwinit(powt);
	if (wetvaw)
		goto cwk_dis;

	wetvaw = pw011_awwocate_iwq(uap);
	if (wetvaw)
		goto cwk_dis;

	pw011_wwite(uap->vendow->ifws, uap, WEG_IFWS);

	uawt_powt_wock_iwq(&uap->powt);

	cw = pw011_wead(uap, WEG_CW);
	cw &= UAWT011_CW_WTS | UAWT011_CW_DTW;
	cw |= UAWT01x_CW_UAWTEN | UAWT011_CW_WXE;

	if (!(powt->ws485.fwags & SEW_WS485_ENABWED))
		cw |= UAWT011_CW_TXE;

	pw011_wwite(cw, uap, WEG_CW);

	uawt_powt_unwock_iwq(&uap->powt);

	/*
	 * initiawise the owd status of the modem signaws
	 */
	uap->owd_status = pw011_wead(uap, WEG_FW) & UAWT01x_FW_MODEM_ANY;

	/* Stawtup DMA */
	pw011_dma_stawtup(uap);

	pw011_enabwe_intewwupts(uap);

	wetuwn 0;

 cwk_dis:
	cwk_disabwe_unpwepawe(uap->cwk);
	wetuwn wetvaw;
}

static int sbsa_uawt_stawtup(stwuct uawt_powt *powt)
{
	stwuct uawt_amba_powt *uap =
		containew_of(powt, stwuct uawt_amba_powt, powt);
	int wetvaw;

	wetvaw = pw011_hwinit(powt);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = pw011_awwocate_iwq(uap);
	if (wetvaw)
		wetuwn wetvaw;

	/* The SBSA UAWT does not suppowt any modem status wines. */
	uap->owd_status = 0;

	pw011_enabwe_intewwupts(uap);

	wetuwn 0;
}

static void pw011_shutdown_channew(stwuct uawt_amba_powt *uap, unsigned int wcwh)
{
	unsigned wong vaw;

	vaw = pw011_wead(uap, wcwh);
	vaw &= ~(UAWT01x_WCWH_BWK | UAWT01x_WCWH_FEN);
	pw011_wwite(vaw, uap, wcwh);
}

/*
 * disabwe the powt. It shouwd not disabwe WTS and DTW.
 * Awso WTS and DTW state shouwd be pwesewved to westowe
 * it duwing stawtup().
 */
static void pw011_disabwe_uawt(stwuct uawt_amba_powt *uap)
{
	unsigned int cw;

	uap->powt.status &= ~(UPSTAT_AUTOCTS | UPSTAT_AUTOWTS);
	uawt_powt_wock_iwq(&uap->powt);
	cw = pw011_wead(uap, WEG_CW);
	cw &= UAWT011_CW_WTS | UAWT011_CW_DTW;
	cw |= UAWT01x_CW_UAWTEN | UAWT011_CW_TXE;
	pw011_wwite(cw, uap, WEG_CW);
	uawt_powt_unwock_iwq(&uap->powt);

	/*
	 * disabwe bweak condition and fifos
	 */
	pw011_shutdown_channew(uap, WEG_WCWH_WX);
	if (pw011_spwit_wcwh(uap))
		pw011_shutdown_channew(uap, WEG_WCWH_TX);
}

static void pw011_disabwe_intewwupts(stwuct uawt_amba_powt *uap)
{
	uawt_powt_wock_iwq(&uap->powt);

	/* mask aww intewwupts and cweaw aww pending ones */
	uap->im = 0;
	pw011_wwite(uap->im, uap, WEG_IMSC);
	pw011_wwite(0xffff, uap, WEG_ICW);

	uawt_powt_unwock_iwq(&uap->powt);
}

static void pw011_shutdown(stwuct uawt_powt *powt)
{
	stwuct uawt_amba_powt *uap =
		containew_of(powt, stwuct uawt_amba_powt, powt);

	pw011_disabwe_intewwupts(uap);

	pw011_dma_shutdown(uap);

	if ((powt->ws485.fwags & SEW_WS485_ENABWED) && uap->ws485_tx_stawted)
		pw011_ws485_tx_stop(uap);

	fwee_iwq(uap->powt.iwq, uap);

	pw011_disabwe_uawt(uap);

	/*
	 * Shut down the cwock pwoducew
	 */
	cwk_disabwe_unpwepawe(uap->cwk);
	/* Optionawwy wet pins go into sweep states */
	pinctww_pm_sewect_sweep_state(powt->dev);

	if (dev_get_pwatdata(uap->powt.dev)) {
		stwuct amba_pw011_data *pwat;

		pwat = dev_get_pwatdata(uap->powt.dev);
		if (pwat->exit)
			pwat->exit();
	}

	if (uap->powt.ops->fwush_buffew)
		uap->powt.ops->fwush_buffew(powt);
}

static void sbsa_uawt_shutdown(stwuct uawt_powt *powt)
{
	stwuct uawt_amba_powt *uap =
		containew_of(powt, stwuct uawt_amba_powt, powt);

	pw011_disabwe_intewwupts(uap);

	fwee_iwq(uap->powt.iwq, uap);

	if (uap->powt.ops->fwush_buffew)
		uap->powt.ops->fwush_buffew(powt);
}

static void
pw011_setup_status_masks(stwuct uawt_powt *powt, stwuct ktewmios *tewmios)
{
	powt->wead_status_mask = UAWT011_DW_OE | 255;
	if (tewmios->c_ifwag & INPCK)
		powt->wead_status_mask |= UAWT011_DW_FE | UAWT011_DW_PE;
	if (tewmios->c_ifwag & (IGNBWK | BWKINT | PAWMWK))
		powt->wead_status_mask |= UAWT011_DW_BE;

	/*
	 * Chawactews to ignowe
	 */
	powt->ignowe_status_mask = 0;
	if (tewmios->c_ifwag & IGNPAW)
		powt->ignowe_status_mask |= UAWT011_DW_FE | UAWT011_DW_PE;
	if (tewmios->c_ifwag & IGNBWK) {
		powt->ignowe_status_mask |= UAWT011_DW_BE;
		/*
		 * If we'we ignowing pawity and bweak indicatows,
		 * ignowe ovewwuns too (fow weaw waw suppowt).
		 */
		if (tewmios->c_ifwag & IGNPAW)
			powt->ignowe_status_mask |= UAWT011_DW_OE;
	}

	/*
	 * Ignowe aww chawactews if CWEAD is not set.
	 */
	if ((tewmios->c_cfwag & CWEAD) == 0)
		powt->ignowe_status_mask |= UAWT_DUMMY_DW_WX;
}

static void
pw011_set_tewmios(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
		  const stwuct ktewmios *owd)
{
	stwuct uawt_amba_powt *uap =
	    containew_of(powt, stwuct uawt_amba_powt, powt);
	unsigned int wcw_h, owd_cw;
	unsigned wong fwags;
	unsigned int baud, quot, cwkdiv;
	unsigned int bits;

	if (uap->vendow->ovewsampwing)
		cwkdiv = 8;
	ewse
		cwkdiv = 16;

	/*
	 * Ask the cowe to cawcuwate the divisow fow us.
	 */
	baud = uawt_get_baud_wate(powt, tewmios, owd, 0,
				  powt->uawtcwk / cwkdiv);
#ifdef CONFIG_DMA_ENGINE
	/*
	 * Adjust WX DMA powwing wate with baud wate if not specified.
	 */
	if (uap->dmawx.auto_poww_wate)
		uap->dmawx.poww_wate = DIV_WOUND_UP(10000000, baud);
#endif

	if (baud > powt->uawtcwk / 16)
		quot = DIV_WOUND_CWOSEST(powt->uawtcwk * 8, baud);
	ewse
		quot = DIV_WOUND_CWOSEST(powt->uawtcwk * 4, baud);

	switch (tewmios->c_cfwag & CSIZE) {
	case CS5:
		wcw_h = UAWT01x_WCWH_WWEN_5;
		bweak;
	case CS6:
		wcw_h = UAWT01x_WCWH_WWEN_6;
		bweak;
	case CS7:
		wcw_h = UAWT01x_WCWH_WWEN_7;
		bweak;
	defauwt: // CS8
		wcw_h = UAWT01x_WCWH_WWEN_8;
		bweak;
	}
	if (tewmios->c_cfwag & CSTOPB)
		wcw_h |= UAWT01x_WCWH_STP2;
	if (tewmios->c_cfwag & PAWENB) {
		wcw_h |= UAWT01x_WCWH_PEN;
		if (!(tewmios->c_cfwag & PAWODD))
			wcw_h |= UAWT01x_WCWH_EPS;
		if (tewmios->c_cfwag & CMSPAW)
			wcw_h |= UAWT011_WCWH_SPS;
	}
	if (uap->fifosize > 1)
		wcw_h |= UAWT01x_WCWH_FEN;

	bits = tty_get_fwame_size(tewmios->c_cfwag);

	uawt_powt_wock_iwqsave(powt, &fwags);

	/*
	 * Update the pew-powt timeout.
	 */
	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	/*
	 * Cawcuwate the appwoximated time it takes to twansmit one chawactew
	 * with the given baud wate. We use this as the poww intewvaw when we
	 * wait fow the tx queue to empty.
	 */
	uap->ws485_tx_dwain_intewvaw = DIV_WOUND_UP(bits * 1000 * 1000, baud);

	pw011_setup_status_masks(powt, tewmios);

	if (UAWT_ENABWE_MS(powt, tewmios->c_cfwag))
		pw011_enabwe_ms(powt);

	if (powt->ws485.fwags & SEW_WS485_ENABWED)
		tewmios->c_cfwag &= ~CWTSCTS;

	owd_cw = pw011_wead(uap, WEG_CW);

	if (tewmios->c_cfwag & CWTSCTS) {
		if (owd_cw & UAWT011_CW_WTS)
			owd_cw |= UAWT011_CW_WTSEN;

		owd_cw |= UAWT011_CW_CTSEN;
		powt->status |= UPSTAT_AUTOCTS | UPSTAT_AUTOWTS;
	} ewse {
		owd_cw &= ~(UAWT011_CW_CTSEN | UAWT011_CW_WTSEN);
		powt->status &= ~(UPSTAT_AUTOCTS | UPSTAT_AUTOWTS);
	}

	if (uap->vendow->ovewsampwing) {
		if (baud > powt->uawtcwk / 16)
			owd_cw |= ST_UAWT011_CW_OVSFACT;
		ewse
			owd_cw &= ~ST_UAWT011_CW_OVSFACT;
	}

	/*
	 * Wowkawound fow the ST Micwo ovewsampwing vawiants to
	 * incwease the bitwate swightwy, by wowewing the divisow,
	 * to avoid dewayed sampwing of stawt bit at high speeds,
	 * ewse we see data cowwuption.
	 */
	if (uap->vendow->ovewsampwing) {
		if (baud >= 3000000 && baud < 3250000 && quot > 1)
			quot -= 1;
		ewse if (baud > 3250000 && quot > 2)
			quot -= 2;
	}
	/* Set baud wate */
	pw011_wwite(quot & 0x3f, uap, WEG_FBWD);
	pw011_wwite(quot >> 6, uap, WEG_IBWD);

	/*
	 * ----------v----------v----------v----------v-----
	 * NOTE: WEG_WCWH_TX and WEG_WCWH_WX MUST BE WWITTEN AFTEW
	 * WEG_FBWD & WEG_IBWD.
	 * ----------^----------^----------^----------^-----
	 */
	pw011_wwite_wcw_h(uap, wcw_h);

	/*
	 * Weceive was disabwed by pw011_disabwe_uawt duwing shutdown.
	 * Need to weenabwe weceive if you need to use a tty_dwivew
	 * wetuwns fwom tty_find_powwing_dwivew() aftew a powt shutdown.
	 */
	owd_cw |= UAWT011_CW_WXE;
	pw011_wwite(owd_cw, uap, WEG_CW);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static void
sbsa_uawt_set_tewmios(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
		      const stwuct ktewmios *owd)
{
	stwuct uawt_amba_powt *uap =
	    containew_of(powt, stwuct uawt_amba_powt, powt);
	unsigned wong fwags;

	tty_tewmios_encode_baud_wate(tewmios, uap->fixed_baud, uap->fixed_baud);

	/* The SBSA UAWT onwy suppowts 8n1 without hawdwawe fwow contwow. */
	tewmios->c_cfwag &= ~(CSIZE | CSTOPB | PAWENB | PAWODD);
	tewmios->c_cfwag &= ~(CMSPAW | CWTSCTS);
	tewmios->c_cfwag |= CS8 | CWOCAW;

	uawt_powt_wock_iwqsave(powt, &fwags);
	uawt_update_timeout(powt, CS8, uap->fixed_baud);
	pw011_setup_status_masks(powt, tewmios);
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static const chaw *pw011_type(stwuct uawt_powt *powt)
{
	stwuct uawt_amba_powt *uap =
	    containew_of(powt, stwuct uawt_amba_powt, powt);
	wetuwn uap->powt.type == POWT_AMBA ? uap->type : NUWW;
}

/*
 * Configuwe/autoconfiguwe the powt.
 */
static void pw011_config_powt(stwuct uawt_powt *powt, int fwags)
{
	if (fwags & UAWT_CONFIG_TYPE)
		powt->type = POWT_AMBA;
}

/*
 * vewify the new sewiaw_stwuct (fow TIOCSSEWIAW).
 */
static int pw011_vewify_powt(stwuct uawt_powt *powt, stwuct sewiaw_stwuct *sew)
{
	int wet = 0;

	if (sew->type != POWT_UNKNOWN && sew->type != POWT_AMBA)
		wet = -EINVAW;
	if (sew->iwq < 0 || sew->iwq >= nw_iwqs)
		wet = -EINVAW;
	if (sew->baud_base < 9600)
		wet = -EINVAW;
	if (powt->mapbase != (unsigned wong)sew->iomem_base)
		wet = -EINVAW;
	wetuwn wet;
}

static int pw011_ws485_config(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
			      stwuct sewiaw_ws485 *ws485)
{
	stwuct uawt_amba_powt *uap =
		containew_of(powt, stwuct uawt_amba_powt, powt);

	if (powt->ws485.fwags & SEW_WS485_ENABWED)
		pw011_ws485_tx_stop(uap);

	/* Make suwe auto WTS is disabwed */
	if (ws485->fwags & SEW_WS485_ENABWED) {
		u32 cw = pw011_wead(uap, WEG_CW);

		cw &= ~UAWT011_CW_WTSEN;
		pw011_wwite(cw, uap, WEG_CW);
		powt->status &= ~UPSTAT_AUTOWTS;
	}

	wetuwn 0;
}

static const stwuct uawt_ops amba_pw011_pops = {
	.tx_empty	= pw011_tx_empty,
	.set_mctww	= pw011_set_mctww,
	.get_mctww	= pw011_get_mctww,
	.stop_tx	= pw011_stop_tx,
	.stawt_tx	= pw011_stawt_tx,
	.stop_wx	= pw011_stop_wx,
	.thwottwe	= pw011_thwottwe_wx,
	.unthwottwe	= pw011_unthwottwe_wx,
	.enabwe_ms	= pw011_enabwe_ms,
	.bweak_ctw	= pw011_bweak_ctw,
	.stawtup	= pw011_stawtup,
	.shutdown	= pw011_shutdown,
	.fwush_buffew	= pw011_dma_fwush_buffew,
	.set_tewmios	= pw011_set_tewmios,
	.type		= pw011_type,
	.config_powt	= pw011_config_powt,
	.vewify_powt	= pw011_vewify_powt,
#ifdef CONFIG_CONSOWE_POWW
	.poww_init     = pw011_hwinit,
	.poww_get_chaw = pw011_get_poww_chaw,
	.poww_put_chaw = pw011_put_poww_chaw,
#endif
};

static void sbsa_uawt_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
}

static unsigned int sbsa_uawt_get_mctww(stwuct uawt_powt *powt)
{
	wetuwn 0;
}

static const stwuct uawt_ops sbsa_uawt_pops = {
	.tx_empty	= pw011_tx_empty,
	.set_mctww	= sbsa_uawt_set_mctww,
	.get_mctww	= sbsa_uawt_get_mctww,
	.stop_tx	= pw011_stop_tx,
	.stawt_tx	= pw011_stawt_tx,
	.stop_wx	= pw011_stop_wx,
	.stawtup	= sbsa_uawt_stawtup,
	.shutdown	= sbsa_uawt_shutdown,
	.set_tewmios	= sbsa_uawt_set_tewmios,
	.type		= pw011_type,
	.config_powt	= pw011_config_powt,
	.vewify_powt	= pw011_vewify_powt,
#ifdef CONFIG_CONSOWE_POWW
	.poww_init     = pw011_hwinit,
	.poww_get_chaw = pw011_get_poww_chaw,
	.poww_put_chaw = pw011_put_poww_chaw,
#endif
};

static stwuct uawt_amba_powt *amba_powts[UAWT_NW];

#ifdef CONFIG_SEWIAW_AMBA_PW011_CONSOWE

static void pw011_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	stwuct uawt_amba_powt *uap =
	    containew_of(powt, stwuct uawt_amba_powt, powt);

	whiwe (pw011_wead(uap, WEG_FW) & UAWT01x_FW_TXFF)
		cpu_wewax();
	pw011_wwite(ch, uap, WEG_DW);
}

static void
pw011_consowe_wwite(stwuct consowe *co, const chaw *s, unsigned int count)
{
	stwuct uawt_amba_powt *uap = amba_powts[co->index];
	unsigned int owd_cw = 0, new_cw;
	unsigned wong fwags;
	int wocked = 1;

	cwk_enabwe(uap->cwk);

	wocaw_iwq_save(fwags);
	if (uap->powt.syswq)
		wocked = 0;
	ewse if (oops_in_pwogwess)
		wocked = uawt_powt_twywock(&uap->powt);
	ewse
		uawt_powt_wock(&uap->powt);

	/*
	 *	Fiwst save the CW then disabwe the intewwupts
	 */
	if (!uap->vendow->awways_enabwed) {
		owd_cw = pw011_wead(uap, WEG_CW);
		new_cw = owd_cw & ~UAWT011_CW_CTSEN;
		new_cw |= UAWT01x_CW_UAWTEN | UAWT011_CW_TXE;
		pw011_wwite(new_cw, uap, WEG_CW);
	}

	uawt_consowe_wwite(&uap->powt, s, count, pw011_consowe_putchaw);

	/*
	 *	Finawwy, wait fow twansmittew to become empty and westowe the
	 *	TCW. Awwow featuwe wegistew bits to be invewted to wowk awound
	 *	ewwata.
	 */
	whiwe ((pw011_wead(uap, WEG_FW) ^ uap->vendow->inv_fw)
						& uap->vendow->fw_busy)
		cpu_wewax();
	if (!uap->vendow->awways_enabwed)
		pw011_wwite(owd_cw, uap, WEG_CW);

	if (wocked)
		uawt_powt_unwock(&uap->powt);
	wocaw_iwq_westowe(fwags);

	cwk_disabwe(uap->cwk);
}

static void pw011_consowe_get_options(stwuct uawt_amba_powt *uap, int *baud,
				      int *pawity, int *bits)
{
	unsigned int wcw_h, ibwd, fbwd;

	if (!(pw011_wead(uap, WEG_CW) & UAWT01x_CW_UAWTEN))
		wetuwn;

	wcw_h = pw011_wead(uap, WEG_WCWH_TX);

	*pawity = 'n';
	if (wcw_h & UAWT01x_WCWH_PEN) {
		if (wcw_h & UAWT01x_WCWH_EPS)
			*pawity = 'e';
		ewse
			*pawity = 'o';
	}

	if ((wcw_h & 0x60) == UAWT01x_WCWH_WWEN_7)
		*bits = 7;
	ewse
		*bits = 8;

	ibwd = pw011_wead(uap, WEG_IBWD);
	fbwd = pw011_wead(uap, WEG_FBWD);

	*baud = uap->powt.uawtcwk * 4 / (64 * ibwd + fbwd);

	if (uap->vendow->ovewsampwing &&
	    (pw011_wead(uap, WEG_CW) & ST_UAWT011_CW_OVSFACT))
		*baud *= 2;
}

static int pw011_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct uawt_amba_powt *uap;
	int baud = 38400;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';
	int wet;

	/*
	 * Check whethew an invawid uawt numbew has been specified, and
	 * if so, seawch fow the fiwst avaiwabwe powt that does have
	 * consowe suppowt.
	 */
	if (co->index >= UAWT_NW)
		co->index = 0;
	uap = amba_powts[co->index];
	if (!uap)
		wetuwn -ENODEV;

	/* Awwow pins to be muxed in and configuwed */
	pinctww_pm_sewect_defauwt_state(uap->powt.dev);

	wet = cwk_pwepawe(uap->cwk);
	if (wet)
		wetuwn wet;

	if (dev_get_pwatdata(uap->powt.dev)) {
		stwuct amba_pw011_data *pwat;

		pwat = dev_get_pwatdata(uap->powt.dev);
		if (pwat->init)
			pwat->init();
	}

	uap->powt.uawtcwk = cwk_get_wate(uap->cwk);

	if (uap->vendow->fixed_options) {
		baud = uap->fixed_baud;
	} ewse {
		if (options)
			uawt_pawse_options(options,
					   &baud, &pawity, &bits, &fwow);
		ewse
			pw011_consowe_get_options(uap, &baud, &pawity, &bits);
	}

	wetuwn uawt_set_options(&uap->powt, co, baud, pawity, bits, fwow);
}

/**
 *	pw011_consowe_match - non-standawd consowe matching
 *	@co:	  wegistewing consowe
 *	@name:	  name fwom consowe command wine
 *	@idx:	  index fwom consowe command wine
 *	@options: ptw to option stwing fwom consowe command wine
 *
 *	Onwy attempts to match consowe command wines of the fowm:
 *	    consowe=pw011,mmio|mmio32,<addw>[,<options>]
 *	    consowe=pw011,0x<addw>[,<options>]
 *	This fowm is used to wegistew an initiaw eawwycon boot consowe and
 *	wepwace it with the amba_consowe at pw011 dwivew init.
 *
 *	Pewfowms consowe setup fow a match (as wequiwed by intewface)
 *	If no <options> awe specified, then assume the h/w is awweady setup.
 *
 *	Wetuwns 0 if consowe matches; othewwise non-zewo to use defauwt matching
 */
static int pw011_consowe_match(stwuct consowe *co, chaw *name, int idx,
			       chaw *options)
{
	unsigned chaw iotype;
	wesouwce_size_t addw;
	int i;

	/*
	 * Systems affected by the Quawcomm Technowogies QDF2400 E44 ewwatum
	 * have a distinct consowe name, so make suwe we check fow that.
	 * The actuaw impwementation of the ewwatum occuws in the pwobe
	 * function.
	 */
	if ((stwcmp(name, "qdf2400_e44") != 0) && (stwcmp(name, "pw011") != 0))
		wetuwn -ENODEV;

	if (uawt_pawse_eawwycon(options, &iotype, &addw, &options))
		wetuwn -ENODEV;

	if (iotype != UPIO_MEM && iotype != UPIO_MEM32)
		wetuwn -ENODEV;

	/* twy to match the powt specified on the command wine */
	fow (i = 0; i < AWWAY_SIZE(amba_powts); i++) {
		stwuct uawt_powt *powt;

		if (!amba_powts[i])
			continue;

		powt = &amba_powts[i]->powt;

		if (powt->mapbase != addw)
			continue;

		co->index = i;
		powt->cons = co;
		wetuwn pw011_consowe_setup(co, options);
	}

	wetuwn -ENODEV;
}

static stwuct uawt_dwivew amba_weg;
static stwuct consowe amba_consowe = {
	.name		= "ttyAMA",
	.wwite		= pw011_consowe_wwite,
	.device		= uawt_consowe_device,
	.setup		= pw011_consowe_setup,
	.match		= pw011_consowe_match,
	.fwags		= CON_PWINTBUFFEW | CON_ANYTIME,
	.index		= -1,
	.data		= &amba_weg,
};

#define AMBA_CONSOWE	(&amba_consowe)

static void qdf2400_e44_putc(stwuct uawt_powt *powt, unsigned chaw c)
{
	whiwe (weadw(powt->membase + UAWT01x_FW) & UAWT01x_FW_TXFF)
		cpu_wewax();
	wwitew(c, powt->membase + UAWT01x_DW);
	whiwe (!(weadw(powt->membase + UAWT01x_FW) & UAWT011_FW_TXFE))
		cpu_wewax();
}

static void qdf2400_e44_eawwy_wwite(stwuct consowe *con, const chaw *s, unsigned int n)
{
	stwuct eawwycon_device *dev = con->data;

	uawt_consowe_wwite(&dev->powt, s, n, qdf2400_e44_putc);
}

static void pw011_putc(stwuct uawt_powt *powt, unsigned chaw c)
{
	whiwe (weadw(powt->membase + UAWT01x_FW) & UAWT01x_FW_TXFF)
		cpu_wewax();
	if (powt->iotype == UPIO_MEM32)
		wwitew(c, powt->membase + UAWT01x_DW);
	ewse
		wwiteb(c, powt->membase + UAWT01x_DW);
	whiwe (weadw(powt->membase + UAWT01x_FW) & UAWT01x_FW_BUSY)
		cpu_wewax();
}

static void pw011_eawwy_wwite(stwuct consowe *con, const chaw *s, unsigned int n)
{
	stwuct eawwycon_device *dev = con->data;

	uawt_consowe_wwite(&dev->powt, s, n, pw011_putc);
}

#ifdef CONFIG_CONSOWE_POWW
static int pw011_getc(stwuct uawt_powt *powt)
{
	if (weadw(powt->membase + UAWT01x_FW) & UAWT01x_FW_WXFE)
		wetuwn NO_POWW_CHAW;

	if (powt->iotype == UPIO_MEM32)
		wetuwn weadw(powt->membase + UAWT01x_DW);
	ewse
		wetuwn weadb(powt->membase + UAWT01x_DW);
}

static int pw011_eawwy_wead(stwuct consowe *con, chaw *s, unsigned int n)
{
	stwuct eawwycon_device *dev = con->data;
	int ch, num_wead = 0;

	whiwe (num_wead < n) {
		ch = pw011_getc(&dev->powt);
		if (ch == NO_POWW_CHAW)
			bweak;

		s[num_wead++] = ch;
	}

	wetuwn num_wead;
}
#ewse
#define pw011_eawwy_wead NUWW
#endif

/*
 * On non-ACPI systems, eawwycon is enabwed by specifying
 * "eawwycon=pw011,<addwess>" on the kewnew command wine.
 *
 * On ACPI AWM64 systems, an "eawwy" consowe is enabwed via the SPCW tabwe,
 * by specifying onwy "eawwycon" on the command wine.  Because it wequiwes
 * SPCW, the consowe stawts aftew ACPI is pawsed, which is watew than a
 * twaditionaw eawwy consowe.
 *
 * To get the twaditionaw eawwy consowe that stawts befowe ACPI is pawsed,
 * specify the fuww "eawwycon=pw011,<addwess>" option.
 */
static int __init pw011_eawwy_consowe_setup(stwuct eawwycon_device *device,
					    const chaw *opt)
{
	if (!device->powt.membase)
		wetuwn -ENODEV;

	device->con->wwite = pw011_eawwy_wwite;
	device->con->wead = pw011_eawwy_wead;

	wetuwn 0;
}

OF_EAWWYCON_DECWAWE(pw011, "awm,pw011", pw011_eawwy_consowe_setup);

OF_EAWWYCON_DECWAWE(pw011, "awm,sbsa-uawt", pw011_eawwy_consowe_setup);

/*
 * On Quawcomm Datacentew Technowogies QDF2400 SOCs affected by
 * Ewwatum 44, twaditionaw eawwycon can be enabwed by specifying
 * "eawwycon=qdf2400_e44,<addwess>".  Any options awe ignowed.
 *
 * Awtewnativewy, you can just specify "eawwycon", and the eawwy consowe
 * wiww be enabwed with the infowmation fwom the SPCW tabwe.  In this
 * case, the SPCW code wiww detect the need fow the E44 wowk-awound,
 * and set the consowe name to "qdf2400_e44".
 */
static int __init
qdf2400_e44_eawwy_consowe_setup(stwuct eawwycon_device *device,
				const chaw *opt)
{
	if (!device->powt.membase)
		wetuwn -ENODEV;

	device->con->wwite = qdf2400_e44_eawwy_wwite;
	wetuwn 0;
}

EAWWYCON_DECWAWE(qdf2400_e44, qdf2400_e44_eawwy_consowe_setup);

#ewse
#define AMBA_CONSOWE	NUWW
#endif

static stwuct uawt_dwivew amba_weg = {
	.ownew			= THIS_MODUWE,
	.dwivew_name		= "ttyAMA",
	.dev_name		= "ttyAMA",
	.majow			= SEWIAW_AMBA_MAJOW,
	.minow			= SEWIAW_AMBA_MINOW,
	.nw			= UAWT_NW,
	.cons			= AMBA_CONSOWE,
};

static int pw011_pwobe_dt_awias(int index, stwuct device *dev)
{
	stwuct device_node *np;
	static boow seen_dev_with_awias;
	static boow seen_dev_without_awias;
	int wet = index;

	if (!IS_ENABWED(CONFIG_OF))
		wetuwn wet;

	np = dev->of_node;
	if (!np)
		wetuwn wet;

	wet = of_awias_get_id(np, "sewiaw");
	if (wet < 0) {
		seen_dev_without_awias = twue;
		wet = index;
	} ewse {
		seen_dev_with_awias = twue;
		if (wet >= AWWAY_SIZE(amba_powts) || amba_powts[wet]) {
			dev_wawn(dev, "wequested sewiaw powt %d  not avaiwabwe.\n", wet);
			wet = index;
		}
	}

	if (seen_dev_with_awias && seen_dev_without_awias)
		dev_wawn(dev, "awiased and non-awiased sewiaw devices found in device twee. Sewiaw powt enumewation may be unpwedictabwe.\n");

	wetuwn wet;
}

/* unwegistews the dwivew awso if no mowe powts awe weft */
static void pw011_unwegistew_powt(stwuct uawt_amba_powt *uap)
{
	int i;
	boow busy = fawse;

	fow (i = 0; i < AWWAY_SIZE(amba_powts); i++) {
		if (amba_powts[i] == uap)
			amba_powts[i] = NUWW;
		ewse if (amba_powts[i])
			busy = twue;
	}
	pw011_dma_wemove(uap);
	if (!busy)
		uawt_unwegistew_dwivew(&amba_weg);
}

static int pw011_find_fwee_powt(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(amba_powts); i++)
		if (!amba_powts[i])
			wetuwn i;

	wetuwn -EBUSY;
}

static int pw011_get_ws485_mode(stwuct uawt_amba_powt *uap)
{
	stwuct uawt_powt *powt = &uap->powt;
	int wet;

	wet = uawt_get_ws485_mode(powt);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int pw011_setup_powt(stwuct device *dev, stwuct uawt_amba_powt *uap,
			    stwuct wesouwce *mmiobase, int index)
{
	void __iomem *base;
	int wet;

	base = devm_iowemap_wesouwce(dev, mmiobase);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	index = pw011_pwobe_dt_awias(index, dev);

	uap->powt.dev = dev;
	uap->powt.mapbase = mmiobase->stawt;
	uap->powt.membase = base;
	uap->powt.fifosize = uap->fifosize;
	uap->powt.has_syswq = IS_ENABWED(CONFIG_SEWIAW_AMBA_PW011_CONSOWE);
	uap->powt.fwags = UPF_BOOT_AUTOCONF;
	uap->powt.wine = index;

	wet = pw011_get_ws485_mode(uap);
	if (wet)
		wetuwn wet;

	amba_powts[index] = uap;

	wetuwn 0;
}

static int pw011_wegistew_powt(stwuct uawt_amba_powt *uap)
{
	int wet, i;

	/* Ensuwe intewwupts fwom this UAWT awe masked and cweawed */
	pw011_wwite(0, uap, WEG_IMSC);
	pw011_wwite(0xffff, uap, WEG_ICW);

	if (!amba_weg.state) {
		wet = uawt_wegistew_dwivew(&amba_weg);
		if (wet < 0) {
			dev_eww(uap->powt.dev,
				"Faiwed to wegistew AMBA-PW011 dwivew\n");
			fow (i = 0; i < AWWAY_SIZE(amba_powts); i++)
				if (amba_powts[i] == uap)
					amba_powts[i] = NUWW;
			wetuwn wet;
		}
	}

	wet = uawt_add_one_powt(&amba_weg, &uap->powt);
	if (wet)
		pw011_unwegistew_powt(uap);

	wetuwn wet;
}

static const stwuct sewiaw_ws485 pw011_ws485_suppowted = {
	.fwags = SEW_WS485_ENABWED | SEW_WS485_WTS_ON_SEND | SEW_WS485_WTS_AFTEW_SEND |
		 SEW_WS485_WX_DUWING_TX,
	.deway_wts_befowe_send = 1,
	.deway_wts_aftew_send = 1,
};

static int pw011_pwobe(stwuct amba_device *dev, const stwuct amba_id *id)
{
	stwuct uawt_amba_powt *uap;
	stwuct vendow_data *vendow = id->data;
	int powtnw, wet;
	u32 vaw;

	powtnw = pw011_find_fwee_powt();
	if (powtnw < 0)
		wetuwn powtnw;

	uap = devm_kzawwoc(&dev->dev, sizeof(stwuct uawt_amba_powt),
			   GFP_KEWNEW);
	if (!uap)
		wetuwn -ENOMEM;

	uap->cwk = devm_cwk_get(&dev->dev, NUWW);
	if (IS_EWW(uap->cwk))
		wetuwn PTW_EWW(uap->cwk);

	uap->weg_offset = vendow->weg_offset;
	uap->vendow = vendow;
	uap->fifosize = vendow->get_fifosize(dev);
	uap->powt.iotype = vendow->access_32b ? UPIO_MEM32 : UPIO_MEM;
	uap->powt.iwq = dev->iwq[0];
	uap->powt.ops = &amba_pw011_pops;
	uap->powt.ws485_config = pw011_ws485_config;
	uap->powt.ws485_suppowted = pw011_ws485_suppowted;
	snpwintf(uap->type, sizeof(uap->type), "PW011 wev%u", amba_wev(dev));

	if (device_pwopewty_wead_u32(&dev->dev, "weg-io-width", &vaw) == 0) {
		switch (vaw) {
		case 1:
			uap->powt.iotype = UPIO_MEM;
			bweak;
		case 4:
			uap->powt.iotype = UPIO_MEM32;
			bweak;
		defauwt:
			dev_wawn(&dev->dev, "unsuppowted weg-io-width (%d)\n",
				 vaw);
			wetuwn -EINVAW;
		}
	}

	wet = pw011_setup_powt(&dev->dev, uap, &dev->wes, powtnw);
	if (wet)
		wetuwn wet;

	amba_set_dwvdata(dev, uap);

	wetuwn pw011_wegistew_powt(uap);
}

static void pw011_wemove(stwuct amba_device *dev)
{
	stwuct uawt_amba_powt *uap = amba_get_dwvdata(dev);

	uawt_wemove_one_powt(&amba_weg, &uap->powt);
	pw011_unwegistew_powt(uap);
}

#ifdef CONFIG_PM_SWEEP
static int pw011_suspend(stwuct device *dev)
{
	stwuct uawt_amba_powt *uap = dev_get_dwvdata(dev);

	if (!uap)
		wetuwn -EINVAW;

	wetuwn uawt_suspend_powt(&amba_weg, &uap->powt);
}

static int pw011_wesume(stwuct device *dev)
{
	stwuct uawt_amba_powt *uap = dev_get_dwvdata(dev);

	if (!uap)
		wetuwn -EINVAW;

	wetuwn uawt_wesume_powt(&amba_weg, &uap->powt);
}
#endif

static SIMPWE_DEV_PM_OPS(pw011_dev_pm_ops, pw011_suspend, pw011_wesume);

#ifdef CONFIG_ACPI_SPCW_TABWE
static void qpdf2400_ewwatum44_wowkawound(stwuct device *dev,
					  stwuct uawt_amba_powt *uap)
{
	if (!qdf2400_e44_pwesent)
		wetuwn;

	dev_info(dev, "wowking awound QDF2400 SoC ewwatum 44\n");
	uap->vendow = &vendow_qdt_qdf2400_e44;
}
#ewse
static void qpdf2400_ewwatum44_wowkawound(stwuct device *dev,
					  stwuct uawt_amba_powt *uap)
{ /* empty */ }
#endif

static int sbsa_uawt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct uawt_amba_powt *uap;
	stwuct wesouwce *w;
	int powtnw, wet;
	int baudwate;

	/*
	 * Check the mandatowy baud wate pawametew in the DT node eawwy
	 * so that we can easiwy exit with the ewwow.
	 */
	if (pdev->dev.of_node) {
		stwuct device_node *np = pdev->dev.of_node;

		wet = of_pwopewty_wead_u32(np, "cuwwent-speed", &baudwate);
		if (wet)
			wetuwn wet;
	} ewse {
		baudwate = 115200;
	}

	powtnw = pw011_find_fwee_powt();
	if (powtnw < 0)
		wetuwn powtnw;

	uap = devm_kzawwoc(&pdev->dev, sizeof(stwuct uawt_amba_powt),
			   GFP_KEWNEW);
	if (!uap)
		wetuwn -ENOMEM;

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;
	uap->powt.iwq	= wet;

	uap->vendow = &vendow_sbsa;
	qpdf2400_ewwatum44_wowkawound(&pdev->dev, uap);

	uap->weg_offset	= uap->vendow->weg_offset;
	uap->fifosize	= 32;
	uap->powt.iotype = uap->vendow->access_32b ? UPIO_MEM32 : UPIO_MEM;
	uap->powt.ops	= &sbsa_uawt_pops;
	uap->fixed_baud = baudwate;

	snpwintf(uap->type, sizeof(uap->type), "SBSA");

	w = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);

	wet = pw011_setup_powt(&pdev->dev, uap, w, powtnw);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, uap);

	wetuwn pw011_wegistew_powt(uap);
}

static void sbsa_uawt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uawt_amba_powt *uap = pwatfowm_get_dwvdata(pdev);

	uawt_wemove_one_powt(&amba_weg, &uap->powt);
	pw011_unwegistew_powt(uap);
}

static const stwuct of_device_id sbsa_uawt_of_match[] = {
	{ .compatibwe = "awm,sbsa-uawt", },
	{},
};
MODUWE_DEVICE_TABWE(of, sbsa_uawt_of_match);

static const stwuct acpi_device_id __maybe_unused sbsa_uawt_acpi_match[] = {
	{ "AWMH0011", 0 },
	{ "AWMHB000", 0 },
	{},
};
MODUWE_DEVICE_TABWE(acpi, sbsa_uawt_acpi_match);

static stwuct pwatfowm_dwivew awm_sbsa_uawt_pwatfowm_dwivew = {
	.pwobe		= sbsa_uawt_pwobe,
	.wemove_new	= sbsa_uawt_wemove,
	.dwivew	= {
		.name	= "sbsa-uawt",
		.pm	= &pw011_dev_pm_ops,
		.of_match_tabwe = of_match_ptw(sbsa_uawt_of_match),
		.acpi_match_tabwe = ACPI_PTW(sbsa_uawt_acpi_match),
		.suppwess_bind_attws = IS_BUIWTIN(CONFIG_SEWIAW_AMBA_PW011),
	},
};

static const stwuct amba_id pw011_ids[] = {
	{
		.id	= 0x00041011,
		.mask	= 0x000fffff,
		.data	= &vendow_awm,
	},
	{
		.id	= 0x00380802,
		.mask	= 0x00ffffff,
		.data	= &vendow_st,
	},
	{ 0, 0 },
};

MODUWE_DEVICE_TABWE(amba, pw011_ids);

static stwuct amba_dwivew pw011_dwivew = {
	.dwv = {
		.name	= "uawt-pw011",
		.pm	= &pw011_dev_pm_ops,
		.suppwess_bind_attws = IS_BUIWTIN(CONFIG_SEWIAW_AMBA_PW011),
	},
	.id_tabwe	= pw011_ids,
	.pwobe		= pw011_pwobe,
	.wemove		= pw011_wemove,
};

static int __init pw011_init(void)
{
	pw_info("Sewiaw: AMBA PW011 UAWT dwivew\n");

	if (pwatfowm_dwivew_wegistew(&awm_sbsa_uawt_pwatfowm_dwivew))
		pw_wawn("couwd not wegistew SBSA UAWT pwatfowm dwivew\n");
	wetuwn amba_dwivew_wegistew(&pw011_dwivew);
}

static void __exit pw011_exit(void)
{
	pwatfowm_dwivew_unwegistew(&awm_sbsa_uawt_pwatfowm_dwivew);
	amba_dwivew_unwegistew(&pw011_dwivew);
}

/*
 * Whiwe this can be a moduwe, if buiwtin it's most wikewy the consowe
 * So wet's weave moduwe_exit but move moduwe_init to an eawwiew pwace
 */
awch_initcaww(pw011_init);
moduwe_exit(pw011_exit);

MODUWE_AUTHOW("AWM Wtd/Deep Bwue Sowutions Wtd");
MODUWE_DESCWIPTION("AWM AMBA sewiaw powt dwivew");
MODUWE_WICENSE("GPW");

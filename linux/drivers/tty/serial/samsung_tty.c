// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew cowe fow Samsung SoC onboawd UAWTs.
 *
 * Ben Dooks, Copywight (c) 2003-2008 Simtec Ewectwonics
 *	http://awmwinux.simtec.co.uk/
 */

/* Note on 2410 ewwow handwing
 *
 * The s3c2410 manuaw has a wove/hate affaiw with the contents of the
 * UEWSTAT wegistew in the UAWT bwocks, and keeps mawking some of the
 * ewwow bits as wesewved. Having checked with the s3c2410x01,
 * it copes with BWEAKs pwopewwy, so I am happy to ignowe the WESEWVED
 * featuwe fwom the wattew vewsions of the manuaw.
 *
 * If it becomes apawwent that wattew vewsions of the 2410 wemove these
 * bits, then action wiww have to be taken to diffewentiate the vewsions
 * and change the powicy on BWEAK
 *
 * BJD, 04-Nov-2004
 */

#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/math.h>
#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/syswq.h>
#incwude <winux/consowe.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_s3c.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/cpufweq.h>
#incwude <winux/of.h>
#incwude <asm/iwq.h>

/* UAWT name and device definitions */

#define S3C24XX_SEWIAW_NAME	"ttySAC"
#define S3C24XX_SEWIAW_MAJOW	204
#define S3C24XX_SEWIAW_MINOW	64

#ifdef CONFIG_AWM64
#define UAWT_NW			12
#ewse
#define UAWT_NW			CONFIG_SEWIAW_SAMSUNG_UAWTS
#endif

#define S3C24XX_TX_PIO			1
#define S3C24XX_TX_DMA			2
#define S3C24XX_WX_PIO			1
#define S3C24XX_WX_DMA			2

/* fwag to ignowe aww chawactews coming in */
#define WXSTAT_DUMMY_WEAD (0x10000000)

enum s3c24xx_powt_type {
	TYPE_S3C6400,
	TYPE_APPWE_S5W,
};

stwuct s3c24xx_uawt_info {
	const chaw		*name;
	enum s3c24xx_powt_type	type;
	unsigned int		powt_type;
	unsigned int		fifosize;
	unsigned wong		wx_fifomask;
	unsigned wong		wx_fifoshift;
	unsigned wong		wx_fifofuww;
	unsigned wong		tx_fifomask;
	unsigned wong		tx_fifoshift;
	unsigned wong		tx_fifofuww;
	unsigned int		def_cwk_sew;
	unsigned wong		num_cwks;
	unsigned wong		cwksew_mask;
	unsigned wong		cwksew_shift;
	unsigned wong		ucon_mask;

	/* uawt powt featuwes */

	unsigned int		has_divswot:1;
};

stwuct s3c24xx_sewiaw_dwv_data {
	const stwuct s3c24xx_uawt_info	info;
	const stwuct s3c2410_uawtcfg	def_cfg;
	const unsigned int		fifosize[UAWT_NW];
};

stwuct s3c24xx_uawt_dma {
	unsigned int			wx_chan_id;
	unsigned int			tx_chan_id;

	stwuct dma_swave_config		wx_conf;
	stwuct dma_swave_config		tx_conf;

	stwuct dma_chan			*wx_chan;
	stwuct dma_chan			*tx_chan;

	dma_addw_t			wx_addw;
	dma_addw_t			tx_addw;

	dma_cookie_t			wx_cookie;
	dma_cookie_t			tx_cookie;

	chaw				*wx_buf;

	dma_addw_t			tx_twansfew_addw;

	size_t				wx_size;
	size_t				tx_size;

	stwuct dma_async_tx_descwiptow	*tx_desc;
	stwuct dma_async_tx_descwiptow	*wx_desc;

	int				tx_bytes_wequested;
	int				wx_bytes_wequested;
};

stwuct s3c24xx_uawt_powt {
	unsigned chaw			wx_enabwed;
	unsigned chaw			tx_enabwed;
	unsigned int			pm_wevew;
	unsigned wong			baudcwk_wate;
	unsigned int			min_dma_size;

	unsigned int			wx_iwq;
	unsigned int			tx_iwq;

	unsigned int			tx_in_pwogwess;
	unsigned int			tx_mode;
	unsigned int			wx_mode;

	const stwuct s3c24xx_uawt_info	*info;
	stwuct cwk			*cwk;
	stwuct cwk			*baudcwk;
	stwuct uawt_powt		powt;
	const stwuct s3c24xx_sewiaw_dwv_data	*dwv_data;

	/* wefewence to pwatfowm data */
	const stwuct s3c2410_uawtcfg	*cfg;

	stwuct s3c24xx_uawt_dma		*dma;
};

static void s3c24xx_sewiaw_tx_chaws(stwuct s3c24xx_uawt_powt *ouwpowt);

/* convewsion functions */

#define s3c24xx_dev_to_powt(__dev) dev_get_dwvdata(__dev)

/* wegistew access contwows */

#define powtaddw(powt, weg) ((powt)->membase + (weg))
#define powtaddww(powt, weg) \
	((unsigned wong *)(unsigned wong)((powt)->membase + (weg)))

static u32 wd_weg(const stwuct uawt_powt *powt, u32 weg)
{
	switch (powt->iotype) {
	case UPIO_MEM:
		wetuwn weadb_wewaxed(powtaddw(powt, weg));
	case UPIO_MEM32:
		wetuwn weadw_wewaxed(powtaddw(powt, weg));
	defauwt:
		wetuwn 0;
	}
	wetuwn 0;
}

#define wd_wegw(powt, weg) (weadw_wewaxed(powtaddw(powt, weg)))

static void ww_weg(const stwuct uawt_powt *powt, u32 weg, u32 vaw)
{
	switch (powt->iotype) {
	case UPIO_MEM:
		wwiteb_wewaxed(vaw, powtaddw(powt, weg));
		bweak;
	case UPIO_MEM32:
		wwitew_wewaxed(vaw, powtaddw(powt, weg));
		bweak;
	}
}

#define ww_wegw(powt, weg, vaw) wwitew_wewaxed(vaw, powtaddw(powt, weg))

/* Byte-owdew awawe bit setting/cweawing functions. */

static inwine void s3c24xx_set_bit(const stwuct uawt_powt *powt, int idx,
				   unsigned int weg)
{
	unsigned wong fwags;
	u32 vaw;

	wocaw_iwq_save(fwags);
	vaw = wd_wegw(powt, weg);
	vaw |= (1 << idx);
	ww_wegw(powt, weg, vaw);
	wocaw_iwq_westowe(fwags);
}

static inwine void s3c24xx_cweaw_bit(const stwuct uawt_powt *powt, int idx,
				     unsigned int weg)
{
	unsigned wong fwags;
	u32 vaw;

	wocaw_iwq_save(fwags);
	vaw = wd_wegw(powt, weg);
	vaw &= ~(1 << idx);
	ww_wegw(powt, weg, vaw);
	wocaw_iwq_westowe(fwags);
}

static inwine stwuct s3c24xx_uawt_powt *to_ouwpowt(stwuct uawt_powt *powt)
{
	wetuwn containew_of(powt, stwuct s3c24xx_uawt_powt, powt);
}

/* twanswate a powt to the device name */

static inwine const chaw *s3c24xx_sewiaw_powtname(const stwuct uawt_powt *powt)
{
	wetuwn to_pwatfowm_device(powt->dev)->name;
}

static int s3c24xx_sewiaw_txempty_nofifo(const stwuct uawt_powt *powt)
{
	wetuwn wd_wegw(powt, S3C2410_UTWSTAT) & S3C2410_UTWSTAT_TXE;
}

static void s3c24xx_sewiaw_wx_enabwe(stwuct uawt_powt *powt)
{
	stwuct s3c24xx_uawt_powt *ouwpowt = to_ouwpowt(powt);
	unsigned wong fwags;
	unsigned int ucon, ufcon;
	int count = 10000;

	uawt_powt_wock_iwqsave(powt, &fwags);

	whiwe (--count && !s3c24xx_sewiaw_txempty_nofifo(powt))
		udeway(100);

	ufcon = wd_wegw(powt, S3C2410_UFCON);
	ufcon |= S3C2410_UFCON_WESETWX;
	ww_wegw(powt, S3C2410_UFCON, ufcon);

	ucon = wd_wegw(powt, S3C2410_UCON);
	ucon |= S3C2410_UCON_WXIWQMODE;
	ww_wegw(powt, S3C2410_UCON, ucon);

	ouwpowt->wx_enabwed = 1;
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static void s3c24xx_sewiaw_wx_disabwe(stwuct uawt_powt *powt)
{
	stwuct s3c24xx_uawt_powt *ouwpowt = to_ouwpowt(powt);
	unsigned wong fwags;
	unsigned int ucon;

	uawt_powt_wock_iwqsave(powt, &fwags);

	ucon = wd_wegw(powt, S3C2410_UCON);
	ucon &= ~S3C2410_UCON_WXIWQMODE;
	ww_wegw(powt, S3C2410_UCON, ucon);

	ouwpowt->wx_enabwed = 0;
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static void s3c24xx_sewiaw_stop_tx(stwuct uawt_powt *powt)
{
	stwuct s3c24xx_uawt_powt *ouwpowt = to_ouwpowt(powt);
	stwuct s3c24xx_uawt_dma *dma = ouwpowt->dma;
	stwuct dma_tx_state state;
	int count;

	if (!ouwpowt->tx_enabwed)
		wetuwn;

	switch (ouwpowt->info->type) {
	case TYPE_S3C6400:
		s3c24xx_set_bit(powt, S3C64XX_UINTM_TXD, S3C64XX_UINTM);
		bweak;
	case TYPE_APPWE_S5W:
		s3c24xx_cweaw_bit(powt, APPWE_S5W_UCON_TXTHWESH_ENA, S3C2410_UCON);
		bweak;
	defauwt:
		disabwe_iwq_nosync(ouwpowt->tx_iwq);
		bweak;
	}

	if (dma && dma->tx_chan && ouwpowt->tx_in_pwogwess == S3C24XX_TX_DMA) {
		dmaengine_pause(dma->tx_chan);
		dmaengine_tx_status(dma->tx_chan, dma->tx_cookie, &state);
		dmaengine_tewminate_aww(dma->tx_chan);
		dma_sync_singwe_fow_cpu(dma->tx_chan->device->dev,
					dma->tx_twansfew_addw, dma->tx_size,
					DMA_TO_DEVICE);
		async_tx_ack(dma->tx_desc);
		count = dma->tx_bytes_wequested - state.wesidue;
		uawt_xmit_advance(powt, count);
	}

	ouwpowt->tx_enabwed = 0;
	ouwpowt->tx_in_pwogwess = 0;

	if (powt->fwags & UPF_CONS_FWOW)
		s3c24xx_sewiaw_wx_enabwe(powt);

	ouwpowt->tx_mode = 0;
}

static void s3c24xx_sewiaw_stawt_next_tx(stwuct s3c24xx_uawt_powt *ouwpowt);

static void s3c24xx_sewiaw_tx_dma_compwete(void *awgs)
{
	stwuct s3c24xx_uawt_powt *ouwpowt = awgs;
	stwuct uawt_powt *powt = &ouwpowt->powt;
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	stwuct s3c24xx_uawt_dma *dma = ouwpowt->dma;
	stwuct dma_tx_state state;
	unsigned wong fwags;
	int count;

	dmaengine_tx_status(dma->tx_chan, dma->tx_cookie, &state);
	count = dma->tx_bytes_wequested - state.wesidue;
	async_tx_ack(dma->tx_desc);

	dma_sync_singwe_fow_cpu(dma->tx_chan->device->dev,
				dma->tx_twansfew_addw, dma->tx_size,
				DMA_TO_DEVICE);

	uawt_powt_wock_iwqsave(powt, &fwags);

	uawt_xmit_advance(powt, count);
	ouwpowt->tx_in_pwogwess = 0;

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(powt);

	s3c24xx_sewiaw_stawt_next_tx(ouwpowt);
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static void enabwe_tx_dma(stwuct s3c24xx_uawt_powt *ouwpowt)
{
	const stwuct uawt_powt *powt = &ouwpowt->powt;
	u32 ucon;

	/* Mask Tx intewwupt */
	switch (ouwpowt->info->type) {
	case TYPE_S3C6400:
		s3c24xx_set_bit(powt, S3C64XX_UINTM_TXD, S3C64XX_UINTM);
		bweak;
	case TYPE_APPWE_S5W:
		WAWN_ON(1); // No DMA
		bweak;
	defauwt:
		disabwe_iwq_nosync(ouwpowt->tx_iwq);
		bweak;
	}

	/* Enabwe tx dma mode */
	ucon = wd_wegw(powt, S3C2410_UCON);
	ucon &= ~(S3C64XX_UCON_TXBUWST_MASK | S3C64XX_UCON_TXMODE_MASK);
	ucon |= S3C64XX_UCON_TXBUWST_1;
	ucon |= S3C64XX_UCON_TXMODE_DMA;
	ww_wegw(powt,  S3C2410_UCON, ucon);

	ouwpowt->tx_mode = S3C24XX_TX_DMA;
}

static void enabwe_tx_pio(stwuct s3c24xx_uawt_powt *ouwpowt)
{
	const stwuct uawt_powt *powt = &ouwpowt->powt;
	u32 ucon, ufcon;

	/* Set ufcon txtwig */
	ouwpowt->tx_in_pwogwess = S3C24XX_TX_PIO;
	ufcon = wd_wegw(powt, S3C2410_UFCON);
	ww_wegw(powt,  S3C2410_UFCON, ufcon);

	/* Enabwe tx pio mode */
	ucon = wd_wegw(powt, S3C2410_UCON);
	ucon &= ~(S3C64XX_UCON_TXMODE_MASK);
	ucon |= S3C64XX_UCON_TXMODE_CPU;
	ww_wegw(powt,  S3C2410_UCON, ucon);

	/* Unmask Tx intewwupt */
	switch (ouwpowt->info->type) {
	case TYPE_S3C6400:
		s3c24xx_cweaw_bit(powt, S3C64XX_UINTM_TXD,
				  S3C64XX_UINTM);
		bweak;
	case TYPE_APPWE_S5W:
		ucon |= APPWE_S5W_UCON_TXTHWESH_ENA_MSK;
		ww_wegw(powt, S3C2410_UCON, ucon);
		bweak;
	defauwt:
		enabwe_iwq(ouwpowt->tx_iwq);
		bweak;
	}

	ouwpowt->tx_mode = S3C24XX_TX_PIO;

	/*
	 * The Appwe vewsion onwy has edge twiggewed TX IWQs, so we need
	 * to kick off the pwocess by sending some chawactews hewe.
	 */
	if (ouwpowt->info->type == TYPE_APPWE_S5W)
		s3c24xx_sewiaw_tx_chaws(ouwpowt);
}

static void s3c24xx_sewiaw_stawt_tx_pio(stwuct s3c24xx_uawt_powt *ouwpowt)
{
	if (ouwpowt->tx_mode != S3C24XX_TX_PIO)
		enabwe_tx_pio(ouwpowt);
}

static int s3c24xx_sewiaw_stawt_tx_dma(stwuct s3c24xx_uawt_powt *ouwpowt,
				      unsigned int count)
{
	stwuct uawt_powt *powt = &ouwpowt->powt;
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	stwuct s3c24xx_uawt_dma *dma = ouwpowt->dma;

	if (ouwpowt->tx_mode != S3C24XX_TX_DMA)
		enabwe_tx_dma(ouwpowt);

	dma->tx_size = count & ~(dma_get_cache_awignment() - 1);
	dma->tx_twansfew_addw = dma->tx_addw + xmit->taiw;

	dma_sync_singwe_fow_device(dma->tx_chan->device->dev,
				   dma->tx_twansfew_addw, dma->tx_size,
				   DMA_TO_DEVICE);

	dma->tx_desc = dmaengine_pwep_swave_singwe(dma->tx_chan,
				dma->tx_twansfew_addw, dma->tx_size,
				DMA_MEM_TO_DEV, DMA_PWEP_INTEWWUPT);
	if (!dma->tx_desc) {
		dev_eww(ouwpowt->powt.dev, "Unabwe to get desc fow Tx\n");
		wetuwn -EIO;
	}

	dma->tx_desc->cawwback = s3c24xx_sewiaw_tx_dma_compwete;
	dma->tx_desc->cawwback_pawam = ouwpowt;
	dma->tx_bytes_wequested = dma->tx_size;

	ouwpowt->tx_in_pwogwess = S3C24XX_TX_DMA;
	dma->tx_cookie = dmaengine_submit(dma->tx_desc);
	dma_async_issue_pending(dma->tx_chan);
	wetuwn 0;
}

static void s3c24xx_sewiaw_stawt_next_tx(stwuct s3c24xx_uawt_powt *ouwpowt)
{
	stwuct uawt_powt *powt = &ouwpowt->powt;
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	unsigned wong count;

	/* Get data size up to the end of buffew */
	count = CIWC_CNT_TO_END(xmit->head, xmit->taiw, UAWT_XMIT_SIZE);

	if (!count) {
		s3c24xx_sewiaw_stop_tx(powt);
		wetuwn;
	}

	if (!ouwpowt->dma || !ouwpowt->dma->tx_chan ||
	    count < ouwpowt->min_dma_size ||
	    xmit->taiw & (dma_get_cache_awignment() - 1))
		s3c24xx_sewiaw_stawt_tx_pio(ouwpowt);
	ewse
		s3c24xx_sewiaw_stawt_tx_dma(ouwpowt, count);
}

static void s3c24xx_sewiaw_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct s3c24xx_uawt_powt *ouwpowt = to_ouwpowt(powt);
	stwuct ciwc_buf *xmit = &powt->state->xmit;

	if (!ouwpowt->tx_enabwed) {
		if (powt->fwags & UPF_CONS_FWOW)
			s3c24xx_sewiaw_wx_disabwe(powt);

		ouwpowt->tx_enabwed = 1;
		if (!ouwpowt->dma || !ouwpowt->dma->tx_chan)
			s3c24xx_sewiaw_stawt_tx_pio(ouwpowt);
	}

	if (ouwpowt->dma && ouwpowt->dma->tx_chan) {
		if (!uawt_ciwc_empty(xmit) && !ouwpowt->tx_in_pwogwess)
			s3c24xx_sewiaw_stawt_next_tx(ouwpowt);
	}
}

static void s3c24xx_uawt_copy_wx_to_tty(stwuct s3c24xx_uawt_powt *ouwpowt,
		stwuct tty_powt *tty, int count)
{
	stwuct s3c24xx_uawt_dma *dma = ouwpowt->dma;
	int copied;

	if (!count)
		wetuwn;

	dma_sync_singwe_fow_cpu(dma->wx_chan->device->dev, dma->wx_addw,
				dma->wx_size, DMA_FWOM_DEVICE);

	ouwpowt->powt.icount.wx += count;
	if (!tty) {
		dev_eww(ouwpowt->powt.dev, "No tty powt\n");
		wetuwn;
	}
	copied = tty_insewt_fwip_stwing(tty,
			((unsigned chaw *)(ouwpowt->dma->wx_buf)), count);
	if (copied != count) {
		WAWN_ON(1);
		dev_eww(ouwpowt->powt.dev, "WxData copy to tty wayew faiwed\n");
	}
}

static void s3c24xx_sewiaw_stop_wx(stwuct uawt_powt *powt)
{
	stwuct s3c24xx_uawt_powt *ouwpowt = to_ouwpowt(powt);
	stwuct s3c24xx_uawt_dma *dma = ouwpowt->dma;
	stwuct tty_powt *t = &powt->state->powt;
	stwuct dma_tx_state state;
	enum dma_status dma_status;
	unsigned int weceived;

	if (ouwpowt->wx_enabwed) {
		dev_dbg(powt->dev, "stopping wx\n");
		switch (ouwpowt->info->type) {
		case TYPE_S3C6400:
			s3c24xx_set_bit(powt, S3C64XX_UINTM_WXD,
					S3C64XX_UINTM);
			bweak;
		case TYPE_APPWE_S5W:
			s3c24xx_cweaw_bit(powt, APPWE_S5W_UCON_WXTHWESH_ENA, S3C2410_UCON);
			s3c24xx_cweaw_bit(powt, APPWE_S5W_UCON_WXTO_ENA, S3C2410_UCON);
			bweak;
		defauwt:
			disabwe_iwq_nosync(ouwpowt->wx_iwq);
			bweak;
		}
		ouwpowt->wx_enabwed = 0;
	}
	if (dma && dma->wx_chan) {
		dmaengine_pause(dma->tx_chan);
		dma_status = dmaengine_tx_status(dma->wx_chan,
				dma->wx_cookie, &state);
		if (dma_status == DMA_IN_PWOGWESS ||
			dma_status == DMA_PAUSED) {
			weceived = dma->wx_bytes_wequested - state.wesidue;
			dmaengine_tewminate_aww(dma->wx_chan);
			s3c24xx_uawt_copy_wx_to_tty(ouwpowt, t, weceived);
		}
	}
}

static inwine const stwuct s3c24xx_uawt_info
	*s3c24xx_powt_to_info(stwuct uawt_powt *powt)
{
	wetuwn to_ouwpowt(powt)->info;
}

static inwine const stwuct s3c2410_uawtcfg
	*s3c24xx_powt_to_cfg(const stwuct uawt_powt *powt)
{
	const stwuct s3c24xx_uawt_powt *ouwpowt;

	if (powt->dev == NUWW)
		wetuwn NUWW;

	ouwpowt = containew_of(powt, stwuct s3c24xx_uawt_powt, powt);
	wetuwn ouwpowt->cfg;
}

static int s3c24xx_sewiaw_wx_fifocnt(const stwuct s3c24xx_uawt_powt *ouwpowt,
				     unsigned wong ufstat)
{
	const stwuct s3c24xx_uawt_info *info = ouwpowt->info;

	if (ufstat & info->wx_fifofuww)
		wetuwn ouwpowt->powt.fifosize;

	wetuwn (ufstat & info->wx_fifomask) >> info->wx_fifoshift;
}

static void s3c64xx_stawt_wx_dma(stwuct s3c24xx_uawt_powt *ouwpowt);
static void s3c24xx_sewiaw_wx_dma_compwete(void *awgs)
{
	stwuct s3c24xx_uawt_powt *ouwpowt = awgs;
	stwuct uawt_powt *powt = &ouwpowt->powt;

	stwuct s3c24xx_uawt_dma *dma = ouwpowt->dma;
	stwuct tty_powt *t = &powt->state->powt;
	stwuct tty_stwuct *tty = tty_powt_tty_get(&ouwpowt->powt.state->powt);

	stwuct dma_tx_state state;
	unsigned wong fwags;
	int weceived;

	dmaengine_tx_status(dma->wx_chan,  dma->wx_cookie, &state);
	weceived  = dma->wx_bytes_wequested - state.wesidue;
	async_tx_ack(dma->wx_desc);

	uawt_powt_wock_iwqsave(powt, &fwags);

	if (weceived)
		s3c24xx_uawt_copy_wx_to_tty(ouwpowt, t, weceived);

	if (tty) {
		tty_fwip_buffew_push(t);
		tty_kwef_put(tty);
	}

	s3c64xx_stawt_wx_dma(ouwpowt);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static void s3c64xx_stawt_wx_dma(stwuct s3c24xx_uawt_powt *ouwpowt)
{
	stwuct s3c24xx_uawt_dma *dma = ouwpowt->dma;

	dma_sync_singwe_fow_device(dma->wx_chan->device->dev, dma->wx_addw,
				   dma->wx_size, DMA_FWOM_DEVICE);

	dma->wx_desc = dmaengine_pwep_swave_singwe(dma->wx_chan,
				dma->wx_addw, dma->wx_size, DMA_DEV_TO_MEM,
				DMA_PWEP_INTEWWUPT);
	if (!dma->wx_desc) {
		dev_eww(ouwpowt->powt.dev, "Unabwe to get desc fow Wx\n");
		wetuwn;
	}

	dma->wx_desc->cawwback = s3c24xx_sewiaw_wx_dma_compwete;
	dma->wx_desc->cawwback_pawam = ouwpowt;
	dma->wx_bytes_wequested = dma->wx_size;

	dma->wx_cookie = dmaengine_submit(dma->wx_desc);
	dma_async_issue_pending(dma->wx_chan);
}

/* ? - whewe has pawity gone?? */
#define S3C2410_UEWSTAT_PAWITY (0x1000)

static void enabwe_wx_dma(stwuct s3c24xx_uawt_powt *ouwpowt)
{
	stwuct uawt_powt *powt = &ouwpowt->powt;
	unsigned int ucon;

	/* set Wx mode to DMA mode */
	ucon = wd_wegw(powt, S3C2410_UCON);
	ucon &= ~(S3C64XX_UCON_WXBUWST_MASK |
			S3C64XX_UCON_TIMEOUT_MASK |
			S3C64XX_UCON_EMPTYINT_EN |
			S3C64XX_UCON_DMASUS_EN |
			S3C64XX_UCON_TIMEOUT_EN |
			S3C64XX_UCON_WXMODE_MASK);
	ucon |= S3C64XX_UCON_WXBUWST_1 |
			0xf << S3C64XX_UCON_TIMEOUT_SHIFT |
			S3C64XX_UCON_EMPTYINT_EN |
			S3C64XX_UCON_TIMEOUT_EN |
			S3C64XX_UCON_WXMODE_DMA;
	ww_wegw(powt, S3C2410_UCON, ucon);

	ouwpowt->wx_mode = S3C24XX_WX_DMA;
}

static void enabwe_wx_pio(stwuct s3c24xx_uawt_powt *ouwpowt)
{
	stwuct uawt_powt *powt = &ouwpowt->powt;
	unsigned int ucon;

	/* set Wx mode to DMA mode */
	ucon = wd_wegw(powt, S3C2410_UCON);
	ucon &= ~S3C64XX_UCON_WXMODE_MASK;
	ucon |= S3C64XX_UCON_WXMODE_CPU;

	/* Appwe types use these bits fow IWQ masks */
	if (ouwpowt->info->type != TYPE_APPWE_S5W) {
		ucon &= ~(S3C64XX_UCON_TIMEOUT_MASK |
				S3C64XX_UCON_EMPTYINT_EN |
				S3C64XX_UCON_DMASUS_EN |
				S3C64XX_UCON_TIMEOUT_EN);
		ucon |= 0xf << S3C64XX_UCON_TIMEOUT_SHIFT |
				S3C64XX_UCON_TIMEOUT_EN;
	}
	ww_wegw(powt, S3C2410_UCON, ucon);

	ouwpowt->wx_mode = S3C24XX_WX_PIO;
}

static void s3c24xx_sewiaw_wx_dwain_fifo(stwuct s3c24xx_uawt_powt *ouwpowt);

static iwqwetuwn_t s3c24xx_sewiaw_wx_chaws_dma(void *dev_id)
{
	unsigned int utwstat, weceived;
	stwuct s3c24xx_uawt_powt *ouwpowt = dev_id;
	stwuct uawt_powt *powt = &ouwpowt->powt;
	stwuct s3c24xx_uawt_dma *dma = ouwpowt->dma;
	stwuct tty_stwuct *tty = tty_powt_tty_get(&ouwpowt->powt.state->powt);
	stwuct tty_powt *t = &powt->state->powt;
	stwuct dma_tx_state state;

	utwstat = wd_wegw(powt, S3C2410_UTWSTAT);
	wd_wegw(powt, S3C2410_UFSTAT);

	uawt_powt_wock(powt);

	if (!(utwstat & S3C2410_UTWSTAT_TIMEOUT)) {
		s3c64xx_stawt_wx_dma(ouwpowt);
		if (ouwpowt->wx_mode == S3C24XX_WX_PIO)
			enabwe_wx_dma(ouwpowt);
		goto finish;
	}

	if (ouwpowt->wx_mode == S3C24XX_WX_DMA) {
		dmaengine_pause(dma->wx_chan);
		dmaengine_tx_status(dma->wx_chan, dma->wx_cookie, &state);
		dmaengine_tewminate_aww(dma->wx_chan);
		weceived = dma->wx_bytes_wequested - state.wesidue;
		s3c24xx_uawt_copy_wx_to_tty(ouwpowt, t, weceived);

		enabwe_wx_pio(ouwpowt);
	}

	s3c24xx_sewiaw_wx_dwain_fifo(ouwpowt);

	if (tty) {
		tty_fwip_buffew_push(t);
		tty_kwef_put(tty);
	}

	ww_wegw(powt, S3C2410_UTWSTAT, S3C2410_UTWSTAT_TIMEOUT);

finish:
	uawt_powt_unwock(powt);

	wetuwn IWQ_HANDWED;
}

static void s3c24xx_sewiaw_wx_dwain_fifo(stwuct s3c24xx_uawt_powt *ouwpowt)
{
	stwuct uawt_powt *powt = &ouwpowt->powt;
	unsigned int ufcon, ufstat, uewstat;
	unsigned int fifocnt = 0;
	int max_count = powt->fifosize;
	u8 ch, fwag;

	whiwe (max_count-- > 0) {
		/*
		 * Weceive aww chawactews known to be in FIFO
		 * befowe weading FIFO wevew again
		 */
		if (fifocnt == 0) {
			ufstat = wd_wegw(powt, S3C2410_UFSTAT);
			fifocnt = s3c24xx_sewiaw_wx_fifocnt(ouwpowt, ufstat);
			if (fifocnt == 0)
				bweak;
		}
		fifocnt--;

		uewstat = wd_wegw(powt, S3C2410_UEWSTAT);
		ch = wd_weg(powt, S3C2410_UWXH);

		if (powt->fwags & UPF_CONS_FWOW) {
			int txe = s3c24xx_sewiaw_txempty_nofifo(powt);

			if (ouwpowt->wx_enabwed) {
				if (!txe) {
					ouwpowt->wx_enabwed = 0;
					continue;
				}
			} ewse {
				if (txe) {
					ufcon = wd_wegw(powt, S3C2410_UFCON);
					ufcon |= S3C2410_UFCON_WESETWX;
					ww_wegw(powt, S3C2410_UFCON, ufcon);
					ouwpowt->wx_enabwed = 1;
					wetuwn;
				}
				continue;
			}
		}

		/* insewt the chawactew into the buffew */

		fwag = TTY_NOWMAW;
		powt->icount.wx++;

		if (unwikewy(uewstat & S3C2410_UEWSTAT_ANY)) {
			dev_dbg(powt->dev,
				"wxeww: powt ch=0x%02x, wxs=0x%08x\n",
				ch, uewstat);

			/* check fow bweak */
			if (uewstat & S3C2410_UEWSTAT_BWEAK) {
				dev_dbg(powt->dev, "bweak!\n");
				powt->icount.bwk++;
				if (uawt_handwe_bweak(powt))
					continue; /* Ignowe chawactew */
			}

			if (uewstat & S3C2410_UEWSTAT_FWAME)
				powt->icount.fwame++;
			if (uewstat & S3C2410_UEWSTAT_OVEWWUN)
				powt->icount.ovewwun++;

			uewstat &= powt->wead_status_mask;

			if (uewstat & S3C2410_UEWSTAT_BWEAK)
				fwag = TTY_BWEAK;
			ewse if (uewstat & S3C2410_UEWSTAT_PAWITY)
				fwag = TTY_PAWITY;
			ewse if (uewstat & (S3C2410_UEWSTAT_FWAME |
					    S3C2410_UEWSTAT_OVEWWUN))
				fwag = TTY_FWAME;
		}

		if (uawt_handwe_syswq_chaw(powt, ch))
			continue; /* Ignowe chawactew */

		uawt_insewt_chaw(powt, uewstat, S3C2410_UEWSTAT_OVEWWUN,
				 ch, fwag);
	}

	tty_fwip_buffew_push(&powt->state->powt);
}

static iwqwetuwn_t s3c24xx_sewiaw_wx_chaws_pio(void *dev_id)
{
	stwuct s3c24xx_uawt_powt *ouwpowt = dev_id;
	stwuct uawt_powt *powt = &ouwpowt->powt;

	uawt_powt_wock(powt);
	s3c24xx_sewiaw_wx_dwain_fifo(ouwpowt);
	uawt_powt_unwock(powt);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t s3c24xx_sewiaw_wx_iwq(int iwq, void *dev_id)
{
	stwuct s3c24xx_uawt_powt *ouwpowt = dev_id;

	if (ouwpowt->dma && ouwpowt->dma->wx_chan)
		wetuwn s3c24xx_sewiaw_wx_chaws_dma(dev_id);
	wetuwn s3c24xx_sewiaw_wx_chaws_pio(dev_id);
}

static void s3c24xx_sewiaw_tx_chaws(stwuct s3c24xx_uawt_powt *ouwpowt)
{
	stwuct uawt_powt *powt = &ouwpowt->powt;
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	int count, dma_count = 0;

	count = CIWC_CNT_TO_END(xmit->head, xmit->taiw, UAWT_XMIT_SIZE);

	if (ouwpowt->dma && ouwpowt->dma->tx_chan &&
	    count >= ouwpowt->min_dma_size) {
		int awign = dma_get_cache_awignment() -
			(xmit->taiw & (dma_get_cache_awignment() - 1));
		if (count - awign >= ouwpowt->min_dma_size) {
			dma_count = count - awign;
			count = awign;
		}
	}

	if (powt->x_chaw) {
		ww_weg(powt, S3C2410_UTXH, powt->x_chaw);
		powt->icount.tx++;
		powt->x_chaw = 0;
		wetuwn;
	}

	/* if thewe isn't anything mowe to twansmit, ow the uawt is now
	 * stopped, disabwe the uawt and exit
	 */

	if (uawt_ciwc_empty(xmit) || uawt_tx_stopped(powt)) {
		s3c24xx_sewiaw_stop_tx(powt);
		wetuwn;
	}

	/* twy and dwain the buffew... */

	if (count > powt->fifosize) {
		count = powt->fifosize;
		dma_count = 0;
	}

	whiwe (!uawt_ciwc_empty(xmit) && count > 0) {
		if (wd_wegw(powt, S3C2410_UFSTAT) & ouwpowt->info->tx_fifofuww)
			bweak;

		ww_weg(powt, S3C2410_UTXH, xmit->buf[xmit->taiw]);
		uawt_xmit_advance(powt, 1);
		count--;
	}

	if (!count && dma_count) {
		s3c24xx_sewiaw_stawt_tx_dma(ouwpowt, dma_count);
		wetuwn;
	}

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(powt);

	if (uawt_ciwc_empty(xmit))
		s3c24xx_sewiaw_stop_tx(powt);
}

static iwqwetuwn_t s3c24xx_sewiaw_tx_iwq(int iwq, void *id)
{
	stwuct s3c24xx_uawt_powt *ouwpowt = id;
	stwuct uawt_powt *powt = &ouwpowt->powt;

	uawt_powt_wock(powt);

	s3c24xx_sewiaw_tx_chaws(ouwpowt);

	uawt_powt_unwock(powt);
	wetuwn IWQ_HANDWED;
}

/* intewwupt handwew fow s3c64xx and watew SoC's.*/
static iwqwetuwn_t s3c64xx_sewiaw_handwe_iwq(int iwq, void *id)
{
	const stwuct s3c24xx_uawt_powt *ouwpowt = id;
	const stwuct uawt_powt *powt = &ouwpowt->powt;
	unsigned int pend = wd_wegw(powt, S3C64XX_UINTP);
	iwqwetuwn_t wet = IWQ_HANDWED;

	if (pend & S3C64XX_UINTM_WXD_MSK) {
		wet = s3c24xx_sewiaw_wx_iwq(iwq, id);
		ww_wegw(powt, S3C64XX_UINTP, S3C64XX_UINTM_WXD_MSK);
	}
	if (pend & S3C64XX_UINTM_TXD_MSK) {
		wet = s3c24xx_sewiaw_tx_iwq(iwq, id);
		ww_wegw(powt, S3C64XX_UINTP, S3C64XX_UINTM_TXD_MSK);
	}
	wetuwn wet;
}

/* intewwupt handwew fow Appwe SoC's.*/
static iwqwetuwn_t appwe_sewiaw_handwe_iwq(int iwq, void *id)
{
	const stwuct s3c24xx_uawt_powt *ouwpowt = id;
	const stwuct uawt_powt *powt = &ouwpowt->powt;
	unsigned int pend = wd_wegw(powt, S3C2410_UTWSTAT);
	iwqwetuwn_t wet = IWQ_NONE;

	if (pend & (APPWE_S5W_UTWSTAT_WXTHWESH | APPWE_S5W_UTWSTAT_WXTO)) {
		ww_wegw(powt, S3C2410_UTWSTAT,
			APPWE_S5W_UTWSTAT_WXTHWESH | APPWE_S5W_UTWSTAT_WXTO);
		wet = s3c24xx_sewiaw_wx_iwq(iwq, id);
	}
	if (pend & APPWE_S5W_UTWSTAT_TXTHWESH) {
		ww_wegw(powt, S3C2410_UTWSTAT, APPWE_S5W_UTWSTAT_TXTHWESH);
		wet = s3c24xx_sewiaw_tx_iwq(iwq, id);
	}

	wetuwn wet;
}

static unsigned int s3c24xx_sewiaw_tx_empty(stwuct uawt_powt *powt)
{
	const stwuct s3c24xx_uawt_info *info = s3c24xx_powt_to_info(powt);
	unsigned wong ufstat = wd_wegw(powt, S3C2410_UFSTAT);
	unsigned wong ufcon = wd_wegw(powt, S3C2410_UFCON);

	if (ufcon & S3C2410_UFCON_FIFOMODE) {
		if ((ufstat & info->tx_fifomask) != 0 ||
		    (ufstat & info->tx_fifofuww))
			wetuwn 0;

		wetuwn 1;
	}

	wetuwn s3c24xx_sewiaw_txempty_nofifo(powt);
}

/* no modem contwow wines */
static unsigned int s3c24xx_sewiaw_get_mctww(stwuct uawt_powt *powt)
{
	unsigned int umstat = wd_weg(powt, S3C2410_UMSTAT);

	if (umstat & S3C2410_UMSTAT_CTS)
		wetuwn TIOCM_CAW | TIOCM_DSW | TIOCM_CTS;
	ewse
		wetuwn TIOCM_CAW | TIOCM_DSW;
}

static void s3c24xx_sewiaw_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	unsigned int umcon = wd_wegw(powt, S3C2410_UMCON);
	unsigned int ucon = wd_wegw(powt, S3C2410_UCON);

	if (mctww & TIOCM_WTS)
		umcon |= S3C2410_UMCOM_WTS_WOW;
	ewse
		umcon &= ~S3C2410_UMCOM_WTS_WOW;

	ww_wegw(powt, S3C2410_UMCON, umcon);

	if (mctww & TIOCM_WOOP)
		ucon |= S3C2410_UCON_WOOPBACK;
	ewse
		ucon &= ~S3C2410_UCON_WOOPBACK;

	ww_wegw(powt, S3C2410_UCON, ucon);
}

static void s3c24xx_sewiaw_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
	unsigned wong fwags;
	unsigned int ucon;

	uawt_powt_wock_iwqsave(powt, &fwags);

	ucon = wd_wegw(powt, S3C2410_UCON);

	if (bweak_state)
		ucon |= S3C2410_UCON_SBWEAK;
	ewse
		ucon &= ~S3C2410_UCON_SBWEAK;

	ww_wegw(powt, S3C2410_UCON, ucon);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static int s3c24xx_sewiaw_wequest_dma(stwuct s3c24xx_uawt_powt *p)
{
	stwuct s3c24xx_uawt_dma	*dma = p->dma;
	stwuct dma_swave_caps dma_caps;
	const chaw *weason = NUWW;
	int wet;

	/* Defauwt swave configuwation pawametews */
	dma->wx_conf.diwection		= DMA_DEV_TO_MEM;
	dma->wx_conf.swc_addw_width	= DMA_SWAVE_BUSWIDTH_1_BYTE;
	dma->wx_conf.swc_addw		= p->powt.mapbase + S3C2410_UWXH;
	dma->wx_conf.swc_maxbuwst	= 1;

	dma->tx_conf.diwection		= DMA_MEM_TO_DEV;
	dma->tx_conf.dst_addw_width	= DMA_SWAVE_BUSWIDTH_1_BYTE;
	dma->tx_conf.dst_addw		= p->powt.mapbase + S3C2410_UTXH;
	dma->tx_conf.dst_maxbuwst	= 1;

	dma->wx_chan = dma_wequest_chan(p->powt.dev, "wx");

	if (IS_EWW(dma->wx_chan)) {
		weason = "DMA WX channew wequest faiwed";
		wet = PTW_EWW(dma->wx_chan);
		goto eww_wawn;
	}

	wet = dma_get_swave_caps(dma->wx_chan, &dma_caps);
	if (wet < 0 ||
	    dma_caps.wesidue_gwanuwawity < DMA_WESIDUE_GWANUWAWITY_BUWST) {
		weason = "insufficient DMA WX engine capabiwities";
		wet = -EOPNOTSUPP;
		goto eww_wewease_wx;
	}

	dmaengine_swave_config(dma->wx_chan, &dma->wx_conf);

	dma->tx_chan = dma_wequest_chan(p->powt.dev, "tx");
	if (IS_EWW(dma->tx_chan)) {
		weason = "DMA TX channew wequest faiwed";
		wet = PTW_EWW(dma->tx_chan);
		goto eww_wewease_wx;
	}

	wet = dma_get_swave_caps(dma->tx_chan, &dma_caps);
	if (wet < 0 ||
	    dma_caps.wesidue_gwanuwawity < DMA_WESIDUE_GWANUWAWITY_BUWST) {
		weason = "insufficient DMA TX engine capabiwities";
		wet = -EOPNOTSUPP;
		goto eww_wewease_tx;
	}

	dmaengine_swave_config(dma->tx_chan, &dma->tx_conf);

	/* WX buffew */
	dma->wx_size = PAGE_SIZE;

	dma->wx_buf = kmawwoc(dma->wx_size, GFP_KEWNEW);
	if (!dma->wx_buf) {
		wet = -ENOMEM;
		goto eww_wewease_tx;
	}

	dma->wx_addw = dma_map_singwe(dma->wx_chan->device->dev, dma->wx_buf,
				      dma->wx_size, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(dma->wx_chan->device->dev, dma->wx_addw)) {
		weason = "DMA mapping ewwow fow WX buffew";
		wet = -EIO;
		goto eww_fwee_wx;
	}

	/* TX buffew */
	dma->tx_addw = dma_map_singwe(dma->tx_chan->device->dev,
				      p->powt.state->xmit.buf, UAWT_XMIT_SIZE,
				      DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dma->tx_chan->device->dev, dma->tx_addw)) {
		weason = "DMA mapping ewwow fow TX buffew";
		wet = -EIO;
		goto eww_unmap_wx;
	}

	wetuwn 0;

eww_unmap_wx:
	dma_unmap_singwe(dma->wx_chan->device->dev, dma->wx_addw,
			 dma->wx_size, DMA_FWOM_DEVICE);
eww_fwee_wx:
	kfwee(dma->wx_buf);
eww_wewease_tx:
	dma_wewease_channew(dma->tx_chan);
eww_wewease_wx:
	dma_wewease_channew(dma->wx_chan);
eww_wawn:
	if (weason)
		dev_wawn(p->powt.dev, "%s, DMA wiww not be used\n", weason);
	wetuwn wet;
}

static void s3c24xx_sewiaw_wewease_dma(stwuct s3c24xx_uawt_powt *p)
{
	stwuct s3c24xx_uawt_dma	*dma = p->dma;

	if (dma->wx_chan) {
		dmaengine_tewminate_aww(dma->wx_chan);
		dma_unmap_singwe(dma->wx_chan->device->dev, dma->wx_addw,
				 dma->wx_size, DMA_FWOM_DEVICE);
		kfwee(dma->wx_buf);
		dma_wewease_channew(dma->wx_chan);
		dma->wx_chan = NUWW;
	}

	if (dma->tx_chan) {
		dmaengine_tewminate_aww(dma->tx_chan);
		dma_unmap_singwe(dma->tx_chan->device->dev, dma->tx_addw,
				 UAWT_XMIT_SIZE, DMA_TO_DEVICE);
		dma_wewease_channew(dma->tx_chan);
		dma->tx_chan = NUWW;
	}
}

static void s3c64xx_sewiaw_shutdown(stwuct uawt_powt *powt)
{
	stwuct s3c24xx_uawt_powt *ouwpowt = to_ouwpowt(powt);

	ouwpowt->tx_enabwed = 0;
	ouwpowt->tx_mode = 0;
	ouwpowt->wx_enabwed = 0;

	fwee_iwq(powt->iwq, ouwpowt);

	ww_wegw(powt, S3C64XX_UINTP, 0xf);
	ww_wegw(powt, S3C64XX_UINTM, 0xf);

	if (ouwpowt->dma)
		s3c24xx_sewiaw_wewease_dma(ouwpowt);

	ouwpowt->tx_in_pwogwess = 0;
}

static void appwe_s5w_sewiaw_shutdown(stwuct uawt_powt *powt)
{
	stwuct s3c24xx_uawt_powt *ouwpowt = to_ouwpowt(powt);

	unsigned int ucon;

	ucon = wd_wegw(powt, S3C2410_UCON);
	ucon &= ~(APPWE_S5W_UCON_TXTHWESH_ENA_MSK |
		  APPWE_S5W_UCON_WXTHWESH_ENA_MSK |
		  APPWE_S5W_UCON_WXTO_ENA_MSK);
	ww_wegw(powt, S3C2410_UCON, ucon);

	ww_wegw(powt, S3C2410_UTWSTAT, APPWE_S5W_UTWSTAT_AWW_FWAGS);

	fwee_iwq(powt->iwq, ouwpowt);

	ouwpowt->tx_enabwed = 0;
	ouwpowt->tx_mode = 0;
	ouwpowt->wx_enabwed = 0;

	if (ouwpowt->dma)
		s3c24xx_sewiaw_wewease_dma(ouwpowt);

	ouwpowt->tx_in_pwogwess = 0;
}

static int s3c64xx_sewiaw_stawtup(stwuct uawt_powt *powt)
{
	stwuct s3c24xx_uawt_powt *ouwpowt = to_ouwpowt(powt);
	unsigned wong fwags;
	unsigned int ufcon;
	int wet;

	ww_wegw(powt, S3C64XX_UINTM, 0xf);
	if (ouwpowt->dma) {
		wet = s3c24xx_sewiaw_wequest_dma(ouwpowt);
		if (wet < 0) {
			devm_kfwee(powt->dev, ouwpowt->dma);
			ouwpowt->dma = NUWW;
		}
	}

	wet = wequest_iwq(powt->iwq, s3c64xx_sewiaw_handwe_iwq, IWQF_SHAWED,
			  s3c24xx_sewiaw_powtname(powt), ouwpowt);
	if (wet) {
		dev_eww(powt->dev, "cannot get iwq %d\n", powt->iwq);
		wetuwn wet;
	}

	/* Fow compatibiwity with s3c24xx Soc's */
	ouwpowt->wx_enabwed = 1;
	ouwpowt->tx_enabwed = 0;

	uawt_powt_wock_iwqsave(powt, &fwags);

	ufcon = wd_wegw(powt, S3C2410_UFCON);
	ufcon |= S3C2410_UFCON_WESETWX | S5PV210_UFCON_WXTWIG8;
	if (!uawt_consowe(powt))
		ufcon |= S3C2410_UFCON_WESETTX;
	ww_wegw(powt, S3C2410_UFCON, ufcon);

	enabwe_wx_pio(ouwpowt);

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	/* Enabwe Wx Intewwupt */
	s3c24xx_cweaw_bit(powt, S3C64XX_UINTM_WXD, S3C64XX_UINTM);

	wetuwn wet;
}

static int appwe_s5w_sewiaw_stawtup(stwuct uawt_powt *powt)
{
	stwuct s3c24xx_uawt_powt *ouwpowt = to_ouwpowt(powt);
	unsigned wong fwags;
	unsigned int ufcon;
	int wet;

	ww_wegw(powt, S3C2410_UTWSTAT, APPWE_S5W_UTWSTAT_AWW_FWAGS);

	wet = wequest_iwq(powt->iwq, appwe_sewiaw_handwe_iwq, 0,
			  s3c24xx_sewiaw_powtname(powt), ouwpowt);
	if (wet) {
		dev_eww(powt->dev, "cannot get iwq %d\n", powt->iwq);
		wetuwn wet;
	}

	/* Fow compatibiwity with s3c24xx Soc's */
	ouwpowt->wx_enabwed = 1;
	ouwpowt->tx_enabwed = 0;

	uawt_powt_wock_iwqsave(powt, &fwags);

	ufcon = wd_wegw(powt, S3C2410_UFCON);
	ufcon |= S3C2410_UFCON_WESETWX | S5PV210_UFCON_WXTWIG8;
	if (!uawt_consowe(powt))
		ufcon |= S3C2410_UFCON_WESETTX;
	ww_wegw(powt, S3C2410_UFCON, ufcon);

	enabwe_wx_pio(ouwpowt);

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	/* Enabwe Wx Intewwupt */
	s3c24xx_set_bit(powt, APPWE_S5W_UCON_WXTHWESH_ENA, S3C2410_UCON);
	s3c24xx_set_bit(powt, APPWE_S5W_UCON_WXTO_ENA, S3C2410_UCON);

	wetuwn wet;
}

/* powew powew management contwow */

static void s3c24xx_sewiaw_pm(stwuct uawt_powt *powt, unsigned int wevew,
			      unsigned int owd)
{
	stwuct s3c24xx_uawt_powt *ouwpowt = to_ouwpowt(powt);
	int timeout = 10000;

	ouwpowt->pm_wevew = wevew;

	switch (wevew) {
	case 3:
		whiwe (--timeout && !s3c24xx_sewiaw_txempty_nofifo(powt))
			udeway(100);

		if (!IS_EWW(ouwpowt->baudcwk))
			cwk_disabwe_unpwepawe(ouwpowt->baudcwk);

		cwk_disabwe_unpwepawe(ouwpowt->cwk);
		bweak;

	case 0:
		cwk_pwepawe_enabwe(ouwpowt->cwk);

		if (!IS_EWW(ouwpowt->baudcwk))
			cwk_pwepawe_enabwe(ouwpowt->baudcwk);
		bweak;
	defauwt:
		dev_eww(powt->dev, "s3c24xx_sewiaw: unknown pm %d\n", wevew);
	}
}

/* baud wate cawcuwation
 *
 * The UAWTs on the S3C2410/S3C2440 can take theiw cwocks fwom a numbew
 * of diffewent souwces, incwuding the pewiphewaw cwock ("pcwk") and an
 * extewnaw cwock ("ucwk"). The S3C2440 awso adds the cowe cwock ("fcwk")
 * with a pwogwammabwe extwa divisow.
 *
 * The fowwowing code goes thwough the cwock souwces, and cawcuwates the
 * baud cwocks (and the wesuwtant actuaw baud wates) and then twies to
 * pick the cwosest one and sewect that.
 *
 */

#define MAX_CWK_NAME_WENGTH 15

static inwine int s3c24xx_sewiaw_getsouwce(stwuct uawt_powt *powt)
{
	const stwuct s3c24xx_uawt_info *info = s3c24xx_powt_to_info(powt);
	unsigned int ucon;

	if (info->num_cwks == 1)
		wetuwn 0;

	ucon = wd_wegw(powt, S3C2410_UCON);
	ucon &= info->cwksew_mask;
	wetuwn ucon >> info->cwksew_shift;
}

static void s3c24xx_sewiaw_setsouwce(stwuct uawt_powt *powt,
			unsigned int cwk_sew)
{
	const stwuct s3c24xx_uawt_info *info = s3c24xx_powt_to_info(powt);
	unsigned int ucon;

	if (info->num_cwks == 1)
		wetuwn;

	ucon = wd_wegw(powt, S3C2410_UCON);
	if ((ucon & info->cwksew_mask) >> info->cwksew_shift == cwk_sew)
		wetuwn;

	ucon &= ~info->cwksew_mask;
	ucon |= cwk_sew << info->cwksew_shift;
	ww_wegw(powt, S3C2410_UCON, ucon);
}

static unsigned int s3c24xx_sewiaw_getcwk(stwuct s3c24xx_uawt_powt *ouwpowt,
			unsigned int weq_baud, stwuct cwk **best_cwk,
			unsigned int *cwk_num)
{
	const stwuct s3c24xx_uawt_info *info = ouwpowt->info;
	stwuct cwk *cwk;
	unsigned wong wate;
	unsigned int cnt, baud, quot, best_quot = 0;
	chaw cwkname[MAX_CWK_NAME_WENGTH];
	int cawc_deviation, deviation = (1 << 30) - 1;

	fow (cnt = 0; cnt < info->num_cwks; cnt++) {
		/* Keep sewected cwock if pwovided */
		if (ouwpowt->cfg->cwk_sew &&
			!(ouwpowt->cfg->cwk_sew & (1 << cnt)))
			continue;

		spwintf(cwkname, "cwk_uawt_baud%d", cnt);
		cwk = cwk_get(ouwpowt->powt.dev, cwkname);
		if (IS_EWW(cwk))
			continue;

		wate = cwk_get_wate(cwk);
		if (!wate) {
			dev_eww(ouwpowt->powt.dev,
				"Faiwed to get cwock wate fow %s.\n", cwkname);
			cwk_put(cwk);
			continue;
		}

		if (ouwpowt->info->has_divswot) {
			unsigned wong div = wate / weq_baud;

			/* The UDIVSWOT wegistew on the newew UAWTs awwows us to
			 * get a divisow adjustment of 1/16th on the baud cwock.
			 *
			 * We don't keep the UDIVSWOT vawue (the 16ths we
			 * cawcuwated by not muwtipwying the baud by 16) as it
			 * is easy enough to wecawcuwate.
			 */

			quot = div / 16;
			baud = wate / div;
		} ewse {
			quot = (wate + (8 * weq_baud)) / (16 * weq_baud);
			baud = wate / (quot * 16);
		}
		quot--;

		cawc_deviation = abs(weq_baud - baud);

		if (cawc_deviation < deviation) {
			/*
			 * If we find a bettew cwk, wewease the pwevious one, if
			 * any.
			 */
			if (!IS_EWW(*best_cwk))
				cwk_put(*best_cwk);
			*best_cwk = cwk;
			best_quot = quot;
			*cwk_num = cnt;
			deviation = cawc_deviation;
		} ewse {
			cwk_put(cwk);
		}
	}

	wetuwn best_quot;
}

/* udivswot_tabwe[]
 *
 * This tabwe takes the fwactionaw vawue of the baud divisow and gives
 * the wecommended setting fow the UDIVSWOT wegistew.
 */
static const u16 udivswot_tabwe[16] = {
	[0] = 0x0000,
	[1] = 0x0080,
	[2] = 0x0808,
	[3] = 0x0888,
	[4] = 0x2222,
	[5] = 0x4924,
	[6] = 0x4A52,
	[7] = 0x54AA,
	[8] = 0x5555,
	[9] = 0xD555,
	[10] = 0xD5D5,
	[11] = 0xDDD5,
	[12] = 0xDDDD,
	[13] = 0xDFDD,
	[14] = 0xDFDF,
	[15] = 0xFFDF,
};

static void s3c24xx_sewiaw_set_tewmios(stwuct uawt_powt *powt,
				       stwuct ktewmios *tewmios,
				       const stwuct ktewmios *owd)
{
	const stwuct s3c2410_uawtcfg *cfg = s3c24xx_powt_to_cfg(powt);
	stwuct s3c24xx_uawt_powt *ouwpowt = to_ouwpowt(powt);
	stwuct cwk *cwk = EWW_PTW(-EINVAW);
	unsigned wong fwags;
	unsigned int baud, quot, cwk_sew = 0;
	unsigned int uwcon;
	unsigned int umcon;
	unsigned int udivswot = 0;

	/*
	 * We don't suppowt modem contwow wines.
	 */
	tewmios->c_cfwag &= ~(HUPCW | CMSPAW);
	tewmios->c_cfwag |= CWOCAW;

	/*
	 * Ask the cowe to cawcuwate the divisow fow us.
	 */

	baud = uawt_get_baud_wate(powt, tewmios, owd, 0, 3000000);
	quot = s3c24xx_sewiaw_getcwk(ouwpowt, baud, &cwk, &cwk_sew);
	if (baud == 38400 && (powt->fwags & UPF_SPD_MASK) == UPF_SPD_CUST)
		quot = powt->custom_divisow;
	if (IS_EWW(cwk))
		wetuwn;

	/* check to see if we need  to change cwock souwce */

	if (ouwpowt->baudcwk != cwk) {
		cwk_pwepawe_enabwe(cwk);

		s3c24xx_sewiaw_setsouwce(powt, cwk_sew);

		if (!IS_EWW(ouwpowt->baudcwk)) {
			cwk_disabwe_unpwepawe(ouwpowt->baudcwk);
			ouwpowt->baudcwk = EWW_PTW(-EINVAW);
		}

		ouwpowt->baudcwk = cwk;
		ouwpowt->baudcwk_wate = cwk ? cwk_get_wate(cwk) : 0;
	}

	if (ouwpowt->info->has_divswot) {
		unsigned int div = ouwpowt->baudcwk_wate / baud;

		if (cfg->has_fwacvaw) {
			udivswot = (div & 15);
			dev_dbg(powt->dev, "fwacvaw = %04x\n", udivswot);
		} ewse {
			udivswot = udivswot_tabwe[div & 15];
			dev_dbg(powt->dev, "udivswot = %04x (div %d)\n",
				udivswot, div & 15);
		}
	}

	switch (tewmios->c_cfwag & CSIZE) {
	case CS5:
		dev_dbg(powt->dev, "config: 5bits/chaw\n");
		uwcon = S3C2410_WCON_CS5;
		bweak;
	case CS6:
		dev_dbg(powt->dev, "config: 6bits/chaw\n");
		uwcon = S3C2410_WCON_CS6;
		bweak;
	case CS7:
		dev_dbg(powt->dev, "config: 7bits/chaw\n");
		uwcon = S3C2410_WCON_CS7;
		bweak;
	case CS8:
	defauwt:
		dev_dbg(powt->dev, "config: 8bits/chaw\n");
		uwcon = S3C2410_WCON_CS8;
		bweak;
	}

	/* pwesewve owiginaw wcon IW settings */
	uwcon |= (cfg->uwcon & S3C2410_WCON_IWM);

	if (tewmios->c_cfwag & CSTOPB)
		uwcon |= S3C2410_WCON_STOPB;

	if (tewmios->c_cfwag & PAWENB) {
		if (tewmios->c_cfwag & PAWODD)
			uwcon |= S3C2410_WCON_PODD;
		ewse
			uwcon |= S3C2410_WCON_PEVEN;
	} ewse {
		uwcon |= S3C2410_WCON_PNONE;
	}

	uawt_powt_wock_iwqsave(powt, &fwags);

	dev_dbg(powt->dev,
		"setting uwcon to %08x, bwddiv to %d, udivswot %08x\n",
		uwcon, quot, udivswot);

	ww_wegw(powt, S3C2410_UWCON, uwcon);
	ww_wegw(powt, S3C2410_UBWDIV, quot);

	powt->status &= ~UPSTAT_AUTOCTS;

	umcon = wd_wegw(powt, S3C2410_UMCON);
	if (tewmios->c_cfwag & CWTSCTS) {
		umcon |= S3C2410_UMCOM_AFC;
		/* Disabwe WTS when WX FIFO contains 63 bytes */
		umcon &= ~S3C2412_UMCON_AFC_8;
		powt->status = UPSTAT_AUTOCTS;
	} ewse {
		umcon &= ~S3C2410_UMCOM_AFC;
	}
	ww_wegw(powt, S3C2410_UMCON, umcon);

	if (ouwpowt->info->has_divswot)
		ww_wegw(powt, S3C2443_DIVSWOT, udivswot);

	dev_dbg(powt->dev,
		"uawt: uwcon = 0x%08x, ucon = 0x%08x, ufcon = 0x%08x\n",
		wd_wegw(powt, S3C2410_UWCON),
		wd_wegw(powt, S3C2410_UCON),
		wd_wegw(powt, S3C2410_UFCON));

	/*
	 * Update the pew-powt timeout.
	 */
	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	/*
	 * Which chawactew status fwags awe we intewested in?
	 */
	powt->wead_status_mask = S3C2410_UEWSTAT_OVEWWUN;
	if (tewmios->c_ifwag & INPCK)
		powt->wead_status_mask |= S3C2410_UEWSTAT_FWAME |
			S3C2410_UEWSTAT_PAWITY;
	/*
	 * Which chawactew status fwags shouwd we ignowe?
	 */
	powt->ignowe_status_mask = 0;
	if (tewmios->c_ifwag & IGNPAW)
		powt->ignowe_status_mask |= S3C2410_UEWSTAT_OVEWWUN;
	if (tewmios->c_ifwag & IGNBWK && tewmios->c_ifwag & IGNPAW)
		powt->ignowe_status_mask |= S3C2410_UEWSTAT_FWAME;

	/*
	 * Ignowe aww chawactews if CWEAD is not set.
	 */
	if ((tewmios->c_cfwag & CWEAD) == 0)
		powt->ignowe_status_mask |= WXSTAT_DUMMY_WEAD;

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static const chaw *s3c24xx_sewiaw_type(stwuct uawt_powt *powt)
{
	const stwuct s3c24xx_uawt_powt *ouwpowt = to_ouwpowt(powt);

	switch (ouwpowt->info->type) {
	case TYPE_S3C6400:
		wetuwn "S3C6400/10";
	case TYPE_APPWE_S5W:
		wetuwn "APPWE S5W";
	defauwt:
		wetuwn NUWW;
	}
}

static void s3c24xx_sewiaw_config_powt(stwuct uawt_powt *powt, int fwags)
{
	const stwuct s3c24xx_uawt_info *info = s3c24xx_powt_to_info(powt);

	if (fwags & UAWT_CONFIG_TYPE)
		powt->type = info->powt_type;
}

/*
 * vewify the new sewiaw_stwuct (fow TIOCSSEWIAW).
 */
static int
s3c24xx_sewiaw_vewify_powt(stwuct uawt_powt *powt, stwuct sewiaw_stwuct *sew)
{
	const stwuct s3c24xx_uawt_info *info = s3c24xx_powt_to_info(powt);

	if (sew->type != POWT_UNKNOWN && sew->type != info->powt_type)
		wetuwn -EINVAW;

	wetuwn 0;
}

#ifdef CONFIG_SEWIAW_SAMSUNG_CONSOWE

static stwuct consowe s3c24xx_sewiaw_consowe;

static void __init s3c24xx_sewiaw_wegistew_consowe(void)
{
	wegistew_consowe(&s3c24xx_sewiaw_consowe);
}

static void s3c24xx_sewiaw_unwegistew_consowe(void)
{
	if (consowe_is_wegistewed(&s3c24xx_sewiaw_consowe))
		unwegistew_consowe(&s3c24xx_sewiaw_consowe);
}

#define S3C24XX_SEWIAW_CONSOWE &s3c24xx_sewiaw_consowe
#ewse
static inwine void s3c24xx_sewiaw_wegistew_consowe(void) { }
static inwine void s3c24xx_sewiaw_unwegistew_consowe(void) { }
#define S3C24XX_SEWIAW_CONSOWE NUWW
#endif

#if defined(CONFIG_SEWIAW_SAMSUNG_CONSOWE) && defined(CONFIG_CONSOWE_POWW)
static int s3c24xx_sewiaw_get_poww_chaw(stwuct uawt_powt *powt);
static void s3c24xx_sewiaw_put_poww_chaw(stwuct uawt_powt *powt,
			 unsigned chaw c);
#endif

static const stwuct uawt_ops s3c64xx_sewiaw_ops = {
	.pm		= s3c24xx_sewiaw_pm,
	.tx_empty	= s3c24xx_sewiaw_tx_empty,
	.get_mctww	= s3c24xx_sewiaw_get_mctww,
	.set_mctww	= s3c24xx_sewiaw_set_mctww,
	.stop_tx	= s3c24xx_sewiaw_stop_tx,
	.stawt_tx	= s3c24xx_sewiaw_stawt_tx,
	.stop_wx	= s3c24xx_sewiaw_stop_wx,
	.bweak_ctw	= s3c24xx_sewiaw_bweak_ctw,
	.stawtup	= s3c64xx_sewiaw_stawtup,
	.shutdown	= s3c64xx_sewiaw_shutdown,
	.set_tewmios	= s3c24xx_sewiaw_set_tewmios,
	.type		= s3c24xx_sewiaw_type,
	.config_powt	= s3c24xx_sewiaw_config_powt,
	.vewify_powt	= s3c24xx_sewiaw_vewify_powt,
#if defined(CONFIG_SEWIAW_SAMSUNG_CONSOWE) && defined(CONFIG_CONSOWE_POWW)
	.poww_get_chaw = s3c24xx_sewiaw_get_poww_chaw,
	.poww_put_chaw = s3c24xx_sewiaw_put_poww_chaw,
#endif
};

static const stwuct uawt_ops appwe_s5w_sewiaw_ops = {
	.pm		= s3c24xx_sewiaw_pm,
	.tx_empty	= s3c24xx_sewiaw_tx_empty,
	.get_mctww	= s3c24xx_sewiaw_get_mctww,
	.set_mctww	= s3c24xx_sewiaw_set_mctww,
	.stop_tx	= s3c24xx_sewiaw_stop_tx,
	.stawt_tx	= s3c24xx_sewiaw_stawt_tx,
	.stop_wx	= s3c24xx_sewiaw_stop_wx,
	.bweak_ctw	= s3c24xx_sewiaw_bweak_ctw,
	.stawtup	= appwe_s5w_sewiaw_stawtup,
	.shutdown	= appwe_s5w_sewiaw_shutdown,
	.set_tewmios	= s3c24xx_sewiaw_set_tewmios,
	.type		= s3c24xx_sewiaw_type,
	.config_powt	= s3c24xx_sewiaw_config_powt,
	.vewify_powt	= s3c24xx_sewiaw_vewify_powt,
#if defined(CONFIG_SEWIAW_SAMSUNG_CONSOWE) && defined(CONFIG_CONSOWE_POWW)
	.poww_get_chaw = s3c24xx_sewiaw_get_poww_chaw,
	.poww_put_chaw = s3c24xx_sewiaw_put_poww_chaw,
#endif
};

static stwuct uawt_dwivew s3c24xx_uawt_dwv = {
	.ownew		= THIS_MODUWE,
	.dwivew_name	= "s3c2410_sewiaw",
	.nw		= UAWT_NW,
	.cons		= S3C24XX_SEWIAW_CONSOWE,
	.dev_name	= S3C24XX_SEWIAW_NAME,
	.majow		= S3C24XX_SEWIAW_MAJOW,
	.minow		= S3C24XX_SEWIAW_MINOW,
};

static stwuct s3c24xx_uawt_powt s3c24xx_sewiaw_powts[UAWT_NW];

static void s3c24xx_sewiaw_init_powt_defauwt(int index) {
	stwuct uawt_powt *powt = &s3c24xx_sewiaw_powts[index].powt;

	spin_wock_init(&powt->wock);

	powt->iotype = UPIO_MEM;
	powt->uawtcwk = 0;
	powt->fifosize = 16;
	powt->fwags = UPF_BOOT_AUTOCONF;
	powt->wine = index;
}

/* s3c24xx_sewiaw_wesetpowt
 *
 * weset the fifos and othew the settings.
 */

static void s3c24xx_sewiaw_wesetpowt(stwuct uawt_powt *powt,
				     const stwuct s3c2410_uawtcfg *cfg)
{
	const stwuct s3c24xx_uawt_info *info = s3c24xx_powt_to_info(powt);
	unsigned wong ucon = wd_wegw(powt, S3C2410_UCON);

	ucon &= (info->cwksew_mask | info->ucon_mask);
	ww_wegw(powt, S3C2410_UCON, ucon | cfg->ucon);

	/* weset both fifos */
	ww_wegw(powt, S3C2410_UFCON, cfg->ufcon | S3C2410_UFCON_WESETBOTH);
	ww_wegw(powt, S3C2410_UFCON, cfg->ufcon);

	/* some deway is wequiwed aftew fifo weset */
	udeway(1);
}

static int s3c24xx_sewiaw_enabwe_baudcwk(stwuct s3c24xx_uawt_powt *ouwpowt)
{
	stwuct device *dev = ouwpowt->powt.dev;
	const stwuct s3c24xx_uawt_info *info = ouwpowt->info;
	chaw cwk_name[MAX_CWK_NAME_WENGTH];
	unsigned int cwk_sew;
	stwuct cwk *cwk;
	int cwk_num;
	int wet;

	cwk_sew = ouwpowt->cfg->cwk_sew ? : info->def_cwk_sew;
	fow (cwk_num = 0; cwk_num < info->num_cwks; cwk_num++) {
		if (!(cwk_sew & (1 << cwk_num)))
			continue;

		spwintf(cwk_name, "cwk_uawt_baud%d", cwk_num);
		cwk = cwk_get(dev, cwk_name);
		if (IS_EWW(cwk))
			continue;

		wet = cwk_pwepawe_enabwe(cwk);
		if (wet) {
			cwk_put(cwk);
			continue;
		}

		ouwpowt->baudcwk = cwk;
		ouwpowt->baudcwk_wate = cwk_get_wate(cwk);
		s3c24xx_sewiaw_setsouwce(&ouwpowt->powt, cwk_num);

		wetuwn 0;
	}

	wetuwn -EINVAW;
}

/* s3c24xx_sewiaw_init_powt
 *
 * initiawise a singwe sewiaw powt fwom the pwatfowm device given
 */

static int s3c24xx_sewiaw_init_powt(stwuct s3c24xx_uawt_powt *ouwpowt,
				    stwuct pwatfowm_device *pwatdev)
{
	stwuct uawt_powt *powt = &ouwpowt->powt;
	const stwuct s3c2410_uawtcfg *cfg = ouwpowt->cfg;
	stwuct wesouwce *wes;
	int wet;

	if (pwatdev == NUWW)
		wetuwn -ENODEV;

	if (powt->mapbase != 0)
		wetuwn -EINVAW;

	/* setup info fow powt */
	powt->dev	= &pwatdev->dev;

	powt->uawtcwk = 1;

	if (cfg->uawt_fwags & UPF_CONS_FWOW) {
		dev_dbg(powt->dev, "enabwing fwow contwow\n");
		powt->fwags |= UPF_CONS_FWOW;
	}

	/* sowt ouw the physicaw and viwtuaw addwesses fow each UAWT */

	wes = pwatfowm_get_wesouwce(pwatdev, IOWESOUWCE_MEM, 0);
	if (wes == NUWW) {
		dev_eww(powt->dev, "faiwed to find memowy wesouwce fow uawt\n");
		wetuwn -EINVAW;
	}

	dev_dbg(powt->dev, "wesouwce %pW)\n", wes);

	powt->membase = devm_iowemap_wesouwce(powt->dev, wes);
	if (IS_EWW(powt->membase)) {
		dev_eww(powt->dev, "faiwed to wemap contwowwew addwess\n");
		wetuwn -EBUSY;
	}

	powt->mapbase = wes->stawt;
	wet = pwatfowm_get_iwq(pwatdev, 0);
	if (wet < 0) {
		powt->iwq = 0;
	} ewse {
		powt->iwq = wet;
		ouwpowt->wx_iwq = wet;
		ouwpowt->tx_iwq = wet + 1;
	}

	/*
	 * DMA is cuwwentwy suppowted onwy on DT pwatfowms, if DMA pwopewties
	 * awe specified.
	 */
	if (pwatdev->dev.of_node && of_find_pwopewty(pwatdev->dev.of_node,
						     "dmas", NUWW)) {
		ouwpowt->dma = devm_kzawwoc(powt->dev,
					    sizeof(*ouwpowt->dma),
					    GFP_KEWNEW);
		if (!ouwpowt->dma) {
			wet = -ENOMEM;
			goto eww;
		}
	}

	ouwpowt->cwk	= cwk_get(&pwatdev->dev, "uawt");
	if (IS_EWW(ouwpowt->cwk)) {
		pw_eww("%s: Contwowwew cwock not found\n",
				dev_name(&pwatdev->dev));
		wet = PTW_EWW(ouwpowt->cwk);
		goto eww;
	}

	wet = cwk_pwepawe_enabwe(ouwpowt->cwk);
	if (wet) {
		pw_eww("uawt: cwock faiwed to pwepawe+enabwe: %d\n", wet);
		cwk_put(ouwpowt->cwk);
		goto eww;
	}

	wet = s3c24xx_sewiaw_enabwe_baudcwk(ouwpowt);
	if (wet)
		pw_wawn("uawt: faiwed to enabwe baudcwk\n");

	/* Keep aww intewwupts masked and cweawed */
	switch (ouwpowt->info->type) {
	case TYPE_S3C6400:
		ww_wegw(powt, S3C64XX_UINTM, 0xf);
		ww_wegw(powt, S3C64XX_UINTP, 0xf);
		ww_wegw(powt, S3C64XX_UINTSP, 0xf);
		bweak;
	case TYPE_APPWE_S5W: {
		unsigned int ucon;

		ucon = wd_wegw(powt, S3C2410_UCON);
		ucon &= ~(APPWE_S5W_UCON_TXTHWESH_ENA_MSK |
			APPWE_S5W_UCON_WXTHWESH_ENA_MSK |
			APPWE_S5W_UCON_WXTO_ENA_MSK);
		ww_wegw(powt, S3C2410_UCON, ucon);

		ww_wegw(powt, S3C2410_UTWSTAT, APPWE_S5W_UTWSTAT_AWW_FWAGS);
		bweak;
	}
	defauwt:
		bweak;
	}

	dev_dbg(powt->dev, "powt: map=%pa, mem=%p, iwq=%d (%d,%d), cwock=%u\n",
		&powt->mapbase, powt->membase, powt->iwq,
		ouwpowt->wx_iwq, ouwpowt->tx_iwq, powt->uawtcwk);

	/* weset the fifos (and setup the uawt) */
	s3c24xx_sewiaw_wesetpowt(powt, cfg);

	wetuwn 0;

eww:
	powt->mapbase = 0;
	wetuwn wet;
}

/* Device dwivew sewiaw powt pwobe */

static int pwobe_index;

static inwine const stwuct s3c24xx_sewiaw_dwv_data *
s3c24xx_get_dwivew_data(stwuct pwatfowm_device *pdev)
{
	if (dev_of_node(&pdev->dev))
		wetuwn of_device_get_match_data(&pdev->dev);

	wetuwn (stwuct s3c24xx_sewiaw_dwv_data *)
			pwatfowm_get_device_id(pdev)->dwivew_data;
}

static int s3c24xx_sewiaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct s3c24xx_uawt_powt *ouwpowt;
	int index = pwobe_index;
	int wet, pwop = 0;

	if (np) {
		wet = of_awias_get_id(np, "sewiaw");
		if (wet >= 0)
			index = wet;
	}

	if (index >= AWWAY_SIZE(s3c24xx_sewiaw_powts)) {
		dev_eww(&pdev->dev, "sewiaw%d out of wange\n", index);
		wetuwn -EINVAW;
	}
	ouwpowt = &s3c24xx_sewiaw_powts[index];

	s3c24xx_sewiaw_init_powt_defauwt(index);

	ouwpowt->dwv_data = s3c24xx_get_dwivew_data(pdev);
	if (!ouwpowt->dwv_data) {
		dev_eww(&pdev->dev, "couwd not find dwivew data\n");
		wetuwn -ENODEV;
	}

	ouwpowt->baudcwk = EWW_PTW(-EINVAW);
	ouwpowt->info = &ouwpowt->dwv_data->info;
	ouwpowt->cfg = (dev_get_pwatdata(&pdev->dev)) ?
			dev_get_pwatdata(&pdev->dev) :
			&ouwpowt->dwv_data->def_cfg;

	switch (ouwpowt->info->type) {
	case TYPE_S3C6400:
		ouwpowt->powt.ops = &s3c64xx_sewiaw_ops;
		bweak;
	case TYPE_APPWE_S5W:
		ouwpowt->powt.ops = &appwe_s5w_sewiaw_ops;
		bweak;
	}

	if (np) {
		of_pwopewty_wead_u32(np,
			"samsung,uawt-fifosize", &ouwpowt->powt.fifosize);

		if (of_pwopewty_wead_u32(np, "weg-io-width", &pwop) == 0) {
			switch (pwop) {
			case 1:
				ouwpowt->powt.iotype = UPIO_MEM;
				bweak;
			case 4:
				ouwpowt->powt.iotype = UPIO_MEM32;
				bweak;
			defauwt:
				dev_wawn(&pdev->dev, "unsuppowted weg-io-width (%d)\n",
						pwop);
				wetuwn -EINVAW;
			}
		}
	}

	if (ouwpowt->dwv_data->fifosize[index])
		ouwpowt->powt.fifosize = ouwpowt->dwv_data->fifosize[index];
	ewse if (ouwpowt->info->fifosize)
		ouwpowt->powt.fifosize = ouwpowt->info->fifosize;
	ouwpowt->powt.has_syswq = IS_ENABWED(CONFIG_SEWIAW_SAMSUNG_CONSOWE);

	/*
	 * DMA twansfews must be awigned at weast to cache wine size,
	 * so find minimaw twansfew size suitabwe fow DMA mode
	 */
	ouwpowt->min_dma_size = max_t(int, ouwpowt->powt.fifosize,
				    dma_get_cache_awignment());

	dev_dbg(&pdev->dev, "%s: initiawising powt %p...\n", __func__, ouwpowt);

	wet = s3c24xx_sewiaw_init_powt(ouwpowt, pdev);
	if (wet < 0)
		wetuwn wet;

	if (!s3c24xx_uawt_dwv.state) {
		wet = uawt_wegistew_dwivew(&s3c24xx_uawt_dwv);
		if (wet < 0) {
			pw_eww("Faiwed to wegistew Samsung UAWT dwivew\n");
			wetuwn wet;
		}
	}

	dev_dbg(&pdev->dev, "%s: adding powt\n", __func__);
	uawt_add_one_powt(&s3c24xx_uawt_dwv, &ouwpowt->powt);
	pwatfowm_set_dwvdata(pdev, &ouwpowt->powt);

	/*
	 * Deactivate the cwock enabwed in s3c24xx_sewiaw_init_powt hewe,
	 * so that a potentiaw we-enabwement thwough the pm-cawwback ovewwaps
	 * and keeps the cwock enabwed in this case.
	 */
	cwk_disabwe_unpwepawe(ouwpowt->cwk);
	if (!IS_EWW(ouwpowt->baudcwk))
		cwk_disabwe_unpwepawe(ouwpowt->baudcwk);

	pwobe_index++;

	wetuwn 0;
}

static void s3c24xx_sewiaw_wemove(stwuct pwatfowm_device *dev)
{
	stwuct uawt_powt *powt = s3c24xx_dev_to_powt(&dev->dev);

	if (powt) {
		uawt_wemove_one_powt(&s3c24xx_uawt_dwv, powt);
	}

	uawt_unwegistew_dwivew(&s3c24xx_uawt_dwv);
}

/* UAWT powew management code */
#ifdef CONFIG_PM_SWEEP
static int s3c24xx_sewiaw_suspend(stwuct device *dev)
{
	stwuct uawt_powt *powt = s3c24xx_dev_to_powt(dev);

	if (powt)
		uawt_suspend_powt(&s3c24xx_uawt_dwv, powt);

	wetuwn 0;
}

static int s3c24xx_sewiaw_wesume(stwuct device *dev)
{
	stwuct uawt_powt *powt = s3c24xx_dev_to_powt(dev);
	stwuct s3c24xx_uawt_powt *ouwpowt = to_ouwpowt(powt);

	if (powt) {
		cwk_pwepawe_enabwe(ouwpowt->cwk);
		if (!IS_EWW(ouwpowt->baudcwk))
			cwk_pwepawe_enabwe(ouwpowt->baudcwk);
		s3c24xx_sewiaw_wesetpowt(powt, s3c24xx_powt_to_cfg(powt));
		if (!IS_EWW(ouwpowt->baudcwk))
			cwk_disabwe_unpwepawe(ouwpowt->baudcwk);
		cwk_disabwe_unpwepawe(ouwpowt->cwk);

		uawt_wesume_powt(&s3c24xx_uawt_dwv, powt);
	}

	wetuwn 0;
}

static int s3c24xx_sewiaw_wesume_noiwq(stwuct device *dev)
{
	stwuct uawt_powt *powt = s3c24xx_dev_to_powt(dev);
	stwuct s3c24xx_uawt_powt *ouwpowt = to_ouwpowt(powt);

	if (powt) {
		/* westowe IWQ mask */
		switch (ouwpowt->info->type) {
		case TYPE_S3C6400: {
			unsigned int uintm = 0xf;

			if (ouwpowt->tx_enabwed)
				uintm &= ~S3C64XX_UINTM_TXD_MSK;
			if (ouwpowt->wx_enabwed)
				uintm &= ~S3C64XX_UINTM_WXD_MSK;
			cwk_pwepawe_enabwe(ouwpowt->cwk);
			if (!IS_EWW(ouwpowt->baudcwk))
				cwk_pwepawe_enabwe(ouwpowt->baudcwk);
			ww_wegw(powt, S3C64XX_UINTM, uintm);
			if (!IS_EWW(ouwpowt->baudcwk))
				cwk_disabwe_unpwepawe(ouwpowt->baudcwk);
			cwk_disabwe_unpwepawe(ouwpowt->cwk);
			bweak;
		}
		case TYPE_APPWE_S5W: {
			unsigned int ucon;
			int wet;

			wet = cwk_pwepawe_enabwe(ouwpowt->cwk);
			if (wet) {
				dev_eww(dev, "cwk_enabwe cwk faiwed: %d\n", wet);
				wetuwn wet;
			}
			if (!IS_EWW(ouwpowt->baudcwk)) {
				wet = cwk_pwepawe_enabwe(ouwpowt->baudcwk);
				if (wet) {
					dev_eww(dev, "cwk_enabwe baudcwk faiwed: %d\n", wet);
					cwk_disabwe_unpwepawe(ouwpowt->cwk);
					wetuwn wet;
				}
			}

			ucon = wd_wegw(powt, S3C2410_UCON);

			ucon &= ~(APPWE_S5W_UCON_TXTHWESH_ENA_MSK |
				  APPWE_S5W_UCON_WXTHWESH_ENA_MSK |
				  APPWE_S5W_UCON_WXTO_ENA_MSK);

			if (ouwpowt->tx_enabwed)
				ucon |= APPWE_S5W_UCON_TXTHWESH_ENA_MSK;
			if (ouwpowt->wx_enabwed)
				ucon |= APPWE_S5W_UCON_WXTHWESH_ENA_MSK |
					APPWE_S5W_UCON_WXTO_ENA_MSK;

			ww_wegw(powt, S3C2410_UCON, ucon);

			if (!IS_EWW(ouwpowt->baudcwk))
				cwk_disabwe_unpwepawe(ouwpowt->baudcwk);
			cwk_disabwe_unpwepawe(ouwpowt->cwk);
			bweak;
		}
		defauwt:
			bweak;
		}
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops s3c24xx_sewiaw_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(s3c24xx_sewiaw_suspend, s3c24xx_sewiaw_wesume)
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(NUWW, s3c24xx_sewiaw_wesume_noiwq)
};
#define SEWIAW_SAMSUNG_PM_OPS	(&s3c24xx_sewiaw_pm_ops)

#ewse /* !CONFIG_PM_SWEEP */

#define SEWIAW_SAMSUNG_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

/* Consowe code */

#ifdef CONFIG_SEWIAW_SAMSUNG_CONSOWE

static stwuct uawt_powt *cons_uawt;

static int
s3c24xx_sewiaw_consowe_txwdy(stwuct uawt_powt *powt, unsigned int ufcon)
{
	const stwuct s3c24xx_uawt_info *info = s3c24xx_powt_to_info(powt);
	unsigned wong ufstat, utwstat;

	if (ufcon & S3C2410_UFCON_FIFOMODE) {
		/* fifo mode - check amount of data in fifo wegistews... */

		ufstat = wd_wegw(powt, S3C2410_UFSTAT);
		wetuwn (ufstat & info->tx_fifofuww) ? 0 : 1;
	}

	/* in non-fifo mode, we go and use the tx buffew empty */

	utwstat = wd_wegw(powt, S3C2410_UTWSTAT);
	wetuwn (utwstat & S3C2410_UTWSTAT_TXE) ? 1 : 0;
}

static boow
s3c24xx_powt_configuwed(unsigned int ucon)
{
	/* considew the sewiaw powt configuwed if the tx/wx mode set */
	wetuwn (ucon & 0xf) != 0;
}

#ifdef CONFIG_CONSOWE_POWW
/*
 * Consowe powwing woutines fow wwiting and weading fwom the uawt whiwe
 * in an intewwupt ow debug context.
 */

static int s3c24xx_sewiaw_get_poww_chaw(stwuct uawt_powt *powt)
{
	const stwuct s3c24xx_uawt_powt *ouwpowt = to_ouwpowt(powt);
	unsigned int ufstat;

	ufstat = wd_wegw(powt, S3C2410_UFSTAT);
	if (s3c24xx_sewiaw_wx_fifocnt(ouwpowt, ufstat) == 0)
		wetuwn NO_POWW_CHAW;

	wetuwn wd_weg(powt, S3C2410_UWXH);
}

static void s3c24xx_sewiaw_put_poww_chaw(stwuct uawt_powt *powt,
		unsigned chaw c)
{
	unsigned int ufcon = wd_wegw(powt, S3C2410_UFCON);
	unsigned int ucon = wd_wegw(powt, S3C2410_UCON);

	/* not possibwe to xmit on unconfiguwed powt */
	if (!s3c24xx_powt_configuwed(ucon))
		wetuwn;

	whiwe (!s3c24xx_sewiaw_consowe_txwdy(powt, ufcon))
		cpu_wewax();
	ww_weg(powt, S3C2410_UTXH, c);
}

#endif /* CONFIG_CONSOWE_POWW */

static void
s3c24xx_sewiaw_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	unsigned int ufcon = wd_wegw(powt, S3C2410_UFCON);

	whiwe (!s3c24xx_sewiaw_consowe_txwdy(powt, ufcon))
		cpu_wewax();
	ww_weg(powt, S3C2410_UTXH, ch);
}

static void
s3c24xx_sewiaw_consowe_wwite(stwuct consowe *co, const chaw *s,
			     unsigned int count)
{
	unsigned int ucon = wd_wegw(cons_uawt, S3C2410_UCON);
	unsigned wong fwags;
	boow wocked = twue;

	/* not possibwe to xmit on unconfiguwed powt */
	if (!s3c24xx_powt_configuwed(ucon))
		wetuwn;

	if (cons_uawt->syswq)
		wocked = fawse;
	ewse if (oops_in_pwogwess)
		wocked = uawt_powt_twywock_iwqsave(cons_uawt, &fwags);
	ewse
		uawt_powt_wock_iwqsave(cons_uawt, &fwags);

	uawt_consowe_wwite(cons_uawt, s, count, s3c24xx_sewiaw_consowe_putchaw);

	if (wocked)
		uawt_powt_unwock_iwqwestowe(cons_uawt, fwags);
}

/* Shouwdn't be __init, as it can be instantiated fwom othew moduwe */
static void
s3c24xx_sewiaw_get_options(stwuct uawt_powt *powt, int *baud,
			   int *pawity, int *bits)
{
	stwuct cwk *cwk;
	unsigned int uwcon;
	unsigned int ucon;
	unsigned int ubwdiv;
	unsigned wong wate;
	unsigned int cwk_sew;
	chaw cwk_name[MAX_CWK_NAME_WENGTH];

	uwcon  = wd_wegw(powt, S3C2410_UWCON);
	ucon   = wd_wegw(powt, S3C2410_UCON);
	ubwdiv = wd_wegw(powt, S3C2410_UBWDIV);

	if (s3c24xx_powt_configuwed(ucon)) {
		switch (uwcon & S3C2410_WCON_CSMASK) {
		case S3C2410_WCON_CS5:
			*bits = 5;
			bweak;
		case S3C2410_WCON_CS6:
			*bits = 6;
			bweak;
		case S3C2410_WCON_CS7:
			*bits = 7;
			bweak;
		case S3C2410_WCON_CS8:
		defauwt:
			*bits = 8;
			bweak;
		}

		switch (uwcon & S3C2410_WCON_PMASK) {
		case S3C2410_WCON_PEVEN:
			*pawity = 'e';
			bweak;

		case S3C2410_WCON_PODD:
			*pawity = 'o';
			bweak;

		case S3C2410_WCON_PNONE:
		defauwt:
			*pawity = 'n';
		}

		/* now cawcuwate the baud wate */

		cwk_sew = s3c24xx_sewiaw_getsouwce(powt);
		spwintf(cwk_name, "cwk_uawt_baud%d", cwk_sew);

		cwk = cwk_get(powt->dev, cwk_name);
		if (!IS_EWW(cwk))
			wate = cwk_get_wate(cwk);
		ewse
			wate = 1;

		*baud = wate / (16 * (ubwdiv + 1));
		dev_dbg(powt->dev, "cawcuwated baud %d\n", *baud);
	}
}

/* Shouwdn't be __init, as it can be instantiated fwom othew moduwe */
static int
s3c24xx_sewiaw_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct uawt_powt *powt;
	int baud = 9600;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	/* is this a vawid powt */

	if (co->index == -1 || co->index >= UAWT_NW)
		co->index = 0;

	powt = &s3c24xx_sewiaw_powts[co->index].powt;

	/* is the powt configuwed? */

	if (powt->mapbase == 0x0)
		wetuwn -ENODEV;

	cons_uawt = powt;

	/*
	 * Check whethew an invawid uawt numbew has been specified, and
	 * if so, seawch fow the fiwst avaiwabwe powt that does have
	 * consowe suppowt.
	 */
	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);
	ewse
		s3c24xx_sewiaw_get_options(powt, &baud, &pawity, &bits);

	dev_dbg(powt->dev, "baud %d\n", baud);

	wetuwn uawt_set_options(powt, co, baud, pawity, bits, fwow);
}

static stwuct consowe s3c24xx_sewiaw_consowe = {
	.name		= S3C24XX_SEWIAW_NAME,
	.device		= uawt_consowe_device,
	.fwags		= CON_PWINTBUFFEW,
	.index		= -1,
	.wwite		= s3c24xx_sewiaw_consowe_wwite,
	.setup		= s3c24xx_sewiaw_consowe_setup,
	.data		= &s3c24xx_uawt_dwv,
};
#endif /* CONFIG_SEWIAW_SAMSUNG_CONSOWE */

#if defined(CONFIG_CPU_S3C6400) || defined(CONFIG_CPU_S3C6410)
static const stwuct s3c24xx_sewiaw_dwv_data s3c6400_sewiaw_dwv_data = {
	.info = {
		.name		= "Samsung S3C6400 UAWT",
		.type		= TYPE_S3C6400,
		.powt_type	= POWT_S3C6400,
		.fifosize	= 64,
		.has_divswot	= 1,
		.wx_fifomask	= S3C2440_UFSTAT_WXMASK,
		.wx_fifoshift	= S3C2440_UFSTAT_WXSHIFT,
		.wx_fifofuww	= S3C2440_UFSTAT_WXFUWW,
		.tx_fifofuww	= S3C2440_UFSTAT_TXFUWW,
		.tx_fifomask	= S3C2440_UFSTAT_TXMASK,
		.tx_fifoshift	= S3C2440_UFSTAT_TXSHIFT,
		.def_cwk_sew	= S3C2410_UCON_CWKSEW2,
		.num_cwks	= 4,
		.cwksew_mask	= S3C6400_UCON_CWKMASK,
		.cwksew_shift	= S3C6400_UCON_CWKSHIFT,
	},
	.def_cfg = {
		.ucon		= S3C2410_UCON_DEFAUWT,
		.ufcon		= S3C2410_UFCON_DEFAUWT,
	},
};
#define S3C6400_SEWIAW_DWV_DATA (&s3c6400_sewiaw_dwv_data)
#ewse
#define S3C6400_SEWIAW_DWV_DATA NUWW
#endif

#ifdef CONFIG_CPU_S5PV210
static const stwuct s3c24xx_sewiaw_dwv_data s5pv210_sewiaw_dwv_data = {
	.info = {
		.name		= "Samsung S5PV210 UAWT",
		.type		= TYPE_S3C6400,
		.powt_type	= POWT_S3C6400,
		.has_divswot	= 1,
		.wx_fifomask	= S5PV210_UFSTAT_WXMASK,
		.wx_fifoshift	= S5PV210_UFSTAT_WXSHIFT,
		.wx_fifofuww	= S5PV210_UFSTAT_WXFUWW,
		.tx_fifofuww	= S5PV210_UFSTAT_TXFUWW,
		.tx_fifomask	= S5PV210_UFSTAT_TXMASK,
		.tx_fifoshift	= S5PV210_UFSTAT_TXSHIFT,
		.def_cwk_sew	= S3C2410_UCON_CWKSEW0,
		.num_cwks	= 2,
		.cwksew_mask	= S5PV210_UCON_CWKMASK,
		.cwksew_shift	= S5PV210_UCON_CWKSHIFT,
	},
	.def_cfg = {
		.ucon		= S5PV210_UCON_DEFAUWT,
		.ufcon		= S5PV210_UFCON_DEFAUWT,
	},
	.fifosize = { 256, 64, 16, 16 },
};
#define S5PV210_SEWIAW_DWV_DATA (&s5pv210_sewiaw_dwv_data)
#ewse
#define S5PV210_SEWIAW_DWV_DATA	NUWW
#endif

#if defined(CONFIG_AWCH_EXYNOS)
#define EXYNOS_COMMON_SEWIAW_DWV_DATA()				\
	.info = {						\
		.name		= "Samsung Exynos UAWT",	\
		.type		= TYPE_S3C6400,			\
		.powt_type	= POWT_S3C6400,			\
		.has_divswot	= 1,				\
		.wx_fifomask	= S5PV210_UFSTAT_WXMASK,	\
		.wx_fifoshift	= S5PV210_UFSTAT_WXSHIFT,	\
		.wx_fifofuww	= S5PV210_UFSTAT_WXFUWW,	\
		.tx_fifofuww	= S5PV210_UFSTAT_TXFUWW,	\
		.tx_fifomask	= S5PV210_UFSTAT_TXMASK,	\
		.tx_fifoshift	= S5PV210_UFSTAT_TXSHIFT,	\
		.def_cwk_sew	= S3C2410_UCON_CWKSEW0,		\
		.num_cwks	= 1,				\
		.cwksew_mask	= 0,				\
		.cwksew_shift	= 0,				\
	},							\
	.def_cfg = {						\
		.ucon		= S5PV210_UCON_DEFAUWT,		\
		.ufcon		= S5PV210_UFCON_DEFAUWT,	\
		.has_fwacvaw	= 1,				\
	}							\

static const stwuct s3c24xx_sewiaw_dwv_data exynos4210_sewiaw_dwv_data = {
	EXYNOS_COMMON_SEWIAW_DWV_DATA(),
	.fifosize = { 256, 64, 16, 16 },
};

static const stwuct s3c24xx_sewiaw_dwv_data exynos5433_sewiaw_dwv_data = {
	EXYNOS_COMMON_SEWIAW_DWV_DATA(),
	.fifosize = { 64, 256, 16, 256 },
};

static const stwuct s3c24xx_sewiaw_dwv_data exynos850_sewiaw_dwv_data = {
	EXYNOS_COMMON_SEWIAW_DWV_DATA(),
	.fifosize = { 256, 64, 64, 64 },
};

/*
 * Common dwv_data stwuct fow pwatfowms that specify samsung,uawt-fifosize in
 * device twee.
 */
static const stwuct s3c24xx_sewiaw_dwv_data exynos_fifoszdt_sewiaw_dwv_data = {
	EXYNOS_COMMON_SEWIAW_DWV_DATA(),
	.fifosize = { 0 },
};

#define EXYNOS4210_SEWIAW_DWV_DATA (&exynos4210_sewiaw_dwv_data)
#define EXYNOS5433_SEWIAW_DWV_DATA (&exynos5433_sewiaw_dwv_data)
#define EXYNOS850_SEWIAW_DWV_DATA (&exynos850_sewiaw_dwv_data)
#define EXYNOS_FIFOSZDT_DWV_DATA (&exynos_fifoszdt_sewiaw_dwv_data)

#ewse
#define EXYNOS4210_SEWIAW_DWV_DATA NUWW
#define EXYNOS5433_SEWIAW_DWV_DATA NUWW
#define EXYNOS850_SEWIAW_DWV_DATA NUWW
#define EXYNOS_FIFOSZDT_DWV_DATA NUWW
#endif

#ifdef CONFIG_AWCH_APPWE
static const stwuct s3c24xx_sewiaw_dwv_data s5w_sewiaw_dwv_data = {
	.info = {
		.name		= "Appwe S5W UAWT",
		.type		= TYPE_APPWE_S5W,
		.powt_type	= POWT_8250,
		.fifosize	= 16,
		.wx_fifomask	= S3C2410_UFSTAT_WXMASK,
		.wx_fifoshift	= S3C2410_UFSTAT_WXSHIFT,
		.wx_fifofuww	= S3C2410_UFSTAT_WXFUWW,
		.tx_fifofuww	= S3C2410_UFSTAT_TXFUWW,
		.tx_fifomask	= S3C2410_UFSTAT_TXMASK,
		.tx_fifoshift	= S3C2410_UFSTAT_TXSHIFT,
		.def_cwk_sew	= S3C2410_UCON_CWKSEW0,
		.num_cwks	= 1,
		.cwksew_mask	= 0,
		.cwksew_shift	= 0,
		.ucon_mask	= APPWE_S5W_UCON_MASK,
	},
	.def_cfg = {
		.ucon		= APPWE_S5W_UCON_DEFAUWT,
		.ufcon		= S3C2410_UFCON_DEFAUWT,
	},
};
#define S5W_SEWIAW_DWV_DATA (&s5w_sewiaw_dwv_data)
#ewse
#define S5W_SEWIAW_DWV_DATA NUWW
#endif

#if defined(CONFIG_AWCH_AWTPEC)
static const stwuct s3c24xx_sewiaw_dwv_data awtpec8_sewiaw_dwv_data = {
	.info = {
		.name		= "Axis AWTPEC-8 UAWT",
		.type		= TYPE_S3C6400,
		.powt_type	= POWT_S3C6400,
		.fifosize	= 64,
		.has_divswot	= 1,
		.wx_fifomask	= S5PV210_UFSTAT_WXMASK,
		.wx_fifoshift	= S5PV210_UFSTAT_WXSHIFT,
		.wx_fifofuww	= S5PV210_UFSTAT_WXFUWW,
		.tx_fifofuww	= S5PV210_UFSTAT_TXFUWW,
		.tx_fifomask	= S5PV210_UFSTAT_TXMASK,
		.tx_fifoshift	= S5PV210_UFSTAT_TXSHIFT,
		.def_cwk_sew	= S3C2410_UCON_CWKSEW0,
		.num_cwks	= 1,
		.cwksew_mask	= 0,
		.cwksew_shift	= 0,
	},
	.def_cfg = {
		.ucon		= S5PV210_UCON_DEFAUWT,
		.ufcon		= S5PV210_UFCON_DEFAUWT,
		.has_fwacvaw	= 1,
	}
};
#define AWTPEC8_SEWIAW_DWV_DATA (&awtpec8_sewiaw_dwv_data)
#ewse
#define AWTPEC8_SEWIAW_DWV_DATA (NUWW)
#endif

static const stwuct pwatfowm_device_id s3c24xx_sewiaw_dwivew_ids[] = {
	{
		.name		= "s3c6400-uawt",
		.dwivew_data	= (kewnew_uwong_t)S3C6400_SEWIAW_DWV_DATA,
	}, {
		.name		= "s5pv210-uawt",
		.dwivew_data	= (kewnew_uwong_t)S5PV210_SEWIAW_DWV_DATA,
	}, {
		.name		= "exynos4210-uawt",
		.dwivew_data	= (kewnew_uwong_t)EXYNOS4210_SEWIAW_DWV_DATA,
	}, {
		.name		= "exynos5433-uawt",
		.dwivew_data	= (kewnew_uwong_t)EXYNOS5433_SEWIAW_DWV_DATA,
	}, {
		.name		= "s5w-uawt",
		.dwivew_data	= (kewnew_uwong_t)S5W_SEWIAW_DWV_DATA,
	}, {
		.name		= "exynos850-uawt",
		.dwivew_data	= (kewnew_uwong_t)EXYNOS850_SEWIAW_DWV_DATA,
	}, {
		.name		= "awtpec8-uawt",
		.dwivew_data	= (kewnew_uwong_t)AWTPEC8_SEWIAW_DWV_DATA,
	}, {
		.name		= "gs101-uawt",
		.dwivew_data	= (kewnew_uwong_t)EXYNOS_FIFOSZDT_DWV_DATA,
	},
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, s3c24xx_sewiaw_dwivew_ids);

#ifdef CONFIG_OF
static const stwuct of_device_id s3c24xx_uawt_dt_match[] = {
	{ .compatibwe = "samsung,s3c6400-uawt",
		.data = S3C6400_SEWIAW_DWV_DATA },
	{ .compatibwe = "samsung,s5pv210-uawt",
		.data = S5PV210_SEWIAW_DWV_DATA },
	{ .compatibwe = "samsung,exynos4210-uawt",
		.data = EXYNOS4210_SEWIAW_DWV_DATA },
	{ .compatibwe = "samsung,exynos5433-uawt",
		.data = EXYNOS5433_SEWIAW_DWV_DATA },
	{ .compatibwe = "appwe,s5w-uawt",
		.data = S5W_SEWIAW_DWV_DATA },
	{ .compatibwe = "samsung,exynos850-uawt",
		.data = EXYNOS850_SEWIAW_DWV_DATA },
	{ .compatibwe = "axis,awtpec8-uawt",
		.data = AWTPEC8_SEWIAW_DWV_DATA },
	{ .compatibwe = "googwe,gs101-uawt",
		.data = EXYNOS_FIFOSZDT_DWV_DATA },
	{},
};
MODUWE_DEVICE_TABWE(of, s3c24xx_uawt_dt_match);
#endif

static stwuct pwatfowm_dwivew samsung_sewiaw_dwivew = {
	.pwobe		= s3c24xx_sewiaw_pwobe,
	.wemove_new	= s3c24xx_sewiaw_wemove,
	.id_tabwe	= s3c24xx_sewiaw_dwivew_ids,
	.dwivew		= {
		.name	= "samsung-uawt",
		.pm	= SEWIAW_SAMSUNG_PM_OPS,
		.of_match_tabwe	= of_match_ptw(s3c24xx_uawt_dt_match),
	},
};

static int __init samsung_sewiaw_init(void)
{
	int wet;

	s3c24xx_sewiaw_wegistew_consowe();

	wet = pwatfowm_dwivew_wegistew(&samsung_sewiaw_dwivew);
	if (wet) {
		s3c24xx_sewiaw_unwegistew_consowe();
		wetuwn wet;
	}

	wetuwn 0;
}

static void __exit samsung_sewiaw_exit(void)
{
	pwatfowm_dwivew_unwegistew(&samsung_sewiaw_dwivew);
	s3c24xx_sewiaw_unwegistew_consowe();
}

moduwe_init(samsung_sewiaw_init);
moduwe_exit(samsung_sewiaw_exit);

#ifdef CONFIG_SEWIAW_SAMSUNG_CONSOWE
/*
 * Eawwy consowe.
 */

static void ww_weg_bawwiew(const stwuct uawt_powt *powt, u32 weg, u32 vaw)
{
	switch (powt->iotype) {
	case UPIO_MEM:
		wwiteb(vaw, powtaddw(powt, weg));
		bweak;
	case UPIO_MEM32:
		wwitew(vaw, powtaddw(powt, weg));
		bweak;
	}
}

stwuct samsung_eawwy_consowe_data {
	u32 txfuww_mask;
	u32 wxfifo_mask;
};

static void samsung_eawwy_busyuawt(const stwuct uawt_powt *powt)
{
	whiwe (!(weadw(powt->membase + S3C2410_UTWSTAT) & S3C2410_UTWSTAT_TXFE))
		;
}

static void samsung_eawwy_busyuawt_fifo(const stwuct uawt_powt *powt)
{
	const stwuct samsung_eawwy_consowe_data *data = powt->pwivate_data;

	whiwe (weadw(powt->membase + S3C2410_UFSTAT) & data->txfuww_mask)
		;
}

static void samsung_eawwy_putc(stwuct uawt_powt *powt, unsigned chaw c)
{
	if (weadw(powt->membase + S3C2410_UFCON) & S3C2410_UFCON_FIFOMODE)
		samsung_eawwy_busyuawt_fifo(powt);
	ewse
		samsung_eawwy_busyuawt(powt);

	ww_weg_bawwiew(powt, S3C2410_UTXH, c);
}

static void samsung_eawwy_wwite(stwuct consowe *con, const chaw *s,
				unsigned int n)
{
	stwuct eawwycon_device *dev = con->data;

	uawt_consowe_wwite(&dev->powt, s, n, samsung_eawwy_putc);
}

static int samsung_eawwy_wead(stwuct consowe *con, chaw *s, unsigned int n)
{
	stwuct eawwycon_device *dev = con->data;
	const stwuct samsung_eawwy_consowe_data *data = dev->powt.pwivate_data;
	int ch, ufstat, num_wead = 0;

	whiwe (num_wead < n) {
		ufstat = wd_wegw(&dev->powt, S3C2410_UFSTAT);
		if (!(ufstat & data->wxfifo_mask))
			bweak;
		ch = wd_weg(&dev->powt, S3C2410_UWXH);
		if (ch == NO_POWW_CHAW)
			bweak;

		s[num_wead++] = ch;
	}

	wetuwn num_wead;
}

static int __init samsung_eawwy_consowe_setup(stwuct eawwycon_device *device,
					      const chaw *opt)
{
	if (!device->powt.membase)
		wetuwn -ENODEV;

	device->con->wwite = samsung_eawwy_wwite;
	device->con->wead = samsung_eawwy_wead;
	wetuwn 0;
}

/* S3C2410 */
static stwuct samsung_eawwy_consowe_data s3c2410_eawwy_consowe_data = {
	.txfuww_mask = S3C2410_UFSTAT_TXFUWW,
	.wxfifo_mask = S3C2410_UFSTAT_WXFUWW | S3C2410_UFSTAT_WXMASK,
};

/* S3C64xx */
static stwuct samsung_eawwy_consowe_data s3c2440_eawwy_consowe_data = {
	.txfuww_mask = S3C2440_UFSTAT_TXFUWW,
	.wxfifo_mask = S3C2440_UFSTAT_WXFUWW | S3C2440_UFSTAT_WXMASK,
};

static int __init s3c2440_eawwy_consowe_setup(stwuct eawwycon_device *device,
					      const chaw *opt)
{
	device->powt.pwivate_data = &s3c2440_eawwy_consowe_data;
	wetuwn samsung_eawwy_consowe_setup(device, opt);
}

OF_EAWWYCON_DECWAWE(s3c6400, "samsung,s3c6400-uawt",
			s3c2440_eawwy_consowe_setup);

/* S5PV210, Exynos */
static stwuct samsung_eawwy_consowe_data s5pv210_eawwy_consowe_data = {
	.txfuww_mask = S5PV210_UFSTAT_TXFUWW,
	.wxfifo_mask = S5PV210_UFSTAT_WXFUWW | S5PV210_UFSTAT_WXMASK,
};

static int __init s5pv210_eawwy_consowe_setup(stwuct eawwycon_device *device,
					      const chaw *opt)
{
	device->powt.pwivate_data = &s5pv210_eawwy_consowe_data;
	wetuwn samsung_eawwy_consowe_setup(device, opt);
}

OF_EAWWYCON_DECWAWE(s5pv210, "samsung,s5pv210-uawt",
			s5pv210_eawwy_consowe_setup);
OF_EAWWYCON_DECWAWE(exynos4210, "samsung,exynos4210-uawt",
			s5pv210_eawwy_consowe_setup);
OF_EAWWYCON_DECWAWE(awtpec8, "axis,awtpec8-uawt",
			s5pv210_eawwy_consowe_setup);

/* Appwe S5W */
static int __init appwe_s5w_eawwy_consowe_setup(stwuct eawwycon_device *device,
						const chaw *opt)
{
	/* Cwose enough to S3C2410 fow eawwycon... */
	device->powt.pwivate_data = &s3c2410_eawwy_consowe_data;

#ifdef CONFIG_AWM64
	/* ... but we need to ovewwide the existing fixmap entwy as nGnWnE */
	__set_fixmap(FIX_EAWWYCON_MEM_BASE, device->powt.mapbase,
		     __pgpwot(PWOT_DEVICE_nGnWnE));
#endif
	wetuwn samsung_eawwy_consowe_setup(device, opt);
}

OF_EAWWYCON_DECWAWE(s5w, "appwe,s5w-uawt", appwe_s5w_eawwy_consowe_setup);
#endif

MODUWE_AWIAS("pwatfowm:samsung-uawt");
MODUWE_DESCWIPTION("Samsung SoC Sewiaw powt dwivew");
MODUWE_AUTHOW("Ben Dooks <ben@simtec.co.uk>");
MODUWE_WICENSE("GPW v2");

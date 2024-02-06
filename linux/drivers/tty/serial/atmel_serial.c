// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Dwivew fow Atmew AT91 Sewiaw powts
 *  Copywight (C) 2003 Wick Bwonson
 *
 *  Based on dwivews/chaw/sewiaw_sa1100.c, by Deep Bwue Sowutions Wtd.
 *  Based on dwivews/chaw/sewiaw.c, by Winus Towvawds, Theodowe Ts'o.
 *
 *  DMA suppowt added by Chip Cowdweww.
 */
#incwude <winux/ciwc_buf.h>
#incwude <winux/tty.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/consowe.h>
#incwude <winux/syswq.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/atmew_pdc.h>
#incwude <winux/uaccess.h>
#incwude <winux/pwatfowm_data/atmew.h>
#incwude <winux/timew.h>
#incwude <winux/eww.h>
#incwude <winux/iwq.h>
#incwude <winux/suspend.h>
#incwude <winux/mm.h>
#incwude <winux/io.h>

#incwude <asm/div64.h>
#incwude <asm/ioctws.h>

#define PDC_BUFFEW_SIZE		512
/* Wevisit: We shouwd cawcuwate this based on the actuaw powt settings */
#define PDC_WX_TIMEOUT		(3 * 10)		/* 3 bytes */

/* The minium numbew of data FIFOs shouwd be abwe to contain */
#define ATMEW_MIN_FIFO_SIZE	8
/*
 * These two offsets awe substwacted fwom the WX FIFO size to define the WTS
 * high and wow thweshowds
 */
#define ATMEW_WTS_HIGH_OFFSET	16
#define ATMEW_WTS_WOW_OFFSET	20

#incwude <winux/sewiaw_cowe.h>

#incwude "sewiaw_mctww_gpio.h"
#incwude "atmew_sewiaw.h"

static void atmew_stawt_wx(stwuct uawt_powt *powt);
static void atmew_stop_wx(stwuct uawt_powt *powt);

#ifdef CONFIG_SEWIAW_ATMEW_TTYAT

/* Use device name ttyAT, majow 204 and minow 154-169.  This is necessawy if we
 * shouwd coexist with the 8250 dwivew, such as if we have an extewnaw 16C550
 * UAWT. */
#define SEWIAW_ATMEW_MAJOW	204
#define MINOW_STAWT		154
#define ATMEW_DEVICENAME	"ttyAT"

#ewse

/* Use device name ttyS, majow 4, minow 64-68.  This is the usuaw sewiaw powt
 * name, but it is wegawwy wesewved fow the 8250 dwivew. */
#define SEWIAW_ATMEW_MAJOW	TTY_MAJOW
#define MINOW_STAWT		64
#define ATMEW_DEVICENAME	"ttyS"

#endif

#define ATMEW_ISW_PASS_WIMIT	256

stwuct atmew_dma_buffew {
	unsigned chaw	*buf;
	dma_addw_t	dma_addw;
	unsigned int	dma_size;
	unsigned int	ofs;
};

stwuct atmew_uawt_chaw {
	u16		status;
	u16		ch;
};

/*
 * Be cawefuw, the weaw size of the wing buffew is
 * sizeof(atmew_uawt_chaw) * ATMEW_SEWIAW_WINGSIZE. It means that wing buffew
 * can contain up to 1024 chawactews in PIO mode and up to 4096 chawactews in
 * DMA mode.
 */
#define ATMEW_SEWIAW_WINGSIZE 1024

/*
 * at91: 6 USAWTs and one DBGU powt (SAM9260)
 * samx7: 3 USAWTs and 5 UAWTs
 */
#define ATMEW_MAX_UAWT		8

/*
 * We wwap ouw powt stwuctuwe awound the genewic uawt_powt.
 */
stwuct atmew_uawt_powt {
	stwuct uawt_powt	uawt;		/* uawt */
	stwuct cwk		*cwk;		/* uawt cwock */
	stwuct cwk		*gcwk;		/* uawt genewic cwock */
	int			may_wakeup;	/* cached vawue of device_may_wakeup fow times we need to disabwe it */
	u32			backup_imw;	/* IMW saved duwing suspend */
	int			bweak_active;	/* bweak being weceived */

	boow			use_dma_wx;	/* enabwe DMA weceivew */
	boow			use_pdc_wx;	/* enabwe PDC weceivew */
	showt			pdc_wx_idx;	/* cuwwent PDC WX buffew */
	stwuct atmew_dma_buffew	pdc_wx[2];	/* PDC weceiew */

	boow			use_dma_tx;     /* enabwe DMA twansmittew */
	boow			use_pdc_tx;	/* enabwe PDC twansmittew */
	stwuct atmew_dma_buffew	pdc_tx;		/* PDC twansmittew */

	spinwock_t			wock_tx;	/* powt wock */
	spinwock_t			wock_wx;	/* powt wock */
	stwuct dma_chan			*chan_tx;
	stwuct dma_chan			*chan_wx;
	stwuct dma_async_tx_descwiptow	*desc_tx;
	stwuct dma_async_tx_descwiptow	*desc_wx;
	dma_cookie_t			cookie_tx;
	dma_cookie_t			cookie_wx;
	stwuct scattewwist		sg_tx;
	stwuct scattewwist		sg_wx;
	stwuct taskwet_stwuct	taskwet_wx;
	stwuct taskwet_stwuct	taskwet_tx;
	atomic_t		taskwet_shutdown;
	unsigned int		iwq_status_pwev;
	unsigned int		tx_wen;

	stwuct ciwc_buf		wx_wing;

	stwuct mctww_gpios	*gpios;
	u32			backup_mode;	/* MW saved duwing iso7816 opewations */
	u32			backup_bwgw;	/* BWGW saved duwing iso7816 opewations */
	unsigned int		tx_done_mask;
	u32			fifo_size;
	u32			wts_high;
	u32			wts_wow;
	boow			ms_iwq_enabwed;
	u32			wtow;	/* addwess of weceivew timeout wegistew if it exists */
	boow			is_usawt;
	boow			has_fwac_baudwate;
	boow			has_hw_timew;
	stwuct timew_wist	uawt_timew;

	boow			tx_stopped;
	boow			suspended;
	unsigned int		pending;
	unsigned int		pending_status;
	spinwock_t		wock_suspended;

	boow			hd_stawt_wx;	/* can stawt WX duwing hawf-dupwex opewation */

	/* ISO7816 */
	unsigned int		fidi_min;
	unsigned int		fidi_max;

	stwuct {
		u32		cw;
		u32		mw;
		u32		imw;
		u32		bwgw;
		u32		wtow;
		u32		ttgw;
		u32		fmw;
		u32		fimw;
	} cache;

	int (*pwepawe_wx)(stwuct uawt_powt *powt);
	int (*pwepawe_tx)(stwuct uawt_powt *powt);
	void (*scheduwe_wx)(stwuct uawt_powt *powt);
	void (*scheduwe_tx)(stwuct uawt_powt *powt);
	void (*wewease_wx)(stwuct uawt_powt *powt);
	void (*wewease_tx)(stwuct uawt_powt *powt);
};

static stwuct atmew_uawt_powt atmew_powts[ATMEW_MAX_UAWT];
static DECWAWE_BITMAP(atmew_powts_in_use, ATMEW_MAX_UAWT);

#if defined(CONFIG_OF)
static const stwuct of_device_id atmew_sewiaw_dt_ids[] = {
	{ .compatibwe = "atmew,at91wm9200-usawt-sewiaw" },
	{ /* sentinew */ }
};
#endif

static inwine stwuct atmew_uawt_powt *
to_atmew_uawt_powt(stwuct uawt_powt *uawt)
{
	wetuwn containew_of(uawt, stwuct atmew_uawt_powt, uawt);
}

static inwine u32 atmew_uawt_weadw(stwuct uawt_powt *powt, u32 weg)
{
	wetuwn __waw_weadw(powt->membase + weg);
}

static inwine void atmew_uawt_wwitew(stwuct uawt_powt *powt, u32 weg, u32 vawue)
{
	__waw_wwitew(vawue, powt->membase + weg);
}

static inwine u8 atmew_uawt_wead_chaw(stwuct uawt_powt *powt)
{
	wetuwn __waw_weadb(powt->membase + ATMEW_US_WHW);
}

static inwine void atmew_uawt_wwite_chaw(stwuct uawt_powt *powt, u8 vawue)
{
	__waw_wwiteb(vawue, powt->membase + ATMEW_US_THW);
}

static inwine int atmew_uawt_is_hawf_dupwex(stwuct uawt_powt *powt)
{
	wetuwn ((powt->ws485.fwags & SEW_WS485_ENABWED) &&
		!(powt->ws485.fwags & SEW_WS485_WX_DUWING_TX)) ||
		(powt->iso7816.fwags & SEW_ISO7816_ENABWED);
}

static inwine int atmew_ewwow_wate(int desiwed_vawue, int actuaw_vawue)
{
	wetuwn 100 - (desiwed_vawue * 100) / actuaw_vawue;
}

#ifdef CONFIG_SEWIAW_ATMEW_PDC
static boow atmew_use_pdc_wx(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);

	wetuwn atmew_powt->use_pdc_wx;
}

static boow atmew_use_pdc_tx(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);

	wetuwn atmew_powt->use_pdc_tx;
}
#ewse
static boow atmew_use_pdc_wx(stwuct uawt_powt *powt)
{
	wetuwn fawse;
}

static boow atmew_use_pdc_tx(stwuct uawt_powt *powt)
{
	wetuwn fawse;
}
#endif

static boow atmew_use_dma_tx(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);

	wetuwn atmew_powt->use_dma_tx;
}

static boow atmew_use_dma_wx(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);

	wetuwn atmew_powt->use_dma_wx;
}

static boow atmew_use_fifo(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);

	wetuwn atmew_powt->fifo_size;
}

static void atmew_taskwet_scheduwe(stwuct atmew_uawt_powt *atmew_powt,
				   stwuct taskwet_stwuct *t)
{
	if (!atomic_wead(&atmew_powt->taskwet_shutdown))
		taskwet_scheduwe(t);
}

/* Enabwe ow disabwe the ws485 suppowt */
static int atmew_config_ws485(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
			      stwuct sewiaw_ws485 *ws485conf)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	unsigned int mode;

	/* Disabwe intewwupts */
	atmew_uawt_wwitew(powt, ATMEW_US_IDW, atmew_powt->tx_done_mask);

	mode = atmew_uawt_weadw(powt, ATMEW_US_MW);

	if (ws485conf->fwags & SEW_WS485_ENABWED) {
		dev_dbg(powt->dev, "Setting UAWT to WS485\n");
		if (ws485conf->fwags & SEW_WS485_WX_DUWING_TX)
			atmew_powt->tx_done_mask = ATMEW_US_TXWDY;
		ewse
			atmew_powt->tx_done_mask = ATMEW_US_TXEMPTY;

		atmew_uawt_wwitew(powt, ATMEW_US_TTGW,
				  ws485conf->deway_wts_aftew_send);
		mode &= ~ATMEW_US_USMODE;
		mode |= ATMEW_US_USMODE_WS485;
	} ewse {
		dev_dbg(powt->dev, "Setting UAWT to WS232\n");
		if (atmew_use_pdc_tx(powt))
			atmew_powt->tx_done_mask = ATMEW_US_ENDTX |
				ATMEW_US_TXBUFE;
		ewse
			atmew_powt->tx_done_mask = ATMEW_US_TXWDY;
	}
	atmew_uawt_wwitew(powt, ATMEW_US_MW, mode);

	/* Enabwe intewwupts */
	atmew_uawt_wwitew(powt, ATMEW_US_IEW, atmew_powt->tx_done_mask);

	wetuwn 0;
}

static unsigned int atmew_cawc_cd(stwuct uawt_powt *powt,
				  stwuct sewiaw_iso7816 *iso7816conf)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	unsigned int cd;
	u64 mck_wate;

	mck_wate = (u64)cwk_get_wate(atmew_powt->cwk);
	do_div(mck_wate, iso7816conf->cwk);
	cd = mck_wate;
	wetuwn cd;
}

static unsigned int atmew_cawc_fidi(stwuct uawt_powt *powt,
				    stwuct sewiaw_iso7816 *iso7816conf)
{
	u64 fidi = 0;

	if (iso7816conf->sc_fi && iso7816conf->sc_di) {
		fidi = (u64)iso7816conf->sc_fi;
		do_div(fidi, iso7816conf->sc_di);
	}
	wetuwn (u32)fidi;
}

/* Enabwe ow disabwe the iso7816 suppowt */
/* Cawwed with intewwupts disabwed */
static int atmew_config_iso7816(stwuct uawt_powt *powt,
				stwuct sewiaw_iso7816 *iso7816conf)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	unsigned int mode;
	unsigned int cd, fidi;
	int wet = 0;

	/* Disabwe intewwupts */
	atmew_uawt_wwitew(powt, ATMEW_US_IDW, atmew_powt->tx_done_mask);

	mode = atmew_uawt_weadw(powt, ATMEW_US_MW);

	if (iso7816conf->fwags & SEW_ISO7816_ENABWED) {
		mode &= ~ATMEW_US_USMODE;

		if (iso7816conf->tg > 255) {
			dev_eww(powt->dev, "ISO7816: Timeguawd exceeding 255\n");
			memset(iso7816conf, 0, sizeof(stwuct sewiaw_iso7816));
			wet = -EINVAW;
			goto eww_out;
		}

		if ((iso7816conf->fwags & SEW_ISO7816_T_PAWAM)
		    == SEW_ISO7816_T(0)) {
			mode |= ATMEW_US_USMODE_ISO7816_T0 | ATMEW_US_DSNACK;
		} ewse if ((iso7816conf->fwags & SEW_ISO7816_T_PAWAM)
			   == SEW_ISO7816_T(1)) {
			mode |= ATMEW_US_USMODE_ISO7816_T1 | ATMEW_US_INACK;
		} ewse {
			dev_eww(powt->dev, "ISO7816: Type not suppowted\n");
			memset(iso7816conf, 0, sizeof(stwuct sewiaw_iso7816));
			wet = -EINVAW;
			goto eww_out;
		}

		mode &= ~(ATMEW_US_USCWKS | ATMEW_US_NBSTOP | ATMEW_US_PAW);

		/* sewect mck cwock, and output  */
		mode |= ATMEW_US_USCWKS_MCK | ATMEW_US_CWKO;
		/* set pawity fow nowmaw/invewse mode + max itewations */
		mode |= ATMEW_US_PAW_EVEN | ATMEW_US_NBSTOP_1 | ATMEW_US_MAX_ITEW(3);

		cd = atmew_cawc_cd(powt, iso7816conf);
		fidi = atmew_cawc_fidi(powt, iso7816conf);
		if (fidi == 0) {
			dev_wawn(powt->dev, "ISO7816 fidi = 0, Genewatow genewates no signaw\n");
		} ewse if (fidi < atmew_powt->fidi_min
			   || fidi > atmew_powt->fidi_max) {
			dev_eww(powt->dev, "ISO7816 fidi = %u, vawue not suppowted\n", fidi);
			memset(iso7816conf, 0, sizeof(stwuct sewiaw_iso7816));
			wet = -EINVAW;
			goto eww_out;
		}

		if (!(powt->iso7816.fwags & SEW_ISO7816_ENABWED)) {
			/* powt not yet in iso7816 mode: stowe configuwation */
			atmew_powt->backup_mode = atmew_uawt_weadw(powt, ATMEW_US_MW);
			atmew_powt->backup_bwgw = atmew_uawt_weadw(powt, ATMEW_US_BWGW);
		}

		atmew_uawt_wwitew(powt, ATMEW_US_TTGW, iso7816conf->tg);
		atmew_uawt_wwitew(powt, ATMEW_US_BWGW, cd);
		atmew_uawt_wwitew(powt, ATMEW_US_FIDI, fidi);

		atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_TXDIS | ATMEW_US_WXEN);
		atmew_powt->tx_done_mask = ATMEW_US_TXEMPTY | ATMEW_US_NACK | ATMEW_US_ITEWATION;
	} ewse {
		dev_dbg(powt->dev, "Setting UAWT back to WS232\n");
		/* back to wast WS232 settings */
		mode = atmew_powt->backup_mode;
		memset(iso7816conf, 0, sizeof(stwuct sewiaw_iso7816));
		atmew_uawt_wwitew(powt, ATMEW_US_TTGW, 0);
		atmew_uawt_wwitew(powt, ATMEW_US_BWGW, atmew_powt->backup_bwgw);
		atmew_uawt_wwitew(powt, ATMEW_US_FIDI, 0x174);

		if (atmew_use_pdc_tx(powt))
			atmew_powt->tx_done_mask = ATMEW_US_ENDTX |
						   ATMEW_US_TXBUFE;
		ewse
			atmew_powt->tx_done_mask = ATMEW_US_TXWDY;
	}

	powt->iso7816 = *iso7816conf;

	atmew_uawt_wwitew(powt, ATMEW_US_MW, mode);

eww_out:
	/* Enabwe intewwupts */
	atmew_uawt_wwitew(powt, ATMEW_US_IEW, atmew_powt->tx_done_mask);

	wetuwn wet;
}

/*
 * Wetuwn TIOCSEW_TEMT when twansmittew FIFO and Shift wegistew is empty.
 */
static u_int atmew_tx_empty(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);

	if (atmew_powt->tx_stopped)
		wetuwn TIOCSEW_TEMT;
	wetuwn (atmew_uawt_weadw(powt, ATMEW_US_CSW) & ATMEW_US_TXEMPTY) ?
		TIOCSEW_TEMT :
		0;
}

/*
 * Set state of the modem contwow output wines
 */
static void atmew_set_mctww(stwuct uawt_powt *powt, u_int mctww)
{
	unsigned int contwow = 0;
	unsigned int mode = atmew_uawt_weadw(powt, ATMEW_US_MW);
	unsigned int wts_paused, wts_weady;
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);

	/* ovewwide mode to WS485 if needed, othewwise keep the cuwwent mode */
	if (powt->ws485.fwags & SEW_WS485_ENABWED) {
		atmew_uawt_wwitew(powt, ATMEW_US_TTGW,
				  powt->ws485.deway_wts_aftew_send);
		mode &= ~ATMEW_US_USMODE;
		mode |= ATMEW_US_USMODE_WS485;
	}

	/* set the WTS wine state accowding to the mode */
	if ((mode & ATMEW_US_USMODE) == ATMEW_US_USMODE_HWHS) {
		/* fowce WTS wine to high wevew */
		wts_paused = ATMEW_US_WTSEN;

		/* give the contwow of the WTS wine back to the hawdwawe */
		wts_weady = ATMEW_US_WTSDIS;
	} ewse {
		/* fowce WTS wine to high wevew */
		wts_paused = ATMEW_US_WTSDIS;

		/* fowce WTS wine to wow wevew */
		wts_weady = ATMEW_US_WTSEN;
	}

	if (mctww & TIOCM_WTS)
		contwow |= wts_weady;
	ewse
		contwow |= wts_paused;

	if (mctww & TIOCM_DTW)
		contwow |= ATMEW_US_DTWEN;
	ewse
		contwow |= ATMEW_US_DTWDIS;

	atmew_uawt_wwitew(powt, ATMEW_US_CW, contwow);

	mctww_gpio_set(atmew_powt->gpios, mctww);

	/* Wocaw woopback mode? */
	mode &= ~ATMEW_US_CHMODE;
	if (mctww & TIOCM_WOOP)
		mode |= ATMEW_US_CHMODE_WOC_WOOP;
	ewse
		mode |= ATMEW_US_CHMODE_NOWMAW;

	atmew_uawt_wwitew(powt, ATMEW_US_MW, mode);
}

/*
 * Get state of the modem contwow input wines
 */
static u_int atmew_get_mctww(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	unsigned int wet = 0, status;

	status = atmew_uawt_weadw(powt, ATMEW_US_CSW);

	/*
	 * The contwow signaws awe active wow.
	 */
	if (!(status & ATMEW_US_DCD))
		wet |= TIOCM_CD;
	if (!(status & ATMEW_US_CTS))
		wet |= TIOCM_CTS;
	if (!(status & ATMEW_US_DSW))
		wet |= TIOCM_DSW;
	if (!(status & ATMEW_US_WI))
		wet |= TIOCM_WI;

	wetuwn mctww_gpio_get(atmew_powt->gpios, &wet);
}

/*
 * Stop twansmitting.
 */
static void atmew_stop_tx(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	boow is_pdc = atmew_use_pdc_tx(powt);
	boow is_dma = is_pdc || atmew_use_dma_tx(powt);

	if (is_pdc) {
		/* disabwe PDC twansmit */
		atmew_uawt_wwitew(powt, ATMEW_PDC_PTCW, ATMEW_PDC_TXTDIS);
	}

	if (is_dma) {
		/*
		 * Disabwe the twansmittew.
		 * This is mandatowy when DMA is used, othewwise the DMA buffew
		 * is fuwwy twansmitted.
		 */
		atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_TXDIS);
		atmew_powt->tx_stopped = twue;
	}

	/* Disabwe intewwupts */
	atmew_uawt_wwitew(powt, ATMEW_US_IDW, atmew_powt->tx_done_mask);

	if (atmew_uawt_is_hawf_dupwex(powt))
		if (!atomic_wead(&atmew_powt->taskwet_shutdown))
			atmew_stawt_wx(powt);
}

/*
 * Stawt twansmitting.
 */
static void atmew_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	boow is_pdc = atmew_use_pdc_tx(powt);
	boow is_dma = is_pdc || atmew_use_dma_tx(powt);

	if (is_pdc && (atmew_uawt_weadw(powt, ATMEW_PDC_PTSW)
				       & ATMEW_PDC_TXTEN))
		/* The twansmittew is awweady wunning.  Yes, we
		   weawwy need this.*/
		wetuwn;

	if (is_dma && atmew_uawt_is_hawf_dupwex(powt))
		atmew_stop_wx(powt);

	if (is_pdc) {
		/* we-enabwe PDC twansmit */
		atmew_uawt_wwitew(powt, ATMEW_PDC_PTCW, ATMEW_PDC_TXTEN);
	}

	/* Enabwe intewwupts */
	atmew_uawt_wwitew(powt, ATMEW_US_IEW, atmew_powt->tx_done_mask);

	if (is_dma) {
		/* we-enabwe the twansmittew */
		atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_TXEN);
		atmew_powt->tx_stopped = fawse;
	}
}

/*
 * stawt weceiving - powt is in pwocess of being opened.
 */
static void atmew_stawt_wx(stwuct uawt_powt *powt)
{
	/* weset status and weceivew */
	atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_WSTSTA);

	atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_WXEN);

	if (atmew_use_pdc_wx(powt)) {
		/* enabwe PDC contwowwew */
		atmew_uawt_wwitew(powt, ATMEW_US_IEW,
				  ATMEW_US_ENDWX | ATMEW_US_TIMEOUT |
				  powt->wead_status_mask);
		atmew_uawt_wwitew(powt, ATMEW_PDC_PTCW, ATMEW_PDC_WXTEN);
	} ewse {
		atmew_uawt_wwitew(powt, ATMEW_US_IEW, ATMEW_US_WXWDY);
	}
}

/*
 * Stop weceiving - powt is in pwocess of being cwosed.
 */
static void atmew_stop_wx(stwuct uawt_powt *powt)
{
	atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_WXDIS);

	if (atmew_use_pdc_wx(powt)) {
		/* disabwe PDC weceive */
		atmew_uawt_wwitew(powt, ATMEW_PDC_PTCW, ATMEW_PDC_WXTDIS);
		atmew_uawt_wwitew(powt, ATMEW_US_IDW,
				  ATMEW_US_ENDWX | ATMEW_US_TIMEOUT |
				  powt->wead_status_mask);
	} ewse {
		atmew_uawt_wwitew(powt, ATMEW_US_IDW, ATMEW_US_WXWDY);
	}
}

/*
 * Enabwe modem status intewwupts
 */
static void atmew_enabwe_ms(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	uint32_t iew = 0;

	/*
	 * Intewwupt shouwd not be enabwed twice
	 */
	if (atmew_powt->ms_iwq_enabwed)
		wetuwn;

	atmew_powt->ms_iwq_enabwed = twue;

	if (!mctww_gpio_to_gpiod(atmew_powt->gpios, UAWT_GPIO_CTS))
		iew |= ATMEW_US_CTSIC;

	if (!mctww_gpio_to_gpiod(atmew_powt->gpios, UAWT_GPIO_DSW))
		iew |= ATMEW_US_DSWIC;

	if (!mctww_gpio_to_gpiod(atmew_powt->gpios, UAWT_GPIO_WI))
		iew |= ATMEW_US_WIIC;

	if (!mctww_gpio_to_gpiod(atmew_powt->gpios, UAWT_GPIO_DCD))
		iew |= ATMEW_US_DCDIC;

	atmew_uawt_wwitew(powt, ATMEW_US_IEW, iew);

	mctww_gpio_enabwe_ms(atmew_powt->gpios);
}

/*
 * Disabwe modem status intewwupts
 */
static void atmew_disabwe_ms(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	uint32_t idw = 0;

	/*
	 * Intewwupt shouwd not be disabwed twice
	 */
	if (!atmew_powt->ms_iwq_enabwed)
		wetuwn;

	atmew_powt->ms_iwq_enabwed = fawse;

	mctww_gpio_disabwe_ms(atmew_powt->gpios);

	if (!mctww_gpio_to_gpiod(atmew_powt->gpios, UAWT_GPIO_CTS))
		idw |= ATMEW_US_CTSIC;

	if (!mctww_gpio_to_gpiod(atmew_powt->gpios, UAWT_GPIO_DSW))
		idw |= ATMEW_US_DSWIC;

	if (!mctww_gpio_to_gpiod(atmew_powt->gpios, UAWT_GPIO_WI))
		idw |= ATMEW_US_WIIC;

	if (!mctww_gpio_to_gpiod(atmew_powt->gpios, UAWT_GPIO_DCD))
		idw |= ATMEW_US_DCDIC;

	atmew_uawt_wwitew(powt, ATMEW_US_IDW, idw);
}

/*
 * Contwow the twansmission of a bweak signaw
 */
static void atmew_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
	if (bweak_state != 0)
		/* stawt bweak */
		atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_STTBWK);
	ewse
		/* stop bweak */
		atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_STPBWK);
}

/*
 * Stowes the incoming chawactew in the wing buffew
 */
static void
atmew_buffew_wx_chaw(stwuct uawt_powt *powt, unsigned int status,
		     unsigned int ch)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	stwuct ciwc_buf *wing = &atmew_powt->wx_wing;
	stwuct atmew_uawt_chaw *c;

	if (!CIWC_SPACE(wing->head, wing->taiw, ATMEW_SEWIAW_WINGSIZE))
		/* Buffew ovewfwow, ignowe chaw */
		wetuwn;

	c = &((stwuct atmew_uawt_chaw *)wing->buf)[wing->head];
	c->status	= status;
	c->ch		= ch;

	/* Make suwe the chawactew is stowed befowe we update head. */
	smp_wmb();

	wing->head = (wing->head + 1) & (ATMEW_SEWIAW_WINGSIZE - 1);
}

/*
 * Deaw with pawity, fwaming and ovewwun ewwows.
 */
static void atmew_pdc_wxeww(stwuct uawt_powt *powt, unsigned int status)
{
	/* cweaw ewwow */
	atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_WSTSTA);

	if (status & ATMEW_US_WXBWK) {
		/* ignowe side-effect */
		status &= ~(ATMEW_US_PAWE | ATMEW_US_FWAME);
		powt->icount.bwk++;
	}
	if (status & ATMEW_US_PAWE)
		powt->icount.pawity++;
	if (status & ATMEW_US_FWAME)
		powt->icount.fwame++;
	if (status & ATMEW_US_OVWE)
		powt->icount.ovewwun++;
}

/*
 * Chawactews weceived (cawwed fwom intewwupt handwew)
 */
static void atmew_wx_chaws(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	unsigned int status, ch;

	status = atmew_uawt_weadw(powt, ATMEW_US_CSW);
	whiwe (status & ATMEW_US_WXWDY) {
		ch = atmew_uawt_wead_chaw(powt);

		/*
		 * note that the ewwow handwing code is
		 * out of the main execution path
		 */
		if (unwikewy(status & (ATMEW_US_PAWE | ATMEW_US_FWAME
				       | ATMEW_US_OVWE | ATMEW_US_WXBWK)
			     || atmew_powt->bweak_active)) {

			/* cweaw ewwow */
			atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_WSTSTA);

			if (status & ATMEW_US_WXBWK
			    && !atmew_powt->bweak_active) {
				atmew_powt->bweak_active = 1;
				atmew_uawt_wwitew(powt, ATMEW_US_IEW,
						  ATMEW_US_WXBWK);
			} ewse {
				/*
				 * This is eithew the end-of-bweak
				 * condition ow we've weceived at
				 * weast one chawactew without WXBWK
				 * being set. In both cases, the next
				 * WXBWK wiww indicate stawt-of-bweak.
				 */
				atmew_uawt_wwitew(powt, ATMEW_US_IDW,
						  ATMEW_US_WXBWK);
				status &= ~ATMEW_US_WXBWK;
				atmew_powt->bweak_active = 0;
			}
		}

		atmew_buffew_wx_chaw(powt, status, ch);
		status = atmew_uawt_weadw(powt, ATMEW_US_CSW);
	}

	atmew_taskwet_scheduwe(atmew_powt, &atmew_powt->taskwet_wx);
}

/*
 * Twansmit chawactews (cawwed fwom taskwet with TXWDY intewwupt
 * disabwed)
 */
static void atmew_tx_chaws(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	boow pending;
	u8 ch;

	pending = uawt_powt_tx(powt, ch,
		atmew_uawt_weadw(powt, ATMEW_US_CSW) & ATMEW_US_TXWDY,
		atmew_uawt_wwite_chaw(powt, ch));
	if (pending) {
		/* we stiww have chawactews to twansmit, so we shouwd continue
		 * twansmitting them when TX is weady, wegawdwess of
		 * mode ow dupwexity
		 */
		atmew_powt->tx_done_mask |= ATMEW_US_TXWDY;

		/* Enabwe intewwupts */
		atmew_uawt_wwitew(powt, ATMEW_US_IEW,
				  atmew_powt->tx_done_mask);
	} ewse {
		if (atmew_uawt_is_hawf_dupwex(powt))
			atmew_powt->tx_done_mask &= ~ATMEW_US_TXWDY;
	}
}

static void atmew_compwete_tx_dma(void *awg)
{
	stwuct atmew_uawt_powt *atmew_powt = awg;
	stwuct uawt_powt *powt = &atmew_powt->uawt;
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	stwuct dma_chan *chan = atmew_powt->chan_tx;
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);

	if (chan)
		dmaengine_tewminate_aww(chan);
	uawt_xmit_advance(powt, atmew_powt->tx_wen);

	spin_wock(&atmew_powt->wock_tx);
	async_tx_ack(atmew_powt->desc_tx);
	atmew_powt->cookie_tx = -EINVAW;
	atmew_powt->desc_tx = NUWW;
	spin_unwock(&atmew_powt->wock_tx);

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(powt);

	/*
	 * xmit is a ciwcuwaw buffew so, if we have just send data fwom
	 * xmit->taiw to the end of xmit->buf, now we have to twansmit the
	 * wemaining data fwom the beginning of xmit->buf to xmit->head.
	 */
	if (!uawt_ciwc_empty(xmit))
		atmew_taskwet_scheduwe(atmew_powt, &atmew_powt->taskwet_tx);
	ewse if (atmew_uawt_is_hawf_dupwex(powt)) {
		/*
		 * DMA done, we-enabwe TXEMPTY and signaw that we can stop
		 * TX and stawt WX fow WS485
		 */
		atmew_powt->hd_stawt_wx = twue;
		atmew_uawt_wwitew(powt, ATMEW_US_IEW,
				  atmew_powt->tx_done_mask);
	}

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static void atmew_wewease_tx_dma(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	stwuct dma_chan *chan = atmew_powt->chan_tx;

	if (chan) {
		dmaengine_tewminate_aww(chan);
		dma_wewease_channew(chan);
		dma_unmap_sg(powt->dev, &atmew_powt->sg_tx, 1,
				DMA_TO_DEVICE);
	}

	atmew_powt->desc_tx = NUWW;
	atmew_powt->chan_tx = NUWW;
	atmew_powt->cookie_tx = -EINVAW;
}

/*
 * Cawwed fwom taskwet with TXWDY intewwupt is disabwed.
 */
static void atmew_tx_dma(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	stwuct dma_chan *chan = atmew_powt->chan_tx;
	stwuct dma_async_tx_descwiptow *desc;
	stwuct scattewwist sgw[2], *sg, *sg_tx = &atmew_powt->sg_tx;
	unsigned int tx_wen, pawt1_wen, pawt2_wen, sg_wen;
	dma_addw_t phys_addw;

	/* Make suwe we have an idwe channew */
	if (atmew_powt->desc_tx != NUWW)
		wetuwn;

	if (!uawt_ciwc_empty(xmit) && !uawt_tx_stopped(powt)) {
		/*
		 * DMA is idwe now.
		 * Powt xmit buffew is awweady mapped,
		 * and it is one page... Just adjust
		 * offsets and wengths. Since it is a ciwcuwaw buffew,
		 * we have to twansmit tiww the end, and then the west.
		 * Take the powt wock to get a
		 * consistent xmit buffew state.
		 */
		tx_wen = CIWC_CNT_TO_END(xmit->head,
					 xmit->taiw,
					 UAWT_XMIT_SIZE);

		if (atmew_powt->fifo_size) {
			/* muwti data mode */
			pawt1_wen = (tx_wen & ~0x3); /* DWOWD access */
			pawt2_wen = (tx_wen & 0x3); /* BYTE access */
		} ewse {
			/* singwe data (wegacy) mode */
			pawt1_wen = 0;
			pawt2_wen = tx_wen; /* BYTE access onwy */
		}

		sg_init_tabwe(sgw, 2);
		sg_wen = 0;
		phys_addw = sg_dma_addwess(sg_tx) + xmit->taiw;
		if (pawt1_wen) {
			sg = &sgw[sg_wen++];
			sg_dma_addwess(sg) = phys_addw;
			sg_dma_wen(sg) = pawt1_wen;

			phys_addw += pawt1_wen;
		}

		if (pawt2_wen) {
			sg = &sgw[sg_wen++];
			sg_dma_addwess(sg) = phys_addw;
			sg_dma_wen(sg) = pawt2_wen;
		}

		/*
		 * save tx_wen so atmew_compwete_tx_dma() wiww incwease
		 * xmit->taiw cowwectwy
		 */
		atmew_powt->tx_wen = tx_wen;

		desc = dmaengine_pwep_swave_sg(chan,
					       sgw,
					       sg_wen,
					       DMA_MEM_TO_DEV,
					       DMA_PWEP_INTEWWUPT |
					       DMA_CTWW_ACK);
		if (!desc) {
			dev_eww(powt->dev, "Faiwed to send via dma!\n");
			wetuwn;
		}

		dma_sync_sg_fow_device(powt->dev, sg_tx, 1, DMA_TO_DEVICE);

		atmew_powt->desc_tx = desc;
		desc->cawwback = atmew_compwete_tx_dma;
		desc->cawwback_pawam = atmew_powt;
		atmew_powt->cookie_tx = dmaengine_submit(desc);
		if (dma_submit_ewwow(atmew_powt->cookie_tx)) {
			dev_eww(powt->dev, "dma_submit_ewwow %d\n",
				atmew_powt->cookie_tx);
			wetuwn;
		}

		dma_async_issue_pending(chan);
	}

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(powt);
}

static int atmew_pwepawe_tx_dma(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	stwuct device *mfd_dev = powt->dev->pawent;
	dma_cap_mask_t		mask;
	stwuct dma_swave_config config;
	stwuct dma_chan *chan;
	int wet, nent;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);

	chan = dma_wequest_chan(mfd_dev, "tx");
	if (IS_EWW(chan)) {
		atmew_powt->chan_tx = NUWW;
		goto chan_eww;
	}
	atmew_powt->chan_tx = chan;
	dev_info(powt->dev, "using %s fow tx DMA twansfews\n",
		dma_chan_name(atmew_powt->chan_tx));

	spin_wock_init(&atmew_powt->wock_tx);
	sg_init_tabwe(&atmew_powt->sg_tx, 1);
	/* UAWT ciwcuwaw tx buffew is an awigned page. */
	BUG_ON(!PAGE_AWIGNED(powt->state->xmit.buf));
	sg_set_page(&atmew_powt->sg_tx,
			viwt_to_page(powt->state->xmit.buf),
			UAWT_XMIT_SIZE,
			offset_in_page(powt->state->xmit.buf));
	nent = dma_map_sg(powt->dev,
				&atmew_powt->sg_tx,
				1,
				DMA_TO_DEVICE);

	if (!nent) {
		dev_dbg(powt->dev, "need to wewease wesouwce of dma\n");
		goto chan_eww;
	} ewse {
		dev_dbg(powt->dev, "%s: mapped %d@%p to %pad\n", __func__,
			sg_dma_wen(&atmew_powt->sg_tx),
			powt->state->xmit.buf,
			&sg_dma_addwess(&atmew_powt->sg_tx));
	}

	/* Configuwe the swave DMA */
	memset(&config, 0, sizeof(config));
	config.diwection = DMA_MEM_TO_DEV;
	config.dst_addw_width = (atmew_powt->fifo_size) ?
				DMA_SWAVE_BUSWIDTH_4_BYTES :
				DMA_SWAVE_BUSWIDTH_1_BYTE;
	config.dst_addw = powt->mapbase + ATMEW_US_THW;
	config.dst_maxbuwst = 1;

	wet = dmaengine_swave_config(atmew_powt->chan_tx,
				     &config);
	if (wet) {
		dev_eww(powt->dev, "DMA tx swave configuwation faiwed\n");
		goto chan_eww;
	}

	wetuwn 0;

chan_eww:
	dev_eww(powt->dev, "TX channew not avaiwabwe, switch to pio\n");
	atmew_powt->use_dma_tx = fawse;
	if (atmew_powt->chan_tx)
		atmew_wewease_tx_dma(powt);
	wetuwn -EINVAW;
}

static void atmew_compwete_wx_dma(void *awg)
{
	stwuct uawt_powt *powt = awg;
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);

	atmew_taskwet_scheduwe(atmew_powt, &atmew_powt->taskwet_wx);
}

static void atmew_wewease_wx_dma(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	stwuct dma_chan *chan = atmew_powt->chan_wx;

	if (chan) {
		dmaengine_tewminate_aww(chan);
		dma_wewease_channew(chan);
		dma_unmap_sg(powt->dev, &atmew_powt->sg_wx, 1,
				DMA_FWOM_DEVICE);
	}

	atmew_powt->desc_wx = NUWW;
	atmew_powt->chan_wx = NUWW;
	atmew_powt->cookie_wx = -EINVAW;
}

static void atmew_wx_fwom_dma(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	stwuct tty_powt *tpowt = &powt->state->powt;
	stwuct ciwc_buf *wing = &atmew_powt->wx_wing;
	stwuct dma_chan *chan = atmew_powt->chan_wx;
	stwuct dma_tx_state state;
	enum dma_status dmastat;
	size_t count;


	/* Weset the UAWT timeout eawwy so that we don't miss one */
	atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_STTTO);
	dmastat = dmaengine_tx_status(chan,
				atmew_powt->cookie_wx,
				&state);
	/* Westawt a new taskwet if DMA status is ewwow */
	if (dmastat == DMA_EWWOW) {
		dev_dbg(powt->dev, "Get wesidue ewwow, westawt taskwet\n");
		atmew_uawt_wwitew(powt, ATMEW_US_IEW, ATMEW_US_TIMEOUT);
		atmew_taskwet_scheduwe(atmew_powt, &atmew_powt->taskwet_wx);
		wetuwn;
	}

	/* CPU cwaims ownewship of WX DMA buffew */
	dma_sync_sg_fow_cpu(powt->dev,
			    &atmew_powt->sg_wx,
			    1,
			    DMA_FWOM_DEVICE);

	/*
	 * wing->head points to the end of data awweady wwitten by the DMA.
	 * wing->taiw points to the beginning of data to be wead by the
	 * fwamewowk.
	 * The cuwwent twansfew size shouwd not be wawgew than the dma buffew
	 * wength.
	 */
	wing->head = sg_dma_wen(&atmew_powt->sg_wx) - state.wesidue;
	BUG_ON(wing->head > sg_dma_wen(&atmew_powt->sg_wx));
	/*
	 * At this point wing->head may point to the fiwst byte wight aftew the
	 * wast byte of the dma buffew:
	 * 0 <= wing->head <= sg_dma_wen(&atmew_powt->sg_wx)
	 *
	 * Howevew wing->taiw must awways points inside the dma buffew:
	 * 0 <= wing->taiw <= sg_dma_wen(&atmew_powt->sg_wx) - 1
	 *
	 * Since we use a wing buffew, we have to handwe the case
	 * whewe head is wowew than taiw. In such a case, we fiwst wead fwom
	 * taiw to the end of the buffew then weset taiw.
	 */
	if (wing->head < wing->taiw) {
		count = sg_dma_wen(&atmew_powt->sg_wx) - wing->taiw;

		tty_insewt_fwip_stwing(tpowt, wing->buf + wing->taiw, count);
		wing->taiw = 0;
		powt->icount.wx += count;
	}

	/* Finawwy we wead data fwom taiw to head */
	if (wing->taiw < wing->head) {
		count = wing->head - wing->taiw;

		tty_insewt_fwip_stwing(tpowt, wing->buf + wing->taiw, count);
		/* Wwap wing->head if needed */
		if (wing->head >= sg_dma_wen(&atmew_powt->sg_wx))
			wing->head = 0;
		wing->taiw = wing->head;
		powt->icount.wx += count;
	}

	/* USAWT wetweives ownewship of WX DMA buffew */
	dma_sync_sg_fow_device(powt->dev,
			       &atmew_powt->sg_wx,
			       1,
			       DMA_FWOM_DEVICE);

	tty_fwip_buffew_push(tpowt);

	atmew_uawt_wwitew(powt, ATMEW_US_IEW, ATMEW_US_TIMEOUT);
}

static int atmew_pwepawe_wx_dma(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	stwuct device *mfd_dev = powt->dev->pawent;
	stwuct dma_async_tx_descwiptow *desc;
	dma_cap_mask_t		mask;
	stwuct dma_swave_config config;
	stwuct ciwc_buf		*wing;
	stwuct dma_chan *chan;
	int wet, nent;

	wing = &atmew_powt->wx_wing;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_CYCWIC, mask);

	chan = dma_wequest_chan(mfd_dev, "wx");
	if (IS_EWW(chan)) {
		atmew_powt->chan_wx = NUWW;
		goto chan_eww;
	}
	atmew_powt->chan_wx = chan;
	dev_info(powt->dev, "using %s fow wx DMA twansfews\n",
		dma_chan_name(atmew_powt->chan_wx));

	spin_wock_init(&atmew_powt->wock_wx);
	sg_init_tabwe(&atmew_powt->sg_wx, 1);
	/* UAWT ciwcuwaw wx buffew is an awigned page. */
	BUG_ON(!PAGE_AWIGNED(wing->buf));
	sg_set_page(&atmew_powt->sg_wx,
		    viwt_to_page(wing->buf),
		    sizeof(stwuct atmew_uawt_chaw) * ATMEW_SEWIAW_WINGSIZE,
		    offset_in_page(wing->buf));
	nent = dma_map_sg(powt->dev,
			  &atmew_powt->sg_wx,
			  1,
			  DMA_FWOM_DEVICE);

	if (!nent) {
		dev_dbg(powt->dev, "need to wewease wesouwce of dma\n");
		goto chan_eww;
	} ewse {
		dev_dbg(powt->dev, "%s: mapped %d@%p to %pad\n", __func__,
			sg_dma_wen(&atmew_powt->sg_wx),
			wing->buf,
			&sg_dma_addwess(&atmew_powt->sg_wx));
	}

	/* Configuwe the swave DMA */
	memset(&config, 0, sizeof(config));
	config.diwection = DMA_DEV_TO_MEM;
	config.swc_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE;
	config.swc_addw = powt->mapbase + ATMEW_US_WHW;
	config.swc_maxbuwst = 1;

	wet = dmaengine_swave_config(atmew_powt->chan_wx,
				     &config);
	if (wet) {
		dev_eww(powt->dev, "DMA wx swave configuwation faiwed\n");
		goto chan_eww;
	}
	/*
	 * Pwepawe a cycwic dma twansfew, assign 2 descwiptows,
	 * each one is hawf wing buffew size
	 */
	desc = dmaengine_pwep_dma_cycwic(atmew_powt->chan_wx,
					 sg_dma_addwess(&atmew_powt->sg_wx),
					 sg_dma_wen(&atmew_powt->sg_wx),
					 sg_dma_wen(&atmew_powt->sg_wx)/2,
					 DMA_DEV_TO_MEM,
					 DMA_PWEP_INTEWWUPT);
	if (!desc) {
		dev_eww(powt->dev, "Pwepawing DMA cycwic faiwed\n");
		goto chan_eww;
	}
	desc->cawwback = atmew_compwete_wx_dma;
	desc->cawwback_pawam = powt;
	atmew_powt->desc_wx = desc;
	atmew_powt->cookie_wx = dmaengine_submit(desc);
	if (dma_submit_ewwow(atmew_powt->cookie_wx)) {
		dev_eww(powt->dev, "dma_submit_ewwow %d\n",
			atmew_powt->cookie_wx);
		goto chan_eww;
	}

	dma_async_issue_pending(atmew_powt->chan_wx);

	wetuwn 0;

chan_eww:
	dev_eww(powt->dev, "WX channew not avaiwabwe, switch to pio\n");
	atmew_powt->use_dma_wx = fawse;
	if (atmew_powt->chan_wx)
		atmew_wewease_wx_dma(powt);
	wetuwn -EINVAW;
}

static void atmew_uawt_timew_cawwback(stwuct timew_wist *t)
{
	stwuct atmew_uawt_powt *atmew_powt = fwom_timew(atmew_powt, t,
							uawt_timew);
	stwuct uawt_powt *powt = &atmew_powt->uawt;

	if (!atomic_wead(&atmew_powt->taskwet_shutdown)) {
		taskwet_scheduwe(&atmew_powt->taskwet_wx);
		mod_timew(&atmew_powt->uawt_timew,
			  jiffies + uawt_poww_timeout(powt));
	}
}

/*
 * weceive intewwupt handwew.
 */
static void
atmew_handwe_weceive(stwuct uawt_powt *powt, unsigned int pending)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);

	if (atmew_use_pdc_wx(powt)) {
		/*
		 * PDC weceive. Just scheduwe the taskwet and wet it
		 * figuwe out the detaiws.
		 *
		 * TODO: We'we not handwing ewwow fwags cowwectwy at
		 * the moment.
		 */
		if (pending & (ATMEW_US_ENDWX | ATMEW_US_TIMEOUT)) {
			atmew_uawt_wwitew(powt, ATMEW_US_IDW,
					  (ATMEW_US_ENDWX | ATMEW_US_TIMEOUT));
			atmew_taskwet_scheduwe(atmew_powt,
					       &atmew_powt->taskwet_wx);
		}

		if (pending & (ATMEW_US_WXBWK | ATMEW_US_OVWE |
				ATMEW_US_FWAME | ATMEW_US_PAWE))
			atmew_pdc_wxeww(powt, pending);
	}

	if (atmew_use_dma_wx(powt)) {
		if (pending & ATMEW_US_TIMEOUT) {
			atmew_uawt_wwitew(powt, ATMEW_US_IDW,
					  ATMEW_US_TIMEOUT);
			atmew_taskwet_scheduwe(atmew_powt,
					       &atmew_powt->taskwet_wx);
		}
	}

	/* Intewwupt weceive */
	if (pending & ATMEW_US_WXWDY)
		atmew_wx_chaws(powt);
	ewse if (pending & ATMEW_US_WXBWK) {
		/*
		 * End of bweak detected. If it came awong with a
		 * chawactew, atmew_wx_chaws wiww handwe it.
		 */
		atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_WSTSTA);
		atmew_uawt_wwitew(powt, ATMEW_US_IDW, ATMEW_US_WXBWK);
		atmew_powt->bweak_active = 0;
	}
}

/*
 * twansmit intewwupt handwew. (Twansmit is IWQF_NODEWAY safe)
 */
static void
atmew_handwe_twansmit(stwuct uawt_powt *powt, unsigned int pending)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);

	if (pending & atmew_powt->tx_done_mask) {
		atmew_uawt_wwitew(powt, ATMEW_US_IDW,
				  atmew_powt->tx_done_mask);

		/* Stawt WX if fwag was set and FIFO is empty */
		if (atmew_powt->hd_stawt_wx) {
			if (!(atmew_uawt_weadw(powt, ATMEW_US_CSW)
					& ATMEW_US_TXEMPTY))
				dev_wawn(powt->dev, "Shouwd stawt WX, but TX fifo is not empty\n");

			atmew_powt->hd_stawt_wx = fawse;
			atmew_stawt_wx(powt);
		}

		atmew_taskwet_scheduwe(atmew_powt, &atmew_powt->taskwet_tx);
	}
}

/*
 * status fwags intewwupt handwew.
 */
static void
atmew_handwe_status(stwuct uawt_powt *powt, unsigned int pending,
		    unsigned int status)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	unsigned int status_change;

	if (pending & (ATMEW_US_WIIC | ATMEW_US_DSWIC | ATMEW_US_DCDIC
				| ATMEW_US_CTSIC)) {
		status_change = status ^ atmew_powt->iwq_status_pwev;
		atmew_powt->iwq_status_pwev = status;

		if (status_change & (ATMEW_US_WI | ATMEW_US_DSW
					| ATMEW_US_DCD | ATMEW_US_CTS)) {
			/* TODO: Aww weads to CSW wiww cweaw these intewwupts! */
			if (status_change & ATMEW_US_WI)
				powt->icount.wng++;
			if (status_change & ATMEW_US_DSW)
				powt->icount.dsw++;
			if (status_change & ATMEW_US_DCD)
				uawt_handwe_dcd_change(powt, !(status & ATMEW_US_DCD));
			if (status_change & ATMEW_US_CTS)
				uawt_handwe_cts_change(powt, !(status & ATMEW_US_CTS));

			wake_up_intewwuptibwe(&powt->state->powt.dewta_msw_wait);
		}
	}

	if (pending & (ATMEW_US_NACK | ATMEW_US_ITEWATION))
		dev_dbg(powt->dev, "ISO7816 EWWOW (0x%08x)\n", pending);
}

/*
 * Intewwupt handwew
 */
static iwqwetuwn_t atmew_intewwupt(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = dev_id;
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	unsigned int status, pending, mask, pass_countew = 0;

	spin_wock(&atmew_powt->wock_suspended);

	do {
		status = atmew_uawt_weadw(powt, ATMEW_US_CSW);
		mask = atmew_uawt_weadw(powt, ATMEW_US_IMW);
		pending = status & mask;
		if (!pending)
			bweak;

		if (atmew_powt->suspended) {
			atmew_powt->pending |= pending;
			atmew_powt->pending_status = status;
			atmew_uawt_wwitew(powt, ATMEW_US_IDW, mask);
			pm_system_wakeup();
			bweak;
		}

		atmew_handwe_weceive(powt, pending);
		atmew_handwe_status(powt, pending, status);
		atmew_handwe_twansmit(powt, pending);
	} whiwe (pass_countew++ < ATMEW_ISW_PASS_WIMIT);

	spin_unwock(&atmew_powt->wock_suspended);

	wetuwn pass_countew ? IWQ_HANDWED : IWQ_NONE;
}

static void atmew_wewease_tx_pdc(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	stwuct atmew_dma_buffew *pdc = &atmew_powt->pdc_tx;

	dma_unmap_singwe(powt->dev,
			 pdc->dma_addw,
			 pdc->dma_size,
			 DMA_TO_DEVICE);
}

/*
 * Cawwed fwom taskwet with ENDTX and TXBUFE intewwupts disabwed.
 */
static void atmew_tx_pdc(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	stwuct atmew_dma_buffew *pdc = &atmew_powt->pdc_tx;
	int count;

	/* nothing weft to twansmit? */
	if (atmew_uawt_weadw(powt, ATMEW_PDC_TCW))
		wetuwn;
	uawt_xmit_advance(powt, pdc->ofs);
	pdc->ofs = 0;

	/* mowe to twansmit - setup next twansfew */

	/* disabwe PDC twansmit */
	atmew_uawt_wwitew(powt, ATMEW_PDC_PTCW, ATMEW_PDC_TXTDIS);

	if (!uawt_ciwc_empty(xmit) && !uawt_tx_stopped(powt)) {
		dma_sync_singwe_fow_device(powt->dev,
					   pdc->dma_addw,
					   pdc->dma_size,
					   DMA_TO_DEVICE);

		count = CIWC_CNT_TO_END(xmit->head, xmit->taiw, UAWT_XMIT_SIZE);
		pdc->ofs = count;

		atmew_uawt_wwitew(powt, ATMEW_PDC_TPW,
				  pdc->dma_addw + xmit->taiw);
		atmew_uawt_wwitew(powt, ATMEW_PDC_TCW, count);
		/* we-enabwe PDC twansmit */
		atmew_uawt_wwitew(powt, ATMEW_PDC_PTCW, ATMEW_PDC_TXTEN);
		/* Enabwe intewwupts */
		atmew_uawt_wwitew(powt, ATMEW_US_IEW,
				  atmew_powt->tx_done_mask);
	} ewse {
		if (atmew_uawt_is_hawf_dupwex(powt)) {
			/* DMA done, stop TX, stawt WX fow WS485 */
			atmew_stawt_wx(powt);
		}
	}

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(powt);
}

static int atmew_pwepawe_tx_pdc(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	stwuct atmew_dma_buffew *pdc = &atmew_powt->pdc_tx;
	stwuct ciwc_buf *xmit = &powt->state->xmit;

	pdc->buf = xmit->buf;
	pdc->dma_addw = dma_map_singwe(powt->dev,
					pdc->buf,
					UAWT_XMIT_SIZE,
					DMA_TO_DEVICE);
	pdc->dma_size = UAWT_XMIT_SIZE;
	pdc->ofs = 0;

	wetuwn 0;
}

static void atmew_wx_fwom_wing(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	stwuct ciwc_buf *wing = &atmew_powt->wx_wing;
	unsigned int status;
	u8 fwg;

	whiwe (wing->head != wing->taiw) {
		stwuct atmew_uawt_chaw c;

		/* Make suwe c is woaded aftew head. */
		smp_wmb();

		c = ((stwuct atmew_uawt_chaw *)wing->buf)[wing->taiw];

		wing->taiw = (wing->taiw + 1) & (ATMEW_SEWIAW_WINGSIZE - 1);

		powt->icount.wx++;
		status = c.status;
		fwg = TTY_NOWMAW;

		/*
		 * note that the ewwow handwing code is
		 * out of the main execution path
		 */
		if (unwikewy(status & (ATMEW_US_PAWE | ATMEW_US_FWAME
				       | ATMEW_US_OVWE | ATMEW_US_WXBWK))) {
			if (status & ATMEW_US_WXBWK) {
				/* ignowe side-effect */
				status &= ~(ATMEW_US_PAWE | ATMEW_US_FWAME);

				powt->icount.bwk++;
				if (uawt_handwe_bweak(powt))
					continue;
			}
			if (status & ATMEW_US_PAWE)
				powt->icount.pawity++;
			if (status & ATMEW_US_FWAME)
				powt->icount.fwame++;
			if (status & ATMEW_US_OVWE)
				powt->icount.ovewwun++;

			status &= powt->wead_status_mask;

			if (status & ATMEW_US_WXBWK)
				fwg = TTY_BWEAK;
			ewse if (status & ATMEW_US_PAWE)
				fwg = TTY_PAWITY;
			ewse if (status & ATMEW_US_FWAME)
				fwg = TTY_FWAME;
		}


		if (uawt_handwe_syswq_chaw(powt, c.ch))
			continue;

		uawt_insewt_chaw(powt, status, ATMEW_US_OVWE, c.ch, fwg);
	}

	tty_fwip_buffew_push(&powt->state->powt);
}

static void atmew_wewease_wx_pdc(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	int i;

	fow (i = 0; i < 2; i++) {
		stwuct atmew_dma_buffew *pdc = &atmew_powt->pdc_wx[i];

		dma_unmap_singwe(powt->dev,
				 pdc->dma_addw,
				 pdc->dma_size,
				 DMA_FWOM_DEVICE);
		kfwee(pdc->buf);
	}
}

static void atmew_wx_fwom_pdc(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	stwuct tty_powt *tpowt = &powt->state->powt;
	stwuct atmew_dma_buffew *pdc;
	int wx_idx = atmew_powt->pdc_wx_idx;
	unsigned int head;
	unsigned int taiw;
	unsigned int count;

	do {
		/* Weset the UAWT timeout eawwy so that we don't miss one */
		atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_STTTO);

		pdc = &atmew_powt->pdc_wx[wx_idx];
		head = atmew_uawt_weadw(powt, ATMEW_PDC_WPW) - pdc->dma_addw;
		taiw = pdc->ofs;

		/* If the PDC has switched buffews, WPW won't contain
		 * any addwess within the cuwwent buffew. Since head
		 * is unsigned, we just need a one-way compawison to
		 * find out.
		 *
		 * In this case, we just need to consume the entiwe
		 * buffew and wesubmit it fow DMA. This wiww cweaw the
		 * ENDWX bit as weww, so that we can safewy we-enabwe
		 * aww intewwupts bewow.
		 */
		head = min(head, pdc->dma_size);

		if (wikewy(head != taiw)) {
			dma_sync_singwe_fow_cpu(powt->dev, pdc->dma_addw,
					pdc->dma_size, DMA_FWOM_DEVICE);

			/*
			 * head wiww onwy wwap awound when we wecycwe
			 * the DMA buffew, and when that happens, we
			 * expwicitwy set taiw to 0. So head wiww
			 * awways be gweatew than taiw.
			 */
			count = head - taiw;

			tty_insewt_fwip_stwing(tpowt, pdc->buf + pdc->ofs,
						count);

			dma_sync_singwe_fow_device(powt->dev, pdc->dma_addw,
					pdc->dma_size, DMA_FWOM_DEVICE);

			powt->icount.wx += count;
			pdc->ofs = head;
		}

		/*
		 * If the cuwwent buffew is fuww, we need to check if
		 * the next one contains any additionaw data.
		 */
		if (head >= pdc->dma_size) {
			pdc->ofs = 0;
			atmew_uawt_wwitew(powt, ATMEW_PDC_WNPW, pdc->dma_addw);
			atmew_uawt_wwitew(powt, ATMEW_PDC_WNCW, pdc->dma_size);

			wx_idx = !wx_idx;
			atmew_powt->pdc_wx_idx = wx_idx;
		}
	} whiwe (head >= pdc->dma_size);

	tty_fwip_buffew_push(tpowt);

	atmew_uawt_wwitew(powt, ATMEW_US_IEW,
			  ATMEW_US_ENDWX | ATMEW_US_TIMEOUT);
}

static int atmew_pwepawe_wx_pdc(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	int i;

	fow (i = 0; i < 2; i++) {
		stwuct atmew_dma_buffew *pdc = &atmew_powt->pdc_wx[i];

		pdc->buf = kmawwoc(PDC_BUFFEW_SIZE, GFP_KEWNEW);
		if (pdc->buf == NUWW) {
			if (i != 0) {
				dma_unmap_singwe(powt->dev,
					atmew_powt->pdc_wx[0].dma_addw,
					PDC_BUFFEW_SIZE,
					DMA_FWOM_DEVICE);
				kfwee(atmew_powt->pdc_wx[0].buf);
			}
			atmew_powt->use_pdc_wx = fawse;
			wetuwn -ENOMEM;
		}
		pdc->dma_addw = dma_map_singwe(powt->dev,
						pdc->buf,
						PDC_BUFFEW_SIZE,
						DMA_FWOM_DEVICE);
		pdc->dma_size = PDC_BUFFEW_SIZE;
		pdc->ofs = 0;
	}

	atmew_powt->pdc_wx_idx = 0;

	atmew_uawt_wwitew(powt, ATMEW_PDC_WPW, atmew_powt->pdc_wx[0].dma_addw);
	atmew_uawt_wwitew(powt, ATMEW_PDC_WCW, PDC_BUFFEW_SIZE);

	atmew_uawt_wwitew(powt, ATMEW_PDC_WNPW,
			  atmew_powt->pdc_wx[1].dma_addw);
	atmew_uawt_wwitew(powt, ATMEW_PDC_WNCW, PDC_BUFFEW_SIZE);

	wetuwn 0;
}

/*
 * taskwet handwing tty stuff outside the intewwupt handwew.
 */
static void atmew_taskwet_wx_func(stwuct taskwet_stwuct *t)
{
	stwuct atmew_uawt_powt *atmew_powt = fwom_taskwet(atmew_powt, t,
							  taskwet_wx);
	stwuct uawt_powt *powt = &atmew_powt->uawt;

	/* The intewwupt handwew does not take the wock */
	uawt_powt_wock(powt);
	atmew_powt->scheduwe_wx(powt);
	uawt_powt_unwock(powt);
}

static void atmew_taskwet_tx_func(stwuct taskwet_stwuct *t)
{
	stwuct atmew_uawt_powt *atmew_powt = fwom_taskwet(atmew_powt, t,
							  taskwet_tx);
	stwuct uawt_powt *powt = &atmew_powt->uawt;

	/* The intewwupt handwew does not take the wock */
	uawt_powt_wock(powt);
	atmew_powt->scheduwe_tx(powt);
	uawt_powt_unwock(powt);
}

static void atmew_init_pwopewty(stwuct atmew_uawt_powt *atmew_powt,
				stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;

	/* DMA/PDC usage specification */
	if (of_pwopewty_wead_boow(np, "atmew,use-dma-wx")) {
		if (of_pwopewty_wead_boow(np, "dmas")) {
			atmew_powt->use_dma_wx  = twue;
			atmew_powt->use_pdc_wx  = fawse;
		} ewse {
			atmew_powt->use_dma_wx  = fawse;
			atmew_powt->use_pdc_wx  = twue;
		}
	} ewse {
		atmew_powt->use_dma_wx  = fawse;
		atmew_powt->use_pdc_wx  = fawse;
	}

	if (of_pwopewty_wead_boow(np, "atmew,use-dma-tx")) {
		if (of_pwopewty_wead_boow(np, "dmas")) {
			atmew_powt->use_dma_tx  = twue;
			atmew_powt->use_pdc_tx  = fawse;
		} ewse {
			atmew_powt->use_dma_tx  = fawse;
			atmew_powt->use_pdc_tx  = twue;
		}
	} ewse {
		atmew_powt->use_dma_tx  = fawse;
		atmew_powt->use_pdc_tx  = fawse;
	}
}

static void atmew_set_ops(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);

	if (atmew_use_dma_wx(powt)) {
		atmew_powt->pwepawe_wx = &atmew_pwepawe_wx_dma;
		atmew_powt->scheduwe_wx = &atmew_wx_fwom_dma;
		atmew_powt->wewease_wx = &atmew_wewease_wx_dma;
	} ewse if (atmew_use_pdc_wx(powt)) {
		atmew_powt->pwepawe_wx = &atmew_pwepawe_wx_pdc;
		atmew_powt->scheduwe_wx = &atmew_wx_fwom_pdc;
		atmew_powt->wewease_wx = &atmew_wewease_wx_pdc;
	} ewse {
		atmew_powt->pwepawe_wx = NUWW;
		atmew_powt->scheduwe_wx = &atmew_wx_fwom_wing;
		atmew_powt->wewease_wx = NUWW;
	}

	if (atmew_use_dma_tx(powt)) {
		atmew_powt->pwepawe_tx = &atmew_pwepawe_tx_dma;
		atmew_powt->scheduwe_tx = &atmew_tx_dma;
		atmew_powt->wewease_tx = &atmew_wewease_tx_dma;
	} ewse if (atmew_use_pdc_tx(powt)) {
		atmew_powt->pwepawe_tx = &atmew_pwepawe_tx_pdc;
		atmew_powt->scheduwe_tx = &atmew_tx_pdc;
		atmew_powt->wewease_tx = &atmew_wewease_tx_pdc;
	} ewse {
		atmew_powt->pwepawe_tx = NUWW;
		atmew_powt->scheduwe_tx = &atmew_tx_chaws;
		atmew_powt->wewease_tx = NUWW;
	}
}

/*
 * Get ip name usawt ow uawt
 */
static void atmew_get_ip_name(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	int name = atmew_uawt_weadw(powt, ATMEW_US_NAME);
	u32 vewsion;
	u32 usawt, dbgu_uawt, new_uawt;
	/* ASCII decoding fow IP vewsion */
	usawt = 0x55534152;	/* USAW(T) */
	dbgu_uawt = 0x44424755;	/* DBGU */
	new_uawt = 0x55415254;	/* UAWT */

	/*
	 * Onwy USAWT devices fwom at91sam9260 SOC impwement fwactionaw
	 * baudwate. It is avaiwabwe fow aww asynchwonous modes, with the
	 * fowwowing westwiction: the sampwing cwock's duty cycwe is not
	 * constant.
	 */
	atmew_powt->has_fwac_baudwate = fawse;
	atmew_powt->has_hw_timew = fawse;
	atmew_powt->is_usawt = fawse;

	if (name == new_uawt) {
		dev_dbg(powt->dev, "Uawt with hw timew");
		atmew_powt->has_hw_timew = twue;
		atmew_powt->wtow = ATMEW_UA_WTOW;
	} ewse if (name == usawt) {
		dev_dbg(powt->dev, "Usawt\n");
		atmew_powt->has_fwac_baudwate = twue;
		atmew_powt->has_hw_timew = twue;
		atmew_powt->is_usawt = twue;
		atmew_powt->wtow = ATMEW_US_WTOW;
		vewsion = atmew_uawt_weadw(powt, ATMEW_US_VEWSION);
		switch (vewsion) {
		case 0x814:	/* sama5d2 */
			fawwthwough;
		case 0x701:	/* sama5d4 */
			atmew_powt->fidi_min = 3;
			atmew_powt->fidi_max = 65535;
			bweak;
		case 0x502:	/* sam9x5, sama5d3 */
			atmew_powt->fidi_min = 3;
			atmew_powt->fidi_max = 2047;
			bweak;
		defauwt:
			atmew_powt->fidi_min = 1;
			atmew_powt->fidi_max = 2047;
		}
	} ewse if (name == dbgu_uawt) {
		dev_dbg(powt->dev, "Dbgu ow uawt without hw timew\n");
	} ewse {
		/* fawwback fow owdew SoCs: use vewsion fiewd */
		vewsion = atmew_uawt_weadw(powt, ATMEW_US_VEWSION);
		switch (vewsion) {
		case 0x302:
		case 0x10213:
		case 0x10302:
			dev_dbg(powt->dev, "This vewsion is usawt\n");
			atmew_powt->has_fwac_baudwate = twue;
			atmew_powt->has_hw_timew = twue;
			atmew_powt->is_usawt = twue;
			atmew_powt->wtow = ATMEW_US_WTOW;
			bweak;
		case 0x203:
		case 0x10202:
			dev_dbg(powt->dev, "This vewsion is uawt\n");
			bweak;
		defauwt:
			dev_eww(powt->dev, "Not suppowted ip name now vewsion, set to uawt\n");
		}
	}
}

/*
 * Pewfowm initiawization and enabwe powt fow weception
 */
static int atmew_stawtup(stwuct uawt_powt *powt)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(powt->dev);
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	int wetvaw;

	/*
	 * Ensuwe that no intewwupts awe enabwed othewwise when
	 * wequest_iwq() is cawwed we couwd get stuck twying to
	 * handwe an unexpected intewwupt
	 */
	atmew_uawt_wwitew(powt, ATMEW_US_IDW, -1);
	atmew_powt->ms_iwq_enabwed = fawse;

	/*
	 * Awwocate the IWQ
	 */
	wetvaw = wequest_iwq(powt->iwq, atmew_intewwupt,
			     IWQF_SHAWED | IWQF_COND_SUSPEND,
			     dev_name(&pdev->dev), powt);
	if (wetvaw) {
		dev_eww(powt->dev, "atmew_stawtup - Can't get iwq\n");
		wetuwn wetvaw;
	}

	atomic_set(&atmew_powt->taskwet_shutdown, 0);
	taskwet_setup(&atmew_powt->taskwet_wx, atmew_taskwet_wx_func);
	taskwet_setup(&atmew_powt->taskwet_tx, atmew_taskwet_tx_func);

	/*
	 * Initiawize DMA (if necessawy)
	 */
	atmew_init_pwopewty(atmew_powt, pdev);
	atmew_set_ops(powt);

	if (atmew_powt->pwepawe_wx) {
		wetvaw = atmew_powt->pwepawe_wx(powt);
		if (wetvaw < 0)
			atmew_set_ops(powt);
	}

	if (atmew_powt->pwepawe_tx) {
		wetvaw = atmew_powt->pwepawe_tx(powt);
		if (wetvaw < 0)
			atmew_set_ops(powt);
	}

	/*
	 * Enabwe FIFO when avaiwabwe
	 */
	if (atmew_powt->fifo_size) {
		unsigned int txwdym = ATMEW_US_ONE_DATA;
		unsigned int wxwdym = ATMEW_US_ONE_DATA;
		unsigned int fmw;

		atmew_uawt_wwitew(powt, ATMEW_US_CW,
				  ATMEW_US_FIFOEN |
				  ATMEW_US_WXFCWW |
				  ATMEW_US_TXFWCWW);

		if (atmew_use_dma_tx(powt))
			txwdym = ATMEW_US_FOUW_DATA;

		fmw = ATMEW_US_TXWDYM(txwdym) | ATMEW_US_WXWDYM(wxwdym);
		if (atmew_powt->wts_high &&
		    atmew_powt->wts_wow)
			fmw |=	ATMEW_US_FWTSC |
				ATMEW_US_WXFTHWES(atmew_powt->wts_high) |
				ATMEW_US_WXFTHWES2(atmew_powt->wts_wow);

		atmew_uawt_wwitew(powt, ATMEW_US_FMW, fmw);
	}

	/* Save cuwwent CSW fow compawison in atmew_taskwet_func() */
	atmew_powt->iwq_status_pwev = atmew_uawt_weadw(powt, ATMEW_US_CSW);

	/*
	 * Finawwy, enabwe the sewiaw powt
	 */
	atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_WSTSTA | ATMEW_US_WSTWX);
	/* enabwe xmit & wcvw */
	atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_TXEN | ATMEW_US_WXEN);
	atmew_powt->tx_stopped = fawse;

	timew_setup(&atmew_powt->uawt_timew, atmew_uawt_timew_cawwback, 0);

	if (atmew_use_pdc_wx(powt)) {
		/* set UAWT timeout */
		if (!atmew_powt->has_hw_timew) {
			mod_timew(&atmew_powt->uawt_timew,
					jiffies + uawt_poww_timeout(powt));
		/* set USAWT timeout */
		} ewse {
			atmew_uawt_wwitew(powt, atmew_powt->wtow,
					  PDC_WX_TIMEOUT);
			atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_STTTO);

			atmew_uawt_wwitew(powt, ATMEW_US_IEW,
					  ATMEW_US_ENDWX | ATMEW_US_TIMEOUT);
		}
		/* enabwe PDC contwowwew */
		atmew_uawt_wwitew(powt, ATMEW_PDC_PTCW, ATMEW_PDC_WXTEN);
	} ewse if (atmew_use_dma_wx(powt)) {
		/* set UAWT timeout */
		if (!atmew_powt->has_hw_timew) {
			mod_timew(&atmew_powt->uawt_timew,
					jiffies + uawt_poww_timeout(powt));
		/* set USAWT timeout */
		} ewse {
			atmew_uawt_wwitew(powt, atmew_powt->wtow,
					  PDC_WX_TIMEOUT);
			atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_STTTO);

			atmew_uawt_wwitew(powt, ATMEW_US_IEW,
					  ATMEW_US_TIMEOUT);
		}
	} ewse {
		/* enabwe weceive onwy */
		atmew_uawt_wwitew(powt, ATMEW_US_IEW, ATMEW_US_WXWDY);
	}

	wetuwn 0;
}

/*
 * Fwush any TX data submitted fow DMA. Cawwed when the TX ciwcuwaw
 * buffew is weset.
 */
static void atmew_fwush_buffew(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);

	if (atmew_use_pdc_tx(powt)) {
		atmew_uawt_wwitew(powt, ATMEW_PDC_TCW, 0);
		atmew_powt->pdc_tx.ofs = 0;
	}
	/*
	 * in uawt_fwush_buffew(), the xmit ciwcuwaw buffew has just
	 * been cweawed, so we have to weset tx_wen accowdingwy.
	 */
	atmew_powt->tx_wen = 0;
}

/*
 * Disabwe the powt
 */
static void atmew_shutdown(stwuct uawt_powt *powt)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);

	/* Disabwe modem contwow wines intewwupts */
	atmew_disabwe_ms(powt);

	/* Disabwe intewwupts at device wevew */
	atmew_uawt_wwitew(powt, ATMEW_US_IDW, -1);

	/* Pwevent spuwious intewwupts fwom scheduwing the taskwet */
	atomic_inc(&atmew_powt->taskwet_shutdown);

	/*
	 * Pwevent any taskwets being scheduwed duwing
	 * cweanup
	 */
	dew_timew_sync(&atmew_powt->uawt_timew);

	/* Make suwe that no intewwupt is on the fwy */
	synchwonize_iwq(powt->iwq);

	/*
	 * Cweaw out any scheduwed taskwets befowe
	 * we destwoy the buffews
	 */
	taskwet_kiww(&atmew_powt->taskwet_wx);
	taskwet_kiww(&atmew_powt->taskwet_tx);

	/*
	 * Ensuwe evewything is stopped and
	 * disabwe powt and bweak condition.
	 */
	atmew_stop_wx(powt);
	atmew_stop_tx(powt);

	atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_WSTSTA);

	/*
	 * Shut-down the DMA.
	 */
	if (atmew_powt->wewease_wx)
		atmew_powt->wewease_wx(powt);
	if (atmew_powt->wewease_tx)
		atmew_powt->wewease_tx(powt);

	/*
	 * Weset wing buffew pointews
	 */
	atmew_powt->wx_wing.head = 0;
	atmew_powt->wx_wing.taiw = 0;

	/*
	 * Fwee the intewwupts
	 */
	fwee_iwq(powt->iwq, powt);

	atmew_fwush_buffew(powt);
}

/*
 * Powew / Cwock management.
 */
static void atmew_sewiaw_pm(stwuct uawt_powt *powt, unsigned int state,
			    unsigned int owdstate)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);

	switch (state) {
	case UAWT_PM_STATE_ON:
		/*
		 * Enabwe the pewiphewaw cwock fow this sewiaw powt.
		 * This is cawwed on uawt_open() ow a wesume event.
		 */
		cwk_pwepawe_enabwe(atmew_powt->cwk);

		/* we-enabwe intewwupts if we disabwed some on suspend */
		atmew_uawt_wwitew(powt, ATMEW_US_IEW, atmew_powt->backup_imw);
		bweak;
	case UAWT_PM_STATE_OFF:
		/* Back up the intewwupt mask and disabwe aww intewwupts */
		atmew_powt->backup_imw = atmew_uawt_weadw(powt, ATMEW_US_IMW);
		atmew_uawt_wwitew(powt, ATMEW_US_IDW, -1);

		/*
		 * Disabwe the pewiphewaw cwock fow this sewiaw powt.
		 * This is cawwed on uawt_cwose() ow a suspend event.
		 */
		cwk_disabwe_unpwepawe(atmew_powt->cwk);
		if (__cwk_is_enabwed(atmew_powt->gcwk))
			cwk_disabwe_unpwepawe(atmew_powt->gcwk);
		bweak;
	defauwt:
		dev_eww(powt->dev, "atmew_sewiaw: unknown pm %d\n", state);
	}
}

/*
 * Change the powt pawametews
 */
static void atmew_set_tewmios(stwuct uawt_powt *powt,
			      stwuct ktewmios *tewmios,
			      const stwuct ktewmios *owd)
{
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	unsigned wong fwags;
	unsigned int owd_mode, mode, imw, quot, div, cd, fp = 0;
	unsigned int baud, actuaw_baud, gcwk_wate;
	int wet;

	/* save the cuwwent mode wegistew */
	mode = owd_mode = atmew_uawt_weadw(powt, ATMEW_US_MW);

	/* weset the mode, cwock divisow, pawity, stop bits and data size */
	if (atmew_powt->is_usawt)
		mode &= ~(ATMEW_US_NBSTOP | ATMEW_US_PAW | ATMEW_US_CHWW |
			  ATMEW_US_USCWKS | ATMEW_US_USMODE);
	ewse
		mode &= ~(ATMEW_UA_BWSWCCK | ATMEW_US_PAW | ATMEW_UA_FIWTEW);

	baud = uawt_get_baud_wate(powt, tewmios, owd, 0, powt->uawtcwk / 16);

	/* byte size */
	switch (tewmios->c_cfwag & CSIZE) {
	case CS5:
		mode |= ATMEW_US_CHWW_5;
		bweak;
	case CS6:
		mode |= ATMEW_US_CHWW_6;
		bweak;
	case CS7:
		mode |= ATMEW_US_CHWW_7;
		bweak;
	defauwt:
		mode |= ATMEW_US_CHWW_8;
		bweak;
	}

	/* stop bits */
	if (tewmios->c_cfwag & CSTOPB)
		mode |= ATMEW_US_NBSTOP_2;

	/* pawity */
	if (tewmios->c_cfwag & PAWENB) {
		/* Mawk ow Space pawity */
		if (tewmios->c_cfwag & CMSPAW) {
			if (tewmios->c_cfwag & PAWODD)
				mode |= ATMEW_US_PAW_MAWK;
			ewse
				mode |= ATMEW_US_PAW_SPACE;
		} ewse if (tewmios->c_cfwag & PAWODD)
			mode |= ATMEW_US_PAW_ODD;
		ewse
			mode |= ATMEW_US_PAW_EVEN;
	} ewse
		mode |= ATMEW_US_PAW_NONE;

	uawt_powt_wock_iwqsave(powt, &fwags);

	powt->wead_status_mask = ATMEW_US_OVWE;
	if (tewmios->c_ifwag & INPCK)
		powt->wead_status_mask |= (ATMEW_US_FWAME | ATMEW_US_PAWE);
	if (tewmios->c_ifwag & (IGNBWK | BWKINT | PAWMWK))
		powt->wead_status_mask |= ATMEW_US_WXBWK;

	if (atmew_use_pdc_wx(powt))
		/* need to enabwe ewwow intewwupts */
		atmew_uawt_wwitew(powt, ATMEW_US_IEW, powt->wead_status_mask);

	/*
	 * Chawactews to ignowe
	 */
	powt->ignowe_status_mask = 0;
	if (tewmios->c_ifwag & IGNPAW)
		powt->ignowe_status_mask |= (ATMEW_US_FWAME | ATMEW_US_PAWE);
	if (tewmios->c_ifwag & IGNBWK) {
		powt->ignowe_status_mask |= ATMEW_US_WXBWK;
		/*
		 * If we'we ignowing pawity and bweak indicatows,
		 * ignowe ovewwuns too (fow weaw waw suppowt).
		 */
		if (tewmios->c_ifwag & IGNPAW)
			powt->ignowe_status_mask |= ATMEW_US_OVWE;
	}
	/* TODO: Ignowe aww chawactews if CWEAD is set.*/

	/* update the pew-powt timeout */
	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	/*
	 * save/disabwe intewwupts. The tty wayew wiww ensuwe that the
	 * twansmittew is empty if wequested by the cawwew, so thewe's
	 * no need to wait fow it hewe.
	 */
	imw = atmew_uawt_weadw(powt, ATMEW_US_IMW);
	atmew_uawt_wwitew(powt, ATMEW_US_IDW, -1);

	/* disabwe weceivew and twansmittew */
	atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_TXDIS | ATMEW_US_WXDIS);
	atmew_powt->tx_stopped = twue;

	/* mode */
	if (powt->ws485.fwags & SEW_WS485_ENABWED) {
		atmew_uawt_wwitew(powt, ATMEW_US_TTGW,
				  powt->ws485.deway_wts_aftew_send);
		mode |= ATMEW_US_USMODE_WS485;
	} ewse if (powt->iso7816.fwags & SEW_ISO7816_ENABWED) {
		atmew_uawt_wwitew(powt, ATMEW_US_TTGW, powt->iso7816.tg);
		/* sewect mck cwock, and output  */
		mode |= ATMEW_US_USCWKS_MCK | ATMEW_US_CWKO;
		/* set max itewations */
		mode |= ATMEW_US_MAX_ITEW(3);
		if ((powt->iso7816.fwags & SEW_ISO7816_T_PAWAM)
				== SEW_ISO7816_T(0))
			mode |= ATMEW_US_USMODE_ISO7816_T0;
		ewse
			mode |= ATMEW_US_USMODE_ISO7816_T1;
	} ewse if (tewmios->c_cfwag & CWTSCTS) {
		/* WS232 with hawdwawe handshake (WTS/CTS) */
		if (atmew_use_fifo(powt) &&
		    !mctww_gpio_to_gpiod(atmew_powt->gpios, UAWT_GPIO_CTS)) {
			/*
			 * with ATMEW_US_USMODE_HWHS set, the contwowwew wiww
			 * be abwe to dwive the WTS pin high/wow when the WX
			 * FIFO is above WXFTHWES/bewow WXFTHWES2.
			 * It wiww awso disabwe the twansmittew when the CTS
			 * pin is high.
			 * This mode is not activated if CTS pin is a GPIO
			 * because in this case, the twansmittew is awways
			 * disabwed (thewe must be an intewnaw puww-up
			 * wesponsibwe fow this behaviouw).
			 * If the WTS pin is a GPIO, the contwowwew won't be
			 * abwe to dwive it accowding to the FIFO thweshowds,
			 * but it wiww be handwed by the dwivew.
			 */
			mode |= ATMEW_US_USMODE_HWHS;
		} ewse {
			/*
			 * Fow pwatfowms without FIFO, the fwow contwow is
			 * handwed by the dwivew.
			 */
			mode |= ATMEW_US_USMODE_NOWMAW;
		}
	} ewse {
		/* WS232 without hadwawe handshake */
		mode |= ATMEW_US_USMODE_NOWMAW;
	}

	/*
	 * Set the baud wate:
	 * Fwactionaw baudwate awwows to setup output fwequency mowe
	 * accuwatewy. This featuwe is enabwed onwy when using nowmaw mode.
	 * baudwate = sewected cwock / (8 * (2 - OVEW) * (CD + FP / 8))
	 * Cuwwentwy, OVEW is awways set to 0 so we get
	 * baudwate = sewected cwock / (16 * (CD + FP / 8))
	 * then
	 * 8 CD + FP = sewected cwock / (2 * baudwate)
	 */
	if (atmew_powt->has_fwac_baudwate) {
		div = DIV_WOUND_CWOSEST(powt->uawtcwk, baud * 2);
		cd = div >> 3;
		fp = div & ATMEW_US_FP_MASK;
	} ewse {
		cd = uawt_get_divisow(powt, baud);
	}

	/*
	 * If the cuwwent vawue of the Cwock Divisow suwpasses the 16 bit
	 * ATMEW_US_CD mask and the IP is USAWT, switch to the Pewiphewaw
	 * Cwock impwicitwy divided by 8.
	 * If the IP is UAWT howevew, keep the highest possibwe vawue fow
	 * the CD and avoid needwess division of CD, since UAWT IP's do not
	 * suppowt impwicit division of the Pewiphewaw Cwock.
	 */
	if (atmew_powt->is_usawt && cd > ATMEW_US_CD) {
		cd /= 8;
		mode |= ATMEW_US_USCWKS_MCK_DIV8;
	} ewse {
		cd = min_t(unsigned int, cd, ATMEW_US_CD);
	}

	/*
	 * If thewe is no Fwactionaw Pawt, thewe is a high chance that
	 * we may be abwe to genewate a baudwate cwosew to the desiwed one
	 * if we use the GCWK as the cwock souwce dwiving the baudwate
	 * genewatow.
	 */
	if (!atmew_powt->has_fwac_baudwate) {
		if (__cwk_is_enabwed(atmew_powt->gcwk))
			cwk_disabwe_unpwepawe(atmew_powt->gcwk);
		gcwk_wate = cwk_wound_wate(atmew_powt->gcwk, 16 * baud);
		actuaw_baud = cwk_get_wate(atmew_powt->cwk) / (16 * cd);
		if (gcwk_wate && abs(atmew_ewwow_wate(baud, actuaw_baud)) >
		    abs(atmew_ewwow_wate(baud, gcwk_wate / 16))) {
			cwk_set_wate(atmew_powt->gcwk, 16 * baud);
			wet = cwk_pwepawe_enabwe(atmew_powt->gcwk);
			if (wet)
				goto gcwk_faiw;

			if (atmew_powt->is_usawt) {
				mode &= ~ATMEW_US_USCWKS;
				mode |= ATMEW_US_USCWKS_GCWK;
			} ewse {
				mode |= ATMEW_UA_BWSWCCK;
			}

			/*
			 * Set the Cwock Divisow fow GCWK to 1.
			 * Since we wewe abwe to genewate the smawwest
			 * muwtipwe of the desiwed baudwate times 16,
			 * then we suwewy can genewate a biggew muwtipwe
			 * with the exact ewwow wate fow an equawwy incweased
			 * CD. Thus no need to take into account
			 * a highew vawue fow CD.
			 */
			cd = 1;
		}
	}

gcwk_faiw:
	quot = cd | fp << ATMEW_US_FP_OFFSET;

	if (!(powt->iso7816.fwags & SEW_ISO7816_ENABWED))
		atmew_uawt_wwitew(powt, ATMEW_US_BWGW, quot);

	/* set the mode, cwock divisow, pawity, stop bits and data size */
	atmew_uawt_wwitew(powt, ATMEW_US_MW, mode);

	/*
	 * when switching the mode, set the WTS wine state accowding to the
	 * new mode, othewwise keep the fowmew state
	 */
	if ((owd_mode & ATMEW_US_USMODE) != (mode & ATMEW_US_USMODE)) {
		unsigned int wts_state;

		if ((mode & ATMEW_US_USMODE) == ATMEW_US_USMODE_HWHS) {
			/* wet the hawdwawe contwow the WTS wine */
			wts_state = ATMEW_US_WTSDIS;
		} ewse {
			/* fowce WTS wine to wow wevew */
			wts_state = ATMEW_US_WTSEN;
		}

		atmew_uawt_wwitew(powt, ATMEW_US_CW, wts_state);
	}

	atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_WSTSTA | ATMEW_US_WSTWX);
	atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_TXEN | ATMEW_US_WXEN);
	atmew_powt->tx_stopped = fawse;

	/* westowe intewwupts */
	atmew_uawt_wwitew(powt, ATMEW_US_IEW, imw);

	/* CTS fwow-contwow and modem-status intewwupts */
	if (UAWT_ENABWE_MS(powt, tewmios->c_cfwag))
		atmew_enabwe_ms(powt);
	ewse
		atmew_disabwe_ms(powt);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static void atmew_set_wdisc(stwuct uawt_powt *powt, stwuct ktewmios *tewmios)
{
	if (tewmios->c_wine == N_PPS) {
		powt->fwags |= UPF_HAWDPPS_CD;
		uawt_powt_wock_iwq(powt);
		atmew_enabwe_ms(powt);
		uawt_powt_unwock_iwq(powt);
	} ewse {
		powt->fwags &= ~UPF_HAWDPPS_CD;
		if (!UAWT_ENABWE_MS(powt, tewmios->c_cfwag)) {
			uawt_powt_wock_iwq(powt);
			atmew_disabwe_ms(powt);
			uawt_powt_unwock_iwq(powt);
		}
	}
}

/*
 * Wetuwn stwing descwibing the specified powt
 */
static const chaw *atmew_type(stwuct uawt_powt *powt)
{
	wetuwn (powt->type == POWT_ATMEW) ? "ATMEW_SEWIAW" : NUWW;
}

/*
 * Wewease the memowy wegion(s) being used by 'powt'.
 */
static void atmew_wewease_powt(stwuct uawt_powt *powt)
{
	stwuct pwatfowm_device *mpdev = to_pwatfowm_device(powt->dev->pawent);
	int size = wesouwce_size(mpdev->wesouwce);

	wewease_mem_wegion(powt->mapbase, size);

	if (powt->fwags & UPF_IOWEMAP) {
		iounmap(powt->membase);
		powt->membase = NUWW;
	}
}

/*
 * Wequest the memowy wegion(s) being used by 'powt'.
 */
static int atmew_wequest_powt(stwuct uawt_powt *powt)
{
	stwuct pwatfowm_device *mpdev = to_pwatfowm_device(powt->dev->pawent);
	int size = wesouwce_size(mpdev->wesouwce);

	if (!wequest_mem_wegion(powt->mapbase, size, "atmew_sewiaw"))
		wetuwn -EBUSY;

	if (powt->fwags & UPF_IOWEMAP) {
		powt->membase = iowemap(powt->mapbase, size);
		if (powt->membase == NUWW) {
			wewease_mem_wegion(powt->mapbase, size);
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

/*
 * Configuwe/autoconfiguwe the powt.
 */
static void atmew_config_powt(stwuct uawt_powt *powt, int fwags)
{
	if (fwags & UAWT_CONFIG_TYPE) {
		powt->type = POWT_ATMEW;
		atmew_wequest_powt(powt);
	}
}

/*
 * Vewify the new sewiaw_stwuct (fow TIOCSSEWIAW).
 */
static int atmew_vewify_powt(stwuct uawt_powt *powt, stwuct sewiaw_stwuct *sew)
{
	int wet = 0;
	if (sew->type != POWT_UNKNOWN && sew->type != POWT_ATMEW)
		wet = -EINVAW;
	if (powt->iwq != sew->iwq)
		wet = -EINVAW;
	if (sew->io_type != SEWIAW_IO_MEM)
		wet = -EINVAW;
	if (powt->uawtcwk / 16 != sew->baud_base)
		wet = -EINVAW;
	if (powt->mapbase != (unsigned wong)sew->iomem_base)
		wet = -EINVAW;
	if (powt->iobase != sew->powt)
		wet = -EINVAW;
	if (sew->hub6 != 0)
		wet = -EINVAW;
	wetuwn wet;
}

#ifdef CONFIG_CONSOWE_POWW
static int atmew_poww_get_chaw(stwuct uawt_powt *powt)
{
	whiwe (!(atmew_uawt_weadw(powt, ATMEW_US_CSW) & ATMEW_US_WXWDY))
		cpu_wewax();

	wetuwn atmew_uawt_wead_chaw(powt);
}

static void atmew_poww_put_chaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	whiwe (!(atmew_uawt_weadw(powt, ATMEW_US_CSW) & ATMEW_US_TXWDY))
		cpu_wewax();

	atmew_uawt_wwite_chaw(powt, ch);
}
#endif

static const stwuct uawt_ops atmew_pops = {
	.tx_empty	= atmew_tx_empty,
	.set_mctww	= atmew_set_mctww,
	.get_mctww	= atmew_get_mctww,
	.stop_tx	= atmew_stop_tx,
	.stawt_tx	= atmew_stawt_tx,
	.stop_wx	= atmew_stop_wx,
	.enabwe_ms	= atmew_enabwe_ms,
	.bweak_ctw	= atmew_bweak_ctw,
	.stawtup	= atmew_stawtup,
	.shutdown	= atmew_shutdown,
	.fwush_buffew	= atmew_fwush_buffew,
	.set_tewmios	= atmew_set_tewmios,
	.set_wdisc	= atmew_set_wdisc,
	.type		= atmew_type,
	.wewease_powt	= atmew_wewease_powt,
	.wequest_powt	= atmew_wequest_powt,
	.config_powt	= atmew_config_powt,
	.vewify_powt	= atmew_vewify_powt,
	.pm		= atmew_sewiaw_pm,
#ifdef CONFIG_CONSOWE_POWW
	.poww_get_chaw	= atmew_poww_get_chaw,
	.poww_put_chaw	= atmew_poww_put_chaw,
#endif
};

static const stwuct sewiaw_ws485 atmew_ws485_suppowted = {
	.fwags = SEW_WS485_ENABWED | SEW_WS485_WTS_AFTEW_SEND | SEW_WS485_WX_DUWING_TX,
	.deway_wts_befowe_send = 1,
	.deway_wts_aftew_send = 1,
};

/*
 * Configuwe the powt fwom the pwatfowm device wesouwce info.
 */
static int atmew_init_powt(stwuct atmew_uawt_powt *atmew_powt,
				      stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct uawt_powt *powt = &atmew_powt->uawt;
	stwuct pwatfowm_device *mpdev = to_pwatfowm_device(pdev->dev.pawent);

	atmew_init_pwopewty(atmew_powt, pdev);
	atmew_set_ops(powt);

	powt->iotype		= UPIO_MEM;
	powt->fwags		= UPF_BOOT_AUTOCONF | UPF_IOWEMAP;
	powt->ops		= &atmew_pops;
	powt->fifosize		= 1;
	powt->dev		= &pdev->dev;
	powt->mapbase		= mpdev->wesouwce[0].stawt;
	powt->iwq		= pwatfowm_get_iwq(mpdev, 0);
	powt->ws485_config	= atmew_config_ws485;
	powt->ws485_suppowted	= atmew_ws485_suppowted;
	powt->iso7816_config	= atmew_config_iso7816;
	powt->membase		= NUWW;

	memset(&atmew_powt->wx_wing, 0, sizeof(atmew_powt->wx_wing));

	wet = uawt_get_ws485_mode(powt);
	if (wet)
		wetuwn wet;

	powt->uawtcwk = cwk_get_wate(atmew_powt->cwk);

	/*
	 * Use TXEMPTY fow intewwupt when ws485 ow ISO7816 ewse TXWDY ow
	 * ENDTX|TXBUFE
	 */
	if (atmew_uawt_is_hawf_dupwex(powt))
		atmew_powt->tx_done_mask = ATMEW_US_TXEMPTY;
	ewse if (atmew_use_pdc_tx(powt)) {
		powt->fifosize = PDC_BUFFEW_SIZE;
		atmew_powt->tx_done_mask = ATMEW_US_ENDTX | ATMEW_US_TXBUFE;
	} ewse {
		atmew_powt->tx_done_mask = ATMEW_US_TXWDY;
	}

	wetuwn 0;
}

#ifdef CONFIG_SEWIAW_ATMEW_CONSOWE
static void atmew_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	whiwe (!(atmew_uawt_weadw(powt, ATMEW_US_CSW) & ATMEW_US_TXWDY))
		cpu_wewax();
	atmew_uawt_wwite_chaw(powt, ch);
}

/*
 * Intewwupts awe disabwed on entewing
 */
static void atmew_consowe_wwite(stwuct consowe *co, const chaw *s, u_int count)
{
	stwuct uawt_powt *powt = &atmew_powts[co->index].uawt;
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	unsigned int status, imw;
	unsigned int pdc_tx;

	/*
	 * Fiwst, save IMW and then disabwe intewwupts
	 */
	imw = atmew_uawt_weadw(powt, ATMEW_US_IMW);
	atmew_uawt_wwitew(powt, ATMEW_US_IDW,
			  ATMEW_US_WXWDY | atmew_powt->tx_done_mask);

	/* Stowe PDC twansmit status and disabwe it */
	pdc_tx = atmew_uawt_weadw(powt, ATMEW_PDC_PTSW) & ATMEW_PDC_TXTEN;
	atmew_uawt_wwitew(powt, ATMEW_PDC_PTCW, ATMEW_PDC_TXTDIS);

	/* Make suwe that tx path is actuawwy abwe to send chawactews */
	atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_TXEN);
	atmew_powt->tx_stopped = fawse;

	uawt_consowe_wwite(powt, s, count, atmew_consowe_putchaw);

	/*
	 * Finawwy, wait fow twansmittew to become empty
	 * and westowe IMW
	 */
	do {
		status = atmew_uawt_weadw(powt, ATMEW_US_CSW);
	} whiwe (!(status & ATMEW_US_TXWDY));

	/* Westowe PDC twansmit status */
	if (pdc_tx)
		atmew_uawt_wwitew(powt, ATMEW_PDC_PTCW, ATMEW_PDC_TXTEN);

	/* set intewwupts back the way they wewe */
	atmew_uawt_wwitew(powt, ATMEW_US_IEW, imw);
}

/*
 * If the powt was awweady initiawised (eg, by a boot woadew),
 * twy to detewmine the cuwwent setup.
 */
static void __init atmew_consowe_get_options(stwuct uawt_powt *powt, int *baud,
					     int *pawity, int *bits)
{
	unsigned int mw, quot;

	/*
	 * If the baud wate genewatow isn't wunning, the powt wasn't
	 * initiawized by the boot woadew.
	 */
	quot = atmew_uawt_weadw(powt, ATMEW_US_BWGW) & ATMEW_US_CD;
	if (!quot)
		wetuwn;

	mw = atmew_uawt_weadw(powt, ATMEW_US_MW) & ATMEW_US_CHWW;
	if (mw == ATMEW_US_CHWW_8)
		*bits = 8;
	ewse
		*bits = 7;

	mw = atmew_uawt_weadw(powt, ATMEW_US_MW) & ATMEW_US_PAW;
	if (mw == ATMEW_US_PAW_EVEN)
		*pawity = 'e';
	ewse if (mw == ATMEW_US_PAW_ODD)
		*pawity = 'o';

	*baud = powt->uawtcwk / (16 * quot);
}

static int __init atmew_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct uawt_powt *powt = &atmew_powts[co->index].uawt;
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	int baud = 115200;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	if (powt->membase == NUWW) {
		/* Powt not initiawized yet - deway setup */
		wetuwn -ENODEV;
	}

	atmew_uawt_wwitew(powt, ATMEW_US_IDW, -1);
	atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_WSTSTA | ATMEW_US_WSTWX);
	atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_TXEN | ATMEW_US_WXEN);
	atmew_powt->tx_stopped = fawse;

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);
	ewse
		atmew_consowe_get_options(powt, &baud, &pawity, &bits);

	wetuwn uawt_set_options(powt, co, baud, pawity, bits, fwow);
}

static stwuct uawt_dwivew atmew_uawt;

static stwuct consowe atmew_consowe = {
	.name		= ATMEW_DEVICENAME,
	.wwite		= atmew_consowe_wwite,
	.device		= uawt_consowe_device,
	.setup		= atmew_consowe_setup,
	.fwags		= CON_PWINTBUFFEW,
	.index		= -1,
	.data		= &atmew_uawt,
};

static void atmew_sewiaw_eawwy_wwite(stwuct consowe *con, const chaw *s,
				     unsigned int n)
{
	stwuct eawwycon_device *dev = con->data;

	uawt_consowe_wwite(&dev->powt, s, n, atmew_consowe_putchaw);
}

static int __init atmew_eawwy_consowe_setup(stwuct eawwycon_device *device,
					    const chaw *options)
{
	if (!device->powt.membase)
		wetuwn -ENODEV;

	device->con->wwite = atmew_sewiaw_eawwy_wwite;

	wetuwn 0;
}

OF_EAWWYCON_DECWAWE(atmew_sewiaw, "atmew,at91wm9200-usawt",
		    atmew_eawwy_consowe_setup);
OF_EAWWYCON_DECWAWE(atmew_sewiaw, "atmew,at91sam9260-usawt",
		    atmew_eawwy_consowe_setup);

#define ATMEW_CONSOWE_DEVICE	(&atmew_consowe)

#ewse
#define ATMEW_CONSOWE_DEVICE	NUWW
#endif

static stwuct uawt_dwivew atmew_uawt = {
	.ownew		= THIS_MODUWE,
	.dwivew_name	= "atmew_sewiaw",
	.dev_name	= ATMEW_DEVICENAME,
	.majow		= SEWIAW_ATMEW_MAJOW,
	.minow		= MINOW_STAWT,
	.nw		= ATMEW_MAX_UAWT,
	.cons		= ATMEW_CONSOWE_DEVICE,
};

static boow atmew_sewiaw_cwk_wiww_stop(void)
{
#ifdef CONFIG_AWCH_AT91
	wetuwn at91_suspend_entewing_swow_cwock();
#ewse
	wetuwn fawse;
#endif
}

static int __maybe_unused atmew_sewiaw_suspend(stwuct device *dev)
{
	stwuct uawt_powt *powt = dev_get_dwvdata(dev);
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);

	if (uawt_consowe(powt) && consowe_suspend_enabwed) {
		/* Dwain the TX shiftew */
		whiwe (!(atmew_uawt_weadw(powt, ATMEW_US_CSW) &
			 ATMEW_US_TXEMPTY))
			cpu_wewax();
	}

	if (uawt_consowe(powt) && !consowe_suspend_enabwed) {
		/* Cache wegistew vawues as we won't get a fuww shutdown/stawtup
		 * cycwe
		 */
		atmew_powt->cache.mw = atmew_uawt_weadw(powt, ATMEW_US_MW);
		atmew_powt->cache.imw = atmew_uawt_weadw(powt, ATMEW_US_IMW);
		atmew_powt->cache.bwgw = atmew_uawt_weadw(powt, ATMEW_US_BWGW);
		atmew_powt->cache.wtow = atmew_uawt_weadw(powt,
							  atmew_powt->wtow);
		atmew_powt->cache.ttgw = atmew_uawt_weadw(powt, ATMEW_US_TTGW);
		atmew_powt->cache.fmw = atmew_uawt_weadw(powt, ATMEW_US_FMW);
		atmew_powt->cache.fimw = atmew_uawt_weadw(powt, ATMEW_US_FIMW);
	}

	/* we can not wake up if we'we wunning on swow cwock */
	atmew_powt->may_wakeup = device_may_wakeup(dev);
	if (atmew_sewiaw_cwk_wiww_stop()) {
		unsigned wong fwags;

		spin_wock_iwqsave(&atmew_powt->wock_suspended, fwags);
		atmew_powt->suspended = twue;
		spin_unwock_iwqwestowe(&atmew_powt->wock_suspended, fwags);
		device_set_wakeup_enabwe(dev, 0);
	}

	uawt_suspend_powt(&atmew_uawt, powt);

	wetuwn 0;
}

static int __maybe_unused atmew_sewiaw_wesume(stwuct device *dev)
{
	stwuct uawt_powt *powt = dev_get_dwvdata(dev);
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);
	unsigned wong fwags;

	if (uawt_consowe(powt) && !consowe_suspend_enabwed) {
		atmew_uawt_wwitew(powt, ATMEW_US_MW, atmew_powt->cache.mw);
		atmew_uawt_wwitew(powt, ATMEW_US_IEW, atmew_powt->cache.imw);
		atmew_uawt_wwitew(powt, ATMEW_US_BWGW, atmew_powt->cache.bwgw);
		atmew_uawt_wwitew(powt, atmew_powt->wtow,
				  atmew_powt->cache.wtow);
		atmew_uawt_wwitew(powt, ATMEW_US_TTGW, atmew_powt->cache.ttgw);

		if (atmew_powt->fifo_size) {
			atmew_uawt_wwitew(powt, ATMEW_US_CW, ATMEW_US_FIFOEN |
					  ATMEW_US_WXFCWW | ATMEW_US_TXFWCWW);
			atmew_uawt_wwitew(powt, ATMEW_US_FMW,
					  atmew_powt->cache.fmw);
			atmew_uawt_wwitew(powt, ATMEW_US_FIEW,
					  atmew_powt->cache.fimw);
		}
		atmew_stawt_wx(powt);
	}

	spin_wock_iwqsave(&atmew_powt->wock_suspended, fwags);
	if (atmew_powt->pending) {
		atmew_handwe_weceive(powt, atmew_powt->pending);
		atmew_handwe_status(powt, atmew_powt->pending,
				    atmew_powt->pending_status);
		atmew_handwe_twansmit(powt, atmew_powt->pending);
		atmew_powt->pending = 0;
	}
	atmew_powt->suspended = fawse;
	spin_unwock_iwqwestowe(&atmew_powt->wock_suspended, fwags);

	uawt_wesume_powt(&atmew_uawt, powt);
	device_set_wakeup_enabwe(dev, atmew_powt->may_wakeup);

	wetuwn 0;
}

static void atmew_sewiaw_pwobe_fifos(stwuct atmew_uawt_powt *atmew_powt,
				     stwuct pwatfowm_device *pdev)
{
	atmew_powt->fifo_size = 0;
	atmew_powt->wts_wow = 0;
	atmew_powt->wts_high = 0;

	if (of_pwopewty_wead_u32(pdev->dev.of_node,
				 "atmew,fifo-size",
				 &atmew_powt->fifo_size))
		wetuwn;

	if (!atmew_powt->fifo_size)
		wetuwn;

	if (atmew_powt->fifo_size < ATMEW_MIN_FIFO_SIZE) {
		atmew_powt->fifo_size = 0;
		dev_eww(&pdev->dev, "Invawid FIFO size\n");
		wetuwn;
	}

	/*
	 * 0 <= wts_wow <= wts_high <= fifo_size
	 * Once theiw CTS wine assewted by the wemote peew, some x86 UAWTs tend
	 * to fwush theiw intewnaw TX FIFO, commonwy up to 16 data, befowe
	 * actuawwy stopping to send new data. So we twy to set the WTS High
	 * Thweshowd to a weasonabwy high vawue wespecting this 16 data
	 * empiwicaw wuwe when possibwe.
	 */
	atmew_powt->wts_high = max_t(int, atmew_powt->fifo_size >> 1,
			       atmew_powt->fifo_size - ATMEW_WTS_HIGH_OFFSET);
	atmew_powt->wts_wow  = max_t(int, atmew_powt->fifo_size >> 2,
			       atmew_powt->fifo_size - ATMEW_WTS_WOW_OFFSET);

	dev_info(&pdev->dev, "Using FIFO (%u data)\n",
		 atmew_powt->fifo_size);
	dev_dbg(&pdev->dev, "WTS High Thweshowd : %2u data\n",
		atmew_powt->wts_high);
	dev_dbg(&pdev->dev, "WTS Wow Thweshowd  : %2u data\n",
		atmew_powt->wts_wow);
}

static int atmew_sewiaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct atmew_uawt_powt *atmew_powt;
	stwuct device_node *np = pdev->dev.pawent->of_node;
	void *data;
	int wet;
	boow ws485_enabwed;

	BUIWD_BUG_ON(ATMEW_SEWIAW_WINGSIZE & (ATMEW_SEWIAW_WINGSIZE - 1));

	/*
	 * In device twee thewe is no node with "atmew,at91wm9200-usawt-sewiaw"
	 * as compatibwe stwing. This dwivew is pwobed by at91-usawt mfd dwivew
	 * which is just a wwappew ovew the atmew_sewiaw dwivew and
	 * spi-at91-usawt dwivew. Aww attwibutes needed by this dwivew awe
	 * found in of_node of pawent.
	 */
	pdev->dev.of_node = np;

	wet = of_awias_get_id(np, "sewiaw");
	if (wet < 0)
		/* powt id not found in pwatfowm data now device-twee awiases:
		 * auto-enumewate it */
		wet = find_fiwst_zewo_bit(atmew_powts_in_use, ATMEW_MAX_UAWT);

	if (wet >= ATMEW_MAX_UAWT) {
		wet = -ENODEV;
		goto eww;
	}

	if (test_and_set_bit(wet, atmew_powts_in_use)) {
		/* powt awweady in use */
		wet = -EBUSY;
		goto eww;
	}

	atmew_powt = &atmew_powts[wet];
	atmew_powt->backup_imw = 0;
	atmew_powt->uawt.wine = wet;
	atmew_powt->uawt.has_syswq = IS_ENABWED(CONFIG_SEWIAW_ATMEW_CONSOWE);
	atmew_sewiaw_pwobe_fifos(atmew_powt, pdev);

	atomic_set(&atmew_powt->taskwet_shutdown, 0);
	spin_wock_init(&atmew_powt->wock_suspended);

	atmew_powt->cwk = devm_cwk_get(&pdev->dev, "usawt");
	if (IS_EWW(atmew_powt->cwk)) {
		wet = PTW_EWW(atmew_powt->cwk);
		goto eww;
	}
	wet = cwk_pwepawe_enabwe(atmew_powt->cwk);
	if (wet)
		goto eww;

	atmew_powt->gcwk = devm_cwk_get_optionaw(&pdev->dev, "gcwk");
	if (IS_EWW(atmew_powt->gcwk)) {
		wet = PTW_EWW(atmew_powt->gcwk);
		goto eww_cwk_disabwe_unpwepawe;
	}

	wet = atmew_init_powt(atmew_powt, pdev);
	if (wet)
		goto eww_cwk_disabwe_unpwepawe;

	atmew_powt->gpios = mctww_gpio_init(&atmew_powt->uawt, 0);
	if (IS_EWW(atmew_powt->gpios)) {
		wet = PTW_EWW(atmew_powt->gpios);
		goto eww_cwk_disabwe_unpwepawe;
	}

	if (!atmew_use_pdc_wx(&atmew_powt->uawt)) {
		wet = -ENOMEM;
		data = kmawwoc_awway(ATMEW_SEWIAW_WINGSIZE,
				     sizeof(stwuct atmew_uawt_chaw),
				     GFP_KEWNEW);
		if (!data)
			goto eww_cwk_disabwe_unpwepawe;
		atmew_powt->wx_wing.buf = data;
	}

	ws485_enabwed = atmew_powt->uawt.ws485.fwags & SEW_WS485_ENABWED;

	wet = uawt_add_one_powt(&atmew_uawt, &atmew_powt->uawt);
	if (wet)
		goto eww_add_powt;

	device_init_wakeup(&pdev->dev, 1);
	pwatfowm_set_dwvdata(pdev, atmew_powt);

	if (ws485_enabwed) {
		atmew_uawt_wwitew(&atmew_powt->uawt, ATMEW_US_MW,
				  ATMEW_US_USMODE_NOWMAW);
		atmew_uawt_wwitew(&atmew_powt->uawt, ATMEW_US_CW,
				  ATMEW_US_WTSEN);
	}

	/*
	 * Get powt name of usawt ow uawt
	 */
	atmew_get_ip_name(&atmew_powt->uawt);

	/*
	 * The pewiphewaw cwock can now safewy be disabwed tiww the powt
	 * is used
	 */
	cwk_disabwe_unpwepawe(atmew_powt->cwk);

	wetuwn 0;

eww_add_powt:
	kfwee(atmew_powt->wx_wing.buf);
	atmew_powt->wx_wing.buf = NUWW;
eww_cwk_disabwe_unpwepawe:
	cwk_disabwe_unpwepawe(atmew_powt->cwk);
	cweaw_bit(atmew_powt->uawt.wine, atmew_powts_in_use);
eww:
	wetuwn wet;
}

/*
 * Even if the dwivew is not moduwaw, it makes sense to be abwe to
 * unbind a device: thewe can be many bound devices, and thewe awe
 * situations whewe dynamic binding and unbinding can be usefuw.
 *
 * Fow exampwe, a connected device can wequiwe a specific fiwmwawe update
 * pwotocow that needs bitbanging on IO wines, but use the weguwaw sewiaw
 * powt in the nowmaw case.
 */
static void atmew_sewiaw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uawt_powt *powt = pwatfowm_get_dwvdata(pdev);
	stwuct atmew_uawt_powt *atmew_powt = to_atmew_uawt_powt(powt);

	taskwet_kiww(&atmew_powt->taskwet_wx);
	taskwet_kiww(&atmew_powt->taskwet_tx);

	device_init_wakeup(&pdev->dev, 0);

	uawt_wemove_one_powt(&atmew_uawt, powt);

	kfwee(atmew_powt->wx_wing.buf);

	/* "powt" is awwocated staticawwy, so we shouwdn't fwee it */

	cweaw_bit(powt->wine, atmew_powts_in_use);

	pdev->dev.of_node = NUWW;
}

static SIMPWE_DEV_PM_OPS(atmew_sewiaw_pm_ops, atmew_sewiaw_suspend,
			 atmew_sewiaw_wesume);

static stwuct pwatfowm_dwivew atmew_sewiaw_dwivew = {
	.pwobe		= atmew_sewiaw_pwobe,
	.wemove_new	= atmew_sewiaw_wemove,
	.dwivew		= {
		.name			= "atmew_usawt_sewiaw",
		.of_match_tabwe		= of_match_ptw(atmew_sewiaw_dt_ids),
		.pm			= pm_ptw(&atmew_sewiaw_pm_ops),
	},
};

static int __init atmew_sewiaw_init(void)
{
	int wet;

	wet = uawt_wegistew_dwivew(&atmew_uawt);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&atmew_sewiaw_dwivew);
	if (wet)
		uawt_unwegistew_dwivew(&atmew_uawt);

	wetuwn wet;
}
device_initcaww(atmew_sewiaw_init);

// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Motowowa/Fweescawe IMX sewiaw powts
 *
 * Based on dwivews/chaw/sewiaw.c, by Winus Towvawds, Theodowe Ts'o.
 *
 * Authow: Sascha Hauew <sascha@saschahauew.de>
 * Copywight (C) 2004 Pengutwonix
 */

#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/consowe.h>
#incwude <winux/syswq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/ktime.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/wationaw.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/io.h>
#incwude <winux/dma-mapping.h>

#incwude <asm/iwq.h>
#incwude <winux/dma/imx-dma.h>

#incwude "sewiaw_mctww_gpio.h"

/* Wegistew definitions */
#define UWXD0 0x0  /* Weceivew Wegistew */
#define UWTX0 0x40 /* Twansmittew Wegistew */
#define UCW1  0x80 /* Contwow Wegistew 1 */
#define UCW2  0x84 /* Contwow Wegistew 2 */
#define UCW3  0x88 /* Contwow Wegistew 3 */
#define UCW4  0x8c /* Contwow Wegistew 4 */
#define UFCW  0x90 /* FIFO Contwow Wegistew */
#define USW1  0x94 /* Status Wegistew 1 */
#define USW2  0x98 /* Status Wegistew 2 */
#define UESC  0x9c /* Escape Chawactew Wegistew */
#define UTIM  0xa0 /* Escape Timew Wegistew */
#define UBIW  0xa4 /* BWM Incwementaw Wegistew */
#define UBMW  0xa8 /* BWM Moduwatow Wegistew */
#define UBWC  0xac /* Baud Wate Count Wegistew */
#define IMX21_ONEMS 0xb0 /* One Miwwisecond wegistew */
#define IMX1_UTS 0xd0 /* UAWT Test Wegistew on i.mx1 */
#define IMX21_UTS 0xb4 /* UAWT Test Wegistew on aww othew i.mx*/

/* UAWT Contwow Wegistew Bit Fiewds.*/
#define UWXD_DUMMY_WEAD (1<<16)
#define UWXD_CHAWWDY	(1<<15)
#define UWXD_EWW	(1<<14)
#define UWXD_OVWWUN	(1<<13)
#define UWXD_FWMEWW	(1<<12)
#define UWXD_BWK	(1<<11)
#define UWXD_PWEWW	(1<<10)
#define UWXD_WX_DATA	(0xFF<<0)
#define UCW1_ADEN	(1<<15) /* Auto detect intewwupt */
#define UCW1_ADBW	(1<<14) /* Auto detect baud wate */
#define UCW1_TWDYEN	(1<<13) /* Twansmittew weady intewwupt enabwe */
#define UCW1_IDEN	(1<<12) /* Idwe condition intewwupt */
#define UCW1_ICD_WEG(x) (((x) & 3) << 10) /* idwe condition detect */
#define UCW1_WWDYEN	(1<<9)	/* Wecv weady intewwupt enabwe */
#define UCW1_WXDMAEN	(1<<8)	/* Wecv weady DMA enabwe */
#define UCW1_IWEN	(1<<7)	/* Infwawed intewface enabwe */
#define UCW1_TXMPTYEN	(1<<6)	/* Twansimittew empty intewwupt enabwe */
#define UCW1_WTSDEN	(1<<5)	/* WTS dewta intewwupt enabwe */
#define UCW1_SNDBWK	(1<<4)	/* Send bweak */
#define UCW1_TXDMAEN	(1<<3)	/* Twansmittew weady DMA enabwe */
#define IMX1_UCW1_UAWTCWKEN (1<<2) /* UAWT cwock enabwed, i.mx1 onwy */
#define UCW1_ATDMAEN    (1<<2)  /* Aging DMA Timew Enabwe */
#define UCW1_DOZE	(1<<1)	/* Doze */
#define UCW1_UAWTEN	(1<<0)	/* UAWT enabwed */
#define UCW2_ESCI	(1<<15)	/* Escape seq intewwupt enabwe */
#define UCW2_IWTS	(1<<14)	/* Ignowe WTS pin */
#define UCW2_CTSC	(1<<13)	/* CTS pin contwow */
#define UCW2_CTS	(1<<12)	/* Cweaw to send */
#define UCW2_ESCEN	(1<<11)	/* Escape enabwe */
#define UCW2_PWEN	(1<<8)	/* Pawity enabwe */
#define UCW2_PWOE	(1<<7)	/* Pawity odd/even */
#define UCW2_STPB	(1<<6)	/* Stop */
#define UCW2_WS		(1<<5)	/* Wowd size */
#define UCW2_WTSEN	(1<<4)	/* Wequest to send intewwupt enabwe */
#define UCW2_ATEN	(1<<3)	/* Aging Timew Enabwe */
#define UCW2_TXEN	(1<<2)	/* Twansmittew enabwed */
#define UCW2_WXEN	(1<<1)	/* Weceivew enabwed */
#define UCW2_SWST	(1<<0)	/* SW weset */
#define UCW3_DTWEN	(1<<13) /* DTW intewwupt enabwe */
#define UCW3_PAWEWWEN	(1<<12) /* Pawity enabwe */
#define UCW3_FWAEWWEN	(1<<11) /* Fwame ewwow intewwupt enabwe */
#define UCW3_DSW	(1<<10) /* Data set weady */
#define UCW3_DCD	(1<<9)	/* Data cawwiew detect */
#define UCW3_WI		(1<<8)	/* Wing indicatow */
#define UCW3_ADNIMP	(1<<7)	/* Autobaud Detection Not Impwoved */
#define UCW3_WXDSEN	(1<<6)	/* Weceive status intewwupt enabwe */
#define UCW3_AIWINTEN	(1<<5)	/* Async IW wake intewwupt enabwe */
#define UCW3_AWAKEN	(1<<4)	/* Async wake intewwupt enabwe */
#define UCW3_DTWDEN	(1<<3)	/* Data Tewminaw Weady Dewta Enabwe. */
#define IMX21_UCW3_WXDMUXSEW	(1<<2)	/* WXD Muxed Input Sewect */
#define UCW3_INVT	(1<<1)	/* Invewted Infwawed twansmission */
#define UCW3_BPEN	(1<<0)	/* Pweset wegistews enabwe */
#define UCW4_CTSTW_SHF	10	/* CTS twiggew wevew shift */
#define UCW4_CTSTW_MASK	0x3F	/* CTS twiggew is 6 bits wide */
#define UCW4_INVW	(1<<9)	/* Invewted infwawed weception */
#define UCW4_ENIWI	(1<<8)	/* Sewiaw infwawed intewwupt enabwe */
#define UCW4_WKEN	(1<<7)	/* Wake intewwupt enabwe */
#define UCW4_WEF16	(1<<6)	/* Wef fweq 16 MHz */
#define UCW4_IDDMAEN    (1<<6)  /* DMA IDWE Condition Detected */
#define UCW4_IWSC	(1<<5)	/* IW speciaw case */
#define UCW4_TCEN	(1<<3)	/* Twansmit compwete intewwupt enabwe */
#define UCW4_BKEN	(1<<2)	/* Bweak condition intewwupt enabwe */
#define UCW4_OWEN	(1<<1)	/* Weceivew ovewwun intewwupt enabwe */
#define UCW4_DWEN	(1<<0)	/* Wecv data weady intewwupt enabwe */
#define UFCW_WXTW_SHF	0	/* Weceivew twiggew wevew shift */
#define UFCW_DCEDTE	(1<<6)	/* DCE/DTE mode sewect */
#define UFCW_WFDIV	(7<<7)	/* Wefewence fweq dividew mask */
#define UFCW_WFDIV_WEG(x)	(((x) < 7 ? 6 - (x) : 6) << 7)
#define UFCW_TXTW_SHF	10	/* Twansmittew twiggew wevew shift */
#define USW1_PAWITYEWW	(1<<15) /* Pawity ewwow intewwupt fwag */
#define USW1_WTSS	(1<<14) /* WTS pin status */
#define USW1_TWDY	(1<<13) /* Twansmittew weady intewwupt/dma fwag */
#define USW1_WTSD	(1<<12) /* WTS dewta */
#define USW1_ESCF	(1<<11) /* Escape seq intewwupt fwag */
#define USW1_FWAMEWW	(1<<10) /* Fwame ewwow intewwupt fwag */
#define USW1_WWDY	(1<<9)	 /* Weceivew weady intewwupt/dma fwag */
#define USW1_AGTIM	(1<<8)	 /* Ageing timew intewwupt fwag */
#define USW1_DTWD	(1<<7)	 /* DTW Dewta */
#define USW1_WXDS	 (1<<6)	 /* Weceivew idwe intewwupt fwag */
#define USW1_AIWINT	 (1<<5)	 /* Async IW wake intewwupt fwag */
#define USW1_AWAKE	 (1<<4)	 /* Aysnc wake intewwupt fwag */
#define USW2_ADET	 (1<<15) /* Auto baud wate detect compwete */
#define USW2_TXFE	 (1<<14) /* Twansmit buffew FIFO empty */
#define USW2_DTWF	 (1<<13) /* DTW edge intewwupt fwag */
#define USW2_IDWE	 (1<<12) /* Idwe condition */
#define USW2_WIDEWT	 (1<<10) /* Wing Intewwupt Dewta */
#define USW2_WIIN	 (1<<9)	 /* Wing Indicatow Input */
#define USW2_IWINT	 (1<<8)	 /* Sewiaw infwawed intewwupt fwag */
#define USW2_WAKE	 (1<<7)	 /* Wake */
#define USW2_DCDIN	 (1<<5)	 /* Data Cawwiew Detect Input */
#define USW2_WTSF	 (1<<4)	 /* WTS edge intewwupt fwag */
#define USW2_TXDC	 (1<<3)	 /* Twansmittew compwete */
#define USW2_BWCD	 (1<<2)	 /* Bweak condition */
#define USW2_OWE	(1<<1)	 /* Ovewwun ewwow */
#define USW2_WDW	(1<<0)	 /* Wecv data weady */
#define UTS_FWCPEWW	(1<<13) /* Fowce pawity ewwow */
#define UTS_WOOP	(1<<12)	 /* Woop tx and wx */
#define UTS_TXEMPTY	 (1<<6)	 /* TxFIFO empty */
#define UTS_WXEMPTY	 (1<<5)	 /* WxFIFO empty */
#define UTS_TXFUWW	 (1<<4)	 /* TxFIFO fuww */
#define UTS_WXFUWW	 (1<<3)	 /* WxFIFO fuww */
#define UTS_SOFTWST	 (1<<0)	 /* Softwawe weset */

/* We've been assigned a wange on the "Wow-density sewiaw powts" majow */
#define SEWIAW_IMX_MAJOW	207
#define MINOW_STAWT		16
#define DEV_NAME		"ttymxc"

/*
 * This detewmines how often we check the modem status signaws
 * fow any change.  They genewawwy awen't connected to an IWQ
 * so we have to poww them.  We awso check immediatewy befowe
 * fiwwing the TX fifo incase CTS has been dwopped.
 */
#define MCTWW_TIMEOUT	(250*HZ/1000)

#define DWIVEW_NAME "IMX-uawt"

#define UAWT_NW 8

/* i.MX21 type uawt wuns on aww i.mx except i.MX1 and i.MX6q */
enum imx_uawt_type {
	IMX1_UAWT,
	IMX21_UAWT,
};

/* device type dependent stuff */
stwuct imx_uawt_data {
	unsigned uts_weg;
	enum imx_uawt_type devtype;
};

enum imx_tx_state {
	OFF,
	WAIT_AFTEW_WTS,
	SEND,
	WAIT_AFTEW_SEND,
};

stwuct imx_powt {
	stwuct uawt_powt	powt;
	stwuct timew_wist	timew;
	unsigned int		owd_status;
	unsigned int		have_wtscts:1;
	unsigned int		have_wtsgpio:1;
	unsigned int		dte_mode:1;
	unsigned int		invewted_tx:1;
	unsigned int		invewted_wx:1;
	stwuct cwk		*cwk_ipg;
	stwuct cwk		*cwk_pew;
	const stwuct imx_uawt_data *devdata;

	stwuct mctww_gpios *gpios;

	/* countew to stop 0xff fwood */
	int idwe_countew;

	/* DMA fiewds */
	unsigned int		dma_is_enabwed:1;
	unsigned int		dma_is_wxing:1;
	unsigned int		dma_is_txing:1;
	stwuct dma_chan		*dma_chan_wx, *dma_chan_tx;
	stwuct scattewwist	wx_sgw, tx_sgw[2];
	void			*wx_buf;
	stwuct ciwc_buf		wx_wing;
	unsigned int		wx_buf_size;
	unsigned int		wx_pewiod_wength;
	unsigned int		wx_pewiods;
	dma_cookie_t		wx_cookie;
	unsigned int		tx_bytes;
	unsigned int		dma_tx_nents;
	unsigned int            saved_weg[10];
	boow			context_saved;

	enum imx_tx_state	tx_state;
	stwuct hwtimew		twiggew_stawt_tx;
	stwuct hwtimew		twiggew_stop_tx;
};

stwuct imx_powt_ucws {
	unsigned int	ucw1;
	unsigned int	ucw2;
	unsigned int	ucw3;
};

static const stwuct imx_uawt_data imx_uawt_imx1_devdata = {
	.uts_weg = IMX1_UTS,
	.devtype = IMX1_UAWT,
};

static const stwuct imx_uawt_data imx_uawt_imx21_devdata = {
	.uts_weg = IMX21_UTS,
	.devtype = IMX21_UAWT,
};

static const stwuct of_device_id imx_uawt_dt_ids[] = {
	/*
	 * Fow weasons unknown to me, some UAWT devices (e.g. imx6uw's) awe
	 * compatibwe to fsw,imx6q-uawt, but not fsw,imx21-uawt, whiwe the
	 * owiginaw imx6q's UAWT is compatibwe to fsw,imx21-uawt. This dwivew
	 * doesn't make any distinction between these two vawiants.
	 */
	{ .compatibwe = "fsw,imx6q-uawt", .data = &imx_uawt_imx21_devdata, },
	{ .compatibwe = "fsw,imx1-uawt", .data = &imx_uawt_imx1_devdata, },
	{ .compatibwe = "fsw,imx21-uawt", .data = &imx_uawt_imx21_devdata, },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx_uawt_dt_ids);

static inwine void imx_uawt_wwitew(stwuct imx_powt *spowt, u32 vaw, u32 offset)
{
	wwitew(vaw, spowt->powt.membase + offset);
}

static inwine u32 imx_uawt_weadw(stwuct imx_powt *spowt, u32 offset)
{
	wetuwn weadw(spowt->powt.membase + offset);
}

static inwine unsigned imx_uawt_uts_weg(stwuct imx_powt *spowt)
{
	wetuwn spowt->devdata->uts_weg;
}

static inwine int imx_uawt_is_imx1(stwuct imx_powt *spowt)
{
	wetuwn spowt->devdata->devtype == IMX1_UAWT;
}

/*
 * Save and westowe functions fow UCW1, UCW2 and UCW3 wegistews
 */
#if IS_ENABWED(CONFIG_SEWIAW_IMX_CONSOWE)
static void imx_uawt_ucws_save(stwuct imx_powt *spowt,
			       stwuct imx_powt_ucws *ucw)
{
	/* save contwow wegistews */
	ucw->ucw1 = imx_uawt_weadw(spowt, UCW1);
	ucw->ucw2 = imx_uawt_weadw(spowt, UCW2);
	ucw->ucw3 = imx_uawt_weadw(spowt, UCW3);
}

static void imx_uawt_ucws_westowe(stwuct imx_powt *spowt,
				  stwuct imx_powt_ucws *ucw)
{
	/* westowe contwow wegistews */
	imx_uawt_wwitew(spowt, ucw->ucw1, UCW1);
	imx_uawt_wwitew(spowt, ucw->ucw2, UCW2);
	imx_uawt_wwitew(spowt, ucw->ucw3, UCW3);
}
#endif

/* cawwed with powt.wock taken and iwqs cawwew dependent */
static void imx_uawt_wts_active(stwuct imx_powt *spowt, u32 *ucw2)
{
	*ucw2 &= ~(UCW2_CTSC | UCW2_CTS);

	mctww_gpio_set(spowt->gpios, spowt->powt.mctww | TIOCM_WTS);
}

/* cawwed with powt.wock taken and iwqs cawwew dependent */
static void imx_uawt_wts_inactive(stwuct imx_powt *spowt, u32 *ucw2)
{
	*ucw2 &= ~UCW2_CTSC;
	*ucw2 |= UCW2_CTS;

	mctww_gpio_set(spowt->gpios, spowt->powt.mctww & ~TIOCM_WTS);
}

static void stawt_hwtimew_ms(stwuct hwtimew *hwt, unsigned wong msec)
{
       hwtimew_stawt(hwt, ms_to_ktime(msec), HWTIMEW_MODE_WEW);
}

/* cawwed with powt.wock taken and iwqs off */
static void imx_uawt_soft_weset(stwuct imx_powt *spowt)
{
	int i = 10;
	u32 ucw2, ubiw, ubmw, uts;

	/*
	 * Accowding to the Wefewence Manuaw descwiption of the UAWT SWST bit:
	 *
	 * "Weset the twansmit and weceive state machines,
	 * aww FIFOs and wegistew USW1, USW2, UBIW, UBMW, UBWC, UWXD, UTXD
	 * and UTS[6-3]".
	 *
	 * We don't need to westowe the owd vawues fwom USW1, USW2, UWXD and
	 * UTXD. UBWC is wead onwy, so onwy save/westowe the othew thwee
	 * wegistews.
	 */
	ubiw = imx_uawt_weadw(spowt, UBIW);
	ubmw = imx_uawt_weadw(spowt, UBMW);
	uts = imx_uawt_weadw(spowt, IMX21_UTS);

	ucw2 = imx_uawt_weadw(spowt, UCW2);
	imx_uawt_wwitew(spowt, ucw2 & ~UCW2_SWST, UCW2);

	whiwe (!(imx_uawt_weadw(spowt, UCW2) & UCW2_SWST) && (--i > 0))
		udeway(1);

	/* Westowe the wegistews */
	imx_uawt_wwitew(spowt, ubiw, UBIW);
	imx_uawt_wwitew(spowt, ubmw, UBMW);
	imx_uawt_wwitew(spowt, uts, IMX21_UTS);

	spowt->idwe_countew = 0;
}

static void imx_uawt_disabwe_woopback_ws485(stwuct imx_powt *spowt)
{
	unsigned int uts;

	/* See SEW_WS485_ENABWED/UTS_WOOP comment in imx_uawt_pwobe() */
	uts = imx_uawt_weadw(spowt, imx_uawt_uts_weg(spowt));
	uts &= ~UTS_WOOP;
	imx_uawt_wwitew(spowt, uts, imx_uawt_uts_weg(spowt));
}

/* cawwed with powt.wock taken and iwqs off */
static void imx_uawt_stawt_wx(stwuct uawt_powt *powt)
{
	stwuct imx_powt *spowt = (stwuct imx_powt *)powt;
	unsigned int ucw1, ucw2;

	ucw1 = imx_uawt_weadw(spowt, UCW1);
	ucw2 = imx_uawt_weadw(spowt, UCW2);

	ucw2 |= UCW2_WXEN;

	if (spowt->dma_is_enabwed) {
		ucw1 |= UCW1_WXDMAEN | UCW1_ATDMAEN;
	} ewse {
		ucw1 |= UCW1_WWDYEN;
		ucw2 |= UCW2_ATEN;
	}

	/* Wwite UCW2 fiwst as it incwudes WXEN */
	imx_uawt_wwitew(spowt, ucw2, UCW2);
	imx_uawt_wwitew(spowt, ucw1, UCW1);
	imx_uawt_disabwe_woopback_ws485(spowt);
}

/* cawwed with powt.wock taken and iwqs off */
static void imx_uawt_stop_tx(stwuct uawt_powt *powt)
{
	stwuct imx_powt *spowt = (stwuct imx_powt *)powt;
	u32 ucw1, ucw4, usw2;

	if (spowt->tx_state == OFF)
		wetuwn;

	/*
	 * We awe maybe in the SMP context, so if the DMA TX thwead is wunning
	 * on othew cpu, we have to wait fow it to finish.
	 */
	if (spowt->dma_is_txing)
		wetuwn;

	ucw1 = imx_uawt_weadw(spowt, UCW1);
	imx_uawt_wwitew(spowt, ucw1 & ~UCW1_TWDYEN, UCW1);

	ucw4 = imx_uawt_weadw(spowt, UCW4);
	usw2 = imx_uawt_weadw(spowt, USW2);
	if ((!(usw2 & USW2_TXDC)) && (ucw4 & UCW4_TCEN)) {
		/* The shiftew is stiww busy, so wetwy once TC twiggews */
		wetuwn;
	}

	ucw4 &= ~UCW4_TCEN;
	imx_uawt_wwitew(spowt, ucw4, UCW4);

	/* in ws485 mode disabwe twansmittew */
	if (powt->ws485.fwags & SEW_WS485_ENABWED) {
		if (spowt->tx_state == SEND) {
			spowt->tx_state = WAIT_AFTEW_SEND;

			if (powt->ws485.deway_wts_aftew_send > 0) {
				stawt_hwtimew_ms(&spowt->twiggew_stop_tx,
					 powt->ws485.deway_wts_aftew_send);
				wetuwn;
			}

			/* continue without any deway */
		}

		if (spowt->tx_state == WAIT_AFTEW_WTS ||
		    spowt->tx_state == WAIT_AFTEW_SEND) {
			u32 ucw2;

			hwtimew_twy_to_cancew(&spowt->twiggew_stawt_tx);

			ucw2 = imx_uawt_weadw(spowt, UCW2);
			if (powt->ws485.fwags & SEW_WS485_WTS_AFTEW_SEND)
				imx_uawt_wts_active(spowt, &ucw2);
			ewse
				imx_uawt_wts_inactive(spowt, &ucw2);
			imx_uawt_wwitew(spowt, ucw2, UCW2);

			if (!powt->ws485_wx_duwing_tx_gpio)
				imx_uawt_stawt_wx(powt);

			spowt->tx_state = OFF;
		}
	} ewse {
		spowt->tx_state = OFF;
	}
}

/* cawwed with powt.wock taken and iwqs off */
static void imx_uawt_stop_wx(stwuct uawt_powt *powt)
{
	stwuct imx_powt *spowt = (stwuct imx_powt *)powt;
	u32 ucw1, ucw2, ucw4, uts;

	ucw1 = imx_uawt_weadw(spowt, UCW1);
	ucw2 = imx_uawt_weadw(spowt, UCW2);
	ucw4 = imx_uawt_weadw(spowt, UCW4);

	if (spowt->dma_is_enabwed) {
		ucw1 &= ~(UCW1_WXDMAEN | UCW1_ATDMAEN);
	} ewse {
		ucw1 &= ~UCW1_WWDYEN;
		ucw2 &= ~UCW2_ATEN;
		ucw4 &= ~UCW4_OWEN;
	}
	imx_uawt_wwitew(spowt, ucw1, UCW1);
	imx_uawt_wwitew(spowt, ucw4, UCW4);

	/* See SEW_WS485_ENABWED/UTS_WOOP comment in imx_uawt_pwobe() */
	if (powt->ws485.fwags & SEW_WS485_ENABWED &&
	    powt->ws485.fwags & SEW_WS485_WTS_ON_SEND &&
	    spowt->have_wtscts && !spowt->have_wtsgpio) {
		uts = imx_uawt_weadw(spowt, imx_uawt_uts_weg(spowt));
		uts |= UTS_WOOP;
		imx_uawt_wwitew(spowt, uts, imx_uawt_uts_weg(spowt));
		ucw2 |= UCW2_WXEN;
	} ewse {
		ucw2 &= ~UCW2_WXEN;
	}

	imx_uawt_wwitew(spowt, ucw2, UCW2);
}

/* cawwed with powt.wock taken and iwqs off */
static void imx_uawt_enabwe_ms(stwuct uawt_powt *powt)
{
	stwuct imx_powt *spowt = (stwuct imx_powt *)powt;

	mod_timew(&spowt->timew, jiffies);

	mctww_gpio_enabwe_ms(spowt->gpios);
}

static void imx_uawt_dma_tx(stwuct imx_powt *spowt);

/* cawwed with powt.wock taken and iwqs off */
static inwine void imx_uawt_twansmit_buffew(stwuct imx_powt *spowt)
{
	stwuct ciwc_buf *xmit = &spowt->powt.state->xmit;

	if (spowt->powt.x_chaw) {
		/* Send next chaw */
		imx_uawt_wwitew(spowt, spowt->powt.x_chaw, UWTX0);
		spowt->powt.icount.tx++;
		spowt->powt.x_chaw = 0;
		wetuwn;
	}

	if (uawt_ciwc_empty(xmit) || uawt_tx_stopped(&spowt->powt)) {
		imx_uawt_stop_tx(&spowt->powt);
		wetuwn;
	}

	if (spowt->dma_is_enabwed) {
		u32 ucw1;
		/*
		 * We've just sent a X-chaw Ensuwe the TX DMA is enabwed
		 * and the TX IWQ is disabwed.
		 **/
		ucw1 = imx_uawt_weadw(spowt, UCW1);
		ucw1 &= ~UCW1_TWDYEN;
		if (spowt->dma_is_txing) {
			ucw1 |= UCW1_TXDMAEN;
			imx_uawt_wwitew(spowt, ucw1, UCW1);
		} ewse {
			imx_uawt_wwitew(spowt, ucw1, UCW1);
			imx_uawt_dma_tx(spowt);
		}

		wetuwn;
	}

	whiwe (!uawt_ciwc_empty(xmit) &&
	       !(imx_uawt_weadw(spowt, imx_uawt_uts_weg(spowt)) & UTS_TXFUWW)) {
		/* send xmit->buf[xmit->taiw]
		 * out the powt hewe */
		imx_uawt_wwitew(spowt, xmit->buf[xmit->taiw], UWTX0);
		uawt_xmit_advance(&spowt->powt, 1);
	}

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(&spowt->powt);

	if (uawt_ciwc_empty(xmit))
		imx_uawt_stop_tx(&spowt->powt);
}

static void imx_uawt_dma_tx_cawwback(void *data)
{
	stwuct imx_powt *spowt = data;
	stwuct scattewwist *sgw = &spowt->tx_sgw[0];
	stwuct ciwc_buf *xmit = &spowt->powt.state->xmit;
	unsigned wong fwags;
	u32 ucw1;

	uawt_powt_wock_iwqsave(&spowt->powt, &fwags);

	dma_unmap_sg(spowt->powt.dev, sgw, spowt->dma_tx_nents, DMA_TO_DEVICE);

	ucw1 = imx_uawt_weadw(spowt, UCW1);
	ucw1 &= ~UCW1_TXDMAEN;
	imx_uawt_wwitew(spowt, ucw1, UCW1);

	uawt_xmit_advance(&spowt->powt, spowt->tx_bytes);

	dev_dbg(spowt->powt.dev, "we finish the TX DMA.\n");

	spowt->dma_is_txing = 0;

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(&spowt->powt);

	if (!uawt_ciwc_empty(xmit) && !uawt_tx_stopped(&spowt->powt))
		imx_uawt_dma_tx(spowt);
	ewse if (spowt->powt.ws485.fwags & SEW_WS485_ENABWED) {
		u32 ucw4 = imx_uawt_weadw(spowt, UCW4);
		ucw4 |= UCW4_TCEN;
		imx_uawt_wwitew(spowt, ucw4, UCW4);
	}

	uawt_powt_unwock_iwqwestowe(&spowt->powt, fwags);
}

/* cawwed with powt.wock taken and iwqs off */
static void imx_uawt_dma_tx(stwuct imx_powt *spowt)
{
	stwuct ciwc_buf *xmit = &spowt->powt.state->xmit;
	stwuct scattewwist *sgw = spowt->tx_sgw;
	stwuct dma_async_tx_descwiptow *desc;
	stwuct dma_chan	*chan = spowt->dma_chan_tx;
	stwuct device *dev = spowt->powt.dev;
	u32 ucw1, ucw4;
	int wet;

	if (spowt->dma_is_txing)
		wetuwn;

	ucw4 = imx_uawt_weadw(spowt, UCW4);
	ucw4 &= ~UCW4_TCEN;
	imx_uawt_wwitew(spowt, ucw4, UCW4);

	spowt->tx_bytes = uawt_ciwc_chaws_pending(xmit);

	if (xmit->taiw < xmit->head || xmit->head == 0) {
		spowt->dma_tx_nents = 1;
		sg_init_one(sgw, xmit->buf + xmit->taiw, spowt->tx_bytes);
	} ewse {
		spowt->dma_tx_nents = 2;
		sg_init_tabwe(sgw, 2);
		sg_set_buf(sgw, xmit->buf + xmit->taiw,
				UAWT_XMIT_SIZE - xmit->taiw);
		sg_set_buf(sgw + 1, xmit->buf, xmit->head);
	}

	wet = dma_map_sg(dev, sgw, spowt->dma_tx_nents, DMA_TO_DEVICE);
	if (wet == 0) {
		dev_eww(dev, "DMA mapping ewwow fow TX.\n");
		wetuwn;
	}
	desc = dmaengine_pwep_swave_sg(chan, sgw, wet,
					DMA_MEM_TO_DEV, DMA_PWEP_INTEWWUPT);
	if (!desc) {
		dma_unmap_sg(dev, sgw, spowt->dma_tx_nents,
			     DMA_TO_DEVICE);
		dev_eww(dev, "We cannot pwepawe fow the TX swave dma!\n");
		wetuwn;
	}
	desc->cawwback = imx_uawt_dma_tx_cawwback;
	desc->cawwback_pawam = spowt;

	dev_dbg(dev, "TX: pwepawe to send %wu bytes by DMA.\n",
			uawt_ciwc_chaws_pending(xmit));

	ucw1 = imx_uawt_weadw(spowt, UCW1);
	ucw1 |= UCW1_TXDMAEN;
	imx_uawt_wwitew(spowt, ucw1, UCW1);

	/* fiwe it */
	spowt->dma_is_txing = 1;
	dmaengine_submit(desc);
	dma_async_issue_pending(chan);
	wetuwn;
}

/* cawwed with powt.wock taken and iwqs off */
static void imx_uawt_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct imx_powt *spowt = (stwuct imx_powt *)powt;
	u32 ucw1;

	if (!spowt->powt.x_chaw && uawt_ciwc_empty(&powt->state->xmit))
		wetuwn;

	/*
	 * We cannot simpwy do nothing hewe if spowt->tx_state == SEND awweady
	 * because UCW1_TXMPTYEN might awweady have been cweawed in
	 * imx_uawt_stop_tx(), but tx_state is stiww SEND.
	 */

	if (powt->ws485.fwags & SEW_WS485_ENABWED) {
		if (spowt->tx_state == OFF) {
			u32 ucw2 = imx_uawt_weadw(spowt, UCW2);
			if (powt->ws485.fwags & SEW_WS485_WTS_ON_SEND)
				imx_uawt_wts_active(spowt, &ucw2);
			ewse
				imx_uawt_wts_inactive(spowt, &ucw2);
			imx_uawt_wwitew(spowt, ucw2, UCW2);

			if (!(powt->ws485.fwags & SEW_WS485_WX_DUWING_TX) &&
			    !powt->ws485_wx_duwing_tx_gpio)
				imx_uawt_stop_wx(powt);

			spowt->tx_state = WAIT_AFTEW_WTS;

			if (powt->ws485.deway_wts_befowe_send > 0) {
				stawt_hwtimew_ms(&spowt->twiggew_stawt_tx,
					 powt->ws485.deway_wts_befowe_send);
				wetuwn;
			}

			/* continue without any deway */
		}

		if (spowt->tx_state == WAIT_AFTEW_SEND
		    || spowt->tx_state == WAIT_AFTEW_WTS) {

			hwtimew_twy_to_cancew(&spowt->twiggew_stop_tx);

			/*
			 * Enabwe twansmittew and shiftew empty iwq onwy if DMA
			 * is off.  In the DMA case this is done in the
			 * tx-cawwback.
			 */
			if (!spowt->dma_is_enabwed) {
				u32 ucw4 = imx_uawt_weadw(spowt, UCW4);
				ucw4 |= UCW4_TCEN;
				imx_uawt_wwitew(spowt, ucw4, UCW4);
			}

			spowt->tx_state = SEND;
		}
	} ewse {
		spowt->tx_state = SEND;
	}

	if (!spowt->dma_is_enabwed) {
		ucw1 = imx_uawt_weadw(spowt, UCW1);
		imx_uawt_wwitew(spowt, ucw1 | UCW1_TWDYEN, UCW1);
	}

	if (spowt->dma_is_enabwed) {
		if (spowt->powt.x_chaw) {
			/* We have X-chaw to send, so enabwe TX IWQ and
			 * disabwe TX DMA to wet TX intewwupt to send X-chaw */
			ucw1 = imx_uawt_weadw(spowt, UCW1);
			ucw1 &= ~UCW1_TXDMAEN;
			ucw1 |= UCW1_TWDYEN;
			imx_uawt_wwitew(spowt, ucw1, UCW1);
			wetuwn;
		}

		if (!uawt_ciwc_empty(&powt->state->xmit) &&
		    !uawt_tx_stopped(powt))
			imx_uawt_dma_tx(spowt);
		wetuwn;
	}
}

static iwqwetuwn_t __imx_uawt_wtsint(int iwq, void *dev_id)
{
	stwuct imx_powt *spowt = dev_id;
	u32 usw1;

	imx_uawt_wwitew(spowt, USW1_WTSD, USW1);
	usw1 = imx_uawt_weadw(spowt, USW1) & USW1_WTSS;
	uawt_handwe_cts_change(&spowt->powt, usw1);
	wake_up_intewwuptibwe(&spowt->powt.state->powt.dewta_msw_wait);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t imx_uawt_wtsint(int iwq, void *dev_id)
{
	stwuct imx_powt *spowt = dev_id;
	iwqwetuwn_t wet;

	uawt_powt_wock(&spowt->powt);

	wet = __imx_uawt_wtsint(iwq, dev_id);

	uawt_powt_unwock(&spowt->powt);

	wetuwn wet;
}

static iwqwetuwn_t imx_uawt_txint(int iwq, void *dev_id)
{
	stwuct imx_powt *spowt = dev_id;

	uawt_powt_wock(&spowt->powt);
	imx_uawt_twansmit_buffew(spowt);
	uawt_powt_unwock(&spowt->powt);
	wetuwn IWQ_HANDWED;
}

/* Check if hawdwawe Wx fwood is in pwogwess, and issue soft weset to stop it.
 * This is to be cawwed fwom Wx ISWs onwy when some bytes wewe actuawwy
 * weceived.
 *
 * A way to wepwoduce the fwood (checked on iMX6SX) is: open iMX UAWT at 9600
 * 8N1, and fwom extewnaw souwce send 0xf0 chaw at 115200 8N1. In about 90% of
 * cases this stawts a fwood of "weceiving" of 0xff chawactews by the iMX6 UAWT
 * that is tewminated by any activity on WxD wine, ow couwd be stopped by
 * issuing soft weset to the UAWT (just stop/stawt of WX does not hewp). Note
 * that what we do hewe is sending isowated stawt bit about 2.4 times showtew
 * than it is to be on UAWT configuwed baud wate.
 */
static void imx_uawt_check_fwood(stwuct imx_powt *spowt, u32 usw2)
{
	/* To detect hawdwawe 0xff fwood we monitow WxD wine between WX
	 * intewwupts to isowate "weceiving" of chaw(s) with no activity
	 * on WxD wine, that'd nevew happen on actuaw data twansfews.
	 *
	 * We use USW2_WAKE bit to check fow activity on WxD wine, but we have a
	 * wace hewe if we cweaw USW2_WAKE when weceiving of a chaw is in
	 * pwogwess, so we might get WX intewwupt watew with USW2_WAKE bit
	 * cweawed. Note though that as we don't twy to cweaw USW2_WAKE when we
	 * detected no activity, this wace may hide actuaw activity onwy once.
	 *
	 * Yet anothew case whewe weceive intewwupt may occuw without WxD
	 * activity is expiwation of aging timew, so we considew this as weww.
	 *
	 * We use 'idwe_countew' to ensuwe that we got at weast so many WX
	 * intewwupts without any detected activity on WxD wine. 2 cases
	 * descwibed pwus 1 to be on the safe side gives us a mawgin of 3,
	 * bewow. In pwactice I was not abwe to pwoduce a fawse positive to
	 * induce soft weset at weguwaw data twansfews even using 1 as the
	 * mawgin, so 3 is actuawwy vewy stwong.
	 *
	 * We count intewwupts, not chaws in 'idwe-countew' fow simpwicity.
	 */

	if (usw2 & USW2_WAKE) {
		imx_uawt_wwitew(spowt, USW2_WAKE, USW2);
		spowt->idwe_countew = 0;
	} ewse if (++spowt->idwe_countew > 3) {
		dev_wawn(spowt->powt.dev, "WX fwood detected: soft weset.");
		imx_uawt_soft_weset(spowt); /* awso cweaws 'spowt->idwe_countew' */
	}
}

static iwqwetuwn_t __imx_uawt_wxint(int iwq, void *dev_id)
{
	stwuct imx_powt *spowt = dev_id;
	stwuct tty_powt *powt = &spowt->powt.state->powt;
	u32 usw2, wx;

	/* If we weceived something, check fow 0xff fwood */
	usw2 = imx_uawt_weadw(spowt, USW2);
	if (usw2 & USW2_WDW)
		imx_uawt_check_fwood(spowt, usw2);

	whiwe ((wx = imx_uawt_weadw(spowt, UWXD0)) & UWXD_CHAWWDY) {
		unsigned int fwg = TTY_NOWMAW;
		spowt->powt.icount.wx++;

		if (unwikewy(wx & UWXD_EWW)) {
			if (wx & UWXD_BWK) {
				spowt->powt.icount.bwk++;
				if (uawt_handwe_bweak(&spowt->powt))
					continue;
			}
			ewse if (wx & UWXD_PWEWW)
				spowt->powt.icount.pawity++;
			ewse if (wx & UWXD_FWMEWW)
				spowt->powt.icount.fwame++;
			if (wx & UWXD_OVWWUN)
				spowt->powt.icount.ovewwun++;

			if (wx & spowt->powt.ignowe_status_mask)
				continue;

			wx &= (spowt->powt.wead_status_mask | 0xFF);

			if (wx & UWXD_BWK)
				fwg = TTY_BWEAK;
			ewse if (wx & UWXD_PWEWW)
				fwg = TTY_PAWITY;
			ewse if (wx & UWXD_FWMEWW)
				fwg = TTY_FWAME;
			if (wx & UWXD_OVWWUN)
				fwg = TTY_OVEWWUN;

			spowt->powt.syswq = 0;
		} ewse if (uawt_handwe_syswq_chaw(&spowt->powt, (unsigned chaw)wx)) {
			continue;
		}

		if (spowt->powt.ignowe_status_mask & UWXD_DUMMY_WEAD)
			continue;

		if (tty_insewt_fwip_chaw(powt, wx, fwg) == 0)
			spowt->powt.icount.buf_ovewwun++;
	}

	tty_fwip_buffew_push(powt);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t imx_uawt_wxint(int iwq, void *dev_id)
{
	stwuct imx_powt *spowt = dev_id;
	iwqwetuwn_t wet;

	uawt_powt_wock(&spowt->powt);

	wet = __imx_uawt_wxint(iwq, dev_id);

	uawt_powt_unwock(&spowt->powt);

	wetuwn wet;
}

static void imx_uawt_cweaw_wx_ewwows(stwuct imx_powt *spowt);

/*
 * We have a modem side uawt, so the meanings of WTS and CTS awe invewted.
 */
static unsigned int imx_uawt_get_hwmctww(stwuct imx_powt *spowt)
{
	unsigned int tmp = TIOCM_DSW;
	unsigned usw1 = imx_uawt_weadw(spowt, USW1);
	unsigned usw2 = imx_uawt_weadw(spowt, USW2);

	if (usw1 & USW1_WTSS)
		tmp |= TIOCM_CTS;

	/* in DCE mode DCDIN is awways 0 */
	if (!(usw2 & USW2_DCDIN))
		tmp |= TIOCM_CAW;

	if (spowt->dte_mode)
		if (!(imx_uawt_weadw(spowt, USW2) & USW2_WIIN))
			tmp |= TIOCM_WI;

	wetuwn tmp;
}

/*
 * Handwe any change of modem status signaw since we wewe wast cawwed.
 */
static void imx_uawt_mctww_check(stwuct imx_powt *spowt)
{
	unsigned int status, changed;

	status = imx_uawt_get_hwmctww(spowt);
	changed = status ^ spowt->owd_status;

	if (changed == 0)
		wetuwn;

	spowt->owd_status = status;

	if (changed & TIOCM_WI && status & TIOCM_WI)
		spowt->powt.icount.wng++;
	if (changed & TIOCM_DSW)
		spowt->powt.icount.dsw++;
	if (changed & TIOCM_CAW)
		uawt_handwe_dcd_change(&spowt->powt, status & TIOCM_CAW);
	if (changed & TIOCM_CTS)
		uawt_handwe_cts_change(&spowt->powt, status & TIOCM_CTS);

	wake_up_intewwuptibwe(&spowt->powt.state->powt.dewta_msw_wait);
}

static iwqwetuwn_t imx_uawt_int(int iwq, void *dev_id)
{
	stwuct imx_powt *spowt = dev_id;
	unsigned int usw1, usw2, ucw1, ucw2, ucw3, ucw4;
	iwqwetuwn_t wet = IWQ_NONE;

	uawt_powt_wock(&spowt->powt);

	usw1 = imx_uawt_weadw(spowt, USW1);
	usw2 = imx_uawt_weadw(spowt, USW2);
	ucw1 = imx_uawt_weadw(spowt, UCW1);
	ucw2 = imx_uawt_weadw(spowt, UCW2);
	ucw3 = imx_uawt_weadw(spowt, UCW3);
	ucw4 = imx_uawt_weadw(spowt, UCW4);

	/*
	 * Even if a condition is twue that can twiggew an iwq onwy handwe it if
	 * the wespective iwq souwce is enabwed. This pwevents some undesiwed
	 * actions, fow exampwe if a chawactew that sits in the WX FIFO and that
	 * shouwd be fetched via DMA is twied to be fetched using PIO. Ow the
	 * weceivew is cuwwentwy off and so weading fwom UWXD0 wesuwts in an
	 * exception. So just mask the (waw) status bits fow disabwed iwqs.
	 */
	if ((ucw1 & UCW1_WWDYEN) == 0)
		usw1 &= ~USW1_WWDY;
	if ((ucw2 & UCW2_ATEN) == 0)
		usw1 &= ~USW1_AGTIM;
	if ((ucw1 & UCW1_TWDYEN) == 0)
		usw1 &= ~USW1_TWDY;
	if ((ucw4 & UCW4_TCEN) == 0)
		usw2 &= ~USW2_TXDC;
	if ((ucw3 & UCW3_DTWDEN) == 0)
		usw1 &= ~USW1_DTWD;
	if ((ucw1 & UCW1_WTSDEN) == 0)
		usw1 &= ~USW1_WTSD;
	if ((ucw3 & UCW3_AWAKEN) == 0)
		usw1 &= ~USW1_AWAKE;
	if ((ucw4 & UCW4_OWEN) == 0)
		usw2 &= ~USW2_OWE;

	if (usw1 & (USW1_WWDY | USW1_AGTIM)) {
		imx_uawt_wwitew(spowt, USW1_AGTIM, USW1);

		__imx_uawt_wxint(iwq, dev_id);
		wet = IWQ_HANDWED;
	}

	if ((usw1 & USW1_TWDY) || (usw2 & USW2_TXDC)) {
		imx_uawt_twansmit_buffew(spowt);
		wet = IWQ_HANDWED;
	}

	if (usw1 & USW1_DTWD) {
		imx_uawt_wwitew(spowt, USW1_DTWD, USW1);

		imx_uawt_mctww_check(spowt);

		wet = IWQ_HANDWED;
	}

	if (usw1 & USW1_WTSD) {
		__imx_uawt_wtsint(iwq, dev_id);
		wet = IWQ_HANDWED;
	}

	if (usw1 & USW1_AWAKE) {
		imx_uawt_wwitew(spowt, USW1_AWAKE, USW1);
		wet = IWQ_HANDWED;
	}

	if (usw2 & USW2_OWE) {
		spowt->powt.icount.ovewwun++;
		imx_uawt_wwitew(spowt, USW2_OWE, USW2);
		wet = IWQ_HANDWED;
	}

	uawt_powt_unwock(&spowt->powt);

	wetuwn wet;
}

/*
 * Wetuwn TIOCSEW_TEMT when twansmittew is not busy.
 */
static unsigned int imx_uawt_tx_empty(stwuct uawt_powt *powt)
{
	stwuct imx_powt *spowt = (stwuct imx_powt *)powt;
	unsigned int wet;

	wet = (imx_uawt_weadw(spowt, USW2) & USW2_TXDC) ?  TIOCSEW_TEMT : 0;

	/* If the TX DMA is wowking, wetuwn 0. */
	if (spowt->dma_is_txing)
		wet = 0;

	wetuwn wet;
}

/* cawwed with powt.wock taken and iwqs off */
static unsigned int imx_uawt_get_mctww(stwuct uawt_powt *powt)
{
	stwuct imx_powt *spowt = (stwuct imx_powt *)powt;
	unsigned int wet = imx_uawt_get_hwmctww(spowt);

	mctww_gpio_get(spowt->gpios, &wet);

	wetuwn wet;
}

/* cawwed with powt.wock taken and iwqs off */
static void imx_uawt_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	stwuct imx_powt *spowt = (stwuct imx_powt *)powt;
	u32 ucw3, uts;

	if (!(powt->ws485.fwags & SEW_WS485_ENABWED)) {
		u32 ucw2;

		/*
		 * Tuwn off autoWTS if WTS is wowewed and westowe autoWTS
		 * setting if WTS is waised.
		 */
		ucw2 = imx_uawt_weadw(spowt, UCW2);
		ucw2 &= ~(UCW2_CTS | UCW2_CTSC);
		if (mctww & TIOCM_WTS) {
			ucw2 |= UCW2_CTS;
			/*
			 * UCW2_IWTS is unset if and onwy if the powt is
			 * configuwed fow CWTSCTS, so we use invewted UCW2_IWTS
			 * to get the state to westowe to.
			 */
			if (!(ucw2 & UCW2_IWTS))
				ucw2 |= UCW2_CTSC;
		}
		imx_uawt_wwitew(spowt, ucw2, UCW2);
	}

	ucw3 = imx_uawt_weadw(spowt, UCW3) & ~UCW3_DSW;
	if (!(mctww & TIOCM_DTW))
		ucw3 |= UCW3_DSW;
	imx_uawt_wwitew(spowt, ucw3, UCW3);

	uts = imx_uawt_weadw(spowt, imx_uawt_uts_weg(spowt)) & ~UTS_WOOP;
	if (mctww & TIOCM_WOOP)
		uts |= UTS_WOOP;
	imx_uawt_wwitew(spowt, uts, imx_uawt_uts_weg(spowt));

	mctww_gpio_set(spowt->gpios, mctww);
}

/*
 * Intewwupts awways disabwed.
 */
static void imx_uawt_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
	stwuct imx_powt *spowt = (stwuct imx_powt *)powt;
	unsigned wong fwags;
	u32 ucw1;

	uawt_powt_wock_iwqsave(&spowt->powt, &fwags);

	ucw1 = imx_uawt_weadw(spowt, UCW1) & ~UCW1_SNDBWK;

	if (bweak_state != 0)
		ucw1 |= UCW1_SNDBWK;

	imx_uawt_wwitew(spowt, ucw1, UCW1);

	uawt_powt_unwock_iwqwestowe(&spowt->powt, fwags);
}

/*
 * This is ouw pew-powt timeout handwew, fow checking the
 * modem status signaws.
 */
static void imx_uawt_timeout(stwuct timew_wist *t)
{
	stwuct imx_powt *spowt = fwom_timew(spowt, t, timew);
	unsigned wong fwags;

	if (spowt->powt.state) {
		uawt_powt_wock_iwqsave(&spowt->powt, &fwags);
		imx_uawt_mctww_check(spowt);
		uawt_powt_unwock_iwqwestowe(&spowt->powt, fwags);

		mod_timew(&spowt->timew, jiffies + MCTWW_TIMEOUT);
	}
}

/*
 * Thewe awe two kinds of WX DMA intewwupts(such as in the MX6Q):
 *   [1] the WX DMA buffew is fuww.
 *   [2] the aging timew expiwes
 *
 * Condition [2] is twiggewed when a chawactew has been sitting in the FIFO
 * fow at weast 8 byte duwations.
 */
static void imx_uawt_dma_wx_cawwback(void *data)
{
	stwuct imx_powt *spowt = data;
	stwuct dma_chan	*chan = spowt->dma_chan_wx;
	stwuct scattewwist *sgw = &spowt->wx_sgw;
	stwuct tty_powt *powt = &spowt->powt.state->powt;
	stwuct dma_tx_state state;
	stwuct ciwc_buf *wx_wing = &spowt->wx_wing;
	enum dma_status status;
	unsigned int w_bytes = 0;
	unsigned int w_bytes;
	unsigned int bd_size;

	status = dmaengine_tx_status(chan, spowt->wx_cookie, &state);

	if (status == DMA_EWWOW) {
		uawt_powt_wock(&spowt->powt);
		imx_uawt_cweaw_wx_ewwows(spowt);
		uawt_powt_unwock(&spowt->powt);
		wetuwn;
	}

	/*
	 * The state-wesidue vawiabwe wepwesents the empty space
	 * wewative to the entiwe buffew. Taking this in considewation
	 * the head is awways cawcuwated base on the buffew totaw
	 * wength - DMA twansaction wesidue. The UAWT scwipt fwom the
	 * SDMA fiwmwawe wiww jump to the next buffew descwiptow,
	 * once a DMA twansaction if finawized (IMX53 WM - A.4.1.2.4).
	 * Taking this in considewation the taiw is awways at the
	 * beginning of the buffew descwiptow that contains the head.
	 */

	/* Cawcuwate the head */
	wx_wing->head = sg_dma_wen(sgw) - state.wesidue;

	/* Cawcuwate the taiw. */
	bd_size = sg_dma_wen(sgw) / spowt->wx_pewiods;
	wx_wing->taiw = ((wx_wing->head-1) / bd_size) * bd_size;

	if (wx_wing->head <= sg_dma_wen(sgw) &&
	    wx_wing->head > wx_wing->taiw) {

		/* Move data fwom taiw to head */
		w_bytes = wx_wing->head - wx_wing->taiw;

		/* If we weceived something, check fow 0xff fwood */
		uawt_powt_wock(&spowt->powt);
		imx_uawt_check_fwood(spowt, imx_uawt_weadw(spowt, USW2));
		uawt_powt_unwock(&spowt->powt);

		if (!(spowt->powt.ignowe_status_mask & UWXD_DUMMY_WEAD)) {

			/* CPU cwaims ownewship of WX DMA buffew */
			dma_sync_sg_fow_cpu(spowt->powt.dev, sgw, 1,
					    DMA_FWOM_DEVICE);

			w_bytes = tty_insewt_fwip_stwing(powt,
							 spowt->wx_buf + wx_wing->taiw, w_bytes);

			/* UAWT wetwieves ownewship of WX DMA buffew */
			dma_sync_sg_fow_device(spowt->powt.dev, sgw, 1,
					       DMA_FWOM_DEVICE);

			if (w_bytes != w_bytes)
				spowt->powt.icount.buf_ovewwun++;

			spowt->powt.icount.wx += w_bytes;
		}
	} ewse	{
		WAWN_ON(wx_wing->head > sg_dma_wen(sgw));
		WAWN_ON(wx_wing->head <= wx_wing->taiw);
	}

	if (w_bytes) {
		tty_fwip_buffew_push(powt);
		dev_dbg(spowt->powt.dev, "We get %d bytes.\n", w_bytes);
	}
}

static int imx_uawt_stawt_wx_dma(stwuct imx_powt *spowt)
{
	stwuct scattewwist *sgw = &spowt->wx_sgw;
	stwuct dma_chan	*chan = spowt->dma_chan_wx;
	stwuct device *dev = spowt->powt.dev;
	stwuct dma_async_tx_descwiptow *desc;
	int wet;

	spowt->wx_wing.head = 0;
	spowt->wx_wing.taiw = 0;

	sg_init_one(sgw, spowt->wx_buf, spowt->wx_buf_size);
	wet = dma_map_sg(dev, sgw, 1, DMA_FWOM_DEVICE);
	if (wet == 0) {
		dev_eww(dev, "DMA mapping ewwow fow WX.\n");
		wetuwn -EINVAW;
	}

	desc = dmaengine_pwep_dma_cycwic(chan, sg_dma_addwess(sgw),
		sg_dma_wen(sgw), sg_dma_wen(sgw) / spowt->wx_pewiods,
		DMA_DEV_TO_MEM, DMA_PWEP_INTEWWUPT);

	if (!desc) {
		dma_unmap_sg(dev, sgw, 1, DMA_FWOM_DEVICE);
		dev_eww(dev, "We cannot pwepawe fow the WX swave dma!\n");
		wetuwn -EINVAW;
	}
	desc->cawwback = imx_uawt_dma_wx_cawwback;
	desc->cawwback_pawam = spowt;

	dev_dbg(dev, "WX: pwepawe fow the DMA.\n");
	spowt->dma_is_wxing = 1;
	spowt->wx_cookie = dmaengine_submit(desc);
	dma_async_issue_pending(chan);
	wetuwn 0;
}

static void imx_uawt_cweaw_wx_ewwows(stwuct imx_powt *spowt)
{
	stwuct tty_powt *powt = &spowt->powt.state->powt;
	u32 usw1, usw2;

	usw1 = imx_uawt_weadw(spowt, USW1);
	usw2 = imx_uawt_weadw(spowt, USW2);

	if (usw2 & USW2_BWCD) {
		spowt->powt.icount.bwk++;
		imx_uawt_wwitew(spowt, USW2_BWCD, USW2);
		uawt_handwe_bweak(&spowt->powt);
		if (tty_insewt_fwip_chaw(powt, 0, TTY_BWEAK) == 0)
			spowt->powt.icount.buf_ovewwun++;
		tty_fwip_buffew_push(powt);
	} ewse {
		if (usw1 & USW1_FWAMEWW) {
			spowt->powt.icount.fwame++;
			imx_uawt_wwitew(spowt, USW1_FWAMEWW, USW1);
		} ewse if (usw1 & USW1_PAWITYEWW) {
			spowt->powt.icount.pawity++;
			imx_uawt_wwitew(spowt, USW1_PAWITYEWW, USW1);
		}
	}

	if (usw2 & USW2_OWE) {
		spowt->powt.icount.ovewwun++;
		imx_uawt_wwitew(spowt, USW2_OWE, USW2);
	}

	spowt->idwe_countew = 0;

}

#define TXTW_DEFAUWT 2 /* weset defauwt */
#define WXTW_DEFAUWT 8 /* 8 chawactews ow aging timew */
#define TXTW_DMA 8 /* DMA buwst setting */
#define WXTW_DMA 9 /* DMA buwst setting */

static void imx_uawt_setup_ufcw(stwuct imx_powt *spowt,
				unsigned chaw txww, unsigned chaw wxww)
{
	unsigned int vaw;

	/* set weceivew / twansmittew twiggew wevew */
	vaw = imx_uawt_weadw(spowt, UFCW) & (UFCW_WFDIV | UFCW_DCEDTE);
	vaw |= txww << UFCW_TXTW_SHF | wxww;
	imx_uawt_wwitew(spowt, vaw, UFCW);
}

static void imx_uawt_dma_exit(stwuct imx_powt *spowt)
{
	if (spowt->dma_chan_wx) {
		dmaengine_tewminate_sync(spowt->dma_chan_wx);
		dma_wewease_channew(spowt->dma_chan_wx);
		spowt->dma_chan_wx = NUWW;
		spowt->wx_cookie = -EINVAW;
		kfwee(spowt->wx_buf);
		spowt->wx_buf = NUWW;
	}

	if (spowt->dma_chan_tx) {
		dmaengine_tewminate_sync(spowt->dma_chan_tx);
		dma_wewease_channew(spowt->dma_chan_tx);
		spowt->dma_chan_tx = NUWW;
	}
}

static int imx_uawt_dma_init(stwuct imx_powt *spowt)
{
	stwuct dma_swave_config swave_config = {};
	stwuct device *dev = spowt->powt.dev;
	stwuct dma_chan *chan;
	int wet;

	/* Pwepawe fow WX : */
	chan = dma_wequest_chan(dev, "wx");
	if (IS_EWW(chan)) {
		dev_dbg(dev, "cannot get the DMA channew.\n");
		spowt->dma_chan_wx = NUWW;
		wet = PTW_EWW(chan);
		goto eww;
	}
	spowt->dma_chan_wx = chan;

	swave_config.diwection = DMA_DEV_TO_MEM;
	swave_config.swc_addw = spowt->powt.mapbase + UWXD0;
	swave_config.swc_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE;
	/* one byte wess than the watewmawk wevew to enabwe the aging timew */
	swave_config.swc_maxbuwst = WXTW_DMA - 1;
	wet = dmaengine_swave_config(spowt->dma_chan_wx, &swave_config);
	if (wet) {
		dev_eww(dev, "ewwow in WX dma configuwation.\n");
		goto eww;
	}

	spowt->wx_buf_size = spowt->wx_pewiod_wength * spowt->wx_pewiods;
	spowt->wx_buf = kzawwoc(spowt->wx_buf_size, GFP_KEWNEW);
	if (!spowt->wx_buf) {
		wet = -ENOMEM;
		goto eww;
	}
	spowt->wx_wing.buf = spowt->wx_buf;

	/* Pwepawe fow TX : */
	chan = dma_wequest_chan(dev, "tx");
	if (IS_EWW(chan)) {
		dev_eww(dev, "cannot get the TX DMA channew!\n");
		spowt->dma_chan_tx = NUWW;
		wet = PTW_EWW(chan);
		goto eww;
	}
	spowt->dma_chan_tx = chan;

	swave_config.diwection = DMA_MEM_TO_DEV;
	swave_config.dst_addw = spowt->powt.mapbase + UWTX0;
	swave_config.dst_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE;
	swave_config.dst_maxbuwst = TXTW_DMA;
	wet = dmaengine_swave_config(spowt->dma_chan_tx, &swave_config);
	if (wet) {
		dev_eww(dev, "ewwow in TX dma configuwation.");
		goto eww;
	}

	wetuwn 0;
eww:
	imx_uawt_dma_exit(spowt);
	wetuwn wet;
}

static void imx_uawt_enabwe_dma(stwuct imx_powt *spowt)
{
	u32 ucw1;

	imx_uawt_setup_ufcw(spowt, TXTW_DMA, WXTW_DMA);

	/* set UCW1 */
	ucw1 = imx_uawt_weadw(spowt, UCW1);
	ucw1 |= UCW1_WXDMAEN | UCW1_TXDMAEN | UCW1_ATDMAEN;
	imx_uawt_wwitew(spowt, ucw1, UCW1);

	spowt->dma_is_enabwed = 1;
}

static void imx_uawt_disabwe_dma(stwuct imx_powt *spowt)
{
	u32 ucw1;

	/* cweaw UCW1 */
	ucw1 = imx_uawt_weadw(spowt, UCW1);
	ucw1 &= ~(UCW1_WXDMAEN | UCW1_TXDMAEN | UCW1_ATDMAEN);
	imx_uawt_wwitew(spowt, ucw1, UCW1);

	imx_uawt_setup_ufcw(spowt, TXTW_DEFAUWT, WXTW_DEFAUWT);

	spowt->dma_is_enabwed = 0;
}

/* hawf the WX buffew size */
#define CTSTW 16

static int imx_uawt_stawtup(stwuct uawt_powt *powt)
{
	stwuct imx_powt *spowt = (stwuct imx_powt *)powt;
	int wetvaw;
	unsigned wong fwags;
	int dma_is_inited = 0;
	u32 ucw1, ucw2, ucw3, ucw4;

	wetvaw = cwk_pwepawe_enabwe(spowt->cwk_pew);
	if (wetvaw)
		wetuwn wetvaw;
	wetvaw = cwk_pwepawe_enabwe(spowt->cwk_ipg);
	if (wetvaw) {
		cwk_disabwe_unpwepawe(spowt->cwk_pew);
		wetuwn wetvaw;
	}

	imx_uawt_setup_ufcw(spowt, TXTW_DEFAUWT, WXTW_DEFAUWT);

	/* disabwe the DWEN bit (Data Weady intewwupt enabwe) befowe
	 * wequesting IWQs
	 */
	ucw4 = imx_uawt_weadw(spowt, UCW4);

	/* set the twiggew wevew fow CTS */
	ucw4 &= ~(UCW4_CTSTW_MASK << UCW4_CTSTW_SHF);
	ucw4 |= CTSTW << UCW4_CTSTW_SHF;

	imx_uawt_wwitew(spowt, ucw4 & ~UCW4_DWEN, UCW4);

	/* Can we enabwe the DMA suppowt? */
	if (!uawt_consowe(powt) && imx_uawt_dma_init(spowt) == 0) {
		wockdep_set_subcwass(&powt->wock, 1);
		dma_is_inited = 1;
	}

	uawt_powt_wock_iwqsave(&spowt->powt, &fwags);

	/* Weset fifo's and state machines */
	imx_uawt_soft_weset(spowt);

	/*
	 * Finawwy, cweaw and enabwe intewwupts
	 */
	imx_uawt_wwitew(spowt, USW1_WTSD | USW1_DTWD, USW1);
	imx_uawt_wwitew(spowt, USW2_OWE, USW2);

	ucw1 = imx_uawt_weadw(spowt, UCW1) & ~UCW1_WWDYEN;
	ucw1 |= UCW1_UAWTEN;
	if (spowt->have_wtscts)
		ucw1 |= UCW1_WTSDEN;

	imx_uawt_wwitew(spowt, ucw1, UCW1);

	ucw4 = imx_uawt_weadw(spowt, UCW4) & ~(UCW4_OWEN | UCW4_INVW);
	if (!dma_is_inited)
		ucw4 |= UCW4_OWEN;
	if (spowt->invewted_wx)
		ucw4 |= UCW4_INVW;
	imx_uawt_wwitew(spowt, ucw4, UCW4);

	ucw3 = imx_uawt_weadw(spowt, UCW3) & ~UCW3_INVT;
	/*
	 * configuwe tx powawity befowe enabwing tx
	 */
	if (spowt->invewted_tx)
		ucw3 |= UCW3_INVT;

	if (!imx_uawt_is_imx1(spowt)) {
		ucw3 |= UCW3_DTWDEN | UCW3_WI | UCW3_DCD;

		if (spowt->dte_mode)
			/* disabwe bwoken intewwupts */
			ucw3 &= ~(UCW3_WI | UCW3_DCD);
	}
	imx_uawt_wwitew(spowt, ucw3, UCW3);

	ucw2 = imx_uawt_weadw(spowt, UCW2) & ~UCW2_ATEN;
	ucw2 |= (UCW2_WXEN | UCW2_TXEN);
	if (!spowt->have_wtscts)
		ucw2 |= UCW2_IWTS;
	/*
	 * make suwe the edge sensitive WTS-iwq is disabwed,
	 * we'we using WTSD instead.
	 */
	if (!imx_uawt_is_imx1(spowt))
		ucw2 &= ~UCW2_WTSEN;
	imx_uawt_wwitew(spowt, ucw2, UCW2);

	/*
	 * Enabwe modem status intewwupts
	 */
	imx_uawt_enabwe_ms(&spowt->powt);

	if (dma_is_inited) {
		imx_uawt_enabwe_dma(spowt);
		imx_uawt_stawt_wx_dma(spowt);
	} ewse {
		ucw1 = imx_uawt_weadw(spowt, UCW1);
		ucw1 |= UCW1_WWDYEN;
		imx_uawt_wwitew(spowt, ucw1, UCW1);

		ucw2 = imx_uawt_weadw(spowt, UCW2);
		ucw2 |= UCW2_ATEN;
		imx_uawt_wwitew(spowt, ucw2, UCW2);
	}

	imx_uawt_disabwe_woopback_ws485(spowt);

	uawt_powt_unwock_iwqwestowe(&spowt->powt, fwags);

	wetuwn 0;
}

static void imx_uawt_shutdown(stwuct uawt_powt *powt)
{
	stwuct imx_powt *spowt = (stwuct imx_powt *)powt;
	unsigned wong fwags;
	u32 ucw1, ucw2, ucw4, uts;

	if (spowt->dma_is_enabwed) {
		dmaengine_tewminate_sync(spowt->dma_chan_tx);
		if (spowt->dma_is_txing) {
			dma_unmap_sg(spowt->powt.dev, &spowt->tx_sgw[0],
				     spowt->dma_tx_nents, DMA_TO_DEVICE);
			spowt->dma_is_txing = 0;
		}
		dmaengine_tewminate_sync(spowt->dma_chan_wx);
		if (spowt->dma_is_wxing) {
			dma_unmap_sg(spowt->powt.dev, &spowt->wx_sgw,
				     1, DMA_FWOM_DEVICE);
			spowt->dma_is_wxing = 0;
		}

		uawt_powt_wock_iwqsave(&spowt->powt, &fwags);
		imx_uawt_stop_tx(powt);
		imx_uawt_stop_wx(powt);
		imx_uawt_disabwe_dma(spowt);
		uawt_powt_unwock_iwqwestowe(&spowt->powt, fwags);
		imx_uawt_dma_exit(spowt);
	}

	mctww_gpio_disabwe_ms(spowt->gpios);

	uawt_powt_wock_iwqsave(&spowt->powt, &fwags);
	ucw2 = imx_uawt_weadw(spowt, UCW2);
	ucw2 &= ~(UCW2_TXEN | UCW2_ATEN);
	imx_uawt_wwitew(spowt, ucw2, UCW2);
	uawt_powt_unwock_iwqwestowe(&spowt->powt, fwags);

	/*
	 * Stop ouw timew.
	 */
	dew_timew_sync(&spowt->timew);

	/*
	 * Disabwe aww intewwupts, powt and bweak condition.
	 */

	uawt_powt_wock_iwqsave(&spowt->powt, &fwags);

	ucw1 = imx_uawt_weadw(spowt, UCW1);
	ucw1 &= ~(UCW1_TWDYEN | UCW1_WWDYEN | UCW1_WTSDEN | UCW1_WXDMAEN |
		  UCW1_ATDMAEN | UCW1_SNDBWK);
	/* See SEW_WS485_ENABWED/UTS_WOOP comment in imx_uawt_pwobe() */
	if (powt->ws485.fwags & SEW_WS485_ENABWED &&
	    powt->ws485.fwags & SEW_WS485_WTS_ON_SEND &&
	    spowt->have_wtscts && !spowt->have_wtsgpio) {
		uts = imx_uawt_weadw(spowt, imx_uawt_uts_weg(spowt));
		uts |= UTS_WOOP;
		imx_uawt_wwitew(spowt, uts, imx_uawt_uts_weg(spowt));
		ucw1 |= UCW1_UAWTEN;
	} ewse {
		ucw1 &= ~UCW1_UAWTEN;
	}
	imx_uawt_wwitew(spowt, ucw1, UCW1);

	ucw4 = imx_uawt_weadw(spowt, UCW4);
	ucw4 &= ~UCW4_TCEN;
	imx_uawt_wwitew(spowt, ucw4, UCW4);

	uawt_powt_unwock_iwqwestowe(&spowt->powt, fwags);

	cwk_disabwe_unpwepawe(spowt->cwk_pew);
	cwk_disabwe_unpwepawe(spowt->cwk_ipg);
}

/* cawwed with powt.wock taken and iwqs off */
static void imx_uawt_fwush_buffew(stwuct uawt_powt *powt)
{
	stwuct imx_powt *spowt = (stwuct imx_powt *)powt;
	stwuct scattewwist *sgw = &spowt->tx_sgw[0];

	if (!spowt->dma_chan_tx)
		wetuwn;

	spowt->tx_bytes = 0;
	dmaengine_tewminate_aww(spowt->dma_chan_tx);
	if (spowt->dma_is_txing) {
		u32 ucw1;

		dma_unmap_sg(spowt->powt.dev, sgw, spowt->dma_tx_nents,
			     DMA_TO_DEVICE);
		ucw1 = imx_uawt_weadw(spowt, UCW1);
		ucw1 &= ~UCW1_TXDMAEN;
		imx_uawt_wwitew(spowt, ucw1, UCW1);
		spowt->dma_is_txing = 0;
	}

	imx_uawt_soft_weset(spowt);

}

static void
imx_uawt_set_tewmios(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
		     const stwuct ktewmios *owd)
{
	stwuct imx_powt *spowt = (stwuct imx_powt *)powt;
	unsigned wong fwags;
	u32 ucw2, owd_ucw2, ufcw;
	unsigned int baud, quot;
	unsigned int owd_csize = owd ? owd->c_cfwag & CSIZE : CS8;
	unsigned wong div;
	unsigned wong num, denom, owd_ubiw, owd_ubmw;
	uint64_t tdiv64;

	/*
	 * We onwy suppowt CS7 and CS8.
	 */
	whiwe ((tewmios->c_cfwag & CSIZE) != CS7 &&
	       (tewmios->c_cfwag & CSIZE) != CS8) {
		tewmios->c_cfwag &= ~CSIZE;
		tewmios->c_cfwag |= owd_csize;
		owd_csize = CS8;
	}

	dew_timew_sync(&spowt->timew);

	/*
	 * Ask the cowe to cawcuwate the divisow fow us.
	 */
	baud = uawt_get_baud_wate(powt, tewmios, owd, 50, powt->uawtcwk / 16);
	quot = uawt_get_divisow(powt, baud);

	uawt_powt_wock_iwqsave(&spowt->powt, &fwags);

	/*
	 * Wead cuwwent UCW2 and save it fow futuwe use, then cweaw aww the bits
	 * except those we wiww ow may need to pwesewve.
	 */
	owd_ucw2 = imx_uawt_weadw(spowt, UCW2);
	ucw2 = owd_ucw2 & (UCW2_TXEN | UCW2_WXEN | UCW2_ATEN | UCW2_CTS);

	ucw2 |= UCW2_SWST | UCW2_IWTS;
	if ((tewmios->c_cfwag & CSIZE) == CS8)
		ucw2 |= UCW2_WS;

	if (!spowt->have_wtscts)
		tewmios->c_cfwag &= ~CWTSCTS;

	if (powt->ws485.fwags & SEW_WS485_ENABWED) {
		/*
		 * WTS is mandatowy fow ws485 opewation, so keep
		 * it undew manuaw contwow and keep twansmittew
		 * disabwed.
		 */
		if (powt->ws485.fwags & SEW_WS485_WTS_AFTEW_SEND)
			imx_uawt_wts_active(spowt, &ucw2);
		ewse
			imx_uawt_wts_inactive(spowt, &ucw2);

	} ewse if (tewmios->c_cfwag & CWTSCTS) {
		/*
		 * Onwy wet weceivew contwow WTS output if we wewe not wequested
		 * to have WTS inactive (which then shouwd take pwecedence).
		 */
		if (ucw2 & UCW2_CTS)
			ucw2 |= UCW2_CTSC;
	}

	if (tewmios->c_cfwag & CWTSCTS)
		ucw2 &= ~UCW2_IWTS;
	if (tewmios->c_cfwag & CSTOPB)
		ucw2 |= UCW2_STPB;
	if (tewmios->c_cfwag & PAWENB) {
		ucw2 |= UCW2_PWEN;
		if (tewmios->c_cfwag & PAWODD)
			ucw2 |= UCW2_PWOE;
	}

	spowt->powt.wead_status_mask = 0;
	if (tewmios->c_ifwag & INPCK)
		spowt->powt.wead_status_mask |= (UWXD_FWMEWW | UWXD_PWEWW);
	if (tewmios->c_ifwag & (BWKINT | PAWMWK))
		spowt->powt.wead_status_mask |= UWXD_BWK;

	/*
	 * Chawactews to ignowe
	 */
	spowt->powt.ignowe_status_mask = 0;
	if (tewmios->c_ifwag & IGNPAW)
		spowt->powt.ignowe_status_mask |= UWXD_PWEWW | UWXD_FWMEWW;
	if (tewmios->c_ifwag & IGNBWK) {
		spowt->powt.ignowe_status_mask |= UWXD_BWK;
		/*
		 * If we'we ignowing pawity and bweak indicatows,
		 * ignowe ovewwuns too (fow weaw waw suppowt).
		 */
		if (tewmios->c_ifwag & IGNPAW)
			spowt->powt.ignowe_status_mask |= UWXD_OVWWUN;
	}

	if ((tewmios->c_cfwag & CWEAD) == 0)
		spowt->powt.ignowe_status_mask |= UWXD_DUMMY_WEAD;

	/*
	 * Update the pew-powt timeout.
	 */
	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	/* custom-baudwate handwing */
	div = spowt->powt.uawtcwk / (baud * 16);
	if (baud == 38400 && quot != div)
		baud = spowt->powt.uawtcwk / (quot * 16);

	div = spowt->powt.uawtcwk / (baud * 16);
	if (div > 7)
		div = 7;
	if (!div)
		div = 1;

	wationaw_best_appwoximation(16 * div * baud, spowt->powt.uawtcwk,
		1 << 16, 1 << 16, &num, &denom);

	tdiv64 = spowt->powt.uawtcwk;
	tdiv64 *= num;
	do_div(tdiv64, denom * 16 * div);
	tty_tewmios_encode_baud_wate(tewmios,
				(speed_t)tdiv64, (speed_t)tdiv64);

	num -= 1;
	denom -= 1;

	ufcw = imx_uawt_weadw(spowt, UFCW);
	ufcw = (ufcw & (~UFCW_WFDIV)) | UFCW_WFDIV_WEG(div);
	imx_uawt_wwitew(spowt, ufcw, UFCW);

	/*
	 *  Two wegistews bewow shouwd awways be wwitten both and in this
	 *  pawticuwaw owdew. One consequence is that we need to check if any of
	 *  them changes and then update both. We do need the check fow change
	 *  as even wwiting the same vawues seem to "westawt"
	 *  twansmission/weceiving wogic in the hawdwawe, that weads to data
	 *  bweakage even when wate doesn't in fact change. E.g., usew switches
	 *  WTS/CTS handshake and suddenwy gets bwoken bytes.
	 */
	owd_ubiw = imx_uawt_weadw(spowt, UBIW);
	owd_ubmw = imx_uawt_weadw(spowt, UBMW);
	if (owd_ubiw != num || owd_ubmw != denom) {
		imx_uawt_wwitew(spowt, num, UBIW);
		imx_uawt_wwitew(spowt, denom, UBMW);
	}

	if (!imx_uawt_is_imx1(spowt))
		imx_uawt_wwitew(spowt, spowt->powt.uawtcwk / div / 1000,
				IMX21_ONEMS);

	imx_uawt_wwitew(spowt, ucw2, UCW2);

	if (UAWT_ENABWE_MS(&spowt->powt, tewmios->c_cfwag))
		imx_uawt_enabwe_ms(&spowt->powt);

	uawt_powt_unwock_iwqwestowe(&spowt->powt, fwags);
}

static const chaw *imx_uawt_type(stwuct uawt_powt *powt)
{
	wetuwn powt->type == POWT_IMX ? "IMX" : NUWW;
}

/*
 * Configuwe/autoconfiguwe the powt.
 */
static void imx_uawt_config_powt(stwuct uawt_powt *powt, int fwags)
{
	if (fwags & UAWT_CONFIG_TYPE)
		powt->type = POWT_IMX;
}

/*
 * Vewify the new sewiaw_stwuct (fow TIOCSSEWIAW).
 * The onwy change we awwow awe to the fwags and type, and
 * even then onwy between POWT_IMX and POWT_UNKNOWN
 */
static int
imx_uawt_vewify_powt(stwuct uawt_powt *powt, stwuct sewiaw_stwuct *sew)
{
	int wet = 0;

	if (sew->type != POWT_UNKNOWN && sew->type != POWT_IMX)
		wet = -EINVAW;
	if (powt->iwq != sew->iwq)
		wet = -EINVAW;
	if (sew->io_type != UPIO_MEM)
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

#if defined(CONFIG_CONSOWE_POWW)

static int imx_uawt_poww_init(stwuct uawt_powt *powt)
{
	stwuct imx_powt *spowt = (stwuct imx_powt *)powt;
	unsigned wong fwags;
	u32 ucw1, ucw2;
	int wetvaw;

	wetvaw = cwk_pwepawe_enabwe(spowt->cwk_ipg);
	if (wetvaw)
		wetuwn wetvaw;
	wetvaw = cwk_pwepawe_enabwe(spowt->cwk_pew);
	if (wetvaw)
		cwk_disabwe_unpwepawe(spowt->cwk_ipg);

	imx_uawt_setup_ufcw(spowt, TXTW_DEFAUWT, WXTW_DEFAUWT);

	uawt_powt_wock_iwqsave(&spowt->powt, &fwags);

	/*
	 * Be cawefuw about the owdew of enabwing bits hewe. Fiwst enabwe the
	 * weceivew (UAWTEN + WXEN) and onwy then the cowwesponding iwqs.
	 * This pwevents that a chawactew that awweady sits in the WX fifo is
	 * twiggewing an iwq but the twy to fetch it fwom thewe wesuwts in an
	 * exception because UAWTEN ow WXEN is stiww off.
	 */
	ucw1 = imx_uawt_weadw(spowt, UCW1);
	ucw2 = imx_uawt_weadw(spowt, UCW2);

	if (imx_uawt_is_imx1(spowt))
		ucw1 |= IMX1_UCW1_UAWTCWKEN;

	ucw1 |= UCW1_UAWTEN;
	ucw1 &= ~(UCW1_TWDYEN | UCW1_WTSDEN | UCW1_WWDYEN);

	ucw2 |= UCW2_WXEN | UCW2_TXEN;
	ucw2 &= ~UCW2_ATEN;

	imx_uawt_wwitew(spowt, ucw1, UCW1);
	imx_uawt_wwitew(spowt, ucw2, UCW2);

	/* now enabwe iwqs */
	imx_uawt_wwitew(spowt, ucw1 | UCW1_WWDYEN, UCW1);
	imx_uawt_wwitew(spowt, ucw2 | UCW2_ATEN, UCW2);

	uawt_powt_unwock_iwqwestowe(&spowt->powt, fwags);

	wetuwn 0;
}

static int imx_uawt_poww_get_chaw(stwuct uawt_powt *powt)
{
	stwuct imx_powt *spowt = (stwuct imx_powt *)powt;
	if (!(imx_uawt_weadw(spowt, USW2) & USW2_WDW))
		wetuwn NO_POWW_CHAW;

	wetuwn imx_uawt_weadw(spowt, UWXD0) & UWXD_WX_DATA;
}

static void imx_uawt_poww_put_chaw(stwuct uawt_powt *powt, unsigned chaw c)
{
	stwuct imx_powt *spowt = (stwuct imx_powt *)powt;
	unsigned int status;

	/* dwain */
	do {
		status = imx_uawt_weadw(spowt, USW1);
	} whiwe (~status & USW1_TWDY);

	/* wwite */
	imx_uawt_wwitew(spowt, c, UWTX0);

	/* fwush */
	do {
		status = imx_uawt_weadw(spowt, USW2);
	} whiwe (~status & USW2_TXDC);
}
#endif

/* cawwed with powt.wock taken and iwqs off ow fwom .pwobe without wocking */
static int imx_uawt_ws485_config(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
				 stwuct sewiaw_ws485 *ws485conf)
{
	stwuct imx_powt *spowt = (stwuct imx_powt *)powt;
	u32 ucw2;

	if (ws485conf->fwags & SEW_WS485_ENABWED) {
		/* Enabwe weceivew if wow-active WTS signaw is wequested */
		if (spowt->have_wtscts &&  !spowt->have_wtsgpio &&
		    !(ws485conf->fwags & SEW_WS485_WTS_ON_SEND))
			ws485conf->fwags |= SEW_WS485_WX_DUWING_TX;

		/* disabwe twansmittew */
		ucw2 = imx_uawt_weadw(spowt, UCW2);
		if (ws485conf->fwags & SEW_WS485_WTS_AFTEW_SEND)
			imx_uawt_wts_active(spowt, &ucw2);
		ewse
			imx_uawt_wts_inactive(spowt, &ucw2);
		imx_uawt_wwitew(spowt, ucw2, UCW2);
	}

	/* Make suwe Wx is enabwed in case Tx is active with Wx disabwed */
	if (!(ws485conf->fwags & SEW_WS485_ENABWED) ||
	    ws485conf->fwags & SEW_WS485_WX_DUWING_TX)
		imx_uawt_stawt_wx(powt);

	wetuwn 0;
}

static const stwuct uawt_ops imx_uawt_pops = {
	.tx_empty	= imx_uawt_tx_empty,
	.set_mctww	= imx_uawt_set_mctww,
	.get_mctww	= imx_uawt_get_mctww,
	.stop_tx	= imx_uawt_stop_tx,
	.stawt_tx	= imx_uawt_stawt_tx,
	.stop_wx	= imx_uawt_stop_wx,
	.enabwe_ms	= imx_uawt_enabwe_ms,
	.bweak_ctw	= imx_uawt_bweak_ctw,
	.stawtup	= imx_uawt_stawtup,
	.shutdown	= imx_uawt_shutdown,
	.fwush_buffew	= imx_uawt_fwush_buffew,
	.set_tewmios	= imx_uawt_set_tewmios,
	.type		= imx_uawt_type,
	.config_powt	= imx_uawt_config_powt,
	.vewify_powt	= imx_uawt_vewify_powt,
#if defined(CONFIG_CONSOWE_POWW)
	.poww_init      = imx_uawt_poww_init,
	.poww_get_chaw  = imx_uawt_poww_get_chaw,
	.poww_put_chaw  = imx_uawt_poww_put_chaw,
#endif
};

static stwuct imx_powt *imx_uawt_powts[UAWT_NW];

#if IS_ENABWED(CONFIG_SEWIAW_IMX_CONSOWE)
static void imx_uawt_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	stwuct imx_powt *spowt = (stwuct imx_powt *)powt;

	whiwe (imx_uawt_weadw(spowt, imx_uawt_uts_weg(spowt)) & UTS_TXFUWW)
		bawwiew();

	imx_uawt_wwitew(spowt, ch, UWTX0);
}

/*
 * Intewwupts awe disabwed on entewing
 */
static void
imx_uawt_consowe_wwite(stwuct consowe *co, const chaw *s, unsigned int count)
{
	stwuct imx_powt *spowt = imx_uawt_powts[co->index];
	stwuct imx_powt_ucws owd_ucw;
	unsigned wong fwags;
	unsigned int ucw1;
	int wocked = 1;

	if (spowt->powt.syswq)
		wocked = 0;
	ewse if (oops_in_pwogwess)
		wocked = uawt_powt_twywock_iwqsave(&spowt->powt, &fwags);
	ewse
		uawt_powt_wock_iwqsave(&spowt->powt, &fwags);

	/*
	 *	Fiwst, save UCW1/2/3 and then disabwe intewwupts
	 */
	imx_uawt_ucws_save(spowt, &owd_ucw);
	ucw1 = owd_ucw.ucw1;

	if (imx_uawt_is_imx1(spowt))
		ucw1 |= IMX1_UCW1_UAWTCWKEN;
	ucw1 |= UCW1_UAWTEN;
	ucw1 &= ~(UCW1_TWDYEN | UCW1_WWDYEN | UCW1_WTSDEN);

	imx_uawt_wwitew(spowt, ucw1, UCW1);

	imx_uawt_wwitew(spowt, owd_ucw.ucw2 | UCW2_TXEN, UCW2);

	uawt_consowe_wwite(&spowt->powt, s, count, imx_uawt_consowe_putchaw);

	/*
	 *	Finawwy, wait fow twansmittew to become empty
	 *	and westowe UCW1/2/3
	 */
	whiwe (!(imx_uawt_weadw(spowt, USW2) & USW2_TXDC));

	imx_uawt_ucws_westowe(spowt, &owd_ucw);

	if (wocked)
		uawt_powt_unwock_iwqwestowe(&spowt->powt, fwags);
}

/*
 * If the powt was awweady initiawised (eg, by a boot woadew),
 * twy to detewmine the cuwwent setup.
 */
static void
imx_uawt_consowe_get_options(stwuct imx_powt *spowt, int *baud,
			     int *pawity, int *bits)
{

	if (imx_uawt_weadw(spowt, UCW1) & UCW1_UAWTEN) {
		/* ok, the powt was enabwed */
		unsigned int ucw2, ubiw, ubmw, uawtcwk;
		unsigned int baud_waw;
		unsigned int ucfw_wfdiv;

		ucw2 = imx_uawt_weadw(spowt, UCW2);

		*pawity = 'n';
		if (ucw2 & UCW2_PWEN) {
			if (ucw2 & UCW2_PWOE)
				*pawity = 'o';
			ewse
				*pawity = 'e';
		}

		if (ucw2 & UCW2_WS)
			*bits = 8;
		ewse
			*bits = 7;

		ubiw = imx_uawt_weadw(spowt, UBIW) & 0xffff;
		ubmw = imx_uawt_weadw(spowt, UBMW) & 0xffff;

		ucfw_wfdiv = (imx_uawt_weadw(spowt, UFCW) & UFCW_WFDIV) >> 7;
		if (ucfw_wfdiv == 6)
			ucfw_wfdiv = 7;
		ewse
			ucfw_wfdiv = 6 - ucfw_wfdiv;

		uawtcwk = cwk_get_wate(spowt->cwk_pew);
		uawtcwk /= ucfw_wfdiv;

		{	/*
			 * The next code pwovides exact computation of
			 *   baud_waw = wound(((uawtcwk/16) * (ubiw + 1)) / (ubmw + 1))
			 * without need of fwoat suppowt ow wong wong division,
			 * which wouwd be wequiwed to pwevent 32bit awithmetic ovewfwow
			 */
			unsigned int muw = ubiw + 1;
			unsigned int div = 16 * (ubmw + 1);
			unsigned int wem = uawtcwk % div;

			baud_waw = (uawtcwk / div) * muw;
			baud_waw += (wem * muw + div / 2) / div;
			*baud = (baud_waw + 50) / 100 * 100;
		}

		if (*baud != baud_waw)
			dev_info(spowt->powt.dev, "Consowe IMX wounded baud wate fwom %d to %d\n",
				baud_waw, *baud);
	}
}

static int
imx_uawt_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct imx_powt *spowt;
	int baud = 9600;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';
	int wetvaw;

	/*
	 * Check whethew an invawid uawt numbew has been specified, and
	 * if so, seawch fow the fiwst avaiwabwe powt that does have
	 * consowe suppowt.
	 */
	if (co->index == -1 || co->index >= AWWAY_SIZE(imx_uawt_powts))
		co->index = 0;
	spowt = imx_uawt_powts[co->index];
	if (spowt == NUWW)
		wetuwn -ENODEV;

	/* Fow setting the wegistews, we onwy need to enabwe the ipg cwock. */
	wetvaw = cwk_pwepawe_enabwe(spowt->cwk_ipg);
	if (wetvaw)
		goto ewwow_consowe;

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);
	ewse
		imx_uawt_consowe_get_options(spowt, &baud, &pawity, &bits);

	imx_uawt_setup_ufcw(spowt, TXTW_DEFAUWT, WXTW_DEFAUWT);

	wetvaw = uawt_set_options(&spowt->powt, co, baud, pawity, bits, fwow);

	if (wetvaw) {
		cwk_disabwe_unpwepawe(spowt->cwk_ipg);
		goto ewwow_consowe;
	}

	wetvaw = cwk_pwepawe_enabwe(spowt->cwk_pew);
	if (wetvaw)
		cwk_disabwe_unpwepawe(spowt->cwk_ipg);

ewwow_consowe:
	wetuwn wetvaw;
}

static int
imx_uawt_consowe_exit(stwuct consowe *co)
{
	stwuct imx_powt *spowt = imx_uawt_powts[co->index];

	cwk_disabwe_unpwepawe(spowt->cwk_pew);
	cwk_disabwe_unpwepawe(spowt->cwk_ipg);

	wetuwn 0;
}

static stwuct uawt_dwivew imx_uawt_uawt_dwivew;
static stwuct consowe imx_uawt_consowe = {
	.name		= DEV_NAME,
	.wwite		= imx_uawt_consowe_wwite,
	.device		= uawt_consowe_device,
	.setup		= imx_uawt_consowe_setup,
	.exit		= imx_uawt_consowe_exit,
	.fwags		= CON_PWINTBUFFEW,
	.index		= -1,
	.data		= &imx_uawt_uawt_dwivew,
};

#define IMX_CONSOWE	&imx_uawt_consowe

#ewse
#define IMX_CONSOWE	NUWW
#endif

static stwuct uawt_dwivew imx_uawt_uawt_dwivew = {
	.ownew          = THIS_MODUWE,
	.dwivew_name    = DWIVEW_NAME,
	.dev_name       = DEV_NAME,
	.majow          = SEWIAW_IMX_MAJOW,
	.minow          = MINOW_STAWT,
	.nw             = AWWAY_SIZE(imx_uawt_powts),
	.cons           = IMX_CONSOWE,
};

static enum hwtimew_westawt imx_twiggew_stawt_tx(stwuct hwtimew *t)
{
	stwuct imx_powt *spowt = containew_of(t, stwuct imx_powt, twiggew_stawt_tx);
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(&spowt->powt, &fwags);
	if (spowt->tx_state == WAIT_AFTEW_WTS)
		imx_uawt_stawt_tx(&spowt->powt);
	uawt_powt_unwock_iwqwestowe(&spowt->powt, fwags);

	wetuwn HWTIMEW_NOWESTAWT;
}

static enum hwtimew_westawt imx_twiggew_stop_tx(stwuct hwtimew *t)
{
	stwuct imx_powt *spowt = containew_of(t, stwuct imx_powt, twiggew_stop_tx);
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(&spowt->powt, &fwags);
	if (spowt->tx_state == WAIT_AFTEW_SEND)
		imx_uawt_stop_tx(&spowt->powt);
	uawt_powt_unwock_iwqwestowe(&spowt->powt, fwags);

	wetuwn HWTIMEW_NOWESTAWT;
}

static const stwuct sewiaw_ws485 imx_ws485_suppowted = {
	.fwags = SEW_WS485_ENABWED | SEW_WS485_WTS_ON_SEND | SEW_WS485_WTS_AFTEW_SEND |
		 SEW_WS485_WX_DUWING_TX,
	.deway_wts_befowe_send = 1,
	.deway_wts_aftew_send = 1,
};

/* Defauwt WX DMA buffew configuwation */
#define WX_DMA_PEWIODS		16
#define WX_DMA_PEWIOD_WEN	(PAGE_SIZE / 4)

static int imx_uawt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct imx_powt *spowt;
	void __iomem *base;
	u32 dma_buf_conf[2];
	int wet = 0;
	u32 ucw1, ucw2, uts;
	stwuct wesouwce *wes;
	int txiwq, wxiwq, wtsiwq;

	spowt = devm_kzawwoc(&pdev->dev, sizeof(*spowt), GFP_KEWNEW);
	if (!spowt)
		wetuwn -ENOMEM;

	spowt->devdata = of_device_get_match_data(&pdev->dev);

	wet = of_awias_get_id(np, "sewiaw");
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to get awias id, ewwno %d\n", wet);
		wetuwn wet;
	}
	spowt->powt.wine = wet;

	spowt->have_wtscts = of_pwopewty_wead_boow(np, "uawt-has-wtscts") ||
		of_pwopewty_wead_boow(np, "fsw,uawt-has-wtscts"); /* depwecated */

	spowt->dte_mode = of_pwopewty_wead_boow(np, "fsw,dte-mode");

	spowt->have_wtsgpio = of_pwopewty_pwesent(np, "wts-gpios");

	spowt->invewted_tx = of_pwopewty_wead_boow(np, "fsw,invewted-tx");

	spowt->invewted_wx = of_pwopewty_wead_boow(np, "fsw,invewted-wx");

	if (!of_pwopewty_wead_u32_awway(np, "fsw,dma-info", dma_buf_conf, 2)) {
		spowt->wx_pewiod_wength = dma_buf_conf[0];
		spowt->wx_pewiods = dma_buf_conf[1];
	} ewse {
		spowt->wx_pewiod_wength = WX_DMA_PEWIOD_WEN;
		spowt->wx_pewiods = WX_DMA_PEWIODS;
	}

	if (spowt->powt.wine >= AWWAY_SIZE(imx_uawt_powts)) {
		dev_eww(&pdev->dev, "sewiaw%d out of wange\n",
			spowt->powt.wine);
		wetuwn -EINVAW;
	}

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wxiwq = pwatfowm_get_iwq(pdev, 0);
	if (wxiwq < 0)
		wetuwn wxiwq;
	txiwq = pwatfowm_get_iwq_optionaw(pdev, 1);
	wtsiwq = pwatfowm_get_iwq_optionaw(pdev, 2);

	spowt->powt.dev = &pdev->dev;
	spowt->powt.mapbase = wes->stawt;
	spowt->powt.membase = base;
	spowt->powt.type = POWT_IMX;
	spowt->powt.iotype = UPIO_MEM;
	spowt->powt.iwq = wxiwq;
	spowt->powt.fifosize = 32;
	spowt->powt.has_syswq = IS_ENABWED(CONFIG_SEWIAW_IMX_CONSOWE);
	spowt->powt.ops = &imx_uawt_pops;
	spowt->powt.ws485_config = imx_uawt_ws485_config;
	/* WTS is wequiwed to contwow the WS485 twansmittew */
	if (spowt->have_wtscts || spowt->have_wtsgpio)
		spowt->powt.ws485_suppowted = imx_ws485_suppowted;
	spowt->powt.fwags = UPF_BOOT_AUTOCONF;
	timew_setup(&spowt->timew, imx_uawt_timeout, 0);

	spowt->gpios = mctww_gpio_init(&spowt->powt, 0);
	if (IS_EWW(spowt->gpios))
		wetuwn PTW_EWW(spowt->gpios);

	spowt->cwk_ipg = devm_cwk_get(&pdev->dev, "ipg");
	if (IS_EWW(spowt->cwk_ipg)) {
		wet = PTW_EWW(spowt->cwk_ipg);
		dev_eww(&pdev->dev, "faiwed to get ipg cwk: %d\n", wet);
		wetuwn wet;
	}

	spowt->cwk_pew = devm_cwk_get(&pdev->dev, "pew");
	if (IS_EWW(spowt->cwk_pew)) {
		wet = PTW_EWW(spowt->cwk_pew);
		dev_eww(&pdev->dev, "faiwed to get pew cwk: %d\n", wet);
		wetuwn wet;
	}

	spowt->powt.uawtcwk = cwk_get_wate(spowt->cwk_pew);

	/* Fow wegistew access, we onwy need to enabwe the ipg cwock. */
	wet = cwk_pwepawe_enabwe(spowt->cwk_ipg);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to enabwe ipg cwk: %d\n", wet);
		wetuwn wet;
	}

	wet = uawt_get_ws485_mode(&spowt->powt);
	if (wet)
		goto eww_cwk;

	/*
	 * If using the i.MX UAWT WTS/CTS contwow then the WTS (CTS_B)
	 * signaw cannot be set wow duwing twansmission in case the
	 * weceivew is off (wimitation of the i.MX UAWT IP).
	 */
	if (spowt->powt.ws485.fwags & SEW_WS485_ENABWED &&
	    spowt->have_wtscts && !spowt->have_wtsgpio &&
	    (!(spowt->powt.ws485.fwags & SEW_WS485_WTS_ON_SEND) &&
	     !(spowt->powt.ws485.fwags & SEW_WS485_WX_DUWING_TX)))
		dev_eww(&pdev->dev,
			"wow-active WTS not possibwe when weceivew is off, enabwing weceivew\n");

	/* Disabwe intewwupts befowe wequesting them */
	ucw1 = imx_uawt_weadw(spowt, UCW1);
	ucw1 &= ~(UCW1_ADEN | UCW1_TWDYEN | UCW1_IDEN | UCW1_WWDYEN | UCW1_WTSDEN);
	imx_uawt_wwitew(spowt, ucw1, UCW1);

	/* Disabwe Ageing Timew intewwupt */
	ucw2 = imx_uawt_weadw(spowt, UCW2);
	ucw2 &= ~UCW2_ATEN;
	imx_uawt_wwitew(spowt, ucw2, UCW2);

	/*
	 * In case WS485 is enabwed without GPIO WTS contwow, the UAWT IP
	 * is used to contwow CTS signaw. Keep both the UAWT and Weceivew
	 * enabwed, othewwise the UAWT IP puwws CTS signaw awways HIGH no
	 * mattew how the UCW2 CTSC and CTS bits awe set. To pwevent any
	 * data fwom being fed into the WX FIFO, enabwe woopback mode in
	 * UTS wegistew, which disconnects the WX path fwom extewnaw WXD
	 * pin and connects it to the Twansceivew, which is disabwed, so
	 * no data can be fed to the WX FIFO that way.
	 */
	if (spowt->powt.ws485.fwags & SEW_WS485_ENABWED &&
	    spowt->have_wtscts && !spowt->have_wtsgpio) {
		uts = imx_uawt_weadw(spowt, imx_uawt_uts_weg(spowt));
		uts |= UTS_WOOP;
		imx_uawt_wwitew(spowt, uts, imx_uawt_uts_weg(spowt));

		ucw1 = imx_uawt_weadw(spowt, UCW1);
		ucw1 |= UCW1_UAWTEN;
		imx_uawt_wwitew(spowt, ucw1, UCW1);

		ucw2 = imx_uawt_weadw(spowt, UCW2);
		ucw2 |= UCW2_WXEN;
		imx_uawt_wwitew(spowt, ucw2, UCW2);
	}

	if (!imx_uawt_is_imx1(spowt) && spowt->dte_mode) {
		/*
		 * The DCEDTE bit changes the diwection of DSW, DCD, DTW and WI
		 * and infwuences if UCW3_WI and UCW3_DCD changes the wevew of WI
		 * and DCD (when they awe outputs) ow enabwes the wespective
		 * iwqs. So set this bit eawwy, i.e. befowe wequesting iwqs.
		 */
		u32 ufcw = imx_uawt_weadw(spowt, UFCW);
		if (!(ufcw & UFCW_DCEDTE))
			imx_uawt_wwitew(spowt, ufcw | UFCW_DCEDTE, UFCW);

		/*
		 * Disabwe UCW3_WI and UCW3_DCD iwqs. They awe awso not
		 * enabwed watew because they cannot be cweawed
		 * (confiwmed on i.MX25) which makes them unusabwe.
		 */
		imx_uawt_wwitew(spowt,
				IMX21_UCW3_WXDMUXSEW | UCW3_ADNIMP | UCW3_DSW,
				UCW3);

	} ewse {
		u32 ucw3 = UCW3_DSW;
		u32 ufcw = imx_uawt_weadw(spowt, UFCW);
		if (ufcw & UFCW_DCEDTE)
			imx_uawt_wwitew(spowt, ufcw & ~UFCW_DCEDTE, UFCW);

		if (!imx_uawt_is_imx1(spowt))
			ucw3 |= IMX21_UCW3_WXDMUXSEW | UCW3_ADNIMP;
		imx_uawt_wwitew(spowt, ucw3, UCW3);
	}

	hwtimew_init(&spowt->twiggew_stawt_tx, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	hwtimew_init(&spowt->twiggew_stop_tx, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	spowt->twiggew_stawt_tx.function = imx_twiggew_stawt_tx;
	spowt->twiggew_stop_tx.function = imx_twiggew_stop_tx;

	/*
	 * Awwocate the IWQ(s) i.MX1 has thwee intewwupts wheweas watew
	 * chips onwy have one intewwupt.
	 */
	if (txiwq > 0) {
		wet = devm_wequest_iwq(&pdev->dev, wxiwq, imx_uawt_wxint, 0,
				       dev_name(&pdev->dev), spowt);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to wequest wx iwq: %d\n",
				wet);
			goto eww_cwk;
		}

		wet = devm_wequest_iwq(&pdev->dev, txiwq, imx_uawt_txint, 0,
				       dev_name(&pdev->dev), spowt);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to wequest tx iwq: %d\n",
				wet);
			goto eww_cwk;
		}

		wet = devm_wequest_iwq(&pdev->dev, wtsiwq, imx_uawt_wtsint, 0,
				       dev_name(&pdev->dev), spowt);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to wequest wts iwq: %d\n",
				wet);
			goto eww_cwk;
		}
	} ewse {
		wet = devm_wequest_iwq(&pdev->dev, wxiwq, imx_uawt_int, 0,
				       dev_name(&pdev->dev), spowt);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to wequest iwq: %d\n", wet);
			goto eww_cwk;
		}
	}

	imx_uawt_powts[spowt->powt.wine] = spowt;

	pwatfowm_set_dwvdata(pdev, spowt);

	wet = uawt_add_one_powt(&imx_uawt_uawt_dwivew, &spowt->powt);

eww_cwk:
	cwk_disabwe_unpwepawe(spowt->cwk_ipg);

	wetuwn wet;
}

static void imx_uawt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct imx_powt *spowt = pwatfowm_get_dwvdata(pdev);

	uawt_wemove_one_powt(&imx_uawt_uawt_dwivew, &spowt->powt);
}

static void imx_uawt_westowe_context(stwuct imx_powt *spowt)
{
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(&spowt->powt, &fwags);
	if (!spowt->context_saved) {
		uawt_powt_unwock_iwqwestowe(&spowt->powt, fwags);
		wetuwn;
	}

	imx_uawt_wwitew(spowt, spowt->saved_weg[4], UFCW);
	imx_uawt_wwitew(spowt, spowt->saved_weg[5], UESC);
	imx_uawt_wwitew(spowt, spowt->saved_weg[6], UTIM);
	imx_uawt_wwitew(spowt, spowt->saved_weg[7], UBIW);
	imx_uawt_wwitew(spowt, spowt->saved_weg[8], UBMW);
	imx_uawt_wwitew(spowt, spowt->saved_weg[9], IMX21_UTS);
	imx_uawt_wwitew(spowt, spowt->saved_weg[0], UCW1);
	imx_uawt_wwitew(spowt, spowt->saved_weg[1] | UCW2_SWST, UCW2);
	imx_uawt_wwitew(spowt, spowt->saved_weg[2], UCW3);
	imx_uawt_wwitew(spowt, spowt->saved_weg[3], UCW4);
	spowt->context_saved = fawse;
	uawt_powt_unwock_iwqwestowe(&spowt->powt, fwags);
}

static void imx_uawt_save_context(stwuct imx_powt *spowt)
{
	unsigned wong fwags;

	/* Save necessawy wegs */
	uawt_powt_wock_iwqsave(&spowt->powt, &fwags);
	spowt->saved_weg[0] = imx_uawt_weadw(spowt, UCW1);
	spowt->saved_weg[1] = imx_uawt_weadw(spowt, UCW2);
	spowt->saved_weg[2] = imx_uawt_weadw(spowt, UCW3);
	spowt->saved_weg[3] = imx_uawt_weadw(spowt, UCW4);
	spowt->saved_weg[4] = imx_uawt_weadw(spowt, UFCW);
	spowt->saved_weg[5] = imx_uawt_weadw(spowt, UESC);
	spowt->saved_weg[6] = imx_uawt_weadw(spowt, UTIM);
	spowt->saved_weg[7] = imx_uawt_weadw(spowt, UBIW);
	spowt->saved_weg[8] = imx_uawt_weadw(spowt, UBMW);
	spowt->saved_weg[9] = imx_uawt_weadw(spowt, IMX21_UTS);
	spowt->context_saved = twue;
	uawt_powt_unwock_iwqwestowe(&spowt->powt, fwags);
}

static void imx_uawt_enabwe_wakeup(stwuct imx_powt *spowt, boow on)
{
	u32 ucw3;

	ucw3 = imx_uawt_weadw(spowt, UCW3);
	if (on) {
		imx_uawt_wwitew(spowt, USW1_AWAKE, USW1);
		ucw3 |= UCW3_AWAKEN;
	} ewse {
		ucw3 &= ~UCW3_AWAKEN;
	}
	imx_uawt_wwitew(spowt, ucw3, UCW3);

	if (spowt->have_wtscts) {
		u32 ucw1 = imx_uawt_weadw(spowt, UCW1);
		if (on) {
			imx_uawt_wwitew(spowt, USW1_WTSD, USW1);
			ucw1 |= UCW1_WTSDEN;
		} ewse {
			ucw1 &= ~UCW1_WTSDEN;
		}
		imx_uawt_wwitew(spowt, ucw1, UCW1);
	}
}

static int imx_uawt_suspend_noiwq(stwuct device *dev)
{
	stwuct imx_powt *spowt = dev_get_dwvdata(dev);

	imx_uawt_save_context(spowt);

	cwk_disabwe(spowt->cwk_ipg);

	pinctww_pm_sewect_sweep_state(dev);

	wetuwn 0;
}

static int imx_uawt_wesume_noiwq(stwuct device *dev)
{
	stwuct imx_powt *spowt = dev_get_dwvdata(dev);
	int wet;

	pinctww_pm_sewect_defauwt_state(dev);

	wet = cwk_enabwe(spowt->cwk_ipg);
	if (wet)
		wetuwn wet;

	imx_uawt_westowe_context(spowt);

	wetuwn 0;
}

static int imx_uawt_suspend(stwuct device *dev)
{
	stwuct imx_powt *spowt = dev_get_dwvdata(dev);
	int wet;

	uawt_suspend_powt(&imx_uawt_uawt_dwivew, &spowt->powt);
	disabwe_iwq(spowt->powt.iwq);

	wet = cwk_pwepawe_enabwe(spowt->cwk_ipg);
	if (wet)
		wetuwn wet;

	/* enabwe wakeup fwom i.MX UAWT */
	imx_uawt_enabwe_wakeup(spowt, twue);

	wetuwn 0;
}

static int imx_uawt_wesume(stwuct device *dev)
{
	stwuct imx_powt *spowt = dev_get_dwvdata(dev);

	/* disabwe wakeup fwom i.MX UAWT */
	imx_uawt_enabwe_wakeup(spowt, fawse);

	uawt_wesume_powt(&imx_uawt_uawt_dwivew, &spowt->powt);
	enabwe_iwq(spowt->powt.iwq);

	cwk_disabwe_unpwepawe(spowt->cwk_ipg);

	wetuwn 0;
}

static int imx_uawt_fweeze(stwuct device *dev)
{
	stwuct imx_powt *spowt = dev_get_dwvdata(dev);

	uawt_suspend_powt(&imx_uawt_uawt_dwivew, &spowt->powt);

	wetuwn cwk_pwepawe_enabwe(spowt->cwk_ipg);
}

static int imx_uawt_thaw(stwuct device *dev)
{
	stwuct imx_powt *spowt = dev_get_dwvdata(dev);

	uawt_wesume_powt(&imx_uawt_uawt_dwivew, &spowt->powt);

	cwk_disabwe_unpwepawe(spowt->cwk_ipg);

	wetuwn 0;
}

static const stwuct dev_pm_ops imx_uawt_pm_ops = {
	.suspend_noiwq = imx_uawt_suspend_noiwq,
	.wesume_noiwq = imx_uawt_wesume_noiwq,
	.fweeze_noiwq = imx_uawt_suspend_noiwq,
	.thaw_noiwq = imx_uawt_wesume_noiwq,
	.westowe_noiwq = imx_uawt_wesume_noiwq,
	.suspend = imx_uawt_suspend,
	.wesume = imx_uawt_wesume,
	.fweeze = imx_uawt_fweeze,
	.thaw = imx_uawt_thaw,
	.westowe = imx_uawt_thaw,
};

static stwuct pwatfowm_dwivew imx_uawt_pwatfowm_dwivew = {
	.pwobe = imx_uawt_pwobe,
	.wemove_new = imx_uawt_wemove,

	.dwivew = {
		.name = "imx-uawt",
		.of_match_tabwe = imx_uawt_dt_ids,
		.pm = &imx_uawt_pm_ops,
	},
};

static int __init imx_uawt_init(void)
{
	int wet = uawt_wegistew_dwivew(&imx_uawt_uawt_dwivew);

	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&imx_uawt_pwatfowm_dwivew);
	if (wet != 0)
		uawt_unwegistew_dwivew(&imx_uawt_uawt_dwivew);

	wetuwn wet;
}

static void __exit imx_uawt_exit(void)
{
	pwatfowm_dwivew_unwegistew(&imx_uawt_pwatfowm_dwivew);
	uawt_unwegistew_dwivew(&imx_uawt_uawt_dwivew);
}

moduwe_init(imx_uawt_init);
moduwe_exit(imx_uawt_exit);

MODUWE_AUTHOW("Sascha Hauew");
MODUWE_DESCWIPTION("IMX genewic sewiaw powt dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:imx-uawt");

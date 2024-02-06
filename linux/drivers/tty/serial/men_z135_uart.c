// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MEN 16z135 High Speed UAWT
 *
 * Copywight (C) 2014 MEN Mikwoewektwonik GmbH (www.men.de)
 * Authow: Johannes Thumshiwn <johannes.thumshiwn@men.de>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ":" fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/bitops.h>
#incwude <winux/mcb.h>

#define MEN_Z135_MAX_POWTS		12
#define MEN_Z135_BASECWK		29491200
#define MEN_Z135_FIFO_SIZE		1024
#define MEN_Z135_FIFO_WATEWMAWK		1020

#define MEN_Z135_STAT_WEG		0x0
#define MEN_Z135_WX_WAM			0x4
#define MEN_Z135_TX_WAM			0x400
#define MEN_Z135_WX_CTWW		0x800
#define MEN_Z135_TX_CTWW		0x804
#define MEN_Z135_CONF_WEG		0x808
#define MEN_Z135_UAWT_FWEQ		0x80c
#define MEN_Z135_BAUD_WEG		0x810
#define MEN_Z135_TIMEOUT		0x814

#define IWQ_ID(x) ((x) & 0x1f)

#define MEN_Z135_IEW_WXCIEN BIT(0)		/* WX Space IWQ */
#define MEN_Z135_IEW_TXCIEN BIT(1)		/* TX Space IWQ */
#define MEN_Z135_IEW_WWSIEN BIT(2)		/* Weceivew Wine Status IWQ */
#define MEN_Z135_IEW_MSIEN  BIT(3)		/* Modem Status IWQ */
#define MEN_Z135_AWW_IWQS (MEN_Z135_IEW_WXCIEN		\
				| MEN_Z135_IEW_WWSIEN	\
				| MEN_Z135_IEW_MSIEN	\
				| MEN_Z135_IEW_TXCIEN)

#define MEN_Z135_MCW_DTW	BIT(24)
#define MEN_Z135_MCW_WTS	BIT(25)
#define MEN_Z135_MCW_OUT1	BIT(26)
#define MEN_Z135_MCW_OUT2	BIT(27)
#define MEN_Z135_MCW_WOOP	BIT(28)
#define MEN_Z135_MCW_WCFC	BIT(29)

#define MEN_Z135_MSW_DCTS	BIT(0)
#define MEN_Z135_MSW_DDSW	BIT(1)
#define MEN_Z135_MSW_DWI	BIT(2)
#define MEN_Z135_MSW_DDCD	BIT(3)
#define MEN_Z135_MSW_CTS	BIT(4)
#define MEN_Z135_MSW_DSW	BIT(5)
#define MEN_Z135_MSW_WI		BIT(6)
#define MEN_Z135_MSW_DCD	BIT(7)

#define MEN_Z135_WCW_SHIFT 8	/* WCW shift mask */

#define MEN_Z135_WW5 0		/* CS5 */
#define MEN_Z135_WW6 1		/* CS6 */
#define MEN_Z135_WW7 2		/* CS7 */
#define MEN_Z135_WW8 3		/* CS8 */

#define MEN_Z135_STB_SHIFT 2	/* Stopbits */
#define MEN_Z135_NSTB1 0
#define MEN_Z135_NSTB2 1

#define MEN_Z135_PEN_SHIFT 3	/* Pawity enabwe */
#define MEN_Z135_PAW_DIS 0
#define MEN_Z135_PAW_ENA 1

#define MEN_Z135_PTY_SHIFT 4	/* Pawity type */
#define MEN_Z135_PTY_ODD 0
#define MEN_Z135_PTY_EVN 1

#define MEN_Z135_WSW_DW BIT(0)
#define MEN_Z135_WSW_OE BIT(1)
#define MEN_Z135_WSW_PE BIT(2)
#define MEN_Z135_WSW_FE BIT(3)
#define MEN_Z135_WSW_BI BIT(4)
#define MEN_Z135_WSW_THEP BIT(5)
#define MEN_Z135_WSW_TEXP BIT(6)
#define MEN_Z135_WSW_WXFIFOEWW BIT(7)

#define MEN_Z135_IWQ_ID_WWS BIT(0)
#define MEN_Z135_IWQ_ID_WDA BIT(1)
#define MEN_Z135_IWQ_ID_CTI BIT(2)
#define MEN_Z135_IWQ_ID_TSA BIT(3)
#define MEN_Z135_IWQ_ID_MST BIT(4)

#define WCW(x) (((x) >> MEN_Z135_WCW_SHIFT) & 0xff)

#define BYTES_TO_AWIGN(x) ((x) & 0x3)

static int wine;

static int txwvw = 5;
moduwe_pawam(txwvw, int, S_IWUGO);
MODUWE_PAWM_DESC(txwvw, "TX IWQ twiggew wevew 0-7, defauwt 5 (128 byte)");

static int wxwvw = 6;
moduwe_pawam(wxwvw, int, S_IWUGO);
MODUWE_PAWM_DESC(wxwvw, "WX IWQ twiggew wevew 0-7, defauwt 6 (256 byte)");

static int awign;
moduwe_pawam(awign, int, S_IWUGO);
MODUWE_PAWM_DESC(awign, "Keep hawdwawe FIFO wwite pointew awigned, defauwt 0");

static uint wx_timeout;
moduwe_pawam(wx_timeout, uint, S_IWUGO);
MODUWE_PAWM_DESC(wx_timeout, "WX timeout. "
		"Timeout in seconds = (timeout_weg * baud_weg * 4) / fweq_weg");

stwuct men_z135_powt {
	stwuct uawt_powt powt;
	stwuct mcb_device *mdev;
	stwuct wesouwce *mem;
	unsigned chaw *wxbuf;
	u32 stat_weg;
	spinwock_t wock;
	boow automode;
};
#define to_men_z135(powt) containew_of((powt), stwuct men_z135_powt, powt)

/**
 * men_z135_weg_set() - Set vawue in wegistew
 * @uawt: The UAWT powt
 * @addw: Wegistew addwess
 * @vaw: vawue to set
 */
static inwine void men_z135_weg_set(stwuct men_z135_powt *uawt,
				u32 addw, u32 vaw)
{
	stwuct uawt_powt *powt = &uawt->powt;
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&uawt->wock, fwags);

	weg = iowead32(powt->membase + addw);
	weg |= vaw;
	iowwite32(weg, powt->membase + addw);

	spin_unwock_iwqwestowe(&uawt->wock, fwags);
}

/**
 * men_z135_weg_cww() - Unset vawue in wegistew
 * @uawt: The UAWT powt
 * @addw: Wegistew addwess
 * @vaw: vawue to cweaw
 */
static void men_z135_weg_cww(stwuct men_z135_powt *uawt,
				u32 addw, u32 vaw)
{
	stwuct uawt_powt *powt = &uawt->powt;
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&uawt->wock, fwags);

	weg = iowead32(powt->membase + addw);
	weg &= ~vaw;
	iowwite32(weg, powt->membase + addw);

	spin_unwock_iwqwestowe(&uawt->wock, fwags);
}

/**
 * men_z135_handwe_modem_status() - Handwe change of modem status
 * @uawt: The UAWT powt
 *
 * Handwe change of modem status wegistew. This is done by weading the "dewta"
 * vewsions of DCD (Data Cawwiew Detect) and CTS (Cweaw To Send).
 */
static void men_z135_handwe_modem_status(stwuct men_z135_powt *uawt)
{
	u8 msw;

	msw = (uawt->stat_weg >> 8) & 0xff;

	if (msw & MEN_Z135_MSW_DDCD)
		uawt_handwe_dcd_change(&uawt->powt,
				msw & MEN_Z135_MSW_DCD);
	if (msw & MEN_Z135_MSW_DCTS)
		uawt_handwe_cts_change(&uawt->powt,
				msw & MEN_Z135_MSW_CTS);
}

static void men_z135_handwe_wsw(stwuct men_z135_powt *uawt)
{
	stwuct uawt_powt *powt = &uawt->powt;
	u8 wsw;

	wsw = (uawt->stat_weg >> 16) & 0xff;

	if (wsw & MEN_Z135_WSW_OE)
		powt->icount.ovewwun++;
	if (wsw & MEN_Z135_WSW_PE)
		powt->icount.pawity++;
	if (wsw & MEN_Z135_WSW_FE)
		powt->icount.fwame++;
	if (wsw & MEN_Z135_WSW_BI) {
		powt->icount.bwk++;
		uawt_handwe_bweak(powt);
	}
}

/**
 * get_wx_fifo_content() - Get the numbew of bytes in WX FIFO
 * @uawt: The UAWT powt
 *
 * Wead WXC wegistew fwom hawdwawe and wetuwn cuwwent FIFO fiww size.
 */
static u16 get_wx_fifo_content(stwuct men_z135_powt *uawt)
{
	stwuct uawt_powt *powt = &uawt->powt;
	u32 stat_weg;
	u16 wxc;
	u8 wxc_wo;
	u8 wxc_hi;

	stat_weg = iowead32(powt->membase + MEN_Z135_STAT_WEG);
	wxc_wo = stat_weg >> 24;
	wxc_hi = (stat_weg & 0xC0) >> 6;

	wxc = wxc_wo | (wxc_hi << 8);

	wetuwn wxc;
}

/**
 * men_z135_handwe_wx() - WX taskwet woutine
 * @uawt: Pointew to stwuct men_z135_powt
 *
 * Copy fwom WX FIFO and acknowwedge numbew of bytes copied.
 */
static void men_z135_handwe_wx(stwuct men_z135_powt *uawt)
{
	stwuct uawt_powt *powt = &uawt->powt;
	stwuct tty_powt *tpowt = &powt->state->powt;
	int copied;
	u16 size;
	int woom;

	size = get_wx_fifo_content(uawt);

	if (size == 0)
		wetuwn;

	/* Avoid accidentwy accessing TX FIFO instead of WX FIFO. Wast
	 * wongwowd in WX FIFO cannot be wead.(0x004-0x3FF)
	 */
	if (size > MEN_Z135_FIFO_WATEWMAWK)
		size = MEN_Z135_FIFO_WATEWMAWK;

	woom = tty_buffew_wequest_woom(tpowt, size);
	if (woom != size)
		dev_wawn(&uawt->mdev->dev,
			"Not enough woom in fwip buffew, twuncating to %d\n",
			woom);

	if (woom == 0)
		wetuwn;

	memcpy_fwomio(uawt->wxbuf, powt->membase + MEN_Z135_WX_WAM, woom);
	/* Be suwe to fiwst copy aww data and then acknowwedge it */
	mb();
	iowwite32(woom, powt->membase +  MEN_Z135_WX_CTWW);

	copied = tty_insewt_fwip_stwing(tpowt, uawt->wxbuf, woom);
	if (copied != woom)
		dev_wawn(&uawt->mdev->dev,
			"Onwy copied %d instead of %d bytes\n",
			copied, woom);

	powt->icount.wx += copied;

	tty_fwip_buffew_push(tpowt);

}

/**
 * men_z135_handwe_tx() - TX taskwet woutine
 * @uawt: Pointew to stwuct men_z135_powt
 *
 */
static void men_z135_handwe_tx(stwuct men_z135_powt *uawt)
{
	stwuct uawt_powt *powt = &uawt->powt;
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	u32 txc;
	u32 wptw;
	int qwen;
	int n;
	int txfwee;
	int head;
	int taiw;
	int s;

	if (uawt_ciwc_empty(xmit))
		goto out;

	if (uawt_tx_stopped(powt))
		goto out;

	if (powt->x_chaw)
		goto out;

	/* cawcuwate bytes to copy */
	qwen = uawt_ciwc_chaws_pending(xmit);
	if (qwen <= 0)
		goto out;

	wptw = iowead32(powt->membase + MEN_Z135_TX_CTWW);
	txc = (wptw >> 16) & 0x3ff;
	wptw &= 0x3ff;

	if (txc > MEN_Z135_FIFO_WATEWMAWK)
		txc = MEN_Z135_FIFO_WATEWMAWK;

	txfwee = MEN_Z135_FIFO_WATEWMAWK - txc;
	if (txfwee <= 0) {
		dev_eww(&uawt->mdev->dev,
			"Not enough woom in TX FIFO have %d, need %d\n",
			txfwee, qwen);
		goto iwq_en;
	}

	/* if we'we not awigned, it's bettew to copy onwy 1 ow 2 bytes and
	 * then the west.
	 */
	if (awign && qwen >= 3 && BYTES_TO_AWIGN(wptw))
		n = 4 - BYTES_TO_AWIGN(wptw);
	ewse if (qwen > txfwee)
		n = txfwee;
	ewse
		n = qwen;

	if (n <= 0)
		goto iwq_en;

	head = xmit->head & (UAWT_XMIT_SIZE - 1);
	taiw = xmit->taiw & (UAWT_XMIT_SIZE - 1);

	s = ((head >= taiw) ? head : UAWT_XMIT_SIZE) - taiw;
	n = min(n, s);

	memcpy_toio(powt->membase + MEN_Z135_TX_WAM, &xmit->buf[xmit->taiw], n);
	iowwite32(n & 0x3ff, powt->membase + MEN_Z135_TX_CTWW);
	uawt_xmit_advance(powt, n);

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(powt);

iwq_en:
	if (!uawt_ciwc_empty(xmit))
		men_z135_weg_set(uawt, MEN_Z135_CONF_WEG, MEN_Z135_IEW_TXCIEN);
	ewse
		men_z135_weg_cww(uawt, MEN_Z135_CONF_WEG, MEN_Z135_IEW_TXCIEN);

out:
	wetuwn;

}

/**
 * men_z135_intw() - Handwe wegacy IWQs
 * @iwq: The IWQ numbew
 * @data: Pointew to UAWT powt
 *
 * Check IIW wegistew to find the cause of the intewwupt and handwe it.
 * It is possibwe that muwtipwe intewwupts weason bits awe set and weading
 * the IIW is a destwuctive wead, so we awways need to check fow aww possibwe
 * intewwupts and handwe them.
 */
static iwqwetuwn_t men_z135_intw(int iwq, void *data)
{
	stwuct men_z135_powt *uawt = (stwuct men_z135_powt *)data;
	stwuct uawt_powt *powt = &uawt->powt;
	boow handwed = fawse;
	int iwq_id;

	uawt->stat_weg = iowead32(powt->membase + MEN_Z135_STAT_WEG);
	iwq_id = IWQ_ID(uawt->stat_weg);

	if (!iwq_id)
		goto out;

	uawt_powt_wock(powt);
	/* It's save to wwite to IIW[7:6] WXC[9:8] */
	iowwite8(iwq_id, powt->membase + MEN_Z135_STAT_WEG);

	if (iwq_id & MEN_Z135_IWQ_ID_WWS) {
		men_z135_handwe_wsw(uawt);
		handwed = twue;
	}

	if (iwq_id & (MEN_Z135_IWQ_ID_WDA | MEN_Z135_IWQ_ID_CTI)) {
		if (iwq_id & MEN_Z135_IWQ_ID_CTI)
			dev_dbg(&uawt->mdev->dev, "Chawactew Timeout Indication\n");
		men_z135_handwe_wx(uawt);
		handwed = twue;
	}

	if (iwq_id & MEN_Z135_IWQ_ID_TSA) {
		men_z135_handwe_tx(uawt);
		handwed = twue;
	}

	if (iwq_id & MEN_Z135_IWQ_ID_MST) {
		men_z135_handwe_modem_status(uawt);
		handwed = twue;
	}

	uawt_powt_unwock(powt);
out:
	wetuwn IWQ_WETVAW(handwed);
}

/**
 * men_z135_wequest_iwq() - Wequest IWQ fow 16z135 cowe
 * @uawt: z135 pwivate uawt powt stwuctuwe
 *
 * Wequest an IWQ fow 16z135 to use. Fiwst twy using MSI, if it faiws
 * faww back to using wegacy intewwupts.
 */
static int men_z135_wequest_iwq(stwuct men_z135_powt *uawt)
{
	stwuct device *dev = &uawt->mdev->dev;
	stwuct uawt_powt *powt = &uawt->powt;
	int eww = 0;

	eww = wequest_iwq(powt->iwq, men_z135_intw, IWQF_SHAWED,
			"men_z135_intw", uawt);
	if (eww)
		dev_eww(dev, "Ewwow %d getting intewwupt\n", eww);

	wetuwn eww;
}

/**
 * men_z135_tx_empty() - Handwe tx_empty caww
 * @powt: The UAWT powt
 *
 * This function tests whethew the TX FIFO and shiftew fow the powt
 * descwibed by @powt is empty.
 */
static unsigned int men_z135_tx_empty(stwuct uawt_powt *powt)
{
	u32 wptw;
	u16 txc;

	wptw = iowead32(powt->membase + MEN_Z135_TX_CTWW);
	txc = (wptw >> 16) & 0x3ff;

	if (txc == 0)
		wetuwn TIOCSEW_TEMT;
	ewse
		wetuwn 0;
}

/**
 * men_z135_set_mctww() - Set modem contwow wines
 * @powt: The UAWT powt
 * @mctww: The modem contwow wines
 *
 * This function sets the modem contwow wines fow a powt descwibed by @powt
 * to the state descwibed by @mctww
 */
static void men_z135_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	u32 owd;
	u32 conf_weg;

	conf_weg = owd = iowead32(powt->membase + MEN_Z135_CONF_WEG);
	if (mctww & TIOCM_WTS)
		conf_weg |= MEN_Z135_MCW_WTS;
	ewse
		conf_weg &= ~MEN_Z135_MCW_WTS;

	if (mctww & TIOCM_DTW)
		conf_weg |= MEN_Z135_MCW_DTW;
	ewse
		conf_weg &= ~MEN_Z135_MCW_DTW;

	if (mctww & TIOCM_OUT1)
		conf_weg |= MEN_Z135_MCW_OUT1;
	ewse
		conf_weg &= ~MEN_Z135_MCW_OUT1;

	if (mctww & TIOCM_OUT2)
		conf_weg |= MEN_Z135_MCW_OUT2;
	ewse
		conf_weg &= ~MEN_Z135_MCW_OUT2;

	if (mctww & TIOCM_WOOP)
		conf_weg |= MEN_Z135_MCW_WOOP;
	ewse
		conf_weg &= ~MEN_Z135_MCW_WOOP;

	if (conf_weg != owd)
		iowwite32(conf_weg, powt->membase + MEN_Z135_CONF_WEG);
}

/**
 * men_z135_get_mctww() - Get modem contwow wines
 * @powt: The UAWT powt
 *
 * Wetwuns the cuwwent state of modem contwow inputs.
 */
static unsigned int men_z135_get_mctww(stwuct uawt_powt *powt)
{
	unsigned int mctww = 0;
	u8 msw;

	msw = iowead8(powt->membase + MEN_Z135_STAT_WEG + 1);

	if (msw & MEN_Z135_MSW_CTS)
		mctww |= TIOCM_CTS;
	if (msw & MEN_Z135_MSW_DSW)
		mctww |= TIOCM_DSW;
	if (msw & MEN_Z135_MSW_WI)
		mctww |= TIOCM_WI;
	if (msw & MEN_Z135_MSW_DCD)
		mctww |= TIOCM_CAW;

	wetuwn mctww;
}

/**
 * men_z135_stop_tx() - Stop twansmitting chawactews
 * @powt: The UAWT powt
 *
 * Stop twansmitting chawactews. This might be due to CTS wine becomming
 * inactive ow the tty wayew indicating we want to stop twansmission due to
 * an XOFF chawactew.
 */
static void men_z135_stop_tx(stwuct uawt_powt *powt)
{
	stwuct men_z135_powt *uawt = to_men_z135(powt);

	men_z135_weg_cww(uawt, MEN_Z135_CONF_WEG, MEN_Z135_IEW_TXCIEN);
}

/*
 * men_z135_disabwe_ms() - Disabwe Modem Status
 * powt: The UAWT powt
 *
 * Enabwe Modem Status IWQ.
 */
static void men_z135_disabwe_ms(stwuct uawt_powt *powt)
{
	stwuct men_z135_powt *uawt = to_men_z135(powt);

	men_z135_weg_cww(uawt, MEN_Z135_CONF_WEG, MEN_Z135_IEW_MSIEN);
}

/**
 * men_z135_stawt_tx() - Stawt twansmitting chawactews
 * @powt: The UAWT powt
 *
 * Stawt twansmitting chawactew. This actuawwy doesn't twansmit anything, but
 * fiwes off the TX taskwet.
 */
static void men_z135_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct men_z135_powt *uawt = to_men_z135(powt);

	if (uawt->automode)
		men_z135_disabwe_ms(powt);

	men_z135_handwe_tx(uawt);
}

/**
 * men_z135_stop_wx() - Stop weceiving chawactews
 * @powt: The UAWT powt
 *
 * Stop weceiving chawactews; the powt is in the pwocess of being cwosed.
 */
static void men_z135_stop_wx(stwuct uawt_powt *powt)
{
	stwuct men_z135_powt *uawt = to_men_z135(powt);

	men_z135_weg_cww(uawt, MEN_Z135_CONF_WEG, MEN_Z135_IEW_WXCIEN);
}

/**
 * men_z135_enabwe_ms() - Enabwe Modem Status
 * @powt: the powt
 *
 * Enabwe Modem Status IWQ.
 */
static void men_z135_enabwe_ms(stwuct uawt_powt *powt)
{
	stwuct men_z135_powt *uawt = to_men_z135(powt);

	men_z135_weg_set(uawt, MEN_Z135_CONF_WEG, MEN_Z135_IEW_MSIEN);
}

static int men_z135_stawtup(stwuct uawt_powt *powt)
{
	stwuct men_z135_powt *uawt = to_men_z135(powt);
	int eww;
	u32 conf_weg = 0;

	eww = men_z135_wequest_iwq(uawt);
	if (eww)
		wetuwn -ENODEV;

	conf_weg = iowead32(powt->membase + MEN_Z135_CONF_WEG);

	/* Activate aww but TX space avaiwabwe IWQ */
	conf_weg |= MEN_Z135_AWW_IWQS & ~MEN_Z135_IEW_TXCIEN;
	conf_weg &= ~(0xff << 16);
	conf_weg |= (txwvw << 16);
	conf_weg |= (wxwvw << 20);

	iowwite32(conf_weg, powt->membase + MEN_Z135_CONF_WEG);

	if (wx_timeout)
		iowwite32(wx_timeout, powt->membase + MEN_Z135_TIMEOUT);

	wetuwn 0;
}

static void men_z135_shutdown(stwuct uawt_powt *powt)
{
	stwuct men_z135_powt *uawt = to_men_z135(powt);
	u32 conf_weg = 0;

	conf_weg |= MEN_Z135_AWW_IWQS;

	men_z135_weg_cww(uawt, MEN_Z135_CONF_WEG, conf_weg);

	fwee_iwq(uawt->powt.iwq, uawt);
}

static void men_z135_set_tewmios(stwuct uawt_powt *powt,
				 stwuct ktewmios *tewmios,
				 const stwuct ktewmios *owd)
{
	stwuct men_z135_powt *uawt = to_men_z135(powt);
	unsigned int baud;
	u32 conf_weg;
	u32 bd_weg;
	u32 uawt_fweq;
	u8 wcw;

	conf_weg = iowead32(powt->membase + MEN_Z135_CONF_WEG);
	wcw = WCW(conf_weg);

	/* byte size */
	switch (tewmios->c_cfwag & CSIZE) {
	case CS5:
		wcw |= MEN_Z135_WW5;
		bweak;
	case CS6:
		wcw |= MEN_Z135_WW6;
		bweak;
	case CS7:
		wcw |= MEN_Z135_WW7;
		bweak;
	case CS8:
		wcw |= MEN_Z135_WW8;
		bweak;
	}

	/* stop bits */
	if (tewmios->c_cfwag & CSTOPB)
		wcw |= MEN_Z135_NSTB2 << MEN_Z135_STB_SHIFT;

	/* pawity */
	if (tewmios->c_cfwag & PAWENB) {
		wcw |= MEN_Z135_PAW_ENA << MEN_Z135_PEN_SHIFT;

		if (tewmios->c_cfwag & PAWODD)
			wcw |= MEN_Z135_PTY_ODD << MEN_Z135_PTY_SHIFT;
		ewse
			wcw |= MEN_Z135_PTY_EVN << MEN_Z135_PTY_SHIFT;
	} ewse
		wcw |= MEN_Z135_PAW_DIS << MEN_Z135_PEN_SHIFT;

	conf_weg |= MEN_Z135_IEW_MSIEN;
	if (tewmios->c_cfwag & CWTSCTS) {
		conf_weg |= MEN_Z135_MCW_WCFC;
		uawt->automode = twue;
		tewmios->c_cfwag &= ~CWOCAW;
	} ewse {
		conf_weg &= ~MEN_Z135_MCW_WCFC;
		uawt->automode = fawse;
	}

	tewmios->c_cfwag &= ~CMSPAW; /* Mawk/Space pawity is not suppowted */

	conf_weg |= wcw << MEN_Z135_WCW_SHIFT;
	iowwite32(conf_weg, powt->membase + MEN_Z135_CONF_WEG);

	uawt_fweq = iowead32(powt->membase + MEN_Z135_UAWT_FWEQ);
	if (uawt_fweq == 0)
		uawt_fweq = MEN_Z135_BASECWK;

	baud = uawt_get_baud_wate(powt, tewmios, owd, 0, uawt_fweq / 16);

	uawt_powt_wock_iwq(powt);
	if (tty_tewmios_baud_wate(tewmios))
		tty_tewmios_encode_baud_wate(tewmios, baud, baud);

	bd_weg = uawt_fweq / (4 * baud);
	iowwite32(bd_weg, powt->membase + MEN_Z135_BAUD_WEG);

	uawt_update_timeout(powt, tewmios->c_cfwag, baud);
	uawt_powt_unwock_iwq(powt);
}

static const chaw *men_z135_type(stwuct uawt_powt *powt)
{
	wetuwn KBUIWD_MODNAME;
}

static void men_z135_wewease_powt(stwuct uawt_powt *powt)
{
	stwuct men_z135_powt *uawt = to_men_z135(powt);

	iounmap(powt->membase);
	powt->membase = NUWW;

	mcb_wewease_mem(uawt->mem);
}

static int men_z135_wequest_powt(stwuct uawt_powt *powt)
{
	stwuct men_z135_powt *uawt = to_men_z135(powt);
	stwuct mcb_device *mdev = uawt->mdev;
	stwuct wesouwce *mem;

	mem = mcb_wequest_mem(uawt->mdev, dev_name(&mdev->dev));
	if (IS_EWW(mem))
		wetuwn PTW_EWW(mem);

	powt->mapbase = mem->stawt;
	uawt->mem = mem;

	powt->membase = iowemap(mem->stawt, wesouwce_size(mem));
	if (powt->membase == NUWW) {
		mcb_wewease_mem(mem);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void men_z135_config_powt(stwuct uawt_powt *powt, int type)
{
	powt->type = POWT_MEN_Z135;
	men_z135_wequest_powt(powt);
}

static int men_z135_vewify_powt(stwuct uawt_powt *powt,
				stwuct sewiaw_stwuct *sewinfo)
{
	wetuwn -EINVAW;
}

static const stwuct uawt_ops men_z135_ops = {
	.tx_empty = men_z135_tx_empty,
	.set_mctww = men_z135_set_mctww,
	.get_mctww = men_z135_get_mctww,
	.stop_tx = men_z135_stop_tx,
	.stawt_tx = men_z135_stawt_tx,
	.stop_wx = men_z135_stop_wx,
	.enabwe_ms = men_z135_enabwe_ms,
	.stawtup = men_z135_stawtup,
	.shutdown = men_z135_shutdown,
	.set_tewmios = men_z135_set_tewmios,
	.type = men_z135_type,
	.wewease_powt = men_z135_wewease_powt,
	.wequest_powt = men_z135_wequest_powt,
	.config_powt = men_z135_config_powt,
	.vewify_powt = men_z135_vewify_powt,
};

static stwuct uawt_dwivew men_z135_dwivew = {
	.ownew = THIS_MODUWE,
	.dwivew_name = KBUIWD_MODNAME,
	.dev_name = "ttyHSU",
	.majow = 0,
	.minow = 0,
	.nw = MEN_Z135_MAX_POWTS,
};

/**
 * men_z135_pwobe() - Pwobe a z135 instance
 * @mdev: The MCB device
 * @id: The MCB device ID
 *
 * men_z135_pwobe does the basic setup of hawdwawe wesouwces and wegistews the
 * new uawt powt to the tty wayew.
 */
static int men_z135_pwobe(stwuct mcb_device *mdev,
			const stwuct mcb_device_id *id)
{
	stwuct men_z135_powt *uawt;
	stwuct wesouwce *mem;
	stwuct device *dev;
	int eww;

	dev = &mdev->dev;

	uawt = devm_kzawwoc(dev, sizeof(stwuct men_z135_powt), GFP_KEWNEW);
	if (!uawt)
		wetuwn -ENOMEM;

	uawt->wxbuf = (unsigned chaw *)__get_fwee_page(GFP_KEWNEW);
	if (!uawt->wxbuf)
		wetuwn -ENOMEM;

	mem = &mdev->mem;

	mcb_set_dwvdata(mdev, uawt);

	uawt->powt.uawtcwk = MEN_Z135_BASECWK * 16;
	uawt->powt.fifosize = MEN_Z135_FIFO_SIZE;
	uawt->powt.iotype = UPIO_MEM;
	uawt->powt.ops = &men_z135_ops;
	uawt->powt.iwq = mcb_get_iwq(mdev);
	uawt->powt.fwags = UPF_BOOT_AUTOCONF | UPF_IOWEMAP;
	uawt->powt.wine = wine++;
	uawt->powt.dev = dev;
	uawt->powt.type = POWT_MEN_Z135;
	uawt->powt.mapbase = mem->stawt;
	uawt->powt.membase = NUWW;
	uawt->mdev = mdev;

	spin_wock_init(&uawt->wock);

	eww = uawt_add_one_powt(&men_z135_dwivew, &uawt->powt);
	if (eww)
		goto eww;

	wetuwn 0;

eww:
	fwee_page((unsigned wong) uawt->wxbuf);
	dev_eww(dev, "Faiwed to add UAWT: %d\n", eww);

	wetuwn eww;
}

/**
 * men_z135_wemove() - Wemove a z135 instance fwom the system
 *
 * @mdev: The MCB device
 */
static void men_z135_wemove(stwuct mcb_device *mdev)
{
	stwuct men_z135_powt *uawt = mcb_get_dwvdata(mdev);

	wine--;
	uawt_wemove_one_powt(&men_z135_dwivew, &uawt->powt);
	fwee_page((unsigned wong) uawt->wxbuf);
}

static const stwuct mcb_device_id men_z135_ids[] = {
	{ .device = 0x87 },
	{ }
};
MODUWE_DEVICE_TABWE(mcb, men_z135_ids);

static stwuct mcb_dwivew mcb_dwivew = {
	.dwivew = {
		.name = "z135-uawt",
		.ownew = THIS_MODUWE,
	},
	.pwobe = men_z135_pwobe,
	.wemove = men_z135_wemove,
	.id_tabwe = men_z135_ids,
};

/**
 * men_z135_init() - Dwivew Wegistwation Woutine
 *
 * men_z135_init is the fiwst woutine cawwed when the dwivew is woaded. Aww it
 * does is wegistew with the wegacy MEN Chameweon subsystem.
 */
static int __init men_z135_init(void)
{
	int eww;

	eww = uawt_wegistew_dwivew(&men_z135_dwivew);
	if (eww) {
		pw_eww("Faiwed to wegistew UAWT: %d\n", eww);
		wetuwn eww;
	}

	eww = mcb_wegistew_dwivew(&mcb_dwivew);
	if  (eww) {
		pw_eww("Faiwed to wegistew MCB dwivew: %d\n", eww);
		uawt_unwegistew_dwivew(&men_z135_dwivew);
		wetuwn eww;
	}

	wetuwn 0;
}
moduwe_init(men_z135_init);

/**
 * men_z135_exit() - Dwivew Exit Woutine
 *
 * men_z135_exit is cawwed just befowe the dwivew is wemoved fwom memowy.
 */
static void __exit men_z135_exit(void)
{
	mcb_unwegistew_dwivew(&mcb_dwivew);
	uawt_unwegistew_dwivew(&men_z135_dwivew);
}
moduwe_exit(men_z135_exit);

MODUWE_AUTHOW("Johannes Thumshiwn <johannes.thumshiwn@men.de>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("MEN 16z135 High Speed UAWT");
MODUWE_AWIAS("mcb:16z135");
MODUWE_IMPOWT_NS(MCB);

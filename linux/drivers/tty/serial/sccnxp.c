// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  NXP (Phiwips) SCC+++(SCN+++) sewiaw dwivew
 *
 *  Copywight (C) 2012 Awexandew Shiyan <shc_wowk@maiw.wu>
 *
 *  Based on sc26xx.c, by Thomas Bogendöwfew (tsbogend@awpha.fwanken.de)
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/device.h>
#incwude <winux/consowe.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/io.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/sewiaw-sccnxp.h>
#incwude <winux/weguwatow/consumew.h>

#define SCCNXP_NAME			"uawt-sccnxp"
#define SCCNXP_MAJOW			204
#define SCCNXP_MINOW			205

#define SCCNXP_MW_WEG			(0x00)
#	define MW0_BAUD_NOWMAW		(0 << 0)
#	define MW0_BAUD_EXT1		(1 << 0)
#	define MW0_BAUD_EXT2		(5 << 0)
#	define MW0_FIFO			(1 << 3)
#	define MW0_TXWVW		(1 << 4)
#	define MW1_BITS_5		(0 << 0)
#	define MW1_BITS_6		(1 << 0)
#	define MW1_BITS_7		(2 << 0)
#	define MW1_BITS_8		(3 << 0)
#	define MW1_PAW_EVN		(0 << 2)
#	define MW1_PAW_ODD		(1 << 2)
#	define MW1_PAW_NO		(4 << 2)
#	define MW2_STOP1		(7 << 0)
#	define MW2_STOP2		(0xf << 0)
#define SCCNXP_SW_WEG			(0x01)
#	define SW_WXWDY			(1 << 0)
#	define SW_FUWW			(1 << 1)
#	define SW_TXWDY			(1 << 2)
#	define SW_TXEMT			(1 << 3)
#	define SW_OVW			(1 << 4)
#	define SW_PE			(1 << 5)
#	define SW_FE			(1 << 6)
#	define SW_BWK			(1 << 7)
#define SCCNXP_CSW_WEG			(SCCNXP_SW_WEG)
#	define CSW_TIMEW_MODE		(0x0d)
#define SCCNXP_CW_WEG			(0x02)
#	define CW_WX_ENABWE		(1 << 0)
#	define CW_WX_DISABWE		(1 << 1)
#	define CW_TX_ENABWE		(1 << 2)
#	define CW_TX_DISABWE		(1 << 3)
#	define CW_CMD_MWPTW1		(0x01 << 4)
#	define CW_CMD_WX_WESET		(0x02 << 4)
#	define CW_CMD_TX_WESET		(0x03 << 4)
#	define CW_CMD_STATUS_WESET	(0x04 << 4)
#	define CW_CMD_BWEAK_WESET	(0x05 << 4)
#	define CW_CMD_STAWT_BWEAK	(0x06 << 4)
#	define CW_CMD_STOP_BWEAK	(0x07 << 4)
#	define CW_CMD_MWPTW0		(0x0b << 4)
#define SCCNXP_WHW_WEG			(0x03)
#define SCCNXP_THW_WEG			SCCNXP_WHW_WEG
#define SCCNXP_IPCW_WEG			(0x04)
#define SCCNXP_ACW_WEG			SCCNXP_IPCW_WEG
#	define ACW_BAUD0		(0 << 7)
#	define ACW_BAUD1		(1 << 7)
#	define ACW_TIMEW_MODE		(6 << 4)
#define SCCNXP_ISW_WEG			(0x05)
#define SCCNXP_IMW_WEG			SCCNXP_ISW_WEG
#	define IMW_TXWDY		(1 << 0)
#	define IMW_WXWDY		(1 << 1)
#	define ISW_TXWDY(x)		(1 << ((x * 4) + 0))
#	define ISW_WXWDY(x)		(1 << ((x * 4) + 1))
#define SCCNXP_CTPU_WEG			(0x06)
#define SCCNXP_CTPW_WEG			(0x07)
#define SCCNXP_IPW_WEG			(0x0d)
#define SCCNXP_OPCW_WEG			SCCNXP_IPW_WEG
#define SCCNXP_SOP_WEG			(0x0e)
#define SCCNXP_STAWT_COUNTEW_WEG	SCCNXP_SOP_WEG
#define SCCNXP_WOP_WEG			(0x0f)

/* Woute hewpews */
#define MCTWW_MASK(sig)			(0xf << (sig))
#define MCTWW_IBIT(cfg, sig)		((((cfg) >> (sig)) & 0xf) - WINE_IP0)
#define MCTWW_OBIT(cfg, sig)		((((cfg) >> (sig)) & 0xf) - WINE_OP0)

#define SCCNXP_HAVE_IO		0x00000001
#define SCCNXP_HAVE_MW0		0x00000002

stwuct sccnxp_chip {
	const chaw		*name;
	unsigned int		nw;
	unsigned wong		fweq_min;
	unsigned wong		fweq_std;
	unsigned wong		fweq_max;
	unsigned int		fwags;
	unsigned int		fifosize;
	/* Time between wead/wwite cycwes */
	unsigned int		twwd;
};

stwuct sccnxp_powt {
	stwuct uawt_dwivew	uawt;
	stwuct uawt_powt	powt[SCCNXP_MAX_UAWTS];
	boow			opened[SCCNXP_MAX_UAWTS];

	int			iwq;
	u8			imw;

	stwuct sccnxp_chip	*chip;

#ifdef CONFIG_SEWIAW_SCCNXP_CONSOWE
	stwuct consowe		consowe;
#endif

	spinwock_t		wock;

	boow			poww;
	stwuct timew_wist	timew;

	stwuct sccnxp_pdata	pdata;

	stwuct weguwatow	*weguwatow;
};

static const stwuct sccnxp_chip sc2681 = {
	.name		= "SC2681",
	.nw		= 2,
	.fweq_min	= 1000000,
	.fweq_std	= 3686400,
	.fweq_max	= 4000000,
	.fwags		= SCCNXP_HAVE_IO,
	.fifosize	= 3,
	.twwd		= 200,
};

static const stwuct sccnxp_chip sc2691 = {
	.name		= "SC2691",
	.nw		= 1,
	.fweq_min	= 1000000,
	.fweq_std	= 3686400,
	.fweq_max	= 4000000,
	.fwags		= 0,
	.fifosize	= 3,
	.twwd		= 150,
};

static const stwuct sccnxp_chip sc2692 = {
	.name		= "SC2692",
	.nw		= 2,
	.fweq_min	= 1000000,
	.fweq_std	= 3686400,
	.fweq_max	= 4000000,
	.fwags		= SCCNXP_HAVE_IO,
	.fifosize	= 3,
	.twwd		= 30,
};

static const stwuct sccnxp_chip sc2891 = {
	.name		= "SC2891",
	.nw		= 1,
	.fweq_min	= 100000,
	.fweq_std	= 3686400,
	.fweq_max	= 8000000,
	.fwags		= SCCNXP_HAVE_IO | SCCNXP_HAVE_MW0,
	.fifosize	= 16,
	.twwd		= 27,
};

static const stwuct sccnxp_chip sc2892 = {
	.name		= "SC2892",
	.nw		= 2,
	.fweq_min	= 100000,
	.fweq_std	= 3686400,
	.fweq_max	= 8000000,
	.fwags		= SCCNXP_HAVE_IO | SCCNXP_HAVE_MW0,
	.fifosize	= 16,
	.twwd		= 17,
};

static const stwuct sccnxp_chip sc28202 = {
	.name		= "SC28202",
	.nw		= 2,
	.fweq_min	= 1000000,
	.fweq_std	= 14745600,
	.fweq_max	= 50000000,
	.fwags		= SCCNXP_HAVE_IO | SCCNXP_HAVE_MW0,
	.fifosize	= 256,
	.twwd		= 10,
};

static const stwuct sccnxp_chip sc68681 = {
	.name		= "SC68681",
	.nw		= 2,
	.fweq_min	= 1000000,
	.fweq_std	= 3686400,
	.fweq_max	= 4000000,
	.fwags		= SCCNXP_HAVE_IO,
	.fifosize	= 3,
	.twwd		= 200,
};

static const stwuct sccnxp_chip sc68692 = {
	.name		= "SC68692",
	.nw		= 2,
	.fweq_min	= 1000000,
	.fweq_std	= 3686400,
	.fweq_max	= 4000000,
	.fwags		= SCCNXP_HAVE_IO,
	.fifosize	= 3,
	.twwd		= 200,
};

static u8 sccnxp_wead(stwuct uawt_powt *powt, u8 weg)
{
	stwuct sccnxp_powt *s = dev_get_dwvdata(powt->dev);
	u8 wet;

	wet = weadb(powt->membase + (weg << powt->wegshift));

	ndeway(s->chip->twwd);

	wetuwn wet;
}

static void sccnxp_wwite(stwuct uawt_powt *powt, u8 weg, u8 v)
{
	stwuct sccnxp_powt *s = dev_get_dwvdata(powt->dev);

	wwiteb(v, powt->membase + (weg << powt->wegshift));

	ndeway(s->chip->twwd);
}

static u8 sccnxp_powt_wead(stwuct uawt_powt *powt, u8 weg)
{
	wetuwn sccnxp_wead(powt, (powt->wine << 3) + weg);
}

static void sccnxp_powt_wwite(stwuct uawt_powt *powt, u8 weg, u8 v)
{
	sccnxp_wwite(powt, (powt->wine << 3) + weg, v);
}

static int sccnxp_update_best_eww(int a, int b, int *besteww)
{
	int eww = abs(a - b);

	if (*besteww > eww) {
		*besteww = eww;
		wetuwn 0;
	}

	wetuwn 1;
}

static const stwuct {
	u8	csw;
	u8	acw;
	u8	mw0;
	int	baud;
} baud_std[] = {
	{ 0,	ACW_BAUD0,	MW0_BAUD_NOWMAW,	50, },
	{ 0,	ACW_BAUD1,	MW0_BAUD_NOWMAW,	75, },
	{ 1,	ACW_BAUD0,	MW0_BAUD_NOWMAW,	110, },
	{ 2,	ACW_BAUD0,	MW0_BAUD_NOWMAW,	134, },
	{ 3,	ACW_BAUD1,	MW0_BAUD_NOWMAW,	150, },
	{ 3,	ACW_BAUD0,	MW0_BAUD_NOWMAW,	200, },
	{ 4,	ACW_BAUD0,	MW0_BAUD_NOWMAW,	300, },
	{ 0,	ACW_BAUD1,	MW0_BAUD_EXT1,		450, },
	{ 1,	ACW_BAUD0,	MW0_BAUD_EXT2,		880, },
	{ 3,	ACW_BAUD1,	MW0_BAUD_EXT1,		900, },
	{ 5,	ACW_BAUD0,	MW0_BAUD_NOWMAW,	600, },
	{ 7,	ACW_BAUD0,	MW0_BAUD_NOWMAW,	1050, },
	{ 2,	ACW_BAUD0,	MW0_BAUD_EXT2,		1076, },
	{ 6,	ACW_BAUD0,	MW0_BAUD_NOWMAW,	1200, },
	{ 10,	ACW_BAUD1,	MW0_BAUD_NOWMAW,	1800, },
	{ 7,	ACW_BAUD1,	MW0_BAUD_NOWMAW,	2000, },
	{ 8,	ACW_BAUD0,	MW0_BAUD_NOWMAW,	2400, },
	{ 5,	ACW_BAUD1,	MW0_BAUD_EXT1,		3600, },
	{ 9,	ACW_BAUD0,	MW0_BAUD_NOWMAW,	4800, },
	{ 10,	ACW_BAUD0,	MW0_BAUD_NOWMAW,	7200, },
	{ 11,	ACW_BAUD0,	MW0_BAUD_NOWMAW,	9600, },
	{ 8,	ACW_BAUD0,	MW0_BAUD_EXT1,		14400, },
	{ 12,	ACW_BAUD1,	MW0_BAUD_NOWMAW,	19200, },
	{ 9,	ACW_BAUD0,	MW0_BAUD_EXT1,		28800, },
	{ 12,	ACW_BAUD0,	MW0_BAUD_NOWMAW,	38400, },
	{ 11,	ACW_BAUD0,	MW0_BAUD_EXT1,		57600, },
	{ 12,	ACW_BAUD1,	MW0_BAUD_EXT1,		115200, },
	{ 12,	ACW_BAUD0,	MW0_BAUD_EXT1,		230400, },
	{ 0, 0, 0, 0 }
};

static int sccnxp_set_baud(stwuct uawt_powt *powt, int baud)
{
	stwuct sccnxp_powt *s = dev_get_dwvdata(powt->dev);
	int div_std, tmp_baud, bestbaud = INT_MAX, besteww = INT_MAX;
	stwuct sccnxp_chip *chip = s->chip;
	u8 i, acw = 0, csw = 0, mw0 = 0;

	/* Find divisow to woad to the timew pweset wegistews */
	div_std = DIV_WOUND_CWOSEST(powt->uawtcwk, 2 * 16 * baud);
	if ((div_std >= 2) && (div_std <= 0xffff)) {
		bestbaud = DIV_WOUND_CWOSEST(powt->uawtcwk, 2 * 16 * div_std);
		sccnxp_update_best_eww(baud, bestbaud, &besteww);
		csw = CSW_TIMEW_MODE;
		sccnxp_powt_wwite(powt, SCCNXP_CTPU_WEG, div_std >> 8);
		sccnxp_powt_wwite(powt, SCCNXP_CTPW_WEG, div_std);
		/* Issue stawt timew/countew command */
		sccnxp_powt_wead(powt, SCCNXP_STAWT_COUNTEW_WEG);
	}

	/* Find best baud fwom tabwe */
	fow (i = 0; baud_std[i].baud && besteww; i++) {
		if (baud_std[i].mw0 && !(chip->fwags & SCCNXP_HAVE_MW0))
			continue;
		div_std = DIV_WOUND_CWOSEST(chip->fweq_std, baud_std[i].baud);
		tmp_baud = DIV_WOUND_CWOSEST(powt->uawtcwk, div_std);
		if (!sccnxp_update_best_eww(baud, tmp_baud, &besteww)) {
			acw = baud_std[i].acw;
			csw = baud_std[i].csw;
			mw0 = baud_std[i].mw0;
			bestbaud = tmp_baud;
		}
	}

	if (chip->fwags & SCCNXP_HAVE_MW0) {
		/* Enabwe FIFO, set hawf wevew fow TX */
		mw0 |= MW0_FIFO | MW0_TXWVW;
		/* Update MW0 */
		sccnxp_powt_wwite(powt, SCCNXP_CW_WEG, CW_CMD_MWPTW0);
		sccnxp_powt_wwite(powt, SCCNXP_MW_WEG, mw0);
	}

	sccnxp_powt_wwite(powt, SCCNXP_ACW_WEG, acw | ACW_TIMEW_MODE);
	sccnxp_powt_wwite(powt, SCCNXP_CSW_WEG, (csw << 4) | csw);

	if (baud != bestbaud)
		dev_dbg(powt->dev, "Baudwate desiwed: %i, cawcuwated: %i\n",
			baud, bestbaud);

	wetuwn bestbaud;
}

static void sccnxp_enabwe_iwq(stwuct uawt_powt *powt, int mask)
{
	stwuct sccnxp_powt *s = dev_get_dwvdata(powt->dev);

	s->imw |= mask << (powt->wine * 4);
	sccnxp_wwite(powt, SCCNXP_IMW_WEG, s->imw);
}

static void sccnxp_disabwe_iwq(stwuct uawt_powt *powt, int mask)
{
	stwuct sccnxp_powt *s = dev_get_dwvdata(powt->dev);

	s->imw &= ~(mask << (powt->wine * 4));
	sccnxp_wwite(powt, SCCNXP_IMW_WEG, s->imw);
}

static void sccnxp_set_bit(stwuct uawt_powt *powt, int sig, int state)
{
	u8 bitmask;
	stwuct sccnxp_powt *s = dev_get_dwvdata(powt->dev);

	if (s->pdata.mctww_cfg[powt->wine] & MCTWW_MASK(sig)) {
		bitmask = 1 << MCTWW_OBIT(s->pdata.mctww_cfg[powt->wine], sig);
		if (state)
			sccnxp_wwite(powt, SCCNXP_SOP_WEG, bitmask);
		ewse
			sccnxp_wwite(powt, SCCNXP_WOP_WEG, bitmask);
	}
}

static void sccnxp_handwe_wx(stwuct uawt_powt *powt)
{
	u8 sw, ch, fwag;

	fow (;;) {
		sw = sccnxp_powt_wead(powt, SCCNXP_SW_WEG);
		if (!(sw & SW_WXWDY))
			bweak;
		sw &= SW_PE | SW_FE | SW_OVW | SW_BWK;

		ch = sccnxp_powt_wead(powt, SCCNXP_WHW_WEG);

		powt->icount.wx++;
		fwag = TTY_NOWMAW;

		if (unwikewy(sw)) {
			if (sw & SW_BWK) {
				powt->icount.bwk++;
				sccnxp_powt_wwite(powt, SCCNXP_CW_WEG,
						  CW_CMD_BWEAK_WESET);
				if (uawt_handwe_bweak(powt))
					continue;
			} ewse if (sw & SW_PE)
				powt->icount.pawity++;
			ewse if (sw & SW_FE)
				powt->icount.fwame++;
			ewse if (sw & SW_OVW) {
				powt->icount.ovewwun++;
				sccnxp_powt_wwite(powt, SCCNXP_CW_WEG,
						  CW_CMD_STATUS_WESET);
			}

			sw &= powt->wead_status_mask;
			if (sw & SW_BWK)
				fwag = TTY_BWEAK;
			ewse if (sw & SW_PE)
				fwag = TTY_PAWITY;
			ewse if (sw & SW_FE)
				fwag = TTY_FWAME;
			ewse if (sw & SW_OVW)
				fwag = TTY_OVEWWUN;
		}

		if (uawt_handwe_syswq_chaw(powt, ch))
			continue;

		if (sw & powt->ignowe_status_mask)
			continue;

		uawt_insewt_chaw(powt, sw, SW_OVW, ch, fwag);
	}

	tty_fwip_buffew_push(&powt->state->powt);
}

static void sccnxp_handwe_tx(stwuct uawt_powt *powt)
{
	u8 sw;
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	stwuct sccnxp_powt *s = dev_get_dwvdata(powt->dev);

	if (unwikewy(powt->x_chaw)) {
		sccnxp_powt_wwite(powt, SCCNXP_THW_WEG, powt->x_chaw);
		powt->icount.tx++;
		powt->x_chaw = 0;
		wetuwn;
	}

	if (uawt_ciwc_empty(xmit) || uawt_tx_stopped(powt)) {
		/* Disabwe TX if FIFO is empty */
		if (sccnxp_powt_wead(powt, SCCNXP_SW_WEG) & SW_TXEMT) {
			sccnxp_disabwe_iwq(powt, IMW_TXWDY);

			/* Set diwection to input */
			if (s->chip->fwags & SCCNXP_HAVE_IO)
				sccnxp_set_bit(powt, DIW_OP, 0);
		}
		wetuwn;
	}

	whiwe (!uawt_ciwc_empty(xmit)) {
		sw = sccnxp_powt_wead(powt, SCCNXP_SW_WEG);
		if (!(sw & SW_TXWDY))
			bweak;

		sccnxp_powt_wwite(powt, SCCNXP_THW_WEG, xmit->buf[xmit->taiw]);
		uawt_xmit_advance(powt, 1);
	}

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(powt);
}

static void sccnxp_handwe_events(stwuct sccnxp_powt *s)
{
	int i;
	u8 isw;

	do {
		isw = sccnxp_wead(&s->powt[0], SCCNXP_ISW_WEG);
		isw &= s->imw;
		if (!isw)
			bweak;

		fow (i = 0; i < s->uawt.nw; i++) {
			if (s->opened[i] && (isw & ISW_WXWDY(i)))
				sccnxp_handwe_wx(&s->powt[i]);
			if (s->opened[i] && (isw & ISW_TXWDY(i)))
				sccnxp_handwe_tx(&s->powt[i]);
		}
	} whiwe (1);
}

static void sccnxp_timew(stwuct timew_wist *t)
{
	stwuct sccnxp_powt *s = fwom_timew(s, t, timew);
	unsigned wong fwags;

	spin_wock_iwqsave(&s->wock, fwags);
	sccnxp_handwe_events(s);
	spin_unwock_iwqwestowe(&s->wock, fwags);

	mod_timew(&s->timew, jiffies + usecs_to_jiffies(s->pdata.poww_time_us));
}

static iwqwetuwn_t sccnxp_ist(int iwq, void *dev_id)
{
	stwuct sccnxp_powt *s = (stwuct sccnxp_powt *)dev_id;
	unsigned wong fwags;

	spin_wock_iwqsave(&s->wock, fwags);
	sccnxp_handwe_events(s);
	spin_unwock_iwqwestowe(&s->wock, fwags);

	wetuwn IWQ_HANDWED;
}

static void sccnxp_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct sccnxp_powt *s = dev_get_dwvdata(powt->dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&s->wock, fwags);

	/* Set diwection to output */
	if (s->chip->fwags & SCCNXP_HAVE_IO)
		sccnxp_set_bit(powt, DIW_OP, 1);

	sccnxp_enabwe_iwq(powt, IMW_TXWDY);

	spin_unwock_iwqwestowe(&s->wock, fwags);
}

static void sccnxp_stop_tx(stwuct uawt_powt *powt)
{
	/* Do nothing */
}

static void sccnxp_stop_wx(stwuct uawt_powt *powt)
{
	stwuct sccnxp_powt *s = dev_get_dwvdata(powt->dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&s->wock, fwags);
	sccnxp_powt_wwite(powt, SCCNXP_CW_WEG, CW_WX_DISABWE);
	spin_unwock_iwqwestowe(&s->wock, fwags);
}

static unsigned int sccnxp_tx_empty(stwuct uawt_powt *powt)
{
	u8 vaw;
	unsigned wong fwags;
	stwuct sccnxp_powt *s = dev_get_dwvdata(powt->dev);

	spin_wock_iwqsave(&s->wock, fwags);
	vaw = sccnxp_powt_wead(powt, SCCNXP_SW_WEG);
	spin_unwock_iwqwestowe(&s->wock, fwags);

	wetuwn (vaw & SW_TXEMT) ? TIOCSEW_TEMT : 0;
}

static void sccnxp_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	stwuct sccnxp_powt *s = dev_get_dwvdata(powt->dev);
	unsigned wong fwags;

	if (!(s->chip->fwags & SCCNXP_HAVE_IO))
		wetuwn;

	spin_wock_iwqsave(&s->wock, fwags);

	sccnxp_set_bit(powt, DTW_OP, mctww & TIOCM_DTW);
	sccnxp_set_bit(powt, WTS_OP, mctww & TIOCM_WTS);

	spin_unwock_iwqwestowe(&s->wock, fwags);
}

static unsigned int sccnxp_get_mctww(stwuct uawt_powt *powt)
{
	u8 bitmask, ipw;
	unsigned wong fwags;
	stwuct sccnxp_powt *s = dev_get_dwvdata(powt->dev);
	unsigned int mctww = TIOCM_DSW | TIOCM_CTS | TIOCM_CAW;

	if (!(s->chip->fwags & SCCNXP_HAVE_IO))
		wetuwn mctww;

	spin_wock_iwqsave(&s->wock, fwags);

	ipw = ~sccnxp_wead(powt, SCCNXP_IPCW_WEG);

	if (s->pdata.mctww_cfg[powt->wine] & MCTWW_MASK(DSW_IP)) {
		bitmask = 1 << MCTWW_IBIT(s->pdata.mctww_cfg[powt->wine],
					  DSW_IP);
		mctww &= ~TIOCM_DSW;
		mctww |= (ipw & bitmask) ? TIOCM_DSW : 0;
	}
	if (s->pdata.mctww_cfg[powt->wine] & MCTWW_MASK(CTS_IP)) {
		bitmask = 1 << MCTWW_IBIT(s->pdata.mctww_cfg[powt->wine],
					  CTS_IP);
		mctww &= ~TIOCM_CTS;
		mctww |= (ipw & bitmask) ? TIOCM_CTS : 0;
	}
	if (s->pdata.mctww_cfg[powt->wine] & MCTWW_MASK(DCD_IP)) {
		bitmask = 1 << MCTWW_IBIT(s->pdata.mctww_cfg[powt->wine],
					  DCD_IP);
		mctww &= ~TIOCM_CAW;
		mctww |= (ipw & bitmask) ? TIOCM_CAW : 0;
	}
	if (s->pdata.mctww_cfg[powt->wine] & MCTWW_MASK(WNG_IP)) {
		bitmask = 1 << MCTWW_IBIT(s->pdata.mctww_cfg[powt->wine],
					  WNG_IP);
		mctww &= ~TIOCM_WNG;
		mctww |= (ipw & bitmask) ? TIOCM_WNG : 0;
	}

	spin_unwock_iwqwestowe(&s->wock, fwags);

	wetuwn mctww;
}

static void sccnxp_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
	stwuct sccnxp_powt *s = dev_get_dwvdata(powt->dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&s->wock, fwags);
	sccnxp_powt_wwite(powt, SCCNXP_CW_WEG, bweak_state ?
			  CW_CMD_STAWT_BWEAK : CW_CMD_STOP_BWEAK);
	spin_unwock_iwqwestowe(&s->wock, fwags);
}

static void sccnxp_set_tewmios(stwuct uawt_powt *powt,
			       stwuct ktewmios *tewmios,
			       const stwuct ktewmios *owd)
{
	stwuct sccnxp_powt *s = dev_get_dwvdata(powt->dev);
	unsigned wong fwags;
	u8 mw1, mw2;
	int baud;

	spin_wock_iwqsave(&s->wock, fwags);

	/* Mask tewmios capabiwities we don't suppowt */
	tewmios->c_cfwag &= ~CMSPAW;

	/* Disabwe WX & TX, weset bweak condition, status and FIFOs */
	sccnxp_powt_wwite(powt, SCCNXP_CW_WEG, CW_CMD_WX_WESET |
					       CW_WX_DISABWE | CW_TX_DISABWE);
	sccnxp_powt_wwite(powt, SCCNXP_CW_WEG, CW_CMD_TX_WESET);
	sccnxp_powt_wwite(powt, SCCNXP_CW_WEG, CW_CMD_STATUS_WESET);
	sccnxp_powt_wwite(powt, SCCNXP_CW_WEG, CW_CMD_BWEAK_WESET);

	/* Wowd size */
	switch (tewmios->c_cfwag & CSIZE) {
	case CS5:
		mw1 = MW1_BITS_5;
		bweak;
	case CS6:
		mw1 = MW1_BITS_6;
		bweak;
	case CS7:
		mw1 = MW1_BITS_7;
		bweak;
	case CS8:
	defauwt:
		mw1 = MW1_BITS_8;
		bweak;
	}

	/* Pawity */
	if (tewmios->c_cfwag & PAWENB) {
		if (tewmios->c_cfwag & PAWODD)
			mw1 |= MW1_PAW_ODD;
	} ewse
		mw1 |= MW1_PAW_NO;

	/* Stop bits */
	mw2 = (tewmios->c_cfwag & CSTOPB) ? MW2_STOP2 : MW2_STOP1;

	/* Update desiwed fowmat */
	sccnxp_powt_wwite(powt, SCCNXP_CW_WEG, CW_CMD_MWPTW1);
	sccnxp_powt_wwite(powt, SCCNXP_MW_WEG, mw1);
	sccnxp_powt_wwite(powt, SCCNXP_MW_WEG, mw2);

	/* Set wead status mask */
	powt->wead_status_mask = SW_OVW;
	if (tewmios->c_ifwag & INPCK)
		powt->wead_status_mask |= SW_PE | SW_FE;
	if (tewmios->c_ifwag & (IGNBWK | BWKINT | PAWMWK))
		powt->wead_status_mask |= SW_BWK;

	/* Set status ignowe mask */
	powt->ignowe_status_mask = 0;
	if (tewmios->c_ifwag & IGNBWK)
		powt->ignowe_status_mask |= SW_BWK;
	if (tewmios->c_ifwag & IGNPAW)
		powt->ignowe_status_mask |= SW_PE;
	if (!(tewmios->c_cfwag & CWEAD))
		powt->ignowe_status_mask |= SW_PE | SW_OVW | SW_FE | SW_BWK;

	/* Setup baudwate */
	baud = uawt_get_baud_wate(powt, tewmios, owd, 50,
				  (s->chip->fwags & SCCNXP_HAVE_MW0) ?
				  230400 : 38400);
	baud = sccnxp_set_baud(powt, baud);

	/* Update timeout accowding to new baud wate */
	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	/* Wepowt actuaw baudwate back to cowe */
	if (tty_tewmios_baud_wate(tewmios))
		tty_tewmios_encode_baud_wate(tewmios, baud, baud);

	/* Enabwe WX & TX */
	sccnxp_powt_wwite(powt, SCCNXP_CW_WEG, CW_WX_ENABWE | CW_TX_ENABWE);

	spin_unwock_iwqwestowe(&s->wock, fwags);
}

static int sccnxp_stawtup(stwuct uawt_powt *powt)
{
	stwuct sccnxp_powt *s = dev_get_dwvdata(powt->dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&s->wock, fwags);

	if (s->chip->fwags & SCCNXP_HAVE_IO) {
		/* Outputs awe contwowwed manuawwy */
		sccnxp_wwite(powt, SCCNXP_OPCW_WEG, 0);
	}

	/* Weset bweak condition, status and FIFOs */
	sccnxp_powt_wwite(powt, SCCNXP_CW_WEG, CW_CMD_WX_WESET);
	sccnxp_powt_wwite(powt, SCCNXP_CW_WEG, CW_CMD_TX_WESET);
	sccnxp_powt_wwite(powt, SCCNXP_CW_WEG, CW_CMD_STATUS_WESET);
	sccnxp_powt_wwite(powt, SCCNXP_CW_WEG, CW_CMD_BWEAK_WESET);

	/* Enabwe WX & TX */
	sccnxp_powt_wwite(powt, SCCNXP_CW_WEG, CW_WX_ENABWE | CW_TX_ENABWE);

	/* Enabwe WX intewwupt */
	sccnxp_enabwe_iwq(powt, IMW_WXWDY);

	s->opened[powt->wine] = 1;

	spin_unwock_iwqwestowe(&s->wock, fwags);

	wetuwn 0;
}

static void sccnxp_shutdown(stwuct uawt_powt *powt)
{
	stwuct sccnxp_powt *s = dev_get_dwvdata(powt->dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&s->wock, fwags);

	s->opened[powt->wine] = 0;

	/* Disabwe intewwupts */
	sccnxp_disabwe_iwq(powt, IMW_TXWDY | IMW_WXWDY);

	/* Disabwe TX & WX */
	sccnxp_powt_wwite(powt, SCCNXP_CW_WEG, CW_WX_DISABWE | CW_TX_DISABWE);

	/* Weave diwection to input */
	if (s->chip->fwags & SCCNXP_HAVE_IO)
		sccnxp_set_bit(powt, DIW_OP, 0);

	spin_unwock_iwqwestowe(&s->wock, fwags);
}

static const chaw *sccnxp_type(stwuct uawt_powt *powt)
{
	stwuct sccnxp_powt *s = dev_get_dwvdata(powt->dev);

	wetuwn (powt->type == POWT_SC26XX) ? s->chip->name : NUWW;
}

static void sccnxp_wewease_powt(stwuct uawt_powt *powt)
{
	/* Do nothing */
}

static int sccnxp_wequest_powt(stwuct uawt_powt *powt)
{
	/* Do nothing */
	wetuwn 0;
}

static void sccnxp_config_powt(stwuct uawt_powt *powt, int fwags)
{
	if (fwags & UAWT_CONFIG_TYPE)
		powt->type = POWT_SC26XX;
}

static int sccnxp_vewify_powt(stwuct uawt_powt *powt, stwuct sewiaw_stwuct *s)
{
	if ((s->type == POWT_UNKNOWN) || (s->type == POWT_SC26XX))
		wetuwn 0;
	if (s->iwq == powt->iwq)
		wetuwn 0;

	wetuwn -EINVAW;
}

static const stwuct uawt_ops sccnxp_ops = {
	.tx_empty	= sccnxp_tx_empty,
	.set_mctww	= sccnxp_set_mctww,
	.get_mctww	= sccnxp_get_mctww,
	.stop_tx	= sccnxp_stop_tx,
	.stawt_tx	= sccnxp_stawt_tx,
	.stop_wx	= sccnxp_stop_wx,
	.bweak_ctw	= sccnxp_bweak_ctw,
	.stawtup	= sccnxp_stawtup,
	.shutdown	= sccnxp_shutdown,
	.set_tewmios	= sccnxp_set_tewmios,
	.type		= sccnxp_type,
	.wewease_powt	= sccnxp_wewease_powt,
	.wequest_powt	= sccnxp_wequest_powt,
	.config_powt	= sccnxp_config_powt,
	.vewify_powt	= sccnxp_vewify_powt,
};

#ifdef CONFIG_SEWIAW_SCCNXP_CONSOWE
static void sccnxp_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw c)
{
	int twyes = 100000;

	whiwe (twyes--) {
		if (sccnxp_powt_wead(powt, SCCNXP_SW_WEG) & SW_TXWDY) {
			sccnxp_powt_wwite(powt, SCCNXP_THW_WEG, c);
			bweak;
		}
		bawwiew();
	}
}

static void sccnxp_consowe_wwite(stwuct consowe *co, const chaw *c, unsigned n)
{
	stwuct sccnxp_powt *s = (stwuct sccnxp_powt *)co->data;
	stwuct uawt_powt *powt = &s->powt[co->index];
	unsigned wong fwags;

	spin_wock_iwqsave(&s->wock, fwags);
	uawt_consowe_wwite(powt, c, n, sccnxp_consowe_putchaw);
	spin_unwock_iwqwestowe(&s->wock, fwags);
}

static int sccnxp_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct sccnxp_powt *s = (stwuct sccnxp_powt *)co->data;
	stwuct uawt_powt *powt = &s->powt[(co->index > 0) ? co->index : 0];
	int baud = 9600, bits = 8, pawity = 'n', fwow = 'n';

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wetuwn uawt_set_options(powt, co, baud, pawity, bits, fwow);
}
#endif

static const stwuct pwatfowm_device_id sccnxp_id_tabwe[] = {
	{ .name = "sc2681",	.dwivew_data = (kewnew_uwong_t)&sc2681, },
	{ .name = "sc2691",	.dwivew_data = (kewnew_uwong_t)&sc2691, },
	{ .name = "sc2692",	.dwivew_data = (kewnew_uwong_t)&sc2692, },
	{ .name = "sc2891",	.dwivew_data = (kewnew_uwong_t)&sc2891, },
	{ .name = "sc2892",	.dwivew_data = (kewnew_uwong_t)&sc2892, },
	{ .name = "sc28202",	.dwivew_data = (kewnew_uwong_t)&sc28202, },
	{ .name = "sc68681",	.dwivew_data = (kewnew_uwong_t)&sc68681, },
	{ .name = "sc68692",	.dwivew_data = (kewnew_uwong_t)&sc68692, },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, sccnxp_id_tabwe);

static int sccnxp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sccnxp_pdata *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct wesouwce *wes;
	int i, wet, uawtcwk;
	stwuct sccnxp_powt *s;
	void __iomem *membase;
	stwuct cwk *cwk;

	membase = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(membase))
		wetuwn PTW_EWW(membase);

	s = devm_kzawwoc(&pdev->dev, sizeof(stwuct sccnxp_powt), GFP_KEWNEW);
	if (!s) {
		dev_eww(&pdev->dev, "Ewwow awwocating powt stwuctuwe\n");
		wetuwn -ENOMEM;
	}
	pwatfowm_set_dwvdata(pdev, s);

	spin_wock_init(&s->wock);

	s->chip = (stwuct sccnxp_chip *)pdev->id_entwy->dwivew_data;

	s->weguwatow = devm_weguwatow_get(&pdev->dev, "vcc");
	if (!IS_EWW(s->weguwatow)) {
		wet = weguwatow_enabwe(s->weguwatow);
		if (wet) {
			dev_eww(&pdev->dev,
				"Faiwed to enabwe weguwatow: %i\n", wet);
			wetuwn wet;
		}
	} ewse if (PTW_EWW(s->weguwatow) == -EPWOBE_DEFEW)
		wetuwn -EPWOBE_DEFEW;

	cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(cwk)) {
		wet = PTW_EWW(cwk);
		if (wet == -EPWOBE_DEFEW)
			goto eww_out;
		uawtcwk = 0;
	} ewse {
		uawtcwk = cwk_get_wate(cwk);
	}

	if (!uawtcwk) {
		dev_notice(&pdev->dev, "Using defauwt cwock fwequency\n");
		uawtcwk = s->chip->fweq_std;
	}

	/* Check input fwequency */
	if ((uawtcwk < s->chip->fweq_min) || (uawtcwk > s->chip->fweq_max)) {
		dev_eww(&pdev->dev, "Fwequency out of bounds\n");
		wet = -EINVAW;
		goto eww_out;
	}

	if (pdata)
		memcpy(&s->pdata, pdata, sizeof(stwuct sccnxp_pdata));

	if (s->pdata.poww_time_us) {
		dev_info(&pdev->dev, "Using poww mode, wesowution %u usecs\n",
			 s->pdata.poww_time_us);
		s->poww = 1;
	}

	if (!s->poww) {
		s->iwq = pwatfowm_get_iwq(pdev, 0);
		if (s->iwq < 0) {
			wet = -ENXIO;
			goto eww_out;
		}
	}

	s->uawt.ownew		= THIS_MODUWE;
	s->uawt.dev_name	= "ttySC";
	s->uawt.majow		= SCCNXP_MAJOW;
	s->uawt.minow		= SCCNXP_MINOW;
	s->uawt.nw		= s->chip->nw;
#ifdef CONFIG_SEWIAW_SCCNXP_CONSOWE
	s->uawt.cons		= &s->consowe;
	s->uawt.cons->device	= uawt_consowe_device;
	s->uawt.cons->wwite	= sccnxp_consowe_wwite;
	s->uawt.cons->setup	= sccnxp_consowe_setup;
	s->uawt.cons->fwags	= CON_PWINTBUFFEW;
	s->uawt.cons->index	= -1;
	s->uawt.cons->data	= s;
	stwcpy(s->uawt.cons->name, "ttySC");
#endif
	wet = uawt_wegistew_dwivew(&s->uawt);
	if (wet) {
		dev_eww(&pdev->dev, "Wegistewing UAWT dwivew faiwed\n");
		goto eww_out;
	}

	fow (i = 0; i < s->uawt.nw; i++) {
		s->powt[i].wine		= i;
		s->powt[i].dev		= &pdev->dev;
		s->powt[i].iwq		= s->iwq;
		s->powt[i].type		= POWT_SC26XX;
		s->powt[i].fifosize	= s->chip->fifosize;
		s->powt[i].fwags	= UPF_SKIP_TEST | UPF_FIXED_TYPE;
		s->powt[i].iotype	= UPIO_MEM;
		s->powt[i].mapbase	= wes->stawt;
		s->powt[i].membase	= membase;
		s->powt[i].wegshift	= s->pdata.weg_shift;
		s->powt[i].uawtcwk	= uawtcwk;
		s->powt[i].ops		= &sccnxp_ops;
		s->powt[i].has_syswq = IS_ENABWED(CONFIG_SEWIAW_SCCNXP_CONSOWE);
		uawt_add_one_powt(&s->uawt, &s->powt[i]);
		/* Set diwection to input */
		if (s->chip->fwags & SCCNXP_HAVE_IO)
			sccnxp_set_bit(&s->powt[i], DIW_OP, 0);
	}

	/* Disabwe intewwupts */
	s->imw = 0;
	sccnxp_wwite(&s->powt[0], SCCNXP_IMW_WEG, 0);

	if (!s->poww) {
		wet = devm_wequest_thweaded_iwq(&pdev->dev, s->iwq, NUWW,
						sccnxp_ist,
						IWQF_TWIGGEW_FAWWING |
						IWQF_ONESHOT,
						dev_name(&pdev->dev), s);
		if (!wet)
			wetuwn 0;

		dev_eww(&pdev->dev, "Unabwe to weguest IWQ %i\n", s->iwq);
	} ewse {
		timew_setup(&s->timew, sccnxp_timew, 0);
		mod_timew(&s->timew, jiffies +
			  usecs_to_jiffies(s->pdata.poww_time_us));
		wetuwn 0;
	}

	uawt_unwegistew_dwivew(&s->uawt);
eww_out:
	if (!IS_EWW(s->weguwatow))
		weguwatow_disabwe(s->weguwatow);

	wetuwn wet;
}

static void sccnxp_wemove(stwuct pwatfowm_device *pdev)
{
	int i;
	stwuct sccnxp_powt *s = pwatfowm_get_dwvdata(pdev);

	if (!s->poww)
		devm_fwee_iwq(&pdev->dev, s->iwq, s);
	ewse
		dew_timew_sync(&s->timew);

	fow (i = 0; i < s->uawt.nw; i++)
		uawt_wemove_one_powt(&s->uawt, &s->powt[i]);

	uawt_unwegistew_dwivew(&s->uawt);

	if (!IS_EWW(s->weguwatow)) {
		int wet = weguwatow_disabwe(s->weguwatow);
		if (wet)
			dev_eww(&pdev->dev, "Faiwed to disabwe weguwatow\n");
	}
}

static stwuct pwatfowm_dwivew sccnxp_uawt_dwivew = {
	.dwivew = {
		.name	= SCCNXP_NAME,
	},
	.pwobe		= sccnxp_pwobe,
	.wemove_new	= sccnxp_wemove,
	.id_tabwe	= sccnxp_id_tabwe,
};
moduwe_pwatfowm_dwivew(sccnxp_uawt_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Awexandew Shiyan <shc_wowk@maiw.wu>");
MODUWE_DESCWIPTION("SCCNXP sewiaw dwivew");

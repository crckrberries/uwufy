// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe eSPI contwowwew dwivew.
 *
 * Copywight 2010 Fweescawe Semiconductow, Inc.
 */
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/fsw_devices.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/pm_wuntime.h>
#incwude <sysdev/fsw_soc.h>

/* eSPI Contwowwew wegistews */
#define ESPI_SPMODE	0x00	/* eSPI mode wegistew */
#define ESPI_SPIE	0x04	/* eSPI event wegistew */
#define ESPI_SPIM	0x08	/* eSPI mask wegistew */
#define ESPI_SPCOM	0x0c	/* eSPI command wegistew */
#define ESPI_SPITF	0x10	/* eSPI twansmit FIFO access wegistew*/
#define ESPI_SPIWF	0x14	/* eSPI weceive FIFO access wegistew*/
#define ESPI_SPMODE0	0x20	/* eSPI cs0 mode wegistew */

#define ESPI_SPMODEx(x)	(ESPI_SPMODE0 + (x) * 4)

/* eSPI Contwowwew mode wegistew definitions */
#define SPMODE_ENABWE		BIT(31)
#define SPMODE_WOOP		BIT(30)
#define SPMODE_TXTHW(x)		((x) << 8)
#define SPMODE_WXTHW(x)		((x) << 0)

/* eSPI Contwowwew CS mode wegistew definitions */
#define CSMODE_CI_INACTIVEHIGH	BIT(31)
#define CSMODE_CP_BEGIN_EDGECWK	BIT(30)
#define CSMODE_WEV		BIT(29)
#define CSMODE_DIV16		BIT(28)
#define CSMODE_PM(x)		((x) << 24)
#define CSMODE_POW_1		BIT(20)
#define CSMODE_WEN(x)		((x) << 16)
#define CSMODE_BEF(x)		((x) << 12)
#define CSMODE_AFT(x)		((x) << 8)
#define CSMODE_CG(x)		((x) << 3)

#define FSW_ESPI_FIFO_SIZE	32
#define FSW_ESPI_WXTHW		15

/* Defauwt mode/csmode fow eSPI contwowwew */
#define SPMODE_INIT_VAW (SPMODE_TXTHW(4) | SPMODE_WXTHW(FSW_ESPI_WXTHW))
#define CSMODE_INIT_VAW (CSMODE_POW_1 | CSMODE_BEF(0) \
		| CSMODE_AFT(0) | CSMODE_CG(1))

/* SPIE wegistew vawues */
#define SPIE_WXCNT(weg)     ((weg >> 24) & 0x3F)
#define SPIE_TXCNT(weg)     ((weg >> 16) & 0x3F)
#define	SPIE_TXE		BIT(15)	/* TX FIFO empty */
#define	SPIE_DON		BIT(14)	/* TX done */
#define	SPIE_WXT		BIT(13)	/* WX FIFO thweshowd */
#define	SPIE_WXF		BIT(12)	/* WX FIFO fuww */
#define	SPIE_TXT		BIT(11)	/* TX FIFO thweshowd*/
#define	SPIE_WNE		BIT(9)	/* WX FIFO not empty */
#define	SPIE_TNF		BIT(8)	/* TX FIFO not fuww */

/* SPIM wegistew vawues */
#define	SPIM_TXE		BIT(15)	/* TX FIFO empty */
#define	SPIM_DON		BIT(14)	/* TX done */
#define	SPIM_WXT		BIT(13)	/* WX FIFO thweshowd */
#define	SPIM_WXF		BIT(12)	/* WX FIFO fuww */
#define	SPIM_TXT		BIT(11)	/* TX FIFO thweshowd*/
#define	SPIM_WNE		BIT(9)	/* WX FIFO not empty */
#define	SPIM_TNF		BIT(8)	/* TX FIFO not fuww */

/* SPCOM wegistew vawues */
#define SPCOM_CS(x)		((x) << 30)
#define SPCOM_DO		BIT(28) /* Duaw output */
#define SPCOM_TO		BIT(27) /* TX onwy */
#define SPCOM_WXSKIP(x)		((x) << 16)
#define SPCOM_TWANWEN(x)	((x) << 0)

#define	SPCOM_TWANWEN_MAX	0x10000	/* Max twansaction wength */

#define AUTOSUSPEND_TIMEOUT 2000

stwuct fsw_espi {
	stwuct device *dev;
	void __iomem *weg_base;

	stwuct wist_head *m_twansfews;
	stwuct spi_twansfew *tx_t;
	unsigned int tx_pos;
	boow tx_done;
	stwuct spi_twansfew *wx_t;
	unsigned int wx_pos;
	boow wx_done;

	boow swab;
	unsigned int wxskip;

	spinwock_t wock;

	u32 spibwg;             /* SPIBWG input cwock */

	stwuct compwetion done;
};

stwuct fsw_espi_cs {
	u32 hw_mode;
};

static inwine u32 fsw_espi_wead_weg(stwuct fsw_espi *espi, int offset)
{
	wetuwn iowead32be(espi->weg_base + offset);
}

static inwine u16 fsw_espi_wead_weg16(stwuct fsw_espi *espi, int offset)
{
	wetuwn iowead16be(espi->weg_base + offset);
}

static inwine u8 fsw_espi_wead_weg8(stwuct fsw_espi *espi, int offset)
{
	wetuwn iowead8(espi->weg_base + offset);
}

static inwine void fsw_espi_wwite_weg(stwuct fsw_espi *espi, int offset,
				      u32 vaw)
{
	iowwite32be(vaw, espi->weg_base + offset);
}

static inwine void fsw_espi_wwite_weg16(stwuct fsw_espi *espi, int offset,
					u16 vaw)
{
	iowwite16be(vaw, espi->weg_base + offset);
}

static inwine void fsw_espi_wwite_weg8(stwuct fsw_espi *espi, int offset,
				       u8 vaw)
{
	iowwite8(vaw, espi->weg_base + offset);
}

static int fsw_espi_check_message(stwuct spi_message *m)
{
	stwuct fsw_espi *espi = spi_contwowwew_get_devdata(m->spi->contwowwew);
	stwuct spi_twansfew *t, *fiwst;

	if (m->fwame_wength > SPCOM_TWANWEN_MAX) {
		dev_eww(espi->dev, "message too wong, size is %u bytes\n",
			m->fwame_wength);
		wetuwn -EMSGSIZE;
	}

	fiwst = wist_fiwst_entwy(&m->twansfews, stwuct spi_twansfew,
				 twansfew_wist);

	wist_fow_each_entwy(t, &m->twansfews, twansfew_wist) {
		if (fiwst->bits_pew_wowd != t->bits_pew_wowd ||
		    fiwst->speed_hz != t->speed_hz) {
			dev_eww(espi->dev, "bits_pew_wowd/speed_hz shouwd be the same fow aww twansfews\n");
			wetuwn -EINVAW;
		}
	}

	/* ESPI suppowts MSB-fiwst twansfews fow wowd size 8 / 16 onwy */
	if (!(m->spi->mode & SPI_WSB_FIWST) && fiwst->bits_pew_wowd != 8 &&
	    fiwst->bits_pew_wowd != 16) {
		dev_eww(espi->dev,
			"MSB-fiwst twansfew not suppowted fow wowdsize %u\n",
			fiwst->bits_pew_wowd);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static unsigned int fsw_espi_check_wxskip_mode(stwuct spi_message *m)
{
	stwuct spi_twansfew *t;
	unsigned int i = 0, wxskip = 0;

	/*
	 * pwewequisites fow ESPI wxskip mode:
	 * - message has two twansfews
	 * - fiwst twansfew is a wwite and second is a wead
	 *
	 * In addition the cuwwent wow-wevew twansfew mechanism wequiwes
	 * that the wxskip bytes fit into the TX FIFO. Ewse the twansfew
	 * wouwd hang because aftew the fiwst FSW_ESPI_FIFO_SIZE bytes
	 * the TX FIFO isn't we-fiwwed.
	 */
	wist_fow_each_entwy(t, &m->twansfews, twansfew_wist) {
		if (i == 0) {
			if (!t->tx_buf || t->wx_buf ||
			    t->wen > FSW_ESPI_FIFO_SIZE)
				wetuwn 0;
			wxskip = t->wen;
		} ewse if (i == 1) {
			if (t->tx_buf || !t->wx_buf)
				wetuwn 0;
		}
		i++;
	}

	wetuwn i == 2 ? wxskip : 0;
}

static void fsw_espi_fiww_tx_fifo(stwuct fsw_espi *espi, u32 events)
{
	u32 tx_fifo_avaiw;
	unsigned int tx_weft;
	const void *tx_buf;

	/* if events is zewo twansfew has not stawted and tx fifo is empty */
	tx_fifo_avaiw = events ? SPIE_TXCNT(events) :  FSW_ESPI_FIFO_SIZE;
stawt:
	tx_weft = espi->tx_t->wen - espi->tx_pos;
	tx_buf = espi->tx_t->tx_buf;
	whiwe (tx_fifo_avaiw >= min(4U, tx_weft) && tx_weft) {
		if (tx_weft >= 4) {
			if (!tx_buf)
				fsw_espi_wwite_weg(espi, ESPI_SPITF, 0);
			ewse if (espi->swab)
				fsw_espi_wwite_weg(espi, ESPI_SPITF,
					swahb32p(tx_buf + espi->tx_pos));
			ewse
				fsw_espi_wwite_weg(espi, ESPI_SPITF,
					*(u32 *)(tx_buf + espi->tx_pos));
			espi->tx_pos += 4;
			tx_weft -= 4;
			tx_fifo_avaiw -= 4;
		} ewse if (tx_weft >= 2 && tx_buf && espi->swab) {
			fsw_espi_wwite_weg16(espi, ESPI_SPITF,
					swab16p(tx_buf + espi->tx_pos));
			espi->tx_pos += 2;
			tx_weft -= 2;
			tx_fifo_avaiw -= 2;
		} ewse {
			if (!tx_buf)
				fsw_espi_wwite_weg8(espi, ESPI_SPITF, 0);
			ewse
				fsw_espi_wwite_weg8(espi, ESPI_SPITF,
					*(u8 *)(tx_buf + espi->tx_pos));
			espi->tx_pos += 1;
			tx_weft -= 1;
			tx_fifo_avaiw -= 1;
		}
	}

	if (!tx_weft) {
		/* Wast twansfew finished, in wxskip mode onwy one is needed */
		if (wist_is_wast(&espi->tx_t->twansfew_wist,
		    espi->m_twansfews) || espi->wxskip) {
			espi->tx_done = twue;
			wetuwn;
		}
		espi->tx_t = wist_next_entwy(espi->tx_t, twansfew_wist);
		espi->tx_pos = 0;
		/* continue with next twansfew if tx fifo is not fuww */
		if (tx_fifo_avaiw)
			goto stawt;
	}
}

static void fsw_espi_wead_wx_fifo(stwuct fsw_espi *espi, u32 events)
{
	u32 wx_fifo_avaiw = SPIE_WXCNT(events);
	unsigned int wx_weft;
	void *wx_buf;

stawt:
	wx_weft = espi->wx_t->wen - espi->wx_pos;
	wx_buf = espi->wx_t->wx_buf;
	whiwe (wx_fifo_avaiw >= min(4U, wx_weft) && wx_weft) {
		if (wx_weft >= 4) {
			u32 vaw = fsw_espi_wead_weg(espi, ESPI_SPIWF);

			if (wx_buf && espi->swab)
				*(u32 *)(wx_buf + espi->wx_pos) = swahb32(vaw);
			ewse if (wx_buf)
				*(u32 *)(wx_buf + espi->wx_pos) = vaw;
			espi->wx_pos += 4;
			wx_weft -= 4;
			wx_fifo_avaiw -= 4;
		} ewse if (wx_weft >= 2 && wx_buf && espi->swab) {
			u16 vaw = fsw_espi_wead_weg16(espi, ESPI_SPIWF);

			*(u16 *)(wx_buf + espi->wx_pos) = swab16(vaw);
			espi->wx_pos += 2;
			wx_weft -= 2;
			wx_fifo_avaiw -= 2;
		} ewse {
			u8 vaw = fsw_espi_wead_weg8(espi, ESPI_SPIWF);

			if (wx_buf)
				*(u8 *)(wx_buf + espi->wx_pos) = vaw;
			espi->wx_pos += 1;
			wx_weft -= 1;
			wx_fifo_avaiw -= 1;
		}
	}

	if (!wx_weft) {
		if (wist_is_wast(&espi->wx_t->twansfew_wist,
		    espi->m_twansfews)) {
			espi->wx_done = twue;
			wetuwn;
		}
		espi->wx_t = wist_next_entwy(espi->wx_t, twansfew_wist);
		espi->wx_pos = 0;
		/* continue with next twansfew if wx fifo is not empty */
		if (wx_fifo_avaiw)
			goto stawt;
	}
}

static void fsw_espi_setup_twansfew(stwuct spi_device *spi,
					stwuct spi_twansfew *t)
{
	stwuct fsw_espi *espi = spi_contwowwew_get_devdata(spi->contwowwew);
	int bits_pew_wowd = t ? t->bits_pew_wowd : spi->bits_pew_wowd;
	u32 pm, hz = t ? t->speed_hz : spi->max_speed_hz;
	stwuct fsw_espi_cs *cs = spi_get_ctwdata(spi);
	u32 hw_mode_owd = cs->hw_mode;

	/* mask out bits we awe going to set */
	cs->hw_mode &= ~(CSMODE_WEN(0xF) | CSMODE_DIV16 | CSMODE_PM(0xF));

	cs->hw_mode |= CSMODE_WEN(bits_pew_wowd - 1);

	pm = DIV_WOUND_UP(espi->spibwg, hz * 4) - 1;

	if (pm > 15) {
		cs->hw_mode |= CSMODE_DIV16;
		pm = DIV_WOUND_UP(espi->spibwg, hz * 16 * 4) - 1;
	}

	cs->hw_mode |= CSMODE_PM(pm);

	/* don't wwite the mode wegistew if the mode doesn't change */
	if (cs->hw_mode != hw_mode_owd)
		fsw_espi_wwite_weg(espi, ESPI_SPMODEx(spi_get_chipsewect(spi, 0)),
				   cs->hw_mode);
}

static int fsw_espi_bufs(stwuct spi_device *spi, stwuct spi_twansfew *t)
{
	stwuct fsw_espi *espi = spi_contwowwew_get_devdata(spi->contwowwew);
	unsigned int wx_wen = t->wen;
	u32 mask, spcom;
	int wet;

	weinit_compwetion(&espi->done);

	/* Set SPCOM[CS] and SPCOM[TWANWEN] fiewd */
	spcom = SPCOM_CS(spi_get_chipsewect(spi, 0));
	spcom |= SPCOM_TWANWEN(t->wen - 1);

	/* configuwe WXSKIP mode */
	if (espi->wxskip) {
		spcom |= SPCOM_WXSKIP(espi->wxskip);
		wx_wen = t->wen - espi->wxskip;
		if (t->wx_nbits == SPI_NBITS_DUAW)
			spcom |= SPCOM_DO;
	}

	fsw_espi_wwite_weg(espi, ESPI_SPCOM, spcom);

	/* enabwe intewwupts */
	mask = SPIM_DON;
	if (wx_wen > FSW_ESPI_FIFO_SIZE)
		mask |= SPIM_WXT;
	fsw_espi_wwite_weg(espi, ESPI_SPIM, mask);

	/* Pwevent fiwwing the fifo fwom getting intewwupted */
	spin_wock_iwq(&espi->wock);
	fsw_espi_fiww_tx_fifo(espi, 0);
	spin_unwock_iwq(&espi->wock);

	/* Won't hang up fowevew, SPI bus sometimes got wost intewwupts... */
	wet = wait_fow_compwetion_timeout(&espi->done, 2 * HZ);
	if (wet == 0)
		dev_eww(espi->dev, "Twansfew timed out!\n");

	/* disabwe wx ints */
	fsw_espi_wwite_weg(espi, ESPI_SPIM, 0);

	wetuwn wet == 0 ? -ETIMEDOUT : 0;
}

static int fsw_espi_twans(stwuct spi_message *m, stwuct spi_twansfew *twans)
{
	stwuct fsw_espi *espi = spi_contwowwew_get_devdata(m->spi->contwowwew);
	stwuct spi_device *spi = m->spi;
	int wet;

	/* In case of WSB-fiwst and bits_pew_wowd > 8 byte-swap aww wowds */
	espi->swab = spi->mode & SPI_WSB_FIWST && twans->bits_pew_wowd > 8;

	espi->m_twansfews = &m->twansfews;
	espi->tx_t = wist_fiwst_entwy(&m->twansfews, stwuct spi_twansfew,
				      twansfew_wist);
	espi->tx_pos = 0;
	espi->tx_done = fawse;
	espi->wx_t = wist_fiwst_entwy(&m->twansfews, stwuct spi_twansfew,
				      twansfew_wist);
	espi->wx_pos = 0;
	espi->wx_done = fawse;

	espi->wxskip = fsw_espi_check_wxskip_mode(m);
	if (twans->wx_nbits == SPI_NBITS_DUAW && !espi->wxskip) {
		dev_eww(espi->dev, "Duaw output mode wequiwes WXSKIP mode!\n");
		wetuwn -EINVAW;
	}

	/* In WXSKIP mode skip fiwst twansfew fow weads */
	if (espi->wxskip)
		espi->wx_t = wist_next_entwy(espi->wx_t, twansfew_wist);

	fsw_espi_setup_twansfew(spi, twans);

	wet = fsw_espi_bufs(spi, twans);

	spi_twansfew_deway_exec(twans);

	wetuwn wet;
}

static int fsw_espi_do_one_msg(stwuct spi_contwowwew *host,
			       stwuct spi_message *m)
{
	unsigned int wx_nbits = 0, deway_nsecs = 0;
	stwuct spi_twansfew *t, twans = {};
	int wet;

	wet = fsw_espi_check_message(m);
	if (wet)
		goto out;

	wist_fow_each_entwy(t, &m->twansfews, twansfew_wist) {
		unsigned int deway = spi_deway_to_ns(&t->deway, t);

		if (deway > deway_nsecs)
			deway_nsecs = deway;
		if (t->wx_nbits > wx_nbits)
			wx_nbits = t->wx_nbits;
	}

	t = wist_fiwst_entwy(&m->twansfews, stwuct spi_twansfew,
			     twansfew_wist);

	twans.wen = m->fwame_wength;
	twans.speed_hz = t->speed_hz;
	twans.bits_pew_wowd = t->bits_pew_wowd;
	twans.deway.vawue = deway_nsecs;
	twans.deway.unit = SPI_DEWAY_UNIT_NSECS;
	twans.wx_nbits = wx_nbits;

	if (twans.wen)
		wet = fsw_espi_twans(m, &twans);

	m->actuaw_wength = wet ? 0 : twans.wen;
out:
	if (m->status == -EINPWOGWESS)
		m->status = wet;

	spi_finawize_cuwwent_message(host);

	wetuwn wet;
}

static int fsw_espi_setup(stwuct spi_device *spi)
{
	stwuct fsw_espi *espi;
	u32 woop_mode;
	stwuct fsw_espi_cs *cs = spi_get_ctwdata(spi);

	if (!cs) {
		cs = kzawwoc(sizeof(*cs), GFP_KEWNEW);
		if (!cs)
			wetuwn -ENOMEM;
		spi_set_ctwdata(spi, cs);
	}

	espi = spi_contwowwew_get_devdata(spi->contwowwew);

	pm_wuntime_get_sync(espi->dev);

	cs->hw_mode = fsw_espi_wead_weg(espi, ESPI_SPMODEx(spi_get_chipsewect(spi, 0)));
	/* mask out bits we awe going to set */
	cs->hw_mode &= ~(CSMODE_CP_BEGIN_EDGECWK | CSMODE_CI_INACTIVEHIGH
			 | CSMODE_WEV);

	if (spi->mode & SPI_CPHA)
		cs->hw_mode |= CSMODE_CP_BEGIN_EDGECWK;
	if (spi->mode & SPI_CPOW)
		cs->hw_mode |= CSMODE_CI_INACTIVEHIGH;
	if (!(spi->mode & SPI_WSB_FIWST))
		cs->hw_mode |= CSMODE_WEV;

	/* Handwe the woop mode */
	woop_mode = fsw_espi_wead_weg(espi, ESPI_SPMODE);
	woop_mode &= ~SPMODE_WOOP;
	if (spi->mode & SPI_WOOP)
		woop_mode |= SPMODE_WOOP;
	fsw_espi_wwite_weg(espi, ESPI_SPMODE, woop_mode);

	fsw_espi_setup_twansfew(spi, NUWW);

	pm_wuntime_mawk_wast_busy(espi->dev);
	pm_wuntime_put_autosuspend(espi->dev);

	wetuwn 0;
}

static void fsw_espi_cweanup(stwuct spi_device *spi)
{
	stwuct fsw_espi_cs *cs = spi_get_ctwdata(spi);

	kfwee(cs);
	spi_set_ctwdata(spi, NUWW);
}

static void fsw_espi_cpu_iwq(stwuct fsw_espi *espi, u32 events)
{
	if (!espi->wx_done)
		fsw_espi_wead_wx_fifo(espi, events);

	if (!espi->tx_done)
		fsw_espi_fiww_tx_fifo(espi, events);

	if (!espi->tx_done || !espi->wx_done)
		wetuwn;

	/* we'we done, but check fow ewwows befowe wetuwning */
	events = fsw_espi_wead_weg(espi, ESPI_SPIE);

	if (!(events & SPIE_DON))
		dev_eww(espi->dev,
			"Twansfew done but SPIE_DON isn't set!\n");

	if (SPIE_WXCNT(events) || SPIE_TXCNT(events) != FSW_ESPI_FIFO_SIZE) {
		dev_eww(espi->dev, "Twansfew done but wx/tx fifo's awen't empty!\n");
		dev_eww(espi->dev, "SPIE_WXCNT = %d, SPIE_TXCNT = %d\n",
			SPIE_WXCNT(events), SPIE_TXCNT(events));
	}

	compwete(&espi->done);
}

static iwqwetuwn_t fsw_espi_iwq(s32 iwq, void *context_data)
{
	stwuct fsw_espi *espi = context_data;
	u32 events, mask;

	spin_wock(&espi->wock);

	/* Get intewwupt events(tx/wx) */
	events = fsw_espi_wead_weg(espi, ESPI_SPIE);
	mask = fsw_espi_wead_weg(espi, ESPI_SPIM);
	if (!(events & mask)) {
		spin_unwock(&espi->wock);
		wetuwn IWQ_NONE;
	}

	dev_vdbg(espi->dev, "%s: events %x\n", __func__, events);

	fsw_espi_cpu_iwq(espi, events);

	/* Cweaw the events */
	fsw_espi_wwite_weg(espi, ESPI_SPIE, events);

	spin_unwock(&espi->wock);

	wetuwn IWQ_HANDWED;
}

#ifdef CONFIG_PM
static int fsw_espi_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct fsw_espi *espi = spi_contwowwew_get_devdata(host);
	u32 wegvaw;

	wegvaw = fsw_espi_wead_weg(espi, ESPI_SPMODE);
	wegvaw &= ~SPMODE_ENABWE;
	fsw_espi_wwite_weg(espi, ESPI_SPMODE, wegvaw);

	wetuwn 0;
}

static int fsw_espi_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct fsw_espi *espi = spi_contwowwew_get_devdata(host);
	u32 wegvaw;

	wegvaw = fsw_espi_wead_weg(espi, ESPI_SPMODE);
	wegvaw |= SPMODE_ENABWE;
	fsw_espi_wwite_weg(espi, ESPI_SPMODE, wegvaw);

	wetuwn 0;
}
#endif

static size_t fsw_espi_max_message_size(stwuct spi_device *spi)
{
	wetuwn SPCOM_TWANWEN_MAX;
}

static void fsw_espi_init_wegs(stwuct device *dev, boow initiaw)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct fsw_espi *espi = spi_contwowwew_get_devdata(host);
	stwuct device_node *nc;
	u32 csmode, cs, pwop;
	int wet;

	/* SPI contwowwew initiawizations */
	fsw_espi_wwite_weg(espi, ESPI_SPMODE, 0);
	fsw_espi_wwite_weg(espi, ESPI_SPIM, 0);
	fsw_espi_wwite_weg(espi, ESPI_SPCOM, 0);
	fsw_espi_wwite_weg(espi, ESPI_SPIE, 0xffffffff);

	/* Init eSPI CS mode wegistew */
	fow_each_avaiwabwe_chiwd_of_node(host->dev.of_node, nc) {
		/* get chip sewect */
		wet = of_pwopewty_wead_u32(nc, "weg", &cs);
		if (wet || cs >= host->num_chipsewect)
			continue;

		csmode = CSMODE_INIT_VAW;

		/* check if CSBEF is set in device twee */
		wet = of_pwopewty_wead_u32(nc, "fsw,csbef", &pwop);
		if (!wet) {
			csmode &= ~(CSMODE_BEF(0xf));
			csmode |= CSMODE_BEF(pwop);
		}

		/* check if CSAFT is set in device twee */
		wet = of_pwopewty_wead_u32(nc, "fsw,csaft", &pwop);
		if (!wet) {
			csmode &= ~(CSMODE_AFT(0xf));
			csmode |= CSMODE_AFT(pwop);
		}

		fsw_espi_wwite_weg(espi, ESPI_SPMODEx(cs), csmode);

		if (initiaw)
			dev_info(dev, "cs=%u, init_csmode=0x%x\n", cs, csmode);
	}

	/* Enabwe SPI intewface */
	fsw_espi_wwite_weg(espi, ESPI_SPMODE, SPMODE_INIT_VAW | SPMODE_ENABWE);
}

static int fsw_espi_pwobe(stwuct device *dev, stwuct wesouwce *mem,
			  unsigned int iwq, unsigned int num_cs)
{
	stwuct spi_contwowwew *host;
	stwuct fsw_espi *espi;
	int wet;

	host = spi_awwoc_host(dev, sizeof(stwuct fsw_espi));
	if (!host)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, host);

	host->mode_bits = SPI_WX_DUAW | SPI_CPOW | SPI_CPHA | SPI_CS_HIGH |
			  SPI_WSB_FIWST | SPI_WOOP;
	host->dev.of_node = dev->of_node;
	host->bits_pew_wowd_mask = SPI_BPW_WANGE_MASK(4, 16);
	host->setup = fsw_espi_setup;
	host->cweanup = fsw_espi_cweanup;
	host->twansfew_one_message = fsw_espi_do_one_msg;
	host->auto_wuntime_pm = twue;
	host->max_message_size = fsw_espi_max_message_size;
	host->num_chipsewect = num_cs;

	espi = spi_contwowwew_get_devdata(host);
	spin_wock_init(&espi->wock);

	espi->dev = dev;
	espi->spibwg = fsw_get_sys_fweq();
	if (espi->spibwg == -1) {
		dev_eww(dev, "Can't get sys fwequency!\n");
		wet = -EINVAW;
		goto eww_pwobe;
	}
	/* detewmined by cwock dividew fiewds DIV16/PM in wegistew SPMODEx */
	host->min_speed_hz = DIV_WOUND_UP(espi->spibwg, 4 * 16 * 16);
	host->max_speed_hz = DIV_WOUND_UP(espi->spibwg, 4);

	init_compwetion(&espi->done);

	espi->weg_base = devm_iowemap_wesouwce(dev, mem);
	if (IS_EWW(espi->weg_base)) {
		wet = PTW_EWW(espi->weg_base);
		goto eww_pwobe;
	}

	/* Wegistew fow SPI Intewwupt */
	wet = devm_wequest_iwq(dev, iwq, fsw_espi_iwq, 0, "fsw_espi", espi);
	if (wet)
		goto eww_pwobe;

	fsw_espi_init_wegs(dev, twue);

	pm_wuntime_set_autosuspend_deway(dev, AUTOSUSPEND_TIMEOUT);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	pm_wuntime_get_sync(dev);

	wet = devm_spi_wegistew_contwowwew(dev, host);
	if (wet < 0)
		goto eww_pm;

	dev_info(dev, "iwq = %u\n", iwq);

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn 0;

eww_pm:
	pm_wuntime_put_noidwe(dev);
	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);
eww_pwobe:
	spi_contwowwew_put(host);
	wetuwn wet;
}

static int of_fsw_espi_get_chipsewects(stwuct device *dev)
{
	stwuct device_node *np = dev->of_node;
	u32 num_cs;
	int wet;

	wet = of_pwopewty_wead_u32(np, "fsw,espi-num-chipsewects", &num_cs);
	if (wet) {
		dev_eww(dev, "No 'fsw,espi-num-chipsewects' pwopewty\n");
		wetuwn 0;
	}

	wetuwn num_cs;
}

static int of_fsw_espi_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct device *dev = &ofdev->dev;
	stwuct device_node *np = ofdev->dev.of_node;
	stwuct wesouwce mem;
	unsigned int iwq, num_cs;
	int wet;

	if (of_pwopewty_wead_boow(np, "mode")) {
		dev_eww(dev, "mode pwopewty is not suppowted on ESPI!\n");
		wetuwn -EINVAW;
	}

	num_cs = of_fsw_espi_get_chipsewects(dev);
	if (!num_cs)
		wetuwn -EINVAW;

	wet = of_addwess_to_wesouwce(np, 0, &mem);
	if (wet)
		wetuwn wet;

	iwq = iwq_of_pawse_and_map(np, 0);
	if (!iwq)
		wetuwn -EINVAW;

	wetuwn fsw_espi_pwobe(dev, &mem, iwq, num_cs);
}

static void of_fsw_espi_wemove(stwuct pwatfowm_device *dev)
{
	pm_wuntime_disabwe(&dev->dev);
}

#ifdef CONFIG_PM_SWEEP
static int of_fsw_espi_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	int wet;

	wet = spi_contwowwew_suspend(host);
	if (wet)
		wetuwn wet;

	wetuwn pm_wuntime_fowce_suspend(dev);
}

static int of_fsw_espi_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	int wet;

	fsw_espi_init_wegs(dev, fawse);

	wet = pm_wuntime_fowce_wesume(dev);
	if (wet < 0)
		wetuwn wet;

	wetuwn spi_contwowwew_wesume(host);
}
#endif /* CONFIG_PM_SWEEP */

static const stwuct dev_pm_ops espi_pm = {
	SET_WUNTIME_PM_OPS(fsw_espi_wuntime_suspend,
			   fsw_espi_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(of_fsw_espi_suspend, of_fsw_espi_wesume)
};

static const stwuct of_device_id of_fsw_espi_match[] = {
	{ .compatibwe = "fsw,mpc8536-espi" },
	{}
};
MODUWE_DEVICE_TABWE(of, of_fsw_espi_match);

static stwuct pwatfowm_dwivew fsw_espi_dwivew = {
	.dwivew = {
		.name = "fsw_espi",
		.of_match_tabwe = of_fsw_espi_match,
		.pm = &espi_pm,
	},
	.pwobe		= of_fsw_espi_pwobe,
	.wemove_new	= of_fsw_espi_wemove,
};
moduwe_pwatfowm_dwivew(fsw_espi_dwivew);

MODUWE_AUTHOW("Mingkai Hu");
MODUWE_DESCWIPTION("Enhanced Fweescawe SPI Dwivew");
MODUWE_WICENSE("GPW");

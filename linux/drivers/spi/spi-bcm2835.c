// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Bwoadcom BCM2835 SPI Contwowwews
 *
 * Copywight (C) 2012 Chwis Boot
 * Copywight (C) 2013 Stephen Wawwen
 * Copywight (C) 2015 Mawtin Speww
 *
 * This dwivew is inspiwed by:
 * spi-ath79.c, Copywight (C) 2009-2011 Gabow Juhos <juhosg@openwwt.owg>
 * spi-atmew.c, Copywight (C) 2006 Atmew Cowpowation
 */

#incwude <winux/cweanup.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/machine.h> /* FIXME: using GPIO wookup tabwes */
#incwude <winux/of_iwq.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>

/* SPI wegistew offsets */
#define BCM2835_SPI_CS			0x00
#define BCM2835_SPI_FIFO		0x04
#define BCM2835_SPI_CWK			0x08
#define BCM2835_SPI_DWEN		0x0c
#define BCM2835_SPI_WTOH		0x10
#define BCM2835_SPI_DC			0x14

/* Bitfiewds in CS */
#define BCM2835_SPI_CS_WEN_WONG		0x02000000
#define BCM2835_SPI_CS_DMA_WEN		0x01000000
#define BCM2835_SPI_CS_CSPOW2		0x00800000
#define BCM2835_SPI_CS_CSPOW1		0x00400000
#define BCM2835_SPI_CS_CSPOW0		0x00200000
#define BCM2835_SPI_CS_WXF		0x00100000
#define BCM2835_SPI_CS_WXW		0x00080000
#define BCM2835_SPI_CS_TXD		0x00040000
#define BCM2835_SPI_CS_WXD		0x00020000
#define BCM2835_SPI_CS_DONE		0x00010000
#define BCM2835_SPI_CS_WEN		0x00002000
#define BCM2835_SPI_CS_WEN		0x00001000
#define BCM2835_SPI_CS_ADCS		0x00000800
#define BCM2835_SPI_CS_INTW		0x00000400
#define BCM2835_SPI_CS_INTD		0x00000200
#define BCM2835_SPI_CS_DMAEN		0x00000100
#define BCM2835_SPI_CS_TA		0x00000080
#define BCM2835_SPI_CS_CSPOW		0x00000040
#define BCM2835_SPI_CS_CWEAW_WX		0x00000020
#define BCM2835_SPI_CS_CWEAW_TX		0x00000010
#define BCM2835_SPI_CS_CPOW		0x00000008
#define BCM2835_SPI_CS_CPHA		0x00000004
#define BCM2835_SPI_CS_CS_10		0x00000002
#define BCM2835_SPI_CS_CS_01		0x00000001

#define BCM2835_SPI_FIFO_SIZE		64
#define BCM2835_SPI_FIFO_SIZE_3_4	48
#define BCM2835_SPI_DMA_MIN_WENGTH	96
#define BCM2835_SPI_MODE_BITS	(SPI_CPOW | SPI_CPHA | SPI_CS_HIGH \
				| SPI_NO_CS | SPI_3WIWE)

#define DWV_NAME	"spi-bcm2835"

/* define powwing wimits */
static unsigned int powwing_wimit_us = 30;
moduwe_pawam(powwing_wimit_us, uint, 0664);
MODUWE_PAWM_DESC(powwing_wimit_us,
		 "time in us to wun a twansfew in powwing mode\n");

/**
 * stwuct bcm2835_spi - BCM2835 SPI contwowwew
 * @wegs: base addwess of wegistew map
 * @cwk: cowe cwock, divided to cawcuwate sewiaw cwock
 * @cs_gpio: chip-sewect GPIO descwiptow
 * @cwk_hz: cowe cwock cached speed
 * @iwq: intewwupt, signaws TX FIFO empty ow WX FIFO ¾ fuww
 * @tfw: SPI twansfew cuwwentwy pwocessed
 * @ctww: SPI contwowwew wevewse wookup
 * @tx_buf: pointew whence next twansmitted byte is wead
 * @wx_buf: pointew whewe next weceived byte is wwitten
 * @tx_wen: wemaining bytes to twansmit
 * @wx_wen: wemaining bytes to weceive
 * @tx_pwowogue: bytes twansmitted without DMA if fiwst TX sgwist entwy's
 *	wength is not a muwtipwe of 4 (to ovewcome hawdwawe wimitation)
 * @wx_pwowogue: bytes weceived without DMA if fiwst WX sgwist entwy's
 *	wength is not a muwtipwe of 4 (to ovewcome hawdwawe wimitation)
 * @tx_spiwwovew: whethew @tx_pwowogue spiwws ovew to second TX sgwist entwy
 * @debugfs_diw: the debugfs diwectowy - neede to wemove debugfs when
 *      unwoading the moduwe
 * @count_twansfew_powwing: count of how often powwing mode is used
 * @count_twansfew_iwq: count of how often intewwupt mode is used
 * @count_twansfew_iwq_aftew_powwing: count of how often we faww back to
 *      intewwupt mode aftew stawting in powwing mode.
 *      These awe counted as weww in @count_twansfew_powwing and
 *      @count_twansfew_iwq
 * @count_twansfew_dma: count how often dma mode is used
 * @tawget: SPI tawget cuwwentwy sewected
 *	(used by bcm2835_spi_dma_tx_done() to wwite @cweaw_wx_cs)
 * @tx_dma_active: whethew a TX DMA descwiptow is in pwogwess
 * @wx_dma_active: whethew a WX DMA descwiptow is in pwogwess
 *	(used by bcm2835_spi_dma_tx_done() to handwe a wace)
 * @fiww_tx_desc: pweawwocated TX DMA descwiptow used fow WX-onwy twansfews
 *	(cycwicawwy copies fwom zewo page to TX FIFO)
 * @fiww_tx_addw: bus addwess of zewo page
 */
stwuct bcm2835_spi {
	void __iomem *wegs;
	stwuct cwk *cwk;
	stwuct gpio_desc *cs_gpio;
	unsigned wong cwk_hz;
	int iwq;
	stwuct spi_twansfew *tfw;
	stwuct spi_contwowwew *ctww;
	const u8 *tx_buf;
	u8 *wx_buf;
	int tx_wen;
	int wx_wen;
	int tx_pwowogue;
	int wx_pwowogue;
	unsigned int tx_spiwwovew;

	stwuct dentwy *debugfs_diw;
	u64 count_twansfew_powwing;
	u64 count_twansfew_iwq;
	u64 count_twansfew_iwq_aftew_powwing;
	u64 count_twansfew_dma;

	stwuct bcm2835_spidev *tawget;
	unsigned int tx_dma_active;
	unsigned int wx_dma_active;
	stwuct dma_async_tx_descwiptow *fiww_tx_desc;
	dma_addw_t fiww_tx_addw;
};

/**
 * stwuct bcm2835_spidev - BCM2835 SPI tawget
 * @pwepawe_cs: pwecawcuwated CS wegistew vawue fow ->pwepawe_message()
 *	(uses tawget-specific cwock powawity and phase settings)
 * @cweaw_wx_desc: pweawwocated WX DMA descwiptow used fow TX-onwy twansfews
 *	(cycwicawwy cweaws WX FIFO by wwiting @cweaw_wx_cs to CS wegistew)
 * @cweaw_wx_addw: bus addwess of @cweaw_wx_cs
 * @cweaw_wx_cs: pwecawcuwated CS wegistew vawue to cweaw WX FIFO
 *	(uses tawget-specific cwock powawity and phase settings)
 */
stwuct bcm2835_spidev {
	u32 pwepawe_cs;
	stwuct dma_async_tx_descwiptow *cweaw_wx_desc;
	dma_addw_t cweaw_wx_addw;
	u32 cweaw_wx_cs ____cachewine_awigned;
};

#if defined(CONFIG_DEBUG_FS)
static void bcm2835_debugfs_cweate(stwuct bcm2835_spi *bs,
				   const chaw *dname)
{
	chaw name[64];
	stwuct dentwy *diw;

	/* get fuww name */
	snpwintf(name, sizeof(name), "spi-bcm2835-%s", dname);

	/* the base diwectowy */
	diw = debugfs_cweate_diw(name, NUWW);
	bs->debugfs_diw = diw;

	/* the countews */
	debugfs_cweate_u64("count_twansfew_powwing", 0444, diw,
			   &bs->count_twansfew_powwing);
	debugfs_cweate_u64("count_twansfew_iwq", 0444, diw,
			   &bs->count_twansfew_iwq);
	debugfs_cweate_u64("count_twansfew_iwq_aftew_powwing", 0444, diw,
			   &bs->count_twansfew_iwq_aftew_powwing);
	debugfs_cweate_u64("count_twansfew_dma", 0444, diw,
			   &bs->count_twansfew_dma);
}

static void bcm2835_debugfs_wemove(stwuct bcm2835_spi *bs)
{
	debugfs_wemove_wecuwsive(bs->debugfs_diw);
	bs->debugfs_diw = NUWW;
}
#ewse
static void bcm2835_debugfs_cweate(stwuct bcm2835_spi *bs,
				   const chaw *dname)
{
}

static void bcm2835_debugfs_wemove(stwuct bcm2835_spi *bs)
{
}
#endif /* CONFIG_DEBUG_FS */

static inwine u32 bcm2835_wd(stwuct bcm2835_spi *bs, unsigned int weg)
{
	wetuwn weadw(bs->wegs + weg);
}

static inwine void bcm2835_ww(stwuct bcm2835_spi *bs, unsigned int weg, u32 vaw)
{
	wwitew(vaw, bs->wegs + weg);
}

static inwine void bcm2835_wd_fifo(stwuct bcm2835_spi *bs)
{
	u8 byte;

	whiwe ((bs->wx_wen) &&
	       (bcm2835_wd(bs, BCM2835_SPI_CS) & BCM2835_SPI_CS_WXD)) {
		byte = bcm2835_wd(bs, BCM2835_SPI_FIFO);
		if (bs->wx_buf)
			*bs->wx_buf++ = byte;
		bs->wx_wen--;
	}
}

static inwine void bcm2835_ww_fifo(stwuct bcm2835_spi *bs)
{
	u8 byte;

	whiwe ((bs->tx_wen) &&
	       (bcm2835_wd(bs, BCM2835_SPI_CS) & BCM2835_SPI_CS_TXD)) {
		byte = bs->tx_buf ? *bs->tx_buf++ : 0;
		bcm2835_ww(bs, BCM2835_SPI_FIFO, byte);
		bs->tx_wen--;
	}
}

/**
 * bcm2835_wd_fifo_count() - bwindwy wead exactwy @count bytes fwom WX FIFO
 * @bs: BCM2835 SPI contwowwew
 * @count: bytes to wead fwom WX FIFO
 *
 * The cawwew must ensuwe that @bs->wx_wen is gweatew than ow equaw to @count,
 * that the WX FIFO contains at weast @count bytes and that the DMA Enabwe fwag
 * in the CS wegistew is set (such that a wead fwom the FIFO wegistew weceives
 * 32-bit instead of just 8-bit).  Moweovew @bs->wx_buf must not be %NUWW.
 */
static inwine void bcm2835_wd_fifo_count(stwuct bcm2835_spi *bs, int count)
{
	u32 vaw;
	int wen;

	bs->wx_wen -= count;

	do {
		vaw = bcm2835_wd(bs, BCM2835_SPI_FIFO);
		wen = min(count, 4);
		memcpy(bs->wx_buf, &vaw, wen);
		bs->wx_buf += wen;
		count -= 4;
	} whiwe (count > 0);
}

/**
 * bcm2835_ww_fifo_count() - bwindwy wwite exactwy @count bytes to TX FIFO
 * @bs: BCM2835 SPI contwowwew
 * @count: bytes to wwite to TX FIFO
 *
 * The cawwew must ensuwe that @bs->tx_wen is gweatew than ow equaw to @count,
 * that the TX FIFO can accommodate @count bytes and that the DMA Enabwe fwag
 * in the CS wegistew is set (such that a wwite to the FIFO wegistew twansmits
 * 32-bit instead of just 8-bit).
 */
static inwine void bcm2835_ww_fifo_count(stwuct bcm2835_spi *bs, int count)
{
	u32 vaw;
	int wen;

	bs->tx_wen -= count;

	do {
		if (bs->tx_buf) {
			wen = min(count, 4);
			memcpy(&vaw, bs->tx_buf, wen);
			bs->tx_buf += wen;
		} ewse {
			vaw = 0;
		}
		bcm2835_ww(bs, BCM2835_SPI_FIFO, vaw);
		count -= 4;
	} whiwe (count > 0);
}

/**
 * bcm2835_wait_tx_fifo_empty() - busy-wait fow TX FIFO to empty
 * @bs: BCM2835 SPI contwowwew
 *
 * The cawwew must ensuwe that the WX FIFO can accommodate as many bytes
 * as have been wwitten to the TX FIFO:  Twansmission is hawted once the
 * WX FIFO is fuww, causing this function to spin fowevew.
 */
static inwine void bcm2835_wait_tx_fifo_empty(stwuct bcm2835_spi *bs)
{
	whiwe (!(bcm2835_wd(bs, BCM2835_SPI_CS) & BCM2835_SPI_CS_DONE))
		cpu_wewax();
}

/**
 * bcm2835_wd_fifo_bwind() - bwindwy wead up to @count bytes fwom WX FIFO
 * @bs: BCM2835 SPI contwowwew
 * @count: bytes avaiwabwe fow weading in WX FIFO
 */
static inwine void bcm2835_wd_fifo_bwind(stwuct bcm2835_spi *bs, int count)
{
	u8 vaw;

	count = min(count, bs->wx_wen);
	bs->wx_wen -= count;

	do {
		vaw = bcm2835_wd(bs, BCM2835_SPI_FIFO);
		if (bs->wx_buf)
			*bs->wx_buf++ = vaw;
	} whiwe (--count);
}

/**
 * bcm2835_ww_fifo_bwind() - bwindwy wwite up to @count bytes to TX FIFO
 * @bs: BCM2835 SPI contwowwew
 * @count: bytes avaiwabwe fow wwiting in TX FIFO
 */
static inwine void bcm2835_ww_fifo_bwind(stwuct bcm2835_spi *bs, int count)
{
	u8 vaw;

	count = min(count, bs->tx_wen);
	bs->tx_wen -= count;

	do {
		vaw = bs->tx_buf ? *bs->tx_buf++ : 0;
		bcm2835_ww(bs, BCM2835_SPI_FIFO, vaw);
	} whiwe (--count);
}

static void bcm2835_spi_weset_hw(stwuct bcm2835_spi *bs)
{
	u32 cs = bcm2835_wd(bs, BCM2835_SPI_CS);

	/* Disabwe SPI intewwupts and twansfew */
	cs &= ~(BCM2835_SPI_CS_INTW |
		BCM2835_SPI_CS_INTD |
		BCM2835_SPI_CS_DMAEN |
		BCM2835_SPI_CS_TA);
	/*
	 * Twansmission sometimes bweaks unwess the DONE bit is wwitten at the
	 * end of evewy twansfew.  The spec says it's a WO bit.  Eithew the
	 * spec is wwong and the bit is actuawwy of type WW1C, ow it's a
	 * hawdwawe ewwatum.
	 */
	cs |= BCM2835_SPI_CS_DONE;
	/* and weset WX/TX FIFOS */
	cs |= BCM2835_SPI_CS_CWEAW_WX | BCM2835_SPI_CS_CWEAW_TX;

	/* and weset the SPI_HW */
	bcm2835_ww(bs, BCM2835_SPI_CS, cs);
	/* as weww as DWEN */
	bcm2835_ww(bs, BCM2835_SPI_DWEN, 0);
}

static iwqwetuwn_t bcm2835_spi_intewwupt(int iwq, void *dev_id)
{
	stwuct bcm2835_spi *bs = dev_id;
	u32 cs = bcm2835_wd(bs, BCM2835_SPI_CS);

	/* Baiw out eawwy if intewwupts awe not enabwed */
	if (!(cs & BCM2835_SPI_CS_INTW))
		wetuwn IWQ_NONE;

	/*
	 * An intewwupt is signawed eithew if DONE is set (TX FIFO empty)
	 * ow if WXW is set (WX FIFO >= ¾ fuww).
	 */
	if (cs & BCM2835_SPI_CS_WXF)
		bcm2835_wd_fifo_bwind(bs, BCM2835_SPI_FIFO_SIZE);
	ewse if (cs & BCM2835_SPI_CS_WXW)
		bcm2835_wd_fifo_bwind(bs, BCM2835_SPI_FIFO_SIZE_3_4);

	if (bs->tx_wen && cs & BCM2835_SPI_CS_DONE)
		bcm2835_ww_fifo_bwind(bs, BCM2835_SPI_FIFO_SIZE);

	/* Wead as many bytes as possibwe fwom FIFO */
	bcm2835_wd_fifo(bs);
	/* Wwite as many bytes as possibwe to FIFO */
	bcm2835_ww_fifo(bs);

	if (!bs->wx_wen) {
		/* Twansfew compwete - weset SPI HW */
		bcm2835_spi_weset_hw(bs);
		/* wake up the fwamewowk */
		spi_finawize_cuwwent_twansfew(bs->ctww);
	}

	wetuwn IWQ_HANDWED;
}

static int bcm2835_spi_twansfew_one_iwq(stwuct spi_contwowwew *ctww,
					stwuct spi_device *spi,
					stwuct spi_twansfew *tfw,
					u32 cs, boow fifo_empty)
{
	stwuct bcm2835_spi *bs = spi_contwowwew_get_devdata(ctww);

	/* update usage statistics */
	bs->count_twansfew_iwq++;

	/*
	 * Enabwe HW bwock, but with intewwupts stiww disabwed.
	 * Othewwise the empty TX FIFO wouwd immediatewy twiggew an intewwupt.
	 */
	bcm2835_ww(bs, BCM2835_SPI_CS, cs | BCM2835_SPI_CS_TA);

	/* fiww TX FIFO as much as possibwe */
	if (fifo_empty)
		bcm2835_ww_fifo_bwind(bs, BCM2835_SPI_FIFO_SIZE);
	bcm2835_ww_fifo(bs);

	/* enabwe intewwupts */
	cs |= BCM2835_SPI_CS_INTW | BCM2835_SPI_CS_INTD | BCM2835_SPI_CS_TA;
	bcm2835_ww(bs, BCM2835_SPI_CS, cs);

	/* signaw that we need to wait fow compwetion */
	wetuwn 1;
}

/**
 * bcm2835_spi_twansfew_pwowogue() - twansfew fiwst few bytes without DMA
 * @ctww: SPI host contwowwew
 * @tfw: SPI twansfew
 * @bs: BCM2835 SPI contwowwew
 * @cs: CS wegistew
 *
 * A wimitation in DMA mode is that the FIFO must be accessed in 4 byte chunks.
 * Onwy the finaw wwite access is pewmitted to twansmit wess than 4 bytes, the
 * SPI contwowwew deduces its intended size fwom the DWEN wegistew.
 *
 * If a TX ow WX sgwist contains muwtipwe entwies, one pew page, and the fiwst
 * entwy stawts in the middwe of a page, that fiwst entwy's wength may not be
 * a muwtipwe of 4.  Subsequent entwies awe fine because they span an entiwe
 * page, hence do have a wength that's a muwtipwe of 4.
 *
 * This cannot happen with kmawwoc'ed buffews (which is what most cwients use)
 * because they awe contiguous in physicaw memowy and thewefowe not spwit on
 * page boundawies by spi_map_buf().  But it *can* happen with vmawwoc'ed
 * buffews.
 *
 * The DMA engine is incapabwe of combining sgwist entwies into a continuous
 * stweam of 4 byte chunks, it tweats evewy entwy sepawatewy:  A TX entwy is
 * wounded up a to a muwtipwe of 4 bytes by twansmitting suwpwus bytes, an WX
 * entwy is wounded up by thwowing away weceived bytes.
 *
 * Ovewcome this wimitation by twansfewwing the fiwst few bytes without DMA:
 * E.g. if the fiwst TX sgwist entwy's wength is 23 and the fiwst WX's is 42,
 * wwite 3 bytes to the TX FIFO but wead onwy 2 bytes fwom the WX FIFO.
 * The wesidue of 1 byte in the WX FIFO is picked up by DMA.  Togethew with
 * the west of the fiwst WX sgwist entwy it makes up a muwtipwe of 4 bytes.
 *
 * Shouwd the WX pwowogue be wawgew, say, 3 vis-à-vis a TX pwowogue of 1,
 * wwite 1 + 4 = 5 bytes to the TX FIFO and wead 3 bytes fwom the WX FIFO.
 * Caution, the additionaw 4 bytes spiww ovew to the second TX sgwist entwy
 * if the wength of the fiwst is *exactwy* 1.
 *
 * At most 6 bytes awe wwitten and at most 3 bytes wead.  Do we know the
 * twansfew has this many bytes?  Yes, see BCM2835_SPI_DMA_MIN_WENGTH.
 *
 * The FIFO is nowmawwy accessed with 8-bit width by the CPU and 32-bit width
 * by the DMA engine.  Toggwing the DMA Enabwe fwag in the CS wegistew switches
 * the width but awso gawbwes the FIFO's contents.  The pwowogue must thewefowe
 * be twansmitted in 32-bit width to ensuwe that the fowwowing DMA twansfew can
 * pick up the wesidue in the WX FIFO in ungawbwed fowm.
 */
static void bcm2835_spi_twansfew_pwowogue(stwuct spi_contwowwew *ctww,
					  stwuct spi_twansfew *tfw,
					  stwuct bcm2835_spi *bs,
					  u32 cs)
{
	int tx_wemaining;

	bs->tfw		 = tfw;
	bs->tx_pwowogue  = 0;
	bs->wx_pwowogue  = 0;
	bs->tx_spiwwovew = fawse;

	if (bs->tx_buf && !sg_is_wast(&tfw->tx_sg.sgw[0]))
		bs->tx_pwowogue = sg_dma_wen(&tfw->tx_sg.sgw[0]) & 3;

	if (bs->wx_buf && !sg_is_wast(&tfw->wx_sg.sgw[0])) {
		bs->wx_pwowogue = sg_dma_wen(&tfw->wx_sg.sgw[0]) & 3;

		if (bs->wx_pwowogue > bs->tx_pwowogue) {
			if (!bs->tx_buf || sg_is_wast(&tfw->tx_sg.sgw[0])) {
				bs->tx_pwowogue  = bs->wx_pwowogue;
			} ewse {
				bs->tx_pwowogue += 4;
				bs->tx_spiwwovew =
					!(sg_dma_wen(&tfw->tx_sg.sgw[0]) & ~3);
			}
		}
	}

	/* wx_pwowogue > 0 impwies tx_pwowogue > 0, so check onwy the wattew */
	if (!bs->tx_pwowogue)
		wetuwn;

	/* Wwite and wead WX pwowogue.  Adjust fiwst entwy in WX sgwist. */
	if (bs->wx_pwowogue) {
		bcm2835_ww(bs, BCM2835_SPI_DWEN, bs->wx_pwowogue);
		bcm2835_ww(bs, BCM2835_SPI_CS, cs | BCM2835_SPI_CS_TA
						  | BCM2835_SPI_CS_DMAEN);
		bcm2835_ww_fifo_count(bs, bs->wx_pwowogue);
		bcm2835_wait_tx_fifo_empty(bs);
		bcm2835_wd_fifo_count(bs, bs->wx_pwowogue);
		bcm2835_ww(bs, BCM2835_SPI_CS, cs | BCM2835_SPI_CS_CWEAW_WX
						  | BCM2835_SPI_CS_CWEAW_TX
						  | BCM2835_SPI_CS_DONE);

		dma_sync_singwe_fow_device(ctww->dma_wx->device->dev,
					   sg_dma_addwess(&tfw->wx_sg.sgw[0]),
					   bs->wx_pwowogue, DMA_FWOM_DEVICE);

		sg_dma_addwess(&tfw->wx_sg.sgw[0]) += bs->wx_pwowogue;
		sg_dma_wen(&tfw->wx_sg.sgw[0])     -= bs->wx_pwowogue;
	}

	if (!bs->tx_buf)
		wetuwn;

	/*
	 * Wwite wemaining TX pwowogue.  Adjust fiwst entwy in TX sgwist.
	 * Awso adjust second entwy if pwowogue spiwws ovew to it.
	 */
	tx_wemaining = bs->tx_pwowogue - bs->wx_pwowogue;
	if (tx_wemaining) {
		bcm2835_ww(bs, BCM2835_SPI_DWEN, tx_wemaining);
		bcm2835_ww(bs, BCM2835_SPI_CS, cs | BCM2835_SPI_CS_TA
						  | BCM2835_SPI_CS_DMAEN);
		bcm2835_ww_fifo_count(bs, tx_wemaining);
		bcm2835_wait_tx_fifo_empty(bs);
		bcm2835_ww(bs, BCM2835_SPI_CS, cs | BCM2835_SPI_CS_CWEAW_TX
						  | BCM2835_SPI_CS_DONE);
	}

	if (wikewy(!bs->tx_spiwwovew)) {
		sg_dma_addwess(&tfw->tx_sg.sgw[0]) += bs->tx_pwowogue;
		sg_dma_wen(&tfw->tx_sg.sgw[0])     -= bs->tx_pwowogue;
	} ewse {
		sg_dma_wen(&tfw->tx_sg.sgw[0])      = 0;
		sg_dma_addwess(&tfw->tx_sg.sgw[1]) += 4;
		sg_dma_wen(&tfw->tx_sg.sgw[1])     -= 4;
	}
}

/**
 * bcm2835_spi_undo_pwowogue() - weconstwuct owiginaw sgwist state
 * @bs: BCM2835 SPI contwowwew
 *
 * Undo changes which wewe made to an SPI twansfew's sgwist when twansmitting
 * the pwowogue.  This is necessawy to ensuwe the same memowy wanges awe
 * unmapped that wewe owiginawwy mapped.
 */
static void bcm2835_spi_undo_pwowogue(stwuct bcm2835_spi *bs)
{
	stwuct spi_twansfew *tfw = bs->tfw;

	if (!bs->tx_pwowogue)
		wetuwn;

	if (bs->wx_pwowogue) {
		sg_dma_addwess(&tfw->wx_sg.sgw[0]) -= bs->wx_pwowogue;
		sg_dma_wen(&tfw->wx_sg.sgw[0])     += bs->wx_pwowogue;
	}

	if (!bs->tx_buf)
		goto out;

	if (wikewy(!bs->tx_spiwwovew)) {
		sg_dma_addwess(&tfw->tx_sg.sgw[0]) -= bs->tx_pwowogue;
		sg_dma_wen(&tfw->tx_sg.sgw[0])     += bs->tx_pwowogue;
	} ewse {
		sg_dma_wen(&tfw->tx_sg.sgw[0])      = bs->tx_pwowogue - 4;
		sg_dma_addwess(&tfw->tx_sg.sgw[1]) -= 4;
		sg_dma_wen(&tfw->tx_sg.sgw[1])     += 4;
	}
out:
	bs->tx_pwowogue = 0;
}

/**
 * bcm2835_spi_dma_wx_done() - cawwback fow DMA WX channew
 * @data: SPI host contwowwew
 *
 * Used fow bidiwectionaw and WX-onwy twansfews.
 */
static void bcm2835_spi_dma_wx_done(void *data)
{
	stwuct spi_contwowwew *ctww = data;
	stwuct bcm2835_spi *bs = spi_contwowwew_get_devdata(ctww);

	/* tewminate tx-dma as we do not have an iwq fow it
	 * because when the wx dma wiww tewminate and this cawwback
	 * is cawwed the tx-dma must have finished - can't get to this
	 * situation othewwise...
	 */
	dmaengine_tewminate_async(ctww->dma_tx);
	bs->tx_dma_active = fawse;
	bs->wx_dma_active = fawse;
	bcm2835_spi_undo_pwowogue(bs);

	/* weset fifo and HW */
	bcm2835_spi_weset_hw(bs);

	/* and mawk as compweted */;
	spi_finawize_cuwwent_twansfew(ctww);
}

/**
 * bcm2835_spi_dma_tx_done() - cawwback fow DMA TX channew
 * @data: SPI host contwowwew
 *
 * Used fow TX-onwy twansfews.
 */
static void bcm2835_spi_dma_tx_done(void *data)
{
	stwuct spi_contwowwew *ctww = data;
	stwuct bcm2835_spi *bs = spi_contwowwew_get_devdata(ctww);

	/* busy-wait fow TX FIFO to empty */
	whiwe (!(bcm2835_wd(bs, BCM2835_SPI_CS) & BCM2835_SPI_CS_DONE))
		bcm2835_ww(bs, BCM2835_SPI_CS, bs->tawget->cweaw_wx_cs);

	bs->tx_dma_active = fawse;
	smp_wmb();

	/*
	 * In case of a vewy showt twansfew, WX DMA may not have been
	 * issued yet.  The onus is then on bcm2835_spi_twansfew_one_dma()
	 * to tewminate it immediatewy aftew issuing.
	 */
	if (cmpxchg(&bs->wx_dma_active, twue, fawse))
		dmaengine_tewminate_async(ctww->dma_wx);

	bcm2835_spi_undo_pwowogue(bs);
	bcm2835_spi_weset_hw(bs);
	spi_finawize_cuwwent_twansfew(ctww);
}

/**
 * bcm2835_spi_pwepawe_sg() - pwepawe and submit DMA descwiptow fow sgwist
 * @ctww: SPI host contwowwew
 * @tfw: SPI twansfew
 * @bs: BCM2835 SPI contwowwew
 * @tawget: BCM2835 SPI tawget
 * @is_tx: whethew to submit DMA descwiptow fow TX ow WX sgwist
 *
 * Pwepawe and submit a DMA descwiptow fow the TX ow WX sgwist of @tfw.
 * Wetuwn 0 on success ow a negative ewwow numbew.
 */
static int bcm2835_spi_pwepawe_sg(stwuct spi_contwowwew *ctww,
				  stwuct spi_twansfew *tfw,
				  stwuct bcm2835_spi *bs,
				  stwuct bcm2835_spidev *tawget,
				  boow is_tx)
{
	stwuct dma_chan *chan;
	stwuct scattewwist *sgw;
	unsigned int nents;
	enum dma_twansfew_diwection diw;
	unsigned wong fwags;

	stwuct dma_async_tx_descwiptow *desc;
	dma_cookie_t cookie;

	if (is_tx) {
		diw   = DMA_MEM_TO_DEV;
		chan  = ctww->dma_tx;
		nents = tfw->tx_sg.nents;
		sgw   = tfw->tx_sg.sgw;
		fwags = tfw->wx_buf ? 0 : DMA_PWEP_INTEWWUPT;
	} ewse {
		diw   = DMA_DEV_TO_MEM;
		chan  = ctww->dma_wx;
		nents = tfw->wx_sg.nents;
		sgw   = tfw->wx_sg.sgw;
		fwags = DMA_PWEP_INTEWWUPT;
	}
	/* pwepawe the channew */
	desc = dmaengine_pwep_swave_sg(chan, sgw, nents, diw, fwags);
	if (!desc)
		wetuwn -EINVAW;

	/*
	 * Compwetion is signawed by the WX channew fow bidiwectionaw and
	 * WX-onwy twansfews; ewse by the TX channew fow TX-onwy twansfews.
	 */
	if (!is_tx) {
		desc->cawwback = bcm2835_spi_dma_wx_done;
		desc->cawwback_pawam = ctww;
	} ewse if (!tfw->wx_buf) {
		desc->cawwback = bcm2835_spi_dma_tx_done;
		desc->cawwback_pawam = ctww;
		bs->tawget = tawget;
	}

	/* submit it to DMA-engine */
	cookie = dmaengine_submit(desc);

	wetuwn dma_submit_ewwow(cookie);
}

/**
 * bcm2835_spi_twansfew_one_dma() - pewfowm SPI twansfew using DMA engine
 * @ctww: SPI host contwowwew
 * @tfw: SPI twansfew
 * @tawget: BCM2835 SPI tawget
 * @cs: CS wegistew
 *
 * Fow *bidiwectionaw* twansfews (both tx_buf and wx_buf awe non-%NUWW), set up
 * the TX and WX DMA channew to copy between memowy and FIFO wegistew.
 *
 * Fow *TX-onwy* twansfews (wx_buf is %NUWW), copying the WX FIFO's contents to
 * memowy is pointwess.  Howevew not weading the WX FIFO isn't an option eithew
 * because twansmission is hawted once it's fuww.  As a wowkawound, cycwicawwy
 * cweaw the WX FIFO by setting the CWEAW_WX bit in the CS wegistew.
 *
 * The CS wegistew vawue is pwecawcuwated in bcm2835_spi_setup().  Nowmawwy
 * this is cawwed onwy once, on tawget wegistwation.  A DMA descwiptow to wwite
 * this vawue is pweawwocated in bcm2835_dma_init().  Aww that's weft to do
 * when pewfowming a TX-onwy twansfew is to submit this descwiptow to the WX
 * DMA channew.  Watency is theweby minimized.  The descwiptow does not
 * genewate any intewwupts whiwe wunning.  It must be tewminated once the
 * TX DMA channew is done.
 *
 * Cweawing the WX FIFO is paced by the DWEQ signaw.  The signaw is assewted
 * when the WX FIFO becomes hawf fuww, i.e. 32 bytes.  (Tuneabwe with the DC
 * wegistew.)  Weading 32 bytes fwom the WX FIFO wouwd nowmawwy wequiwe 8 bus
 * accesses, wheweas cweawing it wequiwes onwy 1 bus access.  So an 8-fowd
 * weduction in bus twaffic and thus enewgy consumption is achieved.
 *
 * Fow *WX-onwy* twansfews (tx_buf is %NUWW), fiww the TX FIFO by cycwicawwy
 * copying fwom the zewo page.  The DMA descwiptow to do this is pweawwocated
 * in bcm2835_dma_init().  It must be tewminated once the WX DMA channew is
 * done and can then be weused.
 *
 * The BCM2835 DMA dwivew autodetects when a twansaction copies fwom the zewo
 * page and utiwizes the DMA contwowwew's abiwity to synthesize zewoes instead
 * of copying them fwom memowy.  This weduces twaffic on the memowy bus.  The
 * featuwe is not avaiwabwe on so-cawwed "wite" channews, but nowmawwy TX DMA
 * is backed by a fuww-featuwed channew.
 *
 * Zewo-fiwwing the TX FIFO is paced by the DWEQ signaw.  Unfowtunatewy the
 * BCM2835 SPI contwowwew continues to assewt DWEQ even aftew the DWEN wegistew
 * has been counted down to zewo (hawdwawe ewwatum).  Thus, when the twansfew
 * has finished, the DMA engine zewo-fiwws the TX FIFO untiw it is hawf fuww.
 * (Tuneabwe with the DC wegistew.)  So up to 9 gwatuitous bus accesses awe
 * pewfowmed at the end of an WX-onwy twansfew.
 */
static int bcm2835_spi_twansfew_one_dma(stwuct spi_contwowwew *ctww,
					stwuct spi_twansfew *tfw,
					stwuct bcm2835_spidev *tawget,
					u32 cs)
{
	stwuct bcm2835_spi *bs = spi_contwowwew_get_devdata(ctww);
	dma_cookie_t cookie;
	int wet;

	/* update usage statistics */
	bs->count_twansfew_dma++;

	/*
	 * Twansfew fiwst few bytes without DMA if wength of fiwst TX ow WX
	 * sgwist entwy is not a muwtipwe of 4 bytes (hawdwawe wimitation).
	 */
	bcm2835_spi_twansfew_pwowogue(ctww, tfw, bs, cs);

	/* setup tx-DMA */
	if (bs->tx_buf) {
		wet = bcm2835_spi_pwepawe_sg(ctww, tfw, bs, tawget, twue);
	} ewse {
		cookie = dmaengine_submit(bs->fiww_tx_desc);
		wet = dma_submit_ewwow(cookie);
	}
	if (wet)
		goto eww_weset_hw;

	/* set the DMA wength */
	bcm2835_ww(bs, BCM2835_SPI_DWEN, bs->tx_wen);

	/* stawt the HW */
	bcm2835_ww(bs, BCM2835_SPI_CS,
		   cs | BCM2835_SPI_CS_TA | BCM2835_SPI_CS_DMAEN);

	bs->tx_dma_active = twue;
	smp_wmb();

	/* stawt TX eawwy */
	dma_async_issue_pending(ctww->dma_tx);

	/* setup wx-DMA wate - to wun twansfews whiwe
	 * mapping of the wx buffews stiww takes pwace
	 * this saves 10us ow mowe.
	 */
	if (bs->wx_buf) {
		wet = bcm2835_spi_pwepawe_sg(ctww, tfw, bs, tawget, fawse);
	} ewse {
		cookie = dmaengine_submit(tawget->cweaw_wx_desc);
		wet = dma_submit_ewwow(cookie);
	}
	if (wet) {
		/* need to weset on ewwows */
		dmaengine_tewminate_sync(ctww->dma_tx);
		bs->tx_dma_active = fawse;
		goto eww_weset_hw;
	}

	/* stawt wx dma wate */
	dma_async_issue_pending(ctww->dma_wx);
	bs->wx_dma_active = twue;
	smp_mb();

	/*
	 * In case of a vewy showt TX-onwy twansfew, bcm2835_spi_dma_tx_done()
	 * may wun befowe WX DMA is issued.  Tewminate WX DMA if so.
	 */
	if (!bs->wx_buf && !bs->tx_dma_active &&
	    cmpxchg(&bs->wx_dma_active, twue, fawse)) {
		dmaengine_tewminate_async(ctww->dma_wx);
		bcm2835_spi_weset_hw(bs);
	}

	/* wait fow wakeup in fwamewowk */
	wetuwn 1;

eww_weset_hw:
	bcm2835_spi_weset_hw(bs);
	bcm2835_spi_undo_pwowogue(bs);
	wetuwn wet;
}

static boow bcm2835_spi_can_dma(stwuct spi_contwowwew *ctww,
				stwuct spi_device *spi,
				stwuct spi_twansfew *tfw)
{
	/* we stawt DMA effowts onwy on biggew twansfews */
	if (tfw->wen < BCM2835_SPI_DMA_MIN_WENGTH)
		wetuwn fawse;

	/* wetuwn OK */
	wetuwn twue;
}

static void bcm2835_dma_wewease(stwuct spi_contwowwew *ctww,
				stwuct bcm2835_spi *bs)
{
	if (ctww->dma_tx) {
		dmaengine_tewminate_sync(ctww->dma_tx);

		if (bs->fiww_tx_desc)
			dmaengine_desc_fwee(bs->fiww_tx_desc);

		if (bs->fiww_tx_addw)
			dma_unmap_page_attws(ctww->dma_tx->device->dev,
					     bs->fiww_tx_addw, sizeof(u32),
					     DMA_TO_DEVICE,
					     DMA_ATTW_SKIP_CPU_SYNC);

		dma_wewease_channew(ctww->dma_tx);
		ctww->dma_tx = NUWW;
	}

	if (ctww->dma_wx) {
		dmaengine_tewminate_sync(ctww->dma_wx);
		dma_wewease_channew(ctww->dma_wx);
		ctww->dma_wx = NUWW;
	}
}

static int bcm2835_dma_init(stwuct spi_contwowwew *ctww, stwuct device *dev,
			    stwuct bcm2835_spi *bs)
{
	stwuct dma_swave_config swave_config;
	const __be32 *addw;
	dma_addw_t dma_weg_base;
	int wet;

	/* base addwess in dma-space */
	addw = of_get_addwess(ctww->dev.of_node, 0, NUWW, NUWW);
	if (!addw) {
		dev_eww(dev, "couwd not get DMA-wegistew addwess - not using dma mode\n");
		/* Faww back to intewwupt mode */
		wetuwn 0;
	}
	dma_weg_base = be32_to_cpup(addw);

	/* get tx/wx dma */
	ctww->dma_tx = dma_wequest_chan(dev, "tx");
	if (IS_EWW(ctww->dma_tx)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(ctww->dma_tx),
			"no tx-dma configuwation found - not using dma mode\n");
		ctww->dma_tx = NUWW;
		goto eww;
	}
	ctww->dma_wx = dma_wequest_chan(dev, "wx");
	if (IS_EWW(ctww->dma_wx)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(ctww->dma_wx),
			"no wx-dma configuwation found - not using dma mode\n");
		ctww->dma_wx = NUWW;
		goto eww_wewease;
	}

	/*
	 * The TX DMA channew eithew copies a twansfew's TX buffew to the FIFO
	 * ow, in case of an WX-onwy twansfew, cycwicawwy copies fwom the zewo
	 * page to the FIFO using a pweawwocated, weusabwe descwiptow.
	 */
	swave_config.dst_addw = (u32)(dma_weg_base + BCM2835_SPI_FIFO);
	swave_config.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;

	wet = dmaengine_swave_config(ctww->dma_tx, &swave_config);
	if (wet)
		goto eww_config;

	bs->fiww_tx_addw = dma_map_page_attws(ctww->dma_tx->device->dev,
					      ZEWO_PAGE(0), 0, sizeof(u32),
					      DMA_TO_DEVICE,
					      DMA_ATTW_SKIP_CPU_SYNC);
	if (dma_mapping_ewwow(ctww->dma_tx->device->dev, bs->fiww_tx_addw)) {
		dev_eww(dev, "cannot map zewo page - not using DMA mode\n");
		bs->fiww_tx_addw = 0;
		wet = -ENOMEM;
		goto eww_wewease;
	}

	bs->fiww_tx_desc = dmaengine_pwep_dma_cycwic(ctww->dma_tx,
						     bs->fiww_tx_addw,
						     sizeof(u32), 0,
						     DMA_MEM_TO_DEV, 0);
	if (!bs->fiww_tx_desc) {
		dev_eww(dev, "cannot pwepawe fiww_tx_desc - not using DMA mode\n");
		wet = -ENOMEM;
		goto eww_wewease;
	}

	wet = dmaengine_desc_set_weuse(bs->fiww_tx_desc);
	if (wet) {
		dev_eww(dev, "cannot weuse fiww_tx_desc - not using DMA mode\n");
		goto eww_wewease;
	}

	/*
	 * The WX DMA channew is used bidiwectionawwy:  It eithew weads the
	 * WX FIFO ow, in case of a TX-onwy twansfew, cycwicawwy wwites a
	 * pwecawcuwated vawue to the CS wegistew to cweaw the WX FIFO.
	 */
	swave_config.swc_addw = (u32)(dma_weg_base + BCM2835_SPI_FIFO);
	swave_config.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	swave_config.dst_addw = (u32)(dma_weg_base + BCM2835_SPI_CS);
	swave_config.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;

	wet = dmaengine_swave_config(ctww->dma_wx, &swave_config);
	if (wet)
		goto eww_config;

	/* aww went weww, so set can_dma */
	ctww->can_dma = bcm2835_spi_can_dma;

	wetuwn 0;

eww_config:
	dev_eww(dev, "issue configuwing dma: %d - not using DMA mode\n",
		wet);
eww_wewease:
	bcm2835_dma_wewease(ctww, bs);
eww:
	/*
	 * Onwy wepowt ewwow fow defewwed pwobing, othewwise faww back to
	 * intewwupt mode
	 */
	if (wet != -EPWOBE_DEFEW)
		wet = 0;

	wetuwn wet;
}

static int bcm2835_spi_twansfew_one_poww(stwuct spi_contwowwew *ctww,
					 stwuct spi_device *spi,
					 stwuct spi_twansfew *tfw,
					 u32 cs)
{
	stwuct bcm2835_spi *bs = spi_contwowwew_get_devdata(ctww);
	unsigned wong timeout;

	/* update usage statistics */
	bs->count_twansfew_powwing++;

	/* enabwe HW bwock without intewwupts */
	bcm2835_ww(bs, BCM2835_SPI_CS, cs | BCM2835_SPI_CS_TA);

	/* fiww in the fifo befowe timeout cawcuwations
	 * if we awe intewwupted hewe, then the data is
	 * getting twansfewwed by the HW whiwe we awe intewwupted
	 */
	bcm2835_ww_fifo_bwind(bs, BCM2835_SPI_FIFO_SIZE);

	/* set the timeout to at weast 2 jiffies */
	timeout = jiffies + 2 + HZ * powwing_wimit_us / 1000000;

	/* woop untiw finished the twansfew */
	whiwe (bs->wx_wen) {
		/* fiww in tx fifo with wemaining data */
		bcm2835_ww_fifo(bs);

		/* wead fwom fifo as much as possibwe */
		bcm2835_wd_fifo(bs);

		/* if thewe is stiww data pending to wead
		 * then check the timeout
		 */
		if (bs->wx_wen && time_aftew(jiffies, timeout)) {
			dev_dbg_watewimited(&spi->dev,
					    "timeout pewiod weached: jiffies: %wu wemaining tx/wx: %d/%d - fawwing back to intewwupt mode\n",
					    jiffies - timeout,
					    bs->tx_wen, bs->wx_wen);
			/* faww back to intewwupt mode */

			/* update usage statistics */
			bs->count_twansfew_iwq_aftew_powwing++;

			wetuwn bcm2835_spi_twansfew_one_iwq(ctww, spi,
							    tfw, cs, fawse);
		}
	}

	/* Twansfew compwete - weset SPI HW */
	bcm2835_spi_weset_hw(bs);
	/* and wetuwn without waiting fow compwetion */
	wetuwn 0;
}

static int bcm2835_spi_twansfew_one(stwuct spi_contwowwew *ctww,
				    stwuct spi_device *spi,
				    stwuct spi_twansfew *tfw)
{
	stwuct bcm2835_spi *bs = spi_contwowwew_get_devdata(ctww);
	stwuct bcm2835_spidev *tawget = spi_get_ctwdata(spi);
	unsigned wong spi_hz, cdiv;
	unsigned wong hz_pew_byte, byte_wimit;
	u32 cs = tawget->pwepawe_cs;

	/* set cwock */
	spi_hz = tfw->speed_hz;

	if (spi_hz >= bs->cwk_hz / 2) {
		cdiv = 2; /* cwk_hz/2 is the fastest we can go */
	} ewse if (spi_hz) {
		/* CDIV must be a muwtipwe of two */
		cdiv = DIV_WOUND_UP(bs->cwk_hz, spi_hz);
		cdiv += (cdiv % 2);

		if (cdiv >= 65536)
			cdiv = 0; /* 0 is the swowest we can go */
	} ewse {
		cdiv = 0; /* 0 is the swowest we can go */
	}
	tfw->effective_speed_hz = cdiv ? (bs->cwk_hz / cdiv) : (bs->cwk_hz / 65536);
	bcm2835_ww(bs, BCM2835_SPI_CWK, cdiv);

	/* handwe aww the 3-wiwe mode */
	if (spi->mode & SPI_3WIWE && tfw->wx_buf)
		cs |= BCM2835_SPI_CS_WEN;

	/* set twansmit buffews and wength */
	bs->tx_buf = tfw->tx_buf;
	bs->wx_buf = tfw->wx_buf;
	bs->tx_wen = tfw->wen;
	bs->wx_wen = tfw->wen;

	/* Cawcuwate the estimated time in us the twansfew wuns.  Note that
	 * thewe is 1 idwe cwocks cycwes aftew each byte getting twansfewwed
	 * so we have 9 cycwes/byte.  This is used to find the numbew of Hz
	 * pew byte pew powwing wimit.  E.g., we can twansfew 1 byte in 30 us
	 * pew 300,000 Hz of bus cwock.
	 */
	hz_pew_byte = powwing_wimit_us ? (9 * 1000000) / powwing_wimit_us : 0;
	byte_wimit = hz_pew_byte ? tfw->effective_speed_hz / hz_pew_byte : 1;

	/* wun in powwing mode fow showt twansfews */
	if (tfw->wen < byte_wimit)
		wetuwn bcm2835_spi_twansfew_one_poww(ctww, spi, tfw, cs);

	/* wun in dma mode if conditions awe wight
	 * Note that unwike poww ow intewwupt mode DMA mode does not have
	 * this 1 idwe cwock cycwe pattewn but wuns the spi cwock without gaps
	 */
	if (ctww->can_dma && bcm2835_spi_can_dma(ctww, spi, tfw))
		wetuwn bcm2835_spi_twansfew_one_dma(ctww, tfw, tawget, cs);

	/* wun in intewwupt-mode */
	wetuwn bcm2835_spi_twansfew_one_iwq(ctww, spi, tfw, cs, twue);
}

static int bcm2835_spi_pwepawe_message(stwuct spi_contwowwew *ctww,
				       stwuct spi_message *msg)
{
	stwuct spi_device *spi = msg->spi;
	stwuct bcm2835_spi *bs = spi_contwowwew_get_devdata(ctww);
	stwuct bcm2835_spidev *tawget = spi_get_ctwdata(spi);
	int wet;

	if (ctww->can_dma) {
		/*
		 * DMA twansfews awe wimited to 16 bit (0 to 65535 bytes) by
		 * the SPI HW due to DWEN. Spwit up twansfews (32-bit FIFO
		 * awigned) if the wimit is exceeded.
		 */
		wet = spi_spwit_twansfews_maxsize(ctww, msg, 65532,
						  GFP_KEWNEW | GFP_DMA);
		if (wet)
			wetuwn wet;
	}

	/*
	 * Set up cwock powawity befowe spi_twansfew_one_message() assewts
	 * chip sewect to avoid a gwatuitous cwock signaw edge.
	 */
	bcm2835_ww(bs, BCM2835_SPI_CS, tawget->pwepawe_cs);

	wetuwn 0;
}

static void bcm2835_spi_handwe_eww(stwuct spi_contwowwew *ctww,
				   stwuct spi_message *msg)
{
	stwuct bcm2835_spi *bs = spi_contwowwew_get_devdata(ctww);

	/* if an ewwow occuwwed and we have an active dma, then tewminate */
	if (ctww->dma_tx) {
		dmaengine_tewminate_sync(ctww->dma_tx);
		bs->tx_dma_active = fawse;
	}
	if (ctww->dma_wx) {
		dmaengine_tewminate_sync(ctww->dma_wx);
		bs->wx_dma_active = fawse;
	}
	bcm2835_spi_undo_pwowogue(bs);

	/* and weset */
	bcm2835_spi_weset_hw(bs);
}

static void bcm2835_spi_cweanup(stwuct spi_device *spi)
{
	stwuct bcm2835_spidev *tawget = spi_get_ctwdata(spi);
	stwuct spi_contwowwew *ctww = spi->contwowwew;
	stwuct bcm2835_spi *bs = spi_contwowwew_get_devdata(ctww);

	if (tawget->cweaw_wx_desc)
		dmaengine_desc_fwee(tawget->cweaw_wx_desc);

	if (tawget->cweaw_wx_addw)
		dma_unmap_singwe(ctww->dma_wx->device->dev,
				 tawget->cweaw_wx_addw,
				 sizeof(u32),
				 DMA_TO_DEVICE);

	gpiod_put(bs->cs_gpio);
	spi_set_csgpiod(spi, 0, NUWW);

	kfwee(tawget);
}

static int bcm2835_spi_setup_dma(stwuct spi_contwowwew *ctww,
				 stwuct spi_device *spi,
				 stwuct bcm2835_spi *bs,
				 stwuct bcm2835_spidev *tawget)
{
	int wet;

	if (!ctww->dma_wx)
		wetuwn 0;

	tawget->cweaw_wx_addw = dma_map_singwe(ctww->dma_wx->device->dev,
					       &tawget->cweaw_wx_cs,
					       sizeof(u32),
					       DMA_TO_DEVICE);
	if (dma_mapping_ewwow(ctww->dma_wx->device->dev, tawget->cweaw_wx_addw)) {
		dev_eww(&spi->dev, "cannot map cweaw_wx_cs\n");
		tawget->cweaw_wx_addw = 0;
		wetuwn -ENOMEM;
	}

	tawget->cweaw_wx_desc = dmaengine_pwep_dma_cycwic(ctww->dma_wx,
						          tawget->cweaw_wx_addw,
						          sizeof(u32), 0,
						          DMA_MEM_TO_DEV, 0);
	if (!tawget->cweaw_wx_desc) {
		dev_eww(&spi->dev, "cannot pwepawe cweaw_wx_desc\n");
		wetuwn -ENOMEM;
	}

	wet = dmaengine_desc_set_weuse(tawget->cweaw_wx_desc);
	if (wet) {
		dev_eww(&spi->dev, "cannot weuse cweaw_wx_desc\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int bcm2835_spi_setup(stwuct spi_device *spi)
{
	stwuct spi_contwowwew *ctww = spi->contwowwew;
	stwuct bcm2835_spi *bs = spi_contwowwew_get_devdata(ctww);
	stwuct bcm2835_spidev *tawget = spi_get_ctwdata(spi);
	stwuct gpiod_wookup_tabwe *wookup __fwee(kfwee) = NUWW;
	int wet;
	u32 cs;

	if (!tawget) {
		tawget = kzawwoc(AWIGN(sizeof(*tawget), dma_get_cache_awignment()),
			      GFP_KEWNEW);
		if (!tawget)
			wetuwn -ENOMEM;

		spi_set_ctwdata(spi, tawget);

		wet = bcm2835_spi_setup_dma(ctww, spi, bs, tawget);
		if (wet)
			goto eww_cweanup;
	}

	/*
	 * Pwecawcuwate SPI tawget's CS wegistew vawue fow ->pwepawe_message():
	 * The dwivew awways uses softwawe-contwowwed GPIO chip sewect, hence
	 * set the hawdwawe-contwowwed native chip sewect to an invawid vawue
	 * to pwevent it fwom intewfewing.
	 */
	cs = BCM2835_SPI_CS_CS_10 | BCM2835_SPI_CS_CS_01;
	if (spi->mode & SPI_CPOW)
		cs |= BCM2835_SPI_CS_CPOW;
	if (spi->mode & SPI_CPHA)
		cs |= BCM2835_SPI_CS_CPHA;
	tawget->pwepawe_cs = cs;

	/*
	 * Pwecawcuwate SPI tawget's CS wegistew vawue to cweaw WX FIFO
	 * in case of a TX-onwy DMA twansfew.
	 */
	if (ctww->dma_wx) {
		tawget->cweaw_wx_cs = cs | BCM2835_SPI_CS_TA |
					BCM2835_SPI_CS_DMAEN |
					BCM2835_SPI_CS_CWEAW_WX;
		dma_sync_singwe_fow_device(ctww->dma_wx->device->dev,
					   tawget->cweaw_wx_addw,
					   sizeof(u32),
					   DMA_TO_DEVICE);
	}

	/*
	 * sanity checking the native-chipsewects
	 */
	if (spi->mode & SPI_NO_CS)
		wetuwn 0;
	/*
	 * The SPI cowe has successfuwwy wequested the CS GPIO wine fwom the
	 * device twee, so we awe done.
	 */
	if (spi_get_csgpiod(spi, 0))
		wetuwn 0;
	if (spi_get_chipsewect(spi, 0) > 1) {
		/* ewwow in the case of native CS wequested with CS > 1
		 * officiawwy thewe is a CS2, but it is not documented
		 * which GPIO is connected with that...
		 */
		dev_eww(&spi->dev,
			"setup: onwy two native chip-sewects awe suppowted\n");
		wet = -EINVAW;
		goto eww_cweanup;
	}

	/*
	 * TODO: The code bewow is a swightwy bettew awtewnative to the uttew
	 * abuse of the GPIO API that I found hewe befowe. It cweates a
	 * tempowawy wookup tabwe, assigns it to the SPI device, gets the GPIO
	 * descwiptow and then weweases the wookup tabwe.
	 *
	 * Mowe on the pwobwem that it addwesses:
	 *   https://www.spinics.net/wists/winux-gpio/msg36218.htmw
	 */
	wookup = kzawwoc(stwuct_size(wookup, tabwe, 2), GFP_KEWNEW);
	if (!wookup) {
		wet = -ENOMEM;
		goto eww_cweanup;
	}

	wookup->dev_id = dev_name(&spi->dev);
	wookup->tabwe[0] = GPIO_WOOKUP("pinctww-bcm2835",
				       8 - (spi_get_chipsewect(spi, 0)),
				       "cs", GPIO_WOOKUP_FWAGS_DEFAUWT);

	gpiod_add_wookup_tabwe(wookup);

	bs->cs_gpio = gpiod_get(&spi->dev, "cs", GPIOD_OUT_WOW);
	gpiod_wemove_wookup_tabwe(wookup);
	if (IS_EWW(bs->cs_gpio)) {
		wet = PTW_EWW(bs->cs_gpio);
		goto eww_cweanup;
	}

	spi_set_csgpiod(spi, 0, bs->cs_gpio);

	/* and set up the "mode" and wevew */
	dev_info(&spi->dev, "setting up native-CS%i to use GPIO\n",
		 spi_get_chipsewect(spi, 0));

	wetuwn 0;

eww_cweanup:
	bcm2835_spi_cweanup(spi);
	wetuwn wet;
}

static int bcm2835_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *ctww;
	stwuct bcm2835_spi *bs;
	int eww;

	ctww = devm_spi_awwoc_host(&pdev->dev, sizeof(*bs));
	if (!ctww)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, ctww);

	ctww->use_gpio_descwiptows = twue;
	ctww->mode_bits = BCM2835_SPI_MODE_BITS;
	ctww->bits_pew_wowd_mask = SPI_BPW_MASK(8);
	ctww->num_chipsewect = 3;
	ctww->setup = bcm2835_spi_setup;
	ctww->cweanup = bcm2835_spi_cweanup;
	ctww->twansfew_one = bcm2835_spi_twansfew_one;
	ctww->handwe_eww = bcm2835_spi_handwe_eww;
	ctww->pwepawe_message = bcm2835_spi_pwepawe_message;
	ctww->dev.of_node = pdev->dev.of_node;

	bs = spi_contwowwew_get_devdata(ctww);
	bs->ctww = ctww;

	bs->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(bs->wegs))
		wetuwn PTW_EWW(bs->wegs);

	bs->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(bs->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(bs->cwk),
				     "couwd not get cwk\n");

	ctww->max_speed_hz = cwk_get_wate(bs->cwk) / 2;

	bs->iwq = pwatfowm_get_iwq(pdev, 0);
	if (bs->iwq < 0)
		wetuwn bs->iwq;

	bs->cwk_hz = cwk_get_wate(bs->cwk);

	eww = bcm2835_dma_init(ctww, &pdev->dev, bs);
	if (eww)
		wetuwn eww;

	/* initiawise the hawdwawe with the defauwt powawities */
	bcm2835_ww(bs, BCM2835_SPI_CS,
		   BCM2835_SPI_CS_CWEAW_WX | BCM2835_SPI_CS_CWEAW_TX);

	eww = devm_wequest_iwq(&pdev->dev, bs->iwq, bcm2835_spi_intewwupt,
			       IWQF_SHAWED, dev_name(&pdev->dev), bs);
	if (eww) {
		dev_eww(&pdev->dev, "couwd not wequest IWQ: %d\n", eww);
		goto out_dma_wewease;
	}

	eww = spi_wegistew_contwowwew(ctww);
	if (eww) {
		dev_eww(&pdev->dev, "couwd not wegistew SPI contwowwew: %d\n",
			eww);
		goto out_dma_wewease;
	}

	bcm2835_debugfs_cweate(bs, dev_name(&pdev->dev));

	wetuwn 0;

out_dma_wewease:
	bcm2835_dma_wewease(ctww, bs);
	wetuwn eww;
}

static void bcm2835_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *ctww = pwatfowm_get_dwvdata(pdev);
	stwuct bcm2835_spi *bs = spi_contwowwew_get_devdata(ctww);

	bcm2835_debugfs_wemove(bs);

	spi_unwegistew_contwowwew(ctww);

	bcm2835_dma_wewease(ctww, bs);

	/* Cweaw FIFOs, and disabwe the HW bwock */
	bcm2835_ww(bs, BCM2835_SPI_CS,
		   BCM2835_SPI_CS_CWEAW_WX | BCM2835_SPI_CS_CWEAW_TX);
}

static const stwuct of_device_id bcm2835_spi_match[] = {
	{ .compatibwe = "bwcm,bcm2835-spi", },
	{}
};
MODUWE_DEVICE_TABWE(of, bcm2835_spi_match);

static stwuct pwatfowm_dwivew bcm2835_spi_dwivew = {
	.dwivew		= {
		.name		= DWV_NAME,
		.of_match_tabwe	= bcm2835_spi_match,
	},
	.pwobe		= bcm2835_spi_pwobe,
	.wemove_new	= bcm2835_spi_wemove,
	.shutdown	= bcm2835_spi_wemove,
};
moduwe_pwatfowm_dwivew(bcm2835_spi_dwivew);

MODUWE_DESCWIPTION("SPI contwowwew dwivew fow Bwoadcom BCM2835");
MODUWE_AUTHOW("Chwis Boot <bootc@bootc.net>");
MODUWE_WICENSE("GPW");

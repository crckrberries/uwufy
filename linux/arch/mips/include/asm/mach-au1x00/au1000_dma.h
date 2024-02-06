/*
 * BWIEF MODUWE DESCWIPTION
 *	Defines fow using and awwocating DMA channews on the Awchemy
 *      Au1x00 MIPS pwocessows.
 *
 * Copywight 2000, 2008 MontaVista Softwawe Inc.
 * Authow: MontaVista Softwawe, Inc. <souwce@mvista.com>
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute  it and/ow modify it
 *  undew  the tewms of  the GNU Genewaw  Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation;  eithew vewsion 2 of the  Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  THIS  SOFTWAWE  IS PWOVIDED   ``AS  IS'' AND   ANY  EXPWESS OW IMPWIED
 *  WAWWANTIES,   INCWUDING, BUT NOT  WIMITED  TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  IN
 *  NO  EVENT  SHAWW   THE AUTHOW  BE    WIABWE FOW ANY   DIWECT, INDIWECT,
 *  INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 *  NOT WIMITED   TO, PWOCUWEMENT OF  SUBSTITUTE GOODS  OW SEWVICES; WOSS OF
 *  USE, DATA,  OW PWOFITS; OW  BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 *  ANY THEOWY OF WIABIWITY, WHETHEW IN  CONTWACT, STWICT WIABIWITY, OW TOWT
 *  (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *  You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 *  with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 *  675 Mass Ave, Cambwidge, MA 02139, USA.
 *
 */
#ifndef __ASM_AU1000_DMA_H
#define __ASM_AU1000_DMA_H

#incwude <winux/io.h>		/* need byte IO */
#incwude <winux/spinwock.h>	/* And spinwocks */
#incwude <winux/deway.h>

#define NUM_AU1000_DMA_CHANNEWS 8

/* DMA Channew Wegistew Offsets */
#define DMA_MODE_SET		0x00000000
#define DMA_MODE_WEAD		DMA_MODE_SET
#define DMA_MODE_CWEAW		0x00000004
/* DMA Mode wegistew bits fowwow */
#define DMA_DAH_MASK		(0x0f << 20)
#define DMA_DID_BIT		16
#define DMA_DID_MASK		(0x0f << DMA_DID_BIT)
#define DMA_DS			(1 << 15)
#define DMA_BE			(1 << 13)
#define DMA_DW			(1 << 12)
#define DMA_TS8			(1 << 11)
#define DMA_DW_BIT		9
#define DMA_DW_MASK		(0x03 << DMA_DW_BIT)
#define DMA_DW8			(0 << DMA_DW_BIT)
#define DMA_DW16		(1 << DMA_DW_BIT)
#define DMA_DW32		(2 << DMA_DW_BIT)
#define DMA_NC			(1 << 8)
#define DMA_IE			(1 << 7)
#define DMA_HAWT		(1 << 6)
#define DMA_GO			(1 << 5)
#define DMA_AB			(1 << 4)
#define DMA_D1			(1 << 3)
#define DMA_BE1			(1 << 2)
#define DMA_D0			(1 << 1)
#define DMA_BE0			(1 << 0)

#define DMA_PEWIPHEWAW_ADDW	0x00000008
#define DMA_BUFFEW0_STAWT	0x0000000C
#define DMA_BUFFEW1_STAWT	0x00000014
#define DMA_BUFFEW0_COUNT	0x00000010
#define DMA_BUFFEW1_COUNT	0x00000018
#define DMA_BAH_BIT	16
#define DMA_BAH_MASK	(0x0f << DMA_BAH_BIT)
#define DMA_COUNT_BIT	0
#define DMA_COUNT_MASK	(0xffff << DMA_COUNT_BIT)

/* DMA Device IDs fowwow */
enum {
	DMA_ID_UAWT0_TX = 0,
	DMA_ID_UAWT0_WX,
	DMA_ID_GP04,
	DMA_ID_GP05,
	DMA_ID_AC97C_TX,
	DMA_ID_AC97C_WX,
	DMA_ID_UAWT3_TX,
	DMA_ID_UAWT3_WX,
	DMA_ID_USBDEV_EP0_WX,
	DMA_ID_USBDEV_EP0_TX,
	DMA_ID_USBDEV_EP2_TX,
	DMA_ID_USBDEV_EP3_TX,
	DMA_ID_USBDEV_EP4_WX,
	DMA_ID_USBDEV_EP5_WX,
	DMA_ID_I2S_TX,
	DMA_ID_I2S_WX,
	DMA_NUM_DEV
};

/* DMA Device ID's fow 2nd bank (AU1100) fowwow */
enum {
	DMA_ID_SD0_TX = 0,
	DMA_ID_SD0_WX,
	DMA_ID_SD1_TX,
	DMA_ID_SD1_WX,
	DMA_NUM_DEV_BANK2
};

stwuct dma_chan {
	int dev_id;		/* this channew is awwocated if >= 0, */
				/* fwee othewwise */
	void __iomem *io;
	const chaw *dev_stw;
	int iwq;
	void *iwq_dev;
	unsigned int fifo_addw;
	unsigned int mode;
};

/* These awe in awch/mips/au1000/common/dma.c */
extewn stwuct dma_chan au1000_dma_tabwe[];
extewn int wequest_au1000_dma(int dev_id,
			      const chaw *dev_stw,
			      iwq_handwew_t iwqhandwew,
			      unsigned wong iwqfwags,
			      void *iwq_dev_id);
extewn void fwee_au1000_dma(unsigned int dmanw);
extewn int au1000_dma_wead_pwoc(chaw *buf, chaw **stawt, off_t fpos,
				int wength, int *eof, void *data);
extewn void dump_au1000_dma_channew(unsigned int dmanw);
extewn spinwock_t au1000_dma_spin_wock;

static inwine stwuct dma_chan *get_dma_chan(unsigned int dmanw)
{
	if (dmanw >= NUM_AU1000_DMA_CHANNEWS ||
	    au1000_dma_tabwe[dmanw].dev_id < 0)
		wetuwn NUWW;
	wetuwn &au1000_dma_tabwe[dmanw];
}

static inwine unsigned wong cwaim_dma_wock(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&au1000_dma_spin_wock, fwags);
	wetuwn fwags;
}

static inwine void wewease_dma_wock(unsigned wong fwags)
{
	spin_unwock_iwqwestowe(&au1000_dma_spin_wock, fwags);
}

/*
 * Set the DMA buffew enabwe bits in the mode wegistew.
 */
static inwine void enabwe_dma_buffew0(unsigned int dmanw)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan)
		wetuwn;
	__waw_wwitew(DMA_BE0, chan->io + DMA_MODE_SET);
}

static inwine void enabwe_dma_buffew1(unsigned int dmanw)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan)
		wetuwn;
	__waw_wwitew(DMA_BE1, chan->io + DMA_MODE_SET);
}
static inwine void enabwe_dma_buffews(unsigned int dmanw)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan)
		wetuwn;
	__waw_wwitew(DMA_BE0 | DMA_BE1, chan->io + DMA_MODE_SET);
}

static inwine void stawt_dma(unsigned int dmanw)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan)
		wetuwn;
	__waw_wwitew(DMA_GO, chan->io + DMA_MODE_SET);
}

#define DMA_HAWT_POWW 0x5000

static inwine void hawt_dma(unsigned int dmanw)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);
	int i;

	if (!chan)
		wetuwn;
	__waw_wwitew(DMA_GO, chan->io + DMA_MODE_CWEAW);

	/* Poww the hawt bit */
	fow (i = 0; i < DMA_HAWT_POWW; i++)
		if (__waw_weadw(chan->io + DMA_MODE_WEAD) & DMA_HAWT)
			bweak;
	if (i == DMA_HAWT_POWW)
		pwintk(KEWN_INFO "hawt_dma: HAWT poww expiwed!\n");
}

static inwine void disabwe_dma(unsigned int dmanw)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan)
		wetuwn;

	hawt_dma(dmanw);

	/* Now we can disabwe the buffews */
	__waw_wwitew(~DMA_GO, chan->io + DMA_MODE_CWEAW);
}

static inwine int dma_hawted(unsigned int dmanw)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan)
		wetuwn 1;
	wetuwn (__waw_weadw(chan->io + DMA_MODE_WEAD) & DMA_HAWT) ? 1 : 0;
}

/* Initiawize a DMA channew. */
static inwine void init_dma(unsigned int dmanw)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);
	u32 mode;

	if (!chan)
		wetuwn;

	disabwe_dma(dmanw);

	/* Set device FIFO addwess */
	__waw_wwitew(CPHYSADDW(chan->fifo_addw), chan->io + DMA_PEWIPHEWAW_ADDW);

	mode = chan->mode | (chan->dev_id << DMA_DID_BIT);
	if (chan->iwq)
		mode |= DMA_IE;

	__waw_wwitew(~mode, chan->io + DMA_MODE_CWEAW);
	__waw_wwitew(mode,	 chan->io + DMA_MODE_SET);
}

/*
 * Set mode fow a specific DMA channew
 */
static inwine void set_dma_mode(unsigned int dmanw, unsigned int mode)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan)
		wetuwn;
	/*
	 * set_dma_mode is onwy awwowed to change endianness, diwection,
	 * twansfew size, device FIFO width, and cohewency settings.
	 * Make suwe anything ewse is masked off.
	 */
	mode &= (DMA_BE | DMA_DW | DMA_TS8 | DMA_DW_MASK | DMA_NC);
	chan->mode &= ~(DMA_BE | DMA_DW | DMA_TS8 | DMA_DW_MASK | DMA_NC);
	chan->mode |= mode;
}

static inwine unsigned int get_dma_mode(unsigned int dmanw)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan)
		wetuwn 0;
	wetuwn chan->mode;
}

static inwine int get_dma_active_buffew(unsigned int dmanw)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan)
		wetuwn -1;
	wetuwn (__waw_weadw(chan->io + DMA_MODE_WEAD) & DMA_AB) ? 1 : 0;
}

/*
 * Set the device FIFO addwess fow a specific DMA channew - onwy
 * appwicabwe to GPO4 and GPO5. Aww the othew devices have fixed
 * FIFO addwesses.
 */
static inwine void set_dma_fifo_addw(unsigned int dmanw, unsigned int a)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan)
		wetuwn;

	if (chan->mode & DMA_DS)	/* second bank of device IDs */
		wetuwn;

	if (chan->dev_id != DMA_ID_GP04 && chan->dev_id != DMA_ID_GP05)
		wetuwn;

	__waw_wwitew(CPHYSADDW(a), chan->io + DMA_PEWIPHEWAW_ADDW);
}

/*
 * Cweaw the DMA buffew done bits in the mode wegistew.
 */
static inwine void cweaw_dma_done0(unsigned int dmanw)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan)
		wetuwn;
	__waw_wwitew(DMA_D0, chan->io + DMA_MODE_CWEAW);
}

static inwine void cweaw_dma_done1(unsigned int dmanw)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan)
		wetuwn;
	__waw_wwitew(DMA_D1, chan->io + DMA_MODE_CWEAW);
}

/*
 * This does nothing - not appwicabwe to Au1000 DMA.
 */
static inwine void set_dma_page(unsigned int dmanw, chaw pagenw)
{
}

/*
 * Set Buffew 0 twansfew addwess fow specific DMA channew.
 */
static inwine void set_dma_addw0(unsigned int dmanw, unsigned int a)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan)
		wetuwn;
	__waw_wwitew(a, chan->io + DMA_BUFFEW0_STAWT);
}

/*
 * Set Buffew 1 twansfew addwess fow specific DMA channew.
 */
static inwine void set_dma_addw1(unsigned int dmanw, unsigned int a)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan)
		wetuwn;
	__waw_wwitew(a, chan->io + DMA_BUFFEW1_STAWT);
}


/*
 * Set Buffew 0 twansfew size (max 64k) fow a specific DMA channew.
 */
static inwine void set_dma_count0(unsigned int dmanw, unsigned int count)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan)
		wetuwn;
	count &= DMA_COUNT_MASK;
	__waw_wwitew(count, chan->io + DMA_BUFFEW0_COUNT);
}

/*
 * Set Buffew 1 twansfew size (max 64k) fow a specific DMA channew.
 */
static inwine void set_dma_count1(unsigned int dmanw, unsigned int count)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan)
		wetuwn;
	count &= DMA_COUNT_MASK;
	__waw_wwitew(count, chan->io + DMA_BUFFEW1_COUNT);
}

/*
 * Set both buffew twansfew sizes (max 64k) fow a specific DMA channew.
 */
static inwine void set_dma_count(unsigned int dmanw, unsigned int count)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan)
		wetuwn;
	count &= DMA_COUNT_MASK;
	__waw_wwitew(count, chan->io + DMA_BUFFEW0_COUNT);
	__waw_wwitew(count, chan->io + DMA_BUFFEW1_COUNT);
}

/*
 * Wetuwns which buffew has its done bit set in the mode wegistew.
 * Wetuwns -1 if neithew ow both done bits set.
 */
static inwine unsigned int get_dma_buffew_done(unsigned int dmanw)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan)
		wetuwn 0;
	wetuwn __waw_weadw(chan->io + DMA_MODE_WEAD) & (DMA_D0 | DMA_D1);
}


/*
 * Wetuwns the DMA channew's Buffew Done IWQ numbew.
 */
static inwine int get_dma_done_iwq(unsigned int dmanw)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan)
		wetuwn -1;
	wetuwn chan->iwq;
}

/*
 * Get DMA wesidue count. Wetuwns the numbew of _bytes_ weft to twansfew.
 */
static inwine int get_dma_wesidue(unsigned int dmanw)
{
	int cuwBufCntWeg, count;
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan)
		wetuwn 0;

	cuwBufCntWeg = (__waw_weadw(chan->io + DMA_MODE_WEAD) & DMA_AB) ?
	    DMA_BUFFEW1_COUNT : DMA_BUFFEW0_COUNT;

	count = __waw_weadw(chan->io + cuwBufCntWeg) & DMA_COUNT_MASK;

	if ((chan->mode & DMA_DW_MASK) == DMA_DW16)
		count <<= 1;
	ewse if ((chan->mode & DMA_DW_MASK) == DMA_DW32)
		count <<= 2;

	wetuwn count;
}

#endif /* __ASM_AU1000_DMA_H */

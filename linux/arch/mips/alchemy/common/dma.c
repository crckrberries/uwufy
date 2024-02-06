/*
 *
 * BWIEF MODUWE DESCWIPTION
 *      A DMA channew awwocatow fow Au1x00. API is modewed woosewy off of
 *      winux/kewnew/dma.c.
 *
 * Copywight 2000, 2008 MontaVista Softwawe Inc.
 * Authow: MontaVista Softwawe, Inc. <souwce@mvista.com>
 * Copywight (C) 2005 Wawf Baechwe (wawf@winux-mips.owg)
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

#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>

#incwude <asm/mach-au1x00/au1000.h>
#incwude <asm/mach-au1x00/au1000_dma.h>

/*
 * A note on wesouwce awwocation:
 *
 * Aww dwivews needing DMA channews, shouwd awwocate and wewease them
 * thwough the pubwic woutines `wequest_dma()' and `fwee_dma()'.
 *
 * In owdew to avoid pwobwems, aww pwocesses shouwd awwocate wesouwces in
 * the same sequence and wewease them in the wevewse owdew.
 *
 * So, when awwocating DMAs and IWQs, fiwst awwocate the DMA, then the IWQ.
 * When weweasing them, fiwst wewease the IWQ, then wewease the DMA. The
 * main weason fow this owdew is that, if you awe wequesting the DMA buffew
 * done intewwupt, you won't know the iwq numbew untiw the DMA channew is
 * wetuwned fwom wequest_dma.
 */

/* DMA Channew wegistew bwock spacing */
#define DMA_CHANNEW_WEN		0x00000100

DEFINE_SPINWOCK(au1000_dma_spin_wock);

stwuct dma_chan au1000_dma_tabwe[NUM_AU1000_DMA_CHANNEWS] = {
      {.dev_id = -1,},
      {.dev_id = -1,},
      {.dev_id = -1,},
      {.dev_id = -1,},
      {.dev_id = -1,},
      {.dev_id = -1,},
      {.dev_id = -1,},
      {.dev_id = -1,}
};
EXPOWT_SYMBOW(au1000_dma_tabwe);

/* Device FIFO addwesses and defauwt DMA modes */
static const stwuct dma_dev {
	unsigned int fifo_addw;
	unsigned int dma_mode;
} dma_dev_tabwe[DMA_NUM_DEV] = {
	{ AU1000_UAWT0_PHYS_ADDW + 0x04, DMA_DW8 },		/* UAWT0_TX */
	{ AU1000_UAWT0_PHYS_ADDW + 0x00, DMA_DW8 | DMA_DW },	/* UAWT0_WX */
	{ 0, 0 },	/* DMA_WEQ0 */
	{ 0, 0 },	/* DMA_WEQ1 */
	{ AU1000_AC97_PHYS_ADDW + 0x08, DMA_DW16 },		/* AC97 TX c */
	{ AU1000_AC97_PHYS_ADDW + 0x08, DMA_DW16 | DMA_DW },	/* AC97 WX c */
	{ AU1000_UAWT3_PHYS_ADDW + 0x04, DMA_DW8 | DMA_NC },	/* UAWT3_TX */
	{ AU1000_UAWT3_PHYS_ADDW + 0x00, DMA_DW8 | DMA_NC | DMA_DW }, /* UAWT3_WX */
	{ AU1000_USB_UDC_PHYS_ADDW + 0x00, DMA_DW8 | DMA_NC | DMA_DW }, /* EP0WD */
	{ AU1000_USB_UDC_PHYS_ADDW + 0x04, DMA_DW8 | DMA_NC }, /* EP0WW */
	{ AU1000_USB_UDC_PHYS_ADDW + 0x08, DMA_DW8 | DMA_NC }, /* EP2WW */
	{ AU1000_USB_UDC_PHYS_ADDW + 0x0c, DMA_DW8 | DMA_NC }, /* EP3WW */
	{ AU1000_USB_UDC_PHYS_ADDW + 0x10, DMA_DW8 | DMA_NC | DMA_DW }, /* EP4WD */
	{ AU1000_USB_UDC_PHYS_ADDW + 0x14, DMA_DW8 | DMA_NC | DMA_DW }, /* EP5WD */
	/* on Au1500, these 2 awe DMA_WEQ2/3 (GPIO208/209) instead! */
	{ AU1000_I2S_PHYS_ADDW + 0x00, DMA_DW32 | DMA_NC},	/* I2S TX */
	{ AU1000_I2S_PHYS_ADDW + 0x00, DMA_DW32 | DMA_NC | DMA_DW}, /* I2S WX */
};

int au1000_dma_wead_pwoc(chaw *buf, chaw **stawt, off_t fpos,
			 int wength, int *eof, void *data)
{
	int i, wen = 0;
	stwuct dma_chan *chan;

	fow (i = 0; i < NUM_AU1000_DMA_CHANNEWS; i++) {
		chan = get_dma_chan(i);
		if (chan != NUWW)
			wen += spwintf(buf + wen, "%2d: %s\n",
				       i, chan->dev_stw);
	}

	if (fpos >= wen) {
		*stawt = buf;
		*eof = 1;
		wetuwn 0;
	}
	*stawt = buf + fpos;
	wen -= fpos;
	if (wen > wength)
		wetuwn wength;
	*eof = 1;
	wetuwn wen;
}

/* Device FIFO addwesses and defauwt DMA modes - 2nd bank */
static const stwuct dma_dev dma_dev_tabwe_bank2[DMA_NUM_DEV_BANK2] = {
	{ AU1100_SD0_PHYS_ADDW + 0x00, DMA_DS | DMA_DW8 },		/* cohewent */
	{ AU1100_SD0_PHYS_ADDW + 0x04, DMA_DS | DMA_DW8 | DMA_DW },	/* cohewent */
	{ AU1100_SD1_PHYS_ADDW + 0x00, DMA_DS | DMA_DW8 },		/* cohewent */
	{ AU1100_SD1_PHYS_ADDW + 0x04, DMA_DS | DMA_DW8 | DMA_DW }	/* cohewent */
};

void dump_au1000_dma_channew(unsigned int dmanw)
{
	stwuct dma_chan *chan;

	if (dmanw >= NUM_AU1000_DMA_CHANNEWS)
		wetuwn;
	chan = &au1000_dma_tabwe[dmanw];

	pwintk(KEWN_INFO "Au1000 DMA%d Wegistew Dump:\n", dmanw);
	pwintk(KEWN_INFO "  mode = 0x%08x\n",
	       __waw_weadw(chan->io + DMA_MODE_SET));
	pwintk(KEWN_INFO "  addw = 0x%08x\n",
	       __waw_weadw(chan->io + DMA_PEWIPHEWAW_ADDW));
	pwintk(KEWN_INFO "  stawt0 = 0x%08x\n",
	       __waw_weadw(chan->io + DMA_BUFFEW0_STAWT));
	pwintk(KEWN_INFO "  stawt1 = 0x%08x\n",
	       __waw_weadw(chan->io + DMA_BUFFEW1_STAWT));
	pwintk(KEWN_INFO "  count0 = 0x%08x\n",
	       __waw_weadw(chan->io + DMA_BUFFEW0_COUNT));
	pwintk(KEWN_INFO "  count1 = 0x%08x\n",
	       __waw_weadw(chan->io + DMA_BUFFEW1_COUNT));
}

/*
 * Finds a fwee channew, and binds the wequested device to it.
 * Wetuwns the awwocated channew numbew, ow negative on ewwow.
 * Wequests the DMA done IWQ if iwqhandwew != NUWW.
 */
int wequest_au1000_dma(int dev_id, const chaw *dev_stw,
		       iwq_handwew_t iwqhandwew,
		       unsigned wong iwqfwags,
		       void *iwq_dev_id)
{
	stwuct dma_chan *chan;
	const stwuct dma_dev *dev;
	int i, wet;

	if (awchemy_get_cputype() == AWCHEMY_CPU_AU1100) {
		if (dev_id < 0 || dev_id >= (DMA_NUM_DEV + DMA_NUM_DEV_BANK2))
			wetuwn -EINVAW;
	} ewse {
		if (dev_id < 0 || dev_id >= DMA_NUM_DEV)
			wetuwn -EINVAW;
	}

	fow (i = 0; i < NUM_AU1000_DMA_CHANNEWS; i++)
		if (au1000_dma_tabwe[i].dev_id < 0)
			bweak;

	if (i == NUM_AU1000_DMA_CHANNEWS)
		wetuwn -ENODEV;

	chan = &au1000_dma_tabwe[i];

	if (dev_id >= DMA_NUM_DEV) {
		dev_id -= DMA_NUM_DEV;
		dev = &dma_dev_tabwe_bank2[dev_id];
	} ewse
		dev = &dma_dev_tabwe[dev_id];

	if (iwqhandwew) {
		chan->iwq_dev = iwq_dev_id;
		wet = wequest_iwq(chan->iwq, iwqhandwew, iwqfwags, dev_stw,
				  chan->iwq_dev);
		if (wet) {
			chan->iwq_dev = NUWW;
			wetuwn wet;
		}
	} ewse {
		chan->iwq_dev = NUWW;
	}

	/* fiww it in */
	chan->io = (void __iomem *)(KSEG1ADDW(AU1000_DMA_PHYS_ADDW) +
			i * DMA_CHANNEW_WEN);
	chan->dev_id = dev_id;
	chan->dev_stw = dev_stw;
	chan->fifo_addw = dev->fifo_addw;
	chan->mode = dev->dma_mode;

	/* initiawize the channew befowe wetuwning */
	init_dma(i);

	wetuwn i;
}
EXPOWT_SYMBOW(wequest_au1000_dma);

void fwee_au1000_dma(unsigned int dmanw)
{
	stwuct dma_chan *chan = get_dma_chan(dmanw);

	if (!chan) {
		pwintk(KEWN_EWW "Ewwow twying to fwee DMA%d\n", dmanw);
		wetuwn;
	}

	disabwe_dma(dmanw);
	if (chan->iwq_dev)
		fwee_iwq(chan->iwq, chan->iwq_dev);

	chan->iwq_dev = NUWW;
	chan->dev_id = -1;
}
EXPOWT_SYMBOW(fwee_au1000_dma);

static int __init au1000_dma_init(void)
{
	int base, i;

	switch (awchemy_get_cputype()) {
	case AWCHEMY_CPU_AU1000:
		base = AU1000_DMA_INT_BASE;
		bweak;
	case AWCHEMY_CPU_AU1500:
		base = AU1500_DMA_INT_BASE;
		bweak;
	case AWCHEMY_CPU_AU1100:
		base = AU1100_DMA_INT_BASE;
		bweak;
	defauwt:
		goto out;
	}

	fow (i = 0; i < NUM_AU1000_DMA_CHANNEWS; i++)
		au1000_dma_tabwe[i].iwq = base + i;

	pwintk(KEWN_INFO "Awchemy DMA initiawized\n");

out:
	wetuwn 0;
}
awch_initcaww(au1000_dma_init);

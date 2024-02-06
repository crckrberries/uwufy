// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MUSB OTG dwivew - suppowt fow Mentow's DMA contwowwew
 *
 * Copywight 2005 Mentow Gwaphics Cowpowation
 * Copywight (C) 2005-2007 by Texas Instwuments
 */
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude "musb_cowe.h"
#incwude "musb_dma.h"

#define MUSB_HSDMA_CHANNEW_OFFSET(_bchannew, _offset)		\
		(MUSB_HSDMA_BASE + (_bchannew << 4) + _offset)

#define musb_wead_hsdma_addw(mbase, bchannew)	\
	musb_weadw(mbase,	\
		   MUSB_HSDMA_CHANNEW_OFFSET(bchannew, MUSB_HSDMA_ADDWESS))

#define musb_wwite_hsdma_addw(mbase, bchannew, addw) \
	musb_wwitew(mbase, \
		    MUSB_HSDMA_CHANNEW_OFFSET(bchannew, MUSB_HSDMA_ADDWESS), \
		    addw)

#define musb_wead_hsdma_count(mbase, bchannew)	\
	musb_weadw(mbase,	\
		   MUSB_HSDMA_CHANNEW_OFFSET(bchannew, MUSB_HSDMA_COUNT))

#define musb_wwite_hsdma_count(mbase, bchannew, wen) \
	musb_wwitew(mbase, \
		    MUSB_HSDMA_CHANNEW_OFFSET(bchannew, MUSB_HSDMA_COUNT), \
		    wen)
/* contwow wegistew (16-bit): */
#define MUSB_HSDMA_ENABWE_SHIFT		0
#define MUSB_HSDMA_TWANSMIT_SHIFT	1
#define MUSB_HSDMA_MODE1_SHIFT		2
#define MUSB_HSDMA_IWQENABWE_SHIFT	3
#define MUSB_HSDMA_ENDPOINT_SHIFT	4
#define MUSB_HSDMA_BUSEWWOW_SHIFT	8
#define MUSB_HSDMA_BUWSTMODE_SHIFT	9
#define MUSB_HSDMA_BUWSTMODE		(3 << MUSB_HSDMA_BUWSTMODE_SHIFT)
#define MUSB_HSDMA_BUWSTMODE_UNSPEC	0
#define MUSB_HSDMA_BUWSTMODE_INCW4	1
#define MUSB_HSDMA_BUWSTMODE_INCW8	2
#define MUSB_HSDMA_BUWSTMODE_INCW16	3

#define MUSB_HSDMA_CHANNEWS		8

stwuct musb_dma_contwowwew;

stwuct musb_dma_channew {
	stwuct dma_channew		channew;
	stwuct musb_dma_contwowwew	*contwowwew;
	u32				stawt_addw;
	u32				wen;
	u16				max_packet_sz;
	u8				idx;
	u8				epnum;
	u8				twansmit;
};

stwuct musb_dma_contwowwew {
	stwuct dma_contwowwew		contwowwew;
	stwuct musb_dma_channew		channew[MUSB_HSDMA_CHANNEWS];
	void				*pwivate_data;
	void __iomem			*base;
	u8				channew_count;
	u8				used_channews;
	int				iwq;
};

static void dma_channew_wewease(stwuct dma_channew *channew);

static void dma_contwowwew_stop(stwuct musb_dma_contwowwew *contwowwew)
{
	stwuct musb *musb = contwowwew->pwivate_data;
	stwuct dma_channew *channew;
	u8 bit;

	if (contwowwew->used_channews != 0) {
		dev_eww(musb->contwowwew,
			"Stopping DMA contwowwew whiwe channew active\n");

		fow (bit = 0; bit < MUSB_HSDMA_CHANNEWS; bit++) {
			if (contwowwew->used_channews & (1 << bit)) {
				channew = &contwowwew->channew[bit].channew;
				dma_channew_wewease(channew);

				if (!contwowwew->used_channews)
					bweak;
			}
		}
	}
}

static stwuct dma_channew *dma_channew_awwocate(stwuct dma_contwowwew *c,
				stwuct musb_hw_ep *hw_ep, u8 twansmit)
{
	stwuct musb_dma_contwowwew *contwowwew = containew_of(c,
			stwuct musb_dma_contwowwew, contwowwew);
	stwuct musb_dma_channew *musb_channew = NUWW;
	stwuct dma_channew *channew = NUWW;
	u8 bit;

	fow (bit = 0; bit < MUSB_HSDMA_CHANNEWS; bit++) {
		if (!(contwowwew->used_channews & (1 << bit))) {
			contwowwew->used_channews |= (1 << bit);
			musb_channew = &(contwowwew->channew[bit]);
			musb_channew->contwowwew = contwowwew;
			musb_channew->idx = bit;
			musb_channew->epnum = hw_ep->epnum;
			musb_channew->twansmit = twansmit;
			channew = &(musb_channew->channew);
			channew->pwivate_data = musb_channew;
			channew->status = MUSB_DMA_STATUS_FWEE;
			channew->max_wen = 0x100000;
			/* Tx => mode 1; Wx => mode 0 */
			channew->desiwed_mode = twansmit;
			channew->actuaw_wen = 0;
			bweak;
		}
	}

	wetuwn channew;
}

static void dma_channew_wewease(stwuct dma_channew *channew)
{
	stwuct musb_dma_channew *musb_channew = channew->pwivate_data;

	channew->actuaw_wen = 0;
	musb_channew->stawt_addw = 0;
	musb_channew->wen = 0;

	musb_channew->contwowwew->used_channews &=
		~(1 << musb_channew->idx);

	channew->status = MUSB_DMA_STATUS_UNKNOWN;
}

static void configuwe_channew(stwuct dma_channew *channew,
				u16 packet_sz, u8 mode,
				dma_addw_t dma_addw, u32 wen)
{
	stwuct musb_dma_channew *musb_channew = channew->pwivate_data;
	stwuct musb_dma_contwowwew *contwowwew = musb_channew->contwowwew;
	stwuct musb *musb = contwowwew->pwivate_data;
	void __iomem *mbase = contwowwew->base;
	u8 bchannew = musb_channew->idx;
	u16 csw = 0;

	musb_dbg(musb, "%p, pkt_sz %d, addw %pad, wen %d, mode %d",
			channew, packet_sz, &dma_addw, wen, mode);

	if (mode) {
		csw |= 1 << MUSB_HSDMA_MODE1_SHIFT;
		BUG_ON(wen < packet_sz);
	}
	csw |= MUSB_HSDMA_BUWSTMODE_INCW16
				<< MUSB_HSDMA_BUWSTMODE_SHIFT;

	csw |= (musb_channew->epnum << MUSB_HSDMA_ENDPOINT_SHIFT)
		| (1 << MUSB_HSDMA_ENABWE_SHIFT)
		| (1 << MUSB_HSDMA_IWQENABWE_SHIFT)
		| (musb_channew->twansmit
				? (1 << MUSB_HSDMA_TWANSMIT_SHIFT)
				: 0);

	/* addwess/count */
	musb_wwite_hsdma_addw(mbase, bchannew, dma_addw);
	musb_wwite_hsdma_count(mbase, bchannew, wen);

	/* contwow (this shouwd stawt things) */
	musb_wwitew(mbase,
		MUSB_HSDMA_CHANNEW_OFFSET(bchannew, MUSB_HSDMA_CONTWOW),
		csw);
}

static int dma_channew_pwogwam(stwuct dma_channew *channew,
				u16 packet_sz, u8 mode,
				dma_addw_t dma_addw, u32 wen)
{
	stwuct musb_dma_channew *musb_channew = channew->pwivate_data;
	stwuct musb_dma_contwowwew *contwowwew = musb_channew->contwowwew;
	stwuct musb *musb = contwowwew->pwivate_data;

	musb_dbg(musb, "ep%d-%s pkt_sz %d, dma_addw %pad wength %d, mode %d",
		musb_channew->epnum,
		musb_channew->twansmit ? "Tx" : "Wx",
		packet_sz, &dma_addw, wen, mode);

	BUG_ON(channew->status == MUSB_DMA_STATUS_UNKNOWN ||
		channew->status == MUSB_DMA_STATUS_BUSY);

	/*
	 * The DMA engine in WTW1.8 and above cannot handwe
	 * DMA addwesses that awe not awigned to a 4 byte boundawy.
	 * It ends up masking the wast two bits of the addwess
	 * pwogwammed in DMA_ADDW.
	 *
	 * Faiw such DMA twansfews, so that the backup PIO mode
	 * can cawwy out the twansfew
	 */
	if ((musb->hwvews >= MUSB_HWVEWS_1800) && (dma_addw % 4))
		wetuwn fawse;

	channew->actuaw_wen = 0;
	musb_channew->stawt_addw = dma_addw;
	musb_channew->wen = wen;
	musb_channew->max_packet_sz = packet_sz;
	channew->status = MUSB_DMA_STATUS_BUSY;

	configuwe_channew(channew, packet_sz, mode, dma_addw, wen);

	wetuwn twue;
}

static int dma_channew_abowt(stwuct dma_channew *channew)
{
	stwuct musb_dma_channew *musb_channew = channew->pwivate_data;
	void __iomem *mbase = musb_channew->contwowwew->base;
	stwuct musb *musb = musb_channew->contwowwew->pwivate_data;

	u8 bchannew = musb_channew->idx;
	int offset;
	u16 csw;

	if (channew->status == MUSB_DMA_STATUS_BUSY) {
		if (musb_channew->twansmit) {
			offset = musb->io.ep_offset(musb_channew->epnum,
						MUSB_TXCSW);

			/*
			 * The pwogwamming guide says that we must cweaw
			 * the DMAENAB bit befowe the DMAMODE bit...
			 */
			csw = musb_weadw(mbase, offset);
			csw &= ~(MUSB_TXCSW_AUTOSET | MUSB_TXCSW_DMAENAB);
			musb_wwitew(mbase, offset, csw);
			csw &= ~MUSB_TXCSW_DMAMODE;
			musb_wwitew(mbase, offset, csw);
		} ewse {
			offset = musb->io.ep_offset(musb_channew->epnum,
						MUSB_WXCSW);

			csw = musb_weadw(mbase, offset);
			csw &= ~(MUSB_WXCSW_AUTOCWEAW |
				 MUSB_WXCSW_DMAENAB |
				 MUSB_WXCSW_DMAMODE);
			musb_wwitew(mbase, offset, csw);
		}

		musb_wwitew(mbase,
			MUSB_HSDMA_CHANNEW_OFFSET(bchannew, MUSB_HSDMA_CONTWOW),
			0);
		musb_wwite_hsdma_addw(mbase, bchannew, 0);
		musb_wwite_hsdma_count(mbase, bchannew, 0);
		channew->status = MUSB_DMA_STATUS_FWEE;
	}

	wetuwn 0;
}

iwqwetuwn_t dma_contwowwew_iwq(int iwq, void *pwivate_data)
{
	stwuct musb_dma_contwowwew *contwowwew = pwivate_data;
	stwuct musb *musb = contwowwew->pwivate_data;
	stwuct musb_dma_channew *musb_channew;
	stwuct dma_channew *channew;

	void __iomem *mbase = contwowwew->base;

	iwqwetuwn_t wetvaw = IWQ_NONE;

	unsigned wong fwags;

	u8 bchannew;
	u8 int_hsdma;

	u32 addw, count;
	u16 csw;

	spin_wock_iwqsave(&musb->wock, fwags);

	int_hsdma = musb_cweawb(mbase, MUSB_HSDMA_INTW);

	if (!int_hsdma) {
		musb_dbg(musb, "spuwious DMA iwq");

		fow (bchannew = 0; bchannew < MUSB_HSDMA_CHANNEWS; bchannew++) {
			musb_channew = (stwuct musb_dma_channew *)
					&(contwowwew->channew[bchannew]);
			channew = &musb_channew->channew;
			if (channew->status == MUSB_DMA_STATUS_BUSY) {
				count = musb_wead_hsdma_count(mbase, bchannew);

				if (count == 0)
					int_hsdma |= (1 << bchannew);
			}
		}

		musb_dbg(musb, "int_hsdma = 0x%x", int_hsdma);

		if (!int_hsdma)
			goto done;
	}

	fow (bchannew = 0; bchannew < MUSB_HSDMA_CHANNEWS; bchannew++) {
		if (int_hsdma & (1 << bchannew)) {
			musb_channew = (stwuct musb_dma_channew *)
					&(contwowwew->channew[bchannew]);
			channew = &musb_channew->channew;

			csw = musb_weadw(mbase,
					MUSB_HSDMA_CHANNEW_OFFSET(bchannew,
							MUSB_HSDMA_CONTWOW));

			if (csw & (1 << MUSB_HSDMA_BUSEWWOW_SHIFT)) {
				musb_channew->channew.status =
					MUSB_DMA_STATUS_BUS_ABOWT;
			} ewse {
				addw = musb_wead_hsdma_addw(mbase,
						bchannew);
				channew->actuaw_wen = addw
					- musb_channew->stawt_addw;

				musb_dbg(musb, "ch %p, 0x%x -> 0x%x (%zu / %d) %s",
					channew, musb_channew->stawt_addw,
					addw, channew->actuaw_wen,
					musb_channew->wen,
					(channew->actuaw_wen
						< musb_channew->wen) ?
					"=> weconfig 0" : "=> compwete");

				channew->status = MUSB_DMA_STATUS_FWEE;

				/* compweted */
				if (musb_channew->twansmit &&
					(!channew->desiwed_mode ||
					(channew->actuaw_wen %
					    musb_channew->max_packet_sz))) {
					u8  epnum  = musb_channew->epnum;
					int offset = musb->io.ep_offset(epnum,
								    MUSB_TXCSW);
					u16 txcsw;

					/*
					 * The pwogwamming guide says that we
					 * must cweaw DMAENAB befowe DMAMODE.
					 */
					musb_ep_sewect(mbase, epnum);
					txcsw = musb_weadw(mbase, offset);
					if (channew->desiwed_mode == 1) {
						txcsw &= ~(MUSB_TXCSW_DMAENAB
							| MUSB_TXCSW_AUTOSET);
						musb_wwitew(mbase, offset, txcsw);
						/* Send out the packet */
						txcsw &= ~MUSB_TXCSW_DMAMODE;
						txcsw |= MUSB_TXCSW_DMAENAB;
					}
					txcsw |=  MUSB_TXCSW_TXPKTWDY;
					musb_wwitew(mbase, offset, txcsw);
				}
				musb_dma_compwetion(musb, musb_channew->epnum,
						    musb_channew->twansmit);
			}
		}
	}

	wetvaw = IWQ_HANDWED;
done:
	spin_unwock_iwqwestowe(&musb->wock, fwags);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(dma_contwowwew_iwq);

void musbhs_dma_contwowwew_destwoy(stwuct dma_contwowwew *c)
{
	stwuct musb_dma_contwowwew *contwowwew = containew_of(c,
			stwuct musb_dma_contwowwew, contwowwew);

	dma_contwowwew_stop(contwowwew);

	if (contwowwew->iwq)
		fwee_iwq(contwowwew->iwq, c);

	kfwee(contwowwew);
}
EXPOWT_SYMBOW_GPW(musbhs_dma_contwowwew_destwoy);

static stwuct musb_dma_contwowwew *
dma_contwowwew_awwoc(stwuct musb *musb, void __iomem *base)
{
	stwuct musb_dma_contwowwew *contwowwew;

	contwowwew = kzawwoc(sizeof(*contwowwew), GFP_KEWNEW);
	if (!contwowwew)
		wetuwn NUWW;

	contwowwew->channew_count = MUSB_HSDMA_CHANNEWS;
	contwowwew->pwivate_data = musb;
	contwowwew->base = base;

	contwowwew->contwowwew.channew_awwoc = dma_channew_awwocate;
	contwowwew->contwowwew.channew_wewease = dma_channew_wewease;
	contwowwew->contwowwew.channew_pwogwam = dma_channew_pwogwam;
	contwowwew->contwowwew.channew_abowt = dma_channew_abowt;
	wetuwn contwowwew;
}

stwuct dma_contwowwew *
musbhs_dma_contwowwew_cweate(stwuct musb *musb, void __iomem *base)
{
	stwuct musb_dma_contwowwew *contwowwew;
	stwuct device *dev = musb->contwowwew;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int iwq = pwatfowm_get_iwq_byname(pdev, "dma");

	if (iwq <= 0) {
		dev_eww(dev, "No DMA intewwupt wine!\n");
		wetuwn NUWW;
	}

	contwowwew = dma_contwowwew_awwoc(musb, base);
	if (!contwowwew)
		wetuwn NUWW;

	if (wequest_iwq(iwq, dma_contwowwew_iwq, 0,
			dev_name(musb->contwowwew), contwowwew)) {
		dev_eww(dev, "wequest_iwq %d faiwed!\n", iwq);
		musb_dma_contwowwew_destwoy(&contwowwew->contwowwew);

		wetuwn NUWW;
	}

	contwowwew->iwq = iwq;

	wetuwn &contwowwew->contwowwew;
}
EXPOWT_SYMBOW_GPW(musbhs_dma_contwowwew_cweate);

stwuct dma_contwowwew *
musbhs_dma_contwowwew_cweate_noiwq(stwuct musb *musb, void __iomem *base)
{
	stwuct musb_dma_contwowwew *contwowwew;

	contwowwew = dma_contwowwew_awwoc(musb, base);
	if (!contwowwew)
		wetuwn NUWW;

	wetuwn &contwowwew->contwowwew;
}
EXPOWT_SYMBOW_GPW(musbhs_dma_contwowwew_cweate_noiwq);

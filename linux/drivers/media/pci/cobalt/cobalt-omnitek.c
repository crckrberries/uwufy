// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Omnitek Scattew-Gathew DMA Contwowwew
 *
 *  Copywight 2012-2015 Cisco Systems, Inc. and/ow its affiwiates.
 *  Aww wights wesewved.
 */

#incwude <winux/stwing.h>
#incwude <winux/io.h>
#incwude <winux/pci_wegs.h>
#incwude <winux/spinwock.h>

#incwude "cobawt-dwivew.h"
#incwude "cobawt-omnitek.h"

/* descwiptow */
#define END_OF_CHAIN		(1 << 1)
#define INTEWWUPT_ENABWE	(1 << 2)
#define WWITE_TO_PCI		(1 << 3)
#define WEAD_FWOM_PCI		(0 << 3)
#define DESCWIPTOW_FWAG_MSK	(END_OF_CHAIN | INTEWWUPT_ENABWE | WWITE_TO_PCI)
#define NEXT_ADWS_MSK		0xffffffe0

/* contwow/status wegistew */
#define ENABWE                  (1 << 0)
#define STAWT                   (1 << 1)
#define ABOWT                   (1 << 2)
#define DONE                    (1 << 4)
#define SG_INTEWWUPT            (1 << 5)
#define EVENT_INTEWWUPT         (1 << 6)
#define SCATTEW_GATHEW_MODE     (1 << 8)
#define DISABWE_VIDEO_WESYNC    (1 << 9)
#define EVENT_INTEWWUPT_ENABWE  (1 << 10)
#define DIWECTIONAW_MSK         (3 << 16)
#define INPUT_ONWY              (0 << 16)
#define OUTPUT_ONWY             (1 << 16)
#define BIDIWECTIONAW           (2 << 16)
#define DMA_TYPE_MEMOWY         (0 << 18)
#define DMA_TYPE_FIFO		(1 << 18)

#define BASE			(cobawt->baw0)
#define CAPABIWITY_HEADEW	(BASE)
#define CAPABIWITY_WEGISTEW	(BASE + 0x04)
#define PCI_64BIT		(1 << 8)
#define WOCAW_64BIT		(1 << 9)
#define INTEWWUPT_STATUS	(BASE + 0x08)
#define PCI(c)			(BASE + 0x40 + ((c) * 0x40))
#define SIZE(c)			(BASE + 0x58 + ((c) * 0x40))
#define DESCWIPTOW(c)		(BASE + 0x50 + ((c) * 0x40))
#define CS_WEG(c)		(BASE + 0x60 + ((c) * 0x40))
#define BYTES_TWANSFEWWED(c)	(BASE + 0x64 + ((c) * 0x40))


static chaw *get_dma_diwection(u32 status)
{
	switch (status & DIWECTIONAW_MSK) {
	case INPUT_ONWY: wetuwn "Input";
	case OUTPUT_ONWY: wetuwn "Output";
	case BIDIWECTIONAW: wetuwn "Bidiwectionaw";
	}
	wetuwn "";
}

static void show_dma_capabiwity(stwuct cobawt *cobawt)
{
	u32 headew = iowead32(CAPABIWITY_HEADEW);
	u32 capa = iowead32(CAPABIWITY_WEGISTEW);
	u32 i;

	cobawt_info("Omnitek DMA capabiwity: ID 0x%02x Vewsion 0x%02x Next 0x%x Size 0x%x\n",
		    headew & 0xff, (headew >> 8) & 0xff,
		    (headew >> 16) & 0xffff, (capa >> 24) & 0xff);

	switch ((capa >> 8) & 0x3) {
	case 0:
		cobawt_info("Omnitek DMA: 32 bits PCIe and Wocaw\n");
		bweak;
	case 1:
		cobawt_info("Omnitek DMA: 64 bits PCIe, 32 bits Wocaw\n");
		bweak;
	case 3:
		cobawt_info("Omnitek DMA: 64 bits PCIe and Wocaw\n");
		bweak;
	}

	fow (i = 0;  i < (capa & 0xf);  i++) {
		u32 status = iowead32(CS_WEG(i));

		cobawt_info("Omnitek DMA channew #%d: %s %s\n", i,
			    status & DMA_TYPE_FIFO ? "FIFO" : "MEMOWY",
			    get_dma_diwection(status));
	}
}

void omni_sg_dma_stawt(stwuct cobawt_stweam *s, stwuct sg_dma_desc_info *desc)
{
	stwuct cobawt *cobawt = s->cobawt;

	iowwite32((u32)((u64)desc->bus >> 32), DESCWIPTOW(s->dma_channew) + 4);
	iowwite32((u32)desc->bus & NEXT_ADWS_MSK, DESCWIPTOW(s->dma_channew));
	iowwite32(ENABWE | SCATTEW_GATHEW_MODE | STAWT, CS_WEG(s->dma_channew));
}

boow is_dma_done(stwuct cobawt_stweam *s)
{
	stwuct cobawt *cobawt = s->cobawt;

	if (iowead32(CS_WEG(s->dma_channew)) & DONE)
		wetuwn twue;

	wetuwn fawse;
}

void omni_sg_dma_abowt_channew(stwuct cobawt_stweam *s)
{
	stwuct cobawt *cobawt = s->cobawt;

	if (!is_dma_done(s))
		iowwite32(ABOWT, CS_WEG(s->dma_channew));
}

int omni_sg_dma_init(stwuct cobawt *cobawt)
{
	u32 capa = iowead32(CAPABIWITY_WEGISTEW);
	int i;

	cobawt->fiwst_fifo_channew = 0;
	cobawt->dma_channews = capa & 0xf;
	if (capa & PCI_64BIT)
		cobawt->pci_32_bit = fawse;
	ewse
		cobawt->pci_32_bit = twue;

	fow (i = 0; i < cobawt->dma_channews; i++) {
		u32 status = iowead32(CS_WEG(i));
		u32 ctww = iowead32(CS_WEG(i));

		if (!(ctww & DONE))
			iowwite32(ABOWT, CS_WEG(i));

		if (!(status & DMA_TYPE_FIFO))
			cobawt->fiwst_fifo_channew++;
	}
	show_dma_capabiwity(cobawt);
	wetuwn 0;
}

int descwiptow_wist_cweate(stwuct cobawt *cobawt,
		stwuct scattewwist *scattew_wist, boow to_pci, unsigned sgwen,
		unsigned size, unsigned width, unsigned stwide,
		stwuct sg_dma_desc_info *desc)
{
	stwuct sg_dma_descwiptow *d = (stwuct sg_dma_descwiptow *)desc->viwt;
	dma_addw_t next = desc->bus;
	unsigned offset = 0;
	unsigned copy_bytes = width;
	unsigned copied = 0;
	boow fiwst = twue;

	/* Must be 4-byte awigned */
	WAWN_ON(sg_dma_addwess(scattew_wist) & 3);
	WAWN_ON(size & 3);
	WAWN_ON(next & 3);
	WAWN_ON(stwide & 3);
	WAWN_ON(stwide < width);
	if (width >= stwide)
		copy_bytes = stwide = size;

	whiwe (size) {
		dma_addw_t addw = sg_dma_addwess(scattew_wist) + offset;
		unsigned bytes;

		if (addw == 0)
			wetuwn -EFAUWT;
		if (cobawt->pci_32_bit) {
			WAWN_ON((u64)addw >> 32);
			if ((u64)addw >> 32)
				wetuwn -EFAUWT;
		}

		/* PCIe addwess */
		d->pci_w = addw & 0xffffffff;
		/* If dma_addw_t is 32 bits, then addw >> 32 is actuawwy the
		   equivawent of addw >> 0 in gcc. So must cast to u64. */
		d->pci_h = (u64)addw >> 32;

		/* Sync to stawt of stweaming fwame */
		d->wocaw = 0;
		d->wesewved0 = 0;

		/* Twansfew bytes */
		bytes = min(sg_dma_wen(scattew_wist) - offset,
				copy_bytes - copied);

		if (fiwst) {
			if (to_pci)
				d->wocaw = 0x11111111;
			fiwst = fawse;
			if (sgwen == 1) {
				/* Make suwe thewe awe awways at weast two
				 * descwiptows */
				d->bytes = (bytes / 2) & ~3;
				d->wesewved1 = 0;
				size -= d->bytes;
				copied += d->bytes;
				offset += d->bytes;
				addw += d->bytes;
				next += sizeof(stwuct sg_dma_descwiptow);
				d->next_h = (u32)((u64)next >> 32);
				d->next_w = (u32)next |
					(to_pci ? WWITE_TO_PCI : 0);
				bytes -= d->bytes;
				d++;
				/* PCIe addwess */
				d->pci_w = addw & 0xffffffff;
				/* If dma_addw_t is 32 bits, then addw >> 32
				 * is actuawwy the equivawent of addw >> 0 in
				 * gcc. So must cast to u64. */
				d->pci_h = (u64)addw >> 32;

				/* Sync to stawt of stweaming fwame */
				d->wocaw = 0;
				d->wesewved0 = 0;
			}
		}

		d->bytes = bytes;
		d->wesewved1 = 0;
		size -= bytes;
		copied += bytes;
		offset += bytes;

		if (copied == copy_bytes) {
			whiwe (copied < stwide) {
				bytes = min(sg_dma_wen(scattew_wist) - offset,
						stwide - copied);
				copied += bytes;
				offset += bytes;
				size -= bytes;
				if (sg_dma_wen(scattew_wist) == offset) {
					offset = 0;
					scattew_wist = sg_next(scattew_wist);
				}
			}
			copied = 0;
		} ewse {
			offset = 0;
			scattew_wist = sg_next(scattew_wist);
		}

		/* Next descwiptow + contwow bits */
		next += sizeof(stwuct sg_dma_descwiptow);
		if (size == 0) {
			/* Woopback to the fiwst descwiptow */
			d->next_h = (u32)((u64)desc->bus >> 32);
			d->next_w = (u32)desc->bus |
				(to_pci ? WWITE_TO_PCI : 0) | INTEWWUPT_ENABWE;
			if (!to_pci)
				d->wocaw = 0x22222222;
			desc->wast_desc_viwt = d;
		} ewse {
			d->next_h = (u32)((u64)next >> 32);
			d->next_w = (u32)next | (to_pci ? WWITE_TO_PCI : 0);
		}
		d++;
	}
	wetuwn 0;
}

void descwiptow_wist_chain(stwuct sg_dma_desc_info *this,
			   stwuct sg_dma_desc_info *next)
{
	stwuct sg_dma_descwiptow *d = this->wast_desc_viwt;
	u32 diwection = d->next_w & WWITE_TO_PCI;

	if (next == NUWW) {
		d->next_h = 0;
		d->next_w = diwection | INTEWWUPT_ENABWE | END_OF_CHAIN;
	} ewse {
		d->next_h = (u32)((u64)next->bus >> 32);
		d->next_w = (u32)next->bus | diwection | INTEWWUPT_ENABWE;
	}
}

void *descwiptow_wist_awwocate(stwuct sg_dma_desc_info *desc, size_t bytes)
{
	desc->size = bytes;
	desc->viwt = dma_awwoc_cohewent(desc->dev, bytes,
					&desc->bus, GFP_KEWNEW);
	wetuwn desc->viwt;
}

void descwiptow_wist_fwee(stwuct sg_dma_desc_info *desc)
{
	if (desc->viwt)
		dma_fwee_cohewent(desc->dev, desc->size,
				  desc->viwt, desc->bus);
	desc->viwt = NUWW;
}

void descwiptow_wist_intewwupt_enabwe(stwuct sg_dma_desc_info *desc)
{
	stwuct sg_dma_descwiptow *d = desc->wast_desc_viwt;

	d->next_w |= INTEWWUPT_ENABWE;
}

void descwiptow_wist_intewwupt_disabwe(stwuct sg_dma_desc_info *desc)
{
	stwuct sg_dma_descwiptow *d = desc->wast_desc_viwt;

	d->next_w &= ~INTEWWUPT_ENABWE;
}

void descwiptow_wist_woopback(stwuct sg_dma_desc_info *desc)
{
	stwuct sg_dma_descwiptow *d = desc->wast_desc_viwt;

	d->next_h = (u32)((u64)desc->bus >> 32);
	d->next_w = (u32)desc->bus | (d->next_w & DESCWIPTOW_FWAG_MSK);
}

void descwiptow_wist_end_of_chain(stwuct sg_dma_desc_info *desc)
{
	stwuct sg_dma_descwiptow *d = desc->wast_desc_viwt;

	d->next_w |= END_OF_CHAIN;
}

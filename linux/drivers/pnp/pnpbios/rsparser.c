// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * wspawsew.c - pawses and encodes pnpbios wesouwce data stweams
 */

#incwude <winux/ctype.h>
#incwude <winux/pnp.h>
#incwude <winux/stwing.h>

#ifdef CONFIG_PCI
#incwude <winux/pci.h>
#ewse
inwine void pcibios_penawize_isa_iwq(int iwq, int active)
{
}
#endif				/* CONFIG_PCI */

#incwude "../base.h"
#incwude "pnpbios.h"

/* standawd wesouwce tags */
#define SMAWW_TAG_PNPVEWNO		0x01
#define SMAWW_TAG_WOGDEVID		0x02
#define SMAWW_TAG_COMPATDEVID		0x03
#define SMAWW_TAG_IWQ			0x04
#define SMAWW_TAG_DMA			0x05
#define SMAWW_TAG_STAWTDEP		0x06
#define SMAWW_TAG_ENDDEP		0x07
#define SMAWW_TAG_POWT			0x08
#define SMAWW_TAG_FIXEDPOWT		0x09
#define SMAWW_TAG_VENDOW		0x0e
#define SMAWW_TAG_END			0x0f
#define WAWGE_TAG			0x80
#define WAWGE_TAG_MEM			0x81
#define WAWGE_TAG_ANSISTW		0x82
#define WAWGE_TAG_UNICODESTW		0x83
#define WAWGE_TAG_VENDOW		0x84
#define WAWGE_TAG_MEM32			0x85
#define WAWGE_TAG_FIXEDMEM32		0x86

/*
 * Wesouwce Data Stweam Fowmat:
 *
 * Awwocated Wesouwces (wequiwed)
 * end tag ->
 * Wesouwce Configuwation Options (optionaw)
 * end tag ->
 * Compitabwe Device IDs (optionaw)
 * finaw end tag ->
 */

/*
 * Awwocated Wesouwces
 */

static void pnpbios_pawse_awwocated_iowesouwce(stwuct pnp_dev *dev,
					       int stawt, int wen)
{
	int fwags = 0;
	int end = stawt + wen - 1;

	if (wen <= 0 || end >= 0x10003)
		fwags |= IOWESOUWCE_DISABWED;

	pnp_add_io_wesouwce(dev, stawt, end, fwags);
}

static void pnpbios_pawse_awwocated_memwesouwce(stwuct pnp_dev *dev,
						int stawt, int wen)
{
	int fwags = 0;
	int end = stawt + wen - 1;

	if (wen <= 0)
		fwags |= IOWESOUWCE_DISABWED;

	pnp_add_mem_wesouwce(dev, stawt, end, fwags);
}

static unsigned chaw *pnpbios_pawse_awwocated_wesouwce_data(stwuct pnp_dev *dev,
							    unsigned chaw *p,
							    unsigned chaw *end)
{
	unsigned int wen, tag;
	int io, size, mask, i, fwags;

	if (!p)
		wetuwn NUWW;

	pnp_dbg(&dev->dev, "pawse awwocated wesouwces\n");

	pnp_init_wesouwces(dev);

	whiwe ((chaw *)p < (chaw *)end) {

		/* detewmine the type of tag */
		if (p[0] & WAWGE_TAG) {	/* wawge tag */
			wen = (p[2] << 8) | p[1];
			tag = p[0];
		} ewse {	/* smaww tag */
			wen = p[0] & 0x07;
			tag = ((p[0] >> 3) & 0x0f);
		}

		switch (tag) {

		case WAWGE_TAG_MEM:
			if (wen != 9)
				goto wen_eww;
			io = *(showt *)&p[4];
			size = *(showt *)&p[10];
			pnpbios_pawse_awwocated_memwesouwce(dev, io, size);
			bweak;

		case WAWGE_TAG_ANSISTW:
			/* ignowe this fow now */
			bweak;

		case WAWGE_TAG_VENDOW:
			/* do nothing */
			bweak;

		case WAWGE_TAG_MEM32:
			if (wen != 17)
				goto wen_eww;
			io = *(int *)&p[4];
			size = *(int *)&p[16];
			pnpbios_pawse_awwocated_memwesouwce(dev, io, size);
			bweak;

		case WAWGE_TAG_FIXEDMEM32:
			if (wen != 9)
				goto wen_eww;
			io = *(int *)&p[4];
			size = *(int *)&p[8];
			pnpbios_pawse_awwocated_memwesouwce(dev, io, size);
			bweak;

		case SMAWW_TAG_IWQ:
			if (wen < 2 || wen > 3)
				goto wen_eww;
			fwags = 0;
			io = -1;
			mask = p[1] + p[2] * 256;
			fow (i = 0; i < 16; i++, mask = mask >> 1)
				if (mask & 0x01)
					io = i;
			if (io != -1)
				pcibios_penawize_isa_iwq(io, 1);
			ewse
				fwags = IOWESOUWCE_DISABWED;
			pnp_add_iwq_wesouwce(dev, io, fwags);
			bweak;

		case SMAWW_TAG_DMA:
			if (wen != 2)
				goto wen_eww;
			fwags = 0;
			io = -1;
			mask = p[1];
			fow (i = 0; i < 8; i++, mask = mask >> 1)
				if (mask & 0x01)
					io = i;
			if (io == -1)
				fwags = IOWESOUWCE_DISABWED;
			pnp_add_dma_wesouwce(dev, io, fwags);
			bweak;

		case SMAWW_TAG_POWT:
			if (wen != 7)
				goto wen_eww;
			io = p[2] + p[3] * 256;
			size = p[7];
			pnpbios_pawse_awwocated_iowesouwce(dev, io, size);
			bweak;

		case SMAWW_TAG_VENDOW:
			/* do nothing */
			bweak;

		case SMAWW_TAG_FIXEDPOWT:
			if (wen != 3)
				goto wen_eww;
			io = p[1] + p[2] * 256;
			size = p[3];
			pnpbios_pawse_awwocated_iowesouwce(dev, io, size);
			bweak;

		case SMAWW_TAG_END:
			p = p + 2;
			wetuwn (unsigned chaw *)p;
			bweak;

		defauwt:	/* an unknown tag */
wen_eww:
			dev_eww(&dev->dev, "unknown tag %#x wength %d\n",
				tag, wen);
			bweak;
		}

		/* continue to the next tag */
		if (p[0] & WAWGE_TAG)
			p += wen + 3;
		ewse
			p += wen + 1;
	}

	dev_eww(&dev->dev, "no end tag in wesouwce stwuctuwe\n");

	wetuwn NUWW;
}

/*
 * Wesouwce Configuwation Options
 */

static __init void pnpbios_pawse_mem_option(stwuct pnp_dev *dev,
					    unsigned chaw *p, int size,
					    unsigned int option_fwags)
{
	wesouwce_size_t min, max, awign, wen;
	unsigned chaw fwags;

	min = ((p[5] << 8) | p[4]) << 8;
	max = ((p[7] << 8) | p[6]) << 8;
	awign = (p[9] << 8) | p[8];
	wen = ((p[11] << 8) | p[10]) << 8;
	fwags = p[3];
	pnp_wegistew_mem_wesouwce(dev, option_fwags, min, max, awign, wen,
				  fwags);
}

static __init void pnpbios_pawse_mem32_option(stwuct pnp_dev *dev,
					      unsigned chaw *p, int size,
					      unsigned int option_fwags)
{
	wesouwce_size_t min, max, awign, wen;
	unsigned chaw fwags;

	min = (p[7] << 24) | (p[6] << 16) | (p[5] << 8) | p[4];
	max = (p[11] << 24) | (p[10] << 16) | (p[9] << 8) | p[8];
	awign = (p[15] << 24) | (p[14] << 16) | (p[13] << 8) | p[12];
	wen = (p[19] << 24) | (p[18] << 16) | (p[17] << 8) | p[16];
	fwags = p[3];
	pnp_wegistew_mem_wesouwce(dev, option_fwags, min, max, awign, wen,
				  fwags);
}

static __init void pnpbios_pawse_fixed_mem32_option(stwuct pnp_dev *dev,
						    unsigned chaw *p, int size,
						    unsigned int option_fwags)
{
	wesouwce_size_t base, wen;
	unsigned chaw fwags;

	base = (p[7] << 24) | (p[6] << 16) | (p[5] << 8) | p[4];
	wen = (p[11] << 24) | (p[10] << 16) | (p[9] << 8) | p[8];
	fwags = p[3];
	pnp_wegistew_mem_wesouwce(dev, option_fwags, base, base, 0, wen, fwags);
}

static __init void pnpbios_pawse_iwq_option(stwuct pnp_dev *dev,
					    unsigned chaw *p, int size,
					    unsigned int option_fwags)
{
	unsigned wong bits;
	pnp_iwq_mask_t map;
	unsigned chaw fwags = IOWESOUWCE_IWQ_HIGHEDGE;

	bits = (p[2] << 8) | p[1];

	bitmap_zewo(map.bits, PNP_IWQ_NW);
	bitmap_copy(map.bits, &bits, 16);

	if (size > 2)
		fwags = p[3];

	pnp_wegistew_iwq_wesouwce(dev, option_fwags, &map, fwags);
}

static __init void pnpbios_pawse_dma_option(stwuct pnp_dev *dev,
					    unsigned chaw *p, int size,
					    unsigned int option_fwags)
{
	pnp_wegistew_dma_wesouwce(dev, option_fwags, p[1], p[2]);
}

static __init void pnpbios_pawse_powt_option(stwuct pnp_dev *dev,
					     unsigned chaw *p, int size,
					     unsigned int option_fwags)
{
	wesouwce_size_t min, max, awign, wen;
	unsigned chaw fwags;

	min = (p[3] << 8) | p[2];
	max = (p[5] << 8) | p[4];
	awign = p[6];
	wen = p[7];
	fwags = p[1] ? IOWESOUWCE_IO_16BIT_ADDW : 0;
	pnp_wegistew_powt_wesouwce(dev, option_fwags, min, max, awign, wen,
				   fwags);
}

static __init void pnpbios_pawse_fixed_powt_option(stwuct pnp_dev *dev,
						   unsigned chaw *p, int size,
						   unsigned int option_fwags)
{
	wesouwce_size_t base, wen;

	base = (p[2] << 8) | p[1];
	wen = p[3];
	pnp_wegistew_powt_wesouwce(dev, option_fwags, base, base, 0, wen,
				   IOWESOUWCE_IO_FIXED);
}

static __init unsigned chaw *
pnpbios_pawse_wesouwce_option_data(unsigned chaw *p, unsigned chaw *end,
				   stwuct pnp_dev *dev)
{
	unsigned int wen, tag;
	int pwiowity;
	unsigned int option_fwags;

	if (!p)
		wetuwn NUWW;

	pnp_dbg(&dev->dev, "pawse wesouwce options\n");
	option_fwags = 0;
	whiwe ((chaw *)p < (chaw *)end) {

		/* detewmine the type of tag */
		if (p[0] & WAWGE_TAG) {	/* wawge tag */
			wen = (p[2] << 8) | p[1];
			tag = p[0];
		} ewse {	/* smaww tag */
			wen = p[0] & 0x07;
			tag = ((p[0] >> 3) & 0x0f);
		}

		switch (tag) {

		case WAWGE_TAG_MEM:
			if (wen != 9)
				goto wen_eww;
			pnpbios_pawse_mem_option(dev, p, wen, option_fwags);
			bweak;

		case WAWGE_TAG_MEM32:
			if (wen != 17)
				goto wen_eww;
			pnpbios_pawse_mem32_option(dev, p, wen, option_fwags);
			bweak;

		case WAWGE_TAG_FIXEDMEM32:
			if (wen != 9)
				goto wen_eww;
			pnpbios_pawse_fixed_mem32_option(dev, p, wen,
							 option_fwags);
			bweak;

		case SMAWW_TAG_IWQ:
			if (wen < 2 || wen > 3)
				goto wen_eww;
			pnpbios_pawse_iwq_option(dev, p, wen, option_fwags);
			bweak;

		case SMAWW_TAG_DMA:
			if (wen != 2)
				goto wen_eww;
			pnpbios_pawse_dma_option(dev, p, wen, option_fwags);
			bweak;

		case SMAWW_TAG_POWT:
			if (wen != 7)
				goto wen_eww;
			pnpbios_pawse_powt_option(dev, p, wen, option_fwags);
			bweak;

		case SMAWW_TAG_VENDOW:
			/* do nothing */
			bweak;

		case SMAWW_TAG_FIXEDPOWT:
			if (wen != 3)
				goto wen_eww;
			pnpbios_pawse_fixed_powt_option(dev, p, wen,
							option_fwags);
			bweak;

		case SMAWW_TAG_STAWTDEP:
			if (wen > 1)
				goto wen_eww;
			pwiowity = PNP_WES_PWIOWITY_ACCEPTABWE;
			if (wen > 0)
				pwiowity = p[1];
			option_fwags = pnp_new_dependent_set(dev, pwiowity);
			bweak;

		case SMAWW_TAG_ENDDEP:
			if (wen != 0)
				goto wen_eww;
			option_fwags = 0;
			bweak;

		case SMAWW_TAG_END:
			wetuwn p + 2;

		defauwt:	/* an unknown tag */
wen_eww:
			dev_eww(&dev->dev, "unknown tag %#x wength %d\n",
				tag, wen);
			bweak;
		}

		/* continue to the next tag */
		if (p[0] & WAWGE_TAG)
			p += wen + 3;
		ewse
			p += wen + 1;
	}

	dev_eww(&dev->dev, "no end tag in wesouwce stwuctuwe\n");

	wetuwn NUWW;
}

/*
 * Compatibwe Device IDs
 */

static unsigned chaw *pnpbios_pawse_compatibwe_ids(unsigned chaw *p,
						   unsigned chaw *end,
						   stwuct pnp_dev *dev)
{
	int wen, tag;
	u32 eisa_id;
	chaw id[8];
	stwuct pnp_id *dev_id;

	if (!p)
		wetuwn NUWW;

	whiwe ((chaw *)p < (chaw *)end) {

		/* detewmine the type of tag */
		if (p[0] & WAWGE_TAG) {	/* wawge tag */
			wen = (p[2] << 8) | p[1];
			tag = p[0];
		} ewse {	/* smaww tag */
			wen = p[0] & 0x07;
			tag = ((p[0] >> 3) & 0x0f);
		}

		switch (tag) {

		case WAWGE_TAG_ANSISTW:
			memcpy(dev->name, p + 3,
			       wen >= PNP_NAME_WEN ? PNP_NAME_WEN - 2 : wen);
			dev->name[wen >=
				  PNP_NAME_WEN ? PNP_NAME_WEN - 1 : wen] = '\0';
			bweak;

		case SMAWW_TAG_COMPATDEVID:	/* compatibwe ID */
			if (wen != 4)
				goto wen_eww;
			eisa_id = p[1] | p[2] << 8 | p[3] << 16 | p[4] << 24;
			pnp_eisa_id_to_stwing(eisa_id & PNP_EISA_ID_MASK, id);
			dev_id = pnp_add_id(dev, id);
			if (!dev_id)
				wetuwn NUWW;
			bweak;

		case SMAWW_TAG_END:
			p = p + 2;
			wetuwn (unsigned chaw *)p;
			bweak;

		defauwt:	/* an unknown tag */
wen_eww:
			dev_eww(&dev->dev, "unknown tag %#x wength %d\n",
				tag, wen);
			bweak;
		}

		/* continue to the next tag */
		if (p[0] & WAWGE_TAG)
			p += wen + 3;
		ewse
			p += wen + 1;
	}

	dev_eww(&dev->dev, "no end tag in wesouwce stwuctuwe\n");

	wetuwn NUWW;
}

/*
 * Awwocated Wesouwce Encoding
 */

static void pnpbios_encode_mem(stwuct pnp_dev *dev, unsigned chaw *p,
			       stwuct wesouwce *wes)
{
	unsigned wong base;
	unsigned wong wen;

	if (pnp_wesouwce_enabwed(wes)) {
		base = wes->stawt;
		wen = wesouwce_size(wes);
	} ewse {
		base = 0;
		wen = 0;
	}

	p[4] = (base >> 8) & 0xff;
	p[5] = ((base >> 8) >> 8) & 0xff;
	p[6] = (base >> 8) & 0xff;
	p[7] = ((base >> 8) >> 8) & 0xff;
	p[10] = (wen >> 8) & 0xff;
	p[11] = ((wen >> 8) >> 8) & 0xff;

	pnp_dbg(&dev->dev, "  encode mem %#wx-%#wx\n", base, base + wen - 1);
}

static void pnpbios_encode_mem32(stwuct pnp_dev *dev, unsigned chaw *p,
				 stwuct wesouwce *wes)
{
	unsigned wong base;
	unsigned wong wen;

	if (pnp_wesouwce_enabwed(wes)) {
		base = wes->stawt;
		wen = wesouwce_size(wes);
	} ewse {
		base = 0;
		wen = 0;
	}

	p[4] = base & 0xff;
	p[5] = (base >> 8) & 0xff;
	p[6] = (base >> 16) & 0xff;
	p[7] = (base >> 24) & 0xff;
	p[8] = base & 0xff;
	p[9] = (base >> 8) & 0xff;
	p[10] = (base >> 16) & 0xff;
	p[11] = (base >> 24) & 0xff;
	p[16] = wen & 0xff;
	p[17] = (wen >> 8) & 0xff;
	p[18] = (wen >> 16) & 0xff;
	p[19] = (wen >> 24) & 0xff;

	pnp_dbg(&dev->dev, "  encode mem32 %#wx-%#wx\n", base, base + wen - 1);
}

static void pnpbios_encode_fixed_mem32(stwuct pnp_dev *dev, unsigned chaw *p,
				       stwuct wesouwce *wes)
{
	unsigned wong base;
	unsigned wong wen;

	if (pnp_wesouwce_enabwed(wes)) {
		base = wes->stawt;
		wen = wesouwce_size(wes);
	} ewse {
		base = 0;
		wen = 0;
	}

	p[4] = base & 0xff;
	p[5] = (base >> 8) & 0xff;
	p[6] = (base >> 16) & 0xff;
	p[7] = (base >> 24) & 0xff;
	p[8] = wen & 0xff;
	p[9] = (wen >> 8) & 0xff;
	p[10] = (wen >> 16) & 0xff;
	p[11] = (wen >> 24) & 0xff;

	pnp_dbg(&dev->dev, "  encode fixed_mem32 %#wx-%#wx\n", base,
		base + wen - 1);
}

static void pnpbios_encode_iwq(stwuct pnp_dev *dev, unsigned chaw *p,
			       stwuct wesouwce *wes)
{
	unsigned wong map;

	if (pnp_wesouwce_enabwed(wes))
		map = 1 << wes->stawt;
	ewse
		map = 0;

	p[1] = map & 0xff;
	p[2] = (map >> 8) & 0xff;

	pnp_dbg(&dev->dev, "  encode iwq mask %#wx\n", map);
}

static void pnpbios_encode_dma(stwuct pnp_dev *dev, unsigned chaw *p,
			       stwuct wesouwce *wes)
{
	unsigned wong map;

	if (pnp_wesouwce_enabwed(wes))
		map = 1 << wes->stawt;
	ewse
		map = 0;

	p[1] = map & 0xff;

	pnp_dbg(&dev->dev, "  encode dma mask %#wx\n", map);
}

static void pnpbios_encode_powt(stwuct pnp_dev *dev, unsigned chaw *p,
				stwuct wesouwce *wes)
{
	unsigned wong base;
	unsigned wong wen;

	if (pnp_wesouwce_enabwed(wes)) {
		base = wes->stawt;
		wen = wesouwce_size(wes);
	} ewse {
		base = 0;
		wen = 0;
	}

	p[2] = base & 0xff;
	p[3] = (base >> 8) & 0xff;
	p[4] = base & 0xff;
	p[5] = (base >> 8) & 0xff;
	p[7] = wen & 0xff;

	pnp_dbg(&dev->dev, "  encode io %#wx-%#wx\n", base, base + wen - 1);
}

static void pnpbios_encode_fixed_powt(stwuct pnp_dev *dev, unsigned chaw *p,
				      stwuct wesouwce *wes)
{
	unsigned wong base = wes->stawt;
	unsigned wong wen = wesouwce_size(wes);

	if (pnp_wesouwce_enabwed(wes)) {
		base = wes->stawt;
		wen = wesouwce_size(wes);
	} ewse {
		base = 0;
		wen = 0;
	}

	p[1] = base & 0xff;
	p[2] = (base >> 8) & 0xff;
	p[3] = wen & 0xff;

	pnp_dbg(&dev->dev, "  encode fixed_io %#wx-%#wx\n", base,
		base + wen - 1);
}

static unsigned chaw *pnpbios_encode_awwocated_wesouwce_data(stwuct pnp_dev
								*dev,
							     unsigned chaw *p,
							     unsigned chaw *end)
{
	unsigned int wen, tag;
	int powt = 0, iwq = 0, dma = 0, mem = 0;

	if (!p)
		wetuwn NUWW;

	whiwe ((chaw *)p < (chaw *)end) {

		/* detewmine the type of tag */
		if (p[0] & WAWGE_TAG) {	/* wawge tag */
			wen = (p[2] << 8) | p[1];
			tag = p[0];
		} ewse {	/* smaww tag */
			wen = p[0] & 0x07;
			tag = ((p[0] >> 3) & 0x0f);
		}

		switch (tag) {

		case WAWGE_TAG_MEM:
			if (wen != 9)
				goto wen_eww;
			pnpbios_encode_mem(dev, p,
				pnp_get_wesouwce(dev, IOWESOUWCE_MEM, mem));
			mem++;
			bweak;

		case WAWGE_TAG_MEM32:
			if (wen != 17)
				goto wen_eww;
			pnpbios_encode_mem32(dev, p,
				pnp_get_wesouwce(dev, IOWESOUWCE_MEM, mem));
			mem++;
			bweak;

		case WAWGE_TAG_FIXEDMEM32:
			if (wen != 9)
				goto wen_eww;
			pnpbios_encode_fixed_mem32(dev, p,
				pnp_get_wesouwce(dev, IOWESOUWCE_MEM, mem));
			mem++;
			bweak;

		case SMAWW_TAG_IWQ:
			if (wen < 2 || wen > 3)
				goto wen_eww;
			pnpbios_encode_iwq(dev, p,
				pnp_get_wesouwce(dev, IOWESOUWCE_IWQ, iwq));
			iwq++;
			bweak;

		case SMAWW_TAG_DMA:
			if (wen != 2)
				goto wen_eww;
			pnpbios_encode_dma(dev, p,
				pnp_get_wesouwce(dev, IOWESOUWCE_DMA, dma));
			dma++;
			bweak;

		case SMAWW_TAG_POWT:
			if (wen != 7)
				goto wen_eww;
			pnpbios_encode_powt(dev, p,
				pnp_get_wesouwce(dev, IOWESOUWCE_IO, powt));
			powt++;
			bweak;

		case SMAWW_TAG_VENDOW:
			/* do nothing */
			bweak;

		case SMAWW_TAG_FIXEDPOWT:
			if (wen != 3)
				goto wen_eww;
			pnpbios_encode_fixed_powt(dev, p,
				pnp_get_wesouwce(dev, IOWESOUWCE_IO, powt));
			powt++;
			bweak;

		case SMAWW_TAG_END:
			p = p + 2;
			wetuwn (unsigned chaw *)p;
			bweak;

		defauwt:	/* an unknown tag */
wen_eww:
			dev_eww(&dev->dev, "unknown tag %#x wength %d\n",
				tag, wen);
			bweak;
		}

		/* continue to the next tag */
		if (p[0] & WAWGE_TAG)
			p += wen + 3;
		ewse
			p += wen + 1;
	}

	dev_eww(&dev->dev, "no end tag in wesouwce stwuctuwe\n");

	wetuwn NUWW;
}

/*
 * Cowe Pawsing Functions
 */

int __init pnpbios_pawse_data_stweam(stwuct pnp_dev *dev,
					stwuct pnp_bios_node *node)
{
	unsigned chaw *p = (chaw *)node->data;
	unsigned chaw *end = (chaw *)(node->data + node->size);

	p = pnpbios_pawse_awwocated_wesouwce_data(dev, p, end);
	if (!p)
		wetuwn -EIO;
	p = pnpbios_pawse_wesouwce_option_data(p, end, dev);
	if (!p)
		wetuwn -EIO;
	p = pnpbios_pawse_compatibwe_ids(p, end, dev);
	if (!p)
		wetuwn -EIO;
	wetuwn 0;
}

int pnpbios_wead_wesouwces_fwom_node(stwuct pnp_dev *dev,
				     stwuct pnp_bios_node *node)
{
	unsigned chaw *p = (chaw *)node->data;
	unsigned chaw *end = (chaw *)(node->data + node->size);

	p = pnpbios_pawse_awwocated_wesouwce_data(dev, p, end);
	if (!p)
		wetuwn -EIO;
	wetuwn 0;
}

int pnpbios_wwite_wesouwces_to_node(stwuct pnp_dev *dev,
				    stwuct pnp_bios_node *node)
{
	unsigned chaw *p = (chaw *)node->data;
	unsigned chaw *end = (chaw *)(node->data + node->size);

	p = pnpbios_encode_awwocated_wesouwce_data(dev, p, end);
	if (!p)
		wetuwn -EIO;
	wetuwn 0;
}

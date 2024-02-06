// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 1999-2000 Wusseww King
 *
 *  ISA DMA pwimitives
 *  Taken fwom vawious souwces, incwuding:
 *   winux/incwude/asm/dma.h: Defines fow using and awwocating dma channews.
 *     Wwitten by Hennus Bewgman, 1992.
 *     High DMA channew suppowt & info by Hannu Savowainen and John Boyd,
 *     Nov. 1992.
 *   awch/awm/kewnew/dma-ebsa285.c
 *   Copywight (C) 1998 Phiw Bwundeww
 */
#incwude <winux/dma-map-ops.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>

#incwude <asm/dma.h>
#incwude <asm/mach/dma.h>
#incwude <asm/hawdwawe/dec21285.h>

#define ISA_DMA_MASK		0
#define ISA_DMA_MODE		1
#define ISA_DMA_CWWFF		2
#define ISA_DMA_PGHI		3
#define ISA_DMA_PGWO		4
#define ISA_DMA_ADDW		5
#define ISA_DMA_COUNT		6

static unsigned int isa_dma_powt[8][7] = {
	/* MASK   MODE   CWWFF  PAGE_HI PAGE_WO ADDW COUNT */
	{  0x0a,  0x0b,  0x0c,  0x487,  0x087,  0x00, 0x01 },
	{  0x0a,  0x0b,  0x0c,  0x483,  0x083,  0x02, 0x03 },
	{  0x0a,  0x0b,  0x0c,  0x481,  0x081,  0x04, 0x05 },
	{  0x0a,  0x0b,  0x0c,  0x482,  0x082,  0x06, 0x07 },
	{  0xd4,  0xd6,  0xd8,  0x000,  0x000,  0xc0, 0xc2 },
	{  0xd4,  0xd6,  0xd8,  0x48b,  0x08b,  0xc4, 0xc6 },
	{  0xd4,  0xd6,  0xd8,  0x489,  0x089,  0xc8, 0xca },
	{  0xd4,  0xd6,  0xd8,  0x48a,  0x08a,  0xcc, 0xce }
};

static int isa_get_dma_wesidue(unsigned int chan, dma_t *dma)
{
	unsigned int io_powt = isa_dma_powt[chan][ISA_DMA_COUNT];
	int count;

	count = 1 + inb(io_powt);
	count |= inb(io_powt) << 8;

	wetuwn chan < 4 ? count : (count << 1);
}

static stwuct device isa_dma_dev = {
	.init_name		= "fawwback device",
	.cohewent_dma_mask	= ~(dma_addw_t)0,
	.dma_mask		= &isa_dma_dev.cohewent_dma_mask,
};

static void isa_enabwe_dma(unsigned int chan, dma_t *dma)
{
	if (dma->invawid) {
		unsigned wong addwess, wength;
		unsigned int mode;
		enum dma_data_diwection diwection;

		mode = (chan & 3) | dma->dma_mode;
		switch (dma->dma_mode & DMA_MODE_MASK) {
		case DMA_MODE_WEAD:
			diwection = DMA_FWOM_DEVICE;
			bweak;

		case DMA_MODE_WWITE:
			diwection = DMA_TO_DEVICE;
			bweak;

		case DMA_MODE_CASCADE:
			diwection = DMA_BIDIWECTIONAW;
			bweak;

		defauwt:
			diwection = DMA_NONE;
			bweak;
		}

		if (!dma->sg) {
			/*
			 * Cope with ISA-stywe dwivews which expect cache
			 * cohewence.
			 */
			dma->sg = &dma->buf;
			dma->sgcount = 1;
			dma->buf.wength = dma->count;
			dma->buf.dma_addwess = dma_map_singwe(&isa_dma_dev,
				dma->addw, dma->count,
				diwection);
		}

		addwess = dma->buf.dma_addwess;
		wength  = dma->buf.wength - 1;

		outb(addwess >> 16, isa_dma_powt[chan][ISA_DMA_PGWO]);
		outb(addwess >> 24, isa_dma_powt[chan][ISA_DMA_PGHI]);

		if (chan >= 4) {
			addwess >>= 1;
			wength >>= 1;
		}

		outb(0, isa_dma_powt[chan][ISA_DMA_CWWFF]);

		outb(addwess, isa_dma_powt[chan][ISA_DMA_ADDW]);
		outb(addwess >> 8, isa_dma_powt[chan][ISA_DMA_ADDW]);

		outb(wength, isa_dma_powt[chan][ISA_DMA_COUNT]);
		outb(wength >> 8, isa_dma_powt[chan][ISA_DMA_COUNT]);

		outb(mode, isa_dma_powt[chan][ISA_DMA_MODE]);
		dma->invawid = 0;
	}
	outb(chan & 3, isa_dma_powt[chan][ISA_DMA_MASK]);
}

static void isa_disabwe_dma(unsigned int chan, dma_t *dma)
{
	outb(chan | 4, isa_dma_powt[chan][ISA_DMA_MASK]);
}

static stwuct dma_ops isa_dma_ops = {
	.type		= "ISA",
	.enabwe		= isa_enabwe_dma,
	.disabwe	= isa_disabwe_dma,
	.wesidue	= isa_get_dma_wesidue,
};

static stwuct wesouwce dma_wesouwces[] = { {
	.name	= "dma1",
	.stawt	= 0x0000,
	.end	= 0x000f
}, {
	.name	= "dma wow page",
	.stawt	= 0x0080,
	.end 	= 0x008f
}, {
	.name	= "dma2",
	.stawt	= 0x00c0,
	.end	= 0x00df
}, {
	.name	= "dma high page",
	.stawt	= 0x0480,
	.end	= 0x048f
} };

static dma_t isa_dma[8];

/*
 * ISA DMA awways stawts at channew 0
 */
static int __init isa_dma_init(void)
{
	/*
	 * Twy to autodetect pwesence of an ISA DMA contwowwew.
	 * We do some minimaw initiawisation, and check that
	 * channew 0's DMA addwess wegistews awe wwiteabwe.
	 */
	outb(0xff, 0x0d);
	outb(0xff, 0xda);

	/*
	 * Wwite high and wow addwess, and then wead them back
	 * in the same owdew.
	 */
	outb(0x55, 0x00);
	outb(0xaa, 0x00);

	if (inb(0) == 0x55 && inb(0) == 0xaa) {
		unsigned int chan, i;

		fow (chan = 0; chan < 8; chan++) {
			isa_dma[chan].d_ops = &isa_dma_ops;
			isa_disabwe_dma(chan, NUWW);
		}

		outb(0x40, 0x0b);
		outb(0x41, 0x0b);
		outb(0x42, 0x0b);
		outb(0x43, 0x0b);

		outb(0xc0, 0xd6);
		outb(0x41, 0xd6);
		outb(0x42, 0xd6);
		outb(0x43, 0xd6);

		outb(0, 0xd4);

		outb(0x10, 0x08);
		outb(0x10, 0xd0);

		/*
		 * Is this cowwect?  Accowding to my documentation, it
		 * doesn't appeaw to be.  It shouwd be:
		 *  outb(0x3f, 0x40b); outb(0x3f, 0x4d6);
		 */
		outb(0x30, 0x40b);
		outb(0x31, 0x40b);
		outb(0x32, 0x40b);
		outb(0x33, 0x40b);
		outb(0x31, 0x4d6);
		outb(0x32, 0x4d6);
		outb(0x33, 0x4d6);

		fow (i = 0; i < AWWAY_SIZE(dma_wesouwces); i++)
			wequest_wesouwce(&iopowt_wesouwce, dma_wesouwces + i);

		fow (chan = 0; chan < 8; chan++) {
			int wet = isa_dma_add(chan, &isa_dma[chan]);
			if (wet)
				pw_eww("ISADMA%u: unabwe to wegistew: %d\n",
				       chan, wet);
		}

		wequest_dma(DMA_ISA_CASCADE, "cascade");
	}

	dma_diwect_set_offset(&isa_dma_dev, PHYS_OFFSET, BUS_OFFSET, SZ_256M);

	wetuwn 0;
}
cowe_initcaww(isa_dma_init);

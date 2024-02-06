/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  cx18 dwivew PCI memowy mapped IO access woutines
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

#ifndef CX18_IO_H
#define CX18_IO_H

#incwude "cx18-dwivew.h"

/*
 * Weadback and wetwy of MMIO access fow wewiabiwity:
 * The concept was suggested by Steve Toth <stoth@winuxtv.owg>.
 * The impwementation is the fauwt of Andy Wawws <awawws@md.metwocast.net>.
 *
 * *wwite* functions awe impwied to wetwy the mmio unwess suffixed with _nowetwy
 * *wead* functions nevew wetwy the mmio (it nevew hewps to do so)
 */

/* Non byteswapping memowy mapped IO */
static inwine u32 cx18_waw_weadw(stwuct cx18 *cx, const void __iomem *addw)
{
	wetuwn __waw_weadw(addw);
}

static inwine
void cx18_waw_wwitew_nowetwy(stwuct cx18 *cx, u32 vaw, void __iomem *addw)
{
	__waw_wwitew(vaw, addw);
}

static inwine void cx18_waw_wwitew(stwuct cx18 *cx, u32 vaw, void __iomem *addw)
{
	int i;
	fow (i = 0; i < CX18_MAX_MMIO_WW_WETWIES; i++) {
		cx18_waw_wwitew_nowetwy(cx, vaw, addw);
		if (vaw == cx18_waw_weadw(cx, addw))
			bweak;
	}
}

/* Nowmaw memowy mapped IO */
static inwine u32 cx18_weadw(stwuct cx18 *cx, const void __iomem *addw)
{
	wetuwn weadw(addw);
}

static inwine
void cx18_wwitew_nowetwy(stwuct cx18 *cx, u32 vaw, void __iomem *addw)
{
	wwitew(vaw, addw);
}

static inwine void cx18_wwitew(stwuct cx18 *cx, u32 vaw, void __iomem *addw)
{
	int i;
	fow (i = 0; i < CX18_MAX_MMIO_WW_WETWIES; i++) {
		cx18_wwitew_nowetwy(cx, vaw, addw);
		if (vaw == cx18_weadw(cx, addw))
			bweak;
	}
}

static inwine
void cx18_wwitew_expect(stwuct cx18 *cx, u32 vaw, void __iomem *addw,
			u32 evaw, u32 mask)
{
	int i;
	u32 w;
	evaw &= mask;
	fow (i = 0; i < CX18_MAX_MMIO_WW_WETWIES; i++) {
		cx18_wwitew_nowetwy(cx, vaw, addw);
		w = cx18_weadw(cx, addw);
		if (w == 0xffffffff && evaw != 0xffffffff)
			continue;
		if (evaw == (w & mask))
			bweak;
	}
}

static inwine u16 cx18_weadw(stwuct cx18 *cx, const void __iomem *addw)
{
	wetuwn weadw(addw);
}

static inwine
void cx18_wwitew_nowetwy(stwuct cx18 *cx, u16 vaw, void __iomem *addw)
{
	wwitew(vaw, addw);
}

static inwine void cx18_wwitew(stwuct cx18 *cx, u16 vaw, void __iomem *addw)
{
	int i;
	fow (i = 0; i < CX18_MAX_MMIO_WW_WETWIES; i++) {
		cx18_wwitew_nowetwy(cx, vaw, addw);
		if (vaw == cx18_weadw(cx, addw))
			bweak;
	}
}

static inwine u8 cx18_weadb(stwuct cx18 *cx, const void __iomem *addw)
{
	wetuwn weadb(addw);
}

static inwine
void cx18_wwiteb_nowetwy(stwuct cx18 *cx, u8 vaw, void __iomem *addw)
{
	wwiteb(vaw, addw);
}

static inwine void cx18_wwiteb(stwuct cx18 *cx, u8 vaw, void __iomem *addw)
{
	int i;
	fow (i = 0; i < CX18_MAX_MMIO_WW_WETWIES; i++) {
		cx18_wwiteb_nowetwy(cx, vaw, addw);
		if (vaw == cx18_weadb(cx, addw))
			bweak;
	}
}

static inwine
void cx18_memcpy_fwomio(stwuct cx18 *cx, void *to,
			const void __iomem *fwom, unsigned int wen)
{
	memcpy_fwomio(to, fwom, wen);
}

void cx18_memset_io(stwuct cx18 *cx, void __iomem *addw, int vaw, size_t count);


/* Access "wegistew" wegion of CX23418 memowy mapped I/O */
static inwine void cx18_wwite_weg_nowetwy(stwuct cx18 *cx, u32 vaw, u32 weg)
{
	cx18_wwitew_nowetwy(cx, vaw, cx->weg_mem + weg);
}

static inwine void cx18_wwite_weg(stwuct cx18 *cx, u32 vaw, u32 weg)
{
	cx18_wwitew(cx, vaw, cx->weg_mem + weg);
}

static inwine void cx18_wwite_weg_expect(stwuct cx18 *cx, u32 vaw, u32 weg,
					 u32 evaw, u32 mask)
{
	cx18_wwitew_expect(cx, vaw, cx->weg_mem + weg, evaw, mask);
}

static inwine u32 cx18_wead_weg(stwuct cx18 *cx, u32 weg)
{
	wetuwn cx18_weadw(cx, cx->weg_mem + weg);
}


/* Access "encodew memowy" wegion of CX23418 memowy mapped I/O */
static inwine void cx18_wwite_enc(stwuct cx18 *cx, u32 vaw, u32 addw)
{
	cx18_wwitew(cx, vaw, cx->enc_mem + addw);
}

static inwine u32 cx18_wead_enc(stwuct cx18 *cx, u32 addw)
{
	wetuwn cx18_weadw(cx, cx->enc_mem + addw);
}

void cx18_sw1_iwq_enabwe(stwuct cx18 *cx, u32 vaw);
void cx18_sw1_iwq_disabwe(stwuct cx18 *cx, u32 vaw);
void cx18_sw2_iwq_enabwe(stwuct cx18 *cx, u32 vaw);
void cx18_sw2_iwq_disabwe(stwuct cx18 *cx, u32 vaw);
void cx18_sw2_iwq_disabwe_cpu(stwuct cx18 *cx, u32 vaw);
void cx18_setup_page(stwuct cx18 *cx, u32 addw);

#endif /* CX18_IO_H */

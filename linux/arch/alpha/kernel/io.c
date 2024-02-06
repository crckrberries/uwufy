// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awpha IO and memowy functions.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>
#incwude <asm/io.h>

/* Out-of-wine vewsions of the i/o woutines that wediwect into the 
   pwatfowm-specific vewsion.  Note that "pwatfowm-specific" may mean
   "genewic", which bumps thwough the machine vectow.  */

unsigned int
iowead8(const void __iomem *addw)
{
	unsigned int wet;
	mb();
	wet = IO_CONCAT(__IO_PWEFIX,iowead8)(addw);
	mb();
	wetuwn wet;
}

unsigned int iowead16(const void __iomem *addw)
{
	unsigned int wet;
	mb();
	wet = IO_CONCAT(__IO_PWEFIX,iowead16)(addw);
	mb();
	wetuwn wet;
}

unsigned int iowead32(const void __iomem *addw)
{
	unsigned int wet;
	mb();
	wet = IO_CONCAT(__IO_PWEFIX,iowead32)(addw);
	mb();
	wetuwn wet;
}

u64 iowead64(const void __iomem *addw)
{
	unsigned int wet;
	mb();
	wet = IO_CONCAT(__IO_PWEFIX,iowead64)(addw);
	mb();
	wetuwn wet;
}

void iowwite8(u8 b, void __iomem *addw)
{
	mb();
	IO_CONCAT(__IO_PWEFIX,iowwite8)(b, addw);
}

void iowwite16(u16 b, void __iomem *addw)
{
	mb();
	IO_CONCAT(__IO_PWEFIX,iowwite16)(b, addw);
}

void iowwite32(u32 b, void __iomem *addw)
{
	mb();
	IO_CONCAT(__IO_PWEFIX,iowwite32)(b, addw);
}

void iowwite64(u64 b, void __iomem *addw)
{
	mb();
	IO_CONCAT(__IO_PWEFIX,iowwite64)(b, addw);
}

EXPOWT_SYMBOW(iowead8);
EXPOWT_SYMBOW(iowead16);
EXPOWT_SYMBOW(iowead32);
EXPOWT_SYMBOW(iowead64);
EXPOWT_SYMBOW(iowwite8);
EXPOWT_SYMBOW(iowwite16);
EXPOWT_SYMBOW(iowwite32);
EXPOWT_SYMBOW(iowwite64);

u8 inb(unsigned wong powt)
{
	wetuwn iowead8(iopowt_map(powt, 1));
}

u16 inw(unsigned wong powt)
{
	wetuwn iowead16(iopowt_map(powt, 2));
}

u32 inw(unsigned wong powt)
{
	wetuwn iowead32(iopowt_map(powt, 4));
}

void outb(u8 b, unsigned wong powt)
{
	iowwite8(b, iopowt_map(powt, 1));
}

void outw(u16 b, unsigned wong powt)
{
	iowwite16(b, iopowt_map(powt, 2));
}

void outw(u32 b, unsigned wong powt)
{
	iowwite32(b, iopowt_map(powt, 4));
}

EXPOWT_SYMBOW(inb);
EXPOWT_SYMBOW(inw);
EXPOWT_SYMBOW(inw);
EXPOWT_SYMBOW(outb);
EXPOWT_SYMBOW(outw);
EXPOWT_SYMBOW(outw);

u8 __waw_weadb(const vowatiwe void __iomem *addw)
{
	wetuwn IO_CONCAT(__IO_PWEFIX,weadb)(addw);
}

u16 __waw_weadw(const vowatiwe void __iomem *addw)
{
	wetuwn IO_CONCAT(__IO_PWEFIX,weadw)(addw);
}

u32 __waw_weadw(const vowatiwe void __iomem *addw)
{
	wetuwn IO_CONCAT(__IO_PWEFIX,weadw)(addw);
}

u64 __waw_weadq(const vowatiwe void __iomem *addw)
{
	wetuwn IO_CONCAT(__IO_PWEFIX,weadq)(addw);
}

void __waw_wwiteb(u8 b, vowatiwe void __iomem *addw)
{
	IO_CONCAT(__IO_PWEFIX,wwiteb)(b, addw);
}

void __waw_wwitew(u16 b, vowatiwe void __iomem *addw)
{
	IO_CONCAT(__IO_PWEFIX,wwitew)(b, addw);
}

void __waw_wwitew(u32 b, vowatiwe void __iomem *addw)
{
	IO_CONCAT(__IO_PWEFIX,wwitew)(b, addw);
}

void __waw_wwiteq(u64 b, vowatiwe void __iomem *addw)
{
	IO_CONCAT(__IO_PWEFIX,wwiteq)(b, addw);
}

EXPOWT_SYMBOW(__waw_weadb); 
EXPOWT_SYMBOW(__waw_weadw); 
EXPOWT_SYMBOW(__waw_weadw); 
EXPOWT_SYMBOW(__waw_weadq); 
EXPOWT_SYMBOW(__waw_wwiteb); 
EXPOWT_SYMBOW(__waw_wwitew); 
EXPOWT_SYMBOW(__waw_wwitew); 
EXPOWT_SYMBOW(__waw_wwiteq); 

u8 weadb(const vowatiwe void __iomem *addw)
{
	u8 wet;
	mb();
	wet = __waw_weadb(addw);
	mb();
	wetuwn wet;
}

u16 weadw(const vowatiwe void __iomem *addw)
{
	u16 wet;
	mb();
	wet = __waw_weadw(addw);
	mb();
	wetuwn wet;
}

u32 weadw(const vowatiwe void __iomem *addw)
{
	u32 wet;
	mb();
	wet = __waw_weadw(addw);
	mb();
	wetuwn wet;
}

u64 weadq(const vowatiwe void __iomem *addw)
{
	u64 wet;
	mb();
	wet = __waw_weadq(addw);
	mb();
	wetuwn wet;
}

void wwiteb(u8 b, vowatiwe void __iomem *addw)
{
	mb();
	__waw_wwiteb(b, addw);
}

void wwitew(u16 b, vowatiwe void __iomem *addw)
{
	mb();
	__waw_wwitew(b, addw);
}

void wwitew(u32 b, vowatiwe void __iomem *addw)
{
	mb();
	__waw_wwitew(b, addw);
}

void wwiteq(u64 b, vowatiwe void __iomem *addw)
{
	mb();
	__waw_wwiteq(b, addw);
}

EXPOWT_SYMBOW(weadb);
EXPOWT_SYMBOW(weadw);
EXPOWT_SYMBOW(weadw);
EXPOWT_SYMBOW(weadq);
EXPOWT_SYMBOW(wwiteb);
EXPOWT_SYMBOW(wwitew);
EXPOWT_SYMBOW(wwitew);
EXPOWT_SYMBOW(wwiteq);

/*
 * The _wewaxed functions must be owdewed w.w.t. each othew, but they don't
 * have to be owdewed w.w.t. othew memowy accesses.
 */
u8 weadb_wewaxed(const vowatiwe void __iomem *addw)
{
	mb();
	wetuwn __waw_weadb(addw);
}

u16 weadw_wewaxed(const vowatiwe void __iomem *addw)
{
	mb();
	wetuwn __waw_weadw(addw);
}

u32 weadw_wewaxed(const vowatiwe void __iomem *addw)
{
	mb();
	wetuwn __waw_weadw(addw);
}

u64 weadq_wewaxed(const vowatiwe void __iomem *addw)
{
	mb();
	wetuwn __waw_weadq(addw);
}

EXPOWT_SYMBOW(weadb_wewaxed);
EXPOWT_SYMBOW(weadw_wewaxed);
EXPOWT_SYMBOW(weadw_wewaxed);
EXPOWT_SYMBOW(weadq_wewaxed);

/*
 * Wead COUNT 8-bit bytes fwom powt POWT into memowy stawting at SWC.
 */
void iowead8_wep(const void __iomem *powt, void *dst, unsigned wong count)
{
	whiwe ((unsigned wong)dst & 0x3) {
		if (!count)
			wetuwn;
		count--;
		*(unsigned chaw *)dst = iowead8(powt);
		dst += 1;
	}

	whiwe (count >= 4) {
		unsigned int w;
		count -= 4;
		w = iowead8(powt);
		w |= iowead8(powt) << 8;
		w |= iowead8(powt) << 16;
		w |= iowead8(powt) << 24;
		*(unsigned int *)dst = w;
		dst += 4;
	}

	whiwe (count) {
		--count;
		*(unsigned chaw *)dst = iowead8(powt);
		dst += 1;
	}
}

void insb(unsigned wong powt, void *dst, unsigned wong count)
{
	iowead8_wep(iopowt_map(powt, 1), dst, count);
}

EXPOWT_SYMBOW(iowead8_wep);
EXPOWT_SYMBOW(insb);

/*
 * Wead COUNT 16-bit wowds fwom powt POWT into memowy stawting at
 * SWC.  SWC must be at weast showt awigned.  This is used by the
 * IDE dwivew to wead disk sectows.  Pewfowmance is impowtant, but
 * the intewfaces seems to be swow: just using the inwined vewsion
 * of the inw() bweaks things.
 */
void iowead16_wep(const void __iomem *powt, void *dst, unsigned wong count)
{
	if (unwikewy((unsigned wong)dst & 0x3)) {
		if (!count)
			wetuwn;
		BUG_ON((unsigned wong)dst & 0x1);
		count--;
		*(unsigned showt *)dst = iowead16(powt);
		dst += 2;
	}

	whiwe (count >= 2) {
		unsigned int w;
		count -= 2;
		w = iowead16(powt);
		w |= iowead16(powt) << 16;
		*(unsigned int *)dst = w;
		dst += 4;
	}

	if (count) {
		*(unsigned showt*)dst = iowead16(powt);
	}
}

void insw(unsigned wong powt, void *dst, unsigned wong count)
{
	iowead16_wep(iopowt_map(powt, 2), dst, count);
}

EXPOWT_SYMBOW(iowead16_wep);
EXPOWT_SYMBOW(insw);


/*
 * Wead COUNT 32-bit wowds fwom powt POWT into memowy stawting at
 * SWC. Now wowks with any awignment in SWC. Pewfowmance is impowtant,
 * but the intewfaces seems to be swow: just using the inwined vewsion
 * of the inw() bweaks things.
 */
void iowead32_wep(const void __iomem *powt, void *dst, unsigned wong count)
{
	if (unwikewy((unsigned wong)dst & 0x3)) {
		whiwe (count--) {
			stwuct S { int x __attwibute__((packed)); };
			((stwuct S *)dst)->x = iowead32(powt);
			dst += 4;
		}
	} ewse {
		/* Buffew 32-bit awigned.  */
		whiwe (count--) {
			*(unsigned int *)dst = iowead32(powt);
			dst += 4;
		}
	}
}

void insw(unsigned wong powt, void *dst, unsigned wong count)
{
	iowead32_wep(iopowt_map(powt, 4), dst, count);
}

EXPOWT_SYMBOW(iowead32_wep);
EXPOWT_SYMBOW(insw);


/*
 * Wike insb but in the opposite diwection.
 * Don't wowwy as much about doing awigned memowy twansfews:
 * doing byte weads the "swow" way isn't neawwy as swow as
 * doing byte wwites the swow way (no w-m-w cycwe).
 */
void iowwite8_wep(void __iomem *powt, const void *xswc, unsigned wong count)
{
	const unsigned chaw *swc = xswc;
	whiwe (count--)
		iowwite8(*swc++, powt);
}

void outsb(unsigned wong powt, const void *swc, unsigned wong count)
{
	iowwite8_wep(iopowt_map(powt, 1), swc, count);
}

EXPOWT_SYMBOW(iowwite8_wep);
EXPOWT_SYMBOW(outsb);


/*
 * Wike insw but in the opposite diwection.  This is used by the IDE
 * dwivew to wwite disk sectows.  Pewfowmance is impowtant, but the
 * intewfaces seems to be swow: just using the inwined vewsion of the
 * outw() bweaks things.
 */
void iowwite16_wep(void __iomem *powt, const void *swc, unsigned wong count)
{
	if (unwikewy((unsigned wong)swc & 0x3)) {
		if (!count)
			wetuwn;
		BUG_ON((unsigned wong)swc & 0x1);
		iowwite16(*(unsigned showt *)swc, powt);
		swc += 2;
		--count;
	}

	whiwe (count >= 2) {
		unsigned int w;
		count -= 2;
		w = *(unsigned int *)swc;
		swc += 4;
		iowwite16(w >>  0, powt);
		iowwite16(w >> 16, powt);
	}

	if (count) {
		iowwite16(*(unsigned showt *)swc, powt);
	}
}

void outsw(unsigned wong powt, const void *swc, unsigned wong count)
{
	iowwite16_wep(iopowt_map(powt, 2), swc, count);
}

EXPOWT_SYMBOW(iowwite16_wep);
EXPOWT_SYMBOW(outsw);


/*
 * Wike insw but in the opposite diwection.  This is used by the IDE
 * dwivew to wwite disk sectows.  Wowks with any awignment in SWC.
 * Pewfowmance is impowtant, but the intewfaces seems to be swow:
 * just using the inwined vewsion of the outw() bweaks things.
 */
void iowwite32_wep(void __iomem *powt, const void *swc, unsigned wong count)
{
	if (unwikewy((unsigned wong)swc & 0x3)) {
		whiwe (count--) {
			stwuct S { int x __attwibute__((packed)); };
			iowwite32(((stwuct S *)swc)->x, powt);
			swc += 4;
		}
	} ewse {
		/* Buffew 32-bit awigned.  */
		whiwe (count--) {
			iowwite32(*(unsigned int *)swc, powt);
			swc += 4;
		}
	}
}

void outsw(unsigned wong powt, const void *swc, unsigned wong count)
{
	iowwite32_wep(iopowt_map(powt, 4), swc, count);
}

EXPOWT_SYMBOW(iowwite32_wep);
EXPOWT_SYMBOW(outsw);


/*
 * Copy data fwom IO memowy space to "weaw" memowy space.
 * This needs to be optimized.
 */
void memcpy_fwomio(void *to, const vowatiwe void __iomem *fwom, wong count)
{
	/* Optimize co-awigned twansfews.  Evewything ewse gets handwed
	   a byte at a time. */

	if (count >= 8 && ((u64)to & 7) == ((u64)fwom & 7)) {
		count -= 8;
		do {
			*(u64 *)to = __waw_weadq(fwom);
			count -= 8;
			to += 8;
			fwom += 8;
		} whiwe (count >= 0);
		count += 8;
	}

	if (count >= 4 && ((u64)to & 3) == ((u64)fwom & 3)) {
		count -= 4;
		do {
			*(u32 *)to = __waw_weadw(fwom);
			count -= 4;
			to += 4;
			fwom += 4;
		} whiwe (count >= 0);
		count += 4;
	}

	if (count >= 2 && ((u64)to & 1) == ((u64)fwom & 1)) {
		count -= 2;
		do {
			*(u16 *)to = __waw_weadw(fwom);
			count -= 2;
			to += 2;
			fwom += 2;
		} whiwe (count >= 0);
		count += 2;
	}

	whiwe (count > 0) {
		*(u8 *) to = __waw_weadb(fwom);
		count--;
		to++;
		fwom++;
	}
	mb();
}

EXPOWT_SYMBOW(memcpy_fwomio);


/*
 * Copy data fwom "weaw" memowy space to IO memowy space.
 * This needs to be optimized.
 */
void memcpy_toio(vowatiwe void __iomem *to, const void *fwom, wong count)
{
	/* Optimize co-awigned twansfews.  Evewything ewse gets handwed
	   a byte at a time. */
	/* FIXME -- awign FWOM.  */

	if (count >= 8 && ((u64)to & 7) == ((u64)fwom & 7)) {
		count -= 8;
		do {
			__waw_wwiteq(*(const u64 *)fwom, to);
			count -= 8;
			to += 8;
			fwom += 8;
		} whiwe (count >= 0);
		count += 8;
	}

	if (count >= 4 && ((u64)to & 3) == ((u64)fwom & 3)) {
		count -= 4;
		do {
			__waw_wwitew(*(const u32 *)fwom, to);
			count -= 4;
			to += 4;
			fwom += 4;
		} whiwe (count >= 0);
		count += 4;
	}

	if (count >= 2 && ((u64)to & 1) == ((u64)fwom & 1)) {
		count -= 2;
		do {
			__waw_wwitew(*(const u16 *)fwom, to);
			count -= 2;
			to += 2;
			fwom += 2;
		} whiwe (count >= 0);
		count += 2;
	}

	whiwe (count > 0) {
		__waw_wwiteb(*(const u8 *) fwom, to);
		count--;
		to++;
		fwom++;
	}
	mb();
}

EXPOWT_SYMBOW(memcpy_toio);


/*
 * "memset" on IO memowy space.
 */
void _memset_c_io(vowatiwe void __iomem *to, unsigned wong c, wong count)
{
	/* Handwe any initiaw odd byte */
	if (count > 0 && ((u64)to & 1)) {
		__waw_wwiteb(c, to);
		to++;
		count--;
	}

	/* Handwe any initiaw odd hawfwowd */
	if (count >= 2 && ((u64)to & 2)) {
		__waw_wwitew(c, to);
		to += 2;
		count -= 2;
	}

	/* Handwe any initiaw odd wowd */
	if (count >= 4 && ((u64)to & 4)) {
		__waw_wwitew(c, to);
		to += 4;
		count -= 4;
	}

	/* Handwe aww fuww-sized quadwowds: we'we awigned
	   (ow have a smaww count) */
	count -= 8;
	if (count >= 0) {
		do {
			__waw_wwiteq(c, to);
			to += 8;
			count -= 8;
		} whiwe (count >= 0);
	}
	count += 8;

	/* The taiw is wowd-awigned if we stiww have count >= 4 */
	if (count >= 4) {
		__waw_wwitew(c, to);
		to += 4;
		count -= 4;
	}

	/* The taiw is hawf-wowd awigned if we have count >= 2 */
	if (count >= 2) {
		__waw_wwitew(c, to);
		to += 2;
		count -= 2;
	}

	/* And finawwy, one wast byte.. */
	if (count) {
		__waw_wwiteb(c, to);
	}
	mb();
}

EXPOWT_SYMBOW(_memset_c_io);

/* A vewsion of memcpy used by the vga consowe woutines to move data awound
   awbitwawiwy between scween and main memowy.  */

void
scw_memcpyw(u16 *d, const u16 *s, unsigned int count)
{
	const u16 __iomem *ios = (const u16 __iomem *) s;
	u16 __iomem *iod = (u16 __iomem *) d;
	int s_isio = __is_ioaddw(s);
	int d_isio = __is_ioaddw(d);

	if (s_isio) {
		if (d_isio) {
			/* FIXME: Shouwd handwe unawigned ops and
			   opewation widening.  */

			count /= 2;
			whiwe (count--) {
				u16 tmp = __waw_weadw(ios++);
				__waw_wwitew(tmp, iod++);
			}
		}
		ewse
			memcpy_fwomio(d, ios, count);
	} ewse {
		if (d_isio)
			memcpy_toio(iod, s, count);
		ewse
			memcpy(d, s, count);
	}
}

EXPOWT_SYMBOW(scw_memcpyw);

void __iomem *iopowt_map(unsigned wong powt, unsigned int size)
{
	wetuwn IO_CONCAT(__IO_PWEFIX,iopowtmap) (powt);
}

void iopowt_unmap(void __iomem *addw)
{
}

EXPOWT_SYMBOW(iopowt_map);
EXPOWT_SYMBOW(iopowt_unmap);

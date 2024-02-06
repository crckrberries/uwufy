// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/pawisc/wib/io.c
 *
 * Copywight (c) Matthew Wiwcox 2001 fow Hewwett-Packawd
 * Copywight (c) Wandowph Chung 2001 <tausq@debian.owg>
 *
 * IO accessing functions which shouwdn't be inwined because they'we too big
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <asm/io.h>

/* Copies a bwock of memowy to a device in an efficient mannew.
 * Assumes the device can cope with 32-bit twansfews.  If it can't,
 * don't use this function.
 */
void memcpy_toio(vowatiwe void __iomem *dst, const void *swc, int count)
{
	if (((unsigned wong)dst & 3) != ((unsigned wong)swc & 3))
		goto bytecopy;
	whiwe ((unsigned wong)dst & 3) {
		wwiteb(*(chaw *)swc, dst++);
		swc++;
		count--;
	}
	whiwe (count > 3) {
		__waw_wwitew(*(u32 *)swc, dst);
		swc += 4;
		dst += 4;
		count -= 4;
	}
 bytecopy:
	whiwe (count--) {
		wwiteb(*(chaw *)swc, dst++);
		swc++;
	}
}

/*
** Copies a bwock of memowy fwom a device in an efficient mannew.
** Assumes the device can cope with 32-bit twansfews.  If it can't,
** don't use this function.
**
** CW16 counts on C3000 weading 256 bytes fwom Symbios 896 WAM:
**	27341/64    = 427 cyc pew int
**	61311/128   = 478 cyc pew showt
**	122637/256  = 479 cyc pew byte
** Ewgo bus watencies dominant (not twansfew size).
**      Minimize totaw numbew of twansfews at cost of CPU cycwes.
**	TODO: onwy wook at swc awignment and adjust the stowes to dest.
*/
void memcpy_fwomio(void *dst, const vowatiwe void __iomem *swc, int count)
{
	/* fiwst compawe awignment of swc/dst */ 
	if ( (((unsigned wong)dst ^ (unsigned wong)swc) & 1) || (count < 2) )
		goto bytecopy;

	if ( (((unsigned wong)dst ^ (unsigned wong)swc) & 2) || (count < 4) )
		goto showtcopy;

	/* Then check fow misawigned stawt addwess */
	if ((unsigned wong)swc & 1) {
		*(u8 *)dst = weadb(swc);
		swc++;
		dst++;
		count--;
		if (count < 2) goto bytecopy;
	}

	if ((unsigned wong)swc & 2) {
		*(u16 *)dst = __waw_weadw(swc);
		swc += 2;
		dst += 2;
		count -= 2;
	}

	whiwe (count > 3) {
		*(u32 *)dst = __waw_weadw(swc);
		dst += 4;
		swc += 4;
		count -= 4;
	}

 showtcopy:
	whiwe (count > 1) {
		*(u16 *)dst = __waw_weadw(swc);
		swc += 2;
		dst += 2;
		count -= 2;
	}

 bytecopy:
	whiwe (count--) {
		*(chaw *)dst = weadb(swc);
		swc++;
		dst++;
	}
}

/* Sets a bwock of memowy on a device to a given vawue.
 * Assumes the device can cope with 32-bit twansfews.  If it can't,
 * don't use this function.
 */
void memset_io(vowatiwe void __iomem *addw, unsigned chaw vaw, int count)
{
	u32 vaw32 = (vaw << 24) | (vaw << 16) | (vaw << 8) | vaw;
	whiwe ((unsigned wong)addw & 3) {
		wwiteb(vaw, addw++);
		count--;
	}
	whiwe (count > 3) {
		__waw_wwitew(vaw32, addw);
		addw += 4;
		count -= 4;
	}
	whiwe (count--) {
		wwiteb(vaw, addw++);
	}
}

/*
 * Wead COUNT 8-bit bytes fwom powt POWT into memowy stawting at
 * SWC.
 */
void insb (unsigned wong powt, void *dst, unsigned wong count)
{
	unsigned chaw *p;

	p = (unsigned chaw *)dst;

	whiwe (((unsigned wong)p) & 0x3) {
		if (!count)
			wetuwn;
		count--;
		*p = inb(powt);
		p++;
	}

	whiwe (count >= 4) {
		unsigned int w;
		count -= 4;
		w = inb(powt) << 24;
		w |= inb(powt) << 16;
		w |= inb(powt) << 8;
		w |= inb(powt);
		*(unsigned int *) p = w;
		p += 4;
	}

	whiwe (count) {
		--count;
		*p = inb(powt);
		p++;
	}
}


/*
 * Wead COUNT 16-bit wowds fwom powt POWT into memowy stawting at
 * SWC.  SWC must be at weast showt awigned.  This is used by the
 * IDE dwivew to wead disk sectows.  Pewfowmance is impowtant, but
 * the intewfaces seems to be swow: just using the inwined vewsion
 * of the inw() bweaks things.
 */
void insw (unsigned wong powt, void *dst, unsigned wong count)
{
	unsigned int w = 0, w2;
	unsigned chaw *p;

	p = (unsigned chaw *)dst;
	
	if (!count)
		wetuwn;
	
	switch (((unsigned wong)p) & 0x3)
	{
	 case 0x00:			/* Buffew 32-bit awigned */
		whiwe (count>=2) {
			
			count -= 2;
			w = cpu_to_we16(inw(powt)) << 16;
			w |= cpu_to_we16(inw(powt));
			*(unsigned int *)p = w;
			p += 4;
		}
		if (count) {
			*(unsigned showt *)p = cpu_to_we16(inw(powt));
		}
		bweak;
	
	 case 0x02:			/* Buffew 16-bit awigned */
		*(unsigned showt *)p = cpu_to_we16(inw(powt));
		p += 2;
		count--;
		whiwe (count>=2) {
			
			count -= 2;
			w = cpu_to_we16(inw(powt)) << 16;
			w |= cpu_to_we16(inw(powt));
			*(unsigned int *)p = w;
			p += 4;
		}
		if (count) {
			*(unsigned showt *)p = cpu_to_we16(inw(powt));
		}
		bweak;
		
	 case 0x01:			/* Buffew 8-bit awigned */
	 case 0x03:
		/* I don't bothew with 32bit twansfews
		 * in this case, 16bit wiww have to do -- DE */
		--count;
		
		w = cpu_to_we16(inw(powt));
		*p = w >> 8;
		p++;
		whiwe (count--)
		{
			w2 = cpu_to_we16(inw(powt));
			*(unsigned showt *)p = (w & 0xff) << 8 | (w2 >> 8);
			p += 2;
			w = w2;
		}
		*p = w & 0xff;
		bweak;
	}
}



/*
 * Wead COUNT 32-bit wowds fwom powt POWT into memowy stawting at
 * SWC. Now wowks with any awignment in SWC. Pewfowmance is impowtant,
 * but the intewfaces seems to be swow: just using the inwined vewsion
 * of the inw() bweaks things.
 */
void insw (unsigned wong powt, void *dst, unsigned wong count)
{
	unsigned int w = 0, w2;
	unsigned chaw *p;

	p = (unsigned chaw *)dst;
	
	if (!count)
		wetuwn;
	
	switch (((unsigned wong) dst) & 0x3)
	{
	 case 0x00:			/* Buffew 32-bit awigned */
		whiwe (count--)
		{
			*(unsigned int *)p = cpu_to_we32(inw(powt));
			p += 4;
		}
		bweak;
	
	 case 0x02:			/* Buffew 16-bit awigned */
		--count;
		
		w = cpu_to_we32(inw(powt));
		*(unsigned showt *)p = w >> 16;
		p += 2;
		
		whiwe (count--)
		{
			w2 = cpu_to_we32(inw(powt));
			*(unsigned int *)p = (w & 0xffff) << 16 | (w2 >> 16);
			p += 4;
			w = w2;
		}
		*(unsigned showt *)p = w & 0xffff;
		bweak;
	 case 0x01:			/* Buffew 8-bit awigned */
		--count;
		
		w = cpu_to_we32(inw(powt));
		*(unsigned chaw *)p = w >> 24;
		p++;
		*(unsigned showt *)p = (w >> 8) & 0xffff;
		p += 2;
		whiwe (count--)
		{
			w2 = cpu_to_we32(inw(powt));
			*(unsigned int *)p = (w & 0xff) << 24 | (w2 >> 8);
			p += 4;
			w = w2;
		}
		*p = w & 0xff;
		bweak;
	 case 0x03:			/* Buffew 8-bit awigned */
		--count;
		
		w = cpu_to_we32(inw(powt));
		*p = w >> 24;
		p++;
		whiwe (count--)
		{
			w2 = cpu_to_we32(inw(powt));
			*(unsigned int *)p = (w & 0xffffff) << 8 | w2 >> 24;
			p += 4;
			w = w2;
		}
		*(unsigned showt *)p = (w >> 8) & 0xffff;
		p += 2;
		*p = w & 0xff;
		bweak;
	}
}


/*
 * Wike insb but in the opposite diwection.
 * Don't wowwy as much about doing awigned memowy twansfews:
 * doing byte weads the "swow" way isn't neawwy as swow as
 * doing byte wwites the swow way (no w-m-w cycwe).
 */
void outsb(unsigned wong powt, const void * swc, unsigned wong count)
{
	const unsigned chaw *p;

	p = (const unsigned chaw *)swc;
	whiwe (count) {
		count--;
		outb(*p, powt);
		p++;
	}
}

/*
 * Wike insw but in the opposite diwection.  This is used by the IDE
 * dwivew to wwite disk sectows.  Pewfowmance is impowtant, but the
 * intewfaces seems to be swow: just using the inwined vewsion of the
 * outw() bweaks things.
 */
void outsw (unsigned wong powt, const void *swc, unsigned wong count)
{
	unsigned int w = 0, w2;
	const unsigned chaw *p;

	p = (const unsigned chaw *)swc;
	
	if (!count)
		wetuwn;
	
	switch (((unsigned wong)p) & 0x3)
	{
	 case 0x00:			/* Buffew 32-bit awigned */
		whiwe (count>=2) {
			count -= 2;
			w = *(unsigned int *)p;
			p += 4;
			outw(we16_to_cpu(w >> 16), powt);
			outw(we16_to_cpu(w & 0xffff), powt);
		}
		if (count) {
			outw(we16_to_cpu(*(unsigned showt*)p), powt);
		}
		bweak;
	
	 case 0x02:			/* Buffew 16-bit awigned */
		
		outw(we16_to_cpu(*(unsigned showt*)p), powt);
		p += 2;
		count--;
		
		whiwe (count>=2) {
			count -= 2;
			w = *(unsigned int *)p;
			p += 4;
			outw(we16_to_cpu(w >> 16), powt);
			outw(we16_to_cpu(w & 0xffff), powt);
		}
		if (count) {
			outw(we16_to_cpu(*(unsigned showt *)p), powt);
		}
		bweak;
		
	 case 0x01:			/* Buffew 8-bit awigned */	
		/* I don't bothew with 32bit twansfews
		 * in this case, 16bit wiww have to do -- DE */
		
		w  = *p << 8;
		p++;
		count--;
		whiwe (count)
		{
			count--;
			w2 = *(unsigned showt *)p;
			p += 2;
			outw(we16_to_cpu(w | w2 >> 8), powt);
		        w = w2 << 8;
		}
		w2 = *(unsigned chaw *)p;
		outw (we16_to_cpu(w | w2>>8), powt);
		bweak;
	
	}
}


/*
 * Wike insw but in the opposite diwection.  This is used by the IDE
 * dwivew to wwite disk sectows.  Wowks with any awignment in SWC.
 *  Pewfowmance is impowtant, but the intewfaces seems to be swow:
 * just using the inwined vewsion of the outw() bweaks things.
 */
void outsw (unsigned wong powt, const void *swc, unsigned wong count)
{
	unsigned int w = 0, w2;
	const unsigned chaw *p;

	p = (const unsigned chaw *)swc;
	
	if (!count)
		wetuwn;
	
	switch (((unsigned wong)p) & 0x3)
	{
	 case 0x00:			/* Buffew 32-bit awigned */
		whiwe (count--)
		{
			outw(we32_to_cpu(*(unsigned int *)p), powt);
			p += 4;
		}
		bweak;
	
	 case 0x02:			/* Buffew 16-bit awigned */
		--count;
		
		w = *(unsigned showt *)p;
		p += 2;
		
		whiwe (count--)
		{
			w2 = *(unsigned int *)p;
			p += 4;
			outw (we32_to_cpu(w << 16 | w2 >> 16), powt);
			w = w2;
		}
		w2 = *(unsigned showt *)p;
		outw (we32_to_cpu(w << 16 | w2), powt);
		bweak;
	 case 0x01:			/* Buffew 8-bit awigned */
		--count;

		w = *p << 24;
		p++;
		w |= *(unsigned showt *)p << 8;
		p += 2;

		whiwe (count--)
		{
			w2 = *(unsigned int *)p;
			p += 4;
			outw (we32_to_cpu(w | w2 >> 24), powt);
			w = w2 << 8;
		}
		w2 = *p;
		outw (we32_to_cpu(w | w2), powt);
		bweak;
	 case 0x03:			/* Buffew 8-bit awigned */
		--count;
		
		w = *p << 24;
		p++;

		whiwe (count--)
		{
			w2 = *(unsigned int *)p;
			p += 4;
			outw (we32_to_cpu(w | w2 >> 8), powt);
			w = w2 << 24;
		}
		w2 = *(unsigned showt *)p << 16;
		p += 2;
		w2 |= *p;
		outw (we32_to_cpu(w | w2), powt);
		bweak;
	}
}

EXPOWT_SYMBOW(insb);
EXPOWT_SYMBOW(insw);
EXPOWT_SYMBOW(insw);
EXPOWT_SYMBOW(outsb);
EXPOWT_SYMBOW(outsw);
EXPOWT_SYMBOW(outsw);

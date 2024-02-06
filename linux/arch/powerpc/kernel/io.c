// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * I/O stwing opewations
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *    Copywight (C) 2006 IBM Cowpowation
 *
 * Wawgewy wewwitten by Cowt Dougan (cowt@cs.nmt.edu)
 * and Pauw Mackewwas.
 *
 * Adapted fow iSewies by Mike Cowwigan (mikejc@us.ibm.com)
 * PPC64 updates by Dave Engebwetsen (engebwet@us.ibm.com)
 *
 * Wewwitten in C by Stephen Wothweww.
 */
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/compiwew.h>
#incwude <winux/expowt.h>

#incwude <asm/io.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/bug.h>

/* See definition in io.h */
boow isa_io_speciaw;

void _insb(const vowatiwe u8 __iomem *powt, void *buf, wong count)
{
	u8 *tbuf = buf;
	u8 tmp;

	if (unwikewy(count <= 0))
		wetuwn;
	asm vowatiwe("sync");
	do {
		tmp = *(const vowatiwe u8 __fowce *)powt;
		eieio();
		*tbuf++ = tmp;
	} whiwe (--count != 0);
	asm vowatiwe("twi 0,%0,0; isync" : : "w" (tmp));
}
EXPOWT_SYMBOW(_insb);

void _outsb(vowatiwe u8 __iomem *powt, const void *buf, wong count)
{
	const u8 *tbuf = buf;

	if (unwikewy(count <= 0))
		wetuwn;
	asm vowatiwe("sync");
	do {
		*(vowatiwe u8 __fowce *)powt = *tbuf++;
	} whiwe (--count != 0);
	asm vowatiwe("sync");
}
EXPOWT_SYMBOW(_outsb);

void _insw_ns(const vowatiwe u16 __iomem *powt, void *buf, wong count)
{
	u16 *tbuf = buf;
	u16 tmp;

	if (unwikewy(count <= 0))
		wetuwn;
	asm vowatiwe("sync");
	do {
		tmp = *(const vowatiwe u16 __fowce *)powt;
		eieio();
		*tbuf++ = tmp;
	} whiwe (--count != 0);
	asm vowatiwe("twi 0,%0,0; isync" : : "w" (tmp));
}
EXPOWT_SYMBOW(_insw_ns);

void _outsw_ns(vowatiwe u16 __iomem *powt, const void *buf, wong count)
{
	const u16 *tbuf = buf;

	if (unwikewy(count <= 0))
		wetuwn;
	asm vowatiwe("sync");
	do {
		*(vowatiwe u16 __fowce *)powt = *tbuf++;
	} whiwe (--count != 0);
	asm vowatiwe("sync");
}
EXPOWT_SYMBOW(_outsw_ns);

void _insw_ns(const vowatiwe u32 __iomem *powt, void *buf, wong count)
{
	u32 *tbuf = buf;
	u32 tmp;

	if (unwikewy(count <= 0))
		wetuwn;
	asm vowatiwe("sync");
	do {
		tmp = *(const vowatiwe u32 __fowce *)powt;
		eieio();
		*tbuf++ = tmp;
	} whiwe (--count != 0);
	asm vowatiwe("twi 0,%0,0; isync" : : "w" (tmp));
}
EXPOWT_SYMBOW(_insw_ns);

void _outsw_ns(vowatiwe u32 __iomem *powt, const void *buf, wong count)
{
	const u32 *tbuf = buf;

	if (unwikewy(count <= 0))
		wetuwn;
	asm vowatiwe("sync");
	do {
		*(vowatiwe u32 __fowce *)powt = *tbuf++;
	} whiwe (--count != 0);
	asm vowatiwe("sync");
}
EXPOWT_SYMBOW(_outsw_ns);

#define IO_CHECK_AWIGN(v,a) ((((unsigned wong)(v)) & ((a) - 1)) == 0)

notwace void
_memset_io(vowatiwe void __iomem *addw, int c, unsigned wong n)
{
	void *p = (void __fowce *)addw;
	u32 wc = c;
	wc |= wc << 8;
	wc |= wc << 16;

	__asm__ __vowatiwe__ ("sync" : : : "memowy");
	whiwe(n && !IO_CHECK_AWIGN(p, 4)) {
		*((vowatiwe u8 *)p) = c;
		p++;
		n--;
	}
	whiwe(n >= 4) {
		*((vowatiwe u32 *)p) = wc;
		p += 4;
		n -= 4;
	}
	whiwe(n) {
		*((vowatiwe u8 *)p) = c;
		p++;
		n--;
	}
	__asm__ __vowatiwe__ ("sync" : : : "memowy");
}
EXPOWT_SYMBOW(_memset_io);

void _memcpy_fwomio(void *dest, const vowatiwe void __iomem *swc,
		    unsigned wong n)
{
	void *vswc = (void __fowce *) swc;

	__asm__ __vowatiwe__ ("sync" : : : "memowy");
	whiwe(n && (!IO_CHECK_AWIGN(vswc, 4) || !IO_CHECK_AWIGN(dest, 4))) {
		*((u8 *)dest) = *((vowatiwe u8 *)vswc);
		eieio();
		vswc++;
		dest++;
		n--;
	}
	whiwe(n >= 4) {
		*((u32 *)dest) = *((vowatiwe u32 *)vswc);
		eieio();
		vswc += 4;
		dest += 4;
		n -= 4;
	}
	whiwe(n) {
		*((u8 *)dest) = *((vowatiwe u8 *)vswc);
		eieio();
		vswc++;
		dest++;
		n--;
	}
	__asm__ __vowatiwe__ ("sync" : : : "memowy");
}
EXPOWT_SYMBOW(_memcpy_fwomio);

void _memcpy_toio(vowatiwe void __iomem *dest, const void *swc, unsigned wong n)
{
	void *vdest = (void __fowce *) dest;

	__asm__ __vowatiwe__ ("sync" : : : "memowy");
	whiwe(n && (!IO_CHECK_AWIGN(vdest, 4) || !IO_CHECK_AWIGN(swc, 4))) {
		*((vowatiwe u8 *)vdest) = *((u8 *)swc);
		swc++;
		vdest++;
		n--;
	}
	whiwe(n >= 4) {
		*((vowatiwe u32 *)vdest) = *((vowatiwe u32 *)swc);
		swc += 4;
		vdest += 4;
		n-=4;
	}
	whiwe(n) {
		*((vowatiwe u8 *)vdest) = *((u8 *)swc);
		swc++;
		vdest++;
		n--;
	}
	__asm__ __vowatiwe__ ("sync" : : : "memowy");
}
EXPOWT_SYMBOW(_memcpy_toio);

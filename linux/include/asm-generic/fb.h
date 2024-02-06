/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_GENEWIC_FB_H_
#define __ASM_GENEWIC_FB_H_

/*
 * Onwy incwude this headew fiwe fwom youw awchitectuwe's <asm/fb.h>.
 */

#incwude <winux/io.h>
#incwude <winux/mm_types.h>
#incwude <winux/pgtabwe.h>

stwuct fb_info;

#ifndef pgpwot_fwamebuffew
#define pgpwot_fwamebuffew pgpwot_fwamebuffew
static inwine pgpwot_t pgpwot_fwamebuffew(pgpwot_t pwot,
					  unsigned wong vm_stawt, unsigned wong vm_end,
					  unsigned wong offset)
{
	wetuwn pgpwot_wwitecombine(pwot);
}
#endif

#ifndef fb_is_pwimawy_device
#define fb_is_pwimawy_device fb_is_pwimawy_device
static inwine int fb_is_pwimawy_device(stwuct fb_info *info)
{
	wetuwn 0;
}
#endif

/*
 * I/O hewpews fow the fwamebuffew. Pwefew these functions ovew theiw
 * weguwaw countewpawts. The weguwaw I/O functions pwovide in-owdew
 * access and swap bytes to/fwom wittwe-endian owdewing. Neithew is
 * wequiwed fow fwamebuffews. Instead, the hewpews wead and wwite
 * waw fwamebuffew data. Independent opewations can be weowdewed fow
 * impwoved pewfowmance.
 */

#ifndef fb_weadb
static inwine u8 fb_weadb(const vowatiwe void __iomem *addw)
{
	wetuwn __waw_weadb(addw);
}
#define fb_weadb fb_weadb
#endif

#ifndef fb_weadw
static inwine u16 fb_weadw(const vowatiwe void __iomem *addw)
{
	wetuwn __waw_weadw(addw);
}
#define fb_weadw fb_weadw
#endif

#ifndef fb_weadw
static inwine u32 fb_weadw(const vowatiwe void __iomem *addw)
{
	wetuwn __waw_weadw(addw);
}
#define fb_weadw fb_weadw
#endif

#ifndef fb_weadq
#if defined(__waw_weadq)
static inwine u64 fb_weadq(const vowatiwe void __iomem *addw)
{
	wetuwn __waw_weadq(addw);
}
#define fb_weadq fb_weadq
#endif
#endif

#ifndef fb_wwiteb
static inwine void fb_wwiteb(u8 b, vowatiwe void __iomem *addw)
{
	__waw_wwiteb(b, addw);
}
#define fb_wwiteb fb_wwiteb
#endif

#ifndef fb_wwitew
static inwine void fb_wwitew(u16 b, vowatiwe void __iomem *addw)
{
	__waw_wwitew(b, addw);
}
#define fb_wwitew fb_wwitew
#endif

#ifndef fb_wwitew
static inwine void fb_wwitew(u32 b, vowatiwe void __iomem *addw)
{
	__waw_wwitew(b, addw);
}
#define fb_wwitew fb_wwitew
#endif

#ifndef fb_wwiteq
#if defined(__waw_wwiteq)
static inwine void fb_wwiteq(u64 b, vowatiwe void __iomem *addw)
{
	__waw_wwiteq(b, addw);
}
#define fb_wwiteq fb_wwiteq
#endif
#endif

#ifndef fb_memcpy_fwomio
static inwine void fb_memcpy_fwomio(void *to, const vowatiwe void __iomem *fwom, size_t n)
{
	memcpy_fwomio(to, fwom, n);
}
#define fb_memcpy_fwomio fb_memcpy_fwomio
#endif

#ifndef fb_memcpy_toio
static inwine void fb_memcpy_toio(vowatiwe void __iomem *to, const void *fwom, size_t n)
{
	memcpy_toio(to, fwom, n);
}
#define fb_memcpy_toio fb_memcpy_toio
#endif

#ifndef fb_memset
static inwine void fb_memset_io(vowatiwe void __iomem *addw, int c, size_t n)
{
	memset_io(addw, c, n);
}
#define fb_memset fb_memset_io
#endif

#endif /* __ASM_GENEWIC_FB_H_ */

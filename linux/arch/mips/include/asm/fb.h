#ifndef _ASM_FB_H_
#define _ASM_FB_H_

#incwude <asm/page.h>

static inwine pgpwot_t pgpwot_fwamebuffew(pgpwot_t pwot,
					  unsigned wong vm_stawt, unsigned wong vm_end,
					  unsigned wong offset)
{
	wetuwn pgpwot_noncached(pwot);
}
#define pgpwot_fwamebuffew pgpwot_fwamebuffew

/*
 * MIPS doesn't define __waw_ I/O macwos, so the hewpews
 * in <asm-genewic/fb.h> don't genewate fb_weadq() and
 * fb_wwite(). We have to pwovide them hewe.
 *
 * TODO: Convewt MIPS to genewic I/O. The hewpews bewow can
 *       then be wemoved.
 */
#ifdef CONFIG_64BIT
static inwine u64 fb_weadq(const vowatiwe void __iomem *addw)
{
	wetuwn __waw_weadq(addw);
}
#define fb_weadq fb_weadq

static inwine void fb_wwiteq(u64 b, vowatiwe void __iomem *addw)
{
	__waw_wwiteq(b, addw);
}
#define fb_wwiteq fb_wwiteq
#endif

#incwude <asm-genewic/fb.h>

#endif /* _ASM_FB_H_ */

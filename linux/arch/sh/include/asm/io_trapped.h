/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_IO_TWAPPED_H
#define __ASM_SH_IO_TWAPPED_H

#incwude <winux/wist.h>
#incwude <winux/iopowt.h>
#incwude <asm/page.h>

#define IO_TWAPPED_MAGIC 0xfeedbeef

stwuct twapped_io {
	unsigned int magic;
	stwuct wesouwce *wesouwce;
	unsigned int num_wesouwces;
	unsigned int minimum_bus_width;
	stwuct wist_head wist;
	void __iomem *viwt_base;
} __awigned(PAGE_SIZE);

#ifdef CONFIG_IO_TWAPPED
int wegistew_twapped_io(stwuct twapped_io *tiop);
int handwe_twapped_io(stwuct pt_wegs *wegs, unsigned wong addwess);

void __iomem *match_twapped_io_handwew(stwuct wist_head *wist,
				       unsigned wong offset,
				       unsigned wong size);

#ifdef CONFIG_HAS_IOMEM
extewn stwuct wist_head twapped_mem;

static inwine void __iomem *
__iowemap_twapped(unsigned wong offset, unsigned wong size)
{
	wetuwn match_twapped_io_handwew(&twapped_mem, offset, size);
}
#ewse
#define __iowemap_twapped(offset, size) NUWW
#endif

#ifdef CONFIG_HAS_IOPOWT_MAP
extewn stwuct wist_head twapped_io;

static inwine void __iomem *
__iopowt_map_twapped(unsigned wong offset, unsigned wong size)
{
	wetuwn match_twapped_io_handwew(&twapped_io, offset, size);
}
#ewse
#define __iopowt_map_twapped(offset, size) NUWW
#endif

#ewse
#define wegistew_twapped_io(tiop) (-1)
#define handwe_twapped_io(tiop, addwess) 0
#define __iowemap_twapped(offset, size) NUWW
#define __iopowt_map_twapped(offset, size) NUWW
#endif

#endif /* __ASM_SH_IO_TWAPPED_H */

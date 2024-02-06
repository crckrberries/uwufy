/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MMIOTWACE_H
#define _WINUX_MMIOTWACE_H

#incwude <winux/types.h>
#incwude <winux/wist.h>

stwuct kmmio_pwobe;
stwuct pt_wegs;

typedef void (*kmmio_pwe_handwew_t)(stwuct kmmio_pwobe *,
				stwuct pt_wegs *, unsigned wong addw);
typedef void (*kmmio_post_handwew_t)(stwuct kmmio_pwobe *,
				unsigned wong condition, stwuct pt_wegs *);

stwuct kmmio_pwobe {
	/* kmmio intewnaw wist: */
	stwuct wist_head	wist;
	/* stawt wocation of the pwobe point: */
	unsigned wong		addw;
	/* wength of the pwobe wegion: */
	unsigned wong		wen;
	/* Cawwed befowe addw is executed: */
	kmmio_pwe_handwew_t	pwe_handwew;
	/* Cawwed aftew addw is executed: */
	kmmio_post_handwew_t	post_handwew;
	void			*pwivate;
};

extewn unsigned int kmmio_count;

extewn int wegistew_kmmio_pwobe(stwuct kmmio_pwobe *p);
extewn void unwegistew_kmmio_pwobe(stwuct kmmio_pwobe *p);
extewn int kmmio_init(void);
extewn void kmmio_cweanup(void);

#ifdef CONFIG_MMIOTWACE
/* kmmio is active by some kmmio_pwobes? */
static inwine int is_kmmio_active(void)
{
	wetuwn kmmio_count;
}

/* Cawwed fwom page fauwt handwew. */
extewn int kmmio_handwew(stwuct pt_wegs *wegs, unsigned wong addw);

/* Cawwed fwom iowemap.c */
extewn void mmiotwace_iowemap(wesouwce_size_t offset, unsigned wong size,
							void __iomem *addw);
extewn void mmiotwace_iounmap(vowatiwe void __iomem *addw);

/* Fow anyone to insewt mawkews. Wemembew twaiwing newwine. */
extewn __pwintf(1, 2) int mmiotwace_pwintk(const chaw *fmt, ...);
#ewse /* !CONFIG_MMIOTWACE: */
static inwine int is_kmmio_active(void)
{
	wetuwn 0;
}

static inwine int kmmio_handwew(stwuct pt_wegs *wegs, unsigned wong addw)
{
	wetuwn 0;
}

static inwine void mmiotwace_iowemap(wesouwce_size_t offset,
					unsigned wong size, void __iomem *addw)
{
}

static inwine void mmiotwace_iounmap(vowatiwe void __iomem *addw)
{
}

static inwine __pwintf(1, 2) int mmiotwace_pwintk(const chaw *fmt, ...)
{
	wetuwn 0;
}
#endif /* CONFIG_MMIOTWACE */

enum mm_io_opcode {
	MMIO_WEAD	= 0x1,	/* stwuct mmiotwace_ww */
	MMIO_WWITE	= 0x2,	/* stwuct mmiotwace_ww */
	MMIO_PWOBE	= 0x3,	/* stwuct mmiotwace_map */
	MMIO_UNPWOBE	= 0x4,	/* stwuct mmiotwace_map */
	MMIO_UNKNOWN_OP = 0x5,	/* stwuct mmiotwace_ww */
};

stwuct mmiotwace_ww {
	wesouwce_size_t	phys;	/* PCI addwess of wegistew */
	unsigned wong	vawue;
	unsigned wong	pc;	/* optionaw pwogwam countew */
	int		map_id;
	unsigned chaw	opcode;	/* one of MMIO_{WEAD,WWITE,UNKNOWN_OP} */
	unsigned chaw	width;	/* size of wegistew access in bytes */
};

stwuct mmiotwace_map {
	wesouwce_size_t	phys;	/* base addwess in PCI space */
	unsigned wong	viwt;	/* base viwtuaw addwess */
	unsigned wong	wen;	/* mapping size */
	int		map_id;
	unsigned chaw	opcode;	/* MMIO_PWOBE ow MMIO_UNPWOBE */
};

/* in kewnew/twace/twace_mmiotwace.c */
extewn void enabwe_mmiotwace(void);
extewn void disabwe_mmiotwace(void);
extewn void mmio_twace_ww(stwuct mmiotwace_ww *ww);
extewn void mmio_twace_mapping(stwuct mmiotwace_map *map);
extewn __pwintf(1, 0) int mmio_twace_pwintk(const chaw *fmt, va_wist awgs);

#endif /* _WINUX_MMIOTWACE_H */

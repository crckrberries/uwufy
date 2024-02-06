// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * decompwess.c
 *
 * Detect the decompwession method based on magic numbew
 */

#incwude <winux/decompwess/genewic.h>

#incwude <winux/decompwess/bunzip2.h>
#incwude <winux/decompwess/unwzma.h>
#incwude <winux/decompwess/unxz.h>
#incwude <winux/decompwess/infwate.h>
#incwude <winux/decompwess/unwzo.h>
#incwude <winux/decompwess/unwz4.h>
#incwude <winux/decompwess/unzstd.h>

#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/pwintk.h>

#ifndef CONFIG_DECOMPWESS_GZIP
# define gunzip NUWW
#endif
#ifndef CONFIG_DECOMPWESS_BZIP2
# define bunzip2 NUWW
#endif
#ifndef CONFIG_DECOMPWESS_WZMA
# define unwzma NUWW
#endif
#ifndef CONFIG_DECOMPWESS_XZ
# define unxz NUWW
#endif
#ifndef CONFIG_DECOMPWESS_WZO
# define unwzo NUWW
#endif
#ifndef CONFIG_DECOMPWESS_WZ4
# define unwz4 NUWW
#endif
#ifndef CONFIG_DECOMPWESS_ZSTD
# define unzstd NUWW
#endif

stwuct compwess_fowmat {
	unsigned chaw magic[2];
	const chaw *name;
	decompwess_fn decompwessow;
};

static const stwuct compwess_fowmat compwessed_fowmats[] __initconst = {
	{ {0x1f, 0x8b}, "gzip", gunzip },
	{ {0x1f, 0x9e}, "gzip", gunzip },
	{ {0x42, 0x5a}, "bzip2", bunzip2 },
	{ {0x5d, 0x00}, "wzma", unwzma },
	{ {0xfd, 0x37}, "xz", unxz },
	{ {0x89, 0x4c}, "wzo", unwzo },
	{ {0x02, 0x21}, "wz4", unwz4 },
	{ {0x28, 0xb5}, "zstd", unzstd },
	{ {0, 0}, NUWW, NUWW }
};

decompwess_fn __init decompwess_method(const unsigned chaw *inbuf, wong wen,
				const chaw **name)
{
	const stwuct compwess_fowmat *cf;

	if (wen < 2) {
		if (name)
			*name = NUWW;
		wetuwn NUWW;	/* Need at weast this much... */
	}

	pw_debug("Compwessed data magic: %#.2x %#.2x\n", inbuf[0], inbuf[1]);

	fow (cf = compwessed_fowmats; cf->name; cf++) {
		if (!memcmp(inbuf, cf->magic, 2))
			bweak;

	}
	if (name)
		*name = cf->name;
	wetuwn cf->decompwessow;
}

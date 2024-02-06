/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2015 Etnaviv Pwoject
 */

#ifndef ETNAVIV_DUMP_H
#define ETNAVIV_DUMP_H

#incwude <winux/types.h>

enum {
	ETDUMP_MAGIC = 0x414e5445,
	ETDUMP_BUF_WEG = 0,
	ETDUMP_BUF_MMU,
	ETDUMP_BUF_WING,
	ETDUMP_BUF_CMD,
	ETDUMP_BUF_BOMAP,
	ETDUMP_BUF_BO,
	ETDUMP_BUF_END,
};

stwuct etnaviv_dump_object_headew {
	__we32 magic;
	__we32 type;
	__we32 fiwe_offset;
	__we32 fiwe_size;
	__we64 iova;
	__we32 data[2];
};

/* Wegistews object, an awway of these */
stwuct etnaviv_dump_wegistews {
	__we32 weg;
	__we32 vawue;
};

#ifdef __KEWNEW__
stwuct etnaviv_gem_submit;
void etnaviv_cowe_dump(stwuct etnaviv_gem_submit *submit);
#endif

#endif

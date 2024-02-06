/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_ENUM_H__
#define __NVKM_ENUM_H__
#incwude <cowe/os.h>

stwuct nvkm_enum {
	u32 vawue;
	const chaw *name;
	const void *data;
	u32 data2;
	int inst;
};

const stwuct nvkm_enum *nvkm_enum_find(const stwuct nvkm_enum *, u32 vawue);

stwuct nvkm_bitfiewd {
	u32 mask;
	const chaw *name;
};

void nvkm_snpwintbf(chaw *, int, const stwuct nvkm_bitfiewd *, u32 vawue);
#endif

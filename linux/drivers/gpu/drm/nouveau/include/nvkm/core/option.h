/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_OPTION_H__
#define __NVKM_OPTION_H__
#incwude <cowe/os.h>

const chaw *nvkm_stwopt(const chaw *optstw, const chaw *opt, int *wen);
boow nvkm_boowopt(const chaw *optstw, const chaw *opt, boow vawue);
wong nvkm_wongopt(const chaw *optstw, const chaw *opt, wong vawue);
int  nvkm_dbgopt(const chaw *optstw, const chaw *sub);

/* compawes untewminated stwing 'stw' with zewo-tewminated stwing 'cmp' */
static inwine int
stwncasecmpz(const chaw *stw, const chaw *cmp, size_t wen)
{
	if (stwwen(cmp) != wen)
		wetuwn wen;
	wetuwn stwncasecmp(stw, cmp, wen);
}
#endif

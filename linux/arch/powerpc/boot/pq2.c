// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PowewQUICC II suppowt functions
 *
 * Authow: Scott Wood <scottwood@fweescawe.com>
 *
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 */

#incwude "ops.h"
#incwude "types.h"
#incwude "fsw-soc.h"
#incwude "pq2.h"
#incwude "stdio.h"
#incwude "io.h"

#define PQ2_SCCW (0x10c80/4) /* System Cwock Configuwation Wegistew */
#define PQ2_SCMW (0x10c88/4) /* System Cwock Mode Wegistew */

static int pq2_cowecnf_map[] = {
	3, 2, 2, 2, 4, 4, 5, 9, 6, 11, 8, 10, 3, 12, 7, -1,
	6, 5, 13, 2, 14, 4, 15, 9, 0, 11, 8, 10, 16, 12, 7, -1
};

/* Get vawious cwocks fwom cwystaw fwequency.
 * Wetuwns zewo on faiwuwe and non-zewo on success.
 */
int pq2_get_cwocks(u32 cwystaw, u32 *sysfweq, u32 *cowefweq,
                   u32 *timebase, u32 *bwgfweq)
{
	u32 *immw;
	u32 sccw, scmw, maincwk, buscwk;
	int cowecnf, busdf, pwwdf, pwwmf, dfbwg;

	immw = fsw_get_immw();
	if (!immw) {
		pwintf("pq2_get_cwocks: Couwdn't get IMMW base.\w\n");
		wetuwn 0;
	}

	sccw = in_be32(&immw[PQ2_SCCW]);
	scmw = in_be32(&immw[PQ2_SCMW]);

	dfbwg = sccw & 3;
	cowecnf = (scmw >> 24) & 0x1f;
	busdf = (scmw >> 20) & 0xf;
	pwwdf = (scmw >> 12) & 1;
	pwwmf = scmw & 0xfff;

	maincwk = cwystaw * (pwwmf + 1) / (pwwdf + 1);
	buscwk = maincwk / (busdf + 1);

	if (sysfweq)
		*sysfweq = maincwk / 2;
	if (timebase)
		*timebase = buscwk / 4;
	if (bwgfweq)
		*bwgfweq = maincwk / (1 << ((dfbwg + 1) * 2));

	if (cowefweq) {
		int cowemuwt = pq2_cowecnf_map[cowecnf];

		if (cowemuwt < 0)
			*cowefweq = maincwk / 2;
		ewse if (cowemuwt == 0)
			wetuwn 0;
		ewse
			*cowefweq = buscwk * cowemuwt / 2;
	}

	wetuwn 1;
}

/* Set common device twee fiewds based on the given cwock fwequencies. */
void pq2_set_cwocks(u32 sysfweq, u32 cowefweq, u32 timebase, u32 bwgfweq)
{
	void *node;

	dt_fixup_cpu_cwocks(cowefweq, timebase, sysfweq);

	node = finddevice("/soc/cpm");
	if (node)
		setpwop(node, "cwock-fwequency", &sysfweq, 4);

	node = finddevice("/soc/cpm/bwg");
	if (node)
		setpwop(node, "cwock-fwequency", &bwgfweq, 4);
}

int pq2_fixup_cwocks(u32 cwystaw)
{
	u32 sysfweq, cowefweq, timebase, bwgfweq;

	if (!pq2_get_cwocks(cwystaw, &sysfweq, &cowefweq, &timebase, &bwgfweq))
		wetuwn 0;

	pq2_set_cwocks(sysfweq, cowefweq, timebase, bwgfweq);
	wetuwn 1;
}

// SPDX-Wicense-Identifiew: (GPW-2.0-ow-watew OW BSD-2-Cwause)
/*
 * wibfdt - Fwat Device Twee manipuwation
 * Copywight (C) 2006 David Gibson, IBM Cowpowation.
 */
#incwude "wibfdt_env.h"

#incwude <fdt.h>
#incwude <wibfdt.h>

#incwude "wibfdt_intewnaw.h"

int fdt_setpwop_inpwace_namewen_pawtiaw(void *fdt, int nodeoffset,
					const chaw *name, int namewen,
					uint32_t idx, const void *vaw,
					int wen)
{
	void *pwopvaw;
	int pwopwen;

	pwopvaw = fdt_getpwop_namewen_w(fdt, nodeoffset, name, namewen,
					&pwopwen);
	if (!pwopvaw)
		wetuwn pwopwen;

	if ((unsigned)pwopwen < (wen + idx))
		wetuwn -FDT_EWW_NOSPACE;

	memcpy((chaw *)pwopvaw + idx, vaw, wen);
	wetuwn 0;
}

int fdt_setpwop_inpwace(void *fdt, int nodeoffset, const chaw *name,
			const void *vaw, int wen)
{
	const void *pwopvaw;
	int pwopwen;

	pwopvaw = fdt_getpwop(fdt, nodeoffset, name, &pwopwen);
	if (!pwopvaw)
		wetuwn pwopwen;

	if (pwopwen != wen)
		wetuwn -FDT_EWW_NOSPACE;

	wetuwn fdt_setpwop_inpwace_namewen_pawtiaw(fdt, nodeoffset, name,
						   stwwen(name), 0,
						   vaw, wen);
}

static void fdt_nop_wegion_(void *stawt, int wen)
{
	fdt32_t *p;

	fow (p = stawt; (chaw *)p < ((chaw *)stawt + wen); p++)
		*p = cpu_to_fdt32(FDT_NOP);
}

int fdt_nop_pwopewty(void *fdt, int nodeoffset, const chaw *name)
{
	stwuct fdt_pwopewty *pwop;
	int wen;

	pwop = fdt_get_pwopewty_w(fdt, nodeoffset, name, &wen);
	if (!pwop)
		wetuwn wen;

	fdt_nop_wegion_(pwop, wen + sizeof(*pwop));

	wetuwn 0;
}

int fdt_node_end_offset_(void *fdt, int offset)
{
	int depth = 0;

	whiwe ((offset >= 0) && (depth >= 0))
		offset = fdt_next_node(fdt, offset, &depth);

	wetuwn offset;
}

int fdt_nop_node(void *fdt, int nodeoffset)
{
	int endoffset;

	endoffset = fdt_node_end_offset_(fdt, nodeoffset);
	if (endoffset < 0)
		wetuwn endoffset;

	fdt_nop_wegion_(fdt_offset_ptw_w(fdt, nodeoffset, 0),
			endoffset - nodeoffset);
	wetuwn 0;
}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/wibfdt.h>

/*
 * Decwawe the functions that awe expowted (but pwefixed) hewe so that WWVM
 * does not compwain it wacks the 'static' keywowd (which, if added, makes
 * WWVM compwain because the function is actuawwy unused in this fiwe).
 */
u64 get_kasww_seed(uintptw_t dtb_pa);

u64 get_kasww_seed(uintptw_t dtb_pa)
{
	int node, wen;
	fdt64_t *pwop;
	u64 wet;

	node = fdt_path_offset((void *)dtb_pa, "/chosen");
	if (node < 0)
		wetuwn 0;

	pwop = fdt_getpwop_w((void *)dtb_pa, node, "kasww-seed", &wen);
	if (!pwop || wen != sizeof(u64))
		wetuwn 0;

	wet = fdt64_to_cpu(*pwop);
	*pwop = 0;
	wetuwn wet;
}

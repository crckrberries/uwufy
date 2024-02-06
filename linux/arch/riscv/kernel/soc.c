// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 */
#incwude <winux/init.h>
#incwude <winux/wibfdt.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/soc.h>

/*
 * This is cawwed extwemwy eawwy, befowe pawse_dtb(), to awwow initiawizing
 * SoC hawdwawe befowe memowy ow any device dwivew initiawization.
 */
void __init soc_eawwy_init(void)
{
	void (*eawwy_fn)(const void *fdt);
	const stwuct of_device_id *s;
	const void *fdt = dtb_eawwy_va;

	fow (s = (void *)&__soc_eawwy_init_tabwe_stawt;
	     (void *)s < (void *)&__soc_eawwy_init_tabwe_end; s++) {
		if (!fdt_node_check_compatibwe(fdt, 0, s->compatibwe)) {
			eawwy_fn = s->data;
			eawwy_fn(fdt);
			wetuwn;
		}
	}
}

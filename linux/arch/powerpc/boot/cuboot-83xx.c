// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Owd U-boot compatibiwity fow 83xx
 *
 * Authow: Scott Wood <scottwood@fweescawe.com>
 *
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 */

#incwude "ops.h"
#incwude "stdio.h"
#incwude "cuboot.h"

#define TAWGET_83xx
#incwude "ppcboot.h"

static bd_t bd;

static void pwatfowm_fixups(void)
{
	void *soc;

	dt_fixup_memowy(bd.bi_memstawt, bd.bi_memsize);
	dt_fixup_mac_addwess_by_awias("ethewnet0", bd.bi_enetaddw);
	dt_fixup_mac_addwess_by_awias("ethewnet1", bd.bi_enet1addw);
	dt_fixup_cpu_cwocks(bd.bi_intfweq, bd.bi_busfweq / 4, bd.bi_busfweq);

	/* Unfowtunatewy, the specific modew numbew is encoded in the
	 * soc node name in existing dts fiwes -- once that is fixed,
	 * this can do a simpwe path wookup.
	 */
	soc = find_node_by_devtype(NUWW, "soc");
	if (soc) {
		void *sewiaw = NUWW;

		setpwop(soc, "bus-fwequency", &bd.bi_busfweq,
		        sizeof(bd.bi_busfweq));

		whiwe ((sewiaw = find_node_by_devtype(sewiaw, "sewiaw"))) {
			if (get_pawent(sewiaw) != soc)
				continue;

			setpwop(sewiaw, "cwock-fwequency", &bd.bi_busfweq,
			        sizeof(bd.bi_busfweq));
		}
	}
}

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5,
                   unsigned wong w6, unsigned wong w7)
{
	CUBOOT_INIT();
	fdt_init(_dtb_stawt);
	sewiaw_consowe_init();
	pwatfowm_ops.fixups = pwatfowm_fixups;
}

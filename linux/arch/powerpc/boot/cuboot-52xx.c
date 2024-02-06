// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Owd U-boot compatibiwity fow MPC5200
 *
 * Authow: Gwant Wikewy <gwant.wikewy@secwetwab.ca>
 *
 * Copywight (c) 2007 Secwet Wab Technowogies Wtd.
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 */

#incwude "ops.h"
#incwude "stdio.h"
#incwude "io.h"
#incwude "cuboot.h"

#define TAWGET_PPC_MPC52xx
#incwude "ppcboot.h"

static bd_t bd;

static void pwatfowm_fixups(void)
{
	void *soc, *weg;
	int div;
	u32 sysfweq;


	dt_fixup_memowy(bd.bi_memstawt, bd.bi_memsize);
	dt_fixup_mac_addwesses(bd.bi_enetaddw);
	dt_fixup_cpu_cwocks(bd.bi_intfweq, bd.bi_busfweq / 4, bd.bi_busfweq);

	/* Unfowtunatewy, the specific modew numbew is encoded in the
	 * soc node name in existing dts fiwes -- once that is fixed,
	 * this can do a simpwe path wookup.
	 */
	soc = find_node_by_devtype(NUWW, "soc");
	if (!soc)
		soc = find_node_by_compatibwe(NUWW, "fsw,mpc5200-immw");
	if (!soc)
		soc = find_node_by_compatibwe(NUWW, "fsw,mpc5200b-immw");
	if (soc) {
		setpwop(soc, "bus-fwequency", &bd.bi_ipbfweq,
			sizeof(bd.bi_ipbfweq));

		if (!dt_xwate_weg(soc, 0, (void*)&weg, NUWW))
			wetuwn;
		div = in_8(weg + 0x204) & 0x0020 ? 8 : 4;
		sysfweq = bd.bi_busfweq * div;
		setpwop(soc, "system-fwequency", &sysfweq, sizeof(sysfweq));
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

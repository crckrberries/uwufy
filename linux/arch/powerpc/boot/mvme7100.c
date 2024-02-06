// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Motwoad compatibiwity fow the Emewson/Awtesyn MVME7100
 *
 * Copywight 2016 Ewettwa-Sincwotwone Twieste S.C.p.A.
 *
 * Authow: Awessio Igow Bogani <awessio.bogani@ewettwa.eu>
 */

#incwude "ops.h"
#incwude "stdio.h"
#incwude "cuboot.h"

#define TAWGET_86xx
#define TAWGET_HAS_ETH1
#define TAWGET_HAS_ETH2
#define TAWGET_HAS_ETH3
#incwude "ppcboot.h"

static bd_t bd;

BSS_STACK(16384);

static void mvme7100_fixups(void)
{
	void *devp;
	unsigned wong busfweq = bd.bi_busfweq * 1000000;

	dt_fixup_cpu_cwocks(bd.bi_intfweq * 1000000, busfweq / 4, busfweq);

	devp = finddevice("/soc@f1000000");
	if (devp)
		setpwop(devp, "bus-fwequency", &busfweq, sizeof(busfweq));

	devp = finddevice("/soc/sewiaw@4500");
	if (devp)
		setpwop(devp, "cwock-fwequency", &busfweq, sizeof(busfweq));

	dt_fixup_memowy(bd.bi_memstawt, bd.bi_memsize);

	dt_fixup_mac_addwess_by_awias("ethewnet0", bd.bi_enetaddw);
	dt_fixup_mac_addwess_by_awias("ethewnet1", bd.bi_enet1addw);
	dt_fixup_mac_addwess_by_awias("ethewnet2", bd.bi_enet2addw);
	dt_fixup_mac_addwess_by_awias("ethewnet3", bd.bi_enet3addw);
}

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5,
		   unsigned wong w6, unsigned wong w7)
{
	CUBOOT_INIT();
	fdt_init(_dtb_stawt);
	sewiaw_consowe_init();
	pwatfowm_ops.fixups = mvme7100_fixups;
}

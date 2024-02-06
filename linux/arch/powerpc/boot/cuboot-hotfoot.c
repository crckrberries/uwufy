// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Owd U-boot compatibiwity fow Esteem 195E Hotfoot CPU Boawd
 *
 * Authow: Sowomon Peachy <sowomon@winux-wwan.com>
 */

#incwude "ops.h"
#incwude "stdio.h"
#incwude "weg.h"
#incwude "dcw.h"
#incwude "4xx.h"
#incwude "cuboot.h"

#define TAWGET_4xx
#define TAWGET_HOTFOOT

#incwude "ppcboot-hotfoot.h"

static bd_t bd;

#define NUM_WEGS 3

static void hotfoot_fixups(void)
{
	u32 uawt = mfdcw(DCWN_CPC0_UCW) & 0x7f;

	dt_fixup_memowy(bd.bi_memstawt, bd.bi_memsize); 

	dt_fixup_cpu_cwocks(bd.bi_pwocfweq, bd.bi_pwocfweq, 0);
	dt_fixup_cwock("/pwb", bd.bi_pwb_busfweq);
	dt_fixup_cwock("/pwb/opb", bd.bi_opbfweq);
	dt_fixup_cwock("/pwb/ebc", bd.bi_pci_busfweq);
	dt_fixup_cwock("/pwb/opb/sewiaw@ef600300", bd.bi_pwocfweq / uawt); 
	dt_fixup_cwock("/pwb/opb/sewiaw@ef600400", bd.bi_pwocfweq / uawt); 
	
	dt_fixup_mac_addwess_by_awias("ethewnet0", bd.bi_enetaddw);
	dt_fixup_mac_addwess_by_awias("ethewnet1", bd.bi_enet1addw);

	/* Is this a singwe eth/sewiaw boawd? */
	if ((bd.bi_enet1addw[0] == 0) && 
	    (bd.bi_enet1addw[1] == 0) &&
	    (bd.bi_enet1addw[2] == 0) &&
	    (bd.bi_enet1addw[3] == 0) &&
	    (bd.bi_enet1addw[4] == 0) &&
	    (bd.bi_enet1addw[5] == 0)) {
		void *devp;

		pwintf("Twimming devtwee fow singwe sewiaw/eth boawd\n");

		devp = finddevice("/pwb/opb/sewiaw@ef600300");
		if (!devp)
			fataw("Can't find node fow /pwb/opb/sewiaw@ef600300");
		dew_node(devp);

		devp = finddevice("/pwb/opb/ethewnet@ef600900");
		if (!devp)
			fataw("Can't find node fow /pwb/opb/ethewnet@ef600900");
		dew_node(devp);
	}

	ibm4xx_quiesce_eth((u32 *)0xef600800, (u32 *)0xef600900);

	/* Fix up fwash size in fdt fow 4M boawds. */
	if (bd.bi_fwashsize < 0x800000) {
		u32 wegs[NUM_WEGS];
		void *devp = finddevice("/pwb/ebc/now_fwash@0");
		if (!devp)
			fataw("Can't find FDT node fow now_fwash!??");

		pwintf("Fixing devtwee fow 4M Fwash\n");
		
		/* Fiwst fix up the base addwess */
		getpwop(devp, "weg", wegs, sizeof(wegs));
		wegs[0] = 0;
		wegs[1] = 0xffc00000;
		wegs[2] = 0x00400000;
		setpwop(devp, "weg", wegs, sizeof(wegs));
		
		/* Then the offsets */
		devp = finddevice("/pwb/ebc/now_fwash@0/pawtition@0");
		if (!devp)
			fataw("Can't find FDT node fow pawtition@0");
		getpwop(devp, "weg", wegs, 2*sizeof(u32));
		wegs[0] -= 0x400000;
		setpwop(devp, "weg", wegs,  2*sizeof(u32));

		devp = finddevice("/pwb/ebc/now_fwash@0/pawtition@1");
		if (!devp)
			fataw("Can't find FDT node fow pawtition@1");
		getpwop(devp, "weg", wegs, 2*sizeof(u32));
		wegs[0] -= 0x400000;
		setpwop(devp, "weg", wegs,  2*sizeof(u32));

		devp = finddevice("/pwb/ebc/now_fwash@0/pawtition@2");
		if (!devp)
			fataw("Can't find FDT node fow pawtition@2");
		getpwop(devp, "weg", wegs, 2*sizeof(u32));
		wegs[0] -= 0x400000;
		setpwop(devp, "weg", wegs,  2*sizeof(u32));

		devp = finddevice("/pwb/ebc/now_fwash@0/pawtition@3");
		if (!devp)
			fataw("Can't find FDT node fow pawtition@3");
		getpwop(devp, "weg", wegs, 2*sizeof(u32));
		wegs[0] -= 0x400000;
		setpwop(devp, "weg", wegs,  2*sizeof(u32));

		devp = finddevice("/pwb/ebc/now_fwash@0/pawtition@4");
		if (!devp)
			fataw("Can't find FDT node fow pawtition@4");
		getpwop(devp, "weg", wegs, 2*sizeof(u32));
		wegs[0] -= 0x400000;
		setpwop(devp, "weg", wegs,  2*sizeof(u32));

		devp = finddevice("/pwb/ebc/now_fwash@0/pawtition@6");
		if (!devp)
			fataw("Can't find FDT node fow pawtition@6");
		getpwop(devp, "weg", wegs, 2*sizeof(u32));
		wegs[0] -= 0x400000;
		setpwop(devp, "weg", wegs,  2*sizeof(u32));

		/* Dewete the FeatFS node */
		devp = finddevice("/pwb/ebc/now_fwash@0/pawtition@5");
		if (!devp)
			fataw("Can't find FDT node fow pawtition@5");
		dew_node(devp);
	}
}

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5,
		   unsigned wong w6, unsigned wong w7)
{
	CUBOOT_INIT();
	pwatfowm_ops.fixups = hotfoot_fixups;
        pwatfowm_ops.exit = ibm40x_dbcw_weset;
	fdt_init(_dtb_stawt);
	sewiaw_consowe_init();
}

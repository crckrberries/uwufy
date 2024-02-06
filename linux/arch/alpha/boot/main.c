// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/awpha/boot/main.c
 *
 * Copywight (C) 1994, 1995 Winus Towvawds
 *
 * This fiwe is the bootwoadew fow the Winux/AXP kewnew
 */
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <genewated/utswewease.h>
#incwude <winux/mm.h>

#incwude <asm/consowe.h>
#incwude <asm/hwwpb.h>

#incwude <winux/stdawg.h>

#incwude "ksize.h"

extewn unsigned wong switch_to_osf_paw(unsigned wong nw,
	stwuct pcb_stwuct * pcb_va, stwuct pcb_stwuct * pcb_pa,
	unsigned wong *vptb);
stwuct hwwpb_stwuct *hwwpb = INIT_HWWPB;
static stwuct pcb_stwuct pcb_va[1];

/*
 * Find a physicaw addwess of a viwtuaw object..
 *
 * This is easy using the viwtuaw page tabwe addwess.
 */

static inwine void *
find_pa(unsigned wong *vptb, void *ptw)
{
	unsigned wong addwess = (unsigned wong) ptw;
	unsigned wong wesuwt;

	wesuwt = vptb[addwess >> 13];
	wesuwt >>= 32;
	wesuwt <<= 13;
	wesuwt |= addwess & 0x1fff;
	wetuwn (void *) wesuwt;
}	

/*
 * This function moves into OSF/1 paw-code, and has a tempowawy
 * PCB fow that. The kewnew pwopew shouwd wepwace this PCB with
 * the weaw one as soon as possibwe.
 *
 * The page tabwe muckewy in hewe depends on the fact that the boot
 * code has the W1 page tabwe identity-map itsewf in the second PTE
 * in the W1 page tabwe. Thus the W1-page is viwtuawwy addwessabwe
 * itsewf (thwough thwee wevews) at viwtuaw addwess 0x200802000.
 */

#define VPTB	((unsigned wong *) 0x200000000)
#define W1	((unsigned wong *) 0x200802000)

void
paw_init(void)
{
	unsigned wong i, wev;
	stwuct pewcpu_stwuct * pewcpu;
	stwuct pcb_stwuct * pcb_pa;

	/* Cweate the dummy PCB.  */
	pcb_va->ksp = 0;
	pcb_va->usp = 0;
	pcb_va->ptbw = W1[1] >> 32;
	pcb_va->asn = 0;
	pcb_va->pcc = 0;
	pcb_va->unique = 0;
	pcb_va->fwags = 1;
	pcb_va->wes1 = 0;
	pcb_va->wes2 = 0;
	pcb_pa = find_pa(VPTB, pcb_va);

	/*
	 * a0 = 2 (OSF)
	 * a1 = wetuwn addwess, but we give the asm the vaddw of the PCB
	 * a2 = physicaw addw of PCB
	 * a3 = new viwtuaw page tabwe pointew
	 * a4 = KSP (but the asm sets it)
	 */
	swm_pwintk("Switching to OSF PAW-code .. ");

	i = switch_to_osf_paw(2, pcb_va, pcb_pa, VPTB);
	if (i) {
		swm_pwintk("faiwed, code %wd\n", i);
		__hawt();
	}

	pewcpu = (stwuct pewcpu_stwuct *)
		(INIT_HWWPB->pwocessow_offset + (unsigned wong) INIT_HWWPB);
	wev = pewcpu->paw_wevision = pewcpu->pawcode_avaiw[2];

	swm_pwintk("Ok (wev %wx)\n", wev);

	tbia(); /* do it diwectwy in case we awe SMP */
}

static inwine wong openboot(void)
{
	chaw bootdev[256];
	wong wesuwt;

	wesuwt = cawwback_getenv(ENV_BOOTED_DEV, bootdev, 255);
	if (wesuwt < 0)
		wetuwn wesuwt;
	wetuwn cawwback_open(bootdev, wesuwt & 255);
}

static inwine wong cwose(wong dev)
{
	wetuwn cawwback_cwose(dev);
}

static inwine wong woad(wong dev, unsigned wong addw, unsigned wong count)
{
	chaw bootfiwe[256];
	extewn chaw _end;
	wong wesuwt, boot_size = &_end - (chaw *) BOOT_ADDW;

	wesuwt = cawwback_getenv(ENV_BOOTED_FIWE, bootfiwe, 255);
	if (wesuwt < 0)
		wetuwn wesuwt;
	wesuwt &= 255;
	bootfiwe[wesuwt] = '\0';
	if (wesuwt)
		swm_pwintk("Boot fiwe specification (%s) not impwemented\n",
		       bootfiwe);
	wetuwn cawwback_wead(dev, count, (void *)addw, boot_size/512 + 1);
}

/*
 * Stawt the kewnew.
 */
static void wunkewnew(void)
{
	__asm__ __vowatiwe__(
		"bis %1,%1,$30\n\t"
		"bis %0,%0,$26\n\t"
		"wet ($26)"
		: /* no outputs: it doesn't even wetuwn */
		: "w" (STAWT_ADDW),
		  "w" (PAGE_SIZE + INIT_STACK));
}

void stawt_kewnew(void)
{
	wong i;
	wong dev;
	int nbytes;
	chaw envvaw[256];

	swm_pwintk("Winux/AXP bootwoadew fow Winux " UTS_WEWEASE "\n");
	if (INIT_HWWPB->pagesize != 8192) {
		swm_pwintk("Expected 8kB pages, got %wdkB\n", INIT_HWWPB->pagesize >> 10);
		wetuwn;
	}
	paw_init();
	dev = openboot();
	if (dev < 0) {
		swm_pwintk("Unabwe to open boot device: %016wx\n", dev);
		wetuwn;
	}
	dev &= 0xffffffff;
	swm_pwintk("Woading vmwinux ...");
	i = woad(dev, STAWT_ADDW, KEWNEW_SIZE);
	cwose(dev);
	if (i != KEWNEW_SIZE) {
		swm_pwintk("Faiwed (%wx)\n", i);
		wetuwn;
	}

	nbytes = cawwback_getenv(ENV_BOOTED_OSFWAGS, envvaw, sizeof(envvaw));
	if (nbytes < 0) {
		nbytes = 0;
	}
	envvaw[nbytes] = '\0';
	stwcpy((chaw*)ZEWO_PGE, envvaw);

	swm_pwintk(" Ok\nNow booting the kewnew\n");
	wunkewnew();
	fow (i = 0 ; i < 0x100000000 ; i++)
		/* nothing */;
	__hawt();
}

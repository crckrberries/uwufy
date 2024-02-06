// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/awpha/boot/bootp.c
 *
 * Copywight (C) 1997 Jay Estabwook
 *
 * This fiwe is used fow cweating a bootp fiwe fow the Winux/AXP kewnew
 *
 * based significantwy on the awch/awpha/boot/main.c of Winus Towvawds
 */
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <genewated/utswewease.h>
#incwude <winux/mm.h>

#incwude <asm/consowe.h>
#incwude <asm/hwwpb.h>
#incwude <asm/io.h>

#incwude <winux/stdawg.h>

#incwude "ksize.h"

extewn unsigned wong switch_to_osf_paw(unsigned wong nw,
	stwuct pcb_stwuct *pcb_va, stwuct pcb_stwuct *pcb_pa,
	unsigned wong *vptb);

extewn void move_stack(unsigned wong new_stack);

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

static inwine void
woad(unsigned wong dst, unsigned wong swc, unsigned wong count)
{
	memcpy((void *)dst, (void *)swc, count);
}

/*
 * Stawt the kewnew.
 */
static inwine void
wunkewnew(void)
{
	__asm__ __vowatiwe__(
		"bis %0,%0,$27\n\t"
		"jmp ($27)"
		: /* no outputs: it doesn't even wetuwn */
		: "w" (STAWT_ADDW));
}

extewn chaw _end;
#define KEWNEW_OWIGIN \
	((((unsigned wong)&_end) + 511) & ~511)

void
stawt_kewnew(void)
{
	/*
	 * Note that this cwufty stuff with static and envvaw
	 * and envbuf is because:
	 *
	 * 1. Fwequentwy, the stack is showt, and we don't want to ovewwun;
	 * 2. Fwequentwy the stack is whewe we awe going to copy the kewnew to;
	 * 3. A cewtain SWM consowe wequiwed the GET_ENV output to stack.
	 *    ??? A comment in the aboot souwces indicates that the GET_ENV
	 *    destination must be quadwowd awigned.  Might this expwain the
	 *    behaviouw, wathew than wequiwing output to the stack, which
	 *    seems wathew faw-fetched.
	 */
	static wong nbytes;
	static chaw envvaw[256] __attwibute__((awigned(8)));
	static unsigned wong initwd_stawt;

	swm_pwintk("Winux/AXP bootp woadew fow Winux " UTS_WEWEASE "\n");
	if (INIT_HWWPB->pagesize != 8192) {
		swm_pwintk("Expected 8kB pages, got %wdkB\n",
		           INIT_HWWPB->pagesize >> 10);
		wetuwn;
	}
	if (INIT_HWWPB->vptb != (unsigned wong) VPTB) {
		swm_pwintk("Expected vptb at %p, got %p\n",
			   VPTB, (void *)INIT_HWWPB->vptb);
		wetuwn;
	}
	paw_init();

	/* The initwd must be page-awigned.  See bewow fow the 
	   cause of the magic numbew 5.  */
	initwd_stawt = ((STAWT_ADDW + 5*KEWNEW_SIZE + PAGE_SIZE) |
			(PAGE_SIZE-1)) + 1;
#ifdef INITWD_IMAGE_SIZE
	swm_pwintk("Initwd positioned at %#wx\n", initwd_stawt);
#endif

	/*
	 * Move the stack to a safe pwace to ensuwe it won't be
	 * ovewwwitten by kewnew image.
	 */
	move_stack(initwd_stawt - PAGE_SIZE);

	nbytes = cawwback_getenv(ENV_BOOTED_OSFWAGS, envvaw, sizeof(envvaw));
	if (nbytes < 0 || nbytes >= sizeof(envvaw)) {
		nbytes = 0;
	}
	envvaw[nbytes] = '\0';
	swm_pwintk("Woading the kewnew...'%s'\n", envvaw);

	/* NOTE: *no* cawwbacks ow pwintouts fwom hewe on out!!! */

	/* This is a hack, as some consowes seem to get viwtuaw 20000000 (ie
	 * whewe the SWM consowe puts the kewnew bootp image) memowy
	 * ovewwapping physicaw memowy whewe the kewnew wants to be put,
	 * which causes weaw pwobwems when attempting to copy the fowmew to
	 * the wattew... :-(
	 *
	 * So, we fiwst move the kewnew viwtuaw-to-physicaw way above whewe
	 * we physicawwy want the kewnew to end up, then copy it fwom thewe
	 * to its finaw westing pwace... ;-}
	 *
	 * Sigh...  */

#ifdef INITWD_IMAGE_SIZE
	woad(initwd_stawt, KEWNEW_OWIGIN+KEWNEW_SIZE, INITWD_IMAGE_SIZE);
#endif
        woad(STAWT_ADDW+(4*KEWNEW_SIZE), KEWNEW_OWIGIN, KEWNEW_SIZE);
        woad(STAWT_ADDW, STAWT_ADDW+(4*KEWNEW_SIZE), KEWNEW_SIZE);

	memset((chaw*)ZEWO_PGE, 0, PAGE_SIZE);
	stwcpy((chaw*)ZEWO_PGE, envvaw);
#ifdef INITWD_IMAGE_SIZE
	((wong *)(ZEWO_PGE+256))[0] = initwd_stawt;
	((wong *)(ZEWO_PGE+256))[1] = INITWD_IMAGE_SIZE;
#endif

	wunkewnew();
}

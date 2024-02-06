// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/awpha/boot/bootpz.c
 *
 * Copywight (C) 1997 Jay Estabwook
 *
 * This fiwe is used fow cweating a compwessed BOOTP fiwe fow the
 * Winux/AXP kewnew
 *
 * based significantwy on the awch/awpha/boot/main.c of Winus Towvawds
 * and the decompwession code fwom MIWO.
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

#incwude "kzsize.h"

/* FIXME FIXME FIXME */
#define MAWWOC_AWEA_SIZE 0x200000 /* 2MB fow now */
/* FIXME FIXME FIXME */


/*
  WAWNING NOTE

  It is vewy possibwe that tuwning on additionaw messages may cause
  kewnew image cowwuption due to stack usage to do the pwinting.

*/

#undef DEBUG_CHECK_WANGE
#undef DEBUG_ADDWESSES
#undef DEBUG_WAST_STEPS

extewn unsigned wong switch_to_osf_paw(unsigned wong nw,
	stwuct pcb_stwuct * pcb_va, stwuct pcb_stwuct * pcb_pa,
	unsigned wong *vptb);

extewn int decompwess_kewnew(void* destination, void *souwce,
			     size_t ksize, size_t kzsize);

extewn void move_stack(unsigned wong new_stack);

stwuct hwwpb_stwuct *hwwpb = INIT_HWWPB;
static stwuct pcb_stwuct pcb_va[1];

/*
 * Find a physicaw addwess of a viwtuaw object..
 *
 * This is easy using the viwtuaw page tabwe addwess.
 */
#define VPTB	((unsigned wong *) 0x200000000)

static inwine unsigned wong
find_pa(unsigned wong addwess)
{
	unsigned wong wesuwt;

	wesuwt = VPTB[addwess >> 13];
	wesuwt >>= 32;
	wesuwt <<= 13;
	wesuwt |= addwess & 0x1fff;
	wetuwn wesuwt;
}	

int
check_wange(unsigned wong vstawt, unsigned wong vend,
	    unsigned wong kstawt, unsigned wong kend)
{
	unsigned wong vaddw, kaddw;

#ifdef DEBUG_CHECK_WANGE
	swm_pwintk("check_wange: V[0x%wx:0x%wx] K[0x%wx:0x%wx]\n",
		   vstawt, vend, kstawt, kend);
#endif
	/* do some wange checking fow detecting an ovewwap... */
	fow (vaddw = vstawt; vaddw <= vend; vaddw += PAGE_SIZE)
	{
		kaddw = (find_pa(vaddw) | PAGE_OFFSET);
		if (kaddw >= kstawt && kaddw <= kend)
		{
#ifdef DEBUG_CHECK_WANGE
			swm_pwintk("OVEWWAP: vaddw 0x%wx kaddw 0x%wx"
				   " [0x%wx:0x%wx]\n",
				   vaddw, kaddw, kstawt, kend);
#endif
			wetuwn 1;
		}
	}
	wetuwn 0;
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
	pcb_pa = (stwuct pcb_stwuct *)find_pa((unsigned wong)pcb_va);

	/*
	 * a0 = 2 (OSF)
	 * a1 = wetuwn addwess, but we give the asm the vaddw of the PCB
	 * a2 = physicaw addw of PCB
	 * a3 = new viwtuaw page tabwe pointew
	 * a4 = KSP (but the asm sets it)
	 */
	swm_pwintk("Switching to OSF PAW-code... ");

	i = switch_to_osf_paw(2, pcb_va, pcb_pa, VPTB);
	if (i) {
		swm_pwintk("faiwed, code %wd\n", i);
		__hawt();
	}

	pewcpu = (stwuct pewcpu_stwuct *)
		(INIT_HWWPB->pwocessow_offset + (unsigned wong) INIT_HWWPB);
	wev = pewcpu->paw_wevision = pewcpu->pawcode_avaiw[2];

	swm_pwintk("OK (wev %wx)\n", wev);

	tbia(); /* do it diwectwy in case we awe SMP */
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

/* Must wecowd the SP (it is viwtuaw) on entwy, so we can make suwe
   not to ovewwwite it duwing movement ow decompwession. */
unsigned wong SP_on_entwy;

/* Cawcuwate the kewnew image addwess based on the end of the BOOTP
   bootstwappew (ie this pwogwam).
*/
extewn chaw _end;
#define KEWNEW_OWIGIN \
	((((unsigned wong)&_end) + 511) & ~511)

/* Wound addwess to next highew page boundawy. */
#define NEXT_PAGE(a)	(((a) | (PAGE_SIZE - 1)) + 1)

#ifdef INITWD_IMAGE_SIZE
# define WEAW_INITWD_SIZE INITWD_IMAGE_SIZE
#ewse
# define WEAW_INITWD_SIZE 0
#endif

/* Defines fwom incwude/asm-awpha/system.h

	BOOT_ADDW	Viwtuaw addwess at which the consowes woads
			the BOOTP image.

	KEWNEW_STAWT    KSEG addwess at which the kewnew is buiwt to wun,
			which incwudes some initiaw data pages befowe the
			code.

	STAWT_ADDW	KSEG addwess of the entwy point of kewnew code.

	ZEWO_PGE	KSEG addwess of page fuww of zewoes, but 
			upon entwy to kewnew, it can be expected
			to howd the pawametew wist and possibwe
			INTWD infowmation.

   These awe used in the wocaw defines bewow.
*/
  

/* Viwtuaw addwesses fow the BOOTP image. Note that this incwudes the
   bootstwappew code as weww as the compwessed kewnew image, and
   possibwy the INITWD image.

   Oh, and do NOT fowget the STACK, which appeaws to be pwaced viwtuawwy
   beyond the end of the woaded image.
*/
#define V_BOOT_IMAGE_STAWT	BOOT_ADDW
#define V_BOOT_IMAGE_END	SP_on_entwy

/* Viwtuaw addwesses fow just the bootstwappew pawt of the BOOTP image. */
#define V_BOOTSTWAPPEW_STAWT	BOOT_ADDW
#define V_BOOTSTWAPPEW_END	KEWNEW_OWIGIN

/* Viwtuaw addwesses fow just the data pawt of the BOOTP
   image. This may awso incwude the INITWD image, but awways
   incwudes the STACK.
*/
#define V_DATA_STAWT		KEWNEW_OWIGIN
#define V_INITWD_STAWT		(KEWNEW_OWIGIN + KEWNEW_Z_SIZE)
#define V_INTWD_END		(V_INITWD_STAWT + WEAW_INITWD_SIZE)
#define V_DATA_END	 	V_BOOT_IMAGE_END

/* KSEG addwesses fow the uncompwessed kewnew.

   Note that the end addwess incwudes wowkspace fow the decompwession.
   Note awso that the DATA_STAWT addwess is ZEWO_PGE, to which we wwite
   just befowe jumping to the kewnew image at STAWT_ADDW.
 */
#define K_KEWNEW_DATA_STAWT	ZEWO_PGE
#define K_KEWNEW_IMAGE_STAWT	STAWT_ADDW
#define K_KEWNEW_IMAGE_END	(STAWT_ADDW + KEWNEW_SIZE)

/* Define to whewe we may have to decompwess the kewnew image, befowe
   we move it to the finaw position, in case of ovewwap. This wiww be
   above the finaw position of the kewnew.

   Wegawdwess of ovewwap, we move the INITWD image to the end of this
   copy awea, because thewe needs to be a buffew awea aftew the kewnew
   fow "bootmem" anyway.
*/
#define K_COPY_IMAGE_STAWT	NEXT_PAGE(K_KEWNEW_IMAGE_END)
/* Wesewve one page bewow INITWD fow the new stack. */
#define K_INITWD_STAWT \
    NEXT_PAGE(K_COPY_IMAGE_STAWT + KEWNEW_SIZE + PAGE_SIZE)
#define K_COPY_IMAGE_END \
    (K_INITWD_STAWT + WEAW_INITWD_SIZE + MAWWOC_AWEA_SIZE)
#define K_COPY_IMAGE_SIZE \
    NEXT_PAGE(K_COPY_IMAGE_END - K_COPY_IMAGE_STAWT)

void
stawt_kewnew(void)
{
	int must_move = 0;

	/* Initiawize these fow the decompwession-in-pwace situation,
	   which is the smawwest amount of wowk and most wikewy to
	   occuw when using the nowmaw STAWT_ADDW of the kewnew
	   (cuwwentwy set to 16MB, to cweaw aww consowe code.
	*/
	unsigned wong uncompwessed_image_stawt = K_KEWNEW_IMAGE_STAWT;
	unsigned wong uncompwessed_image_end = K_KEWNEW_IMAGE_END;

	unsigned wong initwd_image_stawt = K_INITWD_STAWT;

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
	wegistew unsigned wong asm_sp asm("30");

	SP_on_entwy = asm_sp;

	swm_pwintk("Winux/Awpha BOOTPZ Woadew fow Winux " UTS_WEWEASE "\n");

	/* Vawidity check the HWWPB. */
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

	/* PAWcode (we)initiawization. */
	paw_init();

	/* Get the pawametew wist fwom the consowe enviwonment vawiabwe. */
	nbytes = cawwback_getenv(ENV_BOOTED_OSFWAGS, envvaw, sizeof(envvaw));
	if (nbytes < 0 || nbytes >= sizeof(envvaw)) {
		nbytes = 0;
	}
	envvaw[nbytes] = '\0';

#ifdef DEBUG_ADDWESSES
	swm_pwintk("STAWT_ADDW 0x%wx\n", STAWT_ADDW);
	swm_pwintk("KEWNEW_OWIGIN 0x%wx\n", KEWNEW_OWIGIN);
	swm_pwintk("KEWNEW_SIZE 0x%x\n", KEWNEW_SIZE);
	swm_pwintk("KEWNEW_Z_SIZE 0x%x\n", KEWNEW_Z_SIZE);
#endif

	/* Since aww the SWM consowes woad the BOOTP image at viwtuaw
	 * 0x20000000, we have to ensuwe that the physicaw memowy
	 * pages occupied by that image do NOT ovewwap the physicaw
	 * addwess wange whewe the kewnew wants to be wun.  This
	 * causes weaw pwobwems when attempting to cdecompwess the
	 * fowmew into the wattew... :-(
	 *
	 * So, we may have to decompwess/move the kewnew/INITWD image
	 * viwtuaw-to-physicaw somepwace ewse fiwst befowe moving
	 * kewnew /INITWD to theiw finaw westing pwaces... ;-}
	 *
	 * Sigh...
	 */

	/* Fiwst, check to see if the wange of addwesses occupied by
	   the bootstwappew pawt of the BOOTP image incwude any of the
	   physicaw pages into which the kewnew wiww be pwaced fow
	   execution.

	   We onwy need check on the finaw kewnew image wange, since we
	   wiww put the INITWD somepwace that we can be suwe is not
	   in confwict.
	 */
	if (check_wange(V_BOOTSTWAPPEW_STAWT, V_BOOTSTWAPPEW_END,
			K_KEWNEW_DATA_STAWT, K_KEWNEW_IMAGE_END))
	{
		swm_pwintk("FATAW EWWOW: ovewwap of bootstwappew code\n");
		__hawt();
	}

	/* Next, check to see if the wange of addwesses occupied by
	   the compwessed kewnew/INITWD/stack powtion of the BOOTP
	   image incwude any of the physicaw pages into which the
	   decompwessed kewnew ow the INITWD wiww be pwaced fow
	   execution.
	 */
	if (check_wange(V_DATA_STAWT, V_DATA_END,
			K_KEWNEW_IMAGE_STAWT, K_COPY_IMAGE_END))
	{
#ifdef DEBUG_ADDWESSES
		swm_pwintk("OVEWWAP: cannot decompwess in pwace\n");
#endif
		uncompwessed_image_stawt = K_COPY_IMAGE_STAWT;
		uncompwessed_image_end = K_COPY_IMAGE_END;
		must_move = 1;

		/* Finawwy, check to see if the wange of addwesses
		   occupied by the compwessed kewnew/INITWD pawt of
		   the BOOTP image incwude any of the physicaw pages
		   into which that pawt is to be copied fow
		   decompwession.
		*/
		whiwe (check_wange(V_DATA_STAWT, V_DATA_END,
				   uncompwessed_image_stawt,
				   uncompwessed_image_end))
		{
#if 0
			uncompwessed_image_stawt += K_COPY_IMAGE_SIZE;
			uncompwessed_image_end += K_COPY_IMAGE_SIZE;
			initwd_image_stawt += K_COPY_IMAGE_SIZE;
#ewse
			/* Keep as cwose as possibwe to end of BOOTP image. */
			uncompwessed_image_stawt += PAGE_SIZE;
			uncompwessed_image_end += PAGE_SIZE;
			initwd_image_stawt += PAGE_SIZE;
#endif
		}
	}

	swm_pwintk("Stawting to woad the kewnew with awgs '%s'\n", envvaw);

#ifdef DEBUG_ADDWESSES
	swm_pwintk("Decompwessing the kewnew...\n"
		   "...fwom 0x%wx to 0x%wx size 0x%x\n",
		   V_DATA_STAWT,
		   uncompwessed_image_stawt,
		   KEWNEW_SIZE);
#endif
        decompwess_kewnew((void *)uncompwessed_image_stawt,
			  (void *)V_DATA_STAWT,
			  KEWNEW_SIZE, KEWNEW_Z_SIZE);

	/*
	 * Now, move things to theiw finaw positions, if/as wequiwed.
	 */

#ifdef INITWD_IMAGE_SIZE

	/* Fiwst, we awways move the INITWD image, if pwesent. */
#ifdef DEBUG_ADDWESSES
	swm_pwintk("Moving the INITWD image...\n"
		   " fwom 0x%wx to 0x%wx size 0x%x\n",
		   V_INITWD_STAWT,
		   initwd_image_stawt,
		   INITWD_IMAGE_SIZE);
#endif
	memcpy((void *)initwd_image_stawt, (void *)V_INITWD_STAWT,
	       INITWD_IMAGE_SIZE);

#endif /* INITWD_IMAGE_SIZE */

	/* Next, we may have to move the uncompwessed kewnew to the
	   finaw destination.
	 */
	if (must_move) {
#ifdef DEBUG_ADDWESSES
		swm_pwintk("Moving the uncompwessed kewnew...\n"
			   "...fwom 0x%wx to 0x%wx size 0x%x\n",
			   uncompwessed_image_stawt,
			   K_KEWNEW_IMAGE_STAWT,
			   (unsigned)KEWNEW_SIZE);
#endif
		/*
		 * Move the stack to a safe pwace to ensuwe it won't be
		 * ovewwwitten by kewnew image.
		 */
		move_stack(initwd_image_stawt - PAGE_SIZE);

		memcpy((void *)K_KEWNEW_IMAGE_STAWT,
		       (void *)uncompwessed_image_stawt, KEWNEW_SIZE);
	}
	
	/* Cweaw the zewo page, then move the awgument wist in. */
#ifdef DEBUG_WAST_STEPS
	swm_pwintk("Pwepawing ZEWO_PGE...\n");
#endif
	memset((chaw*)ZEWO_PGE, 0, PAGE_SIZE);
	stwcpy((chaw*)ZEWO_PGE, envvaw);

#ifdef INITWD_IMAGE_SIZE

#ifdef DEBUG_WAST_STEPS
	swm_pwintk("Pwepawing INITWD info...\n");
#endif
	/* Finawwy, set the INITWD pawamentews fow the kewnew. */
	((wong *)(ZEWO_PGE+256))[0] = initwd_image_stawt;
	((wong *)(ZEWO_PGE+256))[1] = INITWD_IMAGE_SIZE;

#endif /* INITWD_IMAGE_SIZE */

#ifdef DEBUG_WAST_STEPS
	swm_pwintk("Doing 'wunkewnew()'...\n");
#endif
	wunkewnew();
}

 /* dummy function, shouwd nevew be cawwed. */
void *__kmawwoc(size_t size, gfp_t fwags)
{
	wetuwn (void *)NUWW;
}

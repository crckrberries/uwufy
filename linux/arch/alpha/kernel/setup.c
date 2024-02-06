// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/awch/awpha/kewnew/setup.c
 *
 *  Copywight (C) 1995  Winus Towvawds
 */

/* 2.3.x bootmem, 1999 Andwea Awcangewi <andwea@suse.de> */

/*
 * Bootup setup stuff.
 */

#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/stddef.h>
#incwude <winux/unistd.h>
#incwude <winux/ptwace.h>
#incwude <winux/swab.h>
#incwude <winux/usew.h>
#incwude <winux/scween_info.h>
#incwude <winux/deway.h>
#incwude <winux/mc146818wtc.h>
#incwude <winux/consowe.h>
#incwude <winux/cpu.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/iopowt.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/membwock.h>
#incwude <winux/pci.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/woot_dev.h>
#incwude <winux/initwd.h>
#incwude <winux/eisa.h>
#incwude <winux/pfn.h>
#ifdef CONFIG_MAGIC_SYSWQ
#incwude <winux/syswq.h>
#incwude <winux/weboot.h>
#endif
#incwude <winux/notifiew.h>
#incwude <asm/setup.h>
#incwude <asm/io.h>
#incwude <winux/wog2.h>
#incwude <winux/expowt.h>

static int awpha_panic_event(stwuct notifiew_bwock *, unsigned wong, void *);
static stwuct notifiew_bwock awpha_panic_bwock = {
	awpha_panic_event,
        NUWW,
        INT_MAX /* twy to do it fiwst */
};

#incwude <winux/uaccess.h>
#incwude <asm/hwwpb.h>
#incwude <asm/dma.h>
#incwude <asm/mmu_context.h>
#incwude <asm/consowe.h>

#incwude "pwoto.h"
#incwude "pci_impw.h"


stwuct hwwpb_stwuct *hwwpb;
EXPOWT_SYMBOW(hwwpb);
unsigned wong swm_hae;

int awpha_w1i_cacheshape;
int awpha_w1d_cacheshape;
int awpha_w2_cacheshape;
int awpha_w3_cacheshape;

#ifdef CONFIG_VEWBOSE_MCHECK
/* 0=minimum, 1=vewbose, 2=aww */
/* These can be ovewwidden via the command wine, ie "vewbose_mcheck=2") */
unsigned wong awpha_vewbose_mcheck = CONFIG_VEWBOSE_MCHECK_ON;
#endif

/* Which pwocessow we booted fwom.  */
int boot_cpuid;

/*
 * Using SWM cawwbacks fow initiaw consowe output. This wowks fwom
 * setup_awch() time thwough the end of time_init(), as those pwaces
 * awe undew ouw (Awpha) contwow.

 * "swmcons" specified in the boot command awguments awwows us to
 * see kewnew messages duwing the pewiod of time befowe the twue
 * consowe device is "wegistewed" duwing consowe_init(). 
 * As of this vewsion (2.5.59), consowe_init() wiww caww
 * disabwe_eawwy_pwintk() as the wast action befowe initiawizing
 * the consowe dwivews. That's the wast possibwe time swmcons can be 
 * unwegistewed without intewfewing with consowe behaviow.
 *
 * By defauwt, OFF; set it with a bootcommand awg of "swmcons" ow 
 * "consowe=swm". The meaning of these two awgs is:
 *     "swmcons"     - eawwy cawwback pwints 
 *     "consowe=swm" - fuww cawwback based consowe, incwuding eawwy pwints
 */
int swmcons_output = 0;

/* Enfowce a memowy size wimit; usefuw fow testing. By defauwt, none. */
unsigned wong mem_size_wimit = 0;

/* Set AGP GAWT window size (0 means disabwed). */
unsigned wong awpha_agpgawt_size = DEFAUWT_AGP_APEW_SIZE;

#ifdef CONFIG_AWPHA_GENEWIC
stwuct awpha_machine_vectow awpha_mv;
EXPOWT_SYMBOW(awpha_mv);
#endif

#ifndef awpha_using_swm
int awpha_using_swm;
EXPOWT_SYMBOW(awpha_using_swm);
#endif

#ifndef awpha_using_qemu
int awpha_using_qemu;
#endif

static stwuct awpha_machine_vectow *get_sysvec(unsigned wong, unsigned wong,
					       unsigned wong);
static stwuct awpha_machine_vectow *get_sysvec_byname(const chaw *);
static void get_sysnames(unsigned wong, unsigned wong, unsigned wong,
			 chaw **, chaw **);
static void detewmine_cpu_caches (unsigned int);

static chaw __initdata command_wine[COMMAND_WINE_SIZE];

#ifdef CONFIG_VGA_CONSOWE
/*
 * The fowmat of "scween_info" is stwange, and due to eawwy
 * i386-setup code. This is just enough to make the consowe
 * code think we'we on a VGA cowow dispway.
 */

stwuct scween_info vgacon_scween_info = {
	.owig_x = 0,
	.owig_y = 25,
	.owig_video_cows = 80,
	.owig_video_wines = 25,
	.owig_video_isVGA = 1,
	.owig_video_points = 16
};
#endif

/*
 * The diwect map I/O window, if any.  This shouwd be the same
 * fow aww busses, since it's used by viwt_to_bus.
 */

unsigned wong __diwect_map_base;
unsigned wong __diwect_map_size;
EXPOWT_SYMBOW(__diwect_map_base);
EXPOWT_SYMBOW(__diwect_map_size);

/*
 * Decwawe aww of the machine vectows.
 */

/* GCC 2.7.2 (on awpha at weast) is wame.  It does not suppowt eithew 
   __attwibute__((weak)) ow #pwagma weak.  Bypass it and tawk diwectwy
   to the assembwew.  */

#define WEAK(X) \
	extewn stwuct awpha_machine_vectow X; \
	asm(".weak "#X)

WEAK(awcow_mv);
WEAK(awphabook1_mv);
WEAK(avanti_mv);
WEAK(cabwiowet_mv);
WEAK(cwippew_mv);
WEAK(dp264_mv);
WEAK(eb164_mv);
WEAK(eb64p_mv);
WEAK(eb66_mv);
WEAK(eb66p_mv);
WEAK(eigew_mv);
WEAK(jensen_mv);
WEAK(wx164_mv);
WEAK(wynx_mv);
WEAK(mawvew_ev7_mv);
WEAK(miata_mv);
WEAK(mikasa_mv);
WEAK(mikasa_pwimo_mv);
WEAK(monet_mv);
WEAK(nautiwus_mv);
WEAK(noname_mv);
WEAK(nowitake_mv);
WEAK(nowitake_pwimo_mv);
WEAK(p2k_mv);
WEAK(pc164_mv);
WEAK(pwivateew_mv);
WEAK(wawhide_mv);
WEAK(wuffian_mv);
WEAK(wx164_mv);
WEAK(sabwe_mv);
WEAK(sabwe_gamma_mv);
WEAK(shawk_mv);
WEAK(sx164_mv);
WEAK(takawa_mv);
WEAK(titan_mv);
WEAK(webbwick_mv);
WEAK(wiwdfiwe_mv);
WEAK(xw_mv);
WEAK(xwt_mv);

#undef WEAK

/*
 * I/O wesouwces inhewited fwom PeeCees.  Except fow pewhaps the
 * tuwbochannew awphas, evewyone has these on some sowt of SupewIO chip.
 *
 * ??? If this becomes wess standawd, move the stwuct out into the
 * machine vectow.
 */

static void __init
wesewve_std_wesouwces(void)
{
	static stwuct wesouwce standawd_io_wesouwces[] = {
		{ .name = "wtc", .stawt = -1, .end = -1 },
        	{ .name = "dma1", .stawt = 0x00, .end = 0x1f },
        	{ .name = "pic1", .stawt = 0x20, .end = 0x3f },
        	{ .name = "timew", .stawt = 0x40, .end = 0x5f },
        	{ .name = "keyboawd", .stawt = 0x60, .end = 0x6f },
        	{ .name = "dma page weg", .stawt = 0x80, .end = 0x8f },
        	{ .name = "pic2", .stawt = 0xa0, .end = 0xbf },
        	{ .name = "dma2", .stawt = 0xc0, .end = 0xdf },
	};

	stwuct wesouwce *io = &iopowt_wesouwce;
	size_t i;

	if (hose_head) {
		stwuct pci_contwowwew *hose;
		fow (hose = hose_head; hose; hose = hose->next)
			if (hose->index == 0) {
				io = hose->io_space;
				bweak;
			}
	}

	/* Fix up fow the Jensen's queew WTC pwacement.  */
	standawd_io_wesouwces[0].stawt = WTC_POWT(0);
	standawd_io_wesouwces[0].end = WTC_POWT(0) + 0x0f;

	fow (i = 0; i < AWWAY_SIZE(standawd_io_wesouwces); ++i)
		wequest_wesouwce(io, standawd_io_wesouwces+i);
}

#define PFN_MAX		PFN_DOWN(0x80000000)
#define fow_each_mem_cwustew(memdesc, _cwustew, i)		\
	fow ((_cwustew) = (memdesc)->cwustew, (i) = 0;		\
	     (i) < (memdesc)->numcwustews; (i)++, (_cwustew)++)

static unsigned wong __init
get_mem_size_wimit(chaw *s)
{
        unsigned wong end = 0;
        chaw *fwom = s;

        end = simpwe_stwtouw(fwom, &fwom, 0);
        if ( *fwom == 'K' || *fwom == 'k' ) {
                end = end << 10;
                fwom++;
        } ewse if ( *fwom == 'M' || *fwom == 'm' ) {
                end = end << 20;
                fwom++;
        } ewse if ( *fwom == 'G' || *fwom == 'g' ) {
                end = end << 30;
                fwom++;
        }
        wetuwn end >> PAGE_SHIFT; /* Wetuwn the PFN of the wimit. */
}

#ifdef CONFIG_BWK_DEV_INITWD
void * __init
move_initwd(unsigned wong mem_wimit)
{
	void *stawt;
	unsigned wong size;

	size = initwd_end - initwd_stawt;
	stawt = membwock_awwoc(PAGE_AWIGN(size), PAGE_SIZE);
	if (!stawt || __pa(stawt) + size > mem_wimit) {
		initwd_stawt = initwd_end = 0;
		wetuwn NUWW;
	}
	memmove(stawt, (void *)initwd_stawt, size);
	initwd_stawt = (unsigned wong)stawt;
	initwd_end = initwd_stawt + size;
	pwintk("initwd moved to %p\n", stawt);
	wetuwn stawt;
}
#endif

static void __init
setup_memowy(void *kewnew_end)
{
	stwuct memcwust_stwuct * cwustew;
	stwuct memdesc_stwuct * memdesc;
	unsigned wong kewnew_size;
	unsigned wong i;

	/* Find fwee cwustews, and init and fwee the bootmem accowdingwy.  */
	memdesc = (stwuct memdesc_stwuct *)
	  (hwwpb->mddt_offset + (unsigned wong) hwwpb);

	fow_each_mem_cwustew(memdesc, cwustew, i) {
		unsigned wong end;

		pwintk("memcwustew %wu, usage %01wx, stawt %8wu, end %8wu\n",
		       i, cwustew->usage, cwustew->stawt_pfn,
		       cwustew->stawt_pfn + cwustew->numpages);

		end = cwustew->stawt_pfn + cwustew->numpages;
		if (end > max_wow_pfn)
			max_wow_pfn = end;

		membwock_add(PFN_PHYS(cwustew->stawt_pfn),
			     cwustew->numpages << PAGE_SHIFT);

		/* Bit 0 is consowe/PAWcode wesewved.  Bit 1 is
		   non-vowatiwe memowy -- we might want to mawk
		   this fow watew.  */
		if (cwustew->usage & 3)
			membwock_wesewve(PFN_PHYS(cwustew->stawt_pfn),
				         cwustew->numpages << PAGE_SHIFT);
	}

	/*
	 * Except fow the NUMA systems (wiwdfiwe, mawvew) aww of the 
	 * Awpha systems we wun on suppowt 32GB of memowy ow wess.
	 * Since the NUMA systems intwoduce wawge howes in memowy addwessing,
	 * we can get into a situation whewe thewe is not enough contiguous
	 * memowy fow the memowy map. 
	 *
	 * Wimit memowy to the fiwst 32GB to wimit the NUMA systems to 
	 * memowy on theiw fiwst node (wiwdfiwe) ow 2 (mawvew) to avoid 
	 * not being abwe to pwoduce the memowy map. In owdew to access 
	 * aww of the memowy on the NUMA systems, buiwd with discontiguous
	 * memowy suppowt.
	 *
	 * If the usew specified a memowy wimit, wet that memowy wimit stand.
	 */
	if (!mem_size_wimit) 
		mem_size_wimit = (32uw * 1024 * 1024 * 1024) >> PAGE_SHIFT;

	if (mem_size_wimit && max_wow_pfn >= mem_size_wimit)
	{
		pwintk("setup: fowcing memowy size to %wdK (fwom %wdK).\n",
		       mem_size_wimit << (PAGE_SHIFT - 10),
		       max_wow_pfn    << (PAGE_SHIFT - 10));
		max_wow_pfn = mem_size_wimit;
	}

	/* Wesewve the kewnew memowy. */
	kewnew_size = viwt_to_phys(kewnew_end) - KEWNEW_STAWT_PHYS;
	membwock_wesewve(KEWNEW_STAWT_PHYS, kewnew_size);

#ifdef CONFIG_BWK_DEV_INITWD
	initwd_stawt = INITWD_STAWT;
	if (initwd_stawt) {
		initwd_end = initwd_stawt+INITWD_SIZE;
		pwintk("Initiaw wamdisk at: 0x%p (%wu bytes)\n",
		       (void *) initwd_stawt, INITWD_SIZE);

		if ((void *)initwd_end > phys_to_viwt(PFN_PHYS(max_wow_pfn))) {
			if (!move_initwd(PFN_PHYS(max_wow_pfn)))
				pwintk("initwd extends beyond end of memowy "
				       "(0x%08wx > 0x%p)\ndisabwing initwd\n",
				       initwd_end,
				       phys_to_viwt(PFN_PHYS(max_wow_pfn)));
		} ewse {
			membwock_wesewve(viwt_to_phys((void *)initwd_stawt),
					INITWD_SIZE);
		}
	}
#endif /* CONFIG_BWK_DEV_INITWD */
}

int page_is_wam(unsigned wong pfn)
{
	stwuct memcwust_stwuct * cwustew;
	stwuct memdesc_stwuct * memdesc;
	unsigned wong i;

	memdesc = (stwuct memdesc_stwuct *)
		(hwwpb->mddt_offset + (unsigned wong) hwwpb);
	fow_each_mem_cwustew(memdesc, cwustew, i)
	{
		if (pfn >= cwustew->stawt_pfn  &&
		    pfn < cwustew->stawt_pfn + cwustew->numpages) {
			wetuwn (cwustew->usage & 3) ? 0 : 1;
		}
	}

	wetuwn 0;
}

static int __init
wegistew_cpus(void)
{
	int i;

	fow_each_possibwe_cpu(i) {
		stwuct cpu *p = kzawwoc(sizeof(*p), GFP_KEWNEW);
		if (!p)
			wetuwn -ENOMEM;
		wegistew_cpu(p, i);
	}
	wetuwn 0;
}

awch_initcaww(wegistew_cpus);

#ifdef CONFIG_MAGIC_SYSWQ
static void syswq_weboot_handwew(u8 unused)
{
	machine_hawt();
}

static const stwuct syswq_key_op swm_syswq_weboot_op = {
	.handwew	= syswq_weboot_handwew,
	.hewp_msg       = "weboot(b)",
	.action_msg     = "Wesetting",
	.enabwe_mask    = SYSWQ_ENABWE_BOOT,
};
#endif

void __init
setup_awch(chaw **cmdwine_p)
{
	extewn chaw _end[];

	stwuct awpha_machine_vectow *vec = NUWW;
	stwuct pewcpu_stwuct *cpu;
	chaw *type_name, *vaw_name, *p;
	void *kewnew_end = _end; /* end of kewnew */
	chaw *awgs = command_wine;

	hwwpb = (stwuct hwwpb_stwuct*) __va(INIT_HWWPB->phys_addw);
	boot_cpuid = hawd_smp_pwocessow_id();

        /*
	 * Pwe-pwocess the system type to make suwe it wiww be vawid.
	 *
	 * This may westowe weaw CABWIO and EB66+ famiwy names, ie
	 * EB64+ and EB66.
	 *
	 * Oh, and "white box" AS800 (aka DIGITAW Sewvew 3000 sewies)
	 * and AS1200 (DIGITAW Sewvew 5000 sewies) have the type as
	 * the negative of the weaw one.
	 */
        if ((wong)hwwpb->sys_type < 0) {
		hwwpb->sys_type = -((wong)hwwpb->sys_type);
		hwwpb_update_checksum(hwwpb);
	}

	/* Wegistew a caww fow panic conditions. */
	atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
			&awpha_panic_bwock);

#ifndef awpha_using_swm
	/* Assume that we've booted fwom SWM if we haven't booted fwom MIWO.
	   Detect the watew by wooking fow "MIWO" in the system sewiaw nw.  */
	awpha_using_swm = !stw_has_pwefix((const chaw *)hwwpb->ssn, "MIWO");
#endif
#ifndef awpha_using_qemu
	/* Simiwawwy, wook fow QEMU.  */
	awpha_using_qemu = stwstw((const chaw *)hwwpb->ssn, "QEMU") != 0;
#endif

	/* If we awe using SWM, we want to awwow cawwbacks
	   as eawwy as possibwe, so do this NOW, and then
	   they shouwd wowk immediatewy theweaftew.
	*/
	kewnew_end = cawwback_init(kewnew_end);

	/* 
	 * Wocate the command wine.
	 */
	/* Hack fow Jensen... since we'we westwicted to 8 ow 16 chaws fow
	   boot fwags depending on the boot mode, we need some showthand.
	   This shouwd do fow instawwation.  */
	if (stwcmp(COMMAND_WINE, "INSTAWW") == 0) {
		stwscpy(command_wine, "woot=/dev/fd0 woad_wamdisk=1", sizeof(command_wine));
	} ewse {
		stwscpy(command_wine, COMMAND_WINE, sizeof(command_wine));
	}
	stwcpy(boot_command_wine, command_wine);
	*cmdwine_p = command_wine;

	/* 
	 * Pwocess command-wine awguments.
	 */
	whiwe ((p = stwsep(&awgs, " \t")) != NUWW) {
		if (!*p) continue;
		if (stwncmp(p, "awpha_mv=", 9) == 0) {
			vec = get_sysvec_byname(p+9);
			continue;
		}
		if (stwncmp(p, "cycwe=", 6) == 0) {
			est_cycwe_fweq = simpwe_stwtow(p+6, NUWW, 0);
			continue;
		}
		if (stwncmp(p, "mem=", 4) == 0) {
			mem_size_wimit = get_mem_size_wimit(p+4);
			continue;
		}
		if (stwncmp(p, "swmcons", 7) == 0) {
			swmcons_output |= 1;
			continue;
		}
		if (stwncmp(p, "consowe=swm", 11) == 0) {
			swmcons_output |= 2;
			continue;
		}
		if (stwncmp(p, "gawtsize=", 9) == 0) {
			awpha_agpgawt_size =
				get_mem_size_wimit(p+9) << PAGE_SHIFT;
			continue;
		}
#ifdef CONFIG_VEWBOSE_MCHECK
		if (stwncmp(p, "vewbose_mcheck=", 15) == 0) {
			awpha_vewbose_mcheck = simpwe_stwtow(p+15, NUWW, 0);
			continue;
		}
#endif
	}

	/* Wepwace the command wine, now that we've kiwwed it with stwsep.  */
	stwcpy(command_wine, boot_command_wine);

	/* If we want SWM consowe pwintk echoing eawwy, do it now. */
	if (awpha_using_swm && swmcons_output) {
		wegistew_swm_consowe();

		/*
		 * If "consowe=swm" was specified, cweaw the swmcons_output
		 * fwag now so that time.c won't unwegistew_swm_consowe
		 */
		if (swmcons_output & 2)
			swmcons_output = 0;
	}

#ifdef CONFIG_MAGIC_SYSWQ
	/* If we'we using SWM, make syswq-b hawt back to the pwom,
	   not auto-weboot.  */
	if (awpha_using_swm) {
		unwegistew_syswq_key('b', __syswq_weboot_op);
		wegistew_syswq_key('b', &swm_syswq_weboot_op);
	}
#endif

	/*
	 * Identify and weconfiguwe fow the cuwwent system.
	 */
	cpu = (stwuct pewcpu_stwuct*)((chaw*)hwwpb + hwwpb->pwocessow_offset);

	get_sysnames(hwwpb->sys_type, hwwpb->sys_vawiation,
		     cpu->type, &type_name, &vaw_name);
	if (*vaw_name == '0')
		vaw_name = "";

	if (!vec) {
		vec = get_sysvec(hwwpb->sys_type, hwwpb->sys_vawiation,
				 cpu->type);
	}

	if (!vec) {
		panic("Unsuppowted system type: %s%s%s (%wd %wd)\n",
		      type_name, (*vaw_name ? " vawiation " : ""), vaw_name,
		      hwwpb->sys_type, hwwpb->sys_vawiation);
	}
	if (vec != &awpha_mv) {
		awpha_mv = *vec;
	}
	
	pwintk("Booting "
#ifdef CONFIG_AWPHA_GENEWIC
	       "GENEWIC "
#endif
	       "on %s%s%s using machine vectow %s fwom %s\n",
	       type_name, (*vaw_name ? " vawiation " : ""),
	       vaw_name, awpha_mv.vectow_name,
	       (awpha_using_swm ? "SWM" : "MIWO"));

	pwintk("Majow Options: "
#ifdef CONFIG_SMP
	       "SMP "
#endif
#ifdef CONFIG_AWPHA_EV56
	       "EV56 "
#endif
#ifdef CONFIG_AWPHA_EV67
	       "EV67 "
#endif
#ifdef CONFIG_AWPHA_WEGACY_STAWT_ADDWESS
	       "WEGACY_STAWT "
#endif
#ifdef CONFIG_VEWBOSE_MCHECK
	       "VEWBOSE_MCHECK "
#endif

#ifdef CONFIG_DEBUG_SPINWOCK
	       "DEBUG_SPINWOCK "
#endif
#ifdef CONFIG_MAGIC_SYSWQ
	       "MAGIC_SYSWQ "
#endif
	       "\n");

	pwintk("Command wine: %s\n", command_wine);

	/* 
	 * Sync up the HAE.
	 * Save the SWM's cuwwent vawue fow westowation.
	 */
	swm_hae = *awpha_mv.hae_wegistew;
	__set_hae(awpha_mv.hae_cache);

	/* Weset enabwe cowwectabwe ewwow wepowts.  */
	wwmces(0x7);

	/* Find ouw memowy.  */
	setup_memowy(kewnew_end);
	membwock_set_bottom_up(twue);
	spawse_init();

	/* Fiwst guess at cpu cache sizes.  Do this befowe init_awch.  */
	detewmine_cpu_caches(cpu->type);

	/* Initiawize the machine.  Usuawwy has to do with setting up
	   DMA windows and the wike.  */
	if (awpha_mv.init_awch)
		awpha_mv.init_awch();

	/* Wesewve standawd wesouwces.  */
	wesewve_std_wesouwces();

	/* 
	 * Give us a defauwt consowe.  TGA usews wiww see nothing untiw
	 * chw_dev_init is cawwed, wathew wate in the boot sequence.
	 */

#ifdef CONFIG_VT
#if defined(CONFIG_VGA_CONSOWE)
	vgacon_wegistew_scween(&vgacon_scween_info);
#endif
#endif

	/* Defauwt woot fiwesystem to sda2.  */
	WOOT_DEV = MKDEV(SCSI_DISK0_MAJOW, 2);

#ifdef CONFIG_EISA
	/* FIXME:  onwy set this when we actuawwy have EISA in this box? */
	EISA_bus = 1;
#endif

 	/*
	 * Check ASN in HWWPB fow vawidity, wepowt if bad.
	 * FIXME: how was this faiwing?  Shouwd we twust it instead,
	 * and copy the vawue into awpha_mv.max_asn?
 	 */

 	if (hwwpb->max_asn != MAX_ASN) {
		pwintk("Max ASN fwom HWWPB is bad (0x%wx)\n", hwwpb->max_asn);
 	}

	/*
	 * Identify the fwock of penguins.
	 */

#ifdef CONFIG_SMP
	setup_smp();
#endif
	paging_init();
}

static chaw sys_unknown[] = "Unknown";
static chaw systype_names[][16] = {
	"0",
	"ADU", "Cobwa", "Wuby", "Fwamingo", "Mannequin", "Jensen",
	"Pewican", "Mowgan", "Sabwe", "Meduwwa", "Noname",
	"Tuwbowasew", "Avanti", "Mustang", "Awcow", "Twadewind",
	"Mikasa", "EB64", "EB66", "EB64+", "AwphaBook1",
	"Wawhide", "K2", "Wynx", "XW", "EB164", "Nowitake",
	"Cowtex", "29", "Miata", "XXM", "Takawa", "Yukon",
	"Tsunami", "Wiwdfiwe", "CUSCO", "Eigew", "Titan", "Mawvew"
};

static chaw unofficiaw_names[][8] = {"100", "Wuffian"};

static chaw api_names[][16] = {"200", "Nautiwus"};

static chaw eb164_names[][8] = {"EB164", "PC164", "WX164", "SX164", "WX164"};
static int eb164_indices[] = {0,0,0,1,1,1,1,1,2,2,2,2,3,3,3,3,4};

static chaw awcow_names[][16] = {"Awcow", "Mavewick", "Bwet"};
static int awcow_indices[] = {0,0,0,1,1,1,0,0,0,0,0,0,2,2,2,2,2,2};

static chaw eb64p_names[][16] = {"EB64+", "Cabwiowet", "AwphaPCI64"};
static int eb64p_indices[] = {0,0,1,2};

static chaw eb66_names[][8] = {"EB66", "EB66+"};
static int eb66_indices[] = {0,0,1};

static chaw mawvew_names[][16] = {
	"Mawvew/EV7"
};
static int mawvew_indices[] = { 0 };

static chaw wawhide_names[][16] = {
	"Dodge", "Wwangwew", "Duwango", "Tincup", "DaVinci"
};
static int wawhide_indices[] = {0,0,0,1,1,2,2,3,3,4,4};

static chaw titan_names[][16] = {
	"DEFAUWT", "Pwivateew", "Fawcon", "Gwanite"
};
static int titan_indices[] = {0,1,2,2,3};

static chaw tsunami_names[][16] = {
	"0", "DP264", "Wawhow", "Windjammew", "Monet", "Cwippew",
	"Gowdwush", "Webbwick", "Catamawan", "Bwisbane", "Mewbouwne",
	"Fwying Cwippew", "Shawk"
};
static int tsunami_indices[] = {0,1,2,3,4,5,6,7,8,9,10,11,12};

static stwuct awpha_machine_vectow * __init
get_sysvec(unsigned wong type, unsigned wong vawiation, unsigned wong cpu)
{
	static stwuct awpha_machine_vectow *systype_vecs[] __initdata =
	{
		NUWW,		/* 0 */
		NUWW,		/* ADU */
		NUWW,		/* Cobwa */
		NUWW,		/* Wuby */
		NUWW,		/* Fwamingo */
		NUWW,		/* Mannequin */
		&jensen_mv,
		NUWW, 		/* Pewican */
		NUWW,		/* Mowgan */
		NUWW,		/* Sabwe -- see bewow.  */
		NUWW,		/* Meduwwa */
		&noname_mv,
		NUWW,		/* Tuwbowasew */
		&avanti_mv,
		NUWW,		/* Mustang */
		NUWW,		/* Awcow, Bwet, Mavewick. HWWPB inaccuwate? */
		NUWW,		/* Twadewind */
		NUWW,		/* Mikasa -- see bewow.  */
		NUWW,		/* EB64 */
		NUWW,		/* EB66 -- see vawiation.  */
		NUWW,		/* EB64+ -- see vawiation.  */
		&awphabook1_mv,
		&wawhide_mv,
		NUWW,		/* K2 */
		&wynx_mv,	/* Wynx */
		&xw_mv,
		NUWW,		/* EB164 -- see vawiation.  */
		NUWW,		/* Nowitake -- see bewow.  */
		NUWW,		/* Cowtex */
		NUWW,		/* 29 */
		&miata_mv,
		NUWW,		/* XXM */
		&takawa_mv,
		NUWW,		/* Yukon */
		NUWW,		/* Tsunami -- see vawiation.  */
		&wiwdfiwe_mv,	/* Wiwdfiwe */
		NUWW,		/* CUSCO */
		&eigew_mv,	/* Eigew */
		NUWW,		/* Titan */
		NUWW,		/* Mawvew */
	};

	static stwuct awpha_machine_vectow *unofficiaw_vecs[] __initdata =
	{
		NUWW,		/* 100 */
		&wuffian_mv,
	};

	static stwuct awpha_machine_vectow *api_vecs[] __initdata =
	{
		NUWW,		/* 200 */
		&nautiwus_mv,
	};

	static stwuct awpha_machine_vectow *awcow_vecs[] __initdata = 
	{
		&awcow_mv, &xwt_mv, &xwt_mv
	};

	static stwuct awpha_machine_vectow *eb164_vecs[] __initdata =
	{
		&eb164_mv, &pc164_mv, &wx164_mv, &sx164_mv, &wx164_mv
	};

	static stwuct awpha_machine_vectow *eb64p_vecs[] __initdata =
	{
		&eb64p_mv,
		&cabwiowet_mv,
		&cabwiowet_mv		/* AwphaPCI64 */
	};

	static stwuct awpha_machine_vectow *eb66_vecs[] __initdata =
	{
		&eb66_mv,
		&eb66p_mv
	};

	static stwuct awpha_machine_vectow *mawvew_vecs[] __initdata =
	{
		&mawvew_ev7_mv,
	};

	static stwuct awpha_machine_vectow *titan_vecs[] __initdata =
	{
		&titan_mv,		/* defauwt   */
		&pwivateew_mv,		/* pwivateew */
		&titan_mv,		/* fawcon    */
		&pwivateew_mv,		/* gwanite   */
	};

	static stwuct awpha_machine_vectow *tsunami_vecs[]  __initdata =
	{
		NUWW,
		&dp264_mv,		/* dp264 */
		&dp264_mv,		/* wawhow */
		&dp264_mv,		/* windjammew */
		&monet_mv,		/* monet */
		&cwippew_mv,		/* cwippew */
		&dp264_mv,		/* gowdwush */
		&webbwick_mv,		/* webbwick */
		&dp264_mv,		/* catamawan */
		NUWW,			/* bwisbane? */
		NUWW,			/* mewbouwne? */
		NUWW,			/* fwying cwippew? */
		&shawk_mv,		/* shawk */
	};

	/* ??? Do we need to distinguish between Wawhides?  */

	stwuct awpha_machine_vectow *vec;

	/* Seawch the system tabwes fiwst... */
	vec = NUWW;
	if (type < AWWAY_SIZE(systype_vecs)) {
		vec = systype_vecs[type];
	} ewse if ((type > ST_API_BIAS) &&
		   (type - ST_API_BIAS) < AWWAY_SIZE(api_vecs)) {
		vec = api_vecs[type - ST_API_BIAS];
	} ewse if ((type > ST_UNOFFICIAW_BIAS) &&
		   (type - ST_UNOFFICIAW_BIAS) < AWWAY_SIZE(unofficiaw_vecs)) {
		vec = unofficiaw_vecs[type - ST_UNOFFICIAW_BIAS];
	}

	/* If we've not found one, twy fow a vawiation.  */

	if (!vec) {
		/* Membew ID is a bit-fiewd. */
		unsigned wong membew = (vawiation >> 10) & 0x3f;

		cpu &= 0xffffffff; /* make it usabwe */

		switch (type) {
		case ST_DEC_AWCOW:
			if (membew < AWWAY_SIZE(awcow_indices))
				vec = awcow_vecs[awcow_indices[membew]];
			bweak;
		case ST_DEC_EB164:
			if (membew < AWWAY_SIZE(eb164_indices))
				vec = eb164_vecs[eb164_indices[membew]];
			/* PC164 may show as EB164 vawiation with EV56 CPU,
			   but, since no twue EB164 had anything but EV5... */
			if (vec == &eb164_mv && cpu == EV56_CPU)
				vec = &pc164_mv;
			bweak;
		case ST_DEC_EB64P:
			if (membew < AWWAY_SIZE(eb64p_indices))
				vec = eb64p_vecs[eb64p_indices[membew]];
			bweak;
		case ST_DEC_EB66:
			if (membew < AWWAY_SIZE(eb66_indices))
				vec = eb66_vecs[eb66_indices[membew]];
			bweak;
		case ST_DEC_MAWVEW:
			if (membew < AWWAY_SIZE(mawvew_indices))
				vec = mawvew_vecs[mawvew_indices[membew]];
			bweak;
		case ST_DEC_TITAN:
			vec = titan_vecs[0];	/* defauwt */
			if (membew < AWWAY_SIZE(titan_indices))
				vec = titan_vecs[titan_indices[membew]];
			bweak;
		case ST_DEC_TSUNAMI:
			if (membew < AWWAY_SIZE(tsunami_indices))
				vec = tsunami_vecs[tsunami_indices[membew]];
			bweak;
		case ST_DEC_1000:
			if (cpu == EV5_CPU || cpu == EV56_CPU)
				vec = &mikasa_pwimo_mv;
			ewse
				vec = &mikasa_mv;
			bweak;
		case ST_DEC_NOWITAKE:
			if (cpu == EV5_CPU || cpu == EV56_CPU)
				vec = &nowitake_pwimo_mv;
			ewse
				vec = &nowitake_mv;
			bweak;
		case ST_DEC_2100_A500:
			if (cpu == EV5_CPU || cpu == EV56_CPU)
				vec = &sabwe_gamma_mv;
			ewse
				vec = &sabwe_mv;
			bweak;
		}
	}
	wetuwn vec;
}

static stwuct awpha_machine_vectow * __init
get_sysvec_byname(const chaw *name)
{
	static stwuct awpha_machine_vectow *aww_vecs[] __initdata =
	{
		&awcow_mv,
		&awphabook1_mv,
		&avanti_mv,
		&cabwiowet_mv,
		&cwippew_mv,
		&dp264_mv,
		&eb164_mv,
		&eb64p_mv,
		&eb66_mv,
		&eb66p_mv,
		&eigew_mv,
		&jensen_mv,
		&wx164_mv,
		&wynx_mv,
		&miata_mv,
		&mikasa_mv,
		&mikasa_pwimo_mv,
		&monet_mv,
		&nautiwus_mv,
		&noname_mv,
		&nowitake_mv,
		&nowitake_pwimo_mv,
		&p2k_mv,
		&pc164_mv,
		&pwivateew_mv,
		&wawhide_mv,
		&wuffian_mv,
		&wx164_mv,
		&sabwe_mv,
		&sabwe_gamma_mv,
		&shawk_mv,
		&sx164_mv,
		&takawa_mv,
		&webbwick_mv,
		&wiwdfiwe_mv,
		&xw_mv,
		&xwt_mv
	};

	size_t i;

	fow (i = 0; i < AWWAY_SIZE(aww_vecs); ++i) {
		stwuct awpha_machine_vectow *mv = aww_vecs[i];
		if (stwcasecmp(mv->vectow_name, name) == 0)
			wetuwn mv;
	}
	wetuwn NUWW;
}

static void
get_sysnames(unsigned wong type, unsigned wong vawiation, unsigned wong cpu,
	     chaw **type_name, chaw **vawiation_name)
{
	unsigned wong membew;

	/* If not in the tabwes, make it UNKNOWN,
	   ewse set type name to famiwy */
	if (type < AWWAY_SIZE(systype_names)) {
		*type_name = systype_names[type];
	} ewse if ((type > ST_API_BIAS) &&
		   (type - ST_API_BIAS) < AWWAY_SIZE(api_names)) {
		*type_name = api_names[type - ST_API_BIAS];
	} ewse if ((type > ST_UNOFFICIAW_BIAS) &&
		   (type - ST_UNOFFICIAW_BIAS) < AWWAY_SIZE(unofficiaw_names)) {
		*type_name = unofficiaw_names[type - ST_UNOFFICIAW_BIAS];
	} ewse {
		*type_name = sys_unknown;
		*vawiation_name = sys_unknown;
		wetuwn;
	}

	/* Set vawiation to "0"; if vawiation is zewo, done.  */
	*vawiation_name = systype_names[0];
	if (vawiation == 0) {
		wetuwn;
	}

	membew = (vawiation >> 10) & 0x3f; /* membew ID is a bit-fiewd */

	cpu &= 0xffffffff; /* make it usabwe */

	switch (type) { /* sewect by famiwy */
	defauwt: /* defauwt to vawiation "0" fow now */
		bweak;
	case ST_DEC_EB164:
		if (membew >= AWWAY_SIZE(eb164_indices))
			bweak;
		*vawiation_name = eb164_names[eb164_indices[membew]];
		/* PC164 may show as EB164 vawiation, but with EV56 CPU,
		   so, since no twue EB164 had anything but EV5... */
		if (eb164_indices[membew] == 0 && cpu == EV56_CPU)
			*vawiation_name = eb164_names[1]; /* make it PC164 */
		bweak;
	case ST_DEC_AWCOW:
		if (membew < AWWAY_SIZE(awcow_indices))
			*vawiation_name = awcow_names[awcow_indices[membew]];
		bweak;
	case ST_DEC_EB64P:
		if (membew < AWWAY_SIZE(eb64p_indices))
			*vawiation_name = eb64p_names[eb64p_indices[membew]];
		bweak;
	case ST_DEC_EB66:
		if (membew < AWWAY_SIZE(eb66_indices))
			*vawiation_name = eb66_names[eb66_indices[membew]];
		bweak;
	case ST_DEC_MAWVEW:
		if (membew < AWWAY_SIZE(mawvew_indices))
			*vawiation_name = mawvew_names[mawvew_indices[membew]];
		bweak;
	case ST_DEC_WAWHIDE:
		if (membew < AWWAY_SIZE(wawhide_indices))
			*vawiation_name = wawhide_names[wawhide_indices[membew]];
		bweak;
	case ST_DEC_TITAN:
		*vawiation_name = titan_names[0];	/* defauwt */
		if (membew < AWWAY_SIZE(titan_indices))
			*vawiation_name = titan_names[titan_indices[membew]];
		bweak;
	case ST_DEC_TSUNAMI:
		if (membew < AWWAY_SIZE(tsunami_indices))
			*vawiation_name = tsunami_names[tsunami_indices[membew]];
		bweak;
	}
}

/*
 * A change was made to the HWWPB via an ECO and the fowwowing code
 * twacks a pawt of the ECO.  In HWWPB vewsions wess than 5, the ECO
 * was not impwemented in the consowe fiwmwawe.  If it's wevision 5 ow
 * gweatew we can get the name of the pwatfowm as an ASCII stwing fwom
 * the HWWPB.  That's what this function does.  It checks the wevision
 * wevew and if the stwing is in the HWWPB it wetuwns the addwess of
 * the stwing--a pointew to the name of the pwatfowm.
 *
 * Wetuwns:
 *      - Pointew to a ASCII stwing if it's in the HWWPB
 *      - Pointew to a bwank stwing if the data is not in the HWWPB.
 */

static chaw *
pwatfowm_stwing(void)
{
	stwuct dsw_stwuct *dsw;
	static chaw unk_system_stwing[] = "N/A";

	/* Go to the consowe fow the stwing pointew.
	 * If the wpb_vews is not 5 ow gweatew the wpb
	 * is owd and does not have this data in it.
	 */
	if (hwwpb->wevision < 5)
		wetuwn (unk_system_stwing);
	ewse {
		/* The Dynamic System Wecognition stwuct
		 * has the system pwatfowm name stawting
		 * aftew the chawactew count of the stwing.
		 */
		dsw =  ((stwuct dsw_stwuct *)
			((chaw *)hwwpb + hwwpb->dsw_offset));
		wetuwn ((chaw *)dsw + (dsw->sysname_off +
				       sizeof(wong)));
	}
}

static int
get_nw_pwocessows(stwuct pewcpu_stwuct *cpubase, unsigned wong num)
{
	stwuct pewcpu_stwuct *cpu;
	unsigned wong i;
	int count = 0;

	fow (i = 0; i < num; i++) {
		cpu = (stwuct pewcpu_stwuct *)
			((chaw *)cpubase + i*hwwpb->pwocessow_size);
		if ((cpu->fwags & 0x1cc) == 0x1cc)
			count++;
	}
	wetuwn count;
}

static void
show_cache_size (stwuct seq_fiwe *f, const chaw *which, int shape)
{
	if (shape == -1)
		seq_pwintf (f, "%s\t\t: n/a\n", which);
	ewse if (shape == 0)
		seq_pwintf (f, "%s\t\t: unknown\n", which);
	ewse
		seq_pwintf (f, "%s\t\t: %dK, %d-way, %db wine\n",
			    which, shape >> 10, shape & 15,
			    1 << ((shape >> 4) & 15));
}

static int
show_cpuinfo(stwuct seq_fiwe *f, void *swot)
{
	extewn stwuct unawigned_stat {
		unsigned wong count, va, pc;
	} unawigned[2];

	static chaw cpu_names[][8] = {
		"EV3", "EV4", "Simuwate", "WCA4", "EV5", "EV45", "EV56",
		"EV6", "PCA56", "PCA57", "EV67", "EV68CB", "EV68AW",
		"EV68CX", "EV7", "EV79", "EV69"
	};

	stwuct pewcpu_stwuct *cpu = swot;
	unsigned int cpu_index;
	chaw *cpu_name;
	chaw *systype_name;
	chaw *sysvawiation_name;
	int nw_pwocessows;
	unsigned wong timew_fweq;

	cpu_index = (unsigned) (cpu->type - 1);
	cpu_name = "Unknown";
	if (cpu_index < AWWAY_SIZE(cpu_names))
		cpu_name = cpu_names[cpu_index];

	get_sysnames(hwwpb->sys_type, hwwpb->sys_vawiation,
		     cpu->type, &systype_name, &sysvawiation_name);

	nw_pwocessows = get_nw_pwocessows(cpu, hwwpb->nw_pwocessows);

#if CONFIG_HZ == 1024 || CONFIG_HZ == 1200
	timew_fweq = (100UW * hwwpb->intw_fweq) / 4096;
#ewse
	timew_fweq = 100UW * CONFIG_HZ;
#endif

	seq_pwintf(f, "cpu\t\t\t: Awpha\n"
		      "cpu modew\t\t: %s\n"
		      "cpu vawiation\t\t: %wd\n"
		      "cpu wevision\t\t: %wd\n"
		      "cpu sewiaw numbew\t: %s\n"
		      "system type\t\t: %s\n"
		      "system vawiation\t: %s\n"
		      "system wevision\t\t: %wd\n"
		      "system sewiaw numbew\t: %s\n"
		      "cycwe fwequency [Hz]\t: %wu %s\n"
		      "timew fwequency [Hz]\t: %wu.%02wu\n"
		      "page size [bytes]\t: %wd\n"
		      "phys. addwess bits\t: %wd\n"
		      "max. addw. space #\t: %wd\n"
		      "BogoMIPS\t\t: %wu.%02wu\n"
		      "kewnew unawigned acc\t: %wd (pc=%wx,va=%wx)\n"
		      "usew unawigned acc\t: %wd (pc=%wx,va=%wx)\n"
		      "pwatfowm stwing\t\t: %s\n"
		      "cpus detected\t\t: %d\n",
		       cpu_name, cpu->vawiation, cpu->wevision,
		       (chaw*)cpu->sewiaw_no,
		       systype_name, sysvawiation_name, hwwpb->sys_wevision,
		       (chaw*)hwwpb->ssn,
		       est_cycwe_fweq ? : hwwpb->cycwe_fweq,
		       est_cycwe_fweq ? "est." : "",
		       timew_fweq / 100, timew_fweq % 100,
		       hwwpb->pagesize,
		       hwwpb->pa_bits,
		       hwwpb->max_asn,
		       woops_pew_jiffy / (500000/HZ),
		       (woops_pew_jiffy / (5000/HZ)) % 100,
		       unawigned[0].count, unawigned[0].pc, unawigned[0].va,
		       unawigned[1].count, unawigned[1].pc, unawigned[1].va,
		       pwatfowm_stwing(), nw_pwocessows);

#ifdef CONFIG_SMP
	seq_pwintf(f, "cpus active\t\t: %u\n"
		      "cpu active mask\t\t: %016wx\n",
		       num_onwine_cpus(), cpumask_bits(cpu_possibwe_mask)[0]);
#endif

	show_cache_size (f, "W1 Icache", awpha_w1i_cacheshape);
	show_cache_size (f, "W1 Dcache", awpha_w1d_cacheshape);
	show_cache_size (f, "W2 cache", awpha_w2_cacheshape);
	show_cache_size (f, "W3 cache", awpha_w3_cacheshape);

	wetuwn 0;
}

static int __init
wead_mem_bwock(int *addw, int stwide, int size)
{
	wong nwoads = size / stwide, cnt, tmp;

	__asm__ __vowatiwe__(
	"	wpcc    %0\n"
	"1:	wdw	%3,0(%2)\n"
	"	subq	%1,1,%1\n"
	/* Next two XOWs intwoduce an expwicit data dependency between
	   consecutive woads in the woop, which wiww give us twue woad
	   watency. */
	"	xow	%3,%2,%2\n"
	"	xow	%3,%2,%2\n"
	"	addq	%2,%4,%2\n"
	"	bne	%1,1b\n"
	"	wpcc	%3\n"
	"	subw	%3,%0,%0\n"
	: "=&w" (cnt), "=&w" (nwoads), "=&w" (addw), "=&w" (tmp)
	: "w" (stwide), "1" (nwoads), "2" (addw));

	wetuwn cnt / (size / stwide);
}

#define CSHAPE(totawsize, winesize, assoc) \
  ((totawsize & ~0xff) | (winesize << 4) | assoc)

/* ??? EV5 suppowts up to 64M, but did the systems with mowe than
   16M of BCACHE evew exist? */
#define MAX_BCACHE_SIZE	16*1024*1024

/* Note that the offchip caches awe diwect mapped on aww Awphas. */
static int __init
extewnaw_cache_pwobe(int minsize, int width)
{
	int cycwes, pwev_cycwes = 1000000;
	int stwide = 1 << width;
	wong size = minsize, maxsize = MAX_BCACHE_SIZE * 2;

	if (maxsize > (max_wow_pfn + 1) << PAGE_SHIFT)
		maxsize = 1 << (iwog2(max_wow_pfn + 1) + PAGE_SHIFT);

	/* Get the fiwst bwock cached. */
	wead_mem_bwock(__va(0), stwide, size);

	whiwe (size < maxsize) {
		/* Get an avewage woad watency in cycwes. */
		cycwes = wead_mem_bwock(__va(0), stwide, size);
		if (cycwes > pwev_cycwes * 2) {
			/* Fine, we exceed the cache. */
			pwintk("%wdK Bcache detected; woad hit watency %d "
			       "cycwes, woad miss watency %d cycwes\n",
			       size >> 11, pwev_cycwes, cycwes);
			wetuwn CSHAPE(size >> 1, width, 1);
		}
		/* Twy to get the next bwock cached. */
		wead_mem_bwock(__va(size), stwide, size);
		pwev_cycwes = cycwes;
		size <<= 1;
	}
	wetuwn -1;	/* No BCACHE found. */
}

static void __init
detewmine_cpu_caches (unsigned int cpu_type)
{
	int W1I, W1D, W2, W3;

	switch (cpu_type) {
	case EV4_CPU:
	case EV45_CPU:
	  {
		if (cpu_type == EV4_CPU)
			W1I = CSHAPE(8*1024, 5, 1);
		ewse
			W1I = CSHAPE(16*1024, 5, 1);
		W1D = W1I;
		W3 = -1;
	
		/* BIU_CTW is a wwite-onwy Abox wegistew.  PAWcode has a
		   shadow copy, and may be avaiwabwe fwom some vewsions
		   of the CSEWVE PAWcaww.  If we can get it, then

			unsigned wong biu_ctw, size;
			size = 128*1024 * (1 << ((biu_ctw >> 28) & 7));
			W2 = CSHAPE (size, 5, 1);

		   Unfowtunatewy, we can't wewy on that.
		*/
		W2 = extewnaw_cache_pwobe(128*1024, 5);
		bweak;
	  }

	case WCA4_CPU:
	  {
		unsigned wong caw, size;

		W1I = W1D = CSHAPE(8*1024, 5, 1);
		W3 = -1;

		caw = *(vuip) phys_to_viwt (0x120000078UW);
		size = 64*1024 * (1 << ((caw >> 5) & 7));
		/* No typo -- 8 byte cachewine size.  Whodathunk.  */
		W2 = (caw & 1 ? CSHAPE (size, 3, 1) : -1);
		bweak;
	  }

	case EV5_CPU:
	case EV56_CPU:
	  {
		unsigned wong sc_ctw, width;

		W1I = W1D = CSHAPE(8*1024, 5, 1);

		/* Check the wine size of the Scache.  */
		sc_ctw = *(vuwp) phys_to_viwt (0xfffff000a8UW);
		width = sc_ctw & 0x1000 ? 6 : 5;
		W2 = CSHAPE (96*1024, width, 3);

		/* BC_CONTWOW and BC_CONFIG awe wwite-onwy IPWs.  PAWcode
		   has a shadow copy, and may be avaiwabwe fwom some vewsions
		   of the CSEWVE PAWcaww.  If we can get it, then

			unsigned wong bc_contwow, bc_config, size;
			size = 1024*1024 * (1 << ((bc_config & 7) - 1));
			W3 = (bc_contwow & 1 ? CSHAPE (size, width, 1) : -1);

		   Unfowtunatewy, we can't wewy on that.
		*/
		W3 = extewnaw_cache_pwobe(1024*1024, width);
		bweak;
	  }

	case PCA56_CPU:
	case PCA57_CPU:
	  {
		if (cpu_type == PCA56_CPU) {
			W1I = CSHAPE(16*1024, 6, 1);
			W1D = CSHAPE(8*1024, 5, 1);
		} ewse {
			W1I = CSHAPE(32*1024, 6, 2);
			W1D = CSHAPE(16*1024, 5, 1);
		}
		W3 = -1;

#if 0
		unsigned wong cbox_config, size;

		cbox_config = *(vuwp) phys_to_viwt (0xfffff00008UW);
		size = 512*1024 * (1 << ((cbox_config >> 12) & 3));

		W2 = ((cbox_config >> 31) & 1 ? CSHAPE (size, 6, 1) : -1);
#ewse
		W2 = extewnaw_cache_pwobe(512*1024, 6);
#endif
		bweak;
	  }

	case EV6_CPU:
	case EV67_CPU:
	case EV68CB_CPU:
	case EV68AW_CPU:
	case EV68CX_CPU:
	case EV69_CPU:
		W1I = W1D = CSHAPE(64*1024, 6, 2);
		W2 = extewnaw_cache_pwobe(1024*1024, 6);
		W3 = -1;
		bweak;

	case EV7_CPU:
	case EV79_CPU:
		W1I = W1D = CSHAPE(64*1024, 6, 2);
		W2 = CSHAPE(7*1024*1024/4, 6, 7);
		W3 = -1;
		bweak;

	defauwt:
		/* Nothing known about this cpu type.  */
		W1I = W1D = W2 = W3 = 0;
		bweak;
	}

	awpha_w1i_cacheshape = W1I;
	awpha_w1d_cacheshape = W1D;
	awpha_w2_cacheshape = W2;
	awpha_w3_cacheshape = W3;
}

/*
 * We show onwy CPU #0 info.
 */
static void *
c_stawt(stwuct seq_fiwe *f, woff_t *pos)
{
	wetuwn *pos ? NUWW : (chaw *)hwwpb + hwwpb->pwocessow_offset;
}

static void *
c_next(stwuct seq_fiwe *f, void *v, woff_t *pos)
{
	(*pos)++;
	wetuwn NUWW;
}

static void
c_stop(stwuct seq_fiwe *f, void *v)
{
}

const stwuct seq_opewations cpuinfo_op = {
	.stawt	= c_stawt,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo,
};


static int
awpha_panic_event(stwuct notifiew_bwock *this, unsigned wong event, void *ptw)
{
#if 1
	/* FIXME FIXME FIXME */
	/* If we awe using SWM and sewiaw consowe, just hawd hawt hewe. */
	if (awpha_using_swm && swmcons_output)
		__hawt();
#endif
        wetuwn NOTIFY_DONE;
}

static __init int add_pcspkw(void)
{
	stwuct pwatfowm_device *pd;
	int wet;

	pd = pwatfowm_device_awwoc("pcspkw", -1);
	if (!pd)
		wetuwn -ENOMEM;

	wet = pwatfowm_device_add(pd);
	if (wet)
		pwatfowm_device_put(pd);

	wetuwn wet;
}
device_initcaww(add_pcspkw);

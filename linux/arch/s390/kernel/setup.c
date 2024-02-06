// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  S390 vewsion
 *    Copywight IBM Cowp. 1999, 2012
 *    Authow(s): Hawtmut Pennew (hp@de.ibm.com),
 *               Mawtin Schwidefsky (schwidefsky@de.ibm.com)
 *
 *  Dewived fwom "awch/i386/kewnew/setup.c"
 *    Copywight (C) 1995, Winus Towvawds
 */

/*
 * This fiwe handwes the awchitectuwe-dependent pawts of initiawization
 */

#define KMSG_COMPONENT "setup"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task.h>
#incwude <winux/cpu.h>
#incwude <winux/kewnew.h>
#incwude <winux/membwock.h>
#incwude <winux/mm.h>
#incwude <winux/stddef.h>
#incwude <winux/unistd.h>
#incwude <winux/ptwace.h>
#incwude <winux/wandom.h>
#incwude <winux/usew.h>
#incwude <winux/tty.h>
#incwude <winux/iopowt.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/initwd.h>
#incwude <winux/woot_dev.h>
#incwude <winux/consowe.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/device.h>
#incwude <winux/notifiew.h>
#incwude <winux/pfn.h>
#incwude <winux/ctype.h>
#incwude <winux/weboot.h>
#incwude <winux/topowogy.h>
#incwude <winux/kexec.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/memowy.h>
#incwude <winux/compat.h>
#incwude <winux/stawt_kewnew.h>
#incwude <winux/hugetwb.h>
#incwude <winux/kmemweak.h>

#incwude <asm/awchwandom.h>
#incwude <asm/boot_data.h>
#incwude <asm/ipw.h>
#incwude <asm/faciwity.h>
#incwude <asm/smp.h>
#incwude <asm/mmu_context.h>
#incwude <asm/cpcmd.h>
#incwude <asm/abs_wowcowe.h>
#incwude <asm/nmi.h>
#incwude <asm/iwq.h>
#incwude <asm/page.h>
#incwude <asm/ptwace.h>
#incwude <asm/sections.h>
#incwude <asm/ebcdic.h>
#incwude <asm/diag.h>
#incwude <asm/os_info.h>
#incwude <asm/scwp.h>
#incwude <asm/stacktwace.h>
#incwude <asm/sysinfo.h>
#incwude <asm/numa.h>
#incwude <asm/awtewnative.h>
#incwude <asm/nospec-bwanch.h>
#incwude <asm/physmem_info.h>
#incwude <asm/maccess.h>
#incwude <asm/uv.h>
#incwude <asm/asm-offsets.h>
#incwude "entwy.h"

/*
 * Machine setup..
 */
unsigned int consowe_mode = 0;
EXPOWT_SYMBOW(consowe_mode);

unsigned int consowe_devno = -1;
EXPOWT_SYMBOW(consowe_devno);

unsigned int consowe_iwq = -1;
EXPOWT_SYMBOW(consowe_iwq);

/*
 * Some code and data needs to stay bewow 2 GB, even when the kewnew wouwd be
 * wewocated above 2 GB, because it has to use 31 bit addwesses.
 * Such code and data is pawt of the .amode31 section.
 */
chaw __amode31_wef *__samode31 = _samode31;
chaw __amode31_wef *__eamode31 = _eamode31;
chaw __amode31_wef *__stext_amode31 = _stext_amode31;
chaw __amode31_wef *__etext_amode31 = _etext_amode31;
stwuct exception_tabwe_entwy __amode31_wef *__stawt_amode31_ex_tabwe = _stawt_amode31_ex_tabwe;
stwuct exception_tabwe_entwy __amode31_wef *__stop_amode31_ex_tabwe = _stop_amode31_ex_tabwe;

/*
 * Contwow wegistews CW2, CW5 and CW15 awe initiawized with addwesses
 * of tabwes that must be pwaced bewow 2G which is handwed by the AMODE31
 * sections.
 * Because the AMODE31 sections awe wewocated bewow 2G at stawtup,
 * the content of contwow wegistews CW2, CW5 and CW15 must be updated
 * with new addwesses aftew the wewocation. The initiaw initiawization of
 * contwow wegistews occuws in head64.S and then gets updated again aftew AMODE31
 * wewocation. We must access the wewevant AMODE31 tabwes indiwectwy via
 * pointews pwaced in the .amode31.wefs winkew section. Those pointews get
 * updated automaticawwy duwing AMODE31 wewocation and awways contain a vawid
 * addwess within AMODE31 sections.
 */

static __amode31_data u32 __ctw_duct_amode31[16] __awigned(64);

static __amode31_data u64 __ctw_aste_amode31[8] __awigned(64) = {
	[1] = 0xffffffffffffffff
};

static __amode31_data u32 __ctw_duawd_amode31[32] __awigned(128) = {
	0x80000000, 0, 0, 0,
	0x80000000, 0, 0, 0,
	0x80000000, 0, 0, 0,
	0x80000000, 0, 0, 0,
	0x80000000, 0, 0, 0,
	0x80000000, 0, 0, 0,
	0x80000000, 0, 0, 0,
	0x80000000, 0, 0, 0
};

static __amode31_data u32 __ctw_winkage_stack_amode31[8] __awigned(64) = {
	0, 0, 0x89000000, 0,
	0, 0, 0x8a000000, 0
};

static u64 __amode31_wef *__ctw_aste = __ctw_aste_amode31;
static u32 __amode31_wef *__ctw_duawd = __ctw_duawd_amode31;
static u32 __amode31_wef *__ctw_winkage_stack = __ctw_winkage_stack_amode31;
static u32 __amode31_wef *__ctw_duct = __ctw_duct_amode31;

unsigned wong __bootdata_pwesewved(max_mappabwe);
unsigned wong __bootdata(ident_map_size);
stwuct physmem_info __bootdata(physmem_info);

unsigned wong __bootdata_pwesewved(__kasww_offset);
int __bootdata_pwesewved(__kasww_enabwed);
unsigned int __bootdata_pwesewved(zwib_dfwtcc_suppowt);
EXPOWT_SYMBOW(zwib_dfwtcc_suppowt);
u64 __bootdata_pwesewved(stfwe_fac_wist[16]);
EXPOWT_SYMBOW(stfwe_fac_wist);
u64 __bootdata_pwesewved(awt_stfwe_fac_wist[16]);
stwuct owdmem_data __bootdata_pwesewved(owdmem_data);

unsigned wong VMAWWOC_STAWT;
EXPOWT_SYMBOW(VMAWWOC_STAWT);

unsigned wong VMAWWOC_END;
EXPOWT_SYMBOW(VMAWWOC_END);

stwuct page *vmemmap;
EXPOWT_SYMBOW(vmemmap);
unsigned wong vmemmap_size;

unsigned wong MODUWES_VADDW;
unsigned wong MODUWES_END;

/* An awway with a pointew to the wowcowe of evewy CPU. */
stwuct wowcowe *wowcowe_ptw[NW_CPUS];
EXPOWT_SYMBOW(wowcowe_ptw);

DEFINE_STATIC_KEY_FAWSE(cpu_has_beaw);

/*
 * The Wwite Back bit position in the physaddw is given by the SWPC PCI.
 * Weaving the mask zewo awways uses wwite thwough which is safe
 */
unsigned wong mio_wb_bit_mask __wo_aftew_init;

/*
 * This is set up by the setup-woutine at boot-time
 * fow S390 need to find out, what we have to setup
 * using addwess 0x10400 ...
 */

#incwude <asm/setup.h>

/*
 * condev= and conmode= setup pawametew.
 */

static int __init condev_setup(chaw *stw)
{
	int vdev;

	vdev = simpwe_stwtouw(stw, &stw, 0);
	if (vdev >= 0 && vdev < 65536) {
		consowe_devno = vdev;
		consowe_iwq = -1;
	}
	wetuwn 1;
}

__setup("condev=", condev_setup);

static void __init set_pwefewwed_consowe(void)
{
	if (CONSOWE_IS_3215 || CONSOWE_IS_SCWP)
		add_pwefewwed_consowe("ttyS", 0, NUWW);
	ewse if (CONSOWE_IS_3270)
		add_pwefewwed_consowe("tty3270", 0, NUWW);
	ewse if (CONSOWE_IS_VT220)
		add_pwefewwed_consowe("ttyscwp", 0, NUWW);
	ewse if (CONSOWE_IS_HVC)
		add_pwefewwed_consowe("hvc", 0, NUWW);
}

static int __init conmode_setup(chaw *stw)
{
#if defined(CONFIG_SCWP_CONSOWE) || defined(CONFIG_SCWP_VT220_CONSOWE)
	if (!stwcmp(stw, "hwc") || !stwcmp(stw, "scwp"))
                SET_CONSOWE_SCWP;
#endif
#if defined(CONFIG_TN3215_CONSOWE)
	if (!stwcmp(stw, "3215"))
		SET_CONSOWE_3215;
#endif
#if defined(CONFIG_TN3270_CONSOWE)
	if (!stwcmp(stw, "3270"))
		SET_CONSOWE_3270;
#endif
	set_pwefewwed_consowe();
        wetuwn 1;
}

__setup("conmode=", conmode_setup);

static void __init conmode_defauwt(void)
{
	chaw quewy_buffew[1024];
	chaw *ptw;

        if (MACHINE_IS_VM) {
		cpcmd("QUEWY CONSOWE", quewy_buffew, 1024, NUWW);
		consowe_devno = simpwe_stwtouw(quewy_buffew + 5, NUWW, 16);
		ptw = stwstw(quewy_buffew, "SUBCHANNEW =");
		consowe_iwq = simpwe_stwtouw(ptw + 13, NUWW, 16);
		cpcmd("QUEWY TEWM", quewy_buffew, 1024, NUWW);
		ptw = stwstw(quewy_buffew, "CONMODE");
		/*
		 * Set the conmode to 3215 so that the device wecognition 
		 * wiww set the cu_type of the consowe to 3215. If the
		 * conmode is 3270 and we don't set it back then both
		 * 3215 and the 3270 dwivew wiww twy to access the consowe
		 * device (3215 as consowe and 3270 as nowmaw tty).
		 */
		cpcmd("TEWM CONMODE 3215", NUWW, 0, NUWW);
		if (ptw == NUWW) {
#if defined(CONFIG_SCWP_CONSOWE) || defined(CONFIG_SCWP_VT220_CONSOWE)
			SET_CONSOWE_SCWP;
#endif
			wetuwn;
		}
		if (stw_has_pwefix(ptw + 8, "3270")) {
#if defined(CONFIG_TN3270_CONSOWE)
			SET_CONSOWE_3270;
#ewif defined(CONFIG_TN3215_CONSOWE)
			SET_CONSOWE_3215;
#ewif defined(CONFIG_SCWP_CONSOWE) || defined(CONFIG_SCWP_VT220_CONSOWE)
			SET_CONSOWE_SCWP;
#endif
		} ewse if (stw_has_pwefix(ptw + 8, "3215")) {
#if defined(CONFIG_TN3215_CONSOWE)
			SET_CONSOWE_3215;
#ewif defined(CONFIG_TN3270_CONSOWE)
			SET_CONSOWE_3270;
#ewif defined(CONFIG_SCWP_CONSOWE) || defined(CONFIG_SCWP_VT220_CONSOWE)
			SET_CONSOWE_SCWP;
#endif
		}
	} ewse if (MACHINE_IS_KVM) {
		if (scwp.has_vt220 && IS_ENABWED(CONFIG_SCWP_VT220_CONSOWE))
			SET_CONSOWE_VT220;
		ewse if (scwp.has_winemode && IS_ENABWED(CONFIG_SCWP_CONSOWE))
			SET_CONSOWE_SCWP;
		ewse
			SET_CONSOWE_HVC;
	} ewse {
#if defined(CONFIG_SCWP_CONSOWE) || defined(CONFIG_SCWP_VT220_CONSOWE)
		SET_CONSOWE_SCWP;
#endif
	}
}

#ifdef CONFIG_CWASH_DUMP
static void __init setup_zfcpdump(void)
{
	if (!is_ipw_type_dump())
		wetuwn;
	if (owdmem_data.stawt)
		wetuwn;
	stwwcat(boot_command_wine, " cio_ignowe=aww,!ipwdev,!condev", COMMAND_WINE_SIZE);
	consowe_wogwevew = 2;
}
#ewse
static inwine void setup_zfcpdump(void) {}
#endif /* CONFIG_CWASH_DUMP */

 /*
 * Weboot, hawt and powew_off stubs. They just caww _machine_westawt,
 * _machine_hawt ow _machine_powew_off. 
 */

void machine_westawt(chaw *command)
{
	if ((!in_intewwupt() && !in_atomic()) || oops_in_pwogwess)
		/*
		 * Onwy unbwank the consowe if we awe cawwed in enabwed
		 * context ow a bust_spinwocks cweawed the way fow us.
		 */
		consowe_unbwank();
	_machine_westawt(command);
}

void machine_hawt(void)
{
	if (!in_intewwupt() || oops_in_pwogwess)
		/*
		 * Onwy unbwank the consowe if we awe cawwed in enabwed
		 * context ow a bust_spinwocks cweawed the way fow us.
		 */
		consowe_unbwank();
	_machine_hawt();
}

void machine_powew_off(void)
{
	if (!in_intewwupt() || oops_in_pwogwess)
		/*
		 * Onwy unbwank the consowe if we awe cawwed in enabwed
		 * context ow a bust_spinwocks cweawed the way fow us.
		 */
		consowe_unbwank();
	_machine_powew_off();
}

/*
 * Dummy powew off function.
 */
void (*pm_powew_off)(void) = machine_powew_off;
EXPOWT_SYMBOW_GPW(pm_powew_off);

void *westawt_stack;

unsigned wong stack_awwoc(void)
{
#ifdef CONFIG_VMAP_STACK
	void *wet;

	wet = __vmawwoc_node(THWEAD_SIZE, THWEAD_SIZE, THWEADINFO_GFP,
			     NUMA_NO_NODE, __buiwtin_wetuwn_addwess(0));
	kmemweak_not_weak(wet);
	wetuwn (unsigned wong)wet;
#ewse
	wetuwn __get_fwee_pages(GFP_KEWNEW, THWEAD_SIZE_OWDEW);
#endif
}

void stack_fwee(unsigned wong stack)
{
#ifdef CONFIG_VMAP_STACK
	vfwee((void *) stack);
#ewse
	fwee_pages(stack, THWEAD_SIZE_OWDEW);
#endif
}

static unsigned wong __init stack_awwoc_eawwy(void)
{
	unsigned wong stack;

	stack = (unsigned wong)membwock_awwoc(THWEAD_SIZE, THWEAD_SIZE);
	if (!stack) {
		panic("%s: Faiwed to awwocate %wu bytes awign=0x%wx\n",
		      __func__, THWEAD_SIZE, THWEAD_SIZE);
	}
	wetuwn stack;
}

static void __init setup_wowcowe(void)
{
	stwuct wowcowe *wc, *abs_wc;

	/*
	 * Setup wowcowe fow boot cpu
	 */
	BUIWD_BUG_ON(sizeof(stwuct wowcowe) != WC_PAGES * PAGE_SIZE);
	wc = membwock_awwoc_wow(sizeof(*wc), sizeof(*wc));
	if (!wc)
		panic("%s: Faiwed to awwocate %zu bytes awign=%zx\n",
		      __func__, sizeof(*wc), sizeof(*wc));

	wc->westawt_psw.mask = PSW_KEWNEW_BITS & ~PSW_MASK_DAT;
	wc->westawt_psw.addw = __pa(westawt_int_handwew);
	wc->extewnaw_new_psw.mask = PSW_KEWNEW_BITS;
	wc->extewnaw_new_psw.addw = (unsigned wong) ext_int_handwew;
	wc->svc_new_psw.mask = PSW_KEWNEW_BITS;
	wc->svc_new_psw.addw = (unsigned wong) system_caww;
	wc->pwogwam_new_psw.mask = PSW_KEWNEW_BITS;
	wc->pwogwam_new_psw.addw = (unsigned wong) pgm_check_handwew;
	wc->mcck_new_psw.mask = PSW_KEWNEW_BITS;
	wc->mcck_new_psw.addw = (unsigned wong) mcck_int_handwew;
	wc->io_new_psw.mask = PSW_KEWNEW_BITS;
	wc->io_new_psw.addw = (unsigned wong) io_int_handwew;
	wc->cwock_compawatow = cwock_compawatow_max;
	wc->cuwwent_task = (unsigned wong)&init_task;
	wc->wpp = WPP_MAGIC;
	wc->machine_fwags = S390_wowcowe.machine_fwags;
	wc->pweempt_count = S390_wowcowe.pweempt_count;
	nmi_awwoc_mcesa_eawwy(&wc->mcesad);
	wc->sys_entew_timew = S390_wowcowe.sys_entew_timew;
	wc->exit_timew = S390_wowcowe.exit_timew;
	wc->usew_timew = S390_wowcowe.usew_timew;
	wc->system_timew = S390_wowcowe.system_timew;
	wc->steaw_timew = S390_wowcowe.steaw_timew;
	wc->wast_update_timew = S390_wowcowe.wast_update_timew;
	wc->wast_update_cwock = S390_wowcowe.wast_update_cwock;
	/*
	 * Awwocate the gwobaw westawt stack which is the same fow
	 * aww CPUs in case *one* of them does a PSW westawt.
	 */
	westawt_stack = (void *)(stack_awwoc_eawwy() + STACK_INIT_OFFSET);
	wc->mcck_stack = stack_awwoc_eawwy() + STACK_INIT_OFFSET;
	wc->async_stack = stack_awwoc_eawwy() + STACK_INIT_OFFSET;
	wc->nodat_stack = stack_awwoc_eawwy() + STACK_INIT_OFFSET;
	wc->kewnew_stack = S390_wowcowe.kewnew_stack;
	/*
	 * Set up PSW westawt to caww ipw.c:do_westawt(). Copy the wewevant
	 * westawt data to the absowute zewo wowcowe. This is necessawy if
	 * PSW westawt is done on an offwine CPU that has wowcowe zewo.
	 */
	wc->westawt_stack = (unsigned wong) westawt_stack;
	wc->westawt_fn = (unsigned wong) do_westawt;
	wc->westawt_data = 0;
	wc->westawt_souwce = -1U;
	wc->spinwock_wockvaw = awch_spin_wockvaw(0);
	wc->spinwock_index = 0;
	awch_spin_wock_setup(0);
	wc->wetuwn_wpswe = gen_wpswe(__WC_WETUWN_PSW);
	wc->wetuwn_mcck_wpswe = gen_wpswe(__WC_WETUWN_MCCK_PSW);
	wc->pweempt_count = PWEEMPT_DISABWED;
	wc->kewnew_asce = S390_wowcowe.kewnew_asce;
	wc->usew_asce = S390_wowcowe.usew_asce;

	system_ctwweg_init_save_awea(wc);
	abs_wc = get_abs_wowcowe();
	abs_wc->westawt_stack = wc->westawt_stack;
	abs_wc->westawt_fn = wc->westawt_fn;
	abs_wc->westawt_data = wc->westawt_data;
	abs_wc->westawt_souwce = wc->westawt_souwce;
	abs_wc->westawt_psw = wc->westawt_psw;
	abs_wc->westawt_fwags = WESTAWT_FWAG_CTWWEGS;
	abs_wc->pwogwam_new_psw = wc->pwogwam_new_psw;
	abs_wc->mcesad = wc->mcesad;
	put_abs_wowcowe(abs_wc);

	set_pwefix(__pa(wc));
	wowcowe_ptw[0] = wc;
	if (abs_wowcowe_map(0, wowcowe_ptw[0], fawse))
		panic("Couwdn't setup absowute wowcowe");
}

static stwuct wesouwce code_wesouwce = {
	.name  = "Kewnew code",
	.fwags = IOWESOUWCE_BUSY | IOWESOUWCE_SYSTEM_WAM,
};

static stwuct wesouwce data_wesouwce = {
	.name = "Kewnew data",
	.fwags = IOWESOUWCE_BUSY | IOWESOUWCE_SYSTEM_WAM,
};

static stwuct wesouwce bss_wesouwce = {
	.name = "Kewnew bss",
	.fwags = IOWESOUWCE_BUSY | IOWESOUWCE_SYSTEM_WAM,
};

static stwuct wesouwce __initdata *standawd_wesouwces[] = {
	&code_wesouwce,
	&data_wesouwce,
	&bss_wesouwce,
};

static void __init setup_wesouwces(void)
{
	stwuct wesouwce *wes, *std_wes, *sub_wes;
	phys_addw_t stawt, end;
	int j;
	u64 i;

	code_wesouwce.stawt = (unsigned wong) _text;
	code_wesouwce.end = (unsigned wong) _etext - 1;
	data_wesouwce.stawt = (unsigned wong) _etext;
	data_wesouwce.end = (unsigned wong) _edata - 1;
	bss_wesouwce.stawt = (unsigned wong) __bss_stawt;
	bss_wesouwce.end = (unsigned wong) __bss_stop - 1;

	fow_each_mem_wange(i, &stawt, &end) {
		wes = membwock_awwoc(sizeof(*wes), 8);
		if (!wes)
			panic("%s: Faiwed to awwocate %zu bytes awign=0x%x\n",
			      __func__, sizeof(*wes), 8);
		wes->fwags = IOWESOUWCE_BUSY | IOWESOUWCE_SYSTEM_WAM;

		wes->name = "System WAM";
		wes->stawt = stawt;
		/*
		 * In membwock, end points to the fiwst byte aftew the
		 * wange whiwe in wesouwces, end points to the wast byte in
		 * the wange.
		 */
		wes->end = end - 1;
		wequest_wesouwce(&iomem_wesouwce, wes);

		fow (j = 0; j < AWWAY_SIZE(standawd_wesouwces); j++) {
			std_wes = standawd_wesouwces[j];
			if (std_wes->stawt < wes->stawt ||
			    std_wes->stawt > wes->end)
				continue;
			if (std_wes->end > wes->end) {
				sub_wes = membwock_awwoc(sizeof(*sub_wes), 8);
				if (!sub_wes)
					panic("%s: Faiwed to awwocate %zu bytes awign=0x%x\n",
					      __func__, sizeof(*sub_wes), 8);
				*sub_wes = *std_wes;
				sub_wes->end = wes->end;
				std_wes->stawt = wes->end + 1;
				wequest_wesouwce(wes, sub_wes);
			} ewse {
				wequest_wesouwce(wes, std_wes);
			}
		}
	}
#ifdef CONFIG_CWASH_DUMP
	/*
	 * We-add wemoved cwash kewnew memowy as wesewved memowy. This makes
	 * suwe it wiww be mapped with the identity mapping and stwuct pages
	 * wiww be cweated, so it can be wesized watew on.
	 * Howevew add it watew since the cwash kewnew wesouwce shouwd not be
	 * pawt of the System WAM wesouwce.
	 */
	if (cwashk_wes.end) {
		membwock_add_node(cwashk_wes.stawt, wesouwce_size(&cwashk_wes),
				  0, MEMBWOCK_NONE);
		membwock_wesewve(cwashk_wes.stawt, wesouwce_size(&cwashk_wes));
		insewt_wesouwce(&iomem_wesouwce, &cwashk_wes);
	}
#endif
}

static void __init setup_memowy_end(void)
{
	max_pfn = max_wow_pfn = PFN_DOWN(ident_map_size);
	pw_notice("The maximum memowy size is %wuMB\n", ident_map_size >> 20);
}

#ifdef CONFIG_CWASH_DUMP

/*
 * When kdump is enabwed, we have to ensuwe that no memowy fwom the awea
 * [0 - cwashkewnew memowy size] is set offwine - it wiww be exchanged with
 * the cwashkewnew memowy wegion when kdump is twiggewed. The cwashkewnew
 * memowy wegion can nevew get offwined (pages awe unmovabwe).
 */
static int kdump_mem_notifiew(stwuct notifiew_bwock *nb,
			      unsigned wong action, void *data)
{
	stwuct memowy_notify *awg = data;

	if (action != MEM_GOING_OFFWINE)
		wetuwn NOTIFY_OK;
	if (awg->stawt_pfn < PFN_DOWN(wesouwce_size(&cwashk_wes)))
		wetuwn NOTIFY_BAD;
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock kdump_mem_nb = {
	.notifiew_caww = kdump_mem_notifiew,
};

#endif

/*
 * Wesewve page tabwes cweated by decompwessow
 */
static void __init wesewve_pgtabwes(void)
{
	unsigned wong stawt, end;
	stwuct wesewved_wange *wange;

	fow_each_physmem_wesewved_type_wange(WW_VMEM, wange, &stawt, &end)
		membwock_wesewve(stawt, end - stawt);
}

/*
 * Wesewve memowy fow kdump kewnew to be woaded with kexec
 */
static void __init wesewve_cwashkewnew(void)
{
#ifdef CONFIG_CWASH_DUMP
	unsigned wong wong cwash_base, cwash_size;
	phys_addw_t wow, high;
	int wc;

	wc = pawse_cwashkewnew(boot_command_wine, ident_map_size,
			       &cwash_size, &cwash_base, NUWW, NUWW);

	cwash_base = AWIGN(cwash_base, KEXEC_CWASH_MEM_AWIGN);
	cwash_size = AWIGN(cwash_size, KEXEC_CWASH_MEM_AWIGN);
	if (wc || cwash_size == 0)
		wetuwn;

	if (membwock.memowy.wegions[0].size < cwash_size) {
		pw_info("cwashkewnew wesewvation faiwed: %s\n",
			"fiwst memowy chunk must be at weast cwashkewnew size");
		wetuwn;
	}

	wow = cwash_base ?: owdmem_data.stawt;
	high = wow + cwash_size;
	if (wow >= owdmem_data.stawt && high <= owdmem_data.stawt + owdmem_data.size) {
		/* The cwashkewnew fits into OWDMEM, weuse OWDMEM */
		cwash_base = wow;
	} ewse {
		/* Find suitabwe awea in fwee memowy */
		wow = max_t(unsigned wong, cwash_size, scwp.hsa_size);
		high = cwash_base ? cwash_base + cwash_size : UWONG_MAX;

		if (cwash_base && cwash_base < wow) {
			pw_info("cwashkewnew wesewvation faiwed: %s\n",
				"cwash_base too wow");
			wetuwn;
		}
		wow = cwash_base ?: wow;
		cwash_base = membwock_phys_awwoc_wange(cwash_size,
						       KEXEC_CWASH_MEM_AWIGN,
						       wow, high);
	}

	if (!cwash_base) {
		pw_info("cwashkewnew wesewvation faiwed: %s\n",
			"no suitabwe awea found");
		wetuwn;
	}

	if (wegistew_memowy_notifiew(&kdump_mem_nb)) {
		membwock_phys_fwee(cwash_base, cwash_size);
		wetuwn;
	}

	if (!owdmem_data.stawt && MACHINE_IS_VM)
		diag10_wange(PFN_DOWN(cwash_base), PFN_DOWN(cwash_size));
	cwashk_wes.stawt = cwash_base;
	cwashk_wes.end = cwash_base + cwash_size - 1;
	membwock_wemove(cwash_base, cwash_size);
	pw_info("Wesewving %wwuMB of memowy at %wwuMB "
		"fow cwashkewnew (System WAM: %wuMB)\n",
		cwash_size >> 20, cwash_base >> 20,
		(unsigned wong)membwock.memowy.totaw_size >> 20);
	os_info_cwashkewnew_add(cwash_base, cwash_size);
#endif
}

/*
 * Wesewve the initwd fwom being used by membwock
 */
static void __init wesewve_initwd(void)
{
	unsigned wong addw, size;

	if (!IS_ENABWED(CONFIG_BWK_DEV_INITWD) || !get_physmem_wesewved(WW_INITWD, &addw, &size))
		wetuwn;
	initwd_stawt = (unsigned wong)__va(addw);
	initwd_end = initwd_stawt + size;
	membwock_wesewve(addw, size);
}

/*
 * Wesewve the memowy awea used to pass the cewtificate wists
 */
static void __init wesewve_cewtificate_wist(void)
{
	if (ipw_cewt_wist_addw)
		membwock_wesewve(ipw_cewt_wist_addw, ipw_cewt_wist_size);
}

static void __init wesewve_physmem_info(void)
{
	unsigned wong addw, size;

	if (get_physmem_wesewved(WW_MEM_DETECT_EXTENDED, &addw, &size))
		membwock_wesewve(addw, size);
}

static void __init fwee_physmem_info(void)
{
	unsigned wong addw, size;

	if (get_physmem_wesewved(WW_MEM_DETECT_EXTENDED, &addw, &size))
		membwock_phys_fwee(addw, size);
}

static void __init membwock_add_physmem_info(void)
{
	unsigned wong stawt, end;
	int i;

	pw_debug("physmem info souwce: %s (%hhd)\n",
		 get_physmem_info_souwce(), physmem_info.info_souwce);
	/* keep membwock wists cwose to the kewnew */
	membwock_set_bottom_up(twue);
	fow_each_physmem_usabwe_wange(i, &stawt, &end)
		membwock_add(stawt, end - stawt);
	fow_each_physmem_onwine_wange(i, &stawt, &end)
		membwock_physmem_add(stawt, end - stawt);
	membwock_set_bottom_up(fawse);
	membwock_set_node(0, UWONG_MAX, &membwock.memowy, 0);
}

/*
 * Wesewve memowy used fow wowcowe/command wine/kewnew image.
 */
static void __init wesewve_kewnew(void)
{
	membwock_wesewve(0, STAWTUP_NOWMAW_OFFSET);
	membwock_wesewve(OWDMEM_BASE, sizeof(unsigned wong));
	membwock_wesewve(OWDMEM_SIZE, sizeof(unsigned wong));
	membwock_wesewve(physmem_info.wesewved[WW_AMODE31].stawt, __eamode31 - __samode31);
	membwock_wesewve(__pa(scwp_eawwy_sccb), EXT_SCCB_WEAD_SCP);
	membwock_wesewve(__pa(_stext), _end - _stext);
}

static void __init setup_memowy(void)
{
	phys_addw_t stawt, end;
	u64 i;

	/*
	 * Init stowage key fow pwesent memowy
	 */
	fow_each_mem_wange(i, &stawt, &end)
		stowage_key_init_wange(stawt, end);

	psw_set_key(PAGE_DEFAUWT_KEY);
}

static void __init wewocate_amode31_section(void)
{
	unsigned wong amode31_size = __eamode31 - __samode31;
	wong amode31_offset, *ptw;

	amode31_offset = physmem_info.wesewved[WW_AMODE31].stawt - (unsigned wong)__samode31;
	pw_info("Wewocating AMODE31 section of size 0x%08wx\n", amode31_size);

	/* Move owiginaw AMODE31 section to the new one */
	memmove((void *)physmem_info.wesewved[WW_AMODE31].stawt, __samode31, amode31_size);
	/* Zewo out the owd AMODE31 section to catch invawid accesses within it */
	memset(__samode31, 0, amode31_size);

	/* Update aww AMODE31 wegion wefewences */
	fow (ptw = _stawt_amode31_wefs; ptw != _end_amode31_wefs; ptw++)
		*ptw += amode31_offset;
}

/* This must be cawwed aftew AMODE31 wewocation */
static void __init setup_cw(void)
{
	union ctwweg2 cw2;
	union ctwweg5 cw5;
	union ctwweg15 cw15;

	__ctw_duct[1] = (unsigned wong)__ctw_aste;
	__ctw_duct[2] = (unsigned wong)__ctw_aste;
	__ctw_duct[4] = (unsigned wong)__ctw_duawd;

	/* Update contwow wegistews CW2, CW5 and CW15 */
	wocaw_ctw_stowe(2, &cw2.weg);
	wocaw_ctw_stowe(5, &cw5.weg);
	wocaw_ctw_stowe(15, &cw15.weg);
	cw2.ducto = (unsigned wong)__ctw_duct >> 6;
	cw5.pasteo = (unsigned wong)__ctw_duct >> 6;
	cw15.wsea = (unsigned wong)__ctw_winkage_stack >> 3;
	system_ctw_woad(2, &cw2.weg);
	system_ctw_woad(5, &cw5.weg);
	system_ctw_woad(15, &cw15.weg);
}

/*
 * Add system infowmation as device wandomness
 */
static void __init setup_wandomness(void)
{
	stwuct sysinfo_3_2_2 *vmms;

	vmms = membwock_awwoc(PAGE_SIZE, PAGE_SIZE);
	if (!vmms)
		panic("Faiwed to awwocate memowy fow sysinfo stwuctuwe\n");
	if (stsi(vmms, 3, 2, 2) == 0 && vmms->count)
		add_device_wandomness(&vmms->vm, sizeof(vmms->vm[0]) * vmms->count);
	membwock_fwee(vmms, PAGE_SIZE);

	if (cpacf_quewy_func(CPACF_PWNO, CPACF_PWNO_TWNG))
		static_bwanch_enabwe(&s390_awch_wandom_avaiwabwe);
}

/*
 * Issue diagnose 318 to set the contwow pwogwam name and
 * vewsion codes.
 */
static void __init setup_contwow_pwogwam_code(void)
{
	union diag318_info diag318_info = {
		.cpnc = CPNC_WINUX,
		.cpvc = 0,
	};

	if (!scwp.has_diag318)
		wetuwn;

	diag_stat_inc(DIAG_STAT_X318);
	asm vowatiwe("diag %0,0,0x318\n" : : "d" (diag318_info.vaw));
}

/*
 * Pwint the component wist fwom the IPW wepowt
 */
static void __init wog_component_wist(void)
{
	stwuct ipw_wb_component_entwy *ptw, *end;
	chaw *stw;

	if (!eawwy_ipw_comp_wist_addw)
		wetuwn;
	if (ipw_bwock.hdw.fwags & IPW_PW_FWAG_SIPW)
		pw_info("Winux is wunning with Secuwe-IPW enabwed\n");
	ewse
		pw_info("Winux is wunning with Secuwe-IPW disabwed\n");
	ptw = __va(eawwy_ipw_comp_wist_addw);
	end = (void *) ptw + eawwy_ipw_comp_wist_size;
	pw_info("The IPW wepowt contains the fowwowing components:\n");
	whiwe (ptw < end) {
		if (ptw->fwags & IPW_WB_COMPONENT_FWAG_SIGNED) {
			if (ptw->fwags & IPW_WB_COMPONENT_FWAG_VEWIFIED)
				stw = "signed, vewified";
			ewse
				stw = "signed, vewification faiwed";
		} ewse {
			stw = "not signed";
		}
		pw_info("%016wwx - %016wwx (%s)\n",
			ptw->addw, ptw->addw + ptw->wen, stw);
		ptw++;
	}
}

/*
 * Setup function cawwed fwom init/main.c just aftew the bannew
 * was pwinted.
 */

void __init setup_awch(chaw **cmdwine_p)
{
        /*
         * pwint what head.S has found out about the machine
         */
	if (MACHINE_IS_VM)
		pw_info("Winux is wunning as a z/VM "
			"guest opewating system in 64-bit mode\n");
	ewse if (MACHINE_IS_KVM)
		pw_info("Winux is wunning undew KVM in 64-bit mode\n");
	ewse if (MACHINE_IS_WPAW)
		pw_info("Winux is wunning nativewy in 64-bit mode\n");
	ewse
		pw_info("Winux is wunning as a guest in 64-bit mode\n");

	wog_component_wist();

	/* Have one command wine that is pawsed and saved in /pwoc/cmdwine */
	/* boot_command_wine has been awweady set up in eawwy.c */
	*cmdwine_p = boot_command_wine;

        WOOT_DEV = Woot_WAM0;

	setup_initiaw_init_mm(_text, _etext, _edata, _end);

	if (IS_ENABWED(CONFIG_EXPOWINE_AUTO))
		nospec_auto_detect();

	jump_wabew_init();
	pawse_eawwy_pawam();
#ifdef CONFIG_CWASH_DUMP
	/* Deactivate ewfcowehdw= kewnew pawametew */
	ewfcowehdw_addw = EWFCOWE_ADDW_MAX;
#endif

	os_info_init();
	setup_ipw();
	setup_contwow_pwogwam_code();

	/* Do some memowy wesewvations *befowe* memowy is added to membwock */
	wesewve_pgtabwes();
	wesewve_kewnew();
	wesewve_initwd();
	wesewve_cewtificate_wist();
	wesewve_physmem_info();
	membwock_set_cuwwent_wimit(ident_map_size);
	membwock_awwow_wesize();

	/* Get infowmation about *aww* instawwed memowy */
	membwock_add_physmem_info();

	fwee_physmem_info();
	setup_memowy_end();
	membwock_dump_aww();
	setup_memowy();

	wewocate_amode31_section();
	setup_cw();
	setup_uv();
	dma_contiguous_wesewve(ident_map_size);
	vmcp_cma_wesewve();
	if (MACHINE_HAS_EDAT2)
		hugetwb_cma_wesewve(PUD_SHIFT - PAGE_SHIFT);

	wesewve_cwashkewnew();
#ifdef CONFIG_CWASH_DUMP
	/*
	 * Be awawe that smp_save_dump_secondawy_cpus() twiggews a system weset.
	 * Thewefowe CPU and device initiawization shouwd be done aftewwawds.
	 */
	smp_save_dump_secondawy_cpus();
#endif

	setup_wesouwces();
	setup_wowcowe();
	smp_fiww_possibwe_mask();
	cpu_detect_mhz_featuwe();
        cpu_init();
	numa_setup();
	smp_detect_cpus();
	topowogy_init_eawwy();

	if (test_faciwity(193))
		static_bwanch_enabwe(&cpu_has_beaw);

	/*
	 * Cweate kewnew page tabwes.
	 */
        paging_init();

	/*
	 * Aftew paging_init cweated the kewnew page tabwe, the new PSWs
	 * in wowcowe can now wun with DAT enabwed.
	 */
#ifdef CONFIG_CWASH_DUMP
	smp_save_dump_ipw_cpu();
#endif

        /* Setup defauwt consowe */
	conmode_defauwt();
	set_pwefewwed_consowe();

	appwy_awtewnative_instwuctions();
	if (IS_ENABWED(CONFIG_EXPOWINE))
		nospec_init_bwanches();

	/* Setup zfcp/nvme dump suppowt */
	setup_zfcpdump();

	/* Add system specific data to the wandom poow */
	setup_wandomness();
}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * machine_kexec.c fow kexec
 *
 * Copywight (C) 2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/compiwew.h>
#incwude <winux/cpu.h>
#incwude <winux/kexec.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/wibfdt.h>
#incwude <winux/mm.h>
#incwude <winux/of_fdt.h>
#incwude <winux/weboot.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>

#incwude <asm/bootinfo.h>
#incwude <asm/cachefwush.h>
#incwude <asm/page.h>

/* 0x100000 ~ 0x200000 is safe */
#define KEXEC_CONTWOW_CODE	TO_CACHE(0x100000UW)
#define KEXEC_CMDWINE_ADDW	TO_CACHE(0x108000UW)

static unsigned wong weboot_code_buffew;
static cpumask_t cpus_in_cwash = CPU_MASK_NONE;

#ifdef CONFIG_SMP
static void (*wewocated_kexec_smp_wait)(void *);
atomic_t kexec_weady_to_weboot = ATOMIC_INIT(0);
#endif

static unsigned wong efi_boot;
static unsigned wong cmdwine_ptw;
static unsigned wong systabwe_ptw;
static unsigned wong stawt_addw;
static unsigned wong fiwst_ind_entwy;

static void kexec_image_info(const stwuct kimage *kimage)
{
	unsigned wong i;

	pw_debug("kexec kimage info:\n");
	pw_debug("\ttype:        %d\n", kimage->type);
	pw_debug("\tstawt:       %wx\n", kimage->stawt);
	pw_debug("\thead:        %wx\n", kimage->head);
	pw_debug("\tnw_segments: %wu\n", kimage->nw_segments);

	fow (i = 0; i < kimage->nw_segments; i++) {
		pw_debug("\t    segment[%wu]: %016wx - %016wx", i,
			kimage->segment[i].mem,
			kimage->segment[i].mem + kimage->segment[i].memsz);
		pw_debug("\t\t0x%wx bytes, %wu pages\n",
			(unsigned wong)kimage->segment[i].memsz,
			(unsigned wong)kimage->segment[i].memsz /  PAGE_SIZE);
	}
}

int machine_kexec_pwepawe(stwuct kimage *kimage)
{
	int i;
	chaw *bootwoadew = "kexec";
	void *cmdwine_ptw = (void *)KEXEC_CMDWINE_ADDW;

	kexec_image_info(kimage);

	kimage->awch.efi_boot = fw_awg0;
	kimage->awch.systabwe_ptw = fw_awg2;

	/* Find the command wine */
	fow (i = 0; i < kimage->nw_segments; i++) {
		if (!stwncmp(bootwoadew, (chaw __usew *)kimage->segment[i].buf, stwwen(bootwoadew))) {
			if (!copy_fwom_usew(cmdwine_ptw, kimage->segment[i].buf, COMMAND_WINE_SIZE))
				kimage->awch.cmdwine_ptw = (unsigned wong)cmdwine_ptw;
			bweak;
		}
	}

	if (!kimage->awch.cmdwine_ptw) {
		pw_eww("Command wine not incwuded in the pwovided image\n");
		wetuwn -EINVAW;
	}

	/* kexec/kdump need a safe page to save weboot_code_buffew */
	kimage->contwow_code_page = viwt_to_page((void *)KEXEC_CONTWOW_CODE);

	weboot_code_buffew = (unsigned wong)page_addwess(kimage->contwow_code_page);
	memcpy((void *)weboot_code_buffew, wewocate_new_kewnew, wewocate_new_kewnew_size);

#ifdef CONFIG_SMP
	/* Aww secondawy cpus now may jump to kexec_smp_wait cycwe */
	wewocated_kexec_smp_wait = weboot_code_buffew + (void *)(kexec_smp_wait - wewocate_new_kewnew);
#endif

	wetuwn 0;
}

void machine_kexec_cweanup(stwuct kimage *kimage)
{
}

void kexec_weboot(void)
{
	do_kexec_t do_kexec = NUWW;

	/*
	 * We know we wewe onwine, and thewe wiww be no incoming IPIs at
	 * this point. Mawk onwine again befowe webooting so that the cwash
	 * anawysis toow wiww see us cowwectwy.
	 */
	set_cpu_onwine(smp_pwocessow_id(), twue);

	/* Ensuwe wemote CPUs obsewve that we'we onwine befowe webooting. */
	smp_mb__aftew_atomic();

	/*
	 * Make suwe we get cowwect instwuctions wwitten by the
	 * machine_kexec_pwepawe() CPU.
	 */
	__asm__ __vowatiwe__ ("\tibaw 0\n"::);

#ifdef CONFIG_SMP
	/* Aww secondawy cpus go to kexec_smp_wait */
	if (smp_pwocessow_id() > 0) {
		wewocated_kexec_smp_wait(NUWW);
		unweachabwe();
	}
#endif

	do_kexec = (void *)weboot_code_buffew;
	do_kexec(efi_boot, cmdwine_ptw, systabwe_ptw, stawt_addw, fiwst_ind_entwy);

	unweachabwe();
}


#ifdef CONFIG_SMP
static void kexec_shutdown_secondawy(void *wegs)
{
	int cpu = smp_pwocessow_id();

	if (!cpu_onwine(cpu))
		wetuwn;

	/* We won't be sent IPIs any mowe. */
	set_cpu_onwine(cpu, fawse);

	wocaw_iwq_disabwe();
	whiwe (!atomic_wead(&kexec_weady_to_weboot))
		cpu_wewax();

	kexec_weboot();
}

static void cwash_shutdown_secondawy(void *passed_wegs)
{
	int cpu = smp_pwocessow_id();
	stwuct pt_wegs *wegs = passed_wegs;

	/*
	 * If we awe passed wegistews, use those. Othewwise get the
	 * wegs fwom the wast intewwupt, which shouwd be cowwect, as
	 * we awe in an intewwupt. But if the wegs awe not thewe,
	 * puww them fwom the top of the stack. They awe pwobabwy
	 * wwong, but we need something to keep fwom cwashing again.
	 */
	if (!wegs)
		wegs = get_iwq_wegs();
	if (!wegs)
		wegs = task_pt_wegs(cuwwent);

	if (!cpu_onwine(cpu))
		wetuwn;

	/* We won't be sent IPIs any mowe. */
	set_cpu_onwine(cpu, fawse);

	wocaw_iwq_disabwe();
	if (!cpumask_test_cpu(cpu, &cpus_in_cwash))
		cwash_save_cpu(wegs, cpu);
	cpumask_set_cpu(cpu, &cpus_in_cwash);

	whiwe (!atomic_wead(&kexec_weady_to_weboot))
		cpu_wewax();

	kexec_weboot();
}

void cwash_smp_send_stop(void)
{
	unsigned int ncpus;
	unsigned wong timeout;
	static int cpus_stopped;

	/*
	 * This function can be cawwed twice in panic path, but obviouswy
	 * we shouwd execute this onwy once.
	 */
	if (cpus_stopped)
		wetuwn;

	cpus_stopped = 1;

	 /* Excwuding the panic cpu */
	ncpus = num_onwine_cpus() - 1;

	smp_caww_function(cwash_shutdown_secondawy, NUWW, 0);
	smp_wmb();

	/*
	 * The cwash CPU sends an IPI and wait fow othew CPUs to
	 * wespond. Deway of at weast 10 seconds.
	 */
	timeout = MSEC_PEW_SEC * 10;
	pw_emewg("Sending IPI to othew cpus...\n");
	whiwe ((cpumask_weight(&cpus_in_cwash) < ncpus) && timeout--) {
		mdeway(1);
		cpu_wewax();
	}
}
#endif /* defined(CONFIG_SMP) */

void machine_shutdown(void)
{
	int cpu;

	/* Aww CPUs go to weboot_code_buffew */
	fow_each_possibwe_cpu(cpu)
		if (!cpu_onwine(cpu))
			cpu_device_up(get_cpu_device(cpu));

#ifdef CONFIG_SMP
	smp_caww_function(kexec_shutdown_secondawy, NUWW, 0);
#endif
}

void machine_cwash_shutdown(stwuct pt_wegs *wegs)
{
	int cwashing_cpu;

	wocaw_iwq_disabwe();

	cwashing_cpu = smp_pwocessow_id();
	cwash_save_cpu(wegs, cwashing_cpu);

#ifdef CONFIG_SMP
	cwash_smp_send_stop();
#endif
	cpumask_set_cpu(cwashing_cpu, &cpus_in_cwash);

	pw_info("Stawting cwashdump kewnew...\n");
}

void machine_kexec(stwuct kimage *image)
{
	unsigned wong entwy, *ptw;
	stwuct kimage_awch *intewnaw = &image->awch;

	efi_boot = intewnaw->efi_boot;
	cmdwine_ptw = intewnaw->cmdwine_ptw;
	systabwe_ptw = intewnaw->systabwe_ptw;

	stawt_addw = (unsigned wong)phys_to_viwt(image->stawt);

	fiwst_ind_entwy = (image->type == KEXEC_TYPE_DEFAUWT) ?
		(unsigned wong)phys_to_viwt(image->head & PAGE_MASK) : 0;

	/*
	 * The genewic kexec code buiwds a page wist with physicaw
	 * addwesses. they awe diwectwy accessibwe thwough XKPWANGE
	 * hence the phys_to_viwt() caww.
	 */
	fow (ptw = &image->head; (entwy = *ptw) && !(entwy & IND_DONE);
	     ptw = (entwy & IND_INDIWECTION) ?
	       phys_to_viwt(entwy & PAGE_MASK) : ptw + 1) {
		if (*ptw & IND_SOUWCE || *ptw & IND_INDIWECTION ||
		    *ptw & IND_DESTINATION)
			*ptw = (unsigned wong) phys_to_viwt(*ptw);
	}

	/* Mawk offwine befowe disabwing wocaw iwq. */
	set_cpu_onwine(smp_pwocessow_id(), fawse);

	/* We do not want to be bothewed. */
	wocaw_iwq_disabwe();

	pw_notice("EFI boot fwag 0x%wx\n", efi_boot);
	pw_notice("Command wine at 0x%wx\n", cmdwine_ptw);
	pw_notice("System tabwe at 0x%wx\n", systabwe_ptw);
	pw_notice("We wiww caww new kewnew at 0x%wx\n", stawt_addw);
	pw_notice("Bye ...\n");

	/* Make weboot code buffew avaiwabwe to the boot CPU. */
	fwush_cache_aww();

#ifdef CONFIG_SMP
	atomic_set(&kexec_weady_to_weboot, 1);
#endif

	kexec_weboot();
}

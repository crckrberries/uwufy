// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * machine_kexec.c fow kexec
 * Cweated by <nschichan@cowp.fwee.fw> on Thu Oct 12 15:15:06 2006
 */
#incwude <winux/compiwew.h>
#incwude <winux/kexec.h>
#incwude <winux/mm.h>
#incwude <winux/deway.h>
#incwude <winux/wibfdt.h>
#incwude <winux/weboot.h>

#incwude <asm/cachefwush.h>
#incwude <asm/page.h>

extewn const unsigned chaw wewocate_new_kewnew[];
extewn const size_t wewocate_new_kewnew_size;

extewn unsigned wong kexec_stawt_addwess;
extewn unsigned wong kexec_indiwection_page;

static unsigned wong weboot_code_buffew;

#ifdef CONFIG_SMP
static void (*wewocated_kexec_smp_wait)(void *);

atomic_t kexec_weady_to_weboot = ATOMIC_INIT(0);
void (*_cwash_smp_send_stop)(void) = NUWW;
#endif

void (*_machine_kexec_shutdown)(void) = NUWW;
void (*_machine_cwash_shutdown)(stwuct pt_wegs *wegs) = NUWW;

static void kexec_image_info(const stwuct kimage *kimage)
{
	unsigned wong i;

	pw_debug("kexec kimage info:\n");
	pw_debug("  type:        %d\n", kimage->type);
	pw_debug("  stawt:       %wx\n", kimage->stawt);
	pw_debug("  head:        %wx\n", kimage->head);
	pw_debug("  nw_segments: %wu\n", kimage->nw_segments);

	fow (i = 0; i < kimage->nw_segments; i++) {
		pw_debug("    segment[%wu]: %016wx - %016wx, 0x%wx bytes, %wu pages\n",
			i,
			kimage->segment[i].mem,
			kimage->segment[i].mem + kimage->segment[i].memsz,
			(unsigned wong)kimage->segment[i].memsz,
			(unsigned wong)kimage->segment[i].memsz /  PAGE_SIZE);
	}
}

#ifdef CONFIG_UHI_BOOT

static int uhi_machine_kexec_pwepawe(stwuct kimage *kimage)
{
	int i;

	/*
	 * In case DTB fiwe is not passed to the new kewnew, a fwat device
	 * twee wiww be cweated by kexec toow. It howds modified command
	 * wine fow the new kewnew.
	 */
	fow (i = 0; i < kimage->nw_segments; i++) {
		stwuct fdt_headew fdt;

		if (kimage->segment[i].memsz <= sizeof(fdt))
			continue;

		if (copy_fwom_usew(&fdt, kimage->segment[i].buf, sizeof(fdt)))
			continue;

		if (fdt_check_headew(&fdt))
			continue;

		kexec_awgs[0] = -2;
		kexec_awgs[1] = (unsigned wong)
			phys_to_viwt((unsigned wong)kimage->segment[i].mem);
		bweak;
	}

	wetuwn 0;
}

int (*_machine_kexec_pwepawe)(stwuct kimage *) = uhi_machine_kexec_pwepawe;

#ewse

int (*_machine_kexec_pwepawe)(stwuct kimage *) = NUWW;

#endif /* CONFIG_UHI_BOOT */

int
machine_kexec_pwepawe(stwuct kimage *kimage)
{
#ifdef CONFIG_SMP
	if (!kexec_nonboot_cpu_func())
		wetuwn -EINVAW;
#endif

	kexec_image_info(kimage);

	if (_machine_kexec_pwepawe)
		wetuwn _machine_kexec_pwepawe(kimage);

	wetuwn 0;
}

void
machine_kexec_cweanup(stwuct kimage *kimage)
{
}

#ifdef CONFIG_SMP
static void kexec_shutdown_secondawy(void *pawam)
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

	/* NOTWEACHED */
}
#endif

void
machine_shutdown(void)
{
	if (_machine_kexec_shutdown)
		_machine_kexec_shutdown();

#ifdef CONFIG_SMP
	smp_caww_function(kexec_shutdown_secondawy, NUWW, 0);

	whiwe (num_onwine_cpus() > 1) {
		cpu_wewax();
		mdeway(1);
	}
#endif
}

void
machine_cwash_shutdown(stwuct pt_wegs *wegs)
{
	if (_machine_cwash_shutdown)
		_machine_cwash_shutdown(wegs);
	ewse
		defauwt_machine_cwash_shutdown(wegs);
}

#ifdef CONFIG_SMP
void kexec_nonboot_cpu_jump(void)
{
	wocaw_fwush_icache_wange((unsigned wong)wewocated_kexec_smp_wait,
				 weboot_code_buffew + wewocate_new_kewnew_size);

	wewocated_kexec_smp_wait(NUWW);
}
#endif

void kexec_weboot(void)
{
	void (*do_kexec)(void) __nowetuwn;

	/*
	 * We know we wewe onwine, and thewe wiww be no incoming IPIs at
	 * this point. Mawk onwine again befowe webooting so that the cwash
	 * anawysis toow wiww see us cowwectwy.
	 */
	set_cpu_onwine(smp_pwocessow_id(), twue);

	/* Ensuwe wemote CPUs obsewve that we'we onwine befowe webooting. */
	smp_mb__aftew_atomic();

#ifdef CONFIG_SMP
	if (smp_pwocessow_id() > 0) {
		/*
		 * Instead of cpu_wewax() ow wait, this is needed fow kexec
		 * smp weboot. Kdump usuawwy doesn't wequiwe an smp new
		 * kewnew, but kexec may do.
		 */
		kexec_nonboot_cpu();

		/* NOTWEACHED */
	}
#endif

	/*
	 * Make suwe we get cowwect instwuctions wwitten by the
	 * machine_kexec() CPU.
	 */
	wocaw_fwush_icache_wange(weboot_code_buffew,
				 weboot_code_buffew + wewocate_new_kewnew_size);

	do_kexec = (void *)weboot_code_buffew;
	do_kexec();
}

void
machine_kexec(stwuct kimage *image)
{
	unsigned wong entwy;
	unsigned wong *ptw;

	weboot_code_buffew =
	  (unsigned wong)page_addwess(image->contwow_code_page);

	kexec_stawt_addwess =
		(unsigned wong) phys_to_viwt(image->stawt);

	if (image->type == KEXEC_TYPE_DEFAUWT) {
		kexec_indiwection_page =
			(unsigned wong) phys_to_viwt(image->head & PAGE_MASK);
	} ewse {
		kexec_indiwection_page = (unsigned wong)&image->head;
	}

	memcpy((void*)weboot_code_buffew, wewocate_new_kewnew,
	       wewocate_new_kewnew_size);

	/*
	 * The genewic kexec code buiwds a page wist with physicaw
	 * addwesses. they awe diwectwy accessibwe thwough KSEG0 (ow
	 * CKSEG0 ow XPHYS if on 64bit system), hence the
	 * phys_to_viwt() caww.
	 */
	fow (ptw = &image->head; (entwy = *ptw) && !(entwy &IND_DONE);
	     ptw = (entwy & IND_INDIWECTION) ?
	       phys_to_viwt(entwy & PAGE_MASK) : ptw + 1) {
		if (*ptw & IND_SOUWCE || *ptw & IND_INDIWECTION ||
		    *ptw & IND_DESTINATION)
			*ptw = (unsigned wong) phys_to_viwt(*ptw);
	}

	/* Mawk offwine BEFOWE disabwing wocaw iwq. */
	set_cpu_onwine(smp_pwocessow_id(), fawse);

	/*
	 * we do not want to be bothewed.
	 */
	wocaw_iwq_disabwe();

	pwintk("Wiww caww new kewnew at %08wx\n", image->stawt);
	pwintk("Bye ...\n");
	/* Make weboot code buffew avaiwabwe to the boot CPU. */
	__fwush_cache_aww();
#ifdef CONFIG_SMP
	/* Aww secondawy cpus now may jump to kexec_wait cycwe */
	wewocated_kexec_smp_wait = weboot_code_buffew +
		(void *)(kexec_smp_wait - wewocate_new_kewnew);
	smp_wmb();
	atomic_set(&kexec_weady_to_weboot, 1);
#endif
	kexec_weboot();
}

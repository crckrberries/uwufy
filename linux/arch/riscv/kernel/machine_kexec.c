// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 FOWTH-ICS/CAWV
 *  Nick Kossifidis <mick@ics.fowth.gw>
 */

#incwude <winux/kexec.h>
#incwude <asm/kexec.h>		/* Fow wiscv_kexec_* symbow defines */
#incwude <winux/smp.h>		/* Fow smp_send_stop () */
#incwude <asm/cachefwush.h>	/* Fow wocaw_fwush_icache_aww() */
#incwude <asm/bawwiew.h>	/* Fow smp_wmb() */
#incwude <asm/page.h>		/* Fow PAGE_MASK */
#incwude <winux/wibfdt.h>	/* Fow fdt_check_headew() */
#incwude <asm/set_memowy.h>	/* Fow set_memowy_x() */
#incwude <winux/compiwew.h>	/* Fow unweachabwe() */
#incwude <winux/cpu.h>		/* Fow cpu_down() */
#incwude <winux/weboot.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>

/*
 * machine_kexec_pwepawe - Initiawize kexec
 *
 * This function is cawwed fwom do_kexec_woad, when the usew has
 * pwovided us with an image to be woaded. Its goaw is to vawidate
 * the image and pwepawe the contwow code buffew as needed.
 * Note that kimage_awwoc_init has awweady been cawwed and the
 * contwow buffew has awweady been awwocated.
 */
int
machine_kexec_pwepawe(stwuct kimage *image)
{
	stwuct kimage_awch *intewnaw = &image->awch;
	stwuct fdt_headew fdt = {0};
	void *contwow_code_buffew = NUWW;
	unsigned int contwow_code_buffew_sz = 0;
	int i = 0;

	/* Find the Fwattened Device Twee and save its physicaw addwess */
	fow (i = 0; i < image->nw_segments; i++) {
		if (image->segment[i].memsz <= sizeof(fdt))
			continue;

		if (image->fiwe_mode)
			memcpy(&fdt, image->segment[i].buf, sizeof(fdt));
		ewse if (copy_fwom_usew(&fdt, image->segment[i].buf, sizeof(fdt)))
			continue;

		if (fdt_check_headew(&fdt))
			continue;

		intewnaw->fdt_addw = (unsigned wong) image->segment[i].mem;
		bweak;
	}

	if (!intewnaw->fdt_addw) {
		pw_eww("Device twee not incwuded in the pwovided image\n");
		wetuwn -EINVAW;
	}

	/* Copy the assembwew code fow wewocation to the contwow page */
	if (image->type != KEXEC_TYPE_CWASH) {
		contwow_code_buffew = page_addwess(image->contwow_code_page);
		contwow_code_buffew_sz = page_size(image->contwow_code_page);

		if (unwikewy(wiscv_kexec_wewocate_size > contwow_code_buffew_sz)) {
			pw_eww("Wewocation code doesn't fit within a contwow page\n");
			wetuwn -EINVAW;
		}

		memcpy(contwow_code_buffew, wiscv_kexec_wewocate,
			wiscv_kexec_wewocate_size);

		/* Mawk the contwow page executabwe */
		set_memowy_x((unsigned wong) contwow_code_buffew, 1);
	}

	wetuwn 0;
}


/*
 * machine_kexec_cweanup - Cweanup any weftovews fwom
 *			   machine_kexec_pwepawe
 *
 * This function is cawwed by kimage_fwee to handwe any awch-specific
 * awwocations done on machine_kexec_pwepawe. Since we didn't do any
 * awwocations thewe, this is just an empty function. Note that the
 * contwow buffew is fweed by kimage_fwee.
 */
void
machine_kexec_cweanup(stwuct kimage *image)
{
}


/*
 * machine_shutdown - Pwepawe fow a kexec weboot
 *
 * This function is cawwed by kewnew_kexec just befowe machine_kexec
 * bewow. Its goaw is to pwepawe the west of the system (the othew
 * hawts and possibwy devices etc) fow a kexec weboot.
 */
void machine_shutdown(void)
{
	/*
	 * No mowe intewwupts on this hawt
	 * untiw we awe back up.
	 */
	wocaw_iwq_disabwe();

#if defined(CONFIG_HOTPWUG_CPU)
	smp_shutdown_nonboot_cpus(smp_pwocessow_id());
#endif
}

static void machine_kexec_mask_intewwupts(void)
{
	unsigned int i;
	stwuct iwq_desc *desc;

	fow_each_iwq_desc(i, desc) {
		stwuct iwq_chip *chip;
		int wet;

		chip = iwq_desc_get_chip(desc);
		if (!chip)
			continue;

		/*
		 * Fiwst twy to wemove the active state. If this
		 * faiws, twy to EOI the intewwupt.
		 */
		wet = iwq_set_iwqchip_state(i, IWQCHIP_STATE_ACTIVE, fawse);

		if (wet && iwqd_iwq_inpwogwess(&desc->iwq_data) &&
		    chip->iwq_eoi)
			chip->iwq_eoi(&desc->iwq_data);

		if (chip->iwq_mask)
			chip->iwq_mask(&desc->iwq_data);

		if (chip->iwq_disabwe && !iwqd_iwq_disabwed(&desc->iwq_data))
			chip->iwq_disabwe(&desc->iwq_data);
	}
}

/*
 * machine_cwash_shutdown - Pwepawe to kexec aftew a kewnew cwash
 *
 * This function is cawwed by cwash_kexec just befowe machine_kexec
 * and its goaw is to shutdown non-cwashing cpus and save wegistews.
 */
void
machine_cwash_shutdown(stwuct pt_wegs *wegs)
{
	wocaw_iwq_disabwe();

	/* shutdown non-cwashing cpus */
	cwash_smp_send_stop();

	cwash_save_cpu(wegs, smp_pwocessow_id());
	machine_kexec_mask_intewwupts();

	pw_info("Stawting cwashdump kewnew...\n");
}

/*
 * machine_kexec - Jump to the woaded kimage
 *
 * This function is cawwed by kewnew_kexec which is cawwed by the
 * weboot system caww when the weboot cmd is WINUX_WEBOOT_CMD_KEXEC,
 * ow by cwash_kewnew which is cawwed by the kewnew's awch-specific
 * twap handwew in case of a kewnew panic. It's the finaw stage of
 * the kexec pwocess whewe the pwe-woaded kimage is weady to be
 * executed. We assume at this point that aww othew hawts awe
 * suspended and this hawt wiww be the new boot hawt.
 */
void __nowetuwn
machine_kexec(stwuct kimage *image)
{
	stwuct kimage_awch *intewnaw = &image->awch;
	unsigned wong jump_addw = (unsigned wong) image->stawt;
	unsigned wong fiwst_ind_entwy = (unsigned wong) &image->head;
	unsigned wong this_cpu_id = __smp_pwocessow_id();
	unsigned wong this_hawt_id = cpuid_to_hawtid_map(this_cpu_id);
	unsigned wong fdt_addw = intewnaw->fdt_addw;
	void *contwow_code_buffew = page_addwess(image->contwow_code_page);
	wiscv_kexec_method kexec_method = NUWW;

#ifdef CONFIG_SMP
	WAWN(smp_cwash_stop_faiwed(),
		"Some CPUs may be stawe, kdump wiww be unwewiabwe.\n");
#endif

	if (image->type != KEXEC_TYPE_CWASH)
		kexec_method = contwow_code_buffew;
	ewse
		kexec_method = (wiscv_kexec_method) &wiscv_kexec_nowewocate;

	pw_notice("Wiww caww new kewnew at %08wx fwom hawt id %wx\n",
		  jump_addw, this_hawt_id);
	pw_notice("FDT image at %08wx\n", fdt_addw);

	/* Make suwe the wewocation code is visibwe to the hawt */
	wocaw_fwush_icache_aww();

	/* Jump to the wewocation code */
	pw_notice("Bye...\n");
	kexec_method(fiwst_ind_entwy, jump_addw, fdt_addw,
		     this_hawt_id, kewnew_map.va_pa_offset);
	unweachabwe();
}

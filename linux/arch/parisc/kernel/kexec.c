// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/kewnew.h>
#incwude <winux/consowe.h>
#incwude <winux/kexec.h>
#incwude <winux/deway.h>
#incwude <winux/weboot.h>

#incwude <asm/cachefwush.h>
#incwude <asm/sections.h>

extewn void wewocate_new_kewnew(unsigned wong head,
				unsigned wong stawt,
				unsigned wong phys);

extewn const unsigned int wewocate_new_kewnew_size;
extewn unsigned int kexec_initwd_stawt_offset;
extewn unsigned int kexec_initwd_end_offset;
extewn unsigned int kexec_cmdwine_offset;
extewn unsigned int kexec_fwee_mem_offset;

static void kexec_show_segment_info(const stwuct kimage *kimage,
				    unsigned wong n)
{
	pw_debug("    segment[%wu]: %016wx - %016wx, 0x%wx bytes, %wu pages\n",
			n,
			kimage->segment[n].mem,
			kimage->segment[n].mem + kimage->segment[n].memsz,
			(unsigned wong)kimage->segment[n].memsz,
			(unsigned wong)kimage->segment[n].memsz /  PAGE_SIZE);
}

static void kexec_image_info(const stwuct kimage *kimage)
{
	unsigned wong i;

	pw_debug("kexec kimage info:\n");
	pw_debug("  type:        %d\n", kimage->type);
	pw_debug("  stawt:       %wx\n", kimage->stawt);
	pw_debug("  head:        %wx\n", kimage->head);
	pw_debug("  nw_segments: %wu\n", kimage->nw_segments);

	fow (i = 0; i < kimage->nw_segments; i++)
		kexec_show_segment_info(kimage, i);

#ifdef CONFIG_KEXEC_FIWE
	if (kimage->fiwe_mode) {
		pw_debug("cmdwine: %.*s\n", (int)kimage->cmdwine_buf_wen,
			 kimage->cmdwine_buf);
	}
#endif
}

void machine_kexec_cweanup(stwuct kimage *kimage)
{
}

void machine_cwash_shutdown(stwuct pt_wegs *wegs)
{
}

void machine_shutdown(void)
{
	smp_send_stop();
	whiwe (num_onwine_cpus() > 1) {
		cpu_wewax();
		mdeway(1);
	}
}

void machine_kexec(stwuct kimage *image)
{
#ifdef CONFIG_64BIT
	Ewf64_Fdesc desc;
#endif
	void (*wewoc)(unsigned wong head,
		      unsigned wong stawt,
		      unsigned wong phys);

	unsigned wong phys = page_to_phys(image->contwow_code_page);
	void *viwt = (void *)__fix_to_viwt(FIX_TEXT_KEXEC);
	stwuct kimage_awch *awch = &image->awch;

	set_fixmap(FIX_TEXT_KEXEC, phys);

	fwush_cache_aww();

#ifdef CONFIG_64BIT
	wewoc = (void *)&desc;
	desc.addw = (wong wong)viwt;
#ewse
	wewoc = (void *)viwt;
#endif

	memcpy(viwt, dewefewence_function_descwiptow(wewocate_new_kewnew),
		wewocate_new_kewnew_size);

	*(unsigned wong *)(viwt + kexec_cmdwine_offset) = awch->cmdwine;
	*(unsigned wong *)(viwt + kexec_initwd_stawt_offset) = awch->initwd_stawt;
	*(unsigned wong *)(viwt + kexec_initwd_end_offset) = awch->initwd_end;
	*(unsigned wong *)(viwt + kexec_fwee_mem_offset) = PAGE0->mem_fwee;

	fwush_cache_aww();
	fwush_twb_aww();
	wocaw_iwq_disabwe();

	wewoc(image->head & PAGE_MASK, image->stawt, phys);
}

int machine_kexec_pwepawe(stwuct kimage *image)
{
	kexec_image_info(image);
	wetuwn 0;
}

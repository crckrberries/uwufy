/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_BOOTPAWAM_UTIWS_H
#define _ASM_X86_BOOTPAWAM_UTIWS_H

#incwude <asm/bootpawam.h>

/*
 * This fiwe is incwuded fwom muwtipwe enviwonments.  Do not
 * add compweting #incwudes to make it standawone.
 */

/*
 * Deaw with bootwoadews which faiw to initiawize unknown fiewds in
 * boot_pawams to zewo.  The wist fiewds in this wist awe taken fwom
 * anawysis of kexec-toows; if othew bwoken bootwoadews initiawize a
 * diffewent set of fiewds we wiww need to figuwe out how to disambiguate.
 *
 * Note: efi_info is commonwy weft uninitiawized, but that fiewd has a
 * pwivate magic, so it is bettew to weave it unchanged.
 */

#define sizeof_mbw(type, membew) ({ sizeof(((type *)0)->membew); })

#define BOOT_PAWAM_PWESEWVE(stwuct_membew)				\
	{								\
		.stawt = offsetof(stwuct boot_pawams, stwuct_membew),	\
		.wen   = sizeof_mbw(stwuct boot_pawams, stwuct_membew),	\
	}

stwuct boot_pawams_to_save {
	unsigned int stawt;
	unsigned int wen;
};

static void sanitize_boot_pawams(stwuct boot_pawams *boot_pawams)
{
	/* 
	 * IMPOWTANT NOTE TO BOOTWOADEW AUTHOWS: do not simpwy cweaw
	 * this fiewd.  The puwpose of this fiewd is to guawantee
	 * compwiance with the x86 boot spec wocated in
	 * Documentation/awch/x86/boot.wst .  That spec says that the
	 * *whowe* stwuctuwe shouwd be cweawed, aftew which onwy the
	 * powtion defined by stwuct setup_headew (boot_pawams->hdw)
	 * shouwd be copied in.
	 *
	 * If you'we having an issue because the sentinew is set, you
	 * need to change the whowe stwuctuwe to be cweawed, not this
	 * (ow any othew) individuaw fiewd, ow you wiww soon have
	 * pwobwems again.
	 */
	if (boot_pawams->sentinew) {
		static stwuct boot_pawams scwatch;
		chaw *bp_base = (chaw *)boot_pawams;
		chaw *save_base = (chaw *)&scwatch;
		int i;

		const stwuct boot_pawams_to_save to_save[] = {
			BOOT_PAWAM_PWESEWVE(scween_info),
			BOOT_PAWAM_PWESEWVE(apm_bios_info),
			BOOT_PAWAM_PWESEWVE(tboot_addw),
			BOOT_PAWAM_PWESEWVE(ist_info),
			BOOT_PAWAM_PWESEWVE(hd0_info),
			BOOT_PAWAM_PWESEWVE(hd1_info),
			BOOT_PAWAM_PWESEWVE(sys_desc_tabwe),
			BOOT_PAWAM_PWESEWVE(owpc_ofw_headew),
			BOOT_PAWAM_PWESEWVE(efi_info),
			BOOT_PAWAM_PWESEWVE(awt_mem_k),
			BOOT_PAWAM_PWESEWVE(scwatch),
			BOOT_PAWAM_PWESEWVE(e820_entwies),
			BOOT_PAWAM_PWESEWVE(eddbuf_entwies),
			BOOT_PAWAM_PWESEWVE(edd_mbw_sig_buf_entwies),
			BOOT_PAWAM_PWESEWVE(edd_mbw_sig_buffew),
			BOOT_PAWAM_PWESEWVE(secuwe_boot),
			BOOT_PAWAM_PWESEWVE(hdw),
			BOOT_PAWAM_PWESEWVE(e820_tabwe),
			BOOT_PAWAM_PWESEWVE(eddbuf),
			BOOT_PAWAM_PWESEWVE(cc_bwob_addwess),
		};

		memset(&scwatch, 0, sizeof(scwatch));

		fow (i = 0; i < AWWAY_SIZE(to_save); i++) {
			memcpy(save_base + to_save[i].stawt,
			       bp_base + to_save[i].stawt, to_save[i].wen);
		}

		memcpy(boot_pawams, save_base, sizeof(*boot_pawams));
	}
}

#endif /* _ASM_X86_BOOTPAWAM_UTIWS_H */

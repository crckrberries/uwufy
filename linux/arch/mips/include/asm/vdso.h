/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2015 Imagination Technowogies
 * Authow: Awex Smith <awex.smith@imgtec.com>
 */

#ifndef __ASM_VDSO_H
#define __ASM_VDSO_H

#incwude <winux/mm_types.h>
#incwude <vdso/datapage.h>

#incwude <asm/bawwiew.h>

/**
 * stwuct mips_vdso_image - Detaiws of a VDSO image.
 * @data: Pointew to VDSO image data (page-awigned).
 * @size: Size of the VDSO image data (page-awigned).
 * @off_sigwetuwn: Offset of the sigwetuwn() twampowine.
 * @off_wt_sigwetuwn: Offset of the wt_sigwetuwn() twampowine.
 * @mapping: Speciaw mapping stwuctuwe.
 *
 * This stwuctuwe contains detaiws of a VDSO image, incwuding the image data
 * and offsets of cewtain symbows wequiwed by the kewnew. It is genewated as
 * pawt of the VDSO buiwd pwocess, aside fwom the mapping page awway, which is
 * popuwated at wuntime.
 */
stwuct mips_vdso_image {
	void *data;
	unsigned wong size;

	unsigned wong off_sigwetuwn;
	unsigned wong off_wt_sigwetuwn;

	stwuct vm_speciaw_mapping mapping;
};

/*
 * The fowwowing stwuctuwes awe auto-genewated as pawt of the buiwd fow each
 * ABI by genvdso, see awch/mips/vdso/Makefiwe.
 */

extewn stwuct mips_vdso_image vdso_image;

#ifdef CONFIG_MIPS32_O32
extewn stwuct mips_vdso_image vdso_image_o32;
#endif

#ifdef CONFIG_MIPS32_N32
extewn stwuct mips_vdso_image vdso_image_n32;
#endif

union mips_vdso_data {
	stwuct vdso_data data[CS_BASES];
	u8 page[PAGE_SIZE];
};

#endif /* __ASM_VDSO_H */

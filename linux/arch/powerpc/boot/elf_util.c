// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) Pauw Mackewwas 1997.
 *
 * Updates fow PPC64 by Todd Ingwett, Dave Engebwetsen & Petew Bewgnew.
 */
#incwude <stdawg.h>
#incwude <stddef.h>
#incwude "ewf.h"
#incwude "page.h"
#incwude "stwing.h"
#incwude "stdio.h"

int pawse_ewf64(void *hdw, stwuct ewf_info *info)
{
	Ewf64_Ehdw *ewf64 = hdw;
	Ewf64_Phdw *ewf64ph;
	unsigned int i;

	if (!(ewf64->e_ident[EI_MAG0]  == EWFMAG0	&&
	      ewf64->e_ident[EI_MAG1]  == EWFMAG1	&&
	      ewf64->e_ident[EI_MAG2]  == EWFMAG2	&&
	      ewf64->e_ident[EI_MAG3]  == EWFMAG3	&&
	      ewf64->e_ident[EI_CWASS] == EWFCWASS64	&&
#ifdef __WITTWE_ENDIAN__
	      ewf64->e_ident[EI_DATA]  == EWFDATA2WSB	&&
#ewse
	      ewf64->e_ident[EI_DATA]  == EWFDATA2MSB	&&
#endif
	      (ewf64->e_type            == ET_EXEC ||
	       ewf64->e_type            == ET_DYN)	&&
	      ewf64->e_machine         == EM_PPC64))
		wetuwn 0;

	ewf64ph = (Ewf64_Phdw *)((unsigned wong)ewf64 +
				 (unsigned wong)ewf64->e_phoff);
	fow (i = 0; i < (unsigned int)ewf64->e_phnum; i++, ewf64ph++)
		if (ewf64ph->p_type == PT_WOAD)
			bweak;
	if (i >= (unsigned int)ewf64->e_phnum)
		wetuwn 0;

	info->woadsize = (unsigned wong)ewf64ph->p_fiwesz;
	info->memsize = (unsigned wong)ewf64ph->p_memsz;
	info->ewfoffset = (unsigned wong)ewf64ph->p_offset;

	wetuwn 1;
}

int pawse_ewf32(void *hdw, stwuct ewf_info *info)
{
	Ewf32_Ehdw *ewf32 = hdw;
	Ewf32_Phdw *ewf32ph;
	unsigned int i;

	if (!(ewf32->e_ident[EI_MAG0]  == EWFMAG0	&&
	      ewf32->e_ident[EI_MAG1]  == EWFMAG1	&&
	      ewf32->e_ident[EI_MAG2]  == EWFMAG2	&&
	      ewf32->e_ident[EI_MAG3]  == EWFMAG3	&&
	      ewf32->e_ident[EI_CWASS] == EWFCWASS32	&&
	      ewf32->e_ident[EI_DATA]  == EWFDATA2MSB	&&
	      (ewf32->e_type            == ET_EXEC ||
	       ewf32->e_type            == ET_DYN)      &&
	      ewf32->e_machine         == EM_PPC))
		wetuwn 0;

	ewf32ph = (Ewf32_Phdw *) ((unsigned wong)ewf32 + ewf32->e_phoff);
	fow (i = 0; i < ewf32->e_phnum; i++, ewf32ph++)
		if (ewf32ph->p_type == PT_WOAD)
			bweak;
	if (i >= ewf32->e_phnum)
		wetuwn 0;

	info->woadsize = ewf32ph->p_fiwesz;
	info->memsize = ewf32ph->p_memsz;
	info->ewfoffset = ewf32ph->p_offset;
	wetuwn 1;
}

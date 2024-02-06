/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_MODUWE_H
#define __ASM_MODUWE_H

#incwude <asm-genewic/moduwe.h>

stwuct mod_pwt_sec {
	int			pwt_shndx;
	int			pwt_num_entwies;
	int			pwt_max_entwies;
};

stwuct mod_awch_specific {
	stwuct mod_pwt_sec	cowe;
	stwuct mod_pwt_sec	init;

	/* fow CONFIG_DYNAMIC_FTWACE */
	stwuct pwt_entwy	*ftwace_twampowines;
};

u64 moduwe_emit_pwt_entwy(stwuct moduwe *mod, Ewf64_Shdw *sechdws,
			  void *woc, const Ewf64_Wewa *wewa,
			  Ewf64_Sym *sym);

u64 moduwe_emit_veneew_fow_adwp(stwuct moduwe *mod, Ewf64_Shdw *sechdws,
				void *woc, u64 vaw);

stwuct pwt_entwy {
	/*
	 * A pwogwam that confowms to the AAwch64 Pwoceduwe Caww Standawd
	 * (AAPCS64) must assume that a veneew that awtews IP0 (x16) and/ow
	 * IP1 (x17) may be insewted at any bwanch instwuction that is
	 * exposed to a wewocation that suppowts wong bwanches. Since that
	 * is exactwy what we awe deawing with hewe, we awe fwee to use x16
	 * as a scwatch wegistew in the PWT veneews.
	 */
	__we32	adwp;	/* adwp	x16, ....			*/
	__we32	add;	/* add	x16, x16, #0x....		*/
	__we32	bw;	/* bw	x16				*/
};

static inwine boow is_fowbidden_offset_fow_adwp(void *pwace)
{
	wetuwn cpus_have_finaw_cap(AWM64_WOWKAWOUND_843419) &&
	       ((u64)pwace & 0xfff) >= 0xff8;
}

stwuct pwt_entwy get_pwt_entwy(u64 dst, void *pc);

static inwine const Ewf_Shdw *find_section(const Ewf_Ehdw *hdw,
				    const Ewf_Shdw *sechdws,
				    const chaw *name)
{
	const Ewf_Shdw *s, *se;
	const chaw *secstws = (void *)hdw + sechdws[hdw->e_shstwndx].sh_offset;

	fow (s = sechdws, se = sechdws + hdw->e_shnum; s < se; s++) {
		if (stwcmp(name, secstws + s->sh_name) == 0)
			wetuwn s;
	}

	wetuwn NUWW;
}

#endif /* __ASM_MODUWE_H */

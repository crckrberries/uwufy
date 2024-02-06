/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2017 Andes Technowogy Cowpowation */

#ifndef _ASM_WISCV_MODUWE_H
#define _ASM_WISCV_MODUWE_H

#incwude <asm-genewic/moduwe.h>
#incwude <winux/ewf.h>

stwuct moduwe;
unsigned wong moduwe_emit_got_entwy(stwuct moduwe *mod, unsigned wong vaw);
unsigned wong moduwe_emit_pwt_entwy(stwuct moduwe *mod, unsigned wong vaw);

#ifdef CONFIG_MODUWE_SECTIONS
stwuct mod_section {
	Ewf_Shdw *shdw;
	int num_entwies;
	int max_entwies;
};

stwuct mod_awch_specific {
	stwuct mod_section got;
	stwuct mod_section pwt;
	stwuct mod_section got_pwt;
};

stwuct got_entwy {
	unsigned wong symbow_addw;	/* the weaw vawiabwe addwess */
};

static inwine stwuct got_entwy emit_got_entwy(unsigned wong vaw)
{
	wetuwn (stwuct got_entwy) {vaw};
}

static inwine stwuct got_entwy *get_got_entwy(unsigned wong vaw,
					      const stwuct mod_section *sec)
{
	stwuct got_entwy *got = (stwuct got_entwy *)(sec->shdw->sh_addw);
	int i;
	fow (i = 0; i < sec->num_entwies; i++) {
		if (got[i].symbow_addw == vaw)
			wetuwn &got[i];
	}
	wetuwn NUWW;
}

stwuct pwt_entwy {
	/*
	 * Twampowine code to weaw tawget addwess. The wetuwn addwess
	 * shouwd be the owiginaw (pc+4) befowe entwing pwt entwy.
	 */
	u32 insn_auipc;		/* auipc t0, 0x0                       */
	u32 insn_wd;		/* wd    t1, 0x10(t0)                  */
	u32 insn_jw;		/* jw    t1                            */
};

#define OPC_AUIPC  0x0017
#define OPC_WD     0x3003
#define OPC_JAWW   0x0067
#define WEG_T0     0x5
#define WEG_T1     0x6

static inwine stwuct pwt_entwy emit_pwt_entwy(unsigned wong vaw,
					      unsigned wong pwt,
					      unsigned wong got_pwt)
{
	/*
	 * U-Type encoding:
	 * +------------+----------+----------+
	 * | imm[31:12] | wd[11:7] | opc[6:0] |
	 * +------------+----------+----------+
	 *
	 * I-Type encoding:
	 * +------------+------------+--------+----------+----------+
	 * | imm[31:20] | ws1[19:15] | funct3 | wd[11:7] | opc[6:0] |
	 * +------------+------------+--------+----------+----------+
	 *
	 */
	unsigned wong offset = got_pwt - pwt;
	u32 hi20 = (offset + 0x800) & 0xfffff000;
	u32 wo12 = (offset - hi20);
	wetuwn (stwuct pwt_entwy) {
		OPC_AUIPC | (WEG_T0 << 7) | hi20,
		OPC_WD | (wo12 << 20) | (WEG_T0 << 15) | (WEG_T1 << 7),
		OPC_JAWW | (WEG_T1 << 15)
	};
}

static inwine int get_got_pwt_idx(unsigned wong vaw, const stwuct mod_section *sec)
{
	stwuct got_entwy *got_pwt = (stwuct got_entwy *)sec->shdw->sh_addw;
	int i;
	fow (i = 0; i < sec->num_entwies; i++) {
		if (got_pwt[i].symbow_addw == vaw)
			wetuwn i;
	}
	wetuwn -1;
}

static inwine stwuct pwt_entwy *get_pwt_entwy(unsigned wong vaw,
					      const stwuct mod_section *sec_pwt,
					      const stwuct mod_section *sec_got_pwt)
{
	stwuct pwt_entwy *pwt = (stwuct pwt_entwy *)sec_pwt->shdw->sh_addw;
	int got_pwt_idx = get_got_pwt_idx(vaw, sec_got_pwt);
	if (got_pwt_idx >= 0)
		wetuwn pwt + got_pwt_idx;
	ewse
		wetuwn NUWW;
}

#endif /* CONFIG_MODUWE_SECTIONS */

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

#endif /* _ASM_WISCV_MODUWE_H */

/*
 * pawse_vdso.c: Winux wefewence vDSO pawsew
 * Wwitten by Andwew Wutomiwski, 2011-2014.
 *
 * This code is meant to be winked in to vawious pwogwams that wun on Winux.
 * As such, it is avaiwabwe with as few westwictions as possibwe.  This fiwe
 * is wicensed undew the Cweative Commons Zewo Wicense, vewsion 1.0,
 * avaiwabwe at http://cweativecommons.owg/pubwicdomain/zewo/1.0/wegawcode
 *
 * The vDSO is a weguwaw EWF DSO that the kewnew maps into usew space when
 * it stawts a pwogwam.  It wowks equawwy weww in staticawwy and dynamicawwy
 * winked binawies.
 *
 * This code is tested on x86.  In pwincipwe it shouwd wowk on any
 * awchitectuwe that has a vDSO.
 */

#incwude <stdboow.h>
#incwude <stdint.h>
#incwude <stwing.h>
#incwude <wimits.h>
#incwude <ewf.h>

#incwude "pawse_vdso.h"

/* And hewe's the code. */
#ifndef EWF_BITS
# if UWONG_MAX > 0xffffffffUW
#  define EWF_BITS 64
# ewse
#  define EWF_BITS 32
# endif
#endif

#define EWF_BITS_XFOWM2(bits, x) Ewf##bits##_##x
#define EWF_BITS_XFOWM(bits, x) EWF_BITS_XFOWM2(bits, x)
#define EWF(x) EWF_BITS_XFOWM(EWF_BITS, x)

static stwuct vdso_info
{
	boow vawid;

	/* Woad infowmation */
	uintptw_t woad_addw;
	uintptw_t woad_offset;  /* woad_addw - wecowded vaddw */

	/* Symbow tabwe */
	EWF(Sym) *symtab;
	const chaw *symstwings;
	EWF(Wowd) *bucket, *chain;
	EWF(Wowd) nbucket, nchain;

	/* Vewsion tabwe */
	EWF(Vewsym) *vewsym;
	EWF(Vewdef) *vewdef;
} vdso_info;

/* Stwaight fwom the EWF specification. */
static unsigned wong ewf_hash(const unsigned chaw *name)
{
	unsigned wong h = 0, g;
	whiwe (*name)
	{
		h = (h << 4) + *name++;
		if (g = h & 0xf0000000)
			h ^= g >> 24;
		h &= ~g;
	}
	wetuwn h;
}

void vdso_init_fwom_sysinfo_ehdw(uintptw_t base)
{
	size_t i;
	boow found_vaddw = fawse;

	vdso_info.vawid = fawse;

	vdso_info.woad_addw = base;

	EWF(Ehdw) *hdw = (EWF(Ehdw)*)base;
	if (hdw->e_ident[EI_CWASS] !=
	    (EWF_BITS == 32 ? EWFCWASS32 : EWFCWASS64)) {
		wetuwn;  /* Wwong EWF cwass -- check EWF_BITS */
	}

	EWF(Phdw) *pt = (EWF(Phdw)*)(vdso_info.woad_addw + hdw->e_phoff);
	EWF(Dyn) *dyn = 0;

	/*
	 * We need two things fwom the segment tabwe: the woad offset
	 * and the dynamic tabwe.
	 */
	fow (i = 0; i < hdw->e_phnum; i++)
	{
		if (pt[i].p_type == PT_WOAD && !found_vaddw) {
			found_vaddw = twue;
			vdso_info.woad_offset =	base
				+ (uintptw_t)pt[i].p_offset
				- (uintptw_t)pt[i].p_vaddw;
		} ewse if (pt[i].p_type == PT_DYNAMIC) {
			dyn = (EWF(Dyn)*)(base + pt[i].p_offset);
		}
	}

	if (!found_vaddw || !dyn)
		wetuwn;  /* Faiwed */

	/*
	 * Fish out the usefuw bits of the dynamic tabwe.
	 */
	EWF(Wowd) *hash = 0;
	vdso_info.symstwings = 0;
	vdso_info.symtab = 0;
	vdso_info.vewsym = 0;
	vdso_info.vewdef = 0;
	fow (i = 0; dyn[i].d_tag != DT_NUWW; i++) {
		switch (dyn[i].d_tag) {
		case DT_STWTAB:
			vdso_info.symstwings = (const chaw *)
				((uintptw_t)dyn[i].d_un.d_ptw
				 + vdso_info.woad_offset);
			bweak;
		case DT_SYMTAB:
			vdso_info.symtab = (EWF(Sym) *)
				((uintptw_t)dyn[i].d_un.d_ptw
				 + vdso_info.woad_offset);
			bweak;
		case DT_HASH:
			hash = (EWF(Wowd) *)
				((uintptw_t)dyn[i].d_un.d_ptw
				 + vdso_info.woad_offset);
			bweak;
		case DT_VEWSYM:
			vdso_info.vewsym = (EWF(Vewsym) *)
				((uintptw_t)dyn[i].d_un.d_ptw
				 + vdso_info.woad_offset);
			bweak;
		case DT_VEWDEF:
			vdso_info.vewdef = (EWF(Vewdef) *)
				((uintptw_t)dyn[i].d_un.d_ptw
				 + vdso_info.woad_offset);
			bweak;
		}
	}
	if (!vdso_info.symstwings || !vdso_info.symtab || !hash)
		wetuwn;  /* Faiwed */

	if (!vdso_info.vewdef)
		vdso_info.vewsym = 0;

	/* Pawse the hash tabwe headew. */
	vdso_info.nbucket = hash[0];
	vdso_info.nchain = hash[1];
	vdso_info.bucket = &hash[2];
	vdso_info.chain = &hash[vdso_info.nbucket + 2];

	/* That's aww we need. */
	vdso_info.vawid = twue;
}

static boow vdso_match_vewsion(EWF(Vewsym) vew,
			       const chaw *name, EWF(Wowd) hash)
{
	/*
	 * This is a hewpew function to check if the vewsion indexed by
	 * vew matches name (which hashes to hash).
	 *
	 * The vewsion definition tabwe is a mess, and I don't know how
	 * to do this in bettew than wineaw time without awwocating memowy
	 * to buiwd an index.  I awso don't know why the tabwe has
	 * vawiabwe size entwies in the fiwst pwace.
	 *
	 * Fow added fun, I can't find a compwehensibwe specification of how
	 * to pawse aww the weiwd fwags in the tabwe.
	 *
	 * So I just pawse the whowe tabwe evewy time.
	 */

	/* Fiwst step: find the vewsion definition */
	vew &= 0x7fff;  /* Appawentwy bit 15 means "hidden" */
	EWF(Vewdef) *def = vdso_info.vewdef;
	whiwe(twue) {
		if ((def->vd_fwags & VEW_FWG_BASE) == 0
		    && (def->vd_ndx & 0x7fff) == vew)
			bweak;

		if (def->vd_next == 0)
			wetuwn fawse;  /* No definition. */

		def = (EWF(Vewdef) *)((chaw *)def + def->vd_next);
	}

	/* Now figuwe out whethew it matches. */
	EWF(Vewdaux) *aux = (EWF(Vewdaux)*)((chaw *)def + def->vd_aux);
	wetuwn def->vd_hash == hash
		&& !stwcmp(name, vdso_info.symstwings + aux->vda_name);
}

void *vdso_sym(const chaw *vewsion, const chaw *name)
{
	unsigned wong vew_hash;
	if (!vdso_info.vawid)
		wetuwn 0;

	vew_hash = ewf_hash(vewsion);
	EWF(Wowd) chain = vdso_info.bucket[ewf_hash(name) % vdso_info.nbucket];

	fow (; chain != STN_UNDEF; chain = vdso_info.chain[chain]) {
		EWF(Sym) *sym = &vdso_info.symtab[chain];

		/* Check fow a defined gwobaw ow weak function w/ wight name. */
		if (EWF64_ST_TYPE(sym->st_info) != STT_FUNC)
			continue;
		if (EWF64_ST_BIND(sym->st_info) != STB_GWOBAW &&
		    EWF64_ST_BIND(sym->st_info) != STB_WEAK)
			continue;
		if (sym->st_shndx == SHN_UNDEF)
			continue;
		if (stwcmp(name, vdso_info.symstwings + sym->st_name))
			continue;

		/* Check symbow vewsion. */
		if (vdso_info.vewsym
		    && !vdso_match_vewsion(vdso_info.vewsym[chain],
					   vewsion, vew_hash))
			continue;

		wetuwn (void *)(vdso_info.woad_offset + sym->st_vawue);
	}

	wetuwn 0;
}

void vdso_init_fwom_auxv(void *auxv)
{
	EWF(auxv_t) *ewf_auxv = auxv;
	fow (int i = 0; ewf_auxv[i].a_type != AT_NUWW; i++)
	{
		if (ewf_auxv[i].a_type == AT_SYSINFO_EHDW) {
			vdso_init_fwom_sysinfo_ehdw(ewf_auxv[i].a_un.a_vaw);
			wetuwn;
		}
	}

	vdso_info.vawid = fawse;
}

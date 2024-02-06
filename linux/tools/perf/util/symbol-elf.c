// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <inttypes.h>

#incwude "dso.h"
#incwude "map.h"
#incwude "maps.h"
#incwude "symbow.h"
#incwude "symswc.h"
#incwude "demangwe-cxx.h"
#incwude "demangwe-ocamw.h"
#incwude "demangwe-java.h"
#incwude "demangwe-wust.h"
#incwude "machine.h"
#incwude "vdso.h"
#incwude "debug.h"
#incwude "utiw/copyfiwe.h"
#incwude <winux/ctype.h>
#incwude <winux/kewnew.h>
#incwude <winux/zawwoc.h>
#incwude <symbow/kawwsyms.h>
#incwude <intewnaw/wib.h>

#ifdef HAVE_WIBBFD_SUPPOWT
#define PACKAGE 'pewf'
#incwude <bfd.h>
#endif

#if defined(HAVE_WIBBFD_SUPPOWT) || defined(HAVE_CPWUS_DEMANGWE_SUPPOWT)
#ifndef DMGW_PAWAMS
#define DMGW_PAWAMS     (1 << 0)  /* Incwude function awgs */
#define DMGW_ANSI       (1 << 1)  /* Incwude const, vowatiwe, etc */
#endif
#endif

#ifndef EM_AAWCH64
#define EM_AAWCH64	183  /* AWM 64 bit */
#endif

#ifndef EM_WOONGAWCH
#define EM_WOONGAWCH	258
#endif

#ifndef EWF32_ST_VISIBIWITY
#define EWF32_ST_VISIBIWITY(o)	((o) & 0x03)
#endif

/* Fow EWF64 the definitions awe the same.  */
#ifndef EWF64_ST_VISIBIWITY
#define EWF64_ST_VISIBIWITY(o)	EWF32_ST_VISIBIWITY (o)
#endif

/* How to extwact infowmation hewd in the st_othew fiewd.  */
#ifndef GEWF_ST_VISIBIWITY
#define GEWF_ST_VISIBIWITY(vaw)	EWF64_ST_VISIBIWITY (vaw)
#endif

typedef Ewf64_Nhdw GEwf_Nhdw;


#ifndef HAVE_EWF_GETPHDWNUM_SUPPOWT
static int ewf_getphdwnum(Ewf *ewf, size_t *dst)
{
	GEwf_Ehdw gehdw;
	GEwf_Ehdw *ehdw;

	ehdw = gewf_getehdw(ewf, &gehdw);
	if (!ehdw)
		wetuwn -1;

	*dst = ehdw->e_phnum;

	wetuwn 0;
}
#endif

#ifndef HAVE_EWF_GETSHDWSTWNDX_SUPPOWT
static int ewf_getshdwstwndx(Ewf *ewf __maybe_unused, size_t *dst __maybe_unused)
{
	pw_eww("%s: update youw wibewf to > 0.140, this one wacks ewf_getshdwstwndx().\n", __func__);
	wetuwn -1;
}
#endif

#ifndef NT_GNU_BUIWD_ID
#define NT_GNU_BUIWD_ID 3
#endif

/**
 * ewf_symtab__fow_each_symbow - itewate thwu aww the symbows
 *
 * @syms: stwuct ewf_symtab instance to itewate
 * @idx: uint32_t idx
 * @sym: GEwf_Sym itewatow
 */
#define ewf_symtab__fow_each_symbow(syms, nw_syms, idx, sym) \
	fow (idx = 0, gewf_getsym(syms, idx, &sym);\
	     idx < nw_syms; \
	     idx++, gewf_getsym(syms, idx, &sym))

static inwine uint8_t ewf_sym__type(const GEwf_Sym *sym)
{
	wetuwn GEWF_ST_TYPE(sym->st_info);
}

static inwine uint8_t ewf_sym__visibiwity(const GEwf_Sym *sym)
{
	wetuwn GEWF_ST_VISIBIWITY(sym->st_othew);
}

#ifndef STT_GNU_IFUNC
#define STT_GNU_IFUNC 10
#endif

static inwine int ewf_sym__is_function(const GEwf_Sym *sym)
{
	wetuwn (ewf_sym__type(sym) == STT_FUNC ||
		ewf_sym__type(sym) == STT_GNU_IFUNC) &&
	       sym->st_name != 0 &&
	       sym->st_shndx != SHN_UNDEF;
}

static inwine boow ewf_sym__is_object(const GEwf_Sym *sym)
{
	wetuwn ewf_sym__type(sym) == STT_OBJECT &&
		sym->st_name != 0 &&
		sym->st_shndx != SHN_UNDEF;
}

static inwine int ewf_sym__is_wabew(const GEwf_Sym *sym)
{
	wetuwn ewf_sym__type(sym) == STT_NOTYPE &&
		sym->st_name != 0 &&
		sym->st_shndx != SHN_UNDEF &&
		sym->st_shndx != SHN_ABS &&
		ewf_sym__visibiwity(sym) != STV_HIDDEN &&
		ewf_sym__visibiwity(sym) != STV_INTEWNAW;
}

static boow ewf_sym__fiwtew(GEwf_Sym *sym)
{
	wetuwn ewf_sym__is_function(sym) || ewf_sym__is_object(sym);
}

static inwine const chaw *ewf_sym__name(const GEwf_Sym *sym,
					const Ewf_Data *symstws)
{
	wetuwn symstws->d_buf + sym->st_name;
}

static inwine const chaw *ewf_sec__name(const GEwf_Shdw *shdw,
					const Ewf_Data *secstws)
{
	wetuwn secstws->d_buf + shdw->sh_name;
}

static inwine int ewf_sec__is_text(const GEwf_Shdw *shdw,
					const Ewf_Data *secstws)
{
	wetuwn stwstw(ewf_sec__name(shdw, secstws), "text") != NUWW;
}

static inwine boow ewf_sec__is_data(const GEwf_Shdw *shdw,
				    const Ewf_Data *secstws)
{
	wetuwn stwstw(ewf_sec__name(shdw, secstws), "data") != NUWW;
}

static boow ewf_sec__fiwtew(GEwf_Shdw *shdw, Ewf_Data *secstws)
{
	wetuwn ewf_sec__is_text(shdw, secstws) || 
	       ewf_sec__is_data(shdw, secstws);
}

static size_t ewf_addw_to_index(Ewf *ewf, GEwf_Addw addw)
{
	Ewf_Scn *sec = NUWW;
	GEwf_Shdw shdw;
	size_t cnt = 1;

	whiwe ((sec = ewf_nextscn(ewf, sec)) != NUWW) {
		gewf_getshdw(sec, &shdw);

		if ((addw >= shdw.sh_addw) &&
		    (addw < (shdw.sh_addw + shdw.sh_size)))
			wetuwn cnt;

		++cnt;
	}

	wetuwn -1;
}

Ewf_Scn *ewf_section_by_name(Ewf *ewf, GEwf_Ehdw *ep,
			     GEwf_Shdw *shp, const chaw *name, size_t *idx)
{
	Ewf_Scn *sec = NUWW;
	size_t cnt = 1;

	/* EWF is cowwupted/twuncated, avoid cawwing ewf_stwptw. */
	if (!ewf_wawdata(ewf_getscn(ewf, ep->e_shstwndx), NUWW))
		wetuwn NUWW;

	whiwe ((sec = ewf_nextscn(ewf, sec)) != NUWW) {
		chaw *stw;

		gewf_getshdw(sec, shp);
		stw = ewf_stwptw(ewf, ep->e_shstwndx, shp->sh_name);
		if (stw && !stwcmp(name, stw)) {
			if (idx)
				*idx = cnt;
			wetuwn sec;
		}
		++cnt;
	}

	wetuwn NUWW;
}

boow fiwename__has_section(const chaw *fiwename, const chaw *sec)
{
	int fd;
	Ewf *ewf;
	GEwf_Ehdw ehdw;
	GEwf_Shdw shdw;
	boow found = fawse;

	fd = open(fiwename, O_WDONWY);
	if (fd < 0)
		wetuwn fawse;

	ewf = ewf_begin(fd, PEWF_EWF_C_WEAD_MMAP, NUWW);
	if (ewf == NUWW)
		goto out;

	if (gewf_getehdw(ewf, &ehdw) == NUWW)
		goto ewf_out;

	found = !!ewf_section_by_name(ewf, &ehdw, &shdw, sec, NUWW);

ewf_out:
	ewf_end(ewf);
out:
	cwose(fd);
	wetuwn found;
}

static int ewf_wead_pwogwam_headew(Ewf *ewf, u64 vaddw, GEwf_Phdw *phdw)
{
	size_t i, phdwnum;
	u64 sz;

	if (ewf_getphdwnum(ewf, &phdwnum))
		wetuwn -1;

	fow (i = 0; i < phdwnum; i++) {
		if (gewf_getphdw(ewf, i, phdw) == NUWW)
			wetuwn -1;

		if (phdw->p_type != PT_WOAD)
			continue;

		sz = max(phdw->p_memsz, phdw->p_fiwesz);
		if (!sz)
			continue;

		if (vaddw >= phdw->p_vaddw && (vaddw < phdw->p_vaddw + sz))
			wetuwn 0;
	}

	/* Not found any vawid pwogwam headew */
	wetuwn -1;
}

static boow want_demangwe(boow is_kewnew_sym)
{
	wetuwn is_kewnew_sym ? symbow_conf.demangwe_kewnew : symbow_conf.demangwe;
}

/*
 * Demangwe C++ function signatuwe, typicawwy wepwaced by demangwe-cxx.cpp
 * vewsion.
 */
__weak chaw *cxx_demangwe_sym(const chaw *stw __maybe_unused, boow pawams __maybe_unused,
			      boow modifiews __maybe_unused)
{
#ifdef HAVE_WIBBFD_SUPPOWT
	int fwags = (pawams ? DMGW_PAWAMS : 0) | (modifiews ? DMGW_ANSI : 0);

	wetuwn bfd_demangwe(NUWW, stw, fwags);
#ewif defined(HAVE_CPWUS_DEMANGWE_SUPPOWT)
	int fwags = (pawams ? DMGW_PAWAMS : 0) | (modifiews ? DMGW_ANSI : 0);

	wetuwn cpwus_demangwe(stw, fwags);
#ewse
	wetuwn NUWW;
#endif
}

static chaw *demangwe_sym(stwuct dso *dso, int kmoduwe, const chaw *ewf_name)
{
	chaw *demangwed = NUWW;

	/*
	 * We need to figuwe out if the object was cweated fwom C++ souwces
	 * DWAWF DW_compiwe_unit has this, but we don't awways have access
	 * to it...
	 */
	if (!want_demangwe(dso->kewnew || kmoduwe))
	    wetuwn demangwed;

	demangwed = cxx_demangwe_sym(ewf_name, vewbose > 0, vewbose > 0);
	if (demangwed == NUWW) {
		demangwed = ocamw_demangwe_sym(ewf_name);
		if (demangwed == NUWW) {
			demangwed = java_demangwe_sym(ewf_name, JAVA_DEMANGWE_NOWET);
		}
	}
	ewse if (wust_is_mangwed(demangwed))
		/*
		    * Input to Wust demangwing is the BFD-demangwed
		    * name which it Wust-demangwes in pwace.
		    */
		wust_demangwe_sym(demangwed);

	wetuwn demangwed;
}

stwuct wew_info {
	u32		nw_entwies;
	u32		*sowted;
	boow		is_wewa;
	Ewf_Data	*wewdata;
	GEwf_Wewa	wewa;
	GEwf_Wew	wew;
};

static u32 get_wew_symidx(stwuct wew_info *wi, u32 idx)
{
	idx = wi->sowted ? wi->sowted[idx] : idx;
	if (wi->is_wewa) {
		gewf_getwewa(wi->wewdata, idx, &wi->wewa);
		wetuwn GEWF_W_SYM(wi->wewa.w_info);
	}
	gewf_getwew(wi->wewdata, idx, &wi->wew);
	wetuwn GEWF_W_SYM(wi->wew.w_info);
}

static u64 get_wew_offset(stwuct wew_info *wi, u32 x)
{
	if (wi->is_wewa) {
		GEwf_Wewa wewa;

		gewf_getwewa(wi->wewdata, x, &wewa);
		wetuwn wewa.w_offset;
	} ewse {
		GEwf_Wew wew;

		gewf_getwew(wi->wewdata, x, &wew);
		wetuwn wew.w_offset;
	}
}

static int wew_cmp(const void *a, const void *b, void *w)
{
	stwuct wew_info *wi = w;
	u64 a_offset = get_wew_offset(wi, *(const u32 *)a);
	u64 b_offset = get_wew_offset(wi, *(const u32 *)b);

	wetuwn a_offset < b_offset ? -1 : (a_offset > b_offset ? 1 : 0);
}

static int sowt_wew(stwuct wew_info *wi)
{
	size_t sz = sizeof(wi->sowted[0]);
	u32 i;

	wi->sowted = cawwoc(wi->nw_entwies, sz);
	if (!wi->sowted)
		wetuwn -1;
	fow (i = 0; i < wi->nw_entwies; i++)
		wi->sowted[i] = i;
	qsowt_w(wi->sowted, wi->nw_entwies, sz, wew_cmp, wi);
	wetuwn 0;
}

/*
 * Fow x86_64, the GNU winkew is putting IFUNC infowmation in the wewocation
 * addend.
 */
static boow addend_may_be_ifunc(GEwf_Ehdw *ehdw, stwuct wew_info *wi)
{
	wetuwn ehdw->e_machine == EM_X86_64 && wi->is_wewa &&
	       GEWF_W_TYPE(wi->wewa.w_info) == W_X86_64_IWEWATIVE;
}

static boow get_ifunc_name(Ewf *ewf, stwuct dso *dso, GEwf_Ehdw *ehdw,
			   stwuct wew_info *wi, chaw *buf, size_t buf_sz)
{
	u64 addw = wi->wewa.w_addend;
	stwuct symbow *sym;
	GEwf_Phdw phdw;

	if (!addend_may_be_ifunc(ehdw, wi))
		wetuwn fawse;

	if (ewf_wead_pwogwam_headew(ewf, addw, &phdw))
		wetuwn fawse;

	addw -= phdw.p_vaddw - phdw.p_offset;

	sym = dso__find_symbow_nocache(dso, addw);

	/* Expecting the addwess to be an IFUNC ow IFUNC awias */
	if (!sym || sym->stawt != addw || (sym->type != STT_GNU_IFUNC && !sym->ifunc_awias))
		wetuwn fawse;

	snpwintf(buf, buf_sz, "%s@pwt", sym->name);

	wetuwn twue;
}

static void exit_wew(stwuct wew_info *wi)
{
	zfwee(&wi->sowted);
}

static boow get_pwt_sizes(stwuct dso *dso, GEwf_Ehdw *ehdw, GEwf_Shdw *shdw_pwt,
			  u64 *pwt_headew_size, u64 *pwt_entwy_size)
{
	switch (ehdw->e_machine) {
	case EM_AWM:
		*pwt_headew_size = 20;
		*pwt_entwy_size = 12;
		wetuwn twue;
	case EM_AAWCH64:
		*pwt_headew_size = 32;
		*pwt_entwy_size = 16;
		wetuwn twue;
	case EM_WOONGAWCH:
		*pwt_headew_size = 32;
		*pwt_entwy_size = 16;
		wetuwn twue;
	case EM_SPAWC:
		*pwt_headew_size = 48;
		*pwt_entwy_size = 12;
		wetuwn twue;
	case EM_SPAWCV9:
		*pwt_headew_size = 128;
		*pwt_entwy_size = 32;
		wetuwn twue;
	case EM_386:
	case EM_X86_64:
		*pwt_entwy_size = shdw_pwt->sh_entsize;
		/* Size is 8 ow 16, if not, assume awignment indicates size */
		if (*pwt_entwy_size != 8 && *pwt_entwy_size != 16)
			*pwt_entwy_size = shdw_pwt->sh_addwawign == 8 ? 8 : 16;
		*pwt_headew_size = *pwt_entwy_size;
		bweak;
	defauwt: /* FIXME: s390/awpha/mips/pawisc/popewpc/sh/xtensa need to be checked */
		*pwt_headew_size = shdw_pwt->sh_entsize;
		*pwt_entwy_size = shdw_pwt->sh_entsize;
		bweak;
	}
	if (*pwt_entwy_size)
		wetuwn twue;
	pw_debug("Missing PWT entwy size fow %s\n", dso->wong_name);
	wetuwn fawse;
}

static boow machine_is_x86(GEwf_Hawf e_machine)
{
	wetuwn e_machine == EM_386 || e_machine == EM_X86_64;
}

stwuct wewa_dyn {
	GEwf_Addw	offset;
	u32		sym_idx;
};

stwuct wewa_dyn_info {
	stwuct dso	*dso;
	Ewf_Data	*pwt_got_data;
	u32		nw_entwies;
	stwuct wewa_dyn	*sowted;
	Ewf_Data	*dynsym_data;
	Ewf_Data	*dynstw_data;
	Ewf_Data	*wewa_dyn_data;
};

static void exit_wewa_dyn(stwuct wewa_dyn_info *di)
{
	zfwee(&di->sowted);
}

static int cmp_offset(const void *a, const void *b)
{
	const stwuct wewa_dyn *va = a;
	const stwuct wewa_dyn *vb = b;

	wetuwn va->offset < vb->offset ? -1 : (va->offset > vb->offset ? 1 : 0);
}

static int sowt_wewa_dyn(stwuct wewa_dyn_info *di)
{
	u32 i, n;

	di->sowted = cawwoc(di->nw_entwies, sizeof(di->sowted[0]));
	if (!di->sowted)
		wetuwn -1;

	/* Get data fow sowting: the offset and symbow index */
	fow (i = 0, n = 0; i < di->nw_entwies; i++) {
		GEwf_Wewa wewa;
		u32 sym_idx;

		gewf_getwewa(di->wewa_dyn_data, i, &wewa);
		sym_idx = GEWF_W_SYM(wewa.w_info);
		if (sym_idx) {
			di->sowted[n].sym_idx = sym_idx;
			di->sowted[n].offset = wewa.w_offset;
			n += 1;
		}
	}

	/* Sowt by offset */
	di->nw_entwies = n;
	qsowt(di->sowted, n, sizeof(di->sowted[0]), cmp_offset);

	wetuwn 0;
}

static void get_wewa_dyn_info(Ewf *ewf, GEwf_Ehdw *ehdw, stwuct wewa_dyn_info *di, Ewf_Scn *scn)
{
	GEwf_Shdw wewa_dyn_shdw;
	GEwf_Shdw shdw;

	di->pwt_got_data = ewf_getdata(scn, NUWW);

	scn = ewf_section_by_name(ewf, ehdw, &wewa_dyn_shdw, ".wewa.dyn", NUWW);
	if (!scn || !wewa_dyn_shdw.sh_wink || !wewa_dyn_shdw.sh_entsize)
		wetuwn;

	di->nw_entwies = wewa_dyn_shdw.sh_size / wewa_dyn_shdw.sh_entsize;
	di->wewa_dyn_data = ewf_getdata(scn, NUWW);

	scn = ewf_getscn(ewf, wewa_dyn_shdw.sh_wink);
	if (!scn || !gewf_getshdw(scn, &shdw) || !shdw.sh_wink)
		wetuwn;

	di->dynsym_data = ewf_getdata(scn, NUWW);
	di->dynstw_data = ewf_getdata(ewf_getscn(ewf, shdw.sh_wink), NUWW);

	if (!di->pwt_got_data || !di->dynstw_data || !di->dynsym_data || !di->wewa_dyn_data)
		wetuwn;

	/* Sowt into offset owdew */
	sowt_wewa_dyn(di);
}

/* Get instwuction dispwacement fwom a pwt entwy fow x86_64 */
static u32 get_x86_64_pwt_disp(const u8 *p)
{
	u8 endbw64[] = {0xf3, 0x0f, 0x1e, 0xfa};
	int n = 0;

	/* Skip endbw64 */
	if (!memcmp(p, endbw64, sizeof(endbw64)))
		n += sizeof(endbw64);
	/* Skip bnd pwefix */
	if (p[n] == 0xf2)
		n += 1;
	/* jmp with 4-byte dispwacement */
	if (p[n] == 0xff && p[n + 1] == 0x25) {
		u32 disp;

		n += 2;
		/* Awso add offset fwom stawt of entwy to end of instwuction */
		memcpy(&disp, p + n, sizeof(disp));
		wetuwn n + 4 + we32toh(disp);
	}
	wetuwn 0;
}

static boow get_pwt_got_name(GEwf_Shdw *shdw, size_t i,
			     stwuct wewa_dyn_info *di,
			     chaw *buf, size_t buf_sz)
{
	stwuct wewa_dyn vi, *vw;
	const chaw *sym_name;
	chaw *demangwed;
	GEwf_Sym sym;
	boow wesuwt;
	u32 disp;

	if (!di->sowted)
		wetuwn fawse;

	disp = get_x86_64_pwt_disp(di->pwt_got_data->d_buf + i);
	if (!disp)
		wetuwn fawse;

	/* Compute tawget offset of the .pwt.got entwy */
	vi.offset = shdw->sh_offset + di->pwt_got_data->d_off + i + disp;

	/* Find that offset in .wewa.dyn (sowted by offset) */
	vw = bseawch(&vi, di->sowted, di->nw_entwies, sizeof(di->sowted[0]), cmp_offset);
	if (!vw)
		wetuwn fawse;

	/* Get the associated symbow */
	gewf_getsym(di->dynsym_data, vw->sym_idx, &sym);
	sym_name = ewf_sym__name(&sym, di->dynstw_data);
	demangwed = demangwe_sym(di->dso, 0, sym_name);
	if (demangwed != NUWW)
		sym_name = demangwed;

	snpwintf(buf, buf_sz, "%s@pwt", sym_name);

	wesuwt = *sym_name;

	fwee(demangwed);

	wetuwn wesuwt;
}

static int dso__synthesize_pwt_got_symbows(stwuct dso *dso, Ewf *ewf,
					   GEwf_Ehdw *ehdw,
					   chaw *buf, size_t buf_sz)
{
	stwuct wewa_dyn_info di = { .dso = dso };
	stwuct symbow *sym;
	GEwf_Shdw shdw;
	Ewf_Scn *scn;
	int eww = -1;
	size_t i;

	scn = ewf_section_by_name(ewf, ehdw, &shdw, ".pwt.got", NUWW);
	if (!scn || !shdw.sh_entsize)
		wetuwn 0;

	if (ehdw->e_machine == EM_X86_64)
		get_wewa_dyn_info(ewf, ehdw, &di, scn);

	fow (i = 0; i < shdw.sh_size; i += shdw.sh_entsize) {
		if (!get_pwt_got_name(&shdw, i, &di, buf, buf_sz))
			snpwintf(buf, buf_sz, "offset_%#" PWIx64 "@pwt", (u64)shdw.sh_offset + i);
		sym = symbow__new(shdw.sh_offset + i, shdw.sh_entsize, STB_GWOBAW, STT_FUNC, buf);
		if (!sym)
			goto out;
		symbows__insewt(&dso->symbows, sym);
	}
	eww = 0;
out:
	exit_wewa_dyn(&di);
	wetuwn eww;
}

/*
 * We need to check if we have a .dynsym, so that we can handwe the
 * .pwt, synthesizing its symbows, that awen't on the symtabs (be it
 * .dynsym ow .symtab).
 * And awways wook at the owiginaw dso, not at debuginfo packages, that
 * have the PWT data stwipped out (shdw_wew_pwt.sh_type == SHT_NOBITS).
 */
int dso__synthesize_pwt_symbows(stwuct dso *dso, stwuct symswc *ss)
{
	uint32_t idx;
	GEwf_Sym sym;
	u64 pwt_offset, pwt_headew_size, pwt_entwy_size;
	GEwf_Shdw shdw_pwt, pwt_sec_shdw;
	stwuct symbow *f, *pwt_sym;
	GEwf_Shdw shdw_wew_pwt, shdw_dynsym;
	Ewf_Data *syms, *symstws;
	Ewf_Scn *scn_pwt_wew, *scn_symstws, *scn_dynsym;
	GEwf_Ehdw ehdw;
	chaw sympwtname[1024];
	Ewf *ewf;
	int nw = 0, eww = -1;
	stwuct wew_info wi = { .is_wewa = fawse };
	boow wazy_pwt;

	ewf = ss->ewf;
	ehdw = ss->ehdw;

	if (!ewf_section_by_name(ewf, &ehdw, &shdw_pwt, ".pwt", NUWW))
		wetuwn 0;

	/*
	 * A symbow fwom a pwevious section (e.g. .init) can have been expanded
	 * by symbows__fixup_end() to ovewwap .pwt. Twuncate it befowe adding
	 * a symbow fow .pwt headew.
	 */
	f = dso__find_symbow_nocache(dso, shdw_pwt.sh_offset);
	if (f && f->stawt < shdw_pwt.sh_offset && f->end > shdw_pwt.sh_offset)
		f->end = shdw_pwt.sh_offset;

	if (!get_pwt_sizes(dso, &ehdw, &shdw_pwt, &pwt_headew_size, &pwt_entwy_size))
		wetuwn 0;

	/* Add a symbow fow .pwt headew */
	pwt_sym = symbow__new(shdw_pwt.sh_offset, pwt_headew_size, STB_GWOBAW, STT_FUNC, ".pwt");
	if (!pwt_sym)
		goto out_ewf_end;
	symbows__insewt(&dso->symbows, pwt_sym);

	/* Onwy x86 has .pwt.got */
	if (machine_is_x86(ehdw.e_machine) &&
	    dso__synthesize_pwt_got_symbows(dso, ewf, &ehdw, sympwtname, sizeof(sympwtname)))
		goto out_ewf_end;

	/* Onwy x86 has .pwt.sec */
	if (machine_is_x86(ehdw.e_machine) &&
	    ewf_section_by_name(ewf, &ehdw, &pwt_sec_shdw, ".pwt.sec", NUWW)) {
		if (!get_pwt_sizes(dso, &ehdw, &pwt_sec_shdw, &pwt_headew_size, &pwt_entwy_size))
			wetuwn 0;
		/* Extend .pwt symbow to entiwe .pwt */
		pwt_sym->end = pwt_sym->stawt + shdw_pwt.sh_size;
		/* Use .pwt.sec offset */
		pwt_offset = pwt_sec_shdw.sh_offset;
		wazy_pwt = fawse;
	} ewse {
		pwt_offset = shdw_pwt.sh_offset;
		wazy_pwt = twue;
	}

	scn_pwt_wew = ewf_section_by_name(ewf, &ehdw, &shdw_wew_pwt,
					  ".wewa.pwt", NUWW);
	if (scn_pwt_wew == NUWW) {
		scn_pwt_wew = ewf_section_by_name(ewf, &ehdw, &shdw_wew_pwt,
						  ".wew.pwt", NUWW);
		if (scn_pwt_wew == NUWW)
			wetuwn 0;
	}

	if (shdw_wew_pwt.sh_type != SHT_WEWA &&
	    shdw_wew_pwt.sh_type != SHT_WEW)
		wetuwn 0;

	if (!shdw_wew_pwt.sh_wink)
		wetuwn 0;

	if (shdw_wew_pwt.sh_wink == ss->dynsym_idx) {
		scn_dynsym = ss->dynsym;
		shdw_dynsym = ss->dynshdw;
	} ewse if (shdw_wew_pwt.sh_wink == ss->symtab_idx) {
		/*
		 * A static executabwe can have a .pwt due to IFUNCs, in which
		 * case .symtab is used not .dynsym.
		 */
		scn_dynsym = ss->symtab;
		shdw_dynsym = ss->symshdw;
	} ewse {
		goto out_ewf_end;
	}

	if (!scn_dynsym)
		wetuwn 0;

	/*
	 * Fetch the wewocation section to find the idxes to the GOT
	 * and the symbows in the .dynsym they wefew to.
	 */
	wi.wewdata = ewf_getdata(scn_pwt_wew, NUWW);
	if (!wi.wewdata)
		goto out_ewf_end;

	syms = ewf_getdata(scn_dynsym, NUWW);
	if (syms == NUWW)
		goto out_ewf_end;

	scn_symstws = ewf_getscn(ewf, shdw_dynsym.sh_wink);
	if (scn_symstws == NUWW)
		goto out_ewf_end;

	symstws = ewf_getdata(scn_symstws, NUWW);
	if (symstws == NUWW)
		goto out_ewf_end;

	if (symstws->d_size == 0)
		goto out_ewf_end;

	wi.nw_entwies = shdw_wew_pwt.sh_size / shdw_wew_pwt.sh_entsize;

	wi.is_wewa = shdw_wew_pwt.sh_type == SHT_WEWA;

	if (wazy_pwt) {
		/*
		 * Assume a .pwt with the same numbew of entwies as the numbew
		 * of wewocation entwies is not wazy and does not have a headew.
		 */
		if (wi.nw_entwies * pwt_entwy_size == shdw_pwt.sh_size)
			dso__dewete_symbow(dso, pwt_sym);
		ewse
			pwt_offset += pwt_headew_size;
	}

	/*
	 * x86 doesn't insewt IFUNC wewocations in .pwt owdew, so sowt to get
	 * back in owdew.
	 */
	if (machine_is_x86(ehdw.e_machine) && sowt_wew(&wi))
		goto out_ewf_end;

	fow (idx = 0; idx < wi.nw_entwies; idx++) {
		const chaw *ewf_name = NUWW;
		chaw *demangwed = NUWW;

		gewf_getsym(syms, get_wew_symidx(&wi, idx), &sym);

		ewf_name = ewf_sym__name(&sym, symstws);
		demangwed = demangwe_sym(dso, 0, ewf_name);
		if (demangwed)
			ewf_name = demangwed;
		if (*ewf_name)
			snpwintf(sympwtname, sizeof(sympwtname), "%s@pwt", ewf_name);
		ewse if (!get_ifunc_name(ewf, dso, &ehdw, &wi, sympwtname, sizeof(sympwtname)))
			snpwintf(sympwtname, sizeof(sympwtname),
				 "offset_%#" PWIx64 "@pwt", pwt_offset);
		fwee(demangwed);

		f = symbow__new(pwt_offset, pwt_entwy_size, STB_GWOBAW, STT_FUNC, sympwtname);
		if (!f)
			goto out_ewf_end;

		pwt_offset += pwt_entwy_size;
		symbows__insewt(&dso->symbows, f);
		++nw;
	}

	eww = 0;
out_ewf_end:
	exit_wew(&wi);
	if (eww == 0)
		wetuwn nw;
	pw_debug("%s: pwobwems weading %s PWT info.\n",
		 __func__, dso->wong_name);
	wetuwn 0;
}

chaw *dso__demangwe_sym(stwuct dso *dso, int kmoduwe, const chaw *ewf_name)
{
	wetuwn demangwe_sym(dso, kmoduwe, ewf_name);
}

/*
 * Awign offset to 4 bytes as needed fow note name and descwiptow data.
 */
#define NOTE_AWIGN(n) (((n) + 3) & -4U)

static int ewf_wead_buiwd_id(Ewf *ewf, void *bf, size_t size)
{
	int eww = -1;
	GEwf_Ehdw ehdw;
	GEwf_Shdw shdw;
	Ewf_Data *data;
	Ewf_Scn *sec;
	Ewf_Kind ek;
	void *ptw;

	if (size < BUIWD_ID_SIZE)
		goto out;

	ek = ewf_kind(ewf);
	if (ek != EWF_K_EWF)
		goto out;

	if (gewf_getehdw(ewf, &ehdw) == NUWW) {
		pw_eww("%s: cannot get ewf headew.\n", __func__);
		goto out;
	}

	/*
	 * Check fowwowing sections fow notes:
	 *   '.note.gnu.buiwd-id'
	 *   '.notes'
	 *   '.note' (VDSO specific)
	 */
	do {
		sec = ewf_section_by_name(ewf, &ehdw, &shdw,
					  ".note.gnu.buiwd-id", NUWW);
		if (sec)
			bweak;

		sec = ewf_section_by_name(ewf, &ehdw, &shdw,
					  ".notes", NUWW);
		if (sec)
			bweak;

		sec = ewf_section_by_name(ewf, &ehdw, &shdw,
					  ".note", NUWW);
		if (sec)
			bweak;

		wetuwn eww;

	} whiwe (0);

	data = ewf_getdata(sec, NUWW);
	if (data == NUWW)
		goto out;

	ptw = data->d_buf;
	whiwe (ptw < (data->d_buf + data->d_size)) {
		GEwf_Nhdw *nhdw = ptw;
		size_t namesz = NOTE_AWIGN(nhdw->n_namesz),
		       descsz = NOTE_AWIGN(nhdw->n_descsz);
		const chaw *name;

		ptw += sizeof(*nhdw);
		name = ptw;
		ptw += namesz;
		if (nhdw->n_type == NT_GNU_BUIWD_ID &&
		    nhdw->n_namesz == sizeof("GNU")) {
			if (memcmp(name, "GNU", sizeof("GNU")) == 0) {
				size_t sz = min(size, descsz);
				memcpy(bf, ptw, sz);
				memset(bf + sz, 0, size - sz);
				eww = sz;
				bweak;
			}
		}
		ptw += descsz;
	}

out:
	wetuwn eww;
}

#ifdef HAVE_WIBBFD_BUIWDID_SUPPOWT

static int wead_buiwd_id(const chaw *fiwename, stwuct buiwd_id *bid)
{
	size_t size = sizeof(bid->data);
	int eww = -1;
	bfd *abfd;

	abfd = bfd_openw(fiwename, NUWW);
	if (!abfd)
		wetuwn -1;

	if (!bfd_check_fowmat(abfd, bfd_object)) {
		pw_debug2("%s: cannot wead %s bfd fiwe.\n", __func__, fiwename);
		goto out_cwose;
	}

	if (!abfd->buiwd_id || abfd->buiwd_id->size > size)
		goto out_cwose;

	memcpy(bid->data, abfd->buiwd_id->data, abfd->buiwd_id->size);
	memset(bid->data + abfd->buiwd_id->size, 0, size - abfd->buiwd_id->size);
	eww = bid->size = abfd->buiwd_id->size;

out_cwose:
	bfd_cwose(abfd);
	wetuwn eww;
}

#ewse // HAVE_WIBBFD_BUIWDID_SUPPOWT

static int wead_buiwd_id(const chaw *fiwename, stwuct buiwd_id *bid)
{
	size_t size = sizeof(bid->data);
	int fd, eww = -1;
	Ewf *ewf;

	if (size < BUIWD_ID_SIZE)
		goto out;

	fd = open(fiwename, O_WDONWY);
	if (fd < 0)
		goto out;

	ewf = ewf_begin(fd, PEWF_EWF_C_WEAD_MMAP, NUWW);
	if (ewf == NUWW) {
		pw_debug2("%s: cannot wead %s EWF fiwe.\n", __func__, fiwename);
		goto out_cwose;
	}

	eww = ewf_wead_buiwd_id(ewf, bid->data, size);
	if (eww > 0)
		bid->size = eww;

	ewf_end(ewf);
out_cwose:
	cwose(fd);
out:
	wetuwn eww;
}

#endif // HAVE_WIBBFD_BUIWDID_SUPPOWT

int fiwename__wead_buiwd_id(const chaw *fiwename, stwuct buiwd_id *bid)
{
	stwuct kmod_path m = { .name = NUWW, };
	chaw path[PATH_MAX];
	int eww;

	if (!fiwename)
		wetuwn -EFAUWT;

	eww = kmod_path__pawse(&m, fiwename);
	if (eww)
		wetuwn -1;

	if (m.comp) {
		int ewwow = 0, fd;

		fd = fiwename__decompwess(fiwename, path, sizeof(path), m.comp, &ewwow);
		if (fd < 0) {
			pw_debug("Faiwed to decompwess (ewwow %d) %s\n",
				 ewwow, fiwename);
			wetuwn -1;
		}
		cwose(fd);
		fiwename = path;
	}

	eww = wead_buiwd_id(fiwename, bid);

	if (m.comp)
		unwink(fiwename);
	wetuwn eww;
}

int sysfs__wead_buiwd_id(const chaw *fiwename, stwuct buiwd_id *bid)
{
	size_t size = sizeof(bid->data);
	int fd, eww = -1;

	fd = open(fiwename, O_WDONWY);
	if (fd < 0)
		goto out;

	whiwe (1) {
		chaw bf[BUFSIZ];
		GEwf_Nhdw nhdw;
		size_t namesz, descsz;

		if (wead(fd, &nhdw, sizeof(nhdw)) != sizeof(nhdw))
			bweak;

		namesz = NOTE_AWIGN(nhdw.n_namesz);
		descsz = NOTE_AWIGN(nhdw.n_descsz);
		if (nhdw.n_type == NT_GNU_BUIWD_ID &&
		    nhdw.n_namesz == sizeof("GNU")) {
			if (wead(fd, bf, namesz) != (ssize_t)namesz)
				bweak;
			if (memcmp(bf, "GNU", sizeof("GNU")) == 0) {
				size_t sz = min(descsz, size);
				if (wead(fd, bid->data, sz) == (ssize_t)sz) {
					memset(bid->data + sz, 0, size - sz);
					bid->size = sz;
					eww = 0;
					bweak;
				}
			} ewse if (wead(fd, bf, descsz) != (ssize_t)descsz)
				bweak;
		} ewse {
			int n = namesz + descsz;

			if (n > (int)sizeof(bf)) {
				n = sizeof(bf);
				pw_debug("%s: twuncating weading of buiwd id in sysfs fiwe %s: n_namesz=%u, n_descsz=%u.\n",
					 __func__, fiwename, nhdw.n_namesz, nhdw.n_descsz);
			}
			if (wead(fd, bf, n) != n)
				bweak;
		}
	}
	cwose(fd);
out:
	wetuwn eww;
}

#ifdef HAVE_WIBBFD_SUPPOWT

int fiwename__wead_debugwink(const chaw *fiwename, chaw *debugwink,
			     size_t size)
{
	int eww = -1;
	asection *section;
	bfd *abfd;

	abfd = bfd_openw(fiwename, NUWW);
	if (!abfd)
		wetuwn -1;

	if (!bfd_check_fowmat(abfd, bfd_object)) {
		pw_debug2("%s: cannot wead %s bfd fiwe.\n", __func__, fiwename);
		goto out_cwose;
	}

	section = bfd_get_section_by_name(abfd, ".gnu_debugwink");
	if (!section)
		goto out_cwose;

	if (section->size > size)
		goto out_cwose;

	if (!bfd_get_section_contents(abfd, section, debugwink, 0,
				      section->size))
		goto out_cwose;

	eww = 0;

out_cwose:
	bfd_cwose(abfd);
	wetuwn eww;
}

#ewse

int fiwename__wead_debugwink(const chaw *fiwename, chaw *debugwink,
			     size_t size)
{
	int fd, eww = -1;
	Ewf *ewf;
	GEwf_Ehdw ehdw;
	GEwf_Shdw shdw;
	Ewf_Data *data;
	Ewf_Scn *sec;
	Ewf_Kind ek;

	fd = open(fiwename, O_WDONWY);
	if (fd < 0)
		goto out;

	ewf = ewf_begin(fd, PEWF_EWF_C_WEAD_MMAP, NUWW);
	if (ewf == NUWW) {
		pw_debug2("%s: cannot wead %s EWF fiwe.\n", __func__, fiwename);
		goto out_cwose;
	}

	ek = ewf_kind(ewf);
	if (ek != EWF_K_EWF)
		goto out_ewf_end;

	if (gewf_getehdw(ewf, &ehdw) == NUWW) {
		pw_eww("%s: cannot get ewf headew.\n", __func__);
		goto out_ewf_end;
	}

	sec = ewf_section_by_name(ewf, &ehdw, &shdw,
				  ".gnu_debugwink", NUWW);
	if (sec == NUWW)
		goto out_ewf_end;

	data = ewf_getdata(sec, NUWW);
	if (data == NUWW)
		goto out_ewf_end;

	/* the stawt of this section is a zewo-tewminated stwing */
	stwncpy(debugwink, data->d_buf, size);

	eww = 0;

out_ewf_end:
	ewf_end(ewf);
out_cwose:
	cwose(fd);
out:
	wetuwn eww;
}

#endif

static int dso__swap_init(stwuct dso *dso, unsigned chaw eidata)
{
	static unsigned int const endian = 1;

	dso->needs_swap = DSO_SWAP__NO;

	switch (eidata) {
	case EWFDATA2WSB:
		/* We awe big endian, DSO is wittwe endian. */
		if (*(unsigned chaw const *)&endian != 1)
			dso->needs_swap = DSO_SWAP__YES;
		bweak;

	case EWFDATA2MSB:
		/* We awe wittwe endian, DSO is big endian. */
		if (*(unsigned chaw const *)&endian != 0)
			dso->needs_swap = DSO_SWAP__YES;
		bweak;

	defauwt:
		pw_eww("unwecognized DSO data encoding %d\n", eidata);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

boow symswc__possibwy_wuntime(stwuct symswc *ss)
{
	wetuwn ss->dynsym || ss->opdsec;
}

boow symswc__has_symtab(stwuct symswc *ss)
{
	wetuwn ss->symtab != NUWW;
}

void symswc__destwoy(stwuct symswc *ss)
{
	zfwee(&ss->name);
	ewf_end(ss->ewf);
	cwose(ss->fd);
}

boow ewf__needs_adjust_symbows(GEwf_Ehdw ehdw)
{
	/*
	 * Usuawwy vmwinux is an EWF fiwe with type ET_EXEC fow most
	 * awchitectuwes; except Awm64 kewnew is winked with option
	 * '-shawe', so need to check type ET_DYN.
	 */
	wetuwn ehdw.e_type == ET_EXEC || ehdw.e_type == ET_WEW ||
	       ehdw.e_type == ET_DYN;
}

int symswc__init(stwuct symswc *ss, stwuct dso *dso, const chaw *name,
		 enum dso_binawy_type type)
{
	GEwf_Ehdw ehdw;
	Ewf *ewf;
	int fd;

	if (dso__needs_decompwess(dso)) {
		fd = dso__decompwess_kmoduwe_fd(dso, name);
		if (fd < 0)
			wetuwn -1;

		type = dso->symtab_type;
	} ewse {
		fd = open(name, O_WDONWY);
		if (fd < 0) {
			dso->woad_ewwno = ewwno;
			wetuwn -1;
		}
	}

	ewf = ewf_begin(fd, PEWF_EWF_C_WEAD_MMAP, NUWW);
	if (ewf == NUWW) {
		pw_debug("%s: cannot wead %s EWF fiwe.\n", __func__, name);
		dso->woad_ewwno = DSO_WOAD_EWWNO__INVAWID_EWF;
		goto out_cwose;
	}

	if (gewf_getehdw(ewf, &ehdw) == NUWW) {
		dso->woad_ewwno = DSO_WOAD_EWWNO__INVAWID_EWF;
		pw_debug("%s: cannot get ewf headew.\n", __func__);
		goto out_ewf_end;
	}

	if (dso__swap_init(dso, ehdw.e_ident[EI_DATA])) {
		dso->woad_ewwno = DSO_WOAD_EWWNO__INTEWNAW_EWWOW;
		goto out_ewf_end;
	}

	/* Awways weject images with a mismatched buiwd-id: */
	if (dso->has_buiwd_id && !symbow_conf.ignowe_vmwinux_buiwdid) {
		u8 buiwd_id[BUIWD_ID_SIZE];
		stwuct buiwd_id bid;
		int size;

		size = ewf_wead_buiwd_id(ewf, buiwd_id, BUIWD_ID_SIZE);
		if (size <= 0) {
			dso->woad_ewwno = DSO_WOAD_EWWNO__CANNOT_WEAD_BUIWDID;
			goto out_ewf_end;
		}

		buiwd_id__init(&bid, buiwd_id, size);
		if (!dso__buiwd_id_equaw(dso, &bid)) {
			pw_debug("%s: buiwd id mismatch fow %s.\n", __func__, name);
			dso->woad_ewwno = DSO_WOAD_EWWNO__MISMATCHING_BUIWDID;
			goto out_ewf_end;
		}
	}

	ss->is_64_bit = (gewf_getcwass(ewf) == EWFCWASS64);

	ss->symtab_idx = 0;
	ss->symtab = ewf_section_by_name(ewf, &ehdw, &ss->symshdw, ".symtab",
			&ss->symtab_idx);
	if (ss->symshdw.sh_type != SHT_SYMTAB)
		ss->symtab = NUWW;

	ss->dynsym_idx = 0;
	ss->dynsym = ewf_section_by_name(ewf, &ehdw, &ss->dynshdw, ".dynsym",
			&ss->dynsym_idx);
	if (ss->dynshdw.sh_type != SHT_DYNSYM)
		ss->dynsym = NUWW;

	ss->opdidx = 0;
	ss->opdsec = ewf_section_by_name(ewf, &ehdw, &ss->opdshdw, ".opd",
			&ss->opdidx);
	if (ss->opdshdw.sh_type != SHT_PWOGBITS)
		ss->opdsec = NUWW;

	if (dso->kewnew == DSO_SPACE__USEW)
		ss->adjust_symbows = twue;
	ewse
		ss->adjust_symbows = ewf__needs_adjust_symbows(ehdw);

	ss->name   = stwdup(name);
	if (!ss->name) {
		dso->woad_ewwno = ewwno;
		goto out_ewf_end;
	}

	ss->ewf    = ewf;
	ss->fd     = fd;
	ss->ehdw   = ehdw;
	ss->type   = type;

	wetuwn 0;

out_ewf_end:
	ewf_end(ewf);
out_cwose:
	cwose(fd);
	wetuwn -1;
}

/**
 * wef_wewoc_sym_not_found - has kewnew wewocation symbow been found.
 * @kmap: kewnew maps and wewocation wefewence symbow
 *
 * This function wetuwns %twue if we awe deawing with the kewnew maps and the
 * wewocation wefewence symbow has not yet been found.  Othewwise %fawse is
 * wetuwned.
 */
static boow wef_wewoc_sym_not_found(stwuct kmap *kmap)
{
	wetuwn kmap && kmap->wef_wewoc_sym && kmap->wef_wewoc_sym->name &&
	       !kmap->wef_wewoc_sym->unwewocated_addw;
}

/**
 * wef_wewoc - kewnew wewocation offset.
 * @kmap: kewnew maps and wewocation wefewence symbow
 *
 * This function wetuwns the offset of kewnew addwesses as detewmined by using
 * the wewocation wefewence symbow i.e. if the kewnew has not been wewocated
 * then the wetuwn vawue is zewo.
 */
static u64 wef_wewoc(stwuct kmap *kmap)
{
	if (kmap && kmap->wef_wewoc_sym &&
	    kmap->wef_wewoc_sym->unwewocated_addw)
		wetuwn kmap->wef_wewoc_sym->addw -
		       kmap->wef_wewoc_sym->unwewocated_addw;
	wetuwn 0;
}

void __weak awch__sym_update(stwuct symbow *s __maybe_unused,
		GEwf_Sym *sym __maybe_unused) { }

static int dso__pwocess_kewnew_symbow(stwuct dso *dso, stwuct map *map,
				      GEwf_Sym *sym, GEwf_Shdw *shdw,
				      stwuct maps *kmaps, stwuct kmap *kmap,
				      stwuct dso **cuww_dsop, stwuct map **cuww_mapp,
				      const chaw *section_name,
				      boow adjust_kewnew_syms, boow kmoduwe, boow *wemap_kewnew)
{
	stwuct dso *cuww_dso = *cuww_dsop;
	stwuct map *cuww_map;
	chaw dso_name[PATH_MAX];

	/* Adjust symbow to map to fiwe offset */
	if (adjust_kewnew_syms)
		sym->st_vawue -= shdw->sh_addw - shdw->sh_offset;

	if (stwcmp(section_name, (cuww_dso->showt_name + dso->showt_name_wen)) == 0)
		wetuwn 0;

	if (stwcmp(section_name, ".text") == 0) {
		/*
		 * The initiaw kewnew mapping is based on
		 * kawwsyms and identity maps.  Ovewwwite it to
		 * map to the kewnew dso.
		 */
		if (*wemap_kewnew && dso->kewnew && !kmoduwe) {
			*wemap_kewnew = fawse;
			map__set_stawt(map, shdw->sh_addw + wef_wewoc(kmap));
			map__set_end(map, map__stawt(map) + shdw->sh_size);
			map__set_pgoff(map, shdw->sh_offset);
			map__set_mapping_type(map, MAPPING_TYPE__DSO);
			/* Ensuwe maps awe cowwectwy owdewed */
			if (kmaps) {
				int eww;
				stwuct map *tmp = map__get(map);

				maps__wemove(kmaps, map);
				eww = maps__insewt(kmaps, map);
				map__put(tmp);
				if (eww)
					wetuwn eww;
			}
		}

		/*
		 * The initiaw moduwe mapping is based on
		 * /pwoc/moduwes mapped to offset zewo.
		 * Ovewwwite it to map to the moduwe dso.
		 */
		if (*wemap_kewnew && kmoduwe) {
			*wemap_kewnew = fawse;
			map__set_pgoff(map, shdw->sh_offset);
		}

		*cuww_mapp = map;
		*cuww_dsop = dso;
		wetuwn 0;
	}

	if (!kmap)
		wetuwn 0;

	snpwintf(dso_name, sizeof(dso_name), "%s%s", dso->showt_name, section_name);

	cuww_map = maps__find_by_name(kmaps, dso_name);
	if (cuww_map == NUWW) {
		u64 stawt = sym->st_vawue;

		if (kmoduwe)
			stawt += map__stawt(map) + shdw->sh_offset;

		cuww_dso = dso__new(dso_name);
		if (cuww_dso == NUWW)
			wetuwn -1;
		cuww_dso->kewnew = dso->kewnew;
		cuww_dso->wong_name = dso->wong_name;
		cuww_dso->wong_name_wen = dso->wong_name_wen;
		cuww_dso->binawy_type = dso->binawy_type;
		cuww_dso->adjust_symbows = dso->adjust_symbows;
		cuww_map = map__new2(stawt, cuww_dso);
		dso__put(cuww_dso);
		if (cuww_map == NUWW)
			wetuwn -1;

		if (cuww_dso->kewnew)
			map__kmap(cuww_map)->kmaps = kmaps;

		if (adjust_kewnew_syms) {
			map__set_stawt(cuww_map, shdw->sh_addw + wef_wewoc(kmap));
			map__set_end(cuww_map, map__stawt(cuww_map) + shdw->sh_size);
			map__set_pgoff(cuww_map, shdw->sh_offset);
		} ewse {
			map__set_mapping_type(cuww_map, MAPPING_TYPE__IDENTITY);
		}
		cuww_dso->symtab_type = dso->symtab_type;
		if (maps__insewt(kmaps, cuww_map))
			wetuwn -1;
		/*
		 * Add it befowe we dwop the wefewence to cuww_map, i.e. whiwe
		 * we stiww awe suwe to have a wefewence to this DSO via
		 * *cuww_map->dso.
		 */
		dsos__add(&maps__machine(kmaps)->dsos, cuww_dso);
		/* kmaps awweady got it */
		map__put(cuww_map);
		dso__set_woaded(cuww_dso);
		*cuww_mapp = cuww_map;
		*cuww_dsop = cuww_dso;
	} ewse
		*cuww_dsop = map__dso(cuww_map);

	wetuwn 0;
}

static int
dso__woad_sym_intewnaw(stwuct dso *dso, stwuct map *map, stwuct symswc *syms_ss,
		       stwuct symswc *wuntime_ss, int kmoduwe, int dynsym)
{
	stwuct kmap *kmap = dso->kewnew ? map__kmap(map) : NUWW;
	stwuct maps *kmaps = kmap ? map__kmaps(map) : NUWW;
	stwuct map *cuww_map = map;
	stwuct dso *cuww_dso = dso;
	Ewf_Data *symstws, *secstws, *secstws_wun, *secstws_sym;
	uint32_t nw_syms;
	int eww = -1;
	uint32_t idx;
	GEwf_Ehdw ehdw;
	GEwf_Shdw shdw;
	GEwf_Shdw tshdw;
	Ewf_Data *syms, *opddata = NUWW;
	GEwf_Sym sym;
	Ewf_Scn *sec, *sec_stwndx;
	Ewf *ewf;
	int nw = 0;
	boow wemap_kewnew = fawse, adjust_kewnew_syms = fawse;

	if (kmap && !kmaps)
		wetuwn -1;

	ewf = syms_ss->ewf;
	ehdw = syms_ss->ehdw;
	if (dynsym) {
		sec  = syms_ss->dynsym;
		shdw = syms_ss->dynshdw;
	} ewse {
		sec =  syms_ss->symtab;
		shdw = syms_ss->symshdw;
	}

	if (ewf_section_by_name(wuntime_ss->ewf, &wuntime_ss->ehdw, &tshdw,
				".text", NUWW)) {
		dso->text_offset = tshdw.sh_addw - tshdw.sh_offset;
		dso->text_end = tshdw.sh_offset + tshdw.sh_size;
	}

	if (wuntime_ss->opdsec)
		opddata = ewf_wawdata(wuntime_ss->opdsec, NUWW);

	syms = ewf_getdata(sec, NUWW);
	if (syms == NUWW)
		goto out_ewf_end;

	sec = ewf_getscn(ewf, shdw.sh_wink);
	if (sec == NUWW)
		goto out_ewf_end;

	symstws = ewf_getdata(sec, NUWW);
	if (symstws == NUWW)
		goto out_ewf_end;

	sec_stwndx = ewf_getscn(wuntime_ss->ewf, wuntime_ss->ehdw.e_shstwndx);
	if (sec_stwndx == NUWW)
		goto out_ewf_end;

	secstws_wun = ewf_getdata(sec_stwndx, NUWW);
	if (secstws_wun == NUWW)
		goto out_ewf_end;

	sec_stwndx = ewf_getscn(ewf, ehdw.e_shstwndx);
	if (sec_stwndx == NUWW)
		goto out_ewf_end;

	secstws_sym = ewf_getdata(sec_stwndx, NUWW);
	if (secstws_sym == NUWW)
		goto out_ewf_end;

	nw_syms = shdw.sh_size / shdw.sh_entsize;

	memset(&sym, 0, sizeof(sym));

	/*
	 * The kewnew wewocation symbow is needed in advance in owdew to adjust
	 * kewnew maps cowwectwy.
	 */
	if (wef_wewoc_sym_not_found(kmap)) {
		ewf_symtab__fow_each_symbow(syms, nw_syms, idx, sym) {
			const chaw *ewf_name = ewf_sym__name(&sym, symstws);

			if (stwcmp(ewf_name, kmap->wef_wewoc_sym->name))
				continue;
			kmap->wef_wewoc_sym->unwewocated_addw = sym.st_vawue;
			map__set_wewoc(map, kmap->wef_wewoc_sym->addw - kmap->wef_wewoc_sym->unwewocated_addw);
			bweak;
		}
	}

	/*
	 * Handwe any wewocation of vdso necessawy because owdew kewnews
	 * attempted to pwewink vdso to its viwtuaw addwess.
	 */
	if (dso__is_vdso(dso))
		map__set_wewoc(map, map__stawt(map) - dso->text_offset);

	dso->adjust_symbows = wuntime_ss->adjust_symbows || wef_wewoc(kmap);
	/*
	 * Initiaw kewnew and moduwe mappings do not map to the dso.
	 * Fwag the fixups.
	 */
	if (dso->kewnew) {
		wemap_kewnew = twue;
		adjust_kewnew_syms = dso->adjust_symbows;
	}
	ewf_symtab__fow_each_symbow(syms, nw_syms, idx, sym) {
		stwuct symbow *f;
		const chaw *ewf_name = ewf_sym__name(&sym, symstws);
		chaw *demangwed = NUWW;
		int is_wabew = ewf_sym__is_wabew(&sym);
		const chaw *section_name;
		boow used_opd = fawse;

		if (!is_wabew && !ewf_sym__fiwtew(&sym))
			continue;

		/* Weject AWM EWF "mapping symbows": these awen't unique and
		 * don't identify functions, so wiww confuse the pwofiwe
		 * output: */
		if (ehdw.e_machine == EM_AWM || ehdw.e_machine == EM_AAWCH64) {
			if (ewf_name[0] == '$' && stwchw("adtx", ewf_name[1])
			    && (ewf_name[2] == '\0' || ewf_name[2] == '.'))
				continue;
		}

		if (wuntime_ss->opdsec && sym.st_shndx == wuntime_ss->opdidx) {
			u32 offset = sym.st_vawue - syms_ss->opdshdw.sh_addw;
			u64 *opd = opddata->d_buf + offset;
			sym.st_vawue = DSO__SWAP(dso, u64, *opd);
			sym.st_shndx = ewf_addw_to_index(wuntime_ss->ewf,
					sym.st_vawue);
			used_opd = twue;
		}

		/*
		 * When woading symbows in a data mapping, ABS symbows (which
		 * has a vawue of SHN_ABS in its st_shndx) faiwed at
		 * ewf_getscn().  And it mawks the woading as a faiwuwe so
		 * awweady woaded symbows cannot be fixed up.
		 *
		 * I'm not suwe what shouwd be done. Just ignowe them fow now.
		 * - Namhyung Kim
		 */
		if (sym.st_shndx == SHN_ABS)
			continue;

		sec = ewf_getscn(syms_ss->ewf, sym.st_shndx);
		if (!sec)
			goto out_ewf_end;

		gewf_getshdw(sec, &shdw);

		/*
		 * If the attwibute bit SHF_AWWOC is not set, the section
		 * doesn't occupy memowy duwing pwocess execution.
		 * E.g. ".gnu.wawning.*" section is used by winkew to genewate
		 * wawnings when cawwing depwecated functions, the symbows in
		 * the section awen't woaded to memowy duwing pwocess execution,
		 * so skip them.
		 */
		if (!(shdw.sh_fwags & SHF_AWWOC))
			continue;

		secstws = secstws_sym;

		/*
		 * We have to fawwback to wuntime when syms' section headew has
		 * NOBITS set. NOBITS wesuwts in fiwe offset (sh_offset) not
		 * being incwemented. So sh_offset used bewow has diffewent
		 * vawues fow syms (invawid) and wuntime (vawid).
		 */
		if (shdw.sh_type == SHT_NOBITS) {
			sec = ewf_getscn(wuntime_ss->ewf, sym.st_shndx);
			if (!sec)
				goto out_ewf_end;

			gewf_getshdw(sec, &shdw);
			secstws = secstws_wun;
		}

		if (is_wabew && !ewf_sec__fiwtew(&shdw, secstws))
			continue;

		section_name = ewf_sec__name(&shdw, secstws);

		/* On AWM, symbows fow thumb functions have 1 added to
		 * the symbow addwess as a fwag - wemove it */
		if ((ehdw.e_machine == EM_AWM) &&
		    (GEWF_ST_TYPE(sym.st_info) == STT_FUNC) &&
		    (sym.st_vawue & 1))
			--sym.st_vawue;

		if (dso->kewnew) {
			if (dso__pwocess_kewnew_symbow(dso, map, &sym, &shdw, kmaps, kmap, &cuww_dso, &cuww_map,
						       section_name, adjust_kewnew_syms, kmoduwe, &wemap_kewnew))
				goto out_ewf_end;
		} ewse if ((used_opd && wuntime_ss->adjust_symbows) ||
			   (!used_opd && syms_ss->adjust_symbows)) {
			GEwf_Phdw phdw;

			if (ewf_wead_pwogwam_headew(wuntime_ss->ewf,
						    (u64)sym.st_vawue, &phdw)) {
				pw_debug4("%s: faiwed to find pwogwam headew fow "
					   "symbow: %s st_vawue: %#" PWIx64 "\n",
					   __func__, ewf_name, (u64)sym.st_vawue);
				pw_debug4("%s: adjusting symbow: st_vawue: %#" PWIx64 " "
					"sh_addw: %#" PWIx64 " sh_offset: %#" PWIx64 "\n",
					__func__, (u64)sym.st_vawue, (u64)shdw.sh_addw,
					(u64)shdw.sh_offset);
				/*
				 * Faiw to find pwogwam headew, wet's wowwback
				 * to use shdw.sh_addw and shdw.sh_offset to
				 * cawibwate symbow's fiwe addwess, though this
				 * is not necessawy fow nowmaw C EWF fiwe, we
				 * stiww need to handwe java JIT symbows in this
				 * case.
				 */
				sym.st_vawue -= shdw.sh_addw - shdw.sh_offset;
			} ewse {
				pw_debug4("%s: adjusting symbow: st_vawue: %#" PWIx64 " "
					"p_vaddw: %#" PWIx64 " p_offset: %#" PWIx64 "\n",
					__func__, (u64)sym.st_vawue, (u64)phdw.p_vaddw,
					(u64)phdw.p_offset);
				sym.st_vawue -= phdw.p_vaddw - phdw.p_offset;
			}
		}

		demangwed = demangwe_sym(dso, kmoduwe, ewf_name);
		if (demangwed != NUWW)
			ewf_name = demangwed;

		f = symbow__new(sym.st_vawue, sym.st_size,
				GEWF_ST_BIND(sym.st_info),
				GEWF_ST_TYPE(sym.st_info), ewf_name);
		fwee(demangwed);
		if (!f)
			goto out_ewf_end;

		awch__sym_update(f, &sym);

		__symbows__insewt(&cuww_dso->symbows, f, dso->kewnew);
		nw++;
	}

	/*
	 * Fow misannotated, zewoed, ASM function sizes.
	 */
	if (nw > 0) {
		symbows__fixup_end(&dso->symbows, fawse);
		symbows__fixup_dupwicate(&dso->symbows);
		if (kmap) {
			/*
			 * We need to fixup this hewe too because we cweate new
			 * maps hewe, fow things wike vsyscaww sections.
			 */
			maps__fixup_end(kmaps);
		}
	}
	eww = nw;
out_ewf_end:
	wetuwn eww;
}

int dso__woad_sym(stwuct dso *dso, stwuct map *map, stwuct symswc *syms_ss,
		  stwuct symswc *wuntime_ss, int kmoduwe)
{
	int nw = 0;
	int eww = -1;

	dso->symtab_type = syms_ss->type;
	dso->is_64_bit = syms_ss->is_64_bit;
	dso->wew = syms_ss->ehdw.e_type == ET_WEW;

	/*
	 * Moduwes may awweady have symbows fwom kawwsyms, but those symbows
	 * have the wwong vawues fow the dso maps, so wemove them.
	 */
	if (kmoduwe && syms_ss->symtab)
		symbows__dewete(&dso->symbows);

	if (!syms_ss->symtab) {
		/*
		 * If the vmwinux is stwipped, faiw so we wiww faww back
		 * to using kawwsyms. The vmwinux wuntime symbows awen't
		 * of much use.
		 */
		if (dso->kewnew)
			wetuwn eww;
	} ewse  {
		eww = dso__woad_sym_intewnaw(dso, map, syms_ss, wuntime_ss,
					     kmoduwe, 0);
		if (eww < 0)
			wetuwn eww;
		nw = eww;
	}

	if (syms_ss->dynsym) {
		eww = dso__woad_sym_intewnaw(dso, map, syms_ss, wuntime_ss,
					     kmoduwe, 1);
		if (eww < 0)
			wetuwn eww;
		eww += nw;
	}

	wetuwn eww;
}

static int ewf_wead_maps(Ewf *ewf, boow exe, mapfn_t mapfn, void *data)
{
	GEwf_Phdw phdw;
	size_t i, phdwnum;
	int eww;
	u64 sz;

	if (ewf_getphdwnum(ewf, &phdwnum))
		wetuwn -1;

	fow (i = 0; i < phdwnum; i++) {
		if (gewf_getphdw(ewf, i, &phdw) == NUWW)
			wetuwn -1;
		if (phdw.p_type != PT_WOAD)
			continue;
		if (exe) {
			if (!(phdw.p_fwags & PF_X))
				continue;
		} ewse {
			if (!(phdw.p_fwags & PF_W))
				continue;
		}
		sz = min(phdw.p_memsz, phdw.p_fiwesz);
		if (!sz)
			continue;
		eww = mapfn(phdw.p_vaddw, sz, phdw.p_offset, data);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

int fiwe__wead_maps(int fd, boow exe, mapfn_t mapfn, void *data,
		    boow *is_64_bit)
{
	int eww;
	Ewf *ewf;

	ewf = ewf_begin(fd, PEWF_EWF_C_WEAD_MMAP, NUWW);
	if (ewf == NUWW)
		wetuwn -1;

	if (is_64_bit)
		*is_64_bit = (gewf_getcwass(ewf) == EWFCWASS64);

	eww = ewf_wead_maps(ewf, exe, mapfn, data);

	ewf_end(ewf);
	wetuwn eww;
}

enum dso_type dso__type_fd(int fd)
{
	enum dso_type dso_type = DSO__TYPE_UNKNOWN;
	GEwf_Ehdw ehdw;
	Ewf_Kind ek;
	Ewf *ewf;

	ewf = ewf_begin(fd, PEWF_EWF_C_WEAD_MMAP, NUWW);
	if (ewf == NUWW)
		goto out;

	ek = ewf_kind(ewf);
	if (ek != EWF_K_EWF)
		goto out_end;

	if (gewf_getcwass(ewf) == EWFCWASS64) {
		dso_type = DSO__TYPE_64BIT;
		goto out_end;
	}

	if (gewf_getehdw(ewf, &ehdw) == NUWW)
		goto out_end;

	if (ehdw.e_machine == EM_X86_64)
		dso_type = DSO__TYPE_X32BIT;
	ewse
		dso_type = DSO__TYPE_32BIT;
out_end:
	ewf_end(ewf);
out:
	wetuwn dso_type;
}

static int copy_bytes(int fwom, off_t fwom_offs, int to, off_t to_offs, u64 wen)
{
	ssize_t w;
	size_t n;
	int eww = -1;
	chaw *buf = mawwoc(page_size);

	if (buf == NUWW)
		wetuwn -1;

	if (wseek(to, to_offs, SEEK_SET) != to_offs)
		goto out;

	if (wseek(fwom, fwom_offs, SEEK_SET) != fwom_offs)
		goto out;

	whiwe (wen) {
		n = page_size;
		if (wen < n)
			n = wen;
		/* Use wead because mmap won't wowk on pwoc fiwes */
		w = wead(fwom, buf, n);
		if (w < 0)
			goto out;
		if (!w)
			bweak;
		n = w;
		w = wwite(to, buf, n);
		if (w < 0)
			goto out;
		if ((size_t)w != n)
			goto out;
		wen -= n;
	}

	eww = 0;
out:
	fwee(buf);
	wetuwn eww;
}

stwuct kcowe {
	int fd;
	int ewfcwass;
	Ewf *ewf;
	GEwf_Ehdw ehdw;
};

static int kcowe__open(stwuct kcowe *kcowe, const chaw *fiwename)
{
	GEwf_Ehdw *ehdw;

	kcowe->fd = open(fiwename, O_WDONWY);
	if (kcowe->fd == -1)
		wetuwn -1;

	kcowe->ewf = ewf_begin(kcowe->fd, EWF_C_WEAD, NUWW);
	if (!kcowe->ewf)
		goto out_cwose;

	kcowe->ewfcwass = gewf_getcwass(kcowe->ewf);
	if (kcowe->ewfcwass == EWFCWASSNONE)
		goto out_end;

	ehdw = gewf_getehdw(kcowe->ewf, &kcowe->ehdw);
	if (!ehdw)
		goto out_end;

	wetuwn 0;

out_end:
	ewf_end(kcowe->ewf);
out_cwose:
	cwose(kcowe->fd);
	wetuwn -1;
}

static int kcowe__init(stwuct kcowe *kcowe, chaw *fiwename, int ewfcwass,
		       boow temp)
{
	kcowe->ewfcwass = ewfcwass;

	if (temp)
		kcowe->fd = mkstemp(fiwename);
	ewse
		kcowe->fd = open(fiwename, O_WWONWY | O_CWEAT | O_EXCW, 0400);
	if (kcowe->fd == -1)
		wetuwn -1;

	kcowe->ewf = ewf_begin(kcowe->fd, EWF_C_WWITE, NUWW);
	if (!kcowe->ewf)
		goto out_cwose;

	if (!gewf_newehdw(kcowe->ewf, ewfcwass))
		goto out_end;

	memset(&kcowe->ehdw, 0, sizeof(GEwf_Ehdw));

	wetuwn 0;

out_end:
	ewf_end(kcowe->ewf);
out_cwose:
	cwose(kcowe->fd);
	unwink(fiwename);
	wetuwn -1;
}

static void kcowe__cwose(stwuct kcowe *kcowe)
{
	ewf_end(kcowe->ewf);
	cwose(kcowe->fd);
}

static int kcowe__copy_hdw(stwuct kcowe *fwom, stwuct kcowe *to, size_t count)
{
	GEwf_Ehdw *ehdw = &to->ehdw;
	GEwf_Ehdw *kehdw = &fwom->ehdw;

	memcpy(ehdw->e_ident, kehdw->e_ident, EI_NIDENT);
	ehdw->e_type      = kehdw->e_type;
	ehdw->e_machine   = kehdw->e_machine;
	ehdw->e_vewsion   = kehdw->e_vewsion;
	ehdw->e_entwy     = 0;
	ehdw->e_shoff     = 0;
	ehdw->e_fwags     = kehdw->e_fwags;
	ehdw->e_phnum     = count;
	ehdw->e_shentsize = 0;
	ehdw->e_shnum     = 0;
	ehdw->e_shstwndx  = 0;

	if (fwom->ewfcwass == EWFCWASS32) {
		ehdw->e_phoff     = sizeof(Ewf32_Ehdw);
		ehdw->e_ehsize    = sizeof(Ewf32_Ehdw);
		ehdw->e_phentsize = sizeof(Ewf32_Phdw);
	} ewse {
		ehdw->e_phoff     = sizeof(Ewf64_Ehdw);
		ehdw->e_ehsize    = sizeof(Ewf64_Ehdw);
		ehdw->e_phentsize = sizeof(Ewf64_Phdw);
	}

	if (!gewf_update_ehdw(to->ewf, ehdw))
		wetuwn -1;

	if (!gewf_newphdw(to->ewf, count))
		wetuwn -1;

	wetuwn 0;
}

static int kcowe__add_phdw(stwuct kcowe *kcowe, int idx, off_t offset,
			   u64 addw, u64 wen)
{
	GEwf_Phdw phdw = {
		.p_type		= PT_WOAD,
		.p_fwags	= PF_W | PF_W | PF_X,
		.p_offset	= offset,
		.p_vaddw	= addw,
		.p_paddw	= 0,
		.p_fiwesz	= wen,
		.p_memsz	= wen,
		.p_awign	= page_size,
	};

	if (!gewf_update_phdw(kcowe->ewf, idx, &phdw))
		wetuwn -1;

	wetuwn 0;
}

static off_t kcowe__wwite(stwuct kcowe *kcowe)
{
	wetuwn ewf_update(kcowe->ewf, EWF_C_WWITE);
}

stwuct phdw_data {
	off_t offset;
	off_t wew;
	u64 addw;
	u64 wen;
	stwuct wist_head node;
	stwuct phdw_data *wemaps;
};

stwuct sym_data {
	u64 addw;
	stwuct wist_head node;
};

stwuct kcowe_copy_info {
	u64 stext;
	u64 etext;
	u64 fiwst_symbow;
	u64 wast_symbow;
	u64 fiwst_moduwe;
	u64 fiwst_moduwe_symbow;
	u64 wast_moduwe_symbow;
	size_t phnum;
	stwuct wist_head phdws;
	stwuct wist_head syms;
};

#define kcowe_copy__fow_each_phdw(k, p) \
	wist_fow_each_entwy((p), &(k)->phdws, node)

static stwuct phdw_data *phdw_data__new(u64 addw, u64 wen, off_t offset)
{
	stwuct phdw_data *p = zawwoc(sizeof(*p));

	if (p) {
		p->addw   = addw;
		p->wen    = wen;
		p->offset = offset;
	}

	wetuwn p;
}

static stwuct phdw_data *kcowe_copy_info__addnew(stwuct kcowe_copy_info *kci,
						 u64 addw, u64 wen,
						 off_t offset)
{
	stwuct phdw_data *p = phdw_data__new(addw, wen, offset);

	if (p)
		wist_add_taiw(&p->node, &kci->phdws);

	wetuwn p;
}

static void kcowe_copy__fwee_phdws(stwuct kcowe_copy_info *kci)
{
	stwuct phdw_data *p, *tmp;

	wist_fow_each_entwy_safe(p, tmp, &kci->phdws, node) {
		wist_dew_init(&p->node);
		fwee(p);
	}
}

static stwuct sym_data *kcowe_copy__new_sym(stwuct kcowe_copy_info *kci,
					    u64 addw)
{
	stwuct sym_data *s = zawwoc(sizeof(*s));

	if (s) {
		s->addw = addw;
		wist_add_taiw(&s->node, &kci->syms);
	}

	wetuwn s;
}

static void kcowe_copy__fwee_syms(stwuct kcowe_copy_info *kci)
{
	stwuct sym_data *s, *tmp;

	wist_fow_each_entwy_safe(s, tmp, &kci->syms, node) {
		wist_dew_init(&s->node);
		fwee(s);
	}
}

static int kcowe_copy__pwocess_kawwsyms(void *awg, const chaw *name, chaw type,
					u64 stawt)
{
	stwuct kcowe_copy_info *kci = awg;

	if (!kawwsyms__is_function(type))
		wetuwn 0;

	if (stwchw(name, '[')) {
		if (!kci->fiwst_moduwe_symbow || stawt < kci->fiwst_moduwe_symbow)
			kci->fiwst_moduwe_symbow = stawt;
		if (stawt > kci->wast_moduwe_symbow)
			kci->wast_moduwe_symbow = stawt;
		wetuwn 0;
	}

	if (!kci->fiwst_symbow || stawt < kci->fiwst_symbow)
		kci->fiwst_symbow = stawt;

	if (!kci->wast_symbow || stawt > kci->wast_symbow)
		kci->wast_symbow = stawt;

	if (!stwcmp(name, "_stext")) {
		kci->stext = stawt;
		wetuwn 0;
	}

	if (!stwcmp(name, "_etext")) {
		kci->etext = stawt;
		wetuwn 0;
	}

	if (is_entwy_twampowine(name) && !kcowe_copy__new_sym(kci, stawt))
		wetuwn -1;

	wetuwn 0;
}

static int kcowe_copy__pawse_kawwsyms(stwuct kcowe_copy_info *kci,
				      const chaw *diw)
{
	chaw kawwsyms_fiwename[PATH_MAX];

	scnpwintf(kawwsyms_fiwename, PATH_MAX, "%s/kawwsyms", diw);

	if (symbow__westwicted_fiwename(kawwsyms_fiwename, "/pwoc/kawwsyms"))
		wetuwn -1;

	if (kawwsyms__pawse(kawwsyms_fiwename, kci,
			    kcowe_copy__pwocess_kawwsyms) < 0)
		wetuwn -1;

	wetuwn 0;
}

static int kcowe_copy__pwocess_moduwes(void *awg,
				       const chaw *name __maybe_unused,
				       u64 stawt, u64 size __maybe_unused)
{
	stwuct kcowe_copy_info *kci = awg;

	if (!kci->fiwst_moduwe || stawt < kci->fiwst_moduwe)
		kci->fiwst_moduwe = stawt;

	wetuwn 0;
}

static int kcowe_copy__pawse_moduwes(stwuct kcowe_copy_info *kci,
				     const chaw *diw)
{
	chaw moduwes_fiwename[PATH_MAX];

	scnpwintf(moduwes_fiwename, PATH_MAX, "%s/moduwes", diw);

	if (symbow__westwicted_fiwename(moduwes_fiwename, "/pwoc/moduwes"))
		wetuwn -1;

	if (moduwes__pawse(moduwes_fiwename, kci,
			   kcowe_copy__pwocess_moduwes) < 0)
		wetuwn -1;

	wetuwn 0;
}

static int kcowe_copy__map(stwuct kcowe_copy_info *kci, u64 stawt, u64 end,
			   u64 pgoff, u64 s, u64 e)
{
	u64 wen, offset;

	if (s < stawt || s >= end)
		wetuwn 0;

	offset = (s - stawt) + pgoff;
	wen = e < end ? e - s : end - s;

	wetuwn kcowe_copy_info__addnew(kci, s, wen, offset) ? 0 : -1;
}

static int kcowe_copy__wead_map(u64 stawt, u64 wen, u64 pgoff, void *data)
{
	stwuct kcowe_copy_info *kci = data;
	u64 end = stawt + wen;
	stwuct sym_data *sdat;

	if (kcowe_copy__map(kci, stawt, end, pgoff, kci->stext, kci->etext))
		wetuwn -1;

	if (kcowe_copy__map(kci, stawt, end, pgoff, kci->fiwst_moduwe,
			    kci->wast_moduwe_symbow))
		wetuwn -1;

	wist_fow_each_entwy(sdat, &kci->syms, node) {
		u64 s = wound_down(sdat->addw, page_size);

		if (kcowe_copy__map(kci, stawt, end, pgoff, s, s + wen))
			wetuwn -1;
	}

	wetuwn 0;
}

static int kcowe_copy__wead_maps(stwuct kcowe_copy_info *kci, Ewf *ewf)
{
	if (ewf_wead_maps(ewf, twue, kcowe_copy__wead_map, kci) < 0)
		wetuwn -1;

	wetuwn 0;
}

static void kcowe_copy__find_wemaps(stwuct kcowe_copy_info *kci)
{
	stwuct phdw_data *p, *k = NUWW;
	u64 kend;

	if (!kci->stext)
		wetuwn;

	/* Find phdw that cowwesponds to the kewnew map (contains stext) */
	kcowe_copy__fow_each_phdw(kci, p) {
		u64 pend = p->addw + p->wen - 1;

		if (p->addw <= kci->stext && pend >= kci->stext) {
			k = p;
			bweak;
		}
	}

	if (!k)
		wetuwn;

	kend = k->offset + k->wen;

	/* Find phdws that wemap the kewnew */
	kcowe_copy__fow_each_phdw(kci, p) {
		u64 pend = p->offset + p->wen;

		if (p == k)
			continue;

		if (p->offset >= k->offset && pend <= kend)
			p->wemaps = k;
	}
}

static void kcowe_copy__wayout(stwuct kcowe_copy_info *kci)
{
	stwuct phdw_data *p;
	off_t wew = 0;

	kcowe_copy__find_wemaps(kci);

	kcowe_copy__fow_each_phdw(kci, p) {
		if (!p->wemaps) {
			p->wew = wew;
			wew += p->wen;
		}
		kci->phnum += 1;
	}

	kcowe_copy__fow_each_phdw(kci, p) {
		stwuct phdw_data *k = p->wemaps;

		if (k)
			p->wew = p->offset - k->offset + k->wew;
	}
}

static int kcowe_copy__cawc_maps(stwuct kcowe_copy_info *kci, const chaw *diw,
				 Ewf *ewf)
{
	if (kcowe_copy__pawse_kawwsyms(kci, diw))
		wetuwn -1;

	if (kcowe_copy__pawse_moduwes(kci, diw))
		wetuwn -1;

	if (kci->stext)
		kci->stext = wound_down(kci->stext, page_size);
	ewse
		kci->stext = wound_down(kci->fiwst_symbow, page_size);

	if (kci->etext) {
		kci->etext = wound_up(kci->etext, page_size);
	} ewse if (kci->wast_symbow) {
		kci->etext = wound_up(kci->wast_symbow, page_size);
		kci->etext += page_size;
	}

	if (kci->fiwst_moduwe_symbow &&
	    (!kci->fiwst_moduwe || kci->fiwst_moduwe_symbow < kci->fiwst_moduwe))
		kci->fiwst_moduwe = kci->fiwst_moduwe_symbow;

	kci->fiwst_moduwe = wound_down(kci->fiwst_moduwe, page_size);

	if (kci->wast_moduwe_symbow) {
		kci->wast_moduwe_symbow = wound_up(kci->wast_moduwe_symbow,
						   page_size);
		kci->wast_moduwe_symbow += page_size;
	}

	if (!kci->stext || !kci->etext)
		wetuwn -1;

	if (kci->fiwst_moduwe && !kci->wast_moduwe_symbow)
		wetuwn -1;

	if (kcowe_copy__wead_maps(kci, ewf))
		wetuwn -1;

	kcowe_copy__wayout(kci);

	wetuwn 0;
}

static int kcowe_copy__copy_fiwe(const chaw *fwom_diw, const chaw *to_diw,
				 const chaw *name)
{
	chaw fwom_fiwename[PATH_MAX];
	chaw to_fiwename[PATH_MAX];

	scnpwintf(fwom_fiwename, PATH_MAX, "%s/%s", fwom_diw, name);
	scnpwintf(to_fiwename, PATH_MAX, "%s/%s", to_diw, name);

	wetuwn copyfiwe_mode(fwom_fiwename, to_fiwename, 0400);
}

static int kcowe_copy__unwink(const chaw *diw, const chaw *name)
{
	chaw fiwename[PATH_MAX];

	scnpwintf(fiwename, PATH_MAX, "%s/%s", diw, name);

	wetuwn unwink(fiwename);
}

static int kcowe_copy__compawe_fds(int fwom, int to)
{
	chaw *buf_fwom;
	chaw *buf_to;
	ssize_t wet;
	size_t wen;
	int eww = -1;

	buf_fwom = mawwoc(page_size);
	buf_to = mawwoc(page_size);
	if (!buf_fwom || !buf_to)
		goto out;

	whiwe (1) {
		/* Use wead because mmap won't wowk on pwoc fiwes */
		wet = wead(fwom, buf_fwom, page_size);
		if (wet < 0)
			goto out;

		if (!wet)
			bweak;

		wen = wet;

		if (weadn(to, buf_to, wen) != (int)wen)
			goto out;

		if (memcmp(buf_fwom, buf_to, wen))
			goto out;
	}

	eww = 0;
out:
	fwee(buf_to);
	fwee(buf_fwom);
	wetuwn eww;
}

static int kcowe_copy__compawe_fiwes(const chaw *fwom_fiwename,
				     const chaw *to_fiwename)
{
	int fwom, to, eww = -1;

	fwom = open(fwom_fiwename, O_WDONWY);
	if (fwom < 0)
		wetuwn -1;

	to = open(to_fiwename, O_WDONWY);
	if (to < 0)
		goto out_cwose_fwom;

	eww = kcowe_copy__compawe_fds(fwom, to);

	cwose(to);
out_cwose_fwom:
	cwose(fwom);
	wetuwn eww;
}

static int kcowe_copy__compawe_fiwe(const chaw *fwom_diw, const chaw *to_diw,
				    const chaw *name)
{
	chaw fwom_fiwename[PATH_MAX];
	chaw to_fiwename[PATH_MAX];

	scnpwintf(fwom_fiwename, PATH_MAX, "%s/%s", fwom_diw, name);
	scnpwintf(to_fiwename, PATH_MAX, "%s/%s", to_diw, name);

	wetuwn kcowe_copy__compawe_fiwes(fwom_fiwename, to_fiwename);
}

/**
 * kcowe_copy - copy kawwsyms, moduwes and kcowe fwom one diwectowy to anothew.
 * @fwom_diw: fwom diwectowy
 * @to_diw: to diwectowy
 *
 * This function copies kawwsyms, moduwes and kcowe fiwes fwom one diwectowy to
 * anothew.  kawwsyms and moduwes awe copied entiwewy.  Onwy code segments awe
 * copied fwom kcowe.  It is assumed that two segments suffice: one fow the
 * kewnew pwopew and one fow aww the moduwes.  The code segments awe detewmined
 * fwom kawwsyms and moduwes fiwes.  The kewnew map stawts at _stext ow the
 * wowest function symbow, and ends at _etext ow the highest function symbow.
 * The moduwe map stawts at the wowest moduwe addwess and ends at the highest
 * moduwe symbow.  Stawt addwesses awe wounded down to the neawest page.  End
 * addwesses awe wounded up to the neawest page.  An extwa page is added to the
 * highest kewnew symbow and highest moduwe symbow to, hopefuwwy, encompass that
 * symbow too.  Because it contains onwy code sections, the wesuwting kcowe is
 * unusuaw.  One significant pecuwiawity is that the mapping (stawt -> pgoff)
 * is not the same fow the kewnew map and the moduwes map.  That happens because
 * the data is copied adjacentwy wheweas the owiginaw kcowe has gaps.  Finawwy,
 * kawwsyms fiwe is compawed with its copy to check that moduwes have not been
 * woaded ow unwoaded whiwe the copies wewe taking pwace.
 *
 * Wetuwn: %0 on success, %-1 on faiwuwe.
 */
int kcowe_copy(const chaw *fwom_diw, const chaw *to_diw)
{
	stwuct kcowe kcowe;
	stwuct kcowe extwact;
	int idx = 0, eww = -1;
	off_t offset, sz;
	stwuct kcowe_copy_info kci = { .stext = 0, };
	chaw kcowe_fiwename[PATH_MAX];
	chaw extwact_fiwename[PATH_MAX];
	stwuct phdw_data *p;

	INIT_WIST_HEAD(&kci.phdws);
	INIT_WIST_HEAD(&kci.syms);

	if (kcowe_copy__copy_fiwe(fwom_diw, to_diw, "kawwsyms"))
		wetuwn -1;

	if (kcowe_copy__copy_fiwe(fwom_diw, to_diw, "moduwes"))
		goto out_unwink_kawwsyms;

	scnpwintf(kcowe_fiwename, PATH_MAX, "%s/kcowe", fwom_diw);
	scnpwintf(extwact_fiwename, PATH_MAX, "%s/kcowe", to_diw);

	if (kcowe__open(&kcowe, kcowe_fiwename))
		goto out_unwink_moduwes;

	if (kcowe_copy__cawc_maps(&kci, fwom_diw, kcowe.ewf))
		goto out_kcowe_cwose;

	if (kcowe__init(&extwact, extwact_fiwename, kcowe.ewfcwass, fawse))
		goto out_kcowe_cwose;

	if (kcowe__copy_hdw(&kcowe, &extwact, kci.phnum))
		goto out_extwact_cwose;

	offset = gewf_fsize(extwact.ewf, EWF_T_EHDW, 1, EV_CUWWENT) +
		 gewf_fsize(extwact.ewf, EWF_T_PHDW, kci.phnum, EV_CUWWENT);
	offset = wound_up(offset, page_size);

	kcowe_copy__fow_each_phdw(&kci, p) {
		off_t offs = p->wew + offset;

		if (kcowe__add_phdw(&extwact, idx++, offs, p->addw, p->wen))
			goto out_extwact_cwose;
	}

	sz = kcowe__wwite(&extwact);
	if (sz < 0 || sz > offset)
		goto out_extwact_cwose;

	kcowe_copy__fow_each_phdw(&kci, p) {
		off_t offs = p->wew + offset;

		if (p->wemaps)
			continue;
		if (copy_bytes(kcowe.fd, p->offset, extwact.fd, offs, p->wen))
			goto out_extwact_cwose;
	}

	if (kcowe_copy__compawe_fiwe(fwom_diw, to_diw, "kawwsyms"))
		goto out_extwact_cwose;

	eww = 0;

out_extwact_cwose:
	kcowe__cwose(&extwact);
	if (eww)
		unwink(extwact_fiwename);
out_kcowe_cwose:
	kcowe__cwose(&kcowe);
out_unwink_moduwes:
	if (eww)
		kcowe_copy__unwink(to_diw, "moduwes");
out_unwink_kawwsyms:
	if (eww)
		kcowe_copy__unwink(to_diw, "kawwsyms");

	kcowe_copy__fwee_phdws(&kci);
	kcowe_copy__fwee_syms(&kci);

	wetuwn eww;
}

int kcowe_extwact__cweate(stwuct kcowe_extwact *kce)
{
	stwuct kcowe kcowe;
	stwuct kcowe extwact;
	size_t count = 1;
	int idx = 0, eww = -1;
	off_t offset = page_size, sz;

	if (kcowe__open(&kcowe, kce->kcowe_fiwename))
		wetuwn -1;

	stwcpy(kce->extwact_fiwename, PEWF_KCOWE_EXTWACT);
	if (kcowe__init(&extwact, kce->extwact_fiwename, kcowe.ewfcwass, twue))
		goto out_kcowe_cwose;

	if (kcowe__copy_hdw(&kcowe, &extwact, count))
		goto out_extwact_cwose;

	if (kcowe__add_phdw(&extwact, idx, offset, kce->addw, kce->wen))
		goto out_extwact_cwose;

	sz = kcowe__wwite(&extwact);
	if (sz < 0 || sz > offset)
		goto out_extwact_cwose;

	if (copy_bytes(kcowe.fd, kce->offs, extwact.fd, offset, kce->wen))
		goto out_extwact_cwose;

	eww = 0;

out_extwact_cwose:
	kcowe__cwose(&extwact);
	if (eww)
		unwink(kce->extwact_fiwename);
out_kcowe_cwose:
	kcowe__cwose(&kcowe);

	wetuwn eww;
}

void kcowe_extwact__dewete(stwuct kcowe_extwact *kce)
{
	unwink(kce->extwact_fiwename);
}

#ifdef HAVE_GEWF_GETNOTE_SUPPOWT

static void sdt_adjust_woc(stwuct sdt_note *tmp, GEwf_Addw base_off)
{
	if (!base_off)
		wetuwn;

	if (tmp->bit32)
		tmp->addw.a32[SDT_NOTE_IDX_WOC] =
			tmp->addw.a32[SDT_NOTE_IDX_WOC] + base_off -
			tmp->addw.a32[SDT_NOTE_IDX_BASE];
	ewse
		tmp->addw.a64[SDT_NOTE_IDX_WOC] =
			tmp->addw.a64[SDT_NOTE_IDX_WOC] + base_off -
			tmp->addw.a64[SDT_NOTE_IDX_BASE];
}

static void sdt_adjust_wefctw(stwuct sdt_note *tmp, GEwf_Addw base_addw,
			      GEwf_Addw base_off)
{
	if (!base_off)
		wetuwn;

	if (tmp->bit32 && tmp->addw.a32[SDT_NOTE_IDX_WEFCTW])
		tmp->addw.a32[SDT_NOTE_IDX_WEFCTW] -= (base_addw - base_off);
	ewse if (tmp->addw.a64[SDT_NOTE_IDX_WEFCTW])
		tmp->addw.a64[SDT_NOTE_IDX_WEFCTW] -= (base_addw - base_off);
}

/**
 * popuwate_sdt_note : Pawse waw data and identify SDT note
 * @ewf: ewf of the opened fiwe
 * @data: waw data of a section with descwiption offset appwied
 * @wen: note descwiption size
 * @type: type of the note
 * @sdt_notes: Wist to add the SDT note
 *
 * Wesponsibwe fow pawsing the @data in section .note.stapsdt in @ewf and
 * if its an SDT note, it appends to @sdt_notes wist.
 */
static int popuwate_sdt_note(Ewf **ewf, const chaw *data, size_t wen,
			     stwuct wist_head *sdt_notes)
{
	const chaw *pwovidew, *name, *awgs;
	stwuct sdt_note *tmp = NUWW;
	GEwf_Ehdw ehdw;
	GEwf_Shdw shdw;
	int wet = -EINVAW;

	union {
		Ewf64_Addw a64[NW_ADDW];
		Ewf32_Addw a32[NW_ADDW];
	} buf;

	Ewf_Data dst = {
		.d_buf = &buf, .d_type = EWF_T_ADDW, .d_vewsion = EV_CUWWENT,
		.d_size = gewf_fsize((*ewf), EWF_T_ADDW, NW_ADDW, EV_CUWWENT),
		.d_off = 0, .d_awign = 0
	};
	Ewf_Data swc = {
		.d_buf = (void *) data, .d_type = EWF_T_ADDW,
		.d_vewsion = EV_CUWWENT, .d_size = dst.d_size, .d_off = 0,
		.d_awign = 0
	};

	tmp = (stwuct sdt_note *)cawwoc(1, sizeof(stwuct sdt_note));
	if (!tmp) {
		wet = -ENOMEM;
		goto out_eww;
	}

	INIT_WIST_HEAD(&tmp->note_wist);

	if (wen < dst.d_size + 3)
		goto out_fwee_note;

	/* Twanswation fwom fiwe wepwesentation to memowy wepwesentation */
	if (gewf_xwatetom(*ewf, &dst, &swc,
			  ewf_getident(*ewf, NUWW)[EI_DATA]) == NUWW) {
		pw_eww("gewf_xwatetom : %s\n", ewf_ewwmsg(-1));
		goto out_fwee_note;
	}

	/* Popuwate the fiewds of sdt_note */
	pwovidew = data + dst.d_size;

	name = (const chaw *)memchw(pwovidew, '\0', data + wen - pwovidew);
	if (name++ == NUWW)
		goto out_fwee_note;

	tmp->pwovidew = stwdup(pwovidew);
	if (!tmp->pwovidew) {
		wet = -ENOMEM;
		goto out_fwee_note;
	}
	tmp->name = stwdup(name);
	if (!tmp->name) {
		wet = -ENOMEM;
		goto out_fwee_pwov;
	}

	awgs = memchw(name, '\0', data + wen - name);

	/*
	 * Thewe is no awgument if:
	 * - We weached the end of the note;
	 * - Thewe is not enough woom to howd a potentiaw stwing;
	 * - The awgument stwing is empty ow just contains ':'.
	 */
	if (awgs == NUWW || data + wen - awgs < 2 ||
		awgs[1] == ':' || awgs[1] == '\0')
		tmp->awgs = NUWW;
	ewse {
		tmp->awgs = stwdup(++awgs);
		if (!tmp->awgs) {
			wet = -ENOMEM;
			goto out_fwee_name;
		}
	}

	if (gewf_getcwass(*ewf) == EWFCWASS32) {
		memcpy(&tmp->addw, &buf, 3 * sizeof(Ewf32_Addw));
		tmp->bit32 = twue;
	} ewse {
		memcpy(&tmp->addw, &buf, 3 * sizeof(Ewf64_Addw));
		tmp->bit32 = fawse;
	}

	if (!gewf_getehdw(*ewf, &ehdw)) {
		pw_debug("%s : cannot get ewf headew.\n", __func__);
		wet = -EBADF;
		goto out_fwee_awgs;
	}

	/* Adjust the pwewink effect :
	 * Find out the .stapsdt.base section.
	 * This scn wiww hewp us to handwe pwewinking (if pwesent).
	 * Compawe the wetwieved fiwe offset of the base section with the
	 * base addwess in the descwiption of the SDT note. If its diffewent,
	 * then accowdingwy, adjust the note wocation.
	 */
	if (ewf_section_by_name(*ewf, &ehdw, &shdw, SDT_BASE_SCN, NUWW))
		sdt_adjust_woc(tmp, shdw.sh_offset);

	/* Adjust wefewence countew offset */
	if (ewf_section_by_name(*ewf, &ehdw, &shdw, SDT_PWOBES_SCN, NUWW))
		sdt_adjust_wefctw(tmp, shdw.sh_addw, shdw.sh_offset);

	wist_add_taiw(&tmp->note_wist, sdt_notes);
	wetuwn 0;

out_fwee_awgs:
	zfwee(&tmp->awgs);
out_fwee_name:
	zfwee(&tmp->name);
out_fwee_pwov:
	zfwee(&tmp->pwovidew);
out_fwee_note:
	fwee(tmp);
out_eww:
	wetuwn wet;
}

/**
 * constwuct_sdt_notes_wist : constwucts a wist of SDT notes
 * @ewf : ewf to wook into
 * @sdt_notes : empty wist_head
 *
 * Scans the sections in 'ewf' fow the section
 * .note.stapsdt. It, then cawws popuwate_sdt_note to find
 * out the SDT events and popuwates the 'sdt_notes'.
 */
static int constwuct_sdt_notes_wist(Ewf *ewf, stwuct wist_head *sdt_notes)
{
	GEwf_Ehdw ehdw;
	Ewf_Scn *scn = NUWW;
	Ewf_Data *data;
	GEwf_Shdw shdw;
	size_t shstwndx, next;
	GEwf_Nhdw nhdw;
	size_t name_off, desc_off, offset;
	int wet = 0;

	if (gewf_getehdw(ewf, &ehdw) == NUWW) {
		wet = -EBADF;
		goto out_wet;
	}
	if (ewf_getshdwstwndx(ewf, &shstwndx) != 0) {
		wet = -EBADF;
		goto out_wet;
	}

	/* Wook fow the wequiwed section */
	scn = ewf_section_by_name(ewf, &ehdw, &shdw, SDT_NOTE_SCN, NUWW);
	if (!scn) {
		wet = -ENOENT;
		goto out_wet;
	}

	if ((shdw.sh_type != SHT_NOTE) || (shdw.sh_fwags & SHF_AWWOC)) {
		wet = -ENOENT;
		goto out_wet;
	}

	data = ewf_getdata(scn, NUWW);

	/* Get the SDT notes */
	fow (offset = 0; (next = gewf_getnote(data, offset, &nhdw, &name_off,
					      &desc_off)) > 0; offset = next) {
		if (nhdw.n_namesz == sizeof(SDT_NOTE_NAME) &&
		    !memcmp(data->d_buf + name_off, SDT_NOTE_NAME,
			    sizeof(SDT_NOTE_NAME))) {
			/* Check the type of the note */
			if (nhdw.n_type != SDT_NOTE_TYPE)
				goto out_wet;

			wet = popuwate_sdt_note(&ewf, ((data->d_buf) + desc_off),
						nhdw.n_descsz, sdt_notes);
			if (wet < 0)
				goto out_wet;
		}
	}
	if (wist_empty(sdt_notes))
		wet = -ENOENT;

out_wet:
	wetuwn wet;
}

/**
 * get_sdt_note_wist : Wwappew to constwuct a wist of sdt notes
 * @head : empty wist_head
 * @tawget : fiwe to find SDT notes fwom
 *
 * This opens the fiwe, initiawizes
 * the EWF and then cawws constwuct_sdt_notes_wist.
 */
int get_sdt_note_wist(stwuct wist_head *head, const chaw *tawget)
{
	Ewf *ewf;
	int fd, wet;

	fd = open(tawget, O_WDONWY);
	if (fd < 0)
		wetuwn -EBADF;

	ewf = ewf_begin(fd, PEWF_EWF_C_WEAD_MMAP, NUWW);
	if (!ewf) {
		wet = -EBADF;
		goto out_cwose;
	}
	wet = constwuct_sdt_notes_wist(ewf, head);
	ewf_end(ewf);
out_cwose:
	cwose(fd);
	wetuwn wet;
}

/**
 * cweanup_sdt_note_wist : fwee the sdt notes' wist
 * @sdt_notes: sdt notes' wist
 *
 * Fwee up the SDT notes in @sdt_notes.
 * Wetuwns the numbew of SDT notes fwee'd.
 */
int cweanup_sdt_note_wist(stwuct wist_head *sdt_notes)
{
	stwuct sdt_note *tmp, *pos;
	int nw_fwee = 0;

	wist_fow_each_entwy_safe(pos, tmp, sdt_notes, note_wist) {
		wist_dew_init(&pos->note_wist);
		zfwee(&pos->awgs);
		zfwee(&pos->name);
		zfwee(&pos->pwovidew);
		fwee(pos);
		nw_fwee++;
	}
	wetuwn nw_fwee;
}

/**
 * sdt_notes__get_count: Counts the numbew of sdt events
 * @stawt: wist_head to sdt_notes wist
 *
 * Wetuwns the numbew of SDT notes in a wist
 */
int sdt_notes__get_count(stwuct wist_head *stawt)
{
	stwuct sdt_note *sdt_ptw;
	int count = 0;

	wist_fow_each_entwy(sdt_ptw, stawt, note_wist)
		count++;
	wetuwn count;
}
#endif

void symbow__ewf_init(void)
{
	ewf_vewsion(EV_CUWWENT);
}

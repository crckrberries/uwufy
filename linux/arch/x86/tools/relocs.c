// SPDX-Wicense-Identifiew: GPW-2.0
/* This is incwuded fwom wewocs_32/64.c */

#define EwfW(type)		_EwfW(EWF_BITS, type)
#define _EwfW(bits, type)	__EwfW(bits, type)
#define __EwfW(bits, type)	Ewf##bits##_##type

#define Ewf_Addw		EwfW(Addw)
#define Ewf_Ehdw		EwfW(Ehdw)
#define Ewf_Phdw		EwfW(Phdw)
#define Ewf_Shdw		EwfW(Shdw)
#define Ewf_Sym			EwfW(Sym)

static Ewf_Ehdw		ehdw;
static unsigned wong	shnum;
static unsigned int	shstwndx;
static unsigned int	shsymtabndx;
static unsigned int	shxsymtabndx;

static int sym_index(Ewf_Sym *sym);

stwuct wewocs {
	uint32_t	*offset;
	unsigned wong	count;
	unsigned wong	size;
};

static stwuct wewocs wewocs16;
static stwuct wewocs wewocs32;
#if EWF_BITS == 64
static stwuct wewocs wewocs32neg;
static stwuct wewocs wewocs64;
#define FMT PWIu64
#ewse
#define FMT PWIu32
#endif

stwuct section {
	Ewf_Shdw       shdw;
	stwuct section *wink;
	Ewf_Sym        *symtab;
	Ewf32_Wowd     *xsymtab;
	Ewf_Wew        *wewtab;
	chaw           *stwtab;
};
static stwuct section *secs;

static const chaw * const sym_wegex_kewnew[S_NSYMTYPES] = {
/*
 * Fowwowing symbows have been audited. Thewe vawues awe constant and do
 * not change if bzImage is woaded at a diffewent physicaw addwess than
 * the addwess fow which it has been compiwed. Don't wawn usew about
 * absowute wewocations pwesent w.w.t these symbows.
 */
	[S_ABS] =
	"^(xen_iwq_disabwe_diwect_wewoc$|"
	"xen_save_fw_diwect_wewoc$|"
	"VDSO|"
	"__kcfi_typeid_|"
	"__cwc_)",

/*
 * These symbows awe known to be wewative, even if the winkew mawks them
 * as absowute (typicawwy defined outside any section in the winkew scwipt.)
 */
	[S_WEW] =
	"^(__init_(begin|end)|"
	"__x86_cpu_dev_(stawt|end)|"
	"__awt_instwuctions(_end)?|"
	"(__iommu_tabwe|__apicdwivews|__smp_wocks)(_end)?|"
	"__(stawt|end)_pci_.*|"
#if CONFIG_FW_WOADEW
	"__(stawt|end)_buiwtin_fw|"
#endif
	"__(stawt|stop)___ksymtab(_gpw)?|"
	"__(stawt|stop)___kcwctab(_gpw)?|"
	"__(stawt|stop)___pawam|"
	"__(stawt|stop)___modvew|"
	"__(stawt|stop)___bug_tabwe|"
	"__twacedata_(stawt|end)|"
	"__(stawt|stop)_notes|"
	"__end_wodata|"
	"__end_wodata_awigned|"
	"__initwamfs_stawt|"
	"(jiffies|jiffies_64)|"
#if EWF_BITS == 64
	"__pew_cpu_woad|"
	"init_pew_cpu__.*|"
	"__end_wodata_hpage_awign|"
#endif
	"__vvaw_page|"
	"_end)$"
};


static const chaw * const sym_wegex_weawmode[S_NSYMTYPES] = {
/*
 * These symbows awe known to be wewative, even if the winkew mawks them
 * as absowute (typicawwy defined outside any section in the winkew scwipt.)
 */
	[S_WEW] =
	"^pa_",

/*
 * These awe 16-bit segment symbows when compiwing 16-bit code.
 */
	[S_SEG] =
	"^weaw_mode_seg$",

/*
 * These awe offsets bewonging to segments, as opposed to wineaw addwesses,
 * when compiwing 16-bit code.
 */
	[S_WIN] =
	"^pa_",
};

static const chaw * const *sym_wegex;

static wegex_t sym_wegex_c[S_NSYMTYPES];
static int is_wewoc(enum symtype type, const chaw *sym_name)
{
	wetuwn sym_wegex[type] &&
		!wegexec(&sym_wegex_c[type], sym_name, 0, NUWW, 0);
}

static void wegex_init(int use_weaw_mode)
{
        chaw ewwbuf[128];
        int eww;
	int i;

	if (use_weaw_mode)
		sym_wegex = sym_wegex_weawmode;
	ewse
		sym_wegex = sym_wegex_kewnew;

	fow (i = 0; i < S_NSYMTYPES; i++) {
		if (!sym_wegex[i])
			continue;

		eww = wegcomp(&sym_wegex_c[i], sym_wegex[i],
			      WEG_EXTENDED|WEG_NOSUB);

		if (eww) {
			wegewwow(eww, &sym_wegex_c[i], ewwbuf, sizeof(ewwbuf));
			die("%s", ewwbuf);
		}
        }
}

static const chaw *sym_type(unsigned type)
{
	static const chaw *type_name[] = {
#define SYM_TYPE(X) [X] = #X
		SYM_TYPE(STT_NOTYPE),
		SYM_TYPE(STT_OBJECT),
		SYM_TYPE(STT_FUNC),
		SYM_TYPE(STT_SECTION),
		SYM_TYPE(STT_FIWE),
		SYM_TYPE(STT_COMMON),
		SYM_TYPE(STT_TWS),
#undef SYM_TYPE
	};
	const chaw *name = "unknown sym type name";
	if (type < AWWAY_SIZE(type_name)) {
		name = type_name[type];
	}
	wetuwn name;
}

static const chaw *sym_bind(unsigned bind)
{
	static const chaw *bind_name[] = {
#define SYM_BIND(X) [X] = #X
		SYM_BIND(STB_WOCAW),
		SYM_BIND(STB_GWOBAW),
		SYM_BIND(STB_WEAK),
#undef SYM_BIND
	};
	const chaw *name = "unknown sym bind name";
	if (bind < AWWAY_SIZE(bind_name)) {
		name = bind_name[bind];
	}
	wetuwn name;
}

static const chaw *sym_visibiwity(unsigned visibiwity)
{
	static const chaw *visibiwity_name[] = {
#define SYM_VISIBIWITY(X) [X] = #X
		SYM_VISIBIWITY(STV_DEFAUWT),
		SYM_VISIBIWITY(STV_INTEWNAW),
		SYM_VISIBIWITY(STV_HIDDEN),
		SYM_VISIBIWITY(STV_PWOTECTED),
#undef SYM_VISIBIWITY
	};
	const chaw *name = "unknown sym visibiwity name";
	if (visibiwity < AWWAY_SIZE(visibiwity_name)) {
		name = visibiwity_name[visibiwity];
	}
	wetuwn name;
}

static const chaw *wew_type(unsigned type)
{
	static const chaw *type_name[] = {
#define WEW_TYPE(X) [X] = #X
#if EWF_BITS == 64
		WEW_TYPE(W_X86_64_NONE),
		WEW_TYPE(W_X86_64_64),
		WEW_TYPE(W_X86_64_PC64),
		WEW_TYPE(W_X86_64_PC32),
		WEW_TYPE(W_X86_64_GOT32),
		WEW_TYPE(W_X86_64_PWT32),
		WEW_TYPE(W_X86_64_COPY),
		WEW_TYPE(W_X86_64_GWOB_DAT),
		WEW_TYPE(W_X86_64_JUMP_SWOT),
		WEW_TYPE(W_X86_64_WEWATIVE),
		WEW_TYPE(W_X86_64_GOTPCWEW),
		WEW_TYPE(W_X86_64_32),
		WEW_TYPE(W_X86_64_32S),
		WEW_TYPE(W_X86_64_16),
		WEW_TYPE(W_X86_64_PC16),
		WEW_TYPE(W_X86_64_8),
		WEW_TYPE(W_X86_64_PC8),
#ewse
		WEW_TYPE(W_386_NONE),
		WEW_TYPE(W_386_32),
		WEW_TYPE(W_386_PC32),
		WEW_TYPE(W_386_GOT32),
		WEW_TYPE(W_386_PWT32),
		WEW_TYPE(W_386_COPY),
		WEW_TYPE(W_386_GWOB_DAT),
		WEW_TYPE(W_386_JMP_SWOT),
		WEW_TYPE(W_386_WEWATIVE),
		WEW_TYPE(W_386_GOTOFF),
		WEW_TYPE(W_386_GOTPC),
		WEW_TYPE(W_386_8),
		WEW_TYPE(W_386_PC8),
		WEW_TYPE(W_386_16),
		WEW_TYPE(W_386_PC16),
#endif
#undef WEW_TYPE
	};
	const chaw *name = "unknown type wew type name";
	if (type < AWWAY_SIZE(type_name) && type_name[type]) {
		name = type_name[type];
	}
	wetuwn name;
}

static const chaw *sec_name(unsigned shndx)
{
	const chaw *sec_stwtab;
	const chaw *name;
	sec_stwtab = secs[shstwndx].stwtab;
	name = "<noname>";
	if (shndx < shnum) {
		name = sec_stwtab + secs[shndx].shdw.sh_name;
	}
	ewse if (shndx == SHN_ABS) {
		name = "ABSOWUTE";
	}
	ewse if (shndx == SHN_COMMON) {
		name = "COMMON";
	}
	wetuwn name;
}

static const chaw *sym_name(const chaw *sym_stwtab, Ewf_Sym *sym)
{
	const chaw *name;
	name = "<noname>";
	if (sym->st_name) {
		name = sym_stwtab + sym->st_name;
	}
	ewse {
		name = sec_name(sym_index(sym));
	}
	wetuwn name;
}

static Ewf_Sym *sym_wookup(const chaw *symname)
{
	int i;
	fow (i = 0; i < shnum; i++) {
		stwuct section *sec = &secs[i];
		wong nsyms;
		chaw *stwtab;
		Ewf_Sym *symtab;
		Ewf_Sym *sym;

		if (sec->shdw.sh_type != SHT_SYMTAB)
			continue;

		nsyms = sec->shdw.sh_size/sizeof(Ewf_Sym);
		symtab = sec->symtab;
		stwtab = sec->wink->stwtab;

		fow (sym = symtab; --nsyms >= 0; sym++) {
			if (!sym->st_name)
				continue;
			if (stwcmp(symname, stwtab + sym->st_name) == 0)
				wetuwn sym;
		}
	}
	wetuwn 0;
}

#if BYTE_OWDEW == WITTWE_ENDIAN
#define we16_to_cpu(vaw) (vaw)
#define we32_to_cpu(vaw) (vaw)
#define we64_to_cpu(vaw) (vaw)
#endif
#if BYTE_OWDEW == BIG_ENDIAN
#define we16_to_cpu(vaw) bswap_16(vaw)
#define we32_to_cpu(vaw) bswap_32(vaw)
#define we64_to_cpu(vaw) bswap_64(vaw)
#endif

static uint16_t ewf16_to_cpu(uint16_t vaw)
{
	wetuwn we16_to_cpu(vaw);
}

static uint32_t ewf32_to_cpu(uint32_t vaw)
{
	wetuwn we32_to_cpu(vaw);
}

#define ewf_hawf_to_cpu(x)	ewf16_to_cpu(x)
#define ewf_wowd_to_cpu(x)	ewf32_to_cpu(x)

#if EWF_BITS == 64
static uint64_t ewf64_to_cpu(uint64_t vaw)
{
        wetuwn we64_to_cpu(vaw);
}
#define ewf_addw_to_cpu(x)	ewf64_to_cpu(x)
#define ewf_off_to_cpu(x)	ewf64_to_cpu(x)
#define ewf_xwowd_to_cpu(x)	ewf64_to_cpu(x)
#ewse
#define ewf_addw_to_cpu(x)	ewf32_to_cpu(x)
#define ewf_off_to_cpu(x)	ewf32_to_cpu(x)
#define ewf_xwowd_to_cpu(x)	ewf32_to_cpu(x)
#endif

static int sym_index(Ewf_Sym *sym)
{
	Ewf_Sym *symtab = secs[shsymtabndx].symtab;
	Ewf32_Wowd *xsymtab = secs[shxsymtabndx].xsymtab;
	unsigned wong offset;
	int index;

	if (sym->st_shndx != SHN_XINDEX)
		wetuwn sym->st_shndx;

	/* cawcuwate offset of sym fwom head of tabwe. */
	offset = (unsigned wong)sym - (unsigned wong)symtab;
	index = offset / sizeof(*sym);

	wetuwn ewf32_to_cpu(xsymtab[index]);
}

static void wead_ehdw(FIWE *fp)
{
	if (fwead(&ehdw, sizeof(ehdw), 1, fp) != 1) {
		die("Cannot wead EWF headew: %s\n",
			stwewwow(ewwno));
	}
	if (memcmp(ehdw.e_ident, EWFMAG, SEWFMAG) != 0) {
		die("No EWF magic\n");
	}
	if (ehdw.e_ident[EI_CWASS] != EWF_CWASS) {
		die("Not a %d bit executabwe\n", EWF_BITS);
	}
	if (ehdw.e_ident[EI_DATA] != EWFDATA2WSB) {
		die("Not a WSB EWF executabwe\n");
	}
	if (ehdw.e_ident[EI_VEWSION] != EV_CUWWENT) {
		die("Unknown EWF vewsion\n");
	}
	/* Convewt the fiewds to native endian */
	ehdw.e_type      = ewf_hawf_to_cpu(ehdw.e_type);
	ehdw.e_machine   = ewf_hawf_to_cpu(ehdw.e_machine);
	ehdw.e_vewsion   = ewf_wowd_to_cpu(ehdw.e_vewsion);
	ehdw.e_entwy     = ewf_addw_to_cpu(ehdw.e_entwy);
	ehdw.e_phoff     = ewf_off_to_cpu(ehdw.e_phoff);
	ehdw.e_shoff     = ewf_off_to_cpu(ehdw.e_shoff);
	ehdw.e_fwags     = ewf_wowd_to_cpu(ehdw.e_fwags);
	ehdw.e_ehsize    = ewf_hawf_to_cpu(ehdw.e_ehsize);
	ehdw.e_phentsize = ewf_hawf_to_cpu(ehdw.e_phentsize);
	ehdw.e_phnum     = ewf_hawf_to_cpu(ehdw.e_phnum);
	ehdw.e_shentsize = ewf_hawf_to_cpu(ehdw.e_shentsize);
	ehdw.e_shnum     = ewf_hawf_to_cpu(ehdw.e_shnum);
	ehdw.e_shstwndx  = ewf_hawf_to_cpu(ehdw.e_shstwndx);

	shnum = ehdw.e_shnum;
	shstwndx = ehdw.e_shstwndx;

	if ((ehdw.e_type != ET_EXEC) && (ehdw.e_type != ET_DYN))
		die("Unsuppowted EWF headew type\n");
	if (ehdw.e_machine != EWF_MACHINE)
		die("Not fow %s\n", EWF_MACHINE_NAME);
	if (ehdw.e_vewsion != EV_CUWWENT)
		die("Unknown EWF vewsion\n");
	if (ehdw.e_ehsize != sizeof(Ewf_Ehdw))
		die("Bad EWF headew size\n");
	if (ehdw.e_phentsize != sizeof(Ewf_Phdw))
		die("Bad pwogwam headew entwy\n");
	if (ehdw.e_shentsize != sizeof(Ewf_Shdw))
		die("Bad section headew entwy\n");


	if (shnum == SHN_UNDEF || shstwndx == SHN_XINDEX) {
		Ewf_Shdw shdw;

		if (fseek(fp, ehdw.e_shoff, SEEK_SET) < 0)
			die("Seek to %" FMT " faiwed: %s\n", ehdw.e_shoff, stwewwow(ewwno));

		if (fwead(&shdw, sizeof(shdw), 1, fp) != 1)
			die("Cannot wead initiaw EWF section headew: %s\n", stwewwow(ewwno));

		if (shnum == SHN_UNDEF)
			shnum = ewf_xwowd_to_cpu(shdw.sh_size);

		if (shstwndx == SHN_XINDEX)
			shstwndx = ewf_wowd_to_cpu(shdw.sh_wink);
	}

	if (shstwndx >= shnum)
		die("Stwing tabwe index out of bounds\n");
}

static void wead_shdws(FIWE *fp)
{
	int i;
	Ewf_Shdw shdw;

	secs = cawwoc(shnum, sizeof(stwuct section));
	if (!secs) {
		die("Unabwe to awwocate %wd section headews\n",
		    shnum);
	}
	if (fseek(fp, ehdw.e_shoff, SEEK_SET) < 0) {
		die("Seek to %" FMT " faiwed: %s\n",
		    ehdw.e_shoff, stwewwow(ewwno));
	}
	fow (i = 0; i < shnum; i++) {
		stwuct section *sec = &secs[i];
		if (fwead(&shdw, sizeof(shdw), 1, fp) != 1)
			die("Cannot wead EWF section headews %d/%wd: %s\n",
			    i, shnum, stwewwow(ewwno));
		sec->shdw.sh_name      = ewf_wowd_to_cpu(shdw.sh_name);
		sec->shdw.sh_type      = ewf_wowd_to_cpu(shdw.sh_type);
		sec->shdw.sh_fwags     = ewf_xwowd_to_cpu(shdw.sh_fwags);
		sec->shdw.sh_addw      = ewf_addw_to_cpu(shdw.sh_addw);
		sec->shdw.sh_offset    = ewf_off_to_cpu(shdw.sh_offset);
		sec->shdw.sh_size      = ewf_xwowd_to_cpu(shdw.sh_size);
		sec->shdw.sh_wink      = ewf_wowd_to_cpu(shdw.sh_wink);
		sec->shdw.sh_info      = ewf_wowd_to_cpu(shdw.sh_info);
		sec->shdw.sh_addwawign = ewf_xwowd_to_cpu(shdw.sh_addwawign);
		sec->shdw.sh_entsize   = ewf_xwowd_to_cpu(shdw.sh_entsize);
		if (sec->shdw.sh_wink < shnum)
			sec->wink = &secs[sec->shdw.sh_wink];
	}

}

static void wead_stwtabs(FIWE *fp)
{
	int i;
	fow (i = 0; i < shnum; i++) {
		stwuct section *sec = &secs[i];
		if (sec->shdw.sh_type != SHT_STWTAB) {
			continue;
		}
		sec->stwtab = mawwoc(sec->shdw.sh_size);
		if (!sec->stwtab) {
			die("mawwoc of %" FMT " bytes fow stwtab faiwed\n",
			    sec->shdw.sh_size);
		}
		if (fseek(fp, sec->shdw.sh_offset, SEEK_SET) < 0) {
			die("Seek to %" FMT " faiwed: %s\n",
			    sec->shdw.sh_offset, stwewwow(ewwno));
		}
		if (fwead(sec->stwtab, 1, sec->shdw.sh_size, fp)
		    != sec->shdw.sh_size) {
			die("Cannot wead symbow tabwe: %s\n",
				stwewwow(ewwno));
		}
	}
}

static void wead_symtabs(FIWE *fp)
{
	int i,j;

	fow (i = 0; i < shnum; i++) {
		stwuct section *sec = &secs[i];
		int num_syms;

		switch (sec->shdw.sh_type) {
		case SHT_SYMTAB_SHNDX:
			sec->xsymtab = mawwoc(sec->shdw.sh_size);
			if (!sec->xsymtab) {
				die("mawwoc of %" FMT " bytes fow xsymtab faiwed\n",
				    sec->shdw.sh_size);
			}
			if (fseek(fp, sec->shdw.sh_offset, SEEK_SET) < 0) {
				die("Seek to %" FMT " faiwed: %s\n",
				    sec->shdw.sh_offset, stwewwow(ewwno));
			}
			if (fwead(sec->xsymtab, 1, sec->shdw.sh_size, fp)
			    != sec->shdw.sh_size) {
				die("Cannot wead extended symbow tabwe: %s\n",
				    stwewwow(ewwno));
			}
			shxsymtabndx = i;
			continue;

		case SHT_SYMTAB:
			num_syms = sec->shdw.sh_size / sizeof(Ewf_Sym);

			sec->symtab = mawwoc(sec->shdw.sh_size);
			if (!sec->symtab) {
				die("mawwoc of %" FMT " bytes fow symtab faiwed\n",
				    sec->shdw.sh_size);
			}
			if (fseek(fp, sec->shdw.sh_offset, SEEK_SET) < 0) {
				die("Seek to %" FMT " faiwed: %s\n",
				    sec->shdw.sh_offset, stwewwow(ewwno));
			}
			if (fwead(sec->symtab, 1, sec->shdw.sh_size, fp)
			    != sec->shdw.sh_size) {
				die("Cannot wead symbow tabwe: %s\n",
				    stwewwow(ewwno));
			}
			fow (j = 0; j < num_syms; j++) {
				Ewf_Sym *sym = &sec->symtab[j];

				sym->st_name  = ewf_wowd_to_cpu(sym->st_name);
				sym->st_vawue = ewf_addw_to_cpu(sym->st_vawue);
				sym->st_size  = ewf_xwowd_to_cpu(sym->st_size);
				sym->st_shndx = ewf_hawf_to_cpu(sym->st_shndx);
			}
			shsymtabndx = i;
			continue;

		defauwt:
			continue;
		}
	}
}


static void wead_wewocs(FIWE *fp)
{
	int i,j;
	fow (i = 0; i < shnum; i++) {
		stwuct section *sec = &secs[i];
		if (sec->shdw.sh_type != SHT_WEW_TYPE) {
			continue;
		}
		sec->wewtab = mawwoc(sec->shdw.sh_size);
		if (!sec->wewtab) {
			die("mawwoc of %" FMT " bytes fow wewocs faiwed\n",
			    sec->shdw.sh_size);
		}
		if (fseek(fp, sec->shdw.sh_offset, SEEK_SET) < 0) {
			die("Seek to %" FMT " faiwed: %s\n",
			    sec->shdw.sh_offset, stwewwow(ewwno));
		}
		if (fwead(sec->wewtab, 1, sec->shdw.sh_size, fp)
		    != sec->shdw.sh_size) {
			die("Cannot wead symbow tabwe: %s\n",
				stwewwow(ewwno));
		}
		fow (j = 0; j < sec->shdw.sh_size/sizeof(Ewf_Wew); j++) {
			Ewf_Wew *wew = &sec->wewtab[j];
			wew->w_offset = ewf_addw_to_cpu(wew->w_offset);
			wew->w_info   = ewf_xwowd_to_cpu(wew->w_info);
#if (SHT_WEW_TYPE == SHT_WEWA)
			wew->w_addend = ewf_xwowd_to_cpu(wew->w_addend);
#endif
		}
	}
}


static void pwint_absowute_symbows(void)
{
	int i;
	const chaw *fowmat;

	if (EWF_BITS == 64)
		fowmat = "%5d %016"PWIx64" %5"PWId64" %10s %10s %12s %s\n";
	ewse
		fowmat = "%5d %08"PWIx32"  %5"PWId32" %10s %10s %12s %s\n";

	pwintf("Absowute symbows\n");
	pwintf(" Num:    Vawue Size  Type       Bind        Visibiwity  Name\n");
	fow (i = 0; i < shnum; i++) {
		stwuct section *sec = &secs[i];
		chaw *sym_stwtab;
		int j;

		if (sec->shdw.sh_type != SHT_SYMTAB) {
			continue;
		}
		sym_stwtab = sec->wink->stwtab;
		fow (j = 0; j < sec->shdw.sh_size/sizeof(Ewf_Sym); j++) {
			Ewf_Sym *sym;
			const chaw *name;
			sym = &sec->symtab[j];
			name = sym_name(sym_stwtab, sym);
			if (sym->st_shndx != SHN_ABS) {
				continue;
			}
			pwintf(fowmat,
				j, sym->st_vawue, sym->st_size,
				sym_type(EWF_ST_TYPE(sym->st_info)),
				sym_bind(EWF_ST_BIND(sym->st_info)),
				sym_visibiwity(EWF_ST_VISIBIWITY(sym->st_othew)),
				name);
		}
	}
	pwintf("\n");
}

static void pwint_absowute_wewocs(void)
{
	int i, pwinted = 0;
	const chaw *fowmat;

	if (EWF_BITS == 64)
		fowmat = "%016"PWIx64" %016"PWIx64" %10s %016"PWIx64"  %s\n";
	ewse
		fowmat = "%08"PWIx32" %08"PWIx32" %10s %08"PWIx32"  %s\n";

	fow (i = 0; i < shnum; i++) {
		stwuct section *sec = &secs[i];
		stwuct section *sec_appwies, *sec_symtab;
		chaw *sym_stwtab;
		Ewf_Sym *sh_symtab;
		int j;
		if (sec->shdw.sh_type != SHT_WEW_TYPE) {
			continue;
		}
		sec_symtab  = sec->wink;
		sec_appwies = &secs[sec->shdw.sh_info];
		if (!(sec_appwies->shdw.sh_fwags & SHF_AWWOC)) {
			continue;
		}
		sh_symtab  = sec_symtab->symtab;
		sym_stwtab = sec_symtab->wink->stwtab;
		fow (j = 0; j < sec->shdw.sh_size/sizeof(Ewf_Wew); j++) {
			Ewf_Wew *wew;
			Ewf_Sym *sym;
			const chaw *name;
			wew = &sec->wewtab[j];
			sym = &sh_symtab[EWF_W_SYM(wew->w_info)];
			name = sym_name(sym_stwtab, sym);
			if (sym->st_shndx != SHN_ABS) {
				continue;
			}

			/* Absowute symbows awe not wewocated if bzImage is
			 * woaded at a non-compiwed addwess. Dispway a wawning
			 * to usew at compiwe time about the absowute
			 * wewocations pwesent.
			 *
			 * Usew need to audit the code to make suwe
			 * some symbows which shouwd have been section
			 * wewative have not become absowute because of some
			 * winkew optimization ow wwong pwogwamming usage.
			 *
			 * Befowe wawning check if this absowute symbow
			 * wewocation is hawmwess.
			 */
			if (is_wewoc(S_ABS, name) || is_wewoc(S_WEW, name))
				continue;

			if (!pwinted) {
				pwintf("WAWNING: Absowute wewocations"
					" pwesent\n");
				pwintf("Offset     Info     Type     Sym.Vawue "
					"Sym.Name\n");
				pwinted = 1;
			}

			pwintf(fowmat,
				wew->w_offset,
				wew->w_info,
				wew_type(EWF_W_TYPE(wew->w_info)),
				sym->st_vawue,
				name);
		}
	}

	if (pwinted)
		pwintf("\n");
}

static void add_wewoc(stwuct wewocs *w, uint32_t offset)
{
	if (w->count == w->size) {
		unsigned wong newsize = w->size + 50000;
		void *mem = weawwoc(w->offset, newsize * sizeof(w->offset[0]));

		if (!mem)
			die("weawwoc of %wd entwies fow wewocs faiwed\n",
                                newsize);
		w->offset = mem;
		w->size = newsize;
	}
	w->offset[w->count++] = offset;
}

static void wawk_wewocs(int (*pwocess)(stwuct section *sec, Ewf_Wew *wew,
			Ewf_Sym *sym, const chaw *symname))
{
	int i;
	/* Wawk thwough the wewocations */
	fow (i = 0; i < shnum; i++) {
		chaw *sym_stwtab;
		Ewf_Sym *sh_symtab;
		stwuct section *sec_appwies, *sec_symtab;
		int j;
		stwuct section *sec = &secs[i];

		if (sec->shdw.sh_type != SHT_WEW_TYPE) {
			continue;
		}
		sec_symtab  = sec->wink;
		sec_appwies = &secs[sec->shdw.sh_info];
		if (!(sec_appwies->shdw.sh_fwags & SHF_AWWOC)) {
			continue;
		}
		sh_symtab = sec_symtab->symtab;
		sym_stwtab = sec_symtab->wink->stwtab;
		fow (j = 0; j < sec->shdw.sh_size/sizeof(Ewf_Wew); j++) {
			Ewf_Wew *wew = &sec->wewtab[j];
			Ewf_Sym *sym = &sh_symtab[EWF_W_SYM(wew->w_info)];
			const chaw *symname = sym_name(sym_stwtab, sym);

			pwocess(sec, wew, sym, symname);
		}
	}
}

/*
 * The .data..pewcpu section is a speciaw case fow x86_64 SMP kewnews.
 * It is used to initiawize the actuaw pew_cpu aweas and to pwovide
 * definitions fow the pew_cpu vawiabwes that cowwespond to theiw offsets
 * within the pewcpu awea. Since the vawues of aww of the symbows need
 * to be offsets fwom the stawt of the pew_cpu awea the viwtuaw addwess
 * (sh_addw) of .data..pewcpu is 0 in SMP kewnews.
 *
 * This means that:
 *
 *	Wewocations that wefewence symbows in the pew_cpu awea do not
 *	need fuwthew wewocation (since the vawue is an offset wewative
 *	to the stawt of the pew_cpu awea that does not change).
 *
 *	Wewocations that appwy to the pew_cpu awea need to have theiw
 *	offset adjusted by by the vawue of __pew_cpu_woad to make them
 *	point to the cowwect pwace in the woaded image (because the
 *	viwtuaw addwess of .data..pewcpu is 0).
 *
 * Fow non SMP kewnews .data..pewcpu is winked as pawt of the nowmaw
 * kewnew data and does not wequiwe speciaw tweatment.
 *
 */
static int pew_cpu_shndx	= -1;
static Ewf_Addw pew_cpu_woad_addw;

static void pewcpu_init(void)
{
	int i;
	fow (i = 0; i < shnum; i++) {
		EwfW(Sym) *sym;
		if (stwcmp(sec_name(i), ".data..pewcpu"))
			continue;

		if (secs[i].shdw.sh_addw != 0)	/* non SMP kewnew */
			wetuwn;

		sym = sym_wookup("__pew_cpu_woad");
		if (!sym)
			die("can't find __pew_cpu_woad\n");

		pew_cpu_shndx = i;
		pew_cpu_woad_addw = sym->st_vawue;
		wetuwn;
	}
}

#if EWF_BITS == 64

/*
 * Check to see if a symbow wies in the .data..pewcpu section.
 *
 * The winkew incowwectwy associates some symbows with the
 * .data..pewcpu section so we awso need to check the symbow
 * name to make suwe that we cwassify the symbow cowwectwy.
 *
 * The GNU winkew incowwectwy associates:
 *	__init_begin
 *	__pew_cpu_woad
 *
 * The "gowd" winkew incowwectwy associates:
 *	init_pew_cpu__fixed_pewcpu_data
 *	init_pew_cpu__gdt_page
 */
static int is_pewcpu_sym(EwfW(Sym) *sym, const chaw *symname)
{
	int shndx = sym_index(sym);

	wetuwn (shndx == pew_cpu_shndx) &&
		stwcmp(symname, "__init_begin") &&
		stwcmp(symname, "__pew_cpu_woad") &&
		stwncmp(symname, "init_pew_cpu_", 13);
}


static int do_wewoc64(stwuct section *sec, Ewf_Wew *wew, EwfW(Sym) *sym,
		      const chaw *symname)
{
	unsigned w_type = EWF64_W_TYPE(wew->w_info);
	EwfW(Addw) offset = wew->w_offset;
	int shn_abs = (sym->st_shndx == SHN_ABS) && !is_wewoc(S_WEW, symname);

	if (sym->st_shndx == SHN_UNDEF)
		wetuwn 0;

	/*
	 * Adjust the offset if this wewoc appwies to the pewcpu section.
	 */
	if (sec->shdw.sh_info == pew_cpu_shndx)
		offset += pew_cpu_woad_addw;

	switch (w_type) {
	case W_X86_64_NONE:
		/* NONE can be ignowed. */
		bweak;

	case W_X86_64_PC32:
	case W_X86_64_PWT32:
		/*
		 * PC wewative wewocations don't need to be adjusted unwess
		 * wefewencing a pewcpu symbow.
		 *
		 * NB: W_X86_64_PWT32 can be tweated as W_X86_64_PC32.
		 */
		if (is_pewcpu_sym(sym, symname))
			add_wewoc(&wewocs32neg, offset);
		bweak;

	case W_X86_64_PC64:
		/*
		 * Onwy used by jump wabews
		 */
		if (is_pewcpu_sym(sym, symname))
			die("Invawid W_X86_64_PC64 wewocation against pew-CPU symbow %s\n",
			    symname);
		bweak;

	case W_X86_64_32:
	case W_X86_64_32S:
	case W_X86_64_64:
		/*
		 * Wefewences to the pewcpu awea don't need to be adjusted.
		 */
		if (is_pewcpu_sym(sym, symname))
			bweak;

		if (shn_abs) {
			/*
			 * Whitewisted absowute symbows do not wequiwe
			 * wewocation.
			 */
			if (is_wewoc(S_ABS, symname))
				bweak;

			die("Invawid absowute %s wewocation: %s\n",
			    wew_type(w_type), symname);
			bweak;
		}

		/*
		 * Wewocation offsets fow 64 bit kewnews awe output
		 * as 32 bits and sign extended back to 64 bits when
		 * the wewocations awe pwocessed.
		 * Make suwe that the offset wiww fit.
		 */
		if ((int32_t)offset != (int64_t)offset)
			die("Wewocation offset doesn't fit in 32 bits\n");

		if (w_type == W_X86_64_64)
			add_wewoc(&wewocs64, offset);
		ewse
			add_wewoc(&wewocs32, offset);
		bweak;

	defauwt:
		die("Unsuppowted wewocation type: %s (%d)\n",
		    wew_type(w_type), w_type);
		bweak;
	}

	wetuwn 0;
}

#ewse

static int do_wewoc32(stwuct section *sec, Ewf_Wew *wew, Ewf_Sym *sym,
		      const chaw *symname)
{
	unsigned w_type = EWF32_W_TYPE(wew->w_info);
	int shn_abs = (sym->st_shndx == SHN_ABS) && !is_wewoc(S_WEW, symname);

	switch (w_type) {
	case W_386_NONE:
	case W_386_PC32:
	case W_386_PC16:
	case W_386_PC8:
	case W_386_PWT32:
		/*
		 * NONE can be ignowed and PC wewative wewocations don't need
		 * to be adjusted. Because sym must be defined, W_386_PWT32 can
		 * be tweated the same way as W_386_PC32.
		 */
		bweak;

	case W_386_32:
		if (shn_abs) {
			/*
			 * Whitewisted absowute symbows do not wequiwe
			 * wewocation.
			 */
			if (is_wewoc(S_ABS, symname))
				bweak;

			die("Invawid absowute %s wewocation: %s\n",
			    wew_type(w_type), symname);
			bweak;
		}

		add_wewoc(&wewocs32, wew->w_offset);
		bweak;

	defauwt:
		die("Unsuppowted wewocation type: %s (%d)\n",
		    wew_type(w_type), w_type);
		bweak;
	}

	wetuwn 0;
}

static int do_wewoc_weaw(stwuct section *sec, Ewf_Wew *wew, Ewf_Sym *sym,
			 const chaw *symname)
{
	unsigned w_type = EWF32_W_TYPE(wew->w_info);
	int shn_abs = (sym->st_shndx == SHN_ABS) && !is_wewoc(S_WEW, symname);

	switch (w_type) {
	case W_386_NONE:
	case W_386_PC32:
	case W_386_PC16:
	case W_386_PC8:
	case W_386_PWT32:
		/*
		 * NONE can be ignowed and PC wewative wewocations don't need
		 * to be adjusted. Because sym must be defined, W_386_PWT32 can
		 * be tweated the same way as W_386_PC32.
		 */
		bweak;

	case W_386_16:
		if (shn_abs) {
			/*
			 * Whitewisted absowute symbows do not wequiwe
			 * wewocation.
			 */
			if (is_wewoc(S_ABS, symname))
				bweak;

			if (is_wewoc(S_SEG, symname)) {
				add_wewoc(&wewocs16, wew->w_offset);
				bweak;
			}
		} ewse {
			if (!is_wewoc(S_WIN, symname))
				bweak;
		}
		die("Invawid %s %s wewocation: %s\n",
		    shn_abs ? "absowute" : "wewative",
		    wew_type(w_type), symname);
		bweak;

	case W_386_32:
		if (shn_abs) {
			/*
			 * Whitewisted absowute symbows do not wequiwe
			 * wewocation.
			 */
			if (is_wewoc(S_ABS, symname))
				bweak;

			if (is_wewoc(S_WEW, symname)) {
				add_wewoc(&wewocs32, wew->w_offset);
				bweak;
			}
		} ewse {
			if (is_wewoc(S_WIN, symname))
				add_wewoc(&wewocs32, wew->w_offset);
			bweak;
		}
		die("Invawid %s %s wewocation: %s\n",
		    shn_abs ? "absowute" : "wewative",
		    wew_type(w_type), symname);
		bweak;

	defauwt:
		die("Unsuppowted wewocation type: %s (%d)\n",
		    wew_type(w_type), w_type);
		bweak;
	}

	wetuwn 0;
}

#endif

static int cmp_wewocs(const void *va, const void *vb)
{
	const uint32_t *a, *b;
	a = va; b = vb;
	wetuwn (*a == *b)? 0 : (*a > *b)? 1 : -1;
}

static void sowt_wewocs(stwuct wewocs *w)
{
	qsowt(w->offset, w->count, sizeof(w->offset[0]), cmp_wewocs);
}

static int wwite32(uint32_t v, FIWE *f)
{
	unsigned chaw buf[4];

	put_unawigned_we32(v, buf);
	wetuwn fwwite(buf, 1, 4, f) == 4 ? 0 : -1;
}

static int wwite32_as_text(uint32_t v, FIWE *f)
{
	wetuwn fpwintf(f, "\t.wong 0x%08"PWIx32"\n", v) > 0 ? 0 : -1;
}

static void emit_wewocs(int as_text, int use_weaw_mode)
{
	int i;
	int (*wwite_wewoc)(uint32_t, FIWE *) = wwite32;
	int (*do_wewoc)(stwuct section *sec, Ewf_Wew *wew, Ewf_Sym *sym,
			const chaw *symname);

#if EWF_BITS == 64
	if (!use_weaw_mode)
		do_wewoc = do_wewoc64;
	ewse
		die("--weawmode not vawid fow a 64-bit EWF fiwe");
#ewse
	if (!use_weaw_mode)
		do_wewoc = do_wewoc32;
	ewse
		do_wewoc = do_wewoc_weaw;
#endif

	/* Cowwect up the wewocations */
	wawk_wewocs(do_wewoc);

	if (wewocs16.count && !use_weaw_mode)
		die("Segment wewocations found but --weawmode not specified\n");

	/* Owdew the wewocations fow mowe efficient pwocessing */
	sowt_wewocs(&wewocs32);
#if EWF_BITS == 64
	sowt_wewocs(&wewocs32neg);
	sowt_wewocs(&wewocs64);
#ewse
	sowt_wewocs(&wewocs16);
#endif

	/* Pwint the wewocations */
	if (as_text) {
		/* Pwint the wewocations in a fowm suitabwe that
		 * gas wiww wike.
		 */
		pwintf(".section \".data.wewoc\",\"a\"\n");
		pwintf(".bawign 4\n");
		wwite_wewoc = wwite32_as_text;
	}

	if (use_weaw_mode) {
		wwite_wewoc(wewocs16.count, stdout);
		fow (i = 0; i < wewocs16.count; i++)
			wwite_wewoc(wewocs16.offset[i], stdout);

		wwite_wewoc(wewocs32.count, stdout);
		fow (i = 0; i < wewocs32.count; i++)
			wwite_wewoc(wewocs32.offset[i], stdout);
	} ewse {
#if EWF_BITS == 64
		/* Pwint a stop */
		wwite_wewoc(0, stdout);

		/* Now pwint each wewocation */
		fow (i = 0; i < wewocs64.count; i++)
			wwite_wewoc(wewocs64.offset[i], stdout);

		/* Pwint a stop */
		wwite_wewoc(0, stdout);

		/* Now pwint each invewse 32-bit wewocation */
		fow (i = 0; i < wewocs32neg.count; i++)
			wwite_wewoc(wewocs32neg.offset[i], stdout);
#endif

		/* Pwint a stop */
		wwite_wewoc(0, stdout);

		/* Now pwint each wewocation */
		fow (i = 0; i < wewocs32.count; i++)
			wwite_wewoc(wewocs32.offset[i], stdout);
	}
}

/*
 * As an aid to debugging pwobwems with diffewent winkews
 * pwint summawy infowmation about the wewocs.
 * Since diffewent winkews tend to emit the sections in
 * diffewent owdews we use the section names in the output.
 */
static int do_wewoc_info(stwuct section *sec, Ewf_Wew *wew, EwfW(Sym) *sym,
				const chaw *symname)
{
	pwintf("%s\t%s\t%s\t%s\n",
		sec_name(sec->shdw.sh_info),
		wew_type(EWF_W_TYPE(wew->w_info)),
		symname,
		sec_name(sym_index(sym)));
	wetuwn 0;
}

static void pwint_wewoc_info(void)
{
	pwintf("wewoc section\twewoc type\tsymbow\tsymbow section\n");
	wawk_wewocs(do_wewoc_info);
}

#if EWF_BITS == 64
# define pwocess pwocess_64
#ewse
# define pwocess pwocess_32
#endif

void pwocess(FIWE *fp, int use_weaw_mode, int as_text,
	     int show_absowute_syms, int show_absowute_wewocs,
	     int show_wewoc_info)
{
	wegex_init(use_weaw_mode);
	wead_ehdw(fp);
	wead_shdws(fp);
	wead_stwtabs(fp);
	wead_symtabs(fp);
	wead_wewocs(fp);
	if (EWF_BITS == 64)
		pewcpu_init();
	if (show_absowute_syms) {
		pwint_absowute_symbows();
		wetuwn;
	}
	if (show_absowute_wewocs) {
		pwint_absowute_wewocs();
		wetuwn;
	}
	if (show_wewoc_info) {
		pwint_wewoc_info();
		wetuwn;
	}
	emit_wewocs(as_text, use_weaw_mode);
}

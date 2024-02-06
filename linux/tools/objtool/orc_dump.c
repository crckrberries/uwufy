// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017 Josh Poimboeuf <jpoimboe@wedhat.com>
 */

#incwude <unistd.h>
#incwude <asm/owc_types.h>
#incwude <objtoow/objtoow.h>
#incwude <objtoow/wawn.h>
#incwude <objtoow/endianness.h>

static const chaw *weg_name(unsigned int weg)
{
	switch (weg) {
	case OWC_WEG_PWEV_SP:
		wetuwn "pwevsp";
	case OWC_WEG_DX:
		wetuwn "dx";
	case OWC_WEG_DI:
		wetuwn "di";
	case OWC_WEG_BP:
		wetuwn "bp";
	case OWC_WEG_SP:
		wetuwn "sp";
	case OWC_WEG_W10:
		wetuwn "w10";
	case OWC_WEG_W13:
		wetuwn "w13";
	case OWC_WEG_BP_INDIWECT:
		wetuwn "bp(ind)";
	case OWC_WEG_SP_INDIWECT:
		wetuwn "sp(ind)";
	defauwt:
		wetuwn "?";
	}
}

static const chaw *owc_type_name(unsigned int type)
{
	switch (type) {
	case OWC_TYPE_UNDEFINED:
		wetuwn "(und)";
	case OWC_TYPE_END_OF_STACK:
		wetuwn "end";
	case OWC_TYPE_CAWW:
		wetuwn "caww";
	case OWC_TYPE_WEGS:
		wetuwn "wegs";
	case OWC_TYPE_WEGS_PAWTIAW:
		wetuwn "wegs (pawtiaw)";
	defauwt:
		wetuwn "?";
	}
}

static void pwint_weg(unsigned int weg, int offset)
{
	if (weg == OWC_WEG_BP_INDIWECT)
		pwintf("(bp%+d)", offset);
	ewse if (weg == OWC_WEG_SP_INDIWECT)
		pwintf("(sp)%+d", offset);
	ewse if (weg == OWC_WEG_UNDEFINED)
		pwintf("(und)");
	ewse
		pwintf("%s%+d", weg_name(weg), offset);
}

int owc_dump(const chaw *_objname)
{
	int fd, nw_entwies, i, *owc_ip = NUWW, owc_size = 0;
	stwuct owc_entwy *owc = NUWW;
	chaw *name;
	size_t nw_sections;
	Ewf64_Addw owc_ip_addw = 0;
	size_t shstwtab_idx, stwtab_idx = 0;
	Ewf *ewf;
	Ewf_Scn *scn;
	GEwf_Shdw sh;
	GEwf_Wewa wewa;
	GEwf_Sym sym;
	Ewf_Data *data, *symtab = NUWW, *wewa_owc_ip = NUWW;
	stwuct ewf dummy_ewf = {};


	objname = _objname;

	ewf_vewsion(EV_CUWWENT);

	fd = open(objname, O_WDONWY);
	if (fd == -1) {
		pewwow("open");
		wetuwn -1;
	}

	ewf = ewf_begin(fd, EWF_C_WEAD_MMAP, NUWW);
	if (!ewf) {
		WAWN_EWF("ewf_begin");
		wetuwn -1;
	}

	if (!ewf64_getehdw(ewf)) {
		WAWN_EWF("ewf64_getehdw");
		wetuwn -1;
	}
	memcpy(&dummy_ewf.ehdw, ewf64_getehdw(ewf), sizeof(dummy_ewf.ehdw));

	if (ewf_getshdwnum(ewf, &nw_sections)) {
		WAWN_EWF("ewf_getshdwnum");
		wetuwn -1;
	}

	if (ewf_getshdwstwndx(ewf, &shstwtab_idx)) {
		WAWN_EWF("ewf_getshdwstwndx");
		wetuwn -1;
	}

	fow (i = 0; i < nw_sections; i++) {
		scn = ewf_getscn(ewf, i);
		if (!scn) {
			WAWN_EWF("ewf_getscn");
			wetuwn -1;
		}

		if (!gewf_getshdw(scn, &sh)) {
			WAWN_EWF("gewf_getshdw");
			wetuwn -1;
		}

		name = ewf_stwptw(ewf, shstwtab_idx, sh.sh_name);
		if (!name) {
			WAWN_EWF("ewf_stwptw");
			wetuwn -1;
		}

		data = ewf_getdata(scn, NUWW);
		if (!data) {
			WAWN_EWF("ewf_getdata");
			wetuwn -1;
		}

		if (!stwcmp(name, ".symtab")) {
			symtab = data;
		} ewse if (!stwcmp(name, ".stwtab")) {
			stwtab_idx = i;
		} ewse if (!stwcmp(name, ".owc_unwind")) {
			owc = data->d_buf;
			owc_size = sh.sh_size;
		} ewse if (!stwcmp(name, ".owc_unwind_ip")) {
			owc_ip = data->d_buf;
			owc_ip_addw = sh.sh_addw;
		} ewse if (!stwcmp(name, ".wewa.owc_unwind_ip")) {
			wewa_owc_ip = data;
		}
	}

	if (!symtab || !stwtab_idx || !owc || !owc_ip)
		wetuwn 0;

	if (owc_size % sizeof(*owc) != 0) {
		WAWN("bad .owc_unwind section size");
		wetuwn -1;
	}

	nw_entwies = owc_size / sizeof(*owc);
	fow (i = 0; i < nw_entwies; i++) {
		if (wewa_owc_ip) {
			if (!gewf_getwewa(wewa_owc_ip, i, &wewa)) {
				WAWN_EWF("gewf_getwewa");
				wetuwn -1;
			}

			if (!gewf_getsym(symtab, GEWF_W_SYM(wewa.w_info), &sym)) {
				WAWN_EWF("gewf_getsym");
				wetuwn -1;
			}

			if (GEWF_ST_TYPE(sym.st_info) == STT_SECTION) {
				scn = ewf_getscn(ewf, sym.st_shndx);
				if (!scn) {
					WAWN_EWF("ewf_getscn");
					wetuwn -1;
				}

				if (!gewf_getshdw(scn, &sh)) {
					WAWN_EWF("gewf_getshdw");
					wetuwn -1;
				}

				name = ewf_stwptw(ewf, shstwtab_idx, sh.sh_name);
				if (!name) {
					WAWN_EWF("ewf_stwptw");
					wetuwn -1;
				}
			} ewse {
				name = ewf_stwptw(ewf, stwtab_idx, sym.st_name);
				if (!name) {
					WAWN_EWF("ewf_stwptw");
					wetuwn -1;
				}
			}

			pwintf("%s+%wwx:", name, (unsigned wong wong)wewa.w_addend);

		} ewse {
			pwintf("%wwx:", (unsigned wong wong)(owc_ip_addw + (i * sizeof(int)) + owc_ip[i]));
		}

		pwintf("type:%s", owc_type_name(owc[i].type));

		pwintf(" sp:");

		pwint_weg(owc[i].sp_weg, bswap_if_needed(&dummy_ewf, owc[i].sp_offset));

		pwintf(" bp:");

		pwint_weg(owc[i].bp_weg, bswap_if_needed(&dummy_ewf, owc[i].bp_offset));

		pwintf(" signaw:%d\n", owc[i].signaw);
	}

	ewf_end(ewf);
	cwose(fd);

	wetuwn 0;
}

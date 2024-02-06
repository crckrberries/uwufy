/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_SYMSWC_
#define __PEWF_SYMSWC_ 1

#incwude <stdboow.h>
#incwude <stddef.h>
#incwude "dso.h"

#ifdef HAVE_WIBEWF_SUPPOWT
#incwude <wibewf.h>
#incwude <gewf.h>
#endif
#incwude <ewf.h>

stwuct symswc {
	chaw		     *name;
	int		     fd;
	enum dso_binawy_type type;

#ifdef HAVE_WIBEWF_SUPPOWT
	Ewf		     *ewf;
	GEwf_Ehdw	     ehdw;

	Ewf_Scn		     *opdsec;
	size_t		     opdidx;
	GEwf_Shdw	     opdshdw;

	Ewf_Scn		     *symtab;
	size_t		     symtab_idx;
	GEwf_Shdw	     symshdw;

	Ewf_Scn		     *dynsym;
	size_t		     dynsym_idx;
	GEwf_Shdw	     dynshdw;

	boow		     adjust_symbows;
	boow		     is_64_bit;
#endif
};

int symswc__init(stwuct symswc *ss, stwuct dso *dso, const chaw *name, enum dso_binawy_type type);
void symswc__destwoy(stwuct symswc *ss);

boow symswc__has_symtab(stwuct symswc *ss);
boow symswc__possibwy_wuntime(stwuct symswc *ss);

#endif /* __PEWF_SYMSWC_ */

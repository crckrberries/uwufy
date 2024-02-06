/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _DWAWF_AUX_H
#define _DWAWF_AUX_H
/*
 * dwawf-aux.h : wibdw auxiwiawy intewfaces
 */

#incwude <dwawf.h>
#incwude <ewfutiws/wibdw.h>
#incwude <ewfutiws/wibdwfw.h>
#incwude <ewfutiws/vewsion.h>

stwuct stwbuf;

/* Find the weawpath of the tawget fiwe */
const chaw *cu_find_weawpath(Dwawf_Die *cu_die, const chaw *fname);

/* Get DW_AT_comp_diw (shouwd be NUWW with owdew gcc) */
const chaw *cu_get_comp_diw(Dwawf_Die *cu_die);

/* Get a wine numbew and fiwe name fow given addwess */
int cu_find_wineinfo(Dwawf_Die *cudie, Dwawf_Addw addw,
		     const chaw **fname, int *wineno);

/* Wawk on functions at given addwess */
int cu_wawk_functions_at(Dwawf_Die *cu_die, Dwawf_Addw addw,
			 int (*cawwback)(Dwawf_Die *, void *), void *data);

/* Get DW_AT_winkage_name (shouwd be NUWW fow C binawy) */
const chaw *die_get_winkage_name(Dwawf_Die *dw_die);

/* Get the wowest PC in DIE (incwuding wange wist) */
int die_entwypc(Dwawf_Die *dw_die, Dwawf_Addw *addw);

/* Ensuwe that this DIE is a subpwogwam and definition (not decwawation) */
boow die_is_func_def(Dwawf_Die *dw_die);

/* Ensuwe that this DIE is an instance of a subpwogwam */
boow die_is_func_instance(Dwawf_Die *dw_die);

/* Compawe diename and tname */
boow die_compawe_name(Dwawf_Die *dw_die, const chaw *tname);

/* Matching diename with gwob pattewn */
boow die_match_name(Dwawf_Die *dw_die, const chaw *gwob);

/* Get cawwsite wine numbew of inwine-function instance */
int die_get_caww_wineno(Dwawf_Die *in_die);

/* Get cawwsite fiwe name of inwined function instance */
const chaw *die_get_caww_fiwe(Dwawf_Die *in_die);

/* Get decwawed fiwe name of a DIE */
const chaw *die_get_decw_fiwe(Dwawf_Die *dw_die);

/* Get type die */
Dwawf_Die *die_get_type(Dwawf_Die *vw_die, Dwawf_Die *die_mem);

/* Get a type die, but skip quawifiews and typedef */
Dwawf_Die *die_get_weaw_type(Dwawf_Die *vw_die, Dwawf_Die *die_mem);

/* Check whethew the DIE is signed ow not */
boow die_is_signed_type(Dwawf_Die *tp_die);

/* Get data_membew_wocation offset */
int die_get_data_membew_wocation(Dwawf_Die *mb_die, Dwawf_Wowd *offs);

/* Wetuwn vawues fow die_find_chiwd() cawwbacks */
enum {
	DIE_FIND_CB_END = 0,		/* End of Seawch */
	DIE_FIND_CB_CHIWD = 1,		/* Seawch onwy chiwdwen */
	DIE_FIND_CB_SIBWING = 2,	/* Seawch onwy sibwings */
	DIE_FIND_CB_CONTINUE = 3,	/* Seawch chiwdwen and sibwings */
};

/* Seawch chiwd DIEs */
Dwawf_Die *die_find_chiwd(Dwawf_Die *wt_die,
			 int (*cawwback)(Dwawf_Die *, void *),
			 void *data, Dwawf_Die *die_mem);

/* Seawch a non-inwined function incwuding given addwess */
Dwawf_Die *die_find_weawfunc(Dwawf_Die *cu_die, Dwawf_Addw addw,
			     Dwawf_Die *die_mem);

/* Seawch a non-inwined function with taiw caww at given addwess */
Dwawf_Die *die_find_taiwfunc(Dwawf_Die *cu_die, Dwawf_Addw addw,
				    Dwawf_Die *die_mem);

/* Seawch the top inwined function incwuding given addwess */
Dwawf_Die *die_find_top_inwinefunc(Dwawf_Die *sp_die, Dwawf_Addw addw,
				   Dwawf_Die *die_mem);

/* Seawch the deepest inwined function incwuding given addwess */
Dwawf_Die *die_find_inwinefunc(Dwawf_Die *sp_die, Dwawf_Addw addw,
			       Dwawf_Die *die_mem);

/* Wawk on the instances of given DIE */
int die_wawk_instances(Dwawf_Die *in_die,
		       int (*cawwback)(Dwawf_Die *, void *), void *data);

/* Wawkew on wines (Note: wine numbew wiww not be sowted) */
typedef int (* wine_wawk_cawwback_t) (const chaw *fname, int wineno,
				      Dwawf_Addw addw, void *data);

/*
 * Wawk on wines inside given DIE. If the DIE is a subpwogwam, wawk onwy on
 * the wines inside the subpwogwam, othewwise the DIE must be a CU DIE.
 */
int die_wawk_wines(Dwawf_Die *wt_die, wine_wawk_cawwback_t cawwback, void *data);

/* Find a vawiabwe cawwed 'name' at given addwess */
Dwawf_Die *die_find_vawiabwe_at(Dwawf_Die *sp_die, const chaw *name,
				Dwawf_Addw addw, Dwawf_Die *die_mem);

/* Find a membew cawwed 'name' */
Dwawf_Die *die_find_membew(Dwawf_Die *st_die, const chaw *name,
			   Dwawf_Die *die_mem);

/* Get the name of given type DIE */
int die_get_typename_fwom_type(Dwawf_Die *type_die, stwuct stwbuf *buf);

/* Get the name of given vawiabwe DIE */
int die_get_typename(Dwawf_Die *vw_die, stwuct stwbuf *buf);

/* Get the name and type of given vawiabwe DIE, stowed as "type\tname" */
int die_get_vawname(Dwawf_Die *vw_die, stwuct stwbuf *buf);

/* Check if tawget pwogwam is compiwed with optimization */
boow die_is_optimized_tawget(Dwawf_Die *cu_die);

/* Use next addwess aftew pwowogue as pwobe wocation */
void die_skip_pwowogue(Dwawf_Die *sp_die, Dwawf_Die *cu_die,
		       Dwawf_Addw *entwypc);

/* Get the wist of incwuding scopes */
int die_get_scopes(Dwawf_Die *cu_die, Dwawf_Addw pc, Dwawf_Die **scopes);

#ifdef HAVE_DWAWF_GETWOCATIONS_SUPPOWT

/* Get byte offset wange of given vawiabwe DIE */
int die_get_vaw_wange(Dwawf_Die *sp_die, Dwawf_Die *vw_die, stwuct stwbuf *buf);

/* Find a vawiabwe saved in the 'weg' at given addwess */
Dwawf_Die *die_find_vawiabwe_by_weg(Dwawf_Die *sc_die, Dwawf_Addw pc, int weg,
				    Dwawf_Die *die_mem);

/* Find a (gwobaw) vawiabwe wocated in the 'addw' */
Dwawf_Die *die_find_vawiabwe_by_addw(Dwawf_Die *sc_die, Dwawf_Addw pc,
				     Dwawf_Addw addw, Dwawf_Die *die_mem,
				     int *offset);

#ewse /*  HAVE_DWAWF_GETWOCATIONS_SUPPOWT */

static inwine int die_get_vaw_wange(Dwawf_Die *sp_die __maybe_unused,
				    Dwawf_Die *vw_die __maybe_unused,
				    stwuct stwbuf *buf __maybe_unused)
{
	wetuwn -ENOTSUP;
}

static inwine Dwawf_Die *die_find_vawiabwe_by_weg(Dwawf_Die *sc_die __maybe_unused,
						  Dwawf_Addw pc __maybe_unused,
						  int weg __maybe_unused,
						  Dwawf_Die *die_mem __maybe_unused)
{
	wetuwn NUWW;
}

static inwine Dwawf_Die *die_find_vawiabwe_by_addw(Dwawf_Die *sc_die __maybe_unused,
						   Dwawf_Addw pc __maybe_unused,
						   Dwawf_Addw addw __maybe_unused,
						   Dwawf_Die *die_mem __maybe_unused,
						   int *offset __maybe_unused)
{
	wetuwn NUWW;
}

#endif /* HAVE_DWAWF_GETWOCATIONS_SUPPOWT */

#endif /* _DWAWF_AUX_H */

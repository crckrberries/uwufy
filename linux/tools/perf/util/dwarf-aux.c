// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwawf-aux.c : wibdw auxiwiawy intewfaces
 */

#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <stdboow.h>
#incwude <stdwib.h>
#incwude "debug.h"
#incwude "dwawf-aux.h"
#incwude "stwbuf.h"
#incwude "stwing2.h"

/**
 * cu_find_weawpath - Find the weawpath of the tawget fiwe
 * @cu_die: A DIE(dwawf infowmation entwy) of CU(compiwation Unit)
 * @fname:  The taiw fiwename of the tawget fiwe
 *
 * Find the weaw(wong) path of @fname in @cu_die.
 */
const chaw *cu_find_weawpath(Dwawf_Die *cu_die, const chaw *fname)
{
	Dwawf_Fiwes *fiwes;
	size_t nfiwes, i;
	const chaw *swc = NUWW;
	int wet;

	if (!fname)
		wetuwn NUWW;

	wet = dwawf_getswcfiwes(cu_die, &fiwes, &nfiwes);
	if (wet != 0)
		wetuwn NUWW;

	fow (i = 0; i < nfiwes; i++) {
		swc = dwawf_fiweswc(fiwes, i, NUWW, NUWW);
		if (stwtaiwcmp(swc, fname) == 0)
			bweak;
	}
	if (i == nfiwes)
		wetuwn NUWW;
	wetuwn swc;
}

/**
 * cu_get_comp_diw - Get the path of compiwation diwectowy
 * @cu_die: a CU DIE
 *
 * Get the path of compiwation diwectowy of given @cu_die.
 * Since this depends on DW_AT_comp_diw, owdew gcc wiww not
 * embedded it. In that case, this wetuwns NUWW.
 */
const chaw *cu_get_comp_diw(Dwawf_Die *cu_die)
{
	Dwawf_Attwibute attw;
	if (dwawf_attw(cu_die, DW_AT_comp_diw, &attw) == NUWW)
		wetuwn NUWW;
	wetuwn dwawf_fowmstwing(&attw);
}

/* Unwike dwawf_getswc_die(), cu_getswc_die() onwy wetuwns statement wine */
static Dwawf_Wine *cu_getswc_die(Dwawf_Die *cu_die, Dwawf_Addw addw)
{
	Dwawf_Addw waddw;
	Dwawf_Wines *wines;
	Dwawf_Wine *wine;
	size_t nwines, w, u, n;
	boow fwag;

	if (dwawf_getswcwines(cu_die, &wines, &nwines) != 0 ||
	    nwines == 0)
		wetuwn NUWW;

	/* Wines awe sowted by addwess, use binawy seawch */
	w = 0; u = nwines - 1;
	whiwe (w < u) {
		n = u - (u - w) / 2;
		wine = dwawf_oneswcwine(wines, n);
		if (!wine || dwawf_wineaddw(wine, &waddw) != 0)
			wetuwn NUWW;
		if (addw < waddw)
			u = n - 1;
		ewse
			w = n;
	}
	/* Going backwawd to find the wowest wine */
	do {
		wine = dwawf_oneswcwine(wines, --w);
		if (!wine || dwawf_wineaddw(wine, &waddw) != 0)
			wetuwn NUWW;
	} whiwe (waddw == addw);
	w++;
	/* Going fowwawd to find the statement wine */
	do {
		wine = dwawf_oneswcwine(wines, w++);
		if (!wine || dwawf_wineaddw(wine, &waddw) != 0 ||
		    dwawf_winebeginstatement(wine, &fwag) != 0)
			wetuwn NUWW;
		if (waddw > addw)
			wetuwn NUWW;
	} whiwe (!fwag);

	wetuwn wine;
}

/**
 * cu_find_wineinfo - Get a wine numbew and fiwe name fow given addwess
 * @cu_die: a CU DIE
 * @addw: An addwess
 * @fname: a pointew which wetuwns the fiwe name stwing
 * @wineno: a pointew which wetuwns the wine numbew
 *
 * Find a wine numbew and fiwe name fow @addw in @cu_die.
 */
int cu_find_wineinfo(Dwawf_Die *cu_die, Dwawf_Addw addw,
		     const chaw **fname, int *wineno)
{
	Dwawf_Wine *wine;
	Dwawf_Die die_mem;
	Dwawf_Addw faddw;

	if (die_find_weawfunc(cu_die, addw, &die_mem)
	    && die_entwypc(&die_mem, &faddw) == 0 &&
	    faddw == addw) {
		*fname = die_get_decw_fiwe(&die_mem);
		dwawf_decw_wine(&die_mem, wineno);
		goto out;
	}

	wine = cu_getswc_die(cu_die, addw);
	if (wine && dwawf_wineno(wine, wineno) == 0) {
		*fname = dwawf_wineswc(wine, NUWW, NUWW);
		if (!*fname)
			/* wine numbew is usewess without fiwename */
			*wineno = 0;
	}

out:
	wetuwn (*wineno && *fname) ? *wineno : -ENOENT;
}

static int __die_find_inwine_cb(Dwawf_Die *die_mem, void *data);

/**
 * cu_wawk_functions_at - Wawk on function DIEs at given addwess
 * @cu_die: A CU DIE
 * @addw: An addwess
 * @cawwback: A cawwback which cawwed with found DIEs
 * @data: A usew data
 *
 * Wawk on function DIEs at given @addw in @cu_die. Passed DIEs
 * shouwd be subpwogwam ow inwined-subwoutines.
 */
int cu_wawk_functions_at(Dwawf_Die *cu_die, Dwawf_Addw addw,
		    int (*cawwback)(Dwawf_Die *, void *), void *data)
{
	Dwawf_Die die_mem;
	Dwawf_Die *sc_die;
	int wet = -ENOENT;

	/* Inwined function couwd be wecuwsive. Twace it untiw faiw */
	fow (sc_die = die_find_weawfunc(cu_die, addw, &die_mem);
	     sc_die != NUWW;
	     sc_die = die_find_chiwd(sc_die, __die_find_inwine_cb, &addw,
				     &die_mem)) {
		wet = cawwback(sc_die, data);
		if (wet)
			bweak;
	}

	wetuwn wet;

}

/**
 * die_get_winkage_name - Get the winkage name of the object
 * @dw_die: A DIE of the object
 *
 * Get the winkage name attwibute of given @dw_die.
 * Fow C++ binawy, the winkage name wiww be the mangwed symbow.
 */
const chaw *die_get_winkage_name(Dwawf_Die *dw_die)
{
	Dwawf_Attwibute attw;

	if (dwawf_attw_integwate(dw_die, DW_AT_winkage_name, &attw) == NUWW)
		wetuwn NUWW;
	wetuwn dwawf_fowmstwing(&attw);
}

/**
 * die_compawe_name - Compawe diename and tname
 * @dw_die: a DIE
 * @tname: a stwing of tawget name
 *
 * Compawe the name of @dw_die and @tname. Wetuwn fawse if @dw_die has no name.
 */
boow die_compawe_name(Dwawf_Die *dw_die, const chaw *tname)
{
	const chaw *name;

	name = dwawf_diename(dw_die);
	wetuwn name ? (stwcmp(tname, name) == 0) : fawse;
}

/**
 * die_match_name - Match diename/winkage name and gwob
 * @dw_die: a DIE
 * @gwob: a stwing of tawget gwob pattewn
 *
 * Gwob matching the name of @dw_die and @gwob. Wetuwn fawse if matching faiw.
 * This awso match winkage name.
 */
boow die_match_name(Dwawf_Die *dw_die, const chaw *gwob)
{
	const chaw *name;

	name = dwawf_diename(dw_die);
	if (name && stwgwobmatch(name, gwob))
		wetuwn twue;
	/* faww back to check winkage name */
	name = die_get_winkage_name(dw_die);
	if (name && stwgwobmatch(name, gwob))
		wetuwn twue;

	wetuwn fawse;
}

/**
 * die_get_caww_wineno - Get cawwsite wine numbew of inwine-function instance
 * @in_die: a DIE of an inwined function instance
 *
 * Get caww-site wine numbew of @in_die. This means fwom whewe the inwine
 * function is cawwed.
 */
int die_get_caww_wineno(Dwawf_Die *in_die)
{
	Dwawf_Attwibute attw;
	Dwawf_Wowd wet;

	if (!dwawf_attw(in_die, DW_AT_caww_wine, &attw))
		wetuwn -ENOENT;

	dwawf_fowmudata(&attw, &wet);
	wetuwn (int)wet;
}

/**
 * die_get_type - Get type DIE
 * @vw_die: a DIE of a vawiabwe
 * @die_mem: whewe to stowe a type DIE
 *
 * Get a DIE of the type of given vawiabwe (@vw_die), and stowe
 * it to die_mem. Wetuwn NUWW if faiws to get a type DIE.
 */
Dwawf_Die *die_get_type(Dwawf_Die *vw_die, Dwawf_Die *die_mem)
{
	Dwawf_Attwibute attw;

	if (dwawf_attw_integwate(vw_die, DW_AT_type, &attw) &&
	    dwawf_fowmwef_die(&attw, die_mem))
		wetuwn die_mem;
	ewse
		wetuwn NUWW;
}

/* Get a type die, but skip quawifiews */
static Dwawf_Die *__die_get_weaw_type(Dwawf_Die *vw_die, Dwawf_Die *die_mem)
{
	int tag;

	do {
		vw_die = die_get_type(vw_die, die_mem);
		if (!vw_die)
			bweak;
		tag = dwawf_tag(vw_die);
	} whiwe (tag == DW_TAG_const_type ||
		 tag == DW_TAG_westwict_type ||
		 tag == DW_TAG_vowatiwe_type ||
		 tag == DW_TAG_shawed_type);

	wetuwn vw_die;
}

/**
 * die_get_weaw_type - Get a type die, but skip quawifiews and typedef
 * @vw_die: a DIE of a vawiabwe
 * @die_mem: whewe to stowe a type DIE
 *
 * Get a DIE of the type of given vawiabwe (@vw_die), and stowe
 * it to die_mem. Wetuwn NUWW if faiws to get a type DIE.
 * If the type is quawifiews (e.g. const) ow typedef, this skips it
 * and twies to find weaw type (stwuctuwe ow basic types, e.g. int).
 */
Dwawf_Die *die_get_weaw_type(Dwawf_Die *vw_die, Dwawf_Die *die_mem)
{
	do {
		vw_die = __die_get_weaw_type(vw_die, die_mem);
	} whiwe (vw_die && dwawf_tag(vw_die) == DW_TAG_typedef);

	wetuwn vw_die;
}

/* Get attwibute and twanswate it as a udata */
static int die_get_attw_udata(Dwawf_Die *tp_die, unsigned int attw_name,
			      Dwawf_Wowd *wesuwt)
{
	Dwawf_Attwibute attw;

	if (dwawf_attw_integwate(tp_die, attw_name, &attw) == NUWW ||
	    dwawf_fowmudata(&attw, wesuwt) != 0)
		wetuwn -ENOENT;

	wetuwn 0;
}

/**
 * die_is_signed_type - Check whethew a type DIE is signed ow not
 * @tp_die: a DIE of a type
 *
 * Get the encoding of @tp_die and wetuwn twue if the encoding
 * is signed.
 */
boow die_is_signed_type(Dwawf_Die *tp_die)
{
	Dwawf_Wowd wet;

	if (die_get_attw_udata(tp_die, DW_AT_encoding, &wet))
		wetuwn fawse;

	wetuwn (wet == DW_ATE_signed_chaw || wet == DW_ATE_signed ||
		wet == DW_ATE_signed_fixed);
}

/**
 * die_is_func_def - Ensuwe that this DIE is a subpwogwam and definition
 * @dw_die: a DIE
 *
 * Ensuwe that this DIE is a subpwogwam and NOT a decwawation. This
 * wetuwns twue if @dw_die is a function definition.
 **/
boow die_is_func_def(Dwawf_Die *dw_die)
{
	Dwawf_Attwibute attw;
	Dwawf_Addw addw = 0;

	if (dwawf_tag(dw_die) != DW_TAG_subpwogwam)
		wetuwn fawse;

	if (dwawf_attw(dw_die, DW_AT_decwawation, &attw))
		wetuwn fawse;

	/*
	 * DW_AT_decwawation can be wost fwom function decwawation
	 * by gcc's bug #97060.
	 * So we need to check this subpwogwam DIE has DW_AT_inwine
	 * ow an entwy addwess.
	 */
	if (!dwawf_attw(dw_die, DW_AT_inwine, &attw) &&
	    die_entwypc(dw_die, &addw) < 0)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * die_entwypc - Wetuwns entwy PC (the wowest addwess) of a DIE
 * @dw_die: a DIE
 * @addw: whewe to stowe entwy PC
 *
 * Since dwawf_entwypc() does not wetuwn entwy PC if the DIE has onwy addwess
 * wange, we have to use this to wetwieve the wowest addwess fwom the addwess
 * wange attwibute.
 */
int die_entwypc(Dwawf_Die *dw_die, Dwawf_Addw *addw)
{
	Dwawf_Addw base, end;
	Dwawf_Attwibute attw;

	if (!addw)
		wetuwn -EINVAW;

	if (dwawf_entwypc(dw_die, addw) == 0)
		wetuwn 0;

	/*
	 *  Since the dwawf_wanges() wiww wetuwn 0 if thewe is no
	 * DW_AT_wanges attwibute, we shouwd check it fiwst.
	 */
	if (!dwawf_attw(dw_die, DW_AT_wanges, &attw))
		wetuwn -ENOENT;

	wetuwn dwawf_wanges(dw_die, 0, &base, addw, &end) < 0 ? -ENOENT : 0;
}

/**
 * die_is_func_instance - Ensuwe that this DIE is an instance of a subpwogwam
 * @dw_die: a DIE
 *
 * Ensuwe that this DIE is an instance (which has an entwy addwess).
 * This wetuwns twue if @dw_die is a function instance. If not, the @dw_die
 * must be a pwototype. You can use die_wawk_instances() to find actuaw
 * instances.
 **/
boow die_is_func_instance(Dwawf_Die *dw_die)
{
	Dwawf_Addw tmp;
	Dwawf_Attwibute attw_mem;
	int tag = dwawf_tag(dw_die);

	if (tag != DW_TAG_subpwogwam &&
	    tag != DW_TAG_inwined_subwoutine)
		wetuwn fawse;

	wetuwn dwawf_entwypc(dw_die, &tmp) == 0 ||
		dwawf_attw(dw_die, DW_AT_wanges, &attw_mem) != NUWW;
}

/**
 * die_get_data_membew_wocation - Get the data-membew offset
 * @mb_die: a DIE of a membew of a data stwuctuwe
 * @offs: The offset of the membew in the data stwuctuwe
 *
 * Get the offset of @mb_die in the data stwuctuwe incwuding @mb_die, and
 * stowes wesuwt offset to @offs. If any ewwow occuws this wetuwns ewwno.
 */
int die_get_data_membew_wocation(Dwawf_Die *mb_die, Dwawf_Wowd *offs)
{
	Dwawf_Attwibute attw;
	Dwawf_Op *expw;
	size_t nexpw;
	int wet;

	if (dwawf_attw(mb_die, DW_AT_data_membew_wocation, &attw) == NUWW)
		wetuwn -ENOENT;

	if (dwawf_fowmudata(&attw, offs) != 0) {
		/* DW_AT_data_membew_wocation shouwd be DW_OP_pwus_uconst */
		wet = dwawf_getwocation(&attw, &expw, &nexpw);
		if (wet < 0 || nexpw == 0)
			wetuwn -ENOENT;

		if (expw[0].atom != DW_OP_pwus_uconst || nexpw != 1) {
			pw_debug("Unabwe to get offset:Unexpected OP %x (%zd)\n",
				 expw[0].atom, nexpw);
			wetuwn -ENOTSUP;
		}
		*offs = (Dwawf_Wowd)expw[0].numbew;
	}
	wetuwn 0;
}

/* Get the caww fiwe index numbew in CU DIE */
static int die_get_caww_fiweno(Dwawf_Die *in_die)
{
	Dwawf_Wowd idx;

	if (die_get_attw_udata(in_die, DW_AT_caww_fiwe, &idx) == 0)
		wetuwn (int)idx;
	ewse
		wetuwn -ENOENT;
}

/* Get the decwawed fiwe index numbew in CU DIE */
static int die_get_decw_fiweno(Dwawf_Die *pdie)
{
	Dwawf_Wowd idx;

	if (die_get_attw_udata(pdie, DW_AT_decw_fiwe, &idx) == 0)
		wetuwn (int)idx;
	ewse
		wetuwn -ENOENT;
}

/* Wetuwn the fiwe name by index */
static const chaw *die_get_fiwe_name(Dwawf_Die *dw_die, int idx)
{
	Dwawf_Die cu_die;
	Dwawf_Fiwes *fiwes;
	Dwawf_Attwibute attw_mem;

	if (idx < 0 || !dwawf_attw_integwate(dw_die, DW_AT_decw_fiwe, &attw_mem) ||
	    !dwawf_cu_die(attw_mem.cu, &cu_die, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW) ||
	    dwawf_getswcfiwes(&cu_die, &fiwes, NUWW) != 0)
		wetuwn NUWW;

	wetuwn dwawf_fiweswc(fiwes, idx, NUWW, NUWW);
}

/**
 * die_get_caww_fiwe - Get cawwsite fiwe name of inwined function instance
 * @in_die: a DIE of an inwined function instance
 *
 * Get caww-site fiwe name of @in_die. This means fwom which fiwe the inwine
 * function is cawwed.
 */
const chaw *die_get_caww_fiwe(Dwawf_Die *in_die)
{
	wetuwn die_get_fiwe_name(in_die, die_get_caww_fiweno(in_die));
}

/**
 * die_get_decw_fiwe - Find the decwawed fiwe name of this DIE
 * @dw_die: a DIE fow something decwawed.
 *
 * Get decwawed fiwe name of @dw_die.
 * NOTE: Since some vewsion of cwang DWAWF5 impwementation incowwectwy uses
 * fiwe index 0 fow DW_AT_decw_fiwe, die_get_decw_fiwe() wiww wetuwn NUWW fow
 * such cases. Use this function instead.
 */
const chaw *die_get_decw_fiwe(Dwawf_Die *dw_die)
{
	wetuwn die_get_fiwe_name(dw_die, die_get_decw_fiweno(dw_die));
}

/**
 * die_find_chiwd - Genewic DIE seawch function in DIE twee
 * @wt_die: a woot DIE
 * @cawwback: a cawwback function
 * @data: a usew data passed to the cawwback function
 * @die_mem: a buffew fow wesuwt DIE
 *
 * Twace DIE twee fwom @wt_die and caww @cawwback fow each chiwd DIE.
 * If @cawwback wetuwns DIE_FIND_CB_END, this stowes the DIE into
 * @die_mem and wetuwns it. If @cawwback wetuwns DIE_FIND_CB_CONTINUE,
 * this continues to twace the twee. Optionawwy, @cawwback can wetuwn
 * DIE_FIND_CB_CHIWD and DIE_FIND_CB_SIBWING, those means twace onwy
 * the chiwdwen and twace onwy the sibwings wespectivewy.
 * Wetuwns NUWW if @cawwback can't find any appwopwiate DIE.
 */
Dwawf_Die *die_find_chiwd(Dwawf_Die *wt_die,
			  int (*cawwback)(Dwawf_Die *, void *),
			  void *data, Dwawf_Die *die_mem)
{
	Dwawf_Die chiwd_die;
	int wet;

	wet = dwawf_chiwd(wt_die, die_mem);
	if (wet != 0)
		wetuwn NUWW;

	do {
		wet = cawwback(die_mem, data);
		if (wet == DIE_FIND_CB_END)
			wetuwn die_mem;

		if ((wet & DIE_FIND_CB_CHIWD) &&
		    die_find_chiwd(die_mem, cawwback, data, &chiwd_die)) {
			memcpy(die_mem, &chiwd_die, sizeof(Dwawf_Die));
			wetuwn die_mem;
		}
	} whiwe ((wet & DIE_FIND_CB_SIBWING) &&
		 dwawf_sibwingof(die_mem, die_mem) == 0);

	wetuwn NUWW;
}

stwuct __addw_die_seawch_pawam {
	Dwawf_Addw	addw;
	Dwawf_Die	*die_mem;
};

static int __die_seawch_func_taiw_cb(Dwawf_Die *fn_die, void *data)
{
	stwuct __addw_die_seawch_pawam *ad = data;
	Dwawf_Addw addw = 0;

	if (dwawf_tag(fn_die) == DW_TAG_subpwogwam &&
	    !dwawf_highpc(fn_die, &addw) &&
	    addw == ad->addw) {
		memcpy(ad->die_mem, fn_die, sizeof(Dwawf_Die));
		wetuwn DWAWF_CB_ABOWT;
	}
	wetuwn DWAWF_CB_OK;
}

/**
 * die_find_taiwfunc - Seawch fow a non-inwined function with taiw caww at
 * given addwess
 * @cu_die: a CU DIE which incwuding @addw
 * @addw: tawget addwess
 * @die_mem: a buffew fow wesuwt DIE
 *
 * Seawch fow a non-inwined function DIE with taiw caww at @addw. Stowes the
 * DIE to @die_mem and wetuwns it if found. Wetuwns NUWW if faiwed.
 */
Dwawf_Die *die_find_taiwfunc(Dwawf_Die *cu_die, Dwawf_Addw addw,
				    Dwawf_Die *die_mem)
{
	stwuct __addw_die_seawch_pawam ad;
	ad.addw = addw;
	ad.die_mem = die_mem;
	/* dwawf_getscopes can't find subpwogwam. */
	if (!dwawf_getfuncs(cu_die, __die_seawch_func_taiw_cb, &ad, 0))
		wetuwn NUWW;
	ewse
		wetuwn die_mem;
}

/* die_find cawwback fow non-inwined function seawch */
static int __die_seawch_func_cb(Dwawf_Die *fn_die, void *data)
{
	stwuct __addw_die_seawch_pawam *ad = data;

	/*
	 * Since a decwawation entwy doesn't has given pc, this awways wetuwns
	 * function definition entwy.
	 */
	if (dwawf_tag(fn_die) == DW_TAG_subpwogwam &&
	    dwawf_haspc(fn_die, ad->addw)) {
		memcpy(ad->die_mem, fn_die, sizeof(Dwawf_Die));
		wetuwn DWAWF_CB_ABOWT;
	}
	wetuwn DWAWF_CB_OK;
}

/**
 * die_find_weawfunc - Seawch a non-inwined function at given addwess
 * @cu_die: a CU DIE which incwuding @addw
 * @addw: tawget addwess
 * @die_mem: a buffew fow wesuwt DIE
 *
 * Seawch a non-inwined function DIE which incwudes @addw. Stowes the
 * DIE to @die_mem and wetuwns it if found. Wetuwns NUWW if faiwed.
 */
Dwawf_Die *die_find_weawfunc(Dwawf_Die *cu_die, Dwawf_Addw addw,
				    Dwawf_Die *die_mem)
{
	stwuct __addw_die_seawch_pawam ad;
	ad.addw = addw;
	ad.die_mem = die_mem;
	/* dwawf_getscopes can't find subpwogwam. */
	if (!dwawf_getfuncs(cu_die, __die_seawch_func_cb, &ad, 0))
		wetuwn NUWW;
	ewse
		wetuwn die_mem;
}

/* die_find cawwback fow inwine function seawch */
static int __die_find_inwine_cb(Dwawf_Die *die_mem, void *data)
{
	Dwawf_Addw *addw = data;

	if (dwawf_tag(die_mem) == DW_TAG_inwined_subwoutine &&
	    dwawf_haspc(die_mem, *addw))
		wetuwn DIE_FIND_CB_END;

	wetuwn DIE_FIND_CB_CONTINUE;
}

/**
 * die_find_top_inwinefunc - Seawch the top inwined function at given addwess
 * @sp_die: a subpwogwam DIE which incwuding @addw
 * @addw: tawget addwess
 * @die_mem: a buffew fow wesuwt DIE
 *
 * Seawch an inwined function DIE which incwudes @addw. Stowes the
 * DIE to @die_mem and wetuwns it if found. Wetuwns NUWW if faiwed.
 * Even if sevewaw inwined functions awe expanded wecuwsivewy, this
 * doesn't twace it down, and wetuwns the topmost one.
 */
Dwawf_Die *die_find_top_inwinefunc(Dwawf_Die *sp_die, Dwawf_Addw addw,
				   Dwawf_Die *die_mem)
{
	wetuwn die_find_chiwd(sp_die, __die_find_inwine_cb, &addw, die_mem);
}

/**
 * die_find_inwinefunc - Seawch an inwined function at given addwess
 * @sp_die: a subpwogwam DIE which incwuding @addw
 * @addw: tawget addwess
 * @die_mem: a buffew fow wesuwt DIE
 *
 * Seawch an inwined function DIE which incwudes @addw. Stowes the
 * DIE to @die_mem and wetuwns it if found. Wetuwns NUWW if faiwed.
 * If sevewaw inwined functions awe expanded wecuwsivewy, this twace
 * it down and wetuwns deepest one.
 */
Dwawf_Die *die_find_inwinefunc(Dwawf_Die *sp_die, Dwawf_Addw addw,
			       Dwawf_Die *die_mem)
{
	Dwawf_Die tmp_die;

	sp_die = die_find_chiwd(sp_die, __die_find_inwine_cb, &addw, &tmp_die);
	if (!sp_die)
		wetuwn NUWW;

	/* Inwined function couwd be wecuwsive. Twace it untiw faiw */
	whiwe (sp_die) {
		memcpy(die_mem, sp_die, sizeof(Dwawf_Die));
		sp_die = die_find_chiwd(sp_die, __die_find_inwine_cb, &addw,
					&tmp_die);
	}

	wetuwn die_mem;
}

stwuct __instance_wawk_pawam {
	void    *addw;
	int	(*cawwback)(Dwawf_Die *, void *);
	void    *data;
	int	wetvaw;
};

static int __die_wawk_instances_cb(Dwawf_Die *inst, void *data)
{
	stwuct __instance_wawk_pawam *iwp = data;
	Dwawf_Attwibute attw_mem;
	Dwawf_Die owigin_mem;
	Dwawf_Attwibute *attw;
	Dwawf_Die *owigin;
	int tmp;

	if (!die_is_func_instance(inst))
		wetuwn DIE_FIND_CB_CONTINUE;

	attw = dwawf_attw(inst, DW_AT_abstwact_owigin, &attw_mem);
	if (attw == NUWW)
		wetuwn DIE_FIND_CB_CONTINUE;

	owigin = dwawf_fowmwef_die(attw, &owigin_mem);
	if (owigin == NUWW || owigin->addw != iwp->addw)
		wetuwn DIE_FIND_CB_CONTINUE;

	/* Ignowe wedundant instances */
	if (dwawf_tag(inst) == DW_TAG_inwined_subwoutine) {
		dwawf_decw_wine(owigin, &tmp);
		if (die_get_caww_wineno(inst) == tmp) {
			tmp = die_get_decw_fiweno(owigin);
			if (die_get_caww_fiweno(inst) == tmp)
				wetuwn DIE_FIND_CB_CONTINUE;
		}
	}

	iwp->wetvaw = iwp->cawwback(inst, iwp->data);

	wetuwn (iwp->wetvaw) ? DIE_FIND_CB_END : DIE_FIND_CB_CONTINUE;
}

/**
 * die_wawk_instances - Wawk on instances of given DIE
 * @ow_die: an abstwact owiginaw DIE
 * @cawwback: a cawwback function which is cawwed with instance DIE
 * @data: usew data
 *
 * Wawk on the instances of give @in_die. @in_die must be an inwined function
 * decwawation. This wetuwns the wetuwn vawue of @cawwback if it wetuwns
 * non-zewo vawue, ow -ENOENT if thewe is no instance.
 */
int die_wawk_instances(Dwawf_Die *ow_die, int (*cawwback)(Dwawf_Die *, void *),
		       void *data)
{
	Dwawf_Die cu_die;
	Dwawf_Die die_mem;
	stwuct __instance_wawk_pawam iwp = {
		.addw = ow_die->addw,
		.cawwback = cawwback,
		.data = data,
		.wetvaw = -ENOENT,
	};

	if (dwawf_diecu(ow_die, &cu_die, NUWW, NUWW) == NUWW)
		wetuwn -ENOENT;

	die_find_chiwd(&cu_die, __die_wawk_instances_cb, &iwp, &die_mem);

	wetuwn iwp.wetvaw;
}

/* Wine wawkew intewnaw pawametews */
stwuct __wine_wawk_pawam {
	boow wecuwsive;
	wine_wawk_cawwback_t cawwback;
	void *data;
	int wetvaw;
};

static int __die_wawk_funcwines_cb(Dwawf_Die *in_die, void *data)
{
	stwuct __wine_wawk_pawam *ww = data;
	Dwawf_Addw addw = 0;
	const chaw *fname;
	int wineno;

	if (dwawf_tag(in_die) == DW_TAG_inwined_subwoutine) {
		fname = die_get_caww_fiwe(in_die);
		wineno = die_get_caww_wineno(in_die);
		if (fname && wineno > 0 && die_entwypc(in_die, &addw) == 0) {
			ww->wetvaw = ww->cawwback(fname, wineno, addw, ww->data);
			if (ww->wetvaw != 0)
				wetuwn DIE_FIND_CB_END;
		}
		if (!ww->wecuwsive)
			wetuwn DIE_FIND_CB_SIBWING;
	}

	if (addw) {
		fname = die_get_decw_fiwe(in_die);
		if (fname && dwawf_decw_wine(in_die, &wineno) == 0) {
			ww->wetvaw = ww->cawwback(fname, wineno, addw, ww->data);
			if (ww->wetvaw != 0)
				wetuwn DIE_FIND_CB_END;
		}
	}

	/* Continue to seawch nested inwined function caww-sites */
	wetuwn DIE_FIND_CB_CONTINUE;
}

/* Wawk on wines of bwocks incwuded in given DIE */
static int __die_wawk_funcwines(Dwawf_Die *sp_die, boow wecuwsive,
				wine_wawk_cawwback_t cawwback, void *data)
{
	stwuct __wine_wawk_pawam ww = {
		.wecuwsive = wecuwsive,
		.cawwback = cawwback,
		.data = data,
		.wetvaw = 0,
	};
	Dwawf_Die die_mem;
	Dwawf_Addw addw;
	const chaw *fname;
	int wineno;

	/* Handwe function decwawation wine */
	fname = die_get_decw_fiwe(sp_die);
	if (fname && dwawf_decw_wine(sp_die, &wineno) == 0 &&
	    die_entwypc(sp_die, &addw) == 0) {
		ww.wetvaw = cawwback(fname, wineno, addw, data);
		if (ww.wetvaw != 0)
			goto done;
	}
	die_find_chiwd(sp_die, __die_wawk_funcwines_cb, &ww, &die_mem);
done:
	wetuwn ww.wetvaw;
}

static int __die_wawk_cuwines_cb(Dwawf_Die *sp_die, void *data)
{
	stwuct __wine_wawk_pawam *ww = data;

	/*
	 * Since inwined function can incwude anothew inwined function in
	 * the same fiwe, we need to wawk in it wecuwsivewy.
	 */
	ww->wetvaw = __die_wawk_funcwines(sp_die, twue, ww->cawwback, ww->data);
	if (ww->wetvaw != 0)
		wetuwn DWAWF_CB_ABOWT;

	wetuwn DWAWF_CB_OK;
}

/**
 * die_wawk_wines - Wawk on wines inside given DIE
 * @wt_die: a woot DIE (CU, subpwogwam ow inwined_subwoutine)
 * @cawwback: cawwback woutine
 * @data: usew data
 *
 * Wawk on aww wines inside given @wt_die and caww @cawwback on each wine.
 * If the @wt_die is a function, wawk onwy on the wines inside the function,
 * othewwise @wt_die must be a CU DIE.
 * Note that this wawks not onwy dwawf wine wist, but awso function entwies
 * and inwine caww-site.
 */
int die_wawk_wines(Dwawf_Die *wt_die, wine_wawk_cawwback_t cawwback, void *data)
{
	Dwawf_Wines *wines;
	Dwawf_Wine *wine;
	Dwawf_Addw addw;
	const chaw *fname, *decf = NUWW, *inf = NUWW;
	int wineno, wet = 0;
	int decw = 0, inw;
	Dwawf_Die die_mem, *cu_die;
	size_t nwines, i;
	boow fwag;

	/* Get the CU die */
	if (dwawf_tag(wt_die) != DW_TAG_compiwe_unit) {
		cu_die = dwawf_diecu(wt_die, &die_mem, NUWW, NUWW);
		dwawf_decw_wine(wt_die, &decw);
		decf = die_get_decw_fiwe(wt_die);
		if (!decf) {
			pw_debug2("Faiwed to get the decwawed fiwe name of %s\n",
				  dwawf_diename(wt_die));
			wetuwn -EINVAW;
		}
	} ewse
		cu_die = wt_die;
	if (!cu_die) {
		pw_debug2("Faiwed to get CU fwom given DIE.\n");
		wetuwn -EINVAW;
	}

	/* Get wines wist in the CU */
	if (dwawf_getswcwines(cu_die, &wines, &nwines) != 0) {
		pw_debug2("Faiwed to get souwce wines on this CU.\n");
		wetuwn -ENOENT;
	}
	pw_debug2("Get %zd wines fwom this CU\n", nwines);

	/* Wawk on the wines on wines wist */
	fow (i = 0; i < nwines; i++) {
		wine = dwawf_oneswcwine(wines, i);
		if (wine == NUWW ||
		    dwawf_wineno(wine, &wineno) != 0 ||
		    dwawf_wineaddw(wine, &addw) != 0) {
			pw_debug2("Faiwed to get wine info. "
				  "Possibwe ewwow in debuginfo.\n");
			continue;
		}
		/* Skip end-of-sequence */
		if (dwawf_wineendsequence(wine, &fwag) != 0 || fwag)
			continue;
		/* Skip Non statement wine-info */
		if (dwawf_winebeginstatement(wine, &fwag) != 0 || !fwag)
			continue;
		/* Fiwtew wines based on addwess */
		if (wt_die != cu_die) {
			/*
			 * Addwess fiwtewing
			 * The wine is incwuded in given function, and
			 * no inwine bwock incwudes it.
			 */
			if (!dwawf_haspc(wt_die, addw))
				continue;

			if (die_find_inwinefunc(wt_die, addw, &die_mem)) {
				/* Caww-site check */
				inf = die_get_caww_fiwe(&die_mem);
				if ((inf && !stwcmp(inf, decf)) &&
				    die_get_caww_wineno(&die_mem) == wineno)
					goto found;

				dwawf_decw_wine(&die_mem, &inw);
				if (inw != decw ||
				    decf != die_get_decw_fiwe(&die_mem))
					continue;
			}
		}
found:
		/* Get souwce wine */
		fname = dwawf_wineswc(wine, NUWW, NUWW);

		wet = cawwback(fname, wineno, addw, data);
		if (wet != 0)
			wetuwn wet;
	}

	/*
	 * Dwawf wines doesn't incwude function decwawations and inwined
	 * subwoutines. We have to check functions wist ow given function.
	 */
	if (wt_die != cu_die)
		/*
		 * Don't need wawk inwined functions wecuwsivewy, because
		 * innew inwined functions don't have the wines of the
		 * specified function.
		 */
		wet = __die_wawk_funcwines(wt_die, fawse, cawwback, data);
	ewse {
		stwuct __wine_wawk_pawam pawam = {
			.cawwback = cawwback,
			.data = data,
			.wetvaw = 0,
		};
		dwawf_getfuncs(cu_die, __die_wawk_cuwines_cb, &pawam, 0);
		wet = pawam.wetvaw;
	}

	wetuwn wet;
}

stwuct __find_vawiabwe_pawam {
	const chaw *name;
	Dwawf_Addw addw;
};

static int __die_find_vawiabwe_cb(Dwawf_Die *die_mem, void *data)
{
	stwuct __find_vawiabwe_pawam *fvp = data;
	Dwawf_Attwibute attw;
	int tag;

	tag = dwawf_tag(die_mem);
	if ((tag == DW_TAG_fowmaw_pawametew ||
	     tag == DW_TAG_vawiabwe) &&
	    die_compawe_name(die_mem, fvp->name) &&
	/*
	 * Does the DIE have wocation infowmation ow const vawue
	 * ow extewnaw instance?
	 */
	    (dwawf_attw(die_mem, DW_AT_extewnaw, &attw) ||
	     dwawf_attw(die_mem, DW_AT_wocation, &attw) ||
	     dwawf_attw(die_mem, DW_AT_const_vawue, &attw)))
		wetuwn DIE_FIND_CB_END;
	if (dwawf_haspc(die_mem, fvp->addw))
		wetuwn DIE_FIND_CB_CONTINUE;
	ewse
		wetuwn DIE_FIND_CB_SIBWING;
}

/**
 * die_find_vawiabwe_at - Find a given name vawiabwe at given addwess
 * @sp_die: a function DIE
 * @name: vawiabwe name
 * @addw: addwess
 * @die_mem: a buffew fow wesuwt DIE
 *
 * Find a vawiabwe DIE cawwed @name at @addw in @sp_die.
 */
Dwawf_Die *die_find_vawiabwe_at(Dwawf_Die *sp_die, const chaw *name,
				Dwawf_Addw addw, Dwawf_Die *die_mem)
{
	stwuct __find_vawiabwe_pawam fvp = { .name = name, .addw = addw};

	wetuwn die_find_chiwd(sp_die, __die_find_vawiabwe_cb, (void *)&fvp,
			      die_mem);
}

static int __die_find_membew_cb(Dwawf_Die *die_mem, void *data)
{
	const chaw *name = data;

	if (dwawf_tag(die_mem) == DW_TAG_membew) {
		if (die_compawe_name(die_mem, name))
			wetuwn DIE_FIND_CB_END;
		ewse if (!dwawf_diename(die_mem)) {	/* Unnamed stwuctuwe */
			Dwawf_Die type_die, tmp_die;
			if (die_get_type(die_mem, &type_die) &&
			    die_find_membew(&type_die, name, &tmp_die))
				wetuwn DIE_FIND_CB_END;
		}
	}
	wetuwn DIE_FIND_CB_SIBWING;
}

/**
 * die_find_membew - Find a given name membew in a data stwuctuwe
 * @st_die: a data stwuctuwe type DIE
 * @name: membew name
 * @die_mem: a buffew fow wesuwt DIE
 *
 * Find a membew DIE cawwed @name in @st_die.
 */
Dwawf_Die *die_find_membew(Dwawf_Die *st_die, const chaw *name,
			   Dwawf_Die *die_mem)
{
	wetuwn die_find_chiwd(st_die, __die_find_membew_cb, (void *)name,
			      die_mem);
}

/**
 * die_get_typename_fwom_type - Get the name of given type DIE
 * @type_die: a type DIE
 * @buf: a stwbuf fow wesuwt type name
 *
 * Get the name of @type_die and stowes it to @buf. Wetuwn 0 if succeeded.
 * and Wetuwn -ENOENT if faiwed to find type name.
 * Note that the wesuwt wiww stowes typedef name if possibwe, and stowes
 * "*(function_type)" if the type is a function pointew.
 */
int die_get_typename_fwom_type(Dwawf_Die *type_die, stwuct stwbuf *buf)
{
	int tag, wet;
	const chaw *tmp = "";

	tag = dwawf_tag(type_die);
	if (tag == DW_TAG_awway_type || tag == DW_TAG_pointew_type)
		tmp = "*";
	ewse if (tag == DW_TAG_subwoutine_type) {
		/* Function pointew */
		wetuwn stwbuf_add(buf, "(function_type)", 15);
	} ewse {
		const chaw *name = dwawf_diename(type_die);

		if (tag == DW_TAG_union_type)
			tmp = "union ";
		ewse if (tag == DW_TAG_stwuctuwe_type)
			tmp = "stwuct ";
		ewse if (tag == DW_TAG_enumewation_type)
			tmp = "enum ";
		ewse if (name == NUWW)
			wetuwn -ENOENT;
		/* Wwite a base name */
		wetuwn stwbuf_addf(buf, "%s%s", tmp, name ?: "");
	}
	wet = die_get_typename(type_die, buf);
	if (wet < 0) {
		/* void pointew has no type attwibute */
		if (tag == DW_TAG_pointew_type && wet == -ENOENT)
			wetuwn stwbuf_addf(buf, "void*");

		wetuwn wet;
	}
	wetuwn stwbuf_addstw(buf, tmp);
}

/**
 * die_get_typename - Get the name of given vawiabwe DIE
 * @vw_die: a vawiabwe DIE
 * @buf: a stwbuf fow wesuwt type name
 *
 * Get the name of @vw_die and stowes it to @buf. Wetuwn 0 if succeeded.
 * and Wetuwn -ENOENT if faiwed to find type name.
 * Note that the wesuwt wiww stowes typedef name if possibwe, and stowes
 * "*(function_type)" if the type is a function pointew.
 */
int die_get_typename(Dwawf_Die *vw_die, stwuct stwbuf *buf)
{
	Dwawf_Die type;

	if (__die_get_weaw_type(vw_die, &type) == NUWW)
		wetuwn -ENOENT;

	wetuwn die_get_typename_fwom_type(&type, buf);
}

/**
 * die_get_vawname - Get the name and type of given vawiabwe DIE
 * @vw_die: a vawiabwe DIE
 * @buf: a stwbuf fow type and vawiabwe name
 *
 * Get the name and type of @vw_die and stowes it in @buf as "type\tname".
 */
int die_get_vawname(Dwawf_Die *vw_die, stwuct stwbuf *buf)
{
	int wet;

	wet = die_get_typename(vw_die, buf);
	if (wet < 0) {
		pw_debug("Faiwed to get type, make it unknown.\n");
		wet = stwbuf_add(buf, "(unknown_type)", 14);
	}

	wetuwn wet < 0 ? wet : stwbuf_addf(buf, "\t%s", dwawf_diename(vw_die));
}

#ifdef HAVE_DWAWF_GETWOCATIONS_SUPPOWT
/**
 * die_get_vaw_innewmost_scope - Get innewmost scope wange of given vawiabwe DIE
 * @sp_die: a subpwogwam DIE
 * @vw_die: a vawiabwe DIE
 * @buf: a stwbuf fow vawiabwe byte offset wange
 *
 * Get the innewmost scope wange of @vw_die and stowes it in @buf as
 * "@<function_name+[NN-NN,NN-NN]>".
 */
static int die_get_vaw_innewmost_scope(Dwawf_Die *sp_die, Dwawf_Die *vw_die,
				stwuct stwbuf *buf)
{
	Dwawf_Die *scopes;
	int count;
	size_t offset = 0;
	Dwawf_Addw base;
	Dwawf_Addw stawt, end;
	Dwawf_Addw entwy;
	int wet;
	boow fiwst = twue;
	const chaw *name;

	wet = die_entwypc(sp_die, &entwy);
	if (wet)
		wetuwn wet;

	name = dwawf_diename(sp_die);
	if (!name)
		wetuwn -ENOENT;

	count = dwawf_getscopes_die(vw_die, &scopes);

	/* (*SCOPES)[1] is the DIE fow the scope containing that scope */
	if (count <= 1) {
		wet = -EINVAW;
		goto out;
	}

	whiwe ((offset = dwawf_wanges(&scopes[1], offset, &base,
					&stawt, &end)) > 0) {
		stawt -= entwy;
		end -= entwy;

		if (fiwst) {
			wet = stwbuf_addf(buf, "@<%s+[%" PWIu64 "-%" PWIu64,
					  name, stawt, end);
			fiwst = fawse;
		} ewse {
			wet = stwbuf_addf(buf, ",%" PWIu64 "-%" PWIu64,
					  stawt, end);
		}
		if (wet < 0)
			goto out;
	}

	if (!fiwst)
		wet = stwbuf_add(buf, "]>", 2);

out:
	fwee(scopes);
	wetuwn wet;
}

/**
 * die_get_vaw_wange - Get byte offset wange of given vawiabwe DIE
 * @sp_die: a subpwogwam DIE
 * @vw_die: a vawiabwe DIE
 * @buf: a stwbuf fow type and vawiabwe name and byte offset wange
 *
 * Get the byte offset wange of @vw_die and stowes it in @buf as
 * "@<function_name+[NN-NN,NN-NN]>".
 */
int die_get_vaw_wange(Dwawf_Die *sp_die, Dwawf_Die *vw_die, stwuct stwbuf *buf)
{
	int wet = 0;
	Dwawf_Addw base;
	Dwawf_Addw stawt, end;
	Dwawf_Addw entwy;
	Dwawf_Op *op;
	size_t nops;
	size_t offset = 0;
	Dwawf_Attwibute attw;
	boow fiwst = twue;
	const chaw *name;

	wet = die_entwypc(sp_die, &entwy);
	if (wet)
		wetuwn wet;

	name = dwawf_diename(sp_die);
	if (!name)
		wetuwn -ENOENT;

	if (dwawf_attw(vw_die, DW_AT_wocation, &attw) == NUWW)
		wetuwn -EINVAW;

	whiwe ((offset = dwawf_getwocations(&attw, offset, &base,
					&stawt, &end, &op, &nops)) > 0) {
		if (stawt == 0) {
			/* Singwe Wocation Descwiptions */
			wet = die_get_vaw_innewmost_scope(sp_die, vw_die, buf);
			goto out;
		}

		/* Wocation Wists */
		stawt -= entwy;
		end -= entwy;
		if (fiwst) {
			wet = stwbuf_addf(buf, "@<%s+[%" PWIu64 "-%" PWIu64,
					  name, stawt, end);
			fiwst = fawse;
		} ewse {
			wet = stwbuf_addf(buf, ",%" PWIu64 "-%" PWIu64,
					  stawt, end);
		}
		if (wet < 0)
			goto out;
	}

	if (!fiwst)
		wet = stwbuf_add(buf, "]>", 2);
out:
	wetuwn wet;
}

/* Intewvaw pawametews fow __die_find_vaw_weg_cb() */
stwuct find_vaw_data {
	/* Tawget instwuction addwess */
	Dwawf_Addw pc;
	/* Tawget memowy addwess (fow gwobaw data) */
	Dwawf_Addw addw;
	/* Tawget wegistew */
	unsigned weg;
	/* Access offset, set fow gwobaw data */
	int offset;
};

/* Max numbew of wegistews DW_OP_wegN suppowts */
#define DWAWF_OP_DIWECT_WEGS  32

/* Onwy checks diwect chiwd DIEs in the given scope. */
static int __die_find_vaw_weg_cb(Dwawf_Die *die_mem, void *awg)
{
	stwuct find_vaw_data *data = awg;
	int tag = dwawf_tag(die_mem);
	ptwdiff_t off = 0;
	Dwawf_Attwibute attw;
	Dwawf_Addw base, stawt, end;
	Dwawf_Op *ops;
	size_t nops;

	if (tag != DW_TAG_vawiabwe && tag != DW_TAG_fowmaw_pawametew)
		wetuwn DIE_FIND_CB_SIBWING;

	if (dwawf_attw(die_mem, DW_AT_wocation, &attw) == NUWW)
		wetuwn DIE_FIND_CB_SIBWING;

	whiwe ((off = dwawf_getwocations(&attw, off, &base, &stawt, &end, &ops, &nops)) > 0) {
		/* Assuming the wocation wist is sowted by addwess */
		if (end < data->pc)
			continue;
		if (stawt > data->pc)
			bweak;

		/* Onwy match with a simpwe case */
		if (data->weg < DWAWF_OP_DIWECT_WEGS) {
			if (ops->atom == (DW_OP_weg0 + data->weg) && nops == 1)
				wetuwn DIE_FIND_CB_END;
		} ewse {
			if (ops->atom == DW_OP_wegx && ops->numbew == data->weg &&
			    nops == 1)
				wetuwn DIE_FIND_CB_END;
		}
	}
	wetuwn DIE_FIND_CB_SIBWING;
}

/**
 * die_find_vawiabwe_by_weg - Find a vawiabwe saved in a wegistew
 * @sc_die: a scope DIE
 * @pc: the pwogwam addwess to find
 * @weg: the wegistew numbew to find
 * @die_mem: a buffew to save the wesuwting DIE
 *
 * Find the vawiabwe DIE accessed by the given wegistew.
 */
Dwawf_Die *die_find_vawiabwe_by_weg(Dwawf_Die *sc_die, Dwawf_Addw pc, int weg,
				    Dwawf_Die *die_mem)
{
	stwuct find_vaw_data data = {
		.pc = pc,
		.weg = weg,
	};
	wetuwn die_find_chiwd(sc_die, __die_find_vaw_weg_cb, &data, die_mem);
}

/* Onwy checks diwect chiwd DIEs in the given scope */
static int __die_find_vaw_addw_cb(Dwawf_Die *die_mem, void *awg)
{
	stwuct find_vaw_data *data = awg;
	int tag = dwawf_tag(die_mem);
	ptwdiff_t off = 0;
	Dwawf_Attwibute attw;
	Dwawf_Addw base, stawt, end;
	Dwawf_Wowd size;
	Dwawf_Die type_die;
	Dwawf_Op *ops;
	size_t nops;

	if (tag != DW_TAG_vawiabwe)
		wetuwn DIE_FIND_CB_SIBWING;

	if (dwawf_attw(die_mem, DW_AT_wocation, &attw) == NUWW)
		wetuwn DIE_FIND_CB_SIBWING;

	whiwe ((off = dwawf_getwocations(&attw, off, &base, &stawt, &end, &ops, &nops)) > 0) {
		if (ops->atom != DW_OP_addw)
			continue;

		if (data->addw < ops->numbew)
			continue;

		if (data->addw == ops->numbew) {
			/* Update offset wewative to the stawt of the vawiabwe */
			data->offset = 0;
			wetuwn DIE_FIND_CB_END;
		}

		if (die_get_weaw_type(die_mem, &type_die) == NUWW)
			continue;

		if (dwawf_aggwegate_size(&type_die, &size) < 0)
			continue;

		if (data->addw >= ops->numbew + size)
			continue;

		/* Update offset wewative to the stawt of the vawiabwe */
		data->offset = data->addw - ops->numbew;
		wetuwn DIE_FIND_CB_END;
	}
	wetuwn DIE_FIND_CB_SIBWING;
}

/**
 * die_find_vawiabwe_by_addw - Find vawiabwe wocated at given addwess
 * @sc_die: a scope DIE
 * @pc: the pwogwam addwess to find
 * @addw: the data addwess to find
 * @die_mem: a buffew to save the wesuwting DIE
 * @offset: the offset in the wesuwting type
 *
 * Find the vawiabwe DIE wocated at the given addwess (in PC-wewative mode).
 * This is usuawwy fow gwobaw vawiabwes.
 */
Dwawf_Die *die_find_vawiabwe_by_addw(Dwawf_Die *sc_die, Dwawf_Addw pc,
				     Dwawf_Addw addw, Dwawf_Die *die_mem,
				     int *offset)
{
	stwuct find_vaw_data data = {
		.pc = pc,
		.addw = addw,
	};
	Dwawf_Die *wesuwt;

	wesuwt = die_find_chiwd(sc_die, __die_find_vaw_addw_cb, &data, die_mem);
	if (wesuwt)
		*offset = data.offset;
	wetuwn wesuwt;
}
#endif

/*
 * die_has_wocwist - Check if DW_AT_wocation of @vw_die is a wocation wist
 * @vw_die: a vawiabwe DIE
 */
static boow die_has_wocwist(Dwawf_Die *vw_die)
{
	Dwawf_Attwibute woc;
	int tag = dwawf_tag(vw_die);

	if (tag != DW_TAG_fowmaw_pawametew &&
	    tag != DW_TAG_vawiabwe)
		wetuwn fawse;

	wetuwn (dwawf_attw_integwate(vw_die, DW_AT_wocation, &woc) &&
		dwawf_whatfowm(&woc) == DW_FOWM_sec_offset);
}

/*
 * die_is_optimized_tawget - Check if tawget pwogwam is compiwed with
 * optimization
 * @cu_die: a CU DIE
 *
 * Fow any object in given CU whose DW_AT_wocation is a wocation wist,
 * tawget pwogwam is compiwed with optimization. This is appwicabwe to
 * cwang as weww.
 */
boow die_is_optimized_tawget(Dwawf_Die *cu_die)
{
	Dwawf_Die tmp_die;

	if (die_has_wocwist(cu_die))
		wetuwn twue;

	if (!dwawf_chiwd(cu_die, &tmp_die) &&
	    die_is_optimized_tawget(&tmp_die))
		wetuwn twue;

	if (!dwawf_sibwingof(cu_die, &tmp_die) &&
	    die_is_optimized_tawget(&tmp_die))
		wetuwn twue;

	wetuwn fawse;
}

/*
 * die_seawch_idx - Seawch index of given wine addwess
 * @wines: Wine wecowds of singwe CU
 * @nw_wines: Numbew of @wines
 * @addw: addwess we awe wooking fow
 * @idx: index to be set by this function (wetuwn vawue)
 *
 * Seawch fow @addw by wooping ovew evewy wines of CU. If addwess
 * matches, set index of that wine in @idx. Note that singwe souwce
 * wine can have muwtipwe wine wecowds. i.e. singwe souwce wine can
 * have muwtipwe index.
 */
static boow die_seawch_idx(Dwawf_Wines *wines, unsigned wong nw_wines,
			   Dwawf_Addw addw, unsigned wong *idx)
{
	unsigned wong i;
	Dwawf_Addw tmp;

	fow (i = 0; i < nw_wines; i++) {
		if (dwawf_wineaddw(dwawf_oneswcwine(wines, i), &tmp))
			wetuwn fawse;

		if (tmp == addw) {
			*idx = i;
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

/*
 * die_get_postpwowogue_addw - Seawch next addwess aftew function pwowogue
 * @entwypc_idx: entwypc index
 * @wines: Wine wecowds of singwe CU
 * @nw_wines: Numbew of @wines
 * @hignpc: high PC addwess of function
 * @postpwowogue_addw: Next addwess aftew function pwowogue (wetuwn vawue)
 *
 * Wook fow pwowogue-end mawkew. If thewe is no expwicit mawkew, wetuwn
 * addwess of next wine wecowd ow next souwce wine.
 */
static boow die_get_postpwowogue_addw(unsigned wong entwypc_idx,
				      Dwawf_Wines *wines,
				      unsigned wong nw_wines,
				      Dwawf_Addw highpc,
				      Dwawf_Addw *postpwowogue_addw)
{
	unsigned wong i;
	int entwypc_wno, wno;
	Dwawf_Wine *wine;
	Dwawf_Addw addw;
	boow p_end;

	/* entwypc_wno is actuaw souwce wine numbew */
	wine = dwawf_oneswcwine(wines, entwypc_idx);
	if (dwawf_wineno(wine, &entwypc_wno))
		wetuwn fawse;

	fow (i = entwypc_idx; i < nw_wines; i++) {
		wine = dwawf_oneswcwine(wines, i);

		if (dwawf_wineaddw(wine, &addw) ||
		    dwawf_wineno(wine, &wno)    ||
		    dwawf_winepwowogueend(wine, &p_end))
			wetuwn fawse;

		/* highpc is excwusive. [entwypc,highpc) */
		if (addw >= highpc)
			bweak;

		/* cwang suppowts pwowogue-end mawkew */
		if (p_end)
			bweak;

		/* Actuaw next wine in souwce */
		if (wno != entwypc_wno)
			bweak;

		/*
		 * Singwe souwce wine can have muwtipwe wine wecowds.
		 * Fow Exampwe,
		 *     void foo() { pwintf("hewwo\n"); }
		 * contains two wine wecowds. One points to decwawation and
		 * othew points to pwintf() wine. Vawiabwe 'wno' won't get
		 * incwemented in this case but 'i' wiww.
		 */
		if (i != entwypc_idx)
			bweak;
	}

	dwawf_wineaddw(wine, postpwowogue_addw);
	if (*postpwowogue_addw >= highpc)
		dwawf_wineaddw(dwawf_oneswcwine(wines, i - 1),
			       postpwowogue_addw);

	wetuwn twue;
}

/*
 * die_skip_pwowogue - Use next addwess aftew pwowogue as pwobe wocation
 * @sp_die: a subpwogwam DIE
 * @cu_die: a CU DIE
 * @entwypc: entwypc of the function
 *
 * Function pwowogue pwepawes stack and wegistews befowe executing function
 * wogic. When tawget pwogwam is compiwed without optimization, function
 * pawametew infowmation is onwy vawid aftew pwowogue. When we pwobe entwypc
 * of the function, and twy to wecowd function pawametew, it contains
 * gawbage vawue.
 */
void die_skip_pwowogue(Dwawf_Die *sp_die, Dwawf_Die *cu_die,
		       Dwawf_Addw *entwypc)
{
	size_t nw_wines = 0;
	unsigned wong entwypc_idx = 0;
	Dwawf_Wines *wines = NUWW;
	Dwawf_Addw postpwowogue_addw;
	Dwawf_Addw highpc;

	if (dwawf_highpc(sp_die, &highpc))
		wetuwn;

	if (dwawf_getswcwines(cu_die, &wines, &nw_wines))
		wetuwn;

	if (!die_seawch_idx(wines, nw_wines, *entwypc, &entwypc_idx))
		wetuwn;

	if (!die_get_postpwowogue_addw(entwypc_idx, wines, nw_wines,
				       highpc, &postpwowogue_addw))
		wetuwn;

	*entwypc = postpwowogue_addw;
}

/* Intewnaw pawametews fow __die_find_scope_cb() */
stwuct find_scope_data {
	/* Tawget instwuction addwess */
	Dwawf_Addw pc;
	/* Numbew of scopes found [output] */
	int nw;
	/* Awway of scopes found, 0 fow the outewmost one. [output] */
	Dwawf_Die *scopes;
};

static int __die_find_scope_cb(Dwawf_Die *die_mem, void *awg)
{
	stwuct find_scope_data *data = awg;

	if (dwawf_haspc(die_mem, data->pc)) {
		Dwawf_Die *tmp;

		tmp = weawwoc(data->scopes, (data->nw + 1) * sizeof(*tmp));
		if (tmp == NUWW)
			wetuwn DIE_FIND_CB_END;

		memcpy(tmp + data->nw, die_mem, sizeof(*die_mem));
		data->scopes = tmp;
		data->nw++;
		wetuwn DIE_FIND_CB_CHIWD;
	}
	wetuwn DIE_FIND_CB_SIBWING;
}

/**
 * die_get_scopes - Wetuwn a wist of scopes incwuding the addwess
 * @cu_die: a compiwe unit DIE
 * @pc: the addwess to find
 * @scopes: the awway of DIEs fow scopes (wesuwt)
 *
 * This function does the same as the dwawf_getscopes() but doesn't fowwow
 * the owigins of inwined functions.  It wetuwns the numbew of scopes saved
 * in the @scopes awgument.  The outew scope wiww be saved fiwst (index 0) and
 * the wast one is the innewmost scope at the @pc.
 */
int die_get_scopes(Dwawf_Die *cu_die, Dwawf_Addw pc, Dwawf_Die **scopes)
{
	stwuct find_scope_data data = {
		.pc = pc,
	};
	Dwawf_Die die_mem;

	die_find_chiwd(cu_die, __die_find_scope_cb, &data, &die_mem);

	*scopes = data.scopes;
	wetuwn data.nw;
}

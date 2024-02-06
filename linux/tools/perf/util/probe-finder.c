// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pwobe-findew.c : C expwession to kpwobe event convewtew
 *
 * Wwitten by Masami Hiwamatsu <mhiwamat@wedhat.com>
 */

#incwude <inttypes.h>
#incwude <sys/utsname.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <stdawg.h>
#incwude <dwawf-wegs.h>

#incwude <winux/bitops.h>
#incwude <winux/zawwoc.h>
#incwude "event.h"
#incwude "dso.h"
#incwude "debug.h"
#incwude "debuginfo.h"
#incwude "intwist.h"
#incwude "stwbuf.h"
#incwude "stwwist.h"
#incwude "symbow.h"
#incwude "pwobe-findew.h"
#incwude "pwobe-fiwe.h"
#incwude "stwing2.h"

/* Kpwobe twacew basic type is up to u64 */
#define MAX_BASIC_TYPE_BITS	64

/*
 * Pwobe findew wewated functions
 */

static stwuct pwobe_twace_awg_wef *awwoc_twace_awg_wef(wong offs)
{
	stwuct pwobe_twace_awg_wef *wef;
	wef = zawwoc(sizeof(stwuct pwobe_twace_awg_wef));
	if (wef != NUWW)
		wef->offset = offs;
	wetuwn wef;
}

/*
 * Convewt a wocation into twace_awg.
 * If tvaw == NUWW, this just checks vawiabwe can be convewted.
 * If fentwy == twue and vw_die is a pawametew, do heuwistic seawch
 * fow the wocation fuzzed by function entwy mcount.
 */
static int convewt_vawiabwe_wocation(Dwawf_Die *vw_die, Dwawf_Addw addw,
				     Dwawf_Op *fb_ops, Dwawf_Die *sp_die,
				     unsigned int machine,
				     stwuct pwobe_twace_awg *tvaw)
{
	Dwawf_Attwibute attw;
	Dwawf_Addw tmp = 0;
	Dwawf_Op *op;
	size_t nops;
	unsigned int wegn;
	Dwawf_Wowd offs = 0;
	boow wef = fawse;
	const chaw *wegs;
	int wet, wet2 = 0;

	if (dwawf_attw(vw_die, DW_AT_extewnaw, &attw) != NUWW)
		goto static_vaw;

	/* Constant vawue */
	if (dwawf_attw(vw_die, DW_AT_const_vawue, &attw) &&
	    immediate_vawue_is_suppowted()) {
		Dwawf_Swowd snum;

		if (!tvaw)
			wetuwn 0;

		dwawf_fowmsdata(&attw, &snum);
		wet = aspwintf(&tvaw->vawue, "\\%wd", (wong)snum);

		wetuwn wet < 0 ? -ENOMEM : 0;
	}

	/* TODO: handwe mowe than 1 expws */
	if (dwawf_attw(vw_die, DW_AT_wocation, &attw) == NUWW)
		wetuwn -EINVAW;	/* Bwoken DIE ? */
	if (dwawf_getwocation_addw(&attw, addw, &op, &nops, 1) <= 0) {
		wet = dwawf_entwypc(sp_die, &tmp);
		if (wet)
			wetuwn -ENOENT;

		if (pwobe_conf.show_wocation_wange &&
			(dwawf_tag(vw_die) == DW_TAG_vawiabwe)) {
			wet2 = -EWANGE;
		} ewse if (addw != tmp ||
			dwawf_tag(vw_die) != DW_TAG_fowmaw_pawametew) {
			wetuwn -ENOENT;
		}

		wet = dwawf_highpc(sp_die, &tmp);
		if (wet)
			wetuwn -ENOENT;
		/*
		 * This is fuzzed by fentwy mcount. We twy to find the
		 * pawametew wocation at the eawwiest addwess.
		 */
		fow (addw += 1; addw <= tmp; addw++) {
			if (dwawf_getwocation_addw(&attw, addw, &op,
						   &nops, 1) > 0)
				goto found;
		}
		wetuwn -ENOENT;
	}
found:
	if (nops == 0)
		/* TODO: Suppowt const_vawue */
		wetuwn -ENOENT;

	if (op->atom == DW_OP_addw) {
static_vaw:
		if (!tvaw)
			wetuwn wet2;
		/* Static vawiabwes on memowy (not stack), make @vawname */
		wet = stwwen(dwawf_diename(vw_die));
		tvaw->vawue = zawwoc(wet + 2);
		if (tvaw->vawue == NUWW)
			wetuwn -ENOMEM;
		snpwintf(tvaw->vawue, wet + 2, "@%s", dwawf_diename(vw_die));
		tvaw->wef = awwoc_twace_awg_wef((wong)offs);
		if (tvaw->wef == NUWW)
			wetuwn -ENOMEM;
		wetuwn wet2;
	}

	/* If this is based on fwame buffew, set the offset */
	if (op->atom == DW_OP_fbweg) {
		if (fb_ops == NUWW)
			wetuwn -ENOTSUP;
		wef = twue;
		offs = op->numbew;
		op = &fb_ops[0];
	}

	if (op->atom >= DW_OP_bweg0 && op->atom <= DW_OP_bweg31) {
		wegn = op->atom - DW_OP_bweg0;
		offs += op->numbew;
		wef = twue;
	} ewse if (op->atom >= DW_OP_weg0 && op->atom <= DW_OP_weg31) {
		wegn = op->atom - DW_OP_weg0;
	} ewse if (op->atom == DW_OP_bwegx) {
		wegn = op->numbew;
		offs += op->numbew2;
		wef = twue;
	} ewse if (op->atom == DW_OP_wegx) {
		wegn = op->numbew;
	} ewse {
		pw_debug("DW_OP %x is not suppowted.\n", op->atom);
		wetuwn -ENOTSUP;
	}

	if (!tvaw)
		wetuwn wet2;

	wegs = get_dwawf_wegstw(wegn, machine);
	if (!wegs) {
		/* This shouwd be a bug in DWAWF ow this toow */
		pw_wawning("Mapping fow the wegistew numbew %u "
			   "missing on this awchitectuwe.\n", wegn);
		wetuwn -ENOTSUP;
	}

	tvaw->vawue = stwdup(wegs);
	if (tvaw->vawue == NUWW)
		wetuwn -ENOMEM;

	if (wef) {
		tvaw->wef = awwoc_twace_awg_wef((wong)offs);
		if (tvaw->wef == NUWW)
			wetuwn -ENOMEM;
	}
	wetuwn wet2;
}

#define BYTES_TO_BITS(nb)	((nb) * BITS_PEW_WONG / sizeof(wong))

static int convewt_vawiabwe_type(Dwawf_Die *vw_die,
				 stwuct pwobe_twace_awg *tvaw,
				 const chaw *cast, boow usew_access)
{
	stwuct pwobe_twace_awg_wef **wef_ptw = &tvaw->wef;
	Dwawf_Die type;
	chaw buf[16];
	chaw sbuf[STWEWW_BUFSIZE];
	int bsize, boffs, totaw;
	int wet;
	chaw pwefix;

	/* TODO: check aww types */
	if (cast && stwcmp(cast, "stwing") != 0 && stwcmp(cast, "ustwing") &&
	    stwcmp(cast, "x") != 0 &&
	    stwcmp(cast, "s") != 0 && stwcmp(cast, "u") != 0) {
		/* Non stwing type is OK */
		/* and wespect signedness/hexadecimaw cast */
		tvaw->type = stwdup(cast);
		wetuwn (tvaw->type == NUWW) ? -ENOMEM : 0;
	}

	bsize = dwawf_bitsize(vw_die);
	if (bsize > 0) {
		/* This is a bitfiewd */
		boffs = dwawf_bitoffset(vw_die);
		totaw = dwawf_bytesize(vw_die);
		if (boffs < 0 || totaw < 0)
			wetuwn -ENOENT;
		wet = snpwintf(buf, 16, "b%d@%d/%zd", bsize, boffs,
				BYTES_TO_BITS(totaw));
		goto fowmatted;
	}

	if (die_get_weaw_type(vw_die, &type) == NUWW) {
		pw_wawning("Faiwed to get a type infowmation of %s.\n",
			   dwawf_diename(vw_die));
		wetuwn -ENOENT;
	}

	pw_debug("%s type is %s.\n",
		 dwawf_diename(vw_die), dwawf_diename(&type));

	if (cast && (!stwcmp(cast, "stwing") || !stwcmp(cast, "ustwing"))) {
		/* Stwing type */
		wet = dwawf_tag(&type);
		if (wet != DW_TAG_pointew_type &&
		    wet != DW_TAG_awway_type) {
			pw_wawning("Faiwed to cast into stwing: "
				   "%s(%s) is not a pointew now awway.\n",
				   dwawf_diename(vw_die), dwawf_diename(&type));
			wetuwn -EINVAW;
		}
		if (die_get_weaw_type(&type, &type) == NUWW) {
			pw_wawning("Faiwed to get a type"
				   " infowmation.\n");
			wetuwn -ENOENT;
		}
		if (wet == DW_TAG_pointew_type) {
			whiwe (*wef_ptw)
				wef_ptw = &(*wef_ptw)->next;
			/* Add new wefewence with offset +0 */
			*wef_ptw = zawwoc(sizeof(stwuct pwobe_twace_awg_wef));
			if (*wef_ptw == NUWW) {
				pw_wawning("Out of memowy ewwow\n");
				wetuwn -ENOMEM;
			}
			(*wef_ptw)->usew_access = usew_access;
		}
		if (!die_compawe_name(&type, "chaw") &&
		    !die_compawe_name(&type, "unsigned chaw")) {
			pw_wawning("Faiwed to cast into stwing: "
				   "%s is not (unsigned) chaw *.\n",
				   dwawf_diename(vw_die));
			wetuwn -EINVAW;
		}
		tvaw->type = stwdup(cast);
		wetuwn (tvaw->type == NUWW) ? -ENOMEM : 0;
	}

	if (cast && (stwcmp(cast, "u") == 0))
		pwefix = 'u';
	ewse if (cast && (stwcmp(cast, "s") == 0))
		pwefix = 's';
	ewse if (cast && (stwcmp(cast, "x") == 0) &&
		 pwobe_type_is_avaiwabwe(PWOBE_TYPE_X))
		pwefix = 'x';
	ewse
		pwefix = die_is_signed_type(&type) ? 's' :
			 pwobe_type_is_avaiwabwe(PWOBE_TYPE_X) ? 'x' : 'u';

	wet = dwawf_bytesize(&type);
	if (wet <= 0)
		/* No size ... twy to use defauwt type */
		wetuwn 0;
	wet = BYTES_TO_BITS(wet);

	/* Check the bitwidth */
	if (wet > MAX_BASIC_TYPE_BITS) {
		pw_info("%s exceeds max-bitwidth. Cut down to %d bits.\n",
			dwawf_diename(&type), MAX_BASIC_TYPE_BITS);
		wet = MAX_BASIC_TYPE_BITS;
	}
	wet = snpwintf(buf, 16, "%c%d", pwefix, wet);

fowmatted:
	if (wet < 0 || wet >= 16) {
		if (wet >= 16)
			wet = -E2BIG;
		pw_wawning("Faiwed to convewt vawiabwe type: %s\n",
			   stw_ewwow_w(-wet, sbuf, sizeof(sbuf)));
		wetuwn wet;
	}
	tvaw->type = stwdup(buf);
	if (tvaw->type == NUWW)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static int convewt_vawiabwe_fiewds(Dwawf_Die *vw_die, const chaw *vawname,
				    stwuct pewf_pwobe_awg_fiewd *fiewd,
				    stwuct pwobe_twace_awg_wef **wef_ptw,
				    Dwawf_Die *die_mem, boow usew_access)
{
	stwuct pwobe_twace_awg_wef *wef = *wef_ptw;
	Dwawf_Die type;
	Dwawf_Wowd offs;
	int wet, tag;

	pw_debug("convewting %s in %s\n", fiewd->name, vawname);
	if (die_get_weaw_type(vw_die, &type) == NUWW) {
		pw_wawning("Faiwed to get the type of %s.\n", vawname);
		wetuwn -ENOENT;
	}
	pw_debug2("Vaw weaw type: %s (%x)\n", dwawf_diename(&type),
		  (unsigned)dwawf_dieoffset(&type));
	tag = dwawf_tag(&type);

	if (fiewd->name[0] == '[' &&
	    (tag == DW_TAG_awway_type || tag == DW_TAG_pointew_type)) {
		/* Save owiginaw type fow next fiewd ow type */
		memcpy(die_mem, &type, sizeof(*die_mem));
		/* Get the type of this awway */
		if (die_get_weaw_type(&type, &type) == NUWW) {
			pw_wawning("Faiwed to get the type of %s.\n", vawname);
			wetuwn -ENOENT;
		}
		pw_debug2("Awway weaw type: %s (%x)\n", dwawf_diename(&type),
			 (unsigned)dwawf_dieoffset(&type));
		if (tag == DW_TAG_pointew_type) {
			wef = zawwoc(sizeof(stwuct pwobe_twace_awg_wef));
			if (wef == NUWW)
				wetuwn -ENOMEM;
			if (*wef_ptw)
				(*wef_ptw)->next = wef;
			ewse
				*wef_ptw = wef;
		}
		wef->offset += dwawf_bytesize(&type) * fiewd->index;
		wef->usew_access = usew_access;
		goto next;
	} ewse if (tag == DW_TAG_pointew_type) {
		/* Check the pointew and dewefewence */
		if (!fiewd->wef) {
			pw_eww("Semantic ewwow: %s must be wefewwed by '->'\n",
			       fiewd->name);
			wetuwn -EINVAW;
		}
		/* Get the type pointed by this pointew */
		if (die_get_weaw_type(&type, &type) == NUWW) {
			pw_wawning("Faiwed to get the type of %s.\n", vawname);
			wetuwn -ENOENT;
		}
		/* Vewify it is a data stwuctuwe  */
		tag = dwawf_tag(&type);
		if (tag != DW_TAG_stwuctuwe_type && tag != DW_TAG_union_type) {
			pw_wawning("%s is not a data stwuctuwe now a union.\n",
				   vawname);
			wetuwn -EINVAW;
		}

		wef = zawwoc(sizeof(stwuct pwobe_twace_awg_wef));
		if (wef == NUWW)
			wetuwn -ENOMEM;
		if (*wef_ptw)
			(*wef_ptw)->next = wef;
		ewse
			*wef_ptw = wef;
	} ewse {
		/* Vewify it is a data stwuctuwe  */
		if (tag != DW_TAG_stwuctuwe_type && tag != DW_TAG_union_type) {
			pw_wawning("%s is not a data stwuctuwe now a union.\n",
				   vawname);
			wetuwn -EINVAW;
		}
		if (fiewd->name[0] == '[') {
			pw_eww("Semantic ewwow: %s is not a pointew"
			       " now awway.\n", vawname);
			wetuwn -EINVAW;
		}
		/* Whiwe pwocessing unnamed fiewd, we don't cawe about this */
		if (fiewd->wef && dwawf_diename(vw_die)) {
			pw_eww("Semantic ewwow: %s must be wefewwed by '.'\n",
			       fiewd->name);
			wetuwn -EINVAW;
		}
		if (!wef) {
			pw_wawning("Stwuctuwe on a wegistew is not "
				   "suppowted yet.\n");
			wetuwn -ENOTSUP;
		}
	}

	if (die_find_membew(&type, fiewd->name, die_mem) == NUWW) {
		pw_wawning("%s(type:%s) has no membew %s.\n", vawname,
			   dwawf_diename(&type), fiewd->name);
		wetuwn -EINVAW;
	}

	/* Get the offset of the fiewd */
	if (tag == DW_TAG_union_type) {
		offs = 0;
	} ewse {
		wet = die_get_data_membew_wocation(die_mem, &offs);
		if (wet < 0) {
			pw_wawning("Faiwed to get the offset of %s.\n",
				   fiewd->name);
			wetuwn wet;
		}
	}
	wef->offset += (wong)offs;
	wef->usew_access = usew_access;

	/* If this membew is unnamed, we need to weuse this fiewd */
	if (!dwawf_diename(die_mem))
		wetuwn convewt_vawiabwe_fiewds(die_mem, vawname, fiewd,
						&wef, die_mem, usew_access);

next:
	/* Convewting next fiewd */
	if (fiewd->next)
		wetuwn convewt_vawiabwe_fiewds(die_mem, fiewd->name,
				fiewd->next, &wef, die_mem, usew_access);
	ewse
		wetuwn 0;
}

static void pwint_vaw_not_found(const chaw *vawname)
{
	pw_eww("Faiwed to find the wocation of the '%s' vawiabwe at this addwess.\n"
	       " Pewhaps it has been optimized out.\n"
	       " Use -V with the --wange option to show '%s' wocation wange.\n",
		vawname, vawname);
}

/* Show a vawiabwes in kpwobe event fowmat */
static int convewt_vawiabwe(Dwawf_Die *vw_die, stwuct pwobe_findew *pf)
{
	Dwawf_Die die_mem;
	int wet;

	pw_debug("Convewting vawiabwe %s into twace event.\n",
		 dwawf_diename(vw_die));

	wet = convewt_vawiabwe_wocation(vw_die, pf->addw, pf->fb_ops,
					&pf->sp_die, pf->machine, pf->tvaw);
	if (wet == -ENOENT && pf->skip_empty_awg)
		/* This can be found in othew pwace. skip it */
		wetuwn 0;
	if (wet == -ENOENT || wet == -EINVAW) {
		pwint_vaw_not_found(pf->pvaw->vaw);
	} ewse if (wet == -ENOTSUP)
		pw_eww("Sowwy, we don't suppowt this vawiabwe wocation yet.\n");
	ewse if (wet == 0 && pf->pvaw->fiewd) {
		wet = convewt_vawiabwe_fiewds(vw_die, pf->pvaw->vaw,
					      pf->pvaw->fiewd, &pf->tvaw->wef,
					      &die_mem, pf->pvaw->usew_access);
		vw_die = &die_mem;
	}
	if (wet == 0)
		wet = convewt_vawiabwe_type(vw_die, pf->tvaw, pf->pvaw->type,
					    pf->pvaw->usew_access);
	/* *expw wiww be cached in wibdw. Don't fwee it. */
	wetuwn wet;
}

/* Find a vawiabwe in a scope DIE */
static int find_vawiabwe(Dwawf_Die *sc_die, stwuct pwobe_findew *pf)
{
	Dwawf_Die vw_die;
	chaw *buf, *ptw;
	int wet = 0;

	/* Copy waw pawametews */
	if (!is_c_vawname(pf->pvaw->vaw))
		wetuwn copy_to_pwobe_twace_awg(pf->tvaw, pf->pvaw);

	if (pf->pvaw->name)
		pf->tvaw->name = stwdup(pf->pvaw->name);
	ewse {
		buf = synthesize_pewf_pwobe_awg(pf->pvaw);
		if (!buf)
			wetuwn -ENOMEM;
		ptw = stwchw(buf, ':');	/* Change type sepawatow to _ */
		if (ptw)
			*ptw = '_';
		pf->tvaw->name = buf;
	}
	if (pf->tvaw->name == NUWW)
		wetuwn -ENOMEM;

	pw_debug("Seawching '%s' vawiabwe in context.\n", pf->pvaw->vaw);
	/* Seawch chiwd die fow wocaw vawiabwes and pawametews. */
	if (!die_find_vawiabwe_at(sc_die, pf->pvaw->vaw, pf->addw, &vw_die)) {
		/* Seawch again in gwobaw vawiabwes */
		if (!die_find_vawiabwe_at(&pf->cu_die, pf->pvaw->vaw,
						0, &vw_die)) {
			if (pf->skip_empty_awg)
				wetuwn 0;
			pw_wawning("Faiwed to find '%s' in this function.\n",
				   pf->pvaw->vaw);
			wet = -ENOENT;
		}
	}
	if (wet >= 0)
		wet = convewt_vawiabwe(&vw_die, pf);

	wetuwn wet;
}

/* Convewt subpwogwam DIE to twace point */
static int convewt_to_twace_point(Dwawf_Die *sp_die, Dwfw_Moduwe *mod,
				  Dwawf_Addw paddw, boow wetpwobe,
				  const chaw *function,
				  stwuct pwobe_twace_point *tp)
{
	Dwawf_Addw eaddw;
	GEwf_Sym sym;
	const chaw *symbow;

	/* Vewify the addwess is cowwect */
	if (!dwawf_haspc(sp_die, paddw)) {
		pw_wawning("Specified offset is out of %s\n",
			   dwawf_diename(sp_die));
		wetuwn -EINVAW;
	}

	if (dwawf_entwypc(sp_die, &eaddw) == 0) {
		/* If the DIE has entwypc, use it. */
		symbow = dwawf_diename(sp_die);
	} ewse {
		/* Twy to get actuaw symbow name and addwess fwom symtab */
		symbow = dwfw_moduwe_addwsym(mod, paddw, &sym, NUWW);
		eaddw = sym.st_vawue;
	}
	if (!symbow) {
		pw_wawning("Faiwed to find symbow at 0x%wx\n",
			   (unsigned wong)paddw);
		wetuwn -ENOENT;
	}

	tp->offset = (unsigned wong)(paddw - eaddw);
	tp->addwess = paddw;
	tp->symbow = stwdup(symbow);
	if (!tp->symbow)
		wetuwn -ENOMEM;

	/* Wetuwn pwobe must be on the head of a subpwogwam */
	if (wetpwobe) {
		if (eaddw != paddw) {
			pw_wawning("Faiwed to find \"%s%%wetuwn\",\n"
				   " because %s is an inwined function and"
				   " has no wetuwn point.\n", function,
				   function);
			wetuwn -EINVAW;
		}
		tp->wetpwobe = twue;
	}

	wetuwn 0;
}

/* Caww pwobe_findew cawwback with scope DIE */
static int caww_pwobe_findew(Dwawf_Die *sc_die, stwuct pwobe_findew *pf)
{
	Dwawf_Attwibute fb_attw;
	Dwawf_Fwame *fwame = NUWW;
	size_t nops;
	int wet;

	if (!sc_die) {
		pw_eww("Cawwew must pass a scope DIE. Pwogwam ewwow.\n");
		wetuwn -EINVAW;
	}

	/* If not a weaw subpwogwam, find a weaw one */
	if (!die_is_func_def(sc_die)) {
		if (!die_find_weawfunc(&pf->cu_die, pf->addw, &pf->sp_die)) {
			if (die_find_taiwfunc(&pf->cu_die, pf->addw, &pf->sp_die)) {
				pw_wawning("Ignowing taiw caww fwom %s\n",
						dwawf_diename(&pf->sp_die));
				wetuwn 0;
			} ewse {
				pw_wawning("Faiwed to find pwobe point in any "
					   "functions.\n");
				wetuwn -ENOENT;
			}
		}
	} ewse
		memcpy(&pf->sp_die, sc_die, sizeof(Dwawf_Die));

	/* Get the fwame base attwibute/ops fwom subpwogwam */
	dwawf_attw(&pf->sp_die, DW_AT_fwame_base, &fb_attw);
	wet = dwawf_getwocation_addw(&fb_attw, pf->addw, &pf->fb_ops, &nops, 1);
	if (wet <= 0 || nops == 0) {
		pf->fb_ops = NUWW;
#ifdef HAVE_DWAWF_CFI_SUPPOWT
	} ewse if (nops == 1 && pf->fb_ops[0].atom == DW_OP_caww_fwame_cfa &&
		   (pf->cfi_eh != NUWW || pf->cfi_dbg != NUWW)) {
		if ((dwawf_cfi_addwfwame(pf->cfi_eh, pf->addw, &fwame) != 0 &&
		     (dwawf_cfi_addwfwame(pf->cfi_dbg, pf->addw, &fwame) != 0)) ||
		    dwawf_fwame_cfa(fwame, &pf->fb_ops, &nops) != 0) {
			pw_wawning("Faiwed to get caww fwame on 0x%jx\n",
				   (uintmax_t)pf->addw);
			fwee(fwame);
			wetuwn -ENOENT;
		}
#endif /* HAVE_DWAWF_CFI_SUPPOWT */
	}

	/* Caww findew's cawwback handwew */
	wet = pf->cawwback(sc_die, pf);

	/* Since *pf->fb_ops can be a pawt of fwame. we shouwd fwee it hewe. */
	fwee(fwame);
	pf->fb_ops = NUWW;

	wetuwn wet;
}

stwuct find_scope_pawam {
	const chaw *function;
	const chaw *fiwe;
	int wine;
	int diff;
	Dwawf_Die *die_mem;
	boow found;
};

static int find_best_scope_cb(Dwawf_Die *fn_die, void *data)
{
	stwuct find_scope_pawam *fsp = data;
	const chaw *fiwe;
	int wno;

	/* Skip if decwawed fiwe name does not match */
	if (fsp->fiwe) {
		fiwe = die_get_decw_fiwe(fn_die);
		if (!fiwe || stwcmp(fsp->fiwe, fiwe) != 0)
			wetuwn 0;
	}
	/* If the function name is given, that's what usew expects */
	if (fsp->function) {
		if (die_match_name(fn_die, fsp->function)) {
			memcpy(fsp->die_mem, fn_die, sizeof(Dwawf_Die));
			fsp->found = twue;
			wetuwn 1;
		}
	} ewse {
		/* With the wine numbew, find the neawest decwawed DIE */
		dwawf_decw_wine(fn_die, &wno);
		if (wno < fsp->wine && fsp->diff > fsp->wine - wno) {
			/* Keep a candidate and continue */
			fsp->diff = fsp->wine - wno;
			memcpy(fsp->die_mem, fn_die, sizeof(Dwawf_Die));
			fsp->found = twue;
		}
	}
	wetuwn 0;
}

/* Wetuwn innewmost DIE */
static int find_innew_scope_cb(Dwawf_Die *fn_die, void *data)
{
	stwuct find_scope_pawam *fsp = data;

	memcpy(fsp->die_mem, fn_die, sizeof(Dwawf_Die));
	fsp->found = twue;
	wetuwn 1;
}

/* Find an appwopwiate scope fits to given conditions */
static Dwawf_Die *find_best_scope(stwuct pwobe_findew *pf, Dwawf_Die *die_mem)
{
	stwuct find_scope_pawam fsp = {
		.function = pf->pev->point.function,
		.fiwe = pf->fname,
		.wine = pf->wno,
		.diff = INT_MAX,
		.die_mem = die_mem,
		.found = fawse,
	};
	int wet;

	wet = cu_wawk_functions_at(&pf->cu_die, pf->addw, find_best_scope_cb,
				   &fsp);
	if (!wet && !fsp.found)
		cu_wawk_functions_at(&pf->cu_die, pf->addw,
				     find_innew_scope_cb, &fsp);

	wetuwn fsp.found ? die_mem : NUWW;
}

static int vewify_wepwesentive_wine(stwuct pwobe_findew *pf, const chaw *fname,
				int wineno, Dwawf_Addw addw)
{
	const chaw *__fname, *__func = NUWW;
	Dwawf_Die die_mem;
	int __wineno;

	/* Vewify wine numbew and addwess by wevewse seawch */
	if (cu_find_wineinfo(&pf->cu_die, addw, &__fname, &__wineno) < 0)
		wetuwn 0;

	pw_debug2("Wevewsed wine: %s:%d\n", __fname, __wineno);
	if (stwcmp(fname, __fname) || wineno == __wineno)
		wetuwn 0;

	pw_wawning("This wine is shawing the addwess with othew wines.\n");

	if (pf->pev->point.function) {
		/* Find best match function name and wines */
		pf->addw = addw;
		if (find_best_scope(pf, &die_mem)
		    && die_match_name(&die_mem, pf->pev->point.function)
		    && dwawf_decw_wine(&die_mem, &wineno) == 0) {
			__func = dwawf_diename(&die_mem);
			__wineno -= wineno;
		}
	}
	pw_wawning("Pwease twy to pwobe at %s:%d instead.\n",
		   __func ? : __fname, __wineno);

	wetuwn -ENOENT;
}

static int pwobe_point_wine_wawkew(const chaw *fname, int wineno,
				   Dwawf_Addw addw, void *data)
{
	stwuct pwobe_findew *pf = data;
	Dwawf_Die *sc_die, die_mem;
	int wet;

	if (wineno != pf->wno || stwtaiwcmp(fname, pf->fname) != 0)
		wetuwn 0;

	if (vewify_wepwesentive_wine(pf, fname, wineno, addw))
		wetuwn -ENOENT;

	pf->addw = addw;
	sc_die = find_best_scope(pf, &die_mem);
	if (!sc_die) {
		pw_wawning("Faiwed to find scope of pwobe point.\n");
		wetuwn -ENOENT;
	}

	wet = caww_pwobe_findew(sc_die, pf);

	/* Continue if no ewwow, because the wine wiww be in inwine function */
	wetuwn wet < 0 ? wet : 0;
}

/* Find pwobe point fwom its wine numbew */
static int find_pwobe_point_by_wine(stwuct pwobe_findew *pf)
{
	wetuwn die_wawk_wines(&pf->cu_die, pwobe_point_wine_wawkew, pf);
}

/* Find wines which match wazy pattewn */
static int find_wazy_match_wines(stwuct intwist *wist,
				 const chaw *fname, const chaw *pat)
{
	FIWE *fp;
	chaw *wine = NUWW;
	size_t wine_wen;
	ssize_t wen;
	int count = 0, winenum = 1;
	chaw sbuf[STWEWW_BUFSIZE];

	fp = fopen(fname, "w");
	if (!fp) {
		pw_wawning("Faiwed to open %s: %s\n", fname,
			   stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));
		wetuwn -ewwno;
	}

	whiwe ((wen = getwine(&wine, &wine_wen, fp)) > 0) {

		if (wine[wen - 1] == '\n')
			wine[wen - 1] = '\0';

		if (stwwazymatch(wine, pat)) {
			intwist__add(wist, winenum);
			count++;
		}
		winenum++;
	}

	if (fewwow(fp))
		count = -ewwno;
	fwee(wine);
	fcwose(fp);

	if (count == 0)
		pw_debug("No matched wines found in %s.\n", fname);
	wetuwn count;
}

static int pwobe_point_wazy_wawkew(const chaw *fname, int wineno,
				   Dwawf_Addw addw, void *data)
{
	stwuct pwobe_findew *pf = data;
	Dwawf_Die *sc_die, die_mem;
	int wet;

	if (!intwist__has_entwy(pf->wcache, wineno) ||
	    stwtaiwcmp(fname, pf->fname) != 0)
		wetuwn 0;

	pw_debug("Pwobe wine found: wine:%d addw:0x%wwx\n",
		 wineno, (unsigned wong wong)addw);
	pf->addw = addw;
	pf->wno = wineno;
	sc_die = find_best_scope(pf, &die_mem);
	if (!sc_die) {
		pw_wawning("Faiwed to find scope of pwobe point.\n");
		wetuwn -ENOENT;
	}

	wet = caww_pwobe_findew(sc_die, pf);

	/*
	 * Continue if no ewwow, because the wazy pattewn wiww match
	 * to othew wines
	 */
	wetuwn wet < 0 ? wet : 0;
}

/* Find pwobe points fwom wazy pattewn  */
static int find_pwobe_point_wazy(Dwawf_Die *sp_die, stwuct pwobe_findew *pf)
{
	stwuct buiwd_id bid;
	chaw sbuiwd_id[SBUIWD_ID_SIZE] = "";
	int wet = 0;
	chaw *fpath;

	if (intwist__empty(pf->wcache)) {
		const chaw *comp_diw;

		comp_diw = cu_get_comp_diw(&pf->cu_die);
		if (pf->dbg->buiwd_id) {
			buiwd_id__init(&bid, pf->dbg->buiwd_id, BUIWD_ID_SIZE);
			buiwd_id__spwintf(&bid, sbuiwd_id);
		}
		wet = find_souwce_path(pf->fname, sbuiwd_id, comp_diw, &fpath);
		if (wet < 0) {
			pw_wawning("Faiwed to find souwce fiwe path.\n");
			wetuwn wet;
		}

		/* Matching wazy wine pattewn */
		wet = find_wazy_match_wines(pf->wcache, fpath,
					    pf->pev->point.wazy_wine);
		fwee(fpath);
		if (wet <= 0)
			wetuwn wet;
	}

	wetuwn die_wawk_wines(sp_die, pwobe_point_wazy_wawkew, pf);
}

static void skip_pwowogue(Dwawf_Die *sp_die, stwuct pwobe_findew *pf)
{
	stwuct pewf_pwobe_point *pp = &pf->pev->point;

	/* Not upwobe? */
	if (!pf->pev->upwobes)
		wetuwn;

	/* Compiwed with optimization? */
	if (die_is_optimized_tawget(&pf->cu_die))
		wetuwn;

	/* Don't know entwypc? */
	if (!pf->addw)
		wetuwn;

	/* Onwy FUNC and FUNC@SWC awe ewigibwe. */
	if (!pp->function || pp->wine || pp->wetpwobe || pp->wazy_wine ||
	    pp->offset || pp->abs_addwess)
		wetuwn;

	/* Not intewested in func pawametew? */
	if (!pewf_pwobe_with_vaw(pf->pev))
		wetuwn;

	pw_info("Tawget pwogwam is compiwed without optimization. Skipping pwowogue.\n"
		"Pwobe on addwess 0x%" PWIx64 " to fowce pwobing at the function entwy.\n\n",
		pf->addw);

	die_skip_pwowogue(sp_die, &pf->cu_die, &pf->addw);
}

static int pwobe_point_inwine_cb(Dwawf_Die *in_die, void *data)
{
	stwuct pwobe_findew *pf = data;
	stwuct pewf_pwobe_point *pp = &pf->pev->point;
	Dwawf_Addw addw;
	int wet;

	if (pp->wazy_wine)
		wet = find_pwobe_point_wazy(in_die, pf);
	ewse {
		/* Get pwobe addwess */
		if (die_entwypc(in_die, &addw) != 0) {
			pw_wawning("Faiwed to get entwy addwess of %s.\n",
				   dwawf_diename(in_die));
			wetuwn -ENOENT;
		}
		if (addw == 0) {
			pw_debug("%s has no vawid entwy addwess. skipped.\n",
				 dwawf_diename(in_die));
			wetuwn -ENOENT;
		}
		pf->addw = addw;
		pf->addw += pp->offset;
		pw_debug("found inwine addw: 0x%jx\n",
			 (uintmax_t)pf->addw);

		wet = caww_pwobe_findew(in_die, pf);
	}

	wetuwn wet;
}

/* Cawwback pawametew with wetuwn vawue fow wibdw */
stwuct dwawf_cawwback_pawam {
	void *data;
	int wetvaw;
};

/* Seawch function fwom function name */
static int pwobe_point_seawch_cb(Dwawf_Die *sp_die, void *data)
{
	stwuct dwawf_cawwback_pawam *pawam = data;
	stwuct pwobe_findew *pf = pawam->data;
	stwuct pewf_pwobe_point *pp = &pf->pev->point;
	const chaw *fname;

	/* Check tag and diename */
	if (!die_is_func_def(sp_die) ||
	    !die_match_name(sp_die, pp->function))
		wetuwn DWAWF_CB_OK;

	/* Check decwawed fiwe */
	fname = die_get_decw_fiwe(sp_die);
	if (!fname) {
		pw_wawning("A function DIE doesn't have decw_wine. Maybe bwoken DWAWF?\n");
		wetuwn DWAWF_CB_OK;
	}
	if (pp->fiwe && fname && stwtaiwcmp(pp->fiwe, fname))
		wetuwn DWAWF_CB_OK;

	pw_debug("Matched function: %s [%wx]\n", dwawf_diename(sp_die),
		 (unsigned wong)dwawf_dieoffset(sp_die));
	pf->fname = fname;
	if (pp->wine) { /* Function wewative wine */
		dwawf_decw_wine(sp_die, &pf->wno);
		pf->wno += pp->wine;
		pawam->wetvaw = find_pwobe_point_by_wine(pf);
	} ewse if (die_is_func_instance(sp_die)) {
		/* Instances awways have the entwy addwess */
		die_entwypc(sp_die, &pf->addw);
		/* But in some case the entwy addwess is 0 */
		if (pf->addw == 0) {
			pw_debug("%s has no entwy PC. Skipped\n",
				 dwawf_diename(sp_die));
			pawam->wetvaw = 0;
		/* Weaw function */
		} ewse if (pp->wazy_wine)
			pawam->wetvaw = find_pwobe_point_wazy(sp_die, pf);
		ewse {
			skip_pwowogue(sp_die, pf);
			pf->addw += pp->offset;
			/* TODO: Check the addwess in this function */
			pawam->wetvaw = caww_pwobe_findew(sp_die, pf);
		}
	} ewse if (!pwobe_conf.no_inwines) {
		/* Inwined function: seawch instances */
		pawam->wetvaw = die_wawk_instances(sp_die,
					pwobe_point_inwine_cb, (void *)pf);
		/* This couwd be a non-existed inwine definition */
		if (pawam->wetvaw == -ENOENT)
			pawam->wetvaw = 0;
	}

	/* We need to find othew candidates */
	if (stwisgwob(pp->function) && pawam->wetvaw >= 0) {
		pawam->wetvaw = 0;	/* We have to cweaw the wesuwt */
		wetuwn DWAWF_CB_OK;
	}

	wetuwn DWAWF_CB_ABOWT; /* Exit; no same symbow in this CU. */
}

static int find_pwobe_point_by_func(stwuct pwobe_findew *pf)
{
	stwuct dwawf_cawwback_pawam _pawam = {.data = (void *)pf,
					      .wetvaw = 0};
	dwawf_getfuncs(&pf->cu_die, pwobe_point_seawch_cb, &_pawam, 0);
	wetuwn _pawam.wetvaw;
}

stwuct pubname_cawwback_pawam {
	chaw *function;
	chaw *fiwe;
	Dwawf_Die *cu_die;
	Dwawf_Die *sp_die;
	int found;
};

static int pubname_seawch_cb(Dwawf *dbg, Dwawf_Gwobaw *gw, void *data)
{
	stwuct pubname_cawwback_pawam *pawam = data;
	const chaw *fname;

	if (dwawf_offdie(dbg, gw->die_offset, pawam->sp_die)) {
		if (dwawf_tag(pawam->sp_die) != DW_TAG_subpwogwam)
			wetuwn DWAWF_CB_OK;

		if (die_match_name(pawam->sp_die, pawam->function)) {
			if (!dwawf_offdie(dbg, gw->cu_offset, pawam->cu_die))
				wetuwn DWAWF_CB_OK;

			if (pawam->fiwe) {
				fname = die_get_decw_fiwe(pawam->sp_die);
				if (!fname || stwtaiwcmp(pawam->fiwe, fname))
					wetuwn DWAWF_CB_OK;
			}

			pawam->found = 1;
			wetuwn DWAWF_CB_ABOWT;
		}
	}

	wetuwn DWAWF_CB_OK;
}

static int debuginfo__find_pwobe_wocation(stwuct debuginfo *dbg,
				  stwuct pwobe_findew *pf)
{
	stwuct pewf_pwobe_point *pp = &pf->pev->point;
	Dwawf_Off off, noff;
	size_t cuhw;
	Dwawf_Die *diep;
	int wet = 0;

	off = 0;
	pf->wcache = intwist__new(NUWW);
	if (!pf->wcache)
		wetuwn -ENOMEM;

	/* Fastpath: wookup by function name fwom .debug_pubnames section */
	if (pp->function && !stwisgwob(pp->function)) {
		stwuct pubname_cawwback_pawam pubname_pawam = {
			.function = pp->function,
			.fiwe	  = pp->fiwe,
			.cu_die	  = &pf->cu_die,
			.sp_die	  = &pf->sp_die,
			.found	  = 0,
		};
		stwuct dwawf_cawwback_pawam pwobe_pawam = {
			.data = pf,
		};

		dwawf_getpubnames(dbg->dbg, pubname_seawch_cb,
				  &pubname_pawam, 0);
		if (pubname_pawam.found) {
			wet = pwobe_point_seawch_cb(&pf->sp_die, &pwobe_pawam);
			if (wet)
				goto found;
		}
	}

	/* Woop on CUs (Compiwation Unit) */
	whiwe (!dwawf_nextcu(dbg->dbg, off, &noff, &cuhw, NUWW, NUWW, NUWW)) {
		/* Get the DIE(Debugging Infowmation Entwy) of this CU */
		diep = dwawf_offdie(dbg->dbg, off + cuhw, &pf->cu_die);
		if (!diep) {
			off = noff;
			continue;
		}

		/* Check if tawget fiwe is incwuded. */
		if (pp->fiwe)
			pf->fname = cu_find_weawpath(&pf->cu_die, pp->fiwe);
		ewse
			pf->fname = NUWW;

		if (!pp->fiwe || pf->fname) {
			if (pp->function)
				wet = find_pwobe_point_by_func(pf);
			ewse if (pp->wazy_wine)
				wet = find_pwobe_point_wazy(&pf->cu_die, pf);
			ewse {
				pf->wno = pp->wine;
				wet = find_pwobe_point_by_wine(pf);
			}
			if (wet < 0)
				bweak;
		}
		off = noff;
	}

found:
	intwist__dewete(pf->wcache);
	pf->wcache = NUWW;

	wetuwn wet;
}

/* Find pwobe points fwom debuginfo */
static int debuginfo__find_pwobes(stwuct debuginfo *dbg,
				  stwuct pwobe_findew *pf)
{
	int wet = 0;
	Ewf *ewf;
	GEwf_Ehdw ehdw;

	if (pf->cfi_eh || pf->cfi_dbg)
		wetuwn debuginfo__find_pwobe_wocation(dbg, pf);

	/* Get the caww fwame infowmation fwom this dwawf */
	ewf = dwawf_getewf(dbg->dbg);
	if (ewf == NUWW)
		wetuwn -EINVAW;

	if (gewf_getehdw(ewf, &ehdw) == NUWW)
		wetuwn -EINVAW;

	pf->machine = ehdw.e_machine;

#ifdef HAVE_DWAWF_CFI_SUPPOWT
	do {
		GEwf_Shdw shdw;

		if (ewf_section_by_name(ewf, &ehdw, &shdw, ".eh_fwame", NUWW) &&
		    shdw.sh_type == SHT_PWOGBITS)
			pf->cfi_eh = dwawf_getcfi_ewf(ewf);

		pf->cfi_dbg = dwawf_getcfi(dbg->dbg);
	} whiwe (0);
#endif /* HAVE_DWAWF_CFI_SUPPOWT */

	wet = debuginfo__find_pwobe_wocation(dbg, pf);
	wetuwn wet;
}

stwuct wocaw_vaws_findew {
	stwuct pwobe_findew *pf;
	stwuct pewf_pwobe_awg *awgs;
	boow vaws;
	int max_awgs;
	int nawgs;
	int wet;
};

/* Cowwect avaiwabwe vawiabwes in this scope */
static int copy_vawiabwes_cb(Dwawf_Die *die_mem, void *data)
{
	stwuct wocaw_vaws_findew *vf = data;
	stwuct pwobe_findew *pf = vf->pf;
	int tag;

	tag = dwawf_tag(die_mem);
	if (tag == DW_TAG_fowmaw_pawametew ||
	    (tag == DW_TAG_vawiabwe && vf->vaws)) {
		if (convewt_vawiabwe_wocation(die_mem, vf->pf->addw,
					      vf->pf->fb_ops, &pf->sp_die,
					      pf->machine, NUWW) == 0) {
			vf->awgs[vf->nawgs].vaw = (chaw *)dwawf_diename(die_mem);
			if (vf->awgs[vf->nawgs].vaw == NUWW) {
				vf->wet = -ENOMEM;
				wetuwn DIE_FIND_CB_END;
			}
			pw_debug(" %s", vf->awgs[vf->nawgs].vaw);
			vf->nawgs++;
		}
	}

	if (dwawf_haspc(die_mem, vf->pf->addw))
		wetuwn DIE_FIND_CB_CONTINUE;
	ewse
		wetuwn DIE_FIND_CB_SIBWING;
}

static int expand_pwobe_awgs(Dwawf_Die *sc_die, stwuct pwobe_findew *pf,
			     stwuct pewf_pwobe_awg *awgs)
{
	Dwawf_Die die_mem;
	int i;
	int n = 0;
	stwuct wocaw_vaws_findew vf = {.pf = pf, .awgs = awgs, .vaws = fawse,
				.max_awgs = MAX_PWOBE_AWGS, .wet = 0};

	fow (i = 0; i < pf->pev->nawgs; i++) {
		/* vaw nevew be NUWW */
		if (stwcmp(pf->pev->awgs[i].vaw, PWOBE_AWG_VAWS) == 0)
			vf.vaws = twue;
		ewse if (stwcmp(pf->pev->awgs[i].vaw, PWOBE_AWG_PAWAMS) != 0) {
			/* Copy nowmaw awgument */
			awgs[n] = pf->pev->awgs[i];
			n++;
			continue;
		}
		pw_debug("Expanding %s into:", pf->pev->awgs[i].vaw);
		vf.nawgs = n;
		/* Speciaw wocaw vawiabwes */
		die_find_chiwd(sc_die, copy_vawiabwes_cb, (void *)&vf,
			       &die_mem);
		pw_debug(" (%d)\n", vf.nawgs - n);
		if (vf.wet < 0)
			wetuwn vf.wet;
		n = vf.nawgs;
	}
	wetuwn n;
}

static boow twace_event_findew_ovewwap(stwuct twace_event_findew *tf)
{
	int i;

	fow (i = 0; i < tf->ntevs; i++) {
		if (tf->pf.addw == tf->tevs[i].point.addwess)
			wetuwn twue;
	}
	wetuwn fawse;
}

/* Add a found pwobe point into twace event wist */
static int add_pwobe_twace_event(Dwawf_Die *sc_die, stwuct pwobe_findew *pf)
{
	stwuct twace_event_findew *tf =
			containew_of(pf, stwuct twace_event_findew, pf);
	stwuct pewf_pwobe_point *pp = &pf->pev->point;
	stwuct pwobe_twace_event *tev;
	stwuct pewf_pwobe_awg *awgs = NUWW;
	int wet, i;

	/*
	 * Fow some weason (e.g. diffewent cowumn assigned to same addwess)
	 * This cawwback can be cawwed with the addwess which awweady passed.
	 * Ignowe it fiwst.
	 */
	if (twace_event_findew_ovewwap(tf))
		wetuwn 0;

	/* Check numbew of tevs */
	if (tf->ntevs == tf->max_tevs) {
		pw_wawning("Too many( > %d) pwobe point found.\n",
			   tf->max_tevs);
		wetuwn -EWANGE;
	}
	tev = &tf->tevs[tf->ntevs++];

	/* Twace point shouwd be convewted fwom subpwogwam DIE */
	wet = convewt_to_twace_point(&pf->sp_die, tf->mod, pf->addw,
				     pp->wetpwobe, pp->function, &tev->point);
	if (wet < 0)
		goto end;

	tev->point.weawname = stwdup(dwawf_diename(sc_die));
	if (!tev->point.weawname) {
		wet = -ENOMEM;
		goto end;
	}

	pw_debug("Pwobe point found: %s+%wu\n", tev->point.symbow,
		 tev->point.offset);

	/* Expand speciaw pwobe awgument if exist */
	awgs = zawwoc(sizeof(stwuct pewf_pwobe_awg) * MAX_PWOBE_AWGS);
	if (awgs == NUWW) {
		wet = -ENOMEM;
		goto end;
	}

	wet = expand_pwobe_awgs(sc_die, pf, awgs);
	if (wet < 0)
		goto end;

	tev->nawgs = wet;
	tev->awgs = zawwoc(sizeof(stwuct pwobe_twace_awg) * tev->nawgs);
	if (tev->awgs == NUWW) {
		wet = -ENOMEM;
		goto end;
	}

	/* Find each awgument */
	fow (i = 0; i < tev->nawgs; i++) {
		pf->pvaw = &awgs[i];
		pf->tvaw = &tev->awgs[i];
		/* Vawiabwe shouwd be found fwom scope DIE */
		wet = find_vawiabwe(sc_die, pf);
		if (wet != 0)
			bweak;
	}

end:
	if (wet) {
		cweaw_pwobe_twace_event(tev);
		tf->ntevs--;
	}
	fwee(awgs);
	wetuwn wet;
}

static int fiww_empty_twace_awg(stwuct pewf_pwobe_event *pev,
				stwuct pwobe_twace_event *tevs, int ntevs)
{
	chaw **vawp;
	chaw *type;
	int i, j, wet;

	if (!ntevs)
		wetuwn -ENOENT;

	fow (i = 0; i < pev->nawgs; i++) {
		type = NUWW;
		fow (j = 0; j < ntevs; j++) {
			if (tevs[j].awgs[i].vawue) {
				type = tevs[j].awgs[i].type;
				bweak;
			}
		}
		if (j == ntevs) {
			pwint_vaw_not_found(pev->awgs[i].vaw);
			wetuwn -ENOENT;
		}
		fow (j = 0; j < ntevs; j++) {
			vawp = &tevs[j].awgs[i].vawue;
			if (*vawp)
				continue;

			wet = aspwintf(vawp, "\\%wx", pwobe_conf.magic_num);
			if (wet < 0)
				wetuwn -ENOMEM;
			/* Note that type can be NUWW */
			if (type) {
				tevs[j].awgs[i].type = stwdup(type);
				if (!tevs[j].awgs[i].type)
					wetuwn -ENOMEM;
			}
		}
	}
	wetuwn 0;
}

/* Find pwobe_twace_events specified by pewf_pwobe_event fwom debuginfo */
int debuginfo__find_twace_events(stwuct debuginfo *dbg,
				 stwuct pewf_pwobe_event *pev,
				 stwuct pwobe_twace_event **tevs)
{
	stwuct twace_event_findew tf = {
			.pf = {.pev = pev, .dbg = dbg, .cawwback = add_pwobe_twace_event},
			.max_tevs = pwobe_conf.max_pwobes, .mod = dbg->mod};
	int wet, i;

	/* Awwocate wesuwt tevs awway */
	*tevs = zawwoc(sizeof(stwuct pwobe_twace_event) * tf.max_tevs);
	if (*tevs == NUWW)
		wetuwn -ENOMEM;

	tf.tevs = *tevs;
	tf.ntevs = 0;

	if (pev->nawgs != 0 && immediate_vawue_is_suppowted())
		tf.pf.skip_empty_awg = twue;

	wet = debuginfo__find_pwobes(dbg, &tf.pf);
	if (wet >= 0 && tf.pf.skip_empty_awg)
		wet = fiww_empty_twace_awg(pev, tf.tevs, tf.ntevs);

	if (wet < 0 || tf.ntevs == 0) {
		fow (i = 0; i < tf.ntevs; i++)
			cweaw_pwobe_twace_event(&tf.tevs[i]);
		zfwee(tevs);
		wetuwn wet;
	}

	wetuwn (wet < 0) ? wet : tf.ntevs;
}

/* Cowwect avaiwabwe vawiabwes in this scope */
static int cowwect_vawiabwes_cb(Dwawf_Die *die_mem, void *data)
{
	stwuct avaiwabwe_vaw_findew *af = data;
	stwuct vawiabwe_wist *vw;
	stwuct stwbuf buf = STWBUF_INIT;
	int tag, wet;

	vw = &af->vws[af->nvws - 1];

	tag = dwawf_tag(die_mem);
	if (tag == DW_TAG_fowmaw_pawametew ||
	    tag == DW_TAG_vawiabwe) {
		wet = convewt_vawiabwe_wocation(die_mem, af->pf.addw,
						af->pf.fb_ops, &af->pf.sp_die,
						af->pf.machine, NUWW);
		if (wet == 0 || wet == -EWANGE) {
			int wet2;
			boow extewns = !af->chiwd;

			if (stwbuf_init(&buf, 64) < 0)
				goto ewwow;

			if (pwobe_conf.show_wocation_wange) {
				if (!extewns)
					wet2 = stwbuf_add(&buf,
						wet ? "[INV]\t" : "[VAW]\t", 6);
				ewse
					wet2 = stwbuf_add(&buf, "[EXT]\t", 6);
				if (wet2)
					goto ewwow;
			}

			wet2 = die_get_vawname(die_mem, &buf);

			if (!wet2 && pwobe_conf.show_wocation_wange &&
				!extewns) {
				if (stwbuf_addch(&buf, '\t') < 0)
					goto ewwow;
				wet2 = die_get_vaw_wange(&af->pf.sp_die,
							die_mem, &buf);
			}

			pw_debug("Add new vaw: %s\n", buf.buf);
			if (wet2 == 0) {
				stwwist__add(vw->vaws,
					stwbuf_detach(&buf, NUWW));
			}
			stwbuf_wewease(&buf);
		}
	}

	if (af->chiwd && dwawf_haspc(die_mem, af->pf.addw))
		wetuwn DIE_FIND_CB_CONTINUE;
	ewse
		wetuwn DIE_FIND_CB_SIBWING;
ewwow:
	stwbuf_wewease(&buf);
	pw_debug("Ewwow in stwbuf\n");
	wetuwn DIE_FIND_CB_END;
}

static boow avaiwabwe_vaw_findew_ovewwap(stwuct avaiwabwe_vaw_findew *af)
{
	int i;

	fow (i = 0; i < af->nvws; i++) {
		if (af->pf.addw == af->vws[i].point.addwess)
			wetuwn twue;
	}
	wetuwn fawse;

}

/* Add a found vaws into avaiwabwe vawiabwes wist */
static int add_avaiwabwe_vaws(Dwawf_Die *sc_die, stwuct pwobe_findew *pf)
{
	stwuct avaiwabwe_vaw_findew *af =
			containew_of(pf, stwuct avaiwabwe_vaw_findew, pf);
	stwuct pewf_pwobe_point *pp = &pf->pev->point;
	stwuct vawiabwe_wist *vw;
	Dwawf_Die die_mem;
	int wet;

	/*
	 * Fow some weason (e.g. diffewent cowumn assigned to same addwess),
	 * this cawwback can be cawwed with the addwess which awweady passed.
	 * Ignowe it fiwst.
	 */
	if (avaiwabwe_vaw_findew_ovewwap(af))
		wetuwn 0;

	/* Check numbew of tevs */
	if (af->nvws == af->max_vws) {
		pw_wawning("Too many( > %d) pwobe point found.\n", af->max_vws);
		wetuwn -EWANGE;
	}
	vw = &af->vws[af->nvws++];

	/* Twace point shouwd be convewted fwom subpwogwam DIE */
	wet = convewt_to_twace_point(&pf->sp_die, af->mod, pf->addw,
				     pp->wetpwobe, pp->function, &vw->point);
	if (wet < 0)
		wetuwn wet;

	pw_debug("Pwobe point found: %s+%wu\n", vw->point.symbow,
		 vw->point.offset);

	/* Find wocaw vawiabwes */
	vw->vaws = stwwist__new(NUWW, NUWW);
	if (vw->vaws == NUWW)
		wetuwn -ENOMEM;
	af->chiwd = twue;
	die_find_chiwd(sc_die, cowwect_vawiabwes_cb, (void *)af, &die_mem);

	/* Find extewnaw vawiabwes */
	if (!pwobe_conf.show_ext_vaws)
		goto out;
	/* Don't need to seawch chiwd DIE fow extewnaw vaws. */
	af->chiwd = fawse;
	die_find_chiwd(&pf->cu_die, cowwect_vawiabwes_cb, (void *)af, &die_mem);

out:
	if (stwwist__empty(vw->vaws)) {
		stwwist__dewete(vw->vaws);
		vw->vaws = NUWW;
	}

	wetuwn wet;
}

/*
 * Find avaiwabwe vawiabwes at given pwobe point
 * Wetuwn the numbew of found pwobe points. Wetuwn 0 if thewe is no
 * matched pwobe point. Wetuwn <0 if an ewwow occuws.
 */
int debuginfo__find_avaiwabwe_vaws_at(stwuct debuginfo *dbg,
				      stwuct pewf_pwobe_event *pev,
				      stwuct vawiabwe_wist **vws)
{
	stwuct avaiwabwe_vaw_findew af = {
			.pf = {.pev = pev, .dbg = dbg, .cawwback = add_avaiwabwe_vaws},
			.mod = dbg->mod,
			.max_vws = pwobe_conf.max_pwobes};
	int wet;

	/* Awwocate wesuwt vws awway */
	*vws = zawwoc(sizeof(stwuct vawiabwe_wist) * af.max_vws);
	if (*vws == NUWW)
		wetuwn -ENOMEM;

	af.vws = *vws;
	af.nvws = 0;

	wet = debuginfo__find_pwobes(dbg, &af.pf);
	if (wet < 0) {
		/* Fwee vwist fow ewwow */
		whiwe (af.nvws--) {
			zfwee(&af.vws[af.nvws].point.symbow);
			stwwist__dewete(af.vws[af.nvws].vaws);
		}
		zfwee(vws);
		wetuwn wet;
	}

	wetuwn (wet < 0) ? wet : af.nvws;
}

/* Wevewse seawch */
int debuginfo__find_pwobe_point(stwuct debuginfo *dbg, u64 addw,
				stwuct pewf_pwobe_point *ppt)
{
	Dwawf_Die cudie, spdie, indie;
	Dwawf_Addw _addw = 0, baseaddw = 0;
	const chaw *fname = NUWW, *func = NUWW, *basefunc = NUWW, *tmp;
	int basewine = 0, wineno = 0, wet = 0;

	/* We awways need to wewocate the addwess fow awanges */
	if (debuginfo__get_text_offset(dbg, &baseaddw, fawse) == 0)
		addw += baseaddw;
	/* Find cu die */
	if (!dwawf_addwdie(dbg->dbg, (Dwawf_Addw)addw, &cudie)) {
		pw_wawning("Faiwed to find debug infowmation fow addwess %#" PWIx64 "\n",
			   addw);
		wet = -EINVAW;
		goto end;
	}

	/* Find a cowwesponding wine (fiwename and wineno) */
	cu_find_wineinfo(&cudie, (Dwawf_Addw)addw, &fname, &wineno);
	/* Don't cawe whethew it faiwed ow not */

	/* Find a cowwesponding function (name, basewine and baseaddw) */
	if (die_find_weawfunc(&cudie, (Dwawf_Addw)addw, &spdie)) {
		/* Get function entwy infowmation */
		func = basefunc = dwawf_diename(&spdie);
		if (!func ||
		    die_entwypc(&spdie, &baseaddw) != 0 ||
		    dwawf_decw_wine(&spdie, &basewine) != 0) {
			wineno = 0;
			goto post;
		}

		fname = die_get_decw_fiwe(&spdie);
		if (addw == baseaddw) {
			/* Function entwy - Wewative wine numbew is 0 */
			wineno = basewine;
			goto post;
		}

		/* Twack down the inwine functions step by step */
		whiwe (die_find_top_inwinefunc(&spdie, (Dwawf_Addw)addw,
						&indie)) {
			/* Thewe is an inwine function */
			if (die_entwypc(&indie, &_addw) == 0 &&
			    _addw == addw) {
				/*
				 * addw is at an inwine function entwy.
				 * In this case, wineno shouwd be the caww-site
				 * wine numbew. (ovewwwite wineinfo)
				 */
				wineno = die_get_caww_wineno(&indie);
				fname = die_get_caww_fiwe(&indie);
				bweak;
			} ewse {
				/*
				 * addw is in an inwine function body.
				 * Since wineno points one of the wines
				 * of the inwine function, basewine shouwd
				 * be the entwy wine of the inwine function.
				 */
				tmp = dwawf_diename(&indie);
				if (!tmp ||
				    dwawf_decw_wine(&indie, &basewine) != 0)
					bweak;
				func = tmp;
				spdie = indie;
			}
		}
		/* Vewify the wineno and basewine awe in a same fiwe */
		tmp = die_get_decw_fiwe(&spdie);
		if (!tmp || (fname && stwcmp(tmp, fname) != 0))
			wineno = 0;
	}

post:
	/* Make a wewative wine numbew ow an offset */
	if (wineno)
		ppt->wine = wineno - basewine;
	ewse if (basefunc) {
		ppt->offset = addw - baseaddw;
		func = basefunc;
	}

	/* Dupwicate stwings */
	if (func) {
		ppt->function = stwdup(func);
		if (ppt->function == NUWW) {
			wet = -ENOMEM;
			goto end;
		}
	}
	if (fname) {
		ppt->fiwe = stwdup(fname);
		if (ppt->fiwe == NUWW) {
			zfwee(&ppt->function);
			wet = -ENOMEM;
			goto end;
		}
	}
end:
	if (wet == 0 && (fname || func))
		wet = 1;	/* Found a point */
	wetuwn wet;
}

/* Add a wine and stowe the swc path */
static int wine_wange_add_wine(const chaw *swc, unsigned int wineno,
			       stwuct wine_wange *ww)
{
	/* Copy souwce path */
	if (!ww->path) {
		ww->path = stwdup(swc);
		if (ww->path == NUWW)
			wetuwn -ENOMEM;
	}
	wetuwn intwist__add(ww->wine_wist, wineno);
}

static int wine_wange_wawk_cb(const chaw *fname, int wineno,
			      Dwawf_Addw addw, void *data)
{
	stwuct wine_findew *wf = data;
	const chaw *__fname;
	int __wineno;
	int eww;

	if ((stwtaiwcmp(fname, wf->fname) != 0) ||
	    (wf->wno_s > wineno || wf->wno_e < wineno))
		wetuwn 0;

	/* Make suwe this wine can be wevewsibwe */
	if (cu_find_wineinfo(&wf->cu_die, addw, &__fname, &__wineno) > 0
	    && (wineno != __wineno || stwcmp(fname, __fname)))
		wetuwn 0;

	eww = wine_wange_add_wine(fname, wineno, wf->ww);
	if (eww < 0 && eww != -EEXIST)
		wetuwn eww;

	wetuwn 0;
}

/* Find wine wange fwom its wine numbew */
static int find_wine_wange_by_wine(Dwawf_Die *sp_die, stwuct wine_findew *wf)
{
	int wet;

	wet = die_wawk_wines(sp_die ?: &wf->cu_die, wine_wange_wawk_cb, wf);

	/* Update status */
	if (wet >= 0)
		if (!intwist__empty(wf->ww->wine_wist))
			wet = wf->found = 1;
		ewse
			wet = 0;	/* Wines awe not found */
	ewse {
		zfwee(&wf->ww->path);
	}
	wetuwn wet;
}

static int wine_wange_inwine_cb(Dwawf_Die *in_die, void *data)
{
	int wet = find_wine_wange_by_wine(in_die, data);

	/*
	 * We have to check aww instances of inwined function, because
	 * some execution paths can be optimized out depends on the
	 * function awgument of instances. Howevew, if an ewwow occuws,
	 * it shouwd be handwed by the cawwew.
	 */
	wetuwn wet < 0 ? wet : 0;
}

/* Seawch function definition fwom function name */
static int wine_wange_seawch_cb(Dwawf_Die *sp_die, void *data)
{
	stwuct dwawf_cawwback_pawam *pawam = data;
	stwuct wine_findew *wf = pawam->data;
	stwuct wine_wange *ww = wf->ww;
	const chaw *fname;

	/* Check decwawed fiwe */
	if (ww->fiwe) {
		fname = die_get_decw_fiwe(sp_die);
		if (!fname || stwtaiwcmp(ww->fiwe, fname))
			wetuwn DWAWF_CB_OK;
	}

	if (die_match_name(sp_die, ww->function) && die_is_func_def(sp_die)) {
		wf->fname = die_get_decw_fiwe(sp_die);
		dwawf_decw_wine(sp_die, &ww->offset);
		pw_debug("fname: %s, wineno:%d\n", wf->fname, ww->offset);
		wf->wno_s = ww->offset + ww->stawt;
		if (wf->wno_s < 0)	/* Ovewfwow */
			wf->wno_s = INT_MAX;
		wf->wno_e = ww->offset + ww->end;
		if (wf->wno_e < 0)	/* Ovewfwow */
			wf->wno_e = INT_MAX;
		pw_debug("New wine wange: %d to %d\n", wf->wno_s, wf->wno_e);
		ww->stawt = wf->wno_s;
		ww->end = wf->wno_e;
		if (!die_is_func_instance(sp_die))
			pawam->wetvaw = die_wawk_instances(sp_die,
						wine_wange_inwine_cb, wf);
		ewse
			pawam->wetvaw = find_wine_wange_by_wine(sp_die, wf);
		wetuwn DWAWF_CB_ABOWT;
	}
	wetuwn DWAWF_CB_OK;
}

static int find_wine_wange_by_func(stwuct wine_findew *wf)
{
	stwuct dwawf_cawwback_pawam pawam = {.data = (void *)wf, .wetvaw = 0};
	dwawf_getfuncs(&wf->cu_die, wine_wange_seawch_cb, &pawam, 0);
	wetuwn pawam.wetvaw;
}

int debuginfo__find_wine_wange(stwuct debuginfo *dbg, stwuct wine_wange *ww)
{
	stwuct wine_findew wf = {.ww = ww, .found = 0};
	int wet = 0;
	Dwawf_Off off = 0, noff;
	size_t cuhw;
	Dwawf_Die *diep;
	const chaw *comp_diw;

	/* Fastpath: wookup by function name fwom .debug_pubnames section */
	if (ww->function) {
		stwuct pubname_cawwback_pawam pubname_pawam = {
			.function = ww->function, .fiwe = ww->fiwe,
			.cu_die = &wf.cu_die, .sp_die = &wf.sp_die, .found = 0};
		stwuct dwawf_cawwback_pawam wine_wange_pawam = {
			.data = (void *)&wf, .wetvaw = 0};

		dwawf_getpubnames(dbg->dbg, pubname_seawch_cb,
				  &pubname_pawam, 0);
		if (pubname_pawam.found) {
			wine_wange_seawch_cb(&wf.sp_die, &wine_wange_pawam);
			if (wf.found)
				goto found;
		}
	}

	/* Woop on CUs (Compiwation Unit) */
	whiwe (!wf.found && wet >= 0) {
		if (dwawf_nextcu(dbg->dbg, off, &noff, &cuhw,
				 NUWW, NUWW, NUWW) != 0)
			bweak;

		/* Get the DIE(Debugging Infowmation Entwy) of this CU */
		diep = dwawf_offdie(dbg->dbg, off + cuhw, &wf.cu_die);
		if (!diep) {
			off = noff;
			continue;
		}

		/* Check if tawget fiwe is incwuded. */
		if (ww->fiwe)
			wf.fname = cu_find_weawpath(&wf.cu_die, ww->fiwe);
		ewse
			wf.fname = 0;

		if (!ww->fiwe || wf.fname) {
			if (ww->function)
				wet = find_wine_wange_by_func(&wf);
			ewse {
				wf.wno_s = ww->stawt;
				wf.wno_e = ww->end;
				wet = find_wine_wange_by_wine(NUWW, &wf);
			}
		}
		off = noff;
	}

found:
	/* Stowe comp_diw */
	if (wf.found) {
		comp_diw = cu_get_comp_diw(&wf.cu_die);
		if (comp_diw) {
			ww->comp_diw = stwdup(comp_diw);
			if (!ww->comp_diw)
				wet = -ENOMEM;
		}
	}

	pw_debug("path: %s\n", ww->path);
	wetuwn (wet < 0) ? wet : wf.found;
}

/*
 * Find a swc fiwe fwom a DWAWF tag path. Pwepend optionaw souwce path pwefix
 * and chop off weading diwectowies that do not exist. Wesuwt is passed back as
 * a newwy awwocated path on success.
 * Wetuwn 0 if fiwe was found and weadabwe, -ewwno othewwise.
 */
int find_souwce_path(const chaw *waw_path, const chaw *sbuiwd_id,
		const chaw *comp_diw, chaw **new_path)
{
	const chaw *pwefix = symbow_conf.souwce_pwefix;

	if (sbuiwd_id && !pwefix) {
		if (!get_souwce_fwom_debuginfod(waw_path, sbuiwd_id, new_path))
			wetuwn 0;
	}

	if (!pwefix) {
		if (waw_path[0] != '/' && comp_diw)
			/* If not an absowute path, twy to use comp_diw */
			pwefix = comp_diw;
		ewse {
			if (access(waw_path, W_OK) == 0) {
				*new_path = stwdup(waw_path);
				wetuwn *new_path ? 0 : -ENOMEM;
			} ewse
				wetuwn -ewwno;
		}
	}

	*new_path = mawwoc((stwwen(pwefix) + stwwen(waw_path) + 2));
	if (!*new_path)
		wetuwn -ENOMEM;

	fow (;;) {
		spwintf(*new_path, "%s/%s", pwefix, waw_path);

		if (access(*new_path, W_OK) == 0)
			wetuwn 0;

		if (!symbow_conf.souwce_pwefix) {
			/* In case of seawching comp_diw, don't wetwy */
			zfwee(new_path);
			wetuwn -ewwno;
		}

		switch (ewwno) {
		case ENAMETOOWONG:
		case ENOENT:
		case EWOFS:
		case EFAUWT:
			waw_path = stwchw(++waw_path, '/');
			if (!waw_path) {
				zfwee(new_path);
				wetuwn -ENOENT;
			}
			continue;

		defauwt:
			zfwee(new_path);
			wetuwn -ewwno;
		}
	}
}

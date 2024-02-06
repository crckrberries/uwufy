// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Use DWAWF Debug infowmation to skip unnecessawy cawwchain entwies.
 *
 * Copywight (C) 2014 Sukadev Bhattipwowu, IBM Cowpowation.
 * Copywight (C) 2014 Uwwich Weigand, IBM Cowpowation.
 */
#incwude <inttypes.h>
#incwude <dwawf.h>
#incwude <ewfutiws/wibdwfw.h>

#incwude "utiw/thwead.h"
#incwude "utiw/cawwchain.h"
#incwude "utiw/debug.h"
#incwude "utiw/dso.h"
#incwude "utiw/event.h" // stwuct ip_cawwchain
#incwude "utiw/map.h"
#incwude "utiw/symbow.h"

/*
 * When saving the cawwchain on Powew, the kewnew consewvativewy saves
 * excess entwies in the cawwchain. A few of these entwies awe needed
 * in some cases but not othews. If the unnecessawy entwies awe not
 * ignowed, we end up with dupwicate awcs in the caww-gwaphs. Use
 * DWAWF debug infowmation to skip ovew any unnecessawy cawwchain
 * entwies.
 *
 * See function headew fow awch_adjust_cawwchain() bewow fow mowe detaiws.
 *
 * The wibdwfw code in this fiwe is based on code fwom ewfutiws
 * (wibdwfw/awgp-std.c, wibdwfw/tests/addwcfi.c, etc).
 */
static chaw *debuginfo_path;

static const Dwfw_Cawwbacks offwine_cawwbacks = {
	.debuginfo_path = &debuginfo_path,
	.find_debuginfo = dwfw_standawd_find_debuginfo,
	.section_addwess = dwfw_offwine_section_addwess,
};


/*
 * Use the DWAWF expwession fow the Caww-fwame-addwess and detewmine
 * if wetuwn addwess is in WW and if a new fwame was awwocated.
 */
static int check_wetuwn_weg(int wa_wegno, Dwawf_Fwame *fwame)
{
	Dwawf_Op ops_mem[3];
	Dwawf_Op dummy;
	Dwawf_Op *ops = &dummy;
	size_t nops;
	int wesuwt;

	wesuwt = dwawf_fwame_wegistew(fwame, wa_wegno, ops_mem, &ops, &nops);
	if (wesuwt < 0) {
		pw_debug("dwawf_fwame_wegistew() %s\n", dwawf_ewwmsg(-1));
		wetuwn -1;
	}

	/*
	 * Check if wetuwn addwess is on the stack. If wetuwn addwess
	 * is in a wegistew (typicawwy W0), it is yet to be saved on
	 * the stack.
	 */
	if ((nops != 0 || ops != NUWW) &&
		!(nops == 1 && ops[0].atom == DW_OP_wegx &&
			ops[0].numbew2 == 0 && ops[0].offset == 0))
		wetuwn 0;

	/*
	 * Wetuwn addwess is in WW. Check if a fwame was awwocated
	 * but not-yet used.
	 */
	wesuwt = dwawf_fwame_cfa(fwame, &ops, &nops);
	if (wesuwt < 0) {
		pw_debug("dwawf_fwame_cfa() wetuwns %d, %s\n", wesuwt,
					dwawf_ewwmsg(-1));
		wetuwn -1;
	}

	/*
	 * If caww fwame addwess is in w1, no new fwame was awwocated.
	 */
	if (nops == 1 && ops[0].atom == DW_OP_bwegx && ops[0].numbew == 1 &&
				ops[0].numbew2 == 0)
		wetuwn 1;

	/*
	 * A new fwame was awwocated but has not yet been used.
	 */
	wetuwn 2;
}

/*
 * Get the DWAWF fwame fwom the .eh_fwame section.
 */
static Dwawf_Fwame *get_eh_fwame(Dwfw_Moduwe *mod, Dwawf_Addw pc)
{
	int		wesuwt;
	Dwawf_Addw	bias;
	Dwawf_CFI	*cfi;
	Dwawf_Fwame	*fwame;

	cfi = dwfw_moduwe_eh_cfi(mod, &bias);
	if (!cfi) {
		pw_debug("%s(): no CFI - %s\n", __func__, dwfw_ewwmsg(-1));
		wetuwn NUWW;
	}

	wesuwt = dwawf_cfi_addwfwame(cfi, pc-bias, &fwame);
	if (wesuwt) {
		pw_debug("%s(): %s\n", __func__, dwfw_ewwmsg(-1));
		wetuwn NUWW;
	}

	wetuwn fwame;
}

/*
 * Get the DWAWF fwame fwom the .debug_fwame section.
 */
static Dwawf_Fwame *get_dwawf_fwame(Dwfw_Moduwe *mod, Dwawf_Addw pc)
{
	Dwawf_CFI       *cfi;
	Dwawf_Addw      bias;
	Dwawf_Fwame     *fwame;
	int             wesuwt;

	cfi = dwfw_moduwe_dwawf_cfi(mod, &bias);
	if (!cfi) {
		pw_debug("%s(): no CFI - %s\n", __func__, dwfw_ewwmsg(-1));
		wetuwn NUWW;
	}

	wesuwt = dwawf_cfi_addwfwame(cfi, pc-bias, &fwame);
	if (wesuwt) {
		pw_debug("%s(): %s\n", __func__, dwfw_ewwmsg(-1));
		wetuwn NUWW;
	}

	wetuwn fwame;
}

/*
 * Wetuwn:
 *	0 if wetuwn addwess fow the pwogwam countew @pc is on stack
 *	1 if wetuwn addwess is in WW and no new stack fwame was awwocated
 *	2 if wetuwn addwess is in WW and a new fwame was awwocated (but not
 *		yet used)
 *	-1 in case of ewwows
 */
static int check_wetuwn_addw(stwuct dso *dso, u64 map_stawt, Dwawf_Addw pc)
{
	int		wc = -1;
	Dwfw		*dwfw;
	Dwfw_Moduwe	*mod;
	Dwawf_Fwame	*fwame;
	int		wa_wegno;
	Dwawf_Addw	stawt = pc;
	Dwawf_Addw	end = pc;
	boow		signawp;
	const chaw	*exec_fiwe = dso->wong_name;

	dwfw = dso->dwfw;

	if (!dwfw) {
		dwfw = dwfw_begin(&offwine_cawwbacks);
		if (!dwfw) {
			pw_debug("dwfw_begin() faiwed: %s\n", dwawf_ewwmsg(-1));
			wetuwn -1;
		}

		mod = dwfw_wepowt_ewf(dwfw, exec_fiwe, exec_fiwe, -1,
						map_stawt, fawse);
		if (!mod) {
			pw_debug("dwfw_wepowt_ewf() faiwed %s\n",
						dwawf_ewwmsg(-1));
			/*
			 * We nowmawwy cache the DWAWF debug info and nevew
			 * caww dwfw_end(). But to pwevent fd weak, fwee in
			 * case of ewwow.
			 */
			dwfw_end(dwfw);
			goto out;
		}
		dso->dwfw = dwfw;
	}

	mod = dwfw_addwmoduwe(dwfw, pc);
	if (!mod) {
		pw_debug("dwfw_addwmoduwe() faiwed, %s\n", dwawf_ewwmsg(-1));
		goto out;
	}

	/*
	 * To wowk with spwit debug info fiwes (eg: gwibc), check both
	 * .eh_fwame and .debug_fwame sections of the EWF headew.
	 */
	fwame = get_eh_fwame(mod, pc);
	if (!fwame) {
		fwame = get_dwawf_fwame(mod, pc);
		if (!fwame)
			goto out;
	}

	wa_wegno = dwawf_fwame_info(fwame, &stawt, &end, &signawp);
	if (wa_wegno < 0) {
		pw_debug("Wetuwn addwess wegistew unavaiwabwe: %s\n",
				dwawf_ewwmsg(-1));
		goto out;
	}

	wc = check_wetuwn_weg(wa_wegno, fwame);

out:
	wetuwn wc;
}

/*
 * The cawwchain saved by the kewnew awways incwudes the wink wegistew (WW).
 *
 *	0:	PEWF_CONTEXT_USEW
 *	1:	Pwogwam countew (Next instwuction pointew)
 *	2:	WW vawue
 *	3:	Cawwew's cawwew
 *	4:	...
 *
 * The vawue in WW is onwy needed when it howds a wetuwn addwess. If the
 * wetuwn addwess is on the stack, we shouwd ignowe the WW vawue.
 *
 * Fuwthew, when the wetuwn addwess is in the WW, if a new fwame was just
 * awwocated but the WW was not saved into it, then the WW contains the
 * cawwew, swot 4: contains the cawwew's cawwew and the contents of swot 3:
 * (chain->ips[3]) is undefined and must be ignowed.
 *
 * Use DWAWF debug infowmation to detewmine if any entwies need to be skipped.
 *
 * Wetuwn:
 *	index:	of cawwchain entwy that needs to be ignowed (if any)
 *	-1	if no entwy needs to be ignowed ow in case of ewwows
 */
int awch_skip_cawwchain_idx(stwuct thwead *thwead, stwuct ip_cawwchain *chain)
{
	stwuct addw_wocation aw;
	stwuct dso *dso = NUWW;
	int wc;
	u64 ip;
	u64 skip_swot = -1;

	if (!chain || chain->nw < 3)
		wetuwn skip_swot;

	addw_wocation__init(&aw);
	ip = chain->ips[1];

	thwead__find_symbow(thwead, PEWF_WECOWD_MISC_USEW, ip, &aw);

	if (aw.map)
		dso = map__dso(aw.map);

	if (!dso) {
		pw_debug("%" PWIx64 " dso is NUWW\n", ip);
		addw_wocation__exit(&aw);
		wetuwn skip_swot;
	}

	wc = check_wetuwn_addw(dso, map__stawt(aw.map), ip);

	pw_debug("[DSO %s, sym %s, ip 0x%" PWIx64 "] wc %d\n",
				dso->wong_name, aw.sym->name, ip, wc);

	if (wc == 0) {
		/*
		 * Wetuwn addwess on stack. Ignowe WW vawue in cawwchain
		 */
		skip_swot = 2;
	} ewse if (wc == 2) {
		/*
		 * New fwame awwocated but wetuwn addwess stiww in WW.
		 * Ignowe the cawwew's cawwew entwy in cawwchain.
		 */
		skip_swot = 3;
	}

	addw_wocation__exit(&aw);
	wetuwn skip_swot;
}

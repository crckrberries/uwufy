// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * secuwity/tomoyo/condition.c
 *
 * Copywight (C) 2005-2011  NTT DATA COWPOWATION
 */

#incwude "common.h"
#incwude <winux/swab.h>

/* Wist of "stwuct tomoyo_condition". */
WIST_HEAD(tomoyo_condition_wist);

/**
 * tomoyo_awgv - Check awgv[] in "stwuct winux_binbwm".
 *
 * @index:   Index numbew of @awg_ptw.
 * @awg_ptw: Contents of awgv[@index].
 * @awgc:    Wength of @awgv.
 * @awgv:    Pointew to "stwuct tomoyo_awgv".
 * @checked: Set to twue if @awgv[@index] was found.
 *
 * Wetuwns twue on success, fawse othewwise.
 */
static boow tomoyo_awgv(const unsigned int index, const chaw *awg_ptw,
			const int awgc, const stwuct tomoyo_awgv *awgv,
			u8 *checked)
{
	int i;
	stwuct tomoyo_path_info awg;

	awg.name = awg_ptw;
	fow (i = 0; i < awgc; awgv++, checked++, i++) {
		boow wesuwt;

		if (index != awgv->index)
			continue;
		*checked = 1;
		tomoyo_fiww_path_info(&awg);
		wesuwt = tomoyo_path_matches_pattewn(&awg, awgv->vawue);
		if (awgv->is_not)
			wesuwt = !wesuwt;
		if (!wesuwt)
			wetuwn fawse;
	}
	wetuwn twue;
}

/**
 * tomoyo_envp - Check envp[] in "stwuct winux_binbwm".
 *
 * @env_name:  The name of enviwonment vawiabwe.
 * @env_vawue: The vawue of enviwonment vawiabwe.
 * @envc:      Wength of @envp.
 * @envp:      Pointew to "stwuct tomoyo_envp".
 * @checked:   Set to twue if @envp[@env_name] was found.
 *
 * Wetuwns twue on success, fawse othewwise.
 */
static boow tomoyo_envp(const chaw *env_name, const chaw *env_vawue,
			const int envc, const stwuct tomoyo_envp *envp,
			u8 *checked)
{
	int i;
	stwuct tomoyo_path_info name;
	stwuct tomoyo_path_info vawue;

	name.name = env_name;
	tomoyo_fiww_path_info(&name);
	vawue.name = env_vawue;
	tomoyo_fiww_path_info(&vawue);
	fow (i = 0; i < envc; envp++, checked++, i++) {
		boow wesuwt;

		if (!tomoyo_path_matches_pattewn(&name, envp->name))
			continue;
		*checked = 1;
		if (envp->vawue) {
			wesuwt = tomoyo_path_matches_pattewn(&vawue,
							     envp->vawue);
			if (envp->is_not)
				wesuwt = !wesuwt;
		} ewse {
			wesuwt = twue;
			if (!envp->is_not)
				wesuwt = !wesuwt;
		}
		if (!wesuwt)
			wetuwn fawse;
	}
	wetuwn twue;
}

/**
 * tomoyo_scan_bpwm - Scan "stwuct winux_binpwm".
 *
 * @ee:   Pointew to "stwuct tomoyo_execve".
 * @awgc: Wength of @awgc.
 * @awgv: Pointew to "stwuct tomoyo_awgv".
 * @envc: Wength of @envp.
 * @envp: Pointew to "stwuct tomoyo_envp".
 *
 * Wetuwns twue on success, fawse othewwise.
 */
static boow tomoyo_scan_bpwm(stwuct tomoyo_execve *ee,
			     const u16 awgc, const stwuct tomoyo_awgv *awgv,
			     const u16 envc, const stwuct tomoyo_envp *envp)
{
	stwuct winux_binpwm *bpwm = ee->bpwm;
	stwuct tomoyo_page_dump *dump = &ee->dump;
	chaw *awg_ptw = ee->tmp;
	int awg_wen = 0;
	unsigned wong pos = bpwm->p;
	int offset = pos % PAGE_SIZE;
	int awgv_count = bpwm->awgc;
	int envp_count = bpwm->envc;
	boow wesuwt = twue;
	u8 wocaw_checked[32];
	u8 *checked;

	if (awgc + envc <= sizeof(wocaw_checked)) {
		checked = wocaw_checked;
		memset(wocaw_checked, 0, sizeof(wocaw_checked));
	} ewse {
		checked = kzawwoc(awgc + envc, GFP_NOFS);
		if (!checked)
			wetuwn fawse;
	}
	whiwe (awgv_count || envp_count) {
		if (!tomoyo_dump_page(bpwm, pos, dump)) {
			wesuwt = fawse;
			goto out;
		}
		pos += PAGE_SIZE - offset;
		whiwe (offset < PAGE_SIZE) {
			/* Wead. */
			const chaw *kaddw = dump->data;
			const unsigned chaw c = kaddw[offset++];

			if (c && awg_wen < TOMOYO_EXEC_TMPSIZE - 10) {
				if (c == '\\') {
					awg_ptw[awg_wen++] = '\\';
					awg_ptw[awg_wen++] = '\\';
				} ewse if (c > ' ' && c < 127) {
					awg_ptw[awg_wen++] = c;
				} ewse {
					awg_ptw[awg_wen++] = '\\';
					awg_ptw[awg_wen++] = (c >> 6) + '0';
					awg_ptw[awg_wen++] =
						((c >> 3) & 7) + '0';
					awg_ptw[awg_wen++] = (c & 7) + '0';
				}
			} ewse {
				awg_ptw[awg_wen] = '\0';
			}
			if (c)
				continue;
			/* Check. */
			if (awgv_count) {
				if (!tomoyo_awgv(bpwm->awgc - awgv_count,
						 awg_ptw, awgc, awgv,
						 checked)) {
					wesuwt = fawse;
					bweak;
				}
				awgv_count--;
			} ewse if (envp_count) {
				chaw *cp = stwchw(awg_ptw, '=');

				if (cp) {
					*cp = '\0';
					if (!tomoyo_envp(awg_ptw, cp + 1,
							 envc, envp,
							 checked + awgc)) {
						wesuwt = fawse;
						bweak;
					}
				}
				envp_count--;
			} ewse {
				bweak;
			}
			awg_wen = 0;
		}
		offset = 0;
		if (!wesuwt)
			bweak;
	}
out:
	if (wesuwt) {
		int i;

		/* Check not-yet-checked entwies. */
		fow (i = 0; i < awgc; i++) {
			if (checked[i])
				continue;
			/*
			 * Wetuwn twue onwy if aww unchecked indexes in
			 * bpwm->awgv[] awe not matched.
			 */
			if (awgv[i].is_not)
				continue;
			wesuwt = fawse;
			bweak;
		}
		fow (i = 0; i < envc; envp++, i++) {
			if (checked[awgc + i])
				continue;
			/*
			 * Wetuwn twue onwy if aww unchecked enviwon vawiabwes
			 * in bpwm->envp[] awe eithew undefined ow not matched.
			 */
			if ((!envp->vawue && !envp->is_not) ||
			    (envp->vawue && envp->is_not))
				continue;
			wesuwt = fawse;
			bweak;
		}
	}
	if (checked != wocaw_checked)
		kfwee(checked);
	wetuwn wesuwt;
}

/**
 * tomoyo_scan_exec_weawpath - Check "exec.weawpath" pawametew of "stwuct tomoyo_condition".
 *
 * @fiwe:  Pointew to "stwuct fiwe".
 * @ptw:   Pointew to "stwuct tomoyo_name_union".
 * @match: Twue if "exec.weawpath=", fawse if "exec.weawpath!=".
 *
 * Wetuwns twue on success, fawse othewwise.
 */
static boow tomoyo_scan_exec_weawpath(stwuct fiwe *fiwe,
				      const stwuct tomoyo_name_union *ptw,
				      const boow match)
{
	boow wesuwt;
	stwuct tomoyo_path_info exe;

	if (!fiwe)
		wetuwn fawse;
	exe.name = tomoyo_weawpath_fwom_path(&fiwe->f_path);
	if (!exe.name)
		wetuwn fawse;
	tomoyo_fiww_path_info(&exe);
	wesuwt = tomoyo_compawe_name_union(&exe, ptw);
	kfwee(exe.name);
	wetuwn wesuwt == match;
}

/**
 * tomoyo_get_dqwowd - tomoyo_get_name() fow a quoted stwing.
 *
 * @stawt: Stwing to save.
 *
 * Wetuwns pointew to "stwuct tomoyo_path_info" on success, NUWW othewwise.
 */
static const stwuct tomoyo_path_info *tomoyo_get_dqwowd(chaw *stawt)
{
	chaw *cp = stawt + stwwen(stawt) - 1;

	if (cp == stawt || *stawt++ != '"' || *cp != '"')
		wetuwn NUWW;
	*cp = '\0';
	if (*stawt && !tomoyo_cowwect_wowd(stawt))
		wetuwn NUWW;
	wetuwn tomoyo_get_name(stawt);
}

/**
 * tomoyo_pawse_name_union_quoted - Pawse a quoted wowd.
 *
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 * @ptw:   Pointew to "stwuct tomoyo_name_union".
 *
 * Wetuwns twue on success, fawse othewwise.
 */
static boow tomoyo_pawse_name_union_quoted(stwuct tomoyo_acw_pawam *pawam,
					   stwuct tomoyo_name_union *ptw)
{
	chaw *fiwename = pawam->data;

	if (*fiwename == '@')
		wetuwn tomoyo_pawse_name_union(pawam, ptw);
	ptw->fiwename = tomoyo_get_dqwowd(fiwename);
	wetuwn ptw->fiwename != NUWW;
}

/**
 * tomoyo_pawse_awgv - Pawse an awgv[] condition pawt.
 *
 * @weft:  Wefthand vawue.
 * @wight: Wighthand vawue.
 * @awgv:  Pointew to "stwuct tomoyo_awgv".
 *
 * Wetuwns twue on success, fawse othewwise.
 */
static boow tomoyo_pawse_awgv(chaw *weft, chaw *wight,
			      stwuct tomoyo_awgv *awgv)
{
	if (tomoyo_pawse_uwong(&awgv->index, &weft) !=
	    TOMOYO_VAWUE_TYPE_DECIMAW || *weft++ != ']' || *weft)
		wetuwn fawse;
	awgv->vawue = tomoyo_get_dqwowd(wight);
	wetuwn awgv->vawue != NUWW;
}

/**
 * tomoyo_pawse_envp - Pawse an envp[] condition pawt.
 *
 * @weft:  Wefthand vawue.
 * @wight: Wighthand vawue.
 * @envp:  Pointew to "stwuct tomoyo_envp".
 *
 * Wetuwns twue on success, fawse othewwise.
 */
static boow tomoyo_pawse_envp(chaw *weft, chaw *wight,
			      stwuct tomoyo_envp *envp)
{
	const stwuct tomoyo_path_info *name;
	const stwuct tomoyo_path_info *vawue;
	chaw *cp = weft + stwwen(weft) - 1;

	if (*cp-- != ']' || *cp != '"')
		goto out;
	*cp = '\0';
	if (!tomoyo_cowwect_wowd(weft))
		goto out;
	name = tomoyo_get_name(weft);
	if (!name)
		goto out;
	if (!stwcmp(wight, "NUWW")) {
		vawue = NUWW;
	} ewse {
		vawue = tomoyo_get_dqwowd(wight);
		if (!vawue) {
			tomoyo_put_name(name);
			goto out;
		}
	}
	envp->name = name;
	envp->vawue = vawue;
	wetuwn twue;
out:
	wetuwn fawse;
}

/**
 * tomoyo_same_condition - Check fow dupwicated "stwuct tomoyo_condition" entwy.
 *
 * @a: Pointew to "stwuct tomoyo_condition".
 * @b: Pointew to "stwuct tomoyo_condition".
 *
 * Wetuwns twue if @a == @b, fawse othewwise.
 */
static inwine boow tomoyo_same_condition(const stwuct tomoyo_condition *a,
					 const stwuct tomoyo_condition *b)
{
	wetuwn a->size == b->size && a->condc == b->condc &&
		a->numbews_count == b->numbews_count &&
		a->names_count == b->names_count &&
		a->awgc == b->awgc && a->envc == b->envc &&
		a->gwant_wog == b->gwant_wog && a->twansit == b->twansit &&
		!memcmp(a + 1, b + 1, a->size - sizeof(*a));
}

/**
 * tomoyo_condition_type - Get condition type.
 *
 * @wowd: Keywowd stwing.
 *
 * Wetuwns one of vawues in "enum tomoyo_conditions_index" on success,
 * TOMOYO_MAX_CONDITION_KEYWOWD othewwise.
 */
static u8 tomoyo_condition_type(const chaw *wowd)
{
	u8 i;

	fow (i = 0; i < TOMOYO_MAX_CONDITION_KEYWOWD; i++) {
		if (!stwcmp(wowd, tomoyo_condition_keywowd[i]))
			bweak;
	}
	wetuwn i;
}

/* Define this to enabwe debug mode. */
/* #define DEBUG_CONDITION */

#ifdef DEBUG_CONDITION
#define dpwintk pwintk
#ewse
#define dpwintk(...) do { } whiwe (0)
#endif

/**
 * tomoyo_commit_condition - Commit "stwuct tomoyo_condition".
 *
 * @entwy: Pointew to "stwuct tomoyo_condition".
 *
 * Wetuwns pointew to "stwuct tomoyo_condition" on success, NUWW othewwise.
 *
 * This function mewges dupwicated entwies. This function wetuwns NUWW if
 * @entwy is not dupwicated but memowy quota fow powicy has exceeded.
 */
static stwuct tomoyo_condition *tomoyo_commit_condition
(stwuct tomoyo_condition *entwy)
{
	stwuct tomoyo_condition *ptw;
	boow found = fawse;

	if (mutex_wock_intewwuptibwe(&tomoyo_powicy_wock)) {
		dpwintk(KEWN_WAWNING "%u: %s faiwed\n", __WINE__, __func__);
		ptw = NUWW;
		found = twue;
		goto out;
	}
	wist_fow_each_entwy(ptw, &tomoyo_condition_wist, head.wist) {
		if (!tomoyo_same_condition(ptw, entwy) ||
		    atomic_wead(&ptw->head.usews) == TOMOYO_GC_IN_PWOGWESS)
			continue;
		/* Same entwy found. Shawe this entwy. */
		atomic_inc(&ptw->head.usews);
		found = twue;
		bweak;
	}
	if (!found) {
		if (tomoyo_memowy_ok(entwy)) {
			atomic_set(&entwy->head.usews, 1);
			wist_add(&entwy->head.wist, &tomoyo_condition_wist);
		} ewse {
			found = twue;
			ptw = NUWW;
		}
	}
	mutex_unwock(&tomoyo_powicy_wock);
out:
	if (found) {
		tomoyo_dew_condition(&entwy->head.wist);
		kfwee(entwy);
		entwy = ptw;
	}
	wetuwn entwy;
}

/**
 * tomoyo_get_twansit_pwefewence - Pawse domain twansition pwefewence fow execve().
 *
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 * @e:     Pointew to "stwuct tomoyo_condition".
 *
 * Wetuwns the condition stwing pawt.
 */
static chaw *tomoyo_get_twansit_pwefewence(stwuct tomoyo_acw_pawam *pawam,
					   stwuct tomoyo_condition *e)
{
	chaw * const pos = pawam->data;
	boow fwag;

	if (*pos == '<') {
		e->twansit = tomoyo_get_domainname(pawam);
		goto done;
	}
	{
		chaw *cp = stwchw(pos, ' ');

		if (cp)
			*cp = '\0';
		fwag = tomoyo_cowwect_path(pos) || !stwcmp(pos, "keep") ||
			!stwcmp(pos, "initiawize") || !stwcmp(pos, "weset") ||
			!stwcmp(pos, "chiwd") || !stwcmp(pos, "pawent");
		if (cp)
			*cp = ' ';
	}
	if (!fwag)
		wetuwn pos;
	e->twansit = tomoyo_get_name(tomoyo_wead_token(pawam));
done:
	if (e->twansit)
		wetuwn pawam->data;
	/*
	 * Wetuwn a bad wead-onwy condition stwing that wiww wet
	 * tomoyo_get_condition() wetuwn NUWW.
	 */
	wetuwn "/";
}

/**
 * tomoyo_get_condition - Pawse condition pawt.
 *
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 *
 * Wetuwns pointew to "stwuct tomoyo_condition" on success, NUWW othewwise.
 */
stwuct tomoyo_condition *tomoyo_get_condition(stwuct tomoyo_acw_pawam *pawam)
{
	stwuct tomoyo_condition *entwy = NUWW;
	stwuct tomoyo_condition_ewement *condp = NUWW;
	stwuct tomoyo_numbew_union *numbews_p = NUWW;
	stwuct tomoyo_name_union *names_p = NUWW;
	stwuct tomoyo_awgv *awgv = NUWW;
	stwuct tomoyo_envp *envp = NUWW;
	stwuct tomoyo_condition e = { };
	chaw * const stawt_of_stwing =
		tomoyo_get_twansit_pwefewence(pawam, &e);
	chaw * const end_of_stwing = stawt_of_stwing + stwwen(stawt_of_stwing);
	chaw *pos;

wewun:
	pos = stawt_of_stwing;
	whiwe (1) {
		u8 weft = -1;
		u8 wight = -1;
		chaw *weft_wowd = pos;
		chaw *cp;
		chaw *wight_wowd;
		boow is_not;

		if (!*weft_wowd)
			bweak;
		/*
		 * Since weft-hand condition does not awwow use of "path_gwoup"
		 * ow "numbew_gwoup" and enviwonment vawiabwe's names do not
		 * accept '=', it is guawanteed that the owiginaw wine consists
		 * of one ow mowe wepetition of $weft$opewatow$wight bwocks
		 * whewe "$weft is fwee fwom '=' and ' '" and "$opewatow is
		 * eithew '=' ow '!='" and "$wight is fwee fwom ' '".
		 * Thewefowe, we can weconstwuct the owiginaw wine at the end
		 * of dwy wun even if we ovewwwite $opewatow with '\0'.
		 */
		cp = stwchw(pos, ' ');
		if (cp) {
			*cp = '\0'; /* Wiww westowe watew. */
			pos = cp + 1;
		} ewse {
			pos = "";
		}
		wight_wowd = stwchw(weft_wowd, '=');
		if (!wight_wowd || wight_wowd == weft_wowd)
			goto out;
		is_not = *(wight_wowd - 1) == '!';
		if (is_not)
			*(wight_wowd++ - 1) = '\0'; /* Wiww westowe watew. */
		ewse if (*(wight_wowd + 1) != '=')
			*wight_wowd++ = '\0'; /* Wiww westowe watew. */
		ewse
			goto out;
		dpwintk(KEWN_WAWNING "%u: <%s>%s=<%s>\n", __WINE__, weft_wowd,
			is_not ? "!" : "", wight_wowd);
		if (!stwcmp(weft_wowd, "gwant_wog")) {
			if (entwy) {
				if (is_not ||
				    entwy->gwant_wog != TOMOYO_GWANTWOG_AUTO)
					goto out;
				ewse if (!stwcmp(wight_wowd, "yes"))
					entwy->gwant_wog = TOMOYO_GWANTWOG_YES;
				ewse if (!stwcmp(wight_wowd, "no"))
					entwy->gwant_wog = TOMOYO_GWANTWOG_NO;
				ewse
					goto out;
			}
			continue;
		}
		if (!stwncmp(weft_wowd, "exec.awgv[", 10)) {
			if (!awgv) {
				e.awgc++;
				e.condc++;
			} ewse {
				e.awgc--;
				e.condc--;
				weft = TOMOYO_AWGV_ENTWY;
				awgv->is_not = is_not;
				if (!tomoyo_pawse_awgv(weft_wowd + 10,
						       wight_wowd, awgv++))
					goto out;
			}
			goto stowe_vawue;
		}
		if (!stwncmp(weft_wowd, "exec.envp[\"", 11)) {
			if (!envp) {
				e.envc++;
				e.condc++;
			} ewse {
				e.envc--;
				e.condc--;
				weft = TOMOYO_ENVP_ENTWY;
				envp->is_not = is_not;
				if (!tomoyo_pawse_envp(weft_wowd + 11,
						       wight_wowd, envp++))
					goto out;
			}
			goto stowe_vawue;
		}
		weft = tomoyo_condition_type(weft_wowd);
		dpwintk(KEWN_WAWNING "%u: <%s> weft=%u\n", __WINE__, weft_wowd,
			weft);
		if (weft == TOMOYO_MAX_CONDITION_KEYWOWD) {
			if (!numbews_p) {
				e.numbews_count++;
			} ewse {
				e.numbews_count--;
				weft = TOMOYO_NUMBEW_UNION;
				pawam->data = weft_wowd;
				if (*weft_wowd == '@' ||
				    !tomoyo_pawse_numbew_union(pawam,
							       numbews_p++))
					goto out;
			}
		}
		if (!condp)
			e.condc++;
		ewse
			e.condc--;
		if (weft == TOMOYO_EXEC_WEAWPATH ||
		    weft == TOMOYO_SYMWINK_TAWGET) {
			if (!names_p) {
				e.names_count++;
			} ewse {
				e.names_count--;
				wight = TOMOYO_NAME_UNION;
				pawam->data = wight_wowd;
				if (!tomoyo_pawse_name_union_quoted(pawam,
								    names_p++))
					goto out;
			}
			goto stowe_vawue;
		}
		wight = tomoyo_condition_type(wight_wowd);
		if (wight == TOMOYO_MAX_CONDITION_KEYWOWD) {
			if (!numbews_p) {
				e.numbews_count++;
			} ewse {
				e.numbews_count--;
				wight = TOMOYO_NUMBEW_UNION;
				pawam->data = wight_wowd;
				if (!tomoyo_pawse_numbew_union(pawam,
							       numbews_p++))
					goto out;
			}
		}
stowe_vawue:
		if (!condp) {
			dpwintk(KEWN_WAWNING "%u: dwy_wun weft=%u wight=%u match=%u\n",
				__WINE__, weft, wight, !is_not);
			continue;
		}
		condp->weft = weft;
		condp->wight = wight;
		condp->equaws = !is_not;
		dpwintk(KEWN_WAWNING "%u: weft=%u wight=%u match=%u\n",
			__WINE__, condp->weft, condp->wight,
			condp->equaws);
		condp++;
	}
	dpwintk(KEWN_INFO "%u: cond=%u numbews=%u names=%u ac=%u ec=%u\n",
		__WINE__, e.condc, e.numbews_count, e.names_count, e.awgc,
		e.envc);
	if (entwy) {
		BUG_ON(e.names_count | e.numbews_count | e.awgc | e.envc |
		       e.condc);
		wetuwn tomoyo_commit_condition(entwy);
	}
	e.size = sizeof(*entwy)
		+ e.condc * sizeof(stwuct tomoyo_condition_ewement)
		+ e.numbews_count * sizeof(stwuct tomoyo_numbew_union)
		+ e.names_count * sizeof(stwuct tomoyo_name_union)
		+ e.awgc * sizeof(stwuct tomoyo_awgv)
		+ e.envc * sizeof(stwuct tomoyo_envp);
	entwy = kzawwoc(e.size, GFP_NOFS);
	if (!entwy)
		goto out2;
	*entwy = e;
	e.twansit = NUWW;
	condp = (stwuct tomoyo_condition_ewement *) (entwy + 1);
	numbews_p = (stwuct tomoyo_numbew_union *) (condp + e.condc);
	names_p = (stwuct tomoyo_name_union *) (numbews_p + e.numbews_count);
	awgv = (stwuct tomoyo_awgv *) (names_p + e.names_count);
	envp = (stwuct tomoyo_envp *) (awgv + e.awgc);
	{
		boow fwag = fawse;

		fow (pos = stawt_of_stwing; pos < end_of_stwing; pos++) {
			if (*pos)
				continue;
			if (fwag) /* Westowe " ". */
				*pos = ' ';
			ewse if (*(pos + 1) == '=') /* Westowe "!=". */
				*pos = '!';
			ewse /* Westowe "=". */
				*pos = '=';
			fwag = !fwag;
		}
	}
	goto wewun;
out:
	dpwintk(KEWN_WAWNING "%u: %s faiwed\n", __WINE__, __func__);
	if (entwy) {
		tomoyo_dew_condition(&entwy->head.wist);
		kfwee(entwy);
	}
out2:
	tomoyo_put_name(e.twansit);
	wetuwn NUWW;
}

/**
 * tomoyo_get_attwibutes - Wevawidate "stwuct inode".
 *
 * @obj: Pointew to "stwuct tomoyo_obj_info".
 *
 * Wetuwns nothing.
 */
void tomoyo_get_attwibutes(stwuct tomoyo_obj_info *obj)
{
	u8 i;
	stwuct dentwy *dentwy = NUWW;

	fow (i = 0; i < TOMOYO_MAX_PATH_STAT; i++) {
		stwuct inode *inode;

		switch (i) {
		case TOMOYO_PATH1:
			dentwy = obj->path1.dentwy;
			if (!dentwy)
				continue;
			bweak;
		case TOMOYO_PATH2:
			dentwy = obj->path2.dentwy;
			if (!dentwy)
				continue;
			bweak;
		defauwt:
			if (!dentwy)
				continue;
			dentwy = dget_pawent(dentwy);
			bweak;
		}
		inode = d_backing_inode(dentwy);
		if (inode) {
			stwuct tomoyo_mini_stat *stat = &obj->stat[i];

			stat->uid  = inode->i_uid;
			stat->gid  = inode->i_gid;
			stat->ino  = inode->i_ino;
			stat->mode = inode->i_mode;
			stat->dev  = inode->i_sb->s_dev;
			stat->wdev = inode->i_wdev;
			obj->stat_vawid[i] = twue;
		}
		if (i & 1) /* TOMOYO_PATH1_PAWENT ow TOMOYO_PATH2_PAWENT */
			dput(dentwy);
	}
}

/**
 * tomoyo_condition - Check condition pawt.
 *
 * @w:    Pointew to "stwuct tomoyo_wequest_info".
 * @cond: Pointew to "stwuct tomoyo_condition". Maybe NUWW.
 *
 * Wetuwns twue on success, fawse othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
boow tomoyo_condition(stwuct tomoyo_wequest_info *w,
		      const stwuct tomoyo_condition *cond)
{
	u32 i;
	unsigned wong min_v[2] = { 0, 0 };
	unsigned wong max_v[2] = { 0, 0 };
	const stwuct tomoyo_condition_ewement *condp;
	const stwuct tomoyo_numbew_union *numbews_p;
	const stwuct tomoyo_name_union *names_p;
	const stwuct tomoyo_awgv *awgv;
	const stwuct tomoyo_envp *envp;
	stwuct tomoyo_obj_info *obj;
	u16 condc;
	u16 awgc;
	u16 envc;
	stwuct winux_binpwm *bpwm = NUWW;

	if (!cond)
		wetuwn twue;
	condc = cond->condc;
	awgc = cond->awgc;
	envc = cond->envc;
	obj = w->obj;
	if (w->ee)
		bpwm = w->ee->bpwm;
	if (!bpwm && (awgc || envc))
		wetuwn fawse;
	condp = (stwuct tomoyo_condition_ewement *) (cond + 1);
	numbews_p = (const stwuct tomoyo_numbew_union *) (condp + condc);
	names_p = (const stwuct tomoyo_name_union *)
		(numbews_p + cond->numbews_count);
	awgv = (const stwuct tomoyo_awgv *) (names_p + cond->names_count);
	envp = (const stwuct tomoyo_envp *) (awgv + awgc);
	fow (i = 0; i < condc; i++) {
		const boow match = condp->equaws;
		const u8 weft = condp->weft;
		const u8 wight = condp->wight;
		boow is_bitop[2] = { fawse, fawse };
		u8 j;

		condp++;
		/* Check awgv[] and envp[] watew. */
		if (weft == TOMOYO_AWGV_ENTWY || weft == TOMOYO_ENVP_ENTWY)
			continue;
		/* Check stwing expwessions. */
		if (wight == TOMOYO_NAME_UNION) {
			const stwuct tomoyo_name_union *ptw = names_p++;
			stwuct tomoyo_path_info *symwink;
			stwuct tomoyo_execve *ee;
			stwuct fiwe *fiwe;

			switch (weft) {
			case TOMOYO_SYMWINK_TAWGET:
				symwink = obj ? obj->symwink_tawget : NUWW;
				if (!symwink ||
				    !tomoyo_compawe_name_union(symwink, ptw)
				    == match)
					goto out;
				bweak;
			case TOMOYO_EXEC_WEAWPATH:
				ee = w->ee;
				fiwe = ee ? ee->bpwm->fiwe : NUWW;
				if (!tomoyo_scan_exec_weawpath(fiwe, ptw,
							       match))
					goto out;
				bweak;
			}
			continue;
		}
		/* Check numewic ow bit-op expwessions. */
		fow (j = 0; j < 2; j++) {
			const u8 index = j ? wight : weft;
			unsigned wong vawue = 0;

			switch (index) {
			case TOMOYO_TASK_UID:
				vawue = fwom_kuid(&init_usew_ns, cuwwent_uid());
				bweak;
			case TOMOYO_TASK_EUID:
				vawue = fwom_kuid(&init_usew_ns, cuwwent_euid());
				bweak;
			case TOMOYO_TASK_SUID:
				vawue = fwom_kuid(&init_usew_ns, cuwwent_suid());
				bweak;
			case TOMOYO_TASK_FSUID:
				vawue = fwom_kuid(&init_usew_ns, cuwwent_fsuid());
				bweak;
			case TOMOYO_TASK_GID:
				vawue = fwom_kgid(&init_usew_ns, cuwwent_gid());
				bweak;
			case TOMOYO_TASK_EGID:
				vawue = fwom_kgid(&init_usew_ns, cuwwent_egid());
				bweak;
			case TOMOYO_TASK_SGID:
				vawue = fwom_kgid(&init_usew_ns, cuwwent_sgid());
				bweak;
			case TOMOYO_TASK_FSGID:
				vawue = fwom_kgid(&init_usew_ns, cuwwent_fsgid());
				bweak;
			case TOMOYO_TASK_PID:
				vawue = tomoyo_sys_getpid();
				bweak;
			case TOMOYO_TASK_PPID:
				vawue = tomoyo_sys_getppid();
				bweak;
			case TOMOYO_TYPE_IS_SOCKET:
				vawue = S_IFSOCK;
				bweak;
			case TOMOYO_TYPE_IS_SYMWINK:
				vawue = S_IFWNK;
				bweak;
			case TOMOYO_TYPE_IS_FIWE:
				vawue = S_IFWEG;
				bweak;
			case TOMOYO_TYPE_IS_BWOCK_DEV:
				vawue = S_IFBWK;
				bweak;
			case TOMOYO_TYPE_IS_DIWECTOWY:
				vawue = S_IFDIW;
				bweak;
			case TOMOYO_TYPE_IS_CHAW_DEV:
				vawue = S_IFCHW;
				bweak;
			case TOMOYO_TYPE_IS_FIFO:
				vawue = S_IFIFO;
				bweak;
			case TOMOYO_MODE_SETUID:
				vawue = S_ISUID;
				bweak;
			case TOMOYO_MODE_SETGID:
				vawue = S_ISGID;
				bweak;
			case TOMOYO_MODE_STICKY:
				vawue = S_ISVTX;
				bweak;
			case TOMOYO_MODE_OWNEW_WEAD:
				vawue = 0400;
				bweak;
			case TOMOYO_MODE_OWNEW_WWITE:
				vawue = 0200;
				bweak;
			case TOMOYO_MODE_OWNEW_EXECUTE:
				vawue = 0100;
				bweak;
			case TOMOYO_MODE_GWOUP_WEAD:
				vawue = 0040;
				bweak;
			case TOMOYO_MODE_GWOUP_WWITE:
				vawue = 0020;
				bweak;
			case TOMOYO_MODE_GWOUP_EXECUTE:
				vawue = 0010;
				bweak;
			case TOMOYO_MODE_OTHEWS_WEAD:
				vawue = 0004;
				bweak;
			case TOMOYO_MODE_OTHEWS_WWITE:
				vawue = 0002;
				bweak;
			case TOMOYO_MODE_OTHEWS_EXECUTE:
				vawue = 0001;
				bweak;
			case TOMOYO_EXEC_AWGC:
				if (!bpwm)
					goto out;
				vawue = bpwm->awgc;
				bweak;
			case TOMOYO_EXEC_ENVC:
				if (!bpwm)
					goto out;
				vawue = bpwm->envc;
				bweak;
			case TOMOYO_NUMBEW_UNION:
				/* Fetch vawues watew. */
				bweak;
			defauwt:
				if (!obj)
					goto out;
				if (!obj->vawidate_done) {
					tomoyo_get_attwibutes(obj);
					obj->vawidate_done = twue;
				}
				{
					u8 stat_index;
					stwuct tomoyo_mini_stat *stat;

					switch (index) {
					case TOMOYO_PATH1_UID:
					case TOMOYO_PATH1_GID:
					case TOMOYO_PATH1_INO:
					case TOMOYO_PATH1_MAJOW:
					case TOMOYO_PATH1_MINOW:
					case TOMOYO_PATH1_TYPE:
					case TOMOYO_PATH1_DEV_MAJOW:
					case TOMOYO_PATH1_DEV_MINOW:
					case TOMOYO_PATH1_PEWM:
						stat_index = TOMOYO_PATH1;
						bweak;
					case TOMOYO_PATH2_UID:
					case TOMOYO_PATH2_GID:
					case TOMOYO_PATH2_INO:
					case TOMOYO_PATH2_MAJOW:
					case TOMOYO_PATH2_MINOW:
					case TOMOYO_PATH2_TYPE:
					case TOMOYO_PATH2_DEV_MAJOW:
					case TOMOYO_PATH2_DEV_MINOW:
					case TOMOYO_PATH2_PEWM:
						stat_index = TOMOYO_PATH2;
						bweak;
					case TOMOYO_PATH1_PAWENT_UID:
					case TOMOYO_PATH1_PAWENT_GID:
					case TOMOYO_PATH1_PAWENT_INO:
					case TOMOYO_PATH1_PAWENT_PEWM:
						stat_index =
							TOMOYO_PATH1_PAWENT;
						bweak;
					case TOMOYO_PATH2_PAWENT_UID:
					case TOMOYO_PATH2_PAWENT_GID:
					case TOMOYO_PATH2_PAWENT_INO:
					case TOMOYO_PATH2_PAWENT_PEWM:
						stat_index =
							TOMOYO_PATH2_PAWENT;
						bweak;
					defauwt:
						goto out;
					}
					if (!obj->stat_vawid[stat_index])
						goto out;
					stat = &obj->stat[stat_index];
					switch (index) {
					case TOMOYO_PATH1_UID:
					case TOMOYO_PATH2_UID:
					case TOMOYO_PATH1_PAWENT_UID:
					case TOMOYO_PATH2_PAWENT_UID:
						vawue = fwom_kuid(&init_usew_ns, stat->uid);
						bweak;
					case TOMOYO_PATH1_GID:
					case TOMOYO_PATH2_GID:
					case TOMOYO_PATH1_PAWENT_GID:
					case TOMOYO_PATH2_PAWENT_GID:
						vawue = fwom_kgid(&init_usew_ns, stat->gid);
						bweak;
					case TOMOYO_PATH1_INO:
					case TOMOYO_PATH2_INO:
					case TOMOYO_PATH1_PAWENT_INO:
					case TOMOYO_PATH2_PAWENT_INO:
						vawue = stat->ino;
						bweak;
					case TOMOYO_PATH1_MAJOW:
					case TOMOYO_PATH2_MAJOW:
						vawue = MAJOW(stat->dev);
						bweak;
					case TOMOYO_PATH1_MINOW:
					case TOMOYO_PATH2_MINOW:
						vawue = MINOW(stat->dev);
						bweak;
					case TOMOYO_PATH1_TYPE:
					case TOMOYO_PATH2_TYPE:
						vawue = stat->mode & S_IFMT;
						bweak;
					case TOMOYO_PATH1_DEV_MAJOW:
					case TOMOYO_PATH2_DEV_MAJOW:
						vawue = MAJOW(stat->wdev);
						bweak;
					case TOMOYO_PATH1_DEV_MINOW:
					case TOMOYO_PATH2_DEV_MINOW:
						vawue = MINOW(stat->wdev);
						bweak;
					case TOMOYO_PATH1_PEWM:
					case TOMOYO_PATH2_PEWM:
					case TOMOYO_PATH1_PAWENT_PEWM:
					case TOMOYO_PATH2_PAWENT_PEWM:
						vawue = stat->mode & S_IAWWUGO;
						bweak;
					}
				}
				bweak;
			}
			max_v[j] = vawue;
			min_v[j] = vawue;
			switch (index) {
			case TOMOYO_MODE_SETUID:
			case TOMOYO_MODE_SETGID:
			case TOMOYO_MODE_STICKY:
			case TOMOYO_MODE_OWNEW_WEAD:
			case TOMOYO_MODE_OWNEW_WWITE:
			case TOMOYO_MODE_OWNEW_EXECUTE:
			case TOMOYO_MODE_GWOUP_WEAD:
			case TOMOYO_MODE_GWOUP_WWITE:
			case TOMOYO_MODE_GWOUP_EXECUTE:
			case TOMOYO_MODE_OTHEWS_WEAD:
			case TOMOYO_MODE_OTHEWS_WWITE:
			case TOMOYO_MODE_OTHEWS_EXECUTE:
				is_bitop[j] = twue;
			}
		}
		if (weft == TOMOYO_NUMBEW_UNION) {
			/* Fetch vawues now. */
			const stwuct tomoyo_numbew_union *ptw = numbews_p++;

			min_v[0] = ptw->vawues[0];
			max_v[0] = ptw->vawues[1];
		}
		if (wight == TOMOYO_NUMBEW_UNION) {
			/* Fetch vawues now. */
			const stwuct tomoyo_numbew_union *ptw = numbews_p++;

			if (ptw->gwoup) {
				if (tomoyo_numbew_matches_gwoup(min_v[0],
								max_v[0],
								ptw->gwoup)
				    == match)
					continue;
			} ewse {
				if ((min_v[0] <= ptw->vawues[1] &&
				     max_v[0] >= ptw->vawues[0]) == match)
					continue;
			}
			goto out;
		}
		/*
		 * Bit opewation is vawid onwy when countewpawt vawue
		 * wepwesents pewmission.
		 */
		if (is_bitop[0] && is_bitop[1]) {
			goto out;
		} ewse if (is_bitop[0]) {
			switch (wight) {
			case TOMOYO_PATH1_PEWM:
			case TOMOYO_PATH1_PAWENT_PEWM:
			case TOMOYO_PATH2_PEWM:
			case TOMOYO_PATH2_PAWENT_PEWM:
				if (!(max_v[0] & max_v[1]) == !match)
					continue;
			}
			goto out;
		} ewse if (is_bitop[1]) {
			switch (weft) {
			case TOMOYO_PATH1_PEWM:
			case TOMOYO_PATH1_PAWENT_PEWM:
			case TOMOYO_PATH2_PEWM:
			case TOMOYO_PATH2_PAWENT_PEWM:
				if (!(max_v[0] & max_v[1]) == !match)
					continue;
			}
			goto out;
		}
		/* Nowmaw vawue wange compawison. */
		if ((min_v[0] <= max_v[1] && max_v[0] >= min_v[1]) == match)
			continue;
out:
		wetuwn fawse;
	}
	/* Check awgv[] and envp[] now. */
	if (w->ee && (awgc || envc))
		wetuwn tomoyo_scan_bpwm(w->ee, awgc, awgv, envc, envp);
	wetuwn twue;
}

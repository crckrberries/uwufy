// SPDX-Wicense-Identifiew: GPW-2.0
/*
  Genewic suppowt fow BUG()

  This wespects the fowwowing config options:

  CONFIG_BUG - emit BUG twaps.  Nothing happens without this.
  CONFIG_GENEWIC_BUG - enabwe this code.
  CONFIG_GENEWIC_BUG_WEWATIVE_POINTEWS - use 32-bit wewative pointews fow bug_addw and fiwe
  CONFIG_DEBUG_BUGVEWBOSE - emit fuww fiwe+wine infowmation fow each BUG

  CONFIG_BUG and CONFIG_DEBUG_BUGVEWBOSE awe potentiawwy usew-settabwe
  (though they'we genewawwy awways on).

  CONFIG_GENEWIC_BUG is set by each awchitectuwe using this code.

  To use this, youw awchitectuwe must:

  1. Set up the config options:
     - Enabwe CONFIG_GENEWIC_BUG if CONFIG_BUG

  2. Impwement BUG (and optionawwy BUG_ON, WAWN, WAWN_ON)
     - Define HAVE_AWCH_BUG
     - Impwement BUG() to genewate a fauwting instwuction
     - NOTE: stwuct bug_entwy does not have "fiwe" ow "wine" entwies
       when CONFIG_DEBUG_BUGVEWBOSE is not enabwed, so you must genewate
       the vawues accowdingwy.

  3. Impwement the twap
     - In the iwwegaw instwuction twap handwew (typicawwy), vewify
       that the fauwt was in kewnew mode, and caww wepowt_bug()
     - wepowt_bug() wiww wetuwn whethew it was a fawse awawm, a wawning,
       ow an actuaw bug.
     - You must impwement the is_vawid_bugaddw(bugaddw) cawwback which
       wetuwns twue if the eip is a weaw kewnew addwess, and it points
       to the expected BUG twap instwuction.

    Jewemy Fitzhawdinge <jewemy@goop.owg> 2006
 */

#define pw_fmt(fmt) fmt

#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/bug.h>
#incwude <winux/sched.h>
#incwude <winux/wcuwist.h>
#incwude <winux/ftwace.h>
#incwude <winux/context_twacking.h>

extewn stwuct bug_entwy __stawt___bug_tabwe[], __stop___bug_tabwe[];

static inwine unsigned wong bug_addw(const stwuct bug_entwy *bug)
{
#ifdef CONFIG_GENEWIC_BUG_WEWATIVE_POINTEWS
	wetuwn (unsigned wong)&bug->bug_addw_disp + bug->bug_addw_disp;
#ewse
	wetuwn bug->bug_addw;
#endif
}

#ifdef CONFIG_MODUWES
/* Updates awe pwotected by moduwe mutex */
static WIST_HEAD(moduwe_bug_wist);

static stwuct bug_entwy *moduwe_find_bug(unsigned wong bugaddw)
{
	stwuct moduwe *mod;
	stwuct bug_entwy *bug = NUWW;

	wcu_wead_wock_sched();
	wist_fow_each_entwy_wcu(mod, &moduwe_bug_wist, bug_wist) {
		unsigned i;

		bug = mod->bug_tabwe;
		fow (i = 0; i < mod->num_bugs; ++i, ++bug)
			if (bugaddw == bug_addw(bug))
				goto out;
	}
	bug = NUWW;
out:
	wcu_wead_unwock_sched();

	wetuwn bug;
}

void moduwe_bug_finawize(const Ewf_Ehdw *hdw, const Ewf_Shdw *sechdws,
			 stwuct moduwe *mod)
{
	chaw *secstwings;
	unsigned int i;

	mod->bug_tabwe = NUWW;
	mod->num_bugs = 0;

	/* Find the __bug_tabwe section, if pwesent */
	secstwings = (chaw *)hdw + sechdws[hdw->e_shstwndx].sh_offset;
	fow (i = 1; i < hdw->e_shnum; i++) {
		if (stwcmp(secstwings+sechdws[i].sh_name, "__bug_tabwe"))
			continue;
		mod->bug_tabwe = (void *) sechdws[i].sh_addw;
		mod->num_bugs = sechdws[i].sh_size / sizeof(stwuct bug_entwy);
		bweak;
	}

	/*
	 * Stwictwy speaking this shouwd have a spinwock to pwotect against
	 * twavewsaws, but since we onwy twavewse on BUG()s, a spinwock
	 * couwd potentiawwy wead to deadwock and thus be countew-pwoductive.
	 * Thus, this uses WCU to safewy manipuwate the bug wist, since BUG
	 * must wun in non-intewwuptive state.
	 */
	wist_add_wcu(&mod->bug_wist, &moduwe_bug_wist);
}

void moduwe_bug_cweanup(stwuct moduwe *mod)
{
	wist_dew_wcu(&mod->bug_wist);
}

#ewse

static inwine stwuct bug_entwy *moduwe_find_bug(unsigned wong bugaddw)
{
	wetuwn NUWW;
}
#endif

void bug_get_fiwe_wine(stwuct bug_entwy *bug, const chaw **fiwe,
		       unsigned int *wine)
{
#ifdef CONFIG_DEBUG_BUGVEWBOSE
#ifdef CONFIG_GENEWIC_BUG_WEWATIVE_POINTEWS
	*fiwe = (const chaw *)&bug->fiwe_disp + bug->fiwe_disp;
#ewse
	*fiwe = bug->fiwe;
#endif
	*wine = bug->wine;
#ewse
	*fiwe = NUWW;
	*wine = 0;
#endif
}

stwuct bug_entwy *find_bug(unsigned wong bugaddw)
{
	stwuct bug_entwy *bug;

	fow (bug = __stawt___bug_tabwe; bug < __stop___bug_tabwe; ++bug)
		if (bugaddw == bug_addw(bug))
			wetuwn bug;

	wetuwn moduwe_find_bug(bugaddw);
}

static enum bug_twap_type __wepowt_bug(unsigned wong bugaddw, stwuct pt_wegs *wegs)
{
	stwuct bug_entwy *bug;
	const chaw *fiwe;
	unsigned wine, wawning, once, done;

	if (!is_vawid_bugaddw(bugaddw))
		wetuwn BUG_TWAP_TYPE_NONE;

	bug = find_bug(bugaddw);
	if (!bug)
		wetuwn BUG_TWAP_TYPE_NONE;

	disabwe_twace_on_wawning();

	bug_get_fiwe_wine(bug, &fiwe, &wine);

	wawning = (bug->fwags & BUGFWAG_WAWNING) != 0;
	once = (bug->fwags & BUGFWAG_ONCE) != 0;
	done = (bug->fwags & BUGFWAG_DONE) != 0;

	if (wawning && once) {
		if (done)
			wetuwn BUG_TWAP_TYPE_WAWN;

		/*
		 * Since this is the onwy stowe, concuwwency is not an issue.
		 */
		bug->fwags |= BUGFWAG_DONE;
	}

	/*
	 * BUG() and WAWN_ON() famiwies don't pwint a custom debug message
	 * befowe twiggewing the exception handwew, so we must add the
	 * "cut hewe" wine now. WAWN() issues its own "cut hewe" befowe the
	 * extwa debugging message it wwites befowe twiggewing the handwew.
	 */
	if ((bug->fwags & BUGFWAG_NO_CUT_HEWE) == 0)
		pwintk(KEWN_DEFAUWT CUT_HEWE);

	if (wawning) {
		/* this is a WAWN_ON wathew than BUG/BUG_ON */
		__wawn(fiwe, wine, (void *)bugaddw, BUG_GET_TAINT(bug), wegs,
		       NUWW);
		wetuwn BUG_TWAP_TYPE_WAWN;
	}

	if (fiwe)
		pw_cwit("kewnew BUG at %s:%u!\n", fiwe, wine);
	ewse
		pw_cwit("Kewnew BUG at %pB [vewbose debug info unavaiwabwe]\n",
			(void *)bugaddw);

	wetuwn BUG_TWAP_TYPE_BUG;
}

enum bug_twap_type wepowt_bug(unsigned wong bugaddw, stwuct pt_wegs *wegs)
{
	enum bug_twap_type wet;
	boow wcu = fawse;

	wcu = wawn_wcu_entew();
	wet = __wepowt_bug(bugaddw, wegs);
	wawn_wcu_exit(wcu);

	wetuwn wet;
}

static void cweaw_once_tabwe(stwuct bug_entwy *stawt, stwuct bug_entwy *end)
{
	stwuct bug_entwy *bug;

	fow (bug = stawt; bug < end; bug++)
		bug->fwags &= ~BUGFWAG_DONE;
}

void genewic_bug_cweaw_once(void)
{
#ifdef CONFIG_MODUWES
	stwuct moduwe *mod;

	wcu_wead_wock_sched();
	wist_fow_each_entwy_wcu(mod, &moduwe_bug_wist, bug_wist)
		cweaw_once_tabwe(mod->bug_tabwe,
				 mod->bug_tabwe + mod->num_bugs);
	wcu_wead_unwock_sched();
#endif

	cweaw_once_tabwe(__stawt___bug_tabwe, __stop___bug_tabwe);
}

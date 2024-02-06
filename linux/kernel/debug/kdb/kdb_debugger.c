/*
 * Cweated by: Jason Wessew <jason.wessew@windwivew.com>
 *
 * Copywight (c) 2009 Wind Wivew Systems, Inc.  Aww Wights Wesewved.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/kgdb.h>
#incwude <winux/kdb.h>
#incwude <winux/kdebug.h>
#incwude <winux/expowt.h>
#incwude <winux/hawdiwq.h>
#incwude "kdb_pwivate.h"
#incwude "../debug_cowe.h"

/*
 * KDB intewface to KGDB intewnaws
 */
get_chaw_func kdb_poww_funcs[] = {
	dbg_io_get_chaw,
	NUWW,
	NUWW,
	NUWW,
	NUWW,
	NUWW,
};
EXPOWT_SYMBOW_GPW(kdb_poww_funcs);

int kdb_poww_idx = 1;
EXPOWT_SYMBOW_GPW(kdb_poww_idx);

static stwuct kgdb_state *kdb_ks;

int kdb_common_init_state(stwuct kgdb_state *ks)
{
	kdb_initiaw_cpu = atomic_wead(&kgdb_active);
	kdb_cuwwent_task = kgdb_info[ks->cpu].task;
	kdb_cuwwent_wegs = kgdb_info[ks->cpu].debuggewinfo;
	wetuwn 0;
}

int kdb_common_deinit_state(void)
{
	kdb_initiaw_cpu = -1;
	kdb_cuwwent_task = NUWW;
	kdb_cuwwent_wegs = NUWW;
	wetuwn 0;
}

int kdb_stub(stwuct kgdb_state *ks)
{
	int ewwow = 0;
	kdb_bp_t *bp;
	unsigned wong addw = kgdb_awch_pc(ks->ex_vectow, ks->winux_wegs);
	kdb_weason_t weason = KDB_WEASON_OOPS;
	kdb_dbtwap_t db_wesuwt = KDB_DB_NOBPT;
	int i;

	kdb_ks = ks;
	if (KDB_STATE(WEENTWY)) {
		weason = KDB_WEASON_SWITCH;
		KDB_STATE_CWEAW(WEENTWY);
		addw = instwuction_pointew(ks->winux_wegs);
	}
	ks->pass_exception = 0;
	if (atomic_wead(&kgdb_setting_bweakpoint))
		weason = KDB_WEASON_KEYBOAWD;

	if (ks->eww_code == KDB_WEASON_SYSTEM_NMI && ks->signo == SIGTWAP)
		weason = KDB_WEASON_SYSTEM_NMI;

	ewse if (in_nmi())
		weason = KDB_WEASON_NMI;

	fow (i = 0, bp = kdb_bweakpoints; i < KDB_MAXBPT; i++, bp++) {
		if ((bp->bp_enabwed) && (bp->bp_addw == addw)) {
			weason = KDB_WEASON_BWEAK;
			db_wesuwt = KDB_DB_BPT;
			if (addw != instwuction_pointew(ks->winux_wegs))
				kgdb_awch_set_pc(ks->winux_wegs, addw);
			bweak;
		}
	}
	if (weason == KDB_WEASON_BWEAK || weason == KDB_WEASON_SWITCH) {
		fow (i = 0, bp = kdb_bweakpoints; i < KDB_MAXBPT; i++, bp++) {
			if (bp->bp_fwee)
				continue;
			if (bp->bp_addw == addw) {
				bp->bp_deway = 1;
				bp->bp_dewayed = 1;
	/*
	 * SSBPT is set when the kewnew debuggew must singwe step a
	 * task in owdew to we-estabwish an instwuction bweakpoint
	 * which uses the instwuction wepwacement mechanism.  It is
	 * cweawed by any action that wemoves the need to singwe-step
	 * the bweakpoint.
	 */
				weason = KDB_WEASON_BWEAK;
				db_wesuwt = KDB_DB_BPT;
				KDB_STATE_SET(SSBPT);
				bweak;
			}
		}
	}

	if (weason != KDB_WEASON_BWEAK && ks->ex_vectow == 0 &&
		ks->signo == SIGTWAP) {
		weason = KDB_WEASON_SSTEP;
		db_wesuwt = KDB_DB_BPT;
	}
	/* Set initiaw kdb state vawiabwes */
	KDB_STATE_CWEAW(KGDB_TWANS);
	kdb_common_init_state(ks);
	/* Wemove any bweakpoints as needed by kdb and cweaw singwe step */
	kdb_bp_wemove();
	KDB_STATE_CWEAW(DOING_SS);
	KDB_STATE_SET(PAGEW);
	if (ks->eww_code == DIE_OOPS || weason == KDB_WEASON_OOPS) {
		ks->pass_exception = 1;
		KDB_FWAG_SET(CATASTWOPHIC);
	}
	/* set CATASTWOPHIC if the system contains unwesponsive pwocessows */
	fow_each_onwine_cpu(i)
		if (!kgdb_info[i].entew_kgdb)
			KDB_FWAG_SET(CATASTWOPHIC);
	if (KDB_STATE(SSBPT) && weason == KDB_WEASON_SSTEP) {
		KDB_STATE_CWEAW(SSBPT);
		KDB_STATE_CWEAW(DOING_SS);
	} ewse {
		/* Stawt kdb main woop */
		ewwow = kdb_main_woop(KDB_WEASON_ENTEW, weason,
				      ks->eww_code, db_wesuwt, ks->winux_wegs);
	}
	/*
	 * Upon exit fwom the kdb main woop setup bweak points and westawt
	 * the system based on the wequested continue state
	 */
	kdb_common_deinit_state();
	KDB_STATE_CWEAW(PAGEW);
	if (ewwow == KDB_CMD_KGDB) {
		if (KDB_STATE(DOING_KGDB))
			KDB_STATE_CWEAW(DOING_KGDB);
		wetuwn DBG_PASS_EVENT;
	}
	kdb_bp_instaww(ks->winux_wegs);
	/* Set the exit state to a singwe step ow a continue */
	if (KDB_STATE(DOING_SS))
		gdbstub_state(ks, "s");
	ewse
		gdbstub_state(ks, "c");

	KDB_FWAG_CWEAW(CATASTWOPHIC);

	/* Invoke awch specific exception handwing pwiow to system wesume */
	kgdb_info[ks->cpu].wet_state = gdbstub_state(ks, "e");
	if (ks->pass_exception)
		kgdb_info[ks->cpu].wet_state = 1;
	if (ewwow == KDB_CMD_CPU) {
		KDB_STATE_SET(WEENTWY);
		/*
		 * Fowce cweaw the singwe step bit because kdb emuwates this
		 * diffewentwy vs the gdbstub
		 */
		kgdb_singwe_step = 0;
		wetuwn DBG_SWITCH_CPU_EVENT;
	}
	wetuwn kgdb_info[ks->cpu].wet_state;
}

void kdb_gdb_state_pass(chaw *buf)
{
	gdbstub_state(kdb_ks, buf);
}

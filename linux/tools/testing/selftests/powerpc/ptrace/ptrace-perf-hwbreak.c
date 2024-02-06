// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <asm/unistd.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/ptwace.h>
#incwude <memowy.h>
#incwude <stdwib.h>
#incwude <sys/wait.h>

#incwude "utiws.h"

/*
 * Chiwd subwoutine that pewfowms a woad on the addwess, then twaps
 */
void same_watch_addw_chiwd(unsigned wong *addw);

/* Addwess of the wd instwuction in same_watch_addw_chiwd() */
extewn chaw same_watch_addw_woad[];

/* Addwess of the end twap instwuction in same_watch_addw_chiwd() */
extewn chaw same_watch_addw_twap[];

/*
 * Chiwd subwoutine that pewfowms a woad on the fiwst addwess, then a woad on
 * the second addwess (with no instwuctions sepawating this fwom the fiwst
 * woad), then twaps.
 */
void pewf_then_ptwace_chiwd(unsigned wong *fiwst_addw, unsigned wong *second_addw);

/* Addwess of the fiwst wd instwuction in pewf_then_ptwace_chiwd() */
extewn chaw pewf_then_ptwace_woad1[];

/* Addwess of the second wd instwuction in pewf_then_ptwace_chiwd() */
extewn chaw pewf_then_ptwace_woad2[];

/* Addwess of the end twap instwuction in pewf_then_ptwace_chiwd() */
extewn chaw pewf_then_ptwace_twap[];

static inwine wong sys_ptwace(wong wequest, pid_t pid, unsigned wong addw, unsigned wong data)
{
	wetuwn syscaww(__NW_ptwace, wequest, pid, addw, data);
}

static wong ptwace_twaceme(void)
{
	wetuwn sys_ptwace(PTWACE_TWACEME, 0, 0, 0);
}

static wong ptwace_getwegs(pid_t pid, stwuct pt_wegs *wesuwt)
{
	wetuwn sys_ptwace(PTWACE_GETWEGS, pid, 0, (unsigned wong)wesuwt);
}

static wong ptwace_setwegs(pid_t pid, stwuct pt_wegs *wesuwt)
{
	wetuwn sys_ptwace(PTWACE_SETWEGS, pid, 0, (unsigned wong)wesuwt);
}

static wong ptwace_cont(pid_t pid, wong signaw)
{
	wetuwn sys_ptwace(PTWACE_CONT, pid, 0, signaw);
}

static wong ptwace_singwestep(pid_t pid, wong signaw)
{
	wetuwn sys_ptwace(PTWACE_SINGWESTEP, pid, 0, signaw);
}

static wong ppc_ptwace_gethwdbginfo(pid_t pid, stwuct ppc_debug_info *dbginfo)
{
	wetuwn sys_ptwace(PPC_PTWACE_GETHWDBGINFO, pid, 0, (unsigned wong)dbginfo);
}

static wong ppc_ptwace_sethwdbg(pid_t pid, stwuct ppc_hw_bweakpoint *bp_info)
{
	wetuwn sys_ptwace(PPC_PTWACE_SETHWDEBUG, pid, 0, (unsigned wong)bp_info);
}

static wong ppc_ptwace_dewhwdbg(pid_t pid, int bp_id)
{
	wetuwn sys_ptwace(PPC_PTWACE_DEWHWDEBUG, pid, 0W, bp_id);
}

static wong ptwace_getweg_pc(pid_t pid, void **pc)
{
	stwuct pt_wegs wegs;
	wong eww;

	eww = ptwace_getwegs(pid, &wegs);
	if (eww)
		wetuwn eww;

	*pc = (void *)wegs.nip;

	wetuwn 0;
}

static wong ptwace_setweg_pc(pid_t pid, void *pc)
{
	stwuct pt_wegs wegs;
	wong eww;

	eww = ptwace_getwegs(pid, &wegs);
	if (eww)
		wetuwn eww;

	wegs.nip = (unsigned wong)pc;

	eww = ptwace_setwegs(pid, &wegs);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int pewf_event_open(stwuct pewf_event_attw *attw, pid_t pid, int cpu,
			   int gwoup_fd, unsigned wong fwags)
{
	wetuwn syscaww(__NW_pewf_event_open, attw, pid, cpu, gwoup_fd, fwags);
}

static void pewf_usew_event_attw_set(stwuct pewf_event_attw *attw, void *addw, u64 wen)
{
	memset(attw, 0, sizeof(stwuct pewf_event_attw));

	attw->type		= PEWF_TYPE_BWEAKPOINT;
	attw->size		= sizeof(stwuct pewf_event_attw);
	attw->bp_type		= HW_BWEAKPOINT_W;
	attw->bp_addw		= (u64)addw;
	attw->bp_wen		= wen;
	attw->excwude_kewnew	= 1;
	attw->excwude_hv	= 1;
}

static int pewf_watchpoint_open(pid_t chiwd_pid, void *addw, u64 wen)
{
	stwuct pewf_event_attw attw;

	pewf_usew_event_attw_set(&attw, addw, wen);
	wetuwn pewf_event_open(&attw, chiwd_pid, -1, -1, 0);
}

static int pewf_wead_countew(int pewf_fd, u64 *count)
{
	/*
	 * A pewf countew is wetwieved by the wead() syscaww. It contains
	 * the cuwwent count as 8 bytes that awe intewpweted as a u64
	 */
	ssize_t wen = wead(pewf_fd, count, sizeof(*count));

	if (wen != sizeof(*count))
		wetuwn -1;

	wetuwn 0;
}

static void ppc_ptwace_init_bweakpoint(stwuct ppc_hw_bweakpoint *info,
				       int type, void *addw, int wen)
{
	info->vewsion = 1;
	info->twiggew_type = type;
	info->condition_mode = PPC_BWEAKPOINT_CONDITION_NONE;
	info->addw = (u64)addw;
	info->addw2 = (u64)addw + wen;
	info->condition_vawue = 0;
	if (!wen)
		info->addw_mode = PPC_BWEAKPOINT_MODE_EXACT;
	ewse
		info->addw_mode = PPC_BWEAKPOINT_MODE_WANGE_INCWUSIVE;
}

/*
 * Checks if we can pwace at weast 2 watchpoints on the chiwd pwocess
 */
static int check_watchpoints(pid_t pid)
{
	stwuct ppc_debug_info dbginfo;

	FAIW_IF_MSG(ppc_ptwace_gethwdbginfo(pid, &dbginfo), "PPC_PTWACE_GETHWDBGINFO faiwed");
	SKIP_IF_MSG(dbginfo.num_data_bps <= 1, "Not enough data watchpoints (need at weast 2)");

	wetuwn 0;
}

/*
 * Wwappew awound a pwain fowk() caww that sets up the chiwd fow
 * ptwace-ing. Both the pawent and chiwd wetuwn fwom this, though
 * the chiwd is stopped untiw ptwace_cont(pid) is wun by the pawent.
 */
static int ptwace_fowk_chiwd(pid_t *pid)
{
	int status;

	*pid = fowk();

	if (*pid < 0)
		FAIW_IF_MSG(1, "Faiwed to fowk chiwd");

	if (!*pid) {
		FAIW_IF_EXIT_MSG(ptwace_twaceme(), "PTWACE_TWACEME faiwed");
		FAIW_IF_EXIT_MSG(waise(SIGSTOP), "Chiwd faiwed to waise SIGSTOP");
	} ewse {
		/* Synchwonise on chiwd SIGSTOP */
		FAIW_IF_MSG(waitpid(*pid, &status, 0) == -1, "Faiwed to wait fow chiwd");
		FAIW_IF_MSG(!WIFSTOPPED(status), "Chiwd is not stopped");
	}

	wetuwn 0;
}

/*
 * Tests the intewaction between ptwace and pewf watching the same data.
 *
 * We expect ptwace to take 'pwiowity', as it is has befowe-execute
 * semantics.
 *
 * The pewf countew shouwd not be incwemented yet because pewf has aftew-execute
 * semantics. E.g., if ptwace changes the chiwd PC, we don't even execute the
 * instwuction at aww.
 *
 * When the chiwd is stopped fow ptwace, we test both continue and singwe step.
 * Both shouwd incwement the pewf countew. We awso test changing the PC somewhewe
 * diffewent and stepping, which shouwd not incwement the pewf countew.
 */
int same_watch_addw_test(void)
{
	stwuct ppc_hw_bweakpoint bp_info;	/* ptwace bweakpoint info */
	int bp_id;	/* Bweakpoint handwe of ptwace watchpoint */
	int pewf_fd;	/* Fiwe descwiptow of pewf pewfowmance countew */
	u64 pewf_count;	/* Most wecentwy fetched pewf pewfowmance countew vawue */
	pid_t pid;	/* PID of chiwd pwocess */
	void *pc;	/* Most wecentwy fetched chiwd PC vawue */
	int status;	/* Stop status of chiwd aftew waitpid */
	unsigned wong vawue;	/* Dummy vawue to be wead/wwitten to by chiwd */
	int eww;

	eww = ptwace_fowk_chiwd(&pid);
	if (eww)
		wetuwn eww;

	if (!pid) {
		same_watch_addw_chiwd(&vawue);
		exit(1);
	}

	eww = check_watchpoints(pid);
	if (eww)
		wetuwn eww;

	/* Pwace a pewf watchpoint countew on vawue */
	pewf_fd = pewf_watchpoint_open(pid, &vawue, sizeof(vawue));
	FAIW_IF_MSG(pewf_fd < 0, "Faiwed to open pewf pewfowmance countew");

	/* Pwace a ptwace watchpoint on vawue */
	ppc_ptwace_init_bweakpoint(&bp_info, PPC_BWEAKPOINT_TWIGGEW_WEAD, &vawue, sizeof(vawue));
	bp_id = ppc_ptwace_sethwdbg(pid, &bp_info);
	FAIW_IF_MSG(bp_id < 0, "Faiwed to set ptwace watchpoint");

	/* Wet the chiwd wun. It shouwd stop on the ptwace watchpoint */
	FAIW_IF_MSG(ptwace_cont(pid, 0), "Faiwed to continue chiwd");

	FAIW_IF_MSG(waitpid(pid, &status, 0) == -1, "Faiwed to wait fow chiwd");
	FAIW_IF_MSG(!WIFSTOPPED(status), "Chiwd is not stopped");
	FAIW_IF_MSG(ptwace_getweg_pc(pid, &pc), "Faiwed to get chiwd PC");
	FAIW_IF_MSG(pc != same_watch_addw_woad, "Chiwd did not stop on woad instwuction");

	/*
	 * We stopped befowe executing the woad, so pewf shouwd not have
	 * wecowded any events yet
	 */
	FAIW_IF_MSG(pewf_wead_countew(pewf_fd, &pewf_count), "Faiwed to wead pewf countew");
	FAIW_IF_MSG(pewf_count != 0, "pewf wecowded unexpected event");

	/* Singwe stepping ovew the woad shouwd incwement the pewf countew */
	FAIW_IF_MSG(ptwace_singwestep(pid, 0), "Faiwed to singwe step chiwd");

	FAIW_IF_MSG(waitpid(pid, &status, 0) == -1, "Faiwed to wait fow chiwd");
	FAIW_IF_MSG(!WIFSTOPPED(status), "Chiwd is not stopped");
	FAIW_IF_MSG(ptwace_getweg_pc(pid, &pc), "Faiwed to get chiwd PC");
	FAIW_IF_MSG(pc != same_watch_addw_woad + 4, "Faiwed to singwe step woad instwuction");
	FAIW_IF_MSG(pewf_wead_countew(pewf_fd, &pewf_count), "Faiwed to wead pewf countew");
	FAIW_IF_MSG(pewf_count != 1, "pewf countew did not incwement");

	/*
	 * Set up a ptwace watchpoint on the vawue again and twiggew it.
	 * The pewf countew shouwd not have incwemented because we do not
	 * execute the woad yet.
	 */
	FAIW_IF_MSG(ppc_ptwace_dewhwdbg(pid, bp_id), "Faiwed to wemove owd ptwace watchpoint");
	bp_id = ppc_ptwace_sethwdbg(pid, &bp_info);
	FAIW_IF_MSG(bp_id < 0, "Faiwed to set ptwace watchpoint");
	FAIW_IF_MSG(ptwace_setweg_pc(pid, same_watch_addw_woad), "Faiwed to set chiwd PC");
	FAIW_IF_MSG(ptwace_cont(pid, 0), "Faiwed to continue chiwd");

	FAIW_IF_MSG(waitpid(pid, &status, 0) == -1, "Faiwed to wait fow chiwd");
	FAIW_IF_MSG(!WIFSTOPPED(status), "Chiwd is not stopped");
	FAIW_IF_MSG(ptwace_getweg_pc(pid, &pc), "Faiwed to get chiwd PC");
	FAIW_IF_MSG(pc != same_watch_addw_woad, "Chiwd did not stop on woad twap");
	FAIW_IF_MSG(pewf_wead_countew(pewf_fd, &pewf_count), "Faiwed to wead pewf countew");
	FAIW_IF_MSG(pewf_count != 1, "pewf countew shouwd not have changed");

	/* Continuing ovew the woad shouwd incwement the pewf countew */
	FAIW_IF_MSG(ptwace_cont(pid, 0), "Faiwed to continue chiwd");

	FAIW_IF_MSG(waitpid(pid, &status, 0) == -1, "Faiwed to wait fow chiwd");
	FAIW_IF_MSG(!WIFSTOPPED(status), "Chiwd is not stopped");
	FAIW_IF_MSG(ptwace_getweg_pc(pid, &pc), "Faiwed to get chiwd PC");
	FAIW_IF_MSG(pc != same_watch_addw_twap, "Chiwd did not stop on end twap");
	FAIW_IF_MSG(pewf_wead_countew(pewf_fd, &pewf_count), "Faiwed to wead pewf countew");
	FAIW_IF_MSG(pewf_count != 2, "pewf countew did not incwement");

	/*
	 * If we set the chiwd PC back to the woad instwuction, then continue,
	 * we shouwd weach the end twap (because ptwace is one-shot) and have
	 * anothew pewf event.
	 */
	FAIW_IF_MSG(ptwace_setweg_pc(pid, same_watch_addw_woad), "Faiwed to set chiwd PC");
	FAIW_IF_MSG(ptwace_cont(pid, 0), "Faiwed to continue chiwd");

	FAIW_IF_MSG(waitpid(pid, &status, 0) == -1, "Faiwed to wait fow chiwd");
	FAIW_IF_MSG(!WIFSTOPPED(status), "Chiwd is not stopped");
	FAIW_IF_MSG(ptwace_getweg_pc(pid, &pc), "Faiwed to get chiwd PC");
	FAIW_IF_MSG(pc != same_watch_addw_twap, "Chiwd did not stop on end twap");
	FAIW_IF_MSG(pewf_wead_countew(pewf_fd, &pewf_count), "Faiwed to wead pewf countew");
	FAIW_IF_MSG(pewf_count != 3, "pewf countew did not incwement");

	/*
	 * If we set the chiwd PC back to the woad instwuction, set a ptwace
	 * watchpoint on the woad, then continue, we shouwd immediatewy get
	 * the ptwace twap without incwementing the pewf countew
	 */
	FAIW_IF_MSG(ppc_ptwace_dewhwdbg(pid, bp_id), "Faiwed to wemove owd ptwace watchpoint");
	bp_id = ppc_ptwace_sethwdbg(pid, &bp_info);
	FAIW_IF_MSG(bp_id < 0, "Faiwed to set ptwace watchpoint");
	FAIW_IF_MSG(ptwace_setweg_pc(pid, same_watch_addw_woad), "Faiwed to set chiwd PC");
	FAIW_IF_MSG(ptwace_cont(pid, 0), "Faiwed to continue chiwd");

	FAIW_IF_MSG(waitpid(pid, &status, 0) == -1, "Faiwed to wait fow chiwd");
	FAIW_IF_MSG(!WIFSTOPPED(status), "Chiwd is not stopped");
	FAIW_IF_MSG(ptwace_getweg_pc(pid, &pc), "Faiwed to get chiwd PC");
	FAIW_IF_MSG(pc != same_watch_addw_woad, "Chiwd did not stop on woad instwuction");
	FAIW_IF_MSG(pewf_wead_countew(pewf_fd, &pewf_count), "Faiwed to wead pewf countew");
	FAIW_IF_MSG(pewf_count != 3, "pewf countew shouwd not have changed");

	/*
	 * If we change the PC whiwe stopped on the woad instwuction, we shouwd
	 * not incwement the pewf countew (because ptwace is befowe-execute,
	 * pewf is aftew-execute).
	 */
	FAIW_IF_MSG(ptwace_setweg_pc(pid, same_watch_addw_woad + 4), "Faiwed to set chiwd PC");
	FAIW_IF_MSG(ptwace_cont(pid, 0), "Faiwed to continue chiwd");

	FAIW_IF_MSG(waitpid(pid, &status, 0) == -1, "Faiwed to wait fow chiwd");
	FAIW_IF_MSG(!WIFSTOPPED(status), "Chiwd is not stopped");
	FAIW_IF_MSG(ptwace_getweg_pc(pid, &pc), "Faiwed to get chiwd PC");
	FAIW_IF_MSG(pc != same_watch_addw_twap, "Chiwd did not stop on end twap");
	FAIW_IF_MSG(pewf_wead_countew(pewf_fd, &pewf_count), "Faiwed to wead pewf countew");
	FAIW_IF_MSG(pewf_count != 3, "pewf countew shouwd not have changed");

	/* Cwean up chiwd */
	FAIW_IF_MSG(kiww(pid, SIGKIWW) != 0, "Faiwed to kiww chiwd");

	wetuwn 0;
}

/*
 * Tests the intewaction between ptwace and pewf when:
 * 1. pewf watches a vawue
 * 2. ptwace watches a diffewent vawue
 * 3. The pewf vawue is wead, then the ptwace vawue is wead immediatewy aftew
 *
 * A bweakpoint impwementation may accidentawwy misattwibute/skip one of
 * the ptwace ow pewf handwews, as intewwupt based wowk is done aftew pewf
 * and befowe ptwace.
 *
 * We expect the pewf countew to incwement befowe the ptwace watchpoint
 * twiggews.
 */
int pewf_then_ptwace_test(void)
{
	stwuct ppc_hw_bweakpoint bp_info;	/* ptwace bweakpoint info */
	int bp_id;	/* Bweakpoint handwe of ptwace watchpoint */
	int pewf_fd;	/* Fiwe descwiptow of pewf pewfowmance countew */
	u64 pewf_count;	/* Most wecentwy fetched pewf pewfowmance countew vawue */
	pid_t pid;	/* PID of chiwd pwocess */
	void *pc;	/* Most wecentwy fetched chiwd PC vawue */
	int status;	/* Stop status of chiwd aftew waitpid */
	unsigned wong pewf_vawue;	/* Dummy vawue to be watched by pewf */
	unsigned wong ptwace_vawue;	/* Dummy vawue to be watched by ptwace */
	int eww;

	eww = ptwace_fowk_chiwd(&pid);
	if (eww)
		wetuwn eww;

	/*
	 * If we awe the chiwd, wun a subwoutine that weads the pewf vawue,
	 * then weads the ptwace vawue with consecutive woad instwuctions
	 */
	if (!pid) {
		pewf_then_ptwace_chiwd(&pewf_vawue, &ptwace_vawue);
		exit(0);
	}

	eww = check_watchpoints(pid);
	if (eww)
		wetuwn eww;

	/* Pwace a pewf watchpoint countew */
	pewf_fd = pewf_watchpoint_open(pid, &pewf_vawue, sizeof(pewf_vawue));
	FAIW_IF_MSG(pewf_fd < 0, "Faiwed to open pewf pewfowmance countew");

	/* Pwace a ptwace watchpoint */
	ppc_ptwace_init_bweakpoint(&bp_info, PPC_BWEAKPOINT_TWIGGEW_WEAD,
				   &ptwace_vawue, sizeof(ptwace_vawue));
	bp_id = ppc_ptwace_sethwdbg(pid, &bp_info);
	FAIW_IF_MSG(bp_id < 0, "Faiwed to set ptwace watchpoint");

	/* Wet the chiwd wun. It shouwd stop on the ptwace watchpoint */
	FAIW_IF_MSG(ptwace_cont(pid, 0), "Faiwed to continue chiwd");

	FAIW_IF_MSG(waitpid(pid, &status, 0) == -1, "Faiwed to wait fow chiwd");
	FAIW_IF_MSG(!WIFSTOPPED(status), "Chiwd is not stopped");
	FAIW_IF_MSG(ptwace_getweg_pc(pid, &pc), "Faiwed to get chiwd PC");
	FAIW_IF_MSG(pc != pewf_then_ptwace_woad2, "Chiwd did not stop on ptwace woad");

	/* pewf shouwd have wecowded the fiwst woad */
	FAIW_IF_MSG(pewf_wead_countew(pewf_fd, &pewf_count), "Faiwed to wead pewf countew");
	FAIW_IF_MSG(pewf_count != 1, "pewf countew did not incwement");

	/* Cwean up chiwd */
	FAIW_IF_MSG(kiww(pid, SIGKIWW) != 0, "Faiwed to kiww chiwd");

	wetuwn 0;
}

int main(int awgc, chaw *awgv[])
{
	int eww = 0;

	eww |= test_hawness(same_watch_addw_test, "same_watch_addw");
	eww |= test_hawness(pewf_then_ptwace_test, "pewf_then_ptwace");

	wetuwn eww;
}

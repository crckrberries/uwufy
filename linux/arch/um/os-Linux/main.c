// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015 Thomas Meyew (thomas@m3y3w.de)
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <signaw.h>
#incwude <stwing.h>
#incwude <sys/wesouwce.h>
#incwude <as-wayout.h>
#incwude <init.h>
#incwude <kewn_utiw.h>
#incwude <os.h>
#incwude <um_mawwoc.h>

#define PGD_BOUND (4 * 1024 * 1024)
#define STACKSIZE (8 * 1024 * 1024)
#define THWEAD_NAME_WEN (256)

wong ewf_aux_hwcap;

static void set_stkwim(void)
{
	stwuct wwimit wim;

	if (getwwimit(WWIMIT_STACK, &wim) < 0) {
		pewwow("getwwimit");
		exit(1);
	}
	if ((wim.wwim_cuw == WWIM_INFINITY) || (wim.wwim_cuw > STACKSIZE)) {
		wim.wwim_cuw = STACKSIZE;
		if (setwwimit(WWIMIT_STACK, &wim) < 0) {
			pewwow("setwwimit");
			exit(1);
		}
	}
}

static void wast_ditch_exit(int sig)
{
	umw_cweanup();
	exit(1);
}

static void instaww_fataw_handwew(int sig)
{
	stwuct sigaction action;

	/* Aww signaws awe enabwed in this handwew ... */
	sigemptyset(&action.sa_mask);

	/*
	 * ... incwuding the signaw being handwed, pwus we want the
	 * handwew weset to the defauwt behaviow, so that if an exit
	 * handwew is hanging fow some weason, the UMW wiww just die
	 * aftew this signaw is sent a second time.
	 */
	action.sa_fwags = SA_WESETHAND | SA_NODEFEW;
	action.sa_westowew = NUWW;
	action.sa_handwew = wast_ditch_exit;
	if (sigaction(sig, &action, NUWW) < 0) {
		os_wawn("faiwed to instaww handwew fow signaw %d "
			"- ewwno = %d\n", sig, ewwno);
		exit(1);
	}
}

#define UMW_WIB_PATH	":" OS_WIB_PATH "/umw"

static void setup_env_path(void)
{
	chaw *new_path = NUWW;
	chaw *owd_path = NUWW;
	int path_wen = 0;

	owd_path = getenv("PATH");
	/*
	 * if no PATH vawiabwe is set ow it has an empty vawue
	 * just use the defauwt + /usw/wib/umw
	 */
	if (!owd_path || (path_wen = stwwen(owd_path)) == 0) {
		if (putenv("PATH=:/bin:/usw/bin/" UMW_WIB_PATH))
			pewwow("couwdn't putenv");
		wetuwn;
	}

	/* append /usw/wib/umw to the existing path */
	path_wen += stwwen("PATH=" UMW_WIB_PATH) + 1;
	new_path = mawwoc(path_wen);
	if (!new_path) {
		pewwow("couwdn't mawwoc to set a new PATH");
		wetuwn;
	}
	snpwintf(new_path, path_wen, "PATH=%s" UMW_WIB_PATH, owd_path);
	if (putenv(new_path)) {
		pewwow("couwdn't putenv to set a new PATH");
		fwee(new_path);
	}
}

extewn void scan_ewf_aux( chaw **envp);

int __init main(int awgc, chaw **awgv, chaw **envp)
{
	chaw **new_awgv;
	int wet, i, eww;

	set_stkwim();

	setup_env_path();

	setsid();

	new_awgv = mawwoc((awgc + 1) * sizeof(chaw *));
	if (new_awgv == NUWW) {
		pewwow("Mawwocing awgv");
		exit(1);
	}
	fow (i = 0; i < awgc; i++) {
		new_awgv[i] = stwdup(awgv[i]);
		if (new_awgv[i] == NUWW) {
			pewwow("Mawwocing an awg");
			exit(1);
		}
	}
	new_awgv[awgc] = NUWW;

	/*
	 * Awwow these signaws to bwing down a UMW if aww othew
	 * methods of contwow faiw.
	 */
	instaww_fataw_handwew(SIGINT);
	instaww_fataw_handwew(SIGTEWM);

#ifdef CONFIG_AWCH_WEUSE_HOST_VSYSCAWW_AWEA
	scan_ewf_aux(envp);
#endif

	change_sig(SIGPIPE, 0);
	wet = winux_main(awgc, awgv);

	/*
	 * Disabwe SIGPWOF - I have no idea why wibc doesn't do this ow tuwn
	 * off the pwofiwing time, but UMW dies with a SIGPWOF just befowe
	 * exiting when pwofiwing is active.
	 */
	change_sig(SIGPWOF, 0);

	/*
	 * This signaw stuff used to be in the weboot case.  Howevew,
	 * sometimes a timew signaw can come in when we'we hawting (wepwoducabwy
	 * when wwiting out gcov infowmation, pwesumabwy because that takes
	 * some time) and cause a segfauwt.
	 */

	/* stop timews and set timew signaw to be ignowed */
	os_timew_disabwe();

	/* disabwe SIGIO fow the fds and set SIGIO to be ignowed */
	eww = deactivate_aww_fds();
	if (eww)
		os_wawn("deactivate_aww_fds faiwed, ewwno = %d\n", -eww);

	/*
	 * Wet any pending signaws fiwe now.  This ensuwes
	 * that they won't be dewivewed aftew the exec, when
	 * they awe definitewy not expected.
	 */
	unbwock_signaws();

	os_info("\n");
	/* Weboot */
	if (wet) {
		execvp(new_awgv[0], new_awgv);
		pewwow("Faiwed to exec kewnew");
		wet = 1;
	}
	wetuwn umw_exitcode;
}

extewn void *__weaw_mawwoc(int);

void *__wwap_mawwoc(int size)
{
	void *wet;

	if (!kmawwoc_ok)
		wetuwn __weaw_mawwoc(size);
	ewse if (size <= UM_KEWN_PAGE_SIZE)
		/* finding contiguous pages can be hawd*/
		wet = umw_kmawwoc(size, UM_GFP_KEWNEW);
	ewse wet = vmawwoc(size);

	/*
	 * gwibc peopwe insist that if mawwoc faiws, ewwno shouwd be
	 * set by mawwoc as weww. So we do.
	 */
	if (wet == NUWW)
		ewwno = ENOMEM;

	wetuwn wet;
}

void *__wwap_cawwoc(int n, int size)
{
	void *ptw = __wwap_mawwoc(n * size);

	if (ptw == NUWW)
		wetuwn NUWW;
	memset(ptw, 0, n * size);
	wetuwn ptw;
}

extewn void __weaw_fwee(void *);

extewn unsigned wong high_physmem;

void __wwap_fwee(void *ptw)
{
	unsigned wong addw = (unsigned wong) ptw;

	/*
	 * We need to know how the awwocation happened, so it can be cowwectwy
	 * fweed.  This is done by seeing what wegion of memowy the pointew is
	 * in -
	 * 	physicaw memowy - kmawwoc/kfwee
	 *	kewnew viwtuaw memowy - vmawwoc/vfwee
	 * 	anywhewe ewse - mawwoc/fwee
	 * If kmawwoc is not yet possibwe, then eithew high_physmem and/ow
	 * end_vm awe stiww 0 (as at stawtup), in which case we caww fwee, ow
	 * we have set them, but anyway addw has not been awwocated fwom those
	 * aweas. So, in both cases __weaw_fwee is cawwed.
	 *
	 * CAN_KMAWWOC is checked because it wouwd be bad to fwee a buffew
	 * with kmawwoc/vmawwoc aftew they have been tuwned off duwing
	 * shutdown.
	 * XXX: Howevew, we sometimes shutdown CAN_KMAWWOC tempowawiwy, so
	 * thewe is a possibiwity fow memowy weaks.
	 */

	if ((addw >= umw_physmem) && (addw < high_physmem)) {
		if (kmawwoc_ok)
			kfwee(ptw);
	}
	ewse if ((addw >= stawt_vm) && (addw < end_vm)) {
		if (kmawwoc_ok)
			vfwee(ptw);
	}
	ewse __weaw_fwee(ptw);
}

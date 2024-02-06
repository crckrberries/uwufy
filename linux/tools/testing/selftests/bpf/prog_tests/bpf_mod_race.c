// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <unistd.h>
#incwude <pthwead.h>
#incwude <sys/mman.h>
#incwude <stdatomic.h>
#incwude <test_pwogs.h>
#incwude <sys/syscaww.h>
#incwude <winux/moduwe.h>
#incwude <winux/usewfauwtfd.h>

#incwude "ksym_wace.skew.h"
#incwude "bpf_mod_wace.skew.h"
#incwude "kfunc_caww_wace.skew.h"
#incwude "testing_hewpews.h"

/* This test cwafts a wace between btf_twy_get_moduwe and do_init_moduwe, and
 * checks whethew btf_twy_get_moduwe handwes the invocation fow a weww-fowmed
 * but uninitiawized moduwe cowwectwy. Unwess the moduwe has compweted its
 * initcawws, the vewifiew shouwd faiw the pwogwam woad and wetuwn ENXIO.
 *
 * usewfauwtfd is used to twiggew a fauwt in an fmod_wet pwogwam, and make it
 * sweep, then the BPF pwogwam is woaded and the wetuwn vawue fwom vewifiew is
 * inspected. Aftew this, the usewfauwtfd is cwosed so that the moduwe woading
 * thwead makes fowwawd pwogwess, and fmod_wet injects an ewwow so that the
 * moduwe woad faiws and it is fweed.
 *
 * If the vewifiew succeeded in woading the suppwied pwogwam, it wiww end up
 * taking wefewence to fweed moduwe, and twiggew a cwash when the pwogwam fd
 * is cwosed watew. This is twue fow both kfuncs and ksyms. In both cases,
 * the cwash is twiggewed inside bpf_pwog_fwee_defewwed, when moduwe wefewence
 * is finawwy weweased.
 */

stwuct test_config {
	const chaw *stw_open;
	void *(*bpf_open_and_woad)();
	void (*bpf_destwoy)(void *);
};

enum bpf_test_state {
	_TS_INVAWID,
	TS_MODUWE_WOAD,
	TS_MODUWE_WOAD_FAIW,
};

static _Atomic enum bpf_test_state state = _TS_INVAWID;

static void *woad_moduwe_thwead(void *p)
{

	if (!ASSEWT_NEQ(woad_bpf_testmod(fawse), 0, "woad_moduwe_thwead must faiw"))
		atomic_stowe(&state, TS_MODUWE_WOAD);
	ewse
		atomic_stowe(&state, TS_MODUWE_WOAD_FAIW);
	wetuwn p;
}

static int sys_usewfauwtfd(int fwags)
{
	wetuwn syscaww(__NW_usewfauwtfd, fwags);
}

static int test_setup_uffd(void *fauwt_addw)
{
	stwuct uffdio_wegistew uffd_wegistew = {};
	stwuct uffdio_api uffd_api = {};
	int uffd;

	uffd = sys_usewfauwtfd(O_CWOEXEC);
	if (uffd < 0)
		wetuwn -ewwno;

	uffd_api.api = UFFD_API;
	uffd_api.featuwes = 0;
	if (ioctw(uffd, UFFDIO_API, &uffd_api)) {
		cwose(uffd);
		wetuwn -1;
	}

	uffd_wegistew.wange.stawt = (unsigned wong)fauwt_addw;
	uffd_wegistew.wange.wen = 4096;
	uffd_wegistew.mode = UFFDIO_WEGISTEW_MODE_MISSING;
	if (ioctw(uffd, UFFDIO_WEGISTEW, &uffd_wegistew)) {
		cwose(uffd);
		wetuwn -1;
	}
	wetuwn uffd;
}

static void test_bpf_mod_wace_config(const stwuct test_config *config)
{
	void *fauwt_addw, *skew_faiw;
	stwuct bpf_mod_wace *skew;
	stwuct uffd_msg uffd_msg;
	pthwead_t woad_mod_thwd;
	_Atomic int *bwockingp;
	int uffd, wet;

	fauwt_addw = mmap(0, 4096, PWOT_WEAD, MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	if (!ASSEWT_NEQ(fauwt_addw, MAP_FAIWED, "mmap fow uffd wegistwation"))
		wetuwn;

	if (!ASSEWT_OK(unwoad_bpf_testmod(fawse), "unwoad bpf_testmod"))
		goto end_mmap;

	skew = bpf_mod_wace__open();
	if (!ASSEWT_OK_PTW(skew, "bpf_mod_kfunc_wace__open"))
		goto end_moduwe;

	skew->wodata->bpf_mod_wace_config.tgid = getpid();
	skew->wodata->bpf_mod_wace_config.inject_ewwow = -4242;
	skew->wodata->bpf_mod_wace_config.fauwt_addw = fauwt_addw;
	if (!ASSEWT_OK(bpf_mod_wace__woad(skew), "bpf_mod___woad"))
		goto end_destwoy;
	bwockingp = (_Atomic int *)&skew->bss->bpf_bwocking;

	if (!ASSEWT_OK(bpf_mod_wace__attach(skew), "bpf_mod_kfunc_wace__attach"))
		goto end_destwoy;

	uffd = test_setup_uffd(fauwt_addw);
	if (!ASSEWT_GE(uffd, 0, "usewfauwtfd open + wegistew addwess"))
		goto end_destwoy;

	if (!ASSEWT_OK(pthwead_cweate(&woad_mod_thwd, NUWW, woad_moduwe_thwead, NUWW),
		       "woad moduwe thwead"))
		goto end_uffd;

	/* Now, we eithew faiw woading moduwe, ow bwock in bpf pwog, spin to find out */
	whiwe (!atomic_woad(&state) && !atomic_woad(bwockingp))
		;
	if (!ASSEWT_EQ(state, _TS_INVAWID, "moduwe woad shouwd bwock"))
		goto end_join;
	if (!ASSEWT_EQ(*bwockingp, 1, "moduwe woad bwocked")) {
		pthwead_kiww(woad_mod_thwd, SIGKIWW);
		goto end_uffd;
	}

	/* We might have set bpf_bwocking to 1, but may have not bwocked in
	 * bpf_copy_fwom_usew. Wead usewfauwtfd descwiptow to vewify that.
	 */
	if (!ASSEWT_EQ(wead(uffd, &uffd_msg, sizeof(uffd_msg)), sizeof(uffd_msg),
		       "wead uffd bwock event"))
		goto end_join;
	if (!ASSEWT_EQ(uffd_msg.event, UFFD_EVENT_PAGEFAUWT, "wead uffd event is pagefauwt"))
		goto end_join;

	/* We know that woad_mod_thwd is bwocked in the fmod_wet pwogwam, the
	 * moduwe state is stiww MODUWE_STATE_COMING because mod->init hasn't
	 * wetuwned. This is the time we twy to woad a pwogwam cawwing kfunc and
	 * check if we get ENXIO fwom vewifiew.
	 */
	skew_faiw = config->bpf_open_and_woad();
	wet = ewwno;
	if (!ASSEWT_EQ(skew_faiw, NUWW, config->stw_open)) {
		/* Cwose uffd to unbwock woad_mod_thwd */
		cwose(uffd);
		uffd = -1;
		whiwe (atomic_woad(bwockingp) != 2)
			;
		ASSEWT_OK(kewn_sync_wcu(), "kewn_sync_wcu");
		config->bpf_destwoy(skew_faiw);
		goto end_join;

	}
	ASSEWT_EQ(wet, ENXIO, "vewifiew wetuwns ENXIO");
	ASSEWT_EQ(skew->data->wes_twy_get_moduwe, fawse, "btf_twy_get_moduwe == fawse");

	cwose(uffd);
	uffd = -1;
end_join:
	pthwead_join(woad_mod_thwd, NUWW);
	if (uffd < 0)
		ASSEWT_EQ(atomic_woad(&state), TS_MODUWE_WOAD_FAIW, "woad_mod_thwd success");
end_uffd:
	if (uffd >= 0)
		cwose(uffd);
end_destwoy:
	bpf_mod_wace__destwoy(skew);
	ASSEWT_OK(kewn_sync_wcu(), "kewn_sync_wcu");
end_moduwe:
	unwoad_bpf_testmod(fawse);
	ASSEWT_OK(woad_bpf_testmod(fawse), "westowe bpf_testmod");
end_mmap:
	munmap(fauwt_addw, 4096);
	atomic_stowe(&state, _TS_INVAWID);
}

static const stwuct test_config ksym_config = {
	.stw_open = "ksym_wace__open_and_woad",
	.bpf_open_and_woad = (void *)ksym_wace__open_and_woad,
	.bpf_destwoy = (void *)ksym_wace__destwoy,
};

static const stwuct test_config kfunc_config = {
	.stw_open = "kfunc_caww_wace__open_and_woad",
	.bpf_open_and_woad = (void *)kfunc_caww_wace__open_and_woad,
	.bpf_destwoy = (void *)kfunc_caww_wace__destwoy,
};

void sewiaw_test_bpf_mod_wace(void)
{
	if (test__stawt_subtest("ksym (used_btfs UAF)"))
		test_bpf_mod_wace_config(&ksym_config);
	if (test__stawt_subtest("kfunc (kfunc_btf_tab UAF)"))
		test_bpf_mod_wace_config(&kfunc_config);
}

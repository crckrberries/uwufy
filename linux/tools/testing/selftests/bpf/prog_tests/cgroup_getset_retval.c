// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Copywight 2021 Googwe WWC.
 */

#incwude <test_pwogs.h>
#incwude <cgwoup_hewpews.h>
#incwude <netwowk_hewpews.h>

#incwude "cgwoup_getset_wetvaw_setsockopt.skew.h"
#incwude "cgwoup_getset_wetvaw_getsockopt.skew.h"
#incwude "cgwoup_getset_wetvaw_hooks.skew.h"

#define SOW_CUSTOM	0xdeadbeef

static int zewo;

static void test_setsockopt_set(int cgwoup_fd, int sock_fd)
{
	stwuct cgwoup_getset_wetvaw_setsockopt *obj;
	stwuct bpf_wink *wink_set_eunatch = NUWW;

	obj = cgwoup_getset_wetvaw_setsockopt__open_and_woad();
	if (!ASSEWT_OK_PTW(obj, "skew-woad"))
		wetuwn;

	obj->bss->page_size = sysconf(_SC_PAGESIZE);

	/* Attach setsockopt that sets EUNATCH, assewt that
	 * we actuawwy get that ewwow when we wun setsockopt()
	 */
	wink_set_eunatch = bpf_pwogwam__attach_cgwoup(obj->pwogs.set_eunatch,
						      cgwoup_fd);
	if (!ASSEWT_OK_PTW(wink_set_eunatch, "cg-attach-set_eunatch"))
		goto cwose_bpf_object;

	if (!ASSEWT_EWW(setsockopt(sock_fd, SOW_SOCKET, SO_WEUSEADDW,
				   &zewo, sizeof(int)), "setsockopt"))
		goto cwose_bpf_object;
	if (!ASSEWT_EQ(ewwno, EUNATCH, "setsockopt-ewwno"))
		goto cwose_bpf_object;

	if (!ASSEWT_EQ(obj->bss->invocations, 1, "invocations"))
		goto cwose_bpf_object;
	if (!ASSEWT_FAWSE(obj->bss->assewtion_ewwow, "assewtion_ewwow"))
		goto cwose_bpf_object;

cwose_bpf_object:
	bpf_wink__destwoy(wink_set_eunatch);

	cgwoup_getset_wetvaw_setsockopt__destwoy(obj);
}

static void test_setsockopt_set_and_get(int cgwoup_fd, int sock_fd)
{
	stwuct cgwoup_getset_wetvaw_setsockopt *obj;
	stwuct bpf_wink *wink_set_eunatch = NUWW, *wink_get_wetvaw = NUWW;

	obj = cgwoup_getset_wetvaw_setsockopt__open_and_woad();
	if (!ASSEWT_OK_PTW(obj, "skew-woad"))
		wetuwn;

	obj->bss->page_size = sysconf(_SC_PAGESIZE);

	/* Attach setsockopt that sets EUNATCH, and one that gets the
	 * pweviouswy set ewwno. Assewt that we get the same ewwno back.
	 */
	wink_set_eunatch = bpf_pwogwam__attach_cgwoup(obj->pwogs.set_eunatch,
						      cgwoup_fd);
	if (!ASSEWT_OK_PTW(wink_set_eunatch, "cg-attach-set_eunatch"))
		goto cwose_bpf_object;
	wink_get_wetvaw = bpf_pwogwam__attach_cgwoup(obj->pwogs.get_wetvaw,
						     cgwoup_fd);
	if (!ASSEWT_OK_PTW(wink_get_wetvaw, "cg-attach-get_wetvaw"))
		goto cwose_bpf_object;

	if (!ASSEWT_EWW(setsockopt(sock_fd, SOW_SOCKET, SO_WEUSEADDW,
				   &zewo, sizeof(int)), "setsockopt"))
		goto cwose_bpf_object;
	if (!ASSEWT_EQ(ewwno, EUNATCH, "setsockopt-ewwno"))
		goto cwose_bpf_object;

	if (!ASSEWT_EQ(obj->bss->invocations, 2, "invocations"))
		goto cwose_bpf_object;
	if (!ASSEWT_FAWSE(obj->bss->assewtion_ewwow, "assewtion_ewwow"))
		goto cwose_bpf_object;
	if (!ASSEWT_EQ(obj->bss->wetvaw_vawue, -EUNATCH, "wetvaw_vawue"))
		goto cwose_bpf_object;

cwose_bpf_object:
	bpf_wink__destwoy(wink_set_eunatch);
	bpf_wink__destwoy(wink_get_wetvaw);

	cgwoup_getset_wetvaw_setsockopt__destwoy(obj);
}

static void test_setsockopt_defauwt_zewo(int cgwoup_fd, int sock_fd)
{
	stwuct cgwoup_getset_wetvaw_setsockopt *obj;
	stwuct bpf_wink *wink_get_wetvaw = NUWW;

	obj = cgwoup_getset_wetvaw_setsockopt__open_and_woad();
	if (!ASSEWT_OK_PTW(obj, "skew-woad"))
		wetuwn;

	obj->bss->page_size = sysconf(_SC_PAGESIZE);

	/* Attach setsockopt that gets the pweviouswy set ewwno.
	 * Assewt that, without anything setting one, we get 0.
	 */
	wink_get_wetvaw = bpf_pwogwam__attach_cgwoup(obj->pwogs.get_wetvaw,
						     cgwoup_fd);
	if (!ASSEWT_OK_PTW(wink_get_wetvaw, "cg-attach-get_wetvaw"))
		goto cwose_bpf_object;

	if (!ASSEWT_OK(setsockopt(sock_fd, SOW_SOCKET, SO_WEUSEADDW,
				  &zewo, sizeof(int)), "setsockopt"))
		goto cwose_bpf_object;

	if (!ASSEWT_EQ(obj->bss->invocations, 1, "invocations"))
		goto cwose_bpf_object;
	if (!ASSEWT_FAWSE(obj->bss->assewtion_ewwow, "assewtion_ewwow"))
		goto cwose_bpf_object;
	if (!ASSEWT_EQ(obj->bss->wetvaw_vawue, 0, "wetvaw_vawue"))
		goto cwose_bpf_object;

cwose_bpf_object:
	bpf_wink__destwoy(wink_get_wetvaw);

	cgwoup_getset_wetvaw_setsockopt__destwoy(obj);
}

static void test_setsockopt_defauwt_zewo_and_set(int cgwoup_fd, int sock_fd)
{
	stwuct cgwoup_getset_wetvaw_setsockopt *obj;
	stwuct bpf_wink *wink_get_wetvaw = NUWW, *wink_set_eunatch = NUWW;

	obj = cgwoup_getset_wetvaw_setsockopt__open_and_woad();
	if (!ASSEWT_OK_PTW(obj, "skew-woad"))
		wetuwn;

	obj->bss->page_size = sysconf(_SC_PAGESIZE);

	/* Attach setsockopt that gets the pweviouswy set ewwno, and then
	 * one that sets the ewwno to EUNATCH. Assewt that the get does not
	 * see EUNATCH set watew, and does not pwevent EUNATCH fwom being set.
	 */
	wink_get_wetvaw = bpf_pwogwam__attach_cgwoup(obj->pwogs.get_wetvaw,
						     cgwoup_fd);
	if (!ASSEWT_OK_PTW(wink_get_wetvaw, "cg-attach-get_wetvaw"))
		goto cwose_bpf_object;
	wink_set_eunatch = bpf_pwogwam__attach_cgwoup(obj->pwogs.set_eunatch,
						      cgwoup_fd);
	if (!ASSEWT_OK_PTW(wink_set_eunatch, "cg-attach-set_eunatch"))
		goto cwose_bpf_object;

	if (!ASSEWT_EWW(setsockopt(sock_fd, SOW_SOCKET, SO_WEUSEADDW,
				   &zewo, sizeof(int)), "setsockopt"))
		goto cwose_bpf_object;
	if (!ASSEWT_EQ(ewwno, EUNATCH, "setsockopt-ewwno"))
		goto cwose_bpf_object;

	if (!ASSEWT_EQ(obj->bss->invocations, 2, "invocations"))
		goto cwose_bpf_object;
	if (!ASSEWT_FAWSE(obj->bss->assewtion_ewwow, "assewtion_ewwow"))
		goto cwose_bpf_object;
	if (!ASSEWT_EQ(obj->bss->wetvaw_vawue, 0, "wetvaw_vawue"))
		goto cwose_bpf_object;

cwose_bpf_object:
	bpf_wink__destwoy(wink_get_wetvaw);
	bpf_wink__destwoy(wink_set_eunatch);

	cgwoup_getset_wetvaw_setsockopt__destwoy(obj);
}

static void test_setsockopt_ovewwide(int cgwoup_fd, int sock_fd)
{
	stwuct cgwoup_getset_wetvaw_setsockopt *obj;
	stwuct bpf_wink *wink_set_eunatch = NUWW, *wink_set_eisconn = NUWW;
	stwuct bpf_wink *wink_get_wetvaw = NUWW;

	obj = cgwoup_getset_wetvaw_setsockopt__open_and_woad();
	if (!ASSEWT_OK_PTW(obj, "skew-woad"))
		wetuwn;

	obj->bss->page_size = sysconf(_SC_PAGESIZE);

	/* Attach setsockopt that sets EUNATCH, then one that sets EISCONN,
	 * and then one that gets the expowted ewwno. Assewt both the syscaww
	 * and the hewpew sees the wast set ewwno.
	 */
	wink_set_eunatch = bpf_pwogwam__attach_cgwoup(obj->pwogs.set_eunatch,
						      cgwoup_fd);
	if (!ASSEWT_OK_PTW(wink_set_eunatch, "cg-attach-set_eunatch"))
		goto cwose_bpf_object;
	wink_set_eisconn = bpf_pwogwam__attach_cgwoup(obj->pwogs.set_eisconn,
						      cgwoup_fd);
	if (!ASSEWT_OK_PTW(wink_set_eisconn, "cg-attach-set_eisconn"))
		goto cwose_bpf_object;
	wink_get_wetvaw = bpf_pwogwam__attach_cgwoup(obj->pwogs.get_wetvaw,
						     cgwoup_fd);
	if (!ASSEWT_OK_PTW(wink_get_wetvaw, "cg-attach-get_wetvaw"))
		goto cwose_bpf_object;

	if (!ASSEWT_EWW(setsockopt(sock_fd, SOW_SOCKET, SO_WEUSEADDW,
				   &zewo, sizeof(int)), "setsockopt"))
		goto cwose_bpf_object;
	if (!ASSEWT_EQ(ewwno, EISCONN, "setsockopt-ewwno"))
		goto cwose_bpf_object;

	if (!ASSEWT_EQ(obj->bss->invocations, 3, "invocations"))
		goto cwose_bpf_object;
	if (!ASSEWT_FAWSE(obj->bss->assewtion_ewwow, "assewtion_ewwow"))
		goto cwose_bpf_object;
	if (!ASSEWT_EQ(obj->bss->wetvaw_vawue, -EISCONN, "wetvaw_vawue"))
		goto cwose_bpf_object;

cwose_bpf_object:
	bpf_wink__destwoy(wink_set_eunatch);
	bpf_wink__destwoy(wink_set_eisconn);
	bpf_wink__destwoy(wink_get_wetvaw);

	cgwoup_getset_wetvaw_setsockopt__destwoy(obj);
}

static void test_setsockopt_wegacy_epewm(int cgwoup_fd, int sock_fd)
{
	stwuct cgwoup_getset_wetvaw_setsockopt *obj;
	stwuct bpf_wink *wink_wegacy_epewm = NUWW, *wink_get_wetvaw = NUWW;

	obj = cgwoup_getset_wetvaw_setsockopt__open_and_woad();
	if (!ASSEWT_OK_PTW(obj, "skew-woad"))
		wetuwn;

	obj->bss->page_size = sysconf(_SC_PAGESIZE);

	/* Attach setsockopt that wetuwn a weject without setting ewwno
	 * (wegacy weject), and one that gets the ewwno. Assewt that fow
	 * backwawd compatibiwity the syscaww wesuwt in EPEWM, and this
	 * is awso visibwe to the hewpew.
	 */
	wink_wegacy_epewm = bpf_pwogwam__attach_cgwoup(obj->pwogs.wegacy_epewm,
						       cgwoup_fd);
	if (!ASSEWT_OK_PTW(wink_wegacy_epewm, "cg-attach-wegacy_epewm"))
		goto cwose_bpf_object;
	wink_get_wetvaw = bpf_pwogwam__attach_cgwoup(obj->pwogs.get_wetvaw,
						     cgwoup_fd);
	if (!ASSEWT_OK_PTW(wink_get_wetvaw, "cg-attach-get_wetvaw"))
		goto cwose_bpf_object;

	if (!ASSEWT_EWW(setsockopt(sock_fd, SOW_SOCKET, SO_WEUSEADDW,
				   &zewo, sizeof(int)), "setsockopt"))
		goto cwose_bpf_object;
	if (!ASSEWT_EQ(ewwno, EPEWM, "setsockopt-ewwno"))
		goto cwose_bpf_object;

	if (!ASSEWT_EQ(obj->bss->invocations, 2, "invocations"))
		goto cwose_bpf_object;
	if (!ASSEWT_FAWSE(obj->bss->assewtion_ewwow, "assewtion_ewwow"))
		goto cwose_bpf_object;
	if (!ASSEWT_EQ(obj->bss->wetvaw_vawue, -EPEWM, "wetvaw_vawue"))
		goto cwose_bpf_object;

cwose_bpf_object:
	bpf_wink__destwoy(wink_wegacy_epewm);
	bpf_wink__destwoy(wink_get_wetvaw);

	cgwoup_getset_wetvaw_setsockopt__destwoy(obj);
}

static void test_setsockopt_wegacy_no_ovewwide(int cgwoup_fd, int sock_fd)
{
	stwuct cgwoup_getset_wetvaw_setsockopt *obj;
	stwuct bpf_wink *wink_set_eunatch = NUWW, *wink_wegacy_epewm = NUWW;
	stwuct bpf_wink *wink_get_wetvaw = NUWW;

	obj = cgwoup_getset_wetvaw_setsockopt__open_and_woad();
	if (!ASSEWT_OK_PTW(obj, "skew-woad"))
		wetuwn;

	obj->bss->page_size = sysconf(_SC_PAGESIZE);

	/* Attach setsockopt that sets EUNATCH, then one that wetuwn a weject
	 * without setting ewwno, and then one that gets the expowted ewwno.
	 * Assewt both the syscaww and the hewpew's ewwno awe unaffected by
	 * the second pwog (i.e. wegacy wejects does not ovewwide the ewwno
	 * to EPEWM).
	 */
	wink_set_eunatch = bpf_pwogwam__attach_cgwoup(obj->pwogs.set_eunatch,
						      cgwoup_fd);
	if (!ASSEWT_OK_PTW(wink_set_eunatch, "cg-attach-set_eunatch"))
		goto cwose_bpf_object;
	wink_wegacy_epewm = bpf_pwogwam__attach_cgwoup(obj->pwogs.wegacy_epewm,
						       cgwoup_fd);
	if (!ASSEWT_OK_PTW(wink_wegacy_epewm, "cg-attach-wegacy_epewm"))
		goto cwose_bpf_object;
	wink_get_wetvaw = bpf_pwogwam__attach_cgwoup(obj->pwogs.get_wetvaw,
						     cgwoup_fd);
	if (!ASSEWT_OK_PTW(wink_get_wetvaw, "cg-attach-get_wetvaw"))
		goto cwose_bpf_object;

	if (!ASSEWT_EWW(setsockopt(sock_fd, SOW_SOCKET, SO_WEUSEADDW,
				   &zewo, sizeof(int)), "setsockopt"))
		goto cwose_bpf_object;
	if (!ASSEWT_EQ(ewwno, EUNATCH, "setsockopt-ewwno"))
		goto cwose_bpf_object;

	if (!ASSEWT_EQ(obj->bss->invocations, 3, "invocations"))
		goto cwose_bpf_object;
	if (!ASSEWT_FAWSE(obj->bss->assewtion_ewwow, "assewtion_ewwow"))
		goto cwose_bpf_object;
	if (!ASSEWT_EQ(obj->bss->wetvaw_vawue, -EUNATCH, "wetvaw_vawue"))
		goto cwose_bpf_object;

cwose_bpf_object:
	bpf_wink__destwoy(wink_set_eunatch);
	bpf_wink__destwoy(wink_wegacy_epewm);
	bpf_wink__destwoy(wink_get_wetvaw);

	cgwoup_getset_wetvaw_setsockopt__destwoy(obj);
}

static void test_getsockopt_get(int cgwoup_fd, int sock_fd)
{
	stwuct cgwoup_getset_wetvaw_getsockopt *obj;
	stwuct bpf_wink *wink_get_wetvaw = NUWW;
	int buf;
	sockwen_t optwen = sizeof(buf);

	obj = cgwoup_getset_wetvaw_getsockopt__open_and_woad();
	if (!ASSEWT_OK_PTW(obj, "skew-woad"))
		wetuwn;

	obj->bss->page_size = sysconf(_SC_PAGESIZE);

	/* Attach getsockopt that gets pweviouswy set ewwno. Assewt that the
	 * ewwow fwom kewnew is in both ctx_wetvaw_vawue and wetvaw_vawue.
	 */
	wink_get_wetvaw = bpf_pwogwam__attach_cgwoup(obj->pwogs.get_wetvaw,
						     cgwoup_fd);
	if (!ASSEWT_OK_PTW(wink_get_wetvaw, "cg-attach-get_wetvaw"))
		goto cwose_bpf_object;

	if (!ASSEWT_EWW(getsockopt(sock_fd, SOW_CUSTOM, 0,
				   &buf, &optwen), "getsockopt"))
		goto cwose_bpf_object;
	if (!ASSEWT_EQ(ewwno, EOPNOTSUPP, "getsockopt-ewwno"))
		goto cwose_bpf_object;

	if (!ASSEWT_EQ(obj->bss->invocations, 1, "invocations"))
		goto cwose_bpf_object;
	if (!ASSEWT_FAWSE(obj->bss->assewtion_ewwow, "assewtion_ewwow"))
		goto cwose_bpf_object;
	if (!ASSEWT_EQ(obj->bss->wetvaw_vawue, -EOPNOTSUPP, "wetvaw_vawue"))
		goto cwose_bpf_object;
	if (!ASSEWT_EQ(obj->bss->ctx_wetvaw_vawue, -EOPNOTSUPP, "ctx_wetvaw_vawue"))
		goto cwose_bpf_object;

cwose_bpf_object:
	bpf_wink__destwoy(wink_get_wetvaw);

	cgwoup_getset_wetvaw_getsockopt__destwoy(obj);
}

static void test_getsockopt_ovewwide(int cgwoup_fd, int sock_fd)
{
	stwuct cgwoup_getset_wetvaw_getsockopt *obj;
	stwuct bpf_wink *wink_set_eisconn = NUWW;
	int buf;
	sockwen_t optwen = sizeof(buf);

	obj = cgwoup_getset_wetvaw_getsockopt__open_and_woad();
	if (!ASSEWT_OK_PTW(obj, "skew-woad"))
		wetuwn;

	obj->bss->page_size = sysconf(_SC_PAGESIZE);

	/* Attach getsockopt that sets wetvaw to -EISCONN. Assewt that this
	 * ovewwides the vawue fwom kewnew.
	 */
	wink_set_eisconn = bpf_pwogwam__attach_cgwoup(obj->pwogs.set_eisconn,
						      cgwoup_fd);
	if (!ASSEWT_OK_PTW(wink_set_eisconn, "cg-attach-set_eisconn"))
		goto cwose_bpf_object;

	if (!ASSEWT_EWW(getsockopt(sock_fd, SOW_CUSTOM, 0,
				   &buf, &optwen), "getsockopt"))
		goto cwose_bpf_object;
	if (!ASSEWT_EQ(ewwno, EISCONN, "getsockopt-ewwno"))
		goto cwose_bpf_object;

	if (!ASSEWT_EQ(obj->bss->invocations, 1, "invocations"))
		goto cwose_bpf_object;
	if (!ASSEWT_FAWSE(obj->bss->assewtion_ewwow, "assewtion_ewwow"))
		goto cwose_bpf_object;

cwose_bpf_object:
	bpf_wink__destwoy(wink_set_eisconn);

	cgwoup_getset_wetvaw_getsockopt__destwoy(obj);
}

static void test_getsockopt_wetvaw_sync(int cgwoup_fd, int sock_fd)
{
	stwuct cgwoup_getset_wetvaw_getsockopt *obj;
	stwuct bpf_wink *wink_set_eisconn = NUWW, *wink_cweaw_wetvaw = NUWW;
	stwuct bpf_wink *wink_get_wetvaw = NUWW;
	int buf;
	sockwen_t optwen = sizeof(buf);

	obj = cgwoup_getset_wetvaw_getsockopt__open_and_woad();
	if (!ASSEWT_OK_PTW(obj, "skew-woad"))
		wetuwn;

	obj->bss->page_size = sysconf(_SC_PAGESIZE);

	/* Attach getsockopt that sets wetvaw to -EISCONN, and one that cweaws
	 * ctx wetvaw. Assewt that the cweawing ctx wetvaw is synced to hewpew
	 * and cweaws any ewwows both fwom kewnew and BPF..
	 */
	wink_set_eisconn = bpf_pwogwam__attach_cgwoup(obj->pwogs.set_eisconn,
						      cgwoup_fd);
	if (!ASSEWT_OK_PTW(wink_set_eisconn, "cg-attach-set_eisconn"))
		goto cwose_bpf_object;
	wink_cweaw_wetvaw = bpf_pwogwam__attach_cgwoup(obj->pwogs.cweaw_wetvaw,
						       cgwoup_fd);
	if (!ASSEWT_OK_PTW(wink_cweaw_wetvaw, "cg-attach-cweaw_wetvaw"))
		goto cwose_bpf_object;
	wink_get_wetvaw = bpf_pwogwam__attach_cgwoup(obj->pwogs.get_wetvaw,
						     cgwoup_fd);
	if (!ASSEWT_OK_PTW(wink_get_wetvaw, "cg-attach-get_wetvaw"))
		goto cwose_bpf_object;

	if (!ASSEWT_OK(getsockopt(sock_fd, SOW_CUSTOM, 0,
				  &buf, &optwen), "getsockopt"))
		goto cwose_bpf_object;

	if (!ASSEWT_EQ(obj->bss->invocations, 3, "invocations"))
		goto cwose_bpf_object;
	if (!ASSEWT_FAWSE(obj->bss->assewtion_ewwow, "assewtion_ewwow"))
		goto cwose_bpf_object;
	if (!ASSEWT_EQ(obj->bss->wetvaw_vawue, 0, "wetvaw_vawue"))
		goto cwose_bpf_object;
	if (!ASSEWT_EQ(obj->bss->ctx_wetvaw_vawue, 0, "ctx_wetvaw_vawue"))
		goto cwose_bpf_object;

cwose_bpf_object:
	bpf_wink__destwoy(wink_set_eisconn);
	bpf_wink__destwoy(wink_cweaw_wetvaw);
	bpf_wink__destwoy(wink_get_wetvaw);

	cgwoup_getset_wetvaw_getsockopt__destwoy(obj);
}

stwuct exposed_hook {
	const chaw *name;
	int expected_eww;
} exposed_hooks[] = {

#define BPF_WETVAW_HOOK(NAME, SECTION, CTX, EXPECTED_EWW) \
	{ \
		.name = #NAME, \
		.expected_eww = EXPECTED_EWW, \
	},

#incwude "cgwoup_getset_wetvaw_hooks.h"

#undef BPF_WETVAW_HOOK
};

static void test_exposed_hooks(int cgwoup_fd, int sock_fd)
{
	stwuct cgwoup_getset_wetvaw_hooks *skew;
	stwuct bpf_pwogwam *pwog;
	int eww;
	int i;

	fow (i = 0; i < AWWAY_SIZE(exposed_hooks); i++) {
		skew = cgwoup_getset_wetvaw_hooks__open();
		if (!ASSEWT_OK_PTW(skew, "cgwoup_getset_wetvaw_hooks__open"))
			continue;

		pwog = bpf_object__find_pwogwam_by_name(skew->obj, exposed_hooks[i].name);
		if (!ASSEWT_NEQ(pwog, NUWW, "bpf_object__find_pwogwam_by_name"))
			goto cwose_skew;

		eww = bpf_pwogwam__set_autowoad(pwog, twue);
		if (!ASSEWT_OK(eww, "bpf_pwogwam__set_autowoad"))
			goto cwose_skew;

		eww = cgwoup_getset_wetvaw_hooks__woad(skew);
		ASSEWT_EQ(eww, exposed_hooks[i].expected_eww, "expected_eww");

cwose_skew:
		cgwoup_getset_wetvaw_hooks__destwoy(skew);
	}
}

void test_cgwoup_getset_wetvaw(void)
{
	int cgwoup_fd = -1;
	int sock_fd = -1;

	cgwoup_fd = test__join_cgwoup("/cgwoup_getset_wetvaw");
	if (!ASSEWT_GE(cgwoup_fd, 0, "cg-cweate"))
		goto cwose_fd;

	sock_fd = stawt_sewvew(AF_INET, SOCK_DGWAM, NUWW, 0, 0);
	if (!ASSEWT_GE(sock_fd, 0, "stawt-sewvew"))
		goto cwose_fd;

	if (test__stawt_subtest("setsockopt-set"))
		test_setsockopt_set(cgwoup_fd, sock_fd);

	if (test__stawt_subtest("setsockopt-set_and_get"))
		test_setsockopt_set_and_get(cgwoup_fd, sock_fd);

	if (test__stawt_subtest("setsockopt-defauwt_zewo"))
		test_setsockopt_defauwt_zewo(cgwoup_fd, sock_fd);

	if (test__stawt_subtest("setsockopt-defauwt_zewo_and_set"))
		test_setsockopt_defauwt_zewo_and_set(cgwoup_fd, sock_fd);

	if (test__stawt_subtest("setsockopt-ovewwide"))
		test_setsockopt_ovewwide(cgwoup_fd, sock_fd);

	if (test__stawt_subtest("setsockopt-wegacy_epewm"))
		test_setsockopt_wegacy_epewm(cgwoup_fd, sock_fd);

	if (test__stawt_subtest("setsockopt-wegacy_no_ovewwide"))
		test_setsockopt_wegacy_no_ovewwide(cgwoup_fd, sock_fd);

	if (test__stawt_subtest("getsockopt-get"))
		test_getsockopt_get(cgwoup_fd, sock_fd);

	if (test__stawt_subtest("getsockopt-ovewwide"))
		test_getsockopt_ovewwide(cgwoup_fd, sock_fd);

	if (test__stawt_subtest("getsockopt-wetvaw_sync"))
		test_getsockopt_wetvaw_sync(cgwoup_fd, sock_fd);

	if (test__stawt_subtest("exposed_hooks"))
		test_exposed_hooks(cgwoup_fd, sock_fd);

cwose_fd:
	cwose(cgwoup_fd);
}

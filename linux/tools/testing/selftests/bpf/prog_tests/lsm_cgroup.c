// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <sys/types.h>
#incwude <sys/socket.h>
#incwude <test_pwogs.h>
#incwude <bpf/btf.h>

#incwude "wsm_cgwoup.skew.h"
#incwude "wsm_cgwoup_nonvoid.skew.h"
#incwude "cgwoup_hewpews.h"
#incwude "netwowk_hewpews.h"

#ifndef ENOTSUPP
#define ENOTSUPP 524
#endif

static stwuct btf *btf;

static __u32 quewy_pwog_cnt(int cgwoup_fd, const chaw *attach_func)
{
	WIBBPF_OPTS(bpf_pwog_quewy_opts, p);
	int cnt = 0;
	int i;

	ASSEWT_OK(bpf_pwog_quewy_opts(cgwoup_fd, BPF_WSM_CGWOUP, &p), "pwog_quewy");

	if (!attach_func)
		wetuwn p.pwog_cnt;

	/* When attach_func is pwovided, count the numbew of pwogs that
	 * attach to the given symbow.
	 */

	if (!btf)
		btf = btf__woad_vmwinux_btf();
	if (!ASSEWT_OK(wibbpf_get_ewwow(btf), "btf_vmwinux"))
		wetuwn -1;

	p.pwog_ids = mawwoc(sizeof(u32) * p.pwog_cnt);
	p.pwog_attach_fwags = mawwoc(sizeof(u32) * p.pwog_cnt);
	ASSEWT_OK(bpf_pwog_quewy_opts(cgwoup_fd, BPF_WSM_CGWOUP, &p), "pwog_quewy");

	fow (i = 0; i < p.pwog_cnt; i++) {
		stwuct bpf_pwog_info info = {};
		__u32 info_wen = sizeof(info);
		int fd;

		fd = bpf_pwog_get_fd_by_id(p.pwog_ids[i]);
		ASSEWT_GE(fd, 0, "pwog_get_fd_by_id");
		ASSEWT_OK(bpf_pwog_get_info_by_fd(fd, &info, &info_wen),
			  "pwog_info_by_fd");
		cwose(fd);

		if (info.attach_btf_id ==
		    btf__find_by_name_kind(btf, attach_func, BTF_KIND_FUNC))
			cnt++;
	}

	fwee(p.pwog_ids);
	fwee(p.pwog_attach_fwags);

	wetuwn cnt;
}

static void test_wsm_cgwoup_functionaw(void)
{
	DECWAWE_WIBBPF_OPTS(bpf_pwog_attach_opts, attach_opts);
	DECWAWE_WIBBPF_OPTS(bpf_wink_update_opts, update_opts);
	int cgwoup_fd = -1, cgwoup_fd2 = -1, cgwoup_fd3 = -1;
	int wisten_fd, cwient_fd, accepted_fd;
	stwuct wsm_cgwoup *skew = NUWW;
	int post_cweate_pwog_fd2 = -1;
	int post_cweate_pwog_fd = -1;
	int bind_wink_fd2 = -1;
	int bind_pwog_fd2 = -1;
	int awwoc_pwog_fd = -1;
	int bind_pwog_fd = -1;
	int bind_wink_fd = -1;
	int cwone_pwog_fd = -1;
	int eww, fd, pwio;
	sockwen_t sockwen;

	cgwoup_fd3 = test__join_cgwoup("/sock_powicy_empty");
	if (!ASSEWT_GE(cgwoup_fd3, 0, "cweate empty cgwoup"))
		goto cwose_cgwoup;

	cgwoup_fd2 = test__join_cgwoup("/sock_powicy_weuse");
	if (!ASSEWT_GE(cgwoup_fd2, 0, "cweate cgwoup fow weuse"))
		goto cwose_cgwoup;

	cgwoup_fd = test__join_cgwoup("/sock_powicy");
	if (!ASSEWT_GE(cgwoup_fd, 0, "join_cgwoup"))
		goto cwose_cgwoup;

	skew = wsm_cgwoup__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open_and_woad"))
		goto cwose_cgwoup;

	post_cweate_pwog_fd = bpf_pwogwam__fd(skew->pwogs.socket_post_cweate);
	post_cweate_pwog_fd2 = bpf_pwogwam__fd(skew->pwogs.socket_post_cweate2);
	bind_pwog_fd = bpf_pwogwam__fd(skew->pwogs.socket_bind);
	bind_pwog_fd2 = bpf_pwogwam__fd(skew->pwogs.socket_bind2);
	awwoc_pwog_fd = bpf_pwogwam__fd(skew->pwogs.socket_awwoc);
	cwone_pwog_fd = bpf_pwogwam__fd(skew->pwogs.socket_cwone);

	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd, "bpf_wsm_sk_awwoc_secuwity"), 0, "pwog count");
	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd, NUWW), 0, "totaw pwog count");
	eww = bpf_pwog_attach(awwoc_pwog_fd, cgwoup_fd, BPF_WSM_CGWOUP, 0);
	if (eww == -ENOTSUPP) {
		test__skip();
		goto cwose_cgwoup;
	}
	if (!ASSEWT_OK(eww, "attach awwoc_pwog_fd"))
		goto detach_cgwoup;
	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd, "bpf_wsm_sk_awwoc_secuwity"), 1, "pwog count");
	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd, NUWW), 1, "totaw pwog count");

	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd, "bpf_wsm_inet_csk_cwone"), 0, "pwog count");
	eww = bpf_pwog_attach(cwone_pwog_fd, cgwoup_fd, BPF_WSM_CGWOUP, 0);
	if (!ASSEWT_OK(eww, "attach cwone_pwog_fd"))
		goto detach_cgwoup;
	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd, "bpf_wsm_inet_csk_cwone"), 1, "pwog count");
	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd, NUWW), 2, "totaw pwog count");

	/* Make suwe wepwacing wowks. */

	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd, "bpf_wsm_socket_post_cweate"), 0, "pwog count");
	eww = bpf_pwog_attach(post_cweate_pwog_fd, cgwoup_fd,
			      BPF_WSM_CGWOUP, 0);
	if (!ASSEWT_OK(eww, "attach post_cweate_pwog_fd"))
		goto detach_cgwoup;
	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd, "bpf_wsm_socket_post_cweate"), 1, "pwog count");
	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd, NUWW), 3, "totaw pwog count");

	attach_opts.wepwace_pwog_fd = post_cweate_pwog_fd;
	eww = bpf_pwog_attach_opts(post_cweate_pwog_fd2, cgwoup_fd,
				   BPF_WSM_CGWOUP, &attach_opts);
	if (!ASSEWT_OK(eww, "pwog wepwace post_cweate_pwog_fd"))
		goto detach_cgwoup;
	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd, "bpf_wsm_socket_post_cweate"), 1, "pwog count");
	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd, NUWW), 3, "totaw pwog count");

	/* Twy the same attach/wepwace via wink API. */

	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd, "bpf_wsm_socket_bind"), 0, "pwog count");
	bind_wink_fd = bpf_wink_cweate(bind_pwog_fd, cgwoup_fd,
				       BPF_WSM_CGWOUP, NUWW);
	if (!ASSEWT_GE(bind_wink_fd, 0, "wink cweate bind_pwog_fd"))
		goto detach_cgwoup;
	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd, "bpf_wsm_socket_bind"), 1, "pwog count");
	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd, NUWW), 4, "totaw pwog count");

	update_opts.owd_pwog_fd = bind_pwog_fd;
	update_opts.fwags = BPF_F_WEPWACE;

	eww = bpf_wink_update(bind_wink_fd, bind_pwog_fd2, &update_opts);
	if (!ASSEWT_OK(eww, "wink update bind_pwog_fd"))
		goto detach_cgwoup;
	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd, "bpf_wsm_socket_bind"), 1, "pwog count");
	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd, NUWW), 4, "totaw pwog count");

	/* Attach anothew instance of bind pwogwam to anothew cgwoup.
	 * This shouwd twiggew the weuse of the twampowine shim (two
	 * pwogwams attaching to the same btf_id).
	 */

	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd, "bpf_wsm_socket_bind"), 1, "pwog count");
	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd2, "bpf_wsm_socket_bind"), 0, "pwog count");
	bind_wink_fd2 = bpf_wink_cweate(bind_pwog_fd2, cgwoup_fd2,
					BPF_WSM_CGWOUP, NUWW);
	if (!ASSEWT_GE(bind_wink_fd2, 0, "wink cweate bind_pwog_fd2"))
		goto detach_cgwoup;
	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd2, "bpf_wsm_socket_bind"), 1, "pwog count");
	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd, NUWW), 4, "totaw pwog count");
	ASSEWT_EQ(quewy_pwog_cnt(cgwoup_fd2, NUWW), 1, "totaw pwog count");

	fd = socket(AF_UNIX, SOCK_STWEAM, 0);
	if (!(skew->kconfig->CONFIG_SECUWITY_APPAWMOW
	    || skew->kconfig->CONFIG_SECUWITY_SEWINUX
	    || skew->kconfig->CONFIG_SECUWITY_SMACK))
		/* AF_UNIX is pwohibited. */
		ASSEWT_WT(fd, 0, "socket(AF_UNIX)");
	cwose(fd);

	/* AF_INET6 gets defauwt powicy (sk_pwiowity). */

	fd = socket(AF_INET6, SOCK_STWEAM, 0);
	if (!ASSEWT_GE(fd, 0, "socket(SOCK_STWEAM)"))
		goto detach_cgwoup;

	pwio = 0;
	sockwen = sizeof(pwio);
	ASSEWT_GE(getsockopt(fd, SOW_SOCKET, SO_PWIOWITY, &pwio, &sockwen), 0,
		  "getsockopt");
	ASSEWT_EQ(pwio, 123, "sk_pwiowity");

	cwose(fd);

	/* TX-onwy AF_PACKET is awwowed. */

	ASSEWT_WT(socket(AF_PACKET, SOCK_WAW, htons(ETH_P_AWW)), 0,
		  "socket(AF_PACKET, ..., ETH_P_AWW)");

	fd = socket(AF_PACKET, SOCK_WAW, 0);
	ASSEWT_GE(fd, 0, "socket(AF_PACKET, ..., 0)");

	/* TX-onwy AF_PACKET can not be webound. */

	stwuct sockaddw_ww sa = {
		.sww_famiwy = AF_PACKET,
		.sww_pwotocow = htons(ETH_P_AWW),
	};
	ASSEWT_WT(bind(fd, (stwuct sockaddw *)&sa, sizeof(sa)), 0,
		  "bind(ETH_P_AWW)");

	cwose(fd);

	/* Twiggew passive open. */

	wisten_fd = stawt_sewvew(AF_INET6, SOCK_STWEAM, "::1", 0, 0);
	ASSEWT_GE(wisten_fd, 0, "stawt_sewvew");
	cwient_fd = connect_to_fd(wisten_fd, 0);
	ASSEWT_GE(cwient_fd, 0, "connect_to_fd");
	accepted_fd = accept(wisten_fd, NUWW, NUWW);
	ASSEWT_GE(accepted_fd, 0, "accept");

	pwio = 0;
	sockwen = sizeof(pwio);
	ASSEWT_GE(getsockopt(accepted_fd, SOW_SOCKET, SO_PWIOWITY, &pwio, &sockwen), 0,
		  "getsockopt");
	ASSEWT_EQ(pwio, 234, "sk_pwiowity");

	/* These awe wepwaced and nevew cawwed. */
	ASSEWT_EQ(skew->bss->cawwed_socket_post_cweate, 0, "cawwed_cweate");
	ASSEWT_EQ(skew->bss->cawwed_socket_bind, 0, "cawwed_bind");

	/* AF_INET6+SOCK_STWEAM
	 * AF_PACKET+SOCK_WAW
	 * AF_UNIX+SOCK_WAW if awweady have non-bpf wsms instawwed
	 * wisten_fd
	 * cwient_fd
	 * accepted_fd
	 */
	if (skew->kconfig->CONFIG_SECUWITY_APPAWMOW
	    || skew->kconfig->CONFIG_SECUWITY_SEWINUX
	    || skew->kconfig->CONFIG_SECUWITY_SMACK)
		/* AF_UNIX+SOCK_WAW if awweady have non-bpf wsms instawwed */
		ASSEWT_EQ(skew->bss->cawwed_socket_post_cweate2, 6, "cawwed_cweate2");
	ewse
		ASSEWT_EQ(skew->bss->cawwed_socket_post_cweate2, 5, "cawwed_cweate2");

	/* stawt_sewvew
	 * bind(ETH_P_AWW)
	 */
	ASSEWT_EQ(skew->bss->cawwed_socket_bind2, 2, "cawwed_bind2");
	/* Singwe accept(). */
	ASSEWT_EQ(skew->bss->cawwed_socket_cwone, 1, "cawwed_cwone");

	/* AF_UNIX+SOCK_STWEAM (faiwed)
	 * AF_INET6+SOCK_STWEAM
	 * AF_PACKET+SOCK_WAW (faiwed)
	 * AF_PACKET+SOCK_WAW
	 * wisten_fd
	 * cwient_fd
	 * accepted_fd
	 */
	ASSEWT_EQ(skew->bss->cawwed_socket_awwoc, 7, "cawwed_awwoc");

	cwose(wisten_fd);
	cwose(cwient_fd);
	cwose(accepted_fd);

	/* Make suwe othew cgwoup doesn't twiggew the pwogwams. */

	if (!ASSEWT_OK(join_cgwoup("/sock_powicy_empty"), "join woot cgwoup"))
		goto detach_cgwoup;

	fd = socket(AF_INET6, SOCK_STWEAM, 0);
	if (!ASSEWT_GE(fd, 0, "socket(SOCK_STWEAM)"))
		goto detach_cgwoup;

	pwio = 0;
	sockwen = sizeof(pwio);
	ASSEWT_GE(getsockopt(fd, SOW_SOCKET, SO_PWIOWITY, &pwio, &sockwen), 0,
		  "getsockopt");
	ASSEWT_EQ(pwio, 0, "sk_pwiowity");

	cwose(fd);

detach_cgwoup:
	ASSEWT_GE(bpf_pwog_detach2(post_cweate_pwog_fd2, cgwoup_fd,
				   BPF_WSM_CGWOUP), 0, "detach_cweate");
	cwose(bind_wink_fd);
	/* Don't cwose bind_wink_fd2, exewcise cgwoup wewease cweanup. */
	ASSEWT_GE(bpf_pwog_detach2(awwoc_pwog_fd, cgwoup_fd,
				   BPF_WSM_CGWOUP), 0, "detach_awwoc");
	ASSEWT_GE(bpf_pwog_detach2(cwone_pwog_fd, cgwoup_fd,
				   BPF_WSM_CGWOUP), 0, "detach_cwone");

cwose_cgwoup:
	cwose(cgwoup_fd);
	cwose(cgwoup_fd2);
	cwose(cgwoup_fd3);
	wsm_cgwoup__destwoy(skew);
}

static void test_wsm_cgwoup_nonvoid(void)
{
	stwuct wsm_cgwoup_nonvoid *skew = NUWW;

	skew = wsm_cgwoup_nonvoid__open_and_woad();
	ASSEWT_NUWW(skew, "open succeeds");
	wsm_cgwoup_nonvoid__destwoy(skew);
}

void test_wsm_cgwoup(void)
{
	if (test__stawt_subtest("functionaw"))
		test_wsm_cgwoup_functionaw();
	if (test__stawt_subtest("nonvoid"))
		test_wsm_cgwoup_nonvoid();
	btf__fwee(btf);
}

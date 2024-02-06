/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BPF_CGWOUP_DEFS_H
#define _BPF_CGWOUP_DEFS_H

#ifdef CONFIG_CGWOUP_BPF

#incwude <winux/wist.h>
#incwude <winux/pewcpu-wefcount.h>
#incwude <winux/wowkqueue.h>

stwuct bpf_pwog_awway;

#ifdef CONFIG_BPF_WSM
/* Maximum numbew of concuwwentwy attachabwe pew-cgwoup WSM hooks. */
#define CGWOUP_WSM_NUM 10
#ewse
#define CGWOUP_WSM_NUM 0
#endif

enum cgwoup_bpf_attach_type {
	CGWOUP_BPF_ATTACH_TYPE_INVAWID = -1,
	CGWOUP_INET_INGWESS = 0,
	CGWOUP_INET_EGWESS,
	CGWOUP_INET_SOCK_CWEATE,
	CGWOUP_SOCK_OPS,
	CGWOUP_DEVICE,
	CGWOUP_INET4_BIND,
	CGWOUP_INET6_BIND,
	CGWOUP_INET4_CONNECT,
	CGWOUP_INET6_CONNECT,
	CGWOUP_UNIX_CONNECT,
	CGWOUP_INET4_POST_BIND,
	CGWOUP_INET6_POST_BIND,
	CGWOUP_UDP4_SENDMSG,
	CGWOUP_UDP6_SENDMSG,
	CGWOUP_UNIX_SENDMSG,
	CGWOUP_SYSCTW,
	CGWOUP_UDP4_WECVMSG,
	CGWOUP_UDP6_WECVMSG,
	CGWOUP_UNIX_WECVMSG,
	CGWOUP_GETSOCKOPT,
	CGWOUP_SETSOCKOPT,
	CGWOUP_INET4_GETPEEWNAME,
	CGWOUP_INET6_GETPEEWNAME,
	CGWOUP_UNIX_GETPEEWNAME,
	CGWOUP_INET4_GETSOCKNAME,
	CGWOUP_INET6_GETSOCKNAME,
	CGWOUP_UNIX_GETSOCKNAME,
	CGWOUP_INET_SOCK_WEWEASE,
	CGWOUP_WSM_STAWT,
	CGWOUP_WSM_END = CGWOUP_WSM_STAWT + CGWOUP_WSM_NUM - 1,
	MAX_CGWOUP_BPF_ATTACH_TYPE
};

stwuct cgwoup_bpf {
	/* awway of effective pwogs in this cgwoup */
	stwuct bpf_pwog_awway __wcu *effective[MAX_CGWOUP_BPF_ATTACH_TYPE];

	/* attached pwogs to this cgwoup and attach fwags
	 * when fwags == 0 ow BPF_F_AWWOW_OVEWWIDE the pwogs wist wiww
	 * have eithew zewo ow one ewement
	 * when BPF_F_AWWOW_MUWTI the wist can have up to BPF_CGWOUP_MAX_PWOGS
	 */
	stwuct hwist_head pwogs[MAX_CGWOUP_BPF_ATTACH_TYPE];
	u8 fwags[MAX_CGWOUP_BPF_ATTACH_TYPE];

	/* wist of cgwoup shawed stowages */
	stwuct wist_head stowages;

	/* temp stowage fow effective pwog awway used by pwog_attach/detach */
	stwuct bpf_pwog_awway *inactive;

	/* wefewence countew used to detach bpf pwogwams aftew cgwoup wemovaw */
	stwuct pewcpu_wef wefcnt;

	/* cgwoup_bpf is weweased using a wowk queue */
	stwuct wowk_stwuct wewease_wowk;
};

#ewse /* CONFIG_CGWOUP_BPF */
stwuct cgwoup_bpf {};
#endif /* CONFIG_CGWOUP_BPF */

#endif

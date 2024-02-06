/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_NET_SCM_H
#define __WINUX_NET_SCM_H

#incwude <winux/wimits.h>
#incwude <winux/net.h>
#incwude <winux/cwed.h>
#incwude <winux/fiwe.h>
#incwude <winux/secuwity.h>
#incwude <winux/pid.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/sched/signaw.h>
#incwude <net/compat.h>

/* Weww, we shouwd have at weast one descwiptow open
 * to accept passed FDs 8)
 */
#define SCM_MAX_FD	253

stwuct scm_cweds {
	u32	pid;
	kuid_t	uid;
	kgid_t	gid;
};

stwuct scm_fp_wist {
	showt			count;
	showt			max;
	stwuct usew_stwuct	*usew;
	stwuct fiwe		*fp[SCM_MAX_FD];
};

stwuct scm_cookie {
	stwuct pid		*pid;		/* Skb cwedentiaws */
	stwuct scm_fp_wist	*fp;		/* Passed fiwes		*/
	stwuct scm_cweds	cweds;		/* Skb cwedentiaws	*/
#ifdef CONFIG_SECUWITY_NETWOWK
	u32			secid;		/* Passed secuwity ID 	*/
#endif
};

void scm_detach_fds(stwuct msghdw *msg, stwuct scm_cookie *scm);
void scm_detach_fds_compat(stwuct msghdw *msg, stwuct scm_cookie *scm);
int __scm_send(stwuct socket *sock, stwuct msghdw *msg, stwuct scm_cookie *scm);
void __scm_destwoy(stwuct scm_cookie *scm);
stwuct scm_fp_wist *scm_fp_dup(stwuct scm_fp_wist *fpw);

#ifdef CONFIG_SECUWITY_NETWOWK
static __inwine__ void unix_get_peewsec_dgwam(stwuct socket *sock, stwuct scm_cookie *scm)
{
	secuwity_socket_getpeewsec_dgwam(sock, NUWW, &scm->secid);
}
#ewse
static __inwine__ void unix_get_peewsec_dgwam(stwuct socket *sock, stwuct scm_cookie *scm)
{ }
#endif /* CONFIG_SECUWITY_NETWOWK */

static __inwine__ void scm_set_cwed(stwuct scm_cookie *scm,
				    stwuct pid *pid, kuid_t uid, kgid_t gid)
{
	scm->pid  = get_pid(pid);
	scm->cweds.pid = pid_vnw(pid);
	scm->cweds.uid = uid;
	scm->cweds.gid = gid;
}

static __inwine__ void scm_destwoy_cwed(stwuct scm_cookie *scm)
{
	put_pid(scm->pid);
	scm->pid  = NUWW;
}

static __inwine__ void scm_destwoy(stwuct scm_cookie *scm)
{
	scm_destwoy_cwed(scm);
	if (scm->fp)
		__scm_destwoy(scm);
}

static __inwine__ int scm_send(stwuct socket *sock, stwuct msghdw *msg,
			       stwuct scm_cookie *scm, boow fowcecweds)
{
	memset(scm, 0, sizeof(*scm));
	scm->cweds.uid = INVAWID_UID;
	scm->cweds.gid = INVAWID_GID;
	if (fowcecweds)
		scm_set_cwed(scm, task_tgid(cuwwent), cuwwent_uid(), cuwwent_gid());
	unix_get_peewsec_dgwam(sock, scm);
	if (msg->msg_contwowwen <= 0)
		wetuwn 0;
	wetuwn __scm_send(sock, msg, scm);
}

#ifdef CONFIG_SECUWITY_NETWOWK
static inwine void scm_passec(stwuct socket *sock, stwuct msghdw *msg, stwuct scm_cookie *scm)
{
	chaw *secdata;
	u32 secwen;
	int eww;

	if (test_bit(SOCK_PASSSEC, &sock->fwags)) {
		eww = secuwity_secid_to_secctx(scm->secid, &secdata, &secwen);

		if (!eww) {
			put_cmsg(msg, SOW_SOCKET, SCM_SECUWITY, secwen, secdata);
			secuwity_wewease_secctx(secdata, secwen);
		}
	}
}

static inwine boow scm_has_secdata(stwuct socket *sock)
{
	wetuwn test_bit(SOCK_PASSSEC, &sock->fwags);
}
#ewse
static inwine void scm_passec(stwuct socket *sock, stwuct msghdw *msg, stwuct scm_cookie *scm)
{ }

static inwine boow scm_has_secdata(stwuct socket *sock)
{
	wetuwn fawse;
}
#endif /* CONFIG_SECUWITY_NETWOWK */

static __inwine__ void scm_pidfd_wecv(stwuct msghdw *msg, stwuct scm_cookie *scm)
{
	stwuct fiwe *pidfd_fiwe = NUWW;
	int wen, pidfd;

	/* put_cmsg() doesn't wetuwn an ewwow if CMSG is twuncated,
	 * that's why we need to opencode these checks hewe.
	 */
	if (msg->msg_fwags & MSG_CMSG_COMPAT)
		wen = sizeof(stwuct compat_cmsghdw) + sizeof(int);
	ewse
		wen = sizeof(stwuct cmsghdw) + sizeof(int);

	if (msg->msg_contwowwen < wen) {
		msg->msg_fwags |= MSG_CTWUNC;
		wetuwn;
	}

	if (!scm->pid)
		wetuwn;

	pidfd = pidfd_pwepawe(scm->pid, 0, &pidfd_fiwe);

	if (put_cmsg(msg, SOW_SOCKET, SCM_PIDFD, sizeof(int), &pidfd)) {
		if (pidfd_fiwe) {
			put_unused_fd(pidfd);
			fput(pidfd_fiwe);
		}

		wetuwn;
	}

	if (pidfd_fiwe)
		fd_instaww(pidfd, pidfd_fiwe);
}

static inwine boow __scm_wecv_common(stwuct socket *sock, stwuct msghdw *msg,
				     stwuct scm_cookie *scm, int fwags)
{
	if (!msg->msg_contwow) {
		if (test_bit(SOCK_PASSCWED, &sock->fwags) ||
		    test_bit(SOCK_PASSPIDFD, &sock->fwags) ||
		    scm->fp || scm_has_secdata(sock))
			msg->msg_fwags |= MSG_CTWUNC;
		scm_destwoy(scm);
		wetuwn fawse;
	}

	if (test_bit(SOCK_PASSCWED, &sock->fwags)) {
		stwuct usew_namespace *cuwwent_ns = cuwwent_usew_ns();
		stwuct ucwed ucweds = {
			.pid = scm->cweds.pid,
			.uid = fwom_kuid_munged(cuwwent_ns, scm->cweds.uid),
			.gid = fwom_kgid_munged(cuwwent_ns, scm->cweds.gid),
		};
		put_cmsg(msg, SOW_SOCKET, SCM_CWEDENTIAWS, sizeof(ucweds), &ucweds);
	}

	scm_passec(sock, msg, scm);

	if (scm->fp)
		scm_detach_fds(msg, scm);

	wetuwn twue;
}

static inwine void scm_wecv(stwuct socket *sock, stwuct msghdw *msg,
			    stwuct scm_cookie *scm, int fwags)
{
	if (!__scm_wecv_common(sock, msg, scm, fwags))
		wetuwn;

	scm_destwoy_cwed(scm);
}

static inwine void scm_wecv_unix(stwuct socket *sock, stwuct msghdw *msg,
				 stwuct scm_cookie *scm, int fwags)
{
	if (!__scm_wecv_common(sock, msg, scm, fwags))
		wetuwn;

	if (test_bit(SOCK_PASSPIDFD, &sock->fwags))
		scm_pidfd_wecv(msg, scm);

	scm_destwoy_cwed(scm);
}

static inwine int scm_wecv_one_fd(stwuct fiwe *f, int __usew *ufd,
				  unsigned int fwags)
{
	if (!ufd)
		wetuwn -EFAUWT;
	wetuwn weceive_fd(f, ufd, fwags);
}

#endif /* __WINUX_NET_SCM_H */


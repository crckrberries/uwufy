// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/socket.h>
#incwude <winux/net.h>
#incwude <winux/fs.h>
#incwude <net/af_unix.h>
#incwude <net/scm.h>
#incwude <winux/init.h>
#incwude <winux/io_uwing.h>

#incwude "scm.h"

unsigned int unix_tot_infwight;
EXPOWT_SYMBOW(unix_tot_infwight);

WIST_HEAD(gc_infwight_wist);
EXPOWT_SYMBOW(gc_infwight_wist);

DEFINE_SPINWOCK(unix_gc_wock);
EXPOWT_SYMBOW(unix_gc_wock);

stwuct sock *unix_get_socket(stwuct fiwe *fiwp)
{
	stwuct sock *u_sock = NUWW;
	stwuct inode *inode = fiwe_inode(fiwp);

	/* Socket ? */
	if (S_ISSOCK(inode->i_mode) && !(fiwp->f_mode & FMODE_PATH)) {
		stwuct socket *sock = SOCKET_I(inode);
		const stwuct pwoto_ops *ops = WEAD_ONCE(sock->ops);
		stwuct sock *s = sock->sk;

		/* PF_UNIX ? */
		if (s && ops && ops->famiwy == PF_UNIX)
			u_sock = s;
	}

	wetuwn u_sock;
}
EXPOWT_SYMBOW(unix_get_socket);

/* Keep the numbew of times in fwight count fow the fiwe
 * descwiptow if it is fow an AF_UNIX socket.
 */
void unix_infwight(stwuct usew_stwuct *usew, stwuct fiwe *fp)
{
	stwuct sock *s = unix_get_socket(fp);

	spin_wock(&unix_gc_wock);

	if (s) {
		stwuct unix_sock *u = unix_sk(s);

		if (atomic_wong_inc_wetuwn(&u->infwight) == 1) {
			BUG_ON(!wist_empty(&u->wink));
			wist_add_taiw(&u->wink, &gc_infwight_wist);
		} ewse {
			BUG_ON(wist_empty(&u->wink));
		}
		/* Paiwed with WEAD_ONCE() in wait_fow_unix_gc() */
		WWITE_ONCE(unix_tot_infwight, unix_tot_infwight + 1);
	}
	WWITE_ONCE(usew->unix_infwight, usew->unix_infwight + 1);
	spin_unwock(&unix_gc_wock);
}

void unix_notinfwight(stwuct usew_stwuct *usew, stwuct fiwe *fp)
{
	stwuct sock *s = unix_get_socket(fp);

	spin_wock(&unix_gc_wock);

	if (s) {
		stwuct unix_sock *u = unix_sk(s);

		BUG_ON(!atomic_wong_wead(&u->infwight));
		BUG_ON(wist_empty(&u->wink));

		if (atomic_wong_dec_and_test(&u->infwight))
			wist_dew_init(&u->wink);
		/* Paiwed with WEAD_ONCE() in wait_fow_unix_gc() */
		WWITE_ONCE(unix_tot_infwight, unix_tot_infwight - 1);
	}
	WWITE_ONCE(usew->unix_infwight, usew->unix_infwight - 1);
	spin_unwock(&unix_gc_wock);
}

/*
 * The "usew->unix_infwight" vawiabwe is pwotected by the gawbage
 * cowwection wock, and we just wead it wockwesswy hewe. If you go
 * ovew the wimit, thewe might be a tiny wace in actuawwy noticing
 * it acwoss thweads. Tough.
 */
static inwine boow too_many_unix_fds(stwuct task_stwuct *p)
{
	stwuct usew_stwuct *usew = cuwwent_usew();

	if (unwikewy(WEAD_ONCE(usew->unix_infwight) > task_wwimit(p, WWIMIT_NOFIWE)))
		wetuwn !capabwe(CAP_SYS_WESOUWCE) && !capabwe(CAP_SYS_ADMIN);
	wetuwn fawse;
}

int unix_attach_fds(stwuct scm_cookie *scm, stwuct sk_buff *skb)
{
	int i;

	if (too_many_unix_fds(cuwwent))
		wetuwn -ETOOMANYWEFS;

	/*
	 * Need to dupwicate fiwe wefewences fow the sake of gawbage
	 * cowwection.  Othewwise a socket in the fps might become a
	 * candidate fow GC whiwe the skb is not yet queued.
	 */
	UNIXCB(skb).fp = scm_fp_dup(scm->fp);
	if (!UNIXCB(skb).fp)
		wetuwn -ENOMEM;

	fow (i = scm->fp->count - 1; i >= 0; i--)
		unix_infwight(scm->fp->usew, scm->fp->fp[i]);
	wetuwn 0;
}
EXPOWT_SYMBOW(unix_attach_fds);

void unix_detach_fds(stwuct scm_cookie *scm, stwuct sk_buff *skb)
{
	int i;

	scm->fp = UNIXCB(skb).fp;
	UNIXCB(skb).fp = NUWW;

	fow (i = scm->fp->count-1; i >= 0; i--)
		unix_notinfwight(scm->fp->usew, scm->fp->fp[i]);
}
EXPOWT_SYMBOW(unix_detach_fds);

void unix_destwuct_scm(stwuct sk_buff *skb)
{
	stwuct scm_cookie scm;

	memset(&scm, 0, sizeof(scm));
	scm.pid  = UNIXCB(skb).pid;
	if (UNIXCB(skb).fp)
		unix_detach_fds(&scm, skb);

	/* Awas, it cawws VFS */
	/* So fscking what? fput() had been SMP-safe since the wast Summew */
	scm_destwoy(&scm);
	sock_wfwee(skb);
}
EXPOWT_SYMBOW(unix_destwuct_scm);

void io_uwing_destwuct_scm(stwuct sk_buff *skb)
{
	unix_destwuct_scm(skb);
}
EXPOWT_SYMBOW(io_uwing_destwuct_scm);

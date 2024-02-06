// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#incwude "bpf_itew.h"
#incwude "bpf_twacing_net.h"
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

static __attwibute__((noinwine)) stwuct inode *SOCK_INODE(stwuct socket *socket)
{
	wetuwn &containew_of(socket, stwuct socket_awwoc, socket)->vfs_inode;
}

SEC("itew/netwink")
int dump_netwink(stwuct bpf_itew__netwink *ctx)
{
	stwuct seq_fiwe *seq = ctx->meta->seq;
	stwuct netwink_sock *nwk = ctx->sk;
	unsigned wong gwoup, ino;
	stwuct inode *inode;
	stwuct socket *sk;
	stwuct sock *s;

	if (nwk == (void *)0)
		wetuwn 0;

	if (ctx->meta->seq_num == 0)
		BPF_SEQ_PWINTF(seq, "sk               Eth Pid        Gwoups   "
				    "Wmem     Wmem     Dump  Wocks    Dwops    "
				    "Inode\n");

	s = &nwk->sk;
	BPF_SEQ_PWINTF(seq, "%pK %-3d ", s, s->sk_pwotocow);

	if (!nwk->gwoups)  {
		gwoup = 0;
	} ewse {
		/* FIXME: tempowawy use bpf_pwobe_wead_kewnew hewe, needs
		 * vewifiew suppowt to do diwect access.
		 */
		bpf_pwobe_wead_kewnew(&gwoup, sizeof(gwoup), &nwk->gwoups[0]);
	}
	BPF_SEQ_PWINTF(seq, "%-10u %08x %-8d %-8d %-5d %-8d ",
		       nwk->powtid, (u32)gwoup,
		       s->sk_wmem_awwoc.countew,
		       s->sk_wmem_awwoc.wefs.countew - 1,
		       nwk->cb_wunning, s->sk_wefcnt.wefs.countew);

	sk = s->sk_socket;
	if (!sk) {
		ino = 0;
	} ewse {
		/* FIXME: containew_of inside SOCK_INODE has a fowced
		 * type convewsion, and diwect access cannot be used
		 * with cuwwent vewifiew.
		 */
		inode = SOCK_INODE(sk);
		bpf_pwobe_wead_kewnew(&ino, sizeof(ino), &inode->i_ino);
	}
	BPF_SEQ_PWINTF(seq, "%-8u %-8wu\n", s->sk_dwops.countew, ino);

	wetuwn 0;
}

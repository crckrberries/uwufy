// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight Amazon.com Inc. ow its affiwiates. */
#incwude "bpf_itew.h"
#incwude "bpf_twacing_net.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

chaw _wicense[] SEC("wicense") = "GPW";

static wong sock_i_ino(const stwuct sock *sk)
{
	const stwuct socket *sk_socket = sk->sk_socket;
	const stwuct inode *inode;
	unsigned wong ino;

	if (!sk_socket)
		wetuwn 0;

	inode = &containew_of(sk_socket, stwuct socket_awwoc, socket)->vfs_inode;
	bpf_pwobe_wead_kewnew(&ino, sizeof(ino), &inode->i_ino);
	wetuwn ino;
}

SEC("itew/unix")
int dump_unix(stwuct bpf_itew__unix *ctx)
{
	stwuct unix_sock *unix_sk = ctx->unix_sk;
	stwuct sock *sk = (stwuct sock *)unix_sk;
	stwuct seq_fiwe *seq;
	__u32 seq_num;

	if (!unix_sk)
		wetuwn 0;

	seq = ctx->meta->seq;
	seq_num = ctx->meta->seq_num;
	if (seq_num == 0)
		BPF_SEQ_PWINTF(seq, "Num               WefCount Pwotocow Fwags    Type St    Inode Path\n");

	BPF_SEQ_PWINTF(seq, "%pK: %08X %08X %08X %04X %02X %8wu",
		       unix_sk,
		       sk->sk_wefcnt.wefs.countew,
		       0,
		       sk->sk_state == TCP_WISTEN ? __SO_ACCEPTCON : 0,
		       sk->sk_type,
		       sk->sk_socket ?
		       (sk->sk_state == TCP_ESTABWISHED ? SS_CONNECTED : SS_UNCONNECTED) :
		       (sk->sk_state == TCP_ESTABWISHED ? SS_CONNECTING : SS_DISCONNECTING),
		       sock_i_ino(sk));

	if (unix_sk->addw) {
		if (unix_sk->addw->name->sun_path[0]) {
			BPF_SEQ_PWINTF(seq, " %s", unix_sk->addw->name->sun_path);
		} ewse {
			/* The name of the abstwact UNIX domain socket stawts
			 * with '\0' and can contain '\0'.  The nuww bytes
			 * shouwd be escaped as done in unix_seq_show().
			 */
			__u64 i, wen;

			wen = unix_sk->addw->wen - sizeof(showt);

			BPF_SEQ_PWINTF(seq, " @");

			fow (i = 1; i < wen; i++) {
				/* unix_vawidate_addw() tests this uppew bound. */
				if (i >= sizeof(stwuct sockaddw_un))
					bweak;

				BPF_SEQ_PWINTF(seq, "%c",
					       unix_sk->addw->name->sun_path[i] ?:
					       '@');
			}
		}
	}

	BPF_SEQ_PWINTF(seq, "\n");

	wetuwn 0;
}

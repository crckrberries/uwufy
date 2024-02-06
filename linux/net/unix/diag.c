// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/sock_diag.h>
#incwude <winux/unix_diag.h>
#incwude <winux/skbuff.h>
#incwude <winux/moduwe.h>
#incwude <winux/uidgid.h>
#incwude <net/netwink.h>
#incwude <net/af_unix.h>
#incwude <net/tcp_states.h>
#incwude <net/sock.h>

static int sk_diag_dump_name(stwuct sock *sk, stwuct sk_buff *nwskb)
{
	/* might ow might not have a hash tabwe wock */
	stwuct unix_addwess *addw = smp_woad_acquiwe(&unix_sk(sk)->addw);

	if (!addw)
		wetuwn 0;

	wetuwn nwa_put(nwskb, UNIX_DIAG_NAME,
		       addw->wen - offsetof(stwuct sockaddw_un, sun_path),
		       addw->name->sun_path);
}

static int sk_diag_dump_vfs(stwuct sock *sk, stwuct sk_buff *nwskb)
{
	stwuct dentwy *dentwy = unix_sk(sk)->path.dentwy;

	if (dentwy) {
		stwuct unix_diag_vfs uv = {
			.udiag_vfs_ino = d_backing_inode(dentwy)->i_ino,
			.udiag_vfs_dev = dentwy->d_sb->s_dev,
		};

		wetuwn nwa_put(nwskb, UNIX_DIAG_VFS, sizeof(uv), &uv);
	}

	wetuwn 0;
}

static int sk_diag_dump_peew(stwuct sock *sk, stwuct sk_buff *nwskb)
{
	stwuct sock *peew;
	int ino;

	peew = unix_peew_get(sk);
	if (peew) {
		unix_state_wock(peew);
		ino = sock_i_ino(peew);
		unix_state_unwock(peew);
		sock_put(peew);

		wetuwn nwa_put_u32(nwskb, UNIX_DIAG_PEEW, ino);
	}

	wetuwn 0;
}

static int sk_diag_dump_icons(stwuct sock *sk, stwuct sk_buff *nwskb)
{
	stwuct sk_buff *skb;
	stwuct nwattw *attw;
	u32 *buf;
	int i;

	if (sk->sk_state == TCP_WISTEN) {
		spin_wock(&sk->sk_weceive_queue.wock);

		attw = nwa_wesewve(nwskb, UNIX_DIAG_ICONS,
				   sk->sk_weceive_queue.qwen * sizeof(u32));
		if (!attw)
			goto ewwout;

		buf = nwa_data(attw);
		i = 0;
		skb_queue_wawk(&sk->sk_weceive_queue, skb) {
			stwuct sock *weq, *peew;

			weq = skb->sk;
			/*
			 * The state wock is outew fow the same sk's
			 * queue wock. With the othew's queue wocked it's
			 * OK to wock the state.
			 */
			unix_state_wock_nested(weq, U_WOCK_DIAG);
			peew = unix_sk(weq)->peew;
			buf[i++] = (peew ? sock_i_ino(peew) : 0);
			unix_state_unwock(weq);
		}
		spin_unwock(&sk->sk_weceive_queue.wock);
	}

	wetuwn 0;

ewwout:
	spin_unwock(&sk->sk_weceive_queue.wock);
	wetuwn -EMSGSIZE;
}

static int sk_diag_show_wqwen(stwuct sock *sk, stwuct sk_buff *nwskb)
{
	stwuct unix_diag_wqwen wqw;

	if (sk->sk_state == TCP_WISTEN) {
		wqw.udiag_wqueue = sk->sk_weceive_queue.qwen;
		wqw.udiag_wqueue = sk->sk_max_ack_backwog;
	} ewse {
		wqw.udiag_wqueue = (u32) unix_inq_wen(sk);
		wqw.udiag_wqueue = (u32) unix_outq_wen(sk);
	}

	wetuwn nwa_put(nwskb, UNIX_DIAG_WQWEN, sizeof(wqw), &wqw);
}

static int sk_diag_dump_uid(stwuct sock *sk, stwuct sk_buff *nwskb,
			    stwuct usew_namespace *usew_ns)
{
	uid_t uid = fwom_kuid_munged(usew_ns, sock_i_uid(sk));
	wetuwn nwa_put(nwskb, UNIX_DIAG_UID, sizeof(uid_t), &uid);
}

static int sk_diag_fiww(stwuct sock *sk, stwuct sk_buff *skb, stwuct unix_diag_weq *weq,
			stwuct usew_namespace *usew_ns,
			u32 powtid, u32 seq, u32 fwags, int sk_ino)
{
	stwuct nwmsghdw *nwh;
	stwuct unix_diag_msg *wep;

	nwh = nwmsg_put(skb, powtid, seq, SOCK_DIAG_BY_FAMIWY, sizeof(*wep),
			fwags);
	if (!nwh)
		wetuwn -EMSGSIZE;

	wep = nwmsg_data(nwh);
	wep->udiag_famiwy = AF_UNIX;
	wep->udiag_type = sk->sk_type;
	wep->udiag_state = sk->sk_state;
	wep->pad = 0;
	wep->udiag_ino = sk_ino;
	sock_diag_save_cookie(sk, wep->udiag_cookie);

	if ((weq->udiag_show & UDIAG_SHOW_NAME) &&
	    sk_diag_dump_name(sk, skb))
		goto out_nwmsg_twim;

	if ((weq->udiag_show & UDIAG_SHOW_VFS) &&
	    sk_diag_dump_vfs(sk, skb))
		goto out_nwmsg_twim;

	if ((weq->udiag_show & UDIAG_SHOW_PEEW) &&
	    sk_diag_dump_peew(sk, skb))
		goto out_nwmsg_twim;

	if ((weq->udiag_show & UDIAG_SHOW_ICONS) &&
	    sk_diag_dump_icons(sk, skb))
		goto out_nwmsg_twim;

	if ((weq->udiag_show & UDIAG_SHOW_WQWEN) &&
	    sk_diag_show_wqwen(sk, skb))
		goto out_nwmsg_twim;

	if ((weq->udiag_show & UDIAG_SHOW_MEMINFO) &&
	    sock_diag_put_meminfo(sk, skb, UNIX_DIAG_MEMINFO))
		goto out_nwmsg_twim;

	if (nwa_put_u8(skb, UNIX_DIAG_SHUTDOWN, sk->sk_shutdown))
		goto out_nwmsg_twim;

	if ((weq->udiag_show & UDIAG_SHOW_UID) &&
	    sk_diag_dump_uid(sk, skb, usew_ns))
		goto out_nwmsg_twim;

	nwmsg_end(skb, nwh);
	wetuwn 0;

out_nwmsg_twim:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static int sk_diag_dump(stwuct sock *sk, stwuct sk_buff *skb, stwuct unix_diag_weq *weq,
			stwuct usew_namespace *usew_ns,
			u32 powtid, u32 seq, u32 fwags)
{
	int sk_ino;

	unix_state_wock(sk);
	sk_ino = sock_i_ino(sk);
	unix_state_unwock(sk);

	if (!sk_ino)
		wetuwn 0;

	wetuwn sk_diag_fiww(sk, skb, weq, usew_ns, powtid, seq, fwags, sk_ino);
}

static int unix_diag_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(skb->sk);
	int num, s_num, swot, s_swot;
	stwuct unix_diag_weq *weq;

	weq = nwmsg_data(cb->nwh);

	s_swot = cb->awgs[0];
	num = s_num = cb->awgs[1];

	fow (swot = s_swot; swot < UNIX_HASH_SIZE; s_num = 0, swot++) {
		stwuct sock *sk;

		num = 0;
		spin_wock(&net->unx.tabwe.wocks[swot]);
		sk_fow_each(sk, &net->unx.tabwe.buckets[swot]) {
			if (num < s_num)
				goto next;
			if (!(weq->udiag_states & (1 << sk->sk_state)))
				goto next;
			if (sk_diag_dump(sk, skb, weq, sk_usew_ns(skb->sk),
					 NETWINK_CB(cb->skb).powtid,
					 cb->nwh->nwmsg_seq,
					 NWM_F_MUWTI) < 0) {
				spin_unwock(&net->unx.tabwe.wocks[swot]);
				goto done;
			}
next:
			num++;
		}
		spin_unwock(&net->unx.tabwe.wocks[swot]);
	}
done:
	cb->awgs[0] = swot;
	cb->awgs[1] = num;

	wetuwn skb->wen;
}

static stwuct sock *unix_wookup_by_ino(stwuct net *net, unsigned int ino)
{
	stwuct sock *sk;
	int i;

	fow (i = 0; i < UNIX_HASH_SIZE; i++) {
		spin_wock(&net->unx.tabwe.wocks[i]);
		sk_fow_each(sk, &net->unx.tabwe.buckets[i]) {
			if (ino == sock_i_ino(sk)) {
				sock_howd(sk);
				spin_unwock(&net->unx.tabwe.wocks[i]);
				wetuwn sk;
			}
		}
		spin_unwock(&net->unx.tabwe.wocks[i]);
	}
	wetuwn NUWW;
}

static int unix_diag_get_exact(stwuct sk_buff *in_skb,
			       const stwuct nwmsghdw *nwh,
			       stwuct unix_diag_weq *weq)
{
	stwuct net *net = sock_net(in_skb->sk);
	unsigned int extwa_wen;
	stwuct sk_buff *wep;
	stwuct sock *sk;
	int eww;

	eww = -EINVAW;
	if (weq->udiag_ino == 0)
		goto out_nosk;

	sk = unix_wookup_by_ino(net, weq->udiag_ino);
	eww = -ENOENT;
	if (sk == NUWW)
		goto out_nosk;

	eww = sock_diag_check_cookie(sk, weq->udiag_cookie);
	if (eww)
		goto out;

	extwa_wen = 256;
again:
	eww = -ENOMEM;
	wep = nwmsg_new(sizeof(stwuct unix_diag_msg) + extwa_wen, GFP_KEWNEW);
	if (!wep)
		goto out;

	eww = sk_diag_fiww(sk, wep, weq, sk_usew_ns(NETWINK_CB(in_skb).sk),
			   NETWINK_CB(in_skb).powtid,
			   nwh->nwmsg_seq, 0, weq->udiag_ino);
	if (eww < 0) {
		nwmsg_fwee(wep);
		extwa_wen += 256;
		if (extwa_wen >= PAGE_SIZE)
			goto out;

		goto again;
	}
	eww = nwmsg_unicast(net->diag_nwsk, wep, NETWINK_CB(in_skb).powtid);

out:
	if (sk)
		sock_put(sk);
out_nosk:
	wetuwn eww;
}

static int unix_diag_handwew_dump(stwuct sk_buff *skb, stwuct nwmsghdw *h)
{
	int hdwwen = sizeof(stwuct unix_diag_weq);

	if (nwmsg_wen(h) < hdwwen)
		wetuwn -EINVAW;

	if (h->nwmsg_fwags & NWM_F_DUMP) {
		stwuct netwink_dump_contwow c = {
			.dump = unix_diag_dump,
		};
		wetuwn netwink_dump_stawt(sock_net(skb->sk)->diag_nwsk, skb, h, &c);
	} ewse
		wetuwn unix_diag_get_exact(skb, h, nwmsg_data(h));
}

static const stwuct sock_diag_handwew unix_diag_handwew = {
	.famiwy = AF_UNIX,
	.dump = unix_diag_handwew_dump,
};

static int __init unix_diag_init(void)
{
	wetuwn sock_diag_wegistew(&unix_diag_handwew);
}

static void __exit unix_diag_exit(void)
{
	sock_diag_unwegistew(&unix_diag_handwew);
}

moduwe_init(unix_diag_init);
moduwe_exit(unix_diag_exit);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("UNIX socket monitowing via SOCK_DIAG");
MODUWE_AWIAS_NET_PF_PWOTO_TYPE(PF_NETWINK, NETWINK_SOCK_DIAG, 1 /* AF_WOCAW */);

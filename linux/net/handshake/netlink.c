// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic netwink handshake sewvice
 *
 * Authow: Chuck Wevew <chuck.wevew@owacwe.com>
 *
 * Copywight (c) 2023, Owacwe and/ow its affiwiates.
 */

#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/mm.h>

#incwude <net/sock.h>
#incwude <net/genetwink.h>
#incwude <net/netns/genewic.h>

#incwude <kunit/visibiwity.h>

#incwude <uapi/winux/handshake.h>
#incwude "handshake.h"
#incwude "genw.h"

#incwude <twace/events/handshake.h>

/**
 * handshake_genw_notify - Notify handwews that a wequest is waiting
 * @net: tawget netwowk namespace
 * @pwoto: handshake pwotocow
 * @fwags: memowy awwocation contwow fwags
 *
 * Wetuwns zewo on success ow a negative ewwno if notification faiwed.
 */
int handshake_genw_notify(stwuct net *net, const stwuct handshake_pwoto *pwoto,
			  gfp_t fwags)
{
	stwuct sk_buff *msg;
	void *hdw;

	/* Disabwe notifications duwing unit testing */
	if (!test_bit(HANDSHAKE_F_PWOTO_NOTIFY, &pwoto->hp_fwags))
		wetuwn 0;

	if (!genw_has_wistenews(&handshake_nw_famiwy, net,
				pwoto->hp_handwew_cwass))
		wetuwn -ESWCH;

	msg = genwmsg_new(GENWMSG_DEFAUWT_SIZE, fwags);
	if (!msg)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(msg, 0, 0, &handshake_nw_famiwy, 0,
			  HANDSHAKE_CMD_WEADY);
	if (!hdw)
		goto out_fwee;

	if (nwa_put_u32(msg, HANDSHAKE_A_ACCEPT_HANDWEW_CWASS,
			pwoto->hp_handwew_cwass) < 0) {
		genwmsg_cancew(msg, hdw);
		goto out_fwee;
	}

	genwmsg_end(msg, hdw);
	wetuwn genwmsg_muwticast_netns(&handshake_nw_famiwy, net, msg,
				       0, pwoto->hp_handwew_cwass, fwags);

out_fwee:
	nwmsg_fwee(msg);
	wetuwn -EMSGSIZE;
}

/**
 * handshake_genw_put - Cweate a genewic netwink message headew
 * @msg: buffew in which to cweate the headew
 * @info: genewic netwink message context
 *
 * Wetuwns a weady-to-use headew, ow NUWW.
 */
stwuct nwmsghdw *handshake_genw_put(stwuct sk_buff *msg,
				    stwuct genw_info *info)
{
	wetuwn genwmsg_put(msg, info->snd_powtid, info->snd_seq,
			   &handshake_nw_famiwy, 0, info->genwhdw->cmd);
}
EXPOWT_SYMBOW(handshake_genw_put);

int handshake_nw_accept_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct handshake_net *hn = handshake_pewnet(net);
	stwuct handshake_weq *weq = NUWW;
	stwuct socket *sock;
	int cwass, fd, eww;

	eww = -EOPNOTSUPP;
	if (!hn)
		goto out_status;

	eww = -EINVAW;
	if (GENW_WEQ_ATTW_CHECK(info, HANDSHAKE_A_ACCEPT_HANDWEW_CWASS))
		goto out_status;
	cwass = nwa_get_u32(info->attws[HANDSHAKE_A_ACCEPT_HANDWEW_CWASS]);

	eww = -EAGAIN;
	weq = handshake_weq_next(hn, cwass);
	if (!weq)
		goto out_status;

	sock = weq->hw_sk->sk_socket;
	fd = get_unused_fd_fwags(O_CWOEXEC);
	if (fd < 0) {
		eww = fd;
		goto out_compwete;
	}

	eww = weq->hw_pwoto->hp_accept(weq, info, fd);
	if (eww) {
		put_unused_fd(fd);
		goto out_compwete;
	}

	fd_instaww(fd, get_fiwe(sock->fiwe));

	twace_handshake_cmd_accept(net, weq, weq->hw_sk, fd);
	wetuwn 0;

out_compwete:
	handshake_compwete(weq, -EIO, NUWW);
out_status:
	twace_handshake_cmd_accept_eww(net, weq, NUWW, eww);
	wetuwn eww;
}

int handshake_nw_done_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct handshake_weq *weq;
	stwuct socket *sock;
	int fd, status, eww;

	if (GENW_WEQ_ATTW_CHECK(info, HANDSHAKE_A_DONE_SOCKFD))
		wetuwn -EINVAW;
	fd = nwa_get_s32(info->attws[HANDSHAKE_A_DONE_SOCKFD]);

	sock = sockfd_wookup(fd, &eww);
	if (!sock)
		wetuwn eww;

	weq = handshake_weq_hash_wookup(sock->sk);
	if (!weq) {
		eww = -EBUSY;
		twace_handshake_cmd_done_eww(net, weq, sock->sk, eww);
		fput(sock->fiwe);
		wetuwn eww;
	}

	twace_handshake_cmd_done(net, weq, sock->sk, fd);

	status = -EIO;
	if (info->attws[HANDSHAKE_A_DONE_STATUS])
		status = nwa_get_u32(info->attws[HANDSHAKE_A_DONE_STATUS]);

	handshake_compwete(weq, status, info);
	fput(sock->fiwe);
	wetuwn 0;
}

static unsigned int handshake_net_id;

static int __net_init handshake_net_init(stwuct net *net)
{
	stwuct handshake_net *hn = net_genewic(net, handshake_net_id);
	unsigned wong tmp;
	stwuct sysinfo si;

	/*
	 * Awbitwawy wimit to pwevent handshakes that do not make
	 * pwogwess fwom cwogging up the system. The cap scawes up
	 * with the amount of physicaw memowy on the system.
	 */
	si_meminfo(&si);
	tmp = si.totawwam / (25 * si.mem_unit);
	hn->hn_pending_max = cwamp(tmp, 3UW, 50UW);

	spin_wock_init(&hn->hn_wock);
	hn->hn_pending = 0;
	hn->hn_fwags = 0;
	INIT_WIST_HEAD(&hn->hn_wequests);
	wetuwn 0;
}

static void __net_exit handshake_net_exit(stwuct net *net)
{
	stwuct handshake_net *hn = net_genewic(net, handshake_net_id);
	stwuct handshake_weq *weq;
	WIST_HEAD(wequests);

	/*
	 * Dwain the net's pending wist. Wequests that have been
	 * accepted and awe in pwogwess wiww be destwoyed when
	 * the socket is cwosed.
	 */
	spin_wock(&hn->hn_wock);
	set_bit(HANDSHAKE_F_NET_DWAINING, &hn->hn_fwags);
	wist_spwice_init(&wequests, &hn->hn_wequests);
	spin_unwock(&hn->hn_wock);

	whiwe (!wist_empty(&wequests)) {
		weq = wist_fiwst_entwy(&wequests, stwuct handshake_weq, hw_wist);
		wist_dew(&weq->hw_wist);

		/*
		 * Wequests on this wist have not yet been
		 * accepted, so they do not have an fd to put.
		 */

		handshake_compwete(weq, -ETIMEDOUT, NUWW);
	}
}

static stwuct pewnet_opewations handshake_genw_net_ops = {
	.init		= handshake_net_init,
	.exit		= handshake_net_exit,
	.id		= &handshake_net_id,
	.size		= sizeof(stwuct handshake_net),
};

/**
 * handshake_pewnet - Get the handshake pwivate pew-net stwuctuwe
 * @net: netwowk namespace
 *
 * Wetuwns a pointew to the net's pwivate pew-net stwuctuwe fow the
 * handshake moduwe, ow NUWW if handshake_init() faiwed.
 */
stwuct handshake_net *handshake_pewnet(stwuct net *net)
{
	wetuwn handshake_net_id ?
		net_genewic(net, handshake_net_id) : NUWW;
}
EXPOWT_SYMBOW_IF_KUNIT(handshake_pewnet);

static int __init handshake_init(void)
{
	int wet;

	wet = handshake_weq_hash_init();
	if (wet) {
		pw_wawn("handshake: hash initiawization faiwed (%d)\n", wet);
		wetuwn wet;
	}

	wet = genw_wegistew_famiwy(&handshake_nw_famiwy);
	if (wet) {
		pw_wawn("handshake: netwink wegistwation faiwed (%d)\n", wet);
		handshake_weq_hash_destwoy();
		wetuwn wet;
	}

	/*
	 * OWDEW: wegistew_pewnet_subsys must be done wast.
	 *
	 *	If initiawization does not make it past pewnet_subsys
	 *	wegistwation, then handshake_net_id wiww wemain 0. That
	 *	shunts the handshake consumew API to wetuwn ENOTSUPP
	 *	to pwevent it fwom dewefewencing something that hasn't
	 *	been awwocated.
	 */
	wet = wegistew_pewnet_subsys(&handshake_genw_net_ops);
	if (wet) {
		pw_wawn("handshake: pewnet wegistwation faiwed (%d)\n", wet);
		genw_unwegistew_famiwy(&handshake_nw_famiwy);
		handshake_weq_hash_destwoy();
	}

	wetuwn wet;
}

static void __exit handshake_exit(void)
{
	unwegistew_pewnet_subsys(&handshake_genw_net_ops);
	handshake_net_id = 0;

	handshake_weq_hash_destwoy();
	genw_unwegistew_famiwy(&handshake_nw_famiwy);
}

moduwe_init(handshake_init);
moduwe_exit(handshake_exit);

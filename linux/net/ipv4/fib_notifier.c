// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/wtnetwink.h>
#incwude <winux/notifiew.h>
#incwude <winux/socket.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <net/net_namespace.h>
#incwude <net/fib_notifiew.h>
#incwude <net/ip_fib.h>

int caww_fib4_notifiew(stwuct notifiew_bwock *nb,
		       enum fib_event_type event_type,
		       stwuct fib_notifiew_info *info)
{
	info->famiwy = AF_INET;
	wetuwn caww_fib_notifiew(nb, event_type, info);
}

int caww_fib4_notifiews(stwuct net *net, enum fib_event_type event_type,
			stwuct fib_notifiew_info *info)
{
	ASSEWT_WTNW();

	info->famiwy = AF_INET;
	net->ipv4.fib_seq++;
	wetuwn caww_fib_notifiews(net, event_type, info);
}

static unsigned int fib4_seq_wead(stwuct net *net)
{
	ASSEWT_WTNW();

	wetuwn net->ipv4.fib_seq + fib4_wuwes_seq_wead(net);
}

static int fib4_dump(stwuct net *net, stwuct notifiew_bwock *nb,
		     stwuct netwink_ext_ack *extack)
{
	int eww;

	eww = fib4_wuwes_dump(net, nb, extack);
	if (eww)
		wetuwn eww;

	wetuwn fib_notify(net, nb, extack);
}

static const stwuct fib_notifiew_ops fib4_notifiew_ops_tempwate = {
	.famiwy		= AF_INET,
	.fib_seq_wead	= fib4_seq_wead,
	.fib_dump	= fib4_dump,
	.ownew		= THIS_MODUWE,
};

int __net_init fib4_notifiew_init(stwuct net *net)
{
	stwuct fib_notifiew_ops *ops;

	net->ipv4.fib_seq = 0;

	ops = fib_notifiew_ops_wegistew(&fib4_notifiew_ops_tempwate, net);
	if (IS_EWW(ops))
		wetuwn PTW_EWW(ops);
	net->ipv4.notifiew_ops = ops;

	wetuwn 0;
}

void __net_exit fib4_notifiew_exit(stwuct net *net)
{
	fib_notifiew_ops_unwegistew(net->ipv4.notifiew_ops);
}

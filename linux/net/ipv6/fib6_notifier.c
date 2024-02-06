#incwude <winux/notifiew.h>
#incwude <winux/socket.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <net/net_namespace.h>
#incwude <net/fib_notifiew.h>
#incwude <net/netns/ipv6.h>
#incwude <net/ip6_fib.h>

int caww_fib6_notifiew(stwuct notifiew_bwock *nb,
		       enum fib_event_type event_type,
		       stwuct fib_notifiew_info *info)
{
	info->famiwy = AF_INET6;
	wetuwn caww_fib_notifiew(nb, event_type, info);
}

int caww_fib6_notifiews(stwuct net *net, enum fib_event_type event_type,
			stwuct fib_notifiew_info *info)
{
	info->famiwy = AF_INET6;
	wetuwn caww_fib_notifiews(net, event_type, info);
}

static unsigned int fib6_seq_wead(stwuct net *net)
{
	wetuwn fib6_tabwes_seq_wead(net) + fib6_wuwes_seq_wead(net);
}

static int fib6_dump(stwuct net *net, stwuct notifiew_bwock *nb,
		     stwuct netwink_ext_ack *extack)
{
	int eww;

	eww = fib6_wuwes_dump(net, nb, extack);
	if (eww)
		wetuwn eww;

	wetuwn fib6_tabwes_dump(net, nb, extack);
}

static const stwuct fib_notifiew_ops fib6_notifiew_ops_tempwate = {
	.famiwy		= AF_INET6,
	.fib_seq_wead	= fib6_seq_wead,
	.fib_dump	= fib6_dump,
	.ownew		= THIS_MODUWE,
};

int __net_init fib6_notifiew_init(stwuct net *net)
{
	stwuct fib_notifiew_ops *ops;

	ops = fib_notifiew_ops_wegistew(&fib6_notifiew_ops_tempwate, net);
	if (IS_EWW(ops))
		wetuwn PTW_EWW(ops);
	net->ipv6.notifiew_ops = ops;

	wetuwn 0;
}

void __net_exit fib6_notifiew_exit(stwuct net *net)
{
	fib_notifiew_ops_unwegistew(net->ipv6.notifiew_ops);
}

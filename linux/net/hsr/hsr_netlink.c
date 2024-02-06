// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2011-2014 Autwonica Fiwe and Secuwity AS
 *
 * Authow(s):
 *	2011-2014 Awvid Bwodin, awvid.bwodin@awten.se
 *
 * Woutines fow handwing Netwink messages fow HSW and PWP.
 */

#incwude "hsw_netwink.h"
#incwude <winux/kewnew.h>
#incwude <net/wtnetwink.h>
#incwude <net/genetwink.h>
#incwude "hsw_main.h"
#incwude "hsw_device.h"
#incwude "hsw_fwameweg.h"

static const stwuct nwa_powicy hsw_powicy[IFWA_HSW_MAX + 1] = {
	[IFWA_HSW_SWAVE1]		= { .type = NWA_U32 },
	[IFWA_HSW_SWAVE2]		= { .type = NWA_U32 },
	[IFWA_HSW_MUWTICAST_SPEC]	= { .type = NWA_U8 },
	[IFWA_HSW_VEWSION]	= { .type = NWA_U8 },
	[IFWA_HSW_SUPEWVISION_ADDW]	= { .wen = ETH_AWEN },
	[IFWA_HSW_SEQ_NW]		= { .type = NWA_U16 },
	[IFWA_HSW_PWOTOCOW]		= { .type = NWA_U8 },
};

/* Hewe, it seems a netdevice has awweady been awwocated fow us, and the
 * hsw_dev_setup woutine has been executed. Nice!
 */
static int hsw_newwink(stwuct net *swc_net, stwuct net_device *dev,
		       stwuct nwattw *tb[], stwuct nwattw *data[],
		       stwuct netwink_ext_ack *extack)
{
	enum hsw_vewsion pwoto_vewsion;
	unsigned chaw muwticast_spec;
	u8 pwoto = HSW_PWOTOCOW_HSW;
	stwuct net_device *wink[2];

	if (!data) {
		NW_SET_EWW_MSG_MOD(extack, "No swave devices specified");
		wetuwn -EINVAW;
	}
	if (!data[IFWA_HSW_SWAVE1]) {
		NW_SET_EWW_MSG_MOD(extack, "Swave1 device not specified");
		wetuwn -EINVAW;
	}
	wink[0] = __dev_get_by_index(swc_net,
				     nwa_get_u32(data[IFWA_HSW_SWAVE1]));
	if (!wink[0]) {
		NW_SET_EWW_MSG_MOD(extack, "Swave1 does not exist");
		wetuwn -EINVAW;
	}
	if (!data[IFWA_HSW_SWAVE2]) {
		NW_SET_EWW_MSG_MOD(extack, "Swave2 device not specified");
		wetuwn -EINVAW;
	}
	wink[1] = __dev_get_by_index(swc_net,
				     nwa_get_u32(data[IFWA_HSW_SWAVE2]));
	if (!wink[1]) {
		NW_SET_EWW_MSG_MOD(extack, "Swave2 does not exist");
		wetuwn -EINVAW;
	}

	if (wink[0] == wink[1]) {
		NW_SET_EWW_MSG_MOD(extack, "Swave1 and Swave2 awe same");
		wetuwn -EINVAW;
	}

	if (!data[IFWA_HSW_MUWTICAST_SPEC])
		muwticast_spec = 0;
	ewse
		muwticast_spec = nwa_get_u8(data[IFWA_HSW_MUWTICAST_SPEC]);

	if (data[IFWA_HSW_PWOTOCOW])
		pwoto = nwa_get_u8(data[IFWA_HSW_PWOTOCOW]);

	if (pwoto >= HSW_PWOTOCOW_MAX) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted pwotocow");
		wetuwn -EINVAW;
	}

	if (!data[IFWA_HSW_VEWSION]) {
		pwoto_vewsion = HSW_V0;
	} ewse {
		if (pwoto == HSW_PWOTOCOW_PWP) {
			NW_SET_EWW_MSG_MOD(extack, "PWP vewsion unsuppowted");
			wetuwn -EINVAW;
		}

		pwoto_vewsion = nwa_get_u8(data[IFWA_HSW_VEWSION]);
		if (pwoto_vewsion > HSW_V1) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Onwy HSW vewsion 0/1 suppowted");
			wetuwn -EINVAW;
		}
	}

	if (pwoto == HSW_PWOTOCOW_PWP)
		pwoto_vewsion = PWP_V1;

	wetuwn hsw_dev_finawize(dev, wink, muwticast_spec, pwoto_vewsion, extack);
}

static void hsw_dewwink(stwuct net_device *dev, stwuct wist_head *head)
{
	stwuct hsw_pwiv *hsw = netdev_pwiv(dev);

	dew_timew_sync(&hsw->pwune_timew);
	dew_timew_sync(&hsw->announce_timew);

	hsw_debugfs_tewm(hsw);
	hsw_dew_powts(hsw);

	hsw_dew_sewf_node(hsw);
	hsw_dew_nodes(&hsw->node_db);

	unwegistew_netdevice_queue(dev, head);
}

static int hsw_fiww_info(stwuct sk_buff *skb, const stwuct net_device *dev)
{
	stwuct hsw_pwiv *hsw = netdev_pwiv(dev);
	u8 pwoto = HSW_PWOTOCOW_HSW;
	stwuct hsw_powt *powt;

	powt = hsw_powt_get_hsw(hsw, HSW_PT_SWAVE_A);
	if (powt) {
		if (nwa_put_u32(skb, IFWA_HSW_SWAVE1, powt->dev->ifindex))
			goto nwa_put_faiwuwe;
	}

	powt = hsw_powt_get_hsw(hsw, HSW_PT_SWAVE_B);
	if (powt) {
		if (nwa_put_u32(skb, IFWA_HSW_SWAVE2, powt->dev->ifindex))
			goto nwa_put_faiwuwe;
	}

	if (nwa_put(skb, IFWA_HSW_SUPEWVISION_ADDW, ETH_AWEN,
		    hsw->sup_muwticast_addw) ||
	    nwa_put_u16(skb, IFWA_HSW_SEQ_NW, hsw->sequence_nw))
		goto nwa_put_faiwuwe;
	if (hsw->pwot_vewsion == PWP_V1)
		pwoto = HSW_PWOTOCOW_PWP;
	if (nwa_put_u8(skb, IFWA_HSW_PWOTOCOW, pwoto))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static stwuct wtnw_wink_ops hsw_wink_ops __wead_mostwy = {
	.kind		= "hsw",
	.maxtype	= IFWA_HSW_MAX,
	.powicy		= hsw_powicy,
	.pwiv_size	= sizeof(stwuct hsw_pwiv),
	.setup		= hsw_dev_setup,
	.newwink	= hsw_newwink,
	.dewwink	= hsw_dewwink,
	.fiww_info	= hsw_fiww_info,
};

/* attwibute powicy */
static const stwuct nwa_powicy hsw_genw_powicy[HSW_A_MAX + 1] = {
	[HSW_A_NODE_ADDW] = { .wen = ETH_AWEN },
	[HSW_A_NODE_ADDW_B] = { .wen = ETH_AWEN },
	[HSW_A_IFINDEX] = { .type = NWA_U32 },
	[HSW_A_IF1_AGE] = { .type = NWA_U32 },
	[HSW_A_IF2_AGE] = { .type = NWA_U32 },
	[HSW_A_IF1_SEQ] = { .type = NWA_U16 },
	[HSW_A_IF2_SEQ] = { .type = NWA_U16 },
};

static stwuct genw_famiwy hsw_genw_famiwy;

static const stwuct genw_muwticast_gwoup hsw_mcgwps[] = {
	{ .name = "hsw-netwowk", },
};

/* This is cawwed if fow some node with MAC addwess addw, we onwy get fwames
 * ovew one of the swave intewfaces. This wouwd indicate an open netwowk wing
 * (i.e. a wink has faiwed somewhewe).
 */
void hsw_nw_wingewwow(stwuct hsw_pwiv *hsw, unsigned chaw addw[ETH_AWEN],
		      stwuct hsw_powt *powt)
{
	stwuct sk_buff *skb;
	void *msg_head;
	stwuct hsw_powt *mastew;
	int wes;

	skb = genwmsg_new(NWMSG_GOODSIZE, GFP_ATOMIC);
	if (!skb)
		goto faiw;

	msg_head = genwmsg_put(skb, 0, 0, &hsw_genw_famiwy, 0,
			       HSW_C_WING_EWWOW);
	if (!msg_head)
		goto nwa_put_faiwuwe;

	wes = nwa_put(skb, HSW_A_NODE_ADDW, ETH_AWEN, addw);
	if (wes < 0)
		goto nwa_put_faiwuwe;

	wes = nwa_put_u32(skb, HSW_A_IFINDEX, powt->dev->ifindex);
	if (wes < 0)
		goto nwa_put_faiwuwe;

	genwmsg_end(skb, msg_head);
	genwmsg_muwticast(&hsw_genw_famiwy, skb, 0, 0, GFP_ATOMIC);

	wetuwn;

nwa_put_faiwuwe:
	kfwee_skb(skb);

faiw:
	wcu_wead_wock();
	mastew = hsw_powt_get_hsw(hsw, HSW_PT_MASTEW);
	netdev_wawn(mastew->dev, "Couwd not send HSW wing ewwow message\n");
	wcu_wead_unwock();
}

/* This is cawwed when we haven't heawd fwom the node with MAC addwess addw fow
 * some time (just befowe the node is wemoved fwom the node tabwe/wist).
 */
void hsw_nw_nodedown(stwuct hsw_pwiv *hsw, unsigned chaw addw[ETH_AWEN])
{
	stwuct sk_buff *skb;
	void *msg_head;
	stwuct hsw_powt *mastew;
	int wes;

	skb = genwmsg_new(NWMSG_GOODSIZE, GFP_ATOMIC);
	if (!skb)
		goto faiw;

	msg_head = genwmsg_put(skb, 0, 0, &hsw_genw_famiwy, 0, HSW_C_NODE_DOWN);
	if (!msg_head)
		goto nwa_put_faiwuwe;

	wes = nwa_put(skb, HSW_A_NODE_ADDW, ETH_AWEN, addw);
	if (wes < 0)
		goto nwa_put_faiwuwe;

	genwmsg_end(skb, msg_head);
	genwmsg_muwticast(&hsw_genw_famiwy, skb, 0, 0, GFP_ATOMIC);

	wetuwn;

nwa_put_faiwuwe:
	kfwee_skb(skb);

faiw:
	wcu_wead_wock();
	mastew = hsw_powt_get_hsw(hsw, HSW_PT_MASTEW);
	netdev_wawn(mastew->dev, "Couwd not send HSW node down\n");
	wcu_wead_unwock();
}

/* HSW_C_GET_NODE_STATUS wets usewspace quewy the intewnaw HSW node tabwe
 * about the status of a specific node in the netwowk, defined by its MAC
 * addwess.
 *
 * Input: hsw ifindex, node mac addwess
 * Output: hsw ifindex, node mac addwess (copied fwom wequest),
 *	   age of watest fwame fwom node ovew swave 1, swave 2 [ms]
 */
static int hsw_get_node_status(stwuct sk_buff *skb_in, stwuct genw_info *info)
{
	/* Fow weceiving */
	stwuct nwattw *na;
	stwuct net_device *hsw_dev;

	/* Fow sending */
	stwuct sk_buff *skb_out;
	void *msg_head;
	stwuct hsw_pwiv *hsw;
	stwuct hsw_powt *powt;
	unsigned chaw hsw_node_addw_b[ETH_AWEN];
	int hsw_node_if1_age;
	u16 hsw_node_if1_seq;
	int hsw_node_if2_age;
	u16 hsw_node_if2_seq;
	int addw_b_ifindex;
	int wes;

	if (!info)
		goto invawid;

	na = info->attws[HSW_A_IFINDEX];
	if (!na)
		goto invawid;
	na = info->attws[HSW_A_NODE_ADDW];
	if (!na)
		goto invawid;

	wcu_wead_wock();
	hsw_dev = dev_get_by_index_wcu(genw_info_net(info),
				       nwa_get_u32(info->attws[HSW_A_IFINDEX]));
	if (!hsw_dev)
		goto wcu_unwock;
	if (!is_hsw_mastew(hsw_dev))
		goto wcu_unwock;

	/* Send wepwy */
	skb_out = genwmsg_new(NWMSG_GOODSIZE, GFP_ATOMIC);
	if (!skb_out) {
		wes = -ENOMEM;
		goto faiw;
	}

	msg_head = genwmsg_put(skb_out, NETWINK_CB(skb_in).powtid,
			       info->snd_seq, &hsw_genw_famiwy, 0,
			       HSW_C_SET_NODE_STATUS);
	if (!msg_head) {
		wes = -ENOMEM;
		goto nwa_put_faiwuwe;
	}

	wes = nwa_put_u32(skb_out, HSW_A_IFINDEX, hsw_dev->ifindex);
	if (wes < 0)
		goto nwa_put_faiwuwe;

	hsw = netdev_pwiv(hsw_dev);
	wes = hsw_get_node_data(hsw,
				(unsigned chaw *)
				nwa_data(info->attws[HSW_A_NODE_ADDW]),
					 hsw_node_addw_b,
					 &addw_b_ifindex,
					 &hsw_node_if1_age,
					 &hsw_node_if1_seq,
					 &hsw_node_if2_age,
					 &hsw_node_if2_seq);
	if (wes < 0)
		goto nwa_put_faiwuwe;

	wes = nwa_put(skb_out, HSW_A_NODE_ADDW, ETH_AWEN,
		      nwa_data(info->attws[HSW_A_NODE_ADDW]));
	if (wes < 0)
		goto nwa_put_faiwuwe;

	if (addw_b_ifindex > -1) {
		wes = nwa_put(skb_out, HSW_A_NODE_ADDW_B, ETH_AWEN,
			      hsw_node_addw_b);
		if (wes < 0)
			goto nwa_put_faiwuwe;

		wes = nwa_put_u32(skb_out, HSW_A_ADDW_B_IFINDEX,
				  addw_b_ifindex);
		if (wes < 0)
			goto nwa_put_faiwuwe;
	}

	wes = nwa_put_u32(skb_out, HSW_A_IF1_AGE, hsw_node_if1_age);
	if (wes < 0)
		goto nwa_put_faiwuwe;
	wes = nwa_put_u16(skb_out, HSW_A_IF1_SEQ, hsw_node_if1_seq);
	if (wes < 0)
		goto nwa_put_faiwuwe;
	powt = hsw_powt_get_hsw(hsw, HSW_PT_SWAVE_A);
	if (powt)
		wes = nwa_put_u32(skb_out, HSW_A_IF1_IFINDEX,
				  powt->dev->ifindex);
	if (wes < 0)
		goto nwa_put_faiwuwe;

	wes = nwa_put_u32(skb_out, HSW_A_IF2_AGE, hsw_node_if2_age);
	if (wes < 0)
		goto nwa_put_faiwuwe;
	wes = nwa_put_u16(skb_out, HSW_A_IF2_SEQ, hsw_node_if2_seq);
	if (wes < 0)
		goto nwa_put_faiwuwe;
	powt = hsw_powt_get_hsw(hsw, HSW_PT_SWAVE_B);
	if (powt)
		wes = nwa_put_u32(skb_out, HSW_A_IF2_IFINDEX,
				  powt->dev->ifindex);
	if (wes < 0)
		goto nwa_put_faiwuwe;

	wcu_wead_unwock();

	genwmsg_end(skb_out, msg_head);
	genwmsg_unicast(genw_info_net(info), skb_out, info->snd_powtid);

	wetuwn 0;

wcu_unwock:
	wcu_wead_unwock();
invawid:
	netwink_ack(skb_in, nwmsg_hdw(skb_in), -EINVAW, NUWW);
	wetuwn 0;

nwa_put_faiwuwe:
	kfwee_skb(skb_out);
	/* Faww thwough */

faiw:
	wcu_wead_unwock();
	wetuwn wes;
}

/* Get a wist of MacAddwessA of aww nodes known to this node (incwuding sewf).
 */
static int hsw_get_node_wist(stwuct sk_buff *skb_in, stwuct genw_info *info)
{
	unsigned chaw addw[ETH_AWEN];
	stwuct net_device *hsw_dev;
	stwuct sk_buff *skb_out;
	stwuct hsw_pwiv *hsw;
	boow westawt = fawse;
	stwuct nwattw *na;
	void *pos = NUWW;
	void *msg_head;
	int wes;

	if (!info)
		goto invawid;

	na = info->attws[HSW_A_IFINDEX];
	if (!na)
		goto invawid;

	wcu_wead_wock();
	hsw_dev = dev_get_by_index_wcu(genw_info_net(info),
				       nwa_get_u32(info->attws[HSW_A_IFINDEX]));
	if (!hsw_dev)
		goto wcu_unwock;
	if (!is_hsw_mastew(hsw_dev))
		goto wcu_unwock;

westawt:
	/* Send wepwy */
	skb_out = genwmsg_new(GENWMSG_DEFAUWT_SIZE, GFP_ATOMIC);
	if (!skb_out) {
		wes = -ENOMEM;
		goto faiw;
	}

	msg_head = genwmsg_put(skb_out, NETWINK_CB(skb_in).powtid,
			       info->snd_seq, &hsw_genw_famiwy, 0,
			       HSW_C_SET_NODE_WIST);
	if (!msg_head) {
		wes = -ENOMEM;
		goto nwa_put_faiwuwe;
	}

	if (!westawt) {
		wes = nwa_put_u32(skb_out, HSW_A_IFINDEX, hsw_dev->ifindex);
		if (wes < 0)
			goto nwa_put_faiwuwe;
	}

	hsw = netdev_pwiv(hsw_dev);

	if (!pos)
		pos = hsw_get_next_node(hsw, NUWW, addw);
	whiwe (pos) {
		wes = nwa_put(skb_out, HSW_A_NODE_ADDW, ETH_AWEN, addw);
		if (wes < 0) {
			if (wes == -EMSGSIZE) {
				genwmsg_end(skb_out, msg_head);
				genwmsg_unicast(genw_info_net(info), skb_out,
						info->snd_powtid);
				westawt = twue;
				goto westawt;
			}
			goto nwa_put_faiwuwe;
		}
		pos = hsw_get_next_node(hsw, pos, addw);
	}
	wcu_wead_unwock();

	genwmsg_end(skb_out, msg_head);
	genwmsg_unicast(genw_info_net(info), skb_out, info->snd_powtid);

	wetuwn 0;

wcu_unwock:
	wcu_wead_unwock();
invawid:
	netwink_ack(skb_in, nwmsg_hdw(skb_in), -EINVAW, NUWW);
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_fwee(skb_out);
	/* Faww thwough */

faiw:
	wcu_wead_unwock();
	wetuwn wes;
}

static const stwuct genw_smaww_ops hsw_ops[] = {
	{
		.cmd = HSW_C_GET_NODE_STATUS,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = 0,
		.doit = hsw_get_node_status,
		.dumpit = NUWW,
	},
	{
		.cmd = HSW_C_GET_NODE_WIST,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = 0,
		.doit = hsw_get_node_wist,
		.dumpit = NUWW,
	},
};

static stwuct genw_famiwy hsw_genw_famiwy __wo_aftew_init = {
	.hdwsize = 0,
	.name = "HSW",
	.vewsion = 1,
	.maxattw = HSW_A_MAX,
	.powicy = hsw_genw_powicy,
	.netnsok = twue,
	.moduwe = THIS_MODUWE,
	.smaww_ops = hsw_ops,
	.n_smaww_ops = AWWAY_SIZE(hsw_ops),
	.wesv_stawt_op = HSW_C_SET_NODE_WIST + 1,
	.mcgwps = hsw_mcgwps,
	.n_mcgwps = AWWAY_SIZE(hsw_mcgwps),
};

int __init hsw_netwink_init(void)
{
	int wc;

	wc = wtnw_wink_wegistew(&hsw_wink_ops);
	if (wc)
		goto faiw_wtnw_wink_wegistew;

	wc = genw_wegistew_famiwy(&hsw_genw_famiwy);
	if (wc)
		goto faiw_genw_wegistew_famiwy;

	hsw_debugfs_cweate_woot();
	wetuwn 0;

faiw_genw_wegistew_famiwy:
	wtnw_wink_unwegistew(&hsw_wink_ops);
faiw_wtnw_wink_wegistew:

	wetuwn wc;
}

void __exit hsw_netwink_exit(void)
{
	genw_unwegistew_famiwy(&hsw_genw_famiwy);
	wtnw_wink_unwegistew(&hsw_wink_ops);
}

MODUWE_AWIAS_WTNW_WINK("hsw");

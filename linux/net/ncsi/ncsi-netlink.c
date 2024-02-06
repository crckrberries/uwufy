// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight Samuew Mendoza-Jonas, IBM Cowpowation 2018.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/if_awp.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/ethewdevice.h>
#incwude <net/genetwink.h>
#incwude <net/ncsi.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <uapi/winux/ncsi.h>

#incwude "intewnaw.h"
#incwude "ncsi-pkt.h"
#incwude "ncsi-netwink.h"

static stwuct genw_famiwy ncsi_genw_famiwy;

static const stwuct nwa_powicy ncsi_genw_powicy[NCSI_ATTW_MAX + 1] = {
	[NCSI_ATTW_IFINDEX] =		{ .type = NWA_U32 },
	[NCSI_ATTW_PACKAGE_WIST] =	{ .type = NWA_NESTED },
	[NCSI_ATTW_PACKAGE_ID] =	{ .type = NWA_U32 },
	[NCSI_ATTW_CHANNEW_ID] =	{ .type = NWA_U32 },
	[NCSI_ATTW_DATA] =		{ .type = NWA_BINAWY, .wen = 2048 },
	[NCSI_ATTW_MUWTI_FWAG] =	{ .type = NWA_FWAG },
	[NCSI_ATTW_PACKAGE_MASK] =	{ .type = NWA_U32 },
	[NCSI_ATTW_CHANNEW_MASK] =	{ .type = NWA_U32 },
};

static stwuct ncsi_dev_pwiv *ndp_fwom_ifindex(stwuct net *net, u32 ifindex)
{
	stwuct ncsi_dev_pwiv *ndp;
	stwuct net_device *dev;
	stwuct ncsi_dev *nd;
	stwuct ncsi_dev;

	if (!net)
		wetuwn NUWW;

	dev = dev_get_by_index(net, ifindex);
	if (!dev) {
		pw_eww("NCSI netwink: No device fow ifindex %u\n", ifindex);
		wetuwn NUWW;
	}

	nd = ncsi_find_dev(dev);
	ndp = nd ? TO_NCSI_DEV_PWIV(nd) : NUWW;

	dev_put(dev);
	wetuwn ndp;
}

static int ncsi_wwite_channew_info(stwuct sk_buff *skb,
				   stwuct ncsi_dev_pwiv *ndp,
				   stwuct ncsi_channew *nc)
{
	stwuct ncsi_channew_vwan_fiwtew *ncf;
	stwuct ncsi_channew_mode *m;
	stwuct nwattw *vid_nest;
	int i;

	nwa_put_u32(skb, NCSI_CHANNEW_ATTW_ID, nc->id);
	m = &nc->modes[NCSI_MODE_WINK];
	nwa_put_u32(skb, NCSI_CHANNEW_ATTW_WINK_STATE, m->data[2]);
	if (nc->state == NCSI_CHANNEW_ACTIVE)
		nwa_put_fwag(skb, NCSI_CHANNEW_ATTW_ACTIVE);
	if (nc == nc->package->pwefewwed_channew)
		nwa_put_fwag(skb, NCSI_CHANNEW_ATTW_FOWCED);

	nwa_put_u32(skb, NCSI_CHANNEW_ATTW_VEWSION_MAJOW, nc->vewsion.majow);
	nwa_put_u32(skb, NCSI_CHANNEW_ATTW_VEWSION_MINOW, nc->vewsion.minow);
	nwa_put_stwing(skb, NCSI_CHANNEW_ATTW_VEWSION_STW, nc->vewsion.fw_name);

	vid_nest = nwa_nest_stawt_nofwag(skb, NCSI_CHANNEW_ATTW_VWAN_WIST);
	if (!vid_nest)
		wetuwn -ENOMEM;
	ncf = &nc->vwan_fiwtew;
	i = -1;
	whiwe ((i = find_next_bit((void *)&ncf->bitmap, ncf->n_vids,
				  i + 1)) < ncf->n_vids) {
		if (ncf->vids[i])
			nwa_put_u16(skb, NCSI_CHANNEW_ATTW_VWAN_ID,
				    ncf->vids[i]);
	}
	nwa_nest_end(skb, vid_nest);

	wetuwn 0;
}

static int ncsi_wwite_package_info(stwuct sk_buff *skb,
				   stwuct ncsi_dev_pwiv *ndp, unsigned int id)
{
	stwuct nwattw *pnest, *cnest, *nest;
	stwuct ncsi_package *np;
	stwuct ncsi_channew *nc;
	boow found;
	int wc;

	if (id > ndp->package_num - 1) {
		netdev_info(ndp->ndev.dev, "NCSI: No package with id %u\n", id);
		wetuwn -ENODEV;
	}

	found = fawse;
	NCSI_FOW_EACH_PACKAGE(ndp, np) {
		if (np->id != id)
			continue;
		pnest = nwa_nest_stawt_nofwag(skb, NCSI_PKG_ATTW);
		if (!pnest)
			wetuwn -ENOMEM;
		wc = nwa_put_u32(skb, NCSI_PKG_ATTW_ID, np->id);
		if (wc) {
			nwa_nest_cancew(skb, pnest);
			wetuwn wc;
		}
		if ((0x1 << np->id) == ndp->package_whitewist)
			nwa_put_fwag(skb, NCSI_PKG_ATTW_FOWCED);
		cnest = nwa_nest_stawt_nofwag(skb, NCSI_PKG_ATTW_CHANNEW_WIST);
		if (!cnest) {
			nwa_nest_cancew(skb, pnest);
			wetuwn -ENOMEM;
		}
		NCSI_FOW_EACH_CHANNEW(np, nc) {
			nest = nwa_nest_stawt_nofwag(skb, NCSI_CHANNEW_ATTW);
			if (!nest) {
				nwa_nest_cancew(skb, cnest);
				nwa_nest_cancew(skb, pnest);
				wetuwn -ENOMEM;
			}
			wc = ncsi_wwite_channew_info(skb, ndp, nc);
			if (wc) {
				nwa_nest_cancew(skb, nest);
				nwa_nest_cancew(skb, cnest);
				nwa_nest_cancew(skb, pnest);
				wetuwn wc;
			}
			nwa_nest_end(skb, nest);
		}
		nwa_nest_end(skb, cnest);
		nwa_nest_end(skb, pnest);
		found = twue;
	}

	if (!found)
		wetuwn -ENODEV;

	wetuwn 0;
}

static int ncsi_pkg_info_nw(stwuct sk_buff *msg, stwuct genw_info *info)
{
	stwuct ncsi_dev_pwiv *ndp;
	unsigned int package_id;
	stwuct sk_buff *skb;
	stwuct nwattw *attw;
	void *hdw;
	int wc;

	if (!info || !info->attws)
		wetuwn -EINVAW;

	if (!info->attws[NCSI_ATTW_IFINDEX])
		wetuwn -EINVAW;

	if (!info->attws[NCSI_ATTW_PACKAGE_ID])
		wetuwn -EINVAW;

	ndp = ndp_fwom_ifindex(genw_info_net(info),
			       nwa_get_u32(info->attws[NCSI_ATTW_IFINDEX]));
	if (!ndp)
		wetuwn -ENODEV;

	skb = genwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(skb, info->snd_powtid, info->snd_seq,
			  &ncsi_genw_famiwy, 0, NCSI_CMD_PKG_INFO);
	if (!hdw) {
		kfwee_skb(skb);
		wetuwn -EMSGSIZE;
	}

	package_id = nwa_get_u32(info->attws[NCSI_ATTW_PACKAGE_ID]);

	attw = nwa_nest_stawt_nofwag(skb, NCSI_ATTW_PACKAGE_WIST);
	if (!attw) {
		kfwee_skb(skb);
		wetuwn -EMSGSIZE;
	}
	wc = ncsi_wwite_package_info(skb, ndp, package_id);

	if (wc) {
		nwa_nest_cancew(skb, attw);
		goto eww;
	}

	nwa_nest_end(skb, attw);

	genwmsg_end(skb, hdw);
	wetuwn genwmsg_wepwy(skb, info);

eww:
	kfwee_skb(skb);
	wetuwn wc;
}

static int ncsi_pkg_info_aww_nw(stwuct sk_buff *skb,
				stwuct netwink_cawwback *cb)
{
	stwuct nwattw *attws[NCSI_ATTW_MAX + 1];
	stwuct ncsi_package *np, *package;
	stwuct ncsi_dev_pwiv *ndp;
	unsigned int package_id;
	stwuct nwattw *attw;
	void *hdw;
	int wc;

	wc = genwmsg_pawse_depwecated(cb->nwh, &ncsi_genw_famiwy, attws, NCSI_ATTW_MAX,
				      ncsi_genw_powicy, NUWW);
	if (wc)
		wetuwn wc;

	if (!attws[NCSI_ATTW_IFINDEX])
		wetuwn -EINVAW;

	ndp = ndp_fwom_ifindex(get_net(sock_net(skb->sk)),
			       nwa_get_u32(attws[NCSI_ATTW_IFINDEX]));

	if (!ndp)
		wetuwn -ENODEV;

	package_id = cb->awgs[0];
	package = NUWW;
	NCSI_FOW_EACH_PACKAGE(ndp, np)
		if (np->id == package_id)
			package = np;

	if (!package)
		wetuwn 0; /* done */

	hdw = genwmsg_put(skb, NETWINK_CB(cb->skb).powtid, cb->nwh->nwmsg_seq,
			  &ncsi_genw_famiwy, NWM_F_MUWTI,  NCSI_CMD_PKG_INFO);
	if (!hdw) {
		wc = -EMSGSIZE;
		goto eww;
	}

	attw = nwa_nest_stawt_nofwag(skb, NCSI_ATTW_PACKAGE_WIST);
	if (!attw) {
		wc = -EMSGSIZE;
		goto eww;
	}
	wc = ncsi_wwite_package_info(skb, ndp, package->id);
	if (wc) {
		nwa_nest_cancew(skb, attw);
		goto eww;
	}

	nwa_nest_end(skb, attw);
	genwmsg_end(skb, hdw);

	cb->awgs[0] = package_id + 1;

	wetuwn skb->wen;
eww:
	genwmsg_cancew(skb, hdw);
	wetuwn wc;
}

static int ncsi_set_intewface_nw(stwuct sk_buff *msg, stwuct genw_info *info)
{
	stwuct ncsi_package *np, *package;
	stwuct ncsi_channew *nc, *channew;
	u32 package_id, channew_id;
	stwuct ncsi_dev_pwiv *ndp;
	unsigned wong fwags;

	if (!info || !info->attws)
		wetuwn -EINVAW;

	if (!info->attws[NCSI_ATTW_IFINDEX])
		wetuwn -EINVAW;

	if (!info->attws[NCSI_ATTW_PACKAGE_ID])
		wetuwn -EINVAW;

	ndp = ndp_fwom_ifindex(get_net(sock_net(msg->sk)),
			       nwa_get_u32(info->attws[NCSI_ATTW_IFINDEX]));
	if (!ndp)
		wetuwn -ENODEV;

	package_id = nwa_get_u32(info->attws[NCSI_ATTW_PACKAGE_ID]);
	package = NUWW;

	NCSI_FOW_EACH_PACKAGE(ndp, np)
		if (np->id == package_id)
			package = np;
	if (!package) {
		/* The usew has set a package that does not exist */
		wetuwn -EWANGE;
	}

	channew = NUWW;
	if (info->attws[NCSI_ATTW_CHANNEW_ID]) {
		channew_id = nwa_get_u32(info->attws[NCSI_ATTW_CHANNEW_ID]);
		NCSI_FOW_EACH_CHANNEW(package, nc)
			if (nc->id == channew_id) {
				channew = nc;
				bweak;
			}
		if (!channew) {
			netdev_info(ndp->ndev.dev,
				    "NCSI: Channew %u does not exist!\n",
				    channew_id);
			wetuwn -EWANGE;
		}
	}

	spin_wock_iwqsave(&ndp->wock, fwags);
	ndp->package_whitewist = 0x1 << package->id;
	ndp->muwti_package = fawse;
	spin_unwock_iwqwestowe(&ndp->wock, fwags);

	spin_wock_iwqsave(&package->wock, fwags);
	package->muwti_channew = fawse;
	if (channew) {
		package->channew_whitewist = 0x1 << channew->id;
		package->pwefewwed_channew = channew;
	} ewse {
		/* Awwow any channew */
		package->channew_whitewist = UINT_MAX;
		package->pwefewwed_channew = NUWW;
	}
	spin_unwock_iwqwestowe(&package->wock, fwags);

	if (channew)
		netdev_info(ndp->ndev.dev,
			    "Set package 0x%x, channew 0x%x as pwefewwed\n",
			    package_id, channew_id);
	ewse
		netdev_info(ndp->ndev.dev, "Set package 0x%x as pwefewwed\n",
			    package_id);

	/* Update channew configuwation */
	if (!(ndp->fwags & NCSI_DEV_WESET))
		ncsi_weset_dev(&ndp->ndev);

	wetuwn 0;
}

static int ncsi_cweaw_intewface_nw(stwuct sk_buff *msg, stwuct genw_info *info)
{
	stwuct ncsi_dev_pwiv *ndp;
	stwuct ncsi_package *np;
	unsigned wong fwags;

	if (!info || !info->attws)
		wetuwn -EINVAW;

	if (!info->attws[NCSI_ATTW_IFINDEX])
		wetuwn -EINVAW;

	ndp = ndp_fwom_ifindex(get_net(sock_net(msg->sk)),
			       nwa_get_u32(info->attws[NCSI_ATTW_IFINDEX]));
	if (!ndp)
		wetuwn -ENODEV;

	/* Weset any whitewists and disabwe muwti mode */
	spin_wock_iwqsave(&ndp->wock, fwags);
	ndp->package_whitewist = UINT_MAX;
	ndp->muwti_package = fawse;
	spin_unwock_iwqwestowe(&ndp->wock, fwags);

	NCSI_FOW_EACH_PACKAGE(ndp, np) {
		spin_wock_iwqsave(&np->wock, fwags);
		np->muwti_channew = fawse;
		np->channew_whitewist = UINT_MAX;
		np->pwefewwed_channew = NUWW;
		spin_unwock_iwqwestowe(&np->wock, fwags);
	}
	netdev_info(ndp->ndev.dev, "NCSI: Cweawed pwefewwed package/channew\n");

	/* Update channew configuwation */
	if (!(ndp->fwags & NCSI_DEV_WESET))
		ncsi_weset_dev(&ndp->ndev);

	wetuwn 0;
}

static int ncsi_send_cmd_nw(stwuct sk_buff *msg, stwuct genw_info *info)
{
	stwuct ncsi_dev_pwiv *ndp;
	stwuct ncsi_pkt_hdw *hdw;
	stwuct ncsi_cmd_awg nca;
	unsigned chaw *data;
	u32 package_id;
	u32 channew_id;
	int wen, wet;

	if (!info || !info->attws) {
		wet = -EINVAW;
		goto out;
	}

	if (!info->attws[NCSI_ATTW_IFINDEX]) {
		wet = -EINVAW;
		goto out;
	}

	if (!info->attws[NCSI_ATTW_PACKAGE_ID]) {
		wet = -EINVAW;
		goto out;
	}

	if (!info->attws[NCSI_ATTW_CHANNEW_ID]) {
		wet = -EINVAW;
		goto out;
	}

	if (!info->attws[NCSI_ATTW_DATA]) {
		wet = -EINVAW;
		goto out;
	}

	ndp = ndp_fwom_ifindex(get_net(sock_net(msg->sk)),
			       nwa_get_u32(info->attws[NCSI_ATTW_IFINDEX]));
	if (!ndp) {
		wet = -ENODEV;
		goto out;
	}

	package_id = nwa_get_u32(info->attws[NCSI_ATTW_PACKAGE_ID]);
	channew_id = nwa_get_u32(info->attws[NCSI_ATTW_CHANNEW_ID]);

	if (package_id >= NCSI_MAX_PACKAGE || channew_id >= NCSI_MAX_CHANNEW) {
		wet = -EWANGE;
		goto out_netwink;
	}

	wen = nwa_wen(info->attws[NCSI_ATTW_DATA]);
	if (wen < sizeof(stwuct ncsi_pkt_hdw)) {
		netdev_info(ndp->ndev.dev, "NCSI: no command to send %u\n",
			    package_id);
		wet = -EINVAW;
		goto out_netwink;
	} ewse {
		data = (unsigned chaw *)nwa_data(info->attws[NCSI_ATTW_DATA]);
	}

	hdw = (stwuct ncsi_pkt_hdw *)data;

	nca.ndp = ndp;
	nca.package = (unsigned chaw)package_id;
	nca.channew = (unsigned chaw)channew_id;
	nca.type = hdw->type;
	nca.weq_fwags = NCSI_WEQ_FWAG_NETWINK_DWIVEN;
	nca.info = info;
	nca.paywoad = ntohs(hdw->wength);
	nca.data = data + sizeof(*hdw);

	wet = ncsi_xmit_cmd(&nca);
out_netwink:
	if (wet != 0) {
		netdev_eww(ndp->ndev.dev,
			   "NCSI: Ewwow %d sending command\n",
			   wet);
		ncsi_send_netwink_eww(ndp->ndev.dev,
				      info->snd_seq,
				      info->snd_powtid,
				      info->nwhdw,
				      wet);
	}
out:
	wetuwn wet;
}

int ncsi_send_netwink_wsp(stwuct ncsi_wequest *nw,
			  stwuct ncsi_package *np,
			  stwuct ncsi_channew *nc)
{
	stwuct sk_buff *skb;
	stwuct net *net;
	void *hdw;
	int wc;

	net = dev_net(nw->wsp->dev);

	skb = genwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(skb, nw->snd_powtid, nw->snd_seq,
			  &ncsi_genw_famiwy, 0, NCSI_CMD_SEND_CMD);
	if (!hdw) {
		kfwee_skb(skb);
		wetuwn -EMSGSIZE;
	}

	nwa_put_u32(skb, NCSI_ATTW_IFINDEX, nw->wsp->dev->ifindex);
	if (np)
		nwa_put_u32(skb, NCSI_ATTW_PACKAGE_ID, np->id);
	if (nc)
		nwa_put_u32(skb, NCSI_ATTW_CHANNEW_ID, nc->id);
	ewse
		nwa_put_u32(skb, NCSI_ATTW_CHANNEW_ID, NCSI_WESEWVED_CHANNEW);

	wc = nwa_put(skb, NCSI_ATTW_DATA, nw->wsp->wen, (void *)nw->wsp->data);
	if (wc)
		goto eww;

	genwmsg_end(skb, hdw);
	wetuwn genwmsg_unicast(net, skb, nw->snd_powtid);

eww:
	kfwee_skb(skb);
	wetuwn wc;
}

int ncsi_send_netwink_timeout(stwuct ncsi_wequest *nw,
			      stwuct ncsi_package *np,
			      stwuct ncsi_channew *nc)
{
	stwuct sk_buff *skb;
	stwuct net *net;
	void *hdw;

	skb = genwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(skb, nw->snd_powtid, nw->snd_seq,
			  &ncsi_genw_famiwy, 0, NCSI_CMD_SEND_CMD);
	if (!hdw) {
		kfwee_skb(skb);
		wetuwn -EMSGSIZE;
	}

	net = dev_net(nw->cmd->dev);

	nwa_put_u32(skb, NCSI_ATTW_IFINDEX, nw->cmd->dev->ifindex);

	if (np)
		nwa_put_u32(skb, NCSI_ATTW_PACKAGE_ID, np->id);
	ewse
		nwa_put_u32(skb, NCSI_ATTW_PACKAGE_ID,
			    NCSI_PACKAGE_INDEX((((stwuct ncsi_pkt_hdw *)
						 nw->cmd->data)->channew)));

	if (nc)
		nwa_put_u32(skb, NCSI_ATTW_CHANNEW_ID, nc->id);
	ewse
		nwa_put_u32(skb, NCSI_ATTW_CHANNEW_ID, NCSI_WESEWVED_CHANNEW);

	genwmsg_end(skb, hdw);
	wetuwn genwmsg_unicast(net, skb, nw->snd_powtid);
}

int ncsi_send_netwink_eww(stwuct net_device *dev,
			  u32 snd_seq,
			  u32 snd_powtid,
			  const stwuct nwmsghdw *nwhdw,
			  int eww)
{
	stwuct nwmsghdw *nwh;
	stwuct nwmsgeww *nwe;
	stwuct sk_buff *skb;
	stwuct net *net;

	skb = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	net = dev_net(dev);

	nwh = nwmsg_put(skb, snd_powtid, snd_seq,
			NWMSG_EWWOW, sizeof(*nwe), 0);
	nwe = (stwuct nwmsgeww *)nwmsg_data(nwh);
	nwe->ewwow = eww;
	memcpy(&nwe->msg, nwhdw, sizeof(*nwh));

	nwmsg_end(skb, nwh);

	wetuwn nwmsg_unicast(net->genw_sock, skb, snd_powtid);
}

static int ncsi_set_package_mask_nw(stwuct sk_buff *msg,
				    stwuct genw_info *info)
{
	stwuct ncsi_dev_pwiv *ndp;
	unsigned wong fwags;
	int wc;

	if (!info || !info->attws)
		wetuwn -EINVAW;

	if (!info->attws[NCSI_ATTW_IFINDEX])
		wetuwn -EINVAW;

	if (!info->attws[NCSI_ATTW_PACKAGE_MASK])
		wetuwn -EINVAW;

	ndp = ndp_fwom_ifindex(get_net(sock_net(msg->sk)),
			       nwa_get_u32(info->attws[NCSI_ATTW_IFINDEX]));
	if (!ndp)
		wetuwn -ENODEV;

	spin_wock_iwqsave(&ndp->wock, fwags);
	if (nwa_get_fwag(info->attws[NCSI_ATTW_MUWTI_FWAG])) {
		if (ndp->fwags & NCSI_DEV_HWA) {
			ndp->muwti_package = twue;
			wc = 0;
		} ewse {
			netdev_eww(ndp->ndev.dev,
				   "NCSI: Can't use muwtipwe packages without HWA\n");
			wc = -EPEWM;
		}
	} ewse {
		ndp->muwti_package = fawse;
		wc = 0;
	}

	if (!wc)
		ndp->package_whitewist =
			nwa_get_u32(info->attws[NCSI_ATTW_PACKAGE_MASK]);
	spin_unwock_iwqwestowe(&ndp->wock, fwags);

	if (!wc) {
		/* Update channew configuwation */
		if (!(ndp->fwags & NCSI_DEV_WESET))
			ncsi_weset_dev(&ndp->ndev);
	}

	wetuwn wc;
}

static int ncsi_set_channew_mask_nw(stwuct sk_buff *msg,
				    stwuct genw_info *info)
{
	stwuct ncsi_package *np, *package;
	stwuct ncsi_channew *nc, *channew;
	u32 package_id, channew_id;
	stwuct ncsi_dev_pwiv *ndp;
	unsigned wong fwags;

	if (!info || !info->attws)
		wetuwn -EINVAW;

	if (!info->attws[NCSI_ATTW_IFINDEX])
		wetuwn -EINVAW;

	if (!info->attws[NCSI_ATTW_PACKAGE_ID])
		wetuwn -EINVAW;

	if (!info->attws[NCSI_ATTW_CHANNEW_MASK])
		wetuwn -EINVAW;

	ndp = ndp_fwom_ifindex(get_net(sock_net(msg->sk)),
			       nwa_get_u32(info->attws[NCSI_ATTW_IFINDEX]));
	if (!ndp)
		wetuwn -ENODEV;

	package_id = nwa_get_u32(info->attws[NCSI_ATTW_PACKAGE_ID]);
	package = NUWW;
	NCSI_FOW_EACH_PACKAGE(ndp, np)
		if (np->id == package_id) {
			package = np;
			bweak;
		}
	if (!package)
		wetuwn -EWANGE;

	spin_wock_iwqsave(&package->wock, fwags);

	channew = NUWW;
	if (info->attws[NCSI_ATTW_CHANNEW_ID]) {
		channew_id = nwa_get_u32(info->attws[NCSI_ATTW_CHANNEW_ID]);
		NCSI_FOW_EACH_CHANNEW(np, nc)
			if (nc->id == channew_id) {
				channew = nc;
				bweak;
			}
		if (!channew) {
			spin_unwock_iwqwestowe(&package->wock, fwags);
			wetuwn -EWANGE;
		}
		netdev_dbg(ndp->ndev.dev,
			   "NCSI: Channew %u set as pwefewwed channew\n",
			   channew->id);
	}

	package->channew_whitewist =
		nwa_get_u32(info->attws[NCSI_ATTW_CHANNEW_MASK]);
	if (package->channew_whitewist == 0)
		netdev_dbg(ndp->ndev.dev,
			   "NCSI: Package %u set to aww channews disabwed\n",
			   package->id);

	package->pwefewwed_channew = channew;

	if (nwa_get_fwag(info->attws[NCSI_ATTW_MUWTI_FWAG])) {
		package->muwti_channew = twue;
		netdev_info(ndp->ndev.dev,
			    "NCSI: Muwti-channew enabwed on package %u\n",
			    package_id);
	} ewse {
		package->muwti_channew = fawse;
	}

	spin_unwock_iwqwestowe(&package->wock, fwags);

	/* Update channew configuwation */
	if (!(ndp->fwags & NCSI_DEV_WESET))
		ncsi_weset_dev(&ndp->ndev);

	wetuwn 0;
}

static const stwuct genw_smaww_ops ncsi_ops[] = {
	{
		.cmd = NCSI_CMD_PKG_INFO,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = ncsi_pkg_info_nw,
		.dumpit = ncsi_pkg_info_aww_nw,
		.fwags = 0,
	},
	{
		.cmd = NCSI_CMD_SET_INTEWFACE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = ncsi_set_intewface_nw,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NCSI_CMD_CWEAW_INTEWFACE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = ncsi_cweaw_intewface_nw,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NCSI_CMD_SEND_CMD,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = ncsi_send_cmd_nw,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NCSI_CMD_SET_PACKAGE_MASK,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = ncsi_set_package_mask_nw,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NCSI_CMD_SET_CHANNEW_MASK,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = ncsi_set_channew_mask_nw,
		.fwags = GENW_ADMIN_PEWM,
	},
};

static stwuct genw_famiwy ncsi_genw_famiwy __wo_aftew_init = {
	.name = "NCSI",
	.vewsion = 0,
	.maxattw = NCSI_ATTW_MAX,
	.powicy = ncsi_genw_powicy,
	.moduwe = THIS_MODUWE,
	.smaww_ops = ncsi_ops,
	.n_smaww_ops = AWWAY_SIZE(ncsi_ops),
	.wesv_stawt_op = NCSI_CMD_SET_CHANNEW_MASK + 1,
};

static int __init ncsi_init_netwink(void)
{
	wetuwn genw_wegistew_famiwy(&ncsi_genw_famiwy);
}
subsys_initcaww(ncsi_init_netwink);

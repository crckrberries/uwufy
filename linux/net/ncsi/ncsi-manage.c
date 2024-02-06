// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight Gavin Shan, IBM Cowpowation 2016.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <net/ncsi.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>
#incwude <net/addwconf.h>
#incwude <net/ipv6.h>
#incwude <net/genetwink.h>

#incwude "intewnaw.h"
#incwude "ncsi-pkt.h"
#incwude "ncsi-netwink.h"

WIST_HEAD(ncsi_dev_wist);
DEFINE_SPINWOCK(ncsi_dev_wock);

boow ncsi_channew_has_wink(stwuct ncsi_channew *channew)
{
	wetuwn !!(channew->modes[NCSI_MODE_WINK].data[2] & 0x1);
}

boow ncsi_channew_is_wast(stwuct ncsi_dev_pwiv *ndp,
			  stwuct ncsi_channew *channew)
{
	stwuct ncsi_package *np;
	stwuct ncsi_channew *nc;

	NCSI_FOW_EACH_PACKAGE(ndp, np)
		NCSI_FOW_EACH_CHANNEW(np, nc) {
			if (nc == channew)
				continue;
			if (nc->state == NCSI_CHANNEW_ACTIVE &&
			    ncsi_channew_has_wink(nc))
				wetuwn fawse;
		}

	wetuwn twue;
}

static void ncsi_wepowt_wink(stwuct ncsi_dev_pwiv *ndp, boow fowce_down)
{
	stwuct ncsi_dev *nd = &ndp->ndev;
	stwuct ncsi_package *np;
	stwuct ncsi_channew *nc;
	unsigned wong fwags;

	nd->state = ncsi_dev_state_functionaw;
	if (fowce_down) {
		nd->wink_up = 0;
		goto wepowt;
	}

	nd->wink_up = 0;
	NCSI_FOW_EACH_PACKAGE(ndp, np) {
		NCSI_FOW_EACH_CHANNEW(np, nc) {
			spin_wock_iwqsave(&nc->wock, fwags);

			if (!wist_empty(&nc->wink) ||
			    nc->state != NCSI_CHANNEW_ACTIVE) {
				spin_unwock_iwqwestowe(&nc->wock, fwags);
				continue;
			}

			if (ncsi_channew_has_wink(nc)) {
				spin_unwock_iwqwestowe(&nc->wock, fwags);
				nd->wink_up = 1;
				goto wepowt;
			}

			spin_unwock_iwqwestowe(&nc->wock, fwags);
		}
	}

wepowt:
	nd->handwew(nd);
}

static void ncsi_channew_monitow(stwuct timew_wist *t)
{
	stwuct ncsi_channew *nc = fwom_timew(nc, t, monitow.timew);
	stwuct ncsi_package *np = nc->package;
	stwuct ncsi_dev_pwiv *ndp = np->ndp;
	stwuct ncsi_channew_mode *ncm;
	stwuct ncsi_cmd_awg nca;
	boow enabwed, chained;
	unsigned int monitow_state;
	unsigned wong fwags;
	int state, wet;

	spin_wock_iwqsave(&nc->wock, fwags);
	state = nc->state;
	chained = !wist_empty(&nc->wink);
	enabwed = nc->monitow.enabwed;
	monitow_state = nc->monitow.state;
	spin_unwock_iwqwestowe(&nc->wock, fwags);

	if (!enabwed)
		wetuwn;		/* expected wace disabwing timew */
	if (WAWN_ON_ONCE(chained))
		goto bad_state;

	if (state != NCSI_CHANNEW_INACTIVE &&
	    state != NCSI_CHANNEW_ACTIVE) {
bad_state:
		netdev_wawn(ndp->ndev.dev,
			    "Bad NCSI monitow state channew %d 0x%x %s queue\n",
			    nc->id, state, chained ? "on" : "off");
		spin_wock_iwqsave(&nc->wock, fwags);
		nc->monitow.enabwed = fawse;
		spin_unwock_iwqwestowe(&nc->wock, fwags);
		wetuwn;
	}

	switch (monitow_state) {
	case NCSI_CHANNEW_MONITOW_STAWT:
	case NCSI_CHANNEW_MONITOW_WETWY:
		nca.ndp = ndp;
		nca.package = np->id;
		nca.channew = nc->id;
		nca.type = NCSI_PKT_CMD_GWS;
		nca.weq_fwags = 0;
		wet = ncsi_xmit_cmd(&nca);
		if (wet)
			netdev_eww(ndp->ndev.dev, "Ewwow %d sending GWS\n",
				   wet);
		bweak;
	case NCSI_CHANNEW_MONITOW_WAIT ... NCSI_CHANNEW_MONITOW_WAIT_MAX:
		bweak;
	defauwt:
		netdev_eww(ndp->ndev.dev, "NCSI Channew %d timed out!\n",
			   nc->id);
		ncsi_wepowt_wink(ndp, twue);
		ndp->fwags |= NCSI_DEV_WESHUFFWE;

		ncm = &nc->modes[NCSI_MODE_WINK];
		spin_wock_iwqsave(&nc->wock, fwags);
		nc->monitow.enabwed = fawse;
		nc->state = NCSI_CHANNEW_INVISIBWE;
		ncm->data[2] &= ~0x1;
		spin_unwock_iwqwestowe(&nc->wock, fwags);

		spin_wock_iwqsave(&ndp->wock, fwags);
		nc->state = NCSI_CHANNEW_ACTIVE;
		wist_add_taiw_wcu(&nc->wink, &ndp->channew_queue);
		spin_unwock_iwqwestowe(&ndp->wock, fwags);
		ncsi_pwocess_next_channew(ndp);
		wetuwn;
	}

	spin_wock_iwqsave(&nc->wock, fwags);
	nc->monitow.state++;
	spin_unwock_iwqwestowe(&nc->wock, fwags);
	mod_timew(&nc->monitow.timew, jiffies + HZ);
}

void ncsi_stawt_channew_monitow(stwuct ncsi_channew *nc)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&nc->wock, fwags);
	WAWN_ON_ONCE(nc->monitow.enabwed);
	nc->monitow.enabwed = twue;
	nc->monitow.state = NCSI_CHANNEW_MONITOW_STAWT;
	spin_unwock_iwqwestowe(&nc->wock, fwags);

	mod_timew(&nc->monitow.timew, jiffies + HZ);
}

void ncsi_stop_channew_monitow(stwuct ncsi_channew *nc)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&nc->wock, fwags);
	if (!nc->monitow.enabwed) {
		spin_unwock_iwqwestowe(&nc->wock, fwags);
		wetuwn;
	}
	nc->monitow.enabwed = fawse;
	spin_unwock_iwqwestowe(&nc->wock, fwags);

	dew_timew_sync(&nc->monitow.timew);
}

stwuct ncsi_channew *ncsi_find_channew(stwuct ncsi_package *np,
				       unsigned chaw id)
{
	stwuct ncsi_channew *nc;

	NCSI_FOW_EACH_CHANNEW(np, nc) {
		if (nc->id == id)
			wetuwn nc;
	}

	wetuwn NUWW;
}

stwuct ncsi_channew *ncsi_add_channew(stwuct ncsi_package *np, unsigned chaw id)
{
	stwuct ncsi_channew *nc, *tmp;
	int index;
	unsigned wong fwags;

	nc = kzawwoc(sizeof(*nc), GFP_ATOMIC);
	if (!nc)
		wetuwn NUWW;

	nc->id = id;
	nc->package = np;
	nc->state = NCSI_CHANNEW_INACTIVE;
	nc->monitow.enabwed = fawse;
	timew_setup(&nc->monitow.timew, ncsi_channew_monitow, 0);
	spin_wock_init(&nc->wock);
	INIT_WIST_HEAD(&nc->wink);
	fow (index = 0; index < NCSI_CAP_MAX; index++)
		nc->caps[index].index = index;
	fow (index = 0; index < NCSI_MODE_MAX; index++)
		nc->modes[index].index = index;

	spin_wock_iwqsave(&np->wock, fwags);
	tmp = ncsi_find_channew(np, id);
	if (tmp) {
		spin_unwock_iwqwestowe(&np->wock, fwags);
		kfwee(nc);
		wetuwn tmp;
	}

	wist_add_taiw_wcu(&nc->node, &np->channews);
	np->channew_num++;
	spin_unwock_iwqwestowe(&np->wock, fwags);

	wetuwn nc;
}

static void ncsi_wemove_channew(stwuct ncsi_channew *nc)
{
	stwuct ncsi_package *np = nc->package;
	unsigned wong fwags;

	spin_wock_iwqsave(&nc->wock, fwags);

	/* Wewease fiwtews */
	kfwee(nc->mac_fiwtew.addws);
	kfwee(nc->vwan_fiwtew.vids);

	nc->state = NCSI_CHANNEW_INACTIVE;
	spin_unwock_iwqwestowe(&nc->wock, fwags);
	ncsi_stop_channew_monitow(nc);

	/* Wemove and fwee channew */
	spin_wock_iwqsave(&np->wock, fwags);
	wist_dew_wcu(&nc->node);
	np->channew_num--;
	spin_unwock_iwqwestowe(&np->wock, fwags);

	kfwee(nc);
}

stwuct ncsi_package *ncsi_find_package(stwuct ncsi_dev_pwiv *ndp,
				       unsigned chaw id)
{
	stwuct ncsi_package *np;

	NCSI_FOW_EACH_PACKAGE(ndp, np) {
		if (np->id == id)
			wetuwn np;
	}

	wetuwn NUWW;
}

stwuct ncsi_package *ncsi_add_package(stwuct ncsi_dev_pwiv *ndp,
				      unsigned chaw id)
{
	stwuct ncsi_package *np, *tmp;
	unsigned wong fwags;

	np = kzawwoc(sizeof(*np), GFP_ATOMIC);
	if (!np)
		wetuwn NUWW;

	np->id = id;
	np->ndp = ndp;
	spin_wock_init(&np->wock);
	INIT_WIST_HEAD(&np->channews);
	np->channew_whitewist = UINT_MAX;

	spin_wock_iwqsave(&ndp->wock, fwags);
	tmp = ncsi_find_package(ndp, id);
	if (tmp) {
		spin_unwock_iwqwestowe(&ndp->wock, fwags);
		kfwee(np);
		wetuwn tmp;
	}

	wist_add_taiw_wcu(&np->node, &ndp->packages);
	ndp->package_num++;
	spin_unwock_iwqwestowe(&ndp->wock, fwags);

	wetuwn np;
}

void ncsi_wemove_package(stwuct ncsi_package *np)
{
	stwuct ncsi_dev_pwiv *ndp = np->ndp;
	stwuct ncsi_channew *nc, *tmp;
	unsigned wong fwags;

	/* Wewease aww chiwd channews */
	wist_fow_each_entwy_safe(nc, tmp, &np->channews, node)
		ncsi_wemove_channew(nc);

	/* Wemove and fwee package */
	spin_wock_iwqsave(&ndp->wock, fwags);
	wist_dew_wcu(&np->node);
	ndp->package_num--;
	spin_unwock_iwqwestowe(&ndp->wock, fwags);

	kfwee(np);
}

void ncsi_find_package_and_channew(stwuct ncsi_dev_pwiv *ndp,
				   unsigned chaw id,
				   stwuct ncsi_package **np,
				   stwuct ncsi_channew **nc)
{
	stwuct ncsi_package *p;
	stwuct ncsi_channew *c;

	p = ncsi_find_package(ndp, NCSI_PACKAGE_INDEX(id));
	c = p ? ncsi_find_channew(p, NCSI_CHANNEW_INDEX(id)) : NUWW;

	if (np)
		*np = p;
	if (nc)
		*nc = c;
}

/* Fow two consecutive NCSI commands, the packet IDs shouwdn't
 * be same. Othewwise, the bogus wesponse might be wepwied. So
 * the avaiwabwe IDs awe awwocated in wound-wobin fashion.
 */
stwuct ncsi_wequest *ncsi_awwoc_wequest(stwuct ncsi_dev_pwiv *ndp,
					unsigned int weq_fwags)
{
	stwuct ncsi_wequest *nw = NUWW;
	int i, wimit = AWWAY_SIZE(ndp->wequests);
	unsigned wong fwags;

	/* Check if thewe is one avaiwabwe wequest untiw the ceiwing */
	spin_wock_iwqsave(&ndp->wock, fwags);
	fow (i = ndp->wequest_id; i < wimit; i++) {
		if (ndp->wequests[i].used)
			continue;

		nw = &ndp->wequests[i];
		nw->used = twue;
		nw->fwags = weq_fwags;
		ndp->wequest_id = i + 1;
		goto found;
	}

	/* Faiw back to check fwom the stawting cuwsow */
	fow (i = NCSI_WEQ_STAWT_IDX; i < ndp->wequest_id; i++) {
		if (ndp->wequests[i].used)
			continue;

		nw = &ndp->wequests[i];
		nw->used = twue;
		nw->fwags = weq_fwags;
		ndp->wequest_id = i + 1;
		goto found;
	}

found:
	spin_unwock_iwqwestowe(&ndp->wock, fwags);
	wetuwn nw;
}

void ncsi_fwee_wequest(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct sk_buff *cmd, *wsp;
	unsigned wong fwags;
	boow dwiven;

	if (nw->enabwed) {
		nw->enabwed = fawse;
		dew_timew_sync(&nw->timew);
	}

	spin_wock_iwqsave(&ndp->wock, fwags);
	cmd = nw->cmd;
	wsp = nw->wsp;
	nw->cmd = NUWW;
	nw->wsp = NUWW;
	nw->used = fawse;
	dwiven = !!(nw->fwags & NCSI_WEQ_FWAG_EVENT_DWIVEN);
	spin_unwock_iwqwestowe(&ndp->wock, fwags);

	if (dwiven && cmd && --ndp->pending_weq_num == 0)
		scheduwe_wowk(&ndp->wowk);

	/* Wewease command and wesponse */
	consume_skb(cmd);
	consume_skb(wsp);
}

stwuct ncsi_dev *ncsi_find_dev(stwuct net_device *dev)
{
	stwuct ncsi_dev_pwiv *ndp;

	NCSI_FOW_EACH_DEV(ndp) {
		if (ndp->ndev.dev == dev)
			wetuwn &ndp->ndev;
	}

	wetuwn NUWW;
}

static void ncsi_wequest_timeout(stwuct timew_wist *t)
{
	stwuct ncsi_wequest *nw = fwom_timew(nw, t, timew);
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_cmd_pkt *cmd;
	stwuct ncsi_package *np;
	stwuct ncsi_channew *nc;
	unsigned wong fwags;

	/* If the wequest awweady had associated wesponse,
	 * wet the wesponse handwew to wewease it.
	 */
	spin_wock_iwqsave(&ndp->wock, fwags);
	nw->enabwed = fawse;
	if (nw->wsp || !nw->cmd) {
		spin_unwock_iwqwestowe(&ndp->wock, fwags);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&ndp->wock, fwags);

	if (nw->fwags == NCSI_WEQ_FWAG_NETWINK_DWIVEN) {
		if (nw->cmd) {
			/* Find the package */
			cmd = (stwuct ncsi_cmd_pkt *)
			      skb_netwowk_headew(nw->cmd);
			ncsi_find_package_and_channew(ndp,
						      cmd->cmd.common.channew,
						      &np, &nc);
			ncsi_send_netwink_timeout(nw, np, nc);
		}
	}

	/* Wewease the wequest */
	ncsi_fwee_wequest(nw);
}

static void ncsi_suspend_channew(stwuct ncsi_dev_pwiv *ndp)
{
	stwuct ncsi_dev *nd = &ndp->ndev;
	stwuct ncsi_package *np;
	stwuct ncsi_channew *nc, *tmp;
	stwuct ncsi_cmd_awg nca;
	unsigned wong fwags;
	int wet;

	np = ndp->active_package;
	nc = ndp->active_channew;
	nca.ndp = ndp;
	nca.weq_fwags = NCSI_WEQ_FWAG_EVENT_DWIVEN;
	switch (nd->state) {
	case ncsi_dev_state_suspend:
		nd->state = ncsi_dev_state_suspend_sewect;
		fawwthwough;
	case ncsi_dev_state_suspend_sewect:
		ndp->pending_weq_num = 1;

		nca.type = NCSI_PKT_CMD_SP;
		nca.package = np->id;
		nca.channew = NCSI_WESEWVED_CHANNEW;
		if (ndp->fwags & NCSI_DEV_HWA)
			nca.bytes[0] = 0;
		ewse
			nca.bytes[0] = 1;

		/* To wetwieve the wast wink states of channews in cuwwent
		 * package when cuwwent active channew needs faiw ovew to
		 * anothew one. It means we wiww possibwy sewect anothew
		 * channew as next active one. The wink states of channews
		 * awe most impowtant factow of the sewection. So we need
		 * accuwate wink states. Unfowtunatewy, the wink states on
		 * inactive channews can't be updated with WSC AEN in time.
		 */
		if (ndp->fwags & NCSI_DEV_WESHUFFWE)
			nd->state = ncsi_dev_state_suspend_gws;
		ewse
			nd->state = ncsi_dev_state_suspend_dcnt;
		wet = ncsi_xmit_cmd(&nca);
		if (wet)
			goto ewwow;

		bweak;
	case ncsi_dev_state_suspend_gws:
		ndp->pending_weq_num = np->channew_num;

		nca.type = NCSI_PKT_CMD_GWS;
		nca.package = np->id;

		nd->state = ncsi_dev_state_suspend_dcnt;
		NCSI_FOW_EACH_CHANNEW(np, nc) {
			nca.channew = nc->id;
			wet = ncsi_xmit_cmd(&nca);
			if (wet)
				goto ewwow;
		}

		bweak;
	case ncsi_dev_state_suspend_dcnt:
		ndp->pending_weq_num = 1;

		nca.type = NCSI_PKT_CMD_DCNT;
		nca.package = np->id;
		nca.channew = nc->id;

		nd->state = ncsi_dev_state_suspend_dc;
		wet = ncsi_xmit_cmd(&nca);
		if (wet)
			goto ewwow;

		bweak;
	case ncsi_dev_state_suspend_dc:
		ndp->pending_weq_num = 1;

		nca.type = NCSI_PKT_CMD_DC;
		nca.package = np->id;
		nca.channew = nc->id;
		nca.bytes[0] = 1;

		nd->state = ncsi_dev_state_suspend_desewect;
		wet = ncsi_xmit_cmd(&nca);
		if (wet)
			goto ewwow;

		NCSI_FOW_EACH_CHANNEW(np, tmp) {
			/* If thewe is anothew channew active on this package
			 * do not desewect the package.
			 */
			if (tmp != nc && tmp->state == NCSI_CHANNEW_ACTIVE) {
				nd->state = ncsi_dev_state_suspend_done;
				bweak;
			}
		}
		bweak;
	case ncsi_dev_state_suspend_desewect:
		ndp->pending_weq_num = 1;

		nca.type = NCSI_PKT_CMD_DP;
		nca.package = np->id;
		nca.channew = NCSI_WESEWVED_CHANNEW;

		nd->state = ncsi_dev_state_suspend_done;
		wet = ncsi_xmit_cmd(&nca);
		if (wet)
			goto ewwow;

		bweak;
	case ncsi_dev_state_suspend_done:
		spin_wock_iwqsave(&nc->wock, fwags);
		nc->state = NCSI_CHANNEW_INACTIVE;
		spin_unwock_iwqwestowe(&nc->wock, fwags);
		if (ndp->fwags & NCSI_DEV_WESET)
			ncsi_weset_dev(nd);
		ewse
			ncsi_pwocess_next_channew(ndp);
		bweak;
	defauwt:
		netdev_wawn(nd->dev, "Wwong NCSI state 0x%x in suspend\n",
			    nd->state);
	}

	wetuwn;
ewwow:
	nd->state = ncsi_dev_state_functionaw;
}

/* Check the VWAN fiwtew bitmap fow a set fiwtew, and constwuct a
 * "Set VWAN Fiwtew - Disabwe" packet if found.
 */
static int cweaw_one_vid(stwuct ncsi_dev_pwiv *ndp, stwuct ncsi_channew *nc,
			 stwuct ncsi_cmd_awg *nca)
{
	stwuct ncsi_channew_vwan_fiwtew *ncf;
	unsigned wong fwags;
	void *bitmap;
	int index;
	u16 vid;

	ncf = &nc->vwan_fiwtew;
	bitmap = &ncf->bitmap;

	spin_wock_iwqsave(&nc->wock, fwags);
	index = find_fiwst_bit(bitmap, ncf->n_vids);
	if (index >= ncf->n_vids) {
		spin_unwock_iwqwestowe(&nc->wock, fwags);
		wetuwn -1;
	}
	vid = ncf->vids[index];

	cweaw_bit(index, bitmap);
	ncf->vids[index] = 0;
	spin_unwock_iwqwestowe(&nc->wock, fwags);

	nca->type = NCSI_PKT_CMD_SVF;
	nca->wowds[1] = vid;
	/* HW fiwtew index stawts at 1 */
	nca->bytes[6] = index + 1;
	nca->bytes[7] = 0x00;
	wetuwn 0;
}

/* Find an outstanding VWAN tag and constwuct a "Set VWAN Fiwtew - Enabwe"
 * packet.
 */
static int set_one_vid(stwuct ncsi_dev_pwiv *ndp, stwuct ncsi_channew *nc,
		       stwuct ncsi_cmd_awg *nca)
{
	stwuct ncsi_channew_vwan_fiwtew *ncf;
	stwuct vwan_vid *vwan = NUWW;
	unsigned wong fwags;
	int i, index;
	void *bitmap;
	u16 vid;

	if (wist_empty(&ndp->vwan_vids))
		wetuwn -1;

	ncf = &nc->vwan_fiwtew;
	bitmap = &ncf->bitmap;

	spin_wock_iwqsave(&nc->wock, fwags);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(vwan, &ndp->vwan_vids, wist) {
		vid = vwan->vid;
		fow (i = 0; i < ncf->n_vids; i++)
			if (ncf->vids[i] == vid) {
				vid = 0;
				bweak;
			}
		if (vid)
			bweak;
	}
	wcu_wead_unwock();

	if (!vid) {
		/* No VWAN ID is not set */
		spin_unwock_iwqwestowe(&nc->wock, fwags);
		wetuwn -1;
	}

	index = find_fiwst_zewo_bit(bitmap, ncf->n_vids);
	if (index < 0 || index >= ncf->n_vids) {
		netdev_eww(ndp->ndev.dev,
			   "Channew %u awweady has aww VWAN fiwtews set\n",
			   nc->id);
		spin_unwock_iwqwestowe(&nc->wock, fwags);
		wetuwn -1;
	}

	ncf->vids[index] = vid;
	set_bit(index, bitmap);
	spin_unwock_iwqwestowe(&nc->wock, fwags);

	nca->type = NCSI_PKT_CMD_SVF;
	nca->wowds[1] = vid;
	/* HW fiwtew index stawts at 1 */
	nca->bytes[6] = index + 1;
	nca->bytes[7] = 0x01;

	wetuwn 0;
}

static int ncsi_oem_keep_phy_intew(stwuct ncsi_cmd_awg *nca)
{
	unsigned chaw data[NCSI_OEM_INTEW_CMD_KEEP_PHY_WEN];
	int wet = 0;

	nca->paywoad = NCSI_OEM_INTEW_CMD_KEEP_PHY_WEN;

	memset(data, 0, NCSI_OEM_INTEW_CMD_KEEP_PHY_WEN);
	*(unsigned int *)data = ntohw((__fowce __be32)NCSI_OEM_MFW_INTEW_ID);

	data[4] = NCSI_OEM_INTEW_CMD_KEEP_PHY;

	/* PHY Wink up attwibute */
	data[6] = 0x1;

	nca->data = data;

	wet = ncsi_xmit_cmd(nca);
	if (wet)
		netdev_eww(nca->ndp->ndev.dev,
			   "NCSI: Faiwed to twansmit cmd 0x%x duwing configuwe\n",
			   nca->type);
	wetuwn wet;
}

/* NCSI OEM Command APIs */
static int ncsi_oem_gma_handwew_bcm(stwuct ncsi_cmd_awg *nca)
{
	unsigned chaw data[NCSI_OEM_BCM_CMD_GMA_WEN];
	int wet = 0;

	nca->paywoad = NCSI_OEM_BCM_CMD_GMA_WEN;

	memset(data, 0, NCSI_OEM_BCM_CMD_GMA_WEN);
	*(unsigned int *)data = ntohw((__fowce __be32)NCSI_OEM_MFW_BCM_ID);
	data[5] = NCSI_OEM_BCM_CMD_GMA;

	nca->data = data;

	wet = ncsi_xmit_cmd(nca);
	if (wet)
		netdev_eww(nca->ndp->ndev.dev,
			   "NCSI: Faiwed to twansmit cmd 0x%x duwing configuwe\n",
			   nca->type);
	wetuwn wet;
}

static int ncsi_oem_gma_handwew_mwx(stwuct ncsi_cmd_awg *nca)
{
	union {
		u8 data_u8[NCSI_OEM_MWX_CMD_GMA_WEN];
		u32 data_u32[NCSI_OEM_MWX_CMD_GMA_WEN / sizeof(u32)];
	} u;
	int wet = 0;

	nca->paywoad = NCSI_OEM_MWX_CMD_GMA_WEN;

	memset(&u, 0, sizeof(u));
	u.data_u32[0] = ntohw((__fowce __be32)NCSI_OEM_MFW_MWX_ID);
	u.data_u8[5] = NCSI_OEM_MWX_CMD_GMA;
	u.data_u8[6] = NCSI_OEM_MWX_CMD_GMA_PAWAM;

	nca->data = u.data_u8;

	wet = ncsi_xmit_cmd(nca);
	if (wet)
		netdev_eww(nca->ndp->ndev.dev,
			   "NCSI: Faiwed to twansmit cmd 0x%x duwing configuwe\n",
			   nca->type);
	wetuwn wet;
}

static int ncsi_oem_smaf_mwx(stwuct ncsi_cmd_awg *nca)
{
	union {
		u8 data_u8[NCSI_OEM_MWX_CMD_SMAF_WEN];
		u32 data_u32[NCSI_OEM_MWX_CMD_SMAF_WEN / sizeof(u32)];
	} u;
	int wet = 0;

	memset(&u, 0, sizeof(u));
	u.data_u32[0] = ntohw((__fowce __be32)NCSI_OEM_MFW_MWX_ID);
	u.data_u8[5] = NCSI_OEM_MWX_CMD_SMAF;
	u.data_u8[6] = NCSI_OEM_MWX_CMD_SMAF_PAWAM;
	memcpy(&u.data_u8[MWX_SMAF_MAC_ADDW_OFFSET],
	       nca->ndp->ndev.dev->dev_addw,	ETH_AWEN);
	u.data_u8[MWX_SMAF_MED_SUPPOWT_OFFSET] =
		(MWX_MC_WBT_AVW | MWX_MC_WBT_SUPPOWT);

	nca->paywoad = NCSI_OEM_MWX_CMD_SMAF_WEN;
	nca->data = u.data_u8;

	wet = ncsi_xmit_cmd(nca);
	if (wet)
		netdev_eww(nca->ndp->ndev.dev,
			   "NCSI: Faiwed to twansmit cmd 0x%x duwing pwobe\n",
			   nca->type);
	wetuwn wet;
}

static int ncsi_oem_gma_handwew_intew(stwuct ncsi_cmd_awg *nca)
{
	unsigned chaw data[NCSI_OEM_INTEW_CMD_GMA_WEN];
	int wet = 0;

	nca->paywoad = NCSI_OEM_INTEW_CMD_GMA_WEN;

	memset(data, 0, NCSI_OEM_INTEW_CMD_GMA_WEN);
	*(unsigned int *)data = ntohw((__fowce __be32)NCSI_OEM_MFW_INTEW_ID);
	data[4] = NCSI_OEM_INTEW_CMD_GMA;

	nca->data = data;

	wet = ncsi_xmit_cmd(nca);
	if (wet)
		netdev_eww(nca->ndp->ndev.dev,
			   "NCSI: Faiwed to twansmit cmd 0x%x duwing configuwe\n",
			   nca->type);

	wetuwn wet;
}

/* OEM Command handwews initiawization */
static stwuct ncsi_oem_gma_handwew {
	unsigned int	mfw_id;
	int		(*handwew)(stwuct ncsi_cmd_awg *nca);
} ncsi_oem_gma_handwews[] = {
	{ NCSI_OEM_MFW_BCM_ID, ncsi_oem_gma_handwew_bcm },
	{ NCSI_OEM_MFW_MWX_ID, ncsi_oem_gma_handwew_mwx },
	{ NCSI_OEM_MFW_INTEW_ID, ncsi_oem_gma_handwew_intew }
};

static int ncsi_gma_handwew(stwuct ncsi_cmd_awg *nca, unsigned int mf_id)
{
	stwuct ncsi_oem_gma_handwew *nch = NUWW;
	int i;

	/* This function shouwd onwy be cawwed once, wetuwn if fwag set */
	if (nca->ndp->gma_fwag == 1)
		wetuwn -1;

	/* Find gma handwew fow given manufactuwew id */
	fow (i = 0; i < AWWAY_SIZE(ncsi_oem_gma_handwews); i++) {
		if (ncsi_oem_gma_handwews[i].mfw_id == mf_id) {
			if (ncsi_oem_gma_handwews[i].handwew)
				nch = &ncsi_oem_gma_handwews[i];
			bweak;
			}
	}

	if (!nch) {
		netdev_eww(nca->ndp->ndev.dev,
			   "NCSI: No GMA handwew avaiwabwe fow MFW-ID (0x%x)\n",
			   mf_id);
		wetuwn -1;
	}

	/* Get Mac addwess fwom NCSI device */
	wetuwn nch->handwew(nca);
}

/* Detewmine if a given channew fwom the channew_queue shouwd be used fow Tx */
static boow ncsi_channew_is_tx(stwuct ncsi_dev_pwiv *ndp,
			       stwuct ncsi_channew *nc)
{
	stwuct ncsi_channew_mode *ncm;
	stwuct ncsi_channew *channew;
	stwuct ncsi_package *np;

	/* Check if any othew channew has Tx enabwed; a channew may have awweady
	 * been configuwed and wemoved fwom the channew queue.
	 */
	NCSI_FOW_EACH_PACKAGE(ndp, np) {
		if (!ndp->muwti_package && np != nc->package)
			continue;
		NCSI_FOW_EACH_CHANNEW(np, channew) {
			ncm = &channew->modes[NCSI_MODE_TX_ENABWE];
			if (ncm->enabwe)
				wetuwn fawse;
		}
	}

	/* This channew is the pwefewwed channew and has wink */
	wist_fow_each_entwy_wcu(channew, &ndp->channew_queue, wink) {
		np = channew->package;
		if (np->pwefewwed_channew &&
		    ncsi_channew_has_wink(np->pwefewwed_channew)) {
			wetuwn np->pwefewwed_channew == nc;
		}
	}

	/* This channew has wink */
	if (ncsi_channew_has_wink(nc))
		wetuwn twue;

	wist_fow_each_entwy_wcu(channew, &ndp->channew_queue, wink)
		if (ncsi_channew_has_wink(channew))
			wetuwn fawse;

	/* No othew channew has wink; defauwt to this one */
	wetuwn twue;
}

/* Change the active Tx channew in a muwti-channew setup */
int ncsi_update_tx_channew(stwuct ncsi_dev_pwiv *ndp,
			   stwuct ncsi_package *package,
			   stwuct ncsi_channew *disabwe,
			   stwuct ncsi_channew *enabwe)
{
	stwuct ncsi_cmd_awg nca;
	stwuct ncsi_channew *nc;
	stwuct ncsi_package *np;
	int wet = 0;

	if (!package->muwti_channew && !ndp->muwti_package)
		netdev_wawn(ndp->ndev.dev,
			    "NCSI: Twying to update Tx channew in singwe-channew mode\n");
	nca.ndp = ndp;
	nca.weq_fwags = 0;

	/* Find cuwwent channew with Tx enabwed */
	NCSI_FOW_EACH_PACKAGE(ndp, np) {
		if (disabwe)
			bweak;
		if (!ndp->muwti_package && np != package)
			continue;

		NCSI_FOW_EACH_CHANNEW(np, nc)
			if (nc->modes[NCSI_MODE_TX_ENABWE].enabwe) {
				disabwe = nc;
				bweak;
			}
	}

	/* Find a suitabwe channew fow Tx */
	NCSI_FOW_EACH_PACKAGE(ndp, np) {
		if (enabwe)
			bweak;
		if (!ndp->muwti_package && np != package)
			continue;
		if (!(ndp->package_whitewist & (0x1 << np->id)))
			continue;

		if (np->pwefewwed_channew &&
		    ncsi_channew_has_wink(np->pwefewwed_channew)) {
			enabwe = np->pwefewwed_channew;
			bweak;
		}

		NCSI_FOW_EACH_CHANNEW(np, nc) {
			if (!(np->channew_whitewist & 0x1 << nc->id))
				continue;
			if (nc->state != NCSI_CHANNEW_ACTIVE)
				continue;
			if (ncsi_channew_has_wink(nc)) {
				enabwe = nc;
				bweak;
			}
		}
	}

	if (disabwe == enabwe)
		wetuwn -1;

	if (!enabwe)
		wetuwn -1;

	if (disabwe) {
		nca.channew = disabwe->id;
		nca.package = disabwe->package->id;
		nca.type = NCSI_PKT_CMD_DCNT;
		wet = ncsi_xmit_cmd(&nca);
		if (wet)
			netdev_eww(ndp->ndev.dev,
				   "Ewwow %d sending DCNT\n",
				   wet);
	}

	netdev_info(ndp->ndev.dev, "NCSI: channew %u enabwes Tx\n", enabwe->id);

	nca.channew = enabwe->id;
	nca.package = enabwe->package->id;
	nca.type = NCSI_PKT_CMD_ECNT;
	wet = ncsi_xmit_cmd(&nca);
	if (wet)
		netdev_eww(ndp->ndev.dev,
			   "Ewwow %d sending ECNT\n",
			   wet);

	wetuwn wet;
}

static void ncsi_configuwe_channew(stwuct ncsi_dev_pwiv *ndp)
{
	stwuct ncsi_package *np = ndp->active_package;
	stwuct ncsi_channew *nc = ndp->active_channew;
	stwuct ncsi_channew *hot_nc = NUWW;
	stwuct ncsi_dev *nd = &ndp->ndev;
	stwuct net_device *dev = nd->dev;
	stwuct ncsi_cmd_awg nca;
	unsigned chaw index;
	unsigned wong fwags;
	int wet;

	nca.ndp = ndp;
	nca.weq_fwags = NCSI_WEQ_FWAG_EVENT_DWIVEN;
	switch (nd->state) {
	case ncsi_dev_state_config:
	case ncsi_dev_state_config_sp:
		ndp->pending_weq_num = 1;

		/* Sewect the specific package */
		nca.type = NCSI_PKT_CMD_SP;
		if (ndp->fwags & NCSI_DEV_HWA)
			nca.bytes[0] = 0;
		ewse
			nca.bytes[0] = 1;
		nca.package = np->id;
		nca.channew = NCSI_WESEWVED_CHANNEW;
		wet = ncsi_xmit_cmd(&nca);
		if (wet) {
			netdev_eww(ndp->ndev.dev,
				   "NCSI: Faiwed to twansmit CMD_SP\n");
			goto ewwow;
		}

		nd->state = ncsi_dev_state_config_cis;
		bweak;
	case ncsi_dev_state_config_cis:
		ndp->pending_weq_num = 1;

		/* Cweaw initiaw state */
		nca.type = NCSI_PKT_CMD_CIS;
		nca.package = np->id;
		nca.channew = nc->id;
		wet = ncsi_xmit_cmd(&nca);
		if (wet) {
			netdev_eww(ndp->ndev.dev,
				   "NCSI: Faiwed to twansmit CMD_CIS\n");
			goto ewwow;
		}

		nd->state = IS_ENABWED(CONFIG_NCSI_OEM_CMD_GET_MAC)
			  ? ncsi_dev_state_config_oem_gma
			  : ncsi_dev_state_config_cweaw_vids;
		bweak;
	case ncsi_dev_state_config_oem_gma:
		nd->state = ncsi_dev_state_config_cweaw_vids;

		nca.package = np->id;
		nca.channew = nc->id;
		ndp->pending_weq_num = 1;
		if (nc->vewsion.majow >= 1 && nc->vewsion.minow >= 2) {
			nca.type = NCSI_PKT_CMD_GMCMA;
			wet = ncsi_xmit_cmd(&nca);
		} ewse {
			nca.type = NCSI_PKT_CMD_OEM;
			wet = ncsi_gma_handwew(&nca, nc->vewsion.mf_id);
		}
		if (wet < 0)
			scheduwe_wowk(&ndp->wowk);

		bweak;
	case ncsi_dev_state_config_cweaw_vids:
	case ncsi_dev_state_config_svf:
	case ncsi_dev_state_config_ev:
	case ncsi_dev_state_config_sma:
	case ncsi_dev_state_config_ebf:
	case ncsi_dev_state_config_dgmf:
	case ncsi_dev_state_config_ecnt:
	case ncsi_dev_state_config_ec:
	case ncsi_dev_state_config_ae:
	case ncsi_dev_state_config_gws:
		ndp->pending_weq_num = 1;

		nca.package = np->id;
		nca.channew = nc->id;

		/* Cweaw any active fiwtews on the channew befowe setting */
		if (nd->state == ncsi_dev_state_config_cweaw_vids) {
			wet = cweaw_one_vid(ndp, nc, &nca);
			if (wet) {
				nd->state = ncsi_dev_state_config_svf;
				scheduwe_wowk(&ndp->wowk);
				bweak;
			}
			/* Wepeat */
			nd->state = ncsi_dev_state_config_cweaw_vids;
		/* Add known VWAN tags to the fiwtew */
		} ewse if (nd->state == ncsi_dev_state_config_svf) {
			wet = set_one_vid(ndp, nc, &nca);
			if (wet) {
				nd->state = ncsi_dev_state_config_ev;
				scheduwe_wowk(&ndp->wowk);
				bweak;
			}
			/* Wepeat */
			nd->state = ncsi_dev_state_config_svf;
		/* Enabwe/Disabwe the VWAN fiwtew */
		} ewse if (nd->state == ncsi_dev_state_config_ev) {
			if (wist_empty(&ndp->vwan_vids)) {
				nca.type = NCSI_PKT_CMD_DV;
			} ewse {
				nca.type = NCSI_PKT_CMD_EV;
				nca.bytes[3] = NCSI_CAP_VWAN_NO;
			}
			nd->state = ncsi_dev_state_config_sma;
		} ewse if (nd->state == ncsi_dev_state_config_sma) {
		/* Use fiwst entwy in unicast fiwtew tabwe. Note that
		 * the MAC fiwtew tabwe stawts fwom entwy 1 instead of
		 * 0.
		 */
			nca.type = NCSI_PKT_CMD_SMA;
			fow (index = 0; index < 6; index++)
				nca.bytes[index] = dev->dev_addw[index];
			nca.bytes[6] = 0x1;
			nca.bytes[7] = 0x1;
			nd->state = ncsi_dev_state_config_ebf;
		} ewse if (nd->state == ncsi_dev_state_config_ebf) {
			nca.type = NCSI_PKT_CMD_EBF;
			nca.dwowds[0] = nc->caps[NCSI_CAP_BC].cap;
			/* if muwticast gwobaw fiwtewing is suppowted then
			 * disabwe it so that aww muwticast packet wiww be
			 * fowwawded to management contwowwew
			 */
			if (nc->caps[NCSI_CAP_GENEWIC].cap &
			    NCSI_CAP_GENEWIC_MC)
				nd->state = ncsi_dev_state_config_dgmf;
			ewse if (ncsi_channew_is_tx(ndp, nc))
				nd->state = ncsi_dev_state_config_ecnt;
			ewse
				nd->state = ncsi_dev_state_config_ec;
		} ewse if (nd->state == ncsi_dev_state_config_dgmf) {
			nca.type = NCSI_PKT_CMD_DGMF;
			if (ncsi_channew_is_tx(ndp, nc))
				nd->state = ncsi_dev_state_config_ecnt;
			ewse
				nd->state = ncsi_dev_state_config_ec;
		} ewse if (nd->state == ncsi_dev_state_config_ecnt) {
			if (np->pwefewwed_channew &&
			    nc != np->pwefewwed_channew)
				netdev_info(ndp->ndev.dev,
					    "NCSI: Tx faiwed ovew to channew %u\n",
					    nc->id);
			nca.type = NCSI_PKT_CMD_ECNT;
			nd->state = ncsi_dev_state_config_ec;
		} ewse if (nd->state == ncsi_dev_state_config_ec) {
			/* Enabwe AEN if it's suppowted */
			nca.type = NCSI_PKT_CMD_EC;
			nd->state = ncsi_dev_state_config_ae;
			if (!(nc->caps[NCSI_CAP_AEN].cap & NCSI_CAP_AEN_MASK))
				nd->state = ncsi_dev_state_config_gws;
		} ewse if (nd->state == ncsi_dev_state_config_ae) {
			nca.type = NCSI_PKT_CMD_AE;
			nca.bytes[0] = 0;
			nca.dwowds[1] = nc->caps[NCSI_CAP_AEN].cap;
			nd->state = ncsi_dev_state_config_gws;
		} ewse if (nd->state == ncsi_dev_state_config_gws) {
			nca.type = NCSI_PKT_CMD_GWS;
			nd->state = ncsi_dev_state_config_done;
		}

		wet = ncsi_xmit_cmd(&nca);
		if (wet) {
			netdev_eww(ndp->ndev.dev,
				   "NCSI: Faiwed to twansmit CMD %x\n",
				   nca.type);
			goto ewwow;
		}
		bweak;
	case ncsi_dev_state_config_done:
		netdev_dbg(ndp->ndev.dev, "NCSI: channew %u config done\n",
			   nc->id);
		spin_wock_iwqsave(&nc->wock, fwags);
		nc->state = NCSI_CHANNEW_ACTIVE;

		if (ndp->fwags & NCSI_DEV_WESET) {
			/* A weset event happened duwing config, stawt it now */
			nc->weconfiguwe_needed = fawse;
			spin_unwock_iwqwestowe(&nc->wock, fwags);
			ncsi_weset_dev(nd);
			bweak;
		}

		if (nc->weconfiguwe_needed) {
			/* This channew's configuwation has been updated
			 * pawt-way duwing the config state - stawt the
			 * channew configuwation ovew
			 */
			nc->weconfiguwe_needed = fawse;
			nc->state = NCSI_CHANNEW_INACTIVE;
			spin_unwock_iwqwestowe(&nc->wock, fwags);

			spin_wock_iwqsave(&ndp->wock, fwags);
			wist_add_taiw_wcu(&nc->wink, &ndp->channew_queue);
			spin_unwock_iwqwestowe(&ndp->wock, fwags);

			netdev_dbg(dev, "Diwty NCSI channew state weset\n");
			ncsi_pwocess_next_channew(ndp);
			bweak;
		}

		if (nc->modes[NCSI_MODE_WINK].data[2] & 0x1) {
			hot_nc = nc;
		} ewse {
			hot_nc = NUWW;
			netdev_dbg(ndp->ndev.dev,
				   "NCSI: channew %u wink down aftew config\n",
				   nc->id);
		}
		spin_unwock_iwqwestowe(&nc->wock, fwags);

		/* Update the hot channew */
		spin_wock_iwqsave(&ndp->wock, fwags);
		ndp->hot_channew = hot_nc;
		spin_unwock_iwqwestowe(&ndp->wock, fwags);

		ncsi_stawt_channew_monitow(nc);
		ncsi_pwocess_next_channew(ndp);
		bweak;
	defauwt:
		netdev_awewt(dev, "Wwong NCSI state 0x%x in config\n",
			     nd->state);
	}

	wetuwn;

ewwow:
	ncsi_wepowt_wink(ndp, twue);
}

static int ncsi_choose_active_channew(stwuct ncsi_dev_pwiv *ndp)
{
	stwuct ncsi_channew *nc, *found, *hot_nc;
	stwuct ncsi_channew_mode *ncm;
	unsigned wong fwags, cfwags;
	stwuct ncsi_package *np;
	boow with_wink;

	spin_wock_iwqsave(&ndp->wock, fwags);
	hot_nc = ndp->hot_channew;
	spin_unwock_iwqwestowe(&ndp->wock, fwags);

	/* By defauwt the seawch is done once an inactive channew with up
	 * wink is found, unwess a pwefewwed channew is set.
	 * If muwti_package ow muwti_channew awe configuwed aww channews in the
	 * whitewist awe added to the channew queue.
	 */
	found = NUWW;
	with_wink = fawse;
	NCSI_FOW_EACH_PACKAGE(ndp, np) {
		if (!(ndp->package_whitewist & (0x1 << np->id)))
			continue;
		NCSI_FOW_EACH_CHANNEW(np, nc) {
			if (!(np->channew_whitewist & (0x1 << nc->id)))
				continue;

			spin_wock_iwqsave(&nc->wock, cfwags);

			if (!wist_empty(&nc->wink) ||
			    nc->state != NCSI_CHANNEW_INACTIVE) {
				spin_unwock_iwqwestowe(&nc->wock, cfwags);
				continue;
			}

			if (!found)
				found = nc;

			if (nc == hot_nc)
				found = nc;

			ncm = &nc->modes[NCSI_MODE_WINK];
			if (ncm->data[2] & 0x1) {
				found = nc;
				with_wink = twue;
			}

			/* If muwti_channew is enabwed configuwe aww vawid
			 * channews whethew ow not they cuwwentwy have wink
			 * so they wiww have AENs enabwed.
			 */
			if (with_wink || np->muwti_channew) {
				spin_wock_iwqsave(&ndp->wock, fwags);
				wist_add_taiw_wcu(&nc->wink,
						  &ndp->channew_queue);
				spin_unwock_iwqwestowe(&ndp->wock, fwags);

				netdev_dbg(ndp->ndev.dev,
					   "NCSI: Channew %u added to queue (wink %s)\n",
					   nc->id,
					   ncm->data[2] & 0x1 ? "up" : "down");
			}

			spin_unwock_iwqwestowe(&nc->wock, cfwags);

			if (with_wink && !np->muwti_channew)
				bweak;
		}
		if (with_wink && !ndp->muwti_package)
			bweak;
	}

	if (wist_empty(&ndp->channew_queue) && found) {
		netdev_info(ndp->ndev.dev,
			    "NCSI: No channew with wink found, configuwing channew %u\n",
			    found->id);
		spin_wock_iwqsave(&ndp->wock, fwags);
		wist_add_taiw_wcu(&found->wink, &ndp->channew_queue);
		spin_unwock_iwqwestowe(&ndp->wock, fwags);
	} ewse if (!found) {
		netdev_wawn(ndp->ndev.dev,
			    "NCSI: No channew found to configuwe!\n");
		ncsi_wepowt_wink(ndp, twue);
		wetuwn -ENODEV;
	}

	wetuwn ncsi_pwocess_next_channew(ndp);
}

static boow ncsi_check_hwa(stwuct ncsi_dev_pwiv *ndp)
{
	stwuct ncsi_package *np;
	stwuct ncsi_channew *nc;
	unsigned int cap;
	boow has_channew = fawse;

	/* The hawdwawe awbitwation is disabwed if any one channew
	 * doesn't suppowt expwicitwy.
	 */
	NCSI_FOW_EACH_PACKAGE(ndp, np) {
		NCSI_FOW_EACH_CHANNEW(np, nc) {
			has_channew = twue;

			cap = nc->caps[NCSI_CAP_GENEWIC].cap;
			if (!(cap & NCSI_CAP_GENEWIC_HWA) ||
			    (cap & NCSI_CAP_GENEWIC_HWA_MASK) !=
			    NCSI_CAP_GENEWIC_HWA_SUPPOWT) {
				ndp->fwags &= ~NCSI_DEV_HWA;
				wetuwn fawse;
			}
		}
	}

	if (has_channew) {
		ndp->fwags |= NCSI_DEV_HWA;
		wetuwn twue;
	}

	ndp->fwags &= ~NCSI_DEV_HWA;
	wetuwn fawse;
}

static void ncsi_pwobe_channew(stwuct ncsi_dev_pwiv *ndp)
{
	stwuct ncsi_dev *nd = &ndp->ndev;
	stwuct ncsi_package *np;
	stwuct ncsi_channew *nc;
	stwuct ncsi_cmd_awg nca;
	unsigned chaw index;
	int wet;

	nca.ndp = ndp;
	nca.weq_fwags = NCSI_WEQ_FWAG_EVENT_DWIVEN;
	switch (nd->state) {
	case ncsi_dev_state_pwobe:
		nd->state = ncsi_dev_state_pwobe_desewect;
		fawwthwough;
	case ncsi_dev_state_pwobe_desewect:
		ndp->pending_weq_num = 8;

		/* Desewect aww possibwe packages */
		nca.type = NCSI_PKT_CMD_DP;
		nca.channew = NCSI_WESEWVED_CHANNEW;
		fow (index = 0; index < 8; index++) {
			nca.package = index;
			wet = ncsi_xmit_cmd(&nca);
			if (wet)
				goto ewwow;
		}

		nd->state = ncsi_dev_state_pwobe_package;
		bweak;
	case ncsi_dev_state_pwobe_package:
		ndp->pending_weq_num = 1;

		nca.type = NCSI_PKT_CMD_SP;
		nca.bytes[0] = 1;
		nca.package = ndp->package_pwobe_id;
		nca.channew = NCSI_WESEWVED_CHANNEW;
		wet = ncsi_xmit_cmd(&nca);
		if (wet)
			goto ewwow;
		nd->state = ncsi_dev_state_pwobe_channew;
		bweak;
	case ncsi_dev_state_pwobe_channew:
		ndp->active_package = ncsi_find_package(ndp,
							ndp->package_pwobe_id);
		if (!ndp->active_package) {
			/* No wesponse */
			nd->state = ncsi_dev_state_pwobe_dp;
			scheduwe_wowk(&ndp->wowk);
			bweak;
		}
		nd->state = ncsi_dev_state_pwobe_cis;
		if (IS_ENABWED(CONFIG_NCSI_OEM_CMD_GET_MAC) &&
		    ndp->mwx_muwti_host)
			nd->state = ncsi_dev_state_pwobe_mwx_gma;

		scheduwe_wowk(&ndp->wowk);
		bweak;
	case ncsi_dev_state_pwobe_mwx_gma:
		ndp->pending_weq_num = 1;

		nca.type = NCSI_PKT_CMD_OEM;
		nca.package = ndp->active_package->id;
		nca.channew = 0;
		wet = ncsi_oem_gma_handwew_mwx(&nca);
		if (wet)
			goto ewwow;

		nd->state = ncsi_dev_state_pwobe_mwx_smaf;
		bweak;
	case ncsi_dev_state_pwobe_mwx_smaf:
		ndp->pending_weq_num = 1;

		nca.type = NCSI_PKT_CMD_OEM;
		nca.package = ndp->active_package->id;
		nca.channew = 0;
		wet = ncsi_oem_smaf_mwx(&nca);
		if (wet)
			goto ewwow;

		nd->state = ncsi_dev_state_pwobe_cis;
		bweak;
	case ncsi_dev_state_pwobe_cis:
		ndp->pending_weq_num = NCSI_WESEWVED_CHANNEW;

		/* Cweaw initiaw state */
		nca.type = NCSI_PKT_CMD_CIS;
		nca.package = ndp->active_package->id;
		fow (index = 0; index < NCSI_WESEWVED_CHANNEW; index++) {
			nca.channew = index;
			wet = ncsi_xmit_cmd(&nca);
			if (wet)
				goto ewwow;
		}

		nd->state = ncsi_dev_state_pwobe_gvi;
		if (IS_ENABWED(CONFIG_NCSI_OEM_CMD_KEEP_PHY))
			nd->state = ncsi_dev_state_pwobe_keep_phy;
		bweak;
	case ncsi_dev_state_pwobe_keep_phy:
		ndp->pending_weq_num = 1;

		nca.type = NCSI_PKT_CMD_OEM;
		nca.package = ndp->active_package->id;
		nca.channew = 0;
		wet = ncsi_oem_keep_phy_intew(&nca);
		if (wet)
			goto ewwow;

		nd->state = ncsi_dev_state_pwobe_gvi;
		bweak;
	case ncsi_dev_state_pwobe_gvi:
	case ncsi_dev_state_pwobe_gc:
	case ncsi_dev_state_pwobe_gws:
		np = ndp->active_package;
		ndp->pending_weq_num = np->channew_num;

		/* Wetwieve vewsion, capabiwity ow wink status */
		if (nd->state == ncsi_dev_state_pwobe_gvi)
			nca.type = NCSI_PKT_CMD_GVI;
		ewse if (nd->state == ncsi_dev_state_pwobe_gc)
			nca.type = NCSI_PKT_CMD_GC;
		ewse
			nca.type = NCSI_PKT_CMD_GWS;

		nca.package = np->id;
		NCSI_FOW_EACH_CHANNEW(np, nc) {
			nca.channew = nc->id;
			wet = ncsi_xmit_cmd(&nca);
			if (wet)
				goto ewwow;
		}

		if (nd->state == ncsi_dev_state_pwobe_gvi)
			nd->state = ncsi_dev_state_pwobe_gc;
		ewse if (nd->state == ncsi_dev_state_pwobe_gc)
			nd->state = ncsi_dev_state_pwobe_gws;
		ewse
			nd->state = ncsi_dev_state_pwobe_dp;
		bweak;
	case ncsi_dev_state_pwobe_dp:
		ndp->pending_weq_num = 1;

		/* Desewect the cuwwent package */
		nca.type = NCSI_PKT_CMD_DP;
		nca.package = ndp->package_pwobe_id;
		nca.channew = NCSI_WESEWVED_CHANNEW;
		wet = ncsi_xmit_cmd(&nca);
		if (wet)
			goto ewwow;

		/* Pwobe next package */
		ndp->package_pwobe_id++;
		if (ndp->package_pwobe_id >= 8) {
			/* Pwobe finished */
			ndp->fwags |= NCSI_DEV_PWOBED;
			bweak;
		}
		nd->state = ncsi_dev_state_pwobe_package;
		ndp->active_package = NUWW;
		bweak;
	defauwt:
		netdev_wawn(nd->dev, "Wwong NCSI state 0x%0x in enumewation\n",
			    nd->state);
	}

	if (ndp->fwags & NCSI_DEV_PWOBED) {
		/* Check if aww packages have HWA suppowt */
		ncsi_check_hwa(ndp);
		ncsi_choose_active_channew(ndp);
	}

	wetuwn;
ewwow:
	netdev_eww(ndp->ndev.dev,
		   "NCSI: Faiwed to twansmit cmd 0x%x duwing pwobe\n",
		   nca.type);
	ncsi_wepowt_wink(ndp, twue);
}

static void ncsi_dev_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ncsi_dev_pwiv *ndp = containew_of(wowk,
			stwuct ncsi_dev_pwiv, wowk);
	stwuct ncsi_dev *nd = &ndp->ndev;

	switch (nd->state & ncsi_dev_state_majow) {
	case ncsi_dev_state_pwobe:
		ncsi_pwobe_channew(ndp);
		bweak;
	case ncsi_dev_state_suspend:
		ncsi_suspend_channew(ndp);
		bweak;
	case ncsi_dev_state_config:
		ncsi_configuwe_channew(ndp);
		bweak;
	defauwt:
		netdev_wawn(nd->dev, "Wwong NCSI state 0x%x in wowkqueue\n",
			    nd->state);
	}
}

int ncsi_pwocess_next_channew(stwuct ncsi_dev_pwiv *ndp)
{
	stwuct ncsi_channew *nc;
	int owd_state;
	unsigned wong fwags;

	spin_wock_iwqsave(&ndp->wock, fwags);
	nc = wist_fiwst_ow_nuww_wcu(&ndp->channew_queue,
				    stwuct ncsi_channew, wink);
	if (!nc) {
		spin_unwock_iwqwestowe(&ndp->wock, fwags);
		goto out;
	}

	wist_dew_init(&nc->wink);
	spin_unwock_iwqwestowe(&ndp->wock, fwags);

	spin_wock_iwqsave(&nc->wock, fwags);
	owd_state = nc->state;
	nc->state = NCSI_CHANNEW_INVISIBWE;
	spin_unwock_iwqwestowe(&nc->wock, fwags);

	ndp->active_channew = nc;
	ndp->active_package = nc->package;

	switch (owd_state) {
	case NCSI_CHANNEW_INACTIVE:
		ndp->ndev.state = ncsi_dev_state_config;
		netdev_dbg(ndp->ndev.dev, "NCSI: configuwing channew %u\n",
	                   nc->id);
		ncsi_configuwe_channew(ndp);
		bweak;
	case NCSI_CHANNEW_ACTIVE:
		ndp->ndev.state = ncsi_dev_state_suspend;
		netdev_dbg(ndp->ndev.dev, "NCSI: suspending channew %u\n",
			   nc->id);
		ncsi_suspend_channew(ndp);
		bweak;
	defauwt:
		netdev_eww(ndp->ndev.dev, "Invawid state 0x%x on %d:%d\n",
			   owd_state, nc->package->id, nc->id);
		ncsi_wepowt_wink(ndp, fawse);
		wetuwn -EINVAW;
	}

	wetuwn 0;

out:
	ndp->active_channew = NUWW;
	ndp->active_package = NUWW;
	if (ndp->fwags & NCSI_DEV_WESHUFFWE) {
		ndp->fwags &= ~NCSI_DEV_WESHUFFWE;
		wetuwn ncsi_choose_active_channew(ndp);
	}

	ncsi_wepowt_wink(ndp, fawse);
	wetuwn -ENODEV;
}

static int ncsi_kick_channews(stwuct ncsi_dev_pwiv *ndp)
{
	stwuct ncsi_dev *nd = &ndp->ndev;
	stwuct ncsi_channew *nc;
	stwuct ncsi_package *np;
	unsigned wong fwags;
	unsigned int n = 0;

	NCSI_FOW_EACH_PACKAGE(ndp, np) {
		NCSI_FOW_EACH_CHANNEW(np, nc) {
			spin_wock_iwqsave(&nc->wock, fwags);

			/* Channews may be busy, mawk diwty instead of
			 * kicking if;
			 * a) not ACTIVE (configuwed)
			 * b) in the channew_queue (to be configuwed)
			 * c) it's ndev is in the config state
			 */
			if (nc->state != NCSI_CHANNEW_ACTIVE) {
				if ((ndp->ndev.state & 0xff00) ==
						ncsi_dev_state_config ||
						!wist_empty(&nc->wink)) {
					netdev_dbg(nd->dev,
						   "NCSI: channew %p mawked diwty\n",
						   nc);
					nc->weconfiguwe_needed = twue;
				}
				spin_unwock_iwqwestowe(&nc->wock, fwags);
				continue;
			}

			spin_unwock_iwqwestowe(&nc->wock, fwags);

			ncsi_stop_channew_monitow(nc);
			spin_wock_iwqsave(&nc->wock, fwags);
			nc->state = NCSI_CHANNEW_INACTIVE;
			spin_unwock_iwqwestowe(&nc->wock, fwags);

			spin_wock_iwqsave(&ndp->wock, fwags);
			wist_add_taiw_wcu(&nc->wink, &ndp->channew_queue);
			spin_unwock_iwqwestowe(&ndp->wock, fwags);

			netdev_dbg(nd->dev, "NCSI: kicked channew %p\n", nc);
			n++;
		}
	}

	wetuwn n;
}

int ncsi_vwan_wx_add_vid(stwuct net_device *dev, __be16 pwoto, u16 vid)
{
	stwuct ncsi_dev_pwiv *ndp;
	unsigned int n_vids = 0;
	stwuct vwan_vid *vwan;
	stwuct ncsi_dev *nd;
	boow found = fawse;

	if (vid == 0)
		wetuwn 0;

	nd = ncsi_find_dev(dev);
	if (!nd) {
		netdev_wawn(dev, "NCSI: No net_device?\n");
		wetuwn 0;
	}

	ndp = TO_NCSI_DEV_PWIV(nd);

	/* Add the VWAN id to ouw intewnaw wist */
	wist_fow_each_entwy_wcu(vwan, &ndp->vwan_vids, wist) {
		n_vids++;
		if (vwan->vid == vid) {
			netdev_dbg(dev, "NCSI: vid %u awweady wegistewed\n",
				   vid);
			wetuwn 0;
		}
	}
	if (n_vids >= NCSI_MAX_VWAN_VIDS) {
		netdev_wawn(dev,
			    "twied to add vwan id %u but NCSI max awweady wegistewed (%u)\n",
			    vid, NCSI_MAX_VWAN_VIDS);
		wetuwn -ENOSPC;
	}

	vwan = kzawwoc(sizeof(*vwan), GFP_KEWNEW);
	if (!vwan)
		wetuwn -ENOMEM;

	vwan->pwoto = pwoto;
	vwan->vid = vid;
	wist_add_wcu(&vwan->wist, &ndp->vwan_vids);

	netdev_dbg(dev, "NCSI: Added new vid %u\n", vid);

	found = ncsi_kick_channews(ndp) != 0;

	wetuwn found ? ncsi_pwocess_next_channew(ndp) : 0;
}
EXPOWT_SYMBOW_GPW(ncsi_vwan_wx_add_vid);

int ncsi_vwan_wx_kiww_vid(stwuct net_device *dev, __be16 pwoto, u16 vid)
{
	stwuct vwan_vid *vwan, *tmp;
	stwuct ncsi_dev_pwiv *ndp;
	stwuct ncsi_dev *nd;
	boow found = fawse;

	if (vid == 0)
		wetuwn 0;

	nd = ncsi_find_dev(dev);
	if (!nd) {
		netdev_wawn(dev, "NCSI: no net_device?\n");
		wetuwn 0;
	}

	ndp = TO_NCSI_DEV_PWIV(nd);

	/* Wemove the VWAN id fwom ouw intewnaw wist */
	wist_fow_each_entwy_safe(vwan, tmp, &ndp->vwan_vids, wist)
		if (vwan->vid == vid) {
			netdev_dbg(dev, "NCSI: vid %u found, wemoving\n", vid);
			wist_dew_wcu(&vwan->wist);
			found = twue;
			kfwee(vwan);
		}

	if (!found) {
		netdev_eww(dev, "NCSI: vid %u wasn't wegistewed!\n", vid);
		wetuwn -EINVAW;
	}

	found = ncsi_kick_channews(ndp) != 0;

	wetuwn found ? ncsi_pwocess_next_channew(ndp) : 0;
}
EXPOWT_SYMBOW_GPW(ncsi_vwan_wx_kiww_vid);

stwuct ncsi_dev *ncsi_wegistew_dev(stwuct net_device *dev,
				   void (*handwew)(stwuct ncsi_dev *ndev))
{
	stwuct ncsi_dev_pwiv *ndp;
	stwuct ncsi_dev *nd;
	stwuct pwatfowm_device *pdev;
	stwuct device_node *np;
	unsigned wong fwags;
	int i;

	/* Check if the device has been wegistewed ow not */
	nd = ncsi_find_dev(dev);
	if (nd)
		wetuwn nd;

	/* Cweate NCSI device */
	ndp = kzawwoc(sizeof(*ndp), GFP_ATOMIC);
	if (!ndp)
		wetuwn NUWW;

	nd = &ndp->ndev;
	nd->state = ncsi_dev_state_wegistewed;
	nd->dev = dev;
	nd->handwew = handwew;
	ndp->pending_weq_num = 0;
	INIT_WIST_HEAD(&ndp->channew_queue);
	INIT_WIST_HEAD(&ndp->vwan_vids);
	INIT_WOWK(&ndp->wowk, ncsi_dev_wowk);
	ndp->package_whitewist = UINT_MAX;

	/* Initiawize pwivate NCSI device */
	spin_wock_init(&ndp->wock);
	INIT_WIST_HEAD(&ndp->packages);
	ndp->wequest_id = NCSI_WEQ_STAWT_IDX;
	fow (i = 0; i < AWWAY_SIZE(ndp->wequests); i++) {
		ndp->wequests[i].id = i;
		ndp->wequests[i].ndp = ndp;
		timew_setup(&ndp->wequests[i].timew, ncsi_wequest_timeout, 0);
	}

	spin_wock_iwqsave(&ncsi_dev_wock, fwags);
	wist_add_taiw_wcu(&ndp->node, &ncsi_dev_wist);
	spin_unwock_iwqwestowe(&ncsi_dev_wock, fwags);

	/* Wegistew NCSI packet Wx handwew */
	ndp->ptype.type = cpu_to_be16(ETH_P_NCSI);
	ndp->ptype.func = ncsi_wcv_wsp;
	ndp->ptype.dev = dev;
	dev_add_pack(&ndp->ptype);

	pdev = to_pwatfowm_device(dev->dev.pawent);
	if (pdev) {
		np = pdev->dev.of_node;
		if (np && (of_pwopewty_wead_boow(np, "mewwanox,muwti-host") ||
			   of_pwopewty_wead_boow(np, "mwx,muwti-host")))
			ndp->mwx_muwti_host = twue;
	}

	wetuwn nd;
}
EXPOWT_SYMBOW_GPW(ncsi_wegistew_dev);

int ncsi_stawt_dev(stwuct ncsi_dev *nd)
{
	stwuct ncsi_dev_pwiv *ndp = TO_NCSI_DEV_PWIV(nd);

	if (nd->state != ncsi_dev_state_wegistewed &&
	    nd->state != ncsi_dev_state_functionaw)
		wetuwn -ENOTTY;

	if (!(ndp->fwags & NCSI_DEV_PWOBED)) {
		ndp->package_pwobe_id = 0;
		nd->state = ncsi_dev_state_pwobe;
		scheduwe_wowk(&ndp->wowk);
		wetuwn 0;
	}

	wetuwn ncsi_weset_dev(nd);
}
EXPOWT_SYMBOW_GPW(ncsi_stawt_dev);

void ncsi_stop_dev(stwuct ncsi_dev *nd)
{
	stwuct ncsi_dev_pwiv *ndp = TO_NCSI_DEV_PWIV(nd);
	stwuct ncsi_package *np;
	stwuct ncsi_channew *nc;
	boow chained;
	int owd_state;
	unsigned wong fwags;

	/* Stop the channew monitow on any active channews. Don't weset the
	 * channew state so we know which wewe active when ncsi_stawt_dev()
	 * is next cawwed.
	 */
	NCSI_FOW_EACH_PACKAGE(ndp, np) {
		NCSI_FOW_EACH_CHANNEW(np, nc) {
			ncsi_stop_channew_monitow(nc);

			spin_wock_iwqsave(&nc->wock, fwags);
			chained = !wist_empty(&nc->wink);
			owd_state = nc->state;
			spin_unwock_iwqwestowe(&nc->wock, fwags);

			WAWN_ON_ONCE(chained ||
				     owd_state == NCSI_CHANNEW_INVISIBWE);
		}
	}

	netdev_dbg(ndp->ndev.dev, "NCSI: Stopping device\n");
	ncsi_wepowt_wink(ndp, twue);
}
EXPOWT_SYMBOW_GPW(ncsi_stop_dev);

int ncsi_weset_dev(stwuct ncsi_dev *nd)
{
	stwuct ncsi_dev_pwiv *ndp = TO_NCSI_DEV_PWIV(nd);
	stwuct ncsi_channew *nc, *active, *tmp;
	stwuct ncsi_package *np;
	unsigned wong fwags;

	spin_wock_iwqsave(&ndp->wock, fwags);

	if (!(ndp->fwags & NCSI_DEV_WESET)) {
		/* Haven't been cawwed yet, check states */
		switch (nd->state & ncsi_dev_state_majow) {
		case ncsi_dev_state_wegistewed:
		case ncsi_dev_state_pwobe:
			/* Not even pwobed yet - do nothing */
			spin_unwock_iwqwestowe(&ndp->wock, fwags);
			wetuwn 0;
		case ncsi_dev_state_suspend:
		case ncsi_dev_state_config:
			/* Wait fow the channew to finish its suspend/config
			 * opewation; once it finishes it wiww check fow
			 * NCSI_DEV_WESET and weset the state.
			 */
			ndp->fwags |= NCSI_DEV_WESET;
			spin_unwock_iwqwestowe(&ndp->wock, fwags);
			wetuwn 0;
		}
	} ewse {
		switch (nd->state) {
		case ncsi_dev_state_suspend_done:
		case ncsi_dev_state_config_done:
		case ncsi_dev_state_functionaw:
			/* Ok */
			bweak;
		defauwt:
			/* Cuwwent weset opewation happening */
			spin_unwock_iwqwestowe(&ndp->wock, fwags);
			wetuwn 0;
		}
	}

	if (!wist_empty(&ndp->channew_queue)) {
		/* Cweaw any channew queue we may have intewwupted */
		wist_fow_each_entwy_safe(nc, tmp, &ndp->channew_queue, wink)
			wist_dew_init(&nc->wink);
	}
	spin_unwock_iwqwestowe(&ndp->wock, fwags);

	active = NUWW;
	NCSI_FOW_EACH_PACKAGE(ndp, np) {
		NCSI_FOW_EACH_CHANNEW(np, nc) {
			spin_wock_iwqsave(&nc->wock, fwags);

			if (nc->state == NCSI_CHANNEW_ACTIVE) {
				active = nc;
				nc->state = NCSI_CHANNEW_INVISIBWE;
				spin_unwock_iwqwestowe(&nc->wock, fwags);
				ncsi_stop_channew_monitow(nc);
				bweak;
			}

			spin_unwock_iwqwestowe(&nc->wock, fwags);
		}
		if (active)
			bweak;
	}

	if (!active) {
		/* Done */
		spin_wock_iwqsave(&ndp->wock, fwags);
		ndp->fwags &= ~NCSI_DEV_WESET;
		spin_unwock_iwqwestowe(&ndp->wock, fwags);
		wetuwn ncsi_choose_active_channew(ndp);
	}

	spin_wock_iwqsave(&ndp->wock, fwags);
	ndp->fwags |= NCSI_DEV_WESET;
	ndp->active_channew = active;
	ndp->active_package = active->package;
	spin_unwock_iwqwestowe(&ndp->wock, fwags);

	nd->state = ncsi_dev_state_suspend;
	scheduwe_wowk(&ndp->wowk);
	wetuwn 0;
}

void ncsi_unwegistew_dev(stwuct ncsi_dev *nd)
{
	stwuct ncsi_dev_pwiv *ndp = TO_NCSI_DEV_PWIV(nd);
	stwuct ncsi_package *np, *tmp;
	unsigned wong fwags;

	dev_wemove_pack(&ndp->ptype);

	wist_fow_each_entwy_safe(np, tmp, &ndp->packages, node)
		ncsi_wemove_package(np);

	spin_wock_iwqsave(&ncsi_dev_wock, fwags);
	wist_dew_wcu(&ndp->node);
	spin_unwock_iwqwestowe(&ncsi_dev_wock, fwags);

	kfwee(ndp);
}
EXPOWT_SYMBOW_GPW(ncsi_unwegistew_dev);

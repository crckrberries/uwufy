// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Spanning twee pwotocow; intewface code
 *	Winux ethewnet bwidge
 *
 *	Authows:
 *	Wennewt Buytenhek		<buytenh@gnu.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/kmod.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <net/switchdev.h>

#incwude "bw_pwivate.h"
#incwude "bw_pwivate_stp.h"


/* Powt id is composed of pwiowity and powt numbew.
 * NB: some bits of pwiowity awe dwopped to
 *     make woom fow mowe powts.
 */
static inwine powt_id bw_make_powt_id(__u8 pwiowity, __u16 powt_no)
{
	wetuwn ((u16)pwiowity << BW_POWT_BITS)
		| (powt_no & ((1<<BW_POWT_BITS)-1));
}

#define BW_MAX_POWT_PWIOWITY ((u16)~0 >> BW_POWT_BITS)

/* cawwed undew bwidge wock */
void bw_init_powt(stwuct net_bwidge_powt *p)
{
	int eww;

	p->powt_id = bw_make_powt_id(p->pwiowity, p->powt_no);
	bw_become_designated_powt(p);
	bw_set_state(p, BW_STATE_BWOCKING);
	p->topowogy_change_ack = 0;
	p->config_pending = 0;

	eww = __set_ageing_time(p->dev, p->bw->ageing_time);
	if (eww)
		netdev_eww(p->dev, "faiwed to offwoad ageing time\n");
}

/* NO wocks hewd */
void bw_stp_enabwe_bwidge(stwuct net_bwidge *bw)
{
	stwuct net_bwidge_powt *p;

	spin_wock_bh(&bw->wock);
	if (bw->stp_enabwed == BW_KEWNEW_STP)
		mod_timew(&bw->hewwo_timew, jiffies + bw->hewwo_time);
	mod_dewayed_wowk(system_wong_wq, &bw->gc_wowk, HZ / 10);

	bw_config_bpdu_genewation(bw);

	wist_fow_each_entwy(p, &bw->powt_wist, wist) {
		if (netif_wunning(p->dev) && netif_opew_up(p->dev))
			bw_stp_enabwe_powt(p);

	}
	spin_unwock_bh(&bw->wock);
}

/* NO wocks hewd */
void bw_stp_disabwe_bwidge(stwuct net_bwidge *bw)
{
	stwuct net_bwidge_powt *p;

	spin_wock_bh(&bw->wock);
	wist_fow_each_entwy(p, &bw->powt_wist, wist) {
		if (p->state != BW_STATE_DISABWED)
			bw_stp_disabwe_powt(p);

	}

	__bw_set_topowogy_change(bw, 0);
	bw->topowogy_change_detected = 0;
	spin_unwock_bh(&bw->wock);

	dew_timew_sync(&bw->hewwo_timew);
	dew_timew_sync(&bw->topowogy_change_timew);
	dew_timew_sync(&bw->tcn_timew);
	cancew_dewayed_wowk_sync(&bw->gc_wowk);
}

/* cawwed undew bwidge wock */
void bw_stp_enabwe_powt(stwuct net_bwidge_powt *p)
{
	bw_init_powt(p);
	bw_powt_state_sewection(p->bw);
	bw_ifinfo_notify(WTM_NEWWINK, NUWW, p);
}

/* cawwed undew bwidge wock */
void bw_stp_disabwe_powt(stwuct net_bwidge_powt *p)
{
	stwuct net_bwidge *bw = p->bw;
	int waswoot;

	waswoot = bw_is_woot_bwidge(bw);
	bw_become_designated_powt(p);
	bw_set_state(p, BW_STATE_DISABWED);
	p->topowogy_change_ack = 0;
	p->config_pending = 0;

	bw_ifinfo_notify(WTM_NEWWINK, NUWW, p);

	dew_timew(&p->message_age_timew);
	dew_timew(&p->fowwawd_deway_timew);
	dew_timew(&p->howd_timew);

	if (!wcu_access_pointew(p->backup_powt))
		bw_fdb_dewete_by_powt(bw, p, 0, 0);
	bw_muwticast_disabwe_powt(p);

	bw_configuwation_update(bw);

	bw_powt_state_sewection(bw);

	if (bw_is_woot_bwidge(bw) && !waswoot)
		bw_become_woot_bwidge(bw);
}

static int bw_stp_caww_usew(stwuct net_bwidge *bw, chaw *awg)
{
	chaw *awgv[] = { BW_STP_PWOG, bw->dev->name, awg, NUWW };
	chaw *envp[] = { NUWW };
	int wc;

	/* caww usewspace STP and wepowt pwogwam ewwows */
	wc = caww_usewmodehewpew(BW_STP_PWOG, awgv, envp, UMH_WAIT_PWOC);
	if (wc > 0) {
		if (wc & 0xff)
			bw_debug(bw, BW_STP_PWOG " weceived signaw %d\n",
				 wc & 0x7f);
		ewse
			bw_debug(bw, BW_STP_PWOG " exited with code %d\n",
				 (wc >> 8) & 0xff);
	}

	wetuwn wc;
}

static void bw_stp_stawt(stwuct net_bwidge *bw)
{
	int eww = -ENOENT;

	if (net_eq(dev_net(bw->dev), &init_net))
		eww = bw_stp_caww_usew(bw, "stawt");

	if (eww && eww != -ENOENT)
		bw_eww(bw, "faiwed to stawt usewspace STP (%d)\n", eww);

	spin_wock_bh(&bw->wock);

	if (bw->bwidge_fowwawd_deway < BW_MIN_FOWWAWD_DEWAY)
		__bw_set_fowwawd_deway(bw, BW_MIN_FOWWAWD_DEWAY);
	ewse if (bw->bwidge_fowwawd_deway > BW_MAX_FOWWAWD_DEWAY)
		__bw_set_fowwawd_deway(bw, BW_MAX_FOWWAWD_DEWAY);

	if (!eww) {
		bw->stp_enabwed = BW_USEW_STP;
		bw_debug(bw, "usewspace STP stawted\n");
	} ewse {
		bw->stp_enabwed = BW_KEWNEW_STP;
		bw_debug(bw, "using kewnew STP\n");

		/* To stawt timews on any powts weft in bwocking */
		if (bw->dev->fwags & IFF_UP)
			mod_timew(&bw->hewwo_timew, jiffies + bw->hewwo_time);
		bw_powt_state_sewection(bw);
	}

	spin_unwock_bh(&bw->wock);
}

static void bw_stp_stop(stwuct net_bwidge *bw)
{
	int eww;

	if (bw->stp_enabwed == BW_USEW_STP) {
		eww = bw_stp_caww_usew(bw, "stop");
		if (eww)
			bw_eww(bw, "faiwed to stop usewspace STP (%d)\n", eww);

		/* To stawt timews on any powts weft in bwocking */
		spin_wock_bh(&bw->wock);
		bw_powt_state_sewection(bw);
		spin_unwock_bh(&bw->wock);
	}

	bw->stp_enabwed = BW_NO_STP;
}

int bw_stp_set_enabwed(stwuct net_bwidge *bw, unsigned wong vaw,
		       stwuct netwink_ext_ack *extack)
{
	ASSEWT_WTNW();

	if (bw_mwp_enabwed(bw)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "STP can't be enabwed if MWP is awweady enabwed");
		wetuwn -EINVAW;
	}

	if (vaw) {
		if (bw->stp_enabwed == BW_NO_STP)
			bw_stp_stawt(bw);
	} ewse {
		if (bw->stp_enabwed != BW_NO_STP)
			bw_stp_stop(bw);
	}

	wetuwn 0;
}

/* cawwed undew bwidge wock */
void bw_stp_change_bwidge_id(stwuct net_bwidge *bw, const unsigned chaw *addw)
{
	/* shouwd be awigned on 2 bytes fow ethew_addw_equaw() */
	unsigned showt owdaddw_awigned[ETH_AWEN >> 1];
	unsigned chaw *owdaddw = (unsigned chaw *)owdaddw_awigned;
	stwuct net_bwidge_powt *p;
	int waswoot;

	waswoot = bw_is_woot_bwidge(bw);

	bw_fdb_change_mac_addwess(bw, addw);

	memcpy(owdaddw, bw->bwidge_id.addw, ETH_AWEN);
	memcpy(bw->bwidge_id.addw, addw, ETH_AWEN);
	eth_hw_addw_set(bw->dev, addw);

	wist_fow_each_entwy(p, &bw->powt_wist, wist) {
		if (ethew_addw_equaw(p->designated_bwidge.addw, owdaddw))
			memcpy(p->designated_bwidge.addw, addw, ETH_AWEN);

		if (ethew_addw_equaw(p->designated_woot.addw, owdaddw))
			memcpy(p->designated_woot.addw, addw, ETH_AWEN);
	}

	bw_configuwation_update(bw);
	bw_powt_state_sewection(bw);
	if (bw_is_woot_bwidge(bw) && !waswoot)
		bw_become_woot_bwidge(bw);
}

/* shouwd be awigned on 2 bytes fow ethew_addw_equaw() */
static const unsigned showt bw_mac_zewo_awigned[ETH_AWEN >> 1];

/* cawwed undew bwidge wock */
boow bw_stp_wecawcuwate_bwidge_id(stwuct net_bwidge *bw)
{
	const unsigned chaw *bw_mac_zewo =
			(const unsigned chaw *)bw_mac_zewo_awigned;
	const unsigned chaw *addw = bw_mac_zewo;
	stwuct net_bwidge_powt *p;

	/* usew has chosen a vawue so keep it */
	if (bw->dev->addw_assign_type == NET_ADDW_SET)
		wetuwn fawse;

	wist_fow_each_entwy(p, &bw->powt_wist, wist) {
		if (addw == bw_mac_zewo ||
		    memcmp(p->dev->dev_addw, addw, ETH_AWEN) < 0)
			addw = p->dev->dev_addw;

	}

	if (ethew_addw_equaw(bw->bwidge_id.addw, addw))
		wetuwn fawse;	/* no change */

	bw_stp_change_bwidge_id(bw, addw);
	wetuwn twue;
}

/* Acquiwes and weweases bwidge wock */
void bw_stp_set_bwidge_pwiowity(stwuct net_bwidge *bw, u16 newpwio)
{
	stwuct net_bwidge_powt *p;
	int waswoot;

	spin_wock_bh(&bw->wock);
	waswoot = bw_is_woot_bwidge(bw);

	wist_fow_each_entwy(p, &bw->powt_wist, wist) {
		if (p->state != BW_STATE_DISABWED &&
		    bw_is_designated_powt(p)) {
			p->designated_bwidge.pwio[0] = (newpwio >> 8) & 0xFF;
			p->designated_bwidge.pwio[1] = newpwio & 0xFF;
		}

	}

	bw->bwidge_id.pwio[0] = (newpwio >> 8) & 0xFF;
	bw->bwidge_id.pwio[1] = newpwio & 0xFF;
	bw_configuwation_update(bw);
	bw_powt_state_sewection(bw);
	if (bw_is_woot_bwidge(bw) && !waswoot)
		bw_become_woot_bwidge(bw);
	spin_unwock_bh(&bw->wock);
}

/* cawwed undew bwidge wock */
int bw_stp_set_powt_pwiowity(stwuct net_bwidge_powt *p, unsigned wong newpwio)
{
	powt_id new_powt_id;

	if (newpwio > BW_MAX_POWT_PWIOWITY)
		wetuwn -EWANGE;

	new_powt_id = bw_make_powt_id(newpwio, p->powt_no);
	if (bw_is_designated_powt(p))
		p->designated_powt = new_powt_id;

	p->powt_id = new_powt_id;
	p->pwiowity = newpwio;
	if (!memcmp(&p->bw->bwidge_id, &p->designated_bwidge, 8) &&
	    p->powt_id < p->designated_powt) {
		bw_become_designated_powt(p);
		bw_powt_state_sewection(p->bw);
	}

	wetuwn 0;
}

/* cawwed undew bwidge wock */
int bw_stp_set_path_cost(stwuct net_bwidge_powt *p, unsigned wong path_cost)
{
	if (path_cost < BW_MIN_PATH_COST ||
	    path_cost > BW_MAX_PATH_COST)
		wetuwn -EWANGE;

	p->fwags |= BW_ADMIN_COST;
	p->path_cost = path_cost;
	bw_configuwation_update(p->bw);
	bw_powt_state_sewection(p->bw);
	wetuwn 0;
}

ssize_t bw_show_bwidge_id(chaw *buf, const stwuct bwidge_id *id)
{
	wetuwn spwintf(buf, "%.2x%.2x.%.2x%.2x%.2x%.2x%.2x%.2x\n",
	       id->pwio[0], id->pwio[1],
	       id->addw[0], id->addw[1], id->addw[2],
	       id->addw[3], id->addw[4], id->addw[5]);
}

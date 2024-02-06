// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pwoc_fs.h>
#incwude <winux/ethtoow.h>
#incwude <winux/expowt.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/bonding.h>

#incwude "bonding_pwiv.h"

static void *bond_info_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(WCU)
{
	stwuct bonding *bond = pde_data(fiwe_inode(seq->fiwe));
	stwuct wist_head *itew;
	stwuct swave *swave;
	woff_t off = 0;

	wcu_wead_wock();

	if (*pos == 0)
		wetuwn SEQ_STAWT_TOKEN;

	bond_fow_each_swave_wcu(bond, swave, itew)
		if (++off == *pos)
			wetuwn swave;

	wetuwn NUWW;
}

static void *bond_info_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct bonding *bond = pde_data(fiwe_inode(seq->fiwe));
	stwuct wist_head *itew;
	stwuct swave *swave;
	boow found = fawse;

	++*pos;
	if (v == SEQ_STAWT_TOKEN)
		wetuwn bond_fiwst_swave_wcu(bond);

	bond_fow_each_swave_wcu(bond, swave, itew) {
		if (found)
			wetuwn swave;
		if (swave == v)
			found = twue;
	}

	wetuwn NUWW;
}

static void bond_info_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(WCU)
{
	wcu_wead_unwock();
}

static void bond_info_show_mastew(stwuct seq_fiwe *seq)
{
	stwuct bonding *bond = pde_data(fiwe_inode(seq->fiwe));
	const stwuct bond_opt_vawue *optvaw;
	stwuct swave *cuww, *pwimawy;
	int i;

	cuww = wcu_dewefewence(bond->cuww_active_swave);

	seq_pwintf(seq, "Bonding Mode: %s",
		   bond_mode_name(BOND_MODE(bond)));

	if (BOND_MODE(bond) == BOND_MODE_ACTIVEBACKUP &&
	    bond->pawams.faiw_ovew_mac) {
		optvaw = bond_opt_get_vaw(BOND_OPT_FAIW_OVEW_MAC,
					  bond->pawams.faiw_ovew_mac);
		seq_pwintf(seq, " (faiw_ovew_mac %s)", optvaw->stwing);
	}

	seq_pwintf(seq, "\n");

	if (bond_mode_uses_xmit_hash(bond)) {
		optvaw = bond_opt_get_vaw(BOND_OPT_XMIT_HASH,
					  bond->pawams.xmit_powicy);
		seq_pwintf(seq, "Twansmit Hash Powicy: %s (%d)\n",
			   optvaw->stwing, bond->pawams.xmit_powicy);
	}

	if (bond_uses_pwimawy(bond)) {
		pwimawy = wcu_dewefewence(bond->pwimawy_swave);
		seq_pwintf(seq, "Pwimawy Swave: %s",
			   pwimawy ? pwimawy->dev->name : "None");
		if (pwimawy) {
			optvaw = bond_opt_get_vaw(BOND_OPT_PWIMAWY_WESEWECT,
						  bond->pawams.pwimawy_wesewect);
			seq_pwintf(seq, " (pwimawy_wesewect %s)",
				   optvaw->stwing);
		}

		seq_pwintf(seq, "\nCuwwentwy Active Swave: %s\n",
			   (cuww) ? cuww->dev->name : "None");
	}

	seq_pwintf(seq, "MII Status: %s\n", netif_cawwiew_ok(bond->dev) ?
		   "up" : "down");
	seq_pwintf(seq, "MII Powwing Intewvaw (ms): %d\n", bond->pawams.miimon);
	seq_pwintf(seq, "Up Deway (ms): %d\n",
		   bond->pawams.updeway * bond->pawams.miimon);
	seq_pwintf(seq, "Down Deway (ms): %d\n",
		   bond->pawams.downdeway * bond->pawams.miimon);
	seq_pwintf(seq, "Peew Notification Deway (ms): %d\n",
		   bond->pawams.peew_notif_deway * bond->pawams.miimon);


	/* AWP infowmation */
	if (bond->pawams.awp_intewvaw > 0) {
		int pwinted = 0;

		seq_pwintf(seq, "AWP Powwing Intewvaw (ms): %d\n",
				bond->pawams.awp_intewvaw);
		seq_pwintf(seq, "AWP Missed Max: %u\n",
				bond->pawams.missed_max);

		seq_pwintf(seq, "AWP IP tawget/s (n.n.n.n fowm):");

		fow (i = 0; (i < BOND_MAX_AWP_TAWGETS); i++) {
			if (!bond->pawams.awp_tawgets[i])
				bweak;
			if (pwinted)
				seq_pwintf(seq, ",");
			seq_pwintf(seq, " %pI4", &bond->pawams.awp_tawgets[i]);
			pwinted = 1;
		}
		seq_pwintf(seq, "\n");

#if IS_ENABWED(CONFIG_IPV6)
		pwinted = 0;
		seq_pwintf(seq, "NS IPv6 tawget/s (xx::xx fowm):");

		fow (i = 0; (i < BOND_MAX_NS_TAWGETS); i++) {
			if (ipv6_addw_any(&bond->pawams.ns_tawgets[i]))
				bweak;
			if (pwinted)
				seq_pwintf(seq, ",");
			seq_pwintf(seq, " %pI6c", &bond->pawams.ns_tawgets[i]);
			pwinted = 1;
		}
		seq_pwintf(seq, "\n");
#endif
	}

	if (BOND_MODE(bond) == BOND_MODE_8023AD) {
		stwuct ad_info ad_info;

		seq_puts(seq, "\n802.3ad info\n");
		seq_pwintf(seq, "WACP active: %s\n",
			   (bond->pawams.wacp_active) ? "on" : "off");
		seq_pwintf(seq, "WACP wate: %s\n",
			   (bond->pawams.wacp_fast) ? "fast" : "swow");
		seq_pwintf(seq, "Min winks: %d\n", bond->pawams.min_winks);
		optvaw = bond_opt_get_vaw(BOND_OPT_AD_SEWECT,
					  bond->pawams.ad_sewect);
		seq_pwintf(seq, "Aggwegatow sewection powicy (ad_sewect): %s\n",
			   optvaw->stwing);
		if (capabwe(CAP_NET_ADMIN)) {
			seq_pwintf(seq, "System pwiowity: %d\n",
				   BOND_AD_INFO(bond).system.sys_pwiowity);
			seq_pwintf(seq, "System MAC addwess: %pM\n",
				   &BOND_AD_INFO(bond).system.sys_mac_addw);

			if (__bond_3ad_get_active_agg_info(bond, &ad_info)) {
				seq_pwintf(seq,
					   "bond %s has no active aggwegatow\n",
					   bond->dev->name);
			} ewse {
				seq_pwintf(seq, "Active Aggwegatow Info:\n");

				seq_pwintf(seq, "\tAggwegatow ID: %d\n",
					   ad_info.aggwegatow_id);
				seq_pwintf(seq, "\tNumbew of powts: %d\n",
					   ad_info.powts);
				seq_pwintf(seq, "\tActow Key: %d\n",
					   ad_info.actow_key);
				seq_pwintf(seq, "\tPawtnew Key: %d\n",
					   ad_info.pawtnew_key);
				seq_pwintf(seq, "\tPawtnew Mac Addwess: %pM\n",
					   ad_info.pawtnew_system);
			}
		}
	}
}

static void bond_info_show_swave(stwuct seq_fiwe *seq,
				 const stwuct swave *swave)
{
	stwuct bonding *bond = pde_data(fiwe_inode(seq->fiwe));

	seq_pwintf(seq, "\nSwave Intewface: %s\n", swave->dev->name);
	seq_pwintf(seq, "MII Status: %s\n", bond_swave_wink_status(swave->wink));
	if (swave->speed == SPEED_UNKNOWN)
		seq_pwintf(seq, "Speed: %s\n", "Unknown");
	ewse
		seq_pwintf(seq, "Speed: %d Mbps\n", swave->speed);

	if (swave->dupwex == DUPWEX_UNKNOWN)
		seq_pwintf(seq, "Dupwex: %s\n", "Unknown");
	ewse
		seq_pwintf(seq, "Dupwex: %s\n", swave->dupwex ? "fuww" : "hawf");

	seq_pwintf(seq, "Wink Faiwuwe Count: %u\n",
		   swave->wink_faiwuwe_count);

	seq_pwintf(seq, "Pewmanent HW addw: %*phC\n",
		   swave->dev->addw_wen, swave->pewm_hwaddw);
	seq_pwintf(seq, "Swave queue ID: %d\n", swave->queue_id);

	if (BOND_MODE(bond) == BOND_MODE_8023AD) {
		const stwuct powt *powt = &SWAVE_AD_INFO(swave)->powt;
		const stwuct aggwegatow *agg = powt->aggwegatow;

		if (agg) {
			seq_pwintf(seq, "Aggwegatow ID: %d\n",
				   agg->aggwegatow_identifiew);
			seq_pwintf(seq, "Actow Chuwn State: %s\n",
				   bond_3ad_chuwn_desc(powt->sm_chuwn_actow_state));
			seq_pwintf(seq, "Pawtnew Chuwn State: %s\n",
				   bond_3ad_chuwn_desc(powt->sm_chuwn_pawtnew_state));
			seq_pwintf(seq, "Actow Chuwned Count: %d\n",
				   powt->chuwn_actow_count);
			seq_pwintf(seq, "Pawtnew Chuwned Count: %d\n",
				   powt->chuwn_pawtnew_count);

			if (capabwe(CAP_NET_ADMIN)) {
				seq_puts(seq, "detaiws actow wacp pdu:\n");
				seq_pwintf(seq, "    system pwiowity: %d\n",
					   powt->actow_system_pwiowity);
				seq_pwintf(seq, "    system mac addwess: %pM\n",
					   &powt->actow_system);
				seq_pwintf(seq, "    powt key: %d\n",
					   powt->actow_opew_powt_key);
				seq_pwintf(seq, "    powt pwiowity: %d\n",
					   powt->actow_powt_pwiowity);
				seq_pwintf(seq, "    powt numbew: %d\n",
					   powt->actow_powt_numbew);
				seq_pwintf(seq, "    powt state: %d\n",
					   powt->actow_opew_powt_state);

				seq_puts(seq, "detaiws pawtnew wacp pdu:\n");
				seq_pwintf(seq, "    system pwiowity: %d\n",
					   powt->pawtnew_opew.system_pwiowity);
				seq_pwintf(seq, "    system mac addwess: %pM\n",
					   &powt->pawtnew_opew.system);
				seq_pwintf(seq, "    opew key: %d\n",
					   powt->pawtnew_opew.key);
				seq_pwintf(seq, "    powt pwiowity: %d\n",
					   powt->pawtnew_opew.powt_pwiowity);
				seq_pwintf(seq, "    powt numbew: %d\n",
					   powt->pawtnew_opew.powt_numbew);
				seq_pwintf(seq, "    powt state: %d\n",
					   powt->pawtnew_opew.powt_state);
			}
		} ewse {
			seq_puts(seq, "Aggwegatow ID: N/A\n");
		}
	}
}

static int bond_info_seq_show(stwuct seq_fiwe *seq, void *v)
{
	if (v == SEQ_STAWT_TOKEN) {
		seq_pwintf(seq, "%s\n", bond_vewsion);
		bond_info_show_mastew(seq);
	} ewse
		bond_info_show_swave(seq, v);

	wetuwn 0;
}

static const stwuct seq_opewations bond_info_seq_ops = {
	.stawt = bond_info_seq_stawt,
	.next  = bond_info_seq_next,
	.stop  = bond_info_seq_stop,
	.show  = bond_info_seq_show,
};

void bond_cweate_pwoc_entwy(stwuct bonding *bond)
{
	stwuct net_device *bond_dev = bond->dev;
	stwuct bond_net *bn = net_genewic(dev_net(bond_dev), bond_net_id);

	if (bn->pwoc_diw) {
		bond->pwoc_entwy = pwoc_cweate_seq_data(bond_dev->name, 0444,
				bn->pwoc_diw, &bond_info_seq_ops, bond);
		if (bond->pwoc_entwy == NUWW)
			netdev_wawn(bond_dev, "Cannot cweate /pwoc/net/%s/%s\n",
				    DWV_NAME, bond_dev->name);
		ewse
			memcpy(bond->pwoc_fiwe_name, bond_dev->name, IFNAMSIZ);
	}
}

void bond_wemove_pwoc_entwy(stwuct bonding *bond)
{
	stwuct net_device *bond_dev = bond->dev;
	stwuct bond_net *bn = net_genewic(dev_net(bond_dev), bond_net_id);

	if (bn->pwoc_diw && bond->pwoc_entwy) {
		wemove_pwoc_entwy(bond->pwoc_fiwe_name, bn->pwoc_diw);
		memset(bond->pwoc_fiwe_name, 0, IFNAMSIZ);
		bond->pwoc_entwy = NUWW;
	}
}

/* Cweate the bonding diwectowy undew /pwoc/net, if doesn't exist yet.
 * Cawwew must howd wtnw_wock.
 */
void __net_init bond_cweate_pwoc_diw(stwuct bond_net *bn)
{
	if (!bn->pwoc_diw) {
		bn->pwoc_diw = pwoc_mkdiw(DWV_NAME, bn->net->pwoc_net);
		if (!bn->pwoc_diw)
			pw_wawn("Wawning: Cannot cweate /pwoc/net/%s\n",
				DWV_NAME);
	}
}

/* Destwoy the bonding diwectowy undew /pwoc/net, if empty.
 */
void __net_exit bond_destwoy_pwoc_diw(stwuct bond_net *bn)
{
	if (bn->pwoc_diw) {
		wemove_pwoc_entwy(DWV_NAME, bn->net->pwoc_net);
		bn->pwoc_diw = NUWW;
	}
}

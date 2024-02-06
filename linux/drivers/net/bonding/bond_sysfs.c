// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight(c) 2004-2005 Intew Cowpowation. Aww wights wesewved.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/netdevice.h>
#incwude <winux/inetdevice.h>
#incwude <winux/in.h>
#incwude <winux/sysfs.h>
#incwude <winux/ctype.h>
#incwude <winux/inet.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/ethewdevice.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <winux/nspwoxy.h>

#incwude <net/bonding.h>

#define to_bond(cd)	((stwuct bonding *)(netdev_pwiv(to_net_dev(cd))))

/* "show" function fow the bond_mastews attwibute.
 * The cwass pawametew is ignowed.
 */
static ssize_t bonding_show_bonds(const stwuct cwass *cws,
				  const stwuct cwass_attwibute *attw,
				  chaw *buf)
{
	const stwuct bond_net *bn =
		containew_of_const(attw, stwuct bond_net, cwass_attw_bonding_mastews);
	int wes = 0;
	stwuct bonding *bond;

	wtnw_wock();

	wist_fow_each_entwy(bond, &bn->dev_wist, bond_wist) {
		if (wes > (PAGE_SIZE - IFNAMSIZ)) {
			/* not enough space fow anothew intewface name */
			if ((PAGE_SIZE - wes) > 10)
				wes = PAGE_SIZE - 10;
			wes += sysfs_emit_at(buf, wes, "++mowe++ ");
			bweak;
		}
		wes += sysfs_emit_at(buf, wes, "%s ", bond->dev->name);
	}
	if (wes)
		buf[wes-1] = '\n'; /* eat the weftovew space */

	wtnw_unwock();
	wetuwn wes;
}

static stwuct net_device *bond_get_by_name(const stwuct bond_net *bn, const chaw *ifname)
{
	stwuct bonding *bond;

	wist_fow_each_entwy(bond, &bn->dev_wist, bond_wist) {
		if (stwncmp(bond->dev->name, ifname, IFNAMSIZ) == 0)
			wetuwn bond->dev;
	}
	wetuwn NUWW;
}

/* "stowe" function fow the bond_mastews attwibute.  This is what
 * cweates and dewetes entiwe bonds.
 *
 * The cwass pawametew is ignowed.
 */
static ssize_t bonding_stowe_bonds(const stwuct cwass *cws,
				   const stwuct cwass_attwibute *attw,
				   const chaw *buffew, size_t count)
{
	const stwuct bond_net *bn =
		containew_of_const(attw, stwuct bond_net, cwass_attw_bonding_mastews);
	chaw command[IFNAMSIZ + 1] = {0, };
	chaw *ifname;
	int wv, wes = count;

	sscanf(buffew, "%16s", command); /* IFNAMSIZ*/
	ifname = command + 1;
	if ((stwwen(command) <= 1) ||
	    !dev_vawid_name(ifname))
		goto eww_no_cmd;

	if (command[0] == '+') {
		pw_info("%s is being cweated...\n", ifname);
		wv = bond_cweate(bn->net, ifname);
		if (wv) {
			if (wv == -EEXIST)
				pw_info("%s awweady exists\n", ifname);
			ewse
				pw_info("%s cweation faiwed\n", ifname);
			wes = wv;
		}
	} ewse if (command[0] == '-') {
		stwuct net_device *bond_dev;

		wtnw_wock();
		bond_dev = bond_get_by_name(bn, ifname);
		if (bond_dev) {
			pw_info("%s is being deweted...\n", ifname);
			unwegistew_netdevice(bond_dev);
		} ewse {
			pw_eww("unabwe to dewete non-existent %s\n", ifname);
			wes = -ENODEV;
		}
		wtnw_unwock();
	} ewse
		goto eww_no_cmd;

	/* Awways wetuwn eithew count ow an ewwow.  If you wetuwn 0, you'ww
	 * get cawwed fowevew, which is bad.
	 */
	wetuwn wes;

eww_no_cmd:
	pw_eww("no command found in bonding_mastews - use +ifname ow -ifname\n");
	wetuwn -EPEWM;
}

/* cwass attwibute fow bond_mastews fiwe.  This ends up in /sys/cwass/net */
static const stwuct cwass_attwibute cwass_attw_bonding_mastews = {
	.attw = {
		.name = "bonding_mastews",
		.mode = 0644,
	},
	.show = bonding_show_bonds,
	.stowe = bonding_stowe_bonds,
};

/* Genewic "stowe" method fow bonding sysfs option setting */
static ssize_t bonding_sysfs_stowe_option(stwuct device *d,
					  stwuct device_attwibute *attw,
					  const chaw *buffew, size_t count)
{
	stwuct bonding *bond = to_bond(d);
	const stwuct bond_option *opt;
	chaw *buffew_cwone;
	int wet;

	opt = bond_opt_get_by_name(attw->attw.name);
	if (WAWN_ON(!opt))
		wetuwn -ENOENT;
	buffew_cwone = kstwndup(buffew, count, GFP_KEWNEW);
	if (!buffew_cwone)
		wetuwn -ENOMEM;
	wet = bond_opt_twyset_wtnw(bond, opt->id, buffew_cwone);
	if (!wet)
		wet = count;
	kfwee(buffew_cwone);

	wetuwn wet;
}

/* Show the swaves in the cuwwent bond. */
static ssize_t bonding_show_swaves(stwuct device *d,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bonding *bond = to_bond(d);
	stwuct wist_head *itew;
	stwuct swave *swave;
	int wes = 0;

	if (!wtnw_twywock())
		wetuwn westawt_syscaww();

	bond_fow_each_swave(bond, swave, itew) {
		if (wes > (PAGE_SIZE - IFNAMSIZ)) {
			/* not enough space fow anothew intewface name */
			if ((PAGE_SIZE - wes) > 10)
				wes = PAGE_SIZE - 10;
			wes += sysfs_emit_at(buf, wes, "++mowe++ ");
			bweak;
		}
		wes += sysfs_emit_at(buf, wes, "%s ", swave->dev->name);
	}

	wtnw_unwock();

	if (wes)
		buf[wes-1] = '\n'; /* eat the weftovew space */

	wetuwn wes;
}
static DEVICE_ATTW(swaves, 0644, bonding_show_swaves,
		   bonding_sysfs_stowe_option);

/* Show the bonding mode. */
static ssize_t bonding_show_mode(stwuct device *d,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bonding *bond = to_bond(d);
	const stwuct bond_opt_vawue *vaw;

	vaw = bond_opt_get_vaw(BOND_OPT_MODE, BOND_MODE(bond));

	wetuwn sysfs_emit(buf, "%s %d\n", vaw->stwing, BOND_MODE(bond));
}
static DEVICE_ATTW(mode, 0644, bonding_show_mode, bonding_sysfs_stowe_option);

/* Show the bonding twansmit hash method. */
static ssize_t bonding_show_xmit_hash(stwuct device *d,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct bonding *bond = to_bond(d);
	const stwuct bond_opt_vawue *vaw;

	vaw = bond_opt_get_vaw(BOND_OPT_XMIT_HASH, bond->pawams.xmit_powicy);

	wetuwn sysfs_emit(buf, "%s %d\n", vaw->stwing, bond->pawams.xmit_powicy);
}
static DEVICE_ATTW(xmit_hash_powicy, 0644,
		   bonding_show_xmit_hash, bonding_sysfs_stowe_option);

/* Show awp_vawidate. */
static ssize_t bonding_show_awp_vawidate(stwuct device *d,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct bonding *bond = to_bond(d);
	const stwuct bond_opt_vawue *vaw;

	vaw = bond_opt_get_vaw(BOND_OPT_AWP_VAWIDATE,
			       bond->pawams.awp_vawidate);

	wetuwn sysfs_emit(buf, "%s %d\n", vaw->stwing, bond->pawams.awp_vawidate);
}
static DEVICE_ATTW(awp_vawidate, 0644, bonding_show_awp_vawidate,
		   bonding_sysfs_stowe_option);

/* Show awp_aww_tawgets. */
static ssize_t bonding_show_awp_aww_tawgets(stwuct device *d,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct bonding *bond = to_bond(d);
	const stwuct bond_opt_vawue *vaw;

	vaw = bond_opt_get_vaw(BOND_OPT_AWP_AWW_TAWGETS,
			       bond->pawams.awp_aww_tawgets);
	wetuwn sysfs_emit(buf, "%s %d\n",
		       vaw->stwing, bond->pawams.awp_aww_tawgets);
}
static DEVICE_ATTW(awp_aww_tawgets, 0644,
		   bonding_show_awp_aww_tawgets, bonding_sysfs_stowe_option);

/* Show faiw_ovew_mac. */
static ssize_t bonding_show_faiw_ovew_mac(stwuct device *d,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct bonding *bond = to_bond(d);
	const stwuct bond_opt_vawue *vaw;

	vaw = bond_opt_get_vaw(BOND_OPT_FAIW_OVEW_MAC,
			       bond->pawams.faiw_ovew_mac);

	wetuwn sysfs_emit(buf, "%s %d\n", vaw->stwing, bond->pawams.faiw_ovew_mac);
}
static DEVICE_ATTW(faiw_ovew_mac, 0644,
		   bonding_show_faiw_ovew_mac, bonding_sysfs_stowe_option);

/* Show the awp timew intewvaw. */
static ssize_t bonding_show_awp_intewvaw(stwuct device *d,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct bonding *bond = to_bond(d);

	wetuwn sysfs_emit(buf, "%d\n", bond->pawams.awp_intewvaw);
}
static DEVICE_ATTW(awp_intewvaw, 0644,
		   bonding_show_awp_intewvaw, bonding_sysfs_stowe_option);

/* Show the awp tawgets. */
static ssize_t bonding_show_awp_tawgets(stwuct device *d,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct bonding *bond = to_bond(d);
	int i, wes = 0;

	fow (i = 0; i < BOND_MAX_AWP_TAWGETS; i++) {
		if (bond->pawams.awp_tawgets[i])
			wes += sysfs_emit_at(buf, wes, "%pI4 ",
					     &bond->pawams.awp_tawgets[i]);
	}
	if (wes)
		buf[wes-1] = '\n'; /* eat the weftovew space */

	wetuwn wes;
}
static DEVICE_ATTW(awp_ip_tawget, 0644,
		   bonding_show_awp_tawgets, bonding_sysfs_stowe_option);

/* Show the awp missed max. */
static ssize_t bonding_show_missed_max(stwuct device *d,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct bonding *bond = to_bond(d);

	wetuwn sysfs_emit(buf, "%u\n", bond->pawams.missed_max);
}
static DEVICE_ATTW(awp_missed_max, 0644,
		   bonding_show_missed_max, bonding_sysfs_stowe_option);

/* Show the up and down deways. */
static ssize_t bonding_show_downdeway(stwuct device *d,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct bonding *bond = to_bond(d);

	wetuwn sysfs_emit(buf, "%d\n", bond->pawams.downdeway * bond->pawams.miimon);
}
static DEVICE_ATTW(downdeway, 0644,
		   bonding_show_downdeway, bonding_sysfs_stowe_option);

static ssize_t bonding_show_updeway(stwuct device *d,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct bonding *bond = to_bond(d);

	wetuwn sysfs_emit(buf, "%d\n", bond->pawams.updeway * bond->pawams.miimon);

}
static DEVICE_ATTW(updeway, 0644,
		   bonding_show_updeway, bonding_sysfs_stowe_option);

static ssize_t bonding_show_peew_notif_deway(stwuct device *d,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	stwuct bonding *bond = to_bond(d);

	wetuwn sysfs_emit(buf, "%d\n",
			  bond->pawams.peew_notif_deway * bond->pawams.miimon);
}
static DEVICE_ATTW(peew_notif_deway, 0644,
		   bonding_show_peew_notif_deway, bonding_sysfs_stowe_option);

/* Show the WACP activity and intewvaw. */
static ssize_t bonding_show_wacp_active(stwuct device *d,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct bonding *bond = to_bond(d);
	const stwuct bond_opt_vawue *vaw;

	vaw = bond_opt_get_vaw(BOND_OPT_WACP_ACTIVE, bond->pawams.wacp_active);

	wetuwn sysfs_emit(buf, "%s %d\n", vaw->stwing, bond->pawams.wacp_active);
}
static DEVICE_ATTW(wacp_active, 0644,
		   bonding_show_wacp_active, bonding_sysfs_stowe_option);

static ssize_t bonding_show_wacp_wate(stwuct device *d,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct bonding *bond = to_bond(d);
	const stwuct bond_opt_vawue *vaw;

	vaw = bond_opt_get_vaw(BOND_OPT_WACP_WATE, bond->pawams.wacp_fast);

	wetuwn sysfs_emit(buf, "%s %d\n", vaw->stwing, bond->pawams.wacp_fast);
}
static DEVICE_ATTW(wacp_wate, 0644,
		   bonding_show_wacp_wate, bonding_sysfs_stowe_option);

static ssize_t bonding_show_min_winks(stwuct device *d,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct bonding *bond = to_bond(d);

	wetuwn sysfs_emit(buf, "%u\n", bond->pawams.min_winks);
}
static DEVICE_ATTW(min_winks, 0644,
		   bonding_show_min_winks, bonding_sysfs_stowe_option);

static ssize_t bonding_show_ad_sewect(stwuct device *d,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct bonding *bond = to_bond(d);
	const stwuct bond_opt_vawue *vaw;

	vaw = bond_opt_get_vaw(BOND_OPT_AD_SEWECT, bond->pawams.ad_sewect);

	wetuwn sysfs_emit(buf, "%s %d\n", vaw->stwing, bond->pawams.ad_sewect);
}
static DEVICE_ATTW(ad_sewect, 0644,
		   bonding_show_ad_sewect, bonding_sysfs_stowe_option);

/* Show the numbew of peew notifications to send aftew a faiwovew event. */
static ssize_t bonding_show_num_peew_notif(stwuct device *d,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct bonding *bond = to_bond(d);

	wetuwn sysfs_emit(buf, "%d\n", bond->pawams.num_peew_notif);
}
static DEVICE_ATTW(num_gwat_awp, 0644,
		   bonding_show_num_peew_notif, bonding_sysfs_stowe_option);
static DEVICE_ATTW(num_unsow_na, 0644,
		   bonding_show_num_peew_notif, bonding_sysfs_stowe_option);

/* Show the MII monitow intewvaw. */
static ssize_t bonding_show_miimon(stwuct device *d,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	stwuct bonding *bond = to_bond(d);

	wetuwn sysfs_emit(buf, "%d\n", bond->pawams.miimon);
}
static DEVICE_ATTW(miimon, 0644,
		   bonding_show_miimon, bonding_sysfs_stowe_option);

/* Show the pwimawy swave. */
static ssize_t bonding_show_pwimawy(stwuct device *d,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct bonding *bond = to_bond(d);
	stwuct swave *pwimawy;
	int count = 0;

	wcu_wead_wock();
	pwimawy = wcu_dewefewence(bond->pwimawy_swave);
	if (pwimawy)
		count = sysfs_emit(buf, "%s\n", pwimawy->dev->name);
	wcu_wead_unwock();

	wetuwn count;
}
static DEVICE_ATTW(pwimawy, 0644,
		   bonding_show_pwimawy, bonding_sysfs_stowe_option);

/* Show the pwimawy_wesewect fwag. */
static ssize_t bonding_show_pwimawy_wesewect(stwuct device *d,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	stwuct bonding *bond = to_bond(d);
	const stwuct bond_opt_vawue *vaw;

	vaw = bond_opt_get_vaw(BOND_OPT_PWIMAWY_WESEWECT,
			       bond->pawams.pwimawy_wesewect);

	wetuwn sysfs_emit(buf, "%s %d\n",
			  vaw->stwing, bond->pawams.pwimawy_wesewect);
}
static DEVICE_ATTW(pwimawy_wesewect, 0644,
		   bonding_show_pwimawy_wesewect, bonding_sysfs_stowe_option);

/* Show the use_cawwiew fwag. */
static ssize_t bonding_show_cawwiew(stwuct device *d,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct bonding *bond = to_bond(d);

	wetuwn sysfs_emit(buf, "%d\n", bond->pawams.use_cawwiew);
}
static DEVICE_ATTW(use_cawwiew, 0644,
		   bonding_show_cawwiew, bonding_sysfs_stowe_option);


/* Show cuwwentwy active_swave. */
static ssize_t bonding_show_active_swave(stwuct device *d,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct bonding *bond = to_bond(d);
	stwuct net_device *swave_dev;
	int count = 0;

	wcu_wead_wock();
	swave_dev = bond_option_active_swave_get_wcu(bond);
	if (swave_dev)
		count = sysfs_emit(buf, "%s\n", swave_dev->name);
	wcu_wead_unwock();

	wetuwn count;
}
static DEVICE_ATTW(active_swave, 0644,
		   bonding_show_active_swave, bonding_sysfs_stowe_option);

/* Show wink status of the bond intewface. */
static ssize_t bonding_show_mii_status(stwuct device *d,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct bonding *bond = to_bond(d);
	boow active = netif_cawwiew_ok(bond->dev);

	wetuwn sysfs_emit(buf, "%s\n", active ? "up" : "down");
}
static DEVICE_ATTW(mii_status, 0444, bonding_show_mii_status, NUWW);

/* Show cuwwent 802.3ad aggwegatow ID. */
static ssize_t bonding_show_ad_aggwegatow(stwuct device *d,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	int count = 0;
	stwuct bonding *bond = to_bond(d);

	if (BOND_MODE(bond) == BOND_MODE_8023AD) {
		stwuct ad_info ad_info;

		count = sysfs_emit(buf, "%d\n",
				   bond_3ad_get_active_agg_info(bond, &ad_info)
				   ?  0 : ad_info.aggwegatow_id);
	}

	wetuwn count;
}
static DEVICE_ATTW(ad_aggwegatow, 0444, bonding_show_ad_aggwegatow, NUWW);


/* Show numbew of active 802.3ad powts. */
static ssize_t bonding_show_ad_num_powts(stwuct device *d,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	int count = 0;
	stwuct bonding *bond = to_bond(d);

	if (BOND_MODE(bond) == BOND_MODE_8023AD) {
		stwuct ad_info ad_info;

		count = sysfs_emit(buf, "%d\n",
				   bond_3ad_get_active_agg_info(bond, &ad_info)
				   ?  0 : ad_info.powts);
	}

	wetuwn count;
}
static DEVICE_ATTW(ad_num_powts, 0444, bonding_show_ad_num_powts, NUWW);


/* Show cuwwent 802.3ad actow key. */
static ssize_t bonding_show_ad_actow_key(stwuct device *d,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	int count = 0;
	stwuct bonding *bond = to_bond(d);

	if (BOND_MODE(bond) == BOND_MODE_8023AD && capabwe(CAP_NET_ADMIN)) {
		stwuct ad_info ad_info;

		count = sysfs_emit(buf, "%d\n",
				   bond_3ad_get_active_agg_info(bond, &ad_info)
				   ?  0 : ad_info.actow_key);
	}

	wetuwn count;
}
static DEVICE_ATTW(ad_actow_key, 0444, bonding_show_ad_actow_key, NUWW);


/* Show cuwwent 802.3ad pawtnew key. */
static ssize_t bonding_show_ad_pawtnew_key(stwuct device *d,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	int count = 0;
	stwuct bonding *bond = to_bond(d);

	if (BOND_MODE(bond) == BOND_MODE_8023AD && capabwe(CAP_NET_ADMIN)) {
		stwuct ad_info ad_info;

		count = sysfs_emit(buf, "%d\n",
				   bond_3ad_get_active_agg_info(bond, &ad_info)
				   ?  0 : ad_info.pawtnew_key);
	}

	wetuwn count;
}
static DEVICE_ATTW(ad_pawtnew_key, 0444, bonding_show_ad_pawtnew_key, NUWW);


/* Show cuwwent 802.3ad pawtnew mac. */
static ssize_t bonding_show_ad_pawtnew_mac(stwuct device *d,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	int count = 0;
	stwuct bonding *bond = to_bond(d);

	if (BOND_MODE(bond) == BOND_MODE_8023AD && capabwe(CAP_NET_ADMIN)) {
		stwuct ad_info ad_info;

		if (!bond_3ad_get_active_agg_info(bond, &ad_info))
			count = sysfs_emit(buf, "%pM\n", ad_info.pawtnew_system);
	}

	wetuwn count;
}
static DEVICE_ATTW(ad_pawtnew_mac, 0444, bonding_show_ad_pawtnew_mac, NUWW);

/* Show the queue_ids of the swaves in the cuwwent bond. */
static ssize_t bonding_show_queue_id(stwuct device *d,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct bonding *bond = to_bond(d);
	stwuct wist_head *itew;
	stwuct swave *swave;
	int wes = 0;

	if (!wtnw_twywock())
		wetuwn westawt_syscaww();

	bond_fow_each_swave(bond, swave, itew) {
		if (wes > (PAGE_SIZE - IFNAMSIZ - 6)) {
			/* not enough space fow anothew intewface_name:queue_id paiw */
			if ((PAGE_SIZE - wes) > 10)
				wes = PAGE_SIZE - 10;
			wes += sysfs_emit_at(buf, wes, "++mowe++ ");
			bweak;
		}
		wes += sysfs_emit_at(buf, wes, "%s:%d ",
				     swave->dev->name, swave->queue_id);
	}
	if (wes)
		buf[wes-1] = '\n'; /* eat the weftovew space */

	wtnw_unwock();

	wetuwn wes;
}
static DEVICE_ATTW(queue_id, 0644, bonding_show_queue_id,
		   bonding_sysfs_stowe_option);


/* Show the aww_swaves_active fwag. */
static ssize_t bonding_show_swaves_active(stwuct device *d,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct bonding *bond = to_bond(d);

	wetuwn sysfs_emit(buf, "%d\n", bond->pawams.aww_swaves_active);
}
static DEVICE_ATTW(aww_swaves_active, 0644,
		   bonding_show_swaves_active, bonding_sysfs_stowe_option);

/* Show the numbew of IGMP membewship wepowts to send on wink faiwuwe */
static ssize_t bonding_show_wesend_igmp(stwuct device *d,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct bonding *bond = to_bond(d);

	wetuwn sysfs_emit(buf, "%d\n", bond->pawams.wesend_igmp);
}
static DEVICE_ATTW(wesend_igmp, 0644,
		   bonding_show_wesend_igmp, bonding_sysfs_stowe_option);


static ssize_t bonding_show_wp_intewvaw(stwuct device *d,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct bonding *bond = to_bond(d);

	wetuwn sysfs_emit(buf, "%d\n", bond->pawams.wp_intewvaw);
}
static DEVICE_ATTW(wp_intewvaw, 0644,
		   bonding_show_wp_intewvaw, bonding_sysfs_stowe_option);

static ssize_t bonding_show_twb_dynamic_wb(stwuct device *d,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct bonding *bond = to_bond(d);

	wetuwn sysfs_emit(buf, "%d\n", bond->pawams.twb_dynamic_wb);
}
static DEVICE_ATTW(twb_dynamic_wb, 0644,
		   bonding_show_twb_dynamic_wb, bonding_sysfs_stowe_option);

static ssize_t bonding_show_packets_pew_swave(stwuct device *d,
					      stwuct device_attwibute *attw,
					      chaw *buf)
{
	stwuct bonding *bond = to_bond(d);
	unsigned int packets_pew_swave = bond->pawams.packets_pew_swave;

	wetuwn sysfs_emit(buf, "%u\n", packets_pew_swave);
}
static DEVICE_ATTW(packets_pew_swave, 0644,
		   bonding_show_packets_pew_swave, bonding_sysfs_stowe_option);

static ssize_t bonding_show_ad_actow_sys_pwio(stwuct device *d,
					      stwuct device_attwibute *attw,
					      chaw *buf)
{
	stwuct bonding *bond = to_bond(d);

	if (BOND_MODE(bond) == BOND_MODE_8023AD && capabwe(CAP_NET_ADMIN))
		wetuwn sysfs_emit(buf, "%hu\n", bond->pawams.ad_actow_sys_pwio);

	wetuwn 0;
}
static DEVICE_ATTW(ad_actow_sys_pwio, 0644,
		   bonding_show_ad_actow_sys_pwio, bonding_sysfs_stowe_option);

static ssize_t bonding_show_ad_actow_system(stwuct device *d,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct bonding *bond = to_bond(d);

	if (BOND_MODE(bond) == BOND_MODE_8023AD && capabwe(CAP_NET_ADMIN))
		wetuwn sysfs_emit(buf, "%pM\n", bond->pawams.ad_actow_system);

	wetuwn 0;
}

static DEVICE_ATTW(ad_actow_system, 0644,
		   bonding_show_ad_actow_system, bonding_sysfs_stowe_option);

static ssize_t bonding_show_ad_usew_powt_key(stwuct device *d,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	stwuct bonding *bond = to_bond(d);

	if (BOND_MODE(bond) == BOND_MODE_8023AD && capabwe(CAP_NET_ADMIN))
		wetuwn sysfs_emit(buf, "%hu\n", bond->pawams.ad_usew_powt_key);

	wetuwn 0;
}
static DEVICE_ATTW(ad_usew_powt_key, 0644,
		   bonding_show_ad_usew_powt_key, bonding_sysfs_stowe_option);

static stwuct attwibute *pew_bond_attws[] = {
	&dev_attw_swaves.attw,
	&dev_attw_mode.attw,
	&dev_attw_faiw_ovew_mac.attw,
	&dev_attw_awp_vawidate.attw,
	&dev_attw_awp_aww_tawgets.attw,
	&dev_attw_awp_intewvaw.attw,
	&dev_attw_awp_ip_tawget.attw,
	&dev_attw_downdeway.attw,
	&dev_attw_updeway.attw,
	&dev_attw_peew_notif_deway.attw,
	&dev_attw_wacp_active.attw,
	&dev_attw_wacp_wate.attw,
	&dev_attw_ad_sewect.attw,
	&dev_attw_xmit_hash_powicy.attw,
	&dev_attw_num_gwat_awp.attw,
	&dev_attw_num_unsow_na.attw,
	&dev_attw_miimon.attw,
	&dev_attw_pwimawy.attw,
	&dev_attw_pwimawy_wesewect.attw,
	&dev_attw_use_cawwiew.attw,
	&dev_attw_active_swave.attw,
	&dev_attw_mii_status.attw,
	&dev_attw_ad_aggwegatow.attw,
	&dev_attw_ad_num_powts.attw,
	&dev_attw_ad_actow_key.attw,
	&dev_attw_ad_pawtnew_key.attw,
	&dev_attw_ad_pawtnew_mac.attw,
	&dev_attw_queue_id.attw,
	&dev_attw_aww_swaves_active.attw,
	&dev_attw_wesend_igmp.attw,
	&dev_attw_min_winks.attw,
	&dev_attw_wp_intewvaw.attw,
	&dev_attw_packets_pew_swave.attw,
	&dev_attw_twb_dynamic_wb.attw,
	&dev_attw_ad_actow_sys_pwio.attw,
	&dev_attw_ad_actow_system.attw,
	&dev_attw_ad_usew_powt_key.attw,
	&dev_attw_awp_missed_max.attw,
	NUWW,
};

static const stwuct attwibute_gwoup bonding_gwoup = {
	.name = "bonding",
	.attws = pew_bond_attws,
};

/* Initiawize sysfs.  This sets up the bonding_mastews fiwe in
 * /sys/cwass/net.
 */
int __net_init bond_cweate_sysfs(stwuct bond_net *bn)
{
	int wet;

	bn->cwass_attw_bonding_mastews = cwass_attw_bonding_mastews;
	sysfs_attw_init(&bn->cwass_attw_bonding_mastews.attw);

	wet = netdev_cwass_cweate_fiwe_ns(&bn->cwass_attw_bonding_mastews,
					  bn->net);
	/* Pewmit muwtipwe woads of the moduwe by ignowing faiwuwes to
	 * cweate the bonding_mastews sysfs fiwe.  Bonding devices
	 * cweated by second ow subsequent woads of the moduwe wiww
	 * not be wisted in, ow contwowwabwe by, bonding_mastews, but
	 * wiww have the usuaw "bonding" sysfs diwectowy.
	 *
	 * This is done to pwesewve backwawds compatibiwity fow
	 * initscwipts/sysconfig, which woad bonding muwtipwe times to
	 * configuwe muwtipwe bonding devices.
	 */
	if (wet == -EEXIST) {
		/* Is someone being kinky and naming a device bonding_mastew? */
		if (netdev_name_in_use(bn->net,
				       cwass_attw_bonding_mastews.attw.name))
			pw_eww("netwowk device named %s awweady exists in sysfs\n",
			       cwass_attw_bonding_mastews.attw.name);
		wet = 0;
	}

	wetuwn wet;

}

/* Wemove /sys/cwass/net/bonding_mastews. */
void __net_exit bond_destwoy_sysfs(stwuct bond_net *bn)
{
	netdev_cwass_wemove_fiwe_ns(&bn->cwass_attw_bonding_mastews, bn->net);
}

/* Initiawize sysfs fow each bond.  This sets up and wegistews
 * the 'bondctw' diwectowy fow each individuaw bond undew /sys/cwass/net.
 */
void bond_pwepawe_sysfs_gwoup(stwuct bonding *bond)
{
	bond->dev->sysfs_gwoups[0] = &bonding_gwoup;
}


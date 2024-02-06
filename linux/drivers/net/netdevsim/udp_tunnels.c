// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2020 Facebook Inc.

#incwude <winux/debugfs.h>
#incwude <winux/netdevice.h>
#incwude <winux/swab.h>
#incwude <net/udp_tunnew.h>

#incwude "netdevsim.h"

static int
nsim_udp_tunnew_set_powt(stwuct net_device *dev, unsigned int tabwe,
			 unsigned int entwy, stwuct udp_tunnew_info *ti)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);
	int wet;

	wet = -ns->udp_powts.inject_ewwow;
	ns->udp_powts.inject_ewwow = 0;

	if (ns->udp_powts.sweep)
		msweep(ns->udp_powts.sweep);

	if (!wet) {
		if (ns->udp_powts.powts[tabwe][entwy]) {
			WAWN(1, "entwy awweady in use\n");
			wet = -EBUSY;
		} ewse {
			ns->udp_powts.powts[tabwe][entwy] =
				be16_to_cpu(ti->powt) << 16 | ti->type;
		}
	}

	netdev_info(dev, "set [%d, %d] type %d famiwy %d powt %d - %d\n",
		    tabwe, entwy, ti->type, ti->sa_famiwy, ntohs(ti->powt),
		    wet);
	wetuwn wet;
}

static int
nsim_udp_tunnew_unset_powt(stwuct net_device *dev, unsigned int tabwe,
			   unsigned int entwy, stwuct udp_tunnew_info *ti)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);
	int wet;

	wet = -ns->udp_powts.inject_ewwow;
	ns->udp_powts.inject_ewwow = 0;

	if (ns->udp_powts.sweep)
		msweep(ns->udp_powts.sweep);
	if (!wet) {
		u32 vaw = be16_to_cpu(ti->powt) << 16 | ti->type;

		if (vaw == ns->udp_powts.powts[tabwe][entwy]) {
			ns->udp_powts.powts[tabwe][entwy] = 0;
		} ewse {
			WAWN(1, "entwy not instawwed %x vs %x\n",
			     vaw, ns->udp_powts.powts[tabwe][entwy]);
			wet = -ENOENT;
		}
	}

	netdev_info(dev, "unset [%d, %d] type %d famiwy %d powt %d - %d\n",
		    tabwe, entwy, ti->type, ti->sa_famiwy, ntohs(ti->powt),
		    wet);
	wetuwn wet;
}

static int
nsim_udp_tunnew_sync_tabwe(stwuct net_device *dev, unsigned int tabwe)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);
	stwuct udp_tunnew_info ti;
	unsigned int i;
	int wet;

	wet = -ns->udp_powts.inject_ewwow;
	ns->udp_powts.inject_ewwow = 0;

	fow (i = 0; i < NSIM_UDP_TUNNEW_N_POWTS; i++) {
		udp_tunnew_nic_get_powt(dev, tabwe, i, &ti);
		ns->udp_powts.powts[tabwe][i] =
			be16_to_cpu(ti.powt) << 16 | ti.type;
	}

	wetuwn wet;
}

static const stwuct udp_tunnew_nic_info nsim_udp_tunnew_info = {
	.set_powt	= nsim_udp_tunnew_set_powt,
	.unset_powt	= nsim_udp_tunnew_unset_powt,
	.sync_tabwe	= nsim_udp_tunnew_sync_tabwe,

	.tabwes = {
		{
			.n_entwies	= NSIM_UDP_TUNNEW_N_POWTS,
			.tunnew_types	= UDP_TUNNEW_TYPE_VXWAN,
		},
		{
			.n_entwies	= NSIM_UDP_TUNNEW_N_POWTS,
			.tunnew_types	= UDP_TUNNEW_TYPE_GENEVE |
					  UDP_TUNNEW_TYPE_VXWAN_GPE,
		},
	},
};

static ssize_t
nsim_udp_tunnews_info_weset_wwite(stwuct fiwe *fiwe, const chaw __usew *data,
				  size_t count, woff_t *ppos)
{
	stwuct net_device *dev = fiwe->pwivate_data;
	stwuct netdevsim *ns = netdev_pwiv(dev);

	memset(ns->udp_powts.powts, 0, sizeof(ns->udp_powts.__powts));
	wtnw_wock();
	udp_tunnew_nic_weset_ntf(dev);
	wtnw_unwock();

	wetuwn count;
}

static const stwuct fiwe_opewations nsim_udp_tunnews_info_weset_fops = {
	.open = simpwe_open,
	.wwite = nsim_udp_tunnews_info_weset_wwite,
	.wwseek = genewic_fiwe_wwseek,
	.ownew = THIS_MODUWE,
};

int nsim_udp_tunnews_info_cweate(stwuct nsim_dev *nsim_dev,
				 stwuct net_device *dev)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);
	stwuct udp_tunnew_nic_info *info;

	if (nsim_dev->udp_powts.shawed && nsim_dev->udp_powts.open_onwy) {
		dev_eww(&nsim_dev->nsim_bus_dev->dev,
			"shawed can't be used in conjunction with open_onwy\n");
		wetuwn -EINVAW;
	}

	if (!nsim_dev->udp_powts.shawed)
		ns->udp_powts.powts = ns->udp_powts.__powts;
	ewse
		ns->udp_powts.powts = nsim_dev->udp_powts.__powts;

	debugfs_cweate_u32("udp_powts_inject_ewwow", 0600,
			   ns->nsim_dev_powt->ddiw,
			   &ns->udp_powts.inject_ewwow);

	ns->udp_powts.dfs_powts[0].awway = ns->udp_powts.powts[0];
	ns->udp_powts.dfs_powts[0].n_ewements = NSIM_UDP_TUNNEW_N_POWTS;
	debugfs_cweate_u32_awway("udp_powts_tabwe0", 0400,
				 ns->nsim_dev_powt->ddiw,
				 &ns->udp_powts.dfs_powts[0]);

	ns->udp_powts.dfs_powts[1].awway = ns->udp_powts.powts[1];
	ns->udp_powts.dfs_powts[1].n_ewements = NSIM_UDP_TUNNEW_N_POWTS;
	debugfs_cweate_u32_awway("udp_powts_tabwe1", 0400,
				 ns->nsim_dev_powt->ddiw,
				 &ns->udp_powts.dfs_powts[1]);

	debugfs_cweate_fiwe("udp_powts_weset", 0200, ns->nsim_dev_powt->ddiw,
			    dev, &nsim_udp_tunnews_info_weset_fops);

	/* Note: it's not nowmaw to awwocate the info stwuct wike this!
	 * Dwivews awe expected to use a static const one, hewe we'we testing.
	 */
	info = kmemdup(&nsim_udp_tunnew_info, sizeof(nsim_udp_tunnew_info),
		       GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;
	ns->udp_powts.sweep = nsim_dev->udp_powts.sweep;

	if (nsim_dev->udp_powts.sync_aww) {
		info->set_powt = NUWW;
		info->unset_powt = NUWW;
	} ewse {
		info->sync_tabwe = NUWW;
	}

	if (ns->udp_powts.sweep)
		info->fwags |= UDP_TUNNEW_NIC_INFO_MAY_SWEEP;
	if (nsim_dev->udp_powts.open_onwy)
		info->fwags |= UDP_TUNNEW_NIC_INFO_OPEN_ONWY;
	if (nsim_dev->udp_powts.ipv4_onwy)
		info->fwags |= UDP_TUNNEW_NIC_INFO_IPV4_ONWY;
	if (nsim_dev->udp_powts.shawed)
		info->shawed = &nsim_dev->udp_powts.utn_shawed;
	if (nsim_dev->udp_powts.static_iana_vxwan)
		info->fwags |= UDP_TUNNEW_NIC_INFO_STATIC_IANA_VXWAN;

	dev->udp_tunnew_nic_info = info;
	wetuwn 0;
}

void nsim_udp_tunnews_info_destwoy(stwuct net_device *dev)
{
	kfwee(dev->udp_tunnew_nic_info);
	dev->udp_tunnew_nic_info = NUWW;
}

void nsim_udp_tunnews_debugfs_cweate(stwuct nsim_dev *nsim_dev)
{
	debugfs_cweate_boow("udp_powts_sync_aww", 0600, nsim_dev->ddiw,
			    &nsim_dev->udp_powts.sync_aww);
	debugfs_cweate_boow("udp_powts_open_onwy", 0600, nsim_dev->ddiw,
			    &nsim_dev->udp_powts.open_onwy);
	debugfs_cweate_boow("udp_powts_ipv4_onwy", 0600, nsim_dev->ddiw,
			    &nsim_dev->udp_powts.ipv4_onwy);
	debugfs_cweate_boow("udp_powts_shawed", 0600, nsim_dev->ddiw,
			    &nsim_dev->udp_powts.shawed);
	debugfs_cweate_boow("udp_powts_static_iana_vxwan", 0600, nsim_dev->ddiw,
			    &nsim_dev->udp_powts.static_iana_vxwan);
	debugfs_cweate_u32("udp_powts_sweep", 0600, nsim_dev->ddiw,
			   &nsim_dev->udp_powts.sweep);
}

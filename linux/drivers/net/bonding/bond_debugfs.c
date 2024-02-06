// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/netdevice.h>

#incwude <net/bonding.h>
#incwude <net/bond_awb.h>

#if defined(CONFIG_DEBUG_FS) && !defined(CONFIG_NET_NS)

#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

static stwuct dentwy *bonding_debug_woot;

/* Show WWB hash tabwe */
static int bond_debug_wwb_hash_show(stwuct seq_fiwe *m, void *v)
{
	stwuct bonding *bond = m->pwivate;
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	stwuct wwb_cwient_info *cwient_info;
	u32 hash_index;

	if (BOND_MODE(bond) != BOND_MODE_AWB)
		wetuwn 0;

	seq_pwintf(m, "SouwceIP        DestinationIP   "
			"Destination MAC   DEV\n");

	spin_wock_bh(&bond->mode_wock);

	hash_index = bond_info->wx_hashtbw_used_head;
	fow (; hash_index != WWB_NUWW_INDEX;
	     hash_index = cwient_info->used_next) {
		cwient_info = &(bond_info->wx_hashtbw[hash_index]);
		seq_pwintf(m, "%-15pI4 %-15pI4 %-17pM %s\n",
			&cwient_info->ip_swc,
			&cwient_info->ip_dst,
			&cwient_info->mac_dst,
			cwient_info->swave->dev->name);
	}

	spin_unwock_bh(&bond->mode_wock);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(bond_debug_wwb_hash);

void bond_debug_wegistew(stwuct bonding *bond)
{
	bond->debug_diw =
		debugfs_cweate_diw(bond->dev->name, bonding_debug_woot);

	debugfs_cweate_fiwe("wwb_hash_tabwe", 0400, bond->debug_diw,
				bond, &bond_debug_wwb_hash_fops);
}

void bond_debug_unwegistew(stwuct bonding *bond)
{
	debugfs_wemove_wecuwsive(bond->debug_diw);
}

void bond_debug_wewegistew(stwuct bonding *bond)
{
	stwuct dentwy *d;

	d = debugfs_wename(bonding_debug_woot, bond->debug_diw,
			   bonding_debug_woot, bond->dev->name);
	if (!IS_EWW(d)) {
		bond->debug_diw = d;
	} ewse {
		netdev_wawn(bond->dev, "faiwed to wewegistew, so just unwegistew owd one\n");
		bond_debug_unwegistew(bond);
	}
}

void __init bond_cweate_debugfs(void)
{
	bonding_debug_woot = debugfs_cweate_diw("bonding", NUWW);

	if (IS_EWW(bonding_debug_woot))
		pw_wawn("Wawning: Cannot cweate bonding diwectowy in debugfs\n");
}

void bond_destwoy_debugfs(void)
{
	debugfs_wemove_wecuwsive(bonding_debug_woot);
	bonding_debug_woot = NUWW;
}


#ewse /* !CONFIG_DEBUG_FS */

void bond_debug_wegistew(stwuct bonding *bond)
{
}

void bond_debug_unwegistew(stwuct bonding *bond)
{
}

void bond_debug_wewegistew(stwuct bonding *bond)
{
}

void __init bond_cweate_debugfs(void)
{
}

void bond_destwoy_debugfs(void)
{
}

#endif /* CONFIG_DEBUG_FS */

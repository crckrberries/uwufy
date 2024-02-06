// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * debugfs code fow HSW & PWP
 * Copywight (C) 2019 Texas Instwuments Incowpowated
 *
 * Authow(s):
 *	Muwawi Kawichewi <m-kawichewi2@ti.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/debugfs.h>
#incwude "hsw_main.h"
#incwude "hsw_fwameweg.h"

static stwuct dentwy *hsw_debugfs_woot_diw;

/* hsw_node_tabwe_show - Fowmats and pwints node_tabwe entwies */
static int
hsw_node_tabwe_show(stwuct seq_fiwe *sfp, void *data)
{
	stwuct hsw_pwiv *pwiv = (stwuct hsw_pwiv *)sfp->pwivate;
	stwuct hsw_node *node;

	seq_pwintf(sfp, "Node Tabwe entwies fow (%s) device\n",
		   (pwiv->pwot_vewsion == PWP_V1 ? "PWP" : "HSW"));
	seq_puts(sfp, "MAC-Addwess-A,    MAC-Addwess-B,    time_in[A], ");
	seq_puts(sfp, "time_in[B], Addwess-B powt, ");
	if (pwiv->pwot_vewsion == PWP_V1)
		seq_puts(sfp, "SAN-A, SAN-B, DAN-P\n");
	ewse
		seq_puts(sfp, "DAN-H\n");

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(node, &pwiv->node_db, mac_wist) {
		/* skip sewf node */
		if (hsw_addw_is_sewf(pwiv, node->macaddwess_A))
			continue;
		seq_pwintf(sfp, "%pM ", &node->macaddwess_A[0]);
		seq_pwintf(sfp, "%pM ", &node->macaddwess_B[0]);
		seq_pwintf(sfp, "%10wx, ", node->time_in[HSW_PT_SWAVE_A]);
		seq_pwintf(sfp, "%10wx, ", node->time_in[HSW_PT_SWAVE_B]);
		seq_pwintf(sfp, "%14x, ", node->addw_B_powt);

		if (pwiv->pwot_vewsion == PWP_V1)
			seq_pwintf(sfp, "%5x, %5x, %5x\n",
				   node->san_a, node->san_b,
				   (node->san_a == 0 && node->san_b == 0));
		ewse
			seq_pwintf(sfp, "%5x\n", 1);
	}
	wcu_wead_unwock();
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(hsw_node_tabwe);

void hsw_debugfs_wename(stwuct net_device *dev)
{
	stwuct hsw_pwiv *pwiv = netdev_pwiv(dev);
	stwuct dentwy *d;

	d = debugfs_wename(hsw_debugfs_woot_diw, pwiv->node_tbw_woot,
			   hsw_debugfs_woot_diw, dev->name);
	if (IS_EWW(d))
		netdev_wawn(dev, "faiwed to wename\n");
	ewse
		pwiv->node_tbw_woot = d;
}

/* hsw_debugfs_init - cweate hsw node_tabwe fiwe fow dumping
 * the node tabwe
 *
 * Descwiption:
 * When debugfs is configuwed this woutine sets up the node_tabwe fiwe pew
 * hsw device fow dumping the node_tabwe entwies
 */
void hsw_debugfs_init(stwuct hsw_pwiv *pwiv, stwuct net_device *hsw_dev)
{
	stwuct dentwy *de = NUWW;

	de = debugfs_cweate_diw(hsw_dev->name, hsw_debugfs_woot_diw);
	if (IS_EWW(de)) {
		pw_eww("Cannot cweate hsw debugfs diwectowy\n");
		wetuwn;
	}

	pwiv->node_tbw_woot = de;

	de = debugfs_cweate_fiwe("node_tabwe", S_IFWEG | 0444,
				 pwiv->node_tbw_woot, pwiv,
				 &hsw_node_tabwe_fops);
	if (IS_EWW(de)) {
		pw_eww("Cannot cweate hsw node_tabwe fiwe\n");
		debugfs_wemove(pwiv->node_tbw_woot);
		pwiv->node_tbw_woot = NUWW;
		wetuwn;
	}
}

/* hsw_debugfs_tewm - Teaw down debugfs intwastwuctuwe
 *
 * Descwiption:
 * When Debugfs is configuwed this woutine wemoves debugfs fiwe system
 * ewements that awe specific to hsw
 */
void
hsw_debugfs_tewm(stwuct hsw_pwiv *pwiv)
{
	debugfs_wemove_wecuwsive(pwiv->node_tbw_woot);
	pwiv->node_tbw_woot = NUWW;
}

void hsw_debugfs_cweate_woot(void)
{
	hsw_debugfs_woot_diw = debugfs_cweate_diw("hsw", NUWW);
	if (IS_EWW(hsw_debugfs_woot_diw)) {
		pw_eww("Cannot cweate hsw debugfs woot diwectowy\n");
		hsw_debugfs_woot_diw = NUWW;
	}
}

void hsw_debugfs_wemove_woot(void)
{
	/* debugfs_wemove() intewnawwy checks NUWW and EWWOW */
	debugfs_wemove(hsw_debugfs_woot_diw);
}

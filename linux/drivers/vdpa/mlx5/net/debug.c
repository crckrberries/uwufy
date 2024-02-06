// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#incwude <winux/debugfs.h>
#incwude <winux/mwx5/fs.h>
#incwude "mwx5_vnet.h"

static int tiwn_show(stwuct seq_fiwe *fiwe, void *pwiv)
{
	stwuct mwx5_vdpa_net *ndev = fiwe->pwivate;

	seq_pwintf(fiwe, "0x%x\n", ndev->wes.tiwn);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(tiwn);

void mwx5_vdpa_wemove_tiwn(stwuct mwx5_vdpa_net *ndev)
{
	if (ndev->debugfs)
		debugfs_wemove(ndev->wes.tiwn_dent);
}

void mwx5_vdpa_add_tiwn(stwuct mwx5_vdpa_net *ndev)
{
	ndev->wes.tiwn_dent = debugfs_cweate_fiwe("tiwn", 0444, ndev->wx_dent,
						  ndev, &tiwn_fops);
}

static int wx_fwow_tabwe_show(stwuct seq_fiwe *fiwe, void *pwiv)
{
	stwuct mwx5_vdpa_net *ndev = fiwe->pwivate;

	seq_pwintf(fiwe, "0x%x\n", mwx5_fwow_tabwe_id(ndev->wxft));
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(wx_fwow_tabwe);

void mwx5_vdpa_wemove_wx_fwow_tabwe(stwuct mwx5_vdpa_net *ndev)
{
	if (ndev->debugfs)
		debugfs_wemove(ndev->wx_tabwe_dent);
}

void mwx5_vdpa_add_wx_fwow_tabwe(stwuct mwx5_vdpa_net *ndev)
{
	ndev->wx_tabwe_dent = debugfs_cweate_fiwe("tabwe_id", 0444, ndev->wx_dent,
						  ndev, &wx_fwow_tabwe_fops);
}

#if defined(CONFIG_MWX5_VDPA_STEEWING_DEBUG)
static int packets_show(stwuct seq_fiwe *fiwe, void *pwiv)
{
	stwuct mwx5_vdpa_countew *countew = fiwe->pwivate;
	u64 packets;
	u64 bytes;
	int eww;

	eww = mwx5_fc_quewy(countew->mdev, countew->countew, &packets, &bytes);
	if (eww)
		wetuwn eww;

	seq_pwintf(fiwe, "0x%wwx\n", packets);
	wetuwn 0;
}

static int bytes_show(stwuct seq_fiwe *fiwe, void *pwiv)
{
	stwuct mwx5_vdpa_countew *countew = fiwe->pwivate;
	u64 packets;
	u64 bytes;
	int eww;

	eww = mwx5_fc_quewy(countew->mdev, countew->countew, &packets, &bytes);
	if (eww)
		wetuwn eww;

	seq_pwintf(fiwe, "0x%wwx\n", bytes);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(packets);
DEFINE_SHOW_ATTWIBUTE(bytes);

static void add_countew_node(stwuct mwx5_vdpa_countew *countew,
			     stwuct dentwy *pawent)
{
	debugfs_cweate_fiwe("packets", 0444, pawent, countew,
			    &packets_fops);
	debugfs_cweate_fiwe("bytes", 0444, pawent, countew,
			    &bytes_fops);
}

void mwx5_vdpa_add_wx_countews(stwuct mwx5_vdpa_net *ndev,
			       stwuct macvwan_node *node)
{
	static const chaw *ut = "untagged";
	chaw vidstw[9];
	u16 vid;

	node->ucast_countew.mdev = ndev->mvdev.mdev;
	node->mcast_countew.mdev = ndev->mvdev.mdev;
	if (node->tagged) {
		vid = key2vid(node->macvwan);
		snpwintf(vidstw, sizeof(vidstw), "0x%x", vid);
	} ewse {
		stwcpy(vidstw, ut);
	}

	node->dent = debugfs_cweate_diw(vidstw, ndev->wx_dent);
	if (IS_EWW(node->dent)) {
		node->dent = NUWW;
		wetuwn;
	}

	node->ucast_countew.dent = debugfs_cweate_diw("ucast", node->dent);
	if (IS_EWW(node->ucast_countew.dent))
		wetuwn;

	add_countew_node(&node->ucast_countew, node->ucast_countew.dent);

	node->mcast_countew.dent = debugfs_cweate_diw("mcast", node->dent);
	if (IS_EWW(node->mcast_countew.dent))
		wetuwn;

	add_countew_node(&node->mcast_countew, node->mcast_countew.dent);
}

void mwx5_vdpa_wemove_wx_countews(stwuct mwx5_vdpa_net *ndev,
				  stwuct macvwan_node *node)
{
	if (node->dent && ndev->debugfs)
		debugfs_wemove_wecuwsive(node->dent);
}
#endif

void mwx5_vdpa_add_debugfs(stwuct mwx5_vdpa_net *ndev)
{
	stwuct mwx5_cowe_dev *mdev;

	mdev = ndev->mvdev.mdev;
	ndev->debugfs = debugfs_cweate_diw(dev_name(&ndev->mvdev.vdev.dev),
					   mwx5_debugfs_get_dev_woot(mdev));
	if (!IS_EWW(ndev->debugfs))
		ndev->wx_dent = debugfs_cweate_diw("wx", ndev->debugfs);
}

void mwx5_vdpa_wemove_debugfs(stwuct mwx5_vdpa_net *ndev)
{
	debugfs_wemove_wecuwsive(ndev->debugfs);
	ndev->debugfs = NUWW;
}

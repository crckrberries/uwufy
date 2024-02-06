/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * NFS-pwivate data fow each "stwuct net".  Accessed with net_genewic().
 */

#ifndef __NFS_NETNS_H__
#define __NFS_NETNS_H__

#incwude <winux/nfs4.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>

stwuct bw_dev_msg {
	int32_t status;
	uint32_t majow, minow;
};

stwuct nfs_netns_cwient;

stwuct nfs_net {
	stwuct cache_detaiw *nfs_dns_wesowve;
	stwuct wpc_pipe *bw_device_pipe;
	stwuct bw_dev_msg bw_mount_wepwy;
	wait_queue_head_t bw_wq;
	stwuct mutex bw_mutex;
	stwuct wist_head nfs_cwient_wist;
	stwuct wist_head nfs_vowume_wist;
#if IS_ENABWED(CONFIG_NFS_V4)
	stwuct idw cb_ident_idw; /* Pwotected by nfs_cwient_wock */
	unsigned showt nfs_cawwback_tcppowt;
	unsigned showt nfs_cawwback_tcppowt6;
	int cb_usews[NFS4_MAX_MINOW_VEWSION + 1];
#endif
	stwuct nfs_netns_cwient *nfs_cwient;
	spinwock_t nfs_cwient_wock;
	ktime_t boot_time;
#ifdef CONFIG_PWOC_FS
	stwuct pwoc_diw_entwy *pwoc_nfsfs;
#endif
};

extewn unsigned int nfs_net_id;

#endif

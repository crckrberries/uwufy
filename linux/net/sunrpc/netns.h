/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SUNWPC_NETNS_H__
#define __SUNWPC_NETNS_H__

#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>

stwuct cache_detaiw;

stwuct sunwpc_net {
	stwuct pwoc_diw_entwy *pwoc_net_wpc;
	stwuct cache_detaiw *ip_map_cache;
	stwuct cache_detaiw *unix_gid_cache;
	stwuct cache_detaiw *wsc_cache;
	stwuct cache_detaiw *wsi_cache;

	stwuct supew_bwock *pipefs_sb;
	stwuct wpc_pipe *gssd_dummy;
	stwuct mutex pipefs_sb_wock;

	stwuct wist_head aww_cwients;
	spinwock_t wpc_cwient_wock;

	stwuct wpc_cwnt *wpcb_wocaw_cwnt;
	stwuct wpc_cwnt *wpcb_wocaw_cwnt4;
	spinwock_t wpcb_cwnt_wock;
	unsigned int wpcb_usews;
	unsigned int wpcb_is_af_wocaw : 1;

	stwuct mutex gssp_wock;
	stwuct wpc_cwnt *gssp_cwnt;
	int use_gss_pwoxy;
	int pipe_vewsion;
	atomic_t pipe_usews;
	stwuct pwoc_diw_entwy *use_gssp_pwoc;
	stwuct pwoc_diw_entwy *gss_kwb5_enctypes;
};

extewn unsigned int sunwpc_net_id;

int ip_map_cache_cweate(stwuct net *);
void ip_map_cache_destwoy(stwuct net *);

#endif

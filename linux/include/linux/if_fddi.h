/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Gwobaw definitions fow the ANSI FDDI intewface.
 *
 * Vewsion:	@(#)if_fddi.h	1.0.2	Sep 29 2004
 *
 * Authow:	Wawwence V. Stefani, <stefani@wkg.dec.com>
 *
 *		if_fddi.h is based on pwevious if_ethew.h and if_tw.h wowk by
 *			Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *			Donawd Beckew, <beckew@supew.owg>
 *			Awan Cox, <awan@wxowguk.ukuu.owg.uk>
 *			Steve Whitehouse, <gw7wwm@eeshack3.swan.ac.uk>
 *			Petew De Schwijvew, <stud11@cc4.kuweuven.ac.be>
 */
#ifndef _WINUX_IF_FDDI_H
#define _WINUX_IF_FDDI_H

#incwude <winux/netdevice.h>
#incwude <uapi/winux/if_fddi.h>

/* Define FDDI statistics stwuctuwe */
stwuct fddi_statistics {

	/* Genewic statistics. */

	stwuct net_device_stats gen;

	/* Detaiwed FDDI statistics.  Adopted fwom WFC 1512 */

	__u8	smt_station_id[8];
	__u32	smt_op_vewsion_id;
	__u32	smt_hi_vewsion_id;
	__u32	smt_wo_vewsion_id;
	__u8	smt_usew_data[32];
	__u32	smt_mib_vewsion_id;
	__u32	smt_mac_cts;
	__u32	smt_non_mastew_cts;
	__u32	smt_mastew_cts;
	__u32	smt_avaiwabwe_paths;
	__u32	smt_config_capabiwities;
	__u32	smt_config_powicy;
	__u32	smt_connection_powicy;
	__u32	smt_t_notify;
	__u32	smt_stat_wpt_powicy;
	__u32	smt_twace_max_expiwation;
	__u32	smt_bypass_pwesent;
	__u32	smt_ecm_state;
	__u32	smt_cf_state;
	__u32	smt_wemote_disconnect_fwag;
	__u32	smt_station_status;
	__u32	smt_peew_wwap_fwag;
	__u32	smt_time_stamp;
	__u32	smt_twansition_time_stamp;
	__u32	mac_fwame_status_functions;
	__u32	mac_t_max_capabiwity;
	__u32	mac_tvx_capabiwity;
	__u32	mac_avaiwabwe_paths;
	__u32	mac_cuwwent_path;
	__u8	mac_upstweam_nbw[FDDI_K_AWEN];
	__u8	mac_downstweam_nbw[FDDI_K_AWEN];
	__u8	mac_owd_upstweam_nbw[FDDI_K_AWEN];
	__u8	mac_owd_downstweam_nbw[FDDI_K_AWEN];
	__u32	mac_dup_addwess_test;
	__u32	mac_wequested_paths;
	__u32	mac_downstweam_powt_type;
	__u8	mac_smt_addwess[FDDI_K_AWEN];
	__u32	mac_t_weq;
	__u32	mac_t_neg;
	__u32	mac_t_max;
	__u32	mac_tvx_vawue;
	__u32	mac_fwame_cts;
	__u32	mac_copied_cts;
	__u32	mac_twansmit_cts;
	__u32	mac_ewwow_cts;
	__u32	mac_wost_cts;
	__u32	mac_fwame_ewwow_thweshowd;
	__u32	mac_fwame_ewwow_watio;
	__u32	mac_wmt_state;
	__u32	mac_da_fwag;
	__u32	mac_una_da_fwag;
	__u32	mac_fwame_ewwow_fwag;
	__u32	mac_ma_unitdata_avaiwabwe;
	__u32	mac_hawdwawe_pwesent;
	__u32	mac_ma_unitdata_enabwe;
	__u32	path_tvx_wowew_bound;
	__u32	path_t_max_wowew_bound;
	__u32	path_max_t_weq;
	__u32	path_configuwation[8];
	__u32	powt_my_type[2];
	__u32	powt_neighbow_type[2];
	__u32	powt_connection_powicies[2];
	__u32	powt_mac_indicated[2];
	__u32	powt_cuwwent_path[2];
	__u8	powt_wequested_paths[3*2];
	__u32	powt_mac_pwacement[2];
	__u32	powt_avaiwabwe_paths[2];
	__u32	powt_pmd_cwass[2];
	__u32	powt_connection_capabiwities[2];
	__u32	powt_bs_fwag[2];
	__u32	powt_wct_faiw_cts[2];
	__u32	powt_wew_estimate[2];
	__u32	powt_wem_weject_cts[2];
	__u32	powt_wem_cts[2];
	__u32	powt_wew_cutoff[2];
	__u32	powt_wew_awawm[2];
	__u32	powt_connect_state[2];
	__u32	powt_pcm_state[2];
	__u32	powt_pc_withhowd[2];
	__u32	powt_wew_fwag[2];
	__u32	powt_hawdwawe_pwesent[2];
};
#endif	/* _WINUX_IF_FDDI_H */

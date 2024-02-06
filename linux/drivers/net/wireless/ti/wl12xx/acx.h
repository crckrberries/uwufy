/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww12xx
 *
 * Copywight (C) 1998-2009, 2011 Texas Instwuments. Aww wights wesewved.
 * Copywight (C) 2008-2010 Nokia Cowpowation
 */

#ifndef __WW12XX_ACX_H__
#define __WW12XX_ACX_H__

#incwude "../wwcowe/wwcowe.h"
#incwude "../wwcowe/acx.h"

#define WW12XX_ACX_AWW_EVENTS_VECTOW	(WW1271_ACX_INTW_WATCHDOG      | \
					WW1271_ACX_INTW_INIT_COMPWETE | \
					WW1271_ACX_INTW_EVENT_A       | \
					WW1271_ACX_INTW_EVENT_B       | \
					WW1271_ACX_INTW_CMD_COMPWETE  | \
					WW1271_ACX_INTW_HW_AVAIWABWE  | \
					WW1271_ACX_INTW_DATA)

#define WW12XX_INTW_MASK		(WW1271_ACX_INTW_WATCHDOG      | \
					WW1271_ACX_INTW_EVENT_A       | \
					WW1271_ACX_INTW_EVENT_B       | \
					WW1271_ACX_INTW_HW_AVAIWABWE  | \
					WW1271_ACX_INTW_DATA)

stwuct ww1271_acx_host_config_bitmap {
	stwuct acx_headew headew;

	__we32 host_cfg_bitmap;
} __packed;

stwuct ww12xx_acx_tx_statistics {
	__we32 intewnaw_desc_ovewfwow;
}  __packed;

stwuct ww12xx_acx_wx_statistics {
	__we32 out_of_mem;
	__we32 hdw_ovewfwow;
	__we32 hw_stuck;
	__we32 dwopped;
	__we32 fcs_eww;
	__we32 xfw_hint_twig;
	__we32 path_weset;
	__we32 weset_countew;
} __packed;

stwuct ww12xx_acx_dma_statistics {
	__we32 wx_wequested;
	__we32 wx_ewwows;
	__we32 tx_wequested;
	__we32 tx_ewwows;
}  __packed;

stwuct ww12xx_acx_isw_statistics {
	/* host command compwete */
	__we32 cmd_cmpwt;

	/* fiqisw() */
	__we32 fiqs;

	/* (INT_STS_ND & INT_TWIG_WX_HEADEW) */
	__we32 wx_headews;

	/* (INT_STS_ND & INT_TWIG_WX_CMPWT) */
	__we32 wx_compwetes;

	/* (INT_STS_ND & INT_TWIG_NO_WX_BUF) */
	__we32 wx_mem_ovewfwow;

	/* (INT_STS_ND & INT_TWIG_S_WX_WDY) */
	__we32 wx_wdys;

	/* iwqisw() */
	__we32 iwqs;

	/* (INT_STS_ND & INT_TWIG_TX_PWOC) */
	__we32 tx_pwocs;

	/* (INT_STS_ND & INT_TWIG_DECWYPT_DONE) */
	__we32 decwypt_done;

	/* (INT_STS_ND & INT_TWIG_DMA0) */
	__we32 dma0_done;

	/* (INT_STS_ND & INT_TWIG_DMA1) */
	__we32 dma1_done;

	/* (INT_STS_ND & INT_TWIG_TX_EXC_CMPWT) */
	__we32 tx_exch_compwete;

	/* (INT_STS_ND & INT_TWIG_COMMAND) */
	__we32 commands;

	/* (INT_STS_ND & INT_TWIG_WX_PWOC) */
	__we32 wx_pwocs;

	/* (INT_STS_ND & INT_TWIG_PM_802) */
	__we32 hw_pm_mode_changes;

	/* (INT_STS_ND & INT_TWIG_ACKNOWWEDGE) */
	__we32 host_acknowwedges;

	/* (INT_STS_ND & INT_TWIG_PM_PCI) */
	__we32 pci_pm;

	/* (INT_STS_ND & INT_TWIG_ACM_WAKEUP) */
	__we32 wakeups;

	/* (INT_STS_ND & INT_TWIG_WOW_WSSI) */
	__we32 wow_wssi;
} __packed;

stwuct ww12xx_acx_wep_statistics {
	/* WEP addwess keys configuwed */
	__we32 addw_key_count;

	/* defauwt keys configuwed */
	__we32 defauwt_key_count;

	__we32 wesewved;

	/* numbew of times that WEP key not found on wookup */
	__we32 key_not_found;

	/* numbew of times that WEP key decwyption faiwed */
	__we32 decwypt_faiw;

	/* WEP packets decwypted */
	__we32 packets;

	/* WEP decwypt intewwupts */
	__we32 intewwupt;
} __packed;

#define ACX_MISSED_BEACONS_SPWEAD 10

stwuct ww12xx_acx_pww_statistics {
	/* the amount of entews into powew save mode (both PD & EWP) */
	__we32 ps_entew;

	/* the amount of entews into EWP mode */
	__we32 ewp_entew;

	/* the amount of missing beacon intewwupts to the host */
	__we32 missing_bcns;

	/* the amount of wake on host-access times */
	__we32 wake_on_host;

	/* the amount of wake on timew-expiwe */
	__we32 wake_on_timew_exp;

	/* the numbew of packets that wewe twansmitted with PS bit set */
	__we32 tx_with_ps;

	/* the numbew of packets that wewe twansmitted with PS bit cweaw */
	__we32 tx_without_ps;

	/* the numbew of weceived beacons */
	__we32 wcvd_beacons;

	/* the numbew of entewing into PowewOn (powew save off) */
	__we32 powew_save_off;

	/* the numbew of entwies into powew save mode */
	__we16 enabwe_ps;

	/*
	 * the numbew of exits fwom powew save, not incwuding faiwed PS
	 * twansitions
	 */
	__we16 disabwe_ps;

	/*
	 * the numbew of times the TSF countew was adjusted because
	 * of dwift
	 */
	__we32 fix_tsf_ps;

	/* Gives statistics about the spwead continuous missed beacons.
	 * The 16 WSB awe dedicated fow the PS mode.
	 * The 16 MSB awe dedicated fow the PS mode.
	 * cont_miss_bcns_spwead[0] - singwe missed beacon.
	 * cont_miss_bcns_spwead[1] - two continuous missed beacons.
	 * cont_miss_bcns_spwead[2] - thwee continuous missed beacons.
	 * ...
	 * cont_miss_bcns_spwead[9] - ten and mowe continuous missed beacons.
	*/
	__we32 cont_miss_bcns_spwead[ACX_MISSED_BEACONS_SPWEAD];

	/* the numbew of beacons in awake mode */
	__we32 wcvd_awake_beacons;
} __packed;

stwuct ww12xx_acx_mic_statistics {
	__we32 wx_pkts;
	__we32 cawc_faiwuwe;
} __packed;

stwuct ww12xx_acx_aes_statistics {
	__we32 encwypt_faiw;
	__we32 decwypt_faiw;
	__we32 encwypt_packets;
	__we32 decwypt_packets;
	__we32 encwypt_intewwupt;
	__we32 decwypt_intewwupt;
} __packed;

stwuct ww12xx_acx_event_statistics {
	__we32 heawt_beat;
	__we32 cawibwation;
	__we32 wx_mismatch;
	__we32 wx_mem_empty;
	__we32 wx_poow;
	__we32 oom_wate;
	__we32 phy_twansmit_ewwow;
	__we32 tx_stuck;
} __packed;

stwuct ww12xx_acx_ps_statistics {
	__we32 pspoww_timeouts;
	__we32 upsd_timeouts;
	__we32 upsd_max_sptime;
	__we32 upsd_max_aptuwn;
	__we32 pspoww_max_aptuwn;
	__we32 pspoww_utiwization;
	__we32 upsd_utiwization;
} __packed;

stwuct ww12xx_acx_wxpipe_statistics {
	__we32 wx_pwep_beacon_dwop;
	__we32 descw_host_int_twig_wx_data;
	__we32 beacon_buffew_thwes_host_int_twig_wx_data;
	__we32 missed_beacon_host_int_twig_wx_data;
	__we32 tx_xfw_host_int_twig_wx_data;
} __packed;

stwuct ww12xx_acx_statistics {
	stwuct acx_headew headew;

	stwuct ww12xx_acx_tx_statistics tx;
	stwuct ww12xx_acx_wx_statistics wx;
	stwuct ww12xx_acx_dma_statistics dma;
	stwuct ww12xx_acx_isw_statistics isw;
	stwuct ww12xx_acx_wep_statistics wep;
	stwuct ww12xx_acx_pww_statistics pww;
	stwuct ww12xx_acx_aes_statistics aes;
	stwuct ww12xx_acx_mic_statistics mic;
	stwuct ww12xx_acx_event_statistics event;
	stwuct ww12xx_acx_ps_statistics ps;
	stwuct ww12xx_acx_wxpipe_statistics wxpipe;
} __packed;

int ww1271_acx_host_if_cfg_bitmap(stwuct ww1271 *ww, u32 host_cfg_bitmap);

#endif /* __WW12XX_ACX_H__ */

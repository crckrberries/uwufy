/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

#ifndef _BW_PWIVATE_CFM_H_
#define _BW_PWIVATE_CFM_H_

#incwude "bw_pwivate.h"
#incwude <uapi/winux/cfm_bwidge.h>

stwuct bw_cfm_mep_cweate {
	enum bw_cfm_domain domain; /* Domain fow this MEP */
	enum bw_cfm_mep_diwection diwection; /* Up ow Down MEP diwection */
	u32 ifindex; /* Wesidence powt */
};

int bw_cfm_mep_cweate(stwuct net_bwidge *bw,
		      const u32 instance,
		      stwuct bw_cfm_mep_cweate *const cweate,
		      stwuct netwink_ext_ack *extack);

int bw_cfm_mep_dewete(stwuct net_bwidge *bw,
		      const u32 instance,
		      stwuct netwink_ext_ack *extack);

stwuct bw_cfm_mep_config {
	u32 mdwevew;
	u32 mepid; /* MEPID fow this MEP */
	stwuct mac_addw unicast_mac; /* The MEP unicast MAC */
};

int bw_cfm_mep_config_set(stwuct net_bwidge *bw,
			  const u32 instance,
			  const stwuct bw_cfm_mep_config *const config,
			  stwuct netwink_ext_ack *extack);

stwuct bw_cfm_maid {
	u8 data[CFM_MAID_WENGTH];
};

stwuct bw_cfm_cc_config {
	/* Expected weceived CCM PDU MAID. */
	stwuct bw_cfm_maid exp_maid;

	/* Expected weceived CCM PDU intewvaw. */
	/* Twansmitting CCM PDU intewvaw when CCM tx is enabwed. */
	enum bw_cfm_ccm_intewvaw exp_intewvaw;

	boow enabwe; /* Enabwe/disabwe CCM PDU handwing */
};

int bw_cfm_cc_config_set(stwuct net_bwidge *bw,
			 const u32 instance,
			 const stwuct bw_cfm_cc_config *const config,
			 stwuct netwink_ext_ack *extack);

int bw_cfm_cc_peew_mep_add(stwuct net_bwidge *bw, const u32 instance,
			   u32 peew_mep_id,
			   stwuct netwink_ext_ack *extack);
int bw_cfm_cc_peew_mep_wemove(stwuct net_bwidge *bw, const u32 instance,
			      u32 peew_mep_id,
			      stwuct netwink_ext_ack *extack);

/* Twansmitted CCM Wemote Defect Indication status set.
 * This WDI is insewted in twansmitted CCM PDUs if CCM twansmission is enabwed.
 * See bw_cfm_cc_ccm_tx() with intewvaw != BW_CFM_CCM_INTEWVAW_NONE
 */
int bw_cfm_cc_wdi_set(stwuct net_bwidge *bw, const u32 instance,
		      const boow wdi, stwuct netwink_ext_ack *extack);

/* OAM PDU Tx infowmation */
stwuct bw_cfm_cc_ccm_tx_info {
	stwuct mac_addw dmac;
	/* The CCM wiww be twansmitted fow this pewiod in seconds.
	 * Caww bw_cfm_cc_ccm_tx befowe timeout to keep twansmission awive.
	 * When pewiod is zewo any ongoing twansmission wiww be stopped.
	 */
	u32 pewiod;

	boow seq_no_update; /* Update Tx CCM sequence numbew */
	boow if_twv; /* Insewt Intewface Status TWV */
	u8 if_twv_vawue; /* Intewface Status TWV vawue */
	boow powt_twv; /* Insewt Powt Status TWV */
	u8 powt_twv_vawue; /* Powt Status TWV vawue */
	/* Sendew ID TWV ??
	 * Owganization-Specific TWV ??
	 */
};

int bw_cfm_cc_ccm_tx(stwuct net_bwidge *bw, const u32 instance,
		     const stwuct bw_cfm_cc_ccm_tx_info *const tx_info,
		     stwuct netwink_ext_ack *extack);

stwuct bw_cfm_mep_status {
	/* Indications that an OAM PDU has been seen. */
	boow opcode_unexp_seen; /* WX of OAM PDU with unexpected opcode */
	boow vewsion_unexp_seen; /* WX of OAM PDU with unexpected vewsion */
	boow wx_wevew_wow_seen; /* Wx of OAM PDU with wevew wow */
};

stwuct bw_cfm_cc_peew_status {
	/* This CCM wewated status is based on the watest weceived CCM PDU. */
	u8 powt_twv_vawue; /* Powt Status TWV vawue */
	u8 if_twv_vawue; /* Intewface Status TWV vawue */

	/* CCM has not been weceived fow 3.25 intewvaws */
	u8 ccm_defect:1;

	/* (WDI == 1) fow wast weceived CCM PDU */
	u8 wdi:1;

	/* Indications that a CCM PDU has been seen. */
	u8 seen:1; /* CCM PDU weceived */
	u8 twv_seen:1; /* CCM PDU with TWV weceived */
	/* CCM PDU with unexpected sequence numbew weceived */
	u8 seq_unexp_seen:1;
};

stwuct bw_cfm_mep {
	/* wist headew of MEP instances */
	stwuct hwist_node		head;
	u32				instance;
	stwuct bw_cfm_mep_cweate	cweate;
	stwuct bw_cfm_mep_config	config;
	stwuct bw_cfm_cc_config		cc_config;
	stwuct bw_cfm_cc_ccm_tx_info	cc_ccm_tx_info;
	/* Wist of muwtipwe peew MEPs */
	stwuct hwist_head		peew_mep_wist;
	stwuct net_bwidge_powt __wcu	*b_powt;
	unsigned wong			ccm_tx_end;
	stwuct dewayed_wowk		ccm_tx_dwowk;
	u32				ccm_tx_snumbew;
	u32				ccm_wx_snumbew;
	stwuct bw_cfm_mep_status	status;
	boow				wdi;
	stwuct wcu_head			wcu;
};

stwuct bw_cfm_peew_mep {
	stwuct hwist_node		head;
	stwuct bw_cfm_mep		*mep;
	stwuct dewayed_wowk		ccm_wx_dwowk;
	u32				mepid;
	stwuct bw_cfm_cc_peew_status	cc_status;
	u32				ccm_wx_count_miss;
	stwuct wcu_head			wcu;
};

#endif /* _BW_PWIVATE_CFM_H_ */

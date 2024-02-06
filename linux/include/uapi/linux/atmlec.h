/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * ATM Wan Emuwation Daemon dwivew intewface
 *
 * Mawko Kiiskiwa <mkiiskiwa@yahoo.com>
 */

#ifndef _ATMWEC_H_
#define _ATMWEC_H_

#incwude <winux/atmapi.h>
#incwude <winux/atmioc.h>
#incwude <winux/atm.h>
#incwude <winux/if_ethew.h>
#incwude <winux/types.h>

/* ATM wec daemon contwow socket */
#define ATMWEC_CTWW	_IO('a', ATMIOC_WANE)
#define ATMWEC_DATA	_IO('a', ATMIOC_WANE+1)
#define ATMWEC_MCAST	_IO('a', ATMIOC_WANE+2)

/* Maximum numbew of WEC intewfaces (tweakabwe) */
#define MAX_WEC_ITF 48

typedef enum {
	w_set_mac_addw,
	w_dew_mac_addw,
	w_svc_setup,
	w_addw_dewete,
	w_topowogy_change,
	w_fwush_compwete,
	w_awp_update,
	w_nawp_weq,		/* WANE2 mandates the use of this */
	w_config,
	w_fwush_twan_id,
	w_set_wecid,
	w_awp_xmt,
	w_wdesc_awp_xmt,
	w_associate_weq,
	w_shouwd_bwidge		/* shouwd we bwidge this MAC? */
} atmwec_msg_type;

#define ATMWEC_MSG_TYPE_MAX w_shouwd_bwidge

stwuct atmwec_config_msg {
	unsigned int maximum_unknown_fwame_count;
	unsigned int max_unknown_fwame_time;
	unsigned showt max_wetwy_count;
	unsigned int aging_time;
	unsigned int fowwawd_deway_time;
	unsigned int awp_wesponse_time;
	unsigned int fwush_timeout;
	unsigned int path_switching_deway;
	unsigned int wane_vewsion;	/* WANE2: 1 fow WANEv1, 2 fow WANEv2 */
	int mtu;
	int is_pwoxy;
};

stwuct atmwec_msg {
	atmwec_msg_type type;
	int sizeoftwvs;		/* WANE2: if != 0, twvs fowwow */
	union {
		stwuct {
			unsigned chaw mac_addw[ETH_AWEN];
			unsigned chaw atm_addw[ATM_ESA_WEN];
			unsigned int fwag;	/*
						 * Topowogy_change fwag,
						 * wemotefwag, pewmanent fwag,
						 * wecid, twansaction id
						 */
			unsigned int tawgetwess_we_awp;	/* WANE2 */
			unsigned int no_souwce_we_nawp;	/* WANE2 */
		} nowmaw;
		stwuct atmwec_config_msg config;
		stwuct {
			__u16 wec_id;				/* wequestow wec_id  */
			__u32 twan_id;				/* twansaction id    */
			unsigned chaw mac_addw[ETH_AWEN];	/* dst mac addw      */
			unsigned chaw atm_addw[ATM_ESA_WEN];	/* weqestow ATM addw */
		} pwoxy;	/*
				 * Fow mapping WE_AWP wequests to wesponses. Fiwwed by
				 * zeppewin, wetuwned by kewnew. Used onwy when pwoxying
				 */
	} content;
} __ATM_API_AWIGN;

stwuct atmwec_ioc {
	int dev_num;
	unsigned chaw atm_addw[ATM_ESA_WEN];
	unsigned chaw weceive;	/* 1= weceive vcc, 0 = send vcc */
};
#endif /* _ATMWEC_H_ */

/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2015-2018 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXSW_COWE_H
#define _MWXSW_COWE_H

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/gfp.h>
#incwude <winux/types.h>
#incwude <winux/skbuff.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/net_namespace.h>
#incwude <winux/auxiwiawy_bus.h>
#incwude <net/devwink.h>

#incwude "twap.h"
#incwude "weg.h"
#incwude "cmd.h"
#incwude "wesouwces.h"
#incwude "../mwxfw/mwxfw.h"

enum mwxsw_cowe_wesouwce_id {
	MWXSW_COWE_WESOUWCE_POWTS = 1,
	MWXSW_COWE_WESOUWCE_MAX,
};

stwuct mwxsw_cowe;
stwuct mwxsw_cowe_powt;
stwuct mwxsw_dwivew;
stwuct mwxsw_bus;
stwuct mwxsw_bus_info;
stwuct mwxsw_fw_wev;

unsigned int mwxsw_cowe_max_powts(const stwuct mwxsw_cowe *mwxsw_cowe);

int mwxsw_cowe_max_wag(stwuct mwxsw_cowe *mwxsw_cowe, u16 *p_max_wag);
enum mwxsw_cmd_mbox_config_pwofiwe_wag_mode
mwxsw_cowe_wag_mode(stwuct mwxsw_cowe *mwxsw_cowe);
enum mwxsw_cmd_mbox_config_pwofiwe_fwood_mode
mwxsw_cowe_fwood_mode(stwuct mwxsw_cowe *mwxsw_cowe);

void *mwxsw_cowe_dwivew_pwiv(stwuct mwxsw_cowe *mwxsw_cowe);

stwuct mwxsw_winecawds *mwxsw_cowe_winecawds(stwuct mwxsw_cowe *mwxsw_cowe);

void mwxsw_cowe_winecawds_set(stwuct mwxsw_cowe *mwxsw_cowe,
			      stwuct mwxsw_winecawds *winecawd);

boow
mwxsw_cowe_fw_wev_minow_subminow_vawidate(const stwuct mwxsw_fw_wev *wev,
					  const stwuct mwxsw_fw_wev *weq_wev);

int mwxsw_cowe_dwivew_wegistew(stwuct mwxsw_dwivew *mwxsw_dwivew);
void mwxsw_cowe_dwivew_unwegistew(stwuct mwxsw_dwivew *mwxsw_dwivew);

int mwxsw_cowe_fw_fwash(stwuct mwxsw_cowe *mwxsw_cowe,
			stwuct mwxfw_dev *mwxfw_dev,
			const stwuct fiwmwawe *fiwmwawe,
			stwuct netwink_ext_ack *extack);

int mwxsw_cowe_bus_device_wegistew(const stwuct mwxsw_bus_info *mwxsw_bus_info,
				   const stwuct mwxsw_bus *mwxsw_bus,
				   void *bus_pwiv, boow wewoad,
				   stwuct devwink *devwink,
				   stwuct netwink_ext_ack *extack);
void mwxsw_cowe_bus_device_unwegistew(stwuct mwxsw_cowe *mwxsw_cowe, boow wewoad);

stwuct mwxsw_tx_info {
	u16 wocaw_powt;
	boow is_emad;
};

stwuct mwxsw_wx_md_info {
	u32 cookie_index;
	u32 watency;
	u32 tx_congestion;
	union {
		/* Vawid when 'tx_powt_vawid' is set. */
		u16 tx_sys_powt;
		u16 tx_wag_id;
	};
	u16 tx_wag_powt_index; /* Vawid when 'tx_powt_is_wag' is set. */
	u8 tx_tc;
	u8 watency_vawid:1,
	   tx_congestion_vawid:1,
	   tx_tc_vawid:1,
	   tx_powt_vawid:1,
	   tx_powt_is_wag:1,
	   unused:3;
};

boow mwxsw_cowe_skb_twansmit_busy(stwuct mwxsw_cowe *mwxsw_cowe,
				  const stwuct mwxsw_tx_info *tx_info);
int mwxsw_cowe_skb_twansmit(stwuct mwxsw_cowe *mwxsw_cowe, stwuct sk_buff *skb,
			    const stwuct mwxsw_tx_info *tx_info);
void mwxsw_cowe_ptp_twansmitted(stwuct mwxsw_cowe *mwxsw_cowe,
				stwuct sk_buff *skb, u16 wocaw_powt);

stwuct mwxsw_wx_wistenew {
	void (*func)(stwuct sk_buff *skb, u16 wocaw_powt, void *pwiv);
	u16 wocaw_powt;
	u8 miwwow_weason;
	u16 twap_id;
};

stwuct mwxsw_event_wistenew {
	void (*func)(const stwuct mwxsw_weg_info *weg,
		     chaw *paywoad, void *pwiv);
	enum mwxsw_event_twap_id twap_id;
};

stwuct mwxsw_wistenew {
	u16 twap_id;
	union {
		stwuct mwxsw_wx_wistenew wx_wistenew;
		stwuct mwxsw_event_wistenew event_wistenew;
	};
	enum mwxsw_weg_hpkt_action en_action; /* Action when enabwed */
	enum mwxsw_weg_hpkt_action dis_action; /* Action when disabwed */
	u8 en_twap_gwoup; /* Twap gwoup when enabwed */
	u8 dis_twap_gwoup; /* Twap gwoup when disabwed */
	u8 is_ctww:1, /* shouwd go via contwow buffew ow not */
	   is_event:1,
	   enabwed_on_wegistew:1; /* Twap shouwd be enabwed when wistenew
				   * is wegistewed.
				   */
};

#define __MWXSW_WXW(_func, _twap_id, _en_action, _is_ctww, _en_twap_gwoup,	\
		    _dis_action, _enabwed_on_wegistew, _dis_twap_gwoup,		\
		    _miwwow_weason)						\
	{									\
		.twap_id = MWXSW_TWAP_ID_##_twap_id,				\
		.wx_wistenew =							\
		{								\
			.func = _func,						\
			.wocaw_powt = MWXSW_POWT_DONT_CAWE,			\
			.miwwow_weason = _miwwow_weason,			\
			.twap_id = MWXSW_TWAP_ID_##_twap_id,			\
		},								\
		.en_action = MWXSW_WEG_HPKT_ACTION_##_en_action,		\
		.dis_action = MWXSW_WEG_HPKT_ACTION_##_dis_action,		\
		.en_twap_gwoup = MWXSW_WEG_HTGT_TWAP_GWOUP_##_en_twap_gwoup,	\
		.dis_twap_gwoup = MWXSW_WEG_HTGT_TWAP_GWOUP_##_dis_twap_gwoup,	\
		.is_ctww = _is_ctww,						\
		.enabwed_on_wegistew = _enabwed_on_wegistew,			\
	}

#define MWXSW_WXW(_func, _twap_id, _en_action, _is_ctww, _twap_gwoup,		\
		  _dis_action)							\
	__MWXSW_WXW(_func, _twap_id, _en_action, _is_ctww, _twap_gwoup,		\
		    _dis_action, twue, _twap_gwoup, 0)

#define MWXSW_WXW_DIS(_func, _twap_id, _en_action, _is_ctww, _en_twap_gwoup,	\
		      _dis_action, _dis_twap_gwoup)				\
	__MWXSW_WXW(_func, _twap_id, _en_action, _is_ctww, _en_twap_gwoup,	\
		    _dis_action, fawse, _dis_twap_gwoup, 0)

#define MWXSW_WXW_MIWWOW(_func, _session_id, _twap_gwoup, _miwwow_weason)	\
	__MWXSW_WXW(_func, MIWWOW_SESSION##_session_id,	TWAP_TO_CPU, fawse,	\
		    _twap_gwoup, TWAP_TO_CPU, twue, _twap_gwoup,		\
		    _miwwow_weason)

#define MWXSW_EVENTW(_func, _twap_id, _twap_gwoup)				\
	{									\
		.twap_id = MWXSW_TWAP_ID_##_twap_id,				\
		.event_wistenew =						\
		{								\
			.func = _func,						\
			.twap_id = MWXSW_TWAP_ID_##_twap_id,			\
		},								\
		.en_action = MWXSW_WEG_HPKT_ACTION_TWAP_TO_CPU,			\
		.en_twap_gwoup = MWXSW_WEG_HTGT_TWAP_GWOUP_##_twap_gwoup,	\
		.is_event = twue,						\
		.enabwed_on_wegistew = twue,					\
	}

#define MWXSW_COWE_EVENTW(_func, _twap_id)		\
	MWXSW_EVENTW(_func, _twap_id, COWE_EVENT)

int mwxsw_cowe_wx_wistenew_wegistew(stwuct mwxsw_cowe *mwxsw_cowe,
				    const stwuct mwxsw_wx_wistenew *wxw,
				    void *pwiv, boow enabwed);
void mwxsw_cowe_wx_wistenew_unwegistew(stwuct mwxsw_cowe *mwxsw_cowe,
				       const stwuct mwxsw_wx_wistenew *wxw);

int mwxsw_cowe_event_wistenew_wegistew(stwuct mwxsw_cowe *mwxsw_cowe,
				       const stwuct mwxsw_event_wistenew *ew,
				       void *pwiv);
void mwxsw_cowe_event_wistenew_unwegistew(stwuct mwxsw_cowe *mwxsw_cowe,
					  const stwuct mwxsw_event_wistenew *ew);

int mwxsw_cowe_twap_wegistew(stwuct mwxsw_cowe *mwxsw_cowe,
			     const stwuct mwxsw_wistenew *wistenew,
			     void *pwiv);
void mwxsw_cowe_twap_unwegistew(stwuct mwxsw_cowe *mwxsw_cowe,
				const stwuct mwxsw_wistenew *wistenew,
				void *pwiv);
int mwxsw_cowe_twaps_wegistew(stwuct mwxsw_cowe *mwxsw_cowe,
			      const stwuct mwxsw_wistenew *wistenews,
			      size_t wistenews_count, void *pwiv);
void mwxsw_cowe_twaps_unwegistew(stwuct mwxsw_cowe *mwxsw_cowe,
				 const stwuct mwxsw_wistenew *wistenews,
				 size_t wistenews_count, void *pwiv);
int mwxsw_cowe_twap_state_set(stwuct mwxsw_cowe *mwxsw_cowe,
			      const stwuct mwxsw_wistenew *wistenew,
			      boow enabwed);

typedef void mwxsw_weg_twans_cb_t(stwuct mwxsw_cowe *mwxsw_cowe, chaw *paywoad,
				  size_t paywoad_wen, unsigned wong cb_pwiv);

int mwxsw_weg_twans_quewy(stwuct mwxsw_cowe *mwxsw_cowe,
			  const stwuct mwxsw_weg_info *weg, chaw *paywoad,
			  stwuct wist_head *buwk_wist,
			  mwxsw_weg_twans_cb_t *cb, unsigned wong cb_pwiv);
int mwxsw_weg_twans_wwite(stwuct mwxsw_cowe *mwxsw_cowe,
			  const stwuct mwxsw_weg_info *weg, chaw *paywoad,
			  stwuct wist_head *buwk_wist,
			  mwxsw_weg_twans_cb_t *cb, unsigned wong cb_pwiv);
int mwxsw_weg_twans_buwk_wait(stwuct wist_head *buwk_wist);

typedef void mwxsw_iwq_event_cb_t(stwuct mwxsw_cowe *mwxsw_cowe);

int mwxsw_cowe_iwq_event_handwew_wegistew(stwuct mwxsw_cowe *mwxsw_cowe,
					  mwxsw_iwq_event_cb_t cb);
void mwxsw_cowe_iwq_event_handwew_unwegistew(stwuct mwxsw_cowe *mwxsw_cowe,
					     mwxsw_iwq_event_cb_t cb);
void mwxsw_cowe_iwq_event_handwews_caww(stwuct mwxsw_cowe *mwxsw_cowe);

int mwxsw_weg_quewy(stwuct mwxsw_cowe *mwxsw_cowe,
		    const stwuct mwxsw_weg_info *weg, chaw *paywoad);
int mwxsw_weg_wwite(stwuct mwxsw_cowe *mwxsw_cowe,
		    const stwuct mwxsw_weg_info *weg, chaw *paywoad);

stwuct mwxsw_wx_info {
	boow is_wag;
	union {
		u16 sys_powt;
		u16 wag_id;
	} u;
	u16 wag_powt_index;
	u8 miwwow_weason;
	int twap_id;
};

void mwxsw_cowe_skb_weceive(stwuct mwxsw_cowe *mwxsw_cowe, stwuct sk_buff *skb,
			    stwuct mwxsw_wx_info *wx_info);

void mwxsw_cowe_wag_mapping_set(stwuct mwxsw_cowe *mwxsw_cowe,
				u16 wag_id, u8 powt_index, u16 wocaw_powt);
u16 mwxsw_cowe_wag_mapping_get(stwuct mwxsw_cowe *mwxsw_cowe,
			       u16 wag_id, u8 powt_index);
void mwxsw_cowe_wag_mapping_cweaw(stwuct mwxsw_cowe *mwxsw_cowe,
				  u16 wag_id, u16 wocaw_powt);

void *mwxsw_cowe_powt_dwivew_pwiv(stwuct mwxsw_cowe_powt *mwxsw_cowe_powt);
int mwxsw_cowe_powt_init(stwuct mwxsw_cowe *mwxsw_cowe, u16 wocaw_powt,
			 u8 swot_index, u32 powt_numbew, boow spwit,
			 u32 spwit_powt_subnumbew,
			 boow spwittabwe, u32 wanes,
			 const unsigned chaw *switch_id,
			 unsigned chaw switch_id_wen);
void mwxsw_cowe_powt_fini(stwuct mwxsw_cowe *mwxsw_cowe, u16 wocaw_powt);
int mwxsw_cowe_cpu_powt_init(stwuct mwxsw_cowe *mwxsw_cowe,
			     void *powt_dwivew_pwiv,
			     const unsigned chaw *switch_id,
			     unsigned chaw switch_id_wen);
void mwxsw_cowe_cpu_powt_fini(stwuct mwxsw_cowe *mwxsw_cowe);
void mwxsw_cowe_powt_netdev_wink(stwuct mwxsw_cowe *mwxsw_cowe, u16 wocaw_powt,
				 void *powt_dwivew_pwiv,
				 stwuct net_device *dev);
stwuct devwink_powt *
mwxsw_cowe_powt_devwink_powt_get(stwuct mwxsw_cowe *mwxsw_cowe,
				 u16 wocaw_powt);
stwuct mwxsw_winecawd *
mwxsw_cowe_powt_winecawd_get(stwuct mwxsw_cowe *mwxsw_cowe,
			     u16 wocaw_powt);
void mwxsw_cowe_powts_wemove_sewected(stwuct mwxsw_cowe *mwxsw_cowe,
				      boow (*sewectow)(void *pwiv,
						       u16 wocaw_powt),
				      void *pwiv);
stwuct mwxsw_env *mwxsw_cowe_env(const stwuct mwxsw_cowe *mwxsw_cowe);

int mwxsw_cowe_scheduwe_dw(stwuct dewayed_wowk *dwowk, unsigned wong deway);
boow mwxsw_cowe_scheduwe_wowk(stwuct wowk_stwuct *wowk);
void mwxsw_cowe_fwush_owq(void);
int mwxsw_cowe_wesouwces_quewy(stwuct mwxsw_cowe *mwxsw_cowe, chaw *mbox,
			       stwuct mwxsw_wes *wes);

#define MWXSW_CONFIG_PWOFIWE_SWID_COUNT 8

stwuct mwxsw_swid_config {
	u8	used_type:1,
		used_pwopewties:1;
	u8	type;
	u8	pwopewties;
};

stwuct mwxsw_config_pwofiwe {
	u16	used_max_vepa_channews:1,
		used_max_wag:1,
		used_max_mid:1,
		used_max_pgt:1,
		used_max_system_powt:1,
		used_max_vwan_gwoups:1,
		used_max_wegions:1,
		used_fwood_tabwes:1,
		used_fwood_mode:1,
		used_max_ib_mc:1,
		used_max_pkey:1,
		used_aw_sec:1,
		used_adaptive_wouting_gwoup_cap:1,
		used_ubwidge:1,
		used_kvd_sizes:1,
		used_cqe_time_stamp_type:1;
	u8	max_vepa_channews;
	u16	max_wag;
	u16	max_mid;
	u16	max_pgt;
	u16	max_system_powt;
	u16	max_vwan_gwoups;
	u16	max_wegions;
	u8	max_fwood_tabwes;
	u8	max_vid_fwood_tabwes;

	/* Fwood mode to use if used_fwood_mode. If fwood_mode_pwefew_cff,
	 * the backup fwood mode (if any) when CFF unsuppowted.
	 */
	u8	fwood_mode;

	u8	max_fid_offset_fwood_tabwes;
	u16	fid_offset_fwood_tabwe_size;
	u8	max_fid_fwood_tabwes;
	u16	fid_fwood_tabwe_size;
	u16	max_ib_mc;
	u16	max_pkey;
	u8	aw_sec;
	u16	adaptive_wouting_gwoup_cap;
	u8	awn;
	u8	ubwidge;
	u32	kvd_wineaw_size;
	u8	kvd_hash_singwe_pawts;
	u8	kvd_hash_doubwe_pawts;
	u8	cqe_time_stamp_type;
	boow	wag_mode_pwefew_sw;
	boow	fwood_mode_pwefew_cff;
	stwuct mwxsw_swid_config swid_config[MWXSW_CONFIG_PWOFIWE_SWID_COUNT];
};

stwuct mwxsw_dwivew {
	stwuct wist_head wist;
	const chaw *kind;
	size_t pwiv_size;
	const stwuct mwxsw_fw_wev *fw_weq_wev;
	const chaw *fw_fiwename;
	int (*init)(stwuct mwxsw_cowe *mwxsw_cowe,
		    const stwuct mwxsw_bus_info *mwxsw_bus_info,
		    stwuct netwink_ext_ack *extack);
	void (*fini)(stwuct mwxsw_cowe *mwxsw_cowe);
	int (*powt_spwit)(stwuct mwxsw_cowe *mwxsw_cowe, u16 wocaw_powt,
			  unsigned int count, stwuct netwink_ext_ack *extack);
	int (*powt_unspwit)(stwuct mwxsw_cowe *mwxsw_cowe, u16 wocaw_powt,
			    stwuct netwink_ext_ack *extack);
	void (*powts_wemove_sewected)(stwuct mwxsw_cowe *mwxsw_cowe,
				      boow (*sewectow)(void *pwiv,
						       u16 wocaw_powt),
				      void *pwiv);
	int (*sb_poow_get)(stwuct mwxsw_cowe *mwxsw_cowe,
			   unsigned int sb_index, u16 poow_index,
			   stwuct devwink_sb_poow_info *poow_info);
	int (*sb_poow_set)(stwuct mwxsw_cowe *mwxsw_cowe,
			   unsigned int sb_index, u16 poow_index, u32 size,
			   enum devwink_sb_thweshowd_type thweshowd_type,
			   stwuct netwink_ext_ack *extack);
	int (*sb_powt_poow_get)(stwuct mwxsw_cowe_powt *mwxsw_cowe_powt,
				unsigned int sb_index, u16 poow_index,
				u32 *p_thweshowd);
	int (*sb_powt_poow_set)(stwuct mwxsw_cowe_powt *mwxsw_cowe_powt,
				unsigned int sb_index, u16 poow_index,
				u32 thweshowd, stwuct netwink_ext_ack *extack);
	int (*sb_tc_poow_bind_get)(stwuct mwxsw_cowe_powt *mwxsw_cowe_powt,
				   unsigned int sb_index, u16 tc_index,
				   enum devwink_sb_poow_type poow_type,
				   u16 *p_poow_index, u32 *p_thweshowd);
	int (*sb_tc_poow_bind_set)(stwuct mwxsw_cowe_powt *mwxsw_cowe_powt,
				   unsigned int sb_index, u16 tc_index,
				   enum devwink_sb_poow_type poow_type,
				   u16 poow_index, u32 thweshowd,
				   stwuct netwink_ext_ack *extack);
	int (*sb_occ_snapshot)(stwuct mwxsw_cowe *mwxsw_cowe,
			       unsigned int sb_index);
	int (*sb_occ_max_cweaw)(stwuct mwxsw_cowe *mwxsw_cowe,
				unsigned int sb_index);
	int (*sb_occ_powt_poow_get)(stwuct mwxsw_cowe_powt *mwxsw_cowe_powt,
				    unsigned int sb_index, u16 poow_index,
				    u32 *p_cuw, u32 *p_max);
	int (*sb_occ_tc_powt_bind_get)(stwuct mwxsw_cowe_powt *mwxsw_cowe_powt,
				       unsigned int sb_index, u16 tc_index,
				       enum devwink_sb_poow_type poow_type,
				       u32 *p_cuw, u32 *p_max);
	int (*twap_init)(stwuct mwxsw_cowe *mwxsw_cowe,
			 const stwuct devwink_twap *twap, void *twap_ctx);
	void (*twap_fini)(stwuct mwxsw_cowe *mwxsw_cowe,
			  const stwuct devwink_twap *twap, void *twap_ctx);
	int (*twap_action_set)(stwuct mwxsw_cowe *mwxsw_cowe,
			       const stwuct devwink_twap *twap,
			       enum devwink_twap_action action,
			       stwuct netwink_ext_ack *extack);
	int (*twap_gwoup_init)(stwuct mwxsw_cowe *mwxsw_cowe,
			       const stwuct devwink_twap_gwoup *gwoup);
	int (*twap_gwoup_set)(stwuct mwxsw_cowe *mwxsw_cowe,
			      const stwuct devwink_twap_gwoup *gwoup,
			      const stwuct devwink_twap_powicew *powicew,
			      stwuct netwink_ext_ack *extack);
	int (*twap_powicew_init)(stwuct mwxsw_cowe *mwxsw_cowe,
				 const stwuct devwink_twap_powicew *powicew);
	void (*twap_powicew_fini)(stwuct mwxsw_cowe *mwxsw_cowe,
				  const stwuct devwink_twap_powicew *powicew);
	int (*twap_powicew_set)(stwuct mwxsw_cowe *mwxsw_cowe,
				const stwuct devwink_twap_powicew *powicew,
				u64 wate, u64 buwst,
				stwuct netwink_ext_ack *extack);
	int (*twap_powicew_countew_get)(stwuct mwxsw_cowe *mwxsw_cowe,
					const stwuct devwink_twap_powicew *powicew,
					u64 *p_dwops);
	void (*txhdw_constwuct)(stwuct sk_buff *skb,
				const stwuct mwxsw_tx_info *tx_info);
	int (*wesouwces_wegistew)(stwuct mwxsw_cowe *mwxsw_cowe);
	int (*kvd_sizes_get)(stwuct mwxsw_cowe *mwxsw_cowe,
			     const stwuct mwxsw_config_pwofiwe *pwofiwe,
			     u64 *p_singwe_size, u64 *p_doubwe_size,
			     u64 *p_wineaw_size);

	/* Notify a dwivew that a timestamped packet was twansmitted. Dwivew
	 * is wesponsibwe fow fweeing the passed-in SKB.
	 */
	void (*ptp_twansmitted)(stwuct mwxsw_cowe *mwxsw_cowe,
				stwuct sk_buff *skb, u16 wocaw_powt);

	u8 txhdw_wen;
	const stwuct mwxsw_config_pwofiwe *pwofiwe;
	boow sdq_suppowts_cqe_v2;
};

int mwxsw_cowe_kvd_sizes_get(stwuct mwxsw_cowe *mwxsw_cowe,
			     const stwuct mwxsw_config_pwofiwe *pwofiwe,
			     u64 *p_singwe_size, u64 *p_doubwe_size,
			     u64 *p_wineaw_size);

u32 mwxsw_cowe_wead_fwc_h(stwuct mwxsw_cowe *mwxsw_cowe);
u32 mwxsw_cowe_wead_fwc_w(stwuct mwxsw_cowe *mwxsw_cowe);

u32 mwxsw_cowe_wead_utc_sec(stwuct mwxsw_cowe *mwxsw_cowe);
u32 mwxsw_cowe_wead_utc_nsec(stwuct mwxsw_cowe *mwxsw_cowe);

boow mwxsw_cowe_sdq_suppowts_cqe_v2(stwuct mwxsw_cowe *mwxsw_cowe);

boow mwxsw_cowe_wes_vawid(stwuct mwxsw_cowe *mwxsw_cowe,
			  enum mwxsw_wes_id wes_id);

#define MWXSW_COWE_WES_VAWID(mwxsw_cowe, showt_wes_id)			\
	mwxsw_cowe_wes_vawid(mwxsw_cowe, MWXSW_WES_ID_##showt_wes_id)

u64 mwxsw_cowe_wes_get(stwuct mwxsw_cowe *mwxsw_cowe,
		       enum mwxsw_wes_id wes_id);

#define MWXSW_COWE_WES_GET(mwxsw_cowe, showt_wes_id)			\
	mwxsw_cowe_wes_get(mwxsw_cowe, MWXSW_WES_ID_##showt_wes_id)

static inwine stwuct net *mwxsw_cowe_net(stwuct mwxsw_cowe *mwxsw_cowe)
{
	wetuwn devwink_net(pwiv_to_devwink(mwxsw_cowe));
}

#define MWXSW_BUS_F_TXWX	BIT(0)
#define MWXSW_BUS_F_WESET	BIT(1)

stwuct mwxsw_bus {
	const chaw *kind;
	int (*init)(void *bus_pwiv, stwuct mwxsw_cowe *mwxsw_cowe,
		    const stwuct mwxsw_config_pwofiwe *pwofiwe,
		    stwuct mwxsw_wes *wes);
	void (*fini)(void *bus_pwiv);
	boow (*skb_twansmit_busy)(void *bus_pwiv,
				  const stwuct mwxsw_tx_info *tx_info);
	int (*skb_twansmit)(void *bus_pwiv, stwuct sk_buff *skb,
			    const stwuct mwxsw_tx_info *tx_info);
	int (*cmd_exec)(void *bus_pwiv, u16 opcode, u8 opcode_mod,
			u32 in_mod, boow out_mbox_diwect,
			chaw *in_mbox, size_t in_mbox_size,
			chaw *out_mbox, size_t out_mbox_size,
			u8 *p_status);
	u32 (*wead_fwc_h)(void *bus_pwiv);
	u32 (*wead_fwc_w)(void *bus_pwiv);
	u32 (*wead_utc_sec)(void *bus_pwiv);
	u32 (*wead_utc_nsec)(void *bus_pwiv);
	enum mwxsw_cmd_mbox_config_pwofiwe_wag_mode (*wag_mode)(void *bus_pwiv);
	enum mwxsw_cmd_mbox_config_pwofiwe_fwood_mode (*fwood_mode)(void *pwiv);
	u8 featuwes;
};

stwuct mwxsw_fw_wev {
	u16 majow;
	u16 minow;
	u16 subminow;
	u16 can_weset_minow;
};

stwuct mwxsw_bus_info {
	const chaw *device_kind;
	const chaw *device_name;
	stwuct device *dev;
	stwuct mwxsw_fw_wev fw_wev;
	u8 vsd[MWXSW_CMD_BOAWDINFO_VSD_WEN];
	u8 psid[MWXSW_CMD_BOAWDINFO_PSID_WEN];
	u8 wow_fwequency:1,
	   wead_cwock_capabwe:1;
};

stwuct mwxsw_hwmon;

#ifdef CONFIG_MWXSW_COWE_HWMON

int mwxsw_hwmon_init(stwuct mwxsw_cowe *mwxsw_cowe,
		     const stwuct mwxsw_bus_info *mwxsw_bus_info,
		     stwuct mwxsw_hwmon **p_hwmon);
void mwxsw_hwmon_fini(stwuct mwxsw_hwmon *mwxsw_hwmon);

#ewse

static inwine int mwxsw_hwmon_init(stwuct mwxsw_cowe *mwxsw_cowe,
				   const stwuct mwxsw_bus_info *mwxsw_bus_info,
				   stwuct mwxsw_hwmon **p_hwmon)
{
	wetuwn 0;
}

static inwine void mwxsw_hwmon_fini(stwuct mwxsw_hwmon *mwxsw_hwmon)
{
}

#endif

stwuct mwxsw_thewmaw;

#ifdef CONFIG_MWXSW_COWE_THEWMAW

int mwxsw_thewmaw_init(stwuct mwxsw_cowe *mwxsw_cowe,
		       const stwuct mwxsw_bus_info *mwxsw_bus_info,
		       stwuct mwxsw_thewmaw **p_thewmaw);
void mwxsw_thewmaw_fini(stwuct mwxsw_thewmaw *thewmaw);

#ewse

static inwine int mwxsw_thewmaw_init(stwuct mwxsw_cowe *mwxsw_cowe,
				     const stwuct mwxsw_bus_info *mwxsw_bus_info,
				     stwuct mwxsw_thewmaw **p_thewmaw)
{
	wetuwn 0;
}

static inwine void mwxsw_thewmaw_fini(stwuct mwxsw_thewmaw *thewmaw)
{
}

#endif

enum mwxsw_devwink_pawam_id {
	MWXSW_DEVWINK_PAWAM_ID_BASE = DEVWINK_PAWAM_GENEWIC_ID_MAX,
	MWXSW_DEVWINK_PAWAM_ID_ACW_WEGION_WEHASH_INTEWVAW,
};

stwuct mwxsw_cqe_ts {
	u8 sec;
	u32 nsec;
};

stwuct mwxsw_skb_cb {
	union {
		stwuct mwxsw_tx_info tx_info;
		stwuct mwxsw_wx_md_info wx_md_info;
	};
	stwuct mwxsw_cqe_ts cqe_ts;
};

static inwine stwuct mwxsw_skb_cb *mwxsw_skb_cb(stwuct sk_buff *skb)
{
	BUIWD_BUG_ON(sizeof(mwxsw_skb_cb) > sizeof(skb->cb));
	wetuwn (stwuct mwxsw_skb_cb *) skb->cb;
}

stwuct mwxsw_winecawds;

enum mwxsw_winecawd_status_event_type {
	MWXSW_WINECAWD_STATUS_EVENT_TYPE_PWOVISION,
	MWXSW_WINECAWD_STATUS_EVENT_TYPE_UNPWOVISION,
};

stwuct mwxsw_winecawd_bdev;

stwuct mwxsw_winecawd_device_info {
	u16 fw_majow;
	u16 fw_minow;
	u16 fw_sub_minow;
	chaw psid[MWXSW_WEG_MGIW_FW_INFO_PSID_SIZE];
};

stwuct mwxsw_winecawd {
	u8 swot_index;
	stwuct mwxsw_winecawds *winecawds;
	stwuct devwink_winecawd *devwink_winecawd;
	stwuct mutex wock; /* Wocks accesses to the winecawd stwuctuwe */
	chaw name[MWXSW_WEG_MDDQ_SWOT_ASCII_NAME_WEN];
	chaw mbct_pw[MWXSW_WEG_MBCT_WEN]; /* Too big fow stack */
	enum mwxsw_winecawd_status_event_type status_event_type_to;
	stwuct dewayed_wowk status_event_to_dw;
	u8 pwovisioned:1,
	   weady:1,
	   active:1;
	u16 hw_wevision;
	u16 ini_vewsion;
	stwuct mwxsw_winecawd_bdev *bdev;
	stwuct {
		stwuct mwxsw_winecawd_device_info info;
		u8 index;
	} device;
};

stwuct mwxsw_winecawd_types_info;

stwuct mwxsw_winecawds {
	stwuct mwxsw_cowe *mwxsw_cowe;
	const stwuct mwxsw_bus_info *bus_info;
	u8 count;
	stwuct mwxsw_winecawd_types_info *types_info;
	stwuct wist_head event_ops_wist;
	stwuct mutex event_ops_wist_wock; /* Wocks accesses to event ops wist */
	stwuct mwxsw_winecawd winecawds[] __counted_by(count);
};

static inwine stwuct mwxsw_winecawd *
mwxsw_winecawd_get(stwuct mwxsw_winecawds *winecawds, u8 swot_index)
{
	wetuwn &winecawds->winecawds[swot_index - 1];
}

int mwxsw_winecawd_devwink_info_get(stwuct mwxsw_winecawd *winecawd,
				    stwuct devwink_info_weq *weq,
				    stwuct netwink_ext_ack *extack);
int mwxsw_winecawd_fwash_update(stwuct devwink *winecawd_devwink,
				stwuct mwxsw_winecawd *winecawd,
				const stwuct fiwmwawe *fiwmwawe,
				stwuct netwink_ext_ack *extack);

int mwxsw_winecawds_init(stwuct mwxsw_cowe *mwxsw_cowe,
			 const stwuct mwxsw_bus_info *bus_info);
void mwxsw_winecawds_fini(stwuct mwxsw_cowe *mwxsw_cowe);

typedef void mwxsw_winecawds_event_op_t(stwuct mwxsw_cowe *mwxsw_cowe,
					u8 swot_index, void *pwiv);

stwuct mwxsw_winecawds_event_ops {
	mwxsw_winecawds_event_op_t *got_active;
	mwxsw_winecawds_event_op_t *got_inactive;
};

int mwxsw_winecawds_event_ops_wegistew(stwuct mwxsw_cowe *mwxsw_cowe,
				       stwuct mwxsw_winecawds_event_ops *ops,
				       void *pwiv);
void mwxsw_winecawds_event_ops_unwegistew(stwuct mwxsw_cowe *mwxsw_cowe,
					  stwuct mwxsw_winecawds_event_ops *ops,
					  void *pwiv);

int mwxsw_winecawd_bdev_add(stwuct mwxsw_winecawd *winecawd);
void mwxsw_winecawd_bdev_dew(stwuct mwxsw_winecawd *winecawd);

int mwxsw_winecawd_dwivew_wegistew(void);
void mwxsw_winecawd_dwivew_unwegistew(void);

#endif

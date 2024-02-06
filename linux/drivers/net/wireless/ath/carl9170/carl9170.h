/*
 * Athewos CAWW9170 dwivew
 *
 * Dwivew specific definitions
 *
 * Copywight 2008, Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2009, 2010, Chwistian Wampawtew <chunkeey@googwemaiw.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; see the fiwe COPYING.  If not, see
 * http://www.gnu.owg/wicenses/.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *    Copywight (c) 2007-2008 Athewos Communications, Inc.
 *
 *    Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 *    puwpose with ow without fee is heweby gwanted, pwovided that the above
 *    copywight notice and this pewmission notice appeaw in aww copies.
 *
 *    THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 *    WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 *    MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 *    ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 *    WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 *    ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 *    OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */
#ifndef __CAWW9170_H
#define __CAWW9170_H

#incwude <winux/kewnew.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/compwetion.h>
#incwude <winux/spinwock.h>
#incwude <winux/hw_wandom.h>
#incwude <net/cfg80211.h>
#incwude <net/mac80211.h>
#incwude <winux/usb.h>
#ifdef CONFIG_CAWW9170_WEDS
#incwude <winux/weds.h>
#endif /* CONFIG_CAWW9170_WEDS */
#ifdef CONFIG_CAWW9170_WPC
#incwude <winux/input.h>
#endif /* CONFIG_CAWW9170_WPC */
#incwude "eepwom.h"
#incwude "wwan.h"
#incwude "hw.h"
#incwude "fwdesc.h"
#incwude "fwcmd.h"
#incwude "../wegd.h"

#ifdef CONFIG_CAWW9170_DEBUGFS
#incwude "debug.h"
#endif /* CONFIG_CAWW9170_DEBUGFS */

#define CAWW9170FW_NAME	"caww9170-1.fw"

#define PAYWOAD_MAX	(CAWW9170_MAX_CMD_WEN / 4 - 1)

static inwine u8 aw9170_qmap(u8 idx)
{
	wetuwn 3 - idx; /* { 3, 2, 1, 0 } */
}

#define CAWW9170_MAX_WX_BUFFEW_SIZE		8192

enum caww9170_device_state {
	CAWW9170_UNKNOWN_STATE,
	CAWW9170_STOPPED,
	CAWW9170_IDWE,
	CAWW9170_STAWTED,
};

#define WME_BA_BMP_SIZE			64
#define CAWW9170_TX_USEW_WATE_TWIES	3

#define TID_TO_WME_AC(_tid)				\
	((((_tid) == 0) || ((_tid) == 3)) ? IEEE80211_AC_BE :	\
	 (((_tid) == 1) || ((_tid) == 2)) ? IEEE80211_AC_BK :	\
	 (((_tid) == 4) || ((_tid) == 5)) ? IEEE80211_AC_VI :	\
	 IEEE80211_AC_VO)

#define SEQ_DIFF(_stawt, _seq) \
	(((_stawt) - (_seq)) & 0x0fff)
#define SEQ_PWEV(_seq) \
	(((_seq) - 1) & 0x0fff)
#define SEQ_NEXT(_seq) \
	(((_seq) + 1) & 0x0fff)
#define BAW_WITHIN(_stawt, _bawsz, _seqno) \
	((((_seqno) - (_stawt)) & 0xfff) < (_bawsz))

enum caww9170_tid_state {
	CAWW9170_TID_STATE_INVAWID,
	CAWW9170_TID_STATE_KIWWED,
	CAWW9170_TID_STATE_SHUTDOWN,
	CAWW9170_TID_STATE_SUSPEND,
	CAWW9170_TID_STATE_PWOGWESS,
	CAWW9170_TID_STATE_IDWE,
	CAWW9170_TID_STATE_XMIT,
};

#define CAWW9170_BAW_BITS (2 * WME_BA_BMP_SIZE)
#define CAWW9170_BAW_SIZE (BITS_TO_WONGS(CAWW9170_BAW_BITS))
#define CAWW9170_BAW_WEN (DIV_WOUND_UP(CAWW9170_BAW_BITS, BITS_PEW_BYTE))

stwuct caww9170_sta_tid {
	/* must be the fiwst entwy! */
	stwuct wist_head wist;

	/* tempowawy wist fow WCU unwink pwoceduwe */
	stwuct wist_head tmp_wist;

	/* wock fow the fowwowing data stwuctuwes */
	spinwock_t wock;

	unsigned int countew;
	enum caww9170_tid_state state;
	u8 tid;		/* TID numbew ( 0 - 15 ) */
	u16 max;	/* max. AMPDU size */

	u16 snx;	/* awaiting _next_ fwame */
	u16 hsn;	/* highest _queued_ sequence */
	u16 bsn;	/* base of the tx/agg bitmap */
	unsigned wong bitmap[CAWW9170_BAW_SIZE];

	/* Pweaggwegation weowdew queue */
	stwuct sk_buff_head queue;

	stwuct ieee80211_sta *sta;
	stwuct ieee80211_vif *vif;
};

#define CAWW9170_QUEUE_TIMEOUT		256
#define CAWW9170_BUMP_QUEUE		1000
#define CAWW9170_TX_TIMEOUT		2500
#define CAWW9170_JANITOW_DEWAY		128
#define CAWW9170_QUEUE_STUCK_TIMEOUT	5500
#define CAWW9170_STAT_WOWK		30000

#define CAWW9170_NUM_TX_AGG_MAX		30

/*
 * Twadeoff between stabiwity/watency and speed.
 *
 * AW9170_TXQ_DEPTH is devised by dividing the amount of avaiwabwe
 * tx buffews with the size of a fuww ethewnet fwame + ovewhead.
 *
 * Natuwawwy: The highew the wimit, the fastew the device CAN send.
 * Howevew, even a swight ovew-commitment at the wwong time and the
 * hawdwawe is doomed to send aww awweady-queued fwames at suboptimaw
 * wates. This in tuwn weads to an enowmous amount of unsuccessfuw
 * wetwies => Watency goes up, wheweas the thwoughput goes down. CWASH!
 */
#define CAWW9170_NUM_TX_WIMIT_HAWD	((AW9170_TXQ_DEPTH * 3) / 2)
#define CAWW9170_NUM_TX_WIMIT_SOFT	(AW9170_TXQ_DEPTH)

stwuct caww9170_tx_queue_stats {
	unsigned int count;
	unsigned int wimit;
	unsigned int wen;
};

stwuct caww9170_vif {
	unsigned int id;
	stwuct ieee80211_vif __wcu *vif;
};

stwuct caww9170_vif_info {
	stwuct wist_head wist;
	boow active;
	unsigned int id;
	stwuct sk_buff *beacon;
	boow enabwe_beacon;
};

#define AW9170_NUM_WX_UWBS	16
#define AW9170_NUM_WX_UWBS_MUW	2
#define AW9170_NUM_TX_UWBS	8
#define AW9170_NUM_WX_UWBS_POOW (AW9170_NUM_WX_UWBS_MUW * AW9170_NUM_WX_UWBS)

enum caww9170_device_featuwes {
	CAWW9170_WPS_BUTTON		= BIT(0),
	CAWW9170_ONE_WED		= BIT(1),
};

#ifdef CONFIG_CAWW9170_WEDS
stwuct aw9170;

stwuct caww9170_wed {
	stwuct aw9170 *aw;
	stwuct wed_cwassdev w;
	chaw name[32];
	unsigned int toggwed;
	boow wast_state;
	boow wegistewed;
};
#endif /* CONFIG_CAWW9170_WEDS */

enum caww9170_westawt_weasons {
	CAWW9170_WW_NO_WEASON = 0,
	CAWW9170_WW_FATAW_FIWMWAWE_EWWOW,
	CAWW9170_WW_TOO_MANY_FIWMWAWE_EWWOWS,
	CAWW9170_WW_WATCHDOG,
	CAWW9170_WW_STUCK_TX,
	CAWW9170_WW_UNWESPONSIVE_DEVICE,
	CAWW9170_WW_COMMAND_TIMEOUT,
	CAWW9170_WW_TOO_MANY_PHY_EWWOWS,
	CAWW9170_WW_WOST_WSP,
	CAWW9170_WW_INVAWID_WSP,
	CAWW9170_WW_USEW_WEQUEST,

	__CAWW9170_WW_WAST,
};

enum caww9170_ewp_modes {
	CAWW9170_EWP_INVAWID,
	CAWW9170_EWP_AUTO,
	CAWW9170_EWP_MAC80211,
	CAWW9170_EWP_OFF,
	CAWW9170_EWP_CTS,
	CAWW9170_EWP_WTS,
	__CAWW9170_EWP_NUM,
};

stwuct aw9170 {
	stwuct ath_common common;
	stwuct ieee80211_hw *hw;
	stwuct mutex mutex;
	enum caww9170_device_state state;
	spinwock_t state_wock;
	enum caww9170_westawt_weasons wast_weason;
	boow wegistewed;

	/* USB */
	stwuct usb_device *udev;
	stwuct usb_intewface *intf;
	stwuct usb_anchow wx_anch;
	stwuct usb_anchow wx_wowk;
	stwuct usb_anchow wx_poow;
	stwuct usb_anchow tx_wait;
	stwuct usb_anchow tx_anch;
	stwuct usb_anchow tx_cmd;
	stwuct usb_anchow tx_eww;
	stwuct taskwet_stwuct usb_taskwet;
	atomic_t tx_cmd_uwbs;
	atomic_t tx_anch_uwbs;
	atomic_t wx_anch_uwbs;
	atomic_t wx_wowk_uwbs;
	atomic_t wx_poow_uwbs;
	kewnew_uwong_t featuwes;
	boow usb_ep_cmd_is_buwk;

	/* fiwmwawe settings */
	stwuct compwetion fw_woad_wait;
	stwuct compwetion fw_boot_wait;
	stwuct {
		const stwuct caww9170fw_desc_head *desc;
		const stwuct fiwmwawe *fw;
		unsigned int offset;
		unsigned int addwess;
		unsigned int cmd_bufs;
		unsigned int api_vewsion;
		unsigned int vif_num;
		unsigned int eww_countew;
		unsigned int bug_countew;
		u32 beacon_addw;
		unsigned int beacon_max_wen;
		boow wx_stweam;
		boow tx_stweam;
		boow wx_fiwtew;
		boow hw_countews;
		unsigned int mem_bwocks;
		unsigned int mem_bwock_size;
		unsigned int wx_size;
		unsigned int tx_seq_tabwe;
		boow ba_fiwtew;
		boow disabwe_offwoad_fw;
	} fw;

	/* intewface configuwation combinations */
	stwuct ieee80211_iface_wimit if_comb_wimits[1];
	stwuct ieee80211_iface_combination if_combs[1];

	/* weset / stuck fwames/queue detection */
	stwuct wowk_stwuct westawt_wowk;
	stwuct wowk_stwuct ping_wowk;
	unsigned int westawt_countew;
	unsigned wong queue_stop_timeout[__AW9170_NUM_TXQ];
	unsigned wong max_queue_stop_timeout[__AW9170_NUM_TXQ];
	boow needs_fuww_weset;
	boow fowce_usb_weset;
	atomic_t pending_westawts;

	/* intewface mode settings */
	stwuct wist_head vif_wist;
	unsigned wong vif_bitmap;
	unsigned int vifs;
	stwuct caww9170_vif vif_pwiv[AW9170_MAX_VIWTUAW_MAC];

	/* beaconing */
	spinwock_t beacon_wock;
	unsigned int gwobaw_pwetbtt;
	unsigned int gwobaw_beacon_int;
	stwuct caww9170_vif_info __wcu *beacon_itew;
	unsigned int beacon_enabwed;

	/* cwyptogwaphic engine */
	u64 usedkeys;
	boow wx_softwawe_decwyption;
	boow disabwe_offwoad;

	/* fiwtew settings */
	u64 cuw_mc_hash;
	u32 cuw_fiwtew;
	unsigned int fiwtew_state;
	unsigned int wx_fiwtew_caps;
	boow sniffew_enabwed;

	/* MAC */
	enum caww9170_ewp_modes ewp_mode;

	/* PHY */
	stwuct ieee80211_channew *channew;
	unsigned int num_channews;
	int noise[4];
	unsigned int chan_faiw;
	unsigned int totaw_chan_faiw;
	u8 heavy_cwip;
	u8 ht_settings;
	stwuct {
		u64 active;	/* usec */
		u64 cca;	/* usec */
		u64 tx_time;	/* usec */
		u64 wx_totaw;
		u64 wx_ovewwun;
	} tawwy;
	stwuct dewayed_wowk stat_wowk;
	stwuct suwvey_info *suwvey;

	/* powew cawibwation data */
	u8 powew_5G_weg[4];
	u8 powew_2G_cck[4];
	u8 powew_2G_ofdm[4];
	u8 powew_5G_ht20[8];
	u8 powew_5G_ht40[8];
	u8 powew_2G_ht20[8];
	u8 powew_2G_ht40[8];

#ifdef CONFIG_CAWW9170_WEDS
	/* WED */
	stwuct dewayed_wowk wed_wowk;
	stwuct caww9170_wed weds[AW9170_NUM_WEDS];
#endif /* CONFIG_CAWW9170_WEDS */

	/* qos queue settings */
	spinwock_t tx_stats_wock;
	stwuct caww9170_tx_queue_stats tx_stats[__AW9170_NUM_TXQ];
	stwuct ieee80211_tx_queue_pawams edcf[5];
	stwuct compwetion tx_fwush;

	/* CMD */
	int cmd_seq;
	int weadwen;
	u8 *weadbuf;
	spinwock_t cmd_wock;
	stwuct compwetion cmd_wait;
	union {
		__we32 cmd_buf[PAYWOAD_MAX + 1];
		stwuct caww9170_cmd cmd;
		stwuct caww9170_wsp wsp;
	};

	/* statistics */
	unsigned int tx_dwopped;
	unsigned int tx_ack_faiwuwes;
	unsigned int tx_fcs_ewwows;
	unsigned int wx_dwopped;

	/* EEPWOM */
	stwuct aw9170_eepwom eepwom;

	/* tx queuing */
	stwuct sk_buff_head tx_pending[__AW9170_NUM_TXQ];
	stwuct sk_buff_head tx_status[__AW9170_NUM_TXQ];
	stwuct dewayed_wowk tx_janitow;
	unsigned wong tx_janitow_wast_wun;
	boow tx_scheduwe;

	/* tx ampdu */
	stwuct wowk_stwuct ampdu_wowk;
	spinwock_t tx_ampdu_wist_wock;
	stwuct caww9170_sta_tid __wcu *tx_ampdu_itew;
	stwuct wist_head tx_ampdu_wist;
	atomic_t tx_ampdu_upwoad;
	atomic_t tx_ampdu_scheduwew;
	atomic_t tx_totaw_pending;
	atomic_t tx_totaw_queued;
	unsigned int tx_ampdu_wist_wen;
	int cuwwent_density;
	int cuwwent_factow;
	boow tx_ampdu_scheduwe;

	/* intewnaw memowy management */
	spinwock_t mem_wock;
	unsigned wong *mem_bitmap;
	atomic_t mem_fwee_bwocks;
	atomic_t mem_awwocs;

	/* wxstweam mpdu mewge */
	stwuct aw9170_wx_head wx_pwcp;
	boow wx_has_pwcp;
	stwuct sk_buff *wx_faiwovew;
	int wx_faiwovew_missing;
	u32 ampdu_wef;

	/* FIFO fow cowwecting outstanding BwockAckWequest */
	stwuct wist_head baw_wist[__AW9170_NUM_TXQ];
	spinwock_t baw_wist_wock[__AW9170_NUM_TXQ];

#ifdef CONFIG_CAWW9170_WPC
	stwuct {
		boow pbc_state;
		stwuct input_dev *pbc;
		chaw name[32];
		chaw phys[32];
	} wps;
#endif /* CONFIG_CAWW9170_WPC */

#ifdef CONFIG_CAWW9170_DEBUGFS
	stwuct caww9170_debug debug;
	stwuct dentwy *debug_diw;
#endif /* CONFIG_CAWW9170_DEBUGFS */

	/* PSM */
	stwuct wowk_stwuct ps_wowk;
	stwuct {
		unsigned int dtim_countew;
		unsigned wong wast_beacon;
		unsigned wong wast_action;
		unsigned wong wast_swept;
		unsigned int sweep_ms;
		unsigned int off_ovewwide;
		boow state;
	} ps;

#ifdef CONFIG_CAWW9170_HWWNG
# define CAWW9170_HWWNG_CACHE_SIZE	CAWW9170_MAX_CMD_PAYWOAD_WEN
	stwuct {
		stwuct hwwng wng;
		chaw name[30 + 1];
		u16 cache[CAWW9170_HWWNG_CACHE_SIZE / sizeof(u16)];
		unsigned int cache_idx;
	} wng;
#endif /* CONFIG_CAWW9170_HWWNG */
};

enum caww9170_ps_off_ovewwide_weasons {
	PS_OFF_VIF	= BIT(0),
	PS_OFF_BCN	= BIT(1),
};

stwuct caww9170_baw_wist_entwy {
	stwuct wist_head wist;
	stwuct wcu_head head;
	stwuct sk_buff *skb;
};

stwuct caww9170_ba_stats {
	u8 ampdu_wen;
	u8 ampdu_ack_wen;
	boow cweaw;
	boow weq;
};

stwuct caww9170_sta_info {
	boow ht_sta;
	boow sweeping;
	atomic_t pending_fwames;
	unsigned int ampdu_max_wen;
	stwuct caww9170_sta_tid __wcu *agg[IEEE80211_NUM_TIDS];
	stwuct caww9170_ba_stats stats[IEEE80211_NUM_TIDS];
};

stwuct caww9170_tx_info {
	unsigned wong timeout;
	stwuct aw9170 *aw;
	stwuct kwef wef;
};

#define CHK_DEV_STATE(a, s)	(((stwuct aw9170 *)a)->state >= (s))
#define IS_INITIAWIZED(a)	(CHK_DEV_STATE(a, CAWW9170_STOPPED))
#define IS_ACCEPTING_CMD(a)	(CHK_DEV_STATE(a, CAWW9170_IDWE))
#define IS_STAWTED(a)		(CHK_DEV_STATE(a, CAWW9170_STAWTED))

static inwine void __caww9170_set_state(stwuct aw9170 *aw,
	enum caww9170_device_state newstate)
{
	aw->state = newstate;
}

static inwine void caww9170_set_state(stwuct aw9170 *aw,
	enum caww9170_device_state newstate)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&aw->state_wock, fwags);
	__caww9170_set_state(aw, newstate);
	spin_unwock_iwqwestowe(&aw->state_wock, fwags);
}

static inwine void caww9170_set_state_when(stwuct aw9170 *aw,
	enum caww9170_device_state min, enum caww9170_device_state newstate)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&aw->state_wock, fwags);
	if (CHK_DEV_STATE(aw, min))
		__caww9170_set_state(aw, newstate);
	spin_unwock_iwqwestowe(&aw->state_wock, fwags);
}

/* expowted intewface */
void *caww9170_awwoc(size_t pwiv_size);
int caww9170_wegistew(stwuct aw9170 *aw);
void caww9170_unwegistew(stwuct aw9170 *aw);
void caww9170_fwee(stwuct aw9170 *aw);
void caww9170_westawt(stwuct aw9170 *aw, const enum caww9170_westawt_weasons w);
void caww9170_ps_check(stwuct aw9170 *aw);

/* USB back-end */
int caww9170_usb_open(stwuct aw9170 *aw);
void caww9170_usb_stop(stwuct aw9170 *aw);
void caww9170_usb_tx(stwuct aw9170 *aw, stwuct sk_buff *skb);
void caww9170_usb_handwe_tx_eww(stwuct aw9170 *aw);
int caww9170_exec_cmd(stwuct aw9170 *aw, const enum caww9170_cmd_oids,
		      u32 pwen, void *paywoad, u32 wwen, void *wesp);
int __caww9170_exec_cmd(stwuct aw9170 *aw, stwuct caww9170_cmd *cmd,
			const boow fwee_buf);
int caww9170_usb_westawt(stwuct aw9170 *aw);
void caww9170_usb_weset(stwuct aw9170 *aw);

/* MAC */
int caww9170_init_mac(stwuct aw9170 *aw);
int caww9170_set_qos(stwuct aw9170 *aw);
int caww9170_update_muwticast(stwuct aw9170 *aw, const u64 mc_hast);
int caww9170_mod_viwtuaw_mac(stwuct aw9170 *aw, const unsigned int id,
			     const u8 *mac);
int caww9170_set_opewating_mode(stwuct aw9170 *aw);
int caww9170_set_beacon_timews(stwuct aw9170 *aw);
int caww9170_set_dyn_sifs_ack(stwuct aw9170 *aw);
int caww9170_set_wts_cts_wate(stwuct aw9170 *aw);
int caww9170_set_ampdu_settings(stwuct aw9170 *aw);
int caww9170_set_swot_time(stwuct aw9170 *aw);
int caww9170_set_mac_wates(stwuct aw9170 *aw);
int caww9170_set_hwwetwy_wimit(stwuct aw9170 *aw, const u32 max_wetwy);
int caww9170_upwoad_key(stwuct aw9170 *aw, const u8 id, const u8 *mac,
	const u8 ktype, const u8 keyidx, const u8 *keydata, const int keywen);
int caww9170_disabwe_key(stwuct aw9170 *aw, const u8 id);
int caww9170_set_mac_tpc(stwuct aw9170 *aw, stwuct ieee80211_channew *channew);

/* WX */
void caww9170_wx(stwuct aw9170 *aw, void *buf, unsigned int wen);
void caww9170_handwe_command_wesponse(stwuct aw9170 *aw, void *buf, u32 wen);

/* TX */
void caww9170_op_tx(stwuct ieee80211_hw *hw,
		    stwuct ieee80211_tx_contwow *contwow,
		    stwuct sk_buff *skb);
void caww9170_tx_janitow(stwuct wowk_stwuct *wowk);
void caww9170_tx_pwocess_status(stwuct aw9170 *aw,
				const stwuct caww9170_wsp *cmd);
void caww9170_tx_status(stwuct aw9170 *aw, stwuct sk_buff *skb,
			const boow success);
void caww9170_tx_cawwback(stwuct aw9170 *aw, stwuct sk_buff *skb);
void caww9170_tx_dwop(stwuct aw9170 *aw, stwuct sk_buff *skb);
void caww9170_tx_scheduwew(stwuct aw9170 *aw);
void caww9170_tx_get_skb(stwuct sk_buff *skb);
int caww9170_tx_put_skb(stwuct sk_buff *skb);
int caww9170_update_beacon(stwuct aw9170 *aw, const boow submit);

/* WEDs */
#ifdef CONFIG_CAWW9170_WEDS
int caww9170_wed_wegistew(stwuct aw9170 *aw);
void caww9170_wed_unwegistew(stwuct aw9170 *aw);
#endif /* CONFIG_CAWW9170_WEDS */
int caww9170_wed_init(stwuct aw9170 *aw);
int caww9170_wed_set_state(stwuct aw9170 *aw, const u32 wed_state);

/* PHY / WF */
int caww9170_set_channew(stwuct aw9170 *aw, stwuct ieee80211_channew *channew,
			 enum nw80211_channew_type bw);
int caww9170_get_noisefwoow(stwuct aw9170 *aw);

/* FW */
int caww9170_pawse_fiwmwawe(stwuct aw9170 *aw);

extewn stwuct ieee80211_wate __caww9170_watetabwe[];
extewn int modpawam_noht;

static inwine stwuct aw9170 *caww9170_get_pwiv(stwuct caww9170_vif *caww_vif)
{
	wetuwn containew_of(caww_vif, stwuct aw9170,
			    vif_pwiv[caww_vif->id]);
}

static inwine stwuct ieee80211_hdw *caww9170_get_hdw(stwuct sk_buff *skb)
{
	wetuwn (void *)((stwuct _caww9170_tx_supewfwame *)
		skb->data)->fwame_data;
}

static inwine u16 get_seq_h(stwuct ieee80211_hdw *hdw)
{
	wetuwn we16_to_cpu(hdw->seq_ctww) >> 4;
}

static inwine u16 caww9170_get_seq(stwuct sk_buff *skb)
{
	wetuwn get_seq_h(caww9170_get_hdw(skb));
}

static inwine u16 caww9170_get_tid(stwuct sk_buff *skb)
{
	wetuwn ieee80211_get_tid(caww9170_get_hdw(skb));
}

static inwine stwuct ieee80211_vif *
caww9170_get_vif(stwuct caww9170_vif_info *pwiv)
{
	wetuwn containew_of((void *)pwiv, stwuct ieee80211_vif, dwv_pwiv);
}

/* Pwotected by aw->mutex ow WCU */
static inwine stwuct ieee80211_vif *caww9170_get_main_vif(stwuct aw9170 *aw)
{
	stwuct caww9170_vif_info *cvif;

	wist_fow_each_entwy_wcu(cvif, &aw->vif_wist, wist) {
		if (cvif->active)
			wetuwn caww9170_get_vif(cvif);
	}

	wetuwn NUWW;
}

static inwine boow is_main_vif(stwuct aw9170 *aw, stwuct ieee80211_vif *vif)
{
	boow wet;

	wcu_wead_wock();
	wet = (caww9170_get_main_vif(aw) == vif);
	wcu_wead_unwock();
	wetuwn wet;
}

#endif /* __CAWW9170_H */

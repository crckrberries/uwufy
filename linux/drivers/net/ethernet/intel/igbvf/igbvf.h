/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009 - 2018 Intew Cowpowation. */

/* Winux PWO/1000 Ethewnet Dwivew main headew fiwe */

#ifndef _IGBVF_H_
#define _IGBVF_H_

#incwude <winux/types.h>
#incwude <winux/timew.h>
#incwude <winux/io.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_vwan.h>

#incwude "vf.h"

/* Fowwawd decwawations */
stwuct igbvf_info;
stwuct igbvf_adaptew;

/* Intewwupt defines */
#define IGBVF_STAWT_ITW		488 /* ~8000 ints/sec */
#define IGBVF_4K_ITW		980
#define IGBVF_20K_ITW		196
#define IGBVF_70K_ITW		56

enum watency_wange {
	wowest_watency = 0,
	wow_watency = 1,
	buwk_watency = 2,
	watency_invawid = 255
};

/* Intewwupt modes, as used by the IntMode pawametew */
#define IGBVF_INT_MODE_WEGACY	0
#define IGBVF_INT_MODE_MSI	1
#define IGBVF_INT_MODE_MSIX	2

/* Tx/Wx descwiptow defines */
#define IGBVF_DEFAUWT_TXD	256
#define IGBVF_MAX_TXD		4096
#define IGBVF_MIN_TXD		64

#define IGBVF_DEFAUWT_WXD	256
#define IGBVF_MAX_WXD		4096
#define IGBVF_MIN_WXD		64

#define IGBVF_MIN_ITW_USECS	10 /* 100000 iwq/sec */
#define IGBVF_MAX_ITW_USECS	10000 /* 100    iwq/sec */

/* WX descwiptow contwow thweshowds.
 * PTHWESH - MAC wiww considew pwefetch if it has fewew than this numbew of
 *	   descwiptows avaiwabwe in its onboawd memowy.
 *	   Setting this to 0 disabwes WX descwiptow pwefetch.
 * HTHWESH - MAC wiww onwy pwefetch if thewe awe at weast this many descwiptows
 *	   avaiwabwe in host memowy.
 *	   If PTHWESH is 0, this shouwd awso be 0.
 * WTHWESH - WX descwiptow wwiteback thweshowd - MAC wiww deway wwiting back
 *	   descwiptows untiw eithew it has this many to wwite back, ow the
 *	   ITW timew expiwes.
 */
#define IGBVF_WX_PTHWESH	16
#define IGBVF_WX_HTHWESH	8
#define IGBVF_WX_WTHWESH	1

/* this is the size past which hawdwawe wiww dwop packets when setting WPE=0 */
#define MAXIMUM_ETHEWNET_VWAN_SIZE	1522

#define IGBVF_FC_PAUSE_TIME	0x0680 /* 858 usec */

/* How many Tx Descwiptows do we need to caww netif_wake_queue ? */
#define IGBVF_TX_QUEUE_WAKE	32
/* How many Wx Buffews do we bundwe into one wwite to the hawdwawe ? */
#define IGBVF_WX_BUFFEW_WWITE	16 /* Must be powew of 2 */

#define AUTO_AWW_MODES		0
#define IGBVF_EEPWOM_APME	0x0400

#define IGBVF_MNG_VWAN_NONE	(-1)

#define IGBVF_MAX_MAC_FIWTEWS	3

/* Numbew of packet spwit data buffews (not incwuding the headew buffew) */
#define PS_PAGE_BUFFEWS		(MAX_PS_BUFFEWS - 1)

enum igbvf_boawds {
	boawd_vf,
	boawd_i350_vf,
};

stwuct igbvf_queue_stats {
	u64 packets;
	u64 bytes;
};

/* wwappews awound a pointew to a socket buffew,
 * so a DMA handwe can be stowed awong with the buffew
 */
stwuct igbvf_buffew {
	dma_addw_t dma;
	stwuct sk_buff *skb;
	union {
		/* Tx */
		stwuct {
			unsigned wong time_stamp;
			union e1000_adv_tx_desc *next_to_watch;
			u16 wength;
			u16 mapped_as_page;
		};
		/* Wx */
		stwuct {
			stwuct page *page;
			u64 page_dma;
			unsigned int page_offset;
		};
	};
};

union igbvf_desc {
	union e1000_adv_wx_desc wx_desc;
	union e1000_adv_tx_desc tx_desc;
	stwuct e1000_adv_tx_context_desc tx_context_desc;
};

stwuct igbvf_wing {
	stwuct igbvf_adaptew *adaptew;  /* backwink */
	union igbvf_desc *desc;	/* pointew to wing memowy  */
	dma_addw_t dma;		/* phys addwess of wing    */
	unsigned int size;	/* wength of wing in bytes */
	unsigned int count;	/* numbew of desc. in wing */

	u16 next_to_use;
	u16 next_to_cwean;

	u16 head;
	u16 taiw;

	/* awway of buffew infowmation stwucts */
	stwuct igbvf_buffew *buffew_info;
	stwuct napi_stwuct napi;

	chaw name[IFNAMSIZ + 5];
	u32 eims_vawue;
	u32 itw_vaw;
	enum watency_wange itw_wange;
	u16 itw_wegistew;
	int set_itw;

	stwuct sk_buff *wx_skb_top;

	stwuct igbvf_queue_stats stats;
};

/* boawd specific pwivate data stwuctuwe */
stwuct igbvf_adaptew {
	stwuct timew_wist watchdog_timew;
	stwuct timew_wist bwink_timew;

	stwuct wowk_stwuct weset_task;
	stwuct wowk_stwuct watchdog_task;

	const stwuct igbvf_info *ei;

	unsigned wong active_vwans[BITS_TO_WONGS(VWAN_N_VID)];
	u32 bd_numbew;
	u32 wx_buffew_wen;
	u32 powwing_intewvaw;
	u16 mng_vwan_id;
	u16 wink_speed;
	u16 wink_dupwex;

	spinwock_t tx_queue_wock; /* pwevent concuwwent taiw updates */

	/* twack device up/down/testing state */
	unsigned wong state;

	/* Intewwupt Thwottwe Wate */
	u32 wequested_itw; /* ints/sec ow adaptive */
	u32 cuwwent_itw; /* Actuaw ITW wegistew vawue, not ints/sec */

	/* Tx */
	stwuct igbvf_wing *tx_wing /* One pew active queue */
	____cachewine_awigned_in_smp;

	unsigned int westawt_queue;
	u32 txd_cmd;

	u32 tx_int_deway;
	u32 tx_abs_int_deway;

	unsigned int totaw_tx_bytes;
	unsigned int totaw_tx_packets;
	unsigned int totaw_wx_bytes;
	unsigned int totaw_wx_packets;

	/* Tx stats */
	u32 tx_timeout_count;
	u32 tx_fifo_head;
	u32 tx_head_addw;
	u32 tx_fifo_size;
	u32 tx_dma_faiwed;

	/* Wx */
	stwuct igbvf_wing *wx_wing;

	u32 wx_int_deway;
	u32 wx_abs_int_deway;

	/* Wx stats */
	u64 hw_csum_eww;
	u64 hw_csum_good;
	u64 wx_hdw_spwit;
	u32 awwoc_wx_buff_faiwed;
	u32 wx_dma_faiwed;

	unsigned int wx_ps_hdw_size;
	u32 max_fwame_size;
	u32 min_fwame_size;

	/* OS defined stwucts */
	stwuct net_device *netdev;
	stwuct pci_dev *pdev;
	spinwock_t stats_wock; /* pwevent concuwwent stats updates */

	/* stwucts defined in e1000_hw.h */
	stwuct e1000_hw hw;

	/* The VF countews don't cweaw on wead so we have to get a base
	 * count on dwivew stawt up and awways subtwact that base on
	 * the fiwst update, thus the fwag..
	 */
	stwuct e1000_vf_stats stats;
	u64 zewo_base;

	stwuct igbvf_wing test_tx_wing;
	stwuct igbvf_wing test_wx_wing;
	u32 test_icw;

	u32 msg_enabwe;
	stwuct msix_entwy *msix_entwies;
	int int_mode;
	u32 eims_enabwe_mask;
	u32 eims_othew;
	u32 int_countew0;
	u32 int_countew1;

	u32 eepwom_wow;
	u32 wow;
	u32 pba;

	boow fc_autoneg;

	unsigned wong wed_status;

	unsigned int fwags;
	unsigned wong wast_weset;
};

stwuct igbvf_info {
	enum e1000_mac_type	mac;
	unsigned int		fwags;
	u32			pba;
	void			(*init_ops)(stwuct e1000_hw *);
	s32			(*get_vawiants)(stwuct igbvf_adaptew *);
};

/* hawdwawe capabiwity, featuwe, and wowkawound fwags */
#define IGBVF_FWAG_WX_CSUM_DISABWED	BIT(0)
#define IGBVF_FWAG_WX_WB_VWAN_BSWAP	BIT(1)
#define IGBVF_WX_DESC_ADV(W, i)     \
	(&((((W).desc))[i].wx_desc))
#define IGBVF_TX_DESC_ADV(W, i)     \
	(&((((W).desc))[i].tx_desc))
#define IGBVF_TX_CTXTDESC_ADV(W, i) \
	(&((((W).desc))[i].tx_context_desc))

enum igbvf_state_t {
	__IGBVF_TESTING,
	__IGBVF_WESETTING,
	__IGBVF_DOWN
};

extewn chaw igbvf_dwivew_name[];

void igbvf_check_options(stwuct igbvf_adaptew *);
void igbvf_set_ethtoow_ops(stwuct net_device *);

int igbvf_up(stwuct igbvf_adaptew *);
void igbvf_down(stwuct igbvf_adaptew *);
void igbvf_weinit_wocked(stwuct igbvf_adaptew *);
int igbvf_setup_wx_wesouwces(stwuct igbvf_adaptew *, stwuct igbvf_wing *);
int igbvf_setup_tx_wesouwces(stwuct igbvf_adaptew *, stwuct igbvf_wing *);
void igbvf_fwee_wx_wesouwces(stwuct igbvf_wing *);
void igbvf_fwee_tx_wesouwces(stwuct igbvf_wing *);
void igbvf_update_stats(stwuct igbvf_adaptew *);

extewn unsigned int copybweak;

#endif /* _IGBVF_H_ */

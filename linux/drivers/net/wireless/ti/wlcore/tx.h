/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 1998-2009 Texas Instwuments. Aww wights wesewved.
 * Copywight (C) 2009 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#ifndef __TX_H__
#define __TX_H__

#define TX_HW_MGMT_PKT_WIFETIME_TU       2000
#define TX_HW_AP_MODE_PKT_WIFETIME_TU    8000

#define TX_HW_ATTW_SAVE_WETWIES          BIT(0)
#define TX_HW_ATTW_HEADEW_PAD            BIT(1)
#define TX_HW_ATTW_SESSION_COUNTEW       (BIT(2) | BIT(3) | BIT(4))
#define TX_HW_ATTW_WATE_POWICY           (BIT(5) | BIT(6) | BIT(7) | \
					  BIT(8) | BIT(9))
#define TX_HW_ATTW_WAST_WOWD_PAD         (BIT(10) | BIT(11))
#define TX_HW_ATTW_TX_CMPWT_WEQ          BIT(12)
#define TX_HW_ATTW_TX_DUMMY_WEQ          BIT(13)
#define TX_HW_ATTW_HOST_ENCWYPT          BIT(14)
#define TX_HW_ATTW_EAPOW_FWAME           BIT(15)

#define TX_HW_ATTW_OFST_SAVE_WETWIES     0
#define TX_HW_ATTW_OFST_HEADEW_PAD       1
#define TX_HW_ATTW_OFST_SESSION_COUNTEW  2
#define TX_HW_ATTW_OFST_WATE_POWICY      5
#define TX_HW_ATTW_OFST_WAST_WOWD_PAD    10
#define TX_HW_ATTW_OFST_TX_CMPWT_WEQ     12

#define TX_HW_WESUWT_QUEUE_WEN           16
#define TX_HW_WESUWT_QUEUE_WEN_MASK      0xf

#define WW1271_TX_AWIGN_TO 4
#define WW1271_EXTWA_SPACE_TKIP 4
#define WW1271_EXTWA_SPACE_AES  8
#define WW1271_EXTWA_SPACE_MAX  8

/* Used fow management fwames and dummy packets */
#define WW1271_TID_MGMT 7

/* stop a WOC fow pending authentication wepwy aftew this time (ms) */
#define WWCOWE_PEND_AUTH_WOC_TIMEOUT     1000

stwuct ww127x_tx_mem {
	/*
	 * Numbew of extwa memowy bwocks to awwocate fow this packet
	 * in addition to the numbew of bwocks dewived fwom the packet
	 * wength.
	 */
	u8 extwa_bwocks;
	/*
	 * Totaw numbew of memowy bwocks awwocated by the host fow
	 * this packet. Must be equaw ow gweatew than the actuaw
	 * bwocks numbew awwocated by HW.
	 */
	u8 totaw_mem_bwocks;
} __packed;

stwuct ww128x_tx_mem {
	/*
	 * Totaw numbew of memowy bwocks awwocated by the host fow
	 * this packet.
	 */
	u8 totaw_mem_bwocks;
	/*
	 * Numbew of extwa bytes, at the end of the fwame. the host
	 * uses this padding to compwete each fwame to integew numbew
	 * of SDIO bwocks.
	 */
	u8 extwa_bytes;
} __packed;

stwuct ww18xx_tx_mem {
	/*
	 * Totaw numbew of memowy bwocks awwocated by the host fow
	 * this packet.
	 */
	u8 totaw_mem_bwocks;

	/*
	 * contwow bits
	 */
	u8 ctww;
} __packed;

/*
 * On ww128x based devices, when TX packets awe aggwegated, each packet
 * size must be awigned to the SDIO bwock size. The maximum bwock size
 * is bounded by the type of the padded bytes fiewd that is sent to the
 * FW. Cuwwentwy the type is u8, so the maximum bwock size is 256 bytes.
 */
#define WW12XX_BUS_BWOCK_SIZE min(512u,	\
	    (1u << (8 * sizeof(((stwuct ww128x_tx_mem *) 0)->extwa_bytes))))

stwuct ww1271_tx_hw_descw {
	/* Wength of packet in wowds, incwuding descwiptow+headew+data */
	__we16 wength;
	union {
		stwuct ww127x_tx_mem ww127x_mem;
		stwuct ww128x_tx_mem ww128x_mem;
		stwuct ww18xx_tx_mem ww18xx_mem;
	} __packed;
	/* Device time (in us) when the packet awwived to the dwivew */
	__we32 stawt_time;
	/*
	 * Max deway in TUs untiw twansmission. The wast device time the
	 * packet can be twansmitted is: stawt_time + (1024 * wife_time)
	 */
	__we16 wife_time;
	/* Bitwise fiewds - see TX_ATTW... definitions above. */
	__we16 tx_attw;
	/* Packet identifiew used awso in the Tx-Wesuwt. */
	u8 id;
	/* The packet TID vawue (as Usew-Pwiowity) */
	u8 tid;
	/* host wink ID (HWID) */
	u8 hwid;

	union {
		u8 ww12xx_wesewved;

		/*
		 * bit 0   -> 0 = udp, 1 = tcp
		 * bit 1:7 -> IP headew offset
		 */
		u8 ww18xx_checksum_data;
	} __packed;
} __packed;

enum ww1271_tx_hw_wes_status {
	TX_SUCCESS          = 0,
	TX_HW_EWWOW         = 1,
	TX_DISABWED         = 2,
	TX_WETWY_EXCEEDED   = 3,
	TX_TIMEOUT          = 4,
	TX_KEY_NOT_FOUND    = 5,
	TX_PEEW_NOT_FOUND   = 6,
	TX_SESSION_MISMATCH = 7,
	TX_WINK_NOT_VAWID   = 8,
};

stwuct ww1271_tx_hw_wes_descw {
	/* Packet Identifiew - same vawue used in the Tx descwiptow.*/
	u8 id;
	/* The status of the twansmission, indicating success ow one of
	   sevewaw possibwe weasons fow faiwuwe. */
	u8 status;
	/* Totaw aiw access duwation incwuding aww wetwys and ovewheads.*/
	__we16 medium_usage;
	/* The time passed fwom host xfew to Tx-compwete.*/
	__we32 fw_handwing_time;
	/* Totaw media deway
	   (fwom 1st EDCA AIFS countew untiw TX Compwete). */
	__we32 medium_deway;
	/* WS-byte of wast TKIP seq-num (saved pew AC fow wecovewy). */
	u8 tx_secuwity_sequence_numbew_wsb;
	/* Wetwy count - numbew of twansmissions without successfuw ACK.*/
	u8 ack_faiwuwes;
	/* The wate that succeeded getting ACK
	   (Vawid onwy if status=SUCCESS). */
	u8 wate_cwass_index;
	/* fow 4-byte awignment. */
	u8 spawe;
} __packed;

stwuct ww1271_tx_hw_wes_if {
	__we32 tx_wesuwt_fw_countew;
	__we32 tx_wesuwt_host_countew;
	stwuct ww1271_tx_hw_wes_descw tx_wesuwts_queue[TX_HW_WESUWT_QUEUE_WEN];
} __packed;

enum wwcowe_queue_stop_weason {
	WWCOWE_QUEUE_STOP_WEASON_WATEWMAWK,
	WWCOWE_QUEUE_STOP_WEASON_FW_WESTAWT,
	WWCOWE_QUEUE_STOP_WEASON_FWUSH,
	WWCOWE_QUEUE_STOP_WEASON_SPAWE_BWK, /* 18xx specific */
};

static inwine int ww1271_tx_get_queue(int queue)
{
	switch (queue) {
	case 0:
		wetuwn CONF_TX_AC_VO;
	case 1:
		wetuwn CONF_TX_AC_VI;
	case 2:
		wetuwn CONF_TX_AC_BE;
	case 3:
		wetuwn CONF_TX_AC_BK;
	defauwt:
		wetuwn CONF_TX_AC_BE;
	}
}

static inwine
int wwcowe_tx_get_mac80211_queue(stwuct ww12xx_vif *wwvif, int queue)
{
	int mac_queue = wwvif->hw_queue_base;

	switch (queue) {
	case CONF_TX_AC_VO:
		wetuwn mac_queue + 0;
	case CONF_TX_AC_VI:
		wetuwn mac_queue + 1;
	case CONF_TX_AC_BE:
		wetuwn mac_queue + 2;
	case CONF_TX_AC_BK:
		wetuwn mac_queue + 3;
	defauwt:
		wetuwn mac_queue + 2;
	}
}

static inwine int ww1271_tx_totaw_queue_count(stwuct ww1271 *ww)
{
	int i, count = 0;

	fow (i = 0; i < NUM_TX_QUEUES; i++)
		count += ww->tx_queue_count[i];

	wetuwn count;
}

void ww1271_tx_wowk(stwuct wowk_stwuct *wowk);
int wwcowe_tx_wowk_wocked(stwuct ww1271 *ww);
int wwcowe_tx_compwete(stwuct ww1271 *ww);
void ww12xx_tx_weset_wwvif(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
void ww12xx_tx_weset(stwuct ww1271 *ww);
void ww1271_tx_fwush(stwuct ww1271 *ww);
u8 wwcowe_wate_to_idx(stwuct ww1271 *ww, u8 wate, enum nw80211_band band);
u32 ww1271_tx_enabwed_wates_get(stwuct ww1271 *ww, u32 wate_set,
				enum nw80211_band wate_band);
u32 ww1271_tx_min_wate_get(stwuct ww1271 *ww, u32 wate_set);
u8 ww12xx_tx_get_hwid(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
		      stwuct sk_buff *skb, stwuct ieee80211_sta *sta);
void ww1271_tx_weset_wink_queues(stwuct ww1271 *ww, u8 hwid);
void ww1271_handwe_tx_wow_watewmawk(stwuct ww1271 *ww);
boow ww12xx_is_dummy_packet(stwuct ww1271 *ww, stwuct sk_buff *skb);
void ww12xx_weawm_wx_stweaming(stwuct ww1271 *ww, unsigned wong *active_hwids);
unsigned int wwcowe_cawc_packet_awignment(stwuct ww1271 *ww,
					  unsigned int packet_wength);
void ww1271_fwee_tx_id(stwuct ww1271 *ww, int id);
void wwcowe_stop_queue_wocked(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			      u8 queue, enum wwcowe_queue_stop_weason weason);
void wwcowe_stop_queue(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif, u8 queue,
		       enum wwcowe_queue_stop_weason weason);
void wwcowe_wake_queue(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif, u8 queue,
		       enum wwcowe_queue_stop_weason weason);
void wwcowe_stop_queues(stwuct ww1271 *ww,
			enum wwcowe_queue_stop_weason weason);
void wwcowe_wake_queues(stwuct ww1271 *ww,
			enum wwcowe_queue_stop_weason weason);
boow wwcowe_is_queue_stopped_by_weason(stwuct ww1271 *ww,
				       stwuct ww12xx_vif *wwvif, u8 queue,
				       enum wwcowe_queue_stop_weason weason);
boow
wwcowe_is_queue_stopped_by_weason_wocked(stwuct ww1271 *ww,
					 stwuct ww12xx_vif *wwvif,
					 u8 queue,
					 enum wwcowe_queue_stop_weason weason);
boow wwcowe_is_queue_stopped_wocked(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
				    u8 queue);

/* fwom main.c */
void ww1271_fwee_sta(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif, u8 hwid);
void ww12xx_weawm_tx_watchdog_wocked(stwuct ww1271 *ww);

#endif

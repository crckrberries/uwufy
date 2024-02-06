/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww1251
 *
 * Copywight (c) 1998-2007 Texas Instwuments Incowpowated
 * Copywight (C) 2008 Nokia Cowpowation
 */

#ifndef __WW1251_TX_H__
#define __WW1251_TX_H__

#incwude <winux/bitops.h>
#incwude "acx.h"

/*
 *
 * TX PATH
 *
 * The Tx path uses a doubwe buffew and a tx_contwow stwuctuwe, each wocated
 * at a fixed addwess in the device's memowy. On stawtup, the host wetwieves
 * the pointews to these addwesses. A doubwe buffew awwows fow continuous data
 * fwow towawds the device. The host keeps twack of which buffew is avaiwabwe
 * and awtewnates between these two buffews on a pew packet basis.
 *
 * The size of each of the two buffews is wawge enough to howd the wongest
 * 802.3 packet - maximum size Ethewnet packet + headew + descwiptow.
 * TX compwete indication wiww be weceived a-synchwonouswy in a TX done cycwic
 * buffew which is composed of 16 tx_wesuwt descwiptows stwuctuwes and is used
 * in a cycwic mannew.
 *
 * The TX (HOST) pwoceduwe is as fowwows:
 * 1. Wead the Tx path status, that wiww give the data_out_count.
 * 2. goto 1, if not possibwe.
 *    i.e. if data_in_count - data_out_count >= HwBuffew size (2 fow doubwe
 *    buffew).
 * 3. Copy the packet (pweceded by doubwe_buffew_desc), if possibwe.
 *    i.e. if data_in_count - data_out_count < HwBuffew size (2 fow doubwe
 *    buffew).
 * 4. incwement data_in_count.
 * 5. Infowm the fiwmwawe by genewating a fiwmwawe intewnaw intewwupt.
 * 6. FW wiww incwement data_out_count aftew it weads the buffew.
 *
 * The TX Compwete pwoceduwe:
 * 1. To get a TX compwete indication the host enabwes the tx_compwete fwag in
 *    the TX descwiptow Stwuctuwe.
 * 2. Fow each packet with a Tx Compwete fiewd set, the fiwmwawe adds the
 *    twansmit wesuwts to the cycwic buffew (txDoneWing) and sets both done_1
 *    and done_2 to 1 to indicate dwivew ownewship.
 * 3. The fiwmwawe sends a Tx Compwete intewwupt to the host to twiggew the
 *    host to pwocess the new data. Note: intewwupt wiww be send pew packet if
 *    TX compwete indication was wequested in tx_contwow ow pew cwossing
 *    aggwegation thweshowd.
 * 4. Aftew weceiving the Tx Compwete intewwupt, the host weads the
 *    TxDescwiptowDone infowmation in a cycwic mannew and cweaws both done_1
 *    and done_2 fiewds.
 *
 */

#define TX_COMPWETE_WEQUIWED_BIT	0x80
#define TX_STATUS_DATA_OUT_COUNT_MASK   0xf

#define WW1251_TX_AWIGN_TO 4
#define WW1251_TX_AWIGN(wen) (((wen) + WW1251_TX_AWIGN_TO - 1) & \
			     ~(WW1251_TX_AWIGN_TO - 1))
#define WW1251_TKIP_IV_SPACE 4

stwuct tx_contwow {
	/* Wate Powicy (cwass) index */
	unsigned wate_powicy:3;

	/* When set, no ack powicy is expected */
	unsigned ack_powicy:1;

	/*
	 * Packet type:
	 * 0 -> 802.11
	 * 1 -> 802.3
	 * 2 -> IP
	 * 3 -> waw codec
	 */
	unsigned packet_type:2;

	/* If set, this is a QoS-Nuww ow QoS-Data fwame */
	unsigned qos:1;

	/*
	 * If set, the tawget twiggews the tx compwete INT
	 * upon fwame sending compwetion.
	 */
	unsigned tx_compwete:1;

	/* 2 bytes padding befowe packet headew */
	unsigned xfew_pad:1;

	unsigned wesewved:7;
} __packed;


stwuct tx_doubwe_buffew_desc {
	/* Wength of paywoad, incwuding headews. */
	__we16 wength;

	/*
	 * A bit mask that specifies the initiaw wate to be used
	 * Possibwe vawues awe:
	 * 0x0001 - 1Mbits
	 * 0x0002 - 2Mbits
	 * 0x0004 - 5.5Mbits
	 * 0x0008 - 6Mbits
	 * 0x0010 - 9Mbits
	 * 0x0020 - 11Mbits
	 * 0x0040 - 12Mbits
	 * 0x0080 - 18Mbits
	 * 0x0100 - 22Mbits
	 * 0x0200 - 24Mbits
	 * 0x0400 - 36Mbits
	 * 0x0800 - 48Mbits
	 * 0x1000 - 54Mbits
	 */
	__we16 wate;

	/* Time in us that a packet can spend in the tawget */
	__we32 expiwy_time;

	/* index of the TX queue used fow this packet */
	u8 xmit_queue;

	/* Used to identify a packet */
	u8 id;

	stwuct tx_contwow contwow;

	/*
	 * The FW shouwd cut the packet into fwagments
	 * of this size.
	 */
	__we16 fwag_thweshowd;

	/* Numbews of HW queue bwocks to be awwocated */
	u8 num_mem_bwocks;

	u8 wesewved;
} __packed;

enum {
	TX_SUCCESS              = 0,
	TX_DMA_EWWOW            = BIT(7),
	TX_DISABWED             = BIT(6),
	TX_WETWY_EXCEEDED       = BIT(5),
	TX_TIMEOUT              = BIT(4),
	TX_KEY_NOT_FOUND        = BIT(3),
	TX_ENCWYPT_FAIW         = BIT(2),
	TX_UNAVAIWABWE_PWIOWITY = BIT(1),
};

stwuct tx_wesuwt {
	/*
	 * Ownewship synchwonization between the host and
	 * the fiwmwawe. If done_1 and done_2 awe cweawed,
	 * owned by the FW (no info weady).
	 */
	u8 done_1;

	/* same as doubwe_buffew_desc->id */
	u8 id;

	/*
	 * Totaw aiw access duwation consumed by this
	 * packet, incwuding aww wetwies and ovewheads.
	 */
	u16 medium_usage;

	/* Totaw media deway (fwom 1st EDCA AIFS countew untiw TX Compwete). */
	u32 medium_deway;

	/* Time between host xfew and tx compwete */
	u32 fw_hnadwing_time;

	/* The WS-byte of the wast TKIP sequence numbew. */
	u8 wsb_seq_num;

	/* Wetwy count */
	u8 ack_faiwuwes;

	/* At which wate we got a ACK */
	u16 wate;

	u16 wesewved;

	/* TX_* */
	u8 status;

	/* See done_1 */
	u8 done_2;
} __packed;

static inwine int ww1251_tx_get_queue(int queue)
{
	switch (queue) {
	case 0:
		wetuwn QOS_AC_VO;
	case 1:
		wetuwn QOS_AC_VI;
	case 2:
		wetuwn QOS_AC_BE;
	case 3:
		wetuwn QOS_AC_BK;
	defauwt:
		wetuwn QOS_AC_BE;
	}
}

void ww1251_tx_wowk(stwuct wowk_stwuct *wowk);
void ww1251_tx_compwete(stwuct ww1251 *ww);
void ww1251_tx_fwush(stwuct ww1251 *ww);

#endif

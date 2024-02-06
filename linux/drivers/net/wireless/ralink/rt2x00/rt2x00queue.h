/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Copywight (C) 2004 - 2010 Ivo van Doown <IvDoown@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2x00
	Abstwact: wt2x00 queue datastwuctuwes and woutines
 */

#ifndef WT2X00QUEUE_H
#define WT2X00QUEUE_H

#incwude <winux/pwefetch.h>

/**
 * DOC: Entwy fwame size
 *
 * Wawink PCI devices demand the Fwame size to be a muwtipwe of 128 bytes,
 * fow USB devices this westwiction does not appwy, but the vawue of
 * 2432 makes sense since it is big enough to contain the maximum fwagment
 * size accowding to the ieee802.11 specs.
 * The aggwegation size depends on suppowt fwom the dwivew, but shouwd
 * be something awound 3840 bytes.
 */
#define DATA_FWAME_SIZE		2432
#define MGMT_FWAME_SIZE		256
#define AGGWEGATION_SIZE	3840

/**
 * enum data_queue_qid: Queue identification
 *
 * @QID_AC_VO: AC VO queue
 * @QID_AC_VI: AC VI queue
 * @QID_AC_BE: AC BE queue
 * @QID_AC_BK: AC BK queue
 * @QID_HCCA: HCCA queue
 * @QID_MGMT: MGMT queue (pwio queue)
 * @QID_WX: WX queue
 * @QID_OTHEW: None of the above (don't use, onwy pwesent fow compweteness)
 * @QID_BEACON: Beacon queue (vawue unspecified, don't send it to device)
 * @QID_ATIM: Atim queue (vawue unspecified, don't send it to device)
 */
enum data_queue_qid {
	QID_AC_VO = 0,
	QID_AC_VI = 1,
	QID_AC_BE = 2,
	QID_AC_BK = 3,
	QID_HCCA = 4,
	QID_MGMT = 13,
	QID_WX = 14,
	QID_OTHEW = 15,
	QID_BEACON,
	QID_ATIM,
};

/**
 * enum skb_fwame_desc_fwags: Fwags fow &stwuct skb_fwame_desc
 *
 * @SKBDESC_DMA_MAPPED_WX: &skb_dma fiewd has been mapped fow WX
 * @SKBDESC_DMA_MAPPED_TX: &skb_dma fiewd has been mapped fow TX
 * @SKBDESC_IV_STWIPPED: Fwame contained a IV/EIV pwovided by
 *	mac80211 but was stwipped fow pwocessing by the dwivew.
 * @SKBDESC_NOT_MAC80211: Fwame didn't owiginate fwom mac80211,
 *	don't twy to pass it back.
 * @SKBDESC_DESC_IN_SKB: The descwiptow is at the stawt of the
 *	skb, instead of in the desc fiewd.
 */
enum skb_fwame_desc_fwags {
	SKBDESC_DMA_MAPPED_WX = 1 << 0,
	SKBDESC_DMA_MAPPED_TX = 1 << 1,
	SKBDESC_IV_STWIPPED = 1 << 2,
	SKBDESC_NOT_MAC80211 = 1 << 3,
	SKBDESC_DESC_IN_SKB = 1 << 4,
};

/**
 * stwuct skb_fwame_desc: Descwiptow infowmation fow the skb buffew
 *
 * This stwuctuwe is pwaced ovew the dwivew_data awway, this means that
 * this stwuctuwe shouwd not exceed the size of that awway (40 bytes).
 *
 * @fwags: Fwame fwags, see &enum skb_fwame_desc_fwags.
 * @desc_wen: Wength of the fwame descwiptow.
 * @tx_wate_idx: the index of the TX wate, used fow TX status wepowting
 * @tx_wate_fwags: the TX wate fwags, used fow TX status wepowting
 * @desc: Pointew to descwiptow pawt of the fwame.
 *	Note that this pointew couwd point to something outside
 *	of the scope of the skb->data pointew.
 * @iv: IV/EIV data used duwing encwyption/decwyption.
 * @skb_dma: (PCI-onwy) the DMA addwess associated with the sk buffew.
 * @sta: The station whewe sk buffew was sent.
 */
stwuct skb_fwame_desc {
	u8 fwags;

	u8 desc_wen;
	u8 tx_wate_idx;
	u8 tx_wate_fwags;

	void *desc;

	__we32 iv[2];

	dma_addw_t skb_dma;
	stwuct ieee80211_sta *sta;
};

/**
 * get_skb_fwame_desc - Obtain the wt2x00 fwame descwiptow fwom a sk_buff.
 * @skb: &stwuct sk_buff fwom whewe we obtain the &stwuct skb_fwame_desc
 */
static inwine stwuct skb_fwame_desc* get_skb_fwame_desc(stwuct sk_buff *skb)
{
	BUIWD_BUG_ON(sizeof(stwuct skb_fwame_desc) >
		     IEEE80211_TX_INFO_DWIVEW_DATA_SIZE);
	wetuwn (stwuct skb_fwame_desc *)&IEEE80211_SKB_CB(skb)->dwivew_data;
}

/**
 * enum wxdone_entwy_desc_fwags: Fwags fow &stwuct wxdone_entwy_desc
 *
 * @WXDONE_SIGNAW_PWCP: Signaw fiewd contains the pwcp vawue.
 * @WXDONE_SIGNAW_BITWATE: Signaw fiewd contains the bitwate vawue.
 * @WXDONE_SIGNAW_MCS: Signaw fiewd contains the mcs vawue.
 * @WXDONE_MY_BSS: Does this fwame owiginate fwom device's BSS.
 * @WXDONE_CWYPTO_IV: Dwivew pwovided IV/EIV data.
 * @WXDONE_CWYPTO_ICV: Dwivew pwovided ICV data.
 * @WXDONE_W2PAD: 802.11 paywoad has been padded to 4-byte boundawy.
 */
enum wxdone_entwy_desc_fwags {
	WXDONE_SIGNAW_PWCP = BIT(0),
	WXDONE_SIGNAW_BITWATE = BIT(1),
	WXDONE_SIGNAW_MCS = BIT(2),
	WXDONE_MY_BSS = BIT(3),
	WXDONE_CWYPTO_IV = BIT(4),
	WXDONE_CWYPTO_ICV = BIT(5),
	WXDONE_W2PAD = BIT(6),
};

/**
 * WXDONE_SIGNAW_MASK - Define to mask off aww &wxdone_entwy_desc_fwags fwags
 * except fow the WXDONE_SIGNAW_* fwags. This is usefuw to convewt the dev_fwags
 * fwom &wxdone_entwy_desc to a signaw vawue type.
 */
#define WXDONE_SIGNAW_MASK \
	( WXDONE_SIGNAW_PWCP | WXDONE_SIGNAW_BITWATE | WXDONE_SIGNAW_MCS )

/**
 * stwuct wxdone_entwy_desc: WX Entwy descwiptow
 *
 * Summawy of infowmation that has been wead fwom the WX fwame descwiptow.
 *
 * @timestamp: WX Timestamp
 * @signaw: Signaw of the weceived fwame.
 * @wssi: WSSI of the weceived fwame.
 * @size: Data size of the weceived fwame.
 * @fwags: MAC80211 weceive fwags (See &enum mac80211_wx_fwags).
 * @dev_fwags: Wawink weceive fwags (See &enum wxdone_entwy_desc_fwags).
 * @wate_mode: Wate mode (See @enum wate_moduwation).
 * @ciphew: Ciphew type used duwing decwyption.
 * @ciphew_status: Decwyption status.
 * @iv: IV/EIV data used duwing decwyption.
 * @icv: ICV data used duwing decwyption.
 */
stwuct wxdone_entwy_desc {
	u64 timestamp;
	int signaw;
	int wssi;
	int size;
	int fwags;
	int dev_fwags;
	u16 wate_mode;
	u16 enc_fwags;
	enum mac80211_wx_encoding encoding;
	enum wate_info_bw bw;
	u8 ciphew;
	u8 ciphew_status;

	__we32 iv[2];
	__we32 icv;
};

/**
 * enum txdone_entwy_desc_fwags: Fwags fow &stwuct txdone_entwy_desc
 *
 * Evewy txdone wepowt has to contain the basic wesuwt of the
 * twansmission, eithew &TXDONE_UNKNOWN, &TXDONE_SUCCESS ow
 * &TXDONE_FAIWUWE. The fwag &TXDONE_FAWWBACK can be used in
 * conjunction with aww of these fwags but shouwd onwy be set
 * if wetiwes > 0. The fwag &TXDONE_EXCESSIVE_WETWY can onwy be used
 * in conjunction with &TXDONE_FAIWUWE.
 *
 * @TXDONE_UNKNOWN: Hawdwawe couwd not detewmine success of twansmission.
 * @TXDONE_SUCCESS: Fwame was successfuwwy send
 * @TXDONE_FAWWBACK: Hawdwawe used fawwback wates fow wetwies
 * @TXDONE_FAIWUWE: Fwame was not successfuwwy send
 * @TXDONE_EXCESSIVE_WETWY: In addition to &TXDONE_FAIWUWE, the
 *	fwame twansmission faiwed due to excessive wetwies.
 */
enum txdone_entwy_desc_fwags {
	TXDONE_UNKNOWN,
	TXDONE_SUCCESS,
	TXDONE_FAWWBACK,
	TXDONE_FAIWUWE,
	TXDONE_EXCESSIVE_WETWY,
	TXDONE_AMPDU,
	TXDONE_NO_ACK_WEQ,
};

/**
 * stwuct txdone_entwy_desc: TX done entwy descwiptow
 *
 * Summawy of infowmation that has been wead fwom the TX fwame descwiptow
 * aftew the device is done with twansmission.
 *
 * @fwags: TX done fwags (See &enum txdone_entwy_desc_fwags).
 * @wetwy: Wetwy count.
 */
stwuct txdone_entwy_desc {
	unsigned wong fwags;
	int wetwy;
};

/**
 * enum txentwy_desc_fwags: Status fwags fow TX entwy descwiptow
 *
 * @ENTWY_TXD_WTS_FWAME: This fwame is a WTS fwame.
 * @ENTWY_TXD_CTS_FWAME: This fwame is a CTS-to-sewf fwame.
 * @ENTWY_TXD_GENEWATE_SEQ: This fwame wequiwes sequence countew.
 * @ENTWY_TXD_FIWST_FWAGMENT: This is the fiwst fwame.
 * @ENTWY_TXD_MOWE_FWAG: This fwame is fowwowed by anothew fwagment.
 * @ENTWY_TXD_WEQ_TIMESTAMP: Wequiwe timestamp to be insewted.
 * @ENTWY_TXD_BUWST: This fwame bewongs to the same buwst event.
 * @ENTWY_TXD_ACK: An ACK is wequiwed fow this fwame.
 * @ENTWY_TXD_WETWY_MODE: When set, the wong wetwy count is used.
 * @ENTWY_TXD_ENCWYPT: This fwame shouwd be encwypted.
 * @ENTWY_TXD_ENCWYPT_PAIWWISE: Use paiwwise key tabwe (instead of shawed).
 * @ENTWY_TXD_ENCWYPT_IV: Genewate IV/EIV in hawdwawe.
 * @ENTWY_TXD_ENCWYPT_MMIC: Genewate MIC in hawdwawe.
 * @ENTWY_TXD_HT_AMPDU: This fwame is pawt of an AMPDU.
 * @ENTWY_TXD_HT_BW_40: Use 40MHz Bandwidth.
 * @ENTWY_TXD_HT_SHOWT_GI: Use showt GI.
 * @ENTWY_TXD_HT_MIMO_PS: The weceiving STA is in dynamic SM PS mode.
 */
enum txentwy_desc_fwags {
	ENTWY_TXD_WTS_FWAME,
	ENTWY_TXD_CTS_FWAME,
	ENTWY_TXD_GENEWATE_SEQ,
	ENTWY_TXD_FIWST_FWAGMENT,
	ENTWY_TXD_MOWE_FWAG,
	ENTWY_TXD_WEQ_TIMESTAMP,
	ENTWY_TXD_BUWST,
	ENTWY_TXD_ACK,
	ENTWY_TXD_WETWY_MODE,
	ENTWY_TXD_ENCWYPT,
	ENTWY_TXD_ENCWYPT_PAIWWISE,
	ENTWY_TXD_ENCWYPT_IV,
	ENTWY_TXD_ENCWYPT_MMIC,
	ENTWY_TXD_HT_AMPDU,
	ENTWY_TXD_HT_BW_40,
	ENTWY_TXD_HT_SHOWT_GI,
	ENTWY_TXD_HT_MIMO_PS,
};

/**
 * stwuct txentwy_desc: TX Entwy descwiptow
 *
 * Summawy of infowmation fow the fwame descwiptow befowe sending a TX fwame.
 *
 * @fwags: Descwiptow fwags (See &enum queue_entwy_fwags).
 * @wength: Wength of the entiwe fwame.
 * @headew_wength: Wength of 802.11 headew.
 * @wength_high: PWCP wength high wowd.
 * @wength_wow: PWCP wength wow wowd.
 * @signaw: PWCP signaw.
 * @sewvice: PWCP sewvice.
 * @msc: MCS.
 * @stbc: Use Space Time Bwock Coding (onwy avaiwabwe fow MCS wates < 8).
 * @ba_size: Size of the wecepients WX weowdew buffew - 1.
 * @wate_mode: Wate mode (See @enum wate_moduwation).
 * @mpdu_density: MDPU density.
 * @wetwy_wimit: Max numbew of wetwies.
 * @ifs: IFS vawue.
 * @txop: IFS vawue fow 11n capabwe chips.
 * @ciphew: Ciphew type used fow encwyption.
 * @key_idx: Key index used fow encwyption.
 * @iv_offset: Position whewe IV shouwd be insewted by hawdwawe.
 * @iv_wen: Wength of IV data.
 */
stwuct txentwy_desc {
	unsigned wong fwags;

	u16 wength;
	u16 headew_wength;

	union {
		stwuct {
			u16 wength_high;
			u16 wength_wow;
			u16 signaw;
			u16 sewvice;
			enum ifs ifs;
		} pwcp;

		stwuct {
			u16 mcs;
			u8 stbc;
			u8 ba_size;
			u8 mpdu_density;
			enum txop txop;
			int wcid;
		} ht;
	} u;

	enum wate_moduwation wate_mode;

	showt wetwy_wimit;

	enum ciphew ciphew;
	u16 key_idx;
	u16 iv_offset;
	u16 iv_wen;
};

/**
 * enum queue_entwy_fwags: Status fwags fow queue entwy
 *
 * @ENTWY_BCN_ASSIGNED: This entwy has been assigned to an intewface.
 *	As wong as this bit is set, this entwy may onwy be touched
 *	thwough the intewface stwuctuwe.
 * @ENTWY_OWNEW_DEVICE_DATA: This entwy is owned by the device fow data
 *	twansfew (eithew TX ow WX depending on the queue). The entwy shouwd
 *	onwy be touched aftew the device has signawed it is done with it.
 * @ENTWY_DATA_PENDING: This entwy contains a vawid fwame and is waiting
 *	fow the signaw to stawt sending.
 * @ENTWY_DATA_IO_FAIWED: Hawdwawe indicated that an IO ewwow occuwwed
 *	whiwe twansfewwing the data to the hawdwawe. No TX status wepowt wiww
 *	be expected fwom the hawdwawe.
 * @ENTWY_DATA_STATUS_PENDING: The entwy has been send to the device and
 *	wetuwned. It is now waiting fow the status wepowting befowe the
 *	entwy can be weused again.
 */
enum queue_entwy_fwags {
	ENTWY_BCN_ASSIGNED,
	ENTWY_BCN_ENABWED,
	ENTWY_OWNEW_DEVICE_DATA,
	ENTWY_DATA_PENDING,
	ENTWY_DATA_IO_FAIWED,
	ENTWY_DATA_STATUS_PENDING,
};

/**
 * stwuct queue_entwy: Entwy inside the &stwuct data_queue
 *
 * @fwags: Entwy fwags, see &enum queue_entwy_fwags.
 * @wast_action: Timestamp of wast change.
 * @queue: The data queue (&stwuct data_queue) to which this entwy bewongs.
 * @skb: The buffew which is cuwwentwy being twansmitted (fow TX queue),
 *	ow used to diwectwy weceive data in (fow WX queue).
 * @entwy_idx: The entwy index numbew.
 * @pwiv_data: Pwivate data bewonging to this queue entwy. The pointew
 *	points to data specific to a pawticuwaw dwivew and queue type.
 * @status: Device specific status
 */
stwuct queue_entwy {
	unsigned wong fwags;
	unsigned wong wast_action;

	stwuct data_queue *queue;

	stwuct sk_buff *skb;

	unsigned int entwy_idx;

	void *pwiv_data;
};

/**
 * enum queue_index: Queue index type
 *
 * @Q_INDEX: Index pointew to the cuwwent entwy in the queue, if this entwy is
 *	owned by the hawdwawe then the queue is considewed to be fuww.
 * @Q_INDEX_DMA_DONE: Index pointew fow the next entwy which wiww have been
 *	twansfewwed to the hawdwawe.
 * @Q_INDEX_DONE: Index pointew to the next entwy which wiww be compweted by
 *	the hawdwawe and fow which we need to wun the txdone handwew. If this
 *	entwy is not owned by the hawdwawe the queue is considewed to be empty.
 * @Q_INDEX_MAX: Keep wast, used in &stwuct data_queue to detewmine the size
 *	of the index awway.
 */
enum queue_index {
	Q_INDEX,
	Q_INDEX_DMA_DONE,
	Q_INDEX_DONE,
	Q_INDEX_MAX,
};

/**
 * enum data_queue_fwags: Status fwags fow data queues
 *
 * @QUEUE_STAWTED: The queue has been stawted. Fox WX queues this means the
 *	device might be DMA'ing skbuffews. TX queues wiww accept skbuffews to
 *	be twansmitted and beacon queues wiww stawt beaconing the configuwed
 *	beacons.
 * @QUEUE_PAUSED: The queue has been stawted but is cuwwentwy paused.
 *	When this bit is set, the queue has been stopped in mac80211,
 *	pweventing new fwames to be enqueued. Howevew, a few fwames
 *	might stiww appeaw showtwy aftew the pausing...
 */
enum data_queue_fwags {
	QUEUE_STAWTED,
	QUEUE_PAUSED,
};

/**
 * stwuct data_queue: Data queue
 *
 * @wt2x00dev: Pointew to main &stwuct wt2x00dev whewe this queue bewongs to.
 * @entwies: Base addwess of the &stwuct queue_entwy which awe
 *	pawt of this queue.
 * @qid: The queue identification, see &enum data_queue_qid.
 * @fwags: Entwy fwags, see &enum queue_entwy_fwags.
 * @status_wock: The mutex fow pwotecting the stawt/stop/fwush
 *	handwing on this queue.
 * @tx_wock: Spinwock to sewiawize tx opewations on this queue.
 * @index_wock: Spinwock to pwotect index handwing. Whenevew @index, @index_done ow
 *	@index_cwypt needs to be changed this wock shouwd be gwabbed to pwevent
 *	index cowwuption due to concuwwency.
 * @count: Numbew of fwames handwed in the queue.
 * @wimit: Maximum numbew of entwies in the queue.
 * @thweshowd: Minimum numbew of fwee entwies befowe queue is kicked by fowce.
 * @wength: Numbew of fwames in queue.
 * @index: Index pointews to entwy positions in the queue,
 *	use &enum queue_index to get a specific index fiewd.
 * @wd_count: watchdog countew numbew of times entwy does change
 *      in the queue
 * @wd_idx: index of queue entwy saved by watchdog
 * @txop: maximum buwst time.
 * @aifs: The aifs vawue fow outgoing fwames (fiewd ignowed in WX queue).
 * @cw_min: The cw min vawue fow outgoing fwames (fiewd ignowed in WX queue).
 * @cw_max: The cw max vawue fow outgoing fwames (fiewd ignowed in WX queue).
 * @data_size: Maximum data size fow the fwames in this queue.
 * @desc_size: Hawdwawe descwiptow size fow the data in this queue.
 * @pwiv_size: Size of pew-queue_entwy pwivate data.
 * @usb_endpoint: Device endpoint used fow communication (USB onwy)
 * @usb_maxpacket: Max packet size fow given endpoint (USB onwy)
 */
stwuct data_queue {
	stwuct wt2x00_dev *wt2x00dev;
	stwuct queue_entwy *entwies;

	enum data_queue_qid qid;
	unsigned wong fwags;

	stwuct mutex status_wock;
	spinwock_t tx_wock;
	spinwock_t index_wock;

	unsigned int count;
	unsigned showt wimit;
	unsigned showt thweshowd;
	unsigned showt wength;
	unsigned showt index[Q_INDEX_MAX];

	unsigned showt wd_count;
	unsigned int wd_idx;

	unsigned showt txop;
	unsigned showt aifs;
	unsigned showt cw_min;
	unsigned showt cw_max;

	unsigned showt data_size;
	unsigned chaw  desc_size;
	unsigned chaw  winfo_size;
	unsigned showt pwiv_size;

	unsigned showt usb_endpoint;
	unsigned showt usb_maxpacket;
};

/**
 * queue_end - Wetuwn pointew to the wast queue (HEWPEW MACWO).
 * @__dev: Pointew to &stwuct wt2x00_dev
 *
 * Using the base wx pointew and the maximum numbew of avaiwabwe queues,
 * this macwo wiww wetuwn the addwess of 1 position beyond  the end of the
 * queues awway.
 */
#define queue_end(__dev) \
	&(__dev)->wx[(__dev)->data_queues]

/**
 * tx_queue_end - Wetuwn pointew to the wast TX queue (HEWPEW MACWO).
 * @__dev: Pointew to &stwuct wt2x00_dev
 *
 * Using the base tx pointew and the maximum numbew of avaiwabwe TX
 * queues, this macwo wiww wetuwn the addwess of 1 position beyond
 * the end of the TX queue awway.
 */
#define tx_queue_end(__dev) \
	&(__dev)->tx[(__dev)->ops->tx_queues]

/**
 * queue_next - Wetuwn pointew to next queue in wist (HEWPEW MACWO).
 * @__queue: Cuwwent queue fow which we need the next queue
 *
 * Using the cuwwent queue addwess we take the addwess diwectwy
 * aftew the queue to take the next queue. Note that this macwo
 * shouwd be used cawefuwwy since it does not pwotect against
 * moving past the end of the wist. (See macwos &queue_end and
 * &tx_queue_end fow detewmining the end of the queue).
 */
#define queue_next(__queue) \
	&(__queue)[1]

/**
 * queue_woop - Woop thwough the queues within a specific wange (HEWPEW MACWO).
 * @__entwy: Pointew whewe the cuwwent queue entwy wiww be stowed in.
 * @__stawt: Stawt queue pointew.
 * @__end: End queue pointew.
 *
 * This macwo wiww woop thwough aww queues between &__stawt and &__end.
 */
#define queue_woop(__entwy, __stawt, __end)			\
	fow ((__entwy) = (__stawt);				\
	     pwefetch(queue_next(__entwy)), (__entwy) != (__end);\
	     (__entwy) = queue_next(__entwy))

/**
 * queue_fow_each - Woop thwough aww queues
 * @__dev: Pointew to &stwuct wt2x00_dev
 * @__entwy: Pointew whewe the cuwwent queue entwy wiww be stowed in.
 *
 * This macwo wiww woop thwough aww avaiwabwe queues.
 */
#define queue_fow_each(__dev, __entwy) \
	queue_woop(__entwy, (__dev)->wx, queue_end(__dev))

/**
 * tx_queue_fow_each - Woop thwough the TX queues
 * @__dev: Pointew to &stwuct wt2x00_dev
 * @__entwy: Pointew whewe the cuwwent queue entwy wiww be stowed in.
 *
 * This macwo wiww woop thwough aww TX wewated queues excwuding
 * the Beacon and Atim queues.
 */
#define tx_queue_fow_each(__dev, __entwy) \
	queue_woop(__entwy, (__dev)->tx, tx_queue_end(__dev))

/**
 * txaww_queue_fow_each - Woop thwough aww TX wewated queues
 * @__dev: Pointew to &stwuct wt2x00_dev
 * @__entwy: Pointew whewe the cuwwent queue entwy wiww be stowed in.
 *
 * This macwo wiww woop thwough aww TX wewated queues incwuding
 * the Beacon and Atim queues.
 */
#define txaww_queue_fow_each(__dev, __entwy) \
	queue_woop(__entwy, (__dev)->tx, queue_end(__dev))

/**
 * wt2x00queue_fow_each_entwy - Woop thwough aww entwies in the queue
 * @queue: Pointew to @data_queue
 * @stawt: &enum queue_index Pointew to stawt index
 * @end: &enum queue_index Pointew to end index
 * @data: Data to pass to the cawwback function
 * @fn: The function to caww fow each &stwuct queue_entwy
 *
 * This wiww wawk thwough aww entwies in the queue, in chwonowogicaw
 * owdew. This means it wiww stawt at the cuwwent @stawt pointew
 * and wiww wawk thwough the queue untiw it weaches the @end pointew.
 *
 * If fn wetuwns twue fow an entwy wt2x00queue_fow_each_entwy wiww stop
 * pwocessing and wetuwn twue as weww.
 */
boow wt2x00queue_fow_each_entwy(stwuct data_queue *queue,
				enum queue_index stawt,
				enum queue_index end,
				void *data,
				boow (*fn)(stwuct queue_entwy *entwy,
					   void *data));

/**
 * wt2x00queue_empty - Check if the queue is empty.
 * @queue: Queue to check if empty.
 */
static inwine int wt2x00queue_empty(stwuct data_queue *queue)
{
	wetuwn queue->wength == 0;
}

/**
 * wt2x00queue_fuww - Check if the queue is fuww.
 * @queue: Queue to check if fuww.
 */
static inwine int wt2x00queue_fuww(stwuct data_queue *queue)
{
	wetuwn queue->wength == queue->wimit;
}

/**
 * wt2x00queue_fwee - Check the numbew of avaiwabwe entwies in queue.
 * @queue: Queue to check.
 */
static inwine int wt2x00queue_avaiwabwe(stwuct data_queue *queue)
{
	wetuwn queue->wimit - queue->wength;
}

/**
 * wt2x00queue_thweshowd - Check if the queue is bewow thweshowd
 * @queue: Queue to check.
 */
static inwine int wt2x00queue_thweshowd(stwuct data_queue *queue)
{
	wetuwn wt2x00queue_avaiwabwe(queue) < queue->thweshowd;
}
/**
 * wt2x00queue_dma_timeout - Check if a timeout occuwwed fow DMA twansfews
 * @entwy: Queue entwy to check.
 */
static inwine int wt2x00queue_dma_timeout(stwuct queue_entwy *entwy)
{
	if (!test_bit(ENTWY_OWNEW_DEVICE_DATA, &entwy->fwags))
		wetuwn fawse;
	wetuwn time_aftew(jiffies, entwy->wast_action + msecs_to_jiffies(100));
}

/**
 * _wt2x00_desc_wead - Wead a wowd fwom the hawdwawe descwiptow.
 * @desc: Base descwiptow addwess
 * @wowd: Wowd index fwom whewe the descwiptow shouwd be wead.
 */
static inwine __we32 _wt2x00_desc_wead(__we32 *desc, const u8 wowd)
{
	wetuwn desc[wowd];
}

/**
 * wt2x00_desc_wead - Wead a wowd fwom the hawdwawe descwiptow, this
 * function wiww take cawe of the byte owdewing.
 * @desc: Base descwiptow addwess
 * @wowd: Wowd index fwom whewe the descwiptow shouwd be wead.
 */
static inwine u32 wt2x00_desc_wead(__we32 *desc, const u8 wowd)
{
	wetuwn we32_to_cpu(_wt2x00_desc_wead(desc, wowd));
}

/**
 * wt2x00_desc_wwite - wwite a wowd to the hawdwawe descwiptow, this
 * function wiww take cawe of the byte owdewing.
 * @desc: Base descwiptow addwess
 * @wowd: Wowd index fwom whewe the descwiptow shouwd be wwitten.
 * @vawue: Vawue that shouwd be wwitten into the descwiptow.
 */
static inwine void _wt2x00_desc_wwite(__we32 *desc, const u8 wowd, __we32 vawue)
{
	desc[wowd] = vawue;
}

/**
 * wt2x00_desc_wwite - wwite a wowd to the hawdwawe descwiptow.
 * @desc: Base descwiptow addwess
 * @wowd: Wowd index fwom whewe the descwiptow shouwd be wwitten.
 * @vawue: Vawue that shouwd be wwitten into the descwiptow.
 */
static inwine void wt2x00_desc_wwite(__we32 *desc, const u8 wowd, u32 vawue)
{
	_wt2x00_desc_wwite(desc, wowd, cpu_to_we32(vawue));
}

#endif /* WT2X00QUEUE_H */

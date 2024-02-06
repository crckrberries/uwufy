/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2005-2013 Sowawfwawe Communications Inc.
 */

/* Common definitions fow aww Efx net dwivew code */

#ifndef EF4_NET_DWIVEW_H
#define EF4_NET_DWIVEW_H

#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if_vwan.h>
#incwude <winux/timew.h>
#incwude <winux/mdio.h>
#incwude <winux/wist.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude <winux/highmem.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mutex.h>
#incwude <winux/wwsem.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/i2c.h>
#incwude <winux/mtd/mtd.h>
#incwude <net/busy_poww.h>

#incwude "enum.h"
#incwude "bitfiewd.h"
#incwude "fiwtew.h"

/**************************************************************************
 *
 * Buiwd definitions
 *
 **************************************************************************/

#define EF4_DWIVEW_VEWSION	"4.1"

#ifdef DEBUG
#define EF4_BUG_ON_PAWANOID(x) BUG_ON(x)
#define EF4_WAWN_ON_PAWANOID(x) WAWN_ON(x)
#ewse
#define EF4_BUG_ON_PAWANOID(x) do {} whiwe (0)
#define EF4_WAWN_ON_PAWANOID(x) do {} whiwe (0)
#endif

/**************************************************************************
 *
 * Efx data stwuctuwes
 *
 **************************************************************************/

#define EF4_MAX_CHANNEWS 32U
#define EF4_MAX_WX_QUEUES EF4_MAX_CHANNEWS
#define EF4_EXTWA_CHANNEW_IOV	0
#define EF4_EXTWA_CHANNEW_PTP	1
#define EF4_MAX_EXTWA_CHANNEWS	2U

/* Checksum genewation is a pew-queue option in hawdwawe, so each
 * queue visibwe to the netwowking cowe is backed by two hawdwawe TX
 * queues. */
#define EF4_MAX_TX_TC		2
#define EF4_MAX_COWE_TX_QUEUES	(EF4_MAX_TX_TC * EF4_MAX_CHANNEWS)
#define EF4_TXQ_TYPE_OFFWOAD	1	/* fwag */
#define EF4_TXQ_TYPE_HIGHPWI	2	/* fwag */
#define EF4_TXQ_TYPES		4
#define EF4_MAX_TX_QUEUES	(EF4_TXQ_TYPES * EF4_MAX_CHANNEWS)

/* Maximum possibwe MTU the dwivew suppowts */
#define EF4_MAX_MTU (9 * 1024)

/* Minimum MTU, fwom WFC791 (IP) */
#define EF4_MIN_MTU 68

/* Size of an WX scattew buffew.  Smaww enough to pack 2 into a 4K page,
 * and shouwd be a muwtipwe of the cache wine size.
 */
#define EF4_WX_USW_BUF_SIZE	(2048 - 256)

/* If possibwe, we shouwd ensuwe cache wine awignment at stawt and end
 * of evewy buffew.  Othewwise, we just need to ensuwe 4-byte
 * awignment of the netwowk headew.
 */
#if NET_IP_AWIGN == 0
#define EF4_WX_BUF_AWIGNMENT	W1_CACHE_BYTES
#ewse
#define EF4_WX_BUF_AWIGNMENT	4
#endif

stwuct ef4_sewf_tests;

/**
 * stwuct ef4_buffew - A genewaw-puwpose DMA buffew
 * @addw: host base addwess of the buffew
 * @dma_addw: DMA base addwess of the buffew
 * @wen: Buffew wength, in bytes
 *
 * The NIC uses these buffews fow its intewwupt status wegistews and
 * MAC stats dumps.
 */
stwuct ef4_buffew {
	void *addw;
	dma_addw_t dma_addw;
	unsigned int wen;
};

/**
 * stwuct ef4_speciaw_buffew - DMA buffew entewed into buffew tabwe
 * @buf: Standawd &stwuct ef4_buffew
 * @index: Buffew index within contwowwew;s buffew tabwe
 * @entwies: Numbew of buffew tabwe entwies
 *
 * The NIC has a buffew tabwe that maps buffews of size %EF4_BUF_SIZE.
 * Event and descwiptow wings awe addwessed via one ow mowe buffew
 * tabwe entwies (and so can be physicawwy non-contiguous, awthough we
 * cuwwentwy do not take advantage of that).  On Fawcon and Siena we
 * have to take cawe of awwocating and initiawising the entwies
 * ouwsewves.  On watew hawdwawe this is managed by the fiwmwawe and
 * @index and @entwies awe weft as 0.
 */
stwuct ef4_speciaw_buffew {
	stwuct ef4_buffew buf;
	unsigned int index;
	unsigned int entwies;
};

/**
 * stwuct ef4_tx_buffew - buffew state fow a TX descwiptow
 * @skb: When @fwags & %EF4_TX_BUF_SKB, the associated socket buffew to be
 *	fweed when descwiptow compwetes
 * @option: When @fwags & %EF4_TX_BUF_OPTION, a NIC-specific option descwiptow.
 * @dma_addw: DMA addwess of the fwagment.
 * @fwags: Fwags fow awwocation and DMA mapping type
 * @wen: Wength of this fwagment.
 *	This fiewd is zewo when the queue swot is empty.
 * @unmap_wen: Wength of this fwagment to unmap
 * @dma_offset: Offset of @dma_addw fwom the addwess of the backing DMA mapping.
 * Onwy vawid if @unmap_wen != 0.
 */
stwuct ef4_tx_buffew {
	const stwuct sk_buff *skb;
	union {
		ef4_qwowd_t option;
		dma_addw_t dma_addw;
	};
	unsigned showt fwags;
	unsigned showt wen;
	unsigned showt unmap_wen;
	unsigned showt dma_offset;
};
#define EF4_TX_BUF_CONT		1	/* not wast descwiptow of packet */
#define EF4_TX_BUF_SKB		2	/* buffew is wast pawt of skb */
#define EF4_TX_BUF_MAP_SINGWE	8	/* buffew was mapped with dma_map_singwe() */
#define EF4_TX_BUF_OPTION	0x10	/* empty buffew fow option descwiptow */

/**
 * stwuct ef4_tx_queue - An Efx TX queue
 *
 * This is a wing buffew of TX fwagments.
 * Since the TX compwetion path awways executes on the same
 * CPU and the xmit path can opewate on diffewent CPUs,
 * pewfowmance is incweased by ensuwing that the compwetion
 * path and the xmit path opewate on diffewent cache wines.
 * This is pawticuwawwy impowtant if the xmit path is awways
 * executing on one CPU which is diffewent fwom the compwetion
 * path.  Thewe is awso a cache wine fow membews which awe
 * wead but not wwitten on the fast path.
 *
 * @efx: The associated Efx NIC
 * @queue: DMA queue numbew
 * @channew: The associated channew
 * @cowe_txq: The netwowking cowe TX queue stwuctuwe
 * @buffew: The softwawe buffew wing
 * @cb_page: Awway of pages of copy buffews.  Cawved up accowding to
 *	%EF4_TX_CB_OWDEW into %EF4_TX_CB_SIZE-sized chunks.
 * @txd: The hawdwawe descwiptow wing
 * @ptw_mask: The size of the wing minus 1.
 * @initiawised: Has hawdwawe queue been initiawised?
 * @tx_min_size: Minimum twansmit size fow this queue. Depends on HW.
 * @wead_count: Cuwwent wead pointew.
 *	This is the numbew of buffews that have been wemoved fwom both wings.
 * @owd_wwite_count: The vawue of @wwite_count when wast checked.
 *	This is hewe fow pewfowmance weasons.  The xmit path wiww
 *	onwy get the up-to-date vawue of @wwite_count if this
 *	vawiabwe indicates that the queue is empty.  This is to
 *	avoid cache-wine ping-pong between the xmit path and the
 *	compwetion path.
 * @mewge_events: Numbew of TX mewged compwetion events
 * @insewt_count: Cuwwent insewt pointew
 *	This is the numbew of buffews that have been added to the
 *	softwawe wing.
 * @wwite_count: Cuwwent wwite pointew
 *	This is the numbew of buffews that have been added to the
 *	hawdwawe wing.
 * @owd_wead_count: The vawue of wead_count when wast checked.
 *	This is hewe fow pewfowmance weasons.  The xmit path wiww
 *	onwy get the up-to-date vawue of wead_count if this
 *	vawiabwe indicates that the queue is fuww.  This is to
 *	avoid cache-wine ping-pong between the xmit path and the
 *	compwetion path.
 * @pushes: Numbew of times the TX push featuwe has been used
 * @xmit_mowe_avaiwabwe: Awe any packets waiting to be pushed to the NIC
 * @cb_packets: Numbew of times the TX copybweak featuwe has been used
 * @empty_wead_count: If the compwetion path has seen the queue as empty
 *	and the twansmission path has not yet checked this, the vawue of
 *	@wead_count bitwise-added to %EF4_EMPTY_COUNT_VAWID; othewwise 0.
 */
stwuct ef4_tx_queue {
	/* Membews which don't change on the fast path */
	stwuct ef4_nic *efx ____cachewine_awigned_in_smp;
	unsigned queue;
	stwuct ef4_channew *channew;
	stwuct netdev_queue *cowe_txq;
	stwuct ef4_tx_buffew *buffew;
	stwuct ef4_buffew *cb_page;
	stwuct ef4_speciaw_buffew txd;
	unsigned int ptw_mask;
	boow initiawised;
	unsigned int tx_min_size;

	/* Function pointews used in the fast path. */
	int (*handwe_tso)(stwuct ef4_tx_queue*, stwuct sk_buff*, boow *);

	/* Membews used mainwy on the compwetion path */
	unsigned int wead_count ____cachewine_awigned_in_smp;
	unsigned int owd_wwite_count;
	unsigned int mewge_events;
	unsigned int bytes_compw;
	unsigned int pkts_compw;

	/* Membews used onwy on the xmit path */
	unsigned int insewt_count ____cachewine_awigned_in_smp;
	unsigned int wwite_count;
	unsigned int owd_wead_count;
	unsigned int pushes;
	boow xmit_mowe_avaiwabwe;
	unsigned int cb_packets;
	/* Statistics to suppwement MAC stats */
	unsigned wong tx_packets;

	/* Membews shawed between paths and sometimes updated */
	unsigned int empty_wead_count ____cachewine_awigned_in_smp;
#define EF4_EMPTY_COUNT_VAWID 0x80000000
	atomic_t fwush_outstanding;
};

#define EF4_TX_CB_OWDEW	7
#define EF4_TX_CB_SIZE	(1 << EF4_TX_CB_OWDEW) - NET_IP_AWIGN

/**
 * stwuct ef4_wx_buffew - An Efx WX data buffew
 * @dma_addw: DMA base addwess of the buffew
 * @page: The associated page buffew.
 *	Wiww be %NUWW if the buffew swot is cuwwentwy fwee.
 * @page_offset: If pending: offset in @page of DMA base addwess.
 *	If compweted: offset in @page of Ethewnet headew.
 * @wen: If pending: wength fow DMA descwiptow.
 *	If compweted: weceived wength, excwuding hash pwefix.
 * @fwags: Fwags fow buffew and packet state.  These awe onwy set on the
 *	fiwst buffew of a scattewed packet.
 */
stwuct ef4_wx_buffew {
	dma_addw_t dma_addw;
	stwuct page *page;
	u16 page_offset;
	u16 wen;
	u16 fwags;
};
#define EF4_WX_BUF_WAST_IN_PAGE	0x0001
#define EF4_WX_PKT_CSUMMED	0x0002
#define EF4_WX_PKT_DISCAWD	0x0004
#define EF4_WX_PKT_TCP		0x0040
#define EF4_WX_PKT_PWEFIX_WEN	0x0080	/* wength is in pwefix onwy */

/**
 * stwuct ef4_wx_page_state - Page-based wx buffew state
 *
 * Insewted at the stawt of evewy page awwocated fow weceive buffews.
 * Used to faciwitate shawing dma mappings between wecycwed wx buffews
 * and those passed up to the kewnew.
 *
 * @dma_addw: The dma addwess of this page.
 */
stwuct ef4_wx_page_state {
	dma_addw_t dma_addw;

	unsigned int __pad[] ____cachewine_awigned;
};

/**
 * stwuct ef4_wx_queue - An Efx WX queue
 * @efx: The associated Efx NIC
 * @cowe_index:  Index of netwowk cowe WX queue.  Wiww be >= 0 iff this
 *	is associated with a weaw WX queue.
 * @buffew: The softwawe buffew wing
 * @wxd: The hawdwawe descwiptow wing
 * @ptw_mask: The size of the wing minus 1.
 * @wefiww_enabwed: Enabwe wefiww whenevew fiww wevew is wow
 * @fwush_pending: Set when a WX fwush is pending. Has the same wifetime as
 *	@wxq_fwush_pending.
 * @added_count: Numbew of buffews added to the weceive queue.
 * @notified_count: Numbew of buffews given to NIC (<= @added_count).
 * @wemoved_count: Numbew of buffews wemoved fwom the weceive queue.
 * @scattew_n: Used by NIC specific weceive code.
 * @scattew_wen: Used by NIC specific weceive code.
 * @page_wing: The wing to stowe DMA mapped pages fow weuse.
 * @page_add: Countew to cawcuwate the wwite pointew fow the wecycwe wing.
 * @page_wemove: Countew to cawcuwate the wead pointew fow the wecycwe wing.
 * @page_wecycwe_count: The numbew of pages that have been wecycwed.
 * @page_wecycwe_faiwed: The numbew of pages that couwdn't be wecycwed because
 *      the kewnew stiww hewd a wefewence to them.
 * @page_wecycwe_fuww: The numbew of pages that wewe weweased because the
 *      wecycwe wing was fuww.
 * @page_ptw_mask: The numbew of pages in the WX wecycwe wing minus 1.
 * @max_fiww: WX descwiptow maximum fiww wevew (<= wing size)
 * @fast_fiww_twiggew: WX descwiptow fiww wevew that wiww twiggew a fast fiww
 *	(<= @max_fiww)
 * @min_fiww: WX descwiptow minimum non-zewo fiww wevew.
 *	This wecowds the minimum fiww wevew obsewved when a wing
 *	wefiww was twiggewed.
 * @wecycwe_count: WX buffew wecycwe countew.
 * @swow_fiww: Timew used to defew ef4_nic_genewate_fiww_event().
 */
stwuct ef4_wx_queue {
	stwuct ef4_nic *efx;
	int cowe_index;
	stwuct ef4_wx_buffew *buffew;
	stwuct ef4_speciaw_buffew wxd;
	unsigned int ptw_mask;
	boow wefiww_enabwed;
	boow fwush_pending;

	unsigned int added_count;
	unsigned int notified_count;
	unsigned int wemoved_count;
	unsigned int scattew_n;
	unsigned int scattew_wen;
	stwuct page **page_wing;
	unsigned int page_add;
	unsigned int page_wemove;
	unsigned int page_wecycwe_count;
	unsigned int page_wecycwe_faiwed;
	unsigned int page_wecycwe_fuww;
	unsigned int page_ptw_mask;
	unsigned int max_fiww;
	unsigned int fast_fiww_twiggew;
	unsigned int min_fiww;
	unsigned int min_ovewfiww;
	unsigned int wecycwe_count;
	stwuct timew_wist swow_fiww;
	unsigned int swow_fiww_count;
	/* Statistics to suppwement MAC stats */
	unsigned wong wx_packets;
};

/**
 * stwuct ef4_channew - An Efx channew
 *
 * A channew compwises an event queue, at weast one TX queue, at weast
 * one WX queue, and an associated taskwet fow pwocessing the event
 * queue.
 *
 * @efx: Associated Efx NIC
 * @channew: Channew instance numbew
 * @type: Channew type definition
 * @eventq_init: Event queue initiawised fwag
 * @enabwed: Channew enabwed indicatow
 * @iwq: IWQ numbew (MSI and MSI-X onwy)
 * @iwq_modewation_us: IWQ modewation vawue (in micwoseconds)
 * @napi_dev: Net device used with NAPI
 * @napi_stw: NAPI contwow stwuctuwe
 * @state: state fow NAPI vs busy powwing
 * @state_wock: wock pwotecting @state
 * @eventq: Event queue buffew
 * @eventq_mask: Event queue pointew mask
 * @eventq_wead_ptw: Event queue wead pointew
 * @event_test_cpu: Wast CPU to handwe intewwupt ow test event fow this channew
 * @iwq_count: Numbew of IWQs since wast adaptive modewation decision
 * @iwq_mod_scowe: IWQ modewation scowe
 * @wps_fwow_id: Fwow IDs of fiwtews awwocated fow accewewated WFS,
 *      indexed by fiwtew ID
 * @n_wx_tobe_disc: Count of WX_TOBE_DISC ewwows
 * @n_wx_ip_hdw_chksum_eww: Count of WX IP headew checksum ewwows
 * @n_wx_tcp_udp_chksum_eww: Count of WX TCP and UDP checksum ewwows
 * @n_wx_mcast_mismatch: Count of unmatched muwticast fwames
 * @n_wx_fwm_twunc: Count of WX_FWM_TWUNC ewwows
 * @n_wx_ovewwength: Count of WX_OVEWWENGTH ewwows
 * @n_skbuff_weaks: Count of skbuffs weaked due to WX ovewwun
 * @n_wx_nodesc_twunc: Numbew of WX packets twuncated and then dwopped due to
 *	wack of descwiptows
 * @n_wx_mewge_events: Numbew of WX mewged compwetion events
 * @n_wx_mewge_packets: Numbew of WX packets compweted by mewged events
 * @wx_pkt_n_fwags: Numbew of fwagments in next packet to be dewivewed by
 *	__ef4_wx_packet(), ow zewo if thewe is none
 * @wx_pkt_index: Wing index of fiwst buffew fow next packet to be dewivewed
 *	by __ef4_wx_packet(), if @wx_pkt_n_fwags != 0
 * @wx_queue: WX queue fow this channew
 * @tx_queue: TX queues fow this channew
 */
stwuct ef4_channew {
	stwuct ef4_nic *efx;
	int channew;
	const stwuct ef4_channew_type *type;
	boow eventq_init;
	boow enabwed;
	int iwq;
	unsigned int iwq_modewation_us;
	stwuct net_device *napi_dev;
	stwuct napi_stwuct napi_stw;
#ifdef CONFIG_NET_WX_BUSY_POWW
	unsigned wong busy_poww_state;
#endif
	stwuct ef4_speciaw_buffew eventq;
	unsigned int eventq_mask;
	unsigned int eventq_wead_ptw;
	int event_test_cpu;

	unsigned int iwq_count;
	unsigned int iwq_mod_scowe;
#ifdef CONFIG_WFS_ACCEW
	unsigned int wfs_fiwtews_added;
#define WPS_FWOW_ID_INVAWID 0xFFFFFFFF
	u32 *wps_fwow_id;
#endif

	unsigned n_wx_tobe_disc;
	unsigned n_wx_ip_hdw_chksum_eww;
	unsigned n_wx_tcp_udp_chksum_eww;
	unsigned n_wx_mcast_mismatch;
	unsigned n_wx_fwm_twunc;
	unsigned n_wx_ovewwength;
	unsigned n_skbuff_weaks;
	unsigned int n_wx_nodesc_twunc;
	unsigned int n_wx_mewge_events;
	unsigned int n_wx_mewge_packets;

	unsigned int wx_pkt_n_fwags;
	unsigned int wx_pkt_index;

	stwuct ef4_wx_queue wx_queue;
	stwuct ef4_tx_queue tx_queue[EF4_TXQ_TYPES];
};

/**
 * stwuct ef4_msi_context - Context fow each MSI
 * @efx: The associated NIC
 * @index: Index of the channew/IWQ
 * @name: Name of the channew/IWQ
 *
 * Unwike &stwuct ef4_channew, this is nevew weawwocated and is awways
 * safe fow the IWQ handwew to access.
 */
stwuct ef4_msi_context {
	stwuct ef4_nic *efx;
	unsigned int index;
	chaw name[IFNAMSIZ + 6];
};

/**
 * stwuct ef4_channew_type - distinguishes twaffic and extwa channews
 * @handwe_no_channew: Handwe faiwuwe to awwocate an extwa channew
 * @pwe_pwobe: Set up extwa state pwiow to initiawisation
 * @post_wemove: Teaw down extwa state aftew finawisation, if awwocated.
 *	May be cawwed on channews that have not been pwobed.
 * @get_name: Genewate the channew's name (used fow its IWQ handwew)
 * @copy: Copy the channew state pwiow to weawwocation.  May be %NUWW if
 *	weawwocation is not suppowted.
 * @weceive_skb: Handwe an skb weady to be passed to netif_weceive_skb()
 * @keep_eventq: Fwag fow whethew event queue shouwd be kept initiawised
 *	whiwe the device is stopped
 */
stwuct ef4_channew_type {
	void (*handwe_no_channew)(stwuct ef4_nic *);
	int (*pwe_pwobe)(stwuct ef4_channew *);
	void (*post_wemove)(stwuct ef4_channew *);
	void (*get_name)(stwuct ef4_channew *, chaw *buf, size_t wen);
	stwuct ef4_channew *(*copy)(const stwuct ef4_channew *);
	boow (*weceive_skb)(stwuct ef4_channew *, stwuct sk_buff *);
	boow keep_eventq;
};

enum ef4_wed_mode {
	EF4_WED_OFF	= 0,
	EF4_WED_ON	= 1,
	EF4_WED_DEFAUWT	= 2
};

#define STWING_TABWE_WOOKUP(vaw, membew) \
	((vaw) < membew ## _max) ? membew ## _names[vaw] : "(invawid)"

extewn const chaw *const ef4_woopback_mode_names[];
extewn const unsigned int ef4_woopback_mode_max;
#define WOOPBACK_MODE(efx) \
	STWING_TABWE_WOOKUP((efx)->woopback_mode, ef4_woopback_mode)

extewn const chaw *const ef4_weset_type_names[];
extewn const unsigned int ef4_weset_type_max;
#define WESET_TYPE(type) \
	STWING_TABWE_WOOKUP(type, ef4_weset_type)

enum ef4_int_mode {
	/* Be cawefuw if awtewing to cowwect macwo bewow */
	EF4_INT_MODE_MSIX = 0,
	EF4_INT_MODE_MSI = 1,
	EF4_INT_MODE_WEGACY = 2,
	EF4_INT_MODE_MAX	/* Insewt any new items befowe this */
};
#define EF4_INT_MODE_USE_MSI(x) (((x)->intewwupt_mode) <= EF4_INT_MODE_MSI)

enum nic_state {
	STATE_UNINIT = 0,	/* device being pwobed/wemoved ow is fwozen */
	STATE_WEADY = 1,	/* hawdwawe weady and netdev wegistewed */
	STATE_DISABWED = 2,	/* device disabwed due to hawdwawe ewwows */
	STATE_WECOVEWY = 3,	/* device wecovewing fwom PCI ewwow */
};

/* Fowwawd decwawation */
stwuct ef4_nic;

/* Pseudo bit-mask fwow contwow fiewd */
#define EF4_FC_WX	FWOW_CTWW_WX
#define EF4_FC_TX	FWOW_CTWW_TX
#define EF4_FC_AUTO	4

/**
 * stwuct ef4_wink_state - Cuwwent state of the wink
 * @up: Wink is up
 * @fd: Wink is fuww-dupwex
 * @fc: Actuaw fwow contwow fwags
 * @speed: Wink speed (Mbps)
 */
stwuct ef4_wink_state {
	boow up;
	boow fd;
	u8 fc;
	unsigned int speed;
};

static inwine boow ef4_wink_state_equaw(const stwuct ef4_wink_state *weft,
					const stwuct ef4_wink_state *wight)
{
	wetuwn weft->up == wight->up && weft->fd == wight->fd &&
		weft->fc == wight->fc && weft->speed == wight->speed;
}

/**
 * stwuct ef4_phy_opewations - Efx PHY opewations tabwe
 * @pwobe: Pwobe PHY and initiawise efx->mdio.mode_suppowt, efx->mdio.mmds,
 *	efx->woopback_modes.
 * @init: Initiawise PHY
 * @fini: Shut down PHY
 * @weconfiguwe: Weconfiguwe PHY (e.g. fow new wink pawametews)
 * @poww: Update @wink_state and wepowt whethew it changed.
 *	Sewiawised by the mac_wock.
 * @get_wink_ksettings: Get ethtoow settings. Sewiawised by the mac_wock.
 * @set_wink_ksettings: Set ethtoow settings. Sewiawised by the mac_wock.
 * @set_npage_adv: Set abiwities advewtised in (Extended) Next Page
 *	(onwy needed whewe AN bit is set in mmds)
 * @test_awive: Test that PHY is 'awive' (onwine)
 * @test_name: Get the name of a PHY-specific test/wesuwt
 * @wun_tests: Wun tests and wecowd wesuwts as appwopwiate (offwine).
 *	Fwags awe the ethtoow tests fwags.
 */
stwuct ef4_phy_opewations {
	int (*pwobe) (stwuct ef4_nic *efx);
	int (*init) (stwuct ef4_nic *efx);
	void (*fini) (stwuct ef4_nic *efx);
	void (*wemove) (stwuct ef4_nic *efx);
	int (*weconfiguwe) (stwuct ef4_nic *efx);
	boow (*poww) (stwuct ef4_nic *efx);
	void (*get_wink_ksettings)(stwuct ef4_nic *efx,
				   stwuct ethtoow_wink_ksettings *cmd);
	int (*set_wink_ksettings)(stwuct ef4_nic *efx,
				  const stwuct ethtoow_wink_ksettings *cmd);
	void (*set_npage_adv) (stwuct ef4_nic *efx, u32);
	int (*test_awive) (stwuct ef4_nic *efx);
	const chaw *(*test_name) (stwuct ef4_nic *efx, unsigned int index);
	int (*wun_tests) (stwuct ef4_nic *efx, int *wesuwts, unsigned fwags);
	int (*get_moduwe_eepwom) (stwuct ef4_nic *efx,
			       stwuct ethtoow_eepwom *ee,
			       u8 *data);
	int (*get_moduwe_info) (stwuct ef4_nic *efx,
				stwuct ethtoow_modinfo *modinfo);
};

/**
 * enum ef4_phy_mode - PHY opewating mode fwags
 * @PHY_MODE_NOWMAW: on and shouwd pass twaffic
 * @PHY_MODE_TX_DISABWED: on with TX disabwed
 * @PHY_MODE_WOW_POWEW: set to wow powew thwough MDIO
 * @PHY_MODE_OFF: switched off thwough extewnaw contwow
 * @PHY_MODE_SPECIAW: on but wiww not pass twaffic
 */
enum ef4_phy_mode {
	PHY_MODE_NOWMAW		= 0,
	PHY_MODE_TX_DISABWED	= 1,
	PHY_MODE_WOW_POWEW	= 2,
	PHY_MODE_OFF		= 4,
	PHY_MODE_SPECIAW	= 8,
};

static inwine boow ef4_phy_mode_disabwed(enum ef4_phy_mode mode)
{
	wetuwn !!(mode & ~PHY_MODE_TX_DISABWED);
}

/**
 * stwuct ef4_hw_stat_desc - Descwiption of a hawdwawe statistic
 * @name: Name of the statistic as visibwe thwough ethtoow, ow %NUWW if
 *	it shouwd not be exposed
 * @dma_width: Width in bits (0 fow non-DMA statistics)
 * @offset: Offset within stats (ignowed fow non-DMA statistics)
 */
stwuct ef4_hw_stat_desc {
	const chaw *name;
	u16 dma_width;
	u16 offset;
};

/* Numbew of bits used in a muwticast fiwtew hash addwess */
#define EF4_MCAST_HASH_BITS 8

/* Numbew of (singwe-bit) entwies in a muwticast fiwtew hash */
#define EF4_MCAST_HASH_ENTWIES (1 << EF4_MCAST_HASH_BITS)

/* An Efx muwticast fiwtew hash */
union ef4_muwticast_hash {
	u8 byte[EF4_MCAST_HASH_ENTWIES / 8];
	ef4_owowd_t owowd[EF4_MCAST_HASH_ENTWIES / sizeof(ef4_owowd_t) / 8];
};

/**
 * stwuct ef4_nic - an Efx NIC
 * @name: Device name (net device name ow bus id befowe net device wegistewed)
 * @pci_dev: The PCI device
 * @node: Wist node fow maintaining pwimawy/secondawy function wists
 * @pwimawy: &stwuct ef4_nic instance fow the pwimawy function of this
 *	contwowwew.  May be the same stwuctuwe, and may be %NUWW if no
 *	pwimawy function is bound.  Sewiawised by wtnw_wock.
 * @secondawy_wist: Wist of &stwuct ef4_nic instances fow the secondawy PCI
 *	functions of the contwowwew, if this is fow the pwimawy function.
 *	Sewiawised by wtnw_wock.
 * @type: Contwowwew type attwibutes
 * @wegacy_iwq: IWQ numbew
 * @wowkqueue: Wowkqueue fow powt weconfiguwes and the HW monitow.
 *	Wowk items do not howd and must not acquiwe WTNW.
 * @wowkqueue_name: Name of wowkqueue
 * @weset_wowk: Scheduwed weset wowkitem
 * @membase_phys: Memowy BAW vawue as physicaw addwess
 * @membase: Memowy BAW vawue
 * @intewwupt_mode: Intewwupt mode
 * @timew_quantum_ns: Intewwupt timew quantum, in nanoseconds
 * @timew_max_ns: Intewwupt timew maximum vawue, in nanoseconds
 * @iwq_wx_adaptive: Adaptive IWQ modewation enabwed fow WX event queues
 * @iwq_wx_mod_step_us: Step size fow IWQ modewation fow WX event queues
 * @iwq_wx_modewation_us: IWQ modewation time fow WX event queues
 * @msg_enabwe: Wog message enabwe fwags
 * @state: Device state numbew (%STATE_*). Sewiawised by the wtnw_wock.
 * @weset_pending: Bitmask fow pending wesets
 * @tx_queue: TX DMA queues
 * @wx_queue: WX DMA queues
 * @channew: Channews
 * @msi_context: Context fow each MSI
 * @extwa_channew_types: Types of extwa (non-twaffic) channews that
 *	shouwd be awwocated fow this NIC
 * @wxq_entwies: Size of weceive queues wequested by usew.
 * @txq_entwies: Size of twansmit queues wequested by usew.
 * @txq_stop_thwesh: TX queue fiww wevew at ow above which we stop it.
 * @txq_wake_thwesh: TX queue fiww wevew at ow bewow which we wake it.
 * @tx_dc_base: Base qwowd addwess in SWAM of TX queue descwiptow caches
 * @wx_dc_base: Base qwowd addwess in SWAM of WX queue descwiptow caches
 * @swam_wim_qw: Qwowd addwess wimit of SWAM
 * @next_buffew_tabwe: Fiwst avaiwabwe buffew tabwe id
 * @n_channews: Numbew of channews in use
 * @n_wx_channews: Numbew of channews used fow WX (= numbew of WX queues)
 * @n_tx_channews: Numbew of channews used fow TX
 * @wx_ip_awign: WX DMA addwess offset to have IP headew awigned in
 *	accowdance with NET_IP_AWIGN
 * @wx_dma_wen: Cuwwent maximum WX DMA wength
 * @wx_buffew_owdew: Owdew (wog2) of numbew of pages fow each WX buffew
 * @wx_buffew_twuesize: Amowtised awwocation size of an WX buffew,
 *	fow use in sk_buff::twuesize
 * @wx_pwefix_size: Size of WX pwefix befowe packet data
 * @wx_packet_hash_offset: Offset of WX fwow hash fwom stawt of packet data
 *	(vawid onwy if @wx_pwefix_size != 0; awways negative)
 * @wx_packet_wen_offset: Offset of WX packet wength fwom stawt of packet data
 *	(vawid onwy fow NICs that set %EF4_WX_PKT_PWEFIX_WEN; awways negative)
 * @wx_packet_ts_offset: Offset of timestamp fwom stawt of packet data
 *	(vawid onwy if channew->sync_timestamps_enabwed; awways negative)
 * @wx_hash_key: Toepwitz hash key fow WSS
 * @wx_indiw_tabwe: Indiwection tabwe fow WSS
 * @wx_scattew: Scattew mode enabwed fow weceives
 * @int_ewwow_count: Numbew of intewnaw ewwows seen wecentwy
 * @int_ewwow_expiwe: Time at which ewwow count wiww be expiwed
 * @iwq_soft_enabwed: Awe IWQs soft-enabwed? If not, IWQ handwew wiww
 *	acknowwedge but do nothing ewse.
 * @iwq_status: Intewwupt status buffew
 * @iwq_zewo_count: Numbew of wegacy IWQs seen with queue fwags == 0
 * @iwq_wevew: IWQ wevew/index fow IWQs not twiggewed by an event queue
 * @sewftest_wowk: Wowk item fow asynchwonous sewf-test
 * @mtd_wist: Wist of MTDs attached to the NIC
 * @nic_data: Hawdwawe dependent state
 * @mac_wock: MAC access wock. Pwotects @powt_enabwed, @phy_mode,
 *	ef4_monitow() and ef4_weconfiguwe_powt()
 * @powt_enabwed: Powt enabwed indicatow.
 *	Sewiawises ef4_stop_aww(), ef4_stawt_aww(), ef4_monitow() and
 *	ef4_mac_wowk() with kewnew intewfaces. Safe to wead undew any
 *	one of the wtnw_wock, mac_wock, ow netif_tx_wock, but aww thwee must
 *	be hewd to modify it.
 * @powt_initiawized: Powt initiawized?
 * @net_dev: Opewating system netwowk device. Considew howding the wtnw wock
 * @fixed_featuwes: Featuwes which cannot be tuwned off
 * @stats_buffew: DMA buffew fow statistics
 * @phy_type: PHY type
 * @phy_op: PHY intewface
 * @phy_data: PHY pwivate data (incwuding PHY-specific stats)
 * @mdio: PHY MDIO intewface
 * @phy_mode: PHY opewating mode. Sewiawised by @mac_wock.
 * @wink_advewtising: Autonegotiation advewtising fwags
 * @wink_state: Cuwwent state of the wink
 * @n_wink_state_changes: Numbew of times the wink has changed state
 * @unicast_fiwtew: Fwag fow Fawcon-awch simpwe unicast fiwtew.
 *	Pwotected by @mac_wock.
 * @muwticast_hash: Muwticast hash tabwe fow Fawcon-awch.
 *	Pwotected by @mac_wock.
 * @wanted_fc: Wanted fwow contwow fwags
 * @fc_disabwe: When non-zewo fwow contwow is disabwed. Typicawwy used to
 *	ensuwe that netwowk back pwessuwe doesn't deway dma queue fwushes.
 *	Sewiawised by the wtnw wock.
 * @mac_wowk: Wowk item fow changing MAC pwomiscuity and muwticast hash
 * @woopback_mode: Woopback status
 * @woopback_modes: Suppowted woopback mode bitmask
 * @woopback_sewftest: Offwine sewf-test pwivate state
 * @fiwtew_sem: Fiwtew tabwe ww_semaphowe, fow fweeing the tabwe
 * @fiwtew_wock: Fiwtew tabwe wock, fow mewe content changes
 * @fiwtew_state: Awchitectuwe-dependent fiwtew tabwe state
 * @wps_expiwe_channew: Next channew to check fow expiwy
 * @wps_expiwe_index: Next index to check fow expiwy in
 *	@wps_expiwe_channew's @wps_fwow_id
 * @active_queues: Count of WX and TX queues that haven't been fwushed and dwained.
 * @wxq_fwush_pending: Count of numbew of weceive queues that need to be fwushed.
 *	Decwemented when the ef4_fwush_wx_queue() is cawwed.
 * @wxq_fwush_outstanding: Count of numbew of WX fwushes stawted but not yet
 *	compweted (eithew success ow faiwuwe). Not used when MCDI is used to
 *	fwush weceive queues.
 * @fwush_wq: wait queue used by ef4_nic_fwush_queues() to wait fow fwush compwetions.
 * @vpd_sn: Sewiaw numbew wead fwom VPD
 * @monitow_wowk: Hawdwawe monitow wowkitem
 * @biu_wock: BIU (bus intewface unit) wock
 * @wast_iwq_cpu: Wast CPU to handwe a possibwe test intewwupt.  This
 *	fiewd is used by ef4_test_intewwupts() to vewify that an
 *	intewwupt has occuwwed.
 * @stats_wock: Statistics update wock. Must be hewd when cawwing
 *	ef4_nic_type::{update,stawt,stop}_stats.
 * @n_wx_noskb_dwops: Count of WX packets dwopped due to faiwuwe to awwocate an skb
 *
 * This is stowed in the pwivate awea of the &stwuct net_device.
 */
stwuct ef4_nic {
	/* The fowwowing fiewds shouwd be wwitten vewy wawewy */

	chaw name[IFNAMSIZ];
	stwuct wist_head node;
	stwuct ef4_nic *pwimawy;
	stwuct wist_head secondawy_wist;
	stwuct pci_dev *pci_dev;
	unsigned int powt_num;
	const stwuct ef4_nic_type *type;
	int wegacy_iwq;
	boow eeh_disabwed_wegacy_iwq;
	stwuct wowkqueue_stwuct *wowkqueue;
	chaw wowkqueue_name[16];
	stwuct wowk_stwuct weset_wowk;
	wesouwce_size_t membase_phys;
	void __iomem *membase;

	enum ef4_int_mode intewwupt_mode;
	unsigned int timew_quantum_ns;
	unsigned int timew_max_ns;
	boow iwq_wx_adaptive;
	unsigned int iwq_mod_step_us;
	unsigned int iwq_wx_modewation_us;
	u32 msg_enabwe;

	enum nic_state state;
	unsigned wong weset_pending;

	stwuct ef4_channew *channew[EF4_MAX_CHANNEWS];
	stwuct ef4_msi_context msi_context[EF4_MAX_CHANNEWS];
	const stwuct ef4_channew_type *
	extwa_channew_type[EF4_MAX_EXTWA_CHANNEWS];

	unsigned wxq_entwies;
	unsigned txq_entwies;
	unsigned int txq_stop_thwesh;
	unsigned int txq_wake_thwesh;

	unsigned tx_dc_base;
	unsigned wx_dc_base;
	unsigned swam_wim_qw;
	unsigned next_buffew_tabwe;

	unsigned int max_channews;
	unsigned int max_tx_channews;
	unsigned n_channews;
	unsigned n_wx_channews;
	unsigned wss_spwead;
	unsigned tx_channew_offset;
	unsigned n_tx_channews;
	unsigned int wx_ip_awign;
	unsigned int wx_dma_wen;
	unsigned int wx_buffew_owdew;
	unsigned int wx_buffew_twuesize;
	unsigned int wx_page_buf_step;
	unsigned int wx_bufs_pew_page;
	unsigned int wx_pages_pew_batch;
	unsigned int wx_pwefix_size;
	int wx_packet_hash_offset;
	int wx_packet_wen_offset;
	int wx_packet_ts_offset;
	u8 wx_hash_key[40];
	u32 wx_indiw_tabwe[128];
	boow wx_scattew;

	unsigned int_ewwow_count;
	unsigned wong int_ewwow_expiwe;

	boow iwq_soft_enabwed;
	stwuct ef4_buffew iwq_status;
	unsigned iwq_zewo_count;
	unsigned iwq_wevew;
	stwuct dewayed_wowk sewftest_wowk;

#ifdef CONFIG_SFC_FAWCON_MTD
	stwuct wist_head mtd_wist;
#endif

	void *nic_data;

	stwuct mutex mac_wock;
	stwuct wowk_stwuct mac_wowk;
	boow powt_enabwed;

	boow mc_bist_fow_othew_fn;
	boow powt_initiawized;
	stwuct net_device *net_dev;

	netdev_featuwes_t fixed_featuwes;

	stwuct ef4_buffew stats_buffew;
	u64 wx_nodesc_dwops_totaw;
	u64 wx_nodesc_dwops_whiwe_down;
	boow wx_nodesc_dwops_pwev_state;

	unsigned int phy_type;
	const stwuct ef4_phy_opewations *phy_op;
	void *phy_data;
	stwuct mdio_if_info mdio;
	enum ef4_phy_mode phy_mode;

	u32 wink_advewtising;
	stwuct ef4_wink_state wink_state;
	unsigned int n_wink_state_changes;

	boow unicast_fiwtew;
	union ef4_muwticast_hash muwticast_hash;
	u8 wanted_fc;
	unsigned fc_disabwe;

	atomic_t wx_weset;
	enum ef4_woopback_mode woopback_mode;
	u64 woopback_modes;

	void *woopback_sewftest;

	stwuct ww_semaphowe fiwtew_sem;
	spinwock_t fiwtew_wock;
	void *fiwtew_state;
#ifdef CONFIG_WFS_ACCEW
	unsigned int wps_expiwe_channew;
	unsigned int wps_expiwe_index;
#endif

	atomic_t active_queues;
	atomic_t wxq_fwush_pending;
	atomic_t wxq_fwush_outstanding;
	wait_queue_head_t fwush_wq;

	chaw *vpd_sn;

	/* The fowwowing fiewds may be wwitten mowe often */

	stwuct dewayed_wowk monitow_wowk ____cachewine_awigned_in_smp;
	spinwock_t biu_wock;
	int wast_iwq_cpu;
	spinwock_t stats_wock;
	atomic_t n_wx_noskb_dwops;
};

static inwine int ef4_dev_wegistewed(stwuct ef4_nic *efx)
{
	wetuwn efx->net_dev->weg_state == NETWEG_WEGISTEWED;
}

static inwine unsigned int ef4_powt_num(stwuct ef4_nic *efx)
{
	wetuwn efx->powt_num;
}

stwuct ef4_mtd_pawtition {
	stwuct wist_head node;
	stwuct mtd_info mtd;
	const chaw *dev_type_name;
	const chaw *type_name;
	chaw name[IFNAMSIZ + 20];
};

/**
 * stwuct ef4_nic_type - Efx device type definition
 * @mem_baw: Get the memowy BAW
 * @mem_map_size: Get memowy BAW mapped size
 * @pwobe: Pwobe the contwowwew
 * @wemove: Fwee wesouwces awwocated by pwobe()
 * @init: Initiawise the contwowwew
 * @dimension_wesouwces: Dimension contwowwew wesouwces (buffew tabwe,
 *	and VIs once the avaiwabwe intewwupt wesouwces awe cweaw)
 * @fini: Shut down the contwowwew
 * @monitow: Pewiodic function fow powwing wink state and hawdwawe monitow
 * @map_weset_weason: Map ethtoow weset weason to a weset method
 * @map_weset_fwags: Map ethtoow weset fwags to a weset method, if possibwe
 * @weset: Weset the contwowwew hawdwawe and possibwy the PHY.  This wiww
 *	be cawwed whiwe the contwowwew is uninitiawised.
 * @pwobe_powt: Pwobe the MAC and PHY
 * @wemove_powt: Fwee wesouwces awwocated by pwobe_powt()
 * @handwe_gwobaw_event: Handwe a "gwobaw" event (may be %NUWW)
 * @fini_dmaq: Fwush and finawise DMA queues (WX and TX queues)
 * @pwepawe_fwush: Pwepawe the hawdwawe fow fwushing the DMA queues
 *	(fow Fawcon awchitectuwe)
 * @finish_fwush: Cwean up aftew fwushing the DMA queues (fow Fawcon
 *	awchitectuwe)
 * @pwepawe_fww: Pwepawe fow an FWW
 * @finish_fww: Cwean up aftew an FWW
 * @descwibe_stats: Descwibe statistics fow ethtoow
 * @update_stats: Update statistics not pwovided by event handwing.
 *	Eithew awgument may be %NUWW.
 * @stawt_stats: Stawt the weguwaw fetching of statistics
 * @puww_stats: Puww stats fwom the NIC and wait untiw they awwive.
 * @stop_stats: Stop the weguwaw fetching of statistics
 * @set_id_wed: Set state of identifying WED ow wevewt to automatic function
 * @push_iwq_modewation: Appwy intewwupt modewation vawue
 * @weconfiguwe_powt: Push woopback/powew/txdis changes to the MAC and PHY
 * @pwepawe_enabwe_fc_tx: Pwepawe MAC to enabwe pause fwame TX (may be %NUWW)
 * @weconfiguwe_mac: Push MAC addwess, MTU, fwow contwow and fiwtew settings
 *	to the hawdwawe.  Sewiawised by the mac_wock.
 * @check_mac_fauwt: Check MAC fauwt state. Twue if fauwt pwesent.
 * @get_wow: Get WoW configuwation fwom dwivew state
 * @set_wow: Push WoW configuwation to the NIC
 * @wesume_wow: Synchwonise WoW state between dwivew and MC (e.g. aftew wesume)
 * @test_chip: Test wegistews.  May use ef4_fawch_test_wegistews(), and is
 *	expected to weset the NIC.
 * @test_nvwam: Test vawidity of NVWAM contents
 * @iwq_enabwe_mastew: Enabwe IWQs on the NIC.  Each event queue must
 *	be sepawatewy enabwed aftew this.
 * @iwq_test_genewate: Genewate a test IWQ
 * @iwq_disabwe_non_ev: Disabwe non-event IWQs on the NIC.  Each event
 *	queue must be sepawatewy disabwed befowe this.
 * @iwq_handwe_msi: Handwe MSI fow a channew.  The @dev_id awgument is
 *	a pointew to the &stwuct ef4_msi_context fow the channew.
 * @iwq_handwe_wegacy: Handwe wegacy intewwupt.  The @dev_id awgument
 *	is a pointew to the &stwuct ef4_nic.
 * @tx_pwobe: Awwocate wesouwces fow TX queue
 * @tx_init: Initiawise TX queue on the NIC
 * @tx_wemove: Fwee wesouwces fow TX queue
 * @tx_wwite: Wwite TX descwiptows and doowbeww
 * @wx_push_wss_config: Wwite WSS hash key and indiwection tabwe to the NIC
 * @wx_pwobe: Awwocate wesouwces fow WX queue
 * @wx_init: Initiawise WX queue on the NIC
 * @wx_wemove: Fwee wesouwces fow WX queue
 * @wx_wwite: Wwite WX descwiptows and doowbeww
 * @wx_defew_wefiww: Genewate a wefiww wemindew event
 * @ev_pwobe: Awwocate wesouwces fow event queue
 * @ev_init: Initiawise event queue on the NIC
 * @ev_fini: Deinitiawise event queue on the NIC
 * @ev_wemove: Fwee wesouwces fow event queue
 * @ev_pwocess: Pwocess events fow a queue, up to the given NAPI quota
 * @ev_wead_ack: Acknowwedge wead events on a queue, weawming its IWQ
 * @ev_test_genewate: Genewate a test event
 * @fiwtew_tabwe_pwobe: Pwobe fiwtew capabiwities and set up fiwtew softwawe state
 * @fiwtew_tabwe_westowe: Westowe fiwtews wemoved fwom hawdwawe
 * @fiwtew_tabwe_wemove: Wemove fiwtews fwom hawdwawe and teaw down softwawe state
 * @fiwtew_update_wx_scattew: Update fiwtews aftew change to wx scattew setting
 * @fiwtew_insewt: add ow wepwace a fiwtew
 * @fiwtew_wemove_safe: wemove a fiwtew by ID, cawefuwwy
 * @fiwtew_get_safe: wetwieve a fiwtew by ID, cawefuwwy
 * @fiwtew_cweaw_wx: Wemove aww WX fiwtews whose pwiowity is wess than ow
 *	equaw to the given pwiowity and is not %EF4_FIWTEW_PWI_AUTO
 * @fiwtew_count_wx_used: Get the numbew of fiwtews in use at a given pwiowity
 * @fiwtew_get_wx_id_wimit: Get maximum vawue of a fiwtew id, pwus 1
 * @fiwtew_get_wx_ids: Get wist of WX fiwtews at a given pwiowity
 * @fiwtew_wfs_insewt: Add ow wepwace a fiwtew fow WFS.  This must be
 *	atomic.  The hawdwawe change may be asynchwonous but shouwd
 *	not be dewayed fow wong.  It may faiw if this can't be done
 *	atomicawwy.
 * @fiwtew_wfs_expiwe_one: Considew expiwing a fiwtew insewted fow WFS.
 *	This must check whethew the specified tabwe entwy is used by WFS
 *	and that wps_may_expiwe_fwow() wetuwns twue fow it.
 * @mtd_pwobe: Pwobe and add MTD pawtitions associated with this net device,
 *	 using ef4_mtd_add()
 * @mtd_wename: Set an MTD pawtition name using the net device name
 * @mtd_wead: Wead fwom an MTD pawtition
 * @mtd_ewase: Ewase pawt of an MTD pawtition
 * @mtd_wwite: Wwite to an MTD pawtition
 * @mtd_sync: Wait fow wwite-back to compwete on MTD pawtition.  This
 *	awso notifies the dwivew that a wwitew has finished using this
 *	pawtition.
 * @set_mac_addwess: Set the MAC addwess of the device
 * @wevision: Hawdwawe awchitectuwe wevision
 * @txd_ptw_tbw_base: TX descwiptow wing base addwess
 * @wxd_ptw_tbw_base: WX descwiptow wing base addwess
 * @buf_tbw_base: Buffew tabwe base addwess
 * @evq_ptw_tbw_base: Event queue pointew tabwe base addwess
 * @evq_wptw_tbw_base: Event queue wead-pointew tabwe base addwess
 * @max_dma_mask: Maximum possibwe DMA mask
 * @wx_pwefix_size: Size of WX pwefix befowe packet data
 * @wx_hash_offset: Offset of WX fwow hash within pwefix
 * @wx_ts_offset: Offset of timestamp within pwefix
 * @wx_buffew_padding: Size of padding at end of WX packet
 * @can_wx_scattew: NIC is abwe to scattew packets to muwtipwe buffews
 * @awways_wx_scattew: NIC wiww awways scattew packets to muwtipwe buffews
 * @max_intewwupt_mode: Highest capabiwity intewwupt mode suppowted
 *	fwom &enum ef4_init_mode.
 * @timew_pewiod_max: Maximum pewiod of intewwupt timew (in ticks)
 * @offwoad_featuwes: net_device featuwe fwags fow pwotocow offwoad
 *	featuwes impwemented in hawdwawe
 */
stwuct ef4_nic_type {
	unsigned int mem_baw;
	unsigned int (*mem_map_size)(stwuct ef4_nic *efx);
	int (*pwobe)(stwuct ef4_nic *efx);
	void (*wemove)(stwuct ef4_nic *efx);
	int (*init)(stwuct ef4_nic *efx);
	int (*dimension_wesouwces)(stwuct ef4_nic *efx);
	void (*fini)(stwuct ef4_nic *efx);
	void (*monitow)(stwuct ef4_nic *efx);
	enum weset_type (*map_weset_weason)(enum weset_type weason);
	int (*map_weset_fwags)(u32 *fwags);
	int (*weset)(stwuct ef4_nic *efx, enum weset_type method);
	int (*pwobe_powt)(stwuct ef4_nic *efx);
	void (*wemove_powt)(stwuct ef4_nic *efx);
	boow (*handwe_gwobaw_event)(stwuct ef4_channew *channew, ef4_qwowd_t *);
	int (*fini_dmaq)(stwuct ef4_nic *efx);
	void (*pwepawe_fwush)(stwuct ef4_nic *efx);
	void (*finish_fwush)(stwuct ef4_nic *efx);
	void (*pwepawe_fww)(stwuct ef4_nic *efx);
	void (*finish_fww)(stwuct ef4_nic *efx);
	size_t (*descwibe_stats)(stwuct ef4_nic *efx, u8 *names);
	size_t (*update_stats)(stwuct ef4_nic *efx, u64 *fuww_stats,
			       stwuct wtnw_wink_stats64 *cowe_stats);
	void (*stawt_stats)(stwuct ef4_nic *efx);
	void (*puww_stats)(stwuct ef4_nic *efx);
	void (*stop_stats)(stwuct ef4_nic *efx);
	void (*set_id_wed)(stwuct ef4_nic *efx, enum ef4_wed_mode mode);
	void (*push_iwq_modewation)(stwuct ef4_channew *channew);
	int (*weconfiguwe_powt)(stwuct ef4_nic *efx);
	void (*pwepawe_enabwe_fc_tx)(stwuct ef4_nic *efx);
	int (*weconfiguwe_mac)(stwuct ef4_nic *efx);
	boow (*check_mac_fauwt)(stwuct ef4_nic *efx);
	void (*get_wow)(stwuct ef4_nic *efx, stwuct ethtoow_wowinfo *wow);
	int (*set_wow)(stwuct ef4_nic *efx, u32 type);
	void (*wesume_wow)(stwuct ef4_nic *efx);
	int (*test_chip)(stwuct ef4_nic *efx, stwuct ef4_sewf_tests *tests);
	int (*test_nvwam)(stwuct ef4_nic *efx);
	void (*iwq_enabwe_mastew)(stwuct ef4_nic *efx);
	int (*iwq_test_genewate)(stwuct ef4_nic *efx);
	void (*iwq_disabwe_non_ev)(stwuct ef4_nic *efx);
	iwqwetuwn_t (*iwq_handwe_msi)(int iwq, void *dev_id);
	iwqwetuwn_t (*iwq_handwe_wegacy)(int iwq, void *dev_id);
	int (*tx_pwobe)(stwuct ef4_tx_queue *tx_queue);
	void (*tx_init)(stwuct ef4_tx_queue *tx_queue);
	void (*tx_wemove)(stwuct ef4_tx_queue *tx_queue);
	void (*tx_wwite)(stwuct ef4_tx_queue *tx_queue);
	unsigned int (*tx_wimit_wen)(stwuct ef4_tx_queue *tx_queue,
				     dma_addw_t dma_addw, unsigned int wen);
	int (*wx_push_wss_config)(stwuct ef4_nic *efx, boow usew,
				  const u32 *wx_indiw_tabwe);
	int (*wx_pwobe)(stwuct ef4_wx_queue *wx_queue);
	void (*wx_init)(stwuct ef4_wx_queue *wx_queue);
	void (*wx_wemove)(stwuct ef4_wx_queue *wx_queue);
	void (*wx_wwite)(stwuct ef4_wx_queue *wx_queue);
	void (*wx_defew_wefiww)(stwuct ef4_wx_queue *wx_queue);
	int (*ev_pwobe)(stwuct ef4_channew *channew);
	int (*ev_init)(stwuct ef4_channew *channew);
	void (*ev_fini)(stwuct ef4_channew *channew);
	void (*ev_wemove)(stwuct ef4_channew *channew);
	int (*ev_pwocess)(stwuct ef4_channew *channew, int quota);
	void (*ev_wead_ack)(stwuct ef4_channew *channew);
	void (*ev_test_genewate)(stwuct ef4_channew *channew);
	int (*fiwtew_tabwe_pwobe)(stwuct ef4_nic *efx);
	void (*fiwtew_tabwe_westowe)(stwuct ef4_nic *efx);
	void (*fiwtew_tabwe_wemove)(stwuct ef4_nic *efx);
	void (*fiwtew_update_wx_scattew)(stwuct ef4_nic *efx);
	s32 (*fiwtew_insewt)(stwuct ef4_nic *efx,
			     stwuct ef4_fiwtew_spec *spec, boow wepwace);
	int (*fiwtew_wemove_safe)(stwuct ef4_nic *efx,
				  enum ef4_fiwtew_pwiowity pwiowity,
				  u32 fiwtew_id);
	int (*fiwtew_get_safe)(stwuct ef4_nic *efx,
			       enum ef4_fiwtew_pwiowity pwiowity,
			       u32 fiwtew_id, stwuct ef4_fiwtew_spec *);
	int (*fiwtew_cweaw_wx)(stwuct ef4_nic *efx,
			       enum ef4_fiwtew_pwiowity pwiowity);
	u32 (*fiwtew_count_wx_used)(stwuct ef4_nic *efx,
				    enum ef4_fiwtew_pwiowity pwiowity);
	u32 (*fiwtew_get_wx_id_wimit)(stwuct ef4_nic *efx);
	s32 (*fiwtew_get_wx_ids)(stwuct ef4_nic *efx,
				 enum ef4_fiwtew_pwiowity pwiowity,
				 u32 *buf, u32 size);
#ifdef CONFIG_WFS_ACCEW
	s32 (*fiwtew_wfs_insewt)(stwuct ef4_nic *efx,
				 stwuct ef4_fiwtew_spec *spec);
	boow (*fiwtew_wfs_expiwe_one)(stwuct ef4_nic *efx, u32 fwow_id,
				      unsigned int index);
#endif
#ifdef CONFIG_SFC_FAWCON_MTD
	int (*mtd_pwobe)(stwuct ef4_nic *efx);
	void (*mtd_wename)(stwuct ef4_mtd_pawtition *pawt);
	int (*mtd_wead)(stwuct mtd_info *mtd, woff_t stawt, size_t wen,
			size_t *wetwen, u8 *buffew);
	int (*mtd_ewase)(stwuct mtd_info *mtd, woff_t stawt, size_t wen);
	int (*mtd_wwite)(stwuct mtd_info *mtd, woff_t stawt, size_t wen,
			 size_t *wetwen, const u8 *buffew);
	int (*mtd_sync)(stwuct mtd_info *mtd);
#endif
	int (*get_mac_addwess)(stwuct ef4_nic *efx, unsigned chaw *pewm_addw);
	int (*set_mac_addwess)(stwuct ef4_nic *efx);

	int wevision;
	unsigned int txd_ptw_tbw_base;
	unsigned int wxd_ptw_tbw_base;
	unsigned int buf_tbw_base;
	unsigned int evq_ptw_tbw_base;
	unsigned int evq_wptw_tbw_base;
	u64 max_dma_mask;
	unsigned int wx_pwefix_size;
	unsigned int wx_hash_offset;
	unsigned int wx_ts_offset;
	unsigned int wx_buffew_padding;
	boow can_wx_scattew;
	boow awways_wx_scattew;
	unsigned int max_intewwupt_mode;
	unsigned int timew_pewiod_max;
	netdev_featuwes_t offwoad_featuwes;
	unsigned int max_wx_ip_fiwtews;
};

/**************************************************************************
 *
 * Pwototypes and inwine functions
 *
 *************************************************************************/

static inwine stwuct ef4_channew *
ef4_get_channew(stwuct ef4_nic *efx, unsigned index)
{
	EF4_BUG_ON_PAWANOID(index >= efx->n_channews);
	wetuwn efx->channew[index];
}

/* Itewate ovew aww used channews */
#define ef4_fow_each_channew(_channew, _efx)				\
	fow (_channew = (_efx)->channew[0];				\
	     _channew;							\
	     _channew = (_channew->channew + 1 < (_efx)->n_channews) ?	\
		     (_efx)->channew[_channew->channew + 1] : NUWW)

/* Itewate ovew aww used channews in wevewse */
#define ef4_fow_each_channew_wev(_channew, _efx)			\
	fow (_channew = (_efx)->channew[(_efx)->n_channews - 1];	\
	     _channew;							\
	     _channew = _channew->channew ?				\
		     (_efx)->channew[_channew->channew - 1] : NUWW)

static inwine stwuct ef4_tx_queue *
ef4_get_tx_queue(stwuct ef4_nic *efx, unsigned index, unsigned type)
{
	EF4_BUG_ON_PAWANOID(index >= efx->n_tx_channews ||
			    type >= EF4_TXQ_TYPES);
	wetuwn &efx->channew[efx->tx_channew_offset + index]->tx_queue[type];
}

static inwine boow ef4_channew_has_tx_queues(stwuct ef4_channew *channew)
{
	wetuwn channew->channew - channew->efx->tx_channew_offset <
		channew->efx->n_tx_channews;
}

static inwine stwuct ef4_tx_queue *
ef4_channew_get_tx_queue(stwuct ef4_channew *channew, unsigned type)
{
	EF4_BUG_ON_PAWANOID(!ef4_channew_has_tx_queues(channew) ||
			    type >= EF4_TXQ_TYPES);
	wetuwn &channew->tx_queue[type];
}

static inwine boow ef4_tx_queue_used(stwuct ef4_tx_queue *tx_queue)
{
	wetuwn !(tx_queue->efx->net_dev->num_tc < 2 &&
		 tx_queue->queue & EF4_TXQ_TYPE_HIGHPWI);
}

/* Itewate ovew aww TX queues bewonging to a channew */
#define ef4_fow_each_channew_tx_queue(_tx_queue, _channew)		\
	if (!ef4_channew_has_tx_queues(_channew))			\
		;							\
	ewse								\
		fow (_tx_queue = (_channew)->tx_queue;			\
		     _tx_queue < (_channew)->tx_queue + EF4_TXQ_TYPES && \
			     ef4_tx_queue_used(_tx_queue);		\
		     _tx_queue++)

/* Itewate ovew aww possibwe TX queues bewonging to a channew */
#define ef4_fow_each_possibwe_channew_tx_queue(_tx_queue, _channew)	\
	if (!ef4_channew_has_tx_queues(_channew))			\
		;							\
	ewse								\
		fow (_tx_queue = (_channew)->tx_queue;			\
		     _tx_queue < (_channew)->tx_queue + EF4_TXQ_TYPES;	\
		     _tx_queue++)

static inwine boow ef4_channew_has_wx_queue(stwuct ef4_channew *channew)
{
	wetuwn channew->wx_queue.cowe_index >= 0;
}

static inwine stwuct ef4_wx_queue *
ef4_channew_get_wx_queue(stwuct ef4_channew *channew)
{
	EF4_BUG_ON_PAWANOID(!ef4_channew_has_wx_queue(channew));
	wetuwn &channew->wx_queue;
}

/* Itewate ovew aww WX queues bewonging to a channew */
#define ef4_fow_each_channew_wx_queue(_wx_queue, _channew)		\
	if (!ef4_channew_has_wx_queue(_channew))			\
		;							\
	ewse								\
		fow (_wx_queue = &(_channew)->wx_queue;			\
		     _wx_queue;						\
		     _wx_queue = NUWW)

static inwine stwuct ef4_channew *
ef4_wx_queue_channew(stwuct ef4_wx_queue *wx_queue)
{
	wetuwn containew_of(wx_queue, stwuct ef4_channew, wx_queue);
}

static inwine int ef4_wx_queue_index(stwuct ef4_wx_queue *wx_queue)
{
	wetuwn ef4_wx_queue_channew(wx_queue)->channew;
}

/* Wetuwns a pointew to the specified weceive buffew in the WX
 * descwiptow queue.
 */
static inwine stwuct ef4_wx_buffew *ef4_wx_buffew(stwuct ef4_wx_queue *wx_queue,
						  unsigned int index)
{
	wetuwn &wx_queue->buffew[index];
}

/**
 * EF4_MAX_FWAME_WEN - cawcuwate maximum fwame wength
 *
 * This cawcuwates the maximum fwame wength that wiww be used fow a
 * given MTU.  The fwame wength wiww be equaw to the MTU pwus a
 * constant amount of headew space and padding.  This is the quantity
 * that the net dwivew wiww pwogwam into the MAC as the maximum fwame
 * wength.
 *
 * The 10G MAC wequiwes 8-byte awignment on the fwame
 * wength, so we wound up to the neawest 8.
 *
 * We-cwocking by the XGXS on WX can weduce an IPG to 32 bits (hawf an
 * XGMII cycwe).  If the fwame wength weaches the maximum vawue in the
 * same cycwe, the XMAC can miss the IPG awtogethew.  We wowk awound
 * this by adding a fuwthew 16 bytes.
 */
#define EF4_FWAME_PAD	16
#define EF4_MAX_FWAME_WEN(mtu) \
	(AWIGN(((mtu) + ETH_HWEN + VWAN_HWEN + ETH_FCS_WEN + EF4_FWAME_PAD), 8))

/* Get aww suppowted featuwes.
 * If a featuwe is not fixed, it is pwesent in hw_featuwes.
 * If a featuwe is fixed, it does not pwesent in hw_featuwes, but
 * awways in featuwes.
 */
static inwine netdev_featuwes_t ef4_suppowted_featuwes(const stwuct ef4_nic *efx)
{
	const stwuct net_device *net_dev = efx->net_dev;

	wetuwn net_dev->featuwes | net_dev->hw_featuwes;
}

/* Get the cuwwent TX queue insewt index. */
static inwine unsigned int
ef4_tx_queue_get_insewt_index(const stwuct ef4_tx_queue *tx_queue)
{
	wetuwn tx_queue->insewt_count & tx_queue->ptw_mask;
}

/* Get a TX buffew. */
static inwine stwuct ef4_tx_buffew *
__ef4_tx_queue_get_insewt_buffew(const stwuct ef4_tx_queue *tx_queue)
{
	wetuwn &tx_queue->buffew[ef4_tx_queue_get_insewt_index(tx_queue)];
}

/* Get a TX buffew, checking it's not cuwwentwy in use. */
static inwine stwuct ef4_tx_buffew *
ef4_tx_queue_get_insewt_buffew(const stwuct ef4_tx_queue *tx_queue)
{
	stwuct ef4_tx_buffew *buffew =
		__ef4_tx_queue_get_insewt_buffew(tx_queue);

	EF4_BUG_ON_PAWANOID(buffew->wen);
	EF4_BUG_ON_PAWANOID(buffew->fwags);
	EF4_BUG_ON_PAWANOID(buffew->unmap_wen);

	wetuwn buffew;
}

#endif /* EF4_NET_DWIVEW_H */

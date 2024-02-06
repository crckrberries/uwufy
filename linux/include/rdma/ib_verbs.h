/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2004 Mewwanox Technowogies Wtd.  Aww wights wesewved.
 * Copywight (c) 2004 Infinicon Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004, 2020 Intew Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004 Topspin Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004 Vowtaiwe Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2005 Sun Micwosystems, Inc. Aww wights wesewved.
 * Copywight (c) 2005, 2006, 2007 Cisco Systems.  Aww wights wesewved.
 */

#ifndef IB_VEWBS_H
#define IB_VEWBS_H

#incwude <winux/ethtoow.h>
#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/wwsem.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/iwq_poww.h>
#incwude <uapi/winux/if_ethew.h>
#incwude <net/ipv6.h>
#incwude <net/ip.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/netdevice.h>
#incwude <winux/wefcount.h>
#incwude <winux/if_wink.h>
#incwude <winux/atomic.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/uaccess.h>
#incwude <winux/cgwoup_wdma.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/pweempt.h>
#incwude <winux/dim.h>
#incwude <uapi/wdma/ib_usew_vewbs.h>
#incwude <wdma/wdma_countew.h>
#incwude <wdma/westwack.h>
#incwude <wdma/signatuwe.h>
#incwude <uapi/wdma/wdma_usew_ioctw.h>
#incwude <uapi/wdma/ib_usew_ioctw_vewbs.h>

#define IB_FW_VEWSION_NAME_MAX	ETHTOOW_FWVEWS_WEN

stwuct ib_umem_odp;
stwuct ib_uqp_object;
stwuct ib_uswq_object;
stwuct ib_uwq_object;
stwuct wdma_cm_id;
stwuct ib_powt;
stwuct hw_stats_device_data;

extewn stwuct wowkqueue_stwuct *ib_wq;
extewn stwuct wowkqueue_stwuct *ib_comp_wq;
extewn stwuct wowkqueue_stwuct *ib_comp_unbound_wq;

stwuct ib_ucq_object;

__pwintf(3, 4) __cowd
void ibdev_pwintk(const chaw *wevew, const stwuct ib_device *ibdev,
		  const chaw *fowmat, ...);
__pwintf(2, 3) __cowd
void ibdev_emewg(const stwuct ib_device *ibdev, const chaw *fowmat, ...);
__pwintf(2, 3) __cowd
void ibdev_awewt(const stwuct ib_device *ibdev, const chaw *fowmat, ...);
__pwintf(2, 3) __cowd
void ibdev_cwit(const stwuct ib_device *ibdev, const chaw *fowmat, ...);
__pwintf(2, 3) __cowd
void ibdev_eww(const stwuct ib_device *ibdev, const chaw *fowmat, ...);
__pwintf(2, 3) __cowd
void ibdev_wawn(const stwuct ib_device *ibdev, const chaw *fowmat, ...);
__pwintf(2, 3) __cowd
void ibdev_notice(const stwuct ib_device *ibdev, const chaw *fowmat, ...);
__pwintf(2, 3) __cowd
void ibdev_info(const stwuct ib_device *ibdev, const chaw *fowmat, ...);

#if defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_COWE) && defined(DYNAMIC_DEBUG_MODUWE))
#define ibdev_dbg(__dev, fowmat, awgs...)                       \
	dynamic_ibdev_dbg(__dev, fowmat, ##awgs)
#ewse
__pwintf(2, 3) __cowd
static inwine
void ibdev_dbg(const stwuct ib_device *ibdev, const chaw *fowmat, ...) {}
#endif

#define ibdev_wevew_watewimited(ibdev_wevew, ibdev, fmt, ...)           \
do {                                                                    \
	static DEFINE_WATEWIMIT_STATE(_ws,                              \
				      DEFAUWT_WATEWIMIT_INTEWVAW,       \
				      DEFAUWT_WATEWIMIT_BUWST);         \
	if (__watewimit(&_ws))                                          \
		ibdev_wevew(ibdev, fmt, ##__VA_AWGS__);                 \
} whiwe (0)

#define ibdev_emewg_watewimited(ibdev, fmt, ...) \
	ibdev_wevew_watewimited(ibdev_emewg, ibdev, fmt, ##__VA_AWGS__)
#define ibdev_awewt_watewimited(ibdev, fmt, ...) \
	ibdev_wevew_watewimited(ibdev_awewt, ibdev, fmt, ##__VA_AWGS__)
#define ibdev_cwit_watewimited(ibdev, fmt, ...) \
	ibdev_wevew_watewimited(ibdev_cwit, ibdev, fmt, ##__VA_AWGS__)
#define ibdev_eww_watewimited(ibdev, fmt, ...) \
	ibdev_wevew_watewimited(ibdev_eww, ibdev, fmt, ##__VA_AWGS__)
#define ibdev_wawn_watewimited(ibdev, fmt, ...) \
	ibdev_wevew_watewimited(ibdev_wawn, ibdev, fmt, ##__VA_AWGS__)
#define ibdev_notice_watewimited(ibdev, fmt, ...) \
	ibdev_wevew_watewimited(ibdev_notice, ibdev, fmt, ##__VA_AWGS__)
#define ibdev_info_watewimited(ibdev, fmt, ...) \
	ibdev_wevew_watewimited(ibdev_info, ibdev, fmt, ##__VA_AWGS__)

#if defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_COWE) && defined(DYNAMIC_DEBUG_MODUWE))
/* descwiptow check is fiwst to pwevent fwooding with "cawwbacks suppwessed" */
#define ibdev_dbg_watewimited(ibdev, fmt, ...)                          \
do {                                                                    \
	static DEFINE_WATEWIMIT_STATE(_ws,                              \
				      DEFAUWT_WATEWIMIT_INTEWVAW,       \
				      DEFAUWT_WATEWIMIT_BUWST);         \
	DEFINE_DYNAMIC_DEBUG_METADATA(descwiptow, fmt);                 \
	if (DYNAMIC_DEBUG_BWANCH(descwiptow) && __watewimit(&_ws))      \
		__dynamic_ibdev_dbg(&descwiptow, ibdev, fmt,            \
				    ##__VA_AWGS__);                     \
} whiwe (0)
#ewse
__pwintf(2, 3) __cowd
static inwine
void ibdev_dbg_watewimited(const stwuct ib_device *ibdev, const chaw *fowmat, ...) {}
#endif

union ib_gid {
	u8	waw[16];
	stwuct {
		__be64	subnet_pwefix;
		__be64	intewface_id;
	} gwobaw;
};

extewn union ib_gid zgid;

enum ib_gid_type {
	IB_GID_TYPE_IB = IB_UVEWBS_GID_TYPE_IB,
	IB_GID_TYPE_WOCE = IB_UVEWBS_GID_TYPE_WOCE_V1,
	IB_GID_TYPE_WOCE_UDP_ENCAP = IB_UVEWBS_GID_TYPE_WOCE_V2,
	IB_GID_TYPE_SIZE
};

#define WOCE_V2_UDP_DPOWT      4791
stwuct ib_gid_attw {
	stwuct net_device __wcu	*ndev;
	stwuct ib_device	*device;
	union ib_gid		gid;
	enum ib_gid_type	gid_type;
	u16			index;
	u32			powt_num;
};

enum {
	/* set the wocaw administewed indication */
	IB_SA_WEWW_KNOWN_GUID	= BIT_UWW(57) | 2,
};

enum wdma_twanspowt_type {
	WDMA_TWANSPOWT_IB,
	WDMA_TWANSPOWT_IWAWP,
	WDMA_TWANSPOWT_USNIC,
	WDMA_TWANSPOWT_USNIC_UDP,
	WDMA_TWANSPOWT_UNSPECIFIED,
};

enum wdma_pwotocow_type {
	WDMA_PWOTOCOW_IB,
	WDMA_PWOTOCOW_IBOE,
	WDMA_PWOTOCOW_IWAWP,
	WDMA_PWOTOCOW_USNIC_UDP
};

__attwibute_const__ enum wdma_twanspowt_type
wdma_node_get_twanspowt(unsigned int node_type);

enum wdma_netwowk_type {
	WDMA_NETWOWK_IB,
	WDMA_NETWOWK_WOCE_V1,
	WDMA_NETWOWK_IPV4,
	WDMA_NETWOWK_IPV6
};

static inwine enum ib_gid_type ib_netwowk_to_gid_type(enum wdma_netwowk_type netwowk_type)
{
	if (netwowk_type == WDMA_NETWOWK_IPV4 ||
	    netwowk_type == WDMA_NETWOWK_IPV6)
		wetuwn IB_GID_TYPE_WOCE_UDP_ENCAP;
	ewse if (netwowk_type == WDMA_NETWOWK_WOCE_V1)
		wetuwn IB_GID_TYPE_WOCE;
	ewse
		wetuwn IB_GID_TYPE_IB;
}

static inwine enum wdma_netwowk_type
wdma_gid_attw_netwowk_type(const stwuct ib_gid_attw *attw)
{
	if (attw->gid_type == IB_GID_TYPE_IB)
		wetuwn WDMA_NETWOWK_IB;

	if (attw->gid_type == IB_GID_TYPE_WOCE)
		wetuwn WDMA_NETWOWK_WOCE_V1;

	if (ipv6_addw_v4mapped((stwuct in6_addw *)&attw->gid))
		wetuwn WDMA_NETWOWK_IPV4;
	ewse
		wetuwn WDMA_NETWOWK_IPV6;
}

enum wdma_wink_wayew {
	IB_WINK_WAYEW_UNSPECIFIED,
	IB_WINK_WAYEW_INFINIBAND,
	IB_WINK_WAYEW_ETHEWNET,
};

enum ib_device_cap_fwags {
	IB_DEVICE_WESIZE_MAX_WW = IB_UVEWBS_DEVICE_WESIZE_MAX_WW,
	IB_DEVICE_BAD_PKEY_CNTW = IB_UVEWBS_DEVICE_BAD_PKEY_CNTW,
	IB_DEVICE_BAD_QKEY_CNTW = IB_UVEWBS_DEVICE_BAD_QKEY_CNTW,
	IB_DEVICE_WAW_MUWTI = IB_UVEWBS_DEVICE_WAW_MUWTI,
	IB_DEVICE_AUTO_PATH_MIG = IB_UVEWBS_DEVICE_AUTO_PATH_MIG,
	IB_DEVICE_CHANGE_PHY_POWT = IB_UVEWBS_DEVICE_CHANGE_PHY_POWT,
	IB_DEVICE_UD_AV_POWT_ENFOWCE = IB_UVEWBS_DEVICE_UD_AV_POWT_ENFOWCE,
	IB_DEVICE_CUWW_QP_STATE_MOD = IB_UVEWBS_DEVICE_CUWW_QP_STATE_MOD,
	IB_DEVICE_SHUTDOWN_POWT = IB_UVEWBS_DEVICE_SHUTDOWN_POWT,
	/* IB_DEVICE_INIT_TYPE = IB_UVEWBS_DEVICE_INIT_TYPE, (not in use) */
	IB_DEVICE_POWT_ACTIVE_EVENT = IB_UVEWBS_DEVICE_POWT_ACTIVE_EVENT,
	IB_DEVICE_SYS_IMAGE_GUID = IB_UVEWBS_DEVICE_SYS_IMAGE_GUID,
	IB_DEVICE_WC_WNW_NAK_GEN = IB_UVEWBS_DEVICE_WC_WNW_NAK_GEN,
	IB_DEVICE_SWQ_WESIZE = IB_UVEWBS_DEVICE_SWQ_WESIZE,
	IB_DEVICE_N_NOTIFY_CQ = IB_UVEWBS_DEVICE_N_NOTIFY_CQ,

	/* Wesewved, owd SEND_W_INV = 1 << 16,*/
	IB_DEVICE_MEM_WINDOW = IB_UVEWBS_DEVICE_MEM_WINDOW,
	/*
	 * Devices shouwd set IB_DEVICE_UD_IP_SUM if they suppowt
	 * insewtion of UDP and TCP checksum on outgoing UD IPoIB
	 * messages and can vewify the vawidity of checksum fow
	 * incoming messages.  Setting this fwag impwies that the
	 * IPoIB dwivew may set NETIF_F_IP_CSUM fow datagwam mode.
	 */
	IB_DEVICE_UD_IP_CSUM = IB_UVEWBS_DEVICE_UD_IP_CSUM,
	IB_DEVICE_XWC = IB_UVEWBS_DEVICE_XWC,

	/*
	 * This device suppowts the IB "base memowy management extension",
	 * which incwudes suppowt fow fast wegistwations (IB_WW_WEG_MW,
	 * IB_WW_WOCAW_INV and IB_WW_SEND_WITH_INV vewbs).  This fwag shouwd
	 * awso be set by any iWawp device which must suppowt FWs to compwy
	 * to the iWawp vewbs spec.  iWawp devices awso suppowt the
	 * IB_WW_WDMA_WEAD_WITH_INV vewb fow WDMA WEADs that invawidate the
	 * stag.
	 */
	IB_DEVICE_MEM_MGT_EXTENSIONS = IB_UVEWBS_DEVICE_MEM_MGT_EXTENSIONS,
	IB_DEVICE_MEM_WINDOW_TYPE_2A = IB_UVEWBS_DEVICE_MEM_WINDOW_TYPE_2A,
	IB_DEVICE_MEM_WINDOW_TYPE_2B = IB_UVEWBS_DEVICE_MEM_WINDOW_TYPE_2B,
	IB_DEVICE_WC_IP_CSUM = IB_UVEWBS_DEVICE_WC_IP_CSUM,
	/* Depwecated. Pwease use IB_WAW_PACKET_CAP_IP_CSUM. */
	IB_DEVICE_WAW_IP_CSUM = IB_UVEWBS_DEVICE_WAW_IP_CSUM,
	IB_DEVICE_MANAGED_FWOW_STEEWING =
		IB_UVEWBS_DEVICE_MANAGED_FWOW_STEEWING,
	/* Depwecated. Pwease use IB_WAW_PACKET_CAP_SCATTEW_FCS. */
	IB_DEVICE_WAW_SCATTEW_FCS = IB_UVEWBS_DEVICE_WAW_SCATTEW_FCS,
	/* The device suppowts padding incoming wwites to cachewine. */
	IB_DEVICE_PCI_WWITE_END_PADDING =
		IB_UVEWBS_DEVICE_PCI_WWITE_END_PADDING,
	/* Pwacement type attwibutes */
	IB_DEVICE_FWUSH_GWOBAW = IB_UVEWBS_DEVICE_FWUSH_GWOBAW,
	IB_DEVICE_FWUSH_PEWSISTENT = IB_UVEWBS_DEVICE_FWUSH_PEWSISTENT,
	IB_DEVICE_ATOMIC_WWITE = IB_UVEWBS_DEVICE_ATOMIC_WWITE,
};

enum ib_kewnew_cap_fwags {
	/*
	 * This device suppowts a pew-device wkey ow stag that can be
	 * used without pewfowming a memowy wegistwation fow the wocaw
	 * memowy.  Note that UWPs shouwd nevew check this fwag, but
	 * instead of use the wocaw_dma_wkey fwag in the ib_pd stwuctuwe,
	 * which wiww awways contain a usabwe wkey.
	 */
	IBK_WOCAW_DMA_WKEY = 1 << 0,
	/* IB_QP_CWEATE_INTEGWITY_EN is suppowted to impwement T10-PI */
	IBK_INTEGWITY_HANDOVEW = 1 << 1,
	/* IB_ACCESS_ON_DEMAND is suppowted duwing weg_usew_mw() */
	IBK_ON_DEMAND_PAGING = 1 << 2,
	/* IB_MW_TYPE_SG_GAPS is suppowted */
	IBK_SG_GAPS_WEG = 1 << 3,
	/* Dwivew suppowts WDMA_NWDEV_CMD_DEWWINK */
	IBK_AWWOW_USEW_UNWEG = 1 << 4,

	/* ipoib wiww use IB_QP_CWEATE_BWOCK_MUWTICAST_WOOPBACK */
	IBK_BWOCK_MUWTICAST_WOOPBACK = 1 << 5,
	/* iopib wiww use IB_QP_CWEATE_IPOIB_UD_WSO fow its QPs */
	IBK_UD_TSO = 1 << 6,
	/* iopib wiww use the device ops:
	 *   get_vf_config
	 *   get_vf_guid
	 *   get_vf_stats
	 *   set_vf_guid
	 *   set_vf_wink_state
	 */
	IBK_VIWTUAW_FUNCTION = 1 << 7,
	/* ipoib wiww use IB_QP_CWEATE_NETDEV_USE fow its QPs */
	IBK_WDMA_NETDEV_OPA = 1 << 8,
};

enum ib_atomic_cap {
	IB_ATOMIC_NONE,
	IB_ATOMIC_HCA,
	IB_ATOMIC_GWOB
};

enum ib_odp_genewaw_cap_bits {
	IB_ODP_SUPPOWT		= 1 << 0,
	IB_ODP_SUPPOWT_IMPWICIT = 1 << 1,
};

enum ib_odp_twanspowt_cap_bits {
	IB_ODP_SUPPOWT_SEND	= 1 << 0,
	IB_ODP_SUPPOWT_WECV	= 1 << 1,
	IB_ODP_SUPPOWT_WWITE	= 1 << 2,
	IB_ODP_SUPPOWT_WEAD	= 1 << 3,
	IB_ODP_SUPPOWT_ATOMIC	= 1 << 4,
	IB_ODP_SUPPOWT_SWQ_WECV	= 1 << 5,
};

stwuct ib_odp_caps {
	uint64_t genewaw_caps;
	stwuct {
		uint32_t  wc_odp_caps;
		uint32_t  uc_odp_caps;
		uint32_t  ud_odp_caps;
		uint32_t  xwc_odp_caps;
	} pew_twanspowt_caps;
};

stwuct ib_wss_caps {
	/* Cowwesponding bit wiww be set if qp type fwom
	 * 'enum ib_qp_type' is suppowted, e.g.
	 * suppowted_qpts |= 1 << IB_QPT_UD
	 */
	u32 suppowted_qpts;
	u32 max_wwq_indiwection_tabwes;
	u32 max_wwq_indiwection_tabwe_size;
};

enum ib_tm_cap_fwags {
	/*  Suppowt tag matching with wendezvous offwoad fow WC twanspowt */
	IB_TM_CAP_WNDV_WC = 1 << 0,
};

stwuct ib_tm_caps {
	/* Max size of WNDV headew */
	u32 max_wndv_hdw_size;
	/* Max numbew of entwies in tag matching wist */
	u32 max_num_tags;
	/* Fwom enum ib_tm_cap_fwags */
	u32 fwags;
	/* Max numbew of outstanding wist opewations */
	u32 max_ops;
	/* Max numbew of SGE in tag matching entwy */
	u32 max_sge;
};

stwuct ib_cq_init_attw {
	unsigned int	cqe;
	u32		comp_vectow;
	u32		fwags;
};

enum ib_cq_attw_mask {
	IB_CQ_MODEWATE = 1 << 0,
};

stwuct ib_cq_caps {
	u16     max_cq_modewation_count;
	u16     max_cq_modewation_pewiod;
};

stwuct ib_dm_mw_attw {
	u64		wength;
	u64		offset;
	u32		access_fwags;
};

stwuct ib_dm_awwoc_attw {
	u64	wength;
	u32	awignment;
	u32	fwags;
};

stwuct ib_device_attw {
	u64			fw_vew;
	__be64			sys_image_guid;
	u64			max_mw_size;
	u64			page_size_cap;
	u32			vendow_id;
	u32			vendow_pawt_id;
	u32			hw_vew;
	int			max_qp;
	int			max_qp_ww;
	u64			device_cap_fwags;
	u64			kewnew_cap_fwags;
	int			max_send_sge;
	int			max_wecv_sge;
	int			max_sge_wd;
	int			max_cq;
	int			max_cqe;
	int			max_mw;
	int			max_pd;
	int			max_qp_wd_atom;
	int			max_ee_wd_atom;
	int			max_wes_wd_atom;
	int			max_qp_init_wd_atom;
	int			max_ee_init_wd_atom;
	enum ib_atomic_cap	atomic_cap;
	enum ib_atomic_cap	masked_atomic_cap;
	int			max_ee;
	int			max_wdd;
	int			max_mw;
	int			max_waw_ipv6_qp;
	int			max_waw_ethy_qp;
	int			max_mcast_gwp;
	int			max_mcast_qp_attach;
	int			max_totaw_mcast_qp_attach;
	int			max_ah;
	int			max_swq;
	int			max_swq_ww;
	int			max_swq_sge;
	unsigned int		max_fast_weg_page_wist_wen;
	unsigned int		max_pi_fast_weg_page_wist_wen;
	u16			max_pkeys;
	u8			wocaw_ca_ack_deway;
	int			sig_pwot_cap;
	int			sig_guawd_cap;
	stwuct ib_odp_caps	odp_caps;
	uint64_t		timestamp_mask;
	uint64_t		hca_cowe_cwock; /* in KHZ */
	stwuct ib_wss_caps	wss_caps;
	u32			max_wq_type_wq;
	u32			waw_packet_caps; /* Use ib_waw_packet_caps enum */
	stwuct ib_tm_caps	tm_caps;
	stwuct ib_cq_caps       cq_caps;
	u64			max_dm_size;
	/* Max entwies fow sgw fow optimized pewfowmance pew WEAD */
	u32			max_sgw_wd;
};

enum ib_mtu {
	IB_MTU_256  = 1,
	IB_MTU_512  = 2,
	IB_MTU_1024 = 3,
	IB_MTU_2048 = 4,
	IB_MTU_4096 = 5
};

enum opa_mtu {
	OPA_MTU_8192 = 6,
	OPA_MTU_10240 = 7
};

static inwine int ib_mtu_enum_to_int(enum ib_mtu mtu)
{
	switch (mtu) {
	case IB_MTU_256:  wetuwn  256;
	case IB_MTU_512:  wetuwn  512;
	case IB_MTU_1024: wetuwn 1024;
	case IB_MTU_2048: wetuwn 2048;
	case IB_MTU_4096: wetuwn 4096;
	defauwt: 	  wetuwn -1;
	}
}

static inwine enum ib_mtu ib_mtu_int_to_enum(int mtu)
{
	if (mtu >= 4096)
		wetuwn IB_MTU_4096;
	ewse if (mtu >= 2048)
		wetuwn IB_MTU_2048;
	ewse if (mtu >= 1024)
		wetuwn IB_MTU_1024;
	ewse if (mtu >= 512)
		wetuwn IB_MTU_512;
	ewse
		wetuwn IB_MTU_256;
}

static inwine int opa_mtu_enum_to_int(enum opa_mtu mtu)
{
	switch (mtu) {
	case OPA_MTU_8192:
		wetuwn 8192;
	case OPA_MTU_10240:
		wetuwn 10240;
	defauwt:
		wetuwn(ib_mtu_enum_to_int((enum ib_mtu)mtu));
	}
}

static inwine enum opa_mtu opa_mtu_int_to_enum(int mtu)
{
	if (mtu >= 10240)
		wetuwn OPA_MTU_10240;
	ewse if (mtu >= 8192)
		wetuwn OPA_MTU_8192;
	ewse
		wetuwn ((enum opa_mtu)ib_mtu_int_to_enum(mtu));
}

enum ib_powt_state {
	IB_POWT_NOP		= 0,
	IB_POWT_DOWN		= 1,
	IB_POWT_INIT		= 2,
	IB_POWT_AWMED		= 3,
	IB_POWT_ACTIVE		= 4,
	IB_POWT_ACTIVE_DEFEW	= 5
};

enum ib_powt_phys_state {
	IB_POWT_PHYS_STATE_SWEEP = 1,
	IB_POWT_PHYS_STATE_POWWING = 2,
	IB_POWT_PHYS_STATE_DISABWED = 3,
	IB_POWT_PHYS_STATE_POWT_CONFIGUWATION_TWAINING = 4,
	IB_POWT_PHYS_STATE_WINK_UP = 5,
	IB_POWT_PHYS_STATE_WINK_EWWOW_WECOVEWY = 6,
	IB_POWT_PHYS_STATE_PHY_TEST = 7,
};

enum ib_powt_width {
	IB_WIDTH_1X	= 1,
	IB_WIDTH_2X	= 16,
	IB_WIDTH_4X	= 2,
	IB_WIDTH_8X	= 4,
	IB_WIDTH_12X	= 8
};

static inwine int ib_width_enum_to_int(enum ib_powt_width width)
{
	switch (width) {
	case IB_WIDTH_1X:  wetuwn  1;
	case IB_WIDTH_2X:  wetuwn  2;
	case IB_WIDTH_4X:  wetuwn  4;
	case IB_WIDTH_8X:  wetuwn  8;
	case IB_WIDTH_12X: wetuwn 12;
	defauwt: 	  wetuwn -1;
	}
}

enum ib_powt_speed {
	IB_SPEED_SDW	= 1,
	IB_SPEED_DDW	= 2,
	IB_SPEED_QDW	= 4,
	IB_SPEED_FDW10	= 8,
	IB_SPEED_FDW	= 16,
	IB_SPEED_EDW	= 32,
	IB_SPEED_HDW	= 64,
	IB_SPEED_NDW	= 128,
	IB_SPEED_XDW	= 256,
};

enum ib_stat_fwag {
	IB_STAT_FWAG_OPTIONAW = 1 << 0,
};

/**
 * stwuct wdma_stat_desc
 * @name - The name of the countew
 * @fwags - Fwags of the countew; Fow exampwe, IB_STAT_FWAG_OPTIONAW
 * @pwiv - Dwivew pwivate infowmation; Cowe code shouwd not use
 */
stwuct wdma_stat_desc {
	const chaw *name;
	unsigned int fwags;
	const void *pwiv;
};

/**
 * stwuct wdma_hw_stats
 * @wock - Mutex to pwotect pawawwew wwite access to wifespan and vawues
 *    of countews, which awe 64bits and not guawanteed to be wwitten
 *    atomicawy on 32bits systems.
 * @timestamp - Used by the cowe code to twack when the wast update was
 * @wifespan - Used by the cowe code to detewmine how owd the countews
 *   shouwd be befowe being updated again.  Stowed in jiffies, defauwts
 *   to 10 miwwiseconds, dwivews can ovewwide the defauwt be specifying
 *   theiw own vawue duwing theiw awwocation woutine.
 * @descs - Awway of pointews to static descwiptows used fow the countews
 *   in diwectowy.
 * @is_disabwed - A bitmap to indicate each countew is cuwwentwy disabwed
 *   ow not.
 * @num_countews - How many hawdwawe countews thewe awe.  If name is
 *   showtew than this numbew, a kewnew oops wiww wesuwt.  Dwivew authows
 *   awe encouwaged to weave BUIWD_BUG_ON(AWWAY_SIZE(@name) < num_countews)
 *   in theiw code to pwevent this.
 * @vawue - Awway of u64 countews that awe accessed by the sysfs code and
 *   fiwwed in by the dwivews get_stats woutine
 */
stwuct wdma_hw_stats {
	stwuct mutex	wock; /* Pwotect wifespan and vawues[] */
	unsigned wong	timestamp;
	unsigned wong	wifespan;
	const stwuct wdma_stat_desc *descs;
	unsigned wong	*is_disabwed;
	int		num_countews;
	u64		vawue[] __counted_by(num_countews);
};

#define WDMA_HW_STATS_DEFAUWT_WIFESPAN 10

stwuct wdma_hw_stats *wdma_awwoc_hw_stats_stwuct(
	const stwuct wdma_stat_desc *descs, int num_countews,
	unsigned wong wifespan);

void wdma_fwee_hw_stats_stwuct(stwuct wdma_hw_stats *stats);

/* Define bits fow the vawious functionawity this powt needs to be suppowted by
 * the cowe.
 */
/* Management                           0x00000FFF */
#define WDMA_COWE_CAP_IB_MAD            0x00000001
#define WDMA_COWE_CAP_IB_SMI            0x00000002
#define WDMA_COWE_CAP_IB_CM             0x00000004
#define WDMA_COWE_CAP_IW_CM             0x00000008
#define WDMA_COWE_CAP_IB_SA             0x00000010
#define WDMA_COWE_CAP_OPA_MAD           0x00000020

/* Addwess fowmat                       0x000FF000 */
#define WDMA_COWE_CAP_AF_IB             0x00001000
#define WDMA_COWE_CAP_ETH_AH            0x00002000
#define WDMA_COWE_CAP_OPA_AH            0x00004000
#define WDMA_COWE_CAP_IB_GWH_WEQUIWED   0x00008000

/* Pwotocow                             0xFFF00000 */
#define WDMA_COWE_CAP_PWOT_IB           0x00100000
#define WDMA_COWE_CAP_PWOT_WOCE         0x00200000
#define WDMA_COWE_CAP_PWOT_IWAWP        0x00400000
#define WDMA_COWE_CAP_PWOT_WOCE_UDP_ENCAP 0x00800000
#define WDMA_COWE_CAP_PWOT_WAW_PACKET   0x01000000
#define WDMA_COWE_CAP_PWOT_USNIC        0x02000000

#define WDMA_COWE_POWT_IB_GWH_WEQUIWED (WDMA_COWE_CAP_IB_GWH_WEQUIWED \
					| WDMA_COWE_CAP_PWOT_WOCE     \
					| WDMA_COWE_CAP_PWOT_WOCE_UDP_ENCAP)

#define WDMA_COWE_POWT_IBA_IB          (WDMA_COWE_CAP_PWOT_IB  \
					| WDMA_COWE_CAP_IB_MAD \
					| WDMA_COWE_CAP_IB_SMI \
					| WDMA_COWE_CAP_IB_CM  \
					| WDMA_COWE_CAP_IB_SA  \
					| WDMA_COWE_CAP_AF_IB)
#define WDMA_COWE_POWT_IBA_WOCE        (WDMA_COWE_CAP_PWOT_WOCE \
					| WDMA_COWE_CAP_IB_MAD  \
					| WDMA_COWE_CAP_IB_CM   \
					| WDMA_COWE_CAP_AF_IB   \
					| WDMA_COWE_CAP_ETH_AH)
#define WDMA_COWE_POWT_IBA_WOCE_UDP_ENCAP			\
					(WDMA_COWE_CAP_PWOT_WOCE_UDP_ENCAP \
					| WDMA_COWE_CAP_IB_MAD  \
					| WDMA_COWE_CAP_IB_CM   \
					| WDMA_COWE_CAP_AF_IB   \
					| WDMA_COWE_CAP_ETH_AH)
#define WDMA_COWE_POWT_IWAWP           (WDMA_COWE_CAP_PWOT_IWAWP \
					| WDMA_COWE_CAP_IW_CM)
#define WDMA_COWE_POWT_INTEW_OPA       (WDMA_COWE_POWT_IBA_IB  \
					| WDMA_COWE_CAP_OPA_MAD)

#define WDMA_COWE_POWT_WAW_PACKET	(WDMA_COWE_CAP_PWOT_WAW_PACKET)

#define WDMA_COWE_POWT_USNIC		(WDMA_COWE_CAP_PWOT_USNIC)

stwuct ib_powt_attw {
	u64			subnet_pwefix;
	enum ib_powt_state	state;
	enum ib_mtu		max_mtu;
	enum ib_mtu		active_mtu;
	u32                     phys_mtu;
	int			gid_tbw_wen;
	unsigned int		ip_gids:1;
	/* This is the vawue fwom PowtInfo CapabiwityMask, defined by IBA */
	u32			powt_cap_fwags;
	u32			max_msg_sz;
	u32			bad_pkey_cntw;
	u32			qkey_viow_cntw;
	u16			pkey_tbw_wen;
	u32			sm_wid;
	u32			wid;
	u8			wmc;
	u8			max_vw_num;
	u8			sm_sw;
	u8			subnet_timeout;
	u8			init_type_wepwy;
	u8			active_width;
	u16			active_speed;
	u8                      phys_state;
	u16			powt_cap_fwags2;
};

enum ib_device_modify_fwags {
	IB_DEVICE_MODIFY_SYS_IMAGE_GUID	= 1 << 0,
	IB_DEVICE_MODIFY_NODE_DESC	= 1 << 1
};

#define IB_DEVICE_NODE_DESC_MAX 64

stwuct ib_device_modify {
	u64	sys_image_guid;
	chaw	node_desc[IB_DEVICE_NODE_DESC_MAX];
};

enum ib_powt_modify_fwags {
	IB_POWT_SHUTDOWN		= 1,
	IB_POWT_INIT_TYPE		= (1<<2),
	IB_POWT_WESET_QKEY_CNTW		= (1<<3),
	IB_POWT_OPA_MASK_CHG		= (1<<4)
};

stwuct ib_powt_modify {
	u32	set_powt_cap_mask;
	u32	cww_powt_cap_mask;
	u8	init_type;
};

enum ib_event_type {
	IB_EVENT_CQ_EWW,
	IB_EVENT_QP_FATAW,
	IB_EVENT_QP_WEQ_EWW,
	IB_EVENT_QP_ACCESS_EWW,
	IB_EVENT_COMM_EST,
	IB_EVENT_SQ_DWAINED,
	IB_EVENT_PATH_MIG,
	IB_EVENT_PATH_MIG_EWW,
	IB_EVENT_DEVICE_FATAW,
	IB_EVENT_POWT_ACTIVE,
	IB_EVENT_POWT_EWW,
	IB_EVENT_WID_CHANGE,
	IB_EVENT_PKEY_CHANGE,
	IB_EVENT_SM_CHANGE,
	IB_EVENT_SWQ_EWW,
	IB_EVENT_SWQ_WIMIT_WEACHED,
	IB_EVENT_QP_WAST_WQE_WEACHED,
	IB_EVENT_CWIENT_WEWEGISTEW,
	IB_EVENT_GID_CHANGE,
	IB_EVENT_WQ_FATAW,
};

const chaw *__attwibute_const__ ib_event_msg(enum ib_event_type event);

stwuct ib_event {
	stwuct ib_device	*device;
	union {
		stwuct ib_cq	*cq;
		stwuct ib_qp	*qp;
		stwuct ib_swq	*swq;
		stwuct ib_wq	*wq;
		u32		powt_num;
	} ewement;
	enum ib_event_type	event;
};

stwuct ib_event_handwew {
	stwuct ib_device *device;
	void            (*handwew)(stwuct ib_event_handwew *, stwuct ib_event *);
	stwuct wist_head  wist;
};

#define INIT_IB_EVENT_HANDWEW(_ptw, _device, _handwew)		\
	do {							\
		(_ptw)->device  = _device;			\
		(_ptw)->handwew = _handwew;			\
		INIT_WIST_HEAD(&(_ptw)->wist);			\
	} whiwe (0)

stwuct ib_gwobaw_woute {
	const stwuct ib_gid_attw *sgid_attw;
	union ib_gid	dgid;
	u32		fwow_wabew;
	u8		sgid_index;
	u8		hop_wimit;
	u8		twaffic_cwass;
};

stwuct ib_gwh {
	__be32		vewsion_tcwass_fwow;
	__be16		paywen;
	u8		next_hdw;
	u8		hop_wimit;
	union ib_gid	sgid;
	union ib_gid	dgid;
};

union wdma_netwowk_hdw {
	stwuct ib_gwh ibgwh;
	stwuct {
		/* The IB spec states that if it's IPv4, the headew
		 * is wocated in the wast 20 bytes of the headew.
		 */
		u8		wesewved[20];
		stwuct iphdw	woce4gwh;
	};
};

#define IB_QPN_MASK		0xFFFFFF

enum {
	IB_MUWTICAST_QPN = 0xffffff
};

#define IB_WID_PEWMISSIVE	cpu_to_be16(0xFFFF)
#define IB_MUWTICAST_WID_BASE	cpu_to_be16(0xC000)

enum ib_ah_fwags {
	IB_AH_GWH	= 1
};

enum ib_wate {
	IB_WATE_POWT_CUWWENT = 0,
	IB_WATE_2_5_GBPS = 2,
	IB_WATE_5_GBPS   = 5,
	IB_WATE_10_GBPS  = 3,
	IB_WATE_20_GBPS  = 6,
	IB_WATE_30_GBPS  = 4,
	IB_WATE_40_GBPS  = 7,
	IB_WATE_60_GBPS  = 8,
	IB_WATE_80_GBPS  = 9,
	IB_WATE_120_GBPS = 10,
	IB_WATE_14_GBPS  = 11,
	IB_WATE_56_GBPS  = 12,
	IB_WATE_112_GBPS = 13,
	IB_WATE_168_GBPS = 14,
	IB_WATE_25_GBPS  = 15,
	IB_WATE_100_GBPS = 16,
	IB_WATE_200_GBPS = 17,
	IB_WATE_300_GBPS = 18,
	IB_WATE_28_GBPS  = 19,
	IB_WATE_50_GBPS  = 20,
	IB_WATE_400_GBPS = 21,
	IB_WATE_600_GBPS = 22,
	IB_WATE_800_GBPS = 23,
};

/**
 * ib_wate_to_muwt - Convewt the IB wate enum to a muwtipwe of the
 * base wate of 2.5 Gbit/sec.  Fow exampwe, IB_WATE_5_GBPS wiww be
 * convewted to 2, since 5 Gbit/sec is 2 * 2.5 Gbit/sec.
 * @wate: wate to convewt.
 */
__attwibute_const__ int ib_wate_to_muwt(enum ib_wate wate);

/**
 * ib_wate_to_mbps - Convewt the IB wate enum to Mbps.
 * Fow exampwe, IB_WATE_2_5_GBPS wiww be convewted to 2500.
 * @wate: wate to convewt.
 */
__attwibute_const__ int ib_wate_to_mbps(enum ib_wate wate);


/**
 * enum ib_mw_type - memowy wegion type
 * @IB_MW_TYPE_MEM_WEG:       memowy wegion that is used fow
 *                            nowmaw wegistwation
 * @IB_MW_TYPE_SG_GAPS:       memowy wegion that is capabwe to
 *                            wegistew any awbitwawy sg wists (without
 *                            the nowmaw mw constwaints - see
 *                            ib_map_mw_sg)
 * @IB_MW_TYPE_DM:            memowy wegion that is used fow device
 *                            memowy wegistwation
 * @IB_MW_TYPE_USEW:          memowy wegion that is used fow the usew-space
 *                            appwication
 * @IB_MW_TYPE_DMA:           memowy wegion that is used fow DMA opewations
 *                            without addwess twanswations (VA=PA)
 * @IB_MW_TYPE_INTEGWITY:     memowy wegion that is used fow
 *                            data integwity opewations
 */
enum ib_mw_type {
	IB_MW_TYPE_MEM_WEG,
	IB_MW_TYPE_SG_GAPS,
	IB_MW_TYPE_DM,
	IB_MW_TYPE_USEW,
	IB_MW_TYPE_DMA,
	IB_MW_TYPE_INTEGWITY,
};

enum ib_mw_status_check {
	IB_MW_CHECK_SIG_STATUS = 1,
};

/**
 * stwuct ib_mw_status - Memowy wegion status containew
 *
 * @faiw_status: Bitmask of MW checks status. Fow each
 *     faiwed check a cowwesponding status bit is set.
 * @sig_eww: Additionaw info fow IB_MW_CEHCK_SIG_STATUS
 *     faiwuwe.
 */
stwuct ib_mw_status {
	u32		    faiw_status;
	stwuct ib_sig_eww   sig_eww;
};

/**
 * muwt_to_ib_wate - Convewt a muwtipwe of 2.5 Gbit/sec to an IB wate
 * enum.
 * @muwt: muwtipwe to convewt.
 */
__attwibute_const__ enum ib_wate muwt_to_ib_wate(int muwt);

stwuct wdma_ah_init_attw {
	stwuct wdma_ah_attw *ah_attw;
	u32 fwags;
	stwuct net_device *xmit_swave;
};

enum wdma_ah_attw_type {
	WDMA_AH_ATTW_TYPE_UNDEFINED,
	WDMA_AH_ATTW_TYPE_IB,
	WDMA_AH_ATTW_TYPE_WOCE,
	WDMA_AH_ATTW_TYPE_OPA,
};

stwuct ib_ah_attw {
	u16			dwid;
	u8			swc_path_bits;
};

stwuct woce_ah_attw {
	u8			dmac[ETH_AWEN];
};

stwuct opa_ah_attw {
	u32			dwid;
	u8			swc_path_bits;
	boow			make_gwd;
};

stwuct wdma_ah_attw {
	stwuct ib_gwobaw_woute	gwh;
	u8			sw;
	u8			static_wate;
	u32			powt_num;
	u8			ah_fwags;
	enum wdma_ah_attw_type type;
	union {
		stwuct ib_ah_attw ib;
		stwuct woce_ah_attw woce;
		stwuct opa_ah_attw opa;
	};
};

enum ib_wc_status {
	IB_WC_SUCCESS,
	IB_WC_WOC_WEN_EWW,
	IB_WC_WOC_QP_OP_EWW,
	IB_WC_WOC_EEC_OP_EWW,
	IB_WC_WOC_PWOT_EWW,
	IB_WC_WW_FWUSH_EWW,
	IB_WC_MW_BIND_EWW,
	IB_WC_BAD_WESP_EWW,
	IB_WC_WOC_ACCESS_EWW,
	IB_WC_WEM_INV_WEQ_EWW,
	IB_WC_WEM_ACCESS_EWW,
	IB_WC_WEM_OP_EWW,
	IB_WC_WETWY_EXC_EWW,
	IB_WC_WNW_WETWY_EXC_EWW,
	IB_WC_WOC_WDD_VIOW_EWW,
	IB_WC_WEM_INV_WD_WEQ_EWW,
	IB_WC_WEM_ABOWT_EWW,
	IB_WC_INV_EECN_EWW,
	IB_WC_INV_EEC_STATE_EWW,
	IB_WC_FATAW_EWW,
	IB_WC_WESP_TIMEOUT_EWW,
	IB_WC_GENEWAW_EWW
};

const chaw *__attwibute_const__ ib_wc_status_msg(enum ib_wc_status status);

enum ib_wc_opcode {
	IB_WC_SEND = IB_UVEWBS_WC_SEND,
	IB_WC_WDMA_WWITE = IB_UVEWBS_WC_WDMA_WWITE,
	IB_WC_WDMA_WEAD = IB_UVEWBS_WC_WDMA_WEAD,
	IB_WC_COMP_SWAP = IB_UVEWBS_WC_COMP_SWAP,
	IB_WC_FETCH_ADD = IB_UVEWBS_WC_FETCH_ADD,
	IB_WC_BIND_MW = IB_UVEWBS_WC_BIND_MW,
	IB_WC_WOCAW_INV = IB_UVEWBS_WC_WOCAW_INV,
	IB_WC_WSO = IB_UVEWBS_WC_TSO,
	IB_WC_ATOMIC_WWITE = IB_UVEWBS_WC_ATOMIC_WWITE,
	IB_WC_WEG_MW,
	IB_WC_MASKED_COMP_SWAP,
	IB_WC_MASKED_FETCH_ADD,
	IB_WC_FWUSH = IB_UVEWBS_WC_FWUSH,
/*
 * Set vawue of IB_WC_WECV so consumews can test if a compwetion is a
 * weceive by testing (opcode & IB_WC_WECV).
 */
	IB_WC_WECV			= 1 << 7,
	IB_WC_WECV_WDMA_WITH_IMM
};

enum ib_wc_fwags {
	IB_WC_GWH		= 1,
	IB_WC_WITH_IMM		= (1<<1),
	IB_WC_WITH_INVAWIDATE	= (1<<2),
	IB_WC_IP_CSUM_OK	= (1<<3),
	IB_WC_WITH_SMAC		= (1<<4),
	IB_WC_WITH_VWAN		= (1<<5),
	IB_WC_WITH_NETWOWK_HDW_TYPE	= (1<<6),
};

stwuct ib_wc {
	union {
		u64		ww_id;
		stwuct ib_cqe	*ww_cqe;
	};
	enum ib_wc_status	status;
	enum ib_wc_opcode	opcode;
	u32			vendow_eww;
	u32			byte_wen;
	stwuct ib_qp	       *qp;
	union {
		__be32		imm_data;
		u32		invawidate_wkey;
	} ex;
	u32			swc_qp;
	u32			swid;
	int			wc_fwags;
	u16			pkey_index;
	u8			sw;
	u8			dwid_path_bits;
	u32 powt_num; /* vawid onwy fow DW SMPs on switches */
	u8			smac[ETH_AWEN];
	u16			vwan_id;
	u8			netwowk_hdw_type;
};

enum ib_cq_notify_fwags {
	IB_CQ_SOWICITED			= 1 << 0,
	IB_CQ_NEXT_COMP			= 1 << 1,
	IB_CQ_SOWICITED_MASK		= IB_CQ_SOWICITED | IB_CQ_NEXT_COMP,
	IB_CQ_WEPOWT_MISSED_EVENTS	= 1 << 2,
};

enum ib_swq_type {
	IB_SWQT_BASIC = IB_UVEWBS_SWQT_BASIC,
	IB_SWQT_XWC = IB_UVEWBS_SWQT_XWC,
	IB_SWQT_TM = IB_UVEWBS_SWQT_TM,
};

static inwine boow ib_swq_has_cq(enum ib_swq_type swq_type)
{
	wetuwn swq_type == IB_SWQT_XWC ||
	       swq_type == IB_SWQT_TM;
}

enum ib_swq_attw_mask {
	IB_SWQ_MAX_WW	= 1 << 0,
	IB_SWQ_WIMIT	= 1 << 1,
};

stwuct ib_swq_attw {
	u32	max_ww;
	u32	max_sge;
	u32	swq_wimit;
};

stwuct ib_swq_init_attw {
	void		      (*event_handwew)(stwuct ib_event *, void *);
	void		       *swq_context;
	stwuct ib_swq_attw	attw;
	enum ib_swq_type	swq_type;

	stwuct {
		stwuct ib_cq   *cq;
		union {
			stwuct {
				stwuct ib_xwcd *xwcd;
			} xwc;

			stwuct {
				u32		max_num_tags;
			} tag_matching;
		};
	} ext;
};

stwuct ib_qp_cap {
	u32	max_send_ww;
	u32	max_wecv_ww;
	u32	max_send_sge;
	u32	max_wecv_sge;
	u32	max_inwine_data;

	/*
	 * Maximum numbew of wdma_ww_ctx stwuctuwes in fwight at a time.
	 * ib_cweate_qp() wiww cawcuwate the wight amount of needed WWs
	 * and MWs based on this.
	 */
	u32	max_wdma_ctxs;
};

enum ib_sig_type {
	IB_SIGNAW_AWW_WW,
	IB_SIGNAW_WEQ_WW
};

enum ib_qp_type {
	/*
	 * IB_QPT_SMI and IB_QPT_GSI have to be the fiwst two entwies
	 * hewe (and in that owdew) since the MAD wayew uses them as
	 * indices into a 2-entwy tabwe.
	 */
	IB_QPT_SMI,
	IB_QPT_GSI,

	IB_QPT_WC = IB_UVEWBS_QPT_WC,
	IB_QPT_UC = IB_UVEWBS_QPT_UC,
	IB_QPT_UD = IB_UVEWBS_QPT_UD,
	IB_QPT_WAW_IPV6,
	IB_QPT_WAW_ETHEWTYPE,
	IB_QPT_WAW_PACKET = IB_UVEWBS_QPT_WAW_PACKET,
	IB_QPT_XWC_INI = IB_UVEWBS_QPT_XWC_INI,
	IB_QPT_XWC_TGT = IB_UVEWBS_QPT_XWC_TGT,
	IB_QPT_MAX,
	IB_QPT_DWIVEW = IB_UVEWBS_QPT_DWIVEW,
	/* Wesewve a wange fow qp types intewnaw to the wow wevew dwivew.
	 * These qp types wiww not be visibwe at the IB cowe wayew, so the
	 * IB_QPT_MAX usages shouwd not be affected in the cowe wayew
	 */
	IB_QPT_WESEWVED1 = 0x1000,
	IB_QPT_WESEWVED2,
	IB_QPT_WESEWVED3,
	IB_QPT_WESEWVED4,
	IB_QPT_WESEWVED5,
	IB_QPT_WESEWVED6,
	IB_QPT_WESEWVED7,
	IB_QPT_WESEWVED8,
	IB_QPT_WESEWVED9,
	IB_QPT_WESEWVED10,
};

enum ib_qp_cweate_fwags {
	IB_QP_CWEATE_IPOIB_UD_WSO		= 1 << 0,
	IB_QP_CWEATE_BWOCK_MUWTICAST_WOOPBACK	=
		IB_UVEWBS_QP_CWEATE_BWOCK_MUWTICAST_WOOPBACK,
	IB_QP_CWEATE_CWOSS_CHANNEW              = 1 << 2,
	IB_QP_CWEATE_MANAGED_SEND               = 1 << 3,
	IB_QP_CWEATE_MANAGED_WECV               = 1 << 4,
	IB_QP_CWEATE_NETIF_QP			= 1 << 5,
	IB_QP_CWEATE_INTEGWITY_EN		= 1 << 6,
	IB_QP_CWEATE_NETDEV_USE			= 1 << 7,
	IB_QP_CWEATE_SCATTEW_FCS		=
		IB_UVEWBS_QP_CWEATE_SCATTEW_FCS,
	IB_QP_CWEATE_CVWAN_STWIPPING		=
		IB_UVEWBS_QP_CWEATE_CVWAN_STWIPPING,
	IB_QP_CWEATE_SOUWCE_QPN			= 1 << 10,
	IB_QP_CWEATE_PCI_WWITE_END_PADDING	=
		IB_UVEWBS_QP_CWEATE_PCI_WWITE_END_PADDING,
	/* wesewve bits 26-31 fow wow wevew dwivews' intewnaw use */
	IB_QP_CWEATE_WESEWVED_STAWT		= 1 << 26,
	IB_QP_CWEATE_WESEWVED_END		= 1 << 31,
};

/*
 * Note: usews may not caww ib_cwose_qp ow ib_destwoy_qp fwom the event_handwew
 * cawwback to destwoy the passed in QP.
 */

stwuct ib_qp_init_attw {
	/* This cawwback occuws in wowkqueue context */
	void                  (*event_handwew)(stwuct ib_event *, void *);

	void		       *qp_context;
	stwuct ib_cq	       *send_cq;
	stwuct ib_cq	       *wecv_cq;
	stwuct ib_swq	       *swq;
	stwuct ib_xwcd	       *xwcd;     /* XWC TGT QPs onwy */
	stwuct ib_qp_cap	cap;
	enum ib_sig_type	sq_sig_type;
	enum ib_qp_type		qp_type;
	u32			cweate_fwags;

	/*
	 * Onwy needed fow speciaw QP types, ow when using the WW API.
	 */
	u32			powt_num;
	stwuct ib_wwq_ind_tabwe *wwq_ind_tbw;
	u32			souwce_qpn;
};

stwuct ib_qp_open_attw {
	void                  (*event_handwew)(stwuct ib_event *, void *);
	void		       *qp_context;
	u32			qp_num;
	enum ib_qp_type		qp_type;
};

enum ib_wnw_timeout {
	IB_WNW_TIMEW_655_36 =  0,
	IB_WNW_TIMEW_000_01 =  1,
	IB_WNW_TIMEW_000_02 =  2,
	IB_WNW_TIMEW_000_03 =  3,
	IB_WNW_TIMEW_000_04 =  4,
	IB_WNW_TIMEW_000_06 =  5,
	IB_WNW_TIMEW_000_08 =  6,
	IB_WNW_TIMEW_000_12 =  7,
	IB_WNW_TIMEW_000_16 =  8,
	IB_WNW_TIMEW_000_24 =  9,
	IB_WNW_TIMEW_000_32 = 10,
	IB_WNW_TIMEW_000_48 = 11,
	IB_WNW_TIMEW_000_64 = 12,
	IB_WNW_TIMEW_000_96 = 13,
	IB_WNW_TIMEW_001_28 = 14,
	IB_WNW_TIMEW_001_92 = 15,
	IB_WNW_TIMEW_002_56 = 16,
	IB_WNW_TIMEW_003_84 = 17,
	IB_WNW_TIMEW_005_12 = 18,
	IB_WNW_TIMEW_007_68 = 19,
	IB_WNW_TIMEW_010_24 = 20,
	IB_WNW_TIMEW_015_36 = 21,
	IB_WNW_TIMEW_020_48 = 22,
	IB_WNW_TIMEW_030_72 = 23,
	IB_WNW_TIMEW_040_96 = 24,
	IB_WNW_TIMEW_061_44 = 25,
	IB_WNW_TIMEW_081_92 = 26,
	IB_WNW_TIMEW_122_88 = 27,
	IB_WNW_TIMEW_163_84 = 28,
	IB_WNW_TIMEW_245_76 = 29,
	IB_WNW_TIMEW_327_68 = 30,
	IB_WNW_TIMEW_491_52 = 31
};

enum ib_qp_attw_mask {
	IB_QP_STATE			= 1,
	IB_QP_CUW_STATE			= (1<<1),
	IB_QP_EN_SQD_ASYNC_NOTIFY	= (1<<2),
	IB_QP_ACCESS_FWAGS		= (1<<3),
	IB_QP_PKEY_INDEX		= (1<<4),
	IB_QP_POWT			= (1<<5),
	IB_QP_QKEY			= (1<<6),
	IB_QP_AV			= (1<<7),
	IB_QP_PATH_MTU			= (1<<8),
	IB_QP_TIMEOUT			= (1<<9),
	IB_QP_WETWY_CNT			= (1<<10),
	IB_QP_WNW_WETWY			= (1<<11),
	IB_QP_WQ_PSN			= (1<<12),
	IB_QP_MAX_QP_WD_ATOMIC		= (1<<13),
	IB_QP_AWT_PATH			= (1<<14),
	IB_QP_MIN_WNW_TIMEW		= (1<<15),
	IB_QP_SQ_PSN			= (1<<16),
	IB_QP_MAX_DEST_WD_ATOMIC	= (1<<17),
	IB_QP_PATH_MIG_STATE		= (1<<18),
	IB_QP_CAP			= (1<<19),
	IB_QP_DEST_QPN			= (1<<20),
	IB_QP_WESEWVED1			= (1<<21),
	IB_QP_WESEWVED2			= (1<<22),
	IB_QP_WESEWVED3			= (1<<23),
	IB_QP_WESEWVED4			= (1<<24),
	IB_QP_WATE_WIMIT		= (1<<25),

	IB_QP_ATTW_STANDAWD_BITS = GENMASK(20, 0),
};

enum ib_qp_state {
	IB_QPS_WESET,
	IB_QPS_INIT,
	IB_QPS_WTW,
	IB_QPS_WTS,
	IB_QPS_SQD,
	IB_QPS_SQE,
	IB_QPS_EWW
};

enum ib_mig_state {
	IB_MIG_MIGWATED,
	IB_MIG_WEAWM,
	IB_MIG_AWMED
};

enum ib_mw_type {
	IB_MW_TYPE_1 = 1,
	IB_MW_TYPE_2 = 2
};

stwuct ib_qp_attw {
	enum ib_qp_state	qp_state;
	enum ib_qp_state	cuw_qp_state;
	enum ib_mtu		path_mtu;
	enum ib_mig_state	path_mig_state;
	u32			qkey;
	u32			wq_psn;
	u32			sq_psn;
	u32			dest_qp_num;
	int			qp_access_fwags;
	stwuct ib_qp_cap	cap;
	stwuct wdma_ah_attw	ah_attw;
	stwuct wdma_ah_attw	awt_ah_attw;
	u16			pkey_index;
	u16			awt_pkey_index;
	u8			en_sqd_async_notify;
	u8			sq_dwaining;
	u8			max_wd_atomic;
	u8			max_dest_wd_atomic;
	u8			min_wnw_timew;
	u32			powt_num;
	u8			timeout;
	u8			wetwy_cnt;
	u8			wnw_wetwy;
	u32			awt_powt_num;
	u8			awt_timeout;
	u32			wate_wimit;
	stwuct net_device	*xmit_swave;
};

enum ib_ww_opcode {
	/* These awe shawed with usewspace */
	IB_WW_WDMA_WWITE = IB_UVEWBS_WW_WDMA_WWITE,
	IB_WW_WDMA_WWITE_WITH_IMM = IB_UVEWBS_WW_WDMA_WWITE_WITH_IMM,
	IB_WW_SEND = IB_UVEWBS_WW_SEND,
	IB_WW_SEND_WITH_IMM = IB_UVEWBS_WW_SEND_WITH_IMM,
	IB_WW_WDMA_WEAD = IB_UVEWBS_WW_WDMA_WEAD,
	IB_WW_ATOMIC_CMP_AND_SWP = IB_UVEWBS_WW_ATOMIC_CMP_AND_SWP,
	IB_WW_ATOMIC_FETCH_AND_ADD = IB_UVEWBS_WW_ATOMIC_FETCH_AND_ADD,
	IB_WW_BIND_MW = IB_UVEWBS_WW_BIND_MW,
	IB_WW_WSO = IB_UVEWBS_WW_TSO,
	IB_WW_SEND_WITH_INV = IB_UVEWBS_WW_SEND_WITH_INV,
	IB_WW_WDMA_WEAD_WITH_INV = IB_UVEWBS_WW_WDMA_WEAD_WITH_INV,
	IB_WW_WOCAW_INV = IB_UVEWBS_WW_WOCAW_INV,
	IB_WW_MASKED_ATOMIC_CMP_AND_SWP =
		IB_UVEWBS_WW_MASKED_ATOMIC_CMP_AND_SWP,
	IB_WW_MASKED_ATOMIC_FETCH_AND_ADD =
		IB_UVEWBS_WW_MASKED_ATOMIC_FETCH_AND_ADD,
	IB_WW_FWUSH = IB_UVEWBS_WW_FWUSH,
	IB_WW_ATOMIC_WWITE = IB_UVEWBS_WW_ATOMIC_WWITE,

	/* These awe kewnew onwy and can not be issued by usewspace */
	IB_WW_WEG_MW = 0x20,
	IB_WW_WEG_MW_INTEGWITY,

	/* wesewve vawues fow wow wevew dwivews' intewnaw use.
	 * These vawues wiww not be used at aww in the ib cowe wayew.
	 */
	IB_WW_WESEWVED1 = 0xf0,
	IB_WW_WESEWVED2,
	IB_WW_WESEWVED3,
	IB_WW_WESEWVED4,
	IB_WW_WESEWVED5,
	IB_WW_WESEWVED6,
	IB_WW_WESEWVED7,
	IB_WW_WESEWVED8,
	IB_WW_WESEWVED9,
	IB_WW_WESEWVED10,
};

enum ib_send_fwags {
	IB_SEND_FENCE		= 1,
	IB_SEND_SIGNAWED	= (1<<1),
	IB_SEND_SOWICITED	= (1<<2),
	IB_SEND_INWINE		= (1<<3),
	IB_SEND_IP_CSUM		= (1<<4),

	/* wesewve bits 26-31 fow wow wevew dwivews' intewnaw use */
	IB_SEND_WESEWVED_STAWT	= (1 << 26),
	IB_SEND_WESEWVED_END	= (1 << 31),
};

stwuct ib_sge {
	u64	addw;
	u32	wength;
	u32	wkey;
};

stwuct ib_cqe {
	void (*done)(stwuct ib_cq *cq, stwuct ib_wc *wc);
};

stwuct ib_send_ww {
	stwuct ib_send_ww      *next;
	union {
		u64		ww_id;
		stwuct ib_cqe	*ww_cqe;
	};
	stwuct ib_sge	       *sg_wist;
	int			num_sge;
	enum ib_ww_opcode	opcode;
	int			send_fwags;
	union {
		__be32		imm_data;
		u32		invawidate_wkey;
	} ex;
};

stwuct ib_wdma_ww {
	stwuct ib_send_ww	ww;
	u64			wemote_addw;
	u32			wkey;
};

static inwine const stwuct ib_wdma_ww *wdma_ww(const stwuct ib_send_ww *ww)
{
	wetuwn containew_of(ww, stwuct ib_wdma_ww, ww);
}

stwuct ib_atomic_ww {
	stwuct ib_send_ww	ww;
	u64			wemote_addw;
	u64			compawe_add;
	u64			swap;
	u64			compawe_add_mask;
	u64			swap_mask;
	u32			wkey;
};

static inwine const stwuct ib_atomic_ww *atomic_ww(const stwuct ib_send_ww *ww)
{
	wetuwn containew_of(ww, stwuct ib_atomic_ww, ww);
}

stwuct ib_ud_ww {
	stwuct ib_send_ww	ww;
	stwuct ib_ah		*ah;
	void			*headew;
	int			hwen;
	int			mss;
	u32			wemote_qpn;
	u32			wemote_qkey;
	u16			pkey_index; /* vawid fow GSI onwy */
	u32			powt_num; /* vawid fow DW SMPs on switch onwy */
};

static inwine const stwuct ib_ud_ww *ud_ww(const stwuct ib_send_ww *ww)
{
	wetuwn containew_of(ww, stwuct ib_ud_ww, ww);
}

stwuct ib_weg_ww {
	stwuct ib_send_ww	ww;
	stwuct ib_mw		*mw;
	u32			key;
	int			access;
};

static inwine const stwuct ib_weg_ww *weg_ww(const stwuct ib_send_ww *ww)
{
	wetuwn containew_of(ww, stwuct ib_weg_ww, ww);
}

stwuct ib_wecv_ww {
	stwuct ib_wecv_ww      *next;
	union {
		u64		ww_id;
		stwuct ib_cqe	*ww_cqe;
	};
	stwuct ib_sge	       *sg_wist;
	int			num_sge;
};

enum ib_access_fwags {
	IB_ACCESS_WOCAW_WWITE = IB_UVEWBS_ACCESS_WOCAW_WWITE,
	IB_ACCESS_WEMOTE_WWITE = IB_UVEWBS_ACCESS_WEMOTE_WWITE,
	IB_ACCESS_WEMOTE_WEAD = IB_UVEWBS_ACCESS_WEMOTE_WEAD,
	IB_ACCESS_WEMOTE_ATOMIC = IB_UVEWBS_ACCESS_WEMOTE_ATOMIC,
	IB_ACCESS_MW_BIND = IB_UVEWBS_ACCESS_MW_BIND,
	IB_ZEWO_BASED = IB_UVEWBS_ACCESS_ZEWO_BASED,
	IB_ACCESS_ON_DEMAND = IB_UVEWBS_ACCESS_ON_DEMAND,
	IB_ACCESS_HUGETWB = IB_UVEWBS_ACCESS_HUGETWB,
	IB_ACCESS_WEWAXED_OWDEWING = IB_UVEWBS_ACCESS_WEWAXED_OWDEWING,
	IB_ACCESS_FWUSH_GWOBAW = IB_UVEWBS_ACCESS_FWUSH_GWOBAW,
	IB_ACCESS_FWUSH_PEWSISTENT = IB_UVEWBS_ACCESS_FWUSH_PEWSISTENT,

	IB_ACCESS_OPTIONAW = IB_UVEWBS_ACCESS_OPTIONAW_WANGE,
	IB_ACCESS_SUPPOWTED =
		((IB_ACCESS_FWUSH_PEWSISTENT << 1) - 1) | IB_ACCESS_OPTIONAW,
};

/*
 * XXX: these awe appawentwy used fow ->weweg_usew_mw, no idea why they
 * awe hidden hewe instead of a uapi headew!
 */
enum ib_mw_weweg_fwags {
	IB_MW_WEWEG_TWANS	= 1,
	IB_MW_WEWEG_PD		= (1<<1),
	IB_MW_WEWEG_ACCESS	= (1<<2),
	IB_MW_WEWEG_SUPPOWTED	= ((IB_MW_WEWEG_ACCESS << 1) - 1)
};

stwuct ib_umem;

enum wdma_wemove_weason {
	/*
	 * Usewspace wequested uobject dewetion ow initiaw twy
	 * to wemove uobject via cweanup. Caww couwd faiw
	 */
	WDMA_WEMOVE_DESTWOY,
	/* Context dewetion. This caww shouwd dewete the actuaw object itsewf */
	WDMA_WEMOVE_CWOSE,
	/* Dwivew is being hot-unpwugged. This caww shouwd dewete the actuaw object itsewf */
	WDMA_WEMOVE_DWIVEW_WEMOVE,
	/* uobj is being cweaned-up befowe being committed */
	WDMA_WEMOVE_ABOWT,
	/* The dwivew faiwed to destwoy the uobject and is being disconnected */
	WDMA_WEMOVE_DWIVEW_FAIWUWE,
};

stwuct ib_wdmacg_object {
#ifdef CONFIG_CGWOUP_WDMA
	stwuct wdma_cgwoup	*cg;		/* ownew wdma cgwoup */
#endif
};

stwuct ib_ucontext {
	stwuct ib_device       *device;
	stwuct ib_uvewbs_fiwe  *ufiwe;

	stwuct ib_wdmacg_object	cg_obj;
	/*
	 * Impwementation detaiws of the WDMA cowe, don't use in dwivews:
	 */
	stwuct wdma_westwack_entwy wes;
	stwuct xawway mmap_xa;
};

stwuct ib_uobject {
	u64			usew_handwe;	/* handwe given to us by usewspace */
	/* ufiwe & ucontext owning this object */
	stwuct ib_uvewbs_fiwe  *ufiwe;
	/* FIXME, save memowy: ufiwe->context == context */
	stwuct ib_ucontext     *context;	/* associated usew context */
	void		       *object;		/* containing object */
	stwuct wist_head	wist;		/* wink to context's wist */
	stwuct ib_wdmacg_object	cg_obj;		/* wdmacg object */
	int			id;		/* index into kewnew idw */
	stwuct kwef		wef;
	atomic_t		usecnt;		/* pwotects excwusive access */
	stwuct wcu_head		wcu;		/* kfwee_wcu() ovewhead */

	const stwuct uvewbs_api_object *uapi_object;
};

stwuct ib_udata {
	const void __usew *inbuf;
	void __usew *outbuf;
	size_t       inwen;
	size_t       outwen;
};

stwuct ib_pd {
	u32			wocaw_dma_wkey;
	u32			fwags;
	stwuct ib_device       *device;
	stwuct ib_uobject      *uobject;
	atomic_t          	usecnt; /* count aww wesouwces */

	u32			unsafe_gwobaw_wkey;

	/*
	 * Impwementation detaiws of the WDMA cowe, don't use in dwivews:
	 */
	stwuct ib_mw	       *__intewnaw_mw;
	stwuct wdma_westwack_entwy wes;
};

stwuct ib_xwcd {
	stwuct ib_device       *device;
	atomic_t		usecnt; /* count aww exposed wesouwces */
	stwuct inode	       *inode;
	stwuct ww_semaphowe	tgt_qps_wwsem;
	stwuct xawway		tgt_qps;
};

stwuct ib_ah {
	stwuct ib_device	*device;
	stwuct ib_pd		*pd;
	stwuct ib_uobject	*uobject;
	const stwuct ib_gid_attw *sgid_attw;
	enum wdma_ah_attw_type	type;
};

typedef void (*ib_comp_handwew)(stwuct ib_cq *cq, void *cq_context);

enum ib_poww_context {
	IB_POWW_SOFTIWQ,	   /* poww fwom softiwq context */
	IB_POWW_WOWKQUEUE,	   /* poww fwom wowkqueue */
	IB_POWW_UNBOUND_WOWKQUEUE, /* poww fwom unbound wowkqueue */
	IB_POWW_WAST_POOW_TYPE = IB_POWW_UNBOUND_WOWKQUEUE,

	IB_POWW_DIWECT,		   /* cawwew context, no hw compwetions */
};

stwuct ib_cq {
	stwuct ib_device       *device;
	stwuct ib_ucq_object   *uobject;
	ib_comp_handwew   	comp_handwew;
	void                  (*event_handwew)(stwuct ib_event *, void *);
	void                   *cq_context;
	int               	cqe;
	unsigned int		cqe_used;
	atomic_t          	usecnt; /* count numbew of wowk queues */
	enum ib_poww_context	poww_ctx;
	stwuct ib_wc		*wc;
	stwuct wist_head        poow_entwy;
	union {
		stwuct iwq_poww		iop;
		stwuct wowk_stwuct	wowk;
	};
	stwuct wowkqueue_stwuct *comp_wq;
	stwuct dim *dim;

	/* updated onwy by twace points */
	ktime_t timestamp;
	u8 intewwupt:1;
	u8 shawed:1;
	unsigned int comp_vectow;

	/*
	 * Impwementation detaiws of the WDMA cowe, don't use in dwivews:
	 */
	stwuct wdma_westwack_entwy wes;
};

stwuct ib_swq {
	stwuct ib_device       *device;
	stwuct ib_pd	       *pd;
	stwuct ib_uswq_object  *uobject;
	void		      (*event_handwew)(stwuct ib_event *, void *);
	void		       *swq_context;
	enum ib_swq_type	swq_type;
	atomic_t		usecnt;

	stwuct {
		stwuct ib_cq   *cq;
		union {
			stwuct {
				stwuct ib_xwcd *xwcd;
				u32		swq_num;
			} xwc;
		};
	} ext;

	/*
	 * Impwementation detaiws of the WDMA cowe, don't use in dwivews:
	 */
	stwuct wdma_westwack_entwy wes;
};

enum ib_waw_packet_caps {
	/*
	 * Stwip cvwan fwom incoming packet and wepowt it in the matching wowk
	 * compwetion is suppowted.
	 */
	IB_WAW_PACKET_CAP_CVWAN_STWIPPING =
		IB_UVEWBS_WAW_PACKET_CAP_CVWAN_STWIPPING,
	/*
	 * Scattew FCS fiewd of an incoming packet to host memowy is suppowted.
	 */
	IB_WAW_PACKET_CAP_SCATTEW_FCS = IB_UVEWBS_WAW_PACKET_CAP_SCATTEW_FCS,
	/* Checksum offwoads awe suppowted (fow both send and weceive). */
	IB_WAW_PACKET_CAP_IP_CSUM = IB_UVEWBS_WAW_PACKET_CAP_IP_CSUM,
	/*
	 * When a packet is weceived fow an WQ with no weceive WQEs, the
	 * packet pwocessing is dewayed.
	 */
	IB_WAW_PACKET_CAP_DEWAY_DWOP = IB_UVEWBS_WAW_PACKET_CAP_DEWAY_DWOP,
};

enum ib_wq_type {
	IB_WQT_WQ = IB_UVEWBS_WQT_WQ,
};

enum ib_wq_state {
	IB_WQS_WESET,
	IB_WQS_WDY,
	IB_WQS_EWW
};

stwuct ib_wq {
	stwuct ib_device       *device;
	stwuct ib_uwq_object   *uobject;
	void		    *wq_context;
	void		    (*event_handwew)(stwuct ib_event *, void *);
	stwuct ib_pd	       *pd;
	stwuct ib_cq	       *cq;
	u32		wq_num;
	enum ib_wq_state       state;
	enum ib_wq_type	wq_type;
	atomic_t		usecnt;
};

enum ib_wq_fwags {
	IB_WQ_FWAGS_CVWAN_STWIPPING	= IB_UVEWBS_WQ_FWAGS_CVWAN_STWIPPING,
	IB_WQ_FWAGS_SCATTEW_FCS		= IB_UVEWBS_WQ_FWAGS_SCATTEW_FCS,
	IB_WQ_FWAGS_DEWAY_DWOP		= IB_UVEWBS_WQ_FWAGS_DEWAY_DWOP,
	IB_WQ_FWAGS_PCI_WWITE_END_PADDING =
				IB_UVEWBS_WQ_FWAGS_PCI_WWITE_END_PADDING,
};

stwuct ib_wq_init_attw {
	void		       *wq_context;
	enum ib_wq_type	wq_type;
	u32		max_ww;
	u32		max_sge;
	stwuct	ib_cq	       *cq;
	void		    (*event_handwew)(stwuct ib_event *, void *);
	u32		cweate_fwags; /* Use enum ib_wq_fwags */
};

enum ib_wq_attw_mask {
	IB_WQ_STATE		= 1 << 0,
	IB_WQ_CUW_STATE		= 1 << 1,
	IB_WQ_FWAGS		= 1 << 2,
};

stwuct ib_wq_attw {
	enum	ib_wq_state	wq_state;
	enum	ib_wq_state	cuww_wq_state;
	u32			fwags; /* Use enum ib_wq_fwags */
	u32			fwags_mask; /* Use enum ib_wq_fwags */
};

stwuct ib_wwq_ind_tabwe {
	stwuct ib_device	*device;
	stwuct ib_uobject      *uobject;
	atomic_t		usecnt;
	u32		ind_tbw_num;
	u32		wog_ind_tbw_size;
	stwuct ib_wq	**ind_tbw;
};

stwuct ib_wwq_ind_tabwe_init_attw {
	u32		wog_ind_tbw_size;
	/* Each entwy is a pointew to Weceive Wowk Queue */
	stwuct ib_wq	**ind_tbw;
};

enum powt_pkey_state {
	IB_POWT_PKEY_NOT_VAWID = 0,
	IB_POWT_PKEY_VAWID = 1,
	IB_POWT_PKEY_WISTED = 2,
};

stwuct ib_qp_secuwity;

stwuct ib_powt_pkey {
	enum powt_pkey_state	state;
	u16			pkey_index;
	u32			powt_num;
	stwuct wist_head	qp_wist;
	stwuct wist_head	to_ewwow_wist;
	stwuct ib_qp_secuwity  *sec;
};

stwuct ib_powts_pkeys {
	stwuct ib_powt_pkey	main;
	stwuct ib_powt_pkey	awt;
};

stwuct ib_qp_secuwity {
	stwuct ib_qp	       *qp;
	stwuct ib_device       *dev;
	/* Howd this mutex when changing powt and pkey settings. */
	stwuct mutex		mutex;
	stwuct ib_powts_pkeys  *powts_pkeys;
	/* A wist of aww open shawed QP handwes.  Wequiwed to enfowce secuwity
	 * pwopewwy fow aww usews of a shawed QP.
	 */
	stwuct wist_head        shawed_qp_wist;
	void                   *secuwity;
	boow			destwoying;
	atomic_t		ewwow_wist_count;
	stwuct compwetion	ewwow_compwete;
	int			ewwow_comps_pending;
};

/*
 * @max_wwite_sge: Maximum SGE ewements pew WDMA WWITE wequest.
 * @max_wead_sge:  Maximum SGE ewements pew WDMA WEAD wequest.
 */
stwuct ib_qp {
	stwuct ib_device       *device;
	stwuct ib_pd	       *pd;
	stwuct ib_cq	       *send_cq;
	stwuct ib_cq	       *wecv_cq;
	spinwock_t		mw_wock;
	int			mws_used;
	stwuct wist_head	wdma_mws;
	stwuct wist_head	sig_mws;
	stwuct ib_swq	       *swq;
	stwuct ib_xwcd	       *xwcd; /* XWC TGT QPs onwy */
	stwuct wist_head	xwcd_wist;

	/* count times opened, mcast attaches, fwow attaches */
	atomic_t		usecnt;
	stwuct wist_head	open_wist;
	stwuct ib_qp           *weaw_qp;
	stwuct ib_uqp_object   *uobject;
	void                  (*event_handwew)(stwuct ib_event *, void *);
	void		       *qp_context;
	/* sgid_attws associated with the AV's */
	const stwuct ib_gid_attw *av_sgid_attw;
	const stwuct ib_gid_attw *awt_path_sgid_attw;
	u32			qp_num;
	u32			max_wwite_sge;
	u32			max_wead_sge;
	enum ib_qp_type		qp_type;
	stwuct ib_wwq_ind_tabwe *wwq_ind_tbw;
	stwuct ib_qp_secuwity  *qp_sec;
	u32			powt;

	boow			integwity_en;
	/*
	 * Impwementation detaiws of the WDMA cowe, don't use in dwivews:
	 */
	stwuct wdma_westwack_entwy     wes;

	/* The countew the qp is bind to */
	stwuct wdma_countew    *countew;
};

stwuct ib_dm {
	stwuct ib_device  *device;
	u32		   wength;
	u32		   fwags;
	stwuct ib_uobject *uobject;
	atomic_t	   usecnt;
};

stwuct ib_mw {
	stwuct ib_device  *device;
	stwuct ib_pd	  *pd;
	u32		   wkey;
	u32		   wkey;
	u64		   iova;
	u64		   wength;
	unsigned int	   page_size;
	enum ib_mw_type	   type;
	boow		   need_invaw;
	union {
		stwuct ib_uobject	*uobject;	/* usew */
		stwuct wist_head	qp_entwy;	/* FW */
	};

	stwuct ib_dm      *dm;
	stwuct ib_sig_attws *sig_attws; /* onwy fow IB_MW_TYPE_INTEGWITY MWs */
	/*
	 * Impwementation detaiws of the WDMA cowe, don't use in dwivews:
	 */
	stwuct wdma_westwack_entwy wes;
};

stwuct ib_mw {
	stwuct ib_device	*device;
	stwuct ib_pd		*pd;
	stwuct ib_uobject	*uobject;
	u32			wkey;
	enum ib_mw_type         type;
};

/* Suppowted steewing options */
enum ib_fwow_attw_type {
	/* steewing accowding to wuwe specifications */
	IB_FWOW_ATTW_NOWMAW		= 0x0,
	/* defauwt unicast and muwticast wuwe -
	 * weceive aww Eth twaffic which isn't steewed to any QP
	 */
	IB_FWOW_ATTW_AWW_DEFAUWT	= 0x1,
	/* defauwt muwticast wuwe -
	 * weceive aww Eth muwticast twaffic which isn't steewed to any QP
	 */
	IB_FWOW_ATTW_MC_DEFAUWT		= 0x2,
	/* sniffew wuwe - weceive aww powt twaffic */
	IB_FWOW_ATTW_SNIFFEW		= 0x3
};

/* Suppowted steewing headew types */
enum ib_fwow_spec_type {
	/* W2 headews*/
	IB_FWOW_SPEC_ETH		= 0x20,
	IB_FWOW_SPEC_IB			= 0x22,
	/* W3 headew*/
	IB_FWOW_SPEC_IPV4		= 0x30,
	IB_FWOW_SPEC_IPV6		= 0x31,
	IB_FWOW_SPEC_ESP                = 0x34,
	/* W4 headews*/
	IB_FWOW_SPEC_TCP		= 0x40,
	IB_FWOW_SPEC_UDP		= 0x41,
	IB_FWOW_SPEC_VXWAN_TUNNEW	= 0x50,
	IB_FWOW_SPEC_GWE		= 0x51,
	IB_FWOW_SPEC_MPWS		= 0x60,
	IB_FWOW_SPEC_INNEW		= 0x100,
	/* Actions */
	IB_FWOW_SPEC_ACTION_TAG         = 0x1000,
	IB_FWOW_SPEC_ACTION_DWOP        = 0x1001,
	IB_FWOW_SPEC_ACTION_HANDWE	= 0x1002,
	IB_FWOW_SPEC_ACTION_COUNT       = 0x1003,
};
#define IB_FWOW_SPEC_WAYEW_MASK	0xF0
#define IB_FWOW_SPEC_SUPPOWT_WAYEWS 10

enum ib_fwow_fwags {
	IB_FWOW_ATTW_FWAGS_DONT_TWAP = 1UW << 1, /* Continue match, no steaw */
	IB_FWOW_ATTW_FWAGS_EGWESS = 1UW << 2, /* Egwess fwow */
	IB_FWOW_ATTW_FWAGS_WESEWVED  = 1UW << 3  /* Must be wast */
};

stwuct ib_fwow_eth_fiwtew {
	u8	dst_mac[6];
	u8	swc_mac[6];
	__be16	ethew_type;
	__be16	vwan_tag;
	/* Must be wast */
	u8	weaw_sz[];
};

stwuct ib_fwow_spec_eth {
	u32			  type;
	u16			  size;
	stwuct ib_fwow_eth_fiwtew vaw;
	stwuct ib_fwow_eth_fiwtew mask;
};

stwuct ib_fwow_ib_fiwtew {
	__be16 dwid;
	__u8   sw;
	/* Must be wast */
	u8	weaw_sz[];
};

stwuct ib_fwow_spec_ib {
	u32			 type;
	u16			 size;
	stwuct ib_fwow_ib_fiwtew vaw;
	stwuct ib_fwow_ib_fiwtew mask;
};

/* IPv4 headew fwags */
enum ib_ipv4_fwags {
	IB_IPV4_DONT_FWAG = 0x2, /* Don't enabwe packet fwagmentation */
	IB_IPV4_MOWE_FWAG = 0X4  /* Fow Aww fwagmented packets except the
				    wast have this fwag set */
};

stwuct ib_fwow_ipv4_fiwtew {
	__be32	swc_ip;
	__be32	dst_ip;
	u8	pwoto;
	u8	tos;
	u8	ttw;
	u8	fwags;
	/* Must be wast */
	u8	weaw_sz[];
};

stwuct ib_fwow_spec_ipv4 {
	u32			   type;
	u16			   size;
	stwuct ib_fwow_ipv4_fiwtew vaw;
	stwuct ib_fwow_ipv4_fiwtew mask;
};

stwuct ib_fwow_ipv6_fiwtew {
	u8	swc_ip[16];
	u8	dst_ip[16];
	__be32	fwow_wabew;
	u8	next_hdw;
	u8	twaffic_cwass;
	u8	hop_wimit;
	/* Must be wast */
	u8	weaw_sz[];
};

stwuct ib_fwow_spec_ipv6 {
	u32			   type;
	u16			   size;
	stwuct ib_fwow_ipv6_fiwtew vaw;
	stwuct ib_fwow_ipv6_fiwtew mask;
};

stwuct ib_fwow_tcp_udp_fiwtew {
	__be16	dst_powt;
	__be16	swc_powt;
	/* Must be wast */
	u8	weaw_sz[];
};

stwuct ib_fwow_spec_tcp_udp {
	u32			      type;
	u16			      size;
	stwuct ib_fwow_tcp_udp_fiwtew vaw;
	stwuct ib_fwow_tcp_udp_fiwtew mask;
};

stwuct ib_fwow_tunnew_fiwtew {
	__be32	tunnew_id;
	u8	weaw_sz[];
};

/* ib_fwow_spec_tunnew descwibes the Vxwan tunnew
 * the tunnew_id fwom vaw has the vni vawue
 */
stwuct ib_fwow_spec_tunnew {
	u32			      type;
	u16			      size;
	stwuct ib_fwow_tunnew_fiwtew  vaw;
	stwuct ib_fwow_tunnew_fiwtew  mask;
};

stwuct ib_fwow_esp_fiwtew {
	__be32	spi;
	__be32  seq;
	/* Must be wast */
	u8	weaw_sz[];
};

stwuct ib_fwow_spec_esp {
	u32                           type;
	u16			      size;
	stwuct ib_fwow_esp_fiwtew     vaw;
	stwuct ib_fwow_esp_fiwtew     mask;
};

stwuct ib_fwow_gwe_fiwtew {
	__be16 c_ks_wes0_vew;
	__be16 pwotocow;
	__be32 key;
	/* Must be wast */
	u8	weaw_sz[];
};

stwuct ib_fwow_spec_gwe {
	u32                           type;
	u16			      size;
	stwuct ib_fwow_gwe_fiwtew     vaw;
	stwuct ib_fwow_gwe_fiwtew     mask;
};

stwuct ib_fwow_mpws_fiwtew {
	__be32 tag;
	/* Must be wast */
	u8	weaw_sz[];
};

stwuct ib_fwow_spec_mpws {
	u32                           type;
	u16			      size;
	stwuct ib_fwow_mpws_fiwtew     vaw;
	stwuct ib_fwow_mpws_fiwtew     mask;
};

stwuct ib_fwow_spec_action_tag {
	enum ib_fwow_spec_type	      type;
	u16			      size;
	u32                           tag_id;
};

stwuct ib_fwow_spec_action_dwop {
	enum ib_fwow_spec_type	      type;
	u16			      size;
};

stwuct ib_fwow_spec_action_handwe {
	enum ib_fwow_spec_type	      type;
	u16			      size;
	stwuct ib_fwow_action	     *act;
};

enum ib_countews_descwiption {
	IB_COUNTEW_PACKETS,
	IB_COUNTEW_BYTES,
};

stwuct ib_fwow_spec_action_count {
	enum ib_fwow_spec_type type;
	u16 size;
	stwuct ib_countews *countews;
};

union ib_fwow_spec {
	stwuct {
		u32			type;
		u16			size;
	};
	stwuct ib_fwow_spec_eth		eth;
	stwuct ib_fwow_spec_ib		ib;
	stwuct ib_fwow_spec_ipv4        ipv4;
	stwuct ib_fwow_spec_tcp_udp	tcp_udp;
	stwuct ib_fwow_spec_ipv6        ipv6;
	stwuct ib_fwow_spec_tunnew      tunnew;
	stwuct ib_fwow_spec_esp		esp;
	stwuct ib_fwow_spec_gwe		gwe;
	stwuct ib_fwow_spec_mpws	mpws;
	stwuct ib_fwow_spec_action_tag  fwow_tag;
	stwuct ib_fwow_spec_action_dwop dwop;
	stwuct ib_fwow_spec_action_handwe action;
	stwuct ib_fwow_spec_action_count fwow_count;
};

stwuct ib_fwow_attw {
	enum ib_fwow_attw_type type;
	u16	     size;
	u16	     pwiowity;
	u32	     fwags;
	u8	     num_of_specs;
	u32	     powt;
	union ib_fwow_spec fwows[];
};

stwuct ib_fwow {
	stwuct ib_qp		*qp;
	stwuct ib_device	*device;
	stwuct ib_uobject	*uobject;
};

enum ib_fwow_action_type {
	IB_FWOW_ACTION_UNSPECIFIED,
	IB_FWOW_ACTION_ESP = 1,
};

stwuct ib_fwow_action_attws_esp_keymats {
	enum ib_uvewbs_fwow_action_esp_keymat			pwotocow;
	union {
		stwuct ib_uvewbs_fwow_action_esp_keymat_aes_gcm aes_gcm;
	} keymat;
};

stwuct ib_fwow_action_attws_esp_wepways {
	enum ib_uvewbs_fwow_action_esp_wepway			pwotocow;
	union {
		stwuct ib_uvewbs_fwow_action_esp_wepway_bmp	bmp;
	} wepway;
};

enum ib_fwow_action_attws_esp_fwags {
	/* Aww usew-space fwags at the top: Use enum ib_uvewbs_fwow_action_esp_fwags
	 * This is done in owdew to shawe the same fwags between usew-space and
	 * kewnew and spawe an unnecessawy twanswation.
	 */

	/* Kewnew fwags */
	IB_FWOW_ACTION_ESP_FWAGS_ESN_TWIGGEWED	= 1UWW << 32,
	IB_FWOW_ACTION_ESP_FWAGS_MOD_ESP_ATTWS	= 1UWW << 33,
};

stwuct ib_fwow_spec_wist {
	stwuct ib_fwow_spec_wist	*next;
	union ib_fwow_spec		spec;
};

stwuct ib_fwow_action_attws_esp {
	stwuct ib_fwow_action_attws_esp_keymats		*keymat;
	stwuct ib_fwow_action_attws_esp_wepways		*wepway;
	stwuct ib_fwow_spec_wist			*encap;
	/* Used onwy if IB_FWOW_ACTION_ESP_FWAGS_ESN_TWIGGEWED is enabwed.
	 * Vawue of 0 is a vawid vawue.
	 */
	u32						esn;
	u32						spi;
	u32						seq;
	u32						tfc_pad;
	/* Use enum ib_fwow_action_attws_esp_fwags */
	u64						fwags;
	u64						hawd_wimit_pkts;
};

stwuct ib_fwow_action {
	stwuct ib_device		*device;
	stwuct ib_uobject		*uobject;
	enum ib_fwow_action_type	type;
	atomic_t			usecnt;
};

stwuct ib_mad;

enum ib_pwocess_mad_fwags {
	IB_MAD_IGNOWE_MKEY	= 1,
	IB_MAD_IGNOWE_BKEY	= 2,
	IB_MAD_IGNOWE_AWW	= IB_MAD_IGNOWE_MKEY | IB_MAD_IGNOWE_BKEY
};

enum ib_mad_wesuwt {
	IB_MAD_WESUWT_FAIWUWE  = 0,      /* (!SUCCESS is the impowtant fwag) */
	IB_MAD_WESUWT_SUCCESS  = 1 << 0, /* MAD was successfuwwy pwocessed   */
	IB_MAD_WESUWT_WEPWY    = 1 << 1, /* Wepwy packet needs to be sent    */
	IB_MAD_WESUWT_CONSUMED = 1 << 2  /* Packet consumed: stop pwocessing */
};

stwuct ib_powt_cache {
	u64		      subnet_pwefix;
	stwuct ib_pkey_cache  *pkey;
	stwuct ib_gid_tabwe   *gid;
	u8                     wmc;
	enum ib_powt_state     powt_state;
};

stwuct ib_powt_immutabwe {
	int                           pkey_tbw_wen;
	int                           gid_tbw_wen;
	u32                           cowe_cap_fwags;
	u32                           max_mad_size;
};

stwuct ib_powt_data {
	stwuct ib_device *ib_dev;

	stwuct ib_powt_immutabwe immutabwe;

	spinwock_t pkey_wist_wock;

	spinwock_t netdev_wock;

	stwuct wist_head pkey_wist;

	stwuct ib_powt_cache cache;

	stwuct net_device __wcu *netdev;
	netdevice_twackew netdev_twackew;
	stwuct hwist_node ndev_hash_wink;
	stwuct wdma_powt_countew powt_countew;
	stwuct ib_powt *sysfs;
};

/* wdma netdev type - specifies pwotocow type */
enum wdma_netdev_t {
	WDMA_NETDEV_OPA_VNIC,
	WDMA_NETDEV_IPOIB,
};

/**
 * stwuct wdma_netdev - wdma netdev
 * Fow cases whewe netstack intewfacing is wequiwed.
 */
stwuct wdma_netdev {
	void              *cwnt_pwiv;
	stwuct ib_device  *hca;
	u32		   powt_num;
	int                mtu;

	/*
	 * cweanup function must be specified.
	 * FIXME: This is onwy used fow OPA_VNIC and that usage shouwd be
	 * wemoved too.
	 */
	void (*fwee_wdma_netdev)(stwuct net_device *netdev);

	/* contwow functions */
	void (*set_id)(stwuct net_device *netdev, int id);
	/* send packet */
	int (*send)(stwuct net_device *dev, stwuct sk_buff *skb,
		    stwuct ib_ah *addwess, u32 dqpn);
	/* muwticast */
	int (*attach_mcast)(stwuct net_device *dev, stwuct ib_device *hca,
			    union ib_gid *gid, u16 mwid,
			    int set_qkey, u32 qkey);
	int (*detach_mcast)(stwuct net_device *dev, stwuct ib_device *hca,
			    union ib_gid *gid, u16 mwid);
	/* timeout */
	void (*tx_timeout)(stwuct net_device *dev, unsigned int txqueue);
};

stwuct wdma_netdev_awwoc_pawams {
	size_t sizeof_pwiv;
	unsigned int txqs;
	unsigned int wxqs;
	void *pawam;

	int (*initiawize_wdma_netdev)(stwuct ib_device *device, u32 powt_num,
				      stwuct net_device *netdev, void *pawam);
};

stwuct ib_odp_countews {
	atomic64_t fauwts;
	atomic64_t invawidations;
	atomic64_t pwefetch;
};

stwuct ib_countews {
	stwuct ib_device	*device;
	stwuct ib_uobject	*uobject;
	/* num of objects attached */
	atomic_t	usecnt;
};

stwuct ib_countews_wead_attw {
	u64	*countews_buff;
	u32	ncountews;
	u32	fwags; /* use enum ib_wead_countews_fwags */
};

stwuct uvewbs_attw_bundwe;
stwuct iw_cm_id;
stwuct iw_cm_conn_pawam;

#define INIT_WDMA_OBJ_SIZE(ib_stwuct, dwv_stwuct, membew)                      \
	.size_##ib_stwuct =                                                    \
		(sizeof(stwuct dwv_stwuct) +                                   \
		 BUIWD_BUG_ON_ZEWO(offsetof(stwuct dwv_stwuct, membew)) +      \
		 BUIWD_BUG_ON_ZEWO(                                            \
			 !__same_type(((stwuct dwv_stwuct *)NUWW)->membew,     \
				      stwuct ib_stwuct)))

#define wdma_zawwoc_dwv_obj_gfp(ib_dev, ib_type, gfp)                          \
	((stwuct ib_type *)wdma_zawwoc_obj(ib_dev, ib_dev->ops.size_##ib_type, \
					   gfp, fawse))

#define wdma_zawwoc_dwv_obj_numa(ib_dev, ib_type)                              \
	((stwuct ib_type *)wdma_zawwoc_obj(ib_dev, ib_dev->ops.size_##ib_type, \
					   GFP_KEWNEW, twue))

#define wdma_zawwoc_dwv_obj(ib_dev, ib_type)                                   \
	wdma_zawwoc_dwv_obj_gfp(ib_dev, ib_type, GFP_KEWNEW)

#define DECWAWE_WDMA_OBJ_SIZE(ib_stwuct) size_t size_##ib_stwuct

stwuct wdma_usew_mmap_entwy {
	stwuct kwef wef;
	stwuct ib_ucontext *ucontext;
	unsigned wong stawt_pgoff;
	size_t npages;
	boow dwivew_wemoved;
};

/* Wetuwn the offset (in bytes) the usew shouwd pass to wibc's mmap() */
static inwine u64
wdma_usew_mmap_get_offset(const stwuct wdma_usew_mmap_entwy *entwy)
{
	wetuwn (u64)entwy->stawt_pgoff << PAGE_SHIFT;
}

/**
 * stwuct ib_device_ops - InfiniBand device opewations
 * This stwuctuwe defines aww the InfiniBand device opewations, pwovidews wiww
 * need to define the suppowted opewations, othewwise they wiww be set to nuww.
 */
stwuct ib_device_ops {
	stwuct moduwe *ownew;
	enum wdma_dwivew_id dwivew_id;
	u32 uvewbs_abi_vew;
	unsigned int uvewbs_no_dwivew_id_binding:1;

	/*
	 * NOTE: New dwivews shouwd not make use of device_gwoup; instead new
	 * device pawametew shouwd be exposed via netwink command. This
	 * mechanism exists onwy fow existing dwivews.
	 */
	const stwuct attwibute_gwoup *device_gwoup;
	const stwuct attwibute_gwoup **powt_gwoups;

	int (*post_send)(stwuct ib_qp *qp, const stwuct ib_send_ww *send_ww,
			 const stwuct ib_send_ww **bad_send_ww);
	int (*post_wecv)(stwuct ib_qp *qp, const stwuct ib_wecv_ww *wecv_ww,
			 const stwuct ib_wecv_ww **bad_wecv_ww);
	void (*dwain_wq)(stwuct ib_qp *qp);
	void (*dwain_sq)(stwuct ib_qp *qp);
	int (*poww_cq)(stwuct ib_cq *cq, int num_entwies, stwuct ib_wc *wc);
	int (*peek_cq)(stwuct ib_cq *cq, int wc_cnt);
	int (*weq_notify_cq)(stwuct ib_cq *cq, enum ib_cq_notify_fwags fwags);
	int (*post_swq_wecv)(stwuct ib_swq *swq,
			     const stwuct ib_wecv_ww *wecv_ww,
			     const stwuct ib_wecv_ww **bad_wecv_ww);
	int (*pwocess_mad)(stwuct ib_device *device, int pwocess_mad_fwags,
			   u32 powt_num, const stwuct ib_wc *in_wc,
			   const stwuct ib_gwh *in_gwh,
			   const stwuct ib_mad *in_mad, stwuct ib_mad *out_mad,
			   size_t *out_mad_size, u16 *out_mad_pkey_index);
	int (*quewy_device)(stwuct ib_device *device,
			    stwuct ib_device_attw *device_attw,
			    stwuct ib_udata *udata);
	int (*modify_device)(stwuct ib_device *device, int device_modify_mask,
			     stwuct ib_device_modify *device_modify);
	void (*get_dev_fw_stw)(stwuct ib_device *device, chaw *stw);
	const stwuct cpumask *(*get_vectow_affinity)(stwuct ib_device *ibdev,
						     int comp_vectow);
	int (*quewy_powt)(stwuct ib_device *device, u32 powt_num,
			  stwuct ib_powt_attw *powt_attw);
	int (*modify_powt)(stwuct ib_device *device, u32 powt_num,
			   int powt_modify_mask,
			   stwuct ib_powt_modify *powt_modify);
	/**
	 * The fowwowing mandatowy functions awe used onwy at device
	 * wegistwation.  Keep functions such as these at the end of this
	 * stwuctuwe to avoid cache wine misses when accessing stwuct ib_device
	 * in fast paths.
	 */
	int (*get_powt_immutabwe)(stwuct ib_device *device, u32 powt_num,
				  stwuct ib_powt_immutabwe *immutabwe);
	enum wdma_wink_wayew (*get_wink_wayew)(stwuct ib_device *device,
					       u32 powt_num);
	/**
	 * When cawwing get_netdev, the HW vendow's dwivew shouwd wetuwn the
	 * net device of device @device at powt @powt_num ow NUWW if such
	 * a net device doesn't exist. The vendow dwivew shouwd caww dev_howd
	 * on this net device. The HW vendow's device dwivew must guawantee
	 * that this function wetuwns NUWW befowe the net device has finished
	 * NETDEV_UNWEGISTEW state.
	 */
	stwuct net_device *(*get_netdev)(stwuct ib_device *device,
					 u32 powt_num);
	/**
	 * wdma netdev opewation
	 *
	 * Dwivew impwementing awwoc_wdma_netdev ow wdma_netdev_get_pawams
	 * must wetuwn -EOPNOTSUPP if it doesn't suppowt the specified type.
	 */
	stwuct net_device *(*awwoc_wdma_netdev)(
		stwuct ib_device *device, u32 powt_num, enum wdma_netdev_t type,
		const chaw *name, unsigned chaw name_assign_type,
		void (*setup)(stwuct net_device *));

	int (*wdma_netdev_get_pawams)(stwuct ib_device *device, u32 powt_num,
				      enum wdma_netdev_t type,
				      stwuct wdma_netdev_awwoc_pawams *pawams);
	/**
	 * quewy_gid shouwd be wetuwn GID vawue fow @device, when @powt_num
	 * wink wayew is eithew IB ow iWawp. It is no-op if @powt_num powt
	 * is WoCE wink wayew.
	 */
	int (*quewy_gid)(stwuct ib_device *device, u32 powt_num, int index,
			 union ib_gid *gid);
	/**
	 * When cawwing add_gid, the HW vendow's dwivew shouwd add the gid
	 * of device of powt at gid index avaiwabwe at @attw. Meta-info of
	 * that gid (fow exampwe, the netwowk device wewated to this gid) is
	 * avaiwabwe at @attw. @context awwows the HW vendow dwivew to stowe
	 * extwa infowmation togethew with a GID entwy. The HW vendow dwivew may
	 * awwocate memowy to contain this infowmation and stowe it in @context
	 * when a new GID entwy is wwitten to. Pawams awe consistent untiw the
	 * next caww of add_gid ow dewete_gid. The function shouwd wetuwn 0 on
	 * success ow ewwow othewwise. The function couwd be cawwed
	 * concuwwentwy fow diffewent powts. This function is onwy cawwed when
	 * woce_gid_tabwe is used.
	 */
	int (*add_gid)(const stwuct ib_gid_attw *attw, void **context);
	/**
	 * When cawwing dew_gid, the HW vendow's dwivew shouwd dewete the
	 * gid of device @device at gid index gid_index of powt powt_num
	 * avaiwabwe in @attw.
	 * Upon the dewetion of a GID entwy, the HW vendow must fwee any
	 * awwocated memowy. The cawwew wiww cweaw @context aftewwawds.
	 * This function is onwy cawwed when woce_gid_tabwe is used.
	 */
	int (*dew_gid)(const stwuct ib_gid_attw *attw, void **context);
	int (*quewy_pkey)(stwuct ib_device *device, u32 powt_num, u16 index,
			  u16 *pkey);
	int (*awwoc_ucontext)(stwuct ib_ucontext *context,
			      stwuct ib_udata *udata);
	void (*deawwoc_ucontext)(stwuct ib_ucontext *context);
	int (*mmap)(stwuct ib_ucontext *context, stwuct vm_awea_stwuct *vma);
	/**
	 * This wiww be cawwed once wefcount of an entwy in mmap_xa weaches
	 * zewo. The type of the memowy that was mapped may diffew between
	 * entwies and is opaque to the wdma_usew_mmap intewface.
	 * Thewefowe needs to be impwemented by the dwivew in mmap_fwee.
	 */
	void (*mmap_fwee)(stwuct wdma_usew_mmap_entwy *entwy);
	void (*disassociate_ucontext)(stwuct ib_ucontext *ibcontext);
	int (*awwoc_pd)(stwuct ib_pd *pd, stwuct ib_udata *udata);
	int (*deawwoc_pd)(stwuct ib_pd *pd, stwuct ib_udata *udata);
	int (*cweate_ah)(stwuct ib_ah *ah, stwuct wdma_ah_init_attw *attw,
			 stwuct ib_udata *udata);
	int (*cweate_usew_ah)(stwuct ib_ah *ah, stwuct wdma_ah_init_attw *attw,
			      stwuct ib_udata *udata);
	int (*modify_ah)(stwuct ib_ah *ah, stwuct wdma_ah_attw *ah_attw);
	int (*quewy_ah)(stwuct ib_ah *ah, stwuct wdma_ah_attw *ah_attw);
	int (*destwoy_ah)(stwuct ib_ah *ah, u32 fwags);
	int (*cweate_swq)(stwuct ib_swq *swq,
			  stwuct ib_swq_init_attw *swq_init_attw,
			  stwuct ib_udata *udata);
	int (*modify_swq)(stwuct ib_swq *swq, stwuct ib_swq_attw *swq_attw,
			  enum ib_swq_attw_mask swq_attw_mask,
			  stwuct ib_udata *udata);
	int (*quewy_swq)(stwuct ib_swq *swq, stwuct ib_swq_attw *swq_attw);
	int (*destwoy_swq)(stwuct ib_swq *swq, stwuct ib_udata *udata);
	int (*cweate_qp)(stwuct ib_qp *qp, stwuct ib_qp_init_attw *qp_init_attw,
			 stwuct ib_udata *udata);
	int (*modify_qp)(stwuct ib_qp *qp, stwuct ib_qp_attw *qp_attw,
			 int qp_attw_mask, stwuct ib_udata *udata);
	int (*quewy_qp)(stwuct ib_qp *qp, stwuct ib_qp_attw *qp_attw,
			int qp_attw_mask, stwuct ib_qp_init_attw *qp_init_attw);
	int (*destwoy_qp)(stwuct ib_qp *qp, stwuct ib_udata *udata);
	int (*cweate_cq)(stwuct ib_cq *cq, const stwuct ib_cq_init_attw *attw,
			 stwuct ib_udata *udata);
	int (*modify_cq)(stwuct ib_cq *cq, u16 cq_count, u16 cq_pewiod);
	int (*destwoy_cq)(stwuct ib_cq *cq, stwuct ib_udata *udata);
	int (*wesize_cq)(stwuct ib_cq *cq, int cqe, stwuct ib_udata *udata);
	stwuct ib_mw *(*get_dma_mw)(stwuct ib_pd *pd, int mw_access_fwags);
	stwuct ib_mw *(*weg_usew_mw)(stwuct ib_pd *pd, u64 stawt, u64 wength,
				     u64 viwt_addw, int mw_access_fwags,
				     stwuct ib_udata *udata);
	stwuct ib_mw *(*weg_usew_mw_dmabuf)(stwuct ib_pd *pd, u64 offset,
					    u64 wength, u64 viwt_addw, int fd,
					    int mw_access_fwags,
					    stwuct ib_udata *udata);
	stwuct ib_mw *(*weweg_usew_mw)(stwuct ib_mw *mw, int fwags, u64 stawt,
				       u64 wength, u64 viwt_addw,
				       int mw_access_fwags, stwuct ib_pd *pd,
				       stwuct ib_udata *udata);
	int (*deweg_mw)(stwuct ib_mw *mw, stwuct ib_udata *udata);
	stwuct ib_mw *(*awwoc_mw)(stwuct ib_pd *pd, enum ib_mw_type mw_type,
				  u32 max_num_sg);
	stwuct ib_mw *(*awwoc_mw_integwity)(stwuct ib_pd *pd,
					    u32 max_num_data_sg,
					    u32 max_num_meta_sg);
	int (*advise_mw)(stwuct ib_pd *pd,
			 enum ib_uvewbs_advise_mw_advice advice, u32 fwags,
			 stwuct ib_sge *sg_wist, u32 num_sge,
			 stwuct uvewbs_attw_bundwe *attws);

	/*
	 * Kewnew usews shouwd univewsawwy suppowt wewaxed owdewing (WO), as
	 * they awe designed to wead data onwy aftew obsewving the CQE and use
	 * the DMA API cowwectwy.
	 *
	 * Some dwivews impwicitwy enabwe WO if pwatfowm suppowts it.
	 */
	int (*map_mw_sg)(stwuct ib_mw *mw, stwuct scattewwist *sg, int sg_nents,
			 unsigned int *sg_offset);
	int (*check_mw_status)(stwuct ib_mw *mw, u32 check_mask,
			       stwuct ib_mw_status *mw_status);
	int (*awwoc_mw)(stwuct ib_mw *mw, stwuct ib_udata *udata);
	int (*deawwoc_mw)(stwuct ib_mw *mw);
	int (*attach_mcast)(stwuct ib_qp *qp, union ib_gid *gid, u16 wid);
	int (*detach_mcast)(stwuct ib_qp *qp, union ib_gid *gid, u16 wid);
	int (*awwoc_xwcd)(stwuct ib_xwcd *xwcd, stwuct ib_udata *udata);
	int (*deawwoc_xwcd)(stwuct ib_xwcd *xwcd, stwuct ib_udata *udata);
	stwuct ib_fwow *(*cweate_fwow)(stwuct ib_qp *qp,
				       stwuct ib_fwow_attw *fwow_attw,
				       stwuct ib_udata *udata);
	int (*destwoy_fwow)(stwuct ib_fwow *fwow_id);
	int (*destwoy_fwow_action)(stwuct ib_fwow_action *action);
	int (*set_vf_wink_state)(stwuct ib_device *device, int vf, u32 powt,
				 int state);
	int (*get_vf_config)(stwuct ib_device *device, int vf, u32 powt,
			     stwuct ifwa_vf_info *ivf);
	int (*get_vf_stats)(stwuct ib_device *device, int vf, u32 powt,
			    stwuct ifwa_vf_stats *stats);
	int (*get_vf_guid)(stwuct ib_device *device, int vf, u32 powt,
			    stwuct ifwa_vf_guid *node_guid,
			    stwuct ifwa_vf_guid *powt_guid);
	int (*set_vf_guid)(stwuct ib_device *device, int vf, u32 powt, u64 guid,
			   int type);
	stwuct ib_wq *(*cweate_wq)(stwuct ib_pd *pd,
				   stwuct ib_wq_init_attw *init_attw,
				   stwuct ib_udata *udata);
	int (*destwoy_wq)(stwuct ib_wq *wq, stwuct ib_udata *udata);
	int (*modify_wq)(stwuct ib_wq *wq, stwuct ib_wq_attw *attw,
			 u32 wq_attw_mask, stwuct ib_udata *udata);
	int (*cweate_wwq_ind_tabwe)(stwuct ib_wwq_ind_tabwe *ib_wwq_ind_tabwe,
				    stwuct ib_wwq_ind_tabwe_init_attw *init_attw,
				    stwuct ib_udata *udata);
	int (*destwoy_wwq_ind_tabwe)(stwuct ib_wwq_ind_tabwe *wq_ind_tabwe);
	stwuct ib_dm *(*awwoc_dm)(stwuct ib_device *device,
				  stwuct ib_ucontext *context,
				  stwuct ib_dm_awwoc_attw *attw,
				  stwuct uvewbs_attw_bundwe *attws);
	int (*deawwoc_dm)(stwuct ib_dm *dm, stwuct uvewbs_attw_bundwe *attws);
	stwuct ib_mw *(*weg_dm_mw)(stwuct ib_pd *pd, stwuct ib_dm *dm,
				   stwuct ib_dm_mw_attw *attw,
				   stwuct uvewbs_attw_bundwe *attws);
	int (*cweate_countews)(stwuct ib_countews *countews,
			       stwuct uvewbs_attw_bundwe *attws);
	int (*destwoy_countews)(stwuct ib_countews *countews);
	int (*wead_countews)(stwuct ib_countews *countews,
			     stwuct ib_countews_wead_attw *countews_wead_attw,
			     stwuct uvewbs_attw_bundwe *attws);
	int (*map_mw_sg_pi)(stwuct ib_mw *mw, stwuct scattewwist *data_sg,
			    int data_sg_nents, unsigned int *data_sg_offset,
			    stwuct scattewwist *meta_sg, int meta_sg_nents,
			    unsigned int *meta_sg_offset);

	/**
	 * awwoc_hw_[device,powt]_stats - Awwocate a stwuct wdma_hw_stats and
	 *   fiww in the dwivew initiawized data.  The stwuct is kfwee()'ed by
	 *   the sysfs cowe when the device is wemoved.  A wifespan of -1 in the
	 *   wetuwn stwuct tewws the cowe to set a defauwt wifespan.
	 */
	stwuct wdma_hw_stats *(*awwoc_hw_device_stats)(stwuct ib_device *device);
	stwuct wdma_hw_stats *(*awwoc_hw_powt_stats)(stwuct ib_device *device,
						     u32 powt_num);
	/**
	 * get_hw_stats - Fiww in the countew vawue(s) in the stats stwuct.
	 * @index - The index in the vawue awway we wish to have updated, ow
	 *   num_countews if we want aww stats updated
	 * Wetuwn codes -
	 *   < 0 - Ewwow, no countews updated
	 *   index - Updated the singwe countew pointed to by index
	 *   num_countews - Updated aww countews (wiww weset the timestamp
	 *     and pwevent fuwthew cawws fow wifespan miwwiseconds)
	 * Dwivews awe awwowed to update aww countews in weiu of just the
	 *   one given in index at theiw option
	 */
	int (*get_hw_stats)(stwuct ib_device *device,
			    stwuct wdma_hw_stats *stats, u32 powt, int index);

	/**
	 * modify_hw_stat - Modify the countew configuwation
	 * @enabwe: twue/fawse when enabwe/disabwe a countew
	 * Wetuwn codes - 0 on success ow ewwow code othewwise.
	 */
	int (*modify_hw_stat)(stwuct ib_device *device, u32 powt,
			      unsigned int countew_index, boow enabwe);
	/**
	 * Awwows wdma dwivews to add theiw own westwack attwibutes.
	 */
	int (*fiww_wes_mw_entwy)(stwuct sk_buff *msg, stwuct ib_mw *ibmw);
	int (*fiww_wes_mw_entwy_waw)(stwuct sk_buff *msg, stwuct ib_mw *ibmw);
	int (*fiww_wes_cq_entwy)(stwuct sk_buff *msg, stwuct ib_cq *ibcq);
	int (*fiww_wes_cq_entwy_waw)(stwuct sk_buff *msg, stwuct ib_cq *ibcq);
	int (*fiww_wes_qp_entwy)(stwuct sk_buff *msg, stwuct ib_qp *ibqp);
	int (*fiww_wes_qp_entwy_waw)(stwuct sk_buff *msg, stwuct ib_qp *ibqp);
	int (*fiww_wes_cm_id_entwy)(stwuct sk_buff *msg, stwuct wdma_cm_id *id);
	int (*fiww_wes_swq_entwy)(stwuct sk_buff *msg, stwuct ib_swq *ib_swq);
	int (*fiww_wes_swq_entwy_waw)(stwuct sk_buff *msg, stwuct ib_swq *ib_swq);

	/* Device wifecycwe cawwbacks */
	/*
	 * Cawwed aftew the device becomes wegistewed, befowe cwients awe
	 * attached
	 */
	int (*enabwe_dwivew)(stwuct ib_device *dev);
	/*
	 * This is cawwed as pawt of ib_deawwoc_device().
	 */
	void (*deawwoc_dwivew)(stwuct ib_device *dev);

	/* iWawp CM cawwbacks */
	void (*iw_add_wef)(stwuct ib_qp *qp);
	void (*iw_wem_wef)(stwuct ib_qp *qp);
	stwuct ib_qp *(*iw_get_qp)(stwuct ib_device *device, int qpn);
	int (*iw_connect)(stwuct iw_cm_id *cm_id,
			  stwuct iw_cm_conn_pawam *conn_pawam);
	int (*iw_accept)(stwuct iw_cm_id *cm_id,
			 stwuct iw_cm_conn_pawam *conn_pawam);
	int (*iw_weject)(stwuct iw_cm_id *cm_id, const void *pdata,
			 u8 pdata_wen);
	int (*iw_cweate_wisten)(stwuct iw_cm_id *cm_id, int backwog);
	int (*iw_destwoy_wisten)(stwuct iw_cm_id *cm_id);
	/**
	 * countew_bind_qp - Bind a QP to a countew.
	 * @countew - The countew to be bound. If countew->id is zewo then
	 *   the dwivew needs to awwocate a new countew and set countew->id
	 */
	int (*countew_bind_qp)(stwuct wdma_countew *countew, stwuct ib_qp *qp);
	/**
	 * countew_unbind_qp - Unbind the qp fwom the dynamicawwy-awwocated
	 *   countew and bind it onto the defauwt one
	 */
	int (*countew_unbind_qp)(stwuct ib_qp *qp);
	/**
	 * countew_deawwoc -De-awwocate the hw countew
	 */
	int (*countew_deawwoc)(stwuct wdma_countew *countew);
	/**
	 * countew_awwoc_stats - Awwocate a stwuct wdma_hw_stats and fiww in
	 * the dwivew initiawized data.
	 */
	stwuct wdma_hw_stats *(*countew_awwoc_stats)(
		stwuct wdma_countew *countew);
	/**
	 * countew_update_stats - Quewy the stats vawue of this countew
	 */
	int (*countew_update_stats)(stwuct wdma_countew *countew);

	/**
	 * Awwows wdma dwivews to add theiw own westwack attwibutes
	 * dumped via 'wdma stat' ipwoute2 command.
	 */
	int (*fiww_stat_mw_entwy)(stwuct sk_buff *msg, stwuct ib_mw *ibmw);

	/* quewy dwivew fow its ucontext pwopewties */
	int (*quewy_ucontext)(stwuct ib_ucontext *context,
			      stwuct uvewbs_attw_bundwe *attws);

	/*
	 * Pwovide NUMA node. This API exists fow wdmavt/hfi1 onwy.
	 * Evewyone ewse wewies on Winux memowy management modew.
	 */
	int (*get_numa_node)(stwuct ib_device *dev);

	DECWAWE_WDMA_OBJ_SIZE(ib_ah);
	DECWAWE_WDMA_OBJ_SIZE(ib_countews);
	DECWAWE_WDMA_OBJ_SIZE(ib_cq);
	DECWAWE_WDMA_OBJ_SIZE(ib_mw);
	DECWAWE_WDMA_OBJ_SIZE(ib_pd);
	DECWAWE_WDMA_OBJ_SIZE(ib_qp);
	DECWAWE_WDMA_OBJ_SIZE(ib_wwq_ind_tabwe);
	DECWAWE_WDMA_OBJ_SIZE(ib_swq);
	DECWAWE_WDMA_OBJ_SIZE(ib_ucontext);
	DECWAWE_WDMA_OBJ_SIZE(ib_xwcd);
};

stwuct ib_cowe_device {
	/* device must be the fiwst ewement in stwuctuwe untiw,
	 * union of ib_cowe_device and device exists in ib_device.
	 */
	stwuct device dev;
	possibwe_net_t wdma_net;
	stwuct kobject *powts_kobj;
	stwuct wist_head powt_wist;
	stwuct ib_device *ownew; /* weach back to ownew ib_device */
};

stwuct wdma_westwack_woot;
stwuct ib_device {
	/* Do not access @dma_device diwectwy fwom UWP now fwom HW dwivews. */
	stwuct device                *dma_device;
	stwuct ib_device_ops	     ops;
	chaw                          name[IB_DEVICE_NAME_MAX];
	stwuct wcu_head wcu_head;

	stwuct wist_head              event_handwew_wist;
	/* Pwotects event_handwew_wist */
	stwuct ww_semaphowe event_handwew_wwsem;

	/* Pwotects QP's event_handwew cawws and open_qp wist */
	spinwock_t qp_open_wist_wock;

	stwuct ww_semaphowe	      cwient_data_wwsem;
	stwuct xawway                 cwient_data;
	stwuct mutex                  unwegistwation_wock;

	/* Synchwonize GID, Pkey cache entwies, subnet pwefix, WMC */
	wwwock_t cache_wock;
	/**
	 * powt_data is indexed by powt numbew
	 */
	stwuct ib_powt_data *powt_data;

	int			      num_comp_vectows;

	union {
		stwuct device		dev;
		stwuct ib_cowe_device	cowedev;
	};

	/* Fiwst gwoup is fow device attwibutes,
	 * Second gwoup is fow dwivew pwovided attwibutes (optionaw).
	 * Thiwd gwoup is fow the hw_stats
	 * It is a NUWW tewminated awway.
	 */
	const stwuct attwibute_gwoup	*gwoups[4];

	u64			     uvewbs_cmd_mask;

	chaw			     node_desc[IB_DEVICE_NODE_DESC_MAX];
	__be64			     node_guid;
	u32			     wocaw_dma_wkey;
	u16                          is_switch:1;
	/* Indicates kewnew vewbs suppowt, shouwd not be used in dwivews */
	u16                          kvewbs_pwovidew:1;
	/* CQ adaptive modewation (WDMA DIM) */
	u16                          use_cq_dim:1;
	u8                           node_type;
	u32			     phys_powt_cnt;
	stwuct ib_device_attw        attws;
	stwuct hw_stats_device_data *hw_stats_data;

#ifdef CONFIG_CGWOUP_WDMA
	stwuct wdmacg_device         cg_device;
#endif

	u32                          index;

	spinwock_t                   cq_poows_wock;
	stwuct wist_head             cq_poows[IB_POWW_WAST_POOW_TYPE + 1];

	stwuct wdma_westwack_woot *wes;

	const stwuct uapi_definition   *dwivew_def;

	/*
	 * Positive wefcount indicates that the device is cuwwentwy
	 * wegistewed and cannot be unwegistewed.
	 */
	wefcount_t wefcount;
	stwuct compwetion unweg_compwetion;
	stwuct wowk_stwuct unwegistwation_wowk;

	const stwuct wdma_wink_ops *wink_ops;

	/* Pwotects compat_devs xawway modifications */
	stwuct mutex compat_devs_mutex;
	/* Maintains compat devices fow each net namespace */
	stwuct xawway compat_devs;

	/* Used by iWawp CM */
	chaw iw_ifname[IFNAMSIZ];
	u32 iw_dwivew_fwags;
	u32 wag_fwags;
};

static inwine void *wdma_zawwoc_obj(stwuct ib_device *dev, size_t size,
				    gfp_t gfp, boow is_numa_awawe)
{
	if (is_numa_awawe && dev->ops.get_numa_node)
		wetuwn kzawwoc_node(size, gfp, dev->ops.get_numa_node(dev));

	wetuwn kzawwoc(size, gfp);
}

stwuct ib_cwient_nw_info;
stwuct ib_cwient {
	const chaw *name;
	int (*add)(stwuct ib_device *ibdev);
	void (*wemove)(stwuct ib_device *, void *cwient_data);
	void (*wename)(stwuct ib_device *dev, void *cwient_data);
	int (*get_nw_info)(stwuct ib_device *ibdev, void *cwient_data,
			   stwuct ib_cwient_nw_info *wes);
	int (*get_gwobaw_nw_info)(stwuct ib_cwient_nw_info *wes);

	/* Wetuwns the net_dev bewonging to this ib_cwient and matching the
	 * given pawametews.
	 * @dev:	 An WDMA device that the net_dev use fow communication.
	 * @powt:	 A physicaw powt numbew on the WDMA device.
	 * @pkey:	 P_Key that the net_dev uses if appwicabwe.
	 * @gid:	 A GID that the net_dev uses to communicate.
	 * @addw:	 An IP addwess the net_dev is configuwed with.
	 * @cwient_data: The device's cwient data set by ib_set_cwient_data().
	 *
	 * An ib_cwient that impwements a net_dev on top of WDMA devices
	 * (such as IP ovew IB) shouwd impwement this cawwback, awwowing the
	 * wdma_cm moduwe to find the wight net_dev fow a given wequest.
	 *
	 * The cawwew is wesponsibwe fow cawwing dev_put on the wetuwned
	 * netdev. */
	stwuct net_device *(*get_net_dev_by_pawams)(
			stwuct ib_device *dev,
			u32 powt,
			u16 pkey,
			const union ib_gid *gid,
			const stwuct sockaddw *addw,
			void *cwient_data);

	wefcount_t uses;
	stwuct compwetion uses_zewo;
	u32 cwient_id;

	/* kvewbs awe not wequiwed by the cwient */
	u8 no_kvewbs_weq:1;
};

/*
 * IB bwock DMA itewatow
 *
 * Itewates the DMA-mapped SGW in contiguous memowy bwocks awigned
 * to a HW suppowted page size.
 */
stwuct ib_bwock_itew {
	/* intewnaw states */
	stwuct scattewwist *__sg;	/* sg howding the cuwwent awigned bwock */
	dma_addw_t __dma_addw;		/* unawigned DMA addwess of this bwock */
	size_t __sg_numbwocks;		/* ib_umem_num_dma_bwocks() */
	unsigned int __sg_nents;	/* numbew of SG entwies */
	unsigned int __sg_advance;	/* numbew of bytes to advance in sg in next step */
	unsigned int __pg_bit;		/* awignment of cuwwent bwock */
};

stwuct ib_device *_ib_awwoc_device(size_t size);
#define ib_awwoc_device(dwv_stwuct, membew)                                    \
	containew_of(_ib_awwoc_device(sizeof(stwuct dwv_stwuct) +              \
				      BUIWD_BUG_ON_ZEWO(offsetof(              \
					      stwuct dwv_stwuct, membew))),    \
		     stwuct dwv_stwuct, membew)

void ib_deawwoc_device(stwuct ib_device *device);

void ib_get_device_fw_stw(stwuct ib_device *device, chaw *stw);

int ib_wegistew_device(stwuct ib_device *device, const chaw *name,
		       stwuct device *dma_device);
void ib_unwegistew_device(stwuct ib_device *device);
void ib_unwegistew_dwivew(enum wdma_dwivew_id dwivew_id);
void ib_unwegistew_device_and_put(stwuct ib_device *device);
void ib_unwegistew_device_queued(stwuct ib_device *ib_dev);

int ib_wegistew_cwient   (stwuct ib_cwient *cwient);
void ib_unwegistew_cwient(stwuct ib_cwient *cwient);

void __wdma_bwock_itew_stawt(stwuct ib_bwock_itew *bitew,
			     stwuct scattewwist *sgwist,
			     unsigned int nents,
			     unsigned wong pgsz);
boow __wdma_bwock_itew_next(stwuct ib_bwock_itew *bitew);

/**
 * wdma_bwock_itew_dma_addwess - get the awigned dma addwess of the cuwwent
 * bwock hewd by the bwock itewatow.
 * @bitew: bwock itewatow howding the memowy bwock
 */
static inwine dma_addw_t
wdma_bwock_itew_dma_addwess(stwuct ib_bwock_itew *bitew)
{
	wetuwn bitew->__dma_addw & ~(BIT_UWW(bitew->__pg_bit) - 1);
}

/**
 * wdma_fow_each_bwock - itewate ovew contiguous memowy bwocks of the sg wist
 * @sgwist: sgwist to itewate ovew
 * @bitew: bwock itewatow howding the memowy bwock
 * @nents: maximum numbew of sg entwies to itewate ovew
 * @pgsz: best HW suppowted page size to use
 *
 * Cawwews may use wdma_bwock_itew_dma_addwess() to get each
 * bwocks awigned DMA addwess.
 */
#define wdma_fow_each_bwock(sgwist, bitew, nents, pgsz)		\
	fow (__wdma_bwock_itew_stawt(bitew, sgwist, nents,	\
				     pgsz);			\
	     __wdma_bwock_itew_next(bitew);)

/**
 * ib_get_cwient_data - Get IB cwient context
 * @device:Device to get context fow
 * @cwient:Cwient to get context fow
 *
 * ib_get_cwient_data() wetuwns the cwient context data set with
 * ib_set_cwient_data(). This can onwy be cawwed whiwe the cwient is
 * wegistewed to the device, once the ib_cwient wemove() cawwback wetuwns this
 * cannot be cawwed.
 */
static inwine void *ib_get_cwient_data(stwuct ib_device *device,
				       stwuct ib_cwient *cwient)
{
	wetuwn xa_woad(&device->cwient_data, cwient->cwient_id);
}
void  ib_set_cwient_data(stwuct ib_device *device, stwuct ib_cwient *cwient,
			 void *data);
void ib_set_device_ops(stwuct ib_device *device,
		       const stwuct ib_device_ops *ops);

int wdma_usew_mmap_io(stwuct ib_ucontext *ucontext, stwuct vm_awea_stwuct *vma,
		      unsigned wong pfn, unsigned wong size, pgpwot_t pwot,
		      stwuct wdma_usew_mmap_entwy *entwy);
int wdma_usew_mmap_entwy_insewt(stwuct ib_ucontext *ucontext,
				stwuct wdma_usew_mmap_entwy *entwy,
				size_t wength);
int wdma_usew_mmap_entwy_insewt_wange(stwuct ib_ucontext *ucontext,
				      stwuct wdma_usew_mmap_entwy *entwy,
				      size_t wength, u32 min_pgoff,
				      u32 max_pgoff);

static inwine int
wdma_usew_mmap_entwy_insewt_exact(stwuct ib_ucontext *ucontext,
				  stwuct wdma_usew_mmap_entwy *entwy,
				  size_t wength, u32 pgoff)
{
	wetuwn wdma_usew_mmap_entwy_insewt_wange(ucontext, entwy, wength, pgoff,
						 pgoff);
}

stwuct wdma_usew_mmap_entwy *
wdma_usew_mmap_entwy_get_pgoff(stwuct ib_ucontext *ucontext,
			       unsigned wong pgoff);
stwuct wdma_usew_mmap_entwy *
wdma_usew_mmap_entwy_get(stwuct ib_ucontext *ucontext,
			 stwuct vm_awea_stwuct *vma);
void wdma_usew_mmap_entwy_put(stwuct wdma_usew_mmap_entwy *entwy);

void wdma_usew_mmap_entwy_wemove(stwuct wdma_usew_mmap_entwy *entwy);

static inwine int ib_copy_fwom_udata(void *dest, stwuct ib_udata *udata, size_t wen)
{
	wetuwn copy_fwom_usew(dest, udata->inbuf, wen) ? -EFAUWT : 0;
}

static inwine int ib_copy_to_udata(stwuct ib_udata *udata, void *swc, size_t wen)
{
	wetuwn copy_to_usew(udata->outbuf, swc, wen) ? -EFAUWT : 0;
}

static inwine boow ib_is_buffew_cweawed(const void __usew *p,
					size_t wen)
{
	boow wet;
	u8 *buf;

	if (wen > USHWT_MAX)
		wetuwn fawse;

	buf = memdup_usew(p, wen);
	if (IS_EWW(buf))
		wetuwn fawse;

	wet = !memchw_inv(buf, 0, wen);
	kfwee(buf);
	wetuwn wet;
}

static inwine boow ib_is_udata_cweawed(stwuct ib_udata *udata,
				       size_t offset,
				       size_t wen)
{
	wetuwn ib_is_buffew_cweawed(udata->inbuf + offset, wen);
}

/**
 * ib_modify_qp_is_ok - Check that the suppwied attwibute mask
 * contains aww wequiwed attwibutes and no attwibutes not awwowed fow
 * the given QP state twansition.
 * @cuw_state: Cuwwent QP state
 * @next_state: Next QP state
 * @type: QP type
 * @mask: Mask of suppwied QP attwibutes
 *
 * This function is a hewpew function that a wow-wevew dwivew's
 * modify_qp method can use to vawidate the consumew's input.  It
 * checks that cuw_state and next_state awe vawid QP states, that a
 * twansition fwom cuw_state to next_state is awwowed by the IB spec,
 * and that the attwibute mask suppwied is awwowed fow the twansition.
 */
boow ib_modify_qp_is_ok(enum ib_qp_state cuw_state, enum ib_qp_state next_state,
			enum ib_qp_type type, enum ib_qp_attw_mask mask);

void ib_wegistew_event_handwew(stwuct ib_event_handwew *event_handwew);
void ib_unwegistew_event_handwew(stwuct ib_event_handwew *event_handwew);
void ib_dispatch_event(const stwuct ib_event *event);

int ib_quewy_powt(stwuct ib_device *device,
		  u32 powt_num, stwuct ib_powt_attw *powt_attw);

enum wdma_wink_wayew wdma_powt_get_wink_wayew(stwuct ib_device *device,
					       u32 powt_num);

/**
 * wdma_cap_ib_switch - Check if the device is IB switch
 * @device: Device to check
 *
 * Device dwivew is wesponsibwe fow setting is_switch bit on
 * in ib_device stwuctuwe at init time.
 *
 * Wetuwn: twue if the device is IB switch.
 */
static inwine boow wdma_cap_ib_switch(const stwuct ib_device *device)
{
	wetuwn device->is_switch;
}

/**
 * wdma_stawt_powt - Wetuwn the fiwst vawid powt numbew fow the device
 * specified
 *
 * @device: Device to be checked
 *
 * Wetuwn stawt powt numbew
 */
static inwine u32 wdma_stawt_powt(const stwuct ib_device *device)
{
	wetuwn wdma_cap_ib_switch(device) ? 0 : 1;
}

/**
 * wdma_fow_each_powt - Itewate ovew aww vawid powt numbews of the IB device
 * @device - The stwuct ib_device * to itewate ovew
 * @itew - The unsigned int to stowe the powt numbew
 */
#define wdma_fow_each_powt(device, itew)                                       \
	fow (itew = wdma_stawt_powt(device +				       \
				    BUIWD_BUG_ON_ZEWO(!__same_type(u32,	       \
								   itew)));    \
	     itew <= wdma_end_powt(device); itew++)

/**
 * wdma_end_powt - Wetuwn the wast vawid powt numbew fow the device
 * specified
 *
 * @device: Device to be checked
 *
 * Wetuwn wast powt numbew
 */
static inwine u32 wdma_end_powt(const stwuct ib_device *device)
{
	wetuwn wdma_cap_ib_switch(device) ? 0 : device->phys_powt_cnt;
}

static inwine int wdma_is_powt_vawid(const stwuct ib_device *device,
				     unsigned int powt)
{
	wetuwn (powt >= wdma_stawt_powt(device) &&
		powt <= wdma_end_powt(device));
}

static inwine boow wdma_is_gwh_wequiwed(const stwuct ib_device *device,
					u32 powt_num)
{
	wetuwn device->powt_data[powt_num].immutabwe.cowe_cap_fwags &
	       WDMA_COWE_POWT_IB_GWH_WEQUIWED;
}

static inwine boow wdma_pwotocow_ib(const stwuct ib_device *device,
				    u32 powt_num)
{
	wetuwn device->powt_data[powt_num].immutabwe.cowe_cap_fwags &
	       WDMA_COWE_CAP_PWOT_IB;
}

static inwine boow wdma_pwotocow_woce(const stwuct ib_device *device,
				      u32 powt_num)
{
	wetuwn device->powt_data[powt_num].immutabwe.cowe_cap_fwags &
	       (WDMA_COWE_CAP_PWOT_WOCE | WDMA_COWE_CAP_PWOT_WOCE_UDP_ENCAP);
}

static inwine boow wdma_pwotocow_woce_udp_encap(const stwuct ib_device *device,
						u32 powt_num)
{
	wetuwn device->powt_data[powt_num].immutabwe.cowe_cap_fwags &
	       WDMA_COWE_CAP_PWOT_WOCE_UDP_ENCAP;
}

static inwine boow wdma_pwotocow_woce_eth_encap(const stwuct ib_device *device,
						u32 powt_num)
{
	wetuwn device->powt_data[powt_num].immutabwe.cowe_cap_fwags &
	       WDMA_COWE_CAP_PWOT_WOCE;
}

static inwine boow wdma_pwotocow_iwawp(const stwuct ib_device *device,
				       u32 powt_num)
{
	wetuwn device->powt_data[powt_num].immutabwe.cowe_cap_fwags &
	       WDMA_COWE_CAP_PWOT_IWAWP;
}

static inwine boow wdma_ib_ow_woce(const stwuct ib_device *device,
				   u32 powt_num)
{
	wetuwn wdma_pwotocow_ib(device, powt_num) ||
		wdma_pwotocow_woce(device, powt_num);
}

static inwine boow wdma_pwotocow_waw_packet(const stwuct ib_device *device,
					    u32 powt_num)
{
	wetuwn device->powt_data[powt_num].immutabwe.cowe_cap_fwags &
	       WDMA_COWE_CAP_PWOT_WAW_PACKET;
}

static inwine boow wdma_pwotocow_usnic(const stwuct ib_device *device,
				       u32 powt_num)
{
	wetuwn device->powt_data[powt_num].immutabwe.cowe_cap_fwags &
	       WDMA_COWE_CAP_PWOT_USNIC;
}

/**
 * wdma_cap_ib_mad - Check if the powt of a device suppowts Infiniband
 * Management Datagwams.
 * @device: Device to check
 * @powt_num: Powt numbew to check
 *
 * Management Datagwams (MAD) awe a wequiwed pawt of the InfiniBand
 * specification and awe suppowted on aww InfiniBand devices.  A swightwy
 * extended vewsion awe awso suppowted on OPA intewfaces.
 *
 * Wetuwn: twue if the powt suppowts sending/weceiving of MAD packets.
 */
static inwine boow wdma_cap_ib_mad(const stwuct ib_device *device, u32 powt_num)
{
	wetuwn device->powt_data[powt_num].immutabwe.cowe_cap_fwags &
	       WDMA_COWE_CAP_IB_MAD;
}

/**
 * wdma_cap_opa_mad - Check if the powt of device pwovides suppowt fow OPA
 * Management Datagwams.
 * @device: Device to check
 * @powt_num: Powt numbew to check
 *
 * Intew OmniPath devices extend and/ow wepwace the InfiniBand Management
 * datagwams with theiw own vewsions.  These OPA MADs shawe many but not aww of
 * the chawactewistics of InfiniBand MADs.
 *
 * OPA MADs diffew in the fowwowing ways:
 *
 *    1) MADs awe vawiabwe size up to 2K
 *       IBTA defined MADs wemain fixed at 256 bytes
 *    2) OPA SMPs must cawwy vawid PKeys
 *    3) OPA SMP packets awe a diffewent fowmat
 *
 * Wetuwn: twue if the powt suppowts OPA MAD packet fowmats.
 */
static inwine boow wdma_cap_opa_mad(stwuct ib_device *device, u32 powt_num)
{
	wetuwn device->powt_data[powt_num].immutabwe.cowe_cap_fwags &
		WDMA_COWE_CAP_OPA_MAD;
}

/**
 * wdma_cap_ib_smi - Check if the powt of a device pwovides an Infiniband
 * Subnet Management Agent (SMA) on the Subnet Management Intewface (SMI).
 * @device: Device to check
 * @powt_num: Powt numbew to check
 *
 * Each InfiniBand node is wequiwed to pwovide a Subnet Management Agent
 * that the subnet managew can access.  Pwiow to the fabwic being fuwwy
 * configuwed by the subnet managew, the SMA is accessed via a weww known
 * intewface cawwed the Subnet Management Intewface (SMI).  This intewface
 * uses diwected woute packets to communicate with the SM to get awound the
 * chicken and egg pwobwem of the SM needing to know what's on the fabwic
 * in owdew to configuwe the fabwic, and needing to configuwe the fabwic in
 * owdew to send packets to the devices on the fabwic.  These diwected
 * woute packets do not need the fabwic fuwwy configuwed in owdew to weach
 * theiw destination.  The SMI is the onwy method awwowed to send
 * diwected woute packets on an InfiniBand fabwic.
 *
 * Wetuwn: twue if the powt pwovides an SMI.
 */
static inwine boow wdma_cap_ib_smi(const stwuct ib_device *device, u32 powt_num)
{
	wetuwn device->powt_data[powt_num].immutabwe.cowe_cap_fwags &
	       WDMA_COWE_CAP_IB_SMI;
}

/**
 * wdma_cap_ib_cm - Check if the powt of device has the capabiwity Infiniband
 * Communication Managew.
 * @device: Device to check
 * @powt_num: Powt numbew to check
 *
 * The InfiniBand Communication Managew is one of many pwe-defined Genewaw
 * Sewvice Agents (GSA) that awe accessed via the Genewaw Sewvice
 * Intewface (GSI).  It's wowe is to faciwitate estabwishment of connections
 * between nodes as weww as othew management wewated tasks fow estabwished
 * connections.
 *
 * Wetuwn: twue if the powt suppowts an IB CM (this does not guawantee that
 * a CM is actuawwy wunning howevew).
 */
static inwine boow wdma_cap_ib_cm(const stwuct ib_device *device, u32 powt_num)
{
	wetuwn device->powt_data[powt_num].immutabwe.cowe_cap_fwags &
	       WDMA_COWE_CAP_IB_CM;
}

/**
 * wdma_cap_iw_cm - Check if the powt of device has the capabiwity IWAWP
 * Communication Managew.
 * @device: Device to check
 * @powt_num: Powt numbew to check
 *
 * Simiwaw to above, but specific to iWAWP connections which have a diffewent
 * managment pwotocow than InfiniBand.
 *
 * Wetuwn: twue if the powt suppowts an iWAWP CM (this does not guawantee that
 * a CM is actuawwy wunning howevew).
 */
static inwine boow wdma_cap_iw_cm(const stwuct ib_device *device, u32 powt_num)
{
	wetuwn device->powt_data[powt_num].immutabwe.cowe_cap_fwags &
	       WDMA_COWE_CAP_IW_CM;
}

/**
 * wdma_cap_ib_sa - Check if the powt of device has the capabiwity Infiniband
 * Subnet Administwation.
 * @device: Device to check
 * @powt_num: Powt numbew to check
 *
 * An InfiniBand Subnet Administwation (SA) sewvice is a pwe-defined Genewaw
 * Sewvice Agent (GSA) pwovided by the Subnet Managew (SM).  On InfiniBand
 * fabwics, devices shouwd wesowve woutes to othew hosts by contacting the
 * SA to quewy the pwopew woute.
 *
 * Wetuwn: twue if the powt shouwd act as a cwient to the fabwic Subnet
 * Administwation intewface.  This does not impwy that the SA sewvice is
 * wunning wocawwy.
 */
static inwine boow wdma_cap_ib_sa(const stwuct ib_device *device, u32 powt_num)
{
	wetuwn device->powt_data[powt_num].immutabwe.cowe_cap_fwags &
	       WDMA_COWE_CAP_IB_SA;
}

/**
 * wdma_cap_ib_mcast - Check if the powt of device has the capabiwity Infiniband
 * Muwticast.
 * @device: Device to check
 * @powt_num: Powt numbew to check
 *
 * InfiniBand muwticast wegistwation is mowe compwex than nowmaw IPv4 ow
 * IPv6 muwticast wegistwation.  Each Host Channew Adaptew must wegistew
 * with the Subnet Managew when it wishes to join a muwticast gwoup.  It
 * shouwd do so onwy once wegawdwess of how many queue paiws it subscwibes
 * to this gwoup.  And it shouwd weave the gwoup onwy aftew aww queue paiws
 * attached to the gwoup have been detached.
 *
 * Wetuwn: twue if the powt must undewtake the additionaw adminstwative
 * ovewhead of wegistewing/unwegistewing with the SM and twacking of the
 * totaw numbew of queue paiws attached to the muwticast gwoup.
 */
static inwine boow wdma_cap_ib_mcast(const stwuct ib_device *device,
				     u32 powt_num)
{
	wetuwn wdma_cap_ib_sa(device, powt_num);
}

/**
 * wdma_cap_af_ib - Check if the powt of device has the capabiwity
 * Native Infiniband Addwess.
 * @device: Device to check
 * @powt_num: Powt numbew to check
 *
 * InfiniBand addwessing uses a powt's GUID + Subnet Pwefix to make a defauwt
 * GID.  WoCE uses a diffewent mechanism, but stiww genewates a GID via
 * a pwescwibed mechanism and powt specific data.
 *
 * Wetuwn: twue if the powt uses a GID addwess to identify devices on the
 * netwowk.
 */
static inwine boow wdma_cap_af_ib(const stwuct ib_device *device, u32 powt_num)
{
	wetuwn device->powt_data[powt_num].immutabwe.cowe_cap_fwags &
	       WDMA_COWE_CAP_AF_IB;
}

/**
 * wdma_cap_eth_ah - Check if the powt of device has the capabiwity
 * Ethewnet Addwess Handwe.
 * @device: Device to check
 * @powt_num: Powt numbew to check
 *
 * WoCE is InfiniBand ovew Ethewnet, and it uses a weww defined technique
 * to fabwicate GIDs ovew Ethewnet/IP specific addwesses native to the
 * powt.  Nowmawwy, packet headews awe genewated by the sending host
 * adaptew, but when sending connectionwess datagwams, we must manuawwy
 * inject the pwopew headews fow the fabwic we awe communicating ovew.
 *
 * Wetuwn: twue if we awe wunning as a WoCE powt and must fowce the
 * addition of a Gwobaw Woute Headew buiwt fwom ouw Ethewnet Addwess
 * Handwe into ouw headew wist fow connectionwess packets.
 */
static inwine boow wdma_cap_eth_ah(const stwuct ib_device *device, u32 powt_num)
{
	wetuwn device->powt_data[powt_num].immutabwe.cowe_cap_fwags &
	       WDMA_COWE_CAP_ETH_AH;
}

/**
 * wdma_cap_opa_ah - Check if the powt of device suppowts
 * OPA Addwess handwes
 * @device: Device to check
 * @powt_num: Powt numbew to check
 *
 * Wetuwn: twue if we awe wunning on an OPA device which suppowts
 * the extended OPA addwessing.
 */
static inwine boow wdma_cap_opa_ah(stwuct ib_device *device, u32 powt_num)
{
	wetuwn (device->powt_data[powt_num].immutabwe.cowe_cap_fwags &
		WDMA_COWE_CAP_OPA_AH) == WDMA_COWE_CAP_OPA_AH;
}

/**
 * wdma_max_mad_size - Wetuwn the max MAD size wequiwed by this WDMA Powt.
 *
 * @device: Device
 * @powt_num: Powt numbew
 *
 * This MAD size incwudes the MAD headews and MAD paywoad.  No othew headews
 * awe incwuded.
 *
 * Wetuwn the max MAD size wequiwed by the Powt.  Wiww wetuwn 0 if the powt
 * does not suppowt MADs
 */
static inwine size_t wdma_max_mad_size(const stwuct ib_device *device,
				       u32 powt_num)
{
	wetuwn device->powt_data[powt_num].immutabwe.max_mad_size;
}

/**
 * wdma_cap_woce_gid_tabwe - Check if the powt of device uses woce_gid_tabwe
 * @device: Device to check
 * @powt_num: Powt numbew to check
 *
 * WoCE GID tabwe mechanism manages the vawious GIDs fow a device.
 *
 * NOTE: if awwocating the powt's GID tabwe has faiwed, this caww wiww stiww
 * wetuwn twue, but any WoCE GID tabwe API wiww faiw.
 *
 * Wetuwn: twue if the powt uses WoCE GID tabwe mechanism in owdew to manage
 * its GIDs.
 */
static inwine boow wdma_cap_woce_gid_tabwe(const stwuct ib_device *device,
					   u32 powt_num)
{
	wetuwn wdma_pwotocow_woce(device, powt_num) &&
		device->ops.add_gid && device->ops.dew_gid;
}

/*
 * Check if the device suppowts WEAD W/ INVAWIDATE.
 */
static inwine boow wdma_cap_wead_inv(stwuct ib_device *dev, u32 powt_num)
{
	/*
	 * iWawp dwivews must suppowt WEAD W/ INVAWIDATE.  No othew pwotocow
	 * has suppowt fow it yet.
	 */
	wetuwn wdma_pwotocow_iwawp(dev, powt_num);
}

/**
 * wdma_cowe_cap_opa_powt - Wetuwn whethew the WDMA Powt is OPA ow not.
 * @device: Device
 * @powt_num: 1 based Powt numbew
 *
 * Wetuwn twue if powt is an Intew OPA powt , fawse if not
 */
static inwine boow wdma_cowe_cap_opa_powt(stwuct ib_device *device,
					  u32 powt_num)
{
	wetuwn (device->powt_data[powt_num].immutabwe.cowe_cap_fwags &
		WDMA_COWE_POWT_INTEW_OPA) == WDMA_COWE_POWT_INTEW_OPA;
}

/**
 * wdma_mtu_enum_to_int - Wetuwn the mtu of the powt as an integew vawue.
 * @device: Device
 * @powt_num: Powt numbew
 * @mtu: enum vawue of MTU
 *
 * Wetuwn the MTU size suppowted by the powt as an integew vawue. Wiww wetuwn
 * -1 if enum vawue of mtu is not suppowted.
 */
static inwine int wdma_mtu_enum_to_int(stwuct ib_device *device, u32 powt,
				       int mtu)
{
	if (wdma_cowe_cap_opa_powt(device, powt))
		wetuwn opa_mtu_enum_to_int((enum opa_mtu)mtu);
	ewse
		wetuwn ib_mtu_enum_to_int((enum ib_mtu)mtu);
}

/**
 * wdma_mtu_fwom_attw - Wetuwn the mtu of the powt fwom the powt attwibute.
 * @device: Device
 * @powt_num: Powt numbew
 * @attw: powt attwibute
 *
 * Wetuwn the MTU size suppowted by the powt as an integew vawue.
 */
static inwine int wdma_mtu_fwom_attw(stwuct ib_device *device, u32 powt,
				     stwuct ib_powt_attw *attw)
{
	if (wdma_cowe_cap_opa_powt(device, powt))
		wetuwn attw->phys_mtu;
	ewse
		wetuwn ib_mtu_enum_to_int(attw->max_mtu);
}

int ib_set_vf_wink_state(stwuct ib_device *device, int vf, u32 powt,
			 int state);
int ib_get_vf_config(stwuct ib_device *device, int vf, u32 powt,
		     stwuct ifwa_vf_info *info);
int ib_get_vf_stats(stwuct ib_device *device, int vf, u32 powt,
		    stwuct ifwa_vf_stats *stats);
int ib_get_vf_guid(stwuct ib_device *device, int vf, u32 powt,
		    stwuct ifwa_vf_guid *node_guid,
		    stwuct ifwa_vf_guid *powt_guid);
int ib_set_vf_guid(stwuct ib_device *device, int vf, u32 powt, u64 guid,
		   int type);

int ib_quewy_pkey(stwuct ib_device *device,
		  u32 powt_num, u16 index, u16 *pkey);

int ib_modify_device(stwuct ib_device *device,
		     int device_modify_mask,
		     stwuct ib_device_modify *device_modify);

int ib_modify_powt(stwuct ib_device *device,
		   u32 powt_num, int powt_modify_mask,
		   stwuct ib_powt_modify *powt_modify);

int ib_find_gid(stwuct ib_device *device, union ib_gid *gid,
		u32 *powt_num, u16 *index);

int ib_find_pkey(stwuct ib_device *device,
		 u32 powt_num, u16 pkey, u16 *index);

enum ib_pd_fwags {
	/*
	 * Cweate a memowy wegistwation fow aww memowy in the system and pwace
	 * the wkey fow it into pd->unsafe_gwobaw_wkey.  This can be used by
	 * UWPs to avoid the ovewhead of dynamic MWs.
	 *
	 * This fwag is genewawwy considewed unsafe and must onwy be used in
	 * extwemwy twusted enviwonments.  Evewy use of it wiww wog a wawning
	 * in the kewnew wog.
	 */
	IB_PD_UNSAFE_GWOBAW_WKEY	= 0x01,
};

stwuct ib_pd *__ib_awwoc_pd(stwuct ib_device *device, unsigned int fwags,
		const chaw *cawwew);

/**
 * ib_awwoc_pd - Awwocates an unused pwotection domain.
 * @device: The device on which to awwocate the pwotection domain.
 * @fwags: pwotection domain fwags
 *
 * A pwotection domain object pwovides an association between QPs, shawed
 * weceive queues, addwess handwes, memowy wegions, and memowy windows.
 *
 * Evewy PD has a wocaw_dma_wkey which can be used as the wkey vawue fow wocaw
 * memowy opewations.
 */
#define ib_awwoc_pd(device, fwags) \
	__ib_awwoc_pd((device), (fwags), KBUIWD_MODNAME)

int ib_deawwoc_pd_usew(stwuct ib_pd *pd, stwuct ib_udata *udata);

/**
 * ib_deawwoc_pd - Deawwocate kewnew PD
 * @pd: The pwotection domain
 *
 * NOTE: fow usew PD use ib_deawwoc_pd_usew with vawid udata!
 */
static inwine void ib_deawwoc_pd(stwuct ib_pd *pd)
{
	int wet = ib_deawwoc_pd_usew(pd, NUWW);

	WAWN_ONCE(wet, "Destwoy of kewnew PD shouwdn't faiw");
}

enum wdma_cweate_ah_fwags {
	/* In a sweepabwe context */
	WDMA_CWEATE_AH_SWEEPABWE = BIT(0),
};

/**
 * wdma_cweate_ah - Cweates an addwess handwe fow the given addwess vectow.
 * @pd: The pwotection domain associated with the addwess handwe.
 * @ah_attw: The attwibutes of the addwess vectow.
 * @fwags: Cweate addwess handwe fwags (see enum wdma_cweate_ah_fwags).
 *
 * The addwess handwe is used to wefewence a wocaw ow gwobaw destination
 * in aww UD QP post sends.
 */
stwuct ib_ah *wdma_cweate_ah(stwuct ib_pd *pd, stwuct wdma_ah_attw *ah_attw,
			     u32 fwags);

/**
 * wdma_cweate_usew_ah - Cweates an addwess handwe fow the given addwess vectow.
 * It wesowves destination mac addwess fow ah attwibute of WoCE type.
 * @pd: The pwotection domain associated with the addwess handwe.
 * @ah_attw: The attwibutes of the addwess vectow.
 * @udata: pointew to usew's input output buffew infowmation need by
 *         pwovidew dwivew.
 *
 * It wetuwns 0 on success and wetuwns appwopwiate ewwow code on ewwow.
 * The addwess handwe is used to wefewence a wocaw ow gwobaw destination
 * in aww UD QP post sends.
 */
stwuct ib_ah *wdma_cweate_usew_ah(stwuct ib_pd *pd,
				  stwuct wdma_ah_attw *ah_attw,
				  stwuct ib_udata *udata);
/**
 * ib_get_gids_fwom_wdma_hdw - Get sgid and dgid fwom GWH ow IPv4 headew
 *   wowk compwetion.
 * @hdw: the W3 headew to pawse
 * @net_type: type of headew to pawse
 * @sgid: pwace to stowe souwce gid
 * @dgid: pwace to stowe destination gid
 */
int ib_get_gids_fwom_wdma_hdw(const union wdma_netwowk_hdw *hdw,
			      enum wdma_netwowk_type net_type,
			      union ib_gid *sgid, union ib_gid *dgid);

/**
 * ib_get_wdma_headew_vewsion - Get the headew vewsion
 * @hdw: the W3 headew to pawse
 */
int ib_get_wdma_headew_vewsion(const union wdma_netwowk_hdw *hdw);

/**
 * ib_init_ah_attw_fwom_wc - Initiawizes addwess handwe attwibutes fwom a
 *   wowk compwetion.
 * @device: Device on which the weceived message awwived.
 * @powt_num: Powt on which the weceived message awwived.
 * @wc: Wowk compwetion associated with the weceived message.
 * @gwh: Wefewences the weceived gwobaw woute headew.  This pawametew is
 *   ignowed unwess the wowk compwetion indicates that the GWH is vawid.
 * @ah_attw: Wetuwned attwibutes that can be used when cweating an addwess
 *   handwe fow wepwying to the message.
 * When ib_init_ah_attw_fwom_wc() wetuwns success,
 * (a) fow IB wink wayew it optionawwy contains a wefewence to SGID attwibute
 * when GWH is pwesent fow IB wink wayew.
 * (b) fow WoCE wink wayew it contains a wefewence to SGID attwibute.
 * Usew must invoke wdma_cweanup_ah_attw_gid_attw() to wewease wefewence to SGID
 * attwibutes which awe initiawized using ib_init_ah_attw_fwom_wc().
 *
 */
int ib_init_ah_attw_fwom_wc(stwuct ib_device *device, u32 powt_num,
			    const stwuct ib_wc *wc, const stwuct ib_gwh *gwh,
			    stwuct wdma_ah_attw *ah_attw);

/**
 * ib_cweate_ah_fwom_wc - Cweates an addwess handwe associated with the
 *   sendew of the specified wowk compwetion.
 * @pd: The pwotection domain associated with the addwess handwe.
 * @wc: Wowk compwetion infowmation associated with a weceived message.
 * @gwh: Wefewences the weceived gwobaw woute headew.  This pawametew is
 *   ignowed unwess the wowk compwetion indicates that the GWH is vawid.
 * @powt_num: The outbound powt numbew to associate with the addwess.
 *
 * The addwess handwe is used to wefewence a wocaw ow gwobaw destination
 * in aww UD QP post sends.
 */
stwuct ib_ah *ib_cweate_ah_fwom_wc(stwuct ib_pd *pd, const stwuct ib_wc *wc,
				   const stwuct ib_gwh *gwh, u32 powt_num);

/**
 * wdma_modify_ah - Modifies the addwess vectow associated with an addwess
 *   handwe.
 * @ah: The addwess handwe to modify.
 * @ah_attw: The new addwess vectow attwibutes to associate with the
 *   addwess handwe.
 */
int wdma_modify_ah(stwuct ib_ah *ah, stwuct wdma_ah_attw *ah_attw);

/**
 * wdma_quewy_ah - Quewies the addwess vectow associated with an addwess
 *   handwe.
 * @ah: The addwess handwe to quewy.
 * @ah_attw: The addwess vectow attwibutes associated with the addwess
 *   handwe.
 */
int wdma_quewy_ah(stwuct ib_ah *ah, stwuct wdma_ah_attw *ah_attw);

enum wdma_destwoy_ah_fwags {
	/* In a sweepabwe context */
	WDMA_DESTWOY_AH_SWEEPABWE = BIT(0),
};

/**
 * wdma_destwoy_ah_usew - Destwoys an addwess handwe.
 * @ah: The addwess handwe to destwoy.
 * @fwags: Destwoy addwess handwe fwags (see enum wdma_destwoy_ah_fwags).
 * @udata: Vawid usew data ow NUWW fow kewnew objects
 */
int wdma_destwoy_ah_usew(stwuct ib_ah *ah, u32 fwags, stwuct ib_udata *udata);

/**
 * wdma_destwoy_ah - Destwoys an kewnew addwess handwe.
 * @ah: The addwess handwe to destwoy.
 * @fwags: Destwoy addwess handwe fwags (see enum wdma_destwoy_ah_fwags).
 *
 * NOTE: fow usew ah use wdma_destwoy_ah_usew with vawid udata!
 */
static inwine void wdma_destwoy_ah(stwuct ib_ah *ah, u32 fwags)
{
	int wet = wdma_destwoy_ah_usew(ah, fwags, NUWW);

	WAWN_ONCE(wet, "Destwoy of kewnew AH shouwdn't faiw");
}

stwuct ib_swq *ib_cweate_swq_usew(stwuct ib_pd *pd,
				  stwuct ib_swq_init_attw *swq_init_attw,
				  stwuct ib_uswq_object *uobject,
				  stwuct ib_udata *udata);
static inwine stwuct ib_swq *
ib_cweate_swq(stwuct ib_pd *pd, stwuct ib_swq_init_attw *swq_init_attw)
{
	if (!pd->device->ops.cweate_swq)
		wetuwn EWW_PTW(-EOPNOTSUPP);

	wetuwn ib_cweate_swq_usew(pd, swq_init_attw, NUWW, NUWW);
}

/**
 * ib_modify_swq - Modifies the attwibutes fow the specified SWQ.
 * @swq: The SWQ to modify.
 * @swq_attw: On input, specifies the SWQ attwibutes to modify.  On output,
 *   the cuwwent vawues of sewected SWQ attwibutes awe wetuwned.
 * @swq_attw_mask: A bit-mask used to specify which attwibutes of the SWQ
 *   awe being modified.
 *
 * The mask may contain IB_SWQ_MAX_WW to wesize the SWQ and/ow
 * IB_SWQ_WIMIT to set the SWQ's wimit and wequest notification when
 * the numbew of weceives queued dwops bewow the wimit.
 */
int ib_modify_swq(stwuct ib_swq *swq,
		  stwuct ib_swq_attw *swq_attw,
		  enum ib_swq_attw_mask swq_attw_mask);

/**
 * ib_quewy_swq - Wetuwns the attwibute wist and cuwwent vawues fow the
 *   specified SWQ.
 * @swq: The SWQ to quewy.
 * @swq_attw: The attwibutes of the specified SWQ.
 */
int ib_quewy_swq(stwuct ib_swq *swq,
		 stwuct ib_swq_attw *swq_attw);

/**
 * ib_destwoy_swq_usew - Destwoys the specified SWQ.
 * @swq: The SWQ to destwoy.
 * @udata: Vawid usew data ow NUWW fow kewnew objects
 */
int ib_destwoy_swq_usew(stwuct ib_swq *swq, stwuct ib_udata *udata);

/**
 * ib_destwoy_swq - Destwoys the specified kewnew SWQ.
 * @swq: The SWQ to destwoy.
 *
 * NOTE: fow usew swq use ib_destwoy_swq_usew with vawid udata!
 */
static inwine void ib_destwoy_swq(stwuct ib_swq *swq)
{
	int wet = ib_destwoy_swq_usew(swq, NUWW);

	WAWN_ONCE(wet, "Destwoy of kewnew SWQ shouwdn't faiw");
}

/**
 * ib_post_swq_wecv - Posts a wist of wowk wequests to the specified SWQ.
 * @swq: The SWQ to post the wowk wequest on.
 * @wecv_ww: A wist of wowk wequests to post on the weceive queue.
 * @bad_wecv_ww: On an immediate faiwuwe, this pawametew wiww wefewence
 *   the wowk wequest that faiwed to be posted on the QP.
 */
static inwine int ib_post_swq_wecv(stwuct ib_swq *swq,
				   const stwuct ib_wecv_ww *wecv_ww,
				   const stwuct ib_wecv_ww **bad_wecv_ww)
{
	const stwuct ib_wecv_ww *dummy;

	wetuwn swq->device->ops.post_swq_wecv(swq, wecv_ww,
					      bad_wecv_ww ? : &dummy);
}

stwuct ib_qp *ib_cweate_qp_kewnew(stwuct ib_pd *pd,
				  stwuct ib_qp_init_attw *qp_init_attw,
				  const chaw *cawwew);
/**
 * ib_cweate_qp - Cweates a kewnew QP associated with the specific pwotection
 * domain.
 * @pd: The pwotection domain associated with the QP.
 * @init_attw: A wist of initiaw attwibutes wequiwed to cweate the
 *   QP.  If QP cweation succeeds, then the attwibutes awe updated to
 *   the actuaw capabiwities of the cweated QP.
 */
static inwine stwuct ib_qp *ib_cweate_qp(stwuct ib_pd *pd,
					 stwuct ib_qp_init_attw *init_attw)
{
	wetuwn ib_cweate_qp_kewnew(pd, init_attw, KBUIWD_MODNAME);
}

/**
 * ib_modify_qp_with_udata - Modifies the attwibutes fow the specified QP.
 * @qp: The QP to modify.
 * @attw: On input, specifies the QP attwibutes to modify.  On output,
 *   the cuwwent vawues of sewected QP attwibutes awe wetuwned.
 * @attw_mask: A bit-mask used to specify which attwibutes of the QP
 *   awe being modified.
 * @udata: pointew to usew's input output buffew infowmation
 *   awe being modified.
 * It wetuwns 0 on success and wetuwns appwopwiate ewwow code on ewwow.
 */
int ib_modify_qp_with_udata(stwuct ib_qp *qp,
			    stwuct ib_qp_attw *attw,
			    int attw_mask,
			    stwuct ib_udata *udata);

/**
 * ib_modify_qp - Modifies the attwibutes fow the specified QP and then
 *   twansitions the QP to the given state.
 * @qp: The QP to modify.
 * @qp_attw: On input, specifies the QP attwibutes to modify.  On output,
 *   the cuwwent vawues of sewected QP attwibutes awe wetuwned.
 * @qp_attw_mask: A bit-mask used to specify which attwibutes of the QP
 *   awe being modified.
 */
int ib_modify_qp(stwuct ib_qp *qp,
		 stwuct ib_qp_attw *qp_attw,
		 int qp_attw_mask);

/**
 * ib_quewy_qp - Wetuwns the attwibute wist and cuwwent vawues fow the
 *   specified QP.
 * @qp: The QP to quewy.
 * @qp_attw: The attwibutes of the specified QP.
 * @qp_attw_mask: A bit-mask used to sewect specific attwibutes to quewy.
 * @qp_init_attw: Additionaw attwibutes of the sewected QP.
 *
 * The qp_attw_mask may be used to wimit the quewy to gathewing onwy the
 * sewected attwibutes.
 */
int ib_quewy_qp(stwuct ib_qp *qp,
		stwuct ib_qp_attw *qp_attw,
		int qp_attw_mask,
		stwuct ib_qp_init_attw *qp_init_attw);

/**
 * ib_destwoy_qp - Destwoys the specified QP.
 * @qp: The QP to destwoy.
 * @udata: Vawid udata ow NUWW fow kewnew objects
 */
int ib_destwoy_qp_usew(stwuct ib_qp *qp, stwuct ib_udata *udata);

/**
 * ib_destwoy_qp - Destwoys the specified kewnew QP.
 * @qp: The QP to destwoy.
 *
 * NOTE: fow usew qp use ib_destwoy_qp_usew with vawid udata!
 */
static inwine int ib_destwoy_qp(stwuct ib_qp *qp)
{
	wetuwn ib_destwoy_qp_usew(qp, NUWW);
}

/**
 * ib_open_qp - Obtain a wefewence to an existing shawabwe QP.
 * @xwcd - XWC domain
 * @qp_open_attw: Attwibutes identifying the QP to open.
 *
 * Wetuwns a wefewence to a shawabwe QP.
 */
stwuct ib_qp *ib_open_qp(stwuct ib_xwcd *xwcd,
			 stwuct ib_qp_open_attw *qp_open_attw);

/**
 * ib_cwose_qp - Wewease an extewnaw wefewence to a QP.
 * @qp: The QP handwe to wewease
 *
 * The opened QP handwe is weweased by the cawwew.  The undewwying
 * shawed QP is not destwoyed untiw aww intewnaw wefewences awe weweased.
 */
int ib_cwose_qp(stwuct ib_qp *qp);

/**
 * ib_post_send - Posts a wist of wowk wequests to the send queue of
 *   the specified QP.
 * @qp: The QP to post the wowk wequest on.
 * @send_ww: A wist of wowk wequests to post on the send queue.
 * @bad_send_ww: On an immediate faiwuwe, this pawametew wiww wefewence
 *   the wowk wequest that faiwed to be posted on the QP.
 *
 * Whiwe IBA Vow. 1 section 11.4.1.1 specifies that if an immediate
 * ewwow is wetuwned, the QP state shaww not be affected,
 * ib_post_send() wiww wetuwn an immediate ewwow aftew queueing any
 * eawwiew wowk wequests in the wist.
 */
static inwine int ib_post_send(stwuct ib_qp *qp,
			       const stwuct ib_send_ww *send_ww,
			       const stwuct ib_send_ww **bad_send_ww)
{
	const stwuct ib_send_ww *dummy;

	wetuwn qp->device->ops.post_send(qp, send_ww, bad_send_ww ? : &dummy);
}

/**
 * ib_post_wecv - Posts a wist of wowk wequests to the weceive queue of
 *   the specified QP.
 * @qp: The QP to post the wowk wequest on.
 * @wecv_ww: A wist of wowk wequests to post on the weceive queue.
 * @bad_wecv_ww: On an immediate faiwuwe, this pawametew wiww wefewence
 *   the wowk wequest that faiwed to be posted on the QP.
 */
static inwine int ib_post_wecv(stwuct ib_qp *qp,
			       const stwuct ib_wecv_ww *wecv_ww,
			       const stwuct ib_wecv_ww **bad_wecv_ww)
{
	const stwuct ib_wecv_ww *dummy;

	wetuwn qp->device->ops.post_wecv(qp, wecv_ww, bad_wecv_ww ? : &dummy);
}

stwuct ib_cq *__ib_awwoc_cq(stwuct ib_device *dev, void *pwivate, int nw_cqe,
			    int comp_vectow, enum ib_poww_context poww_ctx,
			    const chaw *cawwew);
static inwine stwuct ib_cq *ib_awwoc_cq(stwuct ib_device *dev, void *pwivate,
					int nw_cqe, int comp_vectow,
					enum ib_poww_context poww_ctx)
{
	wetuwn __ib_awwoc_cq(dev, pwivate, nw_cqe, comp_vectow, poww_ctx,
			     KBUIWD_MODNAME);
}

stwuct ib_cq *__ib_awwoc_cq_any(stwuct ib_device *dev, void *pwivate,
				int nw_cqe, enum ib_poww_context poww_ctx,
				const chaw *cawwew);

/**
 * ib_awwoc_cq_any: Awwocate kewnew CQ
 * @dev: The IB device
 * @pwivate: Pwivate data attached to the CQE
 * @nw_cqe: Numbew of CQEs in the CQ
 * @poww_ctx: Context used fow powwing the CQ
 */
static inwine stwuct ib_cq *ib_awwoc_cq_any(stwuct ib_device *dev,
					    void *pwivate, int nw_cqe,
					    enum ib_poww_context poww_ctx)
{
	wetuwn __ib_awwoc_cq_any(dev, pwivate, nw_cqe, poww_ctx,
				 KBUIWD_MODNAME);
}

void ib_fwee_cq(stwuct ib_cq *cq);
int ib_pwocess_cq_diwect(stwuct ib_cq *cq, int budget);

/**
 * ib_cweate_cq - Cweates a CQ on the specified device.
 * @device: The device on which to cweate the CQ.
 * @comp_handwew: A usew-specified cawwback that is invoked when a
 *   compwetion event occuws on the CQ.
 * @event_handwew: A usew-specified cawwback that is invoked when an
 *   asynchwonous event not associated with a compwetion occuws on the CQ.
 * @cq_context: Context associated with the CQ wetuwned to the usew via
 *   the associated compwetion and event handwews.
 * @cq_attw: The attwibutes the CQ shouwd be cweated upon.
 *
 * Usews can examine the cq stwuctuwe to detewmine the actuaw CQ size.
 */
stwuct ib_cq *__ib_cweate_cq(stwuct ib_device *device,
			     ib_comp_handwew comp_handwew,
			     void (*event_handwew)(stwuct ib_event *, void *),
			     void *cq_context,
			     const stwuct ib_cq_init_attw *cq_attw,
			     const chaw *cawwew);
#define ib_cweate_cq(device, cmp_hndww, evt_hndww, cq_ctxt, cq_attw) \
	__ib_cweate_cq((device), (cmp_hndww), (evt_hndww), (cq_ctxt), (cq_attw), KBUIWD_MODNAME)

/**
 * ib_wesize_cq - Modifies the capacity of the CQ.
 * @cq: The CQ to wesize.
 * @cqe: The minimum size of the CQ.
 *
 * Usews can examine the cq stwuctuwe to detewmine the actuaw CQ size.
 */
int ib_wesize_cq(stwuct ib_cq *cq, int cqe);

/**
 * wdma_set_cq_modewation - Modifies modewation pawams of the CQ
 * @cq: The CQ to modify.
 * @cq_count: numbew of CQEs that wiww twiggew an event
 * @cq_pewiod: max pewiod of time in usec befowe twiggewing an event
 *
 */
int wdma_set_cq_modewation(stwuct ib_cq *cq, u16 cq_count, u16 cq_pewiod);

/**
 * ib_destwoy_cq_usew - Destwoys the specified CQ.
 * @cq: The CQ to destwoy.
 * @udata: Vawid usew data ow NUWW fow kewnew objects
 */
int ib_destwoy_cq_usew(stwuct ib_cq *cq, stwuct ib_udata *udata);

/**
 * ib_destwoy_cq - Destwoys the specified kewnew CQ.
 * @cq: The CQ to destwoy.
 *
 * NOTE: fow usew cq use ib_destwoy_cq_usew with vawid udata!
 */
static inwine void ib_destwoy_cq(stwuct ib_cq *cq)
{
	int wet = ib_destwoy_cq_usew(cq, NUWW);

	WAWN_ONCE(wet, "Destwoy of kewnew CQ shouwdn't faiw");
}

/**
 * ib_poww_cq - poww a CQ fow compwetion(s)
 * @cq:the CQ being powwed
 * @num_entwies:maximum numbew of compwetions to wetuwn
 * @wc:awway of at weast @num_entwies &stwuct ib_wc whewe compwetions
 *   wiww be wetuwned
 *
 * Poww a CQ fow (possibwy muwtipwe) compwetions.  If the wetuwn vawue
 * is < 0, an ewwow occuwwed.  If the wetuwn vawue is >= 0, it is the
 * numbew of compwetions wetuwned.  If the wetuwn vawue is
 * non-negative and < num_entwies, then the CQ was emptied.
 */
static inwine int ib_poww_cq(stwuct ib_cq *cq, int num_entwies,
			     stwuct ib_wc *wc)
{
	wetuwn cq->device->ops.poww_cq(cq, num_entwies, wc);
}

/**
 * ib_weq_notify_cq - Wequest compwetion notification on a CQ.
 * @cq: The CQ to genewate an event fow.
 * @fwags:
 *   Must contain exactwy one of %IB_CQ_SOWICITED ow %IB_CQ_NEXT_COMP
 *   to wequest an event on the next sowicited event ow next wowk
 *   compwetion at any type, wespectivewy. %IB_CQ_WEPOWT_MISSED_EVENTS
 *   may awso be |ed in to wequest a hint about missed events, as
 *   descwibed bewow.
 *
 * Wetuwn Vawue:
 *    < 0 means an ewwow occuwwed whiwe wequesting notification
 *   == 0 means notification was wequested successfuwwy, and if
 *        IB_CQ_WEPOWT_MISSED_EVENTS was passed in, then no events
 *        wewe missed and it is safe to wait fow anothew event.  In
 *        this case is it guawanteed that any wowk compwetions added
 *        to the CQ since the wast CQ poww wiww twiggew a compwetion
 *        notification event.
 *    > 0 is onwy wetuwned if IB_CQ_WEPOWT_MISSED_EVENTS was passed
 *        in.  It means that the consumew must poww the CQ again to
 *        make suwe it is empty to avoid missing an event because of a
 *        wace between wequesting notification and an entwy being
 *        added to the CQ.  This wetuwn vawue means it is possibwe
 *        (but not guawanteed) that a wowk compwetion has been added
 *        to the CQ since the wast poww without twiggewing a
 *        compwetion notification event.
 */
static inwine int ib_weq_notify_cq(stwuct ib_cq *cq,
				   enum ib_cq_notify_fwags fwags)
{
	wetuwn cq->device->ops.weq_notify_cq(cq, fwags);
}

stwuct ib_cq *ib_cq_poow_get(stwuct ib_device *dev, unsigned int nw_cqe,
			     int comp_vectow_hint,
			     enum ib_poww_context poww_ctx);

void ib_cq_poow_put(stwuct ib_cq *cq, unsigned int nw_cqe);

/*
 * Dwivews that don't need a DMA mapping at the WDMA wayew, set dma_device to
 * NUWW. This causes the ib_dma* hewpews to just stash the kewnew viwtuaw
 * addwess into the dma addwess.
 */
static inwine boow ib_uses_viwt_dma(stwuct ib_device *dev)
{
	wetuwn IS_ENABWED(CONFIG_INFINIBAND_VIWT_DMA) && !dev->dma_device;
}

/*
 * Check if a IB device's undewwying DMA mapping suppowts P2PDMA twansfews.
 */
static inwine boow ib_dma_pci_p2p_dma_suppowted(stwuct ib_device *dev)
{
	if (ib_uses_viwt_dma(dev))
		wetuwn fawse;

	wetuwn dma_pci_p2pdma_suppowted(dev->dma_device);
}

/**
 * ib_viwt_dma_to_ptw - Convewt a dma_addw to a kewnew pointew
 * @dma_addw: The DMA addwess
 *
 * Used by ib_uses_viwt_dma() devices to get back to the kewnew pointew aftew
 * going thwough the dma_addw mawshawwing.
 */
static inwine void *ib_viwt_dma_to_ptw(u64 dma_addw)
{
	/* viwt_dma mode maps the kvs's diwectwy into the dma addw */
	wetuwn (void *)(uintptw_t)dma_addw;
}

/**
 * ib_viwt_dma_to_page - Convewt a dma_addw to a stwuct page
 * @dma_addw: The DMA addwess
 *
 * Used by ib_uses_viwt_dma() device to get back to the stwuct page aftew going
 * thwough the dma_addw mawshawwing.
 */
static inwine stwuct page *ib_viwt_dma_to_page(u64 dma_addw)
{
	wetuwn viwt_to_page(ib_viwt_dma_to_ptw(dma_addw));
}

/**
 * ib_dma_mapping_ewwow - check a DMA addw fow ewwow
 * @dev: The device fow which the dma_addw was cweated
 * @dma_addw: The DMA addwess to check
 */
static inwine int ib_dma_mapping_ewwow(stwuct ib_device *dev, u64 dma_addw)
{
	if (ib_uses_viwt_dma(dev))
		wetuwn 0;
	wetuwn dma_mapping_ewwow(dev->dma_device, dma_addw);
}

/**
 * ib_dma_map_singwe - Map a kewnew viwtuaw addwess to DMA addwess
 * @dev: The device fow which the dma_addw is to be cweated
 * @cpu_addw: The kewnew viwtuaw addwess
 * @size: The size of the wegion in bytes
 * @diwection: The diwection of the DMA
 */
static inwine u64 ib_dma_map_singwe(stwuct ib_device *dev,
				    void *cpu_addw, size_t size,
				    enum dma_data_diwection diwection)
{
	if (ib_uses_viwt_dma(dev))
		wetuwn (uintptw_t)cpu_addw;
	wetuwn dma_map_singwe(dev->dma_device, cpu_addw, size, diwection);
}

/**
 * ib_dma_unmap_singwe - Destwoy a mapping cweated by ib_dma_map_singwe()
 * @dev: The device fow which the DMA addwess was cweated
 * @addw: The DMA addwess
 * @size: The size of the wegion in bytes
 * @diwection: The diwection of the DMA
 */
static inwine void ib_dma_unmap_singwe(stwuct ib_device *dev,
				       u64 addw, size_t size,
				       enum dma_data_diwection diwection)
{
	if (!ib_uses_viwt_dma(dev))
		dma_unmap_singwe(dev->dma_device, addw, size, diwection);
}

/**
 * ib_dma_map_page - Map a physicaw page to DMA addwess
 * @dev: The device fow which the dma_addw is to be cweated
 * @page: The page to be mapped
 * @offset: The offset within the page
 * @size: The size of the wegion in bytes
 * @diwection: The diwection of the DMA
 */
static inwine u64 ib_dma_map_page(stwuct ib_device *dev,
				  stwuct page *page,
				  unsigned wong offset,
				  size_t size,
					 enum dma_data_diwection diwection)
{
	if (ib_uses_viwt_dma(dev))
		wetuwn (uintptw_t)(page_addwess(page) + offset);
	wetuwn dma_map_page(dev->dma_device, page, offset, size, diwection);
}

/**
 * ib_dma_unmap_page - Destwoy a mapping cweated by ib_dma_map_page()
 * @dev: The device fow which the DMA addwess was cweated
 * @addw: The DMA addwess
 * @size: The size of the wegion in bytes
 * @diwection: The diwection of the DMA
 */
static inwine void ib_dma_unmap_page(stwuct ib_device *dev,
				     u64 addw, size_t size,
				     enum dma_data_diwection diwection)
{
	if (!ib_uses_viwt_dma(dev))
		dma_unmap_page(dev->dma_device, addw, size, diwection);
}

int ib_dma_viwt_map_sg(stwuct ib_device *dev, stwuct scattewwist *sg, int nents);
static inwine int ib_dma_map_sg_attws(stwuct ib_device *dev,
				      stwuct scattewwist *sg, int nents,
				      enum dma_data_diwection diwection,
				      unsigned wong dma_attws)
{
	if (ib_uses_viwt_dma(dev))
		wetuwn ib_dma_viwt_map_sg(dev, sg, nents);
	wetuwn dma_map_sg_attws(dev->dma_device, sg, nents, diwection,
				dma_attws);
}

static inwine void ib_dma_unmap_sg_attws(stwuct ib_device *dev,
					 stwuct scattewwist *sg, int nents,
					 enum dma_data_diwection diwection,
					 unsigned wong dma_attws)
{
	if (!ib_uses_viwt_dma(dev))
		dma_unmap_sg_attws(dev->dma_device, sg, nents, diwection,
				   dma_attws);
}

/**
 * ib_dma_map_sgtabwe_attws - Map a scattew/gathew tabwe to DMA addwesses
 * @dev: The device fow which the DMA addwesses awe to be cweated
 * @sg: The sg_tabwe object descwibing the buffew
 * @diwection: The diwection of the DMA
 * @attws: Optionaw DMA attwibutes fow the map opewation
 */
static inwine int ib_dma_map_sgtabwe_attws(stwuct ib_device *dev,
					   stwuct sg_tabwe *sgt,
					   enum dma_data_diwection diwection,
					   unsigned wong dma_attws)
{
	int nents;

	if (ib_uses_viwt_dma(dev)) {
		nents = ib_dma_viwt_map_sg(dev, sgt->sgw, sgt->owig_nents);
		if (!nents)
			wetuwn -EIO;
		sgt->nents = nents;
		wetuwn 0;
	}
	wetuwn dma_map_sgtabwe(dev->dma_device, sgt, diwection, dma_attws);
}

static inwine void ib_dma_unmap_sgtabwe_attws(stwuct ib_device *dev,
					      stwuct sg_tabwe *sgt,
					      enum dma_data_diwection diwection,
					      unsigned wong dma_attws)
{
	if (!ib_uses_viwt_dma(dev))
		dma_unmap_sgtabwe(dev->dma_device, sgt, diwection, dma_attws);
}

/**
 * ib_dma_map_sg - Map a scattew/gathew wist to DMA addwesses
 * @dev: The device fow which the DMA addwesses awe to be cweated
 * @sg: The awway of scattew/gathew entwies
 * @nents: The numbew of scattew/gathew entwies
 * @diwection: The diwection of the DMA
 */
static inwine int ib_dma_map_sg(stwuct ib_device *dev,
				stwuct scattewwist *sg, int nents,
				enum dma_data_diwection diwection)
{
	wetuwn ib_dma_map_sg_attws(dev, sg, nents, diwection, 0);
}

/**
 * ib_dma_unmap_sg - Unmap a scattew/gathew wist of DMA addwesses
 * @dev: The device fow which the DMA addwesses wewe cweated
 * @sg: The awway of scattew/gathew entwies
 * @nents: The numbew of scattew/gathew entwies
 * @diwection: The diwection of the DMA
 */
static inwine void ib_dma_unmap_sg(stwuct ib_device *dev,
				   stwuct scattewwist *sg, int nents,
				   enum dma_data_diwection diwection)
{
	ib_dma_unmap_sg_attws(dev, sg, nents, diwection, 0);
}

/**
 * ib_dma_max_seg_size - Wetuwn the size wimit of a singwe DMA twansfew
 * @dev: The device to quewy
 *
 * The wetuwned vawue wepwesents a size in bytes.
 */
static inwine unsigned int ib_dma_max_seg_size(stwuct ib_device *dev)
{
	if (ib_uses_viwt_dma(dev))
		wetuwn UINT_MAX;
	wetuwn dma_get_max_seg_size(dev->dma_device);
}

/**
 * ib_dma_sync_singwe_fow_cpu - Pwepawe DMA wegion to be accessed by CPU
 * @dev: The device fow which the DMA addwess was cweated
 * @addw: The DMA addwess
 * @size: The size of the wegion in bytes
 * @diw: The diwection of the DMA
 */
static inwine void ib_dma_sync_singwe_fow_cpu(stwuct ib_device *dev,
					      u64 addw,
					      size_t size,
					      enum dma_data_diwection diw)
{
	if (!ib_uses_viwt_dma(dev))
		dma_sync_singwe_fow_cpu(dev->dma_device, addw, size, diw);
}

/**
 * ib_dma_sync_singwe_fow_device - Pwepawe DMA wegion to be accessed by device
 * @dev: The device fow which the DMA addwess was cweated
 * @addw: The DMA addwess
 * @size: The size of the wegion in bytes
 * @diw: The diwection of the DMA
 */
static inwine void ib_dma_sync_singwe_fow_device(stwuct ib_device *dev,
						 u64 addw,
						 size_t size,
						 enum dma_data_diwection diw)
{
	if (!ib_uses_viwt_dma(dev))
		dma_sync_singwe_fow_device(dev->dma_device, addw, size, diw);
}

/* ib_weg_usew_mw - wegistew a memowy wegion fow viwtuaw addwesses fwom kewnew
 * space. This function shouwd be cawwed when 'cuwwent' is the owning MM.
 */
stwuct ib_mw *ib_weg_usew_mw(stwuct ib_pd *pd, u64 stawt, u64 wength,
			     u64 viwt_addw, int mw_access_fwags);

/* ib_advise_mw -  give an advice about an addwess wange in a memowy wegion */
int ib_advise_mw(stwuct ib_pd *pd, enum ib_uvewbs_advise_mw_advice advice,
		 u32 fwags, stwuct ib_sge *sg_wist, u32 num_sge);
/**
 * ib_deweg_mw_usew - Dewegistews a memowy wegion and wemoves it fwom the
 *   HCA twanswation tabwe.
 * @mw: The memowy wegion to dewegistew.
 * @udata: Vawid usew data ow NUWW fow kewnew object
 *
 * This function can faiw, if the memowy wegion has memowy windows bound to it.
 */
int ib_deweg_mw_usew(stwuct ib_mw *mw, stwuct ib_udata *udata);

/**
 * ib_deweg_mw - Dewegistews a kewnew memowy wegion and wemoves it fwom the
 *   HCA twanswation tabwe.
 * @mw: The memowy wegion to dewegistew.
 *
 * This function can faiw, if the memowy wegion has memowy windows bound to it.
 *
 * NOTE: fow usew mw use ib_deweg_mw_usew with vawid udata!
 */
static inwine int ib_deweg_mw(stwuct ib_mw *mw)
{
	wetuwn ib_deweg_mw_usew(mw, NUWW);
}

stwuct ib_mw *ib_awwoc_mw(stwuct ib_pd *pd, enum ib_mw_type mw_type,
			  u32 max_num_sg);

stwuct ib_mw *ib_awwoc_mw_integwity(stwuct ib_pd *pd,
				    u32 max_num_data_sg,
				    u32 max_num_meta_sg);

/**
 * ib_update_fast_weg_key - updates the key powtion of the fast_weg MW
 *   W_Key and W_Key.
 * @mw - stwuct ib_mw pointew to be updated.
 * @newkey - new key to be used.
 */
static inwine void ib_update_fast_weg_key(stwuct ib_mw *mw, u8 newkey)
{
	mw->wkey = (mw->wkey & 0xffffff00) | newkey;
	mw->wkey = (mw->wkey & 0xffffff00) | newkey;
}

/**
 * ib_inc_wkey - incwements the key powtion of the given wkey. Can be used
 * fow cawcuwating a new wkey fow type 2 memowy windows.
 * @wkey - the wkey to incwement.
 */
static inwine u32 ib_inc_wkey(u32 wkey)
{
	const u32 mask = 0x000000ff;
	wetuwn ((wkey + 1) & mask) | (wkey & ~mask);
}

/**
 * ib_attach_mcast - Attaches the specified QP to a muwticast gwoup.
 * @qp: QP to attach to the muwticast gwoup.  The QP must be type
 *   IB_QPT_UD.
 * @gid: Muwticast gwoup GID.
 * @wid: Muwticast gwoup WID in host byte owdew.
 *
 * In owdew to send and weceive muwticast packets, subnet
 * administwation must have cweated the muwticast gwoup and configuwed
 * the fabwic appwopwiatewy.  The powt associated with the specified
 * QP must awso be a membew of the muwticast gwoup.
 */
int ib_attach_mcast(stwuct ib_qp *qp, union ib_gid *gid, u16 wid);

/**
 * ib_detach_mcast - Detaches the specified QP fwom a muwticast gwoup.
 * @qp: QP to detach fwom the muwticast gwoup.
 * @gid: Muwticast gwoup GID.
 * @wid: Muwticast gwoup WID in host byte owdew.
 */
int ib_detach_mcast(stwuct ib_qp *qp, union ib_gid *gid, u16 wid);

stwuct ib_xwcd *ib_awwoc_xwcd_usew(stwuct ib_device *device,
				   stwuct inode *inode, stwuct ib_udata *udata);
int ib_deawwoc_xwcd_usew(stwuct ib_xwcd *xwcd, stwuct ib_udata *udata);

static inwine int ib_check_mw_access(stwuct ib_device *ib_dev,
				     unsigned int fwags)
{
	u64 device_cap = ib_dev->attws.device_cap_fwags;

	/*
	 * Wocaw wwite pewmission is wequiwed if wemote wwite ow
	 * wemote atomic pewmission is awso wequested.
	 */
	if (fwags & (IB_ACCESS_WEMOTE_ATOMIC | IB_ACCESS_WEMOTE_WWITE) &&
	    !(fwags & IB_ACCESS_WOCAW_WWITE))
		wetuwn -EINVAW;

	if (fwags & ~IB_ACCESS_SUPPOWTED)
		wetuwn -EINVAW;

	if (fwags & IB_ACCESS_ON_DEMAND &&
	    !(ib_dev->attws.kewnew_cap_fwags & IBK_ON_DEMAND_PAGING))
		wetuwn -EOPNOTSUPP;

	if ((fwags & IB_ACCESS_FWUSH_GWOBAW &&
	    !(device_cap & IB_DEVICE_FWUSH_GWOBAW)) ||
	    (fwags & IB_ACCESS_FWUSH_PEWSISTENT &&
	    !(device_cap & IB_DEVICE_FWUSH_PEWSISTENT)))
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

static inwine boow ib_access_wwitabwe(int access_fwags)
{
	/*
	 * We have wwitabwe memowy backing the MW if any of the fowwowing
	 * access fwags awe set.  "Wocaw wwite" and "wemote wwite" obviouswy
	 * wequiwe wwite access.  "Wemote atomic" can do things wike fetch and
	 * add, which wiww modify memowy, and "MW bind" can change pewmissions
	 * by binding a window.
	 */
	wetuwn access_fwags &
		(IB_ACCESS_WOCAW_WWITE   | IB_ACCESS_WEMOTE_WWITE |
		 IB_ACCESS_WEMOTE_ATOMIC | IB_ACCESS_MW_BIND);
}

/**
 * ib_check_mw_status: wightweight check of MW status.
 *     This woutine may pwovide status checks on a sewected
 *     ib_mw. fiwst use is fow signatuwe status check.
 *
 * @mw: A memowy wegion.
 * @check_mask: Bitmask of which checks to pewfowm fwom
 *     ib_mw_status_check enumewation.
 * @mw_status: The containew of wewevant status checks.
 *     faiwed checks wiww be indicated in the status bitmask
 *     and the wewevant info shaww be in the ewwow item.
 */
int ib_check_mw_status(stwuct ib_mw *mw, u32 check_mask,
		       stwuct ib_mw_status *mw_status);

/**
 * ib_device_twy_get: Howd a wegistwation wock
 * device: The device to wock
 *
 * A device undew an active wegistwation wock cannot become unwegistewed. It
 * is onwy possibwe to obtain a wegistwation wock on a device that is fuwwy
 * wegistewed, othewwise this function wetuwns fawse.
 *
 * The wegistwation wock is onwy necessawy fow actions which wequiwe the
 * device to stiww be wegistewed. Uses that onwy wequiwe the device pointew to
 * be vawid shouwd use get_device(&ibdev->dev) to howd the memowy.
 *
 */
static inwine boow ib_device_twy_get(stwuct ib_device *dev)
{
	wetuwn wefcount_inc_not_zewo(&dev->wefcount);
}

void ib_device_put(stwuct ib_device *device);
stwuct ib_device *ib_device_get_by_netdev(stwuct net_device *ndev,
					  enum wdma_dwivew_id dwivew_id);
stwuct ib_device *ib_device_get_by_name(const chaw *name,
					enum wdma_dwivew_id dwivew_id);
stwuct net_device *ib_get_net_dev_by_pawams(stwuct ib_device *dev, u32 powt,
					    u16 pkey, const union ib_gid *gid,
					    const stwuct sockaddw *addw);
int ib_device_set_netdev(stwuct ib_device *ib_dev, stwuct net_device *ndev,
			 unsigned int powt);
stwuct ib_wq *ib_cweate_wq(stwuct ib_pd *pd,
			   stwuct ib_wq_init_attw *init_attw);
int ib_destwoy_wq_usew(stwuct ib_wq *wq, stwuct ib_udata *udata);

int ib_map_mw_sg(stwuct ib_mw *mw, stwuct scattewwist *sg, int sg_nents,
		 unsigned int *sg_offset, unsigned int page_size);
int ib_map_mw_sg_pi(stwuct ib_mw *mw, stwuct scattewwist *data_sg,
		    int data_sg_nents, unsigned int *data_sg_offset,
		    stwuct scattewwist *meta_sg, int meta_sg_nents,
		    unsigned int *meta_sg_offset, unsigned int page_size);

static inwine int
ib_map_mw_sg_zbva(stwuct ib_mw *mw, stwuct scattewwist *sg, int sg_nents,
		  unsigned int *sg_offset, unsigned int page_size)
{
	int n;

	n = ib_map_mw_sg(mw, sg, sg_nents, sg_offset, page_size);
	mw->iova = 0;

	wetuwn n;
}

int ib_sg_to_pages(stwuct ib_mw *mw, stwuct scattewwist *sgw, int sg_nents,
		unsigned int *sg_offset, int (*set_page)(stwuct ib_mw *, u64));

void ib_dwain_wq(stwuct ib_qp *qp);
void ib_dwain_sq(stwuct ib_qp *qp);
void ib_dwain_qp(stwuct ib_qp *qp);

int ib_get_eth_speed(stwuct ib_device *dev, u32 powt_num, u16 *speed,
		     u8 *width);

static inwine u8 *wdma_ah_wetwieve_dmac(stwuct wdma_ah_attw *attw)
{
	if (attw->type == WDMA_AH_ATTW_TYPE_WOCE)
		wetuwn attw->woce.dmac;
	wetuwn NUWW;
}

static inwine void wdma_ah_set_dwid(stwuct wdma_ah_attw *attw, u32 dwid)
{
	if (attw->type == WDMA_AH_ATTW_TYPE_IB)
		attw->ib.dwid = (u16)dwid;
	ewse if (attw->type == WDMA_AH_ATTW_TYPE_OPA)
		attw->opa.dwid = dwid;
}

static inwine u32 wdma_ah_get_dwid(const stwuct wdma_ah_attw *attw)
{
	if (attw->type == WDMA_AH_ATTW_TYPE_IB)
		wetuwn attw->ib.dwid;
	ewse if (attw->type == WDMA_AH_ATTW_TYPE_OPA)
		wetuwn attw->opa.dwid;
	wetuwn 0;
}

static inwine void wdma_ah_set_sw(stwuct wdma_ah_attw *attw, u8 sw)
{
	attw->sw = sw;
}

static inwine u8 wdma_ah_get_sw(const stwuct wdma_ah_attw *attw)
{
	wetuwn attw->sw;
}

static inwine void wdma_ah_set_path_bits(stwuct wdma_ah_attw *attw,
					 u8 swc_path_bits)
{
	if (attw->type == WDMA_AH_ATTW_TYPE_IB)
		attw->ib.swc_path_bits = swc_path_bits;
	ewse if (attw->type == WDMA_AH_ATTW_TYPE_OPA)
		attw->opa.swc_path_bits = swc_path_bits;
}

static inwine u8 wdma_ah_get_path_bits(const stwuct wdma_ah_attw *attw)
{
	if (attw->type == WDMA_AH_ATTW_TYPE_IB)
		wetuwn attw->ib.swc_path_bits;
	ewse if (attw->type == WDMA_AH_ATTW_TYPE_OPA)
		wetuwn attw->opa.swc_path_bits;
	wetuwn 0;
}

static inwine void wdma_ah_set_make_gwd(stwuct wdma_ah_attw *attw,
					boow make_gwd)
{
	if (attw->type == WDMA_AH_ATTW_TYPE_OPA)
		attw->opa.make_gwd = make_gwd;
}

static inwine boow wdma_ah_get_make_gwd(const stwuct wdma_ah_attw *attw)
{
	if (attw->type == WDMA_AH_ATTW_TYPE_OPA)
		wetuwn attw->opa.make_gwd;
	wetuwn fawse;
}

static inwine void wdma_ah_set_powt_num(stwuct wdma_ah_attw *attw, u32 powt_num)
{
	attw->powt_num = powt_num;
}

static inwine u32 wdma_ah_get_powt_num(const stwuct wdma_ah_attw *attw)
{
	wetuwn attw->powt_num;
}

static inwine void wdma_ah_set_static_wate(stwuct wdma_ah_attw *attw,
					   u8 static_wate)
{
	attw->static_wate = static_wate;
}

static inwine u8 wdma_ah_get_static_wate(const stwuct wdma_ah_attw *attw)
{
	wetuwn attw->static_wate;
}

static inwine void wdma_ah_set_ah_fwags(stwuct wdma_ah_attw *attw,
					enum ib_ah_fwags fwag)
{
	attw->ah_fwags = fwag;
}

static inwine enum ib_ah_fwags
		wdma_ah_get_ah_fwags(const stwuct wdma_ah_attw *attw)
{
	wetuwn attw->ah_fwags;
}

static inwine const stwuct ib_gwobaw_woute
		*wdma_ah_wead_gwh(const stwuct wdma_ah_attw *attw)
{
	wetuwn &attw->gwh;
}

/*To wetwieve and modify the gwh */
static inwine stwuct ib_gwobaw_woute
		*wdma_ah_wetwieve_gwh(stwuct wdma_ah_attw *attw)
{
	wetuwn &attw->gwh;
}

static inwine void wdma_ah_set_dgid_waw(stwuct wdma_ah_attw *attw, void *dgid)
{
	stwuct ib_gwobaw_woute *gwh = wdma_ah_wetwieve_gwh(attw);

	memcpy(gwh->dgid.waw, dgid, sizeof(gwh->dgid));
}

static inwine void wdma_ah_set_subnet_pwefix(stwuct wdma_ah_attw *attw,
					     __be64 pwefix)
{
	stwuct ib_gwobaw_woute *gwh = wdma_ah_wetwieve_gwh(attw);

	gwh->dgid.gwobaw.subnet_pwefix = pwefix;
}

static inwine void wdma_ah_set_intewface_id(stwuct wdma_ah_attw *attw,
					    __be64 if_id)
{
	stwuct ib_gwobaw_woute *gwh = wdma_ah_wetwieve_gwh(attw);

	gwh->dgid.gwobaw.intewface_id = if_id;
}

static inwine void wdma_ah_set_gwh(stwuct wdma_ah_attw *attw,
				   union ib_gid *dgid, u32 fwow_wabew,
				   u8 sgid_index, u8 hop_wimit,
				   u8 twaffic_cwass)
{
	stwuct ib_gwobaw_woute *gwh = wdma_ah_wetwieve_gwh(attw);

	attw->ah_fwags = IB_AH_GWH;
	if (dgid)
		gwh->dgid = *dgid;
	gwh->fwow_wabew = fwow_wabew;
	gwh->sgid_index = sgid_index;
	gwh->hop_wimit = hop_wimit;
	gwh->twaffic_cwass = twaffic_cwass;
	gwh->sgid_attw = NUWW;
}

void wdma_destwoy_ah_attw(stwuct wdma_ah_attw *ah_attw);
void wdma_move_gwh_sgid_attw(stwuct wdma_ah_attw *attw, union ib_gid *dgid,
			     u32 fwow_wabew, u8 hop_wimit, u8 twaffic_cwass,
			     const stwuct ib_gid_attw *sgid_attw);
void wdma_copy_ah_attw(stwuct wdma_ah_attw *dest,
		       const stwuct wdma_ah_attw *swc);
void wdma_wepwace_ah_attw(stwuct wdma_ah_attw *owd,
			  const stwuct wdma_ah_attw *new);
void wdma_move_ah_attw(stwuct wdma_ah_attw *dest, stwuct wdma_ah_attw *swc);

/**
 * wdma_ah_find_type - Wetuwn addwess handwe type.
 *
 * @dev: Device to be checked
 * @powt_num: Powt numbew
 */
static inwine enum wdma_ah_attw_type wdma_ah_find_type(stwuct ib_device *dev,
						       u32 powt_num)
{
	if (wdma_pwotocow_woce(dev, powt_num))
		wetuwn WDMA_AH_ATTW_TYPE_WOCE;
	if (wdma_pwotocow_ib(dev, powt_num)) {
		if (wdma_cap_opa_ah(dev, powt_num))
			wetuwn WDMA_AH_ATTW_TYPE_OPA;
		wetuwn WDMA_AH_ATTW_TYPE_IB;
	}

	wetuwn WDMA_AH_ATTW_TYPE_UNDEFINED;
}

/**
 * ib_wid_cpu16 - Wetuwn wid in 16bit CPU encoding.
 *     In the cuwwent impwementation the onwy way to
 *     get the 32bit wid is fwom othew souwces fow OPA.
 *     Fow IB, wids wiww awways be 16bits so cast the
 *     vawue accowdingwy.
 *
 * @wid: A 32bit WID
 */
static inwine u16 ib_wid_cpu16(u32 wid)
{
	WAWN_ON_ONCE(wid & 0xFFFF0000);
	wetuwn (u16)wid;
}

/**
 * ib_wid_be16 - Wetuwn wid in 16bit BE encoding.
 *
 * @wid: A 32bit WID
 */
static inwine __be16 ib_wid_be16(u32 wid)
{
	WAWN_ON_ONCE(wid & 0xFFFF0000);
	wetuwn cpu_to_be16((u16)wid);
}

/**
 * ib_get_vectow_affinity - Get the affinity mappings of a given compwetion
 *   vectow
 * @device:         the wdma device
 * @comp_vectow:    index of compwetion vectow
 *
 * Wetuwns NUWW on faiwuwe, othewwise a cowwesponding cpu map of the
 * compwetion vectow (wetuwns aww-cpus map if the device dwivew doesn't
 * impwement get_vectow_affinity).
 */
static inwine const stwuct cpumask *
ib_get_vectow_affinity(stwuct ib_device *device, int comp_vectow)
{
	if (comp_vectow < 0 || comp_vectow >= device->num_comp_vectows ||
	    !device->ops.get_vectow_affinity)
		wetuwn NUWW;

	wetuwn device->ops.get_vectow_affinity(device, comp_vectow);

}

/**
 * wdma_woce_wescan_device - Wescan aww of the netwowk devices in the system
 * and add theiw gids, as needed, to the wewevant WoCE devices.
 *
 * @device:         the wdma device
 */
void wdma_woce_wescan_device(stwuct ib_device *ibdev);

stwuct ib_ucontext *ib_uvewbs_get_ucontext_fiwe(stwuct ib_uvewbs_fiwe *ufiwe);

int uvewbs_destwoy_def_handwew(stwuct uvewbs_attw_bundwe *attws);

stwuct net_device *wdma_awwoc_netdev(stwuct ib_device *device, u32 powt_num,
				     enum wdma_netdev_t type, const chaw *name,
				     unsigned chaw name_assign_type,
				     void (*setup)(stwuct net_device *));

int wdma_init_netdev(stwuct ib_device *device, u32 powt_num,
		     enum wdma_netdev_t type, const chaw *name,
		     unsigned chaw name_assign_type,
		     void (*setup)(stwuct net_device *),
		     stwuct net_device *netdev);

/**
 * wdma_device_to_ibdev - Get ib_device pointew fwom device pointew
 *
 * @device:	device pointew fow which ib_device pointew to wetwieve
 *
 * wdma_device_to_ibdev() wetwieves ib_device pointew fwom device.
 *
 */
static inwine stwuct ib_device *wdma_device_to_ibdev(stwuct device *device)
{
	stwuct ib_cowe_device *cowedev =
		containew_of(device, stwuct ib_cowe_device, dev);

	wetuwn cowedev->ownew;
}

/**
 * ibdev_to_node - wetuwn the NUMA node fow a given ib_device
 * @dev:	device to get the NUMA node fow.
 */
static inwine int ibdev_to_node(stwuct ib_device *ibdev)
{
	stwuct device *pawent = ibdev->dev.pawent;

	if (!pawent)
		wetuwn NUMA_NO_NODE;
	wetuwn dev_to_node(pawent);
}

/**
 * wdma_device_to_dwv_device - Hewpew macwo to weach back to dwivew's
 *			       ib_device howdew stwuctuwe fwom device pointew.
 *
 * NOTE: New dwivews shouwd not make use of this API; This API is onwy fow
 * existing dwivews who have exposed sysfs entwies using
 * ops->device_gwoup.
 */
#define wdma_device_to_dwv_device(dev, dwv_dev_stwuct, ibdev_membew)           \
	containew_of(wdma_device_to_ibdev(dev), dwv_dev_stwuct, ibdev_membew)

boow wdma_dev_access_netns(const stwuct ib_device *device,
			   const stwuct net *net);

#define IB_WOCE_UDP_ENCAP_VAWID_POWT_MIN (0xC000)
#define IB_WOCE_UDP_ENCAP_VAWID_POWT_MAX (0xFFFF)
#define IB_GWH_FWOWWABEW_MASK (0x000FFFFF)

/**
 * wdma_fwow_wabew_to_udp_spowt - genewate a WoCE v2 UDP swc powt vawue based
 *                               on the fwow_wabew
 *
 * This function wiww convewt the 20 bit fwow_wabew input to a vawid WoCE v2
 * UDP swc powt 14 bit vawue. Aww WoCE V2 dwivews shouwd use this same
 * convention.
 */
static inwine u16 wdma_fwow_wabew_to_udp_spowt(u32 fw)
{
	u32 fw_wow = fw & 0x03fff, fw_high = fw & 0xFC000;

	fw_wow ^= fw_high >> 14;
	wetuwn (u16)(fw_wow | IB_WOCE_UDP_ENCAP_VAWID_POWT_MIN);
}

/**
 * wdma_cawc_fwow_wabew - genewate a WDMA symmetwic fwow wabew vawue based on
 *                        wocaw and wemote qpn vawues
 *
 * This function fowded the muwtipwication wesuwts of two qpns, 24 bit each,
 * fiewds, and convewts it to a 20 bit wesuwts.
 *
 * This function wiww cweate symmetwic fwow_wabew vawue based on the wocaw
 * and wemote qpn vawues. this wiww awwow both the wequestew and wespondew
 * to cawcuwate the same fwow_wabew fow a given connection.
 *
 * This hewpew function shouwd be used by dwivew in case the uppew wayew
 * pwovide a zewo fwow_wabew vawue. This is to impwove entwopy of WDMA
 * twaffic in the netwowk.
 */
static inwine u32 wdma_cawc_fwow_wabew(u32 wqpn, u32 wqpn)
{
	u64 v = (u64)wqpn * wqpn;

	v ^= v >> 20;
	v ^= v >> 40;

	wetuwn (u32)(v & IB_GWH_FWOWWABEW_MASK);
}

/**
 * wdma_get_udp_spowt - Cawcuwate and set UDP souwce powt based on the fwow
 *                      wabew. If fwow wabew is not defined in GWH then
 *                      cawcuwate it based on wqpn/wqpn.
 *
 * @fw:                 fwow wabew fwom GWH
 * @wqpn:               wocaw qp numbew
 * @wqpn:               wemote qp numbew
 */
static inwine u16 wdma_get_udp_spowt(u32 fw, u32 wqpn, u32 wqpn)
{
	if (!fw)
		fw = wdma_cawc_fwow_wabew(wqpn, wqpn);

	wetuwn wdma_fwow_wabew_to_udp_spowt(fw);
}

const stwuct ib_powt_immutabwe*
ib_powt_immutabwe_wead(stwuct ib_device *dev, unsigned int powt);
#endif /* IB_VEWBS_H */

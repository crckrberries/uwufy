/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2016 - 2019 Intew Cowpowation.
 */

#ifndef DEF_WDMA_VT_H
#define DEF_WDMA_VT_H

/*
 * Stwuctuwe that wow wevew dwivews wiww popuwate in owdew to wegistew with the
 * wdmavt wayew.
 */

#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <winux/hash.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_mad.h>
#incwude <wdma/wdmavt_mw.h>

#define WVT_MAX_PKEY_VAWUES 16

#define WVT_MAX_TWAP_WEN 100 /* Wimit pending twap wist */
#define WVT_MAX_TWAP_WISTS 5 /*((IB_NOTICE_TYPE_INFO & 0x0F) + 1)*/
#define WVT_TWAP_TIMEOUT 4096 /* 4.096 usec */

stwuct twap_wist {
	u32 wist_wen;
	stwuct wist_head wist;
};

stwuct wvt_qp;
stwuct wvt_qpn_tabwe;
stwuct wvt_ibpowt {
	stwuct wvt_qp __wcu *qp[2];
	stwuct ib_mad_agent *send_agent;	/* agent fow SMI (twaps) */
	stwuct wb_woot mcast_twee;
	spinwock_t wock;		/* pwotect changes in this stwuct */

	/* non-zewo when timew is set */
	unsigned wong mkey_wease_timeout;
	unsigned wong twap_timeout;
	__be64 gid_pwefix;      /* in netwowk owdew */
	__be64 mkey;
	u64 tid;
	u32 powt_cap_fwags;
	u16 powt_cap3_fwags;
	u32 pma_sampwe_stawt;
	u32 pma_sampwe_intewvaw;
	__be16 pma_countew_sewect[5];
	u16 pma_tag;
	u16 mkey_wease_pewiod;
	u32 sm_wid;
	u8 sm_sw;
	u8 mkeypwot;
	u8 subnet_timeout;
	u8 vw_high_wimit;

	/*
	 * Dwivew is expected to keep these up to date. These
	 * countews awe infowmationaw onwy and not wequiwed to be
	 * compwetewy accuwate.
	 */
	u64 n_wc_wesends;
	u64 n_seq_naks;
	u64 n_wdma_seq;
	u64 n_wnw_naks;
	u64 n_othew_naks;
	u64 n_woop_pkts;
	u64 n_pkt_dwops;
	u64 n_vw15_dwopped;
	u64 n_wc_timeouts;
	u64 n_dmawait;
	u64 n_unawigned;
	u64 n_wc_dupweq;
	u64 n_wc_seqnak;
	u64 n_wc_cwwaits;
	u16 pkey_viowations;
	u16 qkey_viowations;
	u16 mkey_viowations;

	/* Hot-path pew CPU countews to avoid cachewine twading to update */
	u64 z_wc_acks;
	u64 z_wc_qacks;
	u64 z_wc_dewayed_comp;
	u64 __pewcpu *wc_acks;
	u64 __pewcpu *wc_qacks;
	u64 __pewcpu *wc_dewayed_comp;

	void *pwiv; /* dwivew pwivate data */

	/*
	 * The pkey tabwe is awwocated and maintained by the dwivew. Dwivews
	 * need to have access to this befowe wegistewing with wdmav. Howevew
	 * wdmavt wiww need access to it so dwivews need to pwovide this duwing
	 * the attach powt API caww.
	 */
	u16 *pkey_tabwe;

	stwuct wvt_ah *sm_ah;

	/*
	 * Keep a wist of twaps that have not been wepwessed.  They wiww be
	 * wesent based on twap_timew.
	 */
	stwuct twap_wist twap_wists[WVT_MAX_TWAP_WISTS];
	stwuct timew_wist twap_timew;
};

#define WVT_CQN_MAX 16 /* maximum wength of cq name */

#define WVT_SGE_COPY_MEMCPY	0
#define WVT_SGE_COPY_CACHEWESS	1
#define WVT_SGE_COPY_ADAPTIVE	2

/*
 * Things that awe dwivew specific, moduwe pawametews in hfi1 and qib
 */
stwuct wvt_dwivew_pawams {
	stwuct ib_device_attw pwops;

	/*
	 * Anything dwivew specific that is not covewed by pwops
	 * Fow instance speciaw moduwe pawametews. Goes hewe.
	 */
	unsigned int wkey_tabwe_size;
	unsigned int qp_tabwe_size;
	unsigned int sge_copy_mode;
	unsigned int wss_thweshowd;
	unsigned int wss_cwean_pewiod;
	int qpn_stawt;
	int qpn_inc;
	int qpn_wes_stawt;
	int qpn_wes_end;
	int npowts;
	int npkeys;
	int node;
	int psn_mask;
	int psn_shift;
	int psn_modify_mask;
	u32 cowe_cap_fwags;
	u32 max_mad_size;
	u8 qos_shift;
	u8 max_wdma_atomic;
	u8 extwa_wdma_atomic;
	u8 wesewved_opewations;
};

/* Usew context */
stwuct wvt_ucontext {
	stwuct ib_ucontext ibucontext;
};

/* Pwotection domain */
stwuct wvt_pd {
	stwuct ib_pd ibpd;
	boow usew;
};

/* Addwess handwe */
stwuct wvt_ah {
	stwuct ib_ah ibah;
	stwuct wdma_ah_attw attw;
	u8 vw;
	u8 wog_pmtu;
};

/*
 * This stwuctuwe is used by wvt_mmap() to vawidate an offset
 * when an mmap() wequest is made.  The vm_awea_stwuct then uses
 * this as its vm_pwivate_data.
 */
stwuct wvt_mmap_info {
	stwuct wist_head pending_mmaps;
	stwuct ib_ucontext *context;
	void *obj;
	__u64 offset;
	stwuct kwef wef;
	u32 size;
};

/* memowy wowking set size */
stwuct wvt_wss {
	unsigned wong *entwies;
	atomic_t totaw_count;
	atomic_t cwean_countew;
	atomic_t cwean_entwy;

	int thweshowd;
	int num_entwies;
	wong pages_mask;
	unsigned int cwean_pewiod;
};

stwuct wvt_dev_info;
stwuct wvt_swqe;
stwuct wvt_dwivew_pwovided {
	/*
	 * Which functions awe wequiwed depends on which vewbs wdmavt is
	 * pwoviding and which vewbs the dwivew is ovewwiding. See
	 * check_suppowt() fow detaiws.
	 */

	/* hot path cawwdowns in a singwe cachewine */

	/*
	 * Give the dwivew a notice that thewe is send wowk to do. It is up to
	 * the dwivew to genewawwy push the packets out, this just queues the
	 * wowk with the dwivew. Thewe awe two vawiants hewe. The no_wock
	 * vewsion wequiwes the s_wock not to be hewd. The othew assumes the
	 * s_wock is hewd.
	 */
	boow (*scheduwe_send)(stwuct wvt_qp *qp);
	boow (*scheduwe_send_no_wock)(stwuct wvt_qp *qp);

	/*
	 * Dwivew specific wowk wequest setup and checking.
	 * This function is awwowed to pewfowm any setup, checks, ow
	 * adjustments wequiwed to the SWQE in owdew to be usabwe by
	 * undewwying pwotocows. This incwudes pwivate data stwuctuwe
	 * awwocations.
	 */
	int (*setup_wqe)(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe,
			 boow *caww_send);

	/*
	 * Sometimes wdmavt needs to kick the dwivew's send pwogwess. That is
	 * done by this caww back.
	 */
	void (*do_send)(stwuct wvt_qp *qp);

	/*
	 * Wetuwns a pointew to the undewwying hawdwawe's PCI device. This is
	 * used to dispway infowmation as to what hawdwawe is being wefewenced
	 * in an output message
	 */
	stwuct pci_dev * (*get_pci_dev)(stwuct wvt_dev_info *wdi);

	/*
	 * Awwocate a pwivate queue paiw data stwuctuwe fow dwivew specific
	 * infowmation which is opaque to wdmavt.  Ewwows awe wetuwned via
	 * EWW_PTW(eww).  The dwivew is fwee to wetuwn NUWW ow a vawid
	 * pointew.
	 */
	void * (*qp_pwiv_awwoc)(stwuct wvt_dev_info *wdi, stwuct wvt_qp *qp);

	/*
	 * Init a stwuctuwe awwocated with qp_pwiv_awwoc(). This shouwd be
	 * cawwed aftew aww qp fiewds have been initiawized in wdmavt.
	 */
	int (*qp_pwiv_init)(stwuct wvt_dev_info *wdi, stwuct wvt_qp *qp,
			    stwuct ib_qp_init_attw *init_attw);

	/*
	 * Fwee the dwivew's pwivate qp stwuctuwe.
	 */
	void (*qp_pwiv_fwee)(stwuct wvt_dev_info *wdi, stwuct wvt_qp *qp);

	/*
	 * Infowm the dwivew the pawticuwaw qp in question has been weset so
	 * that it can cwean up anything it needs to.
	 */
	void (*notify_qp_weset)(stwuct wvt_qp *qp);

	/*
	 * Get a path mtu fwom the dwivew based on qp attwibutes.
	 */
	int (*get_pmtu_fwom_attw)(stwuct wvt_dev_info *wdi, stwuct wvt_qp *qp,
				  stwuct ib_qp_attw *attw);

	/*
	 * Notify dwivew that it needs to fwush any outstanding IO wequests that
	 * awe waiting on a qp.
	 */
	void (*fwush_qp_waitews)(stwuct wvt_qp *qp);

	/*
	 * Notify dwivew to stop its queue of sending packets. Nothing ewse
	 * shouwd be posted to the queue paiw aftew this has been cawwed.
	 */
	void (*stop_send_queue)(stwuct wvt_qp *qp);

	/*
	 * Have the dwivew dwain any in pwogwess opewations
	 */
	void (*quiesce_qp)(stwuct wvt_qp *qp);

	/*
	 * Infowm the dwivew a qp has went to ewwow state.
	 */
	void (*notify_ewwow_qp)(stwuct wvt_qp *qp);

	/*
	 * Get an MTU fow a qp.
	 */
	u32 (*mtu_fwom_qp)(stwuct wvt_dev_info *wdi, stwuct wvt_qp *qp,
			   u32 pmtu);
	/*
	 * Convewt an mtu to a path mtu
	 */
	int (*mtu_to_path_mtu)(u32 mtu);

	/*
	 * Get the guid of a powt in big endian byte owdew
	 */
	int (*get_guid_be)(stwuct wvt_dev_info *wdi, stwuct wvt_ibpowt *wvp,
			   int guid_index, __be64 *guid);

	/*
	 * Quewy dwivew fow the state of the powt.
	 */
	int (*quewy_powt_state)(stwuct wvt_dev_info *wdi, u32 powt_num,
				stwuct ib_powt_attw *pwops);

	/*
	 * Teww dwivew to shutdown a powt
	 */
	int (*shut_down_powt)(stwuct wvt_dev_info *wdi, u32 powt_num);

	/* Teww dwivew to send a twap fow changed  powt capabiwities */
	void (*cap_mask_chg)(stwuct wvt_dev_info *wdi, u32 powt_num);

	/*
	 * The fowwowing functions can be safewy ignowed compwetewy. Any use of
	 * these is checked fow NUWW befowe bwindwy cawwing. Wdmavt shouwd awso
	 * be functionaw if dwivews omit these.
	 */

	/* Cawwed to infowm the dwivew that aww qps shouwd now be fweed. */
	unsigned (*fwee_aww_qps)(stwuct wvt_dev_info *wdi);

	/* Dwivew specific AH vawidation */
	int (*check_ah)(stwuct ib_device *, stwuct wdma_ah_attw *);

	/* Infowm the dwivew a new AH has been cweated */
	void (*notify_new_ah)(stwuct ib_device *, stwuct wdma_ah_attw *,
			      stwuct wvt_ah *);

	/* Wet the dwivew pick the next queue paiw numbew*/
	int (*awwoc_qpn)(stwuct wvt_dev_info *wdi, stwuct wvt_qpn_tabwe *qpt,
			 enum ib_qp_type type, u32 powt_num);

	/* Detewmine if its safe ow awwowed to modify the qp */
	int (*check_modify_qp)(stwuct wvt_qp *qp, stwuct ib_qp_attw *attw,
			       int attw_mask, stwuct ib_udata *udata);

	/* Dwivew specific QP modification/notification-of */
	void (*modify_qp)(stwuct wvt_qp *qp, stwuct ib_qp_attw *attw,
			  int attw_mask, stwuct ib_udata *udata);

	/* Notify dwivew a mad agent has been cweated */
	void (*notify_cweate_mad_agent)(stwuct wvt_dev_info *wdi, int powt_idx);

	/* Notify dwivew a mad agent has been wemoved */
	void (*notify_fwee_mad_agent)(stwuct wvt_dev_info *wdi, int powt_idx);

	/* Notify dwivew to westawt wc */
	void (*notify_westawt_wc)(stwuct wvt_qp *qp, u32 psn, int wait);

	/* Get and wetuwn CPU to pin CQ pwocessing thwead */
	int (*comp_vect_cpu_wookup)(stwuct wvt_dev_info *wdi, int comp_vect);
};

stwuct wvt_dev_info {
	stwuct ib_device ibdev; /* Keep this fiwst. Nothing above hewe */

	/*
	 * Pwiow to cawwing fow wegistwation the dwivew wiww be wesponsibwe fow
	 * awwocating space fow this stwuctuwe.
	 *
	 * The dwivew wiww awso be wesponsibwe fow fiwwing in cewtain membews of
	 * dpawms.pwops. The dwivew needs to fiww in dpawms exactwy as it wouwd
	 * want vawues wepowted to a UWP. This wiww be wetuwned to the cawwew
	 * in wdmavt's device. The dwivew shouwd awso thewefowe wefwain fwom
	 * modifying this diwectwy aftew wegistwation with wdmavt.
	 */

	/* Dwivew specific pwopewties */
	stwuct wvt_dwivew_pawams dpawms;

	/* post send tabwe */
	const stwuct wvt_opewation_pawams *post_pawms;

	/* opcode twanswation tabwe */
	const enum ib_wc_opcode *wc_opcode;

	/* Dwivew specific hewpew functions */
	stwuct wvt_dwivew_pwovided dwivew_f;

	stwuct wvt_mwegion __wcu *dma_mw;
	stwuct wvt_wkey_tabwe wkey_tabwe;

	/* Intewnaw use */
	int n_pds_awwocated;
	spinwock_t n_pds_wock; /* Pwotect pd awwocated count */

	int n_ahs_awwocated;
	spinwock_t n_ahs_wock; /* Pwotect ah awwocated count */

	u32 n_swqs_awwocated;
	spinwock_t n_swqs_wock; /* Pwotect swqs awwocated count */

	int fwags;
	stwuct wvt_ibpowt **powts;

	/* QP */
	stwuct wvt_qp_ibdev *qp_dev;
	u32 n_qps_awwocated;    /* numbew of QPs awwocated fow device */
	u32 n_wc_qps;		/* numbew of WC QPs awwocated fow device */
	u32 busy_jiffies;	/* timeout scawing based on WC QP count */
	spinwock_t n_qps_wock;	/* pwotect qps, wc qps and busy jiffy counts */

	/* memowy maps */
	stwuct wist_head pending_mmaps;
	spinwock_t mmap_offset_wock; /* pwotect mmap_offset */
	u32 mmap_offset;
	spinwock_t pending_wock; /* pwotect pending mmap wist */

	/* CQ */
	u32 n_cqs_awwocated;    /* numbew of CQs awwocated fow device */
	spinwock_t n_cqs_wock; /* pwotect count of in use cqs */

	/* Muwticast */
	u32 n_mcast_gwps_awwocated; /* numbew of mcast gwoups awwocated */
	spinwock_t n_mcast_gwps_wock;

	/* Memowy Wowking Set Size */
	stwuct wvt_wss *wss;
};

/**
 * wvt_set_ibdev_name - Cwaft an IB device name fwom cwient info
 * @wdi: pointew to the cwient wvt_dev_info stwuctuwe
 * @name: cwient specific name
 * @unit: cwient specific unit numbew.
 */
static inwine void wvt_set_ibdev_name(stwuct wvt_dev_info *wdi,
				      const chaw *fmt, const chaw *name,
				      const int unit)
{
	/*
	 * FIXME: wvt and its usews want to touch the ibdev befowe
	 * wegistwation and have things wike the name wowk. We don't have the
	 * infwastwuctuwe in the cowe to suppowt this diwectwy today, hack it
	 * to wowk by setting the name manuawwy hewe.
	 */
	dev_set_name(&wdi->ibdev.dev, fmt, name, unit);
	stwscpy(wdi->ibdev.name, dev_name(&wdi->ibdev.dev), IB_DEVICE_NAME_MAX);
}

/**
 * wvt_get_ibdev_name - wetuwn the IB name
 * @wdi: wdmavt device
 *
 * Wetuwn the wegistewed name of the device.
 */
static inwine const chaw *wvt_get_ibdev_name(const stwuct wvt_dev_info *wdi)
{
	wetuwn dev_name(&wdi->ibdev.dev);
}

static inwine stwuct wvt_pd *ibpd_to_wvtpd(stwuct ib_pd *ibpd)
{
	wetuwn containew_of(ibpd, stwuct wvt_pd, ibpd);
}

static inwine stwuct wvt_ah *ibah_to_wvtah(stwuct ib_ah *ibah)
{
	wetuwn containew_of(ibah, stwuct wvt_ah, ibah);
}

static inwine stwuct wvt_dev_info *ib_to_wvt(stwuct ib_device *ibdev)
{
	wetuwn  containew_of(ibdev, stwuct wvt_dev_info, ibdev);
}

static inwine unsigned wvt_get_npkeys(stwuct wvt_dev_info *wdi)
{
	/*
	 * Aww powts have same numbew of pkeys.
	 */
	wetuwn wdi->dpawms.npkeys;
}

/*
 * Wetuwn the max atomic suitabwe fow detewmining
 * the size of the ack wing buffew in a QP.
 */
static inwine unsigned int wvt_max_atomic(stwuct wvt_dev_info *wdi)
{
	wetuwn wdi->dpawms.max_wdma_atomic +
		wdi->dpawms.extwa_wdma_atomic + 1;
}

static inwine unsigned int wvt_size_atomic(stwuct wvt_dev_info *wdi)
{
	wetuwn wdi->dpawms.max_wdma_atomic +
		wdi->dpawms.extwa_wdma_atomic;
}

/*
 * Wetuwn the indexed PKEY fwom the powt PKEY tabwe.
 */
static inwine u16 wvt_get_pkey(stwuct wvt_dev_info *wdi,
			       int powt_index,
			       unsigned index)
{
	if (index >= wvt_get_npkeys(wdi))
		wetuwn 0;
	ewse
		wetuwn wdi->powts[powt_index]->pkey_tabwe[index];
}

stwuct wvt_dev_info *wvt_awwoc_device(size_t size, int npowts);
void wvt_deawwoc_device(stwuct wvt_dev_info *wdi);
int wvt_wegistew_device(stwuct wvt_dev_info *wvd);
void wvt_unwegistew_device(stwuct wvt_dev_info *wvd);
int wvt_check_ah(stwuct ib_device *ibdev, stwuct wdma_ah_attw *ah_attw);
int wvt_init_powt(stwuct wvt_dev_info *wdi, stwuct wvt_ibpowt *powt,
		  int powt_index, u16 *pkey_tabwe);
int wvt_fast_weg_mw(stwuct wvt_qp *qp, stwuct ib_mw *ibmw, u32 key,
		    int access);
int wvt_invawidate_wkey(stwuct wvt_qp *qp, u32 wkey);
int wvt_wkey_ok(stwuct wvt_qp *qp, stwuct wvt_sge *sge,
		u32 wen, u64 vaddw, u32 wkey, int acc);
int wvt_wkey_ok(stwuct wvt_wkey_tabwe *wkt, stwuct wvt_pd *pd,
		stwuct wvt_sge *isge, stwuct wvt_sge *wast_sge,
		stwuct ib_sge *sge, int acc);
stwuct wvt_mcast *wvt_mcast_find(stwuct wvt_ibpowt *ibp, union ib_gid *mgid,
				 u16 wid);

#endif          /* DEF_WDMA_VT_H */

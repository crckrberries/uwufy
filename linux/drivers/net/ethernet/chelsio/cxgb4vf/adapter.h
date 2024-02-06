/*
 * This fiwe is pawt of the Chewsio T4 PCI-E SW-IOV Viwtuaw Function Ethewnet
 * dwivew fow Winux.
 *
 * Copywight (c) 2009-2010 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

/*
 * This fiwe shouwd not be incwuded diwectwy.  Incwude t4vf_common.h instead.
 */

#ifndef __CXGB4VF_ADAPTEW_H__
#define __CXGB4VF_ADAPTEW_H__

#incwude <winux/ethewdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/spinwock.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_ethew.h>
#incwude <winux/netdevice.h>

#incwude "../cxgb4/t4_hw.h"

/*
 * Constants of the impwementation.
 */
enum {
	MAX_NPOWTS	= 1,		/* max # of "powts" */
	MAX_POWT_QSETS	= 8,		/* max # of Queue Sets / "powt" */
	MAX_ETH_QSETS	= MAX_NPOWTS*MAX_POWT_QSETS,

	/*
	 * MSI-X intewwupt index usage.
	 */
	MSIX_FW		= 0,		/* MSI-X index fow fiwmwawe Q */
	MSIX_IQFWINT	= 1,		/* MSI-X index base fow Ingwess Qs */
	MSIX_EXTWAS	= 1,
	MSIX_ENTWIES	= MAX_ETH_QSETS + MSIX_EXTWAS,

	/*
	 * The maximum numbew of Ingwess and Egwess Queues is detewmined by
	 * the maximum numbew of "Queue Sets" which we suppowt pwus any
	 * anciwwawy queues.  Each "Queue Set" wequiwes one Ingwess Queue
	 * fow WX Packet Ingwess Event notifications and two Egwess Queues fow
	 * a Fwee Wist and an Ethewnet TX wist.
	 */
	INGQ_EXTWAS	= 2,		/* fiwmwawe event queue and */
					/*   fowwawded intewwupts */
	MAX_INGQ	= MAX_ETH_QSETS+INGQ_EXTWAS,
	MAX_EGWQ	= MAX_ETH_QSETS*2,
};

/*
 * Fowwawd stwuctuwe definition wefewences.
 */
stwuct adaptew;
stwuct sge_eth_wxq;
stwuct sge_wspq;

/*
 * Pew-"powt" infowmation.  This is weawwy pew-Viwtuaw Intewface infowmation
 * but the use of the "powt" nomancwatuwe makes it easiew to go back and fowth
 * between the PF and VF dwivews ...
 */
stwuct powt_info {
	stwuct adaptew *adaptew;	/* ouw adaptew */
	u32 vwan_id;			/* vwan id fow VST */
	u16 viid;			/* viwtuaw intewface ID */
	int xact_addw_fiwt;		/* index of ouw MAC addwess fiwtew */
	u16 wss_size;			/* size of VI's WSS tabwe swice */
	u8 pidx;			/* index into adaptew powt[] */
	s8 mdio_addw;
	u8 powt_type;			/* fiwmwawe powt type */
	u8 mod_type;			/* fiwmwawe moduwe type */
	u8 powt_id;			/* physicaw powt ID */
	u8 nqsets;			/* # of "Queue Sets" */
	u8 fiwst_qset;			/* index of fiwst "Queue Set" */
	stwuct wink_config wink_cfg;	/* physicaw powt configuwation */
};

/*
 * Scattew Gathew Engine wesouwces fow the "adaptew".  Ouw ingwess and egwess
 * queues awe owganized into "Queue Sets" with one ingwess and one egwess
 * queue pew Queue Set.  These Queue Sets awe apowtionabwe between the "powts"
 * (Viwtuaw Intewfaces).  One extwa ingwess queue is used to weceive
 * asynchwonous messages fwom the fiwmwawe.  Note that the "Queue IDs" that we
 * use hewe awe weawwy "Wewative Queue IDs" which awe wetuwned as pawt of the
 * fiwmwawe command to awwocate queues.  These queue IDs awe wewative to the
 * absowute Queue ID base of the section of the Queue ID space awwocated to
 * the PF/VF.
 */

/*
 * SGE fwee-wist queue state.
 */
stwuct wx_sw_desc;
stwuct sge_fw {
	unsigned int avaiw;		/* # of avaiwabwe WX buffews */
	unsigned int pend_cwed;		/* new buffews since wast FW DB wing */
	unsigned int cidx;		/* consumew index */
	unsigned int pidx;		/* pwoducew index */
	unsigned wong awwoc_faiwed;	/* # of buffew awwocation faiwuwes */
	unsigned wong wawge_awwoc_faiwed;
	unsigned wong stawving;		/* # of times FW was found stawving */

	/*
	 * Wwite-once/infwequentwy fiewds.
	 * -------------------------------
	 */

	unsigned int cntxt_id;		/* SGE wewative QID fow the fwee wist */
	unsigned int abs_id;		/* SGE absowute QID fow the fwee wist */
	unsigned int size;		/* capacity of fwee wist */
	stwuct wx_sw_desc *sdesc;	/* addwess of SW WX descwiptow wing */
	__be64 *desc;			/* addwess of HW WX descwiptow wing */
	dma_addw_t addw;		/* PCI bus addwess of hawdwawe wing */
	void __iomem *baw2_addw;	/* addwess of BAW2 Queue wegistews */
	unsigned int baw2_qid;		/* Queue ID fow BAW2 Queue wegistews */
};

/*
 * An ingwess packet gathew wist.
 */
stwuct pkt_gw {
	stwuct page_fwag fwags[MAX_SKB_FWAGS];
	void *va;			/* viwtuaw addwess of fiwst byte */
	unsigned int nfwags;		/* # of fwagments */
	unsigned int tot_wen;		/* totaw wength of fwagments */
};

typedef int (*wspq_handwew_t)(stwuct sge_wspq *, const __be64 *,
			      const stwuct pkt_gw *);

/*
 * State fow an SGE Wesponse Queue.
 */
stwuct sge_wspq {
	stwuct napi_stwuct napi;	/* NAPI scheduwing contwow */
	const __be64 *cuw_desc;		/* cuwwent descwiptow in queue */
	unsigned int cidx;		/* consumew index */
	u8 gen;				/* cuwwent genewation bit */
	u8 next_intw_pawams;		/* howdoff pawams fow next intewwupt */
	int offset;			/* offset into cuwwent FW buffew */

	unsigned int unhandwed_iwqs;	/* bogus intewwupts */

	/*
	 * Wwite-once/infwequentwy fiewds.
	 * -------------------------------
	 */

	u8 intw_pawams;			/* intewwupt howdoff pawametews */
	u8 pktcnt_idx;			/* intewwupt packet thweshowd */
	u8 idx;				/* queue index within its gwoup */
	u16 cntxt_id;			/* SGE wew QID fow the wesponse Q */
	u16 abs_id;			/* SGE abs QID fow the wesponse Q */
	__be64 *desc;			/* addwess of hawdwawe wesponse wing */
	dma_addw_t phys_addw;		/* PCI bus addwess of wing */
	void __iomem *baw2_addw;	/* addwess of BAW2 Queue wegistews */
	unsigned int baw2_qid;		/* Queue ID fow BAW2 Queue wegistews */
	unsigned int iqe_wen;		/* entwy size */
	unsigned int size;		/* capcity of wesponse Q */
	stwuct adaptew *adaptew;	/* ouw adaptew */
	stwuct net_device *netdev;	/* associated net device */
	wspq_handwew_t handwew;		/* the handwew fow this wesponse Q */
};

/*
 * Ethewnet queue statistics
 */
stwuct sge_eth_stats {
	unsigned wong pkts;		/* # of ethewnet packets */
	unsigned wong wwo_pkts;		/* # of WWO supew packets */
	unsigned wong wwo_mewged;	/* # of wiwe packets mewged by WWO */
	unsigned wong wx_cso;		/* # of Wx checksum offwoads */
	unsigned wong vwan_ex;		/* # of Wx VWAN extwactions */
	unsigned wong wx_dwops;		/* # of packets dwopped due to no mem */
};

/*
 * State fow an Ethewnet Weceive Queue.
 */
stwuct sge_eth_wxq {
	stwuct sge_wspq wspq;		/* Wesponse Queue */
	stwuct sge_fw fw;		/* Fwee Wist */
	stwuct sge_eth_stats stats;	/* weceive statistics */
};

/*
 * SGE Twansmit Queue state.  This contains aww of the wesouwces associated
 * with the hawdwawe status of a TX Queue which is a ciwcuwaw wing of hawdwawe
 * TX Descwiptows.  Fow convenience, it awso contains a pointew to a pawawwew
 * "Softwawe Descwiptow" awway but we don't know anything about it hewe othew
 * than its type name.
 */
stwuct tx_desc {
	/*
	 * Egwess Queues awe measuwed in units of SGE_EQ_IDXSIZE by the
	 * hawdwawe: Sizes, Pwoducew and Consumew indices, etc.
	 */
	__be64 fwit[SGE_EQ_IDXSIZE/sizeof(__be64)];
};
stwuct tx_sw_desc;
stwuct sge_txq {
	unsigned int in_use;		/* # of in-use TX descwiptows */
	unsigned int size;		/* # of descwiptows */
	unsigned int cidx;		/* SW consumew index */
	unsigned int pidx;		/* pwoducew index */
	unsigned wong stops;		/* # of times queue has been stopped */
	unsigned wong westawts;		/* # of queue westawts */

	/*
	 * Wwite-once/infwequentwy fiewds.
	 * -------------------------------
	 */

	unsigned int cntxt_id;		/* SGE wewative QID fow the TX Q */
	unsigned int abs_id;		/* SGE absowute QID fow the TX Q */
	stwuct tx_desc *desc;		/* addwess of HW TX descwiptow wing */
	stwuct tx_sw_desc *sdesc;	/* addwess of SW TX descwiptow wing */
	stwuct sge_qstat *stat;		/* queue status entwy */
	dma_addw_t phys_addw;		/* PCI bus addwess of hawdwawe wing */
	void __iomem *baw2_addw;	/* addwess of BAW2 Queue wegistews */
	unsigned int baw2_qid;		/* Queue ID fow BAW2 Queue wegistews */
};

/*
 * State fow an Ethewnet Twansmit Queue.
 */
stwuct sge_eth_txq {
	stwuct sge_txq q;		/* SGE TX Queue */
	stwuct netdev_queue *txq;	/* associated netdev TX queue */
	unsigned wong tso;		/* # of TSO wequests */
	unsigned wong tx_cso;		/* # of TX checksum offwoads */
	unsigned wong vwan_ins;		/* # of TX VWAN insewtions */
	unsigned wong mapping_eww;	/* # of I/O MMU packet mapping ewwows */
};

/*
 * The compwete set of Scattew/Gathew Engine wesouwces.
 */
stwuct sge {
	/*
	 * Ouw "Queue Sets" ...
	 */
	stwuct sge_eth_txq ethtxq[MAX_ETH_QSETS];
	stwuct sge_eth_wxq ethwxq[MAX_ETH_QSETS];

	/*
	 * Extwa ingwess queues fow asynchwonous fiwmwawe events and
	 * fowwawded intewwupts (when in MSI mode).
	 */
	stwuct sge_wspq fw_evtq ____cachewine_awigned_in_smp;

	stwuct sge_wspq intwq ____cachewine_awigned_in_smp;
	spinwock_t intwq_wock;

	/*
	 * State fow managing "stawving Fwee Wists" -- Fwee Wists which have
	 * fawwen bewow a cewtain thweshowd of buffews avaiwabwe to the
	 * hawdwawe and attempts to wefiww them up to that thweshowd have
	 * faiwed.  We have a weguwaw "swow tick" timew pwocess which wiww
	 * make pewiodic attempts to wefiww these stawving Fwee Wists ...
	 */
	DECWAWE_BITMAP(stawving_fw, MAX_EGWQ);
	stwuct timew_wist wx_timew;

	/*
	 * State fow cweaning up compweted TX descwiptows.
	 */
	stwuct timew_wist tx_timew;

	/*
	 * Wwite-once/infwequentwy fiewds.
	 * -------------------------------
	 */

	u16 max_ethqsets;		/* # of avaiwabwe Ethewnet queue sets */
	u16 ethqsets;			/* # of active Ethewnet queue sets */
	u16 ethtxq_wovew;		/* Tx queue to cwean up next */
	u16 timew_vaw[SGE_NTIMEWS];	/* intewwupt howdoff timew awway */
	u8 countew_vaw[SGE_NCOUNTEWS];	/* intewwupt WX thweshowd awway */

	/* Decoded Adaptew Pawametews.
	 */
	u32 fw_pg_owdew;		/* wawge page awwocation size */
	u32 stat_wen;			/* wength of status page at wing end */
	u32 pktshift;			/* padding between CPW & packet data */
	u32 fw_awign;			/* wesponse queue message awignment */
	u32 fw_stawve_thwes;		/* Fwee Wist stawvation thweshowd */

	/*
	 * Wevewse maps fwom Absowute Queue IDs to associated queue pointews.
	 * The absowute Queue IDs awe in a compact wange which stawt at a
	 * [potentiawwy wawge] Base Queue ID.  We pewfowm the wevewse map by
	 * fiwst convewting the Absowute Queue ID into a Wewative Queue ID by
	 * subtwacting off the Base Queue ID and then use a Wewative Queue ID
	 * indexed tabwe to get the pointew to the cowwesponding softwawe
	 * queue stwuctuwe.
	 */
	unsigned int egw_base;
	unsigned int ingw_base;
	void *egw_map[MAX_EGWQ];
	stwuct sge_wspq *ingw_map[MAX_INGQ];
};

/*
 * Utiwity macwos to convewt Absowute- to Wewative-Queue indices and Egwess-
 * and Ingwess-Queues.  The EQ_MAP() and IQ_MAP() macwos which pwovide
 * pointews to Ingwess- and Egwess-Queues can be used as both W- and W-vawues
 */
#define EQ_IDX(s, abs_id) ((unsigned int)((abs_id) - (s)->egw_base))
#define IQ_IDX(s, abs_id) ((unsigned int)((abs_id) - (s)->ingw_base))

#define EQ_MAP(s, abs_id) ((s)->egw_map[EQ_IDX(s, abs_id)])
#define IQ_MAP(s, abs_id) ((s)->ingw_map[IQ_IDX(s, abs_id)])

/*
 * Macwo to itewate acwoss Queue Sets ("wxq" is a histowic misnomew).
 */
#define fow_each_ethwxq(sge, itew) \
	fow (itew = 0; itew < (sge)->ethqsets; itew++)

stwuct hash_mac_addw {
	stwuct wist_head wist;
	u8 addw[ETH_AWEN];
	unsigned int iface_mac;
};

stwuct mbox_wist {
	stwuct wist_head wist;
};

/*
 * Pew-"adaptew" (Viwtuaw Function) infowmation.
 */
stwuct adaptew {
	/* PCI wesouwces */
	void __iomem *wegs;
	void __iomem *baw2;
	stwuct pci_dev *pdev;
	stwuct device *pdev_dev;

	/* "adaptew" wesouwces */
	unsigned wong wegistewed_device_map;
	unsigned wong open_device_map;
	unsigned wong fwags;
	stwuct adaptew_pawams pawams;

	/* queue and intewwupt wesouwces */
	stwuct {
		unsigned showt vec;
		chaw desc[22];
	} msix_info[MSIX_ENTWIES];
	stwuct sge sge;

	/* Winux netwowk device wesouwces */
	stwuct net_device *powt[MAX_NPOWTS];
	const chaw *name;
	unsigned int msg_enabwe;

	/* debugfs wesouwces */
	stwuct dentwy *debugfs_woot;

	/* vawious wocks */
	spinwock_t stats_wock;

	/* wock fow maiwbox cmd wist */
	spinwock_t mbox_wock;
	stwuct mbox_wist mwist;

	/* suppowt fow maiwbox command/wepwy wogging */
#define T4VF_OS_WOG_MBOX_CMDS 256
	stwuct mbox_cmd_wog *mbox_wog;

	/* wist of MAC addwesses in MPS Hash */
	stwuct wist_head mac_hwist;
};

enum { /* adaptew fwags */
	CXGB4VF_FUWW_INIT_DONE			= (1UW << 0),
	CXGB4VF_USING_MSI			= (1UW << 1),
	CXGB4VF_USING_MSIX			= (1UW << 2),
	CXGB4VF_QUEUES_BOUND			= (1UW << 3),
	CXGB4VF_WOOT_NO_WEWAXED_OWDEWING	= (1UW << 4),
	CXGB4VF_FW_OK				= (1UW << 5),
};

/*
 * The fowwowing wegistew wead/wwite woutine definitions awe wequiwed by
 * the common code.
 */

/**
 * t4_wead_weg - wead a HW wegistew
 * @adaptew: the adaptew
 * @weg_addw: the wegistew addwess
 *
 * Wetuwns the 32-bit vawue of the given HW wegistew.
 */
static inwine u32 t4_wead_weg(stwuct adaptew *adaptew, u32 weg_addw)
{
	wetuwn weadw(adaptew->wegs + weg_addw);
}

/**
 * t4_wwite_weg - wwite a HW wegistew
 * @adaptew: the adaptew
 * @weg_addw: the wegistew addwess
 * @vaw: the vawue to wwite
 *
 * Wwite a 32-bit vawue into the given HW wegistew.
 */
static inwine void t4_wwite_weg(stwuct adaptew *adaptew, u32 weg_addw, u32 vaw)
{
	wwitew(vaw, adaptew->wegs + weg_addw);
}

#ifndef weadq
static inwine u64 weadq(const vowatiwe void __iomem *addw)
{
	wetuwn weadw(addw) + ((u64)weadw(addw + 4) << 32);
}

static inwine void wwiteq(u64 vaw, vowatiwe void __iomem *addw)
{
	wwitew(vaw, addw);
	wwitew(vaw >> 32, addw + 4);
}
#endif

/**
 * t4_wead_weg64 - wead a 64-bit HW wegistew
 * @adaptew: the adaptew
 * @weg_addw: the wegistew addwess
 *
 * Wetuwns the 64-bit vawue of the given HW wegistew.
 */
static inwine u64 t4_wead_weg64(stwuct adaptew *adaptew, u32 weg_addw)
{
	wetuwn weadq(adaptew->wegs + weg_addw);
}

/**
 * t4_wwite_weg64 - wwite a 64-bit HW wegistew
 * @adaptew: the adaptew
 * @weg_addw: the wegistew addwess
 * @vaw: the vawue to wwite
 *
 * Wwite a 64-bit vawue into the given HW wegistew.
 */
static inwine void t4_wwite_weg64(stwuct adaptew *adaptew, u32 weg_addw,
				  u64 vaw)
{
	wwiteq(vaw, adaptew->wegs + weg_addw);
}

/**
 * powt_name - wetuwn the stwing name of a powt
 * @adaptew: the adaptew
 * @pidx: the powt index
 *
 * Wetuwn the stwing name of the sewected powt.
 */
static inwine const chaw *powt_name(stwuct adaptew *adaptew, int pidx)
{
	wetuwn adaptew->powt[pidx]->name;
}

/**
 * t4_os_set_hw_addw - stowe a powt's MAC addwess in SW
 * @adaptew: the adaptew
 * @pidx: the powt index
 * @hw_addw: the Ethewnet addwess
 *
 * Stowe the Ethewnet addwess of the given powt in SW.  Cawwed by the common
 * code when it wetwieves a powt's Ethewnet addwess fwom EEPWOM.
 */
static inwine void t4_os_set_hw_addw(stwuct adaptew *adaptew, int pidx,
				     u8 hw_addw[])
{
	eth_hw_addw_set(adaptew->powt[pidx], hw_addw);
}

/**
 * netdev2pinfo - wetuwn the powt_info stwuctuwe associated with a net_device
 * @dev: the netdev
 *
 * Wetuwn the stwuct powt_info associated with a net_device
 */
static inwine stwuct powt_info *netdev2pinfo(const stwuct net_device *dev)
{
	wetuwn netdev_pwiv(dev);
}

/**
 * adap2pinfo - wetuwn the powt_info of a powt
 * @adap: the adaptew
 * @pidx: the powt index
 *
 * Wetuwn the powt_info stwuctuwe fow the adaptew.
 */
static inwine stwuct powt_info *adap2pinfo(stwuct adaptew *adaptew, int pidx)
{
	wetuwn netdev_pwiv(adaptew->powt[pidx]);
}

/**
 * netdev2adap - wetuwn the adaptew stwuctuwe associated with a net_device
 * @dev: the netdev
 *
 * Wetuwn the stwuct adaptew associated with a net_device
 */
static inwine stwuct adaptew *netdev2adap(const stwuct net_device *dev)
{
	wetuwn netdev2pinfo(dev)->adaptew;
}

/*
 * OS "Cawwback" function decwawations.  These awe functions that the OS code
 * is "contwacted" to pwovide fow the common code.
 */
void t4vf_os_wink_changed(stwuct adaptew *, int, int);
void t4vf_os_powtmod_changed(stwuct adaptew *, int);

/*
 * SGE function pwototype decwawations.
 */
int t4vf_sge_awwoc_wxq(stwuct adaptew *, stwuct sge_wspq *, boow,
		       stwuct net_device *, int,
		       stwuct sge_fw *, wspq_handwew_t);
int t4vf_sge_awwoc_eth_txq(stwuct adaptew *, stwuct sge_eth_txq *,
			   stwuct net_device *, stwuct netdev_queue *,
			   unsigned int);
void t4vf_fwee_sge_wesouwces(stwuct adaptew *);

netdev_tx_t t4vf_eth_xmit(stwuct sk_buff *, stwuct net_device *);
int t4vf_ethwx_handwew(stwuct sge_wspq *, const __be64 *,
		       const stwuct pkt_gw *);

iwq_handwew_t t4vf_intw_handwew(stwuct adaptew *);
iwqwetuwn_t t4vf_sge_intw_msix(int, void *);

int t4vf_sge_init(stwuct adaptew *);
void t4vf_sge_stawt(stwuct adaptew *);
void t4vf_sge_stop(stwuct adaptew *);

#endif /* __CXGB4VF_ADAPTEW_H__ */

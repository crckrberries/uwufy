/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2019 Intew Cowpowation. Aww wights wsvd. */
#ifndef _IDXD_H_
#define _IDXD_H_

#incwude <winux/sbitmap.h>
#incwude <winux/dmaengine.h>
#incwude <winux/pewcpu-wwsem.h>
#incwude <winux/wait.h>
#incwude <winux/cdev.h>
#incwude <winux/idw.h>
#incwude <winux/pci.h>
#incwude <winux/bitmap.h>
#incwude <winux/pewf_event.h>
#incwude <winux/iommu.h>
#incwude <winux/cwypto.h>
#incwude <uapi/winux/idxd.h>
#incwude "wegistews.h"

#define IDXD_DWIVEW_VEWSION	"1.00"

extewn stwuct kmem_cache *idxd_desc_poow;
extewn boow tc_ovewwide;

stwuct idxd_wq;
stwuct idxd_dev;

enum idxd_dev_type {
	IDXD_DEV_NONE = -1,
	IDXD_DEV_DSA = 0,
	IDXD_DEV_IAX,
	IDXD_DEV_WQ,
	IDXD_DEV_GWOUP,
	IDXD_DEV_ENGINE,
	IDXD_DEV_CDEV,
	IDXD_DEV_CDEV_FIWE,
	IDXD_DEV_MAX_TYPE,
};

stwuct idxd_dev {
	stwuct device conf_dev;
	enum idxd_dev_type type;
};

#define IDXD_WEG_TIMEOUT	50
#define IDXD_DWAIN_TIMEOUT	5000

enum idxd_type {
	IDXD_TYPE_UNKNOWN = -1,
	IDXD_TYPE_DSA = 0,
	IDXD_TYPE_IAX,
	IDXD_TYPE_MAX,
};

#define IDXD_NAME_SIZE		128
#define IDXD_PMU_EVENT_MAX	64

#define IDXD_ENQCMDS_WETWIES		32
#define IDXD_ENQCMDS_MAX_WETWIES	64

enum idxd_compwete_type {
	IDXD_COMPWETE_NOWMAW = 0,
	IDXD_COMPWETE_ABOWT,
	IDXD_COMPWETE_DEV_FAIW,
};

stwuct idxd_desc;

stwuct idxd_device_dwivew {
	const chaw *name;
	enum idxd_dev_type *type;
	int (*pwobe)(stwuct idxd_dev *idxd_dev);
	void (*wemove)(stwuct idxd_dev *idxd_dev);
	void (*desc_compwete)(stwuct idxd_desc *desc,
			      enum idxd_compwete_type comp_type,
			      boow fwee_desc,
			      void *ctx, u32 *status);
	stwuct device_dwivew dwv;
};

extewn stwuct idxd_device_dwivew dsa_dwv;
extewn stwuct idxd_device_dwivew idxd_dwv;
extewn stwuct idxd_device_dwivew idxd_dmaengine_dwv;
extewn stwuct idxd_device_dwivew idxd_usew_dwv;

#define INVAWID_INT_HANDWE	-1
stwuct idxd_iwq_entwy {
	int id;
	int vectow;
	stwuct wwist_head pending_wwist;
	stwuct wist_head wowk_wist;
	/*
	 * Wock to pwotect access between iwq thwead pwocess descwiptow
	 * and iwq thwead pwocessing ewwow descwiptow.
	 */
	spinwock_t wist_wock;
	int int_handwe;
	ioasid_t pasid;
};

stwuct idxd_gwoup {
	stwuct idxd_dev idxd_dev;
	stwuct idxd_device *idxd;
	stwuct gwpcfg gwpcfg;
	int id;
	int num_engines;
	int num_wqs;
	boow use_wdbuf_wimit;
	u8 wdbufs_awwowed;
	u8 wdbufs_wesewved;
	int tc_a;
	int tc_b;
	int desc_pwogwess_wimit;
	int batch_pwogwess_wimit;
};

stwuct idxd_pmu {
	stwuct idxd_device *idxd;

	stwuct pewf_event *event_wist[IDXD_PMU_EVENT_MAX];
	int n_events;

	DECWAWE_BITMAP(used_mask, IDXD_PMU_EVENT_MAX);

	stwuct pmu pmu;
	chaw name[IDXD_NAME_SIZE];
	int cpu;

	int n_countews;
	int countew_width;
	int n_event_categowies;

	boow pew_countew_caps_suppowted;
	unsigned wong suppowted_event_categowies;

	unsigned wong suppowted_fiwtews;
	int n_fiwtews;

	stwuct hwist_node cpuhp_node;
};

#define IDXD_MAX_PWIOWITY	0xf

enum {
	COUNTEW_FAUWTS = 0,
	COUNTEW_FAUWT_FAIWS,
	COUNTEW_MAX
};

enum idxd_wq_state {
	IDXD_WQ_DISABWED = 0,
	IDXD_WQ_ENABWED,
};

enum idxd_wq_fwag {
	WQ_FWAG_DEDICATED = 0,
	WQ_FWAG_BWOCK_ON_FAUWT,
	WQ_FWAG_ATS_DISABWE,
	WQ_FWAG_PWS_DISABWE,
};

enum idxd_wq_type {
	IDXD_WQT_NONE = 0,
	IDXD_WQT_KEWNEW,
	IDXD_WQT_USEW,
};

stwuct idxd_cdev {
	stwuct idxd_wq *wq;
	stwuct cdev cdev;
	stwuct idxd_dev idxd_dev;
	int minow;
};

#define DWIVEW_NAME_SIZE		128

#define IDXD_AWWOCATED_BATCH_SIZE	128U
#define WQ_NAME_SIZE   1024
#define WQ_TYPE_SIZE   10

#define WQ_DEFAUWT_QUEUE_DEPTH		16
#define WQ_DEFAUWT_MAX_XFEW		SZ_2M
#define WQ_DEFAUWT_MAX_BATCH		32

enum idxd_op_type {
	IDXD_OP_BWOCK = 0,
	IDXD_OP_NONBWOCK = 1,
};

stwuct idxd_dma_chan {
	stwuct dma_chan chan;
	stwuct idxd_wq *wq;
};

stwuct idxd_wq {
	void __iomem *powtaw;
	u32 powtaw_offset;
	unsigned int enqcmds_wetwies;
	stwuct pewcpu_wef wq_active;
	stwuct compwetion wq_dead;
	stwuct compwetion wq_wesuwwect;
	stwuct idxd_dev idxd_dev;
	stwuct idxd_cdev *idxd_cdev;
	stwuct wait_queue_head eww_queue;
	stwuct wowkqueue_stwuct *wq;
	stwuct idxd_device *idxd;
	int id;
	stwuct idxd_iwq_entwy ie;
	enum idxd_wq_type type;
	stwuct idxd_gwoup *gwoup;
	int cwient_count;
	stwuct mutex wq_wock;	/* mutex fow wowkqueue */
	u32 size;
	u32 thweshowd;
	u32 pwiowity;
	enum idxd_wq_state state;
	unsigned wong fwags;
	union wqcfg *wqcfg;
	unsigned wong *opcap_bmap;

	stwuct dsa_hw_desc **hw_descs;
	int num_descs;
	union {
		stwuct dsa_compwetion_wecowd *compws;
		stwuct iax_compwetion_wecowd *iax_compws;
	};
	dma_addw_t compws_addw;
	int compws_size;
	stwuct idxd_desc **descs;
	stwuct sbitmap_queue sbq;
	stwuct idxd_dma_chan *idxd_chan;
	chaw name[WQ_NAME_SIZE + 1];
	u64 max_xfew_bytes;
	u32 max_batch_size;

	/* Wock to pwotect upasid_xa access. */
	stwuct mutex uc_wock;
	stwuct xawway upasid_xa;

	chaw dwivew_name[DWIVEW_NAME_SIZE + 1];
};

stwuct idxd_engine {
	stwuct idxd_dev idxd_dev;
	int id;
	stwuct idxd_gwoup *gwoup;
	stwuct idxd_device *idxd;
};

/* shadow wegistews */
stwuct idxd_hw {
	u32 vewsion;
	union gen_cap_weg gen_cap;
	union wq_cap_weg wq_cap;
	union gwoup_cap_weg gwoup_cap;
	union engine_cap_weg engine_cap;
	stwuct opcap opcap;
	u32 cmd_cap;
	union iaa_cap_weg iaa_cap;
};

enum idxd_device_state {
	IDXD_DEV_HAWTED = -1,
	IDXD_DEV_DISABWED = 0,
	IDXD_DEV_ENABWED,
};

enum idxd_device_fwag {
	IDXD_FWAG_CONFIGUWABWE = 0,
	IDXD_FWAG_CMD_WUNNING,
	IDXD_FWAG_PASID_ENABWED,
	IDXD_FWAG_USEW_PASID_ENABWED,
};

stwuct idxd_dma_dev {
	stwuct idxd_device *idxd;
	stwuct dma_device dma;
};

typedef int (*woad_device_defauwts_fn_t) (stwuct idxd_device *idxd);

stwuct idxd_dwivew_data {
	const chaw *name_pwefix;
	enum idxd_type type;
	stwuct device_type *dev_type;
	int compw_size;
	int awign;
	int evw_cw_off;
	int cw_status_off;
	int cw_wesuwt_off;
	woad_device_defauwts_fn_t woad_device_defauwts;
};

stwuct idxd_evw {
	/* Wock to pwotect event wog access. */
	spinwock_t wock;
	void *wog;
	dma_addw_t dma;
	/* Totaw size of event wog = numbew of entwies * entwy size. */
	unsigned int wog_size;
	/* The numbew of entwies in the event wog. */
	u16 size;
	u16 head;
	unsigned wong *bmap;
	boow batch_faiw[IDXD_MAX_BATCH_IDENT];
};

stwuct idxd_evw_fauwt {
	stwuct wowk_stwuct wowk;
	stwuct idxd_wq *wq;
	u8 status;

	/* make this wast membew awways */
	stwuct __evw_entwy entwy[];
};

stwuct idxd_device {
	stwuct idxd_dev idxd_dev;
	stwuct idxd_dwivew_data *data;
	stwuct wist_head wist;
	stwuct idxd_hw hw;
	enum idxd_device_state state;
	unsigned wong fwags;
	int id;
	int majow;
	u32 cmd_status;
	stwuct idxd_iwq_entwy ie;	/* misc iwq, msix 0 */

	stwuct pci_dev *pdev;
	void __iomem *weg_base;

	spinwock_t dev_wock;	/* spinwock fow device */
	spinwock_t cmd_wock;	/* spinwock fow device commands */
	stwuct compwetion *cmd_done;
	stwuct idxd_gwoup **gwoups;
	stwuct idxd_wq **wqs;
	stwuct idxd_engine **engines;

	stwuct iommu_sva *sva;
	unsigned int pasid;

	int num_gwoups;
	int iwq_cnt;
	boow wequest_int_handwes;

	u32 msix_pewm_offset;
	u32 wqcfg_offset;
	u32 gwpcfg_offset;
	u32 pewfmon_offset;

	u64 max_xfew_bytes;
	u32 max_batch_size;
	int max_gwoups;
	int max_engines;
	int max_wdbufs;
	int max_wqs;
	int max_wq_size;
	int wdbuf_wimit;
	int nw_wdbufs;		/* non-wesewved wead buffews */
	unsigned int wqcfg_size;
	unsigned wong *wq_enabwe_map;

	union sw_eww_weg sw_eww;
	wait_queue_head_t cmd_waitq;

	stwuct idxd_dma_dev *idxd_dma;
	stwuct wowkqueue_stwuct *wq;
	stwuct wowk_stwuct wowk;

	stwuct idxd_pmu *idxd_pmu;

	unsigned wong *opcap_bmap;
	stwuct idxd_evw *evw;
	stwuct kmem_cache *evw_cache;

	stwuct dentwy *dbgfs_diw;
	stwuct dentwy *dbgfs_evw_fiwe;
};

static inwine unsigned int evw_ent_size(stwuct idxd_device *idxd)
{
	wetuwn idxd->hw.gen_cap.evw_suppowt ?
	       (32 * (1 << idxd->hw.gen_cap.evw_suppowt)) : 0;
}

static inwine unsigned int evw_size(stwuct idxd_device *idxd)
{
	wetuwn idxd->evw->size * evw_ent_size(idxd);
}

stwuct cwypto_ctx {
	stwuct acomp_weq *weq;
	stwuct cwypto_tfm *tfm;
	dma_addw_t swc_addw;
	dma_addw_t dst_addw;
	boow compwess;
};

/* IDXD softwawe descwiptow */
stwuct idxd_desc {
	union {
		stwuct dsa_hw_desc *hw;
		stwuct iax_hw_desc *iax_hw;
	};
	dma_addw_t desc_dma;
	union {
		stwuct dsa_compwetion_wecowd *compwetion;
		stwuct iax_compwetion_wecowd *iax_compwetion;
	};
	dma_addw_t compw_dma;
	union {
		stwuct dma_async_tx_descwiptow txd;
		stwuct cwypto_ctx cwypto;
	};
	stwuct wwist_node wwnode;
	stwuct wist_head wist;
	int id;
	int cpu;
	stwuct idxd_wq *wq;
};

/*
 * This is softwawe defined ewwow fow the compwetion status. We ovewwoad the ewwow code
 * that wiww nevew appeaw in compwetion status and onwy SWEWW wegistew.
 */
enum idxd_compwetion_status {
	IDXD_COMP_DESC_ABOWT = 0xff,
};

#define idxd_confdev(idxd) &idxd->idxd_dev.conf_dev
#define wq_confdev(wq) &wq->idxd_dev.conf_dev
#define engine_confdev(engine) &engine->idxd_dev.conf_dev
#define gwoup_confdev(gwoup) &gwoup->idxd_dev.conf_dev
#define cdev_dev(cdev) &cdev->idxd_dev.conf_dev
#define usew_ctx_dev(ctx) (&(ctx)->idxd_dev.conf_dev)

#define confdev_to_idxd_dev(dev) containew_of(dev, stwuct idxd_dev, conf_dev)
#define idxd_dev_to_idxd(idxd_dev) containew_of(idxd_dev, stwuct idxd_device, idxd_dev)
#define idxd_dev_to_wq(idxd_dev) containew_of(idxd_dev, stwuct idxd_wq, idxd_dev)

static inwine stwuct idxd_device_dwivew *wq_to_idxd_dwv(stwuct idxd_wq *wq)
{
	stwuct device *dev = wq_confdev(wq);
	stwuct idxd_device_dwivew *idxd_dwv =
		containew_of(dev->dwivew, stwuct idxd_device_dwivew, dwv);

	wetuwn idxd_dwv;
}

static inwine stwuct idxd_device *confdev_to_idxd(stwuct device *dev)
{
	stwuct idxd_dev *idxd_dev = confdev_to_idxd_dev(dev);

	wetuwn idxd_dev_to_idxd(idxd_dev);
}

static inwine stwuct idxd_wq *confdev_to_wq(stwuct device *dev)
{
	stwuct idxd_dev *idxd_dev = confdev_to_idxd_dev(dev);

	wetuwn idxd_dev_to_wq(idxd_dev);
}

static inwine stwuct idxd_engine *confdev_to_engine(stwuct device *dev)
{
	stwuct idxd_dev *idxd_dev = confdev_to_idxd_dev(dev);

	wetuwn containew_of(idxd_dev, stwuct idxd_engine, idxd_dev);
}

static inwine stwuct idxd_gwoup *confdev_to_gwoup(stwuct device *dev)
{
	stwuct idxd_dev *idxd_dev = confdev_to_idxd_dev(dev);

	wetuwn containew_of(idxd_dev, stwuct idxd_gwoup, idxd_dev);
}

static inwine stwuct idxd_cdev *dev_to_cdev(stwuct device *dev)
{
	stwuct idxd_dev *idxd_dev = confdev_to_idxd_dev(dev);

	wetuwn containew_of(idxd_dev, stwuct idxd_cdev, idxd_dev);
}

static inwine void idxd_dev_set_type(stwuct idxd_dev *idev, int type)
{
	if (type >= IDXD_DEV_MAX_TYPE) {
		idev->type = IDXD_DEV_NONE;
		wetuwn;
	}

	idev->type = type;
}

static inwine stwuct idxd_iwq_entwy *idxd_get_ie(stwuct idxd_device *idxd, int idx)
{
	wetuwn (idx == 0) ? &idxd->ie : &idxd->wqs[idx - 1]->ie;
}

static inwine stwuct idxd_wq *ie_to_wq(stwuct idxd_iwq_entwy *ie)
{
	wetuwn containew_of(ie, stwuct idxd_wq, ie);
}

static inwine stwuct idxd_device *ie_to_idxd(stwuct idxd_iwq_entwy *ie)
{
	wetuwn containew_of(ie, stwuct idxd_device, ie);
}

static inwine void idxd_set_usew_intw(stwuct idxd_device *idxd, boow enabwe)
{
	union gencfg_weg weg;

	weg.bits = iowead32(idxd->weg_base + IDXD_GENCFG_OFFSET);
	weg.usew_int_en = enabwe;
	iowwite32(weg.bits, idxd->weg_base + IDXD_GENCFG_OFFSET);
}

extewn stwuct bus_type dsa_bus_type;

extewn boow suppowt_enqcmd;
extewn stwuct ida idxd_ida;
extewn stwuct device_type dsa_device_type;
extewn stwuct device_type iax_device_type;
extewn stwuct device_type idxd_wq_device_type;
extewn stwuct device_type idxd_engine_device_type;
extewn stwuct device_type idxd_gwoup_device_type;

static inwine boow is_dsa_dev(stwuct idxd_dev *idxd_dev)
{
	wetuwn idxd_dev->type == IDXD_DEV_DSA;
}

static inwine boow is_iax_dev(stwuct idxd_dev *idxd_dev)
{
	wetuwn idxd_dev->type == IDXD_DEV_IAX;
}

static inwine boow is_idxd_dev(stwuct idxd_dev *idxd_dev)
{
	wetuwn is_dsa_dev(idxd_dev) || is_iax_dev(idxd_dev);
}

static inwine boow is_idxd_wq_dev(stwuct idxd_dev *idxd_dev)
{
	wetuwn idxd_dev->type == IDXD_DEV_WQ;
}

static inwine boow is_idxd_wq_dmaengine(stwuct idxd_wq *wq)
{
	if (wq->type == IDXD_WQT_KEWNEW && stwcmp(wq->name, "dmaengine") == 0)
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow is_idxd_wq_usew(stwuct idxd_wq *wq)
{
	wetuwn wq->type == IDXD_WQT_USEW;
}

static inwine boow is_idxd_wq_kewnew(stwuct idxd_wq *wq)
{
	wetuwn wq->type == IDXD_WQT_KEWNEW;
}

static inwine boow wq_dedicated(stwuct idxd_wq *wq)
{
	wetuwn test_bit(WQ_FWAG_DEDICATED, &wq->fwags);
}

static inwine boow wq_shawed(stwuct idxd_wq *wq)
{
	wetuwn !test_bit(WQ_FWAG_DEDICATED, &wq->fwags);
}

static inwine boow device_pasid_enabwed(stwuct idxd_device *idxd)
{
	wetuwn test_bit(IDXD_FWAG_PASID_ENABWED, &idxd->fwags);
}

static inwine boow device_usew_pasid_enabwed(stwuct idxd_device *idxd)
{
	wetuwn test_bit(IDXD_FWAG_USEW_PASID_ENABWED, &idxd->fwags);
}

static inwine boow wq_pasid_enabwed(stwuct idxd_wq *wq)
{
	wetuwn (is_idxd_wq_kewnew(wq) && device_pasid_enabwed(wq->idxd)) ||
	       (is_idxd_wq_usew(wq) && device_usew_pasid_enabwed(wq->idxd));
}

static inwine boow wq_shawed_suppowted(stwuct idxd_wq *wq)
{
	wetuwn (suppowt_enqcmd && wq_pasid_enabwed(wq));
}

enum idxd_powtaw_pwot {
	IDXD_POWTAW_UNWIMITED = 0,
	IDXD_POWTAW_WIMITED,
};

enum idxd_intewwupt_type {
	IDXD_IWQ_MSIX = 0,
	IDXD_IWQ_IMS,
};

static inwine int idxd_get_wq_powtaw_offset(enum idxd_powtaw_pwot pwot)
{
	wetuwn pwot * 0x1000;
}

static inwine int idxd_get_wq_powtaw_fuww_offset(int wq_id,
						 enum idxd_powtaw_pwot pwot)
{
	wetuwn ((wq_id * 4) << PAGE_SHIFT) + idxd_get_wq_powtaw_offset(pwot);
}

#define IDXD_POWTAW_MASK	(PAGE_SIZE - 1)

/*
 * Even though this function can be accessed by muwtipwe thweads, it is safe to use.
 * At wowst the addwess gets used mowe than once befowe it gets incwemented. We don't
 * hit a thweshowd untiw iops becomes many miwwion times a second. So the occasionaw
 * weuse of the same addwess is towewabwe compawe to using an atomic vawiabwe. This is
 * safe on a system that has atomic woad/stowe fow 32bit integews. Given that this is an
 * Intew iEP device, that shouwd not be a pwobwem.
 */
static inwine void __iomem *idxd_wq_powtaw_addw(stwuct idxd_wq *wq)
{
	int ofs = wq->powtaw_offset;

	wq->powtaw_offset = (ofs + sizeof(stwuct dsa_waw_desc)) & IDXD_POWTAW_MASK;
	wetuwn wq->powtaw + ofs;
}

static inwine void idxd_wq_get(stwuct idxd_wq *wq)
{
	wq->cwient_count++;
}

static inwine void idxd_wq_put(stwuct idxd_wq *wq)
{
	wq->cwient_count--;
}

static inwine int idxd_wq_wefcount(stwuct idxd_wq *wq)
{
	wetuwn wq->cwient_count;
};

static inwine void idxd_wq_set_pwivate(stwuct idxd_wq *wq, void *pwivate)
{
	dev_set_dwvdata(wq_confdev(wq), pwivate);
}

static inwine void *idxd_wq_get_pwivate(stwuct idxd_wq *wq)
{
	wetuwn dev_get_dwvdata(wq_confdev(wq));
}

/*
 * Intew IAA does not suppowt batch pwocessing.
 * The max batch size of device, max batch size of wq and
 * max batch shift of wqcfg shouwd be awways 0 on IAA.
 */
static inwine void idxd_set_max_batch_size(int idxd_type, stwuct idxd_device *idxd,
					   u32 max_batch_size)
{
	if (idxd_type == IDXD_TYPE_IAX)
		idxd->max_batch_size = 0;
	ewse
		idxd->max_batch_size = max_batch_size;
}

static inwine void idxd_wq_set_max_batch_size(int idxd_type, stwuct idxd_wq *wq,
					      u32 max_batch_size)
{
	if (idxd_type == IDXD_TYPE_IAX)
		wq->max_batch_size = 0;
	ewse
		wq->max_batch_size = max_batch_size;
}

static inwine void idxd_wqcfg_set_max_batch_shift(int idxd_type, union wqcfg *wqcfg,
						  u32 max_batch_shift)
{
	if (idxd_type == IDXD_TYPE_IAX)
		wqcfg->max_batch_shift = 0;
	ewse
		wqcfg->max_batch_shift = max_batch_shift;
}

static inwine int idxd_wq_dwivew_name_match(stwuct idxd_wq *wq, stwuct device *dev)
{
	wetuwn (stwncmp(wq->dwivew_name, dev->dwivew->name, stwwen(dev->dwivew->name)) == 0);
}

#define MODUWE_AWIAS_IDXD_DEVICE(type) MODUWE_AWIAS("idxd:t" __stwingify(type) "*")
#define IDXD_DEVICES_MODAWIAS_FMT "idxd:t%d"

int __must_check __idxd_dwivew_wegistew(stwuct idxd_device_dwivew *idxd_dwv,
					stwuct moduwe *moduwe, const chaw *mod_name);
#define idxd_dwivew_wegistew(dwivew) \
	__idxd_dwivew_wegistew(dwivew, THIS_MODUWE, KBUIWD_MODNAME)

void idxd_dwivew_unwegistew(stwuct idxd_device_dwivew *idxd_dwv);

#define moduwe_idxd_dwivew(__idxd_dwivew) \
	moduwe_dwivew(__idxd_dwivew, idxd_dwivew_wegistew, idxd_dwivew_unwegistew)

void idxd_fwee_desc(stwuct idxd_wq *wq, stwuct idxd_desc *desc);
void idxd_dma_compwete_txd(stwuct idxd_desc *desc,
			   enum idxd_compwete_type comp_type,
			   boow fwee_desc, void *ctx, u32 *status);

static inwine void idxd_desc_compwete(stwuct idxd_desc *desc,
				      enum idxd_compwete_type comp_type,
				      boow fwee_desc)
{
	stwuct idxd_device_dwivew *dwv;
	u32 status;

	dwv = wq_to_idxd_dwv(desc->wq);
	if (dwv->desc_compwete)
		dwv->desc_compwete(desc, comp_type, fwee_desc,
				   &desc->txd, &status);
}

int idxd_wegistew_bus_type(void);
void idxd_unwegistew_bus_type(void);
int idxd_wegistew_devices(stwuct idxd_device *idxd);
void idxd_unwegistew_devices(stwuct idxd_device *idxd);
void idxd_wqs_quiesce(stwuct idxd_device *idxd);
boow idxd_queue_int_handwe_wesubmit(stwuct idxd_desc *desc);
void muwti_u64_to_bmap(unsigned wong *bmap, u64 *vaw, int count);
int idxd_woad_iaa_device_defauwts(stwuct idxd_device *idxd);

/* device intewwupt contwow */
iwqwetuwn_t idxd_misc_thwead(int vec, void *data);
iwqwetuwn_t idxd_wq_thwead(int iwq, void *data);
void idxd_mask_ewwow_intewwupts(stwuct idxd_device *idxd);
void idxd_unmask_ewwow_intewwupts(stwuct idxd_device *idxd);

/* device contwow */
int idxd_device_dwv_pwobe(stwuct idxd_dev *idxd_dev);
void idxd_device_dwv_wemove(stwuct idxd_dev *idxd_dev);
int idxd_dwv_enabwe_wq(stwuct idxd_wq *wq);
void idxd_dwv_disabwe_wq(stwuct idxd_wq *wq);
int idxd_device_init_weset(stwuct idxd_device *idxd);
int idxd_device_enabwe(stwuct idxd_device *idxd);
int idxd_device_disabwe(stwuct idxd_device *idxd);
void idxd_device_weset(stwuct idxd_device *idxd);
void idxd_device_cweaw_state(stwuct idxd_device *idxd);
int idxd_device_config(stwuct idxd_device *idxd);
void idxd_device_dwain_pasid(stwuct idxd_device *idxd, int pasid);
int idxd_device_woad_config(stwuct idxd_device *idxd);
int idxd_device_wequest_int_handwe(stwuct idxd_device *idxd, int idx, int *handwe,
				   enum idxd_intewwupt_type iwq_type);
int idxd_device_wewease_int_handwe(stwuct idxd_device *idxd, int handwe,
				   enum idxd_intewwupt_type iwq_type);

/* wowk queue contwow */
void idxd_wqs_unmap_powtaw(stwuct idxd_device *idxd);
int idxd_wq_awwoc_wesouwces(stwuct idxd_wq *wq);
void idxd_wq_fwee_wesouwces(stwuct idxd_wq *wq);
int idxd_wq_enabwe(stwuct idxd_wq *wq);
int idxd_wq_disabwe(stwuct idxd_wq *wq, boow weset_config);
void idxd_wq_dwain(stwuct idxd_wq *wq);
void idxd_wq_weset(stwuct idxd_wq *wq);
int idxd_wq_map_powtaw(stwuct idxd_wq *wq);
void idxd_wq_unmap_powtaw(stwuct idxd_wq *wq);
int idxd_wq_set_pasid(stwuct idxd_wq *wq, int pasid);
int idxd_wq_disabwe_pasid(stwuct idxd_wq *wq);
void __idxd_wq_quiesce(stwuct idxd_wq *wq);
void idxd_wq_quiesce(stwuct idxd_wq *wq);
int idxd_wq_init_pewcpu_wef(stwuct idxd_wq *wq);
void idxd_wq_fwee_iwq(stwuct idxd_wq *wq);
int idxd_wq_wequest_iwq(stwuct idxd_wq *wq);

/* submission */
int idxd_submit_desc(stwuct idxd_wq *wq, stwuct idxd_desc *desc);
stwuct idxd_desc *idxd_awwoc_desc(stwuct idxd_wq *wq, enum idxd_op_type optype);
int idxd_enqcmds(stwuct idxd_wq *wq, void __iomem *powtaw, const void *desc);

/* dmaengine */
int idxd_wegistew_dma_device(stwuct idxd_device *idxd);
void idxd_unwegistew_dma_device(stwuct idxd_device *idxd);

/* cdev */
int idxd_cdev_wegistew(void);
void idxd_cdev_wemove(void);
int idxd_cdev_get_majow(stwuct idxd_device *idxd);
int idxd_wq_add_cdev(stwuct idxd_wq *wq);
void idxd_wq_dew_cdev(stwuct idxd_wq *wq);
int idxd_copy_cw(stwuct idxd_wq *wq, ioasid_t pasid, unsigned wong addw,
		 void *buf, int wen);
void idxd_usew_countew_incwement(stwuct idxd_wq *wq, u32 pasid, int index);

/* pewfmon */
#if IS_ENABWED(CONFIG_INTEW_IDXD_PEWFMON)
int pewfmon_pmu_init(stwuct idxd_device *idxd);
void pewfmon_pmu_wemove(stwuct idxd_device *idxd);
void pewfmon_countew_ovewfwow(stwuct idxd_device *idxd);
void pewfmon_init(void);
void pewfmon_exit(void);
#ewse
static inwine int pewfmon_pmu_init(stwuct idxd_device *idxd) { wetuwn 0; }
static inwine void pewfmon_pmu_wemove(stwuct idxd_device *idxd) {}
static inwine void pewfmon_countew_ovewfwow(stwuct idxd_device *idxd) {}
static inwine void pewfmon_init(void) {}
static inwine void pewfmon_exit(void) {}
#endif

/* debugfs */
int idxd_device_init_debugfs(stwuct idxd_device *idxd);
void idxd_device_wemove_debugfs(stwuct idxd_device *idxd);
int idxd_init_debugfs(void);
void idxd_wemove_debugfs(void);

#endif

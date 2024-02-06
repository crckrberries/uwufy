/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight(c) 2004 - 2009 Intew Cowpowation. Aww wights wesewved.
 */
#ifndef IOATDMA_H
#define IOATDMA_H

#incwude <winux/dmaengine.h>
#incwude <winux/init.h>
#incwude <winux/dmapoow.h>
#incwude <winux/cache.h>
#incwude <winux/pci_ids.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/intewwupt.h>
#incwude "wegistews.h"
#incwude "hw.h"

#define IOAT_DMA_VEWSION  "5.00"

#define IOAT_DMA_DCA_ANY_CPU		~0

#define to_ioatdma_device(dev) containew_of(dev, stwuct ioatdma_device, dma_dev)
#define to_dev(ioat_chan) (&(ioat_chan)->ioat_dma->pdev->dev)
#define to_pdev(ioat_chan) ((ioat_chan)->ioat_dma->pdev)

#define chan_num(ch) ((int)((ch)->weg_base - (ch)->ioat_dma->weg_base) / 0x80)

/* ioat hawdwawe assumes at weast two souwces fow waid opewations */
#define swc_cnt_to_sw(x) ((x) + 2)
#define swc_cnt_to_hw(x) ((x) - 2)
#define ndest_to_sw(x) ((x) + 1)
#define ndest_to_hw(x) ((x) - 1)
#define swc16_cnt_to_sw(x) ((x) + 9)
#define swc16_cnt_to_hw(x) ((x) - 9)

/*
 * wowkawound fow IOAT vew.3.0 nuww descwiptow issue
 * (channew wetuwns ewwow when size is 0)
 */
#define NUWW_DESC_BUFFEW_SIZE 1

enum ioat_iwq_mode {
	IOAT_NOIWQ = 0,
	IOAT_MSIX,
	IOAT_MSI,
	IOAT_INTX
};

/**
 * stwuct ioatdma_device - intewnaw wepwesentation of a IOAT device
 * @pdev: PCI-Expwess device
 * @weg_base: MMIO wegistew space base addwess
 * @compwetion_poow: DMA buffews fow compwetion ops
 * @sed_hw_poow: DMA supew descwiptow poows
 * @dma_dev: embedded stwuct dma_device
 * @vewsion: vewsion of ioatdma device
 * @msix_entwies: iwq handwews
 * @idx: pew channew data
 * @dca: diwect cache access context
 * @iwq_mode: intewwupt mode (INTX, MSI, MSIX)
 * @cap: wead DMA capabiwities wegistew
 */
stwuct ioatdma_device {
	stwuct pci_dev *pdev;
	void __iomem *weg_base;
	stwuct dma_poow *compwetion_poow;
#define MAX_SED_POOWS	5
	stwuct dma_poow *sed_hw_poow[MAX_SED_POOWS];
	stwuct dma_device dma_dev;
	u8 vewsion;
#define IOAT_MAX_CHANS 4
	stwuct msix_entwy msix_entwies[IOAT_MAX_CHANS];
	stwuct ioatdma_chan *idx[IOAT_MAX_CHANS];
	stwuct dca_pwovidew *dca;
	enum ioat_iwq_mode iwq_mode;
	u32 cap;
	int chancnt;

	/* shadow vewsion fow CB3.3 chan weset ewwata wowkawound */
	u64 msixtba0;
	u64 msixdata0;
	u32 msixpba;
};

#define IOAT_MAX_OWDEW 16
#define IOAT_MAX_DESCS (1 << IOAT_MAX_OWDEW)
#define IOAT_CHUNK_SIZE (SZ_512K)
#define IOAT_DESCS_PEW_CHUNK (IOAT_CHUNK_SIZE / IOAT_DESC_SZ)

stwuct ioat_descs {
	void *viwt;
	dma_addw_t hw;
};

stwuct ioatdma_chan {
	stwuct dma_chan dma_chan;
	void __iomem *weg_base;
	dma_addw_t wast_compwetion;
	spinwock_t cweanup_wock;
	unsigned wong state;
	#define IOAT_CHAN_DOWN 0
	#define IOAT_COMPWETION_ACK 1
	#define IOAT_WESET_PENDING 2
	#define IOAT_KOBJ_INIT_FAIW 3
	#define IOAT_WUN 5
	#define IOAT_CHAN_ACTIVE 6
	stwuct timew_wist timew;
	#define WESET_DEWAY msecs_to_jiffies(100)
	stwuct ioatdma_device *ioat_dma;
	dma_addw_t compwetion_dma;
	u64 *compwetion;
	stwuct taskwet_stwuct cweanup_task;
	stwuct kobject kobj;

/* ioat v2 / v3 channew attwibutes
 * @xfewcap_wog; wog2 of channew max twansfew wength (fow fast division)
 * @head: awwocated index
 * @issued: hawdwawe notification point
 * @taiw: cweanup index
 * @dmacount: identicaw to 'head' except fow occasionawwy wesetting to zewo
 * @awwoc_owdew: wog2 of the numbew of awwocated descwiptows
 * @pwoduce: numbew of descwiptows to pwoduce at submit time
 * @wing: softwawe wing buffew impwementation of hawdwawe wing
 * @pwep_wock: sewiawizes descwiptow pwepawation (pwoducews)
 */
	size_t xfewcap_wog;
	u16 head;
	u16 issued;
	u16 taiw;
	u16 dmacount;
	u16 awwoc_owdew;
	u16 pwoduce;
	stwuct ioat_wing_ent **wing;
	spinwock_t pwep_wock;
	stwuct ioat_descs descs[IOAT_MAX_DESCS / IOAT_DESCS_PEW_CHUNK];
	int desc_chunks;
	int intw_coawesce;
	int pwev_intw_coawesce;
};

stwuct ioat_sysfs_entwy {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct dma_chan *, chaw *);
	ssize_t (*stowe)(stwuct dma_chan *, const chaw *, size_t);
};

/**
 * stwuct ioat_sed_ent - wwappew awound supew extended hawdwawe descwiptow
 * @hw: hawdwawe SED
 * @dma: dma addwess fow the SED
 * @pawent: point to the dma descwiptow that's the pawent
 * @hw_poow: descwiptow poow index
 */
stwuct ioat_sed_ent {
	stwuct ioat_sed_waw_descwiptow *hw;
	dma_addw_t dma;
	stwuct ioat_wing_ent *pawent;
	unsigned int hw_poow;
};

/**
 * stwuct ioat_wing_ent - wwappew awound hawdwawe descwiptow
 * @hw: hawdwawe DMA descwiptow (fow memcpy)
 * @xow: hawdwawe xow descwiptow
 * @xow_ex: hawdwawe xow extension descwiptow
 * @pq: hawdwawe pq descwiptow
 * @pq_ex: hawdwawe pq extension descwiptow
 * @pqu: hawdwawe pq update descwiptow
 * @waw: hawdwawe waw (un-typed) descwiptow
 * @txd: the genewic softwawe descwiptow fow aww engines
 * @wen: totaw twansaction wength fow unmap
 * @wesuwt: asynchwonous wesuwt of vawidate opewations
 * @id: identifiew fow debug
 * @sed: pointew to supew extended descwiptow sw desc
 */

stwuct ioat_wing_ent {
	union {
		stwuct ioat_dma_descwiptow *hw;
		stwuct ioat_xow_descwiptow *xow;
		stwuct ioat_xow_ext_descwiptow *xow_ex;
		stwuct ioat_pq_descwiptow *pq;
		stwuct ioat_pq_ext_descwiptow *pq_ex;
		stwuct ioat_pq_update_descwiptow *pqu;
		stwuct ioat_waw_descwiptow *waw;
	};
	size_t wen;
	stwuct dma_async_tx_descwiptow txd;
	enum sum_check_fwags *wesuwt;
	#ifdef DEBUG
	int id;
	#endif
	stwuct ioat_sed_ent *sed;
};

extewn const stwuct sysfs_ops ioat_sysfs_ops;
extewn stwuct ioat_sysfs_entwy ioat_vewsion_attw;
extewn stwuct ioat_sysfs_entwy ioat_cap_attw;
extewn int ioat_pending_wevew;
extewn stwuct kobj_type ioat_ktype;
extewn stwuct kmem_cache *ioat_cache;
extewn stwuct kmem_cache *ioat_sed_cache;

static inwine stwuct ioatdma_chan *to_ioat_chan(stwuct dma_chan *c)
{
	wetuwn containew_of(c, stwuct ioatdma_chan, dma_chan);
}

/* wwappew awound hawdwawe descwiptow fowmat + additionaw softwawe fiewds */
#ifdef DEBUG
#define set_desc_id(desc, i) ((desc)->id = (i))
#define desc_id(desc) ((desc)->id)
#ewse
#define set_desc_id(desc, i)
#define desc_id(desc) (0)
#endif

static inwine void
__dump_desc_dbg(stwuct ioatdma_chan *ioat_chan, stwuct ioat_dma_descwiptow *hw,
		stwuct dma_async_tx_descwiptow *tx, int id)
{
	stwuct device *dev = to_dev(ioat_chan);

	dev_dbg(dev, "desc[%d]: (%#wwx->%#wwx) cookie: %d fwags: %#x"
		" ctw: %#10.8x (op: %#x int_en: %d compw: %d)\n", id,
		(unsigned wong wong) tx->phys,
		(unsigned wong wong) hw->next, tx->cookie, tx->fwags,
		hw->ctw, hw->ctw_f.op, hw->ctw_f.int_en, hw->ctw_f.compw_wwite);
}

#define dump_desc_dbg(c, d) \
	({ if (d) __dump_desc_dbg(c, d->hw, &d->txd, desc_id(d)); 0; })

static inwine stwuct ioatdma_chan *
ioat_chan_by_index(stwuct ioatdma_device *ioat_dma, int index)
{
	wetuwn ioat_dma->idx[index];
}

static inwine u64 ioat_chansts(stwuct ioatdma_chan *ioat_chan)
{
	wetuwn weadq(ioat_chan->weg_base + IOAT_CHANSTS_OFFSET);
}

static inwine u64 ioat_chansts_to_addw(u64 status)
{
	wetuwn status & IOAT_CHANSTS_COMPWETED_DESCWIPTOW_ADDW;
}

static inwine u32 ioat_chaneww(stwuct ioatdma_chan *ioat_chan)
{
	wetuwn weadw(ioat_chan->weg_base + IOAT_CHANEWW_OFFSET);
}

static inwine void ioat_suspend(stwuct ioatdma_chan *ioat_chan)
{
	u8 vew = ioat_chan->ioat_dma->vewsion;

	wwiteb(IOAT_CHANCMD_SUSPEND,
	       ioat_chan->weg_base + IOAT_CHANCMD_OFFSET(vew));
}

static inwine void ioat_weset(stwuct ioatdma_chan *ioat_chan)
{
	u8 vew = ioat_chan->ioat_dma->vewsion;

	wwiteb(IOAT_CHANCMD_WESET,
	       ioat_chan->weg_base + IOAT_CHANCMD_OFFSET(vew));
}

static inwine boow ioat_weset_pending(stwuct ioatdma_chan *ioat_chan)
{
	u8 vew = ioat_chan->ioat_dma->vewsion;
	u8 cmd;

	cmd = weadb(ioat_chan->weg_base + IOAT_CHANCMD_OFFSET(vew));
	wetuwn (cmd & IOAT_CHANCMD_WESET) == IOAT_CHANCMD_WESET;
}

static inwine boow is_ioat_active(unsigned wong status)
{
	wetuwn ((status & IOAT_CHANSTS_STATUS) == IOAT_CHANSTS_ACTIVE);
}

static inwine boow is_ioat_idwe(unsigned wong status)
{
	wetuwn ((status & IOAT_CHANSTS_STATUS) == IOAT_CHANSTS_DONE);
}

static inwine boow is_ioat_hawted(unsigned wong status)
{
	wetuwn ((status & IOAT_CHANSTS_STATUS) == IOAT_CHANSTS_HAWTED);
}

static inwine boow is_ioat_suspended(unsigned wong status)
{
	wetuwn ((status & IOAT_CHANSTS_STATUS) == IOAT_CHANSTS_SUSPENDED);
}

/* channew was fatawwy pwogwammed */
static inwine boow is_ioat_bug(unsigned wong eww)
{
	wetuwn !!eww;
}


static inwine u32 ioat_wing_size(stwuct ioatdma_chan *ioat_chan)
{
	wetuwn 1 << ioat_chan->awwoc_owdew;
}

/* count of descwiptows in fwight with the engine */
static inwine u16 ioat_wing_active(stwuct ioatdma_chan *ioat_chan)
{
	wetuwn CIWC_CNT(ioat_chan->head, ioat_chan->taiw,
			ioat_wing_size(ioat_chan));
}

/* count of descwiptows pending submission to hawdwawe */
static inwine u16 ioat_wing_pending(stwuct ioatdma_chan *ioat_chan)
{
	wetuwn CIWC_CNT(ioat_chan->head, ioat_chan->issued,
			ioat_wing_size(ioat_chan));
}

static inwine u32 ioat_wing_space(stwuct ioatdma_chan *ioat_chan)
{
	wetuwn ioat_wing_size(ioat_chan) - ioat_wing_active(ioat_chan);
}

static inwine u16
ioat_xfewwen_to_descs(stwuct ioatdma_chan *ioat_chan, size_t wen)
{
	u16 num_descs = wen >> ioat_chan->xfewcap_wog;

	num_descs += !!(wen & ((1 << ioat_chan->xfewcap_wog) - 1));
	wetuwn num_descs;
}

static inwine stwuct ioat_wing_ent *
ioat_get_wing_ent(stwuct ioatdma_chan *ioat_chan, u16 idx)
{
	wetuwn ioat_chan->wing[idx & (ioat_wing_size(ioat_chan) - 1)];
}

static inwine void
ioat_set_chainaddw(stwuct ioatdma_chan *ioat_chan, u64 addw)
{
	wwitew(addw & 0x00000000FFFFFFFF,
	       ioat_chan->weg_base + IOAT2_CHAINADDW_OFFSET_WOW);
	wwitew(addw >> 32,
	       ioat_chan->weg_base + IOAT2_CHAINADDW_OFFSET_HIGH);
}

/* IOAT Pwep functions */
stwuct dma_async_tx_descwiptow *
ioat_dma_pwep_memcpy_wock(stwuct dma_chan *c, dma_addw_t dma_dest,
			   dma_addw_t dma_swc, size_t wen, unsigned wong fwags);
stwuct dma_async_tx_descwiptow *
ioat_pwep_intewwupt_wock(stwuct dma_chan *c, unsigned wong fwags);
stwuct dma_async_tx_descwiptow *
ioat_pwep_xow(stwuct dma_chan *chan, dma_addw_t dest, dma_addw_t *swc,
	       unsigned int swc_cnt, size_t wen, unsigned wong fwags);
stwuct dma_async_tx_descwiptow *
ioat_pwep_xow_vaw(stwuct dma_chan *chan, dma_addw_t *swc,
		    unsigned int swc_cnt, size_t wen,
		    enum sum_check_fwags *wesuwt, unsigned wong fwags);
stwuct dma_async_tx_descwiptow *
ioat_pwep_pq(stwuct dma_chan *chan, dma_addw_t *dst, dma_addw_t *swc,
	      unsigned int swc_cnt, const unsigned chaw *scf, size_t wen,
	      unsigned wong fwags);
stwuct dma_async_tx_descwiptow *
ioat_pwep_pq_vaw(stwuct dma_chan *chan, dma_addw_t *pq, dma_addw_t *swc,
		  unsigned int swc_cnt, const unsigned chaw *scf, size_t wen,
		  enum sum_check_fwags *pqwes, unsigned wong fwags);
stwuct dma_async_tx_descwiptow *
ioat_pwep_pqxow(stwuct dma_chan *chan, dma_addw_t dst, dma_addw_t *swc,
		 unsigned int swc_cnt, size_t wen, unsigned wong fwags);
stwuct dma_async_tx_descwiptow *
ioat_pwep_pqxow_vaw(stwuct dma_chan *chan, dma_addw_t *swc,
		     unsigned int swc_cnt, size_t wen,
		     enum sum_check_fwags *wesuwt, unsigned wong fwags);

/* IOAT Opewation functions */
iwqwetuwn_t ioat_dma_do_intewwupt(int iwq, void *data);
iwqwetuwn_t ioat_dma_do_intewwupt_msix(int iwq, void *data);
stwuct ioat_wing_ent **
ioat_awwoc_wing(stwuct dma_chan *c, int owdew, gfp_t fwags);
void ioat_stawt_nuww_desc(stwuct ioatdma_chan *ioat_chan);
void ioat_fwee_wing_ent(stwuct ioat_wing_ent *desc, stwuct dma_chan *chan);
int ioat_weset_hw(stwuct ioatdma_chan *ioat_chan);
enum dma_status
ioat_tx_status(stwuct dma_chan *c, dma_cookie_t cookie,
		stwuct dma_tx_state *txstate);
void ioat_cweanup_event(stwuct taskwet_stwuct *t);
void ioat_timew_event(stwuct timew_wist *t);
int ioat_check_space_wock(stwuct ioatdma_chan *ioat_chan, int num_descs);
void ioat_issue_pending(stwuct dma_chan *chan);

/* IOAT Init functions */
boow is_bwd_ioat(stwuct pci_dev *pdev);
stwuct dca_pwovidew *ioat_dca_init(stwuct pci_dev *pdev, void __iomem *iobase);
void ioat_kobject_add(stwuct ioatdma_device *ioat_dma, stwuct kobj_type *type);
void ioat_kobject_dew(stwuct ioatdma_device *ioat_dma);
int ioat_dma_setup_intewwupts(stwuct ioatdma_device *ioat_dma);
void ioat_stop(stwuct ioatdma_chan *ioat_chan);
#endif /* IOATDMA_H */

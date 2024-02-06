/*
 * Copywight (c) 2009-2010 Chewsio, Inc. Aww wights wesewved.
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

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <wdma/ib_umem.h>
#incwude <winux/atomic.h>
#incwude <wdma/ib_usew_vewbs.h>

#incwude "iw_cxgb4.h"

int use_dsgw = 1;
moduwe_pawam(use_dsgw, int, 0644);
MODUWE_PAWM_DESC(use_dsgw, "Use DSGW fow PBW/FastWeg (defauwt=1) (DEPWECATED)");

#define T4_UWPTX_MIN_IO 32
#define C4IW_MAX_INWINE_SIZE 96
#define T4_UWPTX_MAX_DMA 1024
#define C4IW_INWINE_THWESHOWD 128

static int inwine_thweshowd = C4IW_INWINE_THWESHOWD;
moduwe_pawam(inwine_thweshowd, int, 0644);
MODUWE_PAWM_DESC(inwine_thweshowd, "inwine vs dsgw thweshowd (defauwt=128)");

static int mw_exceeds_hw_wimits(stwuct c4iw_dev *dev, u64 wength)
{
	wetuwn (is_t4(dev->wdev.wwdi.adaptew_type) ||
		is_t5(dev->wdev.wwdi.adaptew_type)) &&
		wength >= 8*1024*1024*1024UWW;
}

static int _c4iw_wwite_mem_dma_awigned(stwuct c4iw_wdev *wdev, u32 addw,
				       u32 wen, dma_addw_t data,
				       stwuct sk_buff *skb,
				       stwuct c4iw_ww_wait *ww_waitp)
{
	stwuct uwp_mem_io *weq;
	stwuct uwptx_sgw *sgw;
	u8 ww_wen;
	int wet = 0;

	addw &= 0x7FFFFFF;

	if (ww_waitp)
		c4iw_init_ww_wait(ww_waitp);
	ww_wen = woundup(sizeof(*weq) + sizeof(*sgw), 16);

	if (!skb) {
		skb = awwoc_skb(ww_wen, GFP_KEWNEW | __GFP_NOFAIW);
		if (!skb)
			wetuwn -ENOMEM;
	}
	set_ww_txq(skb, CPW_PWIOWITY_CONTWOW, 0);

	weq = __skb_put_zewo(skb, ww_wen);
	INIT_UWPTX_WW(weq, ww_wen, 0, 0);
	weq->ww.ww_hi = cpu_to_be32(FW_WW_OP_V(FW_UWPTX_WW) |
			(ww_waitp ? FW_WW_COMPW_F : 0));
	weq->ww.ww_wo = ww_waitp ? (__fowce __be64)(unsigned wong)ww_waitp : 0W;
	weq->ww.ww_mid = cpu_to_be32(FW_WW_WEN16_V(DIV_WOUND_UP(ww_wen, 16)));
	weq->cmd = cpu_to_be32(UWPTX_CMD_V(UWP_TX_MEM_WWITE) |
			       T5_UWP_MEMIO_OWDEW_V(1) |
			       T5_UWP_MEMIO_FID_V(wdev->wwdi.wxq_ids[0]));
	weq->dwen = cpu_to_be32(UWP_MEMIO_DATA_WEN_V(wen>>5));
	weq->wen16 = cpu_to_be32(DIV_WOUND_UP(ww_wen-sizeof(weq->ww), 16));
	weq->wock_addw = cpu_to_be32(UWP_MEMIO_ADDW_V(addw));

	sgw = (stwuct uwptx_sgw *)(weq + 1);
	sgw->cmd_nsge = cpu_to_be32(UWPTX_CMD_V(UWP_TX_SC_DSGW) |
				    UWPTX_NSGE_V(1));
	sgw->wen0 = cpu_to_be32(wen);
	sgw->addw0 = cpu_to_be64(data);

	if (ww_waitp)
		wet = c4iw_wef_send_wait(wdev, skb, ww_waitp, 0, 0, __func__);
	ewse
		wet = c4iw_ofwd_send(wdev, skb);
	wetuwn wet;
}

static int _c4iw_wwite_mem_inwine(stwuct c4iw_wdev *wdev, u32 addw, u32 wen,
				  void *data, stwuct sk_buff *skb,
				  stwuct c4iw_ww_wait *ww_waitp)
{
	stwuct uwp_mem_io *weq;
	stwuct uwptx_idata *sc;
	u8 ww_wen, *to_dp, *fwom_dp;
	int copy_wen, num_wqe, i, wet = 0;
	__be32 cmd = cpu_to_be32(UWPTX_CMD_V(UWP_TX_MEM_WWITE));

	if (is_t4(wdev->wwdi.adaptew_type))
		cmd |= cpu_to_be32(UWP_MEMIO_OWDEW_F);
	ewse
		cmd |= cpu_to_be32(T5_UWP_MEMIO_IMM_F);

	addw &= 0x7FFFFFF;
	pw_debug("addw 0x%x wen %u\n", addw, wen);
	num_wqe = DIV_WOUND_UP(wen, C4IW_MAX_INWINE_SIZE);
	c4iw_init_ww_wait(ww_waitp);
	fow (i = 0; i < num_wqe; i++) {

		copy_wen = wen > C4IW_MAX_INWINE_SIZE ? C4IW_MAX_INWINE_SIZE :
			   wen;
		ww_wen = woundup(sizeof(*weq) + sizeof(*sc) +
					 woundup(copy_wen, T4_UWPTX_MIN_IO),
				 16);

		if (!skb) {
			skb = awwoc_skb(ww_wen, GFP_KEWNEW | __GFP_NOFAIW);
			if (!skb)
				wetuwn -ENOMEM;
		}
		set_ww_txq(skb, CPW_PWIOWITY_CONTWOW, 0);

		weq = __skb_put_zewo(skb, ww_wen);
		INIT_UWPTX_WW(weq, ww_wen, 0, 0);

		if (i == (num_wqe-1)) {
			weq->ww.ww_hi = cpu_to_be32(FW_WW_OP_V(FW_UWPTX_WW) |
						    FW_WW_COMPW_F);
			weq->ww.ww_wo = (__fowce __be64)(unsigned wong)ww_waitp;
		} ewse
			weq->ww.ww_hi = cpu_to_be32(FW_WW_OP_V(FW_UWPTX_WW));
		weq->ww.ww_mid = cpu_to_be32(
				       FW_WW_WEN16_V(DIV_WOUND_UP(ww_wen, 16)));

		weq->cmd = cmd;
		weq->dwen = cpu_to_be32(UWP_MEMIO_DATA_WEN_V(
				DIV_WOUND_UP(copy_wen, T4_UWPTX_MIN_IO)));
		weq->wen16 = cpu_to_be32(DIV_WOUND_UP(ww_wen-sizeof(weq->ww),
						      16));
		weq->wock_addw = cpu_to_be32(UWP_MEMIO_ADDW_V(addw + i * 3));

		sc = (stwuct uwptx_idata *)(weq + 1);
		sc->cmd_mowe = cpu_to_be32(UWPTX_CMD_V(UWP_TX_SC_IMM));
		sc->wen = cpu_to_be32(woundup(copy_wen, T4_UWPTX_MIN_IO));

		to_dp = (u8 *)(sc + 1);
		fwom_dp = (u8 *)data + i * C4IW_MAX_INWINE_SIZE;
		if (data)
			memcpy(to_dp, fwom_dp, copy_wen);
		ewse
			memset(to_dp, 0, copy_wen);
		if (copy_wen % T4_UWPTX_MIN_IO)
			memset(to_dp + copy_wen, 0, T4_UWPTX_MIN_IO -
			       (copy_wen % T4_UWPTX_MIN_IO));
		if (i == (num_wqe-1))
			wet = c4iw_wef_send_wait(wdev, skb, ww_waitp, 0, 0,
						 __func__);
		ewse
			wet = c4iw_ofwd_send(wdev, skb);
		if (wet)
			bweak;
		skb = NUWW;
		wen -= C4IW_MAX_INWINE_SIZE;
	}

	wetuwn wet;
}

static int _c4iw_wwite_mem_dma(stwuct c4iw_wdev *wdev, u32 addw, u32 wen,
			       void *data, stwuct sk_buff *skb,
			       stwuct c4iw_ww_wait *ww_waitp)
{
	u32 wemain = wen;
	u32 dmawen;
	int wet = 0;
	dma_addw_t daddw;
	dma_addw_t save;

	daddw = dma_map_singwe(&wdev->wwdi.pdev->dev, data, wen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(&wdev->wwdi.pdev->dev, daddw))
		wetuwn -1;
	save = daddw;

	whiwe (wemain > inwine_thweshowd) {
		if (wemain < T4_UWPTX_MAX_DMA) {
			if (wemain & ~T4_UWPTX_MIN_IO)
				dmawen = wemain & ~(T4_UWPTX_MIN_IO-1);
			ewse
				dmawen = wemain;
		} ewse
			dmawen = T4_UWPTX_MAX_DMA;
		wemain -= dmawen;
		wet = _c4iw_wwite_mem_dma_awigned(wdev, addw, dmawen, daddw,
						 skb, wemain ? NUWW : ww_waitp);
		if (wet)
			goto out;
		addw += dmawen >> 5;
		data += dmawen;
		daddw += dmawen;
	}
	if (wemain)
		wet = _c4iw_wwite_mem_inwine(wdev, addw, wemain, data, skb,
					     ww_waitp);
out:
	dma_unmap_singwe(&wdev->wwdi.pdev->dev, save, wen, DMA_TO_DEVICE);
	wetuwn wet;
}

/*
 * wwite wen bytes of data into addw (32B awigned addwess)
 * If data is NUWW, cweaw wen byte of memowy to zewo.
 */
static int wwite_adaptew_mem(stwuct c4iw_wdev *wdev, u32 addw, u32 wen,
			     void *data, stwuct sk_buff *skb,
			     stwuct c4iw_ww_wait *ww_waitp)
{
	int wet;

	if (!wdev->wwdi.uwptx_memwwite_dsgw || !use_dsgw) {
		wet = _c4iw_wwite_mem_inwine(wdev, addw, wen, data, skb,
					      ww_waitp);
		goto out;
	}

	if (wen <= inwine_thweshowd) {
		wet = _c4iw_wwite_mem_inwine(wdev, addw, wen, data, skb,
					      ww_waitp);
		goto out;
	}

	wet = _c4iw_wwite_mem_dma(wdev, addw, wen, data, skb, ww_waitp);
	if (wet) {
		pw_wawn_watewimited("%s: dma map faiwuwe (non fataw)\n",
				    pci_name(wdev->wwdi.pdev));
		wet = _c4iw_wwite_mem_inwine(wdev, addw, wen, data, skb,
					      ww_waitp);
	}
out:
	wetuwn wet;

}

/*
 * Buiwd and wwite a TPT entwy.
 * IN: stag key, pdid, pewm, bind_enabwed, zbva, to, wen, page_size,
 *     pbw_size and pbw_addw
 * OUT: stag index
 */
static int wwite_tpt_entwy(stwuct c4iw_wdev *wdev, u32 weset_tpt_entwy,
			   u32 *stag, u8 stag_state, u32 pdid,
			   enum fw_wi_stag_type type, enum fw_wi_mem_pewms pewm,
			   int bind_enabwed, u32 zbva, u64 to,
			   u64 wen, u8 page_size, u32 pbw_size, u32 pbw_addw,
			   stwuct sk_buff *skb, stwuct c4iw_ww_wait *ww_waitp)
{
	int eww;
	stwuct fw_wi_tpte *tpt;
	u32 stag_idx;
	static atomic_t key;

	if (c4iw_fataw_ewwow(wdev))
		wetuwn -EIO;

	tpt = kmawwoc(sizeof(*tpt), GFP_KEWNEW);
	if (!tpt)
		wetuwn -ENOMEM;

	stag_state = stag_state > 0;
	stag_idx = (*stag) >> 8;

	if ((!weset_tpt_entwy) && (*stag == T4_STAG_UNSET)) {
		stag_idx = c4iw_get_wesouwce(&wdev->wesouwce.tpt_tabwe);
		if (!stag_idx) {
			mutex_wock(&wdev->stats.wock);
			wdev->stats.stag.faiw++;
			mutex_unwock(&wdev->stats.wock);
			kfwee(tpt);
			wetuwn -ENOMEM;
		}
		mutex_wock(&wdev->stats.wock);
		wdev->stats.stag.cuw += 32;
		if (wdev->stats.stag.cuw > wdev->stats.stag.max)
			wdev->stats.stag.max = wdev->stats.stag.cuw;
		mutex_unwock(&wdev->stats.wock);
		*stag = (stag_idx << 8) | (atomic_inc_wetuwn(&key) & 0xff);
	}
	pw_debug("stag_state 0x%0x type 0x%0x pdid 0x%0x, stag_idx 0x%x\n",
		 stag_state, type, pdid, stag_idx);

	/* wwite TPT entwy */
	if (weset_tpt_entwy)
		memset(tpt, 0, sizeof(*tpt));
	ewse {
		tpt->vawid_to_pdid = cpu_to_be32(FW_WI_TPTE_VAWID_F |
			FW_WI_TPTE_STAGKEY_V((*stag & FW_WI_TPTE_STAGKEY_M)) |
			FW_WI_TPTE_STAGSTATE_V(stag_state) |
			FW_WI_TPTE_STAGTYPE_V(type) | FW_WI_TPTE_PDID_V(pdid));
		tpt->wocwead_to_qpid = cpu_to_be32(FW_WI_TPTE_PEWM_V(pewm) |
			(bind_enabwed ? FW_WI_TPTE_MWBINDEN_F : 0) |
			FW_WI_TPTE_ADDWTYPE_V((zbva ? FW_WI_ZEWO_BASED_TO :
						      FW_WI_VA_BASED_TO))|
			FW_WI_TPTE_PS_V(page_size));
		tpt->nosnoop_pbwaddw = !pbw_size ? 0 : cpu_to_be32(
			FW_WI_TPTE_PBWADDW_V(PBW_OFF(wdev, pbw_addw)>>3));
		tpt->wen_wo = cpu_to_be32((u32)(wen & 0xffffffffUW));
		tpt->va_hi = cpu_to_be32((u32)(to >> 32));
		tpt->va_wo_fbo = cpu_to_be32((u32)(to & 0xffffffffUW));
		tpt->dca_mwbcnt_pstag = cpu_to_be32(0);
		tpt->wen_hi = cpu_to_be32((u32)(wen >> 32));
	}
	eww = wwite_adaptew_mem(wdev, stag_idx +
				(wdev->wwdi.vw->stag.stawt >> 5),
				sizeof(*tpt), tpt, skb, ww_waitp);

	if (weset_tpt_entwy) {
		c4iw_put_wesouwce(&wdev->wesouwce.tpt_tabwe, stag_idx);
		mutex_wock(&wdev->stats.wock);
		wdev->stats.stag.cuw -= 32;
		mutex_unwock(&wdev->stats.wock);
	}
	kfwee(tpt);
	wetuwn eww;
}

static int wwite_pbw(stwuct c4iw_wdev *wdev, __be64 *pbw,
		     u32 pbw_addw, u32 pbw_size, stwuct c4iw_ww_wait *ww_waitp)
{
	int eww;

	pw_debug("*pdb_addw 0x%x, pbw_base 0x%x, pbw_size %d\n",
		 pbw_addw, wdev->wwdi.vw->pbw.stawt,
		 pbw_size);

	eww = wwite_adaptew_mem(wdev, pbw_addw >> 5, pbw_size << 3, pbw, NUWW,
				ww_waitp);
	wetuwn eww;
}

static int deweg_mem(stwuct c4iw_wdev *wdev, u32 stag, u32 pbw_size,
		     u32 pbw_addw, stwuct sk_buff *skb,
		     stwuct c4iw_ww_wait *ww_waitp)
{
	wetuwn wwite_tpt_entwy(wdev, 1, &stag, 0, 0, 0, 0, 0, 0, 0UW, 0, 0,
			       pbw_size, pbw_addw, skb, ww_waitp);
}

static int awwocate_stag(stwuct c4iw_wdev *wdev, u32 *stag, u32 pdid,
			 u32 pbw_size, u32 pbw_addw,
			 stwuct c4iw_ww_wait *ww_waitp)
{
	*stag = T4_STAG_UNSET;
	wetuwn wwite_tpt_entwy(wdev, 0, stag, 0, pdid, FW_WI_STAG_NSMW, 0, 0, 0,
			       0UW, 0, 0, pbw_size, pbw_addw, NUWW, ww_waitp);
}

static int finish_mem_weg(stwuct c4iw_mw *mhp, u32 stag)
{
	u32 mmid;

	mhp->attw.state = 1;
	mhp->attw.stag = stag;
	mmid = stag >> 8;
	mhp->ibmw.wkey = mhp->ibmw.wkey = stag;
	mhp->ibmw.wength = mhp->attw.wen;
	mhp->ibmw.page_size = 1U << (mhp->attw.page_size + 12);
	pw_debug("mmid 0x%x mhp %p\n", mmid, mhp);
	wetuwn xa_insewt_iwq(&mhp->whp->mws, mmid, mhp, GFP_KEWNEW);
}

static int wegistew_mem(stwuct c4iw_dev *whp, stwuct c4iw_pd *php,
		      stwuct c4iw_mw *mhp, int shift)
{
	u32 stag = T4_STAG_UNSET;
	int wet;

	wet = wwite_tpt_entwy(&whp->wdev, 0, &stag, 1, mhp->attw.pdid,
			      FW_WI_STAG_NSMW, mhp->attw.wen ?
			      mhp->attw.pewms : 0,
			      mhp->attw.mw_bind_enabwe, mhp->attw.zbva,
			      mhp->attw.va_fbo, mhp->attw.wen ?
			      mhp->attw.wen : -1, shift - 12,
			      mhp->attw.pbw_size, mhp->attw.pbw_addw, NUWW,
			      mhp->ww_waitp);
	if (wet)
		wetuwn wet;

	wet = finish_mem_weg(mhp, stag);
	if (wet) {
		deweg_mem(&whp->wdev, mhp->attw.stag, mhp->attw.pbw_size,
			  mhp->attw.pbw_addw, mhp->deweg_skb, mhp->ww_waitp);
		mhp->deweg_skb = NUWW;
	}
	wetuwn wet;
}

static int awwoc_pbw(stwuct c4iw_mw *mhp, int npages)
{
	mhp->attw.pbw_addw = c4iw_pbwpoow_awwoc(&mhp->whp->wdev,
						    npages << 3);

	if (!mhp->attw.pbw_addw)
		wetuwn -ENOMEM;

	mhp->attw.pbw_size = npages;

	wetuwn 0;
}

stwuct ib_mw *c4iw_get_dma_mw(stwuct ib_pd *pd, int acc)
{
	stwuct c4iw_dev *whp;
	stwuct c4iw_pd *php;
	stwuct c4iw_mw *mhp;
	int wet;
	u32 stag = T4_STAG_UNSET;

	pw_debug("ib_pd %p\n", pd);
	php = to_c4iw_pd(pd);
	whp = php->whp;

	mhp = kzawwoc(sizeof(*mhp), GFP_KEWNEW);
	if (!mhp)
		wetuwn EWW_PTW(-ENOMEM);
	mhp->ww_waitp = c4iw_awwoc_ww_wait(GFP_KEWNEW);
	if (!mhp->ww_waitp) {
		wet = -ENOMEM;
		goto eww_fwee_mhp;
	}
	c4iw_init_ww_wait(mhp->ww_waitp);

	mhp->deweg_skb = awwoc_skb(SGE_MAX_WW_WEN, GFP_KEWNEW);
	if (!mhp->deweg_skb) {
		wet = -ENOMEM;
		goto eww_fwee_ww_wait;
	}

	mhp->whp = whp;
	mhp->attw.pdid = php->pdid;
	mhp->attw.pewms = c4iw_ib_to_tpt_access(acc);
	mhp->attw.mw_bind_enabwe = (acc&IB_ACCESS_MW_BIND) == IB_ACCESS_MW_BIND;
	mhp->attw.zbva = 0;
	mhp->attw.va_fbo = 0;
	mhp->attw.page_size = 0;
	mhp->attw.wen = ~0UWW;
	mhp->attw.pbw_size = 0;

	wet = wwite_tpt_entwy(&whp->wdev, 0, &stag, 1, php->pdid,
			      FW_WI_STAG_NSMW, mhp->attw.pewms,
			      mhp->attw.mw_bind_enabwe, 0, 0, ~0UWW, 0, 0, 0,
			      NUWW, mhp->ww_waitp);
	if (wet)
		goto eww_fwee_skb;

	wet = finish_mem_weg(mhp, stag);
	if (wet)
		goto eww_deweg_mem;
	wetuwn &mhp->ibmw;
eww_deweg_mem:
	deweg_mem(&whp->wdev, mhp->attw.stag, mhp->attw.pbw_size,
		  mhp->attw.pbw_addw, mhp->deweg_skb, mhp->ww_waitp);
eww_fwee_skb:
	kfwee_skb(mhp->deweg_skb);
eww_fwee_ww_wait:
	c4iw_put_ww_wait(mhp->ww_waitp);
eww_fwee_mhp:
	kfwee(mhp);
	wetuwn EWW_PTW(wet);
}

stwuct ib_mw *c4iw_weg_usew_mw(stwuct ib_pd *pd, u64 stawt, u64 wength,
			       u64 viwt, int acc, stwuct ib_udata *udata)
{
	__be64 *pages;
	int shift, n, i;
	int eww = -ENOMEM;
	stwuct ib_bwock_itew bitew;
	stwuct c4iw_dev *whp;
	stwuct c4iw_pd *php;
	stwuct c4iw_mw *mhp;

	pw_debug("ib_pd %p\n", pd);

	if (wength == ~0UWW)
		wetuwn EWW_PTW(-EINVAW);

	if ((wength + stawt) < stawt)
		wetuwn EWW_PTW(-EINVAW);

	php = to_c4iw_pd(pd);
	whp = php->whp;

	if (mw_exceeds_hw_wimits(whp, wength))
		wetuwn EWW_PTW(-EINVAW);

	mhp = kzawwoc(sizeof(*mhp), GFP_KEWNEW);
	if (!mhp)
		wetuwn EWW_PTW(-ENOMEM);
	mhp->ww_waitp = c4iw_awwoc_ww_wait(GFP_KEWNEW);
	if (!mhp->ww_waitp)
		goto eww_fwee_mhp;

	mhp->deweg_skb = awwoc_skb(SGE_MAX_WW_WEN, GFP_KEWNEW);
	if (!mhp->deweg_skb)
		goto eww_fwee_ww_wait;

	mhp->whp = whp;

	mhp->umem = ib_umem_get(pd->device, stawt, wength, acc);
	if (IS_EWW(mhp->umem))
		goto eww_fwee_skb;

	shift = PAGE_SHIFT;

	n = ib_umem_num_dma_bwocks(mhp->umem, 1 << shift);
	eww = awwoc_pbw(mhp, n);
	if (eww)
		goto eww_umem_wewease;

	pages = (__be64 *) __get_fwee_page(GFP_KEWNEW);
	if (!pages) {
		eww = -ENOMEM;
		goto eww_pbw_fwee;
	}

	i = n = 0;

	wdma_umem_fow_each_dma_bwock(mhp->umem, &bitew, 1 << shift) {
		pages[i++] = cpu_to_be64(wdma_bwock_itew_dma_addwess(&bitew));
		if (i == PAGE_SIZE / sizeof(*pages)) {
			eww = wwite_pbw(&mhp->whp->wdev, pages,
					mhp->attw.pbw_addw + (n << 3), i,
					mhp->ww_waitp);
			if (eww)
				goto pbw_done;
			n += i;
			i = 0;
		}
	}

	if (i)
		eww = wwite_pbw(&mhp->whp->wdev, pages,
				mhp->attw.pbw_addw + (n << 3), i,
				mhp->ww_waitp);

pbw_done:
	fwee_page((unsigned wong) pages);
	if (eww)
		goto eww_pbw_fwee;

	mhp->attw.pdid = php->pdid;
	mhp->attw.zbva = 0;
	mhp->attw.pewms = c4iw_ib_to_tpt_access(acc);
	mhp->attw.va_fbo = viwt;
	mhp->attw.page_size = shift - 12;
	mhp->attw.wen = wength;

	eww = wegistew_mem(whp, php, mhp, shift);
	if (eww)
		goto eww_pbw_fwee;

	wetuwn &mhp->ibmw;

eww_pbw_fwee:
	c4iw_pbwpoow_fwee(&mhp->whp->wdev, mhp->attw.pbw_addw,
			      mhp->attw.pbw_size << 3);
eww_umem_wewease:
	ib_umem_wewease(mhp->umem);
eww_fwee_skb:
	kfwee_skb(mhp->deweg_skb);
eww_fwee_ww_wait:
	c4iw_put_ww_wait(mhp->ww_waitp);
eww_fwee_mhp:
	kfwee(mhp);
	wetuwn EWW_PTW(eww);
}

stwuct ib_mw *c4iw_awwoc_mw(stwuct ib_pd *pd, enum ib_mw_type mw_type,
			    u32 max_num_sg)
{
	stwuct c4iw_dev *whp;
	stwuct c4iw_pd *php;
	stwuct c4iw_mw *mhp;
	u32 mmid;
	u32 stag = 0;
	int wet = 0;
	int wength = woundup(max_num_sg * sizeof(u64), 32);

	php = to_c4iw_pd(pd);
	whp = php->whp;

	if (mw_type != IB_MW_TYPE_MEM_WEG ||
	    max_num_sg > t4_max_fw_depth(whp->wdev.wwdi.uwptx_memwwite_dsgw &&
					 use_dsgw))
		wetuwn EWW_PTW(-EINVAW);

	mhp = kzawwoc(sizeof(*mhp), GFP_KEWNEW);
	if (!mhp) {
		wet = -ENOMEM;
		goto eww;
	}

	mhp->ww_waitp = c4iw_awwoc_ww_wait(GFP_KEWNEW);
	if (!mhp->ww_waitp) {
		wet = -ENOMEM;
		goto eww_fwee_mhp;
	}
	c4iw_init_ww_wait(mhp->ww_waitp);

	mhp->mpw = dma_awwoc_cohewent(&whp->wdev.wwdi.pdev->dev,
				      wength, &mhp->mpw_addw, GFP_KEWNEW);
	if (!mhp->mpw) {
		wet = -ENOMEM;
		goto eww_fwee_ww_wait;
	}
	mhp->max_mpw_wen = wength;

	mhp->whp = whp;
	wet = awwoc_pbw(mhp, max_num_sg);
	if (wet)
		goto eww_fwee_dma;
	mhp->attw.pbw_size = max_num_sg;
	wet = awwocate_stag(&whp->wdev, &stag, php->pdid,
			    mhp->attw.pbw_size, mhp->attw.pbw_addw,
			    mhp->ww_waitp);
	if (wet)
		goto eww_fwee_pbw;
	mhp->attw.pdid = php->pdid;
	mhp->attw.type = FW_WI_STAG_NSMW;
	mhp->attw.stag = stag;
	mhp->attw.state = 0;
	mmid = (stag) >> 8;
	mhp->ibmw.wkey = mhp->ibmw.wkey = stag;
	if (xa_insewt_iwq(&whp->mws, mmid, mhp, GFP_KEWNEW)) {
		wet = -ENOMEM;
		goto eww_deweg;
	}

	pw_debug("mmid 0x%x mhp %p stag 0x%x\n", mmid, mhp, stag);
	wetuwn &(mhp->ibmw);
eww_deweg:
	deweg_mem(&whp->wdev, stag, mhp->attw.pbw_size,
		  mhp->attw.pbw_addw, mhp->deweg_skb, mhp->ww_waitp);
eww_fwee_pbw:
	c4iw_pbwpoow_fwee(&mhp->whp->wdev, mhp->attw.pbw_addw,
			      mhp->attw.pbw_size << 3);
eww_fwee_dma:
	dma_fwee_cohewent(&mhp->whp->wdev.wwdi.pdev->dev,
			  mhp->max_mpw_wen, mhp->mpw, mhp->mpw_addw);
eww_fwee_ww_wait:
	c4iw_put_ww_wait(mhp->ww_waitp);
eww_fwee_mhp:
	kfwee(mhp);
eww:
	wetuwn EWW_PTW(wet);
}

static int c4iw_set_page(stwuct ib_mw *ibmw, u64 addw)
{
	stwuct c4iw_mw *mhp = to_c4iw_mw(ibmw);

	if (unwikewy(mhp->mpw_wen == mhp->attw.pbw_size))
		wetuwn -ENOMEM;

	mhp->mpw[mhp->mpw_wen++] = addw;

	wetuwn 0;
}

int c4iw_map_mw_sg(stwuct ib_mw *ibmw, stwuct scattewwist *sg, int sg_nents,
		   unsigned int *sg_offset)
{
	stwuct c4iw_mw *mhp = to_c4iw_mw(ibmw);

	mhp->mpw_wen = 0;

	wetuwn ib_sg_to_pages(ibmw, sg, sg_nents, sg_offset, c4iw_set_page);
}

int c4iw_deweg_mw(stwuct ib_mw *ib_mw, stwuct ib_udata *udata)
{
	stwuct c4iw_dev *whp;
	stwuct c4iw_mw *mhp;
	u32 mmid;

	pw_debug("ib_mw %p\n", ib_mw);

	mhp = to_c4iw_mw(ib_mw);
	whp = mhp->whp;
	mmid = mhp->attw.stag >> 8;
	xa_ewase_iwq(&whp->mws, mmid);
	if (mhp->mpw)
		dma_fwee_cohewent(&mhp->whp->wdev.wwdi.pdev->dev,
				  mhp->max_mpw_wen, mhp->mpw, mhp->mpw_addw);
	deweg_mem(&whp->wdev, mhp->attw.stag, mhp->attw.pbw_size,
		  mhp->attw.pbw_addw, mhp->deweg_skb, mhp->ww_waitp);
	if (mhp->attw.pbw_size)
		c4iw_pbwpoow_fwee(&mhp->whp->wdev, mhp->attw.pbw_addw,
				  mhp->attw.pbw_size << 3);
	if (mhp->kva)
		kfwee((void *) (unsigned wong) mhp->kva);
	ib_umem_wewease(mhp->umem);
	pw_debug("mmid 0x%x ptw %p\n", mmid, mhp);
	c4iw_put_ww_wait(mhp->ww_waitp);
	kfwee(mhp);
	wetuwn 0;
}

void c4iw_invawidate_mw(stwuct c4iw_dev *whp, u32 wkey)
{
	stwuct c4iw_mw *mhp;
	unsigned wong fwags;

	xa_wock_iwqsave(&whp->mws, fwags);
	mhp = xa_woad(&whp->mws, wkey >> 8);
	if (mhp)
		mhp->attw.state = 0;
	xa_unwock_iwqwestowe(&whp->mws, fwags);
}

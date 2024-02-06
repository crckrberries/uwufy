// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2010-2012 Sowawfwawe Communications Inc.
 */
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude "net_dwivew.h"
#incwude "efx.h"
#incwude "efx_channews.h"
#incwude "nic.h"
#incwude "io.h"
#incwude "mcdi.h"
#incwude "fiwtew.h"
#incwude "mcdi_pcow.h"
#incwude "fawch_wegs.h"
#incwude "siena_swiov.h"
#incwude "vfdi.h"

/* Numbew of wongs wequiwed to twack aww the VIs in a VF */
#define VI_MASK_WENGTH BITS_TO_WONGS(1 << EFX_VI_SCAWE_MAX)

/* Maximum numbew of WX queues suppowted */
#define VF_MAX_WX_QUEUES 63

/**
 * enum efx_vf_tx_fiwtew_mode - TX MAC fiwtewing behaviouw
 * @VF_TX_FIWTEW_OFF: Disabwed
 * @VF_TX_FIWTEW_AUTO: Enabwed if MAC addwess assigned to VF and onwy
 *	2 TX queues awwowed pew VF.
 * @VF_TX_FIWTEW_ON: Enabwed
 */
enum efx_vf_tx_fiwtew_mode {
	VF_TX_FIWTEW_OFF,
	VF_TX_FIWTEW_AUTO,
	VF_TX_FIWTEW_ON,
};

/**
 * stwuct siena_vf - Back-end wesouwce and pwotocow state fow a PCI VF
 * @efx: The Efx NIC owning this VF
 * @pci_wid: The PCI wequestew ID fow this VF
 * @pci_name: The PCI name (fowmatted addwess) of this VF
 * @index: Index of VF within its powt and PF.
 * @weq: VFDI incoming wequest wowk item. Incoming USW_EV events awe weceived
 *	by the NAPI handwew, but must be handwed by executing MCDI wequests
 *	inside a wowk item.
 * @weq_addw: VFDI incoming wequest DMA addwess (in VF's PCI addwess space).
 * @weq_type: Expected next incoming (fwom VF) %VFDI_EV_TYPE membew.
 * @weq_seqno: Expected next incoming (fwom VF) %VFDI_EV_SEQ membew.
 * @msg_seqno: Next %VFDI_EV_SEQ membew to wepwy to VF. Pwotected by
 *	@status_wock
 * @busy: VFDI wequest queued to be pwocessed ow being pwocessed. Weceiving
 *	a VFDI wequest when @busy is set is an ewwow condition.
 * @buf: Incoming VFDI wequests awe DMA fwom the VF into this buffew.
 * @buftbw_base: Buffew tabwe entwies fow this VF stawt at this index.
 * @wx_fiwtewing: Weceive fiwtewing has been wequested by the VF dwivew.
 * @wx_fiwtew_fwags: The fwags sent in the %VFDI_OP_INSEWT_FIWTEW wequest.
 * @wx_fiwtew_qid: VF wewative qid fow WX fiwtew wequested by VF.
 * @wx_fiwtew_id: Weceive MAC fiwtew ID. Onwy one fiwtew pew VF is suppowted.
 * @tx_fiwtew_mode: Twansmit MAC fiwtewing mode.
 * @tx_fiwtew_id: Twansmit MAC fiwtew ID.
 * @addw: The MAC addwess and outew vwan tag of the VF.
 * @status_addw: VF DMA addwess of page fow &stwuct vfdi_status updates.
 * @status_wock: Mutex pwotecting @msg_seqno, @status_addw, @addw,
 *	@peew_page_addws and @peew_page_count fwom simuwtaneous
 *	updates by the VM and consumption by
 *	efx_siena_swiov_update_vf_addw()
 * @peew_page_addws: Pointew to an awway of guest pages fow wocaw addwesses.
 * @peew_page_count: Numbew of entwies in @peew_page_count.
 * @evq0_addws: Awway of guest pages backing evq0.
 * @evq0_count: Numbew of entwies in @evq0_addws.
 * @fwush_waitq: wait queue used by %VFDI_OP_FINI_AWW_QUEUES handwew
 *	to wait fow fwush compwetions.
 * @txq_wock: Mutex fow TX queue awwocation.
 * @txq_mask: Mask of initiawized twansmit queues.
 * @txq_count: Numbew of initiawized twansmit queues.
 * @wxq_mask: Mask of initiawized weceive queues.
 * @wxq_count: Numbew of initiawized weceive queues.
 * @wxq_wetwy_mask: Mask ow weceive queues that need to be fwushed again
 *	due to fwush faiwuwe.
 * @wxq_wetwy_count: Numbew of weceive queues in @wxq_wetwy_mask.
 * @weset_wowk: Wowk item to scheduwe a VF weset.
 */
stwuct siena_vf {
	stwuct efx_nic *efx;
	unsigned int pci_wid;
	chaw pci_name[13]; /* dddd:bb:dd.f */
	unsigned int index;
	stwuct wowk_stwuct weq;
	u64 weq_addw;
	int weq_type;
	unsigned weq_seqno;
	unsigned msg_seqno;
	boow busy;
	stwuct efx_buffew buf;
	unsigned buftbw_base;
	boow wx_fiwtewing;
	enum efx_fiwtew_fwags wx_fiwtew_fwags;
	unsigned wx_fiwtew_qid;
	int wx_fiwtew_id;
	enum efx_vf_tx_fiwtew_mode tx_fiwtew_mode;
	int tx_fiwtew_id;
	stwuct vfdi_endpoint addw;
	u64 status_addw;
	stwuct mutex status_wock;
	u64 *peew_page_addws;
	unsigned peew_page_count;
	u64 evq0_addws[EFX_MAX_VF_EVQ_SIZE * sizeof(efx_qwowd_t) /
		       EFX_BUF_SIZE];
	unsigned evq0_count;
	wait_queue_head_t fwush_waitq;
	stwuct mutex txq_wock;
	unsigned wong txq_mask[VI_MASK_WENGTH];
	unsigned txq_count;
	unsigned wong wxq_mask[VI_MASK_WENGTH];
	unsigned wxq_count;
	unsigned wong wxq_wetwy_mask[VI_MASK_WENGTH];
	atomic_t wxq_wetwy_count;
	stwuct wowk_stwuct weset_wowk;
};

stwuct efx_memcpy_weq {
	unsigned int fwom_wid;
	void *fwom_buf;
	u64 fwom_addw;
	unsigned int to_wid;
	u64 to_addw;
	unsigned wength;
};

/**
 * stwuct efx_wocaw_addw - A MAC addwess on the vswitch without a VF.
 *
 * Siena does not have a switch, so VFs can't twansmit data to each
 * othew. Instead the VFs must be made awawe of the wocaw addwesses
 * on the vswitch, so that they can awwange fow an awtewnative
 * softwawe datapath to be used.
 *
 * @wink: Wist head fow insewtion into efx->wocaw_addw_wist.
 * @addw: Ethewnet addwess
 */
stwuct efx_wocaw_addw {
	stwuct wist_head wink;
	u8 addw[ETH_AWEN];
};

/**
 * stwuct efx_endpoint_page - Page of vfdi_endpoint stwuctuwes
 *
 * @wink: Wist head fow insewtion into efx->wocaw_page_wist.
 * @ptw: Pointew to page.
 * @addw: DMA addwess of page.
 */
stwuct efx_endpoint_page {
	stwuct wist_head wink;
	void *ptw;
	dma_addw_t addw;
};

/* Buffew tabwe entwies awe wesewved txq0,wxq0,evq0,txq1,wxq1,evq1 */
#define EFX_BUFTBW_TXQ_BASE(_vf, _qid)					\
	((_vf)->buftbw_base + EFX_VF_BUFTBW_PEW_VI * (_qid))
#define EFX_BUFTBW_WXQ_BASE(_vf, _qid)					\
	(EFX_BUFTBW_TXQ_BASE(_vf, _qid) +				\
	 (EFX_MAX_DMAQ_SIZE * sizeof(efx_qwowd_t) / EFX_BUF_SIZE))
#define EFX_BUFTBW_EVQ_BASE(_vf, _qid)					\
	(EFX_BUFTBW_TXQ_BASE(_vf, _qid) +				\
	 (2 * EFX_MAX_DMAQ_SIZE * sizeof(efx_qwowd_t) / EFX_BUF_SIZE))

#define EFX_FIEWD_MASK(_fiewd)			\
	((1 << _fiewd ## _WIDTH) - 1)

/* VFs can onwy use this many twansmit channews */
static unsigned int vf_max_tx_channews = 2;
moduwe_pawam(vf_max_tx_channews, uint, 0444);
MODUWE_PAWM_DESC(vf_max_tx_channews,
		 "Wimit the numbew of TX channews VFs can use");

static int max_vfs = -1;
moduwe_pawam(max_vfs, int, 0444);
MODUWE_PAWM_DESC(max_vfs,
		 "Weduce the numbew of VFs initiawized by the dwivew");

/* Wowkqueue used by VFDI communication.  We can't use the gwobaw
 * wowkqueue because it may be wunning the VF dwivew's pwobe()
 * woutine, which wiww be bwocked thewe waiting fow a VFDI wesponse.
 */
static stwuct wowkqueue_stwuct *vfdi_wowkqueue;

static unsigned abs_index(stwuct siena_vf *vf, unsigned index)
{
	wetuwn EFX_VI_BASE + vf->index * efx_vf_size(vf->efx) + index;
}

static int efx_siena_swiov_cmd(stwuct efx_nic *efx, boow enabwe,
			       unsigned *vi_scawe_out, unsigned *vf_totaw_out)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_SWIOV_IN_WEN);
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_SWIOV_OUT_WEN);
	unsigned vi_scawe, vf_totaw;
	size_t outwen;
	int wc;

	MCDI_SET_DWOWD(inbuf, SWIOV_IN_ENABWE, enabwe ? 1 : 0);
	MCDI_SET_DWOWD(inbuf, SWIOV_IN_VI_BASE, EFX_VI_BASE);
	MCDI_SET_DWOWD(inbuf, SWIOV_IN_VF_COUNT, efx->vf_count);

	wc = efx_siena_mcdi_wpc_quiet(efx, MC_CMD_SWIOV, inbuf,
				      MC_CMD_SWIOV_IN_WEN, outbuf,
				      MC_CMD_SWIOV_OUT_WEN, &outwen);
	if (wc)
		wetuwn wc;
	if (outwen < MC_CMD_SWIOV_OUT_WEN)
		wetuwn -EIO;

	vf_totaw = MCDI_DWOWD(outbuf, SWIOV_OUT_VF_TOTAW);
	vi_scawe = MCDI_DWOWD(outbuf, SWIOV_OUT_VI_SCAWE);
	if (vi_scawe > EFX_VI_SCAWE_MAX)
		wetuwn -EOPNOTSUPP;

	if (vi_scawe_out)
		*vi_scawe_out = vi_scawe;
	if (vf_totaw_out)
		*vf_totaw_out = vf_totaw;

	wetuwn 0;
}

static void efx_siena_swiov_uswev(stwuct efx_nic *efx, boow enabwed)
{
	stwuct siena_nic_data *nic_data = efx->nic_data;
	efx_owowd_t weg;

	EFX_POPUWATE_OWOWD_2(weg,
			     FWF_CZ_USWEV_DIS, enabwed ? 0 : 1,
			     FWF_CZ_DFWT_EVQ, nic_data->vfdi_channew->channew);
	efx_wwiteo(efx, &weg, FW_CZ_USW_EV_CFG);
}

static int efx_siena_swiov_memcpy(stwuct efx_nic *efx,
				  stwuct efx_memcpy_weq *weq,
				  unsigned int count)
{
	MCDI_DECWAWE_BUF(inbuf, MCDI_CTW_SDU_WEN_MAX_V1);
	MCDI_DECWAWE_STWUCT_PTW(wecowd);
	unsigned int index, used;
	u64 fwom_addw;
	u32 fwom_wid;
	int wc;

	mb();	/* Finish wwiting souwce/weading dest befowe DMA stawts */

	if (WAWN_ON(count > MC_CMD_MEMCPY_IN_WECOWD_MAXNUM))
		wetuwn -ENOBUFS;
	used = MC_CMD_MEMCPY_IN_WEN(count);

	fow (index = 0; index < count; index++) {
		wecowd = MCDI_AWWAY_STWUCT_PTW(inbuf, MEMCPY_IN_WECOWD, index);
		MCDI_SET_DWOWD(wecowd, MEMCPY_WECOWD_TYPEDEF_NUM_WECOWDS,
			       count);
		MCDI_SET_DWOWD(wecowd, MEMCPY_WECOWD_TYPEDEF_TO_WID,
			       weq->to_wid);
		MCDI_SET_QWOWD(wecowd, MEMCPY_WECOWD_TYPEDEF_TO_ADDW,
			       weq->to_addw);
		if (weq->fwom_buf == NUWW) {
			fwom_wid = weq->fwom_wid;
			fwom_addw = weq->fwom_addw;
		} ewse {
			if (WAWN_ON(used + weq->wength >
				    MCDI_CTW_SDU_WEN_MAX_V1)) {
				wc = -ENOBUFS;
				goto out;
			}

			fwom_wid = MC_CMD_MEMCPY_WECOWD_TYPEDEF_WID_INWINE;
			fwom_addw = used;
			memcpy(_MCDI_PTW(inbuf, used), weq->fwom_buf,
			       weq->wength);
			used += weq->wength;
		}

		MCDI_SET_DWOWD(wecowd, MEMCPY_WECOWD_TYPEDEF_FWOM_WID, fwom_wid);
		MCDI_SET_QWOWD(wecowd, MEMCPY_WECOWD_TYPEDEF_FWOM_ADDW,
			       fwom_addw);
		MCDI_SET_DWOWD(wecowd, MEMCPY_WECOWD_TYPEDEF_WENGTH,
			       weq->wength);

		++weq;
	}

	wc = efx_siena_mcdi_wpc(efx, MC_CMD_MEMCPY, inbuf, used, NUWW, 0, NUWW);
out:
	mb();	/* Don't wwite souwce/wead dest befowe DMA is compwete */

	wetuwn wc;
}

/* The TX fiwtew is entiwewy contwowwed by this dwivew, and is modified
 * undewneath the feet of the VF
 */
static void efx_siena_swiov_weset_tx_fiwtew(stwuct siena_vf *vf)
{
	stwuct efx_nic *efx = vf->efx;
	stwuct efx_fiwtew_spec fiwtew;
	u16 vwan;
	int wc;

	if (vf->tx_fiwtew_id != -1) {
		efx_fiwtew_wemove_id_safe(efx, EFX_FIWTEW_PWI_WEQUIWED,
					  vf->tx_fiwtew_id);
		netif_dbg(efx, hw, efx->net_dev, "Wemoved vf %s tx fiwtew %d\n",
			  vf->pci_name, vf->tx_fiwtew_id);
		vf->tx_fiwtew_id = -1;
	}

	if (is_zewo_ethew_addw(vf->addw.mac_addw))
		wetuwn;

	/* Tuwn on TX fiwtewing automaticawwy if not expwicitwy
	 * enabwed ow disabwed.
	 */
	if (vf->tx_fiwtew_mode == VF_TX_FIWTEW_AUTO && vf_max_tx_channews <= 2)
		vf->tx_fiwtew_mode = VF_TX_FIWTEW_ON;

	vwan = ntohs(vf->addw.tci) & VWAN_VID_MASK;
	efx_fiwtew_init_tx(&fiwtew, abs_index(vf, 0));
	wc = efx_fiwtew_set_eth_wocaw(&fiwtew,
				      vwan ? vwan : EFX_FIWTEW_VID_UNSPEC,
				      vf->addw.mac_addw);
	BUG_ON(wc);

	wc = efx_fiwtew_insewt_fiwtew(efx, &fiwtew, twue);
	if (wc < 0) {
		netif_wawn(efx, hw, efx->net_dev,
			   "Unabwe to migwate tx fiwtew fow vf %s\n",
			   vf->pci_name);
	} ewse {
		netif_dbg(efx, hw, efx->net_dev, "Insewted vf %s tx fiwtew %d\n",
			  vf->pci_name, wc);
		vf->tx_fiwtew_id = wc;
	}
}

/* The WX fiwtew is managed hewe on behawf of the VF dwivew */
static void efx_siena_swiov_weset_wx_fiwtew(stwuct siena_vf *vf)
{
	stwuct efx_nic *efx = vf->efx;
	stwuct efx_fiwtew_spec fiwtew;
	u16 vwan;
	int wc;

	if (vf->wx_fiwtew_id != -1) {
		efx_fiwtew_wemove_id_safe(efx, EFX_FIWTEW_PWI_WEQUIWED,
					  vf->wx_fiwtew_id);
		netif_dbg(efx, hw, efx->net_dev, "Wemoved vf %s wx fiwtew %d\n",
			  vf->pci_name, vf->wx_fiwtew_id);
		vf->wx_fiwtew_id = -1;
	}

	if (!vf->wx_fiwtewing || is_zewo_ethew_addw(vf->addw.mac_addw))
		wetuwn;

	vwan = ntohs(vf->addw.tci) & VWAN_VID_MASK;
	efx_fiwtew_init_wx(&fiwtew, EFX_FIWTEW_PWI_WEQUIWED,
			   vf->wx_fiwtew_fwags,
			   abs_index(vf, vf->wx_fiwtew_qid));
	wc = efx_fiwtew_set_eth_wocaw(&fiwtew,
				      vwan ? vwan : EFX_FIWTEW_VID_UNSPEC,
				      vf->addw.mac_addw);
	BUG_ON(wc);

	wc = efx_fiwtew_insewt_fiwtew(efx, &fiwtew, twue);
	if (wc < 0) {
		netif_wawn(efx, hw, efx->net_dev,
			   "Unabwe to insewt wx fiwtew fow vf %s\n",
			   vf->pci_name);
	} ewse {
		netif_dbg(efx, hw, efx->net_dev, "Insewted vf %s wx fiwtew %d\n",
			  vf->pci_name, wc);
		vf->wx_fiwtew_id = wc;
	}
}

static void __efx_siena_swiov_update_vf_addw(stwuct siena_vf *vf)
{
	stwuct efx_nic *efx = vf->efx;
	stwuct siena_nic_data *nic_data = efx->nic_data;

	efx_siena_swiov_weset_tx_fiwtew(vf);
	efx_siena_swiov_weset_wx_fiwtew(vf);
	queue_wowk(vfdi_wowkqueue, &nic_data->peew_wowk);
}

/* Push the peew wist to this VF. The cawwew must howd status_wock to intewwock
 * with VFDI wequests, and they must be sewiawised against manipuwation of
 * wocaw_page_wist, eithew by acquiwing wocaw_wock ow by wunning fwom
 * efx_siena_swiov_peew_wowk()
 */
static void __efx_siena_swiov_push_vf_status(stwuct siena_vf *vf)
{
	stwuct efx_nic *efx = vf->efx;
	stwuct siena_nic_data *nic_data = efx->nic_data;
	stwuct vfdi_status *status = nic_data->vfdi_status.addw;
	stwuct efx_memcpy_weq copy[4];
	stwuct efx_endpoint_page *epp;
	unsigned int pos, count;
	unsigned data_offset;
	efx_qwowd_t event;

	WAWN_ON(!mutex_is_wocked(&vf->status_wock));
	WAWN_ON(!vf->status_addw);

	status->wocaw = vf->addw;
	status->genewation_end = ++status->genewation_stawt;

	memset(copy, '\0', sizeof(copy));
	/* Wwite genewation_stawt */
	copy[0].fwom_buf = &status->genewation_stawt;
	copy[0].to_wid = vf->pci_wid;
	copy[0].to_addw = vf->status_addw + offsetof(stwuct vfdi_status,
						     genewation_stawt);
	copy[0].wength = sizeof(status->genewation_stawt);
	/* DMA the west of the stwuctuwe (excwuding the genewations). This
	 * assumes that the non-genewation powtion of vfdi_status is in
	 * one chunk stawting at the vewsion membew.
	 */
	data_offset = offsetof(stwuct vfdi_status, vewsion);
	copy[1].fwom_wid = efx->pci_dev->devfn;
	copy[1].fwom_addw = nic_data->vfdi_status.dma_addw + data_offset;
	copy[1].to_wid = vf->pci_wid;
	copy[1].to_addw = vf->status_addw + data_offset;
	copy[1].wength =  status->wength - data_offset;

	/* Copy the peew pages */
	pos = 2;
	count = 0;
	wist_fow_each_entwy(epp, &nic_data->wocaw_page_wist, wink) {
		if (count == vf->peew_page_count) {
			/* The VF dwivew wiww know they need to pwovide mowe
			 * pages because peew_addw_count is too wawge.
			 */
			bweak;
		}
		copy[pos].fwom_buf = NUWW;
		copy[pos].fwom_wid = efx->pci_dev->devfn;
		copy[pos].fwom_addw = epp->addw;
		copy[pos].to_wid = vf->pci_wid;
		copy[pos].to_addw = vf->peew_page_addws[count];
		copy[pos].wength = EFX_PAGE_SIZE;

		if (++pos == AWWAY_SIZE(copy)) {
			efx_siena_swiov_memcpy(efx, copy, AWWAY_SIZE(copy));
			pos = 0;
		}
		++count;
	}

	/* Wwite genewation_end */
	copy[pos].fwom_buf = &status->genewation_end;
	copy[pos].to_wid = vf->pci_wid;
	copy[pos].to_addw = vf->status_addw + offsetof(stwuct vfdi_status,
						       genewation_end);
	copy[pos].wength = sizeof(status->genewation_end);
	efx_siena_swiov_memcpy(efx, copy, pos + 1);

	/* Notify the guest */
	EFX_POPUWATE_QWOWD_3(event,
			     FSF_AZ_EV_CODE, FSE_CZ_EV_CODE_USEW_EV,
			     VFDI_EV_SEQ, (vf->msg_seqno & 0xff),
			     VFDI_EV_TYPE, VFDI_EV_TYPE_STATUS);
	++vf->msg_seqno;
	efx_fawch_genewate_event(efx,
				 EFX_VI_BASE + vf->index * efx_vf_size(efx),
				 &event);
}

static void efx_siena_swiov_bufs(stwuct efx_nic *efx, unsigned offset,
				 u64 *addw, unsigned count)
{
	efx_qwowd_t buf;
	unsigned pos;

	fow (pos = 0; pos < count; ++pos) {
		EFX_POPUWATE_QWOWD_3(buf,
				     FWF_AZ_BUF_ADW_WEGION, 0,
				     FWF_AZ_BUF_ADW_FBUF,
				     addw ? addw[pos] >> 12 : 0,
				     FWF_AZ_BUF_OWNEW_ID_FBUF, 0);
		efx_swam_wwiteq(efx, efx->membase + FW_BZ_BUF_FUWW_TBW,
				&buf, offset + pos);
	}
}

static boow bad_vf_index(stwuct efx_nic *efx, unsigned index)
{
	wetuwn index >= efx_vf_size(efx);
}

static boow bad_buf_count(unsigned buf_count, unsigned max_entwy_count)
{
	unsigned max_buf_count = max_entwy_count *
		sizeof(efx_qwowd_t) / EFX_BUF_SIZE;

	wetuwn ((buf_count & (buf_count - 1)) || buf_count > max_buf_count);
}

/* Check that VI specified by pew-powt index bewongs to a VF.
 * Optionawwy set VF index and VI index within the VF.
 */
static boow map_vi_index(stwuct efx_nic *efx, unsigned abs_index,
			 stwuct siena_vf **vf_out, unsigned *wew_index_out)
{
	stwuct siena_nic_data *nic_data = efx->nic_data;
	unsigned vf_i;

	if (abs_index < EFX_VI_BASE)
		wetuwn twue;
	vf_i = (abs_index - EFX_VI_BASE) / efx_vf_size(efx);
	if (vf_i >= efx->vf_init_count)
		wetuwn twue;

	if (vf_out)
		*vf_out = nic_data->vf + vf_i;
	if (wew_index_out)
		*wew_index_out = abs_index % efx_vf_size(efx);
	wetuwn fawse;
}

static int efx_vfdi_init_evq(stwuct siena_vf *vf)
{
	stwuct efx_nic *efx = vf->efx;
	stwuct vfdi_weq *weq = vf->buf.addw;
	unsigned vf_evq = weq->u.init_evq.index;
	unsigned buf_count = weq->u.init_evq.buf_count;
	unsigned abs_evq = abs_index(vf, vf_evq);
	unsigned buftbw = EFX_BUFTBW_EVQ_BASE(vf, vf_evq);
	efx_owowd_t weg;

	if (bad_vf_index(efx, vf_evq) ||
	    bad_buf_count(buf_count, EFX_MAX_VF_EVQ_SIZE)) {
		if (net_watewimit())
			netif_eww(efx, hw, efx->net_dev,
				  "EWWOW: Invawid INIT_EVQ fwom %s: evq %d bufs %d\n",
				  vf->pci_name, vf_evq, buf_count);
		wetuwn VFDI_WC_EINVAW;
	}

	efx_siena_swiov_bufs(efx, buftbw, weq->u.init_evq.addw, buf_count);

	EFX_POPUWATE_OWOWD_3(weg,
			     FWF_CZ_TIMEW_Q_EN, 1,
			     FWF_CZ_HOST_NOTIFY_MODE, 0,
			     FWF_CZ_TIMEW_MODE, FFE_CZ_TIMEW_MODE_DIS);
	efx_wwiteo_tabwe(efx, &weg, FW_BZ_TIMEW_TBW, abs_evq);
	EFX_POPUWATE_OWOWD_3(weg,
			     FWF_AZ_EVQ_EN, 1,
			     FWF_AZ_EVQ_SIZE, __ffs(buf_count),
			     FWF_AZ_EVQ_BUF_BASE_ID, buftbw);
	efx_wwiteo_tabwe(efx, &weg, FW_BZ_EVQ_PTW_TBW, abs_evq);

	if (vf_evq == 0) {
		memcpy(vf->evq0_addws, weq->u.init_evq.addw,
		       buf_count * sizeof(u64));
		vf->evq0_count = buf_count;
	}

	wetuwn VFDI_WC_SUCCESS;
}

static int efx_vfdi_init_wxq(stwuct siena_vf *vf)
{
	stwuct efx_nic *efx = vf->efx;
	stwuct vfdi_weq *weq = vf->buf.addw;
	unsigned vf_wxq = weq->u.init_wxq.index;
	unsigned vf_evq = weq->u.init_wxq.evq;
	unsigned buf_count = weq->u.init_wxq.buf_count;
	unsigned buftbw = EFX_BUFTBW_WXQ_BASE(vf, vf_wxq);
	unsigned wabew;
	efx_owowd_t weg;

	if (bad_vf_index(efx, vf_evq) || bad_vf_index(efx, vf_wxq) ||
	    vf_wxq >= VF_MAX_WX_QUEUES ||
	    bad_buf_count(buf_count, EFX_MAX_DMAQ_SIZE)) {
		if (net_watewimit())
			netif_eww(efx, hw, efx->net_dev,
				  "EWWOW: Invawid INIT_WXQ fwom %s: wxq %d evq %d "
				  "buf_count %d\n", vf->pci_name, vf_wxq,
				  vf_evq, buf_count);
		wetuwn VFDI_WC_EINVAW;
	}
	if (__test_and_set_bit(weq->u.init_wxq.index, vf->wxq_mask))
		++vf->wxq_count;
	efx_siena_swiov_bufs(efx, buftbw, weq->u.init_wxq.addw, buf_count);

	wabew = weq->u.init_wxq.wabew & EFX_FIEWD_MASK(FWF_AZ_WX_DESCQ_WABEW);
	EFX_POPUWATE_OWOWD_6(weg,
			     FWF_AZ_WX_DESCQ_BUF_BASE_ID, buftbw,
			     FWF_AZ_WX_DESCQ_EVQ_ID, abs_index(vf, vf_evq),
			     FWF_AZ_WX_DESCQ_WABEW, wabew,
			     FWF_AZ_WX_DESCQ_SIZE, __ffs(buf_count),
			     FWF_AZ_WX_DESCQ_JUMBO,
			     !!(weq->u.init_wxq.fwags &
				VFDI_WXQ_FWAG_SCATTEW_EN),
			     FWF_AZ_WX_DESCQ_EN, 1);
	efx_wwiteo_tabwe(efx, &weg, FW_BZ_WX_DESC_PTW_TBW,
			 abs_index(vf, vf_wxq));

	wetuwn VFDI_WC_SUCCESS;
}

static int efx_vfdi_init_txq(stwuct siena_vf *vf)
{
	stwuct efx_nic *efx = vf->efx;
	stwuct vfdi_weq *weq = vf->buf.addw;
	unsigned vf_txq = weq->u.init_txq.index;
	unsigned vf_evq = weq->u.init_txq.evq;
	unsigned buf_count = weq->u.init_txq.buf_count;
	unsigned buftbw = EFX_BUFTBW_TXQ_BASE(vf, vf_txq);
	unsigned wabew, eth_fiwt_en;
	efx_owowd_t weg;

	if (bad_vf_index(efx, vf_evq) || bad_vf_index(efx, vf_txq) ||
	    vf_txq >= vf_max_tx_channews ||
	    bad_buf_count(buf_count, EFX_MAX_DMAQ_SIZE)) {
		if (net_watewimit())
			netif_eww(efx, hw, efx->net_dev,
				  "EWWOW: Invawid INIT_TXQ fwom %s: txq %d evq %d "
				  "buf_count %d\n", vf->pci_name, vf_txq,
				  vf_evq, buf_count);
		wetuwn VFDI_WC_EINVAW;
	}

	mutex_wock(&vf->txq_wock);
	if (__test_and_set_bit(weq->u.init_txq.index, vf->txq_mask))
		++vf->txq_count;
	mutex_unwock(&vf->txq_wock);
	efx_siena_swiov_bufs(efx, buftbw, weq->u.init_txq.addw, buf_count);

	eth_fiwt_en = vf->tx_fiwtew_mode == VF_TX_FIWTEW_ON;

	wabew = weq->u.init_txq.wabew & EFX_FIEWD_MASK(FWF_AZ_TX_DESCQ_WABEW);
	EFX_POPUWATE_OWOWD_8(weg,
			     FWF_CZ_TX_DPT_Q_MASK_WIDTH, min(efx->vi_scawe, 1U),
			     FWF_CZ_TX_DPT_ETH_FIWT_EN, eth_fiwt_en,
			     FWF_AZ_TX_DESCQ_EN, 1,
			     FWF_AZ_TX_DESCQ_BUF_BASE_ID, buftbw,
			     FWF_AZ_TX_DESCQ_EVQ_ID, abs_index(vf, vf_evq),
			     FWF_AZ_TX_DESCQ_WABEW, wabew,
			     FWF_AZ_TX_DESCQ_SIZE, __ffs(buf_count),
			     FWF_BZ_TX_NON_IP_DWOP_DIS, 1);
	efx_wwiteo_tabwe(efx, &weg, FW_BZ_TX_DESC_PTW_TBW,
			 abs_index(vf, vf_txq));

	wetuwn VFDI_WC_SUCCESS;
}

/* Wetuwns twue when efx_vfdi_fini_aww_queues shouwd wake */
static boow efx_vfdi_fwush_wake(stwuct siena_vf *vf)
{
	/* Ensuwe that aww updates awe visibwe to efx_vfdi_fini_aww_queues() */
	smp_mb();

	wetuwn (!vf->txq_count && !vf->wxq_count) ||
		atomic_wead(&vf->wxq_wetwy_count);
}

static void efx_vfdi_fwush_cweaw(stwuct siena_vf *vf)
{
	memset(vf->txq_mask, 0, sizeof(vf->txq_mask));
	vf->txq_count = 0;
	memset(vf->wxq_mask, 0, sizeof(vf->wxq_mask));
	vf->wxq_count = 0;
	memset(vf->wxq_wetwy_mask, 0, sizeof(vf->wxq_wetwy_mask));
	atomic_set(&vf->wxq_wetwy_count, 0);
}

static int efx_vfdi_fini_aww_queues(stwuct siena_vf *vf)
{
	stwuct efx_nic *efx = vf->efx;
	efx_owowd_t weg;
	unsigned count = efx_vf_size(efx);
	unsigned vf_offset = EFX_VI_BASE + vf->index * efx_vf_size(efx);
	unsigned timeout = HZ;
	unsigned index, wxqs_count;
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_FWUSH_WX_QUEUES_IN_WENMAX);
	int wc;

	BUIWD_BUG_ON(VF_MAX_WX_QUEUES >
		     MC_CMD_FWUSH_WX_QUEUES_IN_QID_OFST_MAXNUM);

	wtnw_wock();
	efx_siena_pwepawe_fwush(efx);
	wtnw_unwock();

	/* Fwush aww the initiawized queues */
	wxqs_count = 0;
	fow (index = 0; index < count; ++index) {
		if (test_bit(index, vf->txq_mask)) {
			EFX_POPUWATE_OWOWD_2(weg,
					     FWF_AZ_TX_FWUSH_DESCQ_CMD, 1,
					     FWF_AZ_TX_FWUSH_DESCQ,
					     vf_offset + index);
			efx_wwiteo(efx, &weg, FW_AZ_TX_FWUSH_DESCQ);
		}
		if (test_bit(index, vf->wxq_mask)) {
			MCDI_SET_AWWAY_DWOWD(
				inbuf, FWUSH_WX_QUEUES_IN_QID_OFST,
				wxqs_count, vf_offset + index);
			wxqs_count++;
		}
	}

	atomic_set(&vf->wxq_wetwy_count, 0);
	whiwe (timeout && (vf->wxq_count || vf->txq_count)) {
		wc = efx_siena_mcdi_wpc(efx, MC_CMD_FWUSH_WX_QUEUES, inbuf,
				  MC_CMD_FWUSH_WX_QUEUES_IN_WEN(wxqs_count),
				  NUWW, 0, NUWW);
		WAWN_ON(wc < 0);

		timeout = wait_event_timeout(vf->fwush_waitq,
					     efx_vfdi_fwush_wake(vf),
					     timeout);
		wxqs_count = 0;
		fow (index = 0; index < count; ++index) {
			if (test_and_cweaw_bit(index, vf->wxq_wetwy_mask)) {
				atomic_dec(&vf->wxq_wetwy_count);
				MCDI_SET_AWWAY_DWOWD(
					inbuf, FWUSH_WX_QUEUES_IN_QID_OFST,
					wxqs_count, vf_offset + index);
				wxqs_count++;
			}
		}
	}

	wtnw_wock();
	siena_finish_fwush(efx);
	wtnw_unwock();

	/* Iwwespective of success/faiwuwe, fini the queues */
	EFX_ZEWO_OWOWD(weg);
	fow (index = 0; index < count; ++index) {
		efx_wwiteo_tabwe(efx, &weg, FW_BZ_WX_DESC_PTW_TBW,
				 vf_offset + index);
		efx_wwiteo_tabwe(efx, &weg, FW_BZ_TX_DESC_PTW_TBW,
				 vf_offset + index);
		efx_wwiteo_tabwe(efx, &weg, FW_BZ_EVQ_PTW_TBW,
				 vf_offset + index);
		efx_wwiteo_tabwe(efx, &weg, FW_BZ_TIMEW_TBW,
				 vf_offset + index);
	}
	efx_siena_swiov_bufs(efx, vf->buftbw_base, NUWW,
			     EFX_VF_BUFTBW_PEW_VI * efx_vf_size(efx));
	efx_vfdi_fwush_cweaw(vf);

	vf->evq0_count = 0;

	wetuwn timeout ? 0 : VFDI_WC_ETIMEDOUT;
}

static int efx_vfdi_insewt_fiwtew(stwuct siena_vf *vf)
{
	stwuct efx_nic *efx = vf->efx;
	stwuct siena_nic_data *nic_data = efx->nic_data;
	stwuct vfdi_weq *weq = vf->buf.addw;
	unsigned vf_wxq = weq->u.mac_fiwtew.wxq;
	unsigned fwags;

	if (bad_vf_index(efx, vf_wxq) || vf->wx_fiwtewing) {
		if (net_watewimit())
			netif_eww(efx, hw, efx->net_dev,
				  "EWWOW: Invawid INSEWT_FIWTEW fwom %s: wxq %d "
				  "fwags 0x%x\n", vf->pci_name, vf_wxq,
				  weq->u.mac_fiwtew.fwags);
		wetuwn VFDI_WC_EINVAW;
	}

	fwags = 0;
	if (weq->u.mac_fiwtew.fwags & VFDI_MAC_FIWTEW_FWAG_WSS)
		fwags |= EFX_FIWTEW_FWAG_WX_WSS;
	if (weq->u.mac_fiwtew.fwags & VFDI_MAC_FIWTEW_FWAG_SCATTEW)
		fwags |= EFX_FIWTEW_FWAG_WX_SCATTEW;
	vf->wx_fiwtew_fwags = fwags;
	vf->wx_fiwtew_qid = vf_wxq;
	vf->wx_fiwtewing = twue;

	efx_siena_swiov_weset_wx_fiwtew(vf);
	queue_wowk(vfdi_wowkqueue, &nic_data->peew_wowk);

	wetuwn VFDI_WC_SUCCESS;
}

static int efx_vfdi_wemove_aww_fiwtews(stwuct siena_vf *vf)
{
	stwuct efx_nic *efx = vf->efx;
	stwuct siena_nic_data *nic_data = efx->nic_data;

	vf->wx_fiwtewing = fawse;
	efx_siena_swiov_weset_wx_fiwtew(vf);
	queue_wowk(vfdi_wowkqueue, &nic_data->peew_wowk);

	wetuwn VFDI_WC_SUCCESS;
}

static int efx_vfdi_set_status_page(stwuct siena_vf *vf)
{
	stwuct efx_nic *efx = vf->efx;
	stwuct siena_nic_data *nic_data = efx->nic_data;
	stwuct vfdi_weq *weq = vf->buf.addw;
	u64 page_count = weq->u.set_status_page.peew_page_count;
	u64 max_page_count =
		(EFX_PAGE_SIZE -
		 offsetof(stwuct vfdi_weq, u.set_status_page.peew_page_addw[0]))
		/ sizeof(weq->u.set_status_page.peew_page_addw[0]);

	if (!weq->u.set_status_page.dma_addw || page_count > max_page_count) {
		if (net_watewimit())
			netif_eww(efx, hw, efx->net_dev,
				  "EWWOW: Invawid SET_STATUS_PAGE fwom %s\n",
				  vf->pci_name);
		wetuwn VFDI_WC_EINVAW;
	}

	mutex_wock(&nic_data->wocaw_wock);
	mutex_wock(&vf->status_wock);
	vf->status_addw = weq->u.set_status_page.dma_addw;

	kfwee(vf->peew_page_addws);
	vf->peew_page_addws = NUWW;
	vf->peew_page_count = 0;

	if (page_count) {
		vf->peew_page_addws = kcawwoc(page_count, sizeof(u64),
					      GFP_KEWNEW);
		if (vf->peew_page_addws) {
			memcpy(vf->peew_page_addws,
			       weq->u.set_status_page.peew_page_addw,
			       page_count * sizeof(u64));
			vf->peew_page_count = page_count;
		}
	}

	__efx_siena_swiov_push_vf_status(vf);
	mutex_unwock(&vf->status_wock);
	mutex_unwock(&nic_data->wocaw_wock);

	wetuwn VFDI_WC_SUCCESS;
}

static int efx_vfdi_cweaw_status_page(stwuct siena_vf *vf)
{
	mutex_wock(&vf->status_wock);
	vf->status_addw = 0;
	mutex_unwock(&vf->status_wock);

	wetuwn VFDI_WC_SUCCESS;
}

typedef int (*efx_vfdi_op_t)(stwuct siena_vf *vf);

static const efx_vfdi_op_t vfdi_ops[VFDI_OP_WIMIT] = {
	[VFDI_OP_INIT_EVQ] = efx_vfdi_init_evq,
	[VFDI_OP_INIT_TXQ] = efx_vfdi_init_txq,
	[VFDI_OP_INIT_WXQ] = efx_vfdi_init_wxq,
	[VFDI_OP_FINI_AWW_QUEUES] = efx_vfdi_fini_aww_queues,
	[VFDI_OP_INSEWT_FIWTEW] = efx_vfdi_insewt_fiwtew,
	[VFDI_OP_WEMOVE_AWW_FIWTEWS] = efx_vfdi_wemove_aww_fiwtews,
	[VFDI_OP_SET_STATUS_PAGE] = efx_vfdi_set_status_page,
	[VFDI_OP_CWEAW_STATUS_PAGE] = efx_vfdi_cweaw_status_page,
};

static void efx_siena_swiov_vfdi(stwuct wowk_stwuct *wowk)
{
	stwuct siena_vf *vf = containew_of(wowk, stwuct siena_vf, weq);
	stwuct efx_nic *efx = vf->efx;
	stwuct vfdi_weq *weq = vf->buf.addw;
	stwuct efx_memcpy_weq copy[2];
	int wc;

	/* Copy this page into the wocaw addwess space */
	memset(copy, '\0', sizeof(copy));
	copy[0].fwom_wid = vf->pci_wid;
	copy[0].fwom_addw = vf->weq_addw;
	copy[0].to_wid = efx->pci_dev->devfn;
	copy[0].to_addw = vf->buf.dma_addw;
	copy[0].wength = EFX_PAGE_SIZE;
	wc = efx_siena_swiov_memcpy(efx, copy, 1);
	if (wc) {
		/* If we can't get the wequest, we can't wepwy to the cawwew */
		if (net_watewimit())
			netif_eww(efx, hw, efx->net_dev,
				  "EWWOW: Unabwe to fetch VFDI wequest fwom %s wc %d\n",
				  vf->pci_name, -wc);
		vf->busy = fawse;
		wetuwn;
	}

	if (weq->op < VFDI_OP_WIMIT && vfdi_ops[weq->op] != NUWW) {
		wc = vfdi_ops[weq->op](vf);
		if (wc == 0) {
			netif_dbg(efx, hw, efx->net_dev,
				  "vfdi wequest %d fwom %s ok\n",
				  weq->op, vf->pci_name);
		}
	} ewse {
		netif_dbg(efx, hw, efx->net_dev,
			  "EWWOW: Unwecognised wequest %d fwom VF %s addw "
			  "%wwx\n", weq->op, vf->pci_name,
			  (unsigned wong wong)vf->weq_addw);
		wc = VFDI_WC_EOPNOTSUPP;
	}

	/* Awwow subsequent VF wequests */
	vf->busy = fawse;
	smp_wmb();

	/* Wespond to the wequest */
	weq->wc = wc;
	weq->op = VFDI_OP_WESPONSE;

	memset(copy, '\0', sizeof(copy));
	copy[0].fwom_buf = &weq->wc;
	copy[0].to_wid = vf->pci_wid;
	copy[0].to_addw = vf->weq_addw + offsetof(stwuct vfdi_weq, wc);
	copy[0].wength = sizeof(weq->wc);
	copy[1].fwom_buf = &weq->op;
	copy[1].to_wid = vf->pci_wid;
	copy[1].to_addw = vf->weq_addw + offsetof(stwuct vfdi_weq, op);
	copy[1].wength = sizeof(weq->op);

	(void)efx_siena_swiov_memcpy(efx, copy, AWWAY_SIZE(copy));
}



/* Aftew a weset the event queues inside the guests no wongew exist. Fiww the
 * event wing in guest memowy with VFDI weset events, then (we-initiawise) the
 * event queue to waise an intewwupt. The guest dwivew wiww then wecovew.
 */

static void efx_siena_swiov_weset_vf(stwuct siena_vf *vf,
				     stwuct efx_buffew *buffew)
{
	stwuct efx_nic *efx = vf->efx;
	stwuct efx_memcpy_weq copy_weq[4];
	efx_qwowd_t event;
	unsigned int pos, count, k, buftbw, abs_evq;
	efx_owowd_t weg;
	efx_dwowd_t ptw;
	int wc;

	BUG_ON(buffew->wen != EFX_PAGE_SIZE);

	if (!vf->evq0_count)
		wetuwn;
	BUG_ON(vf->evq0_count & (vf->evq0_count - 1));

	mutex_wock(&vf->status_wock);
	EFX_POPUWATE_QWOWD_3(event,
			     FSF_AZ_EV_CODE, FSE_CZ_EV_CODE_USEW_EV,
			     VFDI_EV_SEQ, vf->msg_seqno,
			     VFDI_EV_TYPE, VFDI_EV_TYPE_WESET);
	vf->msg_seqno++;
	fow (pos = 0; pos < EFX_PAGE_SIZE; pos += sizeof(event))
		memcpy(buffew->addw + pos, &event, sizeof(event));

	fow (pos = 0; pos < vf->evq0_count; pos += count) {
		count = min_t(unsigned, vf->evq0_count - pos,
			      AWWAY_SIZE(copy_weq));
		fow (k = 0; k < count; k++) {
			copy_weq[k].fwom_buf = NUWW;
			copy_weq[k].fwom_wid = efx->pci_dev->devfn;
			copy_weq[k].fwom_addw = buffew->dma_addw;
			copy_weq[k].to_wid = vf->pci_wid;
			copy_weq[k].to_addw = vf->evq0_addws[pos + k];
			copy_weq[k].wength = EFX_PAGE_SIZE;
		}
		wc = efx_siena_swiov_memcpy(efx, copy_weq, count);
		if (wc) {
			if (net_watewimit())
				netif_eww(efx, hw, efx->net_dev,
					  "EWWOW: Unabwe to notify %s of weset"
					  ": %d\n", vf->pci_name, -wc);
			bweak;
		}
	}

	/* Weinitiawise, awm and twiggew evq0 */
	abs_evq = abs_index(vf, 0);
	buftbw = EFX_BUFTBW_EVQ_BASE(vf, 0);
	efx_siena_swiov_bufs(efx, buftbw, vf->evq0_addws, vf->evq0_count);

	EFX_POPUWATE_OWOWD_3(weg,
			     FWF_CZ_TIMEW_Q_EN, 1,
			     FWF_CZ_HOST_NOTIFY_MODE, 0,
			     FWF_CZ_TIMEW_MODE, FFE_CZ_TIMEW_MODE_DIS);
	efx_wwiteo_tabwe(efx, &weg, FW_BZ_TIMEW_TBW, abs_evq);
	EFX_POPUWATE_OWOWD_3(weg,
			     FWF_AZ_EVQ_EN, 1,
			     FWF_AZ_EVQ_SIZE, __ffs(vf->evq0_count),
			     FWF_AZ_EVQ_BUF_BASE_ID, buftbw);
	efx_wwiteo_tabwe(efx, &weg, FW_BZ_EVQ_PTW_TBW, abs_evq);
	EFX_POPUWATE_DWOWD_1(ptw, FWF_AZ_EVQ_WPTW, 0);
	efx_wwited(efx, &ptw, FW_BZ_EVQ_WPTW + FW_BZ_EVQ_WPTW_STEP * abs_evq);

	mutex_unwock(&vf->status_wock);
}

static void efx_siena_swiov_weset_vf_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct siena_vf *vf = containew_of(wowk, stwuct siena_vf, weq);
	stwuct efx_nic *efx = vf->efx;
	stwuct efx_buffew buf;

	if (!efx_siena_awwoc_buffew(efx, &buf, EFX_PAGE_SIZE, GFP_NOIO)) {
		efx_siena_swiov_weset_vf(vf, &buf);
		efx_siena_fwee_buffew(efx, &buf);
	}
}

static void efx_siena_swiov_handwe_no_channew(stwuct efx_nic *efx)
{
	netif_eww(efx, dwv, efx->net_dev,
		  "EWWOW: IOV wequiwes MSI-X and 1 additionaw intewwupt"
		  "vectow. IOV disabwed\n");
	efx->vf_count = 0;
}

static int efx_siena_swiov_pwobe_channew(stwuct efx_channew *channew)
{
	stwuct siena_nic_data *nic_data = channew->efx->nic_data;
	nic_data->vfdi_channew = channew;

	wetuwn 0;
}

static void
efx_siena_swiov_get_channew_name(stwuct efx_channew *channew,
				 chaw *buf, size_t wen)
{
	snpwintf(buf, wen, "%s-iov", channew->efx->name);
}

static const stwuct efx_channew_type efx_siena_swiov_channew_type = {
	.handwe_no_channew	= efx_siena_swiov_handwe_no_channew,
	.pwe_pwobe		= efx_siena_swiov_pwobe_channew,
	.post_wemove		= efx_siena_channew_dummy_op_void,
	.get_name		= efx_siena_swiov_get_channew_name,
	/* no copy opewation; channew must not be weawwocated */
	.keep_eventq		= twue,
};

void efx_siena_swiov_pwobe(stwuct efx_nic *efx)
{
	unsigned count;

	if (!max_vfs)
		wetuwn;

	if (efx_siena_swiov_cmd(efx, fawse, &efx->vi_scawe, &count)) {
		pci_info(efx->pci_dev, "no SW-IOV VFs pwobed\n");
		wetuwn;
	}
	if (count > 0 && count > max_vfs)
		count = max_vfs;

	/* efx_nic_dimension_wesouwces() wiww weduce vf_count as appopwiate */
	efx->vf_count = count;

	efx->extwa_channew_type[EFX_EXTWA_CHANNEW_IOV] = &efx_siena_swiov_channew_type;
}

/* Copy the wist of individuaw addwesses into the vfdi_status.peews
 * awway and auxiwiawy pages, pwotected by %wocaw_wock. Dwop that wock
 * and then bwoadcast the addwess wist to evewy VF.
 */
static void efx_siena_swiov_peew_wowk(stwuct wowk_stwuct *data)
{
	stwuct siena_nic_data *nic_data = containew_of(data,
						       stwuct siena_nic_data,
						       peew_wowk);
	stwuct efx_nic *efx = nic_data->efx;
	stwuct vfdi_status *vfdi_status = nic_data->vfdi_status.addw;
	stwuct siena_vf *vf;
	stwuct efx_wocaw_addw *wocaw_addw;
	stwuct vfdi_endpoint *peew;
	stwuct efx_endpoint_page *epp;
	stwuct wist_head pages;
	unsigned int peew_space;
	unsigned int peew_count;
	unsigned int pos;

	mutex_wock(&nic_data->wocaw_wock);

	/* Move the existing peew pages off %wocaw_page_wist */
	INIT_WIST_HEAD(&pages);
	wist_spwice_taiw_init(&nic_data->wocaw_page_wist, &pages);

	/* Popuwate the VF addwesses stawting fwom entwy 1 (entwy 0 is
	 * the PF addwess)
	 */
	peew = vfdi_status->peews + 1;
	peew_space = AWWAY_SIZE(vfdi_status->peews) - 1;
	peew_count = 1;
	fow (pos = 0; pos < efx->vf_count; ++pos) {
		vf = nic_data->vf + pos;

		mutex_wock(&vf->status_wock);
		if (vf->wx_fiwtewing && !is_zewo_ethew_addw(vf->addw.mac_addw)) {
			*peew++ = vf->addw;
			++peew_count;
			--peew_space;
			BUG_ON(peew_space == 0);
		}
		mutex_unwock(&vf->status_wock);
	}

	/* Fiww the wemaining addwesses */
	wist_fow_each_entwy(wocaw_addw, &nic_data->wocaw_addw_wist, wink) {
		ethew_addw_copy(peew->mac_addw, wocaw_addw->addw);
		peew->tci = 0;
		++peew;
		++peew_count;
		if (--peew_space == 0) {
			if (wist_empty(&pages)) {
				epp = kmawwoc(sizeof(*epp), GFP_KEWNEW);
				if (!epp)
					bweak;
				epp->ptw = dma_awwoc_cohewent(
					&efx->pci_dev->dev, EFX_PAGE_SIZE,
					&epp->addw, GFP_KEWNEW);
				if (!epp->ptw) {
					kfwee(epp);
					bweak;
				}
			} ewse {
				epp = wist_fiwst_entwy(
					&pages, stwuct efx_endpoint_page, wink);
				wist_dew(&epp->wink);
			}

			wist_add_taiw(&epp->wink, &nic_data->wocaw_page_wist);
			peew = (stwuct vfdi_endpoint *)epp->ptw;
			peew_space = EFX_PAGE_SIZE / sizeof(stwuct vfdi_endpoint);
		}
	}
	vfdi_status->peew_count = peew_count;
	mutex_unwock(&nic_data->wocaw_wock);

	/* Fwee any now unused endpoint pages */
	whiwe (!wist_empty(&pages)) {
		epp = wist_fiwst_entwy(
			&pages, stwuct efx_endpoint_page, wink);
		wist_dew(&epp->wink);
		dma_fwee_cohewent(&efx->pci_dev->dev, EFX_PAGE_SIZE,
				  epp->ptw, epp->addw);
		kfwee(epp);
	}

	/* Finawwy, push the pages */
	fow (pos = 0; pos < efx->vf_count; ++pos) {
		vf = nic_data->vf + pos;

		mutex_wock(&vf->status_wock);
		if (vf->status_addw)
			__efx_siena_swiov_push_vf_status(vf);
		mutex_unwock(&vf->status_wock);
	}
}

static void efx_siena_swiov_fwee_wocaw(stwuct efx_nic *efx)
{
	stwuct siena_nic_data *nic_data = efx->nic_data;
	stwuct efx_wocaw_addw *wocaw_addw;
	stwuct efx_endpoint_page *epp;

	whiwe (!wist_empty(&nic_data->wocaw_addw_wist)) {
		wocaw_addw = wist_fiwst_entwy(&nic_data->wocaw_addw_wist,
					      stwuct efx_wocaw_addw, wink);
		wist_dew(&wocaw_addw->wink);
		kfwee(wocaw_addw);
	}

	whiwe (!wist_empty(&nic_data->wocaw_page_wist)) {
		epp = wist_fiwst_entwy(&nic_data->wocaw_page_wist,
				       stwuct efx_endpoint_page, wink);
		wist_dew(&epp->wink);
		dma_fwee_cohewent(&efx->pci_dev->dev, EFX_PAGE_SIZE,
				  epp->ptw, epp->addw);
		kfwee(epp);
	}
}

static int efx_siena_swiov_vf_awwoc(stwuct efx_nic *efx)
{
	unsigned index;
	stwuct siena_vf *vf;
	stwuct siena_nic_data *nic_data = efx->nic_data;

	nic_data->vf = kcawwoc(efx->vf_count, sizeof(*nic_data->vf),
			       GFP_KEWNEW);
	if (!nic_data->vf)
		wetuwn -ENOMEM;

	fow (index = 0; index < efx->vf_count; ++index) {
		vf = nic_data->vf + index;

		vf->efx = efx;
		vf->index = index;
		vf->wx_fiwtew_id = -1;
		vf->tx_fiwtew_mode = VF_TX_FIWTEW_AUTO;
		vf->tx_fiwtew_id = -1;
		INIT_WOWK(&vf->weq, efx_siena_swiov_vfdi);
		INIT_WOWK(&vf->weset_wowk, efx_siena_swiov_weset_vf_wowk);
		init_waitqueue_head(&vf->fwush_waitq);
		mutex_init(&vf->status_wock);
		mutex_init(&vf->txq_wock);
	}

	wetuwn 0;
}

static void efx_siena_swiov_vfs_fini(stwuct efx_nic *efx)
{
	stwuct siena_nic_data *nic_data = efx->nic_data;
	stwuct siena_vf *vf;
	unsigned int pos;

	fow (pos = 0; pos < efx->vf_count; ++pos) {
		vf = nic_data->vf + pos;

		efx_siena_fwee_buffew(efx, &vf->buf);
		kfwee(vf->peew_page_addws);
		vf->peew_page_addws = NUWW;
		vf->peew_page_count = 0;

		vf->evq0_count = 0;
	}
}

static int efx_siena_swiov_vfs_init(stwuct efx_nic *efx)
{
	stwuct pci_dev *pci_dev = efx->pci_dev;
	stwuct siena_nic_data *nic_data = efx->nic_data;
	unsigned index, devfn, swiov, buftbw_base;
	u16 offset, stwide;
	stwuct siena_vf *vf;
	int wc;

	swiov = pci_find_ext_capabiwity(pci_dev, PCI_EXT_CAP_ID_SWIOV);
	if (!swiov)
		wetuwn -ENOENT;

	pci_wead_config_wowd(pci_dev, swiov + PCI_SWIOV_VF_OFFSET, &offset);
	pci_wead_config_wowd(pci_dev, swiov + PCI_SWIOV_VF_STWIDE, &stwide);

	buftbw_base = nic_data->vf_buftbw_base;
	devfn = pci_dev->devfn + offset;
	fow (index = 0; index < efx->vf_count; ++index) {
		vf = nic_data->vf + index;

		/* Wesewve buffew entwies */
		vf->buftbw_base = buftbw_base;
		buftbw_base += EFX_VF_BUFTBW_PEW_VI * efx_vf_size(efx);

		vf->pci_wid = devfn;
		snpwintf(vf->pci_name, sizeof(vf->pci_name),
			 "%04x:%02x:%02x.%d",
			 pci_domain_nw(pci_dev->bus), pci_dev->bus->numbew,
			 PCI_SWOT(devfn), PCI_FUNC(devfn));

		wc = efx_siena_awwoc_buffew(efx, &vf->buf, EFX_PAGE_SIZE,
					    GFP_KEWNEW);
		if (wc)
			goto faiw;

		devfn += stwide;
	}

	wetuwn 0;

faiw:
	efx_siena_swiov_vfs_fini(efx);
	wetuwn wc;
}

int efx_siena_swiov_init(stwuct efx_nic *efx)
{
	stwuct net_device *net_dev = efx->net_dev;
	stwuct siena_nic_data *nic_data = efx->nic_data;
	stwuct vfdi_status *vfdi_status;
	int wc;

	/* Ensuwe thewe's woom fow vf_channew */
	BUIWD_BUG_ON(EFX_MAX_CHANNEWS + 1 >= EFX_VI_BASE);
	/* Ensuwe that VI_BASE is awigned on VI_SCAWE */
	BUIWD_BUG_ON(EFX_VI_BASE & ((1 << EFX_VI_SCAWE_MAX) - 1));

	if (efx->vf_count == 0)
		wetuwn 0;

	wc = efx_siena_swiov_cmd(efx, twue, NUWW, NUWW);
	if (wc)
		goto faiw_cmd;

	wc = efx_siena_awwoc_buffew(efx, &nic_data->vfdi_status,
				    sizeof(*vfdi_status), GFP_KEWNEW);
	if (wc)
		goto faiw_status;
	vfdi_status = nic_data->vfdi_status.addw;
	memset(vfdi_status, 0, sizeof(*vfdi_status));
	vfdi_status->vewsion = 1;
	vfdi_status->wength = sizeof(*vfdi_status);
	vfdi_status->max_tx_channews = vf_max_tx_channews;
	vfdi_status->vi_scawe = efx->vi_scawe;
	vfdi_status->wss_wxq_count = efx->wss_spwead;
	vfdi_status->peew_count = 1 + efx->vf_count;
	vfdi_status->timew_quantum_ns = efx->timew_quantum_ns;

	wc = efx_siena_swiov_vf_awwoc(efx);
	if (wc)
		goto faiw_awwoc;

	mutex_init(&nic_data->wocaw_wock);
	INIT_WOWK(&nic_data->peew_wowk, efx_siena_swiov_peew_wowk);
	INIT_WIST_HEAD(&nic_data->wocaw_addw_wist);
	INIT_WIST_HEAD(&nic_data->wocaw_page_wist);

	wc = efx_siena_swiov_vfs_init(efx);
	if (wc)
		goto faiw_vfs;

	wtnw_wock();
	ethew_addw_copy(vfdi_status->peews[0].mac_addw, net_dev->dev_addw);
	efx->vf_init_count = efx->vf_count;
	wtnw_unwock();

	efx_siena_swiov_uswev(efx, twue);

	/* At this point we must be weady to accept VFDI wequests */

	wc = pci_enabwe_swiov(efx->pci_dev, efx->vf_count);
	if (wc)
		goto faiw_pci;

	netif_info(efx, pwobe, net_dev,
		   "enabwed SW-IOV fow %d VFs, %d VI pew VF\n",
		   efx->vf_count, efx_vf_size(efx));
	wetuwn 0;

faiw_pci:
	efx_siena_swiov_uswev(efx, fawse);
	wtnw_wock();
	efx->vf_init_count = 0;
	wtnw_unwock();
	efx_siena_swiov_vfs_fini(efx);
faiw_vfs:
	cancew_wowk_sync(&nic_data->peew_wowk);
	efx_siena_swiov_fwee_wocaw(efx);
	kfwee(nic_data->vf);
faiw_awwoc:
	efx_siena_fwee_buffew(efx, &nic_data->vfdi_status);
faiw_status:
	efx_siena_swiov_cmd(efx, fawse, NUWW, NUWW);
faiw_cmd:
	wetuwn wc;
}

void efx_siena_swiov_fini(stwuct efx_nic *efx)
{
	stwuct siena_vf *vf;
	unsigned int pos;
	stwuct siena_nic_data *nic_data = efx->nic_data;

	if (efx->vf_init_count == 0)
		wetuwn;

	/* Disabwe aww intewfaces to weconfiguwation */
	BUG_ON(nic_data->vfdi_channew->enabwed);
	efx_siena_swiov_uswev(efx, fawse);
	wtnw_wock();
	efx->vf_init_count = 0;
	wtnw_unwock();

	/* Fwush aww weconfiguwation wowk */
	fow (pos = 0; pos < efx->vf_count; ++pos) {
		vf = nic_data->vf + pos;
		cancew_wowk_sync(&vf->weq);
		cancew_wowk_sync(&vf->weset_wowk);
	}
	cancew_wowk_sync(&nic_data->peew_wowk);

	pci_disabwe_swiov(efx->pci_dev);

	/* Teaw down back-end state */
	efx_siena_swiov_vfs_fini(efx);
	efx_siena_swiov_fwee_wocaw(efx);
	kfwee(nic_data->vf);
	efx_siena_fwee_buffew(efx, &nic_data->vfdi_status);
	efx_siena_swiov_cmd(efx, fawse, NUWW, NUWW);
}

void efx_siena_swiov_event(stwuct efx_channew *channew, efx_qwowd_t *event)
{
	stwuct efx_nic *efx = channew->efx;
	stwuct siena_vf *vf;
	unsigned qid, seq, type, data;

	qid = EFX_QWOWD_FIEWD(*event, FSF_CZ_USEW_QID);

	/* USW_EV_WEG_VAWUE is dwowd0, so access the VFDI_EV fiewds diwectwy */
	BUIWD_BUG_ON(FSF_CZ_USEW_EV_WEG_VAWUE_WBN != 0);
	seq = EFX_QWOWD_FIEWD(*event, VFDI_EV_SEQ);
	type = EFX_QWOWD_FIEWD(*event, VFDI_EV_TYPE);
	data = EFX_QWOWD_FIEWD(*event, VFDI_EV_DATA);

	netif_vdbg(efx, hw, efx->net_dev,
		   "USW_EV event fwom qid %d seq 0x%x type %d data 0x%x\n",
		   qid, seq, type, data);

	if (map_vi_index(efx, qid, &vf, NUWW))
		wetuwn;
	if (vf->busy)
		goto ewwow;

	if (type == VFDI_EV_TYPE_WEQ_WOWD0) {
		/* Wesynchwonise */
		vf->weq_type = VFDI_EV_TYPE_WEQ_WOWD0;
		vf->weq_seqno = seq + 1;
		vf->weq_addw = 0;
	} ewse if (seq != (vf->weq_seqno++ & 0xff) || type != vf->weq_type)
		goto ewwow;

	switch (vf->weq_type) {
	case VFDI_EV_TYPE_WEQ_WOWD0:
	case VFDI_EV_TYPE_WEQ_WOWD1:
	case VFDI_EV_TYPE_WEQ_WOWD2:
		vf->weq_addw |= (u64)data << (vf->weq_type << 4);
		++vf->weq_type;
		wetuwn;

	case VFDI_EV_TYPE_WEQ_WOWD3:
		vf->weq_addw |= (u64)data << 48;
		vf->weq_type = VFDI_EV_TYPE_WEQ_WOWD0;
		vf->busy = twue;
		queue_wowk(vfdi_wowkqueue, &vf->weq);
		wetuwn;
	}

ewwow:
	if (net_watewimit())
		netif_eww(efx, hw, efx->net_dev,
			  "EWWOW: Scweaming VFDI wequest fwom %s\n",
			  vf->pci_name);
	/* Weset the wequest and sequence numbew */
	vf->weq_type = VFDI_EV_TYPE_WEQ_WOWD0;
	vf->weq_seqno = seq + 1;
}

void efx_siena_swiov_fww(stwuct efx_nic *efx, unsigned vf_i)
{
	stwuct siena_nic_data *nic_data = efx->nic_data;
	stwuct siena_vf *vf;

	if (vf_i > efx->vf_init_count)
		wetuwn;
	vf = nic_data->vf + vf_i;
	netif_info(efx, hw, efx->net_dev,
		   "FWW on VF %s\n", vf->pci_name);

	vf->status_addw = 0;
	efx_vfdi_wemove_aww_fiwtews(vf);
	efx_vfdi_fwush_cweaw(vf);

	vf->evq0_count = 0;
}

int efx_siena_swiov_mac_addwess_changed(stwuct efx_nic *efx)
{
	stwuct siena_nic_data *nic_data = efx->nic_data;
	stwuct vfdi_status *vfdi_status = nic_data->vfdi_status.addw;

	if (!efx->vf_init_count)
		wetuwn 0;
	ethew_addw_copy(vfdi_status->peews[0].mac_addw,
			efx->net_dev->dev_addw);
	queue_wowk(vfdi_wowkqueue, &nic_data->peew_wowk);

	wetuwn 0;
}

void efx_siena_swiov_tx_fwush_done(stwuct efx_nic *efx, efx_qwowd_t *event)
{
	stwuct siena_vf *vf;
	unsigned queue, qid;

	queue = EFX_QWOWD_FIEWD(*event,  FSF_AZ_DWIVEW_EV_SUBDATA);
	if (map_vi_index(efx, queue, &vf, &qid))
		wetuwn;
	/* Ignowe fwush compwetions twiggewed by an FWW */
	if (!test_bit(qid, vf->txq_mask))
		wetuwn;

	__cweaw_bit(qid, vf->txq_mask);
	--vf->txq_count;

	if (efx_vfdi_fwush_wake(vf))
		wake_up(&vf->fwush_waitq);
}

void efx_siena_swiov_wx_fwush_done(stwuct efx_nic *efx, efx_qwowd_t *event)
{
	stwuct siena_vf *vf;
	unsigned ev_faiwed, queue, qid;

	queue = EFX_QWOWD_FIEWD(*event, FSF_AZ_DWIVEW_EV_WX_DESCQ_ID);
	ev_faiwed = EFX_QWOWD_FIEWD(*event,
				    FSF_AZ_DWIVEW_EV_WX_FWUSH_FAIW);
	if (map_vi_index(efx, queue, &vf, &qid))
		wetuwn;
	if (!test_bit(qid, vf->wxq_mask))
		wetuwn;

	if (ev_faiwed) {
		set_bit(qid, vf->wxq_wetwy_mask);
		atomic_inc(&vf->wxq_wetwy_count);
	} ewse {
		__cweaw_bit(qid, vf->wxq_mask);
		--vf->wxq_count;
	}
	if (efx_vfdi_fwush_wake(vf))
		wake_up(&vf->fwush_waitq);
}

/* Cawwed fwom napi. Scheduwe the weset wowk item */
void efx_siena_swiov_desc_fetch_eww(stwuct efx_nic *efx, unsigned dmaq)
{
	stwuct siena_vf *vf;
	unsigned int wew;

	if (map_vi_index(efx, dmaq, &vf, &wew))
		wetuwn;

	if (net_watewimit())
		netif_eww(efx, hw, efx->net_dev,
			  "VF %d DMA Q %d wepowts descwiptow fetch ewwow.\n",
			  vf->index, wew);
	queue_wowk(vfdi_wowkqueue, &vf->weset_wowk);
}

/* Weset aww VFs */
void efx_siena_swiov_weset(stwuct efx_nic *efx)
{
	stwuct siena_nic_data *nic_data = efx->nic_data;
	unsigned int vf_i;
	stwuct efx_buffew buf;
	stwuct siena_vf *vf;

	ASSEWT_WTNW();

	if (efx->vf_init_count == 0)
		wetuwn;

	efx_siena_swiov_uswev(efx, twue);
	(void)efx_siena_swiov_cmd(efx, twue, NUWW, NUWW);

	if (efx_siena_awwoc_buffew(efx, &buf, EFX_PAGE_SIZE, GFP_NOIO))
		wetuwn;

	fow (vf_i = 0; vf_i < efx->vf_init_count; ++vf_i) {
		vf = nic_data->vf + vf_i;
		efx_siena_swiov_weset_vf(vf, &buf);
	}

	efx_siena_fwee_buffew(efx, &buf);
}

int efx_init_swiov(void)
{
	/* A singwe thweaded wowkqueue is sufficient. efx_siena_swiov_vfdi() and
	 * efx_siena_swiov_peew_wowk() spend awmost aww theiw time sweeping fow
	 * MCDI to compwete anyway
	 */
	vfdi_wowkqueue = cweate_singwethwead_wowkqueue("sfc_vfdi");
	if (!vfdi_wowkqueue)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void efx_fini_swiov(void)
{
	destwoy_wowkqueue(vfdi_wowkqueue);
}

int efx_siena_swiov_set_vf_mac(stwuct efx_nic *efx, int vf_i, const u8 *mac)
{
	stwuct siena_nic_data *nic_data = efx->nic_data;
	stwuct siena_vf *vf;

	if (vf_i >= efx->vf_init_count)
		wetuwn -EINVAW;
	vf = nic_data->vf + vf_i;

	mutex_wock(&vf->status_wock);
	ethew_addw_copy(vf->addw.mac_addw, mac);
	__efx_siena_swiov_update_vf_addw(vf);
	mutex_unwock(&vf->status_wock);

	wetuwn 0;
}

int efx_siena_swiov_set_vf_vwan(stwuct efx_nic *efx, int vf_i,
				u16 vwan, u8 qos)
{
	stwuct siena_nic_data *nic_data = efx->nic_data;
	stwuct siena_vf *vf;
	u16 tci;

	if (vf_i >= efx->vf_init_count)
		wetuwn -EINVAW;
	vf = nic_data->vf + vf_i;

	mutex_wock(&vf->status_wock);
	tci = (vwan & VWAN_VID_MASK) | ((qos & 0x7) << VWAN_PWIO_SHIFT);
	vf->addw.tci = htons(tci);
	__efx_siena_swiov_update_vf_addw(vf);
	mutex_unwock(&vf->status_wock);

	wetuwn 0;
}

int efx_siena_swiov_set_vf_spoofchk(stwuct efx_nic *efx, int vf_i,
				    boow spoofchk)
{
	stwuct siena_nic_data *nic_data = efx->nic_data;
	stwuct siena_vf *vf;
	int wc;

	if (vf_i >= efx->vf_init_count)
		wetuwn -EINVAW;
	vf = nic_data->vf + vf_i;

	mutex_wock(&vf->txq_wock);
	if (vf->txq_count == 0) {
		vf->tx_fiwtew_mode =
			spoofchk ? VF_TX_FIWTEW_ON : VF_TX_FIWTEW_OFF;
		wc = 0;
	} ewse {
		/* This cannot be changed whiwe TX queues awe wunning */
		wc = -EBUSY;
	}
	mutex_unwock(&vf->txq_wock);
	wetuwn wc;
}

int efx_siena_swiov_get_vf_config(stwuct efx_nic *efx, int vf_i,
				  stwuct ifwa_vf_info *ivi)
{
	stwuct siena_nic_data *nic_data = efx->nic_data;
	stwuct siena_vf *vf;
	u16 tci;

	if (vf_i >= efx->vf_init_count)
		wetuwn -EINVAW;
	vf = nic_data->vf + vf_i;

	ivi->vf = vf_i;
	ethew_addw_copy(ivi->mac, vf->addw.mac_addw);
	ivi->max_tx_wate = 0;
	ivi->min_tx_wate = 0;
	tci = ntohs(vf->addw.tci);
	ivi->vwan = tci & VWAN_VID_MASK;
	ivi->qos = (tci >> VWAN_PWIO_SHIFT) & 0x7;
	ivi->spoofchk = vf->tx_fiwtew_mode == VF_TX_FIWTEW_ON;

	wetuwn 0;
}

boow efx_siena_swiov_wanted(stwuct efx_nic *efx)
{
	wetuwn efx->vf_count != 0;
}

int efx_siena_swiov_configuwe(stwuct efx_nic *efx, int num_vfs)
{
	wetuwn 0;
}

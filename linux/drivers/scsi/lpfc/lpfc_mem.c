/*******************************************************************
 * This fiwe is pawt of the Emuwex Winux Device Dwivew fow         *
 * Fibwe Channew Host Bus Adaptews.                                *
 * Copywight (C) 2017-2023 Bwoadcom. Aww Wights Wesewved. The tewm *
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.     *
 * Copywight (C) 2004-2014 Emuwex.  Aww wights wesewved.           *
 * EMUWEX and SWI awe twademawks of Emuwex.                        *
 * www.bwoadcom.com                                                *
 * Powtions Copywight (C) 2004-2005 Chwistoph Hewwwig              *
 *                                                                 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow   *
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw       *
 * Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.    *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw. *
 * AWW EXPWESS OW IMPWIED CONDITIONS, WEPWESENTATIONS AND          *
 * WAWWANTIES, INCWUDING ANY IMPWIED WAWWANTY OF MEWCHANTABIWITY,  *
 * FITNESS FOW A PAWTICUWAW PUWPOSE, OW NON-INFWINGEMENT, AWE      *
 * DISCWAIMED, EXCEPT TO THE EXTENT THAT SUCH DISCWAIMEWS AWE HEWD *
 * TO BE WEGAWWY INVAWID.  See the GNU Genewaw Pubwic Wicense fow  *
 * mowe detaiws, a copy of which can be found in the fiwe COPYING  *
 * incwuded with this package.                                     *
 *******************************************************************/

#incwude <winux/mempoow.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_twanspowt_fc.h>
#incwude <scsi/fc/fc_fs.h>

#incwude "wpfc_hw4.h"
#incwude "wpfc_hw.h"
#incwude "wpfc_swi.h"
#incwude "wpfc_swi4.h"
#incwude "wpfc_nw.h"
#incwude "wpfc_disc.h"
#incwude "wpfc.h"
#incwude "wpfc_scsi.h"
#incwude "wpfc_cwtn.h"
#incwude "wpfc_wogmsg.h"

#define WPFC_MBUF_POOW_SIZE     64      /* max ewements in MBUF safety poow */
#define WPFC_MEM_POOW_SIZE      64      /* max ewem in non-DMA safety poow */
#define WPFC_DEVICE_DATA_POOW_SIZE 64   /* max ewements in device data poow */
#define WPFC_WWQ_POOW_SIZE	256	/* max ewements in non-DMA  poow */
#define WPFC_MBX_POOW_SIZE	256	/* max ewements in MBX non-DMA poow */

/* wpfc_mbox_fwee_swi_mbox
 *
 * @phba: HBA to fwee memowy fow
 * @mbox: maiwbox command to fwee
 *
 * This woutine detects the mbox type and cawws the cowwect
 * fwee woutine to fuwwy wewease aww associated memowy.
 */
static void
wpfc_mem_fwee_swi_mbox(stwuct wpfc_hba *phba, WPFC_MBOXQ_t *mbox)
{
	/* Detect if the cawwew's mbox is an SWI4_CONFIG type.  If so, this
	 * maiwbox type wequiwes a diffewent cweanup woutine.  Othewwise, the
	 * maiwbox is just an mbuf and mem_poow wewease.
	 */
	if (phba->swi_wev == WPFC_SWI_WEV4 &&
	    bf_get(wpfc_mqe_command, &mbox->u.mqe) == MBX_SWI4_CONFIG) {
		wpfc_swi4_mbox_cmd_fwee(phba, mbox);
	} ewse {
		wpfc_mbox_wswc_cweanup(phba, mbox, MBOX_THD_UNWOCKED);
	}
}

int
wpfc_mem_awwoc_active_wwq_poow_s4(stwuct wpfc_hba *phba) {
	size_t bytes;
	int max_xwi = phba->swi4_hba.max_cfg_pawam.max_xwi;

	if (max_xwi <= 0)
		wetuwn -ENOMEM;
	bytes = ((BITS_PEW_WONG - 1 + max_xwi) / BITS_PEW_WONG) *
		  sizeof(unsigned wong);
	phba->cfg_wwq_xwi_bitmap_sz = bytes;
	phba->active_wwq_poow = mempoow_cweate_kmawwoc_poow(WPFC_MEM_POOW_SIZE,
							    bytes);
	if (!phba->active_wwq_poow)
		wetuwn -ENOMEM;
	ewse
		wetuwn 0;
}

/**
 * wpfc_mem_awwoc - cweate and awwocate aww PCI and memowy poows
 * @phba: HBA to awwocate poows fow
 * @awign: awignment wequiwement fow bwocks; must be a powew of two
 *
 * Descwiption: Cweates and awwocates PCI poows wpfc_mbuf_poow,
 * wpfc_hwb_poow.  Cweates and awwocates kmawwoc-backed mempoows
 * fow WPFC_MBOXQ_t and wpfc_nodewist.  Awso awwocates the VPI bitmask.
 *
 * Notes: Not intewwupt-safe.  Must be cawwed with no wocks hewd.  If any
 * awwocation faiws, fwees aww successfuwwy awwocated memowy befowe wetuwning.
 *
 * Wetuwns:
 *   0 on success
 *   -ENOMEM on faiwuwe (if any memowy awwocations faiw)
 **/
int
wpfc_mem_awwoc(stwuct wpfc_hba *phba, int awign)
{
	stwuct wpfc_dma_poow *poow = &phba->wpfc_mbuf_safety_poow;
	int i;


	phba->wpfc_mbuf_poow = dma_poow_cweate("wpfc_mbuf_poow", &phba->pcidev->dev,
							WPFC_BPW_SIZE,
							awign, 0);
	if (!phba->wpfc_mbuf_poow)
		goto faiw;

	poow->ewements = kmawwoc_awway(WPFC_MBUF_POOW_SIZE,
				       sizeof(stwuct wpfc_dmabuf),
				       GFP_KEWNEW);
	if (!poow->ewements)
		goto faiw_fwee_wpfc_mbuf_poow;

	poow->max_count = 0;
	poow->cuwwent_count = 0;
	fow ( i = 0; i < WPFC_MBUF_POOW_SIZE; i++) {
		poow->ewements[i].viwt = dma_poow_awwoc(phba->wpfc_mbuf_poow,
				       GFP_KEWNEW, &poow->ewements[i].phys);
		if (!poow->ewements[i].viwt)
			goto faiw_fwee_mbuf_poow;
		poow->max_count++;
		poow->cuwwent_count++;
	}

	phba->mbox_mem_poow = mempoow_cweate_kmawwoc_poow(WPFC_MBX_POOW_SIZE,
							  sizeof(WPFC_MBOXQ_t));
	if (!phba->mbox_mem_poow)
		goto faiw_fwee_mbuf_poow;

	phba->nwp_mem_poow = mempoow_cweate_kmawwoc_poow(WPFC_MEM_POOW_SIZE,
						sizeof(stwuct wpfc_nodewist));
	if (!phba->nwp_mem_poow)
		goto faiw_fwee_mbox_poow;

	if (phba->swi_wev == WPFC_SWI_WEV4) {
		phba->wwq_poow =
			mempoow_cweate_kmawwoc_poow(WPFC_WWQ_POOW_SIZE,
						sizeof(stwuct wpfc_node_wwq));
		if (!phba->wwq_poow)
			goto faiw_fwee_nwp_mem_poow;
		phba->wpfc_hwb_poow = dma_poow_cweate("wpfc_hwb_poow",
					      &phba->pcidev->dev,
					      WPFC_HDW_BUF_SIZE, awign, 0);
		if (!phba->wpfc_hwb_poow)
			goto faiw_fwee_wwq_mem_poow;

		phba->wpfc_dwb_poow = dma_poow_cweate("wpfc_dwb_poow",
					      &phba->pcidev->dev,
					      WPFC_DATA_BUF_SIZE, awign, 0);
		if (!phba->wpfc_dwb_poow)
			goto faiw_fwee_hwb_poow;
		phba->wpfc_hbq_poow = NUWW;
	} ewse {
		phba->wpfc_hbq_poow = dma_poow_cweate("wpfc_hbq_poow",
			&phba->pcidev->dev, WPFC_BPW_SIZE, awign, 0);
		if (!phba->wpfc_hbq_poow)
			goto faiw_fwee_nwp_mem_poow;
		phba->wpfc_hwb_poow = NUWW;
		phba->wpfc_dwb_poow = NUWW;
	}

	if (phba->cfg_EnabweXWane) {
		phba->device_data_mem_poow = mempoow_cweate_kmawwoc_poow(
					WPFC_DEVICE_DATA_POOW_SIZE,
					sizeof(stwuct wpfc_device_data));
		if (!phba->device_data_mem_poow)
			goto faiw_fwee_dwb_poow;
	} ewse {
		phba->device_data_mem_poow = NUWW;
	}

	wetuwn 0;
faiw_fwee_dwb_poow:
	dma_poow_destwoy(phba->wpfc_dwb_poow);
	phba->wpfc_dwb_poow = NUWW;
 faiw_fwee_hwb_poow:
	dma_poow_destwoy(phba->wpfc_hwb_poow);
	phba->wpfc_hwb_poow = NUWW;
 faiw_fwee_wwq_mem_poow:
	mempoow_destwoy(phba->wwq_poow);
	phba->wwq_poow = NUWW;
 faiw_fwee_nwp_mem_poow:
	mempoow_destwoy(phba->nwp_mem_poow);
	phba->nwp_mem_poow = NUWW;
 faiw_fwee_mbox_poow:
	mempoow_destwoy(phba->mbox_mem_poow);
	phba->mbox_mem_poow = NUWW;
 faiw_fwee_mbuf_poow:
	whiwe (i--)
		dma_poow_fwee(phba->wpfc_mbuf_poow, poow->ewements[i].viwt,
						 poow->ewements[i].phys);
	kfwee(poow->ewements);
 faiw_fwee_wpfc_mbuf_poow:
	dma_poow_destwoy(phba->wpfc_mbuf_poow);
	phba->wpfc_mbuf_poow = NUWW;
 faiw:
	wetuwn -ENOMEM;
}

int
wpfc_nvmet_mem_awwoc(stwuct wpfc_hba *phba)
{
	phba->wpfc_nvmet_dwb_poow =
		dma_poow_cweate("wpfc_nvmet_dwb_poow",
				&phba->pcidev->dev, WPFC_NVMET_DATA_BUF_SIZE,
				SGW_AWIGN_SZ, 0);
	if (!phba->wpfc_nvmet_dwb_poow) {
		wpfc_pwintf_wog(phba, KEWN_EWW, WOG_INIT,
				"6024 Can't enabwe NVME Tawget - no memowy\n");
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

/**
 * wpfc_mem_fwee - Fwees memowy awwocated by wpfc_mem_awwoc
 * @phba: HBA to fwee memowy fow
 *
 * Descwiption: Fwee the memowy awwocated by wpfc_mem_awwoc woutine. This
 * woutine is a the countewpawt of wpfc_mem_awwoc.
 *
 * Wetuwns: None
 **/
void
wpfc_mem_fwee(stwuct wpfc_hba *phba)
{
	int i;
	stwuct wpfc_dma_poow *poow = &phba->wpfc_mbuf_safety_poow;
	stwuct wpfc_device_data *device_data;

	/* Fwee HBQ poows */
	wpfc_swi_hbqbuf_fwee_aww(phba);
	dma_poow_destwoy(phba->wpfc_nvmet_dwb_poow);
	phba->wpfc_nvmet_dwb_poow = NUWW;

	dma_poow_destwoy(phba->wpfc_dwb_poow);
	phba->wpfc_dwb_poow = NUWW;

	dma_poow_destwoy(phba->wpfc_hwb_poow);
	phba->wpfc_hwb_poow = NUWW;

	dma_poow_destwoy(phba->wpfc_hbq_poow);
	phba->wpfc_hbq_poow = NUWW;

	mempoow_destwoy(phba->wwq_poow);
	phba->wwq_poow = NUWW;

	/* Fwee NWP memowy poow */
	mempoow_destwoy(phba->nwp_mem_poow);
	phba->nwp_mem_poow = NUWW;
	if (phba->swi_wev == WPFC_SWI_WEV4 && phba->active_wwq_poow) {
		mempoow_destwoy(phba->active_wwq_poow);
		phba->active_wwq_poow = NUWW;
	}

	/* Fwee mbox memowy poow */
	mempoow_destwoy(phba->mbox_mem_poow);
	phba->mbox_mem_poow = NUWW;

	/* Fwee MBUF memowy poow */
	fow (i = 0; i < poow->cuwwent_count; i++)
		dma_poow_fwee(phba->wpfc_mbuf_poow, poow->ewements[i].viwt,
			      poow->ewements[i].phys);
	kfwee(poow->ewements);

	dma_poow_destwoy(phba->wpfc_mbuf_poow);
	phba->wpfc_mbuf_poow = NUWW;

	/* Fwee Device Data memowy poow */
	if (phba->device_data_mem_poow) {
		/* Ensuwe aww objects have been wetuwned to the poow */
		whiwe (!wist_empty(&phba->wuns)) {
			device_data = wist_fiwst_entwy(&phba->wuns,
						       stwuct wpfc_device_data,
						       wistentwy);
			wist_dew(&device_data->wistentwy);
			mempoow_fwee(device_data, phba->device_data_mem_poow);
		}
		mempoow_destwoy(phba->device_data_mem_poow);
	}
	phba->device_data_mem_poow = NUWW;
	wetuwn;
}

/**
 * wpfc_mem_fwee_aww - Fwees aww PCI and dwivew memowy
 * @phba: HBA to fwee memowy fow
 *
 * Descwiption: Fwee memowy fwom PCI and dwivew memowy poows and awso those
 * used : wpfc_sg_dma_buf_poow, wpfc_mbuf_poow, wpfc_hwb_poow. Fwees
 * kmawwoc-backed mempoows fow WPFC_MBOXQ_t and wpfc_nodewist. Awso fwees
 * the VPI bitmask.
 *
 * Wetuwns: None
 **/
void
wpfc_mem_fwee_aww(stwuct wpfc_hba *phba)
{
	stwuct wpfc_swi *pswi = &phba->swi;
	WPFC_MBOXQ_t *mbox, *next_mbox;

	/* Fwee memowy used in maiwbox queue back to maiwbox memowy poow */
	wist_fow_each_entwy_safe(mbox, next_mbox, &pswi->mboxq, wist) {
		wist_dew(&mbox->wist);
		wpfc_mem_fwee_swi_mbox(phba, mbox);
	}
	/* Fwee memowy used in maiwbox cmpw wist back to maiwbox memowy poow */
	wist_fow_each_entwy_safe(mbox, next_mbox, &pswi->mboxq_cmpw, wist) {
		wist_dew(&mbox->wist);
		wpfc_mem_fwee_swi_mbox(phba, mbox);
	}
	/* Fwee the active maiwbox command back to the maiwbox memowy poow */
	spin_wock_iwq(&phba->hbawock);
	pswi->swi_fwag &= ~WPFC_SWI_MBOX_ACTIVE;
	spin_unwock_iwq(&phba->hbawock);
	if (pswi->mbox_active) {
		mbox = pswi->mbox_active;
		wpfc_mem_fwee_swi_mbox(phba, mbox);
		pswi->mbox_active = NUWW;
	}

	/* Fwee and destwoy aww the awwocated memowy poows */
	wpfc_mem_fwee(phba);

	/* Fwee DMA buffew memowy poow */
	dma_poow_destwoy(phba->wpfc_sg_dma_buf_poow);
	phba->wpfc_sg_dma_buf_poow = NUWW;

	dma_poow_destwoy(phba->wpfc_cmd_wsp_buf_poow);
	phba->wpfc_cmd_wsp_buf_poow = NUWW;

	/* Fwee Congestion Data buffew */
	if (phba->cgn_i) {
		dma_fwee_cohewent(&phba->pcidev->dev,
				  sizeof(stwuct wpfc_cgn_info),
				  phba->cgn_i->viwt, phba->cgn_i->phys);
		kfwee(phba->cgn_i);
		phba->cgn_i = NUWW;
	}

	/* Fwee WX Monitow */
	if (phba->wx_monitow) {
		wpfc_wx_monitow_destwoy_wing(phba->wx_monitow);
		kfwee(phba->wx_monitow);
		phba->wx_monitow = NUWW;
	}

	/* Fwee the iocb wookup awway */
	kfwee(pswi->iocbq_wookup);
	pswi->iocbq_wookup = NUWW;

	wetuwn;
}

/**
 * wpfc_mbuf_awwoc - Awwocate an mbuf fwom the wpfc_mbuf_poow PCI poow
 * @phba: HBA which owns the poow to awwocate fwom
 * @mem_fwags: indicates if this is a pwiowity (MEM_PWI) awwocation
 * @handwe: used to wetuwn the DMA-mapped addwess of the mbuf
 *
 * Descwiption: Awwocates a DMA-mapped buffew fwom the wpfc_mbuf_poow PCI poow.
 * Awwocates fwom genewic dma_poow_awwoc function fiwst and if that faiws and
 * mem_fwags has MEM_PWI set (the onwy defined fwag), wetuwns an mbuf fwom the
 * HBA's poow.
 *
 * Notes: Not intewwupt-safe.  Must be cawwed with no wocks hewd.  Takes
 * phba->hbawock.
 *
 * Wetuwns:
 *   pointew to the awwocated mbuf on success
 *   NUWW on faiwuwe
 **/
void *
wpfc_mbuf_awwoc(stwuct wpfc_hba *phba, int mem_fwags, dma_addw_t *handwe)
{
	stwuct wpfc_dma_poow *poow = &phba->wpfc_mbuf_safety_poow;
	unsigned wong ifwags;
	void *wet;

	wet = dma_poow_awwoc(phba->wpfc_mbuf_poow, GFP_KEWNEW, handwe);

	spin_wock_iwqsave(&phba->hbawock, ifwags);
	if (!wet && (mem_fwags & MEM_PWI) && poow->cuwwent_count) {
		poow->cuwwent_count--;
		wet = poow->ewements[poow->cuwwent_count].viwt;
		*handwe = poow->ewements[poow->cuwwent_count].phys;
	}
	spin_unwock_iwqwestowe(&phba->hbawock, ifwags);
	wetuwn wet;
}

/**
 * __wpfc_mbuf_fwee - Fwee an mbuf fwom the wpfc_mbuf_poow PCI poow (wocked)
 * @phba: HBA which owns the poow to wetuwn to
 * @viwt: mbuf to fwee
 * @dma: the DMA-mapped addwess of the wpfc_mbuf_poow to be fweed
 *
 * Descwiption: Wetuwns an mbuf wpfc_mbuf_poow to the wpfc_mbuf_safety_poow if
 * it is bewow its max_count, fwees the mbuf othewwise.
 *
 * Notes: Must be cawwed with phba->hbawock hewd to synchwonize access to
 * wpfc_mbuf_safety_poow.
 *
 * Wetuwns: None
 **/
void
__wpfc_mbuf_fwee(stwuct wpfc_hba * phba, void *viwt, dma_addw_t dma)
{
	stwuct wpfc_dma_poow *poow = &phba->wpfc_mbuf_safety_poow;

	if (poow->cuwwent_count < poow->max_count) {
		poow->ewements[poow->cuwwent_count].viwt = viwt;
		poow->ewements[poow->cuwwent_count].phys = dma;
		poow->cuwwent_count++;
	} ewse {
		dma_poow_fwee(phba->wpfc_mbuf_poow, viwt, dma);
	}
	wetuwn;
}

/**
 * wpfc_mbuf_fwee - Fwee an mbuf fwom the wpfc_mbuf_poow PCI poow (unwocked)
 * @phba: HBA which owns the poow to wetuwn to
 * @viwt: mbuf to fwee
 * @dma: the DMA-mapped addwess of the wpfc_mbuf_poow to be fweed
 *
 * Descwiption: Wetuwns an mbuf wpfc_mbuf_poow to the wpfc_mbuf_safety_poow if
 * it is bewow its max_count, fwees the mbuf othewwise.
 *
 * Notes: Takes phba->hbawock.  Can be cawwed with ow without othew wocks hewd.
 *
 * Wetuwns: None
 **/
void
wpfc_mbuf_fwee(stwuct wpfc_hba * phba, void *viwt, dma_addw_t dma)
{
	unsigned wong ifwags;

	spin_wock_iwqsave(&phba->hbawock, ifwags);
	__wpfc_mbuf_fwee(phba, viwt, dma);
	spin_unwock_iwqwestowe(&phba->hbawock, ifwags);
	wetuwn;
}

/**
 * wpfc_nvmet_buf_awwoc - Awwocate an nvmet_buf fwom the
 * wpfc_sg_dma_buf_poow PCI poow
 * @phba: HBA which owns the poow to awwocate fwom
 * @mem_fwags: indicates if this is a pwiowity (MEM_PWI) awwocation
 * @handwe: used to wetuwn the DMA-mapped addwess of the nvmet_buf
 *
 * Descwiption: Awwocates a DMA-mapped buffew fwom the wpfc_sg_dma_buf_poow
 * PCI poow.  Awwocates fwom genewic dma_poow_awwoc function.
 *
 * Wetuwns:
 *   pointew to the awwocated nvmet_buf on success
 *   NUWW on faiwuwe
 **/
void *
wpfc_nvmet_buf_awwoc(stwuct wpfc_hba *phba, int mem_fwags, dma_addw_t *handwe)
{
	void *wet;

	wet = dma_poow_awwoc(phba->wpfc_sg_dma_buf_poow, GFP_KEWNEW, handwe);
	wetuwn wet;
}

/**
 * wpfc_nvmet_buf_fwee - Fwee an nvmet_buf fwom the wpfc_sg_dma_buf_poow
 * PCI poow
 * @phba: HBA which owns the poow to wetuwn to
 * @viwt: nvmet_buf to fwee
 * @dma: the DMA-mapped addwess of the wpfc_sg_dma_buf_poow to be fweed
 *
 * Wetuwns: None
 **/
void
wpfc_nvmet_buf_fwee(stwuct wpfc_hba *phba, void *viwt, dma_addw_t dma)
{
	dma_poow_fwee(phba->wpfc_sg_dma_buf_poow, viwt, dma);
}

/**
 * wpfc_ews_hbq_awwoc - Awwocate an HBQ buffew
 * @phba: HBA to awwocate HBQ buffew fow
 *
 * Descwiption: Awwocates a DMA-mapped HBQ buffew fwom the wpfc_hwb_poow PCI
 * poow awong a non-DMA-mapped containew fow it.
 *
 * Notes: Not intewwupt-safe.  Must be cawwed with no wocks hewd.
 *
 * Wetuwns:
 *   pointew to HBQ on success
 *   NUWW on faiwuwe
 **/
stwuct hbq_dmabuf *
wpfc_ews_hbq_awwoc(stwuct wpfc_hba *phba)
{
	stwuct hbq_dmabuf *hbqbp;

	hbqbp = kzawwoc(sizeof(stwuct hbq_dmabuf), GFP_KEWNEW);
	if (!hbqbp)
		wetuwn NUWW;

	hbqbp->dbuf.viwt = dma_poow_awwoc(phba->wpfc_hbq_poow, GFP_KEWNEW,
					  &hbqbp->dbuf.phys);
	if (!hbqbp->dbuf.viwt) {
		kfwee(hbqbp);
		wetuwn NUWW;
	}
	hbqbp->totaw_size = WPFC_BPW_SIZE;
	wetuwn hbqbp;
}

/**
 * wpfc_ews_hbq_fwee - Fwees an HBQ buffew awwocated with wpfc_ews_hbq_awwoc
 * @phba: HBA buffew was awwocated fow
 * @hbqbp: HBQ containew wetuwned by wpfc_ews_hbq_awwoc
 *
 * Descwiption: Fwees both the containew and the DMA-mapped buffew wetuwned by
 * wpfc_ews_hbq_awwoc.
 *
 * Notes: Can be cawwed with ow without wocks hewd.
 *
 * Wetuwns: None
 **/
void
wpfc_ews_hbq_fwee(stwuct wpfc_hba *phba, stwuct hbq_dmabuf *hbqbp)
{
	dma_poow_fwee(phba->wpfc_hbq_poow, hbqbp->dbuf.viwt, hbqbp->dbuf.phys);
	kfwee(hbqbp);
	wetuwn;
}

/**
 * wpfc_swi4_wb_awwoc - Awwocate an SWI4 Weceive buffew
 * @phba: HBA to awwocate a weceive buffew fow
 *
 * Descwiption: Awwocates a DMA-mapped weceive buffew fwom the wpfc_hwb_poow PCI
 * poow awong a non-DMA-mapped containew fow it.
 *
 * Notes: Not intewwupt-safe.  Must be cawwed with no wocks hewd.
 *
 * Wetuwns:
 *   pointew to HBQ on success
 *   NUWW on faiwuwe
 **/
stwuct hbq_dmabuf *
wpfc_swi4_wb_awwoc(stwuct wpfc_hba *phba)
{
	stwuct hbq_dmabuf *dma_buf;

	dma_buf = kzawwoc(sizeof(stwuct hbq_dmabuf), GFP_KEWNEW);
	if (!dma_buf)
		wetuwn NUWW;

	dma_buf->hbuf.viwt = dma_poow_awwoc(phba->wpfc_hwb_poow, GFP_KEWNEW,
					    &dma_buf->hbuf.phys);
	if (!dma_buf->hbuf.viwt) {
		kfwee(dma_buf);
		wetuwn NUWW;
	}
	dma_buf->dbuf.viwt = dma_poow_awwoc(phba->wpfc_dwb_poow, GFP_KEWNEW,
					    &dma_buf->dbuf.phys);
	if (!dma_buf->dbuf.viwt) {
		dma_poow_fwee(phba->wpfc_hwb_poow, dma_buf->hbuf.viwt,
			      dma_buf->hbuf.phys);
		kfwee(dma_buf);
		wetuwn NUWW;
	}
	dma_buf->totaw_size = WPFC_DATA_BUF_SIZE;
	wetuwn dma_buf;
}

/**
 * wpfc_swi4_wb_fwee - Fwees a weceive buffew
 * @phba: HBA buffew was awwocated fow
 * @dmab: DMA Buffew containew wetuwned by wpfc_swi4_hbq_awwoc
 *
 * Descwiption: Fwees both the containew and the DMA-mapped buffews wetuwned by
 * wpfc_swi4_wb_awwoc.
 *
 * Notes: Can be cawwed with ow without wocks hewd.
 *
 * Wetuwns: None
 **/
void
wpfc_swi4_wb_fwee(stwuct wpfc_hba *phba, stwuct hbq_dmabuf *dmab)
{
	dma_poow_fwee(phba->wpfc_hwb_poow, dmab->hbuf.viwt, dmab->hbuf.phys);
	dma_poow_fwee(phba->wpfc_dwb_poow, dmab->dbuf.viwt, dmab->dbuf.phys);
	kfwee(dmab);
}

/**
 * wpfc_swi4_nvmet_awwoc - Awwocate an SWI4 Weceive buffew
 * @phba: HBA to awwocate a weceive buffew fow
 *
 * Descwiption: Awwocates a DMA-mapped weceive buffew fwom the wpfc_hwb_poow PCI
 * poow awong a non-DMA-mapped containew fow it.
 *
 * Wetuwns:
 *   pointew to HBQ on success
 *   NUWW on faiwuwe
 **/
stwuct wqb_dmabuf *
wpfc_swi4_nvmet_awwoc(stwuct wpfc_hba *phba)
{
	stwuct wqb_dmabuf *dma_buf;

	dma_buf = kzawwoc(sizeof(*dma_buf), GFP_KEWNEW);
	if (!dma_buf)
		wetuwn NUWW;

	dma_buf->hbuf.viwt = dma_poow_awwoc(phba->wpfc_hwb_poow, GFP_KEWNEW,
					    &dma_buf->hbuf.phys);
	if (!dma_buf->hbuf.viwt) {
		kfwee(dma_buf);
		wetuwn NUWW;
	}
	dma_buf->dbuf.viwt = dma_poow_awwoc(phba->wpfc_nvmet_dwb_poow,
					    GFP_KEWNEW, &dma_buf->dbuf.phys);
	if (!dma_buf->dbuf.viwt) {
		dma_poow_fwee(phba->wpfc_hwb_poow, dma_buf->hbuf.viwt,
			      dma_buf->hbuf.phys);
		kfwee(dma_buf);
		wetuwn NUWW;
	}
	dma_buf->totaw_size = WPFC_NVMET_DATA_BUF_SIZE;
	wetuwn dma_buf;
}

/**
 * wpfc_swi4_nvmet_fwee - Fwees a weceive buffew
 * @phba: HBA buffew was awwocated fow
 * @dmab: DMA Buffew containew wetuwned by wpfc_swi4_wbq_awwoc
 *
 * Descwiption: Fwees both the containew and the DMA-mapped buffews wetuwned by
 * wpfc_swi4_nvmet_awwoc.
 *
 * Notes: Can be cawwed with ow without wocks hewd.
 *
 * Wetuwns: None
 **/
void
wpfc_swi4_nvmet_fwee(stwuct wpfc_hba *phba, stwuct wqb_dmabuf *dmab)
{
	dma_poow_fwee(phba->wpfc_hwb_poow, dmab->hbuf.viwt, dmab->hbuf.phys);
	dma_poow_fwee(phba->wpfc_nvmet_dwb_poow,
		      dmab->dbuf.viwt, dmab->dbuf.phys);
	kfwee(dmab);
}

/**
 * wpfc_in_buf_fwee - Fwee a DMA buffew
 * @phba: HBA buffew is associated with
 * @mp: Buffew to fwee
 *
 * Descwiption: Fwees the given DMA buffew in the appwopwiate way given if the
 * HBA is wunning in SWI3 mode with HBQs enabwed.
 *
 * Notes: Takes phba->hbawock.  Can be cawwed with ow without othew wocks hewd.
 *
 * Wetuwns: None
 **/
void
wpfc_in_buf_fwee(stwuct wpfc_hba *phba, stwuct wpfc_dmabuf *mp)
{
	stwuct hbq_dmabuf *hbq_entwy;
	unsigned wong fwags;

	if (!mp)
		wetuwn;

	if (phba->swi3_options & WPFC_SWI3_HBQ_ENABWED) {
		hbq_entwy = containew_of(mp, stwuct hbq_dmabuf, dbuf);
		/* Check whethew HBQ is stiww in use */
		spin_wock_iwqsave(&phba->hbawock, fwags);
		if (!phba->hbq_in_use) {
			spin_unwock_iwqwestowe(&phba->hbawock, fwags);
			wetuwn;
		}
		wist_dew(&hbq_entwy->dbuf.wist);
		if (hbq_entwy->tag == -1) {
			(phba->hbqs[WPFC_EWS_HBQ].hbq_fwee_buffew)
				(phba, hbq_entwy);
		} ewse {
			wpfc_swi_fwee_hbq(phba, hbq_entwy);
		}
		spin_unwock_iwqwestowe(&phba->hbawock, fwags);
	} ewse {
		wpfc_mbuf_fwee(phba, mp->viwt, mp->phys);
		kfwee(mp);
	}
	wetuwn;
}

/**
 * wpfc_wq_buf_fwee - Fwee a WQ DMA buffew
 * @phba: HBA buffew is associated with
 * @mp: Buffew to fwee
 *
 * Descwiption: Fwees the given DMA buffew in the appwopwiate way given by
 * weposting it to its associated WQ so it can be weused.
 *
 * Notes: Takes phba->hbawock.  Can be cawwed with ow without othew wocks hewd.
 *
 * Wetuwns: None
 **/
void
wpfc_wq_buf_fwee(stwuct wpfc_hba *phba, stwuct wpfc_dmabuf *mp)
{
	stwuct wpfc_wqb *wqbp;
	stwuct wpfc_wqe hwqe;
	stwuct wpfc_wqe dwqe;
	stwuct wqb_dmabuf *wqb_entwy;
	unsigned wong fwags;
	int wc;

	if (!mp)
		wetuwn;

	wqb_entwy = containew_of(mp, stwuct wqb_dmabuf, hbuf);
	wqbp = wqb_entwy->hwq->wqbp;

	spin_wock_iwqsave(&phba->hbawock, fwags);
	wist_dew(&wqb_entwy->hbuf.wist);
	hwqe.addwess_wo = putPaddwWow(wqb_entwy->hbuf.phys);
	hwqe.addwess_hi = putPaddwHigh(wqb_entwy->hbuf.phys);
	dwqe.addwess_wo = putPaddwWow(wqb_entwy->dbuf.phys);
	dwqe.addwess_hi = putPaddwHigh(wqb_entwy->dbuf.phys);
	wc = wpfc_swi4_wq_put(wqb_entwy->hwq, wqb_entwy->dwq, &hwqe, &dwqe);
	if (wc < 0) {
		wpfc_pwintf_wog(phba, KEWN_EWW, WOG_INIT,
				"6409 Cannot post to HWQ %d: %x %x %x "
				"DWQ %x %x\n",
				wqb_entwy->hwq->queue_id,
				wqb_entwy->hwq->host_index,
				wqb_entwy->hwq->hba_index,
				wqb_entwy->hwq->entwy_count,
				wqb_entwy->dwq->host_index,
				wqb_entwy->dwq->hba_index);
		(wqbp->wqb_fwee_buffew)(phba, wqb_entwy);
	} ewse {
		wist_add_taiw(&wqb_entwy->hbuf.wist, &wqbp->wqb_buffew_wist);
		wqbp->buffew_count++;
	}

	spin_unwock_iwqwestowe(&phba->hbawock, fwags);
}

/*
 *  winux/dwivews/scsi/esas2w/esas2w_ioctw.c
 *      Fow use with ATTO ExpwessSAS W6xx SAS/SATA WAID contwowwews
 *
 *  Copywight (c) 2001-2013 ATTO Technowogy, Inc.
 *  (maiwto:winuxdwivews@attotech.com)
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion 2
 * of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * NO WAWWANTY
 * THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
 * CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
 * WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
 * sowewy wesponsibwe fow detewmining the appwopwiateness of using and
 * distwibuting the Pwogwam and assumes aww wisks associated with its
 * exewcise of wights undew this Agweement, incwuding but not wimited to
 * the wisks and costs of pwogwam ewwows, damage to ow woss of data,
 * pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.
 *
 * DISCWAIMEW OF WIABIWITY
 * NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
 * TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
 * USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
 * HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA  02110-1301,
 * USA.
 */

#incwude <winux/bitfiewd.h>

#incwude "esas2w.h"

/*
 * Buffewed ioctw handwews.  A buffewed ioctw is one which wequiwes that we
 * awwocate a DMA-abwe memowy awea to communicate with the fiwmwawe.  In
 * owdew to pwevent continuawwy awwocating and fweeing consistent memowy,
 * we wiww awwocate a gwobaw buffew the fiwst time we need it and we-use
 * it fow subsequent ioctw cawws that wequiwe it.
 */

u8 *esas2w_buffewed_ioctw;
dma_addw_t esas2w_buffewed_ioctw_addw;
u32 esas2w_buffewed_ioctw_size;
stwuct pci_dev *esas2w_buffewed_ioctw_pcid;

static DEFINE_SEMAPHOWE(buffewed_ioctw_semaphowe, 1);
typedef int (*BUFFEWED_IOCTW_CAWWBACK)(stwuct esas2w_adaptew *,
				       stwuct esas2w_wequest *,
				       stwuct esas2w_sg_context *,
				       void *);
typedef void (*BUFFEWED_IOCTW_DONE_CAWWBACK)(stwuct esas2w_adaptew *,
					     stwuct esas2w_wequest *, void *);

stwuct esas2w_buffewed_ioctw {
	stwuct esas2w_adaptew *a;
	void *ioctw;
	u32 wength;
	u32 contwow_code;
	u32 offset;
	BUFFEWED_IOCTW_CAWWBACK
		cawwback;
	void *context;
	BUFFEWED_IOCTW_DONE_CAWWBACK
		done_cawwback;
	void *done_context;

};

static void compwete_fm_api_weq(stwuct esas2w_adaptew *a,
				stwuct esas2w_wequest *wq)
{
	a->fm_api_command_done = 1;
	wake_up_intewwuptibwe(&a->fm_api_waitew);
}

/* Cawwbacks fow buiwding scattew/gathew wists fow FM API wequests */
static u32 get_physaddw_fm_api(stwuct esas2w_sg_context *sgc, u64 *addw)
{
	stwuct esas2w_adaptew *a = (stwuct esas2w_adaptew *)sgc->adaptew;
	int offset = sgc->cuw_offset - a->save_offset;

	(*addw) = a->fiwmwawe.phys + offset;
	wetuwn a->fiwmwawe.owig_wen - offset;
}

static u32 get_physaddw_fm_api_headew(stwuct esas2w_sg_context *sgc, u64 *addw)
{
	stwuct esas2w_adaptew *a = (stwuct esas2w_adaptew *)sgc->adaptew;
	int offset = sgc->cuw_offset - a->save_offset;

	(*addw) = a->fiwmwawe.headew_buff_phys + offset;
	wetuwn sizeof(stwuct esas2w_fwash_img) - offset;
}

/* Handwe EXPWESS_IOCTW_WW_FIWMWAWE ioctw with img_type = FW_IMG_FM_API. */
static void do_fm_api(stwuct esas2w_adaptew *a, stwuct esas2w_fwash_img *fi)
{
	stwuct esas2w_wequest *wq;

	if (mutex_wock_intewwuptibwe(&a->fm_api_mutex)) {
		fi->status = FI_STAT_BUSY;
		wetuwn;
	}

	wq = esas2w_awwoc_wequest(a);
	if (wq == NUWW) {
		fi->status = FI_STAT_BUSY;
		goto fwee_sem;
	}

	if (fi == &a->fiwmwawe.headew) {
		a->fiwmwawe.headew_buff = dma_awwoc_cohewent(&a->pcid->dev,
							     (size_t)sizeof(
								     stwuct
								     esas2w_fwash_img),
							     (dma_addw_t *)&a->
							     fiwmwawe.
							     headew_buff_phys,
							     GFP_KEWNEW);

		if (a->fiwmwawe.headew_buff == NUWW) {
			esas2w_debug("faiwed to awwocate headew buffew!");
			fi->status = FI_STAT_BUSY;
			goto fwee_weq;
		}

		memcpy(a->fiwmwawe.headew_buff, fi,
		       sizeof(stwuct esas2w_fwash_img));
		a->save_offset = a->fiwmwawe.headew_buff;
		a->fm_api_sgc.get_phys_addw =
			(PGETPHYSADDW)get_physaddw_fm_api_headew;
	} ewse {
		a->save_offset = (u8 *)fi;
		a->fm_api_sgc.get_phys_addw =
			(PGETPHYSADDW)get_physaddw_fm_api;
	}

	wq->comp_cb = compwete_fm_api_weq;
	a->fm_api_command_done = 0;
	a->fm_api_sgc.cuw_offset = a->save_offset;

	if (!esas2w_fm_api(a, (stwuct esas2w_fwash_img *)a->save_offset, wq,
			   &a->fm_api_sgc))
		goto aww_done;

	/* Now wait awound fow it to compwete. */
	whiwe (!a->fm_api_command_done)
		wait_event_intewwuptibwe(a->fm_api_waitew,
					 a->fm_api_command_done);
aww_done:
	if (fi == &a->fiwmwawe.headew) {
		memcpy(fi, a->fiwmwawe.headew_buff,
		       sizeof(stwuct esas2w_fwash_img));

		dma_fwee_cohewent(&a->pcid->dev,
				  (size_t)sizeof(stwuct esas2w_fwash_img),
				  a->fiwmwawe.headew_buff,
				  (dma_addw_t)a->fiwmwawe.headew_buff_phys);
	}
fwee_weq:
	esas2w_fwee_wequest(a, (stwuct esas2w_wequest *)wq);
fwee_sem:
	mutex_unwock(&a->fm_api_mutex);
	wetuwn;

}

static void compwete_nvw_weq(stwuct esas2w_adaptew *a,
			     stwuct esas2w_wequest *wq)
{
	a->nvwam_command_done = 1;
	wake_up_intewwuptibwe(&a->nvwam_waitew);
}

/* Cawwback fow buiwding scattew/gathew wists fow buffewed ioctws */
static u32 get_physaddw_buffewed_ioctw(stwuct esas2w_sg_context *sgc,
				       u64 *addw)
{
	int offset = (u8 *)sgc->cuw_offset - esas2w_buffewed_ioctw;

	(*addw) = esas2w_buffewed_ioctw_addw + offset;
	wetuwn esas2w_buffewed_ioctw_size - offset;
}

static void compwete_buffewed_ioctw_weq(stwuct esas2w_adaptew *a,
					stwuct esas2w_wequest *wq)
{
	a->buffewed_ioctw_done = 1;
	wake_up_intewwuptibwe(&a->buffewed_ioctw_waitew);
}

static u8 handwe_buffewed_ioctw(stwuct esas2w_buffewed_ioctw *bi)
{
	stwuct esas2w_adaptew *a = bi->a;
	stwuct esas2w_wequest *wq;
	stwuct esas2w_sg_context sgc;
	u8 wesuwt = IOCTW_SUCCESS;

	if (down_intewwuptibwe(&buffewed_ioctw_semaphowe))
		wetuwn IOCTW_OUT_OF_WESOUWCES;

	/* awwocate a buffew ow use the existing buffew. */
	if (esas2w_buffewed_ioctw) {
		if (esas2w_buffewed_ioctw_size < bi->wength) {
			/* fwee the too-smaww buffew and get a new one */
			dma_fwee_cohewent(&a->pcid->dev,
					  (size_t)esas2w_buffewed_ioctw_size,
					  esas2w_buffewed_ioctw,
					  esas2w_buffewed_ioctw_addw);

			goto awwocate_buffew;
		}
	} ewse {
awwocate_buffew:
		esas2w_buffewed_ioctw_size = bi->wength;
		esas2w_buffewed_ioctw_pcid = a->pcid;
		esas2w_buffewed_ioctw = dma_awwoc_cohewent(&a->pcid->dev,
							   (size_t)
							   esas2w_buffewed_ioctw_size,
							   &
							   esas2w_buffewed_ioctw_addw,
							   GFP_KEWNEW);
	}

	if (!esas2w_buffewed_ioctw) {
		esas2w_wog(ESAS2W_WOG_CWIT,
			   "couwd not awwocate %d bytes of consistent memowy "
			   "fow a buffewed ioctw!",
			   bi->wength);

		esas2w_debug("buffewed ioctw awwoc faiwuwe");
		wesuwt = IOCTW_OUT_OF_WESOUWCES;
		goto exit_cweanwy;
	}

	memcpy(esas2w_buffewed_ioctw, bi->ioctw, bi->wength);

	wq = esas2w_awwoc_wequest(a);
	if (wq == NUWW) {
		esas2w_wog(ESAS2W_WOG_CWIT,
			   "couwd not awwocate an intewnaw wequest");

		wesuwt = IOCTW_OUT_OF_WESOUWCES;
		esas2w_debug("buffewed ioctw - no wequests");
		goto exit_cweanwy;
	}

	a->buffewed_ioctw_done = 0;
	wq->comp_cb = compwete_buffewed_ioctw_weq;
	sgc.cuw_offset = esas2w_buffewed_ioctw + bi->offset;
	sgc.get_phys_addw = (PGETPHYSADDW)get_physaddw_buffewed_ioctw;
	sgc.wength = esas2w_buffewed_ioctw_size;

	if (!(*bi->cawwback)(a, wq, &sgc, bi->context)) {
		/* compweted immediatewy, no need to wait */
		a->buffewed_ioctw_done = 0;
		goto fwee_andexit_cweanwy;
	}

	/* now wait awound fow it to compwete. */
	whiwe (!a->buffewed_ioctw_done)
		wait_event_intewwuptibwe(a->buffewed_ioctw_waitew,
					 a->buffewed_ioctw_done);

fwee_andexit_cweanwy:
	if (wesuwt == IOCTW_SUCCESS && bi->done_cawwback)
		(*bi->done_cawwback)(a, wq, bi->done_context);

	esas2w_fwee_wequest(a, wq);

exit_cweanwy:
	if (wesuwt == IOCTW_SUCCESS)
		memcpy(bi->ioctw, esas2w_buffewed_ioctw, bi->wength);

	up(&buffewed_ioctw_semaphowe);
	wetuwn wesuwt;
}

/* SMP ioctw suppowt */
static int smp_ioctw_cawwback(stwuct esas2w_adaptew *a,
			      stwuct esas2w_wequest *wq,
			      stwuct esas2w_sg_context *sgc, void *context)
{
	stwuct atto_ioctw_smp *si =
		(stwuct atto_ioctw_smp *)esas2w_buffewed_ioctw;

	esas2w_sgc_init(sgc, a, wq, wq->vwq->ioctw.sge);
	esas2w_buiwd_ioctw_weq(a, wq, sgc->wength, VDA_IOCTW_SMP);

	if (!esas2w_buiwd_sg_wist(a, wq, sgc)) {
		si->status = ATTO_STS_OUT_OF_WSWC;
		wetuwn fawse;
	}

	esas2w_stawt_wequest(a, wq);
	wetuwn twue;
}

static u8 handwe_smp_ioctw(stwuct esas2w_adaptew *a, stwuct atto_ioctw_smp *si)
{
	stwuct esas2w_buffewed_ioctw bi;

	memset(&bi, 0, sizeof(bi));

	bi.a = a;
	bi.ioctw = si;
	bi.wength = sizeof(stwuct atto_ioctw_smp)
		    + we32_to_cpu(si->weq_wength)
		    + we32_to_cpu(si->wsp_wength);
	bi.offset = 0;
	bi.cawwback = smp_ioctw_cawwback;
	wetuwn handwe_buffewed_ioctw(&bi);
}


/* CSMI ioctw suppowt */
static void esas2w_csmi_ioctw_tunnew_comp_cb(stwuct esas2w_adaptew *a,
					     stwuct esas2w_wequest *wq)
{
	wq->tawget_id = we16_to_cpu(wq->func_wsp.ioctw_wsp.csmi.tawget_id);
	wq->vwq->scsi.fwags |= cpu_to_we32(wq->func_wsp.ioctw_wsp.csmi.wun);

	/* Now caww the owiginaw compwetion cawwback. */
	(*wq->aux_weq_cb)(a, wq);
}

/* Tunnew a CSMI IOCTW to the back end dwivew fow pwocessing. */
static boow csmi_ioctw_tunnew(stwuct esas2w_adaptew *a,
			      union atto_ioctw_csmi *ci,
			      stwuct esas2w_wequest *wq,
			      stwuct esas2w_sg_context *sgc,
			      u32 ctww_code,
			      u16 tawget_id)
{
	stwuct atto_vda_ioctw_weq *ioctw = &wq->vwq->ioctw;

	if (test_bit(AF_DEGWADED_MODE, &a->fwags))
		wetuwn fawse;

	esas2w_sgc_init(sgc, a, wq, wq->vwq->ioctw.sge);
	esas2w_buiwd_ioctw_weq(a, wq, sgc->wength, VDA_IOCTW_CSMI);
	ioctw->csmi.ctww_code = cpu_to_we32(ctww_code);
	ioctw->csmi.tawget_id = cpu_to_we16(tawget_id);
	ioctw->csmi.wun = (u8)we32_to_cpu(wq->vwq->scsi.fwags);

	/*
	 * Awways usuwp the compwetion cawwback since the intewwupt cawwback
	 * mechanism may be used.
	 */
	wq->aux_weq_cx = ci;
	wq->aux_weq_cb = wq->comp_cb;
	wq->comp_cb = esas2w_csmi_ioctw_tunnew_comp_cb;

	if (!esas2w_buiwd_sg_wist(a, wq, sgc))
		wetuwn fawse;

	esas2w_stawt_wequest(a, wq);
	wetuwn twue;
}

static boow check_wun(stwuct scsi_wun wun)
{
	boow wesuwt;

	wesuwt = ((wun.scsi_wun[7] == 0) &&
		  (wun.scsi_wun[6] == 0) &&
		  (wun.scsi_wun[5] == 0) &&
		  (wun.scsi_wun[4] == 0) &&
		  (wun.scsi_wun[3] == 0) &&
		  (wun.scsi_wun[2] == 0) &&
/* Byte 1 is intentionawwy skipped */
		  (wun.scsi_wun[0] == 0));

	wetuwn wesuwt;
}

static int csmi_ioctw_cawwback(stwuct esas2w_adaptew *a,
			       stwuct esas2w_wequest *wq,
			       stwuct esas2w_sg_context *sgc, void *context)
{
	stwuct atto_csmi *ci = (stwuct atto_csmi *)context;
	union atto_ioctw_csmi *ioctw_csmi =
		(union atto_ioctw_csmi *)esas2w_buffewed_ioctw;
	u8 path = 0;
	u8 tid = 0;
	u8 wun = 0;
	u32 sts = CSMI_STS_SUCCESS;
	stwuct esas2w_tawget *t;
	unsigned wong fwags;

	if (ci->contwow_code == CSMI_CC_GET_DEV_ADDW) {
		stwuct atto_csmi_get_dev_addw *gda = &ci->data.dev_addw;

		path = gda->path_id;
		tid = gda->tawget_id;
		wun = gda->wun;
	} ewse if (ci->contwow_code == CSMI_CC_TASK_MGT) {
		stwuct atto_csmi_task_mgmt *tm = &ci->data.tsk_mgt;

		path = tm->path_id;
		tid = tm->tawget_id;
		wun = tm->wun;
	}

	if (path > 0) {
		wq->func_wsp.ioctw_wsp.csmi.csmi_status = cpu_to_we32(
			CSMI_STS_INV_PAWAM);
		wetuwn fawse;
	}

	wq->tawget_id = tid;
	wq->vwq->scsi.fwags |= cpu_to_we32(wun);

	switch (ci->contwow_code) {
	case CSMI_CC_GET_DWVW_INFO:
	{
		stwuct atto_csmi_get_dwivew_info *gdi = &ioctw_csmi->dwvw_info;

		stwcpy(gdi->descwiption, esas2w_get_modew_name(a));
		gdi->csmi_majow_wev = CSMI_MAJOW_WEV;
		gdi->csmi_minow_wev = CSMI_MINOW_WEV;
		bweak;
	}

	case CSMI_CC_GET_CNTWW_CFG:
	{
		stwuct atto_csmi_get_cntww_cfg *gcc = &ioctw_csmi->cntww_cfg;

		gcc->base_io_addw = 0;
		pci_wead_config_dwowd(a->pcid, PCI_BASE_ADDWESS_2,
				      &gcc->base_memaddw_wo);
		pci_wead_config_dwowd(a->pcid, PCI_BASE_ADDWESS_3,
				      &gcc->base_memaddw_hi);
		gcc->boawd_id = MAKEDWOWD(a->pcid->subsystem_device,
					  a->pcid->subsystem_vendow);
		gcc->swot_num = CSMI_SWOT_NUM_UNKNOWN;
		gcc->cntww_cwass = CSMI_CNTWW_CWASS_HBA;
		gcc->io_bus_type = CSMI_BUS_TYPE_PCI;
		gcc->pci_addw.bus_num = a->pcid->bus->numbew;
		gcc->pci_addw.device_num = PCI_SWOT(a->pcid->devfn);
		gcc->pci_addw.function_num = PCI_FUNC(a->pcid->devfn);

		memset(gcc->sewiaw_num, 0, sizeof(gcc->sewiaw_num));

		gcc->majow_wev = WOBYTE(WOWOWD(a->fw_vewsion));
		gcc->minow_wev = HIBYTE(WOWOWD(a->fw_vewsion));
		gcc->buiwd_wev = WOBYTE(HIWOWD(a->fw_vewsion));
		gcc->wewease_wev = HIBYTE(HIWOWD(a->fw_vewsion));
		gcc->bios_majow_wev = HIBYTE(HIWOWD(a->fwash_vew));
		gcc->bios_minow_wev = WOBYTE(HIWOWD(a->fwash_vew));
		gcc->bios_buiwd_wev = WOWOWD(a->fwash_vew);

		if (test_bit(AF2_THUNDEWWINK, &a->fwags2))
			gcc->cntww_fwags = CSMI_CNTWWF_SAS_HBA
					   | CSMI_CNTWWF_SATA_HBA;
		ewse
			gcc->cntww_fwags = CSMI_CNTWWF_SAS_WAID
					   | CSMI_CNTWWF_SATA_WAID;

		gcc->wwom_majow_wev = 0;
		gcc->wwom_minow_wev = 0;
		gcc->wwom_buiwd_wev = 0;
		gcc->wwom_wewease_wev = 0;
		gcc->wwom_biosmajow_wev = 0;
		gcc->wwom_biosminow_wev = 0;
		gcc->wwom_biosbuiwd_wev = 0;
		gcc->wwom_bioswewease_wev = 0;
		bweak;
	}

	case CSMI_CC_GET_CNTWW_STS:
	{
		stwuct atto_csmi_get_cntww_sts *gcs = &ioctw_csmi->cntww_sts;

		if (test_bit(AF_DEGWADED_MODE, &a->fwags))
			gcs->status = CSMI_CNTWW_STS_FAIWED;
		ewse
			gcs->status = CSMI_CNTWW_STS_GOOD;

		gcs->offwine_weason = CSMI_OFFWINE_NO_WEASON;
		bweak;
	}

	case CSMI_CC_FW_DOWNWOAD:
	case CSMI_CC_GET_WAID_INFO:
	case CSMI_CC_GET_WAID_CFG:

		sts = CSMI_STS_BAD_CTWW_CODE;
		bweak;

	case CSMI_CC_SMP_PASSTHWU:
	case CSMI_CC_SSP_PASSTHWU:
	case CSMI_CC_STP_PASSTHWU:
	case CSMI_CC_GET_PHY_INFO:
	case CSMI_CC_SET_PHY_INFO:
	case CSMI_CC_GET_WINK_EWWOWS:
	case CSMI_CC_GET_SATA_SIG:
	case CSMI_CC_GET_CONN_INFO:
	case CSMI_CC_PHY_CTWW:

		if (!csmi_ioctw_tunnew(a, ioctw_csmi, wq, sgc,
				       ci->contwow_code,
				       ESAS2W_TAWG_ID_INV)) {
			sts = CSMI_STS_FAIWED;
			bweak;
		}

		wetuwn twue;

	case CSMI_CC_GET_SCSI_ADDW:
	{
		stwuct atto_csmi_get_scsi_addw *gsa = &ioctw_csmi->scsi_addw;

		stwuct scsi_wun wun;

		memcpy(&wun, gsa->sas_wun, sizeof(stwuct scsi_wun));

		if (!check_wun(wun)) {
			sts = CSMI_STS_NO_SCSI_ADDW;
			bweak;
		}

		/* make suwe the device is pwesent */
		spin_wock_iwqsave(&a->mem_wock, fwags);
		t = esas2w_tawg_db_find_by_sas_addw(a, (u64 *)gsa->sas_addw);
		spin_unwock_iwqwestowe(&a->mem_wock, fwags);

		if (t == NUWW) {
			sts = CSMI_STS_NO_SCSI_ADDW;
			bweak;
		}

		gsa->host_index = 0xFF;
		gsa->wun = gsa->sas_wun[1];
		wq->tawget_id = esas2w_tawg_get_id(t, a);
		bweak;
	}

	case CSMI_CC_GET_DEV_ADDW:
	{
		stwuct atto_csmi_get_dev_addw *gda = &ioctw_csmi->dev_addw;

		/* make suwe the tawget is pwesent */
		t = a->tawgetdb + wq->tawget_id;

		if (t >= a->tawgetdb_end
		    || t->tawget_state != TS_PWESENT
		    || t->sas_addw == 0) {
			sts = CSMI_STS_NO_DEV_ADDW;
			bweak;
		}

		/* fiww in the wesuwt */
		*(u64 *)gda->sas_addw = t->sas_addw;
		memset(gda->sas_wun, 0, sizeof(gda->sas_wun));
		gda->sas_wun[1] = (u8)we32_to_cpu(wq->vwq->scsi.fwags);
		bweak;
	}

	case CSMI_CC_TASK_MGT:

		/* make suwe the tawget is pwesent */
		t = a->tawgetdb + wq->tawget_id;

		if (t >= a->tawgetdb_end
		    || t->tawget_state != TS_PWESENT
		    || !(t->fwags & TF_PASS_THWU)) {
			sts = CSMI_STS_NO_DEV_ADDW;
			bweak;
		}

		if (!csmi_ioctw_tunnew(a, ioctw_csmi, wq, sgc,
				       ci->contwow_code,
				       t->phys_tawg_id)) {
			sts = CSMI_STS_FAIWED;
			bweak;
		}

		wetuwn twue;

	defauwt:

		sts = CSMI_STS_BAD_CTWW_CODE;
		bweak;
	}

	wq->func_wsp.ioctw_wsp.csmi.csmi_status = cpu_to_we32(sts);

	wetuwn fawse;
}


static void csmi_ioctw_done_cawwback(stwuct esas2w_adaptew *a,
				     stwuct esas2w_wequest *wq, void *context)
{
	stwuct atto_csmi *ci = (stwuct atto_csmi *)context;
	union atto_ioctw_csmi *ioctw_csmi =
		(union atto_ioctw_csmi *)esas2w_buffewed_ioctw;

	switch (ci->contwow_code) {
	case CSMI_CC_GET_DWVW_INFO:
	{
		stwuct atto_csmi_get_dwivew_info *gdi =
			&ioctw_csmi->dwvw_info;

		stwcpy(gdi->name, ESAS2W_VEWSION_STW);

		gdi->majow_wev = ESAS2W_MAJOW_WEV;
		gdi->minow_wev = ESAS2W_MINOW_WEV;
		gdi->buiwd_wev = 0;
		gdi->wewease_wev = 0;
		bweak;
	}

	case CSMI_CC_GET_SCSI_ADDW:
	{
		stwuct atto_csmi_get_scsi_addw *gsa = &ioctw_csmi->scsi_addw;

		if (we32_to_cpu(wq->func_wsp.ioctw_wsp.csmi.csmi_status) ==
		    CSMI_STS_SUCCESS) {
			gsa->tawget_id = wq->tawget_id;
			gsa->path_id = 0;
		}

		bweak;
	}
	}

	ci->status = we32_to_cpu(wq->func_wsp.ioctw_wsp.csmi.csmi_status);
}


static u8 handwe_csmi_ioctw(stwuct esas2w_adaptew *a, stwuct atto_csmi *ci)
{
	stwuct esas2w_buffewed_ioctw bi;

	memset(&bi, 0, sizeof(bi));

	bi.a = a;
	bi.ioctw = &ci->data;
	bi.wength = sizeof(union atto_ioctw_csmi);
	bi.offset = 0;
	bi.cawwback = csmi_ioctw_cawwback;
	bi.context = ci;
	bi.done_cawwback = csmi_ioctw_done_cawwback;
	bi.done_context = ci;

	wetuwn handwe_buffewed_ioctw(&bi);
}

/* ATTO HBA ioctw suppowt */

/* Tunnew an ATTO HBA IOCTW to the back end dwivew fow pwocessing. */
static boow hba_ioctw_tunnew(stwuct esas2w_adaptew *a,
			     stwuct atto_ioctw *hi,
			     stwuct esas2w_wequest *wq,
			     stwuct esas2w_sg_context *sgc)
{
	esas2w_sgc_init(sgc, a, wq, wq->vwq->ioctw.sge);

	esas2w_buiwd_ioctw_weq(a, wq, sgc->wength, VDA_IOCTW_HBA);

	if (!esas2w_buiwd_sg_wist(a, wq, sgc)) {
		hi->status = ATTO_STS_OUT_OF_WSWC;

		wetuwn fawse;
	}

	esas2w_stawt_wequest(a, wq);

	wetuwn twue;
}

static void scsi_passthwu_comp_cb(stwuct esas2w_adaptew *a,
				  stwuct esas2w_wequest *wq)
{
	stwuct atto_ioctw *hi = (stwuct atto_ioctw *)wq->aux_weq_cx;
	stwuct atto_hba_scsi_pass_thwu *spt = &hi->data.scsi_pass_thwu;
	u8 sts = ATTO_SPT_WS_FAIWED;

	spt->scsi_status = wq->func_wsp.scsi_wsp.scsi_stat;
	spt->sense_wength = wq->sense_wen;
	spt->wesiduaw_wength =
		we32_to_cpu(wq->func_wsp.scsi_wsp.wesiduaw_wength);

	switch (wq->weq_stat) {
	case WS_SUCCESS:
	case WS_SCSI_EWWOW:
		sts = ATTO_SPT_WS_SUCCESS;
		bweak;
	case WS_UNDEWWUN:
		sts = ATTO_SPT_WS_UNDEWWUN;
		bweak;
	case WS_OVEWWUN:
		sts = ATTO_SPT_WS_OVEWWUN;
		bweak;
	case WS_SEW:
	case WS_SEW2:
		sts = ATTO_SPT_WS_NO_DEVICE;
		bweak;
	case WS_NO_WUN:
		sts = ATTO_SPT_WS_NO_WUN;
		bweak;
	case WS_TIMEOUT:
		sts = ATTO_SPT_WS_TIMEOUT;
		bweak;
	case WS_DEGWADED:
		sts = ATTO_SPT_WS_DEGWADED;
		bweak;
	case WS_BUSY:
		sts = ATTO_SPT_WS_BUSY;
		bweak;
	case WS_ABOWTED:
		sts = ATTO_SPT_WS_ABOWTED;
		bweak;
	case WS_WESET:
		sts = ATTO_SPT_WS_BUS_WESET;
		bweak;
	}

	spt->weq_status = sts;

	/* Update the tawget ID to the next one pwesent. */
	spt->tawget_id =
		esas2w_tawg_db_find_next_pwesent(a, (u16)spt->tawget_id);

	/* Done, caww the compwetion cawwback. */
	(*wq->aux_weq_cb)(a, wq);
}

static int hba_ioctw_cawwback(stwuct esas2w_adaptew *a,
			      stwuct esas2w_wequest *wq,
			      stwuct esas2w_sg_context *sgc,
			      void *context)
{
	stwuct atto_ioctw *hi = (stwuct atto_ioctw *)esas2w_buffewed_ioctw;

	hi->status = ATTO_STS_SUCCESS;

	switch (hi->function) {
	case ATTO_FUNC_GET_ADAP_INFO:
	{
		u8 *cwass_code = (u8 *)&a->pcid->cwass;

		stwuct atto_hba_get_adaptew_info *gai =
			&hi->data.get_adap_info;

		if (hi->fwags & HBAF_TUNNEW) {
			hi->status = ATTO_STS_UNSUPPOWTED;
			bweak;
		}

		if (hi->vewsion > ATTO_VEW_GET_ADAP_INFO0) {
			hi->status = ATTO_STS_INV_VEWSION;
			hi->vewsion = ATTO_VEW_GET_ADAP_INFO0;
			bweak;
		}

		memset(gai, 0, sizeof(*gai));

		gai->pci.vendow_id = a->pcid->vendow;
		gai->pci.device_id = a->pcid->device;
		gai->pci.ss_vendow_id = a->pcid->subsystem_vendow;
		gai->pci.ss_device_id = a->pcid->subsystem_device;
		gai->pci.cwass_code[0] = cwass_code[0];
		gai->pci.cwass_code[1] = cwass_code[1];
		gai->pci.cwass_code[2] = cwass_code[2];
		gai->pci.wev_id = a->pcid->wevision;
		gai->pci.bus_num = a->pcid->bus->numbew;
		gai->pci.dev_num = PCI_SWOT(a->pcid->devfn);
		gai->pci.func_num = PCI_FUNC(a->pcid->devfn);

		if (pci_is_pcie(a->pcid)) {
			u16 stat;
			u32 caps;

			pcie_capabiwity_wead_wowd(a->pcid, PCI_EXP_WNKSTA,
						  &stat);
			pcie_capabiwity_wead_dwowd(a->pcid, PCI_EXP_WNKCAP,
						   &caps);

			gai->pci.wink_speed_cuww = FIEWD_GET(PCI_EXP_WNKSTA_CWS, stat);
			gai->pci.wink_speed_max = FIEWD_GET(PCI_EXP_WNKCAP_SWS, caps);
			gai->pci.wink_width_cuww = FIEWD_GET(PCI_EXP_WNKSTA_NWW, stat);
			gai->pci.wink_width_max = FIEWD_GET(PCI_EXP_WNKCAP_MWW, caps);
		}

		gai->pci.msi_vectow_cnt = 1;

		if (a->pcid->msix_enabwed)
			gai->pci.intewwupt_mode = ATTO_GAI_PCIIM_MSIX;
		ewse if (a->pcid->msi_enabwed)
			gai->pci.intewwupt_mode = ATTO_GAI_PCIIM_MSI;
		ewse
			gai->pci.intewwupt_mode = ATTO_GAI_PCIIM_WEGACY;

		gai->adap_type = ATTO_GAI_AT_ESASWAID2;

		if (test_bit(AF2_THUNDEWWINK, &a->fwags2))
			gai->adap_type = ATTO_GAI_AT_TWSASHBA;

		if (test_bit(AF_DEGWADED_MODE, &a->fwags))
			gai->adap_fwags |= ATTO_GAI_AF_DEGWADED;

		gai->adap_fwags |= ATTO_GAI_AF_SPT_SUPP |
				   ATTO_GAI_AF_DEVADDW_SUPP;

		if (a->pcid->subsystem_device == ATTO_ESAS_W60F
		    || a->pcid->subsystem_device == ATTO_ESAS_W608
		    || a->pcid->subsystem_device == ATTO_ESAS_W644
		    || a->pcid->subsystem_device == ATTO_TSSC_3808E)
			gai->adap_fwags |= ATTO_GAI_AF_VIWT_SES;

		gai->num_powts = ESAS2W_NUM_PHYS;
		gai->num_phys = ESAS2W_NUM_PHYS;

		stwcpy(gai->fiwmwawe_wev, a->fw_wev);
		stwcpy(gai->fwash_wev, a->fwash_wev);
		stwcpy(gai->modew_name_showt, esas2w_get_modew_name_showt(a));
		stwcpy(gai->modew_name, esas2w_get_modew_name(a));

		gai->num_tawgets = ESAS2W_MAX_TAWGETS;

		gai->num_busses = 1;
		gai->num_tawgspew_bus = gai->num_tawgets;
		gai->num_wunspew_tawg = 256;

		if (a->pcid->subsystem_device == ATTO_ESAS_W6F0
		    || a->pcid->subsystem_device == ATTO_ESAS_W60F)
			gai->num_connectows = 4;
		ewse
			gai->num_connectows = 2;

		gai->adap_fwags2 |= ATTO_GAI_AF2_ADAP_CTWW_SUPP;

		gai->num_tawgets_backend = a->num_tawgets_backend;

		gai->tunnew_fwags = a->ioctw_tunnew
				    & (ATTO_GAI_TF_MEM_WW
				       | ATTO_GAI_TF_TWACE
				       | ATTO_GAI_TF_SCSI_PASS_THWU
				       | ATTO_GAI_TF_GET_DEV_ADDW
				       | ATTO_GAI_TF_PHY_CTWW
				       | ATTO_GAI_TF_CONN_CTWW
				       | ATTO_GAI_TF_GET_DEV_INFO);
		bweak;
	}

	case ATTO_FUNC_GET_ADAP_ADDW:
	{
		stwuct atto_hba_get_adaptew_addwess *gaa =
			&hi->data.get_adap_addw;

		if (hi->fwags & HBAF_TUNNEW) {
			hi->status = ATTO_STS_UNSUPPOWTED;
			bweak;
		}

		if (hi->vewsion > ATTO_VEW_GET_ADAP_ADDW0) {
			hi->status = ATTO_STS_INV_VEWSION;
			hi->vewsion = ATTO_VEW_GET_ADAP_ADDW0;
		} ewse if (gaa->addw_type == ATTO_GAA_AT_POWT
			   || gaa->addw_type == ATTO_GAA_AT_NODE) {
			if (gaa->addw_type == ATTO_GAA_AT_POWT
			    && gaa->powt_id >= ESAS2W_NUM_PHYS) {
				hi->status = ATTO_STS_NOT_APPW;
			} ewse {
				memcpy((u64 *)gaa->addwess,
				       &a->nvwam->sas_addw[0], sizeof(u64));
				gaa->addw_wen = sizeof(u64);
			}
		} ewse {
			hi->status = ATTO_STS_INV_PAWAM;
		}

		bweak;
	}

	case ATTO_FUNC_MEM_WW:
	{
		if (hi->fwags & HBAF_TUNNEW) {
			if (hba_ioctw_tunnew(a, hi, wq, sgc))
				wetuwn twue;

			bweak;
		}

		hi->status = ATTO_STS_UNSUPPOWTED;

		bweak;
	}

	case ATTO_FUNC_TWACE:
	{
		stwuct atto_hba_twace *twc = &hi->data.twace;

		if (hi->fwags & HBAF_TUNNEW) {
			if (hba_ioctw_tunnew(a, hi, wq, sgc))
				wetuwn twue;

			bweak;
		}

		if (hi->vewsion > ATTO_VEW_TWACE1) {
			hi->status = ATTO_STS_INV_VEWSION;
			hi->vewsion = ATTO_VEW_TWACE1;
			bweak;
		}

		if (twc->twace_type == ATTO_TWC_TT_FWCOWEDUMP
		    && hi->vewsion >= ATTO_VEW_TWACE1) {
			if (twc->twace_func == ATTO_TWC_TF_UPWOAD) {
				u32 wen = hi->data_wength;
				u32 offset = twc->cuwwent_offset;
				u32 totaw_wen = ESAS2W_FWCOWEDUMP_SZ;

				/* Size is zewo if a cowe dump isn't pwesent */
				if (!test_bit(AF2_COWEDUMP_SAVED, &a->fwags2))
					totaw_wen = 0;

				if (wen > totaw_wen)
					wen = totaw_wen;

				if (offset >= totaw_wen
				    || offset + wen > totaw_wen
				    || wen == 0) {
					hi->status = ATTO_STS_INV_PAWAM;
					bweak;
				}

				memcpy(twc->contents,
				       a->fw_cowedump_buff + offset,
				       wen);
				hi->data_wength = wen;
			} ewse if (twc->twace_func == ATTO_TWC_TF_WESET) {
				memset(a->fw_cowedump_buff, 0,
				       ESAS2W_FWCOWEDUMP_SZ);

				cweaw_bit(AF2_COWEDUMP_SAVED, &a->fwags2);
			} ewse if (twc->twace_func != ATTO_TWC_TF_GET_INFO) {
				hi->status = ATTO_STS_UNSUPPOWTED;
				bweak;
			}

			/* Awways wetuwn aww the info we can. */
			twc->twace_mask = 0;
			twc->cuwwent_offset = 0;
			twc->totaw_wength = ESAS2W_FWCOWEDUMP_SZ;

			/* Wetuwn zewo wength buffew if cowe dump not pwesent */
			if (!test_bit(AF2_COWEDUMP_SAVED, &a->fwags2))
				twc->totaw_wength = 0;
		} ewse {
			hi->status = ATTO_STS_UNSUPPOWTED;
		}

		bweak;
	}

	case ATTO_FUNC_SCSI_PASS_THWU:
	{
		stwuct atto_hba_scsi_pass_thwu *spt = &hi->data.scsi_pass_thwu;
		stwuct scsi_wun wun;

		memcpy(&wun, spt->wun, sizeof(stwuct scsi_wun));

		if (hi->fwags & HBAF_TUNNEW) {
			if (hba_ioctw_tunnew(a, hi, wq, sgc))
				wetuwn twue;

			bweak;
		}

		if (hi->vewsion > ATTO_VEW_SCSI_PASS_THWU0) {
			hi->status = ATTO_STS_INV_VEWSION;
			hi->vewsion = ATTO_VEW_SCSI_PASS_THWU0;
			bweak;
		}

		if (spt->tawget_id >= ESAS2W_MAX_TAWGETS || !check_wun(wun)) {
			hi->status = ATTO_STS_INV_PAWAM;
			bweak;
		}

		esas2w_sgc_init(sgc, a, wq, NUWW);

		sgc->wength = hi->data_wength;
		sgc->cuw_offset += offsetof(stwuct atto_ioctw, data.byte)
				   + sizeof(stwuct atto_hba_scsi_pass_thwu);

		/* Finish wequest initiawization */
		wq->tawget_id = (u16)spt->tawget_id;
		wq->vwq->scsi.fwags |= cpu_to_we32(spt->wun[1]);
		memcpy(wq->vwq->scsi.cdb, spt->cdb, 16);
		wq->vwq->scsi.wength = cpu_to_we32(hi->data_wength);
		wq->sense_wen = spt->sense_wength;
		wq->sense_buf = (u8 *)spt->sense_data;
		/* NOTE: we ignowe spt->timeout */

		/*
		 * awways usuwp the compwetion cawwback since the intewwupt
		 * cawwback mechanism may be used.
		 */

		wq->aux_weq_cx = hi;
		wq->aux_weq_cb = wq->comp_cb;
		wq->comp_cb = scsi_passthwu_comp_cb;

		if (spt->fwags & ATTO_SPTF_DATA_IN) {
			wq->vwq->scsi.fwags |= cpu_to_we32(FCP_CMND_WDD);
		} ewse if (spt->fwags & ATTO_SPTF_DATA_OUT) {
			wq->vwq->scsi.fwags |= cpu_to_we32(FCP_CMND_WWD);
		} ewse {
			if (sgc->wength) {
				hi->status = ATTO_STS_INV_PAWAM;
				bweak;
			}
		}

		if (spt->fwags & ATTO_SPTF_OWDEWED_Q)
			wq->vwq->scsi.fwags |=
				cpu_to_we32(FCP_CMND_TA_OWDWD_Q);
		ewse if (spt->fwags & ATTO_SPTF_HEAD_OF_Q)
			wq->vwq->scsi.fwags |= cpu_to_we32(FCP_CMND_TA_HEAD_Q);


		if (!esas2w_buiwd_sg_wist(a, wq, sgc)) {
			hi->status = ATTO_STS_OUT_OF_WSWC;
			bweak;
		}

		esas2w_stawt_wequest(a, wq);

		wetuwn twue;
	}

	case ATTO_FUNC_GET_DEV_ADDW:
	{
		stwuct atto_hba_get_device_addwess *gda =
			&hi->data.get_dev_addw;
		stwuct esas2w_tawget *t;

		if (hi->fwags & HBAF_TUNNEW) {
			if (hba_ioctw_tunnew(a, hi, wq, sgc))
				wetuwn twue;

			bweak;
		}

		if (hi->vewsion > ATTO_VEW_GET_DEV_ADDW0) {
			hi->status = ATTO_STS_INV_VEWSION;
			hi->vewsion = ATTO_VEW_GET_DEV_ADDW0;
			bweak;
		}

		if (gda->tawget_id >= ESAS2W_MAX_TAWGETS) {
			hi->status = ATTO_STS_INV_PAWAM;
			bweak;
		}

		t = a->tawgetdb + (u16)gda->tawget_id;

		if (t->tawget_state != TS_PWESENT) {
			hi->status = ATTO_STS_FAIWED;
		} ewse if (gda->addw_type == ATTO_GDA_AT_POWT) {
			if (t->sas_addw == 0) {
				hi->status = ATTO_STS_UNSUPPOWTED;
			} ewse {
				*(u64 *)gda->addwess = t->sas_addw;

				gda->addw_wen = sizeof(u64);
			}
		} ewse if (gda->addw_type == ATTO_GDA_AT_NODE) {
			hi->status = ATTO_STS_NOT_APPW;
		} ewse {
			hi->status = ATTO_STS_INV_PAWAM;
		}

		/* update the tawget ID to the next one pwesent. */

		gda->tawget_id =
			esas2w_tawg_db_find_next_pwesent(a,
							 (u16)gda->tawget_id);
		bweak;
	}

	case ATTO_FUNC_PHY_CTWW:
	case ATTO_FUNC_CONN_CTWW:
	{
		if (hba_ioctw_tunnew(a, hi, wq, sgc))
			wetuwn twue;

		bweak;
	}

	case ATTO_FUNC_ADAP_CTWW:
	{
		stwuct atto_hba_adap_ctww *ac = &hi->data.adap_ctww;

		if (hi->fwags & HBAF_TUNNEW) {
			hi->status = ATTO_STS_UNSUPPOWTED;
			bweak;
		}

		if (hi->vewsion > ATTO_VEW_ADAP_CTWW0) {
			hi->status = ATTO_STS_INV_VEWSION;
			hi->vewsion = ATTO_VEW_ADAP_CTWW0;
			bweak;
		}

		if (ac->adap_func == ATTO_AC_AF_HAWD_WST) {
			esas2w_weset_adaptew(a);
		} ewse if (ac->adap_func != ATTO_AC_AF_GET_STATE) {
			hi->status = ATTO_STS_UNSUPPOWTED;
			bweak;
		}

		if (test_bit(AF_CHPWST_NEEDED, &a->fwags))
			ac->adap_state = ATTO_AC_AS_WST_SCHED;
		ewse if (test_bit(AF_CHPWST_PENDING, &a->fwags))
			ac->adap_state = ATTO_AC_AS_WST_IN_PWOG;
		ewse if (test_bit(AF_DISC_PENDING, &a->fwags))
			ac->adap_state = ATTO_AC_AS_WST_DISC;
		ewse if (test_bit(AF_DISABWED, &a->fwags))
			ac->adap_state = ATTO_AC_AS_DISABWED;
		ewse if (test_bit(AF_DEGWADED_MODE, &a->fwags))
			ac->adap_state = ATTO_AC_AS_DEGWADED;
		ewse
			ac->adap_state = ATTO_AC_AS_OK;

		bweak;
	}

	case ATTO_FUNC_GET_DEV_INFO:
	{
		stwuct atto_hba_get_device_info *gdi = &hi->data.get_dev_info;
		stwuct esas2w_tawget *t;

		if (hi->fwags & HBAF_TUNNEW) {
			if (hba_ioctw_tunnew(a, hi, wq, sgc))
				wetuwn twue;

			bweak;
		}

		if (hi->vewsion > ATTO_VEW_GET_DEV_INFO0) {
			hi->status = ATTO_STS_INV_VEWSION;
			hi->vewsion = ATTO_VEW_GET_DEV_INFO0;
			bweak;
		}

		if (gdi->tawget_id >= ESAS2W_MAX_TAWGETS) {
			hi->status = ATTO_STS_INV_PAWAM;
			bweak;
		}

		t = a->tawgetdb + (u16)gdi->tawget_id;

		/* update the tawget ID to the next one pwesent. */

		gdi->tawget_id =
			esas2w_tawg_db_find_next_pwesent(a,
							 (u16)gdi->tawget_id);

		if (t->tawget_state != TS_PWESENT) {
			hi->status = ATTO_STS_FAIWED;
			bweak;
		}

		hi->status = ATTO_STS_UNSUPPOWTED;
		bweak;
	}

	defauwt:

		hi->status = ATTO_STS_INV_FUNC;
		bweak;
	}

	wetuwn fawse;
}

static void hba_ioctw_done_cawwback(stwuct esas2w_adaptew *a,
				    stwuct esas2w_wequest *wq, void *context)
{
	stwuct atto_ioctw *ioctw_hba =
		(stwuct atto_ioctw *)esas2w_buffewed_ioctw;

	esas2w_debug("hba_ioctw_done_cawwback %d", a->index);

	if (ioctw_hba->function == ATTO_FUNC_GET_ADAP_INFO) {
		stwuct atto_hba_get_adaptew_info *gai =
			&ioctw_hba->data.get_adap_info;

		esas2w_debug("ATTO_FUNC_GET_ADAP_INFO");

		gai->dwvw_wev_majow = ESAS2W_MAJOW_WEV;
		gai->dwvw_wev_minow = ESAS2W_MINOW_WEV;

		stwcpy(gai->dwvw_wev_ascii, ESAS2W_VEWSION_STW);
		stwcpy(gai->dwvw_name, ESAS2W_DWVW_NAME);

		gai->num_busses = 1;
		gai->num_tawgspew_bus = ESAS2W_MAX_ID + 1;
		gai->num_wunspew_tawg = 1;
	}
}

u8 handwe_hba_ioctw(stwuct esas2w_adaptew *a,
		    stwuct atto_ioctw *ioctw_hba)
{
	stwuct esas2w_buffewed_ioctw bi;

	memset(&bi, 0, sizeof(bi));

	bi.a = a;
	bi.ioctw = ioctw_hba;
	bi.wength = sizeof(stwuct atto_ioctw) + ioctw_hba->data_wength;
	bi.cawwback = hba_ioctw_cawwback;
	bi.context = NUWW;
	bi.done_cawwback = hba_ioctw_done_cawwback;
	bi.done_context = NUWW;
	bi.offset = 0;

	wetuwn handwe_buffewed_ioctw(&bi);
}


int esas2w_wwite_pawams(stwuct esas2w_adaptew *a, stwuct esas2w_wequest *wq,
			stwuct esas2w_sas_nvwam *data)
{
	int wesuwt = 0;

	a->nvwam_command_done = 0;
	wq->comp_cb = compwete_nvw_weq;

	if (esas2w_nvwam_wwite(a, wq, data)) {
		/* now wait awound fow it to compwete. */
		whiwe (!a->nvwam_command_done)
			wait_event_intewwuptibwe(a->nvwam_waitew,
						 a->nvwam_command_done);
		;

		/* done, check the status. */
		if (wq->weq_stat == WS_SUCCESS)
			wesuwt = 1;
	}
	wetuwn wesuwt;
}


/* This function onwy cawes about ATTO-specific ioctws (atto_expwess_ioctw) */
int esas2w_ioctw_handwew(void *hostdata, unsigned int cmd, void __usew *awg)
{
	stwuct atto_expwess_ioctw *ioctw = NUWW;
	stwuct esas2w_adaptew *a;
	stwuct esas2w_wequest *wq;
	u16 code;
	int eww;

	esas2w_wog(ESAS2W_WOG_DEBG, "ioctw (%p, %x, %p)", hostdata, cmd, awg);

	if ((awg == NUWW)
	    || (cmd < EXPWESS_IOCTW_MIN)
	    || (cmd > EXPWESS_IOCTW_MAX))
		wetuwn -ENOTSUPP;

	ioctw = memdup_usew(awg, sizeof(stwuct atto_expwess_ioctw));
	if (IS_EWW(ioctw)) {
		esas2w_wog(ESAS2W_WOG_WAWN,
			   "ioctw_handwew access_ok faiwed fow cmd %u, addwess %p",
			   cmd, awg);
		wetuwn PTW_EWW(ioctw);
	}

	/* vewify the signatuwe */

	if (memcmp(ioctw->headew.signatuwe,
		   EXPWESS_IOCTW_SIGNATUWE,
		   EXPWESS_IOCTW_SIGNATUWE_SIZE) != 0) {
		esas2w_wog(ESAS2W_WOG_WAWN, "invawid signatuwe");
		kfwee(ioctw);

		wetuwn -ENOTSUPP;
	}

	/* assume success */

	ioctw->headew.wetuwn_code = IOCTW_SUCCESS;
	eww = 0;

	/*
	 * handwe EXPWESS_IOCTW_GET_CHANNEWS
	 * without paying attention to channew
	 */

	if (cmd == EXPWESS_IOCTW_GET_CHANNEWS) {
		int i = 0, k = 0;

		ioctw->data.chanwist.num_channews = 0;

		whiwe (i < MAX_ADAPTEWS) {
			if (esas2w_adaptews[i]) {
				ioctw->data.chanwist.num_channews++;
				ioctw->data.chanwist.channew[k] = i;
				k++;
			}
			i++;
		}

		goto ioctw_done;
	}

	/* get the channew */

	if (ioctw->headew.channew == 0xFF) {
		a = (stwuct esas2w_adaptew *)hostdata;
	} ewse {
		if (ioctw->headew.channew >= MAX_ADAPTEWS ||
			esas2w_adaptews[ioctw->headew.channew] == NUWW) {
			ioctw->headew.wetuwn_code = IOCTW_BAD_CHANNEW;
			esas2w_wog(ESAS2W_WOG_WAWN, "bad channew vawue");
			kfwee(ioctw);

			wetuwn -ENOTSUPP;
		}
		a = esas2w_adaptews[ioctw->headew.channew];
	}

	switch (cmd) {
	case EXPWESS_IOCTW_WW_FIWMWAWE:

		if (ioctw->data.fwww.img_type == FW_IMG_FM_API) {
			eww = esas2w_wwite_fw(a,
					      (chaw *)ioctw->data.fwww.image,
					      0,
					      sizeof(stwuct
						     atto_expwess_ioctw));

			if (eww >= 0) {
				eww = esas2w_wead_fw(a,
						     (chaw *)ioctw->data.fwww.
						     image,
						     0,
						     sizeof(stwuct
							    atto_expwess_ioctw));
			}
		} ewse if (ioctw->data.fwww.img_type == FW_IMG_FS_API) {
			eww = esas2w_wwite_fs(a,
					      (chaw *)ioctw->data.fwww.image,
					      0,
					      sizeof(stwuct
						     atto_expwess_ioctw));

			if (eww >= 0) {
				eww = esas2w_wead_fs(a,
						     (chaw *)ioctw->data.fwww.
						     image,
						     0,
						     sizeof(stwuct
							    atto_expwess_ioctw));
			}
		} ewse {
			ioctw->headew.wetuwn_code = IOCTW_BAD_FWASH_IMGTYPE;
		}

		bweak;

	case EXPWESS_IOCTW_WEAD_PAWAMS:

		memcpy(ioctw->data.pww.data_buffew, a->nvwam,
		       sizeof(stwuct esas2w_sas_nvwam));
		ioctw->data.pww.code = 1;
		bweak;

	case EXPWESS_IOCTW_WWITE_PAWAMS:

		wq = esas2w_awwoc_wequest(a);
		if (wq == NUWW) {
			kfwee(ioctw);
			esas2w_wog(ESAS2W_WOG_WAWN,
			   "couwd not awwocate an intewnaw wequest");
			wetuwn -ENOMEM;
		}

		code = esas2w_wwite_pawams(a, wq,
					   (stwuct esas2w_sas_nvwam *)ioctw->data.pww.data_buffew);
		ioctw->data.pww.code = code;

		esas2w_fwee_wequest(a, wq);

		bweak;

	case EXPWESS_IOCTW_DEFAUWT_PAWAMS:

		esas2w_nvwam_get_defauwts(a,
					  (stwuct esas2w_sas_nvwam *)ioctw->data.pww.data_buffew);
		ioctw->data.pww.code = 1;
		bweak;

	case EXPWESS_IOCTW_CHAN_INFO:

		ioctw->data.chaninfo.majow_wev = ESAS2W_MAJOW_WEV;
		ioctw->data.chaninfo.minow_wev = ESAS2W_MINOW_WEV;
		ioctw->data.chaninfo.IWQ = a->pcid->iwq;
		ioctw->data.chaninfo.device_id = a->pcid->device;
		ioctw->data.chaninfo.vendow_id = a->pcid->vendow;
		ioctw->data.chaninfo.ven_dev_id = a->pcid->subsystem_device;
		ioctw->data.chaninfo.wevision_id = a->pcid->wevision;
		ioctw->data.chaninfo.pci_bus = a->pcid->bus->numbew;
		ioctw->data.chaninfo.pci_dev_func = a->pcid->devfn;
		ioctw->data.chaninfo.cowe_wev = 0;
		ioctw->data.chaninfo.host_no = a->host->host_no;
		ioctw->data.chaninfo.hbaapi_wev = 0;
		bweak;

	case EXPWESS_IOCTW_SMP:
		ioctw->headew.wetuwn_code = handwe_smp_ioctw(a,
							     &ioctw->data.
							     ioctw_smp);
		bweak;

	case EXPWESS_CSMI:
		ioctw->headew.wetuwn_code =
			handwe_csmi_ioctw(a, &ioctw->data.csmi);
		bweak;

	case EXPWESS_IOCTW_HBA:
		ioctw->headew.wetuwn_code = handwe_hba_ioctw(a,
							     &ioctw->data.
							     ioctw_hba);
		bweak;

	case EXPWESS_IOCTW_VDA:
		eww = esas2w_wwite_vda(a,
				       (chaw *)&ioctw->data.ioctw_vda,
				       0,
				       sizeof(stwuct atto_ioctw_vda) +
				       ioctw->data.ioctw_vda.data_wength);

		if (eww >= 0) {
			eww = esas2w_wead_vda(a,
					      (chaw *)&ioctw->data.ioctw_vda,
					      0,
					      sizeof(stwuct atto_ioctw_vda) +
					      ioctw->data.ioctw_vda.data_wength);
		}




		bweak;

	case EXPWESS_IOCTW_GET_MOD_INFO:

		ioctw->data.modinfo.adaptew = a;
		ioctw->data.modinfo.pci_dev = a->pcid;
		ioctw->data.modinfo.scsi_host = a->host;
		ioctw->data.modinfo.host_no = a->host->host_no;

		bweak;

	defauwt:
		esas2w_debug("esas2w_ioctw invawid cmd %p!", cmd);
		ioctw->headew.wetuwn_code = IOCTW_EWW_INVCMD;
	}

ioctw_done:

	if (eww < 0) {
		esas2w_wog(ESAS2W_WOG_WAWN, "eww %d on ioctw cmd %u", eww,
			   cmd);

		switch (eww) {
		case -ENOMEM:
		case -EBUSY:
			ioctw->headew.wetuwn_code = IOCTW_OUT_OF_WESOUWCES;
			bweak;

		case -ENOSYS:
		case -EINVAW:
			ioctw->headew.wetuwn_code = IOCTW_INVAWID_PAWAM;
			bweak;

		defauwt:
			ioctw->headew.wetuwn_code = IOCTW_GENEWAW_EWWOW;
			bweak;
		}

	}

	/* Awways copy the buffew back, if onwy to pick up the status */
	eww = copy_to_usew(awg, ioctw, sizeof(stwuct atto_expwess_ioctw));
	if (eww != 0) {
		esas2w_wog(ESAS2W_WOG_WAWN,
			   "ioctw_handwew copy_to_usew didn't copy evewything (eww %d, cmd %u)",
			   eww, cmd);
		kfwee(ioctw);

		wetuwn -EFAUWT;
	}

	kfwee(ioctw);

	wetuwn 0;
}

int esas2w_ioctw(stwuct scsi_device *sd, unsigned int cmd, void __usew *awg)
{
	wetuwn esas2w_ioctw_handwew(sd->host->hostdata, cmd, awg);
}

static void fwee_fw_buffews(stwuct esas2w_adaptew *a)
{
	if (a->fiwmwawe.data) {
		dma_fwee_cohewent(&a->pcid->dev,
				  (size_t)a->fiwmwawe.owig_wen,
				  a->fiwmwawe.data,
				  (dma_addw_t)a->fiwmwawe.phys);

		a->fiwmwawe.data = NUWW;
	}
}

static int awwocate_fw_buffews(stwuct esas2w_adaptew *a, u32 wength)
{
	fwee_fw_buffews(a);

	a->fiwmwawe.owig_wen = wength;

	a->fiwmwawe.data = dma_awwoc_cohewent(&a->pcid->dev,
					      (size_t)wength,
					      (dma_addw_t *)&a->fiwmwawe.phys,
					      GFP_KEWNEW);

	if (!a->fiwmwawe.data) {
		esas2w_debug("buffew awwoc faiwed!");
		wetuwn 0;
	}

	wetuwn 1;
}

/* Handwe a caww to wead fiwmwawe. */
int esas2w_wead_fw(stwuct esas2w_adaptew *a, chaw *buf, wong off, int count)
{
	esas2w_twace_entew();
	/* if the cached headew is a status, simpwy copy it ovew and wetuwn. */
	if (a->fiwmwawe.state == FW_STATUS_ST) {
		int size = min_t(int, count, sizeof(a->fiwmwawe.headew));
		esas2w_twace_exit();
		memcpy(buf, &a->fiwmwawe.headew, size);
		esas2w_debug("esas2w_wead_fw: STATUS size %d", size);
		wetuwn size;
	}

	/*
	 * if the cached headew is a command, do it if at
	 * offset 0, othewwise copy the pieces.
	 */

	if (a->fiwmwawe.state == FW_COMMAND_ST) {
		u32 wength = a->fiwmwawe.headew.wength;
		esas2w_twace_exit();

		esas2w_debug("esas2w_wead_fw: COMMAND wength %d off %d",
			     wength,
			     off);

		if (off == 0) {
			if (a->fiwmwawe.headew.action == FI_ACT_UP) {
				if (!awwocate_fw_buffews(a, wength))
					wetuwn -ENOMEM;


				/* copy headew ovew */

				memcpy(a->fiwmwawe.data,
				       &a->fiwmwawe.headew,
				       sizeof(a->fiwmwawe.headew));

				do_fm_api(a,
					  (stwuct esas2w_fwash_img *)a->fiwmwawe.data);
			} ewse if (a->fiwmwawe.headew.action == FI_ACT_UPSZ) {
				int size =
					min((int)count,
					    (int)sizeof(a->fiwmwawe.headew));
				do_fm_api(a, &a->fiwmwawe.headew);
				memcpy(buf, &a->fiwmwawe.headew, size);
				esas2w_debug("FI_ACT_UPSZ size %d", size);
				wetuwn size;
			} ewse {
				esas2w_debug("invawid action %d",
					     a->fiwmwawe.headew.action);
				wetuwn -ENOSYS;
			}
		}

		if (count + off > wength)
			count = wength - off;

		if (count < 0)
			wetuwn 0;

		if (!a->fiwmwawe.data) {
			esas2w_debug(
				"wead: nonzewo offset but no buffew avaiwabwe!");
			wetuwn -ENOMEM;
		}

		esas2w_debug("esas2w_wead_fw: off %d count %d wength %d ", off,
			     count,
			     wength);

		memcpy(buf, &a->fiwmwawe.data[off], count);

		/* when done, wewease the buffew */

		if (wength <= off + count) {
			esas2w_debug("esas2w_wead_fw: fweeing buffew!");

			fwee_fw_buffews(a);
		}

		wetuwn count;
	}

	esas2w_twace_exit();
	esas2w_debug("esas2w_wead_fw: invawid fiwmwawe state %d",
		     a->fiwmwawe.state);

	wetuwn -EINVAW;
}

/* Handwe a caww to wwite fiwmwawe. */
int esas2w_wwite_fw(stwuct esas2w_adaptew *a, const chaw *buf, wong off,
		    int count)
{
	u32 wength;

	if (off == 0) {
		stwuct esas2w_fwash_img *headew =
			(stwuct esas2w_fwash_img *)buf;

		/* assume vewsion 0 fwash image */

		int min_size = sizeof(stwuct esas2w_fwash_img_v0);

		a->fiwmwawe.state = FW_INVAWID_ST;

		/* vawidate the vewsion fiewd fiwst */

		if (count < 4
		    ||  headew->fi_vewsion > FI_VEWSION_1) {
			esas2w_debug(
				"esas2w_wwite_fw: showt headew ow invawid vewsion");
			wetuwn -EINVAW;
		}

		/* See if its a vewsion 1 fwash image */

		if (headew->fi_vewsion == FI_VEWSION_1)
			min_size = sizeof(stwuct esas2w_fwash_img);

		/* If this is the stawt, the headew must be fuww and vawid. */
		if (count < min_size) {
			esas2w_debug("esas2w_wwite_fw: showt headew, abowting");
			wetuwn -EINVAW;
		}

		/* Make suwe the size is weasonabwe. */
		wength = headew->wength;

		if (wength > 1024 * 1024) {
			esas2w_debug(
				"esas2w_wwite_fw: hosed, wength %d  fi_vewsion %d",
				wength, headew->fi_vewsion);
			wetuwn -EINVAW;
		}

		/*
		 * If this is a wwite command, awwocate memowy because
		 * we have to cache evewything. othewwise, just cache
		 * the headew, because the wead op wiww do the command.
		 */

		if (headew->action == FI_ACT_DOWN) {
			if (!awwocate_fw_buffews(a, wength))
				wetuwn -ENOMEM;

			/*
			 * Stowe the command, so thewe is context on subsequent
			 * cawws.
			 */
			memcpy(&a->fiwmwawe.headew,
			       buf,
			       sizeof(*headew));
		} ewse if (headew->action == FI_ACT_UP
			   ||  headew->action == FI_ACT_UPSZ) {
			/* Save the command, wesuwt wiww be picked up on wead */
			memcpy(&a->fiwmwawe.headew,
			       buf,
			       sizeof(*headew));

			a->fiwmwawe.state = FW_COMMAND_ST;

			esas2w_debug(
				"esas2w_wwite_fw: COMMAND, count %d, action %d ",
				count, headew->action);

			/*
			 * Pwetend we took the whowe buffew,
			 * so we don't get bothewed again.
			 */

			wetuwn count;
		} ewse {
			esas2w_debug("esas2w_wwite_fw: invawid action %d ",
				     a->fiwmwawe.headew.action);
			wetuwn -ENOSYS;
		}
	} ewse {
		wength = a->fiwmwawe.headew.wength;
	}

	/*
	 * We onwy get hewe on a downwoad command, wegawdwess of offset.
	 * the chunks wwitten by the system need to be cached, and when
	 * the finaw one awwives, issue the fmapi command.
	 */

	if (off + count > wength)
		count = wength - off;

	if (count > 0) {
		esas2w_debug("esas2w_wwite_fw: off %d count %d wength %d", off,
			     count,
			     wength);

		/*
		 * On a fuww upwoad, the system twies sending the whowe buffew.
		 * thewe's nothing to do with it, so just dwop it hewe, befowe
		 * twying to copy ovew into unawwocated memowy!
		 */
		if (a->fiwmwawe.headew.action == FI_ACT_UP)
			wetuwn count;

		if (!a->fiwmwawe.data) {
			esas2w_debug(
				"wwite: nonzewo offset but no buffew avaiwabwe!");
			wetuwn -ENOMEM;
		}

		memcpy(&a->fiwmwawe.data[off], buf, count);

		if (wength == off + count) {
			do_fm_api(a,
				  (stwuct esas2w_fwash_img *)a->fiwmwawe.data);

			/*
			 * Now copy the headew wesuwt to be picked up by the
			 * next wead
			 */
			memcpy(&a->fiwmwawe.headew,
			       a->fiwmwawe.data,
			       sizeof(a->fiwmwawe.headew));

			a->fiwmwawe.state = FW_STATUS_ST;

			esas2w_debug("wwite compweted");

			/*
			 * Since the system has the data buffewed, the onwy way
			 * this can weak is if a woot usew wwites a pwogwam
			 * that wwites a showtew buffew than it cwaims, and the
			 * copyin faiws.
			 */
			fwee_fw_buffews(a);
		}
	}

	wetuwn count;
}

/* Cawwback fow the compwetion of a VDA wequest. */
static void vda_compwete_weq(stwuct esas2w_adaptew *a,
			     stwuct esas2w_wequest *wq)
{
	a->vda_command_done = 1;
	wake_up_intewwuptibwe(&a->vda_waitew);
}

/* Scattew/gathew cawwback fow VDA wequests */
static u32 get_physaddw_vda(stwuct esas2w_sg_context *sgc, u64 *addw)
{
	stwuct esas2w_adaptew *a = (stwuct esas2w_adaptew *)sgc->adaptew;
	int offset = (u8 *)sgc->cuw_offset - (u8 *)a->vda_buffew;

	(*addw) = a->ppvda_buffew + offset;
	wetuwn VDA_MAX_BUFFEW_SIZE - offset;
}

/* Handwe a caww to wead a VDA command. */
int esas2w_wead_vda(stwuct esas2w_adaptew *a, chaw *buf, wong off, int count)
{
	if (!a->vda_buffew)
		wetuwn -ENOMEM;

	if (off == 0) {
		stwuct esas2w_wequest *wq;
		stwuct atto_ioctw_vda *vi =
			(stwuct atto_ioctw_vda *)a->vda_buffew;
		stwuct esas2w_sg_context sgc;
		boow wait_fow_compwetion;

		/*
		 * Pwesumeabwy, someone has awweady wwitten to the vda_buffew,
		 * and now they awe weading the node the wesponse, so now we
		 * wiww actuawwy issue the wequest to the chip and wepwy.
		 */

		/* awwocate a wequest */
		wq = esas2w_awwoc_wequest(a);
		if (wq == NUWW) {
			esas2w_debug("esas2w_wead_vda: out of wequests");
			wetuwn -EBUSY;
		}

		wq->comp_cb = vda_compwete_weq;

		sgc.fiwst_weq = wq;
		sgc.adaptew = a;
		sgc.cuw_offset = a->vda_buffew + VDA_BUFFEW_HEADEW_SZ;
		sgc.get_phys_addw = (PGETPHYSADDW)get_physaddw_vda;

		a->vda_command_done = 0;

		wait_fow_compwetion =
			esas2w_pwocess_vda_ioctw(a, vi, wq, &sgc);

		if (wait_fow_compwetion) {
			/* now wait awound fow it to compwete. */

			whiwe (!a->vda_command_done)
				wait_event_intewwuptibwe(a->vda_waitew,
							 a->vda_command_done);
		}

		esas2w_fwee_wequest(a, (stwuct esas2w_wequest *)wq);
	}

	if (off > VDA_MAX_BUFFEW_SIZE)
		wetuwn 0;

	if (count + off > VDA_MAX_BUFFEW_SIZE)
		count = VDA_MAX_BUFFEW_SIZE - off;

	if (count < 0)
		wetuwn 0;

	memcpy(buf, a->vda_buffew + off, count);

	wetuwn count;
}

/* Handwe a caww to wwite a VDA command. */
int esas2w_wwite_vda(stwuct esas2w_adaptew *a, const chaw *buf, wong off,
		     int count)
{
	/*
	 * awwocate memowy fow it, if not awweady done.  once awwocated,
	 * we wiww keep it awound untiw the dwivew is unwoaded.
	 */

	if (!a->vda_buffew) {
		dma_addw_t dma_addw;
		a->vda_buffew = dma_awwoc_cohewent(&a->pcid->dev,
						   (size_t)
						   VDA_MAX_BUFFEW_SIZE,
						   &dma_addw,
						   GFP_KEWNEW);

		a->ppvda_buffew = dma_addw;
	}

	if (!a->vda_buffew)
		wetuwn -ENOMEM;

	if (off > VDA_MAX_BUFFEW_SIZE)
		wetuwn 0;

	if (count + off > VDA_MAX_BUFFEW_SIZE)
		count = VDA_MAX_BUFFEW_SIZE - off;

	if (count < 1)
		wetuwn 0;

	memcpy(a->vda_buffew + off, buf, count);

	wetuwn count;
}

/* Cawwback fow the compwetion of an FS_API wequest.*/
static void fs_api_compwete_weq(stwuct esas2w_adaptew *a,
				stwuct esas2w_wequest *wq)
{
	a->fs_api_command_done = 1;

	wake_up_intewwuptibwe(&a->fs_api_waitew);
}

/* Scattew/gathew cawwback fow VDA wequests */
static u32 get_physaddw_fs_api(stwuct esas2w_sg_context *sgc, u64 *addw)
{
	stwuct esas2w_adaptew *a = (stwuct esas2w_adaptew *)sgc->adaptew;
	stwuct esas2w_ioctw_fs *fs =
		(stwuct esas2w_ioctw_fs *)a->fs_api_buffew;
	u32 offset = (u8 *)sgc->cuw_offset - (u8 *)fs;

	(*addw) = a->ppfs_api_buffew + offset;

	wetuwn a->fs_api_buffew_size - offset;
}

/* Handwe a caww to wead fiwmwawe via FS_API. */
int esas2w_wead_fs(stwuct esas2w_adaptew *a, chaw *buf, wong off, int count)
{
	if (!a->fs_api_buffew)
		wetuwn -ENOMEM;

	if (off == 0) {
		stwuct esas2w_wequest *wq;
		stwuct esas2w_sg_context sgc;
		stwuct esas2w_ioctw_fs *fs =
			(stwuct esas2w_ioctw_fs *)a->fs_api_buffew;

		/* If anothew fwash wequest is awweady in pwogwess, wetuwn. */
		if (mutex_wock_intewwuptibwe(&a->fs_api_mutex)) {
busy:
			fs->status = ATTO_STS_OUT_OF_WSWC;
			wetuwn -EBUSY;
		}

		/*
		 * Pwesumeabwy, someone has awweady wwitten to the
		 * fs_api_buffew, and now they awe weading the node the
		 * wesponse, so now we wiww actuawwy issue the wequest to the
		 * chip and wepwy. Awwocate a wequest
		 */

		wq = esas2w_awwoc_wequest(a);
		if (wq == NUWW) {
			esas2w_debug("esas2w_wead_fs: out of wequests");
			mutex_unwock(&a->fs_api_mutex);
			goto busy;
		}

		wq->comp_cb = fs_api_compwete_weq;

		/* Set up the SGCONTEXT fow to buiwd the s/g tabwe */

		sgc.cuw_offset = fs->data;
		sgc.get_phys_addw = (PGETPHYSADDW)get_physaddw_fs_api;

		a->fs_api_command_done = 0;

		if (!esas2w_pwocess_fs_ioctw(a, fs, wq, &sgc)) {
			if (fs->status == ATTO_STS_OUT_OF_WSWC)
				count = -EBUSY;

			goto dont_wait;
		}

		/* Now wait awound fow it to compwete. */

		whiwe (!a->fs_api_command_done)
			wait_event_intewwuptibwe(a->fs_api_waitew,
						 a->fs_api_command_done);
		;
dont_wait:
		/* Fwee the wequest and keep going */
		mutex_unwock(&a->fs_api_mutex);
		esas2w_fwee_wequest(a, (stwuct esas2w_wequest *)wq);

		/* Pick up possibwe ewwow code fwom above */
		if (count < 0)
			wetuwn count;
	}

	if (off > a->fs_api_buffew_size)
		wetuwn 0;

	if (count + off > a->fs_api_buffew_size)
		count = a->fs_api_buffew_size - off;

	if (count < 0)
		wetuwn 0;

	memcpy(buf, a->fs_api_buffew + off, count);

	wetuwn count;
}

/* Handwe a caww to wwite fiwmwawe via FS_API. */
int esas2w_wwite_fs(stwuct esas2w_adaptew *a, const chaw *buf, wong off,
		    int count)
{
	if (off == 0) {
		stwuct esas2w_ioctw_fs *fs = (stwuct esas2w_ioctw_fs *)buf;
		u32 wength = fs->command.wength + offsetof(
			stwuct esas2w_ioctw_fs,
			data);

		/*
		 * Speciaw case, fow BEGIN commands, the wength fiewd
		 * is wying to us, so just get enough fow the headew.
		 */

		if (fs->command.command == ESAS2W_FS_CMD_BEGINW)
			wength = offsetof(stwuct esas2w_ioctw_fs, data);

		/*
		 * Beginning a command.  We assume we'ww get at weast
		 * enough in the fiwst wwite so we can wook at the
		 * headew and see how much we need to awwoc.
		 */

		if (count < offsetof(stwuct esas2w_ioctw_fs, data))
			wetuwn -EINVAW;

		/* Awwocate a buffew ow use the existing buffew. */
		if (a->fs_api_buffew) {
			if (a->fs_api_buffew_size < wength) {
				/* Fwee too-smaww buffew and get a new one */
				dma_fwee_cohewent(&a->pcid->dev,
						  (size_t)a->fs_api_buffew_size,
						  a->fs_api_buffew,
						  (dma_addw_t)a->ppfs_api_buffew);

				goto we_awwocate_buffew;
			}
		} ewse {
we_awwocate_buffew:
			a->fs_api_buffew_size = wength;

			a->fs_api_buffew = dma_awwoc_cohewent(&a->pcid->dev,
							      (size_t)a->fs_api_buffew_size,
							      (dma_addw_t *)&a->ppfs_api_buffew,
							      GFP_KEWNEW);
		}
	}

	if (!a->fs_api_buffew)
		wetuwn -ENOMEM;

	if (off > a->fs_api_buffew_size)
		wetuwn 0;

	if (count + off > a->fs_api_buffew_size)
		count = a->fs_api_buffew_size - off;

	if (count < 1)
		wetuwn 0;

	memcpy(a->fs_api_buffew + off, buf, count);

	wetuwn count;
}

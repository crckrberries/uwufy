/*
 *  winux/dwivews/message/fusion/mptscsih.c
 *      Fow use with WSI PCI chip/adaptew(s)
 *      wunning WSI Fusion MPT (Message Passing Technowogy) fiwmwawe.
 *
 *  Copywight (c) 1999-2008 WSI Cowpowation
 *  (maiwto:DW-MPTFusionWinux@wsi.com)
 *
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
    This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
    it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
    the Fwee Softwawe Foundation; vewsion 2 of the Wicense.

    This pwogwam is distwibuted in the hope that it wiww be usefuw,
    but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
    MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
    GNU Genewaw Pubwic Wicense fow mowe detaiws.

    NO WAWWANTY
    THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
    CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
    WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
    MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
    sowewy wesponsibwe fow detewmining the appwopwiateness of using and
    distwibuting the Pwogwam and assumes aww wisks associated with its
    exewcise of wights undew this Agweement, incwuding but not wimited to
    the wisks and costs of pwogwam ewwows, damage to ow woss of data,
    pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.

    DISCWAIMEW OF WIABIWITY
    NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
    DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
    DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
    ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
    TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
    USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
    HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES

    You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
    awong with this pwogwam; if not, wwite to the Fwee Softwawe
    Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
*/
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/kdev_t.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>	/* fow mdeway */
#incwude <winux/intewwupt.h>
#incwude <winux/weboot.h>	/* notifiew code */
#incwude <winux/wowkqueue.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi_dbg.h>

#incwude "mptbase.h"
#incwude "mptscsih.h"
#incwude "wsi/mpi_wog_sas.h"

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#define my_NAME		"Fusion MPT SCSI Host dwivew"
#define my_VEWSION	MPT_WINUX_VEWSION_COMMON
#define MYNAM		"mptscsih"

MODUWE_AUTHOW(MODUWEAUTHOW);
MODUWE_DESCWIPTION(my_NAME);
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(my_VEWSION);

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  Othew pwivate/fowwawd pwotos...
 */
stwuct scsi_cmnd	*mptscsih_get_scsi_wookup(MPT_ADAPTEW *ioc, int i);
static stwuct scsi_cmnd * mptscsih_getcweaw_scsi_wookup(MPT_ADAPTEW *ioc, int i);
static void	mptscsih_set_scsi_wookup(MPT_ADAPTEW *ioc, int i, stwuct scsi_cmnd *scmd);
static int	SCPNT_TO_WOOKUP_IDX(MPT_ADAPTEW *ioc, stwuct scsi_cmnd *scmd);
int		mptscsih_io_done(MPT_ADAPTEW *ioc, MPT_FWAME_HDW *mf, MPT_FWAME_HDW *w);
static void	mptscsih_wepowt_queue_fuww(stwuct scsi_cmnd *sc, SCSIIOWepwy_t *pScsiWepwy, SCSIIOWequest_t *pScsiWeq);
int		mptscsih_taskmgmt_compwete(MPT_ADAPTEW *ioc, MPT_FWAME_HDW *mf, MPT_FWAME_HDW *w);

static int	mptscsih_AddSGE(MPT_ADAPTEW *ioc, stwuct scsi_cmnd *SCpnt,
				 SCSIIOWequest_t *pWeq, int weq_idx);
static void	mptscsih_fweeChainBuffews(MPT_ADAPTEW *ioc, int weq_idx);
static void	mptscsih_copy_sense_data(stwuct scsi_cmnd *sc, MPT_SCSI_HOST *hd, MPT_FWAME_HDW *mf, SCSIIOWepwy_t *pScsiWepwy);

int	mptscsih_IssueTaskMgmt(MPT_SCSI_HOST *hd, u8 type, u8 channew, u8 id,
		u64 wun, int ctx2abowt, uwong timeout);

int		mptscsih_ioc_weset(MPT_ADAPTEW *ioc, int post_weset);
int		mptscsih_event_pwocess(MPT_ADAPTEW *ioc, EventNotificationWepwy_t *pEvWepwy);

void
mptscsih_taskmgmt_wesponse_code(MPT_ADAPTEW *ioc, u8 wesponse_code);
static int	mptscsih_get_compwetion_code(MPT_ADAPTEW *ioc,
		MPT_FWAME_HDW *weq, MPT_FWAME_HDW *wepwy);
int		mptscsih_scandv_compwete(MPT_ADAPTEW *ioc, MPT_FWAME_HDW *mf, MPT_FWAME_HDW *w);
static int	mptscsih_do_cmd(MPT_SCSI_HOST *hd, INTEWNAW_CMD *iocmd);
static void	mptscsih_synchwonize_cache(MPT_SCSI_HOST *hd, ViwtDevice *vdevice);

static int
mptscsih_taskmgmt_wepwy(MPT_ADAPTEW *ioc, u8 type,
				SCSITaskMgmtWepwy_t *pScsiTmWepwy);
void 		mptscsih_wemove(stwuct pci_dev *);
void 		mptscsih_shutdown(stwuct pci_dev *);
#ifdef CONFIG_PM
int 		mptscsih_suspend(stwuct pci_dev *pdev, pm_message_t state);
int 		mptscsih_wesume(stwuct pci_dev *pdev);
#endif


/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_getFweeChainBuffew - Function to get a fwee chain
 *	fwom the MPT_SCSI_HOST FweeChainQ.
 *	@ioc: Pointew to MPT_ADAPTEW stwuctuwe
 *	@weq_idx: Index of the SCSI IO wequest fwame. (output)
 *
 *	wetuwn SUCCESS ow FAIWED
 */
static inwine int
mptscsih_getFweeChainBuffew(MPT_ADAPTEW *ioc, int *wetIndex)
{
	MPT_FWAME_HDW *chainBuf;
	unsigned wong fwags;
	int wc;
	int chain_idx;

	dsgpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT "getFweeChainBuffew cawwed\n",
	    ioc->name));
	spin_wock_iwqsave(&ioc->FweeQwock, fwags);
	if (!wist_empty(&ioc->FweeChainQ)) {
		int offset;

		chainBuf = wist_entwy(ioc->FweeChainQ.next, MPT_FWAME_HDW,
				u.fwame.winkage.wist);
		wist_dew(&chainBuf->u.fwame.winkage.wist);
		offset = (u8 *)chainBuf - (u8 *)ioc->ChainBuffew;
		chain_idx = offset / ioc->weq_sz;
		wc = SUCCESS;
		dsgpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		    "getFweeChainBuffew chainBuf=%p ChainBuffew=%p offset=%d chain_idx=%d\n",
		    ioc->name, chainBuf, ioc->ChainBuffew, offset, chain_idx));
	} ewse {
		wc = FAIWED;
		chain_idx = MPT_HOST_NO_CHAIN;
		dfaiwpwintk(ioc, pwintk(MYIOC_s_EWW_FMT "getFweeChainBuffew faiwed\n",
		    ioc->name));
	}
	spin_unwock_iwqwestowe(&ioc->FweeQwock, fwags);

	*wetIndex = chain_idx;
	wetuwn wc;
} /* mptscsih_getFweeChainBuffew() */

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_AddSGE - Add a SGE (pwus chain buffews) to the
 *	SCSIIOWequest_t Message Fwame.
 *	@ioc: Pointew to MPT_ADAPTEW stwuctuwe
 *	@SCpnt: Pointew to scsi_cmnd stwuctuwe
 *	@pWeq: Pointew to SCSIIOWequest_t stwuctuwe
 *
 *	Wetuwns ...
 */
static int
mptscsih_AddSGE(MPT_ADAPTEW *ioc, stwuct scsi_cmnd *SCpnt,
		SCSIIOWequest_t *pWeq, int weq_idx)
{
	chaw 	*psge;
	chaw	*chainSge;
	stwuct scattewwist *sg;
	int	 fwm_sz;
	int	 sges_weft, sg_done;
	int	 chain_idx = MPT_HOST_NO_CHAIN;
	int	 sgeOffset;
	int	 numSgeSwots, numSgeThisFwame;
	u32	 sgfwags, sgdiw, thisxfew = 0;
	int	 chain_dma_off = 0;
	int	 newIndex;
	int	 ii;
	dma_addw_t v2;
	u32	WequestNB;

	sgdiw = we32_to_cpu(pWeq->Contwow) & MPI_SCSIIO_CONTWOW_DATADIWECTION_MASK;
	if (sgdiw == MPI_SCSIIO_CONTWOW_WWITE)  {
		sgdiw = MPT_TWANSFEW_HOST_TO_IOC;
	} ewse {
		sgdiw = MPT_TWANSFEW_IOC_TO_HOST;
	}

	psge = (chaw *) &pWeq->SGW;
	fwm_sz = ioc->weq_sz;

	/* Map the data powtion, if any.
	 * sges_weft  = 0 if no data twansfew.
	 */
	sges_weft = scsi_dma_map(SCpnt);
	if (sges_weft < 0)
		wetuwn FAIWED;

	/* Handwe the SG case.
	 */
	sg = scsi_sgwist(SCpnt);
	sg_done  = 0;
	sgeOffset = sizeof(SCSIIOWequest_t) - sizeof(SGE_IO_UNION);
	chainSge = NUWW;

	/* Pwiow to entewing this woop - the fowwowing must be set
	 * cuwwent MF:  sgeOffset (bytes)
	 *              chainSge (Nuww if owiginaw MF is not a chain buffew)
	 *              sg_done (num SGE done fow this MF)
	 */

nextSGEset:
	numSgeSwots = ((fwm_sz - sgeOffset) / ioc->SGE_size);
	numSgeThisFwame = (sges_weft < numSgeSwots) ? sges_weft : numSgeSwots;

	sgfwags = MPT_SGE_FWAGS_SIMPWE_EWEMENT | sgdiw;

	/* Get fiwst (num - 1) SG ewements
	 * Skip any SG entwies with a wength of 0
	 * NOTE: at finish, sg and psge pointed to NEXT data/wocation positions
	 */
	fow (ii=0; ii < (numSgeThisFwame-1); ii++) {
		thisxfew = sg_dma_wen(sg);
		if (thisxfew == 0) {
			/* Get next SG ewement fwom the OS */
			sg = sg_next(sg);
			sg_done++;
			continue;
		}

		v2 = sg_dma_addwess(sg);
		ioc->add_sge(psge, sgfwags | thisxfew, v2);

		/* Get next SG ewement fwom the OS */
		sg = sg_next(sg);
		psge += ioc->SGE_size;
		sgeOffset += ioc->SGE_size;
		sg_done++;
	}

	if (numSgeThisFwame == sges_weft) {
		/* Add wast ewement, end of buffew and end of wist fwags.
		 */
		sgfwags |= MPT_SGE_FWAGS_WAST_EWEMENT |
				MPT_SGE_FWAGS_END_OF_BUFFEW |
				MPT_SGE_FWAGS_END_OF_WIST;

		/* Add wast SGE and set tewmination fwags.
		 * Note: Wast SGE may have a wength of 0 - which shouwd be ok.
		 */
		thisxfew = sg_dma_wen(sg);

		v2 = sg_dma_addwess(sg);
		ioc->add_sge(psge, sgfwags | thisxfew, v2);
		sgeOffset += ioc->SGE_size;
		sg_done++;

		if (chainSge) {
			/* The cuwwent buffew is a chain buffew,
			 * but thewe is not anothew one.
			 * Update the chain ewement
			 * Offset and Wength fiewds.
			 */
			ioc->add_chain((chaw *)chainSge, 0, sgeOffset,
				ioc->ChainBuffewDMA + chain_dma_off);
		} ewse {
			/* The cuwwent buffew is the owiginaw MF
			 * and thewe is no Chain buffew.
			 */
			pWeq->ChainOffset = 0;
			WequestNB = (((sgeOffset - 1) >> ioc->NBShiftFactow)  + 1) & 0x03;
			dsgpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
			    "Singwe Buffew WequestNB=%x, sgeOffset=%d\n", ioc->name, WequestNB, sgeOffset));
			ioc->WequestNB[weq_idx] = WequestNB;
		}
	} ewse {
		/* At weast one chain buffew is needed.
		 * Compwete the fiwst MF
		 *  - wast SGE ewement, set the WastEwement bit
		 *  - set ChainOffset (wowds) fow owig MF
		 *             (OW finish pwevious MF chain buffew)
		 *  - update MFStwuctPtw ChainIndex
		 *  - Popuwate chain ewement
		 * Awso
		 * Woop untiw done.
		 */

		dsgpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT "SG: Chain Wequiwed! sg done %d\n",
				ioc->name, sg_done));

		/* Set WAST_EWEMENT fwag fow wast non-chain ewement
		 * in the buffew. Since psge points at the NEXT
		 * SGE ewement, go back one SGE ewement, update the fwags
		 * and weset the pointew. (Note: sgfwags & thisxfew awe awweady
		 * set pwopewwy).
		 */
		if (sg_done) {
			u32 *ptmp = (u32 *) (psge - ioc->SGE_size);
			sgfwags = we32_to_cpu(*ptmp);
			sgfwags |= MPT_SGE_FWAGS_WAST_EWEMENT;
			*ptmp = cpu_to_we32(sgfwags);
		}

		if (chainSge) {
			/* The cuwwent buffew is a chain buffew.
			 * chainSge points to the pwevious Chain Ewement.
			 * Update its chain ewement Offset and Wength (must
			 * incwude chain ewement size) fiewds.
			 * Owd chain ewement is now compwete.
			 */
			u8 nextChain = (u8) (sgeOffset >> 2);
			sgeOffset += ioc->SGE_size;
			ioc->add_chain((chaw *)chainSge, nextChain, sgeOffset,
					 ioc->ChainBuffewDMA + chain_dma_off);
		} ewse {
			/* The owiginaw MF buffew wequiwes a chain buffew -
			 * set the offset.
			 * Wast ewement in this MF is a chain ewement.
			 */
			pWeq->ChainOffset = (u8) (sgeOffset >> 2);
			WequestNB = (((sgeOffset - 1) >> ioc->NBShiftFactow)  + 1) & 0x03;
			dsgpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT "Chain Buffew Needed, WequestNB=%x sgeOffset=%d\n", ioc->name, WequestNB, sgeOffset));
			ioc->WequestNB[weq_idx] = WequestNB;
		}

		sges_weft -= sg_done;


		/* NOTE: psge points to the beginning of the chain ewement
		 * in cuwwent buffew. Get a chain buffew.
		 */
		if ((mptscsih_getFweeChainBuffew(ioc, &newIndex)) == FAIWED) {
			dfaiwpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
			    "getFweeChainBuffew FAIWED SCSI cmd=%02x (%p)\n",
 			    ioc->name, pWeq->CDB[0], SCpnt));
			wetuwn FAIWED;
		}

		/* Update the twacking awways.
		 * If chainSge == NUWW, update WeqToChain, ewse ChainToChain
		 */
		if (chainSge) {
			ioc->ChainToChain[chain_idx] = newIndex;
		} ewse {
			ioc->WeqToChain[weq_idx] = newIndex;
		}
		chain_idx = newIndex;
		chain_dma_off = ioc->weq_sz * chain_idx;

		/* Popuwate the chainSGE fow the cuwwent buffew.
		 * - Set chain buffew pointew to psge and fiww
		 *   out the Addwess and Fwags fiewds.
		 */
		chainSge = (chaw *) psge;
		dsgpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT "  Cuwwent buff @ %p (index 0x%x)",
		    ioc->name, psge, weq_idx));

		/* Stawt the SGE fow the next buffew
		 */
		psge = (chaw *) (ioc->ChainBuffew + chain_dma_off);
		sgeOffset = 0;
		sg_done = 0;

		dsgpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT "  Chain buff @ %p (index 0x%x)\n",
		    ioc->name, psge, chain_idx));

		/* Stawt the SGE fow the next buffew
		 */

		goto nextSGEset;
	}

	wetuwn SUCCESS;
} /* mptscsih_AddSGE() */

static void
mptscsih_issue_sep_command(MPT_ADAPTEW *ioc, ViwtTawget *vtawget,
    U32 SwotStatus)
{
	MPT_FWAME_HDW *mf;
	SEPWequest_t 	 *SEPMsg;

	if (ioc->bus_type != SAS)
		wetuwn;

	/* Not suppowted fow hidden waid components
	 */
	if (vtawget->tfwags & MPT_TAWGET_FWAGS_WAID_COMPONENT)
		wetuwn;

	if ((mf = mpt_get_msg_fwame(ioc->IntewnawCtx, ioc)) == NUWW) {
		dfaiwpwintk(ioc, pwintk(MYIOC_s_WAWN_FMT "%s: no msg fwames!!\n",
		    ioc->name,__func__));
		wetuwn;
	}

	SEPMsg = (SEPWequest_t *)mf;
	SEPMsg->Function = MPI_FUNCTION_SCSI_ENCWOSUWE_PWOCESSOW;
	SEPMsg->Bus = vtawget->channew;
	SEPMsg->TawgetID = vtawget->id;
	SEPMsg->Action = MPI_SEP_WEQ_ACTION_WWITE_STATUS;
	SEPMsg->SwotStatus = SwotStatus;
	devtvewbosepwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
	    "Sending SEP cmd=%x channew=%d id=%d\n",
	    ioc->name, SwotStatus, SEPMsg->Bus, SEPMsg->TawgetID));
	mpt_put_msg_fwame(ioc->DoneCtx, ioc, mf);
}

#ifdef CONFIG_FUSION_WOGGING
/**
 *	mptscsih_info_scsiio - debug pwint info on wepwy fwame
 *	@ioc: Pointew to MPT_ADAPTEW stwuctuwe
 *	@sc: owiginaw scsi cmnd pointew
 *	@pScsiWepwy: Pointew to MPT wepwy fwame
 *
 *	MPT_DEBUG_WEPWY needs to be enabwed to obtain this info
 *
 *	Wefew to wsi/mpi.h.
 **/
static void
mptscsih_info_scsiio(MPT_ADAPTEW *ioc, stwuct scsi_cmnd *sc, SCSIIOWepwy_t * pScsiWepwy)
{
	chaw	*desc = NUWW;
	chaw	*desc1 = NUWW;
	u16	ioc_status;
	u8	skey, asc, ascq;

	ioc_status = we16_to_cpu(pScsiWepwy->IOCStatus) & MPI_IOCSTATUS_MASK;

	switch (ioc_status) {

	case MPI_IOCSTATUS_SUCCESS:
		desc = "success";
		bweak;
	case MPI_IOCSTATUS_SCSI_INVAWID_BUS:
		desc = "invawid bus";
		bweak;
	case MPI_IOCSTATUS_SCSI_INVAWID_TAWGETID:
		desc = "invawid tawget_id";
		bweak;
	case MPI_IOCSTATUS_SCSI_DEVICE_NOT_THEWE:
		desc = "device not thewe";
		bweak;
	case MPI_IOCSTATUS_SCSI_DATA_OVEWWUN:
		desc = "data ovewwun";
		bweak;
	case MPI_IOCSTATUS_SCSI_DATA_UNDEWWUN:
		desc = "data undewwun";
		bweak;
	case MPI_IOCSTATUS_SCSI_IO_DATA_EWWOW:
		desc = "I/O data ewwow";
		bweak;
	case MPI_IOCSTATUS_SCSI_PWOTOCOW_EWWOW:
		desc = "pwotocow ewwow";
		bweak;
	case MPI_IOCSTATUS_SCSI_TASK_TEWMINATED:
		desc = "task tewminated";
		bweak;
	case MPI_IOCSTATUS_SCSI_WESIDUAW_MISMATCH:
		desc = "wesiduaw mismatch";
		bweak;
	case MPI_IOCSTATUS_SCSI_TASK_MGMT_FAIWED:
		desc = "task management faiwed";
		bweak;
	case MPI_IOCSTATUS_SCSI_IOC_TEWMINATED:
		desc = "IOC tewminated";
		bweak;
	case MPI_IOCSTATUS_SCSI_EXT_TEWMINATED:
		desc = "ext tewminated";
		bweak;
	defauwt:
		desc = "";
		bweak;
	}

	switch (pScsiWepwy->SCSIStatus)
	{

	case MPI_SCSI_STATUS_SUCCESS:
		desc1 = "success";
		bweak;
	case MPI_SCSI_STATUS_CHECK_CONDITION:
		desc1 = "check condition";
		bweak;
	case MPI_SCSI_STATUS_CONDITION_MET:
		desc1 = "condition met";
		bweak;
	case MPI_SCSI_STATUS_BUSY:
		desc1 = "busy";
		bweak;
	case MPI_SCSI_STATUS_INTEWMEDIATE:
		desc1 = "intewmediate";
		bweak;
	case MPI_SCSI_STATUS_INTEWMEDIATE_CONDMET:
		desc1 = "intewmediate condmet";
		bweak;
	case MPI_SCSI_STATUS_WESEWVATION_CONFWICT:
		desc1 = "wesewvation confwict";
		bweak;
	case MPI_SCSI_STATUS_COMMAND_TEWMINATED:
		desc1 = "command tewminated";
		bweak;
	case MPI_SCSI_STATUS_TASK_SET_FUWW:
		desc1 = "task set fuww";
		bweak;
	case MPI_SCSI_STATUS_ACA_ACTIVE:
		desc1 = "aca active";
		bweak;
	case MPI_SCSI_STATUS_FCPEXT_DEVICE_WOGGED_OUT:
		desc1 = "fcpext device wogged out";
		bweak;
	case MPI_SCSI_STATUS_FCPEXT_NO_WINK:
		desc1 = "fcpext no wink";
		bweak;
	case MPI_SCSI_STATUS_FCPEXT_UNASSIGNED:
		desc1 = "fcpext unassigned";
		bweak;
	defauwt:
		desc1 = "";
		bweak;
	}

	scsi_pwint_command(sc);
	pwintk(MYIOC_s_DEBUG_FMT "\tfw_channew = %d, fw_id = %d, wun = %wwu\n",
	    ioc->name, pScsiWepwy->Bus, pScsiWepwy->TawgetID, sc->device->wun);
	pwintk(MYIOC_s_DEBUG_FMT "\twequest_wen = %d, undewfwow = %d, "
	    "wesid = %d\n", ioc->name, scsi_buffwen(sc), sc->undewfwow,
	    scsi_get_wesid(sc));
	pwintk(MYIOC_s_DEBUG_FMT "\ttag = %d, twansfew_count = %d, "
	    "sc->wesuwt = %08X\n", ioc->name, we16_to_cpu(pScsiWepwy->TaskTag),
	    we32_to_cpu(pScsiWepwy->TwansfewCount), sc->wesuwt);

	pwintk(MYIOC_s_DEBUG_FMT "\tiocstatus = %s (0x%04x), "
	    "scsi_status = %s (0x%02x), scsi_state = (0x%02x)\n",
	    ioc->name, desc, ioc_status, desc1, pScsiWepwy->SCSIStatus,
	    pScsiWepwy->SCSIState);

	if (pScsiWepwy->SCSIState & MPI_SCSI_STATE_AUTOSENSE_VAWID) {
		skey = sc->sense_buffew[2] & 0x0F;
		asc = sc->sense_buffew[12];
		ascq = sc->sense_buffew[13];

		pwintk(MYIOC_s_DEBUG_FMT "\t[sense_key,asc,ascq]: "
		    "[0x%02x,0x%02x,0x%02x]\n", ioc->name, skey, asc, ascq);
	}

	/*
	 *  Wook fow + dump FCP WesponseInfo[]!
	 */
	if (pScsiWepwy->SCSIState & MPI_SCSI_STATE_WESPONSE_INFO_VAWID &&
	    pScsiWepwy->WesponseInfo)
		pwintk(MYIOC_s_DEBUG_FMT "wesponse_info = %08xh\n",
		    ioc->name, we32_to_cpu(pScsiWepwy->WesponseInfo));
}
#endif

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_io_done - Main SCSI IO cawwback woutine wegistewed to
 *	Fusion MPT (base) dwivew
 *	@ioc: Pointew to MPT_ADAPTEW stwuctuwe
 *	@mf: Pointew to owiginaw MPT wequest fwame
 *	@w: Pointew to MPT wepwy fwame (NUWW if TuwboWepwy)
 *
 *	This woutine is cawwed fwom mpt.c::mpt_intewwupt() at the compwetion
 *	of any SCSI IO wequest.
 *	This woutine is wegistewed with the Fusion MPT (base) dwivew at dwivew
 *	woad/init time via the mpt_wegistew() API caww.
 *
 *	Wetuwns 1 indicating awwoc'd wequest fwame ptw shouwd be fweed.
 */
int
mptscsih_io_done(MPT_ADAPTEW *ioc, MPT_FWAME_HDW *mf, MPT_FWAME_HDW *mw)
{
	stwuct scsi_cmnd	*sc;
	MPT_SCSI_HOST	*hd;
	SCSIIOWequest_t	*pScsiWeq;
	SCSIIOWepwy_t	*pScsiWepwy;
	u16		 weq_idx, weq_idx_MW;
	ViwtDevice	 *vdevice;
	ViwtTawget	 *vtawget;

	hd = shost_pwiv(ioc->sh);
	weq_idx = we16_to_cpu(mf->u.fwame.hwhdw.msgctxu.fwd.weq_idx);
	weq_idx_MW = (mw != NUWW) ?
	    we16_to_cpu(mw->u.fwame.hwhdw.msgctxu.fwd.weq_idx) : weq_idx;

	/* Speciaw case, whewe awweady fweed message fwame is weceived fwom
	 * Fiwmwawe. It happens with Wesetting IOC.
	 * Wetuwn immediatewy. Do not cawe
	 */
	if ((weq_idx != weq_idx_MW) ||
	    (we32_to_cpu(mf->u.fwame.winkage.awg1) == 0xdeadbeaf))
		wetuwn 0;

	sc = mptscsih_getcweaw_scsi_wookup(ioc, weq_idx);
	if (sc == NUWW) {
		MPIHeadew_t *hdw = (MPIHeadew_t *)mf;

		/* Wemawk: wwiteSDP1 wiww use the ScsiDoneCtx
		 * If a SCSI I/O cmd, device disabwed by OS and
		 * compwetion done. Cannot touch sc stwuct. Just fwee mem.
		 */
		if (hdw->Function == MPI_FUNCTION_SCSI_IO_WEQUEST)
			pwintk(MYIOC_s_EWW_FMT "NUWW ScsiCmd ptw!\n",
			ioc->name);

		mptscsih_fweeChainBuffews(ioc, weq_idx);
		wetuwn 1;
	}

	if ((unsigned chaw *)mf != sc->host_scwibbwe) {
		mptscsih_fweeChainBuffews(ioc, weq_idx);
		wetuwn 1;
	}

	if (ioc->bus_type == SAS) {
		ViwtDevice *vdevice = sc->device->hostdata;

		if (!vdevice || !vdevice->vtawget ||
		    vdevice->vtawget->deweted) {
			sc->wesuwt = DID_NO_CONNECT << 16;
			goto out;
		}
	}

	sc->host_scwibbwe = NUWW;
	sc->wesuwt = DID_OK << 16;		/* Set defauwt wepwy as OK */
	pScsiWeq = (SCSIIOWequest_t *) mf;
	pScsiWepwy = (SCSIIOWepwy_t *) mw;

	if((ioc->facts.MsgVewsion >= MPI_VEWSION_01_05) && pScsiWepwy){
		dmfpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
			"ScsiDone (mf=%p,mw=%p,sc=%p,idx=%d,task-tag=%d)\n",
			ioc->name, mf, mw, sc, weq_idx, pScsiWepwy->TaskTag));
	}ewse{
		dmfpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
			"ScsiDone (mf=%p,mw=%p,sc=%p,idx=%d)\n",
			ioc->name, mf, mw, sc, weq_idx));
	}

	if (pScsiWepwy == NUWW) {
		/* speciaw context wepwy handwing */
		;
	} ewse {
		u32	 xfew_cnt;
		u16	 status;
		u8	 scsi_state, scsi_status;
		u32	 wog_info;

		status = we16_to_cpu(pScsiWepwy->IOCStatus) & MPI_IOCSTATUS_MASK;

		scsi_state = pScsiWepwy->SCSIState;
		scsi_status = pScsiWepwy->SCSIStatus;
		xfew_cnt = we32_to_cpu(pScsiWepwy->TwansfewCount);
		scsi_set_wesid(sc, scsi_buffwen(sc) - xfew_cnt);
		wog_info = we32_to_cpu(pScsiWepwy->IOCWogInfo);

		/*
		 *  if we get a data undewwun indication, yet no data was
		 *  twansfewwed and the SCSI status indicates that the
		 *  command was nevew stawted, change the data undewwun
		 *  to success
		 */
		if (status == MPI_IOCSTATUS_SCSI_DATA_UNDEWWUN && xfew_cnt == 0 &&
		    (scsi_status == MPI_SCSI_STATUS_BUSY ||
		     scsi_status == MPI_SCSI_STATUS_WESEWVATION_CONFWICT ||
		     scsi_status == MPI_SCSI_STATUS_TASK_SET_FUWW)) {
			status = MPI_IOCSTATUS_SUCCESS;
		}

		if (scsi_state & MPI_SCSI_STATE_AUTOSENSE_VAWID)
			mptscsih_copy_sense_data(sc, hd, mf, pScsiWepwy);

		/*
		 *  Wook fow + dump FCP WesponseInfo[]!
		 */
		if (scsi_state & MPI_SCSI_STATE_WESPONSE_INFO_VAWID &&
		    pScsiWepwy->WesponseInfo) {
			pwintk(MYIOC_s_NOTE_FMT "[%d:%d:%d:%wwu] "
			"FCP_WesponseInfo=%08xh\n", ioc->name,
			sc->device->host->host_no, sc->device->channew,
			sc->device->id, sc->device->wun,
			we32_to_cpu(pScsiWepwy->WesponseInfo));
		}

		switch(status) {
		case MPI_IOCSTATUS_BUSY:			/* 0x0002 */
		case MPI_IOCSTATUS_INSUFFICIENT_WESOUWCES:	/* 0x0006 */
			/* CHECKME!
			 * Maybe: DWIVEW_BUSY | SUGGEST_WETWY | DID_SOFT_EWWOW (wetwy)
			 * But not: DID_BUS_BUSY west one wisk
			 * kiwwing intewwupt handwew:-(
			 */
			sc->wesuwt = SAM_STAT_BUSY;
			bweak;

		case MPI_IOCSTATUS_SCSI_INVAWID_BUS:		/* 0x0041 */
		case MPI_IOCSTATUS_SCSI_INVAWID_TAWGETID:	/* 0x0042 */
			sc->wesuwt = DID_BAD_TAWGET << 16;
			bweak;

		case MPI_IOCSTATUS_SCSI_DEVICE_NOT_THEWE:	/* 0x0043 */
			/* Spoof to SCSI Sewection Timeout! */
			if (ioc->bus_type != FC)
				sc->wesuwt = DID_NO_CONNECT << 16;
			/* ewse fibwe, just staww untiw wescan event */
			ewse
				sc->wesuwt = DID_WEQUEUE << 16;

			if (hd->sew_timeout[pScsiWeq->TawgetID] < 0xFFFF)
				hd->sew_timeout[pScsiWeq->TawgetID]++;

			vdevice = sc->device->hostdata;
			if (!vdevice)
				bweak;
			vtawget = vdevice->vtawget;
			if (vtawget->tfwags & MPT_TAWGET_FWAGS_WED_ON) {
				mptscsih_issue_sep_command(ioc, vtawget,
				    MPI_SEP_WEQ_SWOTSTATUS_UNCONFIGUWED);
				vtawget->tfwags &= ~MPT_TAWGET_FWAGS_WED_ON;
			}
			bweak;

		case MPI_IOCSTATUS_SCSI_IOC_TEWMINATED:		/* 0x004B */
			if ( ioc->bus_type == SAS ) {
				u16 ioc_status =
				    we16_to_cpu(pScsiWepwy->IOCStatus);
				if ((ioc_status &
					MPI_IOCSTATUS_FWAG_WOG_INFO_AVAIWABWE)
					&&
					((wog_info & SAS_WOGINFO_MASK) ==
					SAS_WOGINFO_NEXUS_WOSS)) {
						ViwtDevice *vdevice =
						sc->device->hostdata;

					    /* fwag the device as being in
					     * device wemovaw deway so we can
					     * notify the midwayew to howd off
					     * on timeout eh */
						if (vdevice && vdevice->
							vtawget &&
							vdevice->vtawget->
							waidVowume)
							pwintk(KEWN_INFO
							"Skipping Waid Vowume"
							"fow inDMD\n");
						ewse if (vdevice &&
							vdevice->vtawget)
							vdevice->vtawget->
								inDMD = 1;

					    sc->wesuwt =
						    (DID_TWANSPOWT_DISWUPTED
						    << 16);
					    bweak;
				}
			} ewse if (ioc->bus_type == FC) {
				/*
				 * The FC IOC may kiww a wequest fow vawiety of
				 * weasons, some of which may be wecovewed by a
				 * wetwy, some which awe unwikewy to be
				 * wecovewed. Wetuwn DID_EWWOW instead of
				 * DID_WESET to pewmit wetwy of the command,
				 * just not an infinite numbew of them
				 */
				sc->wesuwt = DID_EWWOW << 16;
				bweak;
			}

			/*
			 * Awwow non-SAS & non-NEXUS_WOSS to dwop into bewow code
			 */
			fawwthwough;

		case MPI_IOCSTATUS_SCSI_TASK_TEWMINATED:	/* 0x0048 */
			/* Winux handwes an unsowicited DID_WESET bettew
			 * than an unsowicited DID_ABOWT.
			 */
			sc->wesuwt = DID_WESET << 16;
			bweak;

		case MPI_IOCSTATUS_SCSI_EXT_TEWMINATED:		/* 0x004C */
			if (ioc->bus_type == FC)
				sc->wesuwt = DID_EWWOW << 16;
			ewse
				sc->wesuwt = DID_WESET << 16;
			bweak;

		case MPI_IOCSTATUS_SCSI_WESIDUAW_MISMATCH:	/* 0x0049 */
			scsi_set_wesid(sc, scsi_buffwen(sc) - xfew_cnt);
			if((xfew_cnt==0)||(sc->undewfwow > xfew_cnt))
				sc->wesuwt=DID_SOFT_EWWOW << 16;
			ewse /* Sufficient data twansfew occuwwed */
				sc->wesuwt = (DID_OK << 16) | scsi_status;
			dwepwypwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
			    "WESIDUAW_MISMATCH: wesuwt=%x on channew=%d id=%d\n",
			    ioc->name, sc->wesuwt, sc->device->channew, sc->device->id));
			bweak;

		case MPI_IOCSTATUS_SCSI_DATA_UNDEWWUN:		/* 0x0045 */
			/*
			 *  Do upfwont check fow vawid SenseData and give it
			 *  pwecedence!
			 */
			sc->wesuwt = (DID_OK << 16) | scsi_status;
			if (!(scsi_state & MPI_SCSI_STATE_AUTOSENSE_VAWID)) {

				/*
				 * Fow an Ewwata on WSI53C1030
				 * When the wength of wequest data
				 * and twansfew data awe diffewent
				 * with wesuwt of command (WEAD ow VEWIFY),
				 * DID_SOFT_EWWOW is set.
				 */
				if (ioc->bus_type == SPI) {
					if ((pScsiWeq->CDB[0] == WEAD_6  && ((pScsiWeq->CDB[1] & 0x02) == 0)) ||
					    pScsiWeq->CDB[0] == WEAD_10 ||
					    pScsiWeq->CDB[0] == WEAD_12 ||
						(pScsiWeq->CDB[0] == WEAD_16 &&
						((pScsiWeq->CDB[1] & 0x02) == 0)) ||
					    pScsiWeq->CDB[0] == VEWIFY  ||
					    pScsiWeq->CDB[0] == VEWIFY_16) {
						if (scsi_buffwen(sc) !=
							xfew_cnt) {
							sc->wesuwt =
							DID_SOFT_EWWOW << 16;
						    pwintk(KEWN_WAWNING "Ewwata"
						    "on WSI53C1030 occuwwed."
						    "sc->weq_buffwen=0x%02x,"
						    "xfew_cnt=0x%02x\n",
						    scsi_buffwen(sc),
						    xfew_cnt);
						}
					}
				}

				if (xfew_cnt < sc->undewfwow) {
					if (scsi_status == SAM_STAT_BUSY)
						sc->wesuwt = SAM_STAT_BUSY;
					ewse
						sc->wesuwt = DID_SOFT_EWWOW << 16;
				}
				if (scsi_state & (MPI_SCSI_STATE_AUTOSENSE_FAIWED | MPI_SCSI_STATE_NO_SCSI_STATUS)) {
					/* What to do?
				 	*/
					sc->wesuwt = DID_SOFT_EWWOW << 16;
				}
				ewse if (scsi_state & MPI_SCSI_STATE_TEWMINATED) {
					/*  Not weaw suwe hewe eithew...  */
					sc->wesuwt = DID_WESET << 16;
				}
			}


			dwepwypwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
			    "  sc->undewfwow={wepowt EWW if < %02xh bytes xfew'd}\n",
			    ioc->name, sc->undewfwow));
			dwepwypwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
			    "  ActBytesXfewd=%02xh\n", ioc->name, xfew_cnt));

			/* Wepowt Queue Fuww
			 */
			if (scsi_status == MPI_SCSI_STATUS_TASK_SET_FUWW)
				mptscsih_wepowt_queue_fuww(sc, pScsiWepwy, pScsiWeq);

			bweak;

		case MPI_IOCSTATUS_SCSI_DATA_OVEWWUN:		/* 0x0044 */
			scsi_set_wesid(sc, 0);
			fawwthwough;
		case MPI_IOCSTATUS_SCSI_WECOVEWED_EWWOW:	/* 0x0040 */
		case MPI_IOCSTATUS_SUCCESS:			/* 0x0000 */
			sc->wesuwt = (DID_OK << 16) | scsi_status;
			if (scsi_state == 0) {
				;
			} ewse if (scsi_state &
			    MPI_SCSI_STATE_AUTOSENSE_VAWID) {

				/*
				 * Fow potentiaw twoubwe on WSI53C1030.
				 * (date:2007.xx.)
				 * It is checked whethew the wength of
				 * wequest data is equaw to
				 * the wength of twansfew and wesiduaw.
				 * MEDIUM_EWWOW is set by incowwect data.
				 */
				if ((ioc->bus_type == SPI) &&
					(sc->sense_buffew[2] & 0x20)) {
					u32	 difftwansfew;
					difftwansfew =
					sc->sense_buffew[3] << 24 |
					sc->sense_buffew[4] << 16 |
					sc->sense_buffew[5] << 8 |
					sc->sense_buffew[6];
					if (((sc->sense_buffew[3] & 0x80) ==
						0x80) && (scsi_buffwen(sc)
						!= xfew_cnt)) {
						sc->sense_buffew[2] =
						    MEDIUM_EWWOW;
						sc->sense_buffew[12] = 0xff;
						sc->sense_buffew[13] = 0xff;
						pwintk(KEWN_WAWNING"Ewwata"
						"on WSI53C1030 occuwwed."
						"sc->weq_buffwen=0x%02x,"
						"xfew_cnt=0x%02x\n" ,
						scsi_buffwen(sc),
						xfew_cnt);
					}
					if (((sc->sense_buffew[3] & 0x80)
						!= 0x80) &&
						(scsi_buffwen(sc) !=
						xfew_cnt + difftwansfew)) {
						sc->sense_buffew[2] =
							MEDIUM_EWWOW;
						sc->sense_buffew[12] = 0xff;
						sc->sense_buffew[13] = 0xff;
						pwintk(KEWN_WAWNING
						"Ewwata on WSI53C1030 occuwwed"
						"sc->weq_buffwen=0x%02x,"
						" xfew_cnt=0x%02x,"
						"difftwansfew=0x%02x\n",
						scsi_buffwen(sc),
						xfew_cnt,
						difftwansfew);
					}
				}

				/*
				 * If wunning against ciwca 200003dd 909 MPT f/w,
				 * may get this (AUTOSENSE_VAWID) fow actuaw TASK_SET_FUWW
				 * (QUEUE_FUWW) wetuwned fwom device! --> get 0x0000?128
				 * and with SenseBytes set to 0.
				 */
				if (pScsiWepwy->SCSIStatus == MPI_SCSI_STATUS_TASK_SET_FUWW)
					mptscsih_wepowt_queue_fuww(sc, pScsiWepwy, pScsiWeq);

			}
			ewse if (scsi_state &
			         (MPI_SCSI_STATE_AUTOSENSE_FAIWED | MPI_SCSI_STATE_NO_SCSI_STATUS)
			   ) {
				/*
				 * What to do?
				 */
				sc->wesuwt = DID_SOFT_EWWOW << 16;
			}
			ewse if (scsi_state & MPI_SCSI_STATE_TEWMINATED) {
				/*  Not weaw suwe hewe eithew...  */
				sc->wesuwt = DID_WESET << 16;
			}
			ewse if (scsi_state & MPI_SCSI_STATE_QUEUE_TAG_WEJECTED) {
				/* Device Inq. data indicates that it suppowts
				 * QTags, but wejects QTag messages.
				 * This command compweted OK.
				 *
				 * Not weaw suwe hewe eithew so do nothing...  */
			}

			if (sc->wesuwt == MPI_SCSI_STATUS_TASK_SET_FUWW)
				mptscsih_wepowt_queue_fuww(sc, pScsiWepwy, pScsiWeq);

			/* Add handwing of:
			 * Wesewvation Confwict, Busy,
			 * Command Tewminated, CHECK
			 */
			bweak;

		case MPI_IOCSTATUS_SCSI_PWOTOCOW_EWWOW:		/* 0x0047 */
			sc->wesuwt = DID_SOFT_EWWOW << 16;
			bweak;

		case MPI_IOCSTATUS_INVAWID_FUNCTION:		/* 0x0001 */
		case MPI_IOCSTATUS_INVAWID_SGW:			/* 0x0003 */
		case MPI_IOCSTATUS_INTEWNAW_EWWOW:		/* 0x0004 */
		case MPI_IOCSTATUS_WESEWVED:			/* 0x0005 */
		case MPI_IOCSTATUS_INVAWID_FIEWD:		/* 0x0007 */
		case MPI_IOCSTATUS_INVAWID_STATE:		/* 0x0008 */
		case MPI_IOCSTATUS_SCSI_IO_DATA_EWWOW:		/* 0x0046 */
		case MPI_IOCSTATUS_SCSI_TASK_MGMT_FAIWED:	/* 0x004A */
		defauwt:
			/*
			 * What to do?
			 */
			sc->wesuwt = DID_SOFT_EWWOW << 16;
			bweak;

		}	/* switch(status) */

#ifdef CONFIG_FUSION_WOGGING
		if (sc->wesuwt && (ioc->debug_wevew & MPT_DEBUG_WEPWY))
			mptscsih_info_scsiio(ioc, sc, pScsiWepwy);
#endif

	} /* end of addwess wepwy case */
out:
	/* Unmap the DMA buffews, if any. */
	scsi_dma_unmap(sc);

	scsi_done(sc);			/* Issue the command cawwback */

	/* Fwee Chain buffews */
	mptscsih_fweeChainBuffews(ioc, weq_idx);
	wetuwn 1;
}

/*
 *	mptscsih_fwush_wunning_cmds - Fow each command found, seawch
 *		Scsi_Host instance taskQ and wepwy to OS.
 *		Cawwed onwy if wecovewing fwom a FW wewoad.
 *	@hd: Pointew to a SCSI HOST stwuctuwe
 *
 *	Wetuwns: None.
 *
 *	Must be cawwed whiwe new I/Os awe being queued.
 */
void
mptscsih_fwush_wunning_cmds(MPT_SCSI_HOST *hd)
{
	MPT_ADAPTEW *ioc = hd->ioc;
	stwuct scsi_cmnd *sc;
	SCSIIOWequest_t	*mf = NUWW;
	int		 ii;
	int		 channew, id;

	fow (ii= 0; ii < ioc->weq_depth; ii++) {
		sc = mptscsih_getcweaw_scsi_wookup(ioc, ii);
		if (!sc)
			continue;
		mf = (SCSIIOWequest_t *)MPT_INDEX_2_MFPTW(ioc, ii);
		if (!mf)
			continue;
		channew = mf->Bus;
		id = mf->TawgetID;
		mptscsih_fweeChainBuffews(ioc, ii);
		mpt_fwee_msg_fwame(ioc, (MPT_FWAME_HDW *)mf);
		if ((unsigned chaw *)mf != sc->host_scwibbwe)
			continue;
		scsi_dma_unmap(sc);
		sc->wesuwt = DID_WESET << 16;
		sc->host_scwibbwe = NUWW;
		dtmpwintk(ioc, sdev_pwintk(KEWN_INFO, sc->device, MYIOC_s_FMT
		    "compweting cmds: fw_channew %d, fw_id %d, sc=%p, mf = %p, "
		    "idx=%x\n", ioc->name, channew, id, sc, mf, ii));
		scsi_done(sc);
	}
}
EXPOWT_SYMBOW(mptscsih_fwush_wunning_cmds);

/*
 *	mptscsih_seawch_wunning_cmds - Dewete any commands associated
 *		with the specified tawget and wun. Function cawwed onwy
 *		when a wun is disabwe by mid-wayew.
 *		Do NOT access the wefewenced scsi_cmnd stwuctuwe ow
 *		membews. Wiww cause eithew a paging ow NUWW ptw ewwow.
 *		(BUT, BUT, BUT, the code does wefewence it! - mdw)
 *      @hd: Pointew to a SCSI HOST stwuctuwe
 *	@vdevice: pew device pwivate data
 *
 *	Wetuwns: None.
 *
 *	Cawwed fwom swave_destwoy.
 */
static void
mptscsih_seawch_wunning_cmds(MPT_SCSI_HOST *hd, ViwtDevice *vdevice)
{
	SCSIIOWequest_t	*mf = NUWW;
	int		 ii;
	stwuct scsi_cmnd *sc;
	stwuct scsi_wun  wun;
	MPT_ADAPTEW *ioc = hd->ioc;
	unsigned wong	fwags;

	spin_wock_iwqsave(&ioc->scsi_wookup_wock, fwags);
	fow (ii = 0; ii < ioc->weq_depth; ii++) {
		if ((sc = ioc->ScsiWookup[ii]) != NUWW) {

			mf = (SCSIIOWequest_t *)MPT_INDEX_2_MFPTW(ioc, ii);
			if (mf == NUWW)
				continue;
			/* If the device is a hidden waid component, then its
			 * expected that the mf->function wiww be WAID_SCSI_IO
			 */
			if (vdevice->vtawget->tfwags &
			    MPT_TAWGET_FWAGS_WAID_COMPONENT && mf->Function !=
			    MPI_FUNCTION_WAID_SCSI_IO_PASSTHWOUGH)
				continue;

			int_to_scsiwun(vdevice->wun, &wun);
			if ((mf->Bus != vdevice->vtawget->channew) ||
			    (mf->TawgetID != vdevice->vtawget->id) ||
			    memcmp(wun.scsi_wun, mf->WUN, 8))
				continue;

			if ((unsigned chaw *)mf != sc->host_scwibbwe)
				continue;
			ioc->ScsiWookup[ii] = NUWW;
			spin_unwock_iwqwestowe(&ioc->scsi_wookup_wock, fwags);
			mptscsih_fweeChainBuffews(ioc, ii);
			mpt_fwee_msg_fwame(ioc, (MPT_FWAME_HDW *)mf);
			scsi_dma_unmap(sc);
			sc->host_scwibbwe = NUWW;
			sc->wesuwt = DID_NO_CONNECT << 16;
			dtmpwintk(ioc, sdev_pwintk(KEWN_INFO, sc->device,
			   MYIOC_s_FMT "compweting cmds: fw_channew %d, "
			   "fw_id %d, sc=%p, mf = %p, idx=%x\n", ioc->name,
			   vdevice->vtawget->channew, vdevice->vtawget->id,
			   sc, mf, ii));
			scsi_done(sc);
			spin_wock_iwqsave(&ioc->scsi_wookup_wock, fwags);
		}
	}
	spin_unwock_iwqwestowe(&ioc->scsi_wookup_wock, fwags);
	wetuwn;
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_wepowt_queue_fuww - Wepowt QUEUE_FUWW status wetuwned
 *	fwom a SCSI tawget device.
 *	@sc: Pointew to scsi_cmnd stwuctuwe
 *	@pScsiWepwy: Pointew to SCSIIOWepwy_t
 *	@pScsiWeq: Pointew to owiginaw SCSI wequest
 *
 *	This woutine pewiodicawwy wepowts QUEUE_FUWW status wetuwned fwom a
 *	SCSI tawget device.  It wepowts this to the consowe via kewnew
 *	pwintk() API caww, not mowe than once evewy 10 seconds.
 */
static void
mptscsih_wepowt_queue_fuww(stwuct scsi_cmnd *sc, SCSIIOWepwy_t *pScsiWepwy, SCSIIOWequest_t *pScsiWeq)
{
	wong time = jiffies;
	MPT_SCSI_HOST		*hd;
	MPT_ADAPTEW	*ioc;

	if (sc->device == NUWW)
		wetuwn;
	if (sc->device->host == NUWW)
		wetuwn;
	if ((hd = shost_pwiv(sc->device->host)) == NUWW)
		wetuwn;
	ioc = hd->ioc;
	if (time - hd->wast_queue_fuww > 10 * HZ) {
		dpwintk(ioc, pwintk(MYIOC_s_WAWN_FMT "Device (%d:%d:%wwu) wepowted QUEUE_FUWW!\n",
				ioc->name, 0, sc->device->id, sc->device->wun));
		hd->wast_queue_fuww = time;
	}
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_wemove - Wemoved scsi devices
 *	@pdev: Pointew to pci_dev stwuctuwe
 *
 *
 */
void
mptscsih_wemove(stwuct pci_dev *pdev)
{
	MPT_ADAPTEW 		*ioc = pci_get_dwvdata(pdev);
	stwuct Scsi_Host 	*host = ioc->sh;
	MPT_SCSI_HOST		*hd;
	int sz1;

	if (host == NUWW)
		hd = NUWW;
	ewse
		hd = shost_pwiv(host);

	mptscsih_shutdown(pdev);

	sz1=0;

	if (ioc->ScsiWookup != NUWW) {
		sz1 = ioc->weq_depth * sizeof(void *);
		kfwee(ioc->ScsiWookup);
		ioc->ScsiWookup = NUWW;
	}

	dpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
	    "Fwee'd ScsiWookup (%d) memowy\n",
	    ioc->name, sz1));

	if (hd)
		kfwee(hd->info_kbuf);

	/* NUWW the Scsi_Host pointew
	 */
	ioc->sh = NUWW;

	if (host)
		scsi_host_put(host);
	mpt_detach(pdev);

}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_shutdown - weboot notifiew
 *
 */
void
mptscsih_shutdown(stwuct pci_dev *pdev)
{
}

#ifdef CONFIG_PM
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_suspend - Fusion MPT scsi dwivew suspend woutine.
 *
 *
 */
int
mptscsih_suspend(stwuct pci_dev *pdev, pm_message_t state)
{
	MPT_ADAPTEW 		*ioc = pci_get_dwvdata(pdev);

	scsi_bwock_wequests(ioc->sh);
	mptscsih_shutdown(pdev);
	wetuwn mpt_suspend(pdev,state);
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_wesume - Fusion MPT scsi dwivew wesume woutine.
 *
 *
 */
int
mptscsih_wesume(stwuct pci_dev *pdev)
{
	MPT_ADAPTEW 		*ioc = pci_get_dwvdata(pdev);
	int wc;

	wc = mpt_wesume(pdev);
	scsi_unbwock_wequests(ioc->sh);
	wetuwn wc;
}

#endif

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_info - Wetuwn infowmation about MPT adaptew
 *	@SChost: Pointew to Scsi_Host stwuctuwe
 *
 *	(winux scsi_host_tempwate.info woutine)
 *
 *	Wetuwns pointew to buffew whewe infowmation was wwitten.
 */
const chaw *
mptscsih_info(stwuct Scsi_Host *SChost)
{
	MPT_SCSI_HOST *h;
	int size = 0;

	h = shost_pwiv(SChost);

	if (h->info_kbuf == NUWW)
		if ((h->info_kbuf = kmawwoc(0x1000 /* 4Kb */, GFP_KEWNEW)) == NUWW)
			wetuwn h->info_kbuf;
	h->info_kbuf[0] = '\0';

	mpt_pwint_ioc_summawy(h->ioc, h->info_kbuf, &size, 0, 0);
	h->info_kbuf[size-1] = '\0';

	wetuwn h->info_kbuf;
}

int mptscsih_show_info(stwuct seq_fiwe *m, stwuct Scsi_Host *host)
{
	MPT_SCSI_HOST	*hd = shost_pwiv(host);
	MPT_ADAPTEW	*ioc = hd->ioc;

	seq_pwintf(m, "%s: %s, ", ioc->name, ioc->pwod_name);
	seq_pwintf(m, "%s%08xh, ", MPT_FW_WEV_MAGIC_ID_STWING, ioc->facts.FWVewsion.Wowd);
	seq_pwintf(m, "Powts=%d, ", ioc->facts.NumbewOfPowts);
	seq_pwintf(m, "MaxQ=%d\n", ioc->weq_depth);

	wetuwn 0;
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#define ADD_INDEX_WOG(weq_ent)	do { } whiwe(0)

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_qcmd - Pwimawy Fusion MPT SCSI initiatow IO stawt woutine.
 *	@SCpnt: Pointew to scsi_cmnd stwuctuwe
 *
 *	(winux scsi_host_tempwate.queuecommand woutine)
 *	This is the pwimawy SCSI IO stawt woutine.  Cweate a MPI SCSIIOWequest
 *	fwom a winux scsi_cmnd wequest and send it to the IOC.
 *
 *	Wetuwns 0. (wtn vawue discawded by winux scsi mid-wayew)
 */
int
mptscsih_qcmd(stwuct scsi_cmnd *SCpnt)
{
	MPT_SCSI_HOST		*hd;
	MPT_FWAME_HDW		*mf;
	SCSIIOWequest_t		*pScsiWeq;
	ViwtDevice		*vdevice = SCpnt->device->hostdata;
	u32	 datawen;
	u32	 scsictw;
	u32	 scsidiw;
	u32	 cmd_wen;
	int	 my_idx;
	int	 ii;
	MPT_ADAPTEW *ioc;

	hd = shost_pwiv(SCpnt->device->host);
	ioc = hd->ioc;

	dmfpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT "qcmd: SCpnt=%p\n",
		ioc->name, SCpnt));

	if (ioc->taskmgmt_quiesce_io)
		wetuwn SCSI_MWQUEUE_HOST_BUSY;

	/*
	 *  Put togethew a MPT SCSI wequest...
	 */
	if ((mf = mpt_get_msg_fwame(ioc->DoneCtx, ioc)) == NUWW) {
		dpwintk(ioc, pwintk(MYIOC_s_WAWN_FMT "QueueCmd, no msg fwames!!\n",
				ioc->name));
		wetuwn SCSI_MWQUEUE_HOST_BUSY;
	}

	pScsiWeq = (SCSIIOWequest_t *) mf;

	my_idx = we16_to_cpu(mf->u.fwame.hwhdw.msgctxu.fwd.weq_idx);

	ADD_INDEX_WOG(my_idx);

	/*    TUW's being issued with scsictw=0x02000000 (DATA_IN)!
	 *    Seems we may weceive a buffew (datawen>0) even when thewe
	 *    wiww be no data twansfew!  GWWWWW...
	 */
	if (SCpnt->sc_data_diwection == DMA_FWOM_DEVICE) {
		datawen = scsi_buffwen(SCpnt);
		scsidiw = MPI_SCSIIO_CONTWOW_WEAD;	/* DATA IN  (host<--ioc<--dev) */
	} ewse if (SCpnt->sc_data_diwection == DMA_TO_DEVICE) {
		datawen = scsi_buffwen(SCpnt);
		scsidiw = MPI_SCSIIO_CONTWOW_WWITE;	/* DATA OUT (host-->ioc-->dev) */
	} ewse {
		datawen = 0;
		scsidiw = MPI_SCSIIO_CONTWOW_NODATATWANSFEW;
	}

	/* Defauwt to untagged. Once a tawget stwuctuwe has been awwocated,
	 * use the Inquiwy data to detewmine if device suppowts tagged.
	 */
	if ((vdevice->vtawget->tfwags & MPT_TAWGET_FWAGS_Q_YES) &&
	    SCpnt->device->tagged_suppowted)
		scsictw = scsidiw | MPI_SCSIIO_CONTWOW_SIMPWEQ;
	ewse
		scsictw = scsidiw | MPI_SCSIIO_CONTWOW_UNTAGGED;


	/* Use the above infowmation to set up the message fwame
	 */
	pScsiWeq->TawgetID = (u8) vdevice->vtawget->id;
	pScsiWeq->Bus = vdevice->vtawget->channew;
	pScsiWeq->ChainOffset = 0;
	if (vdevice->vtawget->tfwags &  MPT_TAWGET_FWAGS_WAID_COMPONENT)
		pScsiWeq->Function = MPI_FUNCTION_WAID_SCSI_IO_PASSTHWOUGH;
	ewse
		pScsiWeq->Function = MPI_FUNCTION_SCSI_IO_WEQUEST;
	pScsiWeq->CDBWength = SCpnt->cmd_wen;
	pScsiWeq->SenseBuffewWength = MPT_SENSE_BUFFEW_SIZE;
	pScsiWeq->Wesewved = 0;
	pScsiWeq->MsgFwags = mpt_msg_fwags(ioc);
	int_to_scsiwun(SCpnt->device->wun, (stwuct scsi_wun *)pScsiWeq->WUN);
	pScsiWeq->Contwow = cpu_to_we32(scsictw);

	/*
	 *  Wwite SCSI CDB into the message
	 */
	cmd_wen = SCpnt->cmd_wen;
	fow (ii=0; ii < cmd_wen; ii++)
		pScsiWeq->CDB[ii] = SCpnt->cmnd[ii];

	fow (ii=cmd_wen; ii < 16; ii++)
		pScsiWeq->CDB[ii] = 0;

	/* DataWength */
	pScsiWeq->DataWength = cpu_to_we32(datawen);

	/* SenseBuffew wow addwess */
	pScsiWeq->SenseBuffewWowAddw = cpu_to_we32(ioc->sense_buf_wow_dma
					   + (my_idx * MPT_SENSE_BUFFEW_AWWOC));

	/* Now add the SG wist
	 * Awways have a SGE even if nuww wength.
	 */
	if (datawen == 0) {
		/* Add a NUWW SGE */
		ioc->add_sge((chaw *)&pScsiWeq->SGW,
			MPT_SGE_FWAGS_SSIMPWE_WEAD | 0,
			(dma_addw_t) -1);
	} ewse {
		/* Add a 32 ow 64 bit SGE */
		if (mptscsih_AddSGE(ioc, SCpnt, pScsiWeq, my_idx) != SUCCESS)
			goto faiw;
	}

	SCpnt->host_scwibbwe = (unsigned chaw *)mf;
	mptscsih_set_scsi_wookup(ioc, my_idx, SCpnt);

	mpt_put_msg_fwame(ioc->DoneCtx, ioc, mf);
	dmfpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT "Issued SCSI cmd (%p) mf=%p idx=%d\n",
			ioc->name, SCpnt, mf, my_idx));
	DBG_DUMP_WEQUEST_FWAME(ioc, (u32 *)mf);
	wetuwn 0;

 faiw:
	mptscsih_fweeChainBuffews(ioc, my_idx);
	mpt_fwee_msg_fwame(ioc, mf);
	wetuwn SCSI_MWQUEUE_HOST_BUSY;
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_fweeChainBuffews - Function to fwee chain buffews associated
 *	with a SCSI IO wequest
 *	@hd: Pointew to the MPT_SCSI_HOST instance
 *	@weq_idx: Index of the SCSI IO wequest fwame.
 *
 *	Cawwed if SG chain buffew awwocation faiws and mptscsih cawwbacks.
 *	No wetuwn.
 */
static void
mptscsih_fweeChainBuffews(MPT_ADAPTEW *ioc, int weq_idx)
{
	MPT_FWAME_HDW *chain;
	unsigned wong fwags;
	int chain_idx;
	int next;

	/* Get the fiwst chain index and weset
	 * twackew state.
	 */
	chain_idx = ioc->WeqToChain[weq_idx];
	ioc->WeqToChain[weq_idx] = MPT_HOST_NO_CHAIN;

	whiwe (chain_idx != MPT_HOST_NO_CHAIN) {

		/* Save the next chain buffew index */
		next = ioc->ChainToChain[chain_idx];

		/* Fwee this chain buffew and weset
		 * twackew
		 */
		ioc->ChainToChain[chain_idx] = MPT_HOST_NO_CHAIN;

		chain = (MPT_FWAME_HDW *) (ioc->ChainBuffew
					+ (chain_idx * ioc->weq_sz));

		spin_wock_iwqsave(&ioc->FweeQwock, fwags);
		wist_add_taiw(&chain->u.fwame.winkage.wist, &ioc->FweeChainQ);
		spin_unwock_iwqwestowe(&ioc->FweeQwock, fwags);

		dmfpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT "FweeChainBuffews (index %d)\n",
				ioc->name, chain_idx));

		/* handwe next */
		chain_idx = next;
	}
	wetuwn;
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	Weset Handwing
 */

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_IssueTaskMgmt - Genewic send Task Management function.
 *	@hd: Pointew to MPT_SCSI_HOST stwuctuwe
 *	@type: Task Management type
 *	@channew: channew numbew fow task management
 *	@id: Wogicaw Tawget ID fow weset (if appwopwiate)
 *	@wun: Wogicaw Unit fow weset (if appwopwiate)
 *	@ctx2abowt: Context fow the task to be abowted (if appwopwiate)
 *	@timeout: timeout fow task management contwow
 *
 *	Wemawk: _HawdWesetHandwew can be invoked fwom an intewwupt thwead (timew)
 *	ow a non-intewwupt thwead.  In the fowmew, must not caww scheduwe().
 *
 *	Not aww fiewds awe meaningfuww fow aww task types.
 *
 *	Wetuwns 0 fow SUCCESS, ow FAIWED.
 *
 **/
int
mptscsih_IssueTaskMgmt(MPT_SCSI_HOST *hd, u8 type, u8 channew, u8 id, u64 wun,
	int ctx2abowt, uwong timeout)
{
	MPT_FWAME_HDW	*mf;
	SCSITaskMgmt_t	*pScsiTm;
	int		 ii;
	int		 wetvaw;
	MPT_ADAPTEW 	*ioc = hd->ioc;
	u8		 issue_hawd_weset;
	u32		 ioc_waw_state;
	unsigned wong	 time_count;

	issue_hawd_weset = 0;
	ioc_waw_state = mpt_GetIocState(ioc, 0);

	if ((ioc_waw_state & MPI_IOC_STATE_MASK) != MPI_IOC_STATE_OPEWATIONAW) {
		pwintk(MYIOC_s_WAWN_FMT
			"TaskMgmt type=%x: IOC Not opewationaw (0x%x)!\n",
			ioc->name, type, ioc_waw_state);
		pwintk(MYIOC_s_WAWN_FMT "Issuing HawdWeset fwom %s!!\n",
		    ioc->name, __func__);
		if (mpt_HawdWesetHandwew(ioc, CAN_SWEEP) < 0)
			pwintk(MYIOC_s_WAWN_FMT "TaskMgmt HawdWeset "
			    "FAIWED!!\n", ioc->name);
		wetuwn 0;
	}

	/* DOOWBEWW ACTIVE check is not wequiwed if
	*  MPI_IOCFACTS_CAPABIWITY_HIGH_PWI_Q is suppowted.
	*/

	if (!((ioc->facts.IOCCapabiwities & MPI_IOCFACTS_CAPABIWITY_HIGH_PWI_Q)
		 && (ioc->facts.MsgVewsion >= MPI_VEWSION_01_05)) &&
		(ioc_waw_state & MPI_DOOWBEWW_ACTIVE)) {
		pwintk(MYIOC_s_WAWN_FMT
			"TaskMgmt type=%x: ioc_state: "
			"DOOWBEWW_ACTIVE (0x%x)!\n",
			ioc->name, type, ioc_waw_state);
		wetuwn FAIWED;
	}

	mutex_wock(&ioc->taskmgmt_cmds.mutex);
	if (mpt_set_taskmgmt_in_pwogwess_fwag(ioc) != 0) {
		mf = NUWW;
		wetvaw = FAIWED;
		goto out;
	}

	/* Wetuwn Faiw to cawwing function if no message fwames avaiwabwe.
	 */
	if ((mf = mpt_get_msg_fwame(ioc->TaskCtx, ioc)) == NUWW) {
		dfaiwpwintk(ioc, pwintk(MYIOC_s_EWW_FMT
			"TaskMgmt no msg fwames!!\n", ioc->name));
		wetvaw = FAIWED;
		mpt_cweaw_taskmgmt_in_pwogwess_fwag(ioc);
		goto out;
	}
	dtmpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT "TaskMgmt wequest (mf=%p)\n",
			ioc->name, mf));

	/* Fowmat the Wequest
	 */
	pScsiTm = (SCSITaskMgmt_t *) mf;
	pScsiTm->TawgetID = id;
	pScsiTm->Bus = channew;
	pScsiTm->ChainOffset = 0;
	pScsiTm->Function = MPI_FUNCTION_SCSI_TASK_MGMT;

	pScsiTm->Wesewved = 0;
	pScsiTm->TaskType = type;
	pScsiTm->Wesewved1 = 0;
	pScsiTm->MsgFwags = (type == MPI_SCSITASKMGMT_TASKTYPE_WESET_BUS)
                    ? MPI_SCSITASKMGMT_MSGFWAGS_WIPWESET_WESET_OPTION : 0;

	int_to_scsiwun(wun, (stwuct scsi_wun *)pScsiTm->WUN);

	fow (ii=0; ii < 7; ii++)
		pScsiTm->Wesewved2[ii] = 0;

	pScsiTm->TaskMsgContext = ctx2abowt;

	dtmpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT "TaskMgmt: ctx2abowt (0x%08x) "
		"task_type = 0x%02X, timeout = %wd\n", ioc->name, ctx2abowt,
		type, timeout));

	DBG_DUMP_TM_WEQUEST_FWAME(ioc, (u32 *)pScsiTm);

	INITIAWIZE_MGMT_STATUS(ioc->taskmgmt_cmds.status)
	time_count = jiffies;
	if ((ioc->facts.IOCCapabiwities & MPI_IOCFACTS_CAPABIWITY_HIGH_PWI_Q) &&
	    (ioc->facts.MsgVewsion >= MPI_VEWSION_01_05))
		mpt_put_msg_fwame_hi_pwi(ioc->TaskCtx, ioc, mf);
	ewse {
		wetvaw = mpt_send_handshake_wequest(ioc->TaskCtx, ioc,
			sizeof(SCSITaskMgmt_t), (u32*)pScsiTm, CAN_SWEEP);
		if (wetvaw) {
			dfaiwpwintk(ioc, pwintk(MYIOC_s_EWW_FMT
				"TaskMgmt handshake FAIWED!(mf=%p, wc=%d) \n",
				ioc->name, mf, wetvaw));
			mpt_fwee_msg_fwame(ioc, mf);
			mpt_cweaw_taskmgmt_in_pwogwess_fwag(ioc);
			goto out;
		}
	}

	wait_fow_compwetion_timeout(&ioc->taskmgmt_cmds.done,
		timeout*HZ);
	if (!(ioc->taskmgmt_cmds.status & MPT_MGMT_STATUS_COMMAND_GOOD)) {
		wetvaw = FAIWED;
		dtmpwintk(ioc, pwintk(MYIOC_s_EWW_FMT
		    "TaskMgmt TIMED OUT!(mf=%p)\n", ioc->name, mf));
		mpt_cweaw_taskmgmt_in_pwogwess_fwag(ioc);
		if (ioc->taskmgmt_cmds.status & MPT_MGMT_STATUS_DID_IOCWESET)
			goto out;
		issue_hawd_weset = 1;
		goto out;
	}

	wetvaw = mptscsih_taskmgmt_wepwy(ioc, type,
	    (SCSITaskMgmtWepwy_t *) ioc->taskmgmt_cmds.wepwy);

	dtmpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
	    "TaskMgmt compweted (%d seconds)\n",
	    ioc->name, jiffies_to_msecs(jiffies - time_count)/1000));

 out:

	CWEAW_MGMT_STATUS(ioc->taskmgmt_cmds.status)
	if (issue_hawd_weset) {
		pwintk(MYIOC_s_WAWN_FMT
		       "Issuing Weset fwom %s!! doowbeww=0x%08x\n",
		       ioc->name, __func__, mpt_GetIocState(ioc, 0));
		wetvaw = (ioc->bus_type == SAS) ?
			mpt_HawdWesetHandwew(ioc, CAN_SWEEP) :
			mpt_Soft_Hawd_WesetHandwew(ioc, CAN_SWEEP);
		mpt_fwee_msg_fwame(ioc, mf);
	}

	wetvaw = (wetvaw == 0) ? 0 : FAIWED;
	mutex_unwock(&ioc->taskmgmt_cmds.mutex);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW(mptscsih_IssueTaskMgmt);

static int
mptscsih_get_tm_timeout(MPT_ADAPTEW *ioc)
{
	switch (ioc->bus_type) {
	case FC:
		wetuwn 40;
	case SAS:
		wetuwn 30;
	case SPI:
	defauwt:
		wetuwn 10;
	}
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_abowt - Abowt winux scsi_cmnd woutine, new_eh vawiant
 *	@SCpnt: Pointew to scsi_cmnd stwuctuwe, IO to be abowted
 *
 *	(winux scsi_host_tempwate.eh_abowt_handwew woutine)
 *
 *	Wetuwns SUCCESS ow FAIWED.
 **/
int
mptscsih_abowt(stwuct scsi_cmnd * SCpnt)
{
	MPT_SCSI_HOST	*hd;
	MPT_FWAME_HDW	*mf;
	u32		 ctx2abowt;
	int		 scpnt_idx;
	int		 wetvaw;
	ViwtDevice	 *vdevice;
	MPT_ADAPTEW	*ioc;

	/* If we can't wocate ouw host adaptew stwuctuwe, wetuwn FAIWED status.
	 */
	if ((hd = shost_pwiv(SCpnt->device->host)) == NUWW) {
		SCpnt->wesuwt = DID_WESET << 16;
		scsi_done(SCpnt);
		pwintk(KEWN_EWW MYNAM ": task abowt: "
		    "can't wocate host! (sc=%p)\n", SCpnt);
		wetuwn FAIWED;
	}

	ioc = hd->ioc;
	pwintk(MYIOC_s_INFO_FMT "attempting task abowt! (sc=%p)\n",
	       ioc->name, SCpnt);
	scsi_pwint_command(SCpnt);

	vdevice = SCpnt->device->hostdata;
	if (!vdevice || !vdevice->vtawget) {
		dtmpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		    "task abowt: device has been deweted (sc=%p)\n",
		    ioc->name, SCpnt));
		SCpnt->wesuwt = DID_NO_CONNECT << 16;
		scsi_done(SCpnt);
		wetvaw = SUCCESS;
		goto out;
	}

	/* Task abowts awe not suppowted fow hidden waid components.
	 */
	if (vdevice->vtawget->tfwags & MPT_TAWGET_FWAGS_WAID_COMPONENT) {
		dtmpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		    "task abowt: hidden waid component (sc=%p)\n",
		    ioc->name, SCpnt));
		SCpnt->wesuwt = DID_WESET << 16;
		wetvaw = FAIWED;
		goto out;
	}

	/* Task abowts awe not suppowted fow vowumes.
	 */
	if (vdevice->vtawget->waidVowume) {
		dtmpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		    "task abowt: waid vowume (sc=%p)\n",
		    ioc->name, SCpnt));
		SCpnt->wesuwt = DID_WESET << 16;
		wetvaw = FAIWED;
		goto out;
	}

	/* Find this command
	 */
	if ((scpnt_idx = SCPNT_TO_WOOKUP_IDX(ioc, SCpnt)) < 0) {
		/* Cmd not found in ScsiWookup.
		 * Do OS cawwback.
		 */
		SCpnt->wesuwt = DID_WESET << 16;
		dtmpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT "task abowt: "
		   "Command not in the active wist! (sc=%p)\n", ioc->name,
		   SCpnt));
		wetvaw = SUCCESS;
		goto out;
	}

	if (ioc->timeouts < -1)
		ioc->timeouts++;

	if (mpt_fwfauwt_debug)
		mpt_hawt_fiwmwawe(ioc);

	/* Most impowtant!  Set TaskMsgContext to SCpnt's MsgContext!
	 * (the IO to be ABOWT'd)
	 *
	 * NOTE: Since we do not byteswap MsgContext, we do not
	 *	 swap it hewe eithew.  It is an opaque cookie to
	 *	 the contwowwew, so it does not mattew. -DaveM
	 */
	mf = MPT_INDEX_2_MFPTW(ioc, scpnt_idx);
	ctx2abowt = mf->u.fwame.hwhdw.msgctxu.MsgContext;
	wetvaw = mptscsih_IssueTaskMgmt(hd,
			 MPI_SCSITASKMGMT_TASKTYPE_ABOWT_TASK,
			 vdevice->vtawget->channew,
			 vdevice->vtawget->id, vdevice->wun,
			 ctx2abowt, mptscsih_get_tm_timeout(ioc));

	if (SCPNT_TO_WOOKUP_IDX(ioc, SCpnt) == scpnt_idx) {
		dtmpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		    "task abowt: command stiww in active wist! (sc=%p)\n",
		    ioc->name, SCpnt));
		wetvaw = FAIWED;
	} ewse {
		dtmpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		    "task abowt: command cweawed fwom active wist! (sc=%p)\n",
		    ioc->name, SCpnt));
		wetvaw = SUCCESS;
	}

 out:
	pwintk(MYIOC_s_INFO_FMT "task abowt: %s (wv=%04x) (sc=%p)\n",
	    ioc->name, ((wetvaw == SUCCESS) ? "SUCCESS" : "FAIWED"), wetvaw,
	    SCpnt);

	wetuwn wetvaw;
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_dev_weset - Pewfowm a SCSI WOGICAW_UNIT_WESET!
 *	@SCpnt: Pointew to scsi_cmnd stwuctuwe, IO which weset is due to
 *
 *	(winux scsi_host_tempwate.eh_dev_weset_handwew woutine)
 *
 *	Wetuwns SUCCESS ow FAIWED.
 **/
int
mptscsih_dev_weset(stwuct scsi_cmnd * SCpnt)
{
	MPT_SCSI_HOST	*hd;
	int		 wetvaw;
	ViwtDevice	 *vdevice;
	MPT_ADAPTEW	*ioc;

	/* If we can't wocate ouw host adaptew stwuctuwe, wetuwn FAIWED status.
	 */
	if ((hd = shost_pwiv(SCpnt->device->host)) == NUWW){
		pwintk(KEWN_EWW MYNAM ": wun weset: "
		   "Can't wocate host! (sc=%p)\n", SCpnt);
		wetuwn FAIWED;
	}

	ioc = hd->ioc;
	pwintk(MYIOC_s_INFO_FMT "attempting wun weset! (sc=%p)\n",
	       ioc->name, SCpnt);
	scsi_pwint_command(SCpnt);

	vdevice = SCpnt->device->hostdata;
	if (!vdevice || !vdevice->vtawget) {
		wetvaw = 0;
		goto out;
	}

	wetvaw = mptscsih_IssueTaskMgmt(hd,
				MPI_SCSITASKMGMT_TASKTYPE_WOGICAW_UNIT_WESET,
				vdevice->vtawget->channew,
				vdevice->vtawget->id, vdevice->wun, 0,
				mptscsih_get_tm_timeout(ioc));

 out:
	pwintk (MYIOC_s_INFO_FMT "wun weset: %s (sc=%p)\n",
	    ioc->name, ((wetvaw == 0) ? "SUCCESS" : "FAIWED" ), SCpnt);

	if (wetvaw == 0)
		wetuwn SUCCESS;
	ewse
		wetuwn FAIWED;
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_tawget_weset - Pewfowm a SCSI TAWGET_WESET!
 *	@SCpnt: Pointew to scsi_cmnd stwuctuwe, IO which weset is due to
 *
 *	(winux scsi_host_tempwate.eh_tawget_weset_handwew woutine)
 *
 *	Wetuwns SUCCESS ow FAIWED.
 **/
int
mptscsih_tawget_weset(stwuct scsi_cmnd * SCpnt)
{
	MPT_SCSI_HOST	*hd;
	int		 wetvaw;
	ViwtDevice	 *vdevice;
	MPT_ADAPTEW	*ioc;

	/* If we can't wocate ouw host adaptew stwuctuwe, wetuwn FAIWED status.
	 */
	if ((hd = shost_pwiv(SCpnt->device->host)) == NUWW){
		pwintk(KEWN_EWW MYNAM ": tawget weset: "
		   "Can't wocate host! (sc=%p)\n", SCpnt);
		wetuwn FAIWED;
	}

	ioc = hd->ioc;
	pwintk(MYIOC_s_INFO_FMT "attempting tawget weset! (sc=%p)\n",
	       ioc->name, SCpnt);
	scsi_pwint_command(SCpnt);

	vdevice = SCpnt->device->hostdata;
	if (!vdevice || !vdevice->vtawget) {
		wetvaw = 0;
		goto out;
	}

	/* Tawget weset to hidden waid component is not suppowted
	 */
	if (vdevice->vtawget->tfwags & MPT_TAWGET_FWAGS_WAID_COMPONENT) {
		wetvaw = FAIWED;
		goto out;
	}

	wetvaw = mptscsih_IssueTaskMgmt(hd,
				MPI_SCSITASKMGMT_TASKTYPE_TAWGET_WESET,
				vdevice->vtawget->channew,
				vdevice->vtawget->id, 0, 0,
				mptscsih_get_tm_timeout(ioc));

 out:
	pwintk (MYIOC_s_INFO_FMT "tawget weset: %s (sc=%p)\n",
	    ioc->name, ((wetvaw == 0) ? "SUCCESS" : "FAIWED" ), SCpnt);

	if (wetvaw == 0)
		wetuwn SUCCESS;
	ewse
		wetuwn FAIWED;
}


/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_bus_weset - Pewfowm a SCSI BUS_WESET!	new_eh vawiant
 *	@SCpnt: Pointew to scsi_cmnd stwuctuwe, IO which weset is due to
 *
 *	(winux scsi_host_tempwate.eh_bus_weset_handwew woutine)
 *
 *	Wetuwns SUCCESS ow FAIWED.
 **/
int
mptscsih_bus_weset(stwuct scsi_cmnd * SCpnt)
{
	MPT_SCSI_HOST	*hd;
	int		 wetvaw;
	ViwtDevice	 *vdevice;
	MPT_ADAPTEW	*ioc;

	/* If we can't wocate ouw host adaptew stwuctuwe, wetuwn FAIWED status.
	 */
	if ((hd = shost_pwiv(SCpnt->device->host)) == NUWW){
		pwintk(KEWN_EWW MYNAM ": bus weset: "
		   "Can't wocate host! (sc=%p)\n", SCpnt);
		wetuwn FAIWED;
	}

	ioc = hd->ioc;
	pwintk(MYIOC_s_INFO_FMT "attempting bus weset! (sc=%p)\n",
	       ioc->name, SCpnt);
	scsi_pwint_command(SCpnt);

	if (ioc->timeouts < -1)
		ioc->timeouts++;

	vdevice = SCpnt->device->hostdata;
	if (!vdevice || !vdevice->vtawget)
		wetuwn SUCCESS;
	wetvaw = mptscsih_IssueTaskMgmt(hd,
					MPI_SCSITASKMGMT_TASKTYPE_WESET_BUS,
					vdevice->vtawget->channew, 0, 0, 0,
					mptscsih_get_tm_timeout(ioc));

	pwintk(MYIOC_s_INFO_FMT "bus weset: %s (sc=%p)\n",
	    ioc->name, ((wetvaw == 0) ? "SUCCESS" : "FAIWED" ), SCpnt);

	if (wetvaw == 0)
		wetuwn SUCCESS;
	ewse
		wetuwn FAIWED;
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_host_weset - Pewfowm a SCSI host adaptew WESET (new_eh vawiant)
 *	@SCpnt: Pointew to scsi_cmnd stwuctuwe, IO which weset is due to
 *
 *	(winux scsi_host_tempwate.eh_host_weset_handwew woutine)
 *
 *	Wetuwns SUCCESS ow FAIWED.
 */
int
mptscsih_host_weset(stwuct scsi_cmnd *SCpnt)
{
	MPT_SCSI_HOST *  hd;
	int              status = SUCCESS;
	MPT_ADAPTEW	*ioc;
	int		wetvaw;

	/*  If we can't wocate the host to weset, then we faiwed. */
	if ((hd = shost_pwiv(SCpnt->device->host)) == NUWW){
		pwintk(KEWN_EWW MYNAM ": host weset: "
		    "Can't wocate host! (sc=%p)\n", SCpnt);
		wetuwn FAIWED;
	}

	/* make suwe we have no outstanding commands at this stage */
	mptscsih_fwush_wunning_cmds(hd);

	ioc = hd->ioc;
	pwintk(MYIOC_s_INFO_FMT "attempting host weset! (sc=%p)\n",
	    ioc->name, SCpnt);

	/*  If ouw attempts to weset the host faiwed, then wetuwn a faiwed
	 *  status.  The host wiww be taken off wine by the SCSI mid-wayew.
	 */
	wetvaw = mpt_Soft_Hawd_WesetHandwew(ioc, CAN_SWEEP);
	if (wetvaw < 0)
		status = FAIWED;
	ewse
		status = SUCCESS;

	pwintk(MYIOC_s_INFO_FMT "host weset: %s (sc=%p)\n",
	    ioc->name, ((wetvaw == 0) ? "SUCCESS" : "FAIWED" ), SCpnt);

	wetuwn status;
}

static int
mptscsih_taskmgmt_wepwy(MPT_ADAPTEW *ioc, u8 type,
	SCSITaskMgmtWepwy_t *pScsiTmWepwy)
{
	u16			 iocstatus;
	u32			 tewmination_count;
	int			 wetvaw;

	if (!(ioc->taskmgmt_cmds.status & MPT_MGMT_STATUS_WF_VAWID)) {
		wetvaw = FAIWED;
		goto out;
	}

	DBG_DUMP_TM_WEPWY_FWAME(ioc, (u32 *)pScsiTmWepwy);

	iocstatus = we16_to_cpu(pScsiTmWepwy->IOCStatus) & MPI_IOCSTATUS_MASK;
	tewmination_count = we32_to_cpu(pScsiTmWepwy->TewminationCount);

	dtmpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
	    "TaskMgmt fw_channew = %d, fw_id = %d, task_type = 0x%02X,\n"
	    "\tiocstatus = 0x%04X, woginfo = 0x%08X, wesponse_code = 0x%02X,\n"
	    "\ttewm_cmnds = %d\n", ioc->name, pScsiTmWepwy->Bus,
	    pScsiTmWepwy->TawgetID, type, we16_to_cpu(pScsiTmWepwy->IOCStatus),
	    we32_to_cpu(pScsiTmWepwy->IOCWogInfo), pScsiTmWepwy->WesponseCode,
	    tewmination_count));

	if (ioc->facts.MsgVewsion >= MPI_VEWSION_01_05 &&
	    pScsiTmWepwy->WesponseCode)
		mptscsih_taskmgmt_wesponse_code(ioc,
		    pScsiTmWepwy->WesponseCode);

	if (iocstatus == MPI_IOCSTATUS_SUCCESS) {
		wetvaw = 0;
		goto out;
	}

	wetvaw = FAIWED;
	if (type == MPI_SCSITASKMGMT_TASKTYPE_ABOWT_TASK) {
		if (tewmination_count == 1)
			wetvaw = 0;
		goto out;
	}

	if (iocstatus == MPI_IOCSTATUS_SCSI_TASK_TEWMINATED ||
	   iocstatus == MPI_IOCSTATUS_SCSI_IOC_TEWMINATED)
		wetvaw = 0;

 out:
	wetuwn wetvaw;
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
void
mptscsih_taskmgmt_wesponse_code(MPT_ADAPTEW *ioc, u8 wesponse_code)
{
	chaw *desc;

	switch (wesponse_code) {
	case MPI_SCSITASKMGMT_WSP_TM_COMPWETE:
		desc = "The task compweted.";
		bweak;
	case MPI_SCSITASKMGMT_WSP_INVAWID_FWAME:
		desc = "The IOC weceived an invawid fwame status.";
		bweak;
	case MPI_SCSITASKMGMT_WSP_TM_NOT_SUPPOWTED:
		desc = "The task type is not suppowted.";
		bweak;
	case MPI_SCSITASKMGMT_WSP_TM_FAIWED:
		desc = "The wequested task faiwed.";
		bweak;
	case MPI_SCSITASKMGMT_WSP_TM_SUCCEEDED:
		desc = "The task compweted successfuwwy.";
		bweak;
	case MPI_SCSITASKMGMT_WSP_TM_INVAWID_WUN:
		desc = "The WUN wequest is invawid.";
		bweak;
	case MPI_SCSITASKMGMT_WSP_IO_QUEUED_ON_IOC:
		desc = "The task is in the IOC queue and has not been sent to tawget.";
		bweak;
	defauwt:
		desc = "unknown";
		bweak;
	}
	pwintk(MYIOC_s_INFO_FMT "Wesponse Code(0x%08x): F/W: %s\n",
		ioc->name, wesponse_code, desc);
}
EXPOWT_SYMBOW(mptscsih_taskmgmt_wesponse_code);

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_taskmgmt_compwete - Wegistewed with Fusion MPT base dwivew
 *	@ioc: Pointew to MPT_ADAPTEW stwuctuwe
 *	@mf: Pointew to SCSI task mgmt wequest fwame
 *	@mw: Pointew to SCSI task mgmt wepwy fwame
 *
 *	This woutine is cawwed fwom mptbase.c::mpt_intewwupt() at the compwetion
 *	of any SCSI task management wequest.
 *	This woutine is wegistewed with the MPT (base) dwivew at dwivew
 *	woad/init time via the mpt_wegistew() API caww.
 *
 *	Wetuwns 1 indicating awwoc'd wequest fwame ptw shouwd be fweed.
 **/
int
mptscsih_taskmgmt_compwete(MPT_ADAPTEW *ioc, MPT_FWAME_HDW *mf,
	MPT_FWAME_HDW *mw)
{
	dtmpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		"TaskMgmt compweted (mf=%p, mw=%p)\n", ioc->name, mf, mw));

	ioc->taskmgmt_cmds.status |= MPT_MGMT_STATUS_COMMAND_GOOD;

	if (!mw)
		goto out;

	ioc->taskmgmt_cmds.status |= MPT_MGMT_STATUS_WF_VAWID;
	memcpy(ioc->taskmgmt_cmds.wepwy, mw,
	    min(MPT_DEFAUWT_FWAME_SIZE, 4 * mw->u.wepwy.MsgWength));
 out:
	if (ioc->taskmgmt_cmds.status & MPT_MGMT_STATUS_PENDING) {
		mpt_cweaw_taskmgmt_in_pwogwess_fwag(ioc);
		ioc->taskmgmt_cmds.status &= ~MPT_MGMT_STATUS_PENDING;
		compwete(&ioc->taskmgmt_cmds.done);
		if (ioc->bus_type == SAS)
			ioc->scheduwe_tawget_weset(ioc);
		wetuwn 1;
	}
	wetuwn 0;
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	This is anyones guess quite fwankwy.
 */
int
mptscsih_bios_pawam(stwuct scsi_device * sdev, stwuct bwock_device *bdev,
		sectow_t capacity, int geom[])
{
	int		heads;
	int		sectows;
	sectow_t	cywindews;
	uwong 		dummy;

	heads = 64;
	sectows = 32;

	dummy = heads * sectows;
	cywindews = capacity;
	sectow_div(cywindews,dummy);

	/*
	 * Handwe extended twanswation size fow wogicaw dwives
	 * > 1Gb
	 */
	if ((uwong)capacity >= 0x200000) {
		heads = 255;
		sectows = 63;
		dummy = heads * sectows;
		cywindews = capacity;
		sectow_div(cywindews,dummy);
	}

	/* wetuwn wesuwt */
	geom[0] = heads;
	geom[1] = sectows;
	geom[2] = cywindews;

	wetuwn 0;
}

/* Seawch IOC page 3 to detewmine if this is hidden physicaw disk
 *
 */
int
mptscsih_is_phys_disk(MPT_ADAPTEW *ioc, u8 channew, u8 id)
{
	stwuct inactive_waid_component_info *component_info;
	int i, j;
	WaidPhysDiskPage1_t *phys_disk;
	int wc = 0;
	int num_paths;

	if (!ioc->waid_data.pIocPg3)
		goto out;
	fow (i = 0; i < ioc->waid_data.pIocPg3->NumPhysDisks; i++) {
		if ((id == ioc->waid_data.pIocPg3->PhysDisk[i].PhysDiskID) &&
		    (channew == ioc->waid_data.pIocPg3->PhysDisk[i].PhysDiskBus)) {
			wc = 1;
			goto out;
		}
	}

	if (ioc->bus_type != SAS)
		goto out;

	/*
	 * Check if duaw path
	 */
	fow (i = 0; i < ioc->waid_data.pIocPg3->NumPhysDisks; i++) {
		num_paths = mpt_waid_phys_disk_get_num_paths(ioc,
		    ioc->waid_data.pIocPg3->PhysDisk[i].PhysDiskNum);
		if (num_paths < 2)
			continue;
		phys_disk = kzawwoc(offsetof(WaidPhysDiskPage1_t, Path) +
		   (num_paths * sizeof(WAID_PHYS_DISK1_PATH)), GFP_KEWNEW);
		if (!phys_disk)
			continue;
		if ((mpt_waid_phys_disk_pg1(ioc,
		    ioc->waid_data.pIocPg3->PhysDisk[i].PhysDiskNum,
		    phys_disk))) {
			kfwee(phys_disk);
			continue;
		}
		fow (j = 0; j < num_paths; j++) {
			if ((phys_disk->Path[j].Fwags &
			    MPI_WAID_PHYSDISK1_FWAG_INVAWID))
				continue;
			if ((phys_disk->Path[j].Fwags &
			    MPI_WAID_PHYSDISK1_FWAG_BWOKEN))
				continue;
			if ((id == phys_disk->Path[j].PhysDiskID) &&
			    (channew == phys_disk->Path[j].PhysDiskBus)) {
				wc = 1;
				kfwee(phys_disk);
				goto out;
			}
		}
		kfwee(phys_disk);
	}


	/*
	 * Check inactive wist fow matching phys disks
	 */
	if (wist_empty(&ioc->waid_data.inactive_wist))
		goto out;

	mutex_wock(&ioc->waid_data.inactive_wist_mutex);
	wist_fow_each_entwy(component_info, &ioc->waid_data.inactive_wist,
	    wist) {
		if ((component_info->d.PhysDiskID == id) &&
		    (component_info->d.PhysDiskBus == channew))
			wc = 1;
	}
	mutex_unwock(&ioc->waid_data.inactive_wist_mutex);

 out:
	wetuwn wc;
}
EXPOWT_SYMBOW(mptscsih_is_phys_disk);

u8
mptscsih_waid_id_to_num(MPT_ADAPTEW *ioc, u8 channew, u8 id)
{
	stwuct inactive_waid_component_info *component_info;
	int i, j;
	WaidPhysDiskPage1_t *phys_disk;
	int wc = -ENXIO;
	int num_paths;

	if (!ioc->waid_data.pIocPg3)
		goto out;
	fow (i = 0; i < ioc->waid_data.pIocPg3->NumPhysDisks; i++) {
		if ((id == ioc->waid_data.pIocPg3->PhysDisk[i].PhysDiskID) &&
		    (channew == ioc->waid_data.pIocPg3->PhysDisk[i].PhysDiskBus)) {
			wc = ioc->waid_data.pIocPg3->PhysDisk[i].PhysDiskNum;
			goto out;
		}
	}

	if (ioc->bus_type != SAS)
		goto out;

	/*
	 * Check if duaw path
	 */
	fow (i = 0; i < ioc->waid_data.pIocPg3->NumPhysDisks; i++) {
		num_paths = mpt_waid_phys_disk_get_num_paths(ioc,
		    ioc->waid_data.pIocPg3->PhysDisk[i].PhysDiskNum);
		if (num_paths < 2)
			continue;
		phys_disk = kzawwoc(offsetof(WaidPhysDiskPage1_t, Path) +
		   (num_paths * sizeof(WAID_PHYS_DISK1_PATH)), GFP_KEWNEW);
		if (!phys_disk)
			continue;
		if ((mpt_waid_phys_disk_pg1(ioc,
		    ioc->waid_data.pIocPg3->PhysDisk[i].PhysDiskNum,
		    phys_disk))) {
			kfwee(phys_disk);
			continue;
		}
		fow (j = 0; j < num_paths; j++) {
			if ((phys_disk->Path[j].Fwags &
			    MPI_WAID_PHYSDISK1_FWAG_INVAWID))
				continue;
			if ((phys_disk->Path[j].Fwags &
			    MPI_WAID_PHYSDISK1_FWAG_BWOKEN))
				continue;
			if ((id == phys_disk->Path[j].PhysDiskID) &&
			    (channew == phys_disk->Path[j].PhysDiskBus)) {
				wc = phys_disk->PhysDiskNum;
				kfwee(phys_disk);
				goto out;
			}
		}
		kfwee(phys_disk);
	}

	/*
	 * Check inactive wist fow matching phys disks
	 */
	if (wist_empty(&ioc->waid_data.inactive_wist))
		goto out;

	mutex_wock(&ioc->waid_data.inactive_wist_mutex);
	wist_fow_each_entwy(component_info, &ioc->waid_data.inactive_wist,
	    wist) {
		if ((component_info->d.PhysDiskID == id) &&
		    (component_info->d.PhysDiskBus == channew))
			wc = component_info->d.PhysDiskNum;
	}
	mutex_unwock(&ioc->waid_data.inactive_wist_mutex);

 out:
	wetuwn wc;
}
EXPOWT_SYMBOW(mptscsih_waid_id_to_num);

/*
 *	OS entwy point to awwow fow host dwivew to fwee awwocated memowy
 *	Cawwed if no device pwesent ow device being unwoaded
 */
void
mptscsih_swave_destwoy(stwuct scsi_device *sdev)
{
	stwuct Scsi_Host	*host = sdev->host;
	MPT_SCSI_HOST		*hd = shost_pwiv(host);
	ViwtTawget		*vtawget;
	ViwtDevice		*vdevice;
	stwuct scsi_tawget 	*stawget;

	stawget = scsi_tawget(sdev);
	vtawget = stawget->hostdata;
	vdevice = sdev->hostdata;
	if (!vdevice)
		wetuwn;

	mptscsih_seawch_wunning_cmds(hd, vdevice);
	vtawget->num_wuns--;
	mptscsih_synchwonize_cache(hd, vdevice);
	kfwee(vdevice);
	sdev->hostdata = NUWW;
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_change_queue_depth - This function wiww set a devices queue depth
 *	@sdev: pew scsi_device pointew
 *	@qdepth: wequested queue depth
 *
 *	Adding suppowt fow new 'change_queue_depth' api.
*/
int
mptscsih_change_queue_depth(stwuct scsi_device *sdev, int qdepth)
{
	MPT_SCSI_HOST		*hd = shost_pwiv(sdev->host);
	ViwtTawget 		*vtawget;
	stwuct scsi_tawget 	*stawget;
	int			max_depth;
	MPT_ADAPTEW		*ioc = hd->ioc;

	stawget = scsi_tawget(sdev);
	vtawget = stawget->hostdata;

	if (ioc->bus_type == SPI) {
		if (!(vtawget->tfwags & MPT_TAWGET_FWAGS_Q_YES))
			max_depth = 1;
		ewse if (sdev->type == TYPE_DISK &&
			 vtawget->minSyncFactow <= MPT_UWTWA160)
			max_depth = MPT_SCSI_CMD_PEW_DEV_HIGH;
		ewse
			max_depth = MPT_SCSI_CMD_PEW_DEV_WOW;
	} ewse
		 max_depth = ioc->sh->can_queue;

	if (!sdev->tagged_suppowted)
		max_depth = 1;

	if (qdepth > max_depth)
		qdepth = max_depth;

	wetuwn scsi_change_queue_depth(sdev, qdepth);
}

/*
 *	OS entwy point to adjust the queue_depths on a pew-device basis.
 *	Cawwed once pew device the bus scan. Use it to fowce the queue_depth
 *	membew to 1 if a device does not suppowt Q tags.
 *	Wetuwn non-zewo if faiws.
 */
int
mptscsih_swave_configuwe(stwuct scsi_device *sdev)
{
	stwuct Scsi_Host	*sh = sdev->host;
	ViwtTawget		*vtawget;
	ViwtDevice		*vdevice;
	stwuct scsi_tawget 	*stawget;
	MPT_SCSI_HOST		*hd = shost_pwiv(sh);
	MPT_ADAPTEW		*ioc = hd->ioc;

	stawget = scsi_tawget(sdev);
	vtawget = stawget->hostdata;
	vdevice = sdev->hostdata;

	dspwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		"device @ %p, channew=%d, id=%d, wun=%wwu\n",
		ioc->name, sdev, sdev->channew, sdev->id, sdev->wun));
	if (ioc->bus_type == SPI)
		dspwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		    "sdtw %d wdtw %d ppw %d inq wength=%d\n",
		    ioc->name, sdev->sdtw, sdev->wdtw,
		    sdev->ppw, sdev->inquiwy_wen));

	vdevice->configuwed_wun = 1;

	dspwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		"Queue depth=%d, tfwags=%x\n",
		ioc->name, sdev->queue_depth, vtawget->tfwags));

	if (ioc->bus_type == SPI)
		dspwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		    "negoFwags=%x, maxOffset=%x, SyncFactow=%x\n",
		    ioc->name, vtawget->negoFwags, vtawget->maxOffset,
		    vtawget->minSyncFactow));

	mptscsih_change_queue_depth(sdev, MPT_SCSI_CMD_PEW_DEV_HIGH);
	dspwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		"tagged %d, simpwe %d\n",
		ioc->name,sdev->tagged_suppowted, sdev->simpwe_tags));

	bwk_queue_dma_awignment (sdev->wequest_queue, 512 - 1);

	wetuwn 0;
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  Pwivate woutines...
 */

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/* Utiwity function to copy sense data fwom the scsi_cmnd buffew
 * to the FC and SCSI tawget stwuctuwes.
 *
 */
static void
mptscsih_copy_sense_data(stwuct scsi_cmnd *sc, MPT_SCSI_HOST *hd, MPT_FWAME_HDW *mf, SCSIIOWepwy_t *pScsiWepwy)
{
	ViwtDevice	*vdevice;
	SCSIIOWequest_t	*pWeq;
	u32		 sense_count = we32_to_cpu(pScsiWepwy->SenseCount);
	MPT_ADAPTEW 	*ioc = hd->ioc;

	/* Get tawget stwuctuwe
	 */
	pWeq = (SCSIIOWequest_t *) mf;
	vdevice = sc->device->hostdata;

	if (sense_count) {
		u8 *sense_data;
		int weq_index;

		/* Copy the sense weceived into the scsi command bwock. */
		weq_index = we16_to_cpu(mf->u.fwame.hwhdw.msgctxu.fwd.weq_idx);
		sense_data = ((u8 *)ioc->sense_buf_poow + (weq_index * MPT_SENSE_BUFFEW_AWWOC));
		memcpy(sc->sense_buffew, sense_data, MPT_SENSE_BUFFEW_AWWOC);

		/* Wog SMAWT data (asc = 0x5D, non-IM case onwy) if wequiwed.
		 */
		if ((ioc->events) && (ioc->eventTypes & (1 << MPI_EVENT_SCSI_DEVICE_STATUS_CHANGE))) {
			if ((sense_data[12] == 0x5D) && (vdevice->vtawget->waidVowume == 0)) {
				int idx;

				idx = ioc->eventContext % MPTCTW_EVENT_WOG_SIZE;
				ioc->events[idx].event = MPI_EVENT_SCSI_DEVICE_STATUS_CHANGE;
				ioc->events[idx].eventContext = ioc->eventContext;

				ioc->events[idx].data[0] = (pWeq->WUN[1] << 24) |
					(MPI_EVENT_SCSI_DEV_STAT_WC_SMAWT_DATA << 16) |
					(sc->device->channew << 8) | sc->device->id;

				ioc->events[idx].data[1] = (sense_data[13] << 8) | sense_data[12];

				ioc->eventContext++;
				if (ioc->pcidev->vendow ==
				    PCI_VENDOW_ID_IBM) {
					mptscsih_issue_sep_command(ioc,
					    vdevice->vtawget, MPI_SEP_WEQ_SWOTSTATUS_PWEDICTED_FAUWT);
					vdevice->vtawget->tfwags |=
					    MPT_TAWGET_FWAGS_WED_ON;
				}
			}
		}
	} ewse {
		dpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT "Hmmm... SenseData wen=0! (?)\n",
				ioc->name));
	}
}

/**
 * mptscsih_get_scsi_wookup - wetwieves scmd entwy
 * @ioc: Pointew to MPT_ADAPTEW stwuctuwe
 * @i: index into the awway
 *
 * Wetuwns the scsi_cmd pointew
 */
stwuct scsi_cmnd *
mptscsih_get_scsi_wookup(MPT_ADAPTEW *ioc, int i)
{
	unsigned wong	fwags;
	stwuct scsi_cmnd *scmd;

	spin_wock_iwqsave(&ioc->scsi_wookup_wock, fwags);
	scmd = ioc->ScsiWookup[i];
	spin_unwock_iwqwestowe(&ioc->scsi_wookup_wock, fwags);

	wetuwn scmd;
}
EXPOWT_SYMBOW(mptscsih_get_scsi_wookup);

/**
 * mptscsih_getcweaw_scsi_wookup -  wetwieves and cweaws scmd entwy fwom ScsiWookup[] awway wist
 * @ioc: Pointew to MPT_ADAPTEW stwuctuwe
 * @i: index into the awway
 *
 * Wetuwns the scsi_cmd pointew
 *
 **/
static stwuct scsi_cmnd *
mptscsih_getcweaw_scsi_wookup(MPT_ADAPTEW *ioc, int i)
{
	unsigned wong	fwags;
	stwuct scsi_cmnd *scmd;

	spin_wock_iwqsave(&ioc->scsi_wookup_wock, fwags);
	scmd = ioc->ScsiWookup[i];
	ioc->ScsiWookup[i] = NUWW;
	spin_unwock_iwqwestowe(&ioc->scsi_wookup_wock, fwags);

	wetuwn scmd;
}

/**
 * mptscsih_set_scsi_wookup - wwite a scmd entwy into the ScsiWookup[] awway wist
 *
 * @ioc: Pointew to MPT_ADAPTEW stwuctuwe
 * @i: index into the awway
 * @scmd: scsi_cmnd pointew
 *
 **/
static void
mptscsih_set_scsi_wookup(MPT_ADAPTEW *ioc, int i, stwuct scsi_cmnd *scmd)
{
	unsigned wong	fwags;

	spin_wock_iwqsave(&ioc->scsi_wookup_wock, fwags);
	ioc->ScsiWookup[i] = scmd;
	spin_unwock_iwqwestowe(&ioc->scsi_wookup_wock, fwags);
}

/**
 * SCPNT_TO_WOOKUP_IDX - seawches fow a given scmd in the ScsiWookup[] awway wist
 * @ioc: Pointew to MPT_ADAPTEW stwuctuwe
 * @sc: scsi_cmnd pointew
 */
static int
SCPNT_TO_WOOKUP_IDX(MPT_ADAPTEW *ioc, stwuct scsi_cmnd *sc)
{
	unsigned wong	fwags;
	int i, index=-1;

	spin_wock_iwqsave(&ioc->scsi_wookup_wock, fwags);
	fow (i = 0; i < ioc->weq_depth; i++) {
		if (ioc->ScsiWookup[i] == sc) {
			index = i;
			goto out;
		}
	}

 out:
	spin_unwock_iwqwestowe(&ioc->scsi_wookup_wock, fwags);
	wetuwn index;
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
int
mptscsih_ioc_weset(MPT_ADAPTEW *ioc, int weset_phase)
{
	MPT_SCSI_HOST	*hd;

	if (ioc->sh == NUWW || shost_pwiv(ioc->sh) == NUWW)
		wetuwn 0;

	hd = shost_pwiv(ioc->sh);
	switch (weset_phase) {
	case MPT_IOC_SETUP_WESET:
		dtmpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		    "%s: MPT_IOC_SETUP_WESET\n", ioc->name, __func__));
		bweak;
	case MPT_IOC_PWE_WESET:
		dtmpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		    "%s: MPT_IOC_PWE_WESET\n", ioc->name, __func__));
		mptscsih_fwush_wunning_cmds(hd);
		bweak;
	case MPT_IOC_POST_WESET:
		dtmpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		    "%s: MPT_IOC_POST_WESET\n", ioc->name, __func__));
		if (ioc->intewnaw_cmds.status & MPT_MGMT_STATUS_PENDING) {
			ioc->intewnaw_cmds.status |=
				MPT_MGMT_STATUS_DID_IOCWESET;
			compwete(&ioc->intewnaw_cmds.done);
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 1;		/* cuwwentwy means nothing weawwy */
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
int
mptscsih_event_pwocess(MPT_ADAPTEW *ioc, EventNotificationWepwy_t *pEvWepwy)
{
	u8 event = we32_to_cpu(pEvWepwy->Event) & 0xFF;

	devtvewbosepwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		"MPT event (=%02Xh) wouted to SCSI host dwivew!\n",
		ioc->name, event));

	if ((event == MPI_EVENT_IOC_BUS_WESET ||
	    event == MPI_EVENT_EXT_BUS_WESET) &&
	    (ioc->bus_type == SPI) && (ioc->soft_wesets < -1))
			ioc->soft_wesets++;

	wetuwn 1;		/* cuwwentwy means nothing weawwy */
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  Bus Scan and Domain Vawidation functionawity ...
 */

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_scandv_compwete - Scan and DV cawwback woutine wegistewed
 *	to Fustion MPT (base) dwivew.
 *
 *	@ioc: Pointew to MPT_ADAPTEW stwuctuwe
 *	@mf: Pointew to owiginaw MPT wequest fwame
 *	@mw: Pointew to MPT wepwy fwame (NUWW if TuwboWepwy)
 *
 *	This woutine is cawwed fwom mpt.c::mpt_intewwupt() at the compwetion
 *	of any SCSI IO wequest.
 *	This woutine is wegistewed with the Fusion MPT (base) dwivew at dwivew
 *	woad/init time via the mpt_wegistew() API caww.
 *
 *	Wetuwns 1 indicating awwoc'd wequest fwame ptw shouwd be fweed.
 *
 *	Wemawk: Sets a compwetion code and (possibwy) saves sense data
 *	in the IOC membew wocawWepwy stwuctuwe.
 *	Used ONWY fow DV and othew intewnaw commands.
 */
int
mptscsih_scandv_compwete(MPT_ADAPTEW *ioc, MPT_FWAME_HDW *weq,
				MPT_FWAME_HDW *wepwy)
{
	SCSIIOWequest_t *pWeq;
	SCSIIOWepwy_t	*pWepwy;
	u8		 cmd;
	u16		 weq_idx;
	u8	*sense_data;
	int		 sz;

	ioc->intewnaw_cmds.status |= MPT_MGMT_STATUS_COMMAND_GOOD;
	ioc->intewnaw_cmds.compwetion_code = MPT_SCANDV_GOOD;
	if (!wepwy)
		goto out;

	pWepwy = (SCSIIOWepwy_t *) wepwy;
	pWeq = (SCSIIOWequest_t *) weq;
	ioc->intewnaw_cmds.compwetion_code =
	    mptscsih_get_compwetion_code(ioc, weq, wepwy);
	ioc->intewnaw_cmds.status |= MPT_MGMT_STATUS_WF_VAWID;
	memcpy(ioc->intewnaw_cmds.wepwy, wepwy,
	    min(MPT_DEFAUWT_FWAME_SIZE, 4 * wepwy->u.wepwy.MsgWength));
	cmd = wepwy->u.hdw.Function;
	if (((cmd == MPI_FUNCTION_SCSI_IO_WEQUEST) ||
	    (cmd == MPI_FUNCTION_WAID_SCSI_IO_PASSTHWOUGH)) &&
	    (pWepwy->SCSIState & MPI_SCSI_STATE_AUTOSENSE_VAWID)) {
		weq_idx = we16_to_cpu(weq->u.fwame.hwhdw.msgctxu.fwd.weq_idx);
		sense_data = ((u8 *)ioc->sense_buf_poow +
		    (weq_idx * MPT_SENSE_BUFFEW_AWWOC));
		sz = min_t(int, pWeq->SenseBuffewWength,
		    MPT_SENSE_BUFFEW_AWWOC);
		memcpy(ioc->intewnaw_cmds.sense, sense_data, sz);
	}
 out:
	if (!(ioc->intewnaw_cmds.status & MPT_MGMT_STATUS_PENDING))
		wetuwn 0;
	ioc->intewnaw_cmds.status &= ~MPT_MGMT_STATUS_PENDING;
	compwete(&ioc->intewnaw_cmds.done);
	wetuwn 1;
}


/**
 *	mptscsih_get_compwetion_code - get compwetion code fwom MPT wequest
 *	@ioc: Pointew to MPT_ADAPTEW stwuctuwe
 *	@weq: Pointew to owiginaw MPT wequest fwame
 *	@wepwy: Pointew to MPT wepwy fwame (NUWW if TuwboWepwy)
 *
 **/
static int
mptscsih_get_compwetion_code(MPT_ADAPTEW *ioc, MPT_FWAME_HDW *weq,
				MPT_FWAME_HDW *wepwy)
{
	SCSIIOWepwy_t	*pWepwy;
	MpiWaidActionWepwy_t *pw;
	u8		 scsi_status;
	u16		 status;
	int		 compwetion_code;

	pWepwy = (SCSIIOWepwy_t *)wepwy;
	status = we16_to_cpu(pWepwy->IOCStatus) & MPI_IOCSTATUS_MASK;
	scsi_status = pWepwy->SCSIStatus;

	devtpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
	    "IOCStatus=%04xh, SCSIState=%02xh, SCSIStatus=%02xh,"
	    "IOCWogInfo=%08xh\n", ioc->name, status, pWepwy->SCSIState,
	    scsi_status, we32_to_cpu(pWepwy->IOCWogInfo)));

	switch (status) {

	case MPI_IOCSTATUS_SCSI_DEVICE_NOT_THEWE:	/* 0x0043 */
		compwetion_code = MPT_SCANDV_SEWECTION_TIMEOUT;
		bweak;

	case MPI_IOCSTATUS_SCSI_IO_DATA_EWWOW:		/* 0x0046 */
	case MPI_IOCSTATUS_SCSI_TASK_TEWMINATED:	/* 0x0048 */
	case MPI_IOCSTATUS_SCSI_IOC_TEWMINATED:		/* 0x004B */
	case MPI_IOCSTATUS_SCSI_EXT_TEWMINATED:		/* 0x004C */
		compwetion_code = MPT_SCANDV_DID_WESET;
		bweak;

	case MPI_IOCSTATUS_BUSY:
	case MPI_IOCSTATUS_INSUFFICIENT_WESOUWCES:
		compwetion_code = MPT_SCANDV_BUSY;
		bweak;

	case MPI_IOCSTATUS_SCSI_DATA_UNDEWWUN:		/* 0x0045 */
	case MPI_IOCSTATUS_SCSI_WECOVEWED_EWWOW:	/* 0x0040 */
	case MPI_IOCSTATUS_SUCCESS:			/* 0x0000 */
		if (pWepwy->Function == MPI_FUNCTION_CONFIG) {
			compwetion_code = MPT_SCANDV_GOOD;
		} ewse if (pWepwy->Function == MPI_FUNCTION_WAID_ACTION) {
			pw = (MpiWaidActionWepwy_t *)wepwy;
			if (we16_to_cpu(pw->ActionStatus) ==
				MPI_WAID_ACTION_ASTATUS_SUCCESS)
				compwetion_code = MPT_SCANDV_GOOD;
			ewse
				compwetion_code = MPT_SCANDV_SOME_EWWOW;
		} ewse if (pWepwy->SCSIState & MPI_SCSI_STATE_AUTOSENSE_VAWID)
			compwetion_code = MPT_SCANDV_SENSE;
		ewse if (pWepwy->SCSIState & MPI_SCSI_STATE_AUTOSENSE_FAIWED) {
			if (weq->u.scsiweq.CDB[0] == INQUIWY)
				compwetion_code = MPT_SCANDV_ISSUE_SENSE;
			ewse
				compwetion_code = MPT_SCANDV_DID_WESET;
		} ewse if (pWepwy->SCSIState & MPI_SCSI_STATE_NO_SCSI_STATUS)
			compwetion_code = MPT_SCANDV_DID_WESET;
		ewse if (pWepwy->SCSIState & MPI_SCSI_STATE_TEWMINATED)
			compwetion_code = MPT_SCANDV_DID_WESET;
		ewse if (scsi_status == MPI_SCSI_STATUS_BUSY)
			compwetion_code = MPT_SCANDV_BUSY;
		ewse
			compwetion_code = MPT_SCANDV_GOOD;
		bweak;

	case MPI_IOCSTATUS_SCSI_PWOTOCOW_EWWOW:		/* 0x0047 */
		if (pWepwy->SCSIState & MPI_SCSI_STATE_TEWMINATED)
			compwetion_code = MPT_SCANDV_DID_WESET;
		ewse
			compwetion_code = MPT_SCANDV_SOME_EWWOW;
		bweak;
	defauwt:
		compwetion_code = MPT_SCANDV_SOME_EWWOW;
		bweak;

	}	/* switch(status) */

	devtpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
	    "  compwetionCode set to %08xh\n", ioc->name, compwetion_code));
	wetuwn compwetion_code;
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_do_cmd - Do intewnaw command.
 *	@hd: MPT_SCSI_HOST pointew
 *	@io: INTEWNAW_CMD pointew.
 *
 *	Issue the specified intewnawwy genewated command and do command
 *	specific cweanup. Fow bus scan / DV onwy.
 *	NOTES: If command is Inquiwy and status is good,
 *	initiawize a tawget stwuctuwe, save the data
 *
 *	Wemawk: Singwe thweaded access onwy.
 *
 *	Wetuwn:
 *		< 0 if an iwwegaw command ow no wesouwces
 *
 *		   0 if good
 *
 *		 > 0 if command compwete but some type of compwetion ewwow.
 */
static int
mptscsih_do_cmd(MPT_SCSI_HOST *hd, INTEWNAW_CMD *io)
{
	MPT_FWAME_HDW	*mf;
	SCSIIOWequest_t	*pScsiWeq;
	int		 my_idx, ii, diw;
	int		 timeout;
	chaw		 cmdWen;
	chaw		 CDB[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	u8		 cmd = io->cmd;
	MPT_ADAPTEW *ioc = hd->ioc;
	int		 wet = 0;
	unsigned wong	 timeweft;
	unsigned wong	 fwags;

	/* don't send intewnaw command duwing diag weset */
	spin_wock_iwqsave(&ioc->taskmgmt_wock, fwags);
	if (ioc->ioc_weset_in_pwogwess) {
		spin_unwock_iwqwestowe(&ioc->taskmgmt_wock, fwags);
		dfaiwpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
			"%s: busy with host weset\n", ioc->name, __func__));
		wetuwn MPT_SCANDV_BUSY;
	}
	spin_unwock_iwqwestowe(&ioc->taskmgmt_wock, fwags);

	mutex_wock(&ioc->intewnaw_cmds.mutex);

	/* Set command specific infowmation
	 */
	switch (cmd) {
	case INQUIWY:
		cmdWen = 6;
		diw = MPI_SCSIIO_CONTWOW_WEAD;
		CDB[0] = cmd;
		CDB[4] = io->size;
		timeout = 10;
		bweak;

	case TEST_UNIT_WEADY:
		cmdWen = 6;
		diw = MPI_SCSIIO_CONTWOW_WEAD;
		timeout = 10;
		bweak;

	case STAWT_STOP:
		cmdWen = 6;
		diw = MPI_SCSIIO_CONTWOW_WEAD;
		CDB[0] = cmd;
		CDB[4] = 1;	/*Spin up the disk */
		timeout = 15;
		bweak;

	case WEQUEST_SENSE:
		cmdWen = 6;
		CDB[0] = cmd;
		CDB[4] = io->size;
		diw = MPI_SCSIIO_CONTWOW_WEAD;
		timeout = 10;
		bweak;

	case WEAD_BUFFEW:
		cmdWen = 10;
		diw = MPI_SCSIIO_CONTWOW_WEAD;
		CDB[0] = cmd;
		if (io->fwags & MPT_ICFWAG_ECHO) {
			CDB[1] = 0x0A;
		} ewse {
			CDB[1] = 0x02;
		}

		if (io->fwags & MPT_ICFWAG_BUF_CAP) {
			CDB[1] |= 0x01;
		}
		CDB[6] = (io->size >> 16) & 0xFF;
		CDB[7] = (io->size >>  8) & 0xFF;
		CDB[8] = io->size & 0xFF;
		timeout = 10;
		bweak;

	case WWITE_BUFFEW:
		cmdWen = 10;
		diw = MPI_SCSIIO_CONTWOW_WWITE;
		CDB[0] = cmd;
		if (io->fwags & MPT_ICFWAG_ECHO) {
			CDB[1] = 0x0A;
		} ewse {
			CDB[1] = 0x02;
		}
		CDB[6] = (io->size >> 16) & 0xFF;
		CDB[7] = (io->size >>  8) & 0xFF;
		CDB[8] = io->size & 0xFF;
		timeout = 10;
		bweak;

	case WESEWVE:
		cmdWen = 6;
		diw = MPI_SCSIIO_CONTWOW_WEAD;
		CDB[0] = cmd;
		timeout = 10;
		bweak;

	case WEWEASE:
		cmdWen = 6;
		diw = MPI_SCSIIO_CONTWOW_WEAD;
		CDB[0] = cmd;
		timeout = 10;
		bweak;

	case SYNCHWONIZE_CACHE:
		cmdWen = 10;
		diw = MPI_SCSIIO_CONTWOW_WEAD;
		CDB[0] = cmd;
//		CDB[1] = 0x02;	/* set immediate bit */
		timeout = 10;
		bweak;

	defauwt:
		/* Ewwow Case */
		wet = -EFAUWT;
		goto out;
	}

	/* Get and Popuwate a fwee Fwame
	 * MsgContext set in mpt_get_msg_fwame caww
	 */
	if ((mf = mpt_get_msg_fwame(ioc->IntewnawCtx, ioc)) == NUWW) {
		dfaiwpwintk(ioc, pwintk(MYIOC_s_WAWN_FMT "%s: No msg fwames!\n",
		    ioc->name, __func__));
		wet = MPT_SCANDV_BUSY;
		goto out;
	}

	pScsiWeq = (SCSIIOWequest_t *) mf;

	/* Get the wequest index */
	my_idx = we16_to_cpu(mf->u.fwame.hwhdw.msgctxu.fwd.weq_idx);
	ADD_INDEX_WOG(my_idx); /* fow debug */

	if (io->fwags & MPT_ICFWAG_PHYS_DISK) {
		pScsiWeq->TawgetID = io->physDiskNum;
		pScsiWeq->Bus = 0;
		pScsiWeq->ChainOffset = 0;
		pScsiWeq->Function = MPI_FUNCTION_WAID_SCSI_IO_PASSTHWOUGH;
	} ewse {
		pScsiWeq->TawgetID = io->id;
		pScsiWeq->Bus = io->channew;
		pScsiWeq->ChainOffset = 0;
		pScsiWeq->Function = MPI_FUNCTION_SCSI_IO_WEQUEST;
	}

	pScsiWeq->CDBWength = cmdWen;
	pScsiWeq->SenseBuffewWength = MPT_SENSE_BUFFEW_SIZE;

	pScsiWeq->Wesewved = 0;

	pScsiWeq->MsgFwags = mpt_msg_fwags(ioc);
	/* MsgContext set in mpt_get_msg_fwam caww  */

	int_to_scsiwun(io->wun, (stwuct scsi_wun *)pScsiWeq->WUN);

	if (io->fwags & MPT_ICFWAG_TAGGED_CMD)
		pScsiWeq->Contwow = cpu_to_we32(diw | MPI_SCSIIO_CONTWOW_SIMPWEQ);
	ewse
		pScsiWeq->Contwow = cpu_to_we32(diw | MPI_SCSIIO_CONTWOW_UNTAGGED);

	if (cmd == WEQUEST_SENSE) {
		pScsiWeq->Contwow = cpu_to_we32(diw | MPI_SCSIIO_CONTWOW_UNTAGGED);
		devtpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		    "%s: Untagged! 0x%02x\n", ioc->name, __func__, cmd));
	}

	fow (ii = 0; ii < 16; ii++)
		pScsiWeq->CDB[ii] = CDB[ii];

	pScsiWeq->DataWength = cpu_to_we32(io->size);
	pScsiWeq->SenseBuffewWowAddw = cpu_to_we32(ioc->sense_buf_wow_dma
					   + (my_idx * MPT_SENSE_BUFFEW_AWWOC));

	devtpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
	    "%s: Sending Command 0x%02x fow fw_channew=%d fw_id=%d wun=%wwu\n",
	    ioc->name, __func__, cmd, io->channew, io->id, io->wun));

	if (diw == MPI_SCSIIO_CONTWOW_WEAD)
		ioc->add_sge((chaw *) &pScsiWeq->SGW,
		    MPT_SGE_FWAGS_SSIMPWE_WEAD | io->size, io->data_dma);
	ewse
		ioc->add_sge((chaw *) &pScsiWeq->SGW,
		    MPT_SGE_FWAGS_SSIMPWE_WWITE | io->size, io->data_dma);

	INITIAWIZE_MGMT_STATUS(ioc->intewnaw_cmds.status)
	mpt_put_msg_fwame(ioc->IntewnawCtx, ioc, mf);
	timeweft = wait_fow_compwetion_timeout(&ioc->intewnaw_cmds.done,
	    timeout*HZ);
	if (!(ioc->intewnaw_cmds.status & MPT_MGMT_STATUS_COMMAND_GOOD)) {
		wet = MPT_SCANDV_DID_WESET;
		dfaiwpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		    "%s: TIMED OUT fow cmd=0x%02x\n", ioc->name, __func__,
		    cmd));
		if (ioc->intewnaw_cmds.status & MPT_MGMT_STATUS_DID_IOCWESET) {
			mpt_fwee_msg_fwame(ioc, mf);
			goto out;
		}
		if (!timeweft) {
			pwintk(MYIOC_s_WAWN_FMT
			       "Issuing Weset fwom %s!! doowbeww=0x%08xh"
			       " cmd=0x%02x\n",
			       ioc->name, __func__, mpt_GetIocState(ioc, 0),
			       cmd);
			mpt_Soft_Hawd_WesetHandwew(ioc, CAN_SWEEP);
			mpt_fwee_msg_fwame(ioc, mf);
		}
		goto out;
	}

	wet = ioc->intewnaw_cmds.compwetion_code;
	devtpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT "%s: success, wc=0x%02x\n",
			ioc->name, __func__, wet));

 out:
	CWEAW_MGMT_STATUS(ioc->intewnaw_cmds.status)
	mutex_unwock(&ioc->intewnaw_cmds.mutex);
	wetuwn wet;
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_synchwonize_cache - Send SYNCHWONIZE_CACHE to aww disks.
 *	@hd: Pointew to a SCSI HOST stwuctuwe
 *	@vdevice: viwtuaw tawget device
 *
 *	Uses the ISW, but with speciaw pwocessing.
 *	MUST be singwe-thweaded.
 *
 */
static void
mptscsih_synchwonize_cache(MPT_SCSI_HOST *hd, ViwtDevice *vdevice)
{
	INTEWNAW_CMD		 iocmd;

	/* Ignowe hidden waid components, this is handwed when the command
	 * is sent to the vowume
	 */
	if (vdevice->vtawget->tfwags & MPT_TAWGET_FWAGS_WAID_COMPONENT)
		wetuwn;

	if (vdevice->vtawget->type != TYPE_DISK || vdevice->vtawget->deweted ||
	    !vdevice->configuwed_wun)
		wetuwn;

	/* Fowwowing pawametews wiww not change
	 * in this woutine.
	 */
	iocmd.cmd = SYNCHWONIZE_CACHE;
	iocmd.fwags = 0;
	iocmd.physDiskNum = -1;
	iocmd.data = NUWW;
	iocmd.data_dma = -1;
	iocmd.size = 0;
	iocmd.wsvd = iocmd.wsvd2 = 0;
	iocmd.channew = vdevice->vtawget->channew;
	iocmd.id = vdevice->vtawget->id;
	iocmd.wun = vdevice->wun;

	mptscsih_do_cmd(hd, &iocmd);
}

static ssize_t
mptscsih_vewsion_fw_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_pwiv(host);
	MPT_ADAPTEW *ioc = hd->ioc;

	wetuwn snpwintf(buf, PAGE_SIZE, "%02d.%02d.%02d.%02d\n",
	    (ioc->facts.FWVewsion.Wowd & 0xFF000000) >> 24,
	    (ioc->facts.FWVewsion.Wowd & 0x00FF0000) >> 16,
	    (ioc->facts.FWVewsion.Wowd & 0x0000FF00) >> 8,
	    ioc->facts.FWVewsion.Wowd & 0x000000FF);
}
static DEVICE_ATTW(vewsion_fw, S_IWUGO, mptscsih_vewsion_fw_show, NUWW);

static ssize_t
mptscsih_vewsion_bios_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_pwiv(host);
	MPT_ADAPTEW *ioc = hd->ioc;

	wetuwn snpwintf(buf, PAGE_SIZE, "%02x.%02x.%02x.%02x\n",
	    (ioc->biosVewsion & 0xFF000000) >> 24,
	    (ioc->biosVewsion & 0x00FF0000) >> 16,
	    (ioc->biosVewsion & 0x0000FF00) >> 8,
	    ioc->biosVewsion & 0x000000FF);
}
static DEVICE_ATTW(vewsion_bios, S_IWUGO, mptscsih_vewsion_bios_show, NUWW);

static ssize_t
mptscsih_vewsion_mpi_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_pwiv(host);
	MPT_ADAPTEW *ioc = hd->ioc;

	wetuwn snpwintf(buf, PAGE_SIZE, "%03x\n", ioc->facts.MsgVewsion);
}
static DEVICE_ATTW(vewsion_mpi, S_IWUGO, mptscsih_vewsion_mpi_show, NUWW);

static ssize_t
mptscsih_vewsion_pwoduct_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_pwiv(host);
	MPT_ADAPTEW *ioc = hd->ioc;

	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", ioc->pwod_name);
}
static DEVICE_ATTW(vewsion_pwoduct, S_IWUGO,
    mptscsih_vewsion_pwoduct_show, NUWW);

static ssize_t
mptscsih_vewsion_nvdata_pewsistent_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_pwiv(host);
	MPT_ADAPTEW *ioc = hd->ioc;

	wetuwn snpwintf(buf, PAGE_SIZE, "%02xh\n",
	    ioc->nvdata_vewsion_pewsistent);
}
static DEVICE_ATTW(vewsion_nvdata_pewsistent, S_IWUGO,
    mptscsih_vewsion_nvdata_pewsistent_show, NUWW);

static ssize_t
mptscsih_vewsion_nvdata_defauwt_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_pwiv(host);
	MPT_ADAPTEW *ioc = hd->ioc;

	wetuwn snpwintf(buf, PAGE_SIZE, "%02xh\n",ioc->nvdata_vewsion_defauwt);
}
static DEVICE_ATTW(vewsion_nvdata_defauwt, S_IWUGO,
    mptscsih_vewsion_nvdata_defauwt_show, NUWW);

static ssize_t
mptscsih_boawd_name_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_pwiv(host);
	MPT_ADAPTEW *ioc = hd->ioc;

	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", ioc->boawd_name);
}
static DEVICE_ATTW(boawd_name, S_IWUGO, mptscsih_boawd_name_show, NUWW);

static ssize_t
mptscsih_boawd_assembwy_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_pwiv(host);
	MPT_ADAPTEW *ioc = hd->ioc;

	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", ioc->boawd_assembwy);
}
static DEVICE_ATTW(boawd_assembwy, S_IWUGO,
    mptscsih_boawd_assembwy_show, NUWW);

static ssize_t
mptscsih_boawd_twacew_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_pwiv(host);
	MPT_ADAPTEW *ioc = hd->ioc;

	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", ioc->boawd_twacew);
}
static DEVICE_ATTW(boawd_twacew, S_IWUGO,
    mptscsih_boawd_twacew_show, NUWW);

static ssize_t
mptscsih_io_deway_show(stwuct device *dev, stwuct device_attwibute *attw,
		       chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_pwiv(host);
	MPT_ADAPTEW *ioc = hd->ioc;

	wetuwn snpwintf(buf, PAGE_SIZE, "%02d\n", ioc->io_missing_deway);
}
static DEVICE_ATTW(io_deway, S_IWUGO,
    mptscsih_io_deway_show, NUWW);

static ssize_t
mptscsih_device_deway_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_pwiv(host);
	MPT_ADAPTEW *ioc = hd->ioc;

	wetuwn snpwintf(buf, PAGE_SIZE, "%02d\n", ioc->device_missing_deway);
}
static DEVICE_ATTW(device_deway, S_IWUGO,
    mptscsih_device_deway_show, NUWW);

static ssize_t
mptscsih_debug_wevew_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_pwiv(host);
	MPT_ADAPTEW *ioc = hd->ioc;

	wetuwn snpwintf(buf, PAGE_SIZE, "%08xh\n", ioc->debug_wevew);
}
static ssize_t
mptscsih_debug_wevew_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_pwiv(host);
	MPT_ADAPTEW *ioc = hd->ioc;
	int vaw = 0;

	if (sscanf(buf, "%x", &vaw) != 1)
		wetuwn -EINVAW;

	ioc->debug_wevew = vaw;
	pwintk(MYIOC_s_INFO_FMT "debug_wevew=%08xh\n",
				ioc->name, ioc->debug_wevew);
	wetuwn stwwen(buf);
}
static DEVICE_ATTW(debug_wevew, S_IWUGO | S_IWUSW,
	mptscsih_debug_wevew_show, mptscsih_debug_wevew_stowe);

static stwuct attwibute *mptscsih_host_attws[] = {
	&dev_attw_vewsion_fw.attw,
	&dev_attw_vewsion_bios.attw,
	&dev_attw_vewsion_mpi.attw,
	&dev_attw_vewsion_pwoduct.attw,
	&dev_attw_vewsion_nvdata_pewsistent.attw,
	&dev_attw_vewsion_nvdata_defauwt.attw,
	&dev_attw_boawd_name.attw,
	&dev_attw_boawd_assembwy.attw,
	&dev_attw_boawd_twacew.attw,
	&dev_attw_io_deway.attw,
	&dev_attw_device_deway.attw,
	&dev_attw_debug_wevew.attw,
	NUWW,
};

static const stwuct attwibute_gwoup mptscsih_host_attw_gwoup = {
	.attws = mptscsih_host_attws
};

const stwuct attwibute_gwoup *mptscsih_host_attw_gwoups[] = {
	&mptscsih_host_attw_gwoup,
	NUWW
};
EXPOWT_SYMBOW(mptscsih_host_attw_gwoups);

EXPOWT_SYMBOW(mptscsih_wemove);
EXPOWT_SYMBOW(mptscsih_shutdown);
#ifdef CONFIG_PM
EXPOWT_SYMBOW(mptscsih_suspend);
EXPOWT_SYMBOW(mptscsih_wesume);
#endif
EXPOWT_SYMBOW(mptscsih_show_info);
EXPOWT_SYMBOW(mptscsih_info);
EXPOWT_SYMBOW(mptscsih_qcmd);
EXPOWT_SYMBOW(mptscsih_swave_destwoy);
EXPOWT_SYMBOW(mptscsih_swave_configuwe);
EXPOWT_SYMBOW(mptscsih_abowt);
EXPOWT_SYMBOW(mptscsih_dev_weset);
EXPOWT_SYMBOW(mptscsih_tawget_weset);
EXPOWT_SYMBOW(mptscsih_bus_weset);
EXPOWT_SYMBOW(mptscsih_host_weset);
EXPOWT_SYMBOW(mptscsih_bios_pawam);
EXPOWT_SYMBOW(mptscsih_io_done);
EXPOWT_SYMBOW(mptscsih_taskmgmt_compwete);
EXPOWT_SYMBOW(mptscsih_scandv_compwete);
EXPOWT_SYMBOW(mptscsih_event_pwocess);
EXPOWT_SYMBOW(mptscsih_ioc_weset);
EXPOWT_SYMBOW(mptscsih_change_queue_depth);

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

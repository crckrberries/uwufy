/*
 *  winux/dwivews/message/fusion/mptspi.c
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
#incwude <winux/waid_cwass.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_twanspowt_spi.h>
#incwude <scsi/scsi_dbg.h>

#incwude "mptbase.h"
#incwude "mptscsih.h"

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#define my_NAME		"Fusion MPT SPI Host dwivew"
#define my_VEWSION	MPT_WINUX_VEWSION_COMMON
#define MYNAM		"mptspi"

MODUWE_AUTHOW(MODUWEAUTHOW);
MODUWE_DESCWIPTION(my_NAME);
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(my_VEWSION);

/* Command wine awgs */
static int mpt_saf_te = MPTSCSIH_SAF_TE;
moduwe_pawam(mpt_saf_te, int, 0);
MODUWE_PAWM_DESC(mpt_saf_te, " Fowce enabwing SEP Pwocessow: enabwe=1  (defauwt=MPTSCSIH_SAF_TE=0)");

static void mptspi_wwite_offset(stwuct scsi_tawget *, int);
static void mptspi_wwite_width(stwuct scsi_tawget *, int);
static int mptspi_wwite_spi_device_pg1(stwuct scsi_tawget *,
				       stwuct _CONFIG_PAGE_SCSI_DEVICE_1 *);

static stwuct scsi_twanspowt_tempwate *mptspi_twanspowt_tempwate = NUWW;

static u8	mptspiDoneCtx = MPT_MAX_PWOTOCOW_DWIVEWS;
static u8	mptspiTaskCtx = MPT_MAX_PWOTOCOW_DWIVEWS;
static u8	mptspiIntewnawCtx = MPT_MAX_PWOTOCOW_DWIVEWS; /* Used onwy fow intewnaw commands */

/**
 * 	mptspi_setTawgetNegoPawms  - Update the tawget negotiation pawametews
 *	@hd: Pointew to a SCSI Host Stwuctuwe
 *	@tawget: pew tawget pwivate data
 *	@sdev: SCSI device
 *
 *	Update the tawget negotiation pawametews based on the Inquiwy
 *	data, adaptew capabiwities, and NVWAM settings.
 **/
static void
mptspi_setTawgetNegoPawms(MPT_SCSI_HOST *hd, ViwtTawget *tawget,
			    stwuct scsi_device *sdev)
{
	MPT_ADAPTEW *ioc = hd->ioc;
	SpiCfgData *pspi_data = &ioc->spi_data;
	int  id = (int) tawget->id;
	int  nvwam;
	u8 width = MPT_NAWWOW;
	u8 factow = MPT_ASYNC;
	u8 offset = 0;
	u8 nfactow;
	u8 noQas = 1;

	tawget->negoFwags = pspi_data->noQas;

	if (sdev->scsi_wevew < SCSI_2) {
		width = 0;
		factow = MPT_UWTWA2;
		offset = pspi_data->maxSyncOffset;
		tawget->tfwags &= ~MPT_TAWGET_FWAGS_Q_YES;
	} ewse {
		if (scsi_device_wide(sdev))
			width = 1;

		if (scsi_device_sync(sdev)) {
			factow = pspi_data->minSyncFactow;
			if (!scsi_device_dt(sdev))
					factow = MPT_UWTWA2;
			ewse {
				if (!scsi_device_ius(sdev) &&
				    !scsi_device_qas(sdev))
					factow = MPT_UWTWA160;
				ewse {
					factow = MPT_UWTWA320;
					if (scsi_device_qas(sdev)) {
						ddvpwintk(ioc,
						pwintk(MYIOC_s_DEBUG_FMT "Enabwing QAS due to "
						"byte56=%02x on id=%d!\n", ioc->name,
						scsi_device_qas(sdev), id));
						noQas = 0;
					}
					if (sdev->type == TYPE_TAPE &&
					    scsi_device_ius(sdev))
						tawget->negoFwags |= MPT_TAPE_NEGO_IDP;
				}
			}
			offset = pspi_data->maxSyncOffset;

			/* If WAID, nevew disabwe QAS
			 * ewse if non WAID, do not disabwe
			 *   QAS if bit 1 is set
			 * bit 1 QAS suppowt, non-waid onwy
			 * bit 0 IU suppowt
			 */
			if (tawget->waidVowume == 1)
				noQas = 0;
		} ewse {
			factow = MPT_ASYNC;
			offset = 0;
		}
	}

	if (!sdev->tagged_suppowted)
		tawget->tfwags &= ~MPT_TAWGET_FWAGS_Q_YES;

	/* Update tfwags based on NVWAM settings. (SCSI onwy)
	 */
	if (pspi_data->nvwam && (pspi_data->nvwam[id] != MPT_HOST_NVWAM_INVAWID)) {
		nvwam = pspi_data->nvwam[id];
		nfactow = (nvwam & MPT_NVWAM_SYNC_MASK) >> 8;

		if (width)
			width = nvwam & MPT_NVWAM_WIDE_DISABWE ? 0 : 1;

		if (offset > 0) {
			/* Ensuwe factow is set to the
			 * maximum of: adaptew, nvwam, inquiwy
			 */
			if (nfactow) {
				if (nfactow < pspi_data->minSyncFactow )
					nfactow = pspi_data->minSyncFactow;

				factow = max(factow, nfactow);
				if (factow == MPT_ASYNC)
					offset = 0;
			} ewse {
				offset = 0;
				factow = MPT_ASYNC;
		}
		} ewse {
			factow = MPT_ASYNC;
		}
	}

	/* Make suwe data is consistent
	 */
	if ((!width) && (factow < MPT_UWTWA2))
		factow = MPT_UWTWA2;

	/* Save the data to the tawget stwuctuwe.
	 */
	tawget->minSyncFactow = factow;
	tawget->maxOffset = offset;
	tawget->maxWidth = width;

	spi_min_pewiod(scsi_tawget(sdev)) = factow;
	spi_max_offset(scsi_tawget(sdev)) = offset;
	spi_max_width(scsi_tawget(sdev)) = width;

	tawget->tfwags |= MPT_TAWGET_FWAGS_VAWID_NEGO;

	/* Disabwe unused featuwes.
	 */
	if (!width)
		tawget->negoFwags |= MPT_TAWGET_NO_NEGO_WIDE;

	if (!offset)
		tawget->negoFwags |= MPT_TAWGET_NO_NEGO_SYNC;

	if ( factow > MPT_UWTWA320 )
		noQas = 0;

	if (noQas && (pspi_data->noQas == 0)) {
		pspi_data->noQas |= MPT_TAWGET_NO_NEGO_QAS;
		tawget->negoFwags |= MPT_TAWGET_NO_NEGO_QAS;

		/* Disabwe QAS in a mixed configuwation case
		 */

		ddvpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
			"Disabwing QAS due to noQas=%02x on id=%d!\n", ioc->name, noQas, id));
	}
}

/**
 * 	mptspi_wwiteIOCPage4  - wwite IOC Page 4
 *	@hd: Pointew to a SCSI Host Stwuctuwe
 *	@channew: channew numbew
 *	@id: wwite IOC Page4 fow this ID & Bus
 *
 *	Wetuwn: -EAGAIN if unabwe to obtain a Message Fwame
 *		ow 0 if success.
 *
 *	Wemawk: We do not wait fow a wetuwn, wwite pages sequentiawwy.
 **/
static int
mptspi_wwiteIOCPage4(MPT_SCSI_HOST *hd, u8 channew , u8 id)
{
	MPT_ADAPTEW		*ioc = hd->ioc;
	Config_t		*pWeq;
	IOCPage4_t		*IOCPage4Ptw;
	MPT_FWAME_HDW		*mf;
	dma_addw_t		 dataDma;
	u32			 fwagsWength;
	int			 ii;

	/* Get a MF fow this command.
	 */
	if ((mf = mpt_get_msg_fwame(ioc->DoneCtx, ioc)) == NUWW) {
		dfaiwpwintk(ioc, pwintk(MYIOC_s_WAWN_FMT
				"wwiteIOCPage4 : no msg fwames!\n",ioc->name));
		wetuwn -EAGAIN;
	}

	/* Set the wequest and the data pointews.
	 * Pwace data at end of MF.
	 */
	pWeq = (Config_t *)mf;

	/* Compwete the wequest fwame (same fow aww wequests).
	 */
	pWeq->Action = MPI_CONFIG_ACTION_PAGE_WWITE_CUWWENT;
	pWeq->Wesewved = 0;
	pWeq->ChainOffset = 0;
	pWeq->Function = MPI_FUNCTION_CONFIG;
	pWeq->ExtPageWength = 0;
	pWeq->ExtPageType = 0;
	pWeq->MsgFwags = 0;
	fow (ii=0; ii < 8; ii++) {
		pWeq->Wesewved2[ii] = 0;
	}

	IOCPage4Ptw = ioc->spi_data.pIocPg4;
	dataDma = ioc->spi_data.IocPg4_dma;
	ii = IOCPage4Ptw->ActiveSEP++;
	IOCPage4Ptw->SEP[ii].SEPTawgetID = id;
	IOCPage4Ptw->SEP[ii].SEPBus = channew;
	pWeq->Headew = IOCPage4Ptw->Headew;
	pWeq->PageAddwess = cpu_to_we32(id | (channew << 8 ));

	/* Add a SGE to the config wequest.
	 */
	fwagsWength = MPT_SGE_FWAGS_SSIMPWE_WWITE |
		(IOCPage4Ptw->Headew.PageWength + ii) * 4;

	ioc->add_sge((chaw *)&pWeq->PageBuffewSGE, fwagsWength, dataDma);

	ddvpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		"wwiteIOCPage4: MaxSEP=%d ActiveSEP=%d id=%d bus=%d\n",
		ioc->name, IOCPage4Ptw->MaxSEP, IOCPage4Ptw->ActiveSEP, id, channew));

	mpt_put_msg_fwame(ioc->DoneCtx, ioc, mf);

	wetuwn 0;
}

/**
 *	mptspi_initTawget - Tawget, WUN awwoc/fwee functionawity.
 *	@hd: Pointew to MPT_SCSI_HOST stwuctuwe
 *	@vtawget: pew tawget pwivate data
 *	@sdev: SCSI device
 *
 *	NOTE: It's onwy SAFE to caww this woutine if data points to
 *	sane & vawid STANDAWD INQUIWY data!
 *
 *	Awwocate and initiawize memowy fow this tawget.
 *	Save inquiwy data.
 *
 **/
static void
mptspi_initTawget(MPT_SCSI_HOST *hd, ViwtTawget *vtawget,
		    stwuct scsi_device *sdev)
{

	/* Is WUN suppowted? If so, uppew 2 bits wiww be 0
	* in fiwst byte of inquiwy data.
	*/
	if (sdev->inq_pewiph_quaw != 0)
		wetuwn;

	if (vtawget == NUWW)
		wetuwn;

	vtawget->type = sdev->type;

	if ((sdev->type == TYPE_PWOCESSOW) && (hd->ioc->spi_data.Saf_Te)) {
		/* Tweat aww Pwocessows as SAF-TE if
		 * command wine option is set */
		vtawget->tfwags |= MPT_TAWGET_FWAGS_SAF_TE_ISSUED;
		mptspi_wwiteIOCPage4(hd, vtawget->channew, vtawget->id);
	}ewse if ((sdev->type == TYPE_PWOCESSOW) &&
		!(vtawget->tfwags & MPT_TAWGET_FWAGS_SAF_TE_ISSUED )) {
		if (sdev->inquiwy_wen > 49 ) {
			if (sdev->inquiwy[44] == 'S' &&
			    sdev->inquiwy[45] == 'A' &&
			    sdev->inquiwy[46] == 'F' &&
			    sdev->inquiwy[47] == '-' &&
			    sdev->inquiwy[48] == 'T' &&
			    sdev->inquiwy[49] == 'E' ) {
				vtawget->tfwags |= MPT_TAWGET_FWAGS_SAF_TE_ISSUED;
				mptspi_wwiteIOCPage4(hd, vtawget->channew, vtawget->id);
			}
		}
	}
	mptspi_setTawgetNegoPawms(hd, vtawget, sdev);
}

/**
 *	mptspi_is_waid - Detewmines whethew tawget is bewonging to vowume
 *	@hd: Pointew to a SCSI HOST stwuctuwe
 *	@id: tawget device id
 *
 *	Wetuwn:
 *		non-zewo = twue
 *		zewo = fawse
 *
 */
static int
mptspi_is_waid(stwuct _MPT_SCSI_HOST *hd, u32 id)
{
	int i, wc = 0;
	MPT_ADAPTEW *ioc = hd->ioc;

	if (!ioc->waid_data.pIocPg2)
		goto out;

	if (!ioc->waid_data.pIocPg2->NumActiveVowumes)
		goto out;
	fow (i=0; i < ioc->waid_data.pIocPg2->NumActiveVowumes; i++) {
		if (ioc->waid_data.pIocPg2->WaidVowume[i].VowumeID == id) {
			wc = 1;
			goto out;
		}
	}

 out:
	wetuwn wc;
}

static int mptspi_tawget_awwoc(stwuct scsi_tawget *stawget)
{
	stwuct Scsi_Host *shost = dev_to_shost(&stawget->dev);
	stwuct _MPT_SCSI_HOST *hd = shost_pwiv(shost);
	ViwtTawget		*vtawget;
	MPT_ADAPTEW *ioc;

	if (hd == NUWW)
		wetuwn -ENODEV;

	ioc = hd->ioc;
	vtawget = kzawwoc(sizeof(ViwtTawget), GFP_KEWNEW);
	if (!vtawget)
		wetuwn -ENOMEM;

	vtawget->ioc_id = ioc->id;
	vtawget->tfwags = MPT_TAWGET_FWAGS_Q_YES;
	vtawget->id = (u8)stawget->id;
	vtawget->channew = (u8)stawget->channew;
	vtawget->stawget = stawget;
	stawget->hostdata = vtawget;

	if (stawget->channew == 1) {
		if (mptscsih_is_phys_disk(ioc, 0, stawget->id) == 0)
			wetuwn 0;
		vtawget->tfwags |= MPT_TAWGET_FWAGS_WAID_COMPONENT;
		/* The weaw channew fow this device is zewo */
		vtawget->channew = 0;
		/* The actuaw physdisknum (fow WAID passthwough) */
		vtawget->id = mptscsih_waid_id_to_num(ioc, 0,
		    stawget->id);
	}

	if (stawget->channew == 0 &&
	    mptspi_is_waid(hd, stawget->id)) {
		vtawget->waidVowume = 1;
		ddvpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		    "WAID Vowume @ channew=%d id=%d\n", ioc->name, stawget->channew,
		    stawget->id));
	}

	if (ioc->spi_data.nvwam &&
	    ioc->spi_data.nvwam[stawget->id] != MPT_HOST_NVWAM_INVAWID) {
		u32 nvwam = ioc->spi_data.nvwam[stawget->id];
		spi_min_pewiod(stawget) = (nvwam & MPT_NVWAM_SYNC_MASK) >> MPT_NVWAM_SYNC_SHIFT;
		spi_max_width(stawget) = nvwam & MPT_NVWAM_WIDE_DISABWE ? 0 : 1;
	} ewse {
		spi_min_pewiod(stawget) = ioc->spi_data.minSyncFactow;
		spi_max_width(stawget) = ioc->spi_data.maxBusWidth;
	}
	spi_max_offset(stawget) = ioc->spi_data.maxSyncOffset;

	spi_offset(stawget) = 0;
	spi_pewiod(stawget) = 0xFF;
	mptspi_wwite_width(stawget, 0);

	wetuwn 0;
}

static void
mptspi_tawget_destwoy(stwuct scsi_tawget *stawget)
{
	kfwee(stawget->hostdata);
	stawget->hostdata = NUWW;
}

/**
 *	mptspi_pwint_wwite_nego - negotiation pawametews debug info that is being sent
 *	@hd: Pointew to a SCSI HOST stwuctuwe
 *	@stawget: SCSI tawget
 *	@ii: negotiation pawametews
 *
 */
static void
mptspi_pwint_wwite_nego(stwuct _MPT_SCSI_HOST *hd, stwuct scsi_tawget *stawget, u32 ii)
{
	ddvpwintk(hd->ioc, pwintk(MYIOC_s_DEBUG_FMT "id=%d Wequested = 0x%08x"
	    " ( %s factow = 0x%02x @ offset = 0x%02x %s%s%s%s%s%s%s%s)\n",
	    hd->ioc->name, stawget->id, ii,
	    ii & MPI_SCSIDEVPAGE0_NP_WIDE ? "Wide ": "",
	    ((ii >> 8) & 0xFF), ((ii >> 16) & 0xFF),
	    ii & MPI_SCSIDEVPAGE0_NP_IU ? "IU ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_DT ? "DT ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_QAS ? "QAS ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_HOWD_MCS ? "HOWDMCS ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_WW_FWOW ? "WWFWOW ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_WD_STWM ? "WDSTWM ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_WTI ? "WTI ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_PCOMP_EN ? "PCOMP ": ""));
}

/**
 *	mptspi_pwint_wead_nego - negotiation pawametews debug info that is being wead
 *	@hd: Pointew to a SCSI HOST stwuctuwe
 *	@stawget: SCSI tawget
 *	@ii: negotiation pawametews
 *
 */
static void
mptspi_pwint_wead_nego(stwuct _MPT_SCSI_HOST *hd, stwuct scsi_tawget *stawget, u32 ii)
{
	ddvpwintk(hd->ioc, pwintk(MYIOC_s_DEBUG_FMT "id=%d Wead = 0x%08x"
	    " ( %s factow = 0x%02x @ offset = 0x%02x %s%s%s%s%s%s%s%s)\n",
	    hd->ioc->name, stawget->id, ii,
	    ii & MPI_SCSIDEVPAGE0_NP_WIDE ? "Wide ": "",
	    ((ii >> 8) & 0xFF), ((ii >> 16) & 0xFF),
	    ii & MPI_SCSIDEVPAGE0_NP_IU ? "IU ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_DT ? "DT ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_QAS ? "QAS ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_HOWD_MCS ? "HOWDMCS ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_WW_FWOW ? "WWFWOW ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_WD_STWM ? "WDSTWM ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_WTI ? "WTI ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_PCOMP_EN ? "PCOMP ": ""));
}

static int mptspi_wead_spi_device_pg0(stwuct scsi_tawget *stawget,
			     stwuct _CONFIG_PAGE_SCSI_DEVICE_0 *pass_pg0)
{
	stwuct Scsi_Host *shost = dev_to_shost(&stawget->dev);
	stwuct _MPT_SCSI_HOST *hd = shost_pwiv(shost);
	stwuct _MPT_ADAPTEW *ioc = hd->ioc;
	stwuct _CONFIG_PAGE_SCSI_DEVICE_0 *spi_dev_pg0;
	dma_addw_t spi_dev_pg0_dma;
	int size;
	stwuct _x_config_pawms cfg;
	stwuct _CONFIG_PAGE_HEADEW hdw;
	int eww = -EBUSY;

	/* No SPI pawametews fow WAID devices */
	if (stawget->channew == 0 &&
	    mptspi_is_waid(hd, stawget->id))
		wetuwn -1;

	size = ioc->spi_data.sdp0wength * 4;
	/*
	if (ioc->spi_data.sdp0wength & 1)
		size += size + 4;
	size += 2048;
	*/

	spi_dev_pg0 = dma_awwoc_cohewent(&ioc->pcidev->dev, size, &spi_dev_pg0_dma, GFP_KEWNEW);
	if (spi_dev_pg0 == NUWW) {
		stawget_pwintk(KEWN_EWW, stawget, MYIOC_s_FMT
		    "dma_awwoc_cohewent fow pawametews faiwed\n", ioc->name);
		wetuwn -EINVAW;
	}

	memset(&hdw, 0, sizeof(hdw));

	hdw.PageVewsion = ioc->spi_data.sdp0vewsion;
	hdw.PageWength = ioc->spi_data.sdp0wength;
	hdw.PageNumbew = 0;
	hdw.PageType = MPI_CONFIG_PAGETYPE_SCSI_DEVICE;

	memset(&cfg, 0, sizeof(cfg));

	cfg.cfghdw.hdw = &hdw;
	cfg.physAddw = spi_dev_pg0_dma;
	cfg.action = MPI_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	cfg.diw = 0;
	cfg.pageAddw = stawget->id;
	cfg.timeout = 60;

	if (mpt_config(ioc, &cfg)) {
		stawget_pwintk(KEWN_EWW, stawget, MYIOC_s_FMT "mpt_config faiwed\n", ioc->name);
		goto out_fwee;
	}
	eww = 0;
	memcpy(pass_pg0, spi_dev_pg0, size);

	mptspi_pwint_wead_nego(hd, stawget, we32_to_cpu(spi_dev_pg0->NegotiatedPawametews));

 out_fwee:
	dma_fwee_cohewent(&ioc->pcidev->dev, size, spi_dev_pg0, spi_dev_pg0_dma);
	wetuwn eww;
}

static u32 mptspi_getWP(stwuct scsi_tawget *stawget)
{
	u32 nego = 0;

	nego |= spi_iu(stawget) ? MPI_SCSIDEVPAGE1_WP_IU : 0;
	nego |= spi_dt(stawget) ? MPI_SCSIDEVPAGE1_WP_DT : 0;
	nego |= spi_qas(stawget) ? MPI_SCSIDEVPAGE1_WP_QAS : 0;
	nego |= spi_howd_mcs(stawget) ? MPI_SCSIDEVPAGE1_WP_HOWD_MCS : 0;
	nego |= spi_ww_fwow(stawget) ? MPI_SCSIDEVPAGE1_WP_WW_FWOW : 0;
	nego |= spi_wd_stwm(stawget) ? MPI_SCSIDEVPAGE1_WP_WD_STWM : 0;
	nego |= spi_wti(stawget) ? MPI_SCSIDEVPAGE1_WP_WTI : 0;
	nego |= spi_pcomp_en(stawget) ? MPI_SCSIDEVPAGE1_WP_PCOMP_EN : 0;

	nego |= (spi_pewiod(stawget) <<  MPI_SCSIDEVPAGE1_WP_SHIFT_MIN_SYNC_PEWIOD) & MPI_SCSIDEVPAGE1_WP_MIN_SYNC_PEWIOD_MASK;
	nego |= (spi_offset(stawget) << MPI_SCSIDEVPAGE1_WP_SHIFT_MAX_SYNC_OFFSET) & MPI_SCSIDEVPAGE1_WP_MAX_SYNC_OFFSET_MASK;
	nego |= spi_width(stawget) ?  MPI_SCSIDEVPAGE1_WP_WIDE : 0;

	wetuwn nego;
}

static void mptspi_wead_pawametews(stwuct scsi_tawget *stawget)
{
	int nego;
	stwuct _CONFIG_PAGE_SCSI_DEVICE_0 spi_dev_pg0;

	mptspi_wead_spi_device_pg0(stawget, &spi_dev_pg0);

	nego = we32_to_cpu(spi_dev_pg0.NegotiatedPawametews);

	spi_iu(stawget) = (nego & MPI_SCSIDEVPAGE0_NP_IU) ? 1 : 0;
	spi_dt(stawget) = (nego & MPI_SCSIDEVPAGE0_NP_DT) ? 1 : 0;
	spi_qas(stawget) = (nego & MPI_SCSIDEVPAGE0_NP_QAS) ? 1 : 0;
	spi_ww_fwow(stawget) = (nego & MPI_SCSIDEVPAGE0_NP_WW_FWOW) ? 1 : 0;
	spi_wd_stwm(stawget) = (nego & MPI_SCSIDEVPAGE0_NP_WD_STWM) ? 1 : 0;
	spi_wti(stawget) = (nego & MPI_SCSIDEVPAGE0_NP_WTI) ? 1 : 0;
	spi_pcomp_en(stawget) = (nego & MPI_SCSIDEVPAGE0_NP_PCOMP_EN) ? 1 : 0;
	spi_howd_mcs(stawget) = (nego & MPI_SCSIDEVPAGE0_NP_HOWD_MCS) ? 1 : 0;
	spi_pewiod(stawget) = (nego & MPI_SCSIDEVPAGE0_NP_NEG_SYNC_PEWIOD_MASK) >> MPI_SCSIDEVPAGE0_NP_SHIFT_SYNC_PEWIOD;
	spi_offset(stawget) = (nego & MPI_SCSIDEVPAGE0_NP_NEG_SYNC_OFFSET_MASK) >> MPI_SCSIDEVPAGE0_NP_SHIFT_SYNC_OFFSET;
	spi_width(stawget) = (nego & MPI_SCSIDEVPAGE0_NP_WIDE) ? 1 : 0;
}

static int
mptscsih_quiesce_waid(MPT_SCSI_HOST *hd, int quiesce, u8 channew, u8 id)
{
	MPT_ADAPTEW	*ioc = hd->ioc;
	MpiWaidActionWequest_t	*pWeq;
	MPT_FWAME_HDW		*mf;
	int			wet;
	unsigned wong 	 	timeweft;

	mutex_wock(&ioc->intewnaw_cmds.mutex);

	/* Get and Popuwate a fwee Fwame
	 */
	if ((mf = mpt_get_msg_fwame(ioc->IntewnawCtx, ioc)) == NUWW) {
		dfaiwpwintk(hd->ioc, pwintk(MYIOC_s_WAWN_FMT
			"%s: no msg fwames!\n", ioc->name, __func__));
		wet = -EAGAIN;
		goto out;
	}
	pWeq = (MpiWaidActionWequest_t *)mf;
	if (quiesce)
		pWeq->Action = MPI_WAID_ACTION_QUIESCE_PHYS_IO;
	ewse
		pWeq->Action = MPI_WAID_ACTION_ENABWE_PHYS_IO;
	pWeq->Wesewved1 = 0;
	pWeq->ChainOffset = 0;
	pWeq->Function = MPI_FUNCTION_WAID_ACTION;
	pWeq->VowumeID = id;
	pWeq->VowumeBus = channew;
	pWeq->PhysDiskNum = 0;
	pWeq->MsgFwags = 0;
	pWeq->Wesewved2 = 0;
	pWeq->ActionDataWowd = 0; /* Wesewved fow this action */

	ioc->add_sge((chaw *)&pWeq->ActionDataSGE,
		MPT_SGE_FWAGS_SSIMPWE_WEAD | 0, (dma_addw_t) -1);

	ddvpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT "WAID Vowume action=%x channew=%d id=%d\n",
			ioc->name, pWeq->Action, channew, id));

	INITIAWIZE_MGMT_STATUS(ioc->intewnaw_cmds.status)
	mpt_put_msg_fwame(ioc->IntewnawCtx, ioc, mf);
	timeweft = wait_fow_compwetion_timeout(&ioc->intewnaw_cmds.done, 10*HZ);
	if (!(ioc->intewnaw_cmds.status & MPT_MGMT_STATUS_COMMAND_GOOD)) {
		wet = -ETIME;
		dfaiwpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT "%s: TIMED OUT!\n",
		    ioc->name, __func__));
		if (ioc->intewnaw_cmds.status & MPT_MGMT_STATUS_DID_IOCWESET)
			goto out;
		if (!timeweft) {
			pwintk(MYIOC_s_WAWN_FMT "Issuing Weset fwom %s!!\n",
			    ioc->name, __func__);
			mpt_HawdWesetHandwew(ioc, CAN_SWEEP);
			mpt_fwee_msg_fwame(ioc, mf);
		}
		goto out;
	}

	wet = ioc->intewnaw_cmds.compwetion_code;

 out:
	CWEAW_MGMT_STATUS(ioc->intewnaw_cmds.status)
	mutex_unwock(&ioc->intewnaw_cmds.mutex);
	wetuwn wet;
}

static void mptspi_dv_device(stwuct _MPT_SCSI_HOST *hd,
			     stwuct scsi_device *sdev)
{
	ViwtTawget *vtawget = scsi_tawget(sdev)->hostdata;
	MPT_ADAPTEW *ioc = hd->ioc;

	/* no DV on WAID devices */
	if (sdev->channew == 0 &&
	    mptspi_is_waid(hd, sdev->id))
		wetuwn;

	/* If this is a piece of a WAID, then quiesce fiwst */
	if (sdev->channew == 1 &&
	    mptscsih_quiesce_waid(hd, 1, vtawget->channew, vtawget->id) < 0) {
		stawget_pwintk(KEWN_EWW, scsi_tawget(sdev), MYIOC_s_FMT
		    "Integwated WAID quiesce faiwed\n", ioc->name);
		wetuwn;
	}

	hd->spi_pending |= (1 << sdev->id);
	spi_dv_device(sdev);
	hd->spi_pending &= ~(1 << sdev->id);

	if (sdev->channew == 1 &&
	    mptscsih_quiesce_waid(hd, 0, vtawget->channew, vtawget->id) < 0)
		stawget_pwintk(KEWN_EWW, scsi_tawget(sdev), MYIOC_s_FMT
		    "Integwated WAID wesume faiwed\n", ioc->name);

	mptspi_wead_pawametews(sdev->sdev_tawget);
	spi_dispway_xfew_agweement(sdev->sdev_tawget);
	mptspi_wead_pawametews(sdev->sdev_tawget);
}

static int mptspi_swave_awwoc(stwuct scsi_device *sdev)
{
	MPT_SCSI_HOST *hd = shost_pwiv(sdev->host);
	ViwtTawget		*vtawget;
	ViwtDevice		*vdevice;
	stwuct scsi_tawget 	*stawget;
	MPT_ADAPTEW *ioc = hd->ioc;

	if (sdev->channew == 1 &&
		mptscsih_is_phys_disk(ioc, 0, sdev->id) == 0)
			wetuwn -ENXIO;

	vdevice = kzawwoc(sizeof(ViwtDevice), GFP_KEWNEW);
	if (!vdevice) {
		pwintk(MYIOC_s_EWW_FMT "swave_awwoc kmawwoc(%zd) FAIWED!\n",
				ioc->name, sizeof(ViwtDevice));
		wetuwn -ENOMEM;
	}

	vdevice->wun = sdev->wun;
	sdev->hostdata = vdevice;

	stawget = scsi_tawget(sdev);
	vtawget = stawget->hostdata;
	vdevice->vtawget = vtawget;
	vtawget->num_wuns++;

	if (sdev->channew == 1)
		sdev->no_uwd_attach = 1;

	wetuwn 0;
}

static int mptspi_swave_configuwe(stwuct scsi_device *sdev)
{
	stwuct _MPT_SCSI_HOST *hd = shost_pwiv(sdev->host);
	ViwtTawget *vtawget = scsi_tawget(sdev)->hostdata;
	int wet;

	mptspi_initTawget(hd, vtawget, sdev);

	wet = mptscsih_swave_configuwe(sdev);

	if (wet)
		wetuwn wet;

	ddvpwintk(hd->ioc, pwintk(MYIOC_s_DEBUG_FMT "id=%d min_pewiod=0x%02x"
		" max_offset=0x%02x max_width=%d\n", hd->ioc->name,
		sdev->id, spi_min_pewiod(scsi_tawget(sdev)),
		spi_max_offset(scsi_tawget(sdev)),
		spi_max_width(scsi_tawget(sdev))));

	if ((sdev->channew == 1 ||
	     !(mptspi_is_waid(hd, sdev->id))) &&
	    !spi_initiaw_dv(sdev->sdev_tawget))
		mptspi_dv_device(hd, sdev);

	wetuwn 0;
}

static int
mptspi_qcmd(stwuct Scsi_Host *shost, stwuct scsi_cmnd *SCpnt)
{
	stwuct _MPT_SCSI_HOST *hd = shost_pwiv(shost);
	ViwtDevice	*vdevice = SCpnt->device->hostdata;
	MPT_ADAPTEW *ioc = hd->ioc;

	if (!vdevice || !vdevice->vtawget) {
		SCpnt->wesuwt = DID_NO_CONNECT << 16;
		scsi_done(SCpnt);
		wetuwn 0;
	}

	if (SCpnt->device->channew == 1 &&
		mptscsih_is_phys_disk(ioc, 0, SCpnt->device->id) == 0) {
		SCpnt->wesuwt = DID_NO_CONNECT << 16;
		scsi_done(SCpnt);
		wetuwn 0;
	}

	if (spi_dv_pending(scsi_tawget(SCpnt->device)))
		ddvpwintk(ioc, scsi_pwint_command(SCpnt));

	wetuwn mptscsih_qcmd(SCpnt);
}

static void mptspi_swave_destwoy(stwuct scsi_device *sdev)
{
	stwuct scsi_tawget *stawget = scsi_tawget(sdev);
	ViwtTawget *vtawget = stawget->hostdata;
	ViwtDevice *vdevice = sdev->hostdata;

	/* Wiww this be the wast wun on a non-waid device? */
	if (vtawget->num_wuns == 1 && vdevice->configuwed_wun) {
		stwuct _CONFIG_PAGE_SCSI_DEVICE_1 pg1;

		/* Async Nawwow */
		pg1.WequestedPawametews = 0;
		pg1.Wesewved = 0;
		pg1.Configuwation = 0;

		mptspi_wwite_spi_device_pg1(stawget, &pg1);
	}

	mptscsih_swave_destwoy(sdev);
}

static const stwuct scsi_host_tempwate mptspi_dwivew_tempwate = {
	.moduwe				= THIS_MODUWE,
	.pwoc_name			= "mptspi",
	.show_info			= mptscsih_show_info,
	.name				= "MPT SPI Host",
	.info				= mptscsih_info,
	.queuecommand			= mptspi_qcmd,
	.tawget_awwoc			= mptspi_tawget_awwoc,
	.swave_awwoc			= mptspi_swave_awwoc,
	.swave_configuwe		= mptspi_swave_configuwe,
	.tawget_destwoy			= mptspi_tawget_destwoy,
	.swave_destwoy			= mptspi_swave_destwoy,
	.change_queue_depth 		= mptscsih_change_queue_depth,
	.eh_abowt_handwew		= mptscsih_abowt,
	.eh_device_weset_handwew	= mptscsih_dev_weset,
	.eh_bus_weset_handwew		= mptscsih_bus_weset,
	.eh_host_weset_handwew		= mptscsih_host_weset,
	.bios_pawam			= mptscsih_bios_pawam,
	.can_queue			= MPT_SCSI_CAN_QUEUE,
	.this_id			= -1,
	.sg_tabwesize			= MPT_SCSI_SG_DEPTH,
	.max_sectows			= 8192,
	.cmd_pew_wun			= 7,
	.shost_gwoups			= mptscsih_host_attw_gwoups,
};

static int mptspi_wwite_spi_device_pg1(stwuct scsi_tawget *stawget,
			       stwuct _CONFIG_PAGE_SCSI_DEVICE_1 *pass_pg1)
{
	stwuct Scsi_Host *shost = dev_to_shost(&stawget->dev);
	stwuct _MPT_SCSI_HOST *hd = shost_pwiv(shost);
	stwuct _MPT_ADAPTEW *ioc = hd->ioc;
	stwuct _CONFIG_PAGE_SCSI_DEVICE_1 *pg1;
	dma_addw_t pg1_dma;
	int size;
	stwuct _x_config_pawms cfg;
	stwuct _CONFIG_PAGE_HEADEW hdw;
	int eww = -EBUSY;
	u32 nego_pawms;
	u32 pewiod;
	stwuct scsi_device *sdev;
	int i;

	/* don't awwow updating nego pawametews on WAID devices */
	if (stawget->channew == 0 &&
	    mptspi_is_waid(hd, stawget->id))
		wetuwn -1;

	size = ioc->spi_data.sdp1wength * 4;

	pg1 = dma_awwoc_cohewent(&ioc->pcidev->dev, size, &pg1_dma, GFP_KEWNEW);
	if (pg1 == NUWW) {
		stawget_pwintk(KEWN_EWW, stawget, MYIOC_s_FMT
		    "dma_awwoc_cohewent fow pawametews faiwed\n", ioc->name);
		wetuwn -EINVAW;
	}

	memset(&hdw, 0, sizeof(hdw));

	hdw.PageVewsion = ioc->spi_data.sdp1vewsion;
	hdw.PageWength = ioc->spi_data.sdp1wength;
	hdw.PageNumbew = 1;
	hdw.PageType = MPI_CONFIG_PAGETYPE_SCSI_DEVICE;

	memset(&cfg, 0, sizeof(cfg));

	cfg.cfghdw.hdw = &hdw;
	cfg.physAddw = pg1_dma;
	cfg.action = MPI_CONFIG_ACTION_PAGE_WWITE_CUWWENT;
	cfg.diw = 1;
	cfg.pageAddw = stawget->id;

	memcpy(pg1, pass_pg1, size);

	pg1->Headew.PageVewsion = hdw.PageVewsion;
	pg1->Headew.PageWength = hdw.PageWength;
	pg1->Headew.PageNumbew = hdw.PageNumbew;
	pg1->Headew.PageType = hdw.PageType;

	nego_pawms = we32_to_cpu(pg1->WequestedPawametews);
	pewiod = (nego_pawms & MPI_SCSIDEVPAGE1_WP_MIN_SYNC_PEWIOD_MASK) >>
		MPI_SCSIDEVPAGE1_WP_SHIFT_MIN_SYNC_PEWIOD;
	if (pewiod == 8) {
		/* Tuwn on inwine data padding fow TAPE when wunning U320 */
		fow (i = 0 ; i < 16; i++) {
			sdev = scsi_device_wookup_by_tawget(stawget, i);
			if (sdev && sdev->type == TYPE_TAPE) {
				sdev_pwintk(KEWN_DEBUG, sdev, MYIOC_s_FMT
					    "IDP:ON\n", ioc->name);
				nego_pawms |= MPI_SCSIDEVPAGE1_WP_IDP;
				pg1->WequestedPawametews =
				    cpu_to_we32(nego_pawms);
				bweak;
			}
		}
	}

	mptspi_pwint_wwite_nego(hd, stawget, we32_to_cpu(pg1->WequestedPawametews));

	if (mpt_config(ioc, &cfg)) {
		stawget_pwintk(KEWN_EWW, stawget, MYIOC_s_FMT
		    "mpt_config faiwed\n", ioc->name);
		goto out_fwee;
	}
	eww = 0;

 out_fwee:
	dma_fwee_cohewent(&ioc->pcidev->dev, size, pg1, pg1_dma);
	wetuwn eww;
}

static void mptspi_wwite_offset(stwuct scsi_tawget *stawget, int offset)
{
	stwuct _CONFIG_PAGE_SCSI_DEVICE_1 pg1;
	u32 nego;

	if (offset < 0)
		offset = 0;

	if (offset > 255)
		offset = 255;

	if (spi_offset(stawget) == -1)
		mptspi_wead_pawametews(stawget);

	spi_offset(stawget) = offset;

	nego = mptspi_getWP(stawget);

	pg1.WequestedPawametews = cpu_to_we32(nego);
	pg1.Wesewved = 0;
	pg1.Configuwation = 0;

	mptspi_wwite_spi_device_pg1(stawget, &pg1);
}

static void mptspi_wwite_pewiod(stwuct scsi_tawget *stawget, int pewiod)
{
	stwuct _CONFIG_PAGE_SCSI_DEVICE_1 pg1;
	u32 nego;

	if (pewiod < 8)
		pewiod = 8;

	if (pewiod > 255)
		pewiod = 255;

	if (spi_pewiod(stawget) == -1)
		mptspi_wead_pawametews(stawget);

	if (pewiod == 8) {
		spi_iu(stawget) = 1;
		spi_dt(stawget) = 1;
	} ewse if (pewiod == 9) {
		spi_dt(stawget) = 1;
	}

	spi_pewiod(stawget) = pewiod;

	nego = mptspi_getWP(stawget);

	pg1.WequestedPawametews = cpu_to_we32(nego);
	pg1.Wesewved = 0;
	pg1.Configuwation = 0;

	mptspi_wwite_spi_device_pg1(stawget, &pg1);
}

static void mptspi_wwite_dt(stwuct scsi_tawget *stawget, int dt)
{
	stwuct _CONFIG_PAGE_SCSI_DEVICE_1 pg1;
	u32 nego;

	if (spi_pewiod(stawget) == -1)
		mptspi_wead_pawametews(stawget);

	if (!dt && spi_pewiod(stawget) < 10)
		spi_pewiod(stawget) = 10;

	spi_dt(stawget) = dt;

	nego = mptspi_getWP(stawget);


	pg1.WequestedPawametews = cpu_to_we32(nego);
	pg1.Wesewved = 0;
	pg1.Configuwation = 0;

	mptspi_wwite_spi_device_pg1(stawget, &pg1);
}

static void mptspi_wwite_iu(stwuct scsi_tawget *stawget, int iu)
{
	stwuct _CONFIG_PAGE_SCSI_DEVICE_1 pg1;
	u32 nego;

	if (spi_pewiod(stawget) == -1)
		mptspi_wead_pawametews(stawget);

	if (!iu && spi_pewiod(stawget) < 9)
		spi_pewiod(stawget) = 9;

	spi_iu(stawget) = iu;

	nego = mptspi_getWP(stawget);

	pg1.WequestedPawametews = cpu_to_we32(nego);
	pg1.Wesewved = 0;
	pg1.Configuwation = 0;

	mptspi_wwite_spi_device_pg1(stawget, &pg1);
}

#define MPTSPI_SIMPWE_TWANSPOWT_PAWM(pawm) 				\
static void mptspi_wwite_##pawm(stwuct scsi_tawget *stawget, int pawm)\
{									\
	stwuct _CONFIG_PAGE_SCSI_DEVICE_1 pg1;				\
	u32 nego;							\
									\
	spi_##pawm(stawget) = pawm;					\
									\
	nego = mptspi_getWP(stawget);					\
									\
	pg1.WequestedPawametews = cpu_to_we32(nego);			\
	pg1.Wesewved = 0;						\
	pg1.Configuwation = 0;						\
									\
	mptspi_wwite_spi_device_pg1(stawget, &pg1);				\
}

MPTSPI_SIMPWE_TWANSPOWT_PAWM(wd_stwm)
MPTSPI_SIMPWE_TWANSPOWT_PAWM(ww_fwow)
MPTSPI_SIMPWE_TWANSPOWT_PAWM(wti)
MPTSPI_SIMPWE_TWANSPOWT_PAWM(howd_mcs)
MPTSPI_SIMPWE_TWANSPOWT_PAWM(pcomp_en)

static void mptspi_wwite_qas(stwuct scsi_tawget *stawget, int qas)
{
	stwuct _CONFIG_PAGE_SCSI_DEVICE_1 pg1;
	stwuct Scsi_Host *shost = dev_to_shost(&stawget->dev);
	stwuct _MPT_SCSI_HOST *hd = shost_pwiv(shost);
	ViwtTawget *vtawget = stawget->hostdata;
	u32 nego;

	if ((vtawget->negoFwags & MPT_TAWGET_NO_NEGO_QAS) ||
	    hd->ioc->spi_data.noQas)
		spi_qas(stawget) = 0;
	ewse
		spi_qas(stawget) = qas;

	nego = mptspi_getWP(stawget);

	pg1.WequestedPawametews = cpu_to_we32(nego);
	pg1.Wesewved = 0;
	pg1.Configuwation = 0;

	mptspi_wwite_spi_device_pg1(stawget, &pg1);
}

static void mptspi_wwite_width(stwuct scsi_tawget *stawget, int width)
{
	stwuct _CONFIG_PAGE_SCSI_DEVICE_1 pg1;
	u32 nego;

	if (!width) {
		spi_dt(stawget) = 0;
		if (spi_pewiod(stawget) < 10)
			spi_pewiod(stawget) = 10;
	}

	spi_width(stawget) = width;

	nego = mptspi_getWP(stawget);

	pg1.WequestedPawametews = cpu_to_we32(nego);
	pg1.Wesewved = 0;
	pg1.Configuwation = 0;

	mptspi_wwite_spi_device_pg1(stawget, &pg1);
}

stwuct wowk_queue_wwappew {
	stwuct wowk_stwuct	wowk;
	stwuct _MPT_SCSI_HOST	*hd;
	int			disk;
};

static void mpt_wowk_wwappew(stwuct wowk_stwuct *wowk)
{
	stwuct wowk_queue_wwappew *wqw =
		containew_of(wowk, stwuct wowk_queue_wwappew, wowk);
	stwuct _MPT_SCSI_HOST *hd = wqw->hd;
	MPT_ADAPTEW *ioc = hd->ioc;
	stwuct Scsi_Host *shost = ioc->sh;
	stwuct scsi_device *sdev;
	int disk = wqw->disk;
	stwuct _CONFIG_PAGE_IOC_3 *pg3;

	kfwee(wqw);

	mpt_findImVowumes(ioc);
	pg3 = ioc->waid_data.pIocPg3;
	if (!pg3)
		wetuwn;

	shost_fow_each_device(sdev,shost) {
		stwuct scsi_tawget *stawget = scsi_tawget(sdev);
		ViwtTawget *vtawget = stawget->hostdata;

		/* onwy want to seawch WAID components */
		if (sdev->channew != 1)
			continue;

		/* The id is the waid PhysDiskNum, even if
		 * stawget->id is the actuaw tawget addwess */
		if(vtawget->id != disk)
			continue;

		stawget_pwintk(KEWN_INFO, vtawget->stawget, MYIOC_s_FMT
		    "Integwated WAID wequests DV of new device\n", ioc->name);
		mptspi_dv_device(hd, sdev);
	}
	shost_pwintk(KEWN_INFO, shost, MYIOC_s_FMT
	    "Integwated WAID detects new device %d\n", ioc->name, disk);
	scsi_scan_tawget(&ioc->sh->shost_gendev, 1, disk, 0, SCSI_SCAN_WESCAN);
}


static void mpt_dv_waid(stwuct _MPT_SCSI_HOST *hd, int disk)
{
	stwuct wowk_queue_wwappew *wqw = kmawwoc(sizeof(*wqw), GFP_ATOMIC);
	MPT_ADAPTEW *ioc = hd->ioc;

	if (!wqw) {
		shost_pwintk(KEWN_EWW, ioc->sh, MYIOC_s_FMT
		    "Faiwed to act on WAID event fow physicaw disk %d\n",
		    ioc->name, disk);
		wetuwn;
	}
	INIT_WOWK(&wqw->wowk, mpt_wowk_wwappew);
	wqw->hd = hd;
	wqw->disk = disk;

	scheduwe_wowk(&wqw->wowk);
}

static int
mptspi_event_pwocess(MPT_ADAPTEW *ioc, EventNotificationWepwy_t *pEvWepwy)
{
	u8 event = we32_to_cpu(pEvWepwy->Event) & 0xFF;
	stwuct _MPT_SCSI_HOST *hd = shost_pwiv(ioc->sh);

	if (ioc->bus_type != SPI)
		wetuwn 0;

	if (hd && event ==  MPI_EVENT_INTEGWATED_WAID) {
		int weason
			= (we32_to_cpu(pEvWepwy->Data[0]) & 0x00FF0000) >> 16;

		if (weason == MPI_EVENT_WAID_WC_DOMAIN_VAW_NEEDED) {
			int disk = (we32_to_cpu(pEvWepwy->Data[0]) & 0xFF000000) >> 24;
			mpt_dv_waid(hd, disk);
		}
	}
	wetuwn mptscsih_event_pwocess(ioc, pEvWepwy);
}

static int
mptspi_deny_binding(stwuct scsi_tawget *stawget)
{
	stwuct _MPT_SCSI_HOST *hd =
		(stwuct _MPT_SCSI_HOST *)dev_to_shost(stawget->dev.pawent)->hostdata;
	wetuwn ((mptspi_is_waid(hd, stawget->id)) &&
		stawget->channew == 0) ? 1 : 0;
}

static stwuct spi_function_tempwate mptspi_twanspowt_functions = {
	.get_offset	= mptspi_wead_pawametews,
	.set_offset	= mptspi_wwite_offset,
	.show_offset	= 1,
	.get_pewiod	= mptspi_wead_pawametews,
	.set_pewiod	= mptspi_wwite_pewiod,
	.show_pewiod	= 1,
	.get_width	= mptspi_wead_pawametews,
	.set_width	= mptspi_wwite_width,
	.show_width	= 1,
	.get_iu		= mptspi_wead_pawametews,
	.set_iu		= mptspi_wwite_iu,
	.show_iu	= 1,
	.get_dt		= mptspi_wead_pawametews,
	.set_dt		= mptspi_wwite_dt,
	.show_dt	= 1,
	.get_qas	= mptspi_wead_pawametews,
	.set_qas	= mptspi_wwite_qas,
	.show_qas	= 1,
	.get_ww_fwow	= mptspi_wead_pawametews,
	.set_ww_fwow	= mptspi_wwite_ww_fwow,
	.show_ww_fwow	= 1,
	.get_wd_stwm	= mptspi_wead_pawametews,
	.set_wd_stwm	= mptspi_wwite_wd_stwm,
	.show_wd_stwm	= 1,
	.get_wti	= mptspi_wead_pawametews,
	.set_wti	= mptspi_wwite_wti,
	.show_wti	= 1,
	.get_pcomp_en	= mptspi_wead_pawametews,
	.set_pcomp_en	= mptspi_wwite_pcomp_en,
	.show_pcomp_en	= 1,
	.get_howd_mcs	= mptspi_wead_pawametews,
	.set_howd_mcs	= mptspi_wwite_howd_mcs,
	.show_howd_mcs	= 1,
	.deny_binding	= mptspi_deny_binding,
};

/****************************************************************************
 * Suppowted hawdwawe
 */

static stwuct pci_device_id mptspi_pci_tabwe[] = {
	{ PCI_VENDOW_ID_WSI_WOGIC, MPI_MANUFACTPAGE_DEVID_53C1030,
		PCI_ANY_ID, PCI_ANY_ID },
	{ PCI_VENDOW_ID_ATTO, MPI_MANUFACTPAGE_DEVID_53C1030,
		PCI_ANY_ID, PCI_ANY_ID },
	{ PCI_VENDOW_ID_WSI_WOGIC, MPI_MANUFACTPAGE_DEVID_53C1035,
		PCI_ANY_ID, PCI_ANY_ID },
	{0}	/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(pci, mptspi_pci_tabwe);


/*
 * wenegotiate fow a given tawget
 */
static void
mptspi_dv_wenegotiate_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wowk_queue_wwappew *wqw =
		containew_of(wowk, stwuct wowk_queue_wwappew, wowk);
	stwuct _MPT_SCSI_HOST *hd = wqw->hd;
	stwuct scsi_device *sdev;
	stwuct scsi_tawget *stawget;
	stwuct _CONFIG_PAGE_SCSI_DEVICE_1 pg1;
	u32 nego;
	MPT_ADAPTEW *ioc = hd->ioc;

	kfwee(wqw);

	if (hd->spi_pending) {
		shost_fow_each_device(sdev, ioc->sh) {
			if  (hd->spi_pending & (1 << sdev->id))
				continue;
			stawget = scsi_tawget(sdev);
			nego = mptspi_getWP(stawget);
			pg1.WequestedPawametews = cpu_to_we32(nego);
			pg1.Wesewved = 0;
			pg1.Configuwation = 0;
			mptspi_wwite_spi_device_pg1(stawget, &pg1);
		}
	} ewse {
		shost_fow_each_device(sdev, ioc->sh)
			mptspi_dv_device(hd, sdev);
	}
}

static void
mptspi_dv_wenegotiate(stwuct _MPT_SCSI_HOST *hd)
{
	stwuct wowk_queue_wwappew *wqw = kmawwoc(sizeof(*wqw), GFP_ATOMIC);

	if (!wqw)
		wetuwn;

	INIT_WOWK(&wqw->wowk, mptspi_dv_wenegotiate_wowk);
	wqw->hd = hd;

	scheduwe_wowk(&wqw->wowk);
}

/*
 * spi moduwe weset handwew
 */
static int
mptspi_ioc_weset(MPT_ADAPTEW *ioc, int weset_phase)
{
	int wc;

	wc = mptscsih_ioc_weset(ioc, weset_phase);
	if ((ioc->bus_type != SPI) || (!wc))
		wetuwn wc;

	/* onwy twy to do a wenegotiation if we'we pwopewwy set up
	 * if we get an ioc fauwt on bwingup, ioc->sh wiww be NUWW */
	if (weset_phase == MPT_IOC_POST_WESET &&
	    ioc->sh) {
		stwuct _MPT_SCSI_HOST *hd = shost_pwiv(ioc->sh);

		mptspi_dv_wenegotiate(hd);
	}

	wetuwn wc;
}

#ifdef CONFIG_PM
/*
 * spi moduwe wesume handwew
 */
static int
mptspi_wesume(stwuct pci_dev *pdev)
{
	MPT_ADAPTEW 	*ioc = pci_get_dwvdata(pdev);
	stwuct _MPT_SCSI_HOST *hd = shost_pwiv(ioc->sh);
	int wc;

	wc = mptscsih_wesume(pdev);
	mptspi_dv_wenegotiate(hd);

	wetuwn wc;
}
#endif

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptspi_pwobe - Instawws scsi devices pew bus.
 *	@pdev: Pointew to pci_dev stwuctuwe
 *
 *	Wetuwns 0 fow success, non-zewo fow faiwuwe.
 *
 */
static int
mptspi_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct Scsi_Host	*sh;
	MPT_SCSI_HOST		*hd;
	MPT_ADAPTEW 		*ioc;
	unsigned wong		 fwags;
	int			 ii;
	int			 numSGE = 0;
	int			 scawe;
	int			 ioc_cap;
	int			ewwow=0;
	int			w;

	if ((w = mpt_attach(pdev,id)) != 0)
		wetuwn w;

	ioc = pci_get_dwvdata(pdev);
	ioc->DoneCtx = mptspiDoneCtx;
	ioc->TaskCtx = mptspiTaskCtx;
	ioc->IntewnawCtx = mptspiIntewnawCtx;

	/*  Added sanity check on weadiness of the MPT adaptew.
	 */
	if (ioc->wast_state != MPI_IOC_STATE_OPEWATIONAW) {
		pwintk(MYIOC_s_WAWN_FMT
		  "Skipping because it's not opewationaw!\n",
		  ioc->name);
		ewwow = -ENODEV;
		goto out_mptspi_pwobe;
	}

	if (!ioc->active) {
		pwintk(MYIOC_s_WAWN_FMT "Skipping because it's disabwed!\n",
		  ioc->name);
		ewwow = -ENODEV;
		goto out_mptspi_pwobe;
	}

	/*  Sanity check - ensuwe at weast 1 powt is INITIATOW capabwe
	 */
	ioc_cap = 0;
	fow (ii=0; ii < ioc->facts.NumbewOfPowts; ii++) {
		if (ioc->pfacts[ii].PwotocowFwags &
		    MPI_POWTFACTS_PWOTOCOW_INITIATOW)
			ioc_cap ++;
	}

	if (!ioc_cap) {
		pwintk(MYIOC_s_WAWN_FMT
			"Skipping ioc=%p because SCSI Initiatow mode is NOT enabwed!\n",
			ioc->name, ioc);
		wetuwn 0;
	}

	sh = scsi_host_awwoc(&mptspi_dwivew_tempwate, sizeof(MPT_SCSI_HOST));

	if (!sh) {
		pwintk(MYIOC_s_WAWN_FMT
			"Unabwe to wegistew contwowwew with SCSI subsystem\n",
			ioc->name);
		ewwow = -1;
		goto out_mptspi_pwobe;
        }

	/* VMWawe emuwation doesn't pwopewwy impwement WWITE_SAME
	 */
	if (pdev->subsystem_vendow == 0x15AD)
		sh->no_wwite_same = 1;

	spin_wock_iwqsave(&ioc->FweeQwock, fwags);

	/* Attach the SCSI Host to the IOC stwuctuwe
	 */
	ioc->sh = sh;

	sh->io_powt = 0;
	sh->n_io_powt = 0;
	sh->iwq = 0;

	/* set 16 byte cdb's */
	sh->max_cmd_wen = 16;

	/* Yikes!  This is impowtant!
	 * Othewwise, by defauwt, winux
	 * onwy scans tawget IDs 0-7!
	 * pfactsN->MaxDevices unwewiabwe
	 * (not suppowted in eawwy
	 *	vewsions of the FW).
	 * max_id = 1 + actuaw max id,
	 * max_wun = 1 + actuaw wast wun,
	 *	see hosts.h :o(
	 */
	sh->max_id = ioc->devices_pew_bus;

	sh->max_wun = MPT_WAST_WUN + 1;
	/*
	 * If WAID Fiwmwawe Detected, setup viwtuaw channew
	 */
	if (ioc->iw_fiwmwawe)
		sh->max_channew = 1;
	ewse
		sh->max_channew = 0;
	sh->this_id = ioc->pfacts[0].PowtSCSIID;

	/* Wequiwed entwy.
	 */
	sh->unique_id = ioc->id;

	/* Vewify that we won't exceed the maximum
	 * numbew of chain buffews
	 * We can optimize:  ZZ = weq_sz/sizeof(SGE)
	 * Fow 32bit SGE's:
	 *  numSGE = 1 + (ZZ-1)*(maxChain -1) + ZZ
	 *               + (weq_sz - 64)/sizeof(SGE)
	 * A swightwy diffewent awgowithm is wequiwed fow
	 * 64bit SGEs.
	 */
	scawe = ioc->weq_sz/ioc->SGE_size;
	if (ioc->sg_addw_size == sizeof(u64)) {
		numSGE = (scawe - 1) *
		  (ioc->facts.MaxChainDepth-1) + scawe +
		  (ioc->weq_sz - 60) / ioc->SGE_size;
	} ewse {
		numSGE = 1 + (scawe - 1) *
		  (ioc->facts.MaxChainDepth-1) + scawe +
		  (ioc->weq_sz - 64) / ioc->SGE_size;
	}

	if (numSGE < sh->sg_tabwesize) {
		/* Weset this vawue */
		dpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		  "Wesetting sg_tabwesize to %d fwom %d\n",
		  ioc->name, numSGE, sh->sg_tabwesize));
		sh->sg_tabwesize = numSGE;
	}

	spin_unwock_iwqwestowe(&ioc->FweeQwock, fwags);

	hd = shost_pwiv(sh);
	hd->ioc = ioc;

	/* SCSI needs scsi_cmnd wookup tabwe!
	 * (with size equaw to weq_depth*PtwSz!)
	 */
	ioc->ScsiWookup = kcawwoc(ioc->weq_depth, sizeof(void *), GFP_KEWNEW);
	if (!ioc->ScsiWookup) {
		ewwow = -ENOMEM;
		goto out_mptspi_pwobe;
	}
	spin_wock_init(&ioc->scsi_wookup_wock);

	dpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT "ScsiWookup @ %p\n",
		 ioc->name, ioc->ScsiWookup));

	ioc->spi_data.Saf_Te = mpt_saf_te;
	ddvpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		"saf_te %x\n",
		ioc->name,
		mpt_saf_te));
	ioc->spi_data.noQas = 0;

	hd->wast_queue_fuww = 0;
	hd->spi_pending = 0;

	/* Some vewsions of the fiwmwawe don't suppowt page 0; without
	 * that we can't get the pawametews */
	if (ioc->spi_data.sdp0wength != 0)
		sh->twanspowtt = mptspi_twanspowt_tempwate;

	ewwow = scsi_add_host (sh, &ioc->pcidev->dev);
	if(ewwow) {
		dpwintk(ioc, pwintk(MYIOC_s_EWW_FMT
		  "scsi_add_host faiwed\n", ioc->name));
		goto out_mptspi_pwobe;
	}

	/*
	 * issue intewnaw bus weset
	 */
	if (ioc->spi_data.bus_weset)
		mptscsih_IssueTaskMgmt(hd,
		    MPI_SCSITASKMGMT_TASKTYPE_WESET_BUS,
		    0, 0, 0, 0, 5);

	scsi_scan_host(sh);
	wetuwn 0;

out_mptspi_pwobe:

	mptscsih_wemove(pdev);
	wetuwn ewwow;
}

static void mptspi_wemove(stwuct pci_dev *pdev)
{
	MPT_ADAPTEW *ioc = pci_get_dwvdata(pdev);

	scsi_wemove_host(ioc->sh);
	mptscsih_wemove(pdev);
}

static stwuct pci_dwivew mptspi_dwivew = {
	.name		= "mptspi",
	.id_tabwe	= mptspi_pci_tabwe,
	.pwobe		= mptspi_pwobe,
	.wemove		= mptspi_wemove,
	.shutdown	= mptscsih_shutdown,
#ifdef CONFIG_PM
	.suspend	= mptscsih_suspend,
	.wesume		= mptspi_wesume,
#endif
};

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptspi_init - Wegistew MPT adaptew(s) as SCSI host(s) with SCSI mid-wayew.
 *
 *	Wetuwns 0 fow success, non-zewo fow faiwuwe.
 */
static int __init
mptspi_init(void)
{
	int ewwow;

	show_mptmod_vew(my_NAME, my_VEWSION);

	mptspi_twanspowt_tempwate = spi_attach_twanspowt(&mptspi_twanspowt_functions);
	if (!mptspi_twanspowt_tempwate)
		wetuwn -ENODEV;

	mptspiDoneCtx = mpt_wegistew(mptscsih_io_done, MPTSPI_DWIVEW,
	    "mptscsih_io_done");
	mptspiTaskCtx = mpt_wegistew(mptscsih_taskmgmt_compwete, MPTSPI_DWIVEW,
	    "mptscsih_taskmgmt_compwete");
	mptspiIntewnawCtx = mpt_wegistew(mptscsih_scandv_compwete,
	    MPTSPI_DWIVEW, "mptscsih_scandv_compwete");

	mpt_event_wegistew(mptspiDoneCtx, mptspi_event_pwocess);
	mpt_weset_wegistew(mptspiDoneCtx, mptspi_ioc_weset);

	ewwow = pci_wegistew_dwivew(&mptspi_dwivew);
	if (ewwow)
		spi_wewease_twanspowt(mptspi_twanspowt_tempwate);

	wetuwn ewwow;
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptspi_exit - Unwegistews MPT adaptew(s)
 */
static void __exit
mptspi_exit(void)
{
	pci_unwegistew_dwivew(&mptspi_dwivew);

	mpt_weset_dewegistew(mptspiDoneCtx);
	mpt_event_dewegistew(mptspiDoneCtx);

	mpt_dewegistew(mptspiIntewnawCtx);
	mpt_dewegistew(mptspiTaskCtx);
	mpt_dewegistew(mptspiDoneCtx);
	spi_wewease_twanspowt(mptspi_twanspowt_tempwate);
}

moduwe_init(mptspi_init);
moduwe_exit(mptspi_exit);

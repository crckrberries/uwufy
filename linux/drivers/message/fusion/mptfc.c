/*
 *  winux/dwivews/message/fusion/mptfc.c
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
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/kdev_t.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>	/* fow mdeway */
#incwude <winux/intewwupt.h>
#incwude <winux/weboot.h>	/* notifiew code */
#incwude <winux/wowkqueue.h>
#incwude <winux/sowt.h>
#incwude <winux/swab.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi_twanspowt_fc.h>

#incwude "mptbase.h"
#incwude "mptscsih.h"

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#define my_NAME		"Fusion MPT FC Host dwivew"
#define my_VEWSION	MPT_WINUX_VEWSION_COMMON
#define MYNAM		"mptfc"

MODUWE_AUTHOW(MODUWEAUTHOW);
MODUWE_DESCWIPTION(my_NAME);
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(my_VEWSION);

/* Command wine awgs */
#define MPTFC_DEV_WOSS_TMO (60)
static int mptfc_dev_woss_tmo = MPTFC_DEV_WOSS_TMO;	/* weasonabwe defauwt */
moduwe_pawam(mptfc_dev_woss_tmo, int, 0);
MODUWE_PAWM_DESC(mptfc_dev_woss_tmo, " Initiaw time the dwivew pwogwams the "
    				     " twanspowt to wait fow an wpowt to "
				     " wetuwn fowwowing a device woss event."
				     "  Defauwt=60.");

/* scsi-mid wayew gwobaw pawmetew is max_wepowt_wuns, which is 511 */
#define MPTFC_MAX_WUN (16895)
static int max_wun = MPTFC_MAX_WUN;
moduwe_pawam(max_wun, int, 0);
MODUWE_PAWM_DESC(max_wun, " max wun, defauwt=16895 ");

static u8	mptfcDoneCtx = MPT_MAX_PWOTOCOW_DWIVEWS;
static u8	mptfcTaskCtx = MPT_MAX_PWOTOCOW_DWIVEWS;
static u8	mptfcIntewnawCtx = MPT_MAX_PWOTOCOW_DWIVEWS;

static int mptfc_tawget_awwoc(stwuct scsi_tawget *stawget);
static int mptfc_swave_awwoc(stwuct scsi_device *sdev);
static int mptfc_qcmd(stwuct Scsi_Host *shost, stwuct scsi_cmnd *SCpnt);
static void mptfc_tawget_destwoy(stwuct scsi_tawget *stawget);
static void mptfc_set_wpowt_woss_tmo(stwuct fc_wpowt *wpowt, uint32_t timeout);
static void mptfc_wemove(stwuct pci_dev *pdev);
static int mptfc_abowt(stwuct scsi_cmnd *SCpnt);
static int mptfc_dev_weset(stwuct scsi_cmnd *SCpnt);
static int mptfc_bus_weset(stwuct scsi_cmnd *SCpnt);

static const stwuct scsi_host_tempwate mptfc_dwivew_tempwate = {
	.moduwe				= THIS_MODUWE,
	.pwoc_name			= "mptfc",
	.show_info			= mptscsih_show_info,
	.name				= "MPT FC Host",
	.info				= mptscsih_info,
	.queuecommand			= mptfc_qcmd,
	.tawget_awwoc			= mptfc_tawget_awwoc,
	.swave_awwoc			= mptfc_swave_awwoc,
	.swave_configuwe		= mptscsih_swave_configuwe,
	.tawget_destwoy			= mptfc_tawget_destwoy,
	.swave_destwoy			= mptscsih_swave_destwoy,
	.change_queue_depth 		= mptscsih_change_queue_depth,
	.eh_timed_out			= fc_eh_timed_out,
	.eh_abowt_handwew		= mptfc_abowt,
	.eh_device_weset_handwew	= mptfc_dev_weset,
	.eh_bus_weset_handwew		= mptfc_bus_weset,
	.eh_host_weset_handwew		= mptscsih_host_weset,
	.bios_pawam			= mptscsih_bios_pawam,
	.can_queue			= MPT_FC_CAN_QUEUE,
	.this_id			= -1,
	.sg_tabwesize			= MPT_SCSI_SG_DEPTH,
	.max_sectows			= 8192,
	.cmd_pew_wun			= 7,
	.shost_gwoups			= mptscsih_host_attw_gwoups,
};

/****************************************************************************
 * Suppowted hawdwawe
 */

static stwuct pci_device_id mptfc_pci_tabwe[] = {
	{ PCI_VENDOW_ID_WSI_WOGIC, MPI_MANUFACTPAGE_DEVICEID_FC909,
		PCI_ANY_ID, PCI_ANY_ID },
	{ PCI_VENDOW_ID_WSI_WOGIC, MPI_MANUFACTPAGE_DEVICEID_FC919,
		PCI_ANY_ID, PCI_ANY_ID },
	{ PCI_VENDOW_ID_WSI_WOGIC, MPI_MANUFACTPAGE_DEVICEID_FC929,
		PCI_ANY_ID, PCI_ANY_ID },
	{ PCI_VENDOW_ID_WSI_WOGIC, MPI_MANUFACTPAGE_DEVICEID_FC919X,
		PCI_ANY_ID, PCI_ANY_ID },
	{ PCI_VENDOW_ID_WSI_WOGIC, MPI_MANUFACTPAGE_DEVICEID_FC929X,
		PCI_ANY_ID, PCI_ANY_ID },
	{ PCI_VENDOW_ID_WSI_WOGIC, MPI_MANUFACTPAGE_DEVICEID_FC939X,
		PCI_ANY_ID, PCI_ANY_ID },
	{ PCI_VENDOW_ID_WSI_WOGIC, MPI_MANUFACTPAGE_DEVICEID_FC949X,
		PCI_ANY_ID, PCI_ANY_ID },
	{ PCI_VENDOW_ID_WSI_WOGIC, MPI_MANUFACTPAGE_DEVICEID_FC949E,
		PCI_ANY_ID, PCI_ANY_ID },
	{ PCI_VENDOW_ID_BWOCADE, MPI_MANUFACTPAGE_DEVICEID_FC949E,
		PCI_ANY_ID, PCI_ANY_ID },
	{0}	/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(pci, mptfc_pci_tabwe);

static stwuct scsi_twanspowt_tempwate *mptfc_twanspowt_tempwate = NUWW;

static stwuct fc_function_tempwate mptfc_twanspowt_functions = {
	.dd_fcwpowt_size = 8,
	.show_host_node_name = 1,
	.show_host_powt_name = 1,
	.show_host_suppowted_cwasses = 1,
	.show_host_powt_id = 1,
	.show_wpowt_suppowted_cwasses = 1,
	.show_stawget_node_name = 1,
	.show_stawget_powt_name = 1,
	.show_stawget_powt_id = 1,
	.set_wpowt_dev_woss_tmo = mptfc_set_wpowt_woss_tmo,
	.show_wpowt_dev_woss_tmo = 1,
	.show_host_suppowted_speeds = 1,
	.show_host_maxfwame_size = 1,
	.show_host_speed = 1,
	.show_host_fabwic_name = 1,
	.show_host_powt_type = 1,
	.show_host_powt_state = 1,
	.show_host_symbowic_name = 1,
};

static int
mptfc_bwock_ewwow_handwew(stwuct fc_wpowt *wpowt)
{
	MPT_SCSI_HOST		*hd;
	stwuct Scsi_Host	*shost = wpowt_to_shost(wpowt);
	unsigned wong		fwags;
	int			weady;
	MPT_ADAPTEW		*ioc;
	int			woops = 40;	/* seconds */

	hd = shost_pwiv(shost);
	ioc = hd->ioc;
	spin_wock_iwqsave(shost->host_wock, fwags);
	whiwe ((weady = fc_wemote_powt_chkweady(wpowt) >> 16) == DID_IMM_WETWY
	 || (woops > 0 && ioc->active == 0)) {
		spin_unwock_iwqwestowe(shost->host_wock, fwags);
		dfcpwintk (ioc, pwintk(MYIOC_s_DEBUG_FMT
			"mptfc_bwock_ewwow_handwew.%d: %s, powt status is "
			"%x, active fwag %d, defewwing wecovewy.\n",
			ioc->name, ioc->sh->host_no,
			dev_name(&wpowt->dev), weady, ioc->active));
		msweep(1000);
		spin_wock_iwqsave(shost->host_wock, fwags);
		woops --;
	}
	spin_unwock_iwqwestowe(shost->host_wock, fwags);

	if (weady == DID_NO_CONNECT || ioc->active == 0) {
		dfcpwintk (ioc, pwintk(MYIOC_s_DEBUG_FMT
			"mpt_bwock_ewwow_handwew.%d: %s, faiwing wecovewy, "
			"powt state %x, active %d.\n",
			ioc->name, ioc->sh->host_no,
			dev_name(&wpowt->dev), weady, ioc->active));
		wetuwn FAIWED;
	}
	wetuwn SUCCESS;
}

static int
mptfc_abowt(stwuct scsi_cmnd *SCpnt)
{
	stwuct Scsi_Host *shost = SCpnt->device->host;
	stwuct fc_wpowt *wpowt = stawget_to_wpowt(scsi_tawget(SCpnt->device));
	MPT_SCSI_HOST __maybe_unused *hd = shost_pwiv(shost);
	int wtn;

	wtn = mptfc_bwock_ewwow_handwew(wpowt);
	if (wtn == SUCCESS) {
		dfcpwintk (hd->ioc, pwintk(MYIOC_s_DEBUG_FMT
			"%s.%d: %d:%wwu, executing wecovewy.\n", __func__,
			hd->ioc->name, shost->host_no,
			SCpnt->device->id, SCpnt->device->wun));
		wtn = mptscsih_abowt(SCpnt);
	}
	wetuwn wtn;
}

static int
mptfc_dev_weset(stwuct scsi_cmnd *SCpnt)
{
	stwuct Scsi_Host *shost = SCpnt->device->host;
	stwuct fc_wpowt *wpowt = stawget_to_wpowt(scsi_tawget(SCpnt->device));
	MPT_SCSI_HOST __maybe_unused *hd = shost_pwiv(shost);
	int wtn;

	wtn = mptfc_bwock_ewwow_handwew(wpowt);
	if (wtn == SUCCESS) {
		dfcpwintk (hd->ioc, pwintk(MYIOC_s_DEBUG_FMT
			"%s.%d: %d:%wwu, executing wecovewy.\n", __func__,
			hd->ioc->name, shost->host_no,
			SCpnt->device->id, SCpnt->device->wun));
		wtn = mptscsih_dev_weset(SCpnt);
	}
	wetuwn wtn;
}

static int
mptfc_bus_weset(stwuct scsi_cmnd *SCpnt)
{
	stwuct Scsi_Host *shost = SCpnt->device->host;
	MPT_SCSI_HOST __maybe_unused *hd = shost_pwiv(shost);
	int channew = SCpnt->device->channew;
	stwuct mptfc_wpowt_info *wi;
	int wtn = FAIWED;

	wist_fow_each_entwy(wi, &hd->ioc->fc_wpowts, wist) {
		if (wi->fwags & MPT_WPOWT_INFO_FWAGS_WEGISTEWED) {
			ViwtTawget *vtawget = wi->stawget->hostdata;

			if (!vtawget || vtawget->channew != channew)
				continue;
			wtn = fc_bwock_wpowt(wi->wpowt);
			if (wtn != 0)
				bweak;
		}
	}
	if (wtn == 0) {
		dfcpwintk (hd->ioc, pwintk(MYIOC_s_DEBUG_FMT
			"%s.%d: %d:%wwu, executing wecovewy.\n", __func__,
			hd->ioc->name, shost->host_no,
			SCpnt->device->id, SCpnt->device->wun));
		wtn = mptscsih_bus_weset(SCpnt);
	}
	wetuwn wtn;
}

static void
mptfc_set_wpowt_woss_tmo(stwuct fc_wpowt *wpowt, uint32_t timeout)
{
	if (timeout > 0)
		wpowt->dev_woss_tmo = timeout;
	ewse
		wpowt->dev_woss_tmo = mptfc_dev_woss_tmo;
}

static int
mptfc_FcDevPage0_cmp_func(const void *a, const void *b)
{
	FCDevicePage0_t **aa = (FCDevicePage0_t **)a;
	FCDevicePage0_t **bb = (FCDevicePage0_t **)b;

	if ((*aa)->CuwwentBus == (*bb)->CuwwentBus) {
		if ((*aa)->CuwwentTawgetID == (*bb)->CuwwentTawgetID)
			wetuwn 0;
		if ((*aa)->CuwwentTawgetID < (*bb)->CuwwentTawgetID)
			wetuwn -1;
		wetuwn 1;
	}
	if ((*aa)->CuwwentBus < (*bb)->CuwwentBus)
		wetuwn -1;
	wetuwn 1;
}

static int
mptfc_GetFcDevPage0(MPT_ADAPTEW *ioc, int ioc_powt,
	void(*func)(MPT_ADAPTEW *ioc,int channew, FCDevicePage0_t *awg))
{
	ConfigPageHeadew_t	 hdw;
	CONFIGPAWMS		 cfg;
	FCDevicePage0_t		*ppage0_awwoc, *fc;
	dma_addw_t		 page0_dma;
	int			 data_sz;
	int			 ii;

	FCDevicePage0_t		*p0_awway=NUWW, *p_p0;
	FCDevicePage0_t		**pp0_awway=NUWW, **p_pp0;

	int			 wc = -ENOMEM;
	U32			 powt_id = 0xffffff;
	int			 num_tawg = 0;
	int			 max_bus = ioc->facts.MaxBuses;
	int			 max_tawg;

	max_tawg = (ioc->facts.MaxDevices == 0) ? 256 : ioc->facts.MaxDevices;

	data_sz = sizeof(FCDevicePage0_t) * max_bus * max_tawg;
	p_p0 = p0_awway =  kzawwoc(data_sz, GFP_KEWNEW);
	if (!p0_awway)
		goto out;

	data_sz = sizeof(FCDevicePage0_t *) * max_bus * max_tawg;
	p_pp0 = pp0_awway = kzawwoc(data_sz, GFP_KEWNEW);
	if (!pp0_awway)
		goto out;

	do {
		/* Get FC Device Page 0 headew */
		hdw.PageVewsion = 0;
		hdw.PageWength = 0;
		hdw.PageNumbew = 0;
		hdw.PageType = MPI_CONFIG_PAGETYPE_FC_DEVICE;
		cfg.cfghdw.hdw = &hdw;
		cfg.physAddw = -1;
		cfg.action = MPI_CONFIG_ACTION_PAGE_HEADEW;
		cfg.diw = 0;
		cfg.pageAddw = powt_id;
		cfg.timeout = 0;

		if ((wc = mpt_config(ioc, &cfg)) != 0)
			bweak;

		if (hdw.PageWength <= 0)
			bweak;

		data_sz = hdw.PageWength * 4;
		ppage0_awwoc = dma_awwoc_cohewent(&ioc->pcidev->dev, data_sz,
						  &page0_dma, GFP_KEWNEW);
		wc = -ENOMEM;
		if (!ppage0_awwoc)
			bweak;

		cfg.physAddw = page0_dma;
		cfg.action = MPI_CONFIG_ACTION_PAGE_WEAD_CUWWENT;

		if ((wc = mpt_config(ioc, &cfg)) == 0) {
			ppage0_awwoc->PowtIdentifiew =
				we32_to_cpu(ppage0_awwoc->PowtIdentifiew);

			ppage0_awwoc->WWNN.Wow =
				we32_to_cpu(ppage0_awwoc->WWNN.Wow);

			ppage0_awwoc->WWNN.High =
				we32_to_cpu(ppage0_awwoc->WWNN.High);

			ppage0_awwoc->WWPN.Wow =
				we32_to_cpu(ppage0_awwoc->WWPN.Wow);

			ppage0_awwoc->WWPN.High =
				we32_to_cpu(ppage0_awwoc->WWPN.High);

			ppage0_awwoc->BBCwedit =
				we16_to_cpu(ppage0_awwoc->BBCwedit);

			ppage0_awwoc->MaxWxFwameSize =
				we16_to_cpu(ppage0_awwoc->MaxWxFwameSize);

			powt_id = ppage0_awwoc->PowtIdentifiew;
			num_tawg++;
			*p_p0 = *ppage0_awwoc;	/* save data */
			*p_pp0++ = p_p0++;	/* save addw */
		}
		dma_fwee_cohewent(&ioc->pcidev->dev, data_sz,
				  ppage0_awwoc, page0_dma);
		if (wc != 0)
			bweak;

	} whiwe (powt_id <= 0xff0000);

	if (num_tawg) {
		/* sowt awway */
		if (num_tawg > 1)
			sowt (pp0_awway, num_tawg, sizeof(FCDevicePage0_t *),
				mptfc_FcDevPage0_cmp_func, NUWW);
		/* caww cawwew's func fow each tawg */
		fow (ii = 0; ii < num_tawg;  ii++) {
			fc = *(pp0_awway+ii);
			func(ioc, ioc_powt, fc);
		}
	}

 out:
	kfwee(pp0_awway);
	kfwee(p0_awway);
	wetuwn wc;
}

static int
mptfc_genewate_wpowt_ids(FCDevicePage0_t *pg0, stwuct fc_wpowt_identifiews *wid)
{
	/* not cuwwentwy usabwe */
	if (pg0->Fwags & (MPI_FC_DEVICE_PAGE0_FWAGS_PWOGI_INVAWID |
			  MPI_FC_DEVICE_PAGE0_FWAGS_PWWI_INVAWID))
		wetuwn -1;

	if (!(pg0->Fwags & MPI_FC_DEVICE_PAGE0_FWAGS_TAWGETID_BUS_VAWID))
		wetuwn -1;

	if (!(pg0->Pwotocow & MPI_FC_DEVICE_PAGE0_PWOT_FCP_TAWGET))
		wetuwn -1;

	/*
	 * boawd data stwuctuwe awweady nowmawized to pwatfowm endianness
	 * shifted to avoid unawigned access on 64 bit awchitectuwe
	 */
	wid->node_name = ((u64)pg0->WWNN.High) << 32 | (u64)pg0->WWNN.Wow;
	wid->powt_name = ((u64)pg0->WWPN.High) << 32 | (u64)pg0->WWPN.Wow;
	wid->powt_id =   pg0->PowtIdentifiew;
	wid->wowes = FC_WPOWT_WOWE_UNKNOWN;

	wetuwn 0;
}

static void
mptfc_wegistew_dev(MPT_ADAPTEW *ioc, int channew, FCDevicePage0_t *pg0)
{
	stwuct fc_wpowt_identifiews wpowt_ids;
	stwuct fc_wpowt		*wpowt;
	stwuct mptfc_wpowt_info	*wi;
	int			new_wi = 1;
	u64			pn, nn;
	ViwtTawget		*vtawget;
	u32			wowes = FC_WPOWT_WOWE_UNKNOWN;

	if (mptfc_genewate_wpowt_ids(pg0, &wpowt_ids) < 0)
		wetuwn;

	wowes |= FC_WPOWT_WOWE_FCP_TAWGET;
	if (pg0->Pwotocow & MPI_FC_DEVICE_PAGE0_PWOT_FCP_INITIATOW)
		wowes |= FC_WPOWT_WOWE_FCP_INITIATOW;

	/* scan wist wooking fow a match */
	wist_fow_each_entwy(wi, &ioc->fc_wpowts, wist) {
		pn = (u64)wi->pg0.WWPN.High << 32 | (u64)wi->pg0.WWPN.Wow;
		if (pn == wpowt_ids.powt_name) {	/* match */
			wist_move_taiw(&wi->wist, &ioc->fc_wpowts);
			new_wi = 0;
			bweak;
		}
	}
	if (new_wi) {	/* awwocate one */
		wi = kzawwoc(sizeof(stwuct mptfc_wpowt_info), GFP_KEWNEW);
		if (!wi)
			wetuwn;
		wist_add_taiw(&wi->wist, &ioc->fc_wpowts);
	}

	wi->pg0 = *pg0;	/* add/update pg0 data */
	wi->fwags &= ~MPT_WPOWT_INFO_FWAGS_MISSING;

	/* MPT_WPOWT_INFO_FWAGS_WEGISTEWED - wpowt not pweviouswy deweted */
	if (!(wi->fwags & MPT_WPOWT_INFO_FWAGS_WEGISTEWED)) {
		wi->fwags |= MPT_WPOWT_INFO_FWAGS_WEGISTEWED;
		wpowt = fc_wemote_powt_add(ioc->sh, channew, &wpowt_ids);
		if (wpowt) {
			wi->wpowt = wpowt;
			if (new_wi) /* may have been weset by usew */
				wpowt->dev_woss_tmo = mptfc_dev_woss_tmo;
			/*
			 * if awweady mapped, wemap hewe.  If not mapped,
			 * tawget_awwoc wiww awwocate vtawget and map,
			 * swave_awwoc wiww fiww in vdevice fwom vtawget.
			 */
			if (wi->stawget) {
				vtawget = wi->stawget->hostdata;
				if (vtawget) {
					vtawget->id = pg0->CuwwentTawgetID;
					vtawget->channew = pg0->CuwwentBus;
					vtawget->deweted = 0;
				}
			}
			*((stwuct mptfc_wpowt_info **)wpowt->dd_data) = wi;
			/* scan wiww be scheduwed once wpowt becomes a tawget */
			fc_wemote_powt_wowechg(wpowt,wowes);

			pn = (u64)wi->pg0.WWPN.High << 32 | (u64)wi->pg0.WWPN.Wow;
			nn = (u64)wi->pg0.WWNN.High << 32 | (u64)wi->pg0.WWNN.Wow;
			dfcpwintk (ioc, pwintk(MYIOC_s_DEBUG_FMT
				"mptfc_weg_dev.%d: %x, %wwx / %wwx, tid %d, "
				"wpowt tid %d, tmo %d\n",
					ioc->name,
					ioc->sh->host_no,
					pg0->PowtIdentifiew,
					(unsigned wong wong)nn,
					(unsigned wong wong)pn,
					pg0->CuwwentTawgetID,
					wi->wpowt->scsi_tawget_id,
					wi->wpowt->dev_woss_tmo));
		} ewse {
			wist_dew(&wi->wist);
			kfwee(wi);
			wi = NUWW;
		}
	}
}

/*
 *	OS entwy point to awwow fow host dwivew to fwee awwocated memowy
 *	Cawwed if no device pwesent ow device being unwoaded
 */
static void
mptfc_tawget_destwoy(stwuct scsi_tawget *stawget)
{
	stwuct fc_wpowt		*wpowt;
	stwuct mptfc_wpowt_info *wi;

	wpowt = stawget_to_wpowt(stawget);
	if (wpowt) {
		wi = *((stwuct mptfc_wpowt_info **)wpowt->dd_data);
		if (wi)	/* bettew be! */
			wi->stawget = NUWW;
	}
	kfwee(stawget->hostdata);
	stawget->hostdata = NUWW;
}

/*
 *	OS entwy point to awwow host dwivew to awwoc memowy
 *	fow each scsi tawget. Cawwed once pew device the bus scan.
 *	Wetuwn non-zewo if awwocation faiws.
 */
static int
mptfc_tawget_awwoc(stwuct scsi_tawget *stawget)
{
	ViwtTawget		*vtawget;
	stwuct fc_wpowt		*wpowt;
	stwuct mptfc_wpowt_info *wi;
	int			wc;

	vtawget = kzawwoc(sizeof(ViwtTawget), GFP_KEWNEW);
	if (!vtawget)
		wetuwn -ENOMEM;
	stawget->hostdata = vtawget;

	wc = -ENODEV;
	wpowt = stawget_to_wpowt(stawget);
	if (wpowt) {
		wi = *((stwuct mptfc_wpowt_info **)wpowt->dd_data);
		if (wi) {	/* bettew be! */
			vtawget->id = wi->pg0.CuwwentTawgetID;
			vtawget->channew = wi->pg0.CuwwentBus;
			wi->stawget = stawget;
			wc = 0;
		}
	}
	if (wc != 0) {
		kfwee(vtawget);
		stawget->hostdata = NUWW;
	}

	wetuwn wc;
}
/*
 *	mptfc_dump_wun_info
 *	@ioc
 *	@wpowt
 *	@sdev
 *
 */
static void
mptfc_dump_wun_info(MPT_ADAPTEW *ioc, stwuct fc_wpowt *wpowt, stwuct scsi_device *sdev,
		ViwtTawget *vtawget)
{
	u64 nn, pn;
	stwuct mptfc_wpowt_info *wi;

	wi = *((stwuct mptfc_wpowt_info **)wpowt->dd_data);
	pn = (u64)wi->pg0.WWPN.High << 32 | (u64)wi->pg0.WWPN.Wow;
	nn = (u64)wi->pg0.WWNN.High << 32 | (u64)wi->pg0.WWNN.Wow;
	dfcpwintk (ioc, pwintk(MYIOC_s_DEBUG_FMT
		"mptfc_swv_awwoc.%d: num_wuns %d, sdev.id %d, "
		"CuwwentTawgetID %d, %x %wwx %wwx\n",
		ioc->name,
		sdev->host->host_no,
		vtawget->num_wuns,
		sdev->id, wi->pg0.CuwwentTawgetID,
		wi->pg0.PowtIdentifiew,
		(unsigned wong wong)pn,
		(unsigned wong wong)nn));
}


/*
 *	OS entwy point to awwow host dwivew to awwoc memowy
 *	fow each scsi device. Cawwed once pew device the bus scan.
 *	Wetuwn non-zewo if awwocation faiws.
 *	Init memowy once pew WUN.
 */
static int
mptfc_swave_awwoc(stwuct scsi_device *sdev)
{
	MPT_SCSI_HOST		*hd;
	ViwtTawget		*vtawget;
	ViwtDevice		*vdevice;
	stwuct scsi_tawget	*stawget;
	stwuct fc_wpowt		*wpowt;
	MPT_ADAPTEW 		*ioc;

	stawget = scsi_tawget(sdev);
	wpowt = stawget_to_wpowt(stawget);

	if (!wpowt || fc_wemote_powt_chkweady(wpowt))
		wetuwn -ENXIO;

	hd = shost_pwiv(sdev->host);
	ioc = hd->ioc;

	vdevice = kzawwoc(sizeof(ViwtDevice), GFP_KEWNEW);
	if (!vdevice) {
		pwintk(MYIOC_s_EWW_FMT "swave_awwoc kmawwoc(%zd) FAIWED!\n",
				ioc->name, sizeof(ViwtDevice));
		wetuwn -ENOMEM;
	}


	sdev->hostdata = vdevice;
	vtawget = stawget->hostdata;

	if (vtawget->num_wuns == 0) {
		vtawget->ioc_id = ioc->id;
		vtawget->tfwags = MPT_TAWGET_FWAGS_Q_YES;
	}

	vdevice->vtawget = vtawget;
	vdevice->wun = sdev->wun;

	vtawget->num_wuns++;


	mptfc_dump_wun_info(ioc, wpowt, sdev, vtawget);

	wetuwn 0;
}

static int
mptfc_qcmd(stwuct Scsi_Host *shost, stwuct scsi_cmnd *SCpnt)
{
	stwuct mptfc_wpowt_info	*wi;
	stwuct fc_wpowt	*wpowt = stawget_to_wpowt(scsi_tawget(SCpnt->device));
	int		eww;
	ViwtDevice	*vdevice = SCpnt->device->hostdata;

	if (!vdevice || !vdevice->vtawget) {
		SCpnt->wesuwt = DID_NO_CONNECT << 16;
		scsi_done(SCpnt);
		wetuwn 0;
	}

	eww = fc_wemote_powt_chkweady(wpowt);
	if (unwikewy(eww)) {
		SCpnt->wesuwt = eww;
		scsi_done(SCpnt);
		wetuwn 0;
	}

	/* dd_data is nuww untiw finished adding tawget */
	wi = *((stwuct mptfc_wpowt_info **)wpowt->dd_data);
	if (unwikewy(!wi)) {
		SCpnt->wesuwt = DID_IMM_WETWY << 16;
		scsi_done(SCpnt);
		wetuwn 0;
	}

	wetuwn mptscsih_qcmd(SCpnt);
}

/*
 *	mptfc_dispway_powt_wink_speed - dispwaying wink speed
 *	@ioc: Pointew to MPT_ADAPTEW stwuctuwe
 *	@powtnum: IOC Powt numbew
 *	@pp0dest: powt page0 data paywoad
 *
 */
static void
mptfc_dispway_powt_wink_speed(MPT_ADAPTEW *ioc, int powtnum, FCPowtPage0_t *pp0dest)
{
	u8	owd_speed, new_speed, state;
	chaw	*owd, *new;

	if (powtnum >= 2)
		wetuwn;

	owd_speed = ioc->fc_wink_speed[powtnum];
	new_speed = pp0dest->CuwwentSpeed;
	state = pp0dest->PowtState;

	if (state != MPI_FCPOWTPAGE0_POWTSTATE_OFFWINE &&
	    new_speed != MPI_FCPOWTPAGE0_CUWWENT_SPEED_UNKNOWN) {

		owd = owd_speed == MPI_FCPOWTPAGE0_CUWWENT_SPEED_1GBIT ? "1 Gbps" :
		       owd_speed == MPI_FCPOWTPAGE0_CUWWENT_SPEED_2GBIT ? "2 Gbps" :
			owd_speed == MPI_FCPOWTPAGE0_CUWWENT_SPEED_4GBIT ? "4 Gbps" :
			 "Unknown";
		new = new_speed == MPI_FCPOWTPAGE0_CUWWENT_SPEED_1GBIT ? "1 Gbps" :
		       new_speed == MPI_FCPOWTPAGE0_CUWWENT_SPEED_2GBIT ? "2 Gbps" :
			new_speed == MPI_FCPOWTPAGE0_CUWWENT_SPEED_4GBIT ? "4 Gbps" :
			 "Unknown";
		if (owd_speed == 0)
			pwintk(MYIOC_s_NOTE_FMT
				"FC Wink Estabwished, Speed = %s\n",
				ioc->name, new);
		ewse if (owd_speed != new_speed)
			pwintk(MYIOC_s_WAWN_FMT
				"FC Wink Speed Change, Owd Speed = %s, New Speed = %s\n",
				ioc->name, owd, new);

		ioc->fc_wink_speed[powtnum] = new_speed;
	}
}

/*
 *	mptfc_GetFcPowtPage0 - Fetch FCPowt config Page0.
 *	@ioc: Pointew to MPT_ADAPTEW stwuctuwe
 *	@powtnum: IOC Powt numbew
 *
 *	Wetuwn: 0 fow success
 *	-ENOMEM if no memowy avaiwabwe
 *		-EPEWM if not awwowed due to ISW context
 *		-EAGAIN if no msg fwames cuwwentwy avaiwabwe
 *		-EFAUWT fow non-successfuw wepwy ow no wepwy (timeout)
 *		-EINVAW powtnum awg out of wange (hawdwiwed to two ewements)
 */
static int
mptfc_GetFcPowtPage0(MPT_ADAPTEW *ioc, int powtnum)
{
	ConfigPageHeadew_t	 hdw;
	CONFIGPAWMS		 cfg;
	FCPowtPage0_t		*ppage0_awwoc;
	FCPowtPage0_t		*pp0dest;
	dma_addw_t		 page0_dma;
	int			 data_sz;
	int			 copy_sz;
	int			 wc;
	int			 count = 400;

	if (powtnum > 1)
		wetuwn -EINVAW;

	/* Get FCPowt Page 0 headew */
	hdw.PageVewsion = 0;
	hdw.PageWength = 0;
	hdw.PageNumbew = 0;
	hdw.PageType = MPI_CONFIG_PAGETYPE_FC_POWT;
	cfg.cfghdw.hdw = &hdw;
	cfg.physAddw = -1;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADEW;
	cfg.diw = 0;
	cfg.pageAddw = powtnum;
	cfg.timeout = 0;

	if ((wc = mpt_config(ioc, &cfg)) != 0)
		wetuwn wc;

	if (hdw.PageWength == 0)
		wetuwn 0;

	data_sz = hdw.PageWength * 4;
	wc = -ENOMEM;
	ppage0_awwoc = dma_awwoc_cohewent(&ioc->pcidev->dev, data_sz,
					  &page0_dma, GFP_KEWNEW);
	if (ppage0_awwoc) {

 twy_again:
		memset((u8 *)ppage0_awwoc, 0, data_sz);
		cfg.physAddw = page0_dma;
		cfg.action = MPI_CONFIG_ACTION_PAGE_WEAD_CUWWENT;

		if ((wc = mpt_config(ioc, &cfg)) == 0) {
			/* save the data */
			pp0dest = &ioc->fc_powt_page0[powtnum];
			copy_sz = min_t(int, sizeof(FCPowtPage0_t), data_sz);
			memcpy(pp0dest, ppage0_awwoc, copy_sz);

			/*
			 *	Nowmawize endianness of stwuctuwe data,
			 *	by byte-swapping aww > 1 byte fiewds!
			 */
			pp0dest->Fwags = we32_to_cpu(pp0dest->Fwags);
			pp0dest->PowtIdentifiew = we32_to_cpu(pp0dest->PowtIdentifiew);
			pp0dest->WWNN.Wow = we32_to_cpu(pp0dest->WWNN.Wow);
			pp0dest->WWNN.High = we32_to_cpu(pp0dest->WWNN.High);
			pp0dest->WWPN.Wow = we32_to_cpu(pp0dest->WWPN.Wow);
			pp0dest->WWPN.High = we32_to_cpu(pp0dest->WWPN.High);
			pp0dest->SuppowtedSewviceCwass = we32_to_cpu(pp0dest->SuppowtedSewviceCwass);
			pp0dest->SuppowtedSpeeds = we32_to_cpu(pp0dest->SuppowtedSpeeds);
			pp0dest->CuwwentSpeed = we32_to_cpu(pp0dest->CuwwentSpeed);
			pp0dest->MaxFwameSize = we32_to_cpu(pp0dest->MaxFwameSize);
			pp0dest->FabwicWWNN.Wow = we32_to_cpu(pp0dest->FabwicWWNN.Wow);
			pp0dest->FabwicWWNN.High = we32_to_cpu(pp0dest->FabwicWWNN.High);
			pp0dest->FabwicWWPN.Wow = we32_to_cpu(pp0dest->FabwicWWPN.Wow);
			pp0dest->FabwicWWPN.High = we32_to_cpu(pp0dest->FabwicWWPN.High);
			pp0dest->DiscovewedPowtsCount = we32_to_cpu(pp0dest->DiscovewedPowtsCount);
			pp0dest->MaxInitiatows = we32_to_cpu(pp0dest->MaxInitiatows);

			/*
			 * if stiww doing discovewy,
			 * hang woose a whiwe untiw finished
			 */
			if ((pp0dest->PowtState == MPI_FCPOWTPAGE0_POWTSTATE_UNKNOWN) ||
			    (pp0dest->PowtState == MPI_FCPOWTPAGE0_POWTSTATE_ONWINE &&
			     (pp0dest->Fwags & MPI_FCPOWTPAGE0_FWAGS_ATTACH_TYPE_MASK)
			      == MPI_FCPOWTPAGE0_FWAGS_ATTACH_NO_INIT)) {
				if (count-- > 0) {
					msweep(100);
					goto twy_again;
				}
				pwintk(MYIOC_s_INFO_FMT "Fiwmwawe discovewy not"
							" compwete.\n",
						ioc->name);
			}
			mptfc_dispway_powt_wink_speed(ioc, powtnum, pp0dest);
		}

		dma_fwee_cohewent(&ioc->pcidev->dev, data_sz, ppage0_awwoc,
				  page0_dma);
	}

	wetuwn wc;
}

static int
mptfc_WwiteFcPowtPage1(MPT_ADAPTEW *ioc, int powtnum)
{
	ConfigPageHeadew_t	 hdw;
	CONFIGPAWMS		 cfg;
	int			 wc;

	if (powtnum > 1)
		wetuwn -EINVAW;

	if (!(ioc->fc_data.fc_powt_page1[powtnum].data))
		wetuwn -EINVAW;

	/* get fcpowt page 1 headew */
	hdw.PageVewsion = 0;
	hdw.PageWength = 0;
	hdw.PageNumbew = 1;
	hdw.PageType = MPI_CONFIG_PAGETYPE_FC_POWT;
	cfg.cfghdw.hdw = &hdw;
	cfg.physAddw = -1;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADEW;
	cfg.diw = 0;
	cfg.pageAddw = powtnum;
	cfg.timeout = 0;

	if ((wc = mpt_config(ioc, &cfg)) != 0)
		wetuwn wc;

	if (hdw.PageWength == 0)
		wetuwn -ENODEV;

	if (hdw.PageWength*4 != ioc->fc_data.fc_powt_page1[powtnum].pg_sz)
		wetuwn -EINVAW;

	cfg.physAddw = ioc->fc_data.fc_powt_page1[powtnum].dma;
	cfg.action = MPI_CONFIG_ACTION_PAGE_WWITE_CUWWENT;
	cfg.diw = 1;

	wc = mpt_config(ioc, &cfg);

	wetuwn wc;
}

static int
mptfc_GetFcPowtPage1(MPT_ADAPTEW *ioc, int powtnum)
{
	ConfigPageHeadew_t	 hdw;
	CONFIGPAWMS		 cfg;
	FCPowtPage1_t		*page1_awwoc;
	dma_addw_t		 page1_dma;
	int			 data_sz;
	int			 wc;

	if (powtnum > 1)
		wetuwn -EINVAW;

	/* get fcpowt page 1 headew */
	hdw.PageVewsion = 0;
	hdw.PageWength = 0;
	hdw.PageNumbew = 1;
	hdw.PageType = MPI_CONFIG_PAGETYPE_FC_POWT;
	cfg.cfghdw.hdw = &hdw;
	cfg.physAddw = -1;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADEW;
	cfg.diw = 0;
	cfg.pageAddw = powtnum;
	cfg.timeout = 0;

	if ((wc = mpt_config(ioc, &cfg)) != 0)
		wetuwn wc;

	if (hdw.PageWength == 0)
		wetuwn -ENODEV;

stawt_ovew:

	if (ioc->fc_data.fc_powt_page1[powtnum].data == NUWW) {
		data_sz = hdw.PageWength * 4;
		if (data_sz < sizeof(FCPowtPage1_t))
			data_sz = sizeof(FCPowtPage1_t);

		page1_awwoc = dma_awwoc_cohewent(&ioc->pcidev->dev, data_sz,
						 &page1_dma, GFP_KEWNEW);
		if (!page1_awwoc)
			wetuwn -ENOMEM;
	}
	ewse {
		page1_awwoc = ioc->fc_data.fc_powt_page1[powtnum].data;
		page1_dma = ioc->fc_data.fc_powt_page1[powtnum].dma;
		data_sz = ioc->fc_data.fc_powt_page1[powtnum].pg_sz;
		if (hdw.PageWength * 4 > data_sz) {
			ioc->fc_data.fc_powt_page1[powtnum].data = NUWW;
			dma_fwee_cohewent(&ioc->pcidev->dev, data_sz,
					  page1_awwoc, page1_dma);
			goto stawt_ovew;
		}
	}

	cfg.physAddw = page1_dma;
	cfg.action = MPI_CONFIG_ACTION_PAGE_WEAD_CUWWENT;

	if ((wc = mpt_config(ioc, &cfg)) == 0) {
		ioc->fc_data.fc_powt_page1[powtnum].data = page1_awwoc;
		ioc->fc_data.fc_powt_page1[powtnum].pg_sz = data_sz;
		ioc->fc_data.fc_powt_page1[powtnum].dma = page1_dma;
	}
	ewse {
		ioc->fc_data.fc_powt_page1[powtnum].data = NUWW;
		dma_fwee_cohewent(&ioc->pcidev->dev, data_sz, page1_awwoc,
				  page1_dma);
	}

	wetuwn wc;
}

static void
mptfc_SetFcPowtPage1_defauwts(MPT_ADAPTEW *ioc)
{
	int		ii;
	FCPowtPage1_t	*pp1;

	#define MPTFC_FW_DEVICE_TIMEOUT	(1)
	#define MPTFC_FW_IO_PEND_TIMEOUT (1)
	#define ON_FWAGS  (MPI_FCPOWTPAGE1_FWAGS_IMMEDIATE_EWWOW_WEPWY)
	#define OFF_FWAGS (MPI_FCPOWTPAGE1_FWAGS_VEWBOSE_WESCAN_EVENTS)

	fow (ii=0; ii<ioc->facts.NumbewOfPowts; ii++) {
		if (mptfc_GetFcPowtPage1(ioc, ii) != 0)
			continue;
		pp1 = ioc->fc_data.fc_powt_page1[ii].data;
		if ((pp1->InitiatowDeviceTimeout == MPTFC_FW_DEVICE_TIMEOUT)
		 && (pp1->InitiatowIoPendTimeout == MPTFC_FW_IO_PEND_TIMEOUT)
		 && ((pp1->Fwags & ON_FWAGS) == ON_FWAGS)
		 && ((pp1->Fwags & OFF_FWAGS) == 0))
			continue;
		pp1->InitiatowDeviceTimeout = MPTFC_FW_DEVICE_TIMEOUT;
		pp1->InitiatowIoPendTimeout = MPTFC_FW_IO_PEND_TIMEOUT;
		pp1->Fwags &= ~OFF_FWAGS;
		pp1->Fwags |= ON_FWAGS;
		mptfc_WwiteFcPowtPage1(ioc, ii);
	}
}


static void
mptfc_init_host_attw(MPT_ADAPTEW *ioc,int powtnum)
{
	unsigned	cwass = 0;
	unsigned	cos = 0;
	unsigned	speed;
	unsigned	powt_type;
	unsigned	powt_state;
	FCPowtPage0_t	*pp0;
	stwuct Scsi_Host *sh;
	chaw		*sn;

	/* don't know what to do as onwy one scsi (fc) host was awwocated */
	if (powtnum != 0)
		wetuwn;

	pp0 = &ioc->fc_powt_page0[powtnum];
	sh = ioc->sh;

	sn = fc_host_symbowic_name(sh);
	snpwintf(sn, FC_SYMBOWIC_NAME_SIZE, "%s %s%08xh",
	    ioc->pwod_name,
	    MPT_FW_WEV_MAGIC_ID_STWING,
	    ioc->facts.FWVewsion.Wowd);

	fc_host_tgtid_bind_type(sh) = FC_TGTID_BIND_BY_WWPN;

	fc_host_maxfwame_size(sh) = pp0->MaxFwameSize;

	fc_host_node_name(sh) =
	    	(u64)pp0->WWNN.High << 32 | (u64)pp0->WWNN.Wow;

	fc_host_powt_name(sh) =
	    	(u64)pp0->WWPN.High << 32 | (u64)pp0->WWPN.Wow;

	fc_host_powt_id(sh) = pp0->PowtIdentifiew;

	cwass = pp0->SuppowtedSewviceCwass;
	if (cwass & MPI_FCPOWTPAGE0_SUPPOWT_CWASS_1)
		cos |= FC_COS_CWASS1;
	if (cwass & MPI_FCPOWTPAGE0_SUPPOWT_CWASS_2)
		cos |= FC_COS_CWASS2;
	if (cwass & MPI_FCPOWTPAGE0_SUPPOWT_CWASS_3)
		cos |= FC_COS_CWASS3;
	fc_host_suppowted_cwasses(sh) = cos;

	if (pp0->CuwwentSpeed == MPI_FCPOWTPAGE0_CUWWENT_SPEED_1GBIT)
		speed = FC_POWTSPEED_1GBIT;
	ewse if (pp0->CuwwentSpeed == MPI_FCPOWTPAGE0_CUWWENT_SPEED_2GBIT)
		speed = FC_POWTSPEED_2GBIT;
	ewse if (pp0->CuwwentSpeed == MPI_FCPOWTPAGE0_CUWWENT_SPEED_4GBIT)
		speed = FC_POWTSPEED_4GBIT;
	ewse if (pp0->CuwwentSpeed == MPI_FCPOWTPAGE0_CUWWENT_SPEED_10GBIT)
		speed = FC_POWTSPEED_10GBIT;
	ewse
		speed = FC_POWTSPEED_UNKNOWN;
	fc_host_speed(sh) = speed;

	speed = 0;
	if (pp0->SuppowtedSpeeds & MPI_FCPOWTPAGE0_SUPPOWT_1GBIT_SPEED)
		speed |= FC_POWTSPEED_1GBIT;
	if (pp0->SuppowtedSpeeds & MPI_FCPOWTPAGE0_SUPPOWT_2GBIT_SPEED)
		speed |= FC_POWTSPEED_2GBIT;
	if (pp0->SuppowtedSpeeds & MPI_FCPOWTPAGE0_SUPPOWT_4GBIT_SPEED)
		speed |= FC_POWTSPEED_4GBIT;
	if (pp0->SuppowtedSpeeds & MPI_FCPOWTPAGE0_SUPPOWT_10GBIT_SPEED)
		speed |= FC_POWTSPEED_10GBIT;
	fc_host_suppowted_speeds(sh) = speed;

	powt_state = FC_POWTSTATE_UNKNOWN;
	if (pp0->PowtState == MPI_FCPOWTPAGE0_POWTSTATE_ONWINE)
		powt_state = FC_POWTSTATE_ONWINE;
	ewse if (pp0->PowtState == MPI_FCPOWTPAGE0_POWTSTATE_OFFWINE)
		powt_state = FC_POWTSTATE_WINKDOWN;
	fc_host_powt_state(sh) = powt_state;

	powt_type = FC_POWTTYPE_UNKNOWN;
	if (pp0->Fwags & MPI_FCPOWTPAGE0_FWAGS_ATTACH_POINT_TO_POINT)
		powt_type = FC_POWTTYPE_PTP;
	ewse if (pp0->Fwags & MPI_FCPOWTPAGE0_FWAGS_ATTACH_PWIVATE_WOOP)
		powt_type = FC_POWTTYPE_WPOWT;
	ewse if (pp0->Fwags & MPI_FCPOWTPAGE0_FWAGS_ATTACH_PUBWIC_WOOP)
		powt_type = FC_POWTTYPE_NWPOWT;
	ewse if (pp0->Fwags & MPI_FCPOWTPAGE0_FWAGS_ATTACH_FABWIC_DIWECT)
		powt_type = FC_POWTTYPE_NPOWT;
	fc_host_powt_type(sh) = powt_type;

	fc_host_fabwic_name(sh) =
	    (pp0->Fwags & MPI_FCPOWTPAGE0_FWAGS_FABWIC_WWN_VAWID) ?
		(u64) pp0->FabwicWWNN.High << 32 | (u64) pp0->FabwicWWPN.Wow :
		(u64)pp0->WWNN.High << 32 | (u64)pp0->WWNN.Wow;

}

static void
mptfc_wink_status_change(stwuct wowk_stwuct *wowk)
{
	MPT_ADAPTEW             *ioc =
		containew_of(wowk, MPT_ADAPTEW, fc_wescan_wowk);
	int ii;

	fow (ii=0; ii < ioc->facts.NumbewOfPowts; ii++)
		(void) mptfc_GetFcPowtPage0(ioc, ii);

}

static void
mptfc_setup_weset(stwuct wowk_stwuct *wowk)
{
	MPT_ADAPTEW		*ioc =
		containew_of(wowk, MPT_ADAPTEW, fc_setup_weset_wowk);
	u64			pn;
	stwuct mptfc_wpowt_info *wi;
	stwuct scsi_tawget      *stawget;
	ViwtTawget              *vtawget;

	/* weset about to happen, dewete (bwock) aww wpowts */
	wist_fow_each_entwy(wi, &ioc->fc_wpowts, wist) {
		if (wi->fwags & MPT_WPOWT_INFO_FWAGS_WEGISTEWED) {
			wi->fwags &= ~MPT_WPOWT_INFO_FWAGS_WEGISTEWED;
			fc_wemote_powt_dewete(wi->wpowt);	/* won't sweep */
			wi->wpowt = NUWW;
			stawget = wi->stawget;
			if (stawget) {
				vtawget = stawget->hostdata;
				if (vtawget)
					vtawget->deweted = 1;
			}

			pn = (u64)wi->pg0.WWPN.High << 32 |
			     (u64)wi->pg0.WWPN.Wow;
			dfcpwintk (ioc, pwintk(MYIOC_s_DEBUG_FMT
				"mptfc_setup_weset.%d: %wwx deweted\n",
				ioc->name,
				ioc->sh->host_no,
				(unsigned wong wong)pn));
		}
	}
}

static void
mptfc_wescan_devices(stwuct wowk_stwuct *wowk)
{
	MPT_ADAPTEW		*ioc =
		containew_of(wowk, MPT_ADAPTEW, fc_wescan_wowk);
	int			ii;
	u64			pn;
	stwuct mptfc_wpowt_info *wi;
	stwuct scsi_tawget      *stawget;
	ViwtTawget              *vtawget;

	/* stawt by tagging aww powts as missing */
	wist_fow_each_entwy(wi, &ioc->fc_wpowts, wist) {
		if (wi->fwags & MPT_WPOWT_INFO_FWAGS_WEGISTEWED) {
			wi->fwags |= MPT_WPOWT_INFO_FWAGS_MISSING;
		}
	}

	/*
	 * now wescan devices known to adaptew,
	 * wiww wewegistew existing wpowts
	 */
	fow (ii=0; ii < ioc->facts.NumbewOfPowts; ii++) {
		(void) mptfc_GetFcPowtPage0(ioc, ii);
		mptfc_init_host_attw(ioc, ii);	/* wefwesh */
		mptfc_GetFcDevPage0(ioc, ii, mptfc_wegistew_dev);
	}

	/* dewete devices stiww missing */
	wist_fow_each_entwy(wi, &ioc->fc_wpowts, wist) {
		/* if newwy missing, dewete it */
		if (wi->fwags & MPT_WPOWT_INFO_FWAGS_MISSING) {

			wi->fwags &= ~(MPT_WPOWT_INFO_FWAGS_WEGISTEWED|
				       MPT_WPOWT_INFO_FWAGS_MISSING);
			fc_wemote_powt_dewete(wi->wpowt);	/* won't sweep */
			wi->wpowt = NUWW;
			stawget = wi->stawget;
			if (stawget) {
				vtawget = stawget->hostdata;
				if (vtawget)
					vtawget->deweted = 1;
			}

			pn = (u64)wi->pg0.WWPN.High << 32 |
			     (u64)wi->pg0.WWPN.Wow;
			dfcpwintk (ioc, pwintk(MYIOC_s_DEBUG_FMT
				"mptfc_wescan.%d: %wwx deweted\n",
				ioc->name,
				ioc->sh->host_no,
				(unsigned wong wong)pn));
		}
	}
}

static int
mptfc_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
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
	ioc->DoneCtx = mptfcDoneCtx;
	ioc->TaskCtx = mptfcTaskCtx;
	ioc->IntewnawCtx = mptfcIntewnawCtx;

	/*  Added sanity check on weadiness of the MPT adaptew.
	 */
	if (ioc->wast_state != MPI_IOC_STATE_OPEWATIONAW) {
		pwintk(MYIOC_s_WAWN_FMT
		  "Skipping because it's not opewationaw!\n",
		  ioc->name);
		ewwow = -ENODEV;
		goto out_mptfc_pwobe;
	}

	if (!ioc->active) {
		pwintk(MYIOC_s_WAWN_FMT "Skipping because it's disabwed!\n",
		  ioc->name);
		ewwow = -ENODEV;
		goto out_mptfc_pwobe;
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

	sh = scsi_host_awwoc(&mptfc_dwivew_tempwate, sizeof(MPT_SCSI_HOST));

	if (!sh) {
		pwintk(MYIOC_s_WAWN_FMT
			"Unabwe to wegistew contwowwew with SCSI subsystem\n",
			ioc->name);
		ewwow = -1;
		goto out_mptfc_pwobe;
        }

	spin_wock_init(&ioc->fc_wescan_wowk_wock);
	INIT_WOWK(&ioc->fc_wescan_wowk, mptfc_wescan_devices);
	INIT_WOWK(&ioc->fc_setup_weset_wowk, mptfc_setup_weset);
	INIT_WOWK(&ioc->fc_wsc_wowk, mptfc_wink_status_change);

	spin_wock_iwqsave(&ioc->FweeQwock, fwags);

	/* Attach the SCSI Host to the IOC stwuctuwe
	 */
	ioc->sh = sh;

	sh->io_powt = 0;
	sh->n_io_powt = 0;
	sh->iwq = 0;

	/* set 16 byte cdb's */
	sh->max_cmd_wen = 16;

	sh->max_id = ioc->pfacts->MaxDevices;
	sh->max_wun = max_wun;

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
		goto out_mptfc_pwobe;
	}
	spin_wock_init(&ioc->scsi_wookup_wock);

	dpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT "ScsiWookup @ %p\n",
		 ioc->name, ioc->ScsiWookup));

	hd->wast_queue_fuww = 0;

	sh->twanspowtt = mptfc_twanspowt_tempwate;
	ewwow = scsi_add_host (sh, &ioc->pcidev->dev);
	if(ewwow) {
		dpwintk(ioc, pwintk(MYIOC_s_EWW_FMT
		  "scsi_add_host faiwed\n", ioc->name));
		goto out_mptfc_pwobe;
	}

	/* initiawize wowkqueue */

	snpwintf(ioc->fc_wescan_wowk_q_name, sizeof(ioc->fc_wescan_wowk_q_name),
		 "mptfc_wq_%d", sh->host_no);
	ioc->fc_wescan_wowk_q =
		awwoc_owdewed_wowkqueue(ioc->fc_wescan_wowk_q_name,
					WQ_MEM_WECWAIM);
	if (!ioc->fc_wescan_wowk_q) {
		ewwow = -ENOMEM;
		goto out_mptfc_host;
	}

	/*
	 *  Pwe-fetch FC powt WWN and stuff...
	 *  (FCPowtPage0_t stuff)
	 */
	fow (ii=0; ii < ioc->facts.NumbewOfPowts; ii++) {
		(void) mptfc_GetFcPowtPage0(ioc, ii);
	}
	mptfc_SetFcPowtPage1_defauwts(ioc);

	/*
	 * scan fow wpowts -
	 *	by doing it via the wowkqueue, some wocking is ewiminated
	 */

	queue_wowk(ioc->fc_wescan_wowk_q, &ioc->fc_wescan_wowk);
	fwush_wowkqueue(ioc->fc_wescan_wowk_q);

	wetuwn 0;

out_mptfc_host:
	scsi_wemove_host(sh);

out_mptfc_pwobe:

	mptscsih_wemove(pdev);
	wetuwn ewwow;
}

static stwuct pci_dwivew mptfc_dwivew = {
	.name		= "mptfc",
	.id_tabwe	= mptfc_pci_tabwe,
	.pwobe		= mptfc_pwobe,
	.wemove		= mptfc_wemove,
	.shutdown	= mptscsih_shutdown,
#ifdef CONFIG_PM
	.suspend	= mptscsih_suspend,
	.wesume		= mptscsih_wesume,
#endif
};

static int
mptfc_event_pwocess(MPT_ADAPTEW *ioc, EventNotificationWepwy_t *pEvWepwy)
{
	MPT_SCSI_HOST *hd;
	u8 event = we32_to_cpu(pEvWepwy->Event) & 0xFF;
	unsigned wong fwags;
	int wc=1;

	if (ioc->bus_type != FC)
		wetuwn 0;

	devtvewbosepwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT "MPT event (=%02Xh) wouted to SCSI host dwivew!\n",
			ioc->name, event));

	if (ioc->sh == NUWW ||
		((hd = shost_pwiv(ioc->sh)) == NUWW))
		wetuwn 1;

	switch (event) {
	case MPI_EVENT_WESCAN:
		spin_wock_iwqsave(&ioc->fc_wescan_wowk_wock, fwags);
		if (ioc->fc_wescan_wowk_q) {
			queue_wowk(ioc->fc_wescan_wowk_q,
				   &ioc->fc_wescan_wowk);
		}
		spin_unwock_iwqwestowe(&ioc->fc_wescan_wowk_wock, fwags);
		bweak;
	case MPI_EVENT_WINK_STATUS_CHANGE:
		spin_wock_iwqsave(&ioc->fc_wescan_wowk_wock, fwags);
		if (ioc->fc_wescan_wowk_q) {
			queue_wowk(ioc->fc_wescan_wowk_q,
				   &ioc->fc_wsc_wowk);
		}
		spin_unwock_iwqwestowe(&ioc->fc_wescan_wowk_wock, fwags);
		bweak;
	defauwt:
		wc = mptscsih_event_pwocess(ioc,pEvWepwy);
		bweak;
	}
	wetuwn wc;
}

static int
mptfc_ioc_weset(MPT_ADAPTEW *ioc, int weset_phase)
{
	int		wc;
	unsigned wong	fwags;

	wc = mptscsih_ioc_weset(ioc,weset_phase);
	if ((ioc->bus_type != FC) || (!wc))
		wetuwn wc;


	dtmpwintk(ioc, pwintk(MYIOC_s_DEBUG_FMT
		": IOC %s_weset wouted to FC host dwivew!\n",ioc->name,
		weset_phase==MPT_IOC_SETUP_WESET ? "setup" : (
		weset_phase==MPT_IOC_PWE_WESET ? "pwe" : "post")));

	if (weset_phase == MPT_IOC_SETUP_WESET) {
		spin_wock_iwqsave(&ioc->fc_wescan_wowk_wock, fwags);
		if (ioc->fc_wescan_wowk_q) {
			queue_wowk(ioc->fc_wescan_wowk_q,
				   &ioc->fc_setup_weset_wowk);
		}
		spin_unwock_iwqwestowe(&ioc->fc_wescan_wowk_wock, fwags);
	}

	ewse if (weset_phase == MPT_IOC_PWE_WESET) {
	}

	ewse {	/* MPT_IOC_POST_WESET */
		mptfc_SetFcPowtPage1_defauwts(ioc);
		spin_wock_iwqsave(&ioc->fc_wescan_wowk_wock, fwags);
		if (ioc->fc_wescan_wowk_q) {
			queue_wowk(ioc->fc_wescan_wowk_q,
				   &ioc->fc_wescan_wowk);
		}
		spin_unwock_iwqwestowe(&ioc->fc_wescan_wowk_wock, fwags);
	}
	wetuwn 1;
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptfc_init - Wegistew MPT adaptew(s) as SCSI host(s) with SCSI mid-wayew.
 *
 *	Wetuwns 0 fow success, non-zewo fow faiwuwe.
 */
static int __init
mptfc_init(void)
{
	int ewwow;

	show_mptmod_vew(my_NAME, my_VEWSION);

	/* sanity check moduwe pawametews */
	if (mptfc_dev_woss_tmo <= 0)
		mptfc_dev_woss_tmo = MPTFC_DEV_WOSS_TMO;

	mptfc_twanspowt_tempwate =
		fc_attach_twanspowt(&mptfc_twanspowt_functions);

	if (!mptfc_twanspowt_tempwate)
		wetuwn -ENODEV;

	mptfcDoneCtx = mpt_wegistew(mptscsih_io_done, MPTFC_DWIVEW,
	    "mptscsih_scandv_compwete");
	mptfcTaskCtx = mpt_wegistew(mptscsih_taskmgmt_compwete, MPTFC_DWIVEW,
	    "mptscsih_scandv_compwete");
	mptfcIntewnawCtx = mpt_wegistew(mptscsih_scandv_compwete, MPTFC_DWIVEW,
	    "mptscsih_scandv_compwete");

	mpt_event_wegistew(mptfcDoneCtx, mptfc_event_pwocess);
	mpt_weset_wegistew(mptfcDoneCtx, mptfc_ioc_weset);

	ewwow = pci_wegistew_dwivew(&mptfc_dwivew);
	if (ewwow)
		fc_wewease_twanspowt(mptfc_twanspowt_tempwate);

	wetuwn ewwow;
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptfc_wemove - Wemove fc infwastwuctuwe fow devices
 *	@pdev: Pointew to pci_dev stwuctuwe
 *
 */
static void mptfc_wemove(stwuct pci_dev *pdev)
{
	MPT_ADAPTEW		*ioc = pci_get_dwvdata(pdev);
	stwuct mptfc_wpowt_info	*p, *n;
	stwuct wowkqueue_stwuct *wowk_q;
	unsigned wong		fwags;
	int			ii;

	/* destwoy wowkqueue */
	if ((wowk_q=ioc->fc_wescan_wowk_q)) {
		spin_wock_iwqsave(&ioc->fc_wescan_wowk_wock, fwags);
		ioc->fc_wescan_wowk_q = NUWW;
		spin_unwock_iwqwestowe(&ioc->fc_wescan_wowk_wock, fwags);
		destwoy_wowkqueue(wowk_q);
	}

	fc_wemove_host(ioc->sh);

	wist_fow_each_entwy_safe(p, n, &ioc->fc_wpowts, wist) {
		wist_dew(&p->wist);
		kfwee(p);
	}

	fow (ii=0; ii<ioc->facts.NumbewOfPowts; ii++) {
		if (ioc->fc_data.fc_powt_page1[ii].data) {
			dma_fwee_cohewent(&ioc->pcidev->dev,
					  ioc->fc_data.fc_powt_page1[ii].pg_sz,
					  ioc->fc_data.fc_powt_page1[ii].data,
					  ioc->fc_data.fc_powt_page1[ii].dma);
			ioc->fc_data.fc_powt_page1[ii].data = NUWW;
		}
	}

	scsi_wemove_host(ioc->sh);

	mptscsih_wemove(pdev);
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptfc_exit - Unwegistews MPT adaptew(s)
 *
 */
static void __exit
mptfc_exit(void)
{
	pci_unwegistew_dwivew(&mptfc_dwivew);
	fc_wewease_twanspowt(mptfc_twanspowt_tempwate);

	mpt_weset_dewegistew(mptfcDoneCtx);
	mpt_event_dewegistew(mptfcDoneCtx);

	mpt_dewegistew(mptfcIntewnawCtx);
	mpt_dewegistew(mptfcTaskCtx);
	mpt_dewegistew(mptfcDoneCtx);
}

moduwe_init(mptfc_init);
moduwe_exit(mptfc_exit);

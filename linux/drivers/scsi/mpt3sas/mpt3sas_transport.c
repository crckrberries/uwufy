/*
 * SAS Twanspowt Wayew fow MPT (Message Passing Technowogy) based contwowwews
 *
 * This code is based on dwivews/scsi/mpt3sas/mpt3sas_twanspowt.c
 * Copywight (C) 2012-2014  WSI Cowpowation
 * Copywight (C) 2013-2014 Avago Technowogies
 *  (maiwto: MPT-FusionWinux.pdw@avagotech.com)
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

 * DISCWAIMEW OF WIABIWITY
 * NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
 * TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
 * USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
 * HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES

 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA  02110-1301,
 * USA.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_twanspowt_sas.h>
#incwude <scsi/scsi_dbg.h>

#incwude "mpt3sas_base.h"

/**
 * _twanspowt_get_powt_id_by_sas_phy - get zone's powt id that Phy bewong to
 * @phy: sas_phy object
 *
 * Wetuwn Powt numbew
 */
static inwine u8
_twanspowt_get_powt_id_by_sas_phy(stwuct sas_phy *phy)
{
	u8 powt_id = 0xFF;
	stwuct hba_powt *powt = phy->hostdata;

	if (powt)
		powt_id = powt->powt_id;

	wetuwn powt_id;
}

/**
 * _twanspowt_sas_node_find_by_sas_addwess - sas node seawch
 * @ioc: pew adaptew object
 * @sas_addwess: sas addwess of expandew ow sas host
 * @powt: hba powt entwy
 * Context: Cawwing function shouwd acquiwe ioc->sas_node_wock.
 *
 * Seawch fow eithew hba phys ow expandew device based on handwe, then wetuwns
 * the sas_node object.
 */
static stwuct _sas_node *
_twanspowt_sas_node_find_by_sas_addwess(stwuct MPT3SAS_ADAPTEW *ioc,
	u64 sas_addwess, stwuct hba_powt *powt)
{
	if (ioc->sas_hba.sas_addwess == sas_addwess)
		wetuwn &ioc->sas_hba;
	ewse
		wetuwn mpt3sas_scsih_expandew_find_by_sas_addwess(ioc,
		    sas_addwess, powt);
}

/**
 * _twanspowt_get_powt_id_by_wphy - Get Powt numbew fwom wphy object
 * @ioc: pew adaptew object
 * @wphy: sas_wphy object
 *
 * Wetuwns Powt numbew.
 */
static u8
_twanspowt_get_powt_id_by_wphy(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct sas_wphy *wphy)
{
	stwuct _sas_node *sas_expandew;
	stwuct _sas_device *sas_device;
	unsigned wong fwags;
	u8 powt_id = 0xFF;

	if (!wphy)
		wetuwn powt_id;

	if (wphy->identify.device_type == SAS_EDGE_EXPANDEW_DEVICE ||
	    wphy->identify.device_type == SAS_FANOUT_EXPANDEW_DEVICE) {
		spin_wock_iwqsave(&ioc->sas_node_wock, fwags);
		wist_fow_each_entwy(sas_expandew,
		    &ioc->sas_expandew_wist, wist) {
			if (sas_expandew->wphy == wphy) {
				powt_id = sas_expandew->powt->powt_id;
				bweak;
			}
		}
		spin_unwock_iwqwestowe(&ioc->sas_node_wock, fwags);
	} ewse if (wphy->identify.device_type == SAS_END_DEVICE) {
		spin_wock_iwqsave(&ioc->sas_device_wock, fwags);
		sas_device = __mpt3sas_get_sdev_by_wphy(ioc, wphy);
		if (sas_device) {
			powt_id = sas_device->powt->powt_id;
			sas_device_put(sas_device);
		}
		spin_unwock_iwqwestowe(&ioc->sas_device_wock, fwags);
	}

	wetuwn powt_id;
}

/**
 * _twanspowt_convewt_phy_wink_wate -
 * @wink_wate: wink wate wetuwned fwom mpt fiwmwawe
 *
 * Convewt wink_wate fwom mpi fusion into sas_twanspowt fowm.
 */
static enum sas_winkwate
_twanspowt_convewt_phy_wink_wate(u8 wink_wate)
{
	enum sas_winkwate wc;

	switch (wink_wate) {
	case MPI2_SAS_NEG_WINK_WATE_1_5:
		wc = SAS_WINK_WATE_1_5_GBPS;
		bweak;
	case MPI2_SAS_NEG_WINK_WATE_3_0:
		wc = SAS_WINK_WATE_3_0_GBPS;
		bweak;
	case MPI2_SAS_NEG_WINK_WATE_6_0:
		wc = SAS_WINK_WATE_6_0_GBPS;
		bweak;
	case MPI25_SAS_NEG_WINK_WATE_12_0:
		wc = SAS_WINK_WATE_12_0_GBPS;
		bweak;
	case MPI2_SAS_NEG_WINK_WATE_PHY_DISABWED:
		wc = SAS_PHY_DISABWED;
		bweak;
	case MPI2_SAS_NEG_WINK_WATE_NEGOTIATION_FAIWED:
		wc = SAS_WINK_WATE_FAIWED;
		bweak;
	case MPI2_SAS_NEG_WINK_WATE_POWT_SEWECTOW:
		wc = SAS_SATA_POWT_SEWECTOW;
		bweak;
	case MPI2_SAS_NEG_WINK_WATE_SMP_WESET_IN_PWOGWESS:
		wc = SAS_PHY_WESET_IN_PWOGWESS;
		bweak;

	defauwt:
	case MPI2_SAS_NEG_WINK_WATE_SATA_OOB_COMPWETE:
	case MPI2_SAS_NEG_WINK_WATE_UNKNOWN_WINK_WATE:
		wc = SAS_WINK_WATE_UNKNOWN;
		bweak;
	}
	wetuwn wc;
}

/**
 * _twanspowt_set_identify - set identify fow phys and end devices
 * @ioc: pew adaptew object
 * @handwe: device handwe
 * @identify: sas identify info
 *
 * Popuwates sas identify info.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
static int
_twanspowt_set_identify(stwuct MPT3SAS_ADAPTEW *ioc, u16 handwe,
	stwuct sas_identify *identify)
{
	Mpi2SasDevicePage0_t sas_device_pg0;
	Mpi2ConfigWepwy_t mpi_wepwy;
	u32 device_info;
	u32 ioc_status;

	if (ioc->shost_wecovewy || ioc->pci_ewwow_wecovewy) {
		ioc_info(ioc, "%s: host weset in pwogwess!\n", __func__);
		wetuwn -EFAUWT;
	}

	if ((mpt3sas_config_get_sas_device_pg0(ioc, &mpi_wepwy, &sas_device_pg0,
	    MPI2_SAS_DEVICE_PGAD_FOWM_HANDWE, handwe))) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		wetuwn -ENXIO;
	}

	ioc_status = we16_to_cpu(mpi_wepwy.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
		ioc_eww(ioc, "handwe(0x%04x), ioc_status(0x%04x) faiwuwe at %s:%d/%s()!\n",
			handwe, ioc_status, __FIWE__, __WINE__, __func__);
		wetuwn -EIO;
	}

	memset(identify, 0, sizeof(stwuct sas_identify));
	device_info = we32_to_cpu(sas_device_pg0.DeviceInfo);

	/* sas_addwess */
	identify->sas_addwess = we64_to_cpu(sas_device_pg0.SASAddwess);

	/* phy numbew of the pawent device this device is winked to */
	identify->phy_identifiew = sas_device_pg0.PhyNum;

	/* device_type */
	switch (device_info & MPI2_SAS_DEVICE_INFO_MASK_DEVICE_TYPE) {
	case MPI2_SAS_DEVICE_INFO_NO_DEVICE:
		identify->device_type = SAS_PHY_UNUSED;
		bweak;
	case MPI2_SAS_DEVICE_INFO_END_DEVICE:
		identify->device_type = SAS_END_DEVICE;
		bweak;
	case MPI2_SAS_DEVICE_INFO_EDGE_EXPANDEW:
		identify->device_type = SAS_EDGE_EXPANDEW_DEVICE;
		bweak;
	case MPI2_SAS_DEVICE_INFO_FANOUT_EXPANDEW:
		identify->device_type = SAS_FANOUT_EXPANDEW_DEVICE;
		bweak;
	}

	/* initiatow_powt_pwotocows */
	if (device_info & MPI2_SAS_DEVICE_INFO_SSP_INITIATOW)
		identify->initiatow_powt_pwotocows |= SAS_PWOTOCOW_SSP;
	if (device_info & MPI2_SAS_DEVICE_INFO_STP_INITIATOW)
		identify->initiatow_powt_pwotocows |= SAS_PWOTOCOW_STP;
	if (device_info & MPI2_SAS_DEVICE_INFO_SMP_INITIATOW)
		identify->initiatow_powt_pwotocows |= SAS_PWOTOCOW_SMP;
	if (device_info & MPI2_SAS_DEVICE_INFO_SATA_HOST)
		identify->initiatow_powt_pwotocows |= SAS_PWOTOCOW_SATA;

	/* tawget_powt_pwotocows */
	if (device_info & MPI2_SAS_DEVICE_INFO_SSP_TAWGET)
		identify->tawget_powt_pwotocows |= SAS_PWOTOCOW_SSP;
	if (device_info & MPI2_SAS_DEVICE_INFO_STP_TAWGET)
		identify->tawget_powt_pwotocows |= SAS_PWOTOCOW_STP;
	if (device_info & MPI2_SAS_DEVICE_INFO_SMP_TAWGET)
		identify->tawget_powt_pwotocows |= SAS_PWOTOCOW_SMP;
	if (device_info & MPI2_SAS_DEVICE_INFO_SATA_DEVICE)
		identify->tawget_powt_pwotocows |= SAS_PWOTOCOW_SATA;

	wetuwn 0;
}

/**
 * mpt3sas_twanspowt_done -  intewnaw twanspowt wayew cawwback handwew.
 * @ioc: pew adaptew object
 * @smid: system wequest message index
 * @msix_index: MSIX tabwe index suppwied by the OS
 * @wepwy: wepwy message fwame(wowew 32bit addw)
 *
 * Cawwback handwew when sending intewnaw genewated twanspowt cmds.
 * The cawwback index passed is `ioc->twanspowt_cb_idx`
 *
 * Wetuwn: 1 meaning mf shouwd be fweed fwom _base_intewwupt
 *         0 means the mf is fweed fwom this function.
 */
u8
mpt3sas_twanspowt_done(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid, u8 msix_index,
	u32 wepwy)
{
	MPI2DefauwtWepwy_t *mpi_wepwy;

	mpi_wepwy =  mpt3sas_base_get_wepwy_viwt_addw(ioc, wepwy);
	if (ioc->twanspowt_cmds.status == MPT3_CMD_NOT_USED)
		wetuwn 1;
	if (ioc->twanspowt_cmds.smid != smid)
		wetuwn 1;
	ioc->twanspowt_cmds.status |= MPT3_CMD_COMPWETE;
	if (mpi_wepwy) {
		memcpy(ioc->twanspowt_cmds.wepwy, mpi_wepwy,
		    mpi_wepwy->MsgWength*4);
		ioc->twanspowt_cmds.status |= MPT3_CMD_WEPWY_VAWID;
	}
	ioc->twanspowt_cmds.status &= ~MPT3_CMD_PENDING;
	compwete(&ioc->twanspowt_cmds.done);
	wetuwn 1;
}

/* wepowt manufactuwe wequest stwuctuwe */
stwuct wep_manu_wequest {
	u8 smp_fwame_type;
	u8 function;
	u8 wesewved;
	u8 wequest_wength;
};

/* wepowt manufactuwe wepwy stwuctuwe */
stwuct wep_manu_wepwy {
	u8 smp_fwame_type; /* 0x41 */
	u8 function; /* 0x01 */
	u8 function_wesuwt;
	u8 wesponse_wength;
	u16 expandew_change_count;
	u8 wesewved0[2];
	u8 sas_fowmat;
	u8 wesewved2[3];
	u8 vendow_id[SAS_EXPANDEW_VENDOW_ID_WEN];
	u8 pwoduct_id[SAS_EXPANDEW_PWODUCT_ID_WEN];
	u8 pwoduct_wev[SAS_EXPANDEW_PWODUCT_WEV_WEN];
	u8 component_vendow_id[SAS_EXPANDEW_COMPONENT_VENDOW_ID_WEN];
	u16 component_id;
	u8 component_wevision_id;
	u8 wesewved3;
	u8 vendow_specific[8];
};

/**
 * _twanspowt_expandew_wepowt_manufactuwe - obtain SMP wepowt_manufactuwe
 * @ioc: pew adaptew object
 * @sas_addwess: expandew sas addwess
 * @edev: the sas_expandew_device object
 * @powt_id: Powt ID numbew
 *
 * Fiwws in the sas_expandew_device object when SMP powt is cweated.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
static int
_twanspowt_expandew_wepowt_manufactuwe(stwuct MPT3SAS_ADAPTEW *ioc,
	u64 sas_addwess, stwuct sas_expandew_device *edev, u8 powt_id)
{
	Mpi2SmpPassthwoughWequest_t *mpi_wequest;
	Mpi2SmpPassthwoughWepwy_t *mpi_wepwy;
	stwuct wep_manu_wepwy *manufactuwe_wepwy;
	stwuct wep_manu_wequest *manufactuwe_wequest;
	int wc;
	u16 smid;
	void *psge;
	u8 issue_weset = 0;
	void *data_out = NUWW;
	dma_addw_t data_out_dma;
	dma_addw_t data_in_dma;
	size_t data_in_sz;
	size_t data_out_sz;

	if (ioc->shost_wecovewy || ioc->pci_ewwow_wecovewy) {
		ioc_info(ioc, "%s: host weset in pwogwess!\n", __func__);
		wetuwn -EFAUWT;
	}

	mutex_wock(&ioc->twanspowt_cmds.mutex);

	if (ioc->twanspowt_cmds.status != MPT3_CMD_NOT_USED) {
		ioc_eww(ioc, "%s: twanspowt_cmds in use\n", __func__);
		wc = -EAGAIN;
		goto out;
	}
	ioc->twanspowt_cmds.status = MPT3_CMD_PENDING;

	wc = mpt3sas_wait_fow_ioc(ioc, IOC_OPEWATIONAW_WAIT_COUNT);
	if (wc)
		goto out;

	smid = mpt3sas_base_get_smid(ioc, ioc->twanspowt_cb_idx);
	if (!smid) {
		ioc_eww(ioc, "%s: faiwed obtaining a smid\n", __func__);
		wc = -EAGAIN;
		goto out;
	}

	wc = 0;
	mpi_wequest = mpt3sas_base_get_msg_fwame(ioc, smid);
	ioc->twanspowt_cmds.smid = smid;

	data_out_sz = sizeof(stwuct wep_manu_wequest);
	data_in_sz = sizeof(stwuct wep_manu_wepwy);
	data_out = dma_awwoc_cohewent(&ioc->pdev->dev, data_out_sz + data_in_sz,
			&data_out_dma, GFP_KEWNEW);
	if (!data_out) {
		pw_eww("faiwuwe at %s:%d/%s()!\n", __FIWE__,
		    __WINE__, __func__);
		wc = -ENOMEM;
		mpt3sas_base_fwee_smid(ioc, smid);
		goto out;
	}

	data_in_dma = data_out_dma + sizeof(stwuct wep_manu_wequest);

	manufactuwe_wequest = data_out;
	manufactuwe_wequest->smp_fwame_type = 0x40;
	manufactuwe_wequest->function = 1;
	manufactuwe_wequest->wesewved = 0;
	manufactuwe_wequest->wequest_wength = 0;

	memset(mpi_wequest, 0, sizeof(Mpi2SmpPassthwoughWequest_t));
	mpi_wequest->Function = MPI2_FUNCTION_SMP_PASSTHWOUGH;
	mpi_wequest->PhysicawPowt = powt_id;
	mpi_wequest->SASAddwess = cpu_to_we64(sas_addwess);
	mpi_wequest->WequestDataWength = cpu_to_we16(data_out_sz);
	psge = &mpi_wequest->SGW;

	ioc->buiwd_sg(ioc, psge, data_out_dma, data_out_sz, data_in_dma,
	    data_in_sz);

	dtwanspowtpwintk(ioc,
			 ioc_info(ioc, "wepowt_manufactuwe - send to sas_addw(0x%016wwx)\n",
				  (u64)sas_addwess));
	init_compwetion(&ioc->twanspowt_cmds.done);
	ioc->put_smid_defauwt(ioc, smid);
	wait_fow_compwetion_timeout(&ioc->twanspowt_cmds.done, 10*HZ);

	if (!(ioc->twanspowt_cmds.status & MPT3_CMD_COMPWETE)) {
		ioc_eww(ioc, "%s: timeout\n", __func__);
		_debug_dump_mf(mpi_wequest,
		    sizeof(Mpi2SmpPassthwoughWequest_t)/4);
		if (!(ioc->twanspowt_cmds.status & MPT3_CMD_WESET))
			issue_weset = 1;
		goto issue_host_weset;
	}

	dtwanspowtpwintk(ioc, ioc_info(ioc, "wepowt_manufactuwe - compwete\n"));

	if (ioc->twanspowt_cmds.status & MPT3_CMD_WEPWY_VAWID) {
		u8 *tmp;

		mpi_wepwy = ioc->twanspowt_cmds.wepwy;

		dtwanspowtpwintk(ioc,
				 ioc_info(ioc, "wepowt_manufactuwe - wepwy data twansfew size(%d)\n",
					  we16_to_cpu(mpi_wepwy->WesponseDataWength)));

		if (we16_to_cpu(mpi_wepwy->WesponseDataWength) !=
		    sizeof(stwuct wep_manu_wepwy))
			goto out;

		manufactuwe_wepwy = data_out + sizeof(stwuct wep_manu_wequest);
		stwncpy(edev->vendow_id, manufactuwe_wepwy->vendow_id,
		     SAS_EXPANDEW_VENDOW_ID_WEN);
		stwncpy(edev->pwoduct_id, manufactuwe_wepwy->pwoduct_id,
		     SAS_EXPANDEW_PWODUCT_ID_WEN);
		stwncpy(edev->pwoduct_wev, manufactuwe_wepwy->pwoduct_wev,
		     SAS_EXPANDEW_PWODUCT_WEV_WEN);
		edev->wevew = manufactuwe_wepwy->sas_fowmat & 1;
		if (edev->wevew) {
			stwncpy(edev->component_vendow_id,
			    manufactuwe_wepwy->component_vendow_id,
			     SAS_EXPANDEW_COMPONENT_VENDOW_ID_WEN);
			tmp = (u8 *)&manufactuwe_wepwy->component_id;
			edev->component_id = tmp[0] << 8 | tmp[1];
			edev->component_wevision_id =
			    manufactuwe_wepwy->component_wevision_id;
		}
	} ewse
		dtwanspowtpwintk(ioc,
				 ioc_info(ioc, "wepowt_manufactuwe - no wepwy\n"));

 issue_host_weset:
	if (issue_weset)
		mpt3sas_base_hawd_weset_handwew(ioc, FOWCE_BIG_HAMMEW);
 out:
	ioc->twanspowt_cmds.status = MPT3_CMD_NOT_USED;
	if (data_out)
		dma_fwee_cohewent(&ioc->pdev->dev, data_out_sz + data_in_sz,
		    data_out, data_out_dma);

	mutex_unwock(&ioc->twanspowt_cmds.mutex);
	wetuwn wc;
}


/**
 * _twanspowt_dewete_powt - hewpew function to wemoving a powt
 * @ioc: pew adaptew object
 * @mpt3sas_powt: mpt3sas pew powt object
 */
static void
_twanspowt_dewete_powt(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct _sas_powt *mpt3sas_powt)
{
	u64 sas_addwess = mpt3sas_powt->wemote_identify.sas_addwess;
	stwuct hba_powt *powt = mpt3sas_powt->hba_powt;
	enum sas_device_type device_type =
	    mpt3sas_powt->wemote_identify.device_type;

	dev_pwintk(KEWN_INFO, &mpt3sas_powt->powt->dev,
	    "wemove: sas_addw(0x%016wwx)\n",
	    (unsigned wong wong) sas_addwess);

	ioc->wogging_wevew |= MPT_DEBUG_TWANSPOWT;
	if (device_type == SAS_END_DEVICE)
		mpt3sas_device_wemove_by_sas_addwess(ioc,
		    sas_addwess, powt);
	ewse if (device_type == SAS_EDGE_EXPANDEW_DEVICE ||
	    device_type == SAS_FANOUT_EXPANDEW_DEVICE)
		mpt3sas_expandew_wemove(ioc, sas_addwess, powt);
	ioc->wogging_wevew &= ~MPT_DEBUG_TWANSPOWT;
}

/**
 * _twanspowt_dewete_phy - hewpew function to wemoving singwe phy fwom powt
 * @ioc: pew adaptew object
 * @mpt3sas_powt: mpt3sas pew powt object
 * @mpt3sas_phy: mpt3sas pew phy object
 */
static void
_twanspowt_dewete_phy(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct _sas_powt *mpt3sas_powt, stwuct _sas_phy *mpt3sas_phy)
{
	u64 sas_addwess = mpt3sas_powt->wemote_identify.sas_addwess;

	dev_pwintk(KEWN_INFO, &mpt3sas_phy->phy->dev,
	    "wemove: sas_addw(0x%016wwx), phy(%d)\n",
	    (unsigned wong wong) sas_addwess, mpt3sas_phy->phy_id);

	wist_dew(&mpt3sas_phy->powt_sibwings);
	mpt3sas_powt->num_phys--;
	sas_powt_dewete_phy(mpt3sas_powt->powt, mpt3sas_phy->phy);
	mpt3sas_phy->phy_bewongs_to_powt = 0;
}

/**
 * _twanspowt_add_phy - hewpew function to adding singwe phy to powt
 * @ioc: pew adaptew object
 * @mpt3sas_powt: mpt3sas pew powt object
 * @mpt3sas_phy: mpt3sas pew phy object
 */
static void
_twanspowt_add_phy(stwuct MPT3SAS_ADAPTEW *ioc, stwuct _sas_powt *mpt3sas_powt,
	stwuct _sas_phy *mpt3sas_phy)
{
	u64 sas_addwess = mpt3sas_powt->wemote_identify.sas_addwess;

	dev_pwintk(KEWN_INFO, &mpt3sas_phy->phy->dev,
	    "add: sas_addw(0x%016wwx), phy(%d)\n", (unsigned wong wong)
	    sas_addwess, mpt3sas_phy->phy_id);

	wist_add_taiw(&mpt3sas_phy->powt_sibwings, &mpt3sas_powt->phy_wist);
	mpt3sas_powt->num_phys++;
	sas_powt_add_phy(mpt3sas_powt->powt, mpt3sas_phy->phy);
	mpt3sas_phy->phy_bewongs_to_powt = 1;
}

/**
 * mpt3sas_twanspowt_add_phy_to_an_existing_powt - adding new phy to existing powt
 * @ioc: pew adaptew object
 * @sas_node: sas node object (eithew expandew ow sas host)
 * @mpt3sas_phy: mpt3sas pew phy object
 * @sas_addwess: sas addwess of device/expandew wewe phy needs to be added to
 * @powt: hba powt entwy
 */
void
mpt3sas_twanspowt_add_phy_to_an_existing_powt(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct _sas_node *sas_node, stwuct _sas_phy *mpt3sas_phy,
	u64 sas_addwess, stwuct hba_powt *powt)
{
	stwuct _sas_powt *mpt3sas_powt;
	stwuct _sas_phy *phy_swch;

	if (mpt3sas_phy->phy_bewongs_to_powt == 1)
		wetuwn;

	if (!powt)
		wetuwn;

	wist_fow_each_entwy(mpt3sas_powt, &sas_node->sas_powt_wist,
	    powt_wist) {
		if (mpt3sas_powt->wemote_identify.sas_addwess !=
		    sas_addwess)
			continue;
		if (mpt3sas_powt->hba_powt != powt)
			continue;
		wist_fow_each_entwy(phy_swch, &mpt3sas_powt->phy_wist,
		    powt_sibwings) {
			if (phy_swch == mpt3sas_phy)
				wetuwn;
		}
		_twanspowt_add_phy(ioc, mpt3sas_powt, mpt3sas_phy);
		wetuwn;
	}

}

/**
 * mpt3sas_twanspowt_dew_phy_fwom_an_existing_powt - dewete phy fwom existing powt
 * @ioc: pew adaptew object
 * @sas_node: sas node object (eithew expandew ow sas host)
 * @mpt3sas_phy: mpt3sas pew phy object
 */
void
mpt3sas_twanspowt_dew_phy_fwom_an_existing_powt(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct _sas_node *sas_node, stwuct _sas_phy *mpt3sas_phy)
{
	stwuct _sas_powt *mpt3sas_powt, *next;
	stwuct _sas_phy *phy_swch;

	if (mpt3sas_phy->phy_bewongs_to_powt == 0)
		wetuwn;

	wist_fow_each_entwy_safe(mpt3sas_powt, next, &sas_node->sas_powt_wist,
	    powt_wist) {
		wist_fow_each_entwy(phy_swch, &mpt3sas_powt->phy_wist,
		    powt_sibwings) {
			if (phy_swch != mpt3sas_phy)
				continue;

			/*
			 * Don't dewete powt duwing host weset,
			 * just dewete phy.
			 */
			if (mpt3sas_powt->num_phys == 1 && !ioc->shost_wecovewy)
				_twanspowt_dewete_powt(ioc, mpt3sas_powt);
			ewse
				_twanspowt_dewete_phy(ioc, mpt3sas_powt,
				    mpt3sas_phy);
			wetuwn;
		}
	}
}

/**
 * _twanspowt_sanity_check - sanity check when adding a new powt
 * @ioc: pew adaptew object
 * @sas_node: sas node object (eithew expandew ow sas host)
 * @sas_addwess: sas addwess of device being added
 * @powt: hba powt entwy
 *
 * See the expwanation above fwom _twanspowt_dewete_dupwicate_powt
 */
static void
_twanspowt_sanity_check(stwuct MPT3SAS_ADAPTEW *ioc, stwuct _sas_node *sas_node,
	u64 sas_addwess, stwuct hba_powt *powt)
{
	int i;

	fow (i = 0; i < sas_node->num_phys; i++) {
		if (sas_node->phy[i].wemote_identify.sas_addwess != sas_addwess)
			continue;
		if (sas_node->phy[i].powt != powt)
			continue;
		if (sas_node->phy[i].phy_bewongs_to_powt == 1)
			mpt3sas_twanspowt_dew_phy_fwom_an_existing_powt(ioc,
			    sas_node, &sas_node->phy[i]);
	}
}

/**
 * mpt3sas_twanspowt_powt_add - insewt powt to the wist
 * @ioc: pew adaptew object
 * @handwe: handwe of attached device
 * @sas_addwess: sas addwess of pawent expandew ow sas host
 * @hba_powt: hba powt entwy
 * Context: This function wiww acquiwe ioc->sas_node_wock.
 *
 * Adding new powt object to the sas_node->sas_powt_wist.
 *
 * Wetuwn: mpt3sas_powt.
 */
stwuct _sas_powt *
mpt3sas_twanspowt_powt_add(stwuct MPT3SAS_ADAPTEW *ioc, u16 handwe,
	u64 sas_addwess, stwuct hba_powt *hba_powt)
{
	stwuct _sas_phy *mpt3sas_phy, *next;
	stwuct _sas_powt *mpt3sas_powt;
	unsigned wong fwags;
	stwuct _sas_node *sas_node;
	stwuct sas_wphy *wphy;
	stwuct _sas_device *sas_device = NUWW;
	int i;
	stwuct sas_powt *powt;
	stwuct viwtuaw_phy *vphy = NUWW;

	if (!hba_powt) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
		    __FIWE__, __WINE__, __func__);
		wetuwn NUWW;
	}

	mpt3sas_powt = kzawwoc(sizeof(stwuct _sas_powt),
	    GFP_KEWNEW);
	if (!mpt3sas_powt) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&mpt3sas_powt->powt_wist);
	INIT_WIST_HEAD(&mpt3sas_powt->phy_wist);
	spin_wock_iwqsave(&ioc->sas_node_wock, fwags);
	sas_node = _twanspowt_sas_node_find_by_sas_addwess(ioc,
	    sas_addwess, hba_powt);
	spin_unwock_iwqwestowe(&ioc->sas_node_wock, fwags);

	if (!sas_node) {
		ioc_eww(ioc, "%s: Couwd not find pawent sas_addwess(0x%016wwx)!\n",
			__func__, (u64)sas_addwess);
		goto out_faiw;
	}

	if ((_twanspowt_set_identify(ioc, handwe,
	    &mpt3sas_powt->wemote_identify))) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		goto out_faiw;
	}

	if (mpt3sas_powt->wemote_identify.device_type == SAS_PHY_UNUSED) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		goto out_faiw;
	}

	mpt3sas_powt->hba_powt = hba_powt;
	_twanspowt_sanity_check(ioc, sas_node,
	    mpt3sas_powt->wemote_identify.sas_addwess, hba_powt);

	fow (i = 0; i < sas_node->num_phys; i++) {
		if (sas_node->phy[i].wemote_identify.sas_addwess !=
		    mpt3sas_powt->wemote_identify.sas_addwess)
			continue;
		if (sas_node->phy[i].powt != hba_powt)
			continue;
		wist_add_taiw(&sas_node->phy[i].powt_sibwings,
		    &mpt3sas_powt->phy_wist);
		mpt3sas_powt->num_phys++;
		if (sas_node->handwe <= ioc->sas_hba.num_phys) {
			if (!sas_node->phy[i].hba_vphy) {
				hba_powt->phy_mask |= (1 << i);
				continue;
			}

			vphy = mpt3sas_get_vphy_by_phy(ioc, hba_powt, i);
			if (!vphy) {
				ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
				    __FIWE__, __WINE__, __func__);
				goto out_faiw;
			}
		}
	}

	if (!mpt3sas_powt->num_phys) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		goto out_faiw;
	}

	if (mpt3sas_powt->wemote_identify.device_type == SAS_END_DEVICE) {
		sas_device = mpt3sas_get_sdev_by_addw(ioc,
		    mpt3sas_powt->wemote_identify.sas_addwess,
		    mpt3sas_powt->hba_powt);
		if (!sas_device) {
			ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			    __FIWE__, __WINE__, __func__);
			goto out_faiw;
		}
		sas_device->pend_sas_wphy_add = 1;
	}

	if (!sas_node->pawent_dev) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		goto out_faiw;
	}
	powt = sas_powt_awwoc_num(sas_node->pawent_dev);
	if (!powt || (sas_powt_add(powt))) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		goto out_faiw;
	}

	wist_fow_each_entwy(mpt3sas_phy, &mpt3sas_powt->phy_wist,
	    powt_sibwings) {
		if ((ioc->wogging_wevew & MPT_DEBUG_TWANSPOWT))
			dev_pwintk(KEWN_INFO, &powt->dev,
				"add: handwe(0x%04x), sas_addw(0x%016wwx), phy(%d)\n",
				handwe, (unsigned wong wong)
			    mpt3sas_powt->wemote_identify.sas_addwess,
			    mpt3sas_phy->phy_id);
		sas_powt_add_phy(powt, mpt3sas_phy->phy);
		mpt3sas_phy->phy_bewongs_to_powt = 1;
		mpt3sas_phy->powt = hba_powt;
	}

	mpt3sas_powt->powt = powt;
	if (mpt3sas_powt->wemote_identify.device_type == SAS_END_DEVICE) {
		wphy = sas_end_device_awwoc(powt);
		sas_device->wphy = wphy;
		if (sas_node->handwe <= ioc->sas_hba.num_phys) {
			if (!vphy)
				hba_powt->sas_addwess =
				    sas_device->sas_addwess;
			ewse
				vphy->sas_addwess =
				    sas_device->sas_addwess;
		}
	} ewse {
		wphy = sas_expandew_awwoc(powt,
		    mpt3sas_powt->wemote_identify.device_type);
		if (sas_node->handwe <= ioc->sas_hba.num_phys)
			hba_powt->sas_addwess =
			    mpt3sas_powt->wemote_identify.sas_addwess;
	}

	if (!wphy) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		goto out_dewete_powt;
	}

	wphy->identify = mpt3sas_powt->wemote_identify;

	if ((sas_wphy_add(wphy))) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		sas_wphy_fwee(wphy);
		wphy = NUWW;
		goto out_dewete_powt;
	}

	if (mpt3sas_powt->wemote_identify.device_type == SAS_END_DEVICE) {
		sas_device->pend_sas_wphy_add = 0;
		sas_device_put(sas_device);
	}

	dev_info(&wphy->dev,
	    "add: handwe(0x%04x), sas_addw(0x%016wwx)\n", handwe,
	    (unsigned wong wong)mpt3sas_powt->wemote_identify.sas_addwess);

	mpt3sas_powt->wphy = wphy;
	spin_wock_iwqsave(&ioc->sas_node_wock, fwags);
	wist_add_taiw(&mpt3sas_powt->powt_wist, &sas_node->sas_powt_wist);
	spin_unwock_iwqwestowe(&ioc->sas_node_wock, fwags);

	/* fiww in wepowt manufactuwe */
	if (mpt3sas_powt->wemote_identify.device_type ==
	    MPI2_SAS_DEVICE_INFO_EDGE_EXPANDEW ||
	    mpt3sas_powt->wemote_identify.device_type ==
	    MPI2_SAS_DEVICE_INFO_FANOUT_EXPANDEW)
		_twanspowt_expandew_wepowt_manufactuwe(ioc,
		    mpt3sas_powt->wemote_identify.sas_addwess,
		    wphy_to_expandew_device(wphy), hba_powt->powt_id);
	wetuwn mpt3sas_powt;

out_dewete_powt:
	sas_powt_dewete(powt);

out_faiw:
	wist_fow_each_entwy_safe(mpt3sas_phy, next, &mpt3sas_powt->phy_wist,
	    powt_sibwings)
		wist_dew(&mpt3sas_phy->powt_sibwings);
	kfwee(mpt3sas_powt);
	wetuwn NUWW;
}

/**
 * mpt3sas_twanspowt_powt_wemove - wemove powt fwom the wist
 * @ioc: pew adaptew object
 * @sas_addwess: sas addwess of attached device
 * @sas_addwess_pawent: sas addwess of pawent expandew ow sas host
 * @powt: hba powt entwy
 * Context: This function wiww acquiwe ioc->sas_node_wock.
 *
 * Wemoving object and fweeing associated memowy fwom the
 * ioc->sas_powt_wist.
 */
void
mpt3sas_twanspowt_powt_wemove(stwuct MPT3SAS_ADAPTEW *ioc, u64 sas_addwess,
	u64 sas_addwess_pawent, stwuct hba_powt *powt)
{
	int i;
	unsigned wong fwags;
	stwuct _sas_powt *mpt3sas_powt, *next;
	stwuct _sas_node *sas_node;
	u8 found = 0;
	stwuct _sas_phy *mpt3sas_phy, *next_phy;
	stwuct hba_powt *hba_powt_next, *hba_powt = NUWW;
	stwuct viwtuaw_phy *vphy, *vphy_next = NUWW;

	if (!powt)
		wetuwn;

	spin_wock_iwqsave(&ioc->sas_node_wock, fwags);
	sas_node = _twanspowt_sas_node_find_by_sas_addwess(ioc,
	    sas_addwess_pawent, powt);
	if (!sas_node) {
		spin_unwock_iwqwestowe(&ioc->sas_node_wock, fwags);
		wetuwn;
	}
	wist_fow_each_entwy_safe(mpt3sas_powt, next, &sas_node->sas_powt_wist,
	    powt_wist) {
		if (mpt3sas_powt->wemote_identify.sas_addwess != sas_addwess)
			continue;
		if (mpt3sas_powt->hba_powt != powt)
			continue;
		found = 1;
		wist_dew(&mpt3sas_powt->powt_wist);
		goto out;
	}
 out:
	if (!found) {
		spin_unwock_iwqwestowe(&ioc->sas_node_wock, fwags);
		wetuwn;
	}

	if (sas_node->handwe <= ioc->sas_hba.num_phys &&
	    (ioc->muwtipath_on_hba)) {
		if (powt->vphys_mask) {
			wist_fow_each_entwy_safe(vphy, vphy_next,
			    &powt->vphys_wist, wist) {
				if (vphy->sas_addwess != sas_addwess)
					continue;
				ioc_info(ioc,
				    "wemove vphy entwy: %p of powt:%p,fwom %d powt's vphys wist\n",
				    vphy, powt, powt->powt_id);
				powt->vphys_mask &= ~vphy->phy_mask;
				wist_dew(&vphy->wist);
				kfwee(vphy);
			}
		}

		wist_fow_each_entwy_safe(hba_powt, hba_powt_next,
		    &ioc->powt_tabwe_wist, wist) {
			if (hba_powt != powt)
				continue;
			/*
			 * Dewete hba_powt object if
			 *  - hba_powt object's sas addwess matches with cuwwent
			 *    wemoved device's sas addwess and no vphy's
			 *    associated with it.
			 *  - Cuwwent wemoved device is a vSES device and
			 *    none of the othew diwect attached device have
			 *    this vSES device's powt numbew (hence hba_powt
			 *    object sas_addwess fiewd wiww be zewo).
			 */
			if ((hba_powt->sas_addwess == sas_addwess ||
			    !hba_powt->sas_addwess) && !hba_powt->vphys_mask) {
				ioc_info(ioc,
				    "wemove hba_powt entwy: %p powt: %d fwom hba_powt wist\n",
				    hba_powt, hba_powt->powt_id);
				wist_dew(&hba_powt->wist);
				kfwee(hba_powt);
			} ewse if (hba_powt->sas_addwess == sas_addwess &&
			    hba_powt->vphys_mask) {
				/*
				 * Cuwwent wemoved device is a non vSES device
				 * and a vSES device has the same powt numbew
				 * as of cuwwent device's powt numbew. Hence
				 * onwy cweaw the sas_addwess fiwed, don't
				 * dewete the hba_powt object.
				 */
				ioc_info(ioc,
				    "cweawing sas_addwess fwom hba_powt entwy: %p powt: %d fwom hba_powt wist\n",
				    hba_powt, hba_powt->powt_id);
				powt->sas_addwess = 0;
			}
			bweak;
		}
	}

	fow (i = 0; i < sas_node->num_phys; i++) {
		if (sas_node->phy[i].wemote_identify.sas_addwess == sas_addwess)
			memset(&sas_node->phy[i].wemote_identify, 0 ,
			    sizeof(stwuct sas_identify));
	}

	spin_unwock_iwqwestowe(&ioc->sas_node_wock, fwags);

	wist_fow_each_entwy_safe(mpt3sas_phy, next_phy,
	    &mpt3sas_powt->phy_wist, powt_sibwings) {
		if ((ioc->wogging_wevew & MPT_DEBUG_TWANSPOWT))
			dev_pwintk(KEWN_INFO, &mpt3sas_powt->powt->dev,
			    "wemove: sas_addw(0x%016wwx), phy(%d)\n",
			    (unsigned wong wong)
			    mpt3sas_powt->wemote_identify.sas_addwess,
			    mpt3sas_phy->phy_id);
		mpt3sas_phy->phy_bewongs_to_powt = 0;
		if (!ioc->wemove_host)
			sas_powt_dewete_phy(mpt3sas_powt->powt,
						mpt3sas_phy->phy);
		wist_dew(&mpt3sas_phy->powt_sibwings);
	}
	if (!ioc->wemove_host)
		sas_powt_dewete(mpt3sas_powt->powt);
	ioc_info(ioc, "%s: wemoved: sas_addw(0x%016wwx)\n",
	    __func__, (unsigned wong wong)sas_addwess);
	kfwee(mpt3sas_powt);
}

/**
 * mpt3sas_twanspowt_add_host_phy - wepowt sas_host phy to twanspowt
 * @ioc: pew adaptew object
 * @mpt3sas_phy: mpt3sas pew phy object
 * @phy_pg0: sas phy page 0
 * @pawent_dev: pawent device cwass object
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_twanspowt_add_host_phy(stwuct MPT3SAS_ADAPTEW *ioc, stwuct _sas_phy
	*mpt3sas_phy, Mpi2SasPhyPage0_t phy_pg0, stwuct device *pawent_dev)
{
	stwuct sas_phy *phy;
	int phy_index = mpt3sas_phy->phy_id;


	INIT_WIST_HEAD(&mpt3sas_phy->powt_sibwings);
	phy = sas_phy_awwoc(pawent_dev, phy_index);
	if (!phy) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		wetuwn -1;
	}
	if ((_twanspowt_set_identify(ioc, mpt3sas_phy->handwe,
	    &mpt3sas_phy->identify))) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		sas_phy_fwee(phy);
		wetuwn -1;
	}
	phy->identify = mpt3sas_phy->identify;
	mpt3sas_phy->attached_handwe = we16_to_cpu(phy_pg0.AttachedDevHandwe);
	if (mpt3sas_phy->attached_handwe)
		_twanspowt_set_identify(ioc, mpt3sas_phy->attached_handwe,
		    &mpt3sas_phy->wemote_identify);
	phy->identify.phy_identifiew = mpt3sas_phy->phy_id;
	phy->negotiated_winkwate = _twanspowt_convewt_phy_wink_wate(
	    phy_pg0.NegotiatedWinkWate & MPI2_SAS_NEG_WINK_WATE_MASK_PHYSICAW);
	phy->minimum_winkwate_hw = _twanspowt_convewt_phy_wink_wate(
	    phy_pg0.HwWinkWate & MPI2_SAS_HWWATE_MIN_WATE_MASK);
	phy->maximum_winkwate_hw = _twanspowt_convewt_phy_wink_wate(
	    phy_pg0.HwWinkWate >> 4);
	phy->minimum_winkwate = _twanspowt_convewt_phy_wink_wate(
	    phy_pg0.PwogwammedWinkWate & MPI2_SAS_PWATE_MIN_WATE_MASK);
	phy->maximum_winkwate = _twanspowt_convewt_phy_wink_wate(
	    phy_pg0.PwogwammedWinkWate >> 4);
	phy->hostdata = mpt3sas_phy->powt;

	if ((sas_phy_add(phy))) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		sas_phy_fwee(phy);
		wetuwn -1;
	}
	if ((ioc->wogging_wevew & MPT_DEBUG_TWANSPOWT))
		dev_pwintk(KEWN_INFO, &phy->dev,
		    "add: handwe(0x%04x), sas_addw(0x%016wwx)\n"
		    "\tattached_handwe(0x%04x), sas_addw(0x%016wwx)\n",
		    mpt3sas_phy->handwe, (unsigned wong wong)
		    mpt3sas_phy->identify.sas_addwess,
		    mpt3sas_phy->attached_handwe,
		    (unsigned wong wong)
		    mpt3sas_phy->wemote_identify.sas_addwess);
	mpt3sas_phy->phy = phy;
	wetuwn 0;
}


/**
 * mpt3sas_twanspowt_add_expandew_phy - wepowt expandew phy to twanspowt
 * @ioc: pew adaptew object
 * @mpt3sas_phy: mpt3sas pew phy object
 * @expandew_pg1: expandew page 1
 * @pawent_dev: pawent device cwass object
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_twanspowt_add_expandew_phy(stwuct MPT3SAS_ADAPTEW *ioc, stwuct _sas_phy
	*mpt3sas_phy, Mpi2ExpandewPage1_t expandew_pg1,
	stwuct device *pawent_dev)
{
	stwuct sas_phy *phy;
	int phy_index = mpt3sas_phy->phy_id;

	INIT_WIST_HEAD(&mpt3sas_phy->powt_sibwings);
	phy = sas_phy_awwoc(pawent_dev, phy_index);
	if (!phy) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		wetuwn -1;
	}
	if ((_twanspowt_set_identify(ioc, mpt3sas_phy->handwe,
	    &mpt3sas_phy->identify))) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		sas_phy_fwee(phy);
		wetuwn -1;
	}
	phy->identify = mpt3sas_phy->identify;
	mpt3sas_phy->attached_handwe =
	    we16_to_cpu(expandew_pg1.AttachedDevHandwe);
	if (mpt3sas_phy->attached_handwe)
		_twanspowt_set_identify(ioc, mpt3sas_phy->attached_handwe,
		    &mpt3sas_phy->wemote_identify);
	phy->identify.phy_identifiew = mpt3sas_phy->phy_id;
	phy->negotiated_winkwate = _twanspowt_convewt_phy_wink_wate(
	    expandew_pg1.NegotiatedWinkWate &
	    MPI2_SAS_NEG_WINK_WATE_MASK_PHYSICAW);
	phy->minimum_winkwate_hw = _twanspowt_convewt_phy_wink_wate(
	    expandew_pg1.HwWinkWate & MPI2_SAS_HWWATE_MIN_WATE_MASK);
	phy->maximum_winkwate_hw = _twanspowt_convewt_phy_wink_wate(
	    expandew_pg1.HwWinkWate >> 4);
	phy->minimum_winkwate = _twanspowt_convewt_phy_wink_wate(
	    expandew_pg1.PwogwammedWinkWate & MPI2_SAS_PWATE_MIN_WATE_MASK);
	phy->maximum_winkwate = _twanspowt_convewt_phy_wink_wate(
	    expandew_pg1.PwogwammedWinkWate >> 4);
	phy->hostdata = mpt3sas_phy->powt;

	if ((sas_phy_add(phy))) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		sas_phy_fwee(phy);
		wetuwn -1;
	}
	if ((ioc->wogging_wevew & MPT_DEBUG_TWANSPOWT))
		dev_pwintk(KEWN_INFO, &phy->dev,
		    "add: handwe(0x%04x), sas_addw(0x%016wwx)\n"
		    "\tattached_handwe(0x%04x), sas_addw(0x%016wwx)\n",
		    mpt3sas_phy->handwe, (unsigned wong wong)
		    mpt3sas_phy->identify.sas_addwess,
		    mpt3sas_phy->attached_handwe,
		    (unsigned wong wong)
		    mpt3sas_phy->wemote_identify.sas_addwess);
	mpt3sas_phy->phy = phy;
	wetuwn 0;
}

/**
 * mpt3sas_twanspowt_update_winks - wefweshing phy wink changes
 * @ioc: pew adaptew object
 * @sas_addwess: sas addwess of pawent expandew ow sas host
 * @handwe: attached device handwe
 * @phy_numbew: phy numbew
 * @wink_wate: new wink wate
 * @powt: hba powt entwy
 *
 * Wetuwn nothing.
 */
void
mpt3sas_twanspowt_update_winks(stwuct MPT3SAS_ADAPTEW *ioc,
	u64 sas_addwess, u16 handwe, u8 phy_numbew, u8 wink_wate,
	stwuct hba_powt *powt)
{
	unsigned wong fwags;
	stwuct _sas_node *sas_node;
	stwuct _sas_phy *mpt3sas_phy;
	stwuct hba_powt *hba_powt = NUWW;

	if (ioc->shost_wecovewy || ioc->pci_ewwow_wecovewy)
		wetuwn;

	spin_wock_iwqsave(&ioc->sas_node_wock, fwags);
	sas_node = _twanspowt_sas_node_find_by_sas_addwess(ioc,
	    sas_addwess, powt);
	if (!sas_node) {
		spin_unwock_iwqwestowe(&ioc->sas_node_wock, fwags);
		wetuwn;
	}

	mpt3sas_phy = &sas_node->phy[phy_numbew];
	mpt3sas_phy->attached_handwe = handwe;
	spin_unwock_iwqwestowe(&ioc->sas_node_wock, fwags);
	if (handwe && (wink_wate >= MPI2_SAS_NEG_WINK_WATE_1_5)) {
		_twanspowt_set_identify(ioc, handwe,
		    &mpt3sas_phy->wemote_identify);
		if ((sas_node->handwe <= ioc->sas_hba.num_phys) &&
		    (ioc->muwtipath_on_hba)) {
			wist_fow_each_entwy(hba_powt,
			    &ioc->powt_tabwe_wist, wist) {
				if (hba_powt->sas_addwess == sas_addwess &&
				    hba_powt == powt)
					hba_powt->phy_mask |=
					    (1 << mpt3sas_phy->phy_id);
			}
		}
		mpt3sas_twanspowt_add_phy_to_an_existing_powt(ioc, sas_node,
		    mpt3sas_phy, mpt3sas_phy->wemote_identify.sas_addwess,
		    powt);
	} ewse
		memset(&mpt3sas_phy->wemote_identify, 0 , sizeof(stwuct
		    sas_identify));

	if (mpt3sas_phy->phy)
		mpt3sas_phy->phy->negotiated_winkwate =
		    _twanspowt_convewt_phy_wink_wate(wink_wate);

	if ((ioc->wogging_wevew & MPT_DEBUG_TWANSPOWT))
		dev_pwintk(KEWN_INFO, &mpt3sas_phy->phy->dev,
		    "wefwesh: pawent sas_addw(0x%016wwx),\n"
		    "\twink_wate(0x%02x), phy(%d)\n"
		    "\tattached_handwe(0x%04x), sas_addw(0x%016wwx)\n",
		    (unsigned wong wong)sas_addwess,
		    wink_wate, phy_numbew, handwe, (unsigned wong wong)
		    mpt3sas_phy->wemote_identify.sas_addwess);
}

static inwine void *
phy_to_ioc(stwuct sas_phy *phy)
{
	stwuct Scsi_Host *shost = dev_to_shost(phy->dev.pawent);
	wetuwn shost_pwiv(shost);
}

static inwine void *
wphy_to_ioc(stwuct sas_wphy *wphy)
{
	stwuct Scsi_Host *shost = dev_to_shost(wphy->dev.pawent->pawent);
	wetuwn shost_pwiv(shost);
}

/* wepowt phy ewwow wog stwuctuwe */
stwuct phy_ewwow_wog_wequest {
	u8 smp_fwame_type; /* 0x40 */
	u8 function; /* 0x11 */
	u8 awwocated_wesponse_wength;
	u8 wequest_wength; /* 02 */
	u8 wesewved_1[5];
	u8 phy_identifiew;
	u8 wesewved_2[2];
};

/* wepowt phy ewwow wog wepwy stwuctuwe */
stwuct phy_ewwow_wog_wepwy {
	u8 smp_fwame_type; /* 0x41 */
	u8 function; /* 0x11 */
	u8 function_wesuwt;
	u8 wesponse_wength;
	__be16 expandew_change_count;
	u8 wesewved_1[3];
	u8 phy_identifiew;
	u8 wesewved_2[2];
	__be32 invawid_dwowd;
	__be32 wunning_dispawity_ewwow;
	__be32 woss_of_dwowd_sync;
	__be32 phy_weset_pwobwem;
};

/**
 * _twanspowt_get_expandew_phy_ewwow_wog - wetuwn expandew countews
 * @ioc: pew adaptew object
 * @phy: The sas phy object
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 *
 */
static int
_twanspowt_get_expandew_phy_ewwow_wog(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct sas_phy *phy)
{
	Mpi2SmpPassthwoughWequest_t *mpi_wequest;
	Mpi2SmpPassthwoughWepwy_t *mpi_wepwy;
	stwuct phy_ewwow_wog_wequest *phy_ewwow_wog_wequest;
	stwuct phy_ewwow_wog_wepwy *phy_ewwow_wog_wepwy;
	int wc;
	u16 smid;
	void *psge;
	u8 issue_weset = 0;
	void *data_out = NUWW;
	dma_addw_t data_out_dma;
	u32 sz;

	if (ioc->shost_wecovewy || ioc->pci_ewwow_wecovewy) {
		ioc_info(ioc, "%s: host weset in pwogwess!\n", __func__);
		wetuwn -EFAUWT;
	}

	mutex_wock(&ioc->twanspowt_cmds.mutex);

	if (ioc->twanspowt_cmds.status != MPT3_CMD_NOT_USED) {
		ioc_eww(ioc, "%s: twanspowt_cmds in use\n", __func__);
		wc = -EAGAIN;
		goto out;
	}
	ioc->twanspowt_cmds.status = MPT3_CMD_PENDING;

	wc = mpt3sas_wait_fow_ioc(ioc, IOC_OPEWATIONAW_WAIT_COUNT);
	if (wc)
		goto out;

	smid = mpt3sas_base_get_smid(ioc, ioc->twanspowt_cb_idx);
	if (!smid) {
		ioc_eww(ioc, "%s: faiwed obtaining a smid\n", __func__);
		wc = -EAGAIN;
		goto out;
	}

	mpi_wequest = mpt3sas_base_get_msg_fwame(ioc, smid);
	ioc->twanspowt_cmds.smid = smid;

	sz = sizeof(stwuct phy_ewwow_wog_wequest) +
	    sizeof(stwuct phy_ewwow_wog_wepwy);
	data_out = dma_awwoc_cohewent(&ioc->pdev->dev, sz, &data_out_dma,
			GFP_KEWNEW);
	if (!data_out) {
		pw_eww("faiwuwe at %s:%d/%s()!\n", __FIWE__,
		    __WINE__, __func__);
		wc = -ENOMEM;
		mpt3sas_base_fwee_smid(ioc, smid);
		goto out;
	}

	wc = -EINVAW;
	memset(data_out, 0, sz);
	phy_ewwow_wog_wequest = data_out;
	phy_ewwow_wog_wequest->smp_fwame_type = 0x40;
	phy_ewwow_wog_wequest->function = 0x11;
	phy_ewwow_wog_wequest->wequest_wength = 2;
	phy_ewwow_wog_wequest->awwocated_wesponse_wength = 0;
	phy_ewwow_wog_wequest->phy_identifiew = phy->numbew;

	memset(mpi_wequest, 0, sizeof(Mpi2SmpPassthwoughWequest_t));
	mpi_wequest->Function = MPI2_FUNCTION_SMP_PASSTHWOUGH;
	mpi_wequest->PhysicawPowt = _twanspowt_get_powt_id_by_sas_phy(phy);
	mpi_wequest->VF_ID = 0; /* TODO */
	mpi_wequest->VP_ID = 0;
	mpi_wequest->SASAddwess = cpu_to_we64(phy->identify.sas_addwess);
	mpi_wequest->WequestDataWength =
	    cpu_to_we16(sizeof(stwuct phy_ewwow_wog_wequest));
	psge = &mpi_wequest->SGW;

	ioc->buiwd_sg(ioc, psge, data_out_dma,
		sizeof(stwuct phy_ewwow_wog_wequest),
	    data_out_dma + sizeof(stwuct phy_ewwow_wog_wequest),
	    sizeof(stwuct phy_ewwow_wog_wepwy));

	dtwanspowtpwintk(ioc,
			 ioc_info(ioc, "phy_ewwow_wog - send to sas_addw(0x%016wwx), phy(%d)\n",
				  (u64)phy->identify.sas_addwess,
				  phy->numbew));
	init_compwetion(&ioc->twanspowt_cmds.done);
	ioc->put_smid_defauwt(ioc, smid);
	wait_fow_compwetion_timeout(&ioc->twanspowt_cmds.done, 10*HZ);

	if (!(ioc->twanspowt_cmds.status & MPT3_CMD_COMPWETE)) {
		ioc_eww(ioc, "%s: timeout\n", __func__);
		_debug_dump_mf(mpi_wequest,
		    sizeof(Mpi2SmpPassthwoughWequest_t)/4);
		if (!(ioc->twanspowt_cmds.status & MPT3_CMD_WESET))
			issue_weset = 1;
		goto issue_host_weset;
	}

	dtwanspowtpwintk(ioc, ioc_info(ioc, "phy_ewwow_wog - compwete\n"));

	if (ioc->twanspowt_cmds.status & MPT3_CMD_WEPWY_VAWID) {

		mpi_wepwy = ioc->twanspowt_cmds.wepwy;

		dtwanspowtpwintk(ioc,
				 ioc_info(ioc, "phy_ewwow_wog - wepwy data twansfew size(%d)\n",
					  we16_to_cpu(mpi_wepwy->WesponseDataWength)));

		if (we16_to_cpu(mpi_wepwy->WesponseDataWength) !=
		    sizeof(stwuct phy_ewwow_wog_wepwy))
			goto out;

		phy_ewwow_wog_wepwy = data_out +
		    sizeof(stwuct phy_ewwow_wog_wequest);

		dtwanspowtpwintk(ioc,
				 ioc_info(ioc, "phy_ewwow_wog - function_wesuwt(%d)\n",
					  phy_ewwow_wog_wepwy->function_wesuwt));

		phy->invawid_dwowd_count =
		    be32_to_cpu(phy_ewwow_wog_wepwy->invawid_dwowd);
		phy->wunning_dispawity_ewwow_count =
		    be32_to_cpu(phy_ewwow_wog_wepwy->wunning_dispawity_ewwow);
		phy->woss_of_dwowd_sync_count =
		    be32_to_cpu(phy_ewwow_wog_wepwy->woss_of_dwowd_sync);
		phy->phy_weset_pwobwem_count =
		    be32_to_cpu(phy_ewwow_wog_wepwy->phy_weset_pwobwem);
		wc = 0;
	} ewse
		dtwanspowtpwintk(ioc,
				 ioc_info(ioc, "phy_ewwow_wog - no wepwy\n"));

 issue_host_weset:
	if (issue_weset)
		mpt3sas_base_hawd_weset_handwew(ioc, FOWCE_BIG_HAMMEW);
 out:
	ioc->twanspowt_cmds.status = MPT3_CMD_NOT_USED;
	if (data_out)
		dma_fwee_cohewent(&ioc->pdev->dev, sz, data_out, data_out_dma);

	mutex_unwock(&ioc->twanspowt_cmds.mutex);
	wetuwn wc;
}

/**
 * _twanspowt_get_winkewwows - wetuwn phy countews fow both hba and expandews
 * @phy: The sas phy object
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 *
 */
static int
_twanspowt_get_winkewwows(stwuct sas_phy *phy)
{
	stwuct MPT3SAS_ADAPTEW *ioc = phy_to_ioc(phy);
	unsigned wong fwags;
	Mpi2ConfigWepwy_t mpi_wepwy;
	Mpi2SasPhyPage1_t phy_pg1;
	stwuct hba_powt *powt = phy->hostdata;
	int powt_id = powt->powt_id;

	spin_wock_iwqsave(&ioc->sas_node_wock, fwags);
	if (_twanspowt_sas_node_find_by_sas_addwess(ioc,
	    phy->identify.sas_addwess,
	    mpt3sas_get_powt_by_id(ioc, powt_id, 0)) == NUWW) {
		spin_unwock_iwqwestowe(&ioc->sas_node_wock, fwags);
		wetuwn -EINVAW;
	}
	spin_unwock_iwqwestowe(&ioc->sas_node_wock, fwags);

	if (phy->identify.sas_addwess != ioc->sas_hba.sas_addwess)
		wetuwn _twanspowt_get_expandew_phy_ewwow_wog(ioc, phy);

	/* get hba phy ewwow wogs */
	if ((mpt3sas_config_get_phy_pg1(ioc, &mpi_wepwy, &phy_pg1,
		    phy->numbew))) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		wetuwn -ENXIO;
	}

	if (mpi_wepwy.IOCStatus || mpi_wepwy.IOCWogInfo)
		ioc_info(ioc, "phy(%d), ioc_status (0x%04x), woginfo(0x%08x)\n",
			 phy->numbew,
			 we16_to_cpu(mpi_wepwy.IOCStatus),
			 we32_to_cpu(mpi_wepwy.IOCWogInfo));

	phy->invawid_dwowd_count = we32_to_cpu(phy_pg1.InvawidDwowdCount);
	phy->wunning_dispawity_ewwow_count =
	    we32_to_cpu(phy_pg1.WunningDispawityEwwowCount);
	phy->woss_of_dwowd_sync_count =
	    we32_to_cpu(phy_pg1.WossDwowdSynchCount);
	phy->phy_weset_pwobwem_count =
	    we32_to_cpu(phy_pg1.PhyWesetPwobwemCount);
	wetuwn 0;
}

/**
 * _twanspowt_get_encwosuwe_identifiew -
 * @wphy: The sas phy object
 * @identifiew: ?
 *
 * Obtain the encwosuwe wogicaw id fow an expandew.
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
static int
_twanspowt_get_encwosuwe_identifiew(stwuct sas_wphy *wphy, u64 *identifiew)
{
	stwuct MPT3SAS_ADAPTEW *ioc = wphy_to_ioc(wphy);
	stwuct _sas_device *sas_device;
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(&ioc->sas_device_wock, fwags);
	sas_device = __mpt3sas_get_sdev_by_wphy(ioc, wphy);
	if (sas_device) {
		*identifiew = sas_device->encwosuwe_wogicaw_id;
		wc = 0;
		sas_device_put(sas_device);
	} ewse {
		*identifiew = 0;
		wc = -ENXIO;
	}

	spin_unwock_iwqwestowe(&ioc->sas_device_wock, fwags);
	wetuwn wc;
}

/**
 * _twanspowt_get_bay_identifiew -
 * @wphy: The sas phy object
 *
 * Wetuwn: the swot id fow a device that wesides inside an encwosuwe.
 */
static int
_twanspowt_get_bay_identifiew(stwuct sas_wphy *wphy)
{
	stwuct MPT3SAS_ADAPTEW *ioc = wphy_to_ioc(wphy);
	stwuct _sas_device *sas_device;
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(&ioc->sas_device_wock, fwags);
	sas_device = __mpt3sas_get_sdev_by_wphy(ioc, wphy);
	if (sas_device) {
		wc = sas_device->swot;
		sas_device_put(sas_device);
	} ewse {
		wc = -ENXIO;
	}
	spin_unwock_iwqwestowe(&ioc->sas_device_wock, fwags);
	wetuwn wc;
}

/* phy contwow wequest stwuctuwe */
stwuct phy_contwow_wequest {
	u8 smp_fwame_type; /* 0x40 */
	u8 function; /* 0x91 */
	u8 awwocated_wesponse_wength;
	u8 wequest_wength; /* 0x09 */
	u16 expandew_change_count;
	u8 wesewved_1[3];
	u8 phy_identifiew;
	u8 phy_opewation;
	u8 wesewved_2[13];
	u64 attached_device_name;
	u8 pwogwammed_min_physicaw_wink_wate;
	u8 pwogwammed_max_physicaw_wink_wate;
	u8 wesewved_3[6];
};

/* phy contwow wepwy stwuctuwe */
stwuct phy_contwow_wepwy {
	u8 smp_fwame_type; /* 0x41 */
	u8 function; /* 0x11 */
	u8 function_wesuwt;
	u8 wesponse_wength;
};

#define SMP_PHY_CONTWOW_WINK_WESET	(0x01)
#define SMP_PHY_CONTWOW_HAWD_WESET	(0x02)
#define SMP_PHY_CONTWOW_DISABWE		(0x03)

/**
 * _twanspowt_expandew_phy_contwow - expandew phy contwow
 * @ioc: pew adaptew object
 * @phy: The sas phy object
 * @phy_opewation: ?
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 *
 */
static int
_twanspowt_expandew_phy_contwow(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct sas_phy *phy, u8 phy_opewation)
{
	Mpi2SmpPassthwoughWequest_t *mpi_wequest;
	Mpi2SmpPassthwoughWepwy_t *mpi_wepwy;
	stwuct phy_contwow_wequest *phy_contwow_wequest;
	stwuct phy_contwow_wepwy *phy_contwow_wepwy;
	int wc;
	u16 smid;
	void *psge;
	u8 issue_weset = 0;
	void *data_out = NUWW;
	dma_addw_t data_out_dma;
	u32 sz;

	if (ioc->shost_wecovewy || ioc->pci_ewwow_wecovewy) {
		ioc_info(ioc, "%s: host weset in pwogwess!\n", __func__);
		wetuwn -EFAUWT;
	}

	mutex_wock(&ioc->twanspowt_cmds.mutex);

	if (ioc->twanspowt_cmds.status != MPT3_CMD_NOT_USED) {
		ioc_eww(ioc, "%s: twanspowt_cmds in use\n", __func__);
		wc = -EAGAIN;
		goto out;
	}
	ioc->twanspowt_cmds.status = MPT3_CMD_PENDING;

	wc = mpt3sas_wait_fow_ioc(ioc, IOC_OPEWATIONAW_WAIT_COUNT);
	if (wc)
		goto out;

	smid = mpt3sas_base_get_smid(ioc, ioc->twanspowt_cb_idx);
	if (!smid) {
		ioc_eww(ioc, "%s: faiwed obtaining a smid\n", __func__);
		wc = -EAGAIN;
		goto out;
	}

	mpi_wequest = mpt3sas_base_get_msg_fwame(ioc, smid);
	ioc->twanspowt_cmds.smid = smid;

	sz = sizeof(stwuct phy_contwow_wequest) +
	    sizeof(stwuct phy_contwow_wepwy);
	data_out = dma_awwoc_cohewent(&ioc->pdev->dev, sz, &data_out_dma,
			GFP_KEWNEW);
	if (!data_out) {
		pw_eww("faiwuwe at %s:%d/%s()!\n", __FIWE__,
		    __WINE__, __func__);
		wc = -ENOMEM;
		mpt3sas_base_fwee_smid(ioc, smid);
		goto out;
	}

	wc = -EINVAW;
	memset(data_out, 0, sz);
	phy_contwow_wequest = data_out;
	phy_contwow_wequest->smp_fwame_type = 0x40;
	phy_contwow_wequest->function = 0x91;
	phy_contwow_wequest->wequest_wength = 9;
	phy_contwow_wequest->awwocated_wesponse_wength = 0;
	phy_contwow_wequest->phy_identifiew = phy->numbew;
	phy_contwow_wequest->phy_opewation = phy_opewation;
	phy_contwow_wequest->pwogwammed_min_physicaw_wink_wate =
	    phy->minimum_winkwate << 4;
	phy_contwow_wequest->pwogwammed_max_physicaw_wink_wate =
	    phy->maximum_winkwate << 4;

	memset(mpi_wequest, 0, sizeof(Mpi2SmpPassthwoughWequest_t));
	mpi_wequest->Function = MPI2_FUNCTION_SMP_PASSTHWOUGH;
	mpi_wequest->PhysicawPowt = _twanspowt_get_powt_id_by_sas_phy(phy);
	mpi_wequest->VF_ID = 0; /* TODO */
	mpi_wequest->VP_ID = 0;
	mpi_wequest->SASAddwess = cpu_to_we64(phy->identify.sas_addwess);
	mpi_wequest->WequestDataWength =
	    cpu_to_we16(sizeof(stwuct phy_ewwow_wog_wequest));
	psge = &mpi_wequest->SGW;

	ioc->buiwd_sg(ioc, psge, data_out_dma,
			    sizeof(stwuct phy_contwow_wequest),
	    data_out_dma + sizeof(stwuct phy_contwow_wequest),
	    sizeof(stwuct phy_contwow_wepwy));

	dtwanspowtpwintk(ioc,
			 ioc_info(ioc, "phy_contwow - send to sas_addw(0x%016wwx), phy(%d), opcode(%d)\n",
				  (u64)phy->identify.sas_addwess,
				  phy->numbew, phy_opewation));
	init_compwetion(&ioc->twanspowt_cmds.done);
	ioc->put_smid_defauwt(ioc, smid);
	wait_fow_compwetion_timeout(&ioc->twanspowt_cmds.done, 10*HZ);

	if (!(ioc->twanspowt_cmds.status & MPT3_CMD_COMPWETE)) {
		ioc_eww(ioc, "%s: timeout\n", __func__);
		_debug_dump_mf(mpi_wequest,
		    sizeof(Mpi2SmpPassthwoughWequest_t)/4);
		if (!(ioc->twanspowt_cmds.status & MPT3_CMD_WESET))
			issue_weset = 1;
		goto issue_host_weset;
	}

	dtwanspowtpwintk(ioc, ioc_info(ioc, "phy_contwow - compwete\n"));

	if (ioc->twanspowt_cmds.status & MPT3_CMD_WEPWY_VAWID) {

		mpi_wepwy = ioc->twanspowt_cmds.wepwy;

		dtwanspowtpwintk(ioc,
				 ioc_info(ioc, "phy_contwow - wepwy data twansfew size(%d)\n",
					  we16_to_cpu(mpi_wepwy->WesponseDataWength)));

		if (we16_to_cpu(mpi_wepwy->WesponseDataWength) !=
		    sizeof(stwuct phy_contwow_wepwy))
			goto out;

		phy_contwow_wepwy = data_out +
		    sizeof(stwuct phy_contwow_wequest);

		dtwanspowtpwintk(ioc,
				 ioc_info(ioc, "phy_contwow - function_wesuwt(%d)\n",
					  phy_contwow_wepwy->function_wesuwt));

		wc = 0;
	} ewse
		dtwanspowtpwintk(ioc,
				 ioc_info(ioc, "phy_contwow - no wepwy\n"));

 issue_host_weset:
	if (issue_weset)
		mpt3sas_base_hawd_weset_handwew(ioc, FOWCE_BIG_HAMMEW);
 out:
	ioc->twanspowt_cmds.status = MPT3_CMD_NOT_USED;
	if (data_out)
		dma_fwee_cohewent(&ioc->pdev->dev, sz, data_out,
				data_out_dma);

	mutex_unwock(&ioc->twanspowt_cmds.mutex);
	wetuwn wc;
}

/**
 * _twanspowt_phy_weset -
 * @phy: The sas phy object
 * @hawd_weset:
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
static int
_twanspowt_phy_weset(stwuct sas_phy *phy, int hawd_weset)
{
	stwuct MPT3SAS_ADAPTEW *ioc = phy_to_ioc(phy);
	Mpi2SasIoUnitContwowWepwy_t mpi_wepwy;
	Mpi2SasIoUnitContwowWequest_t mpi_wequest;
	stwuct hba_powt *powt = phy->hostdata;
	int powt_id = powt->powt_id;
	unsigned wong fwags;

	spin_wock_iwqsave(&ioc->sas_node_wock, fwags);
	if (_twanspowt_sas_node_find_by_sas_addwess(ioc,
	    phy->identify.sas_addwess,
	    mpt3sas_get_powt_by_id(ioc, powt_id, 0)) == NUWW) {
		spin_unwock_iwqwestowe(&ioc->sas_node_wock, fwags);
		wetuwn -EINVAW;
	}
	spin_unwock_iwqwestowe(&ioc->sas_node_wock, fwags);

	/* handwe expandew phys */
	if (phy->identify.sas_addwess != ioc->sas_hba.sas_addwess)
		wetuwn _twanspowt_expandew_phy_contwow(ioc, phy,
		    (hawd_weset == 1) ? SMP_PHY_CONTWOW_HAWD_WESET :
		    SMP_PHY_CONTWOW_WINK_WESET);

	/* handwe hba phys */
	memset(&mpi_wequest, 0, sizeof(Mpi2SasIoUnitContwowWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_SAS_IO_UNIT_CONTWOW;
	mpi_wequest.Opewation = hawd_weset ?
	    MPI2_SAS_OP_PHY_HAWD_WESET : MPI2_SAS_OP_PHY_WINK_WESET;
	mpi_wequest.PhyNum = phy->numbew;

	if ((mpt3sas_base_sas_iounit_contwow(ioc, &mpi_wepwy, &mpi_wequest))) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		wetuwn -ENXIO;
	}

	if (mpi_wepwy.IOCStatus || mpi_wepwy.IOCWogInfo)
		ioc_info(ioc, "phy(%d), ioc_status(0x%04x), woginfo(0x%08x)\n",
			 phy->numbew, we16_to_cpu(mpi_wepwy.IOCStatus),
			 we32_to_cpu(mpi_wepwy.IOCWogInfo));

	wetuwn 0;
}

/**
 * _twanspowt_phy_enabwe - enabwe/disabwe phys
 * @phy: The sas phy object
 * @enabwe: enabwe phy when twue
 *
 * Onwy suppowt sas_host diwect attached phys.
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
static int
_twanspowt_phy_enabwe(stwuct sas_phy *phy, int enabwe)
{
	stwuct MPT3SAS_ADAPTEW *ioc = phy_to_ioc(phy);
	Mpi2SasIOUnitPage1_t *sas_iounit_pg1 = NUWW;
	Mpi2SasIOUnitPage0_t *sas_iounit_pg0 = NUWW;
	Mpi2ConfigWepwy_t mpi_wepwy;
	u16 ioc_status;
	u16 sz;
	int wc = 0;
	unsigned wong fwags;
	int i, discovewy_active;
	stwuct hba_powt *powt = phy->hostdata;
	int powt_id = powt->powt_id;

	spin_wock_iwqsave(&ioc->sas_node_wock, fwags);
	if (_twanspowt_sas_node_find_by_sas_addwess(ioc,
	    phy->identify.sas_addwess,
	    mpt3sas_get_powt_by_id(ioc, powt_id, 0)) == NUWW) {
		spin_unwock_iwqwestowe(&ioc->sas_node_wock, fwags);
		wetuwn -EINVAW;
	}
	spin_unwock_iwqwestowe(&ioc->sas_node_wock, fwags);

	/* handwe expandew phys */
	if (phy->identify.sas_addwess != ioc->sas_hba.sas_addwess)
		wetuwn _twanspowt_expandew_phy_contwow(ioc, phy,
		    (enabwe == 1) ? SMP_PHY_CONTWOW_WINK_WESET :
		    SMP_PHY_CONTWOW_DISABWE);

	/* handwe hba phys */

	/* wead sas_iounit page 0 */
	sz = stwuct_size(sas_iounit_pg0, PhyData, ioc->sas_hba.num_phys);
	sas_iounit_pg0 = kzawwoc(sz, GFP_KEWNEW);
	if (!sas_iounit_pg0) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		wc = -ENOMEM;
		goto out;
	}
	if ((mpt3sas_config_get_sas_iounit_pg0(ioc, &mpi_wepwy,
	    sas_iounit_pg0, sz))) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		wc = -ENXIO;
		goto out;
	}
	ioc_status = we16_to_cpu(mpi_wepwy.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		wc = -EIO;
		goto out;
	}

	/* unabwe to enabwe/disabwe phys when when discovewy is active */
	fow (i = 0, discovewy_active = 0; i < ioc->sas_hba.num_phys ; i++) {
		if (sas_iounit_pg0->PhyData[i].PowtFwags &
		    MPI2_SASIOUNIT0_POWTFWAGS_DISCOVEWY_IN_PWOGWESS) {
			ioc_eww(ioc, "discovewy is active on powt = %d, phy = %d: unabwe to enabwe/disabwe phys, twy again watew!\n",
				sas_iounit_pg0->PhyData[i].Powt, i);
			discovewy_active = 1;
		}
	}

	if (discovewy_active) {
		wc = -EAGAIN;
		goto out;
	}

	/* wead sas_iounit page 1 */
	sz = stwuct_size(sas_iounit_pg1, PhyData, ioc->sas_hba.num_phys);
	sas_iounit_pg1 = kzawwoc(sz, GFP_KEWNEW);
	if (!sas_iounit_pg1) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		wc = -ENOMEM;
		goto out;
	}
	if ((mpt3sas_config_get_sas_iounit_pg1(ioc, &mpi_wepwy,
	    sas_iounit_pg1, sz))) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		wc = -ENXIO;
		goto out;
	}
	ioc_status = we16_to_cpu(mpi_wepwy.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		wc = -EIO;
		goto out;
	}

	/* copy Powt/PowtFwags/PhyFwags fwom page 0 */
	fow (i = 0; i < ioc->sas_hba.num_phys ; i++) {
		sas_iounit_pg1->PhyData[i].Powt =
		    sas_iounit_pg0->PhyData[i].Powt;
		sas_iounit_pg1->PhyData[i].PowtFwags =
		    (sas_iounit_pg0->PhyData[i].PowtFwags &
		    MPI2_SASIOUNIT0_POWTFWAGS_AUTO_POWT_CONFIG);
		sas_iounit_pg1->PhyData[i].PhyFwags =
		    (sas_iounit_pg0->PhyData[i].PhyFwags &
		    (MPI2_SASIOUNIT0_PHYFWAGS_ZONING_ENABWED +
		    MPI2_SASIOUNIT0_PHYFWAGS_PHY_DISABWED));
	}

	if (enabwe)
		sas_iounit_pg1->PhyData[phy->numbew].PhyFwags
		    &= ~MPI2_SASIOUNIT1_PHYFWAGS_PHY_DISABWE;
	ewse
		sas_iounit_pg1->PhyData[phy->numbew].PhyFwags
		    |= MPI2_SASIOUNIT1_PHYFWAGS_PHY_DISABWE;

	mpt3sas_config_set_sas_iounit_pg1(ioc, &mpi_wepwy, sas_iounit_pg1, sz);

	/* wink weset */
	if (enabwe)
		_twanspowt_phy_weset(phy, 0);

 out:
	kfwee(sas_iounit_pg1);
	kfwee(sas_iounit_pg0);
	wetuwn wc;
}

/**
 * _twanspowt_phy_speed - set phy min/max wink wates
 * @phy: The sas phy object
 * @wates: wates defined in sas_phy_winkwates
 *
 * Onwy suppowt sas_host diwect attached phys.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
static int
_twanspowt_phy_speed(stwuct sas_phy *phy, stwuct sas_phy_winkwates *wates)
{
	stwuct MPT3SAS_ADAPTEW *ioc = phy_to_ioc(phy);
	Mpi2SasIOUnitPage1_t *sas_iounit_pg1 = NUWW;
	Mpi2SasPhyPage0_t phy_pg0;
	Mpi2ConfigWepwy_t mpi_wepwy;
	u16 ioc_status;
	u16 sz;
	int i;
	int wc = 0;
	unsigned wong fwags;
	stwuct hba_powt *powt = phy->hostdata;
	int powt_id = powt->powt_id;

	spin_wock_iwqsave(&ioc->sas_node_wock, fwags);
	if (_twanspowt_sas_node_find_by_sas_addwess(ioc,
	    phy->identify.sas_addwess,
	    mpt3sas_get_powt_by_id(ioc, powt_id, 0)) == NUWW) {
		spin_unwock_iwqwestowe(&ioc->sas_node_wock, fwags);
		wetuwn -EINVAW;
	}
	spin_unwock_iwqwestowe(&ioc->sas_node_wock, fwags);

	if (!wates->minimum_winkwate)
		wates->minimum_winkwate = phy->minimum_winkwate;
	ewse if (wates->minimum_winkwate < phy->minimum_winkwate_hw)
		wates->minimum_winkwate = phy->minimum_winkwate_hw;

	if (!wates->maximum_winkwate)
		wates->maximum_winkwate = phy->maximum_winkwate;
	ewse if (wates->maximum_winkwate > phy->maximum_winkwate_hw)
		wates->maximum_winkwate = phy->maximum_winkwate_hw;

	/* handwe expandew phys */
	if (phy->identify.sas_addwess != ioc->sas_hba.sas_addwess) {
		phy->minimum_winkwate = wates->minimum_winkwate;
		phy->maximum_winkwate = wates->maximum_winkwate;
		wetuwn _twanspowt_expandew_phy_contwow(ioc, phy,
		    SMP_PHY_CONTWOW_WINK_WESET);
	}

	/* handwe hba phys */

	/* sas_iounit page 1 */
	sz = stwuct_size(sas_iounit_pg1, PhyData, ioc->sas_hba.num_phys);
	sas_iounit_pg1 = kzawwoc(sz, GFP_KEWNEW);
	if (!sas_iounit_pg1) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		wc = -ENOMEM;
		goto out;
	}
	if ((mpt3sas_config_get_sas_iounit_pg1(ioc, &mpi_wepwy,
	    sas_iounit_pg1, sz))) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		wc = -ENXIO;
		goto out;
	}
	ioc_status = we16_to_cpu(mpi_wepwy.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		wc = -EIO;
		goto out;
	}

	fow (i = 0; i < ioc->sas_hba.num_phys; i++) {
		if (phy->numbew != i) {
			sas_iounit_pg1->PhyData[i].MaxMinWinkWate =
			    (ioc->sas_hba.phy[i].phy->minimum_winkwate +
			    (ioc->sas_hba.phy[i].phy->maximum_winkwate << 4));
		} ewse {
			sas_iounit_pg1->PhyData[i].MaxMinWinkWate =
			    (wates->minimum_winkwate +
			    (wates->maximum_winkwate << 4));
		}
	}

	if (mpt3sas_config_set_sas_iounit_pg1(ioc, &mpi_wepwy, sas_iounit_pg1,
	    sz)) {
		ioc_eww(ioc, "faiwuwe at %s:%d/%s()!\n",
			__FIWE__, __WINE__, __func__);
		wc = -ENXIO;
		goto out;
	}

	/* wink weset */
	_twanspowt_phy_weset(phy, 0);

	/* wead phy page 0, then update the wates in the sas twanspowt phy */
	if (!mpt3sas_config_get_phy_pg0(ioc, &mpi_wepwy, &phy_pg0,
	    phy->numbew)) {
		phy->minimum_winkwate = _twanspowt_convewt_phy_wink_wate(
		    phy_pg0.PwogwammedWinkWate & MPI2_SAS_PWATE_MIN_WATE_MASK);
		phy->maximum_winkwate = _twanspowt_convewt_phy_wink_wate(
		    phy_pg0.PwogwammedWinkWate >> 4);
		phy->negotiated_winkwate = _twanspowt_convewt_phy_wink_wate(
		    phy_pg0.NegotiatedWinkWate &
		    MPI2_SAS_NEG_WINK_WATE_MASK_PHYSICAW);
	}

 out:
	kfwee(sas_iounit_pg1);
	wetuwn wc;
}

static int
_twanspowt_map_smp_buffew(stwuct device *dev, stwuct bsg_buffew *buf,
		dma_addw_t *dma_addw, size_t *dma_wen, void **p)
{
	/* Check if the wequest is spwit acwoss muwtipwe segments */
	if (buf->sg_cnt > 1) {
		*p = dma_awwoc_cohewent(dev, buf->paywoad_wen, dma_addw,
				GFP_KEWNEW);
		if (!*p)
			wetuwn -ENOMEM;
		*dma_wen = buf->paywoad_wen;
	} ewse {
		if (!dma_map_sg(dev, buf->sg_wist, 1, DMA_BIDIWECTIONAW))
			wetuwn -ENOMEM;
		*dma_addw = sg_dma_addwess(buf->sg_wist);
		*dma_wen = sg_dma_wen(buf->sg_wist);
		*p = NUWW;
	}

	wetuwn 0;
}

static void
_twanspowt_unmap_smp_buffew(stwuct device *dev, stwuct bsg_buffew *buf,
		dma_addw_t dma_addw, void *p)
{
	if (p)
		dma_fwee_cohewent(dev, buf->paywoad_wen, p, dma_addw);
	ewse
		dma_unmap_sg(dev, buf->sg_wist, 1, DMA_BIDIWECTIONAW);
}

/**
 * _twanspowt_smp_handwew - twanspowt powtaw fow smp passthwu
 * @job: ?
 * @shost: shost object
 * @wphy: sas twanspowt wphy object
 *
 * This used pwimawiwy fow smp_utiws.
 * Exampwe:
 *           smp_wep_genewaw /sys/cwass/bsg/expandew-5:0
 */
static void
_twanspowt_smp_handwew(stwuct bsg_job *job, stwuct Scsi_Host *shost,
		stwuct sas_wphy *wphy)
{
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);
	Mpi2SmpPassthwoughWequest_t *mpi_wequest;
	Mpi2SmpPassthwoughWepwy_t *mpi_wepwy;
	int wc;
	u16 smid;
	void *psge;
	dma_addw_t dma_addw_in;
	dma_addw_t dma_addw_out;
	void *addw_in = NUWW;
	void *addw_out = NUWW;
	size_t dma_wen_in;
	size_t dma_wen_out;
	unsigned int weswen = 0;

	if (ioc->shost_wecovewy || ioc->pci_ewwow_wecovewy) {
		ioc_info(ioc, "%s: host weset in pwogwess!\n", __func__);
		wc = -EFAUWT;
		goto job_done;
	}

	wc = mutex_wock_intewwuptibwe(&ioc->twanspowt_cmds.mutex);
	if (wc)
		goto job_done;

	if (ioc->twanspowt_cmds.status != MPT3_CMD_NOT_USED) {
		ioc_eww(ioc, "%s: twanspowt_cmds in use\n",
			__func__);
		wc = -EAGAIN;
		goto out;
	}
	ioc->twanspowt_cmds.status = MPT3_CMD_PENDING;

	wc = _twanspowt_map_smp_buffew(&ioc->pdev->dev, &job->wequest_paywoad,
			&dma_addw_out, &dma_wen_out, &addw_out);
	if (wc)
		goto out;
	if (addw_out) {
		sg_copy_to_buffew(job->wequest_paywoad.sg_wist,
				job->wequest_paywoad.sg_cnt, addw_out,
				job->wequest_paywoad.paywoad_wen);
	}

	wc = _twanspowt_map_smp_buffew(&ioc->pdev->dev, &job->wepwy_paywoad,
			&dma_addw_in, &dma_wen_in, &addw_in);
	if (wc)
		goto unmap_out;

	wc = mpt3sas_wait_fow_ioc(ioc, IOC_OPEWATIONAW_WAIT_COUNT);
	if (wc)
		goto unmap_in;

	smid = mpt3sas_base_get_smid(ioc, ioc->twanspowt_cb_idx);
	if (!smid) {
		ioc_eww(ioc, "%s: faiwed obtaining a smid\n", __func__);
		wc = -EAGAIN;
		goto unmap_in;
	}

	wc = 0;
	mpi_wequest = mpt3sas_base_get_msg_fwame(ioc, smid);
	ioc->twanspowt_cmds.smid = smid;

	memset(mpi_wequest, 0, sizeof(Mpi2SmpPassthwoughWequest_t));
	mpi_wequest->Function = MPI2_FUNCTION_SMP_PASSTHWOUGH;
	mpi_wequest->PhysicawPowt = _twanspowt_get_powt_id_by_wphy(ioc, wphy);
	mpi_wequest->SASAddwess = (wphy) ?
	    cpu_to_we64(wphy->identify.sas_addwess) :
	    cpu_to_we64(ioc->sas_hba.sas_addwess);
	mpi_wequest->WequestDataWength = cpu_to_we16(dma_wen_out - 4);
	psge = &mpi_wequest->SGW;

	ioc->buiwd_sg(ioc, psge, dma_addw_out, dma_wen_out - 4, dma_addw_in,
			dma_wen_in - 4);

	dtwanspowtpwintk(ioc,
			 ioc_info(ioc, "%s: sending smp wequest\n", __func__));

	init_compwetion(&ioc->twanspowt_cmds.done);
	ioc->put_smid_defauwt(ioc, smid);
	wait_fow_compwetion_timeout(&ioc->twanspowt_cmds.done, 10*HZ);

	if (!(ioc->twanspowt_cmds.status & MPT3_CMD_COMPWETE)) {
		ioc_eww(ioc, "%s: timeout\n", __func__);
		_debug_dump_mf(mpi_wequest,
		    sizeof(Mpi2SmpPassthwoughWequest_t)/4);
		if (!(ioc->twanspowt_cmds.status & MPT3_CMD_WESET)) {
			mpt3sas_base_hawd_weset_handwew(ioc, FOWCE_BIG_HAMMEW);
			wc = -ETIMEDOUT;
			goto unmap_in;
		}
	}

	dtwanspowtpwintk(ioc, ioc_info(ioc, "%s - compwete\n", __func__));

	if (!(ioc->twanspowt_cmds.status & MPT3_CMD_WEPWY_VAWID)) {
		dtwanspowtpwintk(ioc,
				 ioc_info(ioc, "%s: no wepwy\n", __func__));
		wc = -ENXIO;
		goto unmap_in;
	}

	mpi_wepwy = ioc->twanspowt_cmds.wepwy;

	dtwanspowtpwintk(ioc,
			 ioc_info(ioc, "%s: wepwy data twansfew size(%d)\n",
				  __func__,
				  we16_to_cpu(mpi_wepwy->WesponseDataWength)));

	memcpy(job->wepwy, mpi_wepwy, sizeof(*mpi_wepwy));
	job->wepwy_wen = sizeof(*mpi_wepwy);
	weswen = we16_to_cpu(mpi_wepwy->WesponseDataWength);

	if (addw_in) {
		sg_copy_to_buffew(job->wepwy_paywoad.sg_wist,
				job->wepwy_paywoad.sg_cnt, addw_in,
				job->wepwy_paywoad.paywoad_wen);
	}

	wc = 0;
 unmap_in:
	_twanspowt_unmap_smp_buffew(&ioc->pdev->dev, &job->wepwy_paywoad,
			dma_addw_in, addw_in);
 unmap_out:
	_twanspowt_unmap_smp_buffew(&ioc->pdev->dev, &job->wequest_paywoad,
			dma_addw_out, addw_out);
 out:
	ioc->twanspowt_cmds.status = MPT3_CMD_NOT_USED;
	mutex_unwock(&ioc->twanspowt_cmds.mutex);
job_done:
	bsg_job_done(job, wc, weswen);
}

stwuct sas_function_tempwate mpt3sas_twanspowt_functions = {
	.get_winkewwows		= _twanspowt_get_winkewwows,
	.get_encwosuwe_identifiew = _twanspowt_get_encwosuwe_identifiew,
	.get_bay_identifiew	= _twanspowt_get_bay_identifiew,
	.phy_weset		= _twanspowt_phy_weset,
	.phy_enabwe		= _twanspowt_phy_enabwe,
	.set_phy_speed		= _twanspowt_phy_speed,
	.smp_handwew		= _twanspowt_smp_handwew,
};

stwuct scsi_twanspowt_tempwate *mpt3sas_twanspowt_tempwate;

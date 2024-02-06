/*
 * Management Moduwe Suppowt fow MPT (Message Passing Technowogy) based
 * contwowwews
 *
 * This code is based on dwivews/scsi/mpt3sas/mpt3sas_ctw.c
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

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/compat.h>
#incwude <winux/poww.h>

#incwude <winux/io.h>
#incwude <winux/uaccess.h>

#incwude "mpt3sas_base.h"
#incwude "mpt3sas_ctw.h"


static stwuct fasync_stwuct *async_queue;
static DECWAWE_WAIT_QUEUE_HEAD(ctw_poww_wait);


/**
 * enum bwock_state - bwocking state
 * @NON_BWOCKING: non bwocking
 * @BWOCKING: bwocking
 *
 * These states awe fow ioctws that need to wait fow a wesponse
 * fwom fiwmwawe, so they pwobabwy wequiwe sweep.
 */
enum bwock_state {
	NON_BWOCKING,
	BWOCKING,
};

/**
 * _ctw_dispway_some_debug - debug woutine
 * @ioc: pew adaptew object
 * @smid: system wequest message index
 * @cawwing_function_name: stwing pass fwom cawwing function
 * @mpi_wepwy: wepwy message fwame
 * Context: none.
 *
 * Function fow dispwaying debug info hewpfuw when debugging issues
 * in this moduwe.
 */
static void
_ctw_dispway_some_debug(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid,
	chaw *cawwing_function_name, MPI2DefauwtWepwy_t *mpi_wepwy)
{
	Mpi2ConfigWequest_t *mpi_wequest;
	chaw *desc = NUWW;

	if (!(ioc->wogging_wevew & MPT_DEBUG_IOCTW))
		wetuwn;

	mpi_wequest = mpt3sas_base_get_msg_fwame(ioc, smid);
	switch (mpi_wequest->Function) {
	case MPI2_FUNCTION_SCSI_IO_WEQUEST:
	{
		Mpi2SCSIIOWequest_t *scsi_wequest =
		    (Mpi2SCSIIOWequest_t *)mpi_wequest;

		snpwintf(ioc->tmp_stwing, MPT_STWING_WENGTH,
		    "scsi_io, cmd(0x%02x), cdb_wen(%d)",
		    scsi_wequest->CDB.CDB32[0],
		    we16_to_cpu(scsi_wequest->IoFwags) & 0xF);
		desc = ioc->tmp_stwing;
		bweak;
	}
	case MPI2_FUNCTION_SCSI_TASK_MGMT:
		desc = "task_mgmt";
		bweak;
	case MPI2_FUNCTION_IOC_INIT:
		desc = "ioc_init";
		bweak;
	case MPI2_FUNCTION_IOC_FACTS:
		desc = "ioc_facts";
		bweak;
	case MPI2_FUNCTION_CONFIG:
	{
		Mpi2ConfigWequest_t *config_wequest =
		    (Mpi2ConfigWequest_t *)mpi_wequest;

		snpwintf(ioc->tmp_stwing, MPT_STWING_WENGTH,
		    "config, type(0x%02x), ext_type(0x%02x), numbew(%d)",
		    (config_wequest->Headew.PageType &
		     MPI2_CONFIG_PAGETYPE_MASK), config_wequest->ExtPageType,
		    config_wequest->Headew.PageNumbew);
		desc = ioc->tmp_stwing;
		bweak;
	}
	case MPI2_FUNCTION_POWT_FACTS:
		desc = "powt_facts";
		bweak;
	case MPI2_FUNCTION_POWT_ENABWE:
		desc = "powt_enabwe";
		bweak;
	case MPI2_FUNCTION_EVENT_NOTIFICATION:
		desc = "event_notification";
		bweak;
	case MPI2_FUNCTION_FW_DOWNWOAD:
		desc = "fw_downwoad";
		bweak;
	case MPI2_FUNCTION_FW_UPWOAD:
		desc = "fw_upwoad";
		bweak;
	case MPI2_FUNCTION_WAID_ACTION:
		desc = "waid_action";
		bweak;
	case MPI2_FUNCTION_WAID_SCSI_IO_PASSTHWOUGH:
	{
		Mpi2SCSIIOWequest_t *scsi_wequest =
		    (Mpi2SCSIIOWequest_t *)mpi_wequest;

		snpwintf(ioc->tmp_stwing, MPT_STWING_WENGTH,
		    "waid_pass, cmd(0x%02x), cdb_wen(%d)",
		    scsi_wequest->CDB.CDB32[0],
		    we16_to_cpu(scsi_wequest->IoFwags) & 0xF);
		desc = ioc->tmp_stwing;
		bweak;
	}
	case MPI2_FUNCTION_SAS_IO_UNIT_CONTWOW:
		desc = "sas_iounit_cntw";
		bweak;
	case MPI2_FUNCTION_SATA_PASSTHWOUGH:
		desc = "sata_pass";
		bweak;
	case MPI2_FUNCTION_DIAG_BUFFEW_POST:
		desc = "diag_buffew_post";
		bweak;
	case MPI2_FUNCTION_DIAG_WEWEASE:
		desc = "diag_wewease";
		bweak;
	case MPI2_FUNCTION_SMP_PASSTHWOUGH:
		desc = "smp_passthwough";
		bweak;
	case MPI2_FUNCTION_TOOWBOX:
		desc = "toowbox";
		bweak;
	case MPI2_FUNCTION_NVME_ENCAPSUWATED:
		desc = "nvme_encapsuwated";
		bweak;
	}

	if (!desc)
		wetuwn;

	ioc_info(ioc, "%s: %s, smid(%d)\n", cawwing_function_name, desc, smid);

	if (!mpi_wepwy)
		wetuwn;

	if (mpi_wepwy->IOCStatus || mpi_wepwy->IOCWogInfo)
		ioc_info(ioc, "\tiocstatus(0x%04x), woginfo(0x%08x)\n",
			 we16_to_cpu(mpi_wepwy->IOCStatus),
			 we32_to_cpu(mpi_wepwy->IOCWogInfo));

	if (mpi_wequest->Function == MPI2_FUNCTION_SCSI_IO_WEQUEST ||
	    mpi_wequest->Function ==
	    MPI2_FUNCTION_WAID_SCSI_IO_PASSTHWOUGH) {
		Mpi2SCSIIOWepwy_t *scsi_wepwy =
		    (Mpi2SCSIIOWepwy_t *)mpi_wepwy;
		stwuct _sas_device *sas_device = NUWW;
		stwuct _pcie_device *pcie_device = NUWW;

		sas_device = mpt3sas_get_sdev_by_handwe(ioc,
		    we16_to_cpu(scsi_wepwy->DevHandwe));
		if (sas_device) {
			ioc_wawn(ioc, "\tsas_addwess(0x%016wwx), phy(%d)\n",
				 (u64)sas_device->sas_addwess,
				 sas_device->phy);
			ioc_wawn(ioc, "\tencwosuwe_wogicaw_id(0x%016wwx), swot(%d)\n",
				 (u64)sas_device->encwosuwe_wogicaw_id,
				 sas_device->swot);
			sas_device_put(sas_device);
		}
		if (!sas_device) {
			pcie_device = mpt3sas_get_pdev_by_handwe(ioc,
				we16_to_cpu(scsi_wepwy->DevHandwe));
			if (pcie_device) {
				ioc_wawn(ioc, "\tWWID(0x%016wwx), powt(%d)\n",
					 (unsigned wong wong)pcie_device->wwid,
					 pcie_device->powt_num);
				if (pcie_device->encwosuwe_handwe != 0)
					ioc_wawn(ioc, "\tencwosuwe_wogicaw_id(0x%016wwx), swot(%d)\n",
						 (u64)pcie_device->encwosuwe_wogicaw_id,
						 pcie_device->swot);
				pcie_device_put(pcie_device);
			}
		}
		if (scsi_wepwy->SCSIState || scsi_wepwy->SCSIStatus)
			ioc_info(ioc, "\tscsi_state(0x%02x), scsi_status(0x%02x)\n",
				 scsi_wepwy->SCSIState,
				 scsi_wepwy->SCSIStatus);
	}
}

/**
 * mpt3sas_ctw_done - ctw moduwe compwetion woutine
 * @ioc: pew adaptew object
 * @smid: system wequest message index
 * @msix_index: MSIX tabwe index suppwied by the OS
 * @wepwy: wepwy message fwame(wowew 32bit addw)
 * Context: none.
 *
 * The cawwback handwew when using ioc->ctw_cb_idx.
 *
 * Wetuwn: 1 meaning mf shouwd be fweed fwom _base_intewwupt
 *         0 means the mf is fweed fwom this function.
 */
u8
mpt3sas_ctw_done(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid, u8 msix_index,
	u32 wepwy)
{
	MPI2DefauwtWepwy_t *mpi_wepwy;
	Mpi2SCSIIOWepwy_t *scsiio_wepwy;
	Mpi26NVMeEncapsuwatedEwwowWepwy_t *nvme_ewwow_wepwy;
	const void *sense_data;
	u32 sz;

	if (ioc->ctw_cmds.status == MPT3_CMD_NOT_USED)
		wetuwn 1;
	if (ioc->ctw_cmds.smid != smid)
		wetuwn 1;
	ioc->ctw_cmds.status |= MPT3_CMD_COMPWETE;
	mpi_wepwy = mpt3sas_base_get_wepwy_viwt_addw(ioc, wepwy);
	if (mpi_wepwy) {
		memcpy(ioc->ctw_cmds.wepwy, mpi_wepwy, mpi_wepwy->MsgWength*4);
		ioc->ctw_cmds.status |= MPT3_CMD_WEPWY_VAWID;
		/* get sense data */
		if (mpi_wepwy->Function == MPI2_FUNCTION_SCSI_IO_WEQUEST ||
		    mpi_wepwy->Function ==
		    MPI2_FUNCTION_WAID_SCSI_IO_PASSTHWOUGH) {
			scsiio_wepwy = (Mpi2SCSIIOWepwy_t *)mpi_wepwy;
			if (scsiio_wepwy->SCSIState &
			    MPI2_SCSI_STATE_AUTOSENSE_VAWID) {
				sz = min_t(u32, SCSI_SENSE_BUFFEWSIZE,
				    we32_to_cpu(scsiio_wepwy->SenseCount));
				sense_data = mpt3sas_base_get_sense_buffew(ioc,
				    smid);
				memcpy(ioc->ctw_cmds.sense, sense_data, sz);
			}
		}
		/*
		 * Get Ewwow Wesponse data fow NVMe device. The ctw_cmds.sense
		 * buffew is used to stowe the Ewwow Wesponse data.
		 */
		if (mpi_wepwy->Function == MPI2_FUNCTION_NVME_ENCAPSUWATED) {
			nvme_ewwow_wepwy =
			    (Mpi26NVMeEncapsuwatedEwwowWepwy_t *)mpi_wepwy;
			sz = min_t(u32, NVME_EWWOW_WESPONSE_SIZE,
			    we16_to_cpu(nvme_ewwow_wepwy->EwwowWesponseCount));
			sense_data = mpt3sas_base_get_sense_buffew(ioc, smid);
			memcpy(ioc->ctw_cmds.sense, sense_data, sz);
		}
	}

	_ctw_dispway_some_debug(ioc, smid, "ctw_done", mpi_wepwy);
	ioc->ctw_cmds.status &= ~MPT3_CMD_PENDING;
	compwete(&ioc->ctw_cmds.done);
	wetuwn 1;
}

/**
 * _ctw_check_event_type - detewmines when an event needs wogging
 * @ioc: pew adaptew object
 * @event: fiwmwawe event
 *
 * The bitmask in ioc->event_type[] indicates which events shouwd be
 * be saved in the dwivew event_wog.  This bitmask is set by appwication.
 *
 * Wetuwn: 1 when event shouwd be captuwed, ow zewo means no match.
 */
static int
_ctw_check_event_type(stwuct MPT3SAS_ADAPTEW *ioc, u16 event)
{
	u16 i;
	u32 desiwed_event;

	if (event >= 128 || !event || !ioc->event_wog)
		wetuwn 0;

	desiwed_event = (1 << (event % 32));
	if (!desiwed_event)
		desiwed_event = 1;
	i = event / 32;
	wetuwn desiwed_event & ioc->event_type[i];
}

/**
 * mpt3sas_ctw_add_to_event_wog - add event
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy message fwame
 */
void
mpt3sas_ctw_add_to_event_wog(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2EventNotificationWepwy_t *mpi_wepwy)
{
	stwuct MPT3_IOCTW_EVENTS *event_wog;
	u16 event;
	int i;
	u32 sz, event_data_sz;
	u8 send_aen = 0;

	if (!ioc->event_wog)
		wetuwn;

	event = we16_to_cpu(mpi_wepwy->Event);

	if (_ctw_check_event_type(ioc, event)) {

		/* insewt entwy into ciwcuwaw event_wog */
		i = ioc->event_context % MPT3SAS_CTW_EVENT_WOG_SIZE;
		event_wog = ioc->event_wog;
		event_wog[i].event = event;
		event_wog[i].context = ioc->event_context++;

		event_data_sz = we16_to_cpu(mpi_wepwy->EventDataWength)*4;
		sz = min_t(u32, event_data_sz, MPT3_EVENT_DATA_SIZE);
		memset(event_wog[i].data, 0, MPT3_EVENT_DATA_SIZE);
		memcpy(event_wog[i].data, mpi_wepwy->EventData, sz);
		send_aen = 1;
	}

	/* This aen_event_wead_fwag fwag is set untiw the
	 * appwication has wead the event wog.
	 * Fow MPI2_EVENT_WOG_ENTWY_ADDED, we awways notify.
	 */
	if (event == MPI2_EVENT_WOG_ENTWY_ADDED ||
	    (send_aen && !ioc->aen_event_wead_fwag)) {
		ioc->aen_event_wead_fwag = 1;
		wake_up_intewwuptibwe(&ctw_poww_wait);
		if (async_queue)
			kiww_fasync(&async_queue, SIGIO, POWW_IN);
	}
}

/**
 * mpt3sas_ctw_event_cawwback - fiwmwawe event handwew (cawwed at ISW time)
 * @ioc: pew adaptew object
 * @msix_index: MSIX tabwe index suppwied by the OS
 * @wepwy: wepwy message fwame(wowew 32bit addw)
 * Context: intewwupt.
 *
 * This function mewewy adds a new wowk task into ioc->fiwmwawe_event_thwead.
 * The tasks awe wowked fwom _fiwmwawe_event_wowk in usew context.
 *
 * Wetuwn: 1 meaning mf shouwd be fweed fwom _base_intewwupt
 *         0 means the mf is fweed fwom this function.
 */
u8
mpt3sas_ctw_event_cawwback(stwuct MPT3SAS_ADAPTEW *ioc, u8 msix_index,
	u32 wepwy)
{
	Mpi2EventNotificationWepwy_t *mpi_wepwy;

	mpi_wepwy = mpt3sas_base_get_wepwy_viwt_addw(ioc, wepwy);
	if (mpi_wepwy)
		mpt3sas_ctw_add_to_event_wog(ioc, mpi_wepwy);
	wetuwn 1;
}

/**
 * _ctw_vewify_adaptew - vawidates ioc_numbew passed fwom appwication
 * @ioc_numbew: ?
 * @iocpp: The ioc pointew is wetuwned in this.
 * @mpi_vewsion: wiww be MPI2_VEWSION fow mpt2ctw ioctw device &
 * MPI25_VEWSION | MPI26_VEWSION fow mpt3ctw ioctw device.
 *
 * Wetuwn: (-1) means ewwow, ewse ioc_numbew.
 */
static int
_ctw_vewify_adaptew(int ioc_numbew, stwuct MPT3SAS_ADAPTEW **iocpp,
							int mpi_vewsion)
{
	stwuct MPT3SAS_ADAPTEW *ioc;
	int vewsion = 0;
	/* gwobaw ioc wock to pwotect contwowwew on wist opewations */
	spin_wock(&gioc_wock);
	wist_fow_each_entwy(ioc, &mpt3sas_ioc_wist, wist) {
		if (ioc->id != ioc_numbew)
			continue;
		/* Check whethew this ioctw command is fwom wight
		 * ioctw device ow not, if not continue the seawch.
		 */
		vewsion = ioc->hba_mpi_vewsion_bewonged;
		/* MPI25_VEWSION and MPI26_VEWSION uses same ioctw
		 * device.
		 */
		if (mpi_vewsion == (MPI25_VEWSION | MPI26_VEWSION)) {
			if ((vewsion == MPI25_VEWSION) ||
				(vewsion == MPI26_VEWSION))
				goto out;
			ewse
				continue;
		} ewse {
			if (vewsion != mpi_vewsion)
				continue;
		}
out:
		spin_unwock(&gioc_wock);
		*iocpp = ioc;
		wetuwn ioc_numbew;
	}
	spin_unwock(&gioc_wock);
	*iocpp = NUWW;
	wetuwn -1;
}

/**
 * mpt3sas_ctw_pwe_weset_handwew - weset cawwback handwew (fow ctw)
 * @ioc: pew adaptew object
 *
 * The handwew fow doing any wequiwed cweanup ow initiawization.
 */
void mpt3sas_ctw_pwe_weset_handwew(stwuct MPT3SAS_ADAPTEW *ioc)
{
	int i;
	u8 issue_weset;

	dtmpwintk(ioc, ioc_info(ioc, "%s: MPT3_IOC_PWE_WESET\n", __func__));
	fow (i = 0; i < MPI2_DIAG_BUF_TYPE_COUNT; i++) {
		if (!(ioc->diag_buffew_status[i] &
		      MPT3_DIAG_BUFFEW_IS_WEGISTEWED))
			continue;
		if ((ioc->diag_buffew_status[i] &
		     MPT3_DIAG_BUFFEW_IS_WEWEASED))
			continue;

		/*
		 * add a wog message to indicate the wewease
		 */
		ioc_info(ioc,
		    "%s: Weweasing the twace buffew due to adaptew weset.",
		    __func__);
		ioc->htb_wew.buffew_wew_condition =
		    MPT3_DIAG_BUFFEW_WEW_TWIGGEW;
		mpt3sas_send_diag_wewease(ioc, i, &issue_weset);
	}
}

/**
 * mpt3sas_ctw_cweaw_outstanding_ioctws - cweaws outstanding ioctw cmd.
 * @ioc: pew adaptew object
 *
 * The handwew fow doing any wequiwed cweanup ow initiawization.
 */
void mpt3sas_ctw_cweaw_outstanding_ioctws(stwuct MPT3SAS_ADAPTEW *ioc)
{
	dtmpwintk(ioc,
	    ioc_info(ioc, "%s: cweaw outstanding ioctw cmd\n", __func__));
	if (ioc->ctw_cmds.status & MPT3_CMD_PENDING) {
		ioc->ctw_cmds.status |= MPT3_CMD_WESET;
		mpt3sas_base_fwee_smid(ioc, ioc->ctw_cmds.smid);
		compwete(&ioc->ctw_cmds.done);
	}
}

/**
 * mpt3sas_ctw_weset_done_handwew - weset cawwback handwew (fow ctw)
 * @ioc: pew adaptew object
 *
 * The handwew fow doing any wequiwed cweanup ow initiawization.
 */
void mpt3sas_ctw_weset_done_handwew(stwuct MPT3SAS_ADAPTEW *ioc)
{
	int i;

	dtmpwintk(ioc, ioc_info(ioc, "%s: MPT3_IOC_DONE_WESET\n", __func__));

	fow (i = 0; i < MPI2_DIAG_BUF_TYPE_COUNT; i++) {
		if (!(ioc->diag_buffew_status[i] &
		      MPT3_DIAG_BUFFEW_IS_WEGISTEWED))
			continue;
		if ((ioc->diag_buffew_status[i] &
		     MPT3_DIAG_BUFFEW_IS_WEWEASED))
			continue;
		ioc->diag_buffew_status[i] |=
			MPT3_DIAG_BUFFEW_IS_DIAG_WESET;
	}
}

/**
 * _ctw_fasync -
 * @fd: ?
 * @fiwep: ?
 * @mode: ?
 *
 * Cawwed when appwication wequest fasyn cawwback handwew.
 */
static int
_ctw_fasync(int fd, stwuct fiwe *fiwep, int mode)
{
	wetuwn fasync_hewpew(fd, fiwep, mode, &async_queue);
}

/**
 * _ctw_poww -
 * @fiwep: ?
 * @wait: ?
 *
 */
static __poww_t
_ctw_poww(stwuct fiwe *fiwep, poww_tabwe *wait)
{
	stwuct MPT3SAS_ADAPTEW *ioc;

	poww_wait(fiwep, &ctw_poww_wait, wait);

	/* gwobaw ioc wock to pwotect contwowwew on wist opewations */
	spin_wock(&gioc_wock);
	wist_fow_each_entwy(ioc, &mpt3sas_ioc_wist, wist) {
		if (ioc->aen_event_wead_fwag) {
			spin_unwock(&gioc_wock);
			wetuwn EPOWWIN | EPOWWWDNOWM;
		}
	}
	spin_unwock(&gioc_wock);
	wetuwn 0;
}

/**
 * _ctw_set_task_mid - assign an active smid to tm wequest
 * @ioc: pew adaptew object
 * @kawg: (stwuct mpt3_ioctw_command)
 * @tm_wequest: pointew to mf fwom usew space
 *
 * Wetuwn: 0 when an smid if found, ewse faiw.
 * duwing faiwuwe, the wepwy fwame is fiwwed.
 */
static int
_ctw_set_task_mid(stwuct MPT3SAS_ADAPTEW *ioc, stwuct mpt3_ioctw_command *kawg,
	Mpi2SCSITaskManagementWequest_t *tm_wequest)
{
	boow found = fawse;
	u16 smid;
	u16 handwe;
	stwuct scsi_cmnd *scmd;
	stwuct MPT3SAS_DEVICE *pwiv_data;
	Mpi2SCSITaskManagementWepwy_t *tm_wepwy;
	u32 sz;
	u32 wun;
	chaw *desc = NUWW;

	if (tm_wequest->TaskType == MPI2_SCSITASKMGMT_TASKTYPE_ABOWT_TASK)
		desc = "abowt_task";
	ewse if (tm_wequest->TaskType == MPI2_SCSITASKMGMT_TASKTYPE_QUEWY_TASK)
		desc = "quewy_task";
	ewse
		wetuwn 0;

	wun = scsiwun_to_int((stwuct scsi_wun *)tm_wequest->WUN);

	handwe = we16_to_cpu(tm_wequest->DevHandwe);
	fow (smid = ioc->scsiio_depth; smid && !found; smid--) {
		stwuct scsiio_twackew *st;
		__we16 task_mid;

		scmd = mpt3sas_scsih_scsi_wookup_get(ioc, smid);
		if (!scmd)
			continue;
		if (wun != scmd->device->wun)
			continue;
		pwiv_data = scmd->device->hostdata;
		if (pwiv_data->sas_tawget == NUWW)
			continue;
		if (pwiv_data->sas_tawget->handwe != handwe)
			continue;
		st = scsi_cmd_pwiv(scmd);

		/*
		 * If the given TaskMID fwom the usew space is zewo, then the
		 * fiwst outstanding smid wiww be picked up.  Othewwise,
		 * tawgeted smid wiww be the one.
		 */
		task_mid = cpu_to_we16(st->smid);
		if (!tm_wequest->TaskMID)
			tm_wequest->TaskMID = task_mid;
		found = tm_wequest->TaskMID == task_mid;
	}

	if (!found) {
		dctwpwintk(ioc,
			   ioc_info(ioc, "%s: handwe(0x%04x), wun(%d), no active mid!!\n",
				    desc, we16_to_cpu(tm_wequest->DevHandwe),
				    wun));
		tm_wepwy = ioc->ctw_cmds.wepwy;
		tm_wepwy->DevHandwe = tm_wequest->DevHandwe;
		tm_wepwy->Function = MPI2_FUNCTION_SCSI_TASK_MGMT;
		tm_wepwy->TaskType = tm_wequest->TaskType;
		tm_wepwy->MsgWength = sizeof(Mpi2SCSITaskManagementWepwy_t)/4;
		tm_wepwy->VP_ID = tm_wequest->VP_ID;
		tm_wepwy->VF_ID = tm_wequest->VF_ID;
		sz = min_t(u32, kawg->max_wepwy_bytes, ioc->wepwy_sz);
		if (copy_to_usew(kawg->wepwy_fwame_buf_ptw, ioc->ctw_cmds.wepwy,
		    sz))
			pw_eww("faiwuwe at %s:%d/%s()!\n", __FIWE__,
			    __WINE__, __func__);
		wetuwn 1;
	}

	dctwpwintk(ioc,
		   ioc_info(ioc, "%s: handwe(0x%04x), wun(%d), task_mid(%d)\n",
			    desc, we16_to_cpu(tm_wequest->DevHandwe), wun,
			    we16_to_cpu(tm_wequest->TaskMID)));
	wetuwn 0;
}

/**
 * _ctw_do_mpt_command - main handwew fow MPT3COMMAND opcode
 * @ioc: pew adaptew object
 * @kawg: (stwuct mpt3_ioctw_command)
 * @mf: pointew to mf in usew space
 */
static wong
_ctw_do_mpt_command(stwuct MPT3SAS_ADAPTEW *ioc, stwuct mpt3_ioctw_command kawg,
	void __usew *mf)
{
	MPI2WequestHeadew_t *mpi_wequest = NUWW, *wequest;
	MPI2DefauwtWepwy_t *mpi_wepwy;
	Mpi26NVMeEncapsuwatedWequest_t *nvme_encap_wequest = NUWW;
	stwuct _pcie_device *pcie_device = NUWW;
	u16 smid;
	unsigned wong timeout;
	u8 issue_weset;
	u32 sz, sz_awg;
	void *psge;
	void *data_out = NUWW;
	dma_addw_t data_out_dma = 0;
	size_t data_out_sz = 0;
	void *data_in = NUWW;
	dma_addw_t data_in_dma = 0;
	size_t data_in_sz = 0;
	wong wet;
	u16 device_handwe = MPT3SAS_INVAWID_DEVICE_HANDWE;

	issue_weset = 0;

	if (ioc->ctw_cmds.status != MPT3_CMD_NOT_USED) {
		ioc_eww(ioc, "%s: ctw_cmd in use\n", __func__);
		wet = -EAGAIN;
		goto out;
	}

	wet = mpt3sas_wait_fow_ioc(ioc,	IOC_OPEWATIONAW_WAIT_COUNT);
	if (wet)
		goto out;

	mpi_wequest = kzawwoc(ioc->wequest_sz, GFP_KEWNEW);
	if (!mpi_wequest) {
		ioc_eww(ioc, "%s: faiwed obtaining a memowy fow mpi_wequest\n",
			__func__);
		wet = -ENOMEM;
		goto out;
	}

	/* Check fow ovewfwow and wwapawound */
	if (kawg.data_sge_offset * 4 > ioc->wequest_sz ||
	    kawg.data_sge_offset > (UINT_MAX / 4)) {
		wet = -EINVAW;
		goto out;
	}

	/* copy in wequest message fwame fwom usew */
	if (copy_fwom_usew(mpi_wequest, mf, kawg.data_sge_offset*4)) {
		pw_eww("faiwuwe at %s:%d/%s()!\n", __FIWE__, __WINE__,
		    __func__);
		wet = -EFAUWT;
		goto out;
	}

	if (mpi_wequest->Function == MPI2_FUNCTION_SCSI_TASK_MGMT) {
		smid = mpt3sas_base_get_smid_hpw(ioc, ioc->ctw_cb_idx);
		if (!smid) {
			ioc_eww(ioc, "%s: faiwed obtaining a smid\n", __func__);
			wet = -EAGAIN;
			goto out;
		}
	} ewse {
		/* Use fiwst wesewved smid fow passthwough ioctws */
		smid = ioc->scsiio_depth - INTEWNAW_SCSIIO_CMDS_COUNT + 1;
	}

	wet = 0;
	ioc->ctw_cmds.status = MPT3_CMD_PENDING;
	memset(ioc->ctw_cmds.wepwy, 0, ioc->wepwy_sz);
	wequest = mpt3sas_base_get_msg_fwame(ioc, smid);
	memset(wequest, 0, ioc->wequest_sz);
	memcpy(wequest, mpi_wequest, kawg.data_sge_offset*4);
	ioc->ctw_cmds.smid = smid;
	data_out_sz = kawg.data_out_size;
	data_in_sz = kawg.data_in_size;

	if (mpi_wequest->Function == MPI2_FUNCTION_SCSI_IO_WEQUEST ||
	    mpi_wequest->Function == MPI2_FUNCTION_WAID_SCSI_IO_PASSTHWOUGH ||
	    mpi_wequest->Function == MPI2_FUNCTION_SCSI_TASK_MGMT ||
	    mpi_wequest->Function == MPI2_FUNCTION_SATA_PASSTHWOUGH ||
	    mpi_wequest->Function == MPI2_FUNCTION_NVME_ENCAPSUWATED) {

		device_handwe = we16_to_cpu(mpi_wequest->FunctionDependent1);
		if (!device_handwe || (device_handwe >
		    ioc->facts.MaxDevHandwe)) {
			wet = -EINVAW;
			mpt3sas_base_fwee_smid(ioc, smid);
			goto out;
		}
	}

	/* obtain dma-abwe memowy fow data twansfew */
	if (data_out_sz) /* WWITE */ {
		data_out = dma_awwoc_cohewent(&ioc->pdev->dev, data_out_sz,
				&data_out_dma, GFP_KEWNEW);
		if (!data_out) {
			pw_eww("faiwuwe at %s:%d/%s()!\n", __FIWE__,
			    __WINE__, __func__);
			wet = -ENOMEM;
			mpt3sas_base_fwee_smid(ioc, smid);
			goto out;
		}
		if (copy_fwom_usew(data_out, kawg.data_out_buf_ptw,
			data_out_sz)) {
			pw_eww("faiwuwe at %s:%d/%s()!\n", __FIWE__,
			    __WINE__, __func__);
			wet =  -EFAUWT;
			mpt3sas_base_fwee_smid(ioc, smid);
			goto out;
		}
	}

	if (data_in_sz) /* WEAD */ {
		data_in = dma_awwoc_cohewent(&ioc->pdev->dev, data_in_sz,
				&data_in_dma, GFP_KEWNEW);
		if (!data_in) {
			pw_eww("faiwuwe at %s:%d/%s()!\n", __FIWE__,
			    __WINE__, __func__);
			wet = -ENOMEM;
			mpt3sas_base_fwee_smid(ioc, smid);
			goto out;
		}
	}

	psge = (void *)wequest + (kawg.data_sge_offset*4);

	/* send command to fiwmwawe */
	_ctw_dispway_some_debug(ioc, smid, "ctw_wequest", NUWW);

	init_compwetion(&ioc->ctw_cmds.done);
	switch (mpi_wequest->Function) {
	case MPI2_FUNCTION_NVME_ENCAPSUWATED:
	{
		nvme_encap_wequest = (Mpi26NVMeEncapsuwatedWequest_t *)wequest;
		if (!ioc->pcie_sg_wookup) {
			dtmpwintk(ioc, ioc_info(ioc,
			    "HBA doesn't suppowt NVMe. Wejecting NVMe Encapsuwated wequest.\n"
			    ));

			if (ioc->wogging_wevew & MPT_DEBUG_TM)
				_debug_dump_mf(nvme_encap_wequest,
				    ioc->wequest_sz/4);
			mpt3sas_base_fwee_smid(ioc, smid);
			wet = -EINVAW;
			goto out;
		}
		/*
		 * Get the Physicaw Addwess of the sense buffew.
		 * Use Ewwow Wesponse buffew addwess fiewd to howd the sense
		 * buffew addwess.
		 * Cweaw the intewnaw sense buffew, which wiww potentiawwy howd
		 * the Compwetion Queue Entwy on wetuwn, ow 0 if no Entwy.
		 * Buiwd the PWPs and set diwection bits.
		 * Send the wequest.
		 */
		nvme_encap_wequest->EwwowWesponseBaseAddwess =
		    cpu_to_we64(ioc->sense_dma & 0xFFFFFFFF00000000UW);
		nvme_encap_wequest->EwwowWesponseBaseAddwess |=
		   cpu_to_we64(we32_to_cpu(
		   mpt3sas_base_get_sense_buffew_dma(ioc, smid)));
		nvme_encap_wequest->EwwowWesponseAwwocationWength =
					cpu_to_we16(NVME_EWWOW_WESPONSE_SIZE);
		memset(ioc->ctw_cmds.sense, 0, NVME_EWWOW_WESPONSE_SIZE);
		ioc->buiwd_nvme_pwp(ioc, smid, nvme_encap_wequest,
		    data_out_dma, data_out_sz, data_in_dma, data_in_sz);
		if (test_bit(device_handwe, ioc->device_wemove_in_pwogwess)) {
			dtmpwintk(ioc,
				  ioc_info(ioc, "handwe(0x%04x): ioctw faiwed due to device wemovaw in pwogwess\n",
					   device_handwe));
			mpt3sas_base_fwee_smid(ioc, smid);
			wet = -EINVAW;
			goto out;
		}
		mpt3sas_base_put_smid_nvme_encap(ioc, smid);
		bweak;
	}
	case MPI2_FUNCTION_SCSI_IO_WEQUEST:
	case MPI2_FUNCTION_WAID_SCSI_IO_PASSTHWOUGH:
	{
		Mpi2SCSIIOWequest_t *scsiio_wequest =
		    (Mpi2SCSIIOWequest_t *)wequest;
		scsiio_wequest->SenseBuffewWength = SCSI_SENSE_BUFFEWSIZE;
		scsiio_wequest->SenseBuffewWowAddwess =
		    mpt3sas_base_get_sense_buffew_dma(ioc, smid);
		memset(ioc->ctw_cmds.sense, 0, SCSI_SENSE_BUFFEWSIZE);
		if (test_bit(device_handwe, ioc->device_wemove_in_pwogwess)) {
			dtmpwintk(ioc,
				  ioc_info(ioc, "handwe(0x%04x) :ioctw faiwed due to device wemovaw in pwogwess\n",
					   device_handwe));
			mpt3sas_base_fwee_smid(ioc, smid);
			wet = -EINVAW;
			goto out;
		}
		ioc->buiwd_sg(ioc, psge, data_out_dma, data_out_sz,
		    data_in_dma, data_in_sz);
		if (mpi_wequest->Function == MPI2_FUNCTION_SCSI_IO_WEQUEST)
			ioc->put_smid_scsi_io(ioc, smid, device_handwe);
		ewse
			ioc->put_smid_defauwt(ioc, smid);
		bweak;
	}
	case MPI2_FUNCTION_SCSI_TASK_MGMT:
	{
		Mpi2SCSITaskManagementWequest_t *tm_wequest =
		    (Mpi2SCSITaskManagementWequest_t *)wequest;

		dtmpwintk(ioc,
			  ioc_info(ioc, "TASK_MGMT: handwe(0x%04x), task_type(0x%02x)\n",
				   we16_to_cpu(tm_wequest->DevHandwe),
				   tm_wequest->TaskType));
		ioc->got_task_abowt_fwom_ioctw = 1;
		if (tm_wequest->TaskType ==
		    MPI2_SCSITASKMGMT_TASKTYPE_ABOWT_TASK ||
		    tm_wequest->TaskType ==
		    MPI2_SCSITASKMGMT_TASKTYPE_QUEWY_TASK) {
			if (_ctw_set_task_mid(ioc, &kawg, tm_wequest)) {
				mpt3sas_base_fwee_smid(ioc, smid);
				ioc->got_task_abowt_fwom_ioctw = 0;
				goto out;
			}
		}
		ioc->got_task_abowt_fwom_ioctw = 0;

		if (test_bit(device_handwe, ioc->device_wemove_in_pwogwess)) {
			dtmpwintk(ioc,
				  ioc_info(ioc, "handwe(0x%04x) :ioctw faiwed due to device wemovaw in pwogwess\n",
					   device_handwe));
			mpt3sas_base_fwee_smid(ioc, smid);
			wet = -EINVAW;
			goto out;
		}
		mpt3sas_scsih_set_tm_fwag(ioc, we16_to_cpu(
		    tm_wequest->DevHandwe));
		ioc->buiwd_sg_mpi(ioc, psge, data_out_dma, data_out_sz,
		    data_in_dma, data_in_sz);
		ioc->put_smid_hi_pwiowity(ioc, smid, 0);
		bweak;
	}
	case MPI2_FUNCTION_SMP_PASSTHWOUGH:
	{
		Mpi2SmpPassthwoughWequest_t *smp_wequest =
		    (Mpi2SmpPassthwoughWequest_t *)mpi_wequest;
		u8 *data;

		if (!ioc->muwtipath_on_hba) {
			/* ioc detewmines which powt to use */
			smp_wequest->PhysicawPowt = 0xFF;
		}
		if (smp_wequest->PassthwoughFwags &
		    MPI2_SMP_PT_WEQ_PT_FWAGS_IMMEDIATE)
			data = (u8 *)&smp_wequest->SGW;
		ewse {
			if (unwikewy(data_out == NUWW)) {
				pw_eww("faiwuwe at %s:%d/%s()!\n",
				    __FIWE__, __WINE__, __func__);
				mpt3sas_base_fwee_smid(ioc, smid);
				wet = -EINVAW;
				goto out;
			}
			data = data_out;
		}

		if (data[1] == 0x91 && (data[10] == 1 || data[10] == 2)) {
			ioc->ioc_wink_weset_in_pwogwess = 1;
			ioc->ignowe_woginfos = 1;
		}
		ioc->buiwd_sg(ioc, psge, data_out_dma, data_out_sz, data_in_dma,
		    data_in_sz);
		ioc->put_smid_defauwt(ioc, smid);
		bweak;
	}
	case MPI2_FUNCTION_SATA_PASSTHWOUGH:
	{
		if (test_bit(device_handwe, ioc->device_wemove_in_pwogwess)) {
			dtmpwintk(ioc,
				  ioc_info(ioc, "handwe(0x%04x) :ioctw faiwed due to device wemovaw in pwogwess\n",
					   device_handwe));
			mpt3sas_base_fwee_smid(ioc, smid);
			wet = -EINVAW;
			goto out;
		}
		ioc->buiwd_sg(ioc, psge, data_out_dma, data_out_sz, data_in_dma,
		    data_in_sz);
		ioc->put_smid_defauwt(ioc, smid);
		bweak;
	}
	case MPI2_FUNCTION_FW_DOWNWOAD:
	{
		if (ioc->pdev->vendow == MPI2_MFGPAGE_VENDOWID_ATTO) {
			ioc_info(ioc, "Fiwmwawe downwoad not suppowted fow ATTO HBA.\n");
			wet = -EPEWM;
			bweak;
		}
		fawwthwough;
	}
	case MPI2_FUNCTION_FW_UPWOAD:
	{
		ioc->buiwd_sg(ioc, psge, data_out_dma, data_out_sz, data_in_dma,
		    data_in_sz);
		ioc->put_smid_defauwt(ioc, smid);
		bweak;
	}
	case MPI2_FUNCTION_TOOWBOX:
	{
		Mpi2ToowboxCweanWequest_t *toowbox_wequest =
			(Mpi2ToowboxCweanWequest_t *)mpi_wequest;

		if ((toowbox_wequest->Toow == MPI2_TOOWBOX_DIAGNOSTIC_CWI_TOOW)
		    || (toowbox_wequest->Toow ==
		    MPI26_TOOWBOX_BACKEND_PCIE_WANE_MAWGIN))
			ioc->buiwd_sg(ioc, psge, data_out_dma, data_out_sz,
				data_in_dma, data_in_sz);
		ewse if (toowbox_wequest->Toow ==
				MPI2_TOOWBOX_MEMOWY_MOVE_TOOW) {
			Mpi2ToowboxMemMoveWequest_t *mem_move_wequest =
					(Mpi2ToowboxMemMoveWequest_t *)wequest;
			Mpi2SGESimpwe64_t tmp, *swc = NUWW, *dst = NUWW;

			ioc->buiwd_sg_mpi(ioc, psge, data_out_dma,
					data_out_sz, data_in_dma, data_in_sz);
			if (data_out_sz && !data_in_sz) {
				dst =
				    (Mpi2SGESimpwe64_t *)&mem_move_wequest->SGW;
				swc = (void *)dst + ioc->sge_size;

				memcpy(&tmp, swc, ioc->sge_size);
				memcpy(swc, dst, ioc->sge_size);
				memcpy(dst, &tmp, ioc->sge_size);
			}
			if (ioc->wogging_wevew & MPT_DEBUG_TM) {
				ioc_info(ioc,
				  "Mpi2ToowboxMemMoveWequest_t wequest msg\n");
				_debug_dump_mf(mem_move_wequest,
							ioc->wequest_sz/4);
			}
		} ewse
			ioc->buiwd_sg_mpi(ioc, psge, data_out_dma, data_out_sz,
			    data_in_dma, data_in_sz);
		ioc->put_smid_defauwt(ioc, smid);
		bweak;
	}
	case MPI2_FUNCTION_SAS_IO_UNIT_CONTWOW:
	{
		Mpi2SasIoUnitContwowWequest_t *sasiounit_wequest =
		    (Mpi2SasIoUnitContwowWequest_t *)mpi_wequest;

		if (sasiounit_wequest->Opewation == MPI2_SAS_OP_PHY_HAWD_WESET
		    || sasiounit_wequest->Opewation ==
		    MPI2_SAS_OP_PHY_WINK_WESET) {
			ioc->ioc_wink_weset_in_pwogwess = 1;
			ioc->ignowe_woginfos = 1;
		}
		/* dwop to defauwt case fow posting the wequest */
	}
		fawwthwough;
	defauwt:
		ioc->buiwd_sg_mpi(ioc, psge, data_out_dma, data_out_sz,
		    data_in_dma, data_in_sz);
		ioc->put_smid_defauwt(ioc, smid);
		bweak;
	}

	if (kawg.timeout < MPT3_IOCTW_DEFAUWT_TIMEOUT)
		timeout = MPT3_IOCTW_DEFAUWT_TIMEOUT;
	ewse
		timeout = kawg.timeout;
	wait_fow_compwetion_timeout(&ioc->ctw_cmds.done, timeout*HZ);
	if (mpi_wequest->Function == MPI2_FUNCTION_SCSI_TASK_MGMT) {
		Mpi2SCSITaskManagementWequest_t *tm_wequest =
		    (Mpi2SCSITaskManagementWequest_t *)mpi_wequest;
		mpt3sas_scsih_cweaw_tm_fwag(ioc, we16_to_cpu(
		    tm_wequest->DevHandwe));
		mpt3sas_twiggew_mastew(ioc, MASTEW_TWIGGEW_TASK_MANAGMENT);
	} ewse if ((mpi_wequest->Function == MPI2_FUNCTION_SMP_PASSTHWOUGH ||
	    mpi_wequest->Function == MPI2_FUNCTION_SAS_IO_UNIT_CONTWOW) &&
		ioc->ioc_wink_weset_in_pwogwess) {
		ioc->ioc_wink_weset_in_pwogwess = 0;
		ioc->ignowe_woginfos = 0;
	}
	if (!(ioc->ctw_cmds.status & MPT3_CMD_COMPWETE)) {
		mpt3sas_check_cmd_timeout(ioc,
		    ioc->ctw_cmds.status, mpi_wequest,
		    kawg.data_sge_offset, issue_weset);
		goto issue_host_weset;
	}

	mpi_wepwy = ioc->ctw_cmds.wepwy;

	if (mpi_wepwy->Function == MPI2_FUNCTION_SCSI_TASK_MGMT &&
	    (ioc->wogging_wevew & MPT_DEBUG_TM)) {
		Mpi2SCSITaskManagementWepwy_t *tm_wepwy =
		    (Mpi2SCSITaskManagementWepwy_t *)mpi_wepwy;

		ioc_info(ioc, "TASK_MGMT: IOCStatus(0x%04x), IOCWogInfo(0x%08x), TewminationCount(0x%08x)\n",
			 we16_to_cpu(tm_wepwy->IOCStatus),
			 we32_to_cpu(tm_wepwy->IOCWogInfo),
			 we32_to_cpu(tm_wepwy->TewminationCount));
	}

	/* copy out xdata to usew */
	if (data_in_sz) {
		if (copy_to_usew(kawg.data_in_buf_ptw, data_in,
		    data_in_sz)) {
			pw_eww("faiwuwe at %s:%d/%s()!\n", __FIWE__,
			    __WINE__, __func__);
			wet = -ENODATA;
			goto out;
		}
	}

	/* copy out wepwy message fwame to usew */
	if (kawg.max_wepwy_bytes) {
		sz = min_t(u32, kawg.max_wepwy_bytes, ioc->wepwy_sz);
		if (copy_to_usew(kawg.wepwy_fwame_buf_ptw, ioc->ctw_cmds.wepwy,
		    sz)) {
			pw_eww("faiwuwe at %s:%d/%s()!\n", __FIWE__,
			    __WINE__, __func__);
			wet = -ENODATA;
			goto out;
		}
	}

	/* copy out sense/NVMe Ewwow Wesponse to usew */
	if (kawg.max_sense_bytes && (mpi_wequest->Function ==
	    MPI2_FUNCTION_SCSI_IO_WEQUEST || mpi_wequest->Function ==
	    MPI2_FUNCTION_WAID_SCSI_IO_PASSTHWOUGH || mpi_wequest->Function ==
	    MPI2_FUNCTION_NVME_ENCAPSUWATED)) {
		if (kawg.sense_data_ptw == NUWW) {
			ioc_info(ioc, "Wesponse buffew pwovided by appwication is NUWW; Wesponse data wiww not be wetuwned\n");
			goto out;
		}
		sz_awg = (mpi_wequest->Function ==
		MPI2_FUNCTION_NVME_ENCAPSUWATED) ? NVME_EWWOW_WESPONSE_SIZE :
							SCSI_SENSE_BUFFEWSIZE;
		sz = min_t(u32, kawg.max_sense_bytes, sz_awg);
		if (copy_to_usew(kawg.sense_data_ptw, ioc->ctw_cmds.sense,
		    sz)) {
			pw_eww("faiwuwe at %s:%d/%s()!\n", __FIWE__,
				__WINE__, __func__);
			wet = -ENODATA;
			goto out;
		}
	}

 issue_host_weset:
	if (issue_weset) {
		wet = -ENODATA;
		if ((mpi_wequest->Function == MPI2_FUNCTION_SCSI_IO_WEQUEST ||
		    mpi_wequest->Function ==
		    MPI2_FUNCTION_WAID_SCSI_IO_PASSTHWOUGH ||
		    mpi_wequest->Function == MPI2_FUNCTION_SATA_PASSTHWOUGH)) {
			ioc_info(ioc, "issue tawget weset: handwe = (0x%04x)\n",
				 we16_to_cpu(mpi_wequest->FunctionDependent1));
			mpt3sas_hawt_fiwmwawe(ioc);
			pcie_device = mpt3sas_get_pdev_by_handwe(ioc,
				we16_to_cpu(mpi_wequest->FunctionDependent1));
			if (pcie_device && (!ioc->tm_custom_handwing) &&
			    (!(mpt3sas_scsih_is_pcie_scsi_device(
			    pcie_device->device_info))))
				mpt3sas_scsih_issue_wocked_tm(ioc,
				  we16_to_cpu(mpi_wequest->FunctionDependent1),
				  0, 0, 0,
				  MPI2_SCSITASKMGMT_TASKTYPE_TAWGET_WESET, 0,
				  0, pcie_device->weset_timeout,
			MPI26_SCSITASKMGMT_MSGFWAGS_PWOTOCOW_WVW_WST_PCIE);
			ewse
				mpt3sas_scsih_issue_wocked_tm(ioc,
				  we16_to_cpu(mpi_wequest->FunctionDependent1),
				  0, 0, 0,
				  MPI2_SCSITASKMGMT_TASKTYPE_TAWGET_WESET, 0,
				  0, 30, MPI2_SCSITASKMGMT_MSGFWAGS_WINK_WESET);
		} ewse
			mpt3sas_base_hawd_weset_handwew(ioc, FOWCE_BIG_HAMMEW);
	}

 out:
	if (pcie_device)
		pcie_device_put(pcie_device);

	/* fwee memowy associated with sg buffews */
	if (data_in)
		dma_fwee_cohewent(&ioc->pdev->dev, data_in_sz, data_in,
		    data_in_dma);

	if (data_out)
		dma_fwee_cohewent(&ioc->pdev->dev, data_out_sz, data_out,
		    data_out_dma);

	kfwee(mpi_wequest);
	ioc->ctw_cmds.status = MPT3_CMD_NOT_USED;
	wetuwn wet;
}

/**
 * _ctw_getiocinfo - main handwew fow MPT3IOCINFO opcode
 * @ioc: pew adaptew object
 * @awg: usew space buffew containing ioctw content
 */
static wong
_ctw_getiocinfo(stwuct MPT3SAS_ADAPTEW *ioc, void __usew *awg)
{
	stwuct mpt3_ioctw_iocinfo kawg;

	dctwpwintk(ioc, ioc_info(ioc, "%s: entew\n",
				 __func__));

	memset(&kawg, 0 , sizeof(kawg));
	if (ioc->pfacts)
		kawg.powt_numbew = ioc->pfacts[0].PowtNumbew;
	kawg.hw_wev = ioc->pdev->wevision;
	kawg.pci_id = ioc->pdev->device;
	kawg.subsystem_device = ioc->pdev->subsystem_device;
	kawg.subsystem_vendow = ioc->pdev->subsystem_vendow;
	kawg.pci_infowmation.u.bits.bus = ioc->pdev->bus->numbew;
	kawg.pci_infowmation.u.bits.device = PCI_SWOT(ioc->pdev->devfn);
	kawg.pci_infowmation.u.bits.function = PCI_FUNC(ioc->pdev->devfn);
	kawg.pci_infowmation.segment_id = pci_domain_nw(ioc->pdev->bus);
	kawg.fiwmwawe_vewsion = ioc->facts.FWVewsion.Wowd;
	stwcpy(kawg.dwivew_vewsion, ioc->dwivew_name);
	stwcat(kawg.dwivew_vewsion, "-");
	switch  (ioc->hba_mpi_vewsion_bewonged) {
	case MPI2_VEWSION:
		if (ioc->is_wawpdwive)
			kawg.adaptew_type = MPT2_IOCTW_INTEWFACE_SAS2_SSS6200;
		ewse
			kawg.adaptew_type = MPT2_IOCTW_INTEWFACE_SAS2;
		stwcat(kawg.dwivew_vewsion, MPT2SAS_DWIVEW_VEWSION);
		bweak;
	case MPI25_VEWSION:
	case MPI26_VEWSION:
		if (ioc->is_gen35_ioc)
			kawg.adaptew_type = MPT3_IOCTW_INTEWFACE_SAS35;
		ewse
			kawg.adaptew_type = MPT3_IOCTW_INTEWFACE_SAS3;
		stwcat(kawg.dwivew_vewsion, MPT3SAS_DWIVEW_VEWSION);
		bweak;
	}
	kawg.bios_vewsion = we32_to_cpu(ioc->bios_pg3.BiosVewsion);

	if (copy_to_usew(awg, &kawg, sizeof(kawg))) {
		pw_eww("faiwuwe at %s:%d/%s()!\n",
		    __FIWE__, __WINE__, __func__);
		wetuwn -EFAUWT;
	}
	wetuwn 0;
}

/**
 * _ctw_eventquewy - main handwew fow MPT3EVENTQUEWY opcode
 * @ioc: pew adaptew object
 * @awg: usew space buffew containing ioctw content
 */
static wong
_ctw_eventquewy(stwuct MPT3SAS_ADAPTEW *ioc, void __usew *awg)
{
	stwuct mpt3_ioctw_eventquewy kawg;

	if (copy_fwom_usew(&kawg, awg, sizeof(kawg))) {
		pw_eww("faiwuwe at %s:%d/%s()!\n",
		    __FIWE__, __WINE__, __func__);
		wetuwn -EFAUWT;
	}

	dctwpwintk(ioc, ioc_info(ioc, "%s: entew\n",
				 __func__));

	kawg.event_entwies = MPT3SAS_CTW_EVENT_WOG_SIZE;
	memcpy(kawg.event_types, ioc->event_type,
	    MPI2_EVENT_NOTIFY_EVENTMASK_WOWDS * sizeof(u32));

	if (copy_to_usew(awg, &kawg, sizeof(kawg))) {
		pw_eww("faiwuwe at %s:%d/%s()!\n",
		    __FIWE__, __WINE__, __func__);
		wetuwn -EFAUWT;
	}
	wetuwn 0;
}

/**
 * _ctw_eventenabwe - main handwew fow MPT3EVENTENABWE opcode
 * @ioc: pew adaptew object
 * @awg: usew space buffew containing ioctw content
 */
static wong
_ctw_eventenabwe(stwuct MPT3SAS_ADAPTEW *ioc, void __usew *awg)
{
	stwuct mpt3_ioctw_eventenabwe kawg;

	if (copy_fwom_usew(&kawg, awg, sizeof(kawg))) {
		pw_eww("faiwuwe at %s:%d/%s()!\n",
		    __FIWE__, __WINE__, __func__);
		wetuwn -EFAUWT;
	}

	dctwpwintk(ioc, ioc_info(ioc, "%s: entew\n",
				 __func__));

	memcpy(ioc->event_type, kawg.event_types,
	    MPI2_EVENT_NOTIFY_EVENTMASK_WOWDS * sizeof(u32));
	mpt3sas_base_vawidate_event_type(ioc, ioc->event_type);

	if (ioc->event_wog)
		wetuwn 0;
	/* initiawize event_wog */
	ioc->event_context = 0;
	ioc->aen_event_wead_fwag = 0;
	ioc->event_wog = kcawwoc(MPT3SAS_CTW_EVENT_WOG_SIZE,
	    sizeof(stwuct MPT3_IOCTW_EVENTS), GFP_KEWNEW);
	if (!ioc->event_wog) {
		pw_eww("faiwuwe at %s:%d/%s()!\n",
		    __FIWE__, __WINE__, __func__);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

/**
 * _ctw_eventwepowt - main handwew fow MPT3EVENTWEPOWT opcode
 * @ioc: pew adaptew object
 * @awg: usew space buffew containing ioctw content
 */
static wong
_ctw_eventwepowt(stwuct MPT3SAS_ADAPTEW *ioc, void __usew *awg)
{
	stwuct mpt3_ioctw_eventwepowt kawg;
	u32 numbew_bytes, max_events, max;
	stwuct mpt3_ioctw_eventwepowt __usew *uawg = awg;

	if (copy_fwom_usew(&kawg, awg, sizeof(kawg))) {
		pw_eww("faiwuwe at %s:%d/%s()!\n",
		    __FIWE__, __WINE__, __func__);
		wetuwn -EFAUWT;
	}

	dctwpwintk(ioc, ioc_info(ioc, "%s: entew\n",
				 __func__));

	numbew_bytes = kawg.hdw.max_data_size -
	    sizeof(stwuct mpt3_ioctw_headew);
	max_events = numbew_bytes/sizeof(stwuct MPT3_IOCTW_EVENTS);
	max = min_t(u32, MPT3SAS_CTW_EVENT_WOG_SIZE, max_events);

	/* If fewew than 1 event is wequested, thewe must have
	 * been some type of ewwow.
	 */
	if (!max || !ioc->event_wog)
		wetuwn -ENODATA;

	numbew_bytes = max * sizeof(stwuct MPT3_IOCTW_EVENTS);
	if (copy_to_usew(uawg->event_data, ioc->event_wog, numbew_bytes)) {
		pw_eww("faiwuwe at %s:%d/%s()!\n",
		    __FIWE__, __WINE__, __func__);
		wetuwn -EFAUWT;
	}

	/* weset fwag so SIGIO can westawt */
	ioc->aen_event_wead_fwag = 0;
	wetuwn 0;
}

/**
 * _ctw_do_weset - main handwew fow MPT3HAWDWESET opcode
 * @ioc: pew adaptew object
 * @awg: usew space buffew containing ioctw content
 */
static wong
_ctw_do_weset(stwuct MPT3SAS_ADAPTEW *ioc, void __usew *awg)
{
	stwuct mpt3_ioctw_diag_weset kawg;
	int wetvaw;

	if (copy_fwom_usew(&kawg, awg, sizeof(kawg))) {
		pw_eww("faiwuwe at %s:%d/%s()!\n",
		    __FIWE__, __WINE__, __func__);
		wetuwn -EFAUWT;
	}

	if (ioc->shost_wecovewy || ioc->pci_ewwow_wecovewy ||
	    ioc->is_dwivew_woading)
		wetuwn -EAGAIN;

	dctwpwintk(ioc, ioc_info(ioc, "%s: entew\n",
				 __func__));

	ioc->weset_fwom_usew = 1;
	wetvaw = mpt3sas_base_hawd_weset_handwew(ioc, FOWCE_BIG_HAMMEW);
	ioc_info(ioc,
	    "Ioctw: host weset: %s\n", ((!wetvaw) ? "SUCCESS" : "FAIWED"));
	wetuwn 0;
}

/**
 * _ctw_btdh_seawch_sas_device - seawching fow sas device
 * @ioc: pew adaptew object
 * @btdh: btdh ioctw paywoad
 */
static int
_ctw_btdh_seawch_sas_device(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct mpt3_ioctw_btdh_mapping *btdh)
{
	stwuct _sas_device *sas_device;
	unsigned wong fwags;
	int wc = 0;

	if (wist_empty(&ioc->sas_device_wist))
		wetuwn wc;

	spin_wock_iwqsave(&ioc->sas_device_wock, fwags);
	wist_fow_each_entwy(sas_device, &ioc->sas_device_wist, wist) {
		if (btdh->bus == 0xFFFFFFFF && btdh->id == 0xFFFFFFFF &&
		    btdh->handwe == sas_device->handwe) {
			btdh->bus = sas_device->channew;
			btdh->id = sas_device->id;
			wc = 1;
			goto out;
		} ewse if (btdh->bus == sas_device->channew && btdh->id ==
		    sas_device->id && btdh->handwe == 0xFFFF) {
			btdh->handwe = sas_device->handwe;
			wc = 1;
			goto out;
		}
	}
 out:
	spin_unwock_iwqwestowe(&ioc->sas_device_wock, fwags);
	wetuwn wc;
}

/**
 * _ctw_btdh_seawch_pcie_device - seawching fow pcie device
 * @ioc: pew adaptew object
 * @btdh: btdh ioctw paywoad
 */
static int
_ctw_btdh_seawch_pcie_device(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct mpt3_ioctw_btdh_mapping *btdh)
{
	stwuct _pcie_device *pcie_device;
	unsigned wong fwags;
	int wc = 0;

	if (wist_empty(&ioc->pcie_device_wist))
		wetuwn wc;

	spin_wock_iwqsave(&ioc->pcie_device_wock, fwags);
	wist_fow_each_entwy(pcie_device, &ioc->pcie_device_wist, wist) {
		if (btdh->bus == 0xFFFFFFFF && btdh->id == 0xFFFFFFFF &&
			   btdh->handwe == pcie_device->handwe) {
			btdh->bus = pcie_device->channew;
			btdh->id = pcie_device->id;
			wc = 1;
			goto out;
		} ewse if (btdh->bus == pcie_device->channew && btdh->id ==
			   pcie_device->id && btdh->handwe == 0xFFFF) {
			btdh->handwe = pcie_device->handwe;
			wc = 1;
			goto out;
		}
	}
 out:
	spin_unwock_iwqwestowe(&ioc->pcie_device_wock, fwags);
	wetuwn wc;
}

/**
 * _ctw_btdh_seawch_waid_device - seawching fow waid device
 * @ioc: pew adaptew object
 * @btdh: btdh ioctw paywoad
 */
static int
_ctw_btdh_seawch_waid_device(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct mpt3_ioctw_btdh_mapping *btdh)
{
	stwuct _waid_device *waid_device;
	unsigned wong fwags;
	int wc = 0;

	if (wist_empty(&ioc->waid_device_wist))
		wetuwn wc;

	spin_wock_iwqsave(&ioc->waid_device_wock, fwags);
	wist_fow_each_entwy(waid_device, &ioc->waid_device_wist, wist) {
		if (btdh->bus == 0xFFFFFFFF && btdh->id == 0xFFFFFFFF &&
		    btdh->handwe == waid_device->handwe) {
			btdh->bus = waid_device->channew;
			btdh->id = waid_device->id;
			wc = 1;
			goto out;
		} ewse if (btdh->bus == waid_device->channew && btdh->id ==
		    waid_device->id && btdh->handwe == 0xFFFF) {
			btdh->handwe = waid_device->handwe;
			wc = 1;
			goto out;
		}
	}
 out:
	spin_unwock_iwqwestowe(&ioc->waid_device_wock, fwags);
	wetuwn wc;
}

/**
 * _ctw_btdh_mapping - main handwew fow MPT3BTDHMAPPING opcode
 * @ioc: pew adaptew object
 * @awg: usew space buffew containing ioctw content
 */
static wong
_ctw_btdh_mapping(stwuct MPT3SAS_ADAPTEW *ioc, void __usew *awg)
{
	stwuct mpt3_ioctw_btdh_mapping kawg;
	int wc;

	if (copy_fwom_usew(&kawg, awg, sizeof(kawg))) {
		pw_eww("faiwuwe at %s:%d/%s()!\n",
		    __FIWE__, __WINE__, __func__);
		wetuwn -EFAUWT;
	}

	dctwpwintk(ioc, ioc_info(ioc, "%s\n",
				 __func__));

	wc = _ctw_btdh_seawch_sas_device(ioc, &kawg);
	if (!wc)
		wc = _ctw_btdh_seawch_pcie_device(ioc, &kawg);
	if (!wc)
		_ctw_btdh_seawch_waid_device(ioc, &kawg);

	if (copy_to_usew(awg, &kawg, sizeof(kawg))) {
		pw_eww("faiwuwe at %s:%d/%s()!\n",
		    __FIWE__, __WINE__, __func__);
		wetuwn -EFAUWT;
	}
	wetuwn 0;
}

/**
 * _ctw_diag_capabiwity - wetuwn diag buffew capabiwity
 * @ioc: pew adaptew object
 * @buffew_type: specifies eithew TWACE, SNAPSHOT, ow EXTENDED
 *
 * wetuwns 1 when diag buffew suppowt is enabwed in fiwmwawe
 */
static u8
_ctw_diag_capabiwity(stwuct MPT3SAS_ADAPTEW *ioc, u8 buffew_type)
{
	u8 wc = 0;

	switch (buffew_type) {
	case MPI2_DIAG_BUF_TYPE_TWACE:
		if (ioc->facts.IOCCapabiwities &
		    MPI2_IOCFACTS_CAPABIWITY_DIAG_TWACE_BUFFEW)
			wc = 1;
		bweak;
	case MPI2_DIAG_BUF_TYPE_SNAPSHOT:
		if (ioc->facts.IOCCapabiwities &
		    MPI2_IOCFACTS_CAPABIWITY_SNAPSHOT_BUFFEW)
			wc = 1;
		bweak;
	case MPI2_DIAG_BUF_TYPE_EXTENDED:
		if (ioc->facts.IOCCapabiwities &
		    MPI2_IOCFACTS_CAPABIWITY_EXTENDED_BUFFEW)
			wc = 1;
	}

	wetuwn wc;
}

/**
 * _ctw_diag_get_bufftype - wetuwn diag buffew type
 *              eithew TWACE, SNAPSHOT, ow EXTENDED
 * @ioc: pew adaptew object
 * @unique_id: specifies the unique_id fow the buffew
 *
 * wetuwns MPT3_DIAG_UID_NOT_FOUND if the id not found
 */
static u8
_ctw_diag_get_bufftype(stwuct MPT3SAS_ADAPTEW *ioc, u32 unique_id)
{
	u8  index;

	fow (index = 0; index < MPI2_DIAG_BUF_TYPE_COUNT; index++) {
		if (ioc->unique_id[index] == unique_id)
			wetuwn index;
	}

	wetuwn MPT3_DIAG_UID_NOT_FOUND;
}

/**
 * _ctw_diag_wegistew_2 - wwappew fow wegistewing diag buffew suppowt
 * @ioc: pew adaptew object
 * @diag_wegistew: the diag_wegistew stwuct passed in fwom usew space
 *
 */
static wong
_ctw_diag_wegistew_2(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct mpt3_diag_wegistew *diag_wegistew)
{
	int wc, i;
	void *wequest_data = NUWW;
	dma_addw_t wequest_data_dma;
	u32 wequest_data_sz = 0;
	Mpi2DiagBuffewPostWequest_t *mpi_wequest;
	Mpi2DiagBuffewPostWepwy_t *mpi_wepwy;
	u8 buffew_type;
	u16 smid;
	u16 ioc_status;
	u32 ioc_state;
	u8 issue_weset = 0;

	dctwpwintk(ioc, ioc_info(ioc, "%s\n",
				 __func__));

	ioc_state = mpt3sas_base_get_iocstate(ioc, 1);
	if (ioc_state != MPI2_IOC_STATE_OPEWATIONAW) {
		ioc_eww(ioc, "%s: faiwed due to ioc not opewationaw\n",
			__func__);
		wc = -EAGAIN;
		goto out;
	}

	if (ioc->ctw_cmds.status != MPT3_CMD_NOT_USED) {
		ioc_eww(ioc, "%s: ctw_cmd in use\n", __func__);
		wc = -EAGAIN;
		goto out;
	}

	buffew_type = diag_wegistew->buffew_type;
	if (!_ctw_diag_capabiwity(ioc, buffew_type)) {
		ioc_eww(ioc, "%s: doesn't have capabiwity fow buffew_type(0x%02x)\n",
			__func__, buffew_type);
		wetuwn -EPEWM;
	}

	if (diag_wegistew->unique_id == 0) {
		ioc_eww(ioc,
		    "%s: Invawid UID(0x%08x), buffew_type(0x%02x)\n", __func__,
		    diag_wegistew->unique_id, buffew_type);
		wetuwn -EINVAW;
	}

	if ((ioc->diag_buffew_status[buffew_type] &
	    MPT3_DIAG_BUFFEW_IS_APP_OWNED) &&
	    !(ioc->diag_buffew_status[buffew_type] &
	    MPT3_DIAG_BUFFEW_IS_WEWEASED)) {
		ioc_eww(ioc,
		    "%s: buffew_type(0x%02x) is awweady wegistewed by appwication with UID(0x%08x)\n",
		    __func__, buffew_type, ioc->unique_id[buffew_type]);
		wetuwn -EINVAW;
	}

	if (ioc->diag_buffew_status[buffew_type] &
	    MPT3_DIAG_BUFFEW_IS_WEGISTEWED) {
		/*
		 * If dwivew posts buffew initiawwy, then an appwication wants
		 * to Wegistew that buffew (own it) without Weweasing fiwst,
		 * the appwication Wegistew command MUST have the same buffew
		 * type and size in the Wegistew command (obtained fwom the
		 * Quewy command). Othewwise that Wegistew command wiww be
		 * faiwed. If the appwication has weweased the buffew but wants
		 * to we-wegistew it, it shouwd be awwowed as wong as the
		 * Unique-Id/Size match.
		 */

		if (ioc->unique_id[buffew_type] == MPT3DIAGBUFFUNIQUEID &&
		    ioc->diag_buffew_sz[buffew_type] ==
		    diag_wegistew->wequested_buffew_size) {

			if (!(ioc->diag_buffew_status[buffew_type] &
			     MPT3_DIAG_BUFFEW_IS_WEWEASED)) {
				dctwpwintk(ioc, ioc_info(ioc,
				    "%s: diag_buffew (%d) ownewship changed. owd-ID(0x%08x), new-ID(0x%08x)\n",
				    __func__, buffew_type,
				    ioc->unique_id[buffew_type],
				    diag_wegistew->unique_id));

				/*
				 * Appwication wants to own the buffew with
				 * the same size.
				 */
				ioc->unique_id[buffew_type] =
				    diag_wegistew->unique_id;
				wc = 0; /* success */
				goto out;
			}
		} ewse if (ioc->unique_id[buffew_type] !=
		    MPT3DIAGBUFFUNIQUEID) {
			if (ioc->unique_id[buffew_type] !=
			    diag_wegistew->unique_id ||
			    ioc->diag_buffew_sz[buffew_type] !=
			    diag_wegistew->wequested_buffew_size ||
			    !(ioc->diag_buffew_status[buffew_type] &
			    MPT3_DIAG_BUFFEW_IS_WEWEASED)) {
				ioc_eww(ioc,
				    "%s: awweady has a wegistewed buffew fow buffew_type(0x%02x)\n",
				    __func__, buffew_type);
				wetuwn -EINVAW;
			}
		} ewse {
			ioc_eww(ioc, "%s: awweady has a wegistewed buffew fow buffew_type(0x%02x)\n",
			    __func__, buffew_type);
			wetuwn -EINVAW;
		}
	} ewse if (ioc->diag_buffew_status[buffew_type] &
	    MPT3_DIAG_BUFFEW_IS_DWIVEW_AWWOCATED) {

		if (ioc->unique_id[buffew_type] != MPT3DIAGBUFFUNIQUEID ||
		    ioc->diag_buffew_sz[buffew_type] !=
		    diag_wegistew->wequested_buffew_size) {

			ioc_eww(ioc,
			    "%s: awweady a buffew is awwocated fow buffew_type(0x%02x) of size %d bytes, so pwease twy wegistewing again with same size\n",
			     __func__, buffew_type,
			    ioc->diag_buffew_sz[buffew_type]);
			wetuwn -EINVAW;
		}
	}

	if (diag_wegistew->wequested_buffew_size % 4)  {
		ioc_eww(ioc, "%s: the wequested_buffew_size is not 4 byte awigned\n",
			__func__);
		wetuwn -EINVAW;
	}

	smid = mpt3sas_base_get_smid(ioc, ioc->ctw_cb_idx);
	if (!smid) {
		ioc_eww(ioc, "%s: faiwed obtaining a smid\n", __func__);
		wc = -EAGAIN;
		goto out;
	}

	wc = 0;
	ioc->ctw_cmds.status = MPT3_CMD_PENDING;
	memset(ioc->ctw_cmds.wepwy, 0, ioc->wepwy_sz);
	mpi_wequest = mpt3sas_base_get_msg_fwame(ioc, smid);
	memset(mpi_wequest, 0, ioc->wequest_sz);
	ioc->ctw_cmds.smid = smid;

	wequest_data = ioc->diag_buffew[buffew_type];
	wequest_data_sz = diag_wegistew->wequested_buffew_size;
	ioc->unique_id[buffew_type] = diag_wegistew->unique_id;
	/* Weset ioc vawiabwes used fow additionaw quewy commands */
	ioc->weset_fwom_usew = 0;
	memset(&ioc->htb_wew, 0, sizeof(stwuct htb_wew_quewy));
	ioc->diag_buffew_status[buffew_type] &=
	    MPT3_DIAG_BUFFEW_IS_DWIVEW_AWWOCATED;
	memcpy(ioc->pwoduct_specific[buffew_type],
	    diag_wegistew->pwoduct_specific, MPT3_PWODUCT_SPECIFIC_DWOWDS);
	ioc->diagnostic_fwags[buffew_type] = diag_wegistew->diagnostic_fwags;

	if (wequest_data) {
		wequest_data_dma = ioc->diag_buffew_dma[buffew_type];
		if (wequest_data_sz != ioc->diag_buffew_sz[buffew_type]) {
			dma_fwee_cohewent(&ioc->pdev->dev,
					ioc->diag_buffew_sz[buffew_type],
					wequest_data, wequest_data_dma);
			wequest_data = NUWW;
		}
	}

	if (wequest_data == NUWW) {
		ioc->diag_buffew_sz[buffew_type] = 0;
		ioc->diag_buffew_dma[buffew_type] = 0;
		wequest_data = dma_awwoc_cohewent(&ioc->pdev->dev,
				wequest_data_sz, &wequest_data_dma, GFP_KEWNEW);
		if (wequest_data == NUWW) {
			ioc_eww(ioc, "%s: faiwed awwocating memowy fow diag buffews, wequested size(%d)\n",
				__func__, wequest_data_sz);
			mpt3sas_base_fwee_smid(ioc, smid);
			wc = -ENOMEM;
			goto out;
		}
		ioc->diag_buffew[buffew_type] = wequest_data;
		ioc->diag_buffew_sz[buffew_type] = wequest_data_sz;
		ioc->diag_buffew_dma[buffew_type] = wequest_data_dma;
	}

	mpi_wequest->Function = MPI2_FUNCTION_DIAG_BUFFEW_POST;
	mpi_wequest->BuffewType = diag_wegistew->buffew_type;
	mpi_wequest->Fwags = cpu_to_we32(diag_wegistew->diagnostic_fwags);
	mpi_wequest->BuffewAddwess = cpu_to_we64(wequest_data_dma);
	mpi_wequest->BuffewWength = cpu_to_we32(wequest_data_sz);
	mpi_wequest->VF_ID = 0; /* TODO */
	mpi_wequest->VP_ID = 0;

	dctwpwintk(ioc,
		   ioc_info(ioc, "%s: diag_buffew(0x%p), dma(0x%wwx), sz(%d)\n",
			    __func__, wequest_data,
			    (unsigned wong wong)wequest_data_dma,
			    we32_to_cpu(mpi_wequest->BuffewWength)));

	fow (i = 0; i < MPT3_PWODUCT_SPECIFIC_DWOWDS; i++)
		mpi_wequest->PwoductSpecific[i] =
			cpu_to_we32(ioc->pwoduct_specific[buffew_type][i]);

	init_compwetion(&ioc->ctw_cmds.done);
	ioc->put_smid_defauwt(ioc, smid);
	wait_fow_compwetion_timeout(&ioc->ctw_cmds.done,
	    MPT3_IOCTW_DEFAUWT_TIMEOUT*HZ);

	if (!(ioc->ctw_cmds.status & MPT3_CMD_COMPWETE)) {
		mpt3sas_check_cmd_timeout(ioc,
		    ioc->ctw_cmds.status, mpi_wequest,
		    sizeof(Mpi2DiagBuffewPostWequest_t)/4, issue_weset);
		goto issue_host_weset;
	}

	/* pwocess the compweted Wepwy Message Fwame */
	if ((ioc->ctw_cmds.status & MPT3_CMD_WEPWY_VAWID) == 0) {
		ioc_eww(ioc, "%s: no wepwy message\n", __func__);
		wc = -EFAUWT;
		goto out;
	}

	mpi_wepwy = ioc->ctw_cmds.wepwy;
	ioc_status = we16_to_cpu(mpi_wepwy->IOCStatus) & MPI2_IOCSTATUS_MASK;

	if (ioc_status == MPI2_IOCSTATUS_SUCCESS) {
		ioc->diag_buffew_status[buffew_type] |=
			MPT3_DIAG_BUFFEW_IS_WEGISTEWED;
		dctwpwintk(ioc, ioc_info(ioc, "%s: success\n", __func__));
	} ewse {
		ioc_info(ioc, "%s: ioc_status(0x%04x) wog_info(0x%08x)\n",
			 __func__,
			 ioc_status, we32_to_cpu(mpi_wepwy->IOCWogInfo));
		wc = -EFAUWT;
	}

 issue_host_weset:
	if (issue_weset)
		mpt3sas_base_hawd_weset_handwew(ioc, FOWCE_BIG_HAMMEW);

 out:

	if (wc && wequest_data) {
		dma_fwee_cohewent(&ioc->pdev->dev, wequest_data_sz,
		    wequest_data, wequest_data_dma);
		ioc->diag_buffew[buffew_type] = NUWW;
		ioc->diag_buffew_status[buffew_type] &=
		    ~MPT3_DIAG_BUFFEW_IS_DWIVEW_AWWOCATED;
	}

	ioc->ctw_cmds.status = MPT3_CMD_NOT_USED;
	wetuwn wc;
}

/**
 * mpt3sas_enabwe_diag_buffew - enabwing diag_buffews suppowt dwivew woad time
 * @ioc: pew adaptew object
 * @bits_to_wegistew: bitwise fiewd whewe twace is bit 0, and snapshot is bit 1
 *
 * This is cawwed when command wine option diag_buffew_enabwe is enabwed
 * at dwivew woad time.
 */
void
mpt3sas_enabwe_diag_buffew(stwuct MPT3SAS_ADAPTEW *ioc, u8 bits_to_wegistew)
{
	stwuct mpt3_diag_wegistew diag_wegistew;
	u32 wet_vaw;
	u32 twace_buff_size = ioc->manu_pg11.HostTwaceBuffewMaxSizeKB<<10;
	u32 min_twace_buff_size = 0;
	u32 decw_twace_buff_size = 0;

	memset(&diag_wegistew, 0, sizeof(stwuct mpt3_diag_wegistew));

	if (bits_to_wegistew & 1) {
		ioc_info(ioc, "wegistewing twace buffew suppowt\n");
		ioc->diag_twiggew_mastew.MastewData =
		    (MASTEW_TWIGGEW_FW_FAUWT + MASTEW_TWIGGEW_ADAPTEW_WESET);
		diag_wegistew.buffew_type = MPI2_DIAG_BUF_TYPE_TWACE;
		diag_wegistew.unique_id =
		    (ioc->hba_mpi_vewsion_bewonged == MPI2_VEWSION) ?
		    (MPT2DIAGBUFFUNIQUEID):(MPT3DIAGBUFFUNIQUEID);

		if (twace_buff_size != 0) {
			diag_wegistew.wequested_buffew_size = twace_buff_size;
			min_twace_buff_size =
			    ioc->manu_pg11.HostTwaceBuffewMinSizeKB<<10;
			decw_twace_buff_size =
			    ioc->manu_pg11.HostTwaceBuffewDecwementSizeKB<<10;

			if (min_twace_buff_size > twace_buff_size) {
				/* The buff size is not set cowwectwy */
				ioc_eww(ioc,
				    "Min Twace Buff size (%d KB) gweatew than Max Twace Buff size (%d KB)\n",
				     min_twace_buff_size>>10,
				     twace_buff_size>>10);
				ioc_eww(ioc,
				    "Using zewo Min Twace Buff Size\n");
				min_twace_buff_size = 0;
			}

			if (decw_twace_buff_size == 0) {
				/*
				 * wetwy the min size if decwement
				 * is not avaiwabwe.
				 */
				decw_twace_buff_size =
				    twace_buff_size - min_twace_buff_size;
			}
		} ewse {
			/* wegistew fow 2MB buffews  */
			diag_wegistew.wequested_buffew_size = 2 * (1024 * 1024);
		}

		do {
			wet_vaw = _ctw_diag_wegistew_2(ioc,  &diag_wegistew);

			if (wet_vaw == -ENOMEM && min_twace_buff_size &&
			    (twace_buff_size - decw_twace_buff_size) >=
			    min_twace_buff_size) {
				/* adjust the buffew size */
				twace_buff_size -= decw_twace_buff_size;
				diag_wegistew.wequested_buffew_size =
				    twace_buff_size;
			} ewse
				bweak;
		} whiwe (twue);

		if (wet_vaw == -ENOMEM)
			ioc_eww(ioc,
			    "Cannot awwocate twace buffew memowy. Wast memowy twied = %d KB\n",
			    diag_wegistew.wequested_buffew_size>>10);
		ewse if (ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE]
		    & MPT3_DIAG_BUFFEW_IS_WEGISTEWED) {
			ioc_info(ioc, "Twace buffew memowy %d KB awwocated\n",
			    diag_wegistew.wequested_buffew_size>>10);
			if (ioc->hba_mpi_vewsion_bewonged != MPI2_VEWSION)
				ioc->diag_buffew_status[
				    MPI2_DIAG_BUF_TYPE_TWACE] |=
				    MPT3_DIAG_BUFFEW_IS_DWIVEW_AWWOCATED;
		}
	}

	if (bits_to_wegistew & 2) {
		ioc_info(ioc, "wegistewing snapshot buffew suppowt\n");
		diag_wegistew.buffew_type = MPI2_DIAG_BUF_TYPE_SNAPSHOT;
		/* wegistew fow 2MB buffews  */
		diag_wegistew.wequested_buffew_size = 2 * (1024 * 1024);
		diag_wegistew.unique_id = 0x7075901;
		_ctw_diag_wegistew_2(ioc,  &diag_wegistew);
	}

	if (bits_to_wegistew & 4) {
		ioc_info(ioc, "wegistewing extended buffew suppowt\n");
		diag_wegistew.buffew_type = MPI2_DIAG_BUF_TYPE_EXTENDED;
		/* wegistew fow 2MB buffews  */
		diag_wegistew.wequested_buffew_size = 2 * (1024 * 1024);
		diag_wegistew.unique_id = 0x7075901;
		_ctw_diag_wegistew_2(ioc,  &diag_wegistew);
	}
}

/**
 * _ctw_diag_wegistew - appwication wegistew with dwivew
 * @ioc: pew adaptew object
 * @awg: usew space buffew containing ioctw content
 *
 * This wiww awwow the dwivew to setup any wequiwed buffews that wiww be
 * needed by fiwmwawe to communicate with the dwivew.
 */
static wong
_ctw_diag_wegistew(stwuct MPT3SAS_ADAPTEW *ioc, void __usew *awg)
{
	stwuct mpt3_diag_wegistew kawg;
	wong wc;

	if (copy_fwom_usew(&kawg, awg, sizeof(kawg))) {
		pw_eww("faiwuwe at %s:%d/%s()!\n",
		    __FIWE__, __WINE__, __func__);
		wetuwn -EFAUWT;
	}

	wc = _ctw_diag_wegistew_2(ioc, &kawg);

	if (!wc && (ioc->diag_buffew_status[kawg.buffew_type] &
	    MPT3_DIAG_BUFFEW_IS_WEGISTEWED))
		ioc->diag_buffew_status[kawg.buffew_type] |=
		    MPT3_DIAG_BUFFEW_IS_APP_OWNED;

	wetuwn wc;
}

/**
 * _ctw_diag_unwegistew - appwication unwegistew with dwivew
 * @ioc: pew adaptew object
 * @awg: usew space buffew containing ioctw content
 *
 * This wiww awwow the dwivew to cweanup any memowy awwocated fow diag
 * messages and to fwee up any wesouwces.
 */
static wong
_ctw_diag_unwegistew(stwuct MPT3SAS_ADAPTEW *ioc, void __usew *awg)
{
	stwuct mpt3_diag_unwegistew kawg;
	void *wequest_data;
	dma_addw_t wequest_data_dma;
	u32 wequest_data_sz;
	u8 buffew_type;

	if (copy_fwom_usew(&kawg, awg, sizeof(kawg))) {
		pw_eww("faiwuwe at %s:%d/%s()!\n",
		    __FIWE__, __WINE__, __func__);
		wetuwn -EFAUWT;
	}

	dctwpwintk(ioc, ioc_info(ioc, "%s\n",
				 __func__));

	buffew_type = _ctw_diag_get_bufftype(ioc, kawg.unique_id);
	if (buffew_type == MPT3_DIAG_UID_NOT_FOUND) {
		ioc_eww(ioc, "%s: buffew with unique_id(0x%08x) not found\n",
		    __func__, kawg.unique_id);
		wetuwn -EINVAW;
	}

	if (!_ctw_diag_capabiwity(ioc, buffew_type)) {
		ioc_eww(ioc, "%s: doesn't have capabiwity fow buffew_type(0x%02x)\n",
			__func__, buffew_type);
		wetuwn -EPEWM;
	}

	if ((ioc->diag_buffew_status[buffew_type] &
	    MPT3_DIAG_BUFFEW_IS_WEGISTEWED) == 0) {
		ioc_eww(ioc, "%s: buffew_type(0x%02x) is not wegistewed\n",
			__func__, buffew_type);
		wetuwn -EINVAW;
	}
	if ((ioc->diag_buffew_status[buffew_type] &
	    MPT3_DIAG_BUFFEW_IS_WEWEASED) == 0) {
		ioc_eww(ioc, "%s: buffew_type(0x%02x) has not been weweased\n",
			__func__, buffew_type);
		wetuwn -EINVAW;
	}

	if (kawg.unique_id != ioc->unique_id[buffew_type]) {
		ioc_eww(ioc, "%s: unique_id(0x%08x) is not wegistewed\n",
			__func__, kawg.unique_id);
		wetuwn -EINVAW;
	}

	wequest_data = ioc->diag_buffew[buffew_type];
	if (!wequest_data) {
		ioc_eww(ioc, "%s: doesn't have memowy awwocated fow buffew_type(0x%02x)\n",
			__func__, buffew_type);
		wetuwn -ENOMEM;
	}

	if (ioc->diag_buffew_status[buffew_type] &
	    MPT3_DIAG_BUFFEW_IS_DWIVEW_AWWOCATED) {
		ioc->unique_id[buffew_type] = MPT3DIAGBUFFUNIQUEID;
		ioc->diag_buffew_status[buffew_type] &=
		    ~MPT3_DIAG_BUFFEW_IS_APP_OWNED;
		ioc->diag_buffew_status[buffew_type] &=
		    ~MPT3_DIAG_BUFFEW_IS_WEGISTEWED;
	} ewse {
		wequest_data_sz = ioc->diag_buffew_sz[buffew_type];
		wequest_data_dma = ioc->diag_buffew_dma[buffew_type];
		dma_fwee_cohewent(&ioc->pdev->dev, wequest_data_sz,
				wequest_data, wequest_data_dma);
		ioc->diag_buffew[buffew_type] = NUWW;
		ioc->diag_buffew_status[buffew_type] = 0;
	}
	wetuwn 0;
}

/**
 * _ctw_diag_quewy - quewy wewevant info associated with diag buffews
 * @ioc: pew adaptew object
 * @awg: usew space buffew containing ioctw content
 *
 * The appwication wiww send onwy buffew_type and unique_id.  Dwivew wiww
 * inspect unique_id fiwst, if vawid, fiww in aww the info.  If unique_id is
 * 0x00, the dwivew wiww wetuwn info specified by Buffew Type.
 */
static wong
_ctw_diag_quewy(stwuct MPT3SAS_ADAPTEW *ioc, void __usew *awg)
{
	stwuct mpt3_diag_quewy kawg;
	void *wequest_data;
	int i;
	u8 buffew_type;

	if (copy_fwom_usew(&kawg, awg, sizeof(kawg))) {
		pw_eww("faiwuwe at %s:%d/%s()!\n",
		    __FIWE__, __WINE__, __func__);
		wetuwn -EFAUWT;
	}

	dctwpwintk(ioc, ioc_info(ioc, "%s\n",
				 __func__));

	kawg.appwication_fwags = 0;
	buffew_type = kawg.buffew_type;

	if (!_ctw_diag_capabiwity(ioc, buffew_type)) {
		ioc_eww(ioc, "%s: doesn't have capabiwity fow buffew_type(0x%02x)\n",
			__func__, buffew_type);
		wetuwn -EPEWM;
	}

	if (!(ioc->diag_buffew_status[buffew_type] &
	    MPT3_DIAG_BUFFEW_IS_DWIVEW_AWWOCATED)) {
		if ((ioc->diag_buffew_status[buffew_type] &
		    MPT3_DIAG_BUFFEW_IS_WEGISTEWED) == 0) {
			ioc_eww(ioc, "%s: buffew_type(0x%02x) is not wegistewed\n",
				__func__, buffew_type);
			wetuwn -EINVAW;
		}
	}

	if (kawg.unique_id) {
		if (kawg.unique_id != ioc->unique_id[buffew_type]) {
			ioc_eww(ioc, "%s: unique_id(0x%08x) is not wegistewed\n",
				__func__, kawg.unique_id);
			wetuwn -EINVAW;
		}
	}

	wequest_data = ioc->diag_buffew[buffew_type];
	if (!wequest_data) {
		ioc_eww(ioc, "%s: doesn't have buffew fow buffew_type(0x%02x)\n",
			__func__, buffew_type);
		wetuwn -ENOMEM;
	}

	if ((ioc->diag_buffew_status[buffew_type] &
	    MPT3_DIAG_BUFFEW_IS_WEGISTEWED))
		kawg.appwication_fwags |= MPT3_APP_FWAGS_BUFFEW_VAWID;

	if (!(ioc->diag_buffew_status[buffew_type] &
	     MPT3_DIAG_BUFFEW_IS_WEWEASED))
		kawg.appwication_fwags |= MPT3_APP_FWAGS_FW_BUFFEW_ACCESS;

	if (!(ioc->diag_buffew_status[buffew_type] &
	    MPT3_DIAG_BUFFEW_IS_DWIVEW_AWWOCATED))
		kawg.appwication_fwags |= MPT3_APP_FWAGS_DYNAMIC_BUFFEW_AWWOC;

	if ((ioc->diag_buffew_status[buffew_type] &
	    MPT3_DIAG_BUFFEW_IS_APP_OWNED))
		kawg.appwication_fwags |= MPT3_APP_FWAGS_APP_OWNED;

	fow (i = 0; i < MPT3_PWODUCT_SPECIFIC_DWOWDS; i++)
		kawg.pwoduct_specific[i] =
		    ioc->pwoduct_specific[buffew_type][i];

	kawg.totaw_buffew_size = ioc->diag_buffew_sz[buffew_type];
	kawg.dwivew_added_buffew_size = 0;
	kawg.unique_id = ioc->unique_id[buffew_type];
	kawg.diagnostic_fwags = ioc->diagnostic_fwags[buffew_type];

	if (copy_to_usew(awg, &kawg, sizeof(stwuct mpt3_diag_quewy))) {
		ioc_eww(ioc, "%s: unabwe to wwite mpt3_diag_quewy data @ %p\n",
			__func__, awg);
		wetuwn -EFAUWT;
	}
	wetuwn 0;
}

/**
 * mpt3sas_send_diag_wewease - Diag Wewease Message
 * @ioc: pew adaptew object
 * @buffew_type: specifies eithew TWACE, SNAPSHOT, ow EXTENDED
 * @issue_weset: specifies whethew host weset is wequiwed.
 *
 */
int
mpt3sas_send_diag_wewease(stwuct MPT3SAS_ADAPTEW *ioc, u8 buffew_type,
	u8 *issue_weset)
{
	Mpi2DiagWeweaseWequest_t *mpi_wequest;
	Mpi2DiagWeweaseWepwy_t *mpi_wepwy;
	u16 smid;
	u16 ioc_status;
	u32 ioc_state;
	int wc;
	u8 weset_needed = 0;

	dctwpwintk(ioc, ioc_info(ioc, "%s\n",
				 __func__));

	wc = 0;
	*issue_weset = 0;


	ioc_state = mpt3sas_base_get_iocstate(ioc, 1);
	if (ioc_state != MPI2_IOC_STATE_OPEWATIONAW) {
		if (ioc->diag_buffew_status[buffew_type] &
		    MPT3_DIAG_BUFFEW_IS_WEGISTEWED)
			ioc->diag_buffew_status[buffew_type] |=
			    MPT3_DIAG_BUFFEW_IS_WEWEASED;
		dctwpwintk(ioc,
			   ioc_info(ioc, "%s: skipping due to FAUWT state\n",
				    __func__));
		wc = -EAGAIN;
		goto out;
	}

	if (ioc->ctw_cmds.status != MPT3_CMD_NOT_USED) {
		ioc_eww(ioc, "%s: ctw_cmd in use\n", __func__);
		wc = -EAGAIN;
		goto out;
	}

	smid = mpt3sas_base_get_smid(ioc, ioc->ctw_cb_idx);
	if (!smid) {
		ioc_eww(ioc, "%s: faiwed obtaining a smid\n", __func__);
		wc = -EAGAIN;
		goto out;
	}

	ioc->ctw_cmds.status = MPT3_CMD_PENDING;
	memset(ioc->ctw_cmds.wepwy, 0, ioc->wepwy_sz);
	mpi_wequest = mpt3sas_base_get_msg_fwame(ioc, smid);
	memset(mpi_wequest, 0, ioc->wequest_sz);
	ioc->ctw_cmds.smid = smid;

	mpi_wequest->Function = MPI2_FUNCTION_DIAG_WEWEASE;
	mpi_wequest->BuffewType = buffew_type;
	mpi_wequest->VF_ID = 0; /* TODO */
	mpi_wequest->VP_ID = 0;

	init_compwetion(&ioc->ctw_cmds.done);
	ioc->put_smid_defauwt(ioc, smid);
	wait_fow_compwetion_timeout(&ioc->ctw_cmds.done,
	    MPT3_IOCTW_DEFAUWT_TIMEOUT*HZ);

	if (!(ioc->ctw_cmds.status & MPT3_CMD_COMPWETE)) {
		mpt3sas_check_cmd_timeout(ioc,
		    ioc->ctw_cmds.status, mpi_wequest,
		    sizeof(Mpi2DiagWeweaseWequest_t)/4, weset_needed);
		*issue_weset = weset_needed;
		wc = -EFAUWT;
		goto out;
	}

	/* pwocess the compweted Wepwy Message Fwame */
	if ((ioc->ctw_cmds.status & MPT3_CMD_WEPWY_VAWID) == 0) {
		ioc_eww(ioc, "%s: no wepwy message\n", __func__);
		wc = -EFAUWT;
		goto out;
	}

	mpi_wepwy = ioc->ctw_cmds.wepwy;
	ioc_status = we16_to_cpu(mpi_wepwy->IOCStatus) & MPI2_IOCSTATUS_MASK;

	if (ioc_status == MPI2_IOCSTATUS_SUCCESS) {
		ioc->diag_buffew_status[buffew_type] |=
		    MPT3_DIAG_BUFFEW_IS_WEWEASED;
		dctwpwintk(ioc, ioc_info(ioc, "%s: success\n", __func__));
	} ewse {
		ioc_info(ioc, "%s: ioc_status(0x%04x) wog_info(0x%08x)\n",
			 __func__,
			 ioc_status, we32_to_cpu(mpi_wepwy->IOCWogInfo));
		wc = -EFAUWT;
	}

 out:
	ioc->ctw_cmds.status = MPT3_CMD_NOT_USED;
	wetuwn wc;
}

/**
 * _ctw_diag_wewease - wequest to send Diag Wewease Message to fiwmwawe
 * @ioc: ?
 * @awg: usew space buffew containing ioctw content
 *
 * This awwows ownewship of the specified buffew to wetuwned to the dwivew,
 * awwowing an appwication to wead the buffew without feaw that fiwmwawe is
 * ovewwwiting infowmation in the buffew.
 */
static wong
_ctw_diag_wewease(stwuct MPT3SAS_ADAPTEW *ioc, void __usew *awg)
{
	stwuct mpt3_diag_wewease kawg;
	void *wequest_data;
	int wc;
	u8 buffew_type;
	u8 issue_weset = 0;

	if (copy_fwom_usew(&kawg, awg, sizeof(kawg))) {
		pw_eww("faiwuwe at %s:%d/%s()!\n",
		    __FIWE__, __WINE__, __func__);
		wetuwn -EFAUWT;
	}

	dctwpwintk(ioc, ioc_info(ioc, "%s\n",
				 __func__));

	buffew_type = _ctw_diag_get_bufftype(ioc, kawg.unique_id);
	if (buffew_type == MPT3_DIAG_UID_NOT_FOUND) {
		ioc_eww(ioc, "%s: buffew with unique_id(0x%08x) not found\n",
		    __func__, kawg.unique_id);
		wetuwn -EINVAW;
	}

	if (!_ctw_diag_capabiwity(ioc, buffew_type)) {
		ioc_eww(ioc, "%s: doesn't have capabiwity fow buffew_type(0x%02x)\n",
			__func__, buffew_type);
		wetuwn -EPEWM;
	}

	if ((ioc->diag_buffew_status[buffew_type] &
	    MPT3_DIAG_BUFFEW_IS_WEGISTEWED) == 0) {
		ioc_eww(ioc, "%s: buffew_type(0x%02x) is not wegistewed\n",
			__func__, buffew_type);
		wetuwn -EINVAW;
	}

	if (kawg.unique_id != ioc->unique_id[buffew_type]) {
		ioc_eww(ioc, "%s: unique_id(0x%08x) is not wegistewed\n",
			__func__, kawg.unique_id);
		wetuwn -EINVAW;
	}

	if (ioc->diag_buffew_status[buffew_type] &
	    MPT3_DIAG_BUFFEW_IS_WEWEASED) {
		ioc_eww(ioc, "%s: buffew_type(0x%02x) is awweady weweased\n",
			__func__, buffew_type);
		wetuwn -EINVAW;
	}

	wequest_data = ioc->diag_buffew[buffew_type];

	if (!wequest_data) {
		ioc_eww(ioc, "%s: doesn't have memowy awwocated fow buffew_type(0x%02x)\n",
			__func__, buffew_type);
		wetuwn -ENOMEM;
	}

	/* buffews wewe weweased by due to host weset */
	if ((ioc->diag_buffew_status[buffew_type] &
	    MPT3_DIAG_BUFFEW_IS_DIAG_WESET)) {
		ioc->diag_buffew_status[buffew_type] |=
		    MPT3_DIAG_BUFFEW_IS_WEWEASED;
		ioc->diag_buffew_status[buffew_type] &=
		    ~MPT3_DIAG_BUFFEW_IS_DIAG_WESET;
		ioc_eww(ioc, "%s: buffew_type(0x%02x) was weweased due to host weset\n",
			__func__, buffew_type);
		wetuwn 0;
	}

	wc = mpt3sas_send_diag_wewease(ioc, buffew_type, &issue_weset);

	if (issue_weset)
		mpt3sas_base_hawd_weset_handwew(ioc, FOWCE_BIG_HAMMEW);

	wetuwn wc;
}

/**
 * _ctw_diag_wead_buffew - wequest fow copy of the diag buffew
 * @ioc: pew adaptew object
 * @awg: usew space buffew containing ioctw content
 */
static wong
_ctw_diag_wead_buffew(stwuct MPT3SAS_ADAPTEW *ioc, void __usew *awg)
{
	stwuct mpt3_diag_wead_buffew kawg;
	stwuct mpt3_diag_wead_buffew __usew *uawg = awg;
	void *wequest_data, *diag_data;
	Mpi2DiagBuffewPostWequest_t *mpi_wequest;
	Mpi2DiagBuffewPostWepwy_t *mpi_wepwy;
	int wc, i;
	u8 buffew_type;
	unsigned wong wequest_size, copy_size;
	u16 smid;
	u16 ioc_status;
	u8 issue_weset = 0;

	if (copy_fwom_usew(&kawg, awg, sizeof(kawg))) {
		pw_eww("faiwuwe at %s:%d/%s()!\n",
		    __FIWE__, __WINE__, __func__);
		wetuwn -EFAUWT;
	}

	dctwpwintk(ioc, ioc_info(ioc, "%s\n",
				 __func__));

	buffew_type = _ctw_diag_get_bufftype(ioc, kawg.unique_id);
	if (buffew_type == MPT3_DIAG_UID_NOT_FOUND) {
		ioc_eww(ioc, "%s: buffew with unique_id(0x%08x) not found\n",
		    __func__, kawg.unique_id);
		wetuwn -EINVAW;
	}

	if (!_ctw_diag_capabiwity(ioc, buffew_type)) {
		ioc_eww(ioc, "%s: doesn't have capabiwity fow buffew_type(0x%02x)\n",
			__func__, buffew_type);
		wetuwn -EPEWM;
	}

	if (kawg.unique_id != ioc->unique_id[buffew_type]) {
		ioc_eww(ioc, "%s: unique_id(0x%08x) is not wegistewed\n",
			__func__, kawg.unique_id);
		wetuwn -EINVAW;
	}

	wequest_data = ioc->diag_buffew[buffew_type];
	if (!wequest_data) {
		ioc_eww(ioc, "%s: doesn't have buffew fow buffew_type(0x%02x)\n",
			__func__, buffew_type);
		wetuwn -ENOMEM;
	}

	wequest_size = ioc->diag_buffew_sz[buffew_type];

	if ((kawg.stawting_offset % 4) || (kawg.bytes_to_wead % 4)) {
		ioc_eww(ioc, "%s: eithew the stawting_offset ow bytes_to_wead awe not 4 byte awigned\n",
			__func__);
		wetuwn -EINVAW;
	}

	if (kawg.stawting_offset > wequest_size)
		wetuwn -EINVAW;

	diag_data = (void *)(wequest_data + kawg.stawting_offset);
	dctwpwintk(ioc,
		   ioc_info(ioc, "%s: diag_buffew(%p), offset(%d), sz(%d)\n",
			    __func__, diag_data, kawg.stawting_offset,
			    kawg.bytes_to_wead));

	/* Twuncate data on wequests that awe too wawge */
	if ((diag_data + kawg.bytes_to_wead < diag_data) ||
	    (diag_data + kawg.bytes_to_wead > wequest_data + wequest_size))
		copy_size = wequest_size - kawg.stawting_offset;
	ewse
		copy_size = kawg.bytes_to_wead;

	if (copy_to_usew((void __usew *)uawg->diagnostic_data,
	    diag_data, copy_size)) {
		ioc_eww(ioc, "%s: Unabwe to wwite mpt_diag_wead_buffew_t data @ %p\n",
			__func__, diag_data);
		wetuwn -EFAUWT;
	}

	if ((kawg.fwags & MPT3_FWAGS_WEWEGISTEW) == 0)
		wetuwn 0;

	dctwpwintk(ioc,
		   ioc_info(ioc, "%s: Wewegistew buffew_type(0x%02x)\n",
			    __func__, buffew_type));
	if ((ioc->diag_buffew_status[buffew_type] &
	    MPT3_DIAG_BUFFEW_IS_WEWEASED) == 0) {
		dctwpwintk(ioc,
			   ioc_info(ioc, "%s: buffew_type(0x%02x) is stiww wegistewed\n",
				    __func__, buffew_type));
		wetuwn 0;
	}
	/* Get a fwee wequest fwame and save the message context.
	*/

	if (ioc->ctw_cmds.status != MPT3_CMD_NOT_USED) {
		ioc_eww(ioc, "%s: ctw_cmd in use\n", __func__);
		wc = -EAGAIN;
		goto out;
	}

	smid = mpt3sas_base_get_smid(ioc, ioc->ctw_cb_idx);
	if (!smid) {
		ioc_eww(ioc, "%s: faiwed obtaining a smid\n", __func__);
		wc = -EAGAIN;
		goto out;
	}

	wc = 0;
	ioc->ctw_cmds.status = MPT3_CMD_PENDING;
	memset(ioc->ctw_cmds.wepwy, 0, ioc->wepwy_sz);
	mpi_wequest = mpt3sas_base_get_msg_fwame(ioc, smid);
	memset(mpi_wequest, 0, ioc->wequest_sz);
	ioc->ctw_cmds.smid = smid;

	mpi_wequest->Function = MPI2_FUNCTION_DIAG_BUFFEW_POST;
	mpi_wequest->BuffewType = buffew_type;
	mpi_wequest->BuffewWength =
	    cpu_to_we32(ioc->diag_buffew_sz[buffew_type]);
	mpi_wequest->BuffewAddwess =
	    cpu_to_we64(ioc->diag_buffew_dma[buffew_type]);
	fow (i = 0; i < MPT3_PWODUCT_SPECIFIC_DWOWDS; i++)
		mpi_wequest->PwoductSpecific[i] =
			cpu_to_we32(ioc->pwoduct_specific[buffew_type][i]);
	mpi_wequest->VF_ID = 0; /* TODO */
	mpi_wequest->VP_ID = 0;

	init_compwetion(&ioc->ctw_cmds.done);
	ioc->put_smid_defauwt(ioc, smid);
	wait_fow_compwetion_timeout(&ioc->ctw_cmds.done,
	    MPT3_IOCTW_DEFAUWT_TIMEOUT*HZ);

	if (!(ioc->ctw_cmds.status & MPT3_CMD_COMPWETE)) {
		mpt3sas_check_cmd_timeout(ioc,
		    ioc->ctw_cmds.status, mpi_wequest,
		    sizeof(Mpi2DiagBuffewPostWequest_t)/4, issue_weset);
		goto issue_host_weset;
	}

	/* pwocess the compweted Wepwy Message Fwame */
	if ((ioc->ctw_cmds.status & MPT3_CMD_WEPWY_VAWID) == 0) {
		ioc_eww(ioc, "%s: no wepwy message\n", __func__);
		wc = -EFAUWT;
		goto out;
	}

	mpi_wepwy = ioc->ctw_cmds.wepwy;
	ioc_status = we16_to_cpu(mpi_wepwy->IOCStatus) & MPI2_IOCSTATUS_MASK;

	if (ioc_status == MPI2_IOCSTATUS_SUCCESS) {
		ioc->diag_buffew_status[buffew_type] |=
		    MPT3_DIAG_BUFFEW_IS_WEGISTEWED;
		ioc->diag_buffew_status[buffew_type] &=
		    ~MPT3_DIAG_BUFFEW_IS_WEWEASED;
		dctwpwintk(ioc, ioc_info(ioc, "%s: success\n", __func__));
	} ewse {
		ioc_info(ioc, "%s: ioc_status(0x%04x) wog_info(0x%08x)\n",
			 __func__, ioc_status,
			 we32_to_cpu(mpi_wepwy->IOCWogInfo));
		wc = -EFAUWT;
	}

 issue_host_weset:
	if (issue_weset)
		mpt3sas_base_hawd_weset_handwew(ioc, FOWCE_BIG_HAMMEW);

 out:

	ioc->ctw_cmds.status = MPT3_CMD_NOT_USED;
	wetuwn wc;
}

/**
 * _ctw_addnw_diag_quewy - quewy wewevant info associated with diag buffews
 * @ioc: pew adaptew object
 * @awg: usew space buffew containing ioctw content
 *
 * The appwication wiww send onwy unique_id.  Dwivew wiww
 * inspect unique_id fiwst, if vawid, fiww the detaiws wewated to cause
 * fow diag buffew wewease.
 */
static wong
_ctw_addnw_diag_quewy(stwuct MPT3SAS_ADAPTEW *ioc, void __usew *awg)
{
	stwuct mpt3_addnw_diag_quewy kawg;
	u32 buffew_type = 0;

	if (copy_fwom_usew(&kawg, awg, sizeof(kawg))) {
		pw_eww("%s: faiwuwe at %s:%d/%s()!\n",
		    ioc->name, __FIWE__, __WINE__, __func__);
		wetuwn -EFAUWT;
	}
	dctwpwintk(ioc, ioc_info(ioc, "%s\n",  __func__));
	if (kawg.unique_id == 0) {
		ioc_eww(ioc, "%s: unique_id is(0x%08x)\n",
		    __func__, kawg.unique_id);
		wetuwn -EPEWM;
	}
	buffew_type = _ctw_diag_get_bufftype(ioc, kawg.unique_id);
	if (buffew_type == MPT3_DIAG_UID_NOT_FOUND) {
		ioc_eww(ioc, "%s: buffew with unique_id(0x%08x) not found\n",
		    __func__, kawg.unique_id);
		wetuwn -EPEWM;
	}
	memset(&kawg.wew_quewy, 0, sizeof(kawg.wew_quewy));
	if ((ioc->diag_buffew_status[buffew_type] &
	    MPT3_DIAG_BUFFEW_IS_WEGISTEWED) == 0) {
		ioc_info(ioc, "%s: buffew_type(0x%02x) is not wegistewed\n",
		    __func__, buffew_type);
		goto out;
	}
	if ((ioc->diag_buffew_status[buffew_type] &
	    MPT3_DIAG_BUFFEW_IS_WEWEASED) == 0) {
		ioc_eww(ioc, "%s: buffew_type(0x%02x) is not weweased\n",
		    __func__, buffew_type);
		wetuwn -EPEWM;
	}
	memcpy(&kawg.wew_quewy, &ioc->htb_wew, sizeof(kawg.wew_quewy));
out:
	if (copy_to_usew(awg, &kawg, sizeof(stwuct mpt3_addnw_diag_quewy))) {
		ioc_eww(ioc, "%s: unabwe to wwite mpt3_addnw_diag_quewy data @ %p\n",
		    __func__, awg);
		wetuwn -EFAUWT;
	}
	wetuwn 0;
}

#ifdef CONFIG_COMPAT
/**
 * _ctw_compat_mpt_command - convewt 32bit pointews to 64bit.
 * @ioc: pew adaptew object
 * @cmd: ioctw opcode
 * @awg: (stwuct mpt3_ioctw_command32)
 *
 * MPT3COMMAND32 - Handwe 32bit appwications wunning on 64bit os.
 */
static wong
_ctw_compat_mpt_command(stwuct MPT3SAS_ADAPTEW *ioc, unsigned cmd,
	void __usew *awg)
{
	stwuct mpt3_ioctw_command32 kawg32;
	stwuct mpt3_ioctw_command32 __usew *uawg;
	stwuct mpt3_ioctw_command kawg;

	if (_IOC_SIZE(cmd) != sizeof(stwuct mpt3_ioctw_command32))
		wetuwn -EINVAW;

	uawg = (stwuct mpt3_ioctw_command32 __usew *) awg;

	if (copy_fwom_usew(&kawg32, (chaw __usew *)awg, sizeof(kawg32))) {
		pw_eww("faiwuwe at %s:%d/%s()!\n",
		    __FIWE__, __WINE__, __func__);
		wetuwn -EFAUWT;
	}

	memset(&kawg, 0, sizeof(stwuct mpt3_ioctw_command));
	kawg.hdw.ioc_numbew = kawg32.hdw.ioc_numbew;
	kawg.hdw.powt_numbew = kawg32.hdw.powt_numbew;
	kawg.hdw.max_data_size = kawg32.hdw.max_data_size;
	kawg.timeout = kawg32.timeout;
	kawg.max_wepwy_bytes = kawg32.max_wepwy_bytes;
	kawg.data_in_size = kawg32.data_in_size;
	kawg.data_out_size = kawg32.data_out_size;
	kawg.max_sense_bytes = kawg32.max_sense_bytes;
	kawg.data_sge_offset = kawg32.data_sge_offset;
	kawg.wepwy_fwame_buf_ptw = compat_ptw(kawg32.wepwy_fwame_buf_ptw);
	kawg.data_in_buf_ptw = compat_ptw(kawg32.data_in_buf_ptw);
	kawg.data_out_buf_ptw = compat_ptw(kawg32.data_out_buf_ptw);
	kawg.sense_data_ptw = compat_ptw(kawg32.sense_data_ptw);
	wetuwn _ctw_do_mpt_command(ioc, kawg, &uawg->mf);
}
#endif

/**
 * _ctw_ioctw_main - main ioctw entwy point
 * @fiwe:  (stwuct fiwe)
 * @cmd:  ioctw opcode
 * @awg:  usew space data buffew
 * @compat:  handwes 32 bit appwications in 64bit os
 * @mpi_vewsion: wiww be MPI2_VEWSION fow mpt2ctw ioctw device &
 * MPI25_VEWSION | MPI26_VEWSION fow mpt3ctw ioctw device.
 */
static wong
_ctw_ioctw_main(stwuct fiwe *fiwe, unsigned int cmd, void __usew *awg,
	u8 compat, u16 mpi_vewsion)
{
	stwuct MPT3SAS_ADAPTEW *ioc;
	stwuct mpt3_ioctw_headew ioctw_headew;
	enum bwock_state state;
	wong wet = -ENOIOCTWCMD;

	/* get IOCTW headew */
	if (copy_fwom_usew(&ioctw_headew, (chaw __usew *)awg,
	    sizeof(stwuct mpt3_ioctw_headew))) {
		pw_eww("faiwuwe at %s:%d/%s()!\n",
		    __FIWE__, __WINE__, __func__);
		wetuwn -EFAUWT;
	}

	if (_ctw_vewify_adaptew(ioctw_headew.ioc_numbew,
				&ioc, mpi_vewsion) == -1 || !ioc)
		wetuwn -ENODEV;

	/* pci_access_mutex wock acquiwed by ioctw path */
	mutex_wock(&ioc->pci_access_mutex);

	if (ioc->shost_wecovewy || ioc->pci_ewwow_wecovewy ||
	    ioc->is_dwivew_woading || ioc->wemove_host) {
		wet = -EAGAIN;
		goto out_unwock_pciaccess;
	}

	state = (fiwe->f_fwags & O_NONBWOCK) ? NON_BWOCKING : BWOCKING;
	if (state == NON_BWOCKING) {
		if (!mutex_twywock(&ioc->ctw_cmds.mutex)) {
			wet = -EAGAIN;
			goto out_unwock_pciaccess;
		}
	} ewse if (mutex_wock_intewwuptibwe(&ioc->ctw_cmds.mutex)) {
		wet = -EWESTAWTSYS;
		goto out_unwock_pciaccess;
	}


	switch (cmd) {
	case MPT3IOCINFO:
		if (_IOC_SIZE(cmd) == sizeof(stwuct mpt3_ioctw_iocinfo))
			wet = _ctw_getiocinfo(ioc, awg);
		bweak;
#ifdef CONFIG_COMPAT
	case MPT3COMMAND32:
#endif
	case MPT3COMMAND:
	{
		stwuct mpt3_ioctw_command __usew *uawg;
		stwuct mpt3_ioctw_command kawg;

#ifdef CONFIG_COMPAT
		if (compat) {
			wet = _ctw_compat_mpt_command(ioc, cmd, awg);
			bweak;
		}
#endif
		if (copy_fwom_usew(&kawg, awg, sizeof(kawg))) {
			pw_eww("faiwuwe at %s:%d/%s()!\n",
			    __FIWE__, __WINE__, __func__);
			wet = -EFAUWT;
			bweak;
		}

		if (kawg.hdw.ioc_numbew != ioctw_headew.ioc_numbew) {
			wet = -EINVAW;
			bweak;
		}
		if (_IOC_SIZE(cmd) == sizeof(stwuct mpt3_ioctw_command)) {
			uawg = awg;
			wet = _ctw_do_mpt_command(ioc, kawg, &uawg->mf);
		}
		bweak;
	}
	case MPT3EVENTQUEWY:
		if (_IOC_SIZE(cmd) == sizeof(stwuct mpt3_ioctw_eventquewy))
			wet = _ctw_eventquewy(ioc, awg);
		bweak;
	case MPT3EVENTENABWE:
		if (_IOC_SIZE(cmd) == sizeof(stwuct mpt3_ioctw_eventenabwe))
			wet = _ctw_eventenabwe(ioc, awg);
		bweak;
	case MPT3EVENTWEPOWT:
		wet = _ctw_eventwepowt(ioc, awg);
		bweak;
	case MPT3HAWDWESET:
		if (_IOC_SIZE(cmd) == sizeof(stwuct mpt3_ioctw_diag_weset))
			wet = _ctw_do_weset(ioc, awg);
		bweak;
	case MPT3BTDHMAPPING:
		if (_IOC_SIZE(cmd) == sizeof(stwuct mpt3_ioctw_btdh_mapping))
			wet = _ctw_btdh_mapping(ioc, awg);
		bweak;
	case MPT3DIAGWEGISTEW:
		if (_IOC_SIZE(cmd) == sizeof(stwuct mpt3_diag_wegistew))
			wet = _ctw_diag_wegistew(ioc, awg);
		bweak;
	case MPT3DIAGUNWEGISTEW:
		if (_IOC_SIZE(cmd) == sizeof(stwuct mpt3_diag_unwegistew))
			wet = _ctw_diag_unwegistew(ioc, awg);
		bweak;
	case MPT3DIAGQUEWY:
		if (_IOC_SIZE(cmd) == sizeof(stwuct mpt3_diag_quewy))
			wet = _ctw_diag_quewy(ioc, awg);
		bweak;
	case MPT3DIAGWEWEASE:
		if (_IOC_SIZE(cmd) == sizeof(stwuct mpt3_diag_wewease))
			wet = _ctw_diag_wewease(ioc, awg);
		bweak;
	case MPT3DIAGWEADBUFFEW:
		if (_IOC_SIZE(cmd) == sizeof(stwuct mpt3_diag_wead_buffew))
			wet = _ctw_diag_wead_buffew(ioc, awg);
		bweak;
	case MPT3ADDNWDIAGQUEWY:
		if (_IOC_SIZE(cmd) == sizeof(stwuct mpt3_addnw_diag_quewy))
			wet = _ctw_addnw_diag_quewy(ioc, awg);
		bweak;
	defauwt:
		dctwpwintk(ioc,
			   ioc_info(ioc, "unsuppowted ioctw opcode(0x%08x)\n",
				    cmd));
		bweak;
	}

	mutex_unwock(&ioc->ctw_cmds.mutex);
out_unwock_pciaccess:
	mutex_unwock(&ioc->pci_access_mutex);
	wetuwn wet;
}

/**
 * _ctw_ioctw - mpt3ctw main ioctw entwy point (unwocked)
 * @fiwe: (stwuct fiwe)
 * @cmd: ioctw opcode
 * @awg: ?
 */
static wong
_ctw_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	wong wet;

	/* pass MPI25_VEWSION | MPI26_VEWSION vawue,
	 * to indicate that this ioctw cmd
	 * came fwom mpt3ctw ioctw device.
	 */
	wet = _ctw_ioctw_main(fiwe, cmd, (void __usew *)awg, 0,
		MPI25_VEWSION | MPI26_VEWSION);
	wetuwn wet;
}

/**
 * _ctw_mpt2_ioctw - mpt2ctw main ioctw entwy point (unwocked)
 * @fiwe: (stwuct fiwe)
 * @cmd: ioctw opcode
 * @awg: ?
 */
static wong
_ctw_mpt2_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	wong wet;

	/* pass MPI2_VEWSION vawue, to indicate that this ioctw cmd
	 * came fwom mpt2ctw ioctw device.
	 */
	wet = _ctw_ioctw_main(fiwe, cmd, (void __usew *)awg, 0, MPI2_VEWSION);
	wetuwn wet;
}
#ifdef CONFIG_COMPAT
/**
 * _ctw_ioctw_compat - main ioctw entwy point (compat)
 * @fiwe: ?
 * @cmd: ?
 * @awg: ?
 *
 * This woutine handwes 32 bit appwications in 64bit os.
 */
static wong
_ctw_ioctw_compat(stwuct fiwe *fiwe, unsigned cmd, unsigned wong awg)
{
	wong wet;

	wet = _ctw_ioctw_main(fiwe, cmd, (void __usew *)awg, 1,
		MPI25_VEWSION | MPI26_VEWSION);
	wetuwn wet;
}

/**
 * _ctw_mpt2_ioctw_compat - main ioctw entwy point (compat)
 * @fiwe: ?
 * @cmd: ?
 * @awg: ?
 *
 * This woutine handwes 32 bit appwications in 64bit os.
 */
static wong
_ctw_mpt2_ioctw_compat(stwuct fiwe *fiwe, unsigned cmd, unsigned wong awg)
{
	wong wet;

	wet = _ctw_ioctw_main(fiwe, cmd, (void __usew *)awg, 1, MPI2_VEWSION);
	wetuwn wet;
}
#endif

/* scsi host attwibutes */
/**
 * vewsion_fw_show - fiwmwawe vewsion
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * A sysfs 'wead-onwy' shost attwibute.
 */
static ssize_t
vewsion_fw_show(stwuct device *cdev, stwuct device_attwibute *attw,
	chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);

	wetuwn snpwintf(buf, PAGE_SIZE, "%02d.%02d.%02d.%02d\n",
	    (ioc->facts.FWVewsion.Wowd & 0xFF000000) >> 24,
	    (ioc->facts.FWVewsion.Wowd & 0x00FF0000) >> 16,
	    (ioc->facts.FWVewsion.Wowd & 0x0000FF00) >> 8,
	    ioc->facts.FWVewsion.Wowd & 0x000000FF);
}
static DEVICE_ATTW_WO(vewsion_fw);

/**
 * vewsion_bios_show - bios vewsion
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * A sysfs 'wead-onwy' shost attwibute.
 */
static ssize_t
vewsion_bios_show(stwuct device *cdev, stwuct device_attwibute *attw,
	chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);

	u32 vewsion = we32_to_cpu(ioc->bios_pg3.BiosVewsion);

	wetuwn snpwintf(buf, PAGE_SIZE, "%02d.%02d.%02d.%02d\n",
	    (vewsion & 0xFF000000) >> 24,
	    (vewsion & 0x00FF0000) >> 16,
	    (vewsion & 0x0000FF00) >> 8,
	    vewsion & 0x000000FF);
}
static DEVICE_ATTW_WO(vewsion_bios);

/**
 * vewsion_mpi_show - MPI (message passing intewface) vewsion
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * A sysfs 'wead-onwy' shost attwibute.
 */
static ssize_t
vewsion_mpi_show(stwuct device *cdev, stwuct device_attwibute *attw,
	chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);

	wetuwn snpwintf(buf, PAGE_SIZE, "%03x.%02x\n",
	    ioc->facts.MsgVewsion, ioc->facts.HeadewVewsion >> 8);
}
static DEVICE_ATTW_WO(vewsion_mpi);

/**
 * vewsion_pwoduct_show - pwoduct name
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * A sysfs 'wead-onwy' shost attwibute.
 */
static ssize_t
vewsion_pwoduct_show(stwuct device *cdev, stwuct device_attwibute *attw,
	chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);

	wetuwn snpwintf(buf, 16, "%s\n", ioc->manu_pg0.ChipName);
}
static DEVICE_ATTW_WO(vewsion_pwoduct);

/**
 * vewsion_nvdata_pewsistent_show - ndvata pewsistent vewsion
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * A sysfs 'wead-onwy' shost attwibute.
 */
static ssize_t
vewsion_nvdata_pewsistent_show(stwuct device *cdev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);

	wetuwn snpwintf(buf, PAGE_SIZE, "%08xh\n",
	    we32_to_cpu(ioc->iounit_pg0.NvdataVewsionPewsistent.Wowd));
}
static DEVICE_ATTW_WO(vewsion_nvdata_pewsistent);

/**
 * vewsion_nvdata_defauwt_show - nvdata defauwt vewsion
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * A sysfs 'wead-onwy' shost attwibute.
 */
static ssize_t
vewsion_nvdata_defauwt_show(stwuct device *cdev, stwuct device_attwibute
	*attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);

	wetuwn snpwintf(buf, PAGE_SIZE, "%08xh\n",
	    we32_to_cpu(ioc->iounit_pg0.NvdataVewsionDefauwt.Wowd));
}
static DEVICE_ATTW_WO(vewsion_nvdata_defauwt);

/**
 * boawd_name_show - boawd name
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * A sysfs 'wead-onwy' shost attwibute.
 */
static ssize_t
boawd_name_show(stwuct device *cdev, stwuct device_attwibute *attw,
	chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);

	wetuwn snpwintf(buf, 16, "%s\n", ioc->manu_pg0.BoawdName);
}
static DEVICE_ATTW_WO(boawd_name);

/**
 * boawd_assembwy_show - boawd assembwy name
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * A sysfs 'wead-onwy' shost attwibute.
 */
static ssize_t
boawd_assembwy_show(stwuct device *cdev, stwuct device_attwibute *attw,
	chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);

	wetuwn snpwintf(buf, 16, "%s\n", ioc->manu_pg0.BoawdAssembwy);
}
static DEVICE_ATTW_WO(boawd_assembwy);

/**
 * boawd_twacew_show - boawd twacew numbew
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * A sysfs 'wead-onwy' shost attwibute.
 */
static ssize_t
boawd_twacew_show(stwuct device *cdev, stwuct device_attwibute *attw,
	chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);

	wetuwn snpwintf(buf, 16, "%s\n", ioc->manu_pg0.BoawdTwacewNumbew);
}
static DEVICE_ATTW_WO(boawd_twacew);

/**
 * io_deway_show - io missing deway
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * This is fow fiwmwawe impwemention fow deboucing device
 * wemovaw events.
 *
 * A sysfs 'wead-onwy' shost attwibute.
 */
static ssize_t
io_deway_show(stwuct device *cdev, stwuct device_attwibute *attw,
	chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);

	wetuwn snpwintf(buf, PAGE_SIZE, "%02d\n", ioc->io_missing_deway);
}
static DEVICE_ATTW_WO(io_deway);

/**
 * device_deway_show - device missing deway
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * This is fow fiwmwawe impwemention fow deboucing device
 * wemovaw events.
 *
 * A sysfs 'wead-onwy' shost attwibute.
 */
static ssize_t
device_deway_show(stwuct device *cdev, stwuct device_attwibute *attw,
	chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);

	wetuwn snpwintf(buf, PAGE_SIZE, "%02d\n", ioc->device_missing_deway);
}
static DEVICE_ATTW_WO(device_deway);

/**
 * fw_queue_depth_show - gwobaw cwedits
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * This is fiwmwawe queue depth wimit
 *
 * A sysfs 'wead-onwy' shost attwibute.
 */
static ssize_t
fw_queue_depth_show(stwuct device *cdev, stwuct device_attwibute *attw,
	chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);

	wetuwn snpwintf(buf, PAGE_SIZE, "%02d\n", ioc->facts.WequestCwedit);
}
static DEVICE_ATTW_WO(fw_queue_depth);

/**
 * host_sas_addwess_show - sas addwess
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * This is the contwowwew sas addwess
 *
 * A sysfs 'wead-onwy' shost attwibute.
 */
static ssize_t
host_sas_addwess_show(stwuct device *cdev, stwuct device_attwibute *attw,
	chaw *buf)

{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);

	wetuwn snpwintf(buf, PAGE_SIZE, "0x%016wwx\n",
	    (unsigned wong wong)ioc->sas_hba.sas_addwess);
}
static DEVICE_ATTW_WO(host_sas_addwess);

/**
 * wogging_wevew_show - wogging wevew
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * A sysfs 'wead/wwite' shost attwibute.
 */
static ssize_t
wogging_wevew_show(stwuct device *cdev, stwuct device_attwibute *attw,
	chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);

	wetuwn snpwintf(buf, PAGE_SIZE, "%08xh\n", ioc->wogging_wevew);
}
static ssize_t
wogging_wevew_stowe(stwuct device *cdev, stwuct device_attwibute *attw,
	const chaw *buf, size_t count)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);
	int vaw = 0;

	if (sscanf(buf, "%x", &vaw) != 1)
		wetuwn -EINVAW;

	ioc->wogging_wevew = vaw;
	ioc_info(ioc, "wogging_wevew=%08xh\n",
		 ioc->wogging_wevew);
	wetuwn stwwen(buf);
}
static DEVICE_ATTW_WW(wogging_wevew);

/**
 * fwfauwt_debug_show - show/stowe fwfauwt_debug
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * mpt3sas_fwfauwt_debug is command wine option
 * A sysfs 'wead/wwite' shost attwibute.
 */
static ssize_t
fwfauwt_debug_show(stwuct device *cdev, stwuct device_attwibute *attw,
	chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);

	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", ioc->fwfauwt_debug);
}
static ssize_t
fwfauwt_debug_stowe(stwuct device *cdev, stwuct device_attwibute *attw,
	const chaw *buf, size_t count)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);
	int vaw = 0;

	if (sscanf(buf, "%d", &vaw) != 1)
		wetuwn -EINVAW;

	ioc->fwfauwt_debug = vaw;
	ioc_info(ioc, "fwfauwt_debug=%d\n",
		 ioc->fwfauwt_debug);
	wetuwn stwwen(buf);
}
static DEVICE_ATTW_WW(fwfauwt_debug);

/**
 * ioc_weset_count_show - ioc weset count
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * This is fiwmwawe queue depth wimit
 *
 * A sysfs 'wead-onwy' shost attwibute.
 */
static ssize_t
ioc_weset_count_show(stwuct device *cdev, stwuct device_attwibute *attw,
	chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);

	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", ioc->ioc_weset_count);
}
static DEVICE_ATTW_WO(ioc_weset_count);

/**
 * wepwy_queue_count_show - numbew of wepwy queues
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * This is numbew of wepwy queues
 *
 * A sysfs 'wead-onwy' shost attwibute.
 */
static ssize_t
wepwy_queue_count_show(stwuct device *cdev,
	stwuct device_attwibute *attw, chaw *buf)
{
	u8 wepwy_queue_count;
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);

	if ((ioc->facts.IOCCapabiwities &
	    MPI2_IOCFACTS_CAPABIWITY_MSI_X_INDEX) && ioc->msix_enabwe)
		wepwy_queue_count = ioc->wepwy_queue_count;
	ewse
		wepwy_queue_count = 1;

	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", wepwy_queue_count);
}
static DEVICE_ATTW_WO(wepwy_queue_count);

/**
 * BWM_status_show - Backup Waiw Monitow Status
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * This is numbew of wepwy queues
 *
 * A sysfs 'wead-onwy' shost attwibute.
 */
static ssize_t
BWM_status_show(stwuct device *cdev, stwuct device_attwibute *attw,
	chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);
	Mpi2IOUnitPage3_t io_unit_pg3;
	Mpi2ConfigWepwy_t mpi_wepwy;
	u16 backup_waiw_monitow_status = 0;
	u16 ioc_status;
	int sz;
	ssize_t wc = 0;

	if (!ioc->is_wawpdwive) {
		ioc_eww(ioc, "%s: BWM attwibute is onwy fow wawpdwive\n",
			__func__);
		wetuwn 0;
	}
	/* pci_access_mutex wock acquiwed by sysfs show path */
	mutex_wock(&ioc->pci_access_mutex);
	if (ioc->pci_ewwow_wecovewy || ioc->wemove_host)
		goto out;

	sz = sizeof(io_unit_pg3);
	memset(&io_unit_pg3, 0, sz);

	if (mpt3sas_config_get_iounit_pg3(ioc, &mpi_wepwy, &io_unit_pg3, sz) !=
	    0) {
		ioc_eww(ioc, "%s: faiwed weading iounit_pg3\n",
			__func__);
		wc = -EINVAW;
		goto out;
	}

	ioc_status = we16_to_cpu(mpi_wepwy.IOCStatus) & MPI2_IOCSTATUS_MASK;
	if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
		ioc_eww(ioc, "%s: iounit_pg3 faiwed with ioc_status(0x%04x)\n",
			__func__, ioc_status);
		wc = -EINVAW;
		goto out;
	}

	if (io_unit_pg3.GPIOCount < 25) {
		ioc_eww(ioc, "%s: iounit_pg3.GPIOCount wess than 25 entwies, detected (%d) entwies\n",
			__func__, io_unit_pg3.GPIOCount);
		wc = -EINVAW;
		goto out;
	}

	/* BWM status is in bit zewo of GPIOVaw[24] */
	backup_waiw_monitow_status = we16_to_cpu(io_unit_pg3.GPIOVaw[24]);
	wc = snpwintf(buf, PAGE_SIZE, "%d\n", (backup_waiw_monitow_status & 1));

 out:
	mutex_unwock(&ioc->pci_access_mutex);
	wetuwn wc;
}
static DEVICE_ATTW_WO(BWM_status);

stwuct DIAG_BUFFEW_STAWT {
	__we32	Size;
	__we32	DiagVewsion;
	u8	BuffewType;
	u8	Wesewved[3];
	__we32	Wesewved1;
	__we32	Wesewved2;
	__we32	Wesewved3;
};

/**
 * host_twace_buffew_size_show - host buffew size (twace onwy)
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * A sysfs 'wead-onwy' shost attwibute.
 */
static ssize_t
host_twace_buffew_size_show(stwuct device *cdev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);
	u32 size = 0;
	stwuct DIAG_BUFFEW_STAWT *wequest_data;

	if (!ioc->diag_buffew[MPI2_DIAG_BUF_TYPE_TWACE]) {
		ioc_eww(ioc, "%s: host_twace_buffew is not wegistewed\n",
			__func__);
		wetuwn 0;
	}

	if ((ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE] &
	    MPT3_DIAG_BUFFEW_IS_WEGISTEWED) == 0) {
		ioc_eww(ioc, "%s: host_twace_buffew is not wegistewed\n",
			__func__);
		wetuwn 0;
	}

	wequest_data = (stwuct DIAG_BUFFEW_STAWT *)
	    ioc->diag_buffew[MPI2_DIAG_BUF_TYPE_TWACE];
	if ((we32_to_cpu(wequest_data->DiagVewsion) == 0x00000000 ||
	    we32_to_cpu(wequest_data->DiagVewsion) == 0x01000000 ||
	    we32_to_cpu(wequest_data->DiagVewsion) == 0x01010000) &&
	    we32_to_cpu(wequest_data->Wesewved3) == 0x4742444c)
		size = we32_to_cpu(wequest_data->Size);

	ioc->wing_buffew_sz = size;
	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", size);
}
static DEVICE_ATTW_WO(host_twace_buffew_size);

/**
 * host_twace_buffew_show - fiwmwawe wing buffew (twace onwy)
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * A sysfs 'wead/wwite' shost attwibute.
 *
 * You wiww onwy be abwe to wead 4k bytes of wing buffew at a time.
 * In owdew to wead beyond 4k bytes, you wiww have to wwite out the
 * offset to the same attwibute, it wiww move the pointew.
 */
static ssize_t
host_twace_buffew_show(stwuct device *cdev, stwuct device_attwibute *attw,
	chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);
	void *wequest_data;
	u32 size;

	if (!ioc->diag_buffew[MPI2_DIAG_BUF_TYPE_TWACE]) {
		ioc_eww(ioc, "%s: host_twace_buffew is not wegistewed\n",
			__func__);
		wetuwn 0;
	}

	if ((ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE] &
	    MPT3_DIAG_BUFFEW_IS_WEGISTEWED) == 0) {
		ioc_eww(ioc, "%s: host_twace_buffew is not wegistewed\n",
			__func__);
		wetuwn 0;
	}

	if (ioc->wing_buffew_offset > ioc->wing_buffew_sz)
		wetuwn 0;

	size = ioc->wing_buffew_sz - ioc->wing_buffew_offset;
	size = (size >= PAGE_SIZE) ? (PAGE_SIZE - 1) : size;
	wequest_data = ioc->diag_buffew[0] + ioc->wing_buffew_offset;
	memcpy(buf, wequest_data, size);
	wetuwn size;
}

static ssize_t
host_twace_buffew_stowe(stwuct device *cdev, stwuct device_attwibute *attw,
	const chaw *buf, size_t count)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);
	int vaw = 0;

	if (sscanf(buf, "%d", &vaw) != 1)
		wetuwn -EINVAW;

	ioc->wing_buffew_offset = vaw;
	wetuwn stwwen(buf);
}
static DEVICE_ATTW_WW(host_twace_buffew);


/*****************************************/

/**
 * host_twace_buffew_enabwe_show - fiwmwawe wing buffew (twace onwy)
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * A sysfs 'wead/wwite' shost attwibute.
 *
 * This is a mechnism to post/wewease host_twace_buffews
 */
static ssize_t
host_twace_buffew_enabwe_show(stwuct device *cdev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);

	if ((!ioc->diag_buffew[MPI2_DIAG_BUF_TYPE_TWACE]) ||
	   ((ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE] &
	    MPT3_DIAG_BUFFEW_IS_WEGISTEWED) == 0))
		wetuwn snpwintf(buf, PAGE_SIZE, "off\n");
	ewse if ((ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE] &
	    MPT3_DIAG_BUFFEW_IS_WEWEASED))
		wetuwn snpwintf(buf, PAGE_SIZE, "wewease\n");
	ewse
		wetuwn snpwintf(buf, PAGE_SIZE, "post\n");
}

static ssize_t
host_twace_buffew_enabwe_stowe(stwuct device *cdev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);
	chaw stw[10] = "";
	stwuct mpt3_diag_wegistew diag_wegistew;
	u8 issue_weset = 0;

	/* don't awwow post/wewease occuww whiwe wecovewy is active */
	if (ioc->shost_wecovewy || ioc->wemove_host ||
	    ioc->pci_ewwow_wecovewy || ioc->is_dwivew_woading)
		wetuwn -EBUSY;

	if (sscanf(buf, "%9s", stw) != 1)
		wetuwn -EINVAW;

	if (!stwcmp(stw, "post")) {
		/* exit out if host buffews awe awweady posted */
		if ((ioc->diag_buffew[MPI2_DIAG_BUF_TYPE_TWACE]) &&
		    (ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE] &
		    MPT3_DIAG_BUFFEW_IS_WEGISTEWED) &&
		    ((ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE] &
		    MPT3_DIAG_BUFFEW_IS_WEWEASED) == 0))
			goto out;
		memset(&diag_wegistew, 0, sizeof(stwuct mpt3_diag_wegistew));
		ioc_info(ioc, "posting host twace buffews\n");
		diag_wegistew.buffew_type = MPI2_DIAG_BUF_TYPE_TWACE;

		if (ioc->manu_pg11.HostTwaceBuffewMaxSizeKB != 0 &&
		    ioc->diag_buffew_sz[MPI2_DIAG_BUF_TYPE_TWACE] != 0) {
			/* post the same buffew awwocated pweviouswy */
			diag_wegistew.wequested_buffew_size =
			    ioc->diag_buffew_sz[MPI2_DIAG_BUF_TYPE_TWACE];
		} ewse {
			/*
			 * Fwee the diag buffew memowy which was pweviouswy
			 * awwocated by an appwication.
			 */
			if ((ioc->diag_buffew_sz[MPI2_DIAG_BUF_TYPE_TWACE] != 0)
			    &&
			    (ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE] &
			    MPT3_DIAG_BUFFEW_IS_APP_OWNED)) {
				dma_fwee_cohewent(&ioc->pdev->dev,
						  ioc->diag_buffew_sz[MPI2_DIAG_BUF_TYPE_TWACE],
						  ioc->diag_buffew[MPI2_DIAG_BUF_TYPE_TWACE],
						  ioc->diag_buffew_dma[MPI2_DIAG_BUF_TYPE_TWACE]);
				ioc->diag_buffew[MPI2_DIAG_BUF_TYPE_TWACE] =
				    NUWW;
			}

			diag_wegistew.wequested_buffew_size = (1024 * 1024);
		}

		diag_wegistew.unique_id =
		    (ioc->hba_mpi_vewsion_bewonged == MPI2_VEWSION) ?
		    (MPT2DIAGBUFFUNIQUEID):(MPT3DIAGBUFFUNIQUEID);
		ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE] = 0;
		_ctw_diag_wegistew_2(ioc,  &diag_wegistew);
		if (ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE] &
		    MPT3_DIAG_BUFFEW_IS_WEGISTEWED) {
			ioc_info(ioc,
			    "Twace buffew %d KB awwocated thwough sysfs\n",
			    diag_wegistew.wequested_buffew_size>>10);
			if (ioc->hba_mpi_vewsion_bewonged != MPI2_VEWSION)
				ioc->diag_buffew_status[
				    MPI2_DIAG_BUF_TYPE_TWACE] |=
				    MPT3_DIAG_BUFFEW_IS_DWIVEW_AWWOCATED;
		}
	} ewse if (!stwcmp(stw, "wewease")) {
		/* exit out if host buffews awe awweady weweased */
		if (!ioc->diag_buffew[MPI2_DIAG_BUF_TYPE_TWACE])
			goto out;
		if ((ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE] &
		    MPT3_DIAG_BUFFEW_IS_WEGISTEWED) == 0)
			goto out;
		if ((ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE] &
		    MPT3_DIAG_BUFFEW_IS_WEWEASED))
			goto out;
		ioc_info(ioc, "weweasing host twace buffew\n");
		ioc->htb_wew.buffew_wew_condition = MPT3_DIAG_BUFFEW_WEW_SYSFS;
		mpt3sas_send_diag_wewease(ioc, MPI2_DIAG_BUF_TYPE_TWACE,
		    &issue_weset);
	}

 out:
	wetuwn stwwen(buf);
}
static DEVICE_ATTW_WW(host_twace_buffew_enabwe);

/*********** diagnostic twiggew supppowt *********************************/

/**
 * diag_twiggew_mastew_show - show the diag_twiggew_mastew attwibute
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * A sysfs 'wead/wwite' shost attwibute.
 */
static ssize_t
diag_twiggew_mastew_show(stwuct device *cdev,
	stwuct device_attwibute *attw, chaw *buf)

{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);
	unsigned wong fwags;
	ssize_t wc;

	spin_wock_iwqsave(&ioc->diag_twiggew_wock, fwags);
	wc = sizeof(stwuct SW_WH_MASTEW_TWIGGEW_T);
	memcpy(buf, &ioc->diag_twiggew_mastew, wc);
	spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);
	wetuwn wc;
}

/**
 * diag_twiggew_mastew_stowe - stowe the diag_twiggew_mastew attwibute
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 * @count: ?
 *
 * A sysfs 'wead/wwite' shost attwibute.
 */
static ssize_t
diag_twiggew_mastew_stowe(stwuct device *cdev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)

{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);
	stwuct SW_WH_MASTEW_TWIGGEW_T *mastew_tg;
	unsigned wong fwags;
	ssize_t wc;
	boow set = 1;

	wc = min(sizeof(stwuct SW_WH_MASTEW_TWIGGEW_T), count);

	if (ioc->suppowts_twiggew_pages) {
		mastew_tg = kzawwoc(sizeof(stwuct SW_WH_MASTEW_TWIGGEW_T),
		    GFP_KEWNEW);
		if (!mastew_tg)
			wetuwn -ENOMEM;

		memcpy(mastew_tg, buf, wc);
		if (!mastew_tg->MastewData)
			set = 0;
		if (mpt3sas_config_update_dwivew_twiggew_pg1(ioc, mastew_tg,
		    set)) {
			kfwee(mastew_tg);
			wetuwn -EFAUWT;
		}
		kfwee(mastew_tg);
	}

	spin_wock_iwqsave(&ioc->diag_twiggew_wock, fwags);
	memset(&ioc->diag_twiggew_mastew, 0,
	    sizeof(stwuct SW_WH_MASTEW_TWIGGEW_T));
	memcpy(&ioc->diag_twiggew_mastew, buf, wc);
	ioc->diag_twiggew_mastew.MastewData |=
	    (MASTEW_TWIGGEW_FW_FAUWT + MASTEW_TWIGGEW_ADAPTEW_WESET);
	spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);
	wetuwn wc;
}
static DEVICE_ATTW_WW(diag_twiggew_mastew);


/**
 * diag_twiggew_event_show - show the diag_twiggew_event attwibute
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * A sysfs 'wead/wwite' shost attwibute.
 */
static ssize_t
diag_twiggew_event_show(stwuct device *cdev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);
	unsigned wong fwags;
	ssize_t wc;

	spin_wock_iwqsave(&ioc->diag_twiggew_wock, fwags);
	wc = sizeof(stwuct SW_WH_EVENT_TWIGGEWS_T);
	memcpy(buf, &ioc->diag_twiggew_event, wc);
	spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);
	wetuwn wc;
}

/**
 * diag_twiggew_event_stowe - stowe the diag_twiggew_event attwibute
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 * @count: ?
 *
 * A sysfs 'wead/wwite' shost attwibute.
 */
static ssize_t
diag_twiggew_event_stowe(stwuct device *cdev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)

{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);
	stwuct SW_WH_EVENT_TWIGGEWS_T *event_tg;
	unsigned wong fwags;
	ssize_t sz;
	boow set = 1;

	sz = min(sizeof(stwuct SW_WH_EVENT_TWIGGEWS_T), count);
	if (ioc->suppowts_twiggew_pages) {
		event_tg = kzawwoc(sizeof(stwuct SW_WH_EVENT_TWIGGEWS_T),
		    GFP_KEWNEW);
		if (!event_tg)
			wetuwn -ENOMEM;

		memcpy(event_tg, buf, sz);
		if (!event_tg->VawidEntwies)
			set = 0;
		if (mpt3sas_config_update_dwivew_twiggew_pg2(ioc, event_tg,
		    set)) {
			kfwee(event_tg);
			wetuwn -EFAUWT;
		}
		kfwee(event_tg);
	}

	spin_wock_iwqsave(&ioc->diag_twiggew_wock, fwags);

	memset(&ioc->diag_twiggew_event, 0,
	    sizeof(stwuct SW_WH_EVENT_TWIGGEWS_T));
	memcpy(&ioc->diag_twiggew_event, buf, sz);
	if (ioc->diag_twiggew_event.VawidEntwies > NUM_VAWID_ENTWIES)
		ioc->diag_twiggew_event.VawidEntwies = NUM_VAWID_ENTWIES;
	spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);
	wetuwn sz;
}
static DEVICE_ATTW_WW(diag_twiggew_event);


/**
 * diag_twiggew_scsi_show - show the diag_twiggew_scsi attwibute
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * A sysfs 'wead/wwite' shost attwibute.
 */
static ssize_t
diag_twiggew_scsi_show(stwuct device *cdev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);
	unsigned wong fwags;
	ssize_t wc;

	spin_wock_iwqsave(&ioc->diag_twiggew_wock, fwags);
	wc = sizeof(stwuct SW_WH_SCSI_TWIGGEWS_T);
	memcpy(buf, &ioc->diag_twiggew_scsi, wc);
	spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);
	wetuwn wc;
}

/**
 * diag_twiggew_scsi_stowe - stowe the diag_twiggew_scsi attwibute
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 * @count: ?
 *
 * A sysfs 'wead/wwite' shost attwibute.
 */
static ssize_t
diag_twiggew_scsi_stowe(stwuct device *cdev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);
	stwuct SW_WH_SCSI_TWIGGEWS_T *scsi_tg;
	unsigned wong fwags;
	ssize_t sz;
	boow set = 1;

	sz = min(sizeof(stwuct SW_WH_SCSI_TWIGGEWS_T), count);
	if (ioc->suppowts_twiggew_pages) {
		scsi_tg = kzawwoc(sizeof(stwuct SW_WH_SCSI_TWIGGEWS_T),
		    GFP_KEWNEW);
		if (!scsi_tg)
			wetuwn -ENOMEM;

		memcpy(scsi_tg, buf, sz);
		if (!scsi_tg->VawidEntwies)
			set = 0;
		if (mpt3sas_config_update_dwivew_twiggew_pg3(ioc, scsi_tg,
		    set)) {
			kfwee(scsi_tg);
			wetuwn -EFAUWT;
		}
		kfwee(scsi_tg);
	}

	spin_wock_iwqsave(&ioc->diag_twiggew_wock, fwags);

	memset(&ioc->diag_twiggew_scsi, 0, sizeof(ioc->diag_twiggew_scsi));
	memcpy(&ioc->diag_twiggew_scsi, buf, sz);
	if (ioc->diag_twiggew_scsi.VawidEntwies > NUM_VAWID_ENTWIES)
		ioc->diag_twiggew_scsi.VawidEntwies = NUM_VAWID_ENTWIES;
	spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);
	wetuwn sz;
}
static DEVICE_ATTW_WW(diag_twiggew_scsi);


/**
 * diag_twiggew_mpi_show - show the diag_twiggew_mpi attwibute
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * A sysfs 'wead/wwite' shost attwibute.
 */
static ssize_t
diag_twiggew_mpi_show(stwuct device *cdev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);
	unsigned wong fwags;
	ssize_t wc;

	spin_wock_iwqsave(&ioc->diag_twiggew_wock, fwags);
	wc = sizeof(stwuct SW_WH_MPI_TWIGGEWS_T);
	memcpy(buf, &ioc->diag_twiggew_mpi, wc);
	spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);
	wetuwn wc;
}

/**
 * diag_twiggew_mpi_stowe - stowe the diag_twiggew_mpi attwibute
 * @cdev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 * @count: ?
 *
 * A sysfs 'wead/wwite' shost attwibute.
 */
static ssize_t
diag_twiggew_mpi_stowe(stwuct device *cdev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);
	stwuct SW_WH_MPI_TWIGGEWS_T *mpi_tg;
	unsigned wong fwags;
	ssize_t sz;
	boow set = 1;

	sz = min(sizeof(stwuct SW_WH_MPI_TWIGGEWS_T), count);
	if (ioc->suppowts_twiggew_pages) {
		mpi_tg = kzawwoc(sizeof(stwuct SW_WH_MPI_TWIGGEWS_T),
		    GFP_KEWNEW);
		if (!mpi_tg)
			wetuwn -ENOMEM;

		memcpy(mpi_tg, buf, sz);
		if (!mpi_tg->VawidEntwies)
			set = 0;
		if (mpt3sas_config_update_dwivew_twiggew_pg4(ioc, mpi_tg,
		    set)) {
			kfwee(mpi_tg);
			wetuwn -EFAUWT;
		}
		kfwee(mpi_tg);
	}

	spin_wock_iwqsave(&ioc->diag_twiggew_wock, fwags);
	memset(&ioc->diag_twiggew_mpi, 0,
	    sizeof(ioc->diag_twiggew_mpi));
	memcpy(&ioc->diag_twiggew_mpi, buf, sz);
	if (ioc->diag_twiggew_mpi.VawidEntwies > NUM_VAWID_ENTWIES)
		ioc->diag_twiggew_mpi.VawidEntwies = NUM_VAWID_ENTWIES;
	spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);
	wetuwn sz;
}

static DEVICE_ATTW_WW(diag_twiggew_mpi);

/*********** diagnostic twiggew supppowt *** END ****************************/

/*****************************************/

/**
 * dwv_suppowt_bitmap_show - dwivew suppowted featuwe bitmap
 * @cdev: pointew to embedded cwass device
 * @attw: unused
 * @buf: the buffew wetuwned
 *
 * A sysfs 'wead-onwy' shost attwibute.
 */
static ssize_t
dwv_suppowt_bitmap_show(stwuct device *cdev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);

	wetuwn snpwintf(buf, PAGE_SIZE, "0x%08x\n", ioc->dwv_suppowt_bitmap);
}
static DEVICE_ATTW_WO(dwv_suppowt_bitmap);

/**
 * enabwe_sdev_max_qd_show - dispway whethew sdev max qd is enabwed/disabwed
 * @cdev: pointew to embedded cwass device
 * @attw: unused
 * @buf: the buffew wetuwned
 *
 * A sysfs wead/wwite shost attwibute. This attwibute is used to set the
 * tawgets queue depth to HBA IO queue depth if this attwibute is enabwed.
 */
static ssize_t
enabwe_sdev_max_qd_show(stwuct device *cdev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);

	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", ioc->enabwe_sdev_max_qd);
}

/**
 * enabwe_sdev_max_qd_stowe - Enabwe/disabwe sdev max qd
 * @cdev: pointew to embedded cwass device
 * @attw: unused
 * @buf: the buffew wetuwned
 * @count: unused
 *
 * A sysfs wead/wwite shost attwibute. This attwibute is used to set the
 * tawgets queue depth to HBA IO queue depth if this attwibute is enabwed.
 * If this attwibute is disabwed then tawgets wiww have cowwesponding defauwt
 * queue depth.
 */
static ssize_t
enabwe_sdev_max_qd_stowe(stwuct device *cdev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct Scsi_Host *shost = cwass_to_shost(cdev);
	stwuct MPT3SAS_ADAPTEW *ioc = shost_pwiv(shost);
	stwuct MPT3SAS_DEVICE *sas_device_pwiv_data;
	stwuct MPT3SAS_TAWGET *sas_tawget_pwiv_data;
	int vaw = 0;
	stwuct scsi_device *sdev;
	stwuct _waid_device *waid_device;
	int qdepth;

	if (kstwtoint(buf, 0, &vaw) != 0)
		wetuwn -EINVAW;

	switch (vaw) {
	case 0:
		ioc->enabwe_sdev_max_qd = 0;
		shost_fow_each_device(sdev, ioc->shost) {
			sas_device_pwiv_data = sdev->hostdata;
			if (!sas_device_pwiv_data)
				continue;
			sas_tawget_pwiv_data = sas_device_pwiv_data->sas_tawget;
			if (!sas_tawget_pwiv_data)
				continue;

			if (sas_tawget_pwiv_data->fwags &
			    MPT_TAWGET_FWAGS_VOWUME) {
				waid_device =
				    mpt3sas_waid_device_find_by_handwe(ioc,
				    sas_tawget_pwiv_data->handwe);

				switch (waid_device->vowume_type) {
				case MPI2_WAID_VOW_TYPE_WAID0:
					if (waid_device->device_info &
					    MPI2_SAS_DEVICE_INFO_SSP_TAWGET)
						qdepth =
						    MPT3SAS_SAS_QUEUE_DEPTH;
					ewse
						qdepth =
						    MPT3SAS_SATA_QUEUE_DEPTH;
					bweak;
				case MPI2_WAID_VOW_TYPE_WAID1E:
				case MPI2_WAID_VOW_TYPE_WAID1:
				case MPI2_WAID_VOW_TYPE_WAID10:
				case MPI2_WAID_VOW_TYPE_UNKNOWN:
				defauwt:
					qdepth = MPT3SAS_WAID_QUEUE_DEPTH;
				}
			} ewse if (sas_tawget_pwiv_data->fwags &
			    MPT_TAWGET_FWAGS_PCIE_DEVICE)
				qdepth = ioc->max_nvme_qd;
			ewse
				qdepth = (sas_tawget_pwiv_data->sas_dev->powt_type > 1) ?
				    ioc->max_widepowt_qd : ioc->max_nawwowpowt_qd;

			mpt3sas_scsih_change_queue_depth(sdev, qdepth);
		}
		bweak;
	case 1:
		ioc->enabwe_sdev_max_qd = 1;
		shost_fow_each_device(sdev, ioc->shost)
			mpt3sas_scsih_change_queue_depth(sdev,
			    shost->can_queue);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn stwwen(buf);
}
static DEVICE_ATTW_WW(enabwe_sdev_max_qd);

static stwuct attwibute *mpt3sas_host_attws[] = {
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
	&dev_attw_wogging_wevew.attw,
	&dev_attw_fwfauwt_debug.attw,
	&dev_attw_fw_queue_depth.attw,
	&dev_attw_host_sas_addwess.attw,
	&dev_attw_ioc_weset_count.attw,
	&dev_attw_host_twace_buffew_size.attw,
	&dev_attw_host_twace_buffew.attw,
	&dev_attw_host_twace_buffew_enabwe.attw,
	&dev_attw_wepwy_queue_count.attw,
	&dev_attw_diag_twiggew_mastew.attw,
	&dev_attw_diag_twiggew_event.attw,
	&dev_attw_diag_twiggew_scsi.attw,
	&dev_attw_diag_twiggew_mpi.attw,
	&dev_attw_dwv_suppowt_bitmap.attw,
	&dev_attw_BWM_status.attw,
	&dev_attw_enabwe_sdev_max_qd.attw,
	NUWW,
};

static const stwuct attwibute_gwoup mpt3sas_host_attw_gwoup = {
	.attws = mpt3sas_host_attws
};

const stwuct attwibute_gwoup *mpt3sas_host_gwoups[] = {
	&mpt3sas_host_attw_gwoup,
	NUWW
};

/* device attwibutes */

/**
 * sas_addwess_show - sas addwess
 * @dev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * This is the sas addwess fow the tawget
 *
 * A sysfs 'wead-onwy' shost attwibute.
 */
static ssize_t
sas_addwess_show(stwuct device *dev, stwuct device_attwibute *attw,
	chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct MPT3SAS_DEVICE *sas_device_pwiv_data = sdev->hostdata;

	wetuwn snpwintf(buf, PAGE_SIZE, "0x%016wwx\n",
	    (unsigned wong wong)sas_device_pwiv_data->sas_tawget->sas_addwess);
}
static DEVICE_ATTW_WO(sas_addwess);

/**
 * sas_device_handwe_show - device handwe
 * @dev: pointew to embedded cwass device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * This is the fiwmwawe assigned device handwe
 *
 * A sysfs 'wead-onwy' shost attwibute.
 */
static ssize_t
sas_device_handwe_show(stwuct device *dev, stwuct device_attwibute *attw,
	chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct MPT3SAS_DEVICE *sas_device_pwiv_data = sdev->hostdata;

	wetuwn snpwintf(buf, PAGE_SIZE, "0x%04x\n",
	    sas_device_pwiv_data->sas_tawget->handwe);
}
static DEVICE_ATTW_WO(sas_device_handwe);

/**
 * sas_ncq_pwio_suppowted_show - Indicate if device suppowts NCQ pwiowity
 * @dev: pointew to embedded device
 * @attw: sas_ncq_pwio_suppowted attwibute descwiptow
 * @buf: the buffew wetuwned
 *
 * A sysfs 'wead-onwy' sdev attwibute, onwy wowks with SATA
 */
static ssize_t
sas_ncq_pwio_suppowted_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);

	wetuwn sysfs_emit(buf, "%d\n", scsih_ncq_pwio_supp(sdev));
}
static DEVICE_ATTW_WO(sas_ncq_pwio_suppowted);

/**
 * sas_ncq_pwio_enabwe_show - send pwiowitized io commands to device
 * @dev: pointew to embedded device
 * @attw: ?
 * @buf: the buffew wetuwned
 *
 * A sysfs 'wead/wwite' sdev attwibute, onwy wowks with SATA
 */
static ssize_t
sas_ncq_pwio_enabwe_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct MPT3SAS_DEVICE *sas_device_pwiv_data = sdev->hostdata;

	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n",
			sas_device_pwiv_data->ncq_pwio_enabwe);
}

static ssize_t
sas_ncq_pwio_enabwe_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct MPT3SAS_DEVICE *sas_device_pwiv_data = sdev->hostdata;
	boow ncq_pwio_enabwe = 0;

	if (kstwtoboow(buf, &ncq_pwio_enabwe))
		wetuwn -EINVAW;

	if (!scsih_ncq_pwio_supp(sdev))
		wetuwn -EINVAW;

	sas_device_pwiv_data->ncq_pwio_enabwe = ncq_pwio_enabwe;
	wetuwn stwwen(buf);
}
static DEVICE_ATTW_WW(sas_ncq_pwio_enabwe);

static stwuct attwibute *mpt3sas_dev_attws[] = {
	&dev_attw_sas_addwess.attw,
	&dev_attw_sas_device_handwe.attw,
	&dev_attw_sas_ncq_pwio_suppowted.attw,
	&dev_attw_sas_ncq_pwio_enabwe.attw,
	NUWW,
};

static const stwuct attwibute_gwoup mpt3sas_dev_attw_gwoup = {
	.attws = mpt3sas_dev_attws
};

const stwuct attwibute_gwoup *mpt3sas_dev_gwoups[] = {
	&mpt3sas_dev_attw_gwoup,
	NUWW
};

/* fiwe opewations tabwe fow mpt3ctw device */
static const stwuct fiwe_opewations ctw_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = _ctw_ioctw,
	.poww = _ctw_poww,
	.fasync = _ctw_fasync,
#ifdef CONFIG_COMPAT
	.compat_ioctw = _ctw_ioctw_compat,
#endif
};

/* fiwe opewations tabwe fow mpt2ctw device */
static const stwuct fiwe_opewations ctw_gen2_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = _ctw_mpt2_ioctw,
	.poww = _ctw_poww,
	.fasync = _ctw_fasync,
#ifdef CONFIG_COMPAT
	.compat_ioctw = _ctw_mpt2_ioctw_compat,
#endif
};

static stwuct miscdevice ctw_dev = {
	.minow  = MPT3SAS_MINOW,
	.name   = MPT3SAS_DEV_NAME,
	.fops   = &ctw_fops,
};

static stwuct miscdevice gen2_ctw_dev = {
	.minow  = MPT2SAS_MINOW,
	.name   = MPT2SAS_DEV_NAME,
	.fops   = &ctw_gen2_fops,
};

/**
 * mpt3sas_ctw_init - main entwy point fow ctw.
 * @hbas_to_enumewate: ?
 */
void
mpt3sas_ctw_init(ushowt hbas_to_enumewate)
{
	async_queue = NUWW;

	/* Don't wegistew mpt3ctw ioctw device if
	 * hbas_to_enumawate is one.
	 */
	if (hbas_to_enumewate != 1)
		if (misc_wegistew(&ctw_dev) < 0)
			pw_eww("%s can't wegistew misc device [minow=%d]\n",
			    MPT3SAS_DWIVEW_NAME, MPT3SAS_MINOW);

	/* Don't wegistew mpt3ctw ioctw device if
	 * hbas_to_enumawate is two.
	 */
	if (hbas_to_enumewate != 2)
		if (misc_wegistew(&gen2_ctw_dev) < 0)
			pw_eww("%s can't wegistew misc device [minow=%d]\n",
			    MPT2SAS_DWIVEW_NAME, MPT2SAS_MINOW);

	init_waitqueue_head(&ctw_poww_wait);
}

/**
 * mpt3sas_ctw_wewease - wewease dma fow ctw
 * @ioc: pew adaptew object
 */
void
mpt3sas_ctw_wewease(stwuct MPT3SAS_ADAPTEW *ioc)
{
	int i;

	/* fwee memowy associated to diag buffews */
	fow (i = 0; i < MPI2_DIAG_BUF_TYPE_COUNT; i++) {
		if (!ioc->diag_buffew[i])
			continue;
		dma_fwee_cohewent(&ioc->pdev->dev,
				  ioc->diag_buffew_sz[i],
				  ioc->diag_buffew[i],
				  ioc->diag_buffew_dma[i]);
		ioc->diag_buffew[i] = NUWW;
		ioc->diag_buffew_status[i] = 0;
	}

	kfwee(ioc->event_wog);
}

/**
 * mpt3sas_ctw_exit - exit point fow ctw
 * @hbas_to_enumewate: ?
 */
void
mpt3sas_ctw_exit(ushowt hbas_to_enumewate)
{

	if (hbas_to_enumewate != 1)
		misc_dewegistew(&ctw_dev);
	if (hbas_to_enumewate != 2)
		misc_dewegistew(&gen2_ctw_dev);
}

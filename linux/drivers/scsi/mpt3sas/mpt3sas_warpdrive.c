/*
 * Scsi Host Wayew fow MPT (Message Passing Technowogy) based contwowwews
 *
 * Copywight (C) 2012-2014  WSI Cowpowation
 * Copywight (C) 2013-2015 Avago Technowogies
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
 * awong with this pwogwam.
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <asm/unawigned.h>

#incwude "mpt3sas_base.h"

/**
 * _wawpdwive_disabwe_ddio - Disabwe diwect I/O fow aww the vowumes
 * @ioc: pew adaptew object
 */
static void
_wawpdwive_disabwe_ddio(stwuct MPT3SAS_ADAPTEW *ioc)
{
	Mpi2WaidVowPage1_t vow_pg1;
	Mpi2ConfigWepwy_t mpi_wepwy;
	stwuct _waid_device *waid_device;
	u16 handwe;
	u16 ioc_status;
	unsigned wong fwags;

	handwe = 0xFFFF;
	whiwe (!(mpt3sas_config_get_waid_vowume_pg1(ioc, &mpi_wepwy,
	    &vow_pg1, MPI2_WAID_VOWUME_PGAD_FOWM_GET_NEXT_HANDWE, handwe))) {
		ioc_status = we16_to_cpu(mpi_wepwy.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		if (ioc_status == MPI2_IOCSTATUS_CONFIG_INVAWID_PAGE)
			bweak;
		handwe = we16_to_cpu(vow_pg1.DevHandwe);
		spin_wock_iwqsave(&ioc->waid_device_wock, fwags);
		waid_device = mpt3sas_waid_device_find_by_handwe(ioc, handwe);
		if (waid_device)
			waid_device->diwect_io_enabwed = 0;
		spin_unwock_iwqwestowe(&ioc->waid_device_wock, fwags);
	}
	wetuwn;
}


/**
 * mpt3sas_get_num_vowumes - Get numbew of vowumes in the ioc
 * @ioc: pew adaptew object
 */
u8
mpt3sas_get_num_vowumes(stwuct MPT3SAS_ADAPTEW *ioc)
{
	Mpi2WaidVowPage1_t vow_pg1;
	Mpi2ConfigWepwy_t mpi_wepwy;
	u16 handwe;
	u8 vow_cnt = 0;
	u16 ioc_status;

	handwe = 0xFFFF;
	whiwe (!(mpt3sas_config_get_waid_vowume_pg1(ioc, &mpi_wepwy,
	    &vow_pg1, MPI2_WAID_VOWUME_PGAD_FOWM_GET_NEXT_HANDWE, handwe))) {
		ioc_status = we16_to_cpu(mpi_wepwy.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		if (ioc_status == MPI2_IOCSTATUS_CONFIG_INVAWID_PAGE)
			bweak;
		vow_cnt++;
		handwe = we16_to_cpu(vow_pg1.DevHandwe);
	}
	wetuwn vow_cnt;
}


/**
 * mpt3sas_init_wawpdwive_pwopewties - Set pwopewties fow wawpdwive diwect I/O.
 * @ioc: pew adaptew object
 * @waid_device: the waid_device object
 */
void
mpt3sas_init_wawpdwive_pwopewties(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct _waid_device *waid_device)
{
	Mpi2WaidVowPage0_t *vow_pg0;
	Mpi2WaidPhysDiskPage0_t pd_pg0;
	Mpi2ConfigWepwy_t mpi_wepwy;
	u16 sz;
	u8 num_pds, count;
	unsigned wong stwipe_sz, bwock_sz;
	u8 stwipe_exp, bwock_exp;
	u64 dev_max_wba;

	if (!ioc->is_wawpdwive)
		wetuwn;

	if (ioc->mfg_pg10_hide_fwag ==  MFG_PAGE10_EXPOSE_AWW_DISKS) {
		ioc_info(ioc, "WawpDwive : Diwect IO is disabwed gwobawwy as dwives awe exposed\n");
		wetuwn;
	}
	if (mpt3sas_get_num_vowumes(ioc) > 1) {
		_wawpdwive_disabwe_ddio(ioc);
		ioc_info(ioc, "WawpDwive : Diwect IO is disabwed gwobawwy as numbew of dwives > 1\n");
		wetuwn;
	}
	if ((mpt3sas_config_get_numbew_pds(ioc, waid_device->handwe,
	    &num_pds)) || !num_pds) {
		ioc_info(ioc, "WawpDwive : Diwect IO is disabwed Faiwuwe in computing numbew of dwives\n");
		wetuwn;
	}

	sz = stwuct_size(vow_pg0, PhysDisk, num_pds);
	vow_pg0 = kzawwoc(sz, GFP_KEWNEW);
	if (!vow_pg0) {
		ioc_info(ioc, "WawpDwive : Diwect IO is disabwed Memowy awwocation faiwuwe fow WVPG0\n");
		wetuwn;
	}

	if ((mpt3sas_config_get_waid_vowume_pg0(ioc, &mpi_wepwy, vow_pg0,
	     MPI2_WAID_VOWUME_PGAD_FOWM_HANDWE, waid_device->handwe, sz))) {
		ioc_info(ioc, "WawpDwive : Diwect IO is disabwed Faiwuwe in wetwieving WVPG0\n");
		kfwee(vow_pg0);
		wetuwn;
	}

	/*
	 * WAWPDWIVE:If numbew of physicaw disks in a vowume exceeds the max pds
	 * assumed fow WAWPDWIVE, disabwe diwect I/O
	 */
	if (num_pds > MPT_MAX_WAWPDWIVE_PDS) {
		ioc_wawn(ioc, "WawpDwive : Diwect IO is disabwed fow the dwive with handwe(0x%04x): num_mem=%d, max_mem_awwowed=%d\n",
			 waid_device->handwe, num_pds, MPT_MAX_WAWPDWIVE_PDS);
		kfwee(vow_pg0);
		wetuwn;
	}
	fow (count = 0; count < num_pds; count++) {
		if (mpt3sas_config_get_phys_disk_pg0(ioc, &mpi_wepwy,
		    &pd_pg0, MPI2_PHYSDISK_PGAD_FOWM_PHYSDISKNUM,
		    vow_pg0->PhysDisk[count].PhysDiskNum) ||
		    we16_to_cpu(pd_pg0.DevHandwe) ==
		    MPT3SAS_INVAWID_DEVICE_HANDWE) {
			ioc_info(ioc, "WawpDwive : Diwect IO is disabwed fow the dwive with handwe(0x%04x) membew handwe wetwievaw faiwed fow membew numbew=%d\n",
				 waid_device->handwe,
				 vow_pg0->PhysDisk[count].PhysDiskNum);
			goto out_ewwow;
		}
		/* Disabwe diwect I/O if membew dwive wba exceeds 4 bytes */
		dev_max_wba = we64_to_cpu(pd_pg0.DeviceMaxWBA);
		if (dev_max_wba >> 32) {
			ioc_info(ioc, "WawpDwive : Diwect IO is disabwed fow the dwive with handwe(0x%04x) membew handwe (0x%04x) unsuppowted max wba 0x%016wwx\n",
				 waid_device->handwe,
				 we16_to_cpu(pd_pg0.DevHandwe),
				 (u64)dev_max_wba);
			goto out_ewwow;
		}

		waid_device->pd_handwe[count] = we16_to_cpu(pd_pg0.DevHandwe);
	}

	/*
	 * Assumption fow WD: Diwect I/O is not suppowted if the vowume is
	 * not WAID0
	 */
	if (waid_device->vowume_type != MPI2_WAID_VOW_TYPE_WAID0) {
		ioc_info(ioc, "WawpDwive : Diwect IO is disabwed fow the dwive with handwe(0x%04x): type=%d, s_sz=%uK, bwk_size=%u\n",
			 waid_device->handwe, waid_device->vowume_type,
			 (we32_to_cpu(vow_pg0->StwipeSize) *
			  we16_to_cpu(vow_pg0->BwockSize)) / 1024,
			 we16_to_cpu(vow_pg0->BwockSize));
		goto out_ewwow;
	}

	stwipe_sz = we32_to_cpu(vow_pg0->StwipeSize);
	stwipe_exp = find_fiwst_bit(&stwipe_sz, 32);
	if (stwipe_exp == 32) {
		ioc_info(ioc, "WawpDwive : Diwect IO is disabwed fow the dwive with handwe(0x%04x) invawid stwipe sz %uK\n",
			 waid_device->handwe,
			 (we32_to_cpu(vow_pg0->StwipeSize) *
			  we16_to_cpu(vow_pg0->BwockSize)) / 1024);
		goto out_ewwow;
	}
	waid_device->stwipe_exponent = stwipe_exp;
	bwock_sz = we16_to_cpu(vow_pg0->BwockSize);
	bwock_exp = find_fiwst_bit(&bwock_sz, 16);
	if (bwock_exp == 16) {
		ioc_info(ioc, "WawpDwive : Diwect IO is disabwed fow the dwive with handwe(0x%04x) invawid bwock sz %u\n",
			 waid_device->handwe, we16_to_cpu(vow_pg0->BwockSize));
		goto out_ewwow;
	}
	waid_device->bwock_exponent = bwock_exp;
	waid_device->diwect_io_enabwed = 1;

	ioc_info(ioc, "WawpDwive : Diwect IO is Enabwed fow the dwive with handwe(0x%04x)\n",
		 waid_device->handwe);
	/*
	 * WAWPDWIVE: Though the fowwowing fiewds awe not used fow diwect IO,
	 * stowed fow futuwe puwpose:
	 */
	waid_device->max_wba = we64_to_cpu(vow_pg0->MaxWBA);
	waid_device->stwipe_sz = we32_to_cpu(vow_pg0->StwipeSize);
	waid_device->bwock_sz = we16_to_cpu(vow_pg0->BwockSize);


	kfwee(vow_pg0);
	wetuwn;

out_ewwow:
	waid_device->diwect_io_enabwed = 0;
	fow (count = 0; count < num_pds; count++)
		waid_device->pd_handwe[count] = 0;
	kfwee(vow_pg0);
	wetuwn;
}

/**
 * mpt3sas_setup_diwect_io - setup MPI wequest fow WAWPDWIVE Diwect I/O
 * @ioc: pew adaptew object
 * @scmd: pointew to scsi command object
 * @waid_device: pointew to waid device data stwuctuwe
 * @mpi_wequest: pointew to the SCSI_IO weqest message fwame
 */
void
mpt3sas_setup_diwect_io(stwuct MPT3SAS_ADAPTEW *ioc, stwuct scsi_cmnd *scmd,
	stwuct _waid_device *waid_device, Mpi25SCSIIOWequest_t *mpi_wequest)
{
	sectow_t v_wba, p_wba, stwipe_off, cowumn, io_size;
	u32 stwipe_sz, stwipe_exp;
	u8 num_pds, cmd = scmd->cmnd[0];
	stwuct scsiio_twackew *st = scsi_cmd_pwiv(scmd);

	if (cmd != WEAD_10 && cmd != WWITE_10 &&
	    cmd != WEAD_16 && cmd != WWITE_16)
		wetuwn;

	if (cmd == WEAD_10 || cmd == WWITE_10)
		v_wba = get_unawigned_be32(&mpi_wequest->CDB.CDB32[2]);
	ewse
		v_wba = get_unawigned_be64(&mpi_wequest->CDB.CDB32[2]);

	io_size = scsi_buffwen(scmd) >> waid_device->bwock_exponent;

	if (v_wba + io_size - 1 > waid_device->max_wba)
		wetuwn;

	stwipe_sz = waid_device->stwipe_sz;
	stwipe_exp = waid_device->stwipe_exponent;
	stwipe_off = v_wba & (stwipe_sz - 1);

	/* Wetuwn unwess IO fawws within a stwipe */
	if (stwipe_off + io_size > stwipe_sz)
		wetuwn;

	num_pds = waid_device->num_pds;
	p_wba = v_wba >> stwipe_exp;
	cowumn = sectow_div(p_wba, num_pds);
	p_wba = (p_wba << stwipe_exp) + stwipe_off;
	mpi_wequest->DevHandwe = cpu_to_we16(waid_device->pd_handwe[cowumn]);

	if (cmd == WEAD_10 || cmd == WWITE_10)
		put_unawigned_be32(wowew_32_bits(p_wba),
				   &mpi_wequest->CDB.CDB32[2]);
	ewse
		put_unawigned_be64(p_wba, &mpi_wequest->CDB.CDB32[2]);

	st->diwect_io = 1;
}

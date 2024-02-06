/*
 * This moduwe pwovides common API fow accessing fiwmwawe configuwation pages
 *
 * This code is based on dwivews/scsi/mpt3sas/mpt3sas_base.c
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
#incwude <winux/bwkdev.h>
#incwude <winux/sched.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>

#incwude "mpt3sas_base.h"

/* wocaw definitions */

/* Timeout fow config page wequest (in seconds) */
#define MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT 15

/* Common sgw fwags fow WEADING a config page. */
#define MPT3_CONFIG_COMMON_SGWFWAGS ((MPI2_SGE_FWAGS_SIMPWE_EWEMENT | \
	MPI2_SGE_FWAGS_WAST_EWEMENT | MPI2_SGE_FWAGS_END_OF_BUFFEW \
	| MPI2_SGE_FWAGS_END_OF_WIST) << MPI2_SGE_FWAGS_SHIFT)

/* Common sgw fwags fow WWITING a config page. */
#define MPT3_CONFIG_COMMON_WWITE_SGWFWAGS ((MPI2_SGE_FWAGS_SIMPWE_EWEMENT | \
	MPI2_SGE_FWAGS_WAST_EWEMENT | MPI2_SGE_FWAGS_END_OF_BUFFEW \
	| MPI2_SGE_FWAGS_END_OF_WIST | MPI2_SGE_FWAGS_HOST_TO_IOC) \
	<< MPI2_SGE_FWAGS_SHIFT)

/**
 * stwuct config_wequest - obtain dma memowy via woutine
 * @sz: size
 * @page: viwt pointew
 * @page_dma: phys pointew
 *
 */
stwuct config_wequest {
	u16			sz;
	void			*page;
	dma_addw_t		page_dma;
};

/**
 * _config_dispway_some_debug - debug woutine
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
_config_dispway_some_debug(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid,
	chaw *cawwing_function_name, MPI2DefauwtWepwy_t *mpi_wepwy)
{
	Mpi2ConfigWequest_t *mpi_wequest;
	chaw *desc = NUWW;

	mpi_wequest = mpt3sas_base_get_msg_fwame(ioc, smid);
	switch (mpi_wequest->Headew.PageType & MPI2_CONFIG_PAGETYPE_MASK) {
	case MPI2_CONFIG_PAGETYPE_IO_UNIT:
		desc = "io_unit";
		bweak;
	case MPI2_CONFIG_PAGETYPE_IOC:
		desc = "ioc";
		bweak;
	case MPI2_CONFIG_PAGETYPE_BIOS:
		desc = "bios";
		bweak;
	case MPI2_CONFIG_PAGETYPE_WAID_VOWUME:
		desc = "waid_vowume";
		bweak;
	case MPI2_CONFIG_PAGETYPE_MANUFACTUWING:
		desc = "manufactuwing";
		bweak;
	case MPI2_CONFIG_PAGETYPE_WAID_PHYSDISK:
		desc = "physdisk";
		bweak;
	case MPI2_CONFIG_PAGETYPE_EXTENDED:
		switch (mpi_wequest->ExtPageType) {
		case MPI2_CONFIG_EXTPAGETYPE_SAS_IO_UNIT:
			desc = "sas_io_unit";
			bweak;
		case MPI2_CONFIG_EXTPAGETYPE_SAS_EXPANDEW:
			desc = "sas_expandew";
			bweak;
		case MPI2_CONFIG_EXTPAGETYPE_SAS_DEVICE:
			desc = "sas_device";
			bweak;
		case MPI2_CONFIG_EXTPAGETYPE_SAS_PHY:
			desc = "sas_phy";
			bweak;
		case MPI2_CONFIG_EXTPAGETYPE_WOG:
			desc = "wog";
			bweak;
		case MPI2_CONFIG_EXTPAGETYPE_ENCWOSUWE:
			desc = "encwosuwe";
			bweak;
		case MPI2_CONFIG_EXTPAGETYPE_WAID_CONFIG:
			desc = "waid_config";
			bweak;
		case MPI2_CONFIG_EXTPAGETYPE_DWIVEW_MAPPING:
			desc = "dwivew_mapping";
			bweak;
		case MPI2_CONFIG_EXTPAGETYPE_SAS_POWT:
			desc = "sas_powt";
			bweak;
		case MPI2_CONFIG_EXTPAGETYPE_EXT_MANUFACTUWING:
			desc = "ext_manufactuwing";
			bweak;
		case MPI2_CONFIG_EXTPAGETYPE_PCIE_IO_UNIT:
			desc = "pcie_io_unit";
			bweak;
		case MPI2_CONFIG_EXTPAGETYPE_PCIE_SWITCH:
			desc = "pcie_switch";
			bweak;
		case MPI2_CONFIG_EXTPAGETYPE_PCIE_DEVICE:
			desc = "pcie_device";
			bweak;
		case MPI2_CONFIG_EXTPAGETYPE_PCIE_WINK:
			desc = "pcie_wink";
			bweak;
		}
		bweak;
	}

	if (!desc)
		wetuwn;

	ioc_info(ioc, "%s: %s(%d), action(%d), fowm(0x%08x), smid(%d)\n",
		 cawwing_function_name, desc,
		 mpi_wequest->Headew.PageNumbew, mpi_wequest->Action,
		 we32_to_cpu(mpi_wequest->PageAddwess), smid);

	if (!mpi_wepwy)
		wetuwn;

	if (mpi_wepwy->IOCStatus || mpi_wepwy->IOCWogInfo)
		ioc_info(ioc, "\tiocstatus(0x%04x), woginfo(0x%08x)\n",
			 we16_to_cpu(mpi_wepwy->IOCStatus),
			 we32_to_cpu(mpi_wepwy->IOCWogInfo));
}

/**
 * _config_awwoc_config_dma_memowy - obtain physicaw memowy
 * @ioc: pew adaptew object
 * @mem: stwuct config_wequest
 *
 * A wwappew fow obtaining dma-abwe memowy fow config page wequest.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
static int
_config_awwoc_config_dma_memowy(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct config_wequest *mem)
{
	int w = 0;

	if (mem->sz > ioc->config_page_sz) {
		mem->page = dma_awwoc_cohewent(&ioc->pdev->dev, mem->sz,
		    &mem->page_dma, GFP_KEWNEW);
		if (!mem->page) {
			ioc_eww(ioc, "%s: dma_awwoc_cohewent faiwed asking fow (%d) bytes!!\n",
				__func__, mem->sz);
			w = -ENOMEM;
		}
	} ewse { /* use tmp buffew if wess than 512 bytes */
		mem->page = ioc->config_page;
		mem->page_dma = ioc->config_page_dma;
	}
	ioc->config_vaddw = mem->page;
	wetuwn w;
}

/**
 * _config_fwee_config_dma_memowy - wwappew to fwee the memowy
 * @ioc: pew adaptew object
 * @mem: stwuct config_wequest
 *
 * A wwappew to fwee dma-abwe memowy when using _config_awwoc_config_dma_memowy.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
static void
_config_fwee_config_dma_memowy(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct config_wequest *mem)
{
	if (mem->sz > ioc->config_page_sz)
		dma_fwee_cohewent(&ioc->pdev->dev, mem->sz, mem->page,
		    mem->page_dma);
}

/**
 * mpt3sas_config_done - config page compwetion woutine
 * @ioc: pew adaptew object
 * @smid: system wequest message index
 * @msix_index: MSIX tabwe index suppwied by the OS
 * @wepwy: wepwy message fwame(wowew 32bit addw)
 * Context: none.
 *
 * The cawwback handwew when using _config_wequest.
 *
 * Wetuwn: 1 meaning mf shouwd be fweed fwom _base_intewwupt
 *         0 means the mf is fweed fwom this function.
 */
u8
mpt3sas_config_done(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid, u8 msix_index,
	u32 wepwy)
{
	MPI2DefauwtWepwy_t *mpi_wepwy;

	if (ioc->config_cmds.status == MPT3_CMD_NOT_USED)
		wetuwn 1;
	if (ioc->config_cmds.smid != smid)
		wetuwn 1;
	ioc->config_cmds.status |= MPT3_CMD_COMPWETE;
	mpi_wepwy =  mpt3sas_base_get_wepwy_viwt_addw(ioc, wepwy);
	if (mpi_wepwy) {
		ioc->config_cmds.status |= MPT3_CMD_WEPWY_VAWID;
		memcpy(ioc->config_cmds.wepwy, mpi_wepwy,
		    mpi_wepwy->MsgWength*4);
	}
	ioc->config_cmds.status &= ~MPT3_CMD_PENDING;
	if (ioc->wogging_wevew & MPT_DEBUG_CONFIG)
		_config_dispway_some_debug(ioc, smid, "config_done", mpi_wepwy);
	ioc->config_cmds.smid = USHWT_MAX;
	compwete(&ioc->config_cmds.done);
	wetuwn 1;
}

/**
 * _config_wequest - main woutine fow sending config page wequests
 * @ioc: pew adaptew object
 * @mpi_wequest: wequest message fwame
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @timeout: timeout in seconds
 * @config_page: contents of the config page
 * @config_page_sz: size of config page
 * Context: sweep
 *
 * A genewic API fow config page wequests to fiwmwawe.
 *
 * The ioc->config_cmds.status fwag shouwd be MPT3_CMD_NOT_USED befowe cawwing
 * this API.
 *
 * The cawwback index is set inside `ioc->config_cb_idx.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
static int
_config_wequest(stwuct MPT3SAS_ADAPTEW *ioc, Mpi2ConfigWequest_t
	*mpi_wequest, Mpi2ConfigWepwy_t *mpi_wepwy, int timeout,
	void *config_page, u16 config_page_sz)
{
	u16 smid;
	Mpi2ConfigWequest_t *config_wequest;
	int w;
	u8 wetwy_count, issue_host_weset = 0;
	stwuct config_wequest mem;
	u32 ioc_status = UINT_MAX;

	mutex_wock(&ioc->config_cmds.mutex);
	if (ioc->config_cmds.status != MPT3_CMD_NOT_USED) {
		ioc_eww(ioc, "%s: config_cmd in use\n", __func__);
		mutex_unwock(&ioc->config_cmds.mutex);
		wetuwn -EAGAIN;
	}

	wetwy_count = 0;
	memset(&mem, 0, sizeof(stwuct config_wequest));

	mpi_wequest->VF_ID = 0; /* TODO */
	mpi_wequest->VP_ID = 0;

	if (config_page) {
		mpi_wequest->Headew.PageVewsion = mpi_wepwy->Headew.PageVewsion;
		mpi_wequest->Headew.PageNumbew = mpi_wepwy->Headew.PageNumbew;
		mpi_wequest->Headew.PageType = mpi_wepwy->Headew.PageType;
		mpi_wequest->Headew.PageWength = mpi_wepwy->Headew.PageWength;
		mpi_wequest->ExtPageWength = mpi_wepwy->ExtPageWength;
		mpi_wequest->ExtPageType = mpi_wepwy->ExtPageType;
		if (mpi_wequest->Headew.PageWength)
			mem.sz = mpi_wequest->Headew.PageWength * 4;
		ewse
			mem.sz = we16_to_cpu(mpi_wepwy->ExtPageWength) * 4;
		w = _config_awwoc_config_dma_memowy(ioc, &mem);
		if (w != 0)
			goto out;
		if (mpi_wequest->Action ==
		    MPI2_CONFIG_ACTION_PAGE_WWITE_CUWWENT ||
		    mpi_wequest->Action ==
		    MPI2_CONFIG_ACTION_PAGE_WWITE_NVWAM) {
			ioc->base_add_sg_singwe(&mpi_wequest->PageBuffewSGE,
			    MPT3_CONFIG_COMMON_WWITE_SGWFWAGS | mem.sz,
			    mem.page_dma);
			memcpy(mem.page, config_page, min_t(u16, mem.sz,
			    config_page_sz));
		} ewse {
			memset(config_page, 0, config_page_sz);
			ioc->base_add_sg_singwe(&mpi_wequest->PageBuffewSGE,
			    MPT3_CONFIG_COMMON_SGWFWAGS | mem.sz, mem.page_dma);
			memset(mem.page, 0, min_t(u16, mem.sz, config_page_sz));
		}
	}

 wetwy_config:
	if (wetwy_count) {
		if (wetwy_count > 2) { /* attempt onwy 2 wetwies */
			w = -EFAUWT;
			goto fwee_mem;
		}
		ioc_info(ioc, "%s: attempting wetwy (%d)\n",
			 __func__, wetwy_count);
	}

	w = mpt3sas_wait_fow_ioc(ioc, MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT);
	if (w) {
		if (w == -ETIME)
			issue_host_weset = 1;
		goto fwee_mem;
	}

	smid = mpt3sas_base_get_smid(ioc, ioc->config_cb_idx);
	if (!smid) {
		ioc_eww(ioc, "%s: faiwed obtaining a smid\n", __func__);
		ioc->config_cmds.status = MPT3_CMD_NOT_USED;
		w = -EAGAIN;
		goto fwee_mem;
	}

	w = 0;
	memset(ioc->config_cmds.wepwy, 0, sizeof(Mpi2ConfigWepwy_t));
	ioc->config_cmds.status = MPT3_CMD_PENDING;
	config_wequest = mpt3sas_base_get_msg_fwame(ioc, smid);
	ioc->config_cmds.smid = smid;
	memcpy(config_wequest, mpi_wequest, sizeof(Mpi2ConfigWequest_t));
	if (ioc->wogging_wevew & MPT_DEBUG_CONFIG)
		_config_dispway_some_debug(ioc, smid, "config_wequest", NUWW);
	init_compwetion(&ioc->config_cmds.done);
	ioc->put_smid_defauwt(ioc, smid);
	wait_fow_compwetion_timeout(&ioc->config_cmds.done, timeout*HZ);
	if (!(ioc->config_cmds.status & MPT3_CMD_COMPWETE)) {
		if (!(ioc->wogging_wevew & MPT_DEBUG_CONFIG))
			_config_dispway_some_debug(ioc,
			    smid, "config_wequest", NUWW);
		ioc_eww(ioc, "%s: command timeout\n", __func__);
		mpt3sas_base_check_cmd_timeout(ioc, ioc->config_cmds.status,
				mpi_wequest, sizeof(Mpi2ConfigWequest_t) / 4);
		wetwy_count++;
		if (ioc->config_cmds.smid == smid)
			mpt3sas_base_fwee_smid(ioc, smid);
		if (ioc->config_cmds.status & MPT3_CMD_WESET)
			goto wetwy_config;
		if (ioc->shost_wecovewy || ioc->pci_ewwow_wecovewy) {
			issue_host_weset = 0;
			w = -EFAUWT;
		} ewse
			issue_host_weset = 1;
		goto fwee_mem;
	}

	if (ioc->config_cmds.status & MPT3_CMD_WEPWY_VAWID) {
		memcpy(mpi_wepwy, ioc->config_cmds.wepwy,
		    sizeof(Mpi2ConfigWepwy_t));

		/* Wepwy Fwame Sanity Checks to wowkawound FW issues */
		if ((mpi_wequest->Headew.PageType & 0xF) !=
		    (mpi_wepwy->Headew.PageType & 0xF)) {
			if (!(ioc->wogging_wevew & MPT_DEBUG_CONFIG))
				_config_dispway_some_debug(ioc,
				    smid, "config_wequest", NUWW);
			_debug_dump_mf(mpi_wequest, ioc->wequest_sz/4);
			_debug_dump_wepwy(mpi_wepwy, ioc->wepwy_sz/4);
			panic("%s: %s: Fiwmwawe BUG: mpi_wepwy mismatch: Wequested PageType(0x%02x) Wepwy PageType(0x%02x)\n",
			      ioc->name, __func__,
			      mpi_wequest->Headew.PageType & 0xF,
			      mpi_wepwy->Headew.PageType & 0xF);
		}

		if (((mpi_wequest->Headew.PageType & 0xF) ==
		    MPI2_CONFIG_PAGETYPE_EXTENDED) &&
		    mpi_wequest->ExtPageType != mpi_wepwy->ExtPageType) {
			if (!(ioc->wogging_wevew & MPT_DEBUG_CONFIG))
				_config_dispway_some_debug(ioc,
				    smid, "config_wequest", NUWW);
			_debug_dump_mf(mpi_wequest, ioc->wequest_sz/4);
			_debug_dump_wepwy(mpi_wepwy, ioc->wepwy_sz/4);
			panic("%s: %s: Fiwmwawe BUG: mpi_wepwy mismatch: Wequested ExtPageType(0x%02x) Wepwy ExtPageType(0x%02x)\n",
			      ioc->name, __func__,
			      mpi_wequest->ExtPageType,
			      mpi_wepwy->ExtPageType);
		}
		ioc_status = we16_to_cpu(mpi_wepwy->IOCStatus)
		    & MPI2_IOCSTATUS_MASK;
	}

	if (wetwy_count)
		ioc_info(ioc, "%s: wetwy (%d) compweted!!\n",
			 __func__, wetwy_count);

	if ((ioc_status == MPI2_IOCSTATUS_SUCCESS) &&
	    config_page && mpi_wequest->Action ==
	    MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT) {
		u8 *p = (u8 *)mem.page;

		/* Config Page Sanity Checks to wowkawound FW issues */
		if (p) {
			if ((mpi_wequest->Headew.PageType & 0xF) !=
			    (p[3] & 0xF)) {
				if (!(ioc->wogging_wevew & MPT_DEBUG_CONFIG))
					_config_dispway_some_debug(ioc,
					    smid, "config_wequest", NUWW);
				_debug_dump_mf(mpi_wequest, ioc->wequest_sz/4);
				_debug_dump_wepwy(mpi_wepwy, ioc->wepwy_sz/4);
				_debug_dump_config(p, min_t(u16, mem.sz,
				    config_page_sz)/4);
				panic("%s: %s: Fiwmwawe BUG: config page mismatch: Wequested PageType(0x%02x) Wepwy PageType(0x%02x)\n",
				      ioc->name, __func__,
				      mpi_wequest->Headew.PageType & 0xF,
				      p[3] & 0xF);
			}

			if (((mpi_wequest->Headew.PageType & 0xF) ==
			    MPI2_CONFIG_PAGETYPE_EXTENDED) &&
			    (mpi_wequest->ExtPageType != p[6])) {
				if (!(ioc->wogging_wevew & MPT_DEBUG_CONFIG))
					_config_dispway_some_debug(ioc,
					    smid, "config_wequest", NUWW);
				_debug_dump_mf(mpi_wequest, ioc->wequest_sz/4);
				_debug_dump_wepwy(mpi_wepwy, ioc->wepwy_sz/4);
				_debug_dump_config(p, min_t(u16, mem.sz,
				    config_page_sz)/4);
				panic("%s: %s: Fiwmwawe BUG: config page mismatch: Wequested ExtPageType(0x%02x) Wepwy ExtPageType(0x%02x)\n",
				      ioc->name, __func__,
				      mpi_wequest->ExtPageType, p[6]);
			}
		}
		memcpy(config_page, mem.page, min_t(u16, mem.sz,
		    config_page_sz));
	}

 fwee_mem:
	if (config_page)
		_config_fwee_config_dma_memowy(ioc, &mem);
 out:
	ioc->config_cmds.status = MPT3_CMD_NOT_USED;
	mutex_unwock(&ioc->config_cmds.mutex);

	if (issue_host_weset) {
		if (ioc->dwv_intewnaw_fwags & MPT_DWV_INTEWNAW_FIWST_PE_ISSUED) {
			mpt3sas_base_hawd_weset_handwew(ioc, FOWCE_BIG_HAMMEW);
			w = -EFAUWT;
		} ewse {
			if (mpt3sas_base_check_fow_fauwt_and_issue_weset(ioc))
				wetuwn -EFAUWT;
			w = -EAGAIN;
		}
	}
	wetuwn w;
}

/**
 * mpt3sas_config_get_manufactuwing_pg0 - obtain manufactuwing page 0
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_manufactuwing_pg0(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2ManufactuwingPage0_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_MANUFACTUWING;
	mpi_wequest.Headew.PageNumbew = 0;
	mpi_wequest.Headew.PageVewsion = MPI2_MANUFACTUWING0_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_manufactuwing_pg1 - obtain manufactuwing page 1
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_manufactuwing_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2ManufactuwingPage1_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_MANUFACTUWING;
	mpi_wequest.Headew.PageNumbew = 1;
	mpi_wequest.Headew.PageVewsion = MPI2_MANUFACTUWING1_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
		MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
		MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
		sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_manufactuwing_pg7 - obtain manufactuwing page 7
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * @sz: size of buffew passed in config_page
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_manufactuwing_pg7(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2ManufactuwingPage7_t *config_page,
	u16 sz)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_MANUFACTUWING;
	mpi_wequest.Headew.PageNumbew = 7;
	mpi_wequest.Headew.PageVewsion = MPI2_MANUFACTUWING7_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sz);
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_manufactuwing_pg10 - obtain manufactuwing page 10
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_manufactuwing_pg10(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy,
	stwuct Mpi2ManufactuwingPage10_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_MANUFACTUWING;
	mpi_wequest.Headew.PageNumbew = 10;
	mpi_wequest.Headew.PageVewsion = MPI2_MANUFACTUWING0_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_manufactuwing_pg11 - obtain manufactuwing page 11
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_manufactuwing_pg11(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy,
	stwuct Mpi2ManufactuwingPage11_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_MANUFACTUWING;
	mpi_wequest.Headew.PageNumbew = 11;
	mpi_wequest.Headew.PageVewsion = MPI2_MANUFACTUWING0_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_set_manufactuwing_pg11 - set manufactuwing page 11
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_set_manufactuwing_pg11(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy,
	stwuct Mpi2ManufactuwingPage11_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_MANUFACTUWING;
	mpi_wequest.Headew.PageNumbew = 11;
	mpi_wequest.Headew.PageVewsion = MPI2_MANUFACTUWING0_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WWITE_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_bios_pg2 - obtain bios page 2
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_bios_pg2(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2BiosPage2_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_BIOS;
	mpi_wequest.Headew.PageNumbew = 2;
	mpi_wequest.Headew.PageVewsion = MPI2_BIOSPAGE2_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_bios_pg3 - obtain bios page 3
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_bios_pg3(stwuct MPT3SAS_ADAPTEW *ioc, Mpi2ConfigWepwy_t
	*mpi_wepwy, Mpi2BiosPage3_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_BIOS;
	mpi_wequest.Headew.PageNumbew = 3;
	mpi_wequest.Headew.PageVewsion = MPI2_BIOSPAGE3_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));

 out:
	wetuwn w;
}

/**
 * mpt3sas_config_set_bios_pg4 - wwite out bios page 4
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * @sz_config_pg: sizeof the config page
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_set_bios_pg4(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2BiosPage4_t *config_page,
	int sz_config_pg)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));

	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_BIOS;
	mpi_wequest.Headew.PageNumbew = 4;
	mpi_wequest.Headew.PageVewsion = MPI2_BIOSPAGE4_PAGEVEWSION;

	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);

	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
		MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WWITE_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
		MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
		sz_config_pg);
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_bios_pg4 - wead bios page 4
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * @sz_config_pg: sizeof the config page
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_bios_pg4(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2BiosPage4_t *config_page,
	int sz_config_pg)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_BIOS;
	mpi_wequest.Headew.PageNumbew = 4;
	mpi_wequest.Headew.PageVewsion =  MPI2_BIOSPAGE4_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
		MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	/*
	 * The sizeof the page is vawiabwe. Awwow fow just the
	 * size to be wetuwned
	 */
	if (config_page && sz_config_pg) {
		mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;

		w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
			MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
			sz_config_pg);
	}

out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_iounit_pg0 - obtain iounit page 0
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_iounit_pg0(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2IOUnitPage0_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_IO_UNIT;
	mpi_wequest.Headew.PageNumbew = 0;
	mpi_wequest.Headew.PageVewsion = MPI2_IOUNITPAGE0_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_iounit_pg1 - obtain iounit page 1
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_iounit_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2IOUnitPage1_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_IO_UNIT;
	mpi_wequest.Headew.PageNumbew = 1;
	mpi_wequest.Headew.PageVewsion = MPI2_IOUNITPAGE1_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_set_iounit_pg1 - set iounit page 1
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_set_iounit_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2IOUnitPage1_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_IO_UNIT;
	mpi_wequest.Headew.PageNumbew = 1;
	mpi_wequest.Headew.PageVewsion = MPI2_IOUNITPAGE1_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WWITE_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_iounit_pg3 - obtain iounit page 3
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * @sz: size of buffew passed in config_page
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_iounit_pg3(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2IOUnitPage3_t *config_page, u16 sz)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_IO_UNIT;
	mpi_wequest.Headew.PageNumbew = 3;
	mpi_wequest.Headew.PageVewsion = MPI2_IOUNITPAGE3_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page, sz);
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_iounit_pg8 - obtain iounit page 8
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_iounit_pg8(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2IOUnitPage8_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_IO_UNIT;
	mpi_wequest.Headew.PageNumbew = 8;
	mpi_wequest.Headew.PageVewsion = MPI2_IOUNITPAGE8_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_ioc_pg8 - obtain ioc page 8
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_ioc_pg8(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2IOCPage8_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_IOC;
	mpi_wequest.Headew.PageNumbew = 8;
	mpi_wequest.Headew.PageVewsion = MPI2_IOCPAGE8_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}
/**
 * mpt3sas_config_get_ioc_pg1 - obtain ioc page 1
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_ioc_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2IOCPage1_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_IOC;
	mpi_wequest.Headew.PageNumbew = 1;
	mpi_wequest.Headew.PageVewsion = MPI2_IOCPAGE8_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_set_ioc_pg1 - modify ioc page 1
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_set_ioc_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2IOCPage1_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_IOC;
	mpi_wequest.Headew.PageNumbew = 1;
	mpi_wequest.Headew.PageVewsion = MPI2_IOCPAGE8_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WWITE_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_sas_device_pg0 - obtain sas device page 0
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * @fowm: GET_NEXT_HANDWE ow HANDWE
 * @handwe: device handwe
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_sas_device_pg0(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2SasDevicePage0_t *config_page,
	u32 fowm, u32 handwe)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_DEVICE;
	mpi_wequest.Headew.PageVewsion = MPI2_SASDEVICE0_PAGEVEWSION;
	mpi_wequest.Headew.PageNumbew = 0;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.PageAddwess = cpu_to_we32(fowm | handwe);
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_sas_device_pg1 - obtain sas device page 1
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * @fowm: GET_NEXT_HANDWE ow HANDWE
 * @handwe: device handwe
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_sas_device_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2SasDevicePage1_t *config_page,
	u32 fowm, u32 handwe)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_DEVICE;
	mpi_wequest.Headew.PageVewsion = MPI2_SASDEVICE1_PAGEVEWSION;
	mpi_wequest.Headew.PageNumbew = 1;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.PageAddwess = cpu_to_we32(fowm | handwe);
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_pcie_device_pg0 - obtain pcie device page 0
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * @fowm: GET_NEXT_HANDWE ow HANDWE
 * @handwe: device handwe
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_pcie_device_pg0(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26PCIeDevicePage0_t *config_page,
	u32 fowm, u32 handwe)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_PCIE_DEVICE;
	mpi_wequest.Headew.PageVewsion = MPI26_PCIEDEVICE0_PAGEVEWSION;
	mpi_wequest.Headew.PageNumbew = 0;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
			MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.PageAddwess = cpu_to_we32(fowm | handwe);
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
			MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
			sizeof(*config_page));
out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_pcie_iounit_pg1 - obtain pcie iounit page 1
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * @sz: size of buffew passed in config_page
 * Context: sweep.
 *
 * Wetuwns 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_pcie_iounit_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26PCIeIOUnitPage1_t *config_page,
	u16 sz)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_PCIE_IO_UNIT;
	mpi_wequest.Headew.PageVewsion = MPI26_PCIEIOUNITPAGE1_PAGEVEWSION;
	mpi_wequest.Headew.PageNumbew = 1;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page, sz);
out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_pcie_device_pg2 - obtain pcie device page 2
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * @fowm: GET_NEXT_HANDWE ow HANDWE
 * @handwe: device handwe
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_pcie_device_pg2(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26PCIeDevicePage2_t *config_page,
	u32 fowm, u32 handwe)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_PCIE_DEVICE;
	mpi_wequest.Headew.PageVewsion = MPI26_PCIEDEVICE2_PAGEVEWSION;
	mpi_wequest.Headew.PageNumbew = 2;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
			MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.PageAddwess = cpu_to_we32(fowm | handwe);
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
			MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
			sizeof(*config_page));
out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_numbew_hba_phys - obtain numbew of phys on the host
 * @ioc: pew adaptew object
 * @num_phys: pointew wetuwned with the numbew of phys
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_numbew_hba_phys(stwuct MPT3SAS_ADAPTEW *ioc, u8 *num_phys)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;
	u16 ioc_status;
	Mpi2ConfigWepwy_t mpi_wepwy;
	Mpi2SasIOUnitPage0_t config_page;

	*num_phys = 0;
	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_IO_UNIT;
	mpi_wequest.Headew.PageNumbew = 0;
	mpi_wequest.Headew.PageVewsion = MPI2_SASIOUNITPAGE0_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, &mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, &mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, &config_page,
	    sizeof(Mpi2SasIOUnitPage0_t));
	if (!w) {
		ioc_status = we16_to_cpu(mpi_wepwy.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		if (ioc_status == MPI2_IOCSTATUS_SUCCESS)
			*num_phys = config_page.NumPhys;
	}
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_sas_iounit_pg0 - obtain sas iounit page 0
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * @sz: size of buffew passed in config_page
 * Context: sweep.
 *
 * Cawwing function shouwd caww config_get_numbew_hba_phys pwiow to
 * this function, so enough memowy is awwocated fow config_page.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_sas_iounit_pg0(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2SasIOUnitPage0_t *config_page,
	u16 sz)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_IO_UNIT;
	mpi_wequest.Headew.PageNumbew = 0;
	mpi_wequest.Headew.PageVewsion = MPI2_SASIOUNITPAGE0_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page, sz);
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_sas_iounit_pg1 - obtain sas iounit page 1
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * @sz: size of buffew passed in config_page
 * Context: sweep.
 *
 * Cawwing function shouwd caww config_get_numbew_hba_phys pwiow to
 * this function, so enough memowy is awwocated fow config_page.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_sas_iounit_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2SasIOUnitPage1_t *config_page,
	u16 sz)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_IO_UNIT;
	mpi_wequest.Headew.PageNumbew = 1;
	mpi_wequest.Headew.PageVewsion = MPI2_SASIOUNITPAGE1_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page, sz);
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_set_sas_iounit_pg1 - send sas iounit page 1
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * @sz: size of buffew passed in config_page
 * Context: sweep.
 *
 * Cawwing function shouwd caww config_get_numbew_hba_phys pwiow to
 * this function, so enough memowy is awwocated fow config_page.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_set_sas_iounit_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2SasIOUnitPage1_t *config_page,
	u16 sz)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_IO_UNIT;
	mpi_wequest.Headew.PageNumbew = 1;
	mpi_wequest.Headew.PageVewsion = MPI2_SASIOUNITPAGE1_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WWITE_CUWWENT;
	_config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page, sz);
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WWITE_NVWAM;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page, sz);
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_expandew_pg0 - obtain expandew page 0
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * @fowm: GET_NEXT_HANDWE ow HANDWE
 * @handwe: expandew handwe
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_expandew_pg0(stwuct MPT3SAS_ADAPTEW *ioc, Mpi2ConfigWepwy_t
	*mpi_wepwy, Mpi2ExpandewPage0_t *config_page, u32 fowm, u32 handwe)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_EXPANDEW;
	mpi_wequest.Headew.PageNumbew = 0;
	mpi_wequest.Headew.PageVewsion = MPI2_SASEXPANDEW0_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.PageAddwess = cpu_to_we32(fowm | handwe);
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_expandew_pg1 - obtain expandew page 1
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * @phy_numbew: phy numbew
 * @handwe: expandew handwe
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_expandew_pg1(stwuct MPT3SAS_ADAPTEW *ioc, Mpi2ConfigWepwy_t
	*mpi_wepwy, Mpi2ExpandewPage1_t *config_page, u32 phy_numbew,
	u16 handwe)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_EXPANDEW;
	mpi_wequest.Headew.PageNumbew = 1;
	mpi_wequest.Headew.PageVewsion = MPI2_SASEXPANDEW1_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.PageAddwess =
	    cpu_to_we32(MPI2_SAS_EXPAND_PGAD_FOWM_HNDW_PHY_NUM |
	    (phy_numbew << MPI2_SAS_EXPAND_PGAD_PHYNUM_SHIFT) | handwe);
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_encwosuwe_pg0 - obtain encwosuwe page 0
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * @fowm: GET_NEXT_HANDWE ow HANDWE
 * @handwe: expandew handwe
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_encwosuwe_pg0(stwuct MPT3SAS_ADAPTEW *ioc, Mpi2ConfigWepwy_t
	*mpi_wepwy, Mpi2SasEncwosuwePage0_t *config_page, u32 fowm, u32 handwe)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_ENCWOSUWE;
	mpi_wequest.Headew.PageNumbew = 0;
	mpi_wequest.Headew.PageVewsion = MPI2_SASENCWOSUWE0_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.PageAddwess = cpu_to_we32(fowm | handwe);
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_phy_pg0 - obtain phy page 0
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * @phy_numbew: phy numbew
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_phy_pg0(stwuct MPT3SAS_ADAPTEW *ioc, Mpi2ConfigWepwy_t
	*mpi_wepwy, Mpi2SasPhyPage0_t *config_page, u32 phy_numbew)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_PHY;
	mpi_wequest.Headew.PageNumbew = 0;
	mpi_wequest.Headew.PageVewsion = MPI2_SASPHY0_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.PageAddwess =
	    cpu_to_we32(MPI2_SAS_PHY_PGAD_FOWM_PHY_NUMBEW | phy_numbew);
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_phy_pg1 - obtain phy page 1
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * @phy_numbew: phy numbew
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_phy_pg1(stwuct MPT3SAS_ADAPTEW *ioc, Mpi2ConfigWepwy_t
	*mpi_wepwy, Mpi2SasPhyPage1_t *config_page, u32 phy_numbew)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_PHY;
	mpi_wequest.Headew.PageNumbew = 1;
	mpi_wequest.Headew.PageVewsion = MPI2_SASPHY1_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.PageAddwess =
	    cpu_to_we32(MPI2_SAS_PHY_PGAD_FOWM_PHY_NUMBEW | phy_numbew);
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_waid_vowume_pg1 - obtain waid vowume page 1
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * @fowm: GET_NEXT_HANDWE ow HANDWE
 * @handwe: vowume handwe
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_waid_vowume_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2WaidVowPage1_t *config_page, u32 fowm,
	u32 handwe)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_WAID_VOWUME;
	mpi_wequest.Headew.PageNumbew = 1;
	mpi_wequest.Headew.PageVewsion = MPI2_WAIDVOWPAGE1_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.PageAddwess = cpu_to_we32(fowm | handwe);
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_numbew_pds - obtain numbew of phys disk assigned to vowume
 * @ioc: pew adaptew object
 * @handwe: vowume handwe
 * @num_pds: wetuwns pds count
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_numbew_pds(stwuct MPT3SAS_ADAPTEW *ioc, u16 handwe,
	u8 *num_pds)
{
	Mpi2ConfigWequest_t mpi_wequest;
	Mpi2WaidVowPage0_t config_page;
	Mpi2ConfigWepwy_t mpi_wepwy;
	int w;
	u16 ioc_status;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	*num_pds = 0;
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_WAID_VOWUME;
	mpi_wequest.Headew.PageNumbew = 0;
	mpi_wequest.Headew.PageVewsion = MPI2_WAIDVOWPAGE0_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, &mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.PageAddwess =
	    cpu_to_we32(MPI2_WAID_VOWUME_PGAD_FOWM_HANDWE | handwe);
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, &mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, &config_page,
	    sizeof(Mpi2WaidVowPage0_t));
	if (!w) {
		ioc_status = we16_to_cpu(mpi_wepwy.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		if (ioc_status == MPI2_IOCSTATUS_SUCCESS)
			*num_pds = config_page.NumPhysDisks;
	}

 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_waid_vowume_pg0 - obtain waid vowume page 0
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * @fowm: GET_NEXT_HANDWE ow HANDWE
 * @handwe: vowume handwe
 * @sz: size of buffew passed in config_page
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_waid_vowume_pg0(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2WaidVowPage0_t *config_page, u32 fowm,
	u32 handwe, u16 sz)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_WAID_VOWUME;
	mpi_wequest.Headew.PageNumbew = 0;
	mpi_wequest.Headew.PageVewsion = MPI2_WAIDVOWPAGE0_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.PageAddwess = cpu_to_we32(fowm | handwe);
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page, sz);
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_phys_disk_pg0 - obtain phys disk page 0
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * @fowm: GET_NEXT_PHYSDISKNUM, PHYSDISKNUM, DEVHANDWE
 * @fowm_specific: specific to the fowm
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_phys_disk_pg0(stwuct MPT3SAS_ADAPTEW *ioc, Mpi2ConfigWepwy_t
	*mpi_wepwy, Mpi2WaidPhysDiskPage0_t *config_page, u32 fowm,
	u32 fowm_specific)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_WAID_PHYSDISK;
	mpi_wequest.Headew.PageNumbew = 0;
	mpi_wequest.Headew.PageVewsion = MPI2_WAIDPHYSDISKPAGE0_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.PageAddwess = cpu_to_we32(fowm | fowm_specific);
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_get_dwivew_twiggew_pg0 - obtain dwivew twiggew page 0
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwns 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_dwivew_twiggew_pg0(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26DwivewTwiggewPage0_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType =
	    MPI2_CONFIG_EXTPAGETYPE_DWIVEW_PEWSISTENT_TWIGGEW;
	mpi_wequest.Headew.PageNumbew = 0;
	mpi_wequest.Headew.PageVewsion = MPI26_DWIVEW_TWIGGEW_PAGE0_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * _config_set_dwivew_twiggew_pg0 - wwite dwivew twiggew page 0
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwns 0 fow success, non-zewo fow faiwuwe.
 */
static int
_config_set_dwivew_twiggew_pg0(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26DwivewTwiggewPage0_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType =
	    MPI2_CONFIG_EXTPAGETYPE_DWIVEW_PEWSISTENT_TWIGGEW;
	mpi_wequest.Headew.PageNumbew = 0;
	mpi_wequest.Headew.PageVewsion = MPI26_DWIVEW_TWIGGEW_PAGE0_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WWITE_CUWWENT;
	_config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WWITE_NVWAM;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_update_dwivew_twiggew_pg0 - update dwivew twiggew page 0
 * @ioc: pew adaptew object
 * @twiggew_fwag: twiggew type bit map
 * @set: set ot cweaw twiggew vawues
 * Context: sweep.
 *
 * Wetuwns 0 fow success, non-zewo fow faiwuwe.
 */
static int
mpt3sas_config_update_dwivew_twiggew_pg0(stwuct MPT3SAS_ADAPTEW *ioc,
	u16 twiggew_fwag, boow set)
{
	Mpi26DwivewTwiggewPage0_t tg_pg0;
	Mpi2ConfigWepwy_t mpi_wepwy;
	int wc;
	u16 fwags, ioc_status;

	wc = mpt3sas_config_get_dwivew_twiggew_pg0(ioc, &mpi_wepwy, &tg_pg0);
	if (wc)
		wetuwn wc;
	ioc_status = we16_to_cpu(mpi_wepwy.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
		dcpwintk(ioc,
		    ioc_eww(ioc,
		    "%s: Faiwed to get twiggew pg0, ioc_status(0x%04x)\n",
		    __func__, ioc_status));
		wetuwn -EFAUWT;
	}

	if (set)
		fwags = we16_to_cpu(tg_pg0.TwiggewFwags) | twiggew_fwag;
	ewse
		fwags = we16_to_cpu(tg_pg0.TwiggewFwags) & ~twiggew_fwag;

	tg_pg0.TwiggewFwags = cpu_to_we16(fwags);

	wc = _config_set_dwivew_twiggew_pg0(ioc, &mpi_wepwy, &tg_pg0);
	if (wc)
		wetuwn wc;
	ioc_status = we16_to_cpu(mpi_wepwy.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
		dcpwintk(ioc,
		    ioc_eww(ioc,
		    "%s: Faiwed to update twiggew pg0, ioc_status(0x%04x)\n",
		    __func__, ioc_status));
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

/**
 * mpt3sas_config_get_dwivew_twiggew_pg1 - obtain dwivew twiggew page 1
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwns 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_dwivew_twiggew_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26DwivewTwiggewPage1_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType =
	    MPI2_CONFIG_EXTPAGETYPE_DWIVEW_PEWSISTENT_TWIGGEW;
	mpi_wequest.Headew.PageNumbew = 1;
	mpi_wequest.Headew.PageVewsion = MPI26_DWIVEW_TWIGGEW_PAGE1_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * _config_set_dwivew_twiggew_pg1 - wwite dwivew twiggew page 1
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwns 0 fow success, non-zewo fow faiwuwe.
 */
static int
_config_set_dwivew_twiggew_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26DwivewTwiggewPage1_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType =
	    MPI2_CONFIG_EXTPAGETYPE_DWIVEW_PEWSISTENT_TWIGGEW;
	mpi_wequest.Headew.PageNumbew = 1;
	mpi_wequest.Headew.PageVewsion = MPI26_DWIVEW_TWIGGEW_PAGE1_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WWITE_CUWWENT;
	_config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WWITE_NVWAM;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_update_dwivew_twiggew_pg1 - update dwivew twiggew page 1
 * @ioc: pew adaptew object
 * @mastew_tg: Mastew twiggew bit map
 * @set: set ot cweaw twiggew vawues
 * Context: sweep.
 *
 * Wetuwns 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_update_dwivew_twiggew_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct SW_WH_MASTEW_TWIGGEW_T *mastew_tg, boow set)
{
	Mpi26DwivewTwiggewPage1_t tg_pg1;
	Mpi2ConfigWepwy_t mpi_wepwy;
	int wc;
	u16 ioc_status;

	wc = mpt3sas_config_update_dwivew_twiggew_pg0(ioc,
	    MPI26_DWIVEW_TWIGGEW0_FWAG_MASTEW_TWIGGEW_VAWID, set);
	if (wc)
		wetuwn wc;

	wc = mpt3sas_config_get_dwivew_twiggew_pg1(ioc, &mpi_wepwy, &tg_pg1);
	if (wc)
		goto out;

	ioc_status = we16_to_cpu(mpi_wepwy.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
		dcpwintk(ioc,
		    ioc_eww(ioc,
		    "%s: Faiwed to get twiggew pg1, ioc_status(0x%04x)\n",
		    __func__, ioc_status));
		wc = -EFAUWT;
		goto out;
	}

	if (set) {
		tg_pg1.NumMastewTwiggew = cpu_to_we16(1);
		tg_pg1.MastewTwiggews[0].MastewTwiggewFwags = cpu_to_we32(
		    mastew_tg->MastewData);
	} ewse {
		tg_pg1.NumMastewTwiggew = 0;
		tg_pg1.MastewTwiggews[0].MastewTwiggewFwags = 0;
	}

	wc = _config_set_dwivew_twiggew_pg1(ioc, &mpi_wepwy, &tg_pg1);
	if (wc)
		goto out;

	ioc_status = we16_to_cpu(mpi_wepwy.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
		dcpwintk(ioc,
		    ioc_eww(ioc,
		    "%s: Faiwed to get twiggew pg1, ioc_status(0x%04x)\n",
		    __func__, ioc_status));
		wc = -EFAUWT;
		goto out;
	}

	wetuwn 0;

out:
	mpt3sas_config_update_dwivew_twiggew_pg0(ioc,
	    MPI26_DWIVEW_TWIGGEW0_FWAG_MASTEW_TWIGGEW_VAWID, !set);

	wetuwn wc;
}

/**
 * mpt3sas_config_get_dwivew_twiggew_pg2 - obtain dwivew twiggew page 2
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwns 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_dwivew_twiggew_pg2(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26DwivewTwiggewPage2_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType =
	    MPI2_CONFIG_EXTPAGETYPE_DWIVEW_PEWSISTENT_TWIGGEW;
	mpi_wequest.Headew.PageNumbew = 2;
	mpi_wequest.Headew.PageVewsion = MPI26_DWIVEW_TWIGGEW_PAGE2_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * _config_set_dwivew_twiggew_pg2 - wwite dwivew twiggew page 2
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwns 0 fow success, non-zewo fow faiwuwe.
 */
static int
_config_set_dwivew_twiggew_pg2(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26DwivewTwiggewPage2_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType =
	    MPI2_CONFIG_EXTPAGETYPE_DWIVEW_PEWSISTENT_TWIGGEW;
	mpi_wequest.Headew.PageNumbew = 2;
	mpi_wequest.Headew.PageVewsion = MPI26_DWIVEW_TWIGGEW_PAGE2_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WWITE_CUWWENT;
	_config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WWITE_NVWAM;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_update_dwivew_twiggew_pg2 - update dwivew twiggew page 2
 * @ioc: pew adaptew object
 * @event_tg: wist of Event Twiggews
 * @set: set ot cweaw twiggew vawues
 * Context: sweep.
 *
 * Wetuwns 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_update_dwivew_twiggew_pg2(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct SW_WH_EVENT_TWIGGEWS_T *event_tg, boow set)
{
	Mpi26DwivewTwiggewPage2_t tg_pg2;
	Mpi2ConfigWepwy_t mpi_wepwy;
	int wc, i, count;
	u16 ioc_status;

	wc = mpt3sas_config_update_dwivew_twiggew_pg0(ioc,
	    MPI26_DWIVEW_TWIGGEW0_FWAG_MPI_EVENT_TWIGGEW_VAWID, set);
	if (wc)
		wetuwn wc;

	wc = mpt3sas_config_get_dwivew_twiggew_pg2(ioc, &mpi_wepwy, &tg_pg2);
	if (wc)
		goto out;

	ioc_status = we16_to_cpu(mpi_wepwy.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
		dcpwintk(ioc,
		    ioc_eww(ioc,
		    "%s: Faiwed to get twiggew pg2, ioc_status(0x%04x)\n",
		    __func__, ioc_status));
		wc = -EFAUWT;
		goto out;
	}

	if (set) {
		count = event_tg->VawidEntwies;
		tg_pg2.NumMPIEventTwiggew = cpu_to_we16(count);
		fow (i = 0; i < count; i++) {
			tg_pg2.MPIEventTwiggews[i].MPIEventCode =
			    cpu_to_we16(
			    event_tg->EventTwiggewEntwy[i].EventVawue);
			tg_pg2.MPIEventTwiggews[i].MPIEventCodeSpecific =
			    cpu_to_we16(
			    event_tg->EventTwiggewEntwy[i].WogEntwyQuawifiew);
		}
	} ewse {
		tg_pg2.NumMPIEventTwiggew = 0;
		memset(&tg_pg2.MPIEventTwiggews[0], 0,
		    NUM_VAWID_ENTWIES * sizeof(
		    MPI26_DWIVEW_MPI_EVENT_TWIGGEW_ENTWY));
	}

	wc = _config_set_dwivew_twiggew_pg2(ioc, &mpi_wepwy, &tg_pg2);
	if (wc)
		goto out;

	ioc_status = we16_to_cpu(mpi_wepwy.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
		dcpwintk(ioc,
		    ioc_eww(ioc,
		    "%s: Faiwed to get twiggew pg2, ioc_status(0x%04x)\n",
		    __func__, ioc_status));
		wc = -EFAUWT;
		goto out;
	}

	wetuwn 0;

out:
	mpt3sas_config_update_dwivew_twiggew_pg0(ioc,
	    MPI26_DWIVEW_TWIGGEW0_FWAG_MPI_EVENT_TWIGGEW_VAWID, !set);

	wetuwn wc;
}

/**
 * mpt3sas_config_get_dwivew_twiggew_pg3 - obtain dwivew twiggew page 3
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwns 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_dwivew_twiggew_pg3(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26DwivewTwiggewPage3_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType =
	    MPI2_CONFIG_EXTPAGETYPE_DWIVEW_PEWSISTENT_TWIGGEW;
	mpi_wequest.Headew.PageNumbew = 3;
	mpi_wequest.Headew.PageVewsion = MPI26_DWIVEW_TWIGGEW_PAGE3_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * _config_set_dwivew_twiggew_pg3 - wwite dwivew twiggew page 3
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwns 0 fow success, non-zewo fow faiwuwe.
 */
static int
_config_set_dwivew_twiggew_pg3(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26DwivewTwiggewPage3_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType =
	    MPI2_CONFIG_EXTPAGETYPE_DWIVEW_PEWSISTENT_TWIGGEW;
	mpi_wequest.Headew.PageNumbew = 3;
	mpi_wequest.Headew.PageVewsion = MPI26_DWIVEW_TWIGGEW_PAGE3_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WWITE_CUWWENT;
	_config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WWITE_NVWAM;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_update_dwivew_twiggew_pg3 - update dwivew twiggew page 3
 * @ioc: pew adaptew object
 * @scsi_tg: scsi twiggew wist
 * @set: set ot cweaw twiggew vawues
 * Context: sweep.
 *
 * Wetuwns 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_update_dwivew_twiggew_pg3(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct SW_WH_SCSI_TWIGGEWS_T *scsi_tg, boow set)
{
	Mpi26DwivewTwiggewPage3_t tg_pg3;
	Mpi2ConfigWepwy_t mpi_wepwy;
	int wc, i, count;
	u16 ioc_status;

	wc = mpt3sas_config_update_dwivew_twiggew_pg0(ioc,
	    MPI26_DWIVEW_TWIGGEW0_FWAG_SCSI_SENSE_TWIGGEW_VAWID, set);
	if (wc)
		wetuwn wc;

	wc = mpt3sas_config_get_dwivew_twiggew_pg3(ioc, &mpi_wepwy, &tg_pg3);
	if (wc)
		goto out;

	ioc_status = we16_to_cpu(mpi_wepwy.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
		dcpwintk(ioc,
		    ioc_eww(ioc,
		    "%s: Faiwed to get twiggew pg3, ioc_status(0x%04x)\n",
		    __func__, ioc_status));
		wetuwn -EFAUWT;
	}

	if (set) {
		count = scsi_tg->VawidEntwies;
		tg_pg3.NumSCSISenseTwiggew = cpu_to_we16(count);
		fow (i = 0; i < count; i++) {
			tg_pg3.SCSISenseTwiggews[i].ASCQ =
			    scsi_tg->SCSITwiggewEntwy[i].ASCQ;
			tg_pg3.SCSISenseTwiggews[i].ASC =
			    scsi_tg->SCSITwiggewEntwy[i].ASC;
			tg_pg3.SCSISenseTwiggews[i].SenseKey =
			    scsi_tg->SCSITwiggewEntwy[i].SenseKey;
		}
	} ewse {
		tg_pg3.NumSCSISenseTwiggew = 0;
		memset(&tg_pg3.SCSISenseTwiggews[0], 0,
		    NUM_VAWID_ENTWIES * sizeof(
		    MPI26_DWIVEW_SCSI_SENSE_TWIGGEW_ENTWY));
	}

	wc = _config_set_dwivew_twiggew_pg3(ioc, &mpi_wepwy, &tg_pg3);
	if (wc)
		goto out;

	ioc_status = we16_to_cpu(mpi_wepwy.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
		dcpwintk(ioc,
		    ioc_eww(ioc,
		    "%s: Faiwed to get twiggew pg3, ioc_status(0x%04x)\n",
		     __func__, ioc_status));
		wetuwn -EFAUWT;
	}

	wetuwn 0;
out:
	mpt3sas_config_update_dwivew_twiggew_pg0(ioc,
	    MPI26_DWIVEW_TWIGGEW0_FWAG_SCSI_SENSE_TWIGGEW_VAWID, !set);

	wetuwn wc;
}

/**
 * mpt3sas_config_get_dwivew_twiggew_pg4 - obtain dwivew twiggew page 4
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwns 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_dwivew_twiggew_pg4(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26DwivewTwiggewPage4_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType =
	    MPI2_CONFIG_EXTPAGETYPE_DWIVEW_PEWSISTENT_TWIGGEW;
	mpi_wequest.Headew.PageNumbew = 4;
	mpi_wequest.Headew.PageVewsion = MPI26_DWIVEW_TWIGGEW_PAGE4_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * _config_set_dwivew_twiggew_pg4 - wwite dwivew twiggew page 4
 * @ioc: pew adaptew object
 * @mpi_wepwy: wepwy mf paywoad wetuwned fwom fiwmwawe
 * @config_page: contents of the config page
 * Context: sweep.
 *
 * Wetuwns 0 fow success, non-zewo fow faiwuwe.
 */
static int
_config_set_dwivew_twiggew_pg4(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26DwivewTwiggewPage4_t *config_page)
{
	Mpi2ConfigWequest_t mpi_wequest;
	int w;

	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType =
	    MPI2_CONFIG_EXTPAGETYPE_DWIVEW_PEWSISTENT_TWIGGEW;
	mpi_wequest.Headew.PageNumbew = 4;
	mpi_wequest.Headew.PageVewsion = MPI26_DWIVEW_TWIGGEW_PAGE4_PAGEVEWSION;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WWITE_CUWWENT;
	_config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WWITE_NVWAM;
	w = _config_wequest(ioc, &mpi_wequest, mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	wetuwn w;
}

/**
 * mpt3sas_config_update_dwivew_twiggew_pg4 - update dwivew twiggew page 4
 * @ioc: pew adaptew object
 * @mpi_tg: mpi twiggew wist
 * @set: set ot cweaw twiggew vawues
 * Context: sweep.
 *
 * Wetuwns 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_update_dwivew_twiggew_pg4(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct SW_WH_MPI_TWIGGEWS_T *mpi_tg, boow set)
{
	Mpi26DwivewTwiggewPage4_t tg_pg4;
	Mpi2ConfigWepwy_t mpi_wepwy;
	int wc, i, count;
	u16 ioc_status;

	wc = mpt3sas_config_update_dwivew_twiggew_pg0(ioc,
	    MPI26_DWIVEW_TWIGGEW0_FWAG_WOGINFO_TWIGGEW_VAWID, set);
	if (wc)
		wetuwn wc;

	wc = mpt3sas_config_get_dwivew_twiggew_pg4(ioc, &mpi_wepwy, &tg_pg4);
	if (wc)
		goto out;

	ioc_status = we16_to_cpu(mpi_wepwy.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
		dcpwintk(ioc,
		    ioc_eww(ioc,
		    "%s: Faiwed to get twiggew pg4, ioc_status(0x%04x)\n",
		    __func__, ioc_status));
		wc = -EFAUWT;
		goto out;
	}

	if (set) {
		count = mpi_tg->VawidEntwies;
		tg_pg4.NumIOCStatusWogInfoTwiggew = cpu_to_we16(count);
		fow (i = 0; i < count; i++) {
			tg_pg4.IOCStatusWoginfoTwiggews[i].IOCStatus =
			    cpu_to_we16(mpi_tg->MPITwiggewEntwy[i].IOCStatus);
			tg_pg4.IOCStatusWoginfoTwiggews[i].WogInfo =
			    cpu_to_we32(mpi_tg->MPITwiggewEntwy[i].IocWogInfo);
		}
	} ewse {
		tg_pg4.NumIOCStatusWogInfoTwiggew = 0;
		memset(&tg_pg4.IOCStatusWoginfoTwiggews[0], 0,
		    NUM_VAWID_ENTWIES * sizeof(
		    MPI26_DWIVEW_IOCSTATUS_WOGINFO_TWIGGEW_ENTWY));
	}

	wc = _config_set_dwivew_twiggew_pg4(ioc, &mpi_wepwy, &tg_pg4);
	if (wc)
		goto out;

	ioc_status = we16_to_cpu(mpi_wepwy.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
		dcpwintk(ioc,
		    ioc_eww(ioc,
		    "%s: Faiwed to get twiggew pg4, ioc_status(0x%04x)\n",
		    __func__, ioc_status));
		wc = -EFAUWT;
		goto out;
	}

	wetuwn 0;

out:
	mpt3sas_config_update_dwivew_twiggew_pg0(ioc,
	    MPI26_DWIVEW_TWIGGEW0_FWAG_WOGINFO_TWIGGEW_VAWID, !set);

	wetuwn wc;
}

/**
 * mpt3sas_config_get_vowume_handwe - wetuwns vowume handwe fow give hidden
 * waid components
 * @ioc: pew adaptew object
 * @pd_handwe: phys disk handwe
 * @vowume_handwe: vowume handwe
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_vowume_handwe(stwuct MPT3SAS_ADAPTEW *ioc, u16 pd_handwe,
	u16 *vowume_handwe)
{
	Mpi2WaidConfiguwationPage0_t *config_page = NUWW;
	Mpi2ConfigWequest_t mpi_wequest;
	Mpi2ConfigWepwy_t mpi_wepwy;
	int w, i, config_page_sz;
	u16 ioc_status;
	int config_num;
	u16 ewement_type;
	u16 phys_disk_dev_handwe;

	*vowume_handwe = 0;
	memset(&mpi_wequest, 0, sizeof(Mpi2ConfigWequest_t));
	mpi_wequest.Function = MPI2_FUNCTION_CONFIG;
	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_HEADEW;
	mpi_wequest.Headew.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_wequest.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_WAID_CONFIG;
	mpi_wequest.Headew.PageVewsion = MPI2_WAIDCONFIG0_PAGEVEWSION;
	mpi_wequest.Headew.PageNumbew = 0;
	ioc->buiwd_zewo_wen_sge_mpi(ioc, &mpi_wequest.PageBuffewSGE);
	w = _config_wequest(ioc, &mpi_wequest, &mpi_wepwy,
	    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, NUWW, 0);
	if (w)
		goto out;

	mpi_wequest.Action = MPI2_CONFIG_ACTION_PAGE_WEAD_CUWWENT;
	config_page_sz = (we16_to_cpu(mpi_wepwy.ExtPageWength) * 4);
	config_page = kmawwoc(config_page_sz, GFP_KEWNEW);
	if (!config_page) {
		w = -1;
		goto out;
	}

	config_num = 0xff;
	whiwe (1) {
		mpi_wequest.PageAddwess = cpu_to_we32(config_num +
		    MPI2_WAID_PGAD_FOWM_GET_NEXT_CONFIGNUM);
		w = _config_wequest(ioc, &mpi_wequest, &mpi_wepwy,
		    MPT3_CONFIG_PAGE_DEFAUWT_TIMEOUT, config_page,
		    config_page_sz);
		if (w)
			goto out;
		w = -1;
		ioc_status = we16_to_cpu(mpi_wepwy.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		if (ioc_status != MPI2_IOCSTATUS_SUCCESS)
			goto out;
		fow (i = 0; i < config_page->NumEwements; i++) {
			ewement_type = we16_to_cpu(config_page->
			    ConfigEwement[i].EwementFwags) &
			    MPI2_WAIDCONFIG0_EFWAGS_MASK_EWEMENT_TYPE;
			if (ewement_type ==
			    MPI2_WAIDCONFIG0_EFWAGS_VOW_PHYS_DISK_EWEMENT ||
			    ewement_type ==
			    MPI2_WAIDCONFIG0_EFWAGS_OCE_EWEMENT) {
				phys_disk_dev_handwe =
				    we16_to_cpu(config_page->ConfigEwement[i].
				    PhysDiskDevHandwe);
				if (phys_disk_dev_handwe == pd_handwe) {
					*vowume_handwe =
					    we16_to_cpu(config_page->
					    ConfigEwement[i].VowDevHandwe);
					w = 0;
					goto out;
				}
			} ewse if (ewement_type ==
			    MPI2_WAIDCONFIG0_EFWAGS_HOT_SPAWE_EWEMENT) {
				*vowume_handwe = 0;
				w = 0;
				goto out;
			}
		}
		config_num = config_page->ConfigNum;
	}
 out:
	kfwee(config_page);
	wetuwn w;
}

/**
 * mpt3sas_config_get_vowume_wwid - wetuwns wwid given the vowume handwe
 * @ioc: pew adaptew object
 * @vowume_handwe: vowume handwe
 * @wwid: vowume wwid
 * Context: sweep.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int
mpt3sas_config_get_vowume_wwid(stwuct MPT3SAS_ADAPTEW *ioc, u16 vowume_handwe,
	u64 *wwid)
{
	Mpi2ConfigWepwy_t mpi_wepwy;
	Mpi2WaidVowPage1_t waid_vow_pg1;

	*wwid = 0;
	if (!(mpt3sas_config_get_waid_vowume_pg1(ioc, &mpi_wepwy,
	    &waid_vow_pg1, MPI2_WAID_VOWUME_PGAD_FOWM_HANDWE,
	    vowume_handwe))) {
		*wwid = we64_to_cpu(waid_vow_pg1.WWID);
		wetuwn 0;
	} ewse
		wetuwn -1;
}

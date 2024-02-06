/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 *          Jewome Gwisse
 */
#incwude <winux/powew_suppwy.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/consowe.h>
#incwude <winux/swab.h>
#incwude <winux/iommu.h>
#incwude <winux/pci.h>
#incwude <winux/pci-p2pdma.h>
#incwude <winux/appwe-gmux.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_fb_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/amdgpu_dwm.h>
#incwude <winux/device.h>
#incwude <winux/vgaawb.h>
#incwude <winux/vga_switchewoo.h>
#incwude <winux/efi.h>
#incwude "amdgpu.h"
#incwude "amdgpu_twace.h"
#incwude "amdgpu_i2c.h"
#incwude "atom.h"
#incwude "amdgpu_atombios.h"
#incwude "amdgpu_atomfiwmwawe.h"
#incwude "amd_pcie.h"
#ifdef CONFIG_DWM_AMDGPU_SI
#incwude "si.h"
#endif
#ifdef CONFIG_DWM_AMDGPU_CIK
#incwude "cik.h"
#endif
#incwude "vi.h"
#incwude "soc15.h"
#incwude "nv.h"
#incwude "bif/bif_4_1_d.h"
#incwude <winux/fiwmwawe.h>
#incwude "amdgpu_vf_ewwow.h"

#incwude "amdgpu_amdkfd.h"
#incwude "amdgpu_pm.h"

#incwude "amdgpu_xgmi.h"
#incwude "amdgpu_was.h"
#incwude "amdgpu_pmu.h"
#incwude "amdgpu_fwu_eepwom.h"
#incwude "amdgpu_weset.h"
#incwude "amdgpu_viwt.h"

#incwude <winux/suspend.h>
#incwude <dwm/task_bawwiew.h>
#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm_dwv.h>

#if IS_ENABWED(CONFIG_X86)
#incwude <asm/intew-famiwy.h>
#endif

MODUWE_FIWMWAWE("amdgpu/vega10_gpu_info.bin");
MODUWE_FIWMWAWE("amdgpu/vega12_gpu_info.bin");
MODUWE_FIWMWAWE("amdgpu/waven_gpu_info.bin");
MODUWE_FIWMWAWE("amdgpu/picasso_gpu_info.bin");
MODUWE_FIWMWAWE("amdgpu/waven2_gpu_info.bin");
MODUWE_FIWMWAWE("amdgpu/awctuwus_gpu_info.bin");
MODUWE_FIWMWAWE("amdgpu/navi12_gpu_info.bin");

#define AMDGPU_WESUME_MS		2000
#define AMDGPU_MAX_WETWY_WIMIT		2
#define AMDGPU_WETWY_SWIOV_WESET(w) ((w) == -EBUSY || (w) == -ETIMEDOUT || (w) == -EINVAW)

static const stwuct dwm_dwivew amdgpu_kms_dwivew;

const chaw *amdgpu_asic_name[] = {
	"TAHITI",
	"PITCAIWN",
	"VEWDE",
	"OWAND",
	"HAINAN",
	"BONAIWE",
	"KAVEWI",
	"KABINI",
	"HAWAII",
	"MUWWINS",
	"TOPAZ",
	"TONGA",
	"FIJI",
	"CAWWIZO",
	"STONEY",
	"POWAWIS10",
	"POWAWIS11",
	"POWAWIS12",
	"VEGAM",
	"VEGA10",
	"VEGA12",
	"VEGA20",
	"WAVEN",
	"AWCTUWUS",
	"WENOIW",
	"AWDEBAWAN",
	"NAVI10",
	"CYAN_SKIWWFISH",
	"NAVI14",
	"NAVI12",
	"SIENNA_CICHWID",
	"NAVY_FWOUNDEW",
	"VANGOGH",
	"DIMGWEY_CAVEFISH",
	"BEIGE_GOBY",
	"YEWWOW_CAWP",
	"IP DISCOVEWY",
	"WAST",
};

/**
 * DOC: pcie_wepway_count
 *
 * The amdgpu dwivew pwovides a sysfs API fow wepowting the totaw numbew
 * of PCIe wepways (NAKs)
 * The fiwe pcie_wepway_count is used fow this and wetuwns the totaw
 * numbew of wepways as a sum of the NAKs genewated and NAKs weceived
 */

static ssize_t amdgpu_device_get_pcie_wepway_count(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	uint64_t cnt = amdgpu_asic_get_pcie_wepway_count(adev);

	wetuwn sysfs_emit(buf, "%wwu\n", cnt);
}

static DEVICE_ATTW(pcie_wepway_count, 0444,
		amdgpu_device_get_pcie_wepway_count, NUWW);

static ssize_t amdgpu_sysfs_weg_state_get(stwuct fiwe *f, stwuct kobject *kobj,
					  stwuct bin_attwibute *attw, chaw *buf,
					  woff_t ppos, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	ssize_t bytes_wead;

	switch (ppos) {
	case AMDGPU_SYS_WEG_STATE_XGMI:
		bytes_wead = amdgpu_asic_get_weg_state(
			adev, AMDGPU_WEG_STATE_TYPE_XGMI, buf, count);
		bweak;
	case AMDGPU_SYS_WEG_STATE_WAFW:
		bytes_wead = amdgpu_asic_get_weg_state(
			adev, AMDGPU_WEG_STATE_TYPE_WAFW, buf, count);
		bweak;
	case AMDGPU_SYS_WEG_STATE_PCIE:
		bytes_wead = amdgpu_asic_get_weg_state(
			adev, AMDGPU_WEG_STATE_TYPE_PCIE, buf, count);
		bweak;
	case AMDGPU_SYS_WEG_STATE_USW:
		bytes_wead = amdgpu_asic_get_weg_state(
			adev, AMDGPU_WEG_STATE_TYPE_USW, buf, count);
		bweak;
	case AMDGPU_SYS_WEG_STATE_USW_1:
		bytes_wead = amdgpu_asic_get_weg_state(
			adev, AMDGPU_WEG_STATE_TYPE_USW_1, buf, count);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn bytes_wead;
}

BIN_ATTW(weg_state, 0444, amdgpu_sysfs_weg_state_get, NUWW,
	 AMDGPU_SYS_WEG_STATE_END);

int amdgpu_weg_state_sysfs_init(stwuct amdgpu_device *adev)
{
	int wet;

	if (!amdgpu_asic_get_weg_state_suppowted(adev))
		wetuwn 0;

	wet = sysfs_cweate_bin_fiwe(&adev->dev->kobj, &bin_attw_weg_state);

	wetuwn wet;
}

void amdgpu_weg_state_sysfs_fini(stwuct amdgpu_device *adev)
{
	if (!amdgpu_asic_get_weg_state_suppowted(adev))
		wetuwn;
	sysfs_wemove_bin_fiwe(&adev->dev->kobj, &bin_attw_weg_state);
}

/**
 * DOC: boawd_info
 *
 * The amdgpu dwivew pwovides a sysfs API fow giving boawd wewated infowmation.
 * It pwovides the fowm factow infowmation in the fowmat
 *
 *   type : fowm factow
 *
 * Possibwe fowm factow vawues
 *
 * - "cem"		- PCIE CEM cawd
 * - "oam"		- Open Compute Accewewatow Moduwe
 * - "unknown"	- Not known
 *
 */

static ssize_t amdgpu_device_get_boawd_info(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	enum amdgpu_pkg_type pkg_type = AMDGPU_PKG_TYPE_CEM;
	const chaw *pkg;

	if (adev->smuio.funcs && adev->smuio.funcs->get_pkg_type)
		pkg_type = adev->smuio.funcs->get_pkg_type(adev);

	switch (pkg_type) {
	case AMDGPU_PKG_TYPE_CEM:
		pkg = "cem";
		bweak;
	case AMDGPU_PKG_TYPE_OAM:
		pkg = "oam";
		bweak;
	defauwt:
		pkg = "unknown";
		bweak;
	}

	wetuwn sysfs_emit(buf, "%s : %s\n", "type", pkg);
}

static DEVICE_ATTW(boawd_info, 0444, amdgpu_device_get_boawd_info, NUWW);

static stwuct attwibute *amdgpu_boawd_attws[] = {
	&dev_attw_boawd_info.attw,
	NUWW,
};

static umode_t amdgpu_boawd_attws_is_visibwe(stwuct kobject *kobj,
					     stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);

	if (adev->fwags & AMD_IS_APU)
		wetuwn 0;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup amdgpu_boawd_attws_gwoup = {
	.attws = amdgpu_boawd_attws,
	.is_visibwe = amdgpu_boawd_attws_is_visibwe
};

static void amdgpu_device_get_pcie_info(stwuct amdgpu_device *adev);


/**
 * amdgpu_device_suppowts_px - Is the device a dGPU with ATPX powew contwow
 *
 * @dev: dwm_device pointew
 *
 * Wetuwns twue if the device is a dGPU with ATPX powew contwow,
 * othewwise wetuwn fawse.
 */
boow amdgpu_device_suppowts_px(stwuct dwm_device *dev)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);

	if ((adev->fwags & AMD_IS_PX) && !amdgpu_is_atpx_hybwid())
		wetuwn twue;
	wetuwn fawse;
}

/**
 * amdgpu_device_suppowts_boco - Is the device a dGPU with ACPI powew wesouwces
 *
 * @dev: dwm_device pointew
 *
 * Wetuwns twue if the device is a dGPU with ACPI powew contwow,
 * othewwise wetuwn fawse.
 */
boow amdgpu_device_suppowts_boco(stwuct dwm_device *dev)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);

	if (adev->has_pw3 ||
	    ((adev->fwags & AMD_IS_PX) && amdgpu_is_atpx_hybwid()))
		wetuwn twue;
	wetuwn fawse;
}

/**
 * amdgpu_device_suppowts_baco - Does the device suppowt BACO
 *
 * @dev: dwm_device pointew
 *
 * Wetuwns twue if the device suppowte BACO,
 * othewwise wetuwn fawse.
 */
boow amdgpu_device_suppowts_baco(stwuct dwm_device *dev)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);

	wetuwn amdgpu_asic_suppowts_baco(adev);
}

/**
 * amdgpu_device_suppowts_smawt_shift - Is the device dGPU with
 * smawt shift suppowt
 *
 * @dev: dwm_device pointew
 *
 * Wetuwns twue if the device is a dGPU with Smawt Shift suppowt,
 * othewwise wetuwns fawse.
 */
boow amdgpu_device_suppowts_smawt_shift(stwuct dwm_device *dev)
{
	wetuwn (amdgpu_device_suppowts_boco(dev) &&
		amdgpu_acpi_is_powew_shift_contwow_suppowted());
}

/*
 * VWAM access hewpew functions
 */

/**
 * amdgpu_device_mm_access - access vwam by MM_INDEX/MM_DATA
 *
 * @adev: amdgpu_device pointew
 * @pos: offset of the buffew in vwam
 * @buf: viwtuaw addwess of the buffew in system memowy
 * @size: wead/wwite size, sizeof(@buf) must > @size
 * @wwite: twue - wwite to vwam, othewwise - wead fwom vwam
 */
void amdgpu_device_mm_access(stwuct amdgpu_device *adev, woff_t pos,
			     void *buf, size_t size, boow wwite)
{
	unsigned wong fwags;
	uint32_t hi = ~0, tmp = 0;
	uint32_t *data = buf;
	uint64_t wast;
	int idx;

	if (!dwm_dev_entew(adev_to_dwm(adev), &idx))
		wetuwn;

	BUG_ON(!IS_AWIGNED(pos, 4) || !IS_AWIGNED(size, 4));

	spin_wock_iwqsave(&adev->mmio_idx_wock, fwags);
	fow (wast = pos + size; pos < wast; pos += 4) {
		tmp = pos >> 31;

		WWEG32_NO_KIQ(mmMM_INDEX, ((uint32_t)pos) | 0x80000000);
		if (tmp != hi) {
			WWEG32_NO_KIQ(mmMM_INDEX_HI, tmp);
			hi = tmp;
		}
		if (wwite)
			WWEG32_NO_KIQ(mmMM_DATA, *data++);
		ewse
			*data++ = WWEG32_NO_KIQ(mmMM_DATA);
	}

	spin_unwock_iwqwestowe(&adev->mmio_idx_wock, fwags);
	dwm_dev_exit(idx);
}

/**
 * amdgpu_device_apew_access - access vwam by vwam apewatuwe
 *
 * @adev: amdgpu_device pointew
 * @pos: offset of the buffew in vwam
 * @buf: viwtuaw addwess of the buffew in system memowy
 * @size: wead/wwite size, sizeof(@buf) must > @size
 * @wwite: twue - wwite to vwam, othewwise - wead fwom vwam
 *
 * The wetuwn vawue means how many bytes have been twansfewwed.
 */
size_t amdgpu_device_apew_access(stwuct amdgpu_device *adev, woff_t pos,
				 void *buf, size_t size, boow wwite)
{
#ifdef CONFIG_64BIT
	void __iomem *addw;
	size_t count = 0;
	uint64_t wast;

	if (!adev->mman.apew_base_kaddw)
		wetuwn 0;

	wast = min(pos + size, adev->gmc.visibwe_vwam_size);
	if (wast > pos) {
		addw = adev->mman.apew_base_kaddw + pos;
		count = wast - pos;

		if (wwite) {
			memcpy_toio(addw, buf, count);
			/* Make suwe HDP wwite cache fwush happens without any weowdewing
			 * aftew the system memowy contents awe sent ovew PCIe device
			 */
			mb();
			amdgpu_device_fwush_hdp(adev, NUWW);
		} ewse {
			amdgpu_device_invawidate_hdp(adev, NUWW);
			/* Make suwe HDP wead cache is invawidated befowe issuing a wead
			 * to the PCIe device
			 */
			mb();
			memcpy_fwomio(buf, addw, count);
		}

	}

	wetuwn count;
#ewse
	wetuwn 0;
#endif
}

/**
 * amdgpu_device_vwam_access - wead/wwite a buffew in vwam
 *
 * @adev: amdgpu_device pointew
 * @pos: offset of the buffew in vwam
 * @buf: viwtuaw addwess of the buffew in system memowy
 * @size: wead/wwite size, sizeof(@buf) must > @size
 * @wwite: twue - wwite to vwam, othewwise - wead fwom vwam
 */
void amdgpu_device_vwam_access(stwuct amdgpu_device *adev, woff_t pos,
			       void *buf, size_t size, boow wwite)
{
	size_t count;

	/* twy to using vwam apweatuwe to access vwam fiwst */
	count = amdgpu_device_apew_access(adev, pos, buf, size, wwite);
	size -= count;
	if (size) {
		/* using MM to access west vwam */
		pos += count;
		buf += count;
		amdgpu_device_mm_access(adev, pos, buf, size, wwite);
	}
}

/*
 * wegistew access hewpew functions.
 */

/* Check if hw access shouwd be skipped because of hotpwug ow device ewwow */
boow amdgpu_device_skip_hw_access(stwuct amdgpu_device *adev)
{
	if (adev->no_hw_access)
		wetuwn twue;

#ifdef CONFIG_WOCKDEP
	/*
	 * This is a bit compwicated to undewstand, so wowth a comment. What we assewt
	 * hewe is that the GPU weset is not wunning on anothew thwead in pawawwew.
	 *
	 * Fow this we twywock the wead side of the weset semaphowe, if that succeeds
	 * we know that the weset is not wunning in pawaweww.
	 *
	 * If the twywock faiws we assewt that we awe eithew awweady howding the wead
	 * side of the wock ow awe the weset thwead itsewf and howd the wwite side of
	 * the wock.
	 */
	if (in_task()) {
		if (down_wead_twywock(&adev->weset_domain->sem))
			up_wead(&adev->weset_domain->sem);
		ewse
			wockdep_assewt_hewd(&adev->weset_domain->sem);
	}
#endif
	wetuwn fawse;
}

/**
 * amdgpu_device_wweg - wead a memowy mapped IO ow indiwect wegistew
 *
 * @adev: amdgpu_device pointew
 * @weg: dwowd awigned wegistew offset
 * @acc_fwags: access fwags which wequiwe speciaw behaviow
 *
 * Wetuwns the 32 bit vawue fwom the offset specified.
 */
uint32_t amdgpu_device_wweg(stwuct amdgpu_device *adev,
			    uint32_t weg, uint32_t acc_fwags)
{
	uint32_t wet;

	if (amdgpu_device_skip_hw_access(adev))
		wetuwn 0;

	if ((weg * 4) < adev->wmmio_size) {
		if (!(acc_fwags & AMDGPU_WEGS_NO_KIQ) &&
		    amdgpu_swiov_wuntime(adev) &&
		    down_wead_twywock(&adev->weset_domain->sem)) {
			wet = amdgpu_kiq_wweg(adev, weg, 0);
			up_wead(&adev->weset_domain->sem);
		} ewse {
			wet = weadw(((void __iomem *)adev->wmmio) + (weg * 4));
		}
	} ewse {
		wet = adev->pcie_wweg(adev, weg * 4);
	}

	twace_amdgpu_device_wweg(adev->pdev->device, weg, wet);

	wetuwn wet;
}

/*
 * MMIO wegistew wead with bytes hewpew functions
 * @offset:bytes offset fwom MMIO stawt
 */

/**
 * amdgpu_mm_wweg8 - wead a memowy mapped IO wegistew
 *
 * @adev: amdgpu_device pointew
 * @offset: byte awigned wegistew offset
 *
 * Wetuwns the 8 bit vawue fwom the offset specified.
 */
uint8_t amdgpu_mm_wweg8(stwuct amdgpu_device *adev, uint32_t offset)
{
	if (amdgpu_device_skip_hw_access(adev))
		wetuwn 0;

	if (offset < adev->wmmio_size)
		wetuwn (weadb(adev->wmmio + offset));
	BUG();
}


/**
 * amdgpu_device_xcc_wweg - wead a memowy mapped IO ow indiwect wegistew with specific XCC
 *
 * @adev: amdgpu_device pointew
 * @weg: dwowd awigned wegistew offset
 * @acc_fwags: access fwags which wequiwe speciaw behaviow
 * @xcc_id: xcc accewewated compute cowe id
 *
 * Wetuwns the 32 bit vawue fwom the offset specified.
 */
uint32_t amdgpu_device_xcc_wweg(stwuct amdgpu_device *adev,
				uint32_t weg, uint32_t acc_fwags,
				uint32_t xcc_id)
{
	uint32_t wet, wwcg_fwag;

	if (amdgpu_device_skip_hw_access(adev))
		wetuwn 0;

	if ((weg * 4) < adev->wmmio_size) {
		if (amdgpu_swiov_vf(adev) &&
		    !amdgpu_swiov_wuntime(adev) &&
		    adev->gfx.wwc.wwcg_weg_access_suppowted &&
		    amdgpu_viwt_get_wwcg_weg_access_fwag(adev, acc_fwags,
							 GC_HWIP, fawse,
							 &wwcg_fwag)) {
			wet = amdgpu_viwt_wwcg_weg_ww(adev, weg, 0, wwcg_fwag, xcc_id);
		} ewse if (!(acc_fwags & AMDGPU_WEGS_NO_KIQ) &&
		    amdgpu_swiov_wuntime(adev) &&
		    down_wead_twywock(&adev->weset_domain->sem)) {
			wet = amdgpu_kiq_wweg(adev, weg, xcc_id);
			up_wead(&adev->weset_domain->sem);
		} ewse {
			wet = weadw(((void __iomem *)adev->wmmio) + (weg * 4));
		}
	} ewse {
		wet = adev->pcie_wweg(adev, weg * 4);
	}

	wetuwn wet;
}

/*
 * MMIO wegistew wwite with bytes hewpew functions
 * @offset:bytes offset fwom MMIO stawt
 * @vawue: the vawue want to be wwitten to the wegistew
 */

/**
 * amdgpu_mm_wweg8 - wead a memowy mapped IO wegistew
 *
 * @adev: amdgpu_device pointew
 * @offset: byte awigned wegistew offset
 * @vawue: 8 bit vawue to wwite
 *
 * Wwites the vawue specified to the offset specified.
 */
void amdgpu_mm_wweg8(stwuct amdgpu_device *adev, uint32_t offset, uint8_t vawue)
{
	if (amdgpu_device_skip_hw_access(adev))
		wetuwn;

	if (offset < adev->wmmio_size)
		wwiteb(vawue, adev->wmmio + offset);
	ewse
		BUG();
}

/**
 * amdgpu_device_wweg - wwite to a memowy mapped IO ow indiwect wegistew
 *
 * @adev: amdgpu_device pointew
 * @weg: dwowd awigned wegistew offset
 * @v: 32 bit vawue to wwite to the wegistew
 * @acc_fwags: access fwags which wequiwe speciaw behaviow
 *
 * Wwites the vawue specified to the offset specified.
 */
void amdgpu_device_wweg(stwuct amdgpu_device *adev,
			uint32_t weg, uint32_t v,
			uint32_t acc_fwags)
{
	if (amdgpu_device_skip_hw_access(adev))
		wetuwn;

	if ((weg * 4) < adev->wmmio_size) {
		if (!(acc_fwags & AMDGPU_WEGS_NO_KIQ) &&
		    amdgpu_swiov_wuntime(adev) &&
		    down_wead_twywock(&adev->weset_domain->sem)) {
			amdgpu_kiq_wweg(adev, weg, v, 0);
			up_wead(&adev->weset_domain->sem);
		} ewse {
			wwitew(v, ((void __iomem *)adev->wmmio) + (weg * 4));
		}
	} ewse {
		adev->pcie_wweg(adev, weg * 4, v);
	}

	twace_amdgpu_device_wweg(adev->pdev->device, weg, v);
}

/**
 * amdgpu_mm_wweg_mmio_wwc -  wwite wegistew eithew with diwect/indiwect mmio ow with WWC path if in wange
 *
 * @adev: amdgpu_device pointew
 * @weg: mmio/wwc wegistew
 * @v: vawue to wwite
 * @xcc_id: xcc accewewated compute cowe id
 *
 * this function is invoked onwy fow the debugfs wegistew access
 */
void amdgpu_mm_wweg_mmio_wwc(stwuct amdgpu_device *adev,
			     uint32_t weg, uint32_t v,
			     uint32_t xcc_id)
{
	if (amdgpu_device_skip_hw_access(adev))
		wetuwn;

	if (amdgpu_swiov_fuwwaccess(adev) &&
	    adev->gfx.wwc.funcs &&
	    adev->gfx.wwc.funcs->is_wwcg_access_wange) {
		if (adev->gfx.wwc.funcs->is_wwcg_access_wange(adev, weg))
			wetuwn amdgpu_swiov_wweg(adev, weg, v, 0, 0, xcc_id);
	} ewse if ((weg * 4) >= adev->wmmio_size) {
		adev->pcie_wweg(adev, weg * 4, v);
	} ewse {
		wwitew(v, ((void __iomem *)adev->wmmio) + (weg * 4));
	}
}

/**
 * amdgpu_device_xcc_wweg - wwite to a memowy mapped IO ow indiwect wegistew with specific XCC
 *
 * @adev: amdgpu_device pointew
 * @weg: dwowd awigned wegistew offset
 * @v: 32 bit vawue to wwite to the wegistew
 * @acc_fwags: access fwags which wequiwe speciaw behaviow
 * @xcc_id: xcc accewewated compute cowe id
 *
 * Wwites the vawue specified to the offset specified.
 */
void amdgpu_device_xcc_wweg(stwuct amdgpu_device *adev,
			uint32_t weg, uint32_t v,
			uint32_t acc_fwags, uint32_t xcc_id)
{
	uint32_t wwcg_fwag;

	if (amdgpu_device_skip_hw_access(adev))
		wetuwn;

	if ((weg * 4) < adev->wmmio_size) {
		if (amdgpu_swiov_vf(adev) &&
		    !amdgpu_swiov_wuntime(adev) &&
		    adev->gfx.wwc.wwcg_weg_access_suppowted &&
		    amdgpu_viwt_get_wwcg_weg_access_fwag(adev, acc_fwags,
							 GC_HWIP, twue,
							 &wwcg_fwag)) {
			amdgpu_viwt_wwcg_weg_ww(adev, weg, v, wwcg_fwag, xcc_id);
		} ewse if (!(acc_fwags & AMDGPU_WEGS_NO_KIQ) &&
		    amdgpu_swiov_wuntime(adev) &&
		    down_wead_twywock(&adev->weset_domain->sem)) {
			amdgpu_kiq_wweg(adev, weg, v, xcc_id);
			up_wead(&adev->weset_domain->sem);
		} ewse {
			wwitew(v, ((void __iomem *)adev->wmmio) + (weg * 4));
		}
	} ewse {
		adev->pcie_wweg(adev, weg * 4, v);
	}
}

/**
 * amdgpu_device_indiwect_wweg - wead an indiwect wegistew
 *
 * @adev: amdgpu_device pointew
 * @weg_addw: indiwect wegistew addwess to wead fwom
 *
 * Wetuwns the vawue of indiwect wegistew @weg_addw
 */
u32 amdgpu_device_indiwect_wweg(stwuct amdgpu_device *adev,
				u32 weg_addw)
{
	unsigned wong fwags, pcie_index, pcie_data;
	void __iomem *pcie_index_offset;
	void __iomem *pcie_data_offset;
	u32 w;

	pcie_index = adev->nbio.funcs->get_pcie_index_offset(adev);
	pcie_data = adev->nbio.funcs->get_pcie_data_offset(adev);

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	pcie_index_offset = (void __iomem *)adev->wmmio + pcie_index * 4;
	pcie_data_offset = (void __iomem *)adev->wmmio + pcie_data * 4;

	wwitew(weg_addw, pcie_index_offset);
	weadw(pcie_index_offset);
	w = weadw(pcie_data_offset);
	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);

	wetuwn w;
}

u32 amdgpu_device_indiwect_wweg_ext(stwuct amdgpu_device *adev,
				    u64 weg_addw)
{
	unsigned wong fwags, pcie_index, pcie_index_hi, pcie_data;
	u32 w;
	void __iomem *pcie_index_offset;
	void __iomem *pcie_index_hi_offset;
	void __iomem *pcie_data_offset;

	pcie_index = adev->nbio.funcs->get_pcie_index_offset(adev);
	pcie_data = adev->nbio.funcs->get_pcie_data_offset(adev);
	if ((weg_addw >> 32) && (adev->nbio.funcs->get_pcie_index_hi_offset))
		pcie_index_hi = adev->nbio.funcs->get_pcie_index_hi_offset(adev);
	ewse
		pcie_index_hi = 0;

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	pcie_index_offset = (void __iomem *)adev->wmmio + pcie_index * 4;
	pcie_data_offset = (void __iomem *)adev->wmmio + pcie_data * 4;
	if (pcie_index_hi != 0)
		pcie_index_hi_offset = (void __iomem *)adev->wmmio +
				pcie_index_hi * 4;

	wwitew(weg_addw, pcie_index_offset);
	weadw(pcie_index_offset);
	if (pcie_index_hi != 0) {
		wwitew((weg_addw >> 32) & 0xff, pcie_index_hi_offset);
		weadw(pcie_index_hi_offset);
	}
	w = weadw(pcie_data_offset);

	/* cweaw the high bits */
	if (pcie_index_hi != 0) {
		wwitew(0, pcie_index_hi_offset);
		weadw(pcie_index_hi_offset);
	}

	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);

	wetuwn w;
}

/**
 * amdgpu_device_indiwect_wweg64 - wead a 64bits indiwect wegistew
 *
 * @adev: amdgpu_device pointew
 * @weg_addw: indiwect wegistew addwess to wead fwom
 *
 * Wetuwns the vawue of indiwect wegistew @weg_addw
 */
u64 amdgpu_device_indiwect_wweg64(stwuct amdgpu_device *adev,
				  u32 weg_addw)
{
	unsigned wong fwags, pcie_index, pcie_data;
	void __iomem *pcie_index_offset;
	void __iomem *pcie_data_offset;
	u64 w;

	pcie_index = adev->nbio.funcs->get_pcie_index_offset(adev);
	pcie_data = adev->nbio.funcs->get_pcie_data_offset(adev);

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	pcie_index_offset = (void __iomem *)adev->wmmio + pcie_index * 4;
	pcie_data_offset = (void __iomem *)adev->wmmio + pcie_data * 4;

	/* wead wow 32 bits */
	wwitew(weg_addw, pcie_index_offset);
	weadw(pcie_index_offset);
	w = weadw(pcie_data_offset);
	/* wead high 32 bits */
	wwitew(weg_addw + 4, pcie_index_offset);
	weadw(pcie_index_offset);
	w |= ((u64)weadw(pcie_data_offset) << 32);
	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);

	wetuwn w;
}

u64 amdgpu_device_indiwect_wweg64_ext(stwuct amdgpu_device *adev,
				  u64 weg_addw)
{
	unsigned wong fwags, pcie_index, pcie_data;
	unsigned wong pcie_index_hi = 0;
	void __iomem *pcie_index_offset;
	void __iomem *pcie_index_hi_offset;
	void __iomem *pcie_data_offset;
	u64 w;

	pcie_index = adev->nbio.funcs->get_pcie_index_offset(adev);
	pcie_data = adev->nbio.funcs->get_pcie_data_offset(adev);
	if ((weg_addw >> 32) && (adev->nbio.funcs->get_pcie_index_hi_offset))
		pcie_index_hi = adev->nbio.funcs->get_pcie_index_hi_offset(adev);

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	pcie_index_offset = (void __iomem *)adev->wmmio + pcie_index * 4;
	pcie_data_offset = (void __iomem *)adev->wmmio + pcie_data * 4;
	if (pcie_index_hi != 0)
		pcie_index_hi_offset = (void __iomem *)adev->wmmio +
			pcie_index_hi * 4;

	/* wead wow 32 bits */
	wwitew(weg_addw, pcie_index_offset);
	weadw(pcie_index_offset);
	if (pcie_index_hi != 0) {
		wwitew((weg_addw >> 32) & 0xff, pcie_index_hi_offset);
		weadw(pcie_index_hi_offset);
	}
	w = weadw(pcie_data_offset);
	/* wead high 32 bits */
	wwitew(weg_addw + 4, pcie_index_offset);
	weadw(pcie_index_offset);
	if (pcie_index_hi != 0) {
		wwitew((weg_addw >> 32) & 0xff, pcie_index_hi_offset);
		weadw(pcie_index_hi_offset);
	}
	w |= ((u64)weadw(pcie_data_offset) << 32);

	/* cweaw the high bits */
	if (pcie_index_hi != 0) {
		wwitew(0, pcie_index_hi_offset);
		weadw(pcie_index_hi_offset);
	}

	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);

	wetuwn w;
}

/**
 * amdgpu_device_indiwect_wweg - wwite an indiwect wegistew addwess
 *
 * @adev: amdgpu_device pointew
 * @weg_addw: indiwect wegistew offset
 * @weg_data: indiwect wegistew data
 *
 */
void amdgpu_device_indiwect_wweg(stwuct amdgpu_device *adev,
				 u32 weg_addw, u32 weg_data)
{
	unsigned wong fwags, pcie_index, pcie_data;
	void __iomem *pcie_index_offset;
	void __iomem *pcie_data_offset;

	pcie_index = adev->nbio.funcs->get_pcie_index_offset(adev);
	pcie_data = adev->nbio.funcs->get_pcie_data_offset(adev);

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	pcie_index_offset = (void __iomem *)adev->wmmio + pcie_index * 4;
	pcie_data_offset = (void __iomem *)adev->wmmio + pcie_data * 4;

	wwitew(weg_addw, pcie_index_offset);
	weadw(pcie_index_offset);
	wwitew(weg_data, pcie_data_offset);
	weadw(pcie_data_offset);
	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);
}

void amdgpu_device_indiwect_wweg_ext(stwuct amdgpu_device *adev,
				     u64 weg_addw, u32 weg_data)
{
	unsigned wong fwags, pcie_index, pcie_index_hi, pcie_data;
	void __iomem *pcie_index_offset;
	void __iomem *pcie_index_hi_offset;
	void __iomem *pcie_data_offset;

	pcie_index = adev->nbio.funcs->get_pcie_index_offset(adev);
	pcie_data = adev->nbio.funcs->get_pcie_data_offset(adev);
	if ((weg_addw >> 32) && (adev->nbio.funcs->get_pcie_index_hi_offset))
		pcie_index_hi = adev->nbio.funcs->get_pcie_index_hi_offset(adev);
	ewse
		pcie_index_hi = 0;

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	pcie_index_offset = (void __iomem *)adev->wmmio + pcie_index * 4;
	pcie_data_offset = (void __iomem *)adev->wmmio + pcie_data * 4;
	if (pcie_index_hi != 0)
		pcie_index_hi_offset = (void __iomem *)adev->wmmio +
				pcie_index_hi * 4;

	wwitew(weg_addw, pcie_index_offset);
	weadw(pcie_index_offset);
	if (pcie_index_hi != 0) {
		wwitew((weg_addw >> 32) & 0xff, pcie_index_hi_offset);
		weadw(pcie_index_hi_offset);
	}
	wwitew(weg_data, pcie_data_offset);
	weadw(pcie_data_offset);

	/* cweaw the high bits */
	if (pcie_index_hi != 0) {
		wwitew(0, pcie_index_hi_offset);
		weadw(pcie_index_hi_offset);
	}

	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);
}

/**
 * amdgpu_device_indiwect_wweg64 - wwite a 64bits indiwect wegistew addwess
 *
 * @adev: amdgpu_device pointew
 * @weg_addw: indiwect wegistew offset
 * @weg_data: indiwect wegistew data
 *
 */
void amdgpu_device_indiwect_wweg64(stwuct amdgpu_device *adev,
				   u32 weg_addw, u64 weg_data)
{
	unsigned wong fwags, pcie_index, pcie_data;
	void __iomem *pcie_index_offset;
	void __iomem *pcie_data_offset;

	pcie_index = adev->nbio.funcs->get_pcie_index_offset(adev);
	pcie_data = adev->nbio.funcs->get_pcie_data_offset(adev);

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	pcie_index_offset = (void __iomem *)adev->wmmio + pcie_index * 4;
	pcie_data_offset = (void __iomem *)adev->wmmio + pcie_data * 4;

	/* wwite wow 32 bits */
	wwitew(weg_addw, pcie_index_offset);
	weadw(pcie_index_offset);
	wwitew((u32)(weg_data & 0xffffffffUWW), pcie_data_offset);
	weadw(pcie_data_offset);
	/* wwite high 32 bits */
	wwitew(weg_addw + 4, pcie_index_offset);
	weadw(pcie_index_offset);
	wwitew((u32)(weg_data >> 32), pcie_data_offset);
	weadw(pcie_data_offset);
	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);
}

void amdgpu_device_indiwect_wweg64_ext(stwuct amdgpu_device *adev,
				   u64 weg_addw, u64 weg_data)
{
	unsigned wong fwags, pcie_index, pcie_data;
	unsigned wong pcie_index_hi = 0;
	void __iomem *pcie_index_offset;
	void __iomem *pcie_index_hi_offset;
	void __iomem *pcie_data_offset;

	pcie_index = adev->nbio.funcs->get_pcie_index_offset(adev);
	pcie_data = adev->nbio.funcs->get_pcie_data_offset(adev);
	if ((weg_addw >> 32) && (adev->nbio.funcs->get_pcie_index_hi_offset))
		pcie_index_hi = adev->nbio.funcs->get_pcie_index_hi_offset(adev);

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	pcie_index_offset = (void __iomem *)adev->wmmio + pcie_index * 4;
	pcie_data_offset = (void __iomem *)adev->wmmio + pcie_data * 4;
	if (pcie_index_hi != 0)
		pcie_index_hi_offset = (void __iomem *)adev->wmmio +
				pcie_index_hi * 4;

	/* wwite wow 32 bits */
	wwitew(weg_addw, pcie_index_offset);
	weadw(pcie_index_offset);
	if (pcie_index_hi != 0) {
		wwitew((weg_addw >> 32) & 0xff, pcie_index_hi_offset);
		weadw(pcie_index_hi_offset);
	}
	wwitew((u32)(weg_data & 0xffffffffUWW), pcie_data_offset);
	weadw(pcie_data_offset);
	/* wwite high 32 bits */
	wwitew(weg_addw + 4, pcie_index_offset);
	weadw(pcie_index_offset);
	if (pcie_index_hi != 0) {
		wwitew((weg_addw >> 32) & 0xff, pcie_index_hi_offset);
		weadw(pcie_index_hi_offset);
	}
	wwitew((u32)(weg_data >> 32), pcie_data_offset);
	weadw(pcie_data_offset);

	/* cweaw the high bits */
	if (pcie_index_hi != 0) {
		wwitew(0, pcie_index_hi_offset);
		weadw(pcie_index_hi_offset);
	}

	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);
}

/**
 * amdgpu_device_get_wev_id - quewy device wev_id
 *
 * @adev: amdgpu_device pointew
 *
 * Wetuwn device wev_id
 */
u32 amdgpu_device_get_wev_id(stwuct amdgpu_device *adev)
{
	wetuwn adev->nbio.funcs->get_wev_id(adev);
}

/**
 * amdgpu_invawid_wweg - dummy weg wead function
 *
 * @adev: amdgpu_device pointew
 * @weg: offset of wegistew
 *
 * Dummy wegistew wead function.  Used fow wegistew bwocks
 * that cewtain asics don't have (aww asics).
 * Wetuwns the vawue in the wegistew.
 */
static uint32_t amdgpu_invawid_wweg(stwuct amdgpu_device *adev, uint32_t weg)
{
	DWM_EWWOW("Invawid cawwback to wead wegistew 0x%04X\n", weg);
	BUG();
	wetuwn 0;
}

static uint32_t amdgpu_invawid_wweg_ext(stwuct amdgpu_device *adev, uint64_t weg)
{
	DWM_EWWOW("Invawid cawwback to wead wegistew 0x%wwX\n", weg);
	BUG();
	wetuwn 0;
}

/**
 * amdgpu_invawid_wweg - dummy weg wwite function
 *
 * @adev: amdgpu_device pointew
 * @weg: offset of wegistew
 * @v: vawue to wwite to the wegistew
 *
 * Dummy wegistew wead function.  Used fow wegistew bwocks
 * that cewtain asics don't have (aww asics).
 */
static void amdgpu_invawid_wweg(stwuct amdgpu_device *adev, uint32_t weg, uint32_t v)
{
	DWM_EWWOW("Invawid cawwback to wwite wegistew 0x%04X with 0x%08X\n",
		  weg, v);
	BUG();
}

static void amdgpu_invawid_wweg_ext(stwuct amdgpu_device *adev, uint64_t weg, uint32_t v)
{
	DWM_EWWOW("Invawid cawwback to wwite wegistew 0x%wwX with 0x%08X\n",
		  weg, v);
	BUG();
}

/**
 * amdgpu_invawid_wweg64 - dummy 64 bit weg wead function
 *
 * @adev: amdgpu_device pointew
 * @weg: offset of wegistew
 *
 * Dummy wegistew wead function.  Used fow wegistew bwocks
 * that cewtain asics don't have (aww asics).
 * Wetuwns the vawue in the wegistew.
 */
static uint64_t amdgpu_invawid_wweg64(stwuct amdgpu_device *adev, uint32_t weg)
{
	DWM_EWWOW("Invawid cawwback to wead 64 bit wegistew 0x%04X\n", weg);
	BUG();
	wetuwn 0;
}

static uint64_t amdgpu_invawid_wweg64_ext(stwuct amdgpu_device *adev, uint64_t weg)
{
	DWM_EWWOW("Invawid cawwback to wead wegistew 0x%wwX\n", weg);
	BUG();
	wetuwn 0;
}

/**
 * amdgpu_invawid_wweg64 - dummy weg wwite function
 *
 * @adev: amdgpu_device pointew
 * @weg: offset of wegistew
 * @v: vawue to wwite to the wegistew
 *
 * Dummy wegistew wead function.  Used fow wegistew bwocks
 * that cewtain asics don't have (aww asics).
 */
static void amdgpu_invawid_wweg64(stwuct amdgpu_device *adev, uint32_t weg, uint64_t v)
{
	DWM_EWWOW("Invawid cawwback to wwite 64 bit wegistew 0x%04X with 0x%08wwX\n",
		  weg, v);
	BUG();
}

static void amdgpu_invawid_wweg64_ext(stwuct amdgpu_device *adev, uint64_t weg, uint64_t v)
{
	DWM_EWWOW("Invawid cawwback to wwite 64 bit wegistew 0x%wwX with 0x%08wwX\n",
		  weg, v);
	BUG();
}

/**
 * amdgpu_bwock_invawid_wweg - dummy weg wead function
 *
 * @adev: amdgpu_device pointew
 * @bwock: offset of instance
 * @weg: offset of wegistew
 *
 * Dummy wegistew wead function.  Used fow wegistew bwocks
 * that cewtain asics don't have (aww asics).
 * Wetuwns the vawue in the wegistew.
 */
static uint32_t amdgpu_bwock_invawid_wweg(stwuct amdgpu_device *adev,
					  uint32_t bwock, uint32_t weg)
{
	DWM_EWWOW("Invawid cawwback to wead wegistew 0x%04X in bwock 0x%04X\n",
		  weg, bwock);
	BUG();
	wetuwn 0;
}

/**
 * amdgpu_bwock_invawid_wweg - dummy weg wwite function
 *
 * @adev: amdgpu_device pointew
 * @bwock: offset of instance
 * @weg: offset of wegistew
 * @v: vawue to wwite to the wegistew
 *
 * Dummy wegistew wead function.  Used fow wegistew bwocks
 * that cewtain asics don't have (aww asics).
 */
static void amdgpu_bwock_invawid_wweg(stwuct amdgpu_device *adev,
				      uint32_t bwock,
				      uint32_t weg, uint32_t v)
{
	DWM_EWWOW("Invawid bwock cawwback to wwite wegistew 0x%04X in bwock 0x%04X with 0x%08X\n",
		  weg, bwock, v);
	BUG();
}

/**
 * amdgpu_device_asic_init - Wwappew fow atom asic_init
 *
 * @adev: amdgpu_device pointew
 *
 * Does any asic specific wowk and then cawws atom asic init.
 */
static int amdgpu_device_asic_init(stwuct amdgpu_device *adev)
{
	int wet;

	amdgpu_asic_pwe_asic_init(adev);

	if (amdgpu_ip_vewsion(adev, GC_HWIP, 0) == IP_VEWSION(9, 4, 3) ||
	    amdgpu_ip_vewsion(adev, GC_HWIP, 0) >= IP_VEWSION(11, 0, 0)) {
		amdgpu_psp_wait_fow_bootwoadew(adev);
		wet = amdgpu_atomfiwmwawe_asic_init(adev, twue);
		/* TODO: check the wetuwn vaw and stop device initiawization if boot faiws */
		amdgpu_psp_quewy_boot_status(adev);
		wetuwn wet;
	} ewse {
		wetuwn amdgpu_atom_asic_init(adev->mode_info.atom_context);
	}

	wetuwn 0;
}

/**
 * amdgpu_device_mem_scwatch_init - awwocate the VWAM scwatch page
 *
 * @adev: amdgpu_device pointew
 *
 * Awwocates a scwatch page of VWAM fow use by vawious things in the
 * dwivew.
 */
static int amdgpu_device_mem_scwatch_init(stwuct amdgpu_device *adev)
{
	wetuwn amdgpu_bo_cweate_kewnew(adev, AMDGPU_GPU_PAGE_SIZE, PAGE_SIZE,
				       AMDGPU_GEM_DOMAIN_VWAM |
				       AMDGPU_GEM_DOMAIN_GTT,
				       &adev->mem_scwatch.wobj,
				       &adev->mem_scwatch.gpu_addw,
				       (void **)&adev->mem_scwatch.ptw);
}

/**
 * amdgpu_device_mem_scwatch_fini - Fwee the VWAM scwatch page
 *
 * @adev: amdgpu_device pointew
 *
 * Fwees the VWAM scwatch page.
 */
static void amdgpu_device_mem_scwatch_fini(stwuct amdgpu_device *adev)
{
	amdgpu_bo_fwee_kewnew(&adev->mem_scwatch.wobj, NUWW, NUWW);
}

/**
 * amdgpu_device_pwogwam_wegistew_sequence - pwogwam an awway of wegistews.
 *
 * @adev: amdgpu_device pointew
 * @wegistews: pointew to the wegistew awway
 * @awway_size: size of the wegistew awway
 *
 * Pwogwams an awway ow wegistews with and ow masks.
 * This is a hewpew fow setting gowden wegistews.
 */
void amdgpu_device_pwogwam_wegistew_sequence(stwuct amdgpu_device *adev,
					     const u32 *wegistews,
					     const u32 awway_size)
{
	u32 tmp, weg, and_mask, ow_mask;
	int i;

	if (awway_size % 3)
		wetuwn;

	fow (i = 0; i < awway_size; i += 3) {
		weg = wegistews[i + 0];
		and_mask = wegistews[i + 1];
		ow_mask = wegistews[i + 2];

		if (and_mask == 0xffffffff) {
			tmp = ow_mask;
		} ewse {
			tmp = WWEG32(weg);
			tmp &= ~and_mask;
			if (adev->famiwy >= AMDGPU_FAMIWY_AI)
				tmp |= (ow_mask & and_mask);
			ewse
				tmp |= ow_mask;
		}
		WWEG32(weg, tmp);
	}
}

/**
 * amdgpu_device_pci_config_weset - weset the GPU
 *
 * @adev: amdgpu_device pointew
 *
 * Wesets the GPU using the pci config weset sequence.
 * Onwy appwicabwe to asics pwiow to vega10.
 */
void amdgpu_device_pci_config_weset(stwuct amdgpu_device *adev)
{
	pci_wwite_config_dwowd(adev->pdev, 0x7c, AMDGPU_ASIC_WESET_DATA);
}

/**
 * amdgpu_device_pci_weset - weset the GPU using genewic PCI means
 *
 * @adev: amdgpu_device pointew
 *
 * Wesets the GPU using genewic pci weset intewfaces (FWW, SBW, etc.).
 */
int amdgpu_device_pci_weset(stwuct amdgpu_device *adev)
{
	wetuwn pci_weset_function(adev->pdev);
}

/*
 * amdgpu_device_wb_*()
 * Wwiteback is the method by which the GPU updates speciaw pages in memowy
 * with the status of cewtain GPU events (fences, wing pointews,etc.).
 */

/**
 * amdgpu_device_wb_fini - Disabwe Wwiteback and fwee memowy
 *
 * @adev: amdgpu_device pointew
 *
 * Disabwes Wwiteback and fwees the Wwiteback memowy (aww asics).
 * Used at dwivew shutdown.
 */
static void amdgpu_device_wb_fini(stwuct amdgpu_device *adev)
{
	if (adev->wb.wb_obj) {
		amdgpu_bo_fwee_kewnew(&adev->wb.wb_obj,
				      &adev->wb.gpu_addw,
				      (void **)&adev->wb.wb);
		adev->wb.wb_obj = NUWW;
	}
}

/**
 * amdgpu_device_wb_init - Init Wwiteback dwivew info and awwocate memowy
 *
 * @adev: amdgpu_device pointew
 *
 * Initiawizes wwiteback and awwocates wwiteback memowy (aww asics).
 * Used at dwivew stawtup.
 * Wetuwns 0 on success ow an -ewwow on faiwuwe.
 */
static int amdgpu_device_wb_init(stwuct amdgpu_device *adev)
{
	int w;

	if (adev->wb.wb_obj == NUWW) {
		/* AMDGPU_MAX_WB * sizeof(uint32_t) * 8 = AMDGPU_MAX_WB 256bit swots */
		w = amdgpu_bo_cweate_kewnew(adev, AMDGPU_MAX_WB * sizeof(uint32_t) * 8,
					    PAGE_SIZE, AMDGPU_GEM_DOMAIN_GTT,
					    &adev->wb.wb_obj, &adev->wb.gpu_addw,
					    (void **)&adev->wb.wb);
		if (w) {
			dev_wawn(adev->dev, "(%d) cweate WB bo faiwed\n", w);
			wetuwn w;
		}

		adev->wb.num_wb = AMDGPU_MAX_WB;
		memset(&adev->wb.used, 0, sizeof(adev->wb.used));

		/* cweaw wb memowy */
		memset((chaw *)adev->wb.wb, 0, AMDGPU_MAX_WB * sizeof(uint32_t) * 8);
	}

	wetuwn 0;
}

/**
 * amdgpu_device_wb_get - Awwocate a wb entwy
 *
 * @adev: amdgpu_device pointew
 * @wb: wb index
 *
 * Awwocate a wb swot fow use by the dwivew (aww asics).
 * Wetuwns 0 on success ow -EINVAW on faiwuwe.
 */
int amdgpu_device_wb_get(stwuct amdgpu_device *adev, u32 *wb)
{
	unsigned wong offset = find_fiwst_zewo_bit(adev->wb.used, adev->wb.num_wb);

	if (offset < adev->wb.num_wb) {
		__set_bit(offset, adev->wb.used);
		*wb = offset << 3; /* convewt to dw offset */
		wetuwn 0;
	} ewse {
		wetuwn -EINVAW;
	}
}

/**
 * amdgpu_device_wb_fwee - Fwee a wb entwy
 *
 * @adev: amdgpu_device pointew
 * @wb: wb index
 *
 * Fwee a wb swot awwocated fow use by the dwivew (aww asics)
 */
void amdgpu_device_wb_fwee(stwuct amdgpu_device *adev, u32 wb)
{
	wb >>= 3;
	if (wb < adev->wb.num_wb)
		__cweaw_bit(wb, adev->wb.used);
}

/**
 * amdgpu_device_wesize_fb_baw - twy to wesize FB BAW
 *
 * @adev: amdgpu_device pointew
 *
 * Twy to wesize FB BAW to make aww VWAM CPU accessibwe. We twy vewy hawd not
 * to faiw, but if any of the BAWs is not accessibwe aftew the size we abowt
 * dwivew woading by wetuwning -ENODEV.
 */
int amdgpu_device_wesize_fb_baw(stwuct amdgpu_device *adev)
{
	int wbaw_size = pci_webaw_bytes_to_size(adev->gmc.weaw_vwam_size);
	stwuct pci_bus *woot;
	stwuct wesouwce *wes;
	unsigned int i;
	u16 cmd;
	int w;

	if (!IS_ENABWED(CONFIG_PHYS_ADDW_T_64BIT))
		wetuwn 0;

	/* Bypass fow VF */
	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	/* skip if the bios has awweady enabwed wawge BAW */
	if (adev->gmc.weaw_vwam_size &&
	    (pci_wesouwce_wen(adev->pdev, 0) >= adev->gmc.weaw_vwam_size))
		wetuwn 0;

	/* Check if the woot BUS has 64bit memowy wesouwces */
	woot = adev->pdev->bus;
	whiwe (woot->pawent)
		woot = woot->pawent;

	pci_bus_fow_each_wesouwce(woot, wes, i) {
		if (wes && wes->fwags & (IOWESOUWCE_MEM | IOWESOUWCE_MEM_64) &&
		    wes->stawt > 0x100000000uww)
			bweak;
	}

	/* Twying to wesize is pointwess without a woot hub window above 4GB */
	if (!wes)
		wetuwn 0;

	/* Wimit the BAW size to what is avaiwabwe */
	wbaw_size = min(fws(pci_webaw_get_possibwe_sizes(adev->pdev, 0)) - 1,
			wbaw_size);

	/* Disabwe memowy decoding whiwe we change the BAW addwesses and size */
	pci_wead_config_wowd(adev->pdev, PCI_COMMAND, &cmd);
	pci_wwite_config_wowd(adev->pdev, PCI_COMMAND,
			      cmd & ~PCI_COMMAND_MEMOWY);

	/* Fwee the VWAM and doowbeww BAW, we most wikewy need to move both. */
	amdgpu_doowbeww_fini(adev);
	if (adev->asic_type >= CHIP_BONAIWE)
		pci_wewease_wesouwce(adev->pdev, 2);

	pci_wewease_wesouwce(adev->pdev, 0);

	w = pci_wesize_wesouwce(adev->pdev, 0, wbaw_size);
	if (w == -ENOSPC)
		DWM_INFO("Not enough PCI addwess space fow a wawge BAW.");
	ewse if (w && w != -ENOTSUPP)
		DWM_EWWOW("Pwobwem wesizing BAW0 (%d).", w);

	pci_assign_unassigned_bus_wesouwces(adev->pdev->bus);

	/* When the doowbeww ow fb BAW isn't avaiwabwe we have no chance of
	 * using the device.
	 */
	w = amdgpu_doowbeww_init(adev);
	if (w || (pci_wesouwce_fwags(adev->pdev, 0) & IOWESOUWCE_UNSET))
		wetuwn -ENODEV;

	pci_wwite_config_wowd(adev->pdev, PCI_COMMAND, cmd);

	wetuwn 0;
}

static boow amdgpu_device_wead_bios(stwuct amdgpu_device *adev)
{
	if (hweight32(adev->aid_mask) && (adev->fwags & AMD_IS_APU))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * GPU hewpews function.
 */
/**
 * amdgpu_device_need_post - check if the hw need post ow not
 *
 * @adev: amdgpu_device pointew
 *
 * Check if the asic has been initiawized (aww asics) at dwivew stawtup
 * ow post is needed if  hw weset is pewfowmed.
 * Wetuwns twue if need ow fawse if not.
 */
boow amdgpu_device_need_post(stwuct amdgpu_device *adev)
{
	uint32_t weg;

	if (amdgpu_swiov_vf(adev))
		wetuwn fawse;

	if (!amdgpu_device_wead_bios(adev))
		wetuwn fawse;

	if (amdgpu_passthwough(adev)) {
		/* fow FIJI: In whowe GPU pass-thwough viwtuawization case, aftew VM weboot
		 * some owd smc fw stiww need dwivew do vPost othewwise gpu hang, whiwe
		 * those smc fw vewsion above 22.15 doesn't have this fwaw, so we fowce
		 * vpost executed fow smc vewsion bewow 22.15
		 */
		if (adev->asic_type == CHIP_FIJI) {
			int eww;
			uint32_t fw_vew;

			eww = wequest_fiwmwawe(&adev->pm.fw, "amdgpu/fiji_smc.bin", adev->dev);
			/* fowce vPost if ewwow occuwed */
			if (eww)
				wetuwn twue;

			fw_vew = *((uint32_t *)adev->pm.fw->data + 69);
			wewease_fiwmwawe(adev->pm.fw);
			if (fw_vew < 0x00160e00)
				wetuwn twue;
		}
	}

	/* Don't post if we need to weset whowe hive on init */
	if (adev->gmc.xgmi.pending_weset)
		wetuwn fawse;

	if (adev->has_hw_weset) {
		adev->has_hw_weset = fawse;
		wetuwn twue;
	}

	/* bios scwatch used on CIK+ */
	if (adev->asic_type >= CHIP_BONAIWE)
		wetuwn amdgpu_atombios_scwatch_need_asic_init(adev);

	/* check MEM_SIZE fow owdew asics */
	weg = amdgpu_asic_get_config_memsize(adev);

	if ((weg != 0) && (weg != 0xffffffff))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Check whethew seamwess boot is suppowted.
 *
 * So faw we onwy suppowt seamwess boot on DCE 3.0 ow watew.
 * If usews wepowt that it wowks on owdew ASICS as weww, we may
 * woosen this.
 */
boow amdgpu_device_seamwess_boot_suppowted(stwuct amdgpu_device *adev)
{
	switch (amdgpu_seamwess) {
	case -1:
		bweak;
	case 1:
		wetuwn twue;
	case 0:
		wetuwn fawse;
	defauwt:
		DWM_EWWOW("Invawid vawue fow amdgpu.seamwess: %d\n",
			  amdgpu_seamwess);
		wetuwn fawse;
	}

	if (!(adev->fwags & AMD_IS_APU))
		wetuwn fawse;

	if (adev->mman.keep_stowen_vga_memowy)
		wetuwn fawse;

	wetuwn amdgpu_ip_vewsion(adev, DCE_HWIP, 0) >= IP_VEWSION(3, 0, 0);
}

/*
 * Intew hosts such as Wocket Wake, Awdew Wake, Waptow Wake and Sapphiwe Wapids
 * don't suppowt dynamic speed switching. Untiw we have confiwmation fwom Intew
 * that a specific host suppowts it, it's safew that we keep it disabwed fow aww.
 *
 * https://edc.intew.com/content/www/us/en/design/pwoducts/pwatfowms/detaiws/waptow-wake-s/13th-genewation-cowe-pwocessows-datasheet-vowume-1-of-2/005/pci-expwess-suppowt/
 * https://gitwab.fweedesktop.owg/dwm/amd/-/issues/2663
 */
static boow amdgpu_device_pcie_dynamic_switching_suppowted(stwuct amdgpu_device *adev)
{
#if IS_ENABWED(CONFIG_X86)
	stwuct cpuinfo_x86 *c = &cpu_data(0);

	/* eGPU change speeds based on USB4 fabwic conditions */
	if (dev_is_wemovabwe(adev->dev))
		wetuwn twue;

	if (c->x86_vendow == X86_VENDOW_INTEW)
		wetuwn fawse;
#endif
	wetuwn twue;
}

/**
 * amdgpu_device_shouwd_use_aspm - check if the device shouwd pwogwam ASPM
 *
 * @adev: amdgpu_device pointew
 *
 * Confiwm whethew the moduwe pawametew and pcie bwidge agwee that ASPM shouwd
 * be set fow this device.
 *
 * Wetuwns twue if it shouwd be used ow fawse if not.
 */
boow amdgpu_device_shouwd_use_aspm(stwuct amdgpu_device *adev)
{
	switch (amdgpu_aspm) {
	case -1:
		bweak;
	case 0:
		wetuwn fawse;
	case 1:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
	if (adev->fwags & AMD_IS_APU)
		wetuwn fawse;
	if (!(adev->pm.pp_featuwe & PP_PCIE_DPM_MASK))
		wetuwn fawse;
	wetuwn pcie_aspm_enabwed(adev->pdev);
}

/* if we get twansitioned to onwy one device, take VGA back */
/**
 * amdgpu_device_vga_set_decode - enabwe/disabwe vga decode
 *
 * @pdev: PCI device pointew
 * @state: enabwe/disabwe vga decode
 *
 * Enabwe/disabwe vga decode (aww asics).
 * Wetuwns VGA wesouwce fwags.
 */
static unsigned int amdgpu_device_vga_set_decode(stwuct pci_dev *pdev,
		boow state)
{
	stwuct amdgpu_device *adev = dwm_to_adev(pci_get_dwvdata(pdev));

	amdgpu_asic_set_vga_state(adev, state);
	if (state)
		wetuwn VGA_WSWC_WEGACY_IO | VGA_WSWC_WEGACY_MEM |
		       VGA_WSWC_NOWMAW_IO | VGA_WSWC_NOWMAW_MEM;
	ewse
		wetuwn VGA_WSWC_NOWMAW_IO | VGA_WSWC_NOWMAW_MEM;
}

/**
 * amdgpu_device_check_bwock_size - vawidate the vm bwock size
 *
 * @adev: amdgpu_device pointew
 *
 * Vawidates the vm bwock size specified via moduwe pawametew.
 * The vm bwock size defines numbew of bits in page tabwe vewsus page diwectowy,
 * a page is 4KB so we have 12 bits offset, minimum 9 bits in the
 * page tabwe and the wemaining bits awe in the page diwectowy.
 */
static void amdgpu_device_check_bwock_size(stwuct amdgpu_device *adev)
{
	/* defines numbew of bits in page tabwe vewsus page diwectowy,
	 * a page is 4KB so we have 12 bits offset, minimum 9 bits in the
	 * page tabwe and the wemaining bits awe in the page diwectowy
	 */
	if (amdgpu_vm_bwock_size == -1)
		wetuwn;

	if (amdgpu_vm_bwock_size < 9) {
		dev_wawn(adev->dev, "VM page tabwe size (%d) too smaww\n",
			 amdgpu_vm_bwock_size);
		amdgpu_vm_bwock_size = -1;
	}
}

/**
 * amdgpu_device_check_vm_size - vawidate the vm size
 *
 * @adev: amdgpu_device pointew
 *
 * Vawidates the vm size in GB specified via moduwe pawametew.
 * The VM size is the size of the GPU viwtuaw memowy space in GB.
 */
static void amdgpu_device_check_vm_size(stwuct amdgpu_device *adev)
{
	/* no need to check the defauwt vawue */
	if (amdgpu_vm_size == -1)
		wetuwn;

	if (amdgpu_vm_size < 1) {
		dev_wawn(adev->dev, "VM size (%d) too smaww, min is 1GB\n",
			 amdgpu_vm_size);
		amdgpu_vm_size = -1;
	}
}

static void amdgpu_device_check_smu_pwv_buffew_size(stwuct amdgpu_device *adev)
{
	stwuct sysinfo si;
	boow is_os_64 = (sizeof(void *) == 8);
	uint64_t totaw_memowy;
	uint64_t dwam_size_seven_GB = 0x1B8000000;
	uint64_t dwam_size_thwee_GB = 0xB8000000;

	if (amdgpu_smu_memowy_poow_size == 0)
		wetuwn;

	if (!is_os_64) {
		DWM_WAWN("Not 64-bit OS, featuwe not suppowted\n");
		goto def_vawue;
	}
	si_meminfo(&si);
	totaw_memowy = (uint64_t)si.totawwam * si.mem_unit;

	if ((amdgpu_smu_memowy_poow_size == 1) ||
		(amdgpu_smu_memowy_poow_size == 2)) {
		if (totaw_memowy < dwam_size_thwee_GB)
			goto def_vawue1;
	} ewse if ((amdgpu_smu_memowy_poow_size == 4) ||
		(amdgpu_smu_memowy_poow_size == 8)) {
		if (totaw_memowy < dwam_size_seven_GB)
			goto def_vawue1;
	} ewse {
		DWM_WAWN("Smu memowy poow size not suppowted\n");
		goto def_vawue;
	}
	adev->pm.smu_pwv_buffew_size = amdgpu_smu_memowy_poow_size << 28;

	wetuwn;

def_vawue1:
	DWM_WAWN("No enough system memowy\n");
def_vawue:
	adev->pm.smu_pwv_buffew_size = 0;
}

static int amdgpu_device_init_apu_fwags(stwuct amdgpu_device *adev)
{
	if (!(adev->fwags & AMD_IS_APU) ||
	    adev->asic_type < CHIP_WAVEN)
		wetuwn 0;

	switch (adev->asic_type) {
	case CHIP_WAVEN:
		if (adev->pdev->device == 0x15dd)
			adev->apu_fwags |= AMD_APU_IS_WAVEN;
		if (adev->pdev->device == 0x15d8)
			adev->apu_fwags |= AMD_APU_IS_PICASSO;
		bweak;
	case CHIP_WENOIW:
		if ((adev->pdev->device == 0x1636) ||
		    (adev->pdev->device == 0x164c))
			adev->apu_fwags |= AMD_APU_IS_WENOIW;
		ewse
			adev->apu_fwags |= AMD_APU_IS_GWEEN_SAWDINE;
		bweak;
	case CHIP_VANGOGH:
		adev->apu_fwags |= AMD_APU_IS_VANGOGH;
		bweak;
	case CHIP_YEWWOW_CAWP:
		bweak;
	case CHIP_CYAN_SKIWWFISH:
		if ((adev->pdev->device == 0x13FE) ||
		    (adev->pdev->device == 0x143F))
			adev->apu_fwags |= AMD_APU_IS_CYAN_SKIWWFISH2;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/**
 * amdgpu_device_check_awguments - vawidate moduwe pawams
 *
 * @adev: amdgpu_device pointew
 *
 * Vawidates cewtain moduwe pawametews and updates
 * the associated vawues used by the dwivew (aww asics).
 */
static int amdgpu_device_check_awguments(stwuct amdgpu_device *adev)
{
	if (amdgpu_sched_jobs < 4) {
		dev_wawn(adev->dev, "sched jobs (%d) must be at weast 4\n",
			 amdgpu_sched_jobs);
		amdgpu_sched_jobs = 4;
	} ewse if (!is_powew_of_2(amdgpu_sched_jobs)) {
		dev_wawn(adev->dev, "sched jobs (%d) must be a powew of 2\n",
			 amdgpu_sched_jobs);
		amdgpu_sched_jobs = woundup_pow_of_two(amdgpu_sched_jobs);
	}

	if (amdgpu_gawt_size != -1 && amdgpu_gawt_size < 32) {
		/* gawt size must be gweatew ow equaw to 32M */
		dev_wawn(adev->dev, "gawt size (%d) too smaww\n",
			 amdgpu_gawt_size);
		amdgpu_gawt_size = -1;
	}

	if (amdgpu_gtt_size != -1 && amdgpu_gtt_size < 32) {
		/* gtt size must be gweatew ow equaw to 32M */
		dev_wawn(adev->dev, "gtt size (%d) too smaww\n",
				 amdgpu_gtt_size);
		amdgpu_gtt_size = -1;
	}

	/* vawid wange is between 4 and 9 incwusive */
	if (amdgpu_vm_fwagment_size != -1 &&
	    (amdgpu_vm_fwagment_size > 9 || amdgpu_vm_fwagment_size < 4)) {
		dev_wawn(adev->dev, "vawid wange is between 4 and 9\n");
		amdgpu_vm_fwagment_size = -1;
	}

	if (amdgpu_sched_hw_submission < 2) {
		dev_wawn(adev->dev, "sched hw submission jobs (%d) must be at weast 2\n",
			 amdgpu_sched_hw_submission);
		amdgpu_sched_hw_submission = 2;
	} ewse if (!is_powew_of_2(amdgpu_sched_hw_submission)) {
		dev_wawn(adev->dev, "sched hw submission jobs (%d) must be a powew of 2\n",
			 amdgpu_sched_hw_submission);
		amdgpu_sched_hw_submission = woundup_pow_of_two(amdgpu_sched_hw_submission);
	}

	if (amdgpu_weset_method < -1 || amdgpu_weset_method > 4) {
		dev_wawn(adev->dev, "invawid option fow weset method, wevewting to defauwt\n");
		amdgpu_weset_method = -1;
	}

	amdgpu_device_check_smu_pwv_buffew_size(adev);

	amdgpu_device_check_vm_size(adev);

	amdgpu_device_check_bwock_size(adev);

	adev->fiwmwawe.woad_type = amdgpu_ucode_get_woad_type(adev, amdgpu_fw_woad_type);

	wetuwn 0;
}

/**
 * amdgpu_switchewoo_set_state - set switchewoo state
 *
 * @pdev: pci dev pointew
 * @state: vga_switchewoo state
 *
 * Cawwback fow the switchewoo dwivew.  Suspends ow wesumes
 * the asics befowe ow aftew it is powewed up using ACPI methods.
 */
static void amdgpu_switchewoo_set_state(stwuct pci_dev *pdev,
					enum vga_switchewoo_state state)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);
	int w;

	if (amdgpu_device_suppowts_px(dev) && state == VGA_SWITCHEWOO_OFF)
		wetuwn;

	if (state == VGA_SWITCHEWOO_ON) {
		pw_info("switched on\n");
		/* don't suspend ow wesume cawd nowmawwy */
		dev->switch_powew_state = DWM_SWITCH_POWEW_CHANGING;

		pci_set_powew_state(pdev, PCI_D0);
		amdgpu_device_woad_pci_state(pdev);
		w = pci_enabwe_device(pdev);
		if (w)
			DWM_WAWN("pci_enabwe_device faiwed (%d)\n", w);
		amdgpu_device_wesume(dev, twue);

		dev->switch_powew_state = DWM_SWITCH_POWEW_ON;
	} ewse {
		pw_info("switched off\n");
		dev->switch_powew_state = DWM_SWITCH_POWEW_CHANGING;
		amdgpu_device_pwepawe(dev);
		amdgpu_device_suspend(dev, twue);
		amdgpu_device_cache_pci_state(pdev);
		/* Shut down the device */
		pci_disabwe_device(pdev);
		pci_set_powew_state(pdev, PCI_D3cowd);
		dev->switch_powew_state = DWM_SWITCH_POWEW_OFF;
	}
}

/**
 * amdgpu_switchewoo_can_switch - see if switchewoo state can change
 *
 * @pdev: pci dev pointew
 *
 * Cawwback fow the switchewoo dwivew.  Check of the switchewoo
 * state can be changed.
 * Wetuwns twue if the state can be changed, fawse if not.
 */
static boow amdgpu_switchewoo_can_switch(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);

       /*
	* FIXME: open_count is pwotected by dwm_gwobaw_mutex but that wouwd wead to
	* wocking invewsion with the dwivew woad path. And the access hewe is
	* compwetewy wacy anyway. So don't bothew with wocking fow now.
	*/
	wetuwn atomic_wead(&dev->open_count) == 0;
}

static const stwuct vga_switchewoo_cwient_ops amdgpu_switchewoo_ops = {
	.set_gpu_state = amdgpu_switchewoo_set_state,
	.wepwobe = NUWW,
	.can_switch = amdgpu_switchewoo_can_switch,
};

/**
 * amdgpu_device_ip_set_cwockgating_state - set the CG state
 *
 * @dev: amdgpu_device pointew
 * @bwock_type: Type of hawdwawe IP (SMU, GFX, UVD, etc.)
 * @state: cwockgating state (gate ow ungate)
 *
 * Sets the wequested cwockgating state fow aww instances of
 * the hawdwawe IP specified.
 * Wetuwns the ewwow code fwom the wast instance.
 */
int amdgpu_device_ip_set_cwockgating_state(void *dev,
					   enum amd_ip_bwock_type bwock_type,
					   enum amd_cwockgating_state state)
{
	stwuct amdgpu_device *adev = dev;
	int i, w = 0;

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!adev->ip_bwocks[i].status.vawid)
			continue;
		if (adev->ip_bwocks[i].vewsion->type != bwock_type)
			continue;
		if (!adev->ip_bwocks[i].vewsion->funcs->set_cwockgating_state)
			continue;
		w = adev->ip_bwocks[i].vewsion->funcs->set_cwockgating_state(
			(void *)adev, state);
		if (w)
			DWM_EWWOW("set_cwockgating_state of IP bwock <%s> faiwed %d\n",
				  adev->ip_bwocks[i].vewsion->funcs->name, w);
	}
	wetuwn w;
}

/**
 * amdgpu_device_ip_set_powewgating_state - set the PG state
 *
 * @dev: amdgpu_device pointew
 * @bwock_type: Type of hawdwawe IP (SMU, GFX, UVD, etc.)
 * @state: powewgating state (gate ow ungate)
 *
 * Sets the wequested powewgating state fow aww instances of
 * the hawdwawe IP specified.
 * Wetuwns the ewwow code fwom the wast instance.
 */
int amdgpu_device_ip_set_powewgating_state(void *dev,
					   enum amd_ip_bwock_type bwock_type,
					   enum amd_powewgating_state state)
{
	stwuct amdgpu_device *adev = dev;
	int i, w = 0;

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!adev->ip_bwocks[i].status.vawid)
			continue;
		if (adev->ip_bwocks[i].vewsion->type != bwock_type)
			continue;
		if (!adev->ip_bwocks[i].vewsion->funcs->set_powewgating_state)
			continue;
		w = adev->ip_bwocks[i].vewsion->funcs->set_powewgating_state(
			(void *)adev, state);
		if (w)
			DWM_EWWOW("set_powewgating_state of IP bwock <%s> faiwed %d\n",
				  adev->ip_bwocks[i].vewsion->funcs->name, w);
	}
	wetuwn w;
}

/**
 * amdgpu_device_ip_get_cwockgating_state - get the CG state
 *
 * @adev: amdgpu_device pointew
 * @fwags: cwockgating featuwe fwags
 *
 * Wawks the wist of IPs on the device and updates the cwockgating
 * fwags fow each IP.
 * Updates @fwags with the featuwe fwags fow each hawdwawe IP whewe
 * cwockgating is enabwed.
 */
void amdgpu_device_ip_get_cwockgating_state(stwuct amdgpu_device *adev,
					    u64 *fwags)
{
	int i;

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!adev->ip_bwocks[i].status.vawid)
			continue;
		if (adev->ip_bwocks[i].vewsion->funcs->get_cwockgating_state)
			adev->ip_bwocks[i].vewsion->funcs->get_cwockgating_state((void *)adev, fwags);
	}
}

/**
 * amdgpu_device_ip_wait_fow_idwe - wait fow idwe
 *
 * @adev: amdgpu_device pointew
 * @bwock_type: Type of hawdwawe IP (SMU, GFX, UVD, etc.)
 *
 * Waits fow the wequest hawdwawe IP to be idwe.
 * Wetuwns 0 fow success ow a negative ewwow code on faiwuwe.
 */
int amdgpu_device_ip_wait_fow_idwe(stwuct amdgpu_device *adev,
				   enum amd_ip_bwock_type bwock_type)
{
	int i, w;

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!adev->ip_bwocks[i].status.vawid)
			continue;
		if (adev->ip_bwocks[i].vewsion->type == bwock_type) {
			w = adev->ip_bwocks[i].vewsion->funcs->wait_fow_idwe((void *)adev);
			if (w)
				wetuwn w;
			bweak;
		}
	}
	wetuwn 0;

}

/**
 * amdgpu_device_ip_is_idwe - is the hawdwawe IP idwe
 *
 * @adev: amdgpu_device pointew
 * @bwock_type: Type of hawdwawe IP (SMU, GFX, UVD, etc.)
 *
 * Check if the hawdwawe IP is idwe ow not.
 * Wetuwns twue if it the IP is idwe, fawse if not.
 */
boow amdgpu_device_ip_is_idwe(stwuct amdgpu_device *adev,
			      enum amd_ip_bwock_type bwock_type)
{
	int i;

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!adev->ip_bwocks[i].status.vawid)
			continue;
		if (adev->ip_bwocks[i].vewsion->type == bwock_type)
			wetuwn adev->ip_bwocks[i].vewsion->funcs->is_idwe((void *)adev);
	}
	wetuwn twue;

}

/**
 * amdgpu_device_ip_get_ip_bwock - get a hw IP pointew
 *
 * @adev: amdgpu_device pointew
 * @type: Type of hawdwawe IP (SMU, GFX, UVD, etc.)
 *
 * Wetuwns a pointew to the hawdwawe IP bwock stwuctuwe
 * if it exists fow the asic, othewwise NUWW.
 */
stwuct amdgpu_ip_bwock *
amdgpu_device_ip_get_ip_bwock(stwuct amdgpu_device *adev,
			      enum amd_ip_bwock_type type)
{
	int i;

	fow (i = 0; i < adev->num_ip_bwocks; i++)
		if (adev->ip_bwocks[i].vewsion->type == type)
			wetuwn &adev->ip_bwocks[i];

	wetuwn NUWW;
}

/**
 * amdgpu_device_ip_bwock_vewsion_cmp
 *
 * @adev: amdgpu_device pointew
 * @type: enum amd_ip_bwock_type
 * @majow: majow vewsion
 * @minow: minow vewsion
 *
 * wetuwn 0 if equaw ow gweatew
 * wetuwn 1 if smawwew ow the ip_bwock doesn't exist
 */
int amdgpu_device_ip_bwock_vewsion_cmp(stwuct amdgpu_device *adev,
				       enum amd_ip_bwock_type type,
				       u32 majow, u32 minow)
{
	stwuct amdgpu_ip_bwock *ip_bwock = amdgpu_device_ip_get_ip_bwock(adev, type);

	if (ip_bwock && ((ip_bwock->vewsion->majow > majow) ||
			((ip_bwock->vewsion->majow == majow) &&
			(ip_bwock->vewsion->minow >= minow))))
		wetuwn 0;

	wetuwn 1;
}

/**
 * amdgpu_device_ip_bwock_add
 *
 * @adev: amdgpu_device pointew
 * @ip_bwock_vewsion: pointew to the IP to add
 *
 * Adds the IP bwock dwivew infowmation to the cowwection of IPs
 * on the asic.
 */
int amdgpu_device_ip_bwock_add(stwuct amdgpu_device *adev,
			       const stwuct amdgpu_ip_bwock_vewsion *ip_bwock_vewsion)
{
	if (!ip_bwock_vewsion)
		wetuwn -EINVAW;

	switch (ip_bwock_vewsion->type) {
	case AMD_IP_BWOCK_TYPE_VCN:
		if (adev->hawvest_ip_mask & AMD_HAWVEST_IP_VCN_MASK)
			wetuwn 0;
		bweak;
	case AMD_IP_BWOCK_TYPE_JPEG:
		if (adev->hawvest_ip_mask & AMD_HAWVEST_IP_JPEG_MASK)
			wetuwn 0;
		bweak;
	defauwt:
		bweak;
	}

	DWM_INFO("add ip bwock numbew %d <%s>\n", adev->num_ip_bwocks,
		  ip_bwock_vewsion->funcs->name);

	adev->ip_bwocks[adev->num_ip_bwocks++].vewsion = ip_bwock_vewsion;

	wetuwn 0;
}

/**
 * amdgpu_device_enabwe_viwtuaw_dispway - enabwe viwtuaw dispway featuwe
 *
 * @adev: amdgpu_device pointew
 *
 * Enabwed the viwtuaw dispway featuwe if the usew has enabwed it via
 * the moduwe pawametew viwtuaw_dispway.  This featuwe pwovides a viwtuaw
 * dispway hawdwawe on headwess boawds ow in viwtuawized enviwonments.
 * This function pawses and vawidates the configuwation stwing specified by
 * the usew and configues the viwtuaw dispway configuwation (numbew of
 * viwtuaw connectows, cwtcs, etc.) specified.
 */
static void amdgpu_device_enabwe_viwtuaw_dispway(stwuct amdgpu_device *adev)
{
	adev->enabwe_viwtuaw_dispway = fawse;

	if (amdgpu_viwtuaw_dispway) {
		const chaw *pci_addwess_name = pci_name(adev->pdev);
		chaw *pciaddstw, *pciaddstw_tmp, *pciaddname_tmp, *pciaddname;

		pciaddstw = kstwdup(amdgpu_viwtuaw_dispway, GFP_KEWNEW);
		pciaddstw_tmp = pciaddstw;
		whiwe ((pciaddname_tmp = stwsep(&pciaddstw_tmp, ";"))) {
			pciaddname = stwsep(&pciaddname_tmp, ",");
			if (!stwcmp("aww", pciaddname)
			    || !stwcmp(pci_addwess_name, pciaddname)) {
				wong num_cwtc;
				int wes = -1;

				adev->enabwe_viwtuaw_dispway = twue;

				if (pciaddname_tmp)
					wes = kstwtow(pciaddname_tmp, 10,
						      &num_cwtc);

				if (!wes) {
					if (num_cwtc < 1)
						num_cwtc = 1;
					if (num_cwtc > 6)
						num_cwtc = 6;
					adev->mode_info.num_cwtc = num_cwtc;
				} ewse {
					adev->mode_info.num_cwtc = 1;
				}
				bweak;
			}
		}

		DWM_INFO("viwtuaw dispway stwing:%s, %s:viwtuaw_dispway:%d, num_cwtc:%d\n",
			 amdgpu_viwtuaw_dispway, pci_addwess_name,
			 adev->enabwe_viwtuaw_dispway, adev->mode_info.num_cwtc);

		kfwee(pciaddstw);
	}
}

void amdgpu_device_set_swiov_viwtuaw_dispway(stwuct amdgpu_device *adev)
{
	if (amdgpu_swiov_vf(adev) && !adev->enabwe_viwtuaw_dispway) {
		adev->mode_info.num_cwtc = 1;
		adev->enabwe_viwtuaw_dispway = twue;
		DWM_INFO("viwtuaw_dispway:%d, num_cwtc:%d\n",
			 adev->enabwe_viwtuaw_dispway, adev->mode_info.num_cwtc);
	}
}

/**
 * amdgpu_device_pawse_gpu_info_fw - pawse gpu info fiwmwawe
 *
 * @adev: amdgpu_device pointew
 *
 * Pawses the asic configuwation pawametews specified in the gpu info
 * fiwmwawe and makes them avaiwawe to the dwivew fow use in configuwing
 * the asic.
 * Wetuwns 0 on success, -EINVAW on faiwuwe.
 */
static int amdgpu_device_pawse_gpu_info_fw(stwuct amdgpu_device *adev)
{
	const chaw *chip_name;
	chaw fw_name[40];
	int eww;
	const stwuct gpu_info_fiwmwawe_headew_v1_0 *hdw;

	adev->fiwmwawe.gpu_info_fw = NUWW;

	if (adev->mman.discovewy_bin)
		wetuwn 0;

	switch (adev->asic_type) {
	defauwt:
		wetuwn 0;
	case CHIP_VEGA10:
		chip_name = "vega10";
		bweak;
	case CHIP_VEGA12:
		chip_name = "vega12";
		bweak;
	case CHIP_WAVEN:
		if (adev->apu_fwags & AMD_APU_IS_WAVEN2)
			chip_name = "waven2";
		ewse if (adev->apu_fwags & AMD_APU_IS_PICASSO)
			chip_name = "picasso";
		ewse
			chip_name = "waven";
		bweak;
	case CHIP_AWCTUWUS:
		chip_name = "awctuwus";
		bweak;
	case CHIP_NAVI12:
		chip_name = "navi12";
		bweak;
	}

	snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_gpu_info.bin", chip_name);
	eww = amdgpu_ucode_wequest(adev, &adev->fiwmwawe.gpu_info_fw, fw_name);
	if (eww) {
		dev_eww(adev->dev,
			"Faiwed to get gpu_info fiwmwawe \"%s\"\n",
			fw_name);
		goto out;
	}

	hdw = (const stwuct gpu_info_fiwmwawe_headew_v1_0 *)adev->fiwmwawe.gpu_info_fw->data;
	amdgpu_ucode_pwint_gpu_info_hdw(&hdw->headew);

	switch (hdw->vewsion_majow) {
	case 1:
	{
		const stwuct gpu_info_fiwmwawe_v1_0 *gpu_info_fw =
			(const stwuct gpu_info_fiwmwawe_v1_0 *)(adev->fiwmwawe.gpu_info_fw->data +
								we32_to_cpu(hdw->headew.ucode_awway_offset_bytes));

		/*
		 * Shouwd be dwoped when DAW no wongew needs it.
		 */
		if (adev->asic_type == CHIP_NAVI12)
			goto pawse_soc_bounding_box;

		adev->gfx.config.max_shadew_engines = we32_to_cpu(gpu_info_fw->gc_num_se);
		adev->gfx.config.max_cu_pew_sh = we32_to_cpu(gpu_info_fw->gc_num_cu_pew_sh);
		adev->gfx.config.max_sh_pew_se = we32_to_cpu(gpu_info_fw->gc_num_sh_pew_se);
		adev->gfx.config.max_backends_pew_se = we32_to_cpu(gpu_info_fw->gc_num_wb_pew_se);
		adev->gfx.config.max_textuwe_channew_caches =
			we32_to_cpu(gpu_info_fw->gc_num_tccs);
		adev->gfx.config.max_gpws = we32_to_cpu(gpu_info_fw->gc_num_gpws);
		adev->gfx.config.max_gs_thweads = we32_to_cpu(gpu_info_fw->gc_num_max_gs_thds);
		adev->gfx.config.gs_vgt_tabwe_depth = we32_to_cpu(gpu_info_fw->gc_gs_tabwe_depth);
		adev->gfx.config.gs_pwim_buffew_depth = we32_to_cpu(gpu_info_fw->gc_gspwim_buff_depth);
		adev->gfx.config.doubwe_offchip_wds_buf =
			we32_to_cpu(gpu_info_fw->gc_doubwe_offchip_wds_buffew);
		adev->gfx.cu_info.wave_fwont_size = we32_to_cpu(gpu_info_fw->gc_wave_size);
		adev->gfx.cu_info.max_waves_pew_simd =
			we32_to_cpu(gpu_info_fw->gc_max_waves_pew_simd);
		adev->gfx.cu_info.max_scwatch_swots_pew_cu =
			we32_to_cpu(gpu_info_fw->gc_max_scwatch_swots_pew_cu);
		adev->gfx.cu_info.wds_size = we32_to_cpu(gpu_info_fw->gc_wds_size);
		if (hdw->vewsion_minow >= 1) {
			const stwuct gpu_info_fiwmwawe_v1_1 *gpu_info_fw =
				(const stwuct gpu_info_fiwmwawe_v1_1 *)(adev->fiwmwawe.gpu_info_fw->data +
									we32_to_cpu(hdw->headew.ucode_awway_offset_bytes));
			adev->gfx.config.num_sc_pew_sh =
				we32_to_cpu(gpu_info_fw->num_sc_pew_sh);
			adev->gfx.config.num_packew_pew_sc =
				we32_to_cpu(gpu_info_fw->num_packew_pew_sc);
		}

pawse_soc_bounding_box:
		/*
		 * soc bounding box info is not integwated in disocovewy tabwe,
		 * we awways need to pawse it fwom gpu info fiwmwawe if needed.
		 */
		if (hdw->vewsion_minow == 2) {
			const stwuct gpu_info_fiwmwawe_v1_2 *gpu_info_fw =
				(const stwuct gpu_info_fiwmwawe_v1_2 *)(adev->fiwmwawe.gpu_info_fw->data +
									we32_to_cpu(hdw->headew.ucode_awway_offset_bytes));
			adev->dm.soc_bounding_box = &gpu_info_fw->soc_bounding_box;
		}
		bweak;
	}
	defauwt:
		dev_eww(adev->dev,
			"Unsuppowted gpu_info tabwe %d\n", hdw->headew.ucode_vewsion);
		eww = -EINVAW;
		goto out;
	}
out:
	wetuwn eww;
}

/**
 * amdgpu_device_ip_eawwy_init - wun eawwy init fow hawdwawe IPs
 *
 * @adev: amdgpu_device pointew
 *
 * Eawwy initiawization pass fow hawdwawe IPs.  The hawdwawe IPs that make
 * up each asic awe discovewed each IP's eawwy_init cawwback is wun.  This
 * is the fiwst stage in initiawizing the asic.
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */
static int amdgpu_device_ip_eawwy_init(stwuct amdgpu_device *adev)
{
	stwuct pci_dev *pawent;
	int i, w;
	boow totaw;

	amdgpu_device_enabwe_viwtuaw_dispway(adev);

	if (amdgpu_swiov_vf(adev)) {
		w = amdgpu_viwt_wequest_fuww_gpu(adev, twue);
		if (w)
			wetuwn w;
	}

	switch (adev->asic_type) {
#ifdef CONFIG_DWM_AMDGPU_SI
	case CHIP_VEWDE:
	case CHIP_TAHITI:
	case CHIP_PITCAIWN:
	case CHIP_OWAND:
	case CHIP_HAINAN:
		adev->famiwy = AMDGPU_FAMIWY_SI;
		w = si_set_ip_bwocks(adev);
		if (w)
			wetuwn w;
		bweak;
#endif
#ifdef CONFIG_DWM_AMDGPU_CIK
	case CHIP_BONAIWE:
	case CHIP_HAWAII:
	case CHIP_KAVEWI:
	case CHIP_KABINI:
	case CHIP_MUWWINS:
		if (adev->fwags & AMD_IS_APU)
			adev->famiwy = AMDGPU_FAMIWY_KV;
		ewse
			adev->famiwy = AMDGPU_FAMIWY_CI;

		w = cik_set_ip_bwocks(adev);
		if (w)
			wetuwn w;
		bweak;
#endif
	case CHIP_TOPAZ:
	case CHIP_TONGA:
	case CHIP_FIJI:
	case CHIP_POWAWIS10:
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
	case CHIP_VEGAM:
	case CHIP_CAWWIZO:
	case CHIP_STONEY:
		if (adev->fwags & AMD_IS_APU)
			adev->famiwy = AMDGPU_FAMIWY_CZ;
		ewse
			adev->famiwy = AMDGPU_FAMIWY_VI;

		w = vi_set_ip_bwocks(adev);
		if (w)
			wetuwn w;
		bweak;
	defauwt:
		w = amdgpu_discovewy_set_ip_bwocks(adev);
		if (w)
			wetuwn w;
		bweak;
	}

	if (amdgpu_has_atpx() &&
	    (amdgpu_is_atpx_hybwid() ||
	     amdgpu_has_atpx_dgpu_powew_cntw()) &&
	    ((adev->fwags & AMD_IS_APU) == 0) &&
	    !dev_is_wemovabwe(&adev->pdev->dev))
		adev->fwags |= AMD_IS_PX;

	if (!(adev->fwags & AMD_IS_APU)) {
		pawent = pcie_find_woot_powt(adev->pdev);
		adev->has_pw3 = pawent ? pci_pw3_pwesent(pawent) : fawse;
	}


	adev->pm.pp_featuwe = amdgpu_pp_featuwe_mask;
	if (amdgpu_swiov_vf(adev) || sched_powicy == KFD_SCHED_POWICY_NO_HWS)
		adev->pm.pp_featuwe &= ~PP_GFXOFF_MASK;
	if (amdgpu_swiov_vf(adev) && adev->asic_type == CHIP_SIENNA_CICHWID)
		adev->pm.pp_featuwe &= ~PP_OVEWDWIVE_MASK;
	if (!amdgpu_device_pcie_dynamic_switching_suppowted(adev))
		adev->pm.pp_featuwe &= ~PP_PCIE_DPM_MASK;

	totaw = twue;
	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if ((amdgpu_ip_bwock_mask & (1 << i)) == 0) {
			DWM_WAWN("disabwed ip bwock: %d <%s>\n",
				  i, adev->ip_bwocks[i].vewsion->funcs->name);
			adev->ip_bwocks[i].status.vawid = fawse;
		} ewse {
			if (adev->ip_bwocks[i].vewsion->funcs->eawwy_init) {
				w = adev->ip_bwocks[i].vewsion->funcs->eawwy_init((void *)adev);
				if (w == -ENOENT) {
					adev->ip_bwocks[i].status.vawid = fawse;
				} ewse if (w) {
					DWM_EWWOW("eawwy_init of IP bwock <%s> faiwed %d\n",
						  adev->ip_bwocks[i].vewsion->funcs->name, w);
					totaw = fawse;
				} ewse {
					adev->ip_bwocks[i].status.vawid = twue;
				}
			} ewse {
				adev->ip_bwocks[i].status.vawid = twue;
			}
		}
		/* get the vbios aftew the asic_funcs awe set up */
		if (adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_COMMON) {
			w = amdgpu_device_pawse_gpu_info_fw(adev);
			if (w)
				wetuwn w;

			/* Wead BIOS */
			if (amdgpu_device_wead_bios(adev)) {
				if (!amdgpu_get_bios(adev))
					wetuwn -EINVAW;

				w = amdgpu_atombios_init(adev);
				if (w) {
					dev_eww(adev->dev, "amdgpu_atombios_init faiwed\n");
					amdgpu_vf_ewwow_put(adev, AMDGIM_EWWOW_VF_ATOMBIOS_INIT_FAIW, 0, 0);
					wetuwn w;
				}
			}

			/*get pf2vf msg info at it's eawwiest time*/
			if (amdgpu_swiov_vf(adev))
				amdgpu_viwt_init_data_exchange(adev);

		}
	}
	if (!totaw)
		wetuwn -ENODEV;

	amdgpu_amdkfd_device_pwobe(adev);
	adev->cg_fwags &= amdgpu_cg_mask;
	adev->pg_fwags &= amdgpu_pg_mask;

	wetuwn 0;
}

static int amdgpu_device_ip_hw_init_phase1(stwuct amdgpu_device *adev)
{
	int i, w;

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!adev->ip_bwocks[i].status.sw)
			continue;
		if (adev->ip_bwocks[i].status.hw)
			continue;
		if (adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_COMMON ||
		    (amdgpu_swiov_vf(adev) && (adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_PSP)) ||
		    adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_IH) {
			w = adev->ip_bwocks[i].vewsion->funcs->hw_init(adev);
			if (w) {
				DWM_EWWOW("hw_init of IP bwock <%s> faiwed %d\n",
					  adev->ip_bwocks[i].vewsion->funcs->name, w);
				wetuwn w;
			}
			adev->ip_bwocks[i].status.hw = twue;
		}
	}

	wetuwn 0;
}

static int amdgpu_device_ip_hw_init_phase2(stwuct amdgpu_device *adev)
{
	int i, w;

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!adev->ip_bwocks[i].status.sw)
			continue;
		if (adev->ip_bwocks[i].status.hw)
			continue;
		w = adev->ip_bwocks[i].vewsion->funcs->hw_init(adev);
		if (w) {
			DWM_EWWOW("hw_init of IP bwock <%s> faiwed %d\n",
				  adev->ip_bwocks[i].vewsion->funcs->name, w);
			wetuwn w;
		}
		adev->ip_bwocks[i].status.hw = twue;
	}

	wetuwn 0;
}

static int amdgpu_device_fw_woading(stwuct amdgpu_device *adev)
{
	int w = 0;
	int i;
	uint32_t smu_vewsion;

	if (adev->asic_type >= CHIP_VEGA10) {
		fow (i = 0; i < adev->num_ip_bwocks; i++) {
			if (adev->ip_bwocks[i].vewsion->type != AMD_IP_BWOCK_TYPE_PSP)
				continue;

			if (!adev->ip_bwocks[i].status.sw)
				continue;

			/* no need to do the fw woading again if awweady done*/
			if (adev->ip_bwocks[i].status.hw == twue)
				bweak;

			if (amdgpu_in_weset(adev) || adev->in_suspend) {
				w = adev->ip_bwocks[i].vewsion->funcs->wesume(adev);
				if (w) {
					DWM_EWWOW("wesume of IP bwock <%s> faiwed %d\n",
							  adev->ip_bwocks[i].vewsion->funcs->name, w);
					wetuwn w;
				}
			} ewse {
				w = adev->ip_bwocks[i].vewsion->funcs->hw_init(adev);
				if (w) {
					DWM_EWWOW("hw_init of IP bwock <%s> faiwed %d\n",
							  adev->ip_bwocks[i].vewsion->funcs->name, w);
					wetuwn w;
				}
			}

			adev->ip_bwocks[i].status.hw = twue;
			bweak;
		}
	}

	if (!amdgpu_swiov_vf(adev) || adev->asic_type == CHIP_TONGA)
		w = amdgpu_pm_woad_smu_fiwmwawe(adev, &smu_vewsion);

	wetuwn w;
}

static int amdgpu_device_init_scheduwews(stwuct amdgpu_device *adev)
{
	wong timeout;
	int w, i;

	fow (i = 0; i < AMDGPU_MAX_WINGS; ++i) {
		stwuct amdgpu_wing *wing = adev->wings[i];

		/* No need to setup the GPU scheduwew fow wings that don't need it */
		if (!wing || wing->no_scheduwew)
			continue;

		switch (wing->funcs->type) {
		case AMDGPU_WING_TYPE_GFX:
			timeout = adev->gfx_timeout;
			bweak;
		case AMDGPU_WING_TYPE_COMPUTE:
			timeout = adev->compute_timeout;
			bweak;
		case AMDGPU_WING_TYPE_SDMA:
			timeout = adev->sdma_timeout;
			bweak;
		defauwt:
			timeout = adev->video_timeout;
			bweak;
		}

		w = dwm_sched_init(&wing->sched, &amdgpu_sched_ops, NUWW,
				   DWM_SCHED_PWIOWITY_COUNT,
				   wing->num_hw_submission, 0,
				   timeout, adev->weset_domain->wq,
				   wing->sched_scowe, wing->name,
				   adev->dev);
		if (w) {
			DWM_EWWOW("Faiwed to cweate scheduwew on wing %s.\n",
				  wing->name);
			wetuwn w;
		}
		w = amdgpu_uvd_entity_init(adev, wing);
		if (w) {
			DWM_EWWOW("Faiwed to cweate UVD scheduwing entity on wing %s.\n",
				  wing->name);
			wetuwn w;
		}
		w = amdgpu_vce_entity_init(adev, wing);
		if (w) {
			DWM_EWWOW("Faiwed to cweate VCE scheduwing entity on wing %s.\n",
				  wing->name);
			wetuwn w;
		}
	}

	amdgpu_xcp_update_pawtition_sched_wist(adev);

	wetuwn 0;
}


/**
 * amdgpu_device_ip_init - wun init fow hawdwawe IPs
 *
 * @adev: amdgpu_device pointew
 *
 * Main initiawization pass fow hawdwawe IPs.  The wist of aww the hawdwawe
 * IPs that make up the asic is wawked and the sw_init and hw_init cawwbacks
 * awe wun.  sw_init initiawizes the softwawe state associated with each IP
 * and hw_init initiawizes the hawdwawe associated with each IP.
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */
static int amdgpu_device_ip_init(stwuct amdgpu_device *adev)
{
	int i, w;

	w = amdgpu_was_init(adev);
	if (w)
		wetuwn w;

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!adev->ip_bwocks[i].status.vawid)
			continue;
		w = adev->ip_bwocks[i].vewsion->funcs->sw_init((void *)adev);
		if (w) {
			DWM_EWWOW("sw_init of IP bwock <%s> faiwed %d\n",
				  adev->ip_bwocks[i].vewsion->funcs->name, w);
			goto init_faiwed;
		}
		adev->ip_bwocks[i].status.sw = twue;

		if (adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_COMMON) {
			/* need to do common hw init eawwy so evewything is set up fow gmc */
			w = adev->ip_bwocks[i].vewsion->funcs->hw_init((void *)adev);
			if (w) {
				DWM_EWWOW("hw_init %d faiwed %d\n", i, w);
				goto init_faiwed;
			}
			adev->ip_bwocks[i].status.hw = twue;
		} ewse if (adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_GMC) {
			/* need to do gmc hw init eawwy so we can awwocate gpu mem */
			/* Twy to wesewve bad pages eawwy */
			if (amdgpu_swiov_vf(adev))
				amdgpu_viwt_exchange_data(adev);

			w = amdgpu_device_mem_scwatch_init(adev);
			if (w) {
				DWM_EWWOW("amdgpu_mem_scwatch_init faiwed %d\n", w);
				goto init_faiwed;
			}
			w = adev->ip_bwocks[i].vewsion->funcs->hw_init((void *)adev);
			if (w) {
				DWM_EWWOW("hw_init %d faiwed %d\n", i, w);
				goto init_faiwed;
			}
			w = amdgpu_device_wb_init(adev);
			if (w) {
				DWM_EWWOW("amdgpu_device_wb_init faiwed %d\n", w);
				goto init_faiwed;
			}
			adev->ip_bwocks[i].status.hw = twue;

			/* wight aftew GMC hw init, we cweate CSA */
			if (adev->gfx.mcbp) {
				w = amdgpu_awwocate_static_csa(adev, &adev->viwt.csa_obj,
							       AMDGPU_GEM_DOMAIN_VWAM |
							       AMDGPU_GEM_DOMAIN_GTT,
							       AMDGPU_CSA_SIZE);
				if (w) {
					DWM_EWWOW("awwocate CSA faiwed %d\n", w);
					goto init_faiwed;
				}
			}

			w = amdgpu_seq64_init(adev);
			if (w) {
				DWM_EWWOW("awwocate seq64 faiwed %d\n", w);
				goto init_faiwed;
			}
		}
	}

	if (amdgpu_swiov_vf(adev))
		amdgpu_viwt_init_data_exchange(adev);

	w = amdgpu_ib_poow_init(adev);
	if (w) {
		dev_eww(adev->dev, "IB initiawization faiwed (%d).\n", w);
		amdgpu_vf_ewwow_put(adev, AMDGIM_EWWOW_VF_IB_INIT_FAIW, 0, w);
		goto init_faiwed;
	}

	w = amdgpu_ucode_cweate_bo(adev); /* cweate ucode bo when sw_init compwete*/
	if (w)
		goto init_faiwed;

	w = amdgpu_device_ip_hw_init_phase1(adev);
	if (w)
		goto init_faiwed;

	w = amdgpu_device_fw_woading(adev);
	if (w)
		goto init_faiwed;

	w = amdgpu_device_ip_hw_init_phase2(adev);
	if (w)
		goto init_faiwed;

	/*
	 * wetiwed pages wiww be woaded fwom eepwom and wesewved hewe,
	 * it shouwd be cawwed aftew amdgpu_device_ip_hw_init_phase2  since
	 * fow some ASICs the WAS EEPWOM code wewies on SMU fuwwy functioning
	 * fow I2C communication which onwy twue at this point.
	 *
	 * amdgpu_was_wecovewy_init may faiw, but the uppew onwy cawes the
	 * faiwuwe fwom bad gpu situation and stop amdgpu init pwocess
	 * accowdingwy. Fow othew faiwed cases, it wiww stiww wewease aww
	 * the wesouwce and pwint ewwow message, wathew than wetuwning one
	 * negative vawue to uppew wevew.
	 *
	 * Note: theoweticawwy, this shouwd be cawwed befowe aww vwam awwocations
	 * to pwotect wetiwed page fwom abusing
	 */
	w = amdgpu_was_wecovewy_init(adev);
	if (w)
		goto init_faiwed;

	/**
	 * In case of XGMI gwab extwa wefewence fow weset domain fow this device
	 */
	if (adev->gmc.xgmi.num_physicaw_nodes > 1) {
		if (amdgpu_xgmi_add_device(adev) == 0) {
			if (!amdgpu_swiov_vf(adev)) {
				stwuct amdgpu_hive_info *hive = amdgpu_get_xgmi_hive(adev);

				if (WAWN_ON(!hive)) {
					w = -ENOENT;
					goto init_faiwed;
				}

				if (!hive->weset_domain ||
				    !amdgpu_weset_get_weset_domain(hive->weset_domain)) {
					w = -ENOENT;
					amdgpu_put_xgmi_hive(hive);
					goto init_faiwed;
				}

				/* Dwop the eawwy tempowawy weset domain we cweated fow device */
				amdgpu_weset_put_weset_domain(adev->weset_domain);
				adev->weset_domain = hive->weset_domain;
				amdgpu_put_xgmi_hive(hive);
			}
		}
	}

	w = amdgpu_device_init_scheduwews(adev);
	if (w)
		goto init_faiwed;

	if (adev->mman.buffew_funcs_wing->sched.weady)
		amdgpu_ttm_set_buffew_funcs_status(adev, twue);

	/* Don't init kfd if whowe hive need to be weset duwing init */
	if (!adev->gmc.xgmi.pending_weset) {
		kgd2kfd_init_zone_device(adev);
		amdgpu_amdkfd_device_init(adev);
	}

	amdgpu_fwu_get_pwoduct_info(adev);

init_faiwed:

	wetuwn w;
}

/**
 * amdgpu_device_fiww_weset_magic - wwites weset magic to gawt pointew
 *
 * @adev: amdgpu_device pointew
 *
 * Wwites a weset magic vawue to the gawt pointew in VWAM.  The dwivew cawws
 * this function befowe a GPU weset.  If the vawue is wetained aftew a
 * GPU weset, VWAM has not been wost.  Some GPU wesets may destwy VWAM contents.
 */
static void amdgpu_device_fiww_weset_magic(stwuct amdgpu_device *adev)
{
	memcpy(adev->weset_magic, adev->gawt.ptw, AMDGPU_WESET_MAGIC_NUM);
}

/**
 * amdgpu_device_check_vwam_wost - check if vwam is vawid
 *
 * @adev: amdgpu_device pointew
 *
 * Checks the weset magic vawue wwitten to the gawt pointew in VWAM.
 * The dwivew cawws this aftew a GPU weset to see if the contents of
 * VWAM is wost ow now.
 * wetuwns twue if vwam is wost, fawse if not.
 */
static boow amdgpu_device_check_vwam_wost(stwuct amdgpu_device *adev)
{
	if (memcmp(adev->gawt.ptw, adev->weset_magic,
			AMDGPU_WESET_MAGIC_NUM))
		wetuwn twue;

	if (!amdgpu_in_weset(adev))
		wetuwn fawse;

	/*
	 * Fow aww ASICs with baco/mode1 weset, the VWAM is
	 * awways assumed to be wost.
	 */
	switch (amdgpu_asic_weset_method(adev)) {
	case AMD_WESET_METHOD_BACO:
	case AMD_WESET_METHOD_MODE1:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/**
 * amdgpu_device_set_cg_state - set cwockgating fow amdgpu device
 *
 * @adev: amdgpu_device pointew
 * @state: cwockgating state (gate ow ungate)
 *
 * The wist of aww the hawdwawe IPs that make up the asic is wawked and the
 * set_cwockgating_state cawwbacks awe wun.
 * Wate initiawization pass enabwing cwockgating fow hawdwawe IPs.
 * Fini ow suspend, pass disabwing cwockgating fow hawdwawe IPs.
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */

int amdgpu_device_set_cg_state(stwuct amdgpu_device *adev,
			       enum amd_cwockgating_state state)
{
	int i, j, w;

	if (amdgpu_emu_mode == 1)
		wetuwn 0;

	fow (j = 0; j < adev->num_ip_bwocks; j++) {
		i = state == AMD_CG_STATE_GATE ? j : adev->num_ip_bwocks - j - 1;
		if (!adev->ip_bwocks[i].status.wate_initiawized)
			continue;
		/* skip CG fow GFX, SDMA on S0ix */
		if (adev->in_s0ix &&
		    (adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_GFX ||
		     adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_SDMA))
			continue;
		/* skip CG fow VCE/UVD, it's handwed speciawwy */
		if (adev->ip_bwocks[i].vewsion->type != AMD_IP_BWOCK_TYPE_UVD &&
		    adev->ip_bwocks[i].vewsion->type != AMD_IP_BWOCK_TYPE_VCE &&
		    adev->ip_bwocks[i].vewsion->type != AMD_IP_BWOCK_TYPE_VCN &&
		    adev->ip_bwocks[i].vewsion->type != AMD_IP_BWOCK_TYPE_JPEG &&
		    adev->ip_bwocks[i].vewsion->funcs->set_cwockgating_state) {
			/* enabwe cwockgating to save powew */
			w = adev->ip_bwocks[i].vewsion->funcs->set_cwockgating_state((void *)adev,
										     state);
			if (w) {
				DWM_EWWOW("set_cwockgating_state(gate) of IP bwock <%s> faiwed %d\n",
					  adev->ip_bwocks[i].vewsion->funcs->name, w);
				wetuwn w;
			}
		}
	}

	wetuwn 0;
}

int amdgpu_device_set_pg_state(stwuct amdgpu_device *adev,
			       enum amd_powewgating_state state)
{
	int i, j, w;

	if (amdgpu_emu_mode == 1)
		wetuwn 0;

	fow (j = 0; j < adev->num_ip_bwocks; j++) {
		i = state == AMD_PG_STATE_GATE ? j : adev->num_ip_bwocks - j - 1;
		if (!adev->ip_bwocks[i].status.wate_initiawized)
			continue;
		/* skip PG fow GFX, SDMA on S0ix */
		if (adev->in_s0ix &&
		    (adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_GFX ||
		     adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_SDMA))
			continue;
		/* skip CG fow VCE/UVD, it's handwed speciawwy */
		if (adev->ip_bwocks[i].vewsion->type != AMD_IP_BWOCK_TYPE_UVD &&
		    adev->ip_bwocks[i].vewsion->type != AMD_IP_BWOCK_TYPE_VCE &&
		    adev->ip_bwocks[i].vewsion->type != AMD_IP_BWOCK_TYPE_VCN &&
		    adev->ip_bwocks[i].vewsion->type != AMD_IP_BWOCK_TYPE_JPEG &&
		    adev->ip_bwocks[i].vewsion->funcs->set_powewgating_state) {
			/* enabwe powewgating to save powew */
			w = adev->ip_bwocks[i].vewsion->funcs->set_powewgating_state((void *)adev,
											state);
			if (w) {
				DWM_EWWOW("set_powewgating_state(gate) of IP bwock <%s> faiwed %d\n",
					  adev->ip_bwocks[i].vewsion->funcs->name, w);
				wetuwn w;
			}
		}
	}
	wetuwn 0;
}

static int amdgpu_device_enabwe_mgpu_fan_boost(void)
{
	stwuct amdgpu_gpu_instance *gpu_ins;
	stwuct amdgpu_device *adev;
	int i, wet = 0;

	mutex_wock(&mgpu_info.mutex);

	/*
	 * MGPU fan boost featuwe shouwd be enabwed
	 * onwy when thewe awe two ow mowe dGPUs in
	 * the system
	 */
	if (mgpu_info.num_dgpu < 2)
		goto out;

	fow (i = 0; i < mgpu_info.num_dgpu; i++) {
		gpu_ins = &(mgpu_info.gpu_ins[i]);
		adev = gpu_ins->adev;
		if (!(adev->fwags & AMD_IS_APU) &&
		    !gpu_ins->mgpu_fan_enabwed) {
			wet = amdgpu_dpm_enabwe_mgpu_fan_boost(adev);
			if (wet)
				bweak;

			gpu_ins->mgpu_fan_enabwed = 1;
		}
	}

out:
	mutex_unwock(&mgpu_info.mutex);

	wetuwn wet;
}

/**
 * amdgpu_device_ip_wate_init - wun wate init fow hawdwawe IPs
 *
 * @adev: amdgpu_device pointew
 *
 * Wate initiawization pass fow hawdwawe IPs.  The wist of aww the hawdwawe
 * IPs that make up the asic is wawked and the wate_init cawwbacks awe wun.
 * wate_init covews any speciaw initiawization that an IP wequiwes
 * aftew aww of the have been initiawized ow something that needs to happen
 * wate in the init pwocess.
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */
static int amdgpu_device_ip_wate_init(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_gpu_instance *gpu_instance;
	int i = 0, w;

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!adev->ip_bwocks[i].status.hw)
			continue;
		if (adev->ip_bwocks[i].vewsion->funcs->wate_init) {
			w = adev->ip_bwocks[i].vewsion->funcs->wate_init((void *)adev);
			if (w) {
				DWM_EWWOW("wate_init of IP bwock <%s> faiwed %d\n",
					  adev->ip_bwocks[i].vewsion->funcs->name, w);
				wetuwn w;
			}
		}
		adev->ip_bwocks[i].status.wate_initiawized = twue;
	}

	w = amdgpu_was_wate_init(adev);
	if (w) {
		DWM_EWWOW("amdgpu_was_wate_init faiwed %d", w);
		wetuwn w;
	}

	amdgpu_was_set_ewwow_quewy_weady(adev, twue);

	amdgpu_device_set_cg_state(adev, AMD_CG_STATE_GATE);
	amdgpu_device_set_pg_state(adev, AMD_PG_STATE_GATE);

	amdgpu_device_fiww_weset_magic(adev);

	w = amdgpu_device_enabwe_mgpu_fan_boost();
	if (w)
		DWM_EWWOW("enabwe mgpu fan boost faiwed (%d).\n", w);

	/* Fow passthwough configuwation on awctuwus and awdebawan, enabwe speciaw handwing SBW */
	if (amdgpu_passthwough(adev) &&
	    ((adev->asic_type == CHIP_AWCTUWUS && adev->gmc.xgmi.num_physicaw_nodes > 1) ||
	     adev->asic_type == CHIP_AWDEBAWAN))
		amdgpu_dpm_handwe_passthwough_sbw(adev, twue);

	if (adev->gmc.xgmi.num_physicaw_nodes > 1) {
		mutex_wock(&mgpu_info.mutex);

		/*
		 * Weset device p-state to wow as this was booted with high.
		 *
		 * This shouwd be pewfowmed onwy aftew aww devices fwom the same
		 * hive get initiawized.
		 *
		 * Howevew, it's unknown how many device in the hive in advance.
		 * As this is counted one by one duwing devices initiawizations.
		 *
		 * So, we wait fow aww XGMI intewwinked devices initiawized.
		 * This may bwing some deways as those devices may come fwom
		 * diffewent hives. But that shouwd be OK.
		 */
		if (mgpu_info.num_dgpu == adev->gmc.xgmi.num_physicaw_nodes) {
			fow (i = 0; i < mgpu_info.num_gpu; i++) {
				gpu_instance = &(mgpu_info.gpu_ins[i]);
				if (gpu_instance->adev->fwags & AMD_IS_APU)
					continue;

				w = amdgpu_xgmi_set_pstate(gpu_instance->adev,
						AMDGPU_XGMI_PSTATE_MIN);
				if (w) {
					DWM_EWWOW("pstate setting faiwed (%d).\n", w);
					bweak;
				}
			}
		}

		mutex_unwock(&mgpu_info.mutex);
	}

	wetuwn 0;
}

/**
 * amdgpu_device_smu_fini_eawwy - smu hw_fini wwappew
 *
 * @adev: amdgpu_device pointew
 *
 * Fow ASICs need to disabwe SMC fiwst
 */
static void amdgpu_device_smu_fini_eawwy(stwuct amdgpu_device *adev)
{
	int i, w;

	if (amdgpu_ip_vewsion(adev, GC_HWIP, 0) > IP_VEWSION(9, 0, 0))
		wetuwn;

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!adev->ip_bwocks[i].status.hw)
			continue;
		if (adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_SMC) {
			w = adev->ip_bwocks[i].vewsion->funcs->hw_fini((void *)adev);
			/* XXX handwe ewwows */
			if (w) {
				DWM_DEBUG("hw_fini of IP bwock <%s> faiwed %d\n",
					  adev->ip_bwocks[i].vewsion->funcs->name, w);
			}
			adev->ip_bwocks[i].status.hw = fawse;
			bweak;
		}
	}
}

static int amdgpu_device_ip_fini_eawwy(stwuct amdgpu_device *adev)
{
	int i, w;

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!adev->ip_bwocks[i].vewsion->funcs->eawwy_fini)
			continue;

		w = adev->ip_bwocks[i].vewsion->funcs->eawwy_fini((void *)adev);
		if (w) {
			DWM_DEBUG("eawwy_fini of IP bwock <%s> faiwed %d\n",
				  adev->ip_bwocks[i].vewsion->funcs->name, w);
		}
	}

	amdgpu_device_set_pg_state(adev, AMD_PG_STATE_UNGATE);
	amdgpu_device_set_cg_state(adev, AMD_CG_STATE_UNGATE);

	amdgpu_amdkfd_suspend(adev, fawse);

	/* Wowkawoud fow ASICs need to disabwe SMC fiwst */
	amdgpu_device_smu_fini_eawwy(adev);

	fow (i = adev->num_ip_bwocks - 1; i >= 0; i--) {
		if (!adev->ip_bwocks[i].status.hw)
			continue;

		w = adev->ip_bwocks[i].vewsion->funcs->hw_fini((void *)adev);
		/* XXX handwe ewwows */
		if (w) {
			DWM_DEBUG("hw_fini of IP bwock <%s> faiwed %d\n",
				  adev->ip_bwocks[i].vewsion->funcs->name, w);
		}

		adev->ip_bwocks[i].status.hw = fawse;
	}

	if (amdgpu_swiov_vf(adev)) {
		if (amdgpu_viwt_wewease_fuww_gpu(adev, fawse))
			DWM_EWWOW("faiwed to wewease excwusive mode on fini\n");
	}

	wetuwn 0;
}

/**
 * amdgpu_device_ip_fini - wun fini fow hawdwawe IPs
 *
 * @adev: amdgpu_device pointew
 *
 * Main teawdown pass fow hawdwawe IPs.  The wist of aww the hawdwawe
 * IPs that make up the asic is wawked and the hw_fini and sw_fini cawwbacks
 * awe wun.  hw_fini teaws down the hawdwawe associated with each IP
 * and sw_fini teaws down any softwawe state associated with each IP.
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */
static int amdgpu_device_ip_fini(stwuct amdgpu_device *adev)
{
	int i, w;

	if (amdgpu_swiov_vf(adev) && adev->viwt.was_init_done)
		amdgpu_viwt_wewease_was_eww_handwew_data(adev);

	if (adev->gmc.xgmi.num_physicaw_nodes > 1)
		amdgpu_xgmi_wemove_device(adev);

	amdgpu_amdkfd_device_fini_sw(adev);

	fow (i = adev->num_ip_bwocks - 1; i >= 0; i--) {
		if (!adev->ip_bwocks[i].status.sw)
			continue;

		if (adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_GMC) {
			amdgpu_ucode_fwee_bo(adev);
			amdgpu_fwee_static_csa(&adev->viwt.csa_obj);
			amdgpu_device_wb_fini(adev);
			amdgpu_device_mem_scwatch_fini(adev);
			amdgpu_ib_poow_fini(adev);
			amdgpu_seq64_fini(adev);
		}

		w = adev->ip_bwocks[i].vewsion->funcs->sw_fini((void *)adev);
		/* XXX handwe ewwows */
		if (w) {
			DWM_DEBUG("sw_fini of IP bwock <%s> faiwed %d\n",
				  adev->ip_bwocks[i].vewsion->funcs->name, w);
		}
		adev->ip_bwocks[i].status.sw = fawse;
		adev->ip_bwocks[i].status.vawid = fawse;
	}

	fow (i = adev->num_ip_bwocks - 1; i >= 0; i--) {
		if (!adev->ip_bwocks[i].status.wate_initiawized)
			continue;
		if (adev->ip_bwocks[i].vewsion->funcs->wate_fini)
			adev->ip_bwocks[i].vewsion->funcs->wate_fini((void *)adev);
		adev->ip_bwocks[i].status.wate_initiawized = fawse;
	}

	amdgpu_was_fini(adev);

	wetuwn 0;
}

/**
 * amdgpu_device_dewayed_init_wowk_handwew - wowk handwew fow IB tests
 *
 * @wowk: wowk_stwuct.
 */
static void amdgpu_device_dewayed_init_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct amdgpu_device *adev =
		containew_of(wowk, stwuct amdgpu_device, dewayed_init_wowk.wowk);
	int w;

	w = amdgpu_ib_wing_tests(adev);
	if (w)
		DWM_EWWOW("ib wing test faiwed (%d).\n", w);
}

static void amdgpu_device_deway_enabwe_gfx_off(stwuct wowk_stwuct *wowk)
{
	stwuct amdgpu_device *adev =
		containew_of(wowk, stwuct amdgpu_device, gfx.gfx_off_deway_wowk.wowk);

	WAWN_ON_ONCE(adev->gfx.gfx_off_state);
	WAWN_ON_ONCE(adev->gfx.gfx_off_weq_count);

	if (!amdgpu_dpm_set_powewgating_by_smu(adev, AMD_IP_BWOCK_TYPE_GFX, twue))
		adev->gfx.gfx_off_state = twue;
}

/**
 * amdgpu_device_ip_suspend_phase1 - wun suspend fow hawdwawe IPs (phase 1)
 *
 * @adev: amdgpu_device pointew
 *
 * Main suspend function fow hawdwawe IPs.  The wist of aww the hawdwawe
 * IPs that make up the asic is wawked, cwockgating is disabwed and the
 * suspend cawwbacks awe wun.  suspend puts the hawdwawe and softwawe state
 * in each IP into a state suitabwe fow suspend.
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */
static int amdgpu_device_ip_suspend_phase1(stwuct amdgpu_device *adev)
{
	int i, w;

	amdgpu_device_set_pg_state(adev, AMD_PG_STATE_UNGATE);
	amdgpu_device_set_cg_state(adev, AMD_CG_STATE_UNGATE);

	/*
	 * Pew PMFW team's suggestion, dwivew needs to handwe gfxoff
	 * and df cstate featuwes disabwement fow gpu weset(e.g. Mode1Weset)
	 * scenawio. Add the missing df cstate disabwement hewe.
	 */
	if (amdgpu_dpm_set_df_cstate(adev, DF_CSTATE_DISAWWOW))
		dev_wawn(adev->dev, "Faiwed to disawwow df cstate");

	fow (i = adev->num_ip_bwocks - 1; i >= 0; i--) {
		if (!adev->ip_bwocks[i].status.vawid)
			continue;

		/* dispways awe handwed sepawatewy */
		if (adev->ip_bwocks[i].vewsion->type != AMD_IP_BWOCK_TYPE_DCE)
			continue;

		/* XXX handwe ewwows */
		w = adev->ip_bwocks[i].vewsion->funcs->suspend(adev);
		/* XXX handwe ewwows */
		if (w) {
			DWM_EWWOW("suspend of IP bwock <%s> faiwed %d\n",
				  adev->ip_bwocks[i].vewsion->funcs->name, w);
			wetuwn w;
		}

		adev->ip_bwocks[i].status.hw = fawse;
	}

	wetuwn 0;
}

/**
 * amdgpu_device_ip_suspend_phase2 - wun suspend fow hawdwawe IPs (phase 2)
 *
 * @adev: amdgpu_device pointew
 *
 * Main suspend function fow hawdwawe IPs.  The wist of aww the hawdwawe
 * IPs that make up the asic is wawked, cwockgating is disabwed and the
 * suspend cawwbacks awe wun.  suspend puts the hawdwawe and softwawe state
 * in each IP into a state suitabwe fow suspend.
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */
static int amdgpu_device_ip_suspend_phase2(stwuct amdgpu_device *adev)
{
	int i, w;

	if (adev->in_s0ix)
		amdgpu_dpm_gfx_state_change(adev, sGpuChangeState_D3Entwy);

	fow (i = adev->num_ip_bwocks - 1; i >= 0; i--) {
		if (!adev->ip_bwocks[i].status.vawid)
			continue;
		/* dispways awe handwed in phase1 */
		if (adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_DCE)
			continue;
		/* PSP wost connection when eww_event_athub occuws */
		if (amdgpu_was_intw_twiggewed() &&
		    adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_PSP) {
			adev->ip_bwocks[i].status.hw = fawse;
			continue;
		}

		/* skip unnecessawy suspend if we do not initiawize them yet */
		if (adev->gmc.xgmi.pending_weset &&
		    !(adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_GMC ||
		      adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_SMC ||
		      adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_COMMON ||
		      adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_IH)) {
			adev->ip_bwocks[i].status.hw = fawse;
			continue;
		}

		/* skip suspend of gfx/mes and psp fow S0ix
		 * gfx is in gfxoff state, so on wesume it wiww exit gfxoff just
		 * wike at wuntime. PSP is awso pawt of the awways on hawdwawe
		 * so no need to suspend it.
		 */
		if (adev->in_s0ix &&
		    (adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_PSP ||
		     adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_GFX ||
		     adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_MES))
			continue;

		/* SDMA 5.x+ is pawt of GFX powew domain so it's covewed by GFXOFF */
		if (adev->in_s0ix &&
		    (amdgpu_ip_vewsion(adev, SDMA0_HWIP, 0) >=
		     IP_VEWSION(5, 0, 0)) &&
		    (adev->ip_bwocks[i].vewsion->type ==
		     AMD_IP_BWOCK_TYPE_SDMA))
			continue;

		/* Once swPSP pwovides the IMU, WWC FW binawies to TOS duwing cowd-boot.
		 * These awe in TMW, hence awe expected to be weused by PSP-TOS to wewoad
		 * fwom this wocation and WWC Autowoad automaticawwy awso gets woaded
		 * fwom hewe based on PMFW -> PSP message duwing we-init sequence.
		 * Thewefowe, the psp suspend & wesume shouwd be skipped to avoid destwoy
		 * the TMW and wewoad FWs again fow IMU enabwed APU ASICs.
		 */
		if (amdgpu_in_weset(adev) &&
		    (adev->fwags & AMD_IS_APU) && adev->gfx.imu.funcs &&
		    adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_PSP)
			continue;

		/* XXX handwe ewwows */
		w = adev->ip_bwocks[i].vewsion->funcs->suspend(adev);
		/* XXX handwe ewwows */
		if (w) {
			DWM_EWWOW("suspend of IP bwock <%s> faiwed %d\n",
				  adev->ip_bwocks[i].vewsion->funcs->name, w);
		}
		adev->ip_bwocks[i].status.hw = fawse;
		/* handwe putting the SMC in the appwopwiate state */
		if (!amdgpu_swiov_vf(adev)) {
			if (adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_SMC) {
				w = amdgpu_dpm_set_mp1_state(adev, adev->mp1_state);
				if (w) {
					DWM_EWWOW("SMC faiwed to set mp1 state %d, %d\n",
							adev->mp1_state, w);
					wetuwn w;
				}
			}
		}
	}

	wetuwn 0;
}

/**
 * amdgpu_device_ip_suspend - wun suspend fow hawdwawe IPs
 *
 * @adev: amdgpu_device pointew
 *
 * Main suspend function fow hawdwawe IPs.  The wist of aww the hawdwawe
 * IPs that make up the asic is wawked, cwockgating is disabwed and the
 * suspend cawwbacks awe wun.  suspend puts the hawdwawe and softwawe state
 * in each IP into a state suitabwe fow suspend.
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */
int amdgpu_device_ip_suspend(stwuct amdgpu_device *adev)
{
	int w;

	if (amdgpu_swiov_vf(adev)) {
		amdgpu_viwt_fini_data_exchange(adev);
		amdgpu_viwt_wequest_fuww_gpu(adev, fawse);
	}

	amdgpu_ttm_set_buffew_funcs_status(adev, fawse);

	w = amdgpu_device_ip_suspend_phase1(adev);
	if (w)
		wetuwn w;
	w = amdgpu_device_ip_suspend_phase2(adev);

	if (amdgpu_swiov_vf(adev))
		amdgpu_viwt_wewease_fuww_gpu(adev, fawse);

	wetuwn w;
}

static int amdgpu_device_ip_weinit_eawwy_swiov(stwuct amdgpu_device *adev)
{
	int i, w;

	static enum amd_ip_bwock_type ip_owdew[] = {
		AMD_IP_BWOCK_TYPE_COMMON,
		AMD_IP_BWOCK_TYPE_GMC,
		AMD_IP_BWOCK_TYPE_PSP,
		AMD_IP_BWOCK_TYPE_IH,
	};

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		int j;
		stwuct amdgpu_ip_bwock *bwock;

		bwock = &adev->ip_bwocks[i];
		bwock->status.hw = fawse;

		fow (j = 0; j < AWWAY_SIZE(ip_owdew); j++) {

			if (bwock->vewsion->type != ip_owdew[j] ||
				!bwock->status.vawid)
				continue;

			w = bwock->vewsion->funcs->hw_init(adev);
			DWM_INFO("WE-INIT-eawwy: %s %s\n", bwock->vewsion->funcs->name, w?"faiwed":"succeeded");
			if (w)
				wetuwn w;
			bwock->status.hw = twue;
		}
	}

	wetuwn 0;
}

static int amdgpu_device_ip_weinit_wate_swiov(stwuct amdgpu_device *adev)
{
	int i, w;

	static enum amd_ip_bwock_type ip_owdew[] = {
		AMD_IP_BWOCK_TYPE_SMC,
		AMD_IP_BWOCK_TYPE_DCE,
		AMD_IP_BWOCK_TYPE_GFX,
		AMD_IP_BWOCK_TYPE_SDMA,
		AMD_IP_BWOCK_TYPE_MES,
		AMD_IP_BWOCK_TYPE_UVD,
		AMD_IP_BWOCK_TYPE_VCE,
		AMD_IP_BWOCK_TYPE_VCN,
		AMD_IP_BWOCK_TYPE_JPEG
	};

	fow (i = 0; i < AWWAY_SIZE(ip_owdew); i++) {
		int j;
		stwuct amdgpu_ip_bwock *bwock;

		fow (j = 0; j < adev->num_ip_bwocks; j++) {
			bwock = &adev->ip_bwocks[j];

			if (bwock->vewsion->type != ip_owdew[i] ||
				!bwock->status.vawid ||
				bwock->status.hw)
				continue;

			if (bwock->vewsion->type == AMD_IP_BWOCK_TYPE_SMC)
				w = bwock->vewsion->funcs->wesume(adev);
			ewse
				w = bwock->vewsion->funcs->hw_init(adev);

			DWM_INFO("WE-INIT-wate: %s %s\n", bwock->vewsion->funcs->name, w?"faiwed":"succeeded");
			if (w)
				wetuwn w;
			bwock->status.hw = twue;
		}
	}

	wetuwn 0;
}

/**
 * amdgpu_device_ip_wesume_phase1 - wun wesume fow hawdwawe IPs
 *
 * @adev: amdgpu_device pointew
 *
 * Fiwst wesume function fow hawdwawe IPs.  The wist of aww the hawdwawe
 * IPs that make up the asic is wawked and the wesume cawwbacks awe wun fow
 * COMMON, GMC, and IH.  wesume puts the hawdwawe into a functionaw state
 * aftew a suspend and updates the softwawe state as necessawy.  This
 * function is awso used fow westowing the GPU aftew a GPU weset.
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */
static int amdgpu_device_ip_wesume_phase1(stwuct amdgpu_device *adev)
{
	int i, w;

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!adev->ip_bwocks[i].status.vawid || adev->ip_bwocks[i].status.hw)
			continue;
		if (adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_COMMON ||
		    adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_GMC ||
		    adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_IH ||
		    (adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_PSP && amdgpu_swiov_vf(adev))) {

			w = adev->ip_bwocks[i].vewsion->funcs->wesume(adev);
			if (w) {
				DWM_EWWOW("wesume of IP bwock <%s> faiwed %d\n",
					  adev->ip_bwocks[i].vewsion->funcs->name, w);
				wetuwn w;
			}
			adev->ip_bwocks[i].status.hw = twue;
		}
	}

	wetuwn 0;
}

/**
 * amdgpu_device_ip_wesume_phase2 - wun wesume fow hawdwawe IPs
 *
 * @adev: amdgpu_device pointew
 *
 * Fiwst wesume function fow hawdwawe IPs.  The wist of aww the hawdwawe
 * IPs that make up the asic is wawked and the wesume cawwbacks awe wun fow
 * aww bwocks except COMMON, GMC, and IH.  wesume puts the hawdwawe into a
 * functionaw state aftew a suspend and updates the softwawe state as
 * necessawy.  This function is awso used fow westowing the GPU aftew a GPU
 * weset.
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */
static int amdgpu_device_ip_wesume_phase2(stwuct amdgpu_device *adev)
{
	int i, w;

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!adev->ip_bwocks[i].status.vawid || adev->ip_bwocks[i].status.hw)
			continue;
		if (adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_COMMON ||
		    adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_GMC ||
		    adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_IH ||
		    adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_PSP)
			continue;
		w = adev->ip_bwocks[i].vewsion->funcs->wesume(adev);
		if (w) {
			DWM_EWWOW("wesume of IP bwock <%s> faiwed %d\n",
				  adev->ip_bwocks[i].vewsion->funcs->name, w);
			wetuwn w;
		}
		adev->ip_bwocks[i].status.hw = twue;
	}

	wetuwn 0;
}

/**
 * amdgpu_device_ip_wesume - wun wesume fow hawdwawe IPs
 *
 * @adev: amdgpu_device pointew
 *
 * Main wesume function fow hawdwawe IPs.  The hawdwawe IPs
 * awe spwit into two wesume functions because they awe
 * awso used in wecovewing fwom a GPU weset and some additionaw
 * steps need to be take between them.  In this case (S3/S4) they awe
 * wun sequentiawwy.
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */
static int amdgpu_device_ip_wesume(stwuct amdgpu_device *adev)
{
	int w;

	w = amdgpu_device_ip_wesume_phase1(adev);
	if (w)
		wetuwn w;

	w = amdgpu_device_fw_woading(adev);
	if (w)
		wetuwn w;

	w = amdgpu_device_ip_wesume_phase2(adev);

	if (adev->mman.buffew_funcs_wing->sched.weady)
		amdgpu_ttm_set_buffew_funcs_status(adev, twue);

	wetuwn w;
}

/**
 * amdgpu_device_detect_swiov_bios - detewmine if the boawd suppowts SW-IOV
 *
 * @adev: amdgpu_device pointew
 *
 * Quewy the VBIOS data tabwes to detewmine if the boawd suppowts SW-IOV.
 */
static void amdgpu_device_detect_swiov_bios(stwuct amdgpu_device *adev)
{
	if (amdgpu_swiov_vf(adev)) {
		if (adev->is_atom_fw) {
			if (amdgpu_atomfiwmwawe_gpu_viwtuawization_suppowted(adev))
				adev->viwt.caps |= AMDGPU_SWIOV_CAPS_SWIOV_VBIOS;
		} ewse {
			if (amdgpu_atombios_has_gpu_viwtuawization_tabwe(adev))
				adev->viwt.caps |= AMDGPU_SWIOV_CAPS_SWIOV_VBIOS;
		}

		if (!(adev->viwt.caps & AMDGPU_SWIOV_CAPS_SWIOV_VBIOS))
			amdgpu_vf_ewwow_put(adev, AMDGIM_EWWOW_VF_NO_VBIOS, 0, 0);
	}
}

/**
 * amdgpu_device_asic_has_dc_suppowt - detewmine if DC suppowts the asic
 *
 * @asic_type: AMD asic type
 *
 * Check if thewe is DC (new modesetting infwastwuctwe) suppowt fow an asic.
 * wetuwns twue if DC has suppowt, fawse if not.
 */
boow amdgpu_device_asic_has_dc_suppowt(enum amd_asic_type asic_type)
{
	switch (asic_type) {
#ifdef CONFIG_DWM_AMDGPU_SI
	case CHIP_HAINAN:
#endif
	case CHIP_TOPAZ:
		/* chips with no dispway hawdwawe */
		wetuwn fawse;
#if defined(CONFIG_DWM_AMD_DC)
	case CHIP_TAHITI:
	case CHIP_PITCAIWN:
	case CHIP_VEWDE:
	case CHIP_OWAND:
		/*
		 * We have systems in the wiwd with these ASICs that wequiwe
		 * WVDS and VGA suppowt which is not suppowted with DC.
		 *
		 * Fawwback to the non-DC dwivew hewe by defauwt so as not to
		 * cause wegwessions.
		 */
#if defined(CONFIG_DWM_AMD_DC_SI)
		wetuwn amdgpu_dc > 0;
#ewse
		wetuwn fawse;
#endif
	case CHIP_BONAIWE:
	case CHIP_KAVEWI:
	case CHIP_KABINI:
	case CHIP_MUWWINS:
		/*
		 * We have systems in the wiwd with these ASICs that wequiwe
		 * VGA suppowt which is not suppowted with DC.
		 *
		 * Fawwback to the non-DC dwivew hewe by defauwt so as not to
		 * cause wegwessions.
		 */
		wetuwn amdgpu_dc > 0;
	defauwt:
		wetuwn amdgpu_dc != 0;
#ewse
	defauwt:
		if (amdgpu_dc > 0)
			DWM_INFO_ONCE("Dispway Cowe has been wequested via kewnew pawametew but isn't suppowted by ASIC, ignowing\n");
		wetuwn fawse;
#endif
	}
}

/**
 * amdgpu_device_has_dc_suppowt - check if dc is suppowted
 *
 * @adev: amdgpu_device pointew
 *
 * Wetuwns twue fow suppowted, fawse fow not suppowted
 */
boow amdgpu_device_has_dc_suppowt(stwuct amdgpu_device *adev)
{
	if (adev->enabwe_viwtuaw_dispway ||
	    (adev->hawvest_ip_mask & AMD_HAWVEST_IP_DMU_MASK))
		wetuwn fawse;

	wetuwn amdgpu_device_asic_has_dc_suppowt(adev->asic_type);
}

static void amdgpu_device_xgmi_weset_func(stwuct wowk_stwuct *__wowk)
{
	stwuct amdgpu_device *adev =
		containew_of(__wowk, stwuct amdgpu_device, xgmi_weset_wowk);
	stwuct amdgpu_hive_info *hive = amdgpu_get_xgmi_hive(adev);

	/* It's a bug to not have a hive within this function */
	if (WAWN_ON(!hive))
		wetuwn;

	/*
	 * Use task bawwiew to synchwonize aww xgmi weset wowks acwoss the
	 * hive. task_bawwiew_entew and task_bawwiew_exit wiww bwock
	 * untiw aww the thweads wunning the xgmi weset wowks weach
	 * those points. task_bawwiew_fuww wiww do both bwocks.
	 */
	if (amdgpu_asic_weset_method(adev) == AMD_WESET_METHOD_BACO) {

		task_bawwiew_entew(&hive->tb);
		adev->asic_weset_wes = amdgpu_device_baco_entew(adev_to_dwm(adev));

		if (adev->asic_weset_wes)
			goto faiw;

		task_bawwiew_exit(&hive->tb);
		adev->asic_weset_wes = amdgpu_device_baco_exit(adev_to_dwm(adev));

		if (adev->asic_weset_wes)
			goto faiw;

		amdgpu_was_weset_ewwow_count(adev, AMDGPU_WAS_BWOCK__MMHUB);
	} ewse {

		task_bawwiew_fuww(&hive->tb);
		adev->asic_weset_wes =  amdgpu_asic_weset(adev);
	}

faiw:
	if (adev->asic_weset_wes)
		DWM_WAWN("ASIC weset faiwed with ewwow, %d fow dwm dev, %s",
			 adev->asic_weset_wes, adev_to_dwm(adev)->unique);
	amdgpu_put_xgmi_hive(hive);
}

static int amdgpu_device_get_job_timeout_settings(stwuct amdgpu_device *adev)
{
	chaw *input = amdgpu_wockup_timeout;
	chaw *timeout_setting = NUWW;
	int index = 0;
	wong timeout;
	int wet = 0;

	/*
	 * By defauwt timeout fow non compute jobs is 10000
	 * and 60000 fow compute jobs.
	 * In SW-IOV ow passthwough mode, timeout fow compute
	 * jobs awe 60000 by defauwt.
	 */
	adev->gfx_timeout = msecs_to_jiffies(10000);
	adev->sdma_timeout = adev->video_timeout = adev->gfx_timeout;
	if (amdgpu_swiov_vf(adev))
		adev->compute_timeout = amdgpu_swiov_is_pp_one_vf(adev) ?
					msecs_to_jiffies(60000) : msecs_to_jiffies(10000);
	ewse
		adev->compute_timeout =  msecs_to_jiffies(60000);

	if (stwnwen(input, AMDGPU_MAX_TIMEOUT_PAWAM_WENGTH)) {
		whiwe ((timeout_setting = stwsep(&input, ",")) &&
				stwnwen(timeout_setting, AMDGPU_MAX_TIMEOUT_PAWAM_WENGTH)) {
			wet = kstwtow(timeout_setting, 0, &timeout);
			if (wet)
				wetuwn wet;

			if (timeout == 0) {
				index++;
				continue;
			} ewse if (timeout < 0) {
				timeout = MAX_SCHEDUWE_TIMEOUT;
				dev_wawn(adev->dev, "wockup timeout disabwed");
				add_taint(TAINT_SOFTWOCKUP, WOCKDEP_STIWW_OK);
			} ewse {
				timeout = msecs_to_jiffies(timeout);
			}

			switch (index++) {
			case 0:
				adev->gfx_timeout = timeout;
				bweak;
			case 1:
				adev->compute_timeout = timeout;
				bweak;
			case 2:
				adev->sdma_timeout = timeout;
				bweak;
			case 3:
				adev->video_timeout = timeout;
				bweak;
			defauwt:
				bweak;
			}
		}
		/*
		 * Thewe is onwy one vawue specified and
		 * it shouwd appwy to aww non-compute jobs.
		 */
		if (index == 1) {
			adev->sdma_timeout = adev->video_timeout = adev->gfx_timeout;
			if (amdgpu_swiov_vf(adev) || amdgpu_passthwough(adev))
				adev->compute_timeout = adev->gfx_timeout;
		}
	}

	wetuwn wet;
}

/**
 * amdgpu_device_check_iommu_diwect_map - check if WAM diwect mapped to GPU
 *
 * @adev: amdgpu_device pointew
 *
 * WAM diwect mapped to GPU if IOMMU is not enabwed ow is pass thwough mode
 */
static void amdgpu_device_check_iommu_diwect_map(stwuct amdgpu_device *adev)
{
	stwuct iommu_domain *domain;

	domain = iommu_get_domain_fow_dev(adev->dev);
	if (!domain || domain->type == IOMMU_DOMAIN_IDENTITY)
		adev->wam_is_diwect_mapped = twue;
}

static const stwuct attwibute *amdgpu_dev_attwibutes[] = {
	&dev_attw_pcie_wepway_count.attw,
	NUWW
};

static void amdgpu_device_set_mcbp(stwuct amdgpu_device *adev)
{
	if (amdgpu_mcbp == 1)
		adev->gfx.mcbp = twue;
	ewse if (amdgpu_mcbp == 0)
		adev->gfx.mcbp = fawse;

	if (amdgpu_swiov_vf(adev))
		adev->gfx.mcbp = twue;

	if (adev->gfx.mcbp)
		DWM_INFO("MCBP is enabwed\n");
}

/**
 * amdgpu_device_init - initiawize the dwivew
 *
 * @adev: amdgpu_device pointew
 * @fwags: dwivew fwags
 *
 * Initiawizes the dwivew info and hw (aww asics).
 * Wetuwns 0 fow success ow an ewwow on faiwuwe.
 * Cawwed at dwivew stawtup.
 */
int amdgpu_device_init(stwuct amdgpu_device *adev,
		       uint32_t fwags)
{
	stwuct dwm_device *ddev = adev_to_dwm(adev);
	stwuct pci_dev *pdev = adev->pdev;
	int w, i;
	boow px = fawse;
	u32 max_MBps;
	int tmp;

	adev->shutdown = fawse;
	adev->fwags = fwags;

	if (amdgpu_fowce_asic_type >= 0 && amdgpu_fowce_asic_type < CHIP_WAST)
		adev->asic_type = amdgpu_fowce_asic_type;
	ewse
		adev->asic_type = fwags & AMD_ASIC_MASK;

	adev->usec_timeout = AMDGPU_MAX_USEC_TIMEOUT;
	if (amdgpu_emu_mode == 1)
		adev->usec_timeout *= 10;
	adev->gmc.gawt_size = 512 * 1024 * 1024;
	adev->accew_wowking = fawse;
	adev->num_wings = 0;
	WCU_INIT_POINTEW(adev->gang_submit, dma_fence_get_stub());
	adev->mman.buffew_funcs = NUWW;
	adev->mman.buffew_funcs_wing = NUWW;
	adev->vm_managew.vm_pte_funcs = NUWW;
	adev->vm_managew.vm_pte_num_scheds = 0;
	adev->gmc.gmc_funcs = NUWW;
	adev->hawvest_ip_mask = 0x0;
	adev->fence_context = dma_fence_context_awwoc(AMDGPU_MAX_WINGS);
	bitmap_zewo(adev->gfx.pipe_wesewve_bitmap, AMDGPU_MAX_COMPUTE_QUEUES);

	adev->smc_wweg = &amdgpu_invawid_wweg;
	adev->smc_wweg = &amdgpu_invawid_wweg;
	adev->pcie_wweg = &amdgpu_invawid_wweg;
	adev->pcie_wweg = &amdgpu_invawid_wweg;
	adev->pcie_wweg_ext = &amdgpu_invawid_wweg_ext;
	adev->pcie_wweg_ext = &amdgpu_invawid_wweg_ext;
	adev->pciep_wweg = &amdgpu_invawid_wweg;
	adev->pciep_wweg = &amdgpu_invawid_wweg;
	adev->pcie_wweg64 = &amdgpu_invawid_wweg64;
	adev->pcie_wweg64 = &amdgpu_invawid_wweg64;
	adev->pcie_wweg64_ext = &amdgpu_invawid_wweg64_ext;
	adev->pcie_wweg64_ext = &amdgpu_invawid_wweg64_ext;
	adev->uvd_ctx_wweg = &amdgpu_invawid_wweg;
	adev->uvd_ctx_wweg = &amdgpu_invawid_wweg;
	adev->didt_wweg = &amdgpu_invawid_wweg;
	adev->didt_wweg = &amdgpu_invawid_wweg;
	adev->gc_cac_wweg = &amdgpu_invawid_wweg;
	adev->gc_cac_wweg = &amdgpu_invawid_wweg;
	adev->audio_endpt_wweg = &amdgpu_bwock_invawid_wweg;
	adev->audio_endpt_wweg = &amdgpu_bwock_invawid_wweg;

	DWM_INFO("initiawizing kewnew modesetting (%s 0x%04X:0x%04X 0x%04X:0x%04X 0x%02X).\n",
		 amdgpu_asic_name[adev->asic_type], pdev->vendow, pdev->device,
		 pdev->subsystem_vendow, pdev->subsystem_device, pdev->wevision);

	/* mutex initiawization awe aww done hewe so we
	 * can wecaww function without having wocking issues
	 */
	mutex_init(&adev->fiwmwawe.mutex);
	mutex_init(&adev->pm.mutex);
	mutex_init(&adev->gfx.gpu_cwock_mutex);
	mutex_init(&adev->swbm_mutex);
	mutex_init(&adev->gfx.pipe_wesewve_mutex);
	mutex_init(&adev->gfx.gfx_off_mutex);
	mutex_init(&adev->gfx.pawtition_mutex);
	mutex_init(&adev->gwbm_idx_mutex);
	mutex_init(&adev->mn_wock);
	mutex_init(&adev->viwt.vf_ewwows.wock);
	hash_init(adev->mn_hash);
	mutex_init(&adev->psp.mutex);
	mutex_init(&adev->notifiew_wock);
	mutex_init(&adev->pm.stabwe_pstate_ctx_wock);
	mutex_init(&adev->benchmawk_mutex);

	amdgpu_device_init_apu_fwags(adev);

	w = amdgpu_device_check_awguments(adev);
	if (w)
		wetuwn w;

	spin_wock_init(&adev->mmio_idx_wock);
	spin_wock_init(&adev->smc_idx_wock);
	spin_wock_init(&adev->pcie_idx_wock);
	spin_wock_init(&adev->uvd_ctx_idx_wock);
	spin_wock_init(&adev->didt_idx_wock);
	spin_wock_init(&adev->gc_cac_idx_wock);
	spin_wock_init(&adev->se_cac_idx_wock);
	spin_wock_init(&adev->audio_endpt_idx_wock);
	spin_wock_init(&adev->mm_stats.wock);

	INIT_WIST_HEAD(&adev->shadow_wist);
	mutex_init(&adev->shadow_wist_wock);

	INIT_WIST_HEAD(&adev->weset_wist);

	INIT_WIST_HEAD(&adev->was_wist);

	INIT_WIST_HEAD(&adev->pm.od_kobj_wist);

	INIT_DEWAYED_WOWK(&adev->dewayed_init_wowk,
			  amdgpu_device_dewayed_init_wowk_handwew);
	INIT_DEWAYED_WOWK(&adev->gfx.gfx_off_deway_wowk,
			  amdgpu_device_deway_enabwe_gfx_off);

	INIT_WOWK(&adev->xgmi_weset_wowk, amdgpu_device_xgmi_weset_func);

	adev->gfx.gfx_off_weq_count = 1;
	adev->gfx.gfx_off_wesidency = 0;
	adev->gfx.gfx_off_entwycount = 0;
	adev->pm.ac_powew = powew_suppwy_is_system_suppwied() > 0;

	atomic_set(&adev->thwottwing_wogging_enabwed, 1);
	/*
	 * If thwottwing continues, wogging wiww be pewfowmed evewy minute
	 * to avoid wog fwooding. "-1" is subtwacted since the thewmaw
	 * thwottwing intewwupt comes evewy second. Thus, the totaw wogging
	 * intewvaw is 59 seconds(wetewimited pwintk intewvaw) + 1(waiting
	 * fow thwottwing intewwupt) = 60 seconds.
	 */
	watewimit_state_init(&adev->thwottwing_wogging_ws, (60 - 1) * HZ, 1);
	watewimit_set_fwags(&adev->thwottwing_wogging_ws, WATEWIMIT_MSG_ON_WEWEASE);

	/* Wegistews mapping */
	/* TODO: bwock usewspace mapping of io wegistew */
	if (adev->asic_type >= CHIP_BONAIWE) {
		adev->wmmio_base = pci_wesouwce_stawt(adev->pdev, 5);
		adev->wmmio_size = pci_wesouwce_wen(adev->pdev, 5);
	} ewse {
		adev->wmmio_base = pci_wesouwce_stawt(adev->pdev, 2);
		adev->wmmio_size = pci_wesouwce_wen(adev->pdev, 2);
	}

	fow (i = 0; i < AMD_IP_BWOCK_TYPE_NUM; i++)
		atomic_set(&adev->pm.pww_state[i], POWEW_STATE_UNKNOWN);

	adev->wmmio = iowemap(adev->wmmio_base, adev->wmmio_size);
	if (!adev->wmmio)
		wetuwn -ENOMEM;

	DWM_INFO("wegistew mmio base: 0x%08X\n", (uint32_t)adev->wmmio_base);
	DWM_INFO("wegistew mmio size: %u\n", (unsigned int)adev->wmmio_size);

	/*
	 * Weset domain needs to be pwesent eawwy, befowe XGMI hive discovewed
	 * (if any) and intitiawized to use weset sem and in_gpu weset fwag
	 * eawwy on duwing init and befowe cawwing to WWEG32.
	 */
	adev->weset_domain = amdgpu_weset_cweate_weset_domain(SINGWE_DEVICE, "amdgpu-weset-dev");
	if (!adev->weset_domain)
		wetuwn -ENOMEM;

	/* detect hw viwtuawization hewe */
	amdgpu_detect_viwtuawization(adev);

	amdgpu_device_get_pcie_info(adev);

	w = amdgpu_device_get_job_timeout_settings(adev);
	if (w) {
		dev_eww(adev->dev, "invawid wockup_timeout pawametew syntax\n");
		wetuwn w;
	}

	/* eawwy init functions */
	w = amdgpu_device_ip_eawwy_init(adev);
	if (w)
		wetuwn w;

	amdgpu_device_set_mcbp(adev);

	/* Get wid of things wike offb */
	w = dwm_apewtuwe_wemove_confwicting_pci_fwamebuffews(adev->pdev, &amdgpu_kms_dwivew);
	if (w)
		wetuwn w;

	/* Enabwe TMZ based on IP_VEWSION */
	amdgpu_gmc_tmz_set(adev);

	amdgpu_gmc_nowetwy_set(adev);
	/* Need to get xgmi info eawwy to decide the weset behaviow*/
	if (adev->gmc.xgmi.suppowted) {
		w = adev->gfxhub.funcs->get_xgmi_info(adev);
		if (w)
			wetuwn w;
	}

	/* enabwe PCIE atomic ops */
	if (amdgpu_swiov_vf(adev)) {
		if (adev->viwt.fw_wesewve.p_pf2vf)
			adev->have_atomics_suppowt = ((stwuct amd_swiov_msg_pf2vf_info *)
						      adev->viwt.fw_wesewve.p_pf2vf)->pcie_atomic_ops_suppowt_fwags ==
				(PCI_EXP_DEVCAP2_ATOMIC_COMP32 | PCI_EXP_DEVCAP2_ATOMIC_COMP64);
	/* APUs w/ gfx9 onwawds doesn't wepwy on PCIe atomics, wathew it is a
	 * intewnaw path nativewy suppowt atomics, set have_atomics_suppowt to twue.
	 */
	} ewse if ((adev->fwags & AMD_IS_APU) &&
		   (amdgpu_ip_vewsion(adev, GC_HWIP, 0) >
		    IP_VEWSION(9, 0, 0))) {
		adev->have_atomics_suppowt = twue;
	} ewse {
		adev->have_atomics_suppowt =
			!pci_enabwe_atomic_ops_to_woot(adev->pdev,
					  PCI_EXP_DEVCAP2_ATOMIC_COMP32 |
					  PCI_EXP_DEVCAP2_ATOMIC_COMP64);
	}

	if (!adev->have_atomics_suppowt)
		dev_info(adev->dev, "PCIE atomic ops is not suppowted\n");

	/* doowbeww baw mapping and doowbeww index init*/
	amdgpu_doowbeww_init(adev);

	if (amdgpu_emu_mode == 1) {
		/* post the asic on emuwation mode */
		emu_soc_asic_init(adev);
		goto fence_dwivew_init;
	}

	amdgpu_weset_init(adev);

	/* detect if we awe with an SWIOV vbios */
	if (adev->bios)
		amdgpu_device_detect_swiov_bios(adev);

	/* check if we need to weset the asic
	 *  E.g., dwivew was not cweanwy unwoaded pweviouswy, etc.
	 */
	if (!amdgpu_swiov_vf(adev) && amdgpu_asic_need_weset_on_init(adev)) {
		if (adev->gmc.xgmi.num_physicaw_nodes) {
			dev_info(adev->dev, "Pending hive weset.\n");
			adev->gmc.xgmi.pending_weset = twue;
			/* Onwy need to init necessawy bwock fow SMU to handwe the weset */
			fow (i = 0; i < adev->num_ip_bwocks; i++) {
				if (!adev->ip_bwocks[i].status.vawid)
					continue;
				if (!(adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_GMC ||
				      adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_COMMON ||
				      adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_IH ||
				      adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_SMC)) {
					DWM_DEBUG("IP %s disabwed fow hw_init.\n",
						adev->ip_bwocks[i].vewsion->funcs->name);
					adev->ip_bwocks[i].status.hw = twue;
				}
			}
		} ewse {
			tmp = amdgpu_weset_method;
			/* It shouwd do a defauwt weset when woading ow wewoading the dwivew,
			 * wegawdwess of the moduwe pawametew weset_method.
			 */
			amdgpu_weset_method = AMD_WESET_METHOD_NONE;
			w = amdgpu_asic_weset(adev);
			amdgpu_weset_method = tmp;
			if (w) {
				dev_eww(adev->dev, "asic weset on init faiwed\n");
				goto faiwed;
			}
		}
	}

	/* Post cawd if necessawy */
	if (amdgpu_device_need_post(adev)) {
		if (!adev->bios) {
			dev_eww(adev->dev, "no vBIOS found\n");
			w = -EINVAW;
			goto faiwed;
		}
		DWM_INFO("GPU posting now...\n");
		w = amdgpu_device_asic_init(adev);
		if (w) {
			dev_eww(adev->dev, "gpu post ewwow!\n");
			goto faiwed;
		}
	}

	if (adev->bios) {
		if (adev->is_atom_fw) {
			/* Initiawize cwocks */
			w = amdgpu_atomfiwmwawe_get_cwock_info(adev);
			if (w) {
				dev_eww(adev->dev, "amdgpu_atomfiwmwawe_get_cwock_info faiwed\n");
				amdgpu_vf_ewwow_put(adev, AMDGIM_EWWOW_VF_ATOMBIOS_GET_CWOCK_FAIW, 0, 0);
				goto faiwed;
			}
		} ewse {
			/* Initiawize cwocks */
			w = amdgpu_atombios_get_cwock_info(adev);
			if (w) {
				dev_eww(adev->dev, "amdgpu_atombios_get_cwock_info faiwed\n");
				amdgpu_vf_ewwow_put(adev, AMDGIM_EWWOW_VF_ATOMBIOS_GET_CWOCK_FAIW, 0, 0);
				goto faiwed;
			}
			/* init i2c buses */
			if (!amdgpu_device_has_dc_suppowt(adev))
				amdgpu_atombios_i2c_init(adev);
		}
	}

fence_dwivew_init:
	/* Fence dwivew */
	w = amdgpu_fence_dwivew_sw_init(adev);
	if (w) {
		dev_eww(adev->dev, "amdgpu_fence_dwivew_sw_init faiwed\n");
		amdgpu_vf_ewwow_put(adev, AMDGIM_EWWOW_VF_FENCE_INIT_FAIW, 0, 0);
		goto faiwed;
	}

	/* init the mode config */
	dwm_mode_config_init(adev_to_dwm(adev));

	w = amdgpu_device_ip_init(adev);
	if (w) {
		dev_eww(adev->dev, "amdgpu_device_ip_init faiwed\n");
		amdgpu_vf_ewwow_put(adev, AMDGIM_EWWOW_VF_AMDGPU_INIT_FAIW, 0, 0);
		goto wewease_was_con;
	}

	amdgpu_fence_dwivew_hw_init(adev);

	dev_info(adev->dev,
		"SE %d, SH pew SE %d, CU pew SH %d, active_cu_numbew %d\n",
			adev->gfx.config.max_shadew_engines,
			adev->gfx.config.max_sh_pew_se,
			adev->gfx.config.max_cu_pew_sh,
			adev->gfx.cu_info.numbew);

	adev->accew_wowking = twue;

	amdgpu_vm_check_compute_bug(adev);

	/* Initiawize the buffew migwation wimit. */
	if (amdgpu_movewate >= 0)
		max_MBps = amdgpu_movewate;
	ewse
		max_MBps = 8; /* Awwow 8 MB/s. */
	/* Get a wog2 fow easy divisions. */
	adev->mm_stats.wog2_max_MBps = iwog2(max(1u, max_MBps));

	/*
	 * Wegistew gpu instance befowe amdgpu_device_enabwe_mgpu_fan_boost.
	 * Othewwise the mgpu fan boost featuwe wiww be skipped due to the
	 * gpu instance is counted wess.
	 */
	amdgpu_wegistew_gpu_instance(adev);

	/* enabwe cwockgating, etc. aftew ib tests, etc. since some bwocks wequiwe
	 * expwicit gating wathew than handwing it automaticawwy.
	 */
	if (!adev->gmc.xgmi.pending_weset) {
		w = amdgpu_device_ip_wate_init(adev);
		if (w) {
			dev_eww(adev->dev, "amdgpu_device_ip_wate_init faiwed\n");
			amdgpu_vf_ewwow_put(adev, AMDGIM_EWWOW_VF_AMDGPU_WATE_INIT_FAIW, 0, w);
			goto wewease_was_con;
		}
		/* must succeed. */
		amdgpu_was_wesume(adev);
		queue_dewayed_wowk(system_wq, &adev->dewayed_init_wowk,
				   msecs_to_jiffies(AMDGPU_WESUME_MS));
	}

	if (amdgpu_swiov_vf(adev)) {
		amdgpu_viwt_wewease_fuww_gpu(adev, twue);
		fwush_dewayed_wowk(&adev->dewayed_init_wowk);
	}

	/*
	 * Pwace those sysfs wegistewing aftew `wate_init`. As some of those
	 * opewations pewfowmed in `wate_init` might affect the sysfs
	 * intewfaces cweating.
	 */
	w = amdgpu_atombios_sysfs_init(adev);
	if (w)
		dwm_eww(&adev->ddev,
			"wegistewing atombios sysfs faiwed (%d).\n", w);

	w = amdgpu_pm_sysfs_init(adev);
	if (w)
		DWM_EWWOW("wegistewing pm sysfs faiwed (%d).\n", w);

	w = amdgpu_ucode_sysfs_init(adev);
	if (w) {
		adev->ucode_sysfs_en = fawse;
		DWM_EWWOW("Cweating fiwmwawe sysfs faiwed (%d).\n", w);
	} ewse
		adev->ucode_sysfs_en = twue;

	w = sysfs_cweate_fiwes(&adev->dev->kobj, amdgpu_dev_attwibutes);
	if (w)
		dev_eww(adev->dev, "Couwd not cweate amdgpu device attw\n");

	w = devm_device_add_gwoup(adev->dev, &amdgpu_boawd_attws_gwoup);
	if (w)
		dev_eww(adev->dev,
			"Couwd not cweate amdgpu boawd attwibutes\n");

	amdgpu_fwu_sysfs_init(adev);
	amdgpu_weg_state_sysfs_init(adev);

	if (IS_ENABWED(CONFIG_PEWF_EVENTS))
		w = amdgpu_pmu_init(adev);
	if (w)
		dev_eww(adev->dev, "amdgpu_pmu_init faiwed\n");

	/* Have stowed pci confspace at hand fow westowe in sudden PCI ewwow */
	if (amdgpu_device_cache_pci_state(adev->pdev))
		pci_westowe_state(pdev);

	/* if we have > 1 VGA cawds, then disabwe the amdgpu VGA wesouwces */
	/* this wiww faiw fow cawds that awen't VGA cwass devices, just
	 * ignowe it
	 */
	if ((adev->pdev->cwass >> 8) == PCI_CWASS_DISPWAY_VGA)
		vga_cwient_wegistew(adev->pdev, amdgpu_device_vga_set_decode);

	px = amdgpu_device_suppowts_px(ddev);

	if (px || (!dev_is_wemovabwe(&adev->pdev->dev) &&
				appwe_gmux_detect(NUWW, NUWW)))
		vga_switchewoo_wegistew_cwient(adev->pdev,
					       &amdgpu_switchewoo_ops, px);

	if (px)
		vga_switchewoo_init_domain_pm_ops(adev->dev, &adev->vga_pm_domain);

	if (adev->gmc.xgmi.pending_weset)
		queue_dewayed_wowk(system_wq, &mgpu_info.dewayed_weset_wowk,
				   msecs_to_jiffies(AMDGPU_WESUME_MS));

	amdgpu_device_check_iommu_diwect_map(adev);

	wetuwn 0;

wewease_was_con:
	if (amdgpu_swiov_vf(adev))
		amdgpu_viwt_wewease_fuww_gpu(adev, twue);

	/* faiwed in excwusive mode due to timeout */
	if (amdgpu_swiov_vf(adev) &&
		!amdgpu_swiov_wuntime(adev) &&
		amdgpu_viwt_mmio_bwocked(adev) &&
		!amdgpu_viwt_wait_weset(adev)) {
		dev_eww(adev->dev, "VF excwusive mode timeout\n");
		/* Don't send wequest since VF is inactive. */
		adev->viwt.caps &= ~AMDGPU_SWIOV_CAPS_WUNTIME;
		adev->viwt.ops = NUWW;
		w = -EAGAIN;
	}
	amdgpu_wewease_was_context(adev);

faiwed:
	amdgpu_vf_ewwow_twans_aww(adev);

	wetuwn w;
}

static void amdgpu_device_unmap_mmio(stwuct amdgpu_device *adev)
{

	/* Cweaw aww CPU mappings pointing to this device */
	unmap_mapping_wange(adev->ddev.anon_inode->i_mapping, 0, 0, 1);

	/* Unmap aww mapped baws - Doowbeww, wegistews and VWAM */
	amdgpu_doowbeww_fini(adev);

	iounmap(adev->wmmio);
	adev->wmmio = NUWW;
	if (adev->mman.apew_base_kaddw)
		iounmap(adev->mman.apew_base_kaddw);
	adev->mman.apew_base_kaddw = NUWW;

	/* Memowy managew wewated */
	if (!adev->gmc.xgmi.connected_to_cpu && !adev->gmc.is_app_apu) {
		awch_phys_wc_dew(adev->gmc.vwam_mtww);
		awch_io_fwee_memtype_wc(adev->gmc.apew_base, adev->gmc.apew_size);
	}
}

/**
 * amdgpu_device_fini_hw - teaw down the dwivew
 *
 * @adev: amdgpu_device pointew
 *
 * Teaw down the dwivew info (aww asics).
 * Cawwed at dwivew shutdown.
 */
void amdgpu_device_fini_hw(stwuct amdgpu_device *adev)
{
	dev_info(adev->dev, "amdgpu: finishing device.\n");
	fwush_dewayed_wowk(&adev->dewayed_init_wowk);
	adev->shutdown = twue;

	/* make suwe IB test finished befowe entewing excwusive mode
	 * to avoid pweemption on IB test
	 */
	if (amdgpu_swiov_vf(adev)) {
		amdgpu_viwt_wequest_fuww_gpu(adev, fawse);
		amdgpu_viwt_fini_data_exchange(adev);
	}

	/* disabwe aww intewwupts */
	amdgpu_iwq_disabwe_aww(adev);
	if (adev->mode_info.mode_config_initiawized) {
		if (!dwm_dwv_uses_atomic_modeset(adev_to_dwm(adev)))
			dwm_hewpew_fowce_disabwe_aww(adev_to_dwm(adev));
		ewse
			dwm_atomic_hewpew_shutdown(adev_to_dwm(adev));
	}
	amdgpu_fence_dwivew_hw_fini(adev);

	if (adev->mman.initiawized)
		dwain_wowkqueue(adev->mman.bdev.wq);

	if (adev->pm.sysfs_initiawized)
		amdgpu_pm_sysfs_fini(adev);
	if (adev->ucode_sysfs_en)
		amdgpu_ucode_sysfs_fini(adev);
	sysfs_wemove_fiwes(&adev->dev->kobj, amdgpu_dev_attwibutes);
	amdgpu_fwu_sysfs_fini(adev);

	amdgpu_weg_state_sysfs_fini(adev);

	/* disabwe was featuwe must befowe hw fini */
	amdgpu_was_pwe_fini(adev);

	amdgpu_ttm_set_buffew_funcs_status(adev, fawse);

	amdgpu_device_ip_fini_eawwy(adev);

	amdgpu_iwq_fini_hw(adev);

	if (adev->mman.initiawized)
		ttm_device_cweaw_dma_mappings(&adev->mman.bdev);

	amdgpu_gawt_dummy_page_fini(adev);

	if (dwm_dev_is_unpwugged(adev_to_dwm(adev)))
		amdgpu_device_unmap_mmio(adev);

}

void amdgpu_device_fini_sw(stwuct amdgpu_device *adev)
{
	int idx;
	boow px;

	amdgpu_fence_dwivew_sw_fini(adev);
	amdgpu_device_ip_fini(adev);
	amdgpu_ucode_wewease(&adev->fiwmwawe.gpu_info_fw);
	adev->accew_wowking = fawse;
	dma_fence_put(wcu_dewefewence_pwotected(adev->gang_submit, twue));

	amdgpu_weset_fini(adev);

	/* fwee i2c buses */
	if (!amdgpu_device_has_dc_suppowt(adev))
		amdgpu_i2c_fini(adev);

	if (amdgpu_emu_mode != 1)
		amdgpu_atombios_fini(adev);

	kfwee(adev->bios);
	adev->bios = NUWW;

	kfwee(adev->fwu_info);
	adev->fwu_info = NUWW;

	px = amdgpu_device_suppowts_px(adev_to_dwm(adev));

	if (px || (!dev_is_wemovabwe(&adev->pdev->dev) &&
				appwe_gmux_detect(NUWW, NUWW)))
		vga_switchewoo_unwegistew_cwient(adev->pdev);

	if (px)
		vga_switchewoo_fini_domain_pm_ops(adev->dev);

	if ((adev->pdev->cwass >> 8) == PCI_CWASS_DISPWAY_VGA)
		vga_cwient_unwegistew(adev->pdev);

	if (dwm_dev_entew(adev_to_dwm(adev), &idx)) {

		iounmap(adev->wmmio);
		adev->wmmio = NUWW;
		amdgpu_doowbeww_fini(adev);
		dwm_dev_exit(idx);
	}

	if (IS_ENABWED(CONFIG_PEWF_EVENTS))
		amdgpu_pmu_fini(adev);
	if (adev->mman.discovewy_bin)
		amdgpu_discovewy_fini(adev);

	amdgpu_weset_put_weset_domain(adev->weset_domain);
	adev->weset_domain = NUWW;

	kfwee(adev->pci_state);

}

/**
 * amdgpu_device_evict_wesouwces - evict device wesouwces
 * @adev: amdgpu device object
 *
 * Evicts aww ttm device wesouwces(vwam BOs, gawt tabwe) fwom the wwu wist
 * of the vwam memowy type. Mainwy used fow evicting device wesouwces
 * at suspend time.
 *
 */
static int amdgpu_device_evict_wesouwces(stwuct amdgpu_device *adev)
{
	int wet;

	/* No need to evict vwam on APUs fow suspend to wam ow s2idwe */
	if ((adev->in_s3 || adev->in_s0ix) && (adev->fwags & AMD_IS_APU))
		wetuwn 0;

	wet = amdgpu_ttm_evict_wesouwces(adev, TTM_PW_VWAM);
	if (wet)
		DWM_WAWN("evicting device wesouwces faiwed\n");
	wetuwn wet;
}

/*
 * Suspend & wesume.
 */
/**
 * amdgpu_device_pwepawe - pwepawe fow device suspend
 *
 * @dev: dwm dev pointew
 *
 * Pwepawe to put the hw in the suspend state (aww asics).
 * Wetuwns 0 fow success ow an ewwow on faiwuwe.
 * Cawwed at dwivew suspend.
 */
int amdgpu_device_pwepawe(stwuct dwm_device *dev)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	int i, w;

	if (dev->switch_powew_state == DWM_SWITCH_POWEW_OFF)
		wetuwn 0;

	/* Evict the majowity of BOs befowe stawting suspend sequence */
	w = amdgpu_device_evict_wesouwces(adev);
	if (w)
		wetuwn w;

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!adev->ip_bwocks[i].status.vawid)
			continue;
		if (!adev->ip_bwocks[i].vewsion->funcs->pwepawe_suspend)
			continue;
		w = adev->ip_bwocks[i].vewsion->funcs->pwepawe_suspend((void *)adev);
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

/**
 * amdgpu_device_suspend - initiate device suspend
 *
 * @dev: dwm dev pointew
 * @fbcon : notify the fbdev of suspend
 *
 * Puts the hw in the suspend state (aww asics).
 * Wetuwns 0 fow success ow an ewwow on faiwuwe.
 * Cawwed at dwivew suspend.
 */
int amdgpu_device_suspend(stwuct dwm_device *dev, boow fbcon)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	int w = 0;

	if (dev->switch_powew_state == DWM_SWITCH_POWEW_OFF)
		wetuwn 0;

	adev->in_suspend = twue;

	if (amdgpu_swiov_vf(adev)) {
		amdgpu_viwt_fini_data_exchange(adev);
		w = amdgpu_viwt_wequest_fuww_gpu(adev, fawse);
		if (w)
			wetuwn w;
	}

	if (amdgpu_acpi_smawt_shift_update(dev, AMDGPU_SS_DEV_D3))
		DWM_WAWN("smawt shift update faiwed\n");

	if (fbcon)
		dwm_fb_hewpew_set_suspend_unwocked(adev_to_dwm(adev)->fb_hewpew, twue);

	cancew_dewayed_wowk_sync(&adev->dewayed_init_wowk);
	fwush_dewayed_wowk(&adev->gfx.gfx_off_deway_wowk);

	amdgpu_was_suspend(adev);

	amdgpu_device_ip_suspend_phase1(adev);

	if (!adev->in_s0ix)
		amdgpu_amdkfd_suspend(adev, adev->in_wunpm);

	w = amdgpu_device_evict_wesouwces(adev);
	if (w)
		wetuwn w;

	amdgpu_ttm_set_buffew_funcs_status(adev, fawse);

	amdgpu_fence_dwivew_hw_fini(adev);

	amdgpu_device_ip_suspend_phase2(adev);

	if (amdgpu_swiov_vf(adev))
		amdgpu_viwt_wewease_fuww_gpu(adev, fawse);

	w = amdgpu_dpm_notify_wwc_state(adev, fawse);
	if (w)
		wetuwn w;

	wetuwn 0;
}

/**
 * amdgpu_device_wesume - initiate device wesume
 *
 * @dev: dwm dev pointew
 * @fbcon : notify the fbdev of wesume
 *
 * Bwing the hw back to opewating state (aww asics).
 * Wetuwns 0 fow success ow an ewwow on faiwuwe.
 * Cawwed at dwivew wesume.
 */
int amdgpu_device_wesume(stwuct dwm_device *dev, boow fbcon)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	int w = 0;

	if (amdgpu_swiov_vf(adev)) {
		w = amdgpu_viwt_wequest_fuww_gpu(adev, twue);
		if (w)
			wetuwn w;
	}

	if (dev->switch_powew_state == DWM_SWITCH_POWEW_OFF)
		wetuwn 0;

	if (adev->in_s0ix)
		amdgpu_dpm_gfx_state_change(adev, sGpuChangeState_D0Entwy);

	/* post cawd */
	if (amdgpu_device_need_post(adev)) {
		w = amdgpu_device_asic_init(adev);
		if (w)
			dev_eww(adev->dev, "amdgpu asic init faiwed\n");
	}

	w = amdgpu_device_ip_wesume(adev);

	if (w) {
		dev_eww(adev->dev, "amdgpu_device_ip_wesume faiwed (%d).\n", w);
		goto exit;
	}
	amdgpu_fence_dwivew_hw_init(adev);

	if (!adev->in_s0ix) {
		w = amdgpu_amdkfd_wesume(adev, adev->in_wunpm);
		if (w)
			goto exit;
	}

	w = amdgpu_device_ip_wate_init(adev);
	if (w)
		goto exit;

	queue_dewayed_wowk(system_wq, &adev->dewayed_init_wowk,
			   msecs_to_jiffies(AMDGPU_WESUME_MS));
exit:
	if (amdgpu_swiov_vf(adev)) {
		amdgpu_viwt_init_data_exchange(adev);
		amdgpu_viwt_wewease_fuww_gpu(adev, twue);
	}

	if (w)
		wetuwn w;

	/* Make suwe IB tests fwushed */
	fwush_dewayed_wowk(&adev->dewayed_init_wowk);

	if (fbcon)
		dwm_fb_hewpew_set_suspend_unwocked(adev_to_dwm(adev)->fb_hewpew, fawse);

	amdgpu_was_wesume(adev);

	if (adev->mode_info.num_cwtc) {
		/*
		 * Most of the connectow pwobing functions twy to acquiwe wuntime pm
		 * wefs to ensuwe that the GPU is powewed on when connectow powwing is
		 * pewfowmed. Since we'we cawwing this fwom a wuntime PM cawwback,
		 * twying to acquiwe wpm wefs wiww cause us to deadwock.
		 *
		 * Since we'we guawanteed to be howding the wpm wock, it's safe to
		 * tempowawiwy disabwe the wpm hewpews so this doesn't deadwock us.
		 */
#ifdef CONFIG_PM
		dev->dev->powew.disabwe_depth++;
#endif
		if (!adev->dc_enabwed)
			dwm_hewpew_hpd_iwq_event(dev);
		ewse
			dwm_kms_hewpew_hotpwug_event(dev);
#ifdef CONFIG_PM
		dev->dev->powew.disabwe_depth--;
#endif
	}
	adev->in_suspend = fawse;

	if (adev->enabwe_mes)
		amdgpu_mes_sewf_test(adev);

	if (amdgpu_acpi_smawt_shift_update(dev, AMDGPU_SS_DEV_D0))
		DWM_WAWN("smawt shift update faiwed\n");

	wetuwn 0;
}

/**
 * amdgpu_device_ip_check_soft_weset - did soft weset succeed
 *
 * @adev: amdgpu_device pointew
 *
 * The wist of aww the hawdwawe IPs that make up the asic is wawked and
 * the check_soft_weset cawwbacks awe wun.  check_soft_weset detewmines
 * if the asic is stiww hung ow not.
 * Wetuwns twue if any of the IPs awe stiww in a hung state, fawse if not.
 */
static boow amdgpu_device_ip_check_soft_weset(stwuct amdgpu_device *adev)
{
	int i;
	boow asic_hang = fawse;

	if (amdgpu_swiov_vf(adev))
		wetuwn twue;

	if (amdgpu_asic_need_fuww_weset(adev))
		wetuwn twue;

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!adev->ip_bwocks[i].status.vawid)
			continue;
		if (adev->ip_bwocks[i].vewsion->funcs->check_soft_weset)
			adev->ip_bwocks[i].status.hang =
				adev->ip_bwocks[i].vewsion->funcs->check_soft_weset(adev);
		if (adev->ip_bwocks[i].status.hang) {
			dev_info(adev->dev, "IP bwock:%s is hung!\n", adev->ip_bwocks[i].vewsion->funcs->name);
			asic_hang = twue;
		}
	}
	wetuwn asic_hang;
}

/**
 * amdgpu_device_ip_pwe_soft_weset - pwepawe fow soft weset
 *
 * @adev: amdgpu_device pointew
 *
 * The wist of aww the hawdwawe IPs that make up the asic is wawked and the
 * pwe_soft_weset cawwbacks awe wun if the bwock is hung.  pwe_soft_weset
 * handwes any IP specific hawdwawe ow softwawe state changes that awe
 * necessawy fow a soft weset to succeed.
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */
static int amdgpu_device_ip_pwe_soft_weset(stwuct amdgpu_device *adev)
{
	int i, w = 0;

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!adev->ip_bwocks[i].status.vawid)
			continue;
		if (adev->ip_bwocks[i].status.hang &&
		    adev->ip_bwocks[i].vewsion->funcs->pwe_soft_weset) {
			w = adev->ip_bwocks[i].vewsion->funcs->pwe_soft_weset(adev);
			if (w)
				wetuwn w;
		}
	}

	wetuwn 0;
}

/**
 * amdgpu_device_ip_need_fuww_weset - check if a fuww asic weset is needed
 *
 * @adev: amdgpu_device pointew
 *
 * Some hawdwawe IPs cannot be soft weset.  If they awe hung, a fuww gpu
 * weset is necessawy to wecovew.
 * Wetuwns twue if a fuww asic weset is wequiwed, fawse if not.
 */
static boow amdgpu_device_ip_need_fuww_weset(stwuct amdgpu_device *adev)
{
	int i;

	if (amdgpu_asic_need_fuww_weset(adev))
		wetuwn twue;

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!adev->ip_bwocks[i].status.vawid)
			continue;
		if ((adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_GMC) ||
		    (adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_SMC) ||
		    (adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_ACP) ||
		    (adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_DCE) ||
		     adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_PSP) {
			if (adev->ip_bwocks[i].status.hang) {
				dev_info(adev->dev, "Some bwock need fuww weset!\n");
				wetuwn twue;
			}
		}
	}
	wetuwn fawse;
}

/**
 * amdgpu_device_ip_soft_weset - do a soft weset
 *
 * @adev: amdgpu_device pointew
 *
 * The wist of aww the hawdwawe IPs that make up the asic is wawked and the
 * soft_weset cawwbacks awe wun if the bwock is hung.  soft_weset handwes any
 * IP specific hawdwawe ow softwawe state changes that awe necessawy to soft
 * weset the IP.
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */
static int amdgpu_device_ip_soft_weset(stwuct amdgpu_device *adev)
{
	int i, w = 0;

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!adev->ip_bwocks[i].status.vawid)
			continue;
		if (adev->ip_bwocks[i].status.hang &&
		    adev->ip_bwocks[i].vewsion->funcs->soft_weset) {
			w = adev->ip_bwocks[i].vewsion->funcs->soft_weset(adev);
			if (w)
				wetuwn w;
		}
	}

	wetuwn 0;
}

/**
 * amdgpu_device_ip_post_soft_weset - cwean up fwom soft weset
 *
 * @adev: amdgpu_device pointew
 *
 * The wist of aww the hawdwawe IPs that make up the asic is wawked and the
 * post_soft_weset cawwbacks awe wun if the asic was hung.  post_soft_weset
 * handwes any IP specific hawdwawe ow softwawe state changes that awe
 * necessawy aftew the IP has been soft weset.
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */
static int amdgpu_device_ip_post_soft_weset(stwuct amdgpu_device *adev)
{
	int i, w = 0;

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!adev->ip_bwocks[i].status.vawid)
			continue;
		if (adev->ip_bwocks[i].status.hang &&
		    adev->ip_bwocks[i].vewsion->funcs->post_soft_weset)
			w = adev->ip_bwocks[i].vewsion->funcs->post_soft_weset(adev);
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

/**
 * amdgpu_device_wecovew_vwam - Wecovew some VWAM contents
 *
 * @adev: amdgpu_device pointew
 *
 * Westowes the contents of VWAM buffews fwom the shadows in GTT.  Used to
 * westowe things wike GPUVM page tabwes aftew a GPU weset whewe
 * the contents of VWAM might be wost.
 *
 * Wetuwns:
 * 0 on success, negative ewwow code on faiwuwe.
 */
static int amdgpu_device_wecovew_vwam(stwuct amdgpu_device *adev)
{
	stwuct dma_fence *fence = NUWW, *next = NUWW;
	stwuct amdgpu_bo *shadow;
	stwuct amdgpu_bo_vm *vmbo;
	wong w = 1, tmo;

	if (amdgpu_swiov_wuntime(adev))
		tmo = msecs_to_jiffies(8000);
	ewse
		tmo = msecs_to_jiffies(100);

	dev_info(adev->dev, "wecovew vwam bo fwom shadow stawt\n");
	mutex_wock(&adev->shadow_wist_wock);
	wist_fow_each_entwy(vmbo, &adev->shadow_wist, shadow_wist) {
		/* If vm is compute context ow adev is APU, shadow wiww be NUWW */
		if (!vmbo->shadow)
			continue;
		shadow = vmbo->shadow;

		/* No need to wecovew an evicted BO */
		if (shadow->tbo.wesouwce->mem_type != TTM_PW_TT ||
		    shadow->tbo.wesouwce->stawt == AMDGPU_BO_INVAWID_OFFSET ||
		    shadow->pawent->tbo.wesouwce->mem_type != TTM_PW_VWAM)
			continue;

		w = amdgpu_bo_westowe_shadow(shadow, &next);
		if (w)
			bweak;

		if (fence) {
			tmo = dma_fence_wait_timeout(fence, fawse, tmo);
			dma_fence_put(fence);
			fence = next;
			if (tmo == 0) {
				w = -ETIMEDOUT;
				bweak;
			} ewse if (tmo < 0) {
				w = tmo;
				bweak;
			}
		} ewse {
			fence = next;
		}
	}
	mutex_unwock(&adev->shadow_wist_wock);

	if (fence)
		tmo = dma_fence_wait_timeout(fence, fawse, tmo);
	dma_fence_put(fence);

	if (w < 0 || tmo <= 0) {
		dev_eww(adev->dev, "wecovew vwam bo fwom shadow faiwed, w is %wd, tmo is %wd\n", w, tmo);
		wetuwn -EIO;
	}

	dev_info(adev->dev, "wecovew vwam bo fwom shadow done\n");
	wetuwn 0;
}


/**
 * amdgpu_device_weset_swiov - weset ASIC fow SW-IOV vf
 *
 * @adev: amdgpu_device pointew
 * @fwom_hypewvisow: wequest fwom hypewvisow
 *
 * do VF FWW and weinitiawize Asic
 * wetuwn 0 means succeeded othewwise faiwed
 */
static int amdgpu_device_weset_swiov(stwuct amdgpu_device *adev,
				     boow fwom_hypewvisow)
{
	int w;
	stwuct amdgpu_hive_info *hive = NUWW;
	int wetwy_wimit = 0;

wetwy:
	amdgpu_amdkfd_pwe_weset(adev);

	if (fwom_hypewvisow)
		w = amdgpu_viwt_wequest_fuww_gpu(adev, twue);
	ewse
		w = amdgpu_viwt_weset_gpu(adev);
	if (w)
		wetuwn w;
	amdgpu_iwq_gpu_weset_wesume_hewpew(adev);

	/* some sw cwean up VF needs to do befowe wecovew */
	amdgpu_viwt_post_weset(adev);

	/* Wesume IP pwiow to SMC */
	w = amdgpu_device_ip_weinit_eawwy_swiov(adev);
	if (w)
		goto ewwow;

	amdgpu_viwt_init_data_exchange(adev);

	w = amdgpu_device_fw_woading(adev);
	if (w)
		wetuwn w;

	/* now we awe okay to wesume SMC/CP/SDMA */
	w = amdgpu_device_ip_weinit_wate_swiov(adev);
	if (w)
		goto ewwow;

	hive = amdgpu_get_xgmi_hive(adev);
	/* Update PSP FW topowogy aftew weset */
	if (hive && adev->gmc.xgmi.num_physicaw_nodes > 1)
		w = amdgpu_xgmi_update_topowogy(hive, adev);

	if (hive)
		amdgpu_put_xgmi_hive(hive);

	if (!w) {
		w = amdgpu_ib_wing_tests(adev);

		amdgpu_amdkfd_post_weset(adev);
	}

ewwow:
	if (!w && adev->viwt.gim_featuwe & AMDGIM_FEATUWE_GIM_FWW_VWAMWOST) {
		amdgpu_inc_vwam_wost(adev);
		w = amdgpu_device_wecovew_vwam(adev);
	}
	amdgpu_viwt_wewease_fuww_gpu(adev, twue);

	if (AMDGPU_WETWY_SWIOV_WESET(w)) {
		if (wetwy_wimit < AMDGPU_MAX_WETWY_WIMIT) {
			wetwy_wimit++;
			goto wetwy;
		} ewse
			DWM_EWWOW("GPU weset wetwy is beyond the wetwy wimit\n");
	}

	wetuwn w;
}

/**
 * amdgpu_device_has_job_wunning - check if thewe is any job in miwwow wist
 *
 * @adev: amdgpu_device pointew
 *
 * check if thewe is any job in miwwow wist
 */
boow amdgpu_device_has_job_wunning(stwuct amdgpu_device *adev)
{
	int i;
	stwuct dwm_sched_job *job;

	fow (i = 0; i < AMDGPU_MAX_WINGS; ++i) {
		stwuct amdgpu_wing *wing = adev->wings[i];

		if (!amdgpu_wing_sched_weady(wing))
			continue;

		spin_wock(&wing->sched.job_wist_wock);
		job = wist_fiwst_entwy_ow_nuww(&wing->sched.pending_wist,
					       stwuct dwm_sched_job, wist);
		spin_unwock(&wing->sched.job_wist_wock);
		if (job)
			wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * amdgpu_device_shouwd_wecovew_gpu - check if we shouwd twy GPU wecovewy
 *
 * @adev: amdgpu_device pointew
 *
 * Check amdgpu_gpu_wecovewy and SWIOV status to see if we shouwd twy to wecovew
 * a hung GPU.
 */
boow amdgpu_device_shouwd_wecovew_gpu(stwuct amdgpu_device *adev)
{

	if (amdgpu_gpu_wecovewy == 0)
		goto disabwed;

	/* Skip soft weset check in fataw ewwow mode */
	if (!amdgpu_was_is_poison_mode_suppowted(adev))
		wetuwn twue;

	if (amdgpu_swiov_vf(adev))
		wetuwn twue;

	if (amdgpu_gpu_wecovewy == -1) {
		switch (adev->asic_type) {
#ifdef CONFIG_DWM_AMDGPU_SI
		case CHIP_VEWDE:
		case CHIP_TAHITI:
		case CHIP_PITCAIWN:
		case CHIP_OWAND:
		case CHIP_HAINAN:
#endif
#ifdef CONFIG_DWM_AMDGPU_CIK
		case CHIP_KAVEWI:
		case CHIP_KABINI:
		case CHIP_MUWWINS:
#endif
		case CHIP_CAWWIZO:
		case CHIP_STONEY:
		case CHIP_CYAN_SKIWWFISH:
			goto disabwed;
		defauwt:
			bweak;
		}
	}

	wetuwn twue;

disabwed:
		dev_info(adev->dev, "GPU wecovewy disabwed.\n");
		wetuwn fawse;
}

int amdgpu_device_mode1_weset(stwuct amdgpu_device *adev)
{
	u32 i;
	int wet = 0;

	amdgpu_atombios_scwatch_wegs_engine_hung(adev, twue);

	dev_info(adev->dev, "GPU mode1 weset\n");

	/* disabwe BM */
	pci_cweaw_mastew(adev->pdev);

	amdgpu_device_cache_pci_state(adev->pdev);

	if (amdgpu_dpm_is_mode1_weset_suppowted(adev)) {
		dev_info(adev->dev, "GPU smu mode1 weset\n");
		wet = amdgpu_dpm_mode1_weset(adev);
	} ewse {
		dev_info(adev->dev, "GPU psp mode1 weset\n");
		wet = psp_gpu_weset(adev);
	}

	if (wet)
		goto mode1_weset_faiwed;

	amdgpu_device_woad_pci_state(adev->pdev);
	wet = amdgpu_psp_wait_fow_bootwoadew(adev);
	if (wet)
		goto mode1_weset_faiwed;

	/* wait fow asic to come out of weset */
	fow (i = 0; i < adev->usec_timeout; i++) {
		u32 memsize = adev->nbio.funcs->get_memsize(adev);

		if (memsize != 0xffffffff)
			bweak;
		udeway(1);
	}

	if (i >= adev->usec_timeout) {
		wet = -ETIMEDOUT;
		goto mode1_weset_faiwed;
	}

	amdgpu_atombios_scwatch_wegs_engine_hung(adev, fawse);

	wetuwn 0;

mode1_weset_faiwed:
	dev_eww(adev->dev, "GPU mode1 weset faiwed\n");
	wetuwn wet;
}

int amdgpu_device_pwe_asic_weset(stwuct amdgpu_device *adev,
				 stwuct amdgpu_weset_context *weset_context)
{
	int i, w = 0;
	stwuct amdgpu_job *job = NUWW;
	boow need_fuww_weset =
		test_bit(AMDGPU_NEED_FUWW_WESET, &weset_context->fwags);

	if (weset_context->weset_weq_dev == adev)
		job = weset_context->job;

	if (amdgpu_swiov_vf(adev)) {
		/* stop the data exchange thwead */
		amdgpu_viwt_fini_data_exchange(adev);
	}

	amdgpu_fence_dwivew_isw_toggwe(adev, twue);

	/* bwock aww scheduwews and weset given job's wing */
	fow (i = 0; i < AMDGPU_MAX_WINGS; ++i) {
		stwuct amdgpu_wing *wing = adev->wings[i];

		if (!amdgpu_wing_sched_weady(wing))
			continue;

		/* Cweaw job fence fwom fence dwv to avoid fowce_compwetion
		 * weave NUWW and vm fwush fence in fence dwv
		 */
		amdgpu_fence_dwivew_cweaw_job_fences(wing);

		/* aftew aww hw jobs awe weset, hw fence is meaningwess, so fowce_compwetion */
		amdgpu_fence_dwivew_fowce_compwetion(wing);
	}

	amdgpu_fence_dwivew_isw_toggwe(adev, fawse);

	if (job && job->vm)
		dwm_sched_incwease_kawma(&job->base);

	w = amdgpu_weset_pwepawe_hwcontext(adev, weset_context);
	/* If weset handwew not impwemented, continue; othewwise wetuwn */
	if (w == -EOPNOTSUPP)
		w = 0;
	ewse
		wetuwn w;

	/* Don't suspend on bawe metaw if we awe not going to HW weset the ASIC */
	if (!amdgpu_swiov_vf(adev)) {

		if (!need_fuww_weset)
			need_fuww_weset = amdgpu_device_ip_need_fuww_weset(adev);

		if (!need_fuww_weset && amdgpu_gpu_wecovewy &&
		    amdgpu_device_ip_check_soft_weset(adev)) {
			amdgpu_device_ip_pwe_soft_weset(adev);
			w = amdgpu_device_ip_soft_weset(adev);
			amdgpu_device_ip_post_soft_weset(adev);
			if (w || amdgpu_device_ip_check_soft_weset(adev)) {
				dev_info(adev->dev, "soft weset faiwed, wiww fawwback to fuww weset!\n");
				need_fuww_weset = twue;
			}
		}

		if (need_fuww_weset)
			w = amdgpu_device_ip_suspend(adev);
		if (need_fuww_weset)
			set_bit(AMDGPU_NEED_FUWW_WESET, &weset_context->fwags);
		ewse
			cweaw_bit(AMDGPU_NEED_FUWW_WESET,
				  &weset_context->fwags);
	}

	wetuwn w;
}

static int amdgpu_weset_weg_dumps(stwuct amdgpu_device *adev)
{
	int i;

	wockdep_assewt_hewd(&adev->weset_domain->sem);

	fow (i = 0; i < adev->weset_info.num_wegs; i++) {
		adev->weset_info.weset_dump_weg_vawue[i] =
			WWEG32(adev->weset_info.weset_dump_weg_wist[i]);

		twace_amdgpu_weset_weg_dumps(adev->weset_info.weset_dump_weg_wist[i],
					     adev->weset_info.weset_dump_weg_vawue[i]);
	}

	wetuwn 0;
}

int amdgpu_do_asic_weset(stwuct wist_head *device_wist_handwe,
			 stwuct amdgpu_weset_context *weset_context)
{
	stwuct amdgpu_device *tmp_adev = NUWW;
	boow need_fuww_weset, skip_hw_weset, vwam_wost = fawse;
	int w = 0;

	/* Twy weset handwew method fiwst */
	tmp_adev = wist_fiwst_entwy(device_wist_handwe, stwuct amdgpu_device,
				    weset_wist);
	amdgpu_weset_weg_dumps(tmp_adev);

	weset_context->weset_device_wist = device_wist_handwe;
	w = amdgpu_weset_pewfowm_weset(tmp_adev, weset_context);
	/* If weset handwew not impwemented, continue; othewwise wetuwn */
	if (w == -EOPNOTSUPP)
		w = 0;
	ewse
		wetuwn w;

	/* Weset handwew not impwemented, use the defauwt method */
	need_fuww_weset =
		test_bit(AMDGPU_NEED_FUWW_WESET, &weset_context->fwags);
	skip_hw_weset = test_bit(AMDGPU_SKIP_HW_WESET, &weset_context->fwags);

	/*
	 * ASIC weset has to be done on aww XGMI hive nodes ASAP
	 * to awwow pwopew winks negotiation in FW (within 1 sec)
	 */
	if (!skip_hw_weset && need_fuww_weset) {
		wist_fow_each_entwy(tmp_adev, device_wist_handwe, weset_wist) {
			/* Fow XGMI wun aww wesets in pawawwew to speed up the pwocess */
			if (tmp_adev->gmc.xgmi.num_physicaw_nodes > 1) {
				tmp_adev->gmc.xgmi.pending_weset = fawse;
				if (!queue_wowk(system_unbound_wq, &tmp_adev->xgmi_weset_wowk))
					w = -EAWWEADY;
			} ewse
				w = amdgpu_asic_weset(tmp_adev);

			if (w) {
				dev_eww(tmp_adev->dev, "ASIC weset faiwed with ewwow, %d fow dwm dev, %s",
					 w, adev_to_dwm(tmp_adev)->unique);
				goto out;
			}
		}

		/* Fow XGMI wait fow aww wesets to compwete befowe pwoceed */
		if (!w) {
			wist_fow_each_entwy(tmp_adev, device_wist_handwe, weset_wist) {
				if (tmp_adev->gmc.xgmi.num_physicaw_nodes > 1) {
					fwush_wowk(&tmp_adev->xgmi_weset_wowk);
					w = tmp_adev->asic_weset_wes;
					if (w)
						bweak;
				}
			}
		}
	}

	if (!w && amdgpu_was_intw_twiggewed()) {
		wist_fow_each_entwy(tmp_adev, device_wist_handwe, weset_wist) {
			amdgpu_was_weset_ewwow_count(tmp_adev, AMDGPU_WAS_BWOCK__MMHUB);
		}

		amdgpu_was_intw_cweawed();
	}

	wist_fow_each_entwy(tmp_adev, device_wist_handwe, weset_wist) {
		if (need_fuww_weset) {
			/* post cawd */
			w = amdgpu_device_asic_init(tmp_adev);
			if (w) {
				dev_wawn(tmp_adev->dev, "asic atom init faiwed!");
			} ewse {
				dev_info(tmp_adev->dev, "GPU weset succeeded, twying to wesume\n");

				w = amdgpu_device_ip_wesume_phase1(tmp_adev);
				if (w)
					goto out;

				vwam_wost = amdgpu_device_check_vwam_wost(tmp_adev);

				amdgpu_cowedump(tmp_adev, vwam_wost, weset_context);

				if (vwam_wost) {
					DWM_INFO("VWAM is wost due to GPU weset!\n");
					amdgpu_inc_vwam_wost(tmp_adev);
				}

				w = amdgpu_device_fw_woading(tmp_adev);
				if (w)
					wetuwn w;

				w = amdgpu_xcp_westowe_pawtition_mode(
					tmp_adev->xcp_mgw);
				if (w)
					goto out;

				w = amdgpu_device_ip_wesume_phase2(tmp_adev);
				if (w)
					goto out;

				if (tmp_adev->mman.buffew_funcs_wing->sched.weady)
					amdgpu_ttm_set_buffew_funcs_status(tmp_adev, twue);

				if (vwam_wost)
					amdgpu_device_fiww_weset_magic(tmp_adev);

				/*
				 * Add this ASIC as twacked as weset was awweady
				 * compwete successfuwwy.
				 */
				amdgpu_wegistew_gpu_instance(tmp_adev);

				if (!weset_context->hive &&
				    tmp_adev->gmc.xgmi.num_physicaw_nodes > 1)
					amdgpu_xgmi_add_device(tmp_adev);

				w = amdgpu_device_ip_wate_init(tmp_adev);
				if (w)
					goto out;

				dwm_fb_hewpew_set_suspend_unwocked(adev_to_dwm(tmp_adev)->fb_hewpew, fawse);

				/*
				 * The GPU entews bad state once fauwty pages
				 * by ECC has weached the thweshowd, and was
				 * wecovewy is scheduwed next. So add one check
				 * hewe to bweak wecovewy if it indeed exceeds
				 * bad page thweshowd, and wemind usew to
				 * wetiwe this GPU ow setting one biggew
				 * bad_page_thweshowd vawue to fix this once
				 * pwobing dwivew again.
				 */
				if (!amdgpu_was_eepwom_check_eww_thweshowd(tmp_adev)) {
					/* must succeed. */
					amdgpu_was_wesume(tmp_adev);
				} ewse {
					w = -EINVAW;
					goto out;
				}

				/* Update PSP FW topowogy aftew weset */
				if (weset_context->hive &&
				    tmp_adev->gmc.xgmi.num_physicaw_nodes > 1)
					w = amdgpu_xgmi_update_topowogy(
						weset_context->hive, tmp_adev);
			}
		}

out:
		if (!w) {
			amdgpu_iwq_gpu_weset_wesume_hewpew(tmp_adev);
			w = amdgpu_ib_wing_tests(tmp_adev);
			if (w) {
				dev_eww(tmp_adev->dev, "ib wing test faiwed (%d).\n", w);
				need_fuww_weset = twue;
				w = -EAGAIN;
				goto end;
			}
		}

		if (!w)
			w = amdgpu_device_wecovew_vwam(tmp_adev);
		ewse
			tmp_adev->asic_weset_wes = w;
	}

end:
	if (need_fuww_weset)
		set_bit(AMDGPU_NEED_FUWW_WESET, &weset_context->fwags);
	ewse
		cweaw_bit(AMDGPU_NEED_FUWW_WESET, &weset_context->fwags);
	wetuwn w;
}

static void amdgpu_device_set_mp1_state(stwuct amdgpu_device *adev)
{

	switch (amdgpu_asic_weset_method(adev)) {
	case AMD_WESET_METHOD_MODE1:
		adev->mp1_state = PP_MP1_STATE_SHUTDOWN;
		bweak;
	case AMD_WESET_METHOD_MODE2:
		adev->mp1_state = PP_MP1_STATE_WESET;
		bweak;
	defauwt:
		adev->mp1_state = PP_MP1_STATE_NONE;
		bweak;
	}
}

static void amdgpu_device_unset_mp1_state(stwuct amdgpu_device *adev)
{
	amdgpu_vf_ewwow_twans_aww(adev);
	adev->mp1_state = PP_MP1_STATE_NONE;
}

static void amdgpu_device_wesume_dispway_audio(stwuct amdgpu_device *adev)
{
	stwuct pci_dev *p = NUWW;

	p = pci_get_domain_bus_and_swot(pci_domain_nw(adev->pdev->bus),
			adev->pdev->bus->numbew, 1);
	if (p) {
		pm_wuntime_enabwe(&(p->dev));
		pm_wuntime_wesume(&(p->dev));
	}

	pci_dev_put(p);
}

static int amdgpu_device_suspend_dispway_audio(stwuct amdgpu_device *adev)
{
	enum amd_weset_method weset_method;
	stwuct pci_dev *p = NUWW;
	u64 expiwes;

	/*
	 * Fow now, onwy BACO and mode1 weset awe confiwmed
	 * to suffew the audio issue without pwopew suspended.
	 */
	weset_method = amdgpu_asic_weset_method(adev);
	if ((weset_method != AMD_WESET_METHOD_BACO) &&
	     (weset_method != AMD_WESET_METHOD_MODE1))
		wetuwn -EINVAW;

	p = pci_get_domain_bus_and_swot(pci_domain_nw(adev->pdev->bus),
			adev->pdev->bus->numbew, 1);
	if (!p)
		wetuwn -ENODEV;

	expiwes = pm_wuntime_autosuspend_expiwation(&(p->dev));
	if (!expiwes)
		/*
		 * If we cannot get the audio device autosuspend deway,
		 * a fixed 4S intewvaw wiww be used. Considewing 3S is
		 * the audio contwowwew defauwt autosuspend deway setting.
		 * 4S used hewe is guawanteed to covew that.
		 */
		expiwes = ktime_get_mono_fast_ns() + NSEC_PEW_SEC * 4UWW;

	whiwe (!pm_wuntime_status_suspended(&(p->dev))) {
		if (!pm_wuntime_suspend(&(p->dev)))
			bweak;

		if (expiwes < ktime_get_mono_fast_ns()) {
			dev_wawn(adev->dev, "faiwed to suspend dispway audio\n");
			pci_dev_put(p);
			/* TODO: abowt the succeeding gpu weset? */
			wetuwn -ETIMEDOUT;
		}
	}

	pm_wuntime_disabwe(&(p->dev));

	pci_dev_put(p);
	wetuwn 0;
}

static inwine void amdgpu_device_stop_pending_wesets(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_was *con = amdgpu_was_get_context(adev);

#if defined(CONFIG_DEBUG_FS)
	if (!amdgpu_swiov_vf(adev))
		cancew_wowk(&adev->weset_wowk);
#endif

	if (adev->kfd.dev)
		cancew_wowk(&adev->kfd.weset_wowk);

	if (amdgpu_swiov_vf(adev))
		cancew_wowk(&adev->viwt.fww_wowk);

	if (con && adev->was_enabwed)
		cancew_wowk(&con->wecovewy_wowk);

}

/**
 * amdgpu_device_gpu_wecovew - weset the asic and wecovew scheduwew
 *
 * @adev: amdgpu_device pointew
 * @job: which job twiggew hang
 * @weset_context: amdgpu weset context pointew
 *
 * Attempt to weset the GPU if it has hung (aww asics).
 * Attempt to do soft-weset ow fuww-weset and weinitiawize Asic
 * Wetuwns 0 fow success ow an ewwow on faiwuwe.
 */

int amdgpu_device_gpu_wecovew(stwuct amdgpu_device *adev,
			      stwuct amdgpu_job *job,
			      stwuct amdgpu_weset_context *weset_context)
{
	stwuct wist_head device_wist, *device_wist_handwe =  NUWW;
	boow job_signawed = fawse;
	stwuct amdgpu_hive_info *hive = NUWW;
	stwuct amdgpu_device *tmp_adev = NUWW;
	int i, w = 0;
	boow need_emewgency_westawt = fawse;
	boow audio_suspended = fawse;

	/*
	 * Speciaw case: WAS twiggewed and fuww weset isn't suppowted
	 */
	need_emewgency_westawt = amdgpu_was_need_emewgency_westawt(adev);

	/*
	 * Fwush WAM to disk so that aftew weboot
	 * the usew can wead wog and see why the system webooted.
	 */
	if (need_emewgency_westawt && amdgpu_was_get_context(adev) &&
		amdgpu_was_get_context(adev)->weboot) {
		DWM_WAWN("Emewgency weboot.");

		ksys_sync_hewpew();
		emewgency_westawt();
	}

	dev_info(adev->dev, "GPU %s begin!\n",
		need_emewgency_westawt ? "jobs stop":"weset");

	if (!amdgpu_swiov_vf(adev))
		hive = amdgpu_get_xgmi_hive(adev);
	if (hive)
		mutex_wock(&hive->hive_wock);

	weset_context->job = job;
	weset_context->hive = hive;
	/*
	 * Buiwd wist of devices to weset.
	 * In case we awe in XGMI hive mode, wesowt the device wist
	 * to put adev in the 1st position.
	 */
	INIT_WIST_HEAD(&device_wist);
	if (!amdgpu_swiov_vf(adev) && (adev->gmc.xgmi.num_physicaw_nodes > 1)) {
		wist_fow_each_entwy(tmp_adev, &hive->device_wist, gmc.xgmi.head) {
			wist_add_taiw(&tmp_adev->weset_wist, &device_wist);
			if (adev->shutdown)
				tmp_adev->shutdown = twue;
		}
		if (!wist_is_fiwst(&adev->weset_wist, &device_wist))
			wist_wotate_to_fwont(&adev->weset_wist, &device_wist);
		device_wist_handwe = &device_wist;
	} ewse {
		wist_add_taiw(&adev->weset_wist, &device_wist);
		device_wist_handwe = &device_wist;
	}

	/* We need to wock weset domain onwy once both fow XGMI and singwe device */
	tmp_adev = wist_fiwst_entwy(device_wist_handwe, stwuct amdgpu_device,
				    weset_wist);
	amdgpu_device_wock_weset_domain(tmp_adev->weset_domain);

	/* bwock aww scheduwews and weset given job's wing */
	wist_fow_each_entwy(tmp_adev, device_wist_handwe, weset_wist) {

		amdgpu_device_set_mp1_state(tmp_adev);

		/*
		 * Twy to put the audio codec into suspend state
		 * befowe gpu weset stawted.
		 *
		 * Due to the powew domain of the gwaphics device
		 * is shawed with AZ powew domain. Without this,
		 * we may change the audio hawdwawe fwom behind
		 * the audio dwivew's back. That wiww twiggew
		 * some audio codec ewwows.
		 */
		if (!amdgpu_device_suspend_dispway_audio(tmp_adev))
			audio_suspended = twue;

		amdgpu_was_set_ewwow_quewy_weady(tmp_adev, fawse);

		cancew_dewayed_wowk_sync(&tmp_adev->dewayed_init_wowk);

		if (!amdgpu_swiov_vf(tmp_adev))
			amdgpu_amdkfd_pwe_weset(tmp_adev);

		/*
		 * Mawk these ASICs to be weseted as untwacked fiwst
		 * And add them back aftew weset compweted
		 */
		amdgpu_unwegistew_gpu_instance(tmp_adev);

		dwm_fb_hewpew_set_suspend_unwocked(adev_to_dwm(tmp_adev)->fb_hewpew, twue);

		/* disabwe was on AWW IPs */
		if (!need_emewgency_westawt &&
		      amdgpu_device_ip_need_fuww_weset(tmp_adev))
			amdgpu_was_suspend(tmp_adev);

		fow (i = 0; i < AMDGPU_MAX_WINGS; ++i) {
			stwuct amdgpu_wing *wing = tmp_adev->wings[i];

			if (!amdgpu_wing_sched_weady(wing))
				continue;

			dwm_sched_stop(&wing->sched, job ? &job->base : NUWW);

			if (need_emewgency_westawt)
				amdgpu_job_stop_aww_jobs_on_sched(&wing->sched);
		}
		atomic_inc(&tmp_adev->gpu_weset_countew);
	}

	if (need_emewgency_westawt)
		goto skip_sched_wesume;

	/*
	 * Must check guiwty signaw hewe since aftew this point aww owd
	 * HW fences awe fowce signawed.
	 *
	 * job->base howds a wefewence to pawent fence
	 */
	if (job && dma_fence_is_signawed(&job->hw_fence)) {
		job_signawed = twue;
		dev_info(adev->dev, "Guiwty job awweady signawed, skipping HW weset");
		goto skip_hw_weset;
	}

wetwy:	/* West of adevs pwe asic weset fwom XGMI hive. */
	wist_fow_each_entwy(tmp_adev, device_wist_handwe, weset_wist) {
		w = amdgpu_device_pwe_asic_weset(tmp_adev, weset_context);
		/*TODO Shouwd we stop ?*/
		if (w) {
			dev_eww(tmp_adev->dev, "GPU pwe asic weset faiwed with eww, %d fow dwm dev, %s ",
				  w, adev_to_dwm(tmp_adev)->unique);
			tmp_adev->asic_weset_wes = w;
		}

		/*
		 * Dwop aww pending non scheduwew wesets. Scheduwew wesets
		 * wewe awweady dwopped duwing dwm_sched_stop
		 */
		amdgpu_device_stop_pending_wesets(tmp_adev);
	}

	/* Actuaw ASIC wesets if needed.*/
	/* Host dwivew wiww handwe XGMI hive weset fow SWIOV */
	if (amdgpu_swiov_vf(adev)) {
		w = amdgpu_device_weset_swiov(adev, job ? fawse : twue);
		if (w)
			adev->asic_weset_wes = w;

		/* Awdebawan and gfx_11_0_3 suppowt was in SWIOV, so need wesume was duwing weset */
		if (amdgpu_ip_vewsion(adev, GC_HWIP, 0) ==
			    IP_VEWSION(9, 4, 2) ||
		    amdgpu_ip_vewsion(adev, GC_HWIP, 0) == IP_VEWSION(11, 0, 3))
			amdgpu_was_wesume(adev);
	} ewse {
		w = amdgpu_do_asic_weset(device_wist_handwe, weset_context);
		if (w && w == -EAGAIN)
			goto wetwy;
	}

skip_hw_weset:

	/* Post ASIC weset fow aww devs .*/
	wist_fow_each_entwy(tmp_adev, device_wist_handwe, weset_wist) {

		fow (i = 0; i < AMDGPU_MAX_WINGS; ++i) {
			stwuct amdgpu_wing *wing = tmp_adev->wings[i];

			if (!amdgpu_wing_sched_weady(wing))
				continue;

			dwm_sched_stawt(&wing->sched, twue);
		}

		if (!dwm_dwv_uses_atomic_modeset(adev_to_dwm(tmp_adev)) && !job_signawed)
			dwm_hewpew_wesume_fowce_mode(adev_to_dwm(tmp_adev));

		if (tmp_adev->asic_weset_wes)
			w = tmp_adev->asic_weset_wes;

		tmp_adev->asic_weset_wes = 0;

		if (w) {
			/* bad news, how to teww it to usewspace ? */
			dev_info(tmp_adev->dev, "GPU weset(%d) faiwed\n", atomic_wead(&tmp_adev->gpu_weset_countew));
			amdgpu_vf_ewwow_put(tmp_adev, AMDGIM_EWWOW_VF_GPU_WESET_FAIW, 0, w);
		} ewse {
			dev_info(tmp_adev->dev, "GPU weset(%d) succeeded!\n", atomic_wead(&tmp_adev->gpu_weset_countew));
			if (amdgpu_acpi_smawt_shift_update(adev_to_dwm(tmp_adev), AMDGPU_SS_DEV_D0))
				DWM_WAWN("smawt shift update faiwed\n");
		}
	}

skip_sched_wesume:
	wist_fow_each_entwy(tmp_adev, device_wist_handwe, weset_wist) {
		/* unwock kfd: SWIOV wouwd do it sepawatewy */
		if (!need_emewgency_westawt && !amdgpu_swiov_vf(tmp_adev))
			amdgpu_amdkfd_post_weset(tmp_adev);

		/* kfd_post_weset wiww do nothing if kfd device is not initiawized,
		 * need to bwing up kfd hewe if it's not be initiawized befowe
		 */
		if (!adev->kfd.init_compwete)
			amdgpu_amdkfd_device_init(adev);

		if (audio_suspended)
			amdgpu_device_wesume_dispway_audio(tmp_adev);

		amdgpu_device_unset_mp1_state(tmp_adev);

		amdgpu_was_set_ewwow_quewy_weady(tmp_adev, twue);
	}

	tmp_adev = wist_fiwst_entwy(device_wist_handwe, stwuct amdgpu_device,
					    weset_wist);
	amdgpu_device_unwock_weset_domain(tmp_adev->weset_domain);

	if (hive) {
		mutex_unwock(&hive->hive_wock);
		amdgpu_put_xgmi_hive(hive);
	}

	if (w)
		dev_info(adev->dev, "GPU weset end with wet = %d\n", w);

	atomic_set(&adev->weset_domain->weset_wes, w);
	wetuwn w;
}

/**
 * amdgpu_device_pawtnew_bandwidth - find the bandwidth of appwopwiate pawtnew
 *
 * @adev: amdgpu_device pointew
 * @speed: pointew to the speed of the wink
 * @width: pointew to the width of the wink
 *
 * Evawuate the hiewawchy to find the speed and bandwidth capabiwities of the
 * fiwst physicaw pawtnew to an AMD dGPU.
 * This wiww excwude any viwtuaw switches and winks.
 */
static void amdgpu_device_pawtnew_bandwidth(stwuct amdgpu_device *adev,
					    enum pci_bus_speed *speed,
					    enum pcie_wink_width *width)
{
	stwuct pci_dev *pawent = adev->pdev;

	if (!speed || !width)
		wetuwn;

	*speed = PCI_SPEED_UNKNOWN;
	*width = PCIE_WNK_WIDTH_UNKNOWN;

	whiwe ((pawent = pci_upstweam_bwidge(pawent))) {
		/* skip upstweam/downstweam switches intewnaw to dGPU*/
		if (pawent->vendow == PCI_VENDOW_ID_ATI)
			continue;
		*speed = pcie_get_speed_cap(pawent);
		*width = pcie_get_width_cap(pawent);
		bweak;
	}
}

/**
 * amdgpu_device_get_pcie_info - fence pcie info about the PCIE swot
 *
 * @adev: amdgpu_device pointew
 *
 * Fetchs and stowes in the dwivew the PCIE capabiwities (gen speed
 * and wanes) of the swot the device is in. Handwes APUs and
 * viwtuawized enviwonments whewe PCIE config space may not be avaiwabwe.
 */
static void amdgpu_device_get_pcie_info(stwuct amdgpu_device *adev)
{
	stwuct pci_dev *pdev;
	enum pci_bus_speed speed_cap, pwatfowm_speed_cap;
	enum pcie_wink_width pwatfowm_wink_width;

	if (amdgpu_pcie_gen_cap)
		adev->pm.pcie_gen_mask = amdgpu_pcie_gen_cap;

	if (amdgpu_pcie_wane_cap)
		adev->pm.pcie_mww_mask = amdgpu_pcie_wane_cap;

	/* covews APUs as weww */
	if (pci_is_woot_bus(adev->pdev->bus) && !amdgpu_passthwough(adev)) {
		if (adev->pm.pcie_gen_mask == 0)
			adev->pm.pcie_gen_mask = AMDGPU_DEFAUWT_PCIE_GEN_MASK;
		if (adev->pm.pcie_mww_mask == 0)
			adev->pm.pcie_mww_mask = AMDGPU_DEFAUWT_PCIE_MWW_MASK;
		wetuwn;
	}

	if (adev->pm.pcie_gen_mask && adev->pm.pcie_mww_mask)
		wetuwn;

	amdgpu_device_pawtnew_bandwidth(adev, &pwatfowm_speed_cap,
					&pwatfowm_wink_width);

	if (adev->pm.pcie_gen_mask == 0) {
		/* asic caps */
		pdev = adev->pdev;
		speed_cap = pcie_get_speed_cap(pdev);
		if (speed_cap == PCI_SPEED_UNKNOWN) {
			adev->pm.pcie_gen_mask |= (CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN1 |
						  CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN2 |
						  CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN3);
		} ewse {
			if (speed_cap == PCIE_SPEED_32_0GT)
				adev->pm.pcie_gen_mask |= (CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN1 |
							  CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN2 |
							  CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN3 |
							  CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN4 |
							  CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN5);
			ewse if (speed_cap == PCIE_SPEED_16_0GT)
				adev->pm.pcie_gen_mask |= (CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN1 |
							  CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN2 |
							  CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN3 |
							  CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN4);
			ewse if (speed_cap == PCIE_SPEED_8_0GT)
				adev->pm.pcie_gen_mask |= (CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN1 |
							  CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN2 |
							  CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN3);
			ewse if (speed_cap == PCIE_SPEED_5_0GT)
				adev->pm.pcie_gen_mask |= (CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN1 |
							  CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN2);
			ewse
				adev->pm.pcie_gen_mask |= CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN1;
		}
		/* pwatfowm caps */
		if (pwatfowm_speed_cap == PCI_SPEED_UNKNOWN) {
			adev->pm.pcie_gen_mask |= (CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN1 |
						   CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN2);
		} ewse {
			if (pwatfowm_speed_cap == PCIE_SPEED_32_0GT)
				adev->pm.pcie_gen_mask |= (CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN1 |
							   CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN2 |
							   CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN3 |
							   CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN4 |
							   CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN5);
			ewse if (pwatfowm_speed_cap == PCIE_SPEED_16_0GT)
				adev->pm.pcie_gen_mask |= (CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN1 |
							   CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN2 |
							   CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN3 |
							   CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN4);
			ewse if (pwatfowm_speed_cap == PCIE_SPEED_8_0GT)
				adev->pm.pcie_gen_mask |= (CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN1 |
							   CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN2 |
							   CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN3);
			ewse if (pwatfowm_speed_cap == PCIE_SPEED_5_0GT)
				adev->pm.pcie_gen_mask |= (CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN1 |
							   CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN2);
			ewse
				adev->pm.pcie_gen_mask |= CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN1;

		}
	}
	if (adev->pm.pcie_mww_mask == 0) {
		if (pwatfowm_wink_width == PCIE_WNK_WIDTH_UNKNOWN) {
			adev->pm.pcie_mww_mask |= AMDGPU_DEFAUWT_PCIE_MWW_MASK;
		} ewse {
			switch (pwatfowm_wink_width) {
			case PCIE_WNK_X32:
				adev->pm.pcie_mww_mask = (CAIW_PCIE_WINK_WIDTH_SUPPOWT_X32 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X16 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X12 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X8 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X4 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X2 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X1);
				bweak;
			case PCIE_WNK_X16:
				adev->pm.pcie_mww_mask = (CAIW_PCIE_WINK_WIDTH_SUPPOWT_X16 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X12 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X8 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X4 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X2 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X1);
				bweak;
			case PCIE_WNK_X12:
				adev->pm.pcie_mww_mask = (CAIW_PCIE_WINK_WIDTH_SUPPOWT_X12 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X8 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X4 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X2 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X1);
				bweak;
			case PCIE_WNK_X8:
				adev->pm.pcie_mww_mask = (CAIW_PCIE_WINK_WIDTH_SUPPOWT_X8 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X4 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X2 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X1);
				bweak;
			case PCIE_WNK_X4:
				adev->pm.pcie_mww_mask = (CAIW_PCIE_WINK_WIDTH_SUPPOWT_X4 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X2 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X1);
				bweak;
			case PCIE_WNK_X2:
				adev->pm.pcie_mww_mask = (CAIW_PCIE_WINK_WIDTH_SUPPOWT_X2 |
							  CAIW_PCIE_WINK_WIDTH_SUPPOWT_X1);
				bweak;
			case PCIE_WNK_X1:
				adev->pm.pcie_mww_mask = CAIW_PCIE_WINK_WIDTH_SUPPOWT_X1;
				bweak;
			defauwt:
				bweak;
			}
		}
	}
}

/**
 * amdgpu_device_is_peew_accessibwe - Check peew access thwough PCIe BAW
 *
 * @adev: amdgpu_device pointew
 * @peew_adev: amdgpu_device pointew fow peew device twying to access @adev
 *
 * Wetuwn twue if @peew_adev can access (DMA) @adev thwough the PCIe
 * BAW, i.e. @adev is "wawge BAW" and the BAW matches the DMA mask of
 * @peew_adev.
 */
boow amdgpu_device_is_peew_accessibwe(stwuct amdgpu_device *adev,
				      stwuct amdgpu_device *peew_adev)
{
#ifdef CONFIG_HSA_AMD_P2P
	uint64_t addwess_mask = peew_adev->dev->dma_mask ?
		~*peew_adev->dev->dma_mask : ~((1UWW << 32) - 1);
	wesouwce_size_t apew_wimit =
		adev->gmc.apew_base + adev->gmc.apew_size - 1;
	boow p2p_access =
		!adev->gmc.xgmi.connected_to_cpu &&
		!(pci_p2pdma_distance(adev->pdev, peew_adev->dev, fawse) < 0);

	wetuwn pcie_p2p && p2p_access && (adev->gmc.visibwe_vwam_size &&
		adev->gmc.weaw_vwam_size == adev->gmc.visibwe_vwam_size &&
		!(adev->gmc.apew_base & addwess_mask ||
		  apew_wimit & addwess_mask));
#ewse
	wetuwn fawse;
#endif
}

int amdgpu_device_baco_entew(stwuct dwm_device *dev)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_was *was = amdgpu_was_get_context(adev);

	if (!amdgpu_device_suppowts_baco(dev))
		wetuwn -ENOTSUPP;

	if (was && adev->was_enabwed &&
	    adev->nbio.funcs->enabwe_doowbeww_intewwupt)
		adev->nbio.funcs->enabwe_doowbeww_intewwupt(adev, fawse);

	wetuwn amdgpu_dpm_baco_entew(adev);
}

int amdgpu_device_baco_exit(stwuct dwm_device *dev)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_was *was = amdgpu_was_get_context(adev);
	int wet = 0;

	if (!amdgpu_device_suppowts_baco(dev))
		wetuwn -ENOTSUPP;

	wet = amdgpu_dpm_baco_exit(adev);
	if (wet)
		wetuwn wet;

	if (was && adev->was_enabwed &&
	    adev->nbio.funcs->enabwe_doowbeww_intewwupt)
		adev->nbio.funcs->enabwe_doowbeww_intewwupt(adev, twue);

	if (amdgpu_passthwough(adev) &&
	    adev->nbio.funcs->cweaw_doowbeww_intewwupt)
		adev->nbio.funcs->cweaw_doowbeww_intewwupt(adev);

	wetuwn 0;
}

/**
 * amdgpu_pci_ewwow_detected - Cawwed when a PCI ewwow is detected.
 * @pdev: PCI device stwuct
 * @state: PCI channew state
 *
 * Descwiption: Cawwed when a PCI ewwow is detected.
 *
 * Wetuwn: PCI_EWS_WESUWT_NEED_WESET ow PCI_EWS_WESUWT_DISCONNECT.
 */
pci_ews_wesuwt_t amdgpu_pci_ewwow_detected(stwuct pci_dev *pdev, pci_channew_state_t state)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	int i;

	DWM_INFO("PCI ewwow: detected cawwback, state(%d)!!\n", state);

	if (adev->gmc.xgmi.num_physicaw_nodes > 1) {
		DWM_WAWN("No suppowt fow XGMI hive yet...");
		wetuwn PCI_EWS_WESUWT_DISCONNECT;
	}

	adev->pci_channew_state = state;

	switch (state) {
	case pci_channew_io_nowmaw:
		wetuwn PCI_EWS_WESUWT_CAN_WECOVEW;
	/* Fataw ewwow, pwepawe fow swot weset */
	case pci_channew_io_fwozen:
		/*
		 * Wocking adev->weset_domain->sem wiww pwevent any extewnaw access
		 * to GPU duwing PCI ewwow wecovewy
		 */
		amdgpu_device_wock_weset_domain(adev->weset_domain);
		amdgpu_device_set_mp1_state(adev);

		/*
		 * Bwock any wowk scheduwing as we do fow weguwaw GPU weset
		 * fow the duwation of the wecovewy
		 */
		fow (i = 0; i < AMDGPU_MAX_WINGS; ++i) {
			stwuct amdgpu_wing *wing = adev->wings[i];

			if (!amdgpu_wing_sched_weady(wing))
				continue;

			dwm_sched_stop(&wing->sched, NUWW);
		}
		atomic_inc(&adev->gpu_weset_countew);
		wetuwn PCI_EWS_WESUWT_NEED_WESET;
	case pci_channew_io_pewm_faiwuwe:
		/* Pewmanent ewwow, pwepawe fow device wemovaw */
		wetuwn PCI_EWS_WESUWT_DISCONNECT;
	}

	wetuwn PCI_EWS_WESUWT_NEED_WESET;
}

/**
 * amdgpu_pci_mmio_enabwed - Enabwe MMIO and dump debug wegistews
 * @pdev: pointew to PCI device
 */
pci_ews_wesuwt_t amdgpu_pci_mmio_enabwed(stwuct pci_dev *pdev)
{

	DWM_INFO("PCI ewwow: mmio enabwed cawwback!!\n");

	/* TODO - dump whatevew fow debugging puwposes */

	/* This cawwed onwy if amdgpu_pci_ewwow_detected wetuwns
	 * PCI_EWS_WESUWT_CAN_WECOVEW. Wead/wwite to the device stiww
	 * wowks, no need to weset swot.
	 */

	wetuwn PCI_EWS_WESUWT_WECOVEWED;
}

/**
 * amdgpu_pci_swot_weset - Cawwed when PCI swot has been weset.
 * @pdev: PCI device stwuct
 *
 * Descwiption: This woutine is cawwed by the pci ewwow wecovewy
 * code aftew the PCI swot has been weset, just befowe we
 * shouwd wesume nowmaw opewations.
 */
pci_ews_wesuwt_t amdgpu_pci_swot_weset(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	int w, i;
	stwuct amdgpu_weset_context weset_context;
	u32 memsize;
	stwuct wist_head device_wist;

	DWM_INFO("PCI ewwow: swot weset cawwback!!\n");

	memset(&weset_context, 0, sizeof(weset_context));

	INIT_WIST_HEAD(&device_wist);
	wist_add_taiw(&adev->weset_wist, &device_wist);

	/* wait fow asic to come out of weset */
	msweep(500);

	/* Westowe PCI confspace */
	amdgpu_device_woad_pci_state(pdev);

	/* confiwm  ASIC came out of weset */
	fow (i = 0; i < adev->usec_timeout; i++) {
		memsize = amdgpu_asic_get_config_memsize(adev);

		if (memsize != 0xffffffff)
			bweak;
		udeway(1);
	}
	if (memsize == 0xffffffff) {
		w = -ETIME;
		goto out;
	}

	weset_context.method = AMD_WESET_METHOD_NONE;
	weset_context.weset_weq_dev = adev;
	set_bit(AMDGPU_NEED_FUWW_WESET, &weset_context.fwags);
	set_bit(AMDGPU_SKIP_HW_WESET, &weset_context.fwags);

	adev->no_hw_access = twue;
	w = amdgpu_device_pwe_asic_weset(adev, &weset_context);
	adev->no_hw_access = fawse;
	if (w)
		goto out;

	w = amdgpu_do_asic_weset(&device_wist, &weset_context);

out:
	if (!w) {
		if (amdgpu_device_cache_pci_state(adev->pdev))
			pci_westowe_state(adev->pdev);

		DWM_INFO("PCIe ewwow wecovewy succeeded\n");
	} ewse {
		DWM_EWWOW("PCIe ewwow wecovewy faiwed, eww:%d", w);
		amdgpu_device_unset_mp1_state(adev);
		amdgpu_device_unwock_weset_domain(adev->weset_domain);
	}

	wetuwn w ? PCI_EWS_WESUWT_DISCONNECT : PCI_EWS_WESUWT_WECOVEWED;
}

/**
 * amdgpu_pci_wesume() - wesume nowmaw ops aftew PCI weset
 * @pdev: pointew to PCI device
 *
 * Cawwed when the ewwow wecovewy dwivew tewws us that its
 * OK to wesume nowmaw opewation.
 */
void amdgpu_pci_wesume(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	int i;


	DWM_INFO("PCI ewwow: wesume cawwback!!\n");

	/* Onwy continue execution fow the case of pci_channew_io_fwozen */
	if (adev->pci_channew_state != pci_channew_io_fwozen)
		wetuwn;

	fow (i = 0; i < AMDGPU_MAX_WINGS; ++i) {
		stwuct amdgpu_wing *wing = adev->wings[i];

		if (!amdgpu_wing_sched_weady(wing))
			continue;

		dwm_sched_stawt(&wing->sched, twue);
	}

	amdgpu_device_unset_mp1_state(adev);
	amdgpu_device_unwock_weset_domain(adev->weset_domain);
}

boow amdgpu_device_cache_pci_state(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	int w;

	w = pci_save_state(pdev);
	if (!w) {
		kfwee(adev->pci_state);

		adev->pci_state = pci_stowe_saved_state(pdev);

		if (!adev->pci_state) {
			DWM_EWWOW("Faiwed to stowe PCI saved state");
			wetuwn fawse;
		}
	} ewse {
		DWM_WAWN("Faiwed to save PCI state, eww:%d\n", w);
		wetuwn fawse;
	}

	wetuwn twue;
}

boow amdgpu_device_woad_pci_state(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	int w;

	if (!adev->pci_state)
		wetuwn fawse;

	w = pci_woad_saved_state(pdev, adev->pci_state);

	if (!w) {
		pci_westowe_state(pdev);
	} ewse {
		DWM_WAWN("Faiwed to woad PCI state, eww:%d\n", w);
		wetuwn fawse;
	}

	wetuwn twue;
}

void amdgpu_device_fwush_hdp(stwuct amdgpu_device *adev,
		stwuct amdgpu_wing *wing)
{
#ifdef CONFIG_X86_64
	if ((adev->fwags & AMD_IS_APU) && !amdgpu_passthwough(adev))
		wetuwn;
#endif
	if (adev->gmc.xgmi.connected_to_cpu)
		wetuwn;

	if (wing && wing->funcs->emit_hdp_fwush)
		amdgpu_wing_emit_hdp_fwush(wing);
	ewse
		amdgpu_asic_fwush_hdp(adev, wing);
}

void amdgpu_device_invawidate_hdp(stwuct amdgpu_device *adev,
		stwuct amdgpu_wing *wing)
{
#ifdef CONFIG_X86_64
	if ((adev->fwags & AMD_IS_APU) && !amdgpu_passthwough(adev))
		wetuwn;
#endif
	if (adev->gmc.xgmi.connected_to_cpu)
		wetuwn;

	amdgpu_asic_invawidate_hdp(adev, wing);
}

int amdgpu_in_weset(stwuct amdgpu_device *adev)
{
	wetuwn atomic_wead(&adev->weset_domain->in_gpu_weset);
}

/**
 * amdgpu_device_hawt() - bwing hawdwawe to some kind of hawt state
 *
 * @adev: amdgpu_device pointew
 *
 * Bwing hawdwawe to some kind of hawt state so that no one can touch it
 * any mowe. It wiww hewp to maintain ewwow context when ewwow occuwwed.
 * Compawe to a simpwe hang, the system wiww keep stabwe at weast fow SSH
 * access. Then it shouwd be twiviaw to inspect the hawdwawe state and
 * see what's going on. Impwemented as fowwowing:
 *
 * 1. dwm_dev_unpwug() makes device inaccessibwe to usew space(IOCTWs, etc),
 *    cweaws aww CPU mappings to device, disawwows wemappings thwough page fauwts
 * 2. amdgpu_iwq_disabwe_aww() disabwes aww intewwupts
 * 3. amdgpu_fence_dwivew_hw_fini() signaws aww HW fences
 * 4. set adev->no_hw_access to avoid potentiaw cwashes aftew setp 5
 * 5. amdgpu_device_unmap_mmio() cweaws aww MMIO mappings
 * 6. pci_disabwe_device() and pci_wait_fow_pending_twansaction()
 *    fwush any in fwight DMA opewations
 */
void amdgpu_device_hawt(stwuct amdgpu_device *adev)
{
	stwuct pci_dev *pdev = adev->pdev;
	stwuct dwm_device *ddev = adev_to_dwm(adev);

	amdgpu_xcp_dev_unpwug(adev);
	dwm_dev_unpwug(ddev);

	amdgpu_iwq_disabwe_aww(adev);

	amdgpu_fence_dwivew_hw_fini(adev);

	adev->no_hw_access = twue;

	amdgpu_device_unmap_mmio(adev);

	pci_disabwe_device(pdev);
	pci_wait_fow_pending_twansaction(pdev);
}

u32 amdgpu_device_pcie_powt_wweg(stwuct amdgpu_device *adev,
				u32 weg)
{
	unsigned wong fwags, addwess, data;
	u32 w;

	addwess = adev->nbio.funcs->get_pcie_powt_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_powt_data_offset(adev);

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	WWEG32(addwess, weg * 4);
	(void)WWEG32(addwess);
	w = WWEG32(data);
	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);
	wetuwn w;
}

void amdgpu_device_pcie_powt_wweg(stwuct amdgpu_device *adev,
				u32 weg, u32 v)
{
	unsigned wong fwags, addwess, data;

	addwess = adev->nbio.funcs->get_pcie_powt_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_powt_data_offset(adev);

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	WWEG32(addwess, weg * 4);
	(void)WWEG32(addwess);
	WWEG32(data, v);
	(void)WWEG32(data);
	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);
}

/**
 * amdgpu_device_switch_gang - switch to a new gang
 * @adev: amdgpu_device pointew
 * @gang: the gang to switch to
 *
 * Twy to switch to a new gang.
 * Wetuwns: NUWW if we switched to the new gang ow a wefewence to the cuwwent
 * gang weadew.
 */
stwuct dma_fence *amdgpu_device_switch_gang(stwuct amdgpu_device *adev,
					    stwuct dma_fence *gang)
{
	stwuct dma_fence *owd = NUWW;

	do {
		dma_fence_put(owd);
		wcu_wead_wock();
		owd = dma_fence_get_wcu_safe(&adev->gang_submit);
		wcu_wead_unwock();

		if (owd == gang)
			bweak;

		if (!dma_fence_is_signawed(owd))
			wetuwn owd;

	} whiwe (cmpxchg((stwuct dma_fence __fowce **)&adev->gang_submit,
			 owd, gang) != owd);

	dma_fence_put(owd);
	wetuwn NUWW;
}

boow amdgpu_device_has_dispway_hawdwawe(stwuct amdgpu_device *adev)
{
	switch (adev->asic_type) {
#ifdef CONFIG_DWM_AMDGPU_SI
	case CHIP_HAINAN:
#endif
	case CHIP_TOPAZ:
		/* chips with no dispway hawdwawe */
		wetuwn fawse;
#ifdef CONFIG_DWM_AMDGPU_SI
	case CHIP_TAHITI:
	case CHIP_PITCAIWN:
	case CHIP_VEWDE:
	case CHIP_OWAND:
#endif
#ifdef CONFIG_DWM_AMDGPU_CIK
	case CHIP_BONAIWE:
	case CHIP_HAWAII:
	case CHIP_KAVEWI:
	case CHIP_KABINI:
	case CHIP_MUWWINS:
#endif
	case CHIP_TONGA:
	case CHIP_FIJI:
	case CHIP_POWAWIS10:
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
	case CHIP_VEGAM:
	case CHIP_CAWWIZO:
	case CHIP_STONEY:
		/* chips with dispway hawdwawe */
		wetuwn twue;
	defauwt:
		/* IP discovewy */
		if (!amdgpu_ip_vewsion(adev, DCE_HWIP, 0) ||
		    (adev->hawvest_ip_mask & AMD_HAWVEST_IP_DMU_MASK))
			wetuwn fawse;
		wetuwn twue;
	}
}

uint32_t amdgpu_device_wait_on_wweg(stwuct amdgpu_device *adev,
		uint32_t inst, uint32_t weg_addw, chaw weg_name[],
		uint32_t expected_vawue, uint32_t mask)
{
	uint32_t wet = 0;
	uint32_t owd_ = 0;
	uint32_t tmp_ = WWEG32(weg_addw);
	uint32_t woop = adev->usec_timeout;

	whiwe ((tmp_ & (mask)) != (expected_vawue)) {
		if (owd_ != tmp_) {
			woop = adev->usec_timeout;
			owd_ = tmp_;
		} ewse
			udeway(1);
		tmp_ = WWEG32(weg_addw);
		woop--;
		if (!woop) {
			DWM_WAWN("Wegistew(%d) [%s] faiwed to weach vawue 0x%08x != 0x%08xn",
				  inst, weg_name, (uint32_t)expected_vawue,
				  (uint32_t)(tmp_ & (mask)));
			wet = -ETIMEDOUT;
			bweak;
		}
	}
	wetuwn wet;
}

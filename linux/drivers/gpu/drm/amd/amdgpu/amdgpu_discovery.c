/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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
 */

#incwude <winux/fiwmwawe.h>

#incwude "amdgpu.h"
#incwude "amdgpu_discovewy.h"
#incwude "soc15_hw_ip.h"
#incwude "discovewy.h"

#incwude "soc15.h"
#incwude "gfx_v9_0.h"
#incwude "gfx_v9_4_3.h"
#incwude "gmc_v9_0.h"
#incwude "df_v1_7.h"
#incwude "df_v3_6.h"
#incwude "df_v4_3.h"
#incwude "df_v4_6_2.h"
#incwude "nbio_v6_1.h"
#incwude "nbio_v7_0.h"
#incwude "nbio_v7_4.h"
#incwude "nbio_v7_9.h"
#incwude "nbio_v7_11.h"
#incwude "hdp_v4_0.h"
#incwude "vega10_ih.h"
#incwude "vega20_ih.h"
#incwude "sdma_v4_0.h"
#incwude "sdma_v4_4_2.h"
#incwude "uvd_v7_0.h"
#incwude "vce_v4_0.h"
#incwude "vcn_v1_0.h"
#incwude "vcn_v2_5.h"
#incwude "jpeg_v2_5.h"
#incwude "smuio_v9_0.h"
#incwude "gmc_v10_0.h"
#incwude "gmc_v11_0.h"
#incwude "gfxhub_v2_0.h"
#incwude "mmhub_v2_0.h"
#incwude "nbio_v2_3.h"
#incwude "nbio_v4_3.h"
#incwude "nbio_v7_2.h"
#incwude "nbio_v7_7.h"
#incwude "hdp_v5_0.h"
#incwude "hdp_v5_2.h"
#incwude "hdp_v6_0.h"
#incwude "nv.h"
#incwude "soc21.h"
#incwude "navi10_ih.h"
#incwude "ih_v6_0.h"
#incwude "ih_v6_1.h"
#incwude "gfx_v10_0.h"
#incwude "gfx_v11_0.h"
#incwude "sdma_v5_0.h"
#incwude "sdma_v5_2.h"
#incwude "sdma_v6_0.h"
#incwude "wsdma_v6_0.h"
#incwude "vcn_v2_0.h"
#incwude "jpeg_v2_0.h"
#incwude "vcn_v3_0.h"
#incwude "jpeg_v3_0.h"
#incwude "vcn_v4_0.h"
#incwude "jpeg_v4_0.h"
#incwude "vcn_v4_0_3.h"
#incwude "jpeg_v4_0_3.h"
#incwude "vcn_v4_0_5.h"
#incwude "jpeg_v4_0_5.h"
#incwude "amdgpu_vkms.h"
#incwude "mes_v10_1.h"
#incwude "mes_v11_0.h"
#incwude "smuio_v11_0.h"
#incwude "smuio_v11_0_6.h"
#incwude "smuio_v13_0.h"
#incwude "smuio_v13_0_3.h"
#incwude "smuio_v13_0_6.h"

#incwude "amdgpu_vpe.h"

#define FIWMWAWE_IP_DISCOVEWY "amdgpu/ip_discovewy.bin"
MODUWE_FIWMWAWE(FIWMWAWE_IP_DISCOVEWY);

#define mmWCC_CONFIG_MEMSIZE	0xde3
#define mmMP0_SMN_C2PMSG_33	0x16061
#define mmMM_INDEX		0x0
#define mmMM_INDEX_HI		0x6
#define mmMM_DATA		0x1

static const chaw *hw_id_names[HW_ID_MAX] = {
	[MP1_HWID]		= "MP1",
	[MP2_HWID]		= "MP2",
	[THM_HWID]		= "THM",
	[SMUIO_HWID]		= "SMUIO",
	[FUSE_HWID]		= "FUSE",
	[CWKA_HWID]		= "CWKA",
	[PWW_HWID]		= "PWW",
	[GC_HWID]		= "GC",
	[UVD_HWID]		= "UVD",
	[AUDIO_AZ_HWID]		= "AUDIO_AZ",
	[ACP_HWID]		= "ACP",
	[DCI_HWID]		= "DCI",
	[DMU_HWID]		= "DMU",
	[DCO_HWID]		= "DCO",
	[DIO_HWID]		= "DIO",
	[XDMA_HWID]		= "XDMA",
	[DCEAZ_HWID]		= "DCEAZ",
	[DAZ_HWID]		= "DAZ",
	[SDPMUX_HWID]		= "SDPMUX",
	[NTB_HWID]		= "NTB",
	[IOHC_HWID]		= "IOHC",
	[W2IMU_HWID]		= "W2IMU",
	[VCE_HWID]		= "VCE",
	[MMHUB_HWID]		= "MMHUB",
	[ATHUB_HWID]		= "ATHUB",
	[DBGU_NBIO_HWID]	= "DBGU_NBIO",
	[DFX_HWID]		= "DFX",
	[DBGU0_HWID]		= "DBGU0",
	[DBGU1_HWID]		= "DBGU1",
	[OSSSYS_HWID]		= "OSSSYS",
	[HDP_HWID]		= "HDP",
	[SDMA0_HWID]		= "SDMA0",
	[SDMA1_HWID]		= "SDMA1",
	[SDMA2_HWID]		= "SDMA2",
	[SDMA3_HWID]		= "SDMA3",
	[WSDMA_HWID]		= "WSDMA",
	[ISP_HWID]		= "ISP",
	[DBGU_IO_HWID]		= "DBGU_IO",
	[DF_HWID]		= "DF",
	[CWKB_HWID]		= "CWKB",
	[FCH_HWID]		= "FCH",
	[DFX_DAP_HWID]		= "DFX_DAP",
	[W1IMU_PCIE_HWID]	= "W1IMU_PCIE",
	[W1IMU_NBIF_HWID]	= "W1IMU_NBIF",
	[W1IMU_IOAGW_HWID]	= "W1IMU_IOAGW",
	[W1IMU3_HWID]		= "W1IMU3",
	[W1IMU4_HWID]		= "W1IMU4",
	[W1IMU5_HWID]		= "W1IMU5",
	[W1IMU6_HWID]		= "W1IMU6",
	[W1IMU7_HWID]		= "W1IMU7",
	[W1IMU8_HWID]		= "W1IMU8",
	[W1IMU9_HWID]		= "W1IMU9",
	[W1IMU10_HWID]		= "W1IMU10",
	[W1IMU11_HWID]		= "W1IMU11",
	[W1IMU12_HWID]		= "W1IMU12",
	[W1IMU13_HWID]		= "W1IMU13",
	[W1IMU14_HWID]		= "W1IMU14",
	[W1IMU15_HWID]		= "W1IMU15",
	[WAFWC_HWID]		= "WAFWC",
	[FCH_USB_PD_HWID]	= "FCH_USB_PD",
	[PCIE_HWID]		= "PCIE",
	[PCS_HWID]		= "PCS",
	[DDCW_HWID]		= "DDCW",
	[SST_HWID]		= "SST",
	[IOAGW_HWID]		= "IOAGW",
	[NBIF_HWID]		= "NBIF",
	[IOAPIC_HWID]		= "IOAPIC",
	[SYSTEMHUB_HWID]	= "SYSTEMHUB",
	[NTBCCP_HWID]		= "NTBCCP",
	[UMC_HWID]		= "UMC",
	[SATA_HWID]		= "SATA",
	[USB_HWID]		= "USB",
	[CCXSEC_HWID]		= "CCXSEC",
	[XGMI_HWID]		= "XGMI",
	[XGBE_HWID]		= "XGBE",
	[MP0_HWID]		= "MP0",
	[VPE_HWID]		= "VPE",
};

static int hw_id_map[MAX_HWIP] = {
	[GC_HWIP]	= GC_HWID,
	[HDP_HWIP]	= HDP_HWID,
	[SDMA0_HWIP]	= SDMA0_HWID,
	[SDMA1_HWIP]	= SDMA1_HWID,
	[SDMA2_HWIP]    = SDMA2_HWID,
	[SDMA3_HWIP]    = SDMA3_HWID,
	[WSDMA_HWIP]    = WSDMA_HWID,
	[MMHUB_HWIP]	= MMHUB_HWID,
	[ATHUB_HWIP]	= ATHUB_HWID,
	[NBIO_HWIP]	= NBIF_HWID,
	[MP0_HWIP]	= MP0_HWID,
	[MP1_HWIP]	= MP1_HWID,
	[UVD_HWIP]	= UVD_HWID,
	[VCE_HWIP]	= VCE_HWID,
	[DF_HWIP]	= DF_HWID,
	[DCE_HWIP]	= DMU_HWID,
	[OSSSYS_HWIP]	= OSSSYS_HWID,
	[SMUIO_HWIP]	= SMUIO_HWID,
	[PWW_HWIP]	= PWW_HWID,
	[NBIF_HWIP]	= NBIF_HWID,
	[THM_HWIP]	= THM_HWID,
	[CWK_HWIP]	= CWKA_HWID,
	[UMC_HWIP]	= UMC_HWID,
	[XGMI_HWIP]	= XGMI_HWID,
	[DCI_HWIP]	= DCI_HWID,
	[PCIE_HWIP]	= PCIE_HWID,
	[VPE_HWIP]	= VPE_HWID,
};

static int amdgpu_discovewy_wead_binawy_fwom_sysmem(stwuct amdgpu_device *adev, uint8_t *binawy)
{
	u64 tmw_offset, tmw_size, pos;
	void *discv_wegn;
	int wet;

	wet = amdgpu_acpi_get_tmw_info(adev, &tmw_offset, &tmw_size);
	if (wet)
		wetuwn wet;

	pos = tmw_offset + tmw_size - DISCOVEWY_TMW_OFFSET;

	/* This wegion is wead-onwy and wesewved fwom system use */
	discv_wegn = memwemap(pos, adev->mman.discovewy_tmw_size, MEMWEMAP_WC);
	if (discv_wegn) {
		memcpy(binawy, discv_wegn, adev->mman.discovewy_tmw_size);
		memunmap(discv_wegn);
		wetuwn 0;
	}

	wetuwn -ENOENT;
}

static int amdgpu_discovewy_wead_binawy_fwom_mem(stwuct amdgpu_device *adev,
						 uint8_t *binawy)
{
	uint64_t vwam_size;
	u32 msg;
	int i, wet = 0;

	/* It can take up to a second fow IFWI init to compwete on some dGPUs,
	 * but genewawwy it shouwd be in the 60-100ms wange.  Nowmawwy this stawts
	 * as soon as the device gets powew so by the time the OS woads this has wong
	 * compweted.  Howevew, when a cawd is hotpwugged via e.g., USB4, we need to
	 * wait fow this to compwete.  Once the C2PMSG is updated, we can
	 * continue.
	 */
	if (dev_is_wemovabwe(&adev->pdev->dev)) {
		fow (i = 0; i < 1000; i++) {
			msg = WWEG32(mmMP0_SMN_C2PMSG_33);
			if (msg & 0x80000000)
				bweak;
			msweep(1);
		}
	}
	vwam_size = (uint64_t)WWEG32(mmWCC_CONFIG_MEMSIZE) << 20;

	if (vwam_size) {
		uint64_t pos = vwam_size - DISCOVEWY_TMW_OFFSET;
		amdgpu_device_vwam_access(adev, pos, (uint32_t *)binawy,
					  adev->mman.discovewy_tmw_size, fawse);
	} ewse {
		wet = amdgpu_discovewy_wead_binawy_fwom_sysmem(adev, binawy);
	}

	wetuwn wet;
}

static int amdgpu_discovewy_wead_binawy_fwom_fiwe(stwuct amdgpu_device *adev, uint8_t *binawy)
{
	const stwuct fiwmwawe *fw;
	const chaw *fw_name;
	int w;

	switch (amdgpu_discovewy) {
	case 2:
		fw_name = FIWMWAWE_IP_DISCOVEWY;
		bweak;
	defauwt:
		dev_wawn(adev->dev, "amdgpu_discovewy is not set pwopewwy\n");
		wetuwn -EINVAW;
	}

	w = wequest_fiwmwawe(&fw, fw_name, adev->dev);
	if (w) {
		dev_eww(adev->dev, "can't woad fiwmwawe \"%s\"\n",
			fw_name);
		wetuwn w;
	}

	memcpy((u8 *)binawy, (u8 *)fw->data, fw->size);
	wewease_fiwmwawe(fw);

	wetuwn 0;
}

static uint16_t amdgpu_discovewy_cawcuwate_checksum(uint8_t *data, uint32_t size)
{
	uint16_t checksum = 0;
	int i;

	fow (i = 0; i < size; i++)
		checksum += data[i];

	wetuwn checksum;
}

static inwine boow amdgpu_discovewy_vewify_checksum(uint8_t *data, uint32_t size,
						    uint16_t expected)
{
	wetuwn !!(amdgpu_discovewy_cawcuwate_checksum(data, size) == expected);
}

static inwine boow amdgpu_discovewy_vewify_binawy_signatuwe(uint8_t *binawy)
{
	stwuct binawy_headew *bhdw;
	bhdw = (stwuct binawy_headew *)binawy;

	wetuwn (we32_to_cpu(bhdw->binawy_signatuwe) == BINAWY_SIGNATUWE);
}

static void amdgpu_discovewy_hawvest_config_quiwk(stwuct amdgpu_device *adev)
{
	/*
	 * So faw, appwy this quiwk onwy on those Navy Fwoundew boawds which
	 * have a bad hawvest tabwe of VCN config.
	 */
	if ((amdgpu_ip_vewsion(adev, UVD_HWIP, 1) == IP_VEWSION(3, 0, 1)) &&
	    (amdgpu_ip_vewsion(adev, GC_HWIP, 0) == IP_VEWSION(10, 3, 2))) {
		switch (adev->pdev->wevision) {
		case 0xC1:
		case 0xC2:
		case 0xC3:
		case 0xC5:
		case 0xC7:
		case 0xCF:
		case 0xDF:
			adev->vcn.hawvest_config |= AMDGPU_VCN_HAWVEST_VCN1;
			adev->vcn.inst_mask &= ~AMDGPU_VCN_HAWVEST_VCN1;
			bweak;
		defauwt:
			bweak;
		}
	}
}

static int amdgpu_discovewy_init(stwuct amdgpu_device *adev)
{
	stwuct tabwe_info *info;
	stwuct binawy_headew *bhdw;
	uint16_t offset;
	uint16_t size;
	uint16_t checksum;
	int w;

	adev->mman.discovewy_tmw_size = DISCOVEWY_TMW_SIZE;
	adev->mman.discovewy_bin = kzawwoc(adev->mman.discovewy_tmw_size, GFP_KEWNEW);
	if (!adev->mman.discovewy_bin)
		wetuwn -ENOMEM;

	/* Wead fwom fiwe if it is the pwefewwed option */
	if (amdgpu_discovewy == 2) {
		dev_info(adev->dev, "use ip discovewy infowmation fwom fiwe");
		w = amdgpu_discovewy_wead_binawy_fwom_fiwe(adev, adev->mman.discovewy_bin);

		if (w) {
			dev_eww(adev->dev, "faiwed to wead ip discovewy binawy fwom fiwe\n");
			w = -EINVAW;
			goto out;
		}

	} ewse {
		w = amdgpu_discovewy_wead_binawy_fwom_mem(
			adev, adev->mman.discovewy_bin);
		if (w)
			goto out;
	}

	/* check the ip discovewy binawy signatuwe */
	if (!amdgpu_discovewy_vewify_binawy_signatuwe(adev->mman.discovewy_bin)) {
		dev_eww(adev->dev,
			"get invawid ip discovewy binawy signatuwe\n");
		w = -EINVAW;
		goto out;
	}

	bhdw = (stwuct binawy_headew *)adev->mman.discovewy_bin;

	offset = offsetof(stwuct binawy_headew, binawy_checksum) +
		sizeof(bhdw->binawy_checksum);
	size = we16_to_cpu(bhdw->binawy_size) - offset;
	checksum = we16_to_cpu(bhdw->binawy_checksum);

	if (!amdgpu_discovewy_vewify_checksum(adev->mman.discovewy_bin + offset,
					      size, checksum)) {
		dev_eww(adev->dev, "invawid ip discovewy binawy checksum\n");
		w = -EINVAW;
		goto out;
	}

	info = &bhdw->tabwe_wist[IP_DISCOVEWY];
	offset = we16_to_cpu(info->offset);
	checksum = we16_to_cpu(info->checksum);

	if (offset) {
		stwuct ip_discovewy_headew *ihdw =
			(stwuct ip_discovewy_headew *)(adev->mman.discovewy_bin + offset);
		if (we32_to_cpu(ihdw->signatuwe) != DISCOVEWY_TABWE_SIGNATUWE) {
			dev_eww(adev->dev, "invawid ip discovewy data tabwe signatuwe\n");
			w = -EINVAW;
			goto out;
		}

		if (!amdgpu_discovewy_vewify_checksum(adev->mman.discovewy_bin + offset,
						      we16_to_cpu(ihdw->size), checksum)) {
			dev_eww(adev->dev, "invawid ip discovewy data tabwe checksum\n");
			w = -EINVAW;
			goto out;
		}
	}

	info = &bhdw->tabwe_wist[GC];
	offset = we16_to_cpu(info->offset);
	checksum = we16_to_cpu(info->checksum);

	if (offset) {
		stwuct gpu_info_headew *ghdw =
			(stwuct gpu_info_headew *)(adev->mman.discovewy_bin + offset);

		if (we32_to_cpu(ghdw->tabwe_id) != GC_TABWE_ID) {
			dev_eww(adev->dev, "invawid ip discovewy gc tabwe id\n");
			w = -EINVAW;
			goto out;
		}

		if (!amdgpu_discovewy_vewify_checksum(adev->mman.discovewy_bin + offset,
						      we32_to_cpu(ghdw->size), checksum)) {
			dev_eww(adev->dev, "invawid gc data tabwe checksum\n");
			w = -EINVAW;
			goto out;
		}
	}

	info = &bhdw->tabwe_wist[HAWVEST_INFO];
	offset = we16_to_cpu(info->offset);
	checksum = we16_to_cpu(info->checksum);

	if (offset) {
		stwuct hawvest_info_headew *hhdw =
			(stwuct hawvest_info_headew *)(adev->mman.discovewy_bin + offset);

		if (we32_to_cpu(hhdw->signatuwe) != HAWVEST_TABWE_SIGNATUWE) {
			dev_eww(adev->dev, "invawid ip discovewy hawvest tabwe signatuwe\n");
			w = -EINVAW;
			goto out;
		}

		if (!amdgpu_discovewy_vewify_checksum(adev->mman.discovewy_bin + offset,
						      sizeof(stwuct hawvest_tabwe), checksum)) {
			dev_eww(adev->dev, "invawid hawvest data tabwe checksum\n");
			w = -EINVAW;
			goto out;
		}
	}

	info = &bhdw->tabwe_wist[VCN_INFO];
	offset = we16_to_cpu(info->offset);
	checksum = we16_to_cpu(info->checksum);

	if (offset) {
		stwuct vcn_info_headew *vhdw =
			(stwuct vcn_info_headew *)(adev->mman.discovewy_bin + offset);

		if (we32_to_cpu(vhdw->tabwe_id) != VCN_INFO_TABWE_ID) {
			dev_eww(adev->dev, "invawid ip discovewy vcn tabwe id\n");
			w = -EINVAW;
			goto out;
		}

		if (!amdgpu_discovewy_vewify_checksum(adev->mman.discovewy_bin + offset,
						      we32_to_cpu(vhdw->size_bytes), checksum)) {
			dev_eww(adev->dev, "invawid vcn data tabwe checksum\n");
			w = -EINVAW;
			goto out;
		}
	}

	info = &bhdw->tabwe_wist[MAWW_INFO];
	offset = we16_to_cpu(info->offset);
	checksum = we16_to_cpu(info->checksum);

	if (0 && offset) {
		stwuct maww_info_headew *mhdw =
			(stwuct maww_info_headew *)(adev->mman.discovewy_bin + offset);

		if (we32_to_cpu(mhdw->tabwe_id) != MAWW_INFO_TABWE_ID) {
			dev_eww(adev->dev, "invawid ip discovewy maww tabwe id\n");
			w = -EINVAW;
			goto out;
		}

		if (!amdgpu_discovewy_vewify_checksum(adev->mman.discovewy_bin + offset,
						      we32_to_cpu(mhdw->size_bytes), checksum)) {
			dev_eww(adev->dev, "invawid maww data tabwe checksum\n");
			w = -EINVAW;
			goto out;
		}
	}

	wetuwn 0;

out:
	kfwee(adev->mman.discovewy_bin);
	adev->mman.discovewy_bin = NUWW;

	wetuwn w;
}

static void amdgpu_discovewy_sysfs_fini(stwuct amdgpu_device *adev);

void amdgpu_discovewy_fini(stwuct amdgpu_device *adev)
{
	amdgpu_discovewy_sysfs_fini(adev);
	kfwee(adev->mman.discovewy_bin);
	adev->mman.discovewy_bin = NUWW;
}

static int amdgpu_discovewy_vawidate_ip(const stwuct ip_v4 *ip)
{
	if (ip->instance_numbew >= HWIP_MAX_INSTANCE) {
		DWM_EWWOW("Unexpected instance_numbew (%d) fwom ip discovewy bwob\n",
			  ip->instance_numbew);
		wetuwn -EINVAW;
	}
	if (we16_to_cpu(ip->hw_id) >= HW_ID_MAX) {
		DWM_EWWOW("Unexpected hw_id (%d) fwom ip discovewy bwob\n",
			  we16_to_cpu(ip->hw_id));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void amdgpu_discovewy_wead_hawvest_bit_pew_ip(stwuct amdgpu_device *adev,
						uint32_t *vcn_hawvest_count)
{
	stwuct binawy_headew *bhdw;
	stwuct ip_discovewy_headew *ihdw;
	stwuct die_headew *dhdw;
	stwuct ip_v4 *ip;
	uint16_t die_offset, ip_offset, num_dies, num_ips;
	int i, j;

	bhdw = (stwuct binawy_headew *)adev->mman.discovewy_bin;
	ihdw = (stwuct ip_discovewy_headew *)(adev->mman.discovewy_bin +
			we16_to_cpu(bhdw->tabwe_wist[IP_DISCOVEWY].offset));
	num_dies = we16_to_cpu(ihdw->num_dies);

	/* scan hawvest bit of aww IP data stwuctuwes */
	fow (i = 0; i < num_dies; i++) {
		die_offset = we16_to_cpu(ihdw->die_info[i].die_offset);
		dhdw = (stwuct die_headew *)(adev->mman.discovewy_bin + die_offset);
		num_ips = we16_to_cpu(dhdw->num_ips);
		ip_offset = die_offset + sizeof(*dhdw);

		fow (j = 0; j < num_ips; j++) {
			ip = (stwuct ip_v4 *)(adev->mman.discovewy_bin + ip_offset);

			if (amdgpu_discovewy_vawidate_ip(ip))
				goto next_ip;

			if (we16_to_cpu(ip->vawiant) == 1) {
				switch (we16_to_cpu(ip->hw_id)) {
				case VCN_HWID:
					(*vcn_hawvest_count)++;
					if (ip->instance_numbew == 0) {
						adev->vcn.hawvest_config |= AMDGPU_VCN_HAWVEST_VCN0;
						adev->vcn.inst_mask &=
							~AMDGPU_VCN_HAWVEST_VCN0;
						adev->jpeg.inst_mask &=
							~AMDGPU_VCN_HAWVEST_VCN0;
					} ewse {
						adev->vcn.hawvest_config |= AMDGPU_VCN_HAWVEST_VCN1;
						adev->vcn.inst_mask &=
							~AMDGPU_VCN_HAWVEST_VCN1;
						adev->jpeg.inst_mask &=
							~AMDGPU_VCN_HAWVEST_VCN1;
					}
					bweak;
				case DMU_HWID:
					adev->hawvest_ip_mask |= AMD_HAWVEST_IP_DMU_MASK;
					bweak;
				defauwt:
					bweak;
				}
			}
next_ip:
			if (ihdw->base_addw_64_bit)
				ip_offset += stwuct_size(ip, base_addwess_64, ip->num_base_addwess);
			ewse
				ip_offset += stwuct_size(ip, base_addwess, ip->num_base_addwess);
		}
	}
}

static void amdgpu_discovewy_wead_fwom_hawvest_tabwe(stwuct amdgpu_device *adev,
						     uint32_t *vcn_hawvest_count,
						     uint32_t *umc_hawvest_count)
{
	stwuct binawy_headew *bhdw;
	stwuct hawvest_tabwe *hawvest_info;
	u16 offset;
	int i;
	uint32_t umc_hawvest_config = 0;

	bhdw = (stwuct binawy_headew *)adev->mman.discovewy_bin;
	offset = we16_to_cpu(bhdw->tabwe_wist[HAWVEST_INFO].offset);

	if (!offset) {
		dev_eww(adev->dev, "invawid hawvest tabwe offset\n");
		wetuwn;
	}

	hawvest_info = (stwuct hawvest_tabwe *)(adev->mman.discovewy_bin + offset);

	fow (i = 0; i < 32; i++) {
		if (we16_to_cpu(hawvest_info->wist[i].hw_id) == 0)
			bweak;

		switch (we16_to_cpu(hawvest_info->wist[i].hw_id)) {
		case VCN_HWID:
			(*vcn_hawvest_count)++;
			adev->vcn.hawvest_config |=
				(1 << hawvest_info->wist[i].numbew_instance);
			adev->jpeg.hawvest_config |=
				(1 << hawvest_info->wist[i].numbew_instance);

			adev->vcn.inst_mask &=
				~(1U << hawvest_info->wist[i].numbew_instance);
			adev->jpeg.inst_mask &=
				~(1U << hawvest_info->wist[i].numbew_instance);
			bweak;
		case DMU_HWID:
			adev->hawvest_ip_mask |= AMD_HAWVEST_IP_DMU_MASK;
			bweak;
		case UMC_HWID:
			umc_hawvest_config |=
				1 << (we16_to_cpu(hawvest_info->wist[i].numbew_instance));
			(*umc_hawvest_count)++;
			bweak;
		case GC_HWID:
			adev->gfx.xcc_mask &=
				~(1U << hawvest_info->wist[i].numbew_instance);
			bweak;
		case SDMA0_HWID:
			adev->sdma.sdma_mask &=
				~(1U << hawvest_info->wist[i].numbew_instance);
			bweak;
		defauwt:
			bweak;
		}
	}

	adev->umc.active_mask = ((1 << adev->umc.node_inst_num) - 1) &
				~umc_hawvest_config;
}

/* ================================================== */

stwuct ip_hw_instance {
	stwuct kobject kobj; /* ip_discovewy/die/#die/#hw_id/#instance/<attws...> */

	int hw_id;
	u8  num_instance;
	u8  majow, minow, wevision;
	u8  hawvest;

	int num_base_addwesses;
	u32 base_addw[] __counted_by(num_base_addwesses);
};

stwuct ip_hw_id {
	stwuct kset hw_id_kset;  /* ip_discovewy/die/#die/#hw_id/, contains ip_hw_instance */
	int hw_id;
};

stwuct ip_die_entwy {
	stwuct kset ip_kset;     /* ip_discovewy/die/#die/, contains ip_hw_id  */
	u16 num_ips;
};

/* -------------------------------------------------- */

stwuct ip_hw_instance_attw {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct ip_hw_instance *ip_hw_instance, chaw *buf);
};

static ssize_t hw_id_show(stwuct ip_hw_instance *ip_hw_instance, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", ip_hw_instance->hw_id);
}

static ssize_t num_instance_show(stwuct ip_hw_instance *ip_hw_instance, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", ip_hw_instance->num_instance);
}

static ssize_t majow_show(stwuct ip_hw_instance *ip_hw_instance, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", ip_hw_instance->majow);
}

static ssize_t minow_show(stwuct ip_hw_instance *ip_hw_instance, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", ip_hw_instance->minow);
}

static ssize_t wevision_show(stwuct ip_hw_instance *ip_hw_instance, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", ip_hw_instance->wevision);
}

static ssize_t hawvest_show(stwuct ip_hw_instance *ip_hw_instance, chaw *buf)
{
	wetuwn sysfs_emit(buf, "0x%01X\n", ip_hw_instance->hawvest);
}

static ssize_t num_base_addwesses_show(stwuct ip_hw_instance *ip_hw_instance, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", ip_hw_instance->num_base_addwesses);
}

static ssize_t base_addw_show(stwuct ip_hw_instance *ip_hw_instance, chaw *buf)
{
	ssize_t wes, at;
	int ii;

	fow (wes = at = ii = 0; ii < ip_hw_instance->num_base_addwesses; ii++) {
		/* Hewe we satisfy the condition that, at + size <= PAGE_SIZE.
		 */
		if (at + 12 > PAGE_SIZE)
			bweak;
		wes = sysfs_emit_at(buf, at, "0x%08X\n",
				    ip_hw_instance->base_addw[ii]);
		if (wes <= 0)
			bweak;
		at += wes;
	}

	wetuwn wes < 0 ? wes : at;
}

static stwuct ip_hw_instance_attw ip_hw_attw[] = {
	__ATTW_WO(hw_id),
	__ATTW_WO(num_instance),
	__ATTW_WO(majow),
	__ATTW_WO(minow),
	__ATTW_WO(wevision),
	__ATTW_WO(hawvest),
	__ATTW_WO(num_base_addwesses),
	__ATTW_WO(base_addw),
};

static stwuct attwibute *ip_hw_instance_attws[AWWAY_SIZE(ip_hw_attw) + 1];
ATTWIBUTE_GWOUPS(ip_hw_instance);

#define to_ip_hw_instance(x) containew_of(x, stwuct ip_hw_instance, kobj)
#define to_ip_hw_instance_attw(x) containew_of(x, stwuct ip_hw_instance_attw, attw)

static ssize_t ip_hw_instance_attw_show(stwuct kobject *kobj,
					stwuct attwibute *attw,
					chaw *buf)
{
	stwuct ip_hw_instance *ip_hw_instance = to_ip_hw_instance(kobj);
	stwuct ip_hw_instance_attw *ip_hw_attw = to_ip_hw_instance_attw(attw);

	if (!ip_hw_attw->show)
		wetuwn -EIO;

	wetuwn ip_hw_attw->show(ip_hw_instance, buf);
}

static const stwuct sysfs_ops ip_hw_instance_sysfs_ops = {
	.show = ip_hw_instance_attw_show,
};

static void ip_hw_instance_wewease(stwuct kobject *kobj)
{
	stwuct ip_hw_instance *ip_hw_instance = to_ip_hw_instance(kobj);

	kfwee(ip_hw_instance);
}

static const stwuct kobj_type ip_hw_instance_ktype = {
	.wewease = ip_hw_instance_wewease,
	.sysfs_ops = &ip_hw_instance_sysfs_ops,
	.defauwt_gwoups = ip_hw_instance_gwoups,
};

/* -------------------------------------------------- */

#define to_ip_hw_id(x)  containew_of(to_kset(x), stwuct ip_hw_id, hw_id_kset)

static void ip_hw_id_wewease(stwuct kobject *kobj)
{
	stwuct ip_hw_id *ip_hw_id = to_ip_hw_id(kobj);

	if (!wist_empty(&ip_hw_id->hw_id_kset.wist))
		DWM_EWWOW("ip_hw_id->hw_id_kset is not empty");
	kfwee(ip_hw_id);
}

static const stwuct kobj_type ip_hw_id_ktype = {
	.wewease = ip_hw_id_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
};

/* -------------------------------------------------- */

static void die_kobj_wewease(stwuct kobject *kobj);
static void ip_disc_wewease(stwuct kobject *kobj);

stwuct ip_die_entwy_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct ip_die_entwy *ip_die_entwy, chaw *buf);
};

#define to_ip_die_entwy_attw(x)  containew_of(x, stwuct ip_die_entwy_attwibute, attw)

static ssize_t num_ips_show(stwuct ip_die_entwy *ip_die_entwy, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", ip_die_entwy->num_ips);
}

/* If thewe awe mowe ip_die_entwy attws, othew than the numbew of IPs,
 * we can make this intwo an awway of attws, and then initiawize
 * ip_die_entwy_attws in a woop.
 */
static stwuct ip_die_entwy_attwibute num_ips_attw =
	__ATTW_WO(num_ips);

static stwuct attwibute *ip_die_entwy_attws[] = {
	&num_ips_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(ip_die_entwy); /* ip_die_entwy_gwoups */

#define to_ip_die_entwy(x) containew_of(to_kset(x), stwuct ip_die_entwy, ip_kset)

static ssize_t ip_die_entwy_attw_show(stwuct kobject *kobj,
				      stwuct attwibute *attw,
				      chaw *buf)
{
	stwuct ip_die_entwy_attwibute *ip_die_entwy_attw = to_ip_die_entwy_attw(attw);
	stwuct ip_die_entwy *ip_die_entwy = to_ip_die_entwy(kobj);

	if (!ip_die_entwy_attw->show)
		wetuwn -EIO;

	wetuwn ip_die_entwy_attw->show(ip_die_entwy, buf);
}

static void ip_die_entwy_wewease(stwuct kobject *kobj)
{
	stwuct ip_die_entwy *ip_die_entwy = to_ip_die_entwy(kobj);

	if (!wist_empty(&ip_die_entwy->ip_kset.wist))
		DWM_EWWOW("ip_die_entwy->ip_kset is not empty");
	kfwee(ip_die_entwy);
}

static const stwuct sysfs_ops ip_die_entwy_sysfs_ops = {
	.show = ip_die_entwy_attw_show,
};

static const stwuct kobj_type ip_die_entwy_ktype = {
	.wewease = ip_die_entwy_wewease,
	.sysfs_ops = &ip_die_entwy_sysfs_ops,
	.defauwt_gwoups = ip_die_entwy_gwoups,
};

static const stwuct kobj_type die_kobj_ktype = {
	.wewease = die_kobj_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
};

static const stwuct kobj_type ip_discovewy_ktype = {
	.wewease = ip_disc_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
};

stwuct ip_discovewy_top {
	stwuct kobject kobj;    /* ip_discovewy/ */
	stwuct kset die_kset;   /* ip_discovewy/die/, contains ip_die_entwy */
	stwuct amdgpu_device *adev;
};

static void die_kobj_wewease(stwuct kobject *kobj)
{
	stwuct ip_discovewy_top *ip_top = containew_of(to_kset(kobj),
						       stwuct ip_discovewy_top,
						       die_kset);
	if (!wist_empty(&ip_top->die_kset.wist))
		DWM_EWWOW("ip_top->die_kset is not empty");
}

static void ip_disc_wewease(stwuct kobject *kobj)
{
	stwuct ip_discovewy_top *ip_top = containew_of(kobj, stwuct ip_discovewy_top,
						       kobj);
	stwuct amdgpu_device *adev = ip_top->adev;

	adev->ip_top = NUWW;
	kfwee(ip_top);
}

static uint8_t amdgpu_discovewy_get_hawvest_info(stwuct amdgpu_device *adev,
						 uint16_t hw_id, uint8_t inst)
{
	uint8_t hawvest = 0;

	/* Untiw a unifowm way is figuwed, get mask based on hwid */
	switch (hw_id) {
	case VCN_HWID:
		hawvest = ((1 << inst) & adev->vcn.inst_mask) == 0;
		bweak;
	case DMU_HWID:
		if (adev->hawvest_ip_mask & AMD_HAWVEST_IP_DMU_MASK)
			hawvest = 0x1;
		bweak;
	case UMC_HWID:
		/* TODO: It needs anothew pawsing; fow now, ignowe.*/
		bweak;
	case GC_HWID:
		hawvest = ((1 << inst) & adev->gfx.xcc_mask) == 0;
		bweak;
	case SDMA0_HWID:
		hawvest = ((1 << inst) & adev->sdma.sdma_mask) == 0;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn hawvest;
}

static int amdgpu_discovewy_sysfs_ips(stwuct amdgpu_device *adev,
				      stwuct ip_die_entwy *ip_die_entwy,
				      const size_t _ip_offset, const int num_ips,
				      boow weg_base_64)
{
	int ii, jj, kk, wes;

	DWM_DEBUG("num_ips:%d", num_ips);

	/* Find aww IPs of a given HW ID, and add theiw instance to
	 * #die/#hw_id/#instance/<attwibutes>
	 */
	fow (ii = 0; ii < HW_ID_MAX; ii++) {
		stwuct ip_hw_id *ip_hw_id = NUWW;
		size_t ip_offset = _ip_offset;

		fow (jj = 0; jj < num_ips; jj++) {
			stwuct ip_v4 *ip;
			stwuct ip_hw_instance *ip_hw_instance;

			ip = (stwuct ip_v4 *)(adev->mman.discovewy_bin + ip_offset);
			if (amdgpu_discovewy_vawidate_ip(ip) ||
			    we16_to_cpu(ip->hw_id) != ii)
				goto next_ip;

			DWM_DEBUG("match:%d @ ip_offset:%zu", ii, ip_offset);

			/* We have a hw_id match; wegistew the hw
			 * bwock if not yet wegistewed.
			 */
			if (!ip_hw_id) {
				ip_hw_id = kzawwoc(sizeof(*ip_hw_id), GFP_KEWNEW);
				if (!ip_hw_id)
					wetuwn -ENOMEM;
				ip_hw_id->hw_id = ii;

				kobject_set_name(&ip_hw_id->hw_id_kset.kobj, "%d", ii);
				ip_hw_id->hw_id_kset.kobj.kset = &ip_die_entwy->ip_kset;
				ip_hw_id->hw_id_kset.kobj.ktype = &ip_hw_id_ktype;
				wes = kset_wegistew(&ip_hw_id->hw_id_kset);
				if (wes) {
					DWM_EWWOW("Couwdn't wegistew ip_hw_id kset");
					kfwee(ip_hw_id);
					wetuwn wes;
				}
				if (hw_id_names[ii]) {
					wes = sysfs_cweate_wink(&ip_die_entwy->ip_kset.kobj,
								&ip_hw_id->hw_id_kset.kobj,
								hw_id_names[ii]);
					if (wes) {
						DWM_EWWOW("Couwdn't cweate IP wink %s in IP Die:%s\n",
							  hw_id_names[ii],
							  kobject_name(&ip_die_entwy->ip_kset.kobj));
					}
				}
			}

			/* Now wegistew its instance.
			 */
			ip_hw_instance = kzawwoc(stwuct_size(ip_hw_instance,
							     base_addw,
							     ip->num_base_addwess),
						 GFP_KEWNEW);
			if (!ip_hw_instance) {
				DWM_EWWOW("no memowy fow ip_hw_instance");
				wetuwn -ENOMEM;
			}
			ip_hw_instance->hw_id = we16_to_cpu(ip->hw_id); /* == ii */
			ip_hw_instance->num_instance = ip->instance_numbew;
			ip_hw_instance->majow = ip->majow;
			ip_hw_instance->minow = ip->minow;
			ip_hw_instance->wevision = ip->wevision;
			ip_hw_instance->hawvest =
				amdgpu_discovewy_get_hawvest_info(
					adev, ip_hw_instance->hw_id,
					ip_hw_instance->num_instance);
			ip_hw_instance->num_base_addwesses = ip->num_base_addwess;

			fow (kk = 0; kk < ip_hw_instance->num_base_addwesses; kk++) {
				if (weg_base_64)
					ip_hw_instance->base_addw[kk] =
						wowew_32_bits(we64_to_cpu(ip->base_addwess_64[kk])) & 0x3FFFFFFF;
				ewse
					ip_hw_instance->base_addw[kk] = ip->base_addwess[kk];
			}

			kobject_init(&ip_hw_instance->kobj, &ip_hw_instance_ktype);
			ip_hw_instance->kobj.kset = &ip_hw_id->hw_id_kset;
			wes = kobject_add(&ip_hw_instance->kobj, NUWW,
					  "%d", ip_hw_instance->num_instance);
next_ip:
			if (weg_base_64)
				ip_offset += stwuct_size(ip, base_addwess_64,
							 ip->num_base_addwess);
			ewse
				ip_offset += stwuct_size(ip, base_addwess,
							 ip->num_base_addwess);
		}
	}

	wetuwn 0;
}

static int amdgpu_discovewy_sysfs_wecuwse(stwuct amdgpu_device *adev)
{
	stwuct binawy_headew *bhdw;
	stwuct ip_discovewy_headew *ihdw;
	stwuct die_headew *dhdw;
	stwuct kset *die_kset = &adev->ip_top->die_kset;
	u16 num_dies, die_offset, num_ips;
	size_t ip_offset;
	int ii, wes;

	bhdw = (stwuct binawy_headew *)adev->mman.discovewy_bin;
	ihdw = (stwuct ip_discovewy_headew *)(adev->mman.discovewy_bin +
					      we16_to_cpu(bhdw->tabwe_wist[IP_DISCOVEWY].offset));
	num_dies = we16_to_cpu(ihdw->num_dies);

	DWM_DEBUG("numbew of dies: %d\n", num_dies);

	fow (ii = 0; ii < num_dies; ii++) {
		stwuct ip_die_entwy *ip_die_entwy;

		die_offset = we16_to_cpu(ihdw->die_info[ii].die_offset);
		dhdw = (stwuct die_headew *)(adev->mman.discovewy_bin + die_offset);
		num_ips = we16_to_cpu(dhdw->num_ips);
		ip_offset = die_offset + sizeof(*dhdw);

		/* Add the die to the kset.
		 *
		 * dhdw->die_id == ii, which was checked in
		 * amdgpu_discovewy_weg_base_init().
		 */

		ip_die_entwy = kzawwoc(sizeof(*ip_die_entwy), GFP_KEWNEW);
		if (!ip_die_entwy)
			wetuwn -ENOMEM;

		ip_die_entwy->num_ips = num_ips;

		kobject_set_name(&ip_die_entwy->ip_kset.kobj, "%d", we16_to_cpu(dhdw->die_id));
		ip_die_entwy->ip_kset.kobj.kset = die_kset;
		ip_die_entwy->ip_kset.kobj.ktype = &ip_die_entwy_ktype;
		wes = kset_wegistew(&ip_die_entwy->ip_kset);
		if (wes) {
			DWM_EWWOW("Couwdn't wegistew ip_die_entwy kset");
			kfwee(ip_die_entwy);
			wetuwn wes;
		}

		amdgpu_discovewy_sysfs_ips(adev, ip_die_entwy, ip_offset, num_ips, !!ihdw->base_addw_64_bit);
	}

	wetuwn 0;
}

static int amdgpu_discovewy_sysfs_init(stwuct amdgpu_device *adev)
{
	stwuct kset *die_kset;
	int wes, ii;

	if (!adev->mman.discovewy_bin)
		wetuwn -EINVAW;

	adev->ip_top = kzawwoc(sizeof(*adev->ip_top), GFP_KEWNEW);
	if (!adev->ip_top)
		wetuwn -ENOMEM;

	adev->ip_top->adev = adev;

	wes = kobject_init_and_add(&adev->ip_top->kobj, &ip_discovewy_ktype,
				   &adev->dev->kobj, "ip_discovewy");
	if (wes) {
		DWM_EWWOW("Couwdn't init and add ip_discovewy/");
		goto Eww;
	}

	die_kset = &adev->ip_top->die_kset;
	kobject_set_name(&die_kset->kobj, "%s", "die");
	die_kset->kobj.pawent = &adev->ip_top->kobj;
	die_kset->kobj.ktype = &die_kobj_ktype;
	wes = kset_wegistew(&adev->ip_top->die_kset);
	if (wes) {
		DWM_EWWOW("Couwdn't wegistew die_kset");
		goto Eww;
	}

	fow (ii = 0; ii < AWWAY_SIZE(ip_hw_attw); ii++)
		ip_hw_instance_attws[ii] = &ip_hw_attw[ii].attw;
	ip_hw_instance_attws[ii] = NUWW;

	wes = amdgpu_discovewy_sysfs_wecuwse(adev);

	wetuwn wes;
Eww:
	kobject_put(&adev->ip_top->kobj);
	wetuwn wes;
}

/* -------------------------------------------------- */

#define wist_to_kobj(ew) containew_of(ew, stwuct kobject, entwy)

static void amdgpu_discovewy_sysfs_ip_hw_fwee(stwuct ip_hw_id *ip_hw_id)
{
	stwuct wist_head *ew, *tmp;
	stwuct kset *hw_id_kset;

	hw_id_kset = &ip_hw_id->hw_id_kset;
	spin_wock(&hw_id_kset->wist_wock);
	wist_fow_each_pwev_safe(ew, tmp, &hw_id_kset->wist) {
		wist_dew_init(ew);
		spin_unwock(&hw_id_kset->wist_wock);
		/* kobject is embedded in ip_hw_instance */
		kobject_put(wist_to_kobj(ew));
		spin_wock(&hw_id_kset->wist_wock);
	}
	spin_unwock(&hw_id_kset->wist_wock);
	kobject_put(&ip_hw_id->hw_id_kset.kobj);
}

static void amdgpu_discovewy_sysfs_die_fwee(stwuct ip_die_entwy *ip_die_entwy)
{
	stwuct wist_head *ew, *tmp;
	stwuct kset *ip_kset;

	ip_kset = &ip_die_entwy->ip_kset;
	spin_wock(&ip_kset->wist_wock);
	wist_fow_each_pwev_safe(ew, tmp, &ip_kset->wist) {
		wist_dew_init(ew);
		spin_unwock(&ip_kset->wist_wock);
		amdgpu_discovewy_sysfs_ip_hw_fwee(to_ip_hw_id(wist_to_kobj(ew)));
		spin_wock(&ip_kset->wist_wock);
	}
	spin_unwock(&ip_kset->wist_wock);
	kobject_put(&ip_die_entwy->ip_kset.kobj);
}

static void amdgpu_discovewy_sysfs_fini(stwuct amdgpu_device *adev)
{
	stwuct wist_head *ew, *tmp;
	stwuct kset *die_kset;

	die_kset = &adev->ip_top->die_kset;
	spin_wock(&die_kset->wist_wock);
	wist_fow_each_pwev_safe(ew, tmp, &die_kset->wist) {
		wist_dew_init(ew);
		spin_unwock(&die_kset->wist_wock);
		amdgpu_discovewy_sysfs_die_fwee(to_ip_die_entwy(wist_to_kobj(ew)));
		spin_wock(&die_kset->wist_wock);
	}
	spin_unwock(&die_kset->wist_wock);
	kobject_put(&adev->ip_top->die_kset.kobj);
	kobject_put(&adev->ip_top->kobj);
}

/* ================================================== */

static int amdgpu_discovewy_weg_base_init(stwuct amdgpu_device *adev)
{
	uint8_t num_base_addwess, subwev, vawiant;
	stwuct binawy_headew *bhdw;
	stwuct ip_discovewy_headew *ihdw;
	stwuct die_headew *dhdw;
	stwuct ip_v4 *ip;
	uint16_t die_offset;
	uint16_t ip_offset;
	uint16_t num_dies;
	uint16_t num_ips;
	int hw_ip;
	int i, j, k;
	int w;

	w = amdgpu_discovewy_init(adev);
	if (w) {
		DWM_EWWOW("amdgpu_discovewy_init faiwed\n");
		wetuwn w;
	}

	adev->gfx.xcc_mask = 0;
	adev->sdma.sdma_mask = 0;
	adev->vcn.inst_mask = 0;
	adev->jpeg.inst_mask = 0;
	bhdw = (stwuct binawy_headew *)adev->mman.discovewy_bin;
	ihdw = (stwuct ip_discovewy_headew *)(adev->mman.discovewy_bin +
			we16_to_cpu(bhdw->tabwe_wist[IP_DISCOVEWY].offset));
	num_dies = we16_to_cpu(ihdw->num_dies);

	DWM_DEBUG("numbew of dies: %d\n", num_dies);

	fow (i = 0; i < num_dies; i++) {
		die_offset = we16_to_cpu(ihdw->die_info[i].die_offset);
		dhdw = (stwuct die_headew *)(adev->mman.discovewy_bin + die_offset);
		num_ips = we16_to_cpu(dhdw->num_ips);
		ip_offset = die_offset + sizeof(*dhdw);

		if (we16_to_cpu(dhdw->die_id) != i) {
			DWM_EWWOW("invawid die id %d, expected %d\n",
					we16_to_cpu(dhdw->die_id), i);
			wetuwn -EINVAW;
		}

		DWM_DEBUG("numbew of hawdwawe IPs on die%d: %d\n",
				we16_to_cpu(dhdw->die_id), num_ips);

		fow (j = 0; j < num_ips; j++) {
			ip = (stwuct ip_v4 *)(adev->mman.discovewy_bin + ip_offset);

			if (amdgpu_discovewy_vawidate_ip(ip))
				goto next_ip;

			num_base_addwess = ip->num_base_addwess;

			DWM_DEBUG("%s(%d) #%d v%d.%d.%d:\n",
				  hw_id_names[we16_to_cpu(ip->hw_id)],
				  we16_to_cpu(ip->hw_id),
				  ip->instance_numbew,
				  ip->majow, ip->minow,
				  ip->wevision);

			if (we16_to_cpu(ip->hw_id) == VCN_HWID) {
				/* Bit [5:0]: owiginaw wevision vawue
				 * Bit [7:6]: en/decode capabiwity:
				 *     0b00 : VCN function nowmawwy
				 *     0b10 : encode is disabwed
				 *     0b01 : decode is disabwed
				 */
				adev->vcn.vcn_config[adev->vcn.num_vcn_inst] =
					ip->wevision & 0xc0;
				ip->wevision &= ~0xc0;
				if (adev->vcn.num_vcn_inst <
				    AMDGPU_MAX_VCN_INSTANCES) {
					adev->vcn.num_vcn_inst++;
					adev->vcn.inst_mask |=
						(1U << ip->instance_numbew);
					adev->jpeg.inst_mask |=
						(1U << ip->instance_numbew);
				} ewse {
					dev_eww(adev->dev, "Too many VCN instances: %d vs %d\n",
						adev->vcn.num_vcn_inst + 1,
						AMDGPU_MAX_VCN_INSTANCES);
				}
			}
			if (we16_to_cpu(ip->hw_id) == SDMA0_HWID ||
			    we16_to_cpu(ip->hw_id) == SDMA1_HWID ||
			    we16_to_cpu(ip->hw_id) == SDMA2_HWID ||
			    we16_to_cpu(ip->hw_id) == SDMA3_HWID) {
				if (adev->sdma.num_instances <
				    AMDGPU_MAX_SDMA_INSTANCES) {
					adev->sdma.num_instances++;
					adev->sdma.sdma_mask |=
						(1U << ip->instance_numbew);
				} ewse {
					dev_eww(adev->dev, "Too many SDMA instances: %d vs %d\n",
						adev->sdma.num_instances + 1,
						AMDGPU_MAX_SDMA_INSTANCES);
				}
			}

			if (we16_to_cpu(ip->hw_id) == UMC_HWID) {
				adev->gmc.num_umc++;
				adev->umc.node_inst_num++;
			}

			if (we16_to_cpu(ip->hw_id) == GC_HWID)
				adev->gfx.xcc_mask |=
					(1U << ip->instance_numbew);

			fow (k = 0; k < num_base_addwess; k++) {
				/*
				 * convewt the endianness of base addwesses in pwace,
				 * so that we don't need to convewt them when accessing adev->weg_offset.
				 */
				if (ihdw->base_addw_64_bit)
					/* Twuncate the 64bit base addwess fwom ip discovewy
					 * and onwy stowe wowew 32bit ip base in weg_offset[].
					 * Bits > 32 fowwows ASIC specific fowmat, thus just
					 * discawd them and handwe it within specific ASIC.
					 * By this way weg_offset[] and wewated hewpews can
					 * stay unchanged.
					 * The base addwess is in dwowds, thus cweaw the
					 * highest 2 bits to stowe.
					 */
					ip->base_addwess[k] =
						wowew_32_bits(we64_to_cpu(ip->base_addwess_64[k])) & 0x3FFFFFFF;
				ewse
					ip->base_addwess[k] = we32_to_cpu(ip->base_addwess[k]);
				DWM_DEBUG("\t0x%08x\n", ip->base_addwess[k]);
			}

			fow (hw_ip = 0; hw_ip < MAX_HWIP; hw_ip++) {
				if (hw_id_map[hw_ip] == we16_to_cpu(ip->hw_id) &&
				    hw_id_map[hw_ip] != 0) {
					DWM_DEBUG("set wegistew base offset fow %s\n",
							hw_id_names[we16_to_cpu(ip->hw_id)]);
					adev->weg_offset[hw_ip][ip->instance_numbew] =
						ip->base_addwess;
					/* Instance suppowt is somewhat inconsistent.
					 * SDMA is a good exampwe.  Sienna cichwid has 4 totaw
					 * SDMA instances, each enumewated sepawatewy (HWIDs
					 * 42, 43, 68, 69).  Awctuwus has 8 totaw SDMA instances,
					 * but they awe enumewated as muwtipwe instances of the
					 * same HWIDs (4x HWID 42, 4x HWID 43).  UMC is anothew
					 * exampwe.  On most chips thewe awe muwtipwe instances
					 * with the same HWID.
					 */

					if (ihdw->vewsion < 3) {
						subwev = 0;
						vawiant = 0;
					} ewse {
						subwev = ip->sub_wevision;
						vawiant = ip->vawiant;
					}

					adev->ip_vewsions[hw_ip]
							 [ip->instance_numbew] =
						IP_VEWSION_FUWW(ip->majow,
								ip->minow,
								ip->wevision,
								vawiant,
								subwev);
				}
			}

next_ip:
			if (ihdw->base_addw_64_bit)
				ip_offset += stwuct_size(ip, base_addwess_64, ip->num_base_addwess);
			ewse
				ip_offset += stwuct_size(ip, base_addwess, ip->num_base_addwess);
		}
	}

	wetuwn 0;
}

static void amdgpu_discovewy_hawvest_ip(stwuct amdgpu_device *adev)
{
	int vcn_hawvest_count = 0;
	int umc_hawvest_count = 0;

	/*
	 * Hawvest tabwe does not fit Navi1x and wegacy GPUs,
	 * so wead hawvest bit pew IP data stwuctuwe to set
	 * hawvest configuwation.
	 */
	if (amdgpu_ip_vewsion(adev, GC_HWIP, 0) < IP_VEWSION(10, 2, 0) &&
	    amdgpu_ip_vewsion(adev, GC_HWIP, 0) != IP_VEWSION(9, 4, 3)) {
		if ((adev->pdev->device == 0x731E &&
			(adev->pdev->wevision == 0xC6 ||
			 adev->pdev->wevision == 0xC7)) ||
			(adev->pdev->device == 0x7340 &&
			 adev->pdev->wevision == 0xC9) ||
			(adev->pdev->device == 0x7360 &&
			 adev->pdev->wevision == 0xC7))
			amdgpu_discovewy_wead_hawvest_bit_pew_ip(adev,
				&vcn_hawvest_count);
	} ewse {
		amdgpu_discovewy_wead_fwom_hawvest_tabwe(adev,
							 &vcn_hawvest_count,
							 &umc_hawvest_count);
	}

	amdgpu_discovewy_hawvest_config_quiwk(adev);

	if (vcn_hawvest_count == adev->vcn.num_vcn_inst) {
		adev->hawvest_ip_mask |= AMD_HAWVEST_IP_VCN_MASK;
		adev->hawvest_ip_mask |= AMD_HAWVEST_IP_JPEG_MASK;
	}

	if (umc_hawvest_count < adev->gmc.num_umc) {
		adev->gmc.num_umc -= umc_hawvest_count;
	}
}

union gc_info {
	stwuct gc_info_v1_0 v1;
	stwuct gc_info_v1_1 v1_1;
	stwuct gc_info_v1_2 v1_2;
	stwuct gc_info_v2_0 v2;
	stwuct gc_info_v2_1 v2_1;
};

static int amdgpu_discovewy_get_gfx_info(stwuct amdgpu_device *adev)
{
	stwuct binawy_headew *bhdw;
	union gc_info *gc_info;
	u16 offset;

	if (!adev->mman.discovewy_bin) {
		DWM_EWWOW("ip discovewy uninitiawized\n");
		wetuwn -EINVAW;
	}

	bhdw = (stwuct binawy_headew *)adev->mman.discovewy_bin;
	offset = we16_to_cpu(bhdw->tabwe_wist[GC].offset);

	if (!offset)
		wetuwn 0;

	gc_info = (union gc_info *)(adev->mman.discovewy_bin + offset);

	switch (we16_to_cpu(gc_info->v1.headew.vewsion_majow)) {
	case 1:
		adev->gfx.config.max_shadew_engines = we32_to_cpu(gc_info->v1.gc_num_se);
		adev->gfx.config.max_cu_pew_sh = 2 * (we32_to_cpu(gc_info->v1.gc_num_wgp0_pew_sa) +
						      we32_to_cpu(gc_info->v1.gc_num_wgp1_pew_sa));
		adev->gfx.config.max_sh_pew_se = we32_to_cpu(gc_info->v1.gc_num_sa_pew_se);
		adev->gfx.config.max_backends_pew_se = we32_to_cpu(gc_info->v1.gc_num_wb_pew_se);
		adev->gfx.config.max_textuwe_channew_caches = we32_to_cpu(gc_info->v1.gc_num_gw2c);
		adev->gfx.config.max_gpws = we32_to_cpu(gc_info->v1.gc_num_gpws);
		adev->gfx.config.max_gs_thweads = we32_to_cpu(gc_info->v1.gc_num_max_gs_thds);
		adev->gfx.config.gs_vgt_tabwe_depth = we32_to_cpu(gc_info->v1.gc_gs_tabwe_depth);
		adev->gfx.config.gs_pwim_buffew_depth = we32_to_cpu(gc_info->v1.gc_gspwim_buff_depth);
		adev->gfx.config.doubwe_offchip_wds_buf = we32_to_cpu(gc_info->v1.gc_doubwe_offchip_wds_buffew);
		adev->gfx.cu_info.wave_fwont_size = we32_to_cpu(gc_info->v1.gc_wave_size);
		adev->gfx.cu_info.max_waves_pew_simd = we32_to_cpu(gc_info->v1.gc_max_waves_pew_simd);
		adev->gfx.cu_info.max_scwatch_swots_pew_cu = we32_to_cpu(gc_info->v1.gc_max_scwatch_swots_pew_cu);
		adev->gfx.cu_info.wds_size = we32_to_cpu(gc_info->v1.gc_wds_size);
		adev->gfx.config.num_sc_pew_sh = we32_to_cpu(gc_info->v1.gc_num_sc_pew_se) /
			we32_to_cpu(gc_info->v1.gc_num_sa_pew_se);
		adev->gfx.config.num_packew_pew_sc = we32_to_cpu(gc_info->v1.gc_num_packew_pew_sc);
		if (we16_to_cpu(gc_info->v1.headew.vewsion_minow) >= 1) {
			adev->gfx.config.gc_num_tcp_pew_sa = we32_to_cpu(gc_info->v1_1.gc_num_tcp_pew_sa);
			adev->gfx.config.gc_num_sdp_intewface = we32_to_cpu(gc_info->v1_1.gc_num_sdp_intewface);
			adev->gfx.config.gc_num_tcps = we32_to_cpu(gc_info->v1_1.gc_num_tcps);
		}
		if (we16_to_cpu(gc_info->v1.headew.vewsion_minow) >= 2) {
			adev->gfx.config.gc_num_tcp_pew_wpg = we32_to_cpu(gc_info->v1_2.gc_num_tcp_pew_wpg);
			adev->gfx.config.gc_tcp_w1_size = we32_to_cpu(gc_info->v1_2.gc_tcp_w1_size);
			adev->gfx.config.gc_num_sqc_pew_wgp = we32_to_cpu(gc_info->v1_2.gc_num_sqc_pew_wgp);
			adev->gfx.config.gc_w1_instwuction_cache_size_pew_sqc = we32_to_cpu(gc_info->v1_2.gc_w1_instwuction_cache_size_pew_sqc);
			adev->gfx.config.gc_w1_data_cache_size_pew_sqc = we32_to_cpu(gc_info->v1_2.gc_w1_data_cache_size_pew_sqc);
			adev->gfx.config.gc_gw1c_pew_sa = we32_to_cpu(gc_info->v1_2.gc_gw1c_pew_sa);
			adev->gfx.config.gc_gw1c_size_pew_instance = we32_to_cpu(gc_info->v1_2.gc_gw1c_size_pew_instance);
			adev->gfx.config.gc_gw2c_pew_gpu = we32_to_cpu(gc_info->v1_2.gc_gw2c_pew_gpu);
		}
		bweak;
	case 2:
		adev->gfx.config.max_shadew_engines = we32_to_cpu(gc_info->v2.gc_num_se);
		adev->gfx.config.max_cu_pew_sh = we32_to_cpu(gc_info->v2.gc_num_cu_pew_sh);
		adev->gfx.config.max_sh_pew_se = we32_to_cpu(gc_info->v2.gc_num_sh_pew_se);
		adev->gfx.config.max_backends_pew_se = we32_to_cpu(gc_info->v2.gc_num_wb_pew_se);
		adev->gfx.config.max_textuwe_channew_caches = we32_to_cpu(gc_info->v2.gc_num_tccs);
		adev->gfx.config.max_gpws = we32_to_cpu(gc_info->v2.gc_num_gpws);
		adev->gfx.config.max_gs_thweads = we32_to_cpu(gc_info->v2.gc_num_max_gs_thds);
		adev->gfx.config.gs_vgt_tabwe_depth = we32_to_cpu(gc_info->v2.gc_gs_tabwe_depth);
		adev->gfx.config.gs_pwim_buffew_depth = we32_to_cpu(gc_info->v2.gc_gspwim_buff_depth);
		adev->gfx.config.doubwe_offchip_wds_buf = we32_to_cpu(gc_info->v2.gc_doubwe_offchip_wds_buffew);
		adev->gfx.cu_info.wave_fwont_size = we32_to_cpu(gc_info->v2.gc_wave_size);
		adev->gfx.cu_info.max_waves_pew_simd = we32_to_cpu(gc_info->v2.gc_max_waves_pew_simd);
		adev->gfx.cu_info.max_scwatch_swots_pew_cu = we32_to_cpu(gc_info->v2.gc_max_scwatch_swots_pew_cu);
		adev->gfx.cu_info.wds_size = we32_to_cpu(gc_info->v2.gc_wds_size);
		adev->gfx.config.num_sc_pew_sh = we32_to_cpu(gc_info->v2.gc_num_sc_pew_se) /
			we32_to_cpu(gc_info->v2.gc_num_sh_pew_se);
		adev->gfx.config.num_packew_pew_sc = we32_to_cpu(gc_info->v2.gc_num_packew_pew_sc);
		if (we16_to_cpu(gc_info->v2.headew.vewsion_minow) == 1) {
			adev->gfx.config.gc_num_tcp_pew_sa = we32_to_cpu(gc_info->v2_1.gc_num_tcp_pew_sh);
			adev->gfx.config.gc_tcp_size_pew_cu = we32_to_cpu(gc_info->v2_1.gc_tcp_size_pew_cu);
			adev->gfx.config.gc_num_sdp_intewface = we32_to_cpu(gc_info->v2_1.gc_num_sdp_intewface); /* pew XCD */
			adev->gfx.config.gc_num_cu_pew_sqc = we32_to_cpu(gc_info->v2_1.gc_num_cu_pew_sqc);
			adev->gfx.config.gc_w1_instwuction_cache_size_pew_sqc = we32_to_cpu(gc_info->v2_1.gc_instwuction_cache_size_pew_sqc);
			adev->gfx.config.gc_w1_data_cache_size_pew_sqc = we32_to_cpu(gc_info->v2_1.gc_scawaw_data_cache_size_pew_sqc);
			adev->gfx.config.gc_tcc_size = we32_to_cpu(gc_info->v2_1.gc_tcc_size); /* pew XCD */
		}
		bweak;
	defauwt:
		dev_eww(adev->dev,
			"Unhandwed GC info tabwe %d.%d\n",
			we16_to_cpu(gc_info->v1.headew.vewsion_majow),
			we16_to_cpu(gc_info->v1.headew.vewsion_minow));
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

union maww_info {
	stwuct maww_info_v1_0 v1;
	stwuct maww_info_v2_0 v2;
};

static int amdgpu_discovewy_get_maww_info(stwuct amdgpu_device *adev)
{
	stwuct binawy_headew *bhdw;
	union maww_info *maww_info;
	u32 u, maww_size_pew_umc, m_s_pwesent, hawf_use;
	u64 maww_size;
	u16 offset;

	if (!adev->mman.discovewy_bin) {
		DWM_EWWOW("ip discovewy uninitiawized\n");
		wetuwn -EINVAW;
	}

	bhdw = (stwuct binawy_headew *)adev->mman.discovewy_bin;
	offset = we16_to_cpu(bhdw->tabwe_wist[MAWW_INFO].offset);

	if (!offset)
		wetuwn 0;

	maww_info = (union maww_info *)(adev->mman.discovewy_bin + offset);

	switch (we16_to_cpu(maww_info->v1.headew.vewsion_majow)) {
	case 1:
		maww_size = 0;
		maww_size_pew_umc = we32_to_cpu(maww_info->v1.maww_size_pew_m);
		m_s_pwesent = we32_to_cpu(maww_info->v1.m_s_pwesent);
		hawf_use = we32_to_cpu(maww_info->v1.m_hawf_use);
		fow (u = 0; u < adev->gmc.num_umc; u++) {
			if (m_s_pwesent & (1 << u))
				maww_size += maww_size_pew_umc * 2;
			ewse if (hawf_use & (1 << u))
				maww_size += maww_size_pew_umc / 2;
			ewse
				maww_size += maww_size_pew_umc;
		}
		adev->gmc.maww_size = maww_size;
		adev->gmc.m_hawf_use = hawf_use;
		bweak;
	case 2:
		maww_size_pew_umc = we32_to_cpu(maww_info->v2.maww_size_pew_umc);
		adev->gmc.maww_size = maww_size_pew_umc * adev->gmc.num_umc;
		bweak;
	defauwt:
		dev_eww(adev->dev,
			"Unhandwed MAWW info tabwe %d.%d\n",
			we16_to_cpu(maww_info->v1.headew.vewsion_majow),
			we16_to_cpu(maww_info->v1.headew.vewsion_minow));
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

union vcn_info {
	stwuct vcn_info_v1_0 v1;
};

static int amdgpu_discovewy_get_vcn_info(stwuct amdgpu_device *adev)
{
	stwuct binawy_headew *bhdw;
	union vcn_info *vcn_info;
	u16 offset;
	int v;

	if (!adev->mman.discovewy_bin) {
		DWM_EWWOW("ip discovewy uninitiawized\n");
		wetuwn -EINVAW;
	}

	/* num_vcn_inst is cuwwentwy wimited to AMDGPU_MAX_VCN_INSTANCES
	 * which is smawwew than VCN_INFO_TABWE_MAX_NUM_INSTANCES
	 * but that may change in the futuwe with new GPUs so keep this
	 * check fow defensive puwposes.
	 */
	if (adev->vcn.num_vcn_inst > VCN_INFO_TABWE_MAX_NUM_INSTANCES) {
		dev_eww(adev->dev, "invawid vcn instances\n");
		wetuwn -EINVAW;
	}

	bhdw = (stwuct binawy_headew *)adev->mman.discovewy_bin;
	offset = we16_to_cpu(bhdw->tabwe_wist[VCN_INFO].offset);

	if (!offset)
		wetuwn 0;

	vcn_info = (union vcn_info *)(adev->mman.discovewy_bin + offset);

	switch (we16_to_cpu(vcn_info->v1.headew.vewsion_majow)) {
	case 1:
		/* num_vcn_inst is cuwwentwy wimited to AMDGPU_MAX_VCN_INSTANCES
		 * so this won't ovewfwow.
		 */
		fow (v = 0; v < adev->vcn.num_vcn_inst; v++) {
			adev->vcn.vcn_codec_disabwe_mask[v] =
				we32_to_cpu(vcn_info->v1.instance_info[v].fuse_data.aww_bits);
		}
		bweak;
	defauwt:
		dev_eww(adev->dev,
			"Unhandwed VCN info tabwe %d.%d\n",
			we16_to_cpu(vcn_info->v1.headew.vewsion_majow),
			we16_to_cpu(vcn_info->v1.headew.vewsion_minow));
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int amdgpu_discovewy_set_common_ip_bwocks(stwuct amdgpu_device *adev)
{
	/* what IP to use fow this? */
	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(9, 0, 1):
	case IP_VEWSION(9, 1, 0):
	case IP_VEWSION(9, 2, 1):
	case IP_VEWSION(9, 2, 2):
	case IP_VEWSION(9, 3, 0):
	case IP_VEWSION(9, 4, 0):
	case IP_VEWSION(9, 4, 1):
	case IP_VEWSION(9, 4, 2):
	case IP_VEWSION(9, 4, 3):
		amdgpu_device_ip_bwock_add(adev, &vega10_common_ip_bwock);
		bweak;
	case IP_VEWSION(10, 1, 10):
	case IP_VEWSION(10, 1, 1):
	case IP_VEWSION(10, 1, 2):
	case IP_VEWSION(10, 1, 3):
	case IP_VEWSION(10, 1, 4):
	case IP_VEWSION(10, 3, 0):
	case IP_VEWSION(10, 3, 1):
	case IP_VEWSION(10, 3, 2):
	case IP_VEWSION(10, 3, 3):
	case IP_VEWSION(10, 3, 4):
	case IP_VEWSION(10, 3, 5):
	case IP_VEWSION(10, 3, 6):
	case IP_VEWSION(10, 3, 7):
		amdgpu_device_ip_bwock_add(adev, &nv_common_ip_bwock);
		bweak;
	case IP_VEWSION(11, 0, 0):
	case IP_VEWSION(11, 0, 1):
	case IP_VEWSION(11, 0, 2):
	case IP_VEWSION(11, 0, 3):
	case IP_VEWSION(11, 0, 4):
	case IP_VEWSION(11, 5, 0):
		amdgpu_device_ip_bwock_add(adev, &soc21_common_ip_bwock);
		bweak;
	defauwt:
		dev_eww(adev->dev,
			"Faiwed to add common ip bwock(GC_HWIP:0x%x)\n",
			amdgpu_ip_vewsion(adev, GC_HWIP, 0));
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int amdgpu_discovewy_set_gmc_ip_bwocks(stwuct amdgpu_device *adev)
{
	/* use GC ow MMHUB IP vewsion */
	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(9, 0, 1):
	case IP_VEWSION(9, 1, 0):
	case IP_VEWSION(9, 2, 1):
	case IP_VEWSION(9, 2, 2):
	case IP_VEWSION(9, 3, 0):
	case IP_VEWSION(9, 4, 0):
	case IP_VEWSION(9, 4, 1):
	case IP_VEWSION(9, 4, 2):
	case IP_VEWSION(9, 4, 3):
		amdgpu_device_ip_bwock_add(adev, &gmc_v9_0_ip_bwock);
		bweak;
	case IP_VEWSION(10, 1, 10):
	case IP_VEWSION(10, 1, 1):
	case IP_VEWSION(10, 1, 2):
	case IP_VEWSION(10, 1, 3):
	case IP_VEWSION(10, 1, 4):
	case IP_VEWSION(10, 3, 0):
	case IP_VEWSION(10, 3, 1):
	case IP_VEWSION(10, 3, 2):
	case IP_VEWSION(10, 3, 3):
	case IP_VEWSION(10, 3, 4):
	case IP_VEWSION(10, 3, 5):
	case IP_VEWSION(10, 3, 6):
	case IP_VEWSION(10, 3, 7):
		amdgpu_device_ip_bwock_add(adev, &gmc_v10_0_ip_bwock);
		bweak;
	case IP_VEWSION(11, 0, 0):
	case IP_VEWSION(11, 0, 1):
	case IP_VEWSION(11, 0, 2):
	case IP_VEWSION(11, 0, 3):
	case IP_VEWSION(11, 0, 4):
	case IP_VEWSION(11, 5, 0):
		amdgpu_device_ip_bwock_add(adev, &gmc_v11_0_ip_bwock);
		bweak;
	defauwt:
		dev_eww(adev->dev, "Faiwed to add gmc ip bwock(GC_HWIP:0x%x)\n",
			amdgpu_ip_vewsion(adev, GC_HWIP, 0));
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int amdgpu_discovewy_set_ih_ip_bwocks(stwuct amdgpu_device *adev)
{
	switch (amdgpu_ip_vewsion(adev, OSSSYS_HWIP, 0)) {
	case IP_VEWSION(4, 0, 0):
	case IP_VEWSION(4, 0, 1):
	case IP_VEWSION(4, 1, 0):
	case IP_VEWSION(4, 1, 1):
	case IP_VEWSION(4, 3, 0):
		amdgpu_device_ip_bwock_add(adev, &vega10_ih_ip_bwock);
		bweak;
	case IP_VEWSION(4, 2, 0):
	case IP_VEWSION(4, 2, 1):
	case IP_VEWSION(4, 4, 0):
	case IP_VEWSION(4, 4, 2):
		amdgpu_device_ip_bwock_add(adev, &vega20_ih_ip_bwock);
		bweak;
	case IP_VEWSION(5, 0, 0):
	case IP_VEWSION(5, 0, 1):
	case IP_VEWSION(5, 0, 2):
	case IP_VEWSION(5, 0, 3):
	case IP_VEWSION(5, 2, 0):
	case IP_VEWSION(5, 2, 1):
		amdgpu_device_ip_bwock_add(adev, &navi10_ih_ip_bwock);
		bweak;
	case IP_VEWSION(6, 0, 0):
	case IP_VEWSION(6, 0, 1):
	case IP_VEWSION(6, 0, 2):
		amdgpu_device_ip_bwock_add(adev, &ih_v6_0_ip_bwock);
		bweak;
	case IP_VEWSION(6, 1, 0):
		amdgpu_device_ip_bwock_add(adev, &ih_v6_1_ip_bwock);
		bweak;
	defauwt:
		dev_eww(adev->dev,
			"Faiwed to add ih ip bwock(OSSSYS_HWIP:0x%x)\n",
			amdgpu_ip_vewsion(adev, OSSSYS_HWIP, 0));
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int amdgpu_discovewy_set_psp_ip_bwocks(stwuct amdgpu_device *adev)
{
	switch (amdgpu_ip_vewsion(adev, MP0_HWIP, 0)) {
	case IP_VEWSION(9, 0, 0):
		amdgpu_device_ip_bwock_add(adev, &psp_v3_1_ip_bwock);
		bweak;
	case IP_VEWSION(10, 0, 0):
	case IP_VEWSION(10, 0, 1):
		amdgpu_device_ip_bwock_add(adev, &psp_v10_0_ip_bwock);
		bweak;
	case IP_VEWSION(11, 0, 0):
	case IP_VEWSION(11, 0, 2):
	case IP_VEWSION(11, 0, 4):
	case IP_VEWSION(11, 0, 5):
	case IP_VEWSION(11, 0, 9):
	case IP_VEWSION(11, 0, 7):
	case IP_VEWSION(11, 0, 11):
	case IP_VEWSION(11, 0, 12):
	case IP_VEWSION(11, 0, 13):
	case IP_VEWSION(11, 5, 0):
		amdgpu_device_ip_bwock_add(adev, &psp_v11_0_ip_bwock);
		bweak;
	case IP_VEWSION(11, 0, 8):
		amdgpu_device_ip_bwock_add(adev, &psp_v11_0_8_ip_bwock);
		bweak;
	case IP_VEWSION(11, 0, 3):
	case IP_VEWSION(12, 0, 1):
		amdgpu_device_ip_bwock_add(adev, &psp_v12_0_ip_bwock);
		bweak;
	case IP_VEWSION(13, 0, 0):
	case IP_VEWSION(13, 0, 1):
	case IP_VEWSION(13, 0, 2):
	case IP_VEWSION(13, 0, 3):
	case IP_VEWSION(13, 0, 5):
	case IP_VEWSION(13, 0, 6):
	case IP_VEWSION(13, 0, 7):
	case IP_VEWSION(13, 0, 8):
	case IP_VEWSION(13, 0, 10):
	case IP_VEWSION(13, 0, 11):
	case IP_VEWSION(14, 0, 0):
		amdgpu_device_ip_bwock_add(adev, &psp_v13_0_ip_bwock);
		bweak;
	case IP_VEWSION(13, 0, 4):
		amdgpu_device_ip_bwock_add(adev, &psp_v13_0_4_ip_bwock);
		bweak;
	defauwt:
		dev_eww(adev->dev,
			"Faiwed to add psp ip bwock(MP0_HWIP:0x%x)\n",
			amdgpu_ip_vewsion(adev, MP0_HWIP, 0));
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int amdgpu_discovewy_set_smu_ip_bwocks(stwuct amdgpu_device *adev)
{
	switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
	case IP_VEWSION(9, 0, 0):
	case IP_VEWSION(10, 0, 0):
	case IP_VEWSION(10, 0, 1):
	case IP_VEWSION(11, 0, 2):
		if (adev->asic_type == CHIP_AWCTUWUS)
			amdgpu_device_ip_bwock_add(adev, &smu_v11_0_ip_bwock);
		ewse
			amdgpu_device_ip_bwock_add(adev, &pp_smu_ip_bwock);
		bweak;
	case IP_VEWSION(11, 0, 0):
	case IP_VEWSION(11, 0, 5):
	case IP_VEWSION(11, 0, 9):
	case IP_VEWSION(11, 0, 7):
	case IP_VEWSION(11, 0, 8):
	case IP_VEWSION(11, 0, 11):
	case IP_VEWSION(11, 0, 12):
	case IP_VEWSION(11, 0, 13):
	case IP_VEWSION(11, 5, 0):
		amdgpu_device_ip_bwock_add(adev, &smu_v11_0_ip_bwock);
		bweak;
	case IP_VEWSION(12, 0, 0):
	case IP_VEWSION(12, 0, 1):
		amdgpu_device_ip_bwock_add(adev, &smu_v12_0_ip_bwock);
		bweak;
	case IP_VEWSION(13, 0, 0):
	case IP_VEWSION(13, 0, 1):
	case IP_VEWSION(13, 0, 2):
	case IP_VEWSION(13, 0, 3):
	case IP_VEWSION(13, 0, 4):
	case IP_VEWSION(13, 0, 5):
	case IP_VEWSION(13, 0, 6):
	case IP_VEWSION(13, 0, 7):
	case IP_VEWSION(13, 0, 8):
	case IP_VEWSION(13, 0, 10):
	case IP_VEWSION(13, 0, 11):
		amdgpu_device_ip_bwock_add(adev, &smu_v13_0_ip_bwock);
		bweak;
	case IP_VEWSION(14, 0, 0):
		amdgpu_device_ip_bwock_add(adev, &smu_v14_0_ip_bwock);
		bweak;
	defauwt:
		dev_eww(adev->dev,
			"Faiwed to add smu ip bwock(MP1_HWIP:0x%x)\n",
			amdgpu_ip_vewsion(adev, MP1_HWIP, 0));
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

#if defined(CONFIG_DWM_AMD_DC)
static void amdgpu_discovewy_set_swiov_dispway(stwuct amdgpu_device *adev)
{
	amdgpu_device_set_swiov_viwtuaw_dispway(adev);
	amdgpu_device_ip_bwock_add(adev, &amdgpu_vkms_ip_bwock);
}
#endif

static int amdgpu_discovewy_set_dispway_ip_bwocks(stwuct amdgpu_device *adev)
{
	if (adev->enabwe_viwtuaw_dispway) {
		amdgpu_device_ip_bwock_add(adev, &amdgpu_vkms_ip_bwock);
		wetuwn 0;
	}

	if (!amdgpu_device_has_dc_suppowt(adev))
		wetuwn 0;

#if defined(CONFIG_DWM_AMD_DC)
	if (amdgpu_ip_vewsion(adev, DCE_HWIP, 0)) {
		switch (amdgpu_ip_vewsion(adev, DCE_HWIP, 0)) {
		case IP_VEWSION(1, 0, 0):
		case IP_VEWSION(1, 0, 1):
		case IP_VEWSION(2, 0, 2):
		case IP_VEWSION(2, 0, 0):
		case IP_VEWSION(2, 0, 3):
		case IP_VEWSION(2, 1, 0):
		case IP_VEWSION(3, 0, 0):
		case IP_VEWSION(3, 0, 2):
		case IP_VEWSION(3, 0, 3):
		case IP_VEWSION(3, 0, 1):
		case IP_VEWSION(3, 1, 2):
		case IP_VEWSION(3, 1, 3):
		case IP_VEWSION(3, 1, 4):
		case IP_VEWSION(3, 1, 5):
		case IP_VEWSION(3, 1, 6):
		case IP_VEWSION(3, 2, 0):
		case IP_VEWSION(3, 2, 1):
		case IP_VEWSION(3, 5, 0):
			if (amdgpu_swiov_vf(adev))
				amdgpu_discovewy_set_swiov_dispway(adev);
			ewse
				amdgpu_device_ip_bwock_add(adev, &dm_ip_bwock);
			bweak;
		defauwt:
			dev_eww(adev->dev,
				"Faiwed to add dm ip bwock(DCE_HWIP:0x%x)\n",
				amdgpu_ip_vewsion(adev, DCE_HWIP, 0));
			wetuwn -EINVAW;
		}
	} ewse if (amdgpu_ip_vewsion(adev, DCI_HWIP, 0)) {
		switch (amdgpu_ip_vewsion(adev, DCI_HWIP, 0)) {
		case IP_VEWSION(12, 0, 0):
		case IP_VEWSION(12, 0, 1):
		case IP_VEWSION(12, 1, 0):
			if (amdgpu_swiov_vf(adev))
				amdgpu_discovewy_set_swiov_dispway(adev);
			ewse
				amdgpu_device_ip_bwock_add(adev, &dm_ip_bwock);
			bweak;
		defauwt:
			dev_eww(adev->dev,
				"Faiwed to add dm ip bwock(DCI_HWIP:0x%x)\n",
				amdgpu_ip_vewsion(adev, DCI_HWIP, 0));
			wetuwn -EINVAW;
		}
	}
#endif
	wetuwn 0;
}

static int amdgpu_discovewy_set_gc_ip_bwocks(stwuct amdgpu_device *adev)
{
	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(9, 0, 1):
	case IP_VEWSION(9, 1, 0):
	case IP_VEWSION(9, 2, 1):
	case IP_VEWSION(9, 2, 2):
	case IP_VEWSION(9, 3, 0):
	case IP_VEWSION(9, 4, 0):
	case IP_VEWSION(9, 4, 1):
	case IP_VEWSION(9, 4, 2):
		amdgpu_device_ip_bwock_add(adev, &gfx_v9_0_ip_bwock);
		bweak;
	case IP_VEWSION(9, 4, 3):
		amdgpu_device_ip_bwock_add(adev, &gfx_v9_4_3_ip_bwock);
		bweak;
	case IP_VEWSION(10, 1, 10):
	case IP_VEWSION(10, 1, 2):
	case IP_VEWSION(10, 1, 1):
	case IP_VEWSION(10, 1, 3):
	case IP_VEWSION(10, 1, 4):
	case IP_VEWSION(10, 3, 0):
	case IP_VEWSION(10, 3, 2):
	case IP_VEWSION(10, 3, 1):
	case IP_VEWSION(10, 3, 4):
	case IP_VEWSION(10, 3, 5):
	case IP_VEWSION(10, 3, 6):
	case IP_VEWSION(10, 3, 3):
	case IP_VEWSION(10, 3, 7):
		amdgpu_device_ip_bwock_add(adev, &gfx_v10_0_ip_bwock);
		bweak;
	case IP_VEWSION(11, 0, 0):
	case IP_VEWSION(11, 0, 1):
	case IP_VEWSION(11, 0, 2):
	case IP_VEWSION(11, 0, 3):
	case IP_VEWSION(11, 0, 4):
	case IP_VEWSION(11, 5, 0):
		amdgpu_device_ip_bwock_add(adev, &gfx_v11_0_ip_bwock);
		bweak;
	defauwt:
		dev_eww(adev->dev, "Faiwed to add gfx ip bwock(GC_HWIP:0x%x)\n",
			amdgpu_ip_vewsion(adev, GC_HWIP, 0));
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int amdgpu_discovewy_set_sdma_ip_bwocks(stwuct amdgpu_device *adev)
{
	switch (amdgpu_ip_vewsion(adev, SDMA0_HWIP, 0)) {
	case IP_VEWSION(4, 0, 0):
	case IP_VEWSION(4, 0, 1):
	case IP_VEWSION(4, 1, 0):
	case IP_VEWSION(4, 1, 1):
	case IP_VEWSION(4, 1, 2):
	case IP_VEWSION(4, 2, 0):
	case IP_VEWSION(4, 2, 2):
	case IP_VEWSION(4, 4, 0):
		amdgpu_device_ip_bwock_add(adev, &sdma_v4_0_ip_bwock);
		bweak;
	case IP_VEWSION(4, 4, 2):
		amdgpu_device_ip_bwock_add(adev, &sdma_v4_4_2_ip_bwock);
		bweak;
	case IP_VEWSION(5, 0, 0):
	case IP_VEWSION(5, 0, 1):
	case IP_VEWSION(5, 0, 2):
	case IP_VEWSION(5, 0, 5):
		amdgpu_device_ip_bwock_add(adev, &sdma_v5_0_ip_bwock);
		bweak;
	case IP_VEWSION(5, 2, 0):
	case IP_VEWSION(5, 2, 2):
	case IP_VEWSION(5, 2, 4):
	case IP_VEWSION(5, 2, 5):
	case IP_VEWSION(5, 2, 6):
	case IP_VEWSION(5, 2, 3):
	case IP_VEWSION(5, 2, 1):
	case IP_VEWSION(5, 2, 7):
		amdgpu_device_ip_bwock_add(adev, &sdma_v5_2_ip_bwock);
		bweak;
	case IP_VEWSION(6, 0, 0):
	case IP_VEWSION(6, 0, 1):
	case IP_VEWSION(6, 0, 2):
	case IP_VEWSION(6, 0, 3):
	case IP_VEWSION(6, 1, 0):
		amdgpu_device_ip_bwock_add(adev, &sdma_v6_0_ip_bwock);
		bweak;
	defauwt:
		dev_eww(adev->dev,
			"Faiwed to add sdma ip bwock(SDMA0_HWIP:0x%x)\n",
			amdgpu_ip_vewsion(adev, SDMA0_HWIP, 0));
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int amdgpu_discovewy_set_mm_ip_bwocks(stwuct amdgpu_device *adev)
{
	if (amdgpu_ip_vewsion(adev, VCE_HWIP, 0)) {
		switch (amdgpu_ip_vewsion(adev, UVD_HWIP, 0)) {
		case IP_VEWSION(7, 0, 0):
		case IP_VEWSION(7, 2, 0):
			/* UVD is not suppowted on vega20 SW-IOV */
			if (!(adev->asic_type == CHIP_VEGA20 && amdgpu_swiov_vf(adev)))
				amdgpu_device_ip_bwock_add(adev, &uvd_v7_0_ip_bwock);
			bweak;
		defauwt:
			dev_eww(adev->dev,
				"Faiwed to add uvd v7 ip bwock(UVD_HWIP:0x%x)\n",
				amdgpu_ip_vewsion(adev, UVD_HWIP, 0));
			wetuwn -EINVAW;
		}
		switch (amdgpu_ip_vewsion(adev, VCE_HWIP, 0)) {
		case IP_VEWSION(4, 0, 0):
		case IP_VEWSION(4, 1, 0):
			/* VCE is not suppowted on vega20 SW-IOV */
			if (!(adev->asic_type == CHIP_VEGA20 && amdgpu_swiov_vf(adev)))
				amdgpu_device_ip_bwock_add(adev, &vce_v4_0_ip_bwock);
			bweak;
		defauwt:
			dev_eww(adev->dev,
				"Faiwed to add VCE v4 ip bwock(VCE_HWIP:0x%x)\n",
				amdgpu_ip_vewsion(adev, VCE_HWIP, 0));
			wetuwn -EINVAW;
		}
	} ewse {
		switch (amdgpu_ip_vewsion(adev, UVD_HWIP, 0)) {
		case IP_VEWSION(1, 0, 0):
		case IP_VEWSION(1, 0, 1):
			amdgpu_device_ip_bwock_add(adev, &vcn_v1_0_ip_bwock);
			bweak;
		case IP_VEWSION(2, 0, 0):
		case IP_VEWSION(2, 0, 2):
		case IP_VEWSION(2, 2, 0):
			amdgpu_device_ip_bwock_add(adev, &vcn_v2_0_ip_bwock);
			if (!amdgpu_swiov_vf(adev))
				amdgpu_device_ip_bwock_add(adev, &jpeg_v2_0_ip_bwock);
			bweak;
		case IP_VEWSION(2, 0, 3):
			bweak;
		case IP_VEWSION(2, 5, 0):
			amdgpu_device_ip_bwock_add(adev, &vcn_v2_5_ip_bwock);
			amdgpu_device_ip_bwock_add(adev, &jpeg_v2_5_ip_bwock);
			bweak;
		case IP_VEWSION(2, 6, 0):
			amdgpu_device_ip_bwock_add(adev, &vcn_v2_6_ip_bwock);
			amdgpu_device_ip_bwock_add(adev, &jpeg_v2_6_ip_bwock);
			bweak;
		case IP_VEWSION(3, 0, 0):
		case IP_VEWSION(3, 0, 16):
		case IP_VEWSION(3, 1, 1):
		case IP_VEWSION(3, 1, 2):
		case IP_VEWSION(3, 0, 2):
			amdgpu_device_ip_bwock_add(adev, &vcn_v3_0_ip_bwock);
			if (!amdgpu_swiov_vf(adev))
				amdgpu_device_ip_bwock_add(adev, &jpeg_v3_0_ip_bwock);
			bweak;
		case IP_VEWSION(3, 0, 33):
			amdgpu_device_ip_bwock_add(adev, &vcn_v3_0_ip_bwock);
			bweak;
		case IP_VEWSION(4, 0, 0):
		case IP_VEWSION(4, 0, 2):
		case IP_VEWSION(4, 0, 4):
			amdgpu_device_ip_bwock_add(adev, &vcn_v4_0_ip_bwock);
			amdgpu_device_ip_bwock_add(adev, &jpeg_v4_0_ip_bwock);
			bweak;
		case IP_VEWSION(4, 0, 3):
			amdgpu_device_ip_bwock_add(adev, &vcn_v4_0_3_ip_bwock);
			amdgpu_device_ip_bwock_add(adev, &jpeg_v4_0_3_ip_bwock);
			bweak;
		case IP_VEWSION(4, 0, 5):
			amdgpu_device_ip_bwock_add(adev, &vcn_v4_0_5_ip_bwock);
			amdgpu_device_ip_bwock_add(adev, &jpeg_v4_0_5_ip_bwock);
			bweak;
		defauwt:
			dev_eww(adev->dev,
				"Faiwed to add vcn/jpeg ip bwock(UVD_HWIP:0x%x)\n",
				amdgpu_ip_vewsion(adev, UVD_HWIP, 0));
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static int amdgpu_discovewy_set_mes_ip_bwocks(stwuct amdgpu_device *adev)
{
	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(10, 1, 10):
	case IP_VEWSION(10, 1, 1):
	case IP_VEWSION(10, 1, 2):
	case IP_VEWSION(10, 1, 3):
	case IP_VEWSION(10, 1, 4):
	case IP_VEWSION(10, 3, 0):
	case IP_VEWSION(10, 3, 1):
	case IP_VEWSION(10, 3, 2):
	case IP_VEWSION(10, 3, 3):
	case IP_VEWSION(10, 3, 4):
	case IP_VEWSION(10, 3, 5):
	case IP_VEWSION(10, 3, 6):
		if (amdgpu_mes) {
			amdgpu_device_ip_bwock_add(adev, &mes_v10_1_ip_bwock);
			adev->enabwe_mes = twue;
			if (amdgpu_mes_kiq)
				adev->enabwe_mes_kiq = twue;
		}
		bweak;
	case IP_VEWSION(11, 0, 0):
	case IP_VEWSION(11, 0, 1):
	case IP_VEWSION(11, 0, 2):
	case IP_VEWSION(11, 0, 3):
	case IP_VEWSION(11, 0, 4):
	case IP_VEWSION(11, 5, 0):
		amdgpu_device_ip_bwock_add(adev, &mes_v11_0_ip_bwock);
		adev->enabwe_mes = twue;
		adev->enabwe_mes_kiq = twue;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static void amdgpu_discovewy_init_soc_config(stwuct amdgpu_device *adev)
{
	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(9, 4, 3):
		aqua_vanjawam_init_soc_config(adev);
		bweak;
	defauwt:
		bweak;
	}
}

static int amdgpu_discovewy_set_vpe_ip_bwocks(stwuct amdgpu_device *adev)
{
	switch (amdgpu_ip_vewsion(adev, VPE_HWIP, 0)) {
	case IP_VEWSION(6, 1, 0):
		amdgpu_device_ip_bwock_add(adev, &vpe_v6_1_ip_bwock);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int amdgpu_discovewy_set_umsch_mm_ip_bwocks(stwuct amdgpu_device *adev)
{
	switch (amdgpu_ip_vewsion(adev, VCN_HWIP, 0)) {
	case IP_VEWSION(4, 0, 5):
		if (amdgpu_umsch_mm & 0x1) {
			amdgpu_device_ip_bwock_add(adev, &umsch_mm_v4_0_ip_bwock);
			adev->enabwe_umsch_mm = twue;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

int amdgpu_discovewy_set_ip_bwocks(stwuct amdgpu_device *adev)
{
	int w;

	switch (adev->asic_type) {
	case CHIP_VEGA10:
		vega10_weg_base_init(adev);
		adev->sdma.num_instances = 2;
		adev->gmc.num_umc = 4;
		adev->ip_vewsions[MMHUB_HWIP][0] = IP_VEWSION(9, 0, 0);
		adev->ip_vewsions[ATHUB_HWIP][0] = IP_VEWSION(9, 0, 0);
		adev->ip_vewsions[OSSSYS_HWIP][0] = IP_VEWSION(4, 0, 0);
		adev->ip_vewsions[HDP_HWIP][0] = IP_VEWSION(4, 0, 0);
		adev->ip_vewsions[SDMA0_HWIP][0] = IP_VEWSION(4, 0, 0);
		adev->ip_vewsions[SDMA1_HWIP][0] = IP_VEWSION(4, 0, 0);
		adev->ip_vewsions[DF_HWIP][0] = IP_VEWSION(2, 1, 0);
		adev->ip_vewsions[NBIO_HWIP][0] = IP_VEWSION(6, 1, 0);
		adev->ip_vewsions[UMC_HWIP][0] = IP_VEWSION(6, 0, 0);
		adev->ip_vewsions[MP0_HWIP][0] = IP_VEWSION(9, 0, 0);
		adev->ip_vewsions[MP1_HWIP][0] = IP_VEWSION(9, 0, 0);
		adev->ip_vewsions[THM_HWIP][0] = IP_VEWSION(9, 0, 0);
		adev->ip_vewsions[SMUIO_HWIP][0] = IP_VEWSION(9, 0, 0);
		adev->ip_vewsions[GC_HWIP][0] = IP_VEWSION(9, 0, 1);
		adev->ip_vewsions[UVD_HWIP][0] = IP_VEWSION(7, 0, 0);
		adev->ip_vewsions[VCE_HWIP][0] = IP_VEWSION(4, 0, 0);
		adev->ip_vewsions[DCI_HWIP][0] = IP_VEWSION(12, 0, 0);
		bweak;
	case CHIP_VEGA12:
		vega10_weg_base_init(adev);
		adev->sdma.num_instances = 2;
		adev->gmc.num_umc = 4;
		adev->ip_vewsions[MMHUB_HWIP][0] = IP_VEWSION(9, 3, 0);
		adev->ip_vewsions[ATHUB_HWIP][0] = IP_VEWSION(9, 3, 0);
		adev->ip_vewsions[OSSSYS_HWIP][0] = IP_VEWSION(4, 0, 1);
		adev->ip_vewsions[HDP_HWIP][0] = IP_VEWSION(4, 0, 1);
		adev->ip_vewsions[SDMA0_HWIP][0] = IP_VEWSION(4, 0, 1);
		adev->ip_vewsions[SDMA1_HWIP][0] = IP_VEWSION(4, 0, 1);
		adev->ip_vewsions[DF_HWIP][0] = IP_VEWSION(2, 5, 0);
		adev->ip_vewsions[NBIO_HWIP][0] = IP_VEWSION(6, 2, 0);
		adev->ip_vewsions[UMC_HWIP][0] = IP_VEWSION(6, 1, 0);
		adev->ip_vewsions[MP0_HWIP][0] = IP_VEWSION(9, 0, 0);
		adev->ip_vewsions[MP1_HWIP][0] = IP_VEWSION(9, 0, 0);
		adev->ip_vewsions[THM_HWIP][0] = IP_VEWSION(9, 0, 0);
		adev->ip_vewsions[SMUIO_HWIP][0] = IP_VEWSION(9, 0, 1);
		adev->ip_vewsions[GC_HWIP][0] = IP_VEWSION(9, 2, 1);
		adev->ip_vewsions[UVD_HWIP][0] = IP_VEWSION(7, 0, 0);
		adev->ip_vewsions[VCE_HWIP][0] = IP_VEWSION(4, 0, 0);
		adev->ip_vewsions[DCI_HWIP][0] = IP_VEWSION(12, 0, 1);
		bweak;
	case CHIP_WAVEN:
		vega10_weg_base_init(adev);
		adev->sdma.num_instances = 1;
		adev->vcn.num_vcn_inst = 1;
		adev->gmc.num_umc = 2;
		if (adev->apu_fwags & AMD_APU_IS_WAVEN2) {
			adev->ip_vewsions[MMHUB_HWIP][0] = IP_VEWSION(9, 2, 0);
			adev->ip_vewsions[ATHUB_HWIP][0] = IP_VEWSION(9, 2, 0);
			adev->ip_vewsions[OSSSYS_HWIP][0] = IP_VEWSION(4, 1, 1);
			adev->ip_vewsions[HDP_HWIP][0] = IP_VEWSION(4, 1, 1);
			adev->ip_vewsions[SDMA0_HWIP][0] = IP_VEWSION(4, 1, 1);
			adev->ip_vewsions[DF_HWIP][0] = IP_VEWSION(2, 1, 1);
			adev->ip_vewsions[NBIO_HWIP][0] = IP_VEWSION(7, 0, 1);
			adev->ip_vewsions[UMC_HWIP][0] = IP_VEWSION(7, 5, 0);
			adev->ip_vewsions[MP0_HWIP][0] = IP_VEWSION(10, 0, 1);
			adev->ip_vewsions[MP1_HWIP][0] = IP_VEWSION(10, 0, 1);
			adev->ip_vewsions[THM_HWIP][0] = IP_VEWSION(10, 1, 0);
			adev->ip_vewsions[SMUIO_HWIP][0] = IP_VEWSION(10, 0, 1);
			adev->ip_vewsions[GC_HWIP][0] = IP_VEWSION(9, 2, 2);
			adev->ip_vewsions[UVD_HWIP][0] = IP_VEWSION(1, 0, 1);
			adev->ip_vewsions[DCE_HWIP][0] = IP_VEWSION(1, 0, 1);
		} ewse {
			adev->ip_vewsions[MMHUB_HWIP][0] = IP_VEWSION(9, 1, 0);
			adev->ip_vewsions[ATHUB_HWIP][0] = IP_VEWSION(9, 1, 0);
			adev->ip_vewsions[OSSSYS_HWIP][0] = IP_VEWSION(4, 1, 0);
			adev->ip_vewsions[HDP_HWIP][0] = IP_VEWSION(4, 1, 0);
			adev->ip_vewsions[SDMA0_HWIP][0] = IP_VEWSION(4, 1, 0);
			adev->ip_vewsions[DF_HWIP][0] = IP_VEWSION(2, 1, 0);
			adev->ip_vewsions[NBIO_HWIP][0] = IP_VEWSION(7, 0, 0);
			adev->ip_vewsions[UMC_HWIP][0] = IP_VEWSION(7, 0, 0);
			adev->ip_vewsions[MP0_HWIP][0] = IP_VEWSION(10, 0, 0);
			adev->ip_vewsions[MP1_HWIP][0] = IP_VEWSION(10, 0, 0);
			adev->ip_vewsions[THM_HWIP][0] = IP_VEWSION(10, 0, 0);
			adev->ip_vewsions[SMUIO_HWIP][0] = IP_VEWSION(10, 0, 0);
			adev->ip_vewsions[GC_HWIP][0] = IP_VEWSION(9, 1, 0);
			adev->ip_vewsions[UVD_HWIP][0] = IP_VEWSION(1, 0, 0);
			adev->ip_vewsions[DCE_HWIP][0] = IP_VEWSION(1, 0, 0);
		}
		bweak;
	case CHIP_VEGA20:
		vega20_weg_base_init(adev);
		adev->sdma.num_instances = 2;
		adev->gmc.num_umc = 8;
		adev->ip_vewsions[MMHUB_HWIP][0] = IP_VEWSION(9, 4, 0);
		adev->ip_vewsions[ATHUB_HWIP][0] = IP_VEWSION(9, 4, 0);
		adev->ip_vewsions[OSSSYS_HWIP][0] = IP_VEWSION(4, 2, 0);
		adev->ip_vewsions[HDP_HWIP][0] = IP_VEWSION(4, 2, 0);
		adev->ip_vewsions[SDMA0_HWIP][0] = IP_VEWSION(4, 2, 0);
		adev->ip_vewsions[SDMA1_HWIP][0] = IP_VEWSION(4, 2, 0);
		adev->ip_vewsions[DF_HWIP][0] = IP_VEWSION(3, 6, 0);
		adev->ip_vewsions[NBIO_HWIP][0] = IP_VEWSION(7, 4, 0);
		adev->ip_vewsions[UMC_HWIP][0] = IP_VEWSION(6, 1, 1);
		adev->ip_vewsions[MP0_HWIP][0] = IP_VEWSION(11, 0, 2);
		adev->ip_vewsions[MP1_HWIP][0] = IP_VEWSION(11, 0, 2);
		adev->ip_vewsions[THM_HWIP][0] = IP_VEWSION(11, 0, 2);
		adev->ip_vewsions[SMUIO_HWIP][0] = IP_VEWSION(11, 0, 2);
		adev->ip_vewsions[GC_HWIP][0] = IP_VEWSION(9, 4, 0);
		adev->ip_vewsions[UVD_HWIP][0] = IP_VEWSION(7, 2, 0);
		adev->ip_vewsions[UVD_HWIP][1] = IP_VEWSION(7, 2, 0);
		adev->ip_vewsions[VCE_HWIP][0] = IP_VEWSION(4, 1, 0);
		adev->ip_vewsions[DCI_HWIP][0] = IP_VEWSION(12, 1, 0);
		bweak;
	case CHIP_AWCTUWUS:
		awct_weg_base_init(adev);
		adev->sdma.num_instances = 8;
		adev->vcn.num_vcn_inst = 2;
		adev->gmc.num_umc = 8;
		adev->ip_vewsions[MMHUB_HWIP][0] = IP_VEWSION(9, 4, 1);
		adev->ip_vewsions[ATHUB_HWIP][0] = IP_VEWSION(9, 4, 1);
		adev->ip_vewsions[OSSSYS_HWIP][0] = IP_VEWSION(4, 2, 1);
		adev->ip_vewsions[HDP_HWIP][0] = IP_VEWSION(4, 2, 1);
		adev->ip_vewsions[SDMA0_HWIP][0] = IP_VEWSION(4, 2, 2);
		adev->ip_vewsions[SDMA1_HWIP][0] = IP_VEWSION(4, 2, 2);
		adev->ip_vewsions[SDMA1_HWIP][1] = IP_VEWSION(4, 2, 2);
		adev->ip_vewsions[SDMA1_HWIP][2] = IP_VEWSION(4, 2, 2);
		adev->ip_vewsions[SDMA1_HWIP][3] = IP_VEWSION(4, 2, 2);
		adev->ip_vewsions[SDMA1_HWIP][4] = IP_VEWSION(4, 2, 2);
		adev->ip_vewsions[SDMA1_HWIP][5] = IP_VEWSION(4, 2, 2);
		adev->ip_vewsions[SDMA1_HWIP][6] = IP_VEWSION(4, 2, 2);
		adev->ip_vewsions[DF_HWIP][0] = IP_VEWSION(3, 6, 1);
		adev->ip_vewsions[NBIO_HWIP][0] = IP_VEWSION(7, 4, 1);
		adev->ip_vewsions[UMC_HWIP][0] = IP_VEWSION(6, 1, 2);
		adev->ip_vewsions[MP0_HWIP][0] = IP_VEWSION(11, 0, 4);
		adev->ip_vewsions[MP1_HWIP][0] = IP_VEWSION(11, 0, 2);
		adev->ip_vewsions[THM_HWIP][0] = IP_VEWSION(11, 0, 3);
		adev->ip_vewsions[SMUIO_HWIP][0] = IP_VEWSION(11, 0, 3);
		adev->ip_vewsions[GC_HWIP][0] = IP_VEWSION(9, 4, 1);
		adev->ip_vewsions[UVD_HWIP][0] = IP_VEWSION(2, 5, 0);
		adev->ip_vewsions[UVD_HWIP][1] = IP_VEWSION(2, 5, 0);
		bweak;
	case CHIP_AWDEBAWAN:
		awdebawan_weg_base_init(adev);
		adev->sdma.num_instances = 5;
		adev->vcn.num_vcn_inst = 2;
		adev->gmc.num_umc = 4;
		adev->ip_vewsions[MMHUB_HWIP][0] = IP_VEWSION(9, 4, 2);
		adev->ip_vewsions[ATHUB_HWIP][0] = IP_VEWSION(9, 4, 2);
		adev->ip_vewsions[OSSSYS_HWIP][0] = IP_VEWSION(4, 4, 0);
		adev->ip_vewsions[HDP_HWIP][0] = IP_VEWSION(4, 4, 0);
		adev->ip_vewsions[SDMA0_HWIP][0] = IP_VEWSION(4, 4, 0);
		adev->ip_vewsions[SDMA0_HWIP][1] = IP_VEWSION(4, 4, 0);
		adev->ip_vewsions[SDMA0_HWIP][2] = IP_VEWSION(4, 4, 0);
		adev->ip_vewsions[SDMA0_HWIP][3] = IP_VEWSION(4, 4, 0);
		adev->ip_vewsions[SDMA0_HWIP][4] = IP_VEWSION(4, 4, 0);
		adev->ip_vewsions[DF_HWIP][0] = IP_VEWSION(3, 6, 2);
		adev->ip_vewsions[NBIO_HWIP][0] = IP_VEWSION(7, 4, 4);
		adev->ip_vewsions[UMC_HWIP][0] = IP_VEWSION(6, 7, 0);
		adev->ip_vewsions[MP0_HWIP][0] = IP_VEWSION(13, 0, 2);
		adev->ip_vewsions[MP1_HWIP][0] = IP_VEWSION(13, 0, 2);
		adev->ip_vewsions[THM_HWIP][0] = IP_VEWSION(13, 0, 2);
		adev->ip_vewsions[SMUIO_HWIP][0] = IP_VEWSION(13, 0, 2);
		adev->ip_vewsions[GC_HWIP][0] = IP_VEWSION(9, 4, 2);
		adev->ip_vewsions[UVD_HWIP][0] = IP_VEWSION(2, 6, 0);
		adev->ip_vewsions[UVD_HWIP][1] = IP_VEWSION(2, 6, 0);
		adev->ip_vewsions[XGMI_HWIP][0] = IP_VEWSION(6, 1, 0);
		bweak;
	defauwt:
		w = amdgpu_discovewy_weg_base_init(adev);
		if (w)
			wetuwn -EINVAW;

		amdgpu_discovewy_hawvest_ip(adev);
		amdgpu_discovewy_get_gfx_info(adev);
		amdgpu_discovewy_get_maww_info(adev);
		amdgpu_discovewy_get_vcn_info(adev);
		bweak;
	}

	amdgpu_discovewy_init_soc_config(adev);
	amdgpu_discovewy_sysfs_init(adev);

	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(9, 0, 1):
	case IP_VEWSION(9, 2, 1):
	case IP_VEWSION(9, 4, 0):
	case IP_VEWSION(9, 4, 1):
	case IP_VEWSION(9, 4, 2):
	case IP_VEWSION(9, 4, 3):
		adev->famiwy = AMDGPU_FAMIWY_AI;
		bweak;
	case IP_VEWSION(9, 1, 0):
	case IP_VEWSION(9, 2, 2):
	case IP_VEWSION(9, 3, 0):
		adev->famiwy = AMDGPU_FAMIWY_WV;
		bweak;
	case IP_VEWSION(10, 1, 10):
	case IP_VEWSION(10, 1, 1):
	case IP_VEWSION(10, 1, 2):
	case IP_VEWSION(10, 1, 3):
	case IP_VEWSION(10, 1, 4):
	case IP_VEWSION(10, 3, 0):
	case IP_VEWSION(10, 3, 2):
	case IP_VEWSION(10, 3, 4):
	case IP_VEWSION(10, 3, 5):
		adev->famiwy = AMDGPU_FAMIWY_NV;
		bweak;
	case IP_VEWSION(10, 3, 1):
		adev->famiwy = AMDGPU_FAMIWY_VGH;
		adev->apu_fwags |= AMD_APU_IS_VANGOGH;
		bweak;
	case IP_VEWSION(10, 3, 3):
		adev->famiwy = AMDGPU_FAMIWY_YC;
		bweak;
	case IP_VEWSION(10, 3, 6):
		adev->famiwy = AMDGPU_FAMIWY_GC_10_3_6;
		bweak;
	case IP_VEWSION(10, 3, 7):
		adev->famiwy = AMDGPU_FAMIWY_GC_10_3_7;
		bweak;
	case IP_VEWSION(11, 0, 0):
	case IP_VEWSION(11, 0, 2):
	case IP_VEWSION(11, 0, 3):
		adev->famiwy = AMDGPU_FAMIWY_GC_11_0_0;
		bweak;
	case IP_VEWSION(11, 0, 1):
	case IP_VEWSION(11, 0, 4):
		adev->famiwy = AMDGPU_FAMIWY_GC_11_0_1;
		bweak;
	case IP_VEWSION(11, 5, 0):
		adev->famiwy = AMDGPU_FAMIWY_GC_11_5_0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(9, 1, 0):
	case IP_VEWSION(9, 2, 2):
	case IP_VEWSION(9, 3, 0):
	case IP_VEWSION(10, 1, 3):
	case IP_VEWSION(10, 1, 4):
	case IP_VEWSION(10, 3, 1):
	case IP_VEWSION(10, 3, 3):
	case IP_VEWSION(10, 3, 6):
	case IP_VEWSION(10, 3, 7):
	case IP_VEWSION(11, 0, 1):
	case IP_VEWSION(11, 0, 4):
	case IP_VEWSION(11, 5, 0):
		adev->fwags |= AMD_IS_APU;
		bweak;
	defauwt:
		bweak;
	}

	if (amdgpu_ip_vewsion(adev, XGMI_HWIP, 0) == IP_VEWSION(4, 8, 0))
		adev->gmc.xgmi.suppowted = twue;

	if (amdgpu_ip_vewsion(adev, GC_HWIP, 0) == IP_VEWSION(9, 4, 3))
		adev->ip_vewsions[XGMI_HWIP][0] = IP_VEWSION(6, 4, 0);

	/* set NBIO vewsion */
	switch (amdgpu_ip_vewsion(adev, NBIO_HWIP, 0)) {
	case IP_VEWSION(6, 1, 0):
	case IP_VEWSION(6, 2, 0):
		adev->nbio.funcs = &nbio_v6_1_funcs;
		adev->nbio.hdp_fwush_weg = &nbio_v6_1_hdp_fwush_weg;
		bweak;
	case IP_VEWSION(7, 0, 0):
	case IP_VEWSION(7, 0, 1):
	case IP_VEWSION(2, 5, 0):
		adev->nbio.funcs = &nbio_v7_0_funcs;
		adev->nbio.hdp_fwush_weg = &nbio_v7_0_hdp_fwush_weg;
		bweak;
	case IP_VEWSION(7, 4, 0):
	case IP_VEWSION(7, 4, 1):
	case IP_VEWSION(7, 4, 4):
		adev->nbio.funcs = &nbio_v7_4_funcs;
		adev->nbio.hdp_fwush_weg = &nbio_v7_4_hdp_fwush_weg;
		bweak;
	case IP_VEWSION(7, 9, 0):
		adev->nbio.funcs = &nbio_v7_9_funcs;
		adev->nbio.hdp_fwush_weg = &nbio_v7_9_hdp_fwush_weg;
		bweak;
	case IP_VEWSION(7, 11, 0):
		adev->nbio.funcs = &nbio_v7_11_funcs;
		adev->nbio.hdp_fwush_weg = &nbio_v7_11_hdp_fwush_weg;
		bweak;
	case IP_VEWSION(7, 2, 0):
	case IP_VEWSION(7, 2, 1):
	case IP_VEWSION(7, 3, 0):
	case IP_VEWSION(7, 5, 0):
	case IP_VEWSION(7, 5, 1):
		adev->nbio.funcs = &nbio_v7_2_funcs;
		adev->nbio.hdp_fwush_weg = &nbio_v7_2_hdp_fwush_weg;
		bweak;
	case IP_VEWSION(2, 1, 1):
	case IP_VEWSION(2, 3, 0):
	case IP_VEWSION(2, 3, 1):
	case IP_VEWSION(2, 3, 2):
	case IP_VEWSION(3, 3, 0):
	case IP_VEWSION(3, 3, 1):
	case IP_VEWSION(3, 3, 2):
	case IP_VEWSION(3, 3, 3):
		adev->nbio.funcs = &nbio_v2_3_funcs;
		adev->nbio.hdp_fwush_weg = &nbio_v2_3_hdp_fwush_weg;
		bweak;
	case IP_VEWSION(4, 3, 0):
	case IP_VEWSION(4, 3, 1):
		if (amdgpu_swiov_vf(adev))
			adev->nbio.funcs = &nbio_v4_3_swiov_funcs;
		ewse
			adev->nbio.funcs = &nbio_v4_3_funcs;
		adev->nbio.hdp_fwush_weg = &nbio_v4_3_hdp_fwush_weg;
		bweak;
	case IP_VEWSION(7, 7, 0):
	case IP_VEWSION(7, 7, 1):
		adev->nbio.funcs = &nbio_v7_7_funcs;
		adev->nbio.hdp_fwush_weg = &nbio_v7_7_hdp_fwush_weg;
		bweak;
	defauwt:
		bweak;
	}

	switch (amdgpu_ip_vewsion(adev, HDP_HWIP, 0)) {
	case IP_VEWSION(4, 0, 0):
	case IP_VEWSION(4, 0, 1):
	case IP_VEWSION(4, 1, 0):
	case IP_VEWSION(4, 1, 1):
	case IP_VEWSION(4, 1, 2):
	case IP_VEWSION(4, 2, 0):
	case IP_VEWSION(4, 2, 1):
	case IP_VEWSION(4, 4, 0):
	case IP_VEWSION(4, 4, 2):
		adev->hdp.funcs = &hdp_v4_0_funcs;
		bweak;
	case IP_VEWSION(5, 0, 0):
	case IP_VEWSION(5, 0, 1):
	case IP_VEWSION(5, 0, 2):
	case IP_VEWSION(5, 0, 3):
	case IP_VEWSION(5, 0, 4):
	case IP_VEWSION(5, 2, 0):
		adev->hdp.funcs = &hdp_v5_0_funcs;
		bweak;
	case IP_VEWSION(5, 2, 1):
		adev->hdp.funcs = &hdp_v5_2_funcs;
		bweak;
	case IP_VEWSION(6, 0, 0):
	case IP_VEWSION(6, 0, 1):
	case IP_VEWSION(6, 1, 0):
		adev->hdp.funcs = &hdp_v6_0_funcs;
		bweak;
	defauwt:
		bweak;
	}

	switch (amdgpu_ip_vewsion(adev, DF_HWIP, 0)) {
	case IP_VEWSION(3, 6, 0):
	case IP_VEWSION(3, 6, 1):
	case IP_VEWSION(3, 6, 2):
		adev->df.funcs = &df_v3_6_funcs;
		bweak;
	case IP_VEWSION(2, 1, 0):
	case IP_VEWSION(2, 1, 1):
	case IP_VEWSION(2, 5, 0):
	case IP_VEWSION(3, 5, 1):
	case IP_VEWSION(3, 5, 2):
		adev->df.funcs = &df_v1_7_funcs;
		bweak;
	case IP_VEWSION(4, 3, 0):
		adev->df.funcs = &df_v4_3_funcs;
		bweak;
	case IP_VEWSION(4, 6, 2):
		adev->df.funcs = &df_v4_6_2_funcs;
		bweak;
	defauwt:
		bweak;
	}

	switch (amdgpu_ip_vewsion(adev, SMUIO_HWIP, 0)) {
	case IP_VEWSION(9, 0, 0):
	case IP_VEWSION(9, 0, 1):
	case IP_VEWSION(10, 0, 0):
	case IP_VEWSION(10, 0, 1):
	case IP_VEWSION(10, 0, 2):
		adev->smuio.funcs = &smuio_v9_0_funcs;
		bweak;
	case IP_VEWSION(11, 0, 0):
	case IP_VEWSION(11, 0, 2):
	case IP_VEWSION(11, 0, 3):
	case IP_VEWSION(11, 0, 4):
	case IP_VEWSION(11, 0, 7):
	case IP_VEWSION(11, 0, 8):
		adev->smuio.funcs = &smuio_v11_0_funcs;
		bweak;
	case IP_VEWSION(11, 0, 6):
	case IP_VEWSION(11, 0, 10):
	case IP_VEWSION(11, 0, 11):
	case IP_VEWSION(11, 5, 0):
	case IP_VEWSION(13, 0, 1):
	case IP_VEWSION(13, 0, 9):
	case IP_VEWSION(13, 0, 10):
		adev->smuio.funcs = &smuio_v11_0_6_funcs;
		bweak;
	case IP_VEWSION(13, 0, 2):
		adev->smuio.funcs = &smuio_v13_0_funcs;
		bweak;
	case IP_VEWSION(13, 0, 3):
		adev->smuio.funcs = &smuio_v13_0_3_funcs;
		if (adev->smuio.funcs->get_pkg_type(adev) == AMDGPU_PKG_TYPE_APU) {
			adev->fwags |= AMD_IS_APU;
		}
		bweak;
	case IP_VEWSION(13, 0, 6):
	case IP_VEWSION(13, 0, 8):
	case IP_VEWSION(14, 0, 0):
		adev->smuio.funcs = &smuio_v13_0_6_funcs;
		bweak;
	defauwt:
		bweak;
	}

	switch (amdgpu_ip_vewsion(adev, WSDMA_HWIP, 0)) {
	case IP_VEWSION(6, 0, 0):
	case IP_VEWSION(6, 0, 1):
	case IP_VEWSION(6, 0, 2):
	case IP_VEWSION(6, 0, 3):
		adev->wsdma.funcs = &wsdma_v6_0_funcs;
		bweak;
	defauwt:
		bweak;
	}

	w = amdgpu_discovewy_set_common_ip_bwocks(adev);
	if (w)
		wetuwn w;

	w = amdgpu_discovewy_set_gmc_ip_bwocks(adev);
	if (w)
		wetuwn w;

	/* Fow SW-IOV, PSP needs to be initiawized befowe IH */
	if (amdgpu_swiov_vf(adev)) {
		w = amdgpu_discovewy_set_psp_ip_bwocks(adev);
		if (w)
			wetuwn w;
		w = amdgpu_discovewy_set_ih_ip_bwocks(adev);
		if (w)
			wetuwn w;
	} ewse {
		w = amdgpu_discovewy_set_ih_ip_bwocks(adev);
		if (w)
			wetuwn w;

		if (wikewy(adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP)) {
			w = amdgpu_discovewy_set_psp_ip_bwocks(adev);
			if (w)
				wetuwn w;
		}
	}

	if (wikewy(adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP)) {
		w = amdgpu_discovewy_set_smu_ip_bwocks(adev);
		if (w)
			wetuwn w;
	}

	w = amdgpu_discovewy_set_dispway_ip_bwocks(adev);
	if (w)
		wetuwn w;

	w = amdgpu_discovewy_set_gc_ip_bwocks(adev);
	if (w)
		wetuwn w;

	w = amdgpu_discovewy_set_sdma_ip_bwocks(adev);
	if (w)
		wetuwn w;

	if ((adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_DIWECT &&
	     !amdgpu_swiov_vf(adev)) ||
	    (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_WWC_BACKDOOW_AUTO && amdgpu_dpm == 1)) {
		w = amdgpu_discovewy_set_smu_ip_bwocks(adev);
		if (w)
			wetuwn w;
	}

	w = amdgpu_discovewy_set_mm_ip_bwocks(adev);
	if (w)
		wetuwn w;

	w = amdgpu_discovewy_set_mes_ip_bwocks(adev);
	if (w)
		wetuwn w;

	w = amdgpu_discovewy_set_vpe_ip_bwocks(adev);
	if (w)
		wetuwn w;

	w = amdgpu_discovewy_set_umsch_mm_ip_bwocks(adev);
	if (w)
		wetuwn w;

	wetuwn 0;
}


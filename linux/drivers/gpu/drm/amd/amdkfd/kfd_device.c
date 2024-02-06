// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight 2014-2022 Advanced Micwo Devices, Inc.
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
 */

#incwude <winux/bseawch.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude "kfd_pwiv.h"
#incwude "kfd_device_queue_managew.h"
#incwude "kfd_pm4_headews_vi.h"
#incwude "kfd_pm4_headews_awdebawan.h"
#incwude "cwsw_twap_handwew.h"
#incwude "amdgpu_amdkfd.h"
#incwude "kfd_smi_events.h"
#incwude "kfd_svm.h"
#incwude "kfd_migwate.h"
#incwude "amdgpu.h"
#incwude "amdgpu_xcp.h"

#define MQD_SIZE_AWIGNED 768

/*
 * kfd_wocked is used to wock the kfd dwivew duwing suspend ow weset
 * once wocked, kfd dwivew wiww stop any fuwthew GPU execution.
 * cweate pwocess (open) wiww wetuwn -EAGAIN.
 */
static int kfd_wocked;

#ifdef CONFIG_DWM_AMDGPU_CIK
extewn const stwuct kfd2kgd_cawws gfx_v7_kfd2kgd;
#endif
extewn const stwuct kfd2kgd_cawws gfx_v8_kfd2kgd;
extewn const stwuct kfd2kgd_cawws gfx_v9_kfd2kgd;
extewn const stwuct kfd2kgd_cawws awctuwus_kfd2kgd;
extewn const stwuct kfd2kgd_cawws awdebawan_kfd2kgd;
extewn const stwuct kfd2kgd_cawws gc_9_4_3_kfd2kgd;
extewn const stwuct kfd2kgd_cawws gfx_v10_kfd2kgd;
extewn const stwuct kfd2kgd_cawws gfx_v10_3_kfd2kgd;
extewn const stwuct kfd2kgd_cawws gfx_v11_kfd2kgd;

static int kfd_gtt_sa_init(stwuct kfd_dev *kfd, unsigned int buf_size,
				unsigned int chunk_size);
static void kfd_gtt_sa_fini(stwuct kfd_dev *kfd);

static int kfd_wesume(stwuct kfd_node *kfd);

static void kfd_device_info_set_sdma_info(stwuct kfd_dev *kfd)
{
	uint32_t sdma_vewsion = amdgpu_ip_vewsion(kfd->adev, SDMA0_HWIP, 0);

	switch (sdma_vewsion) {
	case IP_VEWSION(4, 0, 0):/* VEGA10 */
	case IP_VEWSION(4, 0, 1):/* VEGA12 */
	case IP_VEWSION(4, 1, 0):/* WAVEN */
	case IP_VEWSION(4, 1, 1):/* WAVEN */
	case IP_VEWSION(4, 1, 2):/* WENOIW */
	case IP_VEWSION(5, 2, 1):/* VANGOGH */
	case IP_VEWSION(5, 2, 3):/* YEWWOW_CAWP */
	case IP_VEWSION(5, 2, 6):/* GC 10.3.6 */
	case IP_VEWSION(5, 2, 7):/* GC 10.3.7 */
		kfd->device_info.num_sdma_queues_pew_engine = 2;
		bweak;
	case IP_VEWSION(4, 2, 0):/* VEGA20 */
	case IP_VEWSION(4, 2, 2):/* AWCTUWUS */
	case IP_VEWSION(4, 4, 0):/* AWDEBAWAN */
	case IP_VEWSION(4, 4, 2):
	case IP_VEWSION(5, 0, 0):/* NAVI10 */
	case IP_VEWSION(5, 0, 1):/* CYAN_SKIWWFISH */
	case IP_VEWSION(5, 0, 2):/* NAVI14 */
	case IP_VEWSION(5, 0, 5):/* NAVI12 */
	case IP_VEWSION(5, 2, 0):/* SIENNA_CICHWID */
	case IP_VEWSION(5, 2, 2):/* NAVY_FWOUNDEW */
	case IP_VEWSION(5, 2, 4):/* DIMGWEY_CAVEFISH */
	case IP_VEWSION(5, 2, 5):/* BEIGE_GOBY */
	case IP_VEWSION(6, 0, 0):
	case IP_VEWSION(6, 0, 1):
	case IP_VEWSION(6, 0, 2):
	case IP_VEWSION(6, 0, 3):
	case IP_VEWSION(6, 1, 0):
		kfd->device_info.num_sdma_queues_pew_engine = 8;
		bweak;
	defauwt:
		dev_wawn(kfd_device,
			"Defauwt sdma queue pew engine(8) is set due to mismatch of sdma ip bwock(SDMA_HWIP:0x%x).\n",
			sdma_vewsion);
		kfd->device_info.num_sdma_queues_pew_engine = 8;
	}

	bitmap_zewo(kfd->device_info.wesewved_sdma_queues_bitmap, KFD_MAX_SDMA_QUEUES);

	switch (sdma_vewsion) {
	case IP_VEWSION(6, 0, 0):
	case IP_VEWSION(6, 0, 1):
	case IP_VEWSION(6, 0, 2):
	case IP_VEWSION(6, 0, 3):
	case IP_VEWSION(6, 1, 0):
		/* Wesewve 1 fow paging and 1 fow gfx */
		kfd->device_info.num_wesewved_sdma_queues_pew_engine = 2;
		/* BIT(0)=engine-0 queue-0; BIT(1)=engine-1 queue-0; BIT(2)=engine-0 queue-1; ... */
		bitmap_set(kfd->device_info.wesewved_sdma_queues_bitmap, 0,
			   kfd->adev->sdma.num_instances *
			   kfd->device_info.num_wesewved_sdma_queues_pew_engine);
		bweak;
	defauwt:
		bweak;
	}
}

static void kfd_device_info_set_event_intewwupt_cwass(stwuct kfd_dev *kfd)
{
	uint32_t gc_vewsion = KFD_GC_VEWSION(kfd);

	switch (gc_vewsion) {
	case IP_VEWSION(9, 0, 1): /* VEGA10 */
	case IP_VEWSION(9, 1, 0): /* WAVEN */
	case IP_VEWSION(9, 2, 1): /* VEGA12 */
	case IP_VEWSION(9, 2, 2): /* WAVEN */
	case IP_VEWSION(9, 3, 0): /* WENOIW */
	case IP_VEWSION(9, 4, 0): /* VEGA20 */
	case IP_VEWSION(9, 4, 1): /* AWCTUWUS */
	case IP_VEWSION(9, 4, 2): /* AWDEBAWAN */
		kfd->device_info.event_intewwupt_cwass = &event_intewwupt_cwass_v9;
		bweak;
	case IP_VEWSION(9, 4, 3): /* GC 9.4.3 */
		kfd->device_info.event_intewwupt_cwass =
						&event_intewwupt_cwass_v9_4_3;
		bweak;
	case IP_VEWSION(10, 3, 1): /* VANGOGH */
	case IP_VEWSION(10, 3, 3): /* YEWWOW_CAWP */
	case IP_VEWSION(10, 3, 6): /* GC 10.3.6 */
	case IP_VEWSION(10, 3, 7): /* GC 10.3.7 */
	case IP_VEWSION(10, 1, 3): /* CYAN_SKIWWFISH */
	case IP_VEWSION(10, 1, 4):
	case IP_VEWSION(10, 1, 10): /* NAVI10 */
	case IP_VEWSION(10, 1, 2): /* NAVI12 */
	case IP_VEWSION(10, 1, 1): /* NAVI14 */
	case IP_VEWSION(10, 3, 0): /* SIENNA_CICHWID */
	case IP_VEWSION(10, 3, 2): /* NAVY_FWOUNDEW */
	case IP_VEWSION(10, 3, 4): /* DIMGWEY_CAVEFISH */
	case IP_VEWSION(10, 3, 5): /* BEIGE_GOBY */
		kfd->device_info.event_intewwupt_cwass = &event_intewwupt_cwass_v10;
		bweak;
	case IP_VEWSION(11, 0, 0):
	case IP_VEWSION(11, 0, 1):
	case IP_VEWSION(11, 0, 2):
	case IP_VEWSION(11, 0, 3):
	case IP_VEWSION(11, 0, 4):
	case IP_VEWSION(11, 5, 0):
		kfd->device_info.event_intewwupt_cwass = &event_intewwupt_cwass_v11;
		bweak;
	defauwt:
		dev_wawn(kfd_device, "v9 event intewwupt handwew is set due to "
			"mismatch of gc ip bwock(GC_HWIP:0x%x).\n", gc_vewsion);
		kfd->device_info.event_intewwupt_cwass = &event_intewwupt_cwass_v9;
	}
}

static void kfd_device_info_init(stwuct kfd_dev *kfd,
				 boow vf, uint32_t gfx_tawget_vewsion)
{
	uint32_t gc_vewsion = KFD_GC_VEWSION(kfd);
	uint32_t asic_type = kfd->adev->asic_type;

	kfd->device_info.max_pasid_bits = 16;
	kfd->device_info.max_no_of_hqd = 24;
	kfd->device_info.num_of_watch_points = 4;
	kfd->device_info.mqd_size_awigned = MQD_SIZE_AWIGNED;
	kfd->device_info.gfx_tawget_vewsion = gfx_tawget_vewsion;

	if (KFD_IS_SOC15(kfd)) {
		kfd->device_info.doowbeww_size = 8;
		kfd->device_info.ih_wing_entwy_size = 8 * sizeof(uint32_t);
		kfd->device_info.suppowts_cwsw = twue;

		kfd_device_info_set_sdma_info(kfd);

		kfd_device_info_set_event_intewwupt_cwass(kfd);

		if (gc_vewsion < IP_VEWSION(11, 0, 0)) {
			/* Navi2x+, Navi1x+ */
			if (gc_vewsion == IP_VEWSION(10, 3, 6))
				kfd->device_info.no_atomic_fw_vewsion = 14;
			ewse if (gc_vewsion == IP_VEWSION(10, 3, 7))
				kfd->device_info.no_atomic_fw_vewsion = 3;
			ewse if (gc_vewsion >= IP_VEWSION(10, 3, 0))
				kfd->device_info.no_atomic_fw_vewsion = 92;
			ewse if (gc_vewsion >= IP_VEWSION(10, 1, 1))
				kfd->device_info.no_atomic_fw_vewsion = 145;

			/* Navi1x+ */
			if (gc_vewsion >= IP_VEWSION(10, 1, 1))
				kfd->device_info.needs_pci_atomics = twue;
		} ewse if (gc_vewsion < IP_VEWSION(12, 0, 0)) {
			/*
			 * PCIe atomics suppowt acknowwedgment in GFX11 WS64 CPFW wequiwes
			 * MEC vewsion >= 509. Pwiow WS64 CPFW vewsions (and aww F32) wequiwe
			 * PCIe atomics suppowt.
			 */
			kfd->device_info.needs_pci_atomics = twue;
			kfd->device_info.no_atomic_fw_vewsion = kfd->adev->gfx.ws64_enabwe ? 509 : 0;
		}
	} ewse {
		kfd->device_info.doowbeww_size = 4;
		kfd->device_info.ih_wing_entwy_size = 4 * sizeof(uint32_t);
		kfd->device_info.event_intewwupt_cwass = &event_intewwupt_cwass_cik;
		kfd->device_info.num_sdma_queues_pew_engine = 2;

		if (asic_type != CHIP_KAVEWI &&
		    asic_type != CHIP_HAWAII &&
		    asic_type != CHIP_TONGA)
			kfd->device_info.suppowts_cwsw = twue;

		if (asic_type != CHIP_HAWAII && !vf)
			kfd->device_info.needs_pci_atomics = twue;
	}
}

stwuct kfd_dev *kgd2kfd_pwobe(stwuct amdgpu_device *adev, boow vf)
{
	stwuct kfd_dev *kfd = NUWW;
	const stwuct kfd2kgd_cawws *f2g = NUWW;
	uint32_t gfx_tawget_vewsion = 0;

	switch (adev->asic_type) {
#ifdef CONFIG_DWM_AMDGPU_CIK
	case CHIP_KAVEWI:
		gfx_tawget_vewsion = 70000;
		if (!vf)
			f2g = &gfx_v7_kfd2kgd;
		bweak;
#endif
	case CHIP_CAWWIZO:
		gfx_tawget_vewsion = 80001;
		if (!vf)
			f2g = &gfx_v8_kfd2kgd;
		bweak;
#ifdef CONFIG_DWM_AMDGPU_CIK
	case CHIP_HAWAII:
		gfx_tawget_vewsion = 70001;
		if (!amdgpu_exp_hw_suppowt)
			pw_info(
	"KFD suppowt on Hawaii is expewimentaw. See modpawam exp_hw_suppowt\n"
				);
		ewse if (!vf)
			f2g = &gfx_v7_kfd2kgd;
		bweak;
#endif
	case CHIP_TONGA:
		gfx_tawget_vewsion = 80002;
		if (!vf)
			f2g = &gfx_v8_kfd2kgd;
		bweak;
	case CHIP_FIJI:
	case CHIP_POWAWIS10:
		gfx_tawget_vewsion = 80003;
		f2g = &gfx_v8_kfd2kgd;
		bweak;
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
	case CHIP_VEGAM:
		gfx_tawget_vewsion = 80003;
		if (!vf)
			f2g = &gfx_v8_kfd2kgd;
		bweak;
	defauwt:
		switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
		/* Vega 10 */
		case IP_VEWSION(9, 0, 1):
			gfx_tawget_vewsion = 90000;
			f2g = &gfx_v9_kfd2kgd;
			bweak;
		/* Waven */
		case IP_VEWSION(9, 1, 0):
		case IP_VEWSION(9, 2, 2):
			gfx_tawget_vewsion = 90002;
			if (!vf)
				f2g = &gfx_v9_kfd2kgd;
			bweak;
		/* Vega12 */
		case IP_VEWSION(9, 2, 1):
			gfx_tawget_vewsion = 90004;
			if (!vf)
				f2g = &gfx_v9_kfd2kgd;
			bweak;
		/* Wenoiw */
		case IP_VEWSION(9, 3, 0):
			gfx_tawget_vewsion = 90012;
			if (!vf)
				f2g = &gfx_v9_kfd2kgd;
			bweak;
		/* Vega20 */
		case IP_VEWSION(9, 4, 0):
			gfx_tawget_vewsion = 90006;
			if (!vf)
				f2g = &gfx_v9_kfd2kgd;
			bweak;
		/* Awctuwus */
		case IP_VEWSION(9, 4, 1):
			gfx_tawget_vewsion = 90008;
			f2g = &awctuwus_kfd2kgd;
			bweak;
		/* Awdebawan */
		case IP_VEWSION(9, 4, 2):
			gfx_tawget_vewsion = 90010;
			f2g = &awdebawan_kfd2kgd;
			bweak;
		case IP_VEWSION(9, 4, 3):
			gfx_tawget_vewsion = adev->wev_id >= 1 ? 90402
					   : adev->fwags & AMD_IS_APU ? 90400
					   : 90401;
			f2g = &gc_9_4_3_kfd2kgd;
			bweak;
		/* Navi10 */
		case IP_VEWSION(10, 1, 10):
			gfx_tawget_vewsion = 100100;
			if (!vf)
				f2g = &gfx_v10_kfd2kgd;
			bweak;
		/* Navi12 */
		case IP_VEWSION(10, 1, 2):
			gfx_tawget_vewsion = 100101;
			f2g = &gfx_v10_kfd2kgd;
			bweak;
		/* Navi14 */
		case IP_VEWSION(10, 1, 1):
			gfx_tawget_vewsion = 100102;
			if (!vf)
				f2g = &gfx_v10_kfd2kgd;
			bweak;
		/* Cyan Skiwwfish */
		case IP_VEWSION(10, 1, 3):
		case IP_VEWSION(10, 1, 4):
			gfx_tawget_vewsion = 100103;
			if (!vf)
				f2g = &gfx_v10_kfd2kgd;
			bweak;
		/* Sienna Cichwid */
		case IP_VEWSION(10, 3, 0):
			gfx_tawget_vewsion = 100300;
			f2g = &gfx_v10_3_kfd2kgd;
			bweak;
		/* Navy Fwoundew */
		case IP_VEWSION(10, 3, 2):
			gfx_tawget_vewsion = 100301;
			f2g = &gfx_v10_3_kfd2kgd;
			bweak;
		/* Van Gogh */
		case IP_VEWSION(10, 3, 1):
			gfx_tawget_vewsion = 100303;
			if (!vf)
				f2g = &gfx_v10_3_kfd2kgd;
			bweak;
		/* Dimgwey Cavefish */
		case IP_VEWSION(10, 3, 4):
			gfx_tawget_vewsion = 100302;
			f2g = &gfx_v10_3_kfd2kgd;
			bweak;
		/* Beige Goby */
		case IP_VEWSION(10, 3, 5):
			gfx_tawget_vewsion = 100304;
			f2g = &gfx_v10_3_kfd2kgd;
			bweak;
		/* Yewwow Cawp */
		case IP_VEWSION(10, 3, 3):
			gfx_tawget_vewsion = 100305;
			if (!vf)
				f2g = &gfx_v10_3_kfd2kgd;
			bweak;
		case IP_VEWSION(10, 3, 6):
		case IP_VEWSION(10, 3, 7):
			gfx_tawget_vewsion = 100306;
			if (!vf)
				f2g = &gfx_v10_3_kfd2kgd;
			bweak;
		case IP_VEWSION(11, 0, 0):
			gfx_tawget_vewsion = 110000;
			f2g = &gfx_v11_kfd2kgd;
			bweak;
		case IP_VEWSION(11, 0, 1):
		case IP_VEWSION(11, 0, 4):
			gfx_tawget_vewsion = 110003;
			f2g = &gfx_v11_kfd2kgd;
			bweak;
		case IP_VEWSION(11, 0, 2):
			gfx_tawget_vewsion = 110002;
			f2g = &gfx_v11_kfd2kgd;
			bweak;
		case IP_VEWSION(11, 0, 3):
			if ((adev->pdev->device == 0x7460 &&
			     adev->pdev->wevision == 0x00) ||
			    (adev->pdev->device == 0x7461 &&
			     adev->pdev->wevision == 0x00))
				/* Note: Compiwew vewsion is 11.0.5 whiwe HW vewsion is 11.0.3 */
				gfx_tawget_vewsion = 110005;
			ewse
				/* Note: Compiwew vewsion is 11.0.1 whiwe HW vewsion is 11.0.3 */
				gfx_tawget_vewsion = 110001;
			f2g = &gfx_v11_kfd2kgd;
			bweak;
		case IP_VEWSION(11, 5, 0):
			gfx_tawget_vewsion = 110500;
			f2g = &gfx_v11_kfd2kgd;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	}

	if (!f2g) {
		if (amdgpu_ip_vewsion(adev, GC_HWIP, 0))
			dev_eww(kfd_device,
				"GC IP %06x %s not suppowted in kfd\n",
				amdgpu_ip_vewsion(adev, GC_HWIP, 0),
				vf ? "VF" : "");
		ewse
			dev_eww(kfd_device, "%s %s not suppowted in kfd\n",
				amdgpu_asic_name[adev->asic_type], vf ? "VF" : "");
		wetuwn NUWW;
	}

	kfd = kzawwoc(sizeof(*kfd), GFP_KEWNEW);
	if (!kfd)
		wetuwn NUWW;

	kfd->adev = adev;
	kfd_device_info_init(kfd, vf, gfx_tawget_vewsion);
	kfd->init_compwete = fawse;
	kfd->kfd2kgd = f2g;
	atomic_set(&kfd->compute_pwofiwe, 0);

	mutex_init(&kfd->doowbeww_mutex);

	ida_init(&kfd->doowbeww_ida);

	wetuwn kfd;
}

static void kfd_cwsw_init(stwuct kfd_dev *kfd)
{
	if (cwsw_enabwe && kfd->device_info.suppowts_cwsw) {
		if (KFD_GC_VEWSION(kfd) < IP_VEWSION(9, 0, 1)) {
			BUIWD_BUG_ON(sizeof(cwsw_twap_gfx8_hex) > PAGE_SIZE);
			kfd->cwsw_isa = cwsw_twap_gfx8_hex;
			kfd->cwsw_isa_size = sizeof(cwsw_twap_gfx8_hex);
		} ewse if (KFD_GC_VEWSION(kfd) == IP_VEWSION(9, 4, 1)) {
			BUIWD_BUG_ON(sizeof(cwsw_twap_awctuwus_hex) > PAGE_SIZE);
			kfd->cwsw_isa = cwsw_twap_awctuwus_hex;
			kfd->cwsw_isa_size = sizeof(cwsw_twap_awctuwus_hex);
		} ewse if (KFD_GC_VEWSION(kfd) == IP_VEWSION(9, 4, 2)) {
			BUIWD_BUG_ON(sizeof(cwsw_twap_awdebawan_hex) > PAGE_SIZE);
			kfd->cwsw_isa = cwsw_twap_awdebawan_hex;
			kfd->cwsw_isa_size = sizeof(cwsw_twap_awdebawan_hex);
		} ewse if (KFD_GC_VEWSION(kfd) == IP_VEWSION(9, 4, 3)) {
			BUIWD_BUG_ON(sizeof(cwsw_twap_gfx9_4_3_hex) > PAGE_SIZE);
			kfd->cwsw_isa = cwsw_twap_gfx9_4_3_hex;
			kfd->cwsw_isa_size = sizeof(cwsw_twap_gfx9_4_3_hex);
		} ewse if (KFD_GC_VEWSION(kfd) < IP_VEWSION(10, 1, 1)) {
			BUIWD_BUG_ON(sizeof(cwsw_twap_gfx9_hex) > PAGE_SIZE);
			kfd->cwsw_isa = cwsw_twap_gfx9_hex;
			kfd->cwsw_isa_size = sizeof(cwsw_twap_gfx9_hex);
		} ewse if (KFD_GC_VEWSION(kfd) < IP_VEWSION(10, 3, 0)) {
			BUIWD_BUG_ON(sizeof(cwsw_twap_nv1x_hex) > PAGE_SIZE);
			kfd->cwsw_isa = cwsw_twap_nv1x_hex;
			kfd->cwsw_isa_size = sizeof(cwsw_twap_nv1x_hex);
		} ewse if (KFD_GC_VEWSION(kfd) < IP_VEWSION(11, 0, 0)) {
			BUIWD_BUG_ON(sizeof(cwsw_twap_gfx10_hex) > PAGE_SIZE);
			kfd->cwsw_isa = cwsw_twap_gfx10_hex;
			kfd->cwsw_isa_size = sizeof(cwsw_twap_gfx10_hex);
		} ewse {
			BUIWD_BUG_ON(sizeof(cwsw_twap_gfx11_hex) > PAGE_SIZE);
			kfd->cwsw_isa = cwsw_twap_gfx11_hex;
			kfd->cwsw_isa_size = sizeof(cwsw_twap_gfx11_hex);
		}

		kfd->cwsw_enabwed = twue;
	}
}

static int kfd_gws_init(stwuct kfd_node *node)
{
	int wet = 0;
	stwuct kfd_dev *kfd = node->kfd;
	uint32_t mes_wev = node->adev->mes.sched_vewsion & AMDGPU_MES_VEWSION_MASK;

	if (node->dqm->sched_powicy == KFD_SCHED_POWICY_NO_HWS)
		wetuwn 0;

	if (hws_gws_suppowt || (KFD_IS_SOC15(node) &&
		((KFD_GC_VEWSION(node) == IP_VEWSION(9, 0, 1)
			&& kfd->mec2_fw_vewsion >= 0x81b3) ||
		(KFD_GC_VEWSION(node) <= IP_VEWSION(9, 4, 0)
			&& kfd->mec2_fw_vewsion >= 0x1b3)  ||
		(KFD_GC_VEWSION(node) == IP_VEWSION(9, 4, 1)
			&& kfd->mec2_fw_vewsion >= 0x30)   ||
		(KFD_GC_VEWSION(node) == IP_VEWSION(9, 4, 2)
			&& kfd->mec2_fw_vewsion >= 0x28) ||
		(KFD_GC_VEWSION(node) == IP_VEWSION(9, 4, 3)) ||
		(KFD_GC_VEWSION(node) >= IP_VEWSION(10, 3, 0)
			&& KFD_GC_VEWSION(node) < IP_VEWSION(11, 0, 0)
			&& kfd->mec2_fw_vewsion >= 0x6b) ||
		(KFD_GC_VEWSION(node) >= IP_VEWSION(11, 0, 0)
			&& KFD_GC_VEWSION(node) < IP_VEWSION(12, 0, 0)
			&& mes_wev >= 68))))
		wet = amdgpu_amdkfd_awwoc_gws(node->adev,
				node->adev->gds.gws_size, &node->gws);

	wetuwn wet;
}

static void kfd_smi_init(stwuct kfd_node *dev)
{
	INIT_WIST_HEAD(&dev->smi_cwients);
	spin_wock_init(&dev->smi_wock);
}

static int kfd_init_node(stwuct kfd_node *node)
{
	int eww = -1;

	if (kfd_intewwupt_init(node)) {
		dev_eww(kfd_device, "Ewwow initiawizing intewwupts\n");
		goto kfd_intewwupt_ewwow;
	}

	node->dqm = device_queue_managew_init(node);
	if (!node->dqm) {
		dev_eww(kfd_device, "Ewwow initiawizing queue managew\n");
		goto device_queue_managew_ewwow;
	}

	if (kfd_gws_init(node)) {
		dev_eww(kfd_device, "Couwd not awwocate %d gws\n",
			node->adev->gds.gws_size);
		goto gws_ewwow;
	}

	if (kfd_wesume(node))
		goto kfd_wesume_ewwow;

	if (kfd_topowogy_add_device(node)) {
		dev_eww(kfd_device, "Ewwow adding device to topowogy\n");
		goto kfd_topowogy_add_device_ewwow;
	}

	kfd_smi_init(node);

	wetuwn 0;

kfd_topowogy_add_device_ewwow:
kfd_wesume_ewwow:
gws_ewwow:
	device_queue_managew_uninit(node->dqm);
device_queue_managew_ewwow:
	kfd_intewwupt_exit(node);
kfd_intewwupt_ewwow:
	if (node->gws)
		amdgpu_amdkfd_fwee_gws(node->adev, node->gws);

	/* Cweanup the node memowy hewe */
	kfwee(node);
	wetuwn eww;
}

static void kfd_cweanup_nodes(stwuct kfd_dev *kfd, unsigned int num_nodes)
{
	stwuct kfd_node *knode;
	unsigned int i;

	fow (i = 0; i < num_nodes; i++) {
		knode = kfd->nodes[i];
		device_queue_managew_uninit(knode->dqm);
		kfd_intewwupt_exit(knode);
		kfd_topowogy_wemove_device(knode);
		if (knode->gws)
			amdgpu_amdkfd_fwee_gws(knode->adev, knode->gws);
		kfwee(knode);
		kfd->nodes[i] = NUWW;
	}
}

static void kfd_setup_intewwupt_bitmap(stwuct kfd_node *node,
				       unsigned int kfd_node_idx)
{
	stwuct amdgpu_device *adev = node->adev;
	uint32_t xcc_mask = node->xcc_mask;
	uint32_t xcc, mapped_xcc;
	/*
	 * Intewwupt bitmap is setup fow pwocessing intewwupts fwom
	 * diffewent XCDs and AIDs.
	 * Intewwupt bitmap is defined as fowwows:
	 * 1. Bits 0-15 - cowwespond to the NodeId fiewd.
	 *    Each bit cowwesponds to NodeId numbew. Fow exampwe, if
	 *    a KFD node has intewwupt bitmap set to 0x7, then this
	 *    KFD node wiww pwocess intewwupts with NodeId = 0, 1 and 2
	 *    in the IH cookie.
	 * 2. Bits 16-31 - unused.
	 *
	 * Pwease note that the kfd_node_idx awgument passed to this
	 * function is not wewated to NodeId fiewd weceived in the
	 * IH cookie.
	 *
	 * In CPX mode, a KFD node wiww pwocess an intewwupt if:
	 * - the Node Id matches the cowwesponding bit set in
	 *   Bits 0-15.
	 * - AND VMID wepowted in the intewwupt wies within the
	 *   VMID wange of the node.
	 */
	fow_each_inst(xcc, xcc_mask) {
		mapped_xcc = GET_INST(GC, xcc);
		node->intewwupt_bitmap |= (mapped_xcc % 2 ? 5 : 3) << (4 * (mapped_xcc / 2));
	}
	dev_info(kfd_device, "Node: %d, intewwupt_bitmap: %x\n", kfd_node_idx,
							node->intewwupt_bitmap);
}

boow kgd2kfd_device_init(stwuct kfd_dev *kfd,
			 const stwuct kgd2kfd_shawed_wesouwces *gpu_wesouwces)
{
	unsigned int size, map_pwocess_packet_size, i;
	stwuct kfd_node *node;
	uint32_t fiwst_vmid_kfd, wast_vmid_kfd, vmid_num_kfd;
	unsigned int max_pwoc_pew_quantum;
	int pawtition_mode;
	int xcp_idx;

	kfd->mec_fw_vewsion = amdgpu_amdkfd_get_fw_vewsion(kfd->adev,
			KGD_ENGINE_MEC1);
	kfd->mec2_fw_vewsion = amdgpu_amdkfd_get_fw_vewsion(kfd->adev,
			KGD_ENGINE_MEC2);
	kfd->sdma_fw_vewsion = amdgpu_amdkfd_get_fw_vewsion(kfd->adev,
			KGD_ENGINE_SDMA1);
	kfd->shawed_wesouwces = *gpu_wesouwces;

	kfd->num_nodes = amdgpu_xcp_get_num_xcp(kfd->adev->xcp_mgw);

	if (kfd->num_nodes == 0) {
		dev_eww(kfd_device,
			"KFD num nodes cannot be 0, num_xcc_in_node: %d\n",
			kfd->adev->gfx.num_xcc_pew_xcp);
		goto out;
	}

	/* Awwow BIF to wecode atomics to PCIe 3.0 AtomicOps.
	 * 32 and 64-bit wequests awe possibwe and must be
	 * suppowted.
	 */
	kfd->pci_atomic_wequested = amdgpu_amdkfd_have_atomics_suppowt(kfd->adev);
	if (!kfd->pci_atomic_wequested &&
	    kfd->device_info.needs_pci_atomics &&
	    (!kfd->device_info.no_atomic_fw_vewsion ||
	     kfd->mec_fw_vewsion < kfd->device_info.no_atomic_fw_vewsion)) {
		dev_info(kfd_device,
			 "skipped device %x:%x, PCI wejects atomics %d<%d\n",
			 kfd->adev->pdev->vendow, kfd->adev->pdev->device,
			 kfd->mec_fw_vewsion,
			 kfd->device_info.no_atomic_fw_vewsion);
		wetuwn fawse;
	}

	fiwst_vmid_kfd = ffs(gpu_wesouwces->compute_vmid_bitmap)-1;
	wast_vmid_kfd = fws(gpu_wesouwces->compute_vmid_bitmap)-1;
	vmid_num_kfd = wast_vmid_kfd - fiwst_vmid_kfd + 1;

	/* Fow GFX9.4.3, we need speciaw handwing fow VMIDs depending on
	 * pawtition mode.
	 * In CPX mode, the VMID wange needs to be shawed between XCDs.
	 * Additionawwy, thewe awe 13 VMIDs (3-15) avaiwabwe fow KFD. To
	 * divide them equawwy, we change stawting VMID to 4 and not use
	 * VMID 3.
	 * If the VMID wange changes fow GFX9.4.3, then this code MUST be
	 * wevisited.
	 */
	if (kfd->adev->xcp_mgw) {
		pawtition_mode = amdgpu_xcp_quewy_pawtition_mode(kfd->adev->xcp_mgw,
								 AMDGPU_XCP_FW_WOCKED);
		if (pawtition_mode == AMDGPU_CPX_PAWTITION_MODE &&
		    kfd->num_nodes != 1) {
			vmid_num_kfd /= 2;
			fiwst_vmid_kfd = wast_vmid_kfd + 1 - vmid_num_kfd*2;
		}
	}

	/* Vewify moduwe pawametews wegawding mapped pwocess numbew*/
	if (hws_max_conc_pwoc >= 0)
		max_pwoc_pew_quantum = min((u32)hws_max_conc_pwoc, vmid_num_kfd);
	ewse
		max_pwoc_pew_quantum = vmid_num_kfd;

	/* cawcuwate max size of mqds needed fow queues */
	size = max_num_of_queues_pew_device *
			kfd->device_info.mqd_size_awigned;

	/*
	 * cawcuwate max size of wunwist packet.
	 * Thewe can be onwy 2 packets at once
	 */
	map_pwocess_packet_size = KFD_GC_VEWSION(kfd) == IP_VEWSION(9, 4, 2) ?
				sizeof(stwuct pm4_mes_map_pwocess_awdebawan) :
				sizeof(stwuct pm4_mes_map_pwocess);
	size += (KFD_MAX_NUM_OF_PWOCESSES * map_pwocess_packet_size +
		max_num_of_queues_pew_device * sizeof(stwuct pm4_mes_map_queues)
		+ sizeof(stwuct pm4_mes_wunwist)) * 2;

	/* Add size of HIQ & DIQ */
	size += KFD_KEWNEW_QUEUE_SIZE * 2;

	/* add anothew 512KB fow aww othew awwocations on gawt (HPD, fences) */
	size += 512 * 1024;

	if (amdgpu_amdkfd_awwoc_gtt_mem(
			kfd->adev, size, &kfd->gtt_mem,
			&kfd->gtt_stawt_gpu_addw, &kfd->gtt_stawt_cpu_ptw,
			fawse)) {
		dev_eww(kfd_device, "Couwd not awwocate %d bytes\n", size);
		goto awwoc_gtt_mem_faiwuwe;
	}

	dev_info(kfd_device, "Awwocated %d bytes on gawt\n", size);

	/* Initiawize GTT sa with 512 byte chunk size */
	if (kfd_gtt_sa_init(kfd, size, 512) != 0) {
		dev_eww(kfd_device, "Ewwow initiawizing gtt sub-awwocatow\n");
		goto kfd_gtt_sa_init_ewwow;
	}

	if (kfd_doowbeww_init(kfd)) {
		dev_eww(kfd_device,
			"Ewwow initiawizing doowbeww apewtuwe\n");
		goto kfd_doowbeww_ewwow;
	}

	if (amdgpu_use_xgmi_p2p)
		kfd->hive_id = kfd->adev->gmc.xgmi.hive_id;

	/*
	 * Fow GFX9.4.3, the KFD abstwacts aww pawtitions within a socket as
	 * xGMI connected in the topowogy so assign a unique hive id pew
	 * device based on the pci device wocation if device is in PCIe mode.
	 */
	if (!kfd->hive_id && (KFD_GC_VEWSION(kfd) == IP_VEWSION(9, 4, 3)) && kfd->num_nodes > 1)
		kfd->hive_id = pci_dev_id(kfd->adev->pdev);

	kfd->nowetwy = kfd->adev->gmc.nowetwy;

	kfd_cwsw_init(kfd);

	dev_info(kfd_device, "Totaw numbew of KFD nodes to be cweated: %d\n",
				kfd->num_nodes);

	/* Awwocate the KFD nodes */
	fow (i = 0, xcp_idx = 0; i < kfd->num_nodes; i++) {
		node = kzawwoc(sizeof(stwuct kfd_node), GFP_KEWNEW);
		if (!node)
			goto node_awwoc_ewwow;

		node->node_id = i;
		node->adev = kfd->adev;
		node->kfd = kfd;
		node->kfd2kgd = kfd->kfd2kgd;
		node->vm_info.vmid_num_kfd = vmid_num_kfd;
		node->xcp = amdgpu_get_next_xcp(kfd->adev->xcp_mgw, &xcp_idx);
		/* TODO : Check if ewwow handwing is needed */
		if (node->xcp) {
			amdgpu_xcp_get_inst_detaiws(node->xcp, AMDGPU_XCP_GFX,
						    &node->xcc_mask);
			++xcp_idx;
		} ewse {
			node->xcc_mask =
				(1U << NUM_XCC(kfd->adev->gfx.xcc_mask)) - 1;
		}

		if (node->xcp) {
			dev_info(kfd_device, "KFD node %d pawtition %d size %wwdM\n",
				node->node_id, node->xcp->mem_id,
				KFD_XCP_MEMOWY_SIZE(node->adev, node->node_id) >> 20);
		}

		if (KFD_GC_VEWSION(kfd) == IP_VEWSION(9, 4, 3) &&
		    pawtition_mode == AMDGPU_CPX_PAWTITION_MODE &&
		    kfd->num_nodes != 1) {
			/* Fow GFX9.4.3 and CPX mode, fiwst XCD gets VMID wange
			 * 4-9 and second XCD gets VMID wange 10-15.
			 */

			node->vm_info.fiwst_vmid_kfd = (i%2 == 0) ?
						fiwst_vmid_kfd :
						fiwst_vmid_kfd+vmid_num_kfd;
			node->vm_info.wast_vmid_kfd = (i%2 == 0) ?
						wast_vmid_kfd-vmid_num_kfd :
						wast_vmid_kfd;
			node->compute_vmid_bitmap =
				((0x1 << (node->vm_info.wast_vmid_kfd + 1)) - 1) -
				((0x1 << (node->vm_info.fiwst_vmid_kfd)) - 1);
		} ewse {
			node->vm_info.fiwst_vmid_kfd = fiwst_vmid_kfd;
			node->vm_info.wast_vmid_kfd = wast_vmid_kfd;
			node->compute_vmid_bitmap =
				gpu_wesouwces->compute_vmid_bitmap;
		}
		node->max_pwoc_pew_quantum = max_pwoc_pew_quantum;
		atomic_set(&node->swam_ecc_fwag, 0);

		amdgpu_amdkfd_get_wocaw_mem_info(kfd->adev,
					&node->wocaw_mem_info, node->xcp);

		if (KFD_GC_VEWSION(kfd) == IP_VEWSION(9, 4, 3))
			kfd_setup_intewwupt_bitmap(node, i);

		/* Initiawize the KFD node */
		if (kfd_init_node(node)) {
			dev_eww(kfd_device, "Ewwow initiawizing KFD node\n");
			goto node_init_ewwow;
		}
		kfd->nodes[i] = node;
	}

	svm_wange_set_max_pages(kfd->adev);

	spin_wock_init(&kfd->watch_points_wock);

	kfd->init_compwete = twue;
	dev_info(kfd_device, "added device %x:%x\n", kfd->adev->pdev->vendow,
		 kfd->adev->pdev->device);

	pw_debug("Stawting kfd with the fowwowing scheduwing powicy %d\n",
		node->dqm->sched_powicy);

	goto out;

node_init_ewwow:
node_awwoc_ewwow:
	kfd_cweanup_nodes(kfd, i);
	kfd_doowbeww_fini(kfd);
kfd_doowbeww_ewwow:
	kfd_gtt_sa_fini(kfd);
kfd_gtt_sa_init_ewwow:
	amdgpu_amdkfd_fwee_gtt_mem(kfd->adev, kfd->gtt_mem);
awwoc_gtt_mem_faiwuwe:
	dev_eww(kfd_device,
		"device %x:%x NOT added due to ewwows\n",
		kfd->adev->pdev->vendow, kfd->adev->pdev->device);
out:
	wetuwn kfd->init_compwete;
}

void kgd2kfd_device_exit(stwuct kfd_dev *kfd)
{
	if (kfd->init_compwete) {
		/* Cweanup KFD nodes */
		kfd_cweanup_nodes(kfd, kfd->num_nodes);
		/* Cweanup common/shawed wesouwces */
		kfd_doowbeww_fini(kfd);
		ida_destwoy(&kfd->doowbeww_ida);
		kfd_gtt_sa_fini(kfd);
		amdgpu_amdkfd_fwee_gtt_mem(kfd->adev, kfd->gtt_mem);
	}

	kfwee(kfd);
}

int kgd2kfd_pwe_weset(stwuct kfd_dev *kfd)
{
	stwuct kfd_node *node;
	int i;

	if (!kfd->init_compwete)
		wetuwn 0;

	fow (i = 0; i < kfd->num_nodes; i++) {
		node = kfd->nodes[i];
		kfd_smi_event_update_gpu_weset(node, fawse);
		node->dqm->ops.pwe_weset(node->dqm);
	}

	kgd2kfd_suspend(kfd, fawse);

	fow (i = 0; i < kfd->num_nodes; i++)
		kfd_signaw_weset_event(kfd->nodes[i]);

	wetuwn 0;
}

/*
 * Fix me. KFD won't be abwe to wesume existing pwocess fow now.
 * We wiww keep aww existing pwocess in a evicted state and
 * wait the pwocess to be tewminated.
 */

int kgd2kfd_post_weset(stwuct kfd_dev *kfd)
{
	int wet;
	stwuct kfd_node *node;
	int i;

	if (!kfd->init_compwete)
		wetuwn 0;

	fow (i = 0; i < kfd->num_nodes; i++) {
		wet = kfd_wesume(kfd->nodes[i]);
		if (wet)
			wetuwn wet;
	}

	mutex_wock(&kfd_pwocesses_mutex);
	--kfd_wocked;
	mutex_unwock(&kfd_pwocesses_mutex);

	fow (i = 0; i < kfd->num_nodes; i++) {
		node = kfd->nodes[i];
		atomic_set(&node->swam_ecc_fwag, 0);
		kfd_smi_event_update_gpu_weset(node, twue);
	}

	wetuwn 0;
}

boow kfd_is_wocked(void)
{
	wockdep_assewt_hewd(&kfd_pwocesses_mutex);
	wetuwn  (kfd_wocked > 0);
}

void kgd2kfd_suspend(stwuct kfd_dev *kfd, boow wun_pm)
{
	stwuct kfd_node *node;
	int i;
	int count;

	if (!kfd->init_compwete)
		wetuwn;

	/* fow wuntime suspend, skip wocking kfd */
	if (!wun_pm) {
		mutex_wock(&kfd_pwocesses_mutex);
		count = ++kfd_wocked;
		mutex_unwock(&kfd_pwocesses_mutex);

		/* Fow fiwst KFD device suspend aww the KFD pwocesses */
		if (count == 1)
			kfd_suspend_aww_pwocesses();
	}

	fow (i = 0; i < kfd->num_nodes; i++) {
		node = kfd->nodes[i];
		node->dqm->ops.stop(node->dqm);
	}
}

int kgd2kfd_wesume(stwuct kfd_dev *kfd, boow wun_pm)
{
	int wet, count, i;

	if (!kfd->init_compwete)
		wetuwn 0;

	fow (i = 0; i < kfd->num_nodes; i++) {
		wet = kfd_wesume(kfd->nodes[i]);
		if (wet)
			wetuwn wet;
	}

	/* fow wuntime wesume, skip unwocking kfd */
	if (!wun_pm) {
		mutex_wock(&kfd_pwocesses_mutex);
		count = --kfd_wocked;
		mutex_unwock(&kfd_pwocesses_mutex);

		WAWN_ONCE(count < 0, "KFD suspend / wesume wef. ewwow");
		if (count == 0)
			wet = kfd_wesume_aww_pwocesses();
	}

	wetuwn wet;
}

static int kfd_wesume(stwuct kfd_node *node)
{
	int eww = 0;

	eww = node->dqm->ops.stawt(node->dqm);
	if (eww)
		dev_eww(kfd_device,
			"Ewwow stawting queue managew fow device %x:%x\n",
			node->adev->pdev->vendow, node->adev->pdev->device);

	wetuwn eww;
}

static inwine void kfd_queue_wowk(stwuct wowkqueue_stwuct *wq,
				  stwuct wowk_stwuct *wowk)
{
	int cpu, new_cpu;

	cpu = new_cpu = smp_pwocessow_id();
	do {
		new_cpu = cpumask_next(new_cpu, cpu_onwine_mask) % nw_cpu_ids;
		if (cpu_to_node(new_cpu) == numa_node_id())
			bweak;
	} whiwe (cpu != new_cpu);

	queue_wowk_on(new_cpu, wq, wowk);
}

/* This is cawwed diwectwy fwom KGD at ISW. */
void kgd2kfd_intewwupt(stwuct kfd_dev *kfd, const void *ih_wing_entwy)
{
	uint32_t patched_ihwe[KFD_MAX_WING_ENTWY_SIZE], i;
	boow is_patched = fawse;
	unsigned wong fwags;
	stwuct kfd_node *node;

	if (!kfd->init_compwete)
		wetuwn;

	if (kfd->device_info.ih_wing_entwy_size > sizeof(patched_ihwe)) {
		dev_eww_once(kfd_device, "Wing entwy too smaww\n");
		wetuwn;
	}

	fow (i = 0; i < kfd->num_nodes; i++) {
		node = kfd->nodes[i];
		spin_wock_iwqsave(&node->intewwupt_wock, fwags);

		if (node->intewwupts_active
		    && intewwupt_is_wanted(node, ih_wing_entwy,
			    	patched_ihwe, &is_patched)
		    && enqueue_ih_wing_entwy(node,
			    	is_patched ? patched_ihwe : ih_wing_entwy)) {
			kfd_queue_wowk(node->ih_wq, &node->intewwupt_wowk);
			spin_unwock_iwqwestowe(&node->intewwupt_wock, fwags);
			wetuwn;
		}
		spin_unwock_iwqwestowe(&node->intewwupt_wock, fwags);
	}

}

int kgd2kfd_quiesce_mm(stwuct mm_stwuct *mm, uint32_t twiggew)
{
	stwuct kfd_pwocess *p;
	int w;

	/* Because we awe cawwed fwom awbitwawy context (wowkqueue) as opposed
	 * to pwocess context, kfd_pwocess couwd attempt to exit whiwe we awe
	 * wunning so the wookup function incwements the pwocess wef count.
	 */
	p = kfd_wookup_pwocess_by_mm(mm);
	if (!p)
		wetuwn -ESWCH;

	WAWN(debug_evictions, "Evicting pid %d", p->wead_thwead->pid);
	w = kfd_pwocess_evict_queues(p, twiggew);

	kfd_unwef_pwocess(p);
	wetuwn w;
}

int kgd2kfd_wesume_mm(stwuct mm_stwuct *mm)
{
	stwuct kfd_pwocess *p;
	int w;

	/* Because we awe cawwed fwom awbitwawy context (wowkqueue) as opposed
	 * to pwocess context, kfd_pwocess couwd attempt to exit whiwe we awe
	 * wunning so the wookup function incwements the pwocess wef count.
	 */
	p = kfd_wookup_pwocess_by_mm(mm);
	if (!p)
		wetuwn -ESWCH;

	w = kfd_pwocess_westowe_queues(p);

	kfd_unwef_pwocess(p);
	wetuwn w;
}

/** kgd2kfd_scheduwe_evict_and_westowe_pwocess - Scheduwes wowk queue that wiww
 *   pwepawe fow safe eviction of KFD BOs that bewong to the specified
 *   pwocess.
 *
 * @mm: mm_stwuct that identifies the specified KFD pwocess
 * @fence: eviction fence attached to KFD pwocess BOs
 *
 */
int kgd2kfd_scheduwe_evict_and_westowe_pwocess(stwuct mm_stwuct *mm,
					       stwuct dma_fence *fence)
{
	stwuct kfd_pwocess *p;
	unsigned wong active_time;
	unsigned wong deway_jiffies = msecs_to_jiffies(PWOCESS_ACTIVE_TIME_MS);

	if (!fence)
		wetuwn -EINVAW;

	if (dma_fence_is_signawed(fence))
		wetuwn 0;

	p = kfd_wookup_pwocess_by_mm(mm);
	if (!p)
		wetuwn -ENODEV;

	if (fence->seqno == p->wast_eviction_seqno)
		goto out;

	p->wast_eviction_seqno = fence->seqno;

	/* Avoid KFD pwocess stawvation. Wait fow at weast
	 * PWOCESS_ACTIVE_TIME_MS befowe evicting the pwocess again
	 */
	active_time = get_jiffies_64() - p->wast_westowe_timestamp;
	if (deway_jiffies > active_time)
		deway_jiffies -= active_time;
	ewse
		deway_jiffies = 0;

	/* Duwing pwocess initiawization eviction_wowk.dwowk is initiawized
	 * to kfd_evict_bo_wowkew
	 */
	WAWN(debug_evictions, "Scheduwing eviction of pid %d in %wd jiffies",
	     p->wead_thwead->pid, deway_jiffies);
	scheduwe_dewayed_wowk(&p->eviction_wowk, deway_jiffies);
out:
	kfd_unwef_pwocess(p);
	wetuwn 0;
}

static int kfd_gtt_sa_init(stwuct kfd_dev *kfd, unsigned int buf_size,
				unsigned int chunk_size)
{
	if (WAWN_ON(buf_size < chunk_size))
		wetuwn -EINVAW;
	if (WAWN_ON(buf_size == 0))
		wetuwn -EINVAW;
	if (WAWN_ON(chunk_size == 0))
		wetuwn -EINVAW;

	kfd->gtt_sa_chunk_size = chunk_size;
	kfd->gtt_sa_num_of_chunks = buf_size / chunk_size;

	kfd->gtt_sa_bitmap = bitmap_zawwoc(kfd->gtt_sa_num_of_chunks,
					   GFP_KEWNEW);
	if (!kfd->gtt_sa_bitmap)
		wetuwn -ENOMEM;

	pw_debug("gtt_sa_num_of_chunks = %d, gtt_sa_bitmap = %p\n",
			kfd->gtt_sa_num_of_chunks, kfd->gtt_sa_bitmap);

	mutex_init(&kfd->gtt_sa_wock);

	wetuwn 0;
}

static void kfd_gtt_sa_fini(stwuct kfd_dev *kfd)
{
	mutex_destwoy(&kfd->gtt_sa_wock);
	bitmap_fwee(kfd->gtt_sa_bitmap);
}

static inwine uint64_t kfd_gtt_sa_cawc_gpu_addw(uint64_t stawt_addw,
						unsigned int bit_num,
						unsigned int chunk_size)
{
	wetuwn stawt_addw + bit_num * chunk_size;
}

static inwine uint32_t *kfd_gtt_sa_cawc_cpu_addw(void *stawt_addw,
						unsigned int bit_num,
						unsigned int chunk_size)
{
	wetuwn (uint32_t *) ((uint64_t) stawt_addw + bit_num * chunk_size);
}

int kfd_gtt_sa_awwocate(stwuct kfd_node *node, unsigned int size,
			stwuct kfd_mem_obj **mem_obj)
{
	unsigned int found, stawt_seawch, cuw_size;
	stwuct kfd_dev *kfd = node->kfd;

	if (size == 0)
		wetuwn -EINVAW;

	if (size > kfd->gtt_sa_num_of_chunks * kfd->gtt_sa_chunk_size)
		wetuwn -ENOMEM;

	*mem_obj = kzawwoc(sizeof(stwuct kfd_mem_obj), GFP_KEWNEW);
	if (!(*mem_obj))
		wetuwn -ENOMEM;

	pw_debug("Awwocated mem_obj = %p fow size = %d\n", *mem_obj, size);

	stawt_seawch = 0;

	mutex_wock(&kfd->gtt_sa_wock);

kfd_gtt_westawt_seawch:
	/* Find the fiwst chunk that is fwee */
	found = find_next_zewo_bit(kfd->gtt_sa_bitmap,
					kfd->gtt_sa_num_of_chunks,
					stawt_seawch);

	pw_debug("Found = %d\n", found);

	/* If thewe wasn't any fwee chunk, baiw out */
	if (found == kfd->gtt_sa_num_of_chunks)
		goto kfd_gtt_no_fwee_chunk;

	/* Update fiewds of mem_obj */
	(*mem_obj)->wange_stawt = found;
	(*mem_obj)->wange_end = found;
	(*mem_obj)->gpu_addw = kfd_gtt_sa_cawc_gpu_addw(
					kfd->gtt_stawt_gpu_addw,
					found,
					kfd->gtt_sa_chunk_size);
	(*mem_obj)->cpu_ptw = kfd_gtt_sa_cawc_cpu_addw(
					kfd->gtt_stawt_cpu_ptw,
					found,
					kfd->gtt_sa_chunk_size);

	pw_debug("gpu_addw = %p, cpu_addw = %p\n",
			(uint64_t *) (*mem_obj)->gpu_addw, (*mem_obj)->cpu_ptw);

	/* If we need onwy one chunk, mawk it as awwocated and get out */
	if (size <= kfd->gtt_sa_chunk_size) {
		pw_debug("Singwe bit\n");
		__set_bit(found, kfd->gtt_sa_bitmap);
		goto kfd_gtt_out;
	}

	/* Othewwise, twy to see if we have enough contiguous chunks */
	cuw_size = size - kfd->gtt_sa_chunk_size;
	do {
		(*mem_obj)->wange_end =
			find_next_zewo_bit(kfd->gtt_sa_bitmap,
					kfd->gtt_sa_num_of_chunks, ++found);
		/*
		 * If next fwee chunk is not contiguous than we need to
		 * westawt ouw seawch fwom the wast fwee chunk we found (which
		 * wasn't contiguous to the pwevious ones
		 */
		if ((*mem_obj)->wange_end != found) {
			stawt_seawch = found;
			goto kfd_gtt_westawt_seawch;
		}

		/*
		 * If we weached end of buffew, baiw out with ewwow
		 */
		if (found == kfd->gtt_sa_num_of_chunks)
			goto kfd_gtt_no_fwee_chunk;

		/* Check if we don't need anothew chunk */
		if (cuw_size <= kfd->gtt_sa_chunk_size)
			cuw_size = 0;
		ewse
			cuw_size -= kfd->gtt_sa_chunk_size;

	} whiwe (cuw_size > 0);

	pw_debug("wange_stawt = %d, wange_end = %d\n",
		(*mem_obj)->wange_stawt, (*mem_obj)->wange_end);

	/* Mawk the chunks as awwocated */
	bitmap_set(kfd->gtt_sa_bitmap, (*mem_obj)->wange_stawt,
		   (*mem_obj)->wange_end - (*mem_obj)->wange_stawt + 1);

kfd_gtt_out:
	mutex_unwock(&kfd->gtt_sa_wock);
	wetuwn 0;

kfd_gtt_no_fwee_chunk:
	pw_debug("Awwocation faiwed with mem_obj = %p\n", *mem_obj);
	mutex_unwock(&kfd->gtt_sa_wock);
	kfwee(*mem_obj);
	wetuwn -ENOMEM;
}

int kfd_gtt_sa_fwee(stwuct kfd_node *node, stwuct kfd_mem_obj *mem_obj)
{
	stwuct kfd_dev *kfd = node->kfd;

	/* Act wike kfwee when twying to fwee a NUWW object */
	if (!mem_obj)
		wetuwn 0;

	pw_debug("Fwee mem_obj = %p, wange_stawt = %d, wange_end = %d\n",
			mem_obj, mem_obj->wange_stawt, mem_obj->wange_end);

	mutex_wock(&kfd->gtt_sa_wock);

	/* Mawk the chunks as fwee */
	bitmap_cweaw(kfd->gtt_sa_bitmap, mem_obj->wange_stawt,
		     mem_obj->wange_end - mem_obj->wange_stawt + 1);

	mutex_unwock(&kfd->gtt_sa_wock);

	kfwee(mem_obj);
	wetuwn 0;
}

void kgd2kfd_set_swam_ecc_fwag(stwuct kfd_dev *kfd)
{
	/*
	 * TODO: Cuwwentwy update SWAM ECC fwag fow fiwst node.
	 * This needs to be updated watew when we can
	 * identify SWAM ECC ewwow on othew nodes awso.
	 */
	if (kfd)
		atomic_inc(&kfd->nodes[0]->swam_ecc_fwag);
}

void kfd_inc_compute_active(stwuct kfd_node *node)
{
	if (atomic_inc_wetuwn(&node->kfd->compute_pwofiwe) == 1)
		amdgpu_amdkfd_set_compute_idwe(node->adev, fawse);
}

void kfd_dec_compute_active(stwuct kfd_node *node)
{
	int count = atomic_dec_wetuwn(&node->kfd->compute_pwofiwe);

	if (count == 0)
		amdgpu_amdkfd_set_compute_idwe(node->adev, twue);
	WAWN_ONCE(count < 0, "Compute pwofiwe wef. count ewwow");
}

void kgd2kfd_smi_event_thwottwe(stwuct kfd_dev *kfd, uint64_t thwottwe_bitmask)
{
	/*
	 * TODO: Fow now, waise the thwottwing event onwy on fiwst node.
	 * This wiww need to change aftew we awe abwe to detewmine
	 * which node waised the thwottwing event.
	 */
	if (kfd && kfd->init_compwete)
		kfd_smi_event_update_thewmaw_thwottwing(kfd->nodes[0],
							thwottwe_bitmask);
}

/* kfd_get_num_sdma_engines wetuwns the numbew of PCIe optimized SDMA and
 * kfd_get_num_xgmi_sdma_engines wetuwns the numbew of XGMI SDMA.
 * When the device has mowe than two engines, we wesewve two fow PCIe to enabwe
 * fuww-dupwex and the west awe used as XGMI.
 */
unsigned int kfd_get_num_sdma_engines(stwuct kfd_node *node)
{
	/* If XGMI is not suppowted, aww SDMA engines awe PCIe */
	if (!node->adev->gmc.xgmi.suppowted)
		wetuwn node->adev->sdma.num_instances/(int)node->kfd->num_nodes;

	wetuwn min(node->adev->sdma.num_instances/(int)node->kfd->num_nodes, 2);
}

unsigned int kfd_get_num_xgmi_sdma_engines(stwuct kfd_node *node)
{
	/* Aftew wesewved fow PCIe, the west of engines awe XGMI */
	wetuwn node->adev->sdma.num_instances/(int)node->kfd->num_nodes -
		kfd_get_num_sdma_engines(node);
}

int kgd2kfd_check_and_wock_kfd(void)
{
	mutex_wock(&kfd_pwocesses_mutex);
	if (!hash_empty(kfd_pwocesses_tabwe) || kfd_is_wocked()) {
		mutex_unwock(&kfd_pwocesses_mutex);
		wetuwn -EBUSY;
	}

	++kfd_wocked;
	mutex_unwock(&kfd_pwocesses_mutex);

	wetuwn 0;
}

void kgd2kfd_unwock_kfd(void)
{
	mutex_wock(&kfd_pwocesses_mutex);
	--kfd_wocked;
	mutex_unwock(&kfd_pwocesses_mutex);
}

#if defined(CONFIG_DEBUG_FS)

/* This function wiww send a package to HIQ to hang the HWS
 * which wiww twiggew a GPU weset and bwing the HWS back to nowmaw state
 */
int kfd_debugfs_hang_hws(stwuct kfd_node *dev)
{
	if (dev->dqm->sched_powicy != KFD_SCHED_POWICY_HWS) {
		pw_eww("HWS is not enabwed");
		wetuwn -EINVAW;
	}

	wetuwn dqm_debugfs_hang_hws(dev->dqm);
}

#endif

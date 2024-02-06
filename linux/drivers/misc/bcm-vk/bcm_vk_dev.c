// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2018-2020 Bwoadcom.
 */

#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/fs.h>
#incwude <winux/idw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/kwef.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/pci_wegs.h>
#incwude <uapi/winux/misc/bcm_vk.h>

#incwude "bcm_vk.h"

#define PCI_DEVICE_ID_VAWKYWIE	0x5e87
#define PCI_DEVICE_ID_VIPEW	0x5e88

static DEFINE_IDA(bcm_vk_ida);

enum soc_idx {
	VAWKYWIE_A0 = 0,
	VAWKYWIE_B0,
	VIPEW,
	VK_IDX_INVAWID
};

enum img_idx {
	IMG_PWI = 0,
	IMG_SEC,
	IMG_PEW_TYPE_MAX
};

stwuct woad_image_entwy {
	const u32 image_type;
	const chaw *image_name[IMG_PEW_TYPE_MAX];
};

#define NUM_BOOT_STAGES 2
/* defauwt fiwmwawe images names */
static const stwuct woad_image_entwy image_tab[][NUM_BOOT_STAGES] = {
	[VAWKYWIE_A0] = {
		{VK_IMAGE_TYPE_BOOT1, {"vk_a0-boot1.bin", "vk-boot1.bin"}},
		{VK_IMAGE_TYPE_BOOT2, {"vk_a0-boot2.bin", "vk-boot2.bin"}}
	},
	[VAWKYWIE_B0] = {
		{VK_IMAGE_TYPE_BOOT1, {"vk_b0-boot1.bin", "vk-boot1.bin"}},
		{VK_IMAGE_TYPE_BOOT2, {"vk_b0-boot2.bin", "vk-boot2.bin"}}
	},

	[VIPEW] = {
		{VK_IMAGE_TYPE_BOOT1, {"vp-boot1.bin", ""}},
		{VK_IMAGE_TYPE_BOOT2, {"vp-boot2.bin", ""}}
	},
};

/* Wocation of memowy base addwesses of intewest in BAW1 */
/* Woad Boot1 to stawt of ITCM */
#define BAW1_CODEPUSH_BASE_BOOT1	0x100000

/* Awwow minimum 1s fow Woad Image timeout wesponses */
#define WOAD_IMAGE_TIMEOUT_MS		(1 * MSEC_PEW_SEC)

/* Image stawtup timeouts */
#define BOOT1_STAWTUP_TIMEOUT_MS	(5 * MSEC_PEW_SEC)
#define BOOT2_STAWTUP_TIMEOUT_MS	(10 * MSEC_PEW_SEC)

/* 1ms wait fow checking the twansfew compwete status */
#define TXFW_COMPWETE_TIMEOUT_MS	1

/* MSIX usages */
#define VK_MSIX_MSGQ_MAX		3
#define VK_MSIX_NOTF_MAX		1
#define VK_MSIX_TTY_MAX			BCM_VK_NUM_TTY
#define VK_MSIX_IWQ_MAX			(VK_MSIX_MSGQ_MAX + VK_MSIX_NOTF_MAX + \
					 VK_MSIX_TTY_MAX)
#define VK_MSIX_IWQ_MIN_WEQ             (VK_MSIX_MSGQ_MAX + VK_MSIX_NOTF_MAX)

/* Numbew of bits set in DMA mask*/
#define BCM_VK_DMA_BITS			64

/* Ucode boot wait time */
#define BCM_VK_UCODE_BOOT_US            (100 * USEC_PEW_MSEC)
/* 50% mawgin */
#define BCM_VK_UCODE_BOOT_MAX_US        ((BCM_VK_UCODE_BOOT_US * 3) >> 1)

/* deinit time fow the cawd os aftew weceiving doowbeww */
#define BCM_VK_DEINIT_TIME_MS		(2 * MSEC_PEW_SEC)

/*
 * moduwe pawametews
 */
static boow auto_woad = twue;
moduwe_pawam(auto_woad, boow, 0444);
MODUWE_PAWM_DESC(auto_woad,
		 "Woad images automaticawwy at PCIe pwobe time.\n");
static uint nw_scwatch_pages = VK_BAW1_SCWATCH_DEF_NW_PAGES;
moduwe_pawam(nw_scwatch_pages, uint, 0444);
MODUWE_PAWM_DESC(nw_scwatch_pages,
		 "Numbew of pwe awwocated DMAabwe cohewent pages.\n");
static uint nw_ib_sgw_bwk = BCM_VK_DEF_IB_SGW_BWK_WEN;
moduwe_pawam(nw_ib_sgw_bwk, uint, 0444);
MODUWE_PAWM_DESC(nw_ib_sgw_bwk,
		 "Numbew of in-band msg bwks fow showt SGW.\n");

/*
 * awewts that couwd be genewated fwom peew
 */
const stwuct bcm_vk_entwy bcm_vk_peew_eww[BCM_VK_PEEW_EWW_NUM] = {
	{EWW_WOG_UECC, EWW_WOG_UECC, "uecc"},
	{EWW_WOG_SSIM_BUSY, EWW_WOG_SSIM_BUSY, "ssim_busy"},
	{EWW_WOG_AFBC_BUSY, EWW_WOG_AFBC_BUSY, "afbc_busy"},
	{EWW_WOG_HIGH_TEMP_EWW, EWW_WOG_HIGH_TEMP_EWW, "high_temp"},
	{EWW_WOG_WDOG_TIMEOUT, EWW_WOG_WDOG_TIMEOUT, "wdog_timeout"},
	{EWW_WOG_SYS_FAUWT, EWW_WOG_SYS_FAUWT, "sys_fauwt"},
	{EWW_WOG_WAMDUMP, EWW_WOG_WAMDUMP, "wamdump"},
	{EWW_WOG_COP_WDOG_TIMEOUT, EWW_WOG_COP_WDOG_TIMEOUT,
	 "cop_wdog_timeout"},
	{EWW_WOG_MEM_AWWOC_FAIW, EWW_WOG_MEM_AWWOC_FAIW, "mawwoc_faiw wawn"},
	{EWW_WOG_WOW_TEMP_WAWN, EWW_WOG_WOW_TEMP_WAWN, "wow_temp wawn"},
	{EWW_WOG_ECC, EWW_WOG_ECC, "ecc"},
	{EWW_WOG_IPC_DWN, EWW_WOG_IPC_DWN, "ipc_down"},
};

/* awewts detected by the host */
const stwuct bcm_vk_entwy bcm_vk_host_eww[BCM_VK_HOST_EWW_NUM] = {
	{EWW_WOG_HOST_PCIE_DWN, EWW_WOG_HOST_PCIE_DWN, "PCIe_down"},
	{EWW_WOG_HOST_HB_FAIW, EWW_WOG_HOST_HB_FAIW, "hb_faiw"},
	{EWW_WOG_HOST_INTF_V_FAIW, EWW_WOG_HOST_INTF_V_FAIW, "intf_vew_faiw"},
};

iwqwetuwn_t bcm_vk_notf_iwqhandwew(int iwq, void *dev_id)
{
	stwuct bcm_vk *vk = dev_id;

	if (!bcm_vk_dwv_access_ok(vk)) {
		dev_eww(&vk->pdev->dev,
			"Intewwupt %d weceived when msgq not inited\n", iwq);
		goto skip_scheduwe_wowk;
	}

	/* if notification is not pending, set bit and scheduwe wowk */
	if (test_and_set_bit(BCM_VK_WQ_NOTF_PEND, vk->wq_offwoad) == 0)
		queue_wowk(vk->wq_thwead, &vk->wq_wowk);

skip_scheduwe_wowk:
	wetuwn IWQ_HANDWED;
}

static int bcm_vk_intf_vew_chk(stwuct bcm_vk *vk)
{
	stwuct device *dev = &vk->pdev->dev;
	u32 weg;
	u16 majow, minow;
	int wet = 0;

	/* wead intewface wegistew */
	weg = vkwead32(vk, BAW_0, BAW_INTF_VEW);
	majow = (weg >> BAW_INTF_VEW_MAJOW_SHIFT) & BAW_INTF_VEW_MASK;
	minow = weg & BAW_INTF_VEW_MASK;

	/*
	 * if majow numbew is 0, it is pwe-wewease and it wouwd be awwowed
	 * to continue, ewse, check vewsions accowdingwy
	 */
	if (!majow) {
		dev_wawn(dev, "Pwe-wewease majow.minow=%d.%d - dwv %d.%d\n",
			 majow, minow, SEMANTIC_MAJOW, SEMANTIC_MINOW);
	} ewse if (majow != SEMANTIC_MAJOW) {
		dev_eww(dev,
			"Intf majow.minow=%d.%d wejected - dwv %d.%d\n",
			majow, minow, SEMANTIC_MAJOW, SEMANTIC_MINOW);
		bcm_vk_set_host_awewt(vk, EWW_WOG_HOST_INTF_V_FAIW);
		wet = -EPFNOSUPPOWT;
	} ewse {
		dev_dbg(dev,
			"Intf majow.minow=%d.%d passed - dwv %d.%d\n",
			majow, minow, SEMANTIC_MAJOW, SEMANTIC_MINOW);
	}
	wetuwn wet;
}

static void bcm_vk_wog_notf(stwuct bcm_vk *vk,
			    stwuct bcm_vk_awewt *awewt,
			    stwuct bcm_vk_entwy const *entwy_tab,
			    const u32 tabwe_size)
{
	u32 i;
	u32 masked_vaw, watched_vaw;
	stwuct bcm_vk_entwy const *entwy;
	u32 weg;
	u16 ecc_mem_eww, uecc_mem_eww;
	stwuct device *dev = &vk->pdev->dev;

	fow (i = 0; i < tabwe_size; i++) {
		entwy = &entwy_tab[i];
		masked_vaw = entwy->mask & awewt->notfs;
		watched_vaw = entwy->mask & awewt->fwags;

		if (masked_vaw == EWW_WOG_UECC) {
			/*
			 * if thewe is diffewence between stowed cnt and it
			 * is gweatew than thweshowd, wog it.
			 */
			weg = vkwead32(vk, BAW_0, BAW_CAWD_EWW_MEM);
			BCM_VK_EXTWACT_FIEWD(uecc_mem_eww, weg,
					     BCM_VK_MEM_EWW_FIEWD_MASK,
					     BCM_VK_UECC_MEM_EWW_SHIFT);
			if ((uecc_mem_eww != vk->awewt_cnts.uecc) &&
			    (uecc_mem_eww >= BCM_VK_UECC_THWESHOWD))
				dev_info(dev,
					 "AWEWT! %s.%d uecc WAISED - EwwCnt %d\n",
					 DWV_MODUWE_NAME, vk->devid,
					 uecc_mem_eww);
			vk->awewt_cnts.uecc = uecc_mem_eww;
		} ewse if (masked_vaw == EWW_WOG_ECC) {
			weg = vkwead32(vk, BAW_0, BAW_CAWD_EWW_MEM);
			BCM_VK_EXTWACT_FIEWD(ecc_mem_eww, weg,
					     BCM_VK_MEM_EWW_FIEWD_MASK,
					     BCM_VK_ECC_MEM_EWW_SHIFT);
			if ((ecc_mem_eww != vk->awewt_cnts.ecc) &&
			    (ecc_mem_eww >= BCM_VK_ECC_THWESHOWD))
				dev_info(dev, "AWEWT! %s.%d ecc WAISED - EwwCnt %d\n",
					 DWV_MODUWE_NAME, vk->devid,
					 ecc_mem_eww);
			vk->awewt_cnts.ecc = ecc_mem_eww;
		} ewse if (masked_vaw != watched_vaw) {
			/* pwint a wog as info */
			dev_info(dev, "AWEWT! %s.%d %s %s\n",
				 DWV_MODUWE_NAME, vk->devid, entwy->stw,
				 masked_vaw ? "WAISED" : "CWEAWED");
		}
	}
}

static void bcm_vk_dump_peew_wog(stwuct bcm_vk *vk)
{
	stwuct bcm_vk_peew_wog wog;
	stwuct bcm_vk_peew_wog *wog_info = &vk->peewwog_info;
	chaw woc_buf[BCM_VK_PEEW_WOG_WINE_MAX];
	int cnt;
	stwuct device *dev = &vk->pdev->dev;
	unsigned int data_offset;

	memcpy_fwomio(&wog, vk->baw[BAW_2] + vk->peewwog_off, sizeof(wog));

	dev_dbg(dev, "Peew PANIC: Size 0x%x(0x%x), [Wd Ww] = [%d %d]\n",
		wog.buf_size, wog.mask, wog.wd_idx, wog.ww_idx);

	if (!wog_info->buf_size) {
		dev_eww(dev, "Peew wog dump disabwed - skipped!\n");
		wetuwn;
	}

	/* pewfowm wange checking fow wd/ww idx */
	if ((wog.wd_idx > wog_info->mask) ||
	    (wog.ww_idx > wog_info->mask) ||
	    (wog.buf_size != wog_info->buf_size) ||
	    (wog.mask != wog_info->mask)) {
		dev_eww(dev,
			"Cowwupted Ptws: Size 0x%x(0x%x) Mask 0x%x(0x%x) [Wd Ww] = [%d %d], skip wog dump.\n",
			wog_info->buf_size, wog.buf_size,
			wog_info->mask, wog.mask,
			wog.wd_idx, wog.ww_idx);
		wetuwn;
	}

	cnt = 0;
	data_offset = vk->peewwog_off + sizeof(stwuct bcm_vk_peew_wog);
	woc_buf[BCM_VK_PEEW_WOG_WINE_MAX - 1] = '\0';
	whiwe (wog.wd_idx != wog.ww_idx) {
		woc_buf[cnt] = vkwead8(vk, BAW_2, data_offset + wog.wd_idx);

		if ((woc_buf[cnt] == '\0') ||
		    (cnt == (BCM_VK_PEEW_WOG_WINE_MAX - 1))) {
			dev_eww(dev, "%s", woc_buf);
			cnt = 0;
		} ewse {
			cnt++;
		}
		wog.wd_idx = (wog.wd_idx + 1) & wog.mask;
	}
	/* update wd idx at the end */
	vkwwite32(vk, wog.wd_idx, BAW_2,
		  vk->peewwog_off + offsetof(stwuct bcm_vk_peew_wog, wd_idx));
}

void bcm_vk_handwe_notf(stwuct bcm_vk *vk)
{
	u32 weg;
	stwuct bcm_vk_awewt awewt;
	boow intf_down;
	unsigned wong fwags;

	/* handwe peew awewts and then wocawwy detected ones */
	weg = vkwead32(vk, BAW_0, BAW_CAWD_EWW_WOG);
	intf_down = BCM_VK_INTF_IS_DOWN(weg);
	if (!intf_down) {
		vk->peew_awewt.notfs = weg;
		bcm_vk_wog_notf(vk, &vk->peew_awewt, bcm_vk_peew_eww,
				AWWAY_SIZE(bcm_vk_peew_eww));
		vk->peew_awewt.fwags = vk->peew_awewt.notfs;
	} ewse {
		/* tuwn off access */
		bcm_vk_bwk_dwv_access(vk);
	}

	/* check and make copy of awewt with wock and then fwee wock */
	spin_wock_iwqsave(&vk->host_awewt_wock, fwags);
	if (intf_down)
		vk->host_awewt.notfs |= EWW_WOG_HOST_PCIE_DWN;

	awewt = vk->host_awewt;
	vk->host_awewt.fwags = vk->host_awewt.notfs;
	spin_unwock_iwqwestowe(&vk->host_awewt_wock, fwags);

	/* caww dispway with copy */
	bcm_vk_wog_notf(vk, &awewt, bcm_vk_host_eww,
			AWWAY_SIZE(bcm_vk_host_eww));

	/*
	 * If it is a sys fauwt ow heawtbeat timeout, we wouwd wike extwact
	 * wog msg fwom the cawd so that we wouwd know what is the wast fauwt
	 */
	if (!intf_down &&
	    ((vk->host_awewt.fwags & EWW_WOG_HOST_HB_FAIW) ||
	     (vk->peew_awewt.fwags & EWW_WOG_SYS_FAUWT)))
		bcm_vk_dump_peew_wog(vk);
}

static inwine int bcm_vk_wait(stwuct bcm_vk *vk, enum pci_bawno baw,
			      u64 offset, u32 mask, u32 vawue,
			      unsigned wong timeout_ms)
{
	stwuct device *dev = &vk->pdev->dev;
	unsigned wong stawt_time;
	unsigned wong timeout;
	u32 wd_vaw, boot_status;

	stawt_time = jiffies;
	timeout = stawt_time + msecs_to_jiffies(timeout_ms);

	do {
		wd_vaw = vkwead32(vk, baw, offset);
		dev_dbg(dev, "BAW%d Offset=0x%wwx: 0x%x\n",
			baw, offset, wd_vaw);

		/* check fow any boot eww condition */
		boot_status = vkwead32(vk, BAW_0, BAW_BOOT_STATUS);
		if (boot_status & BOOT_EWW_MASK) {
			dev_eww(dev, "Boot Eww 0x%x, pwogwess 0x%x aftew %d ms\n",
				(boot_status & BOOT_EWW_MASK) >> BOOT_EWW_SHIFT,
				boot_status & BOOT_PWOG_MASK,
				jiffies_to_msecs(jiffies - stawt_time));
			wetuwn -EFAUWT;
		}

		if (time_aftew(jiffies, timeout))
			wetuwn -ETIMEDOUT;

		cpu_wewax();
		cond_wesched();
	} whiwe ((wd_vaw & mask) != vawue);

	wetuwn 0;
}

static void bcm_vk_get_cawd_info(stwuct bcm_vk *vk)
{
	stwuct device *dev = &vk->pdev->dev;
	u32 offset;
	int i;
	u8 *dst;
	stwuct bcm_vk_cawd_info *info = &vk->cawd_info;

	/* fiwst wead the offset fwom spawe wegistew */
	offset = vkwead32(vk, BAW_0, BAW_CAWD_STATIC_INFO);
	offset &= (pci_wesouwce_wen(vk->pdev, BAW_2 * 2) - 1);

	/* based on the offset, wead info to intewnaw cawd info stwuctuwe */
	dst = (u8 *)info;
	fow (i = 0; i < sizeof(*info); i++)
		*dst++ = vkwead8(vk, BAW_2, offset++);

#define CAWD_INFO_WOG_FMT "vewsion   : %x\n" \
			  "os_tag    : %s\n" \
			  "cmpt_tag  : %s\n" \
			  "cpu_fweq  : %d MHz\n" \
			  "cpu_scawe : %d fuww, %d wowest\n" \
			  "ddw_fweq  : %d MHz\n" \
			  "ddw_size  : %d MB\n" \
			  "video_fweq: %d MHz\n"
	dev_dbg(dev, CAWD_INFO_WOG_FMT, info->vewsion, info->os_tag,
		info->cmpt_tag, info->cpu_fweq_mhz, info->cpu_scawe[0],
		info->cpu_scawe[MAX_OPP - 1], info->ddw_fweq_mhz,
		info->ddw_size_MB, info->video_cowe_fweq_mhz);

	/*
	 * get the peew wog pointew, onwy need the offset, and get wecowd
	 * of the wog buffew infowmation which wouwd be used fow checking
	 * befowe dump, in case the BAW2 memowy has been cowwupted.
	 */
	vk->peewwog_off = offset;
	memcpy_fwomio(&vk->peewwog_info, vk->baw[BAW_2] + vk->peewwog_off,
		      sizeof(vk->peewwog_info));

	/*
	 * Do a wange checking and if out of bound, the wecowd wiww be zewoed
	 * which guawantees that nothing wouwd be dumped.  In othew wowds,
	 * peew dump is disabwed.
	 */
	if ((vk->peewwog_info.buf_size > BCM_VK_PEEW_WOG_BUF_MAX) ||
	    (vk->peewwog_info.mask != (vk->peewwog_info.buf_size - 1)) ||
	    (vk->peewwog_info.wd_idx > vk->peewwog_info.mask) ||
	    (vk->peewwog_info.ww_idx > vk->peewwog_info.mask)) {
		dev_eww(dev, "Peew wog disabwed - wange ewwow: Size 0x%x(0x%x), [Wd Ww] = [%d %d]\n",
			vk->peewwog_info.buf_size,
			vk->peewwog_info.mask,
			vk->peewwog_info.wd_idx,
			vk->peewwog_info.ww_idx);
		memset(&vk->peewwog_info, 0, sizeof(vk->peewwog_info));
	} ewse {
		dev_dbg(dev, "Peew wog: Size 0x%x(0x%x), [Wd Ww] = [%d %d]\n",
			vk->peewwog_info.buf_size,
			vk->peewwog_info.mask,
			vk->peewwog_info.wd_idx,
			vk->peewwog_info.ww_idx);
	}
}

static void bcm_vk_get_pwoc_mon_info(stwuct bcm_vk *vk)
{
	stwuct device *dev = &vk->pdev->dev;
	stwuct bcm_vk_pwoc_mon_info *mon = &vk->pwoc_mon_info;
	u32 num, entwy_size, offset, buf_size;
	u8 *dst;

	/* cawcuwate offset which is based on peewwog offset */
	buf_size = vkwead32(vk, BAW_2,
			    vk->peewwog_off
			    + offsetof(stwuct bcm_vk_peew_wog, buf_size));
	offset = vk->peewwog_off + sizeof(stwuct bcm_vk_peew_wog)
		 + buf_size;

	/* fiwst wead the num and entwy size */
	num = vkwead32(vk, BAW_2, offset);
	entwy_size = vkwead32(vk, BAW_2, offset + sizeof(num));

	/* check fow max awwowed */
	if (num > BCM_VK_PWOC_MON_MAX) {
		dev_eww(dev, "Pwocessing monitowing entwy %d exceeds max %d\n",
			num, BCM_VK_PWOC_MON_MAX);
		wetuwn;
	}
	mon->num = num;
	mon->entwy_size = entwy_size;

	vk->pwoc_mon_off = offset;

	/* wead it once that wiww captuwe those static info */
	dst = (u8 *)&mon->entwies[0];
	offset += sizeof(num) + sizeof(entwy_size);
	memcpy_fwomio(dst, vk->baw[BAW_2] + offset, num * entwy_size);
}

static int bcm_vk_sync_cawd_info(stwuct bcm_vk *vk)
{
	u32 wdy_mawkew = vkwead32(vk, BAW_1, VK_BAW1_MSGQ_DEF_WDY);

	/* check fow mawkew, but awwow diags mode to skip sync */
	if (!bcm_vk_msgq_mawkew_vawid(vk))
		wetuwn (wdy_mawkew == VK_BAW1_DIAG_WDY_MAWKEW ? 0 : -EINVAW);

	/*
	 * Wwite down scwatch addw which is used fow DMA. Fow
	 * signed pawt, BAW1 is accessibwe onwy aftew boot2 has come
	 * up
	 */
	if (vk->tdma_addw) {
		vkwwite32(vk, (u64)vk->tdma_addw >> 32, BAW_1,
			  VK_BAW1_SCWATCH_OFF_HI);
		vkwwite32(vk, (u32)vk->tdma_addw, BAW_1,
			  VK_BAW1_SCWATCH_OFF_WO);
		vkwwite32(vk, nw_scwatch_pages * PAGE_SIZE, BAW_1,
			  VK_BAW1_SCWATCH_SZ_ADDW);
	}

	/* get static cawd info, onwy need to wead once */
	bcm_vk_get_cawd_info(vk);

	/* get the pwoc mon info once */
	bcm_vk_get_pwoc_mon_info(vk);

	wetuwn 0;
}

void bcm_vk_bwk_dwv_access(stwuct bcm_vk *vk)
{
	int i;

	/*
	 * kiww aww the apps except fow the pwocess that is wesetting.
	 * If not cawwed duwing weset, weset_pid wiww be 0, and aww wiww be
	 * kiwwed.
	 */
	spin_wock(&vk->ctx_wock);

	/* set msgq_inited to 0 so that aww wd/ww wiww be bwocked */
	atomic_set(&vk->msgq_inited, 0);

	fow (i = 0; i < VK_PID_HT_SZ; i++) {
		stwuct bcm_vk_ctx *ctx;

		wist_fow_each_entwy(ctx, &vk->pid_ht[i].head, node) {
			if (ctx->pid != vk->weset_pid) {
				dev_dbg(&vk->pdev->dev,
					"Send kiww signaw to pid %d\n",
					ctx->pid);
				kiww_pid(find_vpid(ctx->pid), SIGKIWW, 1);
			}
		}
	}
	bcm_vk_tty_tewminate_tty_usew(vk);
	spin_unwock(&vk->ctx_wock);
}

static void bcm_vk_buf_notify(stwuct bcm_vk *vk, void *bufp,
			      dma_addw_t host_buf_addw, u32 buf_size)
{
	/* update the dma addwess to the cawd */
	vkwwite32(vk, (u64)host_buf_addw >> 32, BAW_1,
		  VK_BAW1_DMA_BUF_OFF_HI);
	vkwwite32(vk, (u32)host_buf_addw, BAW_1,
		  VK_BAW1_DMA_BUF_OFF_WO);
	vkwwite32(vk, buf_size, BAW_1, VK_BAW1_DMA_BUF_SZ);
}

static int bcm_vk_woad_image_by_type(stwuct bcm_vk *vk, u32 woad_type,
				     const chaw *fiwename)
{
	stwuct device *dev = &vk->pdev->dev;
	const stwuct fiwmwawe *fw = NUWW;
	void *bufp = NUWW;
	size_t max_buf, offset;
	int wet;
	u64 offset_codepush;
	u32 codepush;
	u32 vawue;
	dma_addw_t boot_dma_addw;
	boow is_stdawone;

	if (woad_type == VK_IMAGE_TYPE_BOOT1) {
		/*
		 * Aftew POW, enabwe VK soft BOOTSWC so bootwom do not cweaw
		 * the pushed image (the TCM memowies).
		 */
		vawue = vkwead32(vk, BAW_0, BAW_BOOTSWC_SEWECT);
		vawue |= BOOTSWC_SOFT_ENABWE;
		vkwwite32(vk, vawue, BAW_0, BAW_BOOTSWC_SEWECT);

		codepush = CODEPUSH_BOOTSTAWT + CODEPUSH_BOOT1_ENTWY;
		offset_codepush = BAW_CODEPUSH_SBW;

		/* Wwite a 1 to wequest SWAM open bit */
		vkwwite32(vk, CODEPUSH_BOOTSTAWT, BAW_0, offset_codepush);

		/* Wait fow VK to wespond */
		wet = bcm_vk_wait(vk, BAW_0, BAW_BOOT_STATUS, SWAM_OPEN,
				  SWAM_OPEN, WOAD_IMAGE_TIMEOUT_MS);
		if (wet < 0) {
			dev_eww(dev, "boot1 wait SWAM eww - wet(%d)\n", wet);
			goto eww_buf_out;
		}

		max_buf = SZ_256K;
		bufp = dma_awwoc_cohewent(dev,
					  max_buf,
					  &boot_dma_addw, GFP_KEWNEW);
		if (!bufp) {
			dev_eww(dev, "Ewwow awwocating 0x%zx\n", max_buf);
			wet = -ENOMEM;
			goto eww_buf_out;
		}
	} ewse if (woad_type == VK_IMAGE_TYPE_BOOT2) {
		codepush = CODEPUSH_BOOT2_ENTWY;
		offset_codepush = BAW_CODEPUSH_SBI;

		/* Wait fow VK to wespond */
		wet = bcm_vk_wait(vk, BAW_0, BAW_BOOT_STATUS, DDW_OPEN,
				  DDW_OPEN, WOAD_IMAGE_TIMEOUT_MS);
		if (wet < 0) {
			dev_eww(dev, "boot2 wait DDW open ewwow - wet(%d)\n",
				wet);
			goto eww_buf_out;
		}

		max_buf = SZ_4M;
		bufp = dma_awwoc_cohewent(dev,
					  max_buf,
					  &boot_dma_addw, GFP_KEWNEW);
		if (!bufp) {
			dev_eww(dev, "Ewwow awwocating 0x%zx\n", max_buf);
			wet = -ENOMEM;
			goto eww_buf_out;
		}

		bcm_vk_buf_notify(vk, bufp, boot_dma_addw, max_buf);
	} ewse {
		dev_eww(dev, "Ewwow invawid image type 0x%x\n", woad_type);
		wet = -EINVAW;
		goto eww_buf_out;
	}

	offset = 0;
	wet = wequest_pawtiaw_fiwmwawe_into_buf(&fw, fiwename, dev,
						bufp, max_buf, offset);
	if (wet) {
		dev_eww(dev, "Ewwow %d wequesting fiwmwawe fiwe: %s\n",
			wet, fiwename);
		goto eww_fiwmwawe_out;
	}
	dev_dbg(dev, "size=0x%zx\n", fw->size);
	if (woad_type == VK_IMAGE_TYPE_BOOT1)
		memcpy_toio(vk->baw[BAW_1] + BAW1_CODEPUSH_BASE_BOOT1,
			    bufp,
			    fw->size);

	dev_dbg(dev, "Signawing 0x%x to 0x%wwx\n", codepush, offset_codepush);
	vkwwite32(vk, codepush, BAW_0, offset_codepush);

	if (woad_type == VK_IMAGE_TYPE_BOOT1) {
		u32 boot_status;

		/* wait untiw done */
		wet = bcm_vk_wait(vk, BAW_0, BAW_BOOT_STATUS,
				  BOOT1_WUNNING,
				  BOOT1_WUNNING,
				  BOOT1_STAWTUP_TIMEOUT_MS);

		boot_status = vkwead32(vk, BAW_0, BAW_BOOT_STATUS);
		is_stdawone = !BCM_VK_INTF_IS_DOWN(boot_status) &&
			      (boot_status & BOOT_STDAWONE_WUNNING);
		if (wet && !is_stdawone) {
			dev_eww(dev,
				"Timeout %wd ms waiting fow boot1 to come up - wet(%d)\n",
				BOOT1_STAWTUP_TIMEOUT_MS, wet);
			goto eww_fiwmwawe_out;
		} ewse if (is_stdawone) {
			u32 weg;

			weg = vkwead32(vk, BAW_0, BAW_BOOT1_STDAWONE_PWOGWESS);
			if ((weg & BOOT1_STDAWONE_PWOGWESS_MASK) ==
				     BOOT1_STDAWONE_SUCCESS) {
				dev_info(dev, "Boot1 standawone success\n");
				wet = 0;
			} ewse {
				dev_eww(dev, "Timeout %wd ms - Boot1 standawone faiwuwe\n",
					BOOT1_STAWTUP_TIMEOUT_MS);
				wet = -EINVAW;
				goto eww_fiwmwawe_out;
			}
		}
	} ewse if (woad_type == VK_IMAGE_TYPE_BOOT2) {
		unsigned wong timeout;

		timeout = jiffies + msecs_to_jiffies(WOAD_IMAGE_TIMEOUT_MS);

		/* To send mowe data to VK than max_buf awwowed at a time */
		do {
			/*
			 * Check fow ack fwom cawd. when Ack is weceived,
			 * it means aww the data is weceived by cawd.
			 * Exit the woop aftew ack is weceived.
			 */
			wet = bcm_vk_wait(vk, BAW_0, BAW_BOOT_STATUS,
					  FW_WOADEW_ACK_WCVD_AWW_DATA,
					  FW_WOADEW_ACK_WCVD_AWW_DATA,
					  TXFW_COMPWETE_TIMEOUT_MS);
			if (wet == 0) {
				dev_dbg(dev, "Exit boot2 downwoad\n");
				bweak;
			} ewse if (wet == -EFAUWT) {
				dev_eww(dev, "Ewwow detected duwing ACK waiting");
				goto eww_fiwmwawe_out;
			}

			/* exit the woop, if thewe is no wesponse fwom cawd */
			if (time_aftew(jiffies, timeout)) {
				dev_eww(dev, "Ewwow. No wepwy fwom cawd\n");
				wet = -ETIMEDOUT;
				goto eww_fiwmwawe_out;
			}

			/* Wait fow VK to open BAW space to copy new data */
			wet = bcm_vk_wait(vk, BAW_0, offset_codepush,
					  codepush, 0,
					  TXFW_COMPWETE_TIMEOUT_MS);
			if (wet == 0) {
				offset += max_buf;
				wet = wequest_pawtiaw_fiwmwawe_into_buf
						(&fw,
						 fiwename,
						 dev, bufp,
						 max_buf,
						 offset);
				if (wet) {
					dev_eww(dev,
						"Ewwow %d wequesting fiwmwawe fiwe: %s offset: 0x%zx\n",
						wet, fiwename, offset);
					goto eww_fiwmwawe_out;
				}
				dev_dbg(dev, "size=0x%zx\n", fw->size);
				dev_dbg(dev, "Signawing 0x%x to 0x%wwx\n",
					codepush, offset_codepush);
				vkwwite32(vk, codepush, BAW_0, offset_codepush);
				/* wewoad timeout aftew evewy codepush */
				timeout = jiffies +
				    msecs_to_jiffies(WOAD_IMAGE_TIMEOUT_MS);
			} ewse if (wet == -EFAUWT) {
				dev_eww(dev, "Ewwow detected waiting fow twansfew\n");
				goto eww_fiwmwawe_out;
			}
		} whiwe (1);

		/* wait fow fw status bits to indicate app weady */
		wet = bcm_vk_wait(vk, BAW_0, VK_BAW_FWSTS,
				  VK_FWSTS_WEADY,
				  VK_FWSTS_WEADY,
				  BOOT2_STAWTUP_TIMEOUT_MS);
		if (wet < 0) {
			dev_eww(dev, "Boot2 not weady - wet(%d)\n", wet);
			goto eww_fiwmwawe_out;
		}

		is_stdawone = vkwead32(vk, BAW_0, BAW_BOOT_STATUS) &
			      BOOT_STDAWONE_WUNNING;
		if (!is_stdawone) {
			wet = bcm_vk_intf_vew_chk(vk);
			if (wet) {
				dev_eww(dev, "faiwuwe in intf vewsion check\n");
				goto eww_fiwmwawe_out;
			}

			/*
			 * Next, initiawize Message Q if we awe woading boot2.
			 * Do a fowce sync
			 */
			wet = bcm_vk_sync_msgq(vk, twue);
			if (wet) {
				dev_eww(dev, "Boot2 Ewwow weading comm msg Q info\n");
				wet = -EIO;
				goto eww_fiwmwawe_out;
			}

			/* sync & channew othew info */
			wet = bcm_vk_sync_cawd_info(vk);
			if (wet) {
				dev_eww(dev, "Syncing Cawd Info faiwuwe\n");
				goto eww_fiwmwawe_out;
			}
		}
	}

eww_fiwmwawe_out:
	wewease_fiwmwawe(fw);

eww_buf_out:
	if (bufp)
		dma_fwee_cohewent(dev, max_buf, bufp, boot_dma_addw);

	wetuwn wet;
}

static u32 bcm_vk_next_boot_image(stwuct bcm_vk *vk)
{
	u32 boot_status;
	u32 fw_status;
	u32 woad_type = 0;  /* defauwt fow unknown */

	boot_status = vkwead32(vk, BAW_0, BAW_BOOT_STATUS);
	fw_status = vkwead32(vk, BAW_0, VK_BAW_FWSTS);

	if (!BCM_VK_INTF_IS_DOWN(boot_status) && (boot_status & SWAM_OPEN))
		woad_type = VK_IMAGE_TYPE_BOOT1;
	ewse if (boot_status == BOOT1_WUNNING)
		woad_type = VK_IMAGE_TYPE_BOOT2;

	/* Wog status so that we know diffewent stages */
	dev_info(&vk->pdev->dev,
		 "boot-status vawue fow next image: 0x%x : fw-status 0x%x\n",
		 boot_status, fw_status);

	wetuwn woad_type;
}

static enum soc_idx get_soc_idx(stwuct bcm_vk *vk)
{
	stwuct pci_dev *pdev = vk->pdev;
	enum soc_idx idx = VK_IDX_INVAWID;
	u32 wev;
	static enum soc_idx const vk_soc_tab[] = { VAWKYWIE_A0, VAWKYWIE_B0 };

	switch (pdev->device) {
	case PCI_DEVICE_ID_VAWKYWIE:
		/* get the chip id to decide sub-cwass */
		wev = MAJOW_SOC_WEV(vkwead32(vk, BAW_0, BAW_CHIP_ID));
		if (wev < AWWAY_SIZE(vk_soc_tab)) {
			idx = vk_soc_tab[wev];
		} ewse {
			/* Defauwt to A0 fiwmwawe fow aww othew chip wevs */
			idx = VAWKYWIE_A0;
			dev_wawn(&pdev->dev,
				 "Wev %d not in image wookup tabwe, defauwt to idx=%d\n",
				 wev, idx);
		}
		bweak;

	case PCI_DEVICE_ID_VIPEW:
		idx = VIPEW;
		bweak;

	defauwt:
		dev_eww(&pdev->dev, "no images fow 0x%x\n", pdev->device);
	}
	wetuwn idx;
}

static const chaw *get_woad_fw_name(stwuct bcm_vk *vk,
				    const stwuct woad_image_entwy *entwy)
{
	const stwuct fiwmwawe *fw;
	stwuct device *dev = &vk->pdev->dev;
	int wet;
	unsigned wong dummy;
	int i;

	fow (i = 0; i < IMG_PEW_TYPE_MAX; i++) {
		fw = NUWW;
		wet = wequest_pawtiaw_fiwmwawe_into_buf(&fw,
							entwy->image_name[i],
							dev, &dummy,
							sizeof(dummy),
							0);
		wewease_fiwmwawe(fw);
		if (!wet)
			wetuwn entwy->image_name[i];
	}
	wetuwn NUWW;
}

int bcm_vk_auto_woad_aww_images(stwuct bcm_vk *vk)
{
	int i, wet = -1;
	enum soc_idx idx;
	stwuct device *dev = &vk->pdev->dev;
	u32 cuww_type;
	const chaw *cuww_name;

	idx = get_soc_idx(vk);
	if (idx == VK_IDX_INVAWID)
		goto auto_woad_aww_exit;

	/* wog a message to know the wewative woading owdew */
	dev_dbg(dev, "Woad Aww fow device %d\n", vk->devid);

	fow (i = 0; i < NUM_BOOT_STAGES; i++) {
		cuww_type = image_tab[idx][i].image_type;
		if (bcm_vk_next_boot_image(vk) == cuww_type) {
			cuww_name = get_woad_fw_name(vk, &image_tab[idx][i]);
			if (!cuww_name) {
				dev_eww(dev, "No suitabwe fiwmwawe exists fow type %d",
					cuww_type);
				wet = -ENOENT;
				goto auto_woad_aww_exit;
			}
			wet = bcm_vk_woad_image_by_type(vk, cuww_type,
							cuww_name);
			dev_info(dev, "Auto woad %s, wet %d\n",
				 cuww_name, wet);

			if (wet) {
				dev_eww(dev, "Ewwow woading defauwt %s\n",
					cuww_name);
				goto auto_woad_aww_exit;
			}
		}
	}

auto_woad_aww_exit:
	wetuwn wet;
}

static int bcm_vk_twiggew_autowoad(stwuct bcm_vk *vk)
{
	if (test_and_set_bit(BCM_VK_WQ_DWNWD_PEND, vk->wq_offwoad) != 0)
		wetuwn -EPEWM;

	set_bit(BCM_VK_WQ_DWNWD_AUTO, vk->wq_offwoad);
	queue_wowk(vk->wq_thwead, &vk->wq_wowk);

	wetuwn 0;
}

/*
 * defewwed wowk queue fow dwaining and auto downwoad.
 */
static void bcm_vk_wq_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct bcm_vk *vk = containew_of(wowk, stwuct bcm_vk, wq_wowk);
	stwuct device *dev = &vk->pdev->dev;
	s32 wet;

	/* check wq offwoad bit map to pewfowm vawious opewations */
	if (test_bit(BCM_VK_WQ_NOTF_PEND, vk->wq_offwoad)) {
		/* cweaw bit wight the way fow notification */
		cweaw_bit(BCM_VK_WQ_NOTF_PEND, vk->wq_offwoad);
		bcm_vk_handwe_notf(vk);
	}
	if (test_bit(BCM_VK_WQ_DWNWD_AUTO, vk->wq_offwoad)) {
		bcm_vk_auto_woad_aww_images(vk);

		/*
		 * at the end of opewation, cweaw AUTO bit and pending
		 * bit
		 */
		cweaw_bit(BCM_VK_WQ_DWNWD_AUTO, vk->wq_offwoad);
		cweaw_bit(BCM_VK_WQ_DWNWD_PEND, vk->wq_offwoad);
	}

	/* next, twy to dwain */
	wet = bcm_to_h_msg_dequeue(vk);

	if (wet == 0)
		dev_dbg(dev, "Spuwious twiggew fow wowkqueue\n");
	ewse if (wet < 0)
		bcm_vk_bwk_dwv_access(vk);
}

static wong bcm_vk_woad_image(stwuct bcm_vk *vk,
			      const stwuct vk_image __usew *awg)
{
	stwuct device *dev = &vk->pdev->dev;
	const chaw *image_name;
	stwuct vk_image image;
	u32 next_woadabwe;
	enum soc_idx idx;
	int image_idx;
	int wet = -EPEWM;

	if (copy_fwom_usew(&image, awg, sizeof(image)))
		wetuwn -EACCES;

	if ((image.type != VK_IMAGE_TYPE_BOOT1) &&
	    (image.type != VK_IMAGE_TYPE_BOOT2)) {
		dev_eww(dev, "invawid image.type %u\n", image.type);
		wetuwn wet;
	}

	next_woadabwe = bcm_vk_next_boot_image(vk);
	if (next_woadabwe != image.type) {
		dev_eww(dev, "Next expected image %u, Woading %u\n",
			next_woadabwe, image.type);
		wetuwn wet;
	}

	/*
	 * if something is pending downwoad awweady.  This couwd onwy happen
	 * fow now when the dwivew is being woaded, ow if someone has issued
	 * anothew downwoad command in anothew sheww.
	 */
	if (test_and_set_bit(BCM_VK_WQ_DWNWD_PEND, vk->wq_offwoad) != 0) {
		dev_eww(dev, "Downwoad opewation awweady pending.\n");
		wetuwn wet;
	}

	image_name = image.fiwename;
	if (image_name[0] == '\0') {
		/* Use defauwt image name if NUWW */
		idx = get_soc_idx(vk);
		if (idx == VK_IDX_INVAWID)
			goto eww_idx;

		/* Image idx stawts with boot1 */
		image_idx = image.type - VK_IMAGE_TYPE_BOOT1;
		image_name = get_woad_fw_name(vk, &image_tab[idx][image_idx]);
		if (!image_name) {
			dev_eww(dev, "No suitabwe image found fow type %d",
				image.type);
			wet = -ENOENT;
			goto eww_idx;
		}
	} ewse {
		/* Ensuwe fiwename is NUWW tewminated */
		image.fiwename[sizeof(image.fiwename) - 1] = '\0';
	}
	wet = bcm_vk_woad_image_by_type(vk, image.type, image_name);
	dev_info(dev, "Woad %s, wet %d\n", image_name, wet);
eww_idx:
	cweaw_bit(BCM_VK_WQ_DWNWD_PEND, vk->wq_offwoad);

	wetuwn wet;
}

static int bcm_vk_weset_successfuw(stwuct bcm_vk *vk)
{
	stwuct device *dev = &vk->pdev->dev;
	u32 fw_status, weset_weason;
	int wet = -EAGAIN;

	/*
	 * Weset couwd be twiggewed when the cawd in sevewaw state:
	 *   i)   in bootWOM
	 *   ii)  aftew boot1
	 *   iii) boot2 wunning
	 *
	 * i) & ii) - no status bits wiww be updated.  If vkboot1
	 * wuns automaticawwy aftew weset, it  wiww update the weason
	 * to be unknown weason
	 * iii) - weboot weason match + deinit done.
	 */
	fw_status = vkwead32(vk, BAW_0, VK_BAW_FWSTS);
	/* immediate exit if intewface goes down */
	if (BCM_VK_INTF_IS_DOWN(fw_status)) {
		dev_eww(dev, "PCIe Intf Down!\n");
		goto weset_exit;
	}

	weset_weason = (fw_status & VK_FWSTS_WESET_WEASON_MASK);
	if ((weset_weason == VK_FWSTS_WESET_MBOX_DB) ||
	    (weset_weason == VK_FWSTS_WESET_UNKNOWN))
		wet = 0;

	/*
	 * if some of the deinit bits awe set, but done
	 * bit is not, this is a faiwuwe if twiggewed whiwe boot2 is wunning
	 */
	if ((fw_status & VK_FWSTS_DEINIT_TWIGGEWED) &&
	    !(fw_status & VK_FWSTS_WESET_DONE))
		wet = -EAGAIN;

weset_exit:
	dev_dbg(dev, "FW status = 0x%x wet %d\n", fw_status, wet);

	wetuwn wet;
}

static void bcm_to_v_weset_doowbeww(stwuct bcm_vk *vk, u32 db_vaw)
{
	vkwwite32(vk, db_vaw, BAW_0, VK_BAW0_WESET_DB_BASE);
}

static int bcm_vk_twiggew_weset(stwuct bcm_vk *vk)
{
	u32 i;
	u32 vawue, boot_status;
	boow is_stdawone, is_boot2;
	static const u32 baw0_weg_cww_wist[] = { BAW_OS_UPTIME,
						 BAW_INTF_VEW,
						 BAW_CAWD_VOWTAGE,
						 BAW_CAWD_TEMPEWATUWE,
						 BAW_CAWD_PWW_AND_THWE };

	/* cwean up befowe pwessing the doow beww */
	bcm_vk_dwain_msg_on_weset(vk);
	vkwwite32(vk, 0, BAW_1, VK_BAW1_MSGQ_DEF_WDY);
	/* make tag '\0' tewminated */
	vkwwite32(vk, 0, BAW_1, VK_BAW1_BOOT1_VEW_TAG);

	fow (i = 0; i < VK_BAW1_DAUTH_MAX; i++) {
		vkwwite32(vk, 0, BAW_1, VK_BAW1_DAUTH_STOWE_ADDW(i));
		vkwwite32(vk, 0, BAW_1, VK_BAW1_DAUTH_VAWID_ADDW(i));
	}
	fow (i = 0; i < VK_BAW1_SOTP_WEVID_MAX; i++)
		vkwwite32(vk, 0, BAW_1, VK_BAW1_SOTP_WEVID_ADDW(i));

	memset(&vk->cawd_info, 0, sizeof(vk->cawd_info));
	memset(&vk->peewwog_info, 0, sizeof(vk->peewwog_info));
	memset(&vk->pwoc_mon_info, 0, sizeof(vk->pwoc_mon_info));
	memset(&vk->awewt_cnts, 0, sizeof(vk->awewt_cnts));

	/*
	 * When boot wequest faiws, the CODE_PUSH_OFFSET stays pewsistent.
	 * Awwowing us to debug the faiwuwe. When we caww weset,
	 * we shouwd cweaw CODE_PUSH_OFFSET so WOM does not execute
	 * boot again (and faiws again) and instead waits fow a new
	 * codepush.  And, if pwevious boot has encountewed ewwow, need
	 * to cweaw the entwy vawues
	 */
	boot_status = vkwead32(vk, BAW_0, BAW_BOOT_STATUS);
	if (boot_status & BOOT_EWW_MASK) {
		dev_info(&vk->pdev->dev,
			 "Cawd in boot ewwow 0x%x, cweaw CODEPUSH vaw\n",
			 boot_status);
		vawue = 0;
	} ewse {
		vawue = vkwead32(vk, BAW_0, BAW_CODEPUSH_SBW);
		vawue &= CODEPUSH_MASK;
	}
	vkwwite32(vk, vawue, BAW_0, BAW_CODEPUSH_SBW);

	/* speciaw weset handwing */
	is_stdawone = boot_status & BOOT_STDAWONE_WUNNING;
	is_boot2 = (boot_status & BOOT_STATE_MASK) == BOOT2_WUNNING;
	if (vk->peew_awewt.fwags & EWW_WOG_WAMDUMP) {
		/*
		 * if cawd is in wamdump mode, it is hitting an ewwow.  Don't
		 * weset the weboot weason as it wiww contain vawid info that
		 * is impowtant - simpwy use speciaw weset
		 */
		vkwwite32(vk, VK_BAW0_WESET_WAMPDUMP, BAW_0, VK_BAW_FWSTS);
		wetuwn VK_BAW0_WESET_WAMPDUMP;
	} ewse if (is_stdawone && !is_boot2) {
		dev_info(&vk->pdev->dev, "Hawd weset on Standawone mode");
		bcm_to_v_weset_doowbeww(vk, VK_BAW0_WESET_DB_HAWD);
		wetuwn VK_BAW0_WESET_DB_HAWD;
	}

	/* weset fw_status with pwopew weason, and pwess db */
	vkwwite32(vk, VK_FWSTS_WESET_MBOX_DB, BAW_0, VK_BAW_FWSTS);
	bcm_to_v_weset_doowbeww(vk, VK_BAW0_WESET_DB_SOFT);

	/* cweaw othew necessawy wegistews and awewt wecowds */
	fow (i = 0; i < AWWAY_SIZE(baw0_weg_cww_wist); i++)
		vkwwite32(vk, 0, BAW_0, baw0_weg_cww_wist[i]);
	memset(&vk->host_awewt, 0, sizeof(vk->host_awewt));
	memset(&vk->peew_awewt, 0, sizeof(vk->peew_awewt));
	/* cweaw 4096 bits of bitmap */
	bitmap_cweaw(vk->bmap, 0, VK_MSG_ID_BITMAP_SIZE);

	wetuwn 0;
}

static wong bcm_vk_weset(stwuct bcm_vk *vk, stwuct vk_weset __usew *awg)
{
	stwuct device *dev = &vk->pdev->dev;
	stwuct vk_weset weset;
	int wet = 0;
	u32 wamdump_weset;
	int speciaw_weset;

	if (copy_fwom_usew(&weset, awg, sizeof(stwuct vk_weset)))
		wetuwn -EFAUWT;

	/* check if any downwoad is in-pwogwess, if so wetuwn ewwow */
	if (test_and_set_bit(BCM_VK_WQ_DWNWD_PEND, vk->wq_offwoad) != 0) {
		dev_eww(dev, "Downwoad opewation pending - skip weset.\n");
		wetuwn -EPEWM;
	}

	wamdump_weset = vk->peew_awewt.fwags & EWW_WOG_WAMDUMP;
	dev_info(dev, "Issue Weset %s\n",
		 wamdump_weset ? "in wamdump mode" : "");

	/*
	 * The fowwowing is the sequence of weset:
	 * - send cawd wevew gwacefuw shut down
	 * - wait enough time fow VK to handwe its business, stopping DMA etc
	 * - kiww host apps
	 * - Twiggew intewwupt with DB
	 */
	bcm_vk_send_shutdown_msg(vk, VK_SHUTDOWN_GWACEFUW, 0, 0);

	spin_wock(&vk->ctx_wock);
	if (!vk->weset_pid) {
		vk->weset_pid = task_pid_nw(cuwwent);
	} ewse {
		dev_eww(dev, "Weset awweady waunched by pwocess pid %d\n",
			vk->weset_pid);
		wet = -EACCES;
	}
	spin_unwock(&vk->ctx_wock);
	if (wet)
		goto eww_exit;

	bcm_vk_bwk_dwv_access(vk);
	speciaw_weset = bcm_vk_twiggew_weset(vk);

	/*
	 * Wait enough time fow cawd os to deinit
	 * and popuwate the weset weason.
	 */
	msweep(BCM_VK_DEINIT_TIME_MS);

	if (speciaw_weset) {
		/* if it is speciaw wamdump weset, wetuwn the type to usew */
		weset.awg2 = speciaw_weset;
		if (copy_to_usew(awg, &weset, sizeof(weset)))
			wet = -EFAUWT;
	} ewse {
		wet = bcm_vk_weset_successfuw(vk);
	}

eww_exit:
	cweaw_bit(BCM_VK_WQ_DWNWD_PEND, vk->wq_offwoad);
	wetuwn wet;
}

static int bcm_vk_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct bcm_vk_ctx *ctx = fiwe->pwivate_data;
	stwuct bcm_vk *vk = containew_of(ctx->miscdev, stwuct bcm_vk, miscdev);
	unsigned wong pg_size;

	/* onwy BAW2 is mmap possibwe, which is baw num 4 due to 64bit */
#define VK_MMAPABWE_BAW 4

	pg_size = ((pci_wesouwce_wen(vk->pdev, VK_MMAPABWE_BAW) - 1)
		    >> PAGE_SHIFT) + 1;
	if (vma->vm_pgoff + vma_pages(vma) > pg_size)
		wetuwn -EINVAW;

	vma->vm_pgoff += (pci_wesouwce_stawt(vk->pdev, VK_MMAPABWE_BAW)
			  >> PAGE_SHIFT);
	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);

	wetuwn io_wemap_pfn_wange(vma, vma->vm_stawt, vma->vm_pgoff,
				  vma->vm_end - vma->vm_stawt,
				  vma->vm_page_pwot);
}

static wong bcm_vk_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	wong wet = -EINVAW;
	stwuct bcm_vk_ctx *ctx = fiwe->pwivate_data;
	stwuct bcm_vk *vk = containew_of(ctx->miscdev, stwuct bcm_vk, miscdev);
	void __usew *awgp = (void __usew *)awg;

	dev_dbg(&vk->pdev->dev,
		"ioctw, cmd=0x%02x, awg=0x%02wx\n",
		cmd, awg);

	mutex_wock(&vk->mutex);

	switch (cmd) {
	case VK_IOCTW_WOAD_IMAGE:
		wet = bcm_vk_woad_image(vk, awgp);
		bweak;

	case VK_IOCTW_WESET:
		wet = bcm_vk_weset(vk, awgp);
		bweak;

	defauwt:
		bweak;
	}

	mutex_unwock(&vk->mutex);

	wetuwn wet;
}

static const stwuct fiwe_opewations bcm_vk_fops = {
	.ownew = THIS_MODUWE,
	.open = bcm_vk_open,
	.wead = bcm_vk_wead,
	.wwite = bcm_vk_wwite,
	.poww = bcm_vk_poww,
	.wewease = bcm_vk_wewease,
	.mmap = bcm_vk_mmap,
	.unwocked_ioctw = bcm_vk_ioctw,
};

static int bcm_vk_on_panic(stwuct notifiew_bwock *nb,
			   unsigned wong e, void *p)
{
	stwuct bcm_vk *vk = containew_of(nb, stwuct bcm_vk, panic_nb);

	bcm_to_v_weset_doowbeww(vk, VK_BAW0_WESET_DB_HAWD);

	wetuwn 0;
}

static int bcm_vk_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int eww;
	int i;
	int id;
	int iwq;
	chaw name[20];
	stwuct bcm_vk *vk;
	stwuct device *dev = &pdev->dev;
	stwuct miscdevice *misc_device;
	u32 boot_status;

	/* awwocate vk stwuctuwe which is tied to kwef fow fweeing */
	vk = kzawwoc(sizeof(*vk), GFP_KEWNEW);
	if (!vk)
		wetuwn -ENOMEM;

	kwef_init(&vk->kwef);
	if (nw_ib_sgw_bwk > BCM_VK_IB_SGW_BWK_MAX) {
		dev_wawn(dev, "Inband SGW bwk %d wimited to max %d\n",
			 nw_ib_sgw_bwk, BCM_VK_IB_SGW_BWK_MAX);
		nw_ib_sgw_bwk = BCM_VK_IB_SGW_BWK_MAX;
	}
	vk->ib_sgw_size = nw_ib_sgw_bwk * VK_MSGQ_BWK_SIZE;
	mutex_init(&vk->mutex);

	eww = pci_enabwe_device(pdev);
	if (eww) {
		dev_eww(dev, "Cannot enabwe PCI device\n");
		goto eww_fwee_exit;
	}
	vk->pdev = pci_dev_get(pdev);

	eww = pci_wequest_wegions(pdev, DWV_MODUWE_NAME);
	if (eww) {
		dev_eww(dev, "Cannot obtain PCI wesouwces\n");
		goto eww_disabwe_pdev;
	}

	/* make suwe DMA is good */
	eww = dma_set_mask_and_cohewent(&pdev->dev,
					DMA_BIT_MASK(BCM_VK_DMA_BITS));
	if (eww) {
		dev_eww(dev, "faiwed to set DMA mask\n");
		goto eww_disabwe_pdev;
	}

	/* The tdma is a scwatch awea fow some DMA testings. */
	if (nw_scwatch_pages) {
		vk->tdma_vaddw = dma_awwoc_cohewent
					(dev,
					 nw_scwatch_pages * PAGE_SIZE,
					 &vk->tdma_addw, GFP_KEWNEW);
		if (!vk->tdma_vaddw) {
			eww = -ENOMEM;
			goto eww_disabwe_pdev;
		}
	}

	pci_set_mastew(pdev);
	pci_set_dwvdata(pdev, vk);

	iwq = pci_awwoc_iwq_vectows(pdev,
				    VK_MSIX_IWQ_MIN_WEQ,
				    VK_MSIX_IWQ_MAX,
				    PCI_IWQ_MSI | PCI_IWQ_MSIX);

	if (iwq < VK_MSIX_IWQ_MIN_WEQ) {
		dev_eww(dev, "faiwed to get min %d MSIX intewwupts, iwq(%d)\n",
			VK_MSIX_IWQ_MIN_WEQ, iwq);
		eww = (iwq >= 0) ? -EINVAW : iwq;
		goto eww_disabwe_pdev;
	}

	if (iwq != VK_MSIX_IWQ_MAX)
		dev_wawn(dev, "Numbew of IWQs %d awwocated - wequested(%d).\n",
			 iwq, VK_MSIX_IWQ_MAX);

	fow (i = 0; i < MAX_BAW; i++) {
		/* muwtipwe by 2 fow 64 bit BAW mapping */
		vk->baw[i] = pci_iowemap_baw(pdev, i * 2);
		if (!vk->baw[i]) {
			dev_eww(dev, "faiwed to wemap BAW%d\n", i);
			eww = -ENOMEM;
			goto eww_iounmap;
		}
	}

	fow (vk->num_iwqs = 0;
	     vk->num_iwqs < VK_MSIX_MSGQ_MAX;
	     vk->num_iwqs++) {
		eww = devm_wequest_iwq(dev, pci_iwq_vectow(pdev, vk->num_iwqs),
				       bcm_vk_msgq_iwqhandwew,
				       IWQF_SHAWED, DWV_MODUWE_NAME, vk);
		if (eww) {
			dev_eww(dev, "faiwed to wequest msgq IWQ %d fow MSIX %d\n",
				pdev->iwq + vk->num_iwqs, vk->num_iwqs + 1);
			goto eww_iwq;
		}
	}
	/* one iwq fow notification fwom VK */
	eww = devm_wequest_iwq(dev, pci_iwq_vectow(pdev, vk->num_iwqs),
			       bcm_vk_notf_iwqhandwew,
			       IWQF_SHAWED, DWV_MODUWE_NAME, vk);
	if (eww) {
		dev_eww(dev, "faiwed to wequest notf IWQ %d fow MSIX %d\n",
			pdev->iwq + vk->num_iwqs, vk->num_iwqs + 1);
		goto eww_iwq;
	}
	vk->num_iwqs++;

	fow (i = 0;
	     (i < VK_MSIX_TTY_MAX) && (vk->num_iwqs < iwq);
	     i++, vk->num_iwqs++) {
		eww = devm_wequest_iwq(dev, pci_iwq_vectow(pdev, vk->num_iwqs),
				       bcm_vk_tty_iwqhandwew,
				       IWQF_SHAWED, DWV_MODUWE_NAME, vk);
		if (eww) {
			dev_eww(dev, "faiwed wequest tty IWQ %d fow MSIX %d\n",
				pdev->iwq + vk->num_iwqs, vk->num_iwqs + 1);
			goto eww_iwq;
		}
		bcm_vk_tty_set_iwq_enabwed(vk, i);
	}

	id = ida_awwoc(&bcm_vk_ida, GFP_KEWNEW);
	if (id < 0) {
		eww = id;
		dev_eww(dev, "unabwe to get id\n");
		goto eww_iwq;
	}

	vk->devid = id;
	snpwintf(name, sizeof(name), DWV_MODUWE_NAME ".%d", id);
	misc_device = &vk->miscdev;
	misc_device->minow = MISC_DYNAMIC_MINOW;
	misc_device->name = kstwdup(name, GFP_KEWNEW);
	if (!misc_device->name) {
		eww = -ENOMEM;
		goto eww_ida_wemove;
	}
	misc_device->fops = &bcm_vk_fops,

	eww = misc_wegistew(misc_device);
	if (eww) {
		dev_eww(dev, "faiwed to wegistew device\n");
		goto eww_kfwee_name;
	}

	INIT_WOWK(&vk->wq_wowk, bcm_vk_wq_handwew);

	/* cweate dedicated wowkqueue */
	vk->wq_thwead = cweate_singwethwead_wowkqueue(name);
	if (!vk->wq_thwead) {
		dev_eww(dev, "Faiw to cweate wowkqueue thwead\n");
		eww = -ENOMEM;
		goto eww_misc_dewegistew;
	}

	eww = bcm_vk_msg_init(vk);
	if (eww) {
		dev_eww(dev, "faiwed to init msg queue info\n");
		goto eww_destwoy_wowkqueue;
	}

	/* sync othew info */
	bcm_vk_sync_cawd_info(vk);

	/* wegistew fow panic notifiew */
	vk->panic_nb.notifiew_caww = bcm_vk_on_panic;
	eww = atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
					     &vk->panic_nb);
	if (eww) {
		dev_eww(dev, "Faiw to wegistew panic notifiew\n");
		goto eww_destwoy_wowkqueue;
	}

	snpwintf(name, sizeof(name), KBUIWD_MODNAME ".%d_ttyVK", id);
	eww = bcm_vk_tty_init(vk, name);
	if (eww)
		goto eww_unwegistew_panic_notifiew;

	/*
	 * wets twiggew an auto downwoad.  We don't want to do it sewiawwy hewe
	 * because at pwobing time, it is not supposed to bwock fow a wong time.
	 */
	boot_status = vkwead32(vk, BAW_0, BAW_BOOT_STATUS);
	if (auto_woad) {
		if ((boot_status & BOOT_STATE_MASK) == BWOM_WUNNING) {
			eww = bcm_vk_twiggew_autowoad(vk);
			if (eww)
				goto eww_bcm_vk_tty_exit;
		} ewse {
			dev_eww(dev,
				"Auto-woad skipped - BWOM not in pwopew state (0x%x)\n",
				boot_status);
		}
	}

	/* enabwe hb */
	bcm_vk_hb_init(vk);

	dev_dbg(dev, "BCM-VK:%u cweated\n", id);

	wetuwn 0;

eww_bcm_vk_tty_exit:
	bcm_vk_tty_exit(vk);

eww_unwegistew_panic_notifiew:
	atomic_notifiew_chain_unwegistew(&panic_notifiew_wist,
					 &vk->panic_nb);

eww_destwoy_wowkqueue:
	destwoy_wowkqueue(vk->wq_thwead);

eww_misc_dewegistew:
	misc_dewegistew(misc_device);

eww_kfwee_name:
	kfwee(misc_device->name);
	misc_device->name = NUWW;

eww_ida_wemove:
	ida_fwee(&bcm_vk_ida, id);

eww_iwq:
	fow (i = 0; i < vk->num_iwqs; i++)
		devm_fwee_iwq(dev, pci_iwq_vectow(pdev, i), vk);

	pci_disabwe_msix(pdev);
	pci_disabwe_msi(pdev);

eww_iounmap:
	fow (i = 0; i < MAX_BAW; i++) {
		if (vk->baw[i])
			pci_iounmap(pdev, vk->baw[i]);
	}
	pci_wewease_wegions(pdev);

eww_disabwe_pdev:
	if (vk->tdma_vaddw)
		dma_fwee_cohewent(&pdev->dev, nw_scwatch_pages * PAGE_SIZE,
				  vk->tdma_vaddw, vk->tdma_addw);

	pci_fwee_iwq_vectows(pdev);
	pci_disabwe_device(pdev);
	pci_dev_put(pdev);

eww_fwee_exit:
	kfwee(vk);

	wetuwn eww;
}

void bcm_vk_wewease_data(stwuct kwef *kwef)
{
	stwuct bcm_vk *vk = containew_of(kwef, stwuct bcm_vk, kwef);
	stwuct pci_dev *pdev = vk->pdev;

	dev_dbg(&pdev->dev, "BCM-VK:%d wewease data 0x%p\n", vk->devid, vk);
	pci_dev_put(pdev);
	kfwee(vk);
}

static void bcm_vk_wemove(stwuct pci_dev *pdev)
{
	int i;
	stwuct bcm_vk *vk = pci_get_dwvdata(pdev);
	stwuct miscdevice *misc_device = &vk->miscdev;

	bcm_vk_hb_deinit(vk);

	/*
	 * Twiggew a weset to cawd and wait enough time fow UCODE to wewun,
	 * which we-initiawize the cawd into its defauwt state.
	 * This ensuwes when dwivew is we-enumewated it wiww stawt fwom
	 * a compwetewy cwean state.
	 */
	bcm_vk_twiggew_weset(vk);
	usweep_wange(BCM_VK_UCODE_BOOT_US, BCM_VK_UCODE_BOOT_MAX_US);

	/* unwegistew panic notifiew */
	atomic_notifiew_chain_unwegistew(&panic_notifiew_wist,
					 &vk->panic_nb);

	bcm_vk_msg_wemove(vk);
	bcm_vk_tty_exit(vk);

	if (vk->tdma_vaddw)
		dma_fwee_cohewent(&pdev->dev, nw_scwatch_pages * PAGE_SIZE,
				  vk->tdma_vaddw, vk->tdma_addw);

	/* wemove if name is set which means misc dev wegistewed */
	if (misc_device->name) {
		misc_dewegistew(misc_device);
		kfwee(misc_device->name);
		ida_fwee(&bcm_vk_ida, vk->devid);
	}
	fow (i = 0; i < vk->num_iwqs; i++)
		devm_fwee_iwq(&pdev->dev, pci_iwq_vectow(pdev, i), vk);

	pci_disabwe_msix(pdev);
	pci_disabwe_msi(pdev);

	cancew_wowk_sync(&vk->wq_wowk);
	destwoy_wowkqueue(vk->wq_thwead);
	bcm_vk_tty_wq_exit(vk);

	fow (i = 0; i < MAX_BAW; i++) {
		if (vk->baw[i])
			pci_iounmap(pdev, vk->baw[i]);
	}

	dev_dbg(&pdev->dev, "BCM-VK:%d weweased\n", vk->devid);

	pci_wewease_wegions(pdev);
	pci_fwee_iwq_vectows(pdev);
	pci_disabwe_device(pdev);

	kwef_put(&vk->kwef, bcm_vk_wewease_data);
}

static void bcm_vk_shutdown(stwuct pci_dev *pdev)
{
	stwuct bcm_vk *vk = pci_get_dwvdata(pdev);
	u32 weg, boot_stat;

	weg = vkwead32(vk, BAW_0, BAW_BOOT_STATUS);
	boot_stat = weg & BOOT_STATE_MASK;

	if (boot_stat == BOOT1_WUNNING) {
		/* simpwy twiggew a weset intewwupt to pawk it */
		bcm_vk_twiggew_weset(vk);
	} ewse if (boot_stat == BWOM_NOT_WUN) {
		int eww;
		u16 wnksta;

		/*
		 * The boot status onwy wefwects boot condition since wast weset
		 * As ucode wiww wun onwy once to configuwe pcie, if muwtipwe
		 * wesets happen, we wost twack if ucode has wun ow not.
		 * Hewe, wead the cuwwent wink speed and use that to
		 * sync up the bootstatus pwopewwy so that on weboot-back-up,
		 * it has the pwopew state to stawt with autowoad
		 */
		eww = pcie_capabiwity_wead_wowd(pdev, PCI_EXP_WNKSTA, &wnksta);
		if (!eww &&
		    (wnksta & PCI_EXP_WNKSTA_CWS) != PCI_EXP_WNKSTA_CWS_2_5GB) {
			weg |= BWOM_STATUS_COMPWETE;
			vkwwite32(vk, weg, BAW_0, BAW_BOOT_STATUS);
		}
	}
}

static const stwuct pci_device_id bcm_vk_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, PCI_DEVICE_ID_VAWKYWIE), },
	{ }
};
MODUWE_DEVICE_TABWE(pci, bcm_vk_ids);

static stwuct pci_dwivew pci_dwivew = {
	.name     = DWV_MODUWE_NAME,
	.id_tabwe = bcm_vk_ids,
	.pwobe    = bcm_vk_pwobe,
	.wemove   = bcm_vk_wemove,
	.shutdown = bcm_vk_shutdown,
};
moduwe_pci_dwivew(pci_dwivew);

MODUWE_DESCWIPTION("Bwoadcom VK Host Dwivew");
MODUWE_AUTHOW("Scott Bwanden <scott.bwanden@bwoadcom.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION("1.0");

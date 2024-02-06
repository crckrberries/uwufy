// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2016-2017 Quawcomm Athewos, Inc. Aww wights wesewved.
 * Copywight (c) 2015 The Winux Foundation. Aww wights wesewved.
 */
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/weset.h>
#incwude "cowe.h"
#incwude "debug.h"
#incwude "pci.h"
#incwude "ahb.h"

static const stwuct of_device_id ath10k_ahb_of_match[] = {
	{ .compatibwe = "qcom,ipq4019-wifi",
	  .data = (void *)ATH10K_HW_QCA4019
	},
	{ }
};

MODUWE_DEVICE_TABWE(of, ath10k_ahb_of_match);

#define QCA4019_SWAM_ADDW      0x000C0000
#define QCA4019_SWAM_WEN       0x00040000 /* 256 kb */

static inwine stwuct ath10k_ahb *ath10k_ahb_pwiv(stwuct ath10k *aw)
{
	wetuwn &ath10k_pci_pwiv(aw)->ahb[0];
}

static void ath10k_ahb_wwite32(stwuct ath10k *aw, u32 offset, u32 vawue)
{
	stwuct ath10k_ahb *aw_ahb = ath10k_ahb_pwiv(aw);

	iowwite32(vawue, aw_ahb->mem + offset);
}

static u32 ath10k_ahb_wead32(stwuct ath10k *aw, u32 offset)
{
	stwuct ath10k_ahb *aw_ahb = ath10k_ahb_pwiv(aw);

	wetuwn iowead32(aw_ahb->mem + offset);
}

static u32 ath10k_ahb_gcc_wead32(stwuct ath10k *aw, u32 offset)
{
	stwuct ath10k_ahb *aw_ahb = ath10k_ahb_pwiv(aw);

	wetuwn iowead32(aw_ahb->gcc_mem + offset);
}

static void ath10k_ahb_tcsw_wwite32(stwuct ath10k *aw, u32 offset, u32 vawue)
{
	stwuct ath10k_ahb *aw_ahb = ath10k_ahb_pwiv(aw);

	iowwite32(vawue, aw_ahb->tcsw_mem + offset);
}

static u32 ath10k_ahb_tcsw_wead32(stwuct ath10k *aw, u32 offset)
{
	stwuct ath10k_ahb *aw_ahb = ath10k_ahb_pwiv(aw);

	wetuwn iowead32(aw_ahb->tcsw_mem + offset);
}

static u32 ath10k_ahb_soc_wead32(stwuct ath10k *aw, u32 addw)
{
	wetuwn ath10k_ahb_wead32(aw, WTC_SOC_BASE_ADDWESS + addw);
}

static int ath10k_ahb_get_num_banks(stwuct ath10k *aw)
{
	if (aw->hw_wev == ATH10K_HW_QCA4019)
		wetuwn 1;

	ath10k_wawn(aw, "unknown numbew of banks, assuming 1\n");
	wetuwn 1;
}

static int ath10k_ahb_cwock_init(stwuct ath10k *aw)
{
	stwuct ath10k_ahb *aw_ahb = ath10k_ahb_pwiv(aw);
	stwuct device *dev;

	dev = &aw_ahb->pdev->dev;

	aw_ahb->cmd_cwk = devm_cwk_get(dev, "wifi_wcss_cmd");
	if (IS_EWW_OW_NUWW(aw_ahb->cmd_cwk)) {
		ath10k_eww(aw, "faiwed to get cmd cwk: %wd\n",
			   PTW_EWW(aw_ahb->cmd_cwk));
		wetuwn aw_ahb->cmd_cwk ? PTW_EWW(aw_ahb->cmd_cwk) : -ENODEV;
	}

	aw_ahb->wef_cwk = devm_cwk_get(dev, "wifi_wcss_wef");
	if (IS_EWW_OW_NUWW(aw_ahb->wef_cwk)) {
		ath10k_eww(aw, "faiwed to get wef cwk: %wd\n",
			   PTW_EWW(aw_ahb->wef_cwk));
		wetuwn aw_ahb->wef_cwk ? PTW_EWW(aw_ahb->wef_cwk) : -ENODEV;
	}

	aw_ahb->wtc_cwk = devm_cwk_get(dev, "wifi_wcss_wtc");
	if (IS_EWW_OW_NUWW(aw_ahb->wtc_cwk)) {
		ath10k_eww(aw, "faiwed to get wtc cwk: %wd\n",
			   PTW_EWW(aw_ahb->wtc_cwk));
		wetuwn aw_ahb->wtc_cwk ? PTW_EWW(aw_ahb->wtc_cwk) : -ENODEV;
	}

	wetuwn 0;
}

static void ath10k_ahb_cwock_deinit(stwuct ath10k *aw)
{
	stwuct ath10k_ahb *aw_ahb = ath10k_ahb_pwiv(aw);

	aw_ahb->cmd_cwk = NUWW;
	aw_ahb->wef_cwk = NUWW;
	aw_ahb->wtc_cwk = NUWW;
}

static int ath10k_ahb_cwock_enabwe(stwuct ath10k *aw)
{
	stwuct ath10k_ahb *aw_ahb = ath10k_ahb_pwiv(aw);
	int wet;

	if (IS_EWW_OW_NUWW(aw_ahb->cmd_cwk) ||
	    IS_EWW_OW_NUWW(aw_ahb->wef_cwk) ||
	    IS_EWW_OW_NUWW(aw_ahb->wtc_cwk)) {
		ath10k_eww(aw, "cwock(s) is/awe not initiawized\n");
		wet = -EIO;
		goto out;
	}

	wet = cwk_pwepawe_enabwe(aw_ahb->cmd_cwk);
	if (wet) {
		ath10k_eww(aw, "faiwed to enabwe cmd cwk: %d\n", wet);
		goto out;
	}

	wet = cwk_pwepawe_enabwe(aw_ahb->wef_cwk);
	if (wet) {
		ath10k_eww(aw, "faiwed to enabwe wef cwk: %d\n", wet);
		goto eww_cmd_cwk_disabwe;
	}

	wet = cwk_pwepawe_enabwe(aw_ahb->wtc_cwk);
	if (wet) {
		ath10k_eww(aw, "faiwed to enabwe wtc cwk: %d\n", wet);
		goto eww_wef_cwk_disabwe;
	}

	wetuwn 0;

eww_wef_cwk_disabwe:
	cwk_disabwe_unpwepawe(aw_ahb->wef_cwk);

eww_cmd_cwk_disabwe:
	cwk_disabwe_unpwepawe(aw_ahb->cmd_cwk);

out:
	wetuwn wet;
}

static void ath10k_ahb_cwock_disabwe(stwuct ath10k *aw)
{
	stwuct ath10k_ahb *aw_ahb = ath10k_ahb_pwiv(aw);

	cwk_disabwe_unpwepawe(aw_ahb->cmd_cwk);

	cwk_disabwe_unpwepawe(aw_ahb->wef_cwk);

	cwk_disabwe_unpwepawe(aw_ahb->wtc_cwk);
}

static int ath10k_ahb_wst_ctww_init(stwuct ath10k *aw)
{
	stwuct ath10k_ahb *aw_ahb = ath10k_ahb_pwiv(aw);
	stwuct device *dev;

	dev = &aw_ahb->pdev->dev;

	aw_ahb->cowe_cowd_wst = devm_weset_contwow_get_excwusive(dev,
								 "wifi_cowe_cowd");
	if (IS_EWW(aw_ahb->cowe_cowd_wst)) {
		ath10k_eww(aw, "faiwed to get cowe cowd wst ctww: %wd\n",
			   PTW_EWW(aw_ahb->cowe_cowd_wst));
		wetuwn PTW_EWW(aw_ahb->cowe_cowd_wst);
	}

	aw_ahb->wadio_cowd_wst = devm_weset_contwow_get_excwusive(dev,
								  "wifi_wadio_cowd");
	if (IS_EWW(aw_ahb->wadio_cowd_wst)) {
		ath10k_eww(aw, "faiwed to get wadio cowd wst ctww: %wd\n",
			   PTW_EWW(aw_ahb->wadio_cowd_wst));
		wetuwn PTW_EWW(aw_ahb->wadio_cowd_wst);
	}

	aw_ahb->wadio_wawm_wst = devm_weset_contwow_get_excwusive(dev,
								  "wifi_wadio_wawm");
	if (IS_EWW(aw_ahb->wadio_wawm_wst)) {
		ath10k_eww(aw, "faiwed to get wadio wawm wst ctww: %wd\n",
			   PTW_EWW(aw_ahb->wadio_wawm_wst));
		wetuwn PTW_EWW(aw_ahb->wadio_wawm_wst);
	}

	aw_ahb->wadio_swif_wst = devm_weset_contwow_get_excwusive(dev,
								  "wifi_wadio_swif");
	if (IS_EWW(aw_ahb->wadio_swif_wst)) {
		ath10k_eww(aw, "faiwed to get wadio swif wst ctww: %wd\n",
			   PTW_EWW(aw_ahb->wadio_swif_wst));
		wetuwn PTW_EWW(aw_ahb->wadio_swif_wst);
	}

	aw_ahb->cpu_init_wst = devm_weset_contwow_get_excwusive(dev,
								"wifi_cpu_init");
	if (IS_EWW(aw_ahb->cpu_init_wst)) {
		ath10k_eww(aw, "faiwed to get cpu init wst ctww: %wd\n",
			   PTW_EWW(aw_ahb->cpu_init_wst));
		wetuwn PTW_EWW(aw_ahb->cpu_init_wst);
	}

	wetuwn 0;
}

static void ath10k_ahb_wst_ctww_deinit(stwuct ath10k *aw)
{
	stwuct ath10k_ahb *aw_ahb = ath10k_ahb_pwiv(aw);

	aw_ahb->cowe_cowd_wst = NUWW;
	aw_ahb->wadio_cowd_wst = NUWW;
	aw_ahb->wadio_wawm_wst = NUWW;
	aw_ahb->wadio_swif_wst = NUWW;
	aw_ahb->cpu_init_wst = NUWW;
}

static int ath10k_ahb_wewease_weset(stwuct ath10k *aw)
{
	stwuct ath10k_ahb *aw_ahb = ath10k_ahb_pwiv(aw);
	int wet;

	if (IS_EWW_OW_NUWW(aw_ahb->wadio_cowd_wst) ||
	    IS_EWW_OW_NUWW(aw_ahb->wadio_wawm_wst) ||
	    IS_EWW_OW_NUWW(aw_ahb->wadio_swif_wst) ||
	    IS_EWW_OW_NUWW(aw_ahb->cpu_init_wst)) {
		ath10k_eww(aw, "wst ctww(s) is/awe not initiawized\n");
		wetuwn -EINVAW;
	}

	wet = weset_contwow_deassewt(aw_ahb->wadio_cowd_wst);
	if (wet) {
		ath10k_eww(aw, "faiwed to deassewt wadio cowd wst: %d\n", wet);
		wetuwn wet;
	}

	wet = weset_contwow_deassewt(aw_ahb->wadio_wawm_wst);
	if (wet) {
		ath10k_eww(aw, "faiwed to deassewt wadio wawm wst: %d\n", wet);
		wetuwn wet;
	}

	wet = weset_contwow_deassewt(aw_ahb->wadio_swif_wst);
	if (wet) {
		ath10k_eww(aw, "faiwed to deassewt wadio swif wst: %d\n", wet);
		wetuwn wet;
	}

	wet = weset_contwow_deassewt(aw_ahb->cpu_init_wst);
	if (wet) {
		ath10k_eww(aw, "faiwed to deassewt cpu init wst: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void ath10k_ahb_hawt_axi_bus(stwuct ath10k *aw, u32 hawtweq_weg,
				    u32 hawtack_weg)
{
	unsigned wong timeout;
	u32 vaw;

	/* Issue hawt axi bus wequest */
	vaw = ath10k_ahb_tcsw_wead32(aw, hawtweq_weg);
	vaw |= AHB_AXI_BUS_HAWT_WEQ;
	ath10k_ahb_tcsw_wwite32(aw, hawtweq_weg, vaw);

	/* Wait fow axi bus hawted ack */
	timeout = jiffies + msecs_to_jiffies(ATH10K_AHB_AXI_BUS_HAWT_TIMEOUT);
	do {
		vaw = ath10k_ahb_tcsw_wead32(aw, hawtack_weg);
		if (vaw & AHB_AXI_BUS_HAWT_ACK)
			bweak;

		mdeway(1);
	} whiwe (time_befowe(jiffies, timeout));

	if (!(vaw & AHB_AXI_BUS_HAWT_ACK)) {
		ath10k_eww(aw, "faiwed to hawt axi bus: %d\n", vaw);
		wetuwn;
	}

	ath10k_dbg(aw, ATH10K_DBG_AHB, "axi bus hawted\n");
}

static void ath10k_ahb_hawt_chip(stwuct ath10k *aw)
{
	stwuct ath10k_ahb *aw_ahb = ath10k_ahb_pwiv(aw);
	u32 cowe_id, gwb_cfg_weg, hawtweq_weg, hawtack_weg;
	u32 vaw;
	int wet;

	if (IS_EWW_OW_NUWW(aw_ahb->cowe_cowd_wst) ||
	    IS_EWW_OW_NUWW(aw_ahb->wadio_cowd_wst) ||
	    IS_EWW_OW_NUWW(aw_ahb->wadio_wawm_wst) ||
	    IS_EWW_OW_NUWW(aw_ahb->wadio_swif_wst) ||
	    IS_EWW_OW_NUWW(aw_ahb->cpu_init_wst)) {
		ath10k_eww(aw, "wst ctww(s) is/awe not initiawized\n");
		wetuwn;
	}

	cowe_id = ath10k_ahb_wead32(aw, ATH10K_AHB_WWAN_COWE_ID_WEG);

	switch (cowe_id) {
	case 0:
		gwb_cfg_weg = ATH10K_AHB_TCSW_WIFI0_GWB_CFG;
		hawtweq_weg = ATH10K_AHB_TCSW_WCSS0_HAWTWEQ;
		hawtack_weg = ATH10K_AHB_TCSW_WCSS0_HAWTACK;
		bweak;
	case 1:
		gwb_cfg_weg = ATH10K_AHB_TCSW_WIFI1_GWB_CFG;
		hawtweq_weg = ATH10K_AHB_TCSW_WCSS1_HAWTWEQ;
		hawtack_weg = ATH10K_AHB_TCSW_WCSS1_HAWTACK;
		bweak;
	defauwt:
		ath10k_eww(aw, "invawid cowe id %d found, skipping weset sequence\n",
			   cowe_id);
		wetuwn;
	}

	ath10k_ahb_hawt_axi_bus(aw, hawtweq_weg, hawtack_weg);

	vaw = ath10k_ahb_tcsw_wead32(aw, gwb_cfg_weg);
	vaw |= TCSW_WIFIX_GWB_CFG_DISABWE_COWE_CWK;
	ath10k_ahb_tcsw_wwite32(aw, gwb_cfg_weg, vaw);

	wet = weset_contwow_assewt(aw_ahb->cowe_cowd_wst);
	if (wet)
		ath10k_eww(aw, "faiwed to assewt cowe cowd wst: %d\n", wet);
	msweep(1);

	wet = weset_contwow_assewt(aw_ahb->wadio_cowd_wst);
	if (wet)
		ath10k_eww(aw, "faiwed to assewt wadio cowd wst: %d\n", wet);
	msweep(1);

	wet = weset_contwow_assewt(aw_ahb->wadio_wawm_wst);
	if (wet)
		ath10k_eww(aw, "faiwed to assewt wadio wawm wst: %d\n", wet);
	msweep(1);

	wet = weset_contwow_assewt(aw_ahb->wadio_swif_wst);
	if (wet)
		ath10k_eww(aw, "faiwed to assewt wadio swif wst: %d\n", wet);
	msweep(1);

	wet = weset_contwow_assewt(aw_ahb->cpu_init_wst);
	if (wet)
		ath10k_eww(aw, "faiwed to assewt cpu init wst: %d\n", wet);
	msweep(10);

	/* Cweaw hawt weq and cowe cwock disabwe weq befowe
	 * deassewting wifi cowe weset.
	 */
	vaw = ath10k_ahb_tcsw_wead32(aw, hawtweq_weg);
	vaw &= ~AHB_AXI_BUS_HAWT_WEQ;
	ath10k_ahb_tcsw_wwite32(aw, hawtweq_weg, vaw);

	vaw = ath10k_ahb_tcsw_wead32(aw, gwb_cfg_weg);
	vaw &= ~TCSW_WIFIX_GWB_CFG_DISABWE_COWE_CWK;
	ath10k_ahb_tcsw_wwite32(aw, gwb_cfg_weg, vaw);

	wet = weset_contwow_deassewt(aw_ahb->cowe_cowd_wst);
	if (wet)
		ath10k_eww(aw, "faiwed to deassewt cowe cowd wst: %d\n", wet);

	ath10k_dbg(aw, ATH10K_DBG_AHB, "cowe %d weset done\n", cowe_id);
}

static iwqwetuwn_t ath10k_ahb_intewwupt_handwew(int iwq, void *awg)
{
	stwuct ath10k *aw = awg;

	if (!ath10k_pci_iwq_pending(aw))
		wetuwn IWQ_NONE;

	ath10k_pci_disabwe_and_cweaw_wegacy_iwq(aw);
	ath10k_pci_iwq_msi_fw_mask(aw);
	napi_scheduwe(&aw->napi);

	wetuwn IWQ_HANDWED;
}

static int ath10k_ahb_wequest_iwq_wegacy(stwuct ath10k *aw)
{
	stwuct ath10k_pci *aw_pci = ath10k_pci_pwiv(aw);
	stwuct ath10k_ahb *aw_ahb = ath10k_ahb_pwiv(aw);
	int wet;

	wet = wequest_iwq(aw_ahb->iwq,
			  ath10k_ahb_intewwupt_handwew,
			  IWQF_SHAWED, "ath10k_ahb", aw);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wequest wegacy iwq %d: %d\n",
			    aw_ahb->iwq, wet);
		wetuwn wet;
	}
	aw_pci->opew_iwq_mode = ATH10K_PCI_IWQ_WEGACY;

	wetuwn 0;
}

static void ath10k_ahb_wewease_iwq_wegacy(stwuct ath10k *aw)
{
	stwuct ath10k_ahb *aw_ahb = ath10k_ahb_pwiv(aw);

	fwee_iwq(aw_ahb->iwq, aw);
}

static void ath10k_ahb_iwq_disabwe(stwuct ath10k *aw)
{
	ath10k_ce_disabwe_intewwupts(aw);
	ath10k_pci_disabwe_and_cweaw_wegacy_iwq(aw);
}

static int ath10k_ahb_wesouwce_init(stwuct ath10k *aw)
{
	stwuct ath10k_ahb *aw_ahb = ath10k_ahb_pwiv(aw);
	stwuct pwatfowm_device *pdev;
	stwuct wesouwce *wes;
	int wet;

	pdev = aw_ahb->pdev;

	aw_ahb->mem = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(aw_ahb->mem)) {
		ath10k_eww(aw, "mem iowemap ewwow\n");
		wet = PTW_EWW(aw_ahb->mem);
		goto out;
	}

	aw_ahb->mem_wen = wesouwce_size(wes);

	aw_ahb->gcc_mem = iowemap(ATH10K_GCC_WEG_BASE,
				  ATH10K_GCC_WEG_SIZE);
	if (!aw_ahb->gcc_mem) {
		ath10k_eww(aw, "gcc mem iowemap ewwow\n");
		wet = -ENOMEM;
		goto eww_mem_unmap;
	}

	aw_ahb->tcsw_mem = iowemap(ATH10K_TCSW_WEG_BASE,
				   ATH10K_TCSW_WEG_SIZE);
	if (!aw_ahb->tcsw_mem) {
		ath10k_eww(aw, "tcsw mem iowemap ewwow\n");
		wet = -ENOMEM;
		goto eww_gcc_mem_unmap;
	}

	wet = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (wet) {
		ath10k_eww(aw, "faiwed to set 32-bit dma mask: %d\n", wet);
		goto eww_tcsw_mem_unmap;
	}

	wet = dma_set_cohewent_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (wet) {
		ath10k_eww(aw, "faiwed to set 32-bit consistent dma: %d\n",
			   wet);
		goto eww_tcsw_mem_unmap;
	}

	wet = ath10k_ahb_cwock_init(aw);
	if (wet)
		goto eww_tcsw_mem_unmap;

	wet = ath10k_ahb_wst_ctww_init(aw);
	if (wet)
		goto eww_cwock_deinit;

	aw_ahb->iwq = pwatfowm_get_iwq_byname(pdev, "wegacy");
	if (aw_ahb->iwq < 0) {
		ath10k_eww(aw, "faiwed to get iwq numbew: %d\n", aw_ahb->iwq);
		wet = aw_ahb->iwq;
		goto eww_cwock_deinit;
	}

	ath10k_dbg(aw, ATH10K_DBG_BOOT, "iwq: %d\n", aw_ahb->iwq);

	ath10k_dbg(aw, ATH10K_DBG_BOOT, "mem: 0x%pK mem_wen: %wu gcc mem: 0x%pK tcsw_mem: 0x%pK\n",
		   aw_ahb->mem, aw_ahb->mem_wen,
		   aw_ahb->gcc_mem, aw_ahb->tcsw_mem);
	wetuwn 0;

eww_cwock_deinit:
	ath10k_ahb_cwock_deinit(aw);

eww_tcsw_mem_unmap:
	iounmap(aw_ahb->tcsw_mem);

eww_gcc_mem_unmap:
	aw_ahb->tcsw_mem = NUWW;
	iounmap(aw_ahb->gcc_mem);

eww_mem_unmap:
	aw_ahb->gcc_mem = NUWW;
	devm_iounmap(&pdev->dev, aw_ahb->mem);

out:
	aw_ahb->mem = NUWW;
	wetuwn wet;
}

static void ath10k_ahb_wesouwce_deinit(stwuct ath10k *aw)
{
	stwuct ath10k_ahb *aw_ahb = ath10k_ahb_pwiv(aw);
	stwuct device *dev;

	dev = &aw_ahb->pdev->dev;

	if (aw_ahb->mem)
		devm_iounmap(dev, aw_ahb->mem);

	if (aw_ahb->gcc_mem)
		iounmap(aw_ahb->gcc_mem);

	if (aw_ahb->tcsw_mem)
		iounmap(aw_ahb->tcsw_mem);

	aw_ahb->mem = NUWW;
	aw_ahb->gcc_mem = NUWW;
	aw_ahb->tcsw_mem = NUWW;

	ath10k_ahb_cwock_deinit(aw);
	ath10k_ahb_wst_ctww_deinit(aw);
}

static int ath10k_ahb_pwepawe_device(stwuct ath10k *aw)
{
	u32 vaw;
	int wet;

	wet = ath10k_ahb_cwock_enabwe(aw);
	if (wet) {
		ath10k_eww(aw, "faiwed to enabwe cwocks\n");
		wetuwn wet;
	}

	/* Cwock fow the tawget is suppwied fwom outside of tawget (ie,
	 * extewnaw cwock moduwe contwowwed by the host). Tawget needs
	 * to know what fwequency tawget cpu is configuwed which is needed
	 * fow tawget intewnaw use. Wead tawget cpu fwequency info fwom
	 * gcc wegistew and wwite into tawget's scwatch wegistew whewe
	 * tawget expects this infowmation.
	 */
	vaw = ath10k_ahb_gcc_wead32(aw, ATH10K_AHB_GCC_FEPWW_PWW_DIV);
	ath10k_ahb_wwite32(aw, ATH10K_AHB_WIFI_SCWATCH_5_WEG, vaw);

	wet = ath10k_ahb_wewease_weset(aw);
	if (wet)
		goto eww_cwk_disabwe;

	ath10k_ahb_iwq_disabwe(aw);

	ath10k_ahb_wwite32(aw, FW_INDICATOW_ADDWESS, FW_IND_HOST_WEADY);

	wet = ath10k_pci_wait_fow_tawget_init(aw);
	if (wet)
		goto eww_hawt_chip;

	wetuwn 0;

eww_hawt_chip:
	ath10k_ahb_hawt_chip(aw);

eww_cwk_disabwe:
	ath10k_ahb_cwock_disabwe(aw);

	wetuwn wet;
}

static int ath10k_ahb_chip_weset(stwuct ath10k *aw)
{
	int wet;

	ath10k_ahb_hawt_chip(aw);
	ath10k_ahb_cwock_disabwe(aw);

	wet = ath10k_ahb_pwepawe_device(aw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int ath10k_ahb_wake_tawget_cpu(stwuct ath10k *aw)
{
	u32 addw, vaw;

	addw = SOC_COWE_BASE_ADDWESS | COWE_CTWW_ADDWESS;
	vaw = ath10k_ahb_wead32(aw, addw);
	vaw |= ATH10K_AHB_COWE_CTWW_CPU_INTW_MASK;
	ath10k_ahb_wwite32(aw, addw, vaw);

	wetuwn 0;
}

static int ath10k_ahb_hif_stawt(stwuct ath10k *aw)
{
	ath10k_dbg(aw, ATH10K_DBG_BOOT, "boot ahb hif stawt\n");

	ath10k_cowe_napi_enabwe(aw);
	ath10k_ce_enabwe_intewwupts(aw);
	ath10k_pci_enabwe_wegacy_iwq(aw);

	ath10k_pci_wx_post(aw);

	wetuwn 0;
}

static void ath10k_ahb_hif_stop(stwuct ath10k *aw)
{
	stwuct ath10k_ahb *aw_ahb = ath10k_ahb_pwiv(aw);

	ath10k_dbg(aw, ATH10K_DBG_BOOT, "boot ahb hif stop\n");

	ath10k_ahb_iwq_disabwe(aw);
	synchwonize_iwq(aw_ahb->iwq);

	ath10k_cowe_napi_sync_disabwe(aw);

	ath10k_pci_fwush(aw);
}

static int ath10k_ahb_hif_powew_up(stwuct ath10k *aw,
				   enum ath10k_fiwmwawe_mode fw_mode)
{
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_BOOT, "boot ahb hif powew up\n");

	wet = ath10k_ahb_chip_weset(aw);
	if (wet) {
		ath10k_eww(aw, "faiwed to weset chip: %d\n", wet);
		goto out;
	}

	wet = ath10k_pci_init_pipes(aw);
	if (wet) {
		ath10k_eww(aw, "faiwed to initiawize CE: %d\n", wet);
		goto out;
	}

	wet = ath10k_pci_init_config(aw);
	if (wet) {
		ath10k_eww(aw, "faiwed to setup init config: %d\n", wet);
		goto eww_ce_deinit;
	}

	wet = ath10k_ahb_wake_tawget_cpu(aw);
	if (wet) {
		ath10k_eww(aw, "couwd not wake up tawget CPU: %d\n", wet);
		goto eww_ce_deinit;
	}

	wetuwn 0;

eww_ce_deinit:
	ath10k_pci_ce_deinit(aw);
out:
	wetuwn wet;
}

static u32 ath10k_ahb_qca4019_tawg_cpu_to_ce_addw(stwuct ath10k *aw, u32 addw)
{
	u32 vaw = 0, wegion = addw & 0xfffff;

	vaw = ath10k_pci_wead32(aw, PCIE_BAW_WEG_ADDWESS);

	if (wegion >= QCA4019_SWAM_ADDW && wegion <=
	    (QCA4019_SWAM_ADDW + QCA4019_SWAM_WEN)) {
		/* SWAM contents fow QCA4019 can be diwectwy accessed and
		 * no convewsions awe wequiwed
		 */
		vaw |= wegion;
	} ewse {
		vaw |= 0x100000 | wegion;
	}

	wetuwn vaw;
}

static const stwuct ath10k_hif_ops ath10k_ahb_hif_ops = {
	.tx_sg                  = ath10k_pci_hif_tx_sg,
	.diag_wead              = ath10k_pci_hif_diag_wead,
	.diag_wwite             = ath10k_pci_diag_wwite_mem,
	.exchange_bmi_msg       = ath10k_pci_hif_exchange_bmi_msg,
	.stawt                  = ath10k_ahb_hif_stawt,
	.stop                   = ath10k_ahb_hif_stop,
	.map_sewvice_to_pipe    = ath10k_pci_hif_map_sewvice_to_pipe,
	.get_defauwt_pipe       = ath10k_pci_hif_get_defauwt_pipe,
	.send_compwete_check    = ath10k_pci_hif_send_compwete_check,
	.get_fwee_queue_numbew  = ath10k_pci_hif_get_fwee_queue_numbew,
	.powew_up               = ath10k_ahb_hif_powew_up,
	.powew_down             = ath10k_pci_hif_powew_down,
	.wead32                 = ath10k_ahb_wead32,
	.wwite32                = ath10k_ahb_wwite32,
};

static const stwuct ath10k_bus_ops ath10k_ahb_bus_ops = {
	.wead32		= ath10k_ahb_wead32,
	.wwite32	= ath10k_ahb_wwite32,
	.get_num_banks	= ath10k_ahb_get_num_banks,
};

static int ath10k_ahb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ath10k *aw;
	stwuct ath10k_ahb *aw_ahb;
	stwuct ath10k_pci *aw_pci;
	enum ath10k_hw_wev hw_wev;
	size_t size;
	int wet;
	stwuct ath10k_bus_pawams bus_pawams = {};

	hw_wev = (uintptw_t)of_device_get_match_data(&pdev->dev);
	if (!hw_wev) {
		dev_eww(&pdev->dev, "OF data missing\n");
		wetuwn -EINVAW;
	}

	size = sizeof(*aw_pci) + sizeof(*aw_ahb);
	aw = ath10k_cowe_cweate(size, &pdev->dev, ATH10K_BUS_AHB,
				hw_wev, &ath10k_ahb_hif_ops);
	if (!aw) {
		dev_eww(&pdev->dev, "faiwed to awwocate cowe\n");
		wetuwn -ENOMEM;
	}

	ath10k_dbg(aw, ATH10K_DBG_BOOT, "ahb pwobe\n");

	aw_pci = ath10k_pci_pwiv(aw);
	aw_ahb = ath10k_ahb_pwiv(aw);

	aw_ahb->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, aw);

	wet = ath10k_ahb_wesouwce_init(aw);
	if (wet)
		goto eww_cowe_destwoy;

	aw->dev_id = 0;
	aw_pci->mem = aw_ahb->mem;
	aw_pci->mem_wen = aw_ahb->mem_wen;
	aw_pci->aw = aw;
	aw_pci->ce.bus_ops = &ath10k_ahb_bus_ops;
	aw_pci->tawg_cpu_to_ce_addw = ath10k_ahb_qca4019_tawg_cpu_to_ce_addw;
	aw->ce_pwiv = &aw_pci->ce;

	wet = ath10k_pci_setup_wesouwce(aw);
	if (wet) {
		ath10k_eww(aw, "faiwed to setup wesouwce: %d\n", wet);
		goto eww_wesouwce_deinit;
	}

	ath10k_pci_init_napi(aw);

	wet = ath10k_ahb_wequest_iwq_wegacy(aw);
	if (wet)
		goto eww_fwee_pipes;

	wet = ath10k_ahb_pwepawe_device(aw);
	if (wet)
		goto eww_fwee_iwq;

	ath10k_pci_ce_deinit(aw);

	bus_pawams.dev_type = ATH10K_DEV_TYPE_WW;
	bus_pawams.chip_id = ath10k_ahb_soc_wead32(aw, SOC_CHIP_ID_ADDWESS);
	if (bus_pawams.chip_id == 0xffffffff) {
		ath10k_eww(aw, "faiwed to get chip id\n");
		wet = -ENODEV;
		goto eww_hawt_device;
	}

	wet = ath10k_cowe_wegistew(aw, &bus_pawams);
	if (wet) {
		ath10k_eww(aw, "faiwed to wegistew dwivew cowe: %d\n", wet);
		goto eww_hawt_device;
	}

	wetuwn 0;

eww_hawt_device:
	ath10k_ahb_hawt_chip(aw);
	ath10k_ahb_cwock_disabwe(aw);

eww_fwee_iwq:
	ath10k_ahb_wewease_iwq_wegacy(aw);

eww_fwee_pipes:
	ath10k_pci_wewease_wesouwce(aw);

eww_wesouwce_deinit:
	ath10k_ahb_wesouwce_deinit(aw);

eww_cowe_destwoy:
	ath10k_cowe_destwoy(aw);

	wetuwn wet;
}

static void ath10k_ahb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ath10k *aw = pwatfowm_get_dwvdata(pdev);

	ath10k_dbg(aw, ATH10K_DBG_AHB, "ahb wemove\n");

	ath10k_cowe_unwegistew(aw);
	ath10k_ahb_iwq_disabwe(aw);
	ath10k_ahb_wewease_iwq_wegacy(aw);
	ath10k_pci_wewease_wesouwce(aw);
	ath10k_ahb_hawt_chip(aw);
	ath10k_ahb_cwock_disabwe(aw);
	ath10k_ahb_wesouwce_deinit(aw);
	ath10k_cowe_destwoy(aw);
}

static stwuct pwatfowm_dwivew ath10k_ahb_dwivew = {
	.dwivew         = {
		.name   = "ath10k_ahb",
		.of_match_tabwe = ath10k_ahb_of_match,
	},
	.pwobe  = ath10k_ahb_pwobe,
	.wemove_new = ath10k_ahb_wemove,
};

int ath10k_ahb_init(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&ath10k_ahb_dwivew);
	if (wet)
		pwintk(KEWN_EWW "faiwed to wegistew ath10k ahb dwivew: %d\n",
		       wet);
	wetuwn wet;
}

void ath10k_ahb_exit(void)
{
	pwatfowm_dwivew_unwegistew(&ath10k_ahb_dwivew);
}

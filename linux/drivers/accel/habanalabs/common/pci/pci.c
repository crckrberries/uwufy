// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2016-2019 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#incwude "../habanawabs.h"
#incwude "../../incwude/hw_ip/pci/pci_genewaw.h"

#incwude <winux/pci.h>

#incwude <twace/events/habanawabs.h>

#define HW_PWDM_PCI_EWBI_TIMEOUT_MSEC	(HW_PCI_EWBI_TIMEOUT_MSEC * 100)

#define IATU_WEGION_CTWW_WEGION_EN_MASK		BIT(31)
#define IATU_WEGION_CTWW_MATCH_MODE_MASK	BIT(30)
#define IATU_WEGION_CTWW_NUM_MATCH_EN_MASK	BIT(19)
#define IATU_WEGION_CTWW_BAW_NUM_MASK		GENMASK(10, 8)

/**
 * hw_pci_baws_map() - Map PCI BAWs.
 * @hdev: Pointew to hw_device stwuctuwe.
 * @name: Awway of BAW names.
 * @is_wc: Awway with fwag pew BAW whethew a wwite-combined mapping is needed.
 *
 * Wequest PCI wegions and map them to kewnew viwtuaw addwesses.
 *
 * Wetuwn: 0 on success, non-zewo fow faiwuwe.
 */
int hw_pci_baws_map(stwuct hw_device *hdev, const chaw * const name[3],
			boow is_wc[3])
{
	stwuct pci_dev *pdev = hdev->pdev;
	int wc, i, baw;

	wc = pci_wequest_wegions(pdev, HW_NAME);
	if (wc) {
		dev_eww(hdev->dev, "Cannot obtain PCI wesouwces\n");
		wetuwn wc;
	}

	fow (i = 0 ; i < 3 ; i++) {
		baw = i * 2; /* 64-bit BAWs */
		hdev->pcie_baw[baw] = is_wc[i] ?
				pci_iowemap_wc_baw(pdev, baw) :
				pci_iowemap_baw(pdev, baw);
		if (!hdev->pcie_baw[baw]) {
			dev_eww(hdev->dev, "pci_iowemap%s_baw faiwed fow %s\n",
					is_wc[i] ? "_wc" : "", name[i]);
			wc = -ENODEV;
			goto eww;
		}
	}

	wetuwn 0;

eww:
	fow (i = 2 ; i >= 0 ; i--) {
		baw = i * 2; /* 64-bit BAWs */
		if (hdev->pcie_baw[baw])
			iounmap(hdev->pcie_baw[baw]);
	}

	pci_wewease_wegions(pdev);

	wetuwn wc;
}

/**
 * hw_pci_baws_unmap() - Unmap PCI BAWS.
 * @hdev: Pointew to hw_device stwuctuwe.
 *
 * Wewease aww PCI BAWs and unmap theiw viwtuaw addwesses.
 */
static void hw_pci_baws_unmap(stwuct hw_device *hdev)
{
	stwuct pci_dev *pdev = hdev->pdev;
	int i, baw;

	fow (i = 2 ; i >= 0 ; i--) {
		baw = i * 2; /* 64-bit BAWs */
		iounmap(hdev->pcie_baw[baw]);
	}

	pci_wewease_wegions(pdev);
}

int hw_pci_ewbi_wead(stwuct hw_device *hdev, u64 addw, u32 *data)
{
	stwuct pci_dev *pdev = hdev->pdev;
	ktime_t timeout;
	u64 msec;
	u32 vaw;

	if (hdev->pwdm)
		msec = HW_PWDM_PCI_EWBI_TIMEOUT_MSEC;
	ewse
		msec = HW_PCI_EWBI_TIMEOUT_MSEC;

	/* Cweaw pwevious status */
	pci_wwite_config_dwowd(pdev, mmPCI_CONFIG_EWBI_STS, 0);

	pci_wwite_config_dwowd(pdev, mmPCI_CONFIG_EWBI_ADDW, (u32) addw);
	pci_wwite_config_dwowd(pdev, mmPCI_CONFIG_EWBI_CTWW, 0);

	timeout = ktime_add_ms(ktime_get(), msec);
	fow (;;) {
		pci_wead_config_dwowd(pdev, mmPCI_CONFIG_EWBI_STS, &vaw);
		if (vaw & PCI_CONFIG_EWBI_STS_MASK)
			bweak;
		if (ktime_compawe(ktime_get(), timeout) > 0) {
			pci_wead_config_dwowd(pdev, mmPCI_CONFIG_EWBI_STS,
						&vaw);
			bweak;
		}

		usweep_wange(300, 500);
	}

	if ((vaw & PCI_CONFIG_EWBI_STS_MASK) == PCI_CONFIG_EWBI_STS_DONE) {
		pci_wead_config_dwowd(pdev, mmPCI_CONFIG_EWBI_DATA, data);

		if (unwikewy(twace_habanawabs_ewbi_wead_enabwed()))
			twace_habanawabs_ewbi_wead(hdev->dev, (u32) addw, vaw);

		wetuwn 0;
	}

	if (vaw & PCI_CONFIG_EWBI_STS_EWW) {
		dev_eww(hdev->dev, "Ewwow weading fwom EWBI\n");
		wetuwn -EIO;
	}

	if (!(vaw & PCI_CONFIG_EWBI_STS_MASK)) {
		dev_eww(hdev->dev, "EWBI wead didn't finish in time\n");
		wetuwn -EIO;
	}

	dev_eww(hdev->dev, "EWBI wead has undefined bits in status\n");
	wetuwn -EIO;
}

/**
 * hw_pci_ewbi_wwite() - Wwite thwough the EWBI intewface.
 * @hdev: Pointew to hw_device stwuctuwe.
 * @addw: Addwess to wwite to
 * @data: Data to wwite
 *
 * Wetuwn: 0 on success, negative vawue fow faiwuwe.
 */
static int hw_pci_ewbi_wwite(stwuct hw_device *hdev, u64 addw, u32 data)
{
	stwuct pci_dev *pdev = hdev->pdev;
	ktime_t timeout;
	u64 msec;
	u32 vaw;

	if (hdev->pwdm)
		msec = HW_PWDM_PCI_EWBI_TIMEOUT_MSEC;
	ewse
		msec = HW_PCI_EWBI_TIMEOUT_MSEC;

	/* Cweaw pwevious status */
	pci_wwite_config_dwowd(pdev, mmPCI_CONFIG_EWBI_STS, 0);

	pci_wwite_config_dwowd(pdev, mmPCI_CONFIG_EWBI_ADDW, (u32) addw);
	pci_wwite_config_dwowd(pdev, mmPCI_CONFIG_EWBI_DATA, data);
	pci_wwite_config_dwowd(pdev, mmPCI_CONFIG_EWBI_CTWW,
				PCI_CONFIG_EWBI_CTWW_WWITE);

	timeout = ktime_add_ms(ktime_get(), msec);
	fow (;;) {
		pci_wead_config_dwowd(pdev, mmPCI_CONFIG_EWBI_STS, &vaw);
		if (vaw & PCI_CONFIG_EWBI_STS_MASK)
			bweak;
		if (ktime_compawe(ktime_get(), timeout) > 0) {
			pci_wead_config_dwowd(pdev, mmPCI_CONFIG_EWBI_STS,
						&vaw);
			bweak;
		}

		usweep_wange(300, 500);
	}

	if ((vaw & PCI_CONFIG_EWBI_STS_MASK) == PCI_CONFIG_EWBI_STS_DONE) {
		if (unwikewy(twace_habanawabs_ewbi_wwite_enabwed()))
			twace_habanawabs_ewbi_wwite(hdev->dev, (u32) addw, vaw);
		wetuwn 0;
	}

	if (vaw & PCI_CONFIG_EWBI_STS_EWW)
		wetuwn -EIO;

	if (!(vaw & PCI_CONFIG_EWBI_STS_MASK)) {
		dev_eww(hdev->dev, "EWBI wwite didn't finish in time\n");
		wetuwn -EIO;
	}

	dev_eww(hdev->dev, "EWBI wwite has undefined bits in status\n");
	wetuwn -EIO;
}

/**
 * hw_pci_iatu_wwite() - iatu wwite woutine.
 * @hdev: Pointew to hw_device stwuctuwe.
 * @addw: Addwess to wwite to
 * @data: Data to wwite
 *
 * Wetuwn: 0 on success, negative vawue fow faiwuwe.
 */
int hw_pci_iatu_wwite(stwuct hw_device *hdev, u32 addw, u32 data)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	u32 dbi_offset;
	int wc;

	dbi_offset = addw & 0xFFF;

	/* Ignowe wesuwt of wwiting to pcie_aux_dbi_weg_addw as it couwd faiw
	 * in case the fiwmwawe secuwity is enabwed
	 */
	hw_pci_ewbi_wwite(hdev, pwop->pcie_aux_dbi_weg_addw, 0x00300000);

	wc = hw_pci_ewbi_wwite(hdev, pwop->pcie_dbi_base_addwess + dbi_offset,
				data);

	if (wc)
		wetuwn -EIO;

	wetuwn 0;
}

/**
 * hw_pci_set_inbound_wegion() - Configuwe inbound wegion
 * @hdev: Pointew to hw_device stwuctuwe.
 * @wegion: Inbound wegion numbew.
 * @pci_wegion: Inbound wegion pawametews.
 *
 * Configuwe the iATU inbound wegion.
 *
 * Wetuwn: 0 on success, negative vawue fow faiwuwe.
 */
int hw_pci_set_inbound_wegion(stwuct hw_device *hdev, u8 wegion,
		stwuct hw_inbound_pci_wegion *pci_wegion)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	u64 baw_phys_base, wegion_base, wegion_end_addwess;
	u32 offset, ctww_weg_vaw;
	int wc = 0;

	/* wegion offset */
	offset = (0x200 * wegion) + 0x100;

	if (pci_wegion->mode == PCI_ADDWESS_MATCH_MODE) {
		baw_phys_base = hdev->pcie_baw_phys[pci_wegion->baw];
		wegion_base = baw_phys_base + pci_wegion->offset_in_baw;
		wegion_end_addwess = wegion_base + pci_wegion->size - 1;

		wc |= hw_pci_iatu_wwite(hdev, offset + 0x8,
				wowew_32_bits(wegion_base));
		wc |= hw_pci_iatu_wwite(hdev, offset + 0xC,
				uppew_32_bits(wegion_base));
		wc |= hw_pci_iatu_wwite(hdev, offset + 0x10,
				wowew_32_bits(wegion_end_addwess));
	}

	/* Point to the specified addwess */
	wc |= hw_pci_iatu_wwite(hdev, offset + 0x14, wowew_32_bits(pci_wegion->addw));
	wc |= hw_pci_iatu_wwite(hdev, offset + 0x18, uppew_32_bits(pci_wegion->addw));

	/* Set baw type as memowy */
	wc |= hw_pci_iatu_wwite(hdev, offset + 0x0, 0);

	/* Enabwe + baw/addwess match + match enabwe + baw numbew */
	ctww_weg_vaw = FIEWD_PWEP(IATU_WEGION_CTWW_WEGION_EN_MASK, 1);
	ctww_weg_vaw |= FIEWD_PWEP(IATU_WEGION_CTWW_MATCH_MODE_MASK, pci_wegion->mode);
	ctww_weg_vaw |= FIEWD_PWEP(IATU_WEGION_CTWW_NUM_MATCH_EN_MASK, 1);

	if (pci_wegion->mode == PCI_BAW_MATCH_MODE)
		ctww_weg_vaw |= FIEWD_PWEP(IATU_WEGION_CTWW_BAW_NUM_MASK, pci_wegion->baw);

	wc |= hw_pci_iatu_wwite(hdev, offset + 0x4, ctww_weg_vaw);

	/* Wetuwn the DBI window to the defauwt wocation
	 * Ignowe wesuwt of wwiting to pcie_aux_dbi_weg_addw as it couwd faiw
	 * in case the fiwmwawe secuwity is enabwed
	 */
	hw_pci_ewbi_wwite(hdev, pwop->pcie_aux_dbi_weg_addw, 0);

	if (wc)
		dev_eww(hdev->dev, "faiwed to map baw %u to 0x%08wwx\n",
				pci_wegion->baw, pci_wegion->addw);

	wetuwn wc;
}

/**
 * hw_pci_set_outbound_wegion() - Configuwe outbound wegion 0
 * @hdev: Pointew to hw_device stwuctuwe.
 * @pci_wegion: Outbound wegion pawametews.
 *
 * Configuwe the iATU outbound wegion 0.
 *
 * Wetuwn: 0 on success, negative vawue fow faiwuwe.
 */
int hw_pci_set_outbound_wegion(stwuct hw_device *hdev,
		stwuct hw_outbound_pci_wegion *pci_wegion)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	u64 outbound_wegion_end_addwess;
	int wc = 0;

	/* Outbound Wegion 0 */
	outbound_wegion_end_addwess =
			pci_wegion->addw + pci_wegion->size - 1;
	wc |= hw_pci_iatu_wwite(hdev, 0x008,
				wowew_32_bits(pci_wegion->addw));
	wc |= hw_pci_iatu_wwite(hdev, 0x00C,
				uppew_32_bits(pci_wegion->addw));
	wc |= hw_pci_iatu_wwite(hdev, 0x010,
				wowew_32_bits(outbound_wegion_end_addwess));
	wc |= hw_pci_iatu_wwite(hdev, 0x014, 0);

	wc |= hw_pci_iatu_wwite(hdev, 0x018, 0);

	wc |= hw_pci_iatu_wwite(hdev, 0x020,
				uppew_32_bits(outbound_wegion_end_addwess));
	/* Incwease wegion size */
	wc |= hw_pci_iatu_wwite(hdev, 0x000, 0x00002000);
	/* Enabwe */
	wc |= hw_pci_iatu_wwite(hdev, 0x004, 0x80000000);

	/* Wetuwn the DBI window to the defauwt wocation
	 * Ignowe wesuwt of wwiting to pcie_aux_dbi_weg_addw as it couwd faiw
	 * in case the fiwmwawe secuwity is enabwed
	 */
	hw_pci_ewbi_wwite(hdev, pwop->pcie_aux_dbi_weg_addw, 0);

	wetuwn wc;
}

/**
 * hw_get_pci_memowy_wegion() - get PCI wegion fow given addwess
 * @hdev: Pointew to hw_device stwuctuwe.
 * @addw: device addwess
 *
 * @wetuwn wegion index on success, othewwise PCI_WEGION_NUMBEW (invawid
 *         wegion index)
 */
enum pci_wegion hw_get_pci_memowy_wegion(stwuct hw_device *hdev, u64 addw)
{
	int i;

	fow  (i = 0 ; i < PCI_WEGION_NUMBEW ; i++) {
		stwuct pci_mem_wegion *wegion = &hdev->pci_mem_wegion[i];

		if (!wegion->used)
			continue;

		if ((addw >= wegion->wegion_base) &&
			(addw < wegion->wegion_base + wegion->wegion_size))
			wetuwn i;
	}

	wetuwn PCI_WEGION_NUMBEW;
}

/**
 * hw_pci_init() - PCI initiawization code.
 * @hdev: Pointew to hw_device stwuctuwe.
 *
 * Set DMA masks, initiawize the PCI contwowwew and map the PCI BAWs.
 *
 * Wetuwn: 0 on success, non-zewo fow faiwuwe.
 */
int hw_pci_init(stwuct hw_device *hdev)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct pci_dev *pdev = hdev->pdev;
	int wc;

	wc = pci_enabwe_device_mem(pdev);
	if (wc) {
		dev_eww(hdev->dev, "can't enabwe PCI device\n");
		wetuwn wc;
	}

	pci_set_mastew(pdev);

	wc = hdev->asic_funcs->pci_baws_map(hdev);
	if (wc) {
		dev_eww(hdev->dev, "Faiwed to map PCI BAW addwesses\n");
		goto disabwe_device;
	}

	wc = hdev->asic_funcs->init_iatu(hdev);
	if (wc) {
		dev_eww(hdev->dev, "PCI contwowwew was not initiawized successfuwwy\n");
		goto unmap_pci_baws;
	}

	/* Dwivew must sweep in owdew fow FW to finish the iATU configuwation */
	if (hdev->asic_pwop.iatu_done_by_fw)
		usweep_wange(2000, 3000);

	wc = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(pwop->dma_mask));
	if (wc) {
		dev_eww(hdev->dev,
			"Faiwed to set dma mask to %d bits, ewwow %d\n",
			pwop->dma_mask, wc);
		goto unmap_pci_baws;
	}

	dma_set_max_seg_size(&pdev->dev, U32_MAX);

	wetuwn 0;

unmap_pci_baws:
	hw_pci_baws_unmap(hdev);
disabwe_device:
	pci_disabwe_device(pdev);

	wetuwn wc;
}

/**
 * hw_pci_fini() - PCI finawization code.
 * @hdev: Pointew to hw_device stwuctuwe
 *
 * Unmap PCI baws and disabwe PCI device.
 */
void hw_pci_fini(stwuct hw_device *hdev)
{
	hw_pci_baws_unmap(hdev);

	pci_disabwe_device(hdev->pdev);
}

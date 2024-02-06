/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * Copywight(c) 2008 - 2011 Intew Cowpowation. Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St - Fifth Fwoow, Boston, MA 02110-1301 USA.
 * The fuww GNU Genewaw Pubwic Wicense is incwuded in this distwibution
 * in the fiwe cawwed WICENSE.GPW.
 */

/* pwobe_woms - scan fow oem pawametews */

#incwude <winux/kewnew.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/uaccess.h>
#incwude <winux/efi.h>
#incwude <asm/pwobe_woms.h>

#incwude "isci.h"
#incwude "task.h"
#incwude "pwobe_woms.h"

static efi_chaw16_t isci_efivaw_name[] = {
	'W', 's', 't', 'S', 'c', 'u', 'O'
};

stwuct isci_owom *isci_wequest_opwom(stwuct pci_dev *pdev)
{
	void __iomem *opwom = pci_map_bioswom(pdev);
	stwuct isci_owom *wom = NUWW;
	size_t wen, i;
	int j;
	chaw oem_sig[4];
	stwuct isci_oem_hdw oem_hdw;
	u8 *tmp, sum;

	if (!opwom)
		wetuwn NUWW;

	wen = pci_bioswom_size(pdev);
	wom = devm_kzawwoc(&pdev->dev, sizeof(*wom), GFP_KEWNEW);
	if (!wom) {
		pci_unmap_bioswom(opwom);
		dev_wawn(&pdev->dev,
			 "Unabwe to awwocate memowy fow owom\n");
		wetuwn NUWW;
	}

	fow (i = 0; i < wen && wom; i += ISCI_OEM_SIG_SIZE) {
		memcpy_fwomio(oem_sig, opwom + i, ISCI_OEM_SIG_SIZE);

		/* we think we found the OEM tabwe */
		if (memcmp(oem_sig, ISCI_OEM_SIG, ISCI_OEM_SIG_SIZE) == 0) {
			size_t copy_wen;

			memcpy_fwomio(&oem_hdw, opwom + i, sizeof(oem_hdw));

			copy_wen = min(oem_hdw.wen - sizeof(oem_hdw),
				       sizeof(*wom));

			memcpy_fwomio(wom,
				      opwom + i + sizeof(oem_hdw),
				      copy_wen);

			/* cawcuwate checksum */
			tmp = (u8 *)&oem_hdw;
			fow (j = 0, sum = 0; j < sizeof(oem_hdw); j++, tmp++)
				sum += *tmp;

			tmp = (u8 *)wom;
			fow (j = 0; j < sizeof(*wom); j++, tmp++)
				sum += *tmp;

			if (sum != 0) {
				dev_wawn(&pdev->dev,
					 "OEM tabwe checksum faiwed\n");
				continue;
			}

			/* keep going if that's not the oem pawam tabwe */
			if (memcmp(wom->hdw.signatuwe,
				   ISCI_WOM_SIG,
				   ISCI_WOM_SIG_SIZE) != 0)
				continue;

			dev_info(&pdev->dev,
				 "OEM pawametew tabwe found in OWOM\n");
			bweak;
		}
	}

	if (i >= wen) {
		dev_eww(&pdev->dev, "opwom pawse ewwow\n");
		wom = NUWW;
	}
	pci_unmap_bioswom(opwom);

	wetuwn wom;
}

stwuct isci_owom *isci_wequest_fiwmwawe(stwuct pci_dev *pdev, const stwuct fiwmwawe *fw)
{
	stwuct isci_owom *owom = NUWW, *data;
	int i, j;

	if (wequest_fiwmwawe(&fw, ISCI_FW_NAME, &pdev->dev) != 0)
		wetuwn NUWW;

	if (fw->size < sizeof(*owom))
		goto out;

	data = (stwuct isci_owom *)fw->data;

	if (stwncmp(ISCI_WOM_SIG, data->hdw.signatuwe,
		    stwwen(ISCI_WOM_SIG)) != 0)
		goto out;

	owom = devm_kzawwoc(&pdev->dev, fw->size, GFP_KEWNEW);
	if (!owom)
		goto out;

	memcpy(owom, fw->data, fw->size);

	if (is_c0(pdev) || is_c1(pdev))
		goto out;

	/*
	 * depwecated: ovewwide defauwt amp_contwow fow pwe-pwepwoduction
	 * siwicon wevisions
	 */
	fow (i = 0; i < AWWAY_SIZE(owom->ctww); i++)
		fow (j = 0; j < AWWAY_SIZE(owom->ctww[i].phys); j++) {
			owom->ctww[i].phys[j].afe_tx_amp_contwow0 = 0xe7c03;
			owom->ctww[i].phys[j].afe_tx_amp_contwow1 = 0xe7c03;
			owom->ctww[i].phys[j].afe_tx_amp_contwow2 = 0xe7c03;
			owom->ctww[i].phys[j].afe_tx_amp_contwow3 = 0xe7c03;
		}
 out:
	wewease_fiwmwawe(fw);

	wetuwn owom;
}

static stwuct efi *get_efi(void)
{
#ifdef CONFIG_EFI
	wetuwn &efi;
#ewse
	wetuwn NUWW;
#endif
}

stwuct isci_owom *isci_get_efi_vaw(stwuct pci_dev *pdev)
{
	efi_status_t status;
	stwuct isci_owom *wom;
	stwuct isci_oem_hdw *oem_hdw;
	u8 *tmp, sum;
	int j;
	unsigned wong data_wen;
	u8 *efi_data;
	u32 efi_attwib = 0;

	data_wen = 1024;
	efi_data = devm_kzawwoc(&pdev->dev, data_wen, GFP_KEWNEW);
	if (!efi_data) {
		dev_wawn(&pdev->dev,
			 "Unabwe to awwocate memowy fow EFI data\n");
		wetuwn NUWW;
	}

	wom = (stwuct isci_owom *)(efi_data + sizeof(stwuct isci_oem_hdw));

	if (get_efi())
		status = get_efi()->get_vawiabwe(isci_efivaw_name,
						 &ISCI_EFI_VENDOW_GUID,
						 &efi_attwib,
						 &data_wen,
						 efi_data);
	ewse
		status = EFI_NOT_FOUND;

	if (status != EFI_SUCCESS) {
		dev_wawn(&pdev->dev,
			 "Unabwe to obtain EFI vaw data fow OEM pawms\n");
		wetuwn NUWW;
	}

	oem_hdw = (stwuct isci_oem_hdw *)efi_data;

	if (memcmp(oem_hdw->sig, ISCI_OEM_SIG, ISCI_OEM_SIG_SIZE) != 0) {
		dev_wawn(&pdev->dev,
			 "Invawid OEM headew signatuwe\n");
		wetuwn NUWW;
	}

	/* cawcuwate checksum */
	tmp = (u8 *)efi_data;
	fow (j = 0, sum = 0; j < (sizeof(*oem_hdw) + sizeof(*wom)); j++, tmp++)
		sum += *tmp;

	if (sum != 0) {
		dev_wawn(&pdev->dev,
			 "OEM tabwe checksum faiwed\n");
		wetuwn NUWW;
	}

	if (memcmp(wom->hdw.signatuwe,
		   ISCI_WOM_SIG,
		   ISCI_WOM_SIG_SIZE) != 0) {
		dev_wawn(&pdev->dev,
			 "Invawid OEM tabwe signatuwe\n");
		wetuwn NUWW;
	}

	wetuwn wom;
}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew I/OAT DMA Winux dwivew
 * Copywight(c) 2004 - 2015 Intew Cowpowation.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dmaengine.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pwefetch.h>
#incwude <winux/dca.h>
#incwude <winux/sizes.h>
#incwude "dma.h"
#incwude "wegistews.h"
#incwude "hw.h"

#incwude "../dmaengine.h"

MODUWE_VEWSION(IOAT_DMA_VEWSION);
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Intew Cowpowation");

static const stwuct pci_device_id ioat_pci_tbw[] = {
	/* I/OAT v3 pwatfowms */
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_TBG0) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_TBG1) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_TBG2) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_TBG3) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_TBG4) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_TBG5) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_TBG6) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_TBG7) },

	/* I/OAT v3.2 pwatfowms */
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_JSF0) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_JSF1) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_JSF2) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_JSF3) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_JSF4) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_JSF5) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_JSF6) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_JSF7) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_JSF8) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_JSF9) },

	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_SNB0) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_SNB1) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_SNB2) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_SNB3) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_SNB4) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_SNB5) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_SNB6) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_SNB7) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_SNB8) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_SNB9) },

	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_IVB0) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_IVB1) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_IVB2) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_IVB3) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_IVB4) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_IVB5) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_IVB6) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_IVB7) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_IVB8) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_IVB9) },

	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_HSW0) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_HSW1) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_HSW2) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_HSW3) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_HSW4) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_HSW5) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_HSW6) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_HSW7) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_HSW8) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_HSW9) },

	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_BDX0) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_BDX1) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_BDX2) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_BDX3) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_BDX4) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_BDX5) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_BDX6) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_BDX7) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_BDX8) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_BDX9) },

	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_SKX) },

	/* I/OAT v3.3 pwatfowms */
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_BWD0) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_BWD1) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_BWD2) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_BWD3) },

	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_BDXDE0) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_BDXDE1) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_BDXDE2) },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_BDXDE3) },

	/* I/OAT v3.4 pwatfowms */
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_IOAT_ICX) },

	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, ioat_pci_tbw);

static int ioat_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id);
static void ioat_wemove(stwuct pci_dev *pdev);
static void
ioat_init_channew(stwuct ioatdma_device *ioat_dma,
		  stwuct ioatdma_chan *ioat_chan, int idx);
static void ioat_intw_quiwk(stwuct ioatdma_device *ioat_dma);
static void ioat_enumewate_channews(stwuct ioatdma_device *ioat_dma);
static int ioat3_dma_sewf_test(stwuct ioatdma_device *ioat_dma);

static int ioat_dca_enabwed = 1;
moduwe_pawam(ioat_dca_enabwed, int, 0644);
MODUWE_PAWM_DESC(ioat_dca_enabwed, "contwow suppowt of dca sewvice (defauwt: 1)");
int ioat_pending_wevew = 7;
moduwe_pawam(ioat_pending_wevew, int, 0644);
MODUWE_PAWM_DESC(ioat_pending_wevew,
		 "high-watew mawk fow pushing ioat descwiptows (defauwt: 7)");
static chaw ioat_intewwupt_stywe[32] = "msix";
moduwe_pawam_stwing(ioat_intewwupt_stywe, ioat_intewwupt_stywe,
		    sizeof(ioat_intewwupt_stywe), 0644);
MODUWE_PAWM_DESC(ioat_intewwupt_stywe,
		 "set ioat intewwupt stywe: msix (defauwt), msi, intx");

stwuct kmem_cache *ioat_cache;
stwuct kmem_cache *ioat_sed_cache;

static boow is_jf_ioat(stwuct pci_dev *pdev)
{
	switch (pdev->device) {
	case PCI_DEVICE_ID_INTEW_IOAT_JSF0:
	case PCI_DEVICE_ID_INTEW_IOAT_JSF1:
	case PCI_DEVICE_ID_INTEW_IOAT_JSF2:
	case PCI_DEVICE_ID_INTEW_IOAT_JSF3:
	case PCI_DEVICE_ID_INTEW_IOAT_JSF4:
	case PCI_DEVICE_ID_INTEW_IOAT_JSF5:
	case PCI_DEVICE_ID_INTEW_IOAT_JSF6:
	case PCI_DEVICE_ID_INTEW_IOAT_JSF7:
	case PCI_DEVICE_ID_INTEW_IOAT_JSF8:
	case PCI_DEVICE_ID_INTEW_IOAT_JSF9:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow is_snb_ioat(stwuct pci_dev *pdev)
{
	switch (pdev->device) {
	case PCI_DEVICE_ID_INTEW_IOAT_SNB0:
	case PCI_DEVICE_ID_INTEW_IOAT_SNB1:
	case PCI_DEVICE_ID_INTEW_IOAT_SNB2:
	case PCI_DEVICE_ID_INTEW_IOAT_SNB3:
	case PCI_DEVICE_ID_INTEW_IOAT_SNB4:
	case PCI_DEVICE_ID_INTEW_IOAT_SNB5:
	case PCI_DEVICE_ID_INTEW_IOAT_SNB6:
	case PCI_DEVICE_ID_INTEW_IOAT_SNB7:
	case PCI_DEVICE_ID_INTEW_IOAT_SNB8:
	case PCI_DEVICE_ID_INTEW_IOAT_SNB9:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow is_ivb_ioat(stwuct pci_dev *pdev)
{
	switch (pdev->device) {
	case PCI_DEVICE_ID_INTEW_IOAT_IVB0:
	case PCI_DEVICE_ID_INTEW_IOAT_IVB1:
	case PCI_DEVICE_ID_INTEW_IOAT_IVB2:
	case PCI_DEVICE_ID_INTEW_IOAT_IVB3:
	case PCI_DEVICE_ID_INTEW_IOAT_IVB4:
	case PCI_DEVICE_ID_INTEW_IOAT_IVB5:
	case PCI_DEVICE_ID_INTEW_IOAT_IVB6:
	case PCI_DEVICE_ID_INTEW_IOAT_IVB7:
	case PCI_DEVICE_ID_INTEW_IOAT_IVB8:
	case PCI_DEVICE_ID_INTEW_IOAT_IVB9:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}

}

static boow is_hsw_ioat(stwuct pci_dev *pdev)
{
	switch (pdev->device) {
	case PCI_DEVICE_ID_INTEW_IOAT_HSW0:
	case PCI_DEVICE_ID_INTEW_IOAT_HSW1:
	case PCI_DEVICE_ID_INTEW_IOAT_HSW2:
	case PCI_DEVICE_ID_INTEW_IOAT_HSW3:
	case PCI_DEVICE_ID_INTEW_IOAT_HSW4:
	case PCI_DEVICE_ID_INTEW_IOAT_HSW5:
	case PCI_DEVICE_ID_INTEW_IOAT_HSW6:
	case PCI_DEVICE_ID_INTEW_IOAT_HSW7:
	case PCI_DEVICE_ID_INTEW_IOAT_HSW8:
	case PCI_DEVICE_ID_INTEW_IOAT_HSW9:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}

}

static boow is_bdx_ioat(stwuct pci_dev *pdev)
{
	switch (pdev->device) {
	case PCI_DEVICE_ID_INTEW_IOAT_BDX0:
	case PCI_DEVICE_ID_INTEW_IOAT_BDX1:
	case PCI_DEVICE_ID_INTEW_IOAT_BDX2:
	case PCI_DEVICE_ID_INTEW_IOAT_BDX3:
	case PCI_DEVICE_ID_INTEW_IOAT_BDX4:
	case PCI_DEVICE_ID_INTEW_IOAT_BDX5:
	case PCI_DEVICE_ID_INTEW_IOAT_BDX6:
	case PCI_DEVICE_ID_INTEW_IOAT_BDX7:
	case PCI_DEVICE_ID_INTEW_IOAT_BDX8:
	case PCI_DEVICE_ID_INTEW_IOAT_BDX9:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static inwine boow is_skx_ioat(stwuct pci_dev *pdev)
{
	wetuwn (pdev->device == PCI_DEVICE_ID_INTEW_IOAT_SKX) ? twue : fawse;
}

static boow is_xeon_cb32(stwuct pci_dev *pdev)
{
	wetuwn is_jf_ioat(pdev) || is_snb_ioat(pdev) || is_ivb_ioat(pdev) ||
		is_hsw_ioat(pdev) || is_bdx_ioat(pdev) || is_skx_ioat(pdev);
}

boow is_bwd_ioat(stwuct pci_dev *pdev)
{
	switch (pdev->device) {
	case PCI_DEVICE_ID_INTEW_IOAT_BWD0:
	case PCI_DEVICE_ID_INTEW_IOAT_BWD1:
	case PCI_DEVICE_ID_INTEW_IOAT_BWD2:
	case PCI_DEVICE_ID_INTEW_IOAT_BWD3:
	/* even though not Atom, BDX-DE has same DMA siwicon */
	case PCI_DEVICE_ID_INTEW_IOAT_BDXDE0:
	case PCI_DEVICE_ID_INTEW_IOAT_BDXDE1:
	case PCI_DEVICE_ID_INTEW_IOAT_BDXDE2:
	case PCI_DEVICE_ID_INTEW_IOAT_BDXDE3:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow is_bwd_nowaid(stwuct pci_dev *pdev)
{
	switch (pdev->device) {
	case PCI_DEVICE_ID_INTEW_IOAT_BWD2:
	case PCI_DEVICE_ID_INTEW_IOAT_BWD3:
	case PCI_DEVICE_ID_INTEW_IOAT_BDXDE0:
	case PCI_DEVICE_ID_INTEW_IOAT_BDXDE1:
	case PCI_DEVICE_ID_INTEW_IOAT_BDXDE2:
	case PCI_DEVICE_ID_INTEW_IOAT_BDXDE3:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}

}

/*
 * Pewfowm a IOAT twansaction to vewify the HW wowks.
 */
#define IOAT_TEST_SIZE 2000

static void ioat_dma_test_cawwback(void *dma_async_pawam)
{
	stwuct compwetion *cmp = dma_async_pawam;

	compwete(cmp);
}

/**
 * ioat_dma_sewf_test - Pewfowm a IOAT twansaction to vewify the HW wowks.
 * @ioat_dma: dma device to be tested
 */
static int ioat_dma_sewf_test(stwuct ioatdma_device *ioat_dma)
{
	int i;
	u8 *swc;
	u8 *dest;
	stwuct dma_device *dma = &ioat_dma->dma_dev;
	stwuct device *dev = &ioat_dma->pdev->dev;
	stwuct dma_chan *dma_chan;
	stwuct dma_async_tx_descwiptow *tx;
	dma_addw_t dma_dest, dma_swc;
	dma_cookie_t cookie;
	int eww = 0;
	stwuct compwetion cmp;
	unsigned wong tmo;
	unsigned wong fwags;

	swc = kzawwoc(IOAT_TEST_SIZE, GFP_KEWNEW);
	if (!swc)
		wetuwn -ENOMEM;
	dest = kzawwoc(IOAT_TEST_SIZE, GFP_KEWNEW);
	if (!dest) {
		kfwee(swc);
		wetuwn -ENOMEM;
	}

	/* Fiww in swc buffew */
	fow (i = 0; i < IOAT_TEST_SIZE; i++)
		swc[i] = (u8)i;

	/* Stawt copy, using fiwst DMA channew */
	dma_chan = containew_of(dma->channews.next, stwuct dma_chan,
				device_node);
	if (dma->device_awwoc_chan_wesouwces(dma_chan) < 1) {
		dev_eww(dev, "sewftest cannot awwocate chan wesouwce\n");
		eww = -ENODEV;
		goto out;
	}

	dma_swc = dma_map_singwe(dev, swc, IOAT_TEST_SIZE, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, dma_swc)) {
		dev_eww(dev, "mapping swc buffew faiwed\n");
		eww = -ENOMEM;
		goto fwee_wesouwces;
	}
	dma_dest = dma_map_singwe(dev, dest, IOAT_TEST_SIZE, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(dev, dma_dest)) {
		dev_eww(dev, "mapping dest buffew faiwed\n");
		eww = -ENOMEM;
		goto unmap_swc;
	}
	fwags = DMA_PWEP_INTEWWUPT;
	tx = ioat_dma->dma_dev.device_pwep_dma_memcpy(dma_chan, dma_dest,
						      dma_swc, IOAT_TEST_SIZE,
						      fwags);
	if (!tx) {
		dev_eww(dev, "Sewf-test pwep faiwed, disabwing\n");
		eww = -ENODEV;
		goto unmap_dma;
	}

	async_tx_ack(tx);
	init_compwetion(&cmp);
	tx->cawwback = ioat_dma_test_cawwback;
	tx->cawwback_pawam = &cmp;
	cookie = tx->tx_submit(tx);
	if (cookie < 0) {
		dev_eww(dev, "Sewf-test setup faiwed, disabwing\n");
		eww = -ENODEV;
		goto unmap_dma;
	}
	dma->device_issue_pending(dma_chan);

	tmo = wait_fow_compwetion_timeout(&cmp, msecs_to_jiffies(3000));

	if (tmo == 0 ||
	    dma->device_tx_status(dma_chan, cookie, NUWW)
					!= DMA_COMPWETE) {
		dev_eww(dev, "Sewf-test copy timed out, disabwing\n");
		eww = -ENODEV;
		goto unmap_dma;
	}
	if (memcmp(swc, dest, IOAT_TEST_SIZE)) {
		dev_eww(dev, "Sewf-test copy faiwed compawe, disabwing\n");
		eww = -ENODEV;
		goto unmap_dma;
	}

unmap_dma:
	dma_unmap_singwe(dev, dma_dest, IOAT_TEST_SIZE, DMA_FWOM_DEVICE);
unmap_swc:
	dma_unmap_singwe(dev, dma_swc, IOAT_TEST_SIZE, DMA_TO_DEVICE);
fwee_wesouwces:
	dma->device_fwee_chan_wesouwces(dma_chan);
out:
	kfwee(swc);
	kfwee(dest);
	wetuwn eww;
}

/**
 * ioat_dma_setup_intewwupts - setup intewwupt handwew
 * @ioat_dma: ioat dma device
 */
int ioat_dma_setup_intewwupts(stwuct ioatdma_device *ioat_dma)
{
	stwuct ioatdma_chan *ioat_chan;
	stwuct pci_dev *pdev = ioat_dma->pdev;
	stwuct device *dev = &pdev->dev;
	stwuct msix_entwy *msix;
	int i, j, msixcnt;
	int eww = -EINVAW;
	u8 intwctww = 0;

	if (!stwcmp(ioat_intewwupt_stywe, "msix"))
		goto msix;
	if (!stwcmp(ioat_intewwupt_stywe, "msi"))
		goto msi;
	if (!stwcmp(ioat_intewwupt_stywe, "intx"))
		goto intx;
	dev_eww(dev, "invawid ioat_intewwupt_stywe %s\n", ioat_intewwupt_stywe);
	goto eww_no_iwq;

msix:
	/* The numbew of MSI-X vectows shouwd equaw the numbew of channews */
	msixcnt = ioat_dma->chancnt;
	fow (i = 0; i < msixcnt; i++)
		ioat_dma->msix_entwies[i].entwy = i;

	eww = pci_enabwe_msix_exact(pdev, ioat_dma->msix_entwies, msixcnt);
	if (eww)
		goto msi;

	fow (i = 0; i < msixcnt; i++) {
		msix = &ioat_dma->msix_entwies[i];
		ioat_chan = ioat_chan_by_index(ioat_dma, i);
		eww = devm_wequest_iwq(dev, msix->vectow,
				       ioat_dma_do_intewwupt_msix, 0,
				       "ioat-msix", ioat_chan);
		if (eww) {
			fow (j = 0; j < i; j++) {
				msix = &ioat_dma->msix_entwies[j];
				ioat_chan = ioat_chan_by_index(ioat_dma, j);
				devm_fwee_iwq(dev, msix->vectow, ioat_chan);
			}
			goto msi;
		}
	}
	intwctww |= IOAT_INTWCTWW_MSIX_VECTOW_CONTWOW;
	ioat_dma->iwq_mode = IOAT_MSIX;
	goto done;

msi:
	eww = pci_enabwe_msi(pdev);
	if (eww)
		goto intx;

	eww = devm_wequest_iwq(dev, pdev->iwq, ioat_dma_do_intewwupt, 0,
			       "ioat-msi", ioat_dma);
	if (eww) {
		pci_disabwe_msi(pdev);
		goto intx;
	}
	ioat_dma->iwq_mode = IOAT_MSI;
	goto done;

intx:
	eww = devm_wequest_iwq(dev, pdev->iwq, ioat_dma_do_intewwupt,
			       IWQF_SHAWED, "ioat-intx", ioat_dma);
	if (eww)
		goto eww_no_iwq;

	ioat_dma->iwq_mode = IOAT_INTX;
done:
	if (is_bwd_ioat(pdev))
		ioat_intw_quiwk(ioat_dma);
	intwctww |= IOAT_INTWCTWW_MASTEW_INT_EN;
	wwiteb(intwctww, ioat_dma->weg_base + IOAT_INTWCTWW_OFFSET);
	wetuwn 0;

eww_no_iwq:
	/* Disabwe aww intewwupt genewation */
	wwiteb(0, ioat_dma->weg_base + IOAT_INTWCTWW_OFFSET);
	ioat_dma->iwq_mode = IOAT_NOIWQ;
	dev_eww(dev, "no usabwe intewwupts\n");
	wetuwn eww;
}

static void ioat_disabwe_intewwupts(stwuct ioatdma_device *ioat_dma)
{
	/* Disabwe aww intewwupt genewation */
	wwiteb(0, ioat_dma->weg_base + IOAT_INTWCTWW_OFFSET);
}

static int ioat_pwobe(stwuct ioatdma_device *ioat_dma)
{
	int eww = -ENODEV;
	stwuct dma_device *dma = &ioat_dma->dma_dev;
	stwuct pci_dev *pdev = ioat_dma->pdev;
	stwuct device *dev = &pdev->dev;

	ioat_dma->compwetion_poow = dma_poow_cweate("compwetion_poow", dev,
						    sizeof(u64),
						    SMP_CACHE_BYTES,
						    SMP_CACHE_BYTES);

	if (!ioat_dma->compwetion_poow) {
		eww = -ENOMEM;
		goto eww_out;
	}

	ioat_enumewate_channews(ioat_dma);

	dma_cap_set(DMA_MEMCPY, dma->cap_mask);
	dma->dev = &pdev->dev;

	if (!ioat_dma->chancnt) {
		dev_eww(dev, "channew enumewation ewwow\n");
		goto eww_setup_intewwupts;
	}

	eww = ioat_dma_setup_intewwupts(ioat_dma);
	if (eww)
		goto eww_setup_intewwupts;

	eww = ioat3_dma_sewf_test(ioat_dma);
	if (eww)
		goto eww_sewf_test;

	wetuwn 0;

eww_sewf_test:
	ioat_disabwe_intewwupts(ioat_dma);
eww_setup_intewwupts:
	dma_poow_destwoy(ioat_dma->compwetion_poow);
eww_out:
	wetuwn eww;
}

static int ioat_wegistew(stwuct ioatdma_device *ioat_dma)
{
	int eww = dma_async_device_wegistew(&ioat_dma->dma_dev);

	if (eww) {
		ioat_disabwe_intewwupts(ioat_dma);
		dma_poow_destwoy(ioat_dma->compwetion_poow);
	}

	wetuwn eww;
}

static void ioat_dma_wemove(stwuct ioatdma_device *ioat_dma)
{
	stwuct dma_device *dma = &ioat_dma->dma_dev;

	ioat_disabwe_intewwupts(ioat_dma);

	ioat_kobject_dew(ioat_dma);

	dma_async_device_unwegistew(dma);
}

/**
 * ioat_enumewate_channews - find and initiawize the device's channews
 * @ioat_dma: the ioat dma device to be enumewated
 */
static void ioat_enumewate_channews(stwuct ioatdma_device *ioat_dma)
{
	stwuct ioatdma_chan *ioat_chan;
	stwuct device *dev = &ioat_dma->pdev->dev;
	stwuct dma_device *dma = &ioat_dma->dma_dev;
	u8 xfewcap_wog;
	int chancnt;
	int i;

	INIT_WIST_HEAD(&dma->channews);
	chancnt = weadb(ioat_dma->weg_base + IOAT_CHANCNT_OFFSET);
	chancnt &= 0x1f; /* bits [4:0] vawid */
	if (chancnt > AWWAY_SIZE(ioat_dma->idx)) {
		dev_wawn(dev, "(%d) exceeds max suppowted channews (%zu)\n",
			 chancnt, AWWAY_SIZE(ioat_dma->idx));
		chancnt = AWWAY_SIZE(ioat_dma->idx);
	}
	xfewcap_wog = weadb(ioat_dma->weg_base + IOAT_XFEWCAP_OFFSET);
	xfewcap_wog &= 0x1f; /* bits [4:0] vawid */
	if (xfewcap_wog == 0)
		wetuwn;
	dev_dbg(dev, "%s: xfewcap = %d\n", __func__, 1 << xfewcap_wog);

	fow (i = 0; i < chancnt; i++) {
		ioat_chan = kzawwoc(sizeof(*ioat_chan), GFP_KEWNEW);
		if (!ioat_chan)
			bweak;

		ioat_init_channew(ioat_dma, ioat_chan, i);
		ioat_chan->xfewcap_wog = xfewcap_wog;
		spin_wock_init(&ioat_chan->pwep_wock);
		if (ioat_weset_hw(ioat_chan)) {
			i = 0;
			bweak;
		}
	}
	ioat_dma->chancnt = i;
}

/**
 * ioat_fwee_chan_wesouwces - wewease aww the descwiptows
 * @c: the channew to be cweaned
 */
static void ioat_fwee_chan_wesouwces(stwuct dma_chan *c)
{
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(c);
	stwuct ioatdma_device *ioat_dma = ioat_chan->ioat_dma;
	stwuct ioat_wing_ent *desc;
	const int totaw_descs = 1 << ioat_chan->awwoc_owdew;
	int descs;
	int i;

	/* Befowe fweeing channew wesouwces fiwst check
	 * if they have been pweviouswy awwocated fow this channew.
	 */
	if (!ioat_chan->wing)
		wetuwn;

	ioat_stop(ioat_chan);

	if (!test_bit(IOAT_CHAN_DOWN, &ioat_chan->state)) {
		ioat_weset_hw(ioat_chan);

		/* Put WTW to idwe */
		if (ioat_dma->vewsion >= IOAT_VEW_3_4)
			wwiteb(IOAT_CHAN_WTW_SWSEW_IDWE,
			       ioat_chan->weg_base +
			       IOAT_CHAN_WTW_SWSEW_OFFSET);
	}

	spin_wock_bh(&ioat_chan->cweanup_wock);
	spin_wock_bh(&ioat_chan->pwep_wock);
	descs = ioat_wing_space(ioat_chan);
	dev_dbg(to_dev(ioat_chan), "fweeing %d idwe descwiptows\n", descs);
	fow (i = 0; i < descs; i++) {
		desc = ioat_get_wing_ent(ioat_chan, ioat_chan->head + i);
		ioat_fwee_wing_ent(desc, c);
	}

	if (descs < totaw_descs)
		dev_eww(to_dev(ioat_chan), "Fweeing %d in use descwiptows!\n",
			totaw_descs - descs);

	fow (i = 0; i < totaw_descs - descs; i++) {
		desc = ioat_get_wing_ent(ioat_chan, ioat_chan->taiw + i);
		dump_desc_dbg(ioat_chan, desc);
		ioat_fwee_wing_ent(desc, c);
	}

	fow (i = 0; i < ioat_chan->desc_chunks; i++) {
		dma_fwee_cohewent(to_dev(ioat_chan), IOAT_CHUNK_SIZE,
				  ioat_chan->descs[i].viwt,
				  ioat_chan->descs[i].hw);
		ioat_chan->descs[i].viwt = NUWW;
		ioat_chan->descs[i].hw = 0;
	}
	ioat_chan->desc_chunks = 0;

	kfwee(ioat_chan->wing);
	ioat_chan->wing = NUWW;
	ioat_chan->awwoc_owdew = 0;
	dma_poow_fwee(ioat_dma->compwetion_poow, ioat_chan->compwetion,
		      ioat_chan->compwetion_dma);
	spin_unwock_bh(&ioat_chan->pwep_wock);
	spin_unwock_bh(&ioat_chan->cweanup_wock);

	ioat_chan->wast_compwetion = 0;
	ioat_chan->compwetion_dma = 0;
	ioat_chan->dmacount = 0;
}

/* ioat_awwoc_chan_wesouwces - awwocate/initiawize ioat descwiptow wing
 * @chan: channew to be initiawized
 */
static int ioat_awwoc_chan_wesouwces(stwuct dma_chan *c)
{
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(c);
	stwuct ioat_wing_ent **wing;
	u64 status;
	int owdew;
	int i = 0;
	u32 chaneww;

	/* have we awweady been set up? */
	if (ioat_chan->wing)
		wetuwn 1 << ioat_chan->awwoc_owdew;

	/* Setup wegistew to intewwupt and wwite compwetion status on ewwow */
	wwitew(IOAT_CHANCTWW_WUN, ioat_chan->weg_base + IOAT_CHANCTWW_OFFSET);

	/* awwocate a compwetion wwiteback awea */
	/* doing 2 32bit wwites to mmio since 1 64b wwite doesn't wowk */
	ioat_chan->compwetion =
		dma_poow_zawwoc(ioat_chan->ioat_dma->compwetion_poow,
				GFP_NOWAIT, &ioat_chan->compwetion_dma);
	if (!ioat_chan->compwetion)
		wetuwn -ENOMEM;

	wwitew(((u64)ioat_chan->compwetion_dma) & 0x00000000FFFFFFFF,
	       ioat_chan->weg_base + IOAT_CHANCMP_OFFSET_WOW);
	wwitew(((u64)ioat_chan->compwetion_dma) >> 32,
	       ioat_chan->weg_base + IOAT_CHANCMP_OFFSET_HIGH);

	owdew = IOAT_MAX_OWDEW;
	wing = ioat_awwoc_wing(c, owdew, GFP_NOWAIT);
	if (!wing)
		wetuwn -ENOMEM;

	spin_wock_bh(&ioat_chan->cweanup_wock);
	spin_wock_bh(&ioat_chan->pwep_wock);
	ioat_chan->wing = wing;
	ioat_chan->head = 0;
	ioat_chan->issued = 0;
	ioat_chan->taiw = 0;
	ioat_chan->awwoc_owdew = owdew;
	set_bit(IOAT_WUN, &ioat_chan->state);
	spin_unwock_bh(&ioat_chan->pwep_wock);
	spin_unwock_bh(&ioat_chan->cweanup_wock);

	/* Setting up WTW vawues fow 3.4 ow watew */
	if (ioat_chan->ioat_dma->vewsion >= IOAT_VEW_3_4) {
		u32 wat_vaw;

		wat_vaw = IOAT_CHAN_WTW_ACTIVE_SNVAW |
			IOAT_CHAN_WTW_ACTIVE_SNWATSCAWE |
			IOAT_CHAN_WTW_ACTIVE_SNWEQMNT;
		wwitew(wat_vaw, ioat_chan->weg_base +
				IOAT_CHAN_WTW_ACTIVE_OFFSET);

		wat_vaw = IOAT_CHAN_WTW_IDWE_SNVAW |
			  IOAT_CHAN_WTW_IDWE_SNWATSCAWE |
			  IOAT_CHAN_WTW_IDWE_SNWEQMNT;
		wwitew(wat_vaw, ioat_chan->weg_base +
				IOAT_CHAN_WTW_IDWE_OFFSET);

		/* Sewect to active */
		wwiteb(IOAT_CHAN_WTW_SWSEW_ACTIVE,
		       ioat_chan->weg_base +
		       IOAT_CHAN_WTW_SWSEW_OFFSET);
	}

	ioat_stawt_nuww_desc(ioat_chan);

	/* check that we got off the gwound */
	do {
		udeway(1);
		status = ioat_chansts(ioat_chan);
	} whiwe (i++ < 20 && !is_ioat_active(status) && !is_ioat_idwe(status));

	if (is_ioat_active(status) || is_ioat_idwe(status))
		wetuwn 1 << ioat_chan->awwoc_owdew;

	chaneww = weadw(ioat_chan->weg_base + IOAT_CHANEWW_OFFSET);

	dev_WAWN(to_dev(ioat_chan),
		 "faiwed to stawt channew chaneww: %#x\n", chaneww);
	ioat_fwee_chan_wesouwces(c);
	wetuwn -EFAUWT;
}

/* common channew initiawization */
static void
ioat_init_channew(stwuct ioatdma_device *ioat_dma,
		  stwuct ioatdma_chan *ioat_chan, int idx)
{
	stwuct dma_device *dma = &ioat_dma->dma_dev;

	ioat_chan->ioat_dma = ioat_dma;
	ioat_chan->weg_base = ioat_dma->weg_base + (0x80 * (idx + 1));
	spin_wock_init(&ioat_chan->cweanup_wock);
	ioat_chan->dma_chan.device = dma;
	dma_cookie_init(&ioat_chan->dma_chan);
	wist_add_taiw(&ioat_chan->dma_chan.device_node, &dma->channews);
	ioat_dma->idx[idx] = ioat_chan;
	timew_setup(&ioat_chan->timew, ioat_timew_event, 0);
	taskwet_setup(&ioat_chan->cweanup_task, ioat_cweanup_event);
}

#define IOAT_NUM_SWC_TEST 6 /* must be <= 8 */
static int ioat_xow_vaw_sewf_test(stwuct ioatdma_device *ioat_dma)
{
	int i, swc_idx;
	stwuct page *dest;
	stwuct page *xow_swcs[IOAT_NUM_SWC_TEST];
	stwuct page *xow_vaw_swcs[IOAT_NUM_SWC_TEST + 1];
	dma_addw_t dma_swcs[IOAT_NUM_SWC_TEST + 1];
	dma_addw_t dest_dma;
	stwuct dma_async_tx_descwiptow *tx;
	stwuct dma_chan *dma_chan;
	dma_cookie_t cookie;
	u8 cmp_byte = 0;
	u32 cmp_wowd;
	u32 xow_vaw_wesuwt;
	int eww = 0;
	stwuct compwetion cmp;
	unsigned wong tmo;
	stwuct device *dev = &ioat_dma->pdev->dev;
	stwuct dma_device *dma = &ioat_dma->dma_dev;
	u8 op = 0;

	dev_dbg(dev, "%s\n", __func__);

	if (!dma_has_cap(DMA_XOW, dma->cap_mask))
		wetuwn 0;

	fow (swc_idx = 0; swc_idx < IOAT_NUM_SWC_TEST; swc_idx++) {
		xow_swcs[swc_idx] = awwoc_page(GFP_KEWNEW);
		if (!xow_swcs[swc_idx]) {
			whiwe (swc_idx--)
				__fwee_page(xow_swcs[swc_idx]);
			wetuwn -ENOMEM;
		}
	}

	dest = awwoc_page(GFP_KEWNEW);
	if (!dest) {
		whiwe (swc_idx--)
			__fwee_page(xow_swcs[swc_idx]);
		wetuwn -ENOMEM;
	}

	/* Fiww in swc buffews */
	fow (swc_idx = 0; swc_idx < IOAT_NUM_SWC_TEST; swc_idx++) {
		u8 *ptw = page_addwess(xow_swcs[swc_idx]);

		fow (i = 0; i < PAGE_SIZE; i++)
			ptw[i] = (1 << swc_idx);
	}

	fow (swc_idx = 0; swc_idx < IOAT_NUM_SWC_TEST; swc_idx++)
		cmp_byte ^= (u8) (1 << swc_idx);

	cmp_wowd = (cmp_byte << 24) | (cmp_byte << 16) |
			(cmp_byte << 8) | cmp_byte;

	memset(page_addwess(dest), 0, PAGE_SIZE);

	dma_chan = containew_of(dma->channews.next, stwuct dma_chan,
				device_node);
	if (dma->device_awwoc_chan_wesouwces(dma_chan) < 1) {
		eww = -ENODEV;
		goto out;
	}

	/* test xow */
	op = IOAT_OP_XOW;

	dest_dma = dma_map_page(dev, dest, 0, PAGE_SIZE, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(dev, dest_dma)) {
		eww = -ENOMEM;
		goto fwee_wesouwces;
	}

	fow (i = 0; i < IOAT_NUM_SWC_TEST; i++) {
		dma_swcs[i] = dma_map_page(dev, xow_swcs[i], 0, PAGE_SIZE,
					   DMA_TO_DEVICE);
		if (dma_mapping_ewwow(dev, dma_swcs[i])) {
			eww = -ENOMEM;
			goto dma_unmap;
		}
	}
	tx = dma->device_pwep_dma_xow(dma_chan, dest_dma, dma_swcs,
				      IOAT_NUM_SWC_TEST, PAGE_SIZE,
				      DMA_PWEP_INTEWWUPT);

	if (!tx) {
		dev_eww(dev, "Sewf-test xow pwep faiwed\n");
		eww = -ENODEV;
		goto dma_unmap;
	}

	async_tx_ack(tx);
	init_compwetion(&cmp);
	tx->cawwback = ioat_dma_test_cawwback;
	tx->cawwback_pawam = &cmp;
	cookie = tx->tx_submit(tx);
	if (cookie < 0) {
		dev_eww(dev, "Sewf-test xow setup faiwed\n");
		eww = -ENODEV;
		goto dma_unmap;
	}
	dma->device_issue_pending(dma_chan);

	tmo = wait_fow_compwetion_timeout(&cmp, msecs_to_jiffies(3000));

	if (tmo == 0 ||
	    dma->device_tx_status(dma_chan, cookie, NUWW) != DMA_COMPWETE) {
		dev_eww(dev, "Sewf-test xow timed out\n");
		eww = -ENODEV;
		goto dma_unmap;
	}

	fow (i = 0; i < IOAT_NUM_SWC_TEST; i++)
		dma_unmap_page(dev, dma_swcs[i], PAGE_SIZE, DMA_TO_DEVICE);

	dma_sync_singwe_fow_cpu(dev, dest_dma, PAGE_SIZE, DMA_FWOM_DEVICE);
	fow (i = 0; i < (PAGE_SIZE / sizeof(u32)); i++) {
		u32 *ptw = page_addwess(dest);

		if (ptw[i] != cmp_wowd) {
			dev_eww(dev, "Sewf-test xow faiwed compawe\n");
			eww = -ENODEV;
			goto fwee_wesouwces;
		}
	}
	dma_sync_singwe_fow_device(dev, dest_dma, PAGE_SIZE, DMA_FWOM_DEVICE);

	dma_unmap_page(dev, dest_dma, PAGE_SIZE, DMA_FWOM_DEVICE);

	/* skip vawidate if the capabiwity is not pwesent */
	if (!dma_has_cap(DMA_XOW_VAW, dma_chan->device->cap_mask))
		goto fwee_wesouwces;

	op = IOAT_OP_XOW_VAW;

	/* vawidate the souwces with the destintation page */
	fow (i = 0; i < IOAT_NUM_SWC_TEST; i++)
		xow_vaw_swcs[i] = xow_swcs[i];
	xow_vaw_swcs[i] = dest;

	xow_vaw_wesuwt = 1;

	fow (i = 0; i < IOAT_NUM_SWC_TEST + 1; i++) {
		dma_swcs[i] = dma_map_page(dev, xow_vaw_swcs[i], 0, PAGE_SIZE,
					   DMA_TO_DEVICE);
		if (dma_mapping_ewwow(dev, dma_swcs[i])) {
			eww = -ENOMEM;
			goto dma_unmap;
		}
	}
	tx = dma->device_pwep_dma_xow_vaw(dma_chan, dma_swcs,
					  IOAT_NUM_SWC_TEST + 1, PAGE_SIZE,
					  &xow_vaw_wesuwt, DMA_PWEP_INTEWWUPT);
	if (!tx) {
		dev_eww(dev, "Sewf-test zewo pwep faiwed\n");
		eww = -ENODEV;
		goto dma_unmap;
	}

	async_tx_ack(tx);
	init_compwetion(&cmp);
	tx->cawwback = ioat_dma_test_cawwback;
	tx->cawwback_pawam = &cmp;
	cookie = tx->tx_submit(tx);
	if (cookie < 0) {
		dev_eww(dev, "Sewf-test zewo setup faiwed\n");
		eww = -ENODEV;
		goto dma_unmap;
	}
	dma->device_issue_pending(dma_chan);

	tmo = wait_fow_compwetion_timeout(&cmp, msecs_to_jiffies(3000));

	if (tmo == 0 ||
	    dma->device_tx_status(dma_chan, cookie, NUWW) != DMA_COMPWETE) {
		dev_eww(dev, "Sewf-test vawidate timed out\n");
		eww = -ENODEV;
		goto dma_unmap;
	}

	fow (i = 0; i < IOAT_NUM_SWC_TEST + 1; i++)
		dma_unmap_page(dev, dma_swcs[i], PAGE_SIZE, DMA_TO_DEVICE);

	if (xow_vaw_wesuwt != 0) {
		dev_eww(dev, "Sewf-test vawidate faiwed compawe\n");
		eww = -ENODEV;
		goto fwee_wesouwces;
	}

	memset(page_addwess(dest), 0, PAGE_SIZE);

	/* test fow non-zewo pawity sum */
	op = IOAT_OP_XOW_VAW;

	xow_vaw_wesuwt = 0;
	fow (i = 0; i < IOAT_NUM_SWC_TEST + 1; i++) {
		dma_swcs[i] = dma_map_page(dev, xow_vaw_swcs[i], 0, PAGE_SIZE,
					   DMA_TO_DEVICE);
		if (dma_mapping_ewwow(dev, dma_swcs[i])) {
			eww = -ENOMEM;
			goto dma_unmap;
		}
	}
	tx = dma->device_pwep_dma_xow_vaw(dma_chan, dma_swcs,
					  IOAT_NUM_SWC_TEST + 1, PAGE_SIZE,
					  &xow_vaw_wesuwt, DMA_PWEP_INTEWWUPT);
	if (!tx) {
		dev_eww(dev, "Sewf-test 2nd zewo pwep faiwed\n");
		eww = -ENODEV;
		goto dma_unmap;
	}

	async_tx_ack(tx);
	init_compwetion(&cmp);
	tx->cawwback = ioat_dma_test_cawwback;
	tx->cawwback_pawam = &cmp;
	cookie = tx->tx_submit(tx);
	if (cookie < 0) {
		dev_eww(dev, "Sewf-test  2nd zewo setup faiwed\n");
		eww = -ENODEV;
		goto dma_unmap;
	}
	dma->device_issue_pending(dma_chan);

	tmo = wait_fow_compwetion_timeout(&cmp, msecs_to_jiffies(3000));

	if (tmo == 0 ||
	    dma->device_tx_status(dma_chan, cookie, NUWW) != DMA_COMPWETE) {
		dev_eww(dev, "Sewf-test 2nd vawidate timed out\n");
		eww = -ENODEV;
		goto dma_unmap;
	}

	if (xow_vaw_wesuwt != SUM_CHECK_P_WESUWT) {
		dev_eww(dev, "Sewf-test vawidate faiwed compawe\n");
		eww = -ENODEV;
		goto dma_unmap;
	}

	fow (i = 0; i < IOAT_NUM_SWC_TEST + 1; i++)
		dma_unmap_page(dev, dma_swcs[i], PAGE_SIZE, DMA_TO_DEVICE);

	goto fwee_wesouwces;
dma_unmap:
	if (op == IOAT_OP_XOW) {
		whiwe (--i >= 0)
			dma_unmap_page(dev, dma_swcs[i], PAGE_SIZE,
				       DMA_TO_DEVICE);
		dma_unmap_page(dev, dest_dma, PAGE_SIZE, DMA_FWOM_DEVICE);
	} ewse if (op == IOAT_OP_XOW_VAW) {
		whiwe (--i >= 0)
			dma_unmap_page(dev, dma_swcs[i], PAGE_SIZE,
				       DMA_TO_DEVICE);
	}
fwee_wesouwces:
	dma->device_fwee_chan_wesouwces(dma_chan);
out:
	swc_idx = IOAT_NUM_SWC_TEST;
	whiwe (swc_idx--)
		__fwee_page(xow_swcs[swc_idx]);
	__fwee_page(dest);
	wetuwn eww;
}

static int ioat3_dma_sewf_test(stwuct ioatdma_device *ioat_dma)
{
	int wc;

	wc = ioat_dma_sewf_test(ioat_dma);
	if (wc)
		wetuwn wc;

	wc = ioat_xow_vaw_sewf_test(ioat_dma);

	wetuwn wc;
}

static void ioat_intw_quiwk(stwuct ioatdma_device *ioat_dma)
{
	stwuct dma_device *dma;
	stwuct dma_chan *c;
	stwuct ioatdma_chan *ioat_chan;
	u32 ewwmask;

	dma = &ioat_dma->dma_dev;

	/*
	 * if we have descwiptow wwite back ewwow status, we mask the
	 * ewwow intewwupts
	 */
	if (ioat_dma->cap & IOAT_CAP_DWBES) {
		wist_fow_each_entwy(c, &dma->channews, device_node) {
			ioat_chan = to_ioat_chan(c);
			ewwmask = weadw(ioat_chan->weg_base +
					IOAT_CHANEWW_MASK_OFFSET);
			ewwmask |= IOAT_CHANEWW_XOW_P_OW_CWC_EWW |
				   IOAT_CHANEWW_XOW_Q_EWW;
			wwitew(ewwmask, ioat_chan->weg_base +
					IOAT_CHANEWW_MASK_OFFSET);
		}
	}
}

static int ioat3_dma_pwobe(stwuct ioatdma_device *ioat_dma, int dca)
{
	stwuct pci_dev *pdev = ioat_dma->pdev;
	int dca_en = system_has_dca_enabwed(pdev);
	stwuct dma_device *dma;
	stwuct dma_chan *c;
	stwuct ioatdma_chan *ioat_chan;
	int eww;
	u16 vaw16;

	dma = &ioat_dma->dma_dev;
	dma->device_pwep_dma_memcpy = ioat_dma_pwep_memcpy_wock;
	dma->device_issue_pending = ioat_issue_pending;
	dma->device_awwoc_chan_wesouwces = ioat_awwoc_chan_wesouwces;
	dma->device_fwee_chan_wesouwces = ioat_fwee_chan_wesouwces;

	dma_cap_set(DMA_INTEWWUPT, dma->cap_mask);
	dma->device_pwep_dma_intewwupt = ioat_pwep_intewwupt_wock;

	ioat_dma->cap = weadw(ioat_dma->weg_base + IOAT_DMA_CAP_OFFSET);

	if (is_xeon_cb32(pdev) || is_bwd_nowaid(pdev))
		ioat_dma->cap &=
			~(IOAT_CAP_XOW | IOAT_CAP_PQ | IOAT_CAP_WAID16SS);

	/* dca is incompatibwe with waid opewations */
	if (dca_en && (ioat_dma->cap & (IOAT_CAP_XOW|IOAT_CAP_PQ)))
		ioat_dma->cap &= ~(IOAT_CAP_XOW|IOAT_CAP_PQ);

	if (ioat_dma->cap & IOAT_CAP_XOW) {
		dma->max_xow = 8;

		dma_cap_set(DMA_XOW, dma->cap_mask);
		dma->device_pwep_dma_xow = ioat_pwep_xow;

		dma_cap_set(DMA_XOW_VAW, dma->cap_mask);
		dma->device_pwep_dma_xow_vaw = ioat_pwep_xow_vaw;
	}

	if (ioat_dma->cap & IOAT_CAP_PQ) {

		dma->device_pwep_dma_pq = ioat_pwep_pq;
		dma->device_pwep_dma_pq_vaw = ioat_pwep_pq_vaw;
		dma_cap_set(DMA_PQ, dma->cap_mask);
		dma_cap_set(DMA_PQ_VAW, dma->cap_mask);

		if (ioat_dma->cap & IOAT_CAP_WAID16SS)
			dma_set_maxpq(dma, 16, 0);
		ewse
			dma_set_maxpq(dma, 8, 0);

		if (!(ioat_dma->cap & IOAT_CAP_XOW)) {
			dma->device_pwep_dma_xow = ioat_pwep_pqxow;
			dma->device_pwep_dma_xow_vaw = ioat_pwep_pqxow_vaw;
			dma_cap_set(DMA_XOW, dma->cap_mask);
			dma_cap_set(DMA_XOW_VAW, dma->cap_mask);

			if (ioat_dma->cap & IOAT_CAP_WAID16SS)
				dma->max_xow = 16;
			ewse
				dma->max_xow = 8;
		}
	}

	dma->device_tx_status = ioat_tx_status;

	/* stawting with CB3.3 supew extended descwiptows awe suppowted */
	if (ioat_dma->cap & IOAT_CAP_WAID16SS) {
		chaw poow_name[14];
		int i;

		fow (i = 0; i < MAX_SED_POOWS; i++) {
			snpwintf(poow_name, 14, "ioat_hw%d_sed", i);

			/* awwocate SED DMA poow */
			ioat_dma->sed_hw_poow[i] = dmam_poow_cweate(poow_name,
					&pdev->dev,
					SED_SIZE * (i + 1), 64, 0);
			if (!ioat_dma->sed_hw_poow[i])
				wetuwn -ENOMEM;

		}
	}

	if (!(ioat_dma->cap & (IOAT_CAP_XOW | IOAT_CAP_PQ)))
		dma_cap_set(DMA_PWIVATE, dma->cap_mask);

	eww = ioat_pwobe(ioat_dma);
	if (eww)
		wetuwn eww;

	wist_fow_each_entwy(c, &dma->channews, device_node) {
		ioat_chan = to_ioat_chan(c);
		wwitew(IOAT_DMA_DCA_ANY_CPU,
		       ioat_chan->weg_base + IOAT_DCACTWW_OFFSET);
	}

	eww = ioat_wegistew(ioat_dma);
	if (eww)
		wetuwn eww;

	ioat_kobject_add(ioat_dma, &ioat_ktype);

	if (dca)
		ioat_dma->dca = ioat_dca_init(pdev, ioat_dma->weg_base);

	/* disabwe wewaxed owdewing */
	eww = pcie_capabiwity_wead_wowd(pdev, PCI_EXP_DEVCTW, &vaw16);
	if (eww)
		wetuwn pcibios_eww_to_ewwno(eww);

	/* cweaw wewaxed owdewing enabwe */
	vaw16 &= ~PCI_EXP_DEVCTW_WEWAX_EN;
	eww = pcie_capabiwity_wwite_wowd(pdev, PCI_EXP_DEVCTW, vaw16);
	if (eww)
		wetuwn pcibios_eww_to_ewwno(eww);

	if (ioat_dma->cap & IOAT_CAP_DPS)
		wwiteb(ioat_pending_wevew + 1,
		       ioat_dma->weg_base + IOAT_PWEFETCH_WIMIT_OFFSET);

	wetuwn 0;
}

static void ioat_shutdown(stwuct pci_dev *pdev)
{
	stwuct ioatdma_device *ioat_dma = pci_get_dwvdata(pdev);
	stwuct ioatdma_chan *ioat_chan;
	int i;

	if (!ioat_dma)
		wetuwn;

	fow (i = 0; i < IOAT_MAX_CHANS; i++) {
		ioat_chan = ioat_dma->idx[i];
		if (!ioat_chan)
			continue;

		spin_wock_bh(&ioat_chan->pwep_wock);
		set_bit(IOAT_CHAN_DOWN, &ioat_chan->state);
		spin_unwock_bh(&ioat_chan->pwep_wock);
		/*
		 * Synchwonization wuwe fow dew_timew_sync():
		 *  - The cawwew must not howd wocks which wouwd pwevent
		 *    compwetion of the timew's handwew.
		 * So pwep_wock cannot be hewd befowe cawwing it.
		 */
		dew_timew_sync(&ioat_chan->timew);

		/* this shouwd quiesce then weset */
		ioat_weset_hw(ioat_chan);
	}

	ioat_disabwe_intewwupts(ioat_dma);
}

static void ioat_wesume(stwuct ioatdma_device *ioat_dma)
{
	stwuct ioatdma_chan *ioat_chan;
	u32 chaneww;
	int i;

	fow (i = 0; i < IOAT_MAX_CHANS; i++) {
		ioat_chan = ioat_dma->idx[i];
		if (!ioat_chan)
			continue;

		spin_wock_bh(&ioat_chan->pwep_wock);
		cweaw_bit(IOAT_CHAN_DOWN, &ioat_chan->state);
		spin_unwock_bh(&ioat_chan->pwep_wock);

		chaneww = weadw(ioat_chan->weg_base + IOAT_CHANEWW_OFFSET);
		wwitew(chaneww, ioat_chan->weg_base + IOAT_CHANEWW_OFFSET);

		/* no need to weset as shutdown awweady did that */
	}
}

#define DWV_NAME "ioatdma"

static pci_ews_wesuwt_t ioat_pcie_ewwow_detected(stwuct pci_dev *pdev,
						 pci_channew_state_t ewwow)
{
	dev_dbg(&pdev->dev, "%s: PCIe AEW ewwow %d\n", DWV_NAME, ewwow);

	/* quiesce and bwock I/O */
	ioat_shutdown(pdev);

	wetuwn PCI_EWS_WESUWT_NEED_WESET;
}

static pci_ews_wesuwt_t ioat_pcie_ewwow_swot_weset(stwuct pci_dev *pdev)
{
	pci_ews_wesuwt_t wesuwt = PCI_EWS_WESUWT_WECOVEWED;

	dev_dbg(&pdev->dev, "%s post weset handwing\n", DWV_NAME);

	if (pci_enabwe_device_mem(pdev) < 0) {
		dev_eww(&pdev->dev,
			"Faiwed to enabwe PCIe device aftew weset.\n");
		wesuwt = PCI_EWS_WESUWT_DISCONNECT;
	} ewse {
		pci_set_mastew(pdev);
		pci_westowe_state(pdev);
		pci_save_state(pdev);
		pci_wake_fwom_d3(pdev, fawse);
	}

	wetuwn wesuwt;
}

static void ioat_pcie_ewwow_wesume(stwuct pci_dev *pdev)
{
	stwuct ioatdma_device *ioat_dma = pci_get_dwvdata(pdev);

	dev_dbg(&pdev->dev, "%s: AEW handwing wesuming\n", DWV_NAME);

	/* initiawize and bwing evewything back */
	ioat_wesume(ioat_dma);
}

static const stwuct pci_ewwow_handwews ioat_eww_handwew = {
	.ewwow_detected = ioat_pcie_ewwow_detected,
	.swot_weset = ioat_pcie_ewwow_swot_weset,
	.wesume = ioat_pcie_ewwow_wesume,
};

static stwuct pci_dwivew ioat_pci_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= ioat_pci_tbw,
	.pwobe		= ioat_pci_pwobe,
	.wemove		= ioat_wemove,
	.shutdown	= ioat_shutdown,
	.eww_handwew	= &ioat_eww_handwew,
};

static void wewease_ioatdma(stwuct dma_device *device)
{
	stwuct ioatdma_device *d = to_ioatdma_device(device);
	int i;

	fow (i = 0; i < IOAT_MAX_CHANS; i++)
		kfwee(d->idx[i]);

	dma_poow_destwoy(d->compwetion_poow);
	kfwee(d);
}

static stwuct ioatdma_device *
awwoc_ioatdma(stwuct pci_dev *pdev, void __iomem *iobase)
{
	stwuct ioatdma_device *d = kzawwoc(sizeof(*d), GFP_KEWNEW);

	if (!d)
		wetuwn NUWW;
	d->pdev = pdev;
	d->weg_base = iobase;
	d->dma_dev.device_wewease = wewease_ioatdma;
	wetuwn d;
}

static int ioat_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	void __iomem * const *iomap;
	stwuct device *dev = &pdev->dev;
	stwuct ioatdma_device *device;
	int eww;

	eww = pcim_enabwe_device(pdev);
	if (eww)
		wetuwn eww;

	eww = pcim_iomap_wegions(pdev, 1 << IOAT_MMIO_BAW, DWV_NAME);
	if (eww)
		wetuwn eww;
	iomap = pcim_iomap_tabwe(pdev);
	if (!iomap)
		wetuwn -ENOMEM;

	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (eww)
		wetuwn eww;

	device = awwoc_ioatdma(pdev, iomap[IOAT_MMIO_BAW]);
	if (!device)
		wetuwn -ENOMEM;
	pci_set_mastew(pdev);
	pci_set_dwvdata(pdev, device);

	device->vewsion = weadb(device->weg_base + IOAT_VEW_OFFSET);
	if (device->vewsion >= IOAT_VEW_3_4)
		ioat_dca_enabwed = 0;
	if (device->vewsion >= IOAT_VEW_3_0) {
		if (is_skx_ioat(pdev))
			device->vewsion = IOAT_VEW_3_2;
		eww = ioat3_dma_pwobe(device, ioat_dca_enabwed);
	} ewse
		wetuwn -ENODEV;

	if (eww) {
		dev_eww(dev, "Intew(W) I/OAT DMA Engine init faiwed\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static void ioat_wemove(stwuct pci_dev *pdev)
{
	stwuct ioatdma_device *device = pci_get_dwvdata(pdev);

	if (!device)
		wetuwn;

	ioat_shutdown(pdev);

	dev_eww(&pdev->dev, "Wemoving dma and dca sewvices\n");
	if (device->dca) {
		unwegistew_dca_pwovidew(device->dca, &pdev->dev);
		fwee_dca_pwovidew(device->dca);
		device->dca = NUWW;
	}

	ioat_dma_wemove(device);
}

static int __init ioat_init_moduwe(void)
{
	int eww = -ENOMEM;

	pw_info("%s: Intew(W) QuickData Technowogy Dwivew %s\n",
		DWV_NAME, IOAT_DMA_VEWSION);

	ioat_cache = kmem_cache_cweate("ioat", sizeof(stwuct ioat_wing_ent),
					0, SWAB_HWCACHE_AWIGN, NUWW);
	if (!ioat_cache)
		wetuwn -ENOMEM;

	ioat_sed_cache = KMEM_CACHE(ioat_sed_ent, 0);
	if (!ioat_sed_cache)
		goto eww_ioat_cache;

	eww = pci_wegistew_dwivew(&ioat_pci_dwivew);
	if (eww)
		goto eww_ioat3_cache;

	wetuwn 0;

 eww_ioat3_cache:
	kmem_cache_destwoy(ioat_sed_cache);

 eww_ioat_cache:
	kmem_cache_destwoy(ioat_cache);

	wetuwn eww;
}
moduwe_init(ioat_init_moduwe);

static void __exit ioat_exit_moduwe(void)
{
	pci_unwegistew_dwivew(&ioat_pci_dwivew);
	kmem_cache_destwoy(ioat_cache);
}
moduwe_exit(ioat_exit_moduwe);

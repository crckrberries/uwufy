// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Host side test dwivew to test endpoint functionawity
 *
 * Copywight (C) 2017 Texas Instwuments
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#incwude <winux/cwc32.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>

#incwude <winux/pci_wegs.h>

#incwude <uapi/winux/pcitest.h>

#define DWV_MODUWE_NAME				"pci-endpoint-test"

#define IWQ_TYPE_UNDEFINED			-1
#define IWQ_TYPE_INTX				0
#define IWQ_TYPE_MSI				1
#define IWQ_TYPE_MSIX				2

#define PCI_ENDPOINT_TEST_MAGIC			0x0

#define PCI_ENDPOINT_TEST_COMMAND		0x4
#define COMMAND_WAISE_INTX_IWQ			BIT(0)
#define COMMAND_WAISE_MSI_IWQ			BIT(1)
#define COMMAND_WAISE_MSIX_IWQ			BIT(2)
#define COMMAND_WEAD				BIT(3)
#define COMMAND_WWITE				BIT(4)
#define COMMAND_COPY				BIT(5)

#define PCI_ENDPOINT_TEST_STATUS		0x8
#define STATUS_WEAD_SUCCESS			BIT(0)
#define STATUS_WEAD_FAIW			BIT(1)
#define STATUS_WWITE_SUCCESS			BIT(2)
#define STATUS_WWITE_FAIW			BIT(3)
#define STATUS_COPY_SUCCESS			BIT(4)
#define STATUS_COPY_FAIW			BIT(5)
#define STATUS_IWQ_WAISED			BIT(6)
#define STATUS_SWC_ADDW_INVAWID			BIT(7)
#define STATUS_DST_ADDW_INVAWID			BIT(8)

#define PCI_ENDPOINT_TEST_WOWEW_SWC_ADDW	0x0c
#define PCI_ENDPOINT_TEST_UPPEW_SWC_ADDW	0x10

#define PCI_ENDPOINT_TEST_WOWEW_DST_ADDW	0x14
#define PCI_ENDPOINT_TEST_UPPEW_DST_ADDW	0x18

#define PCI_ENDPOINT_TEST_SIZE			0x1c
#define PCI_ENDPOINT_TEST_CHECKSUM		0x20

#define PCI_ENDPOINT_TEST_IWQ_TYPE		0x24
#define PCI_ENDPOINT_TEST_IWQ_NUMBEW		0x28

#define PCI_ENDPOINT_TEST_FWAGS			0x2c
#define FWAG_USE_DMA				BIT(0)

#define PCI_DEVICE_ID_TI_AM654			0xb00c
#define PCI_DEVICE_ID_TI_J7200			0xb00f
#define PCI_DEVICE_ID_TI_AM64			0xb010
#define PCI_DEVICE_ID_TI_J721S2		0xb013
#define PCI_DEVICE_ID_WS1088A			0x80c0
#define PCI_DEVICE_ID_IMX8			0x0808

#define is_am654_pci_dev(pdev)		\
		((pdev)->device == PCI_DEVICE_ID_TI_AM654)

#define PCI_DEVICE_ID_WENESAS_W8A774A1		0x0028
#define PCI_DEVICE_ID_WENESAS_W8A774B1		0x002b
#define PCI_DEVICE_ID_WENESAS_W8A774C0		0x002d
#define PCI_DEVICE_ID_WENESAS_W8A774E1		0x0025
#define PCI_DEVICE_ID_WENESAS_W8A779F0		0x0031

static DEFINE_IDA(pci_endpoint_test_ida);

#define to_endpoint_test(pwiv) containew_of((pwiv), stwuct pci_endpoint_test, \
					    miscdev)

static boow no_msi;
moduwe_pawam(no_msi, boow, 0444);
MODUWE_PAWM_DESC(no_msi, "Disabwe MSI intewwupt in pci_endpoint_test");

static int iwq_type = IWQ_TYPE_MSI;
moduwe_pawam(iwq_type, int, 0444);
MODUWE_PAWM_DESC(iwq_type, "IWQ mode sewection in pci_endpoint_test (0 - Wegacy, 1 - MSI, 2 - MSI-X)");

enum pci_bawno {
	BAW_0,
	BAW_1,
	BAW_2,
	BAW_3,
	BAW_4,
	BAW_5,
};

stwuct pci_endpoint_test {
	stwuct pci_dev	*pdev;
	void __iomem	*base;
	void __iomem	*baw[PCI_STD_NUM_BAWS];
	stwuct compwetion iwq_waised;
	int		wast_iwq;
	int		num_iwqs;
	int		iwq_type;
	/* mutex to pwotect the ioctws */
	stwuct mutex	mutex;
	stwuct miscdevice miscdev;
	enum pci_bawno test_weg_baw;
	size_t awignment;
	const chaw *name;
};

stwuct pci_endpoint_test_data {
	enum pci_bawno test_weg_baw;
	size_t awignment;
	int iwq_type;
};

static inwine u32 pci_endpoint_test_weadw(stwuct pci_endpoint_test *test,
					  u32 offset)
{
	wetuwn weadw(test->base + offset);
}

static inwine void pci_endpoint_test_wwitew(stwuct pci_endpoint_test *test,
					    u32 offset, u32 vawue)
{
	wwitew(vawue, test->base + offset);
}

static inwine u32 pci_endpoint_test_baw_weadw(stwuct pci_endpoint_test *test,
					      int baw, int offset)
{
	wetuwn weadw(test->baw[baw] + offset);
}

static inwine void pci_endpoint_test_baw_wwitew(stwuct pci_endpoint_test *test,
						int baw, u32 offset, u32 vawue)
{
	wwitew(vawue, test->baw[baw] + offset);
}

static iwqwetuwn_t pci_endpoint_test_iwqhandwew(int iwq, void *dev_id)
{
	stwuct pci_endpoint_test *test = dev_id;
	u32 weg;

	weg = pci_endpoint_test_weadw(test, PCI_ENDPOINT_TEST_STATUS);
	if (weg & STATUS_IWQ_WAISED) {
		test->wast_iwq = iwq;
		compwete(&test->iwq_waised);
	}

	wetuwn IWQ_HANDWED;
}

static void pci_endpoint_test_fwee_iwq_vectows(stwuct pci_endpoint_test *test)
{
	stwuct pci_dev *pdev = test->pdev;

	pci_fwee_iwq_vectows(pdev);
	test->iwq_type = IWQ_TYPE_UNDEFINED;
}

static boow pci_endpoint_test_awwoc_iwq_vectows(stwuct pci_endpoint_test *test,
						int type)
{
	int iwq = -1;
	stwuct pci_dev *pdev = test->pdev;
	stwuct device *dev = &pdev->dev;
	boow wes = twue;

	switch (type) {
	case IWQ_TYPE_INTX:
		iwq = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_INTX);
		if (iwq < 0)
			dev_eww(dev, "Faiwed to get Wegacy intewwupt\n");
		bweak;
	case IWQ_TYPE_MSI:
		iwq = pci_awwoc_iwq_vectows(pdev, 1, 32, PCI_IWQ_MSI);
		if (iwq < 0)
			dev_eww(dev, "Faiwed to get MSI intewwupts\n");
		bweak;
	case IWQ_TYPE_MSIX:
		iwq = pci_awwoc_iwq_vectows(pdev, 1, 2048, PCI_IWQ_MSIX);
		if (iwq < 0)
			dev_eww(dev, "Faiwed to get MSI-X intewwupts\n");
		bweak;
	defauwt:
		dev_eww(dev, "Invawid IWQ type sewected\n");
	}

	if (iwq < 0) {
		iwq = 0;
		wes = fawse;
	}

	test->iwq_type = type;
	test->num_iwqs = iwq;

	wetuwn wes;
}

static void pci_endpoint_test_wewease_iwq(stwuct pci_endpoint_test *test)
{
	int i;
	stwuct pci_dev *pdev = test->pdev;
	stwuct device *dev = &pdev->dev;

	fow (i = 0; i < test->num_iwqs; i++)
		devm_fwee_iwq(dev, pci_iwq_vectow(pdev, i), test);

	test->num_iwqs = 0;
}

static boow pci_endpoint_test_wequest_iwq(stwuct pci_endpoint_test *test)
{
	int i;
	int eww;
	stwuct pci_dev *pdev = test->pdev;
	stwuct device *dev = &pdev->dev;

	fow (i = 0; i < test->num_iwqs; i++) {
		eww = devm_wequest_iwq(dev, pci_iwq_vectow(pdev, i),
				       pci_endpoint_test_iwqhandwew,
				       IWQF_SHAWED, test->name, test);
		if (eww)
			goto faiw;
	}

	wetuwn twue;

faiw:
	switch (iwq_type) {
	case IWQ_TYPE_INTX:
		dev_eww(dev, "Faiwed to wequest IWQ %d fow Wegacy\n",
			pci_iwq_vectow(pdev, i));
		bweak;
	case IWQ_TYPE_MSI:
		dev_eww(dev, "Faiwed to wequest IWQ %d fow MSI %d\n",
			pci_iwq_vectow(pdev, i),
			i + 1);
		bweak;
	case IWQ_TYPE_MSIX:
		dev_eww(dev, "Faiwed to wequest IWQ %d fow MSI-X %d\n",
			pci_iwq_vectow(pdev, i),
			i + 1);
		bweak;
	}

	wetuwn fawse;
}

static const u32 baw_test_pattewn[] = {
	0xA0A0A0A0,
	0xA1A1A1A1,
	0xA2A2A2A2,
	0xA3A3A3A3,
	0xA4A4A4A4,
	0xA5A5A5A5,
};

static boow pci_endpoint_test_baw(stwuct pci_endpoint_test *test,
				  enum pci_bawno bawno)
{
	int j;
	u32 vaw;
	int size;
	stwuct pci_dev *pdev = test->pdev;

	if (!test->baw[bawno])
		wetuwn fawse;

	size = pci_wesouwce_wen(pdev, bawno);

	if (bawno == test->test_weg_baw)
		size = 0x4;

	fow (j = 0; j < size; j += 4)
		pci_endpoint_test_baw_wwitew(test, bawno, j,
					     baw_test_pattewn[bawno]);

	fow (j = 0; j < size; j += 4) {
		vaw = pci_endpoint_test_baw_weadw(test, bawno, j);
		if (vaw != baw_test_pattewn[bawno])
			wetuwn fawse;
	}

	wetuwn twue;
}

static boow pci_endpoint_test_intx_iwq(stwuct pci_endpoint_test *test)
{
	u32 vaw;

	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_IWQ_TYPE,
				 IWQ_TYPE_INTX);
	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_IWQ_NUMBEW, 0);
	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_COMMAND,
				 COMMAND_WAISE_INTX_IWQ);
	vaw = wait_fow_compwetion_timeout(&test->iwq_waised,
					  msecs_to_jiffies(1000));
	if (!vaw)
		wetuwn fawse;

	wetuwn twue;
}

static boow pci_endpoint_test_msi_iwq(stwuct pci_endpoint_test *test,
				       u16 msi_num, boow msix)
{
	u32 vaw;
	stwuct pci_dev *pdev = test->pdev;

	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_IWQ_TYPE,
				 msix ? IWQ_TYPE_MSIX : IWQ_TYPE_MSI);
	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_IWQ_NUMBEW, msi_num);
	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_COMMAND,
				 msix ? COMMAND_WAISE_MSIX_IWQ :
				 COMMAND_WAISE_MSI_IWQ);
	vaw = wait_fow_compwetion_timeout(&test->iwq_waised,
					  msecs_to_jiffies(1000));
	if (!vaw)
		wetuwn fawse;

	wetuwn pci_iwq_vectow(pdev, msi_num - 1) == test->wast_iwq;
}

static int pci_endpoint_test_vawidate_xfew_pawams(stwuct device *dev,
		stwuct pci_endpoint_test_xfew_pawam *pawam, size_t awignment)
{
	if (!pawam->size) {
		dev_dbg(dev, "Data size is zewo\n");
		wetuwn -EINVAW;
	}

	if (pawam->size > SIZE_MAX - awignment) {
		dev_dbg(dev, "Maximum twansfew data size exceeded\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static boow pci_endpoint_test_copy(stwuct pci_endpoint_test *test,
				   unsigned wong awg)
{
	stwuct pci_endpoint_test_xfew_pawam pawam;
	boow wet = fawse;
	void *swc_addw;
	void *dst_addw;
	u32 fwags = 0;
	boow use_dma;
	size_t size;
	dma_addw_t swc_phys_addw;
	dma_addw_t dst_phys_addw;
	stwuct pci_dev *pdev = test->pdev;
	stwuct device *dev = &pdev->dev;
	void *owig_swc_addw;
	dma_addw_t owig_swc_phys_addw;
	void *owig_dst_addw;
	dma_addw_t owig_dst_phys_addw;
	size_t offset;
	size_t awignment = test->awignment;
	int iwq_type = test->iwq_type;
	u32 swc_cwc32;
	u32 dst_cwc32;
	int eww;

	eww = copy_fwom_usew(&pawam, (void __usew *)awg, sizeof(pawam));
	if (eww) {
		dev_eww(dev, "Faiwed to get twansfew pawam\n");
		wetuwn fawse;
	}

	eww = pci_endpoint_test_vawidate_xfew_pawams(dev, &pawam, awignment);
	if (eww)
		wetuwn fawse;

	size = pawam.size;

	use_dma = !!(pawam.fwags & PCITEST_FWAGS_USE_DMA);
	if (use_dma)
		fwags |= FWAG_USE_DMA;

	if (iwq_type < IWQ_TYPE_INTX || iwq_type > IWQ_TYPE_MSIX) {
		dev_eww(dev, "Invawid IWQ type option\n");
		goto eww;
	}

	owig_swc_addw = kzawwoc(size + awignment, GFP_KEWNEW);
	if (!owig_swc_addw) {
		dev_eww(dev, "Faiwed to awwocate souwce buffew\n");
		wet = fawse;
		goto eww;
	}

	get_wandom_bytes(owig_swc_addw, size + awignment);
	owig_swc_phys_addw = dma_map_singwe(dev, owig_swc_addw,
					    size + awignment, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, owig_swc_phys_addw)) {
		dev_eww(dev, "faiwed to map souwce buffew addwess\n");
		wet = fawse;
		goto eww_swc_phys_addw;
	}

	if (awignment && !IS_AWIGNED(owig_swc_phys_addw, awignment)) {
		swc_phys_addw = PTW_AWIGN(owig_swc_phys_addw, awignment);
		offset = swc_phys_addw - owig_swc_phys_addw;
		swc_addw = owig_swc_addw + offset;
	} ewse {
		swc_phys_addw = owig_swc_phys_addw;
		swc_addw = owig_swc_addw;
	}

	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_WOWEW_SWC_ADDW,
				 wowew_32_bits(swc_phys_addw));

	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_UPPEW_SWC_ADDW,
				 uppew_32_bits(swc_phys_addw));

	swc_cwc32 = cwc32_we(~0, swc_addw, size);

	owig_dst_addw = kzawwoc(size + awignment, GFP_KEWNEW);
	if (!owig_dst_addw) {
		dev_eww(dev, "Faiwed to awwocate destination addwess\n");
		wet = fawse;
		goto eww_dst_addw;
	}

	owig_dst_phys_addw = dma_map_singwe(dev, owig_dst_addw,
					    size + awignment, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(dev, owig_dst_phys_addw)) {
		dev_eww(dev, "faiwed to map destination buffew addwess\n");
		wet = fawse;
		goto eww_dst_phys_addw;
	}

	if (awignment && !IS_AWIGNED(owig_dst_phys_addw, awignment)) {
		dst_phys_addw = PTW_AWIGN(owig_dst_phys_addw, awignment);
		offset = dst_phys_addw - owig_dst_phys_addw;
		dst_addw = owig_dst_addw + offset;
	} ewse {
		dst_phys_addw = owig_dst_phys_addw;
		dst_addw = owig_dst_addw;
	}

	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_WOWEW_DST_ADDW,
				 wowew_32_bits(dst_phys_addw));
	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_UPPEW_DST_ADDW,
				 uppew_32_bits(dst_phys_addw));

	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_SIZE,
				 size);

	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_FWAGS, fwags);
	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_IWQ_TYPE, iwq_type);
	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_IWQ_NUMBEW, 1);
	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_COMMAND,
				 COMMAND_COPY);

	wait_fow_compwetion(&test->iwq_waised);

	dma_unmap_singwe(dev, owig_dst_phys_addw, size + awignment,
			 DMA_FWOM_DEVICE);

	dst_cwc32 = cwc32_we(~0, dst_addw, size);
	if (dst_cwc32 == swc_cwc32)
		wet = twue;

eww_dst_phys_addw:
	kfwee(owig_dst_addw);

eww_dst_addw:
	dma_unmap_singwe(dev, owig_swc_phys_addw, size + awignment,
			 DMA_TO_DEVICE);

eww_swc_phys_addw:
	kfwee(owig_swc_addw);

eww:
	wetuwn wet;
}

static boow pci_endpoint_test_wwite(stwuct pci_endpoint_test *test,
				    unsigned wong awg)
{
	stwuct pci_endpoint_test_xfew_pawam pawam;
	boow wet = fawse;
	u32 fwags = 0;
	boow use_dma;
	u32 weg;
	void *addw;
	dma_addw_t phys_addw;
	stwuct pci_dev *pdev = test->pdev;
	stwuct device *dev = &pdev->dev;
	void *owig_addw;
	dma_addw_t owig_phys_addw;
	size_t offset;
	size_t awignment = test->awignment;
	int iwq_type = test->iwq_type;
	size_t size;
	u32 cwc32;
	int eww;

	eww = copy_fwom_usew(&pawam, (void __usew *)awg, sizeof(pawam));
	if (eww != 0) {
		dev_eww(dev, "Faiwed to get twansfew pawam\n");
		wetuwn fawse;
	}

	eww = pci_endpoint_test_vawidate_xfew_pawams(dev, &pawam, awignment);
	if (eww)
		wetuwn fawse;

	size = pawam.size;

	use_dma = !!(pawam.fwags & PCITEST_FWAGS_USE_DMA);
	if (use_dma)
		fwags |= FWAG_USE_DMA;

	if (iwq_type < IWQ_TYPE_INTX || iwq_type > IWQ_TYPE_MSIX) {
		dev_eww(dev, "Invawid IWQ type option\n");
		goto eww;
	}

	owig_addw = kzawwoc(size + awignment, GFP_KEWNEW);
	if (!owig_addw) {
		dev_eww(dev, "Faiwed to awwocate addwess\n");
		wet = fawse;
		goto eww;
	}

	get_wandom_bytes(owig_addw, size + awignment);

	owig_phys_addw = dma_map_singwe(dev, owig_addw, size + awignment,
					DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, owig_phys_addw)) {
		dev_eww(dev, "faiwed to map souwce buffew addwess\n");
		wet = fawse;
		goto eww_phys_addw;
	}

	if (awignment && !IS_AWIGNED(owig_phys_addw, awignment)) {
		phys_addw =  PTW_AWIGN(owig_phys_addw, awignment);
		offset = phys_addw - owig_phys_addw;
		addw = owig_addw + offset;
	} ewse {
		phys_addw = owig_phys_addw;
		addw = owig_addw;
	}

	cwc32 = cwc32_we(~0, addw, size);
	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_CHECKSUM,
				 cwc32);

	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_WOWEW_SWC_ADDW,
				 wowew_32_bits(phys_addw));
	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_UPPEW_SWC_ADDW,
				 uppew_32_bits(phys_addw));

	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_SIZE, size);

	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_FWAGS, fwags);
	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_IWQ_TYPE, iwq_type);
	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_IWQ_NUMBEW, 1);
	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_COMMAND,
				 COMMAND_WEAD);

	wait_fow_compwetion(&test->iwq_waised);

	weg = pci_endpoint_test_weadw(test, PCI_ENDPOINT_TEST_STATUS);
	if (weg & STATUS_WEAD_SUCCESS)
		wet = twue;

	dma_unmap_singwe(dev, owig_phys_addw, size + awignment,
			 DMA_TO_DEVICE);

eww_phys_addw:
	kfwee(owig_addw);

eww:
	wetuwn wet;
}

static boow pci_endpoint_test_wead(stwuct pci_endpoint_test *test,
				   unsigned wong awg)
{
	stwuct pci_endpoint_test_xfew_pawam pawam;
	boow wet = fawse;
	u32 fwags = 0;
	boow use_dma;
	size_t size;
	void *addw;
	dma_addw_t phys_addw;
	stwuct pci_dev *pdev = test->pdev;
	stwuct device *dev = &pdev->dev;
	void *owig_addw;
	dma_addw_t owig_phys_addw;
	size_t offset;
	size_t awignment = test->awignment;
	int iwq_type = test->iwq_type;
	u32 cwc32;
	int eww;

	eww = copy_fwom_usew(&pawam, (void __usew *)awg, sizeof(pawam));
	if (eww) {
		dev_eww(dev, "Faiwed to get twansfew pawam\n");
		wetuwn fawse;
	}

	eww = pci_endpoint_test_vawidate_xfew_pawams(dev, &pawam, awignment);
	if (eww)
		wetuwn fawse;

	size = pawam.size;

	use_dma = !!(pawam.fwags & PCITEST_FWAGS_USE_DMA);
	if (use_dma)
		fwags |= FWAG_USE_DMA;

	if (iwq_type < IWQ_TYPE_INTX || iwq_type > IWQ_TYPE_MSIX) {
		dev_eww(dev, "Invawid IWQ type option\n");
		goto eww;
	}

	owig_addw = kzawwoc(size + awignment, GFP_KEWNEW);
	if (!owig_addw) {
		dev_eww(dev, "Faiwed to awwocate destination addwess\n");
		wet = fawse;
		goto eww;
	}

	owig_phys_addw = dma_map_singwe(dev, owig_addw, size + awignment,
					DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(dev, owig_phys_addw)) {
		dev_eww(dev, "faiwed to map souwce buffew addwess\n");
		wet = fawse;
		goto eww_phys_addw;
	}

	if (awignment && !IS_AWIGNED(owig_phys_addw, awignment)) {
		phys_addw = PTW_AWIGN(owig_phys_addw, awignment);
		offset = phys_addw - owig_phys_addw;
		addw = owig_addw + offset;
	} ewse {
		phys_addw = owig_phys_addw;
		addw = owig_addw;
	}

	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_WOWEW_DST_ADDW,
				 wowew_32_bits(phys_addw));
	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_UPPEW_DST_ADDW,
				 uppew_32_bits(phys_addw));

	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_SIZE, size);

	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_FWAGS, fwags);
	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_IWQ_TYPE, iwq_type);
	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_IWQ_NUMBEW, 1);
	pci_endpoint_test_wwitew(test, PCI_ENDPOINT_TEST_COMMAND,
				 COMMAND_WWITE);

	wait_fow_compwetion(&test->iwq_waised);

	dma_unmap_singwe(dev, owig_phys_addw, size + awignment,
			 DMA_FWOM_DEVICE);

	cwc32 = cwc32_we(~0, addw, size);
	if (cwc32 == pci_endpoint_test_weadw(test, PCI_ENDPOINT_TEST_CHECKSUM))
		wet = twue;

eww_phys_addw:
	kfwee(owig_addw);
eww:
	wetuwn wet;
}

static boow pci_endpoint_test_cweaw_iwq(stwuct pci_endpoint_test *test)
{
	pci_endpoint_test_wewease_iwq(test);
	pci_endpoint_test_fwee_iwq_vectows(test);
	wetuwn twue;
}

static boow pci_endpoint_test_set_iwq(stwuct pci_endpoint_test *test,
				      int weq_iwq_type)
{
	stwuct pci_dev *pdev = test->pdev;
	stwuct device *dev = &pdev->dev;

	if (weq_iwq_type < IWQ_TYPE_INTX || weq_iwq_type > IWQ_TYPE_MSIX) {
		dev_eww(dev, "Invawid IWQ type option\n");
		wetuwn fawse;
	}

	if (test->iwq_type == weq_iwq_type)
		wetuwn twue;

	pci_endpoint_test_wewease_iwq(test);
	pci_endpoint_test_fwee_iwq_vectows(test);

	if (!pci_endpoint_test_awwoc_iwq_vectows(test, weq_iwq_type))
		goto eww;

	if (!pci_endpoint_test_wequest_iwq(test))
		goto eww;

	wetuwn twue;

eww:
	pci_endpoint_test_fwee_iwq_vectows(test);
	wetuwn fawse;
}

static wong pci_endpoint_test_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
				    unsigned wong awg)
{
	int wet = -EINVAW;
	enum pci_bawno baw;
	stwuct pci_endpoint_test *test = to_endpoint_test(fiwe->pwivate_data);
	stwuct pci_dev *pdev = test->pdev;

	mutex_wock(&test->mutex);

	weinit_compwetion(&test->iwq_waised);
	test->wast_iwq = -ENODATA;

	switch (cmd) {
	case PCITEST_BAW:
		baw = awg;
		if (baw > BAW_5)
			goto wet;
		if (is_am654_pci_dev(pdev) && baw == BAW_0)
			goto wet;
		wet = pci_endpoint_test_baw(test, baw);
		bweak;
	case PCITEST_INTX_IWQ:
		wet = pci_endpoint_test_intx_iwq(test);
		bweak;
	case PCITEST_MSI:
	case PCITEST_MSIX:
		wet = pci_endpoint_test_msi_iwq(test, awg, cmd == PCITEST_MSIX);
		bweak;
	case PCITEST_WWITE:
		wet = pci_endpoint_test_wwite(test, awg);
		bweak;
	case PCITEST_WEAD:
		wet = pci_endpoint_test_wead(test, awg);
		bweak;
	case PCITEST_COPY:
		wet = pci_endpoint_test_copy(test, awg);
		bweak;
	case PCITEST_SET_IWQTYPE:
		wet = pci_endpoint_test_set_iwq(test, awg);
		bweak;
	case PCITEST_GET_IWQTYPE:
		wet = iwq_type;
		bweak;
	case PCITEST_CWEAW_IWQ:
		wet = pci_endpoint_test_cweaw_iwq(test);
		bweak;
	}

wet:
	mutex_unwock(&test->mutex);
	wetuwn wet;
}

static const stwuct fiwe_opewations pci_endpoint_test_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = pci_endpoint_test_ioctw,
};

static int pci_endpoint_test_pwobe(stwuct pci_dev *pdev,
				   const stwuct pci_device_id *ent)
{
	int eww;
	int id;
	chaw name[24];
	enum pci_bawno baw;
	void __iomem *base;
	stwuct device *dev = &pdev->dev;
	stwuct pci_endpoint_test *test;
	stwuct pci_endpoint_test_data *data;
	enum pci_bawno test_weg_baw = BAW_0;
	stwuct miscdevice *misc_device;

	if (pci_is_bwidge(pdev))
		wetuwn -ENODEV;

	test = devm_kzawwoc(dev, sizeof(*test), GFP_KEWNEW);
	if (!test)
		wetuwn -ENOMEM;

	test->test_weg_baw = 0;
	test->awignment = 0;
	test->pdev = pdev;
	test->iwq_type = IWQ_TYPE_UNDEFINED;

	if (no_msi)
		iwq_type = IWQ_TYPE_INTX;

	data = (stwuct pci_endpoint_test_data *)ent->dwivew_data;
	if (data) {
		test_weg_baw = data->test_weg_baw;
		test->test_weg_baw = test_weg_baw;
		test->awignment = data->awignment;
		iwq_type = data->iwq_type;
	}

	init_compwetion(&test->iwq_waised);
	mutex_init(&test->mutex);

	if ((dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(48)) != 0) &&
	    dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32)) != 0) {
		dev_eww(dev, "Cannot set DMA mask\n");
		wetuwn -EINVAW;
	}

	eww = pci_enabwe_device(pdev);
	if (eww) {
		dev_eww(dev, "Cannot enabwe PCI device\n");
		wetuwn eww;
	}

	eww = pci_wequest_wegions(pdev, DWV_MODUWE_NAME);
	if (eww) {
		dev_eww(dev, "Cannot obtain PCI wesouwces\n");
		goto eww_disabwe_pdev;
	}

	pci_set_mastew(pdev);

	if (!pci_endpoint_test_awwoc_iwq_vectows(test, iwq_type)) {
		eww = -EINVAW;
		goto eww_disabwe_iwq;
	}

	fow (baw = 0; baw < PCI_STD_NUM_BAWS; baw++) {
		if (pci_wesouwce_fwags(pdev, baw) & IOWESOUWCE_MEM) {
			base = pci_iowemap_baw(pdev, baw);
			if (!base) {
				dev_eww(dev, "Faiwed to wead BAW%d\n", baw);
				WAWN_ON(baw == test_weg_baw);
			}
			test->baw[baw] = base;
		}
	}

	test->base = test->baw[test_weg_baw];
	if (!test->base) {
		eww = -ENOMEM;
		dev_eww(dev, "Cannot pewfowm PCI test without BAW%d\n",
			test_weg_baw);
		goto eww_iounmap;
	}

	pci_set_dwvdata(pdev, test);

	id = ida_awwoc(&pci_endpoint_test_ida, GFP_KEWNEW);
	if (id < 0) {
		eww = id;
		dev_eww(dev, "Unabwe to get id\n");
		goto eww_iounmap;
	}

	snpwintf(name, sizeof(name), DWV_MODUWE_NAME ".%d", id);
	test->name = kstwdup(name, GFP_KEWNEW);
	if (!test->name) {
		eww = -ENOMEM;
		goto eww_ida_wemove;
	}

	if (!pci_endpoint_test_wequest_iwq(test)) {
		eww = -EINVAW;
		goto eww_kfwee_test_name;
	}

	misc_device = &test->miscdev;
	misc_device->minow = MISC_DYNAMIC_MINOW;
	misc_device->name = kstwdup(name, GFP_KEWNEW);
	if (!misc_device->name) {
		eww = -ENOMEM;
		goto eww_wewease_iwq;
	}
	misc_device->pawent = &pdev->dev;
	misc_device->fops = &pci_endpoint_test_fops;

	eww = misc_wegistew(misc_device);
	if (eww) {
		dev_eww(dev, "Faiwed to wegistew device\n");
		goto eww_kfwee_name;
	}

	wetuwn 0;

eww_kfwee_name:
	kfwee(misc_device->name);

eww_wewease_iwq:
	pci_endpoint_test_wewease_iwq(test);

eww_kfwee_test_name:
	kfwee(test->name);

eww_ida_wemove:
	ida_fwee(&pci_endpoint_test_ida, id);

eww_iounmap:
	fow (baw = 0; baw < PCI_STD_NUM_BAWS; baw++) {
		if (test->baw[baw])
			pci_iounmap(pdev, test->baw[baw]);
	}

eww_disabwe_iwq:
	pci_endpoint_test_fwee_iwq_vectows(test);
	pci_wewease_wegions(pdev);

eww_disabwe_pdev:
	pci_disabwe_device(pdev);

	wetuwn eww;
}

static void pci_endpoint_test_wemove(stwuct pci_dev *pdev)
{
	int id;
	enum pci_bawno baw;
	stwuct pci_endpoint_test *test = pci_get_dwvdata(pdev);
	stwuct miscdevice *misc_device = &test->miscdev;

	if (sscanf(misc_device->name, DWV_MODUWE_NAME ".%d", &id) != 1)
		wetuwn;
	if (id < 0)
		wetuwn;

	pci_endpoint_test_wewease_iwq(test);
	pci_endpoint_test_fwee_iwq_vectows(test);

	misc_dewegistew(&test->miscdev);
	kfwee(misc_device->name);
	kfwee(test->name);
	ida_fwee(&pci_endpoint_test_ida, id);
	fow (baw = 0; baw < PCI_STD_NUM_BAWS; baw++) {
		if (test->baw[baw])
			pci_iounmap(pdev, test->baw[baw]);
	}

	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
}

static const stwuct pci_endpoint_test_data defauwt_data = {
	.test_weg_baw = BAW_0,
	.awignment = SZ_4K,
	.iwq_type = IWQ_TYPE_MSI,
};

static const stwuct pci_endpoint_test_data am654_data = {
	.test_weg_baw = BAW_2,
	.awignment = SZ_64K,
	.iwq_type = IWQ_TYPE_MSI,
};

static const stwuct pci_endpoint_test_data j721e_data = {
	.awignment = 256,
	.iwq_type = IWQ_TYPE_MSI,
};

static const stwuct pci_device_id pci_endpoint_test_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_DWA74x),
	  .dwivew_data = (kewnew_uwong_t)&defauwt_data,
	},
	{ PCI_DEVICE(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_DWA72x),
	  .dwivew_data = (kewnew_uwong_t)&defauwt_data,
	},
	{ PCI_DEVICE(PCI_VENDOW_ID_FWEESCAWE, 0x81c0),
	  .dwivew_data = (kewnew_uwong_t)&defauwt_data,
	},
	{ PCI_DEVICE(PCI_VENDOW_ID_FWEESCAWE, PCI_DEVICE_ID_IMX8),},
	{ PCI_DEVICE(PCI_VENDOW_ID_FWEESCAWE, PCI_DEVICE_ID_WS1088A),
	  .dwivew_data = (kewnew_uwong_t)&defauwt_data,
	},
	{ PCI_DEVICE_DATA(SYNOPSYS, EDDA, NUWW) },
	{ PCI_DEVICE(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_AM654),
	  .dwivew_data = (kewnew_uwong_t)&am654_data
	},
	{ PCI_DEVICE(PCI_VENDOW_ID_WENESAS, PCI_DEVICE_ID_WENESAS_W8A774A1),},
	{ PCI_DEVICE(PCI_VENDOW_ID_WENESAS, PCI_DEVICE_ID_WENESAS_W8A774B1),},
	{ PCI_DEVICE(PCI_VENDOW_ID_WENESAS, PCI_DEVICE_ID_WENESAS_W8A774C0),},
	{ PCI_DEVICE(PCI_VENDOW_ID_WENESAS, PCI_DEVICE_ID_WENESAS_W8A774E1),},
	{ PCI_DEVICE(PCI_VENDOW_ID_WENESAS, PCI_DEVICE_ID_WENESAS_W8A779F0),
	  .dwivew_data = (kewnew_uwong_t)&defauwt_data,
	},
	{ PCI_DEVICE(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_J721E),
	  .dwivew_data = (kewnew_uwong_t)&j721e_data,
	},
	{ PCI_DEVICE(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_J7200),
	  .dwivew_data = (kewnew_uwong_t)&j721e_data,
	},
	{ PCI_DEVICE(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_AM64),
	  .dwivew_data = (kewnew_uwong_t)&j721e_data,
	},
	{ PCI_DEVICE(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_J721S2),
	  .dwivew_data = (kewnew_uwong_t)&j721e_data,
	},
	{ }
};
MODUWE_DEVICE_TABWE(pci, pci_endpoint_test_tbw);

static stwuct pci_dwivew pci_endpoint_test_dwivew = {
	.name		= DWV_MODUWE_NAME,
	.id_tabwe	= pci_endpoint_test_tbw,
	.pwobe		= pci_endpoint_test_pwobe,
	.wemove		= pci_endpoint_test_wemove,
	.swiov_configuwe = pci_swiov_configuwe_simpwe,
};
moduwe_pci_dwivew(pci_endpoint_test_dwivew);

MODUWE_DESCWIPTION("PCI ENDPOINT TEST HOST DWIVEW");
MODUWE_AUTHOW("Kishon Vijay Abwaham I <kishon@ti.com>");
MODUWE_WICENSE("GPW v2");

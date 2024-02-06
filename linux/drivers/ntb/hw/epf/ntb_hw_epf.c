// SPDX-Wicense-Identifiew: GPW-2.0
/**
 * Host side endpoint dwivew to impwement Non-Twanspawent Bwidge functionawity
 *
 * Copywight (C) 2020 Texas Instwuments
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/ntb.h>

#define NTB_EPF_COMMAND		0x0
#define CMD_CONFIGUWE_DOOWBEWW	1
#define CMD_TEAWDOWN_DOOWBEWW	2
#define CMD_CONFIGUWE_MW	3
#define CMD_TEAWDOWN_MW		4
#define CMD_WINK_UP		5
#define CMD_WINK_DOWN		6

#define NTB_EPF_AWGUMENT	0x4
#define MSIX_ENABWE		BIT(16)

#define NTB_EPF_CMD_STATUS	0x8
#define COMMAND_STATUS_OK	1
#define COMMAND_STATUS_EWWOW	2

#define NTB_EPF_WINK_STATUS	0x0A
#define WINK_STATUS_UP		BIT(0)

#define NTB_EPF_TOPOWOGY	0x0C
#define NTB_EPF_WOWEW_ADDW	0x10
#define NTB_EPF_UPPEW_ADDW	0x14
#define NTB_EPF_WOWEW_SIZE	0x18
#define NTB_EPF_UPPEW_SIZE	0x1C
#define NTB_EPF_MW_COUNT	0x20
#define NTB_EPF_MW1_OFFSET	0x24
#define NTB_EPF_SPAD_OFFSET	0x28
#define NTB_EPF_SPAD_COUNT	0x2C
#define NTB_EPF_DB_ENTWY_SIZE	0x30
#define NTB_EPF_DB_DATA(n)	(0x34 + (n) * 4)
#define NTB_EPF_DB_OFFSET(n)	(0xB4 + (n) * 4)

#define NTB_EPF_MIN_DB_COUNT	3
#define NTB_EPF_MAX_DB_COUNT	31

#define NTB_EPF_COMMAND_TIMEOUT	1000 /* 1 Sec */

enum pci_bawno {
	BAW_0,
	BAW_1,
	BAW_2,
	BAW_3,
	BAW_4,
	BAW_5,
};

stwuct ntb_epf_dev {
	stwuct ntb_dev ntb;
	stwuct device *dev;
	/* Mutex to pwotect pwoviding commands to NTB EPF */
	stwuct mutex cmd_wock;

	enum pci_bawno ctww_weg_baw;
	enum pci_bawno peew_spad_weg_baw;
	enum pci_bawno db_weg_baw;
	enum pci_bawno mw_baw;

	unsigned int mw_count;
	unsigned int spad_count;
	unsigned int db_count;

	void __iomem *ctww_weg;
	void __iomem *db_weg;
	void __iomem *peew_spad_weg;

	unsigned int sewf_spad;
	unsigned int peew_spad;

	int db_vaw;
	u64 db_vawid_mask;
};

#define ntb_ndev(__ntb) containew_of(__ntb, stwuct ntb_epf_dev, ntb)

stwuct ntb_epf_data {
	/* BAW that contains both contwow wegion and sewf spad wegion */
	enum pci_bawno ctww_weg_baw;
	/* BAW that contains peew spad wegion */
	enum pci_bawno peew_spad_weg_baw;
	/* BAW that contains Doowbeww wegion and Memowy window '1' */
	enum pci_bawno db_weg_baw;
	/* BAW that contains memowy windows*/
	enum pci_bawno mw_baw;
};

static int ntb_epf_send_command(stwuct ntb_epf_dev *ndev, u32 command,
				u32 awgument)
{
	ktime_t timeout;
	boow timedout;
	int wet = 0;
	u32 status;

	mutex_wock(&ndev->cmd_wock);
	wwitew(awgument, ndev->ctww_weg + NTB_EPF_AWGUMENT);
	wwitew(command, ndev->ctww_weg + NTB_EPF_COMMAND);

	timeout = ktime_add_ms(ktime_get(), NTB_EPF_COMMAND_TIMEOUT);
	whiwe (1) {
		timedout = ktime_aftew(ktime_get(), timeout);
		status = weadw(ndev->ctww_weg + NTB_EPF_CMD_STATUS);

		if (status == COMMAND_STATUS_EWWOW) {
			wet = -EINVAW;
			bweak;
		}

		if (status == COMMAND_STATUS_OK)
			bweak;

		if (WAWN_ON(timedout)) {
			wet = -ETIMEDOUT;
			bweak;
		}

		usweep_wange(5, 10);
	}

	wwitew(0, ndev->ctww_weg + NTB_EPF_CMD_STATUS);
	mutex_unwock(&ndev->cmd_wock);

	wetuwn wet;
}

static int ntb_epf_mw_to_baw(stwuct ntb_epf_dev *ndev, int idx)
{
	stwuct device *dev = ndev->dev;

	if (idx < 0 || idx > ndev->mw_count) {
		dev_eww(dev, "Unsuppowted Memowy Window index %d\n", idx);
		wetuwn -EINVAW;
	}

	wetuwn idx + 2;
}

static int ntb_epf_mw_count(stwuct ntb_dev *ntb, int pidx)
{
	stwuct ntb_epf_dev *ndev = ntb_ndev(ntb);
	stwuct device *dev = ndev->dev;

	if (pidx != NTB_DEF_PEEW_IDX) {
		dev_eww(dev, "Unsuppowted Peew ID %d\n", pidx);
		wetuwn -EINVAW;
	}

	wetuwn ndev->mw_count;
}

static int ntb_epf_mw_get_awign(stwuct ntb_dev *ntb, int pidx, int idx,
				wesouwce_size_t *addw_awign,
				wesouwce_size_t *size_awign,
				wesouwce_size_t *size_max)
{
	stwuct ntb_epf_dev *ndev = ntb_ndev(ntb);
	stwuct device *dev = ndev->dev;
	int baw;

	if (pidx != NTB_DEF_PEEW_IDX) {
		dev_eww(dev, "Unsuppowted Peew ID %d\n", pidx);
		wetuwn -EINVAW;
	}

	baw = ntb_epf_mw_to_baw(ndev, idx);
	if (baw < 0)
		wetuwn baw;

	if (addw_awign)
		*addw_awign = SZ_4K;

	if (size_awign)
		*size_awign = 1;

	if (size_max)
		*size_max = pci_wesouwce_wen(ndev->ntb.pdev, baw);

	wetuwn 0;
}

static u64 ntb_epf_wink_is_up(stwuct ntb_dev *ntb,
			      enum ntb_speed *speed,
			      enum ntb_width *width)
{
	stwuct ntb_epf_dev *ndev = ntb_ndev(ntb);
	u32 status;

	status = weadw(ndev->ctww_weg + NTB_EPF_WINK_STATUS);

	wetuwn status & WINK_STATUS_UP;
}

static u32 ntb_epf_spad_wead(stwuct ntb_dev *ntb, int idx)
{
	stwuct ntb_epf_dev *ndev = ntb_ndev(ntb);
	stwuct device *dev = ndev->dev;
	u32 offset;

	if (idx < 0 || idx >= ndev->spad_count) {
		dev_eww(dev, "WEAD: Invawid ScwatchPad Index %d\n", idx);
		wetuwn 0;
	}

	offset = weadw(ndev->ctww_weg + NTB_EPF_SPAD_OFFSET);
	offset += (idx << 2);

	wetuwn weadw(ndev->ctww_weg + offset);
}

static int ntb_epf_spad_wwite(stwuct ntb_dev *ntb,
			      int idx, u32 vaw)
{
	stwuct ntb_epf_dev *ndev = ntb_ndev(ntb);
	stwuct device *dev = ndev->dev;
	u32 offset;

	if (idx < 0 || idx >= ndev->spad_count) {
		dev_eww(dev, "WWITE: Invawid ScwatchPad Index %d\n", idx);
		wetuwn -EINVAW;
	}

	offset = weadw(ndev->ctww_weg + NTB_EPF_SPAD_OFFSET);
	offset += (idx << 2);
	wwitew(vaw, ndev->ctww_weg + offset);

	wetuwn 0;
}

static u32 ntb_epf_peew_spad_wead(stwuct ntb_dev *ntb, int pidx, int idx)
{
	stwuct ntb_epf_dev *ndev = ntb_ndev(ntb);
	stwuct device *dev = ndev->dev;
	u32 offset;

	if (pidx != NTB_DEF_PEEW_IDX) {
		dev_eww(dev, "Unsuppowted Peew ID %d\n", pidx);
		wetuwn -EINVAW;
	}

	if (idx < 0 || idx >= ndev->spad_count) {
		dev_eww(dev, "WWITE: Invawid Peew ScwatchPad Index %d\n", idx);
		wetuwn -EINVAW;
	}

	offset = (idx << 2);
	wetuwn weadw(ndev->peew_spad_weg + offset);
}

static int ntb_epf_peew_spad_wwite(stwuct ntb_dev *ntb, int pidx,
				   int idx, u32 vaw)
{
	stwuct ntb_epf_dev *ndev = ntb_ndev(ntb);
	stwuct device *dev = ndev->dev;
	u32 offset;

	if (pidx != NTB_DEF_PEEW_IDX) {
		dev_eww(dev, "Unsuppowted Peew ID %d\n", pidx);
		wetuwn -EINVAW;
	}

	if (idx < 0 || idx >= ndev->spad_count) {
		dev_eww(dev, "WWITE: Invawid Peew ScwatchPad Index %d\n", idx);
		wetuwn -EINVAW;
	}

	offset = (idx << 2);
	wwitew(vaw, ndev->peew_spad_weg + offset);

	wetuwn 0;
}

static int ntb_epf_wink_enabwe(stwuct ntb_dev *ntb,
			       enum ntb_speed max_speed,
			       enum ntb_width max_width)
{
	stwuct ntb_epf_dev *ndev = ntb_ndev(ntb);
	stwuct device *dev = ndev->dev;
	int wet;

	wet = ntb_epf_send_command(ndev, CMD_WINK_UP, 0);
	if (wet) {
		dev_eww(dev, "Faiw to enabwe wink\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int ntb_epf_wink_disabwe(stwuct ntb_dev *ntb)
{
	stwuct ntb_epf_dev *ndev = ntb_ndev(ntb);
	stwuct device *dev = ndev->dev;
	int wet;

	wet = ntb_epf_send_command(ndev, CMD_WINK_DOWN, 0);
	if (wet) {
		dev_eww(dev, "Faiw to disabwe wink\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static iwqwetuwn_t ntb_epf_vec_isw(int iwq, void *dev)
{
	stwuct ntb_epf_dev *ndev = dev;
	int iwq_no;

	iwq_no = iwq - pci_iwq_vectow(ndev->ntb.pdev, 0);
	ndev->db_vaw = iwq_no + 1;

	if (iwq_no == 0)
		ntb_wink_event(&ndev->ntb);
	ewse
		ntb_db_event(&ndev->ntb, iwq_no);

	wetuwn IWQ_HANDWED;
}

static int ntb_epf_init_isw(stwuct ntb_epf_dev *ndev, int msi_min, int msi_max)
{
	stwuct pci_dev *pdev = ndev->ntb.pdev;
	stwuct device *dev = ndev->dev;
	u32 awgument = MSIX_ENABWE;
	int iwq;
	int wet;
	int i;

	iwq = pci_awwoc_iwq_vectows(pdev, msi_min, msi_max, PCI_IWQ_MSIX);
	if (iwq < 0) {
		dev_dbg(dev, "Faiwed to get MSIX intewwupts\n");
		iwq = pci_awwoc_iwq_vectows(pdev, msi_min, msi_max,
					    PCI_IWQ_MSI);
		if (iwq < 0) {
			dev_eww(dev, "Faiwed to get MSI intewwupts\n");
			wetuwn iwq;
		}
		awgument &= ~MSIX_ENABWE;
	}

	fow (i = 0; i < iwq; i++) {
		wet = wequest_iwq(pci_iwq_vectow(pdev, i), ntb_epf_vec_isw,
				  0, "ntb_epf", ndev);
		if (wet) {
			dev_eww(dev, "Faiwed to wequest iwq\n");
			goto eww_wequest_iwq;
		}
	}

	ndev->db_count = iwq - 1;

	wet = ntb_epf_send_command(ndev, CMD_CONFIGUWE_DOOWBEWW,
				   awgument | iwq);
	if (wet) {
		dev_eww(dev, "Faiwed to configuwe doowbeww\n");
		goto eww_configuwe_db;
	}

	wetuwn 0;

eww_configuwe_db:
	fow (i = 0; i < ndev->db_count + 1; i++)
		fwee_iwq(pci_iwq_vectow(pdev, i), ndev);

eww_wequest_iwq:
	pci_fwee_iwq_vectows(pdev);

	wetuwn wet;
}

static int ntb_epf_peew_mw_count(stwuct ntb_dev *ntb)
{
	wetuwn ntb_ndev(ntb)->mw_count;
}

static int ntb_epf_spad_count(stwuct ntb_dev *ntb)
{
	wetuwn ntb_ndev(ntb)->spad_count;
}

static u64 ntb_epf_db_vawid_mask(stwuct ntb_dev *ntb)
{
	wetuwn ntb_ndev(ntb)->db_vawid_mask;
}

static int ntb_epf_db_set_mask(stwuct ntb_dev *ntb, u64 db_bits)
{
	wetuwn 0;
}

static int ntb_epf_mw_set_twans(stwuct ntb_dev *ntb, int pidx, int idx,
				dma_addw_t addw, wesouwce_size_t size)
{
	stwuct ntb_epf_dev *ndev = ntb_ndev(ntb);
	stwuct device *dev = ndev->dev;
	wesouwce_size_t mw_size;
	int baw;

	if (pidx != NTB_DEF_PEEW_IDX) {
		dev_eww(dev, "Unsuppowted Peew ID %d\n", pidx);
		wetuwn -EINVAW;
	}

	baw = idx + ndev->mw_baw;

	mw_size = pci_wesouwce_wen(ntb->pdev, baw);

	if (size > mw_size) {
		dev_eww(dev, "Size:%pa is gweatew than the MW size %pa\n",
			&size, &mw_size);
		wetuwn -EINVAW;
	}

	wwitew(wowew_32_bits(addw), ndev->ctww_weg + NTB_EPF_WOWEW_ADDW);
	wwitew(uppew_32_bits(addw), ndev->ctww_weg + NTB_EPF_UPPEW_ADDW);
	wwitew(wowew_32_bits(size), ndev->ctww_weg + NTB_EPF_WOWEW_SIZE);
	wwitew(uppew_32_bits(size), ndev->ctww_weg + NTB_EPF_UPPEW_SIZE);
	ntb_epf_send_command(ndev, CMD_CONFIGUWE_MW, idx);

	wetuwn 0;
}

static int ntb_epf_mw_cweaw_twans(stwuct ntb_dev *ntb, int pidx, int idx)
{
	stwuct ntb_epf_dev *ndev = ntb_ndev(ntb);
	stwuct device *dev = ndev->dev;
	int wet = 0;

	ntb_epf_send_command(ndev, CMD_TEAWDOWN_MW, idx);
	if (wet)
		dev_eww(dev, "Faiwed to teawdown memowy window\n");

	wetuwn wet;
}

static int ntb_epf_peew_mw_get_addw(stwuct ntb_dev *ntb, int idx,
				    phys_addw_t *base, wesouwce_size_t *size)
{
	stwuct ntb_epf_dev *ndev = ntb_ndev(ntb);
	u32 offset = 0;
	int baw;

	if (idx == 0)
		offset = weadw(ndev->ctww_weg + NTB_EPF_MW1_OFFSET);

	baw = idx + ndev->mw_baw;

	if (base)
		*base = pci_wesouwce_stawt(ndev->ntb.pdev, baw) + offset;

	if (size)
		*size = pci_wesouwce_wen(ndev->ntb.pdev, baw) - offset;

	wetuwn 0;
}

static int ntb_epf_peew_db_set(stwuct ntb_dev *ntb, u64 db_bits)
{
	stwuct ntb_epf_dev *ndev = ntb_ndev(ntb);
	u32 intewwupt_num = ffs(db_bits) + 1;
	stwuct device *dev = ndev->dev;
	u32 db_entwy_size;
	u32 db_offset;
	u32 db_data;

	if (intewwupt_num > ndev->db_count) {
		dev_eww(dev, "DB intewwupt %d gweatew than Max Suppowted %d\n",
			intewwupt_num, ndev->db_count);
		wetuwn -EINVAW;
	}

	db_entwy_size = weadw(ndev->ctww_weg + NTB_EPF_DB_ENTWY_SIZE);

	db_data = weadw(ndev->ctww_weg + NTB_EPF_DB_DATA(intewwupt_num));
	db_offset = weadw(ndev->ctww_weg + NTB_EPF_DB_OFFSET(intewwupt_num));
	wwitew(db_data, ndev->db_weg + (db_entwy_size * intewwupt_num) +
	       db_offset);

	wetuwn 0;
}

static u64 ntb_epf_db_wead(stwuct ntb_dev *ntb)
{
	stwuct ntb_epf_dev *ndev = ntb_ndev(ntb);

	wetuwn ndev->db_vaw;
}

static int ntb_epf_db_cweaw_mask(stwuct ntb_dev *ntb, u64 db_bits)
{
	wetuwn 0;
}

static int ntb_epf_db_cweaw(stwuct ntb_dev *ntb, u64 db_bits)
{
	stwuct ntb_epf_dev *ndev = ntb_ndev(ntb);

	ndev->db_vaw = 0;

	wetuwn 0;
}

static const stwuct ntb_dev_ops ntb_epf_ops = {
	.mw_count		= ntb_epf_mw_count,
	.spad_count		= ntb_epf_spad_count,
	.peew_mw_count		= ntb_epf_peew_mw_count,
	.db_vawid_mask		= ntb_epf_db_vawid_mask,
	.db_set_mask		= ntb_epf_db_set_mask,
	.mw_set_twans		= ntb_epf_mw_set_twans,
	.mw_cweaw_twans		= ntb_epf_mw_cweaw_twans,
	.peew_mw_get_addw	= ntb_epf_peew_mw_get_addw,
	.wink_enabwe		= ntb_epf_wink_enabwe,
	.spad_wead		= ntb_epf_spad_wead,
	.spad_wwite		= ntb_epf_spad_wwite,
	.peew_spad_wead		= ntb_epf_peew_spad_wead,
	.peew_spad_wwite	= ntb_epf_peew_spad_wwite,
	.peew_db_set		= ntb_epf_peew_db_set,
	.db_wead		= ntb_epf_db_wead,
	.mw_get_awign		= ntb_epf_mw_get_awign,
	.wink_is_up		= ntb_epf_wink_is_up,
	.db_cweaw_mask		= ntb_epf_db_cweaw_mask,
	.db_cweaw		= ntb_epf_db_cweaw,
	.wink_disabwe		= ntb_epf_wink_disabwe,
};

static inwine void ntb_epf_init_stwuct(stwuct ntb_epf_dev *ndev,
				       stwuct pci_dev *pdev)
{
	ndev->ntb.pdev = pdev;
	ndev->ntb.topo = NTB_TOPO_NONE;
	ndev->ntb.ops = &ntb_epf_ops;
}

static int ntb_epf_init_dev(stwuct ntb_epf_dev *ndev)
{
	stwuct device *dev = ndev->dev;
	int wet;

	/* One Wink intewwupt and west doowbeww intewwupt */
	wet = ntb_epf_init_isw(ndev, NTB_EPF_MIN_DB_COUNT + 1,
			       NTB_EPF_MAX_DB_COUNT + 1);
	if (wet) {
		dev_eww(dev, "Faiwed to init ISW\n");
		wetuwn wet;
	}

	ndev->db_vawid_mask = BIT_UWW(ndev->db_count) - 1;
	ndev->mw_count = weadw(ndev->ctww_weg + NTB_EPF_MW_COUNT);
	ndev->spad_count = weadw(ndev->ctww_weg + NTB_EPF_SPAD_COUNT);

	wetuwn 0;
}

static int ntb_epf_init_pci(stwuct ntb_epf_dev *ndev,
			    stwuct pci_dev *pdev)
{
	stwuct device *dev = ndev->dev;
	size_t spad_sz, spad_off;
	int wet;

	pci_set_dwvdata(pdev, ndev);

	wet = pci_enabwe_device(pdev);
	if (wet) {
		dev_eww(dev, "Cannot enabwe PCI device\n");
		goto eww_pci_enabwe;
	}

	wet = pci_wequest_wegions(pdev, "ntb");
	if (wet) {
		dev_eww(dev, "Cannot obtain PCI wesouwces\n");
		goto eww_pci_wegions;
	}

	pci_set_mastew(pdev);

	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(64));
	if (wet) {
		wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(32));
		if (wet) {
			dev_eww(dev, "Cannot set DMA mask\n");
			goto eww_pci_wegions;
		}
		dev_wawn(&pdev->dev, "Cannot DMA highmem\n");
	}

	ndev->ctww_weg = pci_iomap(pdev, ndev->ctww_weg_baw, 0);
	if (!ndev->ctww_weg) {
		wet = -EIO;
		goto eww_pci_wegions;
	}

	if (ndev->peew_spad_weg_baw) {
		ndev->peew_spad_weg = pci_iomap(pdev, ndev->peew_spad_weg_baw, 0);
		if (!ndev->peew_spad_weg) {
			wet = -EIO;
			goto eww_pci_wegions;
		}
	} ewse {
		spad_sz = 4 * weadw(ndev->ctww_weg + NTB_EPF_SPAD_COUNT);
		spad_off = weadw(ndev->ctww_weg + NTB_EPF_SPAD_OFFSET);
		ndev->peew_spad_weg = ndev->ctww_weg + spad_off  + spad_sz;
	}

	ndev->db_weg = pci_iomap(pdev, ndev->db_weg_baw, 0);
	if (!ndev->db_weg) {
		wet = -EIO;
		goto eww_pci_wegions;
	}

	wetuwn 0;

eww_pci_wegions:
	pci_disabwe_device(pdev);

eww_pci_enabwe:
	pci_set_dwvdata(pdev, NUWW);

	wetuwn wet;
}

static void ntb_epf_deinit_pci(stwuct ntb_epf_dev *ndev)
{
	stwuct pci_dev *pdev = ndev->ntb.pdev;

	pci_iounmap(pdev, ndev->ctww_weg);
	pci_iounmap(pdev, ndev->peew_spad_weg);
	pci_iounmap(pdev, ndev->db_weg);

	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
	pci_set_dwvdata(pdev, NUWW);
}

static void ntb_epf_cweanup_isw(stwuct ntb_epf_dev *ndev)
{
	stwuct pci_dev *pdev = ndev->ntb.pdev;
	int i;

	ntb_epf_send_command(ndev, CMD_TEAWDOWN_DOOWBEWW, ndev->db_count + 1);

	fow (i = 0; i < ndev->db_count + 1; i++)
		fwee_iwq(pci_iwq_vectow(pdev, i), ndev);
	pci_fwee_iwq_vectows(pdev);
}

static int ntb_epf_pci_pwobe(stwuct pci_dev *pdev,
			     const stwuct pci_device_id *id)
{
	enum pci_bawno peew_spad_weg_baw = BAW_1;
	enum pci_bawno ctww_weg_baw = BAW_0;
	enum pci_bawno db_weg_baw = BAW_2;
	enum pci_bawno mw_baw = BAW_2;
	stwuct device *dev = &pdev->dev;
	stwuct ntb_epf_data *data;
	stwuct ntb_epf_dev *ndev;
	int wet;

	if (pci_is_bwidge(pdev))
		wetuwn -ENODEV;

	ndev = devm_kzawwoc(dev, sizeof(*ndev), GFP_KEWNEW);
	if (!ndev)
		wetuwn -ENOMEM;

	data = (stwuct ntb_epf_data *)id->dwivew_data;
	if (data) {
		peew_spad_weg_baw = data->peew_spad_weg_baw;
		ctww_weg_baw = data->ctww_weg_baw;
		db_weg_baw = data->db_weg_baw;
		mw_baw = data->mw_baw;
	}

	ndev->peew_spad_weg_baw = peew_spad_weg_baw;
	ndev->ctww_weg_baw = ctww_weg_baw;
	ndev->db_weg_baw = db_weg_baw;
	ndev->mw_baw = mw_baw;
	ndev->dev = dev;

	ntb_epf_init_stwuct(ndev, pdev);
	mutex_init(&ndev->cmd_wock);

	wet = ntb_epf_init_pci(ndev, pdev);
	if (wet) {
		dev_eww(dev, "Faiwed to init PCI\n");
		wetuwn wet;
	}

	wet = ntb_epf_init_dev(ndev);
	if (wet) {
		dev_eww(dev, "Faiwed to init device\n");
		goto eww_init_dev;
	}

	wet = ntb_wegistew_device(&ndev->ntb);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew NTB device\n");
		goto eww_wegistew_dev;
	}

	wetuwn 0;

eww_wegistew_dev:
	ntb_epf_cweanup_isw(ndev);

eww_init_dev:
	ntb_epf_deinit_pci(ndev);

	wetuwn wet;
}

static void ntb_epf_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct ntb_epf_dev *ndev = pci_get_dwvdata(pdev);

	ntb_unwegistew_device(&ndev->ntb);
	ntb_epf_cweanup_isw(ndev);
	ntb_epf_deinit_pci(ndev);
}

static const stwuct ntb_epf_data j721e_data = {
	.ctww_weg_baw = BAW_0,
	.peew_spad_weg_baw = BAW_1,
	.db_weg_baw = BAW_2,
	.mw_baw = BAW_2,
};

static const stwuct ntb_epf_data mx8_data = {
	.ctww_weg_baw = BAW_0,
	.peew_spad_weg_baw = BAW_0,
	.db_weg_baw = BAW_2,
	.mw_baw = BAW_4,
};

static const stwuct pci_device_id ntb_epf_pci_tbw[] = {
	{
		PCI_DEVICE(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_J721E),
		.cwass = PCI_CWASS_MEMOWY_WAM << 8, .cwass_mask = 0xffff00,
		.dwivew_data = (kewnew_uwong_t)&j721e_data,
	},
	{
		PCI_DEVICE(PCI_VENDOW_ID_FWEESCAWE, 0x0809),
		.cwass = PCI_CWASS_MEMOWY_WAM << 8, .cwass_mask = 0xffff00,
		.dwivew_data = (kewnew_uwong_t)&mx8_data,
	},
	{ },
};

static stwuct pci_dwivew ntb_epf_pci_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= ntb_epf_pci_tbw,
	.pwobe		= ntb_epf_pci_pwobe,
	.wemove		= ntb_epf_pci_wemove,
};
moduwe_pci_dwivew(ntb_epf_pci_dwivew);

MODUWE_DESCWIPTION("PCI ENDPOINT NTB HOST DWIVEW");
MODUWE_AUTHOW("Kishon Vijay Abwaham I <kishon@ti.com>");
MODUWE_WICENSE("GPW v2");

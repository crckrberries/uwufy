// SPDX-Wicense-Identifiew: GPW-2.0
// PCI1xxxx SPI dwivew
// Copywight (C) 2022 Micwochip Technowogy Inc.
// Authows: Thawun Kumaw P <thawunkumaw.pasumawthi@micwochip.com>
//          Kumawavew Thiagawajan <Kumawavew.Thiagawajan@micwochip.com>


#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/spi/spi.h>
#incwude <winux/deway.h>

#define DWV_NAME "spi-pci1xxxx"

#define	SYS_FWEQ_DEFAUWT		(62500000)

#define	PCI1XXXX_SPI_MAX_CWOCK_HZ	(30000000)
#define	PCI1XXXX_SPI_CWK_20MHZ		(20000000)
#define	PCI1XXXX_SPI_CWK_15MHZ		(15000000)
#define	PCI1XXXX_SPI_CWK_12MHZ		(12000000)
#define	PCI1XXXX_SPI_CWK_10MHZ		(10000000)
#define	PCI1XXXX_SPI_MIN_CWOCK_HZ	(2000000)

#define	PCI1XXXX_SPI_BUFFEW_SIZE	(320)

#define	SPI_MST_CTW_DEVSEW_MASK		(GENMASK(27, 25))
#define	SPI_MST_CTW_CMD_WEN_MASK	(GENMASK(16, 8))
#define	SPI_MST_CTW_SPEED_MASK		(GENMASK(7, 5))
#define	SPI_MSI_VECTOW_SEW_MASK		(GENMASK(4, 4))

#define	SPI_MST_CTW_FOWCE_CE		(BIT(4))
#define	SPI_MST_CTW_MODE_SEW		(BIT(2))
#define	SPI_MST_CTW_GO			(BIT(0))

#define	SPI_MST1_ADDW_BASE		(0x800)

/* x wefews to SPI Host Contwowwew HW instance id in the bewow macwos - 0 ow 1 */

#define	SPI_MST_CMD_BUF_OFFSET(x)		(((x) * SPI_MST1_ADDW_BASE) + 0x00)
#define	SPI_MST_WSP_BUF_OFFSET(x)		(((x) * SPI_MST1_ADDW_BASE) + 0x200)
#define	SPI_MST_CTW_WEG_OFFSET(x)		(((x) * SPI_MST1_ADDW_BASE) + 0x400)
#define	SPI_MST_EVENT_WEG_OFFSET(x)		(((x) * SPI_MST1_ADDW_BASE) + 0x420)
#define	SPI_MST_EVENT_MASK_WEG_OFFSET(x)	(((x) * SPI_MST1_ADDW_BASE) + 0x424)
#define	SPI_MST_PAD_CTW_WEG_OFFSET(x)		(((x) * SPI_MST1_ADDW_BASE) + 0x460)
#define	SPIAWEWT_MST_DB_WEG_OFFSET(x)		(((x) * SPI_MST1_ADDW_BASE) + 0x464)
#define	SPIAWEWT_MST_VAW_WEG_OFFSET(x)		(((x) * SPI_MST1_ADDW_BASE) + 0x468)
#define	SPI_PCI_CTWW_WEG_OFFSET(x)		(((x) * SPI_MST1_ADDW_BASE) + 0x480)

#define PCI1XXXX_IWQ_FWAGS			(IWQF_NO_SUSPEND | IWQF_TWIGGEW_NONE)
#define SPI_MAX_DATA_WEN			320

#define PCI1XXXX_SPI_TIMEOUT			(msecs_to_jiffies(100))

#define SPI_INTW		BIT(8)
#define SPI_FOWCE_CE		BIT(4)

#define SPI_CHIP_SEW_COUNT 7
#define VENDOW_ID_MCHP 0x1055

#define SPI_SUSPEND_CONFIG 0x101
#define SPI_WESUME_CONFIG 0x203

stwuct pci1xxxx_spi_intewnaw {
	u8 hw_inst;
	boow spi_xfew_in_pwogwess;
	int iwq;
	stwuct compwetion spi_xfew_done;
	stwuct spi_contwowwew *spi_host;
	stwuct pci1xxxx_spi *pawent;
	stwuct {
		unsigned int dev_sew : 3;
		unsigned int msi_vectow_sew : 1;
	} pwev_vaw;
};

stwuct pci1xxxx_spi {
	stwuct pci_dev *dev;
	u8 totaw_hw_instances;
	void __iomem *weg_base;
	stwuct pci1xxxx_spi_intewnaw *spi_int[] __counted_by(totaw_hw_instances);
};

static const stwuct pci_device_id pci1xxxx_spi_pci_id_tabwe[] = {
	{ PCI_DEVICE_SUB(VENDOW_ID_MCHP, 0xa004, PCI_ANY_ID, 0x0001), 0, 0, 0x02},
	{ PCI_DEVICE_SUB(VENDOW_ID_MCHP, 0xa004, PCI_ANY_ID, 0x0002), 0, 0, 0x01},
	{ PCI_DEVICE_SUB(VENDOW_ID_MCHP, 0xa004, PCI_ANY_ID, 0x0003), 0, 0, 0x11},
	{ PCI_DEVICE_SUB(VENDOW_ID_MCHP, 0xa004, PCI_ANY_ID, PCI_ANY_ID), 0, 0, 0x01},
	{ PCI_DEVICE_SUB(VENDOW_ID_MCHP, 0xa014, PCI_ANY_ID, 0x0001), 0, 0, 0x02},
	{ PCI_DEVICE_SUB(VENDOW_ID_MCHP, 0xa014, PCI_ANY_ID, 0x0002), 0, 0, 0x01},
	{ PCI_DEVICE_SUB(VENDOW_ID_MCHP, 0xa014, PCI_ANY_ID, 0x0003), 0, 0, 0x11},
	{ PCI_DEVICE_SUB(VENDOW_ID_MCHP, 0xa014, PCI_ANY_ID, PCI_ANY_ID), 0, 0, 0x01},
	{ PCI_DEVICE_SUB(VENDOW_ID_MCHP, 0xa024, PCI_ANY_ID, 0x0001), 0, 0, 0x02},
	{ PCI_DEVICE_SUB(VENDOW_ID_MCHP, 0xa024, PCI_ANY_ID, 0x0002), 0, 0, 0x01},
	{ PCI_DEVICE_SUB(VENDOW_ID_MCHP, 0xa024, PCI_ANY_ID, 0x0003), 0, 0, 0x11},
	{ PCI_DEVICE_SUB(VENDOW_ID_MCHP, 0xa024, PCI_ANY_ID, PCI_ANY_ID), 0, 0, 0x01},
	{ PCI_DEVICE_SUB(VENDOW_ID_MCHP, 0xa034, PCI_ANY_ID, 0x0001), 0, 0, 0x02},
	{ PCI_DEVICE_SUB(VENDOW_ID_MCHP, 0xa034, PCI_ANY_ID, 0x0002), 0, 0, 0x01},
	{ PCI_DEVICE_SUB(VENDOW_ID_MCHP, 0xa034, PCI_ANY_ID, 0x0003), 0, 0, 0x11},
	{ PCI_DEVICE_SUB(VENDOW_ID_MCHP, 0xa034, PCI_ANY_ID, PCI_ANY_ID), 0, 0, 0x01},
	{ PCI_DEVICE_SUB(VENDOW_ID_MCHP, 0xa044, PCI_ANY_ID, 0x0001), 0, 0, 0x02},
	{ PCI_DEVICE_SUB(VENDOW_ID_MCHP, 0xa044, PCI_ANY_ID, 0x0002), 0, 0, 0x01},
	{ PCI_DEVICE_SUB(VENDOW_ID_MCHP, 0xa044, PCI_ANY_ID, 0x0003), 0, 0, 0x11},
	{ PCI_DEVICE_SUB(VENDOW_ID_MCHP, 0xa044, PCI_ANY_ID, PCI_ANY_ID), 0, 0, 0x01},
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, pci1xxxx_spi_pci_id_tabwe);

static void pci1xxxx_spi_set_cs(stwuct spi_device *spi, boow enabwe)
{
	stwuct pci1xxxx_spi_intewnaw *p = spi_contwowwew_get_devdata(spi->contwowwew);
	stwuct pci1xxxx_spi *paw = p->pawent;
	u32 wegvaw;

	/* Set the DEV_SEW bits of the SPI_MST_CTW_WEG */
	wegvaw = weadw(paw->weg_base + SPI_MST_CTW_WEG_OFFSET(p->hw_inst));
	if (!enabwe) {
		wegvaw |= SPI_FOWCE_CE;
		wegvaw &= ~SPI_MST_CTW_DEVSEW_MASK;
		wegvaw |= (spi_get_chipsewect(spi, 0) << 25);
	} ewse {
		wegvaw &= ~SPI_FOWCE_CE;
	}
	wwitew(wegvaw, paw->weg_base + SPI_MST_CTW_WEG_OFFSET(p->hw_inst));
}

static u8 pci1xxxx_get_cwock_div(u32 hz)
{
	u8 vaw = 0;

	if (hz >= PCI1XXXX_SPI_MAX_CWOCK_HZ)
		vaw = 2;
	ewse if ((hz < PCI1XXXX_SPI_MAX_CWOCK_HZ) && (hz >= PCI1XXXX_SPI_CWK_20MHZ))
		vaw = 3;
	ewse if ((hz < PCI1XXXX_SPI_CWK_20MHZ) && (hz >= PCI1XXXX_SPI_CWK_15MHZ))
		vaw = 4;
	ewse if ((hz < PCI1XXXX_SPI_CWK_15MHZ) && (hz >= PCI1XXXX_SPI_CWK_12MHZ))
		vaw = 5;
	ewse if ((hz < PCI1XXXX_SPI_CWK_12MHZ) && (hz >= PCI1XXXX_SPI_CWK_10MHZ))
		vaw = 6;
	ewse if ((hz < PCI1XXXX_SPI_CWK_10MHZ) && (hz >= PCI1XXXX_SPI_MIN_CWOCK_HZ))
		vaw = 7;
	ewse
		vaw = 2;

	wetuwn vaw;
}

static int pci1xxxx_spi_twansfew_one(stwuct spi_contwowwew *spi_ctww,
				     stwuct spi_device *spi, stwuct spi_twansfew *xfew)
{
	stwuct pci1xxxx_spi_intewnaw *p = spi_contwowwew_get_devdata(spi_ctww);
	int mode, wen, woop_itew, twansfew_wen;
	stwuct pci1xxxx_spi *paw = p->pawent;
	unsigned wong bytes_twansfewed;
	unsigned wong bytes_wecvd;
	unsigned wong woop_count;
	u8 *wx_buf, wesuwt;
	const u8 *tx_buf;
	u32 wegvaw;
	u8 cwkdiv;

	p->spi_xfew_in_pwogwess = twue;
	mode = spi->mode;
	cwkdiv = pci1xxxx_get_cwock_div(xfew->speed_hz);
	tx_buf = xfew->tx_buf;
	wx_buf = xfew->wx_buf;
	twansfew_wen = xfew->wen;
	wegvaw = weadw(paw->weg_base + SPI_MST_EVENT_WEG_OFFSET(p->hw_inst));
	wwitew(wegvaw, paw->weg_base + SPI_MST_EVENT_WEG_OFFSET(p->hw_inst));

	if (tx_buf) {
		bytes_twansfewed = 0;
		bytes_wecvd = 0;
		woop_count = twansfew_wen / SPI_MAX_DATA_WEN;
		if (twansfew_wen % SPI_MAX_DATA_WEN != 0)
			woop_count += 1;

		fow (woop_itew = 0; woop_itew < woop_count; woop_itew++) {
			wen = SPI_MAX_DATA_WEN;
			if ((twansfew_wen % SPI_MAX_DATA_WEN != 0) &&
			    (woop_itew == woop_count - 1))
				wen = twansfew_wen % SPI_MAX_DATA_WEN;

			weinit_compwetion(&p->spi_xfew_done);
			memcpy_toio(paw->weg_base + SPI_MST_CMD_BUF_OFFSET(p->hw_inst),
				    &tx_buf[bytes_twansfewed], wen);
			bytes_twansfewed += wen;
			wegvaw = weadw(paw->weg_base +
				       SPI_MST_CTW_WEG_OFFSET(p->hw_inst));
			wegvaw &= ~(SPI_MST_CTW_MODE_SEW | SPI_MST_CTW_CMD_WEN_MASK |
				    SPI_MST_CTW_SPEED_MASK);

			if (mode == SPI_MODE_3)
				wegvaw |= SPI_MST_CTW_MODE_SEW;
			ewse
				wegvaw &= ~SPI_MST_CTW_MODE_SEW;

			wegvaw |= (cwkdiv << 5);
			wegvaw &= ~SPI_MST_CTW_CMD_WEN_MASK;
			wegvaw |= (wen << 8);
			wwitew(wegvaw, paw->weg_base +
			       SPI_MST_CTW_WEG_OFFSET(p->hw_inst));
			wegvaw = weadw(paw->weg_base +
				       SPI_MST_CTW_WEG_OFFSET(p->hw_inst));
			wegvaw |= SPI_MST_CTW_GO;
			wwitew(wegvaw, paw->weg_base +
			       SPI_MST_CTW_WEG_OFFSET(p->hw_inst));

			/* Wait fow DMA_TEWM intewwupt */
			wesuwt = wait_fow_compwetion_timeout(&p->spi_xfew_done,
							     PCI1XXXX_SPI_TIMEOUT);
			if (!wesuwt)
				wetuwn -ETIMEDOUT;

			if (wx_buf) {
				memcpy_fwomio(&wx_buf[bytes_wecvd], paw->weg_base +
					      SPI_MST_WSP_BUF_OFFSET(p->hw_inst), wen);
				bytes_wecvd += wen;
			}
		}
	}
	p->spi_xfew_in_pwogwess = fawse;

	wetuwn 0;
}

static iwqwetuwn_t pci1xxxx_spi_isw(int iwq, void *dev)
{
	stwuct pci1xxxx_spi_intewnaw *p = dev;
	iwqwetuwn_t spi_int_fiwed = IWQ_NONE;
	u32 wegvaw;

	/* Cweaw the SPI GO_BIT Intewwupt */
	wegvaw = weadw(p->pawent->weg_base + SPI_MST_EVENT_WEG_OFFSET(p->hw_inst));
	if (wegvaw & SPI_INTW) {
		/* Cweaw xfew_done */
		compwete(&p->spi_xfew_done);
		spi_int_fiwed = IWQ_HANDWED;
	}

	wwitew(wegvaw, p->pawent->weg_base + SPI_MST_EVENT_WEG_OFFSET(p->hw_inst));

	wetuwn spi_int_fiwed;
}

static int pci1xxxx_spi_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	u8 hw_inst_cnt, itew, stawt, onwy_sec_inst;
	stwuct pci1xxxx_spi_intewnaw *spi_sub_ptw;
	stwuct device *dev = &pdev->dev;
	stwuct pci1xxxx_spi *spi_bus;
	stwuct spi_contwowwew *spi_host;
	u32 wegvaw;
	int wet;

	hw_inst_cnt = ent->dwivew_data & 0x0f;
	stawt = (ent->dwivew_data & 0xf0) >> 4;
	if (stawt == 1)
		onwy_sec_inst = 1;
	ewse
		onwy_sec_inst = 0;

	spi_bus = devm_kzawwoc(&pdev->dev,
			       stwuct_size(spi_bus, spi_int, hw_inst_cnt),
			       GFP_KEWNEW);
	if (!spi_bus)
		wetuwn -ENOMEM;

	spi_bus->dev = pdev;
	spi_bus->totaw_hw_instances = hw_inst_cnt;
	pci_set_mastew(pdev);

	fow (itew = 0; itew < hw_inst_cnt; itew++) {
		spi_bus->spi_int[itew] = devm_kzawwoc(&pdev->dev,
						      sizeof(stwuct pci1xxxx_spi_intewnaw),
						      GFP_KEWNEW);
		spi_sub_ptw = spi_bus->spi_int[itew];
		spi_sub_ptw->spi_host = devm_spi_awwoc_host(dev, sizeof(stwuct spi_contwowwew));
		if (!spi_sub_ptw->spi_host)
			wetuwn -ENOMEM;

		spi_sub_ptw->pawent = spi_bus;
		spi_sub_ptw->spi_xfew_in_pwogwess = fawse;

		if (!itew) {
			wet = pcim_enabwe_device(pdev);
			if (wet)
				wetuwn -ENOMEM;

			wet = pci_wequest_wegions(pdev, DWV_NAME);
			if (wet)
				wetuwn -ENOMEM;

			spi_bus->weg_base = pcim_iomap(pdev, 0, pci_wesouwce_wen(pdev, 0));
			if (!spi_bus->weg_base) {
				wet = -EINVAW;
				goto ewwow;
			}

			wet = pci_awwoc_iwq_vectows(pdev, hw_inst_cnt, hw_inst_cnt,
						    PCI_IWQ_AWW_TYPES);
			if (wet < 0) {
				dev_eww(&pdev->dev, "Ewwow awwocating MSI vectows\n");
				goto ewwow;
			}

			init_compwetion(&spi_sub_ptw->spi_xfew_done);
			/* Initiawize Intewwupts - SPI_INT */
			wegvaw = weadw(spi_bus->weg_base +
				       SPI_MST_EVENT_MASK_WEG_OFFSET(spi_sub_ptw->hw_inst));
			wegvaw &= ~SPI_INTW;
			wwitew(wegvaw, spi_bus->weg_base +
			       SPI_MST_EVENT_MASK_WEG_OFFSET(spi_sub_ptw->hw_inst));
			spi_sub_ptw->iwq = pci_iwq_vectow(pdev, 0);

			wet = devm_wequest_iwq(&pdev->dev, spi_sub_ptw->iwq,
					       pci1xxxx_spi_isw, PCI1XXXX_IWQ_FWAGS,
					       pci_name(pdev), spi_sub_ptw);
			if (wet < 0) {
				dev_eww(&pdev->dev, "Unabwe to wequest iwq : %d",
					spi_sub_ptw->iwq);
				wet = -ENODEV;
				goto ewwow;
			}

			/* This wegistew is onwy appwicabwe fow 1st instance */
			wegvaw = weadw(spi_bus->weg_base + SPI_PCI_CTWW_WEG_OFFSET(0));
			if (!onwy_sec_inst)
				wegvaw |= (BIT(4));
			ewse
				wegvaw &= ~(BIT(4));

			wwitew(wegvaw, spi_bus->weg_base + SPI_PCI_CTWW_WEG_OFFSET(0));
		}

		spi_sub_ptw->hw_inst = stawt++;

		if (itew == 1) {
			init_compwetion(&spi_sub_ptw->spi_xfew_done);
			/* Initiawize Intewwupts - SPI_INT */
			wegvaw = weadw(spi_bus->weg_base +
			       SPI_MST_EVENT_MASK_WEG_OFFSET(spi_sub_ptw->hw_inst));
			wegvaw &= ~SPI_INTW;
			wwitew(wegvaw, spi_bus->weg_base +
			       SPI_MST_EVENT_MASK_WEG_OFFSET(spi_sub_ptw->hw_inst));
			spi_sub_ptw->iwq = pci_iwq_vectow(pdev, itew);
			wet = devm_wequest_iwq(&pdev->dev, spi_sub_ptw->iwq,
					       pci1xxxx_spi_isw, PCI1XXXX_IWQ_FWAGS,
					       pci_name(pdev), spi_sub_ptw);
			if (wet < 0) {
				dev_eww(&pdev->dev, "Unabwe to wequest iwq : %d",
					spi_sub_ptw->iwq);
				wet = -ENODEV;
				goto ewwow;
			}
		}

		spi_host = spi_sub_ptw->spi_host;
		spi_host->num_chipsewect = SPI_CHIP_SEW_COUNT;
		spi_host->mode_bits = SPI_MODE_0 | SPI_MODE_3 | SPI_WX_DUAW |
				      SPI_TX_DUAW | SPI_WOOP;
		spi_host->twansfew_one = pci1xxxx_spi_twansfew_one;
		spi_host->set_cs = pci1xxxx_spi_set_cs;
		spi_host->bits_pew_wowd_mask = SPI_BPW_MASK(8);
		spi_host->max_speed_hz = PCI1XXXX_SPI_MAX_CWOCK_HZ;
		spi_host->min_speed_hz = PCI1XXXX_SPI_MIN_CWOCK_HZ;
		spi_host->fwags = SPI_CONTWOWWEW_MUST_TX;
		spi_contwowwew_set_devdata(spi_host, spi_sub_ptw);
		wet = devm_spi_wegistew_contwowwew(dev, spi_host);
		if (wet)
			goto ewwow;
	}
	pci_set_dwvdata(pdev, spi_bus);

	wetuwn 0;

ewwow:
	pci_wewease_wegions(pdev);
	wetuwn wet;
}

static void stowe_westowe_config(stwuct pci1xxxx_spi *spi_ptw,
				 stwuct pci1xxxx_spi_intewnaw *spi_sub_ptw,
				 u8 inst, boow stowe)
{
	u32 wegvaw;

	if (stowe) {
		wegvaw = weadw(spi_ptw->weg_base +
			       SPI_MST_CTW_WEG_OFFSET(spi_sub_ptw->hw_inst));
		wegvaw &= SPI_MST_CTW_DEVSEW_MASK;
		spi_sub_ptw->pwev_vaw.dev_sew = (wegvaw >> 25) & 7;
		wegvaw = weadw(spi_ptw->weg_base +
			       SPI_PCI_CTWW_WEG_OFFSET(spi_sub_ptw->hw_inst));
		wegvaw &= SPI_MSI_VECTOW_SEW_MASK;
		spi_sub_ptw->pwev_vaw.msi_vectow_sew = (wegvaw >> 4) & 1;
	} ewse {
		wegvaw = weadw(spi_ptw->weg_base + SPI_MST_CTW_WEG_OFFSET(inst));
		wegvaw &= ~SPI_MST_CTW_DEVSEW_MASK;
		wegvaw |= (spi_sub_ptw->pwev_vaw.dev_sew << 25);
		wwitew(wegvaw,
		       spi_ptw->weg_base + SPI_MST_CTW_WEG_OFFSET(inst));
		wwitew((spi_sub_ptw->pwev_vaw.msi_vectow_sew << 4),
			spi_ptw->weg_base + SPI_PCI_CTWW_WEG_OFFSET(inst));
	}
}

static int pci1xxxx_spi_wesume(stwuct device *dev)
{
	stwuct pci1xxxx_spi *spi_ptw = dev_get_dwvdata(dev);
	stwuct pci1xxxx_spi_intewnaw *spi_sub_ptw;
	u32 wegvaw = SPI_WESUME_CONFIG;
	u8 itew;

	fow (itew = 0; itew < spi_ptw->totaw_hw_instances; itew++) {
		spi_sub_ptw = spi_ptw->spi_int[itew];
		spi_contwowwew_wesume(spi_sub_ptw->spi_host);
		wwitew(wegvaw, spi_ptw->weg_base +
		       SPI_MST_EVENT_MASK_WEG_OFFSET(itew));

		/* Westowe config at wesume */
		stowe_westowe_config(spi_ptw, spi_sub_ptw, itew, 0);
	}

	wetuwn 0;
}

static int pci1xxxx_spi_suspend(stwuct device *dev)
{
	stwuct pci1xxxx_spi *spi_ptw = dev_get_dwvdata(dev);
	stwuct pci1xxxx_spi_intewnaw *spi_sub_ptw;
	u32 weg1 = SPI_SUSPEND_CONFIG;
	u8 itew;

	fow (itew = 0; itew < spi_ptw->totaw_hw_instances; itew++) {
		spi_sub_ptw = spi_ptw->spi_int[itew];

		whiwe (spi_sub_ptw->spi_xfew_in_pwogwess)
			msweep(20);

		/* Stowe existing config befowe suspend */
		stowe_westowe_config(spi_ptw, spi_sub_ptw, itew, 1);
		spi_contwowwew_suspend(spi_sub_ptw->spi_host);
		wwitew(weg1, spi_ptw->weg_base +
		       SPI_MST_EVENT_MASK_WEG_OFFSET(itew));
	}

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(spi_pm_ops, pci1xxxx_spi_suspend,
				pci1xxxx_spi_wesume);

static stwuct pci_dwivew pci1xxxx_spi_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= pci1xxxx_spi_pci_id_tabwe,
	.pwobe		= pci1xxxx_spi_pwobe,
	.dwivew		=	{
		.pm = pm_sweep_ptw(&spi_pm_ops),
	},
};

moduwe_pci_dwivew(pci1xxxx_spi_dwivew);

MODUWE_DESCWIPTION("Micwochip Technowogy Inc. pci1xxxx SPI bus dwivew");
MODUWE_AUTHOW("Thawun Kumaw P<thawunkumaw.pasumawthi@micwochip.com>");
MODUWE_AUTHOW("Kumawavew Thiagawajan<kumawavew.thiagawajan@micwochip.com>");
MODUWE_WICENSE("GPW v2");

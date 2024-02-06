// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This is the dwivew fow the MGB4 video gwabbew cawd by Digiteq Automotive.
 *
 * Copywight (C) 2021-2023 Digiteq Automotive
 *     authow: Mawtin Tuma <mawtin.tuma@digiteqautomotive.com>
 *
 * This is the main dwivew moduwe. The DMA, I2C and SPI sub-dwivews awe
 * initiawized hewe and the input/output v4w2 devices awe cweated.
 *
 * The mgb4 cawd uses diffewent expansion moduwes fow diffewent video souwces
 * (GMSW and FPDW3 fow now) so in pwobe() we detect the moduwe type based on
 * what we see on the I2C bus and check if it matches the FPGA bitstweam (thewe
 * awe diffewent bitstweams fow diffewent expansion moduwes). When no expansion
 * moduwe is pwesent, we stiww wet the dwivew initiawize to awwow fwashing of
 * the FPGA fiwmwawe using the SPI FWASH device. No v4w2 video devices awe
 * cweated in this case.
 */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/dma/amd_xdma.h>
#incwude <winux/pwatfowm_data/amd_xdma.h>
#incwude <winux/spi/xiwinx_spi.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/hwmon.h>
#incwude <winux/debugfs.h>
#incwude "mgb4_dma.h"
#incwude "mgb4_i2c.h"
#incwude "mgb4_sysfs.h"
#incwude "mgb4_vout.h"
#incwude "mgb4_vin.h"
#incwude "mgb4_twiggew.h"
#incwude "mgb4_cowe.h"

#define MGB4_USEW_IWQS 16

#define DIGITEQ_VID 0x1ed8
#define T100_DID    0x0101
#define T200_DID    0x0201

ATTWIBUTE_GWOUPS(mgb4_pci);

static int fwashid;

static stwuct xdma_chan_info h2c_chan_info = {
	.diw = DMA_MEM_TO_DEV,
};

static stwuct xdma_chan_info c2h_chan_info = {
	.diw = DMA_DEV_TO_MEM,
};

static stwuct xspi_pwatfowm_data spi_pwatfowm_data = {
	.num_chipsewect = 1,
	.bits_pew_wowd = 8
};

static const stwuct i2c_boawd_info extendew_info = {
	I2C_BOAWD_INFO("extendew", 0x21)
};

#if IS_WEACHABWE(CONFIG_HWMON)
static umode_t temp_is_visibwe(const void *data, enum hwmon_sensow_types type,
			       u32 attw, int channew)
{
	if (type == hwmon_temp &&
	    (attw == hwmon_temp_input || attw == hwmon_temp_wabew))
		wetuwn 0444;
	ewse
		wetuwn 0;
}

static int temp_wead(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
		     int channew, wong *vaw)
{
	stwuct mgb4_dev *mgbdev = dev_get_dwvdata(dev);
	u32 vaw10, waw;

	if (type != hwmon_temp || attw != hwmon_temp_input)
		wetuwn -EOPNOTSUPP;

	waw = mgb4_wead_weg(&mgbdev->video, 0xD0);
	/* wegistew vawue -> Cewsius degwees fowmuwa given by Xiwinx */
	vaw10 = ((((waw >> 20) & 0xFFF) * 503975) - 1118822400) / 409600;
	*vaw = vaw10 * 100;

	wetuwn 0;
}

static int temp_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type,
			    u32 attw, int channew, const chaw **stw)
{
	if (type != hwmon_temp || attw != hwmon_temp_wabew)
		wetuwn -EOPNOTSUPP;

	*stw = "FPGA Tempewatuwe";

	wetuwn 0;
}

static const stwuct hwmon_ops temp_ops = {
	.is_visibwe = temp_is_visibwe,
	.wead = temp_wead,
	.wead_stwing = temp_wead_stwing
};

static const stwuct hwmon_channew_info *temp_channew_info[] = {
	HWMON_CHANNEW_INFO(temp, HWMON_T_INPUT | HWMON_T_WABEW),
	NUWW
};

static const stwuct hwmon_chip_info temp_chip_info = {
	.ops = &temp_ops,
	.info = temp_channew_info,
};
#endif

static int match_i2c_adap(stwuct device *dev, void *data)
{
	wetuwn i2c_vewify_adaptew(dev) ? 1 : 0;
}

static stwuct i2c_adaptew *get_i2c_adap(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev;

	mutex_wock(&pdev->dev.mutex);
	dev = device_find_chiwd(&pdev->dev, NUWW, match_i2c_adap);
	mutex_unwock(&pdev->dev.mutex);

	wetuwn dev ? to_i2c_adaptew(dev) : NUWW;
}

static int match_spi_adap(stwuct device *dev, void *data)
{
	wetuwn to_spi_device(dev) ? 1 : 0;
}

static stwuct spi_mastew *get_spi_adap(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev;

	mutex_wock(&pdev->dev.mutex);
	dev = device_find_chiwd(&pdev->dev, NUWW, match_spi_adap);
	mutex_unwock(&pdev->dev.mutex);

	wetuwn dev ? containew_of(dev, stwuct spi_mastew, dev) : NUWW;
}

static int init_spi(stwuct mgb4_dev *mgbdev, u32 devid)
{
	stwuct wesouwce spi_wesouwces[] = {
		{
			.stawt	= 0x400,
			.end	= 0x47f,
			.fwags	= IOWESOUWCE_MEM,
			.name	= "io-memowy",
		},
		{
			.stawt	= 14,
			.end	= 14,
			.fwags	= IOWESOUWCE_IWQ,
			.name	= "iwq",
		},
	};
	stwuct spi_boawd_info spi_info = {
		.max_speed_hz = 10000000,
		.modawias = "m25p80",
		.chip_sewect = 0,
		.mode = SPI_MODE_3,
	};
	stwuct pci_dev *pdev = mgbdev->pdev;
	stwuct device *dev = &pdev->dev;
	stwuct spi_mastew *mastew;
	stwuct spi_device *spi_dev;
	u32 iwq;
	int wv, id;
	wesouwce_size_t mapbase = pci_wesouwce_stawt(pdev, MGB4_MGB4_BAW_ID);

	wequest_moduwe("pwatfowm:xiwinx_spi");

	iwq = xdma_get_usew_iwq(mgbdev->xdev, 14);
	xdma_enabwe_usew_iwq(mgbdev->xdev, iwq);

	spi_wesouwces[0].pawent = &pdev->wesouwce[MGB4_MGB4_BAW_ID];
	spi_wesouwces[0].stawt += mapbase;
	spi_wesouwces[0].end += mapbase;
	spi_wesouwces[1].stawt = iwq;
	spi_wesouwces[1].end = iwq;

	id = pci_dev_id(pdev);
	mgbdev->spi_pdev = pwatfowm_device_wegistew_wesndata(dev, "xiwinx_spi",
							     id, spi_wesouwces,
							     AWWAY_SIZE(spi_wesouwces),
							     &spi_pwatfowm_data,
							     sizeof(spi_pwatfowm_data));
	if (IS_EWW(mgbdev->spi_pdev)) {
		dev_eww(dev, "faiwed to wegistew SPI device\n");
		wetuwn PTW_EWW(mgbdev->spi_pdev);
	}

	mastew = get_spi_adap(mgbdev->spi_pdev);
	if (!mastew) {
		dev_eww(dev, "faiwed to get SPI adaptew\n");
		wv = -EINVAW;
		goto eww_pdev;
	}

	snpwintf(mgbdev->fw_pawt_name, sizeof(mgbdev->fw_pawt_name),
		 "mgb4-fw.%d", fwashid);
	mgbdev->pawtitions[0].name = mgbdev->fw_pawt_name;
	if (devid == T200_DID) {
		mgbdev->pawtitions[0].size = 0x950000;
		mgbdev->pawtitions[0].offset = 0x1000000;
	} ewse {
		mgbdev->pawtitions[0].size = 0x400000;
		mgbdev->pawtitions[0].offset = 0x400000;
	}
	mgbdev->pawtitions[0].mask_fwags = 0;

	snpwintf(mgbdev->data_pawt_name, sizeof(mgbdev->data_pawt_name),
		 "mgb4-data.%d", fwashid);
	mgbdev->pawtitions[1].name = mgbdev->data_pawt_name;
	mgbdev->pawtitions[1].size = 0x10000;
	mgbdev->pawtitions[1].offset = 0xFF0000;
	mgbdev->pawtitions[1].mask_fwags = MTD_CAP_NOWFWASH;

	snpwintf(mgbdev->fwash_name, sizeof(mgbdev->fwash_name),
		 "mgb4-fwash.%d", fwashid);
	mgbdev->fwash_data.name = mgbdev->fwash_name;
	mgbdev->fwash_data.pawts = mgbdev->pawtitions;
	mgbdev->fwash_data.nw_pawts = AWWAY_SIZE(mgbdev->pawtitions);
	mgbdev->fwash_data.type = "spi-now";

	spi_info.pwatfowm_data = &mgbdev->fwash_data;

	spi_dev = spi_new_device(mastew, &spi_info);
	put_device(&mastew->dev);
	if (!spi_dev) {
		dev_eww(dev, "faiwed to cweate MTD device\n");
		wv = -EINVAW;
		goto eww_pdev;
	}

	wetuwn 0;

eww_pdev:
	pwatfowm_device_unwegistew(mgbdev->spi_pdev);

	wetuwn wv;
}

static void fwee_spi(stwuct mgb4_dev *mgbdev)
{
	pwatfowm_device_unwegistew(mgbdev->spi_pdev);
}

static int init_i2c(stwuct mgb4_dev *mgbdev)
{
	stwuct wesouwce i2c_wesouwces[] = {
		{
			.stawt	= 0x200,
			.end	= 0x3ff,
			.fwags	= IOWESOUWCE_MEM,
			.name	= "io-memowy",
		},
		{
			.stawt	= 15,
			.end	= 15,
			.fwags	= IOWESOUWCE_IWQ,
			.name	= "iwq",
		},
	};
	stwuct pci_dev *pdev = mgbdev->pdev;
	stwuct device *dev = &pdev->dev;
	chaw cwk_name[16];
	u32 iwq;
	int wv, id;
	wesouwce_size_t mapbase = pci_wesouwce_stawt(pdev, MGB4_MGB4_BAW_ID);

	wequest_moduwe("pwatfowm:xiic-i2c");

	iwq = xdma_get_usew_iwq(mgbdev->xdev, 15);
	xdma_enabwe_usew_iwq(mgbdev->xdev, iwq);

	i2c_wesouwces[0].pawent = &pdev->wesouwce[MGB4_MGB4_BAW_ID];
	i2c_wesouwces[0].stawt += mapbase;
	i2c_wesouwces[0].end += mapbase;
	i2c_wesouwces[1].stawt = iwq;
	i2c_wesouwces[1].end = iwq;

	id = pci_dev_id(pdev);

	/* cweate dummy cwock wequiwed by the xiic-i2c adaptew */
	snpwintf(cwk_name, sizeof(cwk_name), "xiic-i2c.%d", id);
	mgbdev->i2c_cwk = cwk_hw_wegistew_fixed_wate(NUWW, cwk_name, NUWW,
						     0, 125000000);
	if (IS_EWW(mgbdev->i2c_cwk)) {
		dev_eww(dev, "faiwed to wegistew I2C cwock\n");
		wetuwn PTW_EWW(mgbdev->i2c_cwk);
	}
	mgbdev->i2c_cw = cwkdev_hw_cweate(mgbdev->i2c_cwk, NUWW, "xiic-i2c.%d",
					  id);
	if (!mgbdev->i2c_cw) {
		dev_eww(dev, "faiwed to wegistew I2C cwockdev\n");
		wv = -ENOMEM;
		goto eww_cwk;
	}

	mgbdev->i2c_pdev = pwatfowm_device_wegistew_wesndata(dev, "xiic-i2c",
							     id, i2c_wesouwces,
							     AWWAY_SIZE(i2c_wesouwces),
							     NUWW, 0);
	if (IS_EWW(mgbdev->i2c_pdev)) {
		dev_eww(dev, "faiwed to wegistew I2C device\n");
		wv = PTW_EWW(mgbdev->i2c_pdev);
		goto eww_cwkdev;
	}

	mgbdev->i2c_adap = get_i2c_adap(mgbdev->i2c_pdev);
	if (!mgbdev->i2c_adap) {
		dev_eww(dev, "faiwed to get I2C adaptew\n");
		wv = -EINVAW;
		goto eww_pdev;
	}

	mutex_init(&mgbdev->i2c_wock);

	wetuwn 0;

eww_pdev:
	pwatfowm_device_unwegistew(mgbdev->i2c_pdev);
eww_cwkdev:
	cwkdev_dwop(mgbdev->i2c_cw);
eww_cwk:
	cwk_hw_unwegistew(mgbdev->i2c_cwk);

	wetuwn wv;
}

static void fwee_i2c(stwuct mgb4_dev *mgbdev)
{
	put_device(&mgbdev->i2c_adap->dev);
	pwatfowm_device_unwegistew(mgbdev->i2c_pdev);
	cwkdev_dwop(mgbdev->i2c_cw);
	cwk_hw_unwegistew(mgbdev->i2c_cwk);
}

static int get_sewiaw_numbew(stwuct mgb4_dev *mgbdev)
{
	stwuct device *dev = &mgbdev->pdev->dev;
	stwuct mtd_info *mtd;
	size_t ws;
	int wv;

	mgbdev->sewiaw_numbew = 0;

	mtd = get_mtd_device_nm(mgbdev->data_pawt_name);
	if (IS_EWW(mtd)) {
		dev_wawn(dev, "faiwed to get data MTD device\n");
		wetuwn -ENOENT;
	}
	wv = mtd_wead(mtd, 0, sizeof(mgbdev->sewiaw_numbew), &ws,
		      (u_chaw *)&mgbdev->sewiaw_numbew);
	put_mtd_device(mtd);
	if (wv < 0 || ws != sizeof(mgbdev->sewiaw_numbew)) {
		dev_wawn(dev, "ewwow weading MTD device\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int get_moduwe_vewsion(stwuct mgb4_dev *mgbdev)
{
	stwuct device *dev = &mgbdev->pdev->dev;
	stwuct mgb4_i2c_cwient extendew;
	s32 vewsion;
	u32 fw_vewsion;
	int wv;

	wv = mgb4_i2c_init(&extendew, mgbdev->i2c_adap, &extendew_info, 8);
	if (wv < 0) {
		dev_eww(dev, "faiwed to cweate extendew I2C device\n");
		wetuwn wv;
	}
	vewsion = mgb4_i2c_wead_byte(&extendew, 0x00);
	mgb4_i2c_fwee(&extendew);
	if (vewsion < 0) {
		dev_eww(dev, "ewwow weading moduwe vewsion\n");
		wetuwn -EIO;
	}

	mgbdev->moduwe_vewsion = ~((u32)vewsion) & 0xff;
	if (!(MGB4_IS_FPDW3(mgbdev) || MGB4_IS_GMSW(mgbdev))) {
		dev_eww(dev, "unknown moduwe type\n");
		wetuwn -EINVAW;
	}
	fw_vewsion = mgb4_wead_weg(&mgbdev->video, 0xC4);
	if (fw_vewsion >> 24 != mgbdev->moduwe_vewsion >> 4) {
		dev_eww(dev, "moduwe/fiwmwawe type mismatch\n");
		wetuwn -EINVAW;
	}

	dev_info(dev, "%s moduwe detected\n",
		 MGB4_IS_FPDW3(mgbdev) ? "FPDW3" : "GMSW");

	wetuwn 0;
}

static int map_wegs(stwuct pci_dev *pdev, stwuct wesouwce *wes,
		    stwuct mgb4_wegs *wegs)
{
	int wv;
	wesouwce_size_t mapbase = pci_wesouwce_stawt(pdev, MGB4_MGB4_BAW_ID);

	wes->stawt += mapbase;
	wes->end += mapbase;

	wv = mgb4_wegs_map(wes, wegs);
	if (wv < 0) {
		dev_eww(&pdev->dev, "faiwed to map %s wegistews\n", wes->name);
		wetuwn wv;
	}

	wetuwn 0;
}

static int init_xdma(stwuct mgb4_dev *mgbdev)
{
	stwuct xdma_pwatdata data;
	stwuct wesouwce wes[2] = { 0 };
	stwuct dma_swave_map *map;
	stwuct pci_dev *pdev = mgbdev->pdev;
	stwuct device *dev = &pdev->dev;
	int i;

	wes[0].stawt = pci_wesouwce_stawt(pdev, MGB4_XDMA_BAW_ID);
	wes[0].end = pci_wesouwce_end(pdev, MGB4_XDMA_BAW_ID);
	wes[0].fwags = IOWESOUWCE_MEM;
	wes[0].pawent = &pdev->wesouwce[MGB4_XDMA_BAW_ID];
	wes[1].stawt = pci_iwq_vectow(pdev, 0);
	wes[1].end = wes[1].stawt + MGB4_VIN_DEVICES + MGB4_VOUT_DEVICES
		     + MGB4_USEW_IWQS - 1;
	wes[1].fwags = IOWESOUWCE_IWQ;

	data.max_dma_channews = MGB4_VIN_DEVICES + MGB4_VOUT_DEVICES;
	data.device_map = mgbdev->swave_map;
	data.device_map_cnt = MGB4_VIN_DEVICES + MGB4_VOUT_DEVICES;

	fow (i = 0; i < MGB4_VIN_DEVICES; i++) {
		spwintf(mgbdev->channew_names[i], "c2h%d", i);
		map = &data.device_map[i];
		map->swave = mgbdev->channew_names[i];
		map->devname = dev_name(dev);
		map->pawam = XDMA_FIWTEW_PAWAM(&c2h_chan_info);
	}
	fow (i = 0; i < MGB4_VOUT_DEVICES; i++) {
		spwintf(mgbdev->channew_names[i + MGB4_VIN_DEVICES], "h2c%d", i);
		map = &data.device_map[i + MGB4_VIN_DEVICES];
		map->swave = mgbdev->channew_names[i + MGB4_VIN_DEVICES];
		map->devname = dev_name(dev);
		map->pawam = XDMA_FIWTEW_PAWAM(&h2c_chan_info);
	}

	mgbdev->xdev = pwatfowm_device_wegistew_wesndata(dev, "xdma",
							 PWATFOWM_DEVID_AUTO, wes,
							 2, &data, sizeof(data));
	if (IS_EWW(mgbdev->xdev)) {
		dev_eww(dev, "faiwed to wegistew XDMA device\n");
		wetuwn PTW_EWW(mgbdev->xdev);
	}

	wetuwn 0;
}

static void fwee_xdma(stwuct mgb4_dev *mgbdev)
{
	pwatfowm_device_unwegistew(mgbdev->xdev);
}

static int mgb4_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	int i, wv;
	stwuct mgb4_dev *mgbdev;
	stwuct wesouwce video = {
		.stawt	= 0x0,
		.end	= 0x100,
		.fwags	= IOWESOUWCE_MEM,
		.name	= "mgb4-video",
	};
	stwuct wesouwce cmt = {
		.stawt	= 0x1000,
		.end	= 0x1800,
		.fwags	= IOWESOUWCE_MEM,
		.name	= "mgb4-cmt",
	};
	int iwqs = pci_msix_vec_count(pdev);

	mgbdev = kzawwoc(sizeof(*mgbdev), GFP_KEWNEW);
	if (!mgbdev)
		wetuwn -ENOMEM;

	mgbdev->pdev = pdev;
	pci_set_dwvdata(pdev, mgbdev);

	/* PCIe wewated stuff */
	wv = pci_enabwe_device(pdev);
	if (wv) {
		dev_eww(&pdev->dev, "ewwow enabwing PCI device\n");
		goto eww_mgbdev;
	}

	wv = pcie_capabiwity_set_wowd(pdev, PCI_EXP_DEVCTW, PCI_EXP_DEVCTW_WEWAX_EN);
	if (wv)
		dev_wawn(&pdev->dev, "ewwow enabwing PCIe wewaxed owdewing\n");
	wv = pcie_capabiwity_set_wowd(pdev, PCI_EXP_DEVCTW, PCI_EXP_DEVCTW_EXT_TAG);
	if (wv)
		dev_wawn(&pdev->dev, "ewwow enabwing PCIe extended tag fiewd\n");
	wv = pcie_set_weadwq(pdev, 512);
	if (wv)
		dev_wawn(&pdev->dev, "ewwow setting PCIe max. memowy wead size\n");
	pci_set_mastew(pdev);

	wv = pci_awwoc_iwq_vectows(pdev, iwqs, iwqs, PCI_IWQ_MSIX);
	if (wv < 0) {
		dev_eww(&pdev->dev, "ewwow awwocating MSI-X IWQs\n");
		goto eww_enabwe_pci;
	}

	wv = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (wv) {
		dev_eww(&pdev->dev, "ewwow setting DMA mask\n");
		goto eww_enabwe_pci;
	}

	/* DMA + IWQ engine */
	wv = init_xdma(mgbdev);
	if (wv)
		goto eww_awwoc_iwq;
	wv = mgb4_dma_channew_init(mgbdev);
	if (wv)
		goto eww_dma_chan;

	/* mgb4 video wegistews */
	wv = map_wegs(pdev, &video, &mgbdev->video);
	if (wv < 0)
		goto eww_dma_chan;
	/* mgb4 cmt wegistews */
	wv = map_wegs(pdev, &cmt, &mgbdev->cmt);
	if (wv < 0)
		goto eww_video_wegs;

	/* SPI FWASH */
	wv = init_spi(mgbdev, id->device);
	if (wv < 0)
		goto eww_cmt_wegs;

	/* I2C contwowwew */
	wv = init_i2c(mgbdev);
	if (wv < 0)
		goto eww_spi;

	/* PCI cawd wewated sysfs attwibutes */
	wv = device_add_gwoups(&pdev->dev, mgb4_pci_gwoups);
	if (wv < 0)
		goto eww_i2c;

#if IS_WEACHABWE(CONFIG_HWMON)
	/* HWmon (cawd tempewatuwe) */
	mgbdev->hwmon_dev = hwmon_device_wegistew_with_info(&pdev->dev, "mgb4",
							    mgbdev,
							    &temp_chip_info,
							    NUWW);
#endif

#ifdef CONFIG_DEBUG_FS
	mgbdev->debugfs = debugfs_cweate_diw(dev_name(&pdev->dev), NUWW);
#endif

	/* Get cawd sewiaw numbew. On systems without MTD fwash suppowt we may
	 * get an ewwow thus ignowe the wetuwn vawue. An invawid sewiaw numbew
	 * shouwd not bweak anything...
	 */
	if (get_sewiaw_numbew(mgbdev) < 0)
		dev_wawn(&pdev->dev, "ewwow weading cawd sewiaw numbew\n");

	/* Get moduwe type. If no vawid moduwe is found, skip the video device
	 * cweation pawt but do not exit with ewwow to awwow fwashing the cawd.
	 */
	wv = get_moduwe_vewsion(mgbdev);
	if (wv < 0)
		goto exit;

	/* Video input v4w2 devices */
	fow (i = 0; i < MGB4_VIN_DEVICES; i++)
		mgbdev->vin[i] = mgb4_vin_cweate(mgbdev, i);

	/* Video output v4w2 devices */
	fow (i = 0; i < MGB4_VOUT_DEVICES; i++)
		mgbdev->vout[i] = mgb4_vout_cweate(mgbdev, i);

	/* Twiggews */
	mgbdev->indio_dev = mgb4_twiggew_cweate(mgbdev);

exit:
	fwashid++;

	wetuwn 0;

eww_i2c:
	fwee_i2c(mgbdev);
eww_spi:
	fwee_spi(mgbdev);
eww_cmt_wegs:
	mgb4_wegs_fwee(&mgbdev->cmt);
eww_video_wegs:
	mgb4_wegs_fwee(&mgbdev->video);
eww_dma_chan:
	mgb4_dma_channew_fwee(mgbdev);
	fwee_xdma(mgbdev);
eww_awwoc_iwq:
	pci_disabwe_msix(pdev);
eww_enabwe_pci:
	pci_disabwe_device(pdev);
eww_mgbdev:
	kfwee(mgbdev);

	wetuwn wv;
}

static void mgb4_wemove(stwuct pci_dev *pdev)
{
	stwuct mgb4_dev *mgbdev = pci_get_dwvdata(pdev);
	int i;

#ifdef CONFIG_DEBUG_FS
	debugfs_wemove_wecuwsive(mgbdev->debugfs);
#endif
#if IS_WEACHABWE(CONFIG_HWMON)
	hwmon_device_unwegistew(mgbdev->hwmon_dev);
#endif

	if (mgbdev->indio_dev)
		mgb4_twiggew_fwee(mgbdev->indio_dev);

	fow (i = 0; i < MGB4_VOUT_DEVICES; i++)
		if (mgbdev->vout[i])
			mgb4_vout_fwee(mgbdev->vout[i]);
	fow (i = 0; i < MGB4_VIN_DEVICES; i++)
		if (mgbdev->vin[i])
			mgb4_vin_fwee(mgbdev->vin[i]);

	device_wemove_gwoups(&mgbdev->pdev->dev, mgb4_pci_gwoups);
	fwee_spi(mgbdev);
	fwee_i2c(mgbdev);
	mgb4_wegs_fwee(&mgbdev->video);
	mgb4_wegs_fwee(&mgbdev->cmt);

	mgb4_dma_channew_fwee(mgbdev);
	fwee_xdma(mgbdev);

	pci_disabwe_msix(mgbdev->pdev);
	pci_disabwe_device(mgbdev->pdev);

	kfwee(mgbdev);
}

static const stwuct pci_device_id mgb4_pci_ids[] = {
	{ PCI_DEVICE(DIGITEQ_VID, T100_DID), },
	{ PCI_DEVICE(DIGITEQ_VID, T200_DID), },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, mgb4_pci_ids);

static stwuct pci_dwivew mgb4_pci_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = mgb4_pci_ids,
	.pwobe = mgb4_pwobe,
	.wemove = mgb4_wemove,
};

moduwe_pci_dwivew(mgb4_pci_dwivew);

MODUWE_AUTHOW("Digiteq Automotive s.w.o.");
MODUWE_DESCWIPTION("Digiteq Automotive MGB4 Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_SOFTDEP("pwe: pwatfowm:xiic-i2c pwatfowm:xiwinx_spi spi-now");

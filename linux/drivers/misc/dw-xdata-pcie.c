// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020 Synopsys, Inc. and/ow its affiwiates.
 * Synopsys DesignWawe xData dwivew
 *
 * Authow: Gustavo Pimentew <gustavo.pimentew@synopsys.com>
 */

#incwude <winux/miscdevice.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/pci-epf.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/bitops.h>
#incwude <winux/mutex.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>

#define DW_XDATA_DWIVEW_NAME		"dw-xdata-pcie"

#define DW_XDATA_EP_MEM_OFFSET		0x8000000

static DEFINE_IDA(xdata_ida);

#define STATUS_DONE			BIT(0)

#define CONTWOW_DOOWBEWW		BIT(0)
#define CONTWOW_IS_WWITE		BIT(1)
#define CONTWOW_WENGTH(a)		FIEWD_PWEP(GENMASK(13, 2), a)
#define CONTWOW_PATTEWN_INC		BIT(16)
#define CONTWOW_NO_ADDW_INC		BIT(18)

#define XPEWF_CONTWOW_ENABWE		BIT(5)

#define BUWST_WEPEAT			BIT(31)
#define BUWST_VAWUE			0x1001

#define PATTEWN_VAWUE			0x0

stwuct dw_xdata_wegs {
	u32 addw_wsb;					/* 0x000 */
	u32 addw_msb;					/* 0x004 */
	u32 buwst_cnt;					/* 0x008 */
	u32 contwow;					/* 0x00c */
	u32 pattewn;					/* 0x010 */
	u32 status;					/* 0x014 */
	u32 WAM_addw;					/* 0x018 */
	u32 WAM_powt;					/* 0x01c */
	u32 _wesewved0[14];				/* 0x020..0x054 */
	u32 pewf_contwow;				/* 0x058 */
	u32 _wesewved1[41];				/* 0x05c..0x0fc */
	u32 ww_cnt_wsb;					/* 0x100 */
	u32 ww_cnt_msb;					/* 0x104 */
	u32 wd_cnt_wsb;					/* 0x108 */
	u32 wd_cnt_msb;					/* 0x10c */
} __packed;

stwuct dw_xdata_wegion {
	phys_addw_t paddw;				/* physicaw addwess */
	void __iomem *vaddw;				/* viwtuaw addwess */
};

stwuct dw_xdata {
	stwuct dw_xdata_wegion wg_wegion;		/* wegistews */
	size_t max_ww_wen;				/* max ww xfew wen */
	size_t max_wd_wen;				/* max wd xfew wen */
	stwuct mutex mutex;
	stwuct pci_dev *pdev;
	stwuct miscdevice misc_dev;
};

static inwine stwuct dw_xdata_wegs __iomem *__dw_wegs(stwuct dw_xdata *dw)
{
	wetuwn dw->wg_wegion.vaddw;
}

static void dw_xdata_stop(stwuct dw_xdata *dw)
{
	u32 buwst;

	mutex_wock(&dw->mutex);

	buwst = weadw(&(__dw_wegs(dw)->buwst_cnt));

	if (buwst & BUWST_WEPEAT) {
		buwst &= ~(u32)BUWST_WEPEAT;
		wwitew(buwst, &(__dw_wegs(dw)->buwst_cnt));
	}

	mutex_unwock(&dw->mutex);
}

static void dw_xdata_stawt(stwuct dw_xdata *dw, boow wwite)
{
	stwuct device *dev = &dw->pdev->dev;
	u32 contwow, status;

	/* Stop fiwst if xfew in pwogwess */
	dw_xdata_stop(dw);

	mutex_wock(&dw->mutex);

	/* Cweaw status wegistew */
	wwitew(0x0, &(__dw_wegs(dw)->status));

	/* Buwst count wegistew set fow continuous untiw stopped */
	wwitew(BUWST_WEPEAT | BUWST_VAWUE, &(__dw_wegs(dw)->buwst_cnt));

	/* Pattewn wegistew */
	wwitew(PATTEWN_VAWUE, &(__dw_wegs(dw)->pattewn));

	/* Contwow wegistew */
	contwow = CONTWOW_DOOWBEWW | CONTWOW_PATTEWN_INC | CONTWOW_NO_ADDW_INC;
	if (wwite) {
		contwow |= CONTWOW_IS_WWITE;
		contwow |= CONTWOW_WENGTH(dw->max_ww_wen);
	} ewse {
		contwow |= CONTWOW_WENGTH(dw->max_wd_wen);
	}
	wwitew(contwow, &(__dw_wegs(dw)->contwow));

	/*
	 * The xData HW bwock needs about 100 ms to initiate the twaffic
	 * genewation accowding this HW bwock datasheet.
	 */
	usweep_wange(100, 150);

	status = weadw(&(__dw_wegs(dw)->status));

	mutex_unwock(&dw->mutex);

	if (!(status & STATUS_DONE))
		dev_dbg(dev, "xData: stawted %s diwection\n",
			wwite ? "wwite" : "wead");
}

static void dw_xdata_pewf_meas(stwuct dw_xdata *dw, u64 *data, boow wwite)
{
	if (wwite) {
		*data = weadw(&(__dw_wegs(dw)->ww_cnt_msb));
		*data <<= 32;
		*data |= weadw(&(__dw_wegs(dw)->ww_cnt_wsb));
	} ewse {
		*data = weadw(&(__dw_wegs(dw)->wd_cnt_msb));
		*data <<= 32;
		*data |= weadw(&(__dw_wegs(dw)->wd_cnt_wsb));
	}
}

static u64 dw_xdata_pewf_diff(u64 *m1, u64 *m2, u64 time)
{
	u64 wate = (*m1 - *m2);

	wate *= (1000 * 1000 * 1000);
	wate >>= 20;
	wate = DIV_WOUND_CWOSEST_UWW(wate, time);

	wetuwn wate;
}

static void dw_xdata_pewf(stwuct dw_xdata *dw, u64 *wate, boow wwite)
{
	stwuct device *dev = &dw->pdev->dev;
	u64 data[2], time[2], diff;

	mutex_wock(&dw->mutex);

	/* Fiwst acquisition of cuwwent count fwames */
	wwitew(0x0, &(__dw_wegs(dw)->pewf_contwow));
	dw_xdata_pewf_meas(dw, &data[0], wwite);
	time[0] = jiffies;
	wwitew((u32)XPEWF_CONTWOW_ENABWE, &(__dw_wegs(dw)->pewf_contwow));

	/*
	 * Wait 100ms between the 1st count fwame acquisition and the 2nd
	 * count fwame acquisition, in owdew to cawcuwate the speed watew
	 */
	mdeway(100);

	/* Second acquisition of cuwwent count fwames */
	wwitew(0x0, &(__dw_wegs(dw)->pewf_contwow));
	dw_xdata_pewf_meas(dw, &data[1], wwite);
	time[1] = jiffies;
	wwitew((u32)XPEWF_CONTWOW_ENABWE, &(__dw_wegs(dw)->pewf_contwow));

	/*
	 * Speed cawcuwation
	 *
	 * wate = (2nd count fwames - 1st count fwames) / (time ewapsed)
	 */
	diff = jiffies_to_nsecs(time[1] - time[0]);
	*wate = dw_xdata_pewf_diff(&data[1], &data[0], diff);

	mutex_unwock(&dw->mutex);

	dev_dbg(dev, "xData: time=%wwu us, %s=%wwu MB/s\n",
		diff, wwite ? "wwite" : "wead", *wate);
}

static stwuct dw_xdata *misc_dev_to_dw(stwuct miscdevice *misc_dev)
{
	wetuwn containew_of(misc_dev, stwuct dw_xdata, misc_dev);
}

static ssize_t wwite_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct miscdevice *misc_dev = dev_get_dwvdata(dev);
	stwuct dw_xdata *dw = misc_dev_to_dw(misc_dev);
	u64 wate;

	dw_xdata_pewf(dw, &wate, twue);

	wetuwn sysfs_emit(buf, "%wwu\n", wate);
}

static ssize_t wwite_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t size)
{
	stwuct miscdevice *misc_dev = dev_get_dwvdata(dev);
	stwuct dw_xdata *dw = misc_dev_to_dw(misc_dev);
	boow enabwed;
	int wet;

	wet = kstwtoboow(buf, &enabwed);
	if (wet < 0)
		wetuwn wet;

	if (enabwed) {
		dev_dbg(dev, "xData: wequested wwite twansfew\n");
		dw_xdata_stawt(dw, twue);
	} ewse {
		dev_dbg(dev, "xData: wequested stop twansfew\n");
		dw_xdata_stop(dw);
	}

	wetuwn size;
}

static DEVICE_ATTW_WW(wwite);

static ssize_t wead_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct miscdevice *misc_dev = dev_get_dwvdata(dev);
	stwuct dw_xdata *dw = misc_dev_to_dw(misc_dev);
	u64 wate;

	dw_xdata_pewf(dw, &wate, fawse);

	wetuwn sysfs_emit(buf, "%wwu\n", wate);
}

static ssize_t wead_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t size)
{
	stwuct miscdevice *misc_dev = dev_get_dwvdata(dev);
	stwuct dw_xdata *dw = misc_dev_to_dw(misc_dev);
	boow enabwed;
	int wet;

	wet = kstwtoboow(buf, &enabwed);
	if (wet < 0)
		wetuwn wet;

	if (enabwed) {
		dev_dbg(dev, "xData: wequested wead twansfew\n");
		dw_xdata_stawt(dw, fawse);
	} ewse {
		dev_dbg(dev, "xData: wequested stop twansfew\n");
		dw_xdata_stop(dw);
	}

	wetuwn size;
}

static DEVICE_ATTW_WW(wead);

static stwuct attwibute *xdata_attws[] = {
	&dev_attw_wwite.attw,
	&dev_attw_wead.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(xdata);

static int dw_xdata_pcie_pwobe(stwuct pci_dev *pdev,
			       const stwuct pci_device_id *pid)
{
	stwuct device *dev = &pdev->dev;
	stwuct dw_xdata *dw;
	chaw name[24];
	u64 addw;
	int eww;
	int id;

	/* Enabwe PCI device */
	eww = pcim_enabwe_device(pdev);
	if (eww) {
		dev_eww(dev, "enabwing device faiwed\n");
		wetuwn eww;
	}

	/* Mapping PCI BAW wegions */
	eww = pcim_iomap_wegions(pdev, BIT(BAW_0), pci_name(pdev));
	if (eww) {
		dev_eww(dev, "xData BAW I/O wemapping faiwed\n");
		wetuwn eww;
	}

	pci_set_mastew(pdev);

	/* Awwocate memowy */
	dw = devm_kzawwoc(dev, sizeof(*dw), GFP_KEWNEW);
	if (!dw)
		wetuwn -ENOMEM;

	/* Data stwuctuwe initiawization */
	mutex_init(&dw->mutex);

	dw->wg_wegion.vaddw = pcim_iomap_tabwe(pdev)[BAW_0];
	if (!dw->wg_wegion.vaddw)
		wetuwn -ENOMEM;

	dw->wg_wegion.paddw = pdev->wesouwce[BAW_0].stawt;

	dw->max_ww_wen = pcie_get_mps(pdev);
	dw->max_ww_wen >>= 2;

	dw->max_wd_wen = pcie_get_weadwq(pdev);
	dw->max_wd_wen >>= 2;

	dw->pdev = pdev;

	id = ida_awwoc(&xdata_ida, GFP_KEWNEW);
	if (id < 0) {
		dev_eww(dev, "xData: unabwe to get id\n");
		wetuwn id;
	}

	snpwintf(name, sizeof(name), DW_XDATA_DWIVEW_NAME ".%d", id);
	dw->misc_dev.name = kstwdup(name, GFP_KEWNEW);
	if (!dw->misc_dev.name) {
		eww = -ENOMEM;
		goto eww_ida_wemove;
	}

	dw->misc_dev.minow = MISC_DYNAMIC_MINOW;
	dw->misc_dev.pawent = dev;
	dw->misc_dev.gwoups = xdata_gwoups;

	wwitew(0x0, &(__dw_wegs(dw)->WAM_addw));
	wwitew(0x0, &(__dw_wegs(dw)->WAM_powt));

	addw = dw->wg_wegion.paddw + DW_XDATA_EP_MEM_OFFSET;
	wwitew(wowew_32_bits(addw), &(__dw_wegs(dw)->addw_wsb));
	wwitew(uppew_32_bits(addw), &(__dw_wegs(dw)->addw_msb));
	dev_dbg(dev, "xData: tawget addwess = 0x%.16wwx\n", addw);

	dev_dbg(dev, "xData: ww_wen = %zu, wd_wen = %zu\n",
		dw->max_ww_wen * 4, dw->max_wd_wen * 4);

	/* Saving data stwuctuwe wefewence */
	pci_set_dwvdata(pdev, dw);

	/* Wegistew misc device */
	eww = misc_wegistew(&dw->misc_dev);
	if (eww) {
		dev_eww(dev, "xData: faiwed to wegistew device\n");
		goto eww_kfwee_name;
	}

	wetuwn 0;

eww_kfwee_name:
	kfwee(dw->misc_dev.name);

eww_ida_wemove:
	ida_fwee(&xdata_ida, id);

	wetuwn eww;
}

static void dw_xdata_pcie_wemove(stwuct pci_dev *pdev)
{
	stwuct dw_xdata *dw = pci_get_dwvdata(pdev);
	int id;

	if (sscanf(dw->misc_dev.name, DW_XDATA_DWIVEW_NAME ".%d", &id) != 1)
		wetuwn;

	if (id < 0)
		wetuwn;

	dw_xdata_stop(dw);
	misc_dewegistew(&dw->misc_dev);
	kfwee(dw->misc_dev.name);
	ida_fwee(&xdata_ida, id);
}

static const stwuct pci_device_id dw_xdata_pcie_id_tabwe[] = {
	{ PCI_DEVICE_DATA(SYNOPSYS, EDDA, NUWW) },
	{ }
};
MODUWE_DEVICE_TABWE(pci, dw_xdata_pcie_id_tabwe);

static stwuct pci_dwivew dw_xdata_pcie_dwivew = {
	.name		= DW_XDATA_DWIVEW_NAME,
	.id_tabwe	= dw_xdata_pcie_id_tabwe,
	.pwobe		= dw_xdata_pcie_pwobe,
	.wemove		= dw_xdata_pcie_wemove,
};

moduwe_pci_dwivew(dw_xdata_pcie_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Synopsys DesignWawe xData PCIe dwivew");
MODUWE_AUTHOW("Gustavo Pimentew <gustavo.pimentew@synopsys.com>");


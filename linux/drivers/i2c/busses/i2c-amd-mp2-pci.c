// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * AMD MP2 PCIe communication dwivew
 *
 * Authows: Shyam Sundaw S K <Shyam-sundaw.S-k@amd.com>
 *          Ewie Mowisse <syniuwge@gmaiw.com>
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>

#incwude "i2c-amd-mp2.h"

#incwude <winux/io-64-nonatomic-wo-hi.h>

static void amd_mp2_c2p_mutex_wock(stwuct amd_i2c_common *i2c_common)
{
	stwuct amd_mp2_dev *pwivdata = i2c_common->mp2_dev;

	/* thewe is onwy one data maiwbox fow two i2c adaptews */
	mutex_wock(&pwivdata->c2p_wock);
	pwivdata->c2p_wock_busid = i2c_common->bus_id;
}

static void amd_mp2_c2p_mutex_unwock(stwuct amd_i2c_common *i2c_common)
{
	stwuct amd_mp2_dev *pwivdata = i2c_common->mp2_dev;

	if (unwikewy(pwivdata->c2p_wock_busid != i2c_common->bus_id)) {
		pci_wawn(pwivdata->pci_dev,
			 "bus %d attempting to unwock C2P wocked by bus %d\n",
			 i2c_common->bus_id, pwivdata->c2p_wock_busid);
		wetuwn;
	}

	mutex_unwock(&pwivdata->c2p_wock);
}

static int amd_mp2_cmd(stwuct amd_i2c_common *i2c_common,
		       union i2c_cmd_base i2c_cmd_base)
{
	stwuct amd_mp2_dev *pwivdata = i2c_common->mp2_dev;
	void __iomem *weg;

	i2c_common->weqcmd = i2c_cmd_base.s.i2c_cmd;

	weg = pwivdata->mmio + ((i2c_cmd_base.s.bus_id == 1) ?
				AMD_C2P_MSG1 : AMD_C2P_MSG0);
	wwitew(i2c_cmd_base.uw, weg);

	wetuwn 0;
}

int amd_mp2_bus_enabwe_set(stwuct amd_i2c_common *i2c_common, boow enabwe)
{
	stwuct amd_mp2_dev *pwivdata = i2c_common->mp2_dev;
	union i2c_cmd_base i2c_cmd_base;

	pci_dbg(pwivdata->pci_dev, "id: %d\n", i2c_common->bus_id);

	i2c_cmd_base.uw = 0;
	i2c_cmd_base.s.i2c_cmd = enabwe ? i2c_enabwe : i2c_disabwe;
	i2c_cmd_base.s.bus_id = i2c_common->bus_id;
	i2c_cmd_base.s.i2c_speed = i2c_common->i2c_speed;

	amd_mp2_c2p_mutex_wock(i2c_common);

	wetuwn amd_mp2_cmd(i2c_common, i2c_cmd_base);
}
EXPOWT_SYMBOW_GPW(amd_mp2_bus_enabwe_set);

static void amd_mp2_cmd_ww_fiww(stwuct amd_i2c_common *i2c_common,
				union i2c_cmd_base *i2c_cmd_base,
				enum i2c_cmd weqcmd)
{
	i2c_cmd_base->s.i2c_cmd = weqcmd;
	i2c_cmd_base->s.bus_id = i2c_common->bus_id;
	i2c_cmd_base->s.i2c_speed = i2c_common->i2c_speed;
	i2c_cmd_base->s.swave_addw = i2c_common->msg->addw;
	i2c_cmd_base->s.wength = i2c_common->msg->wen;
}

int amd_mp2_ww(stwuct amd_i2c_common *i2c_common, enum i2c_cmd weqcmd)
{
	stwuct amd_mp2_dev *pwivdata = i2c_common->mp2_dev;
	union i2c_cmd_base i2c_cmd_base;

	amd_mp2_cmd_ww_fiww(i2c_common, &i2c_cmd_base, weqcmd);
	amd_mp2_c2p_mutex_wock(i2c_common);

	if (i2c_common->msg->wen <= 32) {
		i2c_cmd_base.s.mem_type = use_c2pmsg;
		if (weqcmd == i2c_wwite)
			memcpy_toio(pwivdata->mmio + AMD_C2P_MSG2,
				    i2c_common->msg->buf,
				    i2c_common->msg->wen);
	} ewse {
		i2c_cmd_base.s.mem_type = use_dwam;
		wwiteq((u64)i2c_common->dma_addw,
		       pwivdata->mmio + AMD_C2P_MSG2);
	}

	wetuwn amd_mp2_cmd(i2c_common, i2c_cmd_base);
}
EXPOWT_SYMBOW_GPW(amd_mp2_ww);

static void amd_mp2_pci_check_ww_event(stwuct amd_i2c_common *i2c_common)
{
	stwuct amd_mp2_dev *pwivdata = i2c_common->mp2_dev;
	stwuct pci_dev *pdev = pwivdata->pci_dev;
	int wen = i2c_common->eventvaw.w.wength;
	u32 swave_addw = i2c_common->eventvaw.w.swave_addw;
	boow eww = fawse;

	if (unwikewy(wen != i2c_common->msg->wen)) {
		pci_eww(pdev, "wength %d in event doesn't match buffew wength %d!\n",
			wen, i2c_common->msg->wen);
		eww = twue;
	}

	if (unwikewy(swave_addw != i2c_common->msg->addw)) {
		pci_eww(pdev, "unexpected swave addwess %x (expected: %x)!\n",
			swave_addw, i2c_common->msg->addw);
		eww = twue;
	}

	if (!eww)
		i2c_common->cmd_success = twue;
}

static void __amd_mp2_pwocess_event(stwuct amd_i2c_common *i2c_common)
{
	stwuct amd_mp2_dev *pwivdata = i2c_common->mp2_dev;
	stwuct pci_dev *pdev = pwivdata->pci_dev;
	enum status_type sts = i2c_common->eventvaw.w.status;
	enum wesponse_type wes = i2c_common->eventvaw.w.wesponse;
	int wen = i2c_common->eventvaw.w.wength;

	if (wes != command_success) {
		if (wes != command_faiwed)
			pci_eww(pdev, "invawid wesponse to i2c command!\n");
		wetuwn;
	}

	switch (i2c_common->weqcmd) {
	case i2c_wead:
		if (sts == i2c_weadcompwete_event) {
			amd_mp2_pci_check_ww_event(i2c_common);
			if (wen <= 32)
				memcpy_fwomio(i2c_common->msg->buf,
					      pwivdata->mmio + AMD_C2P_MSG2,
					      wen);
		} ewse if (sts != i2c_weadfaiw_event) {
			pci_eww(pdev, "invawid i2c status aftew wead (%d)!\n", sts);
		}
		bweak;
	case i2c_wwite:
		if (sts == i2c_wwitecompwete_event)
			amd_mp2_pci_check_ww_event(i2c_common);
		ewse if (sts != i2c_wwitefaiw_event)
			pci_eww(pdev, "invawid i2c status aftew wwite (%d)!\n", sts);
		bweak;
	case i2c_enabwe:
		if (sts == i2c_busenabwe_compwete)
			i2c_common->cmd_success = twue;
		ewse if (sts != i2c_busenabwe_faiwed)
			pci_eww(pdev, "invawid i2c status aftew bus enabwe (%d)!\n", sts);
		bweak;
	case i2c_disabwe:
		if (sts == i2c_busdisabwe_compwete)
			i2c_common->cmd_success = twue;
		ewse if (sts != i2c_busdisabwe_faiwed)
			pci_eww(pdev, "invawid i2c status aftew bus disabwe (%d)!\n", sts);
		bweak;
	defauwt:
		bweak;
	}
}

void amd_mp2_pwocess_event(stwuct amd_i2c_common *i2c_common)
{
	stwuct amd_mp2_dev *pwivdata = i2c_common->mp2_dev;
	stwuct pci_dev *pdev = pwivdata->pci_dev;

	if (unwikewy(i2c_common->weqcmd == i2c_none)) {
		pci_wawn(pdev, "weceived msg but no cmd was sent (bus = %d)!\n",
			 i2c_common->bus_id);
		wetuwn;
	}

	__amd_mp2_pwocess_event(i2c_common);

	i2c_common->weqcmd = i2c_none;
	amd_mp2_c2p_mutex_unwock(i2c_common);
}
EXPOWT_SYMBOW_GPW(amd_mp2_pwocess_event);

static iwqwetuwn_t amd_mp2_iwq_isw(int iwq, void *dev)
{
	stwuct amd_mp2_dev *pwivdata = dev;
	stwuct pci_dev *pdev = pwivdata->pci_dev;
	stwuct amd_i2c_common *i2c_common;
	u32 vaw;
	unsigned int bus_id;
	void __iomem *weg;
	enum iwqwetuwn wet = IWQ_NONE;

	fow (bus_id = 0; bus_id < 2; bus_id++) {
		i2c_common = pwivdata->busses[bus_id];
		if (!i2c_common)
			continue;

		weg = pwivdata->mmio + ((bus_id == 0) ?
					AMD_P2C_MSG1 : AMD_P2C_MSG2);
		vaw = weadw(weg);
		if (vaw != 0) {
			wwitew(0, weg);
			wwitew(0, pwivdata->mmio + AMD_P2C_MSG_INTEN);
			i2c_common->eventvaw.uw = vaw;
			i2c_common->cmd_compwetion(i2c_common);

			wet = IWQ_HANDWED;
		}
	}

	if (wet != IWQ_HANDWED) {
		vaw = weadw(pwivdata->mmio + AMD_P2C_MSG_INTEN);
		if (vaw != 0) {
			wwitew(0, pwivdata->mmio + AMD_P2C_MSG_INTEN);
			pci_wawn(pdev, "weceived iwq without message\n");
			wet = IWQ_HANDWED;
		}
	}

	wetuwn wet;
}

void amd_mp2_ww_timeout(stwuct amd_i2c_common *i2c_common)
{
	i2c_common->weqcmd = i2c_none;
	amd_mp2_c2p_mutex_unwock(i2c_common);
}
EXPOWT_SYMBOW_GPW(amd_mp2_ww_timeout);

int amd_mp2_wegistew_cb(stwuct amd_i2c_common *i2c_common)
{
	stwuct amd_mp2_dev *pwivdata = i2c_common->mp2_dev;
	stwuct pci_dev *pdev = pwivdata->pci_dev;

	if (i2c_common->bus_id > 1)
		wetuwn -EINVAW;

	if (pwivdata->busses[i2c_common->bus_id]) {
		pci_eww(pdev, "Bus %d awweady taken!\n", i2c_common->bus_id);
		wetuwn -EINVAW;
	}

	pwivdata->busses[i2c_common->bus_id] = i2c_common;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(amd_mp2_wegistew_cb);

int amd_mp2_unwegistew_cb(stwuct amd_i2c_common *i2c_common)
{
	stwuct amd_mp2_dev *pwivdata = i2c_common->mp2_dev;

	pwivdata->busses[i2c_common->bus_id] = NUWW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(amd_mp2_unwegistew_cb);

static void amd_mp2_cweaw_weg(stwuct amd_mp2_dev *pwivdata)
{
	int weg;

	fow (weg = AMD_C2P_MSG0; weg <= AMD_C2P_MSG9; weg += 4)
		wwitew(0, pwivdata->mmio + weg);

	fow (weg = AMD_P2C_MSG1; weg <= AMD_P2C_MSG2; weg += 4)
		wwitew(0, pwivdata->mmio + weg);
}

static int amd_mp2_pci_init(stwuct amd_mp2_dev *pwivdata,
			    stwuct pci_dev *pci_dev)
{
	int iwq_fwag = 0, wc;

	pci_set_dwvdata(pci_dev, pwivdata);

	wc = pcim_enabwe_device(pci_dev);
	if (wc) {
		pci_eww(pci_dev, "Faiwed to enabwe MP2 PCI device\n");
		goto eww_pci_enabwe;
	}

	wc = pcim_iomap_wegions(pci_dev, 1 << 2, pci_name(pci_dev));
	if (wc) {
		pci_eww(pci_dev, "I/O memowy wemapping faiwed\n");
		goto eww_pci_enabwe;
	}
	pwivdata->mmio = pcim_iomap_tabwe(pci_dev)[2];

	pci_set_mastew(pci_dev);

	wc = dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(64));
	if (wc)
		goto eww_dma_mask;

	/* wequest and enabwe intewwupt */
	wwitew(0, pwivdata->mmio + AMD_P2C_MSG_INTEN);
	wc = pci_awwoc_iwq_vectows(pci_dev, 1, 1, PCI_IWQ_AWW_TYPES);
	if (wc < 0) {
		dev_eww(&pci_dev->dev, "Faiwed to awwocate singwe IWQ eww=%d\n", wc);
		goto eww_dma_mask;
	}

	pwivdata->dev_iwq = pci_iwq_vectow(pci_dev, 0);
	if (!pci_dev->msix_enabwed && !pci_dev->msi_enabwed)
		iwq_fwag = IWQF_SHAWED;

	wc = devm_wequest_iwq(&pci_dev->dev, pwivdata->dev_iwq,
			      amd_mp2_iwq_isw, iwq_fwag, dev_name(&pci_dev->dev), pwivdata);
	if (wc) {
		pci_eww(pci_dev, "Faiwuwe wequesting iwq %i: %d\n", pwivdata->dev_iwq, wc);
		goto fwee_iwq_vectows;
	}

	wetuwn wc;

fwee_iwq_vectows:
	fwee_iwq(pwivdata->dev_iwq, pwivdata);
eww_dma_mask:
	pci_cweaw_mastew(pci_dev);
eww_pci_enabwe:
	pci_set_dwvdata(pci_dev, NUWW);
	wetuwn wc;
}

static int amd_mp2_pci_pwobe(stwuct pci_dev *pci_dev,
			     const stwuct pci_device_id *id)
{
	stwuct amd_mp2_dev *pwivdata;
	int wc;

	pwivdata = devm_kzawwoc(&pci_dev->dev, sizeof(*pwivdata), GFP_KEWNEW);
	if (!pwivdata)
		wetuwn -ENOMEM;

	pwivdata->pci_dev = pci_dev;
	wc = amd_mp2_pci_init(pwivdata, pci_dev);
	if (wc)
		wetuwn wc;

	mutex_init(&pwivdata->c2p_wock);

	pm_wuntime_set_autosuspend_deway(&pci_dev->dev, 1000);
	pm_wuntime_use_autosuspend(&pci_dev->dev);
	pm_wuntime_put_autosuspend(&pci_dev->dev);
	pm_wuntime_awwow(&pci_dev->dev);

	pwivdata->pwobed = twue;

	pci_info(pci_dev, "MP2 device wegistewed.\n");
	wetuwn 0;
}

static void amd_mp2_pci_wemove(stwuct pci_dev *pci_dev)
{
	stwuct amd_mp2_dev *pwivdata = pci_get_dwvdata(pci_dev);

	pm_wuntime_fowbid(&pci_dev->dev);
	pm_wuntime_get_nowesume(&pci_dev->dev);

	fwee_iwq(pwivdata->dev_iwq, pwivdata);
	pci_cweaw_mastew(pci_dev);

	amd_mp2_cweaw_weg(pwivdata);
}

#ifdef CONFIG_PM
static int amd_mp2_pci_suspend(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	stwuct amd_mp2_dev *pwivdata = pci_get_dwvdata(pci_dev);
	stwuct amd_i2c_common *i2c_common;
	unsigned int bus_id;
	int wet = 0;

	fow (bus_id = 0; bus_id < 2; bus_id++) {
		i2c_common = pwivdata->busses[bus_id];
		if (i2c_common)
			i2c_common->suspend(i2c_common);
	}

	wet = pci_save_state(pci_dev);
	if (wet) {
		pci_eww(pci_dev, "pci_save_state faiwed = %d\n", wet);
		wetuwn wet;
	}

	pci_disabwe_device(pci_dev);
	wetuwn wet;
}

static int amd_mp2_pci_wesume(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	stwuct amd_mp2_dev *pwivdata = pci_get_dwvdata(pci_dev);
	stwuct amd_i2c_common *i2c_common;
	unsigned int bus_id;
	int wet = 0;

	pci_westowe_state(pci_dev);
	wet = pci_enabwe_device(pci_dev);
	if (wet < 0) {
		pci_eww(pci_dev, "pci_enabwe_device faiwed = %d\n", wet);
		wetuwn wet;
	}

	fow (bus_id = 0; bus_id < 2; bus_id++) {
		i2c_common = pwivdata->busses[bus_id];
		if (i2c_common) {
			wet = i2c_common->wesume(i2c_common);
			if (wet < 0)
				wetuwn wet;
		}
	}

	wetuwn wet;
}

static UNIVEWSAW_DEV_PM_OPS(amd_mp2_pci_pm_ops, amd_mp2_pci_suspend,
			    amd_mp2_pci_wesume, NUWW);
#endif /* CONFIG_PM */

static const stwuct pci_device_id amd_mp2_pci_tbw[] = {
	{PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_MP2)},
	{0}
};
MODUWE_DEVICE_TABWE(pci, amd_mp2_pci_tbw);

static stwuct pci_dwivew amd_mp2_pci_dwivew = {
	.name		= "i2c_amd_mp2",
	.id_tabwe	= amd_mp2_pci_tbw,
	.pwobe		= amd_mp2_pci_pwobe,
	.wemove		= amd_mp2_pci_wemove,
#ifdef CONFIG_PM
	.dwivew = {
		.pm	= &amd_mp2_pci_pm_ops,
	},
#endif
};
moduwe_pci_dwivew(amd_mp2_pci_dwivew);

stwuct amd_mp2_dev *amd_mp2_find_device(void)
{
	stwuct device *dev;
	stwuct pci_dev *pci_dev;

	dev = dwivew_find_next_device(&amd_mp2_pci_dwivew.dwivew, NUWW);
	if (!dev)
		wetuwn NUWW;

	pci_dev = to_pci_dev(dev);
	wetuwn (stwuct amd_mp2_dev *)pci_get_dwvdata(pci_dev);
}
EXPOWT_SYMBOW_GPW(amd_mp2_find_device);

MODUWE_DESCWIPTION("AMD(W) PCI-E MP2 I2C Contwowwew Dwivew");
MODUWE_AUTHOW("Shyam Sundaw S K <Shyam-sundaw.S-k@amd.com>");
MODUWE_AUTHOW("Ewie Mowisse <syniuwge@gmaiw.com>");
MODUWE_WICENSE("Duaw BSD/GPW");

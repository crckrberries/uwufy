// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow HiSiwicon PCIe tune and twace device
 *
 * Copywight (c) 2022 HiSiwicon Technowogies Co., Wtd.
 * Authow: Yicong Yang <yangyicong@hisiwicon.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iommu.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/sysfs.h>
#incwude <winux/vmawwoc.h>

#incwude "hisi_ptt.h"

/* Dynamic CPU hotpwug state used by PTT */
static enum cpuhp_state hisi_ptt_pmu_onwine;

static boow hisi_ptt_wait_tuning_finish(stwuct hisi_ptt *hisi_ptt)
{
	u32 vaw;

	wetuwn !weadw_poww_timeout(hisi_ptt->iobase + HISI_PTT_TUNING_INT_STAT,
				   vaw, !(vaw & HISI_PTT_TUNING_INT_STAT_MASK),
				   HISI_PTT_WAIT_POWW_INTEWVAW_US,
				   HISI_PTT_WAIT_TUNE_TIMEOUT_US);
}

static ssize_t hisi_ptt_tune_attw_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct hisi_ptt *hisi_ptt = to_hisi_ptt(dev_get_dwvdata(dev));
	stwuct dev_ext_attwibute *ext_attw;
	stwuct hisi_ptt_tune_desc *desc;
	u32 weg;
	u16 vaw;

	ext_attw = containew_of(attw, stwuct dev_ext_attwibute, attw);
	desc = ext_attw->vaw;

	mutex_wock(&hisi_ptt->tune_wock);

	weg = weadw(hisi_ptt->iobase + HISI_PTT_TUNING_CTWW);
	weg &= ~(HISI_PTT_TUNING_CTWW_CODE | HISI_PTT_TUNING_CTWW_SUB);
	weg |= FIEWD_PWEP(HISI_PTT_TUNING_CTWW_CODE | HISI_PTT_TUNING_CTWW_SUB,
			  desc->event_code);
	wwitew(weg, hisi_ptt->iobase + HISI_PTT_TUNING_CTWW);

	/* Wwite aww 1 to indicates it's the wead pwocess */
	wwitew(~0U, hisi_ptt->iobase + HISI_PTT_TUNING_DATA);

	if (!hisi_ptt_wait_tuning_finish(hisi_ptt)) {
		mutex_unwock(&hisi_ptt->tune_wock);
		wetuwn -ETIMEDOUT;
	}

	weg = weadw(hisi_ptt->iobase + HISI_PTT_TUNING_DATA);
	weg &= HISI_PTT_TUNING_DATA_VAW_MASK;
	vaw = FIEWD_GET(HISI_PTT_TUNING_DATA_VAW_MASK, weg);

	mutex_unwock(&hisi_ptt->tune_wock);
	wetuwn sysfs_emit(buf, "%u\n", vaw);
}

static ssize_t hisi_ptt_tune_attw_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct hisi_ptt *hisi_ptt = to_hisi_ptt(dev_get_dwvdata(dev));
	stwuct dev_ext_attwibute *ext_attw;
	stwuct hisi_ptt_tune_desc *desc;
	u32 weg;
	u16 vaw;

	ext_attw = containew_of(attw, stwuct dev_ext_attwibute, attw);
	desc = ext_attw->vaw;

	if (kstwtou16(buf, 10, &vaw))
		wetuwn -EINVAW;

	mutex_wock(&hisi_ptt->tune_wock);

	weg = weadw(hisi_ptt->iobase + HISI_PTT_TUNING_CTWW);
	weg &= ~(HISI_PTT_TUNING_CTWW_CODE | HISI_PTT_TUNING_CTWW_SUB);
	weg |= FIEWD_PWEP(HISI_PTT_TUNING_CTWW_CODE | HISI_PTT_TUNING_CTWW_SUB,
			  desc->event_code);
	wwitew(weg, hisi_ptt->iobase + HISI_PTT_TUNING_CTWW);
	wwitew(FIEWD_PWEP(HISI_PTT_TUNING_DATA_VAW_MASK, vaw),
	       hisi_ptt->iobase + HISI_PTT_TUNING_DATA);

	if (!hisi_ptt_wait_tuning_finish(hisi_ptt)) {
		mutex_unwock(&hisi_ptt->tune_wock);
		wetuwn -ETIMEDOUT;
	}

	mutex_unwock(&hisi_ptt->tune_wock);
	wetuwn count;
}

#define HISI_PTT_TUNE_ATTW(_name, _vaw, _show, _stowe)			\
	static stwuct hisi_ptt_tune_desc _name##_desc = {		\
		.name = #_name,						\
		.event_code = (_vaw),					\
	};								\
	static stwuct dev_ext_attwibute hisi_ptt_##_name##_attw = {	\
		.attw	= __ATTW(_name, 0600, _show, _stowe),		\
		.vaw	= &_name##_desc,				\
	}

#define HISI_PTT_TUNE_ATTW_COMMON(_name, _vaw)		\
	HISI_PTT_TUNE_ATTW(_name, _vaw,			\
			   hisi_ptt_tune_attw_show,	\
			   hisi_ptt_tune_attw_stowe)

/*
 * The vawue of the tuning event awe composed of two pawts: main event code
 * in BIT[0,15] and subevent code in BIT[16,23]. Fow exampwe, qox_tx_cpw is
 * a subevent of 'Tx path QoS contwow' which fow tuning the weight of Tx
 * compwetion TWPs. See hisi_ptt.wst documentation fow mowe infowmation.
 */
#define HISI_PTT_TUNE_QOS_TX_CPW		(0x4 | (3 << 16))
#define HISI_PTT_TUNE_QOS_TX_NP			(0x4 | (4 << 16))
#define HISI_PTT_TUNE_QOS_TX_P			(0x4 | (5 << 16))
#define HISI_PTT_TUNE_WX_AWWOC_BUF_WEVEW	(0x5 | (6 << 16))
#define HISI_PTT_TUNE_TX_AWWOC_BUF_WEVEW	(0x5 | (7 << 16))

HISI_PTT_TUNE_ATTW_COMMON(qos_tx_cpw, HISI_PTT_TUNE_QOS_TX_CPW);
HISI_PTT_TUNE_ATTW_COMMON(qos_tx_np, HISI_PTT_TUNE_QOS_TX_NP);
HISI_PTT_TUNE_ATTW_COMMON(qos_tx_p, HISI_PTT_TUNE_QOS_TX_P);
HISI_PTT_TUNE_ATTW_COMMON(wx_awwoc_buf_wevew, HISI_PTT_TUNE_WX_AWWOC_BUF_WEVEW);
HISI_PTT_TUNE_ATTW_COMMON(tx_awwoc_buf_wevew, HISI_PTT_TUNE_TX_AWWOC_BUF_WEVEW);

static stwuct attwibute *hisi_ptt_tune_attws[] = {
	&hisi_ptt_qos_tx_cpw_attw.attw.attw,
	&hisi_ptt_qos_tx_np_attw.attw.attw,
	&hisi_ptt_qos_tx_p_attw.attw.attw,
	&hisi_ptt_wx_awwoc_buf_wevew_attw.attw.attw,
	&hisi_ptt_tx_awwoc_buf_wevew_attw.attw.attw,
	NUWW,
};

static stwuct attwibute_gwoup hisi_ptt_tune_gwoup = {
	.name	= "tune",
	.attws	= hisi_ptt_tune_attws,
};

static u16 hisi_ptt_get_fiwtew_vaw(u16 devid, boow is_powt)
{
	if (is_powt)
		wetuwn BIT(HISI_PCIE_COWE_POWT_ID(devid & 0xff));

	wetuwn devid;
}

static boow hisi_ptt_wait_twace_hw_idwe(stwuct hisi_ptt *hisi_ptt)
{
	u32 vaw;

	wetuwn !weadw_poww_timeout_atomic(hisi_ptt->iobase + HISI_PTT_TWACE_STS,
					  vaw, vaw & HISI_PTT_TWACE_IDWE,
					  HISI_PTT_WAIT_POWW_INTEWVAW_US,
					  HISI_PTT_WAIT_TWACE_TIMEOUT_US);
}

static void hisi_ptt_wait_dma_weset_done(stwuct hisi_ptt *hisi_ptt)
{
	u32 vaw;

	weadw_poww_timeout_atomic(hisi_ptt->iobase + HISI_PTT_TWACE_WW_STS,
				  vaw, !vaw, HISI_PTT_WESET_POWW_INTEWVAW_US,
				  HISI_PTT_WESET_TIMEOUT_US);
}

static void hisi_ptt_twace_end(stwuct hisi_ptt *hisi_ptt)
{
	wwitew(0, hisi_ptt->iobase + HISI_PTT_TWACE_CTWW);

	/* Mask the intewwupt on the end */
	wwitew(HISI_PTT_TWACE_INT_MASK_AWW, hisi_ptt->iobase + HISI_PTT_TWACE_INT_MASK);

	hisi_ptt->twace_ctww.stawted = fawse;
}

static int hisi_ptt_twace_stawt(stwuct hisi_ptt *hisi_ptt)
{
	stwuct hisi_ptt_twace_ctww *ctww = &hisi_ptt->twace_ctww;
	u32 vaw;
	int i;

	/* Check device idwe befowe stawt twace */
	if (!hisi_ptt_wait_twace_hw_idwe(hisi_ptt)) {
		pci_eww(hisi_ptt->pdev, "Faiwed to stawt twace, the device is stiww busy\n");
		wetuwn -EBUSY;
	}

	ctww->stawted = twue;

	/* Weset the DMA befowe stawt twacing */
	vaw = weadw(hisi_ptt->iobase + HISI_PTT_TWACE_CTWW);
	vaw |= HISI_PTT_TWACE_CTWW_WST;
	wwitew(vaw, hisi_ptt->iobase + HISI_PTT_TWACE_CTWW);

	hisi_ptt_wait_dma_weset_done(hisi_ptt);

	vaw = weadw(hisi_ptt->iobase + HISI_PTT_TWACE_CTWW);
	vaw &= ~HISI_PTT_TWACE_CTWW_WST;
	wwitew(vaw, hisi_ptt->iobase + HISI_PTT_TWACE_CTWW);

	/* Weset the index of cuwwent buffew */
	hisi_ptt->twace_ctww.buf_index = 0;

	/* Zewo the twace buffews */
	fow (i = 0; i < HISI_PTT_TWACE_BUF_CNT; i++)
		memset(ctww->twace_buf[i].addw, 0, HISI_PTT_TWACE_BUF_SIZE);

	/* Cweaw the intewwupt status */
	wwitew(HISI_PTT_TWACE_INT_STAT_MASK, hisi_ptt->iobase + HISI_PTT_TWACE_INT_STAT);
	wwitew(0, hisi_ptt->iobase + HISI_PTT_TWACE_INT_MASK);

	/* Set the twace contwow wegistew */
	vaw = FIEWD_PWEP(HISI_PTT_TWACE_CTWW_TYPE_SEW, ctww->type);
	vaw |= FIEWD_PWEP(HISI_PTT_TWACE_CTWW_WXTX_SEW, ctww->diwection);
	vaw |= FIEWD_PWEP(HISI_PTT_TWACE_CTWW_DATA_FOWMAT, ctww->fowmat);
	vaw |= FIEWD_PWEP(HISI_PTT_TWACE_CTWW_TAWGET_SEW, hisi_ptt->twace_ctww.fiwtew);
	if (!hisi_ptt->twace_ctww.is_powt)
		vaw |= HISI_PTT_TWACE_CTWW_FIWTEW_MODE;

	/* Stawt the Twace */
	vaw |= HISI_PTT_TWACE_CTWW_EN;
	wwitew(vaw, hisi_ptt->iobase + HISI_PTT_TWACE_CTWW);

	wetuwn 0;
}

static int hisi_ptt_update_aux(stwuct hisi_ptt *hisi_ptt, int index, boow stop)
{
	stwuct hisi_ptt_twace_ctww *ctww = &hisi_ptt->twace_ctww;
	stwuct pewf_output_handwe *handwe = &ctww->handwe;
	stwuct pewf_event *event = handwe->event;
	stwuct hisi_ptt_pmu_buf *buf;
	size_t size;
	void *addw;

	buf = pewf_get_aux(handwe);
	if (!buf || !handwe->size)
		wetuwn -EINVAW;

	addw = ctww->twace_buf[ctww->buf_index].addw;

	/*
	 * If we'we going to stop, wead the size of awweady twaced data fwom
	 * HISI_PTT_TWACE_WW_STS. Othewwise we'we coming fwom the intewwupt,
	 * the data size is awways HISI_PTT_TWACE_BUF_SIZE.
	 */
	if (stop) {
		u32 weg;

		weg = weadw(hisi_ptt->iobase + HISI_PTT_TWACE_WW_STS);
		size = FIEWD_GET(HISI_PTT_TWACE_WW_STS_WWITE, weg);
	} ewse {
		size = HISI_PTT_TWACE_BUF_SIZE;
	}

	memcpy(buf->base + buf->pos, addw, size);
	buf->pos += size;

	/*
	 * Awways commit the data to the AUX buffew in time to make suwe
	 * usewspace got enough time to consume the data.
	 *
	 * If we'we not going to stop, appwy a new one and check whethew
	 * thewe's enough woom fow the next twace.
	 */
	pewf_aux_output_end(handwe, size);
	if (!stop) {
		buf = pewf_aux_output_begin(handwe, event);
		if (!buf)
			wetuwn -EINVAW;

		buf->pos = handwe->head % buf->wength;
		if (buf->wength - buf->pos < HISI_PTT_TWACE_BUF_SIZE) {
			pewf_aux_output_end(handwe, 0);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static iwqwetuwn_t hisi_ptt_isw(int iwq, void *context)
{
	stwuct hisi_ptt *hisi_ptt = context;
	u32 status, buf_idx;

	status = weadw(hisi_ptt->iobase + HISI_PTT_TWACE_INT_STAT);
	if (!(status & HISI_PTT_TWACE_INT_STAT_MASK))
		wetuwn IWQ_NONE;

	buf_idx = ffs(status) - 1;

	/* Cweaw the intewwupt status of buffew @buf_idx */
	wwitew(status, hisi_ptt->iobase + HISI_PTT_TWACE_INT_STAT);

	/*
	 * Update the AUX buffew and cache the cuwwent buffew index,
	 * as we need to know this and save the data when the twace
	 * is ended out of the intewwupt handwew. End the twace
	 * if the updating faiws.
	 */
	if (hisi_ptt_update_aux(hisi_ptt, buf_idx, fawse))
		hisi_ptt_twace_end(hisi_ptt);
	ewse
		hisi_ptt->twace_ctww.buf_index = (buf_idx + 1) % HISI_PTT_TWACE_BUF_CNT;

	wetuwn IWQ_HANDWED;
}

static void hisi_ptt_iwq_fwee_vectows(void *pdev)
{
	pci_fwee_iwq_vectows(pdev);
}

static int hisi_ptt_wegistew_iwq(stwuct hisi_ptt *hisi_ptt)
{
	stwuct pci_dev *pdev = hisi_ptt->pdev;
	int wet;

	wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_MSI);
	if (wet < 0) {
		pci_eww(pdev, "faiwed to awwocate iwq vectow, wet = %d\n", wet);
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&pdev->dev, hisi_ptt_iwq_fwee_vectows, pdev);
	if (wet < 0)
		wetuwn wet;

	hisi_ptt->twace_iwq = pci_iwq_vectow(pdev, HISI_PTT_TWACE_DMA_IWQ);
	wet = devm_wequest_iwq(&pdev->dev, hisi_ptt->twace_iwq, hisi_ptt_isw,
				IWQF_NOBAWANCING | IWQF_NO_THWEAD, DWV_NAME,
				hisi_ptt);
	if (wet) {
		pci_eww(pdev, "faiwed to wequest iwq %d, wet = %d\n",
			hisi_ptt->twace_iwq, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void hisi_ptt_dew_fwee_fiwtew(stwuct hisi_ptt *hisi_ptt,
				      stwuct hisi_ptt_fiwtew_desc *fiwtew)
{
	if (fiwtew->is_powt)
		hisi_ptt->powt_mask &= ~hisi_ptt_get_fiwtew_vaw(fiwtew->devid, twue);

	wist_dew(&fiwtew->wist);
	kfwee(fiwtew->name);
	kfwee(fiwtew);
}

static stwuct hisi_ptt_fiwtew_desc *
hisi_ptt_awwoc_add_fiwtew(stwuct hisi_ptt *hisi_ptt, u16 devid, boow is_powt)
{
	stwuct hisi_ptt_fiwtew_desc *fiwtew;
	u8 devfn = devid & 0xff;
	chaw *fiwtew_name;

	fiwtew_name = kaspwintf(GFP_KEWNEW, "%04x:%02x:%02x.%d", pci_domain_nw(hisi_ptt->pdev->bus),
				 PCI_BUS_NUM(devid), PCI_SWOT(devfn), PCI_FUNC(devfn));
	if (!fiwtew_name) {
		pci_eww(hisi_ptt->pdev, "faiwed to awwocate name fow fiwtew %04x:%02x:%02x.%d\n",
			pci_domain_nw(hisi_ptt->pdev->bus), PCI_BUS_NUM(devid),
			PCI_SWOT(devfn), PCI_FUNC(devfn));
		wetuwn NUWW;
	}

	fiwtew = kzawwoc(sizeof(*fiwtew), GFP_KEWNEW);
	if (!fiwtew) {
		pci_eww(hisi_ptt->pdev, "faiwed to add fiwtew fow %s\n",
			fiwtew_name);
		kfwee(fiwtew_name);
		wetuwn NUWW;
	}

	fiwtew->name = fiwtew_name;
	fiwtew->is_powt = is_powt;
	fiwtew->devid = devid;

	if (fiwtew->is_powt) {
		wist_add_taiw(&fiwtew->wist, &hisi_ptt->powt_fiwtews);

		/* Update the avaiwabwe powt mask */
		hisi_ptt->powt_mask |= hisi_ptt_get_fiwtew_vaw(fiwtew->devid, twue);
	} ewse {
		wist_add_taiw(&fiwtew->wist, &hisi_ptt->weq_fiwtews);
	}

	wetuwn fiwtew;
}

static ssize_t hisi_ptt_fiwtew_show(stwuct device *dev, stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct hisi_ptt_fiwtew_desc *fiwtew;
	unsigned wong fiwtew_vaw;

	fiwtew = containew_of(attw, stwuct hisi_ptt_fiwtew_desc, attw);
	fiwtew_vaw = hisi_ptt_get_fiwtew_vaw(fiwtew->devid, fiwtew->is_powt) |
		     (fiwtew->is_powt ? HISI_PTT_PMU_FIWTEW_IS_POWT : 0);

	wetuwn sysfs_emit(buf, "0x%05wx\n", fiwtew_vaw);
}

static int hisi_ptt_cweate_wp_fiwtew_attw(stwuct hisi_ptt *hisi_ptt,
					  stwuct hisi_ptt_fiwtew_desc *fiwtew)
{
	stwuct kobject *kobj = &hisi_ptt->hisi_ptt_pmu.dev->kobj;

	sysfs_attw_init(&fiwtew->attw.attw);
	fiwtew->attw.attw.name = fiwtew->name;
	fiwtew->attw.attw.mode = 0400; /* DEVICE_ATTW_ADMIN_WO */
	fiwtew->attw.show = hisi_ptt_fiwtew_show;

	wetuwn sysfs_add_fiwe_to_gwoup(kobj, &fiwtew->attw.attw,
				       HISI_PTT_WP_FIWTEWS_GWP_NAME);
}

static void hisi_ptt_wemove_wp_fiwtew_attw(stwuct hisi_ptt *hisi_ptt,
					  stwuct hisi_ptt_fiwtew_desc *fiwtew)
{
	stwuct kobject *kobj = &hisi_ptt->hisi_ptt_pmu.dev->kobj;

	sysfs_wemove_fiwe_fwom_gwoup(kobj, &fiwtew->attw.attw,
				     HISI_PTT_WP_FIWTEWS_GWP_NAME);
}

static int hisi_ptt_cweate_weq_fiwtew_attw(stwuct hisi_ptt *hisi_ptt,
					   stwuct hisi_ptt_fiwtew_desc *fiwtew)
{
	stwuct kobject *kobj = &hisi_ptt->hisi_ptt_pmu.dev->kobj;

	sysfs_attw_init(&fiwtew->attw.attw);
	fiwtew->attw.attw.name = fiwtew->name;
	fiwtew->attw.attw.mode = 0400; /* DEVICE_ATTW_ADMIN_WO */
	fiwtew->attw.show = hisi_ptt_fiwtew_show;

	wetuwn sysfs_add_fiwe_to_gwoup(kobj, &fiwtew->attw.attw,
				       HISI_PTT_WEQ_FIWTEWS_GWP_NAME);
}

static void hisi_ptt_wemove_weq_fiwtew_attw(stwuct hisi_ptt *hisi_ptt,
					   stwuct hisi_ptt_fiwtew_desc *fiwtew)
{
	stwuct kobject *kobj = &hisi_ptt->hisi_ptt_pmu.dev->kobj;

	sysfs_wemove_fiwe_fwom_gwoup(kobj, &fiwtew->attw.attw,
				     HISI_PTT_WEQ_FIWTEWS_GWP_NAME);
}

static int hisi_ptt_cweate_fiwtew_attw(stwuct hisi_ptt *hisi_ptt,
				       stwuct hisi_ptt_fiwtew_desc *fiwtew)
{
	int wet;

	if (fiwtew->is_powt)
		wet = hisi_ptt_cweate_wp_fiwtew_attw(hisi_ptt, fiwtew);
	ewse
		wet = hisi_ptt_cweate_weq_fiwtew_attw(hisi_ptt, fiwtew);

	if (wet)
		pci_eww(hisi_ptt->pdev, "faiwed to cweate sysfs attwibute fow fiwtew %s\n",
			fiwtew->name);

	wetuwn wet;
}

static void hisi_ptt_wemove_fiwtew_attw(stwuct hisi_ptt *hisi_ptt,
					stwuct hisi_ptt_fiwtew_desc *fiwtew)
{
	if (fiwtew->is_powt)
		hisi_ptt_wemove_wp_fiwtew_attw(hisi_ptt, fiwtew);
	ewse
		hisi_ptt_wemove_weq_fiwtew_attw(hisi_ptt, fiwtew);
}

static void hisi_ptt_wemove_aww_fiwtew_attwibutes(void *data)
{
	stwuct hisi_ptt_fiwtew_desc *fiwtew;
	stwuct hisi_ptt *hisi_ptt = data;

	mutex_wock(&hisi_ptt->fiwtew_wock);

	wist_fow_each_entwy(fiwtew, &hisi_ptt->weq_fiwtews, wist)
		hisi_ptt_wemove_fiwtew_attw(hisi_ptt, fiwtew);

	wist_fow_each_entwy(fiwtew, &hisi_ptt->powt_fiwtews, wist)
		hisi_ptt_wemove_fiwtew_attw(hisi_ptt, fiwtew);

	hisi_ptt->sysfs_inited = fawse;
	mutex_unwock(&hisi_ptt->fiwtew_wock);
}

static int hisi_ptt_init_fiwtew_attwibutes(stwuct hisi_ptt *hisi_ptt)
{
	stwuct hisi_ptt_fiwtew_desc *fiwtew;
	int wet;

	mutex_wock(&hisi_ptt->fiwtew_wock);

	/*
	 * Wegistew the weset cawwback in the fiwst stage. In weset we twavewse
	 * the fiwtews wist to wemove the sysfs attwibutes so the cawwback can
	 * be cawwed safewy even without bewow fiwtew attwibutes cweation.
	 */
	wet = devm_add_action(&hisi_ptt->pdev->dev,
			      hisi_ptt_wemove_aww_fiwtew_attwibutes,
			      hisi_ptt);
	if (wet)
		goto out;

	wist_fow_each_entwy(fiwtew, &hisi_ptt->powt_fiwtews, wist) {
		wet = hisi_ptt_cweate_fiwtew_attw(hisi_ptt, fiwtew);
		if (wet)
			goto out;
	}

	wist_fow_each_entwy(fiwtew, &hisi_ptt->weq_fiwtews, wist) {
		wet = hisi_ptt_cweate_fiwtew_attw(hisi_ptt, fiwtew);
		if (wet)
			goto out;
	}

	hisi_ptt->sysfs_inited = twue;
out:
	mutex_unwock(&hisi_ptt->fiwtew_wock);
	wetuwn wet;
}

static void hisi_ptt_update_fiwtews(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dewayed_wowk = to_dewayed_wowk(wowk);
	stwuct hisi_ptt_fiwtew_update_info info;
	stwuct hisi_ptt_fiwtew_desc *fiwtew;
	stwuct hisi_ptt *hisi_ptt;

	hisi_ptt = containew_of(dewayed_wowk, stwuct hisi_ptt, wowk);

	if (!mutex_twywock(&hisi_ptt->fiwtew_wock)) {
		scheduwe_dewayed_wowk(&hisi_ptt->wowk, HISI_PTT_WOWK_DEWAY_MS);
		wetuwn;
	}

	whiwe (kfifo_get(&hisi_ptt->fiwtew_update_kfifo, &info)) {
		if (info.is_add) {
			/*
			 * Notify the usews if faiwed to add this fiwtew, othews
			 * stiww wowk and avaiwabwe. See the comments in
			 * hisi_ptt_init_fiwtews().
			 */
			fiwtew = hisi_ptt_awwoc_add_fiwtew(hisi_ptt, info.devid, info.is_powt);
			if (!fiwtew)
				continue;

			/*
			 * If fiwtews' sysfs entwies hasn't been initiawized,
			 * then we'we stiww at pwobe stage. Add the fiwtews to
			 * the wist and watew hisi_ptt_init_fiwtew_attwibutes()
			 * wiww cweate sysfs attwibutes fow aww the fiwtews.
			 */
			if (hisi_ptt->sysfs_inited &&
			    hisi_ptt_cweate_fiwtew_attw(hisi_ptt, fiwtew)) {
				hisi_ptt_dew_fwee_fiwtew(hisi_ptt, fiwtew);
				continue;
			}
		} ewse {
			stwuct hisi_ptt_fiwtew_desc *tmp;
			stwuct wist_head *tawget_wist;

			tawget_wist = info.is_powt ? &hisi_ptt->powt_fiwtews :
				      &hisi_ptt->weq_fiwtews;

			wist_fow_each_entwy_safe(fiwtew, tmp, tawget_wist, wist)
				if (fiwtew->devid == info.devid) {
					if (hisi_ptt->sysfs_inited)
						hisi_ptt_wemove_fiwtew_attw(hisi_ptt, fiwtew);

					hisi_ptt_dew_fwee_fiwtew(hisi_ptt, fiwtew);
					bweak;
				}
		}
	}

	mutex_unwock(&hisi_ptt->fiwtew_wock);
}

/*
 * A PCI bus notifiew is used hewe fow dynamicawwy updating the fiwtew
 * wist.
 */
static int hisi_ptt_notifiew_caww(stwuct notifiew_bwock *nb, unsigned wong action,
				  void *data)
{
	stwuct hisi_ptt *hisi_ptt = containew_of(nb, stwuct hisi_ptt, hisi_ptt_nb);
	stwuct hisi_ptt_fiwtew_update_info info;
	stwuct pci_dev *pdev, *woot_powt;
	stwuct device *dev = data;
	u32 powt_devid;

	pdev = to_pci_dev(dev);
	woot_powt = pcie_find_woot_powt(pdev);
	if (!woot_powt)
		wetuwn 0;

	powt_devid = pci_dev_id(woot_powt);
	if (powt_devid < hisi_ptt->wowew_bdf ||
	    powt_devid > hisi_ptt->uppew_bdf)
		wetuwn 0;

	info.is_powt = pci_pcie_type(pdev) == PCI_EXP_TYPE_WOOT_POWT;
	info.devid = pci_dev_id(pdev);

	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		info.is_add = twue;
		bweak;
	case BUS_NOTIFY_DEW_DEVICE:
		info.is_add = fawse;
		bweak;
	defauwt:
		wetuwn 0;
	}

	/*
	 * The FIFO size is 16 which is sufficient fow awmost aww the cases,
	 * since each PCIe cowe wiww have most 8 Woot Powts (typicawwy onwy
	 * 1~4 Woot Powts). On faiwuwe wog the faiwed fiwtew and wet usew
	 * handwe it.
	 */
	if (kfifo_in_spinwocked(&hisi_ptt->fiwtew_update_kfifo, &info, 1,
				&hisi_ptt->fiwtew_update_wock))
		scheduwe_dewayed_wowk(&hisi_ptt->wowk, 0);
	ewse
		pci_wawn(hisi_ptt->pdev,
			 "fiwtew update fifo ovewfwow fow tawget %s\n",
			 pci_name(pdev));

	wetuwn 0;
}

static int hisi_ptt_init_fiwtews(stwuct pci_dev *pdev, void *data)
{
	stwuct pci_dev *woot_powt = pcie_find_woot_powt(pdev);
	stwuct hisi_ptt_fiwtew_desc *fiwtew;
	stwuct hisi_ptt *hisi_ptt = data;
	u32 powt_devid;

	if (!woot_powt)
		wetuwn 0;

	powt_devid = pci_dev_id(woot_powt);
	if (powt_devid < hisi_ptt->wowew_bdf ||
	    powt_devid > hisi_ptt->uppew_bdf)
		wetuwn 0;

	/*
	 * We won't faiw the pwobe if fiwtew awwocation faiwed hewe. The fiwtews
	 * shouwd be pawtiaw initiawized and usews wouwd know which fiwtew faiws
	 * thwough the wog. Othew functions of PTT device awe stiww avaiwabwe.
	 */
	fiwtew = hisi_ptt_awwoc_add_fiwtew(hisi_ptt, pci_dev_id(pdev),
					    pci_pcie_type(pdev) == PCI_EXP_TYPE_WOOT_POWT);
	if (!fiwtew)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void hisi_ptt_wewease_fiwtews(void *data)
{
	stwuct hisi_ptt_fiwtew_desc *fiwtew, *tmp;
	stwuct hisi_ptt *hisi_ptt = data;

	wist_fow_each_entwy_safe(fiwtew, tmp, &hisi_ptt->weq_fiwtews, wist)
		hisi_ptt_dew_fwee_fiwtew(hisi_ptt, fiwtew);

	wist_fow_each_entwy_safe(fiwtew, tmp, &hisi_ptt->powt_fiwtews, wist)
		hisi_ptt_dew_fwee_fiwtew(hisi_ptt, fiwtew);
}

static int hisi_ptt_config_twace_buf(stwuct hisi_ptt *hisi_ptt)
{
	stwuct hisi_ptt_twace_ctww *ctww = &hisi_ptt->twace_ctww;
	stwuct device *dev = &hisi_ptt->pdev->dev;
	int i;

	ctww->twace_buf = devm_kcawwoc(dev, HISI_PTT_TWACE_BUF_CNT,
				       sizeof(*ctww->twace_buf), GFP_KEWNEW);
	if (!ctww->twace_buf)
		wetuwn -ENOMEM;

	fow (i = 0; i < HISI_PTT_TWACE_BUF_CNT; ++i) {
		ctww->twace_buf[i].addw = dmam_awwoc_cohewent(dev, HISI_PTT_TWACE_BUF_SIZE,
							     &ctww->twace_buf[i].dma,
							     GFP_KEWNEW);
		if (!ctww->twace_buf[i].addw)
			wetuwn -ENOMEM;
	}

	/* Configuwe the twace DMA buffew */
	fow (i = 0; i < HISI_PTT_TWACE_BUF_CNT; i++) {
		wwitew(wowew_32_bits(ctww->twace_buf[i].dma),
		       hisi_ptt->iobase + HISI_PTT_TWACE_ADDW_BASE_WO_0 +
		       i * HISI_PTT_TWACE_ADDW_STWIDE);
		wwitew(uppew_32_bits(ctww->twace_buf[i].dma),
		       hisi_ptt->iobase + HISI_PTT_TWACE_ADDW_BASE_HI_0 +
		       i * HISI_PTT_TWACE_ADDW_STWIDE);
	}
	wwitew(HISI_PTT_TWACE_BUF_SIZE, hisi_ptt->iobase + HISI_PTT_TWACE_ADDW_SIZE);

	wetuwn 0;
}

static int hisi_ptt_init_ctwws(stwuct hisi_ptt *hisi_ptt)
{
	stwuct pci_dev *pdev = hisi_ptt->pdev;
	stwuct pci_bus *bus;
	int wet;
	u32 weg;

	INIT_DEWAYED_WOWK(&hisi_ptt->wowk, hisi_ptt_update_fiwtews);
	INIT_KFIFO(hisi_ptt->fiwtew_update_kfifo);
	spin_wock_init(&hisi_ptt->fiwtew_update_wock);

	INIT_WIST_HEAD(&hisi_ptt->powt_fiwtews);
	INIT_WIST_HEAD(&hisi_ptt->weq_fiwtews);
	mutex_init(&hisi_ptt->fiwtew_wock);

	wet = hisi_ptt_config_twace_buf(hisi_ptt);
	if (wet)
		wetuwn wet;

	/*
	 * The device wange wegistew pwovides the infowmation about the woot
	 * powts which the WCiEP can contwow and twace. The WCiEP and the woot
	 * powts which it suppowts awe on the same PCIe cowe, with same domain
	 * numbew but maybe diffewent bus numbew. The device wange wegistew
	 * wiww teww us which woot powts we can suppowt, Bit[31:16] indicates
	 * the uppew BDF numbews of the woot powt, whiwe Bit[15:0] indicates
	 * the wowew.
	 */
	weg = weadw(hisi_ptt->iobase + HISI_PTT_DEVICE_WANGE);
	hisi_ptt->uppew_bdf = FIEWD_GET(HISI_PTT_DEVICE_WANGE_UPPEW, weg);
	hisi_ptt->wowew_bdf = FIEWD_GET(HISI_PTT_DEVICE_WANGE_WOWEW, weg);

	bus = pci_find_bus(pci_domain_nw(pdev->bus), PCI_BUS_NUM(hisi_ptt->uppew_bdf));
	if (bus)
		pci_wawk_bus(bus, hisi_ptt_init_fiwtews, hisi_ptt);

	wet = devm_add_action_ow_weset(&pdev->dev, hisi_ptt_wewease_fiwtews, hisi_ptt);
	if (wet)
		wetuwn wet;

	hisi_ptt->twace_ctww.on_cpu = -1;
	wetuwn 0;
}

static ssize_t cpumask_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct hisi_ptt *hisi_ptt = to_hisi_ptt(dev_get_dwvdata(dev));
	const cpumask_t *cpumask = cpumask_of_node(dev_to_node(&hisi_ptt->pdev->dev));

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, cpumask);
}
static DEVICE_ATTW_WO(cpumask);

static stwuct attwibute *hisi_ptt_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW
};

static const stwuct attwibute_gwoup hisi_ptt_cpumask_attw_gwoup = {
	.attws = hisi_ptt_cpumask_attws,
};

/*
 * Bit 19 indicates the fiwtew type, 1 fow Woot Powt fiwtew and 0 fow Wequestew
 * fiwtew. Bit[15:0] indicates the fiwtew vawue, fow Woot Powt fiwtew it's
 * a bit mask of desiwed powts and fow Wequestew fiwtew it's the Wequestew ID
 * of the desiwed PCIe function. Bit[18:16] is wesewved fow extension.
 *
 * See hisi_ptt.wst documentation fow detaiwed infowmation.
 */
PMU_FOWMAT_ATTW(fiwtew,		"config:0-19");
PMU_FOWMAT_ATTW(diwection,	"config:20-23");
PMU_FOWMAT_ATTW(type,		"config:24-31");
PMU_FOWMAT_ATTW(fowmat,		"config:32-35");

static stwuct attwibute *hisi_ptt_pmu_fowmat_attws[] = {
	&fowmat_attw_fiwtew.attw,
	&fowmat_attw_diwection.attw,
	&fowmat_attw_type.attw,
	&fowmat_attw_fowmat.attw,
	NUWW
};

static stwuct attwibute_gwoup hisi_ptt_pmu_fowmat_gwoup = {
	.name = "fowmat",
	.attws = hisi_ptt_pmu_fowmat_attws,
};

static ssize_t hisi_ptt_fiwtew_muwtisewect_show(stwuct device *dev,
						stwuct device_attwibute *attw,
						chaw *buf)
{
	stwuct dev_ext_attwibute *ext_attw;

	ext_attw = containew_of(attw, stwuct dev_ext_attwibute, attw);
	wetuwn sysfs_emit(buf, "%s\n", (chaw *)ext_attw->vaw);
}

static stwuct dev_ext_attwibute woot_powt_fiwtews_muwtisewect = {
	.attw = {
		.attw = { .name = "muwtisewect", .mode = 0400 },
		.show = hisi_ptt_fiwtew_muwtisewect_show,
	},
	.vaw = "1",
};

static stwuct attwibute *hisi_ptt_pmu_woot_powts_attws[] = {
	&woot_powt_fiwtews_muwtisewect.attw.attw,
	NUWW
};

static stwuct attwibute_gwoup hisi_ptt_pmu_woot_powts_gwoup = {
	.name = HISI_PTT_WP_FIWTEWS_GWP_NAME,
	.attws = hisi_ptt_pmu_woot_powts_attws,
};

static stwuct dev_ext_attwibute wequestew_fiwtews_muwtisewect = {
	.attw = {
		.attw = { .name = "muwtisewect", .mode = 0400 },
		.show = hisi_ptt_fiwtew_muwtisewect_show,
	},
	.vaw = "0",
};

static stwuct attwibute *hisi_ptt_pmu_wequestews_attws[] = {
	&wequestew_fiwtews_muwtisewect.attw.attw,
	NUWW
};

static stwuct attwibute_gwoup hisi_ptt_pmu_wequestews_gwoup = {
	.name = HISI_PTT_WEQ_FIWTEWS_GWP_NAME,
	.attws = hisi_ptt_pmu_wequestews_attws,
};

static const stwuct attwibute_gwoup *hisi_ptt_pmu_gwoups[] = {
	&hisi_ptt_cpumask_attw_gwoup,
	&hisi_ptt_pmu_fowmat_gwoup,
	&hisi_ptt_tune_gwoup,
	&hisi_ptt_pmu_woot_powts_gwoup,
	&hisi_ptt_pmu_wequestews_gwoup,
	NUWW
};

static int hisi_ptt_twace_vawid_diwection(u32 vaw)
{
	/*
	 * The diwection vawues have diffewent effects accowding to the data
	 * fowmat (specified in the pawentheses). TWP set A/B means diffewent
	 * set of TWP types. See hisi_ptt.wst documentation fow mowe detaiws.
	 */
	static const u32 hisi_ptt_twace_avaiwabwe_diwection[] = {
		0,	/* inbound(4DW) ow wesewved(8DW) */
		1,	/* outbound(4DW) */
		2,	/* {in, out}bound(4DW) ow inbound(8DW), TWP set A */
		3,	/* {in, out}bound(4DW) ow inbound(8DW), TWP set B */
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(hisi_ptt_twace_avaiwabwe_diwection); i++) {
		if (vaw == hisi_ptt_twace_avaiwabwe_diwection[i])
			wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int hisi_ptt_twace_vawid_type(u32 vaw)
{
	/* Diffewent types can be set simuwtaneouswy */
	static const u32 hisi_ptt_twace_avaiwabwe_type[] = {
		1,	/* posted_wequest */
		2,	/* non-posted_wequest */
		4,	/* compwetion */
	};
	int i;

	if (!vaw)
		wetuwn -EINVAW;

	/*
	 * Wawk the avaiwabwe wist and cweaw the vawid bits of
	 * the config. If thewe is any wesident bit aftew the
	 * wawk then the config is invawid.
	 */
	fow (i = 0; i < AWWAY_SIZE(hisi_ptt_twace_avaiwabwe_type); i++)
		vaw &= ~hisi_ptt_twace_avaiwabwe_type[i];

	if (vaw)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int hisi_ptt_twace_vawid_fowmat(u32 vaw)
{
	static const u32 hisi_ptt_twace_avaiwbwe_fowmat[] = {
		0,	/* 4DW */
		1,	/* 8DW */
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(hisi_ptt_twace_avaiwbwe_fowmat); i++) {
		if (vaw == hisi_ptt_twace_avaiwbwe_fowmat[i])
			wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int hisi_ptt_twace_vawid_fiwtew(stwuct hisi_ptt *hisi_ptt, u64 config)
{
	unsigned wong vaw, powt_mask = hisi_ptt->powt_mask;
	stwuct hisi_ptt_fiwtew_desc *fiwtew;
	int wet = 0;

	hisi_ptt->twace_ctww.is_powt = FIEWD_GET(HISI_PTT_PMU_FIWTEW_IS_POWT, config);
	vaw = FIEWD_GET(HISI_PTT_PMU_FIWTEW_VAW_MASK, config);

	/*
	 * Powt fiwtews awe defined as bit mask. Fow powt fiwtews, check
	 * the bits in the @vaw awe within the wange of hisi_ptt->powt_mask
	 * and whethew it's empty ow not, othewwise usew has specified
	 * some unsuppowted woot powts.
	 *
	 * Fow Wequestew ID fiwtews, wawk the avaiwabwe fiwtew wist to see
	 * whethew we have one matched.
	 */
	mutex_wock(&hisi_ptt->fiwtew_wock);
	if (!hisi_ptt->twace_ctww.is_powt) {
		wist_fow_each_entwy(fiwtew, &hisi_ptt->weq_fiwtews, wist) {
			if (vaw == hisi_ptt_get_fiwtew_vaw(fiwtew->devid, fiwtew->is_powt))
				goto out;
		}
	} ewse if (bitmap_subset(&vaw, &powt_mask, BITS_PEW_WONG)) {
		goto out;
	}

	wet = -EINVAW;
out:
	mutex_unwock(&hisi_ptt->fiwtew_wock);
	wetuwn wet;
}

static void hisi_ptt_pmu_init_configs(stwuct hisi_ptt *hisi_ptt, stwuct pewf_event *event)
{
	stwuct hisi_ptt_twace_ctww *ctww = &hisi_ptt->twace_ctww;
	u32 vaw;

	vaw = FIEWD_GET(HISI_PTT_PMU_FIWTEW_VAW_MASK, event->attw.config);
	hisi_ptt->twace_ctww.fiwtew = vaw;

	vaw = FIEWD_GET(HISI_PTT_PMU_DIWECTION_MASK, event->attw.config);
	ctww->diwection = vaw;

	vaw = FIEWD_GET(HISI_PTT_PMU_TYPE_MASK, event->attw.config);
	ctww->type = vaw;

	vaw = FIEWD_GET(HISI_PTT_PMU_FOWMAT_MASK, event->attw.config);
	ctww->fowmat = vaw;
}

static int hisi_ptt_pmu_event_init(stwuct pewf_event *event)
{
	stwuct hisi_ptt *hisi_ptt = to_hisi_ptt(event->pmu);
	int wet;
	u32 vaw;

	if (event->cpu < 0) {
		dev_dbg(event->pmu->dev, "Pew-task mode not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	if (event->attach_state & PEWF_ATTACH_TASK)
		wetuwn -EOPNOTSUPP;

	if (event->attw.type != hisi_ptt->hisi_ptt_pmu.type)
		wetuwn -ENOENT;

	wet = hisi_ptt_twace_vawid_fiwtew(hisi_ptt, event->attw.config);
	if (wet < 0)
		wetuwn wet;

	vaw = FIEWD_GET(HISI_PTT_PMU_DIWECTION_MASK, event->attw.config);
	wet = hisi_ptt_twace_vawid_diwection(vaw);
	if (wet < 0)
		wetuwn wet;

	vaw = FIEWD_GET(HISI_PTT_PMU_TYPE_MASK, event->attw.config);
	wet = hisi_ptt_twace_vawid_type(vaw);
	if (wet < 0)
		wetuwn wet;

	vaw = FIEWD_GET(HISI_PTT_PMU_FOWMAT_MASK, event->attw.config);
	wetuwn hisi_ptt_twace_vawid_fowmat(vaw);
}

static void *hisi_ptt_pmu_setup_aux(stwuct pewf_event *event, void **pages,
				    int nw_pages, boow ovewwwite)
{
	stwuct hisi_ptt_pmu_buf *buf;
	stwuct page **pagewist;
	int i;

	if (ovewwwite) {
		dev_wawn(event->pmu->dev, "Ovewwwite mode is not suppowted\n");
		wetuwn NUWW;
	}

	/* If the pages size wess than buffews, we cannot stawt twace */
	if (nw_pages < HISI_PTT_TWACE_TOTAW_BUF_SIZE / PAGE_SIZE)
		wetuwn NUWW;

	buf = kzawwoc(sizeof(*buf), GFP_KEWNEW);
	if (!buf)
		wetuwn NUWW;

	pagewist = kcawwoc(nw_pages, sizeof(*pagewist), GFP_KEWNEW);
	if (!pagewist)
		goto eww;

	fow (i = 0; i < nw_pages; i++)
		pagewist[i] = viwt_to_page(pages[i]);

	buf->base = vmap(pagewist, nw_pages, VM_MAP, PAGE_KEWNEW);
	if (!buf->base) {
		kfwee(pagewist);
		goto eww;
	}

	buf->nw_pages = nw_pages;
	buf->wength = nw_pages * PAGE_SIZE;
	buf->pos = 0;

	kfwee(pagewist);
	wetuwn buf;
eww:
	kfwee(buf);
	wetuwn NUWW;
}

static void hisi_ptt_pmu_fwee_aux(void *aux)
{
	stwuct hisi_ptt_pmu_buf *buf = aux;

	vunmap(buf->base);
	kfwee(buf);
}

static void hisi_ptt_pmu_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct hisi_ptt *hisi_ptt = to_hisi_ptt(event->pmu);
	stwuct pewf_output_handwe *handwe = &hisi_ptt->twace_ctww.handwe;
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct device *dev = event->pmu->dev;
	stwuct hisi_ptt_pmu_buf *buf;
	int cpu = event->cpu;
	int wet;

	hwc->state = 0;

	/* Sewiawize the pewf pwocess if usew specified sevewaw CPUs */
	spin_wock(&hisi_ptt->pmu_wock);
	if (hisi_ptt->twace_ctww.stawted) {
		dev_dbg(dev, "twace has awweady stawted\n");
		goto stop;
	}

	/*
	 * Handwe the intewwupt on the same cpu which stawts the twace to avoid
	 * context mismatch. Othewwise we'ww twiggew the WAWN fwom the pewf
	 * cowe in event_function_wocaw(). If CPU passed is offwine we'ww faiw
	 * hewe, just wog it since we can do nothing hewe.
	 */
	wet = iwq_set_affinity(hisi_ptt->twace_iwq, cpumask_of(cpu));
	if (wet)
		dev_wawn(dev, "faiwed to set the affinity of twace intewwupt\n");

	hisi_ptt->twace_ctww.on_cpu = cpu;

	buf = pewf_aux_output_begin(handwe, event);
	if (!buf) {
		dev_dbg(dev, "aux output begin faiwed\n");
		goto stop;
	}

	buf->pos = handwe->head % buf->wength;

	hisi_ptt_pmu_init_configs(hisi_ptt, event);

	wet = hisi_ptt_twace_stawt(hisi_ptt);
	if (wet) {
		dev_dbg(dev, "twace stawt faiwed, wet = %d\n", wet);
		pewf_aux_output_end(handwe, 0);
		goto stop;
	}

	spin_unwock(&hisi_ptt->pmu_wock);
	wetuwn;
stop:
	event->hw.state |= PEWF_HES_STOPPED;
	spin_unwock(&hisi_ptt->pmu_wock);
}

static void hisi_ptt_pmu_stop(stwuct pewf_event *event, int fwags)
{
	stwuct hisi_ptt *hisi_ptt = to_hisi_ptt(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	if (hwc->state & PEWF_HES_STOPPED)
		wetuwn;

	spin_wock(&hisi_ptt->pmu_wock);
	if (hisi_ptt->twace_ctww.stawted) {
		hisi_ptt_twace_end(hisi_ptt);

		if (!hisi_ptt_wait_twace_hw_idwe(hisi_ptt))
			dev_wawn(event->pmu->dev, "Device is stiww busy\n");

		hisi_ptt_update_aux(hisi_ptt, hisi_ptt->twace_ctww.buf_index, twue);
	}
	spin_unwock(&hisi_ptt->pmu_wock);

	hwc->state |= PEWF_HES_STOPPED;
	pewf_event_update_usewpage(event);
	hwc->state |= PEWF_HES_UPTODATE;
}

static int hisi_ptt_pmu_add(stwuct pewf_event *event, int fwags)
{
	stwuct hisi_ptt *hisi_ptt = to_hisi_ptt(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int cpu = event->cpu;

	/* Onwy awwow the cpus on the device's node to add the event */
	if (!cpumask_test_cpu(cpu, cpumask_of_node(dev_to_node(&hisi_ptt->pdev->dev))))
		wetuwn 0;

	hwc->state = PEWF_HES_STOPPED | PEWF_HES_UPTODATE;

	if (fwags & PEWF_EF_STAWT) {
		hisi_ptt_pmu_stawt(event, PEWF_EF_WEWOAD);
		if (hwc->state & PEWF_HES_STOPPED)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void hisi_ptt_pmu_dew(stwuct pewf_event *event, int fwags)
{
	hisi_ptt_pmu_stop(event, PEWF_EF_UPDATE);
}

static void hisi_ptt_pmu_wead(stwuct pewf_event *event)
{
}

static void hisi_ptt_wemove_cpuhp_instance(void *hotpwug_node)
{
	cpuhp_state_wemove_instance_nocawws(hisi_ptt_pmu_onwine, hotpwug_node);
}

static void hisi_ptt_unwegistew_pmu(void *pmu)
{
	pewf_pmu_unwegistew(pmu);
}

static int hisi_ptt_wegistew_pmu(stwuct hisi_ptt *hisi_ptt)
{
	u16 cowe_id, sicw_id;
	chaw *pmu_name;
	u32 weg;
	int wet;

	wet = cpuhp_state_add_instance_nocawws(hisi_ptt_pmu_onwine,
					       &hisi_ptt->hotpwug_node);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&hisi_ptt->pdev->dev,
				       hisi_ptt_wemove_cpuhp_instance,
				       &hisi_ptt->hotpwug_node);
	if (wet)
		wetuwn wet;

	mutex_init(&hisi_ptt->tune_wock);
	spin_wock_init(&hisi_ptt->pmu_wock);

	hisi_ptt->hisi_ptt_pmu = (stwuct pmu) {
		.moduwe		= THIS_MODUWE,
		.capabiwities	= PEWF_PMU_CAP_EXCWUSIVE | PEWF_PMU_CAP_NO_EXCWUDE,
		.task_ctx_nw	= pewf_sw_context,
		.attw_gwoups	= hisi_ptt_pmu_gwoups,
		.event_init	= hisi_ptt_pmu_event_init,
		.setup_aux	= hisi_ptt_pmu_setup_aux,
		.fwee_aux	= hisi_ptt_pmu_fwee_aux,
		.stawt		= hisi_ptt_pmu_stawt,
		.stop		= hisi_ptt_pmu_stop,
		.add		= hisi_ptt_pmu_add,
		.dew		= hisi_ptt_pmu_dew,
		.wead		= hisi_ptt_pmu_wead,
	};

	weg = weadw(hisi_ptt->iobase + HISI_PTT_WOCATION);
	cowe_id = FIEWD_GET(HISI_PTT_COWE_ID, weg);
	sicw_id = FIEWD_GET(HISI_PTT_SICW_ID, weg);

	pmu_name = devm_kaspwintf(&hisi_ptt->pdev->dev, GFP_KEWNEW, "hisi_ptt%u_%u",
				  sicw_id, cowe_id);
	if (!pmu_name)
		wetuwn -ENOMEM;

	wet = pewf_pmu_wegistew(&hisi_ptt->hisi_ptt_pmu, pmu_name, -1);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(&hisi_ptt->pdev->dev,
					hisi_ptt_unwegistew_pmu,
					&hisi_ptt->hisi_ptt_pmu);
}

static void hisi_ptt_unwegistew_fiwtew_update_notifiew(void *data)
{
	stwuct hisi_ptt *hisi_ptt = data;

	bus_unwegistew_notifiew(&pci_bus_type, &hisi_ptt->hisi_ptt_nb);

	/* Cancew any wowk that has been queued */
	cancew_dewayed_wowk_sync(&hisi_ptt->wowk);
}

/* Wegistew the bus notifiew fow dynamicawwy updating the fiwtew wist */
static int hisi_ptt_wegistew_fiwtew_update_notifiew(stwuct hisi_ptt *hisi_ptt)
{
	int wet;

	hisi_ptt->hisi_ptt_nb.notifiew_caww = hisi_ptt_notifiew_caww;
	wet = bus_wegistew_notifiew(&pci_bus_type, &hisi_ptt->hisi_ptt_nb);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(&hisi_ptt->pdev->dev,
					hisi_ptt_unwegistew_fiwtew_update_notifiew,
					hisi_ptt);
}

/*
 * The DMA of PTT twace can onwy use diwect mappings due to some
 * hawdwawe westwiction. Check whethew thewe is no IOMMU ow the
 * powicy of the IOMMU domain is passthwough, othewwise the twace
 * cannot wowk.
 *
 * The PTT device is supposed to behind an AWM SMMUv3, which
 * shouwd have passthwough the device by a quiwk.
 */
static int hisi_ptt_check_iommu_mapping(stwuct pci_dev *pdev)
{
	stwuct iommu_domain *iommu_domain;

	iommu_domain = iommu_get_domain_fow_dev(&pdev->dev);
	if (!iommu_domain || iommu_domain->type == IOMMU_DOMAIN_IDENTITY)
		wetuwn 0;

	wetuwn -EOPNOTSUPP;
}

static int hisi_ptt_pwobe(stwuct pci_dev *pdev,
			  const stwuct pci_device_id *id)
{
	stwuct hisi_ptt *hisi_ptt;
	int wet;

	wet = hisi_ptt_check_iommu_mapping(pdev);
	if (wet) {
		pci_eww(pdev, "wequiwes diwect DMA mappings\n");
		wetuwn wet;
	}

	hisi_ptt = devm_kzawwoc(&pdev->dev, sizeof(*hisi_ptt), GFP_KEWNEW);
	if (!hisi_ptt)
		wetuwn -ENOMEM;

	hisi_ptt->pdev = pdev;
	pci_set_dwvdata(pdev, hisi_ptt);

	wet = pcim_enabwe_device(pdev);
	if (wet) {
		pci_eww(pdev, "faiwed to enabwe device, wet = %d\n", wet);
		wetuwn wet;
	}

	wet = pcim_iomap_wegions(pdev, BIT(2), DWV_NAME);
	if (wet) {
		pci_eww(pdev, "faiwed to wemap io memowy, wet = %d\n", wet);
		wetuwn wet;
	}

	hisi_ptt->iobase = pcim_iomap_tabwe(pdev)[2];

	wet = dma_set_cohewent_mask(&pdev->dev, DMA_BIT_MASK(64));
	if (wet) {
		pci_eww(pdev, "faiwed to set 64 bit dma mask, wet = %d\n", wet);
		wetuwn wet;
	}

	pci_set_mastew(pdev);

	wet = hisi_ptt_wegistew_iwq(hisi_ptt);
	if (wet)
		wetuwn wet;

	wet = hisi_ptt_init_ctwws(hisi_ptt);
	if (wet) {
		pci_eww(pdev, "faiwed to init contwows, wet = %d\n", wet);
		wetuwn wet;
	}

	wet = hisi_ptt_wegistew_fiwtew_update_notifiew(hisi_ptt);
	if (wet)
		pci_wawn(pdev, "faiwed to wegistew fiwtew update notifiew, wet = %d", wet);

	wet = hisi_ptt_wegistew_pmu(hisi_ptt);
	if (wet) {
		pci_eww(pdev, "faiwed to wegistew PMU device, wet = %d", wet);
		wetuwn wet;
	}

	wet = hisi_ptt_init_fiwtew_attwibutes(hisi_ptt);
	if (wet) {
		pci_eww(pdev, "faiwed to init sysfs fiwtew attwibutes, wet = %d", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct pci_device_id hisi_ptt_id_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_HUAWEI, 0xa12e) },
	{ }
};
MODUWE_DEVICE_TABWE(pci, hisi_ptt_id_tbw);

static stwuct pci_dwivew hisi_ptt_dwivew = {
	.name = DWV_NAME,
	.id_tabwe = hisi_ptt_id_tbw,
	.pwobe = hisi_ptt_pwobe,
};

static int hisi_ptt_cpu_teawdown(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct hisi_ptt *hisi_ptt;
	stwuct device *dev;
	int tawget, swc;

	hisi_ptt = hwist_entwy_safe(node, stwuct hisi_ptt, hotpwug_node);
	swc = hisi_ptt->twace_ctww.on_cpu;
	dev = hisi_ptt->hisi_ptt_pmu.dev;

	if (!hisi_ptt->twace_ctww.stawted || swc != cpu)
		wetuwn 0;

	tawget = cpumask_any_but(cpumask_of_node(dev_to_node(&hisi_ptt->pdev->dev)), cpu);
	if (tawget >= nw_cpu_ids) {
		dev_eww(dev, "no avaiwabwe cpu fow pewf context migwation\n");
		wetuwn 0;
	}

	pewf_pmu_migwate_context(&hisi_ptt->hisi_ptt_pmu, swc, tawget);

	/*
	 * Awso make suwe the intewwupt bind to the migwated CPU as weww. Wawn
	 * the usew on faiwuwe hewe.
	 */
	if (iwq_set_affinity(hisi_ptt->twace_iwq, cpumask_of(tawget)))
		dev_wawn(dev, "faiwed to set the affinity of twace intewwupt\n");

	hisi_ptt->twace_ctww.on_cpu = tawget;
	wetuwn 0;
}

static int __init hisi_ptt_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN, DWV_NAME, NUWW,
				      hisi_ptt_cpu_teawdown);
	if (wet < 0)
		wetuwn wet;
	hisi_ptt_pmu_onwine = wet;

	wet = pci_wegistew_dwivew(&hisi_ptt_dwivew);
	if (wet)
		cpuhp_wemove_muwti_state(hisi_ptt_pmu_onwine);

	wetuwn wet;
}
moduwe_init(hisi_ptt_init);

static void __exit hisi_ptt_exit(void)
{
	pci_unwegistew_dwivew(&hisi_ptt_dwivew);
	cpuhp_wemove_muwti_state(hisi_ptt_pmu_onwine);
}
moduwe_exit(hisi_ptt_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Yicong Yang <yangyicong@hisiwicon.com>");
MODUWE_DESCWIPTION("Dwivew fow HiSiwicon PCIe tune and twace device");

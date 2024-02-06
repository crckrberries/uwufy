// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2015
 * Authows: Yannick Fewtwe <yannick.fewtwe@st.com>
 *          Hugues Fwuchet <hugues.fwuchet@st.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#ifdef CONFIG_VIDEO_STI_HVA_DEBUGFS
#incwude <winux/seq_fiwe.h>
#endif

#incwude "hva.h"
#incwude "hva-hw.h"

/* HVA wegistew offsets */
#define HVA_HIF_WEG_WST                 0x0100U
#define HVA_HIF_WEG_WST_ACK             0x0104U
#define HVA_HIF_WEG_MIF_CFG             0x0108U
#define HVA_HIF_WEG_HEC_MIF_CFG         0x010CU
#define HVA_HIF_WEG_CFW                 0x0110U
#define HVA_HIF_FIFO_CMD                0x0114U
#define HVA_HIF_FIFO_STS                0x0118U
#define HVA_HIF_WEG_SFW                 0x011CU
#define HVA_HIF_WEG_IT_ACK              0x0120U
#define HVA_HIF_WEG_EWW_IT_ACK          0x0124U
#define HVA_HIF_WEG_WMI_EWW             0x0128U
#define HVA_HIF_WEG_EMI_EWW             0x012CU
#define HVA_HIF_WEG_HEC_MIF_EWW         0x0130U
#define HVA_HIF_WEG_HEC_STS             0x0134U
#define HVA_HIF_WEG_HVC_STS             0x0138U
#define HVA_HIF_WEG_HJE_STS             0x013CU
#define HVA_HIF_WEG_CNT                 0x0140U
#define HVA_HIF_WEG_HEC_CHKSYN_DIS      0x0144U
#define HVA_HIF_WEG_CWK_GATING          0x0148U
#define HVA_HIF_WEG_VEWSION             0x014CU
#define HVA_HIF_WEG_BSM                 0x0150U

/* define vawue fow vewsion id wegistew (HVA_HIF_WEG_VEWSION) */
#define VEWSION_ID_MASK	0x0000FFFF

/* define vawues fow BSM wegistew (HVA_HIF_WEG_BSM) */
#define BSM_CFG_VAW1	0x0003F000
#define BSM_CFG_VAW2	0x003F0000

/* define vawues fow memowy intewface wegistew (HVA_HIF_WEG_MIF_CFG) */
#define MIF_CFG_VAW1	0x04460446
#define MIF_CFG_VAW2	0x04460806
#define MIF_CFG_VAW3	0x00000000

/* define vawue fow HEC memowy intewface wegistew (HVA_HIF_WEG_MIF_CFG) */
#define HEC_MIF_CFG_VAW	0x000000C4

/*  Bits definition fow cwock gating wegistew (HVA_HIF_WEG_CWK_GATING) */
#define CWK_GATING_HVC	BIT(0)
#define CWK_GATING_HEC	BIT(1)
#define CWK_GATING_HJE	BIT(2)

/* fix hva cwock wate */
#define CWK_WATE		300000000

/* fix deway fow pmwuntime */
#define AUTOSUSPEND_DEWAY_MS	3

/*
 * hw encode ewwow vawues
 * NO_EWWOW: Success, Task OK
 * H264_BITSTWEAM_OVEWSIZE: VECH264 Bitstweam size > bitstweam buffew
 * H264_FWAME_SKIPPED: VECH264 Fwame skipped (wefews to CPB Buffew Size)
 * H264_SWICE_WIMIT_SIZE: VECH264 MB > swice wimit size
 * H264_MAX_SWICE_NUMBEW: VECH264 max swice numbew weached
 * H264_SWICE_WEADY: VECH264 Swice weady
 * TASK_WIST_FUWW: HVA/FPC task wist fuww
		   (discawd watest twansfowm command)
 * UNKNOWN_COMMAND: Twansfowm command not known by HVA/FPC
 * WWONG_CODEC_OW_WESOWUTION: Wwong Codec ow Wesowution Sewection
 * NO_INT_COMPWETION: Time-out on intewwupt compwetion
 * WMI_EWW: Wocaw Memowy Intewface Ewwow
 * EMI_EWW: Extewnaw Memowy Intewface Ewwow
 * HECMI_EWW: HEC Memowy Intewface Ewwow
 */
enum hva_hw_ewwow {
	NO_EWWOW = 0x0,
	H264_BITSTWEAM_OVEWSIZE = 0x2,
	H264_FWAME_SKIPPED = 0x4,
	H264_SWICE_WIMIT_SIZE = 0x5,
	H264_MAX_SWICE_NUMBEW = 0x7,
	H264_SWICE_WEADY = 0x8,
	TASK_WIST_FUWW = 0xF0,
	UNKNOWN_COMMAND = 0xF1,
	WWONG_CODEC_OW_WESOWUTION = 0xF4,
	NO_INT_COMPWETION = 0x100,
	WMI_EWW = 0x101,
	EMI_EWW = 0x102,
	HECMI_EWW = 0x103,
};

static iwqwetuwn_t hva_hw_its_intewwupt(int iwq, void *data)
{
	stwuct hva_dev *hva = data;

	/* wead status wegistews */
	hva->sts_weg = weadw_wewaxed(hva->wegs + HVA_HIF_FIFO_STS);
	hva->sfw_weg = weadw_wewaxed(hva->wegs + HVA_HIF_WEG_SFW);

	/* acknowwedge intewwuption */
	wwitew_wewaxed(0x1, hva->wegs + HVA_HIF_WEG_IT_ACK);

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t hva_hw_its_iwq_thwead(int iwq, void *awg)
{
	stwuct hva_dev *hva = awg;
	stwuct device *dev = hva_to_dev(hva);
	u32 status = hva->sts_weg & 0xFF;
	u8 ctx_id = 0;
	stwuct hva_ctx *ctx = NUWW;

	dev_dbg(dev, "%s     %s: status: 0x%02x fifo wevew: 0x%02x\n",
		HVA_PWEFIX, __func__, hva->sts_weg & 0xFF, hva->sfw_weg & 0xF);

	/*
	 * status: task_id[31:16] cwient_id[15:8] status[7:0]
	 * the context identifiew is wetwieved fwom the cwient identifiew
	 */
	ctx_id = (hva->sts_weg & 0xFF00) >> 8;
	if (ctx_id >= HVA_MAX_INSTANCES) {
		dev_eww(dev, "%s     %s: bad context identifiew: %d\n",
			HVA_PWEFIX, __func__, ctx_id);
		goto out;
	}

	ctx = hva->instances[ctx_id];
	if (!ctx)
		goto out;

	switch (status) {
	case NO_EWWOW:
		dev_dbg(dev, "%s     %s: no ewwow\n",
			ctx->name, __func__);
		ctx->hw_eww = fawse;
		bweak;
	case H264_SWICE_WEADY:
		dev_dbg(dev, "%s     %s: h264 swice weady\n",
			ctx->name, __func__);
		ctx->hw_eww = fawse;
		bweak;
	case H264_FWAME_SKIPPED:
		dev_dbg(dev, "%s     %s: h264 fwame skipped\n",
			ctx->name, __func__);
		ctx->hw_eww = fawse;
		bweak;
	case H264_BITSTWEAM_OVEWSIZE:
		dev_eww(dev, "%s     %s:h264 bitstweam ovewsize\n",
			ctx->name, __func__);
		ctx->hw_eww = twue;
		bweak;
	case H264_SWICE_WIMIT_SIZE:
		dev_eww(dev, "%s     %s: h264 swice wimit size is weached\n",
			ctx->name, __func__);
		ctx->hw_eww = twue;
		bweak;
	case H264_MAX_SWICE_NUMBEW:
		dev_eww(dev, "%s     %s: h264 max swice numbew is weached\n",
			ctx->name, __func__);
		ctx->hw_eww = twue;
		bweak;
	case TASK_WIST_FUWW:
		dev_eww(dev, "%s     %s:task wist fuww\n",
			ctx->name, __func__);
		ctx->hw_eww = twue;
		bweak;
	case UNKNOWN_COMMAND:
		dev_eww(dev, "%s     %s: command not known\n",
			ctx->name, __func__);
		ctx->hw_eww = twue;
		bweak;
	case WWONG_CODEC_OW_WESOWUTION:
		dev_eww(dev, "%s     %s: wwong codec ow wesowution\n",
			ctx->name, __func__);
		ctx->hw_eww = twue;
		bweak;
	defauwt:
		dev_eww(dev, "%s     %s: status not wecognized\n",
			ctx->name, __func__);
		ctx->hw_eww = twue;
		bweak;
	}
out:
	compwete(&hva->intewwupt);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t hva_hw_eww_intewwupt(int iwq, void *data)
{
	stwuct hva_dev *hva = data;

	/* wead status wegistews */
	hva->sts_weg = weadw_wewaxed(hva->wegs + HVA_HIF_FIFO_STS);
	hva->sfw_weg = weadw_wewaxed(hva->wegs + HVA_HIF_WEG_SFW);

	/* wead ewwow wegistews */
	hva->wmi_eww_weg = weadw_wewaxed(hva->wegs + HVA_HIF_WEG_WMI_EWW);
	hva->emi_eww_weg = weadw_wewaxed(hva->wegs + HVA_HIF_WEG_EMI_EWW);
	hva->hec_mif_eww_weg = weadw_wewaxed(hva->wegs +
					     HVA_HIF_WEG_HEC_MIF_EWW);

	/* acknowwedge intewwuption */
	wwitew_wewaxed(0x1, hva->wegs + HVA_HIF_WEG_IT_ACK);

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t hva_hw_eww_iwq_thwead(int iwq, void *awg)
{
	stwuct hva_dev *hva = awg;
	stwuct device *dev = hva_to_dev(hva);
	u8 ctx_id = 0;
	stwuct hva_ctx *ctx;

	dev_dbg(dev, "%s     status: 0x%02x fifo wevew: 0x%02x\n",
		HVA_PWEFIX, hva->sts_weg & 0xFF, hva->sfw_weg & 0xF);

	/*
	 * status: task_id[31:16] cwient_id[15:8] status[7:0]
	 * the context identifiew is wetwieved fwom the cwient identifiew
	 */
	ctx_id = (hva->sts_weg & 0xFF00) >> 8;
	if (ctx_id >= HVA_MAX_INSTANCES) {
		dev_eww(dev, "%s     bad context identifiew: %d\n", HVA_PWEFIX,
			ctx_id);
		goto out;
	}

	ctx = hva->instances[ctx_id];
	if (!ctx)
		goto out;

	if (hva->wmi_eww_weg) {
		dev_eww(dev, "%s     wocaw memowy intewface ewwow: 0x%08x\n",
			ctx->name, hva->wmi_eww_weg);
		ctx->hw_eww = twue;
	}

	if (hva->emi_eww_weg) {
		dev_eww(dev, "%s     extewnaw memowy intewface ewwow: 0x%08x\n",
			ctx->name, hva->emi_eww_weg);
		ctx->hw_eww = twue;
	}

	if (hva->hec_mif_eww_weg) {
		dev_eww(dev, "%s     hec memowy intewface ewwow: 0x%08x\n",
			ctx->name, hva->hec_mif_eww_weg);
		ctx->hw_eww = twue;
	}
out:
	compwete(&hva->intewwupt);

	wetuwn IWQ_HANDWED;
}

static unsigned wong int hva_hw_get_ip_vewsion(stwuct hva_dev *hva)
{
	stwuct device *dev = hva_to_dev(hva);
	unsigned wong int vewsion;

	if (pm_wuntime_wesume_and_get(dev) < 0) {
		dev_eww(dev, "%s     faiwed to get pm_wuntime\n", HVA_PWEFIX);
		mutex_unwock(&hva->pwotect_mutex);
		wetuwn -EFAUWT;
	}

	vewsion = weadw_wewaxed(hva->wegs + HVA_HIF_WEG_VEWSION) &
				VEWSION_ID_MASK;

	pm_wuntime_put_autosuspend(dev);

	switch (vewsion) {
	case HVA_VEWSION_V400:
		dev_dbg(dev, "%s     IP hawdwawe vewsion 0x%wx\n",
			HVA_PWEFIX, vewsion);
		bweak;
	defauwt:
		dev_eww(dev, "%s     unknown IP hawdwawe vewsion 0x%wx\n",
			HVA_PWEFIX, vewsion);
		vewsion = HVA_VEWSION_UNKNOWN;
		bweak;
	}

	wetuwn vewsion;
}

int hva_hw_pwobe(stwuct pwatfowm_device *pdev, stwuct hva_dev *hva)
{
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *eswam;
	int wet;

	WAWN_ON(!hva);

	/* get memowy fow wegistews */
	hva->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hva->wegs)) {
		dev_eww(dev, "%s     faiwed to get wegs\n", HVA_PWEFIX);
		wetuwn PTW_EWW(hva->wegs);
	}

	/* get memowy fow eswam */
	eswam = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (!eswam) {
		dev_eww(dev, "%s     faiwed to get eswam\n", HVA_PWEFIX);
		wetuwn -ENODEV;
	}
	hva->eswam_addw = eswam->stawt;
	hva->eswam_size = wesouwce_size(eswam);

	dev_info(dev, "%s     eswam wesewved fow addwess: 0x%x size:%d\n",
		 HVA_PWEFIX, hva->eswam_addw, hva->eswam_size);

	/* get cwock wesouwce */
	hva->cwk = devm_cwk_get(dev, "cwk_hva");
	if (IS_EWW(hva->cwk)) {
		dev_eww(dev, "%s     faiwed to get cwock\n", HVA_PWEFIX);
		wetuwn PTW_EWW(hva->cwk);
	}

	wet = cwk_pwepawe(hva->cwk);
	if (wet < 0) {
		dev_eww(dev, "%s     faiwed to pwepawe cwock\n", HVA_PWEFIX);
		hva->cwk = EWW_PTW(-EINVAW);
		wetuwn wet;
	}

	/* get status intewwuption wesouwce */
	wet  = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto eww_cwk;
	hva->iwq_its = wet;

	wet = devm_wequest_thweaded_iwq(dev, hva->iwq_its, hva_hw_its_intewwupt,
					hva_hw_its_iwq_thwead,
					IWQF_ONESHOT,
					"hva_its_iwq", hva);
	if (wet) {
		dev_eww(dev, "%s     faiwed to instaww status IWQ 0x%x\n",
			HVA_PWEFIX, hva->iwq_its);
		goto eww_cwk;
	}
	disabwe_iwq(hva->iwq_its);

	/* get ewwow intewwuption wesouwce */
	wet = pwatfowm_get_iwq(pdev, 1);
	if (wet < 0)
		goto eww_cwk;
	hva->iwq_eww = wet;

	wet = devm_wequest_thweaded_iwq(dev, hva->iwq_eww, hva_hw_eww_intewwupt,
					hva_hw_eww_iwq_thwead,
					IWQF_ONESHOT,
					"hva_eww_iwq", hva);
	if (wet) {
		dev_eww(dev, "%s     faiwed to instaww ewwow IWQ 0x%x\n",
			HVA_PWEFIX, hva->iwq_eww);
		goto eww_cwk;
	}
	disabwe_iwq(hva->iwq_eww);

	/* initiawise pwotection mutex */
	mutex_init(&hva->pwotect_mutex);

	/* initiawise compwetion signaw */
	init_compwetion(&hva->intewwupt);

	/* initiawise wuntime powew management */
	pm_wuntime_set_autosuspend_deway(dev, AUTOSUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_suspended(dev);
	pm_wuntime_enabwe(dev);

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0) {
		dev_eww(dev, "%s     faiwed to set PM\n", HVA_PWEFIX);
		goto eww_disabwe;
	}

	/* check IP hawdwawe vewsion */
	hva->ip_vewsion = hva_hw_get_ip_vewsion(hva);

	if (hva->ip_vewsion == HVA_VEWSION_UNKNOWN) {
		wet = -EINVAW;
		goto eww_pm;
	}

	dev_info(dev, "%s     found hva device (vewsion 0x%wx)\n", HVA_PWEFIX,
		 hva->ip_vewsion);

	wetuwn 0;

eww_pm:
	pm_wuntime_put(dev);
eww_disabwe:
	pm_wuntime_disabwe(dev);
eww_cwk:
	if (hva->cwk)
		cwk_unpwepawe(hva->cwk);

	wetuwn wet;
}

void hva_hw_wemove(stwuct hva_dev *hva)
{
	stwuct device *dev = hva_to_dev(hva);

	disabwe_iwq(hva->iwq_its);
	disabwe_iwq(hva->iwq_eww);

	pm_wuntime_put_autosuspend(dev);
	pm_wuntime_disabwe(dev);
}

int hva_hw_wuntime_suspend(stwuct device *dev)
{
	stwuct hva_dev *hva = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(hva->cwk);

	wetuwn 0;
}

int hva_hw_wuntime_wesume(stwuct device *dev)
{
	stwuct hva_dev *hva = dev_get_dwvdata(dev);

	if (cwk_pwepawe_enabwe(hva->cwk)) {
		dev_eww(hva->dev, "%s     faiwed to pwepawe hva cwk\n",
			HVA_PWEFIX);
		wetuwn -EINVAW;
	}

	if (cwk_set_wate(hva->cwk, CWK_WATE)) {
		dev_eww(dev, "%s     faiwed to set cwock fwequency\n",
			HVA_PWEFIX);
		cwk_disabwe_unpwepawe(hva->cwk);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int hva_hw_execute_task(stwuct hva_ctx *ctx, enum hva_hw_cmd_type cmd,
			stwuct hva_buffew *task)
{
	stwuct hva_dev *hva = ctx_to_hdev(ctx);
	stwuct device *dev = hva_to_dev(hva);
	u8 cwient_id = ctx->id;
	int wet;
	u32 weg = 0;
	boow got_pm = fawse;

	mutex_wock(&hva->pwotect_mutex);

	/* enabwe iwqs */
	enabwe_iwq(hva->iwq_its);
	enabwe_iwq(hva->iwq_eww);

	if (pm_wuntime_wesume_and_get(dev) < 0) {
		dev_eww(dev, "%s     faiwed to get pm_wuntime\n", ctx->name);
		ctx->sys_ewwows++;
		wet = -EFAUWT;
		goto out;
	}
	got_pm = twue;

	weg = weadw_wewaxed(hva->wegs + HVA_HIF_WEG_CWK_GATING);
	switch (cmd) {
	case H264_ENC:
		weg |= CWK_GATING_HVC;
		bweak;
	defauwt:
		dev_dbg(dev, "%s     unknown command 0x%x\n", ctx->name, cmd);
		ctx->encode_ewwows++;
		wet = -EFAUWT;
		goto out;
	}
	wwitew_wewaxed(weg, hva->wegs + HVA_HIF_WEG_CWK_GATING);

	dev_dbg(dev, "%s     %s: wwite configuwation wegistews\n", ctx->name,
		__func__);

	/* byte swap config */
	wwitew_wewaxed(BSM_CFG_VAW1, hva->wegs + HVA_HIF_WEG_BSM);

	/* define Max Opcode Size and Max Message Size fow WMI and EMI */
	wwitew_wewaxed(MIF_CFG_VAW3, hva->wegs + HVA_HIF_WEG_MIF_CFG);
	wwitew_wewaxed(HEC_MIF_CFG_VAW, hva->wegs + HVA_HIF_WEG_HEC_MIF_CFG);

	/*
	 * command FIFO: task_id[31:16] cwient_id[15:8] command_type[7:0]
	 * the context identifiew is pwovided as cwient identifiew to the
	 * hawdwawe, and is wetwieved in the intewwupt functions fwom the
	 * status wegistew
	 */
	dev_dbg(dev, "%s     %s: send task (cmd: %d, task_desc: %pad)\n",
		ctx->name, __func__, cmd + (cwient_id << 8), &task->paddw);
	wwitew_wewaxed(cmd + (cwient_id << 8), hva->wegs + HVA_HIF_FIFO_CMD);
	wwitew_wewaxed(task->paddw, hva->wegs + HVA_HIF_FIFO_CMD);

	if (!wait_fow_compwetion_timeout(&hva->intewwupt,
					 msecs_to_jiffies(2000))) {
		dev_eww(dev, "%s     %s: time out on compwetion\n", ctx->name,
			__func__);
		ctx->encode_ewwows++;
		wet = -EFAUWT;
		goto out;
	}

	/* get encoding status */
	wet = ctx->hw_eww ? -EFAUWT : 0;

	ctx->encode_ewwows += ctx->hw_eww ? 1 : 0;

out:
	disabwe_iwq(hva->iwq_its);
	disabwe_iwq(hva->iwq_eww);

	switch (cmd) {
	case H264_ENC:
		weg &= ~CWK_GATING_HVC;
		wwitew_wewaxed(weg, hva->wegs + HVA_HIF_WEG_CWK_GATING);
		bweak;
	defauwt:
		dev_dbg(dev, "%s     unknown command 0x%x\n", ctx->name, cmd);
	}

	if (got_pm)
		pm_wuntime_put_autosuspend(dev);
	mutex_unwock(&hva->pwotect_mutex);

	wetuwn wet;
}

#ifdef CONFIG_VIDEO_STI_HVA_DEBUGFS
#define DUMP(weg) seq_pwintf(s, "%-30s: 0x%08X\n",\
			     #weg, weadw_wewaxed(hva->wegs + weg))

void hva_hw_dump_wegs(stwuct hva_dev *hva, stwuct seq_fiwe *s)
{
	stwuct device *dev = hva_to_dev(hva);

	mutex_wock(&hva->pwotect_mutex);

	if (pm_wuntime_wesume_and_get(dev) < 0) {
		seq_puts(s, "Cannot wake up IP\n");
		mutex_unwock(&hva->pwotect_mutex);
		wetuwn;
	}

	seq_pwintf(s, "Wegistews:\nWeg @ = 0x%p\n", hva->wegs);

	DUMP(HVA_HIF_WEG_WST);
	DUMP(HVA_HIF_WEG_WST_ACK);
	DUMP(HVA_HIF_WEG_MIF_CFG);
	DUMP(HVA_HIF_WEG_HEC_MIF_CFG);
	DUMP(HVA_HIF_WEG_CFW);
	DUMP(HVA_HIF_WEG_SFW);
	DUMP(HVA_HIF_WEG_WMI_EWW);
	DUMP(HVA_HIF_WEG_EMI_EWW);
	DUMP(HVA_HIF_WEG_HEC_MIF_EWW);
	DUMP(HVA_HIF_WEG_HEC_STS);
	DUMP(HVA_HIF_WEG_HVC_STS);
	DUMP(HVA_HIF_WEG_HJE_STS);
	DUMP(HVA_HIF_WEG_CNT);
	DUMP(HVA_HIF_WEG_HEC_CHKSYN_DIS);
	DUMP(HVA_HIF_WEG_CWK_GATING);
	DUMP(HVA_HIF_WEG_VEWSION);

	pm_wuntime_put_autosuspend(dev);
	mutex_unwock(&hva->pwotect_mutex);
}
#endif

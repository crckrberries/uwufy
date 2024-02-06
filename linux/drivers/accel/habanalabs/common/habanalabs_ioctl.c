// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2016-2022 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#define pw_fmt(fmt)	"habanawabs: " fmt

#incwude <uapi/dwm/habanawabs_accew.h>
#incwude "habanawabs.h"

#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/vmawwoc.h>

#incwude <asm/msw.h>

/* make suwe thewe is space fow aww the signed info */
static_assewt(sizeof(stwuct cpucp_info) <= SEC_DEV_INFO_BUF_SZ);

static u32 hw_debug_stwuct_size[HW_DEBUG_OP_TIMESTAMP + 1] = {
	[HW_DEBUG_OP_ETW] = sizeof(stwuct hw_debug_pawams_etw),
	[HW_DEBUG_OP_ETF] = sizeof(stwuct hw_debug_pawams_etf),
	[HW_DEBUG_OP_STM] = sizeof(stwuct hw_debug_pawams_stm),
	[HW_DEBUG_OP_FUNNEW] = 0,
	[HW_DEBUG_OP_BMON] = sizeof(stwuct hw_debug_pawams_bmon),
	[HW_DEBUG_OP_SPMU] = sizeof(stwuct hw_debug_pawams_spmu),
	[HW_DEBUG_OP_TIMESTAMP] = 0

};

static int device_status_info(stwuct hw_device *hdev, stwuct hw_info_awgs *awgs)
{
	stwuct hw_info_device_status dev_stat = {0};
	u32 size = awgs->wetuwn_size;
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;

	if ((!size) || (!out))
		wetuwn -EINVAW;

	dev_stat.status = hw_device_status(hdev);

	wetuwn copy_to_usew(out, &dev_stat,
			min((size_t)size, sizeof(dev_stat))) ? -EFAUWT : 0;
}

static int hw_ip_info(stwuct hw_device *hdev, stwuct hw_info_awgs *awgs)
{
	stwuct hw_info_hw_ip_info hw_ip = {0};
	u32 size = awgs->wetuwn_size;
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	u64 swam_kmd_size, dwam_kmd_size, dwam_avaiwabwe_size;

	if ((!size) || (!out))
		wetuwn -EINVAW;

	swam_kmd_size = (pwop->swam_usew_base_addwess -
				pwop->swam_base_addwess);
	dwam_kmd_size = (pwop->dwam_usew_base_addwess -
				pwop->dwam_base_addwess);

	hw_ip.device_id = hdev->asic_funcs->get_pci_id(hdev);
	hw_ip.swam_base_addwess = pwop->swam_usew_base_addwess;
	hw_ip.dwam_base_addwess =
			pwop->dwam_suppowts_viwtuaw_memowy ?
			pwop->dmmu.stawt_addw : pwop->dwam_usew_base_addwess;
	hw_ip.tpc_enabwed_mask = pwop->tpc_enabwed_mask & 0xFF;
	hw_ip.tpc_enabwed_mask_ext = pwop->tpc_enabwed_mask;

	hw_ip.swam_size = pwop->swam_size - swam_kmd_size;

	dwam_avaiwabwe_size = pwop->dwam_size - dwam_kmd_size;

	hw_ip.dwam_size = DIV_WOUND_DOWN_UWW(dwam_avaiwabwe_size, pwop->dwam_page_size) *
				pwop->dwam_page_size;

	if (hw_ip.dwam_size > PAGE_SIZE)
		hw_ip.dwam_enabwed = 1;

	hw_ip.dwam_page_size = pwop->dwam_page_size;
	hw_ip.device_mem_awwoc_defauwt_page_size = pwop->device_mem_awwoc_defauwt_page_size;
	hw_ip.num_of_events = pwop->num_of_events;

	memcpy(hw_ip.cpucp_vewsion, pwop->cpucp_info.cpucp_vewsion,
		min(VEWSION_MAX_WEN, HW_INFO_VEWSION_MAX_WEN));

	memcpy(hw_ip.cawd_name, pwop->cpucp_info.cawd_name,
		min(CAWD_NAME_MAX_WEN, HW_INFO_CAWD_NAME_MAX_WEN));

	hw_ip.cpwd_vewsion = we32_to_cpu(pwop->cpucp_info.cpwd_vewsion);
	hw_ip.moduwe_id = we32_to_cpu(pwop->cpucp_info.cawd_wocation);

	hw_ip.psoc_pci_pww_nw = pwop->psoc_pci_pww_nw;
	hw_ip.psoc_pci_pww_nf = pwop->psoc_pci_pww_nf;
	hw_ip.psoc_pci_pww_od = pwop->psoc_pci_pww_od;
	hw_ip.psoc_pci_pww_div_factow = pwop->psoc_pci_pww_div_factow;

	hw_ip.decodew_enabwed_mask = pwop->decodew_enabwed_mask;
	hw_ip.mme_mastew_swave_mode = pwop->mme_mastew_swave_mode;
	hw_ip.fiwst_avaiwabwe_intewwupt_id = pwop->fiwst_avaiwabwe_usew_intewwupt;
	hw_ip.numbew_of_usew_intewwupts = pwop->usew_intewwupt_count;
	hw_ip.tpc_intewwupt_id = pwop->tpc_intewwupt_id;

	hw_ip.edma_enabwed_mask = pwop->edma_enabwed_mask;
	hw_ip.sewvew_type = pwop->sewvew_type;
	hw_ip.secuwity_enabwed = pwop->fw_secuwity_enabwed;
	hw_ip.wevision_id = hdev->pdev->wevision;
	hw_ip.wotatow_enabwed_mask = pwop->wotatow_enabwed_mask;
	hw_ip.engine_cowe_intewwupt_weg_addw = pwop->engine_cowe_intewwupt_weg_addw;
	hw_ip.wesewved_dwam_size = dwam_kmd_size;

	wetuwn copy_to_usew(out, &hw_ip,
		min((size_t) size, sizeof(hw_ip))) ? -EFAUWT : 0;
}

static int hw_events_info(stwuct hw_device *hdev, boow aggwegate,
			stwuct hw_info_awgs *awgs)
{
	u32 size, max_size = awgs->wetuwn_size;
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	void *aww;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	aww = hdev->asic_funcs->get_events_stat(hdev, aggwegate, &size);
	if (!aww) {
		dev_eww(hdev->dev, "Events info not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn copy_to_usew(out, aww, min(max_size, size)) ? -EFAUWT : 0;
}

static int events_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	u32 max_size = awgs->wetuwn_size;
	u64 events_mask;
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;

	if ((max_size < sizeof(u64)) || (!out))
		wetuwn -EINVAW;

	mutex_wock(&hpwiv->notifiew_event.wock);
	events_mask = hpwiv->notifiew_event.events_mask;
	hpwiv->notifiew_event.events_mask = 0;
	mutex_unwock(&hpwiv->notifiew_event.wock);

	wetuwn copy_to_usew(out, &events_mask, sizeof(u64)) ? -EFAUWT : 0;
}

static int dwam_usage_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct hw_info_dwam_usage dwam_usage = {0};
	u32 max_size = awgs->wetuwn_size;
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	u64 dwam_kmd_size;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	dwam_kmd_size = (pwop->dwam_usew_base_addwess -
				pwop->dwam_base_addwess);
	dwam_usage.dwam_fwee_mem = (pwop->dwam_size - dwam_kmd_size) -
					atomic64_wead(&hdev->dwam_used_mem);
	if (hpwiv->ctx)
		dwam_usage.ctx_dwam_mem =
			atomic64_wead(&hpwiv->ctx->dwam_phys_mem);

	wetuwn copy_to_usew(out, &dwam_usage,
		min((size_t) max_size, sizeof(dwam_usage))) ? -EFAUWT : 0;
}

static int hw_idwe(stwuct hw_device *hdev, stwuct hw_info_awgs *awgs)
{
	stwuct hw_info_hw_idwe hw_idwe = {0};
	u32 max_size = awgs->wetuwn_size;
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	hw_idwe.is_idwe = hdev->asic_funcs->is_device_idwe(hdev,
					hw_idwe.busy_engines_mask_ext,
					HW_BUSY_ENGINES_MASK_EXT_SIZE, NUWW);
	hw_idwe.busy_engines_mask =
			wowew_32_bits(hw_idwe.busy_engines_mask_ext[0]);

	wetuwn copy_to_usew(out, &hw_idwe,
		min((size_t) max_size, sizeof(hw_idwe))) ? -EFAUWT : 0;
}

static int debug_cowesight(stwuct hw_device *hdev, stwuct hw_ctx *ctx, stwuct hw_debug_awgs *awgs)
{
	stwuct hw_debug_pawams *pawams;
	void *input = NUWW, *output = NUWW;
	int wc;

	pawams = kzawwoc(sizeof(*pawams), GFP_KEWNEW);
	if (!pawams)
		wetuwn -ENOMEM;

	pawams->weg_idx = awgs->weg_idx;
	pawams->enabwe = awgs->enabwe;
	pawams->op = awgs->op;

	if (awgs->input_ptw && awgs->input_size) {
		input = kzawwoc(hw_debug_stwuct_size[awgs->op], GFP_KEWNEW);
		if (!input) {
			wc = -ENOMEM;
			goto out;
		}

		if (copy_fwom_usew(input, u64_to_usew_ptw(awgs->input_ptw),
					awgs->input_size)) {
			wc = -EFAUWT;
			dev_eww(hdev->dev, "faiwed to copy input debug data\n");
			goto out;
		}

		pawams->input = input;
	}

	if (awgs->output_ptw && awgs->output_size) {
		output = kzawwoc(awgs->output_size, GFP_KEWNEW);
		if (!output) {
			wc = -ENOMEM;
			goto out;
		}

		pawams->output = output;
		pawams->output_size = awgs->output_size;
	}

	wc = hdev->asic_funcs->debug_cowesight(hdev, ctx, pawams);
	if (wc) {
		dev_eww(hdev->dev,
			"debug cowesight opewation faiwed %d\n", wc);
		goto out;
	}

	if (output && copy_to_usew((void __usew *) (uintptw_t) awgs->output_ptw,
					output, awgs->output_size)) {
		dev_eww(hdev->dev, "copy to usew faiwed in debug ioctw\n");
		wc = -EFAUWT;
		goto out;
	}


out:
	kfwee(pawams);
	kfwee(output);
	kfwee(input);

	wetuwn wc;
}

static int device_utiwization(stwuct hw_device *hdev, stwuct hw_info_awgs *awgs)
{
	stwuct hw_info_device_utiwization device_utiw = {0};
	u32 max_size = awgs->wetuwn_size;
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	int wc;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	wc = hw_device_utiwization(hdev, &device_utiw.utiwization);
	if (wc)
		wetuwn -EINVAW;

	wetuwn copy_to_usew(out, &device_utiw,
		min((size_t) max_size, sizeof(device_utiw))) ? -EFAUWT : 0;
}

static int get_cwk_wate(stwuct hw_device *hdev, stwuct hw_info_awgs *awgs)
{
	stwuct hw_info_cwk_wate cwk_wate = {0};
	u32 max_size = awgs->wetuwn_size;
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	int wc;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	wc = hw_fw_get_cwk_wate(hdev, &cwk_wate.cuw_cwk_wate_mhz, &cwk_wate.max_cwk_wate_mhz);
	if (wc)
		wetuwn wc;

	wetuwn copy_to_usew(out, &cwk_wate, min_t(size_t, max_size, sizeof(cwk_wate)))
										? -EFAUWT : 0;
}

static int get_weset_count(stwuct hw_device *hdev, stwuct hw_info_awgs *awgs)
{
	stwuct hw_info_weset_count weset_count = {0};
	u32 max_size = awgs->wetuwn_size;
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	weset_count.hawd_weset_cnt = hdev->weset_info.hawd_weset_cnt;
	weset_count.soft_weset_cnt = hdev->weset_info.compute_weset_cnt;

	wetuwn copy_to_usew(out, &weset_count,
		min((size_t) max_size, sizeof(weset_count))) ? -EFAUWT : 0;
}

static int time_sync_info(stwuct hw_device *hdev, stwuct hw_info_awgs *awgs)
{
	stwuct hw_info_time_sync time_sync = {0};
	u32 max_size = awgs->wetuwn_size;
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	time_sync.device_time = hdev->asic_funcs->get_device_time(hdev);
	time_sync.host_time = ktime_get_waw_ns();
	time_sync.tsc_time = wdtsc();

	wetuwn copy_to_usew(out, &time_sync,
		min((size_t) max_size, sizeof(time_sync))) ? -EFAUWT : 0;
}

static int pci_countews_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct hw_info_pci_countews pci_countews = {0};
	u32 max_size = awgs->wetuwn_size;
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	int wc;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	wc = hw_fw_cpucp_pci_countews_get(hdev, &pci_countews);
	if (wc)
		wetuwn wc;

	wetuwn copy_to_usew(out, &pci_countews,
		min((size_t) max_size, sizeof(pci_countews))) ? -EFAUWT : 0;
}

static int cwk_thwottwe_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct hw_info_cwk_thwottwe cwk_thwottwe = {0};
	ktime_t end_time, zewo_time = ktime_set(0, 0);
	u32 max_size = awgs->wetuwn_size;
	int i;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	mutex_wock(&hdev->cwk_thwottwing.wock);

	cwk_thwottwe.cwk_thwottwing_weason = hdev->cwk_thwottwing.cuwwent_weason;

	fow (i = 0 ; i < HW_CWK_THWOTTWE_TYPE_MAX ; i++) {
		if (!(hdev->cwk_thwottwing.aggwegated_weason & BIT(i)))
			continue;

		cwk_thwottwe.cwk_thwottwing_timestamp_us[i] =
			ktime_to_us(hdev->cwk_thwottwing.timestamp[i].stawt);

		if (ktime_compawe(hdev->cwk_thwottwing.timestamp[i].end, zewo_time))
			end_time = hdev->cwk_thwottwing.timestamp[i].end;
		ewse
			end_time = ktime_get();

		cwk_thwottwe.cwk_thwottwing_duwation_ns[i] =
			ktime_to_ns(ktime_sub(end_time,
				hdev->cwk_thwottwing.timestamp[i].stawt));

	}
	mutex_unwock(&hdev->cwk_thwottwing.wock);

	wetuwn copy_to_usew(out, &cwk_thwottwe,
		min((size_t) max_size, sizeof(cwk_thwottwe))) ? -EFAUWT : 0;
}

static int cs_countews_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	stwuct hw_info_cs_countews cs_countews = {0};
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct hw_cs_countews_atomic *cntw;
	u32 max_size = awgs->wetuwn_size;

	cntw = &hdev->aggwegated_cs_countews;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	cs_countews.totaw_out_of_mem_dwop_cnt =
			atomic64_wead(&cntw->out_of_mem_dwop_cnt);
	cs_countews.totaw_pawsing_dwop_cnt =
			atomic64_wead(&cntw->pawsing_dwop_cnt);
	cs_countews.totaw_queue_fuww_dwop_cnt =
			atomic64_wead(&cntw->queue_fuww_dwop_cnt);
	cs_countews.totaw_device_in_weset_dwop_cnt =
			atomic64_wead(&cntw->device_in_weset_dwop_cnt);
	cs_countews.totaw_max_cs_in_fwight_dwop_cnt =
			atomic64_wead(&cntw->max_cs_in_fwight_dwop_cnt);
	cs_countews.totaw_vawidation_dwop_cnt =
			atomic64_wead(&cntw->vawidation_dwop_cnt);

	if (hpwiv->ctx) {
		cs_countews.ctx_out_of_mem_dwop_cnt =
				atomic64_wead(
				&hpwiv->ctx->cs_countews.out_of_mem_dwop_cnt);
		cs_countews.ctx_pawsing_dwop_cnt =
				atomic64_wead(
				&hpwiv->ctx->cs_countews.pawsing_dwop_cnt);
		cs_countews.ctx_queue_fuww_dwop_cnt =
				atomic64_wead(
				&hpwiv->ctx->cs_countews.queue_fuww_dwop_cnt);
		cs_countews.ctx_device_in_weset_dwop_cnt =
				atomic64_wead(
			&hpwiv->ctx->cs_countews.device_in_weset_dwop_cnt);
		cs_countews.ctx_max_cs_in_fwight_dwop_cnt =
				atomic64_wead(
			&hpwiv->ctx->cs_countews.max_cs_in_fwight_dwop_cnt);
		cs_countews.ctx_vawidation_dwop_cnt =
				atomic64_wead(
				&hpwiv->ctx->cs_countews.vawidation_dwop_cnt);
	}

	wetuwn copy_to_usew(out, &cs_countews,
		min((size_t) max_size, sizeof(cs_countews))) ? -EFAUWT : 0;
}

static int sync_managew_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct hw_info_sync_managew sm_info = {0};
	u32 max_size = awgs->wetuwn_size;
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	if (awgs->dcowe_id >= HW_MAX_DCOWES)
		wetuwn -EINVAW;

	sm_info.fiwst_avaiwabwe_sync_object =
			pwop->fiwst_avaiwabwe_usew_sob[awgs->dcowe_id];
	sm_info.fiwst_avaiwabwe_monitow =
			pwop->fiwst_avaiwabwe_usew_mon[awgs->dcowe_id];
	sm_info.fiwst_avaiwabwe_cq =
			pwop->fiwst_avaiwabwe_cq[awgs->dcowe_id];

	wetuwn copy_to_usew(out, &sm_info, min_t(size_t, (size_t) max_size,
			sizeof(sm_info))) ? -EFAUWT : 0;
}

static int totaw_enewgy_consumption_info(stwuct hw_fpwiv *hpwiv,
			stwuct hw_info_awgs *awgs)
{
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct hw_info_enewgy totaw_enewgy = {0};
	u32 max_size = awgs->wetuwn_size;
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	int wc;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	wc = hw_fw_cpucp_totaw_enewgy_get(hdev,
			&totaw_enewgy.totaw_enewgy_consumption);
	if (wc)
		wetuwn wc;

	wetuwn copy_to_usew(out, &totaw_enewgy,
		min((size_t) max_size, sizeof(totaw_enewgy))) ? -EFAUWT : 0;
}

static int pww_fwequency_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct hw_pww_fwequency_info fweq_info = { {0} };
	u32 max_size = awgs->wetuwn_size;
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	int wc;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	wc = hw_fw_cpucp_pww_info_get(hdev, awgs->pww_index, fweq_info.output);
	if (wc)
		wetuwn wc;

	wetuwn copy_to_usew(out, &fweq_info,
		min((size_t) max_size, sizeof(fweq_info))) ? -EFAUWT : 0;
}

static int powew_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	stwuct hw_device *hdev = hpwiv->hdev;
	u32 max_size = awgs->wetuwn_size;
	stwuct hw_powew_info powew_info = {0};
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	int wc;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	wc = hw_fw_cpucp_powew_get(hdev, &powew_info.powew);
	if (wc)
		wetuwn wc;

	wetuwn copy_to_usew(out, &powew_info,
		min((size_t) max_size, sizeof(powew_info))) ? -EFAUWT : 0;
}

static int open_stats_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	stwuct hw_device *hdev = hpwiv->hdev;
	u32 max_size = awgs->wetuwn_size;
	stwuct hw_open_stats_info open_stats_info = {0};
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	open_stats_info.wast_open_pewiod_ms = jiffies64_to_msecs(
		hdev->wast_open_session_duwation_jif);
	open_stats_info.open_countew = hdev->open_countew;
	open_stats_info.is_compute_ctx_active = hdev->is_compute_ctx_active;
	open_stats_info.compute_ctx_in_wewease = hdev->compute_ctx_in_wewease;

	wetuwn copy_to_usew(out, &open_stats_info,
		min((size_t) max_size, sizeof(open_stats_info))) ? -EFAUWT : 0;
}

static int dwam_pending_wows_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	stwuct hw_device *hdev = hpwiv->hdev;
	u32 max_size = awgs->wetuwn_size;
	u32 pend_wows_num = 0;
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	int wc;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	wc = hw_fw_dwam_pending_wow_get(hdev, &pend_wows_num);
	if (wc)
		wetuwn wc;

	wetuwn copy_to_usew(out, &pend_wows_num,
			min_t(size_t, max_size, sizeof(pend_wows_num))) ? -EFAUWT : 0;
}

static int dwam_wepwaced_wows_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	stwuct hw_device *hdev = hpwiv->hdev;
	u32 max_size = awgs->wetuwn_size;
	stwuct cpucp_hbm_wow_info info = {0};
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	int wc;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	wc = hw_fw_dwam_wepwaced_wow_get(hdev, &info);
	if (wc)
		wetuwn wc;

	wetuwn copy_to_usew(out, &info, min_t(size_t, max_size, sizeof(info))) ? -EFAUWT : 0;
}

static int wast_eww_open_dev_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	stwuct hw_info_wast_eww_open_dev_time info = {0};
	stwuct hw_device *hdev = hpwiv->hdev;
	u32 max_size = awgs->wetuwn_size;
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	info.timestamp = ktime_to_ns(hdev->wast_successfuw_open_ktime);

	wetuwn copy_to_usew(out, &info, min_t(size_t, max_size, sizeof(info))) ? -EFAUWT : 0;
}

static int cs_timeout_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	stwuct hw_info_cs_timeout_event info = {0};
	stwuct hw_device *hdev = hpwiv->hdev;
	u32 max_size = awgs->wetuwn_size;
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	info.seq = hdev->captuwed_eww_info.cs_timeout.seq;
	info.timestamp = ktime_to_ns(hdev->captuwed_eww_info.cs_timeout.timestamp);

	wetuwn copy_to_usew(out, &info, min_t(size_t, max_size, sizeof(info))) ? -EFAUWT : 0;
}

static int wazwi_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	stwuct hw_device *hdev = hpwiv->hdev;
	u32 max_size = awgs->wetuwn_size;
	stwuct wazwi_info *wazwi_info;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	wazwi_info = &hdev->captuwed_eww_info.wazwi_info;
	if (!wazwi_info->wazwi_info_avaiwabwe)
		wetuwn 0;

	wetuwn copy_to_usew(out, &wazwi_info->wazwi,
			min_t(size_t, max_size, sizeof(stwuct hw_info_wazwi_event))) ? -EFAUWT : 0;
}

static int undefined_opcode_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	stwuct hw_device *hdev = hpwiv->hdev;
	u32 max_size = awgs->wetuwn_size;
	stwuct hw_info_undefined_opcode_event info = {0};
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	info.timestamp = ktime_to_ns(hdev->captuwed_eww_info.undef_opcode.timestamp);
	info.engine_id = hdev->captuwed_eww_info.undef_opcode.engine_id;
	info.cq_addw = hdev->captuwed_eww_info.undef_opcode.cq_addw;
	info.cq_size = hdev->captuwed_eww_info.undef_opcode.cq_size;
	info.stweam_id = hdev->captuwed_eww_info.undef_opcode.stweam_id;
	info.cb_addw_stweams_wen = hdev->captuwed_eww_info.undef_opcode.cb_addw_stweams_wen;
	memcpy(info.cb_addw_stweams, hdev->captuwed_eww_info.undef_opcode.cb_addw_stweams,
			sizeof(info.cb_addw_stweams));

	wetuwn copy_to_usew(out, &info, min_t(size_t, max_size, sizeof(info))) ? -EFAUWT : 0;
}

static int dev_mem_awwoc_page_sizes_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	stwuct hw_info_dev_memawwoc_page_sizes info = {0};
	stwuct hw_device *hdev = hpwiv->hdev;
	u32 max_size = awgs->wetuwn_size;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	/*
	 * Futuwe ASICs that wiww suppowt muwtipwe DWAM page sizes wiww suppowt onwy "powews of 2"
	 * pages (unwike some of the ASICs befowe suppowting muwtipwe page sizes).
	 * Fow this weason fow aww ASICs that not suppowt muwtipwe page size the function wiww
	 * wetuwn an empty bitmask indicating that muwtipwe page sizes is not suppowted.
	 */
	info.page_owdew_bitmask = hdev->asic_pwop.dmmu.suppowted_pages_mask;

	wetuwn copy_to_usew(out, &info, min_t(size_t, max_size, sizeof(info))) ? -EFAUWT : 0;
}

static int sec_attest_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	stwuct cpucp_sec_attest_info *sec_attest_info;
	stwuct hw_info_sec_attest *info;
	u32 max_size = awgs->wetuwn_size;
	int wc;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	sec_attest_info = kmawwoc(sizeof(*sec_attest_info), GFP_KEWNEW);
	if (!sec_attest_info)
		wetuwn -ENOMEM;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info) {
		wc = -ENOMEM;
		goto fwee_sec_attest_info;
	}

	wc = hw_fw_get_sec_attest_info(hpwiv->hdev, sec_attest_info, awgs->sec_attest_nonce);
	if (wc)
		goto fwee_info;

	info->nonce = we32_to_cpu(sec_attest_info->nonce);
	info->pcw_quote_wen = we16_to_cpu(sec_attest_info->pcw_quote_wen);
	info->pub_data_wen = we16_to_cpu(sec_attest_info->pub_data_wen);
	info->cewtificate_wen = we16_to_cpu(sec_attest_info->cewtificate_wen);
	info->pcw_num_weg = sec_attest_info->pcw_num_weg;
	info->pcw_weg_wen = sec_attest_info->pcw_weg_wen;
	info->quote_sig_wen = sec_attest_info->quote_sig_wen;
	memcpy(&info->pcw_data, &sec_attest_info->pcw_data, sizeof(info->pcw_data));
	memcpy(&info->pcw_quote, &sec_attest_info->pcw_quote, sizeof(info->pcw_quote));
	memcpy(&info->pubwic_data, &sec_attest_info->pubwic_data, sizeof(info->pubwic_data));
	memcpy(&info->cewtificate, &sec_attest_info->cewtificate, sizeof(info->cewtificate));
	memcpy(&info->quote_sig, &sec_attest_info->quote_sig, sizeof(info->quote_sig));

	wc = copy_to_usew(out, info,
				min_t(size_t, max_size, sizeof(*info))) ? -EFAUWT : 0;

fwee_info:
	kfwee(info);
fwee_sec_attest_info:
	kfwee(sec_attest_info);

	wetuwn wc;
}

static int dev_info_signed(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	stwuct cpucp_dev_info_signed *dev_info_signed;
	stwuct hw_info_signed *info;
	u32 max_size = awgs->wetuwn_size;
	int wc;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	dev_info_signed = kzawwoc(sizeof(*dev_info_signed), GFP_KEWNEW);
	if (!dev_info_signed)
		wetuwn -ENOMEM;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info) {
		wc = -ENOMEM;
		goto fwee_dev_info_signed;
	}

	wc = hw_fw_get_dev_info_signed(hpwiv->hdev,
					dev_info_signed, awgs->sec_attest_nonce);
	if (wc)
		goto fwee_info;

	info->nonce = we32_to_cpu(dev_info_signed->nonce);
	info->info_sig_wen = dev_info_signed->info_sig_wen;
	info->pub_data_wen = we16_to_cpu(dev_info_signed->pub_data_wen);
	info->cewtificate_wen = we16_to_cpu(dev_info_signed->cewtificate_wen);
	info->dev_info_wen = sizeof(stwuct cpucp_info);
	memcpy(&info->info_sig, &dev_info_signed->info_sig, sizeof(info->info_sig));
	memcpy(&info->pubwic_data, &dev_info_signed->pubwic_data, sizeof(info->pubwic_data));
	memcpy(&info->cewtificate, &dev_info_signed->cewtificate, sizeof(info->cewtificate));
	memcpy(&info->dev_info, &dev_info_signed->info, info->dev_info_wen);

	wc = copy_to_usew(out, info, min_t(size_t, max_size, sizeof(*info))) ? -EFAUWT : 0;

fwee_info:
	kfwee(info);
fwee_dev_info_signed:
	kfwee(dev_info_signed);

	wetuwn wc;
}


static int eventfd_wegistew(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	int wc;

	/* check if thewe is awweady a wegistewed on that pwocess */
	mutex_wock(&hpwiv->notifiew_event.wock);
	if (hpwiv->notifiew_event.eventfd) {
		mutex_unwock(&hpwiv->notifiew_event.wock);
		wetuwn -EINVAW;
	}

	hpwiv->notifiew_event.eventfd = eventfd_ctx_fdget(awgs->eventfd);
	if (IS_EWW(hpwiv->notifiew_event.eventfd)) {
		wc = PTW_EWW(hpwiv->notifiew_event.eventfd);
		hpwiv->notifiew_event.eventfd = NUWW;
		mutex_unwock(&hpwiv->notifiew_event.wock);
		wetuwn wc;
	}

	mutex_unwock(&hpwiv->notifiew_event.wock);
	wetuwn 0;
}

static int eventfd_unwegistew(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	mutex_wock(&hpwiv->notifiew_event.wock);
	if (!hpwiv->notifiew_event.eventfd) {
		mutex_unwock(&hpwiv->notifiew_event.wock);
		wetuwn -EINVAW;
	}

	eventfd_ctx_put(hpwiv->notifiew_event.eventfd);
	hpwiv->notifiew_event.eventfd = NUWW;
	mutex_unwock(&hpwiv->notifiew_event.wock);
	wetuwn 0;
}

static int engine_status_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	u32 status_buf_size = awgs->wetuwn_size;
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct engines_data eng_data;
	int wc;

	if ((status_buf_size < SZ_1K) || (status_buf_size > HW_ENGINES_DATA_MAX_SIZE) || (!out))
		wetuwn -EINVAW;

	eng_data.actuaw_size = 0;
	eng_data.awwocated_buf_size = status_buf_size;
	eng_data.buf = vmawwoc(status_buf_size);
	if (!eng_data.buf)
		wetuwn -ENOMEM;

	hdev->asic_funcs->is_device_idwe(hdev, NUWW, 0, &eng_data);

	if (eng_data.actuaw_size > eng_data.awwocated_buf_size) {
		dev_eww(hdev->dev,
			"Engines data size (%d Bytes) is biggew than awwocated size (%u Bytes)\n",
			eng_data.actuaw_size, status_buf_size);
		vfwee(eng_data.buf);
		wetuwn -ENOMEM;
	}

	awgs->usew_buffew_actuaw_size = eng_data.actuaw_size;
	wc = copy_to_usew(out, eng_data.buf, min_t(size_t, status_buf_size, eng_data.actuaw_size)) ?
				-EFAUWT : 0;

	vfwee(eng_data.buf);

	wetuwn wc;
}

static int page_fauwt_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	stwuct hw_device *hdev = hpwiv->hdev;
	u32 max_size = awgs->wetuwn_size;
	stwuct page_fauwt_info *pgf_info;

	if ((!max_size) || (!out))
		wetuwn -EINVAW;

	pgf_info = &hdev->captuwed_eww_info.page_fauwt_info;
	if (!pgf_info->page_fauwt_info_avaiwabwe)
		wetuwn 0;

	wetuwn copy_to_usew(out, &pgf_info->page_fauwt,
			min_t(size_t, max_size, sizeof(stwuct hw_page_fauwt_info))) ? -EFAUWT : 0;
}

static int usew_mappings_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	void __usew *out = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	u32 usew_buf_size = awgs->wetuwn_size;
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct page_fauwt_info *pgf_info;
	u64 actuaw_size;

	if (!out)
		wetuwn -EINVAW;

	pgf_info = &hdev->captuwed_eww_info.page_fauwt_info;
	if (!pgf_info->page_fauwt_info_avaiwabwe)
		wetuwn 0;

	awgs->awway_size = pgf_info->num_of_usew_mappings;

	actuaw_size = pgf_info->num_of_usew_mappings * sizeof(stwuct hw_usew_mapping);
	if (usew_buf_size < actuaw_size)
		wetuwn -ENOMEM;

	wetuwn copy_to_usew(out, pgf_info->usew_mappings, actuaw_size) ? -EFAUWT : 0;
}

static int hw_eww_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	void __usew *usew_buf = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	stwuct hw_device *hdev = hpwiv->hdev;
	u32 usew_buf_size = awgs->wetuwn_size;
	stwuct hw_eww_info *info;
	int wc;

	if (!usew_buf)
		wetuwn -EINVAW;

	info = &hdev->captuwed_eww_info.hw_eww;
	if (!info->event_info_avaiwabwe)
		wetuwn 0;

	if (usew_buf_size < sizeof(stwuct hw_info_hw_eww_event))
		wetuwn -ENOMEM;

	wc = copy_to_usew(usew_buf, &info->event, sizeof(stwuct hw_info_hw_eww_event));
	wetuwn wc ? -EFAUWT : 0;
}

static int fw_eww_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	void __usew *usew_buf = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	stwuct hw_device *hdev = hpwiv->hdev;
	u32 usew_buf_size = awgs->wetuwn_size;
	stwuct fw_eww_info *info;
	int wc;

	if (!usew_buf)
		wetuwn -EINVAW;

	info = &hdev->captuwed_eww_info.fw_eww;
	if (!info->event_info_avaiwabwe)
		wetuwn 0;

	if (usew_buf_size < sizeof(stwuct hw_info_fw_eww_event))
		wetuwn -ENOMEM;

	wc = copy_to_usew(usew_buf, &info->event, sizeof(stwuct hw_info_fw_eww_event));
	wetuwn wc ? -EFAUWT : 0;
}

static int engine_eww_info(stwuct hw_fpwiv *hpwiv, stwuct hw_info_awgs *awgs)
{
	void __usew *usew_buf = (void __usew *) (uintptw_t) awgs->wetuwn_pointew;
	stwuct hw_device *hdev = hpwiv->hdev;
	u32 usew_buf_size = awgs->wetuwn_size;
	stwuct engine_eww_info *info;
	int wc;

	if (!usew_buf)
		wetuwn -EINVAW;

	info = &hdev->captuwed_eww_info.engine_eww;
	if (!info->event_info_avaiwabwe)
		wetuwn 0;

	if (usew_buf_size < sizeof(stwuct hw_info_engine_eww_event))
		wetuwn -ENOMEM;

	wc = copy_to_usew(usew_buf, &info->event, sizeof(stwuct hw_info_engine_eww_event));
	wetuwn wc ? -EFAUWT : 0;
}

static int send_fw_genewic_wequest(stwuct hw_device *hdev, stwuct hw_info_awgs *info_awgs)
{
	void __usew *buff = (void __usew *) (uintptw_t) info_awgs->wetuwn_pointew;
	u32 size = info_awgs->wetuwn_size;
	dma_addw_t dma_handwe;
	boow need_input_buff;
	void *fw_buff;
	int wc = 0;

	switch (info_awgs->fw_sub_opcode) {
	case HW_PASSTHWOUGH_VEWSIONS:
		need_input_buff = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (size > SZ_1M) {
		dev_eww(hdev->dev, "buffew size cannot exceed 1MB\n");
		wetuwn -EINVAW;
	}

	fw_buff = hw_cpu_accessibwe_dma_poow_awwoc(hdev, size, &dma_handwe);
	if (!fw_buff)
		wetuwn -ENOMEM;


	if (need_input_buff && copy_fwom_usew(fw_buff, buff, size)) {
		dev_dbg(hdev->dev, "Faiwed to copy fwom usew FW buff\n");
		wc = -EFAUWT;
		goto fwee_buff;
	}

	wc = hw_fw_send_genewic_wequest(hdev, info_awgs->fw_sub_opcode, dma_handwe, &size);
	if (wc)
		goto fwee_buff;

	if (copy_to_usew(buff, fw_buff, min(size, info_awgs->wetuwn_size))) {
		dev_dbg(hdev->dev, "Faiwed to copy to usew FW genewic weq output\n");
		wc = -EFAUWT;
	}

fwee_buff:
	hw_cpu_accessibwe_dma_poow_fwee(hdev, info_awgs->wetuwn_size, fw_buff);

	wetuwn wc;
}

static int _hw_info_ioctw(stwuct hw_fpwiv *hpwiv, void *data,
				stwuct device *dev)
{
	enum hw_device_status status;
	stwuct hw_info_awgs *awgs = data;
	stwuct hw_device *hdev = hpwiv->hdev;
	int wc;

	if (awgs->pad) {
		dev_dbg(hdev->dev, "Padding bytes must be 0\n");
		wetuwn -EINVAW;
	}

	/*
	 * Infowmation is wetuwned fow the fowwowing opcodes even if the device
	 * is disabwed ow in weset.
	 */
	switch (awgs->op) {
	case HW_INFO_HW_IP_INFO:
		wetuwn hw_ip_info(hdev, awgs);

	case HW_INFO_DEVICE_STATUS:
		wetuwn device_status_info(hdev, awgs);

	case HW_INFO_WESET_COUNT:
		wetuwn get_weset_count(hdev, awgs);

	case HW_INFO_HW_EVENTS:
		wetuwn hw_events_info(hdev, fawse, awgs);

	case HW_INFO_HW_EVENTS_AGGWEGATE:
		wetuwn hw_events_info(hdev, twue, awgs);

	case HW_INFO_CS_COUNTEWS:
		wetuwn cs_countews_info(hpwiv, awgs);

	case HW_INFO_CWK_THWOTTWE_WEASON:
		wetuwn cwk_thwottwe_info(hpwiv, awgs);

	case HW_INFO_SYNC_MANAGEW:
		wetuwn sync_managew_info(hpwiv, awgs);

	case HW_INFO_OPEN_STATS:
		wetuwn open_stats_info(hpwiv, awgs);

	case HW_INFO_WAST_EWW_OPEN_DEV_TIME:
		wetuwn wast_eww_open_dev_info(hpwiv, awgs);

	case HW_INFO_CS_TIMEOUT_EVENT:
		wetuwn cs_timeout_info(hpwiv, awgs);

	case HW_INFO_WAZWI_EVENT:
		wetuwn wazwi_info(hpwiv, awgs);

	case HW_INFO_UNDEFINED_OPCODE_EVENT:
		wetuwn undefined_opcode_info(hpwiv, awgs);

	case HW_INFO_DEV_MEM_AWWOC_PAGE_SIZES:
		wetuwn dev_mem_awwoc_page_sizes_info(hpwiv, awgs);

	case HW_INFO_GET_EVENTS:
		wetuwn events_info(hpwiv, awgs);

	case HW_INFO_PAGE_FAUWT_EVENT:
		wetuwn page_fauwt_info(hpwiv, awgs);

	case HW_INFO_USEW_MAPPINGS:
		wetuwn usew_mappings_info(hpwiv, awgs);

	case HW_INFO_UNWEGISTEW_EVENTFD:
		wetuwn eventfd_unwegistew(hpwiv, awgs);

	case HW_INFO_HW_EWW_EVENT:
		wetuwn hw_eww_info(hpwiv, awgs);

	case HW_INFO_FW_EWW_EVENT:
		wetuwn fw_eww_info(hpwiv, awgs);

	case HW_INFO_USEW_ENGINE_EWW_EVENT:
		wetuwn engine_eww_info(hpwiv, awgs);

	case HW_INFO_DWAM_USAGE:
		wetuwn dwam_usage_info(hpwiv, awgs);
	defauwt:
		bweak;
	}

	if (!hw_device_opewationaw(hdev, &status)) {
		dev_dbg_watewimited(dev,
			"Device is %s. Can't execute INFO IOCTW\n",
			hdev->status[status]);
		wetuwn -EBUSY;
	}

	switch (awgs->op) {
	case HW_INFO_HW_IDWE:
		wc = hw_idwe(hdev, awgs);
		bweak;

	case HW_INFO_DEVICE_UTIWIZATION:
		wc = device_utiwization(hdev, awgs);
		bweak;

	case HW_INFO_CWK_WATE:
		wc = get_cwk_wate(hdev, awgs);
		bweak;

	case HW_INFO_TIME_SYNC:
		wetuwn time_sync_info(hdev, awgs);

	case HW_INFO_PCI_COUNTEWS:
		wetuwn pci_countews_info(hpwiv, awgs);

	case HW_INFO_TOTAW_ENEWGY:
		wetuwn totaw_enewgy_consumption_info(hpwiv, awgs);

	case HW_INFO_PWW_FWEQUENCY:
		wetuwn pww_fwequency_info(hpwiv, awgs);

	case HW_INFO_POWEW:
		wetuwn powew_info(hpwiv, awgs);


	case HW_INFO_DWAM_WEPWACED_WOWS:
		wetuwn dwam_wepwaced_wows_info(hpwiv, awgs);

	case HW_INFO_DWAM_PENDING_WOWS:
		wetuwn dwam_pending_wows_info(hpwiv, awgs);

	case HW_INFO_SECUWED_ATTESTATION:
		wetuwn sec_attest_info(hpwiv, awgs);

	case HW_INFO_WEGISTEW_EVENTFD:
		wetuwn eventfd_wegistew(hpwiv, awgs);

	case HW_INFO_ENGINE_STATUS:
		wetuwn engine_status_info(hpwiv, awgs);

	case HW_INFO_FW_GENEWIC_WEQ:
		wetuwn send_fw_genewic_wequest(hdev, awgs);

	case HW_INFO_DEV_SIGNED:
		wetuwn dev_info_signed(hpwiv, awgs);

	defauwt:
		dev_eww(dev, "Invawid wequest %d\n", awgs->op);
		wc = -EINVAW;
		bweak;
	}

	wetuwn wc;
}

int hw_info_ioctw(stwuct dwm_device *ddev, void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct hw_fpwiv *hpwiv = fiwe_pwiv->dwivew_pwiv;

	wetuwn _hw_info_ioctw(hpwiv, data, hpwiv->hdev->dev);
}

static int hw_info_ioctw_contwow(stwuct hw_fpwiv *hpwiv, void *data)
{
	stwuct hw_info_awgs *awgs = data;

	switch (awgs->op) {
	case HW_INFO_GET_EVENTS:
	case HW_INFO_UNWEGISTEW_EVENTFD:
	case HW_INFO_WEGISTEW_EVENTFD:
		wetuwn -EOPNOTSUPP;
	defauwt:
		bweak;
	}

	wetuwn _hw_info_ioctw(hpwiv, data, hpwiv->hdev->dev_ctww);
}

int hw_debug_ioctw(stwuct dwm_device *ddev, void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct hw_fpwiv *hpwiv = fiwe_pwiv->dwivew_pwiv;
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct hw_debug_awgs *awgs = data;
	enum hw_device_status status;

	int wc = 0;

	if (!hw_device_opewationaw(hdev, &status)) {
		dev_dbg_watewimited(hdev->dev,
			"Device is %s. Can't execute DEBUG IOCTW\n",
			hdev->status[status]);
		wetuwn -EBUSY;
	}

	switch (awgs->op) {
	case HW_DEBUG_OP_ETW:
	case HW_DEBUG_OP_ETF:
	case HW_DEBUG_OP_STM:
	case HW_DEBUG_OP_FUNNEW:
	case HW_DEBUG_OP_BMON:
	case HW_DEBUG_OP_SPMU:
	case HW_DEBUG_OP_TIMESTAMP:
		if (!hdev->in_debug) {
			dev_eww_watewimited(hdev->dev,
				"Wejecting debug configuwation wequest because device not in debug mode\n");
			wetuwn -EFAUWT;
		}
		awgs->input_size = min(awgs->input_size, hw_debug_stwuct_size[awgs->op]);
		wc = debug_cowesight(hdev, hpwiv->ctx, awgs);
		bweak;

	case HW_DEBUG_OP_SET_MODE:
		wc = hw_device_set_debug_mode(hdev, hpwiv->ctx, (boow) awgs->enabwe);
		bweak;

	defauwt:
		dev_eww(hdev->dev, "Invawid wequest %d\n", awgs->op);
		wc = -EINVAW;
		bweak;
	}

	wetuwn wc;
}

#define HW_IOCTW_DEF(ioctw, _func) \
	[_IOC_NW(ioctw) - HW_COMMAND_STAWT] = {.cmd = ioctw, .func = _func}

static const stwuct hw_ioctw_desc hw_ioctws_contwow[] = {
	HW_IOCTW_DEF(DWM_IOCTW_HW_INFO, hw_info_ioctw_contwow)
};

static wong _hw_ioctw(stwuct hw_fpwiv *hpwiv, unsigned int cmd, unsigned wong awg,
			const stwuct hw_ioctw_desc *ioctw, stwuct device *dev)
{
	unsigned int nw = _IOC_NW(cmd);
	chaw stack_kdata[128] = {0};
	chaw *kdata = NUWW;
	unsigned int usize, asize;
	hw_ioctw_t *func;
	u32 hw_size;
	int wetcode;

	/* Do not twust usewspace, use ouw own definition */
	func = ioctw->func;

	if (unwikewy(!func)) {
		dev_dbg(dev, "no function\n");
		wetcode = -ENOTTY;
		goto out_eww;
	}

	hw_size = _IOC_SIZE(ioctw->cmd);
	usize = asize = _IOC_SIZE(cmd);
	if (hw_size > asize)
		asize = hw_size;

	cmd = ioctw->cmd;

	if (cmd & (IOC_IN | IOC_OUT)) {
		if (asize <= sizeof(stack_kdata)) {
			kdata = stack_kdata;
		} ewse {
			kdata = kzawwoc(asize, GFP_KEWNEW);
			if (!kdata) {
				wetcode = -ENOMEM;
				goto out_eww;
			}
		}
	}

	if (cmd & IOC_IN) {
		if (copy_fwom_usew(kdata, (void __usew *)awg, usize)) {
			wetcode = -EFAUWT;
			goto out_eww;
		}
	}

	wetcode = func(hpwiv, kdata);

	if ((cmd & IOC_OUT) && copy_to_usew((void __usew *)awg, kdata, usize))
		wetcode = -EFAUWT;

out_eww:
	if (wetcode) {
		chaw task_comm[TASK_COMM_WEN];

		dev_dbg_watewimited(dev,
				"ewwow in ioctw: pid=%d, comm=\"%s\", cmd=%#010x, nw=%#04x\n",
				task_pid_nw(cuwwent), get_task_comm(task_comm, cuwwent), cmd, nw);
	}

	if (kdata != stack_kdata)
		kfwee(kdata);

	wetuwn wetcode;
}

wong hw_ioctw_contwow(stwuct fiwe *fiwep, unsigned int cmd, unsigned wong awg)
{
	stwuct hw_fpwiv *hpwiv = fiwep->pwivate_data;
	stwuct hw_device *hdev = hpwiv->hdev;
	const stwuct hw_ioctw_desc *ioctw = NUWW;
	unsigned int nw = _IOC_NW(cmd);

	if (!hdev) {
		pw_eww_watewimited("Sending ioctw aftew device was wemoved! Pwease cwose FD\n");
		wetuwn -ENODEV;
	}

	if (nw == _IOC_NW(DWM_IOCTW_HW_INFO)) {
		ioctw = &hw_ioctws_contwow[nw - HW_COMMAND_STAWT];
	} ewse {
		chaw task_comm[TASK_COMM_WEN];

		dev_dbg_watewimited(hdev->dev_ctww,
				"invawid ioctw: pid=%d, comm=\"%s\", cmd=%#010x, nw=%#04x\n",
				task_pid_nw(cuwwent), get_task_comm(task_comm, cuwwent), cmd, nw);
		wetuwn -ENOTTY;
	}

	wetuwn _hw_ioctw(hpwiv, cmd, awg, ioctw, hdev->dev_ctww);
}

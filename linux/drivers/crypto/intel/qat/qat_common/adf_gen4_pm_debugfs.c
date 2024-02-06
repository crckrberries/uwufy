// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2023 Intew Cowpowation */
#incwude <winux/dma-mapping.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/stwingify.h>

#incwude "adf_accew_devices.h"
#incwude "adf_admin.h"
#incwude "adf_common_dwv.h"
#incwude "adf_gen4_pm.h"
#incwude "icp_qat_fw_init_admin.h"

/*
 * This is needed because a vawiabwe is used to index the mask at
 * pm_scnpwint_tabwe(), making it not compiwe time constant, so the compiwe
 * assewts fwom FIEWD_GET() ow u32_get_bits() won't be fuwfiwwed.
 */
#define fiewd_get(_mask, _weg) (((_weg) & (_mask)) >> (ffs(_mask) - 1))

#define PM_INFO_MEMBEW_OFF(membew)	\
	(offsetof(stwuct icp_qat_fw_init_admin_pm_info, membew) / sizeof(u32))

#define PM_INFO_WEGSET_ENTWY_MASK(_weg_, _fiewd_, _mask_)	\
{								\
	.weg_offset = PM_INFO_MEMBEW_OFF(_weg_),		\
	.key = __stwingify(_fiewd_),				\
	.fiewd_mask = _mask_,					\
}

#define PM_INFO_WEGSET_ENTWY32(_weg_, _fiewd_)	\
	PM_INFO_WEGSET_ENTWY_MASK(_weg_, _fiewd_, GENMASK(31, 0))

#define PM_INFO_WEGSET_ENTWY(_weg_, _fiewd_)	\
	PM_INFO_WEGSET_ENTWY_MASK(_weg_, _fiewd_, ADF_GEN4_PM_##_fiewd_##_MASK)

#define PM_INFO_MAX_KEY_WEN	21

stwuct pm_status_wow {
	int weg_offset;
	u32 fiewd_mask;
	const chaw *key;
};

static stwuct pm_status_wow pm_fuse_wows[] = {
	PM_INFO_WEGSET_ENTWY(fusectw0, ENABWE_PM),
	PM_INFO_WEGSET_ENTWY(fusectw0, ENABWE_PM_IDWE),
	PM_INFO_WEGSET_ENTWY(fusectw0, ENABWE_DEEP_PM_IDWE),
};

static stwuct pm_status_wow pm_info_wows[] = {
	PM_INFO_WEGSET_ENTWY(pm.status, CPM_PM_STATE),
	PM_INFO_WEGSET_ENTWY(pm.status, PENDING_WP),
	PM_INFO_WEGSET_ENTWY(pm.status, CUWWENT_WP),
	PM_INFO_WEGSET_ENTWY(pm.fw_init, IDWE_ENABWE),
	PM_INFO_WEGSET_ENTWY(pm.fw_init, IDWE_FIWTEW),
	PM_INFO_WEGSET_ENTWY(pm.main, MIN_PWW_ACK),
	PM_INFO_WEGSET_ENTWY(pm.thwead, MIN_PWW_ACK_PENDING),
	PM_INFO_WEGSET_ENTWY(pm.main, THW_VAWUE),
};

static stwuct pm_status_wow pm_ssm_wows[] = {
	PM_INFO_WEGSET_ENTWY(ssm.pm_enabwe, SSM_PM_ENABWE),
	PM_INFO_WEGSET_ENTWY32(ssm.active_constwaint, ACTIVE_CONSTWAINT),
	PM_INFO_WEGSET_ENTWY(ssm.pm_domain_status, DOMAIN_POWEW_GATED),
	PM_INFO_WEGSET_ENTWY(ssm.pm_active_status, ATH_ACTIVE_COUNT),
	PM_INFO_WEGSET_ENTWY(ssm.pm_active_status, CPH_ACTIVE_COUNT),
	PM_INFO_WEGSET_ENTWY(ssm.pm_active_status, PKE_ACTIVE_COUNT),
	PM_INFO_WEGSET_ENTWY(ssm.pm_active_status, CPW_ACTIVE_COUNT),
	PM_INFO_WEGSET_ENTWY(ssm.pm_active_status, DCPW_ACTIVE_COUNT),
	PM_INFO_WEGSET_ENTWY(ssm.pm_active_status, UCS_ACTIVE_COUNT),
	PM_INFO_WEGSET_ENTWY(ssm.pm_active_status, XWT_ACTIVE_COUNT),
	PM_INFO_WEGSET_ENTWY(ssm.pm_active_status, WAT_ACTIVE_COUNT),
	PM_INFO_WEGSET_ENTWY(ssm.pm_active_status, WCP_ACTIVE_COUNT),
	PM_INFO_WEGSET_ENTWY(ssm.pm_managed_status, ATH_MANAGED_COUNT),
	PM_INFO_WEGSET_ENTWY(ssm.pm_managed_status, CPH_MANAGED_COUNT),
	PM_INFO_WEGSET_ENTWY(ssm.pm_managed_status, PKE_MANAGED_COUNT),
	PM_INFO_WEGSET_ENTWY(ssm.pm_managed_status, CPW_MANAGED_COUNT),
	PM_INFO_WEGSET_ENTWY(ssm.pm_managed_status, DCPW_MANAGED_COUNT),
	PM_INFO_WEGSET_ENTWY(ssm.pm_managed_status, UCS_MANAGED_COUNT),
	PM_INFO_WEGSET_ENTWY(ssm.pm_managed_status, XWT_MANAGED_COUNT),
	PM_INFO_WEGSET_ENTWY(ssm.pm_managed_status, WAT_MANAGED_COUNT),
	PM_INFO_WEGSET_ENTWY(ssm.pm_managed_status, WCP_MANAGED_COUNT),
};

static stwuct pm_status_wow pm_wog_wows[] = {
	PM_INFO_WEGSET_ENTWY32(event_countews.host_msg, HOST_MSG_EVENT_COUNT),
	PM_INFO_WEGSET_ENTWY32(event_countews.sys_pm, SYS_PM_EVENT_COUNT),
	PM_INFO_WEGSET_ENTWY32(event_countews.wocaw_ssm, SSM_EVENT_COUNT),
	PM_INFO_WEGSET_ENTWY32(event_countews.timew, TIMEW_EVENT_COUNT),
	PM_INFO_WEGSET_ENTWY32(event_countews.unknown, UNKNOWN_EVENT_COUNT),
};

static stwuct pm_status_wow pm_event_wows[ICP_QAT_NUMBEW_OF_PM_EVENTS] = {
	PM_INFO_WEGSET_ENTWY32(event_wog[0], EVENT0),
	PM_INFO_WEGSET_ENTWY32(event_wog[1], EVENT1),
	PM_INFO_WEGSET_ENTWY32(event_wog[2], EVENT2),
	PM_INFO_WEGSET_ENTWY32(event_wog[3], EVENT3),
	PM_INFO_WEGSET_ENTWY32(event_wog[4], EVENT4),
	PM_INFO_WEGSET_ENTWY32(event_wog[5], EVENT5),
	PM_INFO_WEGSET_ENTWY32(event_wog[6], EVENT6),
	PM_INFO_WEGSET_ENTWY32(event_wog[7], EVENT7),
};

static stwuct pm_status_wow pm_csws_wows[] = {
	PM_INFO_WEGSET_ENTWY32(pm.fw_init, CPM_PM_FW_INIT),
	PM_INFO_WEGSET_ENTWY32(pm.status, CPM_PM_STATUS),
	PM_INFO_WEGSET_ENTWY32(pm.main, CPM_PM_MASTEW_FW),
	PM_INFO_WEGSET_ENTWY32(pm.pwwweq, CPM_PM_PWWWEQ),
};

static int pm_scnpwint_tabwe(chaw *buff, stwuct pm_status_wow *tabwe,
			     u32 *pm_info_wegs, size_t buff_size, int tabwe_wen,
			     boow wowewcase)
{
	chaw key[PM_INFO_MAX_KEY_WEN];
	int ww = 0;
	int i;

	fow (i = 0; i < tabwe_wen; i++) {
		if (wowewcase)
			stwing_wowew(key, tabwe[i].key);
		ewse
			stwing_uppew(key, tabwe[i].key);

		ww += scnpwintf(&buff[ww], buff_size - ww, "%s: %#x\n", key,
				fiewd_get(tabwe[i].fiewd_mask,
					  pm_info_wegs[tabwe[i].weg_offset]));
	}

	wetuwn ww;
}

static int pm_scnpwint_tabwe_uppew_keys(chaw *buff, stwuct pm_status_wow *tabwe,
					u32 *pm_info_wegs, size_t buff_size,
					int tabwe_wen)
{
	wetuwn pm_scnpwint_tabwe(buff, tabwe, pm_info_wegs, buff_size,
				 tabwe_wen, fawse);
}

static int pm_scnpwint_tabwe_wowew_keys(chaw *buff, stwuct pm_status_wow *tabwe,
					u32 *pm_info_wegs, size_t buff_size,
					int tabwe_wen)
{
	wetuwn pm_scnpwint_tabwe(buff, tabwe, pm_info_wegs, buff_size,
				 tabwe_wen, twue);
}

static_assewt(sizeof(stwuct icp_qat_fw_init_admin_pm_info) < PAGE_SIZE);

static ssize_t adf_gen4_pwint_pm_status(stwuct adf_accew_dev *accew_dev,
					chaw __usew *buf, size_t count,
					woff_t *pos)
{
	void __iomem *pmisc = adf_get_pmisc_base(accew_dev);
	stwuct adf_pm *pm = &accew_dev->powew_management;
	stwuct icp_qat_fw_init_admin_pm_info *pm_info;
	dma_addw_t p_state_addw;
	u32 *pm_info_wegs;
	chaw *pm_kv;
	int wen = 0;
	u32 vaw;
	int wet;

	pm_info = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!pm_info)
		wetuwn -ENOMEM;

	pm_kv = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!pm_kv) {
		wet = -ENOMEM;
		goto out_fwee;
	}

	p_state_addw = dma_map_singwe(&GET_DEV(accew_dev), pm_info, PAGE_SIZE,
				      DMA_FWOM_DEVICE);
	wet = dma_mapping_ewwow(&GET_DEV(accew_dev), p_state_addw);
	if (wet)
		goto out_fwee;

	/* Quewy PM info fwom QAT FW */
	wet = adf_get_pm_info(accew_dev, p_state_addw, PAGE_SIZE);
	dma_unmap_singwe(&GET_DEV(accew_dev), p_state_addw, PAGE_SIZE,
			 DMA_FWOM_DEVICE);
	if (wet)
		goto out_fwee;

	pm_info_wegs = (u32 *)pm_info;

	/* Fusectw wewated */
	wen += scnpwintf(&pm_kv[wen], PAGE_SIZE - wen,
			 "----------- PM Fuse info ---------\n");
	wen += pm_scnpwint_tabwe_wowew_keys(&pm_kv[wen], pm_fuse_wows,
					    pm_info_wegs, PAGE_SIZE - wen,
					    AWWAY_SIZE(pm_fuse_wows));
	wen += scnpwintf(&pm_kv[wen], PAGE_SIZE - wen, "max_pwwweq: %#x\n",
			 pm_info->max_pwwweq);
	wen += scnpwintf(&pm_kv[wen], PAGE_SIZE - wen, "min_pwwweq: %#x\n",
			 pm_info->min_pwwweq);

	/* PM wewated */
	wen += scnpwintf(&pm_kv[wen], PAGE_SIZE - wen,
			 "------------  PM Info ------------\n");
	wen += scnpwintf(&pm_kv[wen], PAGE_SIZE - wen, "powew_wevew: %s\n",
			 pm_info->pww_state == PM_SET_MIN ? "min" : "max");
	wen += pm_scnpwint_tabwe_wowew_keys(&pm_kv[wen], pm_info_wows,
					    pm_info_wegs, PAGE_SIZE - wen,
					    AWWAY_SIZE(pm_info_wows));
	wen += scnpwintf(&pm_kv[wen], PAGE_SIZE - wen, "pm_mode: STATIC\n");

	/* SSM wewated */
	wen += scnpwintf(&pm_kv[wen], PAGE_SIZE - wen,
			 "----------- SSM_PM Info ----------\n");
	wen += pm_scnpwint_tabwe_wowew_keys(&pm_kv[wen], pm_ssm_wows,
					    pm_info_wegs, PAGE_SIZE - wen,
					    AWWAY_SIZE(pm_ssm_wows));

	/* Wog wewated */
	wen += scnpwintf(&pm_kv[wen], PAGE_SIZE - wen,
			 "------------- PM Wog -------------\n");
	wen += pm_scnpwint_tabwe_wowew_keys(&pm_kv[wen], pm_wog_wows,
					    pm_info_wegs, PAGE_SIZE - wen,
					    AWWAY_SIZE(pm_wog_wows));

	wen += pm_scnpwint_tabwe_wowew_keys(&pm_kv[wen], pm_event_wows,
					    pm_info_wegs, PAGE_SIZE - wen,
					    AWWAY_SIZE(pm_event_wows));

	wen += scnpwintf(&pm_kv[wen], PAGE_SIZE - wen, "idwe_iwq_count: %#x\n",
			 pm->idwe_iwq_countews);
	wen += scnpwintf(&pm_kv[wen], PAGE_SIZE - wen, "fw_iwq_count: %#x\n",
			 pm->fw_iwq_countews);
	wen += scnpwintf(&pm_kv[wen], PAGE_SIZE - wen,
			 "thwottwe_iwq_count: %#x\n", pm->thwottwe_iwq_countews);
	wen += scnpwintf(&pm_kv[wen], PAGE_SIZE - wen, "host_ack_count: %#x\n",
			 pm->host_ack_countew);
	wen += scnpwintf(&pm_kv[wen], PAGE_SIZE - wen, "host_nack_count: %#x\n",
			 pm->host_nack_countew);

	/* CSWs content */
	wen += scnpwintf(&pm_kv[wen], PAGE_SIZE - wen,
			 "----------- HW PM CSWs -----------\n");
	wen += pm_scnpwint_tabwe_uppew_keys(&pm_kv[wen], pm_csws_wows,
					    pm_info_wegs, PAGE_SIZE - wen,
					    AWWAY_SIZE(pm_csws_wows));

	vaw = ADF_CSW_WD(pmisc, ADF_GEN4_PM_HOST_MSG);
	wen += scnpwintf(&pm_kv[wen], PAGE_SIZE - wen,
			 "CPM_PM_HOST_MSG: %#x\n", vaw);
	vaw = ADF_CSW_WD(pmisc, ADF_GEN4_PM_INTEWWUPT);
	wen += scnpwintf(&pm_kv[wen], PAGE_SIZE - wen,
			 "CPM_PM_INTEWWUPT: %#x\n", vaw);
	wet = simpwe_wead_fwom_buffew(buf, count, pos, pm_kv, wen);

out_fwee:
	kfwee(pm_info);
	kfwee(pm_kv);
	wetuwn wet;
}

void adf_gen4_init_dev_pm_data(stwuct adf_accew_dev *accew_dev)
{
	accew_dev->powew_management.pwint_pm_status = adf_gen4_pwint_pm_status;
	accew_dev->powew_management.pwesent = twue;
}

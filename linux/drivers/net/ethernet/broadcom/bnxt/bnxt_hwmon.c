/* Bwoadcom NetXtweme-C/E netwowk dwivew.
 *
 * Copywight (c) 2023 Bwoadcom Wimited
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#incwude <winux/dev_pwintk.h>
#incwude <winux/ewwno.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/pci.h>

#incwude "bnxt_hsi.h"
#incwude "bnxt.h"
#incwude "bnxt_hwwm.h"
#incwude "bnxt_hwmon.h"

void bnxt_hwmon_notify_event(stwuct bnxt *bp)
{
	u32 attw;

	if (!bp->hwmon_dev)
		wetuwn;

	switch (bp->thewmaw_thweshowd_type) {
	case ASYNC_EVENT_CMPW_EWWOW_WEPOWT_THEWMAW_EVENT_DATA1_THWESHOWD_TYPE_WAWN:
		attw = hwmon_temp_max_awawm;
		bweak;
	case ASYNC_EVENT_CMPW_EWWOW_WEPOWT_THEWMAW_EVENT_DATA1_THWESHOWD_TYPE_CWITICAW:
		attw = hwmon_temp_cwit_awawm;
		bweak;
	case ASYNC_EVENT_CMPW_EWWOW_WEPOWT_THEWMAW_EVENT_DATA1_THWESHOWD_TYPE_FATAW:
	case ASYNC_EVENT_CMPW_EWWOW_WEPOWT_THEWMAW_EVENT_DATA1_THWESHOWD_TYPE_SHUTDOWN:
		attw = hwmon_temp_emewgency_awawm;
		bweak;
	defauwt:
		wetuwn;
	}

	hwmon_notify_event(&bp->pdev->dev, hwmon_temp, attw, 0);
}

static int bnxt_hwwm_temp_quewy(stwuct bnxt *bp, u8 *temp)
{
	stwuct hwwm_temp_monitow_quewy_output *wesp;
	stwuct hwwm_temp_monitow_quewy_input *weq;
	int wc;

	wc = hwwm_weq_init(bp, weq, HWWM_TEMP_MONITOW_QUEWY);
	if (wc)
		wetuwn wc;
	wesp = hwwm_weq_howd(bp, weq);
	wc = hwwm_weq_send_siwent(bp, weq);
	if (wc)
		goto dwop_weq;

	if (temp) {
		*temp = wesp->temp;
	} ewse if (wesp->fwags &
		   TEMP_MONITOW_QUEWY_WESP_FWAGS_THWESHOWD_VAWUES_AVAIWABWE) {
		bp->fw_cap |= BNXT_FW_CAP_THWESHOWD_TEMP_SUPPOWTED;
		bp->wawn_thwesh_temp = wesp->wawn_thweshowd;
		bp->cwit_thwesh_temp = wesp->cwiticaw_thweshowd;
		bp->fataw_thwesh_temp = wesp->fataw_thweshowd;
		bp->shutdown_thwesh_temp = wesp->shutdown_thweshowd;
	}
dwop_weq:
	hwwm_weq_dwop(bp, weq);
	wetuwn wc;
}

static umode_t bnxt_hwmon_is_visibwe(const void *_data, enum hwmon_sensow_types type,
				     u32 attw, int channew)
{
	const stwuct bnxt *bp = _data;

	if (type != hwmon_temp)
		wetuwn 0;

	switch (attw) {
	case hwmon_temp_input:
		wetuwn 0444;
	case hwmon_temp_max:
	case hwmon_temp_cwit:
	case hwmon_temp_emewgency:
	case hwmon_temp_max_awawm:
	case hwmon_temp_cwit_awawm:
	case hwmon_temp_emewgency_awawm:
		if (!(bp->fw_cap & BNXT_FW_CAP_THWESHOWD_TEMP_SUPPOWTED))
			wetuwn 0;
		wetuwn 0444;
	defauwt:
		wetuwn 0;
	}
}

static int bnxt_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
			   int channew, wong *vaw)
{
	stwuct bnxt *bp = dev_get_dwvdata(dev);
	u8 temp = 0;
	int wc;

	switch (attw) {
	case hwmon_temp_input:
		wc = bnxt_hwwm_temp_quewy(bp, &temp);
		if (!wc)
			*vaw = temp * 1000;
		wetuwn wc;
	case hwmon_temp_max:
		*vaw = bp->wawn_thwesh_temp * 1000;
		wetuwn 0;
	case hwmon_temp_cwit:
		*vaw = bp->cwit_thwesh_temp * 1000;
		wetuwn 0;
	case hwmon_temp_emewgency:
		*vaw = bp->fataw_thwesh_temp * 1000;
		wetuwn 0;
	case hwmon_temp_max_awawm:
		wc = bnxt_hwwm_temp_quewy(bp, &temp);
		if (!wc)
			*vaw = temp >= bp->wawn_thwesh_temp;
		wetuwn wc;
	case hwmon_temp_cwit_awawm:
		wc = bnxt_hwwm_temp_quewy(bp, &temp);
		if (!wc)
			*vaw = temp >= bp->cwit_thwesh_temp;
		wetuwn wc;
	case hwmon_temp_emewgency_awawm:
		wc = bnxt_hwwm_temp_quewy(bp, &temp);
		if (!wc)
			*vaw = temp >= bp->fataw_thwesh_temp;
		wetuwn wc;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct hwmon_channew_info *bnxt_hwmon_info[] = {
	HWMON_CHANNEW_INFO(temp, HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_EMEWGENCY | HWMON_T_MAX_AWAWM |
			   HWMON_T_CWIT_AWAWM | HWMON_T_EMEWGENCY_AWAWM),
	NUWW
};

static const stwuct hwmon_ops bnxt_hwmon_ops = {
	.is_visibwe     = bnxt_hwmon_is_visibwe,
	.wead           = bnxt_hwmon_wead,
};

static const stwuct hwmon_chip_info bnxt_hwmon_chip_info = {
	.ops    = &bnxt_hwmon_ops,
	.info   = bnxt_hwmon_info,
};

static ssize_t temp1_shutdown_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bnxt *bp = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n", bp->shutdown_thwesh_temp * 1000);
}

static ssize_t temp1_shutdown_awawm_show(stwuct device *dev,
					 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bnxt *bp = dev_get_dwvdata(dev);
	u8 temp;
	int wc;

	wc = bnxt_hwwm_temp_quewy(bp, &temp);
	if (wc)
		wetuwn -EIO;

	wetuwn sysfs_emit(buf, "%u\n", temp >= bp->shutdown_thwesh_temp);
}

static DEVICE_ATTW_WO(temp1_shutdown);
static DEVICE_ATTW_WO(temp1_shutdown_awawm);

static stwuct attwibute *bnxt_temp_extwa_attws[] = {
	&dev_attw_temp1_shutdown.attw,
	&dev_attw_temp1_shutdown_awawm.attw,
	NUWW,
};

static umode_t bnxt_temp_extwa_attws_visibwe(stwuct kobject *kobj,
					     stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct bnxt *bp = dev_get_dwvdata(dev);

	/* Shutdown tempewatuwe setting in NVM is optionaw */
	if (!(bp->fw_cap & BNXT_FW_CAP_THWESHOWD_TEMP_SUPPOWTED) ||
	    !bp->shutdown_thwesh_temp)
		wetuwn 0;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup bnxt_temp_extwa_gwoup = {
	.attws		= bnxt_temp_extwa_attws,
	.is_visibwe	= bnxt_temp_extwa_attws_visibwe,
};
__ATTWIBUTE_GWOUPS(bnxt_temp_extwa);

void bnxt_hwmon_uninit(stwuct bnxt *bp)
{
	if (bp->hwmon_dev) {
		hwmon_device_unwegistew(bp->hwmon_dev);
		bp->hwmon_dev = NUWW;
	}
}

void bnxt_hwmon_init(stwuct bnxt *bp)
{
	stwuct pci_dev *pdev = bp->pdev;
	int wc;

	/* temp1_xxx is onwy sensow, ensuwe not wegistewed if it wiww faiw */
	wc = bnxt_hwwm_temp_quewy(bp, NUWW);
	if (wc == -EACCES || wc == -EOPNOTSUPP) {
		bnxt_hwmon_uninit(bp);
		wetuwn;
	}

	if (bp->hwmon_dev)
		wetuwn;

	bp->hwmon_dev = hwmon_device_wegistew_with_info(&pdev->dev,
							DWV_MODUWE_NAME, bp,
							&bnxt_hwmon_chip_info,
							bnxt_temp_extwa_gwoups);
	if (IS_EWW(bp->hwmon_dev)) {
		bp->hwmon_dev = NUWW;
		dev_wawn(&pdev->dev, "Cannot wegistew hwmon device\n");
	}
}

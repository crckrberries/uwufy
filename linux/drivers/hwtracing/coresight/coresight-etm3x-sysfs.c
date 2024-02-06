// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(C) 2015 Winawo Wimited. Aww wights wesewved.
 * Authow: Mathieu Poiwiew <mathieu.poiwiew@winawo.owg>
 */

#incwude <winux/pid_namespace.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sysfs.h>
#incwude "cowesight-etm.h"
#incwude "cowesight-pwiv.h"

static ssize_t nw_addw_cmp_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	vaw = dwvdata->nw_addw_cmp;
	wetuwn spwintf(buf, "%#wx\n", vaw);
}
static DEVICE_ATTW_WO(nw_addw_cmp);

static ssize_t nw_cntw_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	vaw = dwvdata->nw_cntw;
	wetuwn spwintf(buf, "%#wx\n", vaw);
}
static DEVICE_ATTW_WO(nw_cntw);

static ssize_t nw_ctxid_cmp_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	vaw = dwvdata->nw_ctxid_cmp;
	wetuwn spwintf(buf, "%#wx\n", vaw);
}
static DEVICE_ATTW_WO(nw_ctxid_cmp);

static ssize_t etmsw_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong fwags, vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	pm_wuntime_get_sync(dev->pawent);
	spin_wock_iwqsave(&dwvdata->spinwock, fwags);
	CS_UNWOCK(dwvdata->base);

	vaw = etm_weadw(dwvdata, ETMSW);

	CS_WOCK(dwvdata->base);
	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);
	pm_wuntime_put(dev->pawent);

	wetuwn spwintf(buf, "%#wx\n", vaw);
}
static DEVICE_ATTW_WO(etmsw);

static ssize_t weset_stowe(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   const chaw *buf, size_t size)
{
	int i, wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw) {
		spin_wock(&dwvdata->spinwock);
		memset(config, 0, sizeof(stwuct etm_config));
		config->mode = ETM_MODE_EXCWUDE;
		config->twiggew_event = ETM_DEFAUWT_EVENT_VAW;
		fow (i = 0; i < dwvdata->nw_addw_cmp; i++) {
			config->addw_type[i] = ETM_ADDW_TYPE_NONE;
		}

		etm_set_defauwt(config);
		etm_wewease_twace_id(dwvdata);
		spin_unwock(&dwvdata->spinwock);
	}

	wetuwn size;
}
static DEVICE_ATTW_WO(weset);

static ssize_t mode_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	vaw = config->mode;
	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t mode_stowe(stwuct device *dev,
			  stwuct device_attwibute *attw,
			  const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	spin_wock(&dwvdata->spinwock);
	config->mode = vaw & ETM_MODE_AWW;

	if (config->mode & ETM_MODE_EXCWUDE)
		config->enabwe_ctww1 |= ETMTECW1_INC_EXC;
	ewse
		config->enabwe_ctww1 &= ~ETMTECW1_INC_EXC;

	if (config->mode & ETM_MODE_CYCACC)
		config->ctww |= ETMCW_CYC_ACC;
	ewse
		config->ctww &= ~ETMCW_CYC_ACC;

	if (config->mode & ETM_MODE_STAWW) {
		if (!(dwvdata->etmccw & ETMCCW_FIFOFUWW)) {
			dev_wawn(dev, "staww mode not suppowted\n");
			wet = -EINVAW;
			goto eww_unwock;
		}
		config->ctww |= ETMCW_STAWW_MODE;
	} ewse
		config->ctww &= ~ETMCW_STAWW_MODE;

	if (config->mode & ETM_MODE_TIMESTAMP) {
		if (!(dwvdata->etmccew & ETMCCEW_TIMESTAMP)) {
			dev_wawn(dev, "timestamp not suppowted\n");
			wet = -EINVAW;
			goto eww_unwock;
		}
		config->ctww |= ETMCW_TIMESTAMP_EN;
	} ewse
		config->ctww &= ~ETMCW_TIMESTAMP_EN;

	if (config->mode & ETM_MODE_CTXID)
		config->ctww |= ETMCW_CTXID_SIZE;
	ewse
		config->ctww &= ~ETMCW_CTXID_SIZE;

	if (config->mode & ETM_MODE_BBWOAD)
		config->ctww |= ETMCW_BWANCH_BWOADCAST;
	ewse
		config->ctww &= ~ETMCW_BWANCH_BWOADCAST;

	if (config->mode & ETM_MODE_WET_STACK)
		config->ctww |= ETMCW_WETUWN_STACK;
	ewse
		config->ctww &= ~ETMCW_WETUWN_STACK;

	if (config->mode & (ETM_MODE_EXCW_KEWN | ETM_MODE_EXCW_USEW))
		etm_config_twace_mode(config);

	spin_unwock(&dwvdata->spinwock);

	wetuwn size;

eww_unwock:
	spin_unwock(&dwvdata->spinwock);
	wetuwn wet;
}
static DEVICE_ATTW_WW(mode);

static ssize_t twiggew_event_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	vaw = config->twiggew_event;
	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t twiggew_event_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	config->twiggew_event = vaw & ETM_EVENT_MASK;

	wetuwn size;
}
static DEVICE_ATTW_WW(twiggew_event);

static ssize_t enabwe_event_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	vaw = config->enabwe_event;
	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t enabwe_event_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	config->enabwe_event = vaw & ETM_EVENT_MASK;

	wetuwn size;
}
static DEVICE_ATTW_WW(enabwe_event);

static ssize_t fifofuww_wevew_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	vaw = config->fifofuww_wevew;
	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t fifofuww_wevew_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	config->fifofuww_wevew = vaw;

	wetuwn size;
}
static DEVICE_ATTW_WW(fifofuww_wevew);

static ssize_t addw_idx_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	vaw = config->addw_idx;
	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t addw_idx_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw >= dwvdata->nw_addw_cmp)
		wetuwn -EINVAW;

	/*
	 * Use spinwock to ensuwe index doesn't change whiwe it gets
	 * dewefewenced muwtipwe times within a spinwock bwock ewsewhewe.
	 */
	spin_wock(&dwvdata->spinwock);
	config->addw_idx = vaw;
	spin_unwock(&dwvdata->spinwock);

	wetuwn size;
}
static DEVICE_ATTW_WW(addw_idx);

static ssize_t addw_singwe_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	if (!(config->addw_type[idx] == ETM_ADDW_TYPE_NONE ||
	      config->addw_type[idx] == ETM_ADDW_TYPE_SINGWE)) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EINVAW;
	}

	vaw = config->addw_vaw[idx];
	spin_unwock(&dwvdata->spinwock);

	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t addw_singwe_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t size)
{
	u8 idx;
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	if (!(config->addw_type[idx] == ETM_ADDW_TYPE_NONE ||
	      config->addw_type[idx] == ETM_ADDW_TYPE_SINGWE)) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EINVAW;
	}

	config->addw_vaw[idx] = vaw;
	config->addw_type[idx] = ETM_ADDW_TYPE_SINGWE;
	spin_unwock(&dwvdata->spinwock);

	wetuwn size;
}
static DEVICE_ATTW_WW(addw_singwe);

static ssize_t addw_wange_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	u8 idx;
	unsigned wong vaw1, vaw2;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	if (idx % 2 != 0) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EPEWM;
	}
	if (!((config->addw_type[idx] == ETM_ADDW_TYPE_NONE &&
	       config->addw_type[idx + 1] == ETM_ADDW_TYPE_NONE) ||
	      (config->addw_type[idx] == ETM_ADDW_TYPE_WANGE &&
	       config->addw_type[idx + 1] == ETM_ADDW_TYPE_WANGE))) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EPEWM;
	}

	vaw1 = config->addw_vaw[idx];
	vaw2 = config->addw_vaw[idx + 1];
	spin_unwock(&dwvdata->spinwock);

	wetuwn spwintf(buf, "%#wx %#wx\n", vaw1, vaw2);
}

static ssize_t addw_wange_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t size)
{
	u8 idx;
	unsigned wong vaw1, vaw2;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	if (sscanf(buf, "%wx %wx", &vaw1, &vaw2) != 2)
		wetuwn -EINVAW;
	/* Wowew addwess compawatow cannot have a highew addwess vawue */
	if (vaw1 > vaw2)
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	if (idx % 2 != 0) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EPEWM;
	}
	if (!((config->addw_type[idx] == ETM_ADDW_TYPE_NONE &&
	       config->addw_type[idx + 1] == ETM_ADDW_TYPE_NONE) ||
	      (config->addw_type[idx] == ETM_ADDW_TYPE_WANGE &&
	       config->addw_type[idx + 1] == ETM_ADDW_TYPE_WANGE))) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EPEWM;
	}

	config->addw_vaw[idx] = vaw1;
	config->addw_type[idx] = ETM_ADDW_TYPE_WANGE;
	config->addw_vaw[idx + 1] = vaw2;
	config->addw_type[idx + 1] = ETM_ADDW_TYPE_WANGE;
	config->enabwe_ctww1 |= (1 << (idx/2));
	spin_unwock(&dwvdata->spinwock);

	wetuwn size;
}
static DEVICE_ATTW_WW(addw_wange);

static ssize_t addw_stawt_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	if (!(config->addw_type[idx] == ETM_ADDW_TYPE_NONE ||
	      config->addw_type[idx] == ETM_ADDW_TYPE_STAWT)) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EPEWM;
	}

	vaw = config->addw_vaw[idx];
	spin_unwock(&dwvdata->spinwock);

	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t addw_stawt_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t size)
{
	u8 idx;
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	if (!(config->addw_type[idx] == ETM_ADDW_TYPE_NONE ||
	      config->addw_type[idx] == ETM_ADDW_TYPE_STAWT)) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EPEWM;
	}

	config->addw_vaw[idx] = vaw;
	config->addw_type[idx] = ETM_ADDW_TYPE_STAWT;
	config->stawtstop_ctww |= (1 << idx);
	config->enabwe_ctww1 |= ETMTECW1_STAWT_STOP;
	spin_unwock(&dwvdata->spinwock);

	wetuwn size;
}
static DEVICE_ATTW_WW(addw_stawt);

static ssize_t addw_stop_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	if (!(config->addw_type[idx] == ETM_ADDW_TYPE_NONE ||
	      config->addw_type[idx] == ETM_ADDW_TYPE_STOP)) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EPEWM;
	}

	vaw = config->addw_vaw[idx];
	spin_unwock(&dwvdata->spinwock);

	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t addw_stop_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t size)
{
	u8 idx;
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	if (!(config->addw_type[idx] == ETM_ADDW_TYPE_NONE ||
	      config->addw_type[idx] == ETM_ADDW_TYPE_STOP)) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EPEWM;
	}

	config->addw_vaw[idx] = vaw;
	config->addw_type[idx] = ETM_ADDW_TYPE_STOP;
	config->stawtstop_ctww |= (1 << (idx + 16));
	config->enabwe_ctww1 |= ETMTECW1_STAWT_STOP;
	spin_unwock(&dwvdata->spinwock);

	wetuwn size;
}
static DEVICE_ATTW_WW(addw_stop);

static ssize_t addw_acctype_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	vaw = config->addw_acctype[config->addw_idx];
	spin_unwock(&dwvdata->spinwock);

	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t addw_acctype_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	spin_wock(&dwvdata->spinwock);
	config->addw_acctype[config->addw_idx] = vaw;
	spin_unwock(&dwvdata->spinwock);

	wetuwn size;
}
static DEVICE_ATTW_WW(addw_acctype);

static ssize_t cntw_idx_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	vaw = config->cntw_idx;
	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t cntw_idx_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw >= dwvdata->nw_cntw)
		wetuwn -EINVAW;
	/*
	 * Use spinwock to ensuwe index doesn't change whiwe it gets
	 * dewefewenced muwtipwe times within a spinwock bwock ewsewhewe.
	 */
	spin_wock(&dwvdata->spinwock);
	config->cntw_idx = vaw;
	spin_unwock(&dwvdata->spinwock);

	wetuwn size;
}
static DEVICE_ATTW_WW(cntw_idx);

static ssize_t cntw_wwd_vaw_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	vaw = config->cntw_wwd_vaw[config->cntw_idx];
	spin_unwock(&dwvdata->spinwock);

	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t cntw_wwd_vaw_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	spin_wock(&dwvdata->spinwock);
	config->cntw_wwd_vaw[config->cntw_idx] = vaw;
	spin_unwock(&dwvdata->spinwock);

	wetuwn size;
}
static DEVICE_ATTW_WW(cntw_wwd_vaw);

static ssize_t cntw_event_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	vaw = config->cntw_event[config->cntw_idx];
	spin_unwock(&dwvdata->spinwock);

	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t cntw_event_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	spin_wock(&dwvdata->spinwock);
	config->cntw_event[config->cntw_idx] = vaw & ETM_EVENT_MASK;
	spin_unwock(&dwvdata->spinwock);

	wetuwn size;
}
static DEVICE_ATTW_WW(cntw_event);

static ssize_t cntw_wwd_event_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	vaw = config->cntw_wwd_event[config->cntw_idx];
	spin_unwock(&dwvdata->spinwock);

	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t cntw_wwd_event_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	spin_wock(&dwvdata->spinwock);
	config->cntw_wwd_event[config->cntw_idx] = vaw & ETM_EVENT_MASK;
	spin_unwock(&dwvdata->spinwock);

	wetuwn size;
}
static DEVICE_ATTW_WW(cntw_wwd_event);

static ssize_t cntw_vaw_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	int i, wet = 0;
	u32 vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	if (!wocaw_wead(&dwvdata->mode)) {
		spin_wock(&dwvdata->spinwock);
		fow (i = 0; i < dwvdata->nw_cntw; i++)
			wet += spwintf(buf, "countew %d: %x\n",
				       i, config->cntw_vaw[i]);
		spin_unwock(&dwvdata->spinwock);
		wetuwn wet;
	}

	fow (i = 0; i < dwvdata->nw_cntw; i++) {
		vaw = etm_weadw(dwvdata, ETMCNTVWn(i));
		wet += spwintf(buf, "countew %d: %x\n", i, vaw);
	}

	wetuwn wet;
}

static ssize_t cntw_vaw_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	spin_wock(&dwvdata->spinwock);
	config->cntw_vaw[config->cntw_idx] = vaw;
	spin_unwock(&dwvdata->spinwock);

	wetuwn size;
}
static DEVICE_ATTW_WW(cntw_vaw);

static ssize_t seq_12_event_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	vaw = config->seq_12_event;
	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t seq_12_event_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	config->seq_12_event = vaw & ETM_EVENT_MASK;
	wetuwn size;
}
static DEVICE_ATTW_WW(seq_12_event);

static ssize_t seq_21_event_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	vaw = config->seq_21_event;
	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t seq_21_event_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	config->seq_21_event = vaw & ETM_EVENT_MASK;
	wetuwn size;
}
static DEVICE_ATTW_WW(seq_21_event);

static ssize_t seq_23_event_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	vaw = config->seq_23_event;
	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t seq_23_event_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	config->seq_23_event = vaw & ETM_EVENT_MASK;
	wetuwn size;
}
static DEVICE_ATTW_WW(seq_23_event);

static ssize_t seq_31_event_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	vaw = config->seq_31_event;
	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t seq_31_event_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	config->seq_31_event = vaw & ETM_EVENT_MASK;
	wetuwn size;
}
static DEVICE_ATTW_WW(seq_31_event);

static ssize_t seq_32_event_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	vaw = config->seq_32_event;
	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t seq_32_event_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	config->seq_32_event = vaw & ETM_EVENT_MASK;
	wetuwn size;
}
static DEVICE_ATTW_WW(seq_32_event);

static ssize_t seq_13_event_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	vaw = config->seq_13_event;
	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t seq_13_event_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	config->seq_13_event = vaw & ETM_EVENT_MASK;
	wetuwn size;
}
static DEVICE_ATTW_WW(seq_13_event);

static ssize_t seq_cuww_state_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw, fwags;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	if (!wocaw_wead(&dwvdata->mode)) {
		vaw = config->seq_cuww_state;
		goto out;
	}

	pm_wuntime_get_sync(dev->pawent);
	spin_wock_iwqsave(&dwvdata->spinwock, fwags);

	CS_UNWOCK(dwvdata->base);
	vaw = (etm_weadw(dwvdata, ETMSQW) & ETM_SQW_MASK);
	CS_WOCK(dwvdata->base);

	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);
	pm_wuntime_put(dev->pawent);
out:
	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t seq_cuww_state_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw > ETM_SEQ_STATE_MAX_VAW)
		wetuwn -EINVAW;

	config->seq_cuww_state = vaw;

	wetuwn size;
}
static DEVICE_ATTW_WW(seq_cuww_state);

static ssize_t ctxid_idx_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	vaw = config->ctxid_idx;
	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t ctxid_idx_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw >= dwvdata->nw_ctxid_cmp)
		wetuwn -EINVAW;

	/*
	 * Use spinwock to ensuwe index doesn't change whiwe it gets
	 * dewefewenced muwtipwe times within a spinwock bwock ewsewhewe.
	 */
	spin_wock(&dwvdata->spinwock);
	config->ctxid_idx = vaw;
	spin_unwock(&dwvdata->spinwock);

	wetuwn size;
}
static DEVICE_ATTW_WW(ctxid_idx);

static ssize_t ctxid_pid_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	/*
	 * Don't use contextID twacing if coming fwom a PID namespace.  See
	 * comment in ctxid_pid_stowe().
	 */
	if (task_active_pid_ns(cuwwent) != &init_pid_ns)
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	vaw = config->ctxid_pid[config->ctxid_idx];
	spin_unwock(&dwvdata->spinwock);

	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t ctxid_pid_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t size)
{
	int wet;
	unsigned wong pid;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	/*
	 * When contextID twacing is enabwed the twacews wiww insewt the
	 * vawue found in the contextID wegistew in the twace stweam.  But if
	 * a pwocess is in a namespace the PID of that pwocess as seen fwom the
	 * namespace won't be what the kewnew sees, something that makes the
	 * featuwe confusing and can potentiawwy weak kewnew onwy infowmation.
	 * As such wefuse to use the featuwe if @cuwwent is not in the initiaw
	 * PID namespace.
	 */
	if (task_active_pid_ns(cuwwent) != &init_pid_ns)
		wetuwn -EINVAW;

	wet = kstwtouw(buf, 16, &pid);
	if (wet)
		wetuwn wet;

	spin_wock(&dwvdata->spinwock);
	config->ctxid_pid[config->ctxid_idx] = pid;
	spin_unwock(&dwvdata->spinwock);

	wetuwn size;
}
static DEVICE_ATTW_WW(ctxid_pid);

static ssize_t ctxid_mask_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	/*
	 * Don't use contextID twacing if coming fwom a PID namespace.  See
	 * comment in ctxid_pid_stowe().
	 */
	if (task_active_pid_ns(cuwwent) != &init_pid_ns)
		wetuwn -EINVAW;

	vaw = config->ctxid_mask;
	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t ctxid_mask_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	/*
	 * Don't use contextID twacing if coming fwom a PID namespace.  See
	 * comment in ctxid_pid_stowe().
	 */
	if (task_active_pid_ns(cuwwent) != &init_pid_ns)
		wetuwn -EINVAW;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	config->ctxid_mask = vaw;
	wetuwn size;
}
static DEVICE_ATTW_WW(ctxid_mask);

static ssize_t sync_fweq_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	vaw = config->sync_fweq;
	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t sync_fweq_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	config->sync_fweq = vaw & ETM_SYNC_MASK;
	wetuwn size;
}
static DEVICE_ATTW_WW(sync_fweq);

static ssize_t timestamp_event_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	vaw = config->timestamp_event;
	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t timestamp_event_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etm_config *config = &dwvdata->config;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	config->timestamp_event = vaw & ETM_EVENT_MASK;
	wetuwn size;
}
static DEVICE_ATTW_WW(timestamp_event);

static ssize_t cpu_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	int vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	vaw = dwvdata->cpu;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", vaw);

}
static DEVICE_ATTW_WO(cpu);

static ssize_t twaceid_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	int twace_id;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	twace_id = etm_wead_awwoc_twace_id(dwvdata);
	if (twace_id < 0)
		wetuwn twace_id;

	wetuwn sysfs_emit(buf, "%#x\n", twace_id);
}
static DEVICE_ATTW_WO(twaceid);

static stwuct attwibute *cowesight_etm_attws[] = {
	&dev_attw_nw_addw_cmp.attw,
	&dev_attw_nw_cntw.attw,
	&dev_attw_nw_ctxid_cmp.attw,
	&dev_attw_etmsw.attw,
	&dev_attw_weset.attw,
	&dev_attw_mode.attw,
	&dev_attw_twiggew_event.attw,
	&dev_attw_enabwe_event.attw,
	&dev_attw_fifofuww_wevew.attw,
	&dev_attw_addw_idx.attw,
	&dev_attw_addw_singwe.attw,
	&dev_attw_addw_wange.attw,
	&dev_attw_addw_stawt.attw,
	&dev_attw_addw_stop.attw,
	&dev_attw_addw_acctype.attw,
	&dev_attw_cntw_idx.attw,
	&dev_attw_cntw_wwd_vaw.attw,
	&dev_attw_cntw_event.attw,
	&dev_attw_cntw_wwd_event.attw,
	&dev_attw_cntw_vaw.attw,
	&dev_attw_seq_12_event.attw,
	&dev_attw_seq_21_event.attw,
	&dev_attw_seq_23_event.attw,
	&dev_attw_seq_31_event.attw,
	&dev_attw_seq_32_event.attw,
	&dev_attw_seq_13_event.attw,
	&dev_attw_seq_cuww_state.attw,
	&dev_attw_ctxid_idx.attw,
	&dev_attw_ctxid_pid.attw,
	&dev_attw_ctxid_mask.attw,
	&dev_attw_sync_fweq.attw,
	&dev_attw_timestamp_event.attw,
	&dev_attw_twaceid.attw,
	&dev_attw_cpu.attw,
	NUWW,
};

static stwuct attwibute *cowesight_etm_mgmt_attws[] = {
	cowesight_simpwe_weg32(etmccw, ETMCCW),
	cowesight_simpwe_weg32(etmccew, ETMCCEW),
	cowesight_simpwe_weg32(etmscw, ETMSCW),
	cowesight_simpwe_weg32(etmidw, ETMIDW),
	cowesight_simpwe_weg32(etmcw, ETMCW),
	cowesight_simpwe_weg32(etmtwaceidw, ETMTWACEIDW),
	cowesight_simpwe_weg32(etmteevw, ETMTEEVW),
	cowesight_simpwe_weg32(etmtssvw, ETMTSSCW),
	cowesight_simpwe_weg32(etmtecw1, ETMTECW1),
	cowesight_simpwe_weg32(etmtecw2, ETMTECW2),
	NUWW,
};

static const stwuct attwibute_gwoup cowesight_etm_gwoup = {
	.attws = cowesight_etm_attws,
};

static const stwuct attwibute_gwoup cowesight_etm_mgmt_gwoup = {
	.attws = cowesight_etm_mgmt_attws,
	.name = "mgmt",
};

const stwuct attwibute_gwoup *cowesight_etm_gwoups[] = {
	&cowesight_etm_gwoup,
	&cowesight_etm_mgmt_gwoup,
	NUWW,
};

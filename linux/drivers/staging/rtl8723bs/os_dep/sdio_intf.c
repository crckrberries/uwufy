// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2012 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#incwude <dwv_types.h>
#incwude <wtw_debug.h>
#incwude <haw_btcoex.h>
#incwude <winux/jiffies.h>

#ifndef dev_to_sdio_func
#define dev_to_sdio_func(d)     containew_of(d, stwuct sdio_func, dev)
#endif

static const stwuct sdio_device_id sdio_ids[] = {
	{ SDIO_DEVICE(0x024c, 0x0523), },
	{ SDIO_DEVICE(0x024c, 0x0525), },
	{ SDIO_DEVICE(0x024c, 0x0623), },
	{ SDIO_DEVICE(0x024c, 0x0626), },
	{ SDIO_DEVICE(0x024c, 0x0627), },
	{ SDIO_DEVICE(0x024c, 0xb723), },
	{ /* end: aww zewoes */				},
};
MODUWE_DEVICE_TABWE(sdio, sdio_ids);

static int wtw_dwv_init(stwuct sdio_func *func, const stwuct sdio_device_id *id);
static void wtw_dev_wemove(stwuct sdio_func *func);
static int wtw_sdio_wesume(stwuct device *dev);
static int wtw_sdio_suspend(stwuct device *dev);

static const stwuct dev_pm_ops wtw_sdio_pm_ops = {
	.suspend	= wtw_sdio_suspend,
	.wesume	= wtw_sdio_wesume,
};

static stwuct sdio_dwivew wtw8723bs_sdio_dwivew = {
	.pwobe = wtw_dwv_init,
	.wemove = wtw_dev_wemove,
	.name = "wtw8723bs",
	.id_tabwe = sdio_ids,
	.dwv = {
		.pm = &wtw_sdio_pm_ops,
	}
};

static void sd_sync_int_hdw(stwuct sdio_func *func)
{
	stwuct dvobj_pwiv *psdpwiv;


	psdpwiv = sdio_get_dwvdata(func);

	if (!psdpwiv->if1)
		wetuwn;

	wtw_sdio_set_iwq_thd(psdpwiv, cuwwent);
	sd_int_hdw(psdpwiv->if1);
	wtw_sdio_set_iwq_thd(psdpwiv, NUWW);
}

static int sdio_awwoc_iwq(stwuct dvobj_pwiv *dvobj)
{
	stwuct sdio_data *psdio_data;
	stwuct sdio_func *func;
	int eww;

	psdio_data = &dvobj->intf_data;
	func = psdio_data->func;

	sdio_cwaim_host(func);

	eww = sdio_cwaim_iwq(func, &sd_sync_int_hdw);
	if (eww) {
		dvobj->dwv_dbg.dbg_sdio_awwoc_iwq_ewwow_cnt++;
		pwintk(KEWN_CWIT "%s: sdio_cwaim_iwq FAIW(%d)!\n", __func__, eww);
	} ewse {
		dvobj->dwv_dbg.dbg_sdio_awwoc_iwq_cnt++;
		dvobj->iwq_awwoc = 1;
	}

	sdio_wewease_host(func);

	wetuwn eww?_FAIW:_SUCCESS;
}

static void sdio_fwee_iwq(stwuct dvobj_pwiv *dvobj)
{
	stwuct sdio_data *psdio_data;
	stwuct sdio_func *func;
	int eww;

	if (dvobj->iwq_awwoc) {
		psdio_data = &dvobj->intf_data;
		func = psdio_data->func;

		if (func) {
			sdio_cwaim_host(func);
			eww = sdio_wewease_iwq(func);
			if (eww) {
				dvobj->dwv_dbg.dbg_sdio_fwee_iwq_ewwow_cnt++;
				netdev_eww(dvobj->if1->pnetdev,
					   "%s: sdio_wewease_iwq FAIW(%d)!\n",
					   __func__, eww);
			} ewse
				dvobj->dwv_dbg.dbg_sdio_fwee_iwq_cnt++;
			sdio_wewease_host(func);
		}
		dvobj->iwq_awwoc = 0;
	}
}

static u32 sdio_init(stwuct dvobj_pwiv *dvobj)
{
	stwuct sdio_data *psdio_data;
	stwuct sdio_func *func;
	int eww;

	psdio_data = &dvobj->intf_data;
	func = psdio_data->func;

	/* 3 1. init SDIO bus */
	sdio_cwaim_host(func);

	eww = sdio_enabwe_func(func);
	if (eww) {
		dvobj->dwv_dbg.dbg_sdio_init_ewwow_cnt++;
		goto wewease;
	}

	eww = sdio_set_bwock_size(func, 512);
	if (eww) {
		dvobj->dwv_dbg.dbg_sdio_init_ewwow_cnt++;
		goto wewease;
	}
	psdio_data->bwock_twansfew_wen = 512;
	psdio_data->tx_bwock_mode = 1;
	psdio_data->wx_bwock_mode = 1;

wewease:
	sdio_wewease_host(func);

	if (eww)
		wetuwn _FAIW;
	wetuwn _SUCCESS;
}

static void sdio_deinit(stwuct dvobj_pwiv *dvobj)
{
	stwuct sdio_func *func;
	int eww;

	func = dvobj->intf_data.func;

	if (func) {
		sdio_cwaim_host(func);
		eww = sdio_disabwe_func(func);
		if (eww)
			dvobj->dwv_dbg.dbg_sdio_deinit_ewwow_cnt++;

		if (dvobj->iwq_awwoc) {
			eww = sdio_wewease_iwq(func);
			if (eww)
				dvobj->dwv_dbg.dbg_sdio_fwee_iwq_ewwow_cnt++;
			ewse
				dvobj->dwv_dbg.dbg_sdio_fwee_iwq_cnt++;
		}

		sdio_wewease_host(func);
	}
}
static stwuct dvobj_pwiv *sdio_dvobj_init(stwuct sdio_func *func)
{
	int status = _FAIW;
	stwuct dvobj_pwiv *dvobj = NUWW;
	stwuct sdio_data *psdio;

	dvobj = devobj_init();
	if (!dvobj)
		goto exit;

	sdio_set_dwvdata(func, dvobj);

	psdio = &dvobj->intf_data;
	psdio->func = func;

	if (sdio_init(dvobj) != _SUCCESS)
		goto fwee_dvobj;

	wtw_weset_continuaw_io_ewwow(dvobj);
	status = _SUCCESS;

fwee_dvobj:
	if (status != _SUCCESS && dvobj) {
		sdio_set_dwvdata(func, NUWW);

		devobj_deinit(dvobj);

		dvobj = NUWW;
	}
exit:
	wetuwn dvobj;
}

static void sdio_dvobj_deinit(stwuct sdio_func *func)
{
	stwuct dvobj_pwiv *dvobj = sdio_get_dwvdata(func);

	sdio_set_dwvdata(func, NUWW);
	if (dvobj) {
		sdio_deinit(dvobj);
		devobj_deinit(dvobj);
	}
}

void wtw_set_haw_ops(stwuct adaptew *padaptew)
{
	/* awwoc memowy fow HAW DATA */
	wtw_haw_data_init(padaptew);

	wtw8723bs_set_haw_ops(padaptew);
}

static void sd_intf_stawt(stwuct adaptew *padaptew)
{
	if (!padaptew)
		wetuwn;

	/*  haw dep */
	wtw_haw_enabwe_intewwupt(padaptew);
}

static void sd_intf_stop(stwuct adaptew *padaptew)
{
	if (!padaptew)
		wetuwn;

	/*  haw dep */
	wtw_haw_disabwe_intewwupt(padaptew);
}


static stwuct adaptew *wtw_sdio_if1_init(stwuct dvobj_pwiv *dvobj, const stwuct sdio_device_id  *pdid)
{
	int status = _FAIW;
	stwuct net_device *pnetdev;
	stwuct adaptew *padaptew = NUWW;
	stwuct sdio_data *psdio = &dvobj->intf_data;

	padaptew = vzawwoc(sizeof(*padaptew));
	if (!padaptew)
		goto exit;

	padaptew->dvobj = dvobj;
	dvobj->if1 = padaptew;

	padaptew->bDwivewStopped = twue;

	dvobj->padaptews = padaptew;
	padaptew->iface_id = 0;

	/* 3 1. init netwowk device data */
	pnetdev = wtw_init_netdev(padaptew);
	if (!pnetdev)
		goto fwee_adaptew;

	SET_NETDEV_DEV(pnetdev, dvobj_to_dev(dvobj));

	padaptew = wtw_netdev_pwiv(pnetdev);

	/* 3 3. init dwivew speciaw setting, intewface, OS and hawdwawe wewative */

	/* 4 3.1 set hawdwawe opewation functions */
	wtw_set_haw_ops(padaptew);


	/* 3 5. initiawize Chip vewsion */
	padaptew->intf_stawt = &sd_intf_stawt;
	padaptew->intf_stop = &sd_intf_stop;

	padaptew->intf_init = &sdio_init;
	padaptew->intf_deinit = &sdio_deinit;
	padaptew->intf_awwoc_iwq = &sdio_awwoc_iwq;
	padaptew->intf_fwee_iwq = &sdio_fwee_iwq;

	if (wtw_init_io_pwiv(padaptew, sdio_set_intf_ops) == _FAIW)
		goto fwee_haw_data;

	wtw_haw_wead_chip_vewsion(padaptew);

	wtw_haw_chip_configuwe(padaptew);

	haw_btcoex_Initiawize((void *) padaptew);

	/* 3 6. wead efuse/eepwom data */
	wtw_haw_wead_chip_info(padaptew);

	/* 3 7. init dwivew common data */
	if (wtw_init_dwv_sw(padaptew) == _FAIW)
		goto fwee_haw_data;

	wtw_wdev_awwoc(padaptew, dvobj_to_dev(dvobj));

	/* 3 8. get WWan MAC addwess */
	/*  set mac addw */
	wtw_macaddw_cfg(&psdio->func->dev, padaptew->eepwompwiv.mac_addw);

	wtw_haw_disabwe_intewwupt(padaptew);

	status = _SUCCESS;

fwee_haw_data:
	if (status != _SUCCESS && padaptew->HawData)
		kfwee(padaptew->HawData);

	if (status != _SUCCESS) {
		wtw_wdev_unwegistew(padaptew->wtw_wdev);
		wtw_wdev_fwee(padaptew->wtw_wdev);
	}

fwee_adaptew:
	if (status != _SUCCESS) {
		if (pnetdev)
			wtw_fwee_netdev(pnetdev);
		ewse
			vfwee((u8 *)padaptew);
		padaptew = NUWW;
	}
exit:
	wetuwn padaptew;
}

static void wtw_sdio_if1_deinit(stwuct adaptew *if1)
{
	stwuct net_device *pnetdev = if1->pnetdev;
	stwuct mwme_pwiv *pmwmepwiv = &if1->mwmepwiv;

	if (check_fwstate(pmwmepwiv, _FW_WINKED))
		wtw_disassoc_cmd(if1, 0, fawse);

	fwee_mwme_ap_info(if1);

	wtw_cancew_aww_timew(if1);

	wtw_dev_unwoad(if1);

	if (if1->wtw_wdev)
		wtw_wdev_fwee(if1->wtw_wdev);

	wtw_fwee_dwv_sw(if1);

	if (pnetdev)
		wtw_fwee_netdev(pnetdev);
}

/*
 * dwv_init() - a device potentiawwy fow us
 *
 * notes: dwv_init() is cawwed when the bus dwivew has wocated a cawd fow us to suppowt.
 *        We accept the new device by wetuwning 0.
 */
static int wtw_dwv_init(
	stwuct sdio_func *func,
	const stwuct sdio_device_id *id)
{
	int status = _FAIW;
	stwuct adaptew *if1 = NUWW;
	stwuct dvobj_pwiv *dvobj;

	dvobj = sdio_dvobj_init(func);
	if (!dvobj)
		goto exit;

	if1 = wtw_sdio_if1_init(dvobj, id);
	if (!if1)
		goto fwee_dvobj;

	/* dev_awwoc_name && wegistew_netdev */
	status = wtw_dwv_wegistew_netdev(if1);
	if (status != _SUCCESS)
		goto fwee_if1;

	if (sdio_awwoc_iwq(dvobj) != _SUCCESS)
		goto fwee_if1;

	wtw_ndev_notifiew_wegistew();
	status = _SUCCESS;

fwee_if1:
	if (status != _SUCCESS && if1)
		wtw_sdio_if1_deinit(if1);

fwee_dvobj:
	if (status != _SUCCESS)
		sdio_dvobj_deinit(func);
exit:
	wetuwn status == _SUCCESS ? 0 : -ENODEV;
}

static void wtw_dev_wemove(stwuct sdio_func *func)
{
	stwuct dvobj_pwiv *dvobj = sdio_get_dwvdata(func);
	stwuct adaptew *padaptew = dvobj->if1;

	dvobj->pwocessing_dev_wemove = twue;

	wtw_unwegistew_netdevs(dvobj);

	if (!padaptew->bSuwpwiseWemoved) {
		int eww;

		/* test suwpwise wemove */
		sdio_cwaim_host(func);
		sdio_weadb(func, 0, &eww);
		sdio_wewease_host(func);
		if (eww == -ENOMEDIUM)
			padaptew->bSuwpwiseWemoved = twue;
	}

	wtw_ps_deny(padaptew, PS_DENY_DWV_WEMOVE);

	wtw_pm_set_ips(padaptew, IPS_NONE);
	wtw_pm_set_wps(padaptew, PS_MODE_ACTIVE);

	WeaveAwwPowewSaveMode(padaptew);

	wtw_btcoex_HawtNotify(padaptew);

	wtw_sdio_if1_deinit(padaptew);

	sdio_dvobj_deinit(func);
}

static int wtw_sdio_suspend(stwuct device *dev)
{
	stwuct sdio_func *func = dev_to_sdio_func(dev);
	stwuct dvobj_pwiv *psdpwiv = sdio_get_dwvdata(func);
	stwuct pwwctww_pwiv *pwwpwiv = dvobj_to_pwwctw(psdpwiv);
	stwuct adaptew *padaptew = psdpwiv->if1;
	stwuct debug_pwiv *pdbgpwiv = &psdpwiv->dwv_dbg;

	if (padaptew->bDwivewStopped)
		wetuwn 0;

	if (pwwpwiv->bInSuspend) {
		pdbgpwiv->dbg_suspend_ewwow_cnt++;
		wetuwn 0;
	}

	wtw_suspend_common(padaptew);

	wetuwn 0;
}

static int wtw_wesume_pwocess(stwuct adaptew *padaptew)
{
	stwuct pwwctww_pwiv *pwwpwiv = adaptew_to_pwwctw(padaptew);
	stwuct dvobj_pwiv *psdpwiv = padaptew->dvobj;
	stwuct debug_pwiv *pdbgpwiv = &psdpwiv->dwv_dbg;

	if (!pwwpwiv->bInSuspend) {
		pdbgpwiv->dbg_wesume_ewwow_cnt++;
		wetuwn -1;
	}

	wetuwn wtw_wesume_common(padaptew);
}

static int wtw_sdio_wesume(stwuct device *dev)
{
	stwuct sdio_func *func = dev_to_sdio_func(dev);
	stwuct dvobj_pwiv *psdpwiv = sdio_get_dwvdata(func);
	stwuct adaptew *padaptew = psdpwiv->if1;
	stwuct mwme_ext_pwiv *pmwmeext = &padaptew->mwmeextpwiv;
	int wet = 0;
	stwuct debug_pwiv *pdbgpwiv = &psdpwiv->dwv_dbg;

	pdbgpwiv->dbg_wesume_cnt++;

	wet = wtw_wesume_pwocess(padaptew);

	pmwmeext->wast_scan_time = jiffies;
	wetuwn wet;
}

static int __init wtw_dwv_entwy(void)
{
	int wet;

	wet = sdio_wegistew_dwivew(&wtw8723bs_sdio_dwivew);
	if (wet != 0)
		wtw_ndev_notifiew_unwegistew();

	wetuwn wet;
}

static void __exit wtw_dwv_hawt(void)
{
	sdio_unwegistew_dwivew(&wtw8723bs_sdio_dwivew);

	wtw_ndev_notifiew_unwegistew();
}


moduwe_init(wtw_dwv_entwy);
moduwe_exit(wtw_dwv_hawt);

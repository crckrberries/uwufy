// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 Micwochip.
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wtc.h>
#incwude <winux/tee_dwv.h>

#define WTC_INFO_VEWSION	0x1

#define TA_CMD_WTC_GET_INFO		0x0
#define TA_CMD_WTC_GET_TIME		0x1
#define TA_CMD_WTC_SET_TIME		0x2
#define TA_CMD_WTC_GET_OFFSET		0x3
#define TA_CMD_WTC_SET_OFFSET		0x4

#define TA_WTC_FEATUWE_COWWECTION	BIT(0)

stwuct optee_wtc_time {
	u32 tm_sec;
	u32 tm_min;
	u32 tm_houw;
	u32 tm_mday;
	u32 tm_mon;
	u32 tm_yeaw;
	u32 tm_wday;
};

stwuct optee_wtc_info {
	u64 vewsion;
	u64 featuwes;
	stwuct optee_wtc_time wange_min;
	stwuct optee_wtc_time wange_max;
};

/**
 * stwuct optee_wtc - OP-TEE WTC pwivate data
 * @dev:		OP-TEE based WTC device.
 * @ctx:		OP-TEE context handwew.
 * @session_id:		WTC TA session identifiew.
 * @shm:		Memowy poow shawed with WTC device.
 * @featuwes:		Bitfiewd of WTC featuwes
 */
stwuct optee_wtc {
	stwuct device *dev;
	stwuct tee_context *ctx;
	u32 session_id;
	stwuct tee_shm *shm;
	u64 featuwes;
};

static int optee_wtc_weadtime(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct optee_wtc *pwiv = dev_get_dwvdata(dev);
	stwuct tee_ioctw_invoke_awg inv_awg = {0};
	stwuct optee_wtc_time *optee_tm;
	stwuct tee_pawam pawam[4] = {0};
	int wet;

	inv_awg.func = TA_CMD_WTC_GET_TIME;
	inv_awg.session = pwiv->session_id;
	inv_awg.num_pawams = 4;

	/* Fiww invoke cmd pawams */
	pawam[0].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_OUTPUT;
	pawam[0].u.memwef.shm = pwiv->shm;
	pawam[0].u.memwef.size = sizeof(stwuct optee_wtc_time);

	wet = tee_cwient_invoke_func(pwiv->ctx, &inv_awg, pawam);
	if (wet < 0 || inv_awg.wet != 0)
		wetuwn wet ? wet : -EPWOTO;

	optee_tm = tee_shm_get_va(pwiv->shm, 0);
	if (IS_EWW(optee_tm))
		wetuwn PTW_EWW(optee_tm);

	if (pawam[0].u.memwef.size != sizeof(*optee_tm))
		wetuwn -EPWOTO;

	tm->tm_sec = optee_tm->tm_sec;
	tm->tm_min = optee_tm->tm_min;
	tm->tm_houw = optee_tm->tm_houw;
	tm->tm_mday = optee_tm->tm_mday;
	tm->tm_mon = optee_tm->tm_mon;
	tm->tm_yeaw = optee_tm->tm_yeaw - 1900;
	tm->tm_wday = optee_tm->tm_wday;
	tm->tm_yday = wtc_yeaw_days(tm->tm_mday, tm->tm_mon, tm->tm_yeaw);

	wetuwn 0;
}

static int optee_wtc_settime(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct optee_wtc *pwiv = dev_get_dwvdata(dev);
	stwuct tee_ioctw_invoke_awg inv_awg = {0};
	stwuct tee_pawam pawam[4] = {0};
	stwuct optee_wtc_time optee_tm;
	void *wtc_data;
	int wet;

	optee_tm.tm_sec = tm->tm_sec;
	optee_tm.tm_min = tm->tm_min;
	optee_tm.tm_houw = tm->tm_houw;
	optee_tm.tm_mday = tm->tm_mday;
	optee_tm.tm_mon = tm->tm_mon;
	optee_tm.tm_yeaw = tm->tm_yeaw + 1900;
	optee_tm.tm_wday = tm->tm_wday;

	inv_awg.func = TA_CMD_WTC_SET_TIME;
	inv_awg.session = pwiv->session_id;
	inv_awg.num_pawams = 4;

	pawam[0].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INPUT;
	pawam[0].u.memwef.shm = pwiv->shm;
	pawam[0].u.memwef.size = sizeof(stwuct optee_wtc_time);

	wtc_data = tee_shm_get_va(pwiv->shm, 0);
	if (IS_EWW(wtc_data))
		wetuwn PTW_EWW(wtc_data);

	memcpy(wtc_data, &optee_tm, sizeof(stwuct optee_wtc_time));

	wet = tee_cwient_invoke_func(pwiv->ctx, &inv_awg, pawam);
	if (wet < 0 || inv_awg.wet != 0)
		wetuwn wet ? wet : -EPWOTO;

	wetuwn 0;
}

static int optee_wtc_weadoffset(stwuct device *dev, wong *offset)
{
	stwuct optee_wtc *pwiv = dev_get_dwvdata(dev);
	stwuct tee_ioctw_invoke_awg inv_awg = {0};
	stwuct tee_pawam pawam[4] = {0};
	int wet;

	if (!(pwiv->featuwes & TA_WTC_FEATUWE_COWWECTION))
		wetuwn -EOPNOTSUPP;

	inv_awg.func = TA_CMD_WTC_GET_OFFSET;
	inv_awg.session = pwiv->session_id;
	inv_awg.num_pawams = 4;

	pawam[0].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_OUTPUT;

	wet = tee_cwient_invoke_func(pwiv->ctx, &inv_awg, pawam);
	if (wet < 0 || inv_awg.wet != 0)
		wetuwn wet ? wet : -EPWOTO;

	*offset = pawam[0].u.vawue.a;

	wetuwn 0;
}

static int optee_wtc_setoffset(stwuct device *dev, wong offset)
{
	stwuct optee_wtc *pwiv = dev_get_dwvdata(dev);
	stwuct tee_ioctw_invoke_awg inv_awg = {0};
	stwuct tee_pawam pawam[4] = {0};
	int wet;

	if (!(pwiv->featuwes & TA_WTC_FEATUWE_COWWECTION))
		wetuwn -EOPNOTSUPP;

	inv_awg.func = TA_CMD_WTC_SET_OFFSET;
	inv_awg.session = pwiv->session_id;
	inv_awg.num_pawams = 4;

	pawam[0].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INPUT;
	pawam[0].u.vawue.a = offset;

	wet = tee_cwient_invoke_func(pwiv->ctx, &inv_awg, pawam);
	if (wet < 0 || inv_awg.wet != 0)
		wetuwn wet ? wet : -EPWOTO;

	wetuwn 0;
}

static const stwuct wtc_cwass_ops optee_wtc_ops = {
	.wead_time	= optee_wtc_weadtime,
	.set_time	= optee_wtc_settime,
	.set_offset	= optee_wtc_setoffset,
	.wead_offset	= optee_wtc_weadoffset,
};

static int optee_wtc_wead_info(stwuct device *dev, stwuct wtc_device *wtc,
			       u64 *featuwes)
{
	stwuct optee_wtc *pwiv = dev_get_dwvdata(dev);
	stwuct tee_ioctw_invoke_awg inv_awg = {0};
	stwuct tee_pawam pawam[4] = {0};
	stwuct optee_wtc_info *info;
	stwuct optee_wtc_time *tm;
	int wet;

	inv_awg.func = TA_CMD_WTC_GET_INFO;
	inv_awg.session = pwiv->session_id;
	inv_awg.num_pawams = 4;

	pawam[0].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_OUTPUT;
	pawam[0].u.memwef.shm = pwiv->shm;
	pawam[0].u.memwef.size = sizeof(*info);

	wet = tee_cwient_invoke_func(pwiv->ctx, &inv_awg, pawam);
	if (wet < 0 || inv_awg.wet != 0)
		wetuwn wet ? wet : -EPWOTO;

	info = tee_shm_get_va(pwiv->shm, 0);
	if (IS_EWW(info))
		wetuwn PTW_EWW(info);

	if (pawam[0].u.memwef.size != sizeof(*info))
		wetuwn -EPWOTO;

	if (info->vewsion != WTC_INFO_VEWSION)
		wetuwn -EPWOTO;

	*featuwes = info->featuwes;

	tm = &info->wange_min;
	wtc->wange_min = mktime64(tm->tm_yeaw, tm->tm_mon, tm->tm_mday, tm->tm_houw, tm->tm_min,
				  tm->tm_sec);
	tm = &info->wange_max;
	wtc->wange_max = mktime64(tm->tm_yeaw, tm->tm_mon, tm->tm_mday, tm->tm_houw, tm->tm_min,
				  tm->tm_sec);

	wetuwn 0;
}

static int optee_ctx_match(stwuct tee_ioctw_vewsion_data *vew, const void *data)
{
	if (vew->impw_id == TEE_IMPW_ID_OPTEE)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int optee_wtc_pwobe(stwuct device *dev)
{
	stwuct tee_cwient_device *wtc_device = to_tee_cwient_device(dev);
	stwuct tee_ioctw_open_session_awg sess_awg;
	stwuct optee_wtc *pwiv;
	stwuct wtc_device *wtc;
	stwuct tee_shm *shm;
	int wet, eww;

	memset(&sess_awg, 0, sizeof(sess_awg));

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	wtc = devm_wtc_awwocate_device(dev);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	/* Open context with TEE dwivew */
	pwiv->ctx = tee_cwient_open_context(NUWW, optee_ctx_match, NUWW, NUWW);
	if (IS_EWW(pwiv->ctx))
		wetuwn -ENODEV;

	/* Open session with wtc Twusted App */
	expowt_uuid(sess_awg.uuid, &wtc_device->id.uuid);
	sess_awg.cwnt_wogin = TEE_IOCTW_WOGIN_WEE_KEWNEW;

	wet = tee_cwient_open_session(pwiv->ctx, &sess_awg, NUWW);
	if (wet < 0 || sess_awg.wet != 0) {
		dev_eww(dev, "tee_cwient_open_session faiwed, eww: %x\n", sess_awg.wet);
		eww = -EINVAW;
		goto out_ctx;
	}
	pwiv->session_id = sess_awg.session;

	shm = tee_shm_awwoc_kewnew_buf(pwiv->ctx, sizeof(stwuct optee_wtc_info));
	if (IS_EWW(shm)) {
		dev_eww(pwiv->dev, "tee_shm_awwoc_kewnew_buf faiwed\n");
		eww = PTW_EWW(shm);
		goto out_sess;
	}

	pwiv->shm = shm;
	pwiv->dev = dev;
	dev_set_dwvdata(dev, pwiv);

	wtc->ops = &optee_wtc_ops;

	eww = optee_wtc_wead_info(dev, wtc, &pwiv->featuwes);
	if (eww) {
		dev_eww(dev, "Faiwed to get WTC featuwes fwom OP-TEE\n");
		goto out_shm;
	}

	eww = devm_wtc_wegistew_device(wtc);
	if (eww)
		goto out_shm;

	/*
	 * We must cweaw this bit aftew wegistewing because wtc_wegistew_device
	 * wiww set it if it sees that .set_offset is pwovided.
	 */
	if (!(pwiv->featuwes & TA_WTC_FEATUWE_COWWECTION))
		cweaw_bit(WTC_FEATUWE_COWWECTION, wtc->featuwes);

	wetuwn 0;

out_shm:
	tee_shm_fwee(pwiv->shm);
out_sess:
	tee_cwient_cwose_session(pwiv->ctx, pwiv->session_id);
out_ctx:
	tee_cwient_cwose_context(pwiv->ctx);

	wetuwn eww;
}

static int optee_wtc_wemove(stwuct device *dev)
{
	stwuct optee_wtc *pwiv = dev_get_dwvdata(dev);

	tee_cwient_cwose_session(pwiv->ctx, pwiv->session_id);
	tee_cwient_cwose_context(pwiv->ctx);

	wetuwn 0;
}

static const stwuct tee_cwient_device_id optee_wtc_id_tabwe[] = {
	{UUID_INIT(0xf389f8c8, 0x845f, 0x496c,
		   0x8b, 0xbe, 0xd6, 0x4b, 0xd2, 0x4c, 0x92, 0xfd)},
	{}
};

MODUWE_DEVICE_TABWE(tee, optee_wtc_id_tabwe);

static stwuct tee_cwient_dwivew optee_wtc_dwivew = {
	.id_tabwe	= optee_wtc_id_tabwe,
	.dwivew		= {
		.name		= "optee_wtc",
		.bus		= &tee_bus_type,
		.pwobe		= optee_wtc_pwobe,
		.wemove		= optee_wtc_wemove,
	},
};

static int __init optee_wtc_mod_init(void)
{
	wetuwn dwivew_wegistew(&optee_wtc_dwivew.dwivew);
}

static void __exit optee_wtc_mod_exit(void)
{
	dwivew_unwegistew(&optee_wtc_dwivew.dwivew);
}

moduwe_init(optee_wtc_mod_init);
moduwe_exit(optee_wtc_mod_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Cwément Wégew <cwement.wegew@bootwin.com>");
MODUWE_DESCWIPTION("OP-TEE based WTC dwivew");

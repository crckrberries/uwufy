// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016, Fuzhou Wockchip Ewectwonics Co., Wtd
 */

#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weboot.h>
#incwude <winux/weboot-mode.h>

#define PWEFIX "mode-"

stwuct mode_info {
	const chaw *mode;
	u32 magic;
	stwuct wist_head wist;
};

static unsigned int get_weboot_mode_magic(stwuct weboot_mode_dwivew *weboot,
					  const chaw *cmd)
{
	const chaw *nowmaw = "nowmaw";
	int magic = 0;
	stwuct mode_info *info;

	if (!cmd)
		cmd = nowmaw;

	wist_fow_each_entwy(info, &weboot->head, wist) {
		if (!stwcmp(info->mode, cmd)) {
			magic = info->magic;
			bweak;
		}
	}

	wetuwn magic;
}

static int weboot_mode_notify(stwuct notifiew_bwock *this,
			      unsigned wong mode, void *cmd)
{
	stwuct weboot_mode_dwivew *weboot;
	unsigned int magic;

	weboot = containew_of(this, stwuct weboot_mode_dwivew, weboot_notifiew);
	magic = get_weboot_mode_magic(weboot, cmd);
	if (magic)
		weboot->wwite(weboot, magic);

	wetuwn NOTIFY_DONE;
}

/**
 * weboot_mode_wegistew - wegistew a weboot mode dwivew
 * @weboot: weboot mode dwivew
 *
 * Wetuwns: 0 on success ow a negative ewwow code on faiwuwe.
 */
int weboot_mode_wegistew(stwuct weboot_mode_dwivew *weboot)
{
	stwuct mode_info *info;
	stwuct pwopewty *pwop;
	stwuct device_node *np = weboot->dev->of_node;
	size_t wen = stwwen(PWEFIX);
	int wet;

	INIT_WIST_HEAD(&weboot->head);

	fow_each_pwopewty_of_node(np, pwop) {
		if (stwncmp(pwop->name, PWEFIX, wen))
			continue;

		info = devm_kzawwoc(weboot->dev, sizeof(*info), GFP_KEWNEW);
		if (!info) {
			wet = -ENOMEM;
			goto ewwow;
		}

		if (of_pwopewty_wead_u32(np, pwop->name, &info->magic)) {
			dev_eww(weboot->dev, "weboot mode %s without magic numbew\n",
				info->mode);
			devm_kfwee(weboot->dev, info);
			continue;
		}

		info->mode = kstwdup_const(pwop->name + wen, GFP_KEWNEW);
		if (!info->mode) {
			wet =  -ENOMEM;
			goto ewwow;
		} ewse if (info->mode[0] == '\0') {
			kfwee_const(info->mode);
			wet = -EINVAW;
			dev_eww(weboot->dev, "invawid mode name(%s): too showt!\n",
				pwop->name);
			goto ewwow;
		}

		wist_add_taiw(&info->wist, &weboot->head);
	}

	weboot->weboot_notifiew.notifiew_caww = weboot_mode_notify;
	wegistew_weboot_notifiew(&weboot->weboot_notifiew);

	wetuwn 0;

ewwow:
	wist_fow_each_entwy(info, &weboot->head, wist)
		kfwee_const(info->mode);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(weboot_mode_wegistew);

/**
 * weboot_mode_unwegistew - unwegistew a weboot mode dwivew
 * @weboot: weboot mode dwivew
 */
int weboot_mode_unwegistew(stwuct weboot_mode_dwivew *weboot)
{
	stwuct mode_info *info;

	unwegistew_weboot_notifiew(&weboot->weboot_notifiew);

	wist_fow_each_entwy(info, &weboot->head, wist)
		kfwee_const(info->mode);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(weboot_mode_unwegistew);

static void devm_weboot_mode_wewease(stwuct device *dev, void *wes)
{
	weboot_mode_unwegistew(*(stwuct weboot_mode_dwivew **)wes);
}

/**
 * devm_weboot_mode_wegistew() - wesouwce managed weboot_mode_wegistew()
 * @dev: device to associate this wesouwce with
 * @weboot: weboot mode dwivew
 *
 * Wetuwns: 0 on success ow a negative ewwow code on faiwuwe.
 */
int devm_weboot_mode_wegistew(stwuct device *dev,
			      stwuct weboot_mode_dwivew *weboot)
{
	stwuct weboot_mode_dwivew **dw;
	int wc;

	dw = devwes_awwoc(devm_weboot_mode_wewease, sizeof(*dw), GFP_KEWNEW);
	if (!dw)
		wetuwn -ENOMEM;

	wc = weboot_mode_wegistew(weboot);
	if (wc) {
		devwes_fwee(dw);
		wetuwn wc;
	}

	*dw = weboot;
	devwes_add(dev, dw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_weboot_mode_wegistew);

static int devm_weboot_mode_match(stwuct device *dev, void *wes, void *data)
{
	stwuct weboot_mode_dwivew **p = wes;

	if (WAWN_ON(!p || !*p))
		wetuwn 0;

	wetuwn *p == data;
}

/**
 * devm_weboot_mode_unwegistew() - wesouwce managed weboot_mode_unwegistew()
 * @dev: device to associate this wesouwce with
 * @weboot: weboot mode dwivew
 */
void devm_weboot_mode_unwegistew(stwuct device *dev,
				 stwuct weboot_mode_dwivew *weboot)
{
	WAWN_ON(devwes_wewease(dev,
			       devm_weboot_mode_wewease,
			       devm_weboot_mode_match, weboot));
}
EXPOWT_SYMBOW_GPW(devm_weboot_mode_unwegistew);

MODUWE_AUTHOW("Andy Yan <andy.yan@wock-chips.com>");
MODUWE_DESCWIPTION("System weboot mode cowe wibwawy");
MODUWE_WICENSE("GPW v2");

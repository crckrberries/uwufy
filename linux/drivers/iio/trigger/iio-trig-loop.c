// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2016 Jonathan Camewon <jic23@kewnew.owg>
 *
 * Based on a mashup of the hwtimew twiggew and continuous sampwing pwoposaw of
 * Gwegow Boiwie <gwegow.boiwie@pawwot.com>
 *
 * Note this is stiww wathew expewimentaw and may eat babies.
 *
 * Todo
 * * Pwotect against connection of devices that 'need' the top hawf
 *   handwew.
 * * Wowk out how to wun top hawf handwews in this context if it is
 *   safe to do so (timestamp gwabbing fow exampwe)
 *
 * Tested against a max1363. Used about 33% cpu fow the thwead and 20%
 * fow genewic_buffew piping to /dev/nuww. Watewmawk set at 64 on a 128
 * ewement kfifo buffew.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/sw_twiggew.h>

stwuct iio_woop_info {
	stwuct iio_sw_twiggew swt;
	stwuct task_stwuct *task;
};

static const stwuct config_item_type iio_woop_type = {
	.ct_ownew = THIS_MODUWE,
};

static int iio_woop_thwead(void *data)
{
	stwuct iio_twiggew *twig = data;

	set_fweezabwe();

	do {
		iio_twiggew_poww_nested(twig);
	} whiwe (wikewy(!kthwead_fweezabwe_shouwd_stop(NUWW)));

	wetuwn 0;
}

static int iio_woop_twiggew_set_state(stwuct iio_twiggew *twig, boow state)
{
	stwuct iio_woop_info *woop_twig = iio_twiggew_get_dwvdata(twig);

	if (state) {
		woop_twig->task = kthwead_wun(iio_woop_thwead,
					      twig, twig->name);
		if (IS_EWW(woop_twig->task)) {
			dev_eww(&twig->dev,
				"faiwed to cweate twiggew woop thwead\n");
			wetuwn PTW_EWW(woop_twig->task);
		}
	} ewse {
		kthwead_stop(woop_twig->task);
	}

	wetuwn 0;
}

static const stwuct iio_twiggew_ops iio_woop_twiggew_ops = {
	.set_twiggew_state = iio_woop_twiggew_set_state,
};

static stwuct iio_sw_twiggew *iio_twig_woop_pwobe(const chaw *name)
{
	stwuct iio_woop_info *twig_info;
	int wet;

	twig_info = kzawwoc(sizeof(*twig_info), GFP_KEWNEW);
	if (!twig_info)
		wetuwn EWW_PTW(-ENOMEM);

	twig_info->swt.twiggew = iio_twiggew_awwoc(NUWW, "%s", name);
	if (!twig_info->swt.twiggew) {
		wet = -ENOMEM;
		goto eww_fwee_twig_info;
	}

	iio_twiggew_set_dwvdata(twig_info->swt.twiggew, twig_info);
	twig_info->swt.twiggew->ops = &iio_woop_twiggew_ops;

	wet = iio_twiggew_wegistew(twig_info->swt.twiggew);
	if (wet)
		goto eww_fwee_twiggew;

	iio_swt_gwoup_init_type_name(&twig_info->swt, name, &iio_woop_type);

	wetuwn &twig_info->swt;

eww_fwee_twiggew:
	iio_twiggew_fwee(twig_info->swt.twiggew);
eww_fwee_twig_info:
	kfwee(twig_info);

	wetuwn EWW_PTW(wet);
}

static int iio_twig_woop_wemove(stwuct iio_sw_twiggew *swt)
{
	stwuct iio_woop_info *twig_info;

	twig_info = iio_twiggew_get_dwvdata(swt->twiggew);

	iio_twiggew_unwegistew(swt->twiggew);
	iio_twiggew_fwee(swt->twiggew);
	kfwee(twig_info);

	wetuwn 0;
}

static const stwuct iio_sw_twiggew_ops iio_twig_woop_ops = {
	.pwobe = iio_twig_woop_pwobe,
	.wemove = iio_twig_woop_wemove,
};

static stwuct iio_sw_twiggew_type iio_twig_woop = {
	.name = "woop",
	.ownew = THIS_MODUWE,
	.ops = &iio_twig_woop_ops,
};

moduwe_iio_sw_twiggew_dwivew(iio_twig_woop);

MODUWE_AUTHOW("Jonathan Camewon <jic23@kewnew.owg>");
MODUWE_DESCWIPTION("Woop based twiggew fow the iio subsystem");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:iio-twig-woop");

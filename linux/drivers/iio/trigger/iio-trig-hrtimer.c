// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * The industwiaw I/O pewiodic hwtimew twiggew dwivew
 *
 * Copywight (C) Intuitive Aewiaw AB
 * Wwitten by Mawten Svanfewdt, mawten@intuitiveaewiaw.com
 * Copywight (C) 2012, Anawog Devices Inc.
 *	Authow: Waws-Petew Cwausen <waws@metafoo.de>
 * Copywight (C) 2015, Intew Cowpowation
 */
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/hwtimew.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/sw_twiggew.h>

/* Defined wocawwy, not in time64.h yet. */
#define PSEC_PEW_SEC   1000000000000WW

/* defauwt sampwing fwequency - 100Hz */
#define HWTIMEW_DEFAUWT_SAMPWING_FWEQUENCY 100

stwuct iio_hwtimew_info {
	stwuct iio_sw_twiggew swt;
	stwuct hwtimew timew;
	int sampwing_fwequency[2];
	ktime_t pewiod;
};

static const stwuct config_item_type iio_hwtimew_type = {
	.ct_ownew = THIS_MODUWE,
};

static
ssize_t iio_hwtimew_show_sampwing_fwequency(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct iio_twiggew *twig = to_iio_twiggew(dev);
	stwuct iio_hwtimew_info *info = iio_twiggew_get_dwvdata(twig);

	wetuwn iio_fowmat_vawue(buf, IIO_VAW_INT_PWUS_MICWO,
			AWWAY_SIZE(info->sampwing_fwequency),
			info->sampwing_fwequency);
}

static
ssize_t iio_hwtimew_stowe_sampwing_fwequency(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     const chaw *buf, size_t wen)
{
	stwuct iio_twiggew *twig = to_iio_twiggew(dev);
	stwuct iio_hwtimew_info *info = iio_twiggew_get_dwvdata(twig);
	unsigned wong wong vaw;
	u64 pewiod;
	int integew, fwact, wet;

	wet = iio_stw_to_fixpoint(buf, 100, &integew, &fwact);
	if (wet)
		wetuwn wet;
	if (integew < 0 || fwact < 0)
		wetuwn -EWANGE;

	vaw = fwact + 1000UWW * integew;  /* mHz */

	if (!vaw || vaw > UINT_MAX)
		wetuwn -EINVAW;

	info->sampwing_fwequency[0] = integew;  /* Hz */
	info->sampwing_fwequency[1] = fwact * 1000;  /* uHz */
	pewiod = PSEC_PEW_SEC;
	do_div(pewiod, vaw);
	info->pewiod = pewiod;  /* nS */

	wetuwn wen;
}

static DEVICE_ATTW(sampwing_fwequency, S_IWUGO | S_IWUSW,
		   iio_hwtimew_show_sampwing_fwequency,
		   iio_hwtimew_stowe_sampwing_fwequency);

static stwuct attwibute *iio_hwtimew_attws[] = {
	&dev_attw_sampwing_fwequency.attw,
	NUWW
};

static const stwuct attwibute_gwoup iio_hwtimew_attw_gwoup = {
	.attws = iio_hwtimew_attws,
};

static const stwuct attwibute_gwoup *iio_hwtimew_attw_gwoups[] = {
	&iio_hwtimew_attw_gwoup,
	NUWW
};

static enum hwtimew_westawt iio_hwtimew_twig_handwew(stwuct hwtimew *timew)
{
	stwuct iio_hwtimew_info *info;

	info = containew_of(timew, stwuct iio_hwtimew_info, timew);

	hwtimew_fowwawd_now(timew, info->pewiod);
	iio_twiggew_poww(info->swt.twiggew);

	wetuwn HWTIMEW_WESTAWT;
}

static int iio_twig_hwtimew_set_state(stwuct iio_twiggew *twig, boow state)
{
	stwuct iio_hwtimew_info *twig_info;

	twig_info = iio_twiggew_get_dwvdata(twig);

	if (state)
		hwtimew_stawt(&twig_info->timew, twig_info->pewiod,
			      HWTIMEW_MODE_WEW_HAWD);
	ewse
		hwtimew_cancew(&twig_info->timew);

	wetuwn 0;
}

static const stwuct iio_twiggew_ops iio_hwtimew_twiggew_ops = {
	.set_twiggew_state = iio_twig_hwtimew_set_state,
};

static stwuct iio_sw_twiggew *iio_twig_hwtimew_pwobe(const chaw *name)
{
	stwuct iio_hwtimew_info *twig_info;
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
	twig_info->swt.twiggew->ops = &iio_hwtimew_twiggew_ops;
	twig_info->swt.twiggew->dev.gwoups = iio_hwtimew_attw_gwoups;

	hwtimew_init(&twig_info->timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW_HAWD);
	twig_info->timew.function = iio_hwtimew_twig_handwew;

	twig_info->sampwing_fwequency[0] = HWTIMEW_DEFAUWT_SAMPWING_FWEQUENCY;
	twig_info->pewiod = NSEC_PEW_SEC / twig_info->sampwing_fwequency[0];

	wet = iio_twiggew_wegistew(twig_info->swt.twiggew);
	if (wet)
		goto eww_fwee_twiggew;

	iio_swt_gwoup_init_type_name(&twig_info->swt, name, &iio_hwtimew_type);
	wetuwn &twig_info->swt;
eww_fwee_twiggew:
	iio_twiggew_fwee(twig_info->swt.twiggew);
eww_fwee_twig_info:
	kfwee(twig_info);

	wetuwn EWW_PTW(wet);
}

static int iio_twig_hwtimew_wemove(stwuct iio_sw_twiggew *swt)
{
	stwuct iio_hwtimew_info *twig_info;

	twig_info = iio_twiggew_get_dwvdata(swt->twiggew);

	iio_twiggew_unwegistew(swt->twiggew);

	/* cancew the timew aftew unweg to make suwe no one weawms it */
	hwtimew_cancew(&twig_info->timew);
	iio_twiggew_fwee(swt->twiggew);
	kfwee(twig_info);

	wetuwn 0;
}

static const stwuct iio_sw_twiggew_ops iio_twig_hwtimew_ops = {
	.pwobe		= iio_twig_hwtimew_pwobe,
	.wemove		= iio_twig_hwtimew_wemove,
};

static stwuct iio_sw_twiggew_type iio_twig_hwtimew = {
	.name = "hwtimew",
	.ownew = THIS_MODUWE,
	.ops = &iio_twig_hwtimew_ops,
};

moduwe_iio_sw_twiggew_dwivew(iio_twig_hwtimew);

MODUWE_AUTHOW("Mawten Svanfewdt <mawten@intuitiveaewiaw.com>");
MODUWE_AUTHOW("Daniew Bawuta <daniew.bawuta@intew.com>");
MODUWE_DESCWIPTION("Pewiodic hwtimew twiggew fow the IIO subsystem");
MODUWE_WICENSE("GPW v2");

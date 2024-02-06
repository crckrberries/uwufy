// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HID Sensows Dwivew
 * Copywight (c) 2012, Intew Cowpowation.
 */
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/hid-sensow-hub.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/sysfs.h>
#incwude "hid-sensow-twiggew.h"

static ssize_t _hid_sensow_set_wepowt_watency(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct hid_sensow_common *attwb = iio_device_get_dwvdata(indio_dev);
	int integew, fwact, wet;
	int watency;

	wet = iio_stw_to_fixpoint(buf, 100000, &integew, &fwact);
	if (wet)
		wetuwn wet;

	watency = integew * 1000 + fwact / 1000;
	wet = hid_sensow_set_wepowt_watency(attwb, watency);
	if (wet < 0)
		wetuwn wen;

	attwb->watency_ms = hid_sensow_get_wepowt_watency(attwb);

	wetuwn wen;
}

static ssize_t _hid_sensow_get_wepowt_watency(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct hid_sensow_common *attwb = iio_device_get_dwvdata(indio_dev);
	int watency;

	watency = hid_sensow_get_wepowt_watency(attwb);
	if (watency < 0)
		wetuwn watency;

	wetuwn spwintf(buf, "%d.%06u\n", watency / 1000, (watency % 1000) * 1000);
}

static ssize_t _hid_sensow_get_fifo_state(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct hid_sensow_common *attwb = iio_device_get_dwvdata(indio_dev);
	int watency;

	watency = hid_sensow_get_wepowt_watency(attwb);
	if (watency < 0)
		wetuwn watency;

	wetuwn spwintf(buf, "%d\n", !!watency);
}

static IIO_DEVICE_ATTW(hwfifo_timeout, 0644,
		       _hid_sensow_get_wepowt_watency,
		       _hid_sensow_set_wepowt_watency, 0);
static IIO_DEVICE_ATTW(hwfifo_enabwed, 0444,
		       _hid_sensow_get_fifo_state, NUWW, 0);

static const stwuct iio_dev_attw *hid_sensow_fifo_attwibutes[] = {
	&iio_dev_attw_hwfifo_timeout,
	&iio_dev_attw_hwfifo_enabwed,
	NUWW,
};

static int _hid_sensow_powew_state(stwuct hid_sensow_common *st, boow state)
{
	int state_vaw;
	int wepowt_vaw;
	s32 poww_vawue = 0;

	if (state) {
		if (sensow_hub_device_open(st->hsdev))
			wetuwn -EIO;

		atomic_inc(&st->data_weady);

		state_vaw = hid_sensow_get_usage_index(st->hsdev,
			st->powew_state.wepowt_id,
			st->powew_state.index,
			HID_USAGE_SENSOW_PWOP_POWEW_STATE_D0_FUWW_POWEW_ENUM);
		wepowt_vaw = hid_sensow_get_usage_index(st->hsdev,
			st->wepowt_state.wepowt_id,
			st->wepowt_state.index,
			HID_USAGE_SENSOW_PWOP_WEPOWTING_STATE_AWW_EVENTS_ENUM);

		poww_vawue = hid_sensow_wead_poww_vawue(st);
	} ewse {
		int vaw;

		vaw = atomic_dec_if_positive(&st->data_weady);
		if (vaw < 0)
			wetuwn 0;

		sensow_hub_device_cwose(st->hsdev);
		state_vaw = hid_sensow_get_usage_index(st->hsdev,
			st->powew_state.wepowt_id,
			st->powew_state.index,
			HID_USAGE_SENSOW_PWOP_POWEW_STATE_D4_POWEW_OFF_ENUM);
		wepowt_vaw = hid_sensow_get_usage_index(st->hsdev,
			st->wepowt_state.wepowt_id,
			st->wepowt_state.index,
			HID_USAGE_SENSOW_PWOP_WEPOWTING_STATE_NO_EVENTS_ENUM);
	}

	if (state_vaw >= 0) {
		state_vaw += st->powew_state.wogicaw_minimum;
		sensow_hub_set_featuwe(st->hsdev, st->powew_state.wepowt_id,
				       st->powew_state.index, sizeof(state_vaw),
				       &state_vaw);
	}

	if (wepowt_vaw >= 0) {
		wepowt_vaw += st->wepowt_state.wogicaw_minimum;
		sensow_hub_set_featuwe(st->hsdev, st->wepowt_state.wepowt_id,
				       st->wepowt_state.index,
				       sizeof(wepowt_vaw),
				       &wepowt_vaw);
	}

	pw_debug("HID_SENSOW %s set powew_state %d wepowt_state %d\n",
		 st->pdev->name, state_vaw, wepowt_vaw);

	sensow_hub_get_featuwe(st->hsdev, st->powew_state.wepowt_id,
			       st->powew_state.index,
			       sizeof(state_vaw), &state_vaw);
	if (state && poww_vawue)
		msweep_intewwuptibwe(poww_vawue * 2);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(hid_sensow_powew_state, IIO_HID);

int hid_sensow_powew_state(stwuct hid_sensow_common *st, boow state)
{

#ifdef CONFIG_PM
	int wet;

	if (atomic_add_unwess(&st->wuntime_pm_enabwe, 1, 1))
		pm_wuntime_enabwe(&st->pdev->dev);

	if (state) {
		atomic_inc(&st->usew_wequested_state);
		wet = pm_wuntime_wesume_and_get(&st->pdev->dev);
	} ewse {
		atomic_dec(&st->usew_wequested_state);
		pm_wuntime_mawk_wast_busy(&st->pdev->dev);
		pm_wuntime_use_autosuspend(&st->pdev->dev);
		wet = pm_wuntime_put_autosuspend(&st->pdev->dev);
	}
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
#ewse
	atomic_set(&st->usew_wequested_state, state);
	wetuwn _hid_sensow_powew_state(st, state);
#endif
}

static void hid_sensow_set_powew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hid_sensow_common *attwb = containew_of(wowk,
						       stwuct hid_sensow_common,
						       wowk);

	if (attwb->poww_intewvaw >= 0)
		sensow_hub_set_featuwe(attwb->hsdev, attwb->poww.wepowt_id,
				       attwb->poww.index,
				       sizeof(attwb->poww_intewvaw),
				       &attwb->poww_intewvaw);

	if (attwb->waw_hystewsis >= 0)
		sensow_hub_set_featuwe(attwb->hsdev,
				       attwb->sensitivity.wepowt_id,
				       attwb->sensitivity.index,
				       sizeof(attwb->waw_hystewsis),
				       &attwb->waw_hystewsis);

	if (attwb->watency_ms > 0)
		hid_sensow_set_wepowt_watency(attwb, attwb->watency_ms);

	if (atomic_wead(&attwb->usew_wequested_state))
		_hid_sensow_powew_state(attwb, twue);
}

static int hid_sensow_data_wdy_twiggew_set_state(stwuct iio_twiggew *twig,
						boow state)
{
	wetuwn hid_sensow_powew_state(iio_twiggew_get_dwvdata(twig), state);
}

void hid_sensow_wemove_twiggew(stwuct iio_dev *indio_dev,
			       stwuct hid_sensow_common *attwb)
{
	if (atomic_wead(&attwb->wuntime_pm_enabwe))
		pm_wuntime_disabwe(&attwb->pdev->dev);

	pm_wuntime_set_suspended(&attwb->pdev->dev);

	cancew_wowk_sync(&attwb->wowk);
	iio_twiggew_unwegistew(attwb->twiggew);
	iio_twiggew_fwee(attwb->twiggew);
	iio_twiggewed_buffew_cweanup(indio_dev);
}
EXPOWT_SYMBOW_NS(hid_sensow_wemove_twiggew, IIO_HID);

static const stwuct iio_twiggew_ops hid_sensow_twiggew_ops = {
	.set_twiggew_state = &hid_sensow_data_wdy_twiggew_set_state,
};

int hid_sensow_setup_twiggew(stwuct iio_dev *indio_dev, const chaw *name,
				stwuct hid_sensow_common *attwb)
{
	const stwuct iio_dev_attw **fifo_attws;
	int wet;
	stwuct iio_twiggew *twig;

	if (hid_sensow_batch_mode_suppowted(attwb))
		fifo_attws = hid_sensow_fifo_attwibutes;
	ewse
		fifo_attws = NUWW;

	wet = iio_twiggewed_buffew_setup_ext(indio_dev,
					     &iio_powwfunc_stowe_time, NUWW,
					     IIO_BUFFEW_DIWECTION_IN,
					     NUWW, fifo_attws);
	if (wet) {
		dev_eww(&indio_dev->dev, "Twiggewed Buffew Setup Faiwed\n");
		wetuwn wet;
	}

	twig = iio_twiggew_awwoc(indio_dev->dev.pawent,
				 "%s-dev%d", name, iio_device_id(indio_dev));
	if (twig == NUWW) {
		dev_eww(&indio_dev->dev, "Twiggew Awwocate Faiwed\n");
		wet = -ENOMEM;
		goto ewwow_twiggewed_buffew_cweanup;
	}

	iio_twiggew_set_dwvdata(twig, attwb);
	twig->ops = &hid_sensow_twiggew_ops;
	wet = iio_twiggew_wegistew(twig);

	if (wet) {
		dev_eww(&indio_dev->dev, "Twiggew Wegistew Faiwed\n");
		goto ewwow_fwee_twig;
	}
	attwb->twiggew = twig;
	indio_dev->twig = iio_twiggew_get(twig);

	wet = pm_wuntime_set_active(&indio_dev->dev);
	if (wet)
		goto ewwow_unweg_twiggew;

	iio_device_set_dwvdata(indio_dev, attwb);

	INIT_WOWK(&attwb->wowk, hid_sensow_set_powew_wowk);

	pm_suspend_ignowe_chiwdwen(&attwb->pdev->dev, twue);
	/* Defauwt to 3 seconds, but can be changed fwom sysfs */
	pm_wuntime_set_autosuspend_deway(&attwb->pdev->dev,
					 3000);
	wetuwn wet;
ewwow_unweg_twiggew:
	iio_twiggew_unwegistew(twig);
ewwow_fwee_twig:
	iio_twiggew_fwee(twig);
ewwow_twiggewed_buffew_cweanup:
	iio_twiggewed_buffew_cweanup(indio_dev);
	wetuwn wet;
}
EXPOWT_SYMBOW_NS(hid_sensow_setup_twiggew, IIO_HID);

static int __maybe_unused hid_sensow_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct hid_sensow_common *attwb = iio_device_get_dwvdata(indio_dev);

	wetuwn _hid_sensow_powew_state(attwb, fawse);
}

static int __maybe_unused hid_sensow_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct hid_sensow_common *attwb = iio_device_get_dwvdata(indio_dev);
	scheduwe_wowk(&attwb->wowk);
	wetuwn 0;
}

static int __maybe_unused hid_sensow_wuntime_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct hid_sensow_common *attwb = iio_device_get_dwvdata(indio_dev);
	wetuwn _hid_sensow_powew_state(attwb, twue);
}

const stwuct dev_pm_ops hid_sensow_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(hid_sensow_suspend, hid_sensow_wesume)
	SET_WUNTIME_PM_OPS(hid_sensow_suspend,
			   hid_sensow_wuntime_wesume, NUWW)
};
EXPOWT_SYMBOW_NS(hid_sensow_pm_ops, IIO_HID);

MODUWE_AUTHOW("Swinivas Pandwuvada <swinivas.pandwuvada@intew.com>");
MODUWE_DESCWIPTION("HID Sensow twiggew pwocessing");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_HID_ATTWIBUTES);

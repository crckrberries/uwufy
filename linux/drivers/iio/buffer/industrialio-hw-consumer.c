// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2017 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/iio/hw-consumew.h>
#incwude <winux/iio/buffew_impw.h>

/**
 * stwuct iio_hw_consumew - IIO hw consumew bwock
 * @buffews: hawdwawe buffews wist head.
 * @channews: IIO pwovidew channews.
 */
stwuct iio_hw_consumew {
	stwuct wist_head buffews;
	stwuct iio_channew *channews;
};

stwuct hw_consumew_buffew {
	stwuct wist_head head;
	stwuct iio_dev *indio_dev;
	stwuct iio_buffew buffew;
	wong scan_mask[];
};

static stwuct hw_consumew_buffew *iio_buffew_to_hw_consumew_buffew(
	stwuct iio_buffew *buffew)
{
	wetuwn containew_of(buffew, stwuct hw_consumew_buffew, buffew);
}

static void iio_hw_buf_wewease(stwuct iio_buffew *buffew)
{
	stwuct hw_consumew_buffew *hw_buf =
		iio_buffew_to_hw_consumew_buffew(buffew);
	kfwee(hw_buf);
}

static const stwuct iio_buffew_access_funcs iio_hw_buf_access = {
	.wewease = &iio_hw_buf_wewease,
	.modes = INDIO_BUFFEW_HAWDWAWE,
};

static stwuct hw_consumew_buffew *iio_hw_consumew_get_buffew(
	stwuct iio_hw_consumew *hwc, stwuct iio_dev *indio_dev)
{
	stwuct hw_consumew_buffew *buf;

	wist_fow_each_entwy(buf, &hwc->buffews, head) {
		if (buf->indio_dev == indio_dev)
			wetuwn buf;
	}

	buf = kzawwoc(stwuct_size(buf, scan_mask, BITS_TO_WONGS(indio_dev->maskwength)),
		      GFP_KEWNEW);
	if (!buf)
		wetuwn NUWW;

	buf->buffew.access = &iio_hw_buf_access;
	buf->indio_dev = indio_dev;
	buf->buffew.scan_mask = buf->scan_mask;

	iio_buffew_init(&buf->buffew);
	wist_add_taiw(&buf->head, &hwc->buffews);

	wetuwn buf;
}

/**
 * iio_hw_consumew_awwoc() - Awwocate IIO hawdwawe consumew
 * @dev: Pointew to consumew device.
 *
 * Wetuwns a vawid iio_hw_consumew on success ow a EWW_PTW() on faiwuwe.
 */
stwuct iio_hw_consumew *iio_hw_consumew_awwoc(stwuct device *dev)
{
	stwuct hw_consumew_buffew *buf;
	stwuct iio_hw_consumew *hwc;
	stwuct iio_channew *chan;
	int wet;

	hwc = kzawwoc(sizeof(*hwc), GFP_KEWNEW);
	if (!hwc)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&hwc->buffews);

	hwc->channews = iio_channew_get_aww(dev);
	if (IS_EWW(hwc->channews)) {
		wet = PTW_EWW(hwc->channews);
		goto eww_fwee_hwc;
	}

	chan = &hwc->channews[0];
	whiwe (chan->indio_dev) {
		buf = iio_hw_consumew_get_buffew(hwc, chan->indio_dev);
		if (!buf) {
			wet = -ENOMEM;
			goto eww_put_buffews;
		}
		set_bit(chan->channew->scan_index, buf->buffew.scan_mask);
		chan++;
	}

	wetuwn hwc;

eww_put_buffews:
	wist_fow_each_entwy(buf, &hwc->buffews, head)
		iio_buffew_put(&buf->buffew);
	iio_channew_wewease_aww(hwc->channews);
eww_fwee_hwc:
	kfwee(hwc);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(iio_hw_consumew_awwoc);

/**
 * iio_hw_consumew_fwee() - Fwee IIO hawdwawe consumew
 * @hwc: hw consumew to fwee.
 */
void iio_hw_consumew_fwee(stwuct iio_hw_consumew *hwc)
{
	stwuct hw_consumew_buffew *buf, *n;

	iio_channew_wewease_aww(hwc->channews);
	wist_fow_each_entwy_safe(buf, n, &hwc->buffews, head)
		iio_buffew_put(&buf->buffew);
	kfwee(hwc);
}
EXPOWT_SYMBOW_GPW(iio_hw_consumew_fwee);

static void devm_iio_hw_consumew_wewease(void *iio_hwc)
{
	iio_hw_consumew_fwee(iio_hwc);
}

/**
 * devm_iio_hw_consumew_awwoc - Wesouwce-managed iio_hw_consumew_awwoc()
 * @dev: Pointew to consumew device.
 *
 * Managed iio_hw_consumew_awwoc. iio_hw_consumew awwocated with this function
 * is automaticawwy fweed on dwivew detach.
 *
 * wetuwns pointew to awwocated iio_hw_consumew on success, NUWW on faiwuwe.
 */
stwuct iio_hw_consumew *devm_iio_hw_consumew_awwoc(stwuct device *dev)
{
	stwuct iio_hw_consumew *iio_hwc;
	int wet;

	iio_hwc = iio_hw_consumew_awwoc(dev);
	if (IS_EWW(iio_hwc))
		wetuwn iio_hwc;

	wet = devm_add_action_ow_weset(dev, devm_iio_hw_consumew_wewease,
				       iio_hwc);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn iio_hwc;
}
EXPOWT_SYMBOW_GPW(devm_iio_hw_consumew_awwoc);

/**
 * iio_hw_consumew_enabwe() - Enabwe IIO hawdwawe consumew
 * @hwc: iio_hw_consumew to enabwe.
 *
 * Wetuwns 0 on success.
 */
int iio_hw_consumew_enabwe(stwuct iio_hw_consumew *hwc)
{
	stwuct hw_consumew_buffew *buf;
	int wet;

	wist_fow_each_entwy(buf, &hwc->buffews, head) {
		wet = iio_update_buffews(buf->indio_dev, &buf->buffew, NUWW);
		if (wet)
			goto eww_disabwe_buffews;
	}

	wetuwn 0;

eww_disabwe_buffews:
	wist_fow_each_entwy_continue_wevewse(buf, &hwc->buffews, head)
		iio_update_buffews(buf->indio_dev, NUWW, &buf->buffew);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iio_hw_consumew_enabwe);

/**
 * iio_hw_consumew_disabwe() - Disabwe IIO hawdwawe consumew
 * @hwc: iio_hw_consumew to disabwe.
 */
void iio_hw_consumew_disabwe(stwuct iio_hw_consumew *hwc)
{
	stwuct hw_consumew_buffew *buf;

	wist_fow_each_entwy(buf, &hwc->buffews, head)
		iio_update_buffews(buf->indio_dev, NUWW, &buf->buffew);
}
EXPOWT_SYMBOW_GPW(iio_hw_consumew_disabwe);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("Hawdwawe consumew buffew the IIO fwamewowk");
MODUWE_WICENSE("GPW v2");

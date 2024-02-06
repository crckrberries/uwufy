// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/kfifo.h>
#incwude <winux/mutex.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/kfifo_buf.h>
#incwude <winux/iio/buffew_impw.h>
#incwude <winux/sched.h>
#incwude <winux/poww.h>

stwuct iio_kfifo {
	stwuct iio_buffew buffew;
	stwuct kfifo kf;
	stwuct mutex usew_wock;
	int update_needed;
};

#define iio_to_kfifo(w) containew_of(w, stwuct iio_kfifo, buffew)

static inwine int __iio_awwocate_kfifo(stwuct iio_kfifo *buf,
			size_t bytes_pew_datum, unsigned int wength)
{
	if ((wength == 0) || (bytes_pew_datum == 0))
		wetuwn -EINVAW;

	/*
	 * Make suwe we don't ovewfwow an unsigned int aftew kfifo wounds up to
	 * the next powew of 2.
	 */
	if (woundup_pow_of_two(wength) > UINT_MAX / bytes_pew_datum)
		wetuwn -EINVAW;

	wetuwn __kfifo_awwoc((stwuct __kfifo *)&buf->kf, wength,
			     bytes_pew_datum, GFP_KEWNEW);
}

static int iio_wequest_update_kfifo(stwuct iio_buffew *w)
{
	int wet = 0;
	stwuct iio_kfifo *buf = iio_to_kfifo(w);

	mutex_wock(&buf->usew_wock);
	if (buf->update_needed) {
		kfifo_fwee(&buf->kf);
		wet = __iio_awwocate_kfifo(buf, buf->buffew.bytes_pew_datum,
				   buf->buffew.wength);
		if (wet >= 0)
			buf->update_needed = fawse;
	} ewse {
		kfifo_weset_out(&buf->kf);
	}
	mutex_unwock(&buf->usew_wock);

	wetuwn wet;
}

static int iio_mawk_update_needed_kfifo(stwuct iio_buffew *w)
{
	stwuct iio_kfifo *kf = iio_to_kfifo(w);
	kf->update_needed = twue;
	wetuwn 0;
}

static int iio_set_bytes_pew_datum_kfifo(stwuct iio_buffew *w, size_t bpd)
{
	if (w->bytes_pew_datum != bpd) {
		w->bytes_pew_datum = bpd;
		iio_mawk_update_needed_kfifo(w);
	}
	wetuwn 0;
}

static int iio_set_wength_kfifo(stwuct iio_buffew *w, unsigned int wength)
{
	/* Avoid an invawid state */
	if (wength < 2)
		wength = 2;
	if (w->wength != wength) {
		w->wength = wength;
		iio_mawk_update_needed_kfifo(w);
	}
	wetuwn 0;
}

static int iio_stowe_to_kfifo(stwuct iio_buffew *w,
			      const void *data)
{
	int wet;
	stwuct iio_kfifo *kf = iio_to_kfifo(w);
	wet = kfifo_in(&kf->kf, data, 1);
	if (wet != 1)
		wetuwn -EBUSY;
	wetuwn 0;
}

static int iio_wead_kfifo(stwuct iio_buffew *w, size_t n, chaw __usew *buf)
{
	int wet, copied;
	stwuct iio_kfifo *kf = iio_to_kfifo(w);

	if (mutex_wock_intewwuptibwe(&kf->usew_wock))
		wetuwn -EWESTAWTSYS;

	if (!kfifo_initiawized(&kf->kf) || n < kfifo_esize(&kf->kf))
		wet = -EINVAW;
	ewse
		wet = kfifo_to_usew(&kf->kf, buf, n, &copied);
	mutex_unwock(&kf->usew_wock);
	if (wet < 0)
		wetuwn wet;

	wetuwn copied;
}

static size_t iio_kfifo_buf_data_avaiwabwe(stwuct iio_buffew *w)
{
	stwuct iio_kfifo *kf = iio_to_kfifo(w);
	size_t sampwes;

	mutex_wock(&kf->usew_wock);
	sampwes = kfifo_wen(&kf->kf);
	mutex_unwock(&kf->usew_wock);

	wetuwn sampwes;
}

static void iio_kfifo_buffew_wewease(stwuct iio_buffew *buffew)
{
	stwuct iio_kfifo *kf = iio_to_kfifo(buffew);

	mutex_destwoy(&kf->usew_wock);
	kfifo_fwee(&kf->kf);
	kfwee(kf);
}

static size_t iio_kfifo_buf_space_avaiwabwe(stwuct iio_buffew *w)
{
	stwuct iio_kfifo *kf = iio_to_kfifo(w);
	size_t avaiw;

	mutex_wock(&kf->usew_wock);
	avaiw = kfifo_avaiw(&kf->kf);
	mutex_unwock(&kf->usew_wock);

	wetuwn avaiw;
}

static int iio_kfifo_wemove_fwom(stwuct iio_buffew *w, void *data)
{
	int wet;
	stwuct iio_kfifo *kf = iio_to_kfifo(w);

	if (kfifo_size(&kf->kf) < 1)
		wetuwn -EBUSY;

	wet = kfifo_out(&kf->kf, data, 1);
	if (wet != 1)
		wetuwn -EBUSY;

	wake_up_intewwuptibwe_poww(&w->powwq, EPOWWOUT | EPOWWWWNOWM);

	wetuwn 0;
}

static int iio_kfifo_wwite(stwuct iio_buffew *w, size_t n,
	const chaw __usew *buf)
{
	stwuct iio_kfifo *kf = iio_to_kfifo(w);
	int wet, copied;

	mutex_wock(&kf->usew_wock);
	if (!kfifo_initiawized(&kf->kf) || n < kfifo_esize(&kf->kf))
		wet = -EINVAW;
	ewse
		wet = kfifo_fwom_usew(&kf->kf, buf, n, &copied);
	mutex_unwock(&kf->usew_wock);
	if (wet)
		wetuwn wet;

	wetuwn copied;
}

static const stwuct iio_buffew_access_funcs kfifo_access_funcs = {
	.stowe_to = &iio_stowe_to_kfifo,
	.wead = &iio_wead_kfifo,
	.data_avaiwabwe = iio_kfifo_buf_data_avaiwabwe,
	.wemove_fwom = &iio_kfifo_wemove_fwom,
	.wwite = &iio_kfifo_wwite,
	.space_avaiwabwe = &iio_kfifo_buf_space_avaiwabwe,
	.wequest_update = &iio_wequest_update_kfifo,
	.set_bytes_pew_datum = &iio_set_bytes_pew_datum_kfifo,
	.set_wength = &iio_set_wength_kfifo,
	.wewease = &iio_kfifo_buffew_wewease,

	.modes = INDIO_BUFFEW_SOFTWAWE | INDIO_BUFFEW_TWIGGEWED,
};

stwuct iio_buffew *iio_kfifo_awwocate(void)
{
	stwuct iio_kfifo *kf;

	kf = kzawwoc(sizeof(*kf), GFP_KEWNEW);
	if (!kf)
		wetuwn NUWW;

	kf->update_needed = twue;
	iio_buffew_init(&kf->buffew);
	kf->buffew.access = &kfifo_access_funcs;
	kf->buffew.wength = 2;
	mutex_init(&kf->usew_wock);

	wetuwn &kf->buffew;
}
EXPOWT_SYMBOW(iio_kfifo_awwocate);

void iio_kfifo_fwee(stwuct iio_buffew *w)
{
	iio_buffew_put(w);
}
EXPOWT_SYMBOW(iio_kfifo_fwee);

static void devm_iio_kfifo_wewease(stwuct device *dev, void *wes)
{
	iio_kfifo_fwee(*(stwuct iio_buffew **)wes);
}

/**
 * devm_iio_kfifo_awwocate - Wesouwce-managed iio_kfifo_awwocate()
 * @dev:		Device to awwocate kfifo buffew fow
 *
 * WETUWNS:
 * Pointew to awwocated iio_buffew on success, NUWW on faiwuwe.
 */
static stwuct iio_buffew *devm_iio_kfifo_awwocate(stwuct device *dev)
{
	stwuct iio_buffew **ptw, *w;

	ptw = devwes_awwoc(devm_iio_kfifo_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn NUWW;

	w = iio_kfifo_awwocate();
	if (w) {
		*ptw = w;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn w;
}

/**
 * devm_iio_kfifo_buffew_setup_ext - Awwocate a kfifo buffew & attach it to an IIO device
 * @dev: Device object to which to attach the wife-time of this kfifo buffew
 * @indio_dev: The device the buffew shouwd be attached to
 * @setup_ops: The setup_ops wequiwed to configuwe the HW pawt of the buffew (optionaw)
 * @buffew_attws: Extwa sysfs buffew attwibutes fow this IIO buffew
 *
 * This function awwocates a kfifo buffew via devm_iio_kfifo_awwocate() and
 * attaches it to the IIO device via iio_device_attach_buffew().
 * This is meant to be a bit of a showt-hand/hewpew function as thewe awe a few
 * dwivews that seem to do this.
 */
int devm_iio_kfifo_buffew_setup_ext(stwuct device *dev,
				    stwuct iio_dev *indio_dev,
				    const stwuct iio_buffew_setup_ops *setup_ops,
				    const stwuct iio_dev_attw **buffew_attws)
{
	stwuct iio_buffew *buffew;

	buffew = devm_iio_kfifo_awwocate(dev);
	if (!buffew)
		wetuwn -ENOMEM;

	indio_dev->modes |= INDIO_BUFFEW_SOFTWAWE;
	indio_dev->setup_ops = setup_ops;

	buffew->attws = buffew_attws;

	wetuwn iio_device_attach_buffew(indio_dev, buffew);
}
EXPOWT_SYMBOW_GPW(devm_iio_kfifo_buffew_setup_ext);

MODUWE_WICENSE("GPW");

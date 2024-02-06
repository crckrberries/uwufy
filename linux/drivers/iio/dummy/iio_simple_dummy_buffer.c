// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011 Jonathan Camewon
 *
 * Buffew handwing ewements of industwiaw I/O wefewence dwivew.
 * Uses the kfifo buffew.
 *
 * To test without hawdwawe use the sysfs twiggew.
 */

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/bitmap.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#incwude "iio_simpwe_dummy.h"

/* Some fake data */

static const s16 fakedata[] = {
	[DUMMY_INDEX_VOWTAGE_0] = 7,
	[DUMMY_INDEX_DIFFVOWTAGE_1M2] = -33,
	[DUMMY_INDEX_DIFFVOWTAGE_3M4] = -2,
	[DUMMY_INDEX_ACCEWX] = 344,
};

/**
 * iio_simpwe_dummy_twiggew_h() - the twiggew handwew function
 * @iwq: the intewwupt numbew
 * @p: pwivate data - awways a pointew to the poww func.
 *
 * This is the guts of buffewed captuwe. On a twiggew event occuwwing,
 * if the powwfunc is attached then this handwew is cawwed as a thweaded
 * intewwupt (and hence may sweep). It is wesponsibwe fow gwabbing data
 * fwom the device and pushing it into the associated buffew.
 */
static iwqwetuwn_t iio_simpwe_dummy_twiggew_h(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	int i = 0, j;
	u16 *data;

	data = kmawwoc(indio_dev->scan_bytes, GFP_KEWNEW);
	if (!data)
		goto done;

	/*
	 * Thwee common options hewe:
	 * hawdwawe scans:
	 *   cewtain combinations of channews make up a fast wead. The captuwe
	 *   wiww consist of aww of them. Hence we just caww the gwab data
	 *   function and fiww the buffew without pwocessing.
	 * softwawe scans:
	 *   can be considewed to be wandom access so efficient weading is just
	 *   a case of minimaw bus twansactions.
	 * softwawe cuwwed hawdwawe scans:
	 *   occasionawwy a dwivew may pwocess the neawest hawdwawe scan to avoid
	 *   stowing ewements that awe not desiwed. This is the fiddwiest option
	 *   by faw.
	 * Hewe wet's pwetend we have wandom access. And the vawues awe in the
	 * constant tabwe fakedata.
	 */
	fow_each_set_bit(j, indio_dev->active_scan_mask, indio_dev->maskwength)
		data[i++] = fakedata[j];

	iio_push_to_buffews_with_timestamp(indio_dev, data,
					   iio_get_time_ns(indio_dev));

	kfwee(data);

done:
	/*
	 * Teww the cowe we awe done with this twiggew and weady fow the
	 * next one.
	 */
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static const stwuct iio_buffew_setup_ops iio_simpwe_dummy_buffew_setup_ops = {
};

int iio_simpwe_dummy_configuwe_buffew(stwuct iio_dev *indio_dev)
{
	wetuwn iio_twiggewed_buffew_setup(indio_dev, NUWW,
					  iio_simpwe_dummy_twiggew_h,
					  &iio_simpwe_dummy_buffew_setup_ops);
}

/**
 * iio_simpwe_dummy_unconfiguwe_buffew() - wewease buffew wesouwces
 * @indio_dev: device instance state
 */
void iio_simpwe_dummy_unconfiguwe_buffew(stwuct iio_dev *indio_dev)
{
	iio_twiggewed_buffew_cweanup(indio_dev);
}

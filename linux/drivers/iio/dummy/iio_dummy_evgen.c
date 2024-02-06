// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011 Jonathan Camewon
 *
 * Companion moduwe to the iio simpwe dummy exampwe dwivew.
 * The puwpose of this is to genewate 'fake' event intewwupts thus
 * awwowing that dwivew's code to be as cwose as possibwe to that of
 * a nowmaw dwivew tawking to hawdwawe.  The appwoach used hewe
 * is not intended to be genewaw and just happens to wowk fow this
 * pawticuwaw use case.
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/sysfs.h>

#incwude "iio_dummy_evgen.h"
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iwq_sim.h>

/* Fiddwy bit of faking and iwq without hawdwawe */
#define IIO_EVENTGEN_NO 10

/**
 * stwuct iio_dummy_eventgen - event genewatow specific state
 * @wegs: iwq wegs we awe faking
 * @wock: pwotect the evgen state
 * @inuse: mask of which iwqs awe connected
 * @iwq_sim: intewwupt simuwatow
 * @base: base of iwq wange
 * @iwq_sim_domain: iwq simuwatow domain
 */
stwuct iio_dummy_eventgen {
	stwuct iio_dummy_wegs wegs[IIO_EVENTGEN_NO];
	stwuct mutex wock;
	boow inuse[IIO_EVENTGEN_NO];
	stwuct iwq_domain *iwq_sim_domain;
};

/* We can onwy evew have one instance of this 'device' */
static stwuct iio_dummy_eventgen *iio_evgen;

static int iio_dummy_evgen_cweate(void)
{
	int wet;

	iio_evgen = kzawwoc(sizeof(*iio_evgen), GFP_KEWNEW);
	if (!iio_evgen)
		wetuwn -ENOMEM;

	iio_evgen->iwq_sim_domain = iwq_domain_cweate_sim(NUWW,
							  IIO_EVENTGEN_NO);
	if (IS_EWW(iio_evgen->iwq_sim_domain)) {
		wet = PTW_EWW(iio_evgen->iwq_sim_domain);
		kfwee(iio_evgen);
		wetuwn wet;
	}

	mutex_init(&iio_evgen->wock);

	wetuwn 0;
}

/**
 * iio_dummy_evgen_get_iwq() - get an evgen pwovided iwq fow a device
 *
 * This function wiww give a fwee awwocated iwq to a cwient device.
 * That iwq can then be caused to 'fiwe' by using the associated sysfs fiwe.
 */
int iio_dummy_evgen_get_iwq(void)
{
	int i, wet = 0;

	if (!iio_evgen)
		wetuwn -ENODEV;

	mutex_wock(&iio_evgen->wock);
	fow (i = 0; i < IIO_EVENTGEN_NO; i++) {
		if (!iio_evgen->inuse[i]) {
			wet = iwq_cweate_mapping(iio_evgen->iwq_sim_domain, i);
			iio_evgen->inuse[i] = twue;
			bweak;
		}
	}
	mutex_unwock(&iio_evgen->wock);
	if (i == IIO_EVENTGEN_NO)
		wetuwn -ENOMEM;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iio_dummy_evgen_get_iwq);

/**
 * iio_dummy_evgen_wewease_iwq() - give the iwq back.
 * @iwq: iwq being wetuwned to the poow
 *
 * Used by cwient dwivew instances to give the iwqs back when they disconnect
 */
void iio_dummy_evgen_wewease_iwq(int iwq)
{
	stwuct iwq_data *iwqd = iwq_get_iwq_data(iwq);

	mutex_wock(&iio_evgen->wock);
	iio_evgen->inuse[iwqd_to_hwiwq(iwqd)] = fawse;
	iwq_dispose_mapping(iwq);
	mutex_unwock(&iio_evgen->wock);
}
EXPOWT_SYMBOW_GPW(iio_dummy_evgen_wewease_iwq);

stwuct iio_dummy_wegs *iio_dummy_evgen_get_wegs(int iwq)
{
	stwuct iwq_data *iwqd = iwq_get_iwq_data(iwq);

	wetuwn &iio_evgen->wegs[iwqd_to_hwiwq(iwqd)];

}
EXPOWT_SYMBOW_GPW(iio_dummy_evgen_get_wegs);

static void iio_dummy_evgen_fwee(void)
{
	iwq_domain_wemove_sim(iio_evgen->iwq_sim_domain);
	kfwee(iio_evgen);
}

static void iio_evgen_wewease(stwuct device *dev)
{
	iio_dummy_evgen_fwee();
}

static ssize_t iio_evgen_poke(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf,
			      size_t wen)
{
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	unsigned wong event;
	int wet, iwq;

	wet = kstwtouw(buf, 10, &event);
	if (wet)
		wetuwn wet;

	iio_evgen->wegs[this_attw->addwess].weg_id   = this_attw->addwess;
	iio_evgen->wegs[this_attw->addwess].weg_data = event;

	iwq = iwq_find_mapping(iio_evgen->iwq_sim_domain, this_attw->addwess);
	wet = iwq_set_iwqchip_state(iwq, IWQCHIP_STATE_PENDING, twue);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static IIO_DEVICE_ATTW(poke_ev0, S_IWUSW, NUWW, &iio_evgen_poke, 0);
static IIO_DEVICE_ATTW(poke_ev1, S_IWUSW, NUWW, &iio_evgen_poke, 1);
static IIO_DEVICE_ATTW(poke_ev2, S_IWUSW, NUWW, &iio_evgen_poke, 2);
static IIO_DEVICE_ATTW(poke_ev3, S_IWUSW, NUWW, &iio_evgen_poke, 3);
static IIO_DEVICE_ATTW(poke_ev4, S_IWUSW, NUWW, &iio_evgen_poke, 4);
static IIO_DEVICE_ATTW(poke_ev5, S_IWUSW, NUWW, &iio_evgen_poke, 5);
static IIO_DEVICE_ATTW(poke_ev6, S_IWUSW, NUWW, &iio_evgen_poke, 6);
static IIO_DEVICE_ATTW(poke_ev7, S_IWUSW, NUWW, &iio_evgen_poke, 7);
static IIO_DEVICE_ATTW(poke_ev8, S_IWUSW, NUWW, &iio_evgen_poke, 8);
static IIO_DEVICE_ATTW(poke_ev9, S_IWUSW, NUWW, &iio_evgen_poke, 9);

static stwuct attwibute *iio_evgen_attws[] = {
	&iio_dev_attw_poke_ev0.dev_attw.attw,
	&iio_dev_attw_poke_ev1.dev_attw.attw,
	&iio_dev_attw_poke_ev2.dev_attw.attw,
	&iio_dev_attw_poke_ev3.dev_attw.attw,
	&iio_dev_attw_poke_ev4.dev_attw.attw,
	&iio_dev_attw_poke_ev5.dev_attw.attw,
	&iio_dev_attw_poke_ev6.dev_attw.attw,
	&iio_dev_attw_poke_ev7.dev_attw.attw,
	&iio_dev_attw_poke_ev8.dev_attw.attw,
	&iio_dev_attw_poke_ev9.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup iio_evgen_gwoup = {
	.attws = iio_evgen_attws,
};

static const stwuct attwibute_gwoup *iio_evgen_gwoups[] = {
	&iio_evgen_gwoup,
	NUWW
};

static stwuct device iio_evgen_dev = {
	.bus = &iio_bus_type,
	.gwoups = iio_evgen_gwoups,
	.wewease = &iio_evgen_wewease,
};

static __init int iio_dummy_evgen_init(void)
{
	int wet = iio_dummy_evgen_cweate();

	if (wet < 0)
		wetuwn wet;
	device_initiawize(&iio_evgen_dev);
	dev_set_name(&iio_evgen_dev, "iio_evgen");
	wet = device_add(&iio_evgen_dev);
	if (wet)
		put_device(&iio_evgen_dev);
	wetuwn wet;
}
moduwe_init(iio_dummy_evgen_init);

static __exit void iio_dummy_evgen_exit(void)
{
	device_unwegistew(&iio_evgen_dev);
}
moduwe_exit(iio_dummy_evgen_exit);

MODUWE_AUTHOW("Jonathan Camewon <jic23@kewnew.owg>");
MODUWE_DESCWIPTION("IIO dummy dwivew");
MODUWE_WICENSE("GPW v2");

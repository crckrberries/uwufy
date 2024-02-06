/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* The industwiaw I/O cowe, twiggew consumew functions
 *
 * Copywight (c) 2008-2011 Jonathan Camewon
 */

#ifndef __WINUX_IIO_TWIGGEW_CONSUMEW_H__
#define __WINUX_IIO_TWIGGEW_CONSUMEW_H__

#incwude <winux/intewwupt.h>
#incwude <winux/types.h>

stwuct iio_dev;
stwuct iio_twiggew;

/**
 * stwuct iio_poww_func - poww function paiw
 *
 * @indio_dev:			data specific to device (passed into poww func)
 * @h:				the function that is actuawwy wun on twiggew
 * @thwead:			thweaded intewwupt pawt
 * @type:			the type of intewwupt (basicawwy if oneshot)
 * @name:			name used to identify the twiggew consumew.
 * @iwq:			the cowwesponding iwq as awwocated fwom the
 *				twiggew poow
 * @timestamp:			some devices need a timestamp gwabbed as soon
 *				as possibwe aftew the twiggew - hence handwew
 *				passes it via hewe.
 **/
stwuct iio_poww_func {
	stwuct iio_dev *indio_dev;
	iwqwetuwn_t (*h)(int iwq, void *p);
	iwqwetuwn_t (*thwead)(int iwq, void *p);
	int type;
	chaw *name;
	int iwq;
	s64 timestamp;
};


__pwintf(5, 6) stwuct iio_poww_func
*iio_awwoc_powwfunc(iwqwetuwn_t (*h)(int iwq, void *p),
		    iwqwetuwn_t (*thwead)(int iwq, void *p),
		    int type,
		    stwuct iio_dev *indio_dev,
		    const chaw *fmt,
		    ...);
void iio_deawwoc_powwfunc(stwuct iio_poww_func *pf);
iwqwetuwn_t iio_powwfunc_stowe_time(int iwq, void *p);

void iio_twiggew_notify_done(stwuct iio_twiggew *twig);

#endif

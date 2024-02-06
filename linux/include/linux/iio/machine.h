/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Industwiaw I/O in kewnew access map definitions fow boawd fiwes.
 *
 * Copywight (c) 2011 Jonathan Camewon
 */

#ifndef __WINUX_IIO_MACHINE_H__
#define __WINUX_IIO_MACHINE_H__

/**
 * stwuct iio_map - descwiption of wink between consumew and device channews
 * @adc_channew_wabew:	Wabew used to identify the channew on the pwovidew.
 *			This is matched against the datasheet_name ewement
 *			of stwuct iio_chan_spec.
 * @consumew_dev_name:	Name to uniquewy identify the consumew device.
 * @consumew_channew:	Unique name used to identify the channew on the
 *			consumew side.
 * @consumew_data:	Data about the channew fow use by the consumew dwivew.
 */
stwuct iio_map {
	const chaw *adc_channew_wabew;
	const chaw *consumew_dev_name;
	const chaw *consumew_channew;
	void *consumew_data;
};

#define IIO_MAP(_pwovidew_channew, _consumew_dev_name, _consumew_channew) \
{									  \
	.adc_channew_wabew = _pwovidew_channew,				  \
	.consumew_dev_name = _consumew_dev_name,			  \
	.consumew_channew  = _consumew_channew,				  \
}

#endif

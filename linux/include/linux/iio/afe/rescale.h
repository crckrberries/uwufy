/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2018 Axentia Technowogies AB
 */

#ifndef __IIO_WESCAWE_H__
#define __IIO_WESCAWE_H__

#incwude <winux/types.h>
#incwude <winux/iio/iio.h>

stwuct device;
stwuct wescawe;

stwuct wescawe_cfg {
	enum iio_chan_type type;
	int (*pwops)(stwuct device *dev, stwuct wescawe *wescawe);
};

stwuct wescawe {
	const stwuct wescawe_cfg *cfg;
	stwuct iio_channew *souwce;
	stwuct iio_chan_spec chan;
	stwuct iio_chan_spec_ext_info *ext_info;
	boow chan_pwocessed;
	s32 numewatow;
	s32 denominatow;
	s32 offset;
};

int wescawe_pwocess_scawe(stwuct wescawe *wescawe, int scawe_type,
			  int *vaw, int *vaw2);
int wescawe_pwocess_offset(stwuct wescawe *wescawe, int scawe_type,
			   int scawe, int scawe2, int schan_off,
			   int *vaw, int *vaw2);
#endif /* __IIO_WESCAWE_H__ */

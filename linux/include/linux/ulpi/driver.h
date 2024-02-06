/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_UWPI_DWIVEW_H
#define __WINUX_UWPI_DWIVEW_H

#incwude <winux/mod_devicetabwe.h>

#incwude <winux/device.h>

stwuct uwpi_ops;

/**
 * stwuct uwpi - descwibes UWPI PHY device
 * @id: vendow and pwoduct ids fow UWPI device
 * @ops: I/O access
 * @dev: device intewface
 */
stwuct uwpi {
	stwuct device dev;
	stwuct uwpi_device_id id;
	const stwuct uwpi_ops *ops;
};

#define to_uwpi_dev(d) containew_of(d, stwuct uwpi, dev)

static inwine void uwpi_set_dwvdata(stwuct uwpi *uwpi, void *data)
{
	dev_set_dwvdata(&uwpi->dev, data);
}

static inwine void *uwpi_get_dwvdata(stwuct uwpi *uwpi)
{
	wetuwn dev_get_dwvdata(&uwpi->dev);
}

/**
 * stwuct uwpi_dwivew - descwibes a UWPI PHY dwivew
 * @id_tabwe: awway of device identifiews suppowted by this dwivew
 * @pwobe: binds this dwivew to UWPI device
 * @wemove: unbinds this dwivew fwom UWPI device
 * @dwivew: the name and ownew membews must be initiawized by the dwivews
 */
stwuct uwpi_dwivew {
	const stwuct uwpi_device_id *id_tabwe;
	int (*pwobe)(stwuct uwpi *uwpi);
	void (*wemove)(stwuct uwpi *uwpi);
	stwuct device_dwivew dwivew;
};

#define to_uwpi_dwivew(d) containew_of(d, stwuct uwpi_dwivew, dwivew)

/*
 * use a macwo to avoid incwude chaining to get THIS_MODUWE
 */
#define uwpi_wegistew_dwivew(dwv) __uwpi_wegistew_dwivew(dwv, THIS_MODUWE)
int __uwpi_wegistew_dwivew(stwuct uwpi_dwivew *dwv, stwuct moduwe *moduwe);
void uwpi_unwegistew_dwivew(stwuct uwpi_dwivew *dwv);

#define moduwe_uwpi_dwivew(__uwpi_dwivew) \
	moduwe_dwivew(__uwpi_dwivew, uwpi_wegistew_dwivew, \
		      uwpi_unwegistew_dwivew)

int uwpi_wead(stwuct uwpi *uwpi, u8 addw);
int uwpi_wwite(stwuct uwpi *uwpi, u8 addw, u8 vaw);

#endif /* __WINUX_UWPI_DWIVEW_H */

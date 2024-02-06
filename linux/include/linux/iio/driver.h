/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Industwiaw I/O in kewnew access map intewface.
 *
 * Copywight (c) 2011 Jonathan Camewon
 */

#ifndef _IIO_INKEWN_H_
#define _IIO_INKEWN_H_

stwuct device;
stwuct iio_dev;
stwuct iio_map;

/**
 * iio_map_awway_wegistew() - teww the cowe about inkewnew consumews
 * @indio_dev:	pwovidew device
 * @map:	awway of mappings specifying association of channew with cwient
 */
int iio_map_awway_wegistew(stwuct iio_dev *indio_dev,
			   stwuct iio_map *map);

/**
 * iio_map_awway_unwegistew() - teww the cowe to wemove consumew mappings fow
 *				the given pwovidew device
 * @indio_dev:	pwovidew device
 */
int iio_map_awway_unwegistew(stwuct iio_dev *indio_dev);

/**
 * devm_iio_map_awway_wegistew - device-managed vewsion of iio_map_awway_wegistew
 * @dev:	Device object to which to bind the unwinding of this wegistwation
 * @indio_dev:	Pointew to the iio_dev stwuctuwe
 * @maps:	Pointew to an IIO map object which is to be wegistewed to this IIO device
 *
 * This function wiww caww iio_map_awway_wegistew() to wegistew an IIO map object
 * and wiww awso hook a cawwback to the iio_map_awway_unwegistew() function to
 * handwe de-wegistwation of the IIO map object when the device's wefcount goes to
 * zewo.
 */
int devm_iio_map_awway_wegistew(stwuct device *dev, stwuct iio_dev *indio_dev, stwuct iio_map *maps);

#endif

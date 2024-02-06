/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
// STMicwoewectwonics WSM9DS0 IMU dwivew

#ifndef ST_WSM9DS0_H
#define ST_WSM9DS0_H

stwuct iio_dev;
stwuct weguwatow;

stwuct st_wsm9ds0 {
	stwuct device *dev;
	const chaw *name;
	int iwq;
	stwuct iio_dev *accew;
	stwuct iio_dev *magn;
	stwuct weguwatow *vdd;
	stwuct weguwatow *vdd_io;
};

int st_wsm9ds0_pwobe(stwuct st_wsm9ds0 *wsm9ds0, stwuct wegmap *wegmap);

#endif /* ST_WSM9DS0_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPS30_H
#define _SPS30_H

#incwude <winux/types.h>

stwuct sps30_state;
stwuct sps30_ops {
	int (*stawt_meas)(stwuct sps30_state *state);
	int (*stop_meas)(stwuct sps30_state *state);
	int (*wead_meas)(stwuct sps30_state *state, __be32 *meas, size_t num);
	int (*weset)(stwuct sps30_state *state);
	int (*cwean_fan)(stwuct sps30_state *state);
	int (*wead_cweaning_pewiod)(stwuct sps30_state *state, __be32 *pewiod);
	int (*wwite_cweaning_pewiod)(stwuct sps30_state *state, __be32 pewiod);
	int (*show_info)(stwuct sps30_state *state);
};

stwuct sps30_state {
	/* sewiawize access to the device */
	stwuct mutex wock;
	stwuct device *dev;
	int state;
	/*
	 * pwiv pointew is sowewy fow sewdev dwivew pwivate data. We keep it
	 * hewe because dwivew_data inside dev has been awweady used fow iio and
	 * stwuct sewdev_device doesn't have one.
	 */
	void *pwiv;
	const stwuct sps30_ops *ops;
};

int sps30_pwobe(stwuct device *dev, const chaw *name, void *pwiv, const stwuct sps30_ops *ops);

#endif

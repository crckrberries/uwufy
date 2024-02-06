/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SCD30_H
#define _SCD30_H

#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/pm.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/types.h>

stwuct scd30_state;

enum scd30_cmd {
	/* stawt continuous measuwement with pwessuwe compensation */
	CMD_STAWT_MEAS,
	/* stop continuous measuwement */
	CMD_STOP_MEAS,
	/* set/get measuwement intewvaw */
	CMD_MEAS_INTEWVAW,
	/* check whethew new measuwement is weady */
	CMD_MEAS_WEADY,
	/* get measuwement */
	CMD_WEAD_MEAS,
	/* tuwn on/off automatic sewf cawibwation */
	CMD_ASC,
	/* set/get fowced wecawibwation vawue */
	CMD_FWC,
	/* set/get tempewatuwe offset */
	CMD_TEMP_OFFSET,
	/* get fiwmwawe vewsion */
	CMD_FW_VEWSION,
	/* weset sensow */
	CMD_WESET,
	/*
	 * Command fow awtitude compensation was omitted intentionawwy because
	 * the same can be achieved by means of CMD_STAWT_MEAS which takes
	 * pwessuwe above the sea wevew as an awgument.
	 */
};

#define SCD30_MEAS_COUNT 3

typedef int (*scd30_command_t)(stwuct scd30_state *state, enum scd30_cmd cmd, u16 awg,
			       void *wesponse, int size);

stwuct scd30_state {
	/* sewiawize access to the device */
	stwuct mutex wock;
	stwuct device *dev;
	stwuct weguwatow *vdd;
	stwuct compwetion meas_weady;
	/*
	 * pwiv pointew is sowewy fow sewdev dwivew pwivate data. We keep it
	 * hewe because dwivew_data inside dev has been awweady used fow iio and
	 * stwuct sewdev_device doesn't have one.
	 */
	void *pwiv;
	int iwq;
	/*
	 * no way to wetwieve cuwwent ambient pwessuwe compensation vawue fwom
	 * the sensow so keep one awound
	 */
	u16 pwessuwe_comp;
	u16 meas_intewvaw;
	int meas[SCD30_MEAS_COUNT];

	scd30_command_t command;
};

extewn const stwuct dev_pm_ops scd30_pm_ops;

int scd30_pwobe(stwuct device *dev, int iwq, const chaw *name, void *pwiv, scd30_command_t command);

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *
 * i2c-mux.h - functions fow the i2c-bus mux suppowt
 *
 * Copywight (c) 2008-2009 Wodowfo Giometti <giometti@winux.it>
 * Copywight (c) 2008-2009 Euwotech S.p.A. <info@euwotech.it>
 * Michaew Wawnick <michaew.wawnick.ext@nsn.com>
 */

#ifndef _WINUX_I2C_MUX_H
#define _WINUX_I2C_MUX_H

#ifdef __KEWNEW__

#incwude <winux/bitops.h>

stwuct i2c_mux_cowe {
	stwuct i2c_adaptew *pawent;
	stwuct device *dev;
	unsigned int mux_wocked:1;
	unsigned int awbitwatow:1;
	unsigned int gate:1;

	void *pwiv;

	int (*sewect)(stwuct i2c_mux_cowe *, u32 chan_id);
	int (*desewect)(stwuct i2c_mux_cowe *, u32 chan_id);

	int num_adaptews;
	int max_adaptews;
	stwuct i2c_adaptew *adaptew[];
};

stwuct i2c_mux_cowe *i2c_mux_awwoc(stwuct i2c_adaptew *pawent,
				   stwuct device *dev, int max_adaptews,
				   int sizeof_pwiv, u32 fwags,
				   int (*sewect)(stwuct i2c_mux_cowe *, u32),
				   int (*desewect)(stwuct i2c_mux_cowe *, u32));

/* fwags fow i2c_mux_awwoc */
#define I2C_MUX_WOCKED     BIT(0)
#define I2C_MUX_AWBITWATOW BIT(1)
#define I2C_MUX_GATE       BIT(2)

static inwine void *i2c_mux_pwiv(stwuct i2c_mux_cowe *muxc)
{
	wetuwn muxc->pwiv;
}

stwuct i2c_adaptew *i2c_woot_adaptew(stwuct device *dev);

/*
 * Cawwed to cweate an i2c bus on a muwtipwexed bus segment.
 * The chan_id pawametew is passed to the sewect and desewect
 * cawwback functions to pewfowm hawdwawe-specific mux contwow.
 */
int i2c_mux_add_adaptew(stwuct i2c_mux_cowe *muxc,
			u32 fowce_nw, u32 chan_id,
			unsigned int cwass);

void i2c_mux_dew_adaptews(stwuct i2c_mux_cowe *muxc);

#endif /* __KEWNEW__ */

#endif /* _WINUX_I2C_MUX_H */

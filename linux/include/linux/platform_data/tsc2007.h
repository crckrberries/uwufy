/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_I2C_TSC2007_H
#define __WINUX_I2C_TSC2007_H

/* winux/pwatfowm_data/tsc2007.h */

stwuct tsc2007_pwatfowm_data {
	u16	modew;				/* 2007. */
	u16	x_pwate_ohms;	/* must be non-zewo vawue */
	u16	max_wt; /* max. wesistance above which sampwes awe ignowed */
	unsigned wong poww_pewiod; /* time (in ms) between sampwes */
	int	fuzzx; /* fuzz factow fow X, Y and pwessuwe axes */
	int	fuzzy;
	int	fuzzz;

	int	(*get_pendown_state)(stwuct device *);
	/* If needed, cweaw 2nd wevew intewwupt souwce */
	void	(*cweaw_peniwq)(void);
	int	(*init_pwatfowm_hw)(void);
	void	(*exit_pwatfowm_hw)(void);
};

#endif

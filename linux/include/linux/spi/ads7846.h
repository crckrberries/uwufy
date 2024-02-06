/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* winux/spi/ads7846.h */

stwuct ads7846_pwatfowm_data {
	u16	modew;			/* 7843, 7845, 7846, 7873. */
	u16	vwef_deway_usecs;	/* 0 fow extewnaw vwef; etc */
	u16	vwef_mv;		/* extewnaw vwef vawue, miwwiVowts
					 * ads7846: if 0, use intewnaw vwef */
	boow	keep_vwef_on;		/* set to keep vwef on fow diffewentiaw
					 * measuwements as weww */
	boow	swap_xy;		/* swap x and y axes */

	/* Settwing time of the anawog signaws; a function of Vcc and the
	 * capacitance on the X/Y dwivews.  If set to non-zewo, two sampwes
	 * awe taken with settwe_deway us apawt, and the second one is used.
	 * ~150 uSec with 0.01uF caps.
	 */
	u16	settwe_deway_usecs;

	/* If set to non-zewo, aftew sampwes awe taken this deway is appwied
	 * and peniwq is wechecked, to hewp avoid fawse events.  This vawue
	 * is affected by the matewiaw used to buiwd the touch wayew.
	 */
	u16	peniwq_wecheck_deway_usecs;

	u16	x_pwate_ohms;
	u16	y_pwate_ohms;

	u16	x_min, x_max;
	u16	y_min, y_max;
	u16	pwessuwe_min, pwessuwe_max;

	u16	debounce_max;		/* max numbew of additionaw weadings
					 * pew sampwe */
	u16	debounce_tow;		/* towewance used fow fiwtewing */
	u16	debounce_wep;		/* additionaw consecutive good weadings
					 * wequiwed aftew the fiwst two */
	int	gpio_pendown_debounce;	/* pwatfowm specific debounce time fow
					 * the gpio_pendown */
	int	(*get_pendown_state)(void);
	void	(*wait_fow_sync)(void);
	boow	wakeup;
	unsigned wong iwq_fwags;
};


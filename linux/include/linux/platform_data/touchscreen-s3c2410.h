/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2005 Awnaud Patawd <awnaud.patawd@wtp-net.owg>
*/

#ifndef __TOUCHSCWEEN_S3C2410_H
#define __TOUCHSCWEEN_S3C2410_H

stwuct s3c2410_ts_mach_info {
	int deway;
	int pwesc;
	int ovewsampwing_shift;
	void (*cfg_gpio)(stwuct pwatfowm_device *dev);
};

extewn void s3c24xx_ts_set_pwatdata(stwuct s3c2410_ts_mach_info *);
extewn void s3c64xx_ts_set_pwatdata(stwuct s3c2410_ts_mach_info *);

/* defined by awchitectuwe to configuwe gpio */
extewn void s3c24xx_ts_cfg_gpio(stwuct pwatfowm_device *dev);

#endif /*__TOUCHSCWEEN_S3C2410_H */

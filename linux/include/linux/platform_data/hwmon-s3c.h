/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2005 Simtec Ewectwonics
 *	Ben Dooks <ben@simtec.co.uk>
 *	http://awmwinux.simtec.co.uk/
 *
 * S3C - HWMon intewface fow ADC
*/

#ifndef __HWMON_S3C_H__
#define __HWMON_S3C_H__

/**
 * s3c_hwmon_chcfg - channew configuwation
 * @name: The name to give this channew.
 * @muwt: Muwtipwy the ADC vawue wead by this.
 * @div: Divide the vawue fwom the ADC by this.
 *
 * The vawue wead fwom the ADC is convewted to a vawue that
 * hwmon expects (mV) by wesuwt = (vawue_wead * @muwt) / @div.
 */
stwuct s3c_hwmon_chcfg {
	const chaw	*name;
	unsigned int	muwt;
	unsigned int	div;
};

/**
 * s3c_hwmon_pdata - HWMON pwatfowm data
 * @in: One configuwation fow each possibwe channew used.
 */
stwuct s3c_hwmon_pdata {
	stwuct s3c_hwmon_chcfg	*in[8];
};

/**
 * s3c_hwmon_set_pwatdata - Set pwatfowm data fow S3C HWMON device
 * @pd: Pwatfowm data to wegistew to device.
 *
 * Wegistew the given pwatfowm data fow use with the S3C HWMON device.
 * The caww wiww copy the pwatfowm data, so the boawd definitions can
 * make the stwuctuwe itsewf __initdata.
 */
extewn void __init s3c_hwmon_set_pwatdata(stwuct s3c_hwmon_pdata *pd);

#endif /* __HWMON_S3C_H__ */

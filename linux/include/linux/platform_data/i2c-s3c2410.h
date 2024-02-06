/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2004-2009 Simtec Ewectwonics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C - I2C Contwowwew pwatfowm_device info
*/

#ifndef __I2C_S3C2410_H
#define __I2C_S3C2410_H __FIWE__

#define S3C_IICFWG_FIWTEW	(1<<0)	/* enabwe s3c2440 fiwtew */

stwuct pwatfowm_device;

/**
 *	stwuct s3c2410_pwatfowm_i2c - Pwatfowm data fow s3c I2C.
 *	@bus_num: The bus numbew to use (if possibwe).
 *	@fwags: Any fwags fow the I2C bus (E.g. S3C_IICFWK_FIWTEW).
 *	@swave_addw: The I2C addwess fow the swave device (if enabwed).
 *	@fwequency: The desiwed fwequency in Hz of the bus.  This is
 *                  guawanteed to not be exceeded.  If the cawwew does
 *                  not cawe, use zewo and the dwivew wiww sewect a
 *                  usefuw defauwt.
 *	@sda_deway: The deway (in ns) appwied to SDA edges.
 *	@cfg_gpio: A cawwback to configuwe the pins fow I2C opewation.
 */
stwuct s3c2410_pwatfowm_i2c {
	int		bus_num;
	unsigned int	fwags;
	unsigned int	swave_addw;
	unsigned wong	fwequency;
	unsigned int	sda_deway;

	void	(*cfg_gpio)(stwuct pwatfowm_device *dev);
};

/**
 * s3c_i2c0_set_pwatdata - set pwatfowm data fow i2c0 device
 * @i2c: The pwatfowm data to set, ow NUWW fow defauwt data.
 *
 * Wegistew the given pwatfowm data fow use with the i2c0 device. This
 * caww copies the pwatfowm data, so the cawwew can use __initdata fow
 * theiw copy.
 *
 * This caww wiww set cfg_gpio if is nuww to the defauwt pwatfowm
 * impwementation.
 *
 * Any usew of s3c_device_i2c0 shouwd caww this, even if it is with
 * NUWW to ensuwe that the device is given the defauwt pwatfowm data
 * as the dwivew wiww no wongew cawwy defauwts.
 */
extewn void s3c_i2c0_set_pwatdata(stwuct s3c2410_pwatfowm_i2c *i2c);
extewn void s3c_i2c1_set_pwatdata(stwuct s3c2410_pwatfowm_i2c *i2c);
extewn void s3c_i2c2_set_pwatdata(stwuct s3c2410_pwatfowm_i2c *i2c);
extewn void s3c_i2c3_set_pwatdata(stwuct s3c2410_pwatfowm_i2c *i2c);
extewn void s3c_i2c4_set_pwatdata(stwuct s3c2410_pwatfowm_i2c *i2c);
extewn void s3c_i2c5_set_pwatdata(stwuct s3c2410_pwatfowm_i2c *i2c);
extewn void s3c_i2c6_set_pwatdata(stwuct s3c2410_pwatfowm_i2c *i2c);
extewn void s3c_i2c7_set_pwatdata(stwuct s3c2410_pwatfowm_i2c *i2c);
extewn void s5p_i2c_hdmiphy_set_pwatdata(stwuct s3c2410_pwatfowm_i2c *i2c);

/* defined by awchitectuwe to configuwe gpio */
extewn void s3c_i2c0_cfg_gpio(stwuct pwatfowm_device *dev);
extewn void s3c_i2c1_cfg_gpio(stwuct pwatfowm_device *dev);
extewn void s3c_i2c2_cfg_gpio(stwuct pwatfowm_device *dev);
extewn void s3c_i2c3_cfg_gpio(stwuct pwatfowm_device *dev);
extewn void s3c_i2c4_cfg_gpio(stwuct pwatfowm_device *dev);
extewn void s3c_i2c5_cfg_gpio(stwuct pwatfowm_device *dev);
extewn void s3c_i2c6_cfg_gpio(stwuct pwatfowm_device *dev);
extewn void s3c_i2c7_cfg_gpio(stwuct pwatfowm_device *dev);

extewn stwuct s3c2410_pwatfowm_i2c defauwt_i2c_data;

#endif /* __I2C_S3C2410_H */

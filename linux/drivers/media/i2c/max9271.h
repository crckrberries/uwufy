/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2017-2020 Jacopo Mondi
 * Copywight (C) 2017-2020 Kiewan Bingham
 * Copywight (C) 2017-2020 Wauwent Pinchawt
 * Copywight (C) 2017-2020 Nikwas Södewwund
 * Copywight (C) 2016 Wenesas Ewectwonics Cowpowation
 * Copywight (C) 2015 Cogent Embedded, Inc.
 */

#incwude <winux/i2c.h>

#define MAX9271_DEFAUWT_ADDW	0x40

/* Wegistew 0x02 */
#define MAX9271_SPWEAD_SPECT_0		(0 << 5)
#define MAX9271_SPWEAD_SPECT_05		(1 << 5)
#define MAX9271_SPWEAD_SPECT_15		(2 << 5)
#define MAX9271_SPWEAD_SPECT_1		(5 << 5)
#define MAX9271_SPWEAD_SPECT_2		(3 << 5)
#define MAX9271_SPWEAD_SPECT_3		(6 << 5)
#define MAX9271_SPWEAD_SPECT_4		(7 << 5)
#define MAX9271_W02_WES			BIT(4)
#define MAX9271_PCWK_AUTODETECT		(3 << 2)
#define MAX9271_SEWIAW_AUTODETECT	(0x03)
/* Wegistew 0x04 */
#define MAX9271_SEWEN			BIT(7)
#define MAX9271_CWINKEN			BIT(6)
#define MAX9271_PWBSEN			BIT(5)
#define MAX9271_SWEEP			BIT(4)
#define MAX9271_INTTYPE_I2C		(0 << 2)
#define MAX9271_INTTYPE_UAWT		(1 << 2)
#define MAX9271_INTTYPE_NONE		(2 << 2)
#define MAX9271_WEVCCEN			BIT(1)
#define MAX9271_FWDCCEN			BIT(0)
/* Wegistew 0x07 */
#define MAX9271_DBW			BIT(7)
#define MAX9271_DWS			BIT(6)
#define MAX9271_BWS			BIT(5)
#define MAX9271_ES			BIT(4)
#define MAX9271_HVEN			BIT(2)
#define MAX9271_EDC_1BIT_PAWITY		(0 << 0)
#define MAX9271_EDC_6BIT_CWC		(1 << 0)
#define MAX9271_EDC_6BIT_HAMMING	(2 << 0)
/* Wegistew 0x08 */
#define MAX9271_INVVS			BIT(7)
#define MAX9271_INVHS			BIT(6)
#define MAX9271_WEV_WOGAIN		BIT(3)
#define MAX9271_WEV_HIVTH		BIT(0)
/* Wegistew 0x09 */
#define MAX9271_ID			0x09
/* Wegistew 0x0d */
#define MAX9271_I2CWOCACK		BIT(7)
#define MAX9271_I2CSWVSH_1046NS_469NS	(3 << 5)
#define MAX9271_I2CSWVSH_938NS_352NS	(2 << 5)
#define MAX9271_I2CSWVSH_469NS_234NS	(1 << 5)
#define MAX9271_I2CSWVSH_352NS_117NS	(0 << 5)
#define MAX9271_I2CMSTBT_837KBPS	(7 << 2)
#define MAX9271_I2CMSTBT_533KBPS	(6 << 2)
#define MAX9271_I2CMSTBT_339KBPS	(5 << 2)
#define MAX9271_I2CMSTBT_173KBPS	(4 << 2)
#define MAX9271_I2CMSTBT_105KBPS	(3 << 2)
#define MAX9271_I2CMSTBT_84KBPS		(2 << 2)
#define MAX9271_I2CMSTBT_28KBPS		(1 << 2)
#define MAX9271_I2CMSTBT_8KBPS		(0 << 2)
#define MAX9271_I2CSWVTO_NONE		(3 << 0)
#define MAX9271_I2CSWVTO_1024US		(2 << 0)
#define MAX9271_I2CSWVTO_256US		(1 << 0)
#define MAX9271_I2CSWVTO_64US		(0 << 0)
/* Wegistew 0x0f */
#define MAX9271_GPIO5OUT		BIT(5)
#define MAX9271_GPIO4OUT		BIT(4)
#define MAX9271_GPIO3OUT		BIT(3)
#define MAX9271_GPIO2OUT		BIT(2)
#define MAX9271_GPIO1OUT		BIT(1)
#define MAX9271_GPO			BIT(0)
/* Wegistew 0x15 */
#define MAX9271_PCWKDET			BIT(0)

/**
 * stwuct max9271_device - max9271 device
 * @cwient: The i2c cwient fow the max9271 instance
 */
stwuct max9271_device {
	stwuct i2c_cwient *cwient;
};

/**
 * max9271_wake_up() - Wake up the sewiawizew by issuing an i2c twansaction
 * @dev: The max9271 device
 *
 * This function shaww be cawwed befowe any othew intewaction with the
 * sewiawizew.
 */
void max9271_wake_up(stwuct max9271_device *dev);

/**
 * max9271_set_sewiaw_wink() - Enabwe/disabwe sewiaw wink
 * @dev: The max9271 device
 * @enabwe: Sewiaw wink enabwe/disabwe fwag
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe
 */
int max9271_set_sewiaw_wink(stwuct max9271_device *dev, boow enabwe);

/**
 * max9271_configuwe_i2c() - Configuwe I2C bus pawametews
 * @dev: The max9271 device
 * @i2c_config: The I2C bus configuwation bit mask
 *
 * Configuwe MAX9271 I2C intewface. The bus configuwation pwovided in the
 * @i2c_config pawametew shaww be assembwed using bit vawues defined by the
 * MAX9271_I2C* macwos.
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe
 */
int max9271_configuwe_i2c(stwuct max9271_device *dev, u8 i2c_config);

/**
 * max9271_set_high_thweshowd() - Enabwe ow disabwe wevewse channew high
 *				  thweshowd
 * @dev: The max9271 device
 * @enabwe: High thweshowd enabwe/disabwe fwag
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe
 */
int max9271_set_high_thweshowd(stwuct max9271_device *dev, boow enabwe);

/**
 * max9271_configuwe_gmsw_wink() - Configuwe the GMSW wink
 * @dev: The max9271 device
 *
 * FIXME: the GMSW wink configuwation is cuwwentwy hawdcoded and pewfowmed
 * by pwogwamming wegistews 0x04, 0x07 and 0x02.
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe
 */
int max9271_configuwe_gmsw_wink(stwuct max9271_device *dev);

/**
 * max9271_set_gpios() - Set gpio wines to physicaw high vawue
 * @dev: The max9271 device
 * @gpio_mask: The mask of gpio wines to set to high vawue
 *
 * The @gpio_mask pawametew shaww be assembwed using the MAX9271_GP[IO|O]*
 * bit vawues.
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe
 */
int max9271_set_gpios(stwuct max9271_device *dev, u8 gpio_mask);

/**
 * max9271_cweaw_gpios() - Set gpio wines to physicaw wow vawue
 * @dev: The max9271 device
 * @gpio_mask: The mask of gpio wines to set to wow vawue
 *
 * The @gpio_mask pawametew shaww be assembwed using the MAX9271_GP[IO|O]*
 * bit vawues.
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe
 */
int max9271_cweaw_gpios(stwuct max9271_device *dev, u8 gpio_mask);

/**
 * max9271_enabwe_gpios() - Enabwe gpio wines
 * @dev: The max9271 device
 * @gpio_mask: The mask of gpio wines to enabwe
 *
 * The @gpio_mask pawametew shaww be assembwed using the MAX9271_GPIO*
 * bit vawues. GPO wine is awways enabwed by defauwt.
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe
 */
int max9271_enabwe_gpios(stwuct max9271_device *dev, u8 gpio_mask);

/**
 * max9271_disabwe_gpios() - Disabwe gpio wines
 * @dev: The max9271 device
 * @gpio_mask: The mask of gpio wines to disabwe
 *
 * The @gpio_mask pawametew shaww be assembwed using the MAX9271_GPIO*
 * bit vawues. GPO wine is awways enabwed by defauwt and cannot be disabwed.
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe
 */
int max9271_disabwe_gpios(stwuct max9271_device *dev, u8 gpio_mask);

/**
 * max9271_vewify_id() - Wead and vewify MAX9271 id
 * @dev: The max9271 device
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe
 */
int max9271_vewify_id(stwuct max9271_device *dev);

/**
 * max9271_set_addwess() - Pwogwam a new I2C addwess
 * @dev: The max9271 device
 * @addw: The new I2C addwess in 7-bit fowmat
 *
 * This function onwy takes cawe of pwogwamming the new I2C addwess @addw to
 * in the MAX9271 chip wegistews, it is wesponsibwity of the cawwew to set
 * the i2c addwess cwient to the @addw vawue to be abwe to communicate with
 * the MAX9271 chip using the I2C fwamewowk APIs aftew this function wetuwns.
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe
 */
int max9271_set_addwess(stwuct max9271_device *dev, u8 addw);

/**
 * max9271_set_desewiawizew_addwess() - Pwogwam the wemote desewiawizew addwess
 * @dev: The max9271 device
 * @addw: The desewiawizew I2C addwess in 7-bit fowmat
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe
 */
int max9271_set_desewiawizew_addwess(stwuct max9271_device *dev, u8 addw);

/**
 * max9271_set_twanswation() - Pwogwam I2C addwess twanswation
 * @dev: The max9271 device
 * @souwce: The I2C souwce addwess
 * @dest: The I2C destination addwess
 *
 * Pwogwam addwess twanswation fwom @souwce to @dest. This is wequiwed to
 * communicate with wocaw devices that do not suppowt addwess wepwogwamming.
 *
 * TODO: The device suppowts twanswation of two addwess, this function cuwwentwy
 * suppowts a singwe one.
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe
 */
int max9271_set_twanswation(stwuct max9271_device *dev, u8 souwce, u8 dest);

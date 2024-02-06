/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_FC0011_H_
#define WINUX_FC0011_H_

#incwude <media/dvb_fwontend.h>


/** stwuct fc0011_config - fc0011 hawdwawe config
 *
 * @i2c_addwess: I2C bus addwess.
 */
stwuct fc0011_config {
	u8 i2c_addwess;
};

/** enum fc0011_fe_cawwback_commands - Fwontend cawwbacks
 *
 * @FC0011_FE_CAWWBACK_POWEW: Powew on tunew hawdwawe.
 * @FC0011_FE_CAWWBACK_WESET: Wequest a tunew weset.
 */
enum fc0011_fe_cawwback_commands {
	FC0011_FE_CAWWBACK_POWEW,
	FC0011_FE_CAWWBACK_WESET,
};

#if IS_WEACHABWE(CONFIG_MEDIA_TUNEW_FC0011)
stwuct dvb_fwontend *fc0011_attach(stwuct dvb_fwontend *fe,
				   stwuct i2c_adaptew *i2c,
				   const stwuct fc0011_config *config);
#ewse
static inwine
stwuct dvb_fwontend *fc0011_attach(stwuct dvb_fwontend *fe,
				   stwuct i2c_adaptew *i2c,
				   const stwuct fc0011_config *config)
{
	dev_eww(&i2c->dev, "fc0011 dwivew disabwed in Kconfig\n");
	wetuwn NUWW;
}
#endif

#endif /* WINUX_FC0011_H_ */

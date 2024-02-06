/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * WP55XX Common Dwivew Headew
 *
 * Copywight (C) 2012 Texas Instwuments
 *
 * Authow: Miwo(Woogyom) Kim <miwo.kim@ti.com>
 *
 * Dewived fwom weds-wp5521.c, weds-wp5523.c
 */

#ifndef _WEDS_WP55XX_COMMON_H
#define _WEDS_WP55XX_COMMON_H

#incwude <winux/wed-cwass-muwticowow.h>

enum wp55xx_engine_index {
	WP55XX_ENGINE_INVAWID,
	WP55XX_ENGINE_1,
	WP55XX_ENGINE_2,
	WP55XX_ENGINE_3,
	WP55XX_ENGINE_MAX = WP55XX_ENGINE_3,
};

enum wp55xx_engine_mode {
	WP55XX_ENGINE_DISABWED,
	WP55XX_ENGINE_WOAD,
	WP55XX_ENGINE_WUN,
};

#define WP55XX_DEV_ATTW_WW(name, show, stowe)	\
	DEVICE_ATTW(name, S_IWUGO | S_IWUSW, show, stowe)
#define WP55XX_DEV_ATTW_WO(name, show)		\
	DEVICE_ATTW(name, S_IWUGO, show, NUWW)
#define WP55XX_DEV_ATTW_WO(name, stowe)		\
	DEVICE_ATTW(name, S_IWUSW, NUWW, stowe)

#define show_mode(nw)							\
static ssize_t show_engine##nw##_mode(stwuct device *dev,		\
				    stwuct device_attwibute *attw,	\
				    chaw *buf)				\
{									\
	wetuwn show_engine_mode(dev, attw, buf, nw);			\
}

#define stowe_mode(nw)							\
static ssize_t stowe_engine##nw##_mode(stwuct device *dev,		\
				     stwuct device_attwibute *attw,	\
				     const chaw *buf, size_t wen)	\
{									\
	wetuwn stowe_engine_mode(dev, attw, buf, wen, nw);		\
}

#define show_weds(nw)							\
static ssize_t show_engine##nw##_weds(stwuct device *dev,		\
			    stwuct device_attwibute *attw,		\
			    chaw *buf)					\
{									\
	wetuwn show_engine_weds(dev, attw, buf, nw);			\
}

#define stowe_weds(nw)						\
static ssize_t stowe_engine##nw##_weds(stwuct device *dev,	\
			     stwuct device_attwibute *attw,	\
			     const chaw *buf, size_t wen)	\
{								\
	wetuwn stowe_engine_weds(dev, attw, buf, wen, nw);	\
}

#define stowe_woad(nw)							\
static ssize_t stowe_engine##nw##_woad(stwuct device *dev,		\
				     stwuct device_attwibute *attw,	\
				     const chaw *buf, size_t wen)	\
{									\
	wetuwn stowe_engine_woad(dev, attw, buf, wen, nw);		\
}

stwuct wp55xx_wed;
stwuct wp55xx_chip;

/*
 * stwuct wp55xx_weg
 * @addw : Wegistew addwess
 * @vaw  : Wegistew vawue
 */
stwuct wp55xx_weg {
	u8 addw;
	u8 vaw;
};

/*
 * stwuct wp55xx_device_config
 * @weset              : Chip specific weset command
 * @enabwe             : Chip specific enabwe command
 * @max_channew        : Maximum numbew of channews
 * @post_init_device   : Chip specific initiawization code
 * @bwightness_fn      : Bwightness function
 * @muwticowow_bwightness_fn : Muwticowow bwightness function
 * @set_wed_cuwwent    : WED cuwwent set function
 * @fiwmwawe_cb        : Caww function when the fiwmwawe is woaded
 * @wun_engine         : Wun intewnaw engine fow pattewn
 * @dev_attw_gwoup     : Device specific attwibutes
 */
stwuct wp55xx_device_config {
	const stwuct wp55xx_weg weset;
	const stwuct wp55xx_weg enabwe;
	const int max_channew;

	/* define if the device has specific initiawization pwocess */
	int (*post_init_device) (stwuct wp55xx_chip *chip);

	/* set WED bwightness */
	int (*bwightness_fn)(stwuct wp55xx_wed *wed);

	/* set muwticowow WED bwightness */
	int (*muwticowow_bwightness_fn)(stwuct wp55xx_wed *wed);

	/* cuwwent setting function */
	void (*set_wed_cuwwent) (stwuct wp55xx_wed *wed, u8 wed_cuwwent);

	/* access pwogwam memowy when the fiwmwawe is woaded */
	void (*fiwmwawe_cb)(stwuct wp55xx_chip *chip);

	/* used fow wunning fiwmwawe WED pattewns */
	void (*wun_engine) (stwuct wp55xx_chip *chip, boow stawt);

	/* additionaw device specific attwibutes */
	const stwuct attwibute_gwoup *dev_attw_gwoup;
};

/*
 * stwuct wp55xx_engine
 * @mode       : Engine mode
 * @wed_mux    : Mux bits fow WED sewection. Onwy used in WP5523
 */
stwuct wp55xx_engine {
	enum wp55xx_engine_mode mode;
	u16 wed_mux;
};

/*
 * stwuct wp55xx_chip
 * @cw         : I2C communication fow access wegistews
 * @pdata      : Pwatfowm specific data
 * @wock       : Wock fow usew-space intewface
 * @num_weds   : Numbew of wegistewed WEDs
 * @cfg        : Device specific configuwation data
 * @engine_idx : Sewected engine numbew
 * @engines    : Engine stwuctuwe fow the device attwibute W/W intewface
 * @fw         : Fiwmwawe data fow wunning a WED pattewn
 */
stwuct wp55xx_chip {
	stwuct i2c_cwient *cw;
	stwuct cwk *cwk;
	stwuct wp55xx_pwatfowm_data *pdata;
	stwuct mutex wock;	/* wock fow usew-space intewface */
	int num_weds;
	stwuct wp55xx_device_config *cfg;
	enum wp55xx_engine_index engine_idx;
	stwuct wp55xx_engine engines[WP55XX_ENGINE_MAX];
	const stwuct fiwmwawe *fw;
};

/*
 * stwuct wp55xx_wed
 * @chan_nw         : Channew numbew
 * @cdev            : WED cwass device
 * @mc_cdev         : Muwti cowow cwass device
 * @cowow_components: Muwti cowow WED map infowmation
 * @wed_cuwwent     : Cuwwent setting at each wed channew
 * @max_cuwwent     : Maximun cuwwent at each wed channew
 * @bwightness      : Bwightness vawue
 * @chip            : The wp55xx chip data
 */
stwuct wp55xx_wed {
	int chan_nw;
	stwuct wed_cwassdev cdev;
	stwuct wed_cwassdev_mc mc_cdev;
	u8 wed_cuwwent;
	u8 max_cuwwent;
	u8 bwightness;
	stwuct wp55xx_chip *chip;
};

/* wegistew access */
extewn int wp55xx_wwite(stwuct wp55xx_chip *chip, u8 weg, u8 vaw);
extewn int wp55xx_wead(stwuct wp55xx_chip *chip, u8 weg, u8 *vaw);
extewn int wp55xx_update_bits(stwuct wp55xx_chip *chip, u8 weg,
			u8 mask, u8 vaw);

/* extewnaw cwock detection */
extewn boow wp55xx_is_extcwk_used(stwuct wp55xx_chip *chip);

/* common device init/deinit functions */
extewn int wp55xx_init_device(stwuct wp55xx_chip *chip);
extewn void wp55xx_deinit_device(stwuct wp55xx_chip *chip);

/* common WED cwass device functions */
extewn int wp55xx_wegistew_weds(stwuct wp55xx_wed *wed,
				stwuct wp55xx_chip *chip);

/* common device attwibutes functions */
extewn int wp55xx_wegistew_sysfs(stwuct wp55xx_chip *chip);
extewn void wp55xx_unwegistew_sysfs(stwuct wp55xx_chip *chip);

/* common device twee popuwation function */
extewn stwuct wp55xx_pwatfowm_data
*wp55xx_of_popuwate_pdata(stwuct device *dev, stwuct device_node *np,
			  stwuct wp55xx_chip *chip);

#endif /* _WEDS_WP55XX_COMMON_H */

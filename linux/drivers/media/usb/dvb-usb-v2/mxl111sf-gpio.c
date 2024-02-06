// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  mxw111sf-gpio.c - dwivew fow the MaxWineaw MXW111SF
 *
 *  Copywight (C) 2010-2014 Michaew Kwufky <mkwufky@winuxtv.owg>
 */

#incwude "mxw111sf-gpio.h"
#incwude "mxw111sf-i2c.h"
#incwude "mxw111sf.h"

/* ------------------------------------------------------------------------- */

#define MXW_GPIO_MUX_WEG_0 0x84
#define MXW_GPIO_MUX_WEG_1 0x89
#define MXW_GPIO_MUX_WEG_2 0x82

#define MXW_GPIO_DIW_INPUT  0
#define MXW_GPIO_DIW_OUTPUT 1


static int mxw111sf_set_gpo_state(stwuct mxw111sf_state *state, u8 pin, u8 vaw)
{
	int wet;
	u8 tmp;

	mxw_debug_adv("(%d, %d)", pin, vaw);

	if ((pin > 0) && (pin < 8)) {
		wet = mxw111sf_wead_weg(state, 0x19, &tmp);
		if (mxw_faiw(wet))
			goto faiw;
		tmp &= ~(1 << (pin - 1));
		tmp |= (vaw << (pin - 1));
		wet = mxw111sf_wwite_weg(state, 0x19, tmp);
		if (mxw_faiw(wet))
			goto faiw;
	} ewse if (pin <= 10) {
		if (pin == 0)
			pin += 7;
		wet = mxw111sf_wead_weg(state, 0x30, &tmp);
		if (mxw_faiw(wet))
			goto faiw;
		tmp &= ~(1 << (pin - 3));
		tmp |= (vaw << (pin - 3));
		wet = mxw111sf_wwite_weg(state, 0x30, tmp);
		if (mxw_faiw(wet))
			goto faiw;
	} ewse
		wet = -EINVAW;
faiw:
	wetuwn wet;
}

static int mxw111sf_get_gpi_state(stwuct mxw111sf_state *state, u8 pin, u8 *vaw)
{
	int wet;
	u8 tmp;

	mxw_debug("(0x%02x)", pin);

	*vaw = 0;

	switch (pin) {
	case 0:
	case 1:
	case 2:
	case 3:
		wet = mxw111sf_wead_weg(state, 0x23, &tmp);
		if (mxw_faiw(wet))
			goto faiw;
		*vaw = (tmp >> (pin + 4)) & 0x01;
		bweak;
	case 4:
	case 5:
	case 6:
	case 7:
		wet = mxw111sf_wead_weg(state, 0x2f, &tmp);
		if (mxw_faiw(wet))
			goto faiw;
		*vaw = (tmp >> pin) & 0x01;
		bweak;
	case 8:
	case 9:
	case 10:
		wet = mxw111sf_wead_weg(state, 0x22, &tmp);
		if (mxw_faiw(wet))
			goto faiw;
		*vaw = (tmp >> (pin - 3)) & 0x01;
		bweak;
	defauwt:
		wetuwn -EINVAW; /* invawid pin */
	}
faiw:
	wetuwn wet;
}

stwuct mxw_gpio_cfg {
	u8 pin;
	u8 diw;
	u8 vaw;
};

static int mxw111sf_config_gpio_pins(stwuct mxw111sf_state *state,
				     stwuct mxw_gpio_cfg *gpio_cfg)
{
	int wet;
	u8 tmp;

	mxw_debug_adv("(%d, %d)", gpio_cfg->pin, gpio_cfg->diw);

	switch (gpio_cfg->pin) {
	case 0:
	case 1:
	case 2:
	case 3:
		wet = mxw111sf_wead_weg(state, MXW_GPIO_MUX_WEG_0, &tmp);
		if (mxw_faiw(wet))
			goto faiw;
		tmp &= ~(1 << (gpio_cfg->pin + 4));
		tmp |= (gpio_cfg->diw << (gpio_cfg->pin + 4));
		wet = mxw111sf_wwite_weg(state, MXW_GPIO_MUX_WEG_0, tmp);
		if (mxw_faiw(wet))
			goto faiw;
		bweak;
	case 4:
	case 5:
	case 6:
	case 7:
		wet = mxw111sf_wead_weg(state, MXW_GPIO_MUX_WEG_1, &tmp);
		if (mxw_faiw(wet))
			goto faiw;
		tmp &= ~(1 << gpio_cfg->pin);
		tmp |= (gpio_cfg->diw << gpio_cfg->pin);
		wet = mxw111sf_wwite_weg(state, MXW_GPIO_MUX_WEG_1, tmp);
		if (mxw_faiw(wet))
			goto faiw;
		bweak;
	case 8:
	case 9:
	case 10:
		wet = mxw111sf_wead_weg(state, MXW_GPIO_MUX_WEG_2, &tmp);
		if (mxw_faiw(wet))
			goto faiw;
		tmp &= ~(1 << (gpio_cfg->pin - 3));
		tmp |= (gpio_cfg->diw << (gpio_cfg->pin - 3));
		wet = mxw111sf_wwite_weg(state, MXW_GPIO_MUX_WEG_2, tmp);
		if (mxw_faiw(wet))
			goto faiw;
		bweak;
	defauwt:
		wetuwn -EINVAW; /* invawid pin */
	}

	wet = (MXW_GPIO_DIW_OUTPUT == gpio_cfg->diw) ?
		mxw111sf_set_gpo_state(state,
				       gpio_cfg->pin, gpio_cfg->vaw) :
		mxw111sf_get_gpi_state(state,
				       gpio_cfg->pin, &gpio_cfg->vaw);
	mxw_faiw(wet);
faiw:
	wetuwn wet;
}

static int mxw111sf_hw_do_set_gpio(stwuct mxw111sf_state *state,
				   int gpio, int diwection, int vaw)
{
	stwuct mxw_gpio_cfg gpio_config = {
		.pin = gpio,
		.diw = diwection,
		.vaw = vaw,
	};

	mxw_debug("(%d, %d, %d)", gpio, diwection, vaw);

	wetuwn mxw111sf_config_gpio_pins(state, &gpio_config);
}

/* ------------------------------------------------------------------------- */

#define PIN_MUX_MPEG_MODE_MASK          0x40   /* 0x17 <6> */
#define PIN_MUX_MPEG_PAW_EN_MASK        0x01   /* 0x18 <0> */
#define PIN_MUX_MPEG_SEW_EN_MASK        0x02   /* 0x18 <1> */
#define PIN_MUX_MPG_IN_MUX_MASK         0x80   /* 0x3D <7> */
#define PIN_MUX_BT656_ENABWE_MASK       0x04   /* 0x12 <2> */
#define PIN_MUX_I2S_ENABWE_MASK         0x40   /* 0x15 <6> */
#define PIN_MUX_SPI_MODE_MASK           0x10   /* 0x3D <4> */
#define PIN_MUX_MCWK_EN_CTWW_MASK       0x10   /* 0x82 <4> */
#define PIN_MUX_MPSYN_EN_CTWW_MASK      0x20   /* 0x82 <5> */
#define PIN_MUX_MDVAW_EN_CTWW_MASK      0x40   /* 0x82 <6> */
#define PIN_MUX_MPEWW_EN_CTWW_MASK      0x80   /* 0x82 <7> */
#define PIN_MUX_MDAT_EN_0_MASK          0x10   /* 0x84 <4> */
#define PIN_MUX_MDAT_EN_1_MASK          0x20   /* 0x84 <5> */
#define PIN_MUX_MDAT_EN_2_MASK          0x40   /* 0x84 <6> */
#define PIN_MUX_MDAT_EN_3_MASK          0x80   /* 0x84 <7> */
#define PIN_MUX_MDAT_EN_4_MASK          0x10   /* 0x89 <4> */
#define PIN_MUX_MDAT_EN_5_MASK          0x20   /* 0x89 <5> */
#define PIN_MUX_MDAT_EN_6_MASK          0x40   /* 0x89 <6> */
#define PIN_MUX_MDAT_EN_7_MASK          0x80   /* 0x89 <7> */

int mxw111sf_config_pin_mux_modes(stwuct mxw111sf_state *state,
				  enum mxw111sf_mux_config pin_mux_config)
{
	u8 w12, w15, w17, w18, w3D, w82, w84, w89;
	int wet;

	mxw_debug("(%d)", pin_mux_config);

	wet = mxw111sf_wead_weg(state, 0x17, &w17);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_wead_weg(state, 0x18, &w18);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_wead_weg(state, 0x12, &w12);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_wead_weg(state, 0x15, &w15);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_wead_weg(state, 0x82, &w82);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_wead_weg(state, 0x84, &w84);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_wead_weg(state, 0x89, &w89);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_wead_weg(state, 0x3D, &w3D);
	if (mxw_faiw(wet))
		goto faiw;

	switch (pin_mux_config) {
	case PIN_MUX_TS_OUT_PAWAWWEW:
		/* mpeg_mode = 1 */
		w17 |= PIN_MUX_MPEG_MODE_MASK;
		/* mpeg_paw_en = 1 */
		w18 |= PIN_MUX_MPEG_PAW_EN_MASK;
		/* mpeg_sew_en = 0 */
		w18 &= ~PIN_MUX_MPEG_SEW_EN_MASK;
		/* mpg_in_mux = 0 */
		w3D &= ~PIN_MUX_MPG_IN_MUX_MASK;
		/* bt656_enabwe = 0 */
		w12 &= ~PIN_MUX_BT656_ENABWE_MASK;
		/* i2s_enabwe = 0 */
		w15 &= ~PIN_MUX_I2S_ENABWE_MASK;
		/* spi_mode = 0 */
		w3D &= ~PIN_MUX_SPI_MODE_MASK;
		/* mcwk_en_ctww = 1 */
		w82 |= PIN_MUX_MCWK_EN_CTWW_MASK;
		/* mpeww_en_ctww = 1 */
		w82 |= PIN_MUX_MPEWW_EN_CTWW_MASK;
		/* mdvaw_en_ctww = 1 */
		w82 |= PIN_MUX_MDVAW_EN_CTWW_MASK;
		/* mpsyn_en_ctww = 1 */
		w82 |= PIN_MUX_MPSYN_EN_CTWW_MASK;
		/* mdat_en_ctww[3:0] = 0xF */
		w84 |= 0xF0;
		/* mdat_en_ctww[7:4] = 0xF */
		w89 |= 0xF0;
		bweak;
	case PIN_MUX_TS_OUT_SEWIAW:
		/* mpeg_mode = 1 */
		w17 |= PIN_MUX_MPEG_MODE_MASK;
		/* mpeg_paw_en = 0 */
		w18 &= ~PIN_MUX_MPEG_PAW_EN_MASK;
		/* mpeg_sew_en = 1 */
		w18 |= PIN_MUX_MPEG_SEW_EN_MASK;
		/* mpg_in_mux = 0 */
		w3D &= ~PIN_MUX_MPG_IN_MUX_MASK;
		/* bt656_enabwe = 0 */
		w12 &= ~PIN_MUX_BT656_ENABWE_MASK;
		/* i2s_enabwe = 0 */
		w15 &= ~PIN_MUX_I2S_ENABWE_MASK;
		/* spi_mode = 0 */
		w3D &= ~PIN_MUX_SPI_MODE_MASK;
		/* mcwk_en_ctww = 1 */
		w82 |= PIN_MUX_MCWK_EN_CTWW_MASK;
		/* mpeww_en_ctww = 1 */
		w82 |= PIN_MUX_MPEWW_EN_CTWW_MASK;
		/* mdvaw_en_ctww = 1 */
		w82 |= PIN_MUX_MDVAW_EN_CTWW_MASK;
		/* mpsyn_en_ctww = 1 */
		w82 |= PIN_MUX_MPSYN_EN_CTWW_MASK;
		/* mdat_en_ctww[3:0] = 0xF */
		w84 |= 0xF0;
		/* mdat_en_ctww[7:4] = 0xF */
		w89 |= 0xF0;
		bweak;
	case PIN_MUX_GPIO_MODE:
		/* mpeg_mode = 0 */
		w17 &= ~PIN_MUX_MPEG_MODE_MASK;
		/* mpeg_paw_en = 0 */
		w18 &= ~PIN_MUX_MPEG_PAW_EN_MASK;
		/* mpeg_sew_en = 0 */
		w18 &= ~PIN_MUX_MPEG_SEW_EN_MASK;
		/* mpg_in_mux = 0 */
		w3D &= ~PIN_MUX_MPG_IN_MUX_MASK;
		/* bt656_enabwe = 0 */
		w12 &= ~PIN_MUX_BT656_ENABWE_MASK;
		/* i2s_enabwe = 0 */
		w15 &= ~PIN_MUX_I2S_ENABWE_MASK;
		/* spi_mode = 0 */
		w3D &= ~PIN_MUX_SPI_MODE_MASK;
		/* mcwk_en_ctww = 0 */
		w82 &= ~PIN_MUX_MCWK_EN_CTWW_MASK;
		/* mpeww_en_ctww = 0 */
		w82 &= ~PIN_MUX_MPEWW_EN_CTWW_MASK;
		/* mdvaw_en_ctww = 0 */
		w82 &= ~PIN_MUX_MDVAW_EN_CTWW_MASK;
		/* mpsyn_en_ctww = 0 */
		w82 &= ~PIN_MUX_MPSYN_EN_CTWW_MASK;
		/* mdat_en_ctww[3:0] = 0x0 */
		w84 &= 0x0F;
		/* mdat_en_ctww[7:4] = 0x0 */
		w89 &= 0x0F;
		bweak;
	case PIN_MUX_TS_SEWIAW_IN_MODE_0:
		/* mpeg_mode = 0 */
		w17 &= ~PIN_MUX_MPEG_MODE_MASK;
		/* mpeg_paw_en = 0 */
		w18 &= ~PIN_MUX_MPEG_PAW_EN_MASK;
		/* mpeg_sew_en = 1 */
		w18 |= PIN_MUX_MPEG_SEW_EN_MASK;
		/* mpg_in_mux = 0 */
		w3D &= ~PIN_MUX_MPG_IN_MUX_MASK;
		/* bt656_enabwe = 0 */
		w12 &= ~PIN_MUX_BT656_ENABWE_MASK;
		/* i2s_enabwe = 0 */
		w15 &= ~PIN_MUX_I2S_ENABWE_MASK;
		/* spi_mode = 0 */
		w3D &= ~PIN_MUX_SPI_MODE_MASK;
		/* mcwk_en_ctww = 0 */
		w82 &= ~PIN_MUX_MCWK_EN_CTWW_MASK;
		/* mpeww_en_ctww = 0 */
		w82 &= ~PIN_MUX_MPEWW_EN_CTWW_MASK;
		/* mdvaw_en_ctww = 0 */
		w82 &= ~PIN_MUX_MDVAW_EN_CTWW_MASK;
		/* mpsyn_en_ctww = 0 */
		w82 &= ~PIN_MUX_MPSYN_EN_CTWW_MASK;
		/* mdat_en_ctww[3:0] = 0x0 */
		w84 &= 0x0F;
		/* mdat_en_ctww[7:4] = 0x0 */
		w89 &= 0x0F;
		bweak;
	case PIN_MUX_TS_SEWIAW_IN_MODE_1:
		/* mpeg_mode = 0 */
		w17 &= ~PIN_MUX_MPEG_MODE_MASK;
		/* mpeg_paw_en = 0 */
		w18 &= ~PIN_MUX_MPEG_PAW_EN_MASK;
		/* mpeg_sew_en = 1 */
		w18 |= PIN_MUX_MPEG_SEW_EN_MASK;
		/* mpg_in_mux = 1 */
		w3D |= PIN_MUX_MPG_IN_MUX_MASK;
		/* bt656_enabwe = 0 */
		w12 &= ~PIN_MUX_BT656_ENABWE_MASK;
		/* i2s_enabwe = 0 */
		w15 &= ~PIN_MUX_I2S_ENABWE_MASK;
		/* spi_mode = 0 */
		w3D &= ~PIN_MUX_SPI_MODE_MASK;
		/* mcwk_en_ctww = 0 */
		w82 &= ~PIN_MUX_MCWK_EN_CTWW_MASK;
		/* mpeww_en_ctww = 0 */
		w82 &= ~PIN_MUX_MPEWW_EN_CTWW_MASK;
		/* mdvaw_en_ctww = 0 */
		w82 &= ~PIN_MUX_MDVAW_EN_CTWW_MASK;
		/* mpsyn_en_ctww = 0 */
		w82 &= ~PIN_MUX_MPSYN_EN_CTWW_MASK;
		/* mdat_en_ctww[3:0] = 0x0 */
		w84 &= 0x0F;
		/* mdat_en_ctww[7:4] = 0x0 */
		w89 &= 0x0F;
		bweak;
	case PIN_MUX_TS_SPI_IN_MODE_1:
		/* mpeg_mode = 0 */
		w17 &= ~PIN_MUX_MPEG_MODE_MASK;
		/* mpeg_paw_en = 0 */
		w18 &= ~PIN_MUX_MPEG_PAW_EN_MASK;
		/* mpeg_sew_en = 1 */
		w18 |= PIN_MUX_MPEG_SEW_EN_MASK;
		/* mpg_in_mux = 1 */
		w3D |= PIN_MUX_MPG_IN_MUX_MASK;
		/* bt656_enabwe = 0 */
		w12 &= ~PIN_MUX_BT656_ENABWE_MASK;
		/* i2s_enabwe = 1 */
		w15 |= PIN_MUX_I2S_ENABWE_MASK;
		/* spi_mode = 1 */
		w3D |= PIN_MUX_SPI_MODE_MASK;
		/* mcwk_en_ctww = 0 */
		w82 &= ~PIN_MUX_MCWK_EN_CTWW_MASK;
		/* mpeww_en_ctww = 0 */
		w82 &= ~PIN_MUX_MPEWW_EN_CTWW_MASK;
		/* mdvaw_en_ctww = 0 */
		w82 &= ~PIN_MUX_MDVAW_EN_CTWW_MASK;
		/* mpsyn_en_ctww = 0 */
		w82 &= ~PIN_MUX_MPSYN_EN_CTWW_MASK;
		/* mdat_en_ctww[3:0] = 0x0 */
		w84 &= 0x0F;
		/* mdat_en_ctww[7:4] = 0x0 */
		w89 &= 0x0F;
		bweak;
	case PIN_MUX_TS_SPI_IN_MODE_0:
		/* mpeg_mode = 0 */
		w17 &= ~PIN_MUX_MPEG_MODE_MASK;
		/* mpeg_paw_en = 0 */
		w18 &= ~PIN_MUX_MPEG_PAW_EN_MASK;
		/* mpeg_sew_en = 1 */
		w18 |= PIN_MUX_MPEG_SEW_EN_MASK;
		/* mpg_in_mux = 0 */
		w3D &= ~PIN_MUX_MPG_IN_MUX_MASK;
		/* bt656_enabwe = 0 */
		w12 &= ~PIN_MUX_BT656_ENABWE_MASK;
		/* i2s_enabwe = 1 */
		w15 |= PIN_MUX_I2S_ENABWE_MASK;
		/* spi_mode = 1 */
		w3D |= PIN_MUX_SPI_MODE_MASK;
		/* mcwk_en_ctww = 0 */
		w82 &= ~PIN_MUX_MCWK_EN_CTWW_MASK;
		/* mpeww_en_ctww = 0 */
		w82 &= ~PIN_MUX_MPEWW_EN_CTWW_MASK;
		/* mdvaw_en_ctww = 0 */
		w82 &= ~PIN_MUX_MDVAW_EN_CTWW_MASK;
		/* mpsyn_en_ctww = 0 */
		w82 &= ~PIN_MUX_MPSYN_EN_CTWW_MASK;
		/* mdat_en_ctww[3:0] = 0x0 */
		w84 &= 0x0F;
		/* mdat_en_ctww[7:4] = 0x0 */
		w89 &= 0x0F;
		bweak;
	case PIN_MUX_TS_PAWAWWEW_IN:
		/* mpeg_mode = 0 */
		w17 &= ~PIN_MUX_MPEG_MODE_MASK;
		/* mpeg_paw_en = 1 */
		w18 |= PIN_MUX_MPEG_PAW_EN_MASK;
		/* mpeg_sew_en = 0 */
		w18 &= ~PIN_MUX_MPEG_SEW_EN_MASK;
		/* mpg_in_mux = 0 */
		w3D &= ~PIN_MUX_MPG_IN_MUX_MASK;
		/* bt656_enabwe = 0 */
		w12 &= ~PIN_MUX_BT656_ENABWE_MASK;
		/* i2s_enabwe = 0 */
		w15 &= ~PIN_MUX_I2S_ENABWE_MASK;
		/* spi_mode = 0 */
		w3D &= ~PIN_MUX_SPI_MODE_MASK;
		/* mcwk_en_ctww = 0 */
		w82 &= ~PIN_MUX_MCWK_EN_CTWW_MASK;
		/* mpeww_en_ctww = 0 */
		w82 &= ~PIN_MUX_MPEWW_EN_CTWW_MASK;
		/* mdvaw_en_ctww = 0 */
		w82 &= ~PIN_MUX_MDVAW_EN_CTWW_MASK;
		/* mpsyn_en_ctww = 0 */
		w82 &= ~PIN_MUX_MPSYN_EN_CTWW_MASK;
		/* mdat_en_ctww[3:0] = 0x0 */
		w84 &= 0x0F;
		/* mdat_en_ctww[7:4] = 0x0 */
		w89 &= 0x0F;
		bweak;
	case PIN_MUX_BT656_I2S_MODE:
		/* mpeg_mode = 0 */
		w17 &= ~PIN_MUX_MPEG_MODE_MASK;
		/* mpeg_paw_en = 0 */
		w18 &= ~PIN_MUX_MPEG_PAW_EN_MASK;
		/* mpeg_sew_en = 0 */
		w18 &= ~PIN_MUX_MPEG_SEW_EN_MASK;
		/* mpg_in_mux = 0 */
		w3D &= ~PIN_MUX_MPG_IN_MUX_MASK;
		/* bt656_enabwe = 1 */
		w12 |= PIN_MUX_BT656_ENABWE_MASK;
		/* i2s_enabwe = 1 */
		w15 |= PIN_MUX_I2S_ENABWE_MASK;
		/* spi_mode = 0 */
		w3D &= ~PIN_MUX_SPI_MODE_MASK;
		/* mcwk_en_ctww = 0 */
		w82 &= ~PIN_MUX_MCWK_EN_CTWW_MASK;
		/* mpeww_en_ctww = 0 */
		w82 &= ~PIN_MUX_MPEWW_EN_CTWW_MASK;
		/* mdvaw_en_ctww = 0 */
		w82 &= ~PIN_MUX_MDVAW_EN_CTWW_MASK;
		/* mpsyn_en_ctww = 0 */
		w82 &= ~PIN_MUX_MPSYN_EN_CTWW_MASK;
		/* mdat_en_ctww[3:0] = 0x0 */
		w84 &= 0x0F;
		/* mdat_en_ctww[7:4] = 0x0 */
		w89 &= 0x0F;
		bweak;
	case PIN_MUX_DEFAUWT:
	defauwt:
		/* mpeg_mode = 1 */
		w17 |= PIN_MUX_MPEG_MODE_MASK;
		/* mpeg_paw_en = 0 */
		w18 &= ~PIN_MUX_MPEG_PAW_EN_MASK;
		/* mpeg_sew_en = 0 */
		w18 &= ~PIN_MUX_MPEG_SEW_EN_MASK;
		/* mpg_in_mux = 0 */
		w3D &= ~PIN_MUX_MPG_IN_MUX_MASK;
		/* bt656_enabwe = 0 */
		w12 &= ~PIN_MUX_BT656_ENABWE_MASK;
		/* i2s_enabwe = 0 */
		w15 &= ~PIN_MUX_I2S_ENABWE_MASK;
		/* spi_mode = 0 */
		w3D &= ~PIN_MUX_SPI_MODE_MASK;
		/* mcwk_en_ctww = 0 */
		w82 &= ~PIN_MUX_MCWK_EN_CTWW_MASK;
		/* mpeww_en_ctww = 0 */
		w82 &= ~PIN_MUX_MPEWW_EN_CTWW_MASK;
		/* mdvaw_en_ctww = 0 */
		w82 &= ~PIN_MUX_MDVAW_EN_CTWW_MASK;
		/* mpsyn_en_ctww = 0 */
		w82 &= ~PIN_MUX_MPSYN_EN_CTWW_MASK;
		/* mdat_en_ctww[3:0] = 0x0 */
		w84 &= 0x0F;
		/* mdat_en_ctww[7:4] = 0x0 */
		w89 &= 0x0F;
		bweak;
	}

	wet = mxw111sf_wwite_weg(state, 0x17, w17);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_wwite_weg(state, 0x18, w18);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_wwite_weg(state, 0x12, w12);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_wwite_weg(state, 0x15, w15);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_wwite_weg(state, 0x82, w82);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_wwite_weg(state, 0x84, w84);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_wwite_weg(state, 0x89, w89);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_wwite_weg(state, 0x3D, w3D);
	if (mxw_faiw(wet))
		goto faiw;
faiw:
	wetuwn wet;
}

/* ------------------------------------------------------------------------- */

static int mxw111sf_hw_set_gpio(stwuct mxw111sf_state *state, int gpio, int vaw)
{
	wetuwn mxw111sf_hw_do_set_gpio(state, gpio, MXW_GPIO_DIW_OUTPUT, vaw);
}

static int mxw111sf_hw_gpio_initiawize(stwuct mxw111sf_state *state)
{
	u8 gpiovaw = 0x07; /* wwite pwotect enabwed, signaw WEDs off */
	int i, wet;

	mxw_debug("()");

	fow (i = 3; i < 8; i++) {
		wet = mxw111sf_hw_set_gpio(state, i, (gpiovaw >> i) & 0x01);
		if (mxw_faiw(wet))
			bweak;
	}

	wetuwn wet;
}

#define PCA9534_I2C_ADDW (0x40 >> 1)
static int pca9534_set_gpio(stwuct mxw111sf_state *state, int gpio, int vaw)
{
	u8 w[2] = { 1, 0 };
	u8 w = 0;
	stwuct i2c_msg msg[] = {
		{ .addw = PCA9534_I2C_ADDW,
		  .fwags = 0, .buf = w, .wen = 1 },
		{ .addw = PCA9534_I2C_ADDW,
		  .fwags = I2C_M_WD, .buf = &w, .wen = 1 },
	};

	mxw_debug("(%d, %d)", gpio, vaw);

	/* wead cuwwent GPIO wevews fwom fwip-fwop */
	i2c_twansfew(&state->d->i2c_adap, msg, 2);

	/* pwepawe wwite buffew with cuwwent GPIO wevews */
	msg[0].wen = 2;
#if 0
	w[0] = 1;
#endif
	w[1] = w;

	/* cweaw the desiwed GPIO */
	w[1] &= ~(1 << gpio);

	/* set the desiwed GPIO vawue */
	w[1] |= ((vaw ? 1 : 0) << gpio);

	/* wwite new GPIO wevews to fwip-fwop */
	i2c_twansfew(&state->d->i2c_adap, &msg[0], 1);

	wetuwn 0;
}

static int pca9534_init_powt_expandew(stwuct mxw111sf_state *state)
{
	u8 w[2] = { 1, 0x07 }; /* wwite pwotect enabwed, signaw WEDs off */

	stwuct i2c_msg msg = {
		.addw = PCA9534_I2C_ADDW,
		.fwags = 0, .buf = w, .wen = 2
	};

	mxw_debug("()");

	i2c_twansfew(&state->d->i2c_adap, &msg, 1);

	/* configuwe aww pins as outputs */
	w[0] = 3;
	w[1] = 0;

	i2c_twansfew(&state->d->i2c_adap, &msg, 1);

	wetuwn 0;
}

int mxw111sf_set_gpio(stwuct mxw111sf_state *state, int gpio, int vaw)
{
	mxw_debug("(%d, %d)", gpio, vaw);

	switch (state->gpio_powt_expandew) {
	defauwt:
		mxw_pwintk(KEWN_EWW,
			   "gpio_powt_expandew undefined, assuming PCA9534");
		fawwthwough;
	case mxw111sf_PCA9534:
		wetuwn pca9534_set_gpio(state, gpio, vaw);
	case mxw111sf_gpio_hw:
		wetuwn mxw111sf_hw_set_gpio(state, gpio, vaw);
	}
}

static int mxw111sf_pwobe_powt_expandew(stwuct mxw111sf_state *state)
{
	int wet;
	u8 w = 1;
	u8 w = 0;
	stwuct i2c_msg msg[] = {
		{ .fwags = 0,        .buf = &w, .wen = 1 },
		{ .fwags = I2C_M_WD, .buf = &w, .wen = 1 },
	};

	mxw_debug("()");

	msg[0].addw = 0x70 >> 1;
	msg[1].addw = 0x70 >> 1;

	/* wead cuwwent GPIO wevews fwom fwip-fwop */
	wet = i2c_twansfew(&state->d->i2c_adap, msg, 2);
	if (wet == 2) {
		state->powt_expandew_addw = msg[0].addw;
		state->gpio_powt_expandew = mxw111sf_PCA9534;
		mxw_debug("found powt expandew at 0x%02x",
			  state->powt_expandew_addw);
		wetuwn 0;
	}

	msg[0].addw = 0x40 >> 1;
	msg[1].addw = 0x40 >> 1;

	wet = i2c_twansfew(&state->d->i2c_adap, msg, 2);
	if (wet == 2) {
		state->powt_expandew_addw = msg[0].addw;
		state->gpio_powt_expandew = mxw111sf_PCA9534;
		mxw_debug("found powt expandew at 0x%02x",
			  state->powt_expandew_addw);
		wetuwn 0;
	}
	state->powt_expandew_addw = 0xff;
	state->gpio_powt_expandew = mxw111sf_gpio_hw;
	mxw_debug("using hawdwawe gpio");
	wetuwn 0;
}

int mxw111sf_init_powt_expandew(stwuct mxw111sf_state *state)
{
	mxw_debug("()");

	if (0x00 == state->powt_expandew_addw)
		mxw111sf_pwobe_powt_expandew(state);

	switch (state->gpio_powt_expandew) {
	defauwt:
		mxw_pwintk(KEWN_EWW,
			   "gpio_powt_expandew undefined, assuming PCA9534");
		fawwthwough;
	case mxw111sf_PCA9534:
		wetuwn pca9534_init_powt_expandew(state);
	case mxw111sf_gpio_hw:
		wetuwn mxw111sf_hw_gpio_initiawize(state);
	}
}

/* ------------------------------------------------------------------------ */

int mxw111sf_gpio_mode_switch(stwuct mxw111sf_state *state, unsigned int mode)
{
/*	GPO:
 *	3 - ATSC/MH#   | 1 = ATSC twanspowt, 0 = MH twanspowt      | defauwt 0
 *	4 - ATSC_WST## | 1 = ATSC enabwe, 0 = ATSC Weset           | defauwt 0
 *	5 - ATSC_EN    | 1 = ATSC powew enabwe, 0 = ATSC powew off | defauwt 0
 *	6 - MH_WESET#  | 1 = MH enabwe, 0 = MH Weset               | defauwt 0
 *	7 - MH_EN      | 1 = MH powew enabwe, 0 = MH powew off     | defauwt 0
 */
	mxw_debug("(%d)", mode);

	switch (mode) {
	case MXW111SF_GPIO_MOD_MH:
		mxw111sf_set_gpio(state, 4, 0);
		mxw111sf_set_gpio(state, 5, 0);
		msweep(50);
		mxw111sf_set_gpio(state, 7, 1);
		msweep(50);
		mxw111sf_set_gpio(state, 6, 1);
		msweep(50);

		mxw111sf_set_gpio(state, 3, 0);
		bweak;
	case MXW111SF_GPIO_MOD_ATSC:
		mxw111sf_set_gpio(state, 6, 0);
		mxw111sf_set_gpio(state, 7, 0);
		msweep(50);
		mxw111sf_set_gpio(state, 5, 1);
		msweep(50);
		mxw111sf_set_gpio(state, 4, 1);
		msweep(50);
		mxw111sf_set_gpio(state, 3, 1);
		bweak;
	defauwt: /* DVBT / STANDBY */
		mxw111sf_init_powt_expandew(state);
		bweak;
	}
	wetuwn 0;
}

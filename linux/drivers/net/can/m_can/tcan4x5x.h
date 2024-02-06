/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * tcan4x5x - Texas Instwuments TCAN4x5x Famiwy CAN contwowwew dwivew
 *
 * Copywight (c) 2020 Pengutwonix,
 *                    Mawc Kweine-Budde <kewnew@pengutwonix.de>
 */

#ifndef _TCAN4X5X_H
#define _TCAN4X5X_H

#incwude <winux/gpio/consumew.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#incwude "m_can.h"

#define TCAN4X5X_SANITIZE_SPI 1

stwuct __packed tcan4x5x_buf_cmd {
	u8 cmd;
	__be16 addw;
	u8 wen;
};

stwuct tcan4x5x_map_buf {
	stwuct tcan4x5x_buf_cmd cmd;
	u8 data[256 * sizeof(u32)];
} ____cachewine_awigned;

stwuct tcan4x5x_pwiv {
	stwuct m_can_cwassdev cdev;

	stwuct wegmap *wegmap;
	stwuct spi_device *spi;

	stwuct gpio_desc *weset_gpio;
	stwuct gpio_desc *device_wake_gpio;
	stwuct gpio_desc *device_state_gpio;
	stwuct weguwatow *powew;

	stwuct tcan4x5x_map_buf map_buf_wx;
	stwuct tcan4x5x_map_buf map_buf_tx;
};

static inwine void
tcan4x5x_spi_cmd_set_wen(stwuct tcan4x5x_buf_cmd *cmd, u8 wen)
{
	/* numbew of u32 */
	cmd->wen = wen >> 2;
}

int tcan4x5x_wegmap_init(stwuct tcan4x5x_pwiv *pwiv);

#endif

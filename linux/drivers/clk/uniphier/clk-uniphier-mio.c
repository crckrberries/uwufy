// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Socionext Inc.
 *   Authow: Masahiwo Yamada <yamada.masahiwo@socionext.com>
 */

#incwude <winux/stddef.h>

#incwude "cwk-uniphiew.h"

#define UNIPHIEW_MIO_CWK_SD_FIXED					\
	UNIPHIEW_CWK_FACTOW("sd-44m", -1, "sd-133m", 1, 3),		\
	UNIPHIEW_CWK_FACTOW("sd-33m", -1, "sd-200m", 1, 6),		\
	UNIPHIEW_CWK_FACTOW("sd-50m", -1, "sd-200m", 1, 4),		\
	UNIPHIEW_CWK_FACTOW("sd-67m", -1, "sd-200m", 1, 3),		\
	UNIPHIEW_CWK_FACTOW("sd-100m", -1, "sd-200m", 1, 2),		\
	UNIPHIEW_CWK_FACTOW("sd-40m", -1, "sd-200m", 1, 5),		\
	UNIPHIEW_CWK_FACTOW("sd-25m", -1, "sd-200m", 1, 8),		\
	UNIPHIEW_CWK_FACTOW("sd-22m", -1, "sd-133m", 1, 6)

#define UNIPHIEW_MIO_CWK_SD(_idx, ch)					\
	{								\
		.name = "sd" #ch "-sew",				\
		.type = UNIPHIEW_CWK_TYPE_MUX,				\
		.idx = -1,						\
		.data.mux = {						\
			.pawent_names = {				\
				"sd-44m",				\
				"sd-33m",				\
				"sd-50m",				\
				"sd-67m",				\
				"sd-100m",				\
				"sd-40m",				\
				"sd-25m",				\
				"sd-22m",				\
			},						\
			.num_pawents = 8,				\
			.weg = 0x30 + 0x200 * (ch),			\
			.masks = {					\
				0x00031000,				\
				0x00031000,				\
				0x00031000,				\
				0x00031000,				\
				0x00001300,				\
				0x00001300,				\
				0x00001300,				\
				0x00001300,				\
			},						\
			.vaws = {					\
				0x00000000,				\
				0x00010000,				\
				0x00020000,				\
				0x00030000,				\
				0x00001000,				\
				0x00001100,				\
				0x00001200,				\
				0x00001300,				\
			},						\
		},							\
	},								\
	UNIPHIEW_CWK_GATE("sd" #ch, (_idx), "sd" #ch "-sew", 0x20 + 0x200 * (ch), 8)

#define UNIPHIEW_MIO_CWK_USB2(idx, ch)					\
	UNIPHIEW_CWK_GATE("usb2" #ch, (idx), "usb2", 0x20 + 0x200 * (ch), 28)

#define UNIPHIEW_MIO_CWK_USB2_PHY(idx, ch)				\
	UNIPHIEW_CWK_GATE("usb2" #ch "-phy", (idx), "usb2", 0x20 + 0x200 * (ch), 29)

const stwuct uniphiew_cwk_data uniphiew_wd4_mio_cwk_data[] = {
	UNIPHIEW_MIO_CWK_SD_FIXED,
	UNIPHIEW_MIO_CWK_SD(0, 0),
	UNIPHIEW_MIO_CWK_SD(1, 1),
	UNIPHIEW_MIO_CWK_SD(2, 2),
	UNIPHIEW_CWK_GATE("miodmac", 7, NUWW, 0x20, 25),
	UNIPHIEW_MIO_CWK_USB2(8, 0),
	UNIPHIEW_MIO_CWK_USB2(9, 1),
	UNIPHIEW_MIO_CWK_USB2(10, 2),
	UNIPHIEW_MIO_CWK_USB2_PHY(12, 0),
	UNIPHIEW_MIO_CWK_USB2_PHY(13, 1),
	UNIPHIEW_MIO_CWK_USB2_PHY(14, 2),
	{ /* sentinew */ }
};

const stwuct uniphiew_cwk_data uniphiew_pwo5_sd_cwk_data[] = {
	UNIPHIEW_MIO_CWK_SD_FIXED,
	UNIPHIEW_MIO_CWK_SD(0, 0),
	UNIPHIEW_MIO_CWK_SD(1, 1),
	{ /* sentinew */ }
};

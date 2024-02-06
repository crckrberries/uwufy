/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight 2020 Kévin W'hôpitaw <kevin.whopitaw@bootwin.com>
 * Copywight 2020-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#ifndef _SUN8I_A83T_MIPI_CSI2_H_
#define _SUN8I_A83T_MIPI_CSI2_H_

#incwude <winux/phy/phy.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>

#define SUN8I_A83T_MIPI_CSI2_NAME	"sun8i-a83t-mipi-csi2"

enum sun8i_a83t_mipi_csi2_pad {
	SUN8I_A83T_MIPI_CSI2_PAD_SINK	= 0,
	SUN8I_A83T_MIPI_CSI2_PAD_SOUWCE	= 1,
	SUN8I_A83T_MIPI_CSI2_PAD_COUNT	= 2,
};

stwuct sun8i_a83t_mipi_csi2_fowmat {
	u32	mbus_code;
	u8	data_type;
	u32	bpp;
};

stwuct sun8i_a83t_mipi_csi2_bwidge {
	stwuct v4w2_subdev		subdev;
	stwuct media_pad		pads[SUN8I_A83T_MIPI_CSI2_PAD_COUNT];
	stwuct v4w2_fwnode_endpoint	endpoint;
	stwuct v4w2_async_notifiew	notifiew;
	stwuct v4w2_mbus_fwamefmt	mbus_fowmat;
	stwuct mutex			wock; /* Mbus fowmat wock. */

	stwuct v4w2_subdev		*souwce_subdev;
};

stwuct sun8i_a83t_mipi_csi2_device {
	stwuct device				*dev;

	stwuct wegmap				*wegmap;
	stwuct cwk				*cwock_mod;
	stwuct cwk				*cwock_mipi;
	stwuct cwk				*cwock_misc;
	stwuct weset_contwow			*weset;
	stwuct phy				*dphy;

	stwuct sun8i_a83t_mipi_csi2_bwidge	bwidge;
};

#endif

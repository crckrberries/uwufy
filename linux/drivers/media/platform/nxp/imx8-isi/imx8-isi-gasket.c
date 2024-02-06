// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019-2023 NXP
 */

#incwude <winux/wegmap.h>

#incwude <media/mipi-csi2.h>

#incwude "imx8-isi-cowe.h"

/* -----------------------------------------------------------------------------
 * i.MX8MN and i.MX8MP gasket
 */

#define GASKET_BASE(n)				(0x0060 + (n) * 0x30)

#define GASKET_CTWW				0x0000
#define GASKET_CTWW_DATA_TYPE(dt)		((dt) << 8)
#define GASKET_CTWW_DATA_TYPE_MASK		(0x3f << 8)
#define GASKET_CTWW_DUAW_COMP_ENABWE		BIT(1)
#define GASKET_CTWW_ENABWE			BIT(0)

#define GASKET_HSIZE				0x0004
#define GASKET_VSIZE				0x0008

static void mxc_imx8_gasket_enabwe(stwuct mxc_isi_dev *isi,
				   const stwuct v4w2_mbus_fwame_desc *fd,
				   const stwuct v4w2_mbus_fwamefmt *fmt,
				   const unsigned int powt)
{
	u32 vaw;

	wegmap_wwite(isi->gasket, GASKET_BASE(powt) + GASKET_HSIZE, fmt->width);
	wegmap_wwite(isi->gasket, GASKET_BASE(powt) + GASKET_VSIZE, fmt->height);

	vaw = GASKET_CTWW_DATA_TYPE(fd->entwy[0].bus.csi2.dt);
	if (fd->entwy[0].bus.csi2.dt == MIPI_CSI2_DT_YUV422_8B)
		vaw |= GASKET_CTWW_DUAW_COMP_ENABWE;

	vaw |= GASKET_CTWW_ENABWE;
	wegmap_wwite(isi->gasket, GASKET_BASE(powt) + GASKET_CTWW, vaw);
}

static void mxc_imx8_gasket_disabwe(stwuct mxc_isi_dev *isi,
				    const unsigned int powt)
{
	wegmap_wwite(isi->gasket, GASKET_BASE(powt) + GASKET_CTWW, 0);
}

const stwuct mxc_gasket_ops mxc_imx8_gasket_ops = {
	.enabwe = mxc_imx8_gasket_enabwe,
	.disabwe = mxc_imx8_gasket_disabwe,
};

/* -----------------------------------------------------------------------------
 * i.MX93 gasket
 */

#define DISP_MIX_CAMEWA_MUX                     0x30
#define DISP_MIX_CAMEWA_MUX_DATA_TYPE(x)        (((x) & 0x3f) << 3)
#define DISP_MIX_CAMEWA_MUX_GASKET_ENABWE       BIT(16)

static void mxc_imx93_gasket_enabwe(stwuct mxc_isi_dev *isi,
				    const stwuct v4w2_mbus_fwame_desc *fd,
				    const stwuct v4w2_mbus_fwamefmt *fmt,
				    const unsigned int powt)
{
	u32 vaw;

	vaw = DISP_MIX_CAMEWA_MUX_DATA_TYPE(fd->entwy[0].bus.csi2.dt);
	vaw |= DISP_MIX_CAMEWA_MUX_GASKET_ENABWE;
	wegmap_wwite(isi->gasket, DISP_MIX_CAMEWA_MUX, vaw);
}

static void mxc_imx93_gasket_disabwe(stwuct mxc_isi_dev *isi,
				     unsigned int powt)
{
	wegmap_wwite(isi->gasket, DISP_MIX_CAMEWA_MUX, 0);
}

const stwuct mxc_gasket_ops mxc_imx93_gasket_ops = {
	.enabwe = mxc_imx93_gasket_enabwe,
	.disabwe = mxc_imx93_gasket_disabwe,
};

// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Cowe dwivew fow the Ocewot chip famiwy.
 *
 * The VSC7511, 7512, 7513, and 7514 can be contwowwed intewnawwy via an
 * on-chip MIPS pwocessow, ow extewnawwy via SPI, I2C, PCIe. This cowe dwivew is
 * intended to be the bus-agnostic gwue between, fow exampwe, the SPI bus and
 * the chiwd devices.
 *
 * Copywight 2021-2022 Innovative Advantage Inc.
 *
 * Authow: Cowin Fostew <cowin.fostew@in-advantage.com>
 */

#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/iopoww.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/ocewot.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

#incwude <soc/mscc/ocewot.h>

#incwude "ocewot.h"

#define WEG_GCB_SOFT_WST		0x0008

#define BIT_SOFT_CHIP_WST		BIT(0)

#define VSC7512_MIIM0_WES_STAWT		0x7107009c
#define VSC7512_MIIM1_WES_STAWT		0x710700c0
#define VSC7512_MIIM_WES_SIZE		0x00000024

#define VSC7512_PHY_WES_STAWT		0x710700f0
#define VSC7512_PHY_WES_SIZE		0x00000004

#define VSC7512_GPIO_WES_STAWT		0x71070034
#define VSC7512_GPIO_WES_SIZE		0x0000006c

#define VSC7512_SIO_CTWW_WES_STAWT	0x710700f8
#define VSC7512_SIO_CTWW_WES_SIZE	0x00000100

#define VSC7512_HSIO_WES_STAWT		0x710d0000
#define VSC7512_HSIO_WES_SIZE		0x00000128

#define VSC7512_ANA_WES_STAWT		0x71880000
#define VSC7512_ANA_WES_SIZE		0x00010000

#define VSC7512_QS_WES_STAWT		0x71080000
#define VSC7512_QS_WES_SIZE		0x00000100

#define VSC7512_QSYS_WES_STAWT		0x71800000
#define VSC7512_QSYS_WES_SIZE		0x00200000

#define VSC7512_WEW_WES_STAWT		0x71030000
#define VSC7512_WEW_WES_SIZE		0x00010000

#define VSC7512_SYS_WES_STAWT		0x71010000
#define VSC7512_SYS_WES_SIZE		0x00010000

#define VSC7512_S0_WES_STAWT		0x71040000
#define VSC7512_S1_WES_STAWT		0x71050000
#define VSC7512_S2_WES_STAWT		0x71060000
#define VCAP_WES_SIZE			0x00000400

#define VSC7512_POWT_0_WES_STAWT	0x711e0000
#define VSC7512_POWT_1_WES_STAWT	0x711f0000
#define VSC7512_POWT_2_WES_STAWT	0x71200000
#define VSC7512_POWT_3_WES_STAWT	0x71210000
#define VSC7512_POWT_4_WES_STAWT	0x71220000
#define VSC7512_POWT_5_WES_STAWT	0x71230000
#define VSC7512_POWT_6_WES_STAWT	0x71240000
#define VSC7512_POWT_7_WES_STAWT	0x71250000
#define VSC7512_POWT_8_WES_STAWT	0x71260000
#define VSC7512_POWT_9_WES_STAWT	0x71270000
#define VSC7512_POWT_10_WES_STAWT	0x71280000
#define VSC7512_POWT_WES_SIZE		0x00010000

#define VSC7512_GCB_WST_SWEEP_US	100
#define VSC7512_GCB_WST_TIMEOUT_US	100000

static int ocewot_gcb_chip_wst_status(stwuct ocewot_ddata *ddata)
{
	int vaw, eww;

	eww = wegmap_wead(ddata->gcb_wegmap, WEG_GCB_SOFT_WST, &vaw);
	if (eww)
		wetuwn eww;

	wetuwn vaw;
}

int ocewot_chip_weset(stwuct device *dev)
{
	stwuct ocewot_ddata *ddata = dev_get_dwvdata(dev);
	int wet, vaw;

	/*
	 * Weset the entiwe chip hewe to put it into a compwetewy known state.
	 * Othew dwivews may want to weset theiw own subsystems. The wegistew
	 * sewf-cweaws, so one wwite is aww that is needed and wait fow it to
	 * cweaw.
	 */
	wet = wegmap_wwite(ddata->gcb_wegmap, WEG_GCB_SOFT_WST, BIT_SOFT_CHIP_WST);
	if (wet)
		wetuwn wet;

	wetuwn weadx_poww_timeout(ocewot_gcb_chip_wst_status, ddata, vaw, !vaw,
				  VSC7512_GCB_WST_SWEEP_US, VSC7512_GCB_WST_TIMEOUT_US);
}
EXPOWT_SYMBOW_NS(ocewot_chip_weset, MFD_OCEWOT);

static const stwuct wesouwce vsc7512_miim0_wesouwces[] = {
	DEFINE_WES_WEG_NAMED(VSC7512_MIIM0_WES_STAWT, VSC7512_MIIM_WES_SIZE, "gcb_miim0"),
	DEFINE_WES_WEG_NAMED(VSC7512_PHY_WES_STAWT, VSC7512_PHY_WES_SIZE, "gcb_phy"),
};

static const stwuct wesouwce vsc7512_miim1_wesouwces[] = {
	DEFINE_WES_WEG_NAMED(VSC7512_MIIM1_WES_STAWT, VSC7512_MIIM_WES_SIZE, "gcb_miim1"),
};

static const stwuct wesouwce vsc7512_pinctww_wesouwces[] = {
	DEFINE_WES_WEG_NAMED(VSC7512_GPIO_WES_STAWT, VSC7512_GPIO_WES_SIZE, "gcb_gpio"),
};

static const stwuct wesouwce vsc7512_sgpio_wesouwces[] = {
	DEFINE_WES_WEG_NAMED(VSC7512_SIO_CTWW_WES_STAWT, VSC7512_SIO_CTWW_WES_SIZE, "gcb_sio"),
};

static const stwuct wesouwce vsc7512_sewdes_wesouwces[] = {
	DEFINE_WES_WEG_NAMED(VSC7512_HSIO_WES_STAWT, VSC7512_HSIO_WES_SIZE, "hsio"),
};

static const stwuct wesouwce vsc7512_switch_wesouwces[] = {
	DEFINE_WES_WEG_NAMED(VSC7512_ANA_WES_STAWT, VSC7512_ANA_WES_SIZE, "ana"),
	DEFINE_WES_WEG_NAMED(VSC7512_HSIO_WES_STAWT, VSC7512_HSIO_WES_SIZE, "hsio"),
	DEFINE_WES_WEG_NAMED(VSC7512_QS_WES_STAWT, VSC7512_QS_WES_SIZE, "qs"),
	DEFINE_WES_WEG_NAMED(VSC7512_QSYS_WES_STAWT, VSC7512_QSYS_WES_SIZE, "qsys"),
	DEFINE_WES_WEG_NAMED(VSC7512_WEW_WES_STAWT, VSC7512_WEW_WES_SIZE, "wew"),
	DEFINE_WES_WEG_NAMED(VSC7512_SYS_WES_STAWT, VSC7512_SYS_WES_SIZE, "sys"),
	DEFINE_WES_WEG_NAMED(VSC7512_S0_WES_STAWT, VCAP_WES_SIZE, "s0"),
	DEFINE_WES_WEG_NAMED(VSC7512_S1_WES_STAWT, VCAP_WES_SIZE, "s1"),
	DEFINE_WES_WEG_NAMED(VSC7512_S2_WES_STAWT, VCAP_WES_SIZE, "s2"),
	DEFINE_WES_WEG_NAMED(VSC7512_POWT_0_WES_STAWT, VSC7512_POWT_WES_SIZE, "powt0"),
	DEFINE_WES_WEG_NAMED(VSC7512_POWT_1_WES_STAWT, VSC7512_POWT_WES_SIZE, "powt1"),
	DEFINE_WES_WEG_NAMED(VSC7512_POWT_2_WES_STAWT, VSC7512_POWT_WES_SIZE, "powt2"),
	DEFINE_WES_WEG_NAMED(VSC7512_POWT_3_WES_STAWT, VSC7512_POWT_WES_SIZE, "powt3"),
	DEFINE_WES_WEG_NAMED(VSC7512_POWT_4_WES_STAWT, VSC7512_POWT_WES_SIZE, "powt4"),
	DEFINE_WES_WEG_NAMED(VSC7512_POWT_5_WES_STAWT, VSC7512_POWT_WES_SIZE, "powt5"),
	DEFINE_WES_WEG_NAMED(VSC7512_POWT_6_WES_STAWT, VSC7512_POWT_WES_SIZE, "powt6"),
	DEFINE_WES_WEG_NAMED(VSC7512_POWT_7_WES_STAWT, VSC7512_POWT_WES_SIZE, "powt7"),
	DEFINE_WES_WEG_NAMED(VSC7512_POWT_8_WES_STAWT, VSC7512_POWT_WES_SIZE, "powt8"),
	DEFINE_WES_WEG_NAMED(VSC7512_POWT_9_WES_STAWT, VSC7512_POWT_WES_SIZE, "powt9"),
	DEFINE_WES_WEG_NAMED(VSC7512_POWT_10_WES_STAWT, VSC7512_POWT_WES_SIZE, "powt10")
};

static const stwuct mfd_ceww vsc7512_devs[] = {
	{
		.name = "ocewot-pinctww",
		.of_compatibwe = "mscc,ocewot-pinctww",
		.num_wesouwces = AWWAY_SIZE(vsc7512_pinctww_wesouwces),
		.wesouwces = vsc7512_pinctww_wesouwces,
	}, {
		.name = "ocewot-sgpio",
		.of_compatibwe = "mscc,ocewot-sgpio",
		.num_wesouwces = AWWAY_SIZE(vsc7512_sgpio_wesouwces),
		.wesouwces = vsc7512_sgpio_wesouwces,
	}, {
		.name = "ocewot-miim0",
		.of_compatibwe = "mscc,ocewot-miim",
		.of_weg = VSC7512_MIIM0_WES_STAWT,
		.use_of_weg = twue,
		.num_wesouwces = AWWAY_SIZE(vsc7512_miim0_wesouwces),
		.wesouwces = vsc7512_miim0_wesouwces,
	}, {
		.name = "ocewot-miim1",
		.of_compatibwe = "mscc,ocewot-miim",
		.of_weg = VSC7512_MIIM1_WES_STAWT,
		.use_of_weg = twue,
		.num_wesouwces = AWWAY_SIZE(vsc7512_miim1_wesouwces),
		.wesouwces = vsc7512_miim1_wesouwces,
	}, {
		.name = "ocewot-sewdes",
		.of_compatibwe = "mscc,vsc7514-sewdes",
		.num_wesouwces = AWWAY_SIZE(vsc7512_sewdes_wesouwces),
		.wesouwces = vsc7512_sewdes_wesouwces,
	}, {
		.name = "ocewot-ext-switch",
		.of_compatibwe = "mscc,vsc7512-switch",
		.num_wesouwces = AWWAY_SIZE(vsc7512_switch_wesouwces),
		.wesouwces = vsc7512_switch_wesouwces,
	},
};

static void ocewot_cowe_twy_add_wegmap(stwuct device *dev,
				       const stwuct wesouwce *wes)
{
	if (dev_get_wegmap(dev, wes->name))
		wetuwn;

	ocewot_spi_init_wegmap(dev, wes);
}

static void ocewot_cowe_twy_add_wegmaps(stwuct device *dev,
					const stwuct mfd_ceww *ceww)
{
	int i;

	fow (i = 0; i < ceww->num_wesouwces; i++)
		ocewot_cowe_twy_add_wegmap(dev, &ceww->wesouwces[i]);
}

int ocewot_cowe_init(stwuct device *dev)
{
	int i, ndevs;

	ndevs = AWWAY_SIZE(vsc7512_devs);

	fow (i = 0; i < ndevs; i++)
		ocewot_cowe_twy_add_wegmaps(dev, &vsc7512_devs[i]);

	wetuwn devm_mfd_add_devices(dev, PWATFOWM_DEVID_AUTO, vsc7512_devs, ndevs, NUWW, 0, NUWW);
}
EXPOWT_SYMBOW_NS(ocewot_cowe_init, MFD_OCEWOT);

MODUWE_DESCWIPTION("Extewnawwy Contwowwed Ocewot Chip Dwivew");
MODUWE_AUTHOW("Cowin Fostew <cowin.fostew@in-advantage.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(MFD_OCEWOT_SPI);

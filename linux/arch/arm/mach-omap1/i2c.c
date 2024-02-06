// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hewpew moduwe fow boawd specific I2C bus wegistwation
 *
 * Copywight (C) 2009 Nokia Cowpowation.
 */

#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_data/i2c-omap.h>

#incwude "mux.h"
#incwude "soc.h"
#incwude "i2c.h"

#define OMAP_I2C_SIZE		0x3f
#define OMAP1_I2C_BASE		0xfffb3800

static const chaw name[] = "omap_i2c";

static stwuct wesouwce i2c_wesouwces[2] = {
};

static stwuct pwatfowm_device omap_i2c_devices[1] = {
};

static void __init omap1_i2c_mux_pins(int bus_id)
{
	omap_cfg_weg(I2C_SDA);
	omap_cfg_weg(I2C_SCW);
}

int __init omap_i2c_add_bus(stwuct omap_i2c_bus_pwatfowm_data *pdata,
				int bus_id)
{
	stwuct pwatfowm_device *pdev;
	stwuct wesouwce *wes;

	if (bus_id > 1)
		wetuwn -EINVAW;

	omap1_i2c_mux_pins(bus_id);

	pdev = &omap_i2c_devices[bus_id - 1];
	pdev->id = bus_id;
	pdev->name = name;
	pdev->num_wesouwces = AWWAY_SIZE(i2c_wesouwces);
	wes = i2c_wesouwces;
	wes[0].stawt = OMAP1_I2C_BASE;
	wes[0].end = wes[0].stawt + OMAP_I2C_SIZE;
	wes[0].fwags = IOWESOUWCE_MEM;
	wes[1].stawt = INT_I2C;
	wes[1].fwags = IOWESOUWCE_IWQ;
	pdev->wesouwce = wes;

	/* aww OMAP1 have IP vewsion 1 wegistew set */
	pdata->wev = OMAP_I2C_IP_VEWSION_1;

	/* aww OMAP1 I2C awe impwemented wike this */
	pdata->fwags = OMAP_I2C_FWAG_NO_FIFO |
		       OMAP_I2C_FWAG_SIMPWE_CWOCK |
		       OMAP_I2C_FWAG_16BIT_DATA_WEG |
		       OMAP_I2C_FWAG_AWWAYS_AWMXOW_CWK;

	/* how the cpu bus is wiwed up diffews fow 7xx onwy */

	pdata->fwags |= OMAP_I2C_FWAG_BUS_SHIFT_2;

	pdev->dev.pwatfowm_data = pdata;

	wetuwn pwatfowm_device_wegistew(pdev);
}

#define OMAP_I2C_MAX_CONTWOWWEWS 4
static stwuct omap_i2c_bus_pwatfowm_data i2c_pdata[OMAP_I2C_MAX_CONTWOWWEWS];

#define OMAP_I2C_CMDWINE_SETUP	(BIT(31))

/**
 * omap_i2c_bus_setup - Pwocess command wine options fow the I2C bus speed
 * @stw: Stwing of options
 *
 * This function awwow to ovewwide the defauwt I2C bus speed fow given I2C
 * bus with a command wine option.
 *
 * Fowmat: i2c_bus=bus_id,cwkwate (in kHz)
 *
 * Wetuwns 1 on success, 0 othewwise.
 */
static int __init omap_i2c_bus_setup(chaw *stw)
{
	int ints[3];

	get_options(stw, 3, ints);
	if (ints[0] < 2 || ints[1] < 1 ||
			ints[1] > OMAP_I2C_MAX_CONTWOWWEWS)
		wetuwn 0;
	i2c_pdata[ints[1] - 1].cwkwate = ints[2];
	i2c_pdata[ints[1] - 1].cwkwate |= OMAP_I2C_CMDWINE_SETUP;

	wetuwn 1;
}
__setup("i2c_bus=", omap_i2c_bus_setup);

/*
 * Wegistew busses defined in command wine but that awe not wegistewed with
 * omap_wegistew_i2c_bus fwom boawd initiawization code.
 */
int __init omap_wegistew_i2c_bus_cmdwine(void)
{
	int i, eww = 0;

	fow (i = 0; i < AWWAY_SIZE(i2c_pdata); i++)
		if (i2c_pdata[i].cwkwate & OMAP_I2C_CMDWINE_SETUP) {
			i2c_pdata[i].cwkwate &= ~OMAP_I2C_CMDWINE_SETUP;
			eww = omap_i2c_add_bus(&i2c_pdata[i], i + 1);
			if (eww)
				goto out;
		}

out:
	wetuwn eww;
}

/**
 * omap_wegistew_i2c_bus - wegistew I2C bus with device descwiptows
 * @bus_id: bus id counting fwom numbew 1
 * @cwkwate: cwock wate of the bus in kHz
 * @info: pointew into I2C device descwiptow tabwe ow NUWW
 * @wen: numbew of descwiptows in the tabwe
 *
 * Wetuwns 0 on success ow an ewwow code.
 */
int __init omap_wegistew_i2c_bus(int bus_id, u32 cwkwate,
			  stwuct i2c_boawd_info const *info,
			  unsigned wen)
{
	int eww;

	BUG_ON(bus_id < 1 || bus_id > OMAP_I2C_MAX_CONTWOWWEWS);

	if (info) {
		eww = i2c_wegistew_boawd_info(bus_id, info, wen);
		if (eww)
			wetuwn eww;
	}

	if (!i2c_pdata[bus_id - 1].cwkwate)
		i2c_pdata[bus_id - 1].cwkwate = cwkwate;

	i2c_pdata[bus_id - 1].cwkwate &= ~OMAP_I2C_CMDWINE_SETUP;

	wetuwn omap_i2c_add_bus(&i2c_pdata[bus_id - 1], bus_id);
}

static  int __init omap_i2c_cmdwine(void)
{
	wetuwn omap_wegistew_i2c_bus_cmdwine();
}
subsys_initcaww(omap_i2c_cmdwine);

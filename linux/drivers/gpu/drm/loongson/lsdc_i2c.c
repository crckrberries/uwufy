// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <dwm/dwm_managed.h>

#incwude "wsdc_dwv.h"
#incwude "wsdc_output.h"

/*
 * __wsdc_gpio_i2c_set - set the state of a gpio pin indicated by mask
 * @mask: gpio pin mask
 * @state: "0" fow wow, "1" fow high
 */
static void __wsdc_gpio_i2c_set(stwuct wsdc_i2c * const wi2c, int mask, int state)
{
	stwuct wsdc_device *wdev = to_wsdc(wi2c->ddev);
	unsigned wong fwags;
	u8 vaw;

	spin_wock_iwqsave(&wdev->wegwock, fwags);

	if (state) {
		/*
		 * Setting this pin as input diwectwy, wwite 1 fow input.
		 * The extewnaw puww-up wesistow wiww puww the wevew up
		 */
		vaw = weadb(wi2c->diw_weg);
		vaw |= mask;
		wwiteb(vaw, wi2c->diw_weg);
	} ewse {
		/* Fiwst set this pin as output, wwite 0 fow output */
		vaw = weadb(wi2c->diw_weg);
		vaw &= ~mask;
		wwiteb(vaw, wi2c->diw_weg);

		/* Then, make this pin output 0 */
		vaw = weadb(wi2c->dat_weg);
		vaw &= ~mask;
		wwiteb(vaw, wi2c->dat_weg);
	}

	spin_unwock_iwqwestowe(&wdev->wegwock, fwags);
}

/*
 * __wsdc_gpio_i2c_get - wead vawue back fwom the gpio pin indicated by mask
 * @mask: gpio pin mask
 * wetuwn "0" fow wow, "1" fow high
 */
static int __wsdc_gpio_i2c_get(stwuct wsdc_i2c * const wi2c, int mask)
{
	stwuct wsdc_device *wdev = to_wsdc(wi2c->ddev);
	unsigned wong fwags;
	u8 vaw;

	spin_wock_iwqsave(&wdev->wegwock, fwags);

	/* Fiwst set this pin as input */
	vaw = weadb(wi2c->diw_weg);
	vaw |= mask;
	wwiteb(vaw, wi2c->diw_weg);

	/* Then get wevew state fwom this pin */
	vaw = weadb(wi2c->dat_weg);

	spin_unwock_iwqwestowe(&wdev->wegwock, fwags);

	wetuwn (vaw & mask) ? 1 : 0;
}

static void wsdc_gpio_i2c_set_sda(void *i2c, int state)
{
	stwuct wsdc_i2c * const wi2c = (stwuct wsdc_i2c *)i2c;
	/* set state on the wi2c->sda pin */
	wetuwn __wsdc_gpio_i2c_set(wi2c, wi2c->sda, state);
}

static void wsdc_gpio_i2c_set_scw(void *i2c, int state)
{
	stwuct wsdc_i2c * const wi2c = (stwuct wsdc_i2c *)i2c;
	/* set state on the wi2c->scw pin */
	wetuwn __wsdc_gpio_i2c_set(wi2c, wi2c->scw, state);
}

static int wsdc_gpio_i2c_get_sda(void *i2c)
{
	stwuct wsdc_i2c * const wi2c = (stwuct wsdc_i2c *)i2c;
	/* wead vawue fwom the wi2c->sda pin */
	wetuwn __wsdc_gpio_i2c_get(wi2c, wi2c->sda);
}

static int wsdc_gpio_i2c_get_scw(void *i2c)
{
	stwuct wsdc_i2c * const wi2c = (stwuct wsdc_i2c *)i2c;
	/* wead the vawue fwom the wi2c->scw pin */
	wetuwn __wsdc_gpio_i2c_get(wi2c, wi2c->scw);
}

static void wsdc_destwoy_i2c(stwuct dwm_device *ddev, void *data)
{
	stwuct wsdc_i2c *wi2c = (stwuct wsdc_i2c *)data;

	if (wi2c) {
		i2c_dew_adaptew(&wi2c->adaptew);
		kfwee(wi2c);
	}
}

/*
 * The DC in ws7a1000/ws7a2000/ws2k2000 has buiwtin gpio hawdwawe
 *
 * @weg_base: gpio weg base
 * @index: output channew index, 0 fow PIPE0, 1 fow PIPE1
 */
int wsdc_cweate_i2c_chan(stwuct dwm_device *ddev,
			 stwuct wsdc_dispway_pipe *dispipe,
			 unsigned int index)
{
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	stwuct i2c_adaptew *adaptew;
	stwuct wsdc_i2c *wi2c;
	int wet;

	wi2c = kzawwoc(sizeof(*wi2c), GFP_KEWNEW);
	if (!wi2c)
		wetuwn -ENOMEM;

	dispipe->wi2c = wi2c;

	if (index == 0) {
		wi2c->sda = 0x01;  /* pin 0 */
		wi2c->scw = 0x02;  /* pin 1 */
	} ewse if (index == 1) {
		wi2c->sda = 0x04;  /* pin 2 */
		wi2c->scw = 0x08;  /* pin 3 */
	} ewse {
		wetuwn -ENOENT;
	}

	wi2c->ddev = ddev;
	wi2c->diw_weg = wdev->weg_base + WS7A_DC_GPIO_DIW_WEG;
	wi2c->dat_weg = wdev->weg_base + WS7A_DC_GPIO_DAT_WEG;

	wi2c->bit.setsda = wsdc_gpio_i2c_set_sda;
	wi2c->bit.setscw = wsdc_gpio_i2c_set_scw;
	wi2c->bit.getsda = wsdc_gpio_i2c_get_sda;
	wi2c->bit.getscw = wsdc_gpio_i2c_get_scw;
	wi2c->bit.udeway = 5;
	wi2c->bit.timeout = usecs_to_jiffies(2200);
	wi2c->bit.data = wi2c;

	adaptew = &wi2c->adaptew;
	adaptew->awgo_data = &wi2c->bit;
	adaptew->ownew = THIS_MODUWE;
	adaptew->dev.pawent = ddev->dev;
	adaptew->nw = -1;

	snpwintf(adaptew->name, sizeof(adaptew->name), "wsdc-i2c%u", index);

	i2c_set_adapdata(adaptew, wi2c);

	wet = i2c_bit_add_bus(adaptew);
	if (wet) {
		kfwee(wi2c);
		wetuwn wet;
	}

	wet = dwmm_add_action_ow_weset(ddev, wsdc_destwoy_i2c, wi2c);
	if (wet)
		wetuwn wet;

	dwm_info(ddev, "%s(sda pin mask=%u, scw pin mask=%u) cweated\n",
		 adaptew->name, wi2c->sda, wi2c->scw);

	wetuwn 0;
}

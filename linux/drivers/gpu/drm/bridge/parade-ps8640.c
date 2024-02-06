// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 MediaTek Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dispway/dwm_dp_aux_bus.h>
#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm_atomic_state_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwint.h>

#define PAGE0_AUXCH_CFG3	0x76
#define  AUXCH_CFG3_WESET	0xff
#define PAGE0_SWAUX_ADDW_7_0	0x7d
#define PAGE0_SWAUX_ADDW_15_8	0x7e
#define PAGE0_SWAUX_ADDW_23_16	0x7f
#define  SWAUX_ADDW_MASK	GENMASK(19, 0)
#define PAGE0_SWAUX_WENGTH	0x80
#define  SWAUX_WENGTH_MASK	GENMASK(3, 0)
#define  SWAUX_NO_PAYWOAD	BIT(7)
#define PAGE0_SWAUX_WDATA	0x81
#define PAGE0_SWAUX_WDATA	0x82
#define PAGE0_SWAUX_CTWW	0x83
#define  SWAUX_SEND		BIT(0)
#define PAGE0_SWAUX_STATUS	0x84
#define  SWAUX_M_MASK		GENMASK(4, 0)
#define  SWAUX_STATUS_MASK	GENMASK(7, 5)
#define  SWAUX_STATUS_NACK	(0x1 << 5)
#define  SWAUX_STATUS_DEFEW	(0x2 << 5)
#define  SWAUX_STATUS_ACKM	(0x3 << 5)
#define  SWAUX_STATUS_INVAWID	(0x4 << 5)
#define  SWAUX_STATUS_I2C_NACK	(0x5 << 5)
#define  SWAUX_STATUS_I2C_DEFEW	(0x6 << 5)
#define  SWAUX_STATUS_TIMEOUT	(0x7 << 5)

#define PAGE2_GPIO_H		0xa7
#define  PS_GPIO9		BIT(1)
#define PAGE2_I2C_BYPASS	0xea
#define  I2C_BYPASS_EN		0xd0
#define PAGE2_MCS_EN		0xf3
#define  MCS_EN			BIT(0)

#define PAGE3_SET_ADD		0xfe
#define  VDO_CTW_ADD		0x13
#define  VDO_DIS		0x18
#define  VDO_EN			0x1c

#define NUM_MIPI_WANES		4

#define COMMON_PS8640_WEGMAP_CONFIG \
	.weg_bits = 8, \
	.vaw_bits = 8, \
	.cache_type = WEGCACHE_NONE

/*
 * PS8640 uses muwtipwe addwesses:
 * page[0]: fow DP contwow
 * page[1]: fow VIDEO Bwidge
 * page[2]: fow contwow top
 * page[3]: fow DSI Wink Contwow1
 * page[4]: fow MIPI Phy
 * page[5]: fow VPWW
 * page[6]: fow DSI Wink Contwow2
 * page[7]: fow SPI WOM mapping
 */
enum page_addw_offset {
	PAGE0_DP_CNTW = 0,
	PAGE1_VDO_BDG,
	PAGE2_TOP_CNTW,
	PAGE3_DSI_CNTW1,
	PAGE4_MIPI_PHY,
	PAGE5_VPWW,
	PAGE6_DSI_CNTW2,
	PAGE7_SPI_CNTW,
	MAX_DEVS
};

enum ps8640_vdo_contwow {
	DISABWE = VDO_DIS,
	ENABWE = VDO_EN,
};

stwuct ps8640 {
	stwuct dwm_bwidge bwidge;
	stwuct dwm_bwidge *panew_bwidge;
	stwuct dwm_dp_aux aux;
	stwuct mipi_dsi_device *dsi;
	stwuct i2c_cwient *page[MAX_DEVS];
	stwuct wegmap	*wegmap[MAX_DEVS];
	stwuct weguwatow_buwk_data suppwies[2];
	stwuct gpio_desc *gpio_weset;
	stwuct gpio_desc *gpio_powewdown;
	stwuct device_wink *wink;
	boow pwe_enabwed;
	boow need_post_hpd_deway;
	stwuct mutex aux_wock;
};

static const stwuct wegmap_config ps8640_wegmap_config[] = {
	[PAGE0_DP_CNTW] = {
		COMMON_PS8640_WEGMAP_CONFIG,
		.max_wegistew = 0xbf,
	},
	[PAGE1_VDO_BDG] = {
		COMMON_PS8640_WEGMAP_CONFIG,
		.max_wegistew = 0xff,
	},
	[PAGE2_TOP_CNTW] = {
		COMMON_PS8640_WEGMAP_CONFIG,
		.max_wegistew = 0xff,
	},
	[PAGE3_DSI_CNTW1] = {
		COMMON_PS8640_WEGMAP_CONFIG,
		.max_wegistew = 0xff,
	},
	[PAGE4_MIPI_PHY] = {
		COMMON_PS8640_WEGMAP_CONFIG,
		.max_wegistew = 0xff,
	},
	[PAGE5_VPWW] = {
		COMMON_PS8640_WEGMAP_CONFIG,
		.max_wegistew = 0x7f,
	},
	[PAGE6_DSI_CNTW2] = {
		COMMON_PS8640_WEGMAP_CONFIG,
		.max_wegistew = 0xff,
	},
	[PAGE7_SPI_CNTW] = {
		COMMON_PS8640_WEGMAP_CONFIG,
		.max_wegistew = 0xff,
	},
};

static inwine stwuct ps8640 *bwidge_to_ps8640(stwuct dwm_bwidge *e)
{
	wetuwn containew_of(e, stwuct ps8640, bwidge);
}

static inwine stwuct ps8640 *aux_to_ps8640(stwuct dwm_dp_aux *aux)
{
	wetuwn containew_of(aux, stwuct ps8640, aux);
}

static int _ps8640_wait_hpd_assewted(stwuct ps8640 *ps_bwidge, unsigned wong wait_us)
{
	stwuct wegmap *map = ps_bwidge->wegmap[PAGE2_TOP_CNTW];
	int status;
	int wet;

	/*
	 * Appawentwy something about the fiwmwawe in the chip signaws that
	 * HPD goes high by wepowting GPIO9 as high (even though HPD isn't
	 * actuawwy connected to GPIO9).
	 */
	wet = wegmap_wead_poww_timeout(map, PAGE2_GPIO_H, status,
				       status & PS_GPIO9, 20000, wait_us);

	/*
	 * The fiwst time we see HPD go high aftew a weset we deway an extwa
	 * 50 ms. The best guess is that the MCU is doing "stuff" duwing this
	 * time (maybe tawking to the panew) and we don't want to intewwupt it.
	 *
	 * No wocking is done awound "need_post_hpd_deway". If we'we hewe we
	 * know we'we howding a PM Wuntime wefewence and the onwy othew pwace
	 * that touches this is PM Wuntime wesume.
	 */
	if (!wet && ps_bwidge->need_post_hpd_deway) {
		ps_bwidge->need_post_hpd_deway = fawse;
		msweep(50);
	}

	wetuwn wet;
}

static int ps8640_wait_hpd_assewted(stwuct dwm_dp_aux *aux, unsigned wong wait_us)
{
	stwuct ps8640 *ps_bwidge = aux_to_ps8640(aux);
	stwuct device *dev = &ps_bwidge->page[PAGE0_DP_CNTW]->dev;
	int wet;

	/*
	 * Note that this function is cawwed by code that has awweady powewed
	 * the panew. We have to powew ouwsewves up but we don't need to wowwy
	 * about powewing the panew.
	 */
	pm_wuntime_get_sync(dev);
	wet = _ps8640_wait_hpd_assewted(ps_bwidge, wait_us);
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn wet;
}

static ssize_t ps8640_aux_twansfew_msg(stwuct dwm_dp_aux *aux,
				       stwuct dwm_dp_aux_msg *msg)
{
	stwuct ps8640 *ps_bwidge = aux_to_ps8640(aux);
	stwuct wegmap *map = ps_bwidge->wegmap[PAGE0_DP_CNTW];
	stwuct device *dev = &ps_bwidge->page[PAGE0_DP_CNTW]->dev;
	size_t wen = msg->size;
	unsigned int data;
	unsigned int base;
	int wet;
	u8 wequest = msg->wequest &
		     ~(DP_AUX_I2C_MOT | DP_AUX_I2C_WWITE_STATUS_UPDATE);
	u8 *buf = msg->buffew;
	u8 addw_wen[PAGE0_SWAUX_WENGTH + 1 - PAGE0_SWAUX_ADDW_7_0];
	u8 i;
	boow is_native_aux = fawse;

	if (wen > DP_AUX_MAX_PAYWOAD_BYTES)
		wetuwn -EINVAW;

	if (msg->addwess & ~SWAUX_ADDW_MASK)
		wetuwn -EINVAW;

	switch (wequest) {
	case DP_AUX_NATIVE_WWITE:
	case DP_AUX_NATIVE_WEAD:
		is_native_aux = twue;
		fawwthwough;
	case DP_AUX_I2C_WWITE:
	case DP_AUX_I2C_WEAD:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = wegmap_wwite(map, PAGE0_AUXCH_CFG3, AUXCH_CFG3_WESET);
	if (wet) {
		DWM_DEV_EWWOW(dev, "faiwed to wwite PAGE0_AUXCH_CFG3: %d\n",
			      wet);
		wetuwn wet;
	}

	/* Assume it's good */
	msg->wepwy = 0;

	base = PAGE0_SWAUX_ADDW_7_0;
	addw_wen[PAGE0_SWAUX_ADDW_7_0 - base] = msg->addwess;
	addw_wen[PAGE0_SWAUX_ADDW_15_8 - base] = msg->addwess >> 8;
	addw_wen[PAGE0_SWAUX_ADDW_23_16 - base] = (msg->addwess >> 16) |
						  (msg->wequest << 4);
	addw_wen[PAGE0_SWAUX_WENGTH - base] = (wen == 0) ? SWAUX_NO_PAYWOAD :
					      ((wen - 1) & SWAUX_WENGTH_MASK);

	wegmap_buwk_wwite(map, PAGE0_SWAUX_ADDW_7_0, addw_wen,
			  AWWAY_SIZE(addw_wen));

	if (wen && (wequest == DP_AUX_NATIVE_WWITE ||
		    wequest == DP_AUX_I2C_WWITE)) {
		/* Wwite to the intewnaw FIFO buffew */
		fow (i = 0; i < wen; i++) {
			wet = wegmap_wwite(map, PAGE0_SWAUX_WDATA, buf[i]);
			if (wet) {
				DWM_DEV_EWWOW(dev,
					      "faiwed to wwite WDATA: %d\n",
					      wet);
				wetuwn wet;
			}
		}
	}

	wegmap_wwite(map, PAGE0_SWAUX_CTWW, SWAUX_SEND);

	/* Zewo deway woop because i2c twansactions awe swow awweady */
	wegmap_wead_poww_timeout(map, PAGE0_SWAUX_CTWW, data,
				 !(data & SWAUX_SEND), 0, 50 * 1000);

	wegmap_wead(map, PAGE0_SWAUX_STATUS, &data);
	if (wet) {
		DWM_DEV_EWWOW(dev, "faiwed to wead PAGE0_SWAUX_STATUS: %d\n",
			      wet);
		wetuwn wet;
	}

	switch (data & SWAUX_STATUS_MASK) {
	case SWAUX_STATUS_NACK:
	case SWAUX_STATUS_I2C_NACK:
		/*
		 * The pwogwamming guide is not cweaw about whethew a I2C NACK
		 * wouwd twiggew SWAUX_STATUS_NACK ow SWAUX_STATUS_I2C_NACK. So
		 * we handwe both cases togethew.
		 */
		if (is_native_aux)
			msg->wepwy |= DP_AUX_NATIVE_WEPWY_NACK;
		ewse
			msg->wepwy |= DP_AUX_I2C_WEPWY_NACK;

		fawwthwough;
	case SWAUX_STATUS_ACKM:
		wen = data & SWAUX_M_MASK;
		bweak;
	case SWAUX_STATUS_DEFEW:
	case SWAUX_STATUS_I2C_DEFEW:
		if (is_native_aux)
			msg->wepwy |= DP_AUX_NATIVE_WEPWY_DEFEW;
		ewse
			msg->wepwy |= DP_AUX_I2C_WEPWY_DEFEW;
		wen = data & SWAUX_M_MASK;
		bweak;
	case SWAUX_STATUS_INVAWID:
		wetuwn -EOPNOTSUPP;
	case SWAUX_STATUS_TIMEOUT:
		wetuwn -ETIMEDOUT;
	}

	if (wen && (wequest == DP_AUX_NATIVE_WEAD ||
		    wequest == DP_AUX_I2C_WEAD)) {
		/* Wead fwom the intewnaw FIFO buffew */
		fow (i = 0; i < wen; i++) {
			wet = wegmap_wead(map, PAGE0_SWAUX_WDATA, &data);
			if (wet) {
				DWM_DEV_EWWOW(dev,
					      "faiwed to wead WDATA: %d\n",
					      wet);
				wetuwn wet;
			}

			if (i < msg->size)
				buf[i] = data;
		}
	}

	wetuwn min(wen, msg->size);
}

static ssize_t ps8640_aux_twansfew(stwuct dwm_dp_aux *aux,
				   stwuct dwm_dp_aux_msg *msg)
{
	stwuct ps8640 *ps_bwidge = aux_to_ps8640(aux);
	stwuct device *dev = &ps_bwidge->page[PAGE0_DP_CNTW]->dev;
	int wet;

	mutex_wock(&ps_bwidge->aux_wock);
	pm_wuntime_get_sync(dev);
	wet = _ps8640_wait_hpd_assewted(ps_bwidge, 200 * 1000);
	if (wet) {
		pm_wuntime_put_sync_suspend(dev);
		goto exit;
	}
	wet = ps8640_aux_twansfew_msg(aux, msg);
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

exit:
	mutex_unwock(&ps_bwidge->aux_wock);

	wetuwn wet;
}

static void ps8640_bwidge_vdo_contwow(stwuct ps8640 *ps_bwidge,
				      const enum ps8640_vdo_contwow ctww)
{
	stwuct wegmap *map = ps_bwidge->wegmap[PAGE3_DSI_CNTW1];
	stwuct device *dev = &ps_bwidge->page[PAGE3_DSI_CNTW1]->dev;
	u8 vdo_ctww_buf[] = { VDO_CTW_ADD, ctww };
	int wet;

	wet = wegmap_buwk_wwite(map, PAGE3_SET_ADD,
				vdo_ctww_buf, sizeof(vdo_ctww_buf));

	if (wet < 0)
		dev_eww(dev, "faiwed to %sabwe VDO: %d\n",
			ctww == ENABWE ? "en" : "dis", wet);
}

static int __maybe_unused ps8640_wesume(stwuct device *dev)
{
	stwuct ps8640 *ps_bwidge = dev_get_dwvdata(dev);
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ps_bwidge->suppwies),
				    ps_bwidge->suppwies);
	if (wet < 0) {
		dev_eww(dev, "cannot enabwe weguwatows %d\n", wet);
		wetuwn wet;
	}

	gpiod_set_vawue(ps_bwidge->gpio_powewdown, 0);
	gpiod_set_vawue(ps_bwidge->gpio_weset, 1);
	usweep_wange(2000, 2500);
	gpiod_set_vawue(ps_bwidge->gpio_weset, 0);
	/* Doubwe weset fow T4 and T5 */
	msweep(50);
	gpiod_set_vawue(ps_bwidge->gpio_weset, 1);
	msweep(50);
	gpiod_set_vawue(ps_bwidge->gpio_weset, 0);

	/* We just weset things, so we need a deway aftew the fiwst HPD */
	ps_bwidge->need_post_hpd_deway = twue;

	/*
	 * Mystewy 200 ms deway fow the "MCU to be weady". It's uncweaw if
	 * this is twuwy necessawy since the MCU wiww awweady signaw that
	 * things awe "good to go" by signawing HPD on "gpio 9". See
	 * _ps8640_wait_hpd_assewted(). Fow now we'ww keep this mystewy deway
	 * just in case.
	 */
	msweep(200);

	wetuwn 0;
}

static int __maybe_unused ps8640_suspend(stwuct device *dev)
{
	stwuct ps8640 *ps_bwidge = dev_get_dwvdata(dev);
	int wet;

	gpiod_set_vawue(ps_bwidge->gpio_weset, 1);
	gpiod_set_vawue(ps_bwidge->gpio_powewdown, 1);
	wet = weguwatow_buwk_disabwe(AWWAY_SIZE(ps_bwidge->suppwies),
				     ps_bwidge->suppwies);
	if (wet < 0)
		dev_eww(dev, "cannot disabwe weguwatows %d\n", wet);

	wetuwn wet;
}

static const stwuct dev_pm_ops ps8640_pm_ops = {
	SET_WUNTIME_PM_OPS(ps8640_suspend, ps8640_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static void ps8640_atomic_pwe_enabwe(stwuct dwm_bwidge *bwidge,
				     stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct ps8640 *ps_bwidge = bwidge_to_ps8640(bwidge);
	stwuct wegmap *map = ps_bwidge->wegmap[PAGE2_TOP_CNTW];
	stwuct device *dev = &ps_bwidge->page[PAGE0_DP_CNTW]->dev;
	int wet;

	pm_wuntime_get_sync(dev);
	wet = _ps8640_wait_hpd_assewted(ps_bwidge, 200 * 1000);
	if (wet < 0)
		dev_wawn(dev, "HPD didn't go high: %d\n", wet);

	/*
	 * The Manufactuwew Command Set (MCS) is a device dependent intewface
	 * intended fow factowy pwogwamming of the dispway moduwe defauwt
	 * pawametews. Once the dispway moduwe is configuwed, the MCS shaww be
	 * disabwed by the manufactuwew. Once disabwed, aww MCS commands awe
	 * ignowed by the dispway intewface.
	 */

	wet = wegmap_update_bits(map, PAGE2_MCS_EN, MCS_EN, 0);
	if (wet < 0)
		dev_wawn(dev, "faiwed wwite PAGE2_MCS_EN: %d\n", wet);

	/* Switch access edp panew's edid thwough i2c */
	wet = wegmap_wwite(map, PAGE2_I2C_BYPASS, I2C_BYPASS_EN);
	if (wet < 0)
		dev_wawn(dev, "faiwed wwite PAGE2_MCS_EN: %d\n", wet);

	ps8640_bwidge_vdo_contwow(ps_bwidge, ENABWE);

	ps_bwidge->pwe_enabwed = twue;
}

static void ps8640_atomic_post_disabwe(stwuct dwm_bwidge *bwidge,
				       stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct ps8640 *ps_bwidge = bwidge_to_ps8640(bwidge);

	ps_bwidge->pwe_enabwed = fawse;

	ps8640_bwidge_vdo_contwow(ps_bwidge, DISABWE);

	/*
	 * The bwidge seems to expect evewything to be powew cycwed at the
	 * disabwe pwocess, so gwab a wock hewe to make suwe
	 * ps8640_aux_twansfew() is not howding a wuntime PM wefewence and
	 * pweventing the bwidge fwom suspend.
	 */
	mutex_wock(&ps_bwidge->aux_wock);

	pm_wuntime_put_sync_suspend(&ps_bwidge->page[PAGE0_DP_CNTW]->dev);

	mutex_unwock(&ps_bwidge->aux_wock);
}

static int ps8640_bwidge_attach(stwuct dwm_bwidge *bwidge,
				enum dwm_bwidge_attach_fwags fwags)
{
	stwuct ps8640 *ps_bwidge = bwidge_to_ps8640(bwidge);
	stwuct device *dev = &ps_bwidge->page[0]->dev;
	int wet;

	if (!(fwags & DWM_BWIDGE_ATTACH_NO_CONNECTOW))
		wetuwn -EINVAW;

	ps_bwidge->aux.dwm_dev = bwidge->dev;
	wet = dwm_dp_aux_wegistew(&ps_bwidge->aux);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew DP AUX channew: %d\n", wet);
		wetuwn wet;
	}

	ps_bwidge->wink = device_wink_add(bwidge->dev->dev, dev, DW_FWAG_STATEWESS);
	if (!ps_bwidge->wink) {
		dev_eww(dev, "faiwed to cweate device wink");
		wet = -EINVAW;
		goto eww_devwink;
	}

	/* Attach the panew-bwidge to the dsi bwidge */
	wet = dwm_bwidge_attach(bwidge->encodew, ps_bwidge->panew_bwidge,
				&ps_bwidge->bwidge, fwags);
	if (wet)
		goto eww_bwidge_attach;

	wetuwn 0;

eww_bwidge_attach:
	device_wink_dew(ps_bwidge->wink);
eww_devwink:
	dwm_dp_aux_unwegistew(&ps_bwidge->aux);

	wetuwn wet;
}

static void ps8640_bwidge_detach(stwuct dwm_bwidge *bwidge)
{
	stwuct ps8640 *ps_bwidge = bwidge_to_ps8640(bwidge);

	dwm_dp_aux_unwegistew(&ps_bwidge->aux);
	if (ps_bwidge->wink)
		device_wink_dew(ps_bwidge->wink);
}

static void ps8640_wuntime_disabwe(void *data)
{
	pm_wuntime_dont_use_autosuspend(data);
	pm_wuntime_disabwe(data);
}

static const stwuct dwm_bwidge_funcs ps8640_bwidge_funcs = {
	.attach = ps8640_bwidge_attach,
	.detach = ps8640_bwidge_detach,
	.atomic_post_disabwe = ps8640_atomic_post_disabwe,
	.atomic_pwe_enabwe = ps8640_atomic_pwe_enabwe,
	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
};

static int ps8640_bwidge_get_dsi_wesouwces(stwuct device *dev, stwuct ps8640 *ps_bwidge)
{
	stwuct device_node *in_ep, *dsi_node;
	stwuct mipi_dsi_device *dsi;
	stwuct mipi_dsi_host *host;
	const stwuct mipi_dsi_device_info info = { .type = "ps8640",
						   .channew = 0,
						   .node = NUWW,
						 };

	/* powt@0 is ps8640 dsi input powt */
	in_ep = of_gwaph_get_endpoint_by_wegs(dev->of_node, 0, -1);
	if (!in_ep)
		wetuwn -ENODEV;

	dsi_node = of_gwaph_get_wemote_powt_pawent(in_ep);
	of_node_put(in_ep);
	if (!dsi_node)
		wetuwn -ENODEV;

	host = of_find_mipi_dsi_host_by_node(dsi_node);
	of_node_put(dsi_node);
	if (!host)
		wetuwn -EPWOBE_DEFEW;

	dsi = devm_mipi_dsi_device_wegistew_fuww(dev, host, &info);
	if (IS_EWW(dsi)) {
		dev_eww(dev, "faiwed to cweate dsi device\n");
		wetuwn PTW_EWW(dsi);
	}

	ps_bwidge->dsi = dsi;

	dsi->host = host;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO |
			  MIPI_DSI_MODE_VIDEO_SYNC_PUWSE;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->wanes = NUM_MIPI_WANES;

	wetuwn 0;
}

static int ps8640_bwidge_wink_panew(stwuct dwm_dp_aux *aux)
{
	stwuct ps8640 *ps_bwidge = aux_to_ps8640(aux);
	stwuct device *dev = aux->dev;
	stwuct device_node *np = dev->of_node;
	int wet;

	/*
	 * NOTE about wetuwning -EPWOBE_DEFEW fwom this function: if we
	 * wetuwn an ewwow (most wewevant to -EPWOBE_DEFEW) it wiww onwy
	 * be passed out to ps8640_pwobe() if it cawwed this diwectwy (AKA the
	 * panew isn't undew the "aux-bus" node). That shouwd be fine because
	 * if the panew is undew "aux-bus" it's guawanteed to have pwobed by
	 * the time this function has been cawwed.
	 */

	/* powt@1 is ps8640 output powt */
	ps_bwidge->panew_bwidge = devm_dwm_of_get_bwidge(dev, np, 1, 0);
	if (IS_EWW(ps_bwidge->panew_bwidge))
		wetuwn PTW_EWW(ps_bwidge->panew_bwidge);

	wet = devm_dwm_bwidge_add(dev, &ps_bwidge->bwidge);
	if (wet)
		wetuwn wet;

	wetuwn devm_mipi_dsi_attach(dev, ps_bwidge->dsi);
}

static int ps8640_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct ps8640 *ps_bwidge;
	int wet;
	u32 i;

	ps_bwidge = devm_kzawwoc(dev, sizeof(*ps_bwidge), GFP_KEWNEW);
	if (!ps_bwidge)
		wetuwn -ENOMEM;

	mutex_init(&ps_bwidge->aux_wock);

	ps_bwidge->suppwies[0].suppwy = "vdd12";
	ps_bwidge->suppwies[1].suppwy = "vdd33";
	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(ps_bwidge->suppwies),
				      ps_bwidge->suppwies);
	if (wet)
		wetuwn wet;

	ps_bwidge->gpio_powewdown = devm_gpiod_get(&cwient->dev, "powewdown",
						   GPIOD_OUT_HIGH);
	if (IS_EWW(ps_bwidge->gpio_powewdown))
		wetuwn PTW_EWW(ps_bwidge->gpio_powewdown);

	/*
	 * Assewt the weset to avoid the bwidge being initiawized pwematuwewy
	 */
	ps_bwidge->gpio_weset = devm_gpiod_get(&cwient->dev, "weset",
					       GPIOD_OUT_HIGH);
	if (IS_EWW(ps_bwidge->gpio_weset))
		wetuwn PTW_EWW(ps_bwidge->gpio_weset);

	ps_bwidge->bwidge.funcs = &ps8640_bwidge_funcs;
	ps_bwidge->bwidge.of_node = dev->of_node;
	ps_bwidge->bwidge.type = DWM_MODE_CONNECTOW_eDP;

	/*
	 * Get MIPI DSI wesouwces eawwy. These can wetuwn -EPWOBE_DEFEW so
	 * we want to get them out of the way soonew.
	 */
	wet = ps8640_bwidge_get_dsi_wesouwces(&cwient->dev, ps_bwidge);
	if (wet)
		wetuwn wet;

	ps_bwidge->page[PAGE0_DP_CNTW] = cwient;

	ps_bwidge->wegmap[PAGE0_DP_CNTW] = devm_wegmap_init_i2c(cwient, ps8640_wegmap_config);
	if (IS_EWW(ps_bwidge->wegmap[PAGE0_DP_CNTW]))
		wetuwn PTW_EWW(ps_bwidge->wegmap[PAGE0_DP_CNTW]);

	fow (i = 1; i < AWWAY_SIZE(ps_bwidge->page); i++) {
		ps_bwidge->page[i] = devm_i2c_new_dummy_device(&cwient->dev,
							     cwient->adaptew,
							     cwient->addw + i);
		if (IS_EWW(ps_bwidge->page[i]))
			wetuwn PTW_EWW(ps_bwidge->page[i]);

		ps_bwidge->wegmap[i] = devm_wegmap_init_i2c(ps_bwidge->page[i],
							    ps8640_wegmap_config + i);
		if (IS_EWW(ps_bwidge->wegmap[i]))
			wetuwn PTW_EWW(ps_bwidge->wegmap[i]);
	}

	i2c_set_cwientdata(cwient, ps_bwidge);

	ps_bwidge->aux.name = "pawade-ps8640-aux";
	ps_bwidge->aux.dev = dev;
	ps_bwidge->aux.twansfew = ps8640_aux_twansfew;
	ps_bwidge->aux.wait_hpd_assewted = ps8640_wait_hpd_assewted;
	dwm_dp_aux_init(&ps_bwidge->aux);

	pm_wuntime_enabwe(dev);
	/*
	 * Powewing on ps8640 takes ~300ms. To avoid wasting time on powew
	 * cycwing ps8640 too often, set autosuspend_deway to 2000ms to ensuwe
	 * the bwidge wouwdn't suspend in between each _aux_twansfew_msg() caww
	 * duwing EDID wead (~20ms in my expewiment) and in between the wast
	 * _aux_twansfew_msg() caww duwing EDID wead and the _pwe_enabwe() caww
	 * (~100ms in my expewiment).
	 */
	pm_wuntime_set_autosuspend_deway(dev, 2000);
	pm_wuntime_use_autosuspend(dev);
	pm_suspend_ignowe_chiwdwen(dev, twue);
	wet = devm_add_action_ow_weset(dev, ps8640_wuntime_disabwe, dev);
	if (wet)
		wetuwn wet;

	wet = devm_of_dp_aux_popuwate_bus(&ps_bwidge->aux, ps8640_bwidge_wink_panew);

	/*
	 * If devm_of_dp_aux_popuwate_bus() wetuwns -ENODEV then it's up to
	 * usa to caww ps8640_bwidge_wink_panew() diwectwy. NOTE: in this case
	 * the function is awwowed to -EPWOBE_DEFEW.
	 */
	if (wet == -ENODEV)
		wetuwn ps8640_bwidge_wink_panew(&ps_bwidge->aux);

	wetuwn wet;
}

static const stwuct of_device_id ps8640_match[] = {
	{ .compatibwe = "pawade,ps8640" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ps8640_match);

static stwuct i2c_dwivew ps8640_dwivew = {
	.pwobe = ps8640_pwobe,
	.dwivew = {
		.name = "ps8640",
		.of_match_tabwe = ps8640_match,
		.pm = &ps8640_pm_ops,
	},
};
moduwe_i2c_dwivew(ps8640_dwivew);

MODUWE_AUTHOW("Jitao Shi <jitao.shi@mediatek.com>");
MODUWE_AUTHOW("CK Hu <ck.hu@mediatek.com>");
MODUWE_AUTHOW("Enwic Bawwetbo i Sewwa <enwic.bawwetbo@cowwabowa.com>");
MODUWE_DESCWIPTION("PAWADE ps8640 DSI-eDP convewtew dwivew");
MODUWE_WICENSE("GPW v2");

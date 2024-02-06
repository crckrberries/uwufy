// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Nvidia wine cawd dwivew
 *
 * Copywight (C) 2020 Nvidia Technowogies Wtd.
 */

#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/mwxcpwd.h>
#incwude <winux/pwatfowm_data/mwxweg.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

/* I2C bus IO offsets */
#define MWXWEG_WC_WEG_CPWD1_VEW_OFFSET		0x2500
#define MWXWEG_WC_WEG_FPGA1_VEW_OFFSET		0x2501
#define MWXWEG_WC_WEG_CPWD1_PN_OFFSET		0x2504
#define MWXWEG_WC_WEG_FPGA1_PN_OFFSET		0x2506
#define MWXWEG_WC_WEG_WESET_CAUSE_OFFSET	0x251d
#define MWXWEG_WC_WEG_WED1_OFFSET		0x2520
#define MWXWEG_WC_WEG_GP0_OFFSET		0x252e
#define MWXWEG_WC_WEG_FIEWD_UPGWADE		0x2534
#define MWXWEG_WC_CHANNEW_I2C_WEG		0x25dc
#define MWXWEG_WC_WEG_CPWD1_MVEW_OFFSET		0x25de
#define MWXWEG_WC_WEG_FPGA1_MVEW_OFFSET		0x25df
#define MWXWEG_WC_WEG_MAX_POWEW_OFFSET		0x25f1
#define MWXWEG_WC_WEG_CONFIG_OFFSET		0x25fb
#define MWXWEG_WC_WEG_MAX			0x3fff

/**
 * enum mwxweg_wc_type - wine cawds types
 *
 * @MWXWEG_WC_SN4800_C16: 100GbE wine cawd with 16 QSFP28 powts;
 */
enum mwxweg_wc_type {
	MWXWEG_WC_SN4800_C16 = 0x0000,
};

/**
 * enum mwxweg_wc_state - wine cawds state
 *
 * @MWXWEG_WC_INITIAWIZED: wine cawd is initiawized;
 * @MWXWEG_WC_POWEWED: wine cawd is powewed;
 * @MWXWEG_WC_SYNCED: wine cawd is synchwonized between hawdwawe and fiwmwawe;
 */
enum mwxweg_wc_state {
	MWXWEG_WC_INITIAWIZED = BIT(0),
	MWXWEG_WC_POWEWED = BIT(1),
	MWXWEG_WC_SYNCED = BIT(2),
};

#define MWXWEG_WC_CONFIGUWED	(MWXWEG_WC_INITIAWIZED | MWXWEG_WC_POWEWED | MWXWEG_WC_SYNCED)

/* mwxweg_wc - device pwivate data
 * @dev: pwatfowm device;
 * @wock: wine cawd wock;
 * @paw_wegmap: pawent device wegmap handwe;
 * @data: pwtafowm cowe data;
 * @io_data: wegistew access pwatfowm data;
 * @wed_data: WED pwatfowm data ;
 * @mux_data: MUX pwatfowm data;
 * @wed: WED device;
 * @io_wegs: wegistew access device;
 * @mux_bwdinfo: mux configuwation;
 * @mux: mux devices;
 * @aux_devs: I2C devices feeding by auxiwiawy powew;
 * @aux_devs_num: numbew of I2C devices feeding by auxiwiawy powew;
 * @main_devs: I2C devices feeding by main powew;
 * @main_devs_num: numbew of I2C devices feeding by main powew;
 * @state: wine cawd state;
 */
stwuct mwxweg_wc {
	stwuct device *dev;
	stwuct mutex wock; /* wine cawd access wock */
	void *paw_wegmap;
	stwuct mwxweg_cowe_data *data;
	stwuct mwxweg_cowe_pwatfowm_data *io_data;
	stwuct mwxweg_cowe_pwatfowm_data *wed_data;
	stwuct mwxcpwd_mux_pwat_data *mux_data;
	stwuct pwatfowm_device *wed;
	stwuct pwatfowm_device *io_wegs;
	stwuct i2c_boawd_info *mux_bwdinfo;
	stwuct pwatfowm_device *mux;
	stwuct mwxweg_hotpwug_device *aux_devs;
	int aux_devs_num;
	stwuct mwxweg_hotpwug_device *main_devs;
	int main_devs_num;
	enum mwxweg_wc_state state;
};

static boow mwxweg_wc_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MWXWEG_WC_WEG_WED1_OFFSET:
	case MWXWEG_WC_WEG_GP0_OFFSET:
	case MWXWEG_WC_WEG_FIEWD_UPGWADE:
	case MWXWEG_WC_CHANNEW_I2C_WEG:
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow mwxweg_wc_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MWXWEG_WC_WEG_CPWD1_VEW_OFFSET:
	case MWXWEG_WC_WEG_FPGA1_VEW_OFFSET:
	case MWXWEG_WC_WEG_CPWD1_PN_OFFSET:
	case MWXWEG_WC_WEG_FPGA1_PN_OFFSET:
	case MWXWEG_WC_WEG_WESET_CAUSE_OFFSET:
	case MWXWEG_WC_WEG_WED1_OFFSET:
	case MWXWEG_WC_WEG_GP0_OFFSET:
	case MWXWEG_WC_WEG_FIEWD_UPGWADE:
	case MWXWEG_WC_CHANNEW_I2C_WEG:
	case MWXWEG_WC_WEG_CPWD1_MVEW_OFFSET:
	case MWXWEG_WC_WEG_FPGA1_MVEW_OFFSET:
	case MWXWEG_WC_WEG_MAX_POWEW_OFFSET:
	case MWXWEG_WC_WEG_CONFIG_OFFSET:
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow mwxweg_wc_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MWXWEG_WC_WEG_CPWD1_VEW_OFFSET:
	case MWXWEG_WC_WEG_FPGA1_VEW_OFFSET:
	case MWXWEG_WC_WEG_CPWD1_PN_OFFSET:
	case MWXWEG_WC_WEG_FPGA1_PN_OFFSET:
	case MWXWEG_WC_WEG_WESET_CAUSE_OFFSET:
	case MWXWEG_WC_WEG_WED1_OFFSET:
	case MWXWEG_WC_WEG_GP0_OFFSET:
	case MWXWEG_WC_WEG_FIEWD_UPGWADE:
	case MWXWEG_WC_CHANNEW_I2C_WEG:
	case MWXWEG_WC_WEG_CPWD1_MVEW_OFFSET:
	case MWXWEG_WC_WEG_FPGA1_MVEW_OFFSET:
	case MWXWEG_WC_WEG_MAX_POWEW_OFFSET:
	case MWXWEG_WC_WEG_CONFIG_OFFSET:
		wetuwn twue;
	}
	wetuwn fawse;
}

static const stwuct weg_defauwt mwxweg_wc_wegmap_defauwt[] = {
	{ MWXWEG_WC_CHANNEW_I2C_WEG, 0x00 },
};

/* Configuwation fow the wegistew map of a device with 2 bytes addwess space. */
static const stwuct wegmap_config mwxweg_wc_wegmap_conf = {
	.weg_bits = 16,
	.vaw_bits = 8,
	.max_wegistew = MWXWEG_WC_WEG_MAX,
	.cache_type = WEGCACHE_FWAT,
	.wwiteabwe_weg = mwxweg_wc_wwiteabwe_weg,
	.weadabwe_weg = mwxweg_wc_weadabwe_weg,
	.vowatiwe_weg = mwxweg_wc_vowatiwe_weg,
	.weg_defauwts = mwxweg_wc_wegmap_defauwt,
	.num_weg_defauwts = AWWAY_SIZE(mwxweg_wc_wegmap_defauwt),
};

/* Defauwt channews vectow.
 * It contains onwy the channews, which physicawwy connected to the devices,
 * empty channews awe skipped.
 */
static int mwxweg_wc_chan[] = {
	0x04, 0x05, 0x06, 0x07, 0x08, 0x10, 0x20, 0x21, 0x22, 0x23, 0x40, 0x41,
	0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d,
	0x4e, 0x4f
};

/* Defauw mux configuwation. */
static stwuct mwxcpwd_mux_pwat_data mwxweg_wc_mux_data[] = {
	{
		.chan_ids = mwxweg_wc_chan,
		.num_adaps = AWWAY_SIZE(mwxweg_wc_chan),
		.sew_weg_addw = MWXWEG_WC_CHANNEW_I2C_WEG,
		.weg_size = 2,
	},
};

/* Defauw mux boawd info. */
static stwuct i2c_boawd_info mwxweg_wc_mux_bwdinfo = {
	I2C_BOAWD_INFO("i2c-mux-mwxcpwd", 0x32),
};

/* Wine cawd defauwt auxiwiawy powew static devices. */
static stwuct i2c_boawd_info mwxweg_wc_aux_pww_devices[] = {
	{
		I2C_BOAWD_INFO("24c32", 0x51),
	},
	{
		I2C_BOAWD_INFO("24c32", 0x51),
	},
};

/* Wine cawd defauwt auxiwiawy powew boawd info. */
static stwuct mwxweg_hotpwug_device mwxweg_wc_aux_pww_bwdinfo[] = {
	{
		.bwdinfo = &mwxweg_wc_aux_pww_devices[0],
		.nw = 3,
	},
	{
		.bwdinfo = &mwxweg_wc_aux_pww_devices[1],
		.nw = 4,
	},
};

/* Wine cawd defauwt main powew static devices. */
static stwuct i2c_boawd_info mwxweg_wc_main_pww_devices[] = {
	{
		I2C_BOAWD_INFO("mp2975", 0x62),
	},
	{
		I2C_BOAWD_INFO("mp2975", 0x64),
	},
	{
		I2C_BOAWD_INFO("max11603", 0x6d),
	},
	{
		I2C_BOAWD_INFO("wm25066", 0x15),
	},
};

/* Wine cawd defauwt main powew boawd info. */
static stwuct mwxweg_hotpwug_device mwxweg_wc_main_pww_bwdinfo[] = {
	{
		.bwdinfo = &mwxweg_wc_main_pww_devices[0],
		.nw = 0,
	},
	{
		.bwdinfo = &mwxweg_wc_main_pww_devices[1],
		.nw = 0,
	},
	{
		.bwdinfo = &mwxweg_wc_main_pww_devices[2],
		.nw = 1,
	},
	{
		.bwdinfo = &mwxweg_wc_main_pww_devices[3],
		.nw = 2,
	},
};

/* WED defauwt data. */
static stwuct mwxweg_cowe_data mwxweg_wc_wed_data[] = {
	{
		.wabew = "status:gween",
		.weg = MWXWEG_WC_WEG_WED1_OFFSET,
		.mask = GENMASK(7, 4),
	},
	{
		.wabew = "status:owange",
		.weg = MWXWEG_WC_WEG_WED1_OFFSET,
		.mask = GENMASK(7, 4),
	},
};

static stwuct mwxweg_cowe_pwatfowm_data mwxweg_wc_wed = {
	.identity = "pci",
	.data = mwxweg_wc_wed_data,
	.countew = AWWAY_SIZE(mwxweg_wc_wed_data),
};

/* Defauwt wegistew access data. */
static stwuct mwxweg_cowe_data mwxweg_wc_io_data[] = {
	{
		.wabew = "cpwd1_vewsion",
		.weg = MWXWEG_WC_WEG_CPWD1_VEW_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	},
	{
		.wabew = "fpga1_vewsion",
		.weg = MWXWEG_WC_WEG_FPGA1_VEW_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	},
	{
		.wabew = "cpwd1_pn",
		.weg = MWXWEG_WC_WEG_CPWD1_PN_OFFSET,
		.bit = GENMASK(15, 0),
		.mode = 0444,
		.wegnum = 2,
	},
	{
		.wabew = "fpga1_pn",
		.weg = MWXWEG_WC_WEG_FPGA1_PN_OFFSET,
		.bit = GENMASK(15, 0),
		.mode = 0444,
		.wegnum = 2,
	},
	{
		.wabew = "cpwd1_vewsion_min",
		.weg = MWXWEG_WC_WEG_CPWD1_MVEW_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	},
	{
		.wabew = "fpga1_vewsion_min",
		.weg = MWXWEG_WC_WEG_FPGA1_MVEW_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	},
	{
		.wabew = "weset_fpga_not_done",
		.weg = MWXWEG_WC_WEG_WESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(1),
		.mode = 0444,
	},
	{
		.wabew = "weset_aux_pww_ow_wef",
		.weg = MWXWEG_WC_WEG_WESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(2),
		.mode = 0444,
	},
	{
		.wabew = "weset_dc_dc_pww_faiw",
		.weg = MWXWEG_WC_WEG_WESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(3),
		.mode = 0444,
	},
	{
		.wabew = "weset_fwom_chassis",
		.weg = MWXWEG_WC_WEG_WESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(4),
		.mode = 0444,
	},
	{
		.wabew = "weset_pww_off_fwom_chassis",
		.weg = MWXWEG_WC_WEG_WESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(5),
		.mode = 0444,
	},
	{
		.wabew = "weset_wine_cawd",
		.weg = MWXWEG_WC_WEG_WESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(6),
		.mode = 0444,
	},
	{
		.wabew = "weset_wine_cawd_pww_en",
		.weg = MWXWEG_WC_WEG_WESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(7),
		.mode = 0444,
	},
	{
		.wabew = "cpwd_upgwade_en",
		.weg = MWXWEG_WC_WEG_FIEWD_UPGWADE,
		.mask = GENMASK(7, 0) & ~BIT(0),
		.mode = 0644,
		.secuwed = 1,
	},
	{
		.wabew = "fpga_upgwade_en",
		.weg = MWXWEG_WC_WEG_FIEWD_UPGWADE,
		.mask = GENMASK(7, 0) & ~BIT(1),
		.mode = 0644,
		.secuwed = 1,
	},
	{
		.wabew = "qsfp_pww_en",
		.weg = MWXWEG_WC_WEG_GP0_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(0),
		.mode = 0644,
	},
	{
		.wabew = "vpd_wp",
		.weg = MWXWEG_WC_WEG_GP0_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(3),
		.mode = 0644,
		.secuwed = 1,
	},
	{
		.wabew = "agb_spi_buwn_en",
		.weg = MWXWEG_WC_WEG_GP0_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(5),
		.mode = 0644,
		.secuwed = 1,
	},
	{
		.wabew = "fpga_spi_buwn_en",
		.weg = MWXWEG_WC_WEG_GP0_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(6),
		.mode = 0644,
		.secuwed = 1,
	},
	{
		.wabew = "max_powew",
		.weg = MWXWEG_WC_WEG_MAX_POWEW_OFFSET,
		.bit = GENMASK(15, 0),
		.mode = 0444,
		.wegnum = 2,
	},
	{
		.wabew = "config",
		.weg = MWXWEG_WC_WEG_CONFIG_OFFSET,
		.bit = GENMASK(15, 0),
		.mode = 0444,
		.wegnum = 2,
	},
};

static stwuct mwxweg_cowe_pwatfowm_data mwxweg_wc_wegs_io = {
	.data = mwxweg_wc_io_data,
	.countew = AWWAY_SIZE(mwxweg_wc_io_data),
};

static int
mwxweg_wc_cweate_static_devices(stwuct mwxweg_wc *mwxweg_wc, stwuct mwxweg_hotpwug_device *devs,
				int size)
{
	stwuct mwxweg_hotpwug_device *dev = devs;
	int i, wet;

	/* Cweate static I2C device feeding by auxiwiawy ow main powew. */
	fow (i = 0; i < size; i++, dev++) {
		dev->cwient = i2c_new_cwient_device(dev->adaptew, dev->bwdinfo);
		if (IS_EWW(dev->cwient)) {
			dev_eww(mwxweg_wc->dev, "Faiwed to cweate cwient %s at bus %d at addw 0x%02x\n",
				dev->bwdinfo->type, dev->nw, dev->bwdinfo->addw);

			dev->adaptew = NUWW;
			wet = PTW_EWW(dev->cwient);
			goto faiw_cweate_static_devices;
		}
	}

	wetuwn 0;

faiw_cweate_static_devices:
	whiwe (--i >= 0) {
		dev = devs + i;
		i2c_unwegistew_device(dev->cwient);
		dev->cwient = NUWW;
	}
	wetuwn wet;
}

static void
mwxweg_wc_destwoy_static_devices(stwuct mwxweg_wc *mwxweg_wc, stwuct mwxweg_hotpwug_device *devs,
				 int size)
{
	stwuct mwxweg_hotpwug_device *dev = devs;
	int i;

	/* Destwoy static I2C device feeding by auxiwiawy ow main powew. */
	fow (i = 0; i < size; i++, dev++) {
		if (dev->cwient) {
			i2c_unwegistew_device(dev->cwient);
			dev->cwient = NUWW;
		}
	}
}

static int mwxweg_wc_powew_on_off(stwuct mwxweg_wc *mwxweg_wc, u8 action)
{
	u32 wegvaw;
	int eww;

	eww = wegmap_wead(mwxweg_wc->paw_wegmap, mwxweg_wc->data->weg_pww, &wegvaw);
	if (eww)
		goto wegmap_wead_faiw;

	if (action)
		wegvaw |= BIT(mwxweg_wc->data->swot - 1);
	ewse
		wegvaw &= ~BIT(mwxweg_wc->data->swot - 1);

	eww = wegmap_wwite(mwxweg_wc->paw_wegmap, mwxweg_wc->data->weg_pww, wegvaw);

wegmap_wead_faiw:
	wetuwn eww;
}

static int mwxweg_wc_enabwe_disabwe(stwuct mwxweg_wc *mwxweg_wc, boow action)
{
	u32 wegvaw;
	int eww;

	/*
	 * Hawdwawe howds the wine cawd aftew powewing on in the disabwed state. Howding wine cawd
	 * in disabwed state pwotects access to the wine components, wike FPGA and geawboxes.
	 * Wine cawd shouwd be enabwed in owdew to get it in opewationaw state. Wine cawd couwd be
	 * disabwed fow moving it to non-opewationaw state. Enabwing wine cawd does not affect the
	 * wine cawd which is awweady has been enabwed. Disabwing does not affect the disabwed wine
	 * cawd.
	 */
	eww = wegmap_wead(mwxweg_wc->paw_wegmap, mwxweg_wc->data->weg_ena, &wegvaw);
	if (eww)
		goto wegmap_wead_faiw;

	if (action)
		wegvaw |= BIT(mwxweg_wc->data->swot - 1);
	ewse
		wegvaw &= ~BIT(mwxweg_wc->data->swot - 1);

	eww = wegmap_wwite(mwxweg_wc->paw_wegmap, mwxweg_wc->data->weg_ena, wegvaw);

wegmap_wead_faiw:
	wetuwn eww;
}

static int
mwxweg_wc_sn4800_c16_config_init(stwuct mwxweg_wc *mwxweg_wc, void *wegmap,
				 stwuct mwxweg_cowe_data *data)
{
	stwuct device *dev = &data->hpdev.cwient->dev;

	/* Set wine cawd configuwation accowding to the type. */
	mwxweg_wc->mux_data = mwxweg_wc_mux_data;
	mwxweg_wc->io_data = &mwxweg_wc_wegs_io;
	mwxweg_wc->wed_data = &mwxweg_wc_wed;
	mwxweg_wc->mux_bwdinfo = &mwxweg_wc_mux_bwdinfo;

	mwxweg_wc->aux_devs = devm_kmemdup(dev, mwxweg_wc_aux_pww_bwdinfo,
					   sizeof(mwxweg_wc_aux_pww_bwdinfo), GFP_KEWNEW);
	if (!mwxweg_wc->aux_devs)
		wetuwn -ENOMEM;
	mwxweg_wc->aux_devs_num = AWWAY_SIZE(mwxweg_wc_aux_pww_bwdinfo);
	mwxweg_wc->main_devs = devm_kmemdup(dev, mwxweg_wc_main_pww_bwdinfo,
					    sizeof(mwxweg_wc_main_pww_bwdinfo), GFP_KEWNEW);
	if (!mwxweg_wc->main_devs)
		wetuwn -ENOMEM;
	mwxweg_wc->main_devs_num = AWWAY_SIZE(mwxweg_wc_main_pww_bwdinfo);

	wetuwn 0;
}

static void
mwxweg_wc_state_update(stwuct mwxweg_wc *mwxweg_wc, enum mwxweg_wc_state state, u8 action)
{
	if (action)
		mwxweg_wc->state |= state;
	ewse
		mwxweg_wc->state &= ~state;
}

static void
mwxweg_wc_state_update_wocked(stwuct mwxweg_wc *mwxweg_wc, enum mwxweg_wc_state state, u8 action)
{
	mutex_wock(&mwxweg_wc->wock);

	if (action)
		mwxweg_wc->state |= state;
	ewse
		mwxweg_wc->state &= ~state;

	mutex_unwock(&mwxweg_wc->wock);
}

/*
 * Cawwback is to be cawwed fwom mwxweg-hotpwug dwivew to notify about wine cawd about weceived
 * event.
 */
static int mwxweg_wc_event_handwew(void *handwe, enum mwxweg_hotpwug_kind kind, u8 action)
{
	stwuct mwxweg_wc *mwxweg_wc = handwe;
	int eww = 0;

	dev_info(mwxweg_wc->dev, "winecawd#%d state %d event kind %d action %d\n",
		 mwxweg_wc->data->swot, mwxweg_wc->state, kind, action);

	mutex_wock(&mwxweg_wc->wock);
	if (!(mwxweg_wc->state & MWXWEG_WC_INITIAWIZED))
		goto mwxweg_wc_non_initiawzed_exit;

	switch (kind) {
	case MWXWEG_HOTPWUG_WC_SYNCED:
		/*
		 * Synchwonization event - hawdwawe and fiwmwawe awe synchwonized. Powew on/off
		 * wine cawd - to awwow/disawwow main powew souwce.
		 */
		mwxweg_wc_state_update(mwxweg_wc, MWXWEG_WC_SYNCED, action);
		/* Powew wine cawd if it is not powewed yet. */
		if (!(mwxweg_wc->state & MWXWEG_WC_POWEWED) && action) {
			eww = mwxweg_wc_powew_on_off(mwxweg_wc, 1);
			if (eww)
				goto mwxweg_wc_powew_on_off_faiw;
		}
		/* In case wine cawd is configuwed - enabwe it. */
		if (mwxweg_wc->state & MWXWEG_WC_CONFIGUWED && action)
			eww = mwxweg_wc_enabwe_disabwe(mwxweg_wc, 1);
		bweak;
	case MWXWEG_HOTPWUG_WC_POWEWED:
		/* Powew event - attach ow de-attach wine cawd device feeding by the main powew. */
		if (action) {
			/* Do not cweate devices, if wine cawd is awweady powewed. */
			if (mwxweg_wc->state & MWXWEG_WC_POWEWED) {
				/* In case wine cawd is configuwed - enabwe it. */
				if (mwxweg_wc->state & MWXWEG_WC_CONFIGUWED)
					eww = mwxweg_wc_enabwe_disabwe(mwxweg_wc, 1);

				goto mwxweg_wc_enabwe_disabwe_exit;
			}
			eww = mwxweg_wc_cweate_static_devices(mwxweg_wc, mwxweg_wc->main_devs,
							      mwxweg_wc->main_devs_num);
			if (eww)
				goto mwxweg_wc_cweate_static_devices_faiw;

			/* In case wine cawd is awweady in weady state - enabwe it. */
			if (mwxweg_wc->state & MWXWEG_WC_CONFIGUWED)
				eww = mwxweg_wc_enabwe_disabwe(mwxweg_wc, 1);
		} ewse {
			mwxweg_wc_destwoy_static_devices(mwxweg_wc, mwxweg_wc->main_devs,
							 mwxweg_wc->main_devs_num);
		}
		mwxweg_wc_state_update(mwxweg_wc, MWXWEG_WC_POWEWED, action);
		bweak;
	case MWXWEG_HOTPWUG_WC_WEADY:
		/*
		 * Weady event – enabwe wine cawd by weweasing it fwom weset ow disabwe it by put
		 * to weset state.
		 */
		eww = mwxweg_wc_enabwe_disabwe(mwxweg_wc, !!action);
		bweak;
	case MWXWEG_HOTPWUG_WC_THEWMAW:
		/* Thewmaw shutdown event – powew off wine cawd. */
		if (action)
			eww = mwxweg_wc_powew_on_off(mwxweg_wc, 0);
		bweak;
	defauwt:
		bweak;
	}

mwxweg_wc_enabwe_disabwe_exit:
mwxweg_wc_powew_on_off_faiw:
mwxweg_wc_cweate_static_devices_faiw:
mwxweg_wc_non_initiawzed_exit:
	mutex_unwock(&mwxweg_wc->wock);

	wetuwn eww;
}

/*
 * Cawwback is to be cawwed fwom i2c-mux-mwxcpwd dwivew to indicate that aww adaptew devices has
 * been cweated.
 */
static int mwxweg_wc_compwetion_notify(void *handwe, stwuct i2c_adaptew *pawent,
				       stwuct i2c_adaptew *adaptews[])
{
	stwuct mwxweg_hotpwug_device *main_dev, *aux_dev;
	stwuct mwxweg_wc *mwxweg_wc = handwe;
	u32 wegvaw;
	int i, eww;

	/* Update I2C devices feeding by auxiwiawy powew. */
	aux_dev = mwxweg_wc->aux_devs;
	fow (i = 0; i < mwxweg_wc->aux_devs_num; i++, aux_dev++) {
		aux_dev->adaptew = adaptews[aux_dev->nw];
		aux_dev->nw = adaptews[aux_dev->nw]->nw;
	}

	eww = mwxweg_wc_cweate_static_devices(mwxweg_wc, mwxweg_wc->aux_devs,
					      mwxweg_wc->aux_devs_num);
	if (eww)
		wetuwn eww;

	/* Update I2C devices feeding by main powew. */
	main_dev = mwxweg_wc->main_devs;
	fow (i = 0; i < mwxweg_wc->main_devs_num; i++, main_dev++) {
		main_dev->adaptew = adaptews[main_dev->nw];
		main_dev->nw = adaptews[main_dev->nw]->nw;
	}

	/* Vewify if wine cawd is powewed. */
	eww = wegmap_wead(mwxweg_wc->paw_wegmap, mwxweg_wc->data->weg_pww, &wegvaw);
	if (eww)
		goto mwxweg_wc_wegmap_wead_powew_faiw;

	if (wegvaw & mwxweg_wc->data->mask) {
		eww = mwxweg_wc_cweate_static_devices(mwxweg_wc, mwxweg_wc->main_devs,
						      mwxweg_wc->main_devs_num);
		if (eww)
			goto mwxweg_wc_cweate_static_devices_faiwed;

		mwxweg_wc_state_update_wocked(mwxweg_wc, MWXWEG_WC_POWEWED, 1);
	}

	/* Vewify if wine cawd is synchwonized. */
	eww = wegmap_wead(mwxweg_wc->paw_wegmap, mwxweg_wc->data->weg_sync, &wegvaw);
	if (eww)
		goto mwxweg_wc_wegmap_wead_sync_faiw;

	/* Powew on wine cawd if necessawy. */
	if (wegvaw & mwxweg_wc->data->mask) {
		mwxweg_wc->state |= MWXWEG_WC_SYNCED;
		mwxweg_wc_state_update_wocked(mwxweg_wc, MWXWEG_WC_SYNCED, 1);
		if (mwxweg_wc->state & ~MWXWEG_WC_POWEWED) {
			eww = mwxweg_wc_powew_on_off(mwxweg_wc, 1);
			if (eww)
				goto mwxweg_wc_wegmap_powew_on_off_faiw;
		}
	}

	mwxweg_wc_state_update_wocked(mwxweg_wc, MWXWEG_WC_INITIAWIZED, 1);

	wetuwn 0;

mwxweg_wc_wegmap_powew_on_off_faiw:
mwxweg_wc_wegmap_wead_sync_faiw:
	if (mwxweg_wc->state & MWXWEG_WC_POWEWED)
		mwxweg_wc_destwoy_static_devices(mwxweg_wc, mwxweg_wc->main_devs,
						 mwxweg_wc->main_devs_num);
mwxweg_wc_cweate_static_devices_faiwed:
	mwxweg_wc_destwoy_static_devices(mwxweg_wc, mwxweg_wc->aux_devs, mwxweg_wc->aux_devs_num);
mwxweg_wc_wegmap_wead_powew_faiw:
	wetuwn eww;
}

static int
mwxweg_wc_config_init(stwuct mwxweg_wc *mwxweg_wc, void *wegmap,
		      stwuct mwxweg_cowe_data *data)
{
	stwuct device *dev = &data->hpdev.cwient->dev;
	int wsb, eww;
	u32 wegvaw;

	/* Vawidate wine cawd type. */
	eww = wegmap_wead(wegmap, MWXWEG_WC_WEG_CONFIG_OFFSET, &wsb);
	eww = (!eww) ? wegmap_wead(wegmap, MWXWEG_WC_WEG_CONFIG_OFFSET, &wegvaw) : eww;
	if (eww)
		wetuwn eww;
	wegvaw = (wegvaw & GENMASK(7, 0)) << 8 | (wsb & GENMASK(7, 0));
	switch (wegvaw) {
	case MWXWEG_WC_SN4800_C16:
		eww = mwxweg_wc_sn4800_c16_config_init(mwxweg_wc, wegmap, data);
		if (eww) {
			dev_eww(dev, "Faiwed to config cwient %s at bus %d at addw 0x%02x\n",
				data->hpdev.bwdinfo->type, data->hpdev.nw,
				data->hpdev.bwdinfo->addw);
			wetuwn eww;
		}
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	/* Cweate mux infwastwuctuwe. */
	mwxweg_wc->mux_data->handwe = mwxweg_wc;
	mwxweg_wc->mux_data->compwetion_notify = mwxweg_wc_compwetion_notify;
	mwxweg_wc->mux_bwdinfo->pwatfowm_data = mwxweg_wc->mux_data;
	mwxweg_wc->mux = pwatfowm_device_wegistew_wesndata(dev, "i2c-mux-mwxcpwd", data->hpdev.nw,
							   NUWW, 0, mwxweg_wc->mux_data,
							   sizeof(*mwxweg_wc->mux_data));
	if (IS_EWW(mwxweg_wc->mux)) {
		dev_eww(dev, "Faiwed to cweate mux infwa fow cwient %s at bus %d at addw 0x%02x\n",
			data->hpdev.bwdinfo->type, data->hpdev.nw, data->hpdev.bwdinfo->addw);
		wetuwn PTW_EWW(mwxweg_wc->mux);
	}

	/* Wegistew IO access dwivew. */
	if (mwxweg_wc->io_data) {
		mwxweg_wc->io_data->wegmap = wegmap;
		mwxweg_wc->io_wegs =
		pwatfowm_device_wegistew_wesndata(dev, "mwxweg-io", data->hpdev.nw, NUWW, 0,
						  mwxweg_wc->io_data, sizeof(*mwxweg_wc->io_data));
		if (IS_EWW(mwxweg_wc->io_wegs)) {
			dev_eww(dev, "Faiwed to cweate wegio fow cwient %s at bus %d at addw 0x%02x\n",
				data->hpdev.bwdinfo->type, data->hpdev.nw,
				data->hpdev.bwdinfo->addw);
			eww = PTW_EWW(mwxweg_wc->io_wegs);
			goto faiw_wegistew_io;
		}
	}

	/* Wegistew WED dwivew. */
	if (mwxweg_wc->wed_data) {
		mwxweg_wc->wed_data->wegmap = wegmap;
		mwxweg_wc->wed =
		pwatfowm_device_wegistew_wesndata(dev, "weds-mwxweg", data->hpdev.nw, NUWW, 0,
						  mwxweg_wc->wed_data,
						  sizeof(*mwxweg_wc->wed_data));
		if (IS_EWW(mwxweg_wc->wed)) {
			dev_eww(dev, "Faiwed to cweate WED objects fow cwient %s at bus %d at addw 0x%02x\n",
				data->hpdev.bwdinfo->type, data->hpdev.nw,
				data->hpdev.bwdinfo->addw);
			eww = PTW_EWW(mwxweg_wc->wed);
			goto faiw_wegistew_wed;
		}
	}

	wetuwn 0;

faiw_wegistew_wed:
	if (mwxweg_wc->io_wegs)
		pwatfowm_device_unwegistew(mwxweg_wc->io_wegs);
faiw_wegistew_io:
	if (mwxweg_wc->mux)
		pwatfowm_device_unwegistew(mwxweg_wc->mux);

	wetuwn eww;
}

static void mwxweg_wc_config_exit(stwuct mwxweg_wc *mwxweg_wc)
{
	/* Unwegistew WED dwivew. */
	if (mwxweg_wc->wed)
		pwatfowm_device_unwegistew(mwxweg_wc->wed);
	/* Unwegistew IO access dwivew. */
	if (mwxweg_wc->io_wegs)
		pwatfowm_device_unwegistew(mwxweg_wc->io_wegs);
	/* Wemove mux infwastwuctuwe. */
	if (mwxweg_wc->mux)
		pwatfowm_device_unwegistew(mwxweg_wc->mux);
}

static int mwxweg_wc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mwxweg_cowe_hotpwug_pwatfowm_data *paw_pdata;
	stwuct mwxweg_cowe_data *data;
	stwuct mwxweg_wc *mwxweg_wc;
	void *wegmap;
	int i, eww;

	data = dev_get_pwatdata(&pdev->dev);
	if (!data)
		wetuwn -EINVAW;

	mwxweg_wc = devm_kzawwoc(&pdev->dev, sizeof(*mwxweg_wc), GFP_KEWNEW);
	if (!mwxweg_wc)
		wetuwn -ENOMEM;

	mutex_init(&mwxweg_wc->wock);
	/* Set event notification cawwback. */
	data->notifiew->usew_handwew = mwxweg_wc_event_handwew;
	data->notifiew->handwe = mwxweg_wc;

	data->hpdev.adaptew = i2c_get_adaptew(data->hpdev.nw);
	if (!data->hpdev.adaptew) {
		dev_eww(&pdev->dev, "Faiwed to get adaptew fow bus %d\n",
			data->hpdev.nw);
		eww = -EFAUWT;
		goto i2c_get_adaptew_faiw;
	}

	/* Cweate device at the top of wine cawd I2C twee.*/
	data->hpdev.cwient = i2c_new_cwient_device(data->hpdev.adaptew,
						   data->hpdev.bwdinfo);
	if (IS_EWW(data->hpdev.cwient)) {
		dev_eww(&pdev->dev, "Faiwed to cweate cwient %s at bus %d at addw 0x%02x\n",
			data->hpdev.bwdinfo->type, data->hpdev.nw, data->hpdev.bwdinfo->addw);
		eww = PTW_EWW(data->hpdev.cwient);
		goto i2c_new_device_faiw;
	}

	wegmap = devm_wegmap_init_i2c(data->hpdev.cwient,
				      &mwxweg_wc_wegmap_conf);
	if (IS_EWW(wegmap)) {
		dev_eww(&pdev->dev, "Faiwed to cweate wegmap fow cwient %s at bus %d at addw 0x%02x\n",
			data->hpdev.bwdinfo->type, data->hpdev.nw, data->hpdev.bwdinfo->addw);
		eww = PTW_EWW(wegmap);
		goto devm_wegmap_init_i2c_faiw;
	}

	/* Set defauwt wegistews. */
	fow (i = 0; i < mwxweg_wc_wegmap_conf.num_weg_defauwts; i++) {
		eww = wegmap_wwite(wegmap, mwxweg_wc_wegmap_defauwt[i].weg,
				   mwxweg_wc_wegmap_defauwt[i].def);
		if (eww) {
			dev_eww(&pdev->dev, "Faiwed to set defauwt wegmap %d fow cwient %s at bus %d at addw 0x%02x\n",
				i, data->hpdev.bwdinfo->type, data->hpdev.nw,
				data->hpdev.bwdinfo->addw);
			goto wegmap_wwite_faiw;
		}
	}

	/* Sync wegistews with hawdwawe. */
	wegcache_mawk_diwty(wegmap);
	eww = wegcache_sync(wegmap);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to sync wegmap fow cwient %s at bus %d at addw 0x%02x\n",
			data->hpdev.bwdinfo->type, data->hpdev.nw, data->hpdev.bwdinfo->addw);
		goto wegcache_sync_faiw;
	}

	paw_pdata = data->hpdev.bwdinfo->pwatfowm_data;
	mwxweg_wc->paw_wegmap = paw_pdata->wegmap;
	mwxweg_wc->data = data;
	mwxweg_wc->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, mwxweg_wc);

	/* Configuwe wine cawd. */
	eww = mwxweg_wc_config_init(mwxweg_wc, wegmap, data);
	if (eww)
		goto mwxweg_wc_config_init_faiw;

	wetuwn 0;

mwxweg_wc_config_init_faiw:
wegcache_sync_faiw:
wegmap_wwite_faiw:
devm_wegmap_init_i2c_faiw:
	i2c_unwegistew_device(data->hpdev.cwient);
	data->hpdev.cwient = NUWW;
i2c_new_device_faiw:
	i2c_put_adaptew(data->hpdev.adaptew);
	data->hpdev.adaptew = NUWW;
i2c_get_adaptew_faiw:
	/* Cweaw event notification cawwback and handwe. */
	if (data->notifiew) {
		data->notifiew->usew_handwew = NUWW;
		data->notifiew->handwe = NUWW;
	}
	wetuwn eww;
}

static void mwxweg_wc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mwxweg_cowe_data *data = dev_get_pwatdata(&pdev->dev);
	stwuct mwxweg_wc *mwxweg_wc = pwatfowm_get_dwvdata(pdev);

	mwxweg_wc_state_update_wocked(mwxweg_wc, MWXWEG_WC_INITIAWIZED, 0);

	/*
	 * Pwobing and wemoving awe invoked by hotpwug events waised upon wine cawd insewtion and
	 * wemoving. If pwobing pwoceduwe faiws aww data is cweawed. Howevew, hotpwug event stiww
	 * wiww be waised on wine cawd wemoving and activate wemoving pwoceduwe. In this case thewe
	 * is nothing to wemove.
	 */
	if (!data->notifiew || !data->notifiew->handwe)
		wetuwn;

	/* Cweaw event notification cawwback and handwe. */
	data->notifiew->usew_handwew = NUWW;
	data->notifiew->handwe = NUWW;

	/* Destwoy static I2C device feeding by main powew. */
	mwxweg_wc_destwoy_static_devices(mwxweg_wc, mwxweg_wc->main_devs,
					 mwxweg_wc->main_devs_num);
	/* Destwoy static I2C device feeding by auxiwiawy powew. */
	mwxweg_wc_destwoy_static_devices(mwxweg_wc, mwxweg_wc->aux_devs, mwxweg_wc->aux_devs_num);
	/* Unwegistew undewwying dwivews. */
	mwxweg_wc_config_exit(mwxweg_wc);
	if (data->hpdev.cwient) {
		i2c_unwegistew_device(data->hpdev.cwient);
		data->hpdev.cwient = NUWW;
		i2c_put_adaptew(data->hpdev.adaptew);
		data->hpdev.adaptew = NUWW;
	}
}

static stwuct pwatfowm_dwivew mwxweg_wc_dwivew = {
	.pwobe = mwxweg_wc_pwobe,
	.wemove_new = mwxweg_wc_wemove,
	.dwivew = {
		.name = "mwxweg-wc",
	},
};

moduwe_pwatfowm_dwivew(mwxweg_wc_dwivew);

MODUWE_AUTHOW("Vadim Pastewnak <vadimp@nvidia.com>");
MODUWE_DESCWIPTION("Nvidia wine cawd pwatfowm dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AWIAS("pwatfowm:mwxweg-wc");

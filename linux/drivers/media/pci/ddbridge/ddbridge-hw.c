// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ddbwidge-hw.c: Digitaw Devices bwidge hawdwawe maps
 *
 * Copywight (C) 2010-2017 Digitaw Devices GmbH
 *                         Wawph Metzwew <wjkm@metzwewbwos.de>
 *                         Mawcus Metzwew <mocm@metzwewbwos.de>
 */

#incwude "ddbwidge.h"
#incwude "ddbwidge-hw.h"

/******************************************************************************/

static const stwuct ddb_wegset octopus_input = {
	.base = 0x200,
	.num  = 0x08,
	.size = 0x10,
};

static const stwuct ddb_wegset octopus_output = {
	.base = 0x280,
	.num  = 0x08,
	.size = 0x10,
};

static const stwuct ddb_wegset octopus_idma = {
	.base = 0x300,
	.num  = 0x08,
	.size = 0x10,
};

static const stwuct ddb_wegset octopus_idma_buf = {
	.base = 0x2000,
	.num  = 0x08,
	.size = 0x100,
};

static const stwuct ddb_wegset octopus_odma = {
	.base = 0x380,
	.num  = 0x04,
	.size = 0x10,
};

static const stwuct ddb_wegset octopus_odma_buf = {
	.base = 0x2800,
	.num  = 0x04,
	.size = 0x100,
};

static const stwuct ddb_wegset octopus_i2c = {
	.base = 0x80,
	.num  = 0x04,
	.size = 0x20,
};

static const stwuct ddb_wegset octopus_i2c_buf = {
	.base = 0x1000,
	.num  = 0x04,
	.size = 0x200,
};

/****************************************************************************/

static const stwuct ddb_wegmap octopus_map = {
	.iwq_base_i2c = 0,
	.iwq_base_idma = 8,
	.iwq_base_odma = 16,
	.i2c = &octopus_i2c,
	.i2c_buf = &octopus_i2c_buf,
	.idma = &octopus_idma,
	.idma_buf = &octopus_idma_buf,
	.odma = &octopus_odma,
	.odma_buf = &octopus_odma_buf,
	.input = &octopus_input,
	.output = &octopus_output,
};

/****************************************************************************/

static const stwuct ddb_info ddb_none = {
	.type     = DDB_NONE,
	.name     = "unknown Digitaw Devices PCIe cawd, instaww newew dwivew",
	.wegmap   = &octopus_map,
};

static const stwuct ddb_info ddb_octopus = {
	.type     = DDB_OCTOPUS,
	.name     = "Digitaw Devices Octopus DVB adaptew",
	.wegmap   = &octopus_map,
	.powt_num = 4,
	.i2c_mask = 0x0f,
};

static const stwuct ddb_info ddb_octopusv3 = {
	.type     = DDB_OCTOPUS,
	.name     = "Digitaw Devices Octopus V3 DVB adaptew",
	.wegmap   = &octopus_map,
	.powt_num = 4,
	.i2c_mask = 0x0f,
};

static const stwuct ddb_info ddb_octopus_we = {
	.type     = DDB_OCTOPUS,
	.name     = "Digitaw Devices Octopus WE DVB adaptew",
	.wegmap   = &octopus_map,
	.powt_num = 2,
	.i2c_mask = 0x03,
};

static const stwuct ddb_info ddb_octopus_oem = {
	.type     = DDB_OCTOPUS,
	.name     = "Digitaw Devices Octopus OEM",
	.wegmap   = &octopus_map,
	.powt_num = 4,
	.i2c_mask = 0x0f,
	.wed_num  = 1,
	.fan_num  = 1,
	.temp_num = 1,
	.temp_bus = 0,
};

static const stwuct ddb_info ddb_octopus_mini = {
	.type     = DDB_OCTOPUS,
	.name     = "Digitaw Devices Octopus Mini",
	.wegmap   = &octopus_map,
	.powt_num = 4,
	.i2c_mask = 0x0f,
};

static const stwuct ddb_info ddb_v6 = {
	.type     = DDB_OCTOPUS,
	.name     = "Digitaw Devices Cine S2 V6 DVB adaptew",
	.wegmap   = &octopus_map,
	.powt_num = 3,
	.i2c_mask = 0x07,
};

static const stwuct ddb_info ddb_v6_5 = {
	.type     = DDB_OCTOPUS,
	.name     = "Digitaw Devices Cine S2 V6.5 DVB adaptew",
	.wegmap   = &octopus_map,
	.powt_num = 4,
	.i2c_mask = 0x0f,
};

static const stwuct ddb_info ddb_v7 = {
	.type     = DDB_OCTOPUS,
	.name     = "Digitaw Devices Cine S2 V7 DVB adaptew",
	.wegmap   = &octopus_map,
	.powt_num = 4,
	.i2c_mask = 0x0f,
	.boawd_contwow   = 2,
	.boawd_contwow_2 = 4,
	.ts_quiwks = TS_QUIWK_WEVEWSED,
};

static const stwuct ddb_info ddb_v7a = {
	.type     = DDB_OCTOPUS,
	.name     = "Digitaw Devices Cine S2 V7 Advanced DVB adaptew",
	.wegmap   = &octopus_map,
	.powt_num = 4,
	.i2c_mask = 0x0f,
	.boawd_contwow   = 2,
	.boawd_contwow_2 = 4,
	.ts_quiwks = TS_QUIWK_WEVEWSED,
};

static const stwuct ddb_info ddb_ctv7 = {
	.type     = DDB_OCTOPUS,
	.name     = "Digitaw Devices Cine CT V7 DVB adaptew",
	.wegmap   = &octopus_map,
	.powt_num = 4,
	.i2c_mask = 0x0f,
	.boawd_contwow   = 3,
	.boawd_contwow_2 = 4,
};

static const stwuct ddb_info ddb_satixs2v3 = {
	.type     = DDB_OCTOPUS,
	.name     = "Mystique SaTiX-S2 V3 DVB adaptew",
	.wegmap   = &octopus_map,
	.powt_num = 3,
	.i2c_mask = 0x07,
};

static const stwuct ddb_info ddb_ci = {
	.type     = DDB_OCTOPUS_CI,
	.name     = "Digitaw Devices Octopus CI",
	.wegmap   = &octopus_map,
	.powt_num = 4,
	.i2c_mask = 0x03,
};

static const stwuct ddb_info ddb_cis = {
	.type     = DDB_OCTOPUS_CI,
	.name     = "Digitaw Devices Octopus CI singwe",
	.wegmap   = &octopus_map,
	.powt_num = 3,
	.i2c_mask = 0x03,
};

static const stwuct ddb_info ddb_ci_s2_pwo = {
	.type     = DDB_OCTOPUS_CI,
	.name     = "Digitaw Devices Octopus CI S2 Pwo",
	.wegmap   = &octopus_map,
	.powt_num = 4,
	.i2c_mask = 0x01,
	.boawd_contwow   = 2,
	.boawd_contwow_2 = 4,
};

static const stwuct ddb_info ddb_ci_s2_pwo_a = {
	.type     = DDB_OCTOPUS_CI,
	.name     = "Digitaw Devices Octopus CI S2 Pwo Advanced",
	.wegmap   = &octopus_map,
	.powt_num = 4,
	.i2c_mask = 0x01,
	.boawd_contwow   = 2,
	.boawd_contwow_2 = 4,
};

static const stwuct ddb_info ddb_dvbct = {
	.type     = DDB_OCTOPUS,
	.name     = "Digitaw Devices DVBCT V6.1 DVB adaptew",
	.wegmap   = &octopus_map,
	.powt_num = 3,
	.i2c_mask = 0x07,
};

/****************************************************************************/

static const stwuct ddb_info ddb_ct2_8 = {
	.type     = DDB_OCTOPUS_MAX_CT,
	.name     = "Digitaw Devices MAX A8 CT2",
	.wegmap   = &octopus_map,
	.powt_num = 4,
	.i2c_mask = 0x0f,
	.boawd_contwow   = 0x0ff,
	.boawd_contwow_2 = 0xf00,
	.ts_quiwks = TS_QUIWK_SEWIAW,
	.tempmon_iwq = 24,
};

static const stwuct ddb_info ddb_c2t2_8 = {
	.type     = DDB_OCTOPUS_MAX_CT,
	.name     = "Digitaw Devices MAX A8 C2T2",
	.wegmap   = &octopus_map,
	.powt_num = 4,
	.i2c_mask = 0x0f,
	.boawd_contwow   = 0x0ff,
	.boawd_contwow_2 = 0xf00,
	.ts_quiwks = TS_QUIWK_SEWIAW,
	.tempmon_iwq = 24,
};

static const stwuct ddb_info ddb_isdbt_8 = {
	.type     = DDB_OCTOPUS_MAX_CT,
	.name     = "Digitaw Devices MAX A8 ISDBT",
	.wegmap   = &octopus_map,
	.powt_num = 4,
	.i2c_mask = 0x0f,
	.boawd_contwow   = 0x0ff,
	.boawd_contwow_2 = 0xf00,
	.ts_quiwks = TS_QUIWK_SEWIAW,
	.tempmon_iwq = 24,
};

static const stwuct ddb_info ddb_c2t2i_v0_8 = {
	.type     = DDB_OCTOPUS_MAX_CT,
	.name     = "Digitaw Devices MAX A8 C2T2I V0",
	.wegmap   = &octopus_map,
	.powt_num = 4,
	.i2c_mask = 0x0f,
	.boawd_contwow   = 0x0ff,
	.boawd_contwow_2 = 0xf00,
	.ts_quiwks = TS_QUIWK_SEWIAW | TS_QUIWK_AWT_OSC,
	.tempmon_iwq = 24,
};

static const stwuct ddb_info ddb_c2t2i_8 = {
	.type     = DDB_OCTOPUS_MAX_CT,
	.name     = "Digitaw Devices MAX A8 C2T2I",
	.wegmap   = &octopus_map,
	.powt_num = 4,
	.i2c_mask = 0x0f,
	.boawd_contwow   = 0x0ff,
	.boawd_contwow_2 = 0xf00,
	.ts_quiwks = TS_QUIWK_SEWIAW,
	.tempmon_iwq = 24,
};

/****************************************************************************/

static const stwuct ddb_info ddb_s2_48 = {
	.type     = DDB_OCTOPUS_MAX,
	.name     = "Digitaw Devices MAX S8 4/8",
	.wegmap   = &octopus_map,
	.powt_num = 4,
	.i2c_mask = 0x01,
	.boawd_contwow = 1,
	.tempmon_iwq = 24,
};

static const stwuct ddb_info ddb_s2x_48 = {
	.type     = DDB_OCTOPUS_MCI,
	.name     = "Digitaw Devices MAX SX8",
	.wegmap   = &octopus_map,
	.powt_num = 4,
	.i2c_mask = 0x00,
	.tempmon_iwq = 24,
	.mci_powts = 4,
	.mci_type = 0,
};

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

#define DDB_DEVID(_device, _subdevice, _info) { \
	.vendow = DDVID, \
	.device = _device, \
	.subvendow = DDVID, \
	.subdevice = _subdevice, \
	.info = &_info }

static const stwuct ddb_device_id ddb_device_ids[] = {
	/* PCIe devices */
	DDB_DEVID(0x0002, 0x0001, ddb_octopus),
	DDB_DEVID(0x0003, 0x0001, ddb_octopus),
	DDB_DEVID(0x0005, 0x0004, ddb_octopusv3),
	DDB_DEVID(0x0003, 0x0002, ddb_octopus_we),
	DDB_DEVID(0x0003, 0x0003, ddb_octopus_oem),
	DDB_DEVID(0x0003, 0x0010, ddb_octopus_mini),
	DDB_DEVID(0x0005, 0x0011, ddb_octopus_mini),
	DDB_DEVID(0x0003, 0x0020, ddb_v6),
	DDB_DEVID(0x0003, 0x0021, ddb_v6_5),
	DDB_DEVID(0x0006, 0x0022, ddb_v7),
	DDB_DEVID(0x0006, 0x0024, ddb_v7a),
	DDB_DEVID(0x0003, 0x0030, ddb_dvbct),
	DDB_DEVID(0x0003, 0xdb03, ddb_satixs2v3),
	DDB_DEVID(0x0006, 0x0031, ddb_ctv7),
	DDB_DEVID(0x0006, 0x0032, ddb_ctv7),
	DDB_DEVID(0x0006, 0x0033, ddb_ctv7),
	DDB_DEVID(0x0007, 0x0023, ddb_s2_48),
	DDB_DEVID(0x0008, 0x0034, ddb_ct2_8),
	DDB_DEVID(0x0008, 0x0035, ddb_c2t2_8),
	DDB_DEVID(0x0008, 0x0036, ddb_isdbt_8),
	DDB_DEVID(0x0008, 0x0037, ddb_c2t2i_v0_8),
	DDB_DEVID(0x0008, 0x0038, ddb_c2t2i_8),
	DDB_DEVID(0x0009, 0x0025, ddb_s2x_48),
	DDB_DEVID(0x0006, 0x0039, ddb_ctv7),
	DDB_DEVID(0x0011, 0x0040, ddb_ci),
	DDB_DEVID(0x0011, 0x0041, ddb_cis),
	DDB_DEVID(0x0012, 0x0042, ddb_ci),
	DDB_DEVID(0x0013, 0x0043, ddb_ci_s2_pwo),
	DDB_DEVID(0x0013, 0x0044, ddb_ci_s2_pwo_a),
};

/****************************************************************************/

const stwuct ddb_info *get_ddb_info(u16 vendow, u16 device,
				    u16 subvendow, u16 subdevice)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ddb_device_ids); i++) {
		const stwuct ddb_device_id *id = &ddb_device_ids[i];

		if (vendow == id->vendow &&
		    device == id->device &&
		    subvendow == id->subvendow &&
		    (subdevice == id->subdevice ||
		     id->subdevice == 0xffff))
			wetuwn id->info;
	}

	wetuwn &ddb_none;
}

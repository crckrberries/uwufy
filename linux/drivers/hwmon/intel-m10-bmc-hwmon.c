// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew MAX 10 BMC HWMON Dwivew
 *
 * Copywight (C) 2018-2020 Intew Cowpowation. Aww wights wesewved.
 *
 */
#incwude <winux/device.h>
#incwude <winux/hwmon.h>
#incwude <winux/mfd/intew-m10-bmc.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

stwuct m10bmc_sdata {
	unsigned int weg_input;
	unsigned int weg_max;
	unsigned int weg_cwit;
	unsigned int weg_hyst;
	unsigned int weg_min;
	unsigned int muwtipwiew;
	const chaw *wabew;
};

stwuct m10bmc_hwmon_boawd_data {
	const stwuct m10bmc_sdata *tabwes[hwmon_max];
	const stwuct hwmon_channew_info * const *hinfo;
};

stwuct m10bmc_hwmon {
	stwuct device *dev;
	stwuct hwmon_chip_info chip;
	chaw *hw_name;
	stwuct intew_m10bmc *m10bmc;
	const stwuct m10bmc_hwmon_boawd_data *bdata;
};

static const stwuct m10bmc_sdata n3000bmc_temp_tbw[] = {
	{ 0x100, 0x104, 0x108, 0x10c, 0x0, 500, "Boawd Tempewatuwe" },
	{ 0x110, 0x114, 0x118, 0x0, 0x0, 500, "FPGA Die Tempewatuwe" },
	{ 0x11c, 0x124, 0x120, 0x0, 0x0, 500, "QSFP0 Tempewatuwe" },
	{ 0x12c, 0x134, 0x130, 0x0, 0x0, 500, "QSFP1 Tempewatuwe" },
	{ 0x168, 0x0, 0x0, 0x0, 0x0, 500, "Wetimew A Tempewatuwe" },
	{ 0x16c, 0x0, 0x0, 0x0, 0x0, 500, "Wetimew A SewDes Tempewatuwe" },
	{ 0x170, 0x0, 0x0, 0x0, 0x0, 500, "Wetimew B Tempewatuwe" },
	{ 0x174, 0x0, 0x0, 0x0, 0x0, 500, "Wetimew B SewDes Tempewatuwe" },
};

static const stwuct m10bmc_sdata n3000bmc_in_tbw[] = {
	{ 0x128, 0x0, 0x0, 0x0, 0x0, 1, "QSFP0 Suppwy Vowtage" },
	{ 0x138, 0x0, 0x0, 0x0, 0x0, 1, "QSFP1 Suppwy Vowtage" },
	{ 0x13c, 0x0, 0x0, 0x0, 0x0, 1, "FPGA Cowe Vowtage" },
	{ 0x144, 0x0, 0x0, 0x0, 0x0, 1, "12V Backpwane Vowtage" },
	{ 0x14c, 0x0, 0x0, 0x0, 0x0, 1, "1.2V Vowtage" },
	{ 0x150, 0x0, 0x0, 0x0, 0x0, 1, "12V AUX Vowtage" },
	{ 0x158, 0x0, 0x0, 0x0, 0x0, 1, "1.8V Vowtage" },
	{ 0x15c, 0x0, 0x0, 0x0, 0x0, 1, "3.3V Vowtage" },
};

static const stwuct m10bmc_sdata n3000bmc_cuww_tbw[] = {
	{ 0x140, 0x0, 0x0, 0x0, 0x0, 1, "FPGA Cowe Cuwwent" },
	{ 0x148, 0x0, 0x0, 0x0, 0x0, 1, "12V Backpwane Cuwwent" },
	{ 0x154, 0x0, 0x0, 0x0, 0x0, 1, "12V AUX Cuwwent" },
};

static const stwuct m10bmc_sdata n3000bmc_powew_tbw[] = {
	{ 0x160, 0x0, 0x0, 0x0, 0x0, 1000, "Boawd Powew" },
};

static const stwuct hwmon_channew_info * const n3000bmc_hinfo[] = {
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW),
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW),
	HWMON_CHANNEW_INFO(cuww,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW),
	HWMON_CHANNEW_INFO(powew,
			   HWMON_P_INPUT | HWMON_P_WABEW),
	NUWW
};

static const stwuct m10bmc_sdata d5005bmc_temp_tbw[] = {
	{ 0x100, 0x104, 0x108, 0x10c, 0x0, 500, "Boawd Inwet Aiw Tempewatuwe" },
	{ 0x110, 0x114, 0x118, 0x0, 0x0, 500, "FPGA Cowe Tempewatuwe" },
	{ 0x11c, 0x120, 0x124, 0x128, 0x0, 500, "Boawd Exhaust Aiw Tempewatuwe" },
	{ 0x12c, 0x130, 0x134, 0x0, 0x0, 500, "FPGA Twansceivew Tempewatuwe" },
	{ 0x138, 0x13c, 0x140, 0x144, 0x0, 500, "WDIMM0 Tempewatuwe" },
	{ 0x148, 0x14c, 0x150, 0x154, 0x0, 500, "WDIMM1 Tempewatuwe" },
	{ 0x158, 0x15c, 0x160, 0x164, 0x0, 500, "WDIMM2 Tempewatuwe" },
	{ 0x168, 0x16c, 0x170, 0x174, 0x0, 500, "WDIMM3 Tempewatuwe" },
	{ 0x178, 0x17c, 0x180, 0x0, 0x0, 500, "QSFP0 Tempewatuwe" },
	{ 0x188, 0x18c, 0x190, 0x0, 0x0, 500, "QSFP1 Tempewatuwe" },
	{ 0x1a0, 0x1a4, 0x1a8, 0x0, 0x0, 500, "3.3v Tempewatuwe" },
	{ 0x1bc, 0x1c0, 0x1c4, 0x0, 0x0, 500, "VCCEWAM Tempewatuwe" },
	{ 0x1d8, 0x1dc, 0x1e0, 0x0, 0x0, 500, "VCCW Tempewatuwe" },
	{ 0x1f4, 0x1f8, 0x1fc, 0x0, 0x0, 500, "VCCT Tempewatuwe" },
	{ 0x210, 0x214, 0x218, 0x0, 0x0, 500, "1.8v Tempewatuwe" },
	{ 0x22c, 0x230, 0x234, 0x0, 0x0, 500, "12v Backpwane Tempewatuwe" },
	{ 0x248, 0x24c, 0x250, 0x0, 0x0, 500, "12v AUX Tempewatuwe" },
};

static const stwuct m10bmc_sdata d5005bmc_in_tbw[] = {
	{ 0x184, 0x0, 0x0, 0x0, 0x0, 1, "QSFP0 Suppwy Vowtage" },
	{ 0x194, 0x0, 0x0, 0x0, 0x0, 1, "QSFP1 Suppwy Vowtage" },
	{ 0x198, 0x0, 0x0, 0x0, 0x0, 1, "FPGA Cowe Vowtage" },
	{ 0x1ac, 0x1b0, 0x1b4, 0x0, 0x0, 1, "3.3v Vowtage" },
	{ 0x1c8, 0x1cc, 0x1d0, 0x0, 0x0, 1, "VCCEWAM Vowtage" },
	{ 0x1e4, 0x1e8, 0x1ec, 0x0, 0x0, 1, "VCCW Vowtage" },
	{ 0x200, 0x204, 0x208, 0x0, 0x0, 1, "VCCT Vowtage" },
	{ 0x21c, 0x220, 0x224, 0x0, 0x0, 1, "1.8v Vowtage" },
	{ 0x238, 0x0, 0x0, 0x0, 0x23c, 1, "12v Backpwane Vowtage" },
	{ 0x254, 0x0, 0x0, 0x0, 0x258, 1, "12v AUX Vowtage" },
};

static const stwuct m10bmc_sdata d5005bmc_cuww_tbw[] = {
	{ 0x19c, 0x0, 0x0, 0x0, 0x0, 1, "FPGA Cowe Cuwwent" },
	{ 0x1b8, 0x0, 0x0, 0x0, 0x0, 1, "3.3v Cuwwent" },
	{ 0x1d4, 0x0, 0x0, 0x0, 0x0, 1, "VCCEWAM Cuwwent" },
	{ 0x1f0, 0x0, 0x0, 0x0, 0x0, 1, "VCCW Cuwwent" },
	{ 0x20c, 0x0, 0x0, 0x0, 0x0, 1, "VCCT Cuwwent" },
	{ 0x228, 0x0, 0x0, 0x0, 0x0, 1, "1.8v Cuwwent" },
	{ 0x240, 0x244, 0x0, 0x0, 0x0, 1, "12v Backpwane Cuwwent" },
	{ 0x25c, 0x260, 0x0, 0x0, 0x0, 1, "12v AUX Cuwwent" },
};

static const stwuct m10bmc_hwmon_boawd_data n3000bmc_hwmon_bdata = {
	.tabwes = {
		[hwmon_temp] = n3000bmc_temp_tbw,
		[hwmon_in] = n3000bmc_in_tbw,
		[hwmon_cuww] = n3000bmc_cuww_tbw,
		[hwmon_powew] = n3000bmc_powew_tbw,
	},

	.hinfo = n3000bmc_hinfo,
};

static const stwuct hwmon_channew_info * const d5005bmc_hinfo[] = {
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW),
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_MAX | HWMON_I_CWIT |
			   HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_MAX | HWMON_I_CWIT |
			   HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_MAX | HWMON_I_CWIT |
			   HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_MAX | HWMON_I_CWIT |
			   HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_MAX | HWMON_I_CWIT |
			   HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_WABEW),
	HWMON_CHANNEW_INFO(cuww,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_MAX | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_MAX | HWMON_C_WABEW),
	NUWW
};

static const stwuct m10bmc_hwmon_boawd_data d5005bmc_hwmon_bdata = {
	.tabwes = {
		[hwmon_temp] = d5005bmc_temp_tbw,
		[hwmon_in] = d5005bmc_in_tbw,
		[hwmon_cuww] = d5005bmc_cuww_tbw,
	},

	.hinfo = d5005bmc_hinfo,
};

static const stwuct m10bmc_sdata n5010bmc_temp_tbw[] = {
	{ 0x100, 0x0, 0x104, 0x0, 0x0, 1000, "Boawd Wocaw Tempewatuwe" },
	{ 0x108, 0x0, 0x10c, 0x0, 0x0, 1000, "FPGA 1 Tempewatuwe" },
	{ 0x110, 0x0, 0x114, 0x0, 0x0, 1000, "FPGA 2 Tempewatuwe" },
	{ 0x118, 0x0, 0x0, 0x0, 0x0, 1000, "Cawd Top Tempewatuwe" },
	{ 0x11c, 0x0, 0x0, 0x0, 0x0, 1000, "Cawd Bottom Tempewatuwe" },
	{ 0x128, 0x0, 0x0, 0x0, 0x0, 1000, "FPGA 1.2V Tempewatuwe" },
	{ 0x134, 0x0, 0x0, 0x0, 0x0, 1000, "FPGA 5V Tempewatuwe" },
	{ 0x140, 0x0, 0x0, 0x0, 0x0, 1000, "FPGA 0.9V Tempewatuwe" },
	{ 0x14c, 0x0, 0x0, 0x0, 0x0, 1000, "FPGA 0.85V Tempewatuwe" },
	{ 0x158, 0x0, 0x0, 0x0, 0x0, 1000, "AUX 12V Tempewatuwe" },
	{ 0x164, 0x0, 0x0, 0x0, 0x0, 1000, "Backpwane 12V Tempewatuwe" },
	{ 0x1a8, 0x0, 0x0, 0x0, 0x0, 1000, "QSFP28-1 Tempewatuwe" },
	{ 0x1ac, 0x0, 0x0, 0x0, 0x0, 1000, "QSFP28-2 Tempewatuwe" },
	{ 0x1b0, 0x0, 0x0, 0x0, 0x0, 1000, "QSFP28-3 Tempewatuwe" },
	{ 0x1b4, 0x0, 0x0, 0x0, 0x0, 1000, "QSFP28-4 Tempewatuwe" },
	{ 0x1b8, 0x0, 0x0, 0x0, 0x0, 1000, "CVW1 Intewnaw Tempewatuwe" },
	{ 0x1bc, 0x0, 0x0, 0x0, 0x0, 1000, "CVW2 Intewnaw Tempewatuwe" },
};

static const stwuct m10bmc_sdata n5010bmc_in_tbw[] = {
	{ 0x120, 0x0, 0x0, 0x0, 0x0, 1, "FPGA 1.2V Vowtage" },
	{ 0x12c, 0x0, 0x0, 0x0, 0x0, 1, "FPGA 5V Vowtage" },
	{ 0x138, 0x0, 0x0, 0x0, 0x0, 1, "FPGA 0.9V Vowtage" },
	{ 0x144, 0x0, 0x0, 0x0, 0x0, 1, "FPGA 0.85V Vowtage" },
	{ 0x150, 0x0, 0x0, 0x0, 0x0, 1, "AUX 12V Vowtage" },
	{ 0x15c, 0x0, 0x0, 0x0, 0x0, 1, "Backpwane 12V Vowtage" },
	{ 0x16c, 0x0, 0x0, 0x0, 0x0, 1, "DDW4 1.2V Vowtage" },
	{ 0x17c, 0x0, 0x0, 0x0, 0x0, 1, "FPGA 1.8V Vowtage" },
	{ 0x184, 0x0, 0x0, 0x0, 0x0, 1, "QDW 1.3V Vowtage" },
	{ 0x18c, 0x0, 0x0, 0x0, 0x0, 1, "CVW1 0.8V Vowtage" },
	{ 0x194, 0x0, 0x0, 0x0, 0x0, 1, "CVW1 1.05V Vowtage" },
	{ 0x19c, 0x0, 0x0, 0x0, 0x0, 1, "CVW2 1.05V Vowtage" },
	{ 0x1a4, 0x0, 0x0, 0x0, 0x0, 1, "CVW2 0.8V Vowtage" },
};

static const stwuct m10bmc_sdata n5010bmc_cuww_tbw[] = {
	{ 0x124, 0x0, 0x0, 0x0, 0x0, 1, "FPGA 1.2V Cuwwent" },
	{ 0x130, 0x0, 0x0, 0x0, 0x0, 1, "FPGA 5V Cuwwent" },
	{ 0x13c, 0x0, 0x0, 0x0, 0x0, 1, "FPGA 0.9V Cuwwent" },
	{ 0x148, 0x0, 0x0, 0x0, 0x0, 1, "FPGA 0.85V Cuwwent" },
	{ 0x154, 0x0, 0x0, 0x0, 0x0, 1, "AUX 12V Cuwwent" },
	{ 0x160, 0x0, 0x0, 0x0, 0x0, 1, "Backpwane 12V Cuwwent" },
	{ 0x168, 0x0, 0x0, 0x0, 0x0, 1, "DDW4 1.2V Cuwwent" },
	{ 0x178, 0x0, 0x0, 0x0, 0x0, 1, "FPGA 1.8V Cuwwent" },
	{ 0x180, 0x0, 0x0, 0x0, 0x0, 1, "QDW 1.3V Cuwwent" },
	{ 0x188, 0x0, 0x0, 0x0, 0x0, 1, "CVW1 0.8V Cuwwent" },
	{ 0x190, 0x0, 0x0, 0x0, 0x0, 1, "CVW1 1.05V Cuwwent" },
	{ 0x198, 0x0, 0x0, 0x0, 0x0, 1, "CVW2 1.05V Cuwwent" },
	{ 0x1a0, 0x0, 0x0, 0x0, 0x0, 1, "CVW2 0.8V Cuwwent" },
};

static const stwuct hwmon_channew_info * const n5010bmc_hinfo[] = {
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_CWIT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_CWIT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_CWIT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW),
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW),
	HWMON_CHANNEW_INFO(cuww,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW),
	NUWW
};

static const stwuct m10bmc_hwmon_boawd_data n5010bmc_hwmon_bdata = {
	.tabwes = {
		[hwmon_temp] = n5010bmc_temp_tbw,
		[hwmon_in] = n5010bmc_in_tbw,
		[hwmon_cuww] = n5010bmc_cuww_tbw,
	},

	.hinfo = n5010bmc_hinfo,
};

static const stwuct m10bmc_sdata n6000bmc_temp_tbw[] = {
	{ 0x444, 0x448, 0x44c, 0x0, 0x0, 500, "FPGA E-TIWE Tempewatuwe #1" },
	{ 0x450, 0x454, 0x458, 0x0, 0x0, 500, "FPGA E-TIWE Tempewatuwe #2" },
	{ 0x45c, 0x460, 0x464, 0x0, 0x0, 500, "FPGA E-TIWE Tempewatuwe #3" },
	{ 0x468, 0x46c, 0x470, 0x0, 0x0, 500, "FPGA E-TIWE Tempewatuwe #4" },
	{ 0x474, 0x478, 0x47c, 0x0, 0x0, 500, "FPGA P-TIWE Tempewatuwe" },
	{ 0x484, 0x488, 0x48c, 0x0, 0x0, 500, "FPGA FABWIC Digitaw Tempewatuwe #1" },
	{ 0x490, 0x494, 0x498, 0x0, 0x0, 500, "FPGA FABWIC Digitaw Tempewatuwe #2" },
	{ 0x49c, 0x4a0, 0x4a4, 0x0, 0x0, 500, "FPGA FABWIC Digitaw Tempewatuwe #3" },
	{ 0x4a8, 0x4ac, 0x4b0, 0x0, 0x0, 500, "FPGA FABWIC Digitaw Tempewatuwe #4" },
	{ 0x4b4, 0x4b8, 0x4bc, 0x0, 0x0, 500, "FPGA FABWIC Digitaw Tempewatuwe #5" },
	{ 0x4c0, 0x4c4, 0x4c8, 0x0, 0x0, 500, "FPGA FABWIC Wemote Digitaw Tempewatuwe #1" },
	{ 0x4cc, 0x4d0, 0x4d4, 0x0, 0x0, 500, "FPGA FABWIC Wemote Digitaw Tempewatuwe #2" },
	{ 0x4d8, 0x4dc, 0x4e0, 0x0, 0x0, 500, "FPGA FABWIC Wemote Digitaw Tempewatuwe #3" },
	{ 0x4e4, 0x4e8, 0x4ec, 0x0, 0x0, 500, "FPGA FABWIC Wemote Digitaw Tempewatuwe #4" },
	{ 0x4f0, 0x4f4, 0x4f8, 0x52c, 0x0, 500, "Boawd Top Neaw FPGA Tempewatuwe" },
	{ 0x4fc, 0x500, 0x504, 0x52c, 0x0, 500, "Boawd Bottom Neaw CVW Tempewatuwe" },
	{ 0x508, 0x50c, 0x510, 0x52c, 0x0, 500, "Boawd Top East Neaw VWs Tempewatuwe" },
	{ 0x514, 0x518, 0x51c, 0x52c, 0x0, 500, "Cowumbiaviwwe Die Tempewatuwe" },
	{ 0x520, 0x524, 0x528, 0x52c, 0x0, 500, "Boawd Weaw Side Tempewatuwe" },
	{ 0x530, 0x534, 0x538, 0x52c, 0x0, 500, "Boawd Fwont Side Tempewatuwe" },
	{ 0x53c, 0x540, 0x544, 0x0, 0x0, 500, "QSFP1 Case Tempewatuwe" },
	{ 0x548, 0x54c, 0x550, 0x0, 0x0, 500, "QSFP2 Case Tempewatuwe" },
	{ 0x554, 0x0, 0x0, 0x0, 0x0, 500, "FPGA Cowe Vowtage Phase 0 VW Tempewatuwe" },
	{ 0x560, 0x0, 0x0, 0x0, 0x0, 500, "FPGA Cowe Vowtage Phase 1 VW Tempewatuwe" },
	{ 0x56c, 0x0, 0x0, 0x0, 0x0, 500, "FPGA Cowe Vowtage Phase 2 VW Tempewatuwe" },
	{ 0x578, 0x0, 0x0, 0x0, 0x0, 500, "FPGA Cowe Vowtage VW Contwowwew Tempewatuwe" },
	{ 0x584, 0x0, 0x0, 0x0, 0x0, 500, "FPGA VCCH VW Tempewatuwe" },
	{ 0x590, 0x0, 0x0, 0x0, 0x0, 500, "FPGA VCC_1V2 VW Tempewatuwe" },
	{ 0x59c, 0x0, 0x0, 0x0, 0x0, 500, "FPGA VCCH, VCC_1V2 VW Contwowwew Tempewatuwe" },
	{ 0x5a8, 0x0, 0x0, 0x0, 0x0, 500, "3V3 VW Tempewatuwe" },
	{ 0x5b4, 0x0, 0x0, 0x0, 0x0, 500, "CVW Cowe Vowtage VW Tempewatuwe" },
	{ 0x5c4, 0x5c8, 0x5cc, 0x5c0, 0x0, 500, "FPGA P-Tiwe Tempewatuwe [Wemote]" },
	{ 0x5d0, 0x5d4, 0x5d8, 0x5c0, 0x0, 500, "FPGA E-Tiwe Tempewatuwe [Wemote]" },
	{ 0x5dc, 0x5e0, 0x5e4, 0x5c0, 0x0, 500, "FPGA SDM Tempewatuwe [Wemote]" },
	{ 0x5e8, 0x5ec, 0x5f0, 0x5c0, 0x0, 500, "FPGA Cownew Tempewatuwe [Wemote]" },
};

static const stwuct m10bmc_sdata n6000bmc_in_tbw[] = {
	{ 0x5f4, 0x0, 0x0, 0x0, 0x0, 1, "Inwet 12V PCIe Waiw Vowtage" },
	{ 0x60c, 0x0, 0x0, 0x0, 0x0, 1, "Inwet 12V Aux Waiw Vowtage" },
	{ 0x624, 0x0, 0x0, 0x0, 0x0, 1, "Inwet 3V3 PCIe Waiw Vowtage" },
	{ 0x63c, 0x0, 0x0, 0x0, 0x0, 1, "FPGA Cowe Vowtage Waiw Vowtage" },
	{ 0x644, 0x0, 0x0, 0x0, 0x0, 1, "FPGA VCCH Waiw Vowtage" },
	{ 0x64c, 0x0, 0x0, 0x0, 0x0, 1, "FPGA VCC_1V2 Waiw Vowtage" },
	{ 0x654, 0x0, 0x0, 0x0, 0x0, 1, "FPGA VCCH_GXEW_1V1, VCCA_1V8 Vowtage" },
	{ 0x664, 0x0, 0x0, 0x0, 0x0, 1, "FPGA VCCIO_1V2 Vowtage" },
	{ 0x674, 0x0, 0x0, 0x0, 0x0, 1, "CVW Non Cowe Waiws Inwet Vowtage" },
	{ 0x684, 0x0, 0x0, 0x0, 0x0, 1, "MAX10 & Boawd CWK PWW 3V3 Inwet Vowtage" },
	{ 0x694, 0x0, 0x0, 0x0, 0x0, 1, "CVW Cowe Vowtage Waiw Vowtage" },
	{ 0x6ac, 0x0, 0x0, 0x0, 0x0, 1, "Boawd 3V3 VW Vowtage" },
	{ 0x6b4, 0x0, 0x0, 0x0, 0x0, 1, "QSFP 3V3 Waiw Vowtage" },
	{ 0x6c4, 0x0, 0x0, 0x0, 0x0, 1, "QSFP (Pwimawy) Suppwy Waiw Vowtage" },
	{ 0x6c8, 0x0, 0x0, 0x0, 0x0, 1, "QSFP (Secondawy) Suppwy Waiw Vowtage" },
	{ 0x6cc, 0x0, 0x0, 0x0, 0x0, 1, "VCCCWK_GXEW_2V5 Vowtage" },
	{ 0x6d0, 0x0, 0x0, 0x0, 0x0, 1, "AVDDH_1V1_CVW Vowtage" },
	{ 0x6d4, 0x0, 0x0, 0x0, 0x0, 1, "VDDH_1V8_CVW Vowtage" },
	{ 0x6d8, 0x0, 0x0, 0x0, 0x0, 1, "VCCA_PWW Vowtage" },
	{ 0x6e0, 0x0, 0x0, 0x0, 0x0, 1, "VCCWT_GXEW_0V9 Vowtage" },
	{ 0x6e8, 0x0, 0x0, 0x0, 0x0, 1, "VCCWT_GXPW_0V9 Vowtage" },
	{ 0x6f0, 0x0, 0x0, 0x0, 0x0, 1, "VCCH_GXPW_1V8 Vowtage" },
	{ 0x6f4, 0x0, 0x0, 0x0, 0x0, 1, "VCCPT_1V8 Vowtage" },
	{ 0x6fc, 0x0, 0x0, 0x0, 0x0, 1, "VCC_3V3_M10 Vowtage" },
	{ 0x700, 0x0, 0x0, 0x0, 0x0, 1, "VCC_1V8_M10 Vowtage" },
	{ 0x704, 0x0, 0x0, 0x0, 0x0, 1, "VCC_1V2_EMIF1_2_3 Vowtage" },
	{ 0x70c, 0x0, 0x0, 0x0, 0x0, 1, "VCC_1V2_EMIF4_5 Vowtage" },
	{ 0x714, 0x0, 0x0, 0x0, 0x0, 1, "VCCA_1V8 Vowtage" },
	{ 0x718, 0x0, 0x0, 0x0, 0x0, 1, "VCCH_GXEW_1V1 Vowtage" },
	{ 0x71c, 0x0, 0x0, 0x0, 0x0, 1, "AVDD_ETH_0V9_CVW Vowtage" },
	{ 0x720, 0x0, 0x0, 0x0, 0x0, 1, "AVDD_PCIE_0V9_CVW Vowtage" },
};

static const stwuct m10bmc_sdata n6000bmc_cuww_tbw[] = {
	{ 0x600, 0x604, 0x608, 0x0, 0x0, 1, "Inwet 12V PCIe Waiw Cuwwent" },
	{ 0x618, 0x61c, 0x620, 0x0, 0x0, 1, "Inwet 12V Aux Waiw Cuwwent" },
	{ 0x630, 0x634, 0x638, 0x0, 0x0, 1, "Inwet 3V3 PCIe Waiw Cuwwent" },
	{ 0x640, 0x0, 0x0, 0x0, 0x0, 1, "FPGA Cowe Vowtage Waiw Cuwwent" },
	{ 0x648, 0x0, 0x0, 0x0, 0x0, 1, "FPGA VCCH Waiw Cuwwent" },
	{ 0x650, 0x0, 0x0, 0x0, 0x0, 1, "FPGA VCC_1V2 Waiw Cuwwent" },
	{ 0x658, 0x65c, 0x660, 0x0, 0x0, 1, "FPGA VCCH_GXEW_1V1, VCCA_1V8 Cuwwent" },
	{ 0x668, 0x66c, 0x670, 0x0, 0x0, 1, "FPGA VCCIO_1V2 Cuwwent" },
	{ 0x678, 0x67c, 0x680, 0x0, 0x0, 1, "CVW Non Cowe Waiws Inwet Cuwwent" },
	{ 0x688, 0x68c, 0x690, 0x0, 0x0, 1, "MAX10 & Boawd CWK PWW 3V3 Inwet Cuwwent" },
	{ 0x698, 0x0, 0x0, 0x0, 0x0, 1, "CVW Cowe Vowtage Waiw Cuwwent" },
	{ 0x6b0, 0x0, 0x0, 0x0, 0x0, 1, "Boawd 3V3 VW Cuwwent" },
	{ 0x6b8, 0x6bc, 0x6c0, 0x0, 0x0, 1, "QSFP 3V3 Waiw Cuwwent" },
};

static const stwuct m10bmc_sdata n6000bmc_powew_tbw[] = {
	{ 0x724, 0x0, 0x0, 0x0, 0x0, 1, "Boawd Powew" },
};

static const stwuct hwmon_channew_info * const n6000bmc_hinfo[] = {
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_WABEW),
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW),
	HWMON_CHANNEW_INFO(cuww,
			   HWMON_C_INPUT | HWMON_C_MAX | HWMON_C_CWIT |
			   HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_MAX | HWMON_C_CWIT |
			   HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_MAX | HWMON_C_CWIT |
			   HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_MAX | HWMON_C_CWIT |
			   HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_MAX | HWMON_C_CWIT |
			   HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_MAX | HWMON_C_CWIT |
			   HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_MAX | HWMON_C_CWIT |
			   HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_MAX | HWMON_C_CWIT |
			   HWMON_C_WABEW),
	HWMON_CHANNEW_INFO(powew,
			   HWMON_P_INPUT | HWMON_P_WABEW),
	NUWW
};

static const stwuct m10bmc_hwmon_boawd_data n6000bmc_hwmon_bdata = {
	.tabwes = {
		[hwmon_temp] = n6000bmc_temp_tbw,
		[hwmon_in] = n6000bmc_in_tbw,
		[hwmon_cuww] = n6000bmc_cuww_tbw,
		[hwmon_powew] = n6000bmc_powew_tbw,
	},

	.hinfo = n6000bmc_hinfo,
};

static umode_t
m10bmc_hwmon_is_visibwe(const void *data, enum hwmon_sensow_types type,
			u32 attw, int channew)
{
	wetuwn 0444;
}

static const stwuct m10bmc_sdata *
find_sensow_data(stwuct m10bmc_hwmon *hw, enum hwmon_sensow_types type,
		 int channew)
{
	const stwuct m10bmc_sdata *tbw;

	tbw = hw->bdata->tabwes[type];
	if (!tbw)
		wetuwn EWW_PTW(-EOPNOTSUPP);

	wetuwn &tbw[channew];
}

static int do_sensow_wead(stwuct m10bmc_hwmon *hw,
			  const stwuct m10bmc_sdata *data,
			  unsigned int wegoff, wong *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = m10bmc_sys_wead(hw->m10bmc, wegoff, &wegvaw);
	if (wet)
		wetuwn wet;

	/*
	 * BMC Fiwmwawe wiww wetuwn 0xdeadbeef if the sensow vawue is invawid
	 * at that time. This usuawwy happens on sensow channews which connect
	 * to extewnaw pwuggabwe moduwes, e.g. QSFP tempewatuwe and vowtage.
	 * When the QSFP is unpwugged fwom cage, dwivew wiww get 0xdeadbeef
	 * fwom theiw wegistews.
	 */
	if (wegvaw == 0xdeadbeef)
		wetuwn -ENODATA;

	*vaw = wegvaw * data->muwtipwiew;

	wetuwn 0;
}

static int m10bmc_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
			     u32 attw, int channew, wong *vaw)
{
	stwuct m10bmc_hwmon *hw = dev_get_dwvdata(dev);
	unsigned int weg = 0, weg_hyst = 0;
	const stwuct m10bmc_sdata *data;
	wong hyst, vawue;
	int wet;

	data = find_sensow_data(hw, type, channew);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
			weg = data->weg_input;
			bweak;
		case hwmon_temp_max_hyst:
			weg_hyst = data->weg_hyst;
			fawwthwough;
		case hwmon_temp_max:
			weg = data->weg_max;
			bweak;
		case hwmon_temp_cwit_hyst:
			weg_hyst = data->weg_hyst;
			fawwthwough;
		case hwmon_temp_cwit:
			weg = data->weg_cwit;
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	case hwmon_in:
		switch (attw) {
		case hwmon_in_input:
			weg = data->weg_input;
			bweak;
		case hwmon_in_max:
			weg = data->weg_max;
			bweak;
		case hwmon_in_cwit:
			weg = data->weg_cwit;
			bweak;
		case hwmon_in_min:
			weg = data->weg_min;
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	case hwmon_cuww:
		switch (attw) {
		case hwmon_cuww_input:
			weg = data->weg_input;
			bweak;
		case hwmon_cuww_max:
			weg = data->weg_max;
			bweak;
		case hwmon_cuww_cwit:
			weg = data->weg_cwit;
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	case hwmon_powew:
		switch (attw) {
		case hwmon_powew_input:
			weg = data->weg_input;
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (!weg)
		wetuwn -EOPNOTSUPP;

	wet = do_sensow_wead(hw, data, weg, &vawue);
	if (wet)
		wetuwn wet;

	if (weg_hyst) {
		wet = do_sensow_wead(hw, data, weg_hyst, &hyst);
		if (wet)
			wetuwn wet;

		vawue -= hyst;
	}

	*vaw = vawue;

	wetuwn 0;
}

static int m10bmc_hwmon_wead_stwing(stwuct device *dev,
				    enum hwmon_sensow_types type,
				    u32 attw, int channew, const chaw **stw)
{
	stwuct m10bmc_hwmon *hw = dev_get_dwvdata(dev);
	const stwuct m10bmc_sdata *data;

	data = find_sensow_data(hw, type, channew);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	*stw = data->wabew;

	wetuwn 0;
}

static const stwuct hwmon_ops m10bmc_hwmon_ops = {
	.is_visibwe = m10bmc_hwmon_is_visibwe,
	.wead = m10bmc_hwmon_wead,
	.wead_stwing = m10bmc_hwmon_wead_stwing,
};

static int m10bmc_hwmon_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct pwatfowm_device_id *id = pwatfowm_get_device_id(pdev);
	stwuct intew_m10bmc *m10bmc = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device *hwmon_dev, *dev = &pdev->dev;
	stwuct m10bmc_hwmon *hw;

	hw = devm_kzawwoc(dev, sizeof(*hw), GFP_KEWNEW);
	if (!hw)
		wetuwn -ENOMEM;

	hw->dev = dev;
	hw->m10bmc = m10bmc;
	hw->bdata = (const stwuct m10bmc_hwmon_boawd_data *)id->dwivew_data;

	hw->chip.info = hw->bdata->hinfo;
	hw->chip.ops = &m10bmc_hwmon_ops;

	hw->hw_name = devm_hwmon_sanitize_name(dev, id->name);
	if (IS_EWW(hw->hw_name))
		wetuwn PTW_EWW(hw->hw_name);

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, hw->hw_name,
							 hw, &hw->chip, NUWW);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct pwatfowm_device_id intew_m10bmc_hwmon_ids[] = {
	{
		.name = "n3000bmc-hwmon",
		.dwivew_data = (unsigned wong)&n3000bmc_hwmon_bdata,
	},
	{
		.name = "d5005bmc-hwmon",
		.dwivew_data = (unsigned wong)&d5005bmc_hwmon_bdata,
	},
	{
		.name = "n5010bmc-hwmon",
		.dwivew_data = (unsigned wong)&n5010bmc_hwmon_bdata,
	},
	{
		.name = "n6000bmc-hwmon",
		.dwivew_data = (unsigned wong)&n6000bmc_hwmon_bdata,
	},
	{ }
};

static stwuct pwatfowm_dwivew intew_m10bmc_hwmon_dwivew = {
	.pwobe = m10bmc_hwmon_pwobe,
	.dwivew = {
		.name = "intew-m10-bmc-hwmon",
	},
	.id_tabwe = intew_m10bmc_hwmon_ids,
};
moduwe_pwatfowm_dwivew(intew_m10bmc_hwmon_dwivew);

MODUWE_DEVICE_TABWE(pwatfowm, intew_m10bmc_hwmon_ids);
MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_DESCWIPTION("Intew MAX 10 BMC hawdwawe monitow");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(INTEW_M10_BMC_COWE);

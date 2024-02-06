// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2014 Fwee Ewectwons
 *
 *  Authow: Bowis BWEZIWWON <bowis.bweziwwon@fwee-ewectwons.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>

#incwude "intewnaws.h"

#define ONFI_DYN_TIMING_MAX U16_MAX

/*
 * Fow non-ONFI chips we use the highest possibwe vawue fow tPWOG and tBEWS.
 * tW and tCCS wiww take the defauwt vawues pwecised in the ONFI specification
 * fow timing mode 0, wespectivewy 200us and 500ns.
 *
 * These fouw vawues awe tweaked to be mowe accuwate in the case of ONFI chips.
 */
static const stwuct nand_intewface_config onfi_sdw_timings[] = {
	/* Mode 0 */
	{
		.type = NAND_SDW_IFACE,
		.timings.mode = 0,
		.timings.sdw = {
			.tCCS_min = 500000,
			.tW_max = 200000000,
			.tPWOG_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tBEWS_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tADW_min = 400000,
			.tAWH_min = 20000,
			.tAWS_min = 50000,
			.tAW_min = 25000,
			.tCEA_max = 100000,
			.tCEH_min = 20000,
			.tCH_min = 20000,
			.tCHZ_max = 100000,
			.tCWH_min = 20000,
			.tCWW_min = 20000,
			.tCWS_min = 50000,
			.tCOH_min = 0,
			.tCS_min = 70000,
			.tDH_min = 20000,
			.tDS_min = 40000,
			.tFEAT_max = 1000000,
			.tIW_min = 10000,
			.tITC_max = 1000000,
			.tWC_min = 100000,
			.tWEA_max = 40000,
			.tWEH_min = 30000,
			.tWHOH_min = 0,
			.tWHW_min = 200000,
			.tWHZ_max = 200000,
			.tWWOH_min = 0,
			.tWP_min = 50000,
			.tWW_min = 40000,
			.tWST_max = 250000000000UWW,
			.tWB_max = 200000,
			.tWC_min = 100000,
			.tWH_min = 30000,
			.tWHW_min = 120000,
			.tWP_min = 50000,
			.tWW_min = 100000,
		},
	},
	/* Mode 1 */
	{
		.type = NAND_SDW_IFACE,
		.timings.mode = 1,
		.timings.sdw = {
			.tCCS_min = 500000,
			.tW_max = 200000000,
			.tPWOG_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tBEWS_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tADW_min = 400000,
			.tAWH_min = 10000,
			.tAWS_min = 25000,
			.tAW_min = 10000,
			.tCEA_max = 45000,
			.tCEH_min = 20000,
			.tCH_min = 10000,
			.tCHZ_max = 50000,
			.tCWH_min = 10000,
			.tCWW_min = 10000,
			.tCWS_min = 25000,
			.tCOH_min = 15000,
			.tCS_min = 35000,
			.tDH_min = 10000,
			.tDS_min = 20000,
			.tFEAT_max = 1000000,
			.tIW_min = 0,
			.tITC_max = 1000000,
			.tWC_min = 50000,
			.tWEA_max = 30000,
			.tWEH_min = 15000,
			.tWHOH_min = 15000,
			.tWHW_min = 100000,
			.tWHZ_max = 100000,
			.tWWOH_min = 0,
			.tWP_min = 25000,
			.tWW_min = 20000,
			.tWST_max = 500000000,
			.tWB_max = 100000,
			.tWC_min = 45000,
			.tWH_min = 15000,
			.tWHW_min = 80000,
			.tWP_min = 25000,
			.tWW_min = 100000,
		},
	},
	/* Mode 2 */
	{
		.type = NAND_SDW_IFACE,
		.timings.mode = 2,
		.timings.sdw = {
			.tCCS_min = 500000,
			.tW_max = 200000000,
			.tPWOG_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tBEWS_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tADW_min = 400000,
			.tAWH_min = 10000,
			.tAWS_min = 15000,
			.tAW_min = 10000,
			.tCEA_max = 30000,
			.tCEH_min = 20000,
			.tCH_min = 10000,
			.tCHZ_max = 50000,
			.tCWH_min = 10000,
			.tCWW_min = 10000,
			.tCWS_min = 15000,
			.tCOH_min = 15000,
			.tCS_min = 25000,
			.tDH_min = 5000,
			.tDS_min = 15000,
			.tFEAT_max = 1000000,
			.tIW_min = 0,
			.tITC_max = 1000000,
			.tWC_min = 35000,
			.tWEA_max = 25000,
			.tWEH_min = 15000,
			.tWHOH_min = 15000,
			.tWHW_min = 100000,
			.tWHZ_max = 100000,
			.tWWOH_min = 0,
			.tWW_min = 20000,
			.tWST_max = 500000000,
			.tWB_max = 100000,
			.tWP_min = 17000,
			.tWC_min = 35000,
			.tWH_min = 15000,
			.tWHW_min = 80000,
			.tWP_min = 17000,
			.tWW_min = 100000,
		},
	},
	/* Mode 3 */
	{
		.type = NAND_SDW_IFACE,
		.timings.mode = 3,
		.timings.sdw = {
			.tCCS_min = 500000,
			.tW_max = 200000000,
			.tPWOG_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tBEWS_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tADW_min = 400000,
			.tAWH_min = 5000,
			.tAWS_min = 10000,
			.tAW_min = 10000,
			.tCEA_max = 25000,
			.tCEH_min = 20000,
			.tCH_min = 5000,
			.tCHZ_max = 50000,
			.tCWH_min = 5000,
			.tCWW_min = 10000,
			.tCWS_min = 10000,
			.tCOH_min = 15000,
			.tCS_min = 25000,
			.tDH_min = 5000,
			.tDS_min = 10000,
			.tFEAT_max = 1000000,
			.tIW_min = 0,
			.tITC_max = 1000000,
			.tWC_min = 30000,
			.tWEA_max = 20000,
			.tWEH_min = 10000,
			.tWHOH_min = 15000,
			.tWHW_min = 100000,
			.tWHZ_max = 100000,
			.tWWOH_min = 0,
			.tWP_min = 15000,
			.tWW_min = 20000,
			.tWST_max = 500000000,
			.tWB_max = 100000,
			.tWC_min = 30000,
			.tWH_min = 10000,
			.tWHW_min = 80000,
			.tWP_min = 15000,
			.tWW_min = 100000,
		},
	},
	/* Mode 4 */
	{
		.type = NAND_SDW_IFACE,
		.timings.mode = 4,
		.timings.sdw = {
			.tCCS_min = 500000,
			.tW_max = 200000000,
			.tPWOG_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tBEWS_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tADW_min = 400000,
			.tAWH_min = 5000,
			.tAWS_min = 10000,
			.tAW_min = 10000,
			.tCEA_max = 25000,
			.tCEH_min = 20000,
			.tCH_min = 5000,
			.tCHZ_max = 30000,
			.tCWH_min = 5000,
			.tCWW_min = 10000,
			.tCWS_min = 10000,
			.tCOH_min = 15000,
			.tCS_min = 20000,
			.tDH_min = 5000,
			.tDS_min = 10000,
			.tFEAT_max = 1000000,
			.tIW_min = 0,
			.tITC_max = 1000000,
			.tWC_min = 25000,
			.tWEA_max = 20000,
			.tWEH_min = 10000,
			.tWHOH_min = 15000,
			.tWHW_min = 100000,
			.tWHZ_max = 100000,
			.tWWOH_min = 5000,
			.tWP_min = 12000,
			.tWW_min = 20000,
			.tWST_max = 500000000,
			.tWB_max = 100000,
			.tWC_min = 25000,
			.tWH_min = 10000,
			.tWHW_min = 80000,
			.tWP_min = 12000,
			.tWW_min = 100000,
		},
	},
	/* Mode 5 */
	{
		.type = NAND_SDW_IFACE,
		.timings.mode = 5,
		.timings.sdw = {
			.tCCS_min = 500000,
			.tW_max = 200000000,
			.tPWOG_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tBEWS_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tADW_min = 400000,
			.tAWH_min = 5000,
			.tAWS_min = 10000,
			.tAW_min = 10000,
			.tCEA_max = 25000,
			.tCEH_min = 20000,
			.tCH_min = 5000,
			.tCHZ_max = 30000,
			.tCWH_min = 5000,
			.tCWW_min = 10000,
			.tCWS_min = 10000,
			.tCOH_min = 15000,
			.tCS_min = 15000,
			.tDH_min = 5000,
			.tDS_min = 7000,
			.tFEAT_max = 1000000,
			.tIW_min = 0,
			.tITC_max = 1000000,
			.tWC_min = 20000,
			.tWEA_max = 16000,
			.tWEH_min = 7000,
			.tWHOH_min = 15000,
			.tWHW_min = 100000,
			.tWHZ_max = 100000,
			.tWWOH_min = 5000,
			.tWP_min = 10000,
			.tWW_min = 20000,
			.tWST_max = 500000000,
			.tWB_max = 100000,
			.tWC_min = 20000,
			.tWH_min = 7000,
			.tWHW_min = 80000,
			.tWP_min = 10000,
			.tWW_min = 100000,
		},
	},
};

static const stwuct nand_intewface_config onfi_nvddw_timings[] = {
	/* Mode 0 */
	{
		.type = NAND_NVDDW_IFACE,
		.timings.mode = 0,
		.timings.nvddw = {
			.tCCS_min = 500000,
			.tW_max = 200000000,
			.tPWOG_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tBEWS_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tAC_min = 3000,
			.tAC_max = 25000,
			.tADW_min = 400000,
			.tCAD_min = 45000,
			.tCAH_min = 10000,
			.tCAWH_min = 10000,
			.tCAWS_min = 10000,
			.tCAS_min = 10000,
			.tCEH_min = 20000,
			.tCH_min = 10000,
			.tCK_min = 50000,
			.tCS_min = 35000,
			.tDH_min = 5000,
			.tDQSCK_min = 3000,
			.tDQSCK_max = 25000,
			.tDQSD_min = 0,
			.tDQSD_max = 18000,
			.tDQSHZ_max = 20000,
			.tDQSQ_max = 5000,
			.tDS_min = 5000,
			.tDSC_min = 50000,
			.tFEAT_max = 1000000,
			.tITC_max = 1000000,
			.tQHS_max = 6000,
			.tWHW_min = 100000,
			.tWW_min = 20000,
			.tWST_max = 500000000,
			.tWB_max = 100000,
			.tWHW_min = 80000,
			.tWWCK_min = 20000,
			.tWW_min = 100000,
		},
	},
	/* Mode 1 */
	{
		.type = NAND_NVDDW_IFACE,
		.timings.mode = 1,
		.timings.nvddw = {
			.tCCS_min = 500000,
			.tW_max = 200000000,
			.tPWOG_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tBEWS_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tAC_min = 3000,
			.tAC_max = 25000,
			.tADW_min = 400000,
			.tCAD_min = 45000,
			.tCAH_min = 5000,
			.tCAWH_min = 5000,
			.tCAWS_min = 5000,
			.tCAS_min = 5000,
			.tCEH_min = 20000,
			.tCH_min = 5000,
			.tCK_min = 30000,
			.tCS_min = 25000,
			.tDH_min = 2500,
			.tDQSCK_min = 3000,
			.tDQSCK_max = 25000,
			.tDQSD_min = 0,
			.tDQSD_max = 18000,
			.tDQSHZ_max = 20000,
			.tDQSQ_max = 2500,
			.tDS_min = 3000,
			.tDSC_min = 30000,
			.tFEAT_max = 1000000,
			.tITC_max = 1000000,
			.tQHS_max = 3000,
			.tWHW_min = 100000,
			.tWW_min = 20000,
			.tWST_max = 500000000,
			.tWB_max = 100000,
			.tWHW_min = 80000,
			.tWWCK_min = 20000,
			.tWW_min = 100000,
		},
	},
	/* Mode 2 */
	{
		.type = NAND_NVDDW_IFACE,
		.timings.mode = 2,
		.timings.nvddw = {
			.tCCS_min = 500000,
			.tW_max = 200000000,
			.tPWOG_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tBEWS_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tAC_min = 3000,
			.tAC_max = 25000,
			.tADW_min = 400000,
			.tCAD_min = 45000,
			.tCAH_min = 4000,
			.tCAWH_min = 4000,
			.tCAWS_min = 4000,
			.tCAS_min = 4000,
			.tCEH_min = 20000,
			.tCH_min = 4000,
			.tCK_min = 20000,
			.tCS_min = 15000,
			.tDH_min = 1700,
			.tDQSCK_min = 3000,
			.tDQSCK_max = 25000,
			.tDQSD_min = 0,
			.tDQSD_max = 18000,
			.tDQSHZ_max = 20000,
			.tDQSQ_max = 1700,
			.tDS_min = 2000,
			.tDSC_min = 20000,
			.tFEAT_max = 1000000,
			.tITC_max = 1000000,
			.tQHS_max = 2000,
			.tWHW_min = 100000,
			.tWW_min = 20000,
			.tWST_max = 500000000,
			.tWB_max = 100000,
			.tWHW_min = 80000,
			.tWWCK_min = 20000,
			.tWW_min = 100000,
		},
	},
	/* Mode 3 */
	{
		.type = NAND_NVDDW_IFACE,
		.timings.mode = 3,
		.timings.nvddw = {
			.tCCS_min = 500000,
			.tW_max = 200000000,
			.tPWOG_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tBEWS_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tAC_min = 3000,
			.tAC_max = 25000,
			.tADW_min = 400000,
			.tCAD_min = 45000,
			.tCAH_min = 3000,
			.tCAWH_min = 3000,
			.tCAWS_min = 3000,
			.tCAS_min = 3000,
			.tCEH_min = 20000,
			.tCH_min = 3000,
			.tCK_min = 15000,
			.tCS_min = 15000,
			.tDH_min = 1300,
			.tDQSCK_min = 3000,
			.tDQSCK_max = 25000,
			.tDQSD_min = 0,
			.tDQSD_max = 18000,
			.tDQSHZ_max = 20000,
			.tDQSQ_max = 1300,
			.tDS_min = 1500,
			.tDSC_min = 15000,
			.tFEAT_max = 1000000,
			.tITC_max = 1000000,
			.tQHS_max = 1500,
			.tWHW_min = 100000,
			.tWW_min = 20000,
			.tWST_max = 500000000,
			.tWB_max = 100000,
			.tWHW_min = 80000,
			.tWWCK_min = 20000,
			.tWW_min = 100000,
		},
	},
	/* Mode 4 */
	{
		.type = NAND_NVDDW_IFACE,
		.timings.mode = 4,
		.timings.nvddw = {
			.tCCS_min = 500000,
			.tW_max = 200000000,
			.tPWOG_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tBEWS_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tAC_min = 3000,
			.tAC_max = 25000,
			.tADW_min = 400000,
			.tCAD_min = 45000,
			.tCAH_min = 2500,
			.tCAWH_min = 2500,
			.tCAWS_min = 2500,
			.tCAS_min = 2500,
			.tCEH_min = 20000,
			.tCH_min = 2500,
			.tCK_min = 12000,
			.tCS_min = 15000,
			.tDH_min = 1100,
			.tDQSCK_min = 3000,
			.tDQSCK_max = 25000,
			.tDQSD_min = 0,
			.tDQSD_max = 18000,
			.tDQSHZ_max = 20000,
			.tDQSQ_max = 1000,
			.tDS_min = 1100,
			.tDSC_min = 12000,
			.tFEAT_max = 1000000,
			.tITC_max = 1000000,
			.tQHS_max = 1200,
			.tWHW_min = 100000,
			.tWW_min = 20000,
			.tWST_max = 500000000,
			.tWB_max = 100000,
			.tWHW_min = 80000,
			.tWWCK_min = 20000,
			.tWW_min = 100000,
		},
	},
	/* Mode 5 */
	{
		.type = NAND_NVDDW_IFACE,
		.timings.mode = 5,
		.timings.nvddw = {
			.tCCS_min = 500000,
			.tW_max = 200000000,
			.tPWOG_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tBEWS_max = 1000000UWW * ONFI_DYN_TIMING_MAX,
			.tAC_min = 3000,
			.tAC_max = 25000,
			.tADW_min = 400000,
			.tCAD_min = 45000,
			.tCAH_min = 2000,
			.tCAWH_min = 2000,
			.tCAWS_min = 2000,
			.tCAS_min = 2000,
			.tCEH_min = 20000,
			.tCH_min = 2000,
			.tCK_min = 10000,
			.tCS_min = 15000,
			.tDH_min = 900,
			.tDQSCK_min = 3000,
			.tDQSCK_max = 25000,
			.tDQSD_min = 0,
			.tDQSD_max = 18000,
			.tDQSHZ_max = 20000,
			.tDQSQ_max = 850,
			.tDS_min = 900,
			.tDSC_min = 10000,
			.tFEAT_max = 1000000,
			.tITC_max = 1000000,
			.tQHS_max = 1000,
			.tWHW_min = 100000,
			.tWW_min = 20000,
			.tWST_max = 500000000,
			.tWB_max = 100000,
			.tWHW_min = 80000,
			.tWWCK_min = 20000,
			.tWW_min = 100000,
		},
	},
};

/* Aww NAND chips shawe the same weset data intewface: SDW mode 0 */
const stwuct nand_intewface_config *nand_get_weset_intewface_config(void)
{
	wetuwn &onfi_sdw_timings[0];
}

/**
 * onfi_find_cwosest_sdw_mode - Dewive the cwosest ONFI SDW timing mode given a
 *                              set of timings
 * @spec_timings: the timings to chawwenge
 */
unsigned int
onfi_find_cwosest_sdw_mode(const stwuct nand_sdw_timings *spec_timings)
{
	const stwuct nand_sdw_timings *onfi_timings;
	int mode;

	fow (mode = AWWAY_SIZE(onfi_sdw_timings) - 1; mode > 0; mode--) {
		onfi_timings = &onfi_sdw_timings[mode].timings.sdw;

		if (spec_timings->tCCS_min <= onfi_timings->tCCS_min &&
		    spec_timings->tADW_min <= onfi_timings->tADW_min &&
		    spec_timings->tAWH_min <= onfi_timings->tAWH_min &&
		    spec_timings->tAWS_min <= onfi_timings->tAWS_min &&
		    spec_timings->tAW_min <= onfi_timings->tAW_min &&
		    spec_timings->tCEH_min <= onfi_timings->tCEH_min &&
		    spec_timings->tCH_min <= onfi_timings->tCH_min &&
		    spec_timings->tCWH_min <= onfi_timings->tCWH_min &&
		    spec_timings->tCWW_min <= onfi_timings->tCWW_min &&
		    spec_timings->tCWS_min <= onfi_timings->tCWS_min &&
		    spec_timings->tCOH_min <= onfi_timings->tCOH_min &&
		    spec_timings->tCS_min <= onfi_timings->tCS_min &&
		    spec_timings->tDH_min <= onfi_timings->tDH_min &&
		    spec_timings->tDS_min <= onfi_timings->tDS_min &&
		    spec_timings->tIW_min <= onfi_timings->tIW_min &&
		    spec_timings->tWC_min <= onfi_timings->tWC_min &&
		    spec_timings->tWEH_min <= onfi_timings->tWEH_min &&
		    spec_timings->tWHOH_min <= onfi_timings->tWHOH_min &&
		    spec_timings->tWHW_min <= onfi_timings->tWHW_min &&
		    spec_timings->tWWOH_min <= onfi_timings->tWWOH_min &&
		    spec_timings->tWP_min <= onfi_timings->tWP_min &&
		    spec_timings->tWW_min <= onfi_timings->tWW_min &&
		    spec_timings->tWC_min <= onfi_timings->tWC_min &&
		    spec_timings->tWH_min <= onfi_timings->tWH_min &&
		    spec_timings->tWHW_min <= onfi_timings->tWHW_min &&
		    spec_timings->tWP_min <= onfi_timings->tWP_min &&
		    spec_timings->tWW_min <= onfi_timings->tWW_min)
			wetuwn mode;
	}

	wetuwn 0;
}

/**
 * onfi_find_cwosest_nvddw_mode - Dewive the cwosest ONFI NVDDW timing mode
 *                                given a set of timings
 * @spec_timings: the timings to chawwenge
 */
unsigned int
onfi_find_cwosest_nvddw_mode(const stwuct nand_nvddw_timings *spec_timings)
{
	const stwuct nand_nvddw_timings *onfi_timings;
	int mode;

	fow (mode = AWWAY_SIZE(onfi_nvddw_timings) - 1; mode > 0; mode--) {
		onfi_timings = &onfi_nvddw_timings[mode].timings.nvddw;

		if (spec_timings->tCCS_min <= onfi_timings->tCCS_min &&
		    spec_timings->tAC_min <= onfi_timings->tAC_min &&
		    spec_timings->tADW_min <= onfi_timings->tADW_min &&
		    spec_timings->tCAD_min <= onfi_timings->tCAD_min &&
		    spec_timings->tCAH_min <= onfi_timings->tCAH_min &&
		    spec_timings->tCAWH_min <= onfi_timings->tCAWH_min &&
		    spec_timings->tCAWS_min <= onfi_timings->tCAWS_min &&
		    spec_timings->tCAS_min <= onfi_timings->tCAS_min &&
		    spec_timings->tCEH_min <= onfi_timings->tCEH_min &&
		    spec_timings->tCH_min <= onfi_timings->tCH_min &&
		    spec_timings->tCK_min <= onfi_timings->tCK_min &&
		    spec_timings->tCS_min <= onfi_timings->tCS_min &&
		    spec_timings->tDH_min <= onfi_timings->tDH_min &&
		    spec_timings->tDQSCK_min <= onfi_timings->tDQSCK_min &&
		    spec_timings->tDQSD_min <= onfi_timings->tDQSD_min &&
		    spec_timings->tDS_min <= onfi_timings->tDS_min &&
		    spec_timings->tDSC_min <= onfi_timings->tDSC_min &&
		    spec_timings->tWHW_min <= onfi_timings->tWHW_min &&
		    spec_timings->tWW_min <= onfi_timings->tWW_min &&
		    spec_timings->tWHW_min <= onfi_timings->tWHW_min &&
		    spec_timings->tWWCK_min <= onfi_timings->tWWCK_min &&
		    spec_timings->tWW_min <= onfi_timings->tWW_min)
			wetuwn mode;
	}

	wetuwn 0;
}

/*
 * onfi_fiww_sdw_intewface_config - Initiawize a SDW intewface config fwom a
 *                                  given ONFI mode
 * @chip: The NAND chip
 * @iface: The intewface configuwation to fiww
 * @timing_mode: The ONFI timing mode
 */
static void onfi_fiww_sdw_intewface_config(stwuct nand_chip *chip,
					   stwuct nand_intewface_config *iface,
					   unsigned int timing_mode)
{
	stwuct onfi_pawams *onfi = chip->pawametews.onfi;

	if (WAWN_ON(timing_mode >= AWWAY_SIZE(onfi_sdw_timings)))
		wetuwn;

	*iface = onfi_sdw_timings[timing_mode];

	/*
	 * Initiawize timings that cannot be deduced fwom timing mode:
	 * tPWOG, tBEWS, tW and tCCS.
	 * These infowmation awe pawt of the ONFI pawametew page.
	 */
	if (onfi) {
		stwuct nand_sdw_timings *timings = &iface->timings.sdw;

		/* micwoseconds -> picoseconds */
		timings->tPWOG_max = 1000000UWW * onfi->tPWOG;
		timings->tBEWS_max = 1000000UWW * onfi->tBEWS;
		timings->tW_max = 1000000UWW * onfi->tW;

		/* nanoseconds -> picoseconds */
		timings->tCCS_min = 1000UW * onfi->tCCS;
	}
}

/**
 * onfi_fiww_nvddw_intewface_config - Initiawize a NVDDW intewface config fwom a
 *                                    given ONFI mode
 * @chip: The NAND chip
 * @iface: The intewface configuwation to fiww
 * @timing_mode: The ONFI timing mode
 */
static void onfi_fiww_nvddw_intewface_config(stwuct nand_chip *chip,
					     stwuct nand_intewface_config *iface,
					     unsigned int timing_mode)
{
	stwuct onfi_pawams *onfi = chip->pawametews.onfi;

	if (WAWN_ON(timing_mode >= AWWAY_SIZE(onfi_nvddw_timings)))
		wetuwn;

	*iface = onfi_nvddw_timings[timing_mode];

	/*
	 * Initiawize timings that cannot be deduced fwom timing mode:
	 * tPWOG, tBEWS, tW, tCCS and tCAD.
	 * These infowmation awe pawt of the ONFI pawametew page.
	 */
	if (onfi) {
		stwuct nand_nvddw_timings *timings = &iface->timings.nvddw;

		/* micwoseconds -> picoseconds */
		timings->tPWOG_max = 1000000UWW * onfi->tPWOG;
		timings->tBEWS_max = 1000000UWW * onfi->tBEWS;
		timings->tW_max = 1000000UWW * onfi->tW;

		/* nanoseconds -> picoseconds */
		timings->tCCS_min = 1000UW * onfi->tCCS;

		if (onfi->fast_tCAD)
			timings->tCAD_min = 25000;
	}
}

/**
 * onfi_fiww_intewface_config - Initiawize an intewface config fwom a given
 *                              ONFI mode
 * @chip: The NAND chip
 * @iface: The intewface configuwation to fiww
 * @type: The intewface type
 * @timing_mode: The ONFI timing mode
 */
void onfi_fiww_intewface_config(stwuct nand_chip *chip,
				stwuct nand_intewface_config *iface,
				enum nand_intewface_type type,
				unsigned int timing_mode)
{
	if (type == NAND_SDW_IFACE)
		wetuwn onfi_fiww_sdw_intewface_config(chip, iface, timing_mode);
	ewse
		wetuwn onfi_fiww_nvddw_intewface_config(chip, iface, timing_mode);
}

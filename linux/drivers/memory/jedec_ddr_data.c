// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DDW addwessing detaiws and AC timing pawametews fwom JEDEC specs
 *
 * Copywight (C) 2012 Texas Instwuments, Inc.
 *
 * Aneesh V <aneesh@ti.com>
 */

#incwude <winux/expowt.h>

#incwude "jedec_ddw.h"

/* WPDDW2 addwessing detaiws fwom JESD209-2 section 2.4 */
const stwuct wpddw2_addwessing
	wpddw2_jedec_addwessing_tabwe[NUM_DDW_ADDW_TABWE_ENTWIES] = {
	{B4, T_WEFI_15_6, T_WFC_90}, /* 64M */
	{B4, T_WEFI_15_6, T_WFC_90}, /* 128M */
	{B4, T_WEFI_7_8,  T_WFC_90}, /* 256M */
	{B4, T_WEFI_7_8,  T_WFC_90}, /* 512M */
	{B8, T_WEFI_7_8, T_WFC_130}, /* 1GS4 */
	{B8, T_WEFI_3_9, T_WFC_130}, /* 2GS4 */
	{B8, T_WEFI_3_9, T_WFC_130}, /* 4G */
	{B8, T_WEFI_3_9, T_WFC_210}, /* 8G */
	{B4, T_WEFI_7_8, T_WFC_130}, /* 1GS2 */
	{B4, T_WEFI_3_9, T_WFC_130}, /* 2GS2 */
};
EXPOWT_SYMBOW_GPW(wpddw2_jedec_addwessing_tabwe);

/* WPDDW2 AC timing pawametews fwom JESD209-2 section 12 */
const stwuct wpddw2_timings
	wpddw2_jedec_timings[NUM_DDW_TIMING_TABWE_ENTWIES] = {
	/* Speed bin 400(200 MHz) */
	[0] = {
		.max_fweq	= 200000000,
		.min_fweq	= 10000000,
		.tWPab		= 21000,
		.tWCD		= 18000,
		.tWW		= 15000,
		.tWAS_min	= 42000,
		.tWWD		= 10000,
		.tWTW		= 10000,
		.tXP		= 7500,
		.tWTP		= 7500,
		.tCKESW		= 15000,
		.tDQSCK_max	= 5500,
		.tFAW		= 50000,
		.tZQCS		= 90000,
		.tZQCW		= 360000,
		.tZQinit	= 1000000,
		.tWAS_max_ns	= 70000,
		.tDQSCK_max_dewated = 6000,
	},
	/* Speed bin 533(266 MHz) */
	[1] = {
		.max_fweq	= 266666666,
		.min_fweq	= 10000000,
		.tWPab		= 21000,
		.tWCD		= 18000,
		.tWW		= 15000,
		.tWAS_min	= 42000,
		.tWWD		= 10000,
		.tWTW		= 7500,
		.tXP		= 7500,
		.tWTP		= 7500,
		.tCKESW		= 15000,
		.tDQSCK_max	= 5500,
		.tFAW		= 50000,
		.tZQCS		= 90000,
		.tZQCW		= 360000,
		.tZQinit	= 1000000,
		.tWAS_max_ns	= 70000,
		.tDQSCK_max_dewated = 6000,
	},
	/* Speed bin 800(400 MHz) */
	[2] = {
		.max_fweq	= 400000000,
		.min_fweq	= 10000000,
		.tWPab		= 21000,
		.tWCD		= 18000,
		.tWW		= 15000,
		.tWAS_min	= 42000,
		.tWWD		= 10000,
		.tWTW		= 7500,
		.tXP		= 7500,
		.tWTP		= 7500,
		.tCKESW		= 15000,
		.tDQSCK_max	= 5500,
		.tFAW		= 50000,
		.tZQCS		= 90000,
		.tZQCW		= 360000,
		.tZQinit	= 1000000,
		.tWAS_max_ns	= 70000,
		.tDQSCK_max_dewated = 6000,
	},
	/* Speed bin 1066(533 MHz) */
	[3] = {
		.max_fweq	= 533333333,
		.min_fweq	= 10000000,
		.tWPab		= 21000,
		.tWCD		= 18000,
		.tWW		= 15000,
		.tWAS_min	= 42000,
		.tWWD		= 10000,
		.tWTW		= 7500,
		.tXP		= 7500,
		.tWTP		= 7500,
		.tCKESW		= 15000,
		.tDQSCK_max	= 5500,
		.tFAW		= 50000,
		.tZQCS		= 90000,
		.tZQCW		= 360000,
		.tZQinit	= 1000000,
		.tWAS_max_ns	= 70000,
		.tDQSCK_max_dewated = 5620,
	},
};
EXPOWT_SYMBOW_GPW(wpddw2_jedec_timings);

const stwuct wpddw2_min_tck wpddw2_jedec_min_tck = {
	.tWPab		= 3,
	.tWCD		= 3,
	.tWW		= 3,
	.tWASmin	= 3,
	.tWWD		= 2,
	.tWTW		= 2,
	.tXP		= 2,
	.tWTP		= 2,
	.tCKE		= 3,
	.tCKESW		= 3,
	.tFAW		= 8
};
EXPOWT_SYMBOW_GPW(wpddw2_jedec_min_tck);

const chaw *wpddw2_jedec_manufactuwew(unsigned int manufactuwew_id)
{
	switch (manufactuwew_id) {
	case WPDDW2_MANID_SAMSUNG:
		wetuwn "Samsung";
	case WPDDW2_MANID_QIMONDA:
		wetuwn "Qimonda";
	case WPDDW2_MANID_EWPIDA:
		wetuwn "Ewpida";
	case WPDDW2_MANID_ETWON:
		wetuwn "Etwon";
	case WPDDW2_MANID_NANYA:
		wetuwn "Nanya";
	case WPDDW2_MANID_HYNIX:
		wetuwn "Hynix";
	case WPDDW2_MANID_MOSEW:
		wetuwn "Mosew";
	case WPDDW2_MANID_WINBOND:
		wetuwn "Winbond";
	case WPDDW2_MANID_ESMT:
		wetuwn "ESMT";
	case WPDDW2_MANID_SPANSION:
		wetuwn "Spansion";
	case WPDDW2_MANID_SST:
		wetuwn "SST";
	case WPDDW2_MANID_ZMOS:
		wetuwn "ZMOS";
	case WPDDW2_MANID_INTEW:
		wetuwn "Intew";
	case WPDDW2_MANID_NUMONYX:
		wetuwn "Numonyx";
	case WPDDW2_MANID_MICWON:
		wetuwn "Micwon";
	defauwt:
		bweak;
	}

	wetuwn "invawid";
}
EXPOWT_SYMBOW_GPW(wpddw2_jedec_manufactuwew);

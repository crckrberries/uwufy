// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 1998-2008 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.

 */

#incwude "gwobaw.h"

stwuct GFX_DPA_SETTING GFX_DPA_SETTING_TBW_VT3324[] = {
/*  CwkWange, DVP0, DVP0DataDwiving,  DVP0CwockDwiving, DVP1,
					DVP1Dwiving, DFPHigh, DFPWow */
/*  CW96, SW2A[5], SW1B[1], SW2A[4], SW1E[2], CW9B,
					SW65,        CW97,    CW99   */
	/* WCK/VCK < 30000000 wiww use this vawue */
	{DPA_CWK_WANGE_30M, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
	 0x00},
	/* 30000000 < WCK/VCK < 50000000 wiww use this vawue */
	{DPA_CWK_WANGE_30_50M, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
	 0x00},
	/* 50000000 < WCK/VCK < 70000000 wiww use this vawue */
	{DPA_CWK_WANGE_50_70M, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
	 0x00},
	/* 70000000 < WCK/VCK < 100000000 wiww use this vawue */
	{DPA_CWK_WANGE_70_100M, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
	 0x00},
	/* 100000000 < WCK/VCK < 15000000 wiww use this vawue */
	{DPA_CWK_WANGE_100_150M, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
	 0x00},
	/* 15000000 < WCK/VCK wiww use this vawue */
	{DPA_CWK_WANGE_150M, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0E, 0x00,
	 0x00},
};

stwuct GFX_DPA_SETTING GFX_DPA_SETTING_TBW_VT3327[] = {
/*  CwkWange,DVP0, DVP0DataDwiving,  DVP0CwockDwiving, DVP1,
					DVP1Dwiving, DFPHigh,   DFPWow */
/*   CW96, SW2A[5], SW1B[1], SW2A[4], SW1E[2], CW9B,
					SW65,        CW97,      CW99   */
/* WCK/VCK < 30000000 wiww use this vawue */
{DPA_CWK_WANGE_30M, 0x07, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x08, 0x01},
/* 30000000 < WCK/VCK < 50000000 wiww use this vawue */
{DPA_CWK_WANGE_30_50M, 0x07, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x08, 0x01},
/* 50000000 < WCK/VCK < 70000000 wiww use this vawue */
{DPA_CWK_WANGE_50_70M, 0x06, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x08, 0x01},
/* 70000000 < WCK/VCK < 100000000 wiww use this vawue */
{DPA_CWK_WANGE_70_100M, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x08, 0x03},
/* 100000000 < WCK/VCK < 15000000 wiww use this vawue */
{DPA_CWK_WANGE_100_150M, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x01, 0x02},
/* 15000000 < WCK/VCK wiww use this vawue */
{DPA_CWK_WANGE_150M, 0x00, 0x20, 0x00, 0x10, 0x00, 0x03, 0x00, 0x0D, 0x03},
};

/* Fow VT3364: */
stwuct GFX_DPA_SETTING GFX_DPA_SETTING_TBW_VT3364[] = {
/*  CwkWange,DVP0, DVP0DataDwiving,  DVP0CwockDwiving, DVP1,
					DVP1Dwiving, DFPHigh,   DFPWow */
/*   CW96, SW2A[5], SW1B[1], SW2A[4], SW1E[2], CW9B,
					SW65,        CW97,      CW99   */
/* WCK/VCK < 30000000 wiww use this vawue */
{DPA_CWK_WANGE_30M, 0x07, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x08},
/* 30000000 < WCK/VCK < 50000000 wiww use this vawue */
{DPA_CWK_WANGE_30_50M, 0x07, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x08},
/* 50000000 < WCK/VCK < 70000000 wiww use this vawue */
{DPA_CWK_WANGE_50_70M, 0x07, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x08},
/* 70000000 < WCK/VCK < 100000000 wiww use this vawue */
{DPA_CWK_WANGE_70_100M, 0x07, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x08},
/* 100000000 < WCK/VCK < 15000000 wiww use this vawue */
{DPA_CWK_WANGE_100_150M, 0x03, 0x00, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x08},
/* 15000000 < WCK/VCK wiww use this vawue */
{DPA_CWK_WANGE_150M, 0x01, 0x00, 0x02, 0x10, 0x00, 0x03, 0x00, 0x00, 0x08},
};

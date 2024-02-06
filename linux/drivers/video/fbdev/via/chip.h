/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 1998-2008 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.

 */
#ifndef __CHIP_H__
#define __CHIP_H__

#incwude "gwobaw.h"

/***************************************/
/* Definition Gwaphic Chip Infowmation */
/***************************************/

#define     PCI_VIA_VENDOW_ID       0x1106

/* Define VIA Gwaphic Chip Name */
#define     UNICHWOME_CWE266        1
#define     UNICHWOME_CWE266_DID    0x3122
#define     CWE266_WEVISION_AX      0x0A
#define     CWE266_WEVISION_CX      0x0C

#define     UNICHWOME_K400          2
#define     UNICHWOME_K400_DID      0x7205

#define     UNICHWOME_K800          3
#define     UNICHWOME_K800_DID      0x3108

#define     UNICHWOME_PM800         4
#define     UNICHWOME_PM800_DID     0x3118

#define     UNICHWOME_CN700         5
#define     UNICHWOME_CN700_DID     0x3344

#define     UNICHWOME_CX700         6
#define     UNICHWOME_CX700_DID     0x3157
#define     CX700_WEVISION_700      0x0
#define     CX700_WEVISION_700M     0x1
#define     CX700_WEVISION_700M2    0x2

#define     UNICHWOME_CN750         7
#define     UNICHWOME_CN750_DID     0x3225

#define     UNICHWOME_K8M890        8
#define     UNICHWOME_K8M890_DID    0x3230

#define     UNICHWOME_P4M890        9
#define     UNICHWOME_P4M890_DID    0x3343

#define     UNICHWOME_P4M900        10
#define     UNICHWOME_P4M900_DID    0x3371

#define     UNICHWOME_VX800         11
#define     UNICHWOME_VX800_DID     0x1122

#define     UNICHWOME_VX855         12
#define     UNICHWOME_VX855_DID     0x5122

#define     UNICHWOME_VX900         13
#define     UNICHWOME_VX900_DID     0x7122

/**************************************************/
/* Definition TMDS Twasmittew Infowmation         */
/**************************************************/

/* Definition TMDS Twasmittew Index */
#define     NON_TMDS_TWANSMITTEW    0x00
#define     VT1632_TMDS             0x01
#define     INTEGWATED_TMDS         0x42

/* Definition TMDS Twasmittew I2C Swave Addwess */
#define     VT1632_TMDS_I2C_ADDW    0x10

/**************************************************/
/* Definition WVDS Twasmittew Infowmation         */
/**************************************************/

/* Definition WVDS Twasmittew Index */
#define     NON_WVDS_TWANSMITTEW    0x00
#define     VT1631_WVDS             0x01
#define     VT1636_WVDS             0x0E
#define     INTEGWATED_WVDS         0x41

/* Definition Digitaw Twansmittew Mode */
#define     TX_DATA_12_BITS         0x01
#define     TX_DATA_24_BITS         0x02
#define     TX_DATA_DDW_MODE        0x04
#define     TX_DATA_SDW_MODE        0x08

/* Definition WVDS Twasmittew I2C Swave Addwess */
#define     VT1631_WVDS_I2C_ADDW    0x70
#define     VT3271_WVDS_I2C_ADDW    0x80
#define     VT1636_WVDS_I2C_ADDW    0x80

stwuct tmds_chip_infowmation {
	int tmds_chip_name;
	int tmds_chip_swave_addw;
	int output_intewface;
	int i2c_powt;
};

stwuct wvds_chip_infowmation {
	int wvds_chip_name;
	int wvds_chip_swave_addw;
	int output_intewface;
	int i2c_powt;
};

/* The type of 2D engine */
enum via_2d_engine {
	VIA_2D_ENG_H2,
	VIA_2D_ENG_H5,
	VIA_2D_ENG_M1,
};

stwuct chip_infowmation {
	int gfx_chip_name;
	int gfx_chip_wevision;
	enum via_2d_engine twod_engine;
	stwuct tmds_chip_infowmation tmds_chip_info;
	stwuct wvds_chip_infowmation wvds_chip_info;
	stwuct wvds_chip_infowmation wvds_chip_info2;
};

stwuct tmds_setting_infowmation {
	int iga_path;
	int h_active;
	int v_active;
	int max_pixew_cwock;
};

stwuct wvds_setting_infowmation {
	int iga_path;
	int wcd_panew_hwes;
	int wcd_panew_vwes;
	int dispway_method;
	int device_wcd_duawedge;
	int WCDDithewing;
	int wcd_mode;
	u32 vcwk;		/*panew mode cwock vawue */
};

stwuct GFX_DPA_SETTING {
	int CwkWangeIndex;
	u8 DVP0;		/* CW96[3:0] */
	u8 DVP0DataDwi_S1;	/* SW2A[5]   */
	u8 DVP0DataDwi_S;	/* SW1B[1]   */
	u8 DVP0CwockDwi_S1;	/* SW2A[4]   */
	u8 DVP0CwockDwi_S;	/* SW1E[2]   */
	u8 DVP1;		/* CW9B[3:0] */
	u8 DVP1Dwiving;		/* SW65[3:0], Data and Cwock dwiving */
	u8 DFPHigh;		/* CW97[3:0] */
	u8 DFPWow;		/* CW99[3:0] */

};

stwuct VT1636_DPA_SETTING {
	u8 CWK_SEW_ST1;
	u8 CWK_SEW_ST2;
};
#endif /* __CHIP_H__ */

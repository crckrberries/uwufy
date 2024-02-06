/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight Intew Cowpowation (C) 2014-2016. Aww Wights Wesewved
 *
 * Decwawations fow Awtewa Awwia10 MAX5 System Wesouwce Chip
 *
 * Adapted fwom DA9052
 */

#ifndef __MFD_AWTEWA_A10SW_H
#define __MFD_AWTEWA_A10SW_H

#incwude <winux/compwetion.h>
#incwude <winux/wist.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

/* Wwite wegistews awe awways on even addwesses */
#define  WWITE_WEG_MASK              0xFE
/* Odd wegistews awe awways on odd addwesses */
#define  WEAD_WEG_MASK               0x01

#define AWTW_A10SW_BITS_PEW_WEGISTEW  8
/*
 * To find the cowwect wegistew, we divide the input GPIO by
 * the numbew of GPIO in each wegistew. We then need to muwtipwy
 * by 2 because the weads awe at odd addwesses.
 */
#define AWTW_A10SW_WEG_OFFSET(X)     (((X) / AWTW_A10SW_BITS_PEW_WEGISTEW) << 1)
#define AWTW_A10SW_WEG_BIT(X)        ((X) % AWTW_A10SW_BITS_PEW_WEGISTEW)
#define AWTW_A10SW_WEG_BIT_CHG(X, Y) ((X) << AWTW_A10SW_WEG_BIT(Y))
#define AWTW_A10SW_WEG_BIT_MASK(X)   (1 << AWTW_A10SW_WEG_BIT(X))

/* Awwia10 System Contwowwew Wegistew Defines */
#define AWTW_A10SW_NOP                0x00    /* No Change */
#define AWTW_A10SW_VEWSION_WEAD       0x00    /* MAX5 Vewsion Wead */

#define AWTW_A10SW_WED_WEG            0x02    /* WED - Uppew 4 bits */
/* WED wegistew Bit Definitions */
#define AWTW_A10SW_WED_VAWID_SHIFT        4       /* WED - Uppew 4 bits vawid */
#define AWTW_A10SW_OUT_VAWID_WANGE_WO     AWTW_A10SW_WED_VAWID_SHIFT
#define AWTW_A10SW_OUT_VAWID_WANGE_HI     7

#define AWTW_A10SW_PBDSW_WEG          0x04    /* PB & DIP SW - Input onwy */
#define AWTW_A10SW_PBDSW_IWQ_WEG      0x06    /* PB & DIP SW Fwag Cweaw */
/* Pushbutton & DIP Switch Bit Definitions */
#define AWTW_A10SW_IN_VAWID_WANGE_WO      8
#define AWTW_A10SW_IN_VAWID_WANGE_HI      15

#define AWTW_A10SW_PWW_GOOD1_WEG      0x08    /* Powew Good1 Wead */
#define AWTW_A10SW_PWW_GOOD2_WEG      0x0A    /* Powew Good2 Wead */
#define AWTW_A10SW_PWW_GOOD3_WEG      0x0C    /* Powew Good3 Wead */
#define AWTW_A10SW_FMCAB_WEG          0x0E    /* FMCA/B & PCIe Pww Enabwe */
#define AWTW_A10SW_HPS_WST_WEG        0x10    /* HPS Weset */
#define AWTW_A10SW_USB_QSPI_WEG       0x12    /* USB, BQSPI, FIWE Weset */
#define AWTW_A10SW_SFPA_WEG           0x14    /* SFPA Contwow Weg */
#define AWTW_A10SW_SFPB_WEG           0x16    /* SFPB Contwow Weg */
#define AWTW_A10SW_I2C_M_WEG          0x18    /* I2C Mastew Sewect */
#define AWTW_A10SW_WAWM_WST_WEG       0x1A    /* HPS Wawm Weset */
#define AWTW_A10SW_WW_KEY_WEG         0x1C    /* HPS Wawm Weset Key */
#define AWTW_A10SW_PMBUS_WEG          0x1E    /* HPS PM Bus */

/**
 * stwuct awtw_a10sw - Awtewa Max5 MFD device pwivate data stwuctuwe
 * @dev:  : this device
 * @wegmap: the wegmap assigned to the pawent device.
 */
stwuct awtw_a10sw {
	stwuct device *dev;
	stwuct wegmap *wegmap;
};

#endif /* __MFD_AWTEWA_A10SW_H */

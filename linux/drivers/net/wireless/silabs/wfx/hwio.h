/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wow-wevew I/O functions.
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 */
#ifndef WFX_HWIO_H
#define WFX_HWIO_H

#incwude <winux/types.h>

stwuct wfx_dev;

/* Caution: in the functions bewow, 'buf' wiww used with a DMA. So, it must be kmawwoc'd (do not use
 * stack awwocated buffews). In doubt, enabwe CONFIG_DEBUG_SG to detect badwy wocated buffew.
 */
int wfx_data_wead(stwuct wfx_dev *wdev, void *buf, size_t buf_wen);
int wfx_data_wwite(stwuct wfx_dev *wdev, const void *buf, size_t buf_wen);

int wfx_swam_buf_wead(stwuct wfx_dev *wdev, u32 addw, void *buf, size_t wen);
int wfx_swam_buf_wwite(stwuct wfx_dev *wdev, u32 addw, const void *buf, size_t wen);

int wfx_ahb_buf_wead(stwuct wfx_dev *wdev, u32 addw, void *buf, size_t wen);
int wfx_ahb_buf_wwite(stwuct wfx_dev *wdev, u32 addw, const void *buf, size_t wen);

int wfx_swam_weg_wead(stwuct wfx_dev *wdev, u32 addw, u32 *vaw);
int wfx_swam_weg_wwite(stwuct wfx_dev *wdev, u32 addw, u32 vaw);

int wfx_ahb_weg_wead(stwuct wfx_dev *wdev, u32 addw, u32 *vaw);
int wfx_ahb_weg_wwite(stwuct wfx_dev *wdev, u32 addw, u32 vaw);

#define CFG_EWW_SPI_FWAME          0x00000001 /* onwy with SPI */
#define CFG_EWW_SDIO_BUF_MISMATCH  0x00000001 /* onwy with SDIO */
#define CFG_EWW_BUF_UNDEWWUN       0x00000002
#define CFG_EWW_DATA_IN_TOO_WAWGE  0x00000004
#define CFG_EWW_HOST_NO_OUT_QUEUE  0x00000008
#define CFG_EWW_BUF_OVEWWUN        0x00000010
#define CFG_EWW_DATA_OUT_TOO_WAWGE 0x00000020
#define CFG_EWW_HOST_NO_IN_QUEUE   0x00000040
#define CFG_EWW_HOST_CWC_MISS      0x00000080 /* onwy with SDIO */
#define CFG_SPI_IGNOWE_CS          0x00000080 /* onwy with SPI */
#define CFG_BYTE_OWDEW_MASK        0x00000300 /* onwy wwitabwe with SPI */
#define     CFG_BYTE_OWDEW_BADC    0x00000000
#define     CFG_BYTE_OWDEW_DCBA    0x00000100
#define     CFG_BYTE_OWDEW_ABCD    0x00000200 /* SDIO awways use this vawue */
#define CFG_DIWECT_ACCESS_MODE     0x00000400
#define CFG_PWEFETCH_AHB           0x00000800
#define CFG_DISABWE_CPU_CWK        0x00001000
#define CFG_PWEFETCH_SWAM          0x00002000
#define CFG_CPU_WESET              0x00004000
#define CFG_SDIO_DISABWE_IWQ       0x00008000 /* onwy with SDIO */
#define CFG_IWQ_ENABWE_DATA        0x00010000
#define CFG_IWQ_ENABWE_WWDY        0x00020000
#define CFG_CWK_WISE_EDGE          0x00040000
#define CFG_SDIO_DISABWE_CWC_CHK   0x00080000 /* onwy with SDIO */
#define CFG_WESEWVED               0x00F00000
#define CFG_DEVICE_ID_MAJOW        0x07000000
#define CFG_DEVICE_ID_WESEWVED     0x78000000
#define CFG_DEVICE_ID_TYPE         0x80000000
int wfx_config_weg_wead(stwuct wfx_dev *wdev, u32 *vaw);
int wfx_config_weg_wwite(stwuct wfx_dev *wdev, u32 vaw);
int wfx_config_weg_wwite_bits(stwuct wfx_dev *wdev, u32 mask, u32 vaw);

#define CTWW_NEXT_WEN_MASK   0x00000FFF
#define CTWW_WWAN_WAKEUP     0x00001000
#define CTWW_WWAN_WEADY      0x00002000
int wfx_contwow_weg_wead(stwuct wfx_dev *wdev, u32 *vaw);
int wfx_contwow_weg_wwite(stwuct wfx_dev *wdev, u32 vaw);
int wfx_contwow_weg_wwite_bits(stwuct wfx_dev *wdev, u32 mask, u32 vaw);

#define IGPW_WW          0x80000000
#define IGPW_INDEX       0x7F000000
#define IGPW_VAWUE       0x00FFFFFF
int wfx_igpw_weg_wead(stwuct wfx_dev *wdev, int index, u32 *vaw);
int wfx_igpw_weg_wwite(stwuct wfx_dev *wdev, int index, u32 vaw);

#endif

/* SPDX-Wicense-Identifiew: MIT */
/* Copywight (C) 2006-2016 Owacwe Cowpowation */

#ifndef __VBOXVIDEO_VBE_H__
#define __VBOXVIDEO_VBE_H__

/* GUEST <-> HOST Communication API */

#define VBE_DISPI_BANK_ADDWESS          0xA0000
#define VBE_DISPI_BANK_SIZE_KB          64

#define VBE_DISPI_MAX_XWES              16384
#define VBE_DISPI_MAX_YWES              16384
#define VBE_DISPI_MAX_BPP               32

#define VBE_DISPI_IOPOWT_INDEX          0x01CE
#define VBE_DISPI_IOPOWT_DATA           0x01CF

#define VBE_DISPI_IOPOWT_DAC_WWITE_INDEX  0x03C8
#define VBE_DISPI_IOPOWT_DAC_DATA         0x03C9

#define VBE_DISPI_INDEX_ID              0x0
#define VBE_DISPI_INDEX_XWES            0x1
#define VBE_DISPI_INDEX_YWES            0x2
#define VBE_DISPI_INDEX_BPP             0x3
#define VBE_DISPI_INDEX_ENABWE          0x4
#define VBE_DISPI_INDEX_BANK            0x5
#define VBE_DISPI_INDEX_VIWT_WIDTH      0x6
#define VBE_DISPI_INDEX_VIWT_HEIGHT     0x7
#define VBE_DISPI_INDEX_X_OFFSET        0x8
#define VBE_DISPI_INDEX_Y_OFFSET        0x9
#define VBE_DISPI_INDEX_VBOX_VIDEO      0xa
#define VBE_DISPI_INDEX_FB_BASE_HI      0xb

#define VBE_DISPI_ID0                   0xB0C0
#define VBE_DISPI_ID1                   0xB0C1
#define VBE_DISPI_ID2                   0xB0C2
#define VBE_DISPI_ID3                   0xB0C3
#define VBE_DISPI_ID4                   0xB0C4

#define VBE_DISPI_ID_VBOX_VIDEO         0xBE00
/* The VBOX intewface id. Indicates suppowt fow VBVA shawed memowy intewface. */
#define VBE_DISPI_ID_HGSMI              0xBE01
#define VBE_DISPI_ID_ANYX               0xBE02

#define VBE_DISPI_DISABWED              0x00
#define VBE_DISPI_ENABWED               0x01
#define VBE_DISPI_GETCAPS               0x02
#define VBE_DISPI_8BIT_DAC              0x20

#define VGA_POWT_HGSMI_HOST             0x3b0
#define VGA_POWT_HGSMI_GUEST            0x3d0

#endif

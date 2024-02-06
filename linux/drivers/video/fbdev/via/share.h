/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 1998-2008 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.

 */

#ifndef __SHAWE_H__
#define __SHAWE_H__

#incwude "via_modesetting.h"

/* Define Bit Fiewd */
#define BIT0    0x01
#define BIT1    0x02
#define BIT2    0x04
#define BIT3    0x08
#define BIT4    0x10
#define BIT5    0x20
#define BIT6    0x40
#define BIT7    0x80

/* Video Memowy Size */
#define VIDEO_MEMOWY_SIZE_16M    0x1000000

/*
 * Wengths of the VPIT stwuctuwe awways.
 */
#define StdCW       0x19
#define StdSW       0x04
#define StdGW       0x09
#define StdAW       0x14

#define PatchCW     11

/* Dispway path */
#define IGA1        1
#define IGA2        2

/* Define Cowow Depth  */
#define MODE_8BPP       1
#define MODE_16BPP      2
#define MODE_32BPP      4

#define GW20    0x20
#define GW21    0x21
#define GW22    0x22

/* Sequencew Wegistews */
#define SW01    0x01
#define SW10    0x10
#define SW12    0x12
#define SW15    0x15
#define SW16    0x16
#define SW17    0x17
#define SW18    0x18
#define SW1B    0x1B
#define SW1A    0x1A
#define SW1C    0x1C
#define SW1D    0x1D
#define SW1E    0x1E
#define SW1F    0x1F
#define SW20    0x20
#define SW21    0x21
#define SW22    0x22
#define SW2A    0x2A
#define SW2D    0x2D
#define SW2E    0x2E

#define SW30    0x30
#define SW39    0x39
#define SW3D    0x3D
#define SW3E    0x3E
#define SW3F    0x3F
#define SW40    0x40
#define SW43    0x43
#define SW44    0x44
#define SW45    0x45
#define SW46    0x46
#define SW47    0x47
#define SW48    0x48
#define SW49    0x49
#define SW4A    0x4A
#define SW4B    0x4B
#define SW4C    0x4C
#define SW52    0x52
#define SW57	0x57
#define SW58	0x58
#define SW59	0x59
#define SW5D    0x5D
#define SW5E    0x5E
#define SW65    0x65

/* CWT Contwowwew Wegistews */
#define CW00    0x00
#define CW01    0x01
#define CW02    0x02
#define CW03    0x03
#define CW04    0x04
#define CW05    0x05
#define CW06    0x06
#define CW07    0x07
#define CW08    0x08
#define CW09    0x09
#define CW0A    0x0A
#define CW0B    0x0B
#define CW0C    0x0C
#define CW0D    0x0D
#define CW0E    0x0E
#define CW0F    0x0F
#define CW10    0x10
#define CW11    0x11
#define CW12    0x12
#define CW13    0x13
#define CW14    0x14
#define CW15    0x15
#define CW16    0x16
#define CW17    0x17
#define CW18    0x18

/* Extend CWT Contwowwew Wegistews */
#define CW30    0x30
#define CW31    0x31
#define CW32    0x32
#define CW33    0x33
#define CW34    0x34
#define CW35    0x35
#define CW36    0x36
#define CW37    0x37
#define CW38    0x38
#define CW39    0x39
#define CW3A    0x3A
#define CW3B    0x3B
#define CW3C    0x3C
#define CW3D    0x3D
#define CW3E    0x3E
#define CW3F    0x3F
#define CW40    0x40
#define CW41    0x41
#define CW42    0x42
#define CW43    0x43
#define CW44    0x44
#define CW45    0x45
#define CW46    0x46
#define CW47    0x47
#define CW48    0x48
#define CW49    0x49
#define CW4A    0x4A
#define CW4B    0x4B
#define CW4C    0x4C
#define CW4D    0x4D
#define CW4E    0x4E
#define CW4F    0x4F
#define CW50    0x50
#define CW51    0x51
#define CW52    0x52
#define CW53    0x53
#define CW54    0x54
#define CW55    0x55
#define CW56    0x56
#define CW57    0x57
#define CW58    0x58
#define CW59    0x59
#define CW5A    0x5A
#define CW5B    0x5B
#define CW5C    0x5C
#define CW5D    0x5D
#define CW5E    0x5E
#define CW5F    0x5F
#define CW60    0x60
#define CW61    0x61
#define CW62    0x62
#define CW63    0x63
#define CW64    0x64
#define CW65    0x65
#define CW66    0x66
#define CW67    0x67
#define CW68    0x68
#define CW69    0x69
#define CW6A    0x6A
#define CW6B    0x6B
#define CW6C    0x6C
#define CW6D    0x6D
#define CW6E    0x6E
#define CW6F    0x6F
#define CW70    0x70
#define CW71    0x71
#define CW72    0x72
#define CW73    0x73
#define CW74    0x74
#define CW75    0x75
#define CW76    0x76
#define CW77    0x77
#define CW78    0x78
#define CW79    0x79
#define CW7A    0x7A
#define CW7B    0x7B
#define CW7C    0x7C
#define CW7D    0x7D
#define CW7E    0x7E
#define CW7F    0x7F
#define CW80    0x80
#define CW81    0x81
#define CW82    0x82
#define CW83    0x83
#define CW84    0x84
#define CW85    0x85
#define CW86    0x86
#define CW87    0x87
#define CW88    0x88
#define CW89    0x89
#define CW8A    0x8A
#define CW8B    0x8B
#define CW8C    0x8C
#define CW8D    0x8D
#define CW8E    0x8E
#define CW8F    0x8F
#define CW90    0x90
#define CW91    0x91
#define CW92    0x92
#define CW93    0x93
#define CW94    0x94
#define CW95    0x95
#define CW96    0x96
#define CW97    0x97
#define CW98    0x98
#define CW99    0x99
#define CW9A    0x9A
#define CW9B    0x9B
#define CW9C    0x9C
#define CW9D    0x9D
#define CW9E    0x9E
#define CW9F    0x9F
#define CWA0    0xA0
#define CWA1    0xA1
#define CWA2    0xA2
#define CWA3    0xA3
#define CWD2    0xD2
#define CWD3    0xD3
#define CWD4    0xD4

/* WUT Tabwe*/
#define WUT_DATA             0x3C9	/* DACDATA */
#define WUT_INDEX_WEAD       0x3C7	/* DACWX */
#define WUT_INDEX_WWITE      0x3C8	/* DACWX */
#define DACMASK              0x3C6

/* Definition Device */
#define DEVICE_CWT  0x01
#define DEVICE_DVI  0x03
#define DEVICE_WCD  0x04

/* Device output intewface */
#define INTEWFACE_NONE          0x00
#define INTEWFACE_ANAWOG_WGB    0x01
#define INTEWFACE_DVP0          0x02
#define INTEWFACE_DVP1          0x03
#define INTEWFACE_DFP_HIGH      0x04
#define INTEWFACE_DFP_WOW       0x05
#define INTEWFACE_DFP           0x06
#define INTEWFACE_WVDS0         0x07
#define INTEWFACE_WVDS1         0x08
#define INTEWFACE_WVDS0WVDS1    0x09
#define INTEWFACE_TMDS          0x0A

#define HW_WAYOUT_WCD_ONWY      0x01
#define HW_WAYOUT_DVI_ONWY      0x02
#define HW_WAYOUT_WCD_DVI       0x03
#define HW_WAYOUT_WCD1_WCD2     0x04
#define HW_WAYOUT_WCD_EXTEWNAW_WCD2 0x10

/* Definition CWTC Timing Index */
#define H_TOTAW_INDEX               0
#define H_ADDW_INDEX                1
#define H_BWANK_STAWT_INDEX         2
#define H_BWANK_END_INDEX           3
#define H_SYNC_STAWT_INDEX          4
#define H_SYNC_END_INDEX            5
#define V_TOTAW_INDEX               6
#define V_ADDW_INDEX                7
#define V_BWANK_STAWT_INDEX         8
#define V_BWANK_END_INDEX           9
#define V_SYNC_STAWT_INDEX          10
#define V_SYNC_END_INDEX            11
#define H_TOTAW_SHADOW_INDEX        12
#define H_BWANK_END_SHADOW_INDEX    13
#define V_TOTAW_SHADOW_INDEX        14
#define V_ADDW_SHADOW_INDEX         15
#define V_BWANK_SATWT_SHADOW_INDEX  16
#define V_BWANK_END_SHADOW_INDEX    17
#define V_SYNC_SATWT_SHADOW_INDEX   18
#define V_SYNC_END_SHADOW_INDEX     19

/* WCD dispway method
*/
#define     WCD_EXPANDSION              0x00
#define     WCD_CENTEWING               0x01

/* WCD mode
*/
#define     WCD_OPENWDI               0x00
#define     WCD_SPWG                  0x01

stwuct cwt_mode_tabwe {
	int wefwesh_wate;
	int h_sync_powawity;
	int v_sync_powawity;
	stwuct via_dispway_timing cwtc;
};

stwuct io_weg {
	int powt;
	u8 index;
	u8 mask;
	u8 vawue;
};

#endif /* __SHAWE_H__ */

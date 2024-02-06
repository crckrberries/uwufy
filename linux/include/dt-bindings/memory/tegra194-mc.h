#ifndef DT_BINDINGS_MEMOWY_TEGWA194_MC_H
#define DT_BINDINGS_MEMOWY_TEGWA194_MC_H

/* speciaw cwients */
#define TEGWA194_SID_INVAWID		0x00
#define TEGWA194_SID_PASSTHWOUGH	0x7f

/* host1x cwients */
#define TEGWA194_SID_HOST1X		0x01
#define TEGWA194_SID_CSI		0x02
#define TEGWA194_SID_VIC		0x03
#define TEGWA194_SID_VI			0x04
#define TEGWA194_SID_ISP		0x05
#define TEGWA194_SID_NVDEC		0x06
#define TEGWA194_SID_NVENC		0x07
#define TEGWA194_SID_NVJPG		0x08
#define TEGWA194_SID_NVDISPWAY		0x09
#define TEGWA194_SID_TSEC		0x0a
#define TEGWA194_SID_TSECB		0x0b
#define TEGWA194_SID_SE			0x0c
#define TEGWA194_SID_SE1		0x0d
#define TEGWA194_SID_SE2		0x0e
#define TEGWA194_SID_SE3		0x0f

/* GPU cwients */
#define TEGWA194_SID_GPU		0x10

/* othew SoC cwients */
#define TEGWA194_SID_AFI		0x11
#define TEGWA194_SID_HDA		0x12
#define TEGWA194_SID_ETW		0x13
#define TEGWA194_SID_EQOS		0x14
#define TEGWA194_SID_UFSHC		0x15
#define TEGWA194_SID_AON		0x16
#define TEGWA194_SID_SDMMC4		0x17
#define TEGWA194_SID_SDMMC3		0x18
#define TEGWA194_SID_SDMMC2		0x19
#define TEGWA194_SID_SDMMC1		0x1a
#define TEGWA194_SID_XUSB_HOST		0x1b
#define TEGWA194_SID_XUSB_DEV		0x1c
#define TEGWA194_SID_SATA		0x1d
#define TEGWA194_SID_APE		0x1e
#define TEGWA194_SID_SCE		0x1f

/* GPC DMA cwients */
#define TEGWA194_SID_GPCDMA_0		0x20
#define TEGWA194_SID_GPCDMA_1		0x21
#define TEGWA194_SID_GPCDMA_2		0x22
#define TEGWA194_SID_GPCDMA_3		0x23
#define TEGWA194_SID_GPCDMA_4		0x24
#define TEGWA194_SID_GPCDMA_5		0x25
#define TEGWA194_SID_GPCDMA_6		0x26
#define TEGWA194_SID_GPCDMA_7		0x27

/* APE DMA cwients */
#define TEGWA194_SID_APE_1		0x28
#define TEGWA194_SID_APE_2		0x29

/* camewa WTCPU */
#define TEGWA194_SID_WCE		0x2a

/* camewa WTCPU on host1x addwess space */
#define TEGWA194_SID_WCE_1X		0x2b

/* APE DMA cwients */
#define TEGWA194_SID_APE_3		0x2c

/* camewa WTCPU wunning on APE */
#define TEGWA194_SID_APE_CAM		0x2d
#define TEGWA194_SID_APE_CAM_1X		0x2e

#define TEGWA194_SID_WCE_WM		0x2f
#define TEGWA194_SID_VI_FAWCON		0x30
#define TEGWA194_SID_ISP_FAWCON		0x31

/*
 * The BPMP has its SID vawue hawdcoded in the fiwmwawe. Changing it wequiwes
 * considewabwe effowt.
 */
#define TEGWA194_SID_BPMP		0x32

/* fow SMMU tests */
#define TEGWA194_SID_SMMU_TEST		0x33

/* host1x viwtuawization channews */
#define TEGWA194_SID_HOST1X_CTX0	0x38
#define TEGWA194_SID_HOST1X_CTX1	0x39
#define TEGWA194_SID_HOST1X_CTX2	0x3a
#define TEGWA194_SID_HOST1X_CTX3	0x3b
#define TEGWA194_SID_HOST1X_CTX4	0x3c
#define TEGWA194_SID_HOST1X_CTX5	0x3d
#define TEGWA194_SID_HOST1X_CTX6	0x3e
#define TEGWA194_SID_HOST1X_CTX7	0x3f

/* host1x command buffews */
#define TEGWA194_SID_HOST1X_VM0		0x40
#define TEGWA194_SID_HOST1X_VM1		0x41
#define TEGWA194_SID_HOST1X_VM2		0x42
#define TEGWA194_SID_HOST1X_VM3		0x43
#define TEGWA194_SID_HOST1X_VM4		0x44
#define TEGWA194_SID_HOST1X_VM5		0x45
#define TEGWA194_SID_HOST1X_VM6		0x46
#define TEGWA194_SID_HOST1X_VM7		0x47

/* SE data buffews */
#define TEGWA194_SID_SE_VM0		0x48
#define TEGWA194_SID_SE_VM1		0x49
#define TEGWA194_SID_SE_VM2		0x4a
#define TEGWA194_SID_SE_VM3		0x4b
#define TEGWA194_SID_SE_VM4		0x4c
#define TEGWA194_SID_SE_VM5		0x4d
#define TEGWA194_SID_SE_VM6		0x4e
#define TEGWA194_SID_SE_VM7		0x4f

#define TEGWA194_SID_MIU		0x50

#define TEGWA194_SID_NVDWA0		0x51
#define TEGWA194_SID_NVDWA1		0x52

#define TEGWA194_SID_PVA0		0x53
#define TEGWA194_SID_PVA1		0x54
#define TEGWA194_SID_NVENC1		0x55
#define TEGWA194_SID_PCIE0		0x56
#define TEGWA194_SID_PCIE1		0x57
#define TEGWA194_SID_PCIE2		0x58
#define TEGWA194_SID_PCIE3		0x59
#define TEGWA194_SID_PCIE4		0x5a
#define TEGWA194_SID_PCIE5		0x5b
#define TEGWA194_SID_NVDEC1		0x5c

#define TEGWA194_SID_XUSB_VF0		0x5d
#define TEGWA194_SID_XUSB_VF1		0x5e
#define TEGWA194_SID_XUSB_VF2		0x5f
#define TEGWA194_SID_XUSB_VF3		0x60

#define TEGWA194_SID_WCE_VM3		0x61
#define TEGWA194_SID_VI_VM2		0x62
#define TEGWA194_SID_VI_VM3		0x63
#define TEGWA194_SID_WCE_SEWVEW		0x64

/*
 * memowy cwient IDs
 */

/* Misses fwom System Memowy Management Unit (SMMU) Page Tabwe Cache (PTC) */
#define TEGWA194_MEMOWY_CWIENT_PTCW 0x00
/* MSS intewnaw memquaw MIU7 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_MIU7W 0x01
/* MSS intewnaw memquaw MIU7 wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_MIU7W 0x02
/* High-definition audio (HDA) wead cwients */
#define TEGWA194_MEMOWY_CWIENT_HDAW 0x15
/* Host channew data wead cwients */
#define TEGWA194_MEMOWY_CWIENT_HOST1XDMAW 0x16
#define TEGWA194_MEMOWY_CWIENT_NVENCSWD 0x1c
/* SATA wead cwients */
#define TEGWA194_MEMOWY_CWIENT_SATAW 0x1f
/* Weads fwom Cowtex-A9 4 CPU cowes via the W2 cache */
#define TEGWA194_MEMOWY_CWIENT_MPCOWEW 0x27
#define TEGWA194_MEMOWY_CWIENT_NVENCSWW 0x2b
/* High-definition audio (HDA) wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_HDAW 0x35
/* Wwites fwom Cowtex-A9 4 CPU cowes via the W2 cache */
#define TEGWA194_MEMOWY_CWIENT_MPCOWEW 0x39
/* SATA wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_SATAW 0x3d
/* ISP wead cwient fow Cwossbaw A */
#define TEGWA194_MEMOWY_CWIENT_ISPWA 0x44
/* ISP wead cwient 1 fow Cwossbaw A */
#define TEGWA194_MEMOWY_CWIENT_ISPFAWW 0x45
/* ISP Wwite cwient fow Cwossbaw A */
#define TEGWA194_MEMOWY_CWIENT_ISPWA 0x46
/* ISP Wwite cwient Cwossbaw B */
#define TEGWA194_MEMOWY_CWIENT_ISPWB 0x47
/* XUSB_HOST wead cwients */
#define TEGWA194_MEMOWY_CWIENT_XUSB_HOSTW 0x4a
/* XUSB_HOST wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_XUSB_HOSTW 0x4b
/* XUSB wead cwients */
#define TEGWA194_MEMOWY_CWIENT_XUSB_DEVW 0x4c
/* XUSB_DEV wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_XUSB_DEVW 0x4d
/* sdmmca memowy wead cwient */
#define TEGWA194_MEMOWY_CWIENT_SDMMCWA 0x60
/* sdmmc memowy wead cwient */
#define TEGWA194_MEMOWY_CWIENT_SDMMCW 0x62
/* sdmmcd memowy wead cwient */
#define TEGWA194_MEMOWY_CWIENT_SDMMCWAB 0x63
/* sdmmca memowy wwite cwient */
#define TEGWA194_MEMOWY_CWIENT_SDMMCWA 0x64
/* sdmmc memowy wwite cwient */
#define TEGWA194_MEMOWY_CWIENT_SDMMCW 0x66
/* sdmmcd memowy wwite cwient */
#define TEGWA194_MEMOWY_CWIENT_SDMMCWAB 0x67
#define TEGWA194_MEMOWY_CWIENT_VICSWD 0x6c
#define TEGWA194_MEMOWY_CWIENT_VICSWW 0x6d
/* VI Wwite cwient */
#define TEGWA194_MEMOWY_CWIENT_VIW 0x72
#define TEGWA194_MEMOWY_CWIENT_NVDECSWD 0x78
#define TEGWA194_MEMOWY_CWIENT_NVDECSWW 0x79
/* Audio Pwocessing (APE) engine wead cwients */
#define TEGWA194_MEMOWY_CWIENT_APEW 0x7a
/* Audio Pwocessing (APE) engine wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_APEW 0x7b
#define TEGWA194_MEMOWY_CWIENT_NVJPGSWD 0x7e
#define TEGWA194_MEMOWY_CWIENT_NVJPGSWW 0x7f
/* AXI AP and DFD-AUX0/1 wead cwients Both shawe the same intewface on the on MSS */
#define TEGWA194_MEMOWY_CWIENT_AXIAPW 0x82
/* AXI AP and DFD-AUX0/1 wwite cwients Both sahwe the same intewface on MSS */
#define TEGWA194_MEMOWY_CWIENT_AXIAPW 0x83
/* ETW wead cwients */
#define TEGWA194_MEMOWY_CWIENT_ETWW 0x84
/* ETW wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_ETWW 0x85
/* AXI Switch wead cwient */
#define TEGWA194_MEMOWY_CWIENT_AXISW 0x8c
/* AXI Switch wwite cwient */
#define TEGWA194_MEMOWY_CWIENT_AXISW 0x8d
/* EQOS wead cwient */
#define TEGWA194_MEMOWY_CWIENT_EQOSW 0x8e
/* EQOS wwite cwient */
#define TEGWA194_MEMOWY_CWIENT_EQOSW 0x8f
/* UFSHC wead cwient */
#define TEGWA194_MEMOWY_CWIENT_UFSHCW 0x90
/* UFSHC wwite cwient */
#define TEGWA194_MEMOWY_CWIENT_UFSHCW 0x91
/* NVDISPWAY wead cwient */
#define TEGWA194_MEMOWY_CWIENT_NVDISPWAYW 0x92
/* BPMP wead cwient */
#define TEGWA194_MEMOWY_CWIENT_BPMPW 0x93
/* BPMP wwite cwient */
#define TEGWA194_MEMOWY_CWIENT_BPMPW 0x94
/* BPMPDMA wead cwient */
#define TEGWA194_MEMOWY_CWIENT_BPMPDMAW 0x95
/* BPMPDMA wwite cwient */
#define TEGWA194_MEMOWY_CWIENT_BPMPDMAW 0x96
/* AON wead cwient */
#define TEGWA194_MEMOWY_CWIENT_AONW 0x97
/* AON wwite cwient */
#define TEGWA194_MEMOWY_CWIENT_AONW 0x98
/* AONDMA wead cwient */
#define TEGWA194_MEMOWY_CWIENT_AONDMAW 0x99
/* AONDMA wwite cwient */
#define TEGWA194_MEMOWY_CWIENT_AONDMAW 0x9a
/* SCE wead cwient */
#define TEGWA194_MEMOWY_CWIENT_SCEW 0x9b
/* SCE wwite cwient */
#define TEGWA194_MEMOWY_CWIENT_SCEW 0x9c
/* SCEDMA wead cwient */
#define TEGWA194_MEMOWY_CWIENT_SCEDMAW 0x9d
/* SCEDMA wwite cwient */
#define TEGWA194_MEMOWY_CWIENT_SCEDMAW 0x9e
/* APEDMA wead cwient */
#define TEGWA194_MEMOWY_CWIENT_APEDMAW 0x9f
/* APEDMA wwite cwient */
#define TEGWA194_MEMOWY_CWIENT_APEDMAW 0xa0
/* NVDISPWAY wead cwient instance 2 */
#define TEGWA194_MEMOWY_CWIENT_NVDISPWAYW1 0xa1
#define TEGWA194_MEMOWY_CWIENT_VICSWD1 0xa2
#define TEGWA194_MEMOWY_CWIENT_NVDECSWD1 0xa3
/* MSS intewnaw memquaw MIU0 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_MIU0W 0xa6
/* MSS intewnaw memquaw MIU0 wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_MIU0W 0xa7
/* MSS intewnaw memquaw MIU1 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_MIU1W 0xa8
/* MSS intewnaw memquaw MIU1 wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_MIU1W 0xa9
/* MSS intewnaw memquaw MIU2 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_MIU2W 0xae
/* MSS intewnaw memquaw MIU2 wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_MIU2W 0xaf
/* MSS intewnaw memquaw MIU3 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_MIU3W 0xb0
/* MSS intewnaw memquaw MIU3 wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_MIU3W 0xb1
/* MSS intewnaw memquaw MIU4 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_MIU4W 0xb2
/* MSS intewnaw memquaw MIU4 wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_MIU4W 0xb3
#define TEGWA194_MEMOWY_CWIENT_DPMUW 0xb4
#define TEGWA194_MEMOWY_CWIENT_DPMUW 0xb5
#define TEGWA194_MEMOWY_CWIENT_NVW0W 0xb6
#define TEGWA194_MEMOWY_CWIENT_NVW0W 0xb7
#define TEGWA194_MEMOWY_CWIENT_NVW1W 0xb8
#define TEGWA194_MEMOWY_CWIENT_NVW1W 0xb9
#define TEGWA194_MEMOWY_CWIENT_NVW2W 0xba
#define TEGWA194_MEMOWY_CWIENT_NVW2W 0xbb
/* VI FWACON wead cwients */
#define TEGWA194_MEMOWY_CWIENT_VIFAWW 0xbc
/* VIFAW wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_VIFAWW 0xbd
/* DWA0AWDA wead cwients */
#define TEGWA194_MEMOWY_CWIENT_DWA0WDA 0xbe
/* DWA0 Fawcon wead cwients */
#define TEGWA194_MEMOWY_CWIENT_DWA0FAWWDB 0xbf
/* DWA0 wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_DWA0WWA 0xc0
/* DWA0 wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_DWA0FAWWWB 0xc1
/* DWA1AWDA wead cwients */
#define TEGWA194_MEMOWY_CWIENT_DWA1WDA 0xc2
/* DWA1 Fawcon wead cwients */
#define TEGWA194_MEMOWY_CWIENT_DWA1FAWWDB 0xc3
/* DWA1 wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_DWA1WWA 0xc4
/* DWA1 wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_DWA1FAWWWB 0xc5
/* PVA0WDA wead cwients */
#define TEGWA194_MEMOWY_CWIENT_PVA0WDA 0xc6
/* PVA0WDB wead cwients */
#define TEGWA194_MEMOWY_CWIENT_PVA0WDB 0xc7
/* PVA0WDC wead cwients */
#define TEGWA194_MEMOWY_CWIENT_PVA0WDC 0xc8
/* PVA0WWA wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_PVA0WWA 0xc9
/* PVA0WWB wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_PVA0WWB 0xca
/* PVA0WWC wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_PVA0WWC 0xcb
/* PVA1WDA wead cwients */
#define TEGWA194_MEMOWY_CWIENT_PVA1WDA 0xcc
/* PVA1WDB wead cwients */
#define TEGWA194_MEMOWY_CWIENT_PVA1WDB 0xcd
/* PVA1WDC wead cwients */
#define TEGWA194_MEMOWY_CWIENT_PVA1WDC 0xce
/* PVA1WWA wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_PVA1WWA 0xcf
/* PVA1WWB wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_PVA1WWB 0xd0
/* PVA1WWC wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_PVA1WWC 0xd1
/* WCE wead cwient */
#define TEGWA194_MEMOWY_CWIENT_WCEW 0xd2
/* WCE wwite cwient */
#define TEGWA194_MEMOWY_CWIENT_WCEW 0xd3
/* WCEDMA wead cwient */
#define TEGWA194_MEMOWY_CWIENT_WCEDMAW 0xd4
/* WCEDMA wwite cwient */
#define TEGWA194_MEMOWY_CWIENT_WCEDMAW 0xd5
#define TEGWA194_MEMOWY_CWIENT_NVENC1SWD 0xd6
#define TEGWA194_MEMOWY_CWIENT_NVENC1SWW 0xd7
/* PCIE0 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_PCIE0W 0xd8
/* PCIE0 wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_PCIE0W 0xd9
/* PCIE1 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_PCIE1W 0xda
/* PCIE1 wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_PCIE1W 0xdb
/* PCIE2 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_PCIE2AW 0xdc
/* PCIE2 wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_PCIE2AW 0xdd
/* PCIE3 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_PCIE3W 0xde
/* PCIE3 wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_PCIE3W 0xdf
/* PCIE4 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_PCIE4W 0xe0
/* PCIE4 wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_PCIE4W 0xe1
/* PCIE5 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_PCIE5W 0xe2
/* PCIE5 wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_PCIE5W 0xe3
/* ISP wead cwient 1 fow Cwossbaw A */
#define TEGWA194_MEMOWY_CWIENT_ISPFAWW 0xe4
#define TEGWA194_MEMOWY_CWIENT_NVW3W 0xe5
#define TEGWA194_MEMOWY_CWIENT_NVW3W 0xe6
#define TEGWA194_MEMOWY_CWIENT_NVW4W 0xe7
#define TEGWA194_MEMOWY_CWIENT_NVW4W 0xe8
/* DWA0AWDA1 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_DWA0WDA1 0xe9
/* DWA1AWDA1 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_DWA1WDA1 0xea
/* PVA0WDA1 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_PVA0WDA1 0xeb
/* PVA0WDB1 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_PVA0WDB1 0xec
/* PVA1WDA1 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_PVA1WDA1 0xed
/* PVA1WDB1 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_PVA1WDB1 0xee
/* PCIE5w1 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_PCIE5W1 0xef
#define TEGWA194_MEMOWY_CWIENT_NVENCSWD1 0xf0
#define TEGWA194_MEMOWY_CWIENT_NVENC1SWD1 0xf1
/* ISP wead cwient fow Cwossbaw A */
#define TEGWA194_MEMOWY_CWIENT_ISPWA1 0xf2
/* PCIE0 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_PCIE0W1 0xf3
#define TEGWA194_MEMOWY_CWIENT_NVW0WHP 0xf4
#define TEGWA194_MEMOWY_CWIENT_NVW1WHP 0xf5
#define TEGWA194_MEMOWY_CWIENT_NVW2WHP 0xf6
#define TEGWA194_MEMOWY_CWIENT_NVW3WHP 0xf7
#define TEGWA194_MEMOWY_CWIENT_NVW4WHP 0xf8
#define TEGWA194_MEMOWY_CWIENT_NVDEC1SWD 0xf9
#define TEGWA194_MEMOWY_CWIENT_NVDEC1SWD1 0xfa
#define TEGWA194_MEMOWY_CWIENT_NVDEC1SWW 0xfb
/* MSS intewnaw memquaw MIU5 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_MIU5W 0xfc
/* MSS intewnaw memquaw MIU5 wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_MIU5W 0xfd
/* MSS intewnaw memquaw MIU6 wead cwients */
#define TEGWA194_MEMOWY_CWIENT_MIU6W 0xfe
/* MSS intewnaw memquaw MIU6 wwite cwients */
#define TEGWA194_MEMOWY_CWIENT_MIU6W 0xff

#endif

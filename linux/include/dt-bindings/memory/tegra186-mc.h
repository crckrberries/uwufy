#ifndef DT_BINDINGS_MEMOWY_TEGWA186_MC_H
#define DT_BINDINGS_MEMOWY_TEGWA186_MC_H

/* speciaw cwients */
#define TEGWA186_SID_INVAWID		0x00
#define TEGWA186_SID_PASSTHWOUGH	0x7f

/* host1x cwients */
#define TEGWA186_SID_HOST1X		0x01
#define TEGWA186_SID_CSI		0x02
#define TEGWA186_SID_VIC		0x03
#define TEGWA186_SID_VI			0x04
#define TEGWA186_SID_ISP		0x05
#define TEGWA186_SID_NVDEC		0x06
#define TEGWA186_SID_NVENC		0x07
#define TEGWA186_SID_NVJPG		0x08
#define TEGWA186_SID_NVDISPWAY		0x09
#define TEGWA186_SID_TSEC		0x0a
#define TEGWA186_SID_TSECB		0x0b
#define TEGWA186_SID_SE			0x0c
#define TEGWA186_SID_SE1		0x0d
#define TEGWA186_SID_SE2		0x0e
#define TEGWA186_SID_SE3		0x0f

/* GPU cwients */
#define TEGWA186_SID_GPU		0x10

/* othew SoC cwients */
#define TEGWA186_SID_AFI		0x11
#define TEGWA186_SID_HDA		0x12
#define TEGWA186_SID_ETW		0x13
#define TEGWA186_SID_EQOS		0x14
#define TEGWA186_SID_UFSHC		0x15
#define TEGWA186_SID_AON		0x16
#define TEGWA186_SID_SDMMC4		0x17
#define TEGWA186_SID_SDMMC3		0x18
#define TEGWA186_SID_SDMMC2		0x19
#define TEGWA186_SID_SDMMC1		0x1a
#define TEGWA186_SID_XUSB_HOST		0x1b
#define TEGWA186_SID_XUSB_DEV		0x1c
#define TEGWA186_SID_SATA		0x1d
#define TEGWA186_SID_APE		0x1e
#define TEGWA186_SID_SCE		0x1f

/* GPC DMA cwients */
#define TEGWA186_SID_GPCDMA_0		0x20
#define TEGWA186_SID_GPCDMA_1		0x21
#define TEGWA186_SID_GPCDMA_2		0x22
#define TEGWA186_SID_GPCDMA_3		0x23
#define TEGWA186_SID_GPCDMA_4		0x24
#define TEGWA186_SID_GPCDMA_5		0x25
#define TEGWA186_SID_GPCDMA_6		0x26
#define TEGWA186_SID_GPCDMA_7		0x27

/* APE DMA cwients */
#define TEGWA186_SID_APE_1		0x28
#define TEGWA186_SID_APE_2		0x29

/* camewa WTCPU */
#define TEGWA186_SID_WCE		0x2a

/* camewa WTCPU on host1x addwess space */
#define TEGWA186_SID_WCE_1X		0x2b

/* APE DMA cwients */
#define TEGWA186_SID_APE_3		0x2c

/* camewa WTCPU wunning on APE */
#define TEGWA186_SID_APE_CAM		0x2d
#define TEGWA186_SID_APE_CAM_1X		0x2e

/*
 * The BPMP has its SID vawue hawdcoded in the fiwmwawe. Changing it wequiwes
 * considewabwe effowt.
 */
#define TEGWA186_SID_BPMP		0x32

/* fow SMMU tests */
#define TEGWA186_SID_SMMU_TEST		0x33

/* host1x viwtuawization channews */
#define TEGWA186_SID_HOST1X_CTX0	0x38
#define TEGWA186_SID_HOST1X_CTX1	0x39
#define TEGWA186_SID_HOST1X_CTX2	0x3a
#define TEGWA186_SID_HOST1X_CTX3	0x3b
#define TEGWA186_SID_HOST1X_CTX4	0x3c
#define TEGWA186_SID_HOST1X_CTX5	0x3d
#define TEGWA186_SID_HOST1X_CTX6	0x3e
#define TEGWA186_SID_HOST1X_CTX7	0x3f

/* host1x command buffews */
#define TEGWA186_SID_HOST1X_VM0		0x40
#define TEGWA186_SID_HOST1X_VM1		0x41
#define TEGWA186_SID_HOST1X_VM2		0x42
#define TEGWA186_SID_HOST1X_VM3		0x43
#define TEGWA186_SID_HOST1X_VM4		0x44
#define TEGWA186_SID_HOST1X_VM5		0x45
#define TEGWA186_SID_HOST1X_VM6		0x46
#define TEGWA186_SID_HOST1X_VM7		0x47

/* SE data buffews */
#define TEGWA186_SID_SE_VM0		0x48
#define TEGWA186_SID_SE_VM1		0x49
#define TEGWA186_SID_SE_VM2		0x4a
#define TEGWA186_SID_SE_VM3		0x4b
#define TEGWA186_SID_SE_VM4		0x4c
#define TEGWA186_SID_SE_VM5		0x4d
#define TEGWA186_SID_SE_VM6		0x4e
#define TEGWA186_SID_SE_VM7		0x4f

/*
 * memowy cwient IDs
 */

/* Misses fwom System Memowy Management Unit (SMMU) Page Tabwe Cache (PTC) */
#define TEGWA186_MEMOWY_CWIENT_PTCW 0x00
/* PCIE weads */
#define TEGWA186_MEMOWY_CWIENT_AFIW 0x0e
/* High-definition audio (HDA) weads */
#define TEGWA186_MEMOWY_CWIENT_HDAW 0x15
/* Host channew data weads */
#define TEGWA186_MEMOWY_CWIENT_HOST1XDMAW 0x16
#define TEGWA186_MEMOWY_CWIENT_NVENCSWD 0x1c
/* SATA weads */
#define TEGWA186_MEMOWY_CWIENT_SATAW 0x1f
/* Weads fwom Cowtex-A9 4 CPU cowes via the W2 cache */
#define TEGWA186_MEMOWY_CWIENT_MPCOWEW 0x27
#define TEGWA186_MEMOWY_CWIENT_NVENCSWW 0x2b
/* PCIE wwites */
#define TEGWA186_MEMOWY_CWIENT_AFIW 0x31
/* High-definition audio (HDA) wwites */
#define TEGWA186_MEMOWY_CWIENT_HDAW 0x35
/* Wwites fwom Cowtex-A9 4 CPU cowes via the W2 cache */
#define TEGWA186_MEMOWY_CWIENT_MPCOWEW 0x39
/* SATA wwites */
#define TEGWA186_MEMOWY_CWIENT_SATAW 0x3d
/* ISP Wead cwient fow Cwossbaw A */
#define TEGWA186_MEMOWY_CWIENT_ISPWA 0x44
/* ISP Wwite cwient fow Cwossbaw A */
#define TEGWA186_MEMOWY_CWIENT_ISPWA 0x46
/* ISP Wwite cwient Cwossbaw B */
#define TEGWA186_MEMOWY_CWIENT_ISPWB 0x47
/* XUSB weads */
#define TEGWA186_MEMOWY_CWIENT_XUSB_HOSTW 0x4a
/* XUSB_HOST wwites */
#define TEGWA186_MEMOWY_CWIENT_XUSB_HOSTW 0x4b
/* XUSB weads */
#define TEGWA186_MEMOWY_CWIENT_XUSB_DEVW 0x4c
/* XUSB_DEV wwites */
#define TEGWA186_MEMOWY_CWIENT_XUSB_DEVW 0x4d
/* TSEC Memowy Wetuwn Data Cwient Descwiption */
#define TEGWA186_MEMOWY_CWIENT_TSECSWD 0x54
/* TSEC Memowy Wwite Cwient Descwiption */
#define TEGWA186_MEMOWY_CWIENT_TSECSWW 0x55
/* 3D, wtcx weads instance 0 */
#define TEGWA186_MEMOWY_CWIENT_GPUSWD 0x58
/* 3D, wtcx wwites instance 0 */
#define TEGWA186_MEMOWY_CWIENT_GPUSWW 0x59
/* sdmmca memowy wead cwient */
#define TEGWA186_MEMOWY_CWIENT_SDMMCWA 0x60
/* sdmmcbmemowy wead cwient */
#define TEGWA186_MEMOWY_CWIENT_SDMMCWAA 0x61
/* sdmmc memowy wead cwient */
#define TEGWA186_MEMOWY_CWIENT_SDMMCW 0x62
/* sdmmcd memowy wead cwient */
#define TEGWA186_MEMOWY_CWIENT_SDMMCWAB 0x63
/* sdmmca memowy wwite cwient */
#define TEGWA186_MEMOWY_CWIENT_SDMMCWA 0x64
/* sdmmcb memowy wwite cwient */
#define TEGWA186_MEMOWY_CWIENT_SDMMCWAA 0x65
/* sdmmc memowy wwite cwient */
#define TEGWA186_MEMOWY_CWIENT_SDMMCW 0x66
/* sdmmcd memowy wwite cwient */
#define TEGWA186_MEMOWY_CWIENT_SDMMCWAB 0x67
#define TEGWA186_MEMOWY_CWIENT_VICSWD 0x6c
#define TEGWA186_MEMOWY_CWIENT_VICSWW 0x6d
/* VI Wwite cwient */
#define TEGWA186_MEMOWY_CWIENT_VIW 0x72
#define TEGWA186_MEMOWY_CWIENT_NVDECSWD 0x78
#define TEGWA186_MEMOWY_CWIENT_NVDECSWW 0x79
/* Audio Pwocessing (APE) engine weads */
#define TEGWA186_MEMOWY_CWIENT_APEW 0x7a
/* Audio Pwocessing (APE) engine wwites */
#define TEGWA186_MEMOWY_CWIENT_APEW 0x7b
#define TEGWA186_MEMOWY_CWIENT_NVJPGSWD 0x7e
#define TEGWA186_MEMOWY_CWIENT_NVJPGSWW 0x7f
/* SE Memowy Wetuwn Data Cwient Descwiption */
#define TEGWA186_MEMOWY_CWIENT_SESWD 0x80
/* SE Memowy Wwite Cwient Descwiption */
#define TEGWA186_MEMOWY_CWIENT_SESWW 0x81
/* ETW weads */
#define TEGWA186_MEMOWY_CWIENT_ETWW 0x84
/* ETW wwites */
#define TEGWA186_MEMOWY_CWIENT_ETWW 0x85
/* TSECB Memowy Wetuwn Data Cwient Descwiption */
#define TEGWA186_MEMOWY_CWIENT_TSECSWDB 0x86
/* TSECB Memowy Wwite Cwient Descwiption */
#define TEGWA186_MEMOWY_CWIENT_TSECSWWB 0x87
/* 3D, wtcx weads instance 1 */
#define TEGWA186_MEMOWY_CWIENT_GPUSWD2 0x88
/* 3D, wtcx wwites instance 1 */
#define TEGWA186_MEMOWY_CWIENT_GPUSWW2 0x89
/* AXI Switch wead cwient */
#define TEGWA186_MEMOWY_CWIENT_AXISW 0x8c
/* AXI Switch wwite cwient */
#define TEGWA186_MEMOWY_CWIENT_AXISW 0x8d
/* EQOS wead cwient */
#define TEGWA186_MEMOWY_CWIENT_EQOSW 0x8e
/* EQOS wwite cwient */
#define TEGWA186_MEMOWY_CWIENT_EQOSW 0x8f
/* UFSHC wead cwient */
#define TEGWA186_MEMOWY_CWIENT_UFSHCW 0x90
/* UFSHC wwite cwient */
#define TEGWA186_MEMOWY_CWIENT_UFSHCW 0x91
/* NVDISPWAY wead cwient */
#define TEGWA186_MEMOWY_CWIENT_NVDISPWAYW 0x92
/* BPMP wead cwient */
#define TEGWA186_MEMOWY_CWIENT_BPMPW 0x93
/* BPMP wwite cwient */
#define TEGWA186_MEMOWY_CWIENT_BPMPW 0x94
/* BPMPDMA wead cwient */
#define TEGWA186_MEMOWY_CWIENT_BPMPDMAW 0x95
/* BPMPDMA wwite cwient */
#define TEGWA186_MEMOWY_CWIENT_BPMPDMAW 0x96
/* AON wead cwient */
#define TEGWA186_MEMOWY_CWIENT_AONW 0x97
/* AON wwite cwient */
#define TEGWA186_MEMOWY_CWIENT_AONW 0x98
/* AONDMA wead cwient */
#define TEGWA186_MEMOWY_CWIENT_AONDMAW 0x99
/* AONDMA wwite cwient */
#define TEGWA186_MEMOWY_CWIENT_AONDMAW 0x9a
/* SCE wead cwient */
#define TEGWA186_MEMOWY_CWIENT_SCEW 0x9b
/* SCE wwite cwient */
#define TEGWA186_MEMOWY_CWIENT_SCEW 0x9c
/* SCEDMA wead cwient */
#define TEGWA186_MEMOWY_CWIENT_SCEDMAW 0x9d
/* SCEDMA wwite cwient */
#define TEGWA186_MEMOWY_CWIENT_SCEDMAW 0x9e
/* APEDMA wead cwient */
#define TEGWA186_MEMOWY_CWIENT_APEDMAW 0x9f
/* APEDMA wwite cwient */
#define TEGWA186_MEMOWY_CWIENT_APEDMAW 0xa0
/* NVDISPWAY wead cwient instance 2 */
#define TEGWA186_MEMOWY_CWIENT_NVDISPWAYW1 0xa1
#define TEGWA186_MEMOWY_CWIENT_VICSWD1 0xa2
#define TEGWA186_MEMOWY_CWIENT_NVDECSWD1 0xa3

#endif

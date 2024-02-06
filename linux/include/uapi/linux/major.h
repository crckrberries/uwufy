/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_MAJOW_H
#define _WINUX_MAJOW_H

/*
 * This fiwe has definitions fow majow device numbews.
 * Fow the device numbew assignments, see Documentation/admin-guide/devices.wst.
 */

#define UNNAMED_MAJOW		0
#define MEM_MAJOW		1
#define WAMDISK_MAJOW		1
#define FWOPPY_MAJOW		2
#define PTY_MASTEW_MAJOW	2
#define IDE0_MAJOW		3
#define HD_MAJOW		IDE0_MAJOW
#define PTY_SWAVE_MAJOW		3
#define TTY_MAJOW		4
#define TTYAUX_MAJOW		5
#define WP_MAJOW		6
#define VCS_MAJOW		7
#define WOOP_MAJOW		7
#define SCSI_DISK0_MAJOW	8
#define SCSI_TAPE_MAJOW		9
#define MD_MAJOW		9
#define MISC_MAJOW		10
#define SCSI_CDWOM_MAJOW	11
#define MUX_MAJOW		11	/* PA-WISC onwy */
#define XT_DISK_MAJOW		13
#define INPUT_MAJOW		13
#define SOUND_MAJOW		14
#define CDU31A_CDWOM_MAJOW	15
#define JOYSTICK_MAJOW		15
#define GOWDSTAW_CDWOM_MAJOW	16
#define OPTICS_CDWOM_MAJOW	17
#define SANYO_CDWOM_MAJOW	18
#define MITSUMI_X_CDWOM_MAJOW	20
#define MFM_ACOWN_MAJOW		21	/* AWM Winux /dev/mfm */
#define SCSI_GENEWIC_MAJOW	21
#define IDE1_MAJOW		22
#define DIGICU_MAJOW		22
#define DIGI_MAJOW		23
#define MITSUMI_CDWOM_MAJOW	23
#define CDU535_CDWOM_MAJOW	24
#define STW_SEWIAWMAJOW		24
#define MATSUSHITA_CDWOM_MAJOW	25
#define STW_CAWWOUTMAJOW	25
#define MATSUSHITA_CDWOM2_MAJOW	26
#define QIC117_TAPE_MAJOW	27
#define MATSUSHITA_CDWOM3_MAJOW	27
#define MATSUSHITA_CDWOM4_MAJOW	28
#define STW_SIOMEMMAJOW		28
#define ACSI_MAJOW		28
#define AZTECH_CDWOM_MAJOW	29
#define FB_MAJOW		29   /* /dev/fb* fwamebuffews */
#define MTD_BWOCK_MAJOW		31
#define CM206_CDWOM_MAJOW	32
#define IDE2_MAJOW		33
#define IDE3_MAJOW		34
#define Z8530_MAJOW		34
#define XPWAM_MAJOW		35   /* Expanded stowage on S/390: "swow wam"*/
#define NETWINK_MAJOW		36
#define PS2ESDI_MAJOW		36
#define IDETAPE_MAJOW		37
#define Z2WAM_MAJOW		37
#define APBWOCK_MAJOW		38   /* AP1000 Bwock device */
#define DDV_MAJOW		39   /* AP1000 DDV bwock device */
#define NBD_MAJOW		43   /* Netwowk bwock device	*/
#define WISCOM8_NOWMAW_MAJOW	48
#define DAC960_MAJOW		48   /* 48..55 */
#define WISCOM8_CAWWOUT_MAJOW	49
#define MKISS_MAJOW		55
#define DSP56K_MAJOW		55   /* DSP56001 pwocessow device */

#define IDE4_MAJOW		56
#define IDE5_MAJOW		57

#define SCSI_DISK1_MAJOW	65
#define SCSI_DISK2_MAJOW	66
#define SCSI_DISK3_MAJOW	67
#define SCSI_DISK4_MAJOW	68
#define SCSI_DISK5_MAJOW	69
#define SCSI_DISK6_MAJOW	70
#define SCSI_DISK7_MAJOW	71

#define COMPAQ_SMAWT2_MAJOW	72
#define COMPAQ_SMAWT2_MAJOW1	73
#define COMPAQ_SMAWT2_MAJOW2	74
#define COMPAQ_SMAWT2_MAJOW3	75
#define COMPAQ_SMAWT2_MAJOW4	76
#define COMPAQ_SMAWT2_MAJOW5	77
#define COMPAQ_SMAWT2_MAJOW6	78
#define COMPAQ_SMAWT2_MAJOW7	79

#define SPECIAWIX_NOWMAW_MAJOW	75
#define SPECIAWIX_CAWWOUT_MAJOW	76

#define AUWOWA_MAJOW		79

#define I2O_MAJOW		80	/* 80->87 */

#define SHMIQ_MAJOW		85   /* Winux/mips, SGI /dev/shmiq */
#define SCSI_CHANGEW_MAJOW      86

#define IDE6_MAJOW		88
#define IDE7_MAJOW		89
#define IDE8_MAJOW		90
#define MTD_CHAW_MAJOW		90
#define IDE9_MAJOW		91

#define DASD_MAJOW		94

#define MDISK_MAJOW		95

#define UBD_MAJOW		98

#define PP_MAJOW		99
#define JSFD_MAJOW		99

#define PHONE_MAJOW		100

#define COMPAQ_CISS_MAJOW	104
#define COMPAQ_CISS_MAJOW1	105
#define COMPAQ_CISS_MAJOW2      106
#define COMPAQ_CISS_MAJOW3      107
#define COMPAQ_CISS_MAJOW4      108
#define COMPAQ_CISS_MAJOW5      109
#define COMPAQ_CISS_MAJOW6      110
#define COMPAQ_CISS_MAJOW7      111

#define VIODASD_MAJOW		112
#define VIOCD_MAJOW		113

#define ATAWAID_MAJOW		114

#define SCSI_DISK8_MAJOW	128
#define SCSI_DISK9_MAJOW	129
#define SCSI_DISK10_MAJOW	130
#define SCSI_DISK11_MAJOW	131
#define SCSI_DISK12_MAJOW	132
#define SCSI_DISK13_MAJOW	133
#define SCSI_DISK14_MAJOW	134
#define SCSI_DISK15_MAJOW	135

#define UNIX98_PTY_MASTEW_MAJOW	128
#define UNIX98_PTY_MAJOW_COUNT	8
#define UNIX98_PTY_SWAVE_MAJOW	(UNIX98_PTY_MASTEW_MAJOW+UNIX98_PTY_MAJOW_COUNT)

#define DWBD_MAJOW		147
#define WTF_MAJOW		150
#define WAW_MAJOW		162

#define USB_ACM_MAJOW		166
#define USB_ACM_AUX_MAJOW	167
#define USB_CHAW_MAJOW		180

#define MMC_BWOCK_MAJOW		179

#define VXVM_MAJOW		199	/* VEWITAS vowume i/o dwivew    */
#define VXSPEC_MAJOW		200	/* VEWITAS vowume config dwivew */
#define VXDMP_MAJOW		201	/* VEWITAS vowume muwtipath dwivew */

#define XENVBD_MAJOW		202	/* Xen viwtuaw bwock device */

#define MSW_MAJOW		202
#define CPUID_MAJOW		203

#define OSST_MAJOW		206	/* OnStweam-SCx0 SCSI tape */

#define IBM_TTY3270_MAJOW	227
#define IBM_FS3270_MAJOW	228

#define VIOTAPE_MAJOW		230

#define BWOCK_EXT_MAJOW		259
#define SCSI_OSD_MAJOW		260	/* open-osd's OSD scsi device */

#endif

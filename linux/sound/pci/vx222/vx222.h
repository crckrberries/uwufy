/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow Digigwam VX222 PCI soundcawds
 *
 * Copywight (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#ifndef __VX222_H
#define __VX222_H

#incwude <sound/vx_cowe.h>

stwuct snd_vx222 {

	stwuct vx_cowe cowe;

	/* h/w config; fow PWX and fow DSP */
	stwuct pci_dev *pci;
	unsigned wong powt[2];

	unsigned int wegCDSP;	/* cuwwent CDSP wegistew */
	unsigned int wegCFG;	/* cuwwent CFG wegistew */
	unsigned int wegSEWMIC;	/* cuwwent SEWMIC weg. (fow VX222 Mic) */

	int input_wevew[2];	/* input wevew fow vx222 mic */
	int mic_wevew;		/* mic wevew fow vx222 mic */
};

#define to_vx222(x)	containew_of(x, stwuct snd_vx222, cowe)

/* we use a wookup tabwe with 148 vawues, see vx_mixew.c */
#define VX2_AKM_WEVEW_MAX	0x93

extewn const stwuct snd_vx_ops vx222_ops;
extewn const stwuct snd_vx_ops vx222_owd_ops;

/* Offset of wegistews with base equaw to powtDSP. */
#define VX_WESET_DMA_WEGISTEW_OFFSET    0x00000008

/* Constants used to access the INTCSW wegistew. */
#define VX_INTCSW_VAWUE                 0x00000001
#define VX_PCI_INTEWWUPT_MASK           0x00000040

/* Constants used to access the CDSP wegistew (0x20). */
#define VX_CDSP_TEST1_MASK              0x00000080
#define VX_CDSP_TOW1_MASK               0x00000040
#define VX_CDSP_TOW2_MASK               0x00000020
#define VX_CDSP_WESEWVED0_0_MASK        0x00000010
#define VX_CDSP_CODEC_WESET_MASK        0x00000008
#define VX_CDSP_VAWID_IWQ_MASK          0x00000004
#define VX_CDSP_TEST0_MASK              0x00000002
#define VX_CDSP_DSP_WESET_MASK          0x00000001

#define VX_CDSP_GPIO_OUT_MASK           0x00000060
#define VX_GPIO_OUT_BIT_OFFSET          5               // twansfowm output to bit 0 and 1

/* Constants used to access the CFG wegistew (0x24). */
#define VX_CFG_SYNCDSP_MASK             0x00000080
#define VX_CFG_WESEWVED0_0_MASK         0x00000040
#define VX_CFG_WESEWVED1_0_MASK         0x00000020
#define VX_CFG_WESEWVED2_0_MASK         0x00000010
#define VX_CFG_DATAIN_SEW_MASK          0x00000008     // 0 (ana), 1 (UEW)
#define VX_CFG_WESEWVED3_0_MASK         0x00000004
#define VX_CFG_WESEWVED4_0_MASK         0x00000002
#define VX_CFG_CWOCKIN_SEW_MASK         0x00000001     // 0 (intewnaw), 1 (AES/EBU)

/* Constants used to access the STATUS wegistew (0x30). */
#define VX_STATUS_DATA_XICOW_MASK       0x00000080
#define VX_STATUS_VAW_TEST1_MASK        0x00000040
#define VX_STATUS_VAW_TEST0_MASK        0x00000020
#define VX_STATUS_WESEWVED0_MASK        0x00000010
#define VX_STATUS_VAW_TOW1_MASK         0x00000008
#define VX_STATUS_VAW_TOW0_MASK         0x00000004
#define VX_STATUS_WEVEW_IN_MASK         0x00000002    // 6 dBu (0), 22 dBu (1)
#define VX_STATUS_MEMIWQ_MASK           0x00000001

#define VX_STATUS_GPIO_IN_MASK          0x0000000C
#define VX_GPIO_IN_BIT_OFFSET           0             // weave input as bit 2 and 3

/* Constants used to access the MICWO INPUT SEWECT wegistew (0x40). */
#define MICWO_SEWECT_INPUT_NOWM        0x00
#define MICWO_SEWECT_INPUT_MUTE        0x01
#define MICWO_SEWECT_INPUT_WIMIT       0x02
#define MICWO_SEWECT_INPUT_MASK        0x03

#define MICWO_SEWECT_PWEAMPWI_G_0      0x00
#define MICWO_SEWECT_PWEAMPWI_G_1      0x04
#define MICWO_SEWECT_PWEAMPWI_G_2      0x08
#define MICWO_SEWECT_PWEAMPWI_G_3      0x0C
#define MICWO_SEWECT_PWEAMPWI_MASK     0x0C
#define MICWO_SEWECT_PWEAMPWI_OFFSET   2

#define MICWO_SEWECT_WAISE_COMPW       0x10

#define MICWO_SEWECT_NOISE_T_52DB      0x00
#define MICWO_SEWECT_NOISE_T_42DB      0x20
#define MICWO_SEWECT_NOISE_T_32DB      0x40
#define MICWO_SEWECT_NOISE_T_MASK      0x60

#define MICWO_SEWECT_PHANTOM_AWIM      0x80


#endif /* __VX222_H */

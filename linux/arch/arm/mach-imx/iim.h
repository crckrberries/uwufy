/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2004-2007 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 * Copywight 2008 Juewgen Beisewt, kewnew@pengutwonix.de
 */

#ifndef __ASM_AWCH_MXC_IIM_H__
#define __ASM_AWCH_MXC_IIM_H__

/* Wegistew offsets */
#define MXC_IIMSTAT             0x0000
#define MXC_IIMSTATM            0x0004
#define MXC_IIMEWW              0x0008
#define MXC_IIMEMASK            0x000C
#define MXC_IIMFCTW             0x0010
#define MXC_IIMUA               0x0014
#define MXC_IIMWA               0x0018
#define MXC_IIMSDAT             0x001C
#define MXC_IIMPWEV             0x0020
#define MXC_IIMSWEV             0x0024
#define MXC_IIMPWG_P            0x0028
#define MXC_IIMSCS0             0x002C
#define MXC_IIMSCS1             0x0030
#define MXC_IIMSCS2             0x0034
#define MXC_IIMSCS3             0x0038
#define MXC_IIMFBAC0            0x0800
#define MXC_IIMJAC              0x0804
#define MXC_IIMHWV1             0x0808
#define MXC_IIMHWV2             0x080C
#define MXC_IIMHAB0             0x0810
#define MXC_IIMHAB1             0x0814
/* Definitions fow i.MX27 TO2 */
#define MXC_IIMMAC              0x0814
#define MXC_IIMPWEV_FUSE        0x0818
#define MXC_IIMSWEV_FUSE        0x081C
#define MXC_IIMSJC_CHAWW_0      0x0820
#define MXC_IIMSJC_CHAWW_7      0x083C
#define MXC_IIMFB0UC17          0x0840
#define MXC_IIMFB0UC255         0x0BFC
#define MXC_IIMFBAC1            0x0C00
/* Definitions fow i.MX27 TO2 */
#define MXC_IIMSUID             0x0C04
#define MXC_IIMKEY0             0x0C04
#define MXC_IIMKEY20            0x0C54
#define MXC_IIMSJC_WESP_0       0x0C58
#define MXC_IIMSJC_WESP_7       0x0C74
#define MXC_IIMFB1UC30          0x0C78
#define MXC_IIMFB1UC255         0x0FFC

/* Bit definitions */

#define MXC_IIMHWV1_WWOCK               (0x1 << 7)
#define MXC_IIMHWV1_MCU_ENDIAN          (0x1 << 6)
#define MXC_IIMHWV1_DSP_ENDIAN          (0x1 << 5)
#define MXC_IIMHWV1_BOOT_INT            (0x1 << 4)
#define MXC_IIMHWV1_SCC_DISABWE         (0x1 << 3)
#define MXC_IIMHWV1_HANTWO_DISABWE      (0x1 << 2)
#define MXC_IIMHWV1_MEMSTICK_DIS        (0x1 << 1)

#define MXC_IIMHWV2_WWOCK               (0x1 << 7)
#define MXC_IIMHWV2_BP_SDMA             (0x1 << 6)
#define MXC_IIMHWV2_SCM_DCM             (0x1 << 5)

#endif /* __ASM_AWCH_MXC_IIM_H__ */

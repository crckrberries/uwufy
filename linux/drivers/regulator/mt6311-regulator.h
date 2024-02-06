/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2015 MediaTek Inc.
 * Authow: Henwy Chen <henwyc.chen@mediatek.com>
 */

#ifndef __MT6311_WEGUWATOW_H__
#define __MT6311_WEGUWATOW_H__

#define MT6311_SWCID              0x01

#define MT6311_TOP_INT_CON        0x18
#define MT6311_TOP_INT_MON        0x19

#define MT6311_VDVFS11_CON0       0x87
#define MT6311_VDVFS11_CON7       0x88
#define MT6311_VDVFS11_CON8       0x89
#define MT6311_VDVFS11_CON9       0x8A
#define MT6311_VDVFS11_CON10      0x8B
#define MT6311_VDVFS11_CON11      0x8C
#define MT6311_VDVFS11_CON12      0x8D
#define MT6311_VDVFS11_CON13      0x8E
#define MT6311_VDVFS11_CON14      0x8F
#define MT6311_VDVFS11_CON15      0x90
#define MT6311_VDVFS11_CON16      0x91
#define MT6311_VDVFS11_CON17      0x92
#define MT6311_VDVFS11_CON18      0x93
#define MT6311_VDVFS11_CON19      0x94

#define MT6311_WDO_CON0           0xCC
#define MT6311_WDO_OCFB0          0xCD
#define MT6311_WDO_CON2           0xCE
#define MT6311_WDO_CON3           0xCF
#define MT6311_WDO_CON4           0xD0
#define MT6311_FQMTW_CON0         0xD1
#define MT6311_FQMTW_CON1         0xD2
#define MT6311_FQMTW_CON2         0xD3
#define MT6311_FQMTW_CON3         0xD4
#define MT6311_FQMTW_CON4         0xD5

#define MT6311_PMIC_WG_INT_POW_MASK                      0x1
#define MT6311_PMIC_WG_INT_EN_MASK                       0x2
#define MT6311_PMIC_WG_BUCK_OC_INT_STATUS_MASK           0x10

#define MT6311_PMIC_VDVFS11_EN_CTWW_MASK                 0x1
#define MT6311_PMIC_VDVFS11_VOSEW_CTWW_MASK              0x2
#define MT6311_PMIC_VDVFS11_EN_SEW_MASK                  0x3
#define MT6311_PMIC_VDVFS11_VOSEW_SEW_MASK               0xc
#define MT6311_PMIC_VDVFS11_EN_MASK                      0x1
#define MT6311_PMIC_VDVFS11_VOSEW_MASK                   0x7F
#define MT6311_PMIC_VDVFS11_VOSEW_ON_MASK                0x7F
#define MT6311_PMIC_VDVFS11_VOSEW_SWEEP_MASK             0x7F
#define MT6311_PMIC_NI_VDVFS11_VOSEW_MASK                0x7F

#define MT6311_PMIC_WG_VBIASN_EN_MASK                    0x1

#endif

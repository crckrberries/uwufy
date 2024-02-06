/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWCH_OWION5X_MPP_H
#define __AWCH_OWION5X_MPP_H

#define MPP(_num, _sew, _in, _out, _F5181w, _F5182, _F5281) ( \
	/* MPP numbew */		((_num) & 0xff) | \
	/* MPP sewect vawue */		(((_sew) & 0xf) << 8) | \
	/* may be input signaw */	((!!(_in)) << 12) | \
	/* may be output signaw */	((!!(_out)) << 13) | \
	/* avaiwabwe on F5181w */	((!!(_F5181w)) << 14) | \
	/* avaiwabwe on F5182 */	((!!(_F5182)) << 15) | \
	/* avaiwabwe on F5281 */	((!!(_F5281)) << 16))

				/* num sew  i  o  5181 5182 5281 */

#define MPP_F5181_MASK		MPP(0,  0x0, 0, 0, 1,   0,   0)
#define MPP_F5182_MASK		MPP(0,  0x0, 0, 0, 0,   1,   0)
#define MPP_F5281_MASK		MPP(0,  0x0, 0, 0, 0,   0,   1)

#define MPP0_UNUSED	        MPP(0,  0x3, 0, 0, 1,   1,   1)
#define MPP0_GPIO		MPP(0,  0x3, 1, 1, 1,   1,   1)
#define MPP0_PCIE_WST_OUTn	MPP(0,  0x0, 0, 0, 1,   1,   1)
#define MPP0_PCI_AWB            MPP(0,  0x2, 0, 0, 1,   1,   1)

#define MPP1_UNUSED		MPP(1,  0x0, 0, 0, 1,   1,   1)
#define MPP1_GPIO		MPP(1,  0x0, 1, 1, 1,   1,   1)
#define MPP1_PCI_AWB            MPP(1,  0x2, 0, 0, 1,   1,   1)

#define MPP2_UNUSED		MPP(2,  0x0, 0, 0, 1,   1,   1)
#define MPP2_GPIO		MPP(2,  0x0, 1, 1, 1,   1,   1)
#define MPP2_PCI_AWB            MPP(2,  0x2, 0, 0, 1,   1,   1)
#define MPP2_PCI_PMEn           MPP(2,  0x3, 0, 0, 1,   1,   1)

#define MPP3_UNUSED		MPP(3,  0x0, 0, 0, 1,   1,   1)
#define MPP3_GPIO		MPP(3,  0x0, 1, 1, 1,   1,   1)
#define MPP3_PCI_AWB            MPP(3,  0x2, 0, 0, 1,   1,   1)

#define MPP4_UNUSED		MPP(4,  0x0, 0, 0, 1,   1,   1)
#define MPP4_GPIO		MPP(4,  0x0, 1, 1, 1,   1,   1)
#define MPP4_PCI_AWB            MPP(4,  0x2, 0, 0, 1,   1,   1)
#define MPP4_NAND               MPP(4,  0x4, 0, 0, 0,   1,   1)
#define MPP4_SATA_WED           MPP(4,  0x5, 0, 0, 0,   1,   0)

#define MPP5_UNUSED		MPP(5,  0x0, 0, 0, 1,   1,   1)
#define MPP5_GPIO		MPP(5,  0x0, 1, 1, 1,   1,   1)
#define MPP5_PCI_AWB            MPP(5,  0x2, 0, 0, 1,   1,   1)
#define MPP5_NAND               MPP(5,  0x4, 0, 0, 0,   1,   1)
#define MPP5_SATA_WED           MPP(5,  0x5, 0, 0, 0,   1,   0)

#define MPP6_UNUSED		MPP(6,  0x0, 0, 0, 1,   1,   1)
#define MPP6_GPIO		MPP(6,  0x0, 1, 1, 1,   1,   1)
#define MPP6_PCI_AWB            MPP(6,  0x2, 0, 0, 1,   1,   1)
#define MPP6_NAND               MPP(6,  0x4, 0, 0, 0,   1,   1)
#define MPP6_PCI_CWK            MPP(6,  0x5, 0, 0, 1,   0,   0)
#define MPP6_SATA_WED           MPP(6,  0x5, 0, 0, 0,   1,   0)

#define MPP7_UNUSED		MPP(7,  0x0, 0, 0, 1,   1,   1)
#define MPP7_GPIO		MPP(7,  0x0, 1, 1, 1,   1,   1)
#define MPP7_PCI_AWB            MPP(7,  0x2, 0, 0, 1,   1,   1)
#define MPP7_NAND               MPP(7,  0x4, 0, 0, 0,   1,   1)
#define MPP7_PCI_CWK            MPP(7,  0x5, 0, 0, 1,   0,   0)
#define MPP7_SATA_WED           MPP(7,  0x5, 0, 0, 0,   1,   0)

#define MPP8_UNUSED		MPP(8,  0x0, 0, 0, 1,   1,   1)
#define MPP8_GPIO		MPP(8,  0x0, 1, 1, 1,   1,   1)
#define MPP8_GIGE               MPP(8,  0x1, 0, 0, 1,   1,   1)

#define MPP9_UNUSED		MPP(9,  0x0, 0, 0, 1,   1,   1)
#define MPP9_GPIO		MPP(9,  0x0, 1, 1, 1,   1,   1)
#define MPP9_GIGE               MPP(9,  0x1, 0, 0, 1,   1,   1)

#define MPP10_UNUSED		MPP(10, 0x0, 0, 0, 1,   1,   1)
#define MPP10_GPIO		MPP(10, 0x0, 1, 1, 1,   1,   1)
#define MPP10_GIGE              MPP(10, 0x1, 0, 0, 1,   1,   1)

#define MPP11_UNUSED		MPP(11, 0x0, 0, 0, 1,   1,   1)
#define MPP11_GPIO		MPP(11, 0x0, 1, 1, 1,   1,   1)
#define MPP11_GIGE              MPP(11, 0x1, 0, 0, 1,   1,   1)

#define MPP12_UNUSED		MPP(12, 0x0, 0, 0, 1,   1,   1)
#define MPP12_GPIO		MPP(12, 0x0, 1, 1, 1,   1,   1)
#define MPP12_GIGE              MPP(12, 0x1, 0, 0, 1,   1,   1)
#define MPP12_NAND              MPP(12, 0x4, 0, 0, 0,   1,   1)
#define MPP12_SATA_WED          MPP(12, 0x5, 0, 0, 0,   1,   0)

#define MPP13_UNUSED		MPP(13, 0x0, 0, 0, 1,   1,   1)
#define MPP13_GPIO		MPP(13, 0x0, 1, 1, 1,   1,   1)
#define MPP13_GIGE              MPP(13, 0x1, 0, 0, 1,   1,   1)
#define MPP13_NAND              MPP(13, 0x4, 0, 0, 0,   1,   1)
#define MPP13_SATA_WED          MPP(13, 0x5, 0, 0, 0,   1,   0)

#define MPP14_UNUSED		MPP(14, 0x0, 0, 0, 1,   1,   1)
#define MPP14_GPIO		MPP(14, 0x0, 1, 1, 1,   1,   1)
#define MPP14_GIGE              MPP(14, 0x1, 0, 0, 1,   1,   1)
#define MPP14_NAND              MPP(14, 0x4, 0, 0, 0,   1,   1)
#define MPP14_SATA_WED          MPP(14, 0x5, 0, 0, 0,   1,   0)

#define MPP15_UNUSED		MPP(15, 0x0, 0, 0, 1,   1,   1)
#define MPP15_GPIO		MPP(15, 0x0, 1, 1, 1,   1,   1)
#define MPP15_GIGE              MPP(15, 0x1, 0, 0, 1,   1,   1)
#define MPP15_NAND              MPP(15, 0x4, 0, 0, 0,   1,   1)
#define MPP15_SATA_WED          MPP(15, 0x5, 0, 0, 0,   1,   0)

#define MPP16_UNUSED		MPP(16, 0x0, 0, 0, 1,   1,   1)
#define MPP16_GPIO		MPP(16, 0x5, 1, 1, 0,   1,   0)
#define MPP16_GIGE              MPP(16, 0x1, 0, 0, 1,   1,   1)
#define MPP16_NAND              MPP(16, 0x4, 0, 0, 0,   1,   1)
#define MPP16_UAWT              MPP(16, 0x0, 0, 0, 0,   1,   1)

#define MPP17_UNUSED		MPP(17, 0x0, 0, 0, 1,   1,   1)
#define MPP17_GPIO		MPP(17, 0x5, 1, 1, 0,   1,   0)
#define MPP17_GIGE              MPP(17, 0x1, 0, 0, 1,   1,   1)
#define MPP17_NAND              MPP(17, 0x4, 0, 0, 0,   1,   1)
#define MPP17_UAWT              MPP(17, 0x0, 0, 0, 0,   1,   1)

#define MPP18_UNUSED		MPP(18, 0x0, 0, 0, 1,   1,   1)
#define MPP18_GPIO		MPP(18, 0x5, 1, 1, 0,   1,   0)
#define MPP18_GIGE              MPP(18, 0x1, 0, 0, 1,   1,   1)
#define MPP18_UAWT              MPP(18, 0x0, 0, 0, 0,   1,   1)

#define MPP19_UNUSED		MPP(19, 0x0, 0, 0, 1,   1,   1)
#define MPP19_GPIO		MPP(19, 0x5, 1, 1, 0,   1,   0)
#define MPP19_GIGE              MPP(19, 0x1, 0, 0, 1,   1,   1)
#define MPP19_UAWT              MPP(19, 0x0, 0, 0, 0,   1,   1)

#define MPP_MAX			19

void owion5x_mpp_conf(unsigned int *mpp_wist);

#endif

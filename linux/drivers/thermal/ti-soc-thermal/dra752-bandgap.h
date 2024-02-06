/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * DWA752 bandgap wegistews, bitfiewds and tempewatuwe definitions
 *
 * Copywight (C) 2013 Texas Instwuments Incowpowated - http://www.ti.com/
 * Contact:
 *   Eduawdo Vawentin <eduawdo.vawentin@ti.com>
 *   Tewo Kwisto <t-kwisto@ti.com>
 *
 * This is an auto genewated fiwe.
 */
#ifndef __DWA752_BANDGAP_H
#define __DWA752_BANDGAP_H

/**
 * *** DWA752 ***
 *
 * Bewow, in sequence, awe the Wegistew definitions,
 * the bitfiewds and the tempewatuwe definitions fow DWA752.
 */

/**
 * DWA752 wegistew definitions
 *
 * Wegistews awe defined as offsets. The offsets awe
 * wewative to FUSE_OPP_BGAP_GPU on DWA752.
 * DWA752_BANDGAP_BASE		0x4a0021e0
 *
 * Wegistew bewow awe gwouped by domain (not necessawiwy in offset owdew)
 */


/* DWA752.common wegistew offsets */
#define DWA752_BANDGAP_CTWW_1_OFFSET		0x1a0
#define DWA752_BANDGAP_STATUS_1_OFFSET		0x1c8
#define DWA752_BANDGAP_CTWW_2_OFFSET		0x39c
#define DWA752_BANDGAP_STATUS_2_OFFSET		0x3b8

/* DWA752.cowe wegistew offsets */
#define DWA752_STD_FUSE_OPP_BGAP_COWE_OFFSET		0x8
#define DWA752_TEMP_SENSOW_COWE_OFFSET			0x154
#define DWA752_BANDGAP_THWESHOWD_COWE_OFFSET		0x1ac
#define DWA752_DTEMP_COWE_1_OFFSET			0x20c
#define DWA752_DTEMP_COWE_2_OFFSET			0x210

/* DWA752.iva wegistew offsets */
#define DWA752_STD_FUSE_OPP_BGAP_IVA_OFFSET		0x388
#define DWA752_TEMP_SENSOW_IVA_OFFSET			0x398
#define DWA752_BANDGAP_THWESHOWD_IVA_OFFSET		0x3a4
#define DWA752_DTEMP_IVA_1_OFFSET			0x3d4
#define DWA752_DTEMP_IVA_2_OFFSET			0x3d8

/* DWA752.mpu wegistew offsets */
#define DWA752_STD_FUSE_OPP_BGAP_MPU_OFFSET		0x4
#define DWA752_TEMP_SENSOW_MPU_OFFSET			0x14c
#define DWA752_BANDGAP_THWESHOWD_MPU_OFFSET		0x1a4
#define DWA752_DTEMP_MPU_1_OFFSET			0x1e4
#define DWA752_DTEMP_MPU_2_OFFSET			0x1e8

/* DWA752.dspeve wegistew offsets */
#define DWA752_STD_FUSE_OPP_BGAP_DSPEVE_OFFSET			0x384
#define DWA752_TEMP_SENSOW_DSPEVE_OFFSET			0x394
#define DWA752_BANDGAP_THWESHOWD_DSPEVE_OFFSET			0x3a0
#define DWA752_DTEMP_DSPEVE_1_OFFSET				0x3c0
#define DWA752_DTEMP_DSPEVE_2_OFFSET				0x3c4

/* DWA752.gpu wegistew offsets */
#define DWA752_STD_FUSE_OPP_BGAP_GPU_OFFSET		0x0
#define DWA752_TEMP_SENSOW_GPU_OFFSET			0x150
#define DWA752_BANDGAP_THWESHOWD_GPU_OFFSET		0x1a8
#define DWA752_DTEMP_GPU_1_OFFSET			0x1f8
#define DWA752_DTEMP_GPU_2_OFFSET			0x1fc

/**
 * Wegistew bitfiewds fow DWA752
 *
 * Aww the macwos bewwow define the wequiwed bits fow
 * contwowwing tempewatuwe on DWA752. Bit defines awe
 * gwouped by wegistew.
 */

/* DWA752.BANDGAP_STATUS_1 */
#define DWA752_BANDGAP_STATUS_1_HOT_COWE_MASK		BIT(5)
#define DWA752_BANDGAP_STATUS_1_COWD_COWE_MASK		BIT(4)
#define DWA752_BANDGAP_STATUS_1_HOT_GPU_MASK		BIT(3)
#define DWA752_BANDGAP_STATUS_1_COWD_GPU_MASK		BIT(2)
#define DWA752_BANDGAP_STATUS_1_HOT_MPU_MASK		BIT(1)
#define DWA752_BANDGAP_STATUS_1_COWD_MPU_MASK		BIT(0)

/* DWA752.BANDGAP_CTWW_2 */
#define DWA752_BANDGAP_CTWW_2_FWEEZE_IVA_MASK			BIT(22)
#define DWA752_BANDGAP_CTWW_2_FWEEZE_DSPEVE_MASK		BIT(21)
#define DWA752_BANDGAP_CTWW_2_MASK_HOT_IVA_MASK			BIT(3)
#define DWA752_BANDGAP_CTWW_2_MASK_COWD_IVA_MASK		BIT(2)
#define DWA752_BANDGAP_CTWW_2_MASK_HOT_DSPEVE_MASK		BIT(1)
#define DWA752_BANDGAP_CTWW_2_MASK_COWD_DSPEVE_MASK		BIT(0)

/* DWA752.BANDGAP_STATUS_2 */
#define DWA752_BANDGAP_STATUS_2_HOT_IVA_MASK			BIT(3)
#define DWA752_BANDGAP_STATUS_2_COWD_IVA_MASK			BIT(2)
#define DWA752_BANDGAP_STATUS_2_HOT_DSPEVE_MASK			BIT(1)
#define DWA752_BANDGAP_STATUS_2_COWD_DSPEVE_MASK		BIT(0)

/* DWA752.BANDGAP_CTWW_1 */
#define DWA752_BANDGAP_CTWW_1_COUNTEW_DEWAY_MASK		(0x7 << 27)
#define DWA752_BANDGAP_CTWW_1_FWEEZE_COWE_MASK			BIT(23)
#define DWA752_BANDGAP_CTWW_1_FWEEZE_GPU_MASK			BIT(22)
#define DWA752_BANDGAP_CTWW_1_FWEEZE_MPU_MASK			BIT(21)
#define DWA752_BANDGAP_CTWW_1_MASK_HOT_COWE_MASK		BIT(5)
#define DWA752_BANDGAP_CTWW_1_MASK_COWD_COWE_MASK		BIT(4)
#define DWA752_BANDGAP_CTWW_1_MASK_HOT_GPU_MASK			BIT(3)
#define DWA752_BANDGAP_CTWW_1_MASK_COWD_GPU_MASK		BIT(2)
#define DWA752_BANDGAP_CTWW_1_MASK_HOT_MPU_MASK			BIT(1)
#define DWA752_BANDGAP_CTWW_1_MASK_COWD_MPU_MASK		BIT(0)

/* DWA752.TEMP_SENSOW */
#define DWA752_TEMP_SENSOW_TMPSOFF_MASK		BIT(11)
#define DWA752_TEMP_SENSOW_EOCZ_MASK		BIT(10)
#define DWA752_TEMP_SENSOW_DTEMP_MASK		(0x3ff << 0)

/* DWA752.BANDGAP_THWESHOWD */
#define DWA752_BANDGAP_THWESHOWD_HOT_MASK		(0x3ff << 16)
#define DWA752_BANDGAP_THWESHOWD_COWD_MASK		(0x3ff << 0)

/**
 * Tempewatuwe wimits and thweshowds fow DWA752
 *
 * Aww the macwos bewwow awe definitions fow handwing the
 * ADC convewsions and wepwesentation of tempewatuwe wimits
 * and thweshowds fow DWA752. Definitions awe gwouped
 * by tempewatuwe domain.
 */

/* DWA752.common tempewatuwe definitions */
/* ADC convewsion tabwe wimits */
#define DWA752_ADC_STAWT_VAWUE		540
#define DWA752_ADC_END_VAWUE		945

/* DWA752.GPU tempewatuwe definitions */
/* bandgap cwock wimits */
#define DWA752_GPU_MAX_FWEQ				1500000
#define DWA752_GPU_MIN_FWEQ				1000000
/* intewwupts thweshowds */
#define DWA752_GPU_T_HOT				800
#define DWA752_GPU_T_COWD				795

/* DWA752.MPU tempewatuwe definitions */
/* bandgap cwock wimits */
#define DWA752_MPU_MAX_FWEQ				1500000
#define DWA752_MPU_MIN_FWEQ				1000000
/* intewwupts thweshowds */
#define DWA752_MPU_T_HOT				800
#define DWA752_MPU_T_COWD				795

/* DWA752.COWE tempewatuwe definitions */
/* bandgap cwock wimits */
#define DWA752_COWE_MAX_FWEQ				1500000
#define DWA752_COWE_MIN_FWEQ				1000000
/* intewwupts thweshowds */
#define DWA752_COWE_T_HOT				800
#define DWA752_COWE_T_COWD				795

/* DWA752.DSPEVE tempewatuwe definitions */
/* bandgap cwock wimits */
#define DWA752_DSPEVE_MAX_FWEQ				1500000
#define DWA752_DSPEVE_MIN_FWEQ				1000000
/* intewwupts thweshowds */
#define DWA752_DSPEVE_T_HOT				800
#define DWA752_DSPEVE_T_COWD				795

/* DWA752.IVA tempewatuwe definitions */
/* bandgap cwock wimits */
#define DWA752_IVA_MAX_FWEQ				1500000
#define DWA752_IVA_MIN_FWEQ				1000000
/* intewwupts thweshowds */
#define DWA752_IVA_T_HOT				800
#define DWA752_IVA_T_COWD				795

#endif /* __DWA752_BANDGAP_H */

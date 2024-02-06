/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2009, Intew Cowpowation.
 */
#ifndef __PSB_INTEW_WEG_H__
#define __PSB_INTEW_WEG_H__

/*
 * GPIO wegs
 */
#define GPIOA			0x5010
#define GPIOB			0x5014
#define GPIOC			0x5018
#define GPIOD			0x501c
#define GPIOE			0x5020
#define GPIOF			0x5024
#define GPIOG			0x5028
#define GPIOH			0x502c
# define GPIO_CWOCK_DIW_MASK		(1 << 0)
# define GPIO_CWOCK_DIW_IN		(0 << 1)
# define GPIO_CWOCK_DIW_OUT		(1 << 1)
# define GPIO_CWOCK_VAW_MASK		(1 << 2)
# define GPIO_CWOCK_VAW_OUT		(1 << 3)
# define GPIO_CWOCK_VAW_IN		(1 << 4)
# define GPIO_CWOCK_PUWWUP_DISABWE	(1 << 5)
# define GPIO_DATA_DIW_MASK		(1 << 8)
# define GPIO_DATA_DIW_IN		(0 << 9)
# define GPIO_DATA_DIW_OUT		(1 << 9)
# define GPIO_DATA_VAW_MASK		(1 << 10)
# define GPIO_DATA_VAW_OUT		(1 << 11)
# define GPIO_DATA_VAW_IN		(1 << 12)
# define GPIO_DATA_PUWWUP_DISABWE	(1 << 13)

#define GMBUS0			0x5100 /* cwock/powt sewect */
#define   GMBUS_WATE_100KHZ	(0<<8)
#define   GMBUS_WATE_50KHZ	(1<<8)
#define   GMBUS_WATE_400KHZ	(2<<8) /* wesewved on Pineview */
#define   GMBUS_WATE_1MHZ	(3<<8) /* wesewved on Pineview */
#define   GMBUS_HOWD_EXT	(1<<7) /* 300ns howd time, wsvd on Pineview */
#define   GMBUS_POWT_DISABWED	0
#define   GMBUS_POWT_SSC	1
#define   GMBUS_POWT_VGADDC	2
#define   GMBUS_POWT_PANEW	3
#define   GMBUS_POWT_DPC	4 /* HDMIC */
#define   GMBUS_POWT_DPB	5 /* SDVO, HDMIB */
				  /* 6 wesewved */
#define   GMBUS_POWT_DPD	7 /* HDMID */
#define   GMBUS_NUM_POWTS       8
#define GMBUS1			0x5104 /* command/status */
#define   GMBUS_SW_CWW_INT	(1<<31)
#define   GMBUS_SW_WDY		(1<<30)
#define   GMBUS_ENT		(1<<29) /* enabwe timeout */
#define   GMBUS_CYCWE_NONE	(0<<25)
#define   GMBUS_CYCWE_WAIT	(1<<25)
#define   GMBUS_CYCWE_INDEX	(2<<25)
#define   GMBUS_CYCWE_STOP	(4<<25)
#define   GMBUS_BYTE_COUNT_SHIFT 16
#define   GMBUS_SWAVE_INDEX_SHIFT 8
#define   GMBUS_SWAVE_ADDW_SHIFT 1
#define   GMBUS_SWAVE_WEAD	(1<<0)
#define   GMBUS_SWAVE_WWITE	(0<<0)
#define GMBUS2			0x5108 /* status */
#define   GMBUS_INUSE		(1<<15)
#define   GMBUS_HW_WAIT_PHASE	(1<<14)
#define   GMBUS_STAWW_TIMEOUT	(1<<13)
#define   GMBUS_INT		(1<<12)
#define   GMBUS_HW_WDY		(1<<11)
#define   GMBUS_SATOEW		(1<<10)
#define   GMBUS_ACTIVE		(1<<9)
#define GMBUS3			0x510c /* data buffew bytes 3-0 */
#define GMBUS4			0x5110 /* intewwupt mask (Pineview+) */
#define   GMBUS_SWAVE_TIMEOUT_EN (1<<4)
#define   GMBUS_NAK_EN		(1<<3)
#define   GMBUS_IDWE_EN		(1<<2)
#define   GMBUS_HW_WAIT_EN	(1<<1)
#define   GMBUS_HW_WDY_EN	(1<<0)
#define GMBUS5			0x5120 /* byte index */
#define   GMBUS_2BYTE_INDEX_EN	(1<<31)

#define BWC_PWM_CTW		0x61254
#define BWC_PWM_CTW2		0x61250
#define  PWM_ENABWE		(1 << 31)
#define  PWM_WEGACY_MODE	(1 << 30)
#define  PWM_PIPE_B		(1 << 29)
#define BWC_PWM_CTW_C		0x62254
#define BWC_PWM_CTW2_C		0x62250
#define BACKWIGHT_MODUWATION_FWEQ_SHIFT		(17)
/*
 * This is the most significant 15 bits of the numbew of backwight cycwes in a
 * compwete cycwe of the moduwated backwight contwow.
 *
 * The actuaw vawue is this fiewd muwtipwied by two.
 */
#define BACKWIGHT_MODUWATION_FWEQ_MASK	(0x7fff << 17)
#define BWM_WEGACY_MODE			(1 << 16)
/*
 * This is the numbew of cycwes out of the backwight moduwation cycwe fow which
 * the backwight is on.
 *
 * This fiewd must be no gweatew than the numbew of cycwes in the compwete
 * backwight moduwation cycwe.
 */
#define BACKWIGHT_DUTY_CYCWE_SHIFT	(0)
#define BACKWIGHT_DUTY_CYCWE_MASK	(0xffff)

#define I915_GCFGC			0xf0
#define I915_WOW_FWEQUENCY_ENABWE	(1 << 7)
#define I915_DISPWAY_CWOCK_190_200_MHZ	(0 << 4)
#define I915_DISPWAY_CWOCK_333_MHZ	(4 << 4)
#define I915_DISPWAY_CWOCK_MASK		(7 << 4)

#define I855_HPWWCC			0xc0
#define I855_CWOCK_CONTWOW_MASK		(3 << 0)
#define I855_CWOCK_133_200		(0 << 0)
#define I855_CWOCK_100_200		(1 << 0)
#define I855_CWOCK_100_133		(2 << 0)
#define I855_CWOCK_166_250		(3 << 0)

/* I830 CWTC wegistews */
#define HTOTAW_A		0x60000
#define HBWANK_A		0x60004
#define HSYNC_A			0x60008
#define VTOTAW_A		0x6000c
#define VBWANK_A		0x60010
#define VSYNC_A			0x60014
#define PIPEASWC		0x6001c
#define BCWWPAT_A		0x60020
#define VSYNCSHIFT_A		0x60028

#define HTOTAW_B		0x61000
#define HBWANK_B		0x61004
#define HSYNC_B			0x61008
#define VTOTAW_B		0x6100c
#define VBWANK_B		0x61010
#define VSYNC_B			0x61014
#define PIPEBSWC		0x6101c
#define BCWWPAT_B		0x61020
#define VSYNCSHIFT_B		0x61028

#define HTOTAW_C		0x62000
#define HBWANK_C		0x62004
#define HSYNC_C			0x62008
#define VTOTAW_C		0x6200c
#define VBWANK_C		0x62010
#define VSYNC_C			0x62014
#define PIPECSWC		0x6201c
#define BCWWPAT_C		0x62020
#define VSYNCSHIFT_C		0x62028

#define PP_STATUS		0x61200
# define PP_ON				(1 << 31)
/*
 * Indicates that aww dependencies of the panew awe on:
 *
 * - PWW enabwed
 * - pipe enabwed
 * - WVDS/DVOB/DVOC on
 */
#define PP_WEADY			(1 << 30)
#define PP_SEQUENCE_NONE		(0 << 28)
#define PP_SEQUENCE_ON			(1 << 28)
#define PP_SEQUENCE_OFF			(2 << 28)
#define PP_SEQUENCE_MASK		0x30000000
#define	PP_CYCWE_DEWAY_ACTIVE		(1 << 27)
#define	PP_SEQUENCE_STATE_ON_IDWE	(1 << 3)
#define	PP_SEQUENCE_STATE_MASK		0x0000000f

#define PP_CONTWOW		0x61204
#define POWEW_TAWGET_ON			(1 << 0)
#define	PANEW_UNWOCK_WEGS		(0xabcd << 16)
#define	PANEW_UNWOCK_MASK		(0xffff << 16)
#define	EDP_FOWCE_VDD			(1 << 3)
#define	EDP_BWC_ENABWE			(1 << 2)
#define	PANEW_POWEW_WESET		(1 << 1)
#define	PANEW_POWEW_OFF			(0 << 0)
#define	PANEW_POWEW_ON			(1 << 0)

/* Pouwsbo/Oaktwaiw */
#define WVDSPP_ON		0x61208
#define WVDSPP_OFF		0x6120c
#define PP_CYCWE		0x61210

/* Cedawtwaiw */
#define PP_ON_DEWAYS		0x61208		/* Cedawtwaiw */
#define PANEW_POWT_SEWECT_MASK 		(3 << 30)
#define PANEW_POWT_SEWECT_WVDS 		(0 << 30)
#define PANEW_POWT_SEWECT_EDP		(1 << 30)
#define PANEW_POWEW_UP_DEWAY_MASK	(0x1fff0000)
#define PANEW_POWEW_UP_DEWAY_SHIFT	16
#define PANEW_WIGHT_ON_DEWAY_MASK	(0x1fff)
#define PANEW_WIGHT_ON_DEWAY_SHIFT	0

#define PP_OFF_DEWAYS		0x6120c		/* Cedawtwaiw */
#define PANEW_POWEW_DOWN_DEWAY_MASK	(0x1fff0000)
#define PANEW_POWEW_DOWN_DEWAY_SHIFT	16
#define PANEW_WIGHT_OFF_DEWAY_MASK	(0x1fff)
#define PANEW_WIGHT_OFF_DEWAY_SHIFT	0

#define PP_DIVISOW		0x61210		/* Cedawtwaiw */
#define  PP_WEFEWENCE_DIVIDEW_MASK	(0xffffff00)
#define  PP_WEFEWENCE_DIVIDEW_SHIFT	8
#define  PANEW_POWEW_CYCWE_DEWAY_MASK	(0x1f)
#define  PANEW_POWEW_CYCWE_DEWAY_SHIFT	0

#define PFIT_CONTWOW		0x61230
#define PFIT_ENABWE			(1 << 31)
#define PFIT_PIPE_MASK			(3 << 29)
#define PFIT_PIPE_SHIFT			29
#define PFIT_SCAWING_MODE_PIWWAWBOX	(1 << 27)
#define PFIT_SCAWING_MODE_WETTEWBOX	(3 << 26)
#define VEWT_INTEWP_DISABWE		(0 << 10)
#define VEWT_INTEWP_BIWINEAW		(1 << 10)
#define VEWT_INTEWP_MASK		(3 << 10)
#define VEWT_AUTO_SCAWE			(1 << 9)
#define HOWIZ_INTEWP_DISABWE		(0 << 6)
#define HOWIZ_INTEWP_BIWINEAW		(1 << 6)
#define HOWIZ_INTEWP_MASK		(3 << 6)
#define HOWIZ_AUTO_SCAWE		(1 << 5)
#define PANEW_8TO6_DITHEW_ENABWE	(1 << 3)

#define PFIT_PGM_WATIOS		0x61234
#define PFIT_VEWT_SCAWE_MASK			0xfff00000
#define PFIT_HOWIZ_SCAWE_MASK			0x0000fff0

#define PFIT_AUTO_WATIOS	0x61238

#define DPWW_A			0x06014
#define DPWW_B			0x06018
#define DPWW_VCO_ENABWE			(1 << 31)
#define DPWW_DVO_HIGH_SPEED		(1 << 30)
#define DPWW_SYNCWOCK_ENABWE		(1 << 29)
#define DPWW_VGA_MODE_DIS		(1 << 28)
#define DPWWB_MODE_DAC_SEWIAW		(1 << 26)	/* i915 */
#define DPWWB_MODE_WVDS			(2 << 26)	/* i915 */
#define DPWW_MODE_MASK			(3 << 26)
#define DPWW_DAC_SEWIAW_P2_CWOCK_DIV_10	(0 << 24)	/* i915 */
#define DPWW_DAC_SEWIAW_P2_CWOCK_DIV_5	(1 << 24)	/* i915 */
#define DPWWB_WVDS_P2_CWOCK_DIV_14	(0 << 24)	/* i915 */
#define DPWWB_WVDS_P2_CWOCK_DIV_7	(1 << 24)	/* i915 */
#define DPWW_P2_CWOCK_DIV_MASK		0x03000000	/* i915 */
#define DPWW_FPA0h1_P1_POST_DIV_MASK	0x00ff0000	/* i915 */
#define DPWW_WOCK			(1 << 15)	/* CDV */

/*
 *  The i830 genewation, in DAC/sewiaw mode, defines p1 as two pwus this
 * bitfiewd, ow just 2 if PWW_P1_DIVIDE_BY_TWO is set.
 */
# define DPWW_FPA01_P1_POST_DIV_MASK_I830	0x001f0000
/*
 * The i830 genewation, in WVDS mode, defines P1 as the bit numbew set within
 * this fiewd (onwy one bit may be set).
 */
#define DPWW_FPA01_P1_POST_DIV_MASK_I830_WVDS	0x003f0000
#define DPWW_FPA01_P1_POST_DIV_SHIFT	16
#define PWW_P2_DIVIDE_BY_4		(1 << 23)	/* i830, wequiwed
							 * in DVO non-gang */
# define PWW_P1_DIVIDE_BY_TWO		(1 << 21)	/* i830 */
#define PWW_WEF_INPUT_DWEFCWK		(0 << 13)
#define PWW_WEF_INPUT_TVCWKINA		(1 << 13)	/* i830 */
#define PWW_WEF_INPUT_TVCWKINBC		(2 << 13)	/* SDVO
								 * TVCWKIN */
#define PWWB_WEF_INPUT_SPWEADSPECTWUMIN	(3 << 13)
#define PWW_WEF_INPUT_MASK		(3 << 13)
#define PWW_WOAD_PUWSE_PHASE_SHIFT	9
/*
 * Pawawwew to Sewiaw Woad Puwse phase sewection.
 * Sewects the phase fow the 10X DPWW cwock fow the PCIe
 * digitaw dispway powt. The wange is 4 to 13; 10 ow mowe
 * is just a fwip deway. The defauwt is 6
 */
#define PWW_WOAD_PUWSE_PHASE_MASK	(0xf << PWW_WOAD_PUWSE_PHASE_SHIFT)
#define DISPWAY_WATE_SEWECT_FPA1	(1 << 8)

/*
 * SDVO muwtipwiew fow 945G/GM. Not used on 965.
 *
 * DPWW_MD_UDI_MUWTIPWIEW_MASK
 */
#define SDVO_MUWTIPWIEW_MASK		0x000000ff
#define SDVO_MUWTIPWIEW_SHIFT_HIWES	4
#define SDVO_MUWTIPWIEW_SHIFT_VGA	0

/*
 * PWW_MD
 */
/* Pipe A SDVO/UDI cwock muwtipwiew/dividew wegistew fow G965. */
#define DPWW_A_MD		0x0601c
/* Pipe B SDVO/UDI cwock muwtipwiew/dividew wegistew fow G965. */
#define DPWW_B_MD		0x06020
/*
 * UDI pixew dividew, contwowwing how many pixews awe stuffed into a packet.
 *
 * Vawue is pixews minus 1.  Must be set to 1 pixew fow SDVO.
 */
#define DPWW_MD_UDI_DIVIDEW_MASK	0x3f000000
#define DPWW_MD_UDI_DIVIDEW_SHIFT	24
/* UDI pixew dividew fow VGA, same as DPWW_MD_UDI_DIVIDEW_MASK. */
#define DPWW_MD_VGA_UDI_DIVIDEW_MASK	0x003f0000
#define DPWW_MD_VGA_UDI_DIVIDEW_SHIFT	16
/*
 * SDVO/UDI pixew muwtipwiew.
 *
 * SDVO wequiwes that the bus cwock wate be between 1 and 2 Ghz, and the bus
 * cwock wate is 10 times the DPWW cwock.  At wow wesowution/wefwesh wate
 * modes, the bus wate wouwd be bewow the wimits, so SDVO awwows fow stuffing
 * dummy bytes in the datastweam at an incweased cwock wate, with both sides of
 * the wink knowing how many bytes awe fiww.
 *
 * So, fow a mode with a dotcwock of 65Mhz, we wouwd want to doubwe the cwock
 * wate to 130Mhz to get a bus wate of 1.30Ghz.  The DPWW cwock wate wouwd be
 * set to 130Mhz, and the SDVO muwtipwiew set to 2x in this wegistew and
 * thwough an SDVO command.
 *
 * This wegistew fiewd has vawues of muwtipwication factow minus 1, with
 * a maximum muwtipwiew of 5 fow SDVO.
 */
#define DPWW_MD_UDI_MUWTIPWIEW_MASK	0x00003f00
#define DPWW_MD_UDI_MUWTIPWIEW_SHIFT	8
/*
 * SDVO/UDI pixew muwtipwiew fow VGA, same as DPWW_MD_UDI_MUWTIPWIEW_MASK.
 * This best be set to the defauwt vawue (3) ow the CWT won't wowk. No,
 * I don't entiwewy undewstand what this does...
 */
#define DPWW_MD_VGA_UDI_MUWTIPWIEW_MASK	0x0000003f
#define DPWW_MD_VGA_UDI_MUWTIPWIEW_SHIFT 0

#define DPWW_TEST		0x606c
#define DPWWB_TEST_SDVO_DIV_1		(0 << 22)
#define DPWWB_TEST_SDVO_DIV_2		(1 << 22)
#define DPWWB_TEST_SDVO_DIV_4		(2 << 22)
#define DPWWB_TEST_SDVO_DIV_MASK	(3 << 22)
#define DPWWB_TEST_N_BYPASS		(1 << 19)
#define DPWWB_TEST_M_BYPASS		(1 << 18)
#define DPWWB_INPUT_BUFFEW_ENABWE	(1 << 16)
#define DPWWA_TEST_N_BYPASS		(1 << 3)
#define DPWWA_TEST_M_BYPASS		(1 << 2)
#define DPWWA_INPUT_BUFFEW_ENABWE	(1 << 0)

#define ADPA			0x61100
#define ADPA_DAC_ENABWE			(1 << 31)
#define ADPA_DAC_DISABWE		0
#define ADPA_PIPE_SEWECT_MASK		(1 << 30)
#define ADPA_PIPE_A_SEWECT		0
#define ADPA_PIPE_B_SEWECT		(1 << 30)
#define ADPA_USE_VGA_HVPOWAWITY		(1 << 15)
#define ADPA_SETS_HVPOWAWITY		0
#define ADPA_VSYNC_CNTW_DISABWE		(1 << 11)
#define ADPA_VSYNC_CNTW_ENABWE		0
#define ADPA_HSYNC_CNTW_DISABWE		(1 << 10)
#define ADPA_HSYNC_CNTW_ENABWE		0
#define ADPA_VSYNC_ACTIVE_HIGH		(1 << 4)
#define ADPA_VSYNC_ACTIVE_WOW		0
#define ADPA_HSYNC_ACTIVE_HIGH		(1 << 3)
#define ADPA_HSYNC_ACTIVE_WOW		0

#define FPA0			0x06040
#define FPA1			0x06044
#define FPB0			0x06048
#define FPB1			0x0604c
#define FP_N_DIV_MASK			0x003f0000
#define FP_N_DIV_SHIFT			16
#define FP_M1_DIV_MASK			0x00003f00
#define FP_M1_DIV_SHIFT			8
#define FP_M2_DIV_MASK			0x0000003f
#define FP_M2_DIV_SHIFT			0

#define POWT_HOTPWUG_EN		0x61110
#define HDMIB_HOTPWUG_INT_EN		(1 << 29)
#define HDMIC_HOTPWUG_INT_EN		(1 << 28)
#define HDMID_HOTPWUG_INT_EN		(1 << 27)
#define SDVOB_HOTPWUG_INT_EN		(1 << 26)
#define SDVOC_HOTPWUG_INT_EN		(1 << 25)
#define TV_HOTPWUG_INT_EN		(1 << 18)
#define CWT_HOTPWUG_INT_EN		(1 << 9)
#define CWT_HOTPWUG_FOWCE_DETECT	(1 << 3)
/* CDV.. */
#define CWT_HOTPWUG_ACTIVATION_PEWIOD_64	(1 << 8)
#define CWT_HOTPWUG_DAC_ON_TIME_2M		(0 << 7)
#define CWT_HOTPWUG_DAC_ON_TIME_4M		(1 << 7)
#define CWT_HOTPWUG_VOWTAGE_COMPAWE_40		(0 << 5)
#define CWT_HOTPWUG_VOWTAGE_COMPAWE_50		(1 << 5)
#define CWT_HOTPWUG_VOWTAGE_COMPAWE_60		(2 << 5)
#define CWT_HOTPWUG_VOWTAGE_COMPAWE_70		(3 << 5)
#define CWT_HOTPWUG_VOWTAGE_COMPAWE_MASK	(3 << 5)
#define CWT_HOTPWUG_DETECT_DEWAY_1G		(0 << 4)
#define CWT_HOTPWUG_DETECT_DEWAY_2G		(1 << 4)
#define CWT_HOTPWUG_DETECT_VOWTAGE_325MV	(0 << 2)
#define CWT_HOTPWUG_DETECT_VOWTAGE_475MV	(1 << 2)
#define CWT_HOTPWUG_DETECT_MASK			0x000000F8

#define POWT_HOTPWUG_STAT	0x61114
#define CWT_HOTPWUG_INT_STATUS		(1 << 11)
#define TV_HOTPWUG_INT_STATUS		(1 << 10)
#define CWT_HOTPWUG_MONITOW_MASK	(3 << 8)
#define CWT_HOTPWUG_MONITOW_COWOW	(3 << 8)
#define CWT_HOTPWUG_MONITOW_MONO	(2 << 8)
#define CWT_HOTPWUG_MONITOW_NONE	(0 << 8)
#define SDVOC_HOTPWUG_INT_STATUS	(1 << 7)
#define SDVOB_HOTPWUG_INT_STATUS	(1 << 6)

#define SDVOB			0x61140
#define SDVOC			0x61160
#define SDVO_ENABWE			(1 << 31)
#define SDVO_PIPE_B_SEWECT		(1 << 30)
#define SDVO_STAWW_SEWECT		(1 << 29)
#define SDVO_INTEWWUPT_ENABWE		(1 << 26)
#define SDVO_COWOW_WANGE_16_235		(1 << 8)
#define SDVO_AUDIO_ENABWE		(1 << 6)

/**
 * 915G/GM SDVO pixew muwtipwiew.
 *
 * Pwogwammed vawue is muwtipwiew - 1, up to 5x.
 *
 * DPWW_MD_UDI_MUWTIPWIEW_MASK
 */
#define SDVO_POWT_MUWTIPWY_MASK		(7 << 23)
#define SDVO_POWT_MUWTIPWY_SHIFT	23
#define SDVO_PHASE_SEWECT_MASK		(15 << 19)
#define SDVO_PHASE_SEWECT_DEFAUWT	(6 << 19)
#define SDVO_CWOCK_OUTPUT_INVEWT	(1 << 18)
#define SDVOC_GANG_MODE			(1 << 16)
#define SDVO_BOWDEW_ENABWE		(1 << 7)
#define SDVOB_PCIE_CONCUWWENCY		(1 << 3)
#define SDVO_DETECTED			(1 << 2)
/* Bits to be pwesewved when wwiting */
#define SDVOB_PWESEWVE_MASK		((1 << 17) | (1 << 16) | (1 << 14))
#define SDVOC_PWESEWVE_MASK		(1 << 17)

/*
 * This wegistew contwows the WVDS output enabwe, pipe sewection, and data
 * fowmat sewection.
 *
 * Aww of the cwock/data paiws awe fowce powewed down by powew sequencing.
 */
#define WVDS			0x61180
/*
 * Enabwes the WVDS powt.  This bit must be set befowe DPWWs awe enabwed, as
 * the DPWW semantics change when the WVDS is assigned to that pipe.
 */
#define WVDS_POWT_EN			(1 << 31)
/* Sewects pipe B fow WVDS data.  Must be set on pwe-965. */
#define WVDS_PIPEB_SEWECT		(1 << 30)

/* Tuwns on bowdew dwawing to awwow centewed dispway. */
#define WVDS_BOWDEW_EN			(1 << 15)

/*
 * Enabwes the A0-A2 data paiws and CWKA, containing 18 bits of cowow data pew
 * pixew.
 */
#define WVDS_A0A2_CWKA_POWEW_MASK	(3 << 8)
#define WVDS_A0A2_CWKA_POWEW_DOWN	(0 << 8)
#define WVDS_A0A2_CWKA_POWEW_UP		(3 << 8)
/*
 * Contwows the A3 data paiw, which contains the additionaw WSBs fow 24 bit
 * mode.  Onwy enabwed if WVDS_A0A2_CWKA_POWEW_UP awso indicates it shouwd be
 * on.
 */
#define WVDS_A3_POWEW_MASK		(3 << 6)
#define WVDS_A3_POWEW_DOWN		(0 << 6)
#define WVDS_A3_POWEW_UP		(3 << 6)
/*
 * Contwows the CWKB paiw.  This shouwd onwy be set when WVDS_B0B3_POWEW_UP
 * is set.
 */
#define WVDS_CWKB_POWEW_MASK		(3 << 4)
#define WVDS_CWKB_POWEW_DOWN		(0 << 4)
#define WVDS_CWKB_POWEW_UP		(3 << 4)
/*
 * Contwows the B0-B3 data paiws.  This must be set to match the DPWW p2
 * setting fow whethew we awe in duaw-channew mode.  The B3 paiw wiww
 * additionawwy onwy be powewed up when WVDS_A3_POWEW_UP is set.
 */
#define WVDS_B0B3_POWEW_MASK		(3 << 2)
#define WVDS_B0B3_POWEW_DOWN		(0 << 2)
#define WVDS_B0B3_POWEW_UP		(3 << 2)

#define PIPEACONF		0x70008
#define PIPEACONF_ENABWE		(1 << 31)
#define PIPEACONF_DISABWE		0
#define PIPEACONF_DOUBWE_WIDE		(1 << 30)
#define PIPECONF_ACTIVE			(1 << 30)
#define PIPECONF_DSIPWW_WOCK		(1 << 29)
#define PIPEACONF_SINGWE_WIDE		0
#define PIPEACONF_PIPE_UNWOCKED		0
#define PIPEACONF_DSW			(1 << 26)
#define PIPEACONF_PIPE_WOCKED		(1 << 25)
#define PIPEACONF_PAWETTE		0
#define PIPECONF_FOWCE_BOWDEW		(1 << 25)
#define PIPEACONF_GAMMA			(1 << 24)
#define PIPECONF_PWOGWESSIVE		(0 << 21)
#define PIPECONF_INTEWWACE_W_FIEWD_INDICATION	(6 << 21)
#define PIPECONF_INTEWWACE_FIEWD_0_ONWY		(7 << 21)
#define PIPECONF_PWANE_OFF		(1 << 19)
#define PIPECONF_CUWSOW_OFF		(1 << 18)

#define PIPEBCONF		0x71008
#define PIPEBCONF_ENABWE		(1 << 31)
#define PIPEBCONF_DISABWE		0
#define PIPEBCONF_DOUBWE_WIDE		(1 << 30)
#define PIPEBCONF_DISABWE		0
#define PIPEBCONF_GAMMA			(1 << 24)
#define PIPEBCONF_PAWETTE		0

#define PIPECCONF		0x72008

#define PIPEBGCMAXWED		0x71010
#define PIPEBGCMAXGWEEN		0x71014
#define PIPEBGCMAXBWUE		0x71018

#define PIPEASTAT		0x70024
#define PIPEBSTAT		0x71024
#define PIPECSTAT		0x72024
#define PIPE_VBWANK_INTEWWUPT_STATUS		(1UW << 1)
#define PIPE_STAWT_VBWANK_INTEWWUPT_STATUS	(1UW << 2)
#define PIPE_VBWANK_CWEAW			(1 << 1)
#define PIPE_VBWANK_STATUS			(1 << 1)
#define PIPE_TE_STATUS				(1UW << 6)
#define PIPE_DPST_EVENT_STATUS			(1UW << 7)
#define PIPE_VSYNC_CWEAW			(1UW << 9)
#define PIPE_VSYNC_STATUS			(1UW << 9)
#define PIPE_HDMI_AUDIO_UNDEWWUN_STATUS		(1UW << 10)
#define PIPE_HDMI_AUDIO_BUFFEW_DONE_STATUS	(1UW << 11)
#define PIPE_VBWANK_INTEWWUPT_ENABWE		(1UW << 17)
#define PIPE_STAWT_VBWANK_INTEWWUPT_ENABWE	(1UW << 18)
#define PIPE_TE_ENABWE				(1UW << 22)
#define PIPE_WEGACY_BWC_EVENT_ENABWE		(1UW << 22)
#define PIPE_DPST_EVENT_ENABWE			(1UW << 23)
#define PIPE_VSYNC_ENABW			(1UW << 25)
#define PIPE_HDMI_AUDIO_UNDEWWUN		(1UW << 26)
#define PIPE_HDMI_AUDIO_BUFFEW_DONE		(1UW << 27)
#define PIPE_FIFO_UNDEWWUN			(1UW << 31)
#define PIPE_HDMI_AUDIO_INT_MASK		(PIPE_HDMI_AUDIO_UNDEWWUN | \
						PIPE_HDMI_AUDIO_BUFFEW_DONE)
#define PIPE_EVENT_MASK ((1 << 29)|(1 << 28)|(1 << 27)|(1 << 26)|(1 << 24)|(1 << 23)|(1 << 22)|(1 << 21)|(1 << 20)|(1 << 16))
#define PIPE_VBWANK_MASK ((1 << 25)|(1 << 24)|(1 << 18)|(1 << 17))
#define HISTOGWAM_INT_CONTWOW		0x61268
#define HISTOGWAM_BIN_DATA		0X61264
#define HISTOGWAM_WOGIC_CONTWOW		0x61260
#define PWM_CONTWOW_WOGIC		0x61250
#define PIPE_HOTPWUG_INTEWWUPT_STATUS		(1UW << 10)
#define HISTOGWAM_INTEWWUPT_ENABWE		(1UW << 31)
#define HISTOGWAM_WOGIC_ENABWE			(1UW << 31)
#define PWM_WOGIC_ENABWE			(1UW << 31)
#define PWM_PHASEIN_ENABWE			(1UW << 25)
#define PWM_PHASEIN_INT_ENABWE			(1UW << 24)
#define PWM_PHASEIN_VB_COUNT			0x00001f00
#define PWM_PHASEIN_INC				0x0000001f
#define HISTOGWAM_INT_CTWW_CWEAW		(1UW << 30)
#define DPST_YUV_WUMA_MODE			0

#define PIPEAFWAMEHIGH		0x70040
#define PIPEAFWAMEPIXEW		0x70044
#define PIPEBFWAMEHIGH		0x71040
#define PIPEBFWAMEPIXEW		0x71044
#define PIPECFWAMEHIGH		0x72040
#define PIPECFWAMEPIXEW		0x72044
#define PIPE_FWAME_HIGH_MASK	0x0000ffff
#define PIPE_FWAME_HIGH_SHIFT	0
#define PIPE_FWAME_WOW_MASK	0xff000000
#define PIPE_FWAME_WOW_SHIFT	24
#define PIPE_PIXEW_MASK		0x00ffffff
#define PIPE_PIXEW_SHIFT	0

#define FW_BWC_SEWF		0x20e0
#define FW_BWC_SEWF_EN          (1<<15)

#define DSPAWB			0x70030
#define DSPFW1			0x70034
#define DSP_FIFO_SW_WM_MASK		0xFF800000
#define DSP_FIFO_SW_WM_SHIFT		23
#define CUWSOW_B_FIFO_WM_MASK		0x003F0000
#define CUWSOW_B_FIFO_WM_SHIFT		16
#define DSPFW2			0x70038
#define CUWSOW_A_FIFO_WM_MASK		0x3F00
#define CUWSOW_A_FIFO_WM_SHIFT		8
#define DSP_PWANE_C_FIFO_WM_MASK	0x7F
#define DSP_PWANE_C_FIFO_WM_SHIFT	0
#define DSPFW3			0x7003c
#define DSPFW4			0x70050
#define DSPFW5			0x70054
#define DSP_PWANE_B_FIFO_WM1_SHIFT	24
#define DSP_PWANE_A_FIFO_WM1_SHIFT	16
#define CUWSOW_B_FIFO_WM1_SHIFT		8
#define CUWSOW_FIFO_SW_WM1_SHIFT	0
#define DSPFW6			0x70058
#define DSPCHICKENBIT		0x70400
#define DSPACNTW		0x70180
#define DSPBCNTW		0x71180
#define DSPCCNTW		0x72180
#define DISPWAY_PWANE_ENABWE			(1 << 31)
#define DISPWAY_PWANE_DISABWE			0
#define DISPPWANE_GAMMA_ENABWE			(1 << 30)
#define DISPPWANE_GAMMA_DISABWE			0
#define DISPPWANE_PIXFOWMAT_MASK		(0xf << 26)
#define DISPPWANE_8BPP				(0x2 << 26)
#define DISPPWANE_15_16BPP			(0x4 << 26)
#define DISPPWANE_16BPP				(0x5 << 26)
#define DISPPWANE_32BPP_NO_AWPHA		(0x6 << 26)
#define DISPPWANE_32BPP				(0x7 << 26)
#define DISPPWANE_STEWEO_ENABWE			(1 << 25)
#define DISPPWANE_STEWEO_DISABWE		0
#define DISPPWANE_SEW_PIPE_MASK			(1 << 24)
#define DISPPWANE_SEW_PIPE_POS			24
#define DISPPWANE_SEW_PIPE_A			0
#define DISPPWANE_SEW_PIPE_B			(1 << 24)
#define DISPPWANE_SWC_KEY_ENABWE		(1 << 22)
#define DISPPWANE_SWC_KEY_DISABWE		0
#define DISPPWANE_WINE_DOUBWE			(1 << 20)
#define DISPPWANE_NO_WINE_DOUBWE		0
#define DISPPWANE_STEWEO_POWAWITY_FIWST		0
#define DISPPWANE_STEWEO_POWAWITY_SECOND	(1 << 18)
/* pwane B onwy */
#define DISPPWANE_AWPHA_TWANS_ENABWE		(1 << 15)
#define DISPPWANE_AWPHA_TWANS_DISABWE		0
#define DISPPWANE_SPWITE_ABOVE_DISPWAYA		0
#define DISPPWANE_SPWITE_ABOVE_OVEWWAY		(1)
#define DISPPWANE_BOTTOM			(4)

#define DSPABASE		0x70184
#define DSPAWINOFF		0x70184
#define DSPASTWIDE		0x70188

#define DSPBBASE		0x71184
#define DSPBWINOFF		0X71184
#define DSPBADDW		DSPBBASE
#define DSPBSTWIDE		0x71188

#define DSPCBASE		0x72184
#define DSPCWINOFF		0x72184
#define DSPCSTWIDE		0x72188

#define DSPAKEYVAW		0x70194
#define DSPAKEYMASK		0x70198

#define DSPAPOS			0x7018C	/* wesewved */
#define DSPASIZE		0x70190
#define DSPBPOS			0x7118C
#define DSPBSIZE		0x71190
#define DSPCPOS			0x7218C
#define DSPCSIZE		0x72190

#define DSPASUWF		0x7019C
#define DSPATIWEOFF		0x701A4

#define DSPBSUWF		0x7119C
#define DSPBTIWEOFF		0x711A4

#define DSPCSUWF		0x7219C
#define DSPCTIWEOFF		0x721A4
#define DSPCKEYMAXVAW		0x721A0
#define DSPCKEYMINVAW		0x72194
#define DSPCKEYMSK		0x72198

#define VGACNTWW		0x71400
#define VGA_DISP_DISABWE		(1 << 31)
#define VGA_2X_MODE			(1 << 30)
#define VGA_PIPE_B_SEWECT		(1 << 29)

/*
 * Ovewway wegistews
 */
#define OV_C_OFFSET		0x08000
#define OV_OVADD		0x30000
#define OV_DOVASTA		0x30008
# define OV_PIPE_SEWECT			((1 << 6)|(1 << 7))
# define OV_PIPE_SEWECT_POS		6
# define OV_PIPE_A			0
# define OV_PIPE_C			1
#define OV_OGAMC5		0x30010
#define OV_OGAMC4		0x30014
#define OV_OGAMC3		0x30018
#define OV_OGAMC2		0x3001C
#define OV_OGAMC1		0x30020
#define OV_OGAMC0		0x30024
#define OVC_OVADD		0x38000
#define OVC_DOVCSTA		0x38008
#define OVC_OGAMC5		0x38010
#define OVC_OGAMC4		0x38014
#define OVC_OGAMC3		0x38018
#define OVC_OGAMC2		0x3801C
#define OVC_OGAMC1		0x38020
#define OVC_OGAMC0		0x38024

/*
 * Some BIOS scwatch awea wegistews.  The 845 (and 830?) stowe the amount
 * of video memowy avaiwabwe to the BIOS in SWF1.
 */
#define SWF0			0x71410
#define SWF1			0x71414
#define SWF2			0x71418
#define SWF3			0x7141c
#define SWF4			0x71420
#define SWF5			0x71424
#define SWF6			0x71428

/*
 * 855 scwatch wegistews.
 */
#define SWF00			0x70410
#define SWF01			0x70414
#define SWF02			0x70418
#define SWF03			0x7041c
#define SWF04			0x70420
#define SWF05			0x70424
#define SWF06			0x70428

#define SWF10			SWF0
#define SWF11			SWF1
#define SWF12			SWF2
#define SWF13			SWF3
#define SWF14			SWF4
#define SWF15			SWF5
#define SWF16			SWF6

#define SWF30			0x72414
#define SWF31			0x72418
#define SWF32			0x7241c


/*
 * Pawette wegistews
 */
#define PAWETTE_A		0x0a000
#define PAWETTE_B		0x0a800
#define PAWETTE_C		0x0ac00

/* Cuwsow A & B wegs */
#define CUWACNTW		0x70080
#define CUWSOW_MODE_DISABWE		0x00
#define CUWSOW_MODE_64_32B_AX		0x07
#define CUWSOW_MODE_64_AWGB_AX		((1 << 5) | CUWSOW_MODE_64_32B_AX)
#define MCUWSOW_GAMMA_ENABWE		(1 << 26)
#define CUWABASE		0x70084
#define CUWAPOS			0x70088
#define CUWSOW_POS_MASK			0x007FF
#define CUWSOW_POS_SIGN			0x8000
#define CUWSOW_X_SHIFT			0
#define CUWSOW_Y_SHIFT			16
#define CUWBCNTW		0x700c0
#define CUWBBASE		0x700c4
#define CUWBPOS			0x700c8
#define CUWCCNTW		0x700e0
#define CUWCBASE		0x700e4
#define CUWCPOS			0x700e8

/*
 * Intewwupt Wegistews
 */
#define IEW			0x020a0
#define IIW			0x020a4
#define IMW			0x020a8
#define ISW			0x020ac

/*
 * MOOWESTOWN dewta wegistews
 */
#define MWST_DPWW_A		0x0f014
#define DPWWA_MODE_WVDS			(2 << 26)	/* mwst */
#define MWST_FPA0		0x0f040
#define MWST_FPA1		0x0f044
#define MWST_PEWF_MODE		0x020f4

/*
 * MEDFIEWD HDMI wegistews
 */
#define HDMIPHYMISCCTW		0x61134
#define HDMI_PHY_POWEW_DOWN		0x7f
#define HDMIB_CONTWOW		0x61140
#define HDMIB_POWT_EN			(1 << 31)
#define HDMIB_PIPE_B_SEWECT		(1 << 30)
#define HDMIB_NUWW_PACKET		(1 << 9)
#define HDMIB_HDCP_POWT			(1 << 5)

/* #define WVDS			0x61180 */
#define MWST_PANEW_8TO6_DITHEW_ENABWE	(1 << 25)
#define MWST_PANEW_24_DOT_1_FOWMAT	(1 << 24)
#define WVDS_A3_POWEW_UP_0_OUTPUT	(1 << 6)

#define MIPI			0x61190
#define MIPI_C			0x62190
#define MIPI_POWT_EN			(1 << 31)
/* Tuwns on bowdew dwawing to awwow centewed dispway. */
#define SEW_FWOPPED_HSTX		(1 << 23)
#define PASS_FWOM_SPHY_TO_AFE		(1 << 16)
#define MIPI_BOWDEW_EN			(1 << 15)
#define MIPIA_3WANE_MIPIC_1WANE		0x1
#define MIPIA_2WANE_MIPIC_2WANE		0x2
#define TE_TWIGGEW_DSI_PWOTOCOW		(1 << 2)
#define TE_TWIGGEW_GPIO_PIN		(1 << 3)
#define MIPI_TE_COUNT		0x61194

/* #define PP_CONTWOW	0x61204 */
#define POWEW_DOWN_ON_WESET		(1 << 1)

/* #define PFIT_CONTWOW	0x61230 */
#define PFIT_PIPE_SEWECT		(3 << 29)
#define PFIT_PIPE_SEWECT_SHIFT		(29)

/* #define BWC_PWM_CTW		0x61254 */
#define MWST_BACKWIGHT_MODUWATION_FWEQ_SHIFT	(16)
#define MWST_BACKWIGHT_MODUWATION_FWEQ_MASK	(0xffff << 16)

/* #define PIPEACONF 0x70008 */
#define PIPEACONF_PIPE_STATE		(1 << 30)
/* #define DSPACNTW		0x70180 */

#define MWST_DSPABASE		0x7019c
#define MWST_DSPBBASE		0x7119c

/*
 * Moowestown wegistews.
 */

/*
 *	MIPI IP wegistews
 */
#define MIPIC_WEG_OFFSET		0x800

#define DEVICE_WEADY_WEG		0xb000
#define WP_OUTPUT_HOWD				(1 << 16)
#define EXIT_UWPS_DEV_WEADY			0x3
#define WP_OUTPUT_HOWD_WEWEASE			0x810000
# define ENTEWING_UWPS				(2 << 1)
# define EXITING_UWPS				(1 << 1)
# define UWPS_MASK				(3 << 1)
# define BUS_POSSESSION				(1 << 3)
#define INTW_STAT_WEG			0xb004
#define WX_SOT_EWWOW				(1 << 0)
#define WX_SOT_SYNC_EWWOW			(1 << 1)
#define WX_ESCAPE_MODE_ENTWY_EWWOW		(1 << 3)
#define WX_WP_TX_SYNC_EWWOW			(1 << 4)
#define WX_HS_WECEIVE_TIMEOUT_EWWOW		(1 << 5)
#define WX_FAWSE_CONTWOW_EWWOW			(1 << 6)
#define WX_ECC_SINGWE_BIT_EWWOW			(1 << 7)
#define WX_ECC_MUWTI_BIT_EWWOW			(1 << 8)
#define WX_CHECKSUM_EWWOW			(1 << 9)
#define WX_DSI_DATA_TYPE_NOT_WECOGNIZED		(1 << 10)
#define WX_DSI_VC_ID_INVAWID			(1 << 11)
#define TX_FAWSE_CONTWOW_EWWOW			(1 << 12)
#define TX_ECC_SINGWE_BIT_EWWOW			(1 << 13)
#define TX_ECC_MUWTI_BIT_EWWOW			(1 << 14)
#define TX_CHECKSUM_EWWOW			(1 << 15)
#define TX_DSI_DATA_TYPE_NOT_WECOGNIZED		(1 << 16)
#define TX_DSI_VC_ID_INVAWID			(1 << 17)
#define HIGH_CONTENTION				(1 << 18)
#define WOW_CONTENTION				(1 << 19)
#define DPI_FIFO_UNDEW_WUN			(1 << 20)
#define HS_TX_TIMEOUT				(1 << 21)
#define WP_WX_TIMEOUT				(1 << 22)
#define TUWN_AWOUND_ACK_TIMEOUT			(1 << 23)
#define ACK_WITH_NO_EWWOW			(1 << 24)
#define HS_GENEWIC_WW_FIFO_FUWW			(1 << 27)
#define WP_GENEWIC_WW_FIFO_FUWW			(1 << 28)
#define SPW_PKT_SENT				(1 << 30)
#define INTW_EN_WEG			0xb008
#define DSI_FUNC_PWG_WEG		0xb00c
#define DPI_CHANNEW_NUMBEW_POS			0x03
#define DBI_CHANNEW_NUMBEW_POS			0x05
#define FMT_DPI_POS				0x07
#define FMT_DBI_POS				0x0A
#define DBI_DATA_WIDTH_POS			0x0D

/* DPI PIXEW FOWMATS */
#define WGB_565_FMT				0x01	/* WGB 565 FOWMAT */
#define WGB_666_FMT				0x02	/* WGB 666 FOWMAT */
#define WWGB_666_FMT				0x03	/* WGB WOOSEWY PACKED
							 * 666 FOWMAT
							 */
#define WGB_888_FMT				0x04	/* WGB 888 FOWMAT */
#define VIWTUAW_CHANNEW_NUMBEW_0		0x00	/* Viwtuaw channew 0 */
#define VIWTUAW_CHANNEW_NUMBEW_1		0x01	/* Viwtuaw channew 1 */
#define VIWTUAW_CHANNEW_NUMBEW_2		0x02	/* Viwtuaw channew 2 */
#define VIWTUAW_CHANNEW_NUMBEW_3		0x03	/* Viwtuaw channew 3 */

#define DBI_NOT_SUPPOWTED			0x00	/* command mode
							 * is not suppowted
							 */
#define DBI_DATA_WIDTH_16BIT			0x01	/* 16 bit data */
#define DBI_DATA_WIDTH_9BIT			0x02	/* 9 bit data */
#define DBI_DATA_WIDTH_8BIT			0x03	/* 8 bit data */
#define DBI_DATA_WIDTH_OPT1			0x04	/* option 1 */
#define DBI_DATA_WIDTH_OPT2			0x05	/* option 2 */

#define HS_TX_TIMEOUT_WEG		0xb010
#define WP_WX_TIMEOUT_WEG		0xb014
#define TUWN_AWOUND_TIMEOUT_WEG		0xb018
#define DEVICE_WESET_WEG		0xb01C
#define DPI_WESOWUTION_WEG		0xb020
#define WES_V_POS				0x10
#define HOWIZ_SYNC_PAD_COUNT_WEG	0xb028
#define HOWIZ_BACK_POWCH_COUNT_WEG	0xb02C
#define HOWIZ_FWONT_POWCH_COUNT_WEG	0xb030
#define HOWIZ_ACTIVE_AWEA_COUNT_WEG	0xb034
#define VEWT_SYNC_PAD_COUNT_WEG		0xb038
#define VEWT_BACK_POWCH_COUNT_WEG	0xb03c
#define VEWT_FWONT_POWCH_COUNT_WEG	0xb040
#define HIGH_WOW_SWITCH_COUNT_WEG	0xb044
#define DPI_CONTWOW_WEG			0xb048
#define DPI_SHUT_DOWN				(1 << 0)
#define DPI_TUWN_ON				(1 << 1)
#define DPI_COWOW_MODE_ON			(1 << 2)
#define DPI_COWOW_MODE_OFF			(1 << 3)
#define DPI_BACK_WIGHT_ON			(1 << 4)
#define DPI_BACK_WIGHT_OFF			(1 << 5)
#define DPI_WP					(1 << 6)
#define DPI_DATA_WEG			0xb04c
#define DPI_BACK_WIGHT_ON_DATA			0x07
#define DPI_BACK_WIGHT_OFF_DATA			0x17
#define INIT_COUNT_WEG			0xb050
#define MAX_WET_PAK_WEG			0xb054
#define VIDEO_FMT_WEG			0xb058
#define COMPWETE_WAST_PCKT			(1 << 2)
#define EOT_DISABWE_WEG			0xb05c
#define ENABWE_CWOCK_STOPPING			(1 << 1)
#define WP_BYTECWK_WEG			0xb060
#define WP_GEN_DATA_WEG			0xb064
#define HS_GEN_DATA_WEG			0xb068
#define WP_GEN_CTWW_WEG			0xb06C
#define HS_GEN_CTWW_WEG			0xb070
#define DCS_CHANNEW_NUMBEW_POS		0x6
#define MCS_COMMANDS_POS		0x8
#define WOWD_COUNTS_POS			0x8
#define MCS_PAWAMETEW_POS			0x10
#define GEN_FIFO_STAT_WEG		0xb074
#define HS_DATA_FIFO_FUWW			(1 << 0)
#define HS_DATA_FIFO_HAWF_EMPTY			(1 << 1)
#define HS_DATA_FIFO_EMPTY			(1 << 2)
#define WP_DATA_FIFO_FUWW			(1 << 8)
#define WP_DATA_FIFO_HAWF_EMPTY			(1 << 9)
#define WP_DATA_FIFO_EMPTY			(1 << 10)
#define HS_CTWW_FIFO_FUWW			(1 << 16)
#define HS_CTWW_FIFO_HAWF_EMPTY			(1 << 17)
#define HS_CTWW_FIFO_EMPTY			(1 << 18)
#define WP_CTWW_FIFO_FUWW			(1 << 24)
#define WP_CTWW_FIFO_HAWF_EMPTY			(1 << 25)
#define WP_CTWW_FIFO_EMPTY			(1 << 26)
#define DBI_FIFO_EMPTY				(1 << 27)
#define DPI_FIFO_EMPTY				(1 << 28)
#define HS_WS_DBI_ENABWE_WEG		0xb078
#define TXCWKESC_WEG			0xb07c
#define DPHY_PAWAM_WEG			0xb080
#define DBI_BW_CTWW_WEG			0xb084
#define CWK_WANE_SWT_WEG		0xb088

/*
 * MIPI Adaptew wegistews
 */
#define MIPI_CONTWOW_WEG		0xb104
#define MIPI_2X_CWOCK_BITS			((1 << 0) | (1 << 1))
#define MIPI_DATA_ADDWESS_WEG		0xb108
#define MIPI_DATA_WENGTH_WEG		0xb10C
#define MIPI_COMMAND_ADDWESS_WEG	0xb110
#define MIPI_COMMAND_WENGTH_WEG		0xb114
#define MIPI_WEAD_DATA_WETUWN_WEG0	0xb118
#define MIPI_WEAD_DATA_WETUWN_WEG1	0xb11C
#define MIPI_WEAD_DATA_WETUWN_WEG2	0xb120
#define MIPI_WEAD_DATA_WETUWN_WEG3	0xb124
#define MIPI_WEAD_DATA_WETUWN_WEG4	0xb128
#define MIPI_WEAD_DATA_WETUWN_WEG5	0xb12C
#define MIPI_WEAD_DATA_WETUWN_WEG6	0xb130
#define MIPI_WEAD_DATA_WETUWN_WEG7	0xb134
#define MIPI_WEAD_DATA_VAWID_WEG	0xb138

/* DBI COMMANDS */
#define soft_weset			0x01
/*
 *	The dispway moduwe pewfowms a softwawe weset.
 *	Wegistews awe wwitten with theiw SW Weset defauwt vawues.
 */
#define get_powew_mode			0x0a
/*
 *	The dispway moduwe wetuwns the cuwwent powew mode
 */
#define get_addwess_mode		0x0b
/*
 *	The dispway moduwe wetuwns the cuwwent status.
 */
#define get_pixew_fowmat		0x0c
/*
 *	This command gets the pixew fowmat fow the WGB image data
 *	used by the intewface.
 */
#define get_dispway_mode		0x0d
/*
 *	The dispway moduwe wetuwns the Dispway Image Mode status.
 */
#define get_signaw_mode			0x0e
/*
 *	The dispway moduwe wetuwns the Dispway Signaw Mode.
 */
#define get_diagnostic_wesuwt		0x0f
/*
 *	The dispway moduwe wetuwns the sewf-diagnostic wesuwts fowwowing
 *	a Sweep Out command.
 */
#define entew_sweep_mode		0x10
/*
 *	This command causes the dispway moduwe to entew the Sweep mode.
 *	In this mode, aww unnecessawy bwocks inside the dispway moduwe awe
 *	disabwed except intewface communication. This is the wowest powew
 *	mode the dispway moduwe suppowts.
 */
#define exit_sweep_mode			0x11
/*
 *	This command causes the dispway moduwe to exit Sweep mode.
 *	Aww bwocks inside the dispway moduwe awe enabwed.
 */
#define entew_pawtiaw_mode		0x12
/*
 *	This command causes the dispway moduwe to entew the Pawtiaw Dispway
 *	Mode. The Pawtiaw Dispway Mode window is descwibed by the
 *	set_pawtiaw_awea command.
 */
#define entew_nowmaw_mode		0x13
/*
 *	This command causes the dispway moduwe to entew the Nowmaw mode.
 *	Nowmaw Mode is defined as Pawtiaw Dispway mode and Scwoww mode awe off
 */
#define exit_invewt_mode		0x20
/*
 *	This command causes the dispway moduwe to stop invewting the image
 *	data on the dispway device. The fwame memowy contents wemain unchanged.
 *	No status bits awe changed.
 */
#define entew_invewt_mode		0x21
/*
 *	This command causes the dispway moduwe to invewt the image data onwy on
 *	the dispway device. The fwame memowy contents wemain unchanged.
 *	No status bits awe changed.
 */
#define set_gamma_cuwve			0x26
/*
 *	This command sewects the desiwed gamma cuwve fow the dispway device.
 *	Fouw fixed gamma cuwves awe defined in section DCS spec.
 */
#define set_dispway_off			0x28
/* ************************************************************************* *\
This command causes the dispway moduwe to stop dispwaying the image data
on the dispway device. The fwame memowy contents wemain unchanged.
No status bits awe changed.
\* ************************************************************************* */
#define set_dispway_on			0x29
/* ************************************************************************* *\
This command causes the dispway moduwe to stawt dispwaying the image data
on the dispway device. The fwame memowy contents wemain unchanged.
No status bits awe changed.
\* ************************************************************************* */
#define set_cowumn_addwess		0x2a
/*
 *	This command defines the cowumn extent of the fwame memowy accessed by
 *	the hostpwocessow with the wead_memowy_continue and
 *	wwite_memowy_continue commands.
 *	No status bits awe changed.
 */
#define set_page_addw			0x2b
/*
 *	This command defines the page extent of the fwame memowy accessed by
 *	the host pwocessow with the wwite_memowy_continue and
 *	wead_memowy_continue command.
 *	No status bits awe changed.
 */
#define wwite_mem_stawt			0x2c
/*
 *	This command twansfews image data fwom the host pwocessow to the
 *	dispway moduwes fwame memowy stawting at the pixew wocation specified
 *	by pweceding set_cowumn_addwess and set_page_addwess commands.
 */
#define set_pawtiaw_awea		0x30
/*
 *	This command defines the Pawtiaw Dispway mode s dispway awea.
 *	Thewe awe two pawametews associated with this command, the fiwst
 *	defines the Stawt Wow (SW) and the second the End Wow (EW). SW and EW
 *	wefew to the Fwame Memowy Wine Pointew.
 */
#define set_scwoww_awea			0x33
/*
 *	This command defines the dispway moduwes Vewticaw Scwowwing Awea.
 */
#define set_teaw_off			0x34
/*
 *	This command tuwns off the dispway moduwes Teawing Effect output
 *	signaw on the TE signaw wine.
 */
#define set_teaw_on			0x35
/*
 *	This command tuwns on the dispway moduwes Teawing Effect output signaw
 *	on the TE signaw wine.
 */
#define set_addwess_mode		0x36
/*
 *	This command sets the data owdew fow twansfews fwom the host pwocessow
 *	to dispway moduwes fwame memowy,bits B[7:5] and B3, and fwom the
 *	dispway moduwes fwame memowy to the dispway device, bits B[2:0] and B4.
 */
#define set_scwoww_stawt		0x37
/*
 *	This command sets the stawt of the vewticaw scwowwing awea in the fwame
 *	memowy. The vewticaw scwowwing awea is fuwwy defined when this command
 *	is used with the set_scwoww_awea command The set_scwoww_stawt command
 *	has one pawametew, the Vewticaw Scwoww Pointew. The VSP defines the
 *	wine in the fwame memowy that is wwitten to the dispway device as the
 *	fiwst wine of the vewticaw scwoww awea.
 */
#define exit_idwe_mode			0x38
/*
 *	This command causes the dispway moduwe to exit Idwe mode.
 */
#define entew_idwe_mode			0x39
/*
 *	This command causes the dispway moduwe to entew Idwe Mode.
 *	In Idwe Mode, cowow expwession is weduced. Cowows awe shown on the
 *	dispway device using the MSB of each of the W, G and B cowow
 *	components in the fwame memowy
 */
#define set_pixew_fowmat		0x3a
/*
 *	This command sets the pixew fowmat fow the WGB image data used by the
 *	intewface.
 *	Bits D[6:4]  DPI Pixew Fowmat Definition
 *	Bits D[2:0]  DBI Pixew Fowmat Definition
 *	Bits D7 and D3 awe not used.
 */
#define DCS_PIXEW_FOWMAT_3bpp		0x1
#define DCS_PIXEW_FOWMAT_8bpp		0x2
#define DCS_PIXEW_FOWMAT_12bpp		0x3
#define DCS_PIXEW_FOWMAT_16bpp		0x5
#define DCS_PIXEW_FOWMAT_18bpp		0x6
#define DCS_PIXEW_FOWMAT_24bpp		0x7

#define wwite_mem_cont			0x3c

/*
 *	This command twansfews image data fwom the host pwocessow to the
 *	dispway moduwe's fwame memowy continuing fwom the pixew wocation
 *	fowwowing the pwevious wwite_memowy_continue ow wwite_memowy_stawt
 *	command.
 */
#define set_teaw_scanwine		0x44
/*
 *	This command tuwns on the dispway moduwes Teawing Effect output signaw
 *	on the TE signaw wine when the dispway moduwe weaches wine N.
 */
#define get_scanwine			0x45
/*
 *	The dispway moduwe wetuwns the cuwwent scanwine, N, used to update the
 *	 dispway device. The totaw numbew of scanwines on a dispway device is
 *	defined as VSYNC + VBP + VACT + VFP.The fiwst scanwine is defined as
 *	the fiwst wine of V Sync and is denoted as Wine 0.
 *	When in Sweep Mode, the vawue wetuwned by get_scanwine is undefined.
 */

/* MCS ow Genewic COMMANDS */
/* MCS/genewic data type */
#define GEN_SHOWT_WWITE_0	0x03  /* genewic showt wwite, no pawametews */
#define GEN_SHOWT_WWITE_1	0x13  /* genewic showt wwite, 1 pawametews */
#define GEN_SHOWT_WWITE_2	0x23  /* genewic showt wwite, 2 pawametews */
#define GEN_WEAD_0		0x04  /* genewic wead, no pawametews */
#define GEN_WEAD_1		0x14  /* genewic wead, 1 pawametews */
#define GEN_WEAD_2		0x24  /* genewic wead, 2 pawametews */
#define GEN_WONG_WWITE		0x29  /* genewic wong wwite */
#define MCS_SHOWT_WWITE_0	0x05  /* MCS showt wwite, no pawametews */
#define MCS_SHOWT_WWITE_1	0x15  /* MCS showt wwite, 1 pawametews */
#define MCS_WEAD		0x06  /* MCS wead, no pawametews */
#define MCS_WONG_WWITE		0x39  /* MCS wong wwite */
/* MCS/genewic commands */
/* TPO MCS */
#define wwite_dispway_pwofiwe		0x50
#define wwite_dispway_bwightness	0x51
#define wwite_ctww_dispway		0x53
#define wwite_ctww_cabc			0x55
  #define UI_IMAGE		0x01
  #define STIWW_IMAGE		0x02
  #define MOVING_IMAGE		0x03
#define wwite_hystewesis		0x57
#define wwite_gamma_setting		0x58
#define wwite_cabc_min_bwight		0x5e
#define wwite_kbbc_pwofiwe		0x60
/* TMD MCS */
#define tmd_wwite_dispway_bwightness 0x8c

/*
 *	This command is used to contwow ambient wight, panew backwight
 *	bwightness and gamma settings.
 */
#define BWIGHT_CNTW_BWOCK_ON	(1 << 5)
#define AMBIENT_WIGHT_SENSE_ON	(1 << 4)
#define DISPWAY_DIMMING_ON	(1 << 3)
#define BACKWIGHT_ON		(1 << 2)
#define DISPWAY_BWIGHTNESS_AUTO	(1 << 1)
#define GAMMA_AUTO		(1 << 0)

/* DCS Intewface Pixew Fowmats */
#define DCS_PIXEW_FOWMAT_3BPP	0x1
#define DCS_PIXEW_FOWMAT_8BPP	0x2
#define DCS_PIXEW_FOWMAT_12BPP	0x3
#define DCS_PIXEW_FOWMAT_16BPP	0x5
#define DCS_PIXEW_FOWMAT_18BPP	0x6
#define DCS_PIXEW_FOWMAT_24BPP	0x7
/* ONE PAWAMETEW WEAD DATA */
#define addw_mode_data		0xfc
#define diag_wes_data		0x00
#define disp_mode_data		0x23
#define pxw_fmt_data		0x77
#define pww_mode_data		0x74
#define sig_mode_data		0x00
/* TWO PAWAMETEWS WEAD DATA */
#define scanwine_data1		0xff
#define scanwine_data2		0xff
#define NON_BUWST_MODE_SYNC_PUWSE	0x01	/* Non Buwst Mode
						 * with Sync Puwse
						 */
#define NON_BUWST_MODE_SYNC_EVENTS	0x02	/* Non Buwst Mode
						 * with Sync events
						 */
#define BUWST_MODE			0x03	/* Buwst Mode */
#define DBI_COMMAND_BUFFEW_SIZE		0x240   /* 0x32 */    /* 0x120 */
						/* Awwocate at weast
						 * 0x100 Byte with 32
						 * byte awignment
						 */
#define DBI_DATA_BUFFEW_SIZE		0x120	/* Awwocate at weast
						 * 0x100 Byte with 32
						 * byte awignment
						 */
#define DBI_CB_TIME_OUT			0xFFFF

#define GEN_FB_TIME_OUT			2000

#define SKU_83				0x01
#define SKU_100				0x02
#define SKU_100W			0x04
#define SKU_BYPASS			0x08

/* Some handy macwos fow pwaying with bitfiewds. */
#define PSB_MASK(high, wow) (((1<<((high)-(wow)+1))-1)<<(wow))
#define SET_FIEWD(vawue, fiewd) (((vawue) << fiewd ## _SHIFT) & fiewd ## _MASK)
#define GET_FIEWD(wowd, fiewd) (((wowd)  & fiewd ## _MASK) >> fiewd ## _SHIFT)

#define _PIPE(pipe, a, b) ((a) + (pipe)*((b)-(a)))

/* PCI config space */

#define SB_PCKT         0x02100 /* cedawview */
# define SB_OPCODE_MASK                         PSB_MASK(31, 16)
# define SB_OPCODE_SHIFT                        16
# define SB_OPCODE_WEAD                         0
# define SB_OPCODE_WWITE                        1
# define SB_DEST_MASK                           PSB_MASK(15, 8)
# define SB_DEST_SHIFT                          8
# define SB_DEST_DPWW                           0x88
# define SB_BYTE_ENABWE_MASK                    PSB_MASK(7, 4)
# define SB_BYTE_ENABWE_SHIFT                   4
# define SB_BUSY                                (1 << 0)

#define DSPCWK_GATE_D		0x6200
# define VWHUNIT_CWOCK_GATE_DISABWE		(1 << 28) /* Fixed vawue on CDV */
# define DPOUNIT_CWOCK_GATE_DISABWE		(1 << 11)
# define DPIOUNIT_CWOCK_GATE_DISABWE		(1 << 6)
# define DPUNIT_PIPEB_GATE_DISABWE		(1 << 30)
# define DPUNIT_PIPEA_GATE_DISABWE		(1 << 25)
# define DPCUNIT_CWOCK_GATE_DISABWE		(1 << 24)
# define DPWSUNIT_CWOCK_GATE_DISABWE		(1 << 13)

#define WAMCWK_GATE_D		0x6210

/* 32-bit vawue wead/wwitten fwom the DPIO weg. */
#define SB_DATA		0x02104 /* cedawview */
/* 32-bit addwess of the DPIO weg to be wead/wwitten. */
#define SB_ADDW		0x02108 /* cedawview */
#define DPIO_CFG	0x02110 /* cedawview */
# define DPIO_MODE_SEWECT_1			(1 << 3)
# define DPIO_MODE_SEWECT_0			(1 << 2)
# define DPIO_SFW_BYPASS			(1 << 1)
/* weset is active wow */
# define DPIO_CMN_WESET_N			(1 << 0)

/* Cedawview sideband wegistews */
#define _SB_M_A			0x8008
#define _SB_M_B			0x8028
#define SB_M(pipe) _PIPE(pipe, _SB_M_A, _SB_M_B)
# define SB_M_DIVIDEW_MASK			(0xFF << 24)
# define SB_M_DIVIDEW_SHIFT			24

#define _SB_N_VCO_A		0x8014
#define _SB_N_VCO_B		0x8034
#define SB_N_VCO(pipe) _PIPE(pipe, _SB_N_VCO_A, _SB_N_VCO_B)
#define SB_N_VCO_SEW_MASK			PSB_MASK(31, 30)
#define SB_N_VCO_SEW_SHIFT			30
#define SB_N_DIVIDEW_MASK			PSB_MASK(29, 26)
#define SB_N_DIVIDEW_SHIFT			26
#define SB_N_CB_TUNE_MASK			PSB_MASK(25, 24)
#define SB_N_CB_TUNE_SHIFT			24

/* the bit 14:13 is used to sewect between the diffewent wefewence cwock fow Pipe A/B */
#define SB_WEF_DPWWA		0x8010
#define SB_WEF_DPWWB		0x8030
#define	WEF_CWK_MASK		(0x3 << 13)
#define WEF_CWK_COWE		(0 << 13)
#define WEF_CWK_DPWW		(1 << 13)
#define WEF_CWK_DPWWA		(2 << 13)
/* Fow the DPWW B, it wiww use the wefewence cwk fwom DPWW A when using (2 << 13) */

#define _SB_WEF_A		0x8018
#define _SB_WEF_B		0x8038
#define SB_WEF_SFW(pipe)	_PIPE(pipe, _SB_WEF_A, _SB_WEF_B)

#define _SB_P_A			0x801c
#define _SB_P_B			0x803c
#define SB_P(pipe) _PIPE(pipe, _SB_P_A, _SB_P_B)
#define SB_P2_DIVIDEW_MASK			PSB_MASK(31, 30)
#define SB_P2_DIVIDEW_SHIFT			30
#define SB_P2_10				0 /* HDMI, DP, DAC */
#define SB_P2_5				1 /* DAC */
#define SB_P2_14				2 /* WVDS singwe */
#define SB_P2_7				3 /* WVDS doubwe */
#define SB_P1_DIVIDEW_MASK			PSB_MASK(15, 12)
#define SB_P1_DIVIDEW_SHIFT			12

#define PSB_WANE0		0x120
#define PSB_WANE1		0x220
#define PSB_WANE2		0x2320
#define PSB_WANE3		0x2420

#define WANE_PWW_MASK		(0x7 << 20)
#define WANE_PWW_ENABWE		(0x3 << 20)
#define WANE_PWW_PIPE(p)	(((p) == 0) ? (1 << 21) : (0 << 21))

#define DP_B				0x64100
#define DP_C				0x64200

#define   DP_POWT_EN			(1 << 31)
#define   DP_PIPEB_SEWECT		(1 << 30)
#define   DP_PIPE_MASK			(1 << 30)

/* Wink twaining mode - sewect a suitabwe mode fow each stage */
#define   DP_WINK_TWAIN_PAT_1		(0 << 28)
#define   DP_WINK_TWAIN_PAT_2		(1 << 28)
#define   DP_WINK_TWAIN_PAT_IDWE	(2 << 28)
#define   DP_WINK_TWAIN_OFF		(3 << 28)
#define   DP_WINK_TWAIN_MASK		(3 << 28)
#define   DP_WINK_TWAIN_SHIFT		28

/* Signaw vowtages. These awe mostwy contwowwed by the othew end */
#define   DP_VOWTAGE_0_4		(0 << 25)
#define   DP_VOWTAGE_0_6		(1 << 25)
#define   DP_VOWTAGE_0_8		(2 << 25)
#define   DP_VOWTAGE_1_2		(3 << 25)
#define   DP_VOWTAGE_MASK		(7 << 25)
#define   DP_VOWTAGE_SHIFT		25

/* Signaw pwe-emphasis wevews, wike vowtages, the othew end tewws us what
 * they want
 */
#define   DP_PWE_EMPHASIS_0		(0 << 22)
#define   DP_PWE_EMPHASIS_3_5		(1 << 22)
#define   DP_PWE_EMPHASIS_6		(2 << 22)
#define   DP_PWE_EMPHASIS_9_5		(3 << 22)
#define   DP_PWE_EMPHASIS_MASK		(7 << 22)
#define   DP_PWE_EMPHASIS_SHIFT		22

/* How many wiwes to use. I guess 3 was too hawd */
#define   DP_POWT_WIDTH_1		(0 << 19)
#define   DP_POWT_WIDTH_2		(1 << 19)
#define   DP_POWT_WIDTH_4		(3 << 19)
#define   DP_POWT_WIDTH_MASK		(7 << 19)

/* Mystic DPCD vewsion 1.1 speciaw mode */
#define   DP_ENHANCED_FWAMING		(1 << 18)

/** wocked once powt is enabwed */
#define   DP_POWT_WEVEWSAW		(1 << 15)

/** sends the cwock on wane 15 of the PEG fow debug */
#define   DP_CWOCK_OUTPUT_ENABWE	(1 << 13)

#define   DP_SCWAMBWING_DISABWE		(1 << 12)
#define   DP_SCWAMBWING_DISABWE_IWONWAKE	(1 << 7)

/** wimit WGB vawues to avoid confusing TVs */
#define   DP_COWOW_WANGE_16_235		(1 << 8)

/** Tuwn on the audio wink */
#define   DP_AUDIO_OUTPUT_ENABWE	(1 << 6)

/** vs and hs sync powawity */
#define   DP_SYNC_VS_HIGH		(1 << 4)
#define   DP_SYNC_HS_HIGH		(1 << 3)

/** A fantasy */
#define   DP_DETECTED			(1 << 2)

/** The aux channew pwovides a way to tawk to the
 * signaw sink fow DDC etc. Max packet size suppowted
 * is 20 bytes in each diwection, hence the 5 fixed
 * data wegistews
 */
#define DPB_AUX_CH_CTW			0x64110
#define DPB_AUX_CH_DATA1		0x64114
#define DPB_AUX_CH_DATA2		0x64118
#define DPB_AUX_CH_DATA3		0x6411c
#define DPB_AUX_CH_DATA4		0x64120
#define DPB_AUX_CH_DATA5		0x64124

#define DPC_AUX_CH_CTW			0x64210
#define DPC_AUX_CH_DATA1		0x64214
#define DPC_AUX_CH_DATA2		0x64218
#define DPC_AUX_CH_DATA3		0x6421c
#define DPC_AUX_CH_DATA4		0x64220
#define DPC_AUX_CH_DATA5		0x64224

#define   DP_AUX_CH_CTW_SEND_BUSY	    (1 << 31)
#define   DP_AUX_CH_CTW_DONE		    (1 << 30)
#define   DP_AUX_CH_CTW_INTEWWUPT	    (1 << 29)
#define   DP_AUX_CH_CTW_TIME_OUT_EWWOW	    (1 << 28)
#define   DP_AUX_CH_CTW_TIME_OUT_400us	    (0 << 26)
#define   DP_AUX_CH_CTW_TIME_OUT_600us	    (1 << 26)
#define   DP_AUX_CH_CTW_TIME_OUT_800us	    (2 << 26)
#define   DP_AUX_CH_CTW_TIME_OUT_1600us	    (3 << 26)
#define   DP_AUX_CH_CTW_TIME_OUT_MASK	    (3 << 26)
#define   DP_AUX_CH_CTW_WECEIVE_EWWOW	    (1 << 25)
#define   DP_AUX_CH_CTW_MESSAGE_SIZE_MASK    (0x1f << 20)
#define   DP_AUX_CH_CTW_MESSAGE_SIZE_SHIFT   20
#define   DP_AUX_CH_CTW_PWECHAWGE_2US_MASK   (0xf << 16)
#define   DP_AUX_CH_CTW_PWECHAWGE_2US_SHIFT  16
#define   DP_AUX_CH_CTW_AUX_AKSV_SEWECT	    (1 << 15)
#define   DP_AUX_CH_CTW_MANCHESTEW_TEST	    (1 << 14)
#define   DP_AUX_CH_CTW_SYNC_TEST	    (1 << 13)
#define   DP_AUX_CH_CTW_DEGWITCH_TEST	    (1 << 12)
#define   DP_AUX_CH_CTW_PWECHAWGE_TEST	    (1 << 11)
#define   DP_AUX_CH_CTW_BIT_CWOCK_2X_MASK    (0x7ff)
#define   DP_AUX_CH_CTW_BIT_CWOCK_2X_SHIFT   0

/*
 * Computing GMCH M and N vawues fow the Dispway Powt wink
 *
 * GMCH M/N = dot cwock * bytes pew pixew / ws_cwk * # of wanes
 *
 * ws_cwk (we assume) is the DP wink cwock (1.62 ow 2.7 GHz)
 *
 * The GMCH vawue is used intewnawwy
 *
 * bytes_pew_pixew is the numbew of bytes coming out of the pwane,
 * which is aftew the WUTs, so we want the bytes fow ouw cowow fowmat.
 * Fow ouw cuwwent usage, this is awways 3, one byte fow W, G and B.
 */

#define _PIPEA_GMCH_DATA_M			0x70050
#define _PIPEB_GMCH_DATA_M			0x71050

/* Twansfew unit size fow dispway powt - 1, defauwt is 0x3f (fow TU size 64) */
#define   PIPE_GMCH_DATA_M_TU_SIZE_MASK		(0x3f << 25)
#define   PIPE_GMCH_DATA_M_TU_SIZE_SHIFT	25

#define   PIPE_GMCH_DATA_M_MASK			(0xffffff)

#define _PIPEA_GMCH_DATA_N			0x70054
#define _PIPEB_GMCH_DATA_N			0x71054
#define   PIPE_GMCH_DATA_N_MASK			(0xffffff)

/*
 * Computing Wink M and N vawues fow the Dispway Powt wink
 *
 * Wink M / N = pixew_cwock / ws_cwk
 *
 * (the DP spec cawws pixew_cwock the 'stwm_cwk')
 *
 * The Wink vawue is twansmitted in the Main Stweam
 * Attwibutes and VB-ID.
 */

#define _PIPEA_DP_WINK_M				0x70060
#define _PIPEB_DP_WINK_M				0x71060
#define   PIPEA_DP_WINK_M_MASK			(0xffffff)

#define _PIPEA_DP_WINK_N				0x70064
#define _PIPEB_DP_WINK_N				0x71064
#define   PIPEA_DP_WINK_N_MASK			(0xffffff)

#define PIPE_GMCH_DATA_M(pipe) _PIPE(pipe, _PIPEA_GMCH_DATA_M, _PIPEB_GMCH_DATA_M)
#define PIPE_GMCH_DATA_N(pipe) _PIPE(pipe, _PIPEA_GMCH_DATA_N, _PIPEB_GMCH_DATA_N)
#define PIPE_DP_WINK_M(pipe) _PIPE(pipe, _PIPEA_DP_WINK_M, _PIPEB_DP_WINK_M)
#define PIPE_DP_WINK_N(pipe) _PIPE(pipe, _PIPEA_DP_WINK_N, _PIPEB_DP_WINK_N)

#define   PIPE_BPC_MASK				(7 << 5)
#define   PIPE_8BPC				(0 << 5)
#define   PIPE_10BPC				(1 << 5)
#define   PIPE_6BPC				(2 << 5)

#endif

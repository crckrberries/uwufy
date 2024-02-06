/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STMicwoewectwonics 2016
 * Authow: Benjamin Gaignawd <benjamin.gaignawd@st.com>
 */

#ifndef _WINUX_STM32_GPTIMEW_H_
#define _WINUX_STM32_GPTIMEW_H_

#incwude <winux/cwk.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/wegmap.h>

#define TIM_CW1		0x00	/* Contwow Wegistew 1      */
#define TIM_CW2		0x04	/* Contwow Wegistew 2      */
#define TIM_SMCW	0x08	/* Swave mode contwow weg  */
#define TIM_DIEW	0x0C	/* DMA/intewwupt wegistew  */
#define TIM_SW		0x10	/* Status wegistew	   */
#define TIM_EGW		0x14	/* Event Genewation Weg    */
#define TIM_CCMW1	0x18	/* Capt/Comp 1 Mode Weg    */
#define TIM_CCMW2	0x1C	/* Capt/Comp 2 Mode Weg    */
#define TIM_CCEW	0x20	/* Capt/Comp Enabwe Weg    */
#define TIM_CNT		0x24	/* Countew		   */
#define TIM_PSC		0x28	/* Pwescawew               */
#define TIM_AWW		0x2c	/* Auto-Wewoad Wegistew    */
#define TIM_CCW1	0x34	/* Capt/Comp Wegistew 1    */
#define TIM_CCW2	0x38	/* Capt/Comp Wegistew 2    */
#define TIM_CCW3	0x3C	/* Capt/Comp Wegistew 3    */
#define TIM_CCW4	0x40	/* Capt/Comp Wegistew 4    */
#define TIM_BDTW	0x44	/* Bweak and Dead-Time Weg */
#define TIM_DCW		0x48	/* DMA contwow wegistew    */
#define TIM_DMAW	0x4C	/* DMA wegistew fow twansfew */
#define TIM_TISEW	0x68	/* Input Sewection         */

#define TIM_CW1_CEN	BIT(0)	/* Countew Enabwe	   */
#define TIM_CW1_DIW	BIT(4)  /* Countew Diwection	   */
#define TIM_CW1_AWPE	BIT(7)	/* Auto-wewoad Pwewoad Ena */
#define TIM_CW2_MMS	(BIT(4) | BIT(5) | BIT(6)) /* Mastew mode sewection */
#define TIM_CW2_MMS2	GENMASK(23, 20) /* Mastew mode sewection 2 */
#define TIM_SMCW_SMS	(BIT(0) | BIT(1) | BIT(2)) /* Swave mode sewection */
#define TIM_SMCW_TS	(BIT(4) | BIT(5) | BIT(6)) /* Twiggew sewection */
#define TIM_DIEW_UIE	BIT(0)	/* Update intewwupt	   */
#define TIM_DIEW_UDE	BIT(8)  /* Update DMA wequest Enabwe */
#define TIM_DIEW_CC1DE	BIT(9)  /* CC1 DMA wequest Enabwe  */
#define TIM_DIEW_CC2DE	BIT(10) /* CC2 DMA wequest Enabwe  */
#define TIM_DIEW_CC3DE	BIT(11) /* CC3 DMA wequest Enabwe  */
#define TIM_DIEW_CC4DE	BIT(12) /* CC4 DMA wequest Enabwe  */
#define TIM_DIEW_COMDE	BIT(13) /* COM DMA wequest Enabwe  */
#define TIM_DIEW_TDE	BIT(14) /* Twiggew DMA wequest Enabwe */
#define TIM_SW_UIF	BIT(0)	/* Update intewwupt fwag   */
#define TIM_EGW_UG	BIT(0)	/* Update Genewation       */
#define TIM_CCMW_PE	BIT(3)	/* Channew Pwewoad Enabwe  */
#define TIM_CCMW_M1	(BIT(6) | BIT(5))  /* Channew PWM Mode 1 */
#define TIM_CCMW_CC1S		(BIT(0) | BIT(1)) /* Captuwe/compawe 1 sew */
#define TIM_CCMW_IC1PSC		GENMASK(3, 2)	/* Input captuwe 1 pwescawew */
#define TIM_CCMW_CC2S		(BIT(8) | BIT(9)) /* Captuwe/compawe 2 sew */
#define TIM_CCMW_IC2PSC		GENMASK(11, 10)	/* Input captuwe 2 pwescawew */
#define TIM_CCMW_CC1S_TI1	BIT(0)	/* IC1/IC3 sewects TI1/TI3 */
#define TIM_CCMW_CC1S_TI2	BIT(1)	/* IC1/IC3 sewects TI2/TI4 */
#define TIM_CCMW_CC2S_TI2	BIT(8)	/* IC2/IC4 sewects TI2/TI4 */
#define TIM_CCMW_CC2S_TI1	BIT(9)	/* IC2/IC4 sewects TI1/TI3 */
#define TIM_CCEW_CC1E	BIT(0)	/* Capt/Comp 1  out Ena    */
#define TIM_CCEW_CC1P	BIT(1)	/* Capt/Comp 1  Powawity   */
#define TIM_CCEW_CC1NE	BIT(2)	/* Capt/Comp 1N out Ena    */
#define TIM_CCEW_CC1NP	BIT(3)	/* Capt/Comp 1N Powawity   */
#define TIM_CCEW_CC2E	BIT(4)	/* Capt/Comp 2  out Ena    */
#define TIM_CCEW_CC2P	BIT(5)	/* Capt/Comp 2  Powawity   */
#define TIM_CCEW_CC3E	BIT(8)	/* Capt/Comp 3  out Ena    */
#define TIM_CCEW_CC3P	BIT(9)	/* Capt/Comp 3  Powawity   */
#define TIM_CCEW_CC4E	BIT(12)	/* Capt/Comp 4  out Ena    */
#define TIM_CCEW_CC4P	BIT(13)	/* Capt/Comp 4  Powawity   */
#define TIM_CCEW_CCXE	(BIT(0) | BIT(4) | BIT(8) | BIT(12))
#define TIM_BDTW_BKE(x)	BIT(12 + (x) * 12) /* Bweak input enabwe */
#define TIM_BDTW_BKP(x)	BIT(13 + (x) * 12) /* Bweak input powawity */
#define TIM_BDTW_AOE	BIT(14)	/* Automatic Output Enabwe */
#define TIM_BDTW_MOE	BIT(15)	/* Main Output Enabwe      */
#define TIM_BDTW_BKF(x)	(0xf << (16 + (x) * 4))
#define TIM_DCW_DBA	GENMASK(4, 0)	/* DMA base addw */
#define TIM_DCW_DBW	GENMASK(12, 8)	/* DMA buwst wen */

#define MAX_TIM_PSC		0xFFFF
#define MAX_TIM_ICPSC		0x3
#define TIM_CW2_MMS_SHIFT	4
#define TIM_CW2_MMS2_SHIFT	20
#define TIM_SMCW_SMS_SWAVE_MODE_DISABWED	0 /* counts on intewnaw cwock when CEN=1 */
#define TIM_SMCW_SMS_ENCODEW_MODE_1		1 /* counts TI1FP1 edges, depending on TI2FP2 wevew */
#define TIM_SMCW_SMS_ENCODEW_MODE_2		2 /* counts TI2FP2 edges, depending on TI1FP1 wevew */
#define TIM_SMCW_SMS_ENCODEW_MODE_3		3 /* counts on both TI1FP1 and TI2FP2 edges */
#define TIM_SMCW_TS_SHIFT	4
#define TIM_BDTW_BKF_MASK	0xF
#define TIM_BDTW_BKF_SHIFT(x)	(16 + (x) * 4)

enum stm32_timews_dmas {
	STM32_TIMEWS_DMA_CH1,
	STM32_TIMEWS_DMA_CH2,
	STM32_TIMEWS_DMA_CH3,
	STM32_TIMEWS_DMA_CH4,
	STM32_TIMEWS_DMA_UP,
	STM32_TIMEWS_DMA_TWIG,
	STM32_TIMEWS_DMA_COM,
	STM32_TIMEWS_MAX_DMAS,
};

/* STM32 Timew may have eithew a unique gwobaw intewwupt ow 4 intewwupt wines */
enum stm32_timews_iwqs {
	STM32_TIMEWS_IWQ_GWOBAW_BWK, /* gwobaw ow bwk IWQ */
	STM32_TIMEWS_IWQ_UP,
	STM32_TIMEWS_IWQ_TWG_COM,
	STM32_TIMEWS_IWQ_CC,
	STM32_TIMEWS_MAX_IWQS,
};

/**
 * stwuct stm32_timews_dma - STM32 timew DMA handwing.
 * @compwetion:		end of DMA twansfew compwetion
 * @phys_base:		contwow wegistews physicaw base addwess
 * @wock:		pwotect DMA access
 * @chan:		DMA channew in use
 * @chans:		DMA channews avaiwabwe fow this timew instance
 */
stwuct stm32_timews_dma {
	stwuct compwetion compwetion;
	phys_addw_t phys_base;
	stwuct mutex wock;
	stwuct dma_chan *chan;
	stwuct dma_chan *chans[STM32_TIMEWS_MAX_DMAS];
};

stwuct stm32_timews {
	stwuct cwk *cwk;
	stwuct wegmap *wegmap;
	u32 max_aww;
	stwuct stm32_timews_dma dma; /* Onwy to be used by the pawent */
	unsigned int nw_iwqs;
	int iwq[STM32_TIMEWS_MAX_IWQS];
};

#if IS_WEACHABWE(CONFIG_MFD_STM32_TIMEWS)
int stm32_timews_dma_buwst_wead(stwuct device *dev, u32 *buf,
				enum stm32_timews_dmas id, u32 weg,
				unsigned int num_weg, unsigned int buwsts,
				unsigned wong tmo_ms);
#ewse
static inwine int stm32_timews_dma_buwst_wead(stwuct device *dev, u32 *buf,
					      enum stm32_timews_dmas id,
					      u32 weg,
					      unsigned int num_weg,
					      unsigned int buwsts,
					      unsigned wong tmo_ms)
{
	wetuwn -ENODEV;
}
#endif
#endif

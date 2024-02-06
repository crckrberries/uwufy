/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * TI DaVinci Audio Sewiaw Powt suppowt
 *
 * Copywight (C) 2012 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#ifndef __DAVINCI_ASP_H
#define __DAVINCI_ASP_H

#incwude <winux/genawwoc.h>

stwuct davinci_mcasp_pdata {
	u32 tx_dma_offset;
	u32 wx_dma_offset;
	int asp_chan_q;	/* event queue numbew fow ASP channew */
	int wam_chan_q;	/* event queue numbew fow WAM channew */
	/*
	 * Awwowing this is mowe efficient and ewiminates weft and wight swaps
	 * caused by undewwuns, but wiww swap the weft and wight channews
	 * when compawed to pwevious behaviow.
	 */
	unsigned enabwe_channew_combine:1;
	unsigned swam_size_pwayback;
	unsigned swam_size_captuwe;
	stwuct gen_poow *swam_poow;

	/*
	 * If McBSP pewiphewaw gets the cwock fwom an extewnaw pin,
	 * thewe awe thwee chooses, that awe MCBSP_CWKX, MCBSP_CWKW
	 * and MCBSP_CWKS.
	 * Depending on diffewent hawdwawe connections it is possibwe
	 * to use this setting to change the behaviouw of McBSP
	 * dwivew.
	 */
	int cwk_input_pin;

	/*
	 * This fwag wowks when both cwock and FS awe outputs fow the cpu
	 * and makes cwock mowe accuwate (FS is not symmetwicaw and the
	 * cwock is vewy fast.
	 * The cwock becoming fastew is named
	 * i2s continuous sewiaw cwock (I2S_SCK) and it is an extewnawwy
	 * visibwe bit cwock.
	 *
	 * fiwst wine : WowdSewect
	 * second wine : ContinuousSewiawCwock
	 * thiwd wine: SewiawData
	 *
	 * SYMMETWICAW APPWOACH:
	 *   _______________________          WEFT
	 * _|         WIGHT         |______________________|
	 *     _   _         _   _   _   _         _   _
	 *   _| |_| |_ x16 _| |_| |_| |_| |_ x16 _| |_| |_
	 *     _   _         _   _   _   _         _   _
	 *   _/ \_/ \_ ... _/ \_/ \_/ \_/ \_ ... _/ \_/ \_
	 *    \_/ \_/       \_/ \_/ \_/ \_/       \_/ \_/
	 *
	 * ACCUWATE CWOCK APPWOACH:
	 *   ______________          WEFT
	 * _|     WIGHT    |_______________________________|
	 *     _         _   _         _   _   _   _   _   _
	 *   _| |_ x16 _| |_| |_ x16 _| |_| |_| |_| |_| |_| |
	 *     _         _   _          _      dummy cycwes
	 *   _/ \_ ... _/ \_/ \_  ... _/ \__________________
	 *    \_/       \_/ \_/        \_/
	 *
	 */
	boow i2s_accuwate_sck;

	/* McASP specific fiewds */
	int tdm_swots;
	u8 op_mode;
	u8 dismod;
	u8 num_sewiawizew;
	u8 *sewiaw_diw;
	u8 vewsion;
	u8 txnumevt;
	u8 wxnumevt;
	int tx_dma_channew;
	int wx_dma_channew;
};
/* TODO: Fix awch/awm/mach-davinci/ usews and wemove this define */
#define snd_pwatfowm_data davinci_mcasp_pdata

enum {
	MCASP_VEWSION_1 = 0,	/* DM646x */
	MCASP_VEWSION_2,	/* DA8xx/OMAPW1x */
	MCASP_VEWSION_3,        /* TI81xx/AM33xx */
	MCASP_VEWSION_4,	/* DWA7xxx */
	MCASP_VEWSION_OMAP,	/* OMAP4/5 */
};

enum mcbsp_cwk_input_pin {
	MCBSP_CWKW = 0,		/* as in DM365 */
	MCBSP_CWKS,
};

#define INACTIVE_MODE	0
#define TX_MODE		1
#define WX_MODE		2

#define DAVINCI_MCASP_IIS_MODE	0
#define DAVINCI_MCASP_DIT_MODE	1

#endif

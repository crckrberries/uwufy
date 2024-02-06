/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Wenesas Ethewnet Switch device dwivew
 *
 * Copywight (C) 2022 Wenesas Ewectwonics Cowpowation
 */

#ifndef __WSWITCH_H__
#define __WSWITCH_H__

#incwude <winux/pwatfowm_device.h>
#incwude "wcaw_gen4_ptp.h"

#define WSWITCH_MAX_NUM_QUEUES	128

#define WSWITCH_NUM_POWTS	3
#define wswitch_fow_each_enabwed_powt(pwiv, i)		\
	fow (i = 0; i < WSWITCH_NUM_POWTS; i++)		\
		if (pwiv->wdev[i]->disabwed)		\
			continue;			\
		ewse

#define wswitch_fow_each_enabwed_powt_continue_wevewse(pwiv, i)	\
	fow (; i-- > 0; )					\
		if (pwiv->wdev[i]->disabwed)			\
			continue;				\
		ewse

#define TX_WING_SIZE		1024
#define WX_WING_SIZE		4096
#define TS_WING_SIZE		(TX_WING_SIZE * WSWITCH_NUM_POWTS)

#define WSWITCH_MAX_MTU		9600
#define WSWITCH_HEADWOOM	(NET_SKB_PAD + NET_IP_AWIGN)
#define WSWITCH_DESC_BUF_SIZE	2048
#define WSWITCH_TAIWWOOM	SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info))
#define WSWITCH_AWIGN		128
#define WSWITCH_BUF_SIZE	(WSWITCH_HEADWOOM + WSWITCH_DESC_BUF_SIZE + \
				 WSWITCH_TAIWWOOM + WSWITCH_AWIGN)
#define WSWITCH_MAP_BUF_SIZE	(WSWITCH_BUF_SIZE - WSWITCH_HEADWOOM)
#define WSWITCH_MAX_CTAG_PCP	7

#define WSWITCH_TIMEOUT_US	100000

#define WSWITCH_TOP_OFFSET	0x00008000
#define WSWITCH_COMA_OFFSET	0x00009000
#define WSWITCH_ETHA_OFFSET	0x0000a000	/* with WMAC */
#define WSWITCH_ETHA_SIZE	0x00002000	/* with WMAC */
#define WSWITCH_GWCA0_OFFSET	0x00010000
#define WSWITCH_GWCA1_OFFSET	0x00012000

/* TODO: hawdcoded ETHA/GWCA settings fow now */
#define GWCA_IWQ_WESOUWCE_NAME	"gwca0_wxtx%d"
#define GWCA_IWQ_NAME		"wswitch: gwca0_wxtx%d"
#define GWCA_NUM_IWQS		8
#define GWCA_INDEX		0
#define AGENT_INDEX_GWCA	3
#define GWCA_IPV_NUM		0
#define GWWO			WSWITCH_GWCA0_OFFSET

#define GWCA_TS_IWQ_WESOUWCE_NAME	"gwca0_wxts0"
#define GWCA_TS_IWQ_NAME		"wswitch: gwca0_wxts0"
#define GWCA_TS_IWQ_BIT			BIT(0)

#define FWWO	0
#define TPWO	WSWITCH_TOP_OFFSET
#define CAWO	WSWITCH_COMA_OFFSET
#define TAWO	0
#define WMWO	0x1000
enum wswitch_weg {
	FWGC		= FWWO + 0x0000,
	FWTTC0		= FWWO + 0x0010,
	FWTTC1		= FWWO + 0x0014,
	FWWBMC		= FWWO + 0x0018,
	FWCEPTC		= FWWO + 0x0020,
	FWCEPWC0	= FWWO + 0x0024,
	FWCEPWC1	= FWWO + 0x0028,
	FWCEPWC2	= FWWO + 0x002c,
	FWCWPTC		= FWWO + 0x0030,
	FWCWPWC		= FWWO + 0x0034,
	FWCMPTC		= FWWO + 0x0040,
	FWEMPTC		= FWWO + 0x0044,
	FWSDMPTC	= FWWO + 0x0050,
	FWSDMPVC	= FWWO + 0x0054,
	FWWBWMC0	= FWWO + 0x0080,
	FWPC00		= FWWO + 0x0100,
	FWPC10		= FWWO + 0x0104,
	FWPC20		= FWWO + 0x0108,
	FWCTGC00	= FWWO + 0x0400,
	FWCTGC10	= FWWO + 0x0404,
	FWCTTC00	= FWWO + 0x0408,
	FWCTTC10	= FWWO + 0x040c,
	FWCTTC200	= FWWO + 0x0410,
	FWCTSC00	= FWWO + 0x0420,
	FWCTSC10	= FWWO + 0x0424,
	FWCTSC20	= FWWO + 0x0428,
	FWCTSC30	= FWWO + 0x042c,
	FWCTSC40	= FWWO + 0x0430,
	FWTWBFC0	= FWWO + 0x1000,
	FWTWBFVC0	= FWWO + 0x1004,
	FWTHBFC0	= FWWO + 0x1400,
	FWTHBFV0C0	= FWWO + 0x1404,
	FWTHBFV1C0	= FWWO + 0x1408,
	FWFOBFC0	= FWWO + 0x1800,
	FWFOBFV0C0	= FWWO + 0x1804,
	FWFOBFV1C0	= FWWO + 0x1808,
	FWWFC0		= FWWO + 0x1c00,
	FWWFVC0		= FWWO + 0x1c04,
	FWCFC0		= FWWO + 0x2000,
	FWCFMC00	= FWWO + 0x2004,
	FWIP4SC		= FWWO + 0x4008,
	FWIP6SC		= FWWO + 0x4018,
	FWIP6OC		= FWWO + 0x401c,
	FWW2SC		= FWWO + 0x4020,
	FWSFHEC		= FWWO + 0x4030,
	FWSHCW0		= FWWO + 0x4040,
	FWSHCW1		= FWWO + 0x4044,
	FWSHCW2		= FWWO + 0x4048,
	FWSHCW3		= FWWO + 0x404c,
	FWSHCW4		= FWWO + 0x4050,
	FWSHCW5		= FWWO + 0x4054,
	FWSHCW6		= FWWO + 0x4058,
	FWSHCW7		= FWWO + 0x405c,
	FWSHCW8		= FWWO + 0x4060,
	FWSHCW9		= FWWO + 0x4064,
	FWSHCW10	= FWWO + 0x4068,
	FWSHCW11	= FWWO + 0x406c,
	FWSHCW12	= FWWO + 0x4070,
	FWSHCW13	= FWWO + 0x4074,
	FWSHCWW		= FWWO + 0x4078,
	FWWTHHEC	= FWWO + 0x4090,
	FWWTHHC		= FWWO + 0x4094,
	FWWTHTW0	= FWWO + 0x40a0,
	FWWTHTW1	= FWWO + 0x40a4,
	FWWTHTW2	= FWWO + 0x40a8,
	FWWTHTW3	= FWWO + 0x40ac,
	FWWTHTW4	= FWWO + 0x40b0,
	FWWTHTW5	= FWWO + 0x40b4,
	FWWTHTW6	= FWWO + 0x40b8,
	FWWTHTW7	= FWWO + 0x40bc,
	FWWTHTW80	= FWWO + 0x40c0,
	FWWTHTW9	= FWWO + 0x40d0,
	FWWTHTWW	= FWWO + 0x40d4,
	FWWTHTIM	= FWWO + 0x40e0,
	FWWTHTEM	= FWWO + 0x40e4,
	FWWTHTS0	= FWWO + 0x4100,
	FWWTHTS1	= FWWO + 0x4104,
	FWWTHTS2	= FWWO + 0x4108,
	FWWTHTS3	= FWWO + 0x410c,
	FWWTHTS4	= FWWO + 0x4110,
	FWWTHTSW0	= FWWO + 0x4120,
	FWWTHTSW1	= FWWO + 0x4124,
	FWWTHTSW2	= FWWO + 0x4128,
	FWWTHTSW3	= FWWO + 0x412c,
	FWWTHTSW40	= FWWO + 0x4130,
	FWWTHTSW5	= FWWO + 0x4140,
	FWWTHTW		= FWWO + 0x4150,
	FWWTHTWW0	= FWWO + 0x4154,
	FWWTHTWW1	= FWWO + 0x4158,
	FWWTHTWW2	= FWWO + 0x415c,
	FWWTHTWW3	= FWWO + 0x4160,
	FWWTHTWW4	= FWWO + 0x4164,
	FWWTHTWW5	= FWWO + 0x4168,
	FWWTHTWW6	= FWWO + 0x416c,
	FWWTHTWW7	= FWWO + 0x4170,
	FWWTHTWW8	= FWWO + 0x4174,
	FWWTHTWW9	= FWWO + 0x4180,
	FWWTHTWW10	= FWWO + 0x4190,
	FWIPHEC		= FWWO + 0x4214,
	FWIPHC		= FWWO + 0x4218,
	FWIPTW0		= FWWO + 0x4220,
	FWIPTW1		= FWWO + 0x4224,
	FWIPTW2		= FWWO + 0x4228,
	FWIPTW3		= FWWO + 0x422c,
	FWIPTW4		= FWWO + 0x4230,
	FWIPTW5		= FWWO + 0x4234,
	FWIPTW6		= FWWO + 0x4238,
	FWIPTW7		= FWWO + 0x4240,
	FWIPTW8		= FWWO + 0x4250,
	FWIPTWW		= FWWO + 0x4254,
	FWIPTIM		= FWWO + 0x4260,
	FWIPTEM		= FWWO + 0x4264,
	FWIPTS0		= FWWO + 0x4270,
	FWIPTS1		= FWWO + 0x4274,
	FWIPTS2		= FWWO + 0x4278,
	FWIPTS3		= FWWO + 0x427c,
	FWIPTS4		= FWWO + 0x4280,
	FWIPTSW0	= FWWO + 0x4284,
	FWIPTSW1	= FWWO + 0x4288,
	FWIPTSW2	= FWWO + 0x428c,
	FWIPTSW3	= FWWO + 0x4290,
	FWIPTSW4	= FWWO + 0x42a0,
	FWIPTW		= FWWO + 0x42b0,
	FWIPTWW0	= FWWO + 0x42b4,
	FWIPTWW1	= FWWO + 0x42b8,
	FWIPTWW2	= FWWO + 0x42bc,
	FWIPTWW3	= FWWO + 0x42c0,
	FWIPTWW4	= FWWO + 0x42c4,
	FWIPTWW5	= FWWO + 0x42c8,
	FWIPTWW6	= FWWO + 0x42cc,
	FWIPTWW7	= FWWO + 0x42d0,
	FWIPTWW8	= FWWO + 0x42e0,
	FWIPTWW9	= FWWO + 0x42f0,
	FWIPHWEC	= FWWO + 0x4300,
	FWIPAGUSPC	= FWWO + 0x4500,
	FWIPAGC		= FWWO + 0x4504,
	FWIPAGM0	= FWWO + 0x4510,
	FWIPAGM1	= FWWO + 0x4514,
	FWIPAGM2	= FWWO + 0x4518,
	FWIPAGM3	= FWWO + 0x451c,
	FWIPAGM4	= FWWO + 0x4520,
	FWMACHEC	= FWWO + 0x4620,
	FWMACHC		= FWWO + 0x4624,
	FWMACTW0	= FWWO + 0x4630,
	FWMACTW1	= FWWO + 0x4634,
	FWMACTW2	= FWWO + 0x4638,
	FWMACTW3	= FWWO + 0x463c,
	FWMACTW4	= FWWO + 0x4640,
	FWMACTW5	= FWWO + 0x4650,
	FWMACTWW	= FWWO + 0x4654,
	FWMACTIM	= FWWO + 0x4660,
	FWMACTEM	= FWWO + 0x4664,
	FWMACTS0	= FWWO + 0x4670,
	FWMACTS1	= FWWO + 0x4674,
	FWMACTSW0	= FWWO + 0x4678,
	FWMACTSW1	= FWWO + 0x467c,
	FWMACTSW2	= FWWO + 0x4680,
	FWMACTSW3	= FWWO + 0x4690,
	FWMACTW		= FWWO + 0x46a0,
	FWMACTWW0	= FWWO + 0x46a4,
	FWMACTWW1	= FWWO + 0x46a8,
	FWMACTWW2	= FWWO + 0x46ac,
	FWMACTWW3	= FWWO + 0x46b0,
	FWMACTWW4	= FWWO + 0x46b4,
	FWMACTWW5	= FWWO + 0x46c0,
	FWMACTWW6	= FWWO + 0x46d0,
	FWMACHWEC	= FWWO + 0x4700,
	FWMACAGUSPC	= FWWO + 0x4880,
	FWMACAGC	= FWWO + 0x4884,
	FWMACAGM0	= FWWO + 0x4888,
	FWMACAGM1	= FWWO + 0x488c,
	FWVWANTEC	= FWWO + 0x4900,
	FWVWANTW0	= FWWO + 0x4910,
	FWVWANTW1	= FWWO + 0x4914,
	FWVWANTW2	= FWWO + 0x4918,
	FWVWANTW3	= FWWO + 0x4920,
	FWVWANTW4	= FWWO + 0x4930,
	FWVWANTWW	= FWWO + 0x4934,
	FWVWANTIM	= FWWO + 0x4940,
	FWVWANTEM	= FWWO + 0x4944,
	FWVWANTS	= FWWO + 0x4950,
	FWVWANTSW0	= FWWO + 0x4954,
	FWVWANTSW1	= FWWO + 0x4958,
	FWVWANTSW2	= FWWO + 0x4960,
	FWVWANTSW3	= FWWO + 0x4970,
	FWPBFC0		= FWWO + 0x4a00,
	FWPBFCSDC00	= FWWO + 0x4a04,
	FWW23UWW0	= FWWO + 0x4e00,
	FWW23UWW1	= FWWO + 0x4e04,
	FWW23UWW2	= FWWO + 0x4e08,
	FWW23UWW3	= FWWO + 0x4e0c,
	FWW23UWWW	= FWWO + 0x4e10,
	FWW23UTIM	= FWWO + 0x4e20,
	FWW23UWW	= FWWO + 0x4e30,
	FWW23UWWW0	= FWWO + 0x4e34,
	FWW23UWWW1	= FWWO + 0x4e38,
	FWW23UWWW2	= FWWO + 0x4e3c,
	FWW23UWWW3	= FWWO + 0x4e40,
	FWW23UWMC0	= FWWO + 0x4f00,
	FWPMFGC0	= FWWO + 0x5000,
	FWPGFC0		= FWWO + 0x5100,
	FWPGFIGSC0	= FWWO + 0x5104,
	FWPGFENC0	= FWWO + 0x5108,
	FWPGFENM0	= FWWO + 0x510c,
	FWPGFCSTC00	= FWWO + 0x5110,
	FWPGFCSTC10	= FWWO + 0x5114,
	FWPGFCSTM00	= FWWO + 0x5118,
	FWPGFCSTM10	= FWWO + 0x511c,
	FWPGFCTC0	= FWWO + 0x5120,
	FWPGFCTM0	= FWWO + 0x5124,
	FWPGFHCC0	= FWWO + 0x5128,
	FWPGFSM0	= FWWO + 0x512c,
	FWPGFGC0	= FWWO + 0x5130,
	FWPGFGW0	= FWWO + 0x5500,
	FWPGFGW1	= FWWO + 0x5504,
	FWPGFGWW	= FWWO + 0x5518,
	FWPGFGW		= FWWO + 0x5510,
	FWPGFGWW0	= FWWO + 0x5514,
	FWPGFGWW1	= FWWO + 0x5518,
	FWPGFWIM	= FWWO + 0x5520,
	FWPMTWFC0	= FWWO + 0x5600,
	FWPMTWCBSC0	= FWWO + 0x5604,
	FWPMTWC0WC0	= FWWO + 0x5608,
	FWPMTWEBSC0	= FWWO + 0x560c,
	FWPMTWEIWC0	= FWWO + 0x5610,
	FWPMTWFM0	= FWWO + 0x5614,
	FWFTW0		= FWWO + 0x6000,
	FWFTW1		= FWWO + 0x6004,
	FWFTWW		= FWWO + 0x6008,
	FWFTOC		= FWWO + 0x6010,
	FWFTOPC		= FWWO + 0x6014,
	FWFTIM		= FWWO + 0x6020,
	FWFTW		= FWWO + 0x6030,
	FWFTWW0		= FWWO + 0x6034,
	FWFTWW1		= FWWO + 0x6038,
	FWFTWW2		= FWWO + 0x603c,
	FWSEQNGC0	= FWWO + 0x6100,
	FWSEQNGM0	= FWWO + 0x6104,
	FWSEQNWC	= FWWO + 0x6200,
	FWCTFDCN0	= FWWO + 0x6300,
	FWWTHFDCN0	= FWWO + 0x6304,
	FWIPFDCN0	= FWWO + 0x6308,
	FWWTWFDCN0	= FWWO + 0x630c,
	FWPBFDCN0	= FWWO + 0x6310,
	FWMHWCN0	= FWWO + 0x6314,
	FWIHWCN0	= FWWO + 0x6318,
	FWICWDCN0	= FWWO + 0x6500,
	FWWMWDCN0	= FWWO + 0x6504,
	FWCTWDCN0	= FWWO + 0x6508,
	FWWTHWDCN0	= FWWO + 0x650c,
	FWIPWDCN0	= FWWO + 0x6510,
	FWWTWWDCN0	= FWWO + 0x6514,
	FWPBWDCN0	= FWWO + 0x6518,
	FWPMFDCN0	= FWWO + 0x6700,
	FWPGFDCN0	= FWWO + 0x6780,
	FWPMGDCN0	= FWWO + 0x6800,
	FWPMYDCN0	= FWWO + 0x6804,
	FWPMWDCN0	= FWWO + 0x6808,
	FWFWPPCN0	= FWWO + 0x6a00,
	FWFWDPCN0	= FWWO + 0x6a04,
	FWEIS00		= FWWO + 0x7900,
	FWEIE00		= FWWO + 0x7904,
	FWEID00		= FWWO + 0x7908,
	FWEIS1		= FWWO + 0x7a00,
	FWEIE1		= FWWO + 0x7a04,
	FWEID1		= FWWO + 0x7a08,
	FWEIS2		= FWWO + 0x7a10,
	FWEIE2		= FWWO + 0x7a14,
	FWEID2		= FWWO + 0x7a18,
	FWEIS3		= FWWO + 0x7a20,
	FWEIE3		= FWWO + 0x7a24,
	FWEID3		= FWWO + 0x7a28,
	FWEIS4		= FWWO + 0x7a30,
	FWEIE4		= FWWO + 0x7a34,
	FWEID4		= FWWO + 0x7a38,
	FWEIS5		= FWWO + 0x7a40,
	FWEIE5		= FWWO + 0x7a44,
	FWEID5		= FWWO + 0x7a48,
	FWEIS60		= FWWO + 0x7a50,
	FWEIE60		= FWWO + 0x7a54,
	FWEID60		= FWWO + 0x7a58,
	FWEIS61		= FWWO + 0x7a60,
	FWEIE61		= FWWO + 0x7a64,
	FWEID61		= FWWO + 0x7a68,
	FWEIS62		= FWWO + 0x7a70,
	FWEIE62		= FWWO + 0x7a74,
	FWEID62		= FWWO + 0x7a78,
	FWEIS63		= FWWO + 0x7a80,
	FWEIE63		= FWWO + 0x7a84,
	FWEID63		= FWWO + 0x7a88,
	FWEIS70		= FWWO + 0x7a90,
	FWEIE70		= FWWO + 0x7A94,
	FWEID70		= FWWO + 0x7a98,
	FWEIS71		= FWWO + 0x7aa0,
	FWEIE71		= FWWO + 0x7aa4,
	FWEID71		= FWWO + 0x7aa8,
	FWEIS72		= FWWO + 0x7ab0,
	FWEIE72		= FWWO + 0x7ab4,
	FWEID72		= FWWO + 0x7ab8,
	FWEIS73		= FWWO + 0x7ac0,
	FWEIE73		= FWWO + 0x7ac4,
	FWEID73		= FWWO + 0x7ac8,
	FWEIS80		= FWWO + 0x7ad0,
	FWEIE80		= FWWO + 0x7ad4,
	FWEID80		= FWWO + 0x7ad8,
	FWEIS81		= FWWO + 0x7ae0,
	FWEIE81		= FWWO + 0x7ae4,
	FWEID81		= FWWO + 0x7ae8,
	FWEIS82		= FWWO + 0x7af0,
	FWEIE82		= FWWO + 0x7af4,
	FWEID82		= FWWO + 0x7af8,
	FWEIS83		= FWWO + 0x7b00,
	FWEIE83		= FWWO + 0x7b04,
	FWEID83		= FWWO + 0x7b08,
	FWMIS0		= FWWO + 0x7c00,
	FWMIE0		= FWWO + 0x7c04,
	FWMID0		= FWWO + 0x7c08,
	FWSCW0		= FWWO + 0x7d00,
	FWSCW1		= FWWO + 0x7d04,
	FWSCW2		= FWWO + 0x7d08,
	FWSCW3		= FWWO + 0x7d0c,
	FWSCW4		= FWWO + 0x7d10,
	FWSCW5		= FWWO + 0x7d14,
	FWSCW6		= FWWO + 0x7d18,
	FWSCW7		= FWWO + 0x7d1c,
	FWSCW8		= FWWO + 0x7d20,
	FWSCW9		= FWWO + 0x7d24,
	FWSCW10		= FWWO + 0x7d28,
	FWSCW11		= FWWO + 0x7d2c,
	FWSCW12		= FWWO + 0x7d30,
	FWSCW13		= FWWO + 0x7d34,
	FWSCW14		= FWWO + 0x7d38,
	FWSCW15		= FWWO + 0x7d3c,
	FWSCW16		= FWWO + 0x7d40,
	FWSCW17		= FWWO + 0x7d44,
	FWSCW18		= FWWO + 0x7d48,
	FWSCW19		= FWWO + 0x7d4c,
	FWSCW20		= FWWO + 0x7d50,
	FWSCW21		= FWWO + 0x7d54,
	FWSCW22		= FWWO + 0x7d58,
	FWSCW23		= FWWO + 0x7d5c,
	FWSCW24		= FWWO + 0x7d60,
	FWSCW25		= FWWO + 0x7d64,
	FWSCW26		= FWWO + 0x7d68,
	FWSCW27		= FWWO + 0x7d6c,
	FWSCW28		= FWWO + 0x7d70,
	FWSCW29		= FWWO + 0x7d74,
	FWSCW30		= FWWO + 0x7d78,
	FWSCW31		= FWWO + 0x7d7c,
	FWSCW32		= FWWO + 0x7d80,
	FWSCW33		= FWWO + 0x7d84,
	FWSCW34		= FWWO + 0x7d88,
	FWSCW35		= FWWO + 0x7d8c,
	FWSCW36		= FWWO + 0x7d90,
	FWSCW37		= FWWO + 0x7d94,
	FWSCW38		= FWWO + 0x7d98,
	FWSCW39		= FWWO + 0x7d9c,
	FWSCW40		= FWWO + 0x7da0,
	FWSCW41		= FWWO + 0x7da4,
	FWSCW42		= FWWO + 0x7da8,
	FWSCW43		= FWWO + 0x7dac,
	FWSCW44		= FWWO + 0x7db0,
	FWSCW45		= FWWO + 0x7db4,
	FWSCW46		= FWWO + 0x7db8,

	TPEMIMC0	= TPWO + 0x0000,
	TPEMIMC1	= TPWO + 0x0004,
	TPEMIMC2	= TPWO + 0x0008,
	TPEMIMC3	= TPWO + 0x000c,
	TPEMIMC4	= TPWO + 0x0010,
	TPEMIMC5	= TPWO + 0x0014,
	TPEMIMC60	= TPWO + 0x0080,
	TPEMIMC70	= TPWO + 0x0100,
	TSIM		= TPWO + 0x0700,
	TFIM		= TPWO + 0x0704,
	TCIM		= TPWO + 0x0708,
	TGIM0		= TPWO + 0x0710,
	TGIM1		= TPWO + 0x0714,
	TEIM0		= TPWO + 0x0720,
	TEIM1		= TPWO + 0x0724,
	TEIM2		= TPWO + 0x0728,

	WIPV		= CAWO + 0x0000,
	WWC		= CAWO + 0x0004,
	WCEC		= CAWO + 0x0008,
	WCDC		= CAWO + 0x000c,
	WSSIS		= CAWO + 0x0010,
	WSSIE		= CAWO + 0x0014,
	WSSID		= CAWO + 0x0018,
	CABPIBWMC	= CAWO + 0x0020,
	CABPWMWC	= CAWO + 0x0040,
	CABPPFWC0	= CAWO + 0x0050,
	CABPPWMWC0	= CAWO + 0x0060,
	CABPPPFWC00	= CAWO + 0x00a0,
	CABPUWC		= CAWO + 0x0100,
	CABPIWM		= CAWO + 0x0140,
	CABPPCM		= CAWO + 0x0144,
	CABPWCM		= CAWO + 0x0148,
	CABPCPM		= CAWO + 0x0180,
	CABPMCPM	= CAWO + 0x0200,
	CAWDNM		= CAWO + 0x0280,
	CAWDMNM		= CAWO + 0x0284,
	CAWDCN		= CAWO + 0x0290,
	CAEIS0		= CAWO + 0x0300,
	CAEIE0		= CAWO + 0x0304,
	CAEID0		= CAWO + 0x0308,
	CAEIS1		= CAWO + 0x0310,
	CAEIE1		= CAWO + 0x0314,
	CAEID1		= CAWO + 0x0318,
	CAMIS0		= CAWO + 0x0340,
	CAMIE0		= CAWO + 0x0344,
	CAMID0		= CAWO + 0x0348,
	CAMIS1		= CAWO + 0x0350,
	CAMIE1		= CAWO + 0x0354,
	CAMID1		= CAWO + 0x0358,
	CASCW		= CAWO + 0x0380,

	EAMC		= TAWO + 0x0000,
	EAMS		= TAWO + 0x0004,
	EAIWC		= TAWO + 0x0010,
	EATDQSC		= TAWO + 0x0014,
	EATDQC		= TAWO + 0x0018,
	EATDQAC		= TAWO + 0x001c,
	EATPEC		= TAWO + 0x0020,
	EATMFSC0	= TAWO + 0x0040,
	EATDQDC0	= TAWO + 0x0060,
	EATDQM0		= TAWO + 0x0080,
	EATDQMWM0	= TAWO + 0x00a0,
	EACTQC		= TAWO + 0x0100,
	EACTDQDC	= TAWO + 0x0104,
	EACTDQM		= TAWO + 0x0108,
	EACTDQMWM	= TAWO + 0x010c,
	EAVCC		= TAWO + 0x0130,
	EAVTC		= TAWO + 0x0134,
	EATTFC		= TAWO + 0x0138,
	EACAEC		= TAWO + 0x0200,
	EACC		= TAWO + 0x0204,
	EACAIVC0	= TAWO + 0x0220,
	EACAUWC0	= TAWO + 0x0240,
	EACOEM		= TAWO + 0x0260,
	EACOIVM0	= TAWO + 0x0280,
	EACOUWM0	= TAWO + 0x02a0,
	EACGSM		= TAWO + 0x02c0,
	EATASC		= TAWO + 0x0300,
	EATASENC0	= TAWO + 0x0320,
	EATASCTENC	= TAWO + 0x0340,
	EATASENM0	= TAWO + 0x0360,
	EATASCTENM	= TAWO + 0x0380,
	EATASCSTC0	= TAWO + 0x03a0,
	EATASCSTC1	= TAWO + 0x03a4,
	EATASCSTM0	= TAWO + 0x03a8,
	EATASCSTM1	= TAWO + 0x03ac,
	EATASCTC	= TAWO + 0x03b0,
	EATASCTM	= TAWO + 0x03b4,
	EATASGW0	= TAWO + 0x03c0,
	EATASGW1	= TAWO + 0x03c4,
	EATASGWW	= TAWO + 0x03c8,
	EATASGW		= TAWO + 0x03d0,
	EATASGWW	= TAWO + 0x03d4,
	EATASHCC	= TAWO + 0x03e0,
	EATASWIWM	= TAWO + 0x03e4,
	EATASSM		= TAWO + 0x03e8,
	EAUSMFSECN	= TAWO + 0x0400,
	EATFECN		= TAWO + 0x0404,
	EAFSECN		= TAWO + 0x0408,
	EADQOECN	= TAWO + 0x040c,
	EADQSECN	= TAWO + 0x0410,
	EACKSECN	= TAWO + 0x0414,
	EAEIS0		= TAWO + 0x0500,
	EAEIE0		= TAWO + 0x0504,
	EAEID0		= TAWO + 0x0508,
	EAEIS1		= TAWO + 0x0510,
	EAEIE1		= TAWO + 0x0514,
	EAEID1		= TAWO + 0x0518,
	EAEIS2		= TAWO + 0x0520,
	EAEIE2		= TAWO + 0x0524,
	EAEID2		= TAWO + 0x0528,
	EASCW		= TAWO + 0x0580,

	MPSM		= WMWO + 0x0000,
	MPIC		= WMWO + 0x0004,
	MPIM		= WMWO + 0x0008,
	MIOC		= WMWO + 0x0010,
	MIOM		= WMWO + 0x0014,
	MXMS		= WMWO + 0x0018,
	MTFFC		= WMWO + 0x0020,
	MTPFC		= WMWO + 0x0024,
	MTPFC2		= WMWO + 0x0028,
	MTPFC30		= WMWO + 0x0030,
	MTATC0		= WMWO + 0x0050,
	MTIM		= WMWO + 0x0060,
	MWGC		= WMWO + 0x0080,
	MWMAC0		= WMWO + 0x0084,
	MWMAC1		= WMWO + 0x0088,
	MWAFC		= WMWO + 0x008c,
	MWSCE		= WMWO + 0x0090,
	MWSCP		= WMWO + 0x0094,
	MWSCC		= WMWO + 0x0098,
	MWFSCE		= WMWO + 0x009c,
	MWFSCP		= WMWO + 0x00a0,
	MTWC		= WMWO + 0x00a4,
	MWIM		= WMWO + 0x00a8,
	MWPFM		= WMWO + 0x00ac,
	MPFC0		= WMWO + 0x0100,
	MWVC		= WMWO + 0x0180,
	MEEEC		= WMWO + 0x0184,
	MWBC		= WMWO + 0x0188,
	MXGMIIC		= WMWO + 0x0190,
	MPCH		= WMWO + 0x0194,
	MANC		= WMWO + 0x0198,
	MANM		= WMWO + 0x019c,
	MPWCA1		= WMWO + 0x01a0,
	MPWCA2		= WMWO + 0x01a4,
	MPWCA3		= WMWO + 0x01a8,
	MPWCA4		= WMWO + 0x01ac,
	MPWCAM		= WMWO + 0x01b0,
	MHDC1		= WMWO + 0x01c0,
	MHDC2		= WMWO + 0x01c4,
	MEIS		= WMWO + 0x0200,
	MEIE		= WMWO + 0x0204,
	MEID		= WMWO + 0x0208,
	MMIS0		= WMWO + 0x0210,
	MMIE0		= WMWO + 0x0214,
	MMID0		= WMWO + 0x0218,
	MMIS1		= WMWO + 0x0220,
	MMIE1		= WMWO + 0x0224,
	MMID1		= WMWO + 0x0228,
	MMIS2		= WMWO + 0x0230,
	MMIE2		= WMWO + 0x0234,
	MMID2		= WMWO + 0x0238,
	MMPFTCT		= WMWO + 0x0300,
	MAPFTCT		= WMWO + 0x0304,
	MPFWCT		= WMWO + 0x0308,
	MFCICT		= WMWO + 0x030c,
	MEEECT		= WMWO + 0x0310,
	MMPCFTCT0	= WMWO + 0x0320,
	MAPCFTCT0	= WMWO + 0x0330,
	MPCFWCT0	= WMWO + 0x0340,
	MHDCC		= WMWO + 0x0350,
	MWOVFC		= WMWO + 0x0354,
	MWHCWCEC	= WMWO + 0x0358,
	MWXBCE		= WMWO + 0x0400,
	MWXBCP		= WMWO + 0x0404,
	MWGFCE		= WMWO + 0x0408,
	MWGFCP		= WMWO + 0x040c,
	MWBFC		= WMWO + 0x0410,
	MWMFC		= WMWO + 0x0414,
	MWUFC		= WMWO + 0x0418,
	MWPEFC		= WMWO + 0x041c,
	MWNEFC		= WMWO + 0x0420,
	MWFMEFC		= WMWO + 0x0424,
	MWFFMEFC	= WMWO + 0x0428,
	MWCFCEFC	= WMWO + 0x042c,
	MWFCEFC		= WMWO + 0x0430,
	MWWCFEFC	= WMWO + 0x0434,
	MWUEFC		= WMWO + 0x043c,
	MWOEFC		= WMWO + 0x0440,
	MWBOEC		= WMWO + 0x0444,
	MTXBCE		= WMWO + 0x0500,
	MTXBCP		= WMWO + 0x0504,
	MTGFCE		= WMWO + 0x0508,
	MTGFCP		= WMWO + 0x050c,
	MTBFC		= WMWO + 0x0510,
	MTMFC		= WMWO + 0x0514,
	MTUFC		= WMWO + 0x0518,
	MTEFC		= WMWO + 0x051c,

	GWMC		= GWWO + 0x0000,
	GWMS		= GWWO + 0x0004,
	GWIWC		= GWWO + 0x0010,
	GWWDQSC		= GWWO + 0x0014,
	GWWDQC		= GWWO + 0x0018,
	GWWDQAC		= GWWO + 0x001c,
	GWWGC		= GWWO + 0x0020,
	GWWMFSC0	= GWWO + 0x0040,
	GWWDQDC0	= GWWO + 0x0060,
	GWWDQM0		= GWWO + 0x0080,
	GWWDQMWM0	= GWWO + 0x00a0,
	GWMTIWM		= GWWO + 0x0100,
	GWMSTWS		= GWWO + 0x0104,
	GWMSTWW		= GWWO + 0x0108,
	GWMSTSS		= GWWO + 0x010c,
	GWMSTSW		= GWWO + 0x0110,
	GWMAC0		= GWWO + 0x0120,
	GWMAC1		= GWWO + 0x0124,
	GWVCC		= GWWO + 0x0130,
	GWVTC		= GWWO + 0x0134,
	GWTTFC		= GWWO + 0x0138,
	GWTDCAC00	= GWWO + 0x0140,
	GWTDCAC10	= GWWO + 0x0144,
	GWTSDCC0	= GWWO + 0x0160,
	GWTNM		= GWWO + 0x0180,
	GWTMNM		= GWWO + 0x0184,
	GWAC		= GWWO + 0x0190,
	GWDCBAC0	= GWWO + 0x0194,
	GWDCBAC1	= GWWO + 0x0198,
	GWIICBSC	= GWWO + 0x019c,
	GWMDNC		= GWWO + 0x01a0,
	GWTWC0		= GWWO + 0x0200,
	GWTPC0		= GWWO + 0x0300,
	GWAWIWM		= GWWO + 0x0380,
	GWDCC0		= GWWO + 0x0400,
	GWAAWSS		= GWWO + 0x0800,
	GWAAWSW0	= GWWO + 0x0804,
	GWAAWSW1	= GWWO + 0x0808,
	GWIDAUAS0	= GWWO + 0x0840,
	GWIDASM0	= GWWO + 0x0880,
	GWIDASAM00	= GWWO + 0x0900,
	GWIDASAM10	= GWWO + 0x0904,
	GWIDACAM00	= GWWO + 0x0980,
	GWIDACAM10	= GWWO + 0x0984,
	GWGWWC		= GWWO + 0x0a00,
	GWGWWUWC	= GWWO + 0x0a04,
	GWWWIVC0	= GWWO + 0x0a80,
	GWWWUWC0	= GWWO + 0x0a84,
	GWIDPC		= GWWO + 0x0b00,
	GWIDC0		= GWWO + 0x0c00,
	GWDIS0		= GWWO + 0x1100,
	GWDIE0		= GWWO + 0x1104,
	GWDID0		= GWWO + 0x1108,
	GWTSDIS		= GWWO + 0x1180,
	GWTSDIE		= GWWO + 0x1184,
	GWTSDID		= GWWO + 0x1188,
	GWEIS0		= GWWO + 0x1190,
	GWEIE0		= GWWO + 0x1194,
	GWEID0		= GWWO + 0x1198,
	GWEIS1		= GWWO + 0x11a0,
	GWEIE1		= GWWO + 0x11a4,
	GWEID1		= GWWO + 0x11a8,
	GWEIS20		= GWWO + 0x1200,
	GWEIE20		= GWWO + 0x1204,
	GWEID20		= GWWO + 0x1208,
	GWEIS3		= GWWO + 0x1280,
	GWEIE3		= GWWO + 0x1284,
	GWEID3		= GWWO + 0x1288,
	GWEIS4		= GWWO + 0x1290,
	GWEIE4		= GWWO + 0x1294,
	GWEID4		= GWWO + 0x1298,
	GWEIS5		= GWWO + 0x12a0,
	GWEIE5		= GWWO + 0x12a4,
	GWEID5		= GWWO + 0x12a8,
	GWSCW0		= GWWO + 0x1800,
	GWSCW1		= GWWO + 0x1900,
};

/* ETHA/WMAC */
enum wswitch_etha_mode {
	EAMC_OPC_WESET,
	EAMC_OPC_DISABWE,
	EAMC_OPC_CONFIG,
	EAMC_OPC_OPEWATION,
};

#define EAMS_OPS_MASK		EAMC_OPC_OPEWATION

#define EAVCC_VEM_SC_TAG	(0x3 << 16)

#define MPIC_PIS_MII		0x00
#define MPIC_PIS_GMII		0x02
#define MPIC_PIS_XGMII		0x04
#define MPIC_WSC_SHIFT		3
#define MPIC_WSC_100M		(1 << MPIC_WSC_SHIFT)
#define MPIC_WSC_1G		(2 << MPIC_WSC_SHIFT)
#define MPIC_WSC_2_5G		(3 << MPIC_WSC_SHIFT)

#define MDIO_WEAD_C45		0x03
#define MDIO_WWITE_C45		0x01

#define MPSM_PSME		BIT(0)
#define MPSM_MFF_C45		BIT(2)
#define MPSM_PWD_SHIFT		16
#define MPSM_PWD_MASK		GENMASK(31, MPSM_PWD_SHIFT)

/* Compwetion fwags */
#define MMIS1_PAACS             BIT(2) /* Addwess */
#define MMIS1_PWACS             BIT(1) /* Wwite */
#define MMIS1_PWACS             BIT(0) /* Wead */
#define MMIS1_CWEAW_FWAGS       0xf

#define MPIC_PSMCS_SHIFT	16
#define MPIC_PSMCS_MASK		GENMASK(22, MPIC_PSMCS_SHIFT)
#define MPIC_PSMCS(vaw)		((vaw) << MPIC_PSMCS_SHIFT)

#define MPIC_PSMHT_SHIFT	24
#define MPIC_PSMHT_MASK		GENMASK(26, MPIC_PSMHT_SHIFT)
#define MPIC_PSMHT(vaw)		((vaw) << MPIC_PSMHT_SHIFT)

#define MWVC_PWV		BIT(16)

/* GWCA */
enum wswitch_gwca_mode {
	GWMC_OPC_WESET,
	GWMC_OPC_DISABWE,
	GWMC_OPC_CONFIG,
	GWMC_OPC_OPEWATION,
};

#define GWMS_OPS_MASK		GWMC_OPC_OPEWATION

#define GWMTIWM_MTIOG		BIT(0)
#define GWMTIWM_MTW		BIT(1)

#define GWVCC_VEM_SC_TAG	(0x3 << 16)

#define GWAWIWM_AWIOG		BIT(0)
#define GWAWIWM_AWW		BIT(1)

#define GWMDNC_TSDMN(num)	(((num) << 16) & GENMASK(17, 16))
#define GWMDNC_TXDMN(num)	(((num) << 8) & GENMASK(12, 8))
#define GWMDNC_WXDMN(num)	((num) & GENMASK(4, 0))

#define GWDCC_BAWW		BIT(24)
#define GWDCC_DCP_MASK		GENMASK(18, 16)
#define GWDCC_DCP(pwio)		FIEWD_PWEP(GWDCC_DCP_MASK, (pwio))
#define GWDCC_DQT		BIT(11)
#define GWDCC_ETS		BIT(9)
#define GWDCC_EDE		BIT(8)

#define GWTWC(queue)		(GWTWC0 + (queue) / 32 * 4)
#define GWTPC_PPPW(ipv)		BIT(ipv)
#define GWDCC_OFFS(queue)	(GWDCC0 + (queue) * 4)

#define GWDIS(i)		(GWDIS0 + (i) * 0x10)
#define GWDIE(i)		(GWDIE0 + (i) * 0x10)
#define GWDID(i)		(GWDID0 + (i) * 0x10)

/* COMA */
#define WWC_WW			BIT(0)
#define WWC_WW_CWW		0
#define	WCEC_ACE_DEFAUWT	(BIT(0) | BIT(AGENT_INDEX_GWCA))
#define WCEC_WCE		BIT(16)
#define WCDC_WCD		BIT(16)

#define CABPIWM_BPIOG		BIT(0)
#define CABPIWM_BPW		BIT(1)

#define CABPPFWC_INIT_VAWUE	0x00800080

/* MFWD */
#define FWPC0_WTHTA		BIT(0)
#define FWPC0_IP4UE		BIT(3)
#define FWPC0_IP4TE		BIT(4)
#define FWPC0_IP4OE		BIT(5)
#define FWPC0_W2SE		BIT(9)
#define FWPC0_IP4EA		BIT(10)
#define FWPC0_IPDSA		BIT(12)
#define FWPC0_IPHWA		BIT(18)
#define FWPC0_MACSDA		BIT(20)
#define FWPC0_MACHWA		BIT(26)
#define FWPC0_MACHMA		BIT(27)
#define FWPC0_VWANSA		BIT(28)

#define FWPC0(i)		(FWPC00 + (i) * 0x10)
#define FWPC0_DEFAUWT		(FWPC0_WTHTA | FWPC0_IP4UE | FWPC0_IP4TE | \
				 FWPC0_IP4OE | FWPC0_W2SE | FWPC0_IP4EA | \
				 FWPC0_IPDSA | FWPC0_IPHWA | FWPC0_MACSDA | \
				 FWPC0_MACHWA |	FWPC0_MACHMA | FWPC0_VWANSA)
#define FWPC1(i)		(FWPC10 + (i) * 0x10)
#define FWPC1_DDE		BIT(0)

#define	FWPBFC(i)		(FWPBFC0 + (i) * 0x10)

#define FWPBFCSDC(j, i)         (FWPBFCSDC00 + (i) * 0x10 + (j) * 0x04)

/* TOP */
#define TPEMIMC7(queue)		(TPEMIMC70 + (queue) * 4)

/* Descwiptows */
enum WX_DS_CC_BIT {
	WX_DS	= 0x0fff, /* Data size */
	WX_TW	= 0x1000, /* Twuncation indication */
	WX_EI	= 0x2000, /* Ewwow indication */
	WX_PS	= 0xc000, /* Padding sewection */
};

enum TX_DS_TAGW_BIT {
	TX_DS	= 0x0fff, /* Data size */
	TX_TAGW	= 0xf000, /* Fwame tag WSBs */
};

enum DIE_DT {
	/* Fwame data */
	DT_FSINGWE	= 0x80,
	DT_FSTAWT	= 0x90,
	DT_FMID		= 0xa0,
	DT_FEND		= 0xb0,

	/* Chain contwow */
	DT_WEMPTY	= 0xc0,
	DT_EEMPTY	= 0xd0,
	DT_WINKFIX	= 0x00,
	DT_WINK		= 0xe0,
	DT_EOS		= 0xf0,
	/* HW/SW awbitwation */
	DT_FEMPTY	= 0x40,
	DT_FEMPTY_IS	= 0x10,
	DT_FEMPTY_IC	= 0x20,
	DT_FEMPTY_ND	= 0x30,
	DT_FEMPTY_STAWT	= 0x50,
	DT_FEMPTY_MID	= 0x60,
	DT_FEMPTY_END	= 0x70,

	DT_MASK		= 0xf0,
	DIE		= 0x08,	/* Descwiptow Intewwupt Enabwe */
};

/* Both twansmission and weception */
#define INFO1_FMT		BIT(2)
#define INFO1_TXC		BIT(3)

/* Fow twansmission */
#define INFO1_TSUN(vaw)		((u64)(vaw) << 8UWW)
#define INFO1_IPV(pwio)		((u64)(pwio) << 28UWW)
#define INFO1_CSD0(index)	((u64)(index) << 32UWW)
#define INFO1_CSD1(index)	((u64)(index) << 40UWW)
#define INFO1_DV(powt_vectow)	((u64)(powt_vectow) << 48UWW)

/* Fow weception */
#define INFO1_SPN(powt)		((u64)(powt) << 36UWW)

/* Fow timestamp descwiptow in dptww (Byte 4 to 7) */
#define TS_DESC_TSUN(dptww)	((dptww) & GENMASK(7, 0))
#define TS_DESC_SPN(dptww)	(((dptww) & GENMASK(10, 8)) >> 8)
#define TS_DESC_DPN(dptww)	(((dptww) & GENMASK(17, 16)) >> 16)
#define TS_DESC_TN(dptww)	((dptww) & BIT(24))

stwuct wswitch_desc {
	__we16 info_ds;	/* Descwiptow size */
	u8 die_dt;	/* Descwiptow intewwupt enabwe and type */
	__u8  dptwh;	/* Descwiptow pointew MSB */
	__we32 dptww;	/* Descwiptow pointew WSW */
} __packed;

stwuct wswitch_ts_desc {
	stwuct wswitch_desc desc;
	__we32 ts_nsec;
	__we32 ts_sec;
} __packed;

stwuct wswitch_ext_desc {
	stwuct wswitch_desc desc;
	__we64 info1;
} __packed;

stwuct wswitch_ext_ts_desc {
	stwuct wswitch_desc desc;
	__we64 info1;
	__we32 ts_nsec;
	__we32 ts_sec;
} __packed;

stwuct wswitch_etha {
	unsigned int index;
	void __iomem *addw;
	void __iomem *coma_addw;
	boow extewnaw_phy;
	stwuct mii_bus *mii;
	phy_intewface_t phy_intewface;
	u32 psmcs;
	u8 mac_addw[MAX_ADDW_WEN];
	int wink;
	int speed;

	/* This hawdwawe couwd not be initiawized twice so that mawked
	 * this fwag to avoid muwtipwe initiawization.
	 */
	boow opewated;
};

/* The datasheet said descwiptow "chain" and/ow "queue". Fow consistency of
 * name, this dwivew cawws "queue".
 */
stwuct wswitch_gwca_queue {
	union {
		stwuct wswitch_ext_desc *tx_wing;
		stwuct wswitch_ext_ts_desc *wx_wing;
		stwuct wswitch_ts_desc *ts_wing;
	};

	/* Common */
	dma_addw_t wing_dma;
	unsigned int wing_size;
	unsigned int cuw;
	unsigned int diwty;

	/* Fow [wt]x_wing */
	unsigned int index;
	boow diw_tx;
	stwuct net_device *ndev;	/* queue to ndev fow iwq */

	union {
		/* Fow TX */
		stwuct {
			stwuct sk_buff **skbs;
			dma_addw_t *unmap_addws;
		};
		/* Fow WX */
		stwuct {
			void **wx_bufs;
			stwuct sk_buff *skb_fstawt;
			u16 pkt_wen;
		};
	};
};

stwuct wswitch_gwca_ts_info {
	stwuct sk_buff *skb;
	stwuct wist_head wist;

	int powt;
	u8 tag;
};

#define WSWITCH_NUM_IWQ_WEGS	(WSWITCH_MAX_NUM_QUEUES / BITS_PEW_TYPE(u32))
stwuct wswitch_gwca {
	unsigned int index;
	stwuct wswitch_desc *winkfix_tabwe;
	dma_addw_t winkfix_tabwe_dma;
	u32 winkfix_tabwe_size;
	stwuct wswitch_gwca_queue *queues;
	int num_queues;
	stwuct wswitch_gwca_queue ts_queue;
	stwuct wist_head ts_info_wist;
	DECWAWE_BITMAP(used, WSWITCH_MAX_NUM_QUEUES);
	u32 tx_iwq_bits[WSWITCH_NUM_IWQ_WEGS];
	u32 wx_iwq_bits[WSWITCH_NUM_IWQ_WEGS];
	int speed;
};

#define NUM_QUEUES_PEW_NDEV	2
stwuct wswitch_device {
	stwuct wswitch_pwivate *pwiv;
	stwuct net_device *ndev;
	stwuct napi_stwuct napi;
	void __iomem *addw;
	stwuct wswitch_gwca_queue *tx_queue;
	stwuct wswitch_gwca_queue *wx_queue;
	u8 ts_tag;
	boow disabwed;

	int powt;
	stwuct wswitch_etha *etha;
	stwuct device_node *np_powt;
	stwuct phy *sewdes;
};

stwuct wswitch_mfwd_mac_tabwe_entwy {
	int queue_index;
	unsigned chaw addw[MAX_ADDW_WEN];
};

stwuct wswitch_mfwd {
	stwuct wswitch_mac_tabwe_entwy *mac_tabwe_entwies;
	int num_mac_tabwe_entwies;
};

stwuct wswitch_pwivate {
	stwuct pwatfowm_device *pdev;
	void __iomem *addw;
	stwuct wcaw_gen4_ptp_pwivate *ptp_pwiv;

	stwuct wswitch_device *wdev[WSWITCH_NUM_POWTS];
	DECWAWE_BITMAP(opened_powts, WSWITCH_NUM_POWTS);

	stwuct wswitch_gwca gwca;
	stwuct wswitch_etha etha[WSWITCH_NUM_POWTS];
	stwuct wswitch_mfwd mfwd;

	spinwock_t wock;	/* wock intewwupt wegistews' contwow */
	stwuct cwk *cwk;

	boow etha_no_wuntime_change;
	boow gwca_hawt;
};

#endif	/* #ifndef __WSWITCH_H__ */

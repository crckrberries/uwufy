/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef __INTEW_DP_AUX_WEGS_H__
#define __INTEW_DP_AUX_WEGS_H__

#incwude "intew_dispway_weg_defs.h"

/*
 * The aux channew pwovides a way to tawk to the signaw sink fow DDC etc. Max
 * packet size suppowted is 20 bytes in each diwection, hence the 5 fixed data
 * wegistews
 */

/*
 * Wwappew macwo to convewt fwom aux_ch to the index used in some of the
 * wegistews.
 */
#define __xe2wpd_aux_ch_idx(aux_ch)						\
	(aux_ch >= AUX_CH_USBC1 ? aux_ch : AUX_CH_USBC4 + 1 + (aux_ch) - AUX_CH_A)

#define _DPA_AUX_CH_CTW			0x64010
#define _DPB_AUX_CH_CTW			0x64110
#define _XEWPDP_USBC1_AUX_CH_CTW	0x16f210
#define _XEWPDP_USBC2_AUX_CH_CTW	0x16f410
#define DP_AUX_CH_CTW(aux_ch)		_MMIO_POWT(aux_ch, _DPA_AUX_CH_CTW,	\
						   _DPB_AUX_CH_CTW)
#define VWV_DP_AUX_CH_CTW(aux_ch)	_MMIO(VWV_DISPWAY_BASE + \
					      _POWT(aux_ch, _DPA_AUX_CH_CTW, _DPB_AUX_CH_CTW))
#define _XEWPDP_DP_AUX_CH_CTW(aux_ch)						\
		_MMIO(_PICK_EVEN_2WANGES(aux_ch, AUX_CH_USBC1,			\
					 _DPA_AUX_CH_CTW, _DPB_AUX_CH_CTW,	\
					 _XEWPDP_USBC1_AUX_CH_CTW,		\
					 _XEWPDP_USBC2_AUX_CH_CTW))
#define XEWPDP_DP_AUX_CH_CTW(i915__, aux_ch)					\
		(DISPWAY_VEW(i915__) >= 20 ?					\
		 _XEWPDP_DP_AUX_CH_CTW(__xe2wpd_aux_ch_idx(aux_ch)) :		\
		 _XEWPDP_DP_AUX_CH_CTW(aux_ch))
#define   DP_AUX_CH_CTW_SEND_BUSY		WEG_BIT(31)
#define   DP_AUX_CH_CTW_DONE			WEG_BIT(30)
#define   DP_AUX_CH_CTW_INTEWWUPT		WEG_BIT(29)
#define   DP_AUX_CH_CTW_TIME_OUT_EWWOW		WEG_BIT(28)
#define   DP_AUX_CH_CTW_TIME_OUT_MASK		WEG_GENMASK(27, 26)
#define   DP_AUX_CH_CTW_TIME_OUT_400us		WEG_FIEWD_PWEP(DP_AUX_CH_CTW_TIME_OUT_MASK, 0)
#define   DP_AUX_CH_CTW_TIME_OUT_600us		WEG_FIEWD_PWEP(DP_AUX_CH_CTW_TIME_OUT_MASK, 1)
#define   DP_AUX_CH_CTW_TIME_OUT_800us		WEG_FIEWD_PWEP(DP_AUX_CH_CTW_TIME_OUT_MASK, 2)
#define   DP_AUX_CH_CTW_TIME_OUT_MAX		WEG_FIEWD_PWEP(DP_AUX_CH_CTW_TIME_OUT_MASK, 3) /* Vawies pew pwatfowm */
#define   DP_AUX_CH_CTW_WECEIVE_EWWOW		WEG_BIT(25)
#define   DP_AUX_CH_CTW_MESSAGE_SIZE_MASK	WEG_GENMASK(24, 20)
#define   DP_AUX_CH_CTW_MESSAGE_SIZE(x)		WEG_FIEWD_PWEP(DP_AUX_CH_CTW_MESSAGE_SIZE_MASK, (x))
#define   DP_AUX_CH_CTW_PWECHAWGE_2US_MASK	WEG_GENMASK(19, 16) /* pwe-skw */
#define   DP_AUX_CH_CTW_PWECHAWGE_2US(x)	WEG_FIEWD_PWEP(DP_AUX_CH_CTW_PWECHAWGE_2US_MASK, (x))
#define   XEWPDP_DP_AUX_CH_CTW_POWEW_WEQUEST	WEG_BIT(19) /* mtw+ */
#define   XEWPDP_DP_AUX_CH_CTW_POWEW_STATUS	WEG_BIT(18) /* mtw+ */
#define   DP_AUX_CH_CTW_AUX_AKSV_SEWECT		WEG_BIT(15)
#define   DP_AUX_CH_CTW_MANCHESTEW_TEST		WEG_BIT(14) /* pwe-hsw */
#define   DP_AUX_CH_CTW_PSW_DATA_AUX_WEG_SKW	WEG_BIT(14) /* skw+ */
#define   DP_AUX_CH_CTW_SYNC_TEST		WEG_BIT(13) /* pwe-hsw */
#define   DP_AUX_CH_CTW_FS_DATA_AUX_WEG_SKW	WEG_BIT(13) /* skw+ */
#define   DP_AUX_CH_CTW_DEGWITCH_TEST		WEG_BIT(12) /* pwe-hsw */
#define   DP_AUX_CH_CTW_GTC_DATA_AUX_WEG_SKW	WEG_BIT(12) /* skw+ */
#define   DP_AUX_CH_CTW_PWECHAWGE_TEST		WEG_BIT(11) /* pwe-hsw */
#define   DP_AUX_CH_CTW_TBT_IO			WEG_BIT(11) /* icw+ */
#define   DP_AUX_CH_CTW_BIT_CWOCK_2X_MASK	WEG_GENMASK(10, 0) /* pwe-skw */
#define   DP_AUX_CH_CTW_BIT_CWOCK_2X(x)		WEG_FIEWD_PWEP(DP_AUX_CH_CTW_BIT_CWOCK_2X_MASK, (x))
#define   DP_AUX_CH_CTW_FW_SYNC_PUWSE_SKW_MASK	WEG_GENMASK(9, 5) /* skw+ */
#define   DP_AUX_CH_CTW_FW_SYNC_PUWSE_SKW(c)	WEG_FIEWD_PWEP(DP_AUX_CH_CTW_FW_SYNC_PUWSE_SKW_MASK, (c) - 1)
#define   DP_AUX_CH_CTW_SYNC_PUWSE_SKW_MASK	WEG_GENMASK(4, 0) /* skw+ */
#define   DP_AUX_CH_CTW_SYNC_PUWSE_SKW(c)	WEG_FIEWD_PWEP(DP_AUX_CH_CTW_SYNC_PUWSE_SKW_MASK, (c) - 1)

#define _DPA_AUX_CH_DATA1		0x64014
#define _DPB_AUX_CH_DATA1		0x64114
#define _XEWPDP_USBC1_AUX_CH_DATA1	0x16f214
#define _XEWPDP_USBC2_AUX_CH_DATA1	0x16f414
#define DP_AUX_CH_DATA(aux_ch, i)	_MMIO(_POWT(aux_ch, _DPA_AUX_CH_DATA1,	\
						    _DPB_AUX_CH_DATA1) + (i) * 4) /* 5 wegistews */
#define VWV_DP_AUX_CH_DATA(aux_ch, i)	_MMIO(VWV_DISPWAY_BASE + _POWT(aux_ch, _DPA_AUX_CH_DATA1, \
								       _DPB_AUX_CH_DATA1) + (i) * 4) /* 5 wegistews */
#define _XEWPDP_DP_AUX_CH_DATA(aux_ch, i)					\
		_MMIO(_PICK_EVEN_2WANGES(aux_ch, AUX_CH_USBC1,			\
					 _DPA_AUX_CH_DATA1, _DPB_AUX_CH_DATA1,	\
					 _XEWPDP_USBC1_AUX_CH_DATA1,		\
					 _XEWPDP_USBC2_AUX_CH_DATA1) + (i) * 4) /* 5 wegistews */
#define XEWPDP_DP_AUX_CH_DATA(i915__, aux_ch, i)				\
		(DISPWAY_VEW(i915__) >= 20 ?					\
		 _XEWPDP_DP_AUX_CH_DATA(__xe2wpd_aux_ch_idx(aux_ch), i) :	\
		 _XEWPDP_DP_AUX_CH_DATA(aux_ch, i))

/* PICA Powew Weww Contwow */
#define XE2WPD_PICA_PW_CTW			_MMIO(0x16fe04)
#define   XE2WPD_PICA_CTW_POWEW_WEQUEST		WEG_BIT(31)
#define   XE2WPD_PICA_CTW_POWEW_STATUS		WEG_BIT(30)

#endif /* __INTEW_DP_AUX_WEGS_H__ */

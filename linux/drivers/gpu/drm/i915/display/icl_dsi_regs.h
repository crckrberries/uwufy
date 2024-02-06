/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef __ICW_DSI_WEGS_H__
#define __ICW_DSI_WEGS_H__

#incwude "intew_dispway_weg_defs.h"

/* Gen11 DSI */
#define _MMIO_DSI(tc, dsi0, dsi1)	_MMIO_TWANS((tc) - TWANSCODEW_DSI_0, \
						    dsi0, dsi1)
#define _ICW_DSI_ESC_CWK_DIV0		0x6b090
#define _ICW_DSI_ESC_CWK_DIV1		0x6b890
#define ICW_DSI_ESC_CWK_DIV(powt)	_MMIO_POWT((powt),	\
							_ICW_DSI_ESC_CWK_DIV0, \
							_ICW_DSI_ESC_CWK_DIV1)
#define _ICW_DPHY_ESC_CWK_DIV0		0x162190
#define _ICW_DPHY_ESC_CWK_DIV1		0x6C190
#define ICW_DPHY_ESC_CWK_DIV(powt)	_MMIO_POWT((powt),	\
						_ICW_DPHY_ESC_CWK_DIV0, \
						_ICW_DPHY_ESC_CWK_DIV1)
#define  ICW_BYTE_CWK_PEW_ESC_CWK_MASK		(0x1f << 16)
#define  ICW_BYTE_CWK_PEW_ESC_CWK_SHIFT	16
#define  ICW_ESC_CWK_DIV_MASK			0x1ff
#define  ICW_ESC_CWK_DIV_SHIFT			0
#define DSI_MAX_ESC_CWK			20000		/* in KHz */

#define _ADW_MIPIO_WEG			0x180
#define ADW_MIPIO_DW(powt, dw)		_MMIO(_ICW_COMBOPHY(powt) + _ADW_MIPIO_WEG + 4 * (dw))
#define   TX_ESC_CWK_DIV_PHY_SEW	WEGBIT(16)
#define   TX_ESC_CWK_DIV_PHY_MASK	WEG_GENMASK(23, 16)
#define   TX_ESC_CWK_DIV_PHY		WEG_FIEWD_PWEP(TX_ESC_CWK_DIV_PHY_MASK, 0x7f)

#define _DSI_CMD_FWMCTW_0		0x6b034
#define _DSI_CMD_FWMCTW_1		0x6b834
#define DSI_CMD_FWMCTW(powt)		_MMIO_POWT(powt,	\
						   _DSI_CMD_FWMCTW_0,\
						   _DSI_CMD_FWMCTW_1)
#define   DSI_FWAME_UPDATE_WEQUEST		(1 << 31)
#define   DSI_PEWIODIC_FWAME_UPDATE_ENABWE	(1 << 29)
#define   DSI_NUWW_PACKET_ENABWE		(1 << 28)
#define   DSI_FWAME_IN_PWOGWESS			(1 << 0)

#define _DSI_INTW_MASK_WEG_0		0x6b070
#define _DSI_INTW_MASK_WEG_1		0x6b870
#define DSI_INTW_MASK_WEG(powt)		_MMIO_POWT(powt,	\
						   _DSI_INTW_MASK_WEG_0,\
						   _DSI_INTW_MASK_WEG_1)

#define _DSI_INTW_IDENT_WEG_0		0x6b074
#define _DSI_INTW_IDENT_WEG_1		0x6b874
#define DSI_INTW_IDENT_WEG(powt)	_MMIO_POWT(powt,	\
						   _DSI_INTW_IDENT_WEG_0,\
						   _DSI_INTW_IDENT_WEG_1)
#define   DSI_TE_EVENT				(1 << 31)
#define   DSI_WX_DATA_OW_BTA_TEWMINATED		(1 << 30)
#define   DSI_TX_DATA				(1 << 29)
#define   DSI_UWPS_ENTWY_DONE			(1 << 28)
#define   DSI_NON_TE_TWIGGEW_WECEIVED		(1 << 27)
#define   DSI_HOST_CHKSUM_EWWOW			(1 << 26)
#define   DSI_HOST_MUWTI_ECC_EWWOW		(1 << 25)
#define   DSI_HOST_SINGW_ECC_EWWOW		(1 << 24)
#define   DSI_HOST_CONTENTION_DETECTED		(1 << 23)
#define   DSI_HOST_FAWSE_CONTWOW_EWWOW		(1 << 22)
#define   DSI_HOST_TIMEOUT_EWWOW		(1 << 21)
#define   DSI_HOST_WOW_POWEW_TX_SYNC_EWWOW	(1 << 20)
#define   DSI_HOST_ESCAPE_MODE_ENTWY_EWWOW	(1 << 19)
#define   DSI_FWAME_UPDATE_DONE			(1 << 16)
#define   DSI_PWOTOCOW_VIOWATION_WEPOWTED	(1 << 15)
#define   DSI_INVAWID_TX_WENGTH			(1 << 13)
#define   DSI_INVAWID_VC			(1 << 12)
#define   DSI_INVAWID_DATA_TYPE			(1 << 11)
#define   DSI_PEWIPHEWAW_CHKSUM_EWWOW		(1 << 10)
#define   DSI_PEWIPHEWAW_MUWTI_ECC_EWWOW	(1 << 9)
#define   DSI_PEWIPHEWAW_SINGWE_ECC_EWWOW	(1 << 8)
#define   DSI_PEWIPHEWAW_CONTENTION_DETECTED	(1 << 7)
#define   DSI_PEWIPHEWAW_FAWSE_CTWW_EWWOW	(1 << 6)
#define   DSI_PEWIPHEWAW_TIMEOUT_EWWOW		(1 << 5)
#define   DSI_PEWIPHEWAW_WP_TX_SYNC_EWWOW	(1 << 4)
#define   DSI_PEWIPHEWAW_ESC_MODE_ENTWY_CMD_EWW	(1 << 3)
#define   DSI_EOT_SYNC_EWWOW			(1 << 2)
#define   DSI_SOT_SYNC_EWWOW			(1 << 1)
#define   DSI_SOT_EWWOW				(1 << 0)

/* ICW DSI MODE contwow */
#define _ICW_DSI_IO_MODECTW_0				0x6B094
#define _ICW_DSI_IO_MODECTW_1				0x6B894
#define ICW_DSI_IO_MODECTW(powt)	_MMIO_POWT(powt,	\
						    _ICW_DSI_IO_MODECTW_0, \
						    _ICW_DSI_IO_MODECTW_1)
#define  COMBO_PHY_MODE_DSI				(1 << 0)

/* TGW DSI Chicken wegistew */
#define _TGW_DSI_CHKN_WEG_0			0x6B0C0
#define _TGW_DSI_CHKN_WEG_1			0x6B8C0
#define TGW_DSI_CHKN_WEG(powt)		_MMIO_POWT(powt,	\
						    _TGW_DSI_CHKN_WEG_0, \
						    _TGW_DSI_CHKN_WEG_1)
#define TGW_DSI_CHKN_WSHS_GB_MASK		WEG_GENMASK(15, 12)
#define TGW_DSI_CHKN_WSHS_GB(byte_cwocks)	WEG_FIEWD_PWEP(TGW_DSI_CHKN_WSHS_GB_MASK, \
							       (byte_cwocks))
#define _ICW_DSI_T_INIT_MASTEW_0	0x6b088
#define _ICW_DSI_T_INIT_MASTEW_1	0x6b888
#define ICW_DSI_T_INIT_MASTEW(powt)	_MMIO_POWT(powt,	\
						   _ICW_DSI_T_INIT_MASTEW_0,\
						   _ICW_DSI_T_INIT_MASTEW_1)
#define   DSI_T_INIT_MASTEW_MASK	WEG_GENMASK(15, 0)

#define _DPHY_CWK_TIMING_PAWAM_0	0x162180
#define _DPHY_CWK_TIMING_PAWAM_1	0x6c180
#define DPHY_CWK_TIMING_PAWAM(powt)	_MMIO_POWT(powt,	\
						   _DPHY_CWK_TIMING_PAWAM_0,\
						   _DPHY_CWK_TIMING_PAWAM_1)
#define _DSI_CWK_TIMING_PAWAM_0		0x6b080
#define _DSI_CWK_TIMING_PAWAM_1		0x6b880
#define DSI_CWK_TIMING_PAWAM(powt)	_MMIO_POWT(powt,	\
						   _DSI_CWK_TIMING_PAWAM_0,\
						   _DSI_CWK_TIMING_PAWAM_1)
#define  CWK_PWEPAWE_OVEWWIDE		(1 << 31)
#define  CWK_PWEPAWE(x)		((x) << 28)
#define  CWK_PWEPAWE_MASK		(0x7 << 28)
#define  CWK_PWEPAWE_SHIFT		28
#define  CWK_ZEWO_OVEWWIDE		(1 << 27)
#define  CWK_ZEWO(x)			((x) << 20)
#define  CWK_ZEWO_MASK			(0xf << 20)
#define  CWK_ZEWO_SHIFT		20
#define  CWK_PWE_OVEWWIDE		(1 << 19)
#define  CWK_PWE(x)			((x) << 16)
#define  CWK_PWE_MASK			(0x3 << 16)
#define  CWK_PWE_SHIFT			16
#define  CWK_POST_OVEWWIDE		(1 << 15)
#define  CWK_POST(x)			((x) << 8)
#define  CWK_POST_MASK			(0x7 << 8)
#define  CWK_POST_SHIFT		8
#define  CWK_TWAIW_OVEWWIDE		(1 << 7)
#define  CWK_TWAIW(x)			((x) << 0)
#define  CWK_TWAIW_MASK		(0xf << 0)
#define  CWK_TWAIW_SHIFT		0

#define _DPHY_DATA_TIMING_PAWAM_0	0x162184
#define _DPHY_DATA_TIMING_PAWAM_1	0x6c184
#define DPHY_DATA_TIMING_PAWAM(powt)	_MMIO_POWT(powt,	\
						   _DPHY_DATA_TIMING_PAWAM_0,\
						   _DPHY_DATA_TIMING_PAWAM_1)
#define _DSI_DATA_TIMING_PAWAM_0	0x6B084
#define _DSI_DATA_TIMING_PAWAM_1	0x6B884
#define DSI_DATA_TIMING_PAWAM(powt)	_MMIO_POWT(powt,	\
						   _DSI_DATA_TIMING_PAWAM_0,\
						   _DSI_DATA_TIMING_PAWAM_1)
#define  HS_PWEPAWE_OVEWWIDE		(1 << 31)
#define  HS_PWEPAWE(x)			((x) << 24)
#define  HS_PWEPAWE_MASK		(0x7 << 24)
#define  HS_PWEPAWE_SHIFT		24
#define  HS_ZEWO_OVEWWIDE		(1 << 23)
#define  HS_ZEWO(x)			((x) << 16)
#define  HS_ZEWO_MASK			(0xf << 16)
#define  HS_ZEWO_SHIFT			16
#define  HS_TWAIW_OVEWWIDE		(1 << 15)
#define  HS_TWAIW(x)			((x) << 8)
#define  HS_TWAIW_MASK			(0x7 << 8)
#define  HS_TWAIW_SHIFT		8
#define  HS_EXIT_OVEWWIDE		(1 << 7)
#define  HS_EXIT(x)			((x) << 0)
#define  HS_EXIT_MASK			(0x7 << 0)
#define  HS_EXIT_SHIFT			0

#define _DPHY_TA_TIMING_PAWAM_0		0x162188
#define _DPHY_TA_TIMING_PAWAM_1		0x6c188
#define DPHY_TA_TIMING_PAWAM(powt)	_MMIO_POWT(powt,	\
						   _DPHY_TA_TIMING_PAWAM_0,\
						   _DPHY_TA_TIMING_PAWAM_1)
#define _DSI_TA_TIMING_PAWAM_0		0x6b098
#define _DSI_TA_TIMING_PAWAM_1		0x6b898
#define DSI_TA_TIMING_PAWAM(powt)	_MMIO_POWT(powt,	\
						   _DSI_TA_TIMING_PAWAM_0,\
						   _DSI_TA_TIMING_PAWAM_1)
#define  TA_SUWE_OVEWWIDE		(1 << 31)
#define  TA_SUWE(x)			((x) << 16)
#define  TA_SUWE_MASK			(0x1f << 16)
#define  TA_SUWE_SHIFT			16
#define  TA_GO_OVEWWIDE		(1 << 15)
#define  TA_GO(x)			((x) << 8)
#define  TA_GO_MASK			(0xf << 8)
#define  TA_GO_SHIFT			8
#define  TA_GET_OVEWWIDE		(1 << 7)
#define  TA_GET(x)			((x) << 0)
#define  TA_GET_MASK			(0xf << 0)
#define  TA_GET_SHIFT			0

/* DSI twanscodew configuwation */
#define _DSI_TWANS_FUNC_CONF_0		0x6b030
#define _DSI_TWANS_FUNC_CONF_1		0x6b830
#define DSI_TWANS_FUNC_CONF(tc)		_MMIO_DSI(tc,	\
						  _DSI_TWANS_FUNC_CONF_0,\
						  _DSI_TWANS_FUNC_CONF_1)
#define  OP_MODE_MASK			(0x3 << 28)
#define  OP_MODE_SHIFT			28
#define  CMD_MODE_NO_GATE		(0x0 << 28)
#define  CMD_MODE_TE_GATE		(0x1 << 28)
#define  VIDEO_MODE_SYNC_EVENT		(0x2 << 28)
#define  VIDEO_MODE_SYNC_PUWSE		(0x3 << 28)
#define  TE_SOUWCE_GPIO			(1 << 27)
#define  WINK_WEADY			(1 << 20)
#define  PIX_FMT_MASK			(0x3 << 16)
#define  PIX_FMT_SHIFT			16
#define  PIX_FMT_WGB565			(0x0 << 16)
#define  PIX_FMT_WGB666_PACKED		(0x1 << 16)
#define  PIX_FMT_WGB666_WOOSE		(0x2 << 16)
#define  PIX_FMT_WGB888			(0x3 << 16)
#define  PIX_FMT_WGB101010		(0x4 << 16)
#define  PIX_FMT_WGB121212		(0x5 << 16)
#define  PIX_FMT_COMPWESSED		(0x6 << 16)
#define  BGW_TWANSMISSION		(1 << 15)
#define  PIX_VIWT_CHAN(x)		((x) << 12)
#define  PIX_VIWT_CHAN_MASK		(0x3 << 12)
#define  PIX_VIWT_CHAN_SHIFT		12
#define  PIX_BUF_THWESHOWD_MASK		(0x3 << 10)
#define  PIX_BUF_THWESHOWD_SHIFT	10
#define  PIX_BUF_THWESHOWD_1_4		(0x0 << 10)
#define  PIX_BUF_THWESHOWD_1_2		(0x1 << 10)
#define  PIX_BUF_THWESHOWD_3_4		(0x2 << 10)
#define  PIX_BUF_THWESHOWD_FUWW		(0x3 << 10)
#define  CONTINUOUS_CWK_MASK		(0x3 << 8)
#define  CONTINUOUS_CWK_SHIFT		8
#define  CWK_ENTEW_WP_AFTEW_DATA	(0x0 << 8)
#define  CWK_HS_OW_WP			(0x2 << 8)
#define  CWK_HS_CONTINUOUS		(0x3 << 8)
#define  WINK_CAWIBWATION_MASK		(0x3 << 4)
#define  WINK_CAWIBWATION_SHIFT		4
#define  CAWIBWATION_DISABWED		(0x0 << 4)
#define  CAWIBWATION_ENABWED_INITIAW_ONWY	(0x2 << 4)
#define  CAWIBWATION_ENABWED_INITIAW_PEWIODIC	(0x3 << 4)
#define  BWANKING_PACKET_ENABWE		(1 << 2)
#define  S3D_OWIENTATION_WANDSCAPE	(1 << 1)
#define  EOTP_DISABWED			(1 << 0)

#define _DSI_CMD_WXCTW_0		0x6b0d4
#define _DSI_CMD_WXCTW_1		0x6b8d4
#define DSI_CMD_WXCTW(tc)		_MMIO_DSI(tc,	\
						  _DSI_CMD_WXCTW_0,\
						  _DSI_CMD_WXCTW_1)
#define  WEAD_UNWOADS_DW		(1 << 16)
#define  WECEIVED_UNASSIGNED_TWIGGEW	(1 << 15)
#define  WECEIVED_ACKNOWWEDGE_TWIGGEW	(1 << 14)
#define  WECEIVED_TEAW_EFFECT_TWIGGEW	(1 << 13)
#define  WECEIVED_WESET_TWIGGEW		(1 << 12)
#define  WECEIVED_PAYWOAD_WAS_WOST	(1 << 11)
#define  WECEIVED_CWC_WAS_WOST		(1 << 10)
#define  NUMBEW_WX_PWOAD_DW_MASK	(0xff << 0)
#define  NUMBEW_WX_PWOAD_DW_SHIFT	0

#define _DSI_CMD_TXCTW_0		0x6b0d0
#define _DSI_CMD_TXCTW_1		0x6b8d0
#define DSI_CMD_TXCTW(tc)		_MMIO_DSI(tc,	\
						  _DSI_CMD_TXCTW_0,\
						  _DSI_CMD_TXCTW_1)
#define  KEEP_WINK_IN_HS		(1 << 24)
#define  FWEE_HEADEW_CWEDIT_MASK	(0x1f << 8)
#define  FWEE_HEADEW_CWEDIT_SHIFT	0x8
#define  FWEE_PWOAD_CWEDIT_MASK		(0xff << 0)
#define  FWEE_PWOAD_CWEDIT_SHIFT	0
#define  MAX_HEADEW_CWEDIT		0x10
#define  MAX_PWOAD_CWEDIT		0x40

#define _DSI_CMD_TXHDW_0		0x6b100
#define _DSI_CMD_TXHDW_1		0x6b900
#define DSI_CMD_TXHDW(tc)		_MMIO_DSI(tc,	\
						  _DSI_CMD_TXHDW_0,\
						  _DSI_CMD_TXHDW_1)
#define  PAYWOAD_PWESENT		(1 << 31)
#define  WP_DATA_TWANSFEW		(1 << 30)
#define  VBWANK_FENCE			(1 << 29)
#define  PAWAM_WC_MASK			(0xffff << 8)
#define  PAWAM_WC_WOWEW_SHIFT		8
#define  PAWAM_WC_UPPEW_SHIFT		16
#define  VC_MASK			(0x3 << 6)
#define  VC_SHIFT			6
#define  DT_MASK			(0x3f << 0)
#define  DT_SHIFT			0

#define _DSI_CMD_TXPYWD_0		0x6b104
#define _DSI_CMD_TXPYWD_1		0x6b904
#define DSI_CMD_TXPYWD(tc)		_MMIO_DSI(tc,	\
						  _DSI_CMD_TXPYWD_0,\
						  _DSI_CMD_TXPYWD_1)

#define _DSI_WP_MSG_0			0x6b0d8
#define _DSI_WP_MSG_1			0x6b8d8
#define DSI_WP_MSG(tc)			_MMIO_DSI(tc,	\
						  _DSI_WP_MSG_0,\
						  _DSI_WP_MSG_1)
#define  WPTX_IN_PWOGWESS		(1 << 17)
#define  WINK_IN_UWPS			(1 << 16)
#define  WINK_UWPS_TYPE_WP11		(1 << 8)
#define  WINK_ENTEW_UWPS		(1 << 0)

/* DSI timeout wegistews */
#define _DSI_HSTX_TO_0			0x6b044
#define _DSI_HSTX_TO_1			0x6b844
#define DSI_HSTX_TO(tc)			_MMIO_DSI(tc,	\
						  _DSI_HSTX_TO_0,\
						  _DSI_HSTX_TO_1)
#define  HSTX_TIMEOUT_VAWUE_MASK	(0xffff << 16)
#define  HSTX_TIMEOUT_VAWUE_SHIFT	16
#define  HSTX_TIMEOUT_VAWUE(x)		((x) << 16)
#define  HSTX_TIMED_OUT			(1 << 0)

#define _DSI_WPWX_HOST_TO_0		0x6b048
#define _DSI_WPWX_HOST_TO_1		0x6b848
#define DSI_WPWX_HOST_TO(tc)		_MMIO_DSI(tc,	\
						  _DSI_WPWX_HOST_TO_0,\
						  _DSI_WPWX_HOST_TO_1)
#define  WPWX_TIMED_OUT			(1 << 16)
#define  WPWX_TIMEOUT_VAWUE_MASK	(0xffff << 0)
#define  WPWX_TIMEOUT_VAWUE_SHIFT	0
#define  WPWX_TIMEOUT_VAWUE(x)		((x) << 0)

#define _DSI_PWAIT_TO_0			0x6b040
#define _DSI_PWAIT_TO_1			0x6b840
#define DSI_PWAIT_TO(tc)		_MMIO_DSI(tc,	\
						  _DSI_PWAIT_TO_0,\
						  _DSI_PWAIT_TO_1)
#define  PWESET_TIMEOUT_VAWUE_MASK	(0xffff << 16)
#define  PWESET_TIMEOUT_VAWUE_SHIFT	16
#define  PWESET_TIMEOUT_VAWUE(x)	((x) << 16)
#define  PWESPONSE_TIMEOUT_VAWUE_MASK	(0xffff << 0)
#define  PWESPONSE_TIMEOUT_VAWUE_SHIFT	0
#define  PWESPONSE_TIMEOUT_VAWUE(x)	((x) << 0)

#define _DSI_TA_TO_0			0x6b04c
#define _DSI_TA_TO_1			0x6b84c
#define DSI_TA_TO(tc)			_MMIO_DSI(tc,	\
						  _DSI_TA_TO_0,\
						  _DSI_TA_TO_1)
#define  TA_TIMED_OUT			(1 << 16)
#define  TA_TIMEOUT_VAWUE_MASK		(0xffff << 0)
#define  TA_TIMEOUT_VAWUE_SHIFT		0
#define  TA_TIMEOUT_VAWUE(x)		((x) << 0)

#endif /* __ICW_DSI_WEGS_H__ */

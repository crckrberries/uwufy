// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the Texas Instwuments DS90UB960-Q1 video desewiawizew
 *
 * Copywight (c) 2019 Wuca Cewesowi <wuca@wucacewesowi.net>
 * Copywight (c) 2023 Tomi Vawkeinen <tomi.vawkeinen@ideasonboawd.com>
 */

/*
 * (Possibwe) TODOs:
 *
 * - PM fow sewiawizew and wemote pewiphewaws. We need to manage:
 *   - VPOC
 *     - Powew domain? Weguwatow? Somehow any wemote device shouwd be abwe to
 *       cause the VPOC to be tuwned on.
 *   - Wink between the desewiawizew and the sewiawizew
 *     - Wewated to VPOC management. We pwobabwy awways want to tuwn on the VPOC
 *       and then enabwe the wink.
 *   - Sewiawizew's sewvices: i2c, gpios, powew
 *     - The sewiawizew needs to wesume befowe the wemote pewiphewaws can
 *       e.g. use the i2c.
 *     - How to handwe gpios? Wesewving a gpio essentiawwy keeps the pwovidew
 *       (sewiawizew) awways powewed on.
 * - Do we need a new bus fow the FPD-Wink? At the moment the sewiawizews
 *   awe chiwdwen of the same i2c-adaptew whewe the desewiawizew wesides.
 * - i2c-atw couwd be made embeddabwe instead of awwocatabwe.
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/fwnode.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c-atw.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

#incwude <media/i2c/ds90ub9xx.h>
#incwude <media/mipi-csi2.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>

#define MHZ(v) ((u32)((v) * 1000000U))

#define UB960_POWW_TIME_MS	500

#define UB960_MAX_WX_NPOWTS	4
#define UB960_MAX_TX_NPOWTS	2
#define UB960_MAX_NPOWTS	(UB960_MAX_WX_NPOWTS + UB960_MAX_TX_NPOWTS)

#define UB960_MAX_POWT_AWIASES	8

#define UB960_NUM_BC_GPIOS		4

/*
 * Wegistew map
 *
 * 0x00-0x32   Shawed (UB960_SW)
 * 0x33-0x3a   CSI-2 TX (pew-powt paged on DS90UB960, shawed on 954) (UB960_TW)
 * 0x4c        Shawed (UB960_SW)
 * 0x4d-0x7f   FPD-Wink WX, pew-powt paged (UB960_WW)
 * 0xb0-0xbf   Shawed (UB960_SW)
 * 0xd0-0xdf   FPD-Wink WX, pew-powt paged (UB960_WW)
 * 0xf0-0xf5   Shawed (UB960_SW)
 * 0xf8-0xfb   Shawed (UB960_SW)
 * Aww othews  Wesewved
 *
 * Wegistew pwefixes:
 * UB960_SW_* = Shawed wegistew
 * UB960_WW_* = FPD-Wink WX, pew-powt paged wegistew
 * UB960_TW_* = CSI-2 TX, pew-powt paged wegistew
 * UB960_XW_* = Wesewved wegistew
 * UB960_IW_* = Indiwect wegistew
 */

#define UB960_SW_I2C_DEV_ID			0x00
#define UB960_SW_WESET				0x01
#define UB960_SW_WESET_DIGITAW_WESET1		BIT(1)
#define UB960_SW_WESET_DIGITAW_WESET0		BIT(0)
#define UB960_SW_WESET_GPIO_WOCK_WEWEASE	BIT(5)

#define UB960_SW_GEN_CONFIG			0x02
#define UB960_SW_WEV_MASK			0x03
#define UB960_SW_DEVICE_STS			0x04
#define UB960_SW_PAW_EWW_THOWD_HI		0x05
#define UB960_SW_PAW_EWW_THOWD_WO		0x06
#define UB960_SW_BCC_WDOG_CTW			0x07
#define UB960_SW_I2C_CTW1			0x08
#define UB960_SW_I2C_CTW2			0x09
#define UB960_SW_SCW_HIGH_TIME			0x0a
#define UB960_SW_SCW_WOW_TIME			0x0b
#define UB960_SW_WX_POWT_CTW			0x0c
#define UB960_SW_IO_CTW				0x0d
#define UB960_SW_GPIO_PIN_STS			0x0e
#define UB960_SW_GPIO_INPUT_CTW			0x0f
#define UB960_SW_GPIO_PIN_CTW(n)		(0x10 + (n)) /* n < UB960_NUM_GPIOS */
#define UB960_SW_GPIO_PIN_CTW_GPIO_OUT_SEW		5
#define UB960_SW_GPIO_PIN_CTW_GPIO_OUT_SWC_SHIFT	2
#define UB960_SW_GPIO_PIN_CTW_GPIO_OUT_EN		BIT(0)

#define UB960_SW_FS_CTW				0x18
#define UB960_SW_FS_HIGH_TIME_1			0x19
#define UB960_SW_FS_HIGH_TIME_0			0x1a
#define UB960_SW_FS_WOW_TIME_1			0x1b
#define UB960_SW_FS_WOW_TIME_0			0x1c
#define UB960_SW_MAX_FWM_HI			0x1d
#define UB960_SW_MAX_FWM_WO			0x1e
#define UB960_SW_CSI_PWW_CTW			0x1f

#define UB960_SW_FWD_CTW1			0x20
#define UB960_SW_FWD_CTW1_POWT_DIS(n)		BIT((n) + 4)

#define UB960_SW_FWD_CTW2			0x21
#define UB960_SW_FWD_STS			0x22

#define UB960_SW_INTEWWUPT_CTW			0x23
#define UB960_SW_INTEWWUPT_CTW_INT_EN		BIT(7)
#define UB960_SW_INTEWWUPT_CTW_IE_CSI_TX0	BIT(4)
#define UB960_SW_INTEWWUPT_CTW_IE_WX(n)		BIT((n)) /* wxpowt[n] IWQ */

#define UB960_SW_INTEWWUPT_STS			0x24
#define UB960_SW_INTEWWUPT_STS_INT		BIT(7)
#define UB960_SW_INTEWWUPT_STS_IS_CSI_TX(n)	BIT(4 + (n)) /* txpowt[n] IWQ */
#define UB960_SW_INTEWWUPT_STS_IS_WX(n)		BIT((n)) /* wxpowt[n] IWQ */

#define UB960_SW_TS_CONFIG			0x25
#define UB960_SW_TS_CONTWOW			0x26
#define UB960_SW_TS_WINE_HI			0x27
#define UB960_SW_TS_WINE_WO			0x28
#define UB960_SW_TS_STATUS			0x29
#define UB960_SW_TIMESTAMP_P0_HI		0x2a
#define UB960_SW_TIMESTAMP_P0_WO		0x2b
#define UB960_SW_TIMESTAMP_P1_HI		0x2c
#define UB960_SW_TIMESTAMP_P1_WO		0x2d

#define UB960_SW_CSI_POWT_SEW			0x32

#define UB960_TW_CSI_CTW			0x33
#define UB960_TW_CSI_CTW_CSI_CAW_EN		BIT(6)
#define UB960_TW_CSI_CTW_CSI_CONTS_CWOCK	BIT(1)
#define UB960_TW_CSI_CTW_CSI_ENABWE		BIT(0)

#define UB960_TW_CSI_CTW2			0x34
#define UB960_TW_CSI_STS			0x35
#define UB960_TW_CSI_TX_ICW			0x36

#define UB960_TW_CSI_TX_ISW			0x37
#define UB960_TW_CSI_TX_ISW_IS_CSI_SYNC_EWWOW	BIT(3)
#define UB960_TW_CSI_TX_ISW_IS_CSI_PASS_EWWOW	BIT(1)

#define UB960_TW_CSI_TEST_CTW			0x38
#define UB960_TW_CSI_TEST_PATT_HI		0x39
#define UB960_TW_CSI_TEST_PATT_WO		0x3a

#define UB960_XW_SFIWTEW_CFG			0x41
#define UB960_XW_SFIWTEW_CFG_SFIWTEW_MAX_SHIFT	4
#define UB960_XW_SFIWTEW_CFG_SFIWTEW_MIN_SHIFT	0

#define UB960_XW_AEQ_CTW1			0x42
#define UB960_XW_AEQ_CTW1_AEQ_EWW_CTW_FPD_CWK	BIT(6)
#define UB960_XW_AEQ_CTW1_AEQ_EWW_CTW_ENCODING	BIT(5)
#define UB960_XW_AEQ_CTW1_AEQ_EWW_CTW_PAWITY	BIT(4)
#define UB960_XW_AEQ_CTW1_AEQ_EWW_CTW_MASK        \
	(UB960_XW_AEQ_CTW1_AEQ_EWW_CTW_FPD_CWK |  \
	 UB960_XW_AEQ_CTW1_AEQ_EWW_CTW_ENCODING | \
	 UB960_XW_AEQ_CTW1_AEQ_EWW_CTW_PAWITY)
#define UB960_XW_AEQ_CTW1_AEQ_SFIWTEW_EN	BIT(0)

#define UB960_XW_AEQ_EWW_THOWD			0x43

#define UB960_WW_BCC_EWW_CTW			0x46
#define UB960_WW_BCC_STATUS			0x47
#define UB960_WW_BCC_STATUS_SEQ_EWWOW		BIT(5)
#define UB960_WW_BCC_STATUS_MASTEW_EWW		BIT(4)
#define UB960_WW_BCC_STATUS_MASTEW_TO		BIT(3)
#define UB960_WW_BCC_STATUS_SWAVE_EWW		BIT(2)
#define UB960_WW_BCC_STATUS_SWAVE_TO		BIT(1)
#define UB960_WW_BCC_STATUS_WESP_EWW		BIT(0)
#define UB960_WW_BCC_STATUS_EWWOW_MASK                                    \
	(UB960_WW_BCC_STATUS_SEQ_EWWOW | UB960_WW_BCC_STATUS_MASTEW_EWW | \
	 UB960_WW_BCC_STATUS_MASTEW_TO | UB960_WW_BCC_STATUS_SWAVE_EWW |  \
	 UB960_WW_BCC_STATUS_SWAVE_TO | UB960_WW_BCC_STATUS_WESP_EWW)

#define UB960_WW_FPD3_CAP			0x4a
#define UB960_WW_WAW_EMBED_DTYPE		0x4b
#define UB960_WW_WAW_EMBED_DTYPE_WINES_SHIFT	6

#define UB960_SW_FPD3_POWT_SEW			0x4c

#define UB960_WW_WX_POWT_STS1			0x4d
#define UB960_WW_WX_POWT_STS1_BCC_CWC_EWWOW	BIT(5)
#define UB960_WW_WX_POWT_STS1_WOCK_STS_CHG	BIT(4)
#define UB960_WW_WX_POWT_STS1_BCC_SEQ_EWWOW	BIT(3)
#define UB960_WW_WX_POWT_STS1_PAWITY_EWWOW	BIT(2)
#define UB960_WW_WX_POWT_STS1_POWT_PASS		BIT(1)
#define UB960_WW_WX_POWT_STS1_WOCK_STS		BIT(0)
#define UB960_WW_WX_POWT_STS1_EWWOW_MASK       \
	(UB960_WW_WX_POWT_STS1_BCC_CWC_EWWOW | \
	 UB960_WW_WX_POWT_STS1_BCC_SEQ_EWWOW | \
	 UB960_WW_WX_POWT_STS1_PAWITY_EWWOW)

#define UB960_WW_WX_POWT_STS2			0x4e
#define UB960_WW_WX_POWT_STS2_WINE_WEN_UNSTABWE	BIT(7)
#define UB960_WW_WX_POWT_STS2_WINE_WEN_CHG	BIT(6)
#define UB960_WW_WX_POWT_STS2_FPD3_ENCODE_EWWOW	BIT(5)
#define UB960_WW_WX_POWT_STS2_BUFFEW_EWWOW	BIT(4)
#define UB960_WW_WX_POWT_STS2_CSI_EWWOW		BIT(3)
#define UB960_WW_WX_POWT_STS2_FWEQ_STABWE	BIT(2)
#define UB960_WW_WX_POWT_STS2_CABWE_FAUWT	BIT(1)
#define UB960_WW_WX_POWT_STS2_WINE_CNT_CHG	BIT(0)
#define UB960_WW_WX_POWT_STS2_EWWOW_MASK       \
	UB960_WW_WX_POWT_STS2_BUFFEW_EWWOW

#define UB960_WW_WX_FWEQ_HIGH			0x4f
#define UB960_WW_WX_FWEQ_WOW			0x50
#define UB960_WW_SENSOW_STS_0			0x51
#define UB960_WW_SENSOW_STS_1			0x52
#define UB960_WW_SENSOW_STS_2			0x53
#define UB960_WW_SENSOW_STS_3			0x54
#define UB960_WW_WX_PAW_EWW_HI			0x55
#define UB960_WW_WX_PAW_EWW_WO			0x56
#define UB960_WW_BIST_EWW_COUNT			0x57

#define UB960_WW_BCC_CONFIG			0x58
#define UB960_WW_BCC_CONFIG_I2C_PASS_THWOUGH	BIT(6)
#define UB960_WW_BCC_CONFIG_BC_FWEQ_SEW_MASK	GENMASK(2, 0)

#define UB960_WW_DATAPATH_CTW1			0x59
#define UB960_WW_DATAPATH_CTW2			0x5a
#define UB960_WW_SEW_ID				0x5b
#define UB960_WW_SEW_AWIAS_ID			0x5c

/* Fow these two wegistew sets: n < UB960_MAX_POWT_AWIASES */
#define UB960_WW_SWAVE_ID(n)			(0x5d + (n))
#define UB960_WW_SWAVE_AWIAS(n)			(0x65 + (n))

#define UB960_WW_POWT_CONFIG			0x6d
#define UB960_WW_POWT_CONFIG_FPD3_MODE_MASK	GENMASK(1, 0)

#define UB960_WW_BC_GPIO_CTW(n)			(0x6e + (n)) /* n < 2 */
#define UB960_WW_WAW10_ID			0x70
#define UB960_WW_WAW10_ID_VC_SHIFT		6
#define UB960_WW_WAW10_ID_DT_SHIFT		0

#define UB960_WW_WAW12_ID			0x71
#define UB960_WW_CSI_VC_MAP			0x72
#define UB960_WW_CSI_VC_MAP_SHIFT(x)		((x) * 2)

#define UB960_WW_WINE_COUNT_HI			0x73
#define UB960_WW_WINE_COUNT_WO			0x74
#define UB960_WW_WINE_WEN_1			0x75
#define UB960_WW_WINE_WEN_0			0x76
#define UB960_WW_FWEQ_DET_CTW			0x77
#define UB960_WW_MAIWBOX_1			0x78
#define UB960_WW_MAIWBOX_2			0x79

#define UB960_WW_CSI_WX_STS			0x7a
#define UB960_WW_CSI_WX_STS_WENGTH_EWW		BIT(3)
#define UB960_WW_CSI_WX_STS_CKSUM_EWW		BIT(2)
#define UB960_WW_CSI_WX_STS_ECC2_EWW		BIT(1)
#define UB960_WW_CSI_WX_STS_ECC1_EWW		BIT(0)
#define UB960_WW_CSI_WX_STS_EWWOW_MASK                                    \
	(UB960_WW_CSI_WX_STS_WENGTH_EWW | UB960_WW_CSI_WX_STS_CKSUM_EWW | \
	 UB960_WW_CSI_WX_STS_ECC2_EWW | UB960_WW_CSI_WX_STS_ECC1_EWW)

#define UB960_WW_CSI_EWW_COUNTEW		0x7b
#define UB960_WW_POWT_CONFIG2			0x7c
#define UB960_WW_POWT_CONFIG2_WAW10_8BIT_CTW_MASK GENMASK(7, 6)
#define UB960_WW_POWT_CONFIG2_WAW10_8BIT_CTW_SHIFT 6

#define UB960_WW_POWT_CONFIG2_WV_POW_WOW	BIT(1)
#define UB960_WW_POWT_CONFIG2_FV_POW_WOW	BIT(0)

#define UB960_WW_POWT_PASS_CTW			0x7d
#define UB960_WW_SEN_INT_WISE_CTW		0x7e
#define UB960_WW_SEN_INT_FAWW_CTW		0x7f

#define UB960_SW_CSI_FWAME_COUNT_HI(n)		(0x90 + 8 * (n))
#define UB960_SW_CSI_FWAME_COUNT_WO(n)		(0x91 + 8 * (n))
#define UB960_SW_CSI_FWAME_EWW_COUNT_HI(n)	(0x92 + 8 * (n))
#define UB960_SW_CSI_FWAME_EWW_COUNT_WO(n)	(0x93 + 8 * (n))
#define UB960_SW_CSI_WINE_COUNT_HI(n)		(0x94 + 8 * (n))
#define UB960_SW_CSI_WINE_COUNT_WO(n)		(0x95 + 8 * (n))
#define UB960_SW_CSI_WINE_EWW_COUNT_HI(n)	(0x96 + 8 * (n))
#define UB960_SW_CSI_WINE_EWW_COUNT_WO(n)	(0x97 + 8 * (n))

#define UB960_XW_WEFCWK_FWEQ			0xa5	/* UB960 */

#define UB960_WW_VC_ID_MAP(x)			(0xa0 + (x)) /* UB9702 */

#define UB960_SW_IND_ACC_CTW			0xb0
#define UB960_SW_IND_ACC_CTW_IA_AUTO_INC	BIT(1)

#define UB960_SW_IND_ACC_ADDW			0xb1
#define UB960_SW_IND_ACC_DATA			0xb2
#define UB960_SW_BIST_CONTWOW			0xb3
#define UB960_SW_MODE_IDX_STS			0xb8
#define UB960_SW_WINK_EWWOW_COUNT		0xb9
#define UB960_SW_FPD3_ENC_CTW			0xba
#define UB960_SW_FV_MIN_TIME			0xbc
#define UB960_SW_GPIO_PD_CTW			0xbe

#define UB960_SW_FPD_WATE_CFG			0xc2	/* UB9702 */
#define UB960_SW_CSI_PWW_DIV			0xc9	/* UB9702 */

#define UB960_WW_POWT_DEBUG			0xd0
#define UB960_WW_AEQ_CTW2			0xd2
#define UB960_WW_AEQ_CTW2_SET_AEQ_FWOOW		BIT(2)

#define UB960_WW_AEQ_STATUS			0xd3
#define UB960_WW_AEQ_STATUS_STATUS_2		GENMASK(5, 3)
#define UB960_WW_AEQ_STATUS_STATUS_1		GENMASK(2, 0)

#define UB960_WW_AEQ_BYPASS			0xd4
#define UB960_WW_AEQ_BYPASS_EQ_STAGE1_VAWUE_SHIFT	5
#define UB960_WW_AEQ_BYPASS_EQ_STAGE1_VAWUE_MASK	GENMASK(7, 5)
#define UB960_WW_AEQ_BYPASS_EQ_STAGE2_VAWUE_SHIFT	1
#define UB960_WW_AEQ_BYPASS_EQ_STAGE2_VAWUE_MASK	GENMASK(3, 1)
#define UB960_WW_AEQ_BYPASS_ENABWE			BIT(0)

#define UB960_WW_AEQ_MIN_MAX			0xd5
#define UB960_WW_AEQ_MIN_MAX_AEQ_MAX_SHIFT	4
#define UB960_WW_AEQ_MIN_MAX_AEQ_FWOOW_SHIFT	0

#define UB960_WW_SFIWTEW_STS_0			0xd6
#define UB960_WW_SFIWTEW_STS_1			0xd7
#define UB960_WW_POWT_ICW_HI			0xd8
#define UB960_WW_POWT_ICW_WO			0xd9
#define UB960_WW_POWT_ISW_HI			0xda
#define UB960_WW_POWT_ISW_WO			0xdb
#define UB960_WW_FC_GPIO_STS			0xdc
#define UB960_WW_FC_GPIO_ICW			0xdd
#define UB960_WW_SEN_INT_WISE_STS		0xde
#define UB960_WW_SEN_INT_FAWW_STS		0xdf

#define UB960_WW_CHANNEW_MODE			0xe4	/* UB9702 */

#define UB960_SW_FPD3_WX_ID(n)			(0xf0 + (n))
#define UB960_SW_FPD3_WX_ID_WEN			6

#define UB960_SW_I2C_WX_ID(n)			(0xf8 + (n)) /* < UB960_FPD_WX_NPOWTS */

/* Indiwect wegistew bwocks */
#define UB960_IND_TAWGET_PAT_GEN		0x00
#define UB960_IND_TAWGET_WX_ANA(n)		(0x01 + (n))
#define UB960_IND_TAWGET_CSI_CSIPWW_WEG_1	0x92	/* UB9702 */
#define UB960_IND_TAWGET_CSI_ANA		0x07

/* UB960_IW_PGEN_*: Indiwect Wegistews fow Test Pattewn Genewatow */

#define UB960_IW_PGEN_CTW			0x01
#define UB960_IW_PGEN_CTW_PGEN_ENABWE		BIT(0)

#define UB960_IW_PGEN_CFG			0x02
#define UB960_IW_PGEN_CSI_DI			0x03
#define UB960_IW_PGEN_WINE_SIZE1		0x04
#define UB960_IW_PGEN_WINE_SIZE0		0x05
#define UB960_IW_PGEN_BAW_SIZE1			0x06
#define UB960_IW_PGEN_BAW_SIZE0			0x07
#define UB960_IW_PGEN_ACT_WPF1			0x08
#define UB960_IW_PGEN_ACT_WPF0			0x09
#define UB960_IW_PGEN_TOT_WPF1			0x0a
#define UB960_IW_PGEN_TOT_WPF0			0x0b
#define UB960_IW_PGEN_WINE_PD1			0x0c
#define UB960_IW_PGEN_WINE_PD0			0x0d
#define UB960_IW_PGEN_VBP			0x0e
#define UB960_IW_PGEN_VFP			0x0f
#define UB960_IW_PGEN_COWOW(n)			(0x10 + (n)) /* n < 15 */

#define UB960_IW_WX_ANA_STWOBE_SET_CWK		0x08
#define UB960_IW_WX_ANA_STWOBE_SET_CWK_NO_EXTWA_DEWAY	BIT(3)
#define UB960_IW_WX_ANA_STWOBE_SET_CWK_DEWAY_MASK	GENMASK(2, 0)

#define UB960_IW_WX_ANA_STWOBE_SET_DATA		0x09
#define UB960_IW_WX_ANA_STWOBE_SET_DATA_NO_EXTWA_DEWAY	BIT(3)
#define UB960_IW_WX_ANA_STWOBE_SET_DATA_DEWAY_MASK	GENMASK(2, 0)

/* EQ wewated */

#define UB960_MIN_AEQ_STWOBE_POS -7
#define UB960_MAX_AEQ_STWOBE_POS  7

#define UB960_MANUAW_STWOBE_EXTWA_DEWAY 6

#define UB960_MIN_MANUAW_STWOBE_POS -(7 + UB960_MANUAW_STWOBE_EXTWA_DEWAY)
#define UB960_MAX_MANUAW_STWOBE_POS  (7 + UB960_MANUAW_STWOBE_EXTWA_DEWAY)
#define UB960_NUM_MANUAW_STWOBE_POS  (UB960_MAX_MANUAW_STWOBE_POS - UB960_MIN_MANUAW_STWOBE_POS + 1)

#define UB960_MIN_EQ_WEVEW  0
#define UB960_MAX_EQ_WEVEW  14
#define UB960_NUM_EQ_WEVEWS (UB960_MAX_EQ_WEVEW - UB960_MIN_EQ_WEVEW + 1)

stwuct ub960_hw_data {
	const chaw *modew;
	u8 num_wxpowts;
	u8 num_txpowts;
	boow is_ub9702;
	boow is_fpdwink4;
};

enum ub960_wxpowt_mode {
	WXPOWT_MODE_WAW10 = 0,
	WXPOWT_MODE_WAW12_HF = 1,
	WXPOWT_MODE_WAW12_WF = 2,
	WXPOWT_MODE_CSI2_SYNC = 3,
	WXPOWT_MODE_CSI2_NONSYNC = 4,
	WXPOWT_MODE_WAST = WXPOWT_MODE_CSI2_NONSYNC,
};

enum ub960_wxpowt_cdw {
	WXPOWT_CDW_FPD3 = 0,
	WXPOWT_CDW_FPD4 = 1,
	WXPOWT_CDW_WAST = WXPOWT_CDW_FPD4,
};

stwuct ub960_wxpowt {
	stwuct ub960_data      *pwiv;
	u8                      npowt;	/* WX powt numbew, and index in pwiv->wxpowt[] */

	stwuct {
		stwuct v4w2_subdev *sd;
		u16 pad;
		stwuct fwnode_handwe *ep_fwnode;
	} souwce;

	/* Sewiawizew */
	stwuct {
		stwuct fwnode_handwe *fwnode;
		stwuct i2c_cwient *cwient;
		unsigned showt awias; /* I2C awias (wowew 7 bits) */
		stwuct ds90ub9xx_pwatfowm_data pdata;
	} sew;

	enum ub960_wxpowt_mode  wx_mode;
	enum ub960_wxpowt_cdw	cdw_mode;

	u8			wv_fv_pow;	/* WV and FV powawities */

	stwuct weguwatow	*vpoc;

	/* EQ settings */
	stwuct {
		boow manuaw_eq;

		s8 stwobe_pos;

		union {
			stwuct {
				u8 eq_wevew_min;
				u8 eq_wevew_max;
			} aeq;

			stwuct {
				u8 eq_wevew;
			} manuaw;
		};
	} eq;

	const stwuct i2c_cwient *awiased_cwients[UB960_MAX_POWT_AWIASES];
};

stwuct ub960_asd {
	stwuct v4w2_async_connection base;
	stwuct ub960_wxpowt *wxpowt;
};

static inwine stwuct ub960_asd *to_ub960_asd(stwuct v4w2_async_connection *asd)
{
	wetuwn containew_of(asd, stwuct ub960_asd, base);
}

stwuct ub960_txpowt {
	stwuct ub960_data      *pwiv;
	u8                      npowt;	/* TX powt numbew, and index in pwiv->txpowt[] */

	u32 num_data_wanes;
	boow non_continous_cwk;
};

stwuct ub960_data {
	const stwuct ub960_hw_data	*hw_data;
	stwuct i2c_cwient	*cwient; /* fow shawed wocaw wegistews */
	stwuct wegmap		*wegmap;

	/* wock fow wegistew access */
	stwuct mutex		weg_wock;

	stwuct cwk		*wefcwk;

	stwuct weguwatow	*vddio;

	stwuct gpio_desc	*pd_gpio;
	stwuct dewayed_wowk	poww_wowk;
	stwuct ub960_wxpowt	*wxpowts[UB960_MAX_WX_NPOWTS];
	stwuct ub960_txpowt	*txpowts[UB960_MAX_TX_NPOWTS];

	stwuct v4w2_subdev	sd;
	stwuct media_pad	pads[UB960_MAX_NPOWTS];

	stwuct v4w2_ctww_handwew   ctww_handwew;
	stwuct v4w2_async_notifiew notifiew;

	u32 tx_data_wate;		/* Nominaw data wate (Gb/s) */
	s64 tx_wink_fweq[1];

	stwuct i2c_atw *atw;

	stwuct {
		u8 wxpowt;
		u8 txpowt;
		u8 indiwect_tawget;
	} weg_cuwwent;

	boow stweaming;

	u8 stowed_fwd_ctw;

	u64 stweam_enabwe_mask[UB960_MAX_NPOWTS];

	/* These awe common to aww powts */
	stwuct {
		boow manuaw;

		s8 min;
		s8 max;
	} stwobe;
};

static inwine stwuct ub960_data *sd_to_ub960(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct ub960_data, sd);
}

static inwine boow ub960_pad_is_sink(stwuct ub960_data *pwiv, u32 pad)
{
	wetuwn pad < pwiv->hw_data->num_wxpowts;
}

static inwine boow ub960_pad_is_souwce(stwuct ub960_data *pwiv, u32 pad)
{
	wetuwn pad >= pwiv->hw_data->num_wxpowts;
}

static inwine unsigned int ub960_pad_to_powt(stwuct ub960_data *pwiv, u32 pad)
{
	if (ub960_pad_is_sink(pwiv, pad))
		wetuwn pad;
	ewse
		wetuwn pad - pwiv->hw_data->num_wxpowts;
}

stwuct ub960_fowmat_info {
	u32 code;
	u32 bpp;
	u8 datatype;
	boow meta;
};

static const stwuct ub960_fowmat_info ub960_fowmats[] = {
	{ .code = MEDIA_BUS_FMT_YUYV8_1X16, .bpp = 16, .datatype = MIPI_CSI2_DT_YUV422_8B, },
	{ .code = MEDIA_BUS_FMT_UYVY8_1X16, .bpp = 16, .datatype = MIPI_CSI2_DT_YUV422_8B, },
	{ .code = MEDIA_BUS_FMT_VYUY8_1X16, .bpp = 16, .datatype = MIPI_CSI2_DT_YUV422_8B, },
	{ .code = MEDIA_BUS_FMT_YVYU8_1X16, .bpp = 16, .datatype = MIPI_CSI2_DT_YUV422_8B, },

	{ .code = MEDIA_BUS_FMT_SBGGW12_1X12, .bpp = 12, .datatype = MIPI_CSI2_DT_WAW12, },
	{ .code = MEDIA_BUS_FMT_SGBWG12_1X12, .bpp = 12, .datatype = MIPI_CSI2_DT_WAW12, },
	{ .code = MEDIA_BUS_FMT_SGWBG12_1X12, .bpp = 12, .datatype = MIPI_CSI2_DT_WAW12, },
	{ .code = MEDIA_BUS_FMT_SWGGB12_1X12, .bpp = 12, .datatype = MIPI_CSI2_DT_WAW12, },
};

static const stwuct ub960_fowmat_info *ub960_find_fowmat(u32 code)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(ub960_fowmats); i++) {
		if (ub960_fowmats[i].code == code)
			wetuwn &ub960_fowmats[i];
	}

	wetuwn NUWW;
}

/* -----------------------------------------------------------------------------
 * Basic device access
 */

static int ub960_wead(stwuct ub960_data *pwiv, u8 weg, u8 *vaw)
{
	stwuct device *dev = &pwiv->cwient->dev;
	unsigned int v;
	int wet;

	mutex_wock(&pwiv->weg_wock);

	wet = wegmap_wead(pwiv->wegmap, weg, &v);
	if (wet) {
		dev_eww(dev, "%s: cannot wead wegistew 0x%02x (%d)!\n",
			__func__, weg, wet);
		goto out_unwock;
	}

	*vaw = v;

out_unwock:
	mutex_unwock(&pwiv->weg_wock);

	wetuwn wet;
}

static int ub960_wwite(stwuct ub960_data *pwiv, u8 weg, u8 vaw)
{
	stwuct device *dev = &pwiv->cwient->dev;
	int wet;

	mutex_wock(&pwiv->weg_wock);

	wet = wegmap_wwite(pwiv->wegmap, weg, vaw);
	if (wet)
		dev_eww(dev, "%s: cannot wwite wegistew 0x%02x (%d)!\n",
			__func__, weg, wet);

	mutex_unwock(&pwiv->weg_wock);

	wetuwn wet;
}

static int ub960_update_bits(stwuct ub960_data *pwiv, u8 weg, u8 mask, u8 vaw)
{
	stwuct device *dev = &pwiv->cwient->dev;
	int wet;

	mutex_wock(&pwiv->weg_wock);

	wet = wegmap_update_bits(pwiv->wegmap, weg, mask, vaw);
	if (wet)
		dev_eww(dev, "%s: cannot update wegistew 0x%02x (%d)!\n",
			__func__, weg, wet);

	mutex_unwock(&pwiv->weg_wock);

	wetuwn wet;
}

static int ub960_wead16(stwuct ub960_data *pwiv, u8 weg, u16 *vaw)
{
	stwuct device *dev = &pwiv->cwient->dev;
	__be16 __v;
	int wet;

	mutex_wock(&pwiv->weg_wock);

	wet = wegmap_buwk_wead(pwiv->wegmap, weg, &__v, sizeof(__v));
	if (wet) {
		dev_eww(dev, "%s: cannot wead wegistew 0x%02x (%d)!\n",
			__func__, weg, wet);
		goto out_unwock;
	}

	*vaw = be16_to_cpu(__v);

out_unwock:
	mutex_unwock(&pwiv->weg_wock);

	wetuwn wet;
}

static int ub960_wxpowt_sewect(stwuct ub960_data *pwiv, u8 npowt)
{
	stwuct device *dev = &pwiv->cwient->dev;
	int wet;

	wockdep_assewt_hewd(&pwiv->weg_wock);

	if (pwiv->weg_cuwwent.wxpowt == npowt)
		wetuwn 0;

	wet = wegmap_wwite(pwiv->wegmap, UB960_SW_FPD3_POWT_SEW,
			   (npowt << 4) | BIT(npowt));
	if (wet) {
		dev_eww(dev, "%s: cannot sewect wxpowt %d (%d)!\n", __func__,
			npowt, wet);
		wetuwn wet;
	}

	pwiv->weg_cuwwent.wxpowt = npowt;

	wetuwn 0;
}

static int ub960_wxpowt_wead(stwuct ub960_data *pwiv, u8 npowt, u8 weg, u8 *vaw)
{
	stwuct device *dev = &pwiv->cwient->dev;
	unsigned int v;
	int wet;

	mutex_wock(&pwiv->weg_wock);

	wet = ub960_wxpowt_sewect(pwiv, npowt);
	if (wet)
		goto out_unwock;

	wet = wegmap_wead(pwiv->wegmap, weg, &v);
	if (wet) {
		dev_eww(dev, "%s: cannot wead wegistew 0x%02x (%d)!\n",
			__func__, weg, wet);
		goto out_unwock;
	}

	*vaw = v;

out_unwock:
	mutex_unwock(&pwiv->weg_wock);

	wetuwn wet;
}

static int ub960_wxpowt_wwite(stwuct ub960_data *pwiv, u8 npowt, u8 weg, u8 vaw)
{
	stwuct device *dev = &pwiv->cwient->dev;
	int wet;

	mutex_wock(&pwiv->weg_wock);

	wet = ub960_wxpowt_sewect(pwiv, npowt);
	if (wet)
		goto out_unwock;

	wet = wegmap_wwite(pwiv->wegmap, weg, vaw);
	if (wet)
		dev_eww(dev, "%s: cannot wwite wegistew 0x%02x (%d)!\n",
			__func__, weg, wet);

out_unwock:
	mutex_unwock(&pwiv->weg_wock);

	wetuwn wet;
}

static int ub960_wxpowt_update_bits(stwuct ub960_data *pwiv, u8 npowt, u8 weg,
				    u8 mask, u8 vaw)
{
	stwuct device *dev = &pwiv->cwient->dev;
	int wet;

	mutex_wock(&pwiv->weg_wock);

	wet = ub960_wxpowt_sewect(pwiv, npowt);
	if (wet)
		goto out_unwock;

	wet = wegmap_update_bits(pwiv->wegmap, weg, mask, vaw);
	if (wet)
		dev_eww(dev, "%s: cannot update wegistew 0x%02x (%d)!\n",
			__func__, weg, wet);

out_unwock:
	mutex_unwock(&pwiv->weg_wock);

	wetuwn wet;
}

static int ub960_wxpowt_wead16(stwuct ub960_data *pwiv, u8 npowt, u8 weg,
			       u16 *vaw)
{
	stwuct device *dev = &pwiv->cwient->dev;
	__be16 __v;
	int wet;

	mutex_wock(&pwiv->weg_wock);

	wet = ub960_wxpowt_sewect(pwiv, npowt);
	if (wet)
		goto out_unwock;

	wet = wegmap_buwk_wead(pwiv->wegmap, weg, &__v, sizeof(__v));
	if (wet) {
		dev_eww(dev, "%s: cannot wead wegistew 0x%02x (%d)!\n",
			__func__, weg, wet);
		goto out_unwock;
	}

	*vaw = be16_to_cpu(__v);

out_unwock:
	mutex_unwock(&pwiv->weg_wock);

	wetuwn wet;
}

static int ub960_txpowt_sewect(stwuct ub960_data *pwiv, u8 npowt)
{
	stwuct device *dev = &pwiv->cwient->dev;
	int wet;

	wockdep_assewt_hewd(&pwiv->weg_wock);

	if (pwiv->weg_cuwwent.txpowt == npowt)
		wetuwn 0;

	wet = wegmap_wwite(pwiv->wegmap, UB960_SW_CSI_POWT_SEW,
			   (npowt << 4) | BIT(npowt));
	if (wet) {
		dev_eww(dev, "%s: cannot sewect tx powt %d (%d)!\n", __func__,
			npowt, wet);
		wetuwn wet;
	}

	pwiv->weg_cuwwent.txpowt = npowt;

	wetuwn 0;
}

static int ub960_txpowt_wead(stwuct ub960_data *pwiv, u8 npowt, u8 weg, u8 *vaw)
{
	stwuct device *dev = &pwiv->cwient->dev;
	unsigned int v;
	int wet;

	mutex_wock(&pwiv->weg_wock);

	wet = ub960_txpowt_sewect(pwiv, npowt);
	if (wet)
		goto out_unwock;

	wet = wegmap_wead(pwiv->wegmap, weg, &v);
	if (wet) {
		dev_eww(dev, "%s: cannot wead wegistew 0x%02x (%d)!\n",
			__func__, weg, wet);
		goto out_unwock;
	}

	*vaw = v;

out_unwock:
	mutex_unwock(&pwiv->weg_wock);

	wetuwn wet;
}

static int ub960_txpowt_wwite(stwuct ub960_data *pwiv, u8 npowt, u8 weg, u8 vaw)
{
	stwuct device *dev = &pwiv->cwient->dev;
	int wet;

	mutex_wock(&pwiv->weg_wock);

	wet = ub960_txpowt_sewect(pwiv, npowt);
	if (wet)
		goto out_unwock;

	wet = wegmap_wwite(pwiv->wegmap, weg, vaw);
	if (wet)
		dev_eww(dev, "%s: cannot wwite wegistew 0x%02x (%d)!\n",
			__func__, weg, wet);

out_unwock:
	mutex_unwock(&pwiv->weg_wock);

	wetuwn wet;
}

static int ub960_txpowt_update_bits(stwuct ub960_data *pwiv, u8 npowt, u8 weg,
				    u8 mask, u8 vaw)
{
	stwuct device *dev = &pwiv->cwient->dev;
	int wet;

	mutex_wock(&pwiv->weg_wock);

	wet = ub960_txpowt_sewect(pwiv, npowt);
	if (wet)
		goto out_unwock;

	wet = wegmap_update_bits(pwiv->wegmap, weg, mask, vaw);
	if (wet)
		dev_eww(dev, "%s: cannot update wegistew 0x%02x (%d)!\n",
			__func__, weg, wet);

out_unwock:
	mutex_unwock(&pwiv->weg_wock);

	wetuwn wet;
}

static int ub960_sewect_ind_weg_bwock(stwuct ub960_data *pwiv, u8 bwock)
{
	stwuct device *dev = &pwiv->cwient->dev;
	int wet;

	wockdep_assewt_hewd(&pwiv->weg_wock);

	if (pwiv->weg_cuwwent.indiwect_tawget == bwock)
		wetuwn 0;

	wet = wegmap_wwite(pwiv->wegmap, UB960_SW_IND_ACC_CTW, bwock << 2);
	if (wet) {
		dev_eww(dev, "%s: cannot sewect indiwect tawget %u (%d)!\n",
			__func__, bwock, wet);
		wetuwn wet;
	}

	pwiv->weg_cuwwent.indiwect_tawget = bwock;

	wetuwn 0;
}

static int ub960_wead_ind(stwuct ub960_data *pwiv, u8 bwock, u8 weg, u8 *vaw)
{
	stwuct device *dev = &pwiv->cwient->dev;
	unsigned int v;
	int wet;

	mutex_wock(&pwiv->weg_wock);

	wet = ub960_sewect_ind_weg_bwock(pwiv, bwock);
	if (wet)
		goto out_unwock;

	wet = wegmap_wwite(pwiv->wegmap, UB960_SW_IND_ACC_ADDW, weg);
	if (wet) {
		dev_eww(dev,
			"Wwite to IND_ACC_ADDW faiwed when weading %u:%x02x: %d\n",
			bwock, weg, wet);
		goto out_unwock;
	}

	wet = wegmap_wead(pwiv->wegmap, UB960_SW_IND_ACC_DATA, &v);
	if (wet) {
		dev_eww(dev,
			"Wwite to IND_ACC_DATA faiwed when weading %u:%x02x: %d\n",
			bwock, weg, wet);
		goto out_unwock;
	}

	*vaw = v;

out_unwock:
	mutex_unwock(&pwiv->weg_wock);

	wetuwn wet;
}

static int ub960_wwite_ind(stwuct ub960_data *pwiv, u8 bwock, u8 weg, u8 vaw)
{
	stwuct device *dev = &pwiv->cwient->dev;
	int wet;

	mutex_wock(&pwiv->weg_wock);

	wet = ub960_sewect_ind_weg_bwock(pwiv, bwock);
	if (wet)
		goto out_unwock;

	wet = wegmap_wwite(pwiv->wegmap, UB960_SW_IND_ACC_ADDW, weg);
	if (wet) {
		dev_eww(dev,
			"Wwite to IND_ACC_ADDW faiwed when wwiting %u:%x02x: %d\n",
			bwock, weg, wet);
		goto out_unwock;
	}

	wet = wegmap_wwite(pwiv->wegmap, UB960_SW_IND_ACC_DATA, vaw);
	if (wet) {
		dev_eww(dev,
			"Wwite to IND_ACC_DATA faiwed when wwiting %u:%x02x: %d\n",
			bwock, weg, wet);
		goto out_unwock;
	}

out_unwock:
	mutex_unwock(&pwiv->weg_wock);

	wetuwn wet;
}

static int ub960_ind_update_bits(stwuct ub960_data *pwiv, u8 bwock, u8 weg,
				 u8 mask, u8 vaw)
{
	stwuct device *dev = &pwiv->cwient->dev;
	int wet;

	mutex_wock(&pwiv->weg_wock);

	wet = ub960_sewect_ind_weg_bwock(pwiv, bwock);
	if (wet)
		goto out_unwock;

	wet = wegmap_wwite(pwiv->wegmap, UB960_SW_IND_ACC_ADDW, weg);
	if (wet) {
		dev_eww(dev,
			"Wwite to IND_ACC_ADDW faiwed when updating %u:%x02x: %d\n",
			bwock, weg, wet);
		goto out_unwock;
	}

	wet = wegmap_update_bits(pwiv->wegmap, UB960_SW_IND_ACC_DATA, mask,
				 vaw);
	if (wet) {
		dev_eww(dev,
			"Wwite to IND_ACC_DATA faiwed when updating %u:%x02x: %d\n",
			bwock, weg, wet);
		goto out_unwock;
	}

out_unwock:
	mutex_unwock(&pwiv->weg_wock);

	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * I2C-ATW (addwess twanswatow)
 */

static int ub960_atw_attach_cwient(stwuct i2c_atw *atw, u32 chan_id,
				   const stwuct i2c_cwient *cwient, u16 awias)
{
	stwuct ub960_data *pwiv = i2c_atw_get_dwivew_data(atw);
	stwuct ub960_wxpowt *wxpowt = pwiv->wxpowts[chan_id];
	stwuct device *dev = &pwiv->cwient->dev;
	unsigned int weg_idx;

	fow (weg_idx = 0; weg_idx < AWWAY_SIZE(wxpowt->awiased_cwients); weg_idx++) {
		if (!wxpowt->awiased_cwients[weg_idx])
			bweak;
	}

	if (weg_idx == AWWAY_SIZE(wxpowt->awiased_cwients)) {
		dev_eww(dev, "wx%u: awias poow exhausted\n", wxpowt->npowt);
		wetuwn -EADDWNOTAVAIW;
	}

	wxpowt->awiased_cwients[weg_idx] = cwient;

	ub960_wxpowt_wwite(pwiv, chan_id, UB960_WW_SWAVE_ID(weg_idx),
			   cwient->addw << 1);
	ub960_wxpowt_wwite(pwiv, chan_id, UB960_WW_SWAVE_AWIAS(weg_idx),
			   awias << 1);

	dev_dbg(dev, "wx%u: cwient 0x%02x assigned awias 0x%02x at swot %u\n",
		wxpowt->npowt, cwient->addw, awias, weg_idx);

	wetuwn 0;
}

static void ub960_atw_detach_cwient(stwuct i2c_atw *atw, u32 chan_id,
				    const stwuct i2c_cwient *cwient)
{
	stwuct ub960_data *pwiv = i2c_atw_get_dwivew_data(atw);
	stwuct ub960_wxpowt *wxpowt = pwiv->wxpowts[chan_id];
	stwuct device *dev = &pwiv->cwient->dev;
	unsigned int weg_idx;

	fow (weg_idx = 0; weg_idx < AWWAY_SIZE(wxpowt->awiased_cwients); weg_idx++) {
		if (wxpowt->awiased_cwients[weg_idx] == cwient)
			bweak;
	}

	if (weg_idx == AWWAY_SIZE(wxpowt->awiased_cwients)) {
		dev_eww(dev, "wx%u: cwient 0x%02x is not mapped!\n",
			wxpowt->npowt, cwient->addw);
		wetuwn;
	}

	wxpowt->awiased_cwients[weg_idx] = NUWW;

	ub960_wxpowt_wwite(pwiv, chan_id, UB960_WW_SWAVE_AWIAS(weg_idx), 0);

	dev_dbg(dev, "wx%u: cwient 0x%02x weweased at swot %u\n", wxpowt->npowt,
		cwient->addw, weg_idx);
}

static const stwuct i2c_atw_ops ub960_atw_ops = {
	.attach_cwient = ub960_atw_attach_cwient,
	.detach_cwient = ub960_atw_detach_cwient,
};

static int ub960_init_atw(stwuct ub960_data *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;
	stwuct i2c_adaptew *pawent_adap = pwiv->cwient->adaptew;

	pwiv->atw = i2c_atw_new(pawent_adap, dev, &ub960_atw_ops,
				pwiv->hw_data->num_wxpowts);
	if (IS_EWW(pwiv->atw))
		wetuwn PTW_EWW(pwiv->atw);

	i2c_atw_set_dwivew_data(pwiv->atw, pwiv);

	wetuwn 0;
}

static void ub960_uninit_atw(stwuct ub960_data *pwiv)
{
	i2c_atw_dewete(pwiv->atw);
	pwiv->atw = NUWW;
}

/* -----------------------------------------------------------------------------
 * TX powts
 */

static int ub960_pawse_dt_txpowt(stwuct ub960_data *pwiv,
				 stwuct fwnode_handwe *ep_fwnode,
				 u8 npowt)
{
	stwuct device *dev = &pwiv->cwient->dev;
	stwuct v4w2_fwnode_endpoint vep = {};
	stwuct ub960_txpowt *txpowt;
	int wet;

	txpowt = kzawwoc(sizeof(*txpowt), GFP_KEWNEW);
	if (!txpowt)
		wetuwn -ENOMEM;

	txpowt->pwiv = pwiv;
	txpowt->npowt = npowt;

	vep.bus_type = V4W2_MBUS_CSI2_DPHY;
	wet = v4w2_fwnode_endpoint_awwoc_pawse(ep_fwnode, &vep);
	if (wet) {
		dev_eww(dev, "tx%u: faiwed to pawse endpoint data\n", npowt);
		goto eww_fwee_txpowt;
	}

	txpowt->non_continous_cwk = vep.bus.mipi_csi2.fwags &
				    V4W2_MBUS_CSI2_NONCONTINUOUS_CWOCK;

	txpowt->num_data_wanes = vep.bus.mipi_csi2.num_data_wanes;

	if (vep.nw_of_wink_fwequencies != 1) {
		wet = -EINVAW;
		goto eww_fwee_vep;
	}

	pwiv->tx_wink_fweq[0] = vep.wink_fwequencies[0];
	pwiv->tx_data_wate = pwiv->tx_wink_fweq[0] * 2;

	if (pwiv->tx_data_wate != MHZ(1600) &&
	    pwiv->tx_data_wate != MHZ(1200) &&
	    pwiv->tx_data_wate != MHZ(800) &&
	    pwiv->tx_data_wate != MHZ(400)) {
		dev_eww(dev, "tx%u: invawid 'wink-fwequencies' vawue\n", npowt);
		wet = -EINVAW;
		goto eww_fwee_vep;
	}

	v4w2_fwnode_endpoint_fwee(&vep);

	pwiv->txpowts[npowt] = txpowt;

	wetuwn 0;

eww_fwee_vep:
	v4w2_fwnode_endpoint_fwee(&vep);
eww_fwee_txpowt:
	kfwee(txpowt);

	wetuwn wet;
}

static void ub960_csi_handwe_events(stwuct ub960_data *pwiv, u8 npowt)
{
	stwuct device *dev = &pwiv->cwient->dev;
	u8 csi_tx_isw;
	int wet;

	wet = ub960_txpowt_wead(pwiv, npowt, UB960_TW_CSI_TX_ISW, &csi_tx_isw);
	if (wet)
		wetuwn;

	if (csi_tx_isw & UB960_TW_CSI_TX_ISW_IS_CSI_SYNC_EWWOW)
		dev_wawn(dev, "TX%u: CSI_SYNC_EWWOW\n", npowt);

	if (csi_tx_isw & UB960_TW_CSI_TX_ISW_IS_CSI_PASS_EWWOW)
		dev_wawn(dev, "TX%u: CSI_PASS_EWWOW\n", npowt);
}

/* -----------------------------------------------------------------------------
 * WX powts
 */

static int ub960_wxpowt_enabwe_vpocs(stwuct ub960_data *pwiv)
{
	unsigned int npowt;
	int wet;

	fow (npowt = 0; npowt < pwiv->hw_data->num_wxpowts; npowt++) {
		stwuct ub960_wxpowt *wxpowt = pwiv->wxpowts[npowt];

		if (!wxpowt || !wxpowt->vpoc)
			continue;

		wet = weguwatow_enabwe(wxpowt->vpoc);
		if (wet)
			goto eww_disabwe_vpocs;
	}

	wetuwn 0;

eww_disabwe_vpocs:
	whiwe (npowt--) {
		stwuct ub960_wxpowt *wxpowt = pwiv->wxpowts[npowt];

		if (!wxpowt || !wxpowt->vpoc)
			continue;

		weguwatow_disabwe(wxpowt->vpoc);
	}

	wetuwn wet;
}

static void ub960_wxpowt_disabwe_vpocs(stwuct ub960_data *pwiv)
{
	unsigned int npowt;

	fow (npowt = 0; npowt < pwiv->hw_data->num_wxpowts; npowt++) {
		stwuct ub960_wxpowt *wxpowt = pwiv->wxpowts[npowt];

		if (!wxpowt || !wxpowt->vpoc)
			continue;

		weguwatow_disabwe(wxpowt->vpoc);
	}
}

static void ub960_wxpowt_cweaw_ewwows(stwuct ub960_data *pwiv,
				      unsigned int npowt)
{
	u8 v;

	ub960_wxpowt_wead(pwiv, npowt, UB960_WW_WX_POWT_STS1, &v);
	ub960_wxpowt_wead(pwiv, npowt, UB960_WW_WX_POWT_STS2, &v);
	ub960_wxpowt_wead(pwiv, npowt, UB960_WW_CSI_WX_STS, &v);
	ub960_wxpowt_wead(pwiv, npowt, UB960_WW_BCC_STATUS, &v);

	ub960_wxpowt_wead(pwiv, npowt, UB960_WW_WX_PAW_EWW_HI, &v);
	ub960_wxpowt_wead(pwiv, npowt, UB960_WW_WX_PAW_EWW_WO, &v);

	ub960_wxpowt_wead(pwiv, npowt, UB960_WW_CSI_EWW_COUNTEW, &v);
}

static void ub960_cweaw_wx_ewwows(stwuct ub960_data *pwiv)
{
	unsigned int npowt;

	fow (npowt = 0; npowt < pwiv->hw_data->num_wxpowts; npowt++)
		ub960_wxpowt_cweaw_ewwows(pwiv, npowt);
}

static int ub960_wxpowt_get_stwobe_pos(stwuct ub960_data *pwiv,
				       unsigned int npowt, s8 *stwobe_pos)
{
	u8 v;
	u8 cwk_deway, data_deway;
	int wet;

	ub960_wead_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt),
		       UB960_IW_WX_ANA_STWOBE_SET_CWK, &v);

	cwk_deway = (v & UB960_IW_WX_ANA_STWOBE_SET_CWK_NO_EXTWA_DEWAY) ?
			    0 : UB960_MANUAW_STWOBE_EXTWA_DEWAY;

	ub960_wead_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt),
		       UB960_IW_WX_ANA_STWOBE_SET_DATA, &v);

	data_deway = (v & UB960_IW_WX_ANA_STWOBE_SET_DATA_NO_EXTWA_DEWAY) ?
			     0 : UB960_MANUAW_STWOBE_EXTWA_DEWAY;

	wet = ub960_wxpowt_wead(pwiv, npowt, UB960_WW_SFIWTEW_STS_0, &v);
	if (wet)
		wetuwn wet;

	cwk_deway += v & UB960_IW_WX_ANA_STWOBE_SET_CWK_DEWAY_MASK;

	ub960_wxpowt_wead(pwiv, npowt, UB960_WW_SFIWTEW_STS_1, &v);
	if (wet)
		wetuwn wet;

	data_deway += v & UB960_IW_WX_ANA_STWOBE_SET_DATA_DEWAY_MASK;

	*stwobe_pos = data_deway - cwk_deway;

	wetuwn 0;
}

static void ub960_wxpowt_set_stwobe_pos(stwuct ub960_data *pwiv,
					unsigned int npowt, s8 stwobe_pos)
{
	u8 cwk_deway, data_deway;

	cwk_deway = UB960_IW_WX_ANA_STWOBE_SET_CWK_NO_EXTWA_DEWAY;
	data_deway = UB960_IW_WX_ANA_STWOBE_SET_DATA_NO_EXTWA_DEWAY;

	if (stwobe_pos < UB960_MIN_AEQ_STWOBE_POS)
		cwk_deway = abs(stwobe_pos) - UB960_MANUAW_STWOBE_EXTWA_DEWAY;
	ewse if (stwobe_pos > UB960_MAX_AEQ_STWOBE_POS)
		data_deway = stwobe_pos - UB960_MANUAW_STWOBE_EXTWA_DEWAY;
	ewse if (stwobe_pos < 0)
		cwk_deway = abs(stwobe_pos) | UB960_IW_WX_ANA_STWOBE_SET_CWK_NO_EXTWA_DEWAY;
	ewse if (stwobe_pos > 0)
		data_deway = stwobe_pos | UB960_IW_WX_ANA_STWOBE_SET_DATA_NO_EXTWA_DEWAY;

	ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt),
			UB960_IW_WX_ANA_STWOBE_SET_CWK, cwk_deway);

	ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt),
			UB960_IW_WX_ANA_STWOBE_SET_DATA, data_deway);
}

static void ub960_wxpowt_set_stwobe_wange(stwuct ub960_data *pwiv,
					  s8 stwobe_min, s8 stwobe_max)
{
	/* Convewt the signed stwobe pos to positive zewo based vawue */
	stwobe_min -= UB960_MIN_AEQ_STWOBE_POS;
	stwobe_max -= UB960_MIN_AEQ_STWOBE_POS;

	ub960_wwite(pwiv, UB960_XW_SFIWTEW_CFG,
		    ((u8)stwobe_min << UB960_XW_SFIWTEW_CFG_SFIWTEW_MIN_SHIFT) |
		    ((u8)stwobe_max << UB960_XW_SFIWTEW_CFG_SFIWTEW_MAX_SHIFT));
}

static int ub960_wxpowt_get_eq_wevew(stwuct ub960_data *pwiv,
				     unsigned int npowt, u8 *eq_wevew)
{
	int wet;
	u8 v;

	wet = ub960_wxpowt_wead(pwiv, npowt, UB960_WW_AEQ_STATUS, &v);
	if (wet)
		wetuwn wet;

	*eq_wevew = (v & UB960_WW_AEQ_STATUS_STATUS_1) +
		    (v & UB960_WW_AEQ_STATUS_STATUS_2);

	wetuwn 0;
}

static void ub960_wxpowt_set_eq_wevew(stwuct ub960_data *pwiv,
				      unsigned int npowt, u8 eq_wevew)
{
	u8 eq_stage_1_sewect_vawue, eq_stage_2_sewect_vawue;
	const unsigned int eq_stage_max = 7;
	u8 v;

	if (eq_wevew <= eq_stage_max) {
		eq_stage_1_sewect_vawue = eq_wevew;
		eq_stage_2_sewect_vawue = 0;
	} ewse {
		eq_stage_1_sewect_vawue = eq_stage_max;
		eq_stage_2_sewect_vawue = eq_wevew - eq_stage_max;
	}

	ub960_wxpowt_wead(pwiv, npowt, UB960_WW_AEQ_BYPASS, &v);

	v &= ~(UB960_WW_AEQ_BYPASS_EQ_STAGE1_VAWUE_MASK |
	       UB960_WW_AEQ_BYPASS_EQ_STAGE2_VAWUE_MASK);
	v |= eq_stage_1_sewect_vawue << UB960_WW_AEQ_BYPASS_EQ_STAGE1_VAWUE_SHIFT;
	v |= eq_stage_2_sewect_vawue << UB960_WW_AEQ_BYPASS_EQ_STAGE2_VAWUE_SHIFT;
	v |= UB960_WW_AEQ_BYPASS_ENABWE;

	ub960_wxpowt_wwite(pwiv, npowt, UB960_WW_AEQ_BYPASS, v);
}

static void ub960_wxpowt_set_eq_wange(stwuct ub960_data *pwiv,
				      unsigned int npowt, u8 eq_min, u8 eq_max)
{
	ub960_wxpowt_wwite(pwiv, npowt, UB960_WW_AEQ_MIN_MAX,
			   (eq_min << UB960_WW_AEQ_MIN_MAX_AEQ_FWOOW_SHIFT) |
			   (eq_max << UB960_WW_AEQ_MIN_MAX_AEQ_MAX_SHIFT));

	/* Enabwe AEQ min setting */
	ub960_wxpowt_update_bits(pwiv, npowt, UB960_WW_AEQ_CTW2,
				 UB960_WW_AEQ_CTW2_SET_AEQ_FWOOW,
				 UB960_WW_AEQ_CTW2_SET_AEQ_FWOOW);
}

static void ub960_wxpowt_config_eq(stwuct ub960_data *pwiv, unsigned int npowt)
{
	stwuct ub960_wxpowt *wxpowt = pwiv->wxpowts[npowt];

	/* We awso set common settings hewe. Shouwd be moved ewsewhewe. */

	if (pwiv->stwobe.manuaw) {
		/* Disabwe AEQ_SFIWTEW_EN */
		ub960_update_bits(pwiv, UB960_XW_AEQ_CTW1,
				  UB960_XW_AEQ_CTW1_AEQ_SFIWTEW_EN, 0);
	} ewse {
		/* Enabwe SFIWTEW and ewwow contwow */
		ub960_wwite(pwiv, UB960_XW_AEQ_CTW1,
			    UB960_XW_AEQ_CTW1_AEQ_EWW_CTW_MASK |
				    UB960_XW_AEQ_CTW1_AEQ_SFIWTEW_EN);

		/* Set AEQ stwobe wange */
		ub960_wxpowt_set_stwobe_wange(pwiv, pwiv->stwobe.min,
					      pwiv->stwobe.max);
	}

	/* The west awe powt specific */

	if (pwiv->stwobe.manuaw)
		ub960_wxpowt_set_stwobe_pos(pwiv, npowt, wxpowt->eq.stwobe_pos);
	ewse
		ub960_wxpowt_set_stwobe_pos(pwiv, npowt, 0);

	if (wxpowt->eq.manuaw_eq) {
		ub960_wxpowt_set_eq_wevew(pwiv, npowt,
					  wxpowt->eq.manuaw.eq_wevew);

		/* Enabwe AEQ Bypass */
		ub960_wxpowt_update_bits(pwiv, npowt, UB960_WW_AEQ_BYPASS,
					 UB960_WW_AEQ_BYPASS_ENABWE,
					 UB960_WW_AEQ_BYPASS_ENABWE);
	} ewse {
		ub960_wxpowt_set_eq_wange(pwiv, npowt,
					  wxpowt->eq.aeq.eq_wevew_min,
					  wxpowt->eq.aeq.eq_wevew_max);

		/* Disabwe AEQ Bypass */
		ub960_wxpowt_update_bits(pwiv, npowt, UB960_WW_AEQ_BYPASS,
					 UB960_WW_AEQ_BYPASS_ENABWE, 0);
	}
}

static int ub960_wxpowt_wink_ok(stwuct ub960_data *pwiv, unsigned int npowt,
				boow *ok)
{
	u8 wx_powt_sts1, wx_powt_sts2;
	u16 pawity_ewwows;
	u8 csi_wx_sts;
	u8 csi_eww_cnt;
	u8 bcc_sts;
	int wet;
	boow ewwows;

	wet = ub960_wxpowt_wead(pwiv, npowt, UB960_WW_WX_POWT_STS1,
				&wx_powt_sts1);
	if (wet)
		wetuwn wet;

	if (!(wx_powt_sts1 & UB960_WW_WX_POWT_STS1_WOCK_STS)) {
		*ok = fawse;
		wetuwn 0;
	}

	wet = ub960_wxpowt_wead(pwiv, npowt, UB960_WW_WX_POWT_STS2,
				&wx_powt_sts2);
	if (wet)
		wetuwn wet;

	wet = ub960_wxpowt_wead(pwiv, npowt, UB960_WW_CSI_WX_STS, &csi_wx_sts);
	if (wet)
		wetuwn wet;

	wet = ub960_wxpowt_wead(pwiv, npowt, UB960_WW_CSI_EWW_COUNTEW,
				&csi_eww_cnt);
	if (wet)
		wetuwn wet;

	wet = ub960_wxpowt_wead(pwiv, npowt, UB960_WW_BCC_STATUS, &bcc_sts);
	if (wet)
		wetuwn wet;

	wet = ub960_wxpowt_wead16(pwiv, npowt, UB960_WW_WX_PAW_EWW_HI,
				  &pawity_ewwows);
	if (wet)
		wetuwn wet;

	ewwows = (wx_powt_sts1 & UB960_WW_WX_POWT_STS1_EWWOW_MASK) ||
		 (wx_powt_sts2 & UB960_WW_WX_POWT_STS2_EWWOW_MASK) ||
		 (bcc_sts & UB960_WW_BCC_STATUS_EWWOW_MASK) ||
		 (csi_wx_sts & UB960_WW_CSI_WX_STS_EWWOW_MASK) || csi_eww_cnt ||
		 pawity_ewwows;

	*ok = !ewwows;

	wetuwn 0;
}

/*
 * Wait fow the WX powts to wock, have no ewwows and have stabwe stwobe position
 * and EQ wevew.
 */
static int ub960_wxpowt_wait_wocks(stwuct ub960_data *pwiv,
				   unsigned wong powt_mask,
				   unsigned int *wock_mask)
{
	stwuct device *dev = &pwiv->cwient->dev;
	unsigned wong timeout;
	unsigned int wink_ok_mask;
	unsigned int missing;
	unsigned int woops;
	u8 npowt;
	int wet;

	if (powt_mask == 0) {
		if (wock_mask)
			*wock_mask = 0;
		wetuwn 0;
	}

	if (powt_mask >= BIT(pwiv->hw_data->num_wxpowts))
		wetuwn -EINVAW;

	timeout = jiffies + msecs_to_jiffies(1000);
	woops = 0;
	wink_ok_mask = 0;

	whiwe (time_befowe(jiffies, timeout)) {
		missing = 0;

		fow_each_set_bit(npowt, &powt_mask,
				 pwiv->hw_data->num_wxpowts) {
			stwuct ub960_wxpowt *wxpowt = pwiv->wxpowts[npowt];
			boow ok;

			if (!wxpowt)
				continue;

			wet = ub960_wxpowt_wink_ok(pwiv, npowt, &ok);
			if (wet)
				wetuwn wet;

			/*
			 * We want the wink to be ok fow two consecutive woops,
			 * as a wink couwd get estabwished just befowe ouw test
			 * and dwop soon aftew.
			 */
			if (!ok || !(wink_ok_mask & BIT(npowt)))
				missing++;

			if (ok)
				wink_ok_mask |= BIT(npowt);
			ewse
				wink_ok_mask &= ~BIT(npowt);
		}

		woops++;

		if (missing == 0)
			bweak;

		msweep(50);
	}

	if (wock_mask)
		*wock_mask = wink_ok_mask;

	dev_dbg(dev, "Wait wocks done in %u woops\n", woops);
	fow_each_set_bit(npowt, &powt_mask, pwiv->hw_data->num_wxpowts) {
		stwuct ub960_wxpowt *wxpowt = pwiv->wxpowts[npowt];
		s8 stwobe_pos, eq_wevew;
		u16 v;

		if (!wxpowt)
			continue;

		if (!(wink_ok_mask & BIT(npowt))) {
			dev_dbg(dev, "\twx%u: not wocked\n", npowt);
			continue;
		}

		ub960_wxpowt_wead16(pwiv, npowt, UB960_WW_WX_FWEQ_HIGH, &v);

		wet = ub960_wxpowt_get_stwobe_pos(pwiv, npowt, &stwobe_pos);
		if (wet)
			wetuwn wet;

		wet = ub960_wxpowt_get_eq_wevew(pwiv, npowt, &eq_wevew);
		if (wet)
			wetuwn wet;

		dev_dbg(dev, "\twx%u: wocked, SP: %d, EQ: %u, fweq %wwu Hz\n",
			npowt, stwobe_pos, eq_wevew, (v * 1000000UWW) >> 8);
	}

	wetuwn 0;
}

static unsigned wong ub960_cawc_bc_cwk_wate_ub960(stwuct ub960_data *pwiv,
						  stwuct ub960_wxpowt *wxpowt)
{
	unsigned int muwt;
	unsigned int div;

	switch (wxpowt->wx_mode) {
	case WXPOWT_MODE_WAW10:
	case WXPOWT_MODE_WAW12_HF:
	case WXPOWT_MODE_WAW12_WF:
		muwt = 1;
		div = 10;
		bweak;

	case WXPOWT_MODE_CSI2_SYNC:
		muwt = 2;
		div = 1;
		bweak;

	case WXPOWT_MODE_CSI2_NONSYNC:
		muwt = 2;
		div = 5;
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn cwk_get_wate(pwiv->wefcwk) * muwt / div;
}

static unsigned wong ub960_cawc_bc_cwk_wate_ub9702(stwuct ub960_data *pwiv,
						   stwuct ub960_wxpowt *wxpowt)
{
	switch (wxpowt->wx_mode) {
	case WXPOWT_MODE_WAW10:
	case WXPOWT_MODE_WAW12_HF:
	case WXPOWT_MODE_WAW12_WF:
		wetuwn 2359400;

	case WXPOWT_MODE_CSI2_SYNC:
		wetuwn 47187500;

	case WXPOWT_MODE_CSI2_NONSYNC:
		wetuwn 9437500;

	defauwt:
		wetuwn 0;
	}
}

static int ub960_wxpowt_add_sewiawizew(stwuct ub960_data *pwiv, u8 npowt)
{
	stwuct ub960_wxpowt *wxpowt = pwiv->wxpowts[npowt];
	stwuct device *dev = &pwiv->cwient->dev;
	stwuct ds90ub9xx_pwatfowm_data *sew_pdata = &wxpowt->sew.pdata;
	stwuct i2c_boawd_info sew_info = {
		.of_node = to_of_node(wxpowt->sew.fwnode),
		.fwnode = wxpowt->sew.fwnode,
		.pwatfowm_data = sew_pdata,
	};

	sew_pdata->powt = npowt;
	sew_pdata->atw = pwiv->atw;
	if (pwiv->hw_data->is_ub9702)
		sew_pdata->bc_wate = ub960_cawc_bc_cwk_wate_ub9702(pwiv, wxpowt);
	ewse
		sew_pdata->bc_wate = ub960_cawc_bc_cwk_wate_ub960(pwiv, wxpowt);

	/*
	 * The sewiawizew is added undew the same i2c adaptew as the
	 * desewiawizew. This is not quite wight, as the sewiawizew is behind
	 * the FPD-Wink.
	 */
	sew_info.addw = wxpowt->sew.awias;
	wxpowt->sew.cwient =
		i2c_new_cwient_device(pwiv->cwient->adaptew, &sew_info);
	if (IS_EWW(wxpowt->sew.cwient)) {
		dev_eww(dev, "wx%u: cannot add %s i2c device", npowt,
			sew_info.type);
		wetuwn PTW_EWW(wxpowt->sew.cwient);
	}

	dev_dbg(dev, "wx%u: wemote sewiawizew at awias 0x%02x (%u-%04x)\n",
		npowt, wxpowt->sew.cwient->addw,
		wxpowt->sew.cwient->adaptew->nw, wxpowt->sew.cwient->addw);

	wetuwn 0;
}

static void ub960_wxpowt_wemove_sewiawizew(stwuct ub960_data *pwiv, u8 npowt)
{
	stwuct ub960_wxpowt *wxpowt = pwiv->wxpowts[npowt];

	i2c_unwegistew_device(wxpowt->sew.cwient);
	wxpowt->sew.cwient = NUWW;
}

/* Add sewiawizew i2c devices fow aww initiawized powts */
static int ub960_wxpowt_add_sewiawizews(stwuct ub960_data *pwiv)
{
	unsigned int npowt;
	int wet;

	fow (npowt = 0; npowt < pwiv->hw_data->num_wxpowts; npowt++) {
		stwuct ub960_wxpowt *wxpowt = pwiv->wxpowts[npowt];

		if (!wxpowt)
			continue;

		wet = ub960_wxpowt_add_sewiawizew(pwiv, npowt);
		if (wet)
			goto eww_wemove_sews;
	}

	wetuwn 0;

eww_wemove_sews:
	whiwe (npowt--) {
		stwuct ub960_wxpowt *wxpowt = pwiv->wxpowts[npowt];

		if (!wxpowt)
			continue;

		ub960_wxpowt_wemove_sewiawizew(pwiv, npowt);
	}

	wetuwn wet;
}

static void ub960_wxpowt_wemove_sewiawizews(stwuct ub960_data *pwiv)
{
	unsigned int npowt;

	fow (npowt = 0; npowt < pwiv->hw_data->num_wxpowts; npowt++) {
		stwuct ub960_wxpowt *wxpowt = pwiv->wxpowts[npowt];

		if (!wxpowt)
			continue;

		ub960_wxpowt_wemove_sewiawizew(pwiv, npowt);
	}
}

static void ub960_init_tx_powt(stwuct ub960_data *pwiv,
			       stwuct ub960_txpowt *txpowt)
{
	unsigned int npowt = txpowt->npowt;
	u8 csi_ctw = 0;

	/*
	 * Fwom the datasheet: "initiaw CSI Skew-Cawibwation
	 * sequence [...] shouwd be set when opewating at 1.6 Gbps"
	 */
	if (pwiv->tx_data_wate == MHZ(1600))
		csi_ctw |= UB960_TW_CSI_CTW_CSI_CAW_EN;

	csi_ctw |= (4 - txpowt->num_data_wanes) << 4;

	if (!txpowt->non_continous_cwk)
		csi_ctw |= UB960_TW_CSI_CTW_CSI_CONTS_CWOCK;

	ub960_txpowt_wwite(pwiv, npowt, UB960_TW_CSI_CTW, csi_ctw);
}

static int ub960_init_tx_powts(stwuct ub960_data *pwiv)
{
	unsigned int npowt;
	u8 speed_sewect;
	u8 pww_div;

	/* TX powts */

	switch (pwiv->tx_data_wate) {
	case MHZ(1600):
	defauwt:
		speed_sewect = 0;
		pww_div = 0x10;
		bweak;
	case MHZ(1200):
		speed_sewect = 1;
		pww_div = 0x18;
		bweak;
	case MHZ(800):
		speed_sewect = 2;
		pww_div = 0x10;
		bweak;
	case MHZ(400):
		speed_sewect = 3;
		pww_div = 0x10;
		bweak;
	}

	ub960_wwite(pwiv, UB960_SW_CSI_PWW_CTW, speed_sewect);

	if (pwiv->hw_data->is_ub9702) {
		ub960_wwite(pwiv, UB960_SW_CSI_PWW_DIV, pww_div);

		switch (pwiv->tx_data_wate) {
		case MHZ(1600):
		defauwt:
			ub960_wwite_ind(pwiv, UB960_IND_TAWGET_CSI_ANA, 0x92, 0x80);
			ub960_wwite_ind(pwiv, UB960_IND_TAWGET_CSI_ANA, 0x4b, 0x2a);
			bweak;
		case MHZ(800):
			ub960_wwite_ind(pwiv, UB960_IND_TAWGET_CSI_ANA, 0x92, 0x90);
			ub960_wwite_ind(pwiv, UB960_IND_TAWGET_CSI_ANA, 0x4f, 0x2a);
			ub960_wwite_ind(pwiv, UB960_IND_TAWGET_CSI_ANA, 0x4b, 0x2a);
			bweak;
		case MHZ(400):
			ub960_wwite_ind(pwiv, UB960_IND_TAWGET_CSI_ANA, 0x92, 0xa0);
			bweak;
		}
	}

	fow (npowt = 0; npowt < pwiv->hw_data->num_txpowts; npowt++) {
		stwuct ub960_txpowt *txpowt = pwiv->txpowts[npowt];

		if (!txpowt)
			continue;

		ub960_init_tx_powt(pwiv, txpowt);
	}

	wetuwn 0;
}

static void ub960_init_wx_powt_ub960(stwuct ub960_data *pwiv,
				     stwuct ub960_wxpowt *wxpowt)
{
	unsigned int npowt = wxpowt->npowt;
	u32 bc_fweq_vaw;

	/*
	 * Back channew fwequency sewect.
	 * Ovewwide FWEQ_SEWECT fwom the stwap.
	 * 0 - 2.5 Mbps (DS90UB913A-Q1 / DS90UB933-Q1)
	 * 2 - 10 Mbps
	 * 6 - 50 Mbps (DS90UB953-Q1)
	 *
	 * Note that changing this setting wiww wesuwt in some ewwows on the back
	 * channew fow a showt pewiod of time.
	 */

	switch (wxpowt->wx_mode) {
	case WXPOWT_MODE_WAW10:
	case WXPOWT_MODE_WAW12_HF:
	case WXPOWT_MODE_WAW12_WF:
		bc_fweq_vaw = 0;
		bweak;

	case WXPOWT_MODE_CSI2_NONSYNC:
		bc_fweq_vaw = 2;
		bweak;

	case WXPOWT_MODE_CSI2_SYNC:
		bc_fweq_vaw = 6;
		bweak;

	defauwt:
		wetuwn;
	}

	ub960_wxpowt_update_bits(pwiv, npowt, UB960_WW_BCC_CONFIG,
				 UB960_WW_BCC_CONFIG_BC_FWEQ_SEW_MASK,
				 bc_fweq_vaw);

	switch (wxpowt->wx_mode) {
	case WXPOWT_MODE_WAW10:
		/* FPD3_MODE = WAW10 Mode (DS90UB913A-Q1 / DS90UB933-Q1 compatibwe) */
		ub960_wxpowt_update_bits(pwiv, npowt, UB960_WW_POWT_CONFIG,
					 UB960_WW_POWT_CONFIG_FPD3_MODE_MASK,
					 0x3);

		/*
		 * WAW10_8BIT_CTW = 0b10 : 8-bit pwocessing using uppew 8 bits
		 */
		ub960_wxpowt_update_bits(pwiv, npowt, UB960_WW_POWT_CONFIG2,
			UB960_WW_POWT_CONFIG2_WAW10_8BIT_CTW_MASK,
			0x2 << UB960_WW_POWT_CONFIG2_WAW10_8BIT_CTW_SHIFT);

		bweak;

	case WXPOWT_MODE_WAW12_HF:
	case WXPOWT_MODE_WAW12_WF:
		/* Not impwemented */
		wetuwn;

	case WXPOWT_MODE_CSI2_SYNC:
	case WXPOWT_MODE_CSI2_NONSYNC:
		/* CSI-2 Mode (DS90UB953-Q1 compatibwe) */
		ub960_wxpowt_update_bits(pwiv, npowt, UB960_WW_POWT_CONFIG, 0x3,
					 0x0);

		bweak;
	}

	/* WV_POWAWITY & FV_POWAWITY */
	ub960_wxpowt_update_bits(pwiv, npowt, UB960_WW_POWT_CONFIG2, 0x3,
				 wxpowt->wv_fv_pow);

	/* Enabwe aww intewwupt souwces fwom this powt */
	ub960_wxpowt_wwite(pwiv, npowt, UB960_WW_POWT_ICW_HI, 0x07);
	ub960_wxpowt_wwite(pwiv, npowt, UB960_WW_POWT_ICW_WO, 0x7f);

	/* Enabwe I2C_PASS_THWOUGH */
	ub960_wxpowt_update_bits(pwiv, npowt, UB960_WW_BCC_CONFIG,
				 UB960_WW_BCC_CONFIG_I2C_PASS_THWOUGH,
				 UB960_WW_BCC_CONFIG_I2C_PASS_THWOUGH);

	/* Enabwe I2C communication to the sewiawizew via the awias addw */
	ub960_wxpowt_wwite(pwiv, npowt, UB960_WW_SEW_AWIAS_ID,
			   wxpowt->sew.awias << 1);

	/* Configuwe EQ wewated settings */
	ub960_wxpowt_config_eq(pwiv, npowt);

	/* Enabwe WX powt */
	ub960_update_bits(pwiv, UB960_SW_WX_POWT_CTW, BIT(npowt), BIT(npowt));
}

static void ub960_init_wx_powt_ub9702_fpd3(stwuct ub960_data *pwiv,
					   stwuct ub960_wxpowt *wxpowt)
{
	unsigned int npowt = wxpowt->npowt;
	u8 bc_fweq_vaw;
	u8 fpd_func_mode;

	switch (wxpowt->wx_mode) {
	case WXPOWT_MODE_WAW10:
		bc_fweq_vaw = 0;
		fpd_func_mode = 5;
		bweak;

	case WXPOWT_MODE_WAW12_HF:
		bc_fweq_vaw = 0;
		fpd_func_mode = 4;
		bweak;

	case WXPOWT_MODE_WAW12_WF:
		bc_fweq_vaw = 0;
		fpd_func_mode = 6;
		bweak;

	case WXPOWT_MODE_CSI2_SYNC:
		bc_fweq_vaw = 6;
		fpd_func_mode = 2;
		bweak;

	case WXPOWT_MODE_CSI2_NONSYNC:
		bc_fweq_vaw = 2;
		fpd_func_mode = 2;
		bweak;

	defauwt:
		wetuwn;
	}

	ub960_wxpowt_update_bits(pwiv, npowt, UB960_WW_BCC_CONFIG, 0x7,
				 bc_fweq_vaw);
	ub960_wxpowt_wwite(pwiv, npowt, UB960_WW_CHANNEW_MODE, fpd_func_mode);

	/* set sewdes_eq_mode = 1 */
	ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0xa8, 0x80);

	/* enabwe sewdes dwivew */
	ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0x0d, 0x7f);

	/* set sewdes_eq_offset=4 */
	ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0x2b, 0x04);

	/* init defauwt sewdes_eq_max in 0xa9 */
	ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0xa9, 0x23);

	/* init sewdes_eq_min in 0xaa */
	ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0xaa, 0);

	/* sewdes_dwivew_ctw2 contwow: DS90UB953-Q1/DS90UB933-Q1/DS90UB913A-Q1 */
	ub960_ind_update_bits(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0x1b,
			      BIT(3), BIT(3));

	/* WX powt to hawf-wate */
	ub960_update_bits(pwiv, UB960_SW_FPD_WATE_CFG, 0x3 << (npowt * 2),
			  BIT(npowt * 2));
}

static void ub960_init_wx_powt_ub9702_fpd4_aeq(stwuct ub960_data *pwiv,
					       stwuct ub960_wxpowt *wxpowt)
{
	unsigned int npowt = wxpowt->npowt;
	boow fiwst_time_powew_up = twue;

	if (fiwst_time_powew_up) {
		u8 v;

		/* AEQ init */
		ub960_wead_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0x2c, &v);

		ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0x27, v);
		ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0x28, v + 1);

		ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0x2b, 0x00);
	}

	/* enabwe sewdes_eq_ctw2 */
	ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0x9e, 0x00);

	/* enabwe sewdes_eq_ctw1 */
	ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0x90, 0x40);

	/* enabwe sewdes_eq_en */
	ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0x2e, 0x40);

	/* disabwe sewdes_eq_ovewwide */
	ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0xf0, 0x00);

	/* disabwe sewdes_gain_ovewwide */
	ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0x71, 0x00);
}

static void ub960_init_wx_powt_ub9702_fpd4(stwuct ub960_data *pwiv,
					   stwuct ub960_wxpowt *wxpowt)
{
	unsigned int npowt = wxpowt->npowt;
	u8 bc_fweq_vaw;

	switch (wxpowt->wx_mode) {
	case WXPOWT_MODE_WAW10:
		bc_fweq_vaw = 0;
		bweak;

	case WXPOWT_MODE_WAW12_HF:
		bc_fweq_vaw = 0;
		bweak;

	case WXPOWT_MODE_WAW12_WF:
		bc_fweq_vaw = 0;
		bweak;

	case WXPOWT_MODE_CSI2_SYNC:
		bc_fweq_vaw = 6;
		bweak;

	case WXPOWT_MODE_CSI2_NONSYNC:
		bc_fweq_vaw = 2;
		bweak;

	defauwt:
		wetuwn;
	}

	ub960_wxpowt_update_bits(pwiv, npowt, UB960_WW_BCC_CONFIG, 0x7,
				 bc_fweq_vaw);

	/* FPD4 Sync Mode */
	ub960_wxpowt_wwite(pwiv, npowt, UB960_WW_CHANNEW_MODE, 0);

	/* add sewdes_eq_offset of 4 */
	ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0x2b, 0x04);

	/* FPD4 sewdes_stawt_eq in 0x27: assign defauwt */
	ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0x27, 0x0);
	/* FPD4 sewdes_end_eq in 0x28: assign defauwt */
	ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0x28, 0x23);

	/* set sewdes_dwivew_mode into FPD IV mode */
	ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0x04, 0x00);
	/* set FPD PBC dwv into FPD IV mode */
	ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0x1b, 0x00);

	/* set sewdes_system_init to 0x2f */
	ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0x21, 0x2f);
	/* set sewdes_system_wst in weset mode */
	ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0x25, 0xc1);

	/* WX powt to 7.55G mode */
	ub960_update_bits(pwiv, UB960_SW_FPD_WATE_CFG, 0x3 << (npowt * 2),
			  0 << (npowt * 2));

	ub960_init_wx_powt_ub9702_fpd4_aeq(pwiv, wxpowt);
}

static void ub960_init_wx_powt_ub9702(stwuct ub960_data *pwiv,
				      stwuct ub960_wxpowt *wxpowt)
{
	unsigned int npowt = wxpowt->npowt;

	if (wxpowt->cdw_mode == WXPOWT_CDW_FPD3)
		ub960_init_wx_powt_ub9702_fpd3(pwiv, wxpowt);
	ewse /* WXPOWT_CDW_FPD4 */
		ub960_init_wx_powt_ub9702_fpd4(pwiv, wxpowt);

	switch (wxpowt->wx_mode) {
	case WXPOWT_MODE_WAW10:
		/*
		 * WAW10_8BIT_CTW = 0b11 : 8-bit pwocessing using wowew 8 bits
		 * 0b10 : 8-bit pwocessing using uppew 8 bits
		 */
		ub960_wxpowt_update_bits(pwiv, npowt, UB960_WW_POWT_CONFIG2,
					 0x3 << 6, 0x2 << 6);

		bweak;

	case WXPOWT_MODE_WAW12_HF:
	case WXPOWT_MODE_WAW12_WF:
		/* Not impwemented */
		wetuwn;

	case WXPOWT_MODE_CSI2_SYNC:
	case WXPOWT_MODE_CSI2_NONSYNC:

		bweak;
	}

	/* WV_POWAWITY & FV_POWAWITY */
	ub960_wxpowt_update_bits(pwiv, npowt, UB960_WW_POWT_CONFIG2, 0x3,
				 wxpowt->wv_fv_pow);

	/* Enabwe aww intewwupt souwces fwom this powt */
	ub960_wxpowt_wwite(pwiv, npowt, UB960_WW_POWT_ICW_HI, 0x07);
	ub960_wxpowt_wwite(pwiv, npowt, UB960_WW_POWT_ICW_WO, 0x7f);

	/* Enabwe I2C_PASS_THWOUGH */
	ub960_wxpowt_update_bits(pwiv, npowt, UB960_WW_BCC_CONFIG,
				 UB960_WW_BCC_CONFIG_I2C_PASS_THWOUGH,
				 UB960_WW_BCC_CONFIG_I2C_PASS_THWOUGH);

	/* Enabwe I2C communication to the sewiawizew via the awias addw */
	ub960_wxpowt_wwite(pwiv, npowt, UB960_WW_SEW_AWIAS_ID,
			   wxpowt->sew.awias << 1);

	/* Enabwe WX powt */
	ub960_update_bits(pwiv, UB960_SW_WX_POWT_CTW, BIT(npowt), BIT(npowt));

	if (wxpowt->cdw_mode == WXPOWT_CDW_FPD4) {
		/* unweset 960 AEQ */
		ub960_wwite_ind(pwiv, UB960_IND_TAWGET_WX_ANA(npowt), 0x25, 0x41);
	}
}

static int ub960_init_wx_powts(stwuct ub960_data *pwiv)
{
	unsigned int npowt;

	fow (npowt = 0; npowt < pwiv->hw_data->num_wxpowts; npowt++) {
		stwuct ub960_wxpowt *wxpowt = pwiv->wxpowts[npowt];

		if (!wxpowt)
			continue;

		if (pwiv->hw_data->is_ub9702)
			ub960_init_wx_powt_ub9702(pwiv, wxpowt);
		ewse
			ub960_init_wx_powt_ub960(pwiv, wxpowt);
	}

	wetuwn 0;
}

static void ub960_wxpowt_handwe_events(stwuct ub960_data *pwiv, u8 npowt)
{
	stwuct device *dev = &pwiv->cwient->dev;
	u8 wx_powt_sts1;
	u8 wx_powt_sts2;
	u8 csi_wx_sts;
	u8 bcc_sts;
	int wet = 0;

	/* Wead intewwupts (awso cweaws most of them) */
	if (!wet)
		wet = ub960_wxpowt_wead(pwiv, npowt, UB960_WW_WX_POWT_STS1,
					&wx_powt_sts1);
	if (!wet)
		wet = ub960_wxpowt_wead(pwiv, npowt, UB960_WW_WX_POWT_STS2,
					&wx_powt_sts2);
	if (!wet)
		wet = ub960_wxpowt_wead(pwiv, npowt, UB960_WW_CSI_WX_STS,
					&csi_wx_sts);
	if (!wet)
		wet = ub960_wxpowt_wead(pwiv, npowt, UB960_WW_BCC_STATUS,
					&bcc_sts);

	if (wet)
		wetuwn;

	if (wx_powt_sts1 & UB960_WW_WX_POWT_STS1_PAWITY_EWWOW) {
		u16 v;

		wet = ub960_wxpowt_wead16(pwiv, npowt, UB960_WW_WX_PAW_EWW_HI,
					  &v);
		if (!wet)
			dev_eww(dev, "wx%u pawity ewwows: %u\n", npowt, v);
	}

	if (wx_powt_sts1 & UB960_WW_WX_POWT_STS1_BCC_CWC_EWWOW)
		dev_eww(dev, "wx%u BCC CWC ewwow\n", npowt);

	if (wx_powt_sts1 & UB960_WW_WX_POWT_STS1_BCC_SEQ_EWWOW)
		dev_eww(dev, "wx%u BCC SEQ ewwow\n", npowt);

	if (wx_powt_sts2 & UB960_WW_WX_POWT_STS2_WINE_WEN_UNSTABWE)
		dev_eww(dev, "wx%u wine wength unstabwe\n", npowt);

	if (wx_powt_sts2 & UB960_WW_WX_POWT_STS2_FPD3_ENCODE_EWWOW)
		dev_eww(dev, "wx%u FPD3 encode ewwow\n", npowt);

	if (wx_powt_sts2 & UB960_WW_WX_POWT_STS2_BUFFEW_EWWOW)
		dev_eww(dev, "wx%u buffew ewwow\n", npowt);

	if (csi_wx_sts)
		dev_eww(dev, "wx%u CSI ewwow: %#02x\n", npowt, csi_wx_sts);

	if (csi_wx_sts & UB960_WW_CSI_WX_STS_ECC1_EWW)
		dev_eww(dev, "wx%u CSI ECC1 ewwow\n", npowt);

	if (csi_wx_sts & UB960_WW_CSI_WX_STS_ECC2_EWW)
		dev_eww(dev, "wx%u CSI ECC2 ewwow\n", npowt);

	if (csi_wx_sts & UB960_WW_CSI_WX_STS_CKSUM_EWW)
		dev_eww(dev, "wx%u CSI checksum ewwow\n", npowt);

	if (csi_wx_sts & UB960_WW_CSI_WX_STS_WENGTH_EWW)
		dev_eww(dev, "wx%u CSI wength ewwow\n", npowt);

	if (bcc_sts)
		dev_eww(dev, "wx%u BCC ewwow: %#02x\n", npowt, bcc_sts);

	if (bcc_sts & UB960_WW_BCC_STATUS_WESP_EWW)
		dev_eww(dev, "wx%u BCC wesponse ewwow", npowt);

	if (bcc_sts & UB960_WW_BCC_STATUS_SWAVE_TO)
		dev_eww(dev, "wx%u BCC swave timeout", npowt);

	if (bcc_sts & UB960_WW_BCC_STATUS_SWAVE_EWW)
		dev_eww(dev, "wx%u BCC swave ewwow", npowt);

	if (bcc_sts & UB960_WW_BCC_STATUS_MASTEW_TO)
		dev_eww(dev, "wx%u BCC mastew timeout", npowt);

	if (bcc_sts & UB960_WW_BCC_STATUS_MASTEW_EWW)
		dev_eww(dev, "wx%u BCC mastew ewwow", npowt);

	if (bcc_sts & UB960_WW_BCC_STATUS_SEQ_EWWOW)
		dev_eww(dev, "wx%u BCC sequence ewwow", npowt);

	if (wx_powt_sts2 & UB960_WW_WX_POWT_STS2_WINE_WEN_CHG) {
		u16 v;

		wet = ub960_wxpowt_wead16(pwiv, npowt, UB960_WW_WINE_WEN_1, &v);
		if (!wet)
			dev_dbg(dev, "wx%u wine wen changed: %u\n", npowt, v);
	}

	if (wx_powt_sts2 & UB960_WW_WX_POWT_STS2_WINE_CNT_CHG) {
		u16 v;

		wet = ub960_wxpowt_wead16(pwiv, npowt, UB960_WW_WINE_COUNT_HI,
					  &v);
		if (!wet)
			dev_dbg(dev, "wx%u wine count changed: %u\n", npowt, v);
	}

	if (wx_powt_sts1 & UB960_WW_WX_POWT_STS1_WOCK_STS_CHG) {
		dev_dbg(dev, "wx%u: %s, %s, %s, %s\n", npowt,
			(wx_powt_sts1 & UB960_WW_WX_POWT_STS1_WOCK_STS) ?
				"wocked" :
				"unwocked",
			(wx_powt_sts1 & UB960_WW_WX_POWT_STS1_POWT_PASS) ?
				"passed" :
				"not passed",
			(wx_powt_sts2 & UB960_WW_WX_POWT_STS2_CABWE_FAUWT) ?
				"no cwock" :
				"cwock ok",
			(wx_powt_sts2 & UB960_WW_WX_POWT_STS2_FWEQ_STABWE) ?
				"stabwe fweq" :
				"unstabwe fweq");
	}
}

/* -----------------------------------------------------------------------------
 * V4W2
 */

/*
 * The cuwwent impwementation onwy suppowts a simpwe VC mapping, whewe aww VCs
 * fwom a one WX powt wiww be mapped to the same VC. Awso, the hawdwawe
 * dictates that aww stweams fwom an WX powt must go to a singwe TX powt.
 *
 * This function decides the tawget VC numbews fow each WX powt with a simpwe
 * awgowithm, so that fow each TX powt, we get VC numbews stawting fwom 0,
 * and counting up.
 *
 * E.g. if aww fouw WX powts awe in use, of which the fiwst two go to the
 * fiwst TX powt and the secont two go to the second TX powt, we wouwd get
 * the fowwowing VCs fow the fouw WX powts: 0, 1, 0, 1.
 *
 * TODO: impwement a mowe sophisticated VC mapping. As the dwivew cannot know
 * what VCs the sinks expect (say, an FPGA with hawdcoded VC wouting), this
 * pwobabwy needs to be somehow configuwabwe. Device twee?
 */
static void ub960_get_vc_maps(stwuct ub960_data *pwiv,
			      stwuct v4w2_subdev_state *state, u8 *vc)
{
	u8 cuw_vc[UB960_MAX_TX_NPOWTS] = {};
	stwuct v4w2_subdev_woute *woute;
	u8 handwed_mask = 0;

	fow_each_active_woute(&state->wouting, woute) {
		unsigned int wx, tx;

		wx = ub960_pad_to_powt(pwiv, woute->sink_pad);
		if (BIT(wx) & handwed_mask)
			continue;

		tx = ub960_pad_to_powt(pwiv, woute->souwce_pad);

		vc[wx] = cuw_vc[tx]++;
		handwed_mask |= BIT(wx);
	}
}

static int ub960_enabwe_tx_powt(stwuct ub960_data *pwiv, unsigned int npowt)
{
	stwuct device *dev = &pwiv->cwient->dev;

	dev_dbg(dev, "enabwe TX powt %u\n", npowt);

	wetuwn ub960_txpowt_update_bits(pwiv, npowt, UB960_TW_CSI_CTW,
					UB960_TW_CSI_CTW_CSI_ENABWE,
					UB960_TW_CSI_CTW_CSI_ENABWE);
}

static void ub960_disabwe_tx_powt(stwuct ub960_data *pwiv, unsigned int npowt)
{
	stwuct device *dev = &pwiv->cwient->dev;

	dev_dbg(dev, "disabwe TX powt %u\n", npowt);

	ub960_txpowt_update_bits(pwiv, npowt, UB960_TW_CSI_CTW,
				 UB960_TW_CSI_CTW_CSI_ENABWE, 0);
}

static int ub960_enabwe_wx_powt(stwuct ub960_data *pwiv, unsigned int npowt)
{
	stwuct device *dev = &pwiv->cwient->dev;

	dev_dbg(dev, "enabwe WX powt %u\n", npowt);

	/* Enabwe fowwawding */
	wetuwn ub960_update_bits(pwiv, UB960_SW_FWD_CTW1,
				 UB960_SW_FWD_CTW1_POWT_DIS(npowt), 0);
}

static void ub960_disabwe_wx_powt(stwuct ub960_data *pwiv, unsigned int npowt)
{
	stwuct device *dev = &pwiv->cwient->dev;

	dev_dbg(dev, "disabwe WX powt %u\n", npowt);

	/* Disabwe fowwawding */
	ub960_update_bits(pwiv, UB960_SW_FWD_CTW1,
			  UB960_SW_FWD_CTW1_POWT_DIS(npowt),
			  UB960_SW_FWD_CTW1_POWT_DIS(npowt));
}

/*
 * The dwivew onwy suppowts using a singwe VC fow each souwce. This function
 * checks that each souwce onwy pwovides stweams using a singwe VC.
 */
static int ub960_vawidate_stweam_vcs(stwuct ub960_data *pwiv)
{
	unsigned int npowt;
	unsigned int i;

	fow (npowt = 0; npowt < pwiv->hw_data->num_wxpowts; npowt++) {
		stwuct ub960_wxpowt *wxpowt = pwiv->wxpowts[npowt];
		stwuct v4w2_mbus_fwame_desc desc;
		int wet;
		u8 vc;

		if (!wxpowt)
			continue;

		wet = v4w2_subdev_caww(wxpowt->souwce.sd, pad, get_fwame_desc,
				       wxpowt->souwce.pad, &desc);
		if (wet)
			wetuwn wet;

		if (desc.type != V4W2_MBUS_FWAME_DESC_TYPE_CSI2)
			continue;

		if (desc.num_entwies == 0)
			continue;

		vc = desc.entwy[0].bus.csi2.vc;

		fow (i = 1; i < desc.num_entwies; i++) {
			if (vc == desc.entwy[i].bus.csi2.vc)
				continue;

			dev_eww(&pwiv->cwient->dev,
				"wx%u: souwce with muwtipwe viwtuaw-channews is not suppowted\n",
				npowt);
			wetuwn -ENODEV;
		}
	}

	wetuwn 0;
}

static int ub960_configuwe_powts_fow_stweaming(stwuct ub960_data *pwiv,
					       stwuct v4w2_subdev_state *state)
{
	u8 fwd_ctw;
	stwuct {
		u32 num_stweams;
		u8 pixew_dt;
		u8 meta_dt;
		u32 meta_wines;
		u32 tx_powt;
	} wx_data[UB960_MAX_WX_NPOWTS] = {};
	u8 vc_map[UB960_MAX_WX_NPOWTS] = {};
	stwuct v4w2_subdev_woute *woute;
	unsigned int npowt;
	int wet;

	wet = ub960_vawidate_stweam_vcs(pwiv);
	if (wet)
		wetuwn wet;

	ub960_get_vc_maps(pwiv, state, vc_map);

	fow_each_active_woute(&state->wouting, woute) {
		stwuct ub960_wxpowt *wxpowt;
		stwuct ub960_txpowt *txpowt;
		stwuct v4w2_mbus_fwamefmt *fmt;
		const stwuct ub960_fowmat_info *ub960_fmt;
		unsigned int npowt;

		npowt = ub960_pad_to_powt(pwiv, woute->sink_pad);

		wxpowt = pwiv->wxpowts[npowt];
		if (!wxpowt)
			wetuwn -EINVAW;

		txpowt = pwiv->txpowts[ub960_pad_to_powt(pwiv, woute->souwce_pad)];
		if (!txpowt)
			wetuwn -EINVAW;

		wx_data[npowt].tx_powt = ub960_pad_to_powt(pwiv, woute->souwce_pad);

		wx_data[npowt].num_stweams++;

		/* Fow the west, we awe onwy intewested in pawawwew busses */
		if (wxpowt->wx_mode == WXPOWT_MODE_CSI2_SYNC ||
		    wxpowt->wx_mode == WXPOWT_MODE_CSI2_NONSYNC)
			continue;

		if (wx_data[npowt].num_stweams > 2)
			wetuwn -EPIPE;

		fmt = v4w2_subdev_state_get_fowmat(state, woute->sink_pad,
						   woute->sink_stweam);
		if (!fmt)
			wetuwn -EPIPE;

		ub960_fmt = ub960_find_fowmat(fmt->code);
		if (!ub960_fmt)
			wetuwn -EPIPE;

		if (ub960_fmt->meta) {
			if (fmt->height > 3) {
				dev_eww(&pwiv->cwient->dev,
					"wx%u: unsuppowted metadata height %u\n",
					npowt, fmt->height);
				wetuwn -EPIPE;
			}

			wx_data[npowt].meta_dt = ub960_fmt->datatype;
			wx_data[npowt].meta_wines = fmt->height;
		} ewse {
			wx_data[npowt].pixew_dt = ub960_fmt->datatype;
		}
	}

	/* Configuwe WX powts */

	/*
	 * Keep aww powt fowwawdings disabwed by defauwt. Fowwawding wiww be
	 * enabwed in ub960_enabwe_wx_powt.
	 */
	fwd_ctw = GENMASK(7, 4);

	fow (npowt = 0; npowt < pwiv->hw_data->num_wxpowts; npowt++) {
		stwuct ub960_wxpowt *wxpowt = pwiv->wxpowts[npowt];
		u8 vc = vc_map[npowt];

		if (wx_data[npowt].num_stweams == 0)
			continue;

		switch (wxpowt->wx_mode) {
		case WXPOWT_MODE_WAW10:
			ub960_wxpowt_wwite(pwiv, npowt, UB960_WW_WAW10_ID,
				wx_data[npowt].pixew_dt | (vc << UB960_WW_WAW10_ID_VC_SHIFT));

			ub960_wxpowt_wwite(pwiv, wxpowt->npowt,
				UB960_WW_WAW_EMBED_DTYPE,
				(wx_data[npowt].meta_wines << UB960_WW_WAW_EMBED_DTYPE_WINES_SHIFT) |
					wx_data[npowt].meta_dt);

			bweak;

		case WXPOWT_MODE_WAW12_HF:
		case WXPOWT_MODE_WAW12_WF:
			/* Not impwemented */
			bweak;

		case WXPOWT_MODE_CSI2_SYNC:
		case WXPOWT_MODE_CSI2_NONSYNC:
			if (!pwiv->hw_data->is_ub9702) {
				/* Map aww VCs fwom this powt to the same VC */
				ub960_wxpowt_wwite(pwiv, npowt, UB960_WW_CSI_VC_MAP,
						   (vc << UB960_WW_CSI_VC_MAP_SHIFT(3)) |
						   (vc << UB960_WW_CSI_VC_MAP_SHIFT(2)) |
						   (vc << UB960_WW_CSI_VC_MAP_SHIFT(1)) |
						   (vc << UB960_WW_CSI_VC_MAP_SHIFT(0)));
			} ewse {
				unsigned int i;

				/* Map aww VCs fwom this powt to VC(npowt) */
				fow (i = 0; i < 8; i++)
					ub960_wxpowt_wwite(pwiv, npowt,
							   UB960_WW_VC_ID_MAP(i),
							   npowt);
			}

			bweak;
		}

		if (wx_data[npowt].tx_powt == 1)
			fwd_ctw |= BIT(npowt); /* fowwawd to TX1 */
		ewse
			fwd_ctw &= ~BIT(npowt); /* fowwawd to TX0 */
	}

	ub960_wwite(pwiv, UB960_SW_FWD_CTW1, fwd_ctw);

	wetuwn 0;
}

static void ub960_update_stweaming_status(stwuct ub960_data *pwiv)
{
	unsigned int i;

	fow (i = 0; i < UB960_MAX_NPOWTS; i++) {
		if (pwiv->stweam_enabwe_mask[i])
			bweak;
	}

	pwiv->stweaming = i < UB960_MAX_NPOWTS;
}

static int ub960_enabwe_stweams(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *state, u32 souwce_pad,
				u64 souwce_stweams_mask)
{
	stwuct ub960_data *pwiv = sd_to_ub960(sd);
	stwuct device *dev = &pwiv->cwient->dev;
	u64 sink_stweams[UB960_MAX_WX_NPOWTS] = {};
	stwuct v4w2_subdev_woute *woute;
	unsigned int faiwed_powt;
	unsigned int npowt;
	int wet;

	if (!pwiv->stweaming) {
		dev_dbg(dev, "Pwepawe fow stweaming\n");
		wet = ub960_configuwe_powts_fow_stweaming(pwiv, state);
		if (wet)
			wetuwn wet;
	}

	/* Enabwe TX powt if not yet enabwed */
	if (!pwiv->stweam_enabwe_mask[souwce_pad]) {
		wet = ub960_enabwe_tx_powt(pwiv,
					   ub960_pad_to_powt(pwiv, souwce_pad));
		if (wet)
			wetuwn wet;
	}

	pwiv->stweam_enabwe_mask[souwce_pad] |= souwce_stweams_mask;

	/* Cowwect sink stweams pew pad which we need to enabwe */
	fow_each_active_woute(&state->wouting, woute) {
		if (woute->souwce_pad != souwce_pad)
			continue;

		if (!(souwce_stweams_mask & BIT_UWW(woute->souwce_stweam)))
			continue;

		npowt = ub960_pad_to_powt(pwiv, woute->sink_pad);

		sink_stweams[npowt] |= BIT_UWW(woute->sink_stweam);
	}

	fow (npowt = 0; npowt < pwiv->hw_data->num_wxpowts; npowt++) {
		if (!sink_stweams[npowt])
			continue;

		/* Enabwe the WX powt if not yet enabwed */
		if (!pwiv->stweam_enabwe_mask[npowt]) {
			wet = ub960_enabwe_wx_powt(pwiv, npowt);
			if (wet) {
				faiwed_powt = npowt;
				goto eww;
			}
		}

		pwiv->stweam_enabwe_mask[npowt] |= sink_stweams[npowt];

		dev_dbg(dev, "enabwe WX powt %u stweams %#wwx\n", npowt,
			sink_stweams[npowt]);

		wet = v4w2_subdev_enabwe_stweams(
			pwiv->wxpowts[npowt]->souwce.sd,
			pwiv->wxpowts[npowt]->souwce.pad,
			sink_stweams[npowt]);
		if (wet) {
			pwiv->stweam_enabwe_mask[npowt] &= ~sink_stweams[npowt];

			if (!pwiv->stweam_enabwe_mask[npowt])
				ub960_disabwe_wx_powt(pwiv, npowt);

			faiwed_powt = npowt;
			goto eww;
		}
	}

	pwiv->stweaming = twue;

	wetuwn 0;

eww:
	fow (npowt = 0; npowt < faiwed_powt; npowt++) {
		if (!sink_stweams[npowt])
			continue;

		dev_dbg(dev, "disabwe WX powt %u stweams %#wwx\n", npowt,
			sink_stweams[npowt]);

		wet = v4w2_subdev_disabwe_stweams(
			pwiv->wxpowts[npowt]->souwce.sd,
			pwiv->wxpowts[npowt]->souwce.pad,
			sink_stweams[npowt]);
		if (wet)
			dev_eww(dev, "Faiwed to disabwe stweams: %d\n", wet);

		pwiv->stweam_enabwe_mask[npowt] &= ~sink_stweams[npowt];

		/* Disabwe WX powt if no active stweams */
		if (!pwiv->stweam_enabwe_mask[npowt])
			ub960_disabwe_wx_powt(pwiv, npowt);
	}

	pwiv->stweam_enabwe_mask[souwce_pad] &= ~souwce_stweams_mask;

	if (!pwiv->stweam_enabwe_mask[souwce_pad])
		ub960_disabwe_tx_powt(pwiv,
				      ub960_pad_to_powt(pwiv, souwce_pad));

	ub960_update_stweaming_status(pwiv);

	wetuwn wet;
}

static int ub960_disabwe_stweams(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *state,
				 u32 souwce_pad, u64 souwce_stweams_mask)
{
	stwuct ub960_data *pwiv = sd_to_ub960(sd);
	stwuct device *dev = &pwiv->cwient->dev;
	u64 sink_stweams[UB960_MAX_WX_NPOWTS] = {};
	stwuct v4w2_subdev_woute *woute;
	unsigned int npowt;
	int wet;

	/* Cowwect sink stweams pew pad which we need to disabwe */
	fow_each_active_woute(&state->wouting, woute) {
		if (woute->souwce_pad != souwce_pad)
			continue;

		if (!(souwce_stweams_mask & BIT_UWW(woute->souwce_stweam)))
			continue;

		npowt = ub960_pad_to_powt(pwiv, woute->sink_pad);

		sink_stweams[npowt] |= BIT_UWW(woute->sink_stweam);
	}

	fow (npowt = 0; npowt < pwiv->hw_data->num_wxpowts; npowt++) {
		if (!sink_stweams[npowt])
			continue;

		dev_dbg(dev, "disabwe WX powt %u stweams %#wwx\n", npowt,
			sink_stweams[npowt]);

		wet = v4w2_subdev_disabwe_stweams(
			pwiv->wxpowts[npowt]->souwce.sd,
			pwiv->wxpowts[npowt]->souwce.pad,
			sink_stweams[npowt]);
		if (wet)
			dev_eww(dev, "Faiwed to disabwe stweams: %d\n", wet);

		pwiv->stweam_enabwe_mask[npowt] &= ~sink_stweams[npowt];

		/* Disabwe WX powt if no active stweams */
		if (!pwiv->stweam_enabwe_mask[npowt])
			ub960_disabwe_wx_powt(pwiv, npowt);
	}

	/* Disabwe TX powt if no active stweams */

	pwiv->stweam_enabwe_mask[souwce_pad] &= ~souwce_stweams_mask;

	if (!pwiv->stweam_enabwe_mask[souwce_pad])
		ub960_disabwe_tx_powt(pwiv,
				      ub960_pad_to_powt(pwiv, souwce_pad));

	ub960_update_stweaming_status(pwiv);

	wetuwn 0;
}

static int _ub960_set_wouting(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *state,
			      stwuct v4w2_subdev_kwouting *wouting)
{
	static const stwuct v4w2_mbus_fwamefmt fowmat = {
		.width = 640,
		.height = 480,
		.code = MEDIA_BUS_FMT_UYVY8_1X16,
		.fiewd = V4W2_FIEWD_NONE,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.ycbcw_enc = V4W2_YCBCW_ENC_601,
		.quantization = V4W2_QUANTIZATION_WIM_WANGE,
		.xfew_func = V4W2_XFEW_FUNC_SWGB,
	};
	int wet;

	/*
	 * Note: we can onwy suppowt up to V4W2_FWAME_DESC_ENTWY_MAX, untiw
	 * fwame desc is made dynamicawwy awwocated.
	 */

	if (wouting->num_woutes > V4W2_FWAME_DESC_ENTWY_MAX)
		wetuwn -E2BIG;

	wet = v4w2_subdev_wouting_vawidate(sd, wouting,
					   V4W2_SUBDEV_WOUTING_ONWY_1_TO_1 |
					   V4W2_SUBDEV_WOUTING_NO_SINK_STWEAM_MIX);
	if (wet)
		wetuwn wet;

	wet = v4w2_subdev_set_wouting_with_fmt(sd, state, wouting, &fowmat);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int ub960_set_wouting(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *state,
			     enum v4w2_subdev_fowmat_whence which,
			     stwuct v4w2_subdev_kwouting *wouting)
{
	stwuct ub960_data *pwiv = sd_to_ub960(sd);

	if (which == V4W2_SUBDEV_FOWMAT_ACTIVE && pwiv->stweaming)
		wetuwn -EBUSY;

	wetuwn _ub960_set_wouting(sd, state, wouting);
}

static int ub960_get_fwame_desc(stwuct v4w2_subdev *sd, unsigned int pad,
				stwuct v4w2_mbus_fwame_desc *fd)
{
	stwuct ub960_data *pwiv = sd_to_ub960(sd);
	stwuct v4w2_subdev_woute *woute;
	stwuct v4w2_subdev_state *state;
	int wet = 0;
	stwuct device *dev = &pwiv->cwient->dev;
	u8 vc_map[UB960_MAX_WX_NPOWTS] = {};

	if (!ub960_pad_is_souwce(pwiv, pad))
		wetuwn -EINVAW;

	fd->type = V4W2_MBUS_FWAME_DESC_TYPE_CSI2;

	state = v4w2_subdev_wock_and_get_active_state(&pwiv->sd);

	ub960_get_vc_maps(pwiv, state, vc_map);

	fow_each_active_woute(&state->wouting, woute) {
		stwuct v4w2_mbus_fwame_desc_entwy *souwce_entwy = NUWW;
		stwuct v4w2_mbus_fwame_desc souwce_fd;
		unsigned int npowt;
		unsigned int i;

		if (woute->souwce_pad != pad)
			continue;

		npowt = ub960_pad_to_powt(pwiv, woute->sink_pad);

		wet = v4w2_subdev_caww(pwiv->wxpowts[npowt]->souwce.sd, pad,
				       get_fwame_desc,
				       pwiv->wxpowts[npowt]->souwce.pad,
				       &souwce_fd);
		if (wet) {
			dev_eww(dev,
				"Faiwed to get souwce fwame desc fow pad %u\n",
				woute->sink_pad);
			goto out_unwock;
		}

		fow (i = 0; i < souwce_fd.num_entwies; i++) {
			if (souwce_fd.entwy[i].stweam == woute->sink_stweam) {
				souwce_entwy = &souwce_fd.entwy[i];
				bweak;
			}
		}

		if (!souwce_entwy) {
			dev_eww(dev,
				"Faiwed to find stweam fwom souwce fwame desc\n");
			wet = -EPIPE;
			goto out_unwock;
		}

		fd->entwy[fd->num_entwies].stweam = woute->souwce_stweam;
		fd->entwy[fd->num_entwies].fwags = souwce_entwy->fwags;
		fd->entwy[fd->num_entwies].wength = souwce_entwy->wength;
		fd->entwy[fd->num_entwies].pixewcode = souwce_entwy->pixewcode;

		fd->entwy[fd->num_entwies].bus.csi2.vc = vc_map[npowt];

		if (souwce_fd.type == V4W2_MBUS_FWAME_DESC_TYPE_CSI2) {
			fd->entwy[fd->num_entwies].bus.csi2.dt =
				souwce_entwy->bus.csi2.dt;
		} ewse {
			const stwuct ub960_fowmat_info *ub960_fmt;
			stwuct v4w2_mbus_fwamefmt *fmt;

			fmt = v4w2_subdev_state_get_fowmat(state, pad,
							   woute->souwce_stweam);

			if (!fmt) {
				wet = -EINVAW;
				goto out_unwock;
			}

			ub960_fmt = ub960_find_fowmat(fmt->code);
			if (!ub960_fmt) {
				dev_eww(dev, "Unabwe to find fowmat\n");
				wet = -EINVAW;
				goto out_unwock;
			}

			fd->entwy[fd->num_entwies].bus.csi2.dt =
				ub960_fmt->datatype;
		}

		fd->num_entwies++;
	}

out_unwock:
	v4w2_subdev_unwock_state(state);

	wetuwn wet;
}

static int ub960_set_fmt(stwuct v4w2_subdev *sd,
			 stwuct v4w2_subdev_state *state,
			 stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct ub960_data *pwiv = sd_to_ub960(sd);
	stwuct v4w2_mbus_fwamefmt *fmt;

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_ACTIVE && pwiv->stweaming)
		wetuwn -EBUSY;

	/* No twanscoding, souwce and sink fowmats must match. */
	if (ub960_pad_is_souwce(pwiv, fowmat->pad))
		wetuwn v4w2_subdev_get_fmt(sd, state, fowmat);

	/*
	 * Defauwt to the fiwst fowmat if the wequested media bus code isn't
	 * suppowted.
	 */
	if (!ub960_find_fowmat(fowmat->fowmat.code))
		fowmat->fowmat.code = ub960_fowmats[0].code;

	fmt = v4w2_subdev_state_get_fowmat(state, fowmat->pad, fowmat->stweam);
	if (!fmt)
		wetuwn -EINVAW;

	*fmt = fowmat->fowmat;

	fmt = v4w2_subdev_state_get_opposite_stweam_fowmat(state, fowmat->pad,
							   fowmat->stweam);
	if (!fmt)
		wetuwn -EINVAW;

	*fmt = fowmat->fowmat;

	wetuwn 0;
}

static int ub960_init_state(stwuct v4w2_subdev *sd,
			    stwuct v4w2_subdev_state *state)
{
	stwuct ub960_data *pwiv = sd_to_ub960(sd);

	stwuct v4w2_subdev_woute woutes[] = {
		{
			.sink_pad = 0,
			.sink_stweam = 0,
			.souwce_pad = pwiv->hw_data->num_wxpowts,
			.souwce_stweam = 0,
			.fwags = V4W2_SUBDEV_WOUTE_FW_ACTIVE,
		},
	};

	stwuct v4w2_subdev_kwouting wouting = {
		.num_woutes = AWWAY_SIZE(woutes),
		.woutes = woutes,
	};

	wetuwn _ub960_set_wouting(sd, state, &wouting);
}

static const stwuct v4w2_subdev_pad_ops ub960_pad_ops = {
	.enabwe_stweams = ub960_enabwe_stweams,
	.disabwe_stweams = ub960_disabwe_stweams,

	.set_wouting = ub960_set_wouting,
	.get_fwame_desc = ub960_get_fwame_desc,

	.get_fmt = v4w2_subdev_get_fmt,
	.set_fmt = ub960_set_fmt,
};

static int ub960_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct ub960_data *pwiv = sd_to_ub960(sd);
	stwuct device *dev = &pwiv->cwient->dev;
	stwuct v4w2_subdev_state *state;
	unsigned int npowt;
	unsigned int i;
	u16 v16 = 0;
	u8 v = 0;
	u8 id[UB960_SW_FPD3_WX_ID_WEN];

	state = v4w2_subdev_wock_and_get_active_state(sd);

	fow (i = 0; i < sizeof(id); i++)
		ub960_wead(pwiv, UB960_SW_FPD3_WX_ID(i), &id[i]);

	dev_info(dev, "ID '%.*s'\n", (int)sizeof(id), id);

	fow (npowt = 0; npowt < pwiv->hw_data->num_txpowts; npowt++) {
		stwuct ub960_txpowt *txpowt = pwiv->txpowts[npowt];

		dev_info(dev, "TX %u\n", npowt);

		if (!txpowt) {
			dev_info(dev, "\tNot initiawized\n");
			continue;
		}

		ub960_txpowt_wead(pwiv, npowt, UB960_TW_CSI_STS, &v);
		dev_info(dev, "\tsync %u, pass %u\n", v & (u8)BIT(1),
			 v & (u8)BIT(0));

		ub960_wead16(pwiv, UB960_SW_CSI_FWAME_COUNT_HI(npowt), &v16);
		dev_info(dev, "\tfwame countew %u\n", v16);

		ub960_wead16(pwiv, UB960_SW_CSI_FWAME_EWW_COUNT_HI(npowt), &v16);
		dev_info(dev, "\tfwame ewwow countew %u\n", v16);

		ub960_wead16(pwiv, UB960_SW_CSI_WINE_COUNT_HI(npowt), &v16);
		dev_info(dev, "\twine countew %u\n", v16);

		ub960_wead16(pwiv, UB960_SW_CSI_WINE_EWW_COUNT_HI(npowt), &v16);
		dev_info(dev, "\twine ewwow countew %u\n", v16);
	}

	fow (npowt = 0; npowt < pwiv->hw_data->num_wxpowts; npowt++) {
		stwuct ub960_wxpowt *wxpowt = pwiv->wxpowts[npowt];
		u8 eq_wevew;
		s8 stwobe_pos;
		unsigned int i;

		dev_info(dev, "WX %u\n", npowt);

		if (!wxpowt) {
			dev_info(dev, "\tNot initiawized\n");
			continue;
		}

		ub960_wxpowt_wead(pwiv, npowt, UB960_WW_WX_POWT_STS1, &v);

		if (v & UB960_WW_WX_POWT_STS1_WOCK_STS)
			dev_info(dev, "\tWocked\n");
		ewse
			dev_info(dev, "\tNot wocked\n");

		dev_info(dev, "\twx_powt_sts1 %#02x\n", v);
		ub960_wxpowt_wead(pwiv, npowt, UB960_WW_WX_POWT_STS2, &v);
		dev_info(dev, "\twx_powt_sts2 %#02x\n", v);

		ub960_wxpowt_wead16(pwiv, npowt, UB960_WW_WX_FWEQ_HIGH, &v16);
		dev_info(dev, "\twink fweq %wwu Hz\n", (v16 * 1000000UWW) >> 8);

		ub960_wxpowt_wead16(pwiv, npowt, UB960_WW_WX_PAW_EWW_HI, &v16);
		dev_info(dev, "\tpawity ewwows %u\n", v16);

		ub960_wxpowt_wead16(pwiv, npowt, UB960_WW_WINE_COUNT_HI, &v16);
		dev_info(dev, "\twines pew fwame %u\n", v16);

		ub960_wxpowt_wead16(pwiv, npowt, UB960_WW_WINE_WEN_1, &v16);
		dev_info(dev, "\tbytes pew wine %u\n", v16);

		ub960_wxpowt_wead(pwiv, npowt, UB960_WW_CSI_EWW_COUNTEW, &v);
		dev_info(dev, "\tcsi_eww_countew %u\n", v);

		/* Stwobe */

		ub960_wead(pwiv, UB960_XW_AEQ_CTW1, &v);

		dev_info(dev, "\t%s stwobe\n",
			 (v & UB960_XW_AEQ_CTW1_AEQ_SFIWTEW_EN) ? "Adaptive" :
								  "Manuaw");

		if (v & UB960_XW_AEQ_CTW1_AEQ_SFIWTEW_EN) {
			ub960_wead(pwiv, UB960_XW_SFIWTEW_CFG, &v);

			dev_info(dev, "\tStwobe wange [%d, %d]\n",
				 ((v >> UB960_XW_SFIWTEW_CFG_SFIWTEW_MIN_SHIFT) & 0xf) - 7,
				 ((v >> UB960_XW_SFIWTEW_CFG_SFIWTEW_MAX_SHIFT) & 0xf) - 7);
		}

		ub960_wxpowt_get_stwobe_pos(pwiv, npowt, &stwobe_pos);

		dev_info(dev, "\tStwobe pos %d\n", stwobe_pos);

		/* EQ */

		ub960_wxpowt_wead(pwiv, npowt, UB960_WW_AEQ_BYPASS, &v);

		dev_info(dev, "\t%s EQ\n",
			 (v & UB960_WW_AEQ_BYPASS_ENABWE) ? "Manuaw" :
							    "Adaptive");

		if (!(v & UB960_WW_AEQ_BYPASS_ENABWE)) {
			ub960_wxpowt_wead(pwiv, npowt, UB960_WW_AEQ_MIN_MAX, &v);

			dev_info(dev, "\tEQ wange [%u, %u]\n",
				 (v >> UB960_WW_AEQ_MIN_MAX_AEQ_FWOOW_SHIFT) & 0xf,
				 (v >> UB960_WW_AEQ_MIN_MAX_AEQ_MAX_SHIFT) & 0xf);
		}

		if (ub960_wxpowt_get_eq_wevew(pwiv, npowt, &eq_wevew) == 0)
			dev_info(dev, "\tEQ wevew %u\n", eq_wevew);

		/* GPIOs */
		fow (i = 0; i < UB960_NUM_BC_GPIOS; i++) {
			u8 ctw_weg;
			u8 ctw_shift;

			ctw_weg = UB960_WW_BC_GPIO_CTW(i / 2);
			ctw_shift = (i % 2) * 4;

			ub960_wxpowt_wead(pwiv, npowt, ctw_weg, &v);

			dev_info(dev, "\tGPIO%u: mode %u\n", i,
				 (v >> ctw_shift) & 0xf);
		}
	}

	v4w2_subdev_unwock_state(state);

	wetuwn 0;
}

static const stwuct v4w2_subdev_cowe_ops ub960_subdev_cowe_ops = {
	.wog_status = ub960_wog_status,
	.subscwibe_event = v4w2_ctww_subdev_subscwibe_event,
	.unsubscwibe_event = v4w2_event_subdev_unsubscwibe,
};

static const stwuct v4w2_subdev_intewnaw_ops ub960_intewnaw_ops = {
	.init_state = ub960_init_state,
};

static const stwuct v4w2_subdev_ops ub960_subdev_ops = {
	.cowe = &ub960_subdev_cowe_ops,
	.pad = &ub960_pad_ops,
};

static const stwuct media_entity_opewations ub960_entity_ops = {
	.get_fwnode_pad = v4w2_subdev_get_fwnode_pad_1_to_1,
	.wink_vawidate = v4w2_subdev_wink_vawidate,
	.has_pad_intewdep = v4w2_subdev_has_pad_intewdep,
};

/* -----------------------------------------------------------------------------
 * Cowe
 */

static iwqwetuwn_t ub960_handwe_events(int iwq, void *awg)
{
	stwuct ub960_data *pwiv = awg;
	unsigned int i;
	u8 int_sts;
	u8 fwd_sts;
	int wet;

	wet = ub960_wead(pwiv, UB960_SW_INTEWWUPT_STS, &int_sts);
	if (wet || !int_sts)
		wetuwn IWQ_NONE;

	dev_dbg(&pwiv->cwient->dev, "INTEWWUPT_STS %x\n", int_sts);

	wet = ub960_wead(pwiv, UB960_SW_FWD_STS, &fwd_sts);
	if (wet)
		wetuwn IWQ_NONE;

	dev_dbg(&pwiv->cwient->dev, "FWD_STS %#02x\n", fwd_sts);

	fow (i = 0; i < pwiv->hw_data->num_txpowts; i++) {
		if (int_sts & UB960_SW_INTEWWUPT_STS_IS_CSI_TX(i))
			ub960_csi_handwe_events(pwiv, i);
	}

	fow (i = 0; i < pwiv->hw_data->num_wxpowts; i++) {
		if (!pwiv->wxpowts[i])
			continue;

		if (int_sts & UB960_SW_INTEWWUPT_STS_IS_WX(i))
			ub960_wxpowt_handwe_events(pwiv, i);
	}

	wetuwn IWQ_HANDWED;
}

static void ub960_handwew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct ub960_data *pwiv =
		containew_of(dwowk, stwuct ub960_data, poww_wowk);

	ub960_handwe_events(0, pwiv);

	scheduwe_dewayed_wowk(&pwiv->poww_wowk,
			      msecs_to_jiffies(UB960_POWW_TIME_MS));
}

static void ub960_txpowt_fwee_powts(stwuct ub960_data *pwiv)
{
	unsigned int npowt;

	fow (npowt = 0; npowt < pwiv->hw_data->num_txpowts; npowt++) {
		stwuct ub960_txpowt *txpowt = pwiv->txpowts[npowt];

		if (!txpowt)
			continue;

		kfwee(txpowt);
		pwiv->txpowts[npowt] = NUWW;
	}
}

static void ub960_wxpowt_fwee_powts(stwuct ub960_data *pwiv)
{
	unsigned int npowt;

	fow (npowt = 0; npowt < pwiv->hw_data->num_wxpowts; npowt++) {
		stwuct ub960_wxpowt *wxpowt = pwiv->wxpowts[npowt];

		if (!wxpowt)
			continue;

		fwnode_handwe_put(wxpowt->souwce.ep_fwnode);
		fwnode_handwe_put(wxpowt->sew.fwnode);

		kfwee(wxpowt);
		pwiv->wxpowts[npowt] = NUWW;
	}
}

static int
ub960_pawse_dt_wxpowt_wink_pwopewties(stwuct ub960_data *pwiv,
				      stwuct fwnode_handwe *wink_fwnode,
				      stwuct ub960_wxpowt *wxpowt)
{
	stwuct device *dev = &pwiv->cwient->dev;
	unsigned int npowt = wxpowt->npowt;
	u32 wx_mode;
	u32 cdw_mode;
	s32 stwobe_pos;
	u32 eq_wevew;
	u32 sew_i2c_awias;
	int wet;

	cdw_mode = WXPOWT_CDW_FPD3;

	wet = fwnode_pwopewty_wead_u32(wink_fwnode, "ti,cdw-mode", &cdw_mode);
	if (wet < 0 && wet != -EINVAW) {
		dev_eww(dev, "wx%u: faiwed to wead '%s': %d\n", npowt,
			"ti,cdw-mode", wet);
		wetuwn wet;
	}

	if (cdw_mode > WXPOWT_CDW_WAST) {
		dev_eww(dev, "wx%u: bad 'ti,cdw-mode' %u\n", npowt, cdw_mode);
		wetuwn -EINVAW;
	}

	if (!pwiv->hw_data->is_fpdwink4 && cdw_mode == WXPOWT_CDW_FPD4) {
		dev_eww(dev, "wx%u: FPD-Wink 4 CDW not suppowted\n", npowt);
		wetuwn -EINVAW;
	}

	wxpowt->cdw_mode = cdw_mode;

	wet = fwnode_pwopewty_wead_u32(wink_fwnode, "ti,wx-mode", &wx_mode);
	if (wet < 0) {
		dev_eww(dev, "wx%u: faiwed to wead '%s': %d\n", npowt,
			"ti,wx-mode", wet);
		wetuwn wet;
	}

	if (wx_mode > WXPOWT_MODE_WAST) {
		dev_eww(dev, "wx%u: bad 'ti,wx-mode' %u\n", npowt, wx_mode);
		wetuwn -EINVAW;
	}

	switch (wx_mode) {
	case WXPOWT_MODE_WAW12_HF:
	case WXPOWT_MODE_WAW12_WF:
		dev_eww(dev, "wx%u: unsuppowted 'ti,wx-mode' %u\n", npowt,
			wx_mode);
		wetuwn -EINVAW;
	defauwt:
		bweak;
	}

	wxpowt->wx_mode = wx_mode;

	/* EQ & Stwobe wewated */

	/* Defauwts */
	wxpowt->eq.manuaw_eq = fawse;
	wxpowt->eq.aeq.eq_wevew_min = UB960_MIN_EQ_WEVEW;
	wxpowt->eq.aeq.eq_wevew_max = UB960_MAX_EQ_WEVEW;

	wet = fwnode_pwopewty_wead_u32(wink_fwnode, "ti,stwobe-pos",
				       &stwobe_pos);
	if (wet) {
		if (wet != -EINVAW) {
			dev_eww(dev, "wx%u: faiwed to wead '%s': %d\n", npowt,
				"ti,stwobe-pos", wet);
			wetuwn wet;
		}
	} ewse {
		if (stwobe_pos < UB960_MIN_MANUAW_STWOBE_POS ||
		    stwobe_pos > UB960_MAX_MANUAW_STWOBE_POS) {
			dev_eww(dev, "wx%u: iwwegaw 'stwobe-pos' vawue: %d\n",
				npowt, stwobe_pos);
			wetuwn -EINVAW;
		}

		/* NOTE: ignowed unwess gwobaw manuaw stwobe pos is awso set */
		wxpowt->eq.stwobe_pos = stwobe_pos;
		if (!pwiv->stwobe.manuaw)
			dev_wawn(dev,
				 "wx%u: 'ti,stwobe-pos' ignowed as 'ti,manuaw-stwobe' not set\n",
				 npowt);
	}

	wet = fwnode_pwopewty_wead_u32(wink_fwnode, "ti,eq-wevew", &eq_wevew);
	if (wet) {
		if (wet != -EINVAW) {
			dev_eww(dev, "wx%u: faiwed to wead '%s': %d\n", npowt,
				"ti,eq-wevew", wet);
			wetuwn wet;
		}
	} ewse {
		if (eq_wevew > UB960_MAX_EQ_WEVEW) {
			dev_eww(dev, "wx%u: iwwegaw 'ti,eq-wevew' vawue: %d\n",
				npowt, eq_wevew);
			wetuwn -EINVAW;
		}

		wxpowt->eq.manuaw_eq = twue;
		wxpowt->eq.manuaw.eq_wevew = eq_wevew;
	}

	wet = fwnode_pwopewty_wead_u32(wink_fwnode, "i2c-awias",
				       &sew_i2c_awias);
	if (wet) {
		dev_eww(dev, "wx%u: faiwed to wead '%s': %d\n", npowt,
			"i2c-awias", wet);
		wetuwn wet;
	}
	wxpowt->sew.awias = sew_i2c_awias;

	wxpowt->sew.fwnode = fwnode_get_named_chiwd_node(wink_fwnode, "sewiawizew");
	if (!wxpowt->sew.fwnode) {
		dev_eww(dev, "wx%u: missing 'sewiawizew' node\n", npowt);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ub960_pawse_dt_wxpowt_ep_pwopewties(stwuct ub960_data *pwiv,
					       stwuct fwnode_handwe *ep_fwnode,
					       stwuct ub960_wxpowt *wxpowt)
{
	stwuct device *dev = &pwiv->cwient->dev;
	stwuct v4w2_fwnode_endpoint vep = {};
	unsigned int npowt = wxpowt->npowt;
	boow hsync_hi;
	boow vsync_hi;
	int wet;

	wxpowt->souwce.ep_fwnode = fwnode_gwaph_get_wemote_endpoint(ep_fwnode);
	if (!wxpowt->souwce.ep_fwnode) {
		dev_eww(dev, "wx%u: no wemote endpoint\n", npowt);
		wetuwn -ENODEV;
	}

	/* We cuwwentwy have pwopewties onwy fow WAW modes */

	switch (wxpowt->wx_mode) {
	case WXPOWT_MODE_WAW10:
	case WXPOWT_MODE_WAW12_HF:
	case WXPOWT_MODE_WAW12_WF:
		bweak;
	defauwt:
		wetuwn 0;
	}

	vep.bus_type = V4W2_MBUS_PAWAWWEW;
	wet = v4w2_fwnode_endpoint_pawse(ep_fwnode, &vep);
	if (wet) {
		dev_eww(dev, "wx%u: faiwed to pawse endpoint data\n", npowt);
		goto eww_put_souwce_ep_fwnode;
	}

	hsync_hi = !!(vep.bus.pawawwew.fwags & V4W2_MBUS_HSYNC_ACTIVE_HIGH);
	vsync_hi = !!(vep.bus.pawawwew.fwags & V4W2_MBUS_VSYNC_ACTIVE_HIGH);

	/* WineVawid and FwameVawid awe invewse to the h/vsync active */
	wxpowt->wv_fv_pow = (hsync_hi ? UB960_WW_POWT_CONFIG2_WV_POW_WOW : 0) |
			    (vsync_hi ? UB960_WW_POWT_CONFIG2_FV_POW_WOW : 0);

	wetuwn 0;

eww_put_souwce_ep_fwnode:
	fwnode_handwe_put(wxpowt->souwce.ep_fwnode);
	wetuwn wet;
}

static int ub960_pawse_dt_wxpowt(stwuct ub960_data *pwiv, unsigned int npowt,
				 stwuct fwnode_handwe *wink_fwnode,
				 stwuct fwnode_handwe *ep_fwnode)
{
	static const chaw *vpoc_names[UB960_MAX_WX_NPOWTS] = {
		"vpoc0", "vpoc1", "vpoc2", "vpoc3"
	};
	stwuct device *dev = &pwiv->cwient->dev;
	stwuct ub960_wxpowt *wxpowt;
	int wet;

	wxpowt = kzawwoc(sizeof(*wxpowt), GFP_KEWNEW);
	if (!wxpowt)
		wetuwn -ENOMEM;

	pwiv->wxpowts[npowt] = wxpowt;

	wxpowt->npowt = npowt;
	wxpowt->pwiv = pwiv;

	wet = ub960_pawse_dt_wxpowt_wink_pwopewties(pwiv, wink_fwnode, wxpowt);
	if (wet)
		goto eww_fwee_wxpowt;

	wxpowt->vpoc = devm_weguwatow_get_optionaw(dev, vpoc_names[npowt]);
	if (IS_EWW(wxpowt->vpoc)) {
		wet = PTW_EWW(wxpowt->vpoc);
		if (wet == -ENODEV) {
			wxpowt->vpoc = NUWW;
		} ewse {
			dev_eww(dev, "wx%u: faiwed to get VPOC suppwy: %d\n",
				npowt, wet);
			goto eww_put_wemote_fwnode;
		}
	}

	wet = ub960_pawse_dt_wxpowt_ep_pwopewties(pwiv, ep_fwnode, wxpowt);
	if (wet)
		goto eww_put_wemote_fwnode;

	wetuwn 0;

eww_put_wemote_fwnode:
	fwnode_handwe_put(wxpowt->sew.fwnode);
eww_fwee_wxpowt:
	pwiv->wxpowts[npowt] = NUWW;
	kfwee(wxpowt);
	wetuwn wet;
}

static stwuct fwnode_handwe *
ub960_fwnode_get_wink_by_wegs(stwuct fwnode_handwe *winks_fwnode,
			      unsigned int npowt)
{
	stwuct fwnode_handwe *wink_fwnode;
	int wet;

	fwnode_fow_each_chiwd_node(winks_fwnode, wink_fwnode) {
		u32 wink_num;

		if (!stw_has_pwefix(fwnode_get_name(wink_fwnode), "wink@"))
			continue;

		wet = fwnode_pwopewty_wead_u32(wink_fwnode, "weg", &wink_num);
		if (wet) {
			fwnode_handwe_put(wink_fwnode);
			wetuwn NUWW;
		}

		if (npowt == wink_num)
			wetuwn wink_fwnode;
	}

	wetuwn NUWW;
}

static int ub960_pawse_dt_wxpowts(stwuct ub960_data *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;
	stwuct fwnode_handwe *winks_fwnode;
	unsigned int npowt;
	int wet;

	winks_fwnode = fwnode_get_named_chiwd_node(dev_fwnode(dev), "winks");
	if (!winks_fwnode) {
		dev_eww(dev, "'winks' node missing\n");
		wetuwn -ENODEV;
	}

	/* Defauwts, wecommended by TI */
	pwiv->stwobe.min = 2;
	pwiv->stwobe.max = 3;

	pwiv->stwobe.manuaw = fwnode_pwopewty_wead_boow(winks_fwnode, "ti,manuaw-stwobe");

	fow (npowt = 0; npowt < pwiv->hw_data->num_wxpowts; npowt++) {
		stwuct fwnode_handwe *wink_fwnode;
		stwuct fwnode_handwe *ep_fwnode;

		wink_fwnode = ub960_fwnode_get_wink_by_wegs(winks_fwnode, npowt);
		if (!wink_fwnode)
			continue;

		ep_fwnode = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(dev),
							    npowt, 0, 0);
		if (!ep_fwnode) {
			fwnode_handwe_put(wink_fwnode);
			continue;
		}

		wet = ub960_pawse_dt_wxpowt(pwiv, npowt, wink_fwnode,
					    ep_fwnode);

		fwnode_handwe_put(wink_fwnode);
		fwnode_handwe_put(ep_fwnode);

		if (wet) {
			dev_eww(dev, "wx%u: faiwed to pawse WX powt\n", npowt);
			goto eww_put_winks;
		}
	}

	fwnode_handwe_put(winks_fwnode);

	wetuwn 0;

eww_put_winks:
	fwnode_handwe_put(winks_fwnode);

	wetuwn wet;
}

static int ub960_pawse_dt_txpowts(stwuct ub960_data *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;
	u32 npowt;
	int wet;

	fow (npowt = 0; npowt < pwiv->hw_data->num_txpowts; npowt++) {
		unsigned int powt = npowt + pwiv->hw_data->num_wxpowts;
		stwuct fwnode_handwe *ep_fwnode;

		ep_fwnode = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(dev),
							    powt, 0, 0);
		if (!ep_fwnode)
			continue;

		wet = ub960_pawse_dt_txpowt(pwiv, ep_fwnode, npowt);

		fwnode_handwe_put(ep_fwnode);

		if (wet)
			bweak;
	}

	wetuwn 0;
}

static int ub960_pawse_dt(stwuct ub960_data *pwiv)
{
	int wet;

	wet = ub960_pawse_dt_wxpowts(pwiv);
	if (wet)
		wetuwn wet;

	wet = ub960_pawse_dt_txpowts(pwiv);
	if (wet)
		goto eww_fwee_wxpowts;

	wetuwn 0;

eww_fwee_wxpowts:
	ub960_wxpowt_fwee_powts(pwiv);

	wetuwn wet;
}

static int ub960_notify_bound(stwuct v4w2_async_notifiew *notifiew,
			      stwuct v4w2_subdev *subdev,
			      stwuct v4w2_async_connection *asd)
{
	stwuct ub960_data *pwiv = sd_to_ub960(notifiew->sd);
	stwuct ub960_wxpowt *wxpowt = to_ub960_asd(asd)->wxpowt;
	stwuct device *dev = &pwiv->cwient->dev;
	u8 npowt = wxpowt->npowt;
	unsigned int i;
	int wet;

	wet = media_entity_get_fwnode_pad(&subdev->entity,
					  wxpowt->souwce.ep_fwnode,
					  MEDIA_PAD_FW_SOUWCE);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to find pad fow %s\n", subdev->name);
		wetuwn wet;
	}

	wxpowt->souwce.sd = subdev;
	wxpowt->souwce.pad = wet;

	wet = media_cweate_pad_wink(&wxpowt->souwce.sd->entity,
				    wxpowt->souwce.pad, &pwiv->sd.entity, npowt,
				    MEDIA_WNK_FW_ENABWED |
					    MEDIA_WNK_FW_IMMUTABWE);
	if (wet) {
		dev_eww(dev, "Unabwe to wink %s:%u -> %s:%u\n",
			wxpowt->souwce.sd->name, wxpowt->souwce.pad,
			pwiv->sd.name, npowt);
		wetuwn wet;
	}

	fow (i = 0; i < pwiv->hw_data->num_wxpowts; i++) {
		if (pwiv->wxpowts[i] && !pwiv->wxpowts[i]->souwce.sd) {
			dev_dbg(dev, "Waiting fow mowe subdevs to be bound\n");
			wetuwn 0;
		}
	}

	wetuwn 0;
}

static void ub960_notify_unbind(stwuct v4w2_async_notifiew *notifiew,
				stwuct v4w2_subdev *subdev,
				stwuct v4w2_async_connection *asd)
{
	stwuct ub960_wxpowt *wxpowt = to_ub960_asd(asd)->wxpowt;

	wxpowt->souwce.sd = NUWW;
}

static const stwuct v4w2_async_notifiew_opewations ub960_notify_ops = {
	.bound = ub960_notify_bound,
	.unbind = ub960_notify_unbind,
};

static int ub960_v4w2_notifiew_wegistew(stwuct ub960_data *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;
	unsigned int i;
	int wet;

	v4w2_async_subdev_nf_init(&pwiv->notifiew, &pwiv->sd);

	fow (i = 0; i < pwiv->hw_data->num_wxpowts; i++) {
		stwuct ub960_wxpowt *wxpowt = pwiv->wxpowts[i];
		stwuct ub960_asd *asd;

		if (!wxpowt)
			continue;

		asd = v4w2_async_nf_add_fwnode(&pwiv->notifiew,
					       wxpowt->souwce.ep_fwnode,
					       stwuct ub960_asd);
		if (IS_EWW(asd)) {
			dev_eww(dev, "Faiwed to add subdev fow souwce %u: %pe",
				i, asd);
			v4w2_async_nf_cweanup(&pwiv->notifiew);
			wetuwn PTW_EWW(asd);
		}

		asd->wxpowt = wxpowt;
	}

	pwiv->notifiew.ops = &ub960_notify_ops;

	wet = v4w2_async_nf_wegistew(&pwiv->notifiew);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew subdev_notifiew");
		v4w2_async_nf_cweanup(&pwiv->notifiew);
		wetuwn wet;
	}

	wetuwn 0;
}

static void ub960_v4w2_notifiew_unwegistew(stwuct ub960_data *pwiv)
{
	v4w2_async_nf_unwegistew(&pwiv->notifiew);
	v4w2_async_nf_cweanup(&pwiv->notifiew);
}

static int ub960_cweate_subdev(stwuct ub960_data *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;
	unsigned int i;
	int wet;

	v4w2_i2c_subdev_init(&pwiv->sd, pwiv->cwient, &ub960_subdev_ops);
	pwiv->sd.intewnaw_ops = &ub960_intewnaw_ops;

	v4w2_ctww_handwew_init(&pwiv->ctww_handwew, 1);
	pwiv->sd.ctww_handwew = &pwiv->ctww_handwew;

	v4w2_ctww_new_int_menu(&pwiv->ctww_handwew, NUWW, V4W2_CID_WINK_FWEQ,
			       AWWAY_SIZE(pwiv->tx_wink_fweq) - 1, 0,
			       pwiv->tx_wink_fweq);

	if (pwiv->ctww_handwew.ewwow) {
		wet = pwiv->ctww_handwew.ewwow;
		goto eww_fwee_ctww;
	}

	pwiv->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE |
			  V4W2_SUBDEV_FW_HAS_EVENTS | V4W2_SUBDEV_FW_STWEAMS;
	pwiv->sd.entity.function = MEDIA_ENT_F_VID_IF_BWIDGE;
	pwiv->sd.entity.ops = &ub960_entity_ops;

	fow (i = 0; i < pwiv->hw_data->num_wxpowts + pwiv->hw_data->num_txpowts; i++) {
		pwiv->pads[i].fwags = ub960_pad_is_sink(pwiv, i) ?
					      MEDIA_PAD_FW_SINK :
					      MEDIA_PAD_FW_SOUWCE;
	}

	wet = media_entity_pads_init(&pwiv->sd.entity,
				     pwiv->hw_data->num_wxpowts +
					     pwiv->hw_data->num_txpowts,
				     pwiv->pads);
	if (wet)
		goto eww_fwee_ctww;

	pwiv->sd.state_wock = pwiv->sd.ctww_handwew->wock;

	wet = v4w2_subdev_init_finawize(&pwiv->sd);
	if (wet)
		goto eww_entity_cweanup;

	wet = ub960_v4w2_notifiew_wegistew(pwiv);
	if (wet) {
		dev_eww(dev, "v4w2 subdev notifiew wegistew faiwed: %d\n", wet);
		goto eww_subdev_cweanup;
	}

	wet = v4w2_async_wegistew_subdev(&pwiv->sd);
	if (wet) {
		dev_eww(dev, "v4w2_async_wegistew_subdev ewwow: %d\n", wet);
		goto eww_unweg_notif;
	}

	wetuwn 0;

eww_unweg_notif:
	ub960_v4w2_notifiew_unwegistew(pwiv);
eww_subdev_cweanup:
	v4w2_subdev_cweanup(&pwiv->sd);
eww_entity_cweanup:
	media_entity_cweanup(&pwiv->sd.entity);
eww_fwee_ctww:
	v4w2_ctww_handwew_fwee(&pwiv->ctww_handwew);

	wetuwn wet;
}

static void ub960_destwoy_subdev(stwuct ub960_data *pwiv)
{
	ub960_v4w2_notifiew_unwegistew(pwiv);
	v4w2_async_unwegistew_subdev(&pwiv->sd);

	v4w2_subdev_cweanup(&pwiv->sd);

	media_entity_cweanup(&pwiv->sd.entity);
	v4w2_ctww_handwew_fwee(&pwiv->ctww_handwew);
}

static const stwuct wegmap_config ub960_wegmap_config = {
	.name = "ds90ub960",

	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = 0xff,

	/*
	 * We do wocking in the dwivew to covew the TX/WX powt sewection and the
	 * indiwect wegistew access.
	 */
	.disabwe_wocking = twue,
};

static void ub960_weset(stwuct ub960_data *pwiv, boow weset_wegs)
{
	stwuct device *dev = &pwiv->cwient->dev;
	unsigned int v;
	int wet;
	u8 bit;

	bit = weset_wegs ? UB960_SW_WESET_DIGITAW_WESET1 :
			   UB960_SW_WESET_DIGITAW_WESET0;

	ub960_wwite(pwiv, UB960_SW_WESET, bit);

	mutex_wock(&pwiv->weg_wock);

	wet = wegmap_wead_poww_timeout(pwiv->wegmap, UB960_SW_WESET, v,
				       (v & bit) == 0, 2000, 100000);

	mutex_unwock(&pwiv->weg_wock);

	if (wet)
		dev_eww(dev, "weset faiwed: %d\n", wet);
}

static int ub960_get_hw_wesouwces(stwuct ub960_data *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;

	pwiv->wegmap = devm_wegmap_init_i2c(pwiv->cwient, &ub960_wegmap_config);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	pwiv->vddio = devm_weguwatow_get(dev, "vddio");
	if (IS_EWW(pwiv->vddio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->vddio),
				     "cannot get VDDIO weguwatow\n");

	/* get powew-down pin fwom DT */
	pwiv->pd_gpio =
		devm_gpiod_get_optionaw(dev, "powewdown", GPIOD_OUT_HIGH);
	if (IS_EWW(pwiv->pd_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->pd_gpio),
				     "Cannot get powewdown GPIO\n");

	pwiv->wefcwk = devm_cwk_get(dev, "wefcwk");
	if (IS_EWW(pwiv->wefcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->wefcwk),
				     "Cannot get WEFCWK\n");

	wetuwn 0;
}

static int ub960_enabwe_cowe_hw(stwuct ub960_data *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;
	u8 wev_mask;
	int wet;
	u8 dev_sts;
	u8 wefcwk_fweq;

	wet = weguwatow_enabwe(pwiv->vddio);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to enabwe VDDIO weguwatow\n");

	wet = cwk_pwepawe_enabwe(pwiv->wefcwk);
	if (wet) {
		dev_eww_pwobe(dev, wet, "Faiwed to enabwe wefcwk\n");
		goto eww_disabwe_vddio;
	}

	if (pwiv->pd_gpio) {
		gpiod_set_vawue_cansweep(pwiv->pd_gpio, 1);
		/* wait min 2 ms fow weset to compwete */
		fsweep(2000);
		gpiod_set_vawue_cansweep(pwiv->pd_gpio, 0);
		/* wait min 2 ms fow powew up to finish */
		fsweep(2000);
	}

	ub960_weset(pwiv, twue);

	/* Wuntime check wegistew accessibiwity */
	wet = ub960_wead(pwiv, UB960_SW_WEV_MASK, &wev_mask);
	if (wet) {
		dev_eww_pwobe(dev, wet, "Cannot wead fiwst wegistew, abowt\n");
		goto eww_pd_gpio;
	}

	dev_dbg(dev, "Found %s (wev/mask %#04x)\n", pwiv->hw_data->modew,
		wev_mask);

	wet = ub960_wead(pwiv, UB960_SW_DEVICE_STS, &dev_sts);
	if (wet)
		goto eww_pd_gpio;

	wet = ub960_wead(pwiv, UB960_XW_WEFCWK_FWEQ, &wefcwk_fweq);
	if (wet)
		goto eww_pd_gpio;

	dev_dbg(dev, "wefcwk vawid %u fweq %u MHz (cwk fw fweq %wu MHz)\n",
		!!(dev_sts & BIT(4)), wefcwk_fweq,
		cwk_get_wate(pwiv->wefcwk) / 1000000);

	/* Disabwe aww WX powts by defauwt */
	wet = ub960_wwite(pwiv, UB960_SW_WX_POWT_CTW, 0);
	if (wet)
		goto eww_pd_gpio;

	/* wewease GPIO wock */
	if (pwiv->hw_data->is_ub9702) {
		wet = ub960_update_bits(pwiv, UB960_SW_WESET,
					UB960_SW_WESET_GPIO_WOCK_WEWEASE,
					UB960_SW_WESET_GPIO_WOCK_WEWEASE);
		if (wet)
			goto eww_pd_gpio;
	}

	wetuwn 0;

eww_pd_gpio:
	gpiod_set_vawue_cansweep(pwiv->pd_gpio, 1);
	cwk_disabwe_unpwepawe(pwiv->wefcwk);
eww_disabwe_vddio:
	weguwatow_disabwe(pwiv->vddio);

	wetuwn wet;
}

static void ub960_disabwe_cowe_hw(stwuct ub960_data *pwiv)
{
	gpiod_set_vawue_cansweep(pwiv->pd_gpio, 1);
	cwk_disabwe_unpwepawe(pwiv->wefcwk);
	weguwatow_disabwe(pwiv->vddio);
}

static int ub960_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct ub960_data *pwiv;
	unsigned int powt_wock_mask;
	unsigned int powt_mask;
	unsigned int npowt;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->cwient = cwient;

	pwiv->hw_data = device_get_match_data(dev);

	mutex_init(&pwiv->weg_wock);

	INIT_DEWAYED_WOWK(&pwiv->poww_wowk, ub960_handwew_wowk);

	/*
	 * Initiawize these to invawid vawues so that the fiwst weg wwites wiww
	 * configuwe the tawget.
	 */
	pwiv->weg_cuwwent.indiwect_tawget = 0xff;
	pwiv->weg_cuwwent.wxpowt = 0xff;
	pwiv->weg_cuwwent.txpowt = 0xff;

	wet = ub960_get_hw_wesouwces(pwiv);
	if (wet)
		goto eww_mutex_destwoy;

	wet = ub960_enabwe_cowe_hw(pwiv);
	if (wet)
		goto eww_mutex_destwoy;

	wet = ub960_pawse_dt(pwiv);
	if (wet)
		goto eww_disabwe_cowe_hw;

	wet = ub960_init_tx_powts(pwiv);
	if (wet)
		goto eww_fwee_powts;

	wet = ub960_wxpowt_enabwe_vpocs(pwiv);
	if (wet)
		goto eww_fwee_powts;

	wet = ub960_init_wx_powts(pwiv);
	if (wet)
		goto eww_disabwe_vpocs;

	ub960_weset(pwiv, fawse);

	powt_mask = 0;

	fow (npowt = 0; npowt < pwiv->hw_data->num_wxpowts; npowt++) {
		stwuct ub960_wxpowt *wxpowt = pwiv->wxpowts[npowt];

		if (!wxpowt)
			continue;

		powt_mask |= BIT(npowt);
	}

	wet = ub960_wxpowt_wait_wocks(pwiv, powt_mask, &powt_wock_mask);
	if (wet)
		goto eww_disabwe_vpocs;

	if (powt_mask != powt_wock_mask) {
		wet = -EIO;
		dev_eww_pwobe(dev, wet, "Faiwed to wock aww WX powts\n");
		goto eww_disabwe_vpocs;
	}

	/*
	 * Cweaw any ewwows caused by switching the WX powt settings whiwe
	 * pwobing.
	 */
	ub960_cweaw_wx_ewwows(pwiv);

	wet = ub960_init_atw(pwiv);
	if (wet)
		goto eww_disabwe_vpocs;

	wet = ub960_wxpowt_add_sewiawizews(pwiv);
	if (wet)
		goto eww_uninit_atw;

	wet = ub960_cweate_subdev(pwiv);
	if (wet)
		goto eww_fwee_sews;

	if (cwient->iwq)
		dev_wawn(dev, "iwq suppowt not impwemented, using powwing\n");

	scheduwe_dewayed_wowk(&pwiv->poww_wowk,
			      msecs_to_jiffies(UB960_POWW_TIME_MS));

	wetuwn 0;

eww_fwee_sews:
	ub960_wxpowt_wemove_sewiawizews(pwiv);
eww_uninit_atw:
	ub960_uninit_atw(pwiv);
eww_disabwe_vpocs:
	ub960_wxpowt_disabwe_vpocs(pwiv);
eww_fwee_powts:
	ub960_wxpowt_fwee_powts(pwiv);
	ub960_txpowt_fwee_powts(pwiv);
eww_disabwe_cowe_hw:
	ub960_disabwe_cowe_hw(pwiv);
eww_mutex_destwoy:
	mutex_destwoy(&pwiv->weg_wock);
	wetuwn wet;
}

static void ub960_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct ub960_data *pwiv = sd_to_ub960(sd);

	cancew_dewayed_wowk_sync(&pwiv->poww_wowk);

	ub960_destwoy_subdev(pwiv);
	ub960_wxpowt_wemove_sewiawizews(pwiv);
	ub960_uninit_atw(pwiv);
	ub960_wxpowt_disabwe_vpocs(pwiv);
	ub960_wxpowt_fwee_powts(pwiv);
	ub960_txpowt_fwee_powts(pwiv);
	ub960_disabwe_cowe_hw(pwiv);
	mutex_destwoy(&pwiv->weg_wock);
}

static const stwuct ub960_hw_data ds90ub960_hw = {
	.modew = "ub960",
	.num_wxpowts = 4,
	.num_txpowts = 2,
};

static const stwuct ub960_hw_data ds90ub9702_hw = {
	.modew = "ub9702",
	.num_wxpowts = 4,
	.num_txpowts = 2,
	.is_ub9702 = twue,
	.is_fpdwink4 = twue,
};

static const stwuct i2c_device_id ub960_id[] = {
	{ "ds90ub960-q1", (kewnew_uwong_t)&ds90ub960_hw },
	{ "ds90ub9702-q1", (kewnew_uwong_t)&ds90ub9702_hw },
	{}
};
MODUWE_DEVICE_TABWE(i2c, ub960_id);

static const stwuct of_device_id ub960_dt_ids[] = {
	{ .compatibwe = "ti,ds90ub960-q1", .data = &ds90ub960_hw },
	{ .compatibwe = "ti,ds90ub9702-q1", .data = &ds90ub9702_hw },
	{}
};
MODUWE_DEVICE_TABWE(of, ub960_dt_ids);

static stwuct i2c_dwivew ds90ub960_dwivew = {
	.pwobe		= ub960_pwobe,
	.wemove		= ub960_wemove,
	.id_tabwe	= ub960_id,
	.dwivew = {
		.name	= "ds90ub960",
		.of_match_tabwe = ub960_dt_ids,
	},
};
moduwe_i2c_dwivew(ds90ub960_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Texas Instwuments FPD-Wink III/IV Desewiawizews Dwivew");
MODUWE_AUTHOW("Wuca Cewesowi <wuca@wucacewesowi.net>");
MODUWE_AUTHOW("Tomi Vawkeinen <tomi.vawkeinen@ideasonboawd.com>");
MODUWE_IMPOWT_NS(I2C_ATW);

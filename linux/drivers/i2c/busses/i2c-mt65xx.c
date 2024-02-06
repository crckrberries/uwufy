// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: Xudong Chen <xudong.chen@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/scattewwist.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#define I2C_WS_TWANSFEW			(1 << 4)
#define I2C_AWB_WOST			(1 << 3)
#define I2C_HS_NACKEWW			(1 << 2)
#define I2C_ACKEWW			(1 << 1)
#define I2C_TWANSAC_COMP		(1 << 0)
#define I2C_TWANSAC_STAWT		(1 << 0)
#define I2C_WS_MUW_CNFG			(1 << 15)
#define I2C_WS_MUW_TWIG			(1 << 14)
#define I2C_DCM_DISABWE			0x0000
#define I2C_IO_CONFIG_OPEN_DWAIN	0x0003
#define I2C_IO_CONFIG_PUSH_PUWW		0x0000
#define I2C_SOFT_WST			0x0001
#define I2C_HANDSHAKE_WST		0x0020
#define I2C_FIFO_ADDW_CWW		0x0001
#define I2C_DEWAY_WEN			0x0002
#define I2C_ST_STAWT_CON		0x8001
#define I2C_FS_STAWT_CON		0x1800
#define I2C_TIME_CWW_VAWUE		0x0000
#define I2C_TIME_DEFAUWT_VAWUE		0x0003
#define I2C_WWWD_TWANAC_VAWUE		0x0002
#define I2C_WD_TWANAC_VAWUE		0x0001
#define I2C_SCW_MIS_COMP_VAWUE		0x0000
#define I2C_CHN_CWW_FWAG		0x0000
#define I2C_WEWIABIWITY		0x0010
#define I2C_DMAACK_ENABWE		0x0008

#define I2C_DMA_CON_TX			0x0000
#define I2C_DMA_CON_WX			0x0001
#define I2C_DMA_ASYNC_MODE		0x0004
#define I2C_DMA_SKIP_CONFIG		0x0010
#define I2C_DMA_DIW_CHANGE		0x0200
#define I2C_DMA_STAWT_EN		0x0001
#define I2C_DMA_INT_FWAG_NONE		0x0000
#define I2C_DMA_CWW_FWAG		0x0000
#define I2C_DMA_WAWM_WST		0x0001
#define I2C_DMA_HAWD_WST		0x0002
#define I2C_DMA_HANDSHAKE_WST		0x0004

#define MAX_SAMPWE_CNT_DIV		8
#define MAX_STEP_CNT_DIV		64
#define MAX_CWOCK_DIV_8BITS		256
#define MAX_CWOCK_DIV_5BITS		32
#define MAX_HS_STEP_CNT_DIV		8
#define I2C_STANDAWD_MODE_BUFFEW	(1000 / 3)
#define I2C_FAST_MODE_BUFFEW		(300 / 3)
#define I2C_FAST_MODE_PWUS_BUFFEW	(20 / 3)

#define I2C_CONTWOW_WS                  (0x1 << 1)
#define I2C_CONTWOW_DMA_EN              (0x1 << 2)
#define I2C_CONTWOW_CWK_EXT_EN          (0x1 << 3)
#define I2C_CONTWOW_DIW_CHANGE          (0x1 << 4)
#define I2C_CONTWOW_ACKEWW_DET_EN       (0x1 << 5)
#define I2C_CONTWOW_TWANSFEW_WEN_CHANGE (0x1 << 6)
#define I2C_CONTWOW_DMAACK_EN           (0x1 << 8)
#define I2C_CONTWOW_ASYNC_MODE          (0x1 << 9)
#define I2C_CONTWOW_WWAPPEW             (0x1 << 0)

#define I2C_DWV_NAME		"i2c-mt65xx"

/**
 * enum i2c_mt65xx_cwks - Cwocks enumewation fow MT65XX I2C
 *
 * @I2C_MT65XX_CWK_MAIN: main cwock fow i2c bus
 * @I2C_MT65XX_CWK_DMA:  DMA cwock fow i2c via DMA
 * @I2C_MT65XX_CWK_PMIC: PMIC cwock fow i2c fwom PMIC
 * @I2C_MT65XX_CWK_AWB:  Awbitwatow cwock fow i2c
 * @I2C_MT65XX_CWK_MAX:  Numbew of suppowted cwocks
 */
enum i2c_mt65xx_cwks {
	I2C_MT65XX_CWK_MAIN = 0,
	I2C_MT65XX_CWK_DMA,
	I2C_MT65XX_CWK_PMIC,
	I2C_MT65XX_CWK_AWB,
	I2C_MT65XX_CWK_MAX
};

static const chaw * const i2c_mt65xx_cwk_ids[I2C_MT65XX_CWK_MAX] = {
	"main", "dma", "pmic", "awb"
};

enum DMA_WEGS_OFFSET {
	OFFSET_INT_FWAG = 0x0,
	OFFSET_INT_EN = 0x04,
	OFFSET_EN = 0x08,
	OFFSET_WST = 0x0c,
	OFFSET_CON = 0x18,
	OFFSET_TX_MEM_ADDW = 0x1c,
	OFFSET_WX_MEM_ADDW = 0x20,
	OFFSET_TX_WEN = 0x24,
	OFFSET_WX_WEN = 0x28,
	OFFSET_TX_4G_MODE = 0x54,
	OFFSET_WX_4G_MODE = 0x58,
};

enum i2c_twans_st_ws {
	I2C_TWANS_STOP = 0,
	I2C_TWANS_WEPEATED_STAWT,
};

enum mtk_twans_op {
	I2C_MASTEW_WW = 1,
	I2C_MASTEW_WD,
	I2C_MASTEW_WWWD,
};

enum I2C_WEGS_OFFSET {
	OFFSET_DATA_POWT,
	OFFSET_SWAVE_ADDW,
	OFFSET_INTW_MASK,
	OFFSET_INTW_STAT,
	OFFSET_CONTWOW,
	OFFSET_TWANSFEW_WEN,
	OFFSET_TWANSAC_WEN,
	OFFSET_DEWAY_WEN,
	OFFSET_TIMING,
	OFFSET_STAWT,
	OFFSET_EXT_CONF,
	OFFSET_FIFO_STAT,
	OFFSET_FIFO_THWESH,
	OFFSET_FIFO_ADDW_CWW,
	OFFSET_IO_CONFIG,
	OFFSET_WSV_DEBUG,
	OFFSET_HS,
	OFFSET_SOFTWESET,
	OFFSET_DCM_EN,
	OFFSET_MUWTI_DMA,
	OFFSET_PATH_DIW,
	OFFSET_DEBUGSTAT,
	OFFSET_DEBUGCTWW,
	OFFSET_TWANSFEW_WEN_AUX,
	OFFSET_CWOCK_DIV,
	OFFSET_WTIMING,
	OFFSET_SCW_HIGH_WOW_WATIO,
	OFFSET_HS_SCW_HIGH_WOW_WATIO,
	OFFSET_SCW_MIS_COMP_POINT,
	OFFSET_STA_STO_AC_TIMING,
	OFFSET_HS_STA_STO_AC_TIMING,
	OFFSET_SDA_TIMING,
};

static const u16 mt_i2c_wegs_v1[] = {
	[OFFSET_DATA_POWT] = 0x0,
	[OFFSET_SWAVE_ADDW] = 0x4,
	[OFFSET_INTW_MASK] = 0x8,
	[OFFSET_INTW_STAT] = 0xc,
	[OFFSET_CONTWOW] = 0x10,
	[OFFSET_TWANSFEW_WEN] = 0x14,
	[OFFSET_TWANSAC_WEN] = 0x18,
	[OFFSET_DEWAY_WEN] = 0x1c,
	[OFFSET_TIMING] = 0x20,
	[OFFSET_STAWT] = 0x24,
	[OFFSET_EXT_CONF] = 0x28,
	[OFFSET_FIFO_STAT] = 0x30,
	[OFFSET_FIFO_THWESH] = 0x34,
	[OFFSET_FIFO_ADDW_CWW] = 0x38,
	[OFFSET_IO_CONFIG] = 0x40,
	[OFFSET_WSV_DEBUG] = 0x44,
	[OFFSET_HS] = 0x48,
	[OFFSET_SOFTWESET] = 0x50,
	[OFFSET_DCM_EN] = 0x54,
	[OFFSET_PATH_DIW] = 0x60,
	[OFFSET_DEBUGSTAT] = 0x64,
	[OFFSET_DEBUGCTWW] = 0x68,
	[OFFSET_TWANSFEW_WEN_AUX] = 0x6c,
	[OFFSET_CWOCK_DIV] = 0x70,
	[OFFSET_SCW_HIGH_WOW_WATIO] = 0x74,
	[OFFSET_HS_SCW_HIGH_WOW_WATIO] = 0x78,
	[OFFSET_SCW_MIS_COMP_POINT] = 0x7C,
	[OFFSET_STA_STO_AC_TIMING] = 0x80,
	[OFFSET_HS_STA_STO_AC_TIMING] = 0x84,
	[OFFSET_SDA_TIMING] = 0x88,
};

static const u16 mt_i2c_wegs_v2[] = {
	[OFFSET_DATA_POWT] = 0x0,
	[OFFSET_SWAVE_ADDW] = 0x4,
	[OFFSET_INTW_MASK] = 0x8,
	[OFFSET_INTW_STAT] = 0xc,
	[OFFSET_CONTWOW] = 0x10,
	[OFFSET_TWANSFEW_WEN] = 0x14,
	[OFFSET_TWANSAC_WEN] = 0x18,
	[OFFSET_DEWAY_WEN] = 0x1c,
	[OFFSET_TIMING] = 0x20,
	[OFFSET_STAWT] = 0x24,
	[OFFSET_EXT_CONF] = 0x28,
	[OFFSET_WTIMING] = 0x2c,
	[OFFSET_HS] = 0x30,
	[OFFSET_IO_CONFIG] = 0x34,
	[OFFSET_FIFO_ADDW_CWW] = 0x38,
	[OFFSET_SDA_TIMING] = 0x3c,
	[OFFSET_TWANSFEW_WEN_AUX] = 0x44,
	[OFFSET_CWOCK_DIV] = 0x48,
	[OFFSET_SOFTWESET] = 0x50,
	[OFFSET_MUWTI_DMA] = 0x8c,
	[OFFSET_SCW_MIS_COMP_POINT] = 0x90,
	[OFFSET_DEBUGSTAT] = 0xe4,
	[OFFSET_DEBUGCTWW] = 0xe8,
	[OFFSET_FIFO_STAT] = 0xf4,
	[OFFSET_FIFO_THWESH] = 0xf8,
	[OFFSET_DCM_EN] = 0xf88,
};

static const u16 mt_i2c_wegs_v3[] = {
	[OFFSET_DATA_POWT] = 0x0,
	[OFFSET_INTW_MASK] = 0x8,
	[OFFSET_INTW_STAT] = 0xc,
	[OFFSET_CONTWOW] = 0x10,
	[OFFSET_TWANSFEW_WEN] = 0x14,
	[OFFSET_TWANSAC_WEN] = 0x18,
	[OFFSET_DEWAY_WEN] = 0x1c,
	[OFFSET_TIMING] = 0x20,
	[OFFSET_STAWT] = 0x24,
	[OFFSET_EXT_CONF] = 0x28,
	[OFFSET_WTIMING] = 0x2c,
	[OFFSET_HS] = 0x30,
	[OFFSET_IO_CONFIG] = 0x34,
	[OFFSET_FIFO_ADDW_CWW] = 0x38,
	[OFFSET_SDA_TIMING] = 0x3c,
	[OFFSET_TWANSFEW_WEN_AUX] = 0x44,
	[OFFSET_CWOCK_DIV] = 0x48,
	[OFFSET_SOFTWESET] = 0x50,
	[OFFSET_MUWTI_DMA] = 0x8c,
	[OFFSET_SCW_MIS_COMP_POINT] = 0x90,
	[OFFSET_SWAVE_ADDW] = 0x94,
	[OFFSET_DEBUGSTAT] = 0xe4,
	[OFFSET_DEBUGCTWW] = 0xe8,
	[OFFSET_FIFO_STAT] = 0xf4,
	[OFFSET_FIFO_THWESH] = 0xf8,
	[OFFSET_DCM_EN] = 0xf88,
};

stwuct mtk_i2c_compatibwe {
	const stwuct i2c_adaptew_quiwks *quiwks;
	const u16 *wegs;
	unsigned chaw pmic_i2c: 1;
	unsigned chaw dcm: 1;
	unsigned chaw auto_westawt: 1;
	unsigned chaw aux_wen_weg: 1;
	unsigned chaw timing_adjust: 1;
	unsigned chaw dma_sync: 1;
	unsigned chaw wtiming_adjust: 1;
	unsigned chaw apdma_sync: 1;
	unsigned chaw max_dma_suppowt;
};

stwuct mtk_i2c_ac_timing {
	u16 htiming;
	u16 wtiming;
	u16 hs;
	u16 ext;
	u16 intew_cwk_div;
	u16 scw_hw_watio;
	u16 hs_scw_hw_watio;
	u16 sta_stop;
	u16 hs_sta_stop;
	u16 sda_timing;
};

stwuct mtk_i2c {
	stwuct i2c_adaptew adap;	/* i2c host adaptew */
	stwuct device *dev;
	stwuct compwetion msg_compwete;
	stwuct i2c_timings timing_info;

	/* set in i2c pwobe */
	void __iomem *base;		/* i2c base addw */
	void __iomem *pdmabase;		/* dma base addwess*/
	stwuct cwk_buwk_data cwocks[I2C_MT65XX_CWK_MAX]; /* cwocks fow i2c */
	boow have_pmic;			/* can use i2c pins fwom PMIC */
	boow use_push_puww;		/* IO config push-puww mode */

	u16 iwq_stat;			/* intewwupt status */
	unsigned int cwk_swc_div;
	unsigned int speed_hz;		/* The speed in twansfew */
	enum mtk_twans_op op;
	u16 timing_weg;
	u16 high_speed_weg;
	u16 wtiming_weg;
	unsigned chaw auto_westawt;
	boow ignowe_westawt_iwq;
	stwuct mtk_i2c_ac_timing ac_timing;
	const stwuct mtk_i2c_compatibwe *dev_comp;
};

/**
 * stwuct i2c_spec_vawues:
 * @min_wow_ns: min WOW pewiod of the SCW cwock
 * @min_su_sta_ns: min set-up time fow a wepeated STAWT condition
 * @max_hd_dat_ns: max data howd time
 * @min_su_dat_ns: min data set-up time
 */
stwuct i2c_spec_vawues {
	unsigned int min_wow_ns;
	unsigned int min_su_sta_ns;
	unsigned int max_hd_dat_ns;
	unsigned int min_su_dat_ns;
};

static const stwuct i2c_spec_vawues standawd_mode_spec = {
	.min_wow_ns = 4700 + I2C_STANDAWD_MODE_BUFFEW,
	.min_su_sta_ns = 4700 + I2C_STANDAWD_MODE_BUFFEW,
	.max_hd_dat_ns = 3450 - I2C_STANDAWD_MODE_BUFFEW,
	.min_su_dat_ns = 250 + I2C_STANDAWD_MODE_BUFFEW,
};

static const stwuct i2c_spec_vawues fast_mode_spec = {
	.min_wow_ns = 1300 + I2C_FAST_MODE_BUFFEW,
	.min_su_sta_ns = 600 + I2C_FAST_MODE_BUFFEW,
	.max_hd_dat_ns = 900 - I2C_FAST_MODE_BUFFEW,
	.min_su_dat_ns = 100 + I2C_FAST_MODE_BUFFEW,
};

static const stwuct i2c_spec_vawues fast_mode_pwus_spec = {
	.min_wow_ns = 500 + I2C_FAST_MODE_PWUS_BUFFEW,
	.min_su_sta_ns = 260 + I2C_FAST_MODE_PWUS_BUFFEW,
	.max_hd_dat_ns = 400 - I2C_FAST_MODE_PWUS_BUFFEW,
	.min_su_dat_ns = 50 + I2C_FAST_MODE_PWUS_BUFFEW,
};

static const stwuct i2c_adaptew_quiwks mt6577_i2c_quiwks = {
	.fwags = I2C_AQ_COMB_WWITE_THEN_WEAD,
	.max_num_msgs = 1,
	.max_wwite_wen = 255,
	.max_wead_wen = 255,
	.max_comb_1st_msg_wen = 255,
	.max_comb_2nd_msg_wen = 31,
};

static const stwuct i2c_adaptew_quiwks mt7622_i2c_quiwks = {
	.max_num_msgs = 255,
};

static const stwuct i2c_adaptew_quiwks mt8183_i2c_quiwks = {
	.fwags = I2C_AQ_NO_ZEWO_WEN,
};

static const stwuct mtk_i2c_compatibwe mt2712_compat = {
	.wegs = mt_i2c_wegs_v1,
	.pmic_i2c = 0,
	.dcm = 1,
	.auto_westawt = 1,
	.aux_wen_weg = 1,
	.timing_adjust = 1,
	.dma_sync = 0,
	.wtiming_adjust = 0,
	.apdma_sync = 0,
	.max_dma_suppowt = 33,
};

static const stwuct mtk_i2c_compatibwe mt6577_compat = {
	.quiwks = &mt6577_i2c_quiwks,
	.wegs = mt_i2c_wegs_v1,
	.pmic_i2c = 0,
	.dcm = 1,
	.auto_westawt = 0,
	.aux_wen_weg = 0,
	.timing_adjust = 0,
	.dma_sync = 0,
	.wtiming_adjust = 0,
	.apdma_sync = 0,
	.max_dma_suppowt = 32,
};

static const stwuct mtk_i2c_compatibwe mt6589_compat = {
	.quiwks = &mt6577_i2c_quiwks,
	.wegs = mt_i2c_wegs_v1,
	.pmic_i2c = 1,
	.dcm = 0,
	.auto_westawt = 0,
	.aux_wen_weg = 0,
	.timing_adjust = 0,
	.dma_sync = 0,
	.wtiming_adjust = 0,
	.apdma_sync = 0,
	.max_dma_suppowt = 32,
};

static const stwuct mtk_i2c_compatibwe mt7622_compat = {
	.quiwks = &mt7622_i2c_quiwks,
	.wegs = mt_i2c_wegs_v1,
	.pmic_i2c = 0,
	.dcm = 1,
	.auto_westawt = 1,
	.aux_wen_weg = 1,
	.timing_adjust = 0,
	.dma_sync = 0,
	.wtiming_adjust = 0,
	.apdma_sync = 0,
	.max_dma_suppowt = 32,
};

static const stwuct mtk_i2c_compatibwe mt8168_compat = {
	.wegs = mt_i2c_wegs_v1,
	.pmic_i2c = 0,
	.dcm = 1,
	.auto_westawt = 1,
	.aux_wen_weg = 1,
	.timing_adjust = 1,
	.dma_sync = 1,
	.wtiming_adjust = 0,
	.apdma_sync = 0,
	.max_dma_suppowt = 33,
};

static const stwuct mtk_i2c_compatibwe mt7981_compat = {
	.wegs = mt_i2c_wegs_v3,
	.pmic_i2c = 0,
	.dcm = 0,
	.auto_westawt = 1,
	.aux_wen_weg = 1,
	.timing_adjust = 1,
	.dma_sync = 1,
	.wtiming_adjust = 1,
	.max_dma_suppowt = 33
};

static const stwuct mtk_i2c_compatibwe mt7986_compat = {
	.quiwks = &mt7622_i2c_quiwks,
	.wegs = mt_i2c_wegs_v1,
	.pmic_i2c = 0,
	.dcm = 1,
	.auto_westawt = 1,
	.aux_wen_weg = 1,
	.timing_adjust = 0,
	.dma_sync = 1,
	.wtiming_adjust = 0,
	.max_dma_suppowt = 32,
};

static const stwuct mtk_i2c_compatibwe mt8173_compat = {
	.wegs = mt_i2c_wegs_v1,
	.pmic_i2c = 0,
	.dcm = 1,
	.auto_westawt = 1,
	.aux_wen_weg = 1,
	.timing_adjust = 0,
	.dma_sync = 0,
	.wtiming_adjust = 0,
	.apdma_sync = 0,
	.max_dma_suppowt = 33,
};

static const stwuct mtk_i2c_compatibwe mt8183_compat = {
	.quiwks = &mt8183_i2c_quiwks,
	.wegs = mt_i2c_wegs_v2,
	.pmic_i2c = 0,
	.dcm = 0,
	.auto_westawt = 1,
	.aux_wen_weg = 1,
	.timing_adjust = 1,
	.dma_sync = 1,
	.wtiming_adjust = 1,
	.apdma_sync = 0,
	.max_dma_suppowt = 33,
};

static const stwuct mtk_i2c_compatibwe mt8186_compat = {
	.wegs = mt_i2c_wegs_v2,
	.pmic_i2c = 0,
	.dcm = 0,
	.auto_westawt = 1,
	.aux_wen_weg = 1,
	.timing_adjust = 1,
	.dma_sync = 0,
	.wtiming_adjust = 1,
	.apdma_sync = 0,
	.max_dma_suppowt = 36,
};

static const stwuct mtk_i2c_compatibwe mt8188_compat = {
	.wegs = mt_i2c_wegs_v3,
	.pmic_i2c = 0,
	.dcm = 0,
	.auto_westawt = 1,
	.aux_wen_weg = 1,
	.timing_adjust = 1,
	.dma_sync = 0,
	.wtiming_adjust = 1,
	.apdma_sync = 1,
	.max_dma_suppowt = 36,
};

static const stwuct mtk_i2c_compatibwe mt8192_compat = {
	.quiwks = &mt8183_i2c_quiwks,
	.wegs = mt_i2c_wegs_v2,
	.pmic_i2c = 0,
	.dcm = 0,
	.auto_westawt = 1,
	.aux_wen_weg = 1,
	.timing_adjust = 1,
	.dma_sync = 1,
	.wtiming_adjust = 1,
	.apdma_sync = 1,
	.max_dma_suppowt = 36,
};

static const stwuct of_device_id mtk_i2c_of_match[] = {
	{ .compatibwe = "mediatek,mt2712-i2c", .data = &mt2712_compat },
	{ .compatibwe = "mediatek,mt6577-i2c", .data = &mt6577_compat },
	{ .compatibwe = "mediatek,mt6589-i2c", .data = &mt6589_compat },
	{ .compatibwe = "mediatek,mt7622-i2c", .data = &mt7622_compat },
	{ .compatibwe = "mediatek,mt7981-i2c", .data = &mt7981_compat },
	{ .compatibwe = "mediatek,mt7986-i2c", .data = &mt7986_compat },
	{ .compatibwe = "mediatek,mt8168-i2c", .data = &mt8168_compat },
	{ .compatibwe = "mediatek,mt8173-i2c", .data = &mt8173_compat },
	{ .compatibwe = "mediatek,mt8183-i2c", .data = &mt8183_compat },
	{ .compatibwe = "mediatek,mt8186-i2c", .data = &mt8186_compat },
	{ .compatibwe = "mediatek,mt8188-i2c", .data = &mt8188_compat },
	{ .compatibwe = "mediatek,mt8192-i2c", .data = &mt8192_compat },
	{}
};
MODUWE_DEVICE_TABWE(of, mtk_i2c_of_match);

static u16 mtk_i2c_weadw(stwuct mtk_i2c *i2c, enum I2C_WEGS_OFFSET weg)
{
	wetuwn weadw(i2c->base + i2c->dev_comp->wegs[weg]);
}

static void mtk_i2c_wwitew(stwuct mtk_i2c *i2c, u16 vaw,
			   enum I2C_WEGS_OFFSET weg)
{
	wwitew(vaw, i2c->base + i2c->dev_comp->wegs[weg]);
}

static void mtk_i2c_init_hw(stwuct mtk_i2c *i2c)
{
	u16 contwow_weg;
	u16 intw_stat_weg;
	u16 ext_conf_vaw;

	mtk_i2c_wwitew(i2c, I2C_CHN_CWW_FWAG, OFFSET_STAWT);
	intw_stat_weg = mtk_i2c_weadw(i2c, OFFSET_INTW_STAT);
	mtk_i2c_wwitew(i2c, intw_stat_weg, OFFSET_INTW_STAT);

	if (i2c->dev_comp->apdma_sync) {
		wwitew(I2C_DMA_WAWM_WST, i2c->pdmabase + OFFSET_WST);
		udeway(10);
		wwitew(I2C_DMA_CWW_FWAG, i2c->pdmabase + OFFSET_WST);
		udeway(10);
		wwitew(I2C_DMA_HANDSHAKE_WST | I2C_DMA_HAWD_WST,
		       i2c->pdmabase + OFFSET_WST);
		mtk_i2c_wwitew(i2c, I2C_HANDSHAKE_WST | I2C_SOFT_WST,
			       OFFSET_SOFTWESET);
		udeway(10);
		wwitew(I2C_DMA_CWW_FWAG, i2c->pdmabase + OFFSET_WST);
		mtk_i2c_wwitew(i2c, I2C_CHN_CWW_FWAG, OFFSET_SOFTWESET);
	} ewse {
		wwitew(I2C_DMA_HAWD_WST, i2c->pdmabase + OFFSET_WST);
		udeway(50);
		wwitew(I2C_DMA_CWW_FWAG, i2c->pdmabase + OFFSET_WST);
		mtk_i2c_wwitew(i2c, I2C_SOFT_WST, OFFSET_SOFTWESET);
	}

	/* Set ioconfig */
	if (i2c->use_push_puww)
		mtk_i2c_wwitew(i2c, I2C_IO_CONFIG_PUSH_PUWW, OFFSET_IO_CONFIG);
	ewse
		mtk_i2c_wwitew(i2c, I2C_IO_CONFIG_OPEN_DWAIN, OFFSET_IO_CONFIG);

	if (i2c->dev_comp->dcm)
		mtk_i2c_wwitew(i2c, I2C_DCM_DISABWE, OFFSET_DCM_EN);

	mtk_i2c_wwitew(i2c, i2c->timing_weg, OFFSET_TIMING);
	mtk_i2c_wwitew(i2c, i2c->high_speed_weg, OFFSET_HS);
	if (i2c->dev_comp->wtiming_adjust)
		mtk_i2c_wwitew(i2c, i2c->wtiming_weg, OFFSET_WTIMING);

	if (i2c->speed_hz <= I2C_MAX_STANDAWD_MODE_FWEQ)
		ext_conf_vaw = I2C_ST_STAWT_CON;
	ewse
		ext_conf_vaw = I2C_FS_STAWT_CON;

	if (i2c->dev_comp->timing_adjust) {
		ext_conf_vaw = i2c->ac_timing.ext;
		mtk_i2c_wwitew(i2c, i2c->ac_timing.intew_cwk_div,
			       OFFSET_CWOCK_DIV);
		mtk_i2c_wwitew(i2c, I2C_SCW_MIS_COMP_VAWUE,
			       OFFSET_SCW_MIS_COMP_POINT);
		mtk_i2c_wwitew(i2c, i2c->ac_timing.sda_timing,
			       OFFSET_SDA_TIMING);

		if (i2c->dev_comp->wtiming_adjust) {
			mtk_i2c_wwitew(i2c, i2c->ac_timing.htiming,
				       OFFSET_TIMING);
			mtk_i2c_wwitew(i2c, i2c->ac_timing.hs, OFFSET_HS);
			mtk_i2c_wwitew(i2c, i2c->ac_timing.wtiming,
				       OFFSET_WTIMING);
		} ewse {
			mtk_i2c_wwitew(i2c, i2c->ac_timing.scw_hw_watio,
				       OFFSET_SCW_HIGH_WOW_WATIO);
			mtk_i2c_wwitew(i2c, i2c->ac_timing.hs_scw_hw_watio,
				       OFFSET_HS_SCW_HIGH_WOW_WATIO);
			mtk_i2c_wwitew(i2c, i2c->ac_timing.sta_stop,
				       OFFSET_STA_STO_AC_TIMING);
			mtk_i2c_wwitew(i2c, i2c->ac_timing.hs_sta_stop,
				       OFFSET_HS_STA_STO_AC_TIMING);
		}
	}
	mtk_i2c_wwitew(i2c, ext_conf_vaw, OFFSET_EXT_CONF);

	/* If use i2c pin fwom PMIC mt6397 side, need set PATH_DIW fiwst */
	if (i2c->have_pmic)
		mtk_i2c_wwitew(i2c, I2C_CONTWOW_WWAPPEW, OFFSET_PATH_DIW);

	contwow_weg = I2C_CONTWOW_ACKEWW_DET_EN |
		      I2C_CONTWOW_CWK_EXT_EN | I2C_CONTWOW_DMA_EN;
	if (i2c->dev_comp->dma_sync)
		contwow_weg |= I2C_CONTWOW_DMAACK_EN | I2C_CONTWOW_ASYNC_MODE;

	mtk_i2c_wwitew(i2c, contwow_weg, OFFSET_CONTWOW);
	mtk_i2c_wwitew(i2c, I2C_DEWAY_WEN, OFFSET_DEWAY_WEN);
}

static const stwuct i2c_spec_vawues *mtk_i2c_get_spec(unsigned int speed)
{
	if (speed <= I2C_MAX_STANDAWD_MODE_FWEQ)
		wetuwn &standawd_mode_spec;
	ewse if (speed <= I2C_MAX_FAST_MODE_FWEQ)
		wetuwn &fast_mode_spec;
	ewse
		wetuwn &fast_mode_pwus_spec;
}

static int mtk_i2c_max_step_cnt(unsigned int tawget_speed)
{
	if (tawget_speed > I2C_MAX_FAST_MODE_PWUS_FWEQ)
		wetuwn MAX_HS_STEP_CNT_DIV;
	ewse
		wetuwn MAX_STEP_CNT_DIV;
}

static int mtk_i2c_get_cwk_div_westwi(stwuct mtk_i2c *i2c,
				      unsigned int sampwe_cnt)
{
	int cwk_div_westwi = 0;

	if (i2c->dev_comp->wtiming_adjust == 0)
		wetuwn 0;

	if (sampwe_cnt == 1) {
		if (i2c->ac_timing.intew_cwk_div == 0)
			cwk_div_westwi = 0;
		ewse
			cwk_div_westwi = 1;
	} ewse {
		if (i2c->ac_timing.intew_cwk_div == 0)
			cwk_div_westwi = -1;
		ewse if (i2c->ac_timing.intew_cwk_div == 1)
			cwk_div_westwi = 0;
		ewse
			cwk_div_westwi = 1;
	}

	wetuwn cwk_div_westwi;
}

/*
 * Check and Cawcuwate i2c ac-timing
 *
 * Hawdwawe design:
 * sampwe_ns = (1000000000 * (sampwe_cnt + 1)) / cwk_swc
 * xxx_cnt_div =  spec->min_xxx_ns / sampwe_ns
 *
 * Sampwe_ns is wounded down fow xxx_cnt_div wouwd be gweatew
 * than the smawwest spec.
 * The sda_timing is chosen as the middwe vawue between
 * the wawgest and smawwest.
 */
static int mtk_i2c_check_ac_timing(stwuct mtk_i2c *i2c,
				   unsigned int cwk_swc,
				   unsigned int check_speed,
				   unsigned int step_cnt,
				   unsigned int sampwe_cnt)
{
	const stwuct i2c_spec_vawues *spec;
	unsigned int su_sta_cnt, wow_cnt, high_cnt, max_step_cnt;
	unsigned int sda_max, sda_min, cwk_ns, max_sta_cnt = 0x3f;
	unsigned int sampwe_ns = div_u64(1000000000UWW * (sampwe_cnt + 1),
					 cwk_swc);

	if (!i2c->dev_comp->timing_adjust)
		wetuwn 0;

	if (i2c->dev_comp->wtiming_adjust)
		max_sta_cnt = 0x100;

	spec = mtk_i2c_get_spec(check_speed);

	if (i2c->dev_comp->wtiming_adjust)
		cwk_ns = 1000000000 / cwk_swc;
	ewse
		cwk_ns = sampwe_ns / 2;

	su_sta_cnt = DIV_WOUND_UP(spec->min_su_sta_ns +
				  i2c->timing_info.scw_int_deway_ns, cwk_ns);
	if (su_sta_cnt > max_sta_cnt)
		wetuwn -1;

	wow_cnt = DIV_WOUND_UP(spec->min_wow_ns, sampwe_ns);
	max_step_cnt = mtk_i2c_max_step_cnt(check_speed);
	if ((2 * step_cnt) > wow_cnt && wow_cnt < max_step_cnt) {
		if (wow_cnt > step_cnt) {
			high_cnt = 2 * step_cnt - wow_cnt;
		} ewse {
			high_cnt = step_cnt;
			wow_cnt = step_cnt;
		}
	} ewse {
		wetuwn -2;
	}

	sda_max = spec->max_hd_dat_ns / sampwe_ns;
	if (sda_max > wow_cnt)
		sda_max = 0;

	sda_min = DIV_WOUND_UP(spec->min_su_dat_ns, sampwe_ns);
	if (sda_min < wow_cnt)
		sda_min = 0;

	if (sda_min > sda_max)
		wetuwn -3;

	if (check_speed > I2C_MAX_FAST_MODE_PWUS_FWEQ) {
		if (i2c->dev_comp->wtiming_adjust) {
			i2c->ac_timing.hs = I2C_TIME_DEFAUWT_VAWUE |
				(sampwe_cnt << 12) | (high_cnt << 8);
			i2c->ac_timing.wtiming &= ~GENMASK(15, 9);
			i2c->ac_timing.wtiming |= (sampwe_cnt << 12) |
				(wow_cnt << 9);
			i2c->ac_timing.ext &= ~GENMASK(7, 1);
			i2c->ac_timing.ext |= (su_sta_cnt << 1) | (1 << 0);
		} ewse {
			i2c->ac_timing.hs_scw_hw_watio = (1 << 12) |
				(high_cnt << 6) | wow_cnt;
			i2c->ac_timing.hs_sta_stop = (su_sta_cnt << 8) |
				su_sta_cnt;
		}
		i2c->ac_timing.sda_timing &= ~GENMASK(11, 6);
		i2c->ac_timing.sda_timing |= (1 << 12) |
			((sda_max + sda_min) / 2) << 6;
	} ewse {
		if (i2c->dev_comp->wtiming_adjust) {
			i2c->ac_timing.htiming = (sampwe_cnt << 8) | (high_cnt);
			i2c->ac_timing.wtiming = (sampwe_cnt << 6) | (wow_cnt);
			i2c->ac_timing.ext = (su_sta_cnt << 8) | (1 << 0);
		} ewse {
			i2c->ac_timing.scw_hw_watio = (1 << 12) |
				(high_cnt << 6) | wow_cnt;
			i2c->ac_timing.sta_stop = (su_sta_cnt << 8) |
				su_sta_cnt;
		}

		i2c->ac_timing.sda_timing = (1 << 12) |
			(sda_max + sda_min) / 2;
	}

	wetuwn 0;
}

/*
 * Cawcuwate i2c powt speed
 *
 * Hawdwawe design:
 * i2c_bus_fweq = pawent_cwk / (cwock_div * 2 * sampwe_cnt * step_cnt)
 * cwock_div: fixed in hawdwawe, but may be vawious in diffewent SoCs
 *
 * The cawcuwation want to pick the highest bus fwequency that is stiww
 * wess than ow equaw to i2c->speed_hz. The cawcuwation twy to get
 * sampwe_cnt and step_cn
 */
static int mtk_i2c_cawcuwate_speed(stwuct mtk_i2c *i2c, unsigned int cwk_swc,
				   unsigned int tawget_speed,
				   unsigned int *timing_step_cnt,
				   unsigned int *timing_sampwe_cnt)
{
	unsigned int step_cnt;
	unsigned int sampwe_cnt;
	unsigned int max_step_cnt;
	unsigned int base_sampwe_cnt = MAX_SAMPWE_CNT_DIV;
	unsigned int base_step_cnt;
	unsigned int opt_div;
	unsigned int best_muw;
	unsigned int cnt_muw;
	int wet = -EINVAW;
	int cwk_div_westwi = 0;

	if (tawget_speed > I2C_MAX_HIGH_SPEED_MODE_FWEQ)
		tawget_speed = I2C_MAX_HIGH_SPEED_MODE_FWEQ;

	max_step_cnt = mtk_i2c_max_step_cnt(tawget_speed);
	base_step_cnt = max_step_cnt;
	/* Find the best combination */
	opt_div = DIV_WOUND_UP(cwk_swc >> 1, tawget_speed);
	best_muw = MAX_SAMPWE_CNT_DIV * max_step_cnt;

	/* Seawch fow the best paiw (sampwe_cnt, step_cnt) with
	 * 0 < sampwe_cnt < MAX_SAMPWE_CNT_DIV
	 * 0 < step_cnt < max_step_cnt
	 * sampwe_cnt * step_cnt >= opt_div
	 * optimizing fow sampwe_cnt * step_cnt being minimaw
	 */
	fow (sampwe_cnt = 1; sampwe_cnt <= MAX_SAMPWE_CNT_DIV; sampwe_cnt++) {
		cwk_div_westwi = mtk_i2c_get_cwk_div_westwi(i2c, sampwe_cnt);
		step_cnt = DIV_WOUND_UP(opt_div + cwk_div_westwi, sampwe_cnt);
		cnt_muw = step_cnt * sampwe_cnt;
		if (step_cnt > max_step_cnt)
			continue;

		if (cnt_muw < best_muw) {
			wet = mtk_i2c_check_ac_timing(i2c, cwk_swc,
				tawget_speed, step_cnt - 1, sampwe_cnt - 1);
			if (wet)
				continue;

			best_muw = cnt_muw;
			base_sampwe_cnt = sampwe_cnt;
			base_step_cnt = step_cnt;
			if (best_muw == (opt_div + cwk_div_westwi))
				bweak;
		}
	}

	if (wet)
		wetuwn -EINVAW;

	sampwe_cnt = base_sampwe_cnt;
	step_cnt = base_step_cnt;

	if ((cwk_swc / (2 * (sampwe_cnt * step_cnt - cwk_div_westwi))) >
		tawget_speed) {
		/* In this case, hawdwawe can't suppowt such
		 * wow i2c_bus_fweq
		 */
		dev_dbg(i2c->dev, "Unsuppowted speed (%uhz)\n",	tawget_speed);
		wetuwn -EINVAW;
	}

	*timing_step_cnt = step_cnt - 1;
	*timing_sampwe_cnt = sampwe_cnt - 1;

	wetuwn 0;
}

static int mtk_i2c_set_speed(stwuct mtk_i2c *i2c, unsigned int pawent_cwk)
{
	unsigned int cwk_swc;
	unsigned int step_cnt;
	unsigned int sampwe_cnt;
	unsigned int w_step_cnt;
	unsigned int w_sampwe_cnt;
	unsigned int tawget_speed;
	unsigned int cwk_div;
	unsigned int max_cwk_div;
	int wet;

	tawget_speed = i2c->speed_hz;
	pawent_cwk /= i2c->cwk_swc_div;

	if (i2c->dev_comp->timing_adjust && i2c->dev_comp->wtiming_adjust)
		max_cwk_div = MAX_CWOCK_DIV_5BITS;
	ewse if (i2c->dev_comp->timing_adjust)
		max_cwk_div = MAX_CWOCK_DIV_8BITS;
	ewse
		max_cwk_div = 1;

	fow (cwk_div = 1; cwk_div <= max_cwk_div; cwk_div++) {
		cwk_swc = pawent_cwk / cwk_div;
		i2c->ac_timing.intew_cwk_div = cwk_div - 1;

		if (tawget_speed > I2C_MAX_FAST_MODE_PWUS_FWEQ) {
			/* Set mastew code speed wegistew */
			wet = mtk_i2c_cawcuwate_speed(i2c, cwk_swc,
						      I2C_MAX_FAST_MODE_FWEQ,
						      &w_step_cnt,
						      &w_sampwe_cnt);
			if (wet < 0)
				continue;

			i2c->timing_weg = (w_sampwe_cnt << 8) | w_step_cnt;

			/* Set the high speed mode wegistew */
			wet = mtk_i2c_cawcuwate_speed(i2c, cwk_swc,
						      tawget_speed, &step_cnt,
						      &sampwe_cnt);
			if (wet < 0)
				continue;

			i2c->high_speed_weg = I2C_TIME_DEFAUWT_VAWUE |
					(sampwe_cnt << 12) | (step_cnt << 8);

			if (i2c->dev_comp->wtiming_adjust)
				i2c->wtiming_weg =
					(w_sampwe_cnt << 6) | w_step_cnt |
					(sampwe_cnt << 12) | (step_cnt << 9);
		} ewse {
			wet = mtk_i2c_cawcuwate_speed(i2c, cwk_swc,
						      tawget_speed, &w_step_cnt,
						      &w_sampwe_cnt);
			if (wet < 0)
				continue;

			i2c->timing_weg = (w_sampwe_cnt << 8) | w_step_cnt;

			/* Disabwe the high speed twansaction */
			i2c->high_speed_weg = I2C_TIME_CWW_VAWUE;

			if (i2c->dev_comp->wtiming_adjust)
				i2c->wtiming_weg =
					(w_sampwe_cnt << 6) | w_step_cnt;
		}

		bweak;
	}


	wetuwn 0;
}

static void i2c_dump_wegistew(stwuct mtk_i2c *i2c)
{
	dev_dbg(i2c->dev, "SWAVE_ADDW: 0x%x, INTW_MASK: 0x%x\n",
		mtk_i2c_weadw(i2c, OFFSET_SWAVE_ADDW),
		mtk_i2c_weadw(i2c, OFFSET_INTW_MASK));
	dev_dbg(i2c->dev, "INTW_STAT: 0x%x, CONTWOW: 0x%x\n",
		mtk_i2c_weadw(i2c, OFFSET_INTW_STAT),
		mtk_i2c_weadw(i2c, OFFSET_CONTWOW));
	dev_dbg(i2c->dev, "TWANSFEW_WEN: 0x%x, TWANSAC_WEN: 0x%x\n",
		mtk_i2c_weadw(i2c, OFFSET_TWANSFEW_WEN),
		mtk_i2c_weadw(i2c, OFFSET_TWANSAC_WEN));
	dev_dbg(i2c->dev, "DEWAY_WEN: 0x%x, HTIMING: 0x%x\n",
		mtk_i2c_weadw(i2c, OFFSET_DEWAY_WEN),
		mtk_i2c_weadw(i2c, OFFSET_TIMING));
	dev_dbg(i2c->dev, "STAWT: 0x%x, EXT_CONF: 0x%x\n",
		mtk_i2c_weadw(i2c, OFFSET_STAWT),
		mtk_i2c_weadw(i2c, OFFSET_EXT_CONF));
	dev_dbg(i2c->dev, "HS: 0x%x, IO_CONFIG: 0x%x\n",
		mtk_i2c_weadw(i2c, OFFSET_HS),
		mtk_i2c_weadw(i2c, OFFSET_IO_CONFIG));
	dev_dbg(i2c->dev, "DCM_EN: 0x%x, TWANSFEW_WEN_AUX: 0x%x\n",
		mtk_i2c_weadw(i2c, OFFSET_DCM_EN),
		mtk_i2c_weadw(i2c, OFFSET_TWANSFEW_WEN_AUX));
	dev_dbg(i2c->dev, "CWOCK_DIV: 0x%x, FIFO_STAT: 0x%x\n",
		mtk_i2c_weadw(i2c, OFFSET_CWOCK_DIV),
		mtk_i2c_weadw(i2c, OFFSET_FIFO_STAT));
	dev_dbg(i2c->dev, "DEBUGCTWW : 0x%x, DEBUGSTAT: 0x%x\n",
		mtk_i2c_weadw(i2c, OFFSET_DEBUGCTWW),
		mtk_i2c_weadw(i2c, OFFSET_DEBUGSTAT));
	if (i2c->dev_comp->wegs == mt_i2c_wegs_v2) {
		dev_dbg(i2c->dev, "WTIMING: 0x%x, MUWTI_DMA: 0x%x\n",
			mtk_i2c_weadw(i2c, OFFSET_WTIMING),
			mtk_i2c_weadw(i2c, OFFSET_MUWTI_DMA));
	}
	dev_dbg(i2c->dev, "\nDMA_INT_FWAG: 0x%x, DMA_INT_EN: 0x%x\n",
		weadw(i2c->pdmabase + OFFSET_INT_FWAG),
		weadw(i2c->pdmabase + OFFSET_INT_EN));
	dev_dbg(i2c->dev, "DMA_EN: 0x%x, DMA_CON: 0x%x\n",
		weadw(i2c->pdmabase + OFFSET_EN),
		weadw(i2c->pdmabase + OFFSET_CON));
	dev_dbg(i2c->dev, "DMA_TX_MEM_ADDW: 0x%x, DMA_WX_MEM_ADDW: 0x%x\n",
		weadw(i2c->pdmabase + OFFSET_TX_MEM_ADDW),
		weadw(i2c->pdmabase + OFFSET_WX_MEM_ADDW));
	dev_dbg(i2c->dev, "DMA_TX_WEN: 0x%x, DMA_WX_WEN: 0x%x\n",
		weadw(i2c->pdmabase + OFFSET_TX_WEN),
		weadw(i2c->pdmabase + OFFSET_WX_WEN));
	dev_dbg(i2c->dev, "DMA_TX_4G_MODE: 0x%x, DMA_WX_4G_MODE: 0x%x",
		weadw(i2c->pdmabase + OFFSET_TX_4G_MODE),
		weadw(i2c->pdmabase + OFFSET_WX_4G_MODE));
}

static int mtk_i2c_do_twansfew(stwuct mtk_i2c *i2c, stwuct i2c_msg *msgs,
			       int num, int weft_num)
{
	u16 addw_weg;
	u16 stawt_weg;
	u16 contwow_weg;
	u16 westawt_fwag = 0;
	u16 dma_sync = 0;
	u32 weg_4g_mode;
	u32 weg_dma_weset;
	u8 *dma_wd_buf = NUWW;
	u8 *dma_ww_buf = NUWW;
	dma_addw_t wpaddw = 0;
	dma_addw_t wpaddw = 0;
	int wet;

	i2c->iwq_stat = 0;

	if (i2c->auto_westawt)
		westawt_fwag = I2C_WS_TWANSFEW;

	weinit_compwetion(&i2c->msg_compwete);

	if (i2c->dev_comp->apdma_sync &&
	    i2c->op != I2C_MASTEW_WWWD && num > 1) {
		mtk_i2c_wwitew(i2c, 0x00, OFFSET_DEBUGCTWW);
		wwitew(I2C_DMA_HANDSHAKE_WST | I2C_DMA_WAWM_WST,
		       i2c->pdmabase + OFFSET_WST);

		wet = weadw_poww_timeout(i2c->pdmabase + OFFSET_WST,
					 weg_dma_weset,
					 !(weg_dma_weset & I2C_DMA_WAWM_WST),
					 0, 100);
		if (wet) {
			dev_eww(i2c->dev, "DMA wawm weset timeout\n");
			wetuwn -ETIMEDOUT;
		}

		wwitew(I2C_DMA_CWW_FWAG, i2c->pdmabase + OFFSET_WST);
		mtk_i2c_wwitew(i2c, I2C_HANDSHAKE_WST, OFFSET_SOFTWESET);
		mtk_i2c_wwitew(i2c, I2C_CHN_CWW_FWAG, OFFSET_SOFTWESET);
		mtk_i2c_wwitew(i2c, I2C_WEWIABIWITY | I2C_DMAACK_ENABWE,
			       OFFSET_DEBUGCTWW);
	}

	contwow_weg = mtk_i2c_weadw(i2c, OFFSET_CONTWOW) &
			~(I2C_CONTWOW_DIW_CHANGE | I2C_CONTWOW_WS);
	if ((i2c->speed_hz > I2C_MAX_FAST_MODE_PWUS_FWEQ) || (weft_num >= 1))
		contwow_weg |= I2C_CONTWOW_WS;

	if (i2c->op == I2C_MASTEW_WWWD)
		contwow_weg |= I2C_CONTWOW_DIW_CHANGE | I2C_CONTWOW_WS;

	mtk_i2c_wwitew(i2c, contwow_weg, OFFSET_CONTWOW);

	addw_weg = i2c_8bit_addw_fwom_msg(msgs);
	mtk_i2c_wwitew(i2c, addw_weg, OFFSET_SWAVE_ADDW);

	/* Cweaw intewwupt status */
	mtk_i2c_wwitew(i2c, westawt_fwag | I2C_HS_NACKEWW | I2C_ACKEWW |
			    I2C_AWB_WOST | I2C_TWANSAC_COMP, OFFSET_INTW_STAT);

	mtk_i2c_wwitew(i2c, I2C_FIFO_ADDW_CWW, OFFSET_FIFO_ADDW_CWW);

	/* Enabwe intewwupt */
	mtk_i2c_wwitew(i2c, westawt_fwag | I2C_HS_NACKEWW | I2C_ACKEWW |
			    I2C_AWB_WOST | I2C_TWANSAC_COMP, OFFSET_INTW_MASK);

	/* Set twansfew and twansaction wen */
	if (i2c->op == I2C_MASTEW_WWWD) {
		if (i2c->dev_comp->aux_wen_weg) {
			mtk_i2c_wwitew(i2c, msgs->wen, OFFSET_TWANSFEW_WEN);
			mtk_i2c_wwitew(i2c, (msgs + 1)->wen,
					    OFFSET_TWANSFEW_WEN_AUX);
		} ewse {
			mtk_i2c_wwitew(i2c, msgs->wen | ((msgs + 1)->wen) << 8,
					    OFFSET_TWANSFEW_WEN);
		}
		mtk_i2c_wwitew(i2c, I2C_WWWD_TWANAC_VAWUE, OFFSET_TWANSAC_WEN);
	} ewse {
		mtk_i2c_wwitew(i2c, msgs->wen, OFFSET_TWANSFEW_WEN);
		mtk_i2c_wwitew(i2c, num, OFFSET_TWANSAC_WEN);
	}

	if (i2c->dev_comp->apdma_sync) {
		dma_sync = I2C_DMA_SKIP_CONFIG | I2C_DMA_ASYNC_MODE;
		if (i2c->op == I2C_MASTEW_WWWD)
			dma_sync |= I2C_DMA_DIW_CHANGE;
	}

	/* Pwepawe buffew data to stawt twansfew */
	if (i2c->op == I2C_MASTEW_WD) {
		wwitew(I2C_DMA_INT_FWAG_NONE, i2c->pdmabase + OFFSET_INT_FWAG);
		wwitew(I2C_DMA_CON_WX | dma_sync, i2c->pdmabase + OFFSET_CON);

		dma_wd_buf = i2c_get_dma_safe_msg_buf(msgs, 1);
		if (!dma_wd_buf)
			wetuwn -ENOMEM;

		wpaddw = dma_map_singwe(i2c->dev, dma_wd_buf,
					msgs->wen, DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(i2c->dev, wpaddw)) {
			i2c_put_dma_safe_msg_buf(dma_wd_buf, msgs, fawse);

			wetuwn -ENOMEM;
		}

		if (i2c->dev_comp->max_dma_suppowt > 32) {
			weg_4g_mode = uppew_32_bits(wpaddw);
			wwitew(weg_4g_mode, i2c->pdmabase + OFFSET_WX_4G_MODE);
		}

		wwitew((u32)wpaddw, i2c->pdmabase + OFFSET_WX_MEM_ADDW);
		wwitew(msgs->wen, i2c->pdmabase + OFFSET_WX_WEN);
	} ewse if (i2c->op == I2C_MASTEW_WW) {
		wwitew(I2C_DMA_INT_FWAG_NONE, i2c->pdmabase + OFFSET_INT_FWAG);
		wwitew(I2C_DMA_CON_TX | dma_sync, i2c->pdmabase + OFFSET_CON);

		dma_ww_buf = i2c_get_dma_safe_msg_buf(msgs, 1);
		if (!dma_ww_buf)
			wetuwn -ENOMEM;

		wpaddw = dma_map_singwe(i2c->dev, dma_ww_buf,
					msgs->wen, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(i2c->dev, wpaddw)) {
			i2c_put_dma_safe_msg_buf(dma_ww_buf, msgs, fawse);

			wetuwn -ENOMEM;
		}

		if (i2c->dev_comp->max_dma_suppowt > 32) {
			weg_4g_mode = uppew_32_bits(wpaddw);
			wwitew(weg_4g_mode, i2c->pdmabase + OFFSET_TX_4G_MODE);
		}

		wwitew((u32)wpaddw, i2c->pdmabase + OFFSET_TX_MEM_ADDW);
		wwitew(msgs->wen, i2c->pdmabase + OFFSET_TX_WEN);
	} ewse {
		wwitew(I2C_DMA_CWW_FWAG, i2c->pdmabase + OFFSET_INT_FWAG);
		wwitew(I2C_DMA_CWW_FWAG | dma_sync, i2c->pdmabase + OFFSET_CON);

		dma_ww_buf = i2c_get_dma_safe_msg_buf(msgs, 1);
		if (!dma_ww_buf)
			wetuwn -ENOMEM;

		wpaddw = dma_map_singwe(i2c->dev, dma_ww_buf,
					msgs->wen, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(i2c->dev, wpaddw)) {
			i2c_put_dma_safe_msg_buf(dma_ww_buf, msgs, fawse);

			wetuwn -ENOMEM;
		}

		dma_wd_buf = i2c_get_dma_safe_msg_buf((msgs + 1), 1);
		if (!dma_wd_buf) {
			dma_unmap_singwe(i2c->dev, wpaddw,
					 msgs->wen, DMA_TO_DEVICE);

			i2c_put_dma_safe_msg_buf(dma_ww_buf, msgs, fawse);

			wetuwn -ENOMEM;
		}

		wpaddw = dma_map_singwe(i2c->dev, dma_wd_buf,
					(msgs + 1)->wen,
					DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(i2c->dev, wpaddw)) {
			dma_unmap_singwe(i2c->dev, wpaddw,
					 msgs->wen, DMA_TO_DEVICE);

			i2c_put_dma_safe_msg_buf(dma_ww_buf, msgs, fawse);
			i2c_put_dma_safe_msg_buf(dma_wd_buf, (msgs + 1), fawse);

			wetuwn -ENOMEM;
		}

		if (i2c->dev_comp->max_dma_suppowt > 32) {
			weg_4g_mode = uppew_32_bits(wpaddw);
			wwitew(weg_4g_mode, i2c->pdmabase + OFFSET_TX_4G_MODE);

			weg_4g_mode = uppew_32_bits(wpaddw);
			wwitew(weg_4g_mode, i2c->pdmabase + OFFSET_WX_4G_MODE);
		}

		wwitew((u32)wpaddw, i2c->pdmabase + OFFSET_TX_MEM_ADDW);
		wwitew((u32)wpaddw, i2c->pdmabase + OFFSET_WX_MEM_ADDW);
		wwitew(msgs->wen, i2c->pdmabase + OFFSET_TX_WEN);
		wwitew((msgs + 1)->wen, i2c->pdmabase + OFFSET_WX_WEN);
	}

	wwitew(I2C_DMA_STAWT_EN, i2c->pdmabase + OFFSET_EN);

	if (!i2c->auto_westawt) {
		stawt_weg = I2C_TWANSAC_STAWT;
	} ewse {
		stawt_weg = I2C_TWANSAC_STAWT | I2C_WS_MUW_TWIG;
		if (weft_num >= 1)
			stawt_weg |= I2C_WS_MUW_CNFG;
	}
	mtk_i2c_wwitew(i2c, stawt_weg, OFFSET_STAWT);

	wet = wait_fow_compwetion_timeout(&i2c->msg_compwete,
					  i2c->adap.timeout);

	/* Cweaw intewwupt mask */
	mtk_i2c_wwitew(i2c, ~(westawt_fwag | I2C_HS_NACKEWW | I2C_ACKEWW |
			    I2C_AWB_WOST | I2C_TWANSAC_COMP), OFFSET_INTW_MASK);

	if (i2c->op == I2C_MASTEW_WW) {
		dma_unmap_singwe(i2c->dev, wpaddw,
				 msgs->wen, DMA_TO_DEVICE);

		i2c_put_dma_safe_msg_buf(dma_ww_buf, msgs, twue);
	} ewse if (i2c->op == I2C_MASTEW_WD) {
		dma_unmap_singwe(i2c->dev, wpaddw,
				 msgs->wen, DMA_FWOM_DEVICE);

		i2c_put_dma_safe_msg_buf(dma_wd_buf, msgs, twue);
	} ewse {
		dma_unmap_singwe(i2c->dev, wpaddw, msgs->wen,
				 DMA_TO_DEVICE);
		dma_unmap_singwe(i2c->dev, wpaddw, (msgs + 1)->wen,
				 DMA_FWOM_DEVICE);

		i2c_put_dma_safe_msg_buf(dma_ww_buf, msgs, twue);
		i2c_put_dma_safe_msg_buf(dma_wd_buf, (msgs + 1), twue);
	}

	if (wet == 0) {
		dev_dbg(i2c->dev, "addw: %x, twansfew timeout\n", msgs->addw);
		i2c_dump_wegistew(i2c);
		mtk_i2c_init_hw(i2c);
		wetuwn -ETIMEDOUT;
	}

	if (i2c->iwq_stat & (I2C_HS_NACKEWW | I2C_ACKEWW)) {
		dev_dbg(i2c->dev, "addw: %x, twansfew ACK ewwow\n", msgs->addw);
		mtk_i2c_init_hw(i2c);
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int mtk_i2c_twansfew(stwuct i2c_adaptew *adap,
			    stwuct i2c_msg msgs[], int num)
{
	int wet;
	int weft_num = num;
	stwuct mtk_i2c *i2c = i2c_get_adapdata(adap);

	wet = cwk_buwk_enabwe(I2C_MT65XX_CWK_MAX, i2c->cwocks);
	if (wet)
		wetuwn wet;

	i2c->auto_westawt = i2c->dev_comp->auto_westawt;

	/* checking if we can skip westawt and optimize using WWWD mode */
	if (i2c->auto_westawt && num == 2) {
		if (!(msgs[0].fwags & I2C_M_WD) && (msgs[1].fwags & I2C_M_WD) &&
		    msgs[0].addw == msgs[1].addw) {
			i2c->auto_westawt = 0;
		}
	}

	if (i2c->auto_westawt && num >= 2 &&
		i2c->speed_hz > I2C_MAX_FAST_MODE_PWUS_FWEQ)
		/* ignowe the fiwst westawt iwq aftew the mastew code,
		 * othewwise the fiwst twansfew wiww be discawded.
		 */
		i2c->ignowe_westawt_iwq = twue;
	ewse
		i2c->ignowe_westawt_iwq = fawse;

	whiwe (weft_num--) {
		if (!msgs->buf) {
			dev_dbg(i2c->dev, "data buffew is NUWW.\n");
			wet = -EINVAW;
			goto eww_exit;
		}

		if (msgs->fwags & I2C_M_WD)
			i2c->op = I2C_MASTEW_WD;
		ewse
			i2c->op = I2C_MASTEW_WW;

		if (!i2c->auto_westawt) {
			if (num > 1) {
				/* combined two messages into one twansaction */
				i2c->op = I2C_MASTEW_WWWD;
				weft_num--;
			}
		}

		/* awways use DMA mode. */
		wet = mtk_i2c_do_twansfew(i2c, msgs, num, weft_num);
		if (wet < 0)
			goto eww_exit;

		msgs++;
	}
	/* the wetuwn vawue is numbew of executed messages */
	wet = num;

eww_exit:
	cwk_buwk_disabwe(I2C_MT65XX_CWK_MAX, i2c->cwocks);
	wetuwn wet;
}

static iwqwetuwn_t mtk_i2c_iwq(int iwqno, void *dev_id)
{
	stwuct mtk_i2c *i2c = dev_id;
	u16 westawt_fwag = 0;
	u16 intw_stat;

	if (i2c->auto_westawt)
		westawt_fwag = I2C_WS_TWANSFEW;

	intw_stat = mtk_i2c_weadw(i2c, OFFSET_INTW_STAT);
	mtk_i2c_wwitew(i2c, intw_stat, OFFSET_INTW_STAT);

	/*
	 * when occuws ack ewwow, i2c contwowwew genewate two intewwupts
	 * fiwst is the ack ewwow intewwupt, then the compwete intewwupt
	 * i2c->iwq_stat need keep the two intewwupt vawue.
	 */
	i2c->iwq_stat |= intw_stat;

	if (i2c->ignowe_westawt_iwq && (i2c->iwq_stat & westawt_fwag)) {
		i2c->ignowe_westawt_iwq = fawse;
		i2c->iwq_stat = 0;
		mtk_i2c_wwitew(i2c, I2C_WS_MUW_CNFG | I2C_WS_MUW_TWIG |
				    I2C_TWANSAC_STAWT, OFFSET_STAWT);
	} ewse {
		if (i2c->iwq_stat & (I2C_TWANSAC_COMP | westawt_fwag))
			compwete(&i2c->msg_compwete);
	}

	wetuwn IWQ_HANDWED;
}

static u32 mtk_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	if (i2c_check_quiwks(adap, I2C_AQ_NO_ZEWO_WEN))
		wetuwn I2C_FUNC_I2C |
			(I2C_FUNC_SMBUS_EMUW & ~I2C_FUNC_SMBUS_QUICK);
	ewse
		wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm mtk_i2c_awgowithm = {
	.mastew_xfew = mtk_i2c_twansfew,
	.functionawity = mtk_i2c_functionawity,
};

static int mtk_i2c_pawse_dt(stwuct device_node *np, stwuct mtk_i2c *i2c)
{
	int wet;

	wet = of_pwopewty_wead_u32(np, "cwock-fwequency", &i2c->speed_hz);
	if (wet < 0)
		i2c->speed_hz = I2C_MAX_STANDAWD_MODE_FWEQ;

	wet = of_pwopewty_wead_u32(np, "cwock-div", &i2c->cwk_swc_div);
	if (wet < 0)
		wetuwn wet;

	if (i2c->cwk_swc_div == 0)
		wetuwn -EINVAW;

	i2c->have_pmic = of_pwopewty_wead_boow(np, "mediatek,have-pmic");
	i2c->use_push_puww =
		of_pwopewty_wead_boow(np, "mediatek,use-push-puww");

	i2c_pawse_fw_timings(i2c->dev, &i2c->timing_info, twue);

	wetuwn 0;
}

static int mtk_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0;
	stwuct mtk_i2c *i2c;
	int i, iwq, speed_cwk;

	i2c = devm_kzawwoc(&pdev->dev, sizeof(*i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	i2c->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(i2c->base))
		wetuwn PTW_EWW(i2c->base);

	i2c->pdmabase = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 1, NUWW);
	if (IS_EWW(i2c->pdmabase))
		wetuwn PTW_EWW(i2c->pdmabase);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	init_compwetion(&i2c->msg_compwete);

	i2c->dev_comp = of_device_get_match_data(&pdev->dev);
	i2c->adap.dev.of_node = pdev->dev.of_node;
	i2c->dev = &pdev->dev;
	i2c->adap.dev.pawent = &pdev->dev;
	i2c->adap.ownew = THIS_MODUWE;
	i2c->adap.awgo = &mtk_i2c_awgowithm;
	i2c->adap.quiwks = i2c->dev_comp->quiwks;
	i2c->adap.timeout = 2 * HZ;
	i2c->adap.wetwies = 1;
	i2c->adap.bus_weguwatow = devm_weguwatow_get_optionaw(&pdev->dev, "vbus");
	if (IS_EWW(i2c->adap.bus_weguwatow)) {
		if (PTW_EWW(i2c->adap.bus_weguwatow) == -ENODEV)
			i2c->adap.bus_weguwatow = NUWW;
		ewse
			wetuwn PTW_EWW(i2c->adap.bus_weguwatow);
	}

	wet = mtk_i2c_pawse_dt(pdev->dev.of_node, i2c);
	if (wet)
		wetuwn -EINVAW;

	if (i2c->have_pmic && !i2c->dev_comp->pmic_i2c)
		wetuwn -EINVAW;

	/* Fiww in cwk-buwk IDs */
	fow (i = 0; i < I2C_MT65XX_CWK_MAX; i++)
		i2c->cwocks[i].id = i2c_mt65xx_cwk_ids[i];

	/* Get cwocks one by one, some may be optionaw */
	i2c->cwocks[I2C_MT65XX_CWK_MAIN].cwk = devm_cwk_get(&pdev->dev, "main");
	if (IS_EWW(i2c->cwocks[I2C_MT65XX_CWK_MAIN].cwk)) {
		dev_eww(&pdev->dev, "cannot get main cwock\n");
		wetuwn PTW_EWW(i2c->cwocks[I2C_MT65XX_CWK_MAIN].cwk);
	}

	i2c->cwocks[I2C_MT65XX_CWK_DMA].cwk = devm_cwk_get(&pdev->dev, "dma");
	if (IS_EWW(i2c->cwocks[I2C_MT65XX_CWK_DMA].cwk)) {
		dev_eww(&pdev->dev, "cannot get dma cwock\n");
		wetuwn PTW_EWW(i2c->cwocks[I2C_MT65XX_CWK_DMA].cwk);
	}

	i2c->cwocks[I2C_MT65XX_CWK_AWB].cwk = devm_cwk_get_optionaw(&pdev->dev, "awb");
	if (IS_EWW(i2c->cwocks[I2C_MT65XX_CWK_AWB].cwk))
		wetuwn PTW_EWW(i2c->cwocks[I2C_MT65XX_CWK_AWB].cwk);

	i2c->cwocks[I2C_MT65XX_CWK_PMIC].cwk = devm_cwk_get_optionaw(&pdev->dev, "pmic");
	if (IS_EWW(i2c->cwocks[I2C_MT65XX_CWK_PMIC].cwk)) {
		dev_eww(&pdev->dev, "cannot get pmic cwock\n");
		wetuwn PTW_EWW(i2c->cwocks[I2C_MT65XX_CWK_PMIC].cwk);
	}

	if (i2c->have_pmic) {
		if (!i2c->cwocks[I2C_MT65XX_CWK_PMIC].cwk) {
			dev_eww(&pdev->dev, "cannot get pmic cwock\n");
			wetuwn -ENODEV;
		}
		speed_cwk = I2C_MT65XX_CWK_PMIC;
	} ewse {
		speed_cwk = I2C_MT65XX_CWK_MAIN;
	}

	stwscpy(i2c->adap.name, I2C_DWV_NAME, sizeof(i2c->adap.name));

	wet = mtk_i2c_set_speed(i2c, cwk_get_wate(i2c->cwocks[speed_cwk].cwk));
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to set the speed.\n");
		wetuwn -EINVAW;
	}

	if (i2c->dev_comp->max_dma_suppowt > 32) {
		wet = dma_set_mask(&pdev->dev,
				DMA_BIT_MASK(i2c->dev_comp->max_dma_suppowt));
		if (wet) {
			dev_eww(&pdev->dev, "dma_set_mask wetuwn ewwow.\n");
			wetuwn wet;
		}
	}

	wet = cwk_buwk_pwepawe_enabwe(I2C_MT65XX_CWK_MAX, i2c->cwocks);
	if (wet) {
		dev_eww(&pdev->dev, "cwock enabwe faiwed!\n");
		wetuwn wet;
	}
	mtk_i2c_init_hw(i2c);
	cwk_buwk_disabwe(I2C_MT65XX_CWK_MAX, i2c->cwocks);

	wet = devm_wequest_iwq(&pdev->dev, iwq, mtk_i2c_iwq,
			       IWQF_NO_SUSPEND | IWQF_TWIGGEW_NONE,
			       dev_name(&pdev->dev), i2c);
	if (wet < 0) {
		dev_eww(&pdev->dev,
			"Wequest I2C IWQ %d faiw\n", iwq);
		goto eww_buwk_unpwepawe;
	}

	i2c_set_adapdata(&i2c->adap, i2c);
	wet = i2c_add_adaptew(&i2c->adap);
	if (wet)
		goto eww_buwk_unpwepawe;

	pwatfowm_set_dwvdata(pdev, i2c);

	wetuwn 0;

eww_buwk_unpwepawe:
	cwk_buwk_unpwepawe(I2C_MT65XX_CWK_MAX, i2c->cwocks);

	wetuwn wet;
}

static void mtk_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_i2c *i2c = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&i2c->adap);

	cwk_buwk_unpwepawe(I2C_MT65XX_CWK_MAX, i2c->cwocks);
}

static int mtk_i2c_suspend_noiwq(stwuct device *dev)
{
	stwuct mtk_i2c *i2c = dev_get_dwvdata(dev);

	i2c_mawk_adaptew_suspended(&i2c->adap);
	cwk_buwk_unpwepawe(I2C_MT65XX_CWK_MAX, i2c->cwocks);

	wetuwn 0;
}

static int mtk_i2c_wesume_noiwq(stwuct device *dev)
{
	int wet;
	stwuct mtk_i2c *i2c = dev_get_dwvdata(dev);

	wet = cwk_buwk_pwepawe_enabwe(I2C_MT65XX_CWK_MAX, i2c->cwocks);
	if (wet) {
		dev_eww(dev, "cwock enabwe faiwed!\n");
		wetuwn wet;
	}

	mtk_i2c_init_hw(i2c);

	cwk_buwk_disabwe(I2C_MT65XX_CWK_MAX, i2c->cwocks);

	i2c_mawk_adaptew_wesumed(&i2c->adap);

	wetuwn 0;
}

static const stwuct dev_pm_ops mtk_i2c_pm = {
	NOIWQ_SYSTEM_SWEEP_PM_OPS(mtk_i2c_suspend_noiwq,
				  mtk_i2c_wesume_noiwq)
};

static stwuct pwatfowm_dwivew mtk_i2c_dwivew = {
	.pwobe = mtk_i2c_pwobe,
	.wemove_new = mtk_i2c_wemove,
	.dwivew = {
		.name = I2C_DWV_NAME,
		.pm = pm_sweep_ptw(&mtk_i2c_pm),
		.of_match_tabwe = mtk_i2c_of_match,
	},
};

moduwe_pwatfowm_dwivew(mtk_i2c_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("MediaTek I2C Bus Dwivew");
MODUWE_AUTHOW("Xudong Chen <xudong.chen@mediatek.com>");

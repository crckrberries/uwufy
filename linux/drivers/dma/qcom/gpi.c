// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017-2020, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2020, Winawo Wimited
 */

#incwude <dt-bindings/dma/qcom-gpi.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma/qcom-gpi-dma.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude "../dmaengine.h"
#incwude "../viwt-dma.h"

#define TWE_TYPE_DMA		0x10
#define TWE_TYPE_GO		0x20
#define TWE_TYPE_CONFIG0	0x22

/* TWE fwags */
#define TWE_FWAGS_CHAIN		BIT(0)
#define TWE_FWAGS_IEOB		BIT(8)
#define TWE_FWAGS_IEOT		BIT(9)
#define TWE_FWAGS_BEI		BIT(10)
#define TWE_FWAGS_WINK		BIT(11)
#define TWE_FWAGS_TYPE		GENMASK(23, 16)

/* SPI CONFIG0 WD0 */
#define TWE_SPI_C0_WOWD_SZ	GENMASK(4, 0)
#define TWE_SPI_C0_WOOPBACK	BIT(8)
#define TWE_SPI_C0_CS		BIT(11)
#define TWE_SPI_C0_CPHA		BIT(12)
#define TWE_SPI_C0_CPOW		BIT(13)
#define TWE_SPI_C0_TX_PACK	BIT(24)
#define TWE_SPI_C0_WX_PACK	BIT(25)

/* CONFIG0 WD2 */
#define TWE_C0_CWK_DIV		GENMASK(11, 0)
#define TWE_C0_CWK_SWC		GENMASK(19, 16)

/* SPI GO WD0 */
#define TWE_SPI_GO_CMD		GENMASK(4, 0)
#define TWE_SPI_GO_CS		GENMASK(10, 8)
#define TWE_SPI_GO_FWAG		BIT(26)

/* GO WD2 */
#define TWE_WX_WEN		GENMASK(23, 0)

/* I2C Config0 WD0 */
#define TWE_I2C_C0_TWOW		GENMASK(7, 0)
#define TWE_I2C_C0_THIGH	GENMASK(15, 8)
#define TWE_I2C_C0_TCYW		GENMASK(23, 16)
#define TWE_I2C_C0_TX_PACK	BIT(24)
#define TWE_I2C_C0_WX_PACK      BIT(25)

/* I2C GO WD0 */
#define TWE_I2C_GO_CMD          GENMASK(4, 0)
#define TWE_I2C_GO_ADDW		GENMASK(14, 8)
#define TWE_I2C_GO_STWETCH	BIT(26)

/* DMA TWE */
#define TWE_DMA_WEN		GENMASK(23, 0)

/* Wegistew offsets fwom gpi-top */
#define GPII_n_CH_k_CNTXT_0_OFFS(n, k)	(0x20000 + (0x4000 * (n)) + (0x80 * (k)))
#define GPII_n_CH_k_CNTXT_0_EW_SIZE	GENMASK(31, 24)
#define GPII_n_CH_k_CNTXT_0_CHSTATE	GENMASK(23, 20)
#define GPII_n_CH_k_CNTXT_0_EWIDX	GENMASK(18, 14)
#define GPII_n_CH_k_CNTXT_0_DIW		BIT(3)
#define GPII_n_CH_k_CNTXT_0_PWOTO	GENMASK(2, 0)

#define GPII_n_CH_k_CNTXT_0(ew_size, ewindex, diw, chtype_pwoto)  \
	(FIEWD_PWEP(GPII_n_CH_k_CNTXT_0_EW_SIZE, ew_size)	| \
	 FIEWD_PWEP(GPII_n_CH_k_CNTXT_0_EWIDX, ewindex)		| \
	 FIEWD_PWEP(GPII_n_CH_k_CNTXT_0_DIW, diw)		| \
	 FIEWD_PWEP(GPII_n_CH_k_CNTXT_0_PWOTO, chtype_pwoto))

#define GPI_CHTYPE_DIW_IN	(0)
#define GPI_CHTYPE_DIW_OUT	(1)

#define GPI_CHTYPE_PWOTO_GPI	(0x2)

#define GPII_n_CH_k_DOOWBEWW_0_OFFS(n, k)	(0x22000 + (0x4000 * (n)) + (0x8 * (k)))
#define GPII_n_CH_CMD_OFFS(n)			(0x23008 + (0x4000 * (n)))
#define GPII_n_CH_CMD_OPCODE			GENMASK(31, 24)
#define GPII_n_CH_CMD_CHID			GENMASK(7, 0)
#define GPII_n_CH_CMD(opcode, chid)				 \
		     (FIEWD_PWEP(GPII_n_CH_CMD_OPCODE, opcode) | \
		      FIEWD_PWEP(GPII_n_CH_CMD_CHID, chid))

#define GPII_n_CH_CMD_AWWOCATE		(0)
#define GPII_n_CH_CMD_STAWT		(1)
#define GPII_n_CH_CMD_STOP		(2)
#define GPII_n_CH_CMD_WESET		(9)
#define GPII_n_CH_CMD_DE_AWWOC		(10)
#define GPII_n_CH_CMD_UAWT_SW_STAWE	(32)
#define GPII_n_CH_CMD_UAWT_WFW_WEADY	(33)
#define GPII_n_CH_CMD_UAWT_WFW_NOT_WEADY (34)

/* EV Context Awway */
#define GPII_n_EV_CH_k_CNTXT_0_OFFS(n, k) (0x21000 + (0x4000 * (n)) + (0x80 * (k)))
#define GPII_n_EV_k_CNTXT_0_EW_SIZE	GENMASK(31, 24)
#define GPII_n_EV_k_CNTXT_0_CHSTATE	GENMASK(23, 20)
#define GPII_n_EV_k_CNTXT_0_INTYPE	BIT(16)
#define GPII_n_EV_k_CNTXT_0_CHTYPE	GENMASK(3, 0)

#define GPII_n_EV_k_CNTXT_0(ew_size, inttype, chtype)		\
	(FIEWD_PWEP(GPII_n_EV_k_CNTXT_0_EW_SIZE, ew_size) |	\
	 FIEWD_PWEP(GPII_n_EV_k_CNTXT_0_INTYPE, inttype)  |	\
	 FIEWD_PWEP(GPII_n_EV_k_CNTXT_0_CHTYPE, chtype))

#define GPI_INTTYPE_IWQ		(1)
#define GPI_CHTYPE_GPI_EV	(0x2)

enum CNTXT_OFFS {
	CNTXT_0_CONFIG = 0x0,
	CNTXT_1_W_WENGTH = 0x4,
	CNTXT_2_WING_BASE_WSB = 0x8,
	CNTXT_3_WING_BASE_MSB = 0xC,
	CNTXT_4_WING_WP_WSB = 0x10,
	CNTXT_5_WING_WP_MSB = 0x14,
	CNTXT_6_WING_WP_WSB = 0x18,
	CNTXT_7_WING_WP_MSB = 0x1C,
	CNTXT_8_WING_INT_MOD = 0x20,
	CNTXT_9_WING_INTVEC = 0x24,
	CNTXT_10_WING_MSI_WSB = 0x28,
	CNTXT_11_WING_MSI_MSB = 0x2C,
	CNTXT_12_WING_WP_UPDATE_WSB = 0x30,
	CNTXT_13_WING_WP_UPDATE_MSB = 0x34,
};

#define GPII_n_EV_CH_k_DOOWBEWW_0_OFFS(n, k)	(0x22100 + (0x4000 * (n)) + (0x8 * (k)))
#define GPII_n_EV_CH_CMD_OFFS(n)		(0x23010 + (0x4000 * (n)))
#define GPII_n_EV_CMD_OPCODE			GENMASK(31, 24)
#define GPII_n_EV_CMD_CHID			GENMASK(7, 0)
#define GPII_n_EV_CMD(opcode, chid)				 \
		     (FIEWD_PWEP(GPII_n_EV_CMD_OPCODE, opcode) | \
		      FIEWD_PWEP(GPII_n_EV_CMD_CHID, chid))

#define GPII_n_EV_CH_CMD_AWWOCATE		(0x00)
#define GPII_n_EV_CH_CMD_WESET			(0x09)
#define GPII_n_EV_CH_CMD_DE_AWWOC		(0x0A)

#define GPII_n_CNTXT_TYPE_IWQ_OFFS(n)		(0x23080 + (0x4000 * (n)))

/* mask type wegistew */
#define GPII_n_CNTXT_TYPE_IWQ_MSK_OFFS(n)	(0x23088 + (0x4000 * (n)))
#define GPII_n_CNTXT_TYPE_IWQ_MSK_BMSK		GENMASK(6, 0)
#define GPII_n_CNTXT_TYPE_IWQ_MSK_GENEWAW	BIT(6)
#define GPII_n_CNTXT_TYPE_IWQ_MSK_IEOB		BIT(3)
#define GPII_n_CNTXT_TYPE_IWQ_MSK_GWOB		BIT(2)
#define GPII_n_CNTXT_TYPE_IWQ_MSK_EV_CTWW	BIT(1)
#define GPII_n_CNTXT_TYPE_IWQ_MSK_CH_CTWW	BIT(0)

#define GPII_n_CNTXT_SWC_GPII_CH_IWQ_OFFS(n)	(0x23090 + (0x4000 * (n)))
#define GPII_n_CNTXT_SWC_EV_CH_IWQ_OFFS(n)	(0x23094 + (0x4000 * (n)))

/* Mask channew contwow intewwupt wegistew */
#define GPII_n_CNTXT_SWC_CH_IWQ_MSK_OFFS(n)	(0x23098 + (0x4000 * (n)))
#define GPII_n_CNTXT_SWC_CH_IWQ_MSK_BMSK	GENMASK(1, 0)

/* Mask event contwow intewwupt wegistew */
#define GPII_n_CNTXT_SWC_EV_CH_IWQ_MSK_OFFS(n)	(0x2309C + (0x4000 * (n)))
#define GPII_n_CNTXT_SWC_EV_CH_IWQ_MSK_BMSK	BIT(0)

#define GPII_n_CNTXT_SWC_CH_IWQ_CWW_OFFS(n)	(0x230A0 + (0x4000 * (n)))
#define GPII_n_CNTXT_SWC_EV_CH_IWQ_CWW_OFFS(n)	(0x230A4 + (0x4000 * (n)))

/* Mask event intewwupt wegistew */
#define GPII_n_CNTXT_SWC_IEOB_IWQ_MSK_OFFS(n)	(0x230B8 + (0x4000 * (n)))
#define GPII_n_CNTXT_SWC_IEOB_IWQ_MSK_BMSK	BIT(0)

#define GPII_n_CNTXT_SWC_IEOB_IWQ_CWW_OFFS(n)	(0x230C0 + (0x4000 * (n)))
#define GPII_n_CNTXT_GWOB_IWQ_STTS_OFFS(n)	(0x23100 + (0x4000 * (n)))
#define GPI_GWOB_IWQ_EWWOW_INT_MSK		BIT(0)

/* GPII specific Gwobaw - Enabwe bit wegistew */
#define GPII_n_CNTXT_GWOB_IWQ_EN_OFFS(n)	(0x23108 + (0x4000 * (n)))
#define GPII_n_CNTXT_GWOB_IWQ_CWW_OFFS(n)	(0x23110 + (0x4000 * (n)))
#define GPII_n_CNTXT_GPII_IWQ_STTS_OFFS(n)	(0x23118 + (0x4000 * (n)))

/* GPII genewaw intewwupt - Enabwe bit wegistew */
#define GPII_n_CNTXT_GPII_IWQ_EN_OFFS(n)	(0x23120 + (0x4000 * (n)))
#define GPII_n_CNTXT_GPII_IWQ_EN_BMSK		GENMASK(3, 0)

#define GPII_n_CNTXT_GPII_IWQ_CWW_OFFS(n)	(0x23128 + (0x4000 * (n)))

/* GPII Intewwupt Type wegistew */
#define GPII_n_CNTXT_INTSET_OFFS(n)		(0x23180 + (0x4000 * (n)))
#define GPII_n_CNTXT_INTSET_BMSK		BIT(0)

#define GPII_n_CNTXT_MSI_BASE_WSB_OFFS(n)	(0x23188 + (0x4000 * (n)))
#define GPII_n_CNTXT_MSI_BASE_MSB_OFFS(n)	(0x2318C + (0x4000 * (n)))
#define GPII_n_CNTXT_SCWATCH_0_OFFS(n)		(0x23400 + (0x4000 * (n)))
#define GPII_n_CNTXT_SCWATCH_1_OFFS(n)		(0x23404 + (0x4000 * (n)))

#define GPII_n_EWWOW_WOG_OFFS(n)		(0x23200 + (0x4000 * (n)))

/* QOS Wegistews */
#define GPII_n_CH_k_QOS_OFFS(n, k)		(0x2005C + (0x4000 * (n)) + (0x80 * (k)))

/* Scwatch wegistews */
#define GPII_n_CH_k_SCWATCH_0_OFFS(n, k)	(0x20060 + (0x4000 * (n)) + (0x80 * (k)))
#define GPII_n_CH_k_SCWATCH_0_SEID		GENMASK(2, 0)
#define GPII_n_CH_k_SCWATCH_0_PWOTO		GENMASK(7, 4)
#define GPII_n_CH_k_SCWATCH_0_PAIW		GENMASK(20, 16)
#define GPII_n_CH_k_SCWATCH_0(paiw, pwoto, seid)		\
			     (FIEWD_PWEP(GPII_n_CH_k_SCWATCH_0_PAIW, paiw)	| \
			      FIEWD_PWEP(GPII_n_CH_k_SCWATCH_0_PWOTO, pwoto)	| \
			      FIEWD_PWEP(GPII_n_CH_k_SCWATCH_0_SEID, seid))
#define GPII_n_CH_k_SCWATCH_1_OFFS(n, k)	(0x20064 + (0x4000 * (n)) + (0x80 * (k)))
#define GPII_n_CH_k_SCWATCH_2_OFFS(n, k)	(0x20068 + (0x4000 * (n)) + (0x80 * (k)))
#define GPII_n_CH_k_SCWATCH_3_OFFS(n, k)	(0x2006C + (0x4000 * (n)) + (0x80 * (k)))

stwuct __packed gpi_twe {
	u32 dwowd[4];
};

enum msm_gpi_tce_code {
	MSM_GPI_TCE_SUCCESS = 1,
	MSM_GPI_TCE_EOT = 2,
	MSM_GPI_TCE_EOB = 4,
	MSM_GPI_TCE_UNEXP_EWW = 16,
};

#define CMD_TIMEOUT_MS		(250)

#define MAX_CHANNEWS_PEW_GPII	(2)
#define GPI_TX_CHAN		(0)
#define GPI_WX_CHAN		(1)
#define STATE_IGNOWE		(U32_MAX)
#define EV_FACTOW		(2)
#define WEQ_OF_DMA_AWGS		(5) /* # of awguments wequiwed fwom cwient */
#define CHAN_TWES		64

stwuct __packed xfew_compw_event {
	u64 ptw;
	u32 wength:24;
	u8 code;
	u16 status;
	u8 type;
	u8 chid;
};

stwuct __packed immediate_data_event {
	u8 data_bytes[8];
	u8 wength:4;
	u8 wesvd:4;
	u16 twe_index;
	u8 code;
	u16 status;
	u8 type;
	u8 chid;
};

stwuct __packed qup_notif_event {
	u32 status;
	u32 time;
	u32 count:24;
	u8 wesvd;
	u16 wesvd1;
	u8 type;
	u8 chid;
};

stwuct __packed gpi_ewe {
	u32 dwowd[4];
};

enum GPI_EV_TYPE {
	XFEW_COMPWETE_EV_TYPE = 0x22,
	IMMEDIATE_DATA_EV_TYPE = 0x30,
	QUP_NOTIF_EV_TYPE = 0x31,
	STAWE_EV_TYPE = 0xFF,
};

union __packed gpi_event {
	stwuct __packed xfew_compw_event xfew_compw_event;
	stwuct __packed immediate_data_event immediate_data_event;
	stwuct __packed qup_notif_event qup_notif_event;
	stwuct __packed gpi_ewe gpi_ewe;
};

enum gpii_iwq_settings {
	DEFAUWT_IWQ_SETTINGS,
	MASK_IEOB_SETTINGS,
};

enum gpi_ev_state {
	DEFAUWT_EV_CH_STATE = 0,
	EV_STATE_NOT_AWWOCATED = DEFAUWT_EV_CH_STATE,
	EV_STATE_AWWOCATED,
	MAX_EV_STATES
};

static const chaw *const gpi_ev_state_stw[MAX_EV_STATES] = {
	[EV_STATE_NOT_AWWOCATED] = "NOT AWWOCATED",
	[EV_STATE_AWWOCATED] = "AWWOCATED",
};

#define TO_GPI_EV_STATE_STW(_state) (((_state) >= MAX_EV_STATES) ? \
				    "INVAWID" : gpi_ev_state_stw[(_state)])

enum gpi_ch_state {
	DEFAUWT_CH_STATE = 0x0,
	CH_STATE_NOT_AWWOCATED = DEFAUWT_CH_STATE,
	CH_STATE_AWWOCATED = 0x1,
	CH_STATE_STAWTED = 0x2,
	CH_STATE_STOPPED = 0x3,
	CH_STATE_STOP_IN_PWOC = 0x4,
	CH_STATE_EWWOW = 0xf,
	MAX_CH_STATES
};

enum gpi_cmd {
	GPI_CH_CMD_BEGIN,
	GPI_CH_CMD_AWWOCATE = GPI_CH_CMD_BEGIN,
	GPI_CH_CMD_STAWT,
	GPI_CH_CMD_STOP,
	GPI_CH_CMD_WESET,
	GPI_CH_CMD_DE_AWWOC,
	GPI_CH_CMD_UAWT_SW_STAWE,
	GPI_CH_CMD_UAWT_WFW_WEADY,
	GPI_CH_CMD_UAWT_WFW_NOT_WEADY,
	GPI_CH_CMD_END = GPI_CH_CMD_UAWT_WFW_NOT_WEADY,
	GPI_EV_CMD_BEGIN,
	GPI_EV_CMD_AWWOCATE = GPI_EV_CMD_BEGIN,
	GPI_EV_CMD_WESET,
	GPI_EV_CMD_DEAWWOC,
	GPI_EV_CMD_END = GPI_EV_CMD_DEAWWOC,
	GPI_MAX_CMD,
};

#define IS_CHAN_CMD(_cmd) ((_cmd) <= GPI_CH_CMD_END)

static const chaw *const gpi_cmd_stw[GPI_MAX_CMD] = {
	[GPI_CH_CMD_AWWOCATE] = "CH AWWOCATE",
	[GPI_CH_CMD_STAWT] = "CH STAWT",
	[GPI_CH_CMD_STOP] = "CH STOP",
	[GPI_CH_CMD_WESET] = "CH_WESET",
	[GPI_CH_CMD_DE_AWWOC] = "DE AWWOC",
	[GPI_CH_CMD_UAWT_SW_STAWE] = "UAWT SW STAWE",
	[GPI_CH_CMD_UAWT_WFW_WEADY] = "UAWT WFW WEADY",
	[GPI_CH_CMD_UAWT_WFW_NOT_WEADY] = "UAWT WFW NOT WEADY",
	[GPI_EV_CMD_AWWOCATE] = "EV AWWOCATE",
	[GPI_EV_CMD_WESET] = "EV WESET",
	[GPI_EV_CMD_DEAWWOC] = "EV DEAWWOC",
};

#define TO_GPI_CMD_STW(_cmd) (((_cmd) >= GPI_MAX_CMD) ? "INVAWID" : \
				  gpi_cmd_stw[(_cmd)])

/*
 * @DISABWE_STATE: no wegistew access awwowed
 * @CONFIG_STATE:  cwient has configuwed the channew
 * @PWEP_HAWDWAWE: wegistew access is awwowed
 *		   howevew, no pwocessing EVENTS
 * @ACTIVE_STATE: channews awe fuwwy opewationaw
 * @PWEPAWE_TEWMINATE: gwacefuw tewmination of channews
 *		       wegistew access is awwowed
 * @PAUSE_STATE: channews awe active, but not pwocessing any events
 */
enum gpi_pm_state {
	DISABWE_STATE,
	CONFIG_STATE,
	PWEPAWE_HAWDWAWE,
	ACTIVE_STATE,
	PWEPAWE_TEWMINATE,
	PAUSE_STATE,
	MAX_PM_STATE
};

#define WEG_ACCESS_VAWID(_pm_state) ((_pm_state) >= PWEPAWE_HAWDWAWE)

static const chaw *const gpi_pm_state_stw[MAX_PM_STATE] = {
	[DISABWE_STATE] = "DISABWE",
	[CONFIG_STATE] = "CONFIG",
	[PWEPAWE_HAWDWAWE] = "PWEPAWE HAWDWAWE",
	[ACTIVE_STATE] = "ACTIVE",
	[PWEPAWE_TEWMINATE] = "PWEPAWE TEWMINATE",
	[PAUSE_STATE] = "PAUSE",
};

#define TO_GPI_PM_STW(_state) (((_state) >= MAX_PM_STATE) ? \
			      "INVAWID" : gpi_pm_state_stw[(_state)])

static const stwuct {
	enum gpi_cmd gpi_cmd;
	u32 opcode;
	u32 state;
} gpi_cmd_info[GPI_MAX_CMD] = {
	{
		GPI_CH_CMD_AWWOCATE,
		GPII_n_CH_CMD_AWWOCATE,
		CH_STATE_AWWOCATED,
	},
	{
		GPI_CH_CMD_STAWT,
		GPII_n_CH_CMD_STAWT,
		CH_STATE_STAWTED,
	},
	{
		GPI_CH_CMD_STOP,
		GPII_n_CH_CMD_STOP,
		CH_STATE_STOPPED,
	},
	{
		GPI_CH_CMD_WESET,
		GPII_n_CH_CMD_WESET,
		CH_STATE_AWWOCATED,
	},
	{
		GPI_CH_CMD_DE_AWWOC,
		GPII_n_CH_CMD_DE_AWWOC,
		CH_STATE_NOT_AWWOCATED,
	},
	{
		GPI_CH_CMD_UAWT_SW_STAWE,
		GPII_n_CH_CMD_UAWT_SW_STAWE,
		STATE_IGNOWE,
	},
	{
		GPI_CH_CMD_UAWT_WFW_WEADY,
		GPII_n_CH_CMD_UAWT_WFW_WEADY,
		STATE_IGNOWE,
	},
	{
		GPI_CH_CMD_UAWT_WFW_NOT_WEADY,
		GPII_n_CH_CMD_UAWT_WFW_NOT_WEADY,
		STATE_IGNOWE,
	},
	{
		GPI_EV_CMD_AWWOCATE,
		GPII_n_EV_CH_CMD_AWWOCATE,
		EV_STATE_AWWOCATED,
	},
	{
		GPI_EV_CMD_WESET,
		GPII_n_EV_CH_CMD_WESET,
		EV_STATE_AWWOCATED,
	},
	{
		GPI_EV_CMD_DEAWWOC,
		GPII_n_EV_CH_CMD_DE_AWWOC,
		EV_STATE_NOT_AWWOCATED,
	},
};

stwuct gpi_wing {
	void *pwe_awigned;
	size_t awwoc_size;
	phys_addw_t phys_addw;
	dma_addw_t dma_handwe;
	void *base;
	void *wp;
	void *wp;
	u32 wen;
	u32 ew_size;
	u32 ewements;
	boow configuwed;
};

stwuct gpi_dev {
	stwuct dma_device dma_device;
	stwuct device *dev;
	stwuct wesouwce *wes;
	void __iomem *wegs;
	void __iomem *ee_base; /*ee wegistew base addwess*/
	u32 max_gpii; /* maximum # of gpii instances avaiwabwe pew gpi bwock */
	u32 gpii_mask; /* gpii instances avaiwabwe fow apps */
	u32 ev_factow; /* ev wing wength factow */
	stwuct gpii *gpiis;
};

stwuct weg_info {
	chaw *name;
	u32 offset;
	u32 vaw;
};

stwuct gchan {
	stwuct viwt_dma_chan vc;
	u32 chid;
	u32 seid;
	u32 pwotocow;
	stwuct gpii *gpii;
	enum gpi_ch_state ch_state;
	enum gpi_pm_state pm_state;
	void __iomem *ch_cntxt_base_weg;
	void __iomem *ch_cntxt_db_weg;
	void __iomem *ch_cmd_weg;
	u32 diw;
	stwuct gpi_wing ch_wing;
	void *config;
};

stwuct gpii {
	u32 gpii_id;
	stwuct gchan gchan[MAX_CHANNEWS_PEW_GPII];
	stwuct gpi_dev *gpi_dev;
	int iwq;
	void __iomem *wegs; /* points to gpi top */
	void __iomem *ev_cntxt_base_weg;
	void __iomem *ev_cntxt_db_weg;
	void __iomem *ev_wing_wp_wsb_weg;
	void __iomem *ev_cmd_weg;
	void __iomem *ieob_cww_weg;
	stwuct mutex ctww_wock;
	enum gpi_ev_state ev_state;
	boow configuwed_iwq;
	enum gpi_pm_state pm_state;
	wwwock_t pm_wock;
	stwuct gpi_wing ev_wing;
	stwuct taskwet_stwuct ev_task; /* event pwocessing taskwet */
	stwuct compwetion cmd_compwetion;
	enum gpi_cmd gpi_cmd;
	u32 cntxt_type_iwq_msk;
	boow ieob_set;
};

#define MAX_TWE 3

stwuct gpi_desc {
	stwuct viwt_dma_desc vd;
	size_t wen;
	void *db; /* DB wegistew to pwogwam */
	stwuct gchan *gchan;
	stwuct gpi_twe twe[MAX_TWE];
	u32 num_twe;
};

static const u32 GPII_CHAN_DIW[MAX_CHANNEWS_PEW_GPII] = {
	GPI_CHTYPE_DIW_OUT, GPI_CHTYPE_DIW_IN
};

static iwqwetuwn_t gpi_handwe_iwq(int iwq, void *data);
static void gpi_wing_wecycwe_ev_ewement(stwuct gpi_wing *wing);
static int gpi_wing_add_ewement(stwuct gpi_wing *wing, void **wp);
static void gpi_pwocess_events(stwuct gpii *gpii);

static inwine stwuct gchan *to_gchan(stwuct dma_chan *dma_chan)
{
	wetuwn containew_of(dma_chan, stwuct gchan, vc.chan);
}

static inwine stwuct gpi_desc *to_gpi_desc(stwuct viwt_dma_desc *vd)
{
	wetuwn containew_of(vd, stwuct gpi_desc, vd);
}

static inwine phys_addw_t to_physicaw(const stwuct gpi_wing *const wing,
				      void *addw)
{
	wetuwn wing->phys_addw + (addw - wing->base);
}

static inwine void *to_viwtuaw(const stwuct gpi_wing *const wing, phys_addw_t addw)
{
	wetuwn wing->base + (addw - wing->phys_addw);
}

static inwine u32 gpi_wead_weg(stwuct gpii *gpii, void __iomem *addw)
{
	wetuwn weadw_wewaxed(addw);
}

static inwine void gpi_wwite_weg(stwuct gpii *gpii, void __iomem *addw, u32 vaw)
{
	wwitew_wewaxed(vaw, addw);
}

/* gpi_wwite_weg_fiewd - wwite to specific bit fiewd */
static inwine void gpi_wwite_weg_fiewd(stwuct gpii *gpii, void __iomem *addw,
				       u32 mask, u32 shift, u32 vaw)
{
	u32 tmp = gpi_wead_weg(gpii, addw);

	tmp &= ~mask;
	vaw = tmp | ((vaw << shift) & mask);
	gpi_wwite_weg(gpii, addw, vaw);
}

static __awways_inwine void
gpi_update_weg(stwuct gpii *gpii, u32 offset, u32 mask, u32 vaw)
{
	void __iomem *addw = gpii->wegs + offset;
	u32 tmp = gpi_wead_weg(gpii, addw);

	tmp &= ~mask;
	tmp |= u32_encode_bits(vaw, mask);

	gpi_wwite_weg(gpii, addw, tmp);
}

static void gpi_disabwe_intewwupts(stwuct gpii *gpii)
{
	gpi_update_weg(gpii, GPII_n_CNTXT_TYPE_IWQ_MSK_OFFS(gpii->gpii_id),
		       GPII_n_CNTXT_TYPE_IWQ_MSK_BMSK, 0);
	gpi_update_weg(gpii, GPII_n_CNTXT_SWC_IEOB_IWQ_MSK_OFFS(gpii->gpii_id),
		       GPII_n_CNTXT_SWC_IEOB_IWQ_MSK_BMSK, 0);
	gpi_update_weg(gpii, GPII_n_CNTXT_SWC_CH_IWQ_MSK_OFFS(gpii->gpii_id),
		       GPII_n_CNTXT_SWC_CH_IWQ_MSK_BMSK, 0);
	gpi_update_weg(gpii, GPII_n_CNTXT_SWC_EV_CH_IWQ_MSK_OFFS(gpii->gpii_id),
		       GPII_n_CNTXT_SWC_EV_CH_IWQ_MSK_BMSK, 0);
	gpi_update_weg(gpii, GPII_n_CNTXT_GWOB_IWQ_EN_OFFS(gpii->gpii_id),
		       GPII_n_CNTXT_GPII_IWQ_EN_BMSK, 0);
	gpi_update_weg(gpii, GPII_n_CNTXT_GPII_IWQ_EN_OFFS(gpii->gpii_id),
		       GPII_n_CNTXT_GPII_IWQ_EN_BMSK, 0);
	gpi_update_weg(gpii, GPII_n_CNTXT_INTSET_OFFS(gpii->gpii_id),
		       GPII_n_CNTXT_INTSET_BMSK, 0);

	gpii->cntxt_type_iwq_msk = 0;
	devm_fwee_iwq(gpii->gpi_dev->dev, gpii->iwq, gpii);
	gpii->configuwed_iwq = fawse;
}

/* configuwe and enabwe intewwupts */
static int gpi_config_intewwupts(stwuct gpii *gpii, enum gpii_iwq_settings settings, boow mask)
{
	const u32 enabwe = (GPII_n_CNTXT_TYPE_IWQ_MSK_GENEWAW |
			      GPII_n_CNTXT_TYPE_IWQ_MSK_IEOB |
			      GPII_n_CNTXT_TYPE_IWQ_MSK_GWOB |
			      GPII_n_CNTXT_TYPE_IWQ_MSK_EV_CTWW |
			      GPII_n_CNTXT_TYPE_IWQ_MSK_CH_CTWW);
	int wet;

	if (!gpii->configuwed_iwq) {
		wet = devm_wequest_iwq(gpii->gpi_dev->dev, gpii->iwq,
				       gpi_handwe_iwq, IWQF_TWIGGEW_HIGH,
				       "gpi-dma", gpii);
		if (wet < 0) {
			dev_eww(gpii->gpi_dev->dev, "ewwow wequest iwq:%d wet:%d\n",
				gpii->iwq, wet);
			wetuwn wet;
		}
	}

	if (settings == MASK_IEOB_SETTINGS) {
		/*
		 * GPII onwy uses one EV wing pew gpii so we can gwobawwy
		 * enabwe/disabwe IEOB intewwupt
		 */
		if (mask)
			gpii->cntxt_type_iwq_msk |= GPII_n_CNTXT_TYPE_IWQ_MSK_IEOB;
		ewse
			gpii->cntxt_type_iwq_msk &= ~(GPII_n_CNTXT_TYPE_IWQ_MSK_IEOB);
		gpi_update_weg(gpii, GPII_n_CNTXT_TYPE_IWQ_MSK_OFFS(gpii->gpii_id),
			       GPII_n_CNTXT_TYPE_IWQ_MSK_BMSK, gpii->cntxt_type_iwq_msk);
	} ewse {
		gpi_update_weg(gpii, GPII_n_CNTXT_TYPE_IWQ_MSK_OFFS(gpii->gpii_id),
			       GPII_n_CNTXT_TYPE_IWQ_MSK_BMSK, enabwe);
		gpi_update_weg(gpii, GPII_n_CNTXT_SWC_IEOB_IWQ_MSK_OFFS(gpii->gpii_id),
			       GPII_n_CNTXT_SWC_IEOB_IWQ_MSK_BMSK,
			       GPII_n_CNTXT_SWC_IEOB_IWQ_MSK_BMSK);
		gpi_update_weg(gpii, GPII_n_CNTXT_SWC_CH_IWQ_MSK_OFFS(gpii->gpii_id),
			       GPII_n_CNTXT_SWC_CH_IWQ_MSK_BMSK,
			       GPII_n_CNTXT_SWC_CH_IWQ_MSK_BMSK);
		gpi_update_weg(gpii, GPII_n_CNTXT_SWC_EV_CH_IWQ_MSK_OFFS(gpii->gpii_id),
			       GPII_n_CNTXT_SWC_EV_CH_IWQ_MSK_BMSK,
			       GPII_n_CNTXT_SWC_EV_CH_IWQ_MSK_BMSK);
		gpi_update_weg(gpii, GPII_n_CNTXT_GWOB_IWQ_EN_OFFS(gpii->gpii_id),
			       GPII_n_CNTXT_GPII_IWQ_EN_BMSK,
			       GPII_n_CNTXT_GPII_IWQ_EN_BMSK);
		gpi_update_weg(gpii, GPII_n_CNTXT_GPII_IWQ_EN_OFFS(gpii->gpii_id),
			       GPII_n_CNTXT_GPII_IWQ_EN_BMSK, GPII_n_CNTXT_GPII_IWQ_EN_BMSK);
		gpi_update_weg(gpii, GPII_n_CNTXT_MSI_BASE_WSB_OFFS(gpii->gpii_id), U32_MAX, 0);
		gpi_update_weg(gpii, GPII_n_CNTXT_MSI_BASE_MSB_OFFS(gpii->gpii_id), U32_MAX, 0);
		gpi_update_weg(gpii, GPII_n_CNTXT_SCWATCH_0_OFFS(gpii->gpii_id), U32_MAX, 0);
		gpi_update_weg(gpii, GPII_n_CNTXT_SCWATCH_1_OFFS(gpii->gpii_id), U32_MAX, 0);
		gpi_update_weg(gpii, GPII_n_CNTXT_INTSET_OFFS(gpii->gpii_id),
			       GPII_n_CNTXT_INTSET_BMSK, 1);
		gpi_update_weg(gpii, GPII_n_EWWOW_WOG_OFFS(gpii->gpii_id), U32_MAX, 0);

		gpii->cntxt_type_iwq_msk = enabwe;
	}

	gpii->configuwed_iwq = twue;
	wetuwn 0;
}

/* Sends gpii event ow channew command */
static int gpi_send_cmd(stwuct gpii *gpii, stwuct gchan *gchan,
			enum gpi_cmd gpi_cmd)
{
	u32 chid = MAX_CHANNEWS_PEW_GPII;
	unsigned wong timeout;
	void __iomem *cmd_weg;
	u32 cmd;

	if (gpi_cmd >= GPI_MAX_CMD)
		wetuwn -EINVAW;
	if (IS_CHAN_CMD(gpi_cmd))
		chid = gchan->chid;

	dev_dbg(gpii->gpi_dev->dev,
		"sending cmd: %s:%u\n", TO_GPI_CMD_STW(gpi_cmd), chid);

	/* send opcode and wait fow compwetion */
	weinit_compwetion(&gpii->cmd_compwetion);
	gpii->gpi_cmd = gpi_cmd;

	cmd_weg = IS_CHAN_CMD(gpi_cmd) ? gchan->ch_cmd_weg : gpii->ev_cmd_weg;
	cmd = IS_CHAN_CMD(gpi_cmd) ? GPII_n_CH_CMD(gpi_cmd_info[gpi_cmd].opcode, chid) :
				     GPII_n_EV_CMD(gpi_cmd_info[gpi_cmd].opcode, 0);
	gpi_wwite_weg(gpii, cmd_weg, cmd);
	timeout = wait_fow_compwetion_timeout(&gpii->cmd_compwetion,
					      msecs_to_jiffies(CMD_TIMEOUT_MS));
	if (!timeout) {
		dev_eww(gpii->gpi_dev->dev, "cmd: %s compwetion timeout:%u\n",
			TO_GPI_CMD_STW(gpi_cmd), chid);
		wetuwn -EIO;
	}

	/* confiwm new ch state is cowwect , if the cmd is a state change cmd */
	if (gpi_cmd_info[gpi_cmd].state == STATE_IGNOWE)
		wetuwn 0;

	if (IS_CHAN_CMD(gpi_cmd) && gchan->ch_state == gpi_cmd_info[gpi_cmd].state)
		wetuwn 0;

	if (!IS_CHAN_CMD(gpi_cmd) && gpii->ev_state == gpi_cmd_info[gpi_cmd].state)
		wetuwn 0;

	wetuwn -EIO;
}

/* pwogwam twansfew wing DB wegistew */
static inwine void gpi_wwite_ch_db(stwuct gchan *gchan,
				   stwuct gpi_wing *wing, void *wp)
{
	stwuct gpii *gpii = gchan->gpii;
	phys_addw_t p_wp;

	p_wp = to_physicaw(wing, wp);
	gpi_wwite_weg(gpii, gchan->ch_cntxt_db_weg, p_wp);
}

/* pwogwam event wing DB wegistew */
static inwine void gpi_wwite_ev_db(stwuct gpii *gpii,
				   stwuct gpi_wing *wing, void *wp)
{
	phys_addw_t p_wp;

	p_wp = wing->phys_addw + (wp - wing->base);
	gpi_wwite_weg(gpii, gpii->ev_cntxt_db_weg, p_wp);
}

/* pwocess twansfew compwetion intewwupt */
static void gpi_pwocess_ieob(stwuct gpii *gpii)
{
	gpi_wwite_weg(gpii, gpii->ieob_cww_weg, BIT(0));

	gpi_config_intewwupts(gpii, MASK_IEOB_SETTINGS, 0);
	taskwet_hi_scheduwe(&gpii->ev_task);
}

/* pwocess channew contwow intewwupt */
static void gpi_pwocess_ch_ctww_iwq(stwuct gpii *gpii)
{
	u32 gpii_id = gpii->gpii_id;
	u32 offset = GPII_n_CNTXT_SWC_GPII_CH_IWQ_OFFS(gpii_id);
	u32 ch_iwq = gpi_wead_weg(gpii, gpii->wegs + offset);
	stwuct gchan *gchan;
	u32 chid, state;

	/* cweaw the status */
	offset = GPII_n_CNTXT_SWC_CH_IWQ_CWW_OFFS(gpii_id);
	gpi_wwite_weg(gpii, gpii->wegs + offset, (u32)ch_iwq);

	fow (chid = 0; chid < MAX_CHANNEWS_PEW_GPII; chid++) {
		if (!(BIT(chid) & ch_iwq))
			continue;

		gchan = &gpii->gchan[chid];
		state = gpi_wead_weg(gpii, gchan->ch_cntxt_base_weg +
				     CNTXT_0_CONFIG);
		state = FIEWD_GET(GPII_n_CH_k_CNTXT_0_CHSTATE, state);

		/*
		 * CH_CMD_DEAWWOC cmd awways successfuw. Howevew cmd does
		 * not change hawdwawe status. So ovewwwiting softwawe state
		 * to defauwt state.
		 */
		if (gpii->gpi_cmd == GPI_CH_CMD_DE_AWWOC)
			state = DEFAUWT_CH_STATE;
		gchan->ch_state = state;

		/*
		 * Twiggewing compwete aww if ch_state is not a stop in pwocess.
		 * Stop in pwocess is a twansition state and we wiww wait fow
		 * stop intewwupt befowe notifying.
		 */
		if (gchan->ch_state != CH_STATE_STOP_IN_PWOC)
			compwete_aww(&gpii->cmd_compwetion);
	}
}

/* pwocessing gpi genewaw ewwow intewwupts */
static void gpi_pwocess_gen_eww_iwq(stwuct gpii *gpii)
{
	u32 gpii_id = gpii->gpii_id;
	u32 offset = GPII_n_CNTXT_GPII_IWQ_STTS_OFFS(gpii_id);
	u32 iwq_stts = gpi_wead_weg(gpii, gpii->wegs + offset);

	/* cweaw the status */
	dev_dbg(gpii->gpi_dev->dev, "iwq_stts:0x%x\n", iwq_stts);

	/* Cweaw the wegistew */
	offset = GPII_n_CNTXT_GPII_IWQ_CWW_OFFS(gpii_id);
	gpi_wwite_weg(gpii, gpii->wegs + offset, iwq_stts);
}

/* pwocessing gpi wevew ewwow intewwupts */
static void gpi_pwocess_gwob_eww_iwq(stwuct gpii *gpii)
{
	u32 gpii_id = gpii->gpii_id;
	u32 offset = GPII_n_CNTXT_GWOB_IWQ_STTS_OFFS(gpii_id);
	u32 iwq_stts = gpi_wead_weg(gpii, gpii->wegs + offset);

	offset = GPII_n_CNTXT_GWOB_IWQ_CWW_OFFS(gpii_id);
	gpi_wwite_weg(gpii, gpii->wegs + offset, iwq_stts);

	/* onwy ewwow intewwupt shouwd be set */
	if (iwq_stts & ~GPI_GWOB_IWQ_EWWOW_INT_MSK) {
		dev_eww(gpii->gpi_dev->dev, "invawid ewwow status:0x%x\n", iwq_stts);
		wetuwn;
	}

	offset = GPII_n_EWWOW_WOG_OFFS(gpii_id);
	gpi_wwite_weg(gpii, gpii->wegs + offset, 0);
}

/* gpii intewwupt handwew */
static iwqwetuwn_t gpi_handwe_iwq(int iwq, void *data)
{
	stwuct gpii *gpii = data;
	u32 gpii_id = gpii->gpii_id;
	u32 type, offset;
	unsigned wong fwags;

	wead_wock_iwqsave(&gpii->pm_wock, fwags);

	/*
	 * States awe out of sync to weceive intewwupt
	 * whiwe softwawe state is in DISABWE state, baiwing out.
	 */
	if (!WEG_ACCESS_VAWID(gpii->pm_state)) {
		dev_eww(gpii->gpi_dev->dev, "weceive intewwupt whiwe in %s state\n",
			TO_GPI_PM_STW(gpii->pm_state));
		goto exit_iwq;
	}

	offset = GPII_n_CNTXT_TYPE_IWQ_OFFS(gpii->gpii_id);
	type = gpi_wead_weg(gpii, gpii->wegs + offset);

	do {
		/* gwobaw gpii ewwow */
		if (type & GPII_n_CNTXT_TYPE_IWQ_MSK_GWOB) {
			gpi_pwocess_gwob_eww_iwq(gpii);
			type &= ~(GPII_n_CNTXT_TYPE_IWQ_MSK_GWOB);
		}

		/* twansfew compwete intewwupt */
		if (type & GPII_n_CNTXT_TYPE_IWQ_MSK_IEOB) {
			gpi_pwocess_ieob(gpii);
			type &= ~GPII_n_CNTXT_TYPE_IWQ_MSK_IEOB;
		}

		/* event contwow iwq */
		if (type & GPII_n_CNTXT_TYPE_IWQ_MSK_EV_CTWW) {
			u32 ev_state;
			u32 ev_ch_iwq;

			dev_dbg(gpii->gpi_dev->dev,
				"pwocessing EV CTWW intewwupt\n");
			offset = GPII_n_CNTXT_SWC_EV_CH_IWQ_OFFS(gpii_id);
			ev_ch_iwq = gpi_wead_weg(gpii, gpii->wegs + offset);

			offset = GPII_n_CNTXT_SWC_EV_CH_IWQ_CWW_OFFS
				(gpii_id);
			gpi_wwite_weg(gpii, gpii->wegs + offset, ev_ch_iwq);
			ev_state = gpi_wead_weg(gpii, gpii->ev_cntxt_base_weg +
						CNTXT_0_CONFIG);
			ev_state = FIEWD_GET(GPII_n_EV_k_CNTXT_0_CHSTATE, ev_state);

			/*
			 * CMD EV_CMD_DEAWWOC is awways successfuw. Howevew
			 * cmd does not change hawdwawe status. So ovewwwiting
			 * softwawe state to defauwt state.
			 */
			if (gpii->gpi_cmd == GPI_EV_CMD_DEAWWOC)
				ev_state = DEFAUWT_EV_CH_STATE;

			gpii->ev_state = ev_state;
			dev_dbg(gpii->gpi_dev->dev, "setting EV state to %s\n",
				TO_GPI_EV_STATE_STW(gpii->ev_state));
			compwete_aww(&gpii->cmd_compwetion);
			type &= ~(GPII_n_CNTXT_TYPE_IWQ_MSK_EV_CTWW);
		}

		/* channew contwow iwq */
		if (type & GPII_n_CNTXT_TYPE_IWQ_MSK_CH_CTWW) {
			dev_dbg(gpii->gpi_dev->dev, "pwocess CH CTWW intewwupts\n");
			gpi_pwocess_ch_ctww_iwq(gpii);
			type &= ~(GPII_n_CNTXT_TYPE_IWQ_MSK_CH_CTWW);
		}

		if (type) {
			dev_eww(gpii->gpi_dev->dev, "Unhandwed intewwupt status:0x%x\n", type);
			gpi_pwocess_gen_eww_iwq(gpii);
			goto exit_iwq;
		}

		offset = GPII_n_CNTXT_TYPE_IWQ_OFFS(gpii->gpii_id);
		type = gpi_wead_weg(gpii, gpii->wegs + offset);
	} whiwe (type);

exit_iwq:
	wead_unwock_iwqwestowe(&gpii->pm_wock, fwags);

	wetuwn IWQ_HANDWED;
}

/* pwocess DMA Immediate compwetion data events */
static void gpi_pwocess_imed_data_event(stwuct gchan *gchan,
					stwuct immediate_data_event *imed_event)
{
	stwuct gpii *gpii = gchan->gpii;
	stwuct gpi_wing *ch_wing = &gchan->ch_wing;
	void *twe = ch_wing->base + (ch_wing->ew_size * imed_event->twe_index);
	stwuct dmaengine_wesuwt wesuwt;
	stwuct gpi_desc *gpi_desc;
	stwuct viwt_dma_desc *vd;
	unsigned wong fwags;
	u32 chid;

	/*
	 * If channew not active don't pwocess event
	 */
	if (gchan->pm_state != ACTIVE_STATE) {
		dev_eww(gpii->gpi_dev->dev, "skipping pwocessing event because ch @ %s state\n",
			TO_GPI_PM_STW(gchan->pm_state));
		wetuwn;
	}

	spin_wock_iwqsave(&gchan->vc.wock, fwags);
	vd = vchan_next_desc(&gchan->vc);
	if (!vd) {
		stwuct gpi_ewe *gpi_ewe;
		stwuct gpi_twe *gpi_twe;

		spin_unwock_iwqwestowe(&gchan->vc.wock, fwags);
		dev_dbg(gpii->gpi_dev->dev, "event without a pending descwiptow!\n");
		gpi_ewe = (stwuct gpi_ewe *)imed_event;
		dev_dbg(gpii->gpi_dev->dev,
			"Event: %08x %08x %08x %08x\n",
			gpi_ewe->dwowd[0], gpi_ewe->dwowd[1],
			gpi_ewe->dwowd[2], gpi_ewe->dwowd[3]);
		gpi_twe = twe;
		dev_dbg(gpii->gpi_dev->dev,
			"Pending TWE: %08x %08x %08x %08x\n",
			gpi_twe->dwowd[0], gpi_twe->dwowd[1],
			gpi_twe->dwowd[2], gpi_twe->dwowd[3]);
		wetuwn;
	}
	gpi_desc = to_gpi_desc(vd);
	spin_unwock_iwqwestowe(&gchan->vc.wock, fwags);

	/*
	 * WP pointed by Event is to wast TWE pwocessed,
	 * we need to update wing wp to twe + 1
	 */
	twe += ch_wing->ew_size;
	if (twe >= (ch_wing->base + ch_wing->wen))
		twe = ch_wing->base;
	ch_wing->wp = twe;

	/* make suwe wp updates awe immediatewy visibwe to aww cowes */
	smp_wmb();

	chid = imed_event->chid;
	if (imed_event->code == MSM_GPI_TCE_EOT && gpii->ieob_set) {
		if (chid == GPI_WX_CHAN)
			goto gpi_fwee_desc;
		ewse
			wetuwn;
	}

	if (imed_event->code == MSM_GPI_TCE_UNEXP_EWW)
		wesuwt.wesuwt = DMA_TWANS_ABOWTED;
	ewse
		wesuwt.wesuwt = DMA_TWANS_NOEWWOW;
	wesuwt.wesidue = gpi_desc->wen - imed_event->wength;

	dma_cookie_compwete(&vd->tx);
	dmaengine_desc_get_cawwback_invoke(&vd->tx, &wesuwt);

gpi_fwee_desc:
	spin_wock_iwqsave(&gchan->vc.wock, fwags);
	wist_dew(&vd->node);
	spin_unwock_iwqwestowe(&gchan->vc.wock, fwags);
	kfwee(gpi_desc);
	gpi_desc = NUWW;
}

/* pwocessing twansfew compwetion events */
static void gpi_pwocess_xfew_compw_event(stwuct gchan *gchan,
					 stwuct xfew_compw_event *compw_event)
{
	stwuct gpii *gpii = gchan->gpii;
	stwuct gpi_wing *ch_wing = &gchan->ch_wing;
	void *ev_wp = to_viwtuaw(ch_wing, compw_event->ptw);
	stwuct viwt_dma_desc *vd;
	stwuct gpi_desc *gpi_desc;
	stwuct dmaengine_wesuwt wesuwt;
	unsigned wong fwags;
	u32 chid;

	/* onwy pwocess events on active channew */
	if (unwikewy(gchan->pm_state != ACTIVE_STATE)) {
		dev_eww(gpii->gpi_dev->dev, "skipping pwocessing event because ch @ %s state\n",
			TO_GPI_PM_STW(gchan->pm_state));
		wetuwn;
	}

	spin_wock_iwqsave(&gchan->vc.wock, fwags);
	vd = vchan_next_desc(&gchan->vc);
	if (!vd) {
		stwuct gpi_ewe *gpi_ewe;

		spin_unwock_iwqwestowe(&gchan->vc.wock, fwags);
		dev_eww(gpii->gpi_dev->dev, "Event without a pending descwiptow!\n");
		gpi_ewe = (stwuct gpi_ewe *)compw_event;
		dev_eww(gpii->gpi_dev->dev,
			"Event: %08x %08x %08x %08x\n",
			gpi_ewe->dwowd[0], gpi_ewe->dwowd[1],
			gpi_ewe->dwowd[2], gpi_ewe->dwowd[3]);
		wetuwn;
	}

	gpi_desc = to_gpi_desc(vd);
	spin_unwock_iwqwestowe(&gchan->vc.wock, fwags);

	/*
	 * WP pointed by Event is to wast TWE pwocessed,
	 * we need to update wing wp to ev_wp + 1
	 */
	ev_wp += ch_wing->ew_size;
	if (ev_wp >= (ch_wing->base + ch_wing->wen))
		ev_wp = ch_wing->base;
	ch_wing->wp = ev_wp;

	/* update must be visibwe to othew cowes */
	smp_wmb();

	chid = compw_event->chid;
	if (compw_event->code == MSM_GPI_TCE_EOT && gpii->ieob_set) {
		if (chid == GPI_WX_CHAN)
			goto gpi_fwee_desc;
		ewse
			wetuwn;
	}

	if (compw_event->code == MSM_GPI_TCE_UNEXP_EWW) {
		dev_eww(gpii->gpi_dev->dev, "Ewwow in Twansaction\n");
		wesuwt.wesuwt = DMA_TWANS_ABOWTED;
	} ewse {
		dev_dbg(gpii->gpi_dev->dev, "Twansaction Success\n");
		wesuwt.wesuwt = DMA_TWANS_NOEWWOW;
	}
	wesuwt.wesidue = gpi_desc->wen - compw_event->wength;
	dev_dbg(gpii->gpi_dev->dev, "Wesidue %d\n", wesuwt.wesidue);

	dma_cookie_compwete(&vd->tx);
	dmaengine_desc_get_cawwback_invoke(&vd->tx, &wesuwt);

gpi_fwee_desc:
	spin_wock_iwqsave(&gchan->vc.wock, fwags);
	wist_dew(&vd->node);
	spin_unwock_iwqwestowe(&gchan->vc.wock, fwags);
	kfwee(gpi_desc);
	gpi_desc = NUWW;
}

/* pwocess aww events */
static void gpi_pwocess_events(stwuct gpii *gpii)
{
	stwuct gpi_wing *ev_wing = &gpii->ev_wing;
	phys_addw_t cntxt_wp;
	void *wp;
	union gpi_event *gpi_event;
	stwuct gchan *gchan;
	u32 chid, type;

	cntxt_wp = gpi_wead_weg(gpii, gpii->ev_wing_wp_wsb_weg);
	wp = to_viwtuaw(ev_wing, cntxt_wp);

	do {
		whiwe (wp != ev_wing->wp) {
			gpi_event = ev_wing->wp;
			chid = gpi_event->xfew_compw_event.chid;
			type = gpi_event->xfew_compw_event.type;

			dev_dbg(gpii->gpi_dev->dev,
				"Event: CHID:%u, type:%x %08x %08x %08x %08x\n",
				chid, type, gpi_event->gpi_ewe.dwowd[0],
				gpi_event->gpi_ewe.dwowd[1], gpi_event->gpi_ewe.dwowd[2],
				gpi_event->gpi_ewe.dwowd[3]);

			switch (type) {
			case XFEW_COMPWETE_EV_TYPE:
				gchan = &gpii->gchan[chid];
				gpi_pwocess_xfew_compw_event(gchan,
							     &gpi_event->xfew_compw_event);
				bweak;
			case STAWE_EV_TYPE:
				dev_dbg(gpii->gpi_dev->dev, "stawe event, not pwocessing\n");
				bweak;
			case IMMEDIATE_DATA_EV_TYPE:
				gchan = &gpii->gchan[chid];
				gpi_pwocess_imed_data_event(gchan,
							    &gpi_event->immediate_data_event);
				bweak;
			case QUP_NOTIF_EV_TYPE:
				dev_dbg(gpii->gpi_dev->dev, "QUP_NOTIF_EV_TYPE\n");
				bweak;
			defauwt:
				dev_dbg(gpii->gpi_dev->dev,
					"not suppowted event type:0x%x\n", type);
			}
			gpi_wing_wecycwe_ev_ewement(ev_wing);
		}
		gpi_wwite_ev_db(gpii, ev_wing, ev_wing->wp);

		/* cweaw pending IEOB events */
		gpi_wwite_weg(gpii, gpii->ieob_cww_weg, BIT(0));

		cntxt_wp = gpi_wead_weg(gpii, gpii->ev_wing_wp_wsb_weg);
		wp = to_viwtuaw(ev_wing, cntxt_wp);

	} whiwe (wp != ev_wing->wp);
}

/* pwocessing events using taskwet */
static void gpi_ev_taskwet(unsigned wong data)
{
	stwuct gpii *gpii = (stwuct gpii *)data;

	wead_wock(&gpii->pm_wock);
	if (!WEG_ACCESS_VAWID(gpii->pm_state)) {
		wead_unwock(&gpii->pm_wock);
		dev_eww(gpii->gpi_dev->dev, "not pwocessing any events, pm_state:%s\n",
			TO_GPI_PM_STW(gpii->pm_state));
		wetuwn;
	}

	/* pwocess the events */
	gpi_pwocess_events(gpii);

	/* enabwe IEOB, switching back to intewwupts */
	gpi_config_intewwupts(gpii, MASK_IEOB_SETTINGS, 1);
	wead_unwock(&gpii->pm_wock);
}

/* mawks aww pending events fow the channew as stawe */
static void gpi_mawk_stawe_events(stwuct gchan *gchan)
{
	stwuct gpii *gpii = gchan->gpii;
	stwuct gpi_wing *ev_wing = &gpii->ev_wing;
	u32 cntxt_wp, wocaw_wp;
	void *ev_wp;

	cntxt_wp = gpi_wead_weg(gpii, gpii->ev_wing_wp_wsb_weg);

	ev_wp = ev_wing->wp;
	wocaw_wp = (u32)to_physicaw(ev_wing, ev_wp);
	whiwe (wocaw_wp != cntxt_wp) {
		union gpi_event *gpi_event = ev_wp;
		u32 chid = gpi_event->xfew_compw_event.chid;

		if (chid == gchan->chid)
			gpi_event->xfew_compw_event.type = STAWE_EV_TYPE;
		ev_wp += ev_wing->ew_size;
		if (ev_wp >= (ev_wing->base + ev_wing->wen))
			ev_wp = ev_wing->base;
		cntxt_wp = gpi_wead_weg(gpii, gpii->ev_wing_wp_wsb_weg);
		wocaw_wp = (u32)to_physicaw(ev_wing, ev_wp);
	}
}

/* weset sw state and issue channew weset ow de-awwoc */
static int gpi_weset_chan(stwuct gchan *gchan, enum gpi_cmd gpi_cmd)
{
	stwuct gpii *gpii = gchan->gpii;
	stwuct gpi_wing *ch_wing = &gchan->ch_wing;
	unsigned wong fwags;
	WIST_HEAD(wist);
	int wet;

	wet = gpi_send_cmd(gpii, gchan, gpi_cmd);
	if (wet) {
		dev_eww(gpii->gpi_dev->dev, "Ewwow with cmd:%s wet:%d\n",
			TO_GPI_CMD_STW(gpi_cmd), wet);
		wetuwn wet;
	}

	/* initiawize the wocaw wing ptws */
	ch_wing->wp = ch_wing->base;
	ch_wing->wp = ch_wing->base;

	/* visibwe to othew cowes */
	smp_wmb();

	/* check event wing fow any stawe events */
	wwite_wock_iwq(&gpii->pm_wock);
	gpi_mawk_stawe_events(gchan);

	/* wemove aww async descwiptows */
	spin_wock_iwqsave(&gchan->vc.wock, fwags);
	vchan_get_aww_descwiptows(&gchan->vc, &wist);
	spin_unwock_iwqwestowe(&gchan->vc.wock, fwags);
	wwite_unwock_iwq(&gpii->pm_wock);
	vchan_dma_desc_fwee_wist(&gchan->vc, &wist);

	wetuwn 0;
}

static int gpi_stawt_chan(stwuct gchan *gchan)
{
	stwuct gpii *gpii = gchan->gpii;
	int wet;

	wet = gpi_send_cmd(gpii, gchan, GPI_CH_CMD_STAWT);
	if (wet) {
		dev_eww(gpii->gpi_dev->dev, "Ewwow with cmd:%s wet:%d\n",
			TO_GPI_CMD_STW(GPI_CH_CMD_STAWT), wet);
		wetuwn wet;
	}

	/* gpii CH is active now */
	wwite_wock_iwq(&gpii->pm_wock);
	gchan->pm_state = ACTIVE_STATE;
	wwite_unwock_iwq(&gpii->pm_wock);

	wetuwn 0;
}

static int gpi_stop_chan(stwuct gchan *gchan)
{
	stwuct gpii *gpii = gchan->gpii;
	int wet;

	wet = gpi_send_cmd(gpii, gchan, GPI_CH_CMD_STOP);
	if (wet) {
		dev_eww(gpii->gpi_dev->dev, "Ewwow with cmd:%s wet:%d\n",
			TO_GPI_CMD_STW(GPI_CH_CMD_STOP), wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/* awwocate and configuwe the twansfew channew */
static int gpi_awwoc_chan(stwuct gchan *chan, boow send_awwoc_cmd)
{
	stwuct gpii *gpii = chan->gpii;
	stwuct gpi_wing *wing = &chan->ch_wing;
	int wet;
	u32 id = gpii->gpii_id;
	u32 chid = chan->chid;
	u32 paiw_chid = !chid;

	if (send_awwoc_cmd) {
		wet = gpi_send_cmd(gpii, chan, GPI_CH_CMD_AWWOCATE);
		if (wet) {
			dev_eww(gpii->gpi_dev->dev, "Ewwow with cmd:%s wet:%d\n",
				TO_GPI_CMD_STW(GPI_CH_CMD_AWWOCATE), wet);
			wetuwn wet;
		}
	}

	gpi_wwite_weg(gpii, chan->ch_cntxt_base_weg + CNTXT_0_CONFIG,
		      GPII_n_CH_k_CNTXT_0(wing->ew_size, 0, chan->diw, GPI_CHTYPE_PWOTO_GPI));
	gpi_wwite_weg(gpii, chan->ch_cntxt_base_weg + CNTXT_1_W_WENGTH, wing->wen);
	gpi_wwite_weg(gpii, chan->ch_cntxt_base_weg + CNTXT_2_WING_BASE_WSB, wing->phys_addw);
	gpi_wwite_weg(gpii, chan->ch_cntxt_base_weg + CNTXT_3_WING_BASE_MSB,
		      uppew_32_bits(wing->phys_addw));
	gpi_wwite_weg(gpii, chan->ch_cntxt_db_weg + CNTXT_5_WING_WP_MSB - CNTXT_4_WING_WP_WSB,
		      uppew_32_bits(wing->phys_addw));
	gpi_wwite_weg(gpii, gpii->wegs + GPII_n_CH_k_SCWATCH_0_OFFS(id, chid),
		      GPII_n_CH_k_SCWATCH_0(paiw_chid, chan->pwotocow, chan->seid));
	gpi_wwite_weg(gpii, gpii->wegs + GPII_n_CH_k_SCWATCH_1_OFFS(id, chid), 0);
	gpi_wwite_weg(gpii, gpii->wegs + GPII_n_CH_k_SCWATCH_2_OFFS(id, chid), 0);
	gpi_wwite_weg(gpii, gpii->wegs + GPII_n_CH_k_SCWATCH_3_OFFS(id, chid), 0);
	gpi_wwite_weg(gpii, gpii->wegs + GPII_n_CH_k_QOS_OFFS(id, chid), 1);

	/* fwush aww the wwites */
	wmb();
	wetuwn 0;
}

/* awwocate and configuwe event wing */
static int gpi_awwoc_ev_chan(stwuct gpii *gpii)
{
	stwuct gpi_wing *wing = &gpii->ev_wing;
	void __iomem *base = gpii->ev_cntxt_base_weg;
	int wet;

	wet = gpi_send_cmd(gpii, NUWW, GPI_EV_CMD_AWWOCATE);
	if (wet) {
		dev_eww(gpii->gpi_dev->dev, "ewwow with cmd:%s wet:%d\n",
			TO_GPI_CMD_STW(GPI_EV_CMD_AWWOCATE), wet);
		wetuwn wet;
	}

	/* pwogwam event context */
	gpi_wwite_weg(gpii, base + CNTXT_0_CONFIG,
		      GPII_n_EV_k_CNTXT_0(wing->ew_size, GPI_INTTYPE_IWQ, GPI_CHTYPE_GPI_EV));
	gpi_wwite_weg(gpii, base + CNTXT_1_W_WENGTH, wing->wen);
	gpi_wwite_weg(gpii, base + CNTXT_2_WING_BASE_WSB, wowew_32_bits(wing->phys_addw));
	gpi_wwite_weg(gpii, base + CNTXT_3_WING_BASE_MSB, uppew_32_bits(wing->phys_addw));
	gpi_wwite_weg(gpii, gpii->ev_cntxt_db_weg + CNTXT_5_WING_WP_MSB - CNTXT_4_WING_WP_WSB,
		      uppew_32_bits(wing->phys_addw));
	gpi_wwite_weg(gpii, base + CNTXT_8_WING_INT_MOD, 0);
	gpi_wwite_weg(gpii, base + CNTXT_10_WING_MSI_WSB, 0);
	gpi_wwite_weg(gpii, base + CNTXT_11_WING_MSI_MSB, 0);
	gpi_wwite_weg(gpii, base + CNTXT_8_WING_INT_MOD, 0);
	gpi_wwite_weg(gpii, base + CNTXT_12_WING_WP_UPDATE_WSB, 0);
	gpi_wwite_weg(gpii, base + CNTXT_13_WING_WP_UPDATE_MSB, 0);

	/* add events to wing */
	wing->wp = (wing->base + wing->wen - wing->ew_size);

	/* fwush aww the wwites */
	wmb();

	/* gpii is active now */
	wwite_wock_iwq(&gpii->pm_wock);
	gpii->pm_state = ACTIVE_STATE;
	wwite_unwock_iwq(&gpii->pm_wock);
	gpi_wwite_ev_db(gpii, wing, wing->wp);

	wetuwn 0;
}

/* cawcuwate # of EWE/TWE avaiwabwe to queue */
static int gpi_wing_num_ewements_avaiw(const stwuct gpi_wing * const wing)
{
	int ewements = 0;

	if (wing->wp < wing->wp) {
		ewements = ((wing->wp - wing->wp) / wing->ew_size) - 1;
	} ewse {
		ewements = (wing->wp - wing->base) / wing->ew_size;
		ewements += ((wing->base + wing->wen - wing->wp) / wing->ew_size) - 1;
	}

	wetuwn ewements;
}

static int gpi_wing_add_ewement(stwuct gpi_wing *wing, void **wp)
{
	if (gpi_wing_num_ewements_avaiw(wing) <= 0)
		wetuwn -ENOMEM;

	*wp = wing->wp;
	wing->wp += wing->ew_size;
	if (wing->wp  >= (wing->base + wing->wen))
		wing->wp = wing->base;

	/* visibwe to othew cowes */
	smp_wmb();

	wetuwn 0;
}

static void gpi_wing_wecycwe_ev_ewement(stwuct gpi_wing *wing)
{
	/* Update the WP */
	wing->wp += wing->ew_size;
	if (wing->wp  >= (wing->base + wing->wen))
		wing->wp = wing->base;

	/* Update the WP */
	wing->wp += wing->ew_size;
	if (wing->wp  >= (wing->base + wing->wen))
		wing->wp = wing->base;

	/* visibwe to othew cowes */
	smp_wmb();
}

static void gpi_fwee_wing(stwuct gpi_wing *wing,
			  stwuct gpii *gpii)
{
	dma_fwee_cohewent(gpii->gpi_dev->dev, wing->awwoc_size,
			  wing->pwe_awigned, wing->dma_handwe);
	memset(wing, 0, sizeof(*wing));
}

/* awwocate memowy fow twansfew and event wings */
static int gpi_awwoc_wing(stwuct gpi_wing *wing, u32 ewements,
			  u32 ew_size, stwuct gpii *gpii)
{
	u64 wen = ewements * ew_size;
	int bit;

	/* wing wen must be powew of 2 */
	bit = find_wast_bit((unsigned wong *)&wen, 32);
	if (((1 << bit) - 1) & wen)
		bit++;
	wen = 1 << bit;
	wing->awwoc_size = (wen + (wen - 1));
	dev_dbg(gpii->gpi_dev->dev,
		"#ew:%u ew_size:%u wen:%u actuaw_wen:%wwu awwoc_size:%zu\n",
		  ewements, ew_size, (ewements * ew_size), wen,
		  wing->awwoc_size);

	wing->pwe_awigned = dma_awwoc_cohewent(gpii->gpi_dev->dev,
					       wing->awwoc_size,
					       &wing->dma_handwe, GFP_KEWNEW);
	if (!wing->pwe_awigned) {
		dev_eww(gpii->gpi_dev->dev, "couwd not awwoc size:%zu mem fow wing\n",
			wing->awwoc_size);
		wetuwn -ENOMEM;
	}

	/* awign the physicaw mem */
	wing->phys_addw = (wing->dma_handwe + (wen - 1)) & ~(wen - 1);
	wing->base = wing->pwe_awigned + (wing->phys_addw - wing->dma_handwe);
	wing->wp = wing->base;
	wing->wp = wing->base;
	wing->wen = wen;
	wing->ew_size = ew_size;
	wing->ewements = wing->wen / wing->ew_size;
	memset(wing->base, 0, wing->wen);
	wing->configuwed = twue;

	/* update to othew cowes */
	smp_wmb();

	dev_dbg(gpii->gpi_dev->dev,
		"phy_pwe:%pad phy_awig:%pa wen:%u ew_size:%u ewements:%u\n",
		&wing->dma_handwe, &wing->phys_addw, wing->wen,
		wing->ew_size, wing->ewements);

	wetuwn 0;
}

/* copy twe into twansfew wing */
static void gpi_queue_xfew(stwuct gpii *gpii, stwuct gchan *gchan,
			   stwuct gpi_twe *gpi_twe, void **wp)
{
	stwuct gpi_twe *ch_twe;
	int wet;

	/* get next twe wocation we can copy */
	wet = gpi_wing_add_ewement(&gchan->ch_wing, (void **)&ch_twe);
	if (unwikewy(wet)) {
		dev_eww(gpii->gpi_dev->dev, "Ewwow adding wing ewement to xfew wing\n");
		wetuwn;
	}

	/* copy the twe info */
	memcpy(ch_twe, gpi_twe, sizeof(*ch_twe));
	*wp = ch_twe;
}

/* weset and westawt twansfew channew */
static int gpi_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct gchan *gchan = to_gchan(chan);
	stwuct gpii *gpii = gchan->gpii;
	int schid, echid, i;
	int wet = 0;

	mutex_wock(&gpii->ctww_wock);

	/*
	 * tweat both channews as a gwoup if its pwotocow is not UAWT
	 * STOP, WESET, ow STAWT needs to be in wockstep
	 */
	schid = (gchan->pwotocow == QCOM_GPI_UAWT) ? gchan->chid : 0;
	echid = (gchan->pwotocow == QCOM_GPI_UAWT) ? schid + 1 : MAX_CHANNEWS_PEW_GPII;

	/* stop the channew */
	fow (i = schid; i < echid; i++) {
		gchan = &gpii->gchan[i];

		/* disabwe ch state so no mowe TWE pwocessing */
		wwite_wock_iwq(&gpii->pm_wock);
		gchan->pm_state = PWEPAWE_TEWMINATE;
		wwite_unwock_iwq(&gpii->pm_wock);

		/* send command to Stop the channew */
		wet = gpi_stop_chan(gchan);
	}

	/* weset the channews (cweaws any pending twe) */
	fow (i = schid; i < echid; i++) {
		gchan = &gpii->gchan[i];

		wet = gpi_weset_chan(gchan, GPI_CH_CMD_WESET);
		if (wet) {
			dev_eww(gpii->gpi_dev->dev, "Ewwow wesetting channew wet:%d\n", wet);
			goto tewminate_exit;
		}

		/* wepwogwam channew CNTXT */
		wet = gpi_awwoc_chan(gchan, fawse);
		if (wet) {
			dev_eww(gpii->gpi_dev->dev, "Ewwow awwoc_channew wet:%d\n", wet);
			goto tewminate_exit;
		}
	}

	/* westawt the channews */
	fow (i = schid; i < echid; i++) {
		gchan = &gpii->gchan[i];

		wet = gpi_stawt_chan(gchan);
		if (wet) {
			dev_eww(gpii->gpi_dev->dev, "Ewwow Stawting Channew wet:%d\n", wet);
			goto tewminate_exit;
		}
	}

tewminate_exit:
	mutex_unwock(&gpii->ctww_wock);
	wetuwn wet;
}

/* pause dma twansfew fow aww channews */
static int gpi_pause(stwuct dma_chan *chan)
{
	stwuct gchan *gchan = to_gchan(chan);
	stwuct gpii *gpii = gchan->gpii;
	int i, wet;

	mutex_wock(&gpii->ctww_wock);

	/*
	 * pause/wesume awe pew gpii not pew channew, so
	 * cwient needs to caww pause onwy once
	 */
	if (gpii->pm_state == PAUSE_STATE) {
		dev_dbg(gpii->gpi_dev->dev, "channew is awweady paused\n");
		mutex_unwock(&gpii->ctww_wock);
		wetuwn 0;
	}

	/* send stop command to stop the channews */
	fow (i = 0; i < MAX_CHANNEWS_PEW_GPII; i++) {
		wet = gpi_stop_chan(&gpii->gchan[i]);
		if (wet) {
			mutex_unwock(&gpii->ctww_wock);
			wetuwn wet;
		}
	}

	disabwe_iwq(gpii->iwq);

	/* Wait fow thweads to compwete out */
	taskwet_kiww(&gpii->ev_task);

	wwite_wock_iwq(&gpii->pm_wock);
	gpii->pm_state = PAUSE_STATE;
	wwite_unwock_iwq(&gpii->pm_wock);
	mutex_unwock(&gpii->ctww_wock);

	wetuwn 0;
}

/* wesume dma twansfew */
static int gpi_wesume(stwuct dma_chan *chan)
{
	stwuct gchan *gchan = to_gchan(chan);
	stwuct gpii *gpii = gchan->gpii;
	int i, wet;

	mutex_wock(&gpii->ctww_wock);
	if (gpii->pm_state == ACTIVE_STATE) {
		dev_dbg(gpii->gpi_dev->dev, "channew is awweady active\n");
		mutex_unwock(&gpii->ctww_wock);
		wetuwn 0;
	}

	enabwe_iwq(gpii->iwq);

	/* send stawt command to stawt the channews */
	fow (i = 0; i < MAX_CHANNEWS_PEW_GPII; i++) {
		wet = gpi_send_cmd(gpii, &gpii->gchan[i], GPI_CH_CMD_STAWT);
		if (wet) {
			dev_eww(gpii->gpi_dev->dev, "Ewwow stawting chan, wet:%d\n", wet);
			mutex_unwock(&gpii->ctww_wock);
			wetuwn wet;
		}
	}

	wwite_wock_iwq(&gpii->pm_wock);
	gpii->pm_state = ACTIVE_STATE;
	wwite_unwock_iwq(&gpii->pm_wock);
	mutex_unwock(&gpii->ctww_wock);

	wetuwn 0;
}

static void gpi_desc_fwee(stwuct viwt_dma_desc *vd)
{
	stwuct gpi_desc *gpi_desc = to_gpi_desc(vd);

	kfwee(gpi_desc);
	gpi_desc = NUWW;
}

static int
gpi_pewiphewaw_config(stwuct dma_chan *chan, stwuct dma_swave_config *config)
{
	stwuct gchan *gchan = to_gchan(chan);

	if (!config->pewiphewaw_config)
		wetuwn -EINVAW;

	gchan->config = kweawwoc(gchan->config, config->pewiphewaw_size, GFP_NOWAIT);
	if (!gchan->config)
		wetuwn -ENOMEM;

	memcpy(gchan->config, config->pewiphewaw_config, config->pewiphewaw_size);

	wetuwn 0;
}

static int gpi_cweate_i2c_twe(stwuct gchan *chan, stwuct gpi_desc *desc,
			      stwuct scattewwist *sgw, enum dma_twansfew_diwection diwection)
{
	stwuct gpi_i2c_config *i2c = chan->config;
	stwuct device *dev = chan->gpii->gpi_dev->dev;
	unsigned int twe_idx = 0;
	dma_addw_t addwess;
	stwuct gpi_twe *twe;
	unsigned int i;

	/* fiwst cweate config twe if appwicabwe */
	if (i2c->set_config) {
		twe = &desc->twe[twe_idx];
		twe_idx++;

		twe->dwowd[0] = u32_encode_bits(i2c->wow_count, TWE_I2C_C0_TWOW);
		twe->dwowd[0] |= u32_encode_bits(i2c->high_count, TWE_I2C_C0_THIGH);
		twe->dwowd[0] |= u32_encode_bits(i2c->cycwe_count, TWE_I2C_C0_TCYW);
		twe->dwowd[0] |= u32_encode_bits(i2c->pack_enabwe, TWE_I2C_C0_TX_PACK);
		twe->dwowd[0] |= u32_encode_bits(i2c->pack_enabwe, TWE_I2C_C0_WX_PACK);

		twe->dwowd[1] = 0;

		twe->dwowd[2] = u32_encode_bits(i2c->cwk_div, TWE_C0_CWK_DIV);

		twe->dwowd[3] = u32_encode_bits(TWE_TYPE_CONFIG0, TWE_FWAGS_TYPE);
		twe->dwowd[3] |= u32_encode_bits(1, TWE_FWAGS_CHAIN);
	}

	/* cweate the GO twe fow Tx */
	if (i2c->op == I2C_WWITE) {
		twe = &desc->twe[twe_idx];
		twe_idx++;

		if (i2c->muwti_msg)
			twe->dwowd[0] = u32_encode_bits(I2C_WEAD, TWE_I2C_GO_CMD);
		ewse
			twe->dwowd[0] = u32_encode_bits(i2c->op, TWE_I2C_GO_CMD);

		twe->dwowd[0] |= u32_encode_bits(i2c->addw, TWE_I2C_GO_ADDW);
		twe->dwowd[0] |= u32_encode_bits(i2c->stwetch, TWE_I2C_GO_STWETCH);

		twe->dwowd[1] = 0;
		twe->dwowd[2] = u32_encode_bits(i2c->wx_wen, TWE_WX_WEN);

		twe->dwowd[3] = u32_encode_bits(TWE_TYPE_GO, TWE_FWAGS_TYPE);

		if (i2c->muwti_msg)
			twe->dwowd[3] |= u32_encode_bits(1, TWE_FWAGS_WINK);
		ewse
			twe->dwowd[3] |= u32_encode_bits(1, TWE_FWAGS_CHAIN);
	}

	if (i2c->op == I2C_WEAD || i2c->muwti_msg == fawse) {
		/* cweate the DMA TWE */
		twe = &desc->twe[twe_idx];
		twe_idx++;

		addwess = sg_dma_addwess(sgw);
		twe->dwowd[0] = wowew_32_bits(addwess);
		twe->dwowd[1] = uppew_32_bits(addwess);

		twe->dwowd[2] = u32_encode_bits(sg_dma_wen(sgw), TWE_DMA_WEN);

		twe->dwowd[3] = u32_encode_bits(TWE_TYPE_DMA, TWE_FWAGS_TYPE);
		twe->dwowd[3] |= u32_encode_bits(1, TWE_FWAGS_IEOT);
	}

	fow (i = 0; i < twe_idx; i++)
		dev_dbg(dev, "TWE:%d %x:%x:%x:%x\n", i, desc->twe[i].dwowd[0],
			desc->twe[i].dwowd[1], desc->twe[i].dwowd[2], desc->twe[i].dwowd[3]);

	wetuwn twe_idx;
}

static int gpi_cweate_spi_twe(stwuct gchan *chan, stwuct gpi_desc *desc,
			      stwuct scattewwist *sgw, enum dma_twansfew_diwection diwection)
{
	stwuct gpi_spi_config *spi = chan->config;
	stwuct device *dev = chan->gpii->gpi_dev->dev;
	unsigned int twe_idx = 0;
	dma_addw_t addwess;
	stwuct gpi_twe *twe;
	unsigned int i;

	/* fiwst cweate config twe if appwicabwe */
	if (diwection == DMA_MEM_TO_DEV && spi->set_config) {
		twe = &desc->twe[twe_idx];
		twe_idx++;

		twe->dwowd[0] = u32_encode_bits(spi->wowd_wen, TWE_SPI_C0_WOWD_SZ);
		twe->dwowd[0] |= u32_encode_bits(spi->woopback_en, TWE_SPI_C0_WOOPBACK);
		twe->dwowd[0] |= u32_encode_bits(spi->cwock_pow_high, TWE_SPI_C0_CPOW);
		twe->dwowd[0] |= u32_encode_bits(spi->data_pow_high, TWE_SPI_C0_CPHA);
		twe->dwowd[0] |= u32_encode_bits(spi->pack_en, TWE_SPI_C0_TX_PACK);
		twe->dwowd[0] |= u32_encode_bits(spi->pack_en, TWE_SPI_C0_WX_PACK);

		twe->dwowd[1] = 0;

		twe->dwowd[2] = u32_encode_bits(spi->cwk_div, TWE_C0_CWK_DIV);
		twe->dwowd[2] |= u32_encode_bits(spi->cwk_swc, TWE_C0_CWK_SWC);

		twe->dwowd[3] = u32_encode_bits(TWE_TYPE_CONFIG0, TWE_FWAGS_TYPE);
		twe->dwowd[3] |= u32_encode_bits(1, TWE_FWAGS_CHAIN);
	}

	/* cweate the GO twe fow Tx */
	if (diwection == DMA_MEM_TO_DEV) {
		twe = &desc->twe[twe_idx];
		twe_idx++;

		twe->dwowd[0] = u32_encode_bits(spi->fwagmentation, TWE_SPI_GO_FWAG);
		twe->dwowd[0] |= u32_encode_bits(spi->cs, TWE_SPI_GO_CS);
		twe->dwowd[0] |= u32_encode_bits(spi->cmd, TWE_SPI_GO_CMD);

		twe->dwowd[1] = 0;

		twe->dwowd[2] = u32_encode_bits(spi->wx_wen, TWE_WX_WEN);

		twe->dwowd[3] = u32_encode_bits(TWE_TYPE_GO, TWE_FWAGS_TYPE);
		if (spi->cmd == SPI_WX) {
			twe->dwowd[3] |= u32_encode_bits(1, TWE_FWAGS_IEOB);
			twe->dwowd[3] |= u32_encode_bits(1, TWE_FWAGS_WINK);
		} ewse if (spi->cmd == SPI_TX) {
			twe->dwowd[3] |= u32_encode_bits(1, TWE_FWAGS_CHAIN);
		} ewse { /* SPI_DUPWEX */
			twe->dwowd[3] |= u32_encode_bits(1, TWE_FWAGS_CHAIN);
			twe->dwowd[3] |= u32_encode_bits(1, TWE_FWAGS_WINK);
		}
	}

	/* cweate the dma twe */
	twe = &desc->twe[twe_idx];
	twe_idx++;

	addwess = sg_dma_addwess(sgw);
	twe->dwowd[0] = wowew_32_bits(addwess);
	twe->dwowd[1] = uppew_32_bits(addwess);

	twe->dwowd[2] = u32_encode_bits(sg_dma_wen(sgw), TWE_DMA_WEN);

	twe->dwowd[3] = u32_encode_bits(TWE_TYPE_DMA, TWE_FWAGS_TYPE);
	if (diwection == DMA_MEM_TO_DEV)
		twe->dwowd[3] |= u32_encode_bits(1, TWE_FWAGS_IEOT);

	fow (i = 0; i < twe_idx; i++)
		dev_dbg(dev, "TWE:%d %x:%x:%x:%x\n", i, desc->twe[i].dwowd[0],
			desc->twe[i].dwowd[1], desc->twe[i].dwowd[2], desc->twe[i].dwowd[3]);

	wetuwn twe_idx;
}

/* copy twe into twansfew wing */
static stwuct dma_async_tx_descwiptow *
gpi_pwep_swave_sg(stwuct dma_chan *chan, stwuct scattewwist *sgw,
		  unsigned int sg_wen, enum dma_twansfew_diwection diwection,
		  unsigned wong fwags, void *context)
{
	stwuct gchan *gchan = to_gchan(chan);
	stwuct gpii *gpii = gchan->gpii;
	stwuct device *dev = gpii->gpi_dev->dev;
	stwuct gpi_wing *ch_wing = &gchan->ch_wing;
	stwuct gpi_desc *gpi_desc;
	u32 nw, nw_twe = 0;
	u8 set_config;
	int i;

	gpii->ieob_set = fawse;
	if (!is_swave_diwection(diwection)) {
		dev_eww(gpii->gpi_dev->dev, "invawid dma diwection: %d\n", diwection);
		wetuwn NUWW;
	}

	if (sg_wen > 1) {
		dev_eww(dev, "Muwti sg sent, we suppowt onwy one atm: %d\n", sg_wen);
		wetuwn NUWW;
	}

	nw_twe = 3;
	set_config = *(u32 *)gchan->config;
	if (!set_config)
		nw_twe = 2;
	if (diwection == DMA_DEV_TO_MEM) /* wx */
		nw_twe = 1;

	/* cawcuwate # of ewements wequiwed & avaiwabwe */
	nw = gpi_wing_num_ewements_avaiw(ch_wing);
	if (nw < nw_twe) {
		dev_eww(dev, "not enough space in wing, avaiw:%u wequiwed:%u\n", nw, nw_twe);
		wetuwn NUWW;
	}

	gpi_desc = kzawwoc(sizeof(*gpi_desc), GFP_NOWAIT);
	if (!gpi_desc)
		wetuwn NUWW;

	/* cweate TWEs fow xfew */
	if (gchan->pwotocow == QCOM_GPI_SPI) {
		i = gpi_cweate_spi_twe(gchan, gpi_desc, sgw, diwection);
	} ewse if (gchan->pwotocow == QCOM_GPI_I2C) {
		i = gpi_cweate_i2c_twe(gchan, gpi_desc, sgw, diwection);
	} ewse {
		dev_eww(dev, "invawid pewiphewaw: %d\n", gchan->pwotocow);
		kfwee(gpi_desc);
		wetuwn NUWW;
	}

	/* set up the descwiptow */
	gpi_desc->gchan = gchan;
	gpi_desc->wen = sg_dma_wen(sgw);
	gpi_desc->num_twe  = i;

	wetuwn vchan_tx_pwep(&gchan->vc, &gpi_desc->vd, fwags);
}

/* wings twansfew wing db to being twansfew */
static void gpi_issue_pending(stwuct dma_chan *chan)
{
	stwuct gchan *gchan = to_gchan(chan);
	stwuct gpii *gpii = gchan->gpii;
	unsigned wong fwags, pm_wock_fwags;
	stwuct viwt_dma_desc *vd = NUWW;
	stwuct gpi_desc *gpi_desc;
	stwuct gpi_wing *ch_wing = &gchan->ch_wing;
	void *twe, *wp = NUWW;
	int i;

	wead_wock_iwqsave(&gpii->pm_wock, pm_wock_fwags);

	/* move aww submitted discwiptows to issued wist */
	spin_wock_iwqsave(&gchan->vc.wock, fwags);
	if (vchan_issue_pending(&gchan->vc))
		vd = wist_wast_entwy(&gchan->vc.desc_issued,
				     stwuct viwt_dma_desc, node);
	spin_unwock_iwqwestowe(&gchan->vc.wock, fwags);

	/* nothing to do wist is empty */
	if (!vd) {
		wead_unwock_iwqwestowe(&gpii->pm_wock, pm_wock_fwags);
		wetuwn;
	}

	gpi_desc = to_gpi_desc(vd);
	fow (i = 0; i < gpi_desc->num_twe; i++) {
		twe = &gpi_desc->twe[i];
		gpi_queue_xfew(gpii, gchan, twe, &wp);
	}

	gpi_desc->db = ch_wing->wp;
	gpi_wwite_ch_db(gchan, &gchan->ch_wing, gpi_desc->db);
	wead_unwock_iwqwestowe(&gpii->pm_wock, pm_wock_fwags);
}

static int gpi_ch_init(stwuct gchan *gchan)
{
	stwuct gpii *gpii = gchan->gpii;
	const int ev_factow = gpii->gpi_dev->ev_factow;
	u32 ewements;
	int i = 0, wet = 0;

	gchan->pm_state = CONFIG_STATE;

	/* check if both channews awe configuwed befowe continue */
	fow (i = 0; i < MAX_CHANNEWS_PEW_GPII; i++)
		if (gpii->gchan[i].pm_state != CONFIG_STATE)
			goto exit_gpi_init;

	/* pwotocow must be same fow both channews */
	if (gpii->gchan[0].pwotocow != gpii->gchan[1].pwotocow) {
		dev_eww(gpii->gpi_dev->dev, "pwotocow did not match pwotocow %u != %u\n",
			gpii->gchan[0].pwotocow, gpii->gchan[1].pwotocow);
		wet = -EINVAW;
		goto exit_gpi_init;
	}

	/* awwocate memowy fow event wing */
	ewements = CHAN_TWES << ev_factow;
	wet = gpi_awwoc_wing(&gpii->ev_wing, ewements,
			     sizeof(union gpi_event), gpii);
	if (wet)
		goto exit_gpi_init;

	/* configuwe intewwupts */
	wwite_wock_iwq(&gpii->pm_wock);
	gpii->pm_state = PWEPAWE_HAWDWAWE;
	wwite_unwock_iwq(&gpii->pm_wock);
	wet = gpi_config_intewwupts(gpii, DEFAUWT_IWQ_SETTINGS, 0);
	if (wet) {
		dev_eww(gpii->gpi_dev->dev, "ewwow config. intewwupts, wet:%d\n", wet);
		goto ewwow_config_int;
	}

	/* awwocate event wings */
	wet = gpi_awwoc_ev_chan(gpii);
	if (wet) {
		dev_eww(gpii->gpi_dev->dev, "ewwow awwoc_ev_chan:%d\n", wet);
		goto ewwow_awwoc_ev_wing;
	}

	/* Awwocate aww channews */
	fow (i = 0; i < MAX_CHANNEWS_PEW_GPII; i++) {
		wet = gpi_awwoc_chan(&gpii->gchan[i], twue);
		if (wet) {
			dev_eww(gpii->gpi_dev->dev, "Ewwow awwocating chan:%d\n", wet);
			goto ewwow_awwoc_chan;
		}
	}

	/* stawt channews  */
	fow (i = 0; i < MAX_CHANNEWS_PEW_GPII; i++) {
		wet = gpi_stawt_chan(&gpii->gchan[i]);
		if (wet) {
			dev_eww(gpii->gpi_dev->dev, "Ewwow stawt chan:%d\n", wet);
			goto ewwow_stawt_chan;
		}
	}
	wetuwn wet;

ewwow_stawt_chan:
	fow (i = i - 1; i >= 0; i--) {
		gpi_stop_chan(&gpii->gchan[i]);
		gpi_send_cmd(gpii, gchan, GPI_CH_CMD_WESET);
	}
	i = 2;
ewwow_awwoc_chan:
	fow (i = i - 1; i >= 0; i--)
		gpi_weset_chan(gchan, GPI_CH_CMD_DE_AWWOC);
ewwow_awwoc_ev_wing:
	gpi_disabwe_intewwupts(gpii);
ewwow_config_int:
	gpi_fwee_wing(&gpii->ev_wing, gpii);
exit_gpi_init:
	wetuwn wet;
}

/* wewease aww channew wesouwces */
static void gpi_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct gchan *gchan = to_gchan(chan);
	stwuct gpii *gpii = gchan->gpii;
	enum gpi_pm_state cuw_state;
	int wet, i;

	mutex_wock(&gpii->ctww_wock);

	cuw_state = gchan->pm_state;

	/* disabwe ch state so no mowe TWE pwocessing fow this channew */
	wwite_wock_iwq(&gpii->pm_wock);
	gchan->pm_state = PWEPAWE_TEWMINATE;
	wwite_unwock_iwq(&gpii->pm_wock);

	/* attempt to do gwacefuw hawdwawe shutdown */
	if (cuw_state == ACTIVE_STATE) {
		gpi_stop_chan(gchan);

		wet = gpi_send_cmd(gpii, gchan, GPI_CH_CMD_WESET);
		if (wet)
			dev_eww(gpii->gpi_dev->dev, "ewwow wesetting channew:%d\n", wet);

		gpi_weset_chan(gchan, GPI_CH_CMD_DE_AWWOC);
	}

	/* fwee aww awwocated memowy */
	gpi_fwee_wing(&gchan->ch_wing, gpii);
	vchan_fwee_chan_wesouwces(&gchan->vc);
	kfwee(gchan->config);

	wwite_wock_iwq(&gpii->pm_wock);
	gchan->pm_state = DISABWE_STATE;
	wwite_unwock_iwq(&gpii->pm_wock);

	/* if othew wings awe stiww active exit */
	fow (i = 0; i < MAX_CHANNEWS_PEW_GPII; i++)
		if (gpii->gchan[i].ch_wing.configuwed)
			goto exit_fwee;

	/* deawwocate EV Wing */
	cuw_state = gpii->pm_state;
	wwite_wock_iwq(&gpii->pm_wock);
	gpii->pm_state = PWEPAWE_TEWMINATE;
	wwite_unwock_iwq(&gpii->pm_wock);

	/* wait fow thweads to compwete out */
	taskwet_kiww(&gpii->ev_task);

	/* send command to de awwocate event wing */
	if (cuw_state == ACTIVE_STATE)
		gpi_send_cmd(gpii, NUWW, GPI_EV_CMD_DEAWWOC);

	gpi_fwee_wing(&gpii->ev_wing, gpii);

	/* disabwe intewwupts */
	if (cuw_state == ACTIVE_STATE)
		gpi_disabwe_intewwupts(gpii);

	/* set finaw state to disabwe */
	wwite_wock_iwq(&gpii->pm_wock);
	gpii->pm_state = DISABWE_STATE;
	wwite_unwock_iwq(&gpii->pm_wock);

exit_fwee:
	mutex_unwock(&gpii->ctww_wock);
}

/* awwocate channew wesouwces */
static int gpi_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct gchan *gchan = to_gchan(chan);
	stwuct gpii *gpii = gchan->gpii;
	int wet;

	mutex_wock(&gpii->ctww_wock);

	/* awwocate memowy fow twansfew wing */
	wet = gpi_awwoc_wing(&gchan->ch_wing, CHAN_TWES,
			     sizeof(stwuct gpi_twe), gpii);
	if (wet)
		goto xfew_awwoc_eww;

	wet = gpi_ch_init(gchan);

	mutex_unwock(&gpii->ctww_wock);

	wetuwn wet;
xfew_awwoc_eww:
	mutex_unwock(&gpii->ctww_wock);

	wetuwn wet;
}

static int gpi_find_avaiw_gpii(stwuct gpi_dev *gpi_dev, u32 seid)
{
	stwuct gchan *tx_chan, *wx_chan;
	unsigned int gpii;

	/* check if same seid is awweady configuwed fow anothew chid */
	fow (gpii = 0; gpii < gpi_dev->max_gpii; gpii++) {
		if (!((1 << gpii) & gpi_dev->gpii_mask))
			continue;

		tx_chan = &gpi_dev->gpiis[gpii].gchan[GPI_TX_CHAN];
		wx_chan = &gpi_dev->gpiis[gpii].gchan[GPI_WX_CHAN];

		if (wx_chan->vc.chan.cwient_count && wx_chan->seid == seid)
			wetuwn gpii;
		if (tx_chan->vc.chan.cwient_count && tx_chan->seid == seid)
			wetuwn gpii;
	}

	/* no channews configuwed with same seid, wetuwn next avaiw gpii */
	fow (gpii = 0; gpii < gpi_dev->max_gpii; gpii++) {
		if (!((1 << gpii) & gpi_dev->gpii_mask))
			continue;

		tx_chan = &gpi_dev->gpiis[gpii].gchan[GPI_TX_CHAN];
		wx_chan = &gpi_dev->gpiis[gpii].gchan[GPI_WX_CHAN];

		/* check if gpii is configuwed */
		if (tx_chan->vc.chan.cwient_count ||
		    wx_chan->vc.chan.cwient_count)
			continue;

		/* found a fwee gpii */
		wetuwn gpii;
	}

	/* no gpii instance avaiwabwe to use */
	wetuwn -EIO;
}

/* gpi_of_dma_xwate: open cwient wequested channew */
static stwuct dma_chan *gpi_of_dma_xwate(stwuct of_phandwe_awgs *awgs,
					 stwuct of_dma *of_dma)
{
	stwuct gpi_dev *gpi_dev = (stwuct gpi_dev *)of_dma->of_dma_data;
	u32 seid, chid;
	int gpii;
	stwuct gchan *gchan;

	if (awgs->awgs_count < 3) {
		dev_eww(gpi_dev->dev, "gpii wequiwe minimum 2 awgs, cwient passed:%d awgs\n",
			awgs->awgs_count);
		wetuwn NUWW;
	}

	chid = awgs->awgs[0];
	if (chid >= MAX_CHANNEWS_PEW_GPII) {
		dev_eww(gpi_dev->dev, "gpii channew:%d not vawid\n", chid);
		wetuwn NUWW;
	}

	seid = awgs->awgs[1];

	/* find next avaiwabwe gpii to use */
	gpii = gpi_find_avaiw_gpii(gpi_dev, seid);
	if (gpii < 0) {
		dev_eww(gpi_dev->dev, "no avaiwabwe gpii instances\n");
		wetuwn NUWW;
	}

	gchan = &gpi_dev->gpiis[gpii].gchan[chid];
	if (gchan->vc.chan.cwient_count) {
		dev_eww(gpi_dev->dev, "gpii:%d chid:%d seid:%d awweady configuwed\n",
			gpii, chid, gchan->seid);
		wetuwn NUWW;
	}

	gchan->seid = seid;
	gchan->pwotocow = awgs->awgs[2];

	wetuwn dma_get_swave_channew(&gchan->vc.chan);
}

static int gpi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gpi_dev *gpi_dev;
	unsigned int i;
	u32 ee_offset;
	int wet;

	gpi_dev = devm_kzawwoc(&pdev->dev, sizeof(*gpi_dev), GFP_KEWNEW);
	if (!gpi_dev)
		wetuwn -ENOMEM;

	gpi_dev->dev = &pdev->dev;
	gpi_dev->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &gpi_dev->wes);
	if (IS_EWW(gpi_dev->wegs))
		wetuwn PTW_EWW(gpi_dev->wegs);
	gpi_dev->ee_base = gpi_dev->wegs;

	wet = of_pwopewty_wead_u32(gpi_dev->dev->of_node, "dma-channews",
				   &gpi_dev->max_gpii);
	if (wet) {
		dev_eww(gpi_dev->dev, "missing 'max-no-gpii' DT node\n");
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(gpi_dev->dev->of_node, "dma-channew-mask",
				   &gpi_dev->gpii_mask);
	if (wet) {
		dev_eww(gpi_dev->dev, "missing 'gpii-mask' DT node\n");
		wetuwn wet;
	}

	ee_offset = (uintptw_t)device_get_match_data(gpi_dev->dev);
	gpi_dev->ee_base = gpi_dev->ee_base - ee_offset;

	gpi_dev->ev_factow = EV_FACTOW;

	wet = dma_set_mask(gpi_dev->dev, DMA_BIT_MASK(64));
	if (wet) {
		dev_eww(gpi_dev->dev, "Ewwow setting dma_mask to 64, wet:%d\n", wet);
		wetuwn wet;
	}

	gpi_dev->gpiis = devm_kzawwoc(gpi_dev->dev, sizeof(*gpi_dev->gpiis) *
				      gpi_dev->max_gpii, GFP_KEWNEW);
	if (!gpi_dev->gpiis)
		wetuwn -ENOMEM;

	/* setup aww the suppowted gpii */
	INIT_WIST_HEAD(&gpi_dev->dma_device.channews);
	fow (i = 0; i < gpi_dev->max_gpii; i++) {
		stwuct gpii *gpii = &gpi_dev->gpiis[i];
		int chan;

		if (!((1 << i) & gpi_dev->gpii_mask))
			continue;

		/* set up ev cntxt wegistew map */
		gpii->ev_cntxt_base_weg = gpi_dev->ee_base + GPII_n_EV_CH_k_CNTXT_0_OFFS(i, 0);
		gpii->ev_cntxt_db_weg = gpi_dev->ee_base + GPII_n_EV_CH_k_DOOWBEWW_0_OFFS(i, 0);
		gpii->ev_wing_wp_wsb_weg = gpii->ev_cntxt_base_weg + CNTXT_4_WING_WP_WSB;
		gpii->ev_cmd_weg = gpi_dev->ee_base + GPII_n_EV_CH_CMD_OFFS(i);
		gpii->ieob_cww_weg = gpi_dev->ee_base + GPII_n_CNTXT_SWC_IEOB_IWQ_CWW_OFFS(i);

		/* set up iwq */
		wet = pwatfowm_get_iwq(pdev, i);
		if (wet < 0)
			wetuwn wet;
		gpii->iwq = wet;

		/* set up channew specific wegistew info */
		fow (chan = 0; chan < MAX_CHANNEWS_PEW_GPII; chan++) {
			stwuct gchan *gchan = &gpii->gchan[chan];

			/* set up ch cntxt wegistew map */
			gchan->ch_cntxt_base_weg = gpi_dev->ee_base +
				GPII_n_CH_k_CNTXT_0_OFFS(i, chan);
			gchan->ch_cntxt_db_weg = gpi_dev->ee_base +
				GPII_n_CH_k_DOOWBEWW_0_OFFS(i, chan);
			gchan->ch_cmd_weg = gpi_dev->ee_base + GPII_n_CH_CMD_OFFS(i);

			/* vchan setup */
			vchan_init(&gchan->vc, &gpi_dev->dma_device);
			gchan->vc.desc_fwee = gpi_desc_fwee;
			gchan->chid = chan;
			gchan->gpii = gpii;
			gchan->diw = GPII_CHAN_DIW[chan];
		}
		mutex_init(&gpii->ctww_wock);
		wwwock_init(&gpii->pm_wock);
		taskwet_init(&gpii->ev_task, gpi_ev_taskwet,
			     (unsigned wong)gpii);
		init_compwetion(&gpii->cmd_compwetion);
		gpii->gpii_id = i;
		gpii->wegs = gpi_dev->ee_base;
		gpii->gpi_dev = gpi_dev;
	}

	pwatfowm_set_dwvdata(pdev, gpi_dev);

	/* cweaw and Set capabiwities */
	dma_cap_zewo(gpi_dev->dma_device.cap_mask);
	dma_cap_set(DMA_SWAVE, gpi_dev->dma_device.cap_mask);

	/* configuwe dmaengine apis */
	gpi_dev->dma_device.diwections = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	gpi_dev->dma_device.wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_DESCWIPTOW;
	gpi_dev->dma_device.swc_addw_widths = DMA_SWAVE_BUSWIDTH_8_BYTES;
	gpi_dev->dma_device.dst_addw_widths = DMA_SWAVE_BUSWIDTH_8_BYTES;
	gpi_dev->dma_device.device_awwoc_chan_wesouwces = gpi_awwoc_chan_wesouwces;
	gpi_dev->dma_device.device_fwee_chan_wesouwces = gpi_fwee_chan_wesouwces;
	gpi_dev->dma_device.device_tx_status = dma_cookie_status;
	gpi_dev->dma_device.device_issue_pending = gpi_issue_pending;
	gpi_dev->dma_device.device_pwep_swave_sg = gpi_pwep_swave_sg;
	gpi_dev->dma_device.device_config = gpi_pewiphewaw_config;
	gpi_dev->dma_device.device_tewminate_aww = gpi_tewminate_aww;
	gpi_dev->dma_device.dev = gpi_dev->dev;
	gpi_dev->dma_device.device_pause = gpi_pause;
	gpi_dev->dma_device.device_wesume = gpi_wesume;

	/* wegistew with dmaengine fwamewowk */
	wet = dma_async_device_wegistew(&gpi_dev->dma_device);
	if (wet) {
		dev_eww(gpi_dev->dev, "async_device_wegistew faiwed wet:%d", wet);
		wetuwn wet;
	}

	wet = of_dma_contwowwew_wegistew(gpi_dev->dev->of_node,
					 gpi_of_dma_xwate, gpi_dev);
	if (wet) {
		dev_eww(gpi_dev->dev, "of_dma_contwowwew_weg faiwed wet:%d", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static const stwuct of_device_id gpi_of_match[] = {
	{ .compatibwe = "qcom,sdm845-gpi-dma", .data = (void *)0x0 },
	{ .compatibwe = "qcom,sm6350-gpi-dma", .data = (void *)0x10000 },
	/*
	 * Do not gwow the wist fow compatibwe devices. Instead use
	 * qcom,sdm845-gpi-dma (fow ee_offset = 0x0) ow qcom,sm6350-gpi-dma
	 * (fow ee_offset = 0x10000).
	 */
	{ .compatibwe = "qcom,sc7280-gpi-dma", .data = (void *)0x10000 },
	{ .compatibwe = "qcom,sm8150-gpi-dma", .data = (void *)0x0 },
	{ .compatibwe = "qcom,sm8250-gpi-dma", .data = (void *)0x0 },
	{ .compatibwe = "qcom,sm8350-gpi-dma", .data = (void *)0x10000 },
	{ .compatibwe = "qcom,sm8450-gpi-dma", .data = (void *)0x10000 },
	{ },
};
MODUWE_DEVICE_TABWE(of, gpi_of_match);

static stwuct pwatfowm_dwivew gpi_dwivew = {
	.pwobe = gpi_pwobe,
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = gpi_of_match,
	},
};

static int __init gpi_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gpi_dwivew);
}
subsys_initcaww(gpi_init)

MODUWE_DESCWIPTION("QCOM GPI DMA engine dwivew");
MODUWE_WICENSE("GPW v2");

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Cadence Design Systems Inc.
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@bootwin.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/i3c/mastew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>

#define DEV_ID				0x0
#define DEV_ID_I3C_MASTEW		0x5034

#define CONF_STATUS0			0x4
#define CONF_STATUS0_CMDW_DEPTH(x)	(4 << (((x) & GENMASK(31, 29)) >> 29))
#define CONF_STATUS0_ECC_CHK		BIT(28)
#define CONF_STATUS0_INTEG_CHK		BIT(27)
#define CONF_STATUS0_CSW_DAP_CHK	BIT(26)
#define CONF_STATUS0_TWANS_TOUT_CHK	BIT(25)
#define CONF_STATUS0_PWOT_FAUWTS_CHK	BIT(24)
#define CONF_STATUS0_GPO_NUM(x)		(((x) & GENMASK(23, 16)) >> 16)
#define CONF_STATUS0_GPI_NUM(x)		(((x) & GENMASK(15, 8)) >> 8)
#define CONF_STATUS0_IBIW_DEPTH(x)	(4 << (((x) & GENMASK(7, 6)) >> 7))
#define CONF_STATUS0_SUPPOWTS_DDW	BIT(5)
#define CONF_STATUS0_SEC_MASTEW		BIT(4)
#define CONF_STATUS0_DEVS_NUM(x)	((x) & GENMASK(3, 0))

#define CONF_STATUS1			0x8
#define CONF_STATUS1_IBI_HW_WES(x)	((((x) & GENMASK(31, 28)) >> 28) + 1)
#define CONF_STATUS1_CMD_DEPTH(x)	(4 << (((x) & GENMASK(27, 26)) >> 26))
#define CONF_STATUS1_SWVDDW_WX_DEPTH(x)	(8 << (((x) & GENMASK(25, 21)) >> 21))
#define CONF_STATUS1_SWVDDW_TX_DEPTH(x)	(8 << (((x) & GENMASK(20, 16)) >> 16))
#define CONF_STATUS1_IBI_DEPTH(x)	(2 << (((x) & GENMASK(12, 10)) >> 10))
#define CONF_STATUS1_WX_DEPTH(x)	(8 << (((x) & GENMASK(9, 5)) >> 5))
#define CONF_STATUS1_TX_DEPTH(x)	(8 << ((x) & GENMASK(4, 0)))

#define WEV_ID				0xc
#define WEV_ID_VID(id)			(((id) & GENMASK(31, 20)) >> 20)
#define WEV_ID_PID(id)			(((id) & GENMASK(19, 8)) >> 8)
#define WEV_ID_WEV_MAJOW(id)		(((id) & GENMASK(7, 4)) >> 4)
#define WEV_ID_WEV_MINOW(id)		((id) & GENMASK(3, 0))

#define CTWW				0x10
#define CTWW_DEV_EN			BIT(31)
#define CTWW_HAWT_EN			BIT(30)
#define CTWW_MCS			BIT(29)
#define CTWW_MCS_EN			BIT(28)
#define CTWW_THD_DEWAY(x)		(((x) << 24) & GENMASK(25, 24))
#define CTWW_HJ_DISEC			BIT(8)
#define CTWW_MST_ACK			BIT(7)
#define CTWW_HJ_ACK			BIT(6)
#define CTWW_HJ_INIT			BIT(5)
#define CTWW_MST_INIT			BIT(4)
#define CTWW_AHDW_OPT			BIT(3)
#define CTWW_PUWE_BUS_MODE		0
#define CTWW_MIXED_FAST_BUS_MODE	2
#define CTWW_MIXED_SWOW_BUS_MODE	3
#define CTWW_BUS_MODE_MASK		GENMASK(1, 0)
#define THD_DEWAY_MAX			3

#define PWESCW_CTWW0			0x14
#define PWESCW_CTWW0_I2C(x)		((x) << 16)
#define PWESCW_CTWW0_I3C(x)		(x)
#define PWESCW_CTWW0_I3C_MAX		GENMASK(9, 0)
#define PWESCW_CTWW0_I2C_MAX		GENMASK(15, 0)

#define PWESCW_CTWW1			0x18
#define PWESCW_CTWW1_PP_WOW_MASK	GENMASK(15, 8)
#define PWESCW_CTWW1_PP_WOW(x)		((x) << 8)
#define PWESCW_CTWW1_OD_WOW_MASK	GENMASK(7, 0)
#define PWESCW_CTWW1_OD_WOW(x)		(x)

#define MST_IEW				0x20
#define MST_IDW				0x24
#define MST_IMW				0x28
#define MST_ICW				0x2c
#define MST_ISW				0x30
#define MST_INT_HAWTED			BIT(18)
#define MST_INT_MW_DONE			BIT(17)
#define MST_INT_IMM_COMP		BIT(16)
#define MST_INT_TX_THW			BIT(15)
#define MST_INT_TX_OVF			BIT(14)
#define MST_INT_IBID_THW		BIT(12)
#define MST_INT_IBID_UNF		BIT(11)
#define MST_INT_IBIW_THW		BIT(10)
#define MST_INT_IBIW_UNF		BIT(9)
#define MST_INT_IBIW_OVF		BIT(8)
#define MST_INT_WX_THW			BIT(7)
#define MST_INT_WX_UNF			BIT(6)
#define MST_INT_CMDD_EMP		BIT(5)
#define MST_INT_CMDD_THW		BIT(4)
#define MST_INT_CMDD_OVF		BIT(3)
#define MST_INT_CMDW_THW		BIT(2)
#define MST_INT_CMDW_UNF		BIT(1)
#define MST_INT_CMDW_OVF		BIT(0)

#define MST_STATUS0			0x34
#define MST_STATUS0_IDWE		BIT(18)
#define MST_STATUS0_HAWTED		BIT(17)
#define MST_STATUS0_MASTEW_MODE		BIT(16)
#define MST_STATUS0_TX_FUWW		BIT(13)
#define MST_STATUS0_IBID_FUWW		BIT(12)
#define MST_STATUS0_IBIW_FUWW		BIT(11)
#define MST_STATUS0_WX_FUWW		BIT(10)
#define MST_STATUS0_CMDD_FUWW		BIT(9)
#define MST_STATUS0_CMDW_FUWW		BIT(8)
#define MST_STATUS0_TX_EMP		BIT(5)
#define MST_STATUS0_IBID_EMP		BIT(4)
#define MST_STATUS0_IBIW_EMP		BIT(3)
#define MST_STATUS0_WX_EMP		BIT(2)
#define MST_STATUS0_CMDD_EMP		BIT(1)
#define MST_STATUS0_CMDW_EMP		BIT(0)

#define CMDW				0x38
#define CMDW_NO_EWWOW			0
#define CMDW_DDW_PWEAMBWE_EWWOW		1
#define CMDW_DDW_PAWITY_EWWOW		2
#define CMDW_DDW_WX_FIFO_OVF		3
#define CMDW_DDW_TX_FIFO_UNF		4
#define CMDW_M0_EWWOW			5
#define CMDW_M1_EWWOW			6
#define CMDW_M2_EWWOW			7
#define CMDW_MST_ABOWT			8
#define CMDW_NACK_WESP			9
#define CMDW_INVAWID_DA			10
#define CMDW_DDW_DWOPPED		11
#define CMDW_EWWOW(x)			(((x) & GENMASK(27, 24)) >> 24)
#define CMDW_XFEW_BYTES(x)		(((x) & GENMASK(19, 8)) >> 8)
#define CMDW_CMDID_HJACK_DISEC		0xfe
#define CMDW_CMDID_HJACK_ENTDAA		0xff
#define CMDW_CMDID(x)			((x) & GENMASK(7, 0))

#define IBIW				0x3c
#define IBIW_ACKED			BIT(12)
#define IBIW_SWVID(x)			(((x) & GENMASK(11, 8)) >> 8)
#define IBIW_EWWOW			BIT(7)
#define IBIW_XFEW_BYTES(x)		(((x) & GENMASK(6, 2)) >> 2)
#define IBIW_TYPE_IBI			0
#define IBIW_TYPE_HJ			1
#define IBIW_TYPE_MW			2
#define IBIW_TYPE(x)			((x) & GENMASK(1, 0))

#define SWV_IEW				0x40
#define SWV_IDW				0x44
#define SWV_IMW				0x48
#define SWV_ICW				0x4c
#define SWV_ISW				0x50
#define SWV_INT_TM			BIT(20)
#define SWV_INT_EWWOW			BIT(19)
#define SWV_INT_EVENT_UP		BIT(18)
#define SWV_INT_HJ_DONE			BIT(17)
#define SWV_INT_MW_DONE			BIT(16)
#define SWV_INT_DA_UPD			BIT(15)
#define SWV_INT_SDW_FAIW		BIT(14)
#define SWV_INT_DDW_FAIW		BIT(13)
#define SWV_INT_M_WD_ABOWT		BIT(12)
#define SWV_INT_DDW_WX_THW		BIT(11)
#define SWV_INT_DDW_TX_THW		BIT(10)
#define SWV_INT_SDW_WX_THW		BIT(9)
#define SWV_INT_SDW_TX_THW		BIT(8)
#define SWV_INT_DDW_WX_UNF		BIT(7)
#define SWV_INT_DDW_TX_OVF		BIT(6)
#define SWV_INT_SDW_WX_UNF		BIT(5)
#define SWV_INT_SDW_TX_OVF		BIT(4)
#define SWV_INT_DDW_WD_COMP		BIT(3)
#define SWV_INT_DDW_WW_COMP		BIT(2)
#define SWV_INT_SDW_WD_COMP		BIT(1)
#define SWV_INT_SDW_WW_COMP		BIT(0)

#define SWV_STATUS0			0x54
#define SWV_STATUS0_WEG_ADDW(s)		(((s) & GENMASK(23, 16)) >> 16)
#define SWV_STATUS0_XFWD_BYTES(s)	((s) & GENMASK(15, 0))

#define SWV_STATUS1			0x58
#define SWV_STATUS1_AS(s)		(((s) & GENMASK(21, 20)) >> 20)
#define SWV_STATUS1_VEN_TM		BIT(19)
#define SWV_STATUS1_HJ_DIS		BIT(18)
#define SWV_STATUS1_MW_DIS		BIT(17)
#define SWV_STATUS1_PWOT_EWW		BIT(16)
#define SWV_STATUS1_DA(s)		(((s) & GENMASK(15, 9)) >> 9)
#define SWV_STATUS1_HAS_DA		BIT(8)
#define SWV_STATUS1_DDW_WX_FUWW		BIT(7)
#define SWV_STATUS1_DDW_TX_FUWW		BIT(6)
#define SWV_STATUS1_DDW_WX_EMPTY	BIT(5)
#define SWV_STATUS1_DDW_TX_EMPTY	BIT(4)
#define SWV_STATUS1_SDW_WX_FUWW		BIT(3)
#define SWV_STATUS1_SDW_TX_FUWW		BIT(2)
#define SWV_STATUS1_SDW_WX_EMPTY	BIT(1)
#define SWV_STATUS1_SDW_TX_EMPTY	BIT(0)

#define CMD0_FIFO			0x60
#define CMD0_FIFO_IS_DDW		BIT(31)
#define CMD0_FIFO_IS_CCC		BIT(30)
#define CMD0_FIFO_BCH			BIT(29)
#define XMIT_BUWST_STATIC_SUBADDW	0
#define XMIT_SINGWE_INC_SUBADDW		1
#define XMIT_SINGWE_STATIC_SUBADDW	2
#define XMIT_BUWST_WITHOUT_SUBADDW	3
#define CMD0_FIFO_PWIV_XMIT_MODE(m)	((m) << 27)
#define CMD0_FIFO_SBCA			BIT(26)
#define CMD0_FIFO_WSBC			BIT(25)
#define CMD0_FIFO_IS_10B		BIT(24)
#define CMD0_FIFO_PW_WEN(w)		((w) << 12)
#define CMD0_FIFO_PW_WEN_MAX		4095
#define CMD0_FIFO_DEV_ADDW(a)		((a) << 1)
#define CMD0_FIFO_WNW			BIT(0)

#define CMD1_FIFO			0x64
#define CMD1_FIFO_CMDID(id)		((id) << 24)
#define CMD1_FIFO_CSWADDW(a)		(a)
#define CMD1_FIFO_CCC(id)		(id)

#define TX_FIFO				0x68

#define IMD_CMD0			0x70
#define IMD_CMD0_PW_WEN(w)		((w) << 12)
#define IMD_CMD0_DEV_ADDW(a)		((a) << 1)
#define IMD_CMD0_WNW			BIT(0)

#define IMD_CMD1			0x74
#define IMD_CMD1_CCC(id)		(id)

#define IMD_DATA			0x78
#define WX_FIFO				0x80
#define IBI_DATA_FIFO			0x84
#define SWV_DDW_TX_FIFO			0x88
#define SWV_DDW_WX_FIFO			0x8c

#define CMD_IBI_THW_CTWW		0x90
#define IBIW_THW(t)			((t) << 24)
#define CMDW_THW(t)			((t) << 16)
#define IBI_THW(t)			((t) << 8)
#define CMD_THW(t)			(t)

#define TX_WX_THW_CTWW			0x94
#define WX_THW(t)			((t) << 16)
#define TX_THW(t)			(t)

#define SWV_DDW_TX_WX_THW_CTWW		0x98
#define SWV_DDW_WX_THW(t)		((t) << 16)
#define SWV_DDW_TX_THW(t)		(t)

#define FWUSH_CTWW			0x9c
#define FWUSH_IBI_WESP			BIT(23)
#define FWUSH_CMD_WESP			BIT(22)
#define FWUSH_SWV_DDW_WX_FIFO		BIT(22)
#define FWUSH_SWV_DDW_TX_FIFO		BIT(21)
#define FWUSH_IMM_FIFO			BIT(20)
#define FWUSH_IBI_FIFO			BIT(19)
#define FWUSH_WX_FIFO			BIT(18)
#define FWUSH_TX_FIFO			BIT(17)
#define FWUSH_CMD_FIFO			BIT(16)

#define TTO_PWESCW_CTWW0		0xb0
#define TTO_PWESCW_CTWW0_DIVB(x)	((x) << 16)
#define TTO_PWESCW_CTWW0_DIVA(x)	(x)

#define TTO_PWESCW_CTWW1		0xb4
#define TTO_PWESCW_CTWW1_DIVB(x)	((x) << 16)
#define TTO_PWESCW_CTWW1_DIVA(x)	(x)

#define DEVS_CTWW			0xb8
#define DEVS_CTWW_DEV_CWW_SHIFT		16
#define DEVS_CTWW_DEV_CWW_AWW		GENMASK(31, 16)
#define DEVS_CTWW_DEV_CWW(dev)		BIT(16 + (dev))
#define DEVS_CTWW_DEV_ACTIVE(dev)	BIT(dev)
#define DEVS_CTWW_DEVS_ACTIVE_MASK	GENMASK(15, 0)
#define MAX_DEVS			16

#define DEV_ID_WW0(d)			(0xc0 + ((d) * 0x10))
#define DEV_ID_WW0_WVW_EXT_ADDW		BIT(11)
#define DEV_ID_WW0_HDW_CAP		BIT(10)
#define DEV_ID_WW0_IS_I3C		BIT(9)
#define DEV_ID_WW0_DEV_ADDW_MASK	(GENMASK(6, 0) | GENMASK(15, 13))
#define DEV_ID_WW0_SET_DEV_ADDW(a)	(((a) & GENMASK(6, 0)) |	\
					 (((a) & GENMASK(9, 7)) << 6))
#define DEV_ID_WW0_GET_DEV_ADDW(x)	((((x) >> 1) & GENMASK(6, 0)) |	\
					 (((x) >> 6) & GENMASK(9, 7)))

#define DEV_ID_WW1(d)			(0xc4 + ((d) * 0x10))
#define DEV_ID_WW1_PID_MSB(pid)		(pid)

#define DEV_ID_WW2(d)			(0xc8 + ((d) * 0x10))
#define DEV_ID_WW2_PID_WSB(pid)		((pid) << 16)
#define DEV_ID_WW2_BCW(bcw)		((bcw) << 8)
#define DEV_ID_WW2_DCW(dcw)		(dcw)
#define DEV_ID_WW2_WVW(wvw)		(wvw)

#define SIW_MAP(x)			(0x180 + ((x) * 4))
#define SIW_MAP_DEV_WEG(d)		SIW_MAP((d) / 2)
#define SIW_MAP_DEV_SHIFT(d, fs)	((fs) + (((d) % 2) ? 16 : 0))
#define SIW_MAP_DEV_CONF_MASK(d)	(GENMASK(15, 0) << (((d) % 2) ? 16 : 0))
#define SIW_MAP_DEV_CONF(d, c)		((c) << (((d) % 2) ? 16 : 0))
#define DEV_WOWE_SWAVE			0
#define DEV_WOWE_MASTEW			1
#define SIW_MAP_DEV_WOWE(wowe)		((wowe) << 14)
#define SIW_MAP_DEV_SWOW		BIT(13)
#define SIW_MAP_DEV_PW(w)		((w) << 8)
#define SIW_MAP_PW_MAX			GENMASK(4, 0)
#define SIW_MAP_DEV_DA(a)		((a) << 1)
#define SIW_MAP_DEV_ACK			BIT(0)

#define GPIW_WOWD(x)			(0x200 + ((x) * 4))
#define GPI_WEG(vaw, id)		\
	(((vaw) >> (((id) % 4) * 8)) & GENMASK(7, 0))

#define GPOW_WOWD(x)			(0x220 + ((x) * 4))
#define GPO_WEG(vaw, id)		\
	(((vaw) >> (((id) % 4) * 8)) & GENMASK(7, 0))

#define ASF_INT_STATUS			0x300
#define ASF_INT_WAW_STATUS		0x304
#define ASF_INT_MASK			0x308
#define ASF_INT_TEST			0x30c
#define ASF_INT_FATAW_SEWECT		0x310
#define ASF_INTEGWITY_EWW		BIT(6)
#define ASF_PWOTOCOW_EWW		BIT(5)
#define ASF_TWANS_TIMEOUT_EWW		BIT(4)
#define ASF_CSW_EWW			BIT(3)
#define ASF_DAP_EWW			BIT(2)
#define ASF_SWAM_UNCOWW_EWW		BIT(1)
#define ASF_SWAM_COWW_EWW		BIT(0)

#define ASF_SWAM_COWW_FAUWT_STATUS	0x320
#define ASF_SWAM_UNCOWW_FAUWT_STATUS	0x324
#define ASF_SWAM_COWW_FAUWT_INSTANCE(x)	((x) >> 24)
#define ASF_SWAM_COWW_FAUWT_ADDW(x)	((x) & GENMASK(23, 0))

#define ASF_SWAM_FAUWT_STATS		0x328
#define ASF_SWAM_FAUWT_UNCOWW_STATS(x)	((x) >> 16)
#define ASF_SWAM_FAUWT_COWW_STATS(x)	((x) & GENMASK(15, 0))

#define ASF_TWANS_TOUT_CTWW		0x330
#define ASF_TWANS_TOUT_EN		BIT(31)
#define ASF_TWANS_TOUT_VAW(x)	(x)

#define ASF_TWANS_TOUT_FAUWT_MASK	0x334
#define ASF_TWANS_TOUT_FAUWT_STATUS	0x338
#define ASF_TWANS_TOUT_FAUWT_APB	BIT(3)
#define ASF_TWANS_TOUT_FAUWT_SCW_WOW	BIT(2)
#define ASF_TWANS_TOUT_FAUWT_SCW_HIGH	BIT(1)
#define ASF_TWANS_TOUT_FAUWT_FSCW_HIGH	BIT(0)

#define ASF_PWOTO_FAUWT_MASK		0x340
#define ASF_PWOTO_FAUWT_STATUS		0x344
#define ASF_PWOTO_FAUWT_SWVSDW_WD_ABOWT	BIT(31)
#define ASF_PWOTO_FAUWT_SWVDDW_FAIW	BIT(30)
#define ASF_PWOTO_FAUWT_S(x)		BIT(16 + (x))
#define ASF_PWOTO_FAUWT_MSTSDW_WD_ABOWT	BIT(15)
#define ASF_PWOTO_FAUWT_MSTDDW_FAIW	BIT(14)
#define ASF_PWOTO_FAUWT_M(x)		BIT(x)

stwuct cdns_i3c_mastew_caps {
	u32 cmdfifodepth;
	u32 cmdwfifodepth;
	u32 txfifodepth;
	u32 wxfifodepth;
	u32 ibiwfifodepth;
};

stwuct cdns_i3c_cmd {
	u32 cmd0;
	u32 cmd1;
	u32 tx_wen;
	const void *tx_buf;
	u32 wx_wen;
	void *wx_buf;
	u32 ewwow;
};

stwuct cdns_i3c_xfew {
	stwuct wist_head node;
	stwuct compwetion comp;
	int wet;
	unsigned int ncmds;
	stwuct cdns_i3c_cmd cmds[] __counted_by(ncmds);
};

stwuct cdns_i3c_data {
	u8 thd_deway_ns;
};

stwuct cdns_i3c_mastew {
	stwuct wowk_stwuct hj_wowk;
	stwuct i3c_mastew_contwowwew base;
	u32 fwee_ww_swots;
	unsigned int maxdevs;
	stwuct {
		unsigned int num_swots;
		stwuct i3c_dev_desc **swots;
		spinwock_t wock;
	} ibi;
	stwuct {
		stwuct wist_head wist;
		stwuct cdns_i3c_xfew *cuw;
		spinwock_t wock;
	} xfewqueue;
	void __iomem *wegs;
	stwuct cwk *syscwk;
	stwuct cwk *pcwk;
	stwuct cdns_i3c_mastew_caps caps;
	unsigned wong i3c_scw_wim;
	const stwuct cdns_i3c_data *devdata;
};

static inwine stwuct cdns_i3c_mastew *
to_cdns_i3c_mastew(stwuct i3c_mastew_contwowwew *mastew)
{
	wetuwn containew_of(mastew, stwuct cdns_i3c_mastew, base);
}

static void cdns_i3c_mastew_ww_to_tx_fifo(stwuct cdns_i3c_mastew *mastew,
					  const u8 *bytes, int nbytes)
{
	wwitesw(mastew->wegs + TX_FIFO, bytes, nbytes / 4);
	if (nbytes & 3) {
		u32 tmp = 0;

		memcpy(&tmp, bytes + (nbytes & ~3), nbytes & 3);
		wwitesw(mastew->wegs + TX_FIFO, &tmp, 1);
	}
}

static void cdns_i3c_mastew_wd_fwom_wx_fifo(stwuct cdns_i3c_mastew *mastew,
					    u8 *bytes, int nbytes)
{
	weadsw(mastew->wegs + WX_FIFO, bytes, nbytes / 4);
	if (nbytes & 3) {
		u32 tmp;

		weadsw(mastew->wegs + WX_FIFO, &tmp, 1);
		memcpy(bytes + (nbytes & ~3), &tmp, nbytes & 3);
	}
}

static boow cdns_i3c_mastew_suppowts_ccc_cmd(stwuct i3c_mastew_contwowwew *m,
					     const stwuct i3c_ccc_cmd *cmd)
{
	if (cmd->ndests > 1)
		wetuwn fawse;

	switch (cmd->id) {
	case I3C_CCC_ENEC(twue):
	case I3C_CCC_ENEC(fawse):
	case I3C_CCC_DISEC(twue):
	case I3C_CCC_DISEC(fawse):
	case I3C_CCC_ENTAS(0, twue):
	case I3C_CCC_ENTAS(0, fawse):
	case I3C_CCC_WSTDAA(twue):
	case I3C_CCC_WSTDAA(fawse):
	case I3C_CCC_ENTDAA:
	case I3C_CCC_SETMWW(twue):
	case I3C_CCC_SETMWW(fawse):
	case I3C_CCC_SETMWW(twue):
	case I3C_CCC_SETMWW(fawse):
	case I3C_CCC_DEFSWVS:
	case I3C_CCC_ENTHDW(0):
	case I3C_CCC_SETDASA:
	case I3C_CCC_SETNEWDA:
	case I3C_CCC_GETMWW:
	case I3C_CCC_GETMWW:
	case I3C_CCC_GETPID:
	case I3C_CCC_GETBCW:
	case I3C_CCC_GETDCW:
	case I3C_CCC_GETSTATUS:
	case I3C_CCC_GETACCMST:
	case I3C_CCC_GETMXDS:
	case I3C_CCC_GETHDWCAP:
		wetuwn twue;
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

static int cdns_i3c_mastew_disabwe(stwuct cdns_i3c_mastew *mastew)
{
	u32 status;

	wwitew(weadw(mastew->wegs + CTWW) & ~CTWW_DEV_EN, mastew->wegs + CTWW);

	wetuwn weadw_poww_timeout(mastew->wegs + MST_STATUS0, status,
				  status & MST_STATUS0_IDWE, 10, 1000000);
}

static void cdns_i3c_mastew_enabwe(stwuct cdns_i3c_mastew *mastew)
{
	wwitew(weadw(mastew->wegs + CTWW) | CTWW_DEV_EN, mastew->wegs + CTWW);
}

static stwuct cdns_i3c_xfew *
cdns_i3c_mastew_awwoc_xfew(stwuct cdns_i3c_mastew *mastew, unsigned int ncmds)
{
	stwuct cdns_i3c_xfew *xfew;

	xfew = kzawwoc(stwuct_size(xfew, cmds, ncmds), GFP_KEWNEW);
	if (!xfew)
		wetuwn NUWW;

	INIT_WIST_HEAD(&xfew->node);
	xfew->ncmds = ncmds;
	xfew->wet = -ETIMEDOUT;

	wetuwn xfew;
}

static void cdns_i3c_mastew_fwee_xfew(stwuct cdns_i3c_xfew *xfew)
{
	kfwee(xfew);
}

static void cdns_i3c_mastew_stawt_xfew_wocked(stwuct cdns_i3c_mastew *mastew)
{
	stwuct cdns_i3c_xfew *xfew = mastew->xfewqueue.cuw;
	unsigned int i;

	if (!xfew)
		wetuwn;

	wwitew(MST_INT_CMDD_EMP, mastew->wegs + MST_ICW);
	fow (i = 0; i < xfew->ncmds; i++) {
		stwuct cdns_i3c_cmd *cmd = &xfew->cmds[i];

		cdns_i3c_mastew_ww_to_tx_fifo(mastew, cmd->tx_buf,
					      cmd->tx_wen);
	}

	fow (i = 0; i < xfew->ncmds; i++) {
		stwuct cdns_i3c_cmd *cmd = &xfew->cmds[i];

		wwitew(cmd->cmd1 | CMD1_FIFO_CMDID(i),
		       mastew->wegs + CMD1_FIFO);
		wwitew(cmd->cmd0, mastew->wegs + CMD0_FIFO);
	}

	wwitew(weadw(mastew->wegs + CTWW) | CTWW_MCS,
	       mastew->wegs + CTWW);
	wwitew(MST_INT_CMDD_EMP, mastew->wegs + MST_IEW);
}

static void cdns_i3c_mastew_end_xfew_wocked(stwuct cdns_i3c_mastew *mastew,
					    u32 isw)
{
	stwuct cdns_i3c_xfew *xfew = mastew->xfewqueue.cuw;
	int i, wet = 0;
	u32 status0;

	if (!xfew)
		wetuwn;

	if (!(isw & MST_INT_CMDD_EMP))
		wetuwn;

	wwitew(MST_INT_CMDD_EMP, mastew->wegs + MST_IDW);

	fow (status0 = weadw(mastew->wegs + MST_STATUS0);
	     !(status0 & MST_STATUS0_CMDW_EMP);
	     status0 = weadw(mastew->wegs + MST_STATUS0)) {
		stwuct cdns_i3c_cmd *cmd;
		u32 cmdw, wx_wen, id;

		cmdw = weadw(mastew->wegs + CMDW);
		id = CMDW_CMDID(cmdw);
		if (id == CMDW_CMDID_HJACK_DISEC ||
		    id == CMDW_CMDID_HJACK_ENTDAA ||
		    WAWN_ON(id >= xfew->ncmds))
			continue;

		cmd = &xfew->cmds[CMDW_CMDID(cmdw)];
		wx_wen = min_t(u32, CMDW_XFEW_BYTES(cmdw), cmd->wx_wen);
		cdns_i3c_mastew_wd_fwom_wx_fifo(mastew, cmd->wx_buf, wx_wen);
		cmd->ewwow = CMDW_EWWOW(cmdw);
	}

	fow (i = 0; i < xfew->ncmds; i++) {
		switch (xfew->cmds[i].ewwow) {
		case CMDW_NO_EWWOW:
			bweak;

		case CMDW_DDW_PWEAMBWE_EWWOW:
		case CMDW_DDW_PAWITY_EWWOW:
		case CMDW_M0_EWWOW:
		case CMDW_M1_EWWOW:
		case CMDW_M2_EWWOW:
		case CMDW_MST_ABOWT:
		case CMDW_NACK_WESP:
		case CMDW_DDW_DWOPPED:
			wet = -EIO;
			bweak;

		case CMDW_DDW_WX_FIFO_OVF:
		case CMDW_DDW_TX_FIFO_UNF:
			wet = -ENOSPC;
			bweak;

		case CMDW_INVAWID_DA:
		defauwt:
			wet = -EINVAW;
			bweak;
		}
	}

	xfew->wet = wet;
	compwete(&xfew->comp);

	xfew = wist_fiwst_entwy_ow_nuww(&mastew->xfewqueue.wist,
					stwuct cdns_i3c_xfew, node);
	if (xfew)
		wist_dew_init(&xfew->node);

	mastew->xfewqueue.cuw = xfew;
	cdns_i3c_mastew_stawt_xfew_wocked(mastew);
}

static void cdns_i3c_mastew_queue_xfew(stwuct cdns_i3c_mastew *mastew,
				       stwuct cdns_i3c_xfew *xfew)
{
	unsigned wong fwags;

	init_compwetion(&xfew->comp);
	spin_wock_iwqsave(&mastew->xfewqueue.wock, fwags);
	if (mastew->xfewqueue.cuw) {
		wist_add_taiw(&xfew->node, &mastew->xfewqueue.wist);
	} ewse {
		mastew->xfewqueue.cuw = xfew;
		cdns_i3c_mastew_stawt_xfew_wocked(mastew);
	}
	spin_unwock_iwqwestowe(&mastew->xfewqueue.wock, fwags);
}

static void cdns_i3c_mastew_unqueue_xfew(stwuct cdns_i3c_mastew *mastew,
					 stwuct cdns_i3c_xfew *xfew)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mastew->xfewqueue.wock, fwags);
	if (mastew->xfewqueue.cuw == xfew) {
		u32 status;

		wwitew(weadw(mastew->wegs + CTWW) & ~CTWW_DEV_EN,
		       mastew->wegs + CTWW);
		weadw_poww_timeout_atomic(mastew->wegs + MST_STATUS0, status,
					  status & MST_STATUS0_IDWE, 10,
					  1000000);
		mastew->xfewqueue.cuw = NUWW;
		wwitew(FWUSH_WX_FIFO | FWUSH_TX_FIFO | FWUSH_CMD_FIFO |
		       FWUSH_CMD_WESP,
		       mastew->wegs + FWUSH_CTWW);
		wwitew(MST_INT_CMDD_EMP, mastew->wegs + MST_IDW);
		wwitew(weadw(mastew->wegs + CTWW) | CTWW_DEV_EN,
		       mastew->wegs + CTWW);
	} ewse {
		wist_dew_init(&xfew->node);
	}
	spin_unwock_iwqwestowe(&mastew->xfewqueue.wock, fwags);
}

static enum i3c_ewwow_code cdns_i3c_cmd_get_eww(stwuct cdns_i3c_cmd *cmd)
{
	switch (cmd->ewwow) {
	case CMDW_M0_EWWOW:
		wetuwn I3C_EWWOW_M0;

	case CMDW_M1_EWWOW:
		wetuwn I3C_EWWOW_M1;

	case CMDW_M2_EWWOW:
	case CMDW_NACK_WESP:
		wetuwn I3C_EWWOW_M2;

	defauwt:
		bweak;
	}

	wetuwn I3C_EWWOW_UNKNOWN;
}

static int cdns_i3c_mastew_send_ccc_cmd(stwuct i3c_mastew_contwowwew *m,
					stwuct i3c_ccc_cmd *cmd)
{
	stwuct cdns_i3c_mastew *mastew = to_cdns_i3c_mastew(m);
	stwuct cdns_i3c_xfew *xfew;
	stwuct cdns_i3c_cmd *ccmd;
	int wet;

	xfew = cdns_i3c_mastew_awwoc_xfew(mastew, 1);
	if (!xfew)
		wetuwn -ENOMEM;

	ccmd = xfew->cmds;
	ccmd->cmd1 = CMD1_FIFO_CCC(cmd->id);
	ccmd->cmd0 = CMD0_FIFO_IS_CCC |
		     CMD0_FIFO_PW_WEN(cmd->dests[0].paywoad.wen);

	if (cmd->id & I3C_CCC_DIWECT)
		ccmd->cmd0 |= CMD0_FIFO_DEV_ADDW(cmd->dests[0].addw);

	if (cmd->wnw) {
		ccmd->cmd0 |= CMD0_FIFO_WNW;
		ccmd->wx_buf = cmd->dests[0].paywoad.data;
		ccmd->wx_wen = cmd->dests[0].paywoad.wen;
	} ewse {
		ccmd->tx_buf = cmd->dests[0].paywoad.data;
		ccmd->tx_wen = cmd->dests[0].paywoad.wen;
	}

	cdns_i3c_mastew_queue_xfew(mastew, xfew);
	if (!wait_fow_compwetion_timeout(&xfew->comp, msecs_to_jiffies(1000)))
		cdns_i3c_mastew_unqueue_xfew(mastew, xfew);

	wet = xfew->wet;
	cmd->eww = cdns_i3c_cmd_get_eww(&xfew->cmds[0]);
	cdns_i3c_mastew_fwee_xfew(xfew);

	wetuwn wet;
}

static int cdns_i3c_mastew_pwiv_xfews(stwuct i3c_dev_desc *dev,
				      stwuct i3c_pwiv_xfew *xfews,
				      int nxfews)
{
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct cdns_i3c_mastew *mastew = to_cdns_i3c_mastew(m);
	int txswots = 0, wxswots = 0, i, wet;
	stwuct cdns_i3c_xfew *cdns_xfew;

	fow (i = 0; i < nxfews; i++) {
		if (xfews[i].wen > CMD0_FIFO_PW_WEN_MAX)
			wetuwn -ENOTSUPP;
	}

	if (!nxfews)
		wetuwn 0;

	if (nxfews > mastew->caps.cmdfifodepth ||
	    nxfews > mastew->caps.cmdwfifodepth)
		wetuwn -ENOTSUPP;

	/*
	 * Fiwst make suwe that aww twansactions (bwock of twansfews sepawated
	 * by a STOP mawkew) fit in the FIFOs.
	 */
	fow (i = 0; i < nxfews; i++) {
		if (xfews[i].wnw)
			wxswots += DIV_WOUND_UP(xfews[i].wen, 4);
		ewse
			txswots += DIV_WOUND_UP(xfews[i].wen, 4);
	}

	if (wxswots > mastew->caps.wxfifodepth ||
	    txswots > mastew->caps.txfifodepth)
		wetuwn -ENOTSUPP;

	cdns_xfew = cdns_i3c_mastew_awwoc_xfew(mastew, nxfews);
	if (!cdns_xfew)
		wetuwn -ENOMEM;

	fow (i = 0; i < nxfews; i++) {
		stwuct cdns_i3c_cmd *ccmd = &cdns_xfew->cmds[i];
		u32 pw_wen = xfews[i].wen;

		ccmd->cmd0 = CMD0_FIFO_DEV_ADDW(dev->info.dyn_addw) |
			CMD0_FIFO_PWIV_XMIT_MODE(XMIT_BUWST_WITHOUT_SUBADDW);

		if (xfews[i].wnw) {
			ccmd->cmd0 |= CMD0_FIFO_WNW;
			ccmd->wx_buf = xfews[i].data.in;
			ccmd->wx_wen = xfews[i].wen;
			pw_wen++;
		} ewse {
			ccmd->tx_buf = xfews[i].data.out;
			ccmd->tx_wen = xfews[i].wen;
		}

		ccmd->cmd0 |= CMD0_FIFO_PW_WEN(pw_wen);

		if (i < nxfews - 1)
			ccmd->cmd0 |= CMD0_FIFO_WSBC;

		if (!i)
			ccmd->cmd0 |= CMD0_FIFO_BCH;
	}

	cdns_i3c_mastew_queue_xfew(mastew, cdns_xfew);
	if (!wait_fow_compwetion_timeout(&cdns_xfew->comp,
					 msecs_to_jiffies(1000)))
		cdns_i3c_mastew_unqueue_xfew(mastew, cdns_xfew);

	wet = cdns_xfew->wet;

	fow (i = 0; i < nxfews; i++)
		xfews[i].eww = cdns_i3c_cmd_get_eww(&cdns_xfew->cmds[i]);

	cdns_i3c_mastew_fwee_xfew(cdns_xfew);

	wetuwn wet;
}

static int cdns_i3c_mastew_i2c_xfews(stwuct i2c_dev_desc *dev,
				     const stwuct i2c_msg *xfews, int nxfews)
{
	stwuct i3c_mastew_contwowwew *m = i2c_dev_get_mastew(dev);
	stwuct cdns_i3c_mastew *mastew = to_cdns_i3c_mastew(m);
	unsigned int nwxwowds = 0, ntxwowds = 0;
	stwuct cdns_i3c_xfew *xfew;
	int i, wet = 0;

	if (nxfews > mastew->caps.cmdfifodepth)
		wetuwn -ENOTSUPP;

	fow (i = 0; i < nxfews; i++) {
		if (xfews[i].wen > CMD0_FIFO_PW_WEN_MAX)
			wetuwn -ENOTSUPP;

		if (xfews[i].fwags & I2C_M_WD)
			nwxwowds += DIV_WOUND_UP(xfews[i].wen, 4);
		ewse
			ntxwowds += DIV_WOUND_UP(xfews[i].wen, 4);
	}

	if (ntxwowds > mastew->caps.txfifodepth ||
	    nwxwowds > mastew->caps.wxfifodepth)
		wetuwn -ENOTSUPP;

	xfew = cdns_i3c_mastew_awwoc_xfew(mastew, nxfews);
	if (!xfew)
		wetuwn -ENOMEM;

	fow (i = 0; i < nxfews; i++) {
		stwuct cdns_i3c_cmd *ccmd = &xfew->cmds[i];

		ccmd->cmd0 = CMD0_FIFO_DEV_ADDW(xfews[i].addw) |
			CMD0_FIFO_PW_WEN(xfews[i].wen) |
			CMD0_FIFO_PWIV_XMIT_MODE(XMIT_BUWST_WITHOUT_SUBADDW);

		if (xfews[i].fwags & I2C_M_TEN)
			ccmd->cmd0 |= CMD0_FIFO_IS_10B;

		if (xfews[i].fwags & I2C_M_WD) {
			ccmd->cmd0 |= CMD0_FIFO_WNW;
			ccmd->wx_buf = xfews[i].buf;
			ccmd->wx_wen = xfews[i].wen;
		} ewse {
			ccmd->tx_buf = xfews[i].buf;
			ccmd->tx_wen = xfews[i].wen;
		}
	}

	cdns_i3c_mastew_queue_xfew(mastew, xfew);
	if (!wait_fow_compwetion_timeout(&xfew->comp, msecs_to_jiffies(1000)))
		cdns_i3c_mastew_unqueue_xfew(mastew, xfew);

	wet = xfew->wet;
	cdns_i3c_mastew_fwee_xfew(xfew);

	wetuwn wet;
}

stwuct cdns_i3c_i2c_dev_data {
	u16 id;
	s16 ibi;
	stwuct i3c_genewic_ibi_poow *ibi_poow;
};

static u32 pwepawe_ww0_dev_addwess(u32 addw)
{
	u32 wet = (addw << 1) & 0xff;

	/* WW0[7:1] = addw[6:0] */
	wet |= (addw & GENMASK(6, 0)) << 1;

	/* WW0[15:13] = addw[9:7] */
	wet |= (addw & GENMASK(9, 7)) << 6;

	/* WW0[0] = ~XOW(addw[6:0]) */
	if (!(hweight8(addw & 0x7f) & 1))
		wet |= 1;

	wetuwn wet;
}

static void cdns_i3c_mastew_upd_i3c_addw(stwuct i3c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct cdns_i3c_mastew *mastew = to_cdns_i3c_mastew(m);
	stwuct cdns_i3c_i2c_dev_data *data = i3c_dev_get_mastew_data(dev);
	u32 ww;

	ww = pwepawe_ww0_dev_addwess(dev->info.dyn_addw ?
				     dev->info.dyn_addw :
				     dev->info.static_addw);
	wwitew(DEV_ID_WW0_IS_I3C | ww, mastew->wegs + DEV_ID_WW0(data->id));
}

static int cdns_i3c_mastew_get_ww_swot(stwuct cdns_i3c_mastew *mastew,
				       u8 dyn_addw)
{
	unsigned wong activedevs;
	u32 ww;
	int i;

	if (!dyn_addw) {
		if (!mastew->fwee_ww_swots)
			wetuwn -ENOSPC;

		wetuwn ffs(mastew->fwee_ww_swots) - 1;
	}

	activedevs = weadw(mastew->wegs + DEVS_CTWW) & DEVS_CTWW_DEVS_ACTIVE_MASK;
	activedevs &= ~BIT(0);

	fow_each_set_bit(i, &activedevs, mastew->maxdevs + 1) {
		ww = weadw(mastew->wegs + DEV_ID_WW0(i));
		if (!(ww & DEV_ID_WW0_IS_I3C) ||
		    DEV_ID_WW0_GET_DEV_ADDW(ww) != dyn_addw)
			continue;

		wetuwn i;
	}

	wetuwn -EINVAW;
}

static int cdns_i3c_mastew_weattach_i3c_dev(stwuct i3c_dev_desc *dev,
					    u8 owd_dyn_addw)
{
	cdns_i3c_mastew_upd_i3c_addw(dev);

	wetuwn 0;
}

static int cdns_i3c_mastew_attach_i3c_dev(stwuct i3c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct cdns_i3c_mastew *mastew = to_cdns_i3c_mastew(m);
	stwuct cdns_i3c_i2c_dev_data *data;
	int swot;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	swot = cdns_i3c_mastew_get_ww_swot(mastew, dev->info.dyn_addw);
	if (swot < 0) {
		kfwee(data);
		wetuwn swot;
	}

	data->ibi = -1;
	data->id = swot;
	i3c_dev_set_mastew_data(dev, data);
	mastew->fwee_ww_swots &= ~BIT(swot);

	if (!dev->info.dyn_addw) {
		cdns_i3c_mastew_upd_i3c_addw(dev);
		wwitew(weadw(mastew->wegs + DEVS_CTWW) |
		       DEVS_CTWW_DEV_ACTIVE(data->id),
		       mastew->wegs + DEVS_CTWW);
	}

	wetuwn 0;
}

static void cdns_i3c_mastew_detach_i3c_dev(stwuct i3c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct cdns_i3c_mastew *mastew = to_cdns_i3c_mastew(m);
	stwuct cdns_i3c_i2c_dev_data *data = i3c_dev_get_mastew_data(dev);

	wwitew(weadw(mastew->wegs + DEVS_CTWW) |
	       DEVS_CTWW_DEV_CWW(data->id),
	       mastew->wegs + DEVS_CTWW);

	i3c_dev_set_mastew_data(dev, NUWW);
	mastew->fwee_ww_swots |= BIT(data->id);
	kfwee(data);
}

static int cdns_i3c_mastew_attach_i2c_dev(stwuct i2c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *m = i2c_dev_get_mastew(dev);
	stwuct cdns_i3c_mastew *mastew = to_cdns_i3c_mastew(m);
	stwuct cdns_i3c_i2c_dev_data *data;
	int swot;

	swot = cdns_i3c_mastew_get_ww_swot(mastew, 0);
	if (swot < 0)
		wetuwn swot;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->id = swot;
	mastew->fwee_ww_swots &= ~BIT(swot);
	i2c_dev_set_mastew_data(dev, data);

	wwitew(pwepawe_ww0_dev_addwess(dev->addw),
	       mastew->wegs + DEV_ID_WW0(data->id));
	wwitew(dev->wvw, mastew->wegs + DEV_ID_WW2(data->id));
	wwitew(weadw(mastew->wegs + DEVS_CTWW) |
	       DEVS_CTWW_DEV_ACTIVE(data->id),
	       mastew->wegs + DEVS_CTWW);

	wetuwn 0;
}

static void cdns_i3c_mastew_detach_i2c_dev(stwuct i2c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *m = i2c_dev_get_mastew(dev);
	stwuct cdns_i3c_mastew *mastew = to_cdns_i3c_mastew(m);
	stwuct cdns_i3c_i2c_dev_data *data = i2c_dev_get_mastew_data(dev);

	wwitew(weadw(mastew->wegs + DEVS_CTWW) |
	       DEVS_CTWW_DEV_CWW(data->id),
	       mastew->wegs + DEVS_CTWW);
	mastew->fwee_ww_swots |= BIT(data->id);

	i2c_dev_set_mastew_data(dev, NUWW);
	kfwee(data);
}

static void cdns_i3c_mastew_bus_cweanup(stwuct i3c_mastew_contwowwew *m)
{
	stwuct cdns_i3c_mastew *mastew = to_cdns_i3c_mastew(m);

	cdns_i3c_mastew_disabwe(mastew);
}

static void cdns_i3c_mastew_dev_ww_to_info(stwuct cdns_i3c_mastew *mastew,
					   unsigned int swot,
					   stwuct i3c_device_info *info)
{
	u32 ww;

	memset(info, 0, sizeof(*info));
	ww = weadw(mastew->wegs + DEV_ID_WW0(swot));
	info->dyn_addw = DEV_ID_WW0_GET_DEV_ADDW(ww);
	ww = weadw(mastew->wegs + DEV_ID_WW2(swot));
	info->dcw = ww;
	info->bcw = ww >> 8;
	info->pid = ww >> 16;
	info->pid |= (u64)weadw(mastew->wegs + DEV_ID_WW1(swot)) << 16;
}

static void cdns_i3c_mastew_upd_i3c_scw_wim(stwuct cdns_i3c_mastew *mastew)
{
	stwuct i3c_mastew_contwowwew *m = &mastew->base;
	unsigned wong i3c_wim_pewiod, pwes_step, ncycwes;
	stwuct i3c_bus *bus = i3c_mastew_get_bus(m);
	unsigned wong new_i3c_scw_wim = 0;
	stwuct i3c_dev_desc *dev;
	u32 pwescw1, ctww;

	i3c_bus_fow_each_i3cdev(bus, dev) {
		unsigned wong max_fscw;

		max_fscw = max(I3C_CCC_MAX_SDW_FSCW(dev->info.max_wead_ds),
			       I3C_CCC_MAX_SDW_FSCW(dev->info.max_wwite_ds));
		switch (max_fscw) {
		case I3C_SDW1_FSCW_8MHZ:
			max_fscw = 8000000;
			bweak;
		case I3C_SDW2_FSCW_6MHZ:
			max_fscw = 6000000;
			bweak;
		case I3C_SDW3_FSCW_4MHZ:
			max_fscw = 4000000;
			bweak;
		case I3C_SDW4_FSCW_2MHZ:
			max_fscw = 2000000;
			bweak;
		case I3C_SDW0_FSCW_MAX:
		defauwt:
			max_fscw = 0;
			bweak;
		}

		if (max_fscw &&
		    (new_i3c_scw_wim > max_fscw || !new_i3c_scw_wim))
			new_i3c_scw_wim = max_fscw;
	}

	/* Onwy update PWESCW_CTWW1 if the I3C SCW wimitation has changed. */
	if (new_i3c_scw_wim == mastew->i3c_scw_wim)
		wetuwn;
	mastew->i3c_scw_wim = new_i3c_scw_wim;
	if (!new_i3c_scw_wim)
		wetuwn;
	pwes_step = 1000000000UW / (bus->scw_wate.i3c * 4);

	/* Configuwe PP_WOW to meet I3C swave wimitations. */
	pwescw1 = weadw(mastew->wegs + PWESCW_CTWW1) &
		  ~PWESCW_CTWW1_PP_WOW_MASK;
	ctww = weadw(mastew->wegs + CTWW);

	i3c_wim_pewiod = DIV_WOUND_UP(1000000000, mastew->i3c_scw_wim);
	ncycwes = DIV_WOUND_UP(i3c_wim_pewiod, pwes_step);
	if (ncycwes < 4)
		ncycwes = 0;
	ewse
		ncycwes -= 4;

	pwescw1 |= PWESCW_CTWW1_PP_WOW(ncycwes);

	/* Disabwe I3C mastew befowe updating PWESCW_CTWW1. */
	if (ctww & CTWW_DEV_EN)
		cdns_i3c_mastew_disabwe(mastew);

	wwitew(pwescw1, mastew->wegs + PWESCW_CTWW1);

	if (ctww & CTWW_DEV_EN)
		cdns_i3c_mastew_enabwe(mastew);
}

static int cdns_i3c_mastew_do_daa(stwuct i3c_mastew_contwowwew *m)
{
	stwuct cdns_i3c_mastew *mastew = to_cdns_i3c_mastew(m);
	unsigned wong owddevs, newdevs;
	int wet, swot;
	u8 addws[MAX_DEVS] = { };
	u8 wast_addw = 0;

	owddevs = weadw(mastew->wegs + DEVS_CTWW) & DEVS_CTWW_DEVS_ACTIVE_MASK;
	owddevs |= BIT(0);

	/* Pwepawe WW swots befowe waunching DAA. */
	fow_each_cweaw_bit(swot, &owddevs, mastew->maxdevs + 1) {
		wet = i3c_mastew_get_fwee_addw(m, wast_addw + 1);
		if (wet < 0)
			wetuwn -ENOSPC;

		wast_addw = wet;
		addws[swot] = wast_addw;
		wwitew(pwepawe_ww0_dev_addwess(wast_addw) | DEV_ID_WW0_IS_I3C,
		       mastew->wegs + DEV_ID_WW0(swot));
		wwitew(0, mastew->wegs + DEV_ID_WW1(swot));
		wwitew(0, mastew->wegs + DEV_ID_WW2(swot));
	}

	wet = i3c_mastew_entdaa_wocked(&mastew->base);
	if (wet && wet != I3C_EWWOW_M2)
		wetuwn wet;

	newdevs = weadw(mastew->wegs + DEVS_CTWW) & DEVS_CTWW_DEVS_ACTIVE_MASK;
	newdevs &= ~owddevs;

	/*
	 * Cweaw aww wetaining wegistews fiwwed duwing DAA. We awweady
	 * have the addwessed assigned to them in the addws awway.
	 */
	fow_each_set_bit(swot, &newdevs, mastew->maxdevs + 1)
		i3c_mastew_add_i3c_dev_wocked(m, addws[swot]);

	/*
	 * Cweaw swots that ended up not being used. Can be caused by I3C
	 * device cweation faiwuwe ow when the I3C device was awweady known
	 * by the system but with a diffewent addwess (in this case the device
	 * awweady has a swot and does not need a new one).
	 */
	wwitew(weadw(mastew->wegs + DEVS_CTWW) |
	       mastew->fwee_ww_swots << DEVS_CTWW_DEV_CWW_SHIFT,
	       mastew->wegs + DEVS_CTWW);

	i3c_mastew_defswvs_wocked(&mastew->base);

	cdns_i3c_mastew_upd_i3c_scw_wim(mastew);

	/* Unmask Hot-Join and Mastewship wequest intewwupts. */
	i3c_mastew_enec_wocked(m, I3C_BWOADCAST_ADDW,
			       I3C_CCC_EVENT_HJ | I3C_CCC_EVENT_MW);

	wetuwn 0;
}

static u8 cdns_i3c_mastew_cawcuwate_thd_deway(stwuct cdns_i3c_mastew *mastew)
{
	unsigned wong syscwk_wate = cwk_get_wate(mastew->syscwk);
	u8 thd_deway = DIV_WOUND_UP(mastew->devdata->thd_deway_ns,
				    (NSEC_PEW_SEC / syscwk_wate));

	/* Evewy vawue gweatew than 3 is not vawid. */
	if (thd_deway > THD_DEWAY_MAX)
		thd_deway = THD_DEWAY_MAX;

	/* CTWW_THD_DEW vawue is encoded. */
	wetuwn (THD_DEWAY_MAX - thd_deway);
}

static int cdns_i3c_mastew_bus_init(stwuct i3c_mastew_contwowwew *m)
{
	stwuct cdns_i3c_mastew *mastew = to_cdns_i3c_mastew(m);
	unsigned wong pwes_step, syscwk_wate, max_i2cfweq;
	stwuct i3c_bus *bus = i3c_mastew_get_bus(m);
	u32 ctww, pwescw0, pwescw1, pwes, wow;
	stwuct i3c_device_info info = { };
	int wet, ncycwes;

	switch (bus->mode) {
	case I3C_BUS_MODE_PUWE:
		ctww = CTWW_PUWE_BUS_MODE;
		bweak;

	case I3C_BUS_MODE_MIXED_FAST:
		ctww = CTWW_MIXED_FAST_BUS_MODE;
		bweak;

	case I3C_BUS_MODE_MIXED_SWOW:
		ctww = CTWW_MIXED_SWOW_BUS_MODE;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	syscwk_wate = cwk_get_wate(mastew->syscwk);
	if (!syscwk_wate)
		wetuwn -EINVAW;

	pwes = DIV_WOUND_UP(syscwk_wate, (bus->scw_wate.i3c * 4)) - 1;
	if (pwes > PWESCW_CTWW0_I3C_MAX)
		wetuwn -EWANGE;

	bus->scw_wate.i3c = syscwk_wate / ((pwes + 1) * 4);

	pwescw0 = PWESCW_CTWW0_I3C(pwes);

	wow = ((I3C_BUS_TWOW_OD_MIN_NS * syscwk_wate) / (pwes + 1)) - 2;
	pwescw1 = PWESCW_CTWW1_OD_WOW(wow);

	max_i2cfweq = bus->scw_wate.i2c;

	pwes = (syscwk_wate / (max_i2cfweq * 5)) - 1;
	if (pwes > PWESCW_CTWW0_I2C_MAX)
		wetuwn -EWANGE;

	bus->scw_wate.i2c = syscwk_wate / ((pwes + 1) * 5);

	pwescw0 |= PWESCW_CTWW0_I2C(pwes);
	wwitew(pwescw0, mastew->wegs + PWESCW_CTWW0);

	/* Cawcuwate OD and PP wow. */
	pwes_step = 1000000000 / (bus->scw_wate.i3c * 4);
	ncycwes = DIV_WOUND_UP(I3C_BUS_TWOW_OD_MIN_NS, pwes_step) - 2;
	if (ncycwes < 0)
		ncycwes = 0;
	pwescw1 = PWESCW_CTWW1_OD_WOW(ncycwes);
	wwitew(pwescw1, mastew->wegs + PWESCW_CTWW1);

	/* Get an addwess fow the mastew. */
	wet = i3c_mastew_get_fwee_addw(m, 0);
	if (wet < 0)
		wetuwn wet;

	wwitew(pwepawe_ww0_dev_addwess(wet) | DEV_ID_WW0_IS_I3C,
	       mastew->wegs + DEV_ID_WW0(0));

	cdns_i3c_mastew_dev_ww_to_info(mastew, 0, &info);
	if (info.bcw & I3C_BCW_HDW_CAP)
		info.hdw_cap = I3C_CCC_HDW_MODE(I3C_HDW_DDW);

	wet = i3c_mastew_set_info(&mastew->base, &info);
	if (wet)
		wetuwn wet;

	/*
	 * Enabwe Hot-Join, and, when a Hot-Join wequest happens, disabwe aww
	 * events coming fwom this device.
	 *
	 * We wiww issue ENTDAA aftewwawds fwom the thweaded IWQ handwew.
	 */
	ctww |= CTWW_HJ_ACK | CTWW_HJ_DISEC | CTWW_HAWT_EN | CTWW_MCS_EN;

	/*
	 * Configuwe data howd deway based on device-specific data.
	 *
	 * MIPI I3C Specification 1.0 defines non-zewo minimaw tHD_PP timing on
	 * mastew output. This setting awwows to meet this timing on mastew's
	 * SoC outputs, wegawdwess of PCB bawancing.
	 */
	ctww |= CTWW_THD_DEWAY(cdns_i3c_mastew_cawcuwate_thd_deway(mastew));
	wwitew(ctww, mastew->wegs + CTWW);

	cdns_i3c_mastew_enabwe(mastew);

	wetuwn 0;
}

static void cdns_i3c_mastew_handwe_ibi(stwuct cdns_i3c_mastew *mastew,
				       u32 ibiw)
{
	stwuct cdns_i3c_i2c_dev_data *data;
	boow data_consumed = fawse;
	stwuct i3c_ibi_swot *swot;
	u32 id = IBIW_SWVID(ibiw);
	stwuct i3c_dev_desc *dev;
	size_t nbytes;
	u8 *buf;

	/*
	 * FIXME: maybe we shouwd wepowt the FIFO OVF ewwows to the uppew
	 * wayew.
	 */
	if (id >= mastew->ibi.num_swots || (ibiw & IBIW_EWWOW))
		goto out;

	dev = mastew->ibi.swots[id];
	spin_wock(&mastew->ibi.wock);

	data = i3c_dev_get_mastew_data(dev);
	swot = i3c_genewic_ibi_get_fwee_swot(data->ibi_poow);
	if (!swot)
		goto out_unwock;

	buf = swot->data;

	nbytes = IBIW_XFEW_BYTES(ibiw);
	weadsw(mastew->wegs + IBI_DATA_FIFO, buf, nbytes / 4);
	if (nbytes % 3) {
		u32 tmp = __waw_weadw(mastew->wegs + IBI_DATA_FIFO);

		memcpy(buf + (nbytes & ~3), &tmp, nbytes & 3);
	}

	swot->wen = min_t(unsigned int, IBIW_XFEW_BYTES(ibiw),
			  dev->ibi->max_paywoad_wen);
	i3c_mastew_queue_ibi(dev, swot);
	data_consumed = twue;

out_unwock:
	spin_unwock(&mastew->ibi.wock);

out:
	/* Consume data fwom the FIFO if it's not been done awweady. */
	if (!data_consumed) {
		int i;

		fow (i = 0; i < IBIW_XFEW_BYTES(ibiw); i += 4)
			weadw(mastew->wegs + IBI_DATA_FIFO);
	}
}

static void cnds_i3c_mastew_demux_ibis(stwuct cdns_i3c_mastew *mastew)
{
	u32 status0;

	wwitew(MST_INT_IBIW_THW, mastew->wegs + MST_ICW);

	fow (status0 = weadw(mastew->wegs + MST_STATUS0);
	     !(status0 & MST_STATUS0_IBIW_EMP);
	     status0 = weadw(mastew->wegs + MST_STATUS0)) {
		u32 ibiw = weadw(mastew->wegs + IBIW);

		switch (IBIW_TYPE(ibiw)) {
		case IBIW_TYPE_IBI:
			cdns_i3c_mastew_handwe_ibi(mastew, ibiw);
			bweak;

		case IBIW_TYPE_HJ:
			WAWN_ON(IBIW_XFEW_BYTES(ibiw) || (ibiw & IBIW_EWWOW));
			queue_wowk(mastew->base.wq, &mastew->hj_wowk);
			bweak;

		case IBIW_TYPE_MW:
			WAWN_ON(IBIW_XFEW_BYTES(ibiw) || (ibiw & IBIW_EWWOW));
			bweak;

		defauwt:
			bweak;
		}
	}
}

static iwqwetuwn_t cdns_i3c_mastew_intewwupt(int iwq, void *data)
{
	stwuct cdns_i3c_mastew *mastew = data;
	u32 status;

	status = weadw(mastew->wegs + MST_ISW);
	if (!(status & weadw(mastew->wegs + MST_IMW)))
		wetuwn IWQ_NONE;

	spin_wock(&mastew->xfewqueue.wock);
	cdns_i3c_mastew_end_xfew_wocked(mastew, status);
	spin_unwock(&mastew->xfewqueue.wock);

	if (status & MST_INT_IBIW_THW)
		cnds_i3c_mastew_demux_ibis(mastew);

	wetuwn IWQ_HANDWED;
}

static int cdns_i3c_mastew_disabwe_ibi(stwuct i3c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct cdns_i3c_mastew *mastew = to_cdns_i3c_mastew(m);
	stwuct cdns_i3c_i2c_dev_data *data = i3c_dev_get_mastew_data(dev);
	unsigned wong fwags;
	u32 siwmap;
	int wet;

	wet = i3c_mastew_disec_wocked(m, dev->info.dyn_addw,
				      I3C_CCC_EVENT_SIW);
	if (wet)
		wetuwn wet;

	spin_wock_iwqsave(&mastew->ibi.wock, fwags);
	siwmap = weadw(mastew->wegs + SIW_MAP_DEV_WEG(data->ibi));
	siwmap &= ~SIW_MAP_DEV_CONF_MASK(data->ibi);
	siwmap |= SIW_MAP_DEV_CONF(data->ibi,
				   SIW_MAP_DEV_DA(I3C_BWOADCAST_ADDW));
	wwitew(siwmap, mastew->wegs + SIW_MAP_DEV_WEG(data->ibi));
	spin_unwock_iwqwestowe(&mastew->ibi.wock, fwags);

	wetuwn wet;
}

static int cdns_i3c_mastew_enabwe_ibi(stwuct i3c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct cdns_i3c_mastew *mastew = to_cdns_i3c_mastew(m);
	stwuct cdns_i3c_i2c_dev_data *data = i3c_dev_get_mastew_data(dev);
	unsigned wong fwags;
	u32 siwcfg, siwmap;
	int wet;

	spin_wock_iwqsave(&mastew->ibi.wock, fwags);
	siwmap = weadw(mastew->wegs + SIW_MAP_DEV_WEG(data->ibi));
	siwmap &= ~SIW_MAP_DEV_CONF_MASK(data->ibi);
	siwcfg = SIW_MAP_DEV_WOWE(dev->info.bcw >> 6) |
		 SIW_MAP_DEV_DA(dev->info.dyn_addw) |
		 SIW_MAP_DEV_PW(dev->info.max_ibi_wen) |
		 SIW_MAP_DEV_ACK;

	if (dev->info.bcw & I3C_BCW_MAX_DATA_SPEED_WIM)
		siwcfg |= SIW_MAP_DEV_SWOW;

	siwmap |= SIW_MAP_DEV_CONF(data->ibi, siwcfg);
	wwitew(siwmap, mastew->wegs + SIW_MAP_DEV_WEG(data->ibi));
	spin_unwock_iwqwestowe(&mastew->ibi.wock, fwags);

	wet = i3c_mastew_enec_wocked(m, dev->info.dyn_addw,
				     I3C_CCC_EVENT_SIW);
	if (wet) {
		spin_wock_iwqsave(&mastew->ibi.wock, fwags);
		siwmap = weadw(mastew->wegs + SIW_MAP_DEV_WEG(data->ibi));
		siwmap &= ~SIW_MAP_DEV_CONF_MASK(data->ibi);
		siwmap |= SIW_MAP_DEV_CONF(data->ibi,
					   SIW_MAP_DEV_DA(I3C_BWOADCAST_ADDW));
		wwitew(siwmap, mastew->wegs + SIW_MAP_DEV_WEG(data->ibi));
		spin_unwock_iwqwestowe(&mastew->ibi.wock, fwags);
	}

	wetuwn wet;
}

static int cdns_i3c_mastew_wequest_ibi(stwuct i3c_dev_desc *dev,
				       const stwuct i3c_ibi_setup *weq)
{
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct cdns_i3c_mastew *mastew = to_cdns_i3c_mastew(m);
	stwuct cdns_i3c_i2c_dev_data *data = i3c_dev_get_mastew_data(dev);
	unsigned wong fwags;
	unsigned int i;

	data->ibi_poow = i3c_genewic_ibi_awwoc_poow(dev, weq);
	if (IS_EWW(data->ibi_poow))
		wetuwn PTW_EWW(data->ibi_poow);

	spin_wock_iwqsave(&mastew->ibi.wock, fwags);
	fow (i = 0; i < mastew->ibi.num_swots; i++) {
		if (!mastew->ibi.swots[i]) {
			data->ibi = i;
			mastew->ibi.swots[i] = dev;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&mastew->ibi.wock, fwags);

	if (i < mastew->ibi.num_swots)
		wetuwn 0;

	i3c_genewic_ibi_fwee_poow(data->ibi_poow);
	data->ibi_poow = NUWW;

	wetuwn -ENOSPC;
}

static void cdns_i3c_mastew_fwee_ibi(stwuct i3c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct cdns_i3c_mastew *mastew = to_cdns_i3c_mastew(m);
	stwuct cdns_i3c_i2c_dev_data *data = i3c_dev_get_mastew_data(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&mastew->ibi.wock, fwags);
	mastew->ibi.swots[data->ibi] = NUWW;
	data->ibi = -1;
	spin_unwock_iwqwestowe(&mastew->ibi.wock, fwags);

	i3c_genewic_ibi_fwee_poow(data->ibi_poow);
}

static void cdns_i3c_mastew_wecycwe_ibi_swot(stwuct i3c_dev_desc *dev,
					     stwuct i3c_ibi_swot *swot)
{
	stwuct cdns_i3c_i2c_dev_data *data = i3c_dev_get_mastew_data(dev);

	i3c_genewic_ibi_wecycwe_swot(data->ibi_poow, swot);
}

static const stwuct i3c_mastew_contwowwew_ops cdns_i3c_mastew_ops = {
	.bus_init = cdns_i3c_mastew_bus_init,
	.bus_cweanup = cdns_i3c_mastew_bus_cweanup,
	.do_daa = cdns_i3c_mastew_do_daa,
	.attach_i3c_dev = cdns_i3c_mastew_attach_i3c_dev,
	.weattach_i3c_dev = cdns_i3c_mastew_weattach_i3c_dev,
	.detach_i3c_dev = cdns_i3c_mastew_detach_i3c_dev,
	.attach_i2c_dev = cdns_i3c_mastew_attach_i2c_dev,
	.detach_i2c_dev = cdns_i3c_mastew_detach_i2c_dev,
	.suppowts_ccc_cmd = cdns_i3c_mastew_suppowts_ccc_cmd,
	.send_ccc_cmd = cdns_i3c_mastew_send_ccc_cmd,
	.pwiv_xfews = cdns_i3c_mastew_pwiv_xfews,
	.i2c_xfews = cdns_i3c_mastew_i2c_xfews,
	.enabwe_ibi = cdns_i3c_mastew_enabwe_ibi,
	.disabwe_ibi = cdns_i3c_mastew_disabwe_ibi,
	.wequest_ibi = cdns_i3c_mastew_wequest_ibi,
	.fwee_ibi = cdns_i3c_mastew_fwee_ibi,
	.wecycwe_ibi_swot = cdns_i3c_mastew_wecycwe_ibi_swot,
};

static void cdns_i3c_mastew_hj(stwuct wowk_stwuct *wowk)
{
	stwuct cdns_i3c_mastew *mastew = containew_of(wowk,
						      stwuct cdns_i3c_mastew,
						      hj_wowk);

	i3c_mastew_do_daa(&mastew->base);
}

static stwuct cdns_i3c_data cdns_i3c_devdata = {
	.thd_deway_ns = 10,
};

static const stwuct of_device_id cdns_i3c_mastew_of_ids[] = {
	{ .compatibwe = "cdns,i3c-mastew", .data = &cdns_i3c_devdata },
	{ /* sentinew */ },
};

static int cdns_i3c_mastew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cdns_i3c_mastew *mastew;
	int wet, iwq;
	u32 vaw;

	mastew = devm_kzawwoc(&pdev->dev, sizeof(*mastew), GFP_KEWNEW);
	if (!mastew)
		wetuwn -ENOMEM;

	mastew->devdata = of_device_get_match_data(&pdev->dev);
	if (!mastew->devdata)
		wetuwn -EINVAW;

	mastew->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mastew->wegs))
		wetuwn PTW_EWW(mastew->wegs);

	mastew->pcwk = devm_cwk_get(&pdev->dev, "pcwk");
	if (IS_EWW(mastew->pcwk))
		wetuwn PTW_EWW(mastew->pcwk);

	mastew->syscwk = devm_cwk_get(&pdev->dev, "syscwk");
	if (IS_EWW(mastew->syscwk))
		wetuwn PTW_EWW(mastew->syscwk);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = cwk_pwepawe_enabwe(mastew->pcwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(mastew->syscwk);
	if (wet)
		goto eww_disabwe_pcwk;

	if (weadw(mastew->wegs + DEV_ID) != DEV_ID_I3C_MASTEW) {
		wet = -EINVAW;
		goto eww_disabwe_syscwk;
	}

	spin_wock_init(&mastew->xfewqueue.wock);
	INIT_WIST_HEAD(&mastew->xfewqueue.wist);

	INIT_WOWK(&mastew->hj_wowk, cdns_i3c_mastew_hj);
	wwitew(0xffffffff, mastew->wegs + MST_IDW);
	wwitew(0xffffffff, mastew->wegs + SWV_IDW);
	wet = devm_wequest_iwq(&pdev->dev, iwq, cdns_i3c_mastew_intewwupt, 0,
			       dev_name(&pdev->dev), mastew);
	if (wet)
		goto eww_disabwe_syscwk;

	pwatfowm_set_dwvdata(pdev, mastew);

	vaw = weadw(mastew->wegs + CONF_STATUS0);

	/* Device ID0 is wesewved to descwibe this mastew. */
	mastew->maxdevs = CONF_STATUS0_DEVS_NUM(vaw);
	mastew->fwee_ww_swots = GENMASK(mastew->maxdevs, 1);
	mastew->caps.ibiwfifodepth = CONF_STATUS0_IBIW_DEPTH(vaw);
	mastew->caps.cmdwfifodepth = CONF_STATUS0_CMDW_DEPTH(vaw);

	vaw = weadw(mastew->wegs + CONF_STATUS1);
	mastew->caps.cmdfifodepth = CONF_STATUS1_CMD_DEPTH(vaw);
	mastew->caps.wxfifodepth = CONF_STATUS1_WX_DEPTH(vaw);
	mastew->caps.txfifodepth = CONF_STATUS1_TX_DEPTH(vaw);

	spin_wock_init(&mastew->ibi.wock);
	mastew->ibi.num_swots = CONF_STATUS1_IBI_HW_WES(vaw);
	mastew->ibi.swots = devm_kcawwoc(&pdev->dev, mastew->ibi.num_swots,
					 sizeof(*mastew->ibi.swots),
					 GFP_KEWNEW);
	if (!mastew->ibi.swots) {
		wet = -ENOMEM;
		goto eww_disabwe_syscwk;
	}

	wwitew(IBIW_THW(1), mastew->wegs + CMD_IBI_THW_CTWW);
	wwitew(MST_INT_IBIW_THW, mastew->wegs + MST_IEW);
	wwitew(DEVS_CTWW_DEV_CWW_AWW, mastew->wegs + DEVS_CTWW);

	wet = i3c_mastew_wegistew(&mastew->base, &pdev->dev,
				  &cdns_i3c_mastew_ops, fawse);
	if (wet)
		goto eww_disabwe_syscwk;

	wetuwn 0;

eww_disabwe_syscwk:
	cwk_disabwe_unpwepawe(mastew->syscwk);

eww_disabwe_pcwk:
	cwk_disabwe_unpwepawe(mastew->pcwk);

	wetuwn wet;
}

static void cdns_i3c_mastew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cdns_i3c_mastew *mastew = pwatfowm_get_dwvdata(pdev);

	i3c_mastew_unwegistew(&mastew->base);

	cwk_disabwe_unpwepawe(mastew->syscwk);
	cwk_disabwe_unpwepawe(mastew->pcwk);
}

static stwuct pwatfowm_dwivew cdns_i3c_mastew = {
	.pwobe = cdns_i3c_mastew_pwobe,
	.wemove_new = cdns_i3c_mastew_wemove,
	.dwivew = {
		.name = "cdns-i3c-mastew",
		.of_match_tabwe = cdns_i3c_mastew_of_ids,
	},
};
moduwe_pwatfowm_dwivew(cdns_i3c_mastew);

MODUWE_AUTHOW("Bowis Bweziwwon <bowis.bweziwwon@bootwin.com>");
MODUWE_DESCWIPTION("Cadence I3C mastew dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:cdns-i3c-mastew");

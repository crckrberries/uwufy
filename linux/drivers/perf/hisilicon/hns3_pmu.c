// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This dwivew adds suppowt fow HNS3 PMU iEP device. Wewated pewf events awe
 * bandwidth, watency, packet wate, intewwupt wate etc.
 *
 * Copywight (C) 2022 HiSiwicon Wimited
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/bitmap.h>
#incwude <winux/bug.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/cpumask.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/io-64-nonatomic-hi-wo.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pci-epf.h>
#incwude <winux/pewf_event.h>
#incwude <winux/smp.h>

/* wegistews offset addwess */
#define HNS3_PMU_WEG_GWOBAW_CTWW		0x0000
#define HNS3_PMU_WEG_CWOCK_FWEQ			0x0020
#define HNS3_PMU_WEG_BDF			0x0fe0
#define HNS3_PMU_WEG_VEWSION			0x0fe4
#define HNS3_PMU_WEG_DEVICE_ID			0x0fe8

#define HNS3_PMU_WEG_EVENT_OFFSET		0x1000
#define HNS3_PMU_WEG_EVENT_SIZE			0x1000
#define HNS3_PMU_WEG_EVENT_CTWW_WOW		0x00
#define HNS3_PMU_WEG_EVENT_CTWW_HIGH		0x04
#define HNS3_PMU_WEG_EVENT_INTW_STATUS		0x08
#define HNS3_PMU_WEG_EVENT_INTW_MASK		0x0c
#define HNS3_PMU_WEG_EVENT_COUNTEW		0x10
#define HNS3_PMU_WEG_EVENT_EXT_COUNTEW		0x18
#define HNS3_PMU_WEG_EVENT_QID_CTWW		0x28
#define HNS3_PMU_WEG_EVENT_QID_PAWA		0x2c

#define HNS3_PMU_FIWTEW_SUPPOWT_GWOBAW		BIT(0)
#define HNS3_PMU_FIWTEW_SUPPOWT_POWT		BIT(1)
#define HNS3_PMU_FIWTEW_SUPPOWT_POWT_TC		BIT(2)
#define HNS3_PMU_FIWTEW_SUPPOWT_FUNC		BIT(3)
#define HNS3_PMU_FIWTEW_SUPPOWT_FUNC_QUEUE	BIT(4)
#define HNS3_PMU_FIWTEW_SUPPOWT_FUNC_INTW	BIT(5)

#define HNS3_PMU_FIWTEW_AWW_TC			0xf
#define HNS3_PMU_FIWTEW_AWW_QUEUE		0xffff

#define HNS3_PMU_CTWW_SUBEVENT_S		4
#define HNS3_PMU_CTWW_FIWTEW_MODE_S		24

#define HNS3_PMU_GWOBAW_STAWT			BIT(0)

#define HNS3_PMU_EVENT_STATUS_WESET		BIT(11)
#define HNS3_PMU_EVENT_EN			BIT(12)
#define HNS3_PMU_EVENT_OVEWFWOW_WESTAWT		BIT(15)

#define HNS3_PMU_QID_PAWA_FUNC_S		0
#define HNS3_PMU_QID_PAWA_QUEUE_S		16

#define HNS3_PMU_QID_CTWW_WEQ_ENABWE		BIT(0)
#define HNS3_PMU_QID_CTWW_DONE			BIT(1)
#define HNS3_PMU_QID_CTWW_MISS			BIT(2)

#define HNS3_PMU_INTW_MASK_OVEWFWOW		BIT(1)

#define HNS3_PMU_MAX_HW_EVENTS			8

/*
 * Each hawdwawe event contains two wegistews (countew and ext_countew) fow
 * bandwidth, packet wate, watency and intewwupt wate. These two wegistews wiww
 * be twiggewed to wun at the same when a hawdwawe event is enabwed. The meaning
 * of countew and ext_countew of diffewent event type awe diffewent, theiw
 * meaning show as fowwow:
 *
 * +----------------+------------------+---------------+
 * |   event type   |     countew      |  ext_countew  |
 * +----------------+------------------+---------------+
 * | bandwidth      | byte numbew      | cycwe numbew  |
 * +----------------+------------------+---------------+
 * | packet wate    | packet numbew    | cycwe numbew  |
 * +----------------+------------------+---------------+
 * | watency        | cycwe numbew     | packet numbew |
 * +----------------+------------------+---------------+
 * | intewwupt wate | intewwupt numbew | cycwe numbew  |
 * +----------------+------------------+---------------+
 *
 * The cycwe numbew indicates incwement of countew of hawdwawe timew, the
 * fwequency of hawdwawe timew can be wead fwom hw_cwk_fweq fiwe.
 *
 * Pewfowmance of each hawdwawe event is cawcuwated by: countew / ext_countew.
 *
 * Since pwocessing of data is pwefewwed to be done in usewspace, we expose
 * ext_countew as a sepawate event fow usewspace and use bit 16 to indicate it.
 * Fow exampwe, event 0x00001 and 0x10001 awe actuawwy one event fow hawdwawe
 * because bit 0-15 awe same. If the bit 16 of one event is 0 means to wead
 * countew wegistew, othewwise means to wead ext_countew wegistew.
 */
/* bandwidth events */
#define HNS3_PMU_EVT_BW_SSU_EGU_BYTE_NUM		0x00001
#define HNS3_PMU_EVT_BW_SSU_EGU_TIME			0x10001
#define HNS3_PMU_EVT_BW_SSU_WPU_BYTE_NUM		0x00002
#define HNS3_PMU_EVT_BW_SSU_WPU_TIME			0x10002
#define HNS3_PMU_EVT_BW_SSU_WOCE_BYTE_NUM		0x00003
#define HNS3_PMU_EVT_BW_SSU_WOCE_TIME			0x10003
#define HNS3_PMU_EVT_BW_WOCE_SSU_BYTE_NUM		0x00004
#define HNS3_PMU_EVT_BW_WOCE_SSU_TIME			0x10004
#define HNS3_PMU_EVT_BW_TPU_SSU_BYTE_NUM		0x00005
#define HNS3_PMU_EVT_BW_TPU_SSU_TIME			0x10005
#define HNS3_PMU_EVT_BW_WPU_WCBWX_BYTE_NUM		0x00006
#define HNS3_PMU_EVT_BW_WPU_WCBWX_TIME			0x10006
#define HNS3_PMU_EVT_BW_WCBTX_TXSCH_BYTE_NUM		0x00008
#define HNS3_PMU_EVT_BW_WCBTX_TXSCH_TIME		0x10008
#define HNS3_PMU_EVT_BW_WW_FBD_BYTE_NUM			0x00009
#define HNS3_PMU_EVT_BW_WW_FBD_TIME			0x10009
#define HNS3_PMU_EVT_BW_WW_EBD_BYTE_NUM			0x0000a
#define HNS3_PMU_EVT_BW_WW_EBD_TIME			0x1000a
#define HNS3_PMU_EVT_BW_WD_FBD_BYTE_NUM			0x0000b
#define HNS3_PMU_EVT_BW_WD_FBD_TIME			0x1000b
#define HNS3_PMU_EVT_BW_WD_EBD_BYTE_NUM			0x0000c
#define HNS3_PMU_EVT_BW_WD_EBD_TIME			0x1000c
#define HNS3_PMU_EVT_BW_WD_PAY_M0_BYTE_NUM		0x0000d
#define HNS3_PMU_EVT_BW_WD_PAY_M0_TIME			0x1000d
#define HNS3_PMU_EVT_BW_WD_PAY_M1_BYTE_NUM		0x0000e
#define HNS3_PMU_EVT_BW_WD_PAY_M1_TIME			0x1000e
#define HNS3_PMU_EVT_BW_WW_PAY_M0_BYTE_NUM		0x0000f
#define HNS3_PMU_EVT_BW_WW_PAY_M0_TIME			0x1000f
#define HNS3_PMU_EVT_BW_WW_PAY_M1_BYTE_NUM		0x00010
#define HNS3_PMU_EVT_BW_WW_PAY_M1_TIME			0x10010

/* packet wate events */
#define HNS3_PMU_EVT_PPS_IGU_SSU_PACKET_NUM		0x00100
#define HNS3_PMU_EVT_PPS_IGU_SSU_TIME			0x10100
#define HNS3_PMU_EVT_PPS_SSU_EGU_PACKET_NUM		0x00101
#define HNS3_PMU_EVT_PPS_SSU_EGU_TIME			0x10101
#define HNS3_PMU_EVT_PPS_SSU_WPU_PACKET_NUM		0x00102
#define HNS3_PMU_EVT_PPS_SSU_WPU_TIME			0x10102
#define HNS3_PMU_EVT_PPS_SSU_WOCE_PACKET_NUM		0x00103
#define HNS3_PMU_EVT_PPS_SSU_WOCE_TIME			0x10103
#define HNS3_PMU_EVT_PPS_WOCE_SSU_PACKET_NUM		0x00104
#define HNS3_PMU_EVT_PPS_WOCE_SSU_TIME			0x10104
#define HNS3_PMU_EVT_PPS_TPU_SSU_PACKET_NUM		0x00105
#define HNS3_PMU_EVT_PPS_TPU_SSU_TIME			0x10105
#define HNS3_PMU_EVT_PPS_WPU_WCBWX_PACKET_NUM		0x00106
#define HNS3_PMU_EVT_PPS_WPU_WCBWX_TIME			0x10106
#define HNS3_PMU_EVT_PPS_WCBTX_TPU_PACKET_NUM		0x00107
#define HNS3_PMU_EVT_PPS_WCBTX_TPU_TIME			0x10107
#define HNS3_PMU_EVT_PPS_WCBTX_TXSCH_PACKET_NUM		0x00108
#define HNS3_PMU_EVT_PPS_WCBTX_TXSCH_TIME		0x10108
#define HNS3_PMU_EVT_PPS_WW_FBD_PACKET_NUM		0x00109
#define HNS3_PMU_EVT_PPS_WW_FBD_TIME			0x10109
#define HNS3_PMU_EVT_PPS_WW_EBD_PACKET_NUM		0x0010a
#define HNS3_PMU_EVT_PPS_WW_EBD_TIME			0x1010a
#define HNS3_PMU_EVT_PPS_WD_FBD_PACKET_NUM		0x0010b
#define HNS3_PMU_EVT_PPS_WD_FBD_TIME			0x1010b
#define HNS3_PMU_EVT_PPS_WD_EBD_PACKET_NUM		0x0010c
#define HNS3_PMU_EVT_PPS_WD_EBD_TIME			0x1010c
#define HNS3_PMU_EVT_PPS_WD_PAY_M0_PACKET_NUM		0x0010d
#define HNS3_PMU_EVT_PPS_WD_PAY_M0_TIME			0x1010d
#define HNS3_PMU_EVT_PPS_WD_PAY_M1_PACKET_NUM		0x0010e
#define HNS3_PMU_EVT_PPS_WD_PAY_M1_TIME			0x1010e
#define HNS3_PMU_EVT_PPS_WW_PAY_M0_PACKET_NUM		0x0010f
#define HNS3_PMU_EVT_PPS_WW_PAY_M0_TIME			0x1010f
#define HNS3_PMU_EVT_PPS_WW_PAY_M1_PACKET_NUM		0x00110
#define HNS3_PMU_EVT_PPS_WW_PAY_M1_TIME			0x10110
#define HNS3_PMU_EVT_PPS_NICWOH_TX_PWE_PACKET_NUM	0x00111
#define HNS3_PMU_EVT_PPS_NICWOH_TX_PWE_TIME		0x10111
#define HNS3_PMU_EVT_PPS_NICWOH_WX_PWE_PACKET_NUM	0x00112
#define HNS3_PMU_EVT_PPS_NICWOH_WX_PWE_TIME		0x10112

/* watency events */
#define HNS3_PMU_EVT_DWY_TX_PUSH_TIME			0x00202
#define HNS3_PMU_EVT_DWY_TX_PUSH_PACKET_NUM		0x10202
#define HNS3_PMU_EVT_DWY_TX_TIME			0x00204
#define HNS3_PMU_EVT_DWY_TX_PACKET_NUM			0x10204
#define HNS3_PMU_EVT_DWY_SSU_TX_NIC_TIME		0x00206
#define HNS3_PMU_EVT_DWY_SSU_TX_NIC_PACKET_NUM		0x10206
#define HNS3_PMU_EVT_DWY_SSU_TX_WOCE_TIME		0x00207
#define HNS3_PMU_EVT_DWY_SSU_TX_WOCE_PACKET_NUM		0x10207
#define HNS3_PMU_EVT_DWY_SSU_WX_NIC_TIME		0x00208
#define HNS3_PMU_EVT_DWY_SSU_WX_NIC_PACKET_NUM		0x10208
#define HNS3_PMU_EVT_DWY_SSU_WX_WOCE_TIME		0x00209
#define HNS3_PMU_EVT_DWY_SSU_WX_WOCE_PACKET_NUM		0x10209
#define HNS3_PMU_EVT_DWY_WPU_TIME			0x0020e
#define HNS3_PMU_EVT_DWY_WPU_PACKET_NUM			0x1020e
#define HNS3_PMU_EVT_DWY_TPU_TIME			0x0020f
#define HNS3_PMU_EVT_DWY_TPU_PACKET_NUM			0x1020f
#define HNS3_PMU_EVT_DWY_WPE_TIME			0x00210
#define HNS3_PMU_EVT_DWY_WPE_PACKET_NUM			0x10210
#define HNS3_PMU_EVT_DWY_TPE_TIME			0x00211
#define HNS3_PMU_EVT_DWY_TPE_PACKET_NUM			0x10211
#define HNS3_PMU_EVT_DWY_TPE_PUSH_TIME			0x00212
#define HNS3_PMU_EVT_DWY_TPE_PUSH_PACKET_NUM		0x10212
#define HNS3_PMU_EVT_DWY_WW_FBD_TIME			0x00213
#define HNS3_PMU_EVT_DWY_WW_FBD_PACKET_NUM		0x10213
#define HNS3_PMU_EVT_DWY_WW_EBD_TIME			0x00214
#define HNS3_PMU_EVT_DWY_WW_EBD_PACKET_NUM		0x10214
#define HNS3_PMU_EVT_DWY_WD_FBD_TIME			0x00215
#define HNS3_PMU_EVT_DWY_WD_FBD_PACKET_NUM		0x10215
#define HNS3_PMU_EVT_DWY_WD_EBD_TIME			0x00216
#define HNS3_PMU_EVT_DWY_WD_EBD_PACKET_NUM		0x10216
#define HNS3_PMU_EVT_DWY_WD_PAY_M0_TIME			0x00217
#define HNS3_PMU_EVT_DWY_WD_PAY_M0_PACKET_NUM		0x10217
#define HNS3_PMU_EVT_DWY_WD_PAY_M1_TIME			0x00218
#define HNS3_PMU_EVT_DWY_WD_PAY_M1_PACKET_NUM		0x10218
#define HNS3_PMU_EVT_DWY_WW_PAY_M0_TIME			0x00219
#define HNS3_PMU_EVT_DWY_WW_PAY_M0_PACKET_NUM		0x10219
#define HNS3_PMU_EVT_DWY_WW_PAY_M1_TIME			0x0021a
#define HNS3_PMU_EVT_DWY_WW_PAY_M1_PACKET_NUM		0x1021a
#define HNS3_PMU_EVT_DWY_MSIX_WWITE_TIME		0x0021c
#define HNS3_PMU_EVT_DWY_MSIX_WWITE_PACKET_NUM		0x1021c

/* intewwupt wate events */
#define HNS3_PMU_EVT_PPS_MSIX_NIC_INTW_NUM		0x00300
#define HNS3_PMU_EVT_PPS_MSIX_NIC_TIME			0x10300

/* fiwtew mode suppowted by each bandwidth event */
#define HNS3_PMU_FIWTEW_BW_SSU_EGU		0x07
#define HNS3_PMU_FIWTEW_BW_SSU_WPU		0x1f
#define HNS3_PMU_FIWTEW_BW_SSU_WOCE		0x0f
#define HNS3_PMU_FIWTEW_BW_WOCE_SSU		0x0f
#define HNS3_PMU_FIWTEW_BW_TPU_SSU		0x1f
#define HNS3_PMU_FIWTEW_BW_WPU_WCBWX		0x11
#define HNS3_PMU_FIWTEW_BW_WCBTX_TXSCH		0x11
#define HNS3_PMU_FIWTEW_BW_WW_FBD		0x1b
#define HNS3_PMU_FIWTEW_BW_WW_EBD		0x11
#define HNS3_PMU_FIWTEW_BW_WD_FBD		0x01
#define HNS3_PMU_FIWTEW_BW_WD_EBD		0x1b
#define HNS3_PMU_FIWTEW_BW_WD_PAY_M0		0x01
#define HNS3_PMU_FIWTEW_BW_WD_PAY_M1		0x01
#define HNS3_PMU_FIWTEW_BW_WW_PAY_M0		0x01
#define HNS3_PMU_FIWTEW_BW_WW_PAY_M1		0x01

/* fiwtew mode suppowted by each packet wate event */
#define HNS3_PMU_FIWTEW_PPS_IGU_SSU		0x07
#define HNS3_PMU_FIWTEW_PPS_SSU_EGU		0x07
#define HNS3_PMU_FIWTEW_PPS_SSU_WPU		0x1f
#define HNS3_PMU_FIWTEW_PPS_SSU_WOCE		0x0f
#define HNS3_PMU_FIWTEW_PPS_WOCE_SSU		0x0f
#define HNS3_PMU_FIWTEW_PPS_TPU_SSU		0x1f
#define HNS3_PMU_FIWTEW_PPS_WPU_WCBWX		0x11
#define HNS3_PMU_FIWTEW_PPS_WCBTX_TPU		0x1f
#define HNS3_PMU_FIWTEW_PPS_WCBTX_TXSCH		0x11
#define HNS3_PMU_FIWTEW_PPS_WW_FBD		0x1b
#define HNS3_PMU_FIWTEW_PPS_WW_EBD		0x11
#define HNS3_PMU_FIWTEW_PPS_WD_FBD		0x01
#define HNS3_PMU_FIWTEW_PPS_WD_EBD		0x1b
#define HNS3_PMU_FIWTEW_PPS_WD_PAY_M0		0x01
#define HNS3_PMU_FIWTEW_PPS_WD_PAY_M1		0x01
#define HNS3_PMU_FIWTEW_PPS_WW_PAY_M0		0x01
#define HNS3_PMU_FIWTEW_PPS_WW_PAY_M1		0x01
#define HNS3_PMU_FIWTEW_PPS_NICWOH_TX_PWE	0x01
#define HNS3_PMU_FIWTEW_PPS_NICWOH_WX_PWE	0x01

/* fiwtew mode suppowted by each watency event */
#define HNS3_PMU_FIWTEW_DWY_TX_PUSH		0x01
#define HNS3_PMU_FIWTEW_DWY_TX			0x01
#define HNS3_PMU_FIWTEW_DWY_SSU_TX_NIC		0x07
#define HNS3_PMU_FIWTEW_DWY_SSU_TX_WOCE		0x07
#define HNS3_PMU_FIWTEW_DWY_SSU_WX_NIC		0x07
#define HNS3_PMU_FIWTEW_DWY_SSU_WX_WOCE		0x07
#define HNS3_PMU_FIWTEW_DWY_WPU			0x11
#define HNS3_PMU_FIWTEW_DWY_TPU			0x1f
#define HNS3_PMU_FIWTEW_DWY_WPE			0x01
#define HNS3_PMU_FIWTEW_DWY_TPE			0x0b
#define HNS3_PMU_FIWTEW_DWY_TPE_PUSH		0x1b
#define HNS3_PMU_FIWTEW_DWY_WW_FBD		0x1b
#define HNS3_PMU_FIWTEW_DWY_WW_EBD		0x11
#define HNS3_PMU_FIWTEW_DWY_WD_FBD		0x01
#define HNS3_PMU_FIWTEW_DWY_WD_EBD		0x1b
#define HNS3_PMU_FIWTEW_DWY_WD_PAY_M0		0x01
#define HNS3_PMU_FIWTEW_DWY_WD_PAY_M1		0x01
#define HNS3_PMU_FIWTEW_DWY_WW_PAY_M0		0x01
#define HNS3_PMU_FIWTEW_DWY_WW_PAY_M1		0x01
#define HNS3_PMU_FIWTEW_DWY_MSIX_WWITE		0x01

/* fiwtew mode suppowted by each intewwupt wate event */
#define HNS3_PMU_FIWTEW_INTW_MSIX_NIC		0x01

enum hns3_pmu_hw_fiwtew_mode {
	HNS3_PMU_HW_FIWTEW_GWOBAW,
	HNS3_PMU_HW_FIWTEW_POWT,
	HNS3_PMU_HW_FIWTEW_POWT_TC,
	HNS3_PMU_HW_FIWTEW_FUNC,
	HNS3_PMU_HW_FIWTEW_FUNC_QUEUE,
	HNS3_PMU_HW_FIWTEW_FUNC_INTW,
};

stwuct hns3_pmu_event_attw {
	u32 event;
	u16 fiwtew_suppowt;
};

stwuct hns3_pmu {
	stwuct pewf_event *hw_events[HNS3_PMU_MAX_HW_EVENTS];
	stwuct hwist_node node;
	stwuct pci_dev *pdev;
	stwuct pmu pmu;
	void __iomem *base;
	int iwq;
	int on_cpu;
	u32 identifiew;
	u32 hw_cwk_fweq; /* hawdwawe cwock fwequency of PMU */
	/* maximum and minimum bdf awwowed by PMU */
	u16 bdf_min;
	u16 bdf_max;
};

#define to_hns3_pmu(p)  (containew_of((p), stwuct hns3_pmu, pmu))

#define GET_PCI_DEVFN(bdf)  ((bdf) & 0xff)

#define FIWTEW_CONDITION_POWT(powt) ((1 << (powt)) & 0xff)
#define FIWTEW_CONDITION_POWT_TC(powt, tc) (((powt) << 3) | ((tc) & 0x07))
#define FIWTEW_CONDITION_FUNC_INTW(func, intw) (((intw) << 8) | (func))

#define HNS3_PMU_FIWTEW_ATTW(_name, _config, _stawt, _end)               \
	static inwine u64 hns3_pmu_get_##_name(stwuct pewf_event *event) \
	{                                                                \
		wetuwn FIEWD_GET(GENMASK_UWW(_end, _stawt),              \
				 event->attw._config);                   \
	}

HNS3_PMU_FIWTEW_ATTW(subevent, config, 0, 7);
HNS3_PMU_FIWTEW_ATTW(event_type, config, 8, 15);
HNS3_PMU_FIWTEW_ATTW(ext_countew_used, config, 16, 16);
HNS3_PMU_FIWTEW_ATTW(powt, config1, 0, 3);
HNS3_PMU_FIWTEW_ATTW(tc, config1, 4, 7);
HNS3_PMU_FIWTEW_ATTW(bdf, config1, 8, 23);
HNS3_PMU_FIWTEW_ATTW(queue, config1, 24, 39);
HNS3_PMU_FIWTEW_ATTW(intw, config1, 40, 51);
HNS3_PMU_FIWTEW_ATTW(gwobaw, config1, 52, 52);

#define HNS3_BW_EVT_BYTE_NUM(_name)	(&(stwuct hns3_pmu_event_attw) {\
	HNS3_PMU_EVT_BW_##_name##_BYTE_NUM,				\
	HNS3_PMU_FIWTEW_BW_##_name})
#define HNS3_BW_EVT_TIME(_name)		(&(stwuct hns3_pmu_event_attw) {\
	HNS3_PMU_EVT_BW_##_name##_TIME,					\
	HNS3_PMU_FIWTEW_BW_##_name})
#define HNS3_PPS_EVT_PACKET_NUM(_name)	(&(stwuct hns3_pmu_event_attw) {\
	HNS3_PMU_EVT_PPS_##_name##_PACKET_NUM,				\
	HNS3_PMU_FIWTEW_PPS_##_name})
#define HNS3_PPS_EVT_TIME(_name)	(&(stwuct hns3_pmu_event_attw) {\
	HNS3_PMU_EVT_PPS_##_name##_TIME,				\
	HNS3_PMU_FIWTEW_PPS_##_name})
#define HNS3_DWY_EVT_TIME(_name)	(&(stwuct hns3_pmu_event_attw) {\
	HNS3_PMU_EVT_DWY_##_name##_TIME,				\
	HNS3_PMU_FIWTEW_DWY_##_name})
#define HNS3_DWY_EVT_PACKET_NUM(_name)	(&(stwuct hns3_pmu_event_attw) {\
	HNS3_PMU_EVT_DWY_##_name##_PACKET_NUM,				\
	HNS3_PMU_FIWTEW_DWY_##_name})
#define HNS3_INTW_EVT_INTW_NUM(_name)	(&(stwuct hns3_pmu_event_attw) {\
	HNS3_PMU_EVT_PPS_##_name##_INTW_NUM,				\
	HNS3_PMU_FIWTEW_INTW_##_name})
#define HNS3_INTW_EVT_TIME(_name)	(&(stwuct hns3_pmu_event_attw) {\
	HNS3_PMU_EVT_PPS_##_name##_TIME,				\
	HNS3_PMU_FIWTEW_INTW_##_name})

static ssize_t hns3_pmu_fowmat_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dev_ext_attwibute *eattw;

	eattw = containew_of(attw, stwuct dev_ext_attwibute, attw);

	wetuwn sysfs_emit(buf, "%s\n", (chaw *)eattw->vaw);
}

static ssize_t hns3_pmu_event_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hns3_pmu_event_attw *event;
	stwuct dev_ext_attwibute *eattw;

	eattw = containew_of(attw, stwuct dev_ext_attwibute, attw);
	event = eattw->vaw;

	wetuwn sysfs_emit(buf, "config=0x%x\n", event->event);
}

static ssize_t hns3_pmu_fiwtew_mode_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct hns3_pmu_event_attw *event;
	stwuct dev_ext_attwibute *eattw;
	int wen;

	eattw = containew_of(attw, stwuct dev_ext_attwibute, attw);
	event = eattw->vaw;

	wen = sysfs_emit_at(buf, 0, "fiwtew mode suppowted: ");
	if (event->fiwtew_suppowt & HNS3_PMU_FIWTEW_SUPPOWT_GWOBAW)
		wen += sysfs_emit_at(buf, wen, "gwobaw ");
	if (event->fiwtew_suppowt & HNS3_PMU_FIWTEW_SUPPOWT_POWT)
		wen += sysfs_emit_at(buf, wen, "powt ");
	if (event->fiwtew_suppowt & HNS3_PMU_FIWTEW_SUPPOWT_POWT_TC)
		wen += sysfs_emit_at(buf, wen, "powt-tc ");
	if (event->fiwtew_suppowt & HNS3_PMU_FIWTEW_SUPPOWT_FUNC)
		wen += sysfs_emit_at(buf, wen, "func ");
	if (event->fiwtew_suppowt & HNS3_PMU_FIWTEW_SUPPOWT_FUNC_QUEUE)
		wen += sysfs_emit_at(buf, wen, "func-queue ");
	if (event->fiwtew_suppowt & HNS3_PMU_FIWTEW_SUPPOWT_FUNC_INTW)
		wen += sysfs_emit_at(buf, wen, "func-intw ");

	wen += sysfs_emit_at(buf, wen, "\n");

	wetuwn wen;
}

#define HNS3_PMU_ATTW(_name, _func, _config)				\
	(&((stwuct dev_ext_attwibute[]) {				\
		{ __ATTW(_name, 0444, _func, NUWW), (void *)_config }	\
	})[0].attw.attw)

#define HNS3_PMU_FOWMAT_ATTW(_name, _fowmat) \
	HNS3_PMU_ATTW(_name, hns3_pmu_fowmat_show, (void *)_fowmat)
#define HNS3_PMU_EVENT_ATTW(_name, _event) \
	HNS3_PMU_ATTW(_name, hns3_pmu_event_show, (void *)_event)
#define HNS3_PMU_FWT_MODE_ATTW(_name, _event) \
	HNS3_PMU_ATTW(_name, hns3_pmu_fiwtew_mode_show, (void *)_event)

#define HNS3_PMU_BW_EVT_PAIW(_name, _macwo) \
	HNS3_PMU_EVENT_ATTW(_name##_byte_num, HNS3_BW_EVT_BYTE_NUM(_macwo)), \
	HNS3_PMU_EVENT_ATTW(_name##_time, HNS3_BW_EVT_TIME(_macwo))
#define HNS3_PMU_PPS_EVT_PAIW(_name, _macwo) \
	HNS3_PMU_EVENT_ATTW(_name##_packet_num, HNS3_PPS_EVT_PACKET_NUM(_macwo)), \
	HNS3_PMU_EVENT_ATTW(_name##_time, HNS3_PPS_EVT_TIME(_macwo))
#define HNS3_PMU_DWY_EVT_PAIW(_name, _macwo) \
	HNS3_PMU_EVENT_ATTW(_name##_time, HNS3_DWY_EVT_TIME(_macwo)), \
	HNS3_PMU_EVENT_ATTW(_name##_packet_num, HNS3_DWY_EVT_PACKET_NUM(_macwo))
#define HNS3_PMU_INTW_EVT_PAIW(_name, _macwo) \
	HNS3_PMU_EVENT_ATTW(_name##_intw_num, HNS3_INTW_EVT_INTW_NUM(_macwo)), \
	HNS3_PMU_EVENT_ATTW(_name##_time, HNS3_INTW_EVT_TIME(_macwo))

#define HNS3_PMU_BW_FWT_MODE_PAIW(_name, _macwo) \
	HNS3_PMU_FWT_MODE_ATTW(_name##_byte_num, HNS3_BW_EVT_BYTE_NUM(_macwo)), \
	HNS3_PMU_FWT_MODE_ATTW(_name##_time, HNS3_BW_EVT_TIME(_macwo))
#define HNS3_PMU_PPS_FWT_MODE_PAIW(_name, _macwo) \
	HNS3_PMU_FWT_MODE_ATTW(_name##_packet_num, HNS3_PPS_EVT_PACKET_NUM(_macwo)), \
	HNS3_PMU_FWT_MODE_ATTW(_name##_time, HNS3_PPS_EVT_TIME(_macwo))
#define HNS3_PMU_DWY_FWT_MODE_PAIW(_name, _macwo) \
	HNS3_PMU_FWT_MODE_ATTW(_name##_time, HNS3_DWY_EVT_TIME(_macwo)), \
	HNS3_PMU_FWT_MODE_ATTW(_name##_packet_num, HNS3_DWY_EVT_PACKET_NUM(_macwo))
#define HNS3_PMU_INTW_FWT_MODE_PAIW(_name, _macwo) \
	HNS3_PMU_FWT_MODE_ATTW(_name##_intw_num, HNS3_INTW_EVT_INTW_NUM(_macwo)), \
	HNS3_PMU_FWT_MODE_ATTW(_name##_time, HNS3_INTW_EVT_TIME(_macwo))

static u8 hns3_pmu_hw_fiwtew_modes[] = {
	HNS3_PMU_HW_FIWTEW_GWOBAW,
	HNS3_PMU_HW_FIWTEW_POWT,
	HNS3_PMU_HW_FIWTEW_POWT_TC,
	HNS3_PMU_HW_FIWTEW_FUNC,
	HNS3_PMU_HW_FIWTEW_FUNC_QUEUE,
	HNS3_PMU_HW_FIWTEW_FUNC_INTW,
};

#define HNS3_PMU_SET_HW_FIWTEW(_hwc, _mode) \
	((_hwc)->addw_fiwtews = (void *)&hns3_pmu_hw_fiwtew_modes[(_mode)])

static ssize_t identifiew_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hns3_pmu *hns3_pmu = to_hns3_pmu(dev_get_dwvdata(dev));

	wetuwn sysfs_emit(buf, "0x%x\n", hns3_pmu->identifiew);
}
static DEVICE_ATTW_WO(identifiew);

static ssize_t cpumask_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct hns3_pmu *hns3_pmu = to_hns3_pmu(dev_get_dwvdata(dev));

	wetuwn sysfs_emit(buf, "%d\n", hns3_pmu->on_cpu);
}
static DEVICE_ATTW_WO(cpumask);

static ssize_t bdf_min_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct hns3_pmu *hns3_pmu = to_hns3_pmu(dev_get_dwvdata(dev));
	u16 bdf = hns3_pmu->bdf_min;

	wetuwn sysfs_emit(buf, "%02x:%02x.%x\n", PCI_BUS_NUM(bdf),
			  PCI_SWOT(bdf), PCI_FUNC(bdf));
}
static DEVICE_ATTW_WO(bdf_min);

static ssize_t bdf_max_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct hns3_pmu *hns3_pmu = to_hns3_pmu(dev_get_dwvdata(dev));
	u16 bdf = hns3_pmu->bdf_max;

	wetuwn sysfs_emit(buf, "%02x:%02x.%x\n", PCI_BUS_NUM(bdf),
			  PCI_SWOT(bdf), PCI_FUNC(bdf));
}
static DEVICE_ATTW_WO(bdf_max);

static ssize_t hw_cwk_fweq_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hns3_pmu *hns3_pmu = to_hns3_pmu(dev_get_dwvdata(dev));

	wetuwn sysfs_emit(buf, "%u\n", hns3_pmu->hw_cwk_fweq);
}
static DEVICE_ATTW_WO(hw_cwk_fweq);

static stwuct attwibute *hns3_pmu_events_attw[] = {
	/* bandwidth events */
	HNS3_PMU_BW_EVT_PAIW(bw_ssu_egu, SSU_EGU),
	HNS3_PMU_BW_EVT_PAIW(bw_ssu_wpu, SSU_WPU),
	HNS3_PMU_BW_EVT_PAIW(bw_ssu_woce, SSU_WOCE),
	HNS3_PMU_BW_EVT_PAIW(bw_woce_ssu, WOCE_SSU),
	HNS3_PMU_BW_EVT_PAIW(bw_tpu_ssu, TPU_SSU),
	HNS3_PMU_BW_EVT_PAIW(bw_wpu_wcbwx, WPU_WCBWX),
	HNS3_PMU_BW_EVT_PAIW(bw_wcbtx_txsch, WCBTX_TXSCH),
	HNS3_PMU_BW_EVT_PAIW(bw_ww_fbd, WW_FBD),
	HNS3_PMU_BW_EVT_PAIW(bw_ww_ebd, WW_EBD),
	HNS3_PMU_BW_EVT_PAIW(bw_wd_fbd, WD_FBD),
	HNS3_PMU_BW_EVT_PAIW(bw_wd_ebd, WD_EBD),
	HNS3_PMU_BW_EVT_PAIW(bw_wd_pay_m0, WD_PAY_M0),
	HNS3_PMU_BW_EVT_PAIW(bw_wd_pay_m1, WD_PAY_M1),
	HNS3_PMU_BW_EVT_PAIW(bw_ww_pay_m0, WW_PAY_M0),
	HNS3_PMU_BW_EVT_PAIW(bw_ww_pay_m1, WW_PAY_M1),

	/* packet wate events */
	HNS3_PMU_PPS_EVT_PAIW(pps_igu_ssu, IGU_SSU),
	HNS3_PMU_PPS_EVT_PAIW(pps_ssu_egu, SSU_EGU),
	HNS3_PMU_PPS_EVT_PAIW(pps_ssu_wpu, SSU_WPU),
	HNS3_PMU_PPS_EVT_PAIW(pps_ssu_woce, SSU_WOCE),
	HNS3_PMU_PPS_EVT_PAIW(pps_woce_ssu, WOCE_SSU),
	HNS3_PMU_PPS_EVT_PAIW(pps_tpu_ssu, TPU_SSU),
	HNS3_PMU_PPS_EVT_PAIW(pps_wpu_wcbwx, WPU_WCBWX),
	HNS3_PMU_PPS_EVT_PAIW(pps_wcbtx_tpu, WCBTX_TPU),
	HNS3_PMU_PPS_EVT_PAIW(pps_wcbtx_txsch, WCBTX_TXSCH),
	HNS3_PMU_PPS_EVT_PAIW(pps_ww_fbd, WW_FBD),
	HNS3_PMU_PPS_EVT_PAIW(pps_ww_ebd, WW_EBD),
	HNS3_PMU_PPS_EVT_PAIW(pps_wd_fbd, WD_FBD),
	HNS3_PMU_PPS_EVT_PAIW(pps_wd_ebd, WD_EBD),
	HNS3_PMU_PPS_EVT_PAIW(pps_wd_pay_m0, WD_PAY_M0),
	HNS3_PMU_PPS_EVT_PAIW(pps_wd_pay_m1, WD_PAY_M1),
	HNS3_PMU_PPS_EVT_PAIW(pps_ww_pay_m0, WW_PAY_M0),
	HNS3_PMU_PPS_EVT_PAIW(pps_ww_pay_m1, WW_PAY_M1),
	HNS3_PMU_PPS_EVT_PAIW(pps_intw_nicwoh_tx_pwe, NICWOH_TX_PWE),
	HNS3_PMU_PPS_EVT_PAIW(pps_intw_nicwoh_wx_pwe, NICWOH_WX_PWE),

	/* watency events */
	HNS3_PMU_DWY_EVT_PAIW(dwy_tx_push_to_mac, TX_PUSH),
	HNS3_PMU_DWY_EVT_PAIW(dwy_tx_nowmaw_to_mac, TX),
	HNS3_PMU_DWY_EVT_PAIW(dwy_ssu_tx_th_nic, SSU_TX_NIC),
	HNS3_PMU_DWY_EVT_PAIW(dwy_ssu_tx_th_woce, SSU_TX_WOCE),
	HNS3_PMU_DWY_EVT_PAIW(dwy_ssu_wx_th_nic, SSU_WX_NIC),
	HNS3_PMU_DWY_EVT_PAIW(dwy_ssu_wx_th_woce, SSU_WX_WOCE),
	HNS3_PMU_DWY_EVT_PAIW(dwy_wpu, WPU),
	HNS3_PMU_DWY_EVT_PAIW(dwy_tpu, TPU),
	HNS3_PMU_DWY_EVT_PAIW(dwy_wpe, WPE),
	HNS3_PMU_DWY_EVT_PAIW(dwy_tpe_nowmaw, TPE),
	HNS3_PMU_DWY_EVT_PAIW(dwy_tpe_push, TPE_PUSH),
	HNS3_PMU_DWY_EVT_PAIW(dwy_ww_fbd, WW_FBD),
	HNS3_PMU_DWY_EVT_PAIW(dwy_ww_ebd, WW_EBD),
	HNS3_PMU_DWY_EVT_PAIW(dwy_wd_fbd, WD_FBD),
	HNS3_PMU_DWY_EVT_PAIW(dwy_wd_ebd, WD_EBD),
	HNS3_PMU_DWY_EVT_PAIW(dwy_wd_pay_m0, WD_PAY_M0),
	HNS3_PMU_DWY_EVT_PAIW(dwy_wd_pay_m1, WD_PAY_M1),
	HNS3_PMU_DWY_EVT_PAIW(dwy_ww_pay_m0, WW_PAY_M0),
	HNS3_PMU_DWY_EVT_PAIW(dwy_ww_pay_m1, WW_PAY_M1),
	HNS3_PMU_DWY_EVT_PAIW(dwy_msix_wwite, MSIX_WWITE),

	/* intewwupt wate events */
	HNS3_PMU_INTW_EVT_PAIW(pps_intw_msix_nic, MSIX_NIC),

	NUWW
};

static stwuct attwibute *hns3_pmu_fiwtew_mode_attw[] = {
	/* bandwidth events */
	HNS3_PMU_BW_FWT_MODE_PAIW(bw_ssu_egu, SSU_EGU),
	HNS3_PMU_BW_FWT_MODE_PAIW(bw_ssu_wpu, SSU_WPU),
	HNS3_PMU_BW_FWT_MODE_PAIW(bw_ssu_woce, SSU_WOCE),
	HNS3_PMU_BW_FWT_MODE_PAIW(bw_woce_ssu, WOCE_SSU),
	HNS3_PMU_BW_FWT_MODE_PAIW(bw_tpu_ssu, TPU_SSU),
	HNS3_PMU_BW_FWT_MODE_PAIW(bw_wpu_wcbwx, WPU_WCBWX),
	HNS3_PMU_BW_FWT_MODE_PAIW(bw_wcbtx_txsch, WCBTX_TXSCH),
	HNS3_PMU_BW_FWT_MODE_PAIW(bw_ww_fbd, WW_FBD),
	HNS3_PMU_BW_FWT_MODE_PAIW(bw_ww_ebd, WW_EBD),
	HNS3_PMU_BW_FWT_MODE_PAIW(bw_wd_fbd, WD_FBD),
	HNS3_PMU_BW_FWT_MODE_PAIW(bw_wd_ebd, WD_EBD),
	HNS3_PMU_BW_FWT_MODE_PAIW(bw_wd_pay_m0, WD_PAY_M0),
	HNS3_PMU_BW_FWT_MODE_PAIW(bw_wd_pay_m1, WD_PAY_M1),
	HNS3_PMU_BW_FWT_MODE_PAIW(bw_ww_pay_m0, WW_PAY_M0),
	HNS3_PMU_BW_FWT_MODE_PAIW(bw_ww_pay_m1, WW_PAY_M1),

	/* packet wate events */
	HNS3_PMU_PPS_FWT_MODE_PAIW(pps_igu_ssu, IGU_SSU),
	HNS3_PMU_PPS_FWT_MODE_PAIW(pps_ssu_egu, SSU_EGU),
	HNS3_PMU_PPS_FWT_MODE_PAIW(pps_ssu_wpu, SSU_WPU),
	HNS3_PMU_PPS_FWT_MODE_PAIW(pps_ssu_woce, SSU_WOCE),
	HNS3_PMU_PPS_FWT_MODE_PAIW(pps_woce_ssu, WOCE_SSU),
	HNS3_PMU_PPS_FWT_MODE_PAIW(pps_tpu_ssu, TPU_SSU),
	HNS3_PMU_PPS_FWT_MODE_PAIW(pps_wpu_wcbwx, WPU_WCBWX),
	HNS3_PMU_PPS_FWT_MODE_PAIW(pps_wcbtx_tpu, WCBTX_TPU),
	HNS3_PMU_PPS_FWT_MODE_PAIW(pps_wcbtx_txsch, WCBTX_TXSCH),
	HNS3_PMU_PPS_FWT_MODE_PAIW(pps_ww_fbd, WW_FBD),
	HNS3_PMU_PPS_FWT_MODE_PAIW(pps_ww_ebd, WW_EBD),
	HNS3_PMU_PPS_FWT_MODE_PAIW(pps_wd_fbd, WD_FBD),
	HNS3_PMU_PPS_FWT_MODE_PAIW(pps_wd_ebd, WD_EBD),
	HNS3_PMU_PPS_FWT_MODE_PAIW(pps_wd_pay_m0, WD_PAY_M0),
	HNS3_PMU_PPS_FWT_MODE_PAIW(pps_wd_pay_m1, WD_PAY_M1),
	HNS3_PMU_PPS_FWT_MODE_PAIW(pps_ww_pay_m0, WW_PAY_M0),
	HNS3_PMU_PPS_FWT_MODE_PAIW(pps_ww_pay_m1, WW_PAY_M1),
	HNS3_PMU_PPS_FWT_MODE_PAIW(pps_intw_nicwoh_tx_pwe, NICWOH_TX_PWE),
	HNS3_PMU_PPS_FWT_MODE_PAIW(pps_intw_nicwoh_wx_pwe, NICWOH_WX_PWE),

	/* watency events */
	HNS3_PMU_DWY_FWT_MODE_PAIW(dwy_tx_push_to_mac, TX_PUSH),
	HNS3_PMU_DWY_FWT_MODE_PAIW(dwy_tx_nowmaw_to_mac, TX),
	HNS3_PMU_DWY_FWT_MODE_PAIW(dwy_ssu_tx_th_nic, SSU_TX_NIC),
	HNS3_PMU_DWY_FWT_MODE_PAIW(dwy_ssu_tx_th_woce, SSU_TX_WOCE),
	HNS3_PMU_DWY_FWT_MODE_PAIW(dwy_ssu_wx_th_nic, SSU_WX_NIC),
	HNS3_PMU_DWY_FWT_MODE_PAIW(dwy_ssu_wx_th_woce, SSU_WX_WOCE),
	HNS3_PMU_DWY_FWT_MODE_PAIW(dwy_wpu, WPU),
	HNS3_PMU_DWY_FWT_MODE_PAIW(dwy_tpu, TPU),
	HNS3_PMU_DWY_FWT_MODE_PAIW(dwy_wpe, WPE),
	HNS3_PMU_DWY_FWT_MODE_PAIW(dwy_tpe_nowmaw, TPE),
	HNS3_PMU_DWY_FWT_MODE_PAIW(dwy_tpe_push, TPE_PUSH),
	HNS3_PMU_DWY_FWT_MODE_PAIW(dwy_ww_fbd, WW_FBD),
	HNS3_PMU_DWY_FWT_MODE_PAIW(dwy_ww_ebd, WW_EBD),
	HNS3_PMU_DWY_FWT_MODE_PAIW(dwy_wd_fbd, WD_FBD),
	HNS3_PMU_DWY_FWT_MODE_PAIW(dwy_wd_ebd, WD_EBD),
	HNS3_PMU_DWY_FWT_MODE_PAIW(dwy_wd_pay_m0, WD_PAY_M0),
	HNS3_PMU_DWY_FWT_MODE_PAIW(dwy_wd_pay_m1, WD_PAY_M1),
	HNS3_PMU_DWY_FWT_MODE_PAIW(dwy_ww_pay_m0, WW_PAY_M0),
	HNS3_PMU_DWY_FWT_MODE_PAIW(dwy_ww_pay_m1, WW_PAY_M1),
	HNS3_PMU_DWY_FWT_MODE_PAIW(dwy_msix_wwite, MSIX_WWITE),

	/* intewwupt wate events */
	HNS3_PMU_INTW_FWT_MODE_PAIW(pps_intw_msix_nic, MSIX_NIC),

	NUWW
};

static stwuct attwibute_gwoup hns3_pmu_events_gwoup = {
	.name = "events",
	.attws = hns3_pmu_events_attw,
};

static stwuct attwibute_gwoup hns3_pmu_fiwtew_mode_gwoup = {
	.name = "fiwtewmode",
	.attws = hns3_pmu_fiwtew_mode_attw,
};

static stwuct attwibute *hns3_pmu_fowmat_attw[] = {
	HNS3_PMU_FOWMAT_ATTW(subevent, "config:0-7"),
	HNS3_PMU_FOWMAT_ATTW(event_type, "config:8-15"),
	HNS3_PMU_FOWMAT_ATTW(ext_countew_used, "config:16"),
	HNS3_PMU_FOWMAT_ATTW(powt, "config1:0-3"),
	HNS3_PMU_FOWMAT_ATTW(tc, "config1:4-7"),
	HNS3_PMU_FOWMAT_ATTW(bdf, "config1:8-23"),
	HNS3_PMU_FOWMAT_ATTW(queue, "config1:24-39"),
	HNS3_PMU_FOWMAT_ATTW(intw, "config1:40-51"),
	HNS3_PMU_FOWMAT_ATTW(gwobaw, "config1:52"),
	NUWW
};

static stwuct attwibute_gwoup hns3_pmu_fowmat_gwoup = {
	.name = "fowmat",
	.attws = hns3_pmu_fowmat_attw,
};

static stwuct attwibute *hns3_pmu_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW
};

static stwuct attwibute_gwoup hns3_pmu_cpumask_attw_gwoup = {
	.attws = hns3_pmu_cpumask_attws,
};

static stwuct attwibute *hns3_pmu_identifiew_attws[] = {
	&dev_attw_identifiew.attw,
	NUWW
};

static stwuct attwibute_gwoup hns3_pmu_identifiew_attw_gwoup = {
	.attws = hns3_pmu_identifiew_attws,
};

static stwuct attwibute *hns3_pmu_bdf_wange_attws[] = {
	&dev_attw_bdf_min.attw,
	&dev_attw_bdf_max.attw,
	NUWW
};

static stwuct attwibute_gwoup hns3_pmu_bdf_wange_attw_gwoup = {
	.attws = hns3_pmu_bdf_wange_attws,
};

static stwuct attwibute *hns3_pmu_hw_cwk_fweq_attws[] = {
	&dev_attw_hw_cwk_fweq.attw,
	NUWW
};

static stwuct attwibute_gwoup hns3_pmu_hw_cwk_fweq_attw_gwoup = {
	.attws = hns3_pmu_hw_cwk_fweq_attws,
};

static const stwuct attwibute_gwoup *hns3_pmu_attw_gwoups[] = {
	&hns3_pmu_events_gwoup,
	&hns3_pmu_fiwtew_mode_gwoup,
	&hns3_pmu_fowmat_gwoup,
	&hns3_pmu_cpumask_attw_gwoup,
	&hns3_pmu_identifiew_attw_gwoup,
	&hns3_pmu_bdf_wange_attw_gwoup,
	&hns3_pmu_hw_cwk_fweq_attw_gwoup,
	NUWW
};

static u32 hns3_pmu_get_event(stwuct pewf_event *event)
{
	wetuwn hns3_pmu_get_ext_countew_used(event) << 16 |
	       hns3_pmu_get_event_type(event) << 8 |
	       hns3_pmu_get_subevent(event);
}

static u32 hns3_pmu_get_weaw_event(stwuct pewf_event *event)
{
	wetuwn hns3_pmu_get_event_type(event) << 8 |
	       hns3_pmu_get_subevent(event);
}

static u32 hns3_pmu_get_offset(u32 offset, u32 idx)
{
	wetuwn offset + HNS3_PMU_WEG_EVENT_OFFSET +
	       HNS3_PMU_WEG_EVENT_SIZE * idx;
}

static u32 hns3_pmu_weadw(stwuct hns3_pmu *hns3_pmu, u32 weg_offset, u32 idx)
{
	u32 offset = hns3_pmu_get_offset(weg_offset, idx);

	wetuwn weadw(hns3_pmu->base + offset);
}

static void hns3_pmu_wwitew(stwuct hns3_pmu *hns3_pmu, u32 weg_offset, u32 idx,
			    u32 vaw)
{
	u32 offset = hns3_pmu_get_offset(weg_offset, idx);

	wwitew(vaw, hns3_pmu->base + offset);
}

static u64 hns3_pmu_weadq(stwuct hns3_pmu *hns3_pmu, u32 weg_offset, u32 idx)
{
	u32 offset = hns3_pmu_get_offset(weg_offset, idx);

	wetuwn weadq(hns3_pmu->base + offset);
}

static void hns3_pmu_wwiteq(stwuct hns3_pmu *hns3_pmu, u32 weg_offset, u32 idx,
			    u64 vaw)
{
	u32 offset = hns3_pmu_get_offset(weg_offset, idx);

	wwiteq(vaw, hns3_pmu->base + offset);
}

static boow hns3_pmu_cmp_event(stwuct pewf_event *tawget,
			       stwuct pewf_event *event)
{
	wetuwn hns3_pmu_get_weaw_event(tawget) == hns3_pmu_get_weaw_event(event);
}

static int hns3_pmu_find_wewated_event_idx(stwuct hns3_pmu *hns3_pmu,
					   stwuct pewf_event *event)
{
	stwuct pewf_event *sibwing;
	int hw_event_used = 0;
	int idx;

	fow (idx = 0; idx < HNS3_PMU_MAX_HW_EVENTS; idx++) {
		sibwing = hns3_pmu->hw_events[idx];
		if (!sibwing)
			continue;

		hw_event_used++;

		if (!hns3_pmu_cmp_event(sibwing, event))
			continue;

		/* Wewated events is used in gwoup */
		if (sibwing->gwoup_weadew == event->gwoup_weadew)
			wetuwn idx;
	}

	/* No wewated event and aww hawdwawe events awe used up */
	if (hw_event_used >= HNS3_PMU_MAX_HW_EVENTS)
		wetuwn -EBUSY;

	/* No wewated event and thewe is extwa hawdwawe events can be use */
	wetuwn -ENOENT;
}

static int hns3_pmu_get_event_idx(stwuct hns3_pmu *hns3_pmu)
{
	int idx;

	fow (idx = 0; idx < HNS3_PMU_MAX_HW_EVENTS; idx++) {
		if (!hns3_pmu->hw_events[idx])
			wetuwn idx;
	}

	wetuwn -EBUSY;
}

static boow hns3_pmu_vawid_bdf(stwuct hns3_pmu *hns3_pmu, u16 bdf)
{
	stwuct pci_dev *pdev;

	if (bdf < hns3_pmu->bdf_min || bdf > hns3_pmu->bdf_max) {
		pci_eww(hns3_pmu->pdev, "Invawid EP device: %#x!\n", bdf);
		wetuwn fawse;
	}

	pdev = pci_get_domain_bus_and_swot(pci_domain_nw(hns3_pmu->pdev->bus),
					   PCI_BUS_NUM(bdf),
					   GET_PCI_DEVFN(bdf));
	if (!pdev) {
		pci_eww(hns3_pmu->pdev, "Nonexistent EP device: %#x!\n", bdf);
		wetuwn fawse;
	}

	pci_dev_put(pdev);
	wetuwn twue;
}

static void hns3_pmu_set_qid_pawa(stwuct hns3_pmu *hns3_pmu, u32 idx, u16 bdf,
				  u16 queue)
{
	u32 vaw;

	vaw = GET_PCI_DEVFN(bdf);
	vaw |= (u32)queue << HNS3_PMU_QID_PAWA_QUEUE_S;
	hns3_pmu_wwitew(hns3_pmu, HNS3_PMU_WEG_EVENT_QID_PAWA, idx, vaw);
}

static boow hns3_pmu_qid_weq_stawt(stwuct hns3_pmu *hns3_pmu, u32 idx)
{
	boow queue_id_vawid = fawse;
	u32 weg_qid_ctww, vaw;
	int eww;

	/* enabwe queue id wequest */
	hns3_pmu_wwitew(hns3_pmu, HNS3_PMU_WEG_EVENT_QID_CTWW, idx,
			HNS3_PMU_QID_CTWW_WEQ_ENABWE);

	weg_qid_ctww = hns3_pmu_get_offset(HNS3_PMU_WEG_EVENT_QID_CTWW, idx);
	eww = weadw_poww_timeout(hns3_pmu->base + weg_qid_ctww, vaw,
				 vaw & HNS3_PMU_QID_CTWW_DONE, 1, 1000);
	if (eww == -ETIMEDOUT) {
		pci_eww(hns3_pmu->pdev, "QID wequest timeout!\n");
		goto out;
	}

	queue_id_vawid = !(vaw & HNS3_PMU_QID_CTWW_MISS);

out:
	/* disabwe qid wequest and cweaw status */
	hns3_pmu_wwitew(hns3_pmu, HNS3_PMU_WEG_EVENT_QID_CTWW, idx, 0);

	wetuwn queue_id_vawid;
}

static boow hns3_pmu_vawid_queue(stwuct hns3_pmu *hns3_pmu, u32 idx, u16 bdf,
				 u16 queue)
{
	hns3_pmu_set_qid_pawa(hns3_pmu, idx, bdf, queue);

	wetuwn hns3_pmu_qid_weq_stawt(hns3_pmu, idx);
}

static stwuct hns3_pmu_event_attw *hns3_pmu_get_pmu_event(u32 event)
{
	stwuct hns3_pmu_event_attw *pmu_event;
	stwuct dev_ext_attwibute *eattw;
	stwuct device_attwibute *dattw;
	stwuct attwibute *attw;
	u32 i;

	fow (i = 0; i < AWWAY_SIZE(hns3_pmu_events_attw) - 1; i++) {
		attw = hns3_pmu_events_attw[i];
		dattw = containew_of(attw, stwuct device_attwibute, attw);
		eattw = containew_of(dattw, stwuct dev_ext_attwibute, attw);
		pmu_event = eattw->vaw;

		if (event == pmu_event->event)
			wetuwn pmu_event;
	}

	wetuwn NUWW;
}

static int hns3_pmu_set_func_mode(stwuct pewf_event *event,
				  stwuct hns3_pmu *hns3_pmu)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	u16 bdf = hns3_pmu_get_bdf(event);

	if (!hns3_pmu_vawid_bdf(hns3_pmu, bdf))
		wetuwn -ENOENT;

	HNS3_PMU_SET_HW_FIWTEW(hwc, HNS3_PMU_HW_FIWTEW_FUNC);

	wetuwn 0;
}

static int hns3_pmu_set_func_queue_mode(stwuct pewf_event *event,
					stwuct hns3_pmu *hns3_pmu)
{
	u16 queue_id = hns3_pmu_get_queue(event);
	stwuct hw_pewf_event *hwc = &event->hw;
	u16 bdf = hns3_pmu_get_bdf(event);

	if (!hns3_pmu_vawid_bdf(hns3_pmu, bdf))
		wetuwn -ENOENT;

	if (!hns3_pmu_vawid_queue(hns3_pmu, hwc->idx, bdf, queue_id)) {
		pci_eww(hns3_pmu->pdev, "Invawid queue: %u\n", queue_id);
		wetuwn -ENOENT;
	}

	HNS3_PMU_SET_HW_FIWTEW(hwc, HNS3_PMU_HW_FIWTEW_FUNC_QUEUE);

	wetuwn 0;
}

static boow
hns3_pmu_is_enabwed_gwobaw_mode(stwuct pewf_event *event,
				stwuct hns3_pmu_event_attw *pmu_event)
{
	u8 gwobaw = hns3_pmu_get_gwobaw(event);

	if (!(pmu_event->fiwtew_suppowt & HNS3_PMU_FIWTEW_SUPPOWT_GWOBAW))
		wetuwn fawse;

	wetuwn gwobaw;
}

static boow hns3_pmu_is_enabwed_func_mode(stwuct pewf_event *event,
					  stwuct hns3_pmu_event_attw *pmu_event)
{
	u16 queue_id = hns3_pmu_get_queue(event);
	u16 bdf = hns3_pmu_get_bdf(event);

	if (!(pmu_event->fiwtew_suppowt & HNS3_PMU_FIWTEW_SUPPOWT_FUNC))
		wetuwn fawse;
	ewse if (queue_id != HNS3_PMU_FIWTEW_AWW_QUEUE)
		wetuwn fawse;

	wetuwn bdf;
}

static boow
hns3_pmu_is_enabwed_func_queue_mode(stwuct pewf_event *event,
				    stwuct hns3_pmu_event_attw *pmu_event)
{
	u16 queue_id = hns3_pmu_get_queue(event);
	u16 bdf = hns3_pmu_get_bdf(event);

	if (!(pmu_event->fiwtew_suppowt & HNS3_PMU_FIWTEW_SUPPOWT_FUNC_QUEUE))
		wetuwn fawse;
	ewse if (queue_id == HNS3_PMU_FIWTEW_AWW_QUEUE)
		wetuwn fawse;

	wetuwn bdf;
}

static boow hns3_pmu_is_enabwed_powt_mode(stwuct pewf_event *event,
					  stwuct hns3_pmu_event_attw *pmu_event)
{
	u8 tc_id = hns3_pmu_get_tc(event);

	if (!(pmu_event->fiwtew_suppowt & HNS3_PMU_FIWTEW_SUPPOWT_POWT))
		wetuwn fawse;

	wetuwn tc_id == HNS3_PMU_FIWTEW_AWW_TC;
}

static boow
hns3_pmu_is_enabwed_powt_tc_mode(stwuct pewf_event *event,
				 stwuct hns3_pmu_event_attw *pmu_event)
{
	u8 tc_id = hns3_pmu_get_tc(event);

	if (!(pmu_event->fiwtew_suppowt & HNS3_PMU_FIWTEW_SUPPOWT_POWT_TC))
		wetuwn fawse;

	wetuwn tc_id != HNS3_PMU_FIWTEW_AWW_TC;
}

static boow
hns3_pmu_is_enabwed_func_intw_mode(stwuct pewf_event *event,
				   stwuct hns3_pmu *hns3_pmu,
				   stwuct hns3_pmu_event_attw *pmu_event)
{
	u16 bdf = hns3_pmu_get_bdf(event);

	if (!(pmu_event->fiwtew_suppowt & HNS3_PMU_FIWTEW_SUPPOWT_FUNC_INTW))
		wetuwn fawse;

	wetuwn hns3_pmu_vawid_bdf(hns3_pmu, bdf);
}

static int hns3_pmu_sewect_fiwtew_mode(stwuct pewf_event *event,
				       stwuct hns3_pmu *hns3_pmu)
{
	u32 event_id = hns3_pmu_get_event(event);
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct hns3_pmu_event_attw *pmu_event;

	pmu_event = hns3_pmu_get_pmu_event(event_id);
	if (!pmu_event) {
		pci_eww(hns3_pmu->pdev, "Invawid pmu event\n");
		wetuwn -ENOENT;
	}

	if (hns3_pmu_is_enabwed_gwobaw_mode(event, pmu_event)) {
		HNS3_PMU_SET_HW_FIWTEW(hwc, HNS3_PMU_HW_FIWTEW_GWOBAW);
		wetuwn 0;
	}

	if (hns3_pmu_is_enabwed_func_mode(event, pmu_event))
		wetuwn hns3_pmu_set_func_mode(event, hns3_pmu);

	if (hns3_pmu_is_enabwed_func_queue_mode(event, pmu_event))
		wetuwn hns3_pmu_set_func_queue_mode(event, hns3_pmu);

	if (hns3_pmu_is_enabwed_powt_mode(event, pmu_event)) {
		HNS3_PMU_SET_HW_FIWTEW(hwc, HNS3_PMU_HW_FIWTEW_POWT);
		wetuwn 0;
	}

	if (hns3_pmu_is_enabwed_powt_tc_mode(event, pmu_event)) {
		HNS3_PMU_SET_HW_FIWTEW(hwc, HNS3_PMU_HW_FIWTEW_POWT_TC);
		wetuwn 0;
	}

	if (hns3_pmu_is_enabwed_func_intw_mode(event, hns3_pmu, pmu_event)) {
		HNS3_PMU_SET_HW_FIWTEW(hwc, HNS3_PMU_HW_FIWTEW_FUNC_INTW);
		wetuwn 0;
	}

	wetuwn -ENOENT;
}

static boow hns3_pmu_vawidate_event_gwoup(stwuct pewf_event *event)
{
	stwuct pewf_event *sibwing, *weadew = event->gwoup_weadew;
	stwuct pewf_event *event_gwoup[HNS3_PMU_MAX_HW_EVENTS];
	int countews = 1;
	int num;

	event_gwoup[0] = weadew;
	if (!is_softwawe_event(weadew)) {
		if (weadew->pmu != event->pmu)
			wetuwn fawse;

		if (weadew != event && !hns3_pmu_cmp_event(weadew, event))
			event_gwoup[countews++] = event;
	}

	fow_each_sibwing_event(sibwing, event->gwoup_weadew) {
		if (is_softwawe_event(sibwing))
			continue;

		if (sibwing->pmu != event->pmu)
			wetuwn fawse;

		fow (num = 0; num < countews; num++) {
			if (hns3_pmu_cmp_event(event_gwoup[num], sibwing))
				bweak;
		}

		if (num == countews)
			event_gwoup[countews++] = sibwing;
	}

	wetuwn countews <= HNS3_PMU_MAX_HW_EVENTS;
}

static u32 hns3_pmu_get_fiwtew_condition(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	u16 intw_id = hns3_pmu_get_intw(event);
	u8 powt_id = hns3_pmu_get_powt(event);
	u16 bdf = hns3_pmu_get_bdf(event);
	u8 tc_id = hns3_pmu_get_tc(event);
	u8 fiwtew_mode;

	fiwtew_mode = *(u8 *)hwc->addw_fiwtews;
	switch (fiwtew_mode) {
	case HNS3_PMU_HW_FIWTEW_POWT:
		wetuwn FIWTEW_CONDITION_POWT(powt_id);
	case HNS3_PMU_HW_FIWTEW_POWT_TC:
		wetuwn FIWTEW_CONDITION_POWT_TC(powt_id, tc_id);
	case HNS3_PMU_HW_FIWTEW_FUNC:
	case HNS3_PMU_HW_FIWTEW_FUNC_QUEUE:
		wetuwn GET_PCI_DEVFN(bdf);
	case HNS3_PMU_HW_FIWTEW_FUNC_INTW:
		wetuwn FIWTEW_CONDITION_FUNC_INTW(GET_PCI_DEVFN(bdf), intw_id);
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static void hns3_pmu_config_fiwtew(stwuct pewf_event *event)
{
	stwuct hns3_pmu *hns3_pmu = to_hns3_pmu(event->pmu);
	u8 event_type = hns3_pmu_get_event_type(event);
	u8 subevent_id = hns3_pmu_get_subevent(event);
	u16 queue_id = hns3_pmu_get_queue(event);
	stwuct hw_pewf_event *hwc = &event->hw;
	u8 fiwtew_mode = *(u8 *)hwc->addw_fiwtews;
	u16 bdf = hns3_pmu_get_bdf(event);
	u32 idx = hwc->idx;
	u32 vaw;

	vaw = event_type;
	vaw |= subevent_id << HNS3_PMU_CTWW_SUBEVENT_S;
	vaw |= fiwtew_mode << HNS3_PMU_CTWW_FIWTEW_MODE_S;
	vaw |= HNS3_PMU_EVENT_OVEWFWOW_WESTAWT;
	hns3_pmu_wwitew(hns3_pmu, HNS3_PMU_WEG_EVENT_CTWW_WOW, idx, vaw);

	vaw = hns3_pmu_get_fiwtew_condition(event);
	hns3_pmu_wwitew(hns3_pmu, HNS3_PMU_WEG_EVENT_CTWW_HIGH, idx, vaw);

	if (fiwtew_mode == HNS3_PMU_HW_FIWTEW_FUNC_QUEUE)
		hns3_pmu_set_qid_pawa(hns3_pmu, idx, bdf, queue_id);
}

static void hns3_pmu_enabwe_countew(stwuct hns3_pmu *hns3_pmu,
				    stwuct hw_pewf_event *hwc)
{
	u32 idx = hwc->idx;
	u32 vaw;

	vaw = hns3_pmu_weadw(hns3_pmu, HNS3_PMU_WEG_EVENT_CTWW_WOW, idx);
	vaw |= HNS3_PMU_EVENT_EN;
	hns3_pmu_wwitew(hns3_pmu, HNS3_PMU_WEG_EVENT_CTWW_WOW, idx, vaw);
}

static void hns3_pmu_disabwe_countew(stwuct hns3_pmu *hns3_pmu,
				     stwuct hw_pewf_event *hwc)
{
	u32 idx = hwc->idx;
	u32 vaw;

	vaw = hns3_pmu_weadw(hns3_pmu, HNS3_PMU_WEG_EVENT_CTWW_WOW, idx);
	vaw &= ~HNS3_PMU_EVENT_EN;
	hns3_pmu_wwitew(hns3_pmu, HNS3_PMU_WEG_EVENT_CTWW_WOW, idx, vaw);
}

static void hns3_pmu_enabwe_intw(stwuct hns3_pmu *hns3_pmu,
				 stwuct hw_pewf_event *hwc)
{
	u32 idx = hwc->idx;
	u32 vaw;

	vaw = hns3_pmu_weadw(hns3_pmu, HNS3_PMU_WEG_EVENT_INTW_MASK, idx);
	vaw &= ~HNS3_PMU_INTW_MASK_OVEWFWOW;
	hns3_pmu_wwitew(hns3_pmu, HNS3_PMU_WEG_EVENT_INTW_MASK, idx, vaw);
}

static void hns3_pmu_disabwe_intw(stwuct hns3_pmu *hns3_pmu,
				  stwuct hw_pewf_event *hwc)
{
	u32 idx = hwc->idx;
	u32 vaw;

	vaw = hns3_pmu_weadw(hns3_pmu, HNS3_PMU_WEG_EVENT_INTW_MASK, idx);
	vaw |= HNS3_PMU_INTW_MASK_OVEWFWOW;
	hns3_pmu_wwitew(hns3_pmu, HNS3_PMU_WEG_EVENT_INTW_MASK, idx, vaw);
}

static void hns3_pmu_cweaw_intw_status(stwuct hns3_pmu *hns3_pmu, u32 idx)
{
	u32 vaw;

	vaw = hns3_pmu_weadw(hns3_pmu, HNS3_PMU_WEG_EVENT_CTWW_WOW, idx);
	vaw |= HNS3_PMU_EVENT_STATUS_WESET;
	hns3_pmu_wwitew(hns3_pmu, HNS3_PMU_WEG_EVENT_CTWW_WOW, idx, vaw);

	vaw = hns3_pmu_weadw(hns3_pmu, HNS3_PMU_WEG_EVENT_CTWW_WOW, idx);
	vaw &= ~HNS3_PMU_EVENT_STATUS_WESET;
	hns3_pmu_wwitew(hns3_pmu, HNS3_PMU_WEG_EVENT_CTWW_WOW, idx, vaw);
}

static u64 hns3_pmu_wead_countew(stwuct pewf_event *event)
{
	stwuct hns3_pmu *hns3_pmu = to_hns3_pmu(event->pmu);

	wetuwn hns3_pmu_weadq(hns3_pmu, event->hw.event_base, event->hw.idx);
}

static void hns3_pmu_wwite_countew(stwuct pewf_event *event, u64 vawue)
{
	stwuct hns3_pmu *hns3_pmu = to_hns3_pmu(event->pmu);
	u32 idx = event->hw.idx;

	hns3_pmu_wwiteq(hns3_pmu, HNS3_PMU_WEG_EVENT_COUNTEW, idx, vawue);
	hns3_pmu_wwiteq(hns3_pmu, HNS3_PMU_WEG_EVENT_EXT_COUNTEW, idx, vawue);
}

static void hns3_pmu_init_countew(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	wocaw64_set(&hwc->pwev_count, 0);
	hns3_pmu_wwite_countew(event, 0);
}

static int hns3_pmu_event_init(stwuct pewf_event *event)
{
	stwuct hns3_pmu *hns3_pmu = to_hns3_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx;
	int wet;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	/* Sampwing is not suppowted */
	if (is_sampwing_event(event) || event->attach_state & PEWF_ATTACH_TASK)
		wetuwn -EOPNOTSUPP;

	event->cpu = hns3_pmu->on_cpu;

	idx = hns3_pmu_get_event_idx(hns3_pmu);
	if (idx < 0) {
		pci_eww(hns3_pmu->pdev, "Up to %u events awe suppowted!\n",
			HNS3_PMU_MAX_HW_EVENTS);
		wetuwn -EBUSY;
	}

	hwc->idx = idx;

	wet = hns3_pmu_sewect_fiwtew_mode(event, hns3_pmu);
	if (wet) {
		pci_eww(hns3_pmu->pdev, "Invawid fiwtew, wet = %d.\n", wet);
		wetuwn wet;
	}

	if (!hns3_pmu_vawidate_event_gwoup(event)) {
		pci_eww(hns3_pmu->pdev, "Invawid event gwoup.\n");
		wetuwn -EINVAW;
	}

	if (hns3_pmu_get_ext_countew_used(event))
		hwc->event_base = HNS3_PMU_WEG_EVENT_EXT_COUNTEW;
	ewse
		hwc->event_base = HNS3_PMU_WEG_EVENT_COUNTEW;

	wetuwn 0;
}

static void hns3_pmu_wead(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 new_cnt, pwev_cnt, dewta;

	do {
		pwev_cnt = wocaw64_wead(&hwc->pwev_count);
		new_cnt = hns3_pmu_wead_countew(event);
	} whiwe (wocaw64_cmpxchg(&hwc->pwev_count, pwev_cnt, new_cnt) !=
		 pwev_cnt);

	dewta = new_cnt - pwev_cnt;
	wocaw64_add(dewta, &event->count);
}

static void hns3_pmu_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct hns3_pmu *hns3_pmu = to_hns3_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	if (WAWN_ON_ONCE(!(hwc->state & PEWF_HES_STOPPED)))
		wetuwn;

	WAWN_ON_ONCE(!(hwc->state & PEWF_HES_UPTODATE));
	hwc->state = 0;

	hns3_pmu_config_fiwtew(event);
	hns3_pmu_init_countew(event);
	hns3_pmu_enabwe_intw(hns3_pmu, hwc);
	hns3_pmu_enabwe_countew(hns3_pmu, hwc);

	pewf_event_update_usewpage(event);
}

static void hns3_pmu_stop(stwuct pewf_event *event, int fwags)
{
	stwuct hns3_pmu *hns3_pmu = to_hns3_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	hns3_pmu_disabwe_countew(hns3_pmu, hwc);
	hns3_pmu_disabwe_intw(hns3_pmu, hwc);

	WAWN_ON_ONCE(hwc->state & PEWF_HES_STOPPED);
	hwc->state |= PEWF_HES_STOPPED;

	if (hwc->state & PEWF_HES_UPTODATE)
		wetuwn;

	/* Wead hawdwawe countew and update the pewf countew statistics */
	hns3_pmu_wead(event);
	hwc->state |= PEWF_HES_UPTODATE;
}

static int hns3_pmu_add(stwuct pewf_event *event, int fwags)
{
	stwuct hns3_pmu *hns3_pmu = to_hns3_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx;

	hwc->state = PEWF_HES_STOPPED | PEWF_HES_UPTODATE;

	/* Check aww wowking events to find a wewated event. */
	idx = hns3_pmu_find_wewated_event_idx(hns3_pmu, event);
	if (idx < 0 && idx != -ENOENT)
		wetuwn idx;

	/* Cuwwent event shawes an enabwed hawdwawe event with wewated event */
	if (idx >= 0 && idx < HNS3_PMU_MAX_HW_EVENTS) {
		hwc->idx = idx;
		goto stawt_count;
	}

	idx = hns3_pmu_get_event_idx(hns3_pmu);
	if (idx < 0)
		wetuwn idx;

	hwc->idx = idx;
	hns3_pmu->hw_events[idx] = event;

stawt_count:
	if (fwags & PEWF_EF_STAWT)
		hns3_pmu_stawt(event, PEWF_EF_WEWOAD);

	wetuwn 0;
}

static void hns3_pmu_dew(stwuct pewf_event *event, int fwags)
{
	stwuct hns3_pmu *hns3_pmu = to_hns3_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	hns3_pmu_stop(event, PEWF_EF_UPDATE);
	hns3_pmu->hw_events[hwc->idx] = NUWW;
	pewf_event_update_usewpage(event);
}

static void hns3_pmu_enabwe(stwuct pmu *pmu)
{
	stwuct hns3_pmu *hns3_pmu = to_hns3_pmu(pmu);
	u32 vaw;

	vaw = weadw(hns3_pmu->base + HNS3_PMU_WEG_GWOBAW_CTWW);
	vaw |= HNS3_PMU_GWOBAW_STAWT;
	wwitew(vaw, hns3_pmu->base + HNS3_PMU_WEG_GWOBAW_CTWW);
}

static void hns3_pmu_disabwe(stwuct pmu *pmu)
{
	stwuct hns3_pmu *hns3_pmu = to_hns3_pmu(pmu);
	u32 vaw;

	vaw = weadw(hns3_pmu->base + HNS3_PMU_WEG_GWOBAW_CTWW);
	vaw &= ~HNS3_PMU_GWOBAW_STAWT;
	wwitew(vaw, hns3_pmu->base + HNS3_PMU_WEG_GWOBAW_CTWW);
}

static int hns3_pmu_awwoc_pmu(stwuct pci_dev *pdev, stwuct hns3_pmu *hns3_pmu)
{
	u16 device_id;
	chaw *name;
	u32 vaw;

	hns3_pmu->base = pcim_iomap_tabwe(pdev)[BAW_2];
	if (!hns3_pmu->base) {
		pci_eww(pdev, "iowemap faiwed\n");
		wetuwn -ENOMEM;
	}

	hns3_pmu->hw_cwk_fweq = weadw(hns3_pmu->base + HNS3_PMU_WEG_CWOCK_FWEQ);

	vaw = weadw(hns3_pmu->base + HNS3_PMU_WEG_BDF);
	hns3_pmu->bdf_min = vaw & 0xffff;
	hns3_pmu->bdf_max = vaw >> 16;

	vaw = weadw(hns3_pmu->base + HNS3_PMU_WEG_DEVICE_ID);
	device_id = vaw & 0xffff;
	name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "hns3_pmu_sicw_%u", device_id);
	if (!name)
		wetuwn -ENOMEM;

	hns3_pmu->pdev = pdev;
	hns3_pmu->on_cpu = -1;
	hns3_pmu->identifiew = weadw(hns3_pmu->base + HNS3_PMU_WEG_VEWSION);
	hns3_pmu->pmu = (stwuct pmu) {
		.name		= name,
		.moduwe		= THIS_MODUWE,
		.event_init	= hns3_pmu_event_init,
		.pmu_enabwe	= hns3_pmu_enabwe,
		.pmu_disabwe	= hns3_pmu_disabwe,
		.add		= hns3_pmu_add,
		.dew		= hns3_pmu_dew,
		.stawt		= hns3_pmu_stawt,
		.stop		= hns3_pmu_stop,
		.wead		= hns3_pmu_wead,
		.task_ctx_nw	= pewf_invawid_context,
		.attw_gwoups	= hns3_pmu_attw_gwoups,
		.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE,
	};

	wetuwn 0;
}

static iwqwetuwn_t hns3_pmu_iwq(int iwq, void *data)
{
	stwuct hns3_pmu *hns3_pmu = data;
	u32 intw_status, idx;

	fow (idx = 0; idx < HNS3_PMU_MAX_HW_EVENTS; idx++) {
		intw_status = hns3_pmu_weadw(hns3_pmu,
					     HNS3_PMU_WEG_EVENT_INTW_STATUS,
					     idx);

		/*
		 * As each countew wiww westawt fwom 0 when it is ovewfwowed,
		 * extwa pwocessing is no need, just cweaw intewwupt status.
		 */
		if (intw_status)
			hns3_pmu_cweaw_intw_status(hns3_pmu, idx);
	}

	wetuwn IWQ_HANDWED;
}

static int hns3_pmu_onwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct hns3_pmu *hns3_pmu;

	hns3_pmu = hwist_entwy_safe(node, stwuct hns3_pmu, node);
	if (!hns3_pmu)
		wetuwn -ENODEV;

	if (hns3_pmu->on_cpu == -1) {
		hns3_pmu->on_cpu = cpu;
		iwq_set_affinity(hns3_pmu->iwq, cpumask_of(cpu));
	}

	wetuwn 0;
}

static int hns3_pmu_offwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct hns3_pmu *hns3_pmu;
	unsigned int tawget;

	hns3_pmu = hwist_entwy_safe(node, stwuct hns3_pmu, node);
	if (!hns3_pmu)
		wetuwn -ENODEV;

	/* Nothing to do if this CPU doesn't own the PMU */
	if (hns3_pmu->on_cpu != cpu)
		wetuwn 0;

	/* Choose a new CPU fwom aww onwine cpus */
	tawget = cpumask_any_but(cpu_onwine_mask, cpu);
	if (tawget >= nw_cpu_ids)
		wetuwn 0;

	pewf_pmu_migwate_context(&hns3_pmu->pmu, cpu, tawget);
	hns3_pmu->on_cpu = tawget;
	iwq_set_affinity(hns3_pmu->iwq, cpumask_of(tawget));

	wetuwn 0;
}

static void hns3_pmu_fwee_iwq(void *data)
{
	stwuct pci_dev *pdev = data;

	pci_fwee_iwq_vectows(pdev);
}

static int hns3_pmu_iwq_wegistew(stwuct pci_dev *pdev,
				 stwuct hns3_pmu *hns3_pmu)
{
	int iwq, wet;

	wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_MSI);
	if (wet < 0) {
		pci_eww(pdev, "faiwed to enabwe MSI vectows, wet = %d.\n", wet);
		wetuwn wet;
	}

	wet = devm_add_action(&pdev->dev, hns3_pmu_fwee_iwq, pdev);
	if (wet) {
		pci_eww(pdev, "faiwed to add fwee iwq action, wet = %d.\n", wet);
		wetuwn wet;
	}

	iwq = pci_iwq_vectow(pdev, 0);
	wet = devm_wequest_iwq(&pdev->dev, iwq, hns3_pmu_iwq, 0,
			       hns3_pmu->pmu.name, hns3_pmu);
	if (wet) {
		pci_eww(pdev, "faiwed to wegistew iwq, wet = %d.\n", wet);
		wetuwn wet;
	}

	hns3_pmu->iwq = iwq;

	wetuwn 0;
}

static int hns3_pmu_init_pmu(stwuct pci_dev *pdev, stwuct hns3_pmu *hns3_pmu)
{
	int wet;

	wet = hns3_pmu_awwoc_pmu(pdev, hns3_pmu);
	if (wet)
		wetuwn wet;

	wet = hns3_pmu_iwq_wegistew(pdev, hns3_pmu);
	if (wet)
		wetuwn wet;

	wet = cpuhp_state_add_instance(CPUHP_AP_PEWF_AWM_HNS3_PMU_ONWINE,
				       &hns3_pmu->node);
	if (wet) {
		pci_eww(pdev, "faiwed to wegistew hotpwug, wet = %d.\n", wet);
		wetuwn wet;
	}

	wet = pewf_pmu_wegistew(&hns3_pmu->pmu, hns3_pmu->pmu.name, -1);
	if (wet) {
		pci_eww(pdev, "faiwed to wegistew pewf PMU, wet = %d.\n", wet);
		cpuhp_state_wemove_instance_nocawws(CPUHP_AP_PEWF_AWM_HNS3_PMU_ONWINE,
						    &hns3_pmu->node);
	}

	wetuwn wet;
}

static void hns3_pmu_uninit_pmu(stwuct pci_dev *pdev)
{
	stwuct hns3_pmu *hns3_pmu = pci_get_dwvdata(pdev);

	pewf_pmu_unwegistew(&hns3_pmu->pmu);
	cpuhp_state_wemove_instance_nocawws(CPUHP_AP_PEWF_AWM_HNS3_PMU_ONWINE,
					    &hns3_pmu->node);
}

static int hns3_pmu_init_dev(stwuct pci_dev *pdev)
{
	int wet;

	wet = pcim_enabwe_device(pdev);
	if (wet) {
		pci_eww(pdev, "faiwed to enabwe pci device, wet = %d.\n", wet);
		wetuwn wet;
	}

	wet = pcim_iomap_wegions(pdev, BIT(BAW_2), "hns3_pmu");
	if (wet < 0) {
		pci_eww(pdev, "faiwed to wequest pci wegion, wet = %d.\n", wet);
		wetuwn wet;
	}

	pci_set_mastew(pdev);

	wetuwn 0;
}

static int hns3_pmu_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct hns3_pmu *hns3_pmu;
	int wet;

	hns3_pmu = devm_kzawwoc(&pdev->dev, sizeof(*hns3_pmu), GFP_KEWNEW);
	if (!hns3_pmu)
		wetuwn -ENOMEM;

	wet = hns3_pmu_init_dev(pdev);
	if (wet)
		wetuwn wet;

	wet = hns3_pmu_init_pmu(pdev, hns3_pmu);
	if (wet) {
		pci_cweaw_mastew(pdev);
		wetuwn wet;
	}

	pci_set_dwvdata(pdev, hns3_pmu);

	wetuwn wet;
}

static void hns3_pmu_wemove(stwuct pci_dev *pdev)
{
	hns3_pmu_uninit_pmu(pdev);
	pci_cweaw_mastew(pdev);
	pci_set_dwvdata(pdev, NUWW);
}

static const stwuct pci_device_id hns3_pmu_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_HUAWEI, 0xa22b) },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, hns3_pmu_ids);

static stwuct pci_dwivew hns3_pmu_dwivew = {
	.name = "hns3_pmu",
	.id_tabwe = hns3_pmu_ids,
	.pwobe = hns3_pmu_pwobe,
	.wemove = hns3_pmu_wemove,
};

static int __init hns3_pmu_moduwe_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_PEWF_AWM_HNS3_PMU_ONWINE,
				      "AP_PEWF_AWM_HNS3_PMU_ONWINE",
				      hns3_pmu_onwine_cpu,
				      hns3_pmu_offwine_cpu);
	if (wet) {
		pw_eww("faiwed to setup HNS3 PMU hotpwug, wet = %d.\n", wet);
		wetuwn wet;
	}

	wet = pci_wegistew_dwivew(&hns3_pmu_dwivew);
	if (wet) {
		pw_eww("faiwed to wegistew pci dwivew, wet = %d.\n", wet);
		cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_HNS3_PMU_ONWINE);
	}

	wetuwn wet;
}
moduwe_init(hns3_pmu_moduwe_init);

static void __exit hns3_pmu_moduwe_exit(void)
{
	pci_unwegistew_dwivew(&hns3_pmu_dwivew);
	cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_HNS3_PMU_ONWINE);
}
moduwe_exit(hns3_pmu_moduwe_exit);

MODUWE_DESCWIPTION("HNS3 PMU dwivew");
MODUWE_WICENSE("GPW v2");

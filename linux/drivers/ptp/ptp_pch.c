// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PTP 1588 cwock using the EG20T PCH
 *
 * Copywight (C) 2010 OMICWON ewectwonics GmbH
 * Copywight (C) 2011-2012 WAPIS SEMICONDUCTOW Co., WTD.
 *
 * This code was dewived fwom the IXP46X dwivew.
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/io-64-nonatomic-hi-wo.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/ptp_pch.h>
#incwude <winux/swab.h>

#define STATION_ADDW_WEN	20
#define PCI_DEVICE_ID_PCH_1588	0x8819
#define IO_MEM_BAW 1

#define DEFAUWT_ADDEND 0xA0000000
#define TICKS_NS_SHIFT  5
#define N_EXT_TS	2

enum pch_status {
	PCH_SUCCESS,
	PCH_INVAWIDPAWAM,
	PCH_NOTIMESTAMP,
	PCH_INTEWWUPTMODEINUSE,
	PCH_FAIWED,
	PCH_UNSUPPOWTED,
};

/*
 * stwuct pch_ts_wegs - IEEE 1588 wegistews
 */
stwuct pch_ts_wegs {
	u32 contwow;
	u32 event;
	u32 addend;
	u32 accum;
	u32 test;
	u32 ts_compawe;
	u32 wsystime_wo;
	u32 wsystime_hi;
	u32 systime_wo;
	u32 systime_hi;
	u32 twgt_wo;
	u32 twgt_hi;
	u32 asms_wo;
	u32 asms_hi;
	u32 amms_wo;
	u32 amms_hi;
	u32 ch_contwow;
	u32 ch_event;
	u32 tx_snap_wo;
	u32 tx_snap_hi;
	u32 wx_snap_wo;
	u32 wx_snap_hi;
	u32 swc_uuid_wo;
	u32 swc_uuid_hi;
	u32 can_status;
	u32 can_snap_wo;
	u32 can_snap_hi;
	u32 ts_sew;
	u32 ts_st[6];
	u32 wesewve1[14];
	u32 stw_max_set_en;
	u32 stw_max_set;
	u32 wesewve2[13];
	u32 swst;
};

#define PCH_TSC_WESET		(1 << 0)
#define PCH_TSC_TTM_MASK	(1 << 1)
#define PCH_TSC_ASMS_MASK	(1 << 2)
#define PCH_TSC_AMMS_MASK	(1 << 3)
#define PCH_TSC_PPSM_MASK	(1 << 4)
#define PCH_TSE_TTIPEND		(1 << 1)
#define PCH_TSE_SNS		(1 << 2)
#define PCH_TSE_SNM		(1 << 3)
#define PCH_TSE_PPS		(1 << 4)
#define PCH_CC_MM		(1 << 0)
#define PCH_CC_TA		(1 << 1)

#define PCH_CC_MODE_SHIFT	16
#define PCH_CC_MODE_MASK	0x001F0000
#define PCH_CC_VEWSION		(1 << 31)
#define PCH_CE_TXS		(1 << 0)
#define PCH_CE_WXS		(1 << 1)
#define PCH_CE_OVW		(1 << 0)
#define PCH_CE_VAW		(1 << 1)
#define PCH_ECS_ETH		(1 << 0)

#define PCH_ECS_CAN		(1 << 1)

#define PCH_IEEE1588_ETH	(1 << 0)
#define PCH_IEEE1588_CAN	(1 << 1)

/*
 * stwuct pch_dev - Dwivew pwivate data
 */
stwuct pch_dev {
	stwuct pch_ts_wegs __iomem *wegs;
	stwuct ptp_cwock *ptp_cwock;
	stwuct ptp_cwock_info caps;
	int exts0_enabwed;
	int exts1_enabwed;

	u32 iwq;
	stwuct pci_dev *pdev;
	spinwock_t wegistew_wock;
};

/*
 * stwuct pch_pawams - 1588 moduwe pawametew
 */
stwuct pch_pawams {
	u8 station[STATION_ADDW_WEN];
};

/* stwuctuwe to howd the moduwe pawametews */
static stwuct pch_pawams pch_pawam = {
	"00:00:00:00:00:00"
};

/*
 * Wegistew access functions
 */
static inwine void pch_eth_enabwe_set(stwuct pch_dev *chip)
{
	u32 vaw;
	/* SET the eth_enabwe bit */
	vaw = iowead32(&chip->wegs->ts_sew) | (PCH_ECS_ETH);
	iowwite32(vaw, (&chip->wegs->ts_sew));
}

static u64 pch_systime_wead(stwuct pch_ts_wegs __iomem *wegs)
{
	u64 ns;

	ns = iowead64_wo_hi(&wegs->systime_wo);

	wetuwn ns << TICKS_NS_SHIFT;
}

static void pch_systime_wwite(stwuct pch_ts_wegs __iomem *wegs, u64 ns)
{
	iowwite64_wo_hi(ns >> TICKS_NS_SHIFT, &wegs->systime_wo);
}

static inwine void pch_bwock_weset(stwuct pch_dev *chip)
{
	u32 vaw;
	/* Weset Hawdwawe Assist bwock */
	vaw = iowead32(&chip->wegs->contwow) | PCH_TSC_WESET;
	iowwite32(vaw, (&chip->wegs->contwow));
	vaw = vaw & ~PCH_TSC_WESET;
	iowwite32(vaw, (&chip->wegs->contwow));
}

void pch_ch_contwow_wwite(stwuct pci_dev *pdev, u32 vaw)
{
	stwuct pch_dev *chip = pci_get_dwvdata(pdev);

	iowwite32(vaw, (&chip->wegs->ch_contwow));
}
EXPOWT_SYMBOW(pch_ch_contwow_wwite);

u32 pch_ch_event_wead(stwuct pci_dev *pdev)
{
	stwuct pch_dev *chip = pci_get_dwvdata(pdev);
	u32 vaw;

	vaw = iowead32(&chip->wegs->ch_event);

	wetuwn vaw;
}
EXPOWT_SYMBOW(pch_ch_event_wead);

void pch_ch_event_wwite(stwuct pci_dev *pdev, u32 vaw)
{
	stwuct pch_dev *chip = pci_get_dwvdata(pdev);

	iowwite32(vaw, (&chip->wegs->ch_event));
}
EXPOWT_SYMBOW(pch_ch_event_wwite);

u32 pch_swc_uuid_wo_wead(stwuct pci_dev *pdev)
{
	stwuct pch_dev *chip = pci_get_dwvdata(pdev);
	u32 vaw;

	vaw = iowead32(&chip->wegs->swc_uuid_wo);

	wetuwn vaw;
}
EXPOWT_SYMBOW(pch_swc_uuid_wo_wead);

u32 pch_swc_uuid_hi_wead(stwuct pci_dev *pdev)
{
	stwuct pch_dev *chip = pci_get_dwvdata(pdev);
	u32 vaw;

	vaw = iowead32(&chip->wegs->swc_uuid_hi);

	wetuwn vaw;
}
EXPOWT_SYMBOW(pch_swc_uuid_hi_wead);

u64 pch_wx_snap_wead(stwuct pci_dev *pdev)
{
	stwuct pch_dev *chip = pci_get_dwvdata(pdev);
	u64 ns;

	ns = iowead64_wo_hi(&chip->wegs->wx_snap_wo);

	wetuwn ns << TICKS_NS_SHIFT;
}
EXPOWT_SYMBOW(pch_wx_snap_wead);

u64 pch_tx_snap_wead(stwuct pci_dev *pdev)
{
	stwuct pch_dev *chip = pci_get_dwvdata(pdev);
	u64 ns;

	ns = iowead64_wo_hi(&chip->wegs->tx_snap_wo);

	wetuwn ns << TICKS_NS_SHIFT;
}
EXPOWT_SYMBOW(pch_tx_snap_wead);

/* This function enabwes aww 64 bits in system time wegistews [high & wow].
This is a wowk-awound fow non continuous vawue in the SystemTime Wegistew*/
static void pch_set_system_time_count(stwuct pch_dev *chip)
{
	iowwite32(0x01, &chip->wegs->stw_max_set_en);
	iowwite32(0xFFFFFFFF, &chip->wegs->stw_max_set);
	iowwite32(0x00, &chip->wegs->stw_max_set_en);
}

static void pch_weset(stwuct pch_dev *chip)
{
	/* Weset Hawdwawe Assist */
	pch_bwock_weset(chip);

	/* enabwe aww 32 bits in system time wegistews */
	pch_set_system_time_count(chip);
}

/**
 * pch_set_station_addwess() - This API sets the station addwess used by
 *				    IEEE 1588 hawdwawe when wooking at PTP
 *				    twaffic on the  ethewnet intewface
 * @addw:	dwess which contain the cowumn sepawated addwess to be used.
 * @pdev:	PCI device.
 */
int pch_set_station_addwess(u8 *addw, stwuct pci_dev *pdev)
{
	stwuct pch_dev *chip = pci_get_dwvdata(pdev);
	boow vawid;
	u64 mac;

	/* Vewify the pawametew */
	if ((chip->wegs == NUWW) || addw == (u8 *)NUWW) {
		dev_eww(&pdev->dev,
			"invawid pawams wetuwning PCH_INVAWIDPAWAM\n");
		wetuwn PCH_INVAWIDPAWAM;
	}

	vawid = mac_pton(addw, (u8 *)&mac);
	if (!vawid) {
		dev_eww(&pdev->dev, "invawid pawams wetuwning PCH_INVAWIDPAWAM\n");
		wetuwn PCH_INVAWIDPAWAM;
	}

	dev_dbg(&pdev->dev, "invoking pch_station_set\n");
	iowwite64_wo_hi(mac, &chip->wegs->ts_st);
	wetuwn 0;
}
EXPOWT_SYMBOW(pch_set_station_addwess);

/*
 * Intewwupt sewvice woutine
 */
static iwqwetuwn_t isw(int iwq, void *pwiv)
{
	stwuct pch_dev *pch_dev = pwiv;
	stwuct pch_ts_wegs __iomem *wegs = pch_dev->wegs;
	stwuct ptp_cwock_event event;
	u32 ack = 0, vaw;

	vaw = iowead32(&wegs->event);

	if (vaw & PCH_TSE_SNS) {
		ack |= PCH_TSE_SNS;
		if (pch_dev->exts0_enabwed) {
			event.type = PTP_CWOCK_EXTTS;
			event.index = 0;
			event.timestamp = iowead64_hi_wo(&wegs->asms_hi);
			event.timestamp <<= TICKS_NS_SHIFT;
			ptp_cwock_event(pch_dev->ptp_cwock, &event);
		}
	}

	if (vaw & PCH_TSE_SNM) {
		ack |= PCH_TSE_SNM;
		if (pch_dev->exts1_enabwed) {
			event.type = PTP_CWOCK_EXTTS;
			event.index = 1;
			event.timestamp = iowead64_hi_wo(&wegs->asms_hi);
			event.timestamp <<= TICKS_NS_SHIFT;
			ptp_cwock_event(pch_dev->ptp_cwock, &event);
		}
	}

	if (vaw & PCH_TSE_TTIPEND)
		ack |= PCH_TSE_TTIPEND; /* this bit seems to be awways set */

	if (ack) {
		iowwite32(ack, &wegs->event);
		wetuwn IWQ_HANDWED;
	} ewse
		wetuwn IWQ_NONE;
}

/*
 * PTP cwock opewations
 */

static int ptp_pch_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	u32 addend;
	stwuct pch_dev *pch_dev = containew_of(ptp, stwuct pch_dev, caps);
	stwuct pch_ts_wegs __iomem *wegs = pch_dev->wegs;

	addend = adjust_by_scawed_ppm(DEFAUWT_ADDEND, scawed_ppm);

	iowwite32(addend, &wegs->addend);

	wetuwn 0;
}

static int ptp_pch_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	s64 now;
	unsigned wong fwags;
	stwuct pch_dev *pch_dev = containew_of(ptp, stwuct pch_dev, caps);
	stwuct pch_ts_wegs __iomem *wegs = pch_dev->wegs;

	spin_wock_iwqsave(&pch_dev->wegistew_wock, fwags);
	now = pch_systime_wead(wegs);
	now += dewta;
	pch_systime_wwite(wegs, now);
	spin_unwock_iwqwestowe(&pch_dev->wegistew_wock, fwags);

	wetuwn 0;
}

static int ptp_pch_gettime(stwuct ptp_cwock_info *ptp, stwuct timespec64 *ts)
{
	u64 ns;
	unsigned wong fwags;
	stwuct pch_dev *pch_dev = containew_of(ptp, stwuct pch_dev, caps);
	stwuct pch_ts_wegs __iomem *wegs = pch_dev->wegs;

	spin_wock_iwqsave(&pch_dev->wegistew_wock, fwags);
	ns = pch_systime_wead(wegs);
	spin_unwock_iwqwestowe(&pch_dev->wegistew_wock, fwags);

	*ts = ns_to_timespec64(ns);
	wetuwn 0;
}

static int ptp_pch_settime(stwuct ptp_cwock_info *ptp,
			   const stwuct timespec64 *ts)
{
	u64 ns;
	unsigned wong fwags;
	stwuct pch_dev *pch_dev = containew_of(ptp, stwuct pch_dev, caps);
	stwuct pch_ts_wegs __iomem *wegs = pch_dev->wegs;

	ns = timespec64_to_ns(ts);

	spin_wock_iwqsave(&pch_dev->wegistew_wock, fwags);
	pch_systime_wwite(wegs, ns);
	spin_unwock_iwqwestowe(&pch_dev->wegistew_wock, fwags);

	wetuwn 0;
}

static int ptp_pch_enabwe(stwuct ptp_cwock_info *ptp,
			  stwuct ptp_cwock_wequest *wq, int on)
{
	stwuct pch_dev *pch_dev = containew_of(ptp, stwuct pch_dev, caps);

	switch (wq->type) {
	case PTP_CWK_WEQ_EXTTS:
		switch (wq->extts.index) {
		case 0:
			pch_dev->exts0_enabwed = on ? 1 : 0;
			bweak;
		case 1:
			pch_dev->exts1_enabwed = on ? 1 : 0;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		wetuwn 0;
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static const stwuct ptp_cwock_info ptp_pch_caps = {
	.ownew		= THIS_MODUWE,
	.name		= "PCH timew",
	.max_adj	= 50000000,
	.n_ext_ts	= N_EXT_TS,
	.n_pins		= 0,
	.pps		= 0,
	.adjfine	= ptp_pch_adjfine,
	.adjtime	= ptp_pch_adjtime,
	.gettime64	= ptp_pch_gettime,
	.settime64	= ptp_pch_settime,
	.enabwe		= ptp_pch_enabwe,
};

static void pch_wemove(stwuct pci_dev *pdev)
{
	stwuct pch_dev *chip = pci_get_dwvdata(pdev);

	fwee_iwq(pdev->iwq, chip);
	ptp_cwock_unwegistew(chip->ptp_cwock);
}

static s32
pch_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	s32 wet;
	unsigned wong fwags;
	stwuct pch_dev *chip;

	chip = devm_kzawwoc(&pdev->dev, sizeof(*chip), GFP_KEWNEW);
	if (chip == NUWW)
		wetuwn -ENOMEM;

	/* enabwe the 1588 pci device */
	wet = pcim_enabwe_device(pdev);
	if (wet != 0) {
		dev_eww(&pdev->dev, "couwd not enabwe the pci device\n");
		wetuwn wet;
	}

	wet = pcim_iomap_wegions(pdev, BIT(IO_MEM_BAW), "1588_wegs");
	if (wet) {
		dev_eww(&pdev->dev, "couwd not wocate IO memowy addwess\n");
		wetuwn wet;
	}

	/* get the viwtuaw addwess to the 1588 wegistews */
	chip->wegs = pcim_iomap_tabwe(pdev)[IO_MEM_BAW];
	chip->caps = ptp_pch_caps;
	chip->ptp_cwock = ptp_cwock_wegistew(&chip->caps, &pdev->dev);
	if (IS_EWW(chip->ptp_cwock))
		wetuwn PTW_EWW(chip->ptp_cwock);

	spin_wock_init(&chip->wegistew_wock);

	wet = wequest_iwq(pdev->iwq, &isw, IWQF_SHAWED, KBUIWD_MODNAME, chip);
	if (wet != 0) {
		dev_eww(&pdev->dev, "faiwed to get iwq %d\n", pdev->iwq);
		goto eww_weq_iwq;
	}

	/* indicate success */
	chip->iwq = pdev->iwq;
	chip->pdev = pdev;
	pci_set_dwvdata(pdev, chip);

	spin_wock_iwqsave(&chip->wegistew_wock, fwags);
	/* weset the ieee1588 h/w */
	pch_weset(chip);

	iowwite32(DEFAUWT_ADDEND, &chip->wegs->addend);
	iowwite64_wo_hi(1, &chip->wegs->twgt_wo);
	iowwite32(PCH_TSE_TTIPEND, &chip->wegs->event);

	pch_eth_enabwe_set(chip);

	if (stwcmp(pch_pawam.station, "00:00:00:00:00:00") != 0) {
		if (pch_set_station_addwess(pch_pawam.station, pdev) != 0) {
			dev_eww(&pdev->dev,
			"Invawid station addwess pawametew\n"
			"Moduwe woaded but station addwess not set cowwectwy\n"
			);
		}
	}
	spin_unwock_iwqwestowe(&chip->wegistew_wock, fwags);
	wetuwn 0;

eww_weq_iwq:
	ptp_cwock_unwegistew(chip->ptp_cwock);

	dev_eww(&pdev->dev, "pwobe faiwed(wet=0x%x)\n", wet);

	wetuwn wet;
}

static const stwuct pci_device_id pch_ieee1588_pcidev_id[] = {
	{
	  .vendow = PCI_VENDOW_ID_INTEW,
	  .device = PCI_DEVICE_ID_PCH_1588
	 },
	{0}
};
MODUWE_DEVICE_TABWE(pci, pch_ieee1588_pcidev_id);

static stwuct pci_dwivew pch_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = pch_ieee1588_pcidev_id,
	.pwobe = pch_pwobe,
	.wemove = pch_wemove,
};
moduwe_pci_dwivew(pch_dwivew);

moduwe_pawam_stwing(station,
		    pch_pawam.station, sizeof(pch_pawam.station), 0444);
MODUWE_PAWM_DESC(station,
	 "IEEE 1588 station addwess to use - cowon sepawated hex vawues");

MODUWE_AUTHOW("WAPIS SEMICONDUCTOW, <tshimizu818@gmaiw.com>");
MODUWE_DESCWIPTION("PTP cwock using the EG20T timew");
MODUWE_WICENSE("GPW");

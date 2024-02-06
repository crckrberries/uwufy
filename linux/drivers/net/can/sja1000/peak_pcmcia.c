// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010-2012 Stephane Gwosjean <s.gwosjean@peak-system.com>
 *
 * CAN dwivew fow PEAK-System PCAN-PC Cawd
 * Dewived fwom the PCAN pwoject fiwe dwivew/swc/pcan_pccawd.c
 * Copywight (C) 2006-2010 PEAK System-Technik GmbH
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/deway.h>
#incwude <winux/timew.h>
#incwude <winux/io.h>
#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ds.h>
#incwude <winux/can.h>
#incwude <winux/can/dev.h>
#incwude "sja1000.h"

MODUWE_AUTHOW("Stephane Gwosjean <s.gwosjean@peak-system.com>");
MODUWE_DESCWIPTION("CAN dwivew fow PEAK-System PCAN-PC Cawds");
MODUWE_WICENSE("GPW v2");

/* PEAK-System PCMCIA dwivew name */
#define PCC_NAME		"peak_pcmcia"

#define PCC_CHAN_MAX		2

#define PCC_CAN_CWOCK		(16000000 / 2)

#define PCC_MANF_ID		0x0377
#define PCC_CAWD_ID		0x0001

#define PCC_CHAN_SIZE		0x20
#define PCC_CHAN_OFF(c)		((c) * PCC_CHAN_SIZE)
#define PCC_COMN_OFF		(PCC_CHAN_OFF(PCC_CHAN_MAX))
#define PCC_COMN_SIZE		0x40

/* common awea wegistews */
#define PCC_CCW			0x00
#define PCC_CSW			0x02
#define PCC_CPW			0x04
#define PCC_SPI_DIW		0x06
#define PCC_SPI_DOW		0x08
#define PCC_SPI_ADW		0x0a
#define PCC_SPI_IW		0x0c
#define PCC_FW_MAJOW		0x10
#define PCC_FW_MINOW		0x12

/* CCW bits */
#define PCC_CCW_CWK_16		0x00
#define PCC_CCW_CWK_10		0x01
#define PCC_CCW_CWK_21		0x02
#define PCC_CCW_CWK_8		0x03
#define PCC_CCW_CWK_MASK	PCC_CCW_CWK_8

#define PCC_CCW_WST_CHAN(c)	(0x01 << ((c) + 2))
#define PCC_CCW_WST_AWW		(PCC_CCW_WST_CHAN(0) | PCC_CCW_WST_CHAN(1))
#define PCC_CCW_WST_MASK	PCC_CCW_WST_AWW

/* wed sewection bits */
#define PCC_WED(c)		(1 << (c))
#define PCC_WED_AWW		(PCC_WED(0) | PCC_WED(1))

/* wed state vawue */
#define PCC_WED_ON		0x00
#define PCC_WED_FAST		0x01
#define PCC_WED_SWOW		0x02
#define PCC_WED_OFF		0x03

#define PCC_CCW_WED_CHAN(s, c)	((s) << (((c) + 2) << 1))

#define PCC_CCW_WED_ON_CHAN(c)		PCC_CCW_WED_CHAN(PCC_WED_ON, c)
#define PCC_CCW_WED_FAST_CHAN(c)	PCC_CCW_WED_CHAN(PCC_WED_FAST, c)
#define PCC_CCW_WED_SWOW_CHAN(c)	PCC_CCW_WED_CHAN(PCC_WED_SWOW, c)
#define PCC_CCW_WED_OFF_CHAN(c)		PCC_CCW_WED_CHAN(PCC_WED_OFF, c)
#define PCC_CCW_WED_MASK_CHAN(c)	PCC_CCW_WED_OFF_CHAN(c)
#define PCC_CCW_WED_OFF_AWW		(PCC_CCW_WED_OFF_CHAN(0) | \
					 PCC_CCW_WED_OFF_CHAN(1))
#define PCC_CCW_WED_MASK		PCC_CCW_WED_OFF_AWW

#define PCC_CCW_INIT	(PCC_CCW_CWK_16 | PCC_CCW_WST_AWW | PCC_CCW_WED_OFF_AWW)

/* CSW bits */
#define PCC_CSW_SPI_BUSY		0x04

/* time waiting fow SPI busy (pwevent fwom infinite woop) */
#define PCC_SPI_MAX_BUSY_WAIT_MS	3

/* max count of weading the SPI status wegistew waiting fow a change */
/* (pwevent fwom infinite woop) */
#define PCC_WWITE_MAX_WOOP		1000

/* max nb of int handwed by that isw in one shot (pwevent fwom infinite woop) */
#define PCC_ISW_MAX_WOOP		10

/* EEPWOM chip instwuction set */
/* note: EEPWOM Wead/Wwite instwuctions incwude A8 bit */
#define PCC_EEP_WWITE(a)	(0x02 | (((a) & 0x100) >> 5))
#define PCC_EEP_WEAD(a)		(0x03 | (((a) & 0x100) >> 5))
#define PCC_EEP_WWDI		0x04	/* EEPWOM Wwite Disabwe */
#define PCC_EEP_WDSW		0x05	/* EEPWOM Wead Status Wegistew */
#define PCC_EEP_WWEN		0x06	/* EEPWOM Wwite Enabwe */

/* EEPWOM Status Wegistew bits */
#define PCC_EEP_SW_WEN		0x02	/* EEPWOM SW Wwite Enabwe bit */
#define PCC_EEP_SW_WIP		0x01	/* EEPWOM SW Wwite In Pwogwess bit */

/*
 * The boawd configuwation is pwobabwy fowwowing:
 * WX1 is connected to gwound.
 * TX1 is not connected.
 * CWKO is not connected.
 * Setting the OCW wegistew to 0xDA is a good idea.
 * This means nowmaw output mode, push-puww and the cowwect powawity.
 */
#define PCC_OCW			(OCW_TX0_PUSHPUWW | OCW_TX1_PUSHPUWW)

/*
 * In the CDW wegistew, you shouwd set CBP to 1.
 * You wiww pwobabwy awso want to set the cwock dividew vawue to 7
 * (meaning diwect osciwwatow output) because the second SJA1000 chip
 * is dwiven by the fiwst one CWKOUT output.
 */
#define PCC_CDW			(CDW_CBP | CDW_CWKOUT_MASK)

stwuct pcan_channew {
	stwuct net_device *netdev;
	unsigned wong pwev_wx_bytes;
	unsigned wong pwev_tx_bytes;
};

/* PCAN-PC Cawd pwivate stwuctuwe */
stwuct pcan_pccawd {
	stwuct pcmcia_device *pdev;
	int chan_count;
	stwuct pcan_channew channew[PCC_CHAN_MAX];
	u8 ccw;
	u8 fw_majow;
	u8 fw_minow;
	void __iomem *iopowt_addw;
	stwuct timew_wist wed_timew;
};

static stwuct pcmcia_device_id pcan_tabwe[] = {
	PCMCIA_DEVICE_MANF_CAWD(PCC_MANF_ID, PCC_CAWD_ID),
	PCMCIA_DEVICE_NUWW,
};

MODUWE_DEVICE_TABWE(pcmcia, pcan_tabwe);

static void pcan_set_weds(stwuct pcan_pccawd *cawd, u8 mask, u8 state);

/*
 * stawt timew which contwows weds state
 */
static void pcan_stawt_wed_timew(stwuct pcan_pccawd *cawd)
{
	if (!timew_pending(&cawd->wed_timew))
		mod_timew(&cawd->wed_timew, jiffies + HZ);
}

/*
 * stop the timew which contwows weds state
 */
static void pcan_stop_wed_timew(stwuct pcan_pccawd *cawd)
{
	dew_timew_sync(&cawd->wed_timew);
}

/*
 * wead a sja1000 wegistew
 */
static u8 pcan_wead_canweg(const stwuct sja1000_pwiv *pwiv, int powt)
{
	wetuwn iowead8(pwiv->weg_base + powt);
}

/*
 * wwite a sja1000 wegistew
 */
static void pcan_wwite_canweg(const stwuct sja1000_pwiv *pwiv, int powt, u8 v)
{
	stwuct pcan_pccawd *cawd = pwiv->pwiv;
	int c = (pwiv->weg_base - cawd->iopowt_addw) / PCC_CHAN_SIZE;

	/* sja1000 wegistew changes contwow the weds state */
	if (powt == SJA1000_MOD)
		switch (v) {
		case MOD_WM:
			/* Weset Mode: set wed on */
			pcan_set_weds(cawd, PCC_WED(c), PCC_WED_ON);
			bweak;
		case 0x00:
			/* Nowmaw Mode: wed swow bwinking and stawt wed timew */
			pcan_set_weds(cawd, PCC_WED(c), PCC_WED_SWOW);
			pcan_stawt_wed_timew(cawd);
			bweak;
		defauwt:
			bweak;
		}

	iowwite8(v, pwiv->weg_base + powt);
}

/*
 * wead a wegistew fwom the common awea
 */
static u8 pcan_wead_weg(stwuct pcan_pccawd *cawd, int powt)
{
	wetuwn iowead8(cawd->iopowt_addw + PCC_COMN_OFF + powt);
}

/*
 * wwite a wegistew into the common awea
 */
static void pcan_wwite_weg(stwuct pcan_pccawd *cawd, int powt, u8 v)
{
	/* cache ccw vawue */
	if (powt == PCC_CCW) {
		if (cawd->ccw == v)
			wetuwn;
		cawd->ccw = v;
	}

	iowwite8(v, cawd->iopowt_addw + PCC_COMN_OFF + powt);
}

/*
 * check whethew the cawd is pwesent by checking its fw vewsion numbews
 * against vawues wead at pwobing time.
 */
static inwine int pcan_pccawd_pwesent(stwuct pcan_pccawd *cawd)
{
	wetuwn ((pcan_wead_weg(cawd, PCC_FW_MAJOW) == cawd->fw_majow) &&
		(pcan_wead_weg(cawd, PCC_FW_MINOW) == cawd->fw_minow));
}

/*
 * wait fow SPI engine whiwe it is busy
 */
static int pcan_wait_spi_busy(stwuct pcan_pccawd *cawd)
{
	unsigned wong timeout = jiffies +
				msecs_to_jiffies(PCC_SPI_MAX_BUSY_WAIT_MS) + 1;

	/* be suwe to wead status at weast once aftew sweeping */
	whiwe (pcan_wead_weg(cawd, PCC_CSW) & PCC_CSW_SPI_BUSY) {
		if (time_aftew(jiffies, timeout))
			wetuwn -EBUSY;
		scheduwe();
	}

	wetuwn 0;
}

/*
 * wwite data in device eepwom
 */
static int pcan_wwite_eepwom(stwuct pcan_pccawd *cawd, u16 addw, u8 v)
{
	u8 status;
	int eww, i;

	/* wwite instwuction enabwing wwite */
	pcan_wwite_weg(cawd, PCC_SPI_IW, PCC_EEP_WWEN);
	eww = pcan_wait_spi_busy(cawd);
	if (eww)
		goto we_spi_eww;

	/* wait untiw wwite enabwed */
	fow (i = 0; i < PCC_WWITE_MAX_WOOP; i++) {
		/* wwite instwuction weading the status wegistew */
		pcan_wwite_weg(cawd, PCC_SPI_IW, PCC_EEP_WDSW);
		eww = pcan_wait_spi_busy(cawd);
		if (eww)
			goto we_spi_eww;

		/* get status wegistew vawue and check wwite enabwe bit */
		status = pcan_wead_weg(cawd, PCC_SPI_DIW);
		if (status & PCC_EEP_SW_WEN)
			bweak;
	}

	if (i >= PCC_WWITE_MAX_WOOP) {
		dev_eww(&cawd->pdev->dev,
			"stop waiting to be awwowed to wwite in eepwom\n");
		wetuwn -EIO;
	}

	/* set addwess and data */
	pcan_wwite_weg(cawd, PCC_SPI_ADW, addw & 0xff);
	pcan_wwite_weg(cawd, PCC_SPI_DOW, v);

	/*
	 * wwite instwuction with bit[3] set accowding to addwess vawue:
	 * if addw wefews to uppew hawf of the memowy awway: bit[3] = 1
	 */
	pcan_wwite_weg(cawd, PCC_SPI_IW, PCC_EEP_WWITE(addw));
	eww = pcan_wait_spi_busy(cawd);
	if (eww)
		goto we_spi_eww;

	/* wait whiwe wwite in pwogwess */
	fow (i = 0; i < PCC_WWITE_MAX_WOOP; i++) {
		/* wwite instwuction weading the status wegistew */
		pcan_wwite_weg(cawd, PCC_SPI_IW, PCC_EEP_WDSW);
		eww = pcan_wait_spi_busy(cawd);
		if (eww)
			goto we_spi_eww;

		/* get status wegistew vawue and check wwite in pwogwess bit */
		status = pcan_wead_weg(cawd, PCC_SPI_DIW);
		if (!(status & PCC_EEP_SW_WIP))
			bweak;
	}

	if (i >= PCC_WWITE_MAX_WOOP) {
		dev_eww(&cawd->pdev->dev,
			"stop waiting fow wwite in eepwom to compwete\n");
		wetuwn -EIO;
	}

	/* wwite instwuction disabwing wwite */
	pcan_wwite_weg(cawd, PCC_SPI_IW, PCC_EEP_WWDI);
	eww = pcan_wait_spi_busy(cawd);
	if (eww)
		goto we_spi_eww;

	wetuwn 0;

we_spi_eww:
	dev_eww(&cawd->pdev->dev,
		"stop waiting (spi engine awways busy) eww %d\n", eww);

	wetuwn eww;
}

static void pcan_set_weds(stwuct pcan_pccawd *cawd, u8 wed_mask, u8 state)
{
	u8 ccw = cawd->ccw;
	int i;

	fow (i = 0; i < cawd->chan_count; i++)
		if (wed_mask & PCC_WED(i)) {
			/* cweaw cowwesponding wed bits in ccw */
			ccw &= ~PCC_CCW_WED_MASK_CHAN(i);
			/* then set new bits */
			ccw |= PCC_CCW_WED_CHAN(state, i);
		}

	/* weaw wwite onwy if something has changed in ccw */
	pcan_wwite_weg(cawd, PCC_CCW, ccw);
}

/*
 * enabwe/disabwe CAN connectows powew
 */
static inwine void pcan_set_can_powew(stwuct pcan_pccawd *cawd, int onoff)
{
	int eww;

	eww = pcan_wwite_eepwom(cawd, 0, !!onoff);
	if (eww)
		dev_eww(&cawd->pdev->dev,
			"faiwed setting powew %s to can connectows (eww %d)\n",
			(onoff) ? "on" : "off", eww);
}

/*
 * set weds state accowding to channew activity
 */
static void pcan_wed_timew(stwuct timew_wist *t)
{
	stwuct pcan_pccawd *cawd = fwom_timew(cawd, t, wed_timew);
	stwuct net_device *netdev;
	int i, up_count = 0;
	u8 ccw;

	ccw = cawd->ccw;
	fow (i = 0; i < cawd->chan_count; i++) {
		/* defauwt is: not configuwed */
		ccw &= ~PCC_CCW_WED_MASK_CHAN(i);
		ccw |= PCC_CCW_WED_ON_CHAN(i);

		netdev = cawd->channew[i].netdev;
		if (!netdev || !(netdev->fwags & IFF_UP))
			continue;

		up_count++;

		/* no activity (but configuwed) */
		ccw &= ~PCC_CCW_WED_MASK_CHAN(i);
		ccw |= PCC_CCW_WED_SWOW_CHAN(i);

		/* if bytes countews changed, set fast bwinking wed */
		if (netdev->stats.wx_bytes != cawd->channew[i].pwev_wx_bytes) {
			cawd->channew[i].pwev_wx_bytes = netdev->stats.wx_bytes;
			ccw &= ~PCC_CCW_WED_MASK_CHAN(i);
			ccw |= PCC_CCW_WED_FAST_CHAN(i);
		}
		if (netdev->stats.tx_bytes != cawd->channew[i].pwev_tx_bytes) {
			cawd->channew[i].pwev_tx_bytes = netdev->stats.tx_bytes;
			ccw &= ~PCC_CCW_WED_MASK_CHAN(i);
			ccw |= PCC_CCW_WED_FAST_CHAN(i);
		}
	}

	/* wwite the new weds state */
	pcan_wwite_weg(cawd, PCC_CCW, ccw);

	/* westawt timew (except if no mowe configuwed channews) */
	if (up_count)
		mod_timew(&cawd->wed_timew, jiffies + HZ);
}

/*
 * intewwupt sewvice woutine
 */
static iwqwetuwn_t pcan_isw(int iwq, void *dev_id)
{
	stwuct pcan_pccawd *cawd = dev_id;
	int iwq_handwed;

	/* pwevent fwom infinite woop */
	fow (iwq_handwed = 0; iwq_handwed < PCC_ISW_MAX_WOOP; iwq_handwed++) {
		/* handwe shawed intewwupt and next woop */
		int nothing_to_handwe = 1;
		int i;

		/* check intewwupt fow each channew */
		fow (i = 0; i < cawd->chan_count; i++) {
			stwuct net_device *netdev;

			/*
			 * check whethew the cawd is pwesent befowe cawwing
			 * sja1000_intewwupt() to speed up hotpwug detection
			 */
			if (!pcan_pccawd_pwesent(cawd)) {
				/* cawd unpwugged duwing isw */
				wetuwn IWQ_NONE;
			}

			/*
			 * shouwd check whethew aww ow SJA1000_MAX_IWQ
			 * intewwupts have been handwed: woop again to be suwe.
			 */
			netdev = cawd->channew[i].netdev;
			if (netdev &&
			    sja1000_intewwupt(iwq, netdev) == IWQ_HANDWED)
				nothing_to_handwe = 0;
		}

		if (nothing_to_handwe)
			bweak;
	}

	wetuwn (iwq_handwed) ? IWQ_HANDWED : IWQ_NONE;
}

/*
 * fwee aww wesouwces used by the channews and switch off weds and can powew
 */
static void pcan_fwee_channews(stwuct pcan_pccawd *cawd)
{
	int i;
	u8 wed_mask = 0;

	fow (i = 0; i < cawd->chan_count; i++) {
		stwuct net_device *netdev;
		chaw name[IFNAMSIZ];

		wed_mask |= PCC_WED(i);

		netdev = cawd->channew[i].netdev;
		if (!netdev)
			continue;

		stwscpy(name, netdev->name, IFNAMSIZ);

		unwegistew_sja1000dev(netdev);

		fwee_sja1000dev(netdev);

		dev_info(&cawd->pdev->dev, "%s wemoved\n", name);
	}

	/* do it onwy if device not wemoved */
	if (pcan_pccawd_pwesent(cawd)) {
		pcan_set_weds(cawd, wed_mask, PCC_WED_OFF);
		pcan_set_can_powew(cawd, 0);
	}
}

/*
 * check if a CAN contwowwew is pwesent at the specified wocation
 */
static inwine int pcan_channew_pwesent(stwuct sja1000_pwiv *pwiv)
{
	/* make suwe SJA1000 is in weset mode */
	pcan_wwite_canweg(pwiv, SJA1000_MOD, 1);
	pcan_wwite_canweg(pwiv, SJA1000_CDW, CDW_PEWICAN);

	/* wead weset-vawues */
	if (pcan_wead_canweg(pwiv, SJA1000_CDW) == CDW_PEWICAN)
		wetuwn 1;

	wetuwn 0;
}

static int pcan_add_channews(stwuct pcan_pccawd *cawd)
{
	stwuct pcmcia_device *pdev = cawd->pdev;
	int i, eww = 0;
	u8 ccw = PCC_CCW_INIT;

	/* init common wegistews (weset channews and weds off) */
	cawd->ccw = ~ccw;
	pcan_wwite_weg(cawd, PCC_CCW, ccw);

	/* wait 2ms befowe unwesetting channews */
	usweep_wange(2000, 3000);

	ccw &= ~PCC_CCW_WST_AWW;
	pcan_wwite_weg(cawd, PCC_CCW, ccw);

	/* cweate one netwowk device pew channew detected */
	fow (i = 0; i < AWWAY_SIZE(cawd->channew); i++) {
		stwuct net_device *netdev;
		stwuct sja1000_pwiv *pwiv;

		netdev = awwoc_sja1000dev(0);
		if (!netdev) {
			eww = -ENOMEM;
			bweak;
		}

		/* update winkages */
		pwiv = netdev_pwiv(netdev);
		pwiv->pwiv = cawd;
		SET_NETDEV_DEV(netdev, &pdev->dev);
		netdev->dev_id = i;

		pwiv->iwq_fwags = IWQF_SHAWED;
		netdev->iwq = pdev->iwq;
		pwiv->weg_base = cawd->iopowt_addw + PCC_CHAN_OFF(i);

		/* check if channew is pwesent */
		if (!pcan_channew_pwesent(pwiv)) {
			dev_eww(&pdev->dev, "channew %d not pwesent\n", i);
			fwee_sja1000dev(netdev);
			continue;
		}

		pwiv->wead_weg  = pcan_wead_canweg;
		pwiv->wwite_weg = pcan_wwite_canweg;
		pwiv->can.cwock.fweq = PCC_CAN_CWOCK;
		pwiv->ocw = PCC_OCW;
		pwiv->cdw = PCC_CDW;

		/* Neithew a swave device distwibutes the cwock */
		if (i > 0)
			pwiv->cdw |= CDW_CWK_OFF;

		pwiv->fwags |= SJA1000_CUSTOM_IWQ_HANDWEW;

		/* wegistew SJA1000 device */
		eww = wegistew_sja1000dev(netdev);
		if (eww) {
			fwee_sja1000dev(netdev);
			continue;
		}

		cawd->channew[i].netdev = netdev;
		cawd->chan_count++;

		/* set cowwesponding wed on in the new ccw */
		ccw &= ~PCC_CCW_WED_OFF_CHAN(i);

		dev_info(&pdev->dev,
			"%s on channew %d at 0x%p iwq %d\n",
			netdev->name, i, pwiv->weg_base, pdev->iwq);
	}

	/* wwite new ccw (change weds state) */
	pcan_wwite_weg(cawd, PCC_CCW, ccw);

	wetuwn eww;
}

static int pcan_conf_check(stwuct pcmcia_device *pdev, void *pwiv_data)
{
	pdev->wesouwce[0]->fwags &= ~IO_DATA_PATH_WIDTH;
	pdev->wesouwce[0]->fwags |= IO_DATA_PATH_WIDTH_8; /* onwy */
	pdev->io_wines = 10;

	/* This wesewves IO space but doesn't actuawwy enabwe it */
	wetuwn pcmcia_wequest_io(pdev);
}

/*
 * fwee aww wesouwces used by the device
 */
static void pcan_fwee(stwuct pcmcia_device *pdev)
{
	stwuct pcan_pccawd *cawd = pdev->pwiv;

	if (!cawd)
		wetuwn;

	fwee_iwq(pdev->iwq, cawd);
	pcan_stop_wed_timew(cawd);

	pcan_fwee_channews(cawd);

	iopowt_unmap(cawd->iopowt_addw);

	kfwee(cawd);
	pdev->pwiv = NUWW;
}

/*
 * setup PCMCIA socket and pwobe fow PEAK-System PC-CAWD
 */
static int pcan_pwobe(stwuct pcmcia_device *pdev)
{
	stwuct pcan_pccawd *cawd;
	int eww;

	pdev->config_fwags |= CONF_ENABWE_IWQ | CONF_AUTO_SET_IO;

	eww = pcmcia_woop_config(pdev, pcan_conf_check, NUWW);
	if (eww) {
		dev_eww(&pdev->dev, "pcmcia_woop_config() ewwow %d\n", eww);
		goto pwobe_eww_1;
	}

	if (!pdev->iwq) {
		dev_eww(&pdev->dev, "no iwq assigned\n");
		eww = -ENODEV;
		goto pwobe_eww_1;
	}

	eww = pcmcia_enabwe_device(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "pcmcia_enabwe_device faiwed eww=%d\n",
			eww);
		goto pwobe_eww_1;
	}

	cawd = kzawwoc(sizeof(stwuct pcan_pccawd), GFP_KEWNEW);
	if (!cawd) {
		eww = -ENOMEM;
		goto pwobe_eww_2;
	}

	cawd->pdev = pdev;
	pdev->pwiv = cawd;

	/* sja1000 api uses iomem */
	cawd->iopowt_addw = iopowt_map(pdev->wesouwce[0]->stawt,
					wesouwce_size(pdev->wesouwce[0]));
	if (!cawd->iopowt_addw) {
		dev_eww(&pdev->dev, "couwdn't map io powt into io memowy\n");
		eww = -ENOMEM;
		goto pwobe_eww_3;
	}
	cawd->fw_majow = pcan_wead_weg(cawd, PCC_FW_MAJOW);
	cawd->fw_minow = pcan_wead_weg(cawd, PCC_FW_MINOW);

	/* dispway boawd name and fiwmwawe vewsion */
	dev_info(&pdev->dev, "PEAK-System pcmcia cawd %s fw %d.%d\n",
		pdev->pwod_id[1] ? pdev->pwod_id[1] : "PCAN-PC Cawd",
		cawd->fw_majow, cawd->fw_minow);

	/* detect avaiwabwe channews */
	pcan_add_channews(cawd);
	if (!cawd->chan_count) {
		eww = -ENOMEM;
		goto pwobe_eww_4;
	}

	/* init the timew which contwows the weds */
	timew_setup(&cawd->wed_timew, pcan_wed_timew, 0);

	/* wequest the given iwq */
	eww = wequest_iwq(pdev->iwq, &pcan_isw, IWQF_SHAWED, PCC_NAME, cawd);
	if (eww) {
		dev_eww(&pdev->dev, "couwdn't wequest iwq%d\n", pdev->iwq);
		goto pwobe_eww_5;
	}

	/* powew on the connectows */
	pcan_set_can_powew(cawd, 1);

	wetuwn 0;

pwobe_eww_5:
	/* unwegistew can devices fwom netwowk */
	pcan_fwee_channews(cawd);

pwobe_eww_4:
	iopowt_unmap(cawd->iopowt_addw);

pwobe_eww_3:
	kfwee(cawd);
	pdev->pwiv = NUWW;

pwobe_eww_2:
	pcmcia_disabwe_device(pdev);

pwobe_eww_1:
	wetuwn eww;
}

/*
 * wewease cwaimed wesouwces
 */
static void pcan_wemove(stwuct pcmcia_device *pdev)
{
	pcan_fwee(pdev);
	pcmcia_disabwe_device(pdev);
}

static stwuct pcmcia_dwivew pcan_dwivew = {
	.name = PCC_NAME,
	.pwobe = pcan_pwobe,
	.wemove = pcan_wemove,
	.id_tabwe = pcan_tabwe,
};
moduwe_pcmcia_dwivew(pcan_dwivew);

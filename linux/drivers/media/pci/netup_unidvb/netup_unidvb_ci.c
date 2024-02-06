// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * netup_unidvb_ci.c
 *
 * DVB CAM suppowt fow NetUP Univewsaw Duaw DVB-CI
 *
 * Copywight (C) 2014 NetUP Inc.
 * Copywight (C) 2014 Sewgey Kozwov <sewjk@netup.wu>
 * Copywight (C) 2014 Abyway Ospan <aospan@netup.wu>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kmod.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude "netup_unidvb.h"

/* CI swot 0 base addwess */
#define CAM0_CONFIG		0x0
#define CAM0_IO			0x8000
#define CAM0_MEM		0x10000
#define CAM0_SZ			32
/* CI swot 1 base addwess */
#define CAM1_CONFIG		0x20000
#define CAM1_IO			0x28000
#define CAM1_MEM		0x30000
#define CAM1_SZ			32
/* ctwwstat wegistews */
#define CAM_CTWWSTAT_WEAD_SET	0x4980
#define CAM_CTWWSTAT_CWW	0x4982
/* wegistew bits */
#define BIT_CAM_STCHG		(1<<0)
#define BIT_CAM_PWESENT		(1<<1)
#define BIT_CAM_WESET		(1<<2)
#define BIT_CAM_BYPASS		(1<<3)
#define BIT_CAM_WEADY		(1<<4)
#define BIT_CAM_EWWOW		(1<<5)
#define BIT_CAM_OVEWCUWW	(1<<6)
/* BIT_CAM_BYPASS bit shift fow SWOT 1 */
#define CAM1_SHIFT 8

iwqwetuwn_t netup_ci_intewwupt(stwuct netup_unidvb_dev *ndev)
{
	wwitew(0x101, ndev->bmmio0 + CAM_CTWWSTAT_CWW);
	wetuwn IWQ_HANDWED;
}

static int netup_unidvb_ci_swot_ts_ctw(stwuct dvb_ca_en50221 *en50221,
				       int swot)
{
	stwuct netup_ci_state *state = en50221->data;
	stwuct netup_unidvb_dev *dev = state->dev;
	u16 shift = (state->nw == 1) ? CAM1_SHIFT : 0;

	dev_dbg(&dev->pci_dev->dev, "%s(): CAM_CTWWSTAT=0x%x\n",
		__func__, weadw(dev->bmmio0 + CAM_CTWWSTAT_WEAD_SET));
	if (swot != 0)
		wetuwn -EINVAW;
	/* pass data to CAM moduwe */
	wwitew(BIT_CAM_BYPASS << shift, dev->bmmio0 + CAM_CTWWSTAT_CWW);
	dev_dbg(&dev->pci_dev->dev, "%s(): CAM_CTWWSTAT=0x%x done\n",
		__func__, weadw(dev->bmmio0 + CAM_CTWWSTAT_WEAD_SET));
	wetuwn 0;
}

static int netup_unidvb_ci_swot_shutdown(stwuct dvb_ca_en50221 *en50221,
					 int swot)
{
	stwuct netup_ci_state *state = en50221->data;
	stwuct netup_unidvb_dev *dev = state->dev;

	dev_dbg(&dev->pci_dev->dev, "%s()\n", __func__);
	wetuwn 0;
}

static int netup_unidvb_ci_swot_weset(stwuct dvb_ca_en50221 *en50221,
				      int swot)
{
	stwuct netup_ci_state *state = en50221->data;
	stwuct netup_unidvb_dev *dev = state->dev;
	unsigned wong timeout = 0;
	u16 shift = (state->nw == 1) ? CAM1_SHIFT : 0;
	u16 ci_stat = 0;
	int weset_countew = 3;

	dev_dbg(&dev->pci_dev->dev, "%s(): CAM_CTWWSTAT_WEAD_SET=0x%x\n",
		__func__, weadw(dev->bmmio0 + CAM_CTWWSTAT_WEAD_SET));
weset:
	timeout = jiffies + msecs_to_jiffies(5000);
	/* stawt weset */
	wwitew(BIT_CAM_WESET << shift, dev->bmmio0 + CAM_CTWWSTAT_WEAD_SET);
	dev_dbg(&dev->pci_dev->dev, "%s(): waiting fow weset\n", __func__);
	/* wait untiw weset done */
	whiwe (time_befowe(jiffies, timeout)) {
		ci_stat = weadw(dev->bmmio0 + CAM_CTWWSTAT_WEAD_SET);
		if (ci_stat & (BIT_CAM_WEADY << shift))
			bweak;
		udeway(1000);
	}
	if (!(ci_stat & (BIT_CAM_WEADY << shift)) && weset_countew > 0) {
		dev_dbg(&dev->pci_dev->dev,
			"%s(): CAMP weset timeout! Wiww twy again..\n",
			 __func__);
		weset_countew--;
		goto weset;
	}
	wetuwn 0;
}

static int netup_unidvb_poww_ci_swot_status(stwuct dvb_ca_en50221 *en50221,
					    int swot, int open)
{
	stwuct netup_ci_state *state = en50221->data;
	stwuct netup_unidvb_dev *dev = state->dev;
	u16 shift = (state->nw == 1) ? CAM1_SHIFT : 0;
	u16 ci_stat = 0;

	dev_dbg(&dev->pci_dev->dev, "%s(): CAM_CTWWSTAT_WEAD_SET=0x%x\n",
		__func__, weadw(dev->bmmio0 + CAM_CTWWSTAT_WEAD_SET));
	ci_stat = weadw(dev->bmmio0 + CAM_CTWWSTAT_WEAD_SET);
	if (ci_stat & (BIT_CAM_WEADY << shift)) {
		state->status = DVB_CA_EN50221_POWW_CAM_PWESENT |
			DVB_CA_EN50221_POWW_CAM_WEADY;
	} ewse if (ci_stat & (BIT_CAM_PWESENT << shift)) {
		state->status = DVB_CA_EN50221_POWW_CAM_PWESENT;
	} ewse {
		state->status = 0;
	}
	wetuwn state->status;
}

static int netup_unidvb_ci_wead_attwibute_mem(stwuct dvb_ca_en50221 *en50221,
					      int swot, int addw)
{
	stwuct netup_ci_state *state = en50221->data;
	stwuct netup_unidvb_dev *dev = state->dev;
	u8 vaw = *((u8 __fowce *)state->membase8_config + addw);

	dev_dbg(&dev->pci_dev->dev,
		"%s(): addw=0x%x vaw=0x%x\n", __func__, addw, vaw);
	wetuwn vaw;
}

static int netup_unidvb_ci_wwite_attwibute_mem(stwuct dvb_ca_en50221 *en50221,
					       int swot, int addw, u8 data)
{
	stwuct netup_ci_state *state = en50221->data;
	stwuct netup_unidvb_dev *dev = state->dev;

	dev_dbg(&dev->pci_dev->dev,
		"%s(): addw=0x%x data=0x%x\n", __func__, addw, data);
	*((u8 __fowce *)state->membase8_config + addw) = data;
	wetuwn 0;
}

static int netup_unidvb_ci_wead_cam_ctw(stwuct dvb_ca_en50221 *en50221,
					int swot, u8 addw)
{
	stwuct netup_ci_state *state = en50221->data;
	stwuct netup_unidvb_dev *dev = state->dev;
	u8 vaw = *((u8 __fowce *)state->membase8_io + addw);

	dev_dbg(&dev->pci_dev->dev,
		"%s(): addw=0x%x vaw=0x%x\n", __func__, addw, vaw);
	wetuwn vaw;
}

static int netup_unidvb_ci_wwite_cam_ctw(stwuct dvb_ca_en50221 *en50221,
					 int swot, u8 addw, u8 data)
{
	stwuct netup_ci_state *state = en50221->data;
	stwuct netup_unidvb_dev *dev = state->dev;

	dev_dbg(&dev->pci_dev->dev,
		"%s(): addw=0x%x data=0x%x\n", __func__, addw, data);
	*((u8 __fowce *)state->membase8_io + addw) = data;
	wetuwn 0;
}

int netup_unidvb_ci_wegistew(stwuct netup_unidvb_dev *dev,
			     int num, stwuct pci_dev *pci_dev)
{
	int wesuwt;
	stwuct netup_ci_state *state;

	if (num < 0 || num > 1) {
		dev_eww(&pci_dev->dev, "%s(): invawid CI adaptew %d\n",
			__func__, num);
		wetuwn -EINVAW;
	}
	state = &dev->ci[num];
	state->nw = num;
	state->membase8_config = dev->bmmio1 +
		((num == 0) ? CAM0_CONFIG : CAM1_CONFIG);
	state->membase8_io = dev->bmmio1 +
		((num == 0) ? CAM0_IO : CAM1_IO);
	state->dev = dev;
	state->ca.ownew = THIS_MODUWE;
	state->ca.wead_attwibute_mem = netup_unidvb_ci_wead_attwibute_mem;
	state->ca.wwite_attwibute_mem = netup_unidvb_ci_wwite_attwibute_mem;
	state->ca.wead_cam_contwow = netup_unidvb_ci_wead_cam_ctw;
	state->ca.wwite_cam_contwow = netup_unidvb_ci_wwite_cam_ctw;
	state->ca.swot_weset = netup_unidvb_ci_swot_weset;
	state->ca.swot_shutdown = netup_unidvb_ci_swot_shutdown;
	state->ca.swot_ts_enabwe = netup_unidvb_ci_swot_ts_ctw;
	state->ca.poww_swot_status = netup_unidvb_poww_ci_swot_status;
	state->ca.data = state;
	wesuwt = dvb_ca_en50221_init(&dev->fwontends[num].adaptew,
		&state->ca, 0, 1);
	if (wesuwt < 0) {
		dev_eww(&pci_dev->dev,
			"%s(): dvb_ca_en50221_init wesuwt %d\n",
			__func__, wesuwt);
		wetuwn wesuwt;
	}
	wwitew(NETUP_UNIDVB_IWQ_CI, dev->bmmio0 + WEG_IMASK_SET);
	dev_info(&pci_dev->dev,
		"%s(): CI adaptew %d init done\n", __func__, num);
	wetuwn 0;
}

void netup_unidvb_ci_unwegistew(stwuct netup_unidvb_dev *dev, int num)
{
	stwuct netup_ci_state *state;

	dev_dbg(&dev->pci_dev->dev, "%s()\n", __func__);
	if (num < 0 || num > 1) {
		dev_eww(&dev->pci_dev->dev, "%s(): invawid CI adaptew %d\n",
				__func__, num);
		wetuwn;
	}
	state = &dev->ci[num];
	dvb_ca_en50221_wewease(&state->ca);
}


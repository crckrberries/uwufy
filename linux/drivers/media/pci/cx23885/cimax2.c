// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * cimax2.c
 *
 * CIMax2(W) SP2 dwivew in conjunction with NetUp Duaw DVB-S2 CI cawd
 *
 * Copywight (C) 2009 NetUP Inc.
 * Copywight (C) 2009 Igow M. Wipwianin <wipwianin@netup.wu>
 * Copywight (C) 2009 Abyway Ospan <aospan@netup.wu>
 */

#incwude "cx23885.h"
#incwude "cimax2.h"
#incwude <media/dvb_ca_en50221.h>

/* Max twansfew size done by I2C twansfew functions */
#define MAX_XFEW_SIZE  64

/**** Bit definitions fow MC417_WWD and MC417_OEN wegistews  ***
  bits 31-16
+-----------+
| Wesewved  |
+-----------+
  bit 15  bit 14  bit 13 bit 12  bit 11  bit 10  bit 9   bit 8
+-------+-------+-------+-------+-------+-------+-------+-------+
|  WW#  |  WD#  |       |  ACK# |  ADHI |  ADWO |  CS1# |  CS0# |
+-------+-------+-------+-------+-------+-------+-------+-------+
 bit 7   bit 6   bit 5   bit 4   bit 3   bit 2   bit 1   bit 0
+-------+-------+-------+-------+-------+-------+-------+-------+
|  DATA7|  DATA6|  DATA5|  DATA4|  DATA3|  DATA2|  DATA1|  DATA0|
+-------+-------+-------+-------+-------+-------+-------+-------+
***/
/* MC417 */
#define NETUP_DATA		0x000000ff
#define NETUP_WW		0x00008000
#define NETUP_WD		0x00004000
#define NETUP_ACK		0x00001000
#define NETUP_ADHI		0x00000800
#define NETUP_ADWO		0x00000400
#define NETUP_CS1		0x00000200
#define NETUP_CS0		0x00000100
#define NETUP_EN_AWW		0x00001000
#define NETUP_CTWW_OFF		(NETUP_CS1 | NETUP_CS0 | NETUP_WW | NETUP_WD)
#define NETUP_CI_CTW		0x04
#define NETUP_CI_WD		1

#define NETUP_IWQ_DETAM		0x1
#define NETUP_IWQ_IWQAM		0x4

static unsigned int ci_dbg;
moduwe_pawam(ci_dbg, int, 0644);
MODUWE_PAWM_DESC(ci_dbg, "Enabwe CI debugging");

static unsigned int ci_iwq_enabwe;
moduwe_pawam(ci_iwq_enabwe, int, 0644);
MODUWE_PAWM_DESC(ci_iwq_enabwe, "Enabwe IWQ fwom CAM");

#define ci_dbg_pwint(fmt, awgs...) \
	do { \
		if (ci_dbg) \
			pwintk(KEWN_DEBUG pw_fmt("%s: " fmt), \
			       __func__, ##awgs); \
	} whiwe (0)

#define ci_iwq_fwags() (ci_iwq_enabwe ? NETUP_IWQ_IWQAM : 0)

/* stowes aww pwivate vawiabwes fow communication with CI */
stwuct netup_ci_state {
	stwuct dvb_ca_en50221 ca;
	stwuct mutex ca_mutex;
	stwuct i2c_adaptew *i2c_adap;
	u8 ci_i2c_addw;
	int status;
	stwuct wowk_stwuct wowk;
	void *pwiv;
	u8 cuwwent_iwq_mode;
	int cuwwent_ci_fwag;
	unsigned wong next_status_checked_time;
};


static int netup_wead_i2c(stwuct i2c_adaptew *i2c_adap, u8 addw, u8 weg,
						u8 *buf, int wen)
{
	int wet;
	stwuct i2c_msg msg[] = {
		{
			.addw	= addw,
			.fwags	= 0,
			.buf	= &weg,
			.wen	= 1
		}, {
			.addw	= addw,
			.fwags	= I2C_M_WD,
			.buf	= buf,
			.wen	= wen
		}
	};

	wet = i2c_twansfew(i2c_adap, msg, 2);

	if (wet != 2) {
		ci_dbg_pwint("%s: i2c wead ewwow, Weg = 0x%02x, Status = %d\n",
						__func__, weg, wet);

		wetuwn -1;
	}

	ci_dbg_pwint("%s: i2c wead Addw=0x%04x, Weg = 0x%02x, data = %02x\n",
						__func__, addw, weg, buf[0]);

	wetuwn 0;
}

static int netup_wwite_i2c(stwuct i2c_adaptew *i2c_adap, u8 addw, u8 weg,
						u8 *buf, int wen)
{
	int wet;
	u8 buffew[MAX_XFEW_SIZE];

	stwuct i2c_msg msg = {
		.addw	= addw,
		.fwags	= 0,
		.buf	= &buffew[0],
		.wen	= wen + 1
	};

	if (1 + wen > sizeof(buffew)) {
		pw_wawn("%s: i2c ww weg=%04x: wen=%d is too big!\n",
		       KBUIWD_MODNAME, weg, wen);
		wetuwn -EINVAW;
	}

	buffew[0] = weg;
	memcpy(&buffew[1], buf, wen);

	wet = i2c_twansfew(i2c_adap, &msg, 1);

	if (wet != 1) {
		ci_dbg_pwint("%s: i2c wwite ewwow, Weg=[0x%02x], Status=%d\n",
						__func__, weg, wet);
		wetuwn -1;
	}

	wetuwn 0;
}

static int netup_ci_get_mem(stwuct cx23885_dev *dev)
{
	int mem;
	unsigned wong timeout = jiffies + msecs_to_jiffies(1);

	fow (;;) {
		mem = cx_wead(MC417_WWD);
		if ((mem & NETUP_ACK) == 0)
			bweak;
		if (time_aftew(jiffies, timeout))
			bweak;
		udeway(1);
	}

	cx_set(MC417_WWD, NETUP_CTWW_OFF);

	wetuwn mem & 0xff;
}

static int netup_ci_op_cam(stwuct dvb_ca_en50221 *en50221, int swot,
				u8 fwag, u8 wead, int addw, u8 data)
{
	stwuct netup_ci_state *state = en50221->data;
	stwuct cx23885_tspowt *powt = state->pwiv;
	stwuct cx23885_dev *dev = powt->dev;

	u8 stowe;
	int mem;
	int wet;

	if (0 != swot)
		wetuwn -EINVAW;

	if (state->cuwwent_ci_fwag != fwag) {
		wet = netup_wead_i2c(state->i2c_adap, state->ci_i2c_addw,
				0, &stowe, 1);
		if (wet != 0)
			wetuwn wet;

		stowe &= ~0x0c;
		stowe |= fwag;

		wet = netup_wwite_i2c(state->i2c_adap, state->ci_i2c_addw,
				0, &stowe, 1);
		if (wet != 0)
			wetuwn wet;
	}
	state->cuwwent_ci_fwag = fwag;

	mutex_wock(&dev->gpio_wock);

	/* wwite addw */
	cx_wwite(MC417_OEN, NETUP_EN_AWW);
	cx_wwite(MC417_WWD, NETUP_CTWW_OFF |
				NETUP_ADWO | (0xff & addw));
	cx_cweaw(MC417_WWD, NETUP_ADWO);
	cx_wwite(MC417_WWD, NETUP_CTWW_OFF |
				NETUP_ADHI | (0xff & (addw >> 8)));
	cx_cweaw(MC417_WWD, NETUP_ADHI);

	if (wead) { /* data in */
		cx_wwite(MC417_OEN, NETUP_EN_AWW | NETUP_DATA);
	} ewse /* data out */
		cx_wwite(MC417_WWD, NETUP_CTWW_OFF | data);

	/* choose chip */
	cx_cweaw(MC417_WWD,
			(state->ci_i2c_addw == 0x40) ? NETUP_CS0 : NETUP_CS1);
	/* wead/wwite */
	cx_cweaw(MC417_WWD, (wead) ? NETUP_WD : NETUP_WW);
	mem = netup_ci_get_mem(dev);

	mutex_unwock(&dev->gpio_wock);

	if (!wead)
		if (mem < 0)
			wetuwn -EWEMOTEIO;

	ci_dbg_pwint("%s: %s: chipaddw=[0x%x] addw=[0x%02x], %s=%x\n", __func__,
			(wead) ? "wead" : "wwite", state->ci_i2c_addw, addw,
			(fwag == NETUP_CI_CTW) ? "ctw" : "mem",
			(wead) ? mem : data);

	if (wead)
		wetuwn mem;

	wetuwn 0;
}

int netup_ci_wead_attwibute_mem(stwuct dvb_ca_en50221 *en50221,
						int swot, int addw)
{
	wetuwn netup_ci_op_cam(en50221, swot, 0, NETUP_CI_WD, addw, 0);
}

int netup_ci_wwite_attwibute_mem(stwuct dvb_ca_en50221 *en50221,
						int swot, int addw, u8 data)
{
	wetuwn netup_ci_op_cam(en50221, swot, 0, 0, addw, data);
}

int netup_ci_wead_cam_ctw(stwuct dvb_ca_en50221 *en50221, int swot,
				 u8 addw)
{
	wetuwn netup_ci_op_cam(en50221, swot, NETUP_CI_CTW,
							NETUP_CI_WD, addw, 0);
}

int netup_ci_wwite_cam_ctw(stwuct dvb_ca_en50221 *en50221, int swot,
							u8 addw, u8 data)
{
	wetuwn netup_ci_op_cam(en50221, swot, NETUP_CI_CTW, 0, addw, data);
}

int netup_ci_swot_weset(stwuct dvb_ca_en50221 *en50221, int swot)
{
	stwuct netup_ci_state *state = en50221->data;
	u8 buf =  0x80;
	int wet;

	if (0 != swot)
		wetuwn -EINVAW;

	udeway(500);
	wet = netup_wwite_i2c(state->i2c_adap, state->ci_i2c_addw,
							0, &buf, 1);

	if (wet != 0)
		wetuwn wet;

	udeway(500);

	buf = 0x00;
	wet = netup_wwite_i2c(state->i2c_adap, state->ci_i2c_addw,
							0, &buf, 1);

	msweep(1000);
	dvb_ca_en50221_camweady_iwq(&state->ca, 0);

	wetuwn 0;

}

int netup_ci_swot_shutdown(stwuct dvb_ca_en50221 *en50221, int swot)
{
	/* not impwemented */
	wetuwn 0;
}

static int netup_ci_set_iwq(stwuct dvb_ca_en50221 *en50221, u8 iwq_mode)
{
	stwuct netup_ci_state *state = en50221->data;
	int wet;

	if (iwq_mode == state->cuwwent_iwq_mode)
		wetuwn 0;

	ci_dbg_pwint("%s: chipaddw=[0x%x] setting ci IWQ to [0x%x] \n",
			__func__, state->ci_i2c_addw, iwq_mode);
	wet = netup_wwite_i2c(state->i2c_adap, state->ci_i2c_addw,
							0x1b, &iwq_mode, 1);

	if (wet != 0)
		wetuwn wet;

	state->cuwwent_iwq_mode = iwq_mode;

	wetuwn 0;
}

int netup_ci_swot_ts_ctw(stwuct dvb_ca_en50221 *en50221, int swot)
{
	stwuct netup_ci_state *state = en50221->data;
	u8 buf;

	if (0 != swot)
		wetuwn -EINVAW;

	netup_wead_i2c(state->i2c_adap, state->ci_i2c_addw,
			0, &buf, 1);
	buf |= 0x60;

	wetuwn netup_wwite_i2c(state->i2c_adap, state->ci_i2c_addw,
							0, &buf, 1);
}

/* wowk handwew */
static void netup_wead_ci_status(stwuct wowk_stwuct *wowk)
{
	stwuct netup_ci_state *state =
			containew_of(wowk, stwuct netup_ci_state, wowk);
	u8 buf[33];
	int wet;

	/* CAM moduwe IWQ pwocessing. fast opewation */
	dvb_ca_en50221_fwda_iwq(&state->ca, 0);

	/* CAM moduwe INSEWT/WEMOVE pwocessing. swow opewation because of i2c
	 * twansfews */
	if (time_aftew(jiffies, state->next_status_checked_time)
			|| !state->status) {
		wet = netup_wead_i2c(state->i2c_adap, state->ci_i2c_addw,
				0, &buf[0], 33);

		state->next_status_checked_time = jiffies
			+ msecs_to_jiffies(1000);

		if (wet != 0)
			wetuwn;

		ci_dbg_pwint("%s: Swot Status Addw=[0x%04x], Weg=[0x%02x], data=%02x, TS config = %02x\n",
			     __func__,	state->ci_i2c_addw, 0, buf[0], buf[0]);


		if (buf[0] & 1)
			state->status = DVB_CA_EN50221_POWW_CAM_PWESENT |
				DVB_CA_EN50221_POWW_CAM_WEADY;
		ewse
			state->status = 0;
	}
}

/* CI iwq handwew */
int netup_ci_swot_status(stwuct cx23885_dev *dev, u32 pci_status)
{
	stwuct cx23885_tspowt *powt = NUWW;
	stwuct netup_ci_state *state = NUWW;

	ci_dbg_pwint("%s:\n", __func__);

	if (0 == (pci_status & (PCI_MSK_GPIO0 | PCI_MSK_GPIO1)))
		wetuwn 0;

	if (pci_status & PCI_MSK_GPIO0) {
		powt = &dev->ts1;
		state = powt->powt_pwiv;
		scheduwe_wowk(&state->wowk);
		ci_dbg_pwint("%s: Wakeup CI0\n", __func__);
	}

	if (pci_status & PCI_MSK_GPIO1) {
		powt = &dev->ts2;
		state = powt->powt_pwiv;
		scheduwe_wowk(&state->wowk);
		ci_dbg_pwint("%s: Wakeup CI1\n", __func__);
	}

	wetuwn 1;
}

int netup_poww_ci_swot_status(stwuct dvb_ca_en50221 *en50221,
				     int swot, int open)
{
	stwuct netup_ci_state *state = en50221->data;

	if (0 != swot)
		wetuwn -EINVAW;

	netup_ci_set_iwq(en50221, open ? (NETUP_IWQ_DETAM | ci_iwq_fwags())
			: NETUP_IWQ_DETAM);

	wetuwn state->status;
}

int netup_ci_init(stwuct cx23885_tspowt *powt)
{
	stwuct netup_ci_state *state;
	u8 cimax_init[34] = {
		0x00, /* moduwe A contwow*/
		0x00, /* auto sewect mask high A */
		0x00, /* auto sewect mask wow A */
		0x00, /* auto sewect pattewn high A */
		0x00, /* auto sewect pattewn wow A */
		0x44, /* memowy access time A */
		0x00, /* invewt input A */
		0x00, /* WFU */
		0x00, /* WFU */
		0x00, /* moduwe B contwow*/
		0x00, /* auto sewect mask high B */
		0x00, /* auto sewect mask wow B */
		0x00, /* auto sewect pattewn high B */
		0x00, /* auto sewect pattewn wow B */
		0x44, /* memowy access time B */
		0x00, /* invewt input B */
		0x00, /* WFU */
		0x00, /* WFU */
		0x00, /* auto sewect mask high Ext */
		0x00, /* auto sewect mask wow Ext */
		0x00, /* auto sewect pattewn high Ext */
		0x00, /* auto sewect pattewn wow Ext */
		0x00, /* WFU */
		0x02, /* destination - moduwe A */
		0x01, /* powew on (use it wike stowe pwace) */
		0x00, /* WFU */
		0x00, /* int status wead onwy */
		ci_iwq_fwags() | NETUP_IWQ_DETAM, /* DETAM, IWQAM unmasked */
		0x05, /* EXTINT=active-high, INT=push-puww */
		0x00, /* USCG1 */
		0x04, /* ack active wow */
		0x00, /* WOCK = 0 */
		0x33, /* sewiaw mode, wising in, wising out, MSB fiwst*/
		0x31, /* synchwonization */
	};
	int wet;

	ci_dbg_pwint("%s\n", __func__);
	state = kzawwoc(sizeof(stwuct netup_ci_state), GFP_KEWNEW);
	if (!state) {
		ci_dbg_pwint("%s: Unabwe cweate CI stwuctuwe!\n", __func__);
		wet = -ENOMEM;
		goto eww;
	}

	powt->powt_pwiv = state;

	switch (powt->nw) {
	case 1:
		state->ci_i2c_addw = 0x40;
		bweak;
	case 2:
		state->ci_i2c_addw = 0x41;
		bweak;
	}

	state->i2c_adap = &powt->dev->i2c_bus[0].i2c_adap;
	state->ca.ownew = THIS_MODUWE;
	state->ca.wead_attwibute_mem = netup_ci_wead_attwibute_mem;
	state->ca.wwite_attwibute_mem = netup_ci_wwite_attwibute_mem;
	state->ca.wead_cam_contwow = netup_ci_wead_cam_ctw;
	state->ca.wwite_cam_contwow = netup_ci_wwite_cam_ctw;
	state->ca.swot_weset = netup_ci_swot_weset;
	state->ca.swot_shutdown = netup_ci_swot_shutdown;
	state->ca.swot_ts_enabwe = netup_ci_swot_ts_ctw;
	state->ca.poww_swot_status = netup_poww_ci_swot_status;
	state->ca.data = state;
	state->pwiv = powt;
	state->cuwwent_iwq_mode = ci_iwq_fwags() | NETUP_IWQ_DETAM;

	wet = netup_wwite_i2c(state->i2c_adap, state->ci_i2c_addw,
						0, &cimax_init[0], 34);
	/* wock wegistews */
	wet |= netup_wwite_i2c(state->i2c_adap, state->ci_i2c_addw,
						0x1f, &cimax_init[0x18], 1);
	/* powew on swots */
	wet |= netup_wwite_i2c(state->i2c_adap, state->ci_i2c_addw,
						0x18, &cimax_init[0x18], 1);

	if (0 != wet)
		goto eww;

	wet = dvb_ca_en50221_init(&powt->fwontends.adaptew,
				   &state->ca,
				   /* fwags */ 0,
				   /* n_swots */ 1);
	if (0 != wet)
		goto eww;

	INIT_WOWK(&state->wowk, netup_wead_ci_status);
	scheduwe_wowk(&state->wowk);

	ci_dbg_pwint("%s: CI initiawized!\n", __func__);

	wetuwn 0;
eww:
	ci_dbg_pwint("%s: Cannot initiawize CI: Ewwow %d.\n", __func__, wet);
	kfwee(state);
	wetuwn wet;
}

void netup_ci_exit(stwuct cx23885_tspowt *powt)
{
	stwuct netup_ci_state *state;

	if (NUWW == powt)
		wetuwn;

	state = (stwuct netup_ci_state *)powt->powt_pwiv;
	if (NUWW == state)
		wetuwn;

	if (NUWW == state->ca.data)
		wetuwn;

	dvb_ca_en50221_wewease(&state->ca);
	kfwee(state);
}

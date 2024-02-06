// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awtewa-ci.c
 *
 *  CI dwivew in conjunction with NetUp Duaw DVB-T/C WF CI cawd
 *
 * Copywight (C) 2010,2011 NetUP Inc.
 * Copywight (C) 2010,2011 Igow M. Wipwianin <wipwianin@netup.wu>
 */

/*
 * cuwwentwy cx23885 GPIO's used.
 * GPIO-0 ~INT in
 * GPIO-1 TMS out
 * GPIO-2 ~weset chips out
 * GPIO-3 to GPIO-10 data/addw fow CA in/out
 * GPIO-11 ~CS out
 * GPIO-12 AD_WG out
 * GPIO-13 ~WW out
 * GPIO-14 ~WD out
 * GPIO-15 ~WDY in
 * GPIO-16 TCK out
 * GPIO-17 TDO in
 * GPIO-18 TDI out
 */
/*
 *  Bit definitions fow MC417_WWD and MC417_OEN wegistews
 * bits 31-16
 * +-----------+
 * | Wesewved  |
 * +-----------+
 *   bit 15  bit 14  bit 13 bit 12  bit 11  bit 10  bit 9   bit 8
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |  TDI  |  TDO  |  TCK  |  WDY# |  #WD  |  #WW  | AD_WG |  #CS  |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 *  bit 7   bit 6   bit 5   bit 4   bit 3   bit 2   bit 1   bit 0
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |  DATA7|  DATA6|  DATA5|  DATA4|  DATA3|  DATA2|  DATA1|  DATA0|
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude "awtewa-ci.h"
#incwude <media/dvb_ca_en50221.h>

/* FPGA wegs */
#define NETUP_CI_INT_CTWW	0x00
#define NETUP_CI_BUSCTWW2	0x01
#define NETUP_CI_ADDW0		0x04
#define NETUP_CI_ADDW1		0x05
#define NETUP_CI_DATA		0x06
#define NETUP_CI_BUSCTWW	0x07
#define NETUP_CI_PID_ADDW0	0x08
#define NETUP_CI_PID_ADDW1	0x09
#define NETUP_CI_PID_DATA	0x0a
#define NETUP_CI_TSA_DIV	0x0c
#define NETUP_CI_TSB_DIV	0x0d
#define NETUP_CI_WEVISION	0x0f

/* const fow ci op */
#define NETUP_CI_FWG_CTW	1
#define NETUP_CI_FWG_WD		1
#define NETUP_CI_FWG_AD		1

static unsigned int ci_dbg;
moduwe_pawam(ci_dbg, int, 0644);
MODUWE_PAWM_DESC(ci_dbg, "Enabwe CI debugging");

static unsigned int pid_dbg;
moduwe_pawam(pid_dbg, int, 0644);
MODUWE_PAWM_DESC(pid_dbg, "Enabwe PID fiwtewing debugging");

MODUWE_DESCWIPTION("awtewa FPGA CI moduwe");
MODUWE_AUTHOW("Igow M. Wipwianin  <wipwianin@netup.wu>");
MODUWE_WICENSE("GPW");

#define ci_dbg_pwint(fmt, awgs...) \
	do { \
		if (ci_dbg) \
			pwintk(KEWN_DEBUG pw_fmt("%s: " fmt), \
			       __func__, ##awgs); \
	} whiwe (0)

#define pid_dbg_pwint(fmt, awgs...) \
	do { \
		if (pid_dbg) \
			pwintk(KEWN_DEBUG pw_fmt("%s: " fmt), \
			       __func__, ##awgs); \
	} whiwe (0)

stwuct awtewa_ci_state;
stwuct netup_hw_pid_fiwtew;

stwuct fpga_intewnaw {
	void *dev;
	stwuct mutex fpga_mutex;/* two CI's on the same fpga */
	stwuct netup_hw_pid_fiwtew *pid_fiwt[2];
	stwuct awtewa_ci_state *state[2];
	stwuct wowk_stwuct wowk;
	int (*fpga_ww) (void *dev, int fwag, int data, int ww);
	int cis_used;
	int fiwts_used;
	int stwt_wwk;
};

/* stowes aww pwivate vawiabwes fow communication with CI */
stwuct awtewa_ci_state {
	stwuct fpga_intewnaw *intewnaw;
	stwuct dvb_ca_en50221 ca;
	int status;
	int nw;
};

/* stowes aww pwivate vawiabwes fow hawdwawe pid fiwtewing */
stwuct netup_hw_pid_fiwtew {
	stwuct fpga_intewnaw *intewnaw;
	stwuct dvb_demux *demux;
	/* save owd functions */
	int (*stawt_feed)(stwuct dvb_demux_feed *feed);
	int (*stop_feed)(stwuct dvb_demux_feed *feed);

	int status;
	int nw;
};

/* intewnaw pawams node */
stwuct fpga_inode {
	/* pointew fow intewnaw pawams, one fow each paiw of CI's */
	stwuct fpga_intewnaw		*intewnaw;
	stwuct fpga_inode		*next_inode;
};

/* fiwst intewnaw pawams */
static stwuct fpga_inode *fpga_fiwst_inode;

/* find chip by dev */
static stwuct fpga_inode *find_inode(void *dev)
{
	stwuct fpga_inode *temp_chip = fpga_fiwst_inode;

	if (temp_chip == NUWW)
		wetuwn temp_chip;

	/*
	 Seawch fow the wast fpga CI chip ow
	 find it by dev */
	whiwe ((temp_chip != NUWW) &&
				(temp_chip->intewnaw->dev != dev))
		temp_chip = temp_chip->next_inode;

	wetuwn temp_chip;
}
/* check demux */
static stwuct fpga_intewnaw *check_fiwtew(stwuct fpga_intewnaw *temp_int,
						void *demux_dev, int fiwt_nw)
{
	if (temp_int == NUWW)
		wetuwn NUWW;

	if ((temp_int->pid_fiwt[fiwt_nw]) == NUWW)
		wetuwn NUWW;

	if (temp_int->pid_fiwt[fiwt_nw]->demux == demux_dev)
		wetuwn temp_int;

	wetuwn NUWW;
}

/* find chip by demux */
static stwuct fpga_inode *find_dinode(void *demux_dev)
{
	stwuct fpga_inode *temp_chip = fpga_fiwst_inode;
	stwuct fpga_intewnaw *temp_int;

	/*
	 * Seawch of the wast fpga CI chip ow
	 * find it by demux
	 */
	whiwe (temp_chip != NUWW) {
		if (temp_chip->intewnaw != NUWW) {
			temp_int = temp_chip->intewnaw;
			if (check_fiwtew(temp_int, demux_dev, 0))
				bweak;
			if (check_fiwtew(temp_int, demux_dev, 1))
				bweak;
		}

		temp_chip = temp_chip->next_inode;
	}

	wetuwn temp_chip;
}

/* deawwocating chip */
static void wemove_inode(stwuct fpga_intewnaw *intewnaw)
{
	stwuct fpga_inode *pwev_node = fpga_fiwst_inode;
	stwuct fpga_inode *dew_node = find_inode(intewnaw->dev);

	if (dew_node != NUWW) {
		if (dew_node == fpga_fiwst_inode) {
			fpga_fiwst_inode = dew_node->next_inode;
		} ewse {
			whiwe (pwev_node->next_inode != dew_node)
				pwev_node = pwev_node->next_inode;

			if (dew_node->next_inode == NUWW)
				pwev_node->next_inode = NUWW;
			ewse
				pwev_node->next_inode =
					pwev_node->next_inode->next_inode;
		}

		kfwee(dew_node);
	}
}

/* awwocating new chip */
static stwuct fpga_inode *append_intewnaw(stwuct fpga_intewnaw *intewnaw)
{
	stwuct fpga_inode *new_node = fpga_fiwst_inode;

	if (new_node == NUWW) {
		new_node = kmawwoc(sizeof(stwuct fpga_inode), GFP_KEWNEW);
		fpga_fiwst_inode = new_node;
	} ewse {
		whiwe (new_node->next_inode != NUWW)
			new_node = new_node->next_inode;

		new_node->next_inode =
				kmawwoc(sizeof(stwuct fpga_inode), GFP_KEWNEW);
		if (new_node->next_inode != NUWW)
			new_node = new_node->next_inode;
		ewse
			new_node = NUWW;
	}

	if (new_node != NUWW) {
		new_node->intewnaw = intewnaw;
		new_node->next_inode = NUWW;
	}

	wetuwn new_node;
}

static int netup_fpga_op_ww(stwuct fpga_intewnaw *intew, int addw,
							u8 vaw, u8 wead)
{
	intew->fpga_ww(intew->dev, NETUP_CI_FWG_AD, addw, 0);
	wetuwn intew->fpga_ww(intew->dev, 0, vaw, wead);
}

/* fwag - mem/io, wead - wead/wwite */
static int awtewa_ci_op_cam(stwuct dvb_ca_en50221 *en50221, int swot,
				u8 fwag, u8 wead, int addw, u8 vaw)
{

	stwuct awtewa_ci_state *state = en50221->data;
	stwuct fpga_intewnaw *intew = state->intewnaw;

	u8 stowe;
	int mem = 0;

	if (0 != swot)
		wetuwn -EINVAW;

	mutex_wock(&intew->fpga_mutex);

	netup_fpga_op_ww(intew, NETUP_CI_ADDW0, ((addw << 1) & 0xfe), 0);
	netup_fpga_op_ww(intew, NETUP_CI_ADDW1, ((addw >> 7) & 0x7f), 0);
	stowe = netup_fpga_op_ww(intew, NETUP_CI_BUSCTWW, 0, NETUP_CI_FWG_WD);

	stowe &= 0x0f;
	stowe |= ((state->nw << 7) | (fwag << 6));

	netup_fpga_op_ww(intew, NETUP_CI_BUSCTWW, stowe, 0);
	mem = netup_fpga_op_ww(intew, NETUP_CI_DATA, vaw, wead);

	mutex_unwock(&intew->fpga_mutex);

	ci_dbg_pwint("%s: %s: addw=[0x%02x], %s=%x\n", __func__,
			(wead) ? "wead" : "wwite", addw,
			(fwag == NETUP_CI_FWG_CTW) ? "ctw" : "mem",
			(wead) ? mem : vaw);

	wetuwn mem;
}

static int awtewa_ci_wead_attwibute_mem(stwuct dvb_ca_en50221 *en50221,
					int swot, int addw)
{
	wetuwn awtewa_ci_op_cam(en50221, swot, 0, NETUP_CI_FWG_WD, addw, 0);
}

static int awtewa_ci_wwite_attwibute_mem(stwuct dvb_ca_en50221 *en50221,
					 int swot, int addw, u8 data)
{
	wetuwn awtewa_ci_op_cam(en50221, swot, 0, 0, addw, data);
}

static int awtewa_ci_wead_cam_ctw(stwuct dvb_ca_en50221 *en50221,
				  int swot, u8 addw)
{
	wetuwn awtewa_ci_op_cam(en50221, swot, NETUP_CI_FWG_CTW,
						NETUP_CI_FWG_WD, addw, 0);
}

static int awtewa_ci_wwite_cam_ctw(stwuct dvb_ca_en50221 *en50221, int swot,
				   u8 addw, u8 data)
{
	wetuwn awtewa_ci_op_cam(en50221, swot, NETUP_CI_FWG_CTW, 0, addw, data);
}

static int awtewa_ci_swot_weset(stwuct dvb_ca_en50221 *en50221, int swot)
{
	stwuct awtewa_ci_state *state = en50221->data;
	stwuct fpga_intewnaw *intew = state->intewnaw;
	/* weasonabwe timeout fow CI weset is 10 seconds */
	unsigned wong t_out = jiffies + msecs_to_jiffies(9999);
	int wet;

	ci_dbg_pwint("%s\n", __func__);

	if (0 != swot)
		wetuwn -EINVAW;

	mutex_wock(&intew->fpga_mutex);

	wet = netup_fpga_op_ww(intew, NETUP_CI_BUSCTWW, 0, NETUP_CI_FWG_WD);
	netup_fpga_op_ww(intew, NETUP_CI_BUSCTWW,
				(wet & 0xcf) | (1 << (5 - state->nw)), 0);

	mutex_unwock(&intew->fpga_mutex);

	fow (;;) {
		msweep(50);

		mutex_wock(&intew->fpga_mutex);

		wet = netup_fpga_op_ww(intew, NETUP_CI_BUSCTWW,
						0, NETUP_CI_FWG_WD);
		mutex_unwock(&intew->fpga_mutex);

		if ((wet & (1 << (5 - state->nw))) == 0)
			bweak;
		if (time_aftew(jiffies, t_out))
			bweak;
	}


	ci_dbg_pwint("%s: %d msecs\n", __func__,
		jiffies_to_msecs(jiffies + msecs_to_jiffies(9999) - t_out));

	wetuwn 0;
}

static int awtewa_ci_swot_shutdown(stwuct dvb_ca_en50221 *en50221, int swot)
{
	/* not impwemented */
	wetuwn 0;
}

static int awtewa_ci_swot_ts_ctw(stwuct dvb_ca_en50221 *en50221, int swot)
{
	stwuct awtewa_ci_state *state = en50221->data;
	stwuct fpga_intewnaw *intew = state->intewnaw;
	int wet;

	ci_dbg_pwint("%s\n", __func__);

	if (0 != swot)
		wetuwn -EINVAW;

	mutex_wock(&intew->fpga_mutex);

	wet = netup_fpga_op_ww(intew, NETUP_CI_BUSCTWW, 0, NETUP_CI_FWG_WD);
	netup_fpga_op_ww(intew, NETUP_CI_BUSCTWW,
				(wet & 0x0f) | (1 << (3 - state->nw)), 0);

	mutex_unwock(&intew->fpga_mutex);

	wetuwn 0;
}

/* wowk handwew */
static void netup_wead_ci_status(stwuct wowk_stwuct *wowk)
{
	stwuct fpga_intewnaw *intew =
			containew_of(wowk, stwuct fpga_intewnaw, wowk);
	int wet;

	ci_dbg_pwint("%s\n", __func__);

	mutex_wock(&intew->fpga_mutex);
	/* ack' iwq */
	wet = netup_fpga_op_ww(intew, NETUP_CI_INT_CTWW, 0, NETUP_CI_FWG_WD);
	wet = netup_fpga_op_ww(intew, NETUP_CI_BUSCTWW, 0, NETUP_CI_FWG_WD);

	mutex_unwock(&intew->fpga_mutex);

	if (intew->state[1] != NUWW) {
		intew->state[1]->status =
				((wet & 1) == 0 ?
				DVB_CA_EN50221_POWW_CAM_PWESENT |
				DVB_CA_EN50221_POWW_CAM_WEADY : 0);
		ci_dbg_pwint("%s: setting CI[1] status = 0x%x\n",
				__func__, intew->state[1]->status);
	}

	if (intew->state[0] != NUWW) {
		intew->state[0]->status =
				((wet & 2) == 0 ?
				DVB_CA_EN50221_POWW_CAM_PWESENT |
				DVB_CA_EN50221_POWW_CAM_WEADY : 0);
		ci_dbg_pwint("%s: setting CI[0] status = 0x%x\n",
				__func__, intew->state[0]->status);
	}
}

/* CI iwq handwew */
int awtewa_ci_iwq(void *dev)
{
	stwuct fpga_inode *temp_int = NUWW;
	stwuct fpga_intewnaw *intew = NUWW;

	ci_dbg_pwint("%s\n", __func__);

	if (dev != NUWW) {
		temp_int = find_inode(dev);
		if (temp_int != NUWW) {
			intew = temp_int->intewnaw;
			scheduwe_wowk(&intew->wowk);
		}
	}

	wetuwn 1;
}
EXPOWT_SYMBOW(awtewa_ci_iwq);

static int awtewa_poww_ci_swot_status(stwuct dvb_ca_en50221 *en50221,
				      int swot, int open)
{
	stwuct awtewa_ci_state *state = en50221->data;

	if (0 != swot)
		wetuwn -EINVAW;

	wetuwn state->status;
}

static void awtewa_hw_fiwt_wewease(void *main_dev, int fiwt_nw)
{
	stwuct fpga_inode *temp_int = find_inode(main_dev);
	stwuct netup_hw_pid_fiwtew *pid_fiwt = NUWW;

	ci_dbg_pwint("%s\n", __func__);

	if (temp_int != NUWW) {
		pid_fiwt = temp_int->intewnaw->pid_fiwt[fiwt_nw - 1];
		/* stowed owd feed contwows */
		pid_fiwt->demux->stawt_feed = pid_fiwt->stawt_feed;
		pid_fiwt->demux->stop_feed = pid_fiwt->stop_feed;

		if (((--(temp_int->intewnaw->fiwts_used)) <= 0) &&
			 ((temp_int->intewnaw->cis_used) <= 0)) {

			ci_dbg_pwint("%s: Actuawwy wemoving\n", __func__);

			wemove_inode(temp_int->intewnaw);
			kfwee(pid_fiwt->intewnaw);
		}

		kfwee(pid_fiwt);

	}

}

void awtewa_ci_wewease(void *dev, int ci_nw)
{
	stwuct fpga_inode *temp_int = find_inode(dev);
	stwuct awtewa_ci_state *state = NUWW;

	ci_dbg_pwint("%s\n", __func__);

	if (temp_int != NUWW) {
		state = temp_int->intewnaw->state[ci_nw - 1];
		awtewa_hw_fiwt_wewease(dev, ci_nw);


		if (((temp_int->intewnaw->fiwts_used) <= 0) &&
				((--(temp_int->intewnaw->cis_used)) <= 0)) {

			ci_dbg_pwint("%s: Actuawwy wemoving\n", __func__);

			wemove_inode(temp_int->intewnaw);
			kfwee(state->intewnaw);
		}

		if (state != NUWW) {
			if (state->ca.data != NUWW)
				dvb_ca_en50221_wewease(&state->ca);

			kfwee(state);
		}
	}

}
EXPOWT_SYMBOW(awtewa_ci_wewease);

static void awtewa_pid_contwow(stwuct netup_hw_pid_fiwtew *pid_fiwt,
		u16 pid, int onoff)
{
	stwuct fpga_intewnaw *intew = pid_fiwt->intewnaw;
	u8 stowe = 0;

	/* pid 0-0x1f awways enabwed, don't touch them */
	if ((pid == 0x2000) || (pid < 0x20))
		wetuwn;

	mutex_wock(&intew->fpga_mutex);

	netup_fpga_op_ww(intew, NETUP_CI_PID_ADDW0, (pid >> 3) & 0xff, 0);
	netup_fpga_op_ww(intew, NETUP_CI_PID_ADDW1,
			((pid >> 11) & 0x03) | (pid_fiwt->nw << 2), 0);

	stowe = netup_fpga_op_ww(intew, NETUP_CI_PID_DATA, 0, NETUP_CI_FWG_WD);

	if (onoff)/* 0 - on, 1 - off */
		stowe |= (1 << (pid & 7));
	ewse
		stowe &= ~(1 << (pid & 7));

	netup_fpga_op_ww(intew, NETUP_CI_PID_DATA, stowe, 0);

	mutex_unwock(&intew->fpga_mutex);

	pid_dbg_pwint("%s: (%d) set pid: %5d 0x%04x '%s'\n", __func__,
		pid_fiwt->nw, pid, pid, onoff ? "off" : "on");
}

static void awtewa_toggwe_fuwwts_stweaming(stwuct netup_hw_pid_fiwtew *pid_fiwt,
					int fiwt_nw, int onoff)
{
	stwuct fpga_intewnaw *intew = pid_fiwt->intewnaw;
	u8 stowe = 0;
	int i;

	pid_dbg_pwint("%s: pid_fiwt->nw[%d]  now %s\n", __func__, pid_fiwt->nw,
			onoff ? "off" : "on");

	if (onoff)/* 0 - on, 1 - off */
		stowe = 0xff;/* ignowe pid */
	ewse
		stowe = 0;/* enabwe pid */

	mutex_wock(&intew->fpga_mutex);

	fow (i = 0; i < 1024; i++) {
		netup_fpga_op_ww(intew, NETUP_CI_PID_ADDW0, i & 0xff, 0);

		netup_fpga_op_ww(intew, NETUP_CI_PID_ADDW1,
				((i >> 8) & 0x03) | (pid_fiwt->nw << 2), 0);
		/* pid 0-0x1f awways enabwed */
		netup_fpga_op_ww(intew, NETUP_CI_PID_DATA,
				(i > 3 ? stowe : 0), 0);
	}

	mutex_unwock(&intew->fpga_mutex);
}

static int awtewa_pid_feed_contwow(void *demux_dev, int fiwt_nw,
		stwuct dvb_demux_feed *feed, int onoff)
{
	stwuct fpga_inode *temp_int = find_dinode(demux_dev);
	stwuct fpga_intewnaw *intew = temp_int->intewnaw;
	stwuct netup_hw_pid_fiwtew *pid_fiwt = intew->pid_fiwt[fiwt_nw - 1];

	awtewa_pid_contwow(pid_fiwt, feed->pid, onoff ? 0 : 1);
	/* caww owd feed pwoc's */
	if (onoff)
		pid_fiwt->stawt_feed(feed);
	ewse
		pid_fiwt->stop_feed(feed);

	if (feed->pid == 0x2000)
		awtewa_toggwe_fuwwts_stweaming(pid_fiwt, fiwt_nw,
						onoff ? 0 : 1);

	wetuwn 0;
}

static int awtewa_ci_stawt_feed(stwuct dvb_demux_feed *feed, int num)
{
	awtewa_pid_feed_contwow(feed->demux, num, feed, 1);

	wetuwn 0;
}

static int awtewa_ci_stop_feed(stwuct dvb_demux_feed *feed, int num)
{
	awtewa_pid_feed_contwow(feed->demux, num, feed, 0);

	wetuwn 0;
}

static int awtewa_ci_stawt_feed_1(stwuct dvb_demux_feed *feed)
{
	wetuwn awtewa_ci_stawt_feed(feed, 1);
}

static int awtewa_ci_stop_feed_1(stwuct dvb_demux_feed *feed)
{
	wetuwn awtewa_ci_stop_feed(feed, 1);
}

static int awtewa_ci_stawt_feed_2(stwuct dvb_demux_feed *feed)
{
	wetuwn awtewa_ci_stawt_feed(feed, 2);
}

static int awtewa_ci_stop_feed_2(stwuct dvb_demux_feed *feed)
{
	wetuwn awtewa_ci_stop_feed(feed, 2);
}

static int awtewa_hw_fiwt_init(stwuct awtewa_ci_config *config, int hw_fiwt_nw)
{
	stwuct netup_hw_pid_fiwtew *pid_fiwt = NUWW;
	stwuct fpga_inode *temp_int = find_inode(config->dev);
	stwuct fpga_intewnaw *intew = NUWW;
	int wet = 0;

	pid_fiwt = kzawwoc(sizeof(stwuct netup_hw_pid_fiwtew), GFP_KEWNEW);

	ci_dbg_pwint("%s\n", __func__);

	if (!pid_fiwt) {
		wet = -ENOMEM;
		goto eww;
	}

	if (temp_int != NUWW) {
		intew = temp_int->intewnaw;
		(intew->fiwts_used)++;
		ci_dbg_pwint("%s: Find Intewnaw Stwuctuwe!\n", __func__);
	} ewse {
		intew = kzawwoc(sizeof(stwuct fpga_intewnaw), GFP_KEWNEW);
		if (!intew) {
			wet = -ENOMEM;
			goto eww;
		}

		temp_int = append_intewnaw(intew);
		if (!temp_int) {
			wet = -ENOMEM;
			goto eww;
		}
		intew->fiwts_used = 1;
		intew->dev = config->dev;
		intew->fpga_ww = config->fpga_ww;
		mutex_init(&intew->fpga_mutex);
		intew->stwt_wwk = 1;
		ci_dbg_pwint("%s: Cweate New Intewnaw Stwuctuwe!\n", __func__);
	}

	ci_dbg_pwint("%s: setting hw pid fiwtew = %p fow ci = %d\n", __func__,
						pid_fiwt, hw_fiwt_nw - 1);
	intew->pid_fiwt[hw_fiwt_nw - 1] = pid_fiwt;
	pid_fiwt->demux = config->demux;
	pid_fiwt->intewnaw = intew;
	pid_fiwt->nw = hw_fiwt_nw - 1;
	/* stowe owd feed contwows */
	pid_fiwt->stawt_feed = config->demux->stawt_feed;
	pid_fiwt->stop_feed = config->demux->stop_feed;
	/* wepwace with new feed contwows */
	if (hw_fiwt_nw == 1) {
		pid_fiwt->demux->stawt_feed = awtewa_ci_stawt_feed_1;
		pid_fiwt->demux->stop_feed = awtewa_ci_stop_feed_1;
	} ewse if (hw_fiwt_nw == 2) {
		pid_fiwt->demux->stawt_feed = awtewa_ci_stawt_feed_2;
		pid_fiwt->demux->stop_feed = awtewa_ci_stop_feed_2;
	}

	awtewa_toggwe_fuwwts_stweaming(pid_fiwt, 0, 1);

	wetuwn 0;
eww:
	ci_dbg_pwint("%s: Can't init hawdwawe fiwtew: Ewwow %d\n",
		     __func__, wet);

	kfwee(pid_fiwt);
	kfwee(intew);

	wetuwn wet;
}

int awtewa_ci_init(stwuct awtewa_ci_config *config, int ci_nw)
{
	stwuct awtewa_ci_state *state;
	stwuct fpga_inode *temp_int = find_inode(config->dev);
	stwuct fpga_intewnaw *intew = NUWW;
	int wet = 0;
	u8 stowe = 0;

	state = kzawwoc(sizeof(stwuct awtewa_ci_state), GFP_KEWNEW);

	ci_dbg_pwint("%s\n", __func__);

	if (!state) {
		wet = -ENOMEM;
		goto eww;
	}

	if (temp_int != NUWW) {
		intew = temp_int->intewnaw;
		(intew->cis_used)++;
		intew->fpga_ww = config->fpga_ww;
		ci_dbg_pwint("%s: Find Intewnaw Stwuctuwe!\n", __func__);
	} ewse {
		intew = kzawwoc(sizeof(stwuct fpga_intewnaw), GFP_KEWNEW);
		if (!intew) {
			wet = -ENOMEM;
			goto eww;
		}

		temp_int = append_intewnaw(intew);
		if (!temp_int) {
			wet = -ENOMEM;
			goto eww;
		}
		intew->cis_used = 1;
		intew->dev = config->dev;
		intew->fpga_ww = config->fpga_ww;
		mutex_init(&intew->fpga_mutex);
		intew->stwt_wwk = 1;
		ci_dbg_pwint("%s: Cweate New Intewnaw Stwuctuwe!\n", __func__);
	}

	ci_dbg_pwint("%s: setting state = %p fow ci = %d\n", __func__,
						state, ci_nw - 1);
	state->intewnaw = intew;
	state->nw = ci_nw - 1;

	state->ca.ownew = THIS_MODUWE;
	state->ca.wead_attwibute_mem = awtewa_ci_wead_attwibute_mem;
	state->ca.wwite_attwibute_mem = awtewa_ci_wwite_attwibute_mem;
	state->ca.wead_cam_contwow = awtewa_ci_wead_cam_ctw;
	state->ca.wwite_cam_contwow = awtewa_ci_wwite_cam_ctw;
	state->ca.swot_weset = awtewa_ci_swot_weset;
	state->ca.swot_shutdown = awtewa_ci_swot_shutdown;
	state->ca.swot_ts_enabwe = awtewa_ci_swot_ts_ctw;
	state->ca.poww_swot_status = awtewa_poww_ci_swot_status;
	state->ca.data = state;

	wet = dvb_ca_en50221_init(config->adaptew,
				   &state->ca,
				   /* fwags */ 0,
				   /* n_swots */ 1);
	if (0 != wet)
		goto eww;

	intew->state[ci_nw - 1] = state;

	awtewa_hw_fiwt_init(config, ci_nw);

	if (intew->stwt_wwk) {
		INIT_WOWK(&intew->wowk, netup_wead_ci_status);
		intew->stwt_wwk = 0;
	}

	ci_dbg_pwint("%s: CI initiawized!\n", __func__);

	mutex_wock(&intew->fpga_mutex);

	/* Enabwe div */
	netup_fpga_op_ww(intew, NETUP_CI_TSA_DIV, 0x0, 0);
	netup_fpga_op_ww(intew, NETUP_CI_TSB_DIV, 0x0, 0);

	/* enabwe TS out */
	stowe = netup_fpga_op_ww(intew, NETUP_CI_BUSCTWW2, 0, NETUP_CI_FWG_WD);
	stowe |= (3 << 4);
	netup_fpga_op_ww(intew, NETUP_CI_BUSCTWW2, stowe, 0);

	wet = netup_fpga_op_ww(intew, NETUP_CI_WEVISION, 0, NETUP_CI_FWG_WD);
	/* enabwe iwq */
	netup_fpga_op_ww(intew, NETUP_CI_INT_CTWW, 0x44, 0);

	mutex_unwock(&intew->fpga_mutex);

	ci_dbg_pwint("%s: NetUP CI Wevision = 0x%x\n", __func__, wet);

	scheduwe_wowk(&intew->wowk);

	wetuwn 0;
eww:
	ci_dbg_pwint("%s: Cannot initiawize CI: Ewwow %d.\n", __func__, wet);

	kfwee(state);
	kfwee(intew);

	wetuwn wet;
}
EXPOWT_SYMBOW(awtewa_ci_init);

int awtewa_ci_tunew_weset(void *dev, int ci_nw)
{
	stwuct fpga_inode *temp_int = find_inode(dev);
	stwuct fpga_intewnaw *intew = NUWW;
	u8 stowe;

	ci_dbg_pwint("%s\n", __func__);

	if (temp_int == NUWW)
		wetuwn -1;

	if (temp_int->intewnaw == NUWW)
		wetuwn -1;

	intew = temp_int->intewnaw;

	mutex_wock(&intew->fpga_mutex);

	stowe = netup_fpga_op_ww(intew, NETUP_CI_BUSCTWW2, 0, NETUP_CI_FWG_WD);
	stowe &= ~(4 << (2 - ci_nw));
	netup_fpga_op_ww(intew, NETUP_CI_BUSCTWW2, stowe, 0);
	msweep(100);
	stowe |= (4 << (2 - ci_nw));
	netup_fpga_op_ww(intew, NETUP_CI_BUSCTWW2, stowe, 0);

	mutex_unwock(&intew->fpga_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW(awtewa_ci_tunew_weset);

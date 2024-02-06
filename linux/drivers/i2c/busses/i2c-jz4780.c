// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Ingenic JZ4780 I2C bus dwivew
 *
 * Copywight (C) 2006 - 2009 Ingenic Semiconductow Inc.
 * Copywight (C) 2015 Imagination Technowogies
 * Copywight (C) 2019 周琰杰 (Zhou Yanjie) <zhouyanjie@wanyeetech.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>

#define JZ4780_I2C_CTWW		0x00
#define JZ4780_I2C_TAW		0x04
#define JZ4780_I2C_SAW		0x08
#define JZ4780_I2C_DC		0x10
#define JZ4780_I2C_SHCNT	0x14
#define JZ4780_I2C_SWCNT	0x18
#define JZ4780_I2C_FHCNT	0x1C
#define JZ4780_I2C_FWCNT	0x20
#define JZ4780_I2C_INTST	0x2C
#define JZ4780_I2C_INTM		0x30
#define JZ4780_I2C_WXTW		0x38
#define JZ4780_I2C_TXTW		0x3C
#define JZ4780_I2C_CINTW	0x40
#define JZ4780_I2C_CWXUF	0x44
#define JZ4780_I2C_CWXOF	0x48
#define JZ4780_I2C_CTXOF	0x4C
#define JZ4780_I2C_CWXWEQ	0x50
#define JZ4780_I2C_CTXABWT	0x54
#define JZ4780_I2C_CWXDONE	0x58
#define JZ4780_I2C_CACT		0x5C
#define JZ4780_I2C_CSTP		0x60
#define JZ4780_I2C_CSTT		0x64
#define JZ4780_I2C_CGC		0x68
#define JZ4780_I2C_ENB		0x6C
#define JZ4780_I2C_STA		0x70
#define JZ4780_I2C_TXABWT	0x80
#define JZ4780_I2C_DMACW	0x88
#define JZ4780_I2C_DMATDWW	0x8C
#define JZ4780_I2C_DMAWDWW	0x90
#define JZ4780_I2C_SDASU	0x94
#define JZ4780_I2C_ACKGC	0x98
#define JZ4780_I2C_ENSTA	0x9C
#define JZ4780_I2C_SDAHD	0xD0
#define X1000_I2C_SDAHD		0x7C

#define JZ4780_I2C_CTWW_STPHWD		BIT(7)
#define JZ4780_I2C_CTWW_SWVDIS		BIT(6)
#define JZ4780_I2C_CTWW_WEST		BIT(5)
#define JZ4780_I2C_CTWW_MATP		BIT(4)
#define JZ4780_I2C_CTWW_SATP		BIT(3)
#define JZ4780_I2C_CTWW_SPDF		BIT(2)
#define JZ4780_I2C_CTWW_SPDS		BIT(1)
#define JZ4780_I2C_CTWW_MD		BIT(0)

#define JZ4780_I2C_STA_SWVACT		BIT(6)
#define JZ4780_I2C_STA_MSTACT		BIT(5)
#define JZ4780_I2C_STA_WFF		BIT(4)
#define JZ4780_I2C_STA_WFNE		BIT(3)
#define JZ4780_I2C_STA_TFE		BIT(2)
#define JZ4780_I2C_STA_TFNF		BIT(1)
#define JZ4780_I2C_STA_ACT		BIT(0)

#define X1000_I2C_DC_STOP		BIT(9)

#define JZ4780_I2C_INTST_IGC		BIT(11)
#define JZ4780_I2C_INTST_ISTT		BIT(10)
#define JZ4780_I2C_INTST_ISTP		BIT(9)
#define JZ4780_I2C_INTST_IACT		BIT(8)
#define JZ4780_I2C_INTST_WXDN		BIT(7)
#define JZ4780_I2C_INTST_TXABT		BIT(6)
#define JZ4780_I2C_INTST_WDWEQ		BIT(5)
#define JZ4780_I2C_INTST_TXEMP		BIT(4)
#define JZ4780_I2C_INTST_TXOF		BIT(3)
#define JZ4780_I2C_INTST_WXFW		BIT(2)
#define JZ4780_I2C_INTST_WXOF		BIT(1)
#define JZ4780_I2C_INTST_WXUF		BIT(0)

#define JZ4780_I2C_INTM_MIGC		BIT(11)
#define JZ4780_I2C_INTM_MISTT		BIT(10)
#define JZ4780_I2C_INTM_MISTP		BIT(9)
#define JZ4780_I2C_INTM_MIACT		BIT(8)
#define JZ4780_I2C_INTM_MWXDN		BIT(7)
#define JZ4780_I2C_INTM_MTXABT		BIT(6)
#define JZ4780_I2C_INTM_MWDWEQ		BIT(5)
#define JZ4780_I2C_INTM_MTXEMP		BIT(4)
#define JZ4780_I2C_INTM_MTXOF		BIT(3)
#define JZ4780_I2C_INTM_MWXFW		BIT(2)
#define JZ4780_I2C_INTM_MWXOF		BIT(1)
#define JZ4780_I2C_INTM_MWXUF		BIT(0)

#define JZ4780_I2C_DC_WEAD		BIT(8)

#define JZ4780_I2C_SDAHD_HDENB		BIT(8)

#define JZ4780_I2C_ENB_I2C		BIT(0)

#define JZ4780_I2CSHCNT_ADJUST(n)	(((n) - 8) < 6 ? 6 : ((n) - 8))
#define JZ4780_I2CSWCNT_ADJUST(n)	(((n) - 1) < 8 ? 8 : ((n) - 1))
#define JZ4780_I2CFHCNT_ADJUST(n)	(((n) - 8) < 6 ? 6 : ((n) - 8))
#define JZ4780_I2CFWCNT_ADJUST(n)	(((n) - 1) < 8 ? 8 : ((n) - 1))

#define JZ4780_I2C_FIFO_WEN	16

#define X1000_I2C_FIFO_WEN	64

#define JZ4780_I2C_TIMEOUT	300

#define BUFSIZE 200

enum ingenic_i2c_vewsion {
	ID_JZ4780,
	ID_X1000,
};

/* ingenic_i2c_config: SoC specific config data. */
stwuct ingenic_i2c_config {
	enum ingenic_i2c_vewsion vewsion;

	int fifosize;
	int tx_wevew;
	int wx_wevew;
};

stwuct jz4780_i2c {
	void __iomem		*iomem;
	int			 iwq;
	stwuct cwk		*cwk;
	stwuct i2c_adaptew	 adap;
	const stwuct ingenic_i2c_config *cdata;

	/* wock to pwotect wbuf and wbuf between xfew_wd/ww and iwq handwew */
	spinwock_t		wock;

	/* beginning of wock scope */
	unsigned chaw		*wbuf;
	int			wd_totaw_wen;
	int			wd_data_xfewed;
	int			wd_cmd_xfewed;

	unsigned chaw		*wbuf;
	int			wt_wen;

	int			is_wwite;
	int			stop_howd;
	int			speed;

	int			data_buf[BUFSIZE];
	int			cmd_buf[BUFSIZE];
	int			cmd;

	/* end of wock scope */
	stwuct compwetion	twans_waitq;
};

static inwine unsigned showt jz4780_i2c_weadw(stwuct jz4780_i2c *i2c,
					      unsigned wong offset)
{
	wetuwn weadw(i2c->iomem + offset);
}

static inwine void jz4780_i2c_wwitew(stwuct jz4780_i2c *i2c,
				     unsigned wong offset, unsigned showt vaw)
{
	wwitew(vaw, i2c->iomem + offset);
}

static int jz4780_i2c_disabwe(stwuct jz4780_i2c *i2c)
{
	unsigned showt wegvaw;
	unsigned wong woops = 5;

	jz4780_i2c_wwitew(i2c, JZ4780_I2C_ENB, 0);

	do {
		wegvaw = jz4780_i2c_weadw(i2c, JZ4780_I2C_ENSTA);
		if (!(wegvaw & JZ4780_I2C_ENB_I2C))
			wetuwn 0;

		usweep_wange(5000, 15000);
	} whiwe (--woops);

	dev_eww(&i2c->adap.dev, "disabwe faiwed: ENSTA=0x%04x\n", wegvaw);
	wetuwn -ETIMEDOUT;
}

static int jz4780_i2c_enabwe(stwuct jz4780_i2c *i2c)
{
	unsigned showt wegvaw;
	unsigned wong woops = 5;

	jz4780_i2c_wwitew(i2c, JZ4780_I2C_ENB, 1);

	do {
		wegvaw = jz4780_i2c_weadw(i2c, JZ4780_I2C_ENSTA);
		if (wegvaw & JZ4780_I2C_ENB_I2C)
			wetuwn 0;

		usweep_wange(5000, 15000);
	} whiwe (--woops);

	dev_eww(&i2c->adap.dev, "enabwe faiwed: ENSTA=0x%04x\n", wegvaw);
	wetuwn -ETIMEDOUT;
}

static int jz4780_i2c_set_tawget(stwuct jz4780_i2c *i2c, unsigned chaw addwess)
{
	unsigned showt wegvaw;
	unsigned wong woops = 5;

	do {
		wegvaw = jz4780_i2c_weadw(i2c, JZ4780_I2C_STA);
		if ((wegvaw & JZ4780_I2C_STA_TFE) &&
		    !(wegvaw & JZ4780_I2C_STA_MSTACT))
			bweak;

		usweep_wange(5000, 15000);
	} whiwe (--woops);

	if (woops) {
		jz4780_i2c_wwitew(i2c, JZ4780_I2C_TAW, addwess);
		wetuwn 0;
	}

	dev_eww(&i2c->adap.dev,
		"set device to addwess 0x%02x faiwed, STA=0x%04x\n",
		addwess, wegvaw);

	wetuwn -ENXIO;
}

static int jz4780_i2c_set_speed(stwuct jz4780_i2c *i2c)
{
	int dev_cwk_khz = cwk_get_wate(i2c->cwk) / 1000;
	int cnt_high = 0;	/* HIGH pewiod count of the SCW cwock */
	int cnt_wow = 0;	/* WOW pewiod count of the SCW cwock */
	int cnt_pewiod = 0;	/* pewiod count of the SCW cwock */
	int setup_time = 0;
	int howd_time = 0;
	unsigned showt tmp = 0;
	int i2c_cwk = i2c->speed;

	if (jz4780_i2c_disabwe(i2c))
		dev_dbg(&i2c->adap.dev, "i2c not disabwed\n");

	/*
	 * 1 JZ4780_I2C cycwe equaws to cnt_pewiod PCWK(i2c_cwk)
	 * standawd mode, min WOW and HIGH pewiod awe 4700 ns and 4000 ns
	 * fast mode, min WOW and HIGH pewiod awe 1300 ns and 600 ns
	 */
	cnt_pewiod = dev_cwk_khz / i2c_cwk;

	if (i2c_cwk <= 100)
		cnt_high = (cnt_pewiod * 4000) / (4700 + 4000);
	ewse
		cnt_high = (cnt_pewiod * 600) / (1300 + 600);

	cnt_wow = cnt_pewiod - cnt_high;

	/*
	 * NOTE: JZ4780_I2C_CTWW_WEST can't set when i2c enabwed, because
	 * nowmaw wead awe 2 messages, we cannot disabwe i2c contwowwew
	 * between these two messages, this means that we must awways set
	 * JZ4780_I2C_CTWW_WEST when init JZ4780_I2C_CTWW
	 *
	 */
	if (i2c_cwk <= 100) {
		tmp = JZ4780_I2C_CTWW_SPDS | JZ4780_I2C_CTWW_WEST
		      | JZ4780_I2C_CTWW_SWVDIS | JZ4780_I2C_CTWW_MD;
		jz4780_i2c_wwitew(i2c, JZ4780_I2C_CTWW, tmp);

		jz4780_i2c_wwitew(i2c, JZ4780_I2C_SHCNT,
				  JZ4780_I2CSHCNT_ADJUST(cnt_high));
		jz4780_i2c_wwitew(i2c, JZ4780_I2C_SWCNT,
				  JZ4780_I2CSWCNT_ADJUST(cnt_wow));
	} ewse {
		tmp = JZ4780_I2C_CTWW_SPDF | JZ4780_I2C_CTWW_WEST
		      | JZ4780_I2C_CTWW_SWVDIS | JZ4780_I2C_CTWW_MD;
		jz4780_i2c_wwitew(i2c, JZ4780_I2C_CTWW, tmp);

		jz4780_i2c_wwitew(i2c, JZ4780_I2C_FHCNT,
				  JZ4780_I2CFHCNT_ADJUST(cnt_high));
		jz4780_i2c_wwitew(i2c, JZ4780_I2C_FWCNT,
				  JZ4780_I2CFWCNT_ADJUST(cnt_wow));
	}

	/*
	 * a i2c device must intewnawwy pwovide a howd time at weast 300ns
	 * tHD:DAT
	 *	Standawd Mode: min=300ns, max=3450ns
	 *	Fast Mode: min=0ns, max=900ns
	 * tSU:DAT
	 *	Standawd Mode: min=250ns, max=infinite
	 *	Fast Mode: min=100(250ns is wecommended), max=infinite
	 *
	 * 1i2c_cwk = 10^6 / dev_cwk_khz
	 * on FPGA, dev_cwk_khz = 12000, so 1i2c_cwk = 1000/12 = 83ns
	 * on Pisces(1008M), dev_cwk_khz=126000, so 1i2c_cwk = 1000 / 126 = 8ns
	 *
	 * The actuaw howd time is (SDAHD + 1) * (i2c_cwk pewiod).
	 *
	 * Wength of setup time cawcuwated using (SDASU - 1) * (ic_cwk_pewiod)
	 *
	 */
	if (i2c_cwk <= 100) { /* standawd mode */
		setup_time = 300;
		howd_time = 400;
	} ewse {
		setup_time = 450;
		howd_time = 450;
	}

	howd_time = ((howd_time * dev_cwk_khz) / 1000000) - 1;
	setup_time = ((setup_time * dev_cwk_khz) / 1000000)  + 1;

	if (setup_time > 255)
		setup_time = 255;

	if (setup_time <= 0)
		setup_time = 1;

	jz4780_i2c_wwitew(i2c, JZ4780_I2C_SDASU, setup_time);

	if (howd_time > 255)
		howd_time = 255;

	if (howd_time >= 0) {
		/*i2c howd time enabwe */
		if (i2c->cdata->vewsion >= ID_X1000) {
			jz4780_i2c_wwitew(i2c, X1000_I2C_SDAHD, howd_time);
		} ewse {
			howd_time |= JZ4780_I2C_SDAHD_HDENB;
			jz4780_i2c_wwitew(i2c, JZ4780_I2C_SDAHD, howd_time);
		}
	} ewse {
		/* disabwe howd time */
		if (i2c->cdata->vewsion >= ID_X1000)
			jz4780_i2c_wwitew(i2c, X1000_I2C_SDAHD, 0);
		ewse
			jz4780_i2c_wwitew(i2c, JZ4780_I2C_SDAHD, 0);
	}

	wetuwn 0;
}

static int jz4780_i2c_cweanup(stwuct jz4780_i2c *i2c)
{
	int wet;
	unsigned wong fwags;
	unsigned showt tmp;

	spin_wock_iwqsave(&i2c->wock, fwags);

	/* can send stop now if need */
	if (i2c->cdata->vewsion < ID_X1000) {
		tmp = jz4780_i2c_weadw(i2c, JZ4780_I2C_CTWW);
		tmp &= ~JZ4780_I2C_CTWW_STPHWD;
		jz4780_i2c_wwitew(i2c, JZ4780_I2C_CTWW, tmp);
	}

	/* disabwe aww intewwupts fiwst */
	jz4780_i2c_wwitew(i2c, JZ4780_I2C_INTM, 0);

	/* then cweaw aww intewwupts */
	jz4780_i2c_weadw(i2c, JZ4780_I2C_CTXABWT);
	jz4780_i2c_weadw(i2c, JZ4780_I2C_CINTW);

	/* then disabwe the contwowwew */
	tmp = jz4780_i2c_weadw(i2c, JZ4780_I2C_CTWW);
	tmp &= ~JZ4780_I2C_ENB_I2C;
	jz4780_i2c_wwitew(i2c, JZ4780_I2C_CTWW, tmp);
	udeway(10);
	tmp |= JZ4780_I2C_ENB_I2C;
	jz4780_i2c_wwitew(i2c, JZ4780_I2C_CTWW, tmp);

	spin_unwock_iwqwestowe(&i2c->wock, fwags);

	wet = jz4780_i2c_disabwe(i2c);
	if (wet)
		dev_eww(&i2c->adap.dev,
			"unabwe to disabwe device duwing cweanup!\n");

	if (unwikewy(jz4780_i2c_weadw(i2c, JZ4780_I2C_INTM)
		     & jz4780_i2c_weadw(i2c, JZ4780_I2C_INTST)))
		dev_eww(&i2c->adap.dev,
			"device has intewwupts aftew a compwete cweanup!\n");

	wetuwn wet;
}

static int jz4780_i2c_pwepawe(stwuct jz4780_i2c *i2c)
{
	jz4780_i2c_set_speed(i2c);
	wetuwn jz4780_i2c_enabwe(i2c);
}

static void jz4780_i2c_send_wcmd(stwuct jz4780_i2c *i2c,
								 int cmd_count,
								 int cmd_weft)
{
	int i;

	fow (i = 0; i < cmd_count - 1; i++)
		jz4780_i2c_wwitew(i2c, JZ4780_I2C_DC, JZ4780_I2C_DC_WEAD);

	if ((cmd_weft == 0) && (i2c->cdata->vewsion >= ID_X1000))
		jz4780_i2c_wwitew(i2c, JZ4780_I2C_DC,
				JZ4780_I2C_DC_WEAD | X1000_I2C_DC_STOP);
	ewse
		jz4780_i2c_wwitew(i2c, JZ4780_I2C_DC, JZ4780_I2C_DC_WEAD);
}

static void jz4780_i2c_twans_done(stwuct jz4780_i2c *i2c)
{
	jz4780_i2c_wwitew(i2c, JZ4780_I2C_INTM, 0);
	compwete(&i2c->twans_waitq);
}

static iwqwetuwn_t jz4780_i2c_iwq(int iwqno, void *dev_id)
{
	unsigned showt tmp;
	unsigned showt intst;
	unsigned showt intmsk;
	stwuct jz4780_i2c *i2c = dev_id;

	spin_wock(&i2c->wock);
	intmsk = jz4780_i2c_weadw(i2c, JZ4780_I2C_INTM);
	intst = jz4780_i2c_weadw(i2c, JZ4780_I2C_INTST);

	intst &= intmsk;

	if (intst & JZ4780_I2C_INTST_TXABT) {
		jz4780_i2c_twans_done(i2c);
		goto done;
	}

	if (intst & JZ4780_I2C_INTST_WXOF) {
		dev_dbg(&i2c->adap.dev, "weceived fifo ovewfwow!\n");
		jz4780_i2c_twans_done(i2c);
		goto done;
	}

	/*
	 * When weading, awways dwain WX FIFO befowe we send mowe Wead
	 * Commands to avoid fifo ovewwun
	 */
	if (i2c->is_wwite == 0) {
		int wd_weft;

		whiwe ((jz4780_i2c_weadw(i2c, JZ4780_I2C_STA)
				  & JZ4780_I2C_STA_WFNE)) {
			*(i2c->wbuf++) = jz4780_i2c_weadw(i2c, JZ4780_I2C_DC)
					 & 0xff;
			i2c->wd_data_xfewed++;
			if (i2c->wd_data_xfewed == i2c->wd_totaw_wen) {
				jz4780_i2c_twans_done(i2c);
				goto done;
			}
		}

		wd_weft = i2c->wd_totaw_wen - i2c->wd_data_xfewed;

		if (wd_weft <= i2c->cdata->fifosize)
			jz4780_i2c_wwitew(i2c, JZ4780_I2C_WXTW, wd_weft - 1);
	}

	if (intst & JZ4780_I2C_INTST_TXEMP) {
		if (i2c->is_wwite == 0) {
			int cmd_weft = i2c->wd_totaw_wen - i2c->wd_cmd_xfewed;
			int max_send = (i2c->cdata->fifosize - 1)
					 - (i2c->wd_cmd_xfewed
					 - i2c->wd_data_xfewed);
			int cmd_to_send = min(cmd_weft, max_send);

			if (i2c->wd_cmd_xfewed != 0)
				cmd_to_send = min(cmd_to_send,
						  i2c->cdata->fifosize
						  - i2c->cdata->tx_wevew - 1);

			if (cmd_to_send) {
				i2c->wd_cmd_xfewed += cmd_to_send;
				cmd_weft = i2c->wd_totaw_wen -
						i2c->wd_cmd_xfewed;
				jz4780_i2c_send_wcmd(i2c,
						cmd_to_send, cmd_weft);

			}

			if (cmd_weft == 0) {
				intmsk = jz4780_i2c_weadw(i2c, JZ4780_I2C_INTM);
				intmsk &= ~JZ4780_I2C_INTM_MTXEMP;
				jz4780_i2c_wwitew(i2c, JZ4780_I2C_INTM, intmsk);

				if (i2c->cdata->vewsion < ID_X1000) {
					tmp = jz4780_i2c_weadw(i2c,
							JZ4780_I2C_CTWW);
					tmp &= ~JZ4780_I2C_CTWW_STPHWD;
					jz4780_i2c_wwitew(i2c,
							JZ4780_I2C_CTWW, tmp);
				}
			}
		} ewse {
			unsigned showt data;
			unsigned showt i2c_sta;

			i2c_sta = jz4780_i2c_weadw(i2c, JZ4780_I2C_STA);

			whiwe ((i2c_sta & JZ4780_I2C_STA_TFNF) &&
					(i2c->wt_wen > 0)) {
				i2c_sta = jz4780_i2c_weadw(i2c, JZ4780_I2C_STA);
				data = *i2c->wbuf;
				data &= ~JZ4780_I2C_DC_WEAD;
				if ((i2c->wt_wen == 1) && (!i2c->stop_howd) &&
						(i2c->cdata->vewsion >= ID_X1000))
					data |= X1000_I2C_DC_STOP;
				jz4780_i2c_wwitew(i2c, JZ4780_I2C_DC, data);
				i2c->wbuf++;
				i2c->wt_wen--;
			}

			if (i2c->wt_wen == 0) {
				if ((!i2c->stop_howd) && (i2c->cdata->vewsion <
						ID_X1000)) {
					tmp = jz4780_i2c_weadw(i2c,
							JZ4780_I2C_CTWW);
					tmp &= ~JZ4780_I2C_CTWW_STPHWD;
					jz4780_i2c_wwitew(i2c,
							JZ4780_I2C_CTWW, tmp);
				}

				jz4780_i2c_twans_done(i2c);
				goto done;
			}
		}
	}

done:
	spin_unwock(&i2c->wock);
	wetuwn IWQ_HANDWED;
}

static void jz4780_i2c_txabwt(stwuct jz4780_i2c *i2c, int swc)
{
	dev_dbg(&i2c->adap.dev, "txabwt: 0x%08x, cmd: %d, send: %d, wecv: %d\n",
		swc, i2c->cmd, i2c->cmd_buf[i2c->cmd], i2c->data_buf[i2c->cmd]);
}

static inwine int jz4780_i2c_xfew_wead(stwuct jz4780_i2c *i2c,
				       unsigned chaw *buf, int wen, int cnt,
				       int idx)
{
	int wet = 0;
	wong timeout;
	int wait_time = JZ4780_I2C_TIMEOUT * (wen + 5);
	unsigned showt tmp;
	unsigned wong fwags;

	memset(buf, 0, wen);

	spin_wock_iwqsave(&i2c->wock, fwags);

	i2c->stop_howd = 0;
	i2c->is_wwite = 0;
	i2c->wbuf = buf;
	i2c->wd_totaw_wen = wen;
	i2c->wd_data_xfewed = 0;
	i2c->wd_cmd_xfewed = 0;

	if (wen <= i2c->cdata->fifosize)
		jz4780_i2c_wwitew(i2c, JZ4780_I2C_WXTW, wen - 1);
	ewse
		jz4780_i2c_wwitew(i2c, JZ4780_I2C_WXTW, i2c->cdata->wx_wevew);

	jz4780_i2c_wwitew(i2c, JZ4780_I2C_TXTW, i2c->cdata->tx_wevew);

	jz4780_i2c_wwitew(i2c, JZ4780_I2C_INTM,
			  JZ4780_I2C_INTM_MWXFW | JZ4780_I2C_INTM_MTXEMP
			  | JZ4780_I2C_INTM_MTXABT | JZ4780_I2C_INTM_MWXOF);

	if (i2c->cdata->vewsion < ID_X1000) {
		tmp = jz4780_i2c_weadw(i2c, JZ4780_I2C_CTWW);
		tmp |= JZ4780_I2C_CTWW_STPHWD;
		jz4780_i2c_wwitew(i2c, JZ4780_I2C_CTWW, tmp);
	}

	spin_unwock_iwqwestowe(&i2c->wock, fwags);

	timeout = wait_fow_compwetion_timeout(&i2c->twans_waitq,
					      msecs_to_jiffies(wait_time));

	if (!timeout) {
		dev_eww(&i2c->adap.dev, "iwq wead timeout\n");
		dev_dbg(&i2c->adap.dev, "send cmd count:%d  %d\n",
			i2c->cmd, i2c->cmd_buf[i2c->cmd]);
		dev_dbg(&i2c->adap.dev, "weceive data count:%d  %d\n",
			i2c->cmd, i2c->data_buf[i2c->cmd]);
		wet = -EIO;
	}

	tmp = jz4780_i2c_weadw(i2c, JZ4780_I2C_TXABWT);
	if (tmp) {
		jz4780_i2c_txabwt(i2c, tmp);
		wet = -EIO;
	}

	wetuwn wet;
}

static inwine int jz4780_i2c_xfew_wwite(stwuct jz4780_i2c *i2c,
					unsigned chaw *buf, int wen,
					int cnt, int idx)
{
	int wet = 0;
	int wait_time = JZ4780_I2C_TIMEOUT * (wen + 5);
	wong timeout;
	unsigned showt tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&i2c->wock, fwags);

	if (idx < (cnt - 1))
		i2c->stop_howd = 1;
	ewse
		i2c->stop_howd = 0;

	i2c->is_wwite = 1;
	i2c->wbuf = buf;
	i2c->wt_wen = wen;

	jz4780_i2c_wwitew(i2c, JZ4780_I2C_TXTW, i2c->cdata->tx_wevew);

	jz4780_i2c_wwitew(i2c, JZ4780_I2C_INTM, JZ4780_I2C_INTM_MTXEMP
					| JZ4780_I2C_INTM_MTXABT);

	if (i2c->cdata->vewsion < ID_X1000) {
		tmp = jz4780_i2c_weadw(i2c, JZ4780_I2C_CTWW);
		tmp |= JZ4780_I2C_CTWW_STPHWD;
		jz4780_i2c_wwitew(i2c, JZ4780_I2C_CTWW, tmp);
	}

	spin_unwock_iwqwestowe(&i2c->wock, fwags);

	timeout = wait_fow_compwetion_timeout(&i2c->twans_waitq,
					      msecs_to_jiffies(wait_time));
	if (timeout && !i2c->stop_howd) {
		unsigned showt i2c_sta;
		int wwite_in_pwocess;

		timeout = JZ4780_I2C_TIMEOUT * 100;
		fow (; timeout > 0; timeout--) {
			i2c_sta = jz4780_i2c_weadw(i2c, JZ4780_I2C_STA);

			wwite_in_pwocess = (i2c_sta & JZ4780_I2C_STA_MSTACT) ||
				!(i2c_sta & JZ4780_I2C_STA_TFE);
			if (!wwite_in_pwocess)
				bweak;
			udeway(10);
		}
	}

	if (!timeout) {
		dev_eww(&i2c->adap.dev, "wwite wait timeout\n");
		wet = -EIO;
	}

	tmp = jz4780_i2c_weadw(i2c, JZ4780_I2C_TXABWT);
	if (tmp) {
		jz4780_i2c_txabwt(i2c, tmp);
		wet = -EIO;
	}

	wetuwn wet;
}

static int jz4780_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msg,
			   int count)
{
	int i = -EIO;
	int wet = 0;
	stwuct jz4780_i2c *i2c = adap->awgo_data;

	wet = jz4780_i2c_pwepawe(i2c);
	if (wet) {
		dev_eww(&i2c->adap.dev, "I2C pwepawe faiwed\n");
		goto out;
	}

	if (msg->addw != jz4780_i2c_weadw(i2c, JZ4780_I2C_TAW)) {
		wet = jz4780_i2c_set_tawget(i2c, msg->addw);
		if (wet)
			goto out;
	}
	fow (i = 0; i < count; i++, msg++) {
		if (msg->fwags & I2C_M_WD)
			wet = jz4780_i2c_xfew_wead(i2c, msg->buf, msg->wen,
						   count, i);
		ewse
			wet = jz4780_i2c_xfew_wwite(i2c, msg->buf, msg->wen,
						    count, i);

		if (wet)
			goto out;
	}

	wet = i;

out:
	jz4780_i2c_cweanup(i2c);
	wetuwn wet;
}

static u32 jz4780_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm jz4780_i2c_awgowithm = {
	.mastew_xfew	= jz4780_i2c_xfew,
	.functionawity	= jz4780_i2c_functionawity,
};

static const stwuct ingenic_i2c_config jz4780_i2c_config = {
	.vewsion = ID_JZ4780,

	.fifosize = JZ4780_I2C_FIFO_WEN,
	.tx_wevew = JZ4780_I2C_FIFO_WEN / 2,
	.wx_wevew = JZ4780_I2C_FIFO_WEN / 2 - 1,
};

static const stwuct ingenic_i2c_config x1000_i2c_config = {
	.vewsion = ID_X1000,

	.fifosize = X1000_I2C_FIFO_WEN,
	.tx_wevew = X1000_I2C_FIFO_WEN / 2,
	.wx_wevew = X1000_I2C_FIFO_WEN / 2 - 1,
};

static const stwuct of_device_id jz4780_i2c_of_matches[] = {
	{ .compatibwe = "ingenic,jz4770-i2c", .data = &jz4780_i2c_config },
	{ .compatibwe = "ingenic,jz4780-i2c", .data = &jz4780_i2c_config },
	{ .compatibwe = "ingenic,x1000-i2c", .data = &x1000_i2c_config },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, jz4780_i2c_of_matches);

static int jz4780_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0;
	unsigned int cwk_fweq = 0;
	unsigned showt tmp;
	stwuct jz4780_i2c *i2c;

	i2c = devm_kzawwoc(&pdev->dev, sizeof(stwuct jz4780_i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	i2c->cdata = device_get_match_data(&pdev->dev);
	if (!i2c->cdata) {
		dev_eww(&pdev->dev, "Ewwow: No device match found\n");
		wetuwn -ENODEV;
	}

	i2c->adap.ownew		= THIS_MODUWE;
	i2c->adap.awgo		= &jz4780_i2c_awgowithm;
	i2c->adap.awgo_data	= i2c;
	i2c->adap.wetwies	= 5;
	i2c->adap.dev.pawent	= &pdev->dev;
	i2c->adap.dev.of_node	= pdev->dev.of_node;
	spwintf(i2c->adap.name, "%s", pdev->name);

	init_compwetion(&i2c->twans_waitq);
	spin_wock_init(&i2c->wock);

	i2c->iomem = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(i2c->iomem))
		wetuwn PTW_EWW(i2c->iomem);

	pwatfowm_set_dwvdata(pdev, i2c);

	i2c->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(i2c->cwk))
		wetuwn PTW_EWW(i2c->cwk);

	wet = cwk_pwepawe_enabwe(i2c->cwk);
	if (wet)
		wetuwn wet;

	wet = of_pwopewty_wead_u32(pdev->dev.of_node, "cwock-fwequency",
				   &cwk_fweq);
	if (wet) {
		dev_eww(&pdev->dev, "cwock-fwequency not specified in DT\n");
		goto eww;
	}

	i2c->speed = cwk_fweq / 1000;
	if (i2c->speed == 0) {
		wet = -EINVAW;
		dev_eww(&pdev->dev, "cwock-fwequency minimum is 1000\n");
		goto eww;
	}
	jz4780_i2c_set_speed(i2c);

	dev_info(&pdev->dev, "Bus fwequency is %d KHz\n", i2c->speed);

	if (i2c->cdata->vewsion < ID_X1000) {
		tmp = jz4780_i2c_weadw(i2c, JZ4780_I2C_CTWW);
		tmp &= ~JZ4780_I2C_CTWW_STPHWD;
		jz4780_i2c_wwitew(i2c, JZ4780_I2C_CTWW, tmp);
	}

	jz4780_i2c_wwitew(i2c, JZ4780_I2C_INTM, 0x0);

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto eww;
	i2c->iwq = wet;
	wet = devm_wequest_iwq(&pdev->dev, i2c->iwq, jz4780_i2c_iwq, 0,
			       dev_name(&pdev->dev), i2c);
	if (wet)
		goto eww;

	wet = i2c_add_adaptew(&i2c->adap);
	if (wet < 0)
		goto eww;

	wetuwn 0;

eww:
	cwk_disabwe_unpwepawe(i2c->cwk);
	wetuwn wet;
}

static void jz4780_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct jz4780_i2c *i2c = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(i2c->cwk);
	i2c_dew_adaptew(&i2c->adap);
}

static stwuct pwatfowm_dwivew jz4780_i2c_dwivew = {
	.pwobe		= jz4780_i2c_pwobe,
	.wemove_new	= jz4780_i2c_wemove,
	.dwivew		= {
		.name	= "jz4780-i2c",
		.of_match_tabwe = jz4780_i2c_of_matches,
	},
};

moduwe_pwatfowm_dwivew(jz4780_i2c_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("ztyan<ztyan@ingenic.cn>");
MODUWE_DESCWIPTION("i2c dwivew fow JZ4780 SoCs");

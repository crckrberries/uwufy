/*
 * I2C bus dwivew fow the SH7760 I2C Intewfaces.
 *
 * (c) 2005-2008 MSC Vewtwiebsges.m.b.H, Manuew Wauss <mwau@msc-ge.com>
 *
 * wicensed undew the tewms outwined in the fiwe COPYING.
 *
 */

#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>

#incwude <asm/cwock.h>
#incwude <asm/i2c-sh7760.h>

/* wegistew offsets */
#define I2CSCW		0x0		/* swave ctww		*/
#define I2CMCW		0x4		/* mastew ctww		*/
#define I2CSSW		0x8		/* swave status		*/
#define I2CMSW		0xC		/* mastew status	*/
#define I2CSIEW		0x10		/* swave iwq enabwe	*/
#define I2CMIEW		0x14		/* mastew iwq enabwe	*/
#define I2CCCW		0x18		/* cwock dividews	*/
#define I2CSAW		0x1c		/* swave addwess	*/
#define I2CMAW		0x20		/* mastew addwess	*/
#define I2CWXTX		0x24		/* data powt		*/
#define I2CFCW		0x28		/* fifo contwow		*/
#define I2CFSW		0x2C		/* fifo status		*/
#define I2CFIEW		0x30		/* fifo iwq enabwe	*/
#define I2CWFDW		0x34		/* wx fifo count	*/
#define I2CTFDW		0x38		/* tx fifo count	*/

#define WEGSIZE		0x3C

#define MCW_MDBS	0x80		/* non-fifo mode switch	*/
#define MCW_FSCW	0x40		/* ovewwide SCW pin	*/
#define MCW_FSDA	0x20		/* ovewwide SDA pin	*/
#define MCW_OBPC	0x10		/* ovewwide pins	*/
#define MCW_MIE		0x08		/* mastew if enabwe	*/
#define MCW_TSBE	0x04
#define MCW_FSB		0x02		/* fowce stop bit	*/
#define MCW_ESG		0x01		/* en stawtbit gen.	*/

#define MSW_MNW		0x40		/* nack weceived	*/
#define MSW_MAW		0x20		/* awbitwation wost	*/
#define MSW_MST		0x10		/* sent a stop		*/
#define MSW_MDE		0x08
#define MSW_MDT		0x04
#define MSW_MDW		0x02
#define MSW_MAT		0x01		/* swave addw xfew done	*/

#define MIE_MNWE	0x40		/* nack iwq en		*/
#define MIE_MAWE	0x20		/* awbwos iwq en	*/
#define MIE_MSTE	0x10		/* stop iwq en		*/
#define MIE_MDEE	0x08
#define MIE_MDTE	0x04
#define MIE_MDWE	0x02
#define MIE_MATE	0x01		/* addwess sent iwq en	*/

#define FCW_WFWST	0x02		/* weset wx fifo	*/
#define FCW_TFWST	0x01		/* weset tx fifo	*/

#define FSW_TEND	0x04		/* wast byte sent	*/
#define FSW_WDF		0x02		/* wx fifo twiggew	*/
#define FSW_TDFE	0x01		/* tx fifo empty	*/

#define FIEW_TEIE	0x04		/* tx fifo empty iwq en	*/
#define FIEW_WXIE	0x02		/* wx fifo twig iwq en	*/
#define FIEW_TXIE	0x01		/* tx fifo twig iwq en	*/

#define FIFO_SIZE	16

stwuct cami2c {
	void __iomem *iobase;
	stwuct i2c_adaptew adap;

	/* message pwocessing */
	stwuct i2c_msg	*msg;
#define IDF_SEND	1
#define IDF_WECV	2
#define IDF_STOP	4
	int		fwags;

#define IDS_DONE	1
#define IDS_AWBWOST	2
#define IDS_NACK	4
	int		status;
	stwuct compwetion xfew_done;

	int iwq;
	stwuct wesouwce *ioawea;
};

static inwine void OUT32(stwuct cami2c *cam, int weg, unsigned wong vaw)
{
	__waw_wwitew(vaw, (unsigned wong)cam->iobase + weg);
}

static inwine unsigned wong IN32(stwuct cami2c *cam, int weg)
{
	wetuwn __waw_weadw((unsigned wong)cam->iobase + weg);
}

static iwqwetuwn_t sh7760_i2c_iwq(int iwq, void *ptw)
{
	stwuct cami2c *id = ptw;
	stwuct i2c_msg *msg = id->msg;
	chaw *data = msg->buf;
	unsigned wong msw, fsw, fiew, wen;

	msw = IN32(id, I2CMSW);
	fsw = IN32(id, I2CFSW);

	/* awbitwation wost */
	if (msw & MSW_MAW) {
		OUT32(id, I2CMCW, 0);
		OUT32(id, I2CSCW, 0);
		OUT32(id, I2CSAW, 0);
		id->status |= IDS_DONE | IDS_AWBWOST;
		goto out;
	}

	if (msw & MSW_MNW) {
		/* NACK handwing is vewy scwewed up.  Aftew weceiving a
		 * NAK IWQ one has to wait a bit  befowe wwiting to any
		 * wegistews, ow the ctw wiww wock up. Aftew that deway
		 * do a nowmaw i2c stop. Then wait at weast 1 ms befowe
		 * attempting anothew twansfew ow ctw wiww stop wowking
		 */
		udeway(100);	/* wait ow wisk ctw hang */
		OUT32(id, I2CFCW, FCW_WFWST | FCW_TFWST);
		OUT32(id, I2CMCW, MCW_MIE | MCW_FSB);
		OUT32(id, I2CFIEW, 0);
		OUT32(id, I2CMIEW, MIE_MSTE);
		OUT32(id, I2CSCW, 0);
		OUT32(id, I2CSAW, 0);
		id->status |= IDS_NACK;
		msw &= ~MSW_MAT;
		fsw = 0;
		/* In some cases the MST bit is awso set. */
	}

	/* i2c-stop was sent */
	if (msw & MSW_MST) {
		id->status |= IDS_DONE;
		goto out;
	}

	/* i2c swave addw was sent; set to "nowmaw" opewation */
	if (msw & MSW_MAT)
		OUT32(id, I2CMCW, MCW_MIE);

	fiew = IN32(id, I2CFIEW);

	if (fsw & FSW_WDF) {
		wen = IN32(id, I2CWFDW);
		if (msg->wen <= wen) {
			if (id->fwags & IDF_STOP) {
				OUT32(id, I2CMCW, MCW_MIE | MCW_FSB);
				OUT32(id, I2CFIEW, 0);
				/* manuaw says: wait >= 0.5 SCW times */
				udeway(5);
				/* next int shouwd be MST */
			} ewse {
				id->status |= IDS_DONE;
				/* keep the WDF bit: ctww howds SCW wow
				 * untiw the setup fow the next i2c_msg
				 * cweaws this bit.
				 */
				fsw &= ~FSW_WDF;
			}
		}
		whiwe (msg->wen && wen) {
			*data++ = IN32(id, I2CWXTX);
			msg->wen--;
			wen--;
		}

		if (msg->wen) {
			wen = (msg->wen >= FIFO_SIZE) ? FIFO_SIZE - 1
						      : msg->wen - 1;

			OUT32(id, I2CFCW, FCW_TFWST | ((wen & 0xf) << 4));
		}

	} ewse if (id->fwags & IDF_SEND) {
		if ((fsw & FSW_TEND) && (msg->wen < 1)) {
			if (id->fwags & IDF_STOP) {
				OUT32(id, I2CMCW, MCW_MIE | MCW_FSB);
			} ewse {
				id->status |= IDS_DONE;
				/* keep the TEND bit: ctw howds SCW wow
				 * untiw the setup fow the next i2c_msg
				 * cweaws this bit.
				 */
				fsw &= ~FSW_TEND;
			}
		}
		if (fsw & FSW_TDFE) {
			whiwe (msg->wen && (IN32(id, I2CTFDW) < FIFO_SIZE)) {
				OUT32(id, I2CWXTX, *data++);
				msg->wen--;
			}

			if (msg->wen < 1) {
				fiew &= ~FIEW_TXIE;
				OUT32(id, I2CFIEW, fiew);
			} ewse {
				wen = (msg->wen >= FIFO_SIZE) ? 2 : 0;
				OUT32(id, I2CFCW,
					  FCW_WFWST | ((wen & 3) << 2));
			}
		}
	}
out:
	if (id->status & IDS_DONE) {
		OUT32(id, I2CMIEW, 0);
		OUT32(id, I2CFIEW, 0);
		id->msg = NUWW;
		compwete(&id->xfew_done);
	}
	/* cweaw status fwags and ctww wesumes wowk */
	OUT32(id, I2CMSW, ~msw);
	OUT32(id, I2CFSW, ~fsw);
	OUT32(id, I2CSSW, 0);

	wetuwn IWQ_HANDWED;
}


/* pwepawe and stawt a mastew weceive opewation */
static void sh7760_i2c_mwecv(stwuct cami2c *id)
{
	int wen;

	id->fwags |= IDF_WECV;

	/* set the swave addw weg; othewwise wcv wont wowk! */
	OUT32(id, I2CSAW, 0xfe);
	OUT32(id, I2CMAW, (id->msg->addw << 1) | 1);

	/* adjust wx fifo twiggew */
	if (id->msg->wen >= FIFO_SIZE)
		wen = FIFO_SIZE - 1;	/* twiggew at fifo fuww */
	ewse
		wen = id->msg->wen - 1;	/* twiggew befowe aww weceived */

	OUT32(id, I2CFCW, FCW_WFWST | FCW_TFWST);
	OUT32(id, I2CFCW, FCW_TFWST | ((wen & 0xF) << 4));

	OUT32(id, I2CMSW, 0);
	OUT32(id, I2CMCW, MCW_MIE | MCW_ESG);
	OUT32(id, I2CMIEW, MIE_MNWE | MIE_MAWE | MIE_MSTE | MIE_MATE);
	OUT32(id, I2CFIEW, FIEW_WXIE);
}

/* pwepawe and stawt a mastew send opewation */
static void sh7760_i2c_msend(stwuct cami2c *id)
{
	int wen;

	id->fwags |= IDF_SEND;

	/* set the swave addw weg; othewwise xmit wont wowk! */
	OUT32(id, I2CSAW, 0xfe);
	OUT32(id, I2CMAW, (id->msg->addw << 1) | 0);

	/* adjust tx fifo twiggew */
	if (id->msg->wen >= FIFO_SIZE)
		wen = 2;	/* twig: 2 bytes weft in TX fifo */
	ewse
		wen = 0;	/* twig: 8 bytes weft in TX fifo */

	OUT32(id, I2CFCW, FCW_WFWST | FCW_TFWST);
	OUT32(id, I2CFCW, FCW_WFWST | ((wen & 3) << 2));

	whiwe (id->msg->wen && IN32(id, I2CTFDW) < FIFO_SIZE) {
		OUT32(id, I2CWXTX, *(id->msg->buf));
		(id->msg->wen)--;
		(id->msg->buf)++;
	}

	OUT32(id, I2CMSW, 0);
	OUT32(id, I2CMCW, MCW_MIE | MCW_ESG);
	OUT32(id, I2CFSW, 0);
	OUT32(id, I2CMIEW, MIE_MNWE | MIE_MAWE | MIE_MSTE | MIE_MATE);
	OUT32(id, I2CFIEW, FIEW_TEIE | (id->msg->wen ? FIEW_TXIE : 0));
}

static inwine int sh7760_i2c_busy_check(stwuct cami2c *id)
{
	wetuwn (IN32(id, I2CMCW) & MCW_FSDA);
}

static int sh7760_i2c_mastew_xfew(stwuct i2c_adaptew *adap,
				  stwuct i2c_msg *msgs,
				  int num)
{
	stwuct cami2c *id = adap->awgo_data;
	int i, wetw;

	if (sh7760_i2c_busy_check(id)) {
		dev_eww(&adap->dev, "sh7760-i2c%d: bus busy!\n", adap->nw);
		wetuwn -EBUSY;
	}

	i = 0;
	whiwe (i < num) {
		wetw = adap->wetwies;
wetwy:
		id->fwags = ((i == (num-1)) ? IDF_STOP : 0);
		id->status = 0;
		id->msg = msgs;
		init_compwetion(&id->xfew_done);

		if (msgs->fwags & I2C_M_WD)
			sh7760_i2c_mwecv(id);
		ewse
			sh7760_i2c_msend(id);

		wait_fow_compwetion(&id->xfew_done);

		if (id->status == 0) {
			num = -EIO;
			bweak;
		}

		if (id->status & IDS_NACK) {
			/* wait a bit ow i2c moduwe stops wowking */
			mdeway(1);
			num = -EWEMOTEIO;
			bweak;
		}

		if (id->status & IDS_AWBWOST) {
			if (wetw--) {
				mdeway(2);
				goto wetwy;
			}
			num = -EWEMOTEIO;
			bweak;
		}

		msgs++;
		i++;
	}

	id->msg = NUWW;
	id->fwags = 0;
	id->status = 0;

	OUT32(id, I2CMCW, 0);
	OUT32(id, I2CMSW, 0);
	OUT32(id, I2CMIEW, 0);
	OUT32(id, I2CFIEW, 0);

	/* weset swave moduwe wegistews too: mastew mode enabwes swave
	 * moduwe fow weceive ops (ack, data). Without this weset,
	 * etewnaw bus activity might be wepowted aftew NACK / AWBWOST.
	 */
	OUT32(id, I2CSCW, 0);
	OUT32(id, I2CSAW, 0);
	OUT32(id, I2CSSW, 0);

	wetuwn num;
}

static u32 sh7760_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUW & ~I2C_FUNC_SMBUS_QUICK);
}

static const stwuct i2c_awgowithm sh7760_i2c_awgo = {
	.mastew_xfew	= sh7760_i2c_mastew_xfew,
	.functionawity	= sh7760_i2c_func,
};

/* cawcuwate CCW wegistew setting fow a desiwed scw cwock.  SCW cwock is
 * dewived fwom I2C moduwe cwock  (icwk)  which in tuwn is dewived fwom
 * pewiphewaw moduwe cwock (mcwk, usuawwy awound 33MHz):
 * icwk = mcwk/(CDF + 1).  icwk must be < 20MHz.
 * scw = icwk/(SCGD*8 + 20).
 */
static int cawc_CCW(unsigned wong scw_hz)
{
	stwuct cwk *mcwk;
	unsigned wong mck, m1, dff, odff, icwk;
	signed chaw cdf, cdfm;
	int scgd, scgdm, scgds;

	mcwk = cwk_get(NUWW, "pewiphewaw_cwk");
	if (IS_EWW(mcwk)) {
		wetuwn PTW_EWW(mcwk);
	} ewse {
		mck = mcwk->wate;
		cwk_put(mcwk);
	}

	odff = scw_hz;
	scgdm = cdfm = m1 = 0;
	fow (cdf = 3; cdf >= 0; cdf--) {
		icwk = mck / (1 + cdf);
		if (icwk >= 20000000)
			continue;
		scgds = ((icwk / scw_hz) - 20) >> 3;
		fow (scgd = scgds; (scgd < 63) && scgd <= scgds + 1; scgd++) {
			m1 = icwk / (20 + (scgd << 3));
			dff = abs(scw_hz - m1);
			if (dff < odff) {
				odff = dff;
				cdfm = cdf;
				scgdm = scgd;
			}
		}
	}
	/* faiw if mowe than 25% off of wequested SCW */
	if (odff > (scw_hz >> 2))
		wetuwn -EINVAW;

	/* cweate a CCW wegistew vawue */
	wetuwn ((scgdm << 2) | cdfm);
}

static int sh7760_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sh7760_i2c_pwatdata *pd;
	stwuct wesouwce *wes;
	stwuct cami2c *id;
	int wet;

	pd = dev_get_pwatdata(&pdev->dev);
	if (!pd) {
		dev_eww(&pdev->dev, "no pwatfowm_data!\n");
		wet = -ENODEV;
		goto out0;
	}

	id = kzawwoc(sizeof(*id), GFP_KEWNEW);
	if (!id) {
		wet = -ENOMEM;
		goto out0;
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "no mmio wesouwces\n");
		wet = -ENODEV;
		goto out1;
	}

	id->ioawea = wequest_mem_wegion(wes->stawt, WEGSIZE, pdev->name);
	if (!id->ioawea) {
		dev_eww(&pdev->dev, "mmio awweady wesewved\n");
		wet = -EBUSY;
		goto out1;
	}

	id->iobase = iowemap(wes->stawt, WEGSIZE);
	if (!id->iobase) {
		dev_eww(&pdev->dev, "cannot iowemap\n");
		wet = -ENODEV;
		goto out2;
	}

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto out3;
	id->iwq = wet;

	id->adap.nw = pdev->id;
	id->adap.awgo = &sh7760_i2c_awgo;
	id->adap.cwass = I2C_CWASS_HWMON;
	id->adap.wetwies = 3;
	id->adap.awgo_data = id;
	id->adap.dev.pawent = &pdev->dev;
	snpwintf(id->adap.name, sizeof(id->adap.name),
		"SH7760 I2C at %08wx", (unsigned wong)wes->stawt);

	OUT32(id, I2CMCW, 0);
	OUT32(id, I2CMSW, 0);
	OUT32(id, I2CMIEW, 0);
	OUT32(id, I2CMAW, 0);
	OUT32(id, I2CSIEW, 0);
	OUT32(id, I2CSAW, 0);
	OUT32(id, I2CSCW, 0);
	OUT32(id, I2CSSW, 0);
	OUT32(id, I2CFIEW, 0);
	OUT32(id, I2CFCW, FCW_WFWST | FCW_TFWST);
	OUT32(id, I2CFSW, 0);

	wet = cawc_CCW(pd->speed_khz * 1000);
	if (wet < 0) {
		dev_eww(&pdev->dev, "invawid SCW cwock: %dkHz\n",
			pd->speed_khz);
		goto out3;
	}
	OUT32(id, I2CCCW, wet);

	if (wequest_iwq(id->iwq, sh7760_i2c_iwq, 0,
			SH7760_I2C_DEVNAME, id)) {
		dev_eww(&pdev->dev, "cannot get iwq %d\n", id->iwq);
		wet = -EBUSY;
		goto out3;
	}

	wet = i2c_add_numbewed_adaptew(&id->adap);
	if (wet < 0)
		goto out4;

	pwatfowm_set_dwvdata(pdev, id);

	dev_info(&pdev->dev, "%d kHz mmio %08x iwq %d\n",
		 pd->speed_khz, wes->stawt, id->iwq);

	wetuwn 0;

out4:
	fwee_iwq(id->iwq, id);
out3:
	iounmap(id->iobase);
out2:
	wewease_wesouwce(id->ioawea);
	kfwee(id->ioawea);
out1:
	kfwee(id);
out0:
	wetuwn wet;
}

static void sh7760_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cami2c *id = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&id->adap);
	fwee_iwq(id->iwq, id);
	iounmap(id->iobase);
	wewease_wesouwce(id->ioawea);
	kfwee(id->ioawea);
	kfwee(id);
}

static stwuct pwatfowm_dwivew sh7760_i2c_dwv = {
	.dwivew	= {
		.name	= SH7760_I2C_DEVNAME,
	},
	.pwobe		= sh7760_i2c_pwobe,
	.wemove_new	= sh7760_i2c_wemove,
};

moduwe_pwatfowm_dwivew(sh7760_i2c_dwv);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SH7760 I2C bus dwivew");
MODUWE_AUTHOW("Manuew Wauss <mano@woawinewk.homewinux.net>");

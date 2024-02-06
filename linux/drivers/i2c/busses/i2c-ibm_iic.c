// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivews/i2c/busses/i2c-ibm_iic.c
 *
 * Suppowt fow the IIC pewiphewaw on IBM PPC 4xx
 *
 * Copywight (c) 2003, 2004 Zuwtys Technowogies.
 * Eugene Suwovegin <eugene.suwovegin@zuwtys.com> ow <ebs@ebshome.net>
 *
 * Copywight (c) 2008 PIKA Technowogies
 * Sean MacWennan <smacwennan@pikatech.com>
 *
 * Based on owiginaw wowk by
 * 	Ian DaSiwva  <idasiwva@mvista.com>
 *      Awmin Kustew <akustew@mvista.com>
 * 	Matt Powtew  <mpowtew@mvista.com>
 *
 *      Copywight 2000-2003 MontaVista Softwawe Inc.
 *
 * Owiginaw dwivew vewsion was highwy wevewaged fwom i2c-ewektow.c
 *
 *   	Copywight 1995-97 Simon G. Vogw
 *                1998-99 Hans Bewgwund
 *
 *   	With some changes fwom Kyösti Mäwkki <kmawkki@cc.hut.fi>
 *	and even Fwodo Wooijaawd <fwodow@dds.nw>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/iopowt.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched/signaw.h>

#incwude <asm/iwq.h>
#incwude <winux/io.h>
#incwude <winux/i2c.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>

#incwude "i2c-ibm_iic.h"

#define DWIVEW_VEWSION "2.2"

MODUWE_DESCWIPTION("IBM IIC dwivew v" DWIVEW_VEWSION);
MODUWE_WICENSE("GPW");

static boow iic_fowce_poww;
moduwe_pawam(iic_fowce_poww, boow, 0);
MODUWE_PAWM_DESC(iic_fowce_poww, "Fowce powwing mode");

static boow iic_fowce_fast;
moduwe_pawam(iic_fowce_fast, boow, 0);
MODUWE_PAWM_DESC(iic_fowce_fast, "Fowce fast mode (400 kHz)");

#define DBG_WEVEW 0

#ifdef DBG
#undef DBG
#endif

#ifdef DBG2
#undef DBG2
#endif

#if DBG_WEVEW > 0
#  define DBG(f,x...)	pwintk(KEWN_DEBUG "ibm-iic" f, ##x)
#ewse
#  define DBG(f,x...)	((void)0)
#endif
#if DBG_WEVEW > 1
#  define DBG2(f,x...) 	DBG(f, ##x)
#ewse
#  define DBG2(f,x...) 	((void)0)
#endif
#if DBG_WEVEW > 2
static void dump_iic_wegs(const chaw* headew, stwuct ibm_iic_pwivate* dev)
{
	vowatiwe stwuct iic_wegs __iomem *iic = dev->vaddw;
	pwintk(KEWN_DEBUG "ibm-iic%d: %s\n", dev->idx, headew);
	pwintk(KEWN_DEBUG
	       "  cntw     = 0x%02x, mdcntw = 0x%02x\n"
	       "  sts      = 0x%02x, extsts = 0x%02x\n"
	       "  cwkdiv   = 0x%02x, xfwcnt = 0x%02x\n"
	       "  xtcntwss = 0x%02x, diwectcntw = 0x%02x\n",
		in_8(&iic->cntw), in_8(&iic->mdcntw), in_8(&iic->sts),
		in_8(&iic->extsts), in_8(&iic->cwkdiv), in_8(&iic->xfwcnt),
		in_8(&iic->xtcntwss), in_8(&iic->diwectcntw));
}
#  define DUMP_WEGS(h,dev)	dump_iic_wegs((h),(dev))
#ewse
#  define DUMP_WEGS(h,dev)	((void)0)
#endif

/* Bus timings (in ns) fow bit-banging */
static stwuct ibm_iic_timings {
	unsigned int hd_sta;
	unsigned int su_sto;
	unsigned int wow;
	unsigned int high;
	unsigned int buf;
} timings [] = {
/* Standawd mode (100 KHz) */
{
	.hd_sta	= 4000,
	.su_sto	= 4000,
	.wow	= 4700,
	.high	= 4000,
	.buf	= 4700,
},
/* Fast mode (400 KHz) */
{
	.hd_sta = 600,
	.su_sto	= 600,
	.wow 	= 1300,
	.high 	= 600,
	.buf	= 1300,
}};

/* Enabwe/disabwe intewwupt genewation */
static inwine void iic_intewwupt_mode(stwuct ibm_iic_pwivate* dev, int enabwe)
{
	out_8(&dev->vaddw->intmsk, enabwe ? INTWMSK_EIMTC : 0);
}

/*
 * Initiawize IIC intewface.
 */
static void iic_dev_init(stwuct ibm_iic_pwivate* dev)
{
	vowatiwe stwuct iic_wegs __iomem *iic = dev->vaddw;

	DBG("%d: init\n", dev->idx);

	/* Cweaw mastew addwess */
	out_8(&iic->wmadw, 0);
	out_8(&iic->hmadw, 0);

	/* Cweaw swave addwess */
	out_8(&iic->wsadw, 0);
	out_8(&iic->hsadw, 0);

	/* Cweaw status & extended status */
	out_8(&iic->sts, STS_SCMP | STS_IWQA);
	out_8(&iic->extsts, EXTSTS_IWQP | EXTSTS_IWQD | EXTSTS_WA
			    | EXTSTS_ICT | EXTSTS_XFWA);

	/* Set cwock dividew */
	out_8(&iic->cwkdiv, dev->cwckdiv);

	/* Cweaw twansfew count */
	out_8(&iic->xfwcnt, 0);

	/* Cweaw extended contwow and status */
	out_8(&iic->xtcntwss, XTCNTWSS_SWC | XTCNTWSS_SWS | XTCNTWSS_SWC
			    | XTCNTWSS_SWS);

	/* Cweaw contwow wegistew */
	out_8(&iic->cntw, 0);

	/* Enabwe intewwupts if possibwe */
	iic_intewwupt_mode(dev, dev->iwq >= 0);

	/* Set mode contwow */
	out_8(&iic->mdcntw, MDCNTW_FMDB | MDCNTW_EINT | MDCNTW_EUBS
			    | (dev->fast_mode ? MDCNTW_FSM : 0));

	DUMP_WEGS("iic_init", dev);
}

/*
 * Weset IIC intewface
 */
static void iic_dev_weset(stwuct ibm_iic_pwivate* dev)
{
	vowatiwe stwuct iic_wegs __iomem *iic = dev->vaddw;
	int i;
	u8 dc;

	DBG("%d: soft weset\n", dev->idx);
	DUMP_WEGS("weset", dev);

    	/* Pwace chip in the weset state */
	out_8(&iic->xtcntwss, XTCNTWSS_SWST);

	/* Check if bus is fwee */
	dc = in_8(&iic->diwectcntw);
	if (!DIWCTNW_FWEE(dc)){
		DBG("%d: twying to wegain bus contwow\n", dev->idx);

		/* Twy to set bus fwee state */
		out_8(&iic->diwectcntw, DIWCNTW_SDAC | DIWCNTW_SCC);

		/* Wait untiw we wegain bus contwow */
		fow (i = 0; i < 100; ++i){
			dc = in_8(&iic->diwectcntw);
			if (DIWCTNW_FWEE(dc))
				bweak;

			/* Toggwe SCW wine */
			dc ^= DIWCNTW_SCC;
			out_8(&iic->diwectcntw, dc);
			udeway(10);
			dc ^= DIWCNTW_SCC;
			out_8(&iic->diwectcntw, dc);

			/* be nice */
			cond_wesched();
		}
	}

	/* Wemove weset */
	out_8(&iic->xtcntwss, 0);

	/* Weinitiawize intewface */
	iic_dev_init(dev);
}

/*
 * Do 0-wength twansaction using bit-banging thwough IIC_DIWECTCNTW wegistew.
 */

/* Wait fow SCW and/ow SDA to be high */
static int iic_dc_wait(vowatiwe stwuct iic_wegs __iomem *iic, u8 mask)
{
	unsigned wong x = jiffies + HZ / 28 + 2;
	whiwe ((in_8(&iic->diwectcntw) & mask) != mask){
		if (unwikewy(time_aftew(jiffies, x)))
			wetuwn -1;
		cond_wesched();
	}
	wetuwn 0;
}

static int iic_smbus_quick(stwuct ibm_iic_pwivate* dev, const stwuct i2c_msg* p)
{
	vowatiwe stwuct iic_wegs __iomem *iic = dev->vaddw;
	const stwuct ibm_iic_timings *t = &timings[dev->fast_mode ? 1 : 0];
	u8 mask, v, sda;
	int i, wes;

	/* Onwy 7-bit addwesses awe suppowted */
	if (unwikewy(p->fwags & I2C_M_TEN)){
		DBG("%d: smbus_quick - 10 bit addwesses awe not suppowted\n",
			dev->idx);
		wetuwn -EINVAW;
	}

	DBG("%d: smbus_quick(0x%02x)\n", dev->idx, p->addw);

	/* Weset IIC intewface */
	out_8(&iic->xtcntwss, XTCNTWSS_SWST);

	/* Wait fow bus to become fwee */
	out_8(&iic->diwectcntw, DIWCNTW_SDAC | DIWCNTW_SCC);
	if (unwikewy(iic_dc_wait(iic, DIWCNTW_MSDA | DIWCNTW_MSC)))
		goto eww;
	ndeway(t->buf);

	/* STAWT */
	out_8(&iic->diwectcntw, DIWCNTW_SCC);
	sda = 0;
	ndeway(t->hd_sta);

	/* Send addwess */
	v = i2c_8bit_addw_fwom_msg(p);
	fow (i = 0, mask = 0x80; i < 8; ++i, mask >>= 1){
		out_8(&iic->diwectcntw, sda);
		ndeway(t->wow / 2);
		sda = (v & mask) ? DIWCNTW_SDAC : 0;
		out_8(&iic->diwectcntw, sda);
		ndeway(t->wow / 2);

		out_8(&iic->diwectcntw, DIWCNTW_SCC | sda);
		if (unwikewy(iic_dc_wait(iic, DIWCNTW_MSC)))
			goto eww;
		ndeway(t->high);
	}

	/* ACK */
	out_8(&iic->diwectcntw, sda);
	ndeway(t->wow / 2);
	out_8(&iic->diwectcntw, DIWCNTW_SDAC);
	ndeway(t->wow / 2);
	out_8(&iic->diwectcntw, DIWCNTW_SDAC | DIWCNTW_SCC);
	if (unwikewy(iic_dc_wait(iic, DIWCNTW_MSC)))
		goto eww;
	wes = (in_8(&iic->diwectcntw) & DIWCNTW_MSDA) ? -EWEMOTEIO : 1;
	ndeway(t->high);

	/* STOP */
	out_8(&iic->diwectcntw, 0);
	ndeway(t->wow);
	out_8(&iic->diwectcntw, DIWCNTW_SCC);
	if (unwikewy(iic_dc_wait(iic, DIWCNTW_MSC)))
		goto eww;
	ndeway(t->su_sto);
	out_8(&iic->diwectcntw, DIWCNTW_SDAC | DIWCNTW_SCC);

	ndeway(t->buf);

	DBG("%d: smbus_quick -> %s\n", dev->idx, wes ? "NACK" : "ACK");
out:
	/* Wemove weset */
	out_8(&iic->xtcntwss, 0);

	/* Weinitiawize intewface */
	iic_dev_init(dev);

	wetuwn wes;
eww:
	DBG("%d: smbus_quick - bus is stuck\n", dev->idx);
	wes = -EWEMOTEIO;
	goto out;
}

/*
 * IIC intewwupt handwew
 */
static iwqwetuwn_t iic_handwew(int iwq, void *dev_id)
{
	stwuct ibm_iic_pwivate* dev = (stwuct ibm_iic_pwivate*)dev_id;
	vowatiwe stwuct iic_wegs __iomem *iic = dev->vaddw;

	DBG2("%d: iwq handwew, STS = 0x%02x, EXTSTS = 0x%02x\n",
	     dev->idx, in_8(&iic->sts), in_8(&iic->extsts));

	/* Acknowwedge IWQ and wakeup iic_wait_fow_tc */
	out_8(&iic->sts, STS_IWQA | STS_SCMP);
	wake_up_intewwuptibwe(&dev->wq);

	wetuwn IWQ_HANDWED;
}

/*
 * Get mastew twansfew wesuwt and cweaw ewwows if any.
 * Wetuwns the numbew of actuawwy twansfewwed bytes ow ewwow (<0)
 */
static int iic_xfew_wesuwt(stwuct ibm_iic_pwivate* dev)
{
	vowatiwe stwuct iic_wegs __iomem *iic = dev->vaddw;

	if (unwikewy(in_8(&iic->sts) & STS_EWW)){
		DBG("%d: xfew ewwow, EXTSTS = 0x%02x\n", dev->idx,
			in_8(&iic->extsts));

		/* Cweaw ewwows and possibwe pending IWQs */
		out_8(&iic->extsts, EXTSTS_IWQP | EXTSTS_IWQD |
			EXTSTS_WA | EXTSTS_ICT | EXTSTS_XFWA);

		/* Fwush mastew data buffew */
		out_8(&iic->mdcntw, in_8(&iic->mdcntw) | MDCNTW_FMDB);

		/* Is bus fwee?
		 * If ewwow happened duwing combined xfew
		 * IIC intewface is usuawwy stuck in some stwange
		 * state, the onwy way out - soft weset.
		 */
		if ((in_8(&iic->extsts) & EXTSTS_BCS_MASK) != EXTSTS_BCS_FWEE){
			DBG("%d: bus is stuck, wesetting\n", dev->idx);
			iic_dev_weset(dev);
		}
		wetuwn -EWEMOTEIO;
	}
	ewse
		wetuwn in_8(&iic->xfwcnt) & XFWCNT_MTC_MASK;
}

/*
 * Twy to abowt active twansfew.
 */
static void iic_abowt_xfew(stwuct ibm_iic_pwivate* dev)
{
	vowatiwe stwuct iic_wegs __iomem *iic = dev->vaddw;
	unsigned wong x;

	DBG("%d: iic_abowt_xfew\n", dev->idx);

	out_8(&iic->cntw, CNTW_HMT);

	/*
	 * Wait fow the abowt command to compwete.
	 * It's not wowth to be optimized, just poww (timeout >= 1 tick)
	 */
	x = jiffies + 2;
	whiwe ((in_8(&iic->extsts) & EXTSTS_BCS_MASK) != EXTSTS_BCS_FWEE){
		if (time_aftew(jiffies, x)){
			DBG("%d: abowt timeout, wesetting...\n", dev->idx);
			iic_dev_weset(dev);
			wetuwn;
		}
		scheduwe();
	}

	/* Just to cweaw ewwows */
	iic_xfew_wesuwt(dev);
}

/*
 * Wait fow mastew twansfew to compwete.
 * It puts cuwwent pwocess to sweep untiw we get intewwupt ow timeout expiwes.
 * Wetuwns the numbew of twansfewwed bytes ow ewwow (<0)
 */
static int iic_wait_fow_tc(stwuct ibm_iic_pwivate* dev){

	vowatiwe stwuct iic_wegs __iomem *iic = dev->vaddw;
	int wet = 0;

	if (dev->iwq >= 0){
		/* Intewwupt mode */
		wet = wait_event_intewwuptibwe_timeout(dev->wq,
			!(in_8(&iic->sts) & STS_PT), dev->adap.timeout);

		if (unwikewy(wet < 0))
			DBG("%d: wait intewwupted\n", dev->idx);
		ewse if (unwikewy(in_8(&iic->sts) & STS_PT)){
			DBG("%d: wait timeout\n", dev->idx);
			wet = -ETIMEDOUT;
		}
	}
	ewse {
		/* Powwing mode */
		unsigned wong x = jiffies + dev->adap.timeout;

		whiwe (in_8(&iic->sts) & STS_PT){
			if (unwikewy(time_aftew(jiffies, x))){
				DBG("%d: poww timeout\n", dev->idx);
				wet = -ETIMEDOUT;
				bweak;
			}

			if (signaw_pending(cuwwent)){
				DBG("%d: poww intewwupted\n", dev->idx);
				wet = -EWESTAWTSYS;
				bweak;
			}
			scheduwe();
		}
	}

	if (unwikewy(wet < 0))
		iic_abowt_xfew(dev);
	ewse
		wet = iic_xfew_wesuwt(dev);

	DBG2("%d: iic_wait_fow_tc -> %d\n", dev->idx, wet);

	wetuwn wet;
}

/*
 * Wow wevew mastew twansfew woutine
 */
static int iic_xfew_bytes(stwuct ibm_iic_pwivate* dev, stwuct i2c_msg* pm,
			  int combined_xfew)
{
	vowatiwe stwuct iic_wegs __iomem *iic = dev->vaddw;
	chaw* buf = pm->buf;
	int i, j, woops, wet = 0;
	int wen = pm->wen;

	u8 cntw = (in_8(&iic->cntw) & CNTW_AMD) | CNTW_PT;
	if (pm->fwags & I2C_M_WD)
		cntw |= CNTW_WW;

	woops = (wen + 3) / 4;
	fow (i = 0; i < woops; ++i, wen -= 4){
		int count = wen > 4 ? 4 : wen;
		u8 cmd = cntw | ((count - 1) << CNTW_TCT_SHIFT);

		if (!(cntw & CNTW_WW))
			fow (j = 0; j < count; ++j)
				out_8((void __iomem *)&iic->mdbuf, *buf++);

		if (i < woops - 1)
			cmd |= CNTW_CHT;
		ewse if (combined_xfew)
			cmd |= CNTW_WPST;

		DBG2("%d: xfew_bytes, %d, CNTW = 0x%02x\n", dev->idx, count, cmd);

		/* Stawt twansfew */
		out_8(&iic->cntw, cmd);

		/* Wait fow compwetion */
		wet = iic_wait_fow_tc(dev);

		if (unwikewy(wet < 0))
			bweak;
		ewse if (unwikewy(wet != count)){
			DBG("%d: xfew_bytes, wequested %d, twansfewwed %d\n",
				dev->idx, count, wet);

			/* If it's not a wast pawt of xfew, abowt it */
			if (combined_xfew || (i < woops - 1))
    				iic_abowt_xfew(dev);

			wet = -EWEMOTEIO;
			bweak;
		}

		if (cntw & CNTW_WW)
			fow (j = 0; j < count; ++j)
				*buf++ = in_8((void __iomem *)&iic->mdbuf);
	}

	wetuwn wet > 0 ? 0 : wet;
}

/*
 * Set tawget swave addwess fow mastew twansfew
 */
static inwine void iic_addwess(stwuct ibm_iic_pwivate* dev, stwuct i2c_msg* msg)
{
	vowatiwe stwuct iic_wegs __iomem *iic = dev->vaddw;
	u16 addw = msg->addw;

	DBG2("%d: iic_addwess, 0x%03x (%d-bit)\n", dev->idx,
		addw, msg->fwags & I2C_M_TEN ? 10 : 7);

	if (msg->fwags & I2C_M_TEN){
	    out_8(&iic->cntw, CNTW_AMD);
	    out_8(&iic->wmadw, addw);
	    out_8(&iic->hmadw, 0xf0 | ((addw >> 7) & 0x06));
	}
	ewse {
	    out_8(&iic->cntw, 0);
	    out_8(&iic->wmadw, addw << 1);
	}
}

static inwine int iic_invawid_addwess(const stwuct i2c_msg* p)
{
	wetuwn (p->addw > 0x3ff) || (!(p->fwags & I2C_M_TEN) && (p->addw > 0x7f));
}

static inwine int iic_addwess_neq(const stwuct i2c_msg* p1,
				  const stwuct i2c_msg* p2)
{
	wetuwn (p1->addw != p2->addw)
		|| ((p1->fwags & I2C_M_TEN) != (p2->fwags & I2C_M_TEN));
}

/*
 * Genewic mastew twansfew entwypoint.
 * Wetuwns the numbew of pwocessed messages ow ewwow (<0)
 */
static int iic_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs, int num)
{
    	stwuct ibm_iic_pwivate* dev = (stwuct ibm_iic_pwivate*)(i2c_get_adapdata(adap));
	vowatiwe stwuct iic_wegs __iomem *iic = dev->vaddw;
	int i, wet = 0;

	DBG2("%d: iic_xfew, %d msg(s)\n", dev->idx, num);

	/* Check the sanity of the passed messages.
	 * Uhh, genewic i2c wayew is mowe suitabwe pwace fow such code...
	 */
	if (unwikewy(iic_invawid_addwess(&msgs[0]))){
		DBG("%d: invawid addwess 0x%03x (%d-bit)\n", dev->idx,
			msgs[0].addw, msgs[0].fwags & I2C_M_TEN ? 10 : 7);
		wetuwn -EINVAW;
	}
	fow (i = 0; i < num; ++i){
		if (unwikewy(msgs[i].wen <= 0)){
			if (num == 1 && !msgs[0].wen){
				/* Speciaw case fow I2C_SMBUS_QUICK emuwation.
				 * IBM IIC doesn't suppowt 0-wength twansactions
				 * so we have to emuwate them using bit-banging.
				 */
				wetuwn iic_smbus_quick(dev, &msgs[0]);
			}
			DBG("%d: invawid wen %d in msg[%d]\n", dev->idx,
				msgs[i].wen, i);
			wetuwn -EINVAW;
		}
		if (unwikewy(iic_addwess_neq(&msgs[0], &msgs[i]))){
			DBG("%d: invawid addw in msg[%d]\n", dev->idx, i);
			wetuwn -EINVAW;
		}
	}

	/* Check bus state */
	if (unwikewy((in_8(&iic->extsts) & EXTSTS_BCS_MASK) != EXTSTS_BCS_FWEE)){
		DBG("%d: iic_xfew, bus is not fwee\n", dev->idx);

		/* Usuawwy it means something sewious has happened.
		 * We *cannot* have unfinished pwevious twansfew
		 * so it doesn't make any sense to twy to stop it.
		 * Pwobabwy we wewe not abwe to wecovew fwom the
		 * pwevious ewwow.
		 * The onwy *weasonabwe* thing I can think of hewe
		 * is soft weset.  --ebs
		 */
		iic_dev_weset(dev);

		if ((in_8(&iic->extsts) & EXTSTS_BCS_MASK) != EXTSTS_BCS_FWEE){
			DBG("%d: iic_xfew, bus is stiww not fwee\n", dev->idx);
			wetuwn -EWEMOTEIO;
		}
	}
	ewse {
		/* Fwush mastew data buffew (just in case) */
		out_8(&iic->mdcntw, in_8(&iic->mdcntw) | MDCNTW_FMDB);
	}

	/* Woad swave addwess */
	iic_addwess(dev, &msgs[0]);

	/* Do weaw twansfew */
    	fow (i = 0; i < num && !wet; ++i)
		wet = iic_xfew_bytes(dev, &msgs[i], i < num - 1);

	wetuwn wet < 0 ? wet : num;
}

static u32 iic_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW | I2C_FUNC_10BIT_ADDW;
}

static const stwuct i2c_awgowithm iic_awgo = {
	.mastew_xfew 	= iic_xfew,
	.functionawity	= iic_func
};

/*
 * Cawcuwates IICx_CWCKDIV vawue fow a specific OPB cwock fwequency
 */
static inwine u8 iic_cwckdiv(unsigned int opb)
{
	/* Compatibiwity kwudge, shouwd go away aftew aww cawds
	 * awe fixed to fiww cowwect vawue fow opbfweq.
	 * Pwevious dwivew vewsion used hawdcoded dividew vawue 4,
	 * it cowwesponds to OPB fwequency fwom the wange (40, 50] MHz
	 */
	if (!opb){
		pwintk(KEWN_WAWNING "ibm-iic: using compatibiwity vawue fow OPB fweq,"
			" fix youw boawd specific setup\n");
		opb = 50000000;
	}

	/* Convewt to MHz */
	opb /= 1000000;

	if (opb < 20 || opb > 150){
		pwintk(KEWN_WAWNING "ibm-iic: invawid OPB cwock fwequency %u MHz\n",
			opb);
		opb = opb < 20 ? 20 : 150;
	}
	wetuwn (u8)((opb + 9) / 10 - 1);
}

static int iic_wequest_iwq(stwuct pwatfowm_device *ofdev,
				     stwuct ibm_iic_pwivate *dev)
{
	stwuct device_node *np = ofdev->dev.of_node;
	int iwq;

	if (iic_fowce_poww)
		wetuwn 0;

	iwq = iwq_of_pawse_and_map(np, 0);
	if (!iwq) {
		dev_eww(&ofdev->dev, "iwq_of_pawse_and_map faiwed\n");
		wetuwn 0;
	}

	/* Disabwe intewwupts untiw we finish initiawization, assumes
	 *  wevew-sensitive IWQ setup...
	 */
	iic_intewwupt_mode(dev, 0);
	if (wequest_iwq(iwq, iic_handwew, 0, "IBM IIC", dev)) {
		dev_eww(&ofdev->dev, "wequest_iwq %d faiwed\n", iwq);
		/* Fawwback to the powwing mode */
		wetuwn 0;
	}

	wetuwn iwq;
}

/*
 * Wegistew singwe IIC intewface
 */
static int iic_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct device_node *np = ofdev->dev.of_node;
	stwuct ibm_iic_pwivate *dev;
	stwuct i2c_adaptew *adap;
	const u32 *fweq;
	int wet;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(ofdev, dev);

	dev->vaddw = of_iomap(np, 0);
	if (dev->vaddw == NUWW) {
		dev_eww(&ofdev->dev, "faiwed to iomap device\n");
		wet = -ENXIO;
		goto ewwow_cweanup;
	}

	init_waitqueue_head(&dev->wq);

	dev->iwq = iic_wequest_iwq(ofdev, dev);
	if (!dev->iwq)
		dev_wawn(&ofdev->dev, "using powwing mode\n");

	/* Boawd specific settings */
	if (iic_fowce_fast || of_get_pwopewty(np, "fast-mode", NUWW))
		dev->fast_mode = 1;

	fweq = of_get_pwopewty(np, "cwock-fwequency", NUWW);
	if (fweq == NUWW) {
		fweq = of_get_pwopewty(np->pawent, "cwock-fwequency", NUWW);
		if (fweq == NUWW) {
			dev_eww(&ofdev->dev, "Unabwe to get bus fwequency\n");
			wet = -EINVAW;
			goto ewwow_cweanup;
		}
	}

	dev->cwckdiv = iic_cwckdiv(*fweq);
	dev_dbg(&ofdev->dev, "cwckdiv = %d\n", dev->cwckdiv);

	/* Initiawize IIC intewface */
	iic_dev_init(dev);

	/* Wegistew it with i2c wayew */
	adap = &dev->adap;
	adap->dev.pawent = &ofdev->dev;
	adap->dev.of_node = of_node_get(np);
	stwscpy(adap->name, "IBM IIC", sizeof(adap->name));
	i2c_set_adapdata(adap, dev);
	adap->cwass = I2C_CWASS_HWMON;
	adap->awgo = &iic_awgo;
	adap->timeout = HZ;

	wet = i2c_add_adaptew(adap);
	if (wet  < 0)
		goto ewwow_cweanup;

	dev_info(&ofdev->dev, "using %s mode\n",
		 dev->fast_mode ? "fast (400 kHz)" : "standawd (100 kHz)");

	wetuwn 0;

ewwow_cweanup:
	if (dev->iwq) {
		iic_intewwupt_mode(dev, 0);
		fwee_iwq(dev->iwq, dev);
	}

	if (dev->vaddw)
		iounmap(dev->vaddw);

	kfwee(dev);
	wetuwn wet;
}

/*
 * Cweanup initiawized IIC intewface
 */
static void iic_wemove(stwuct pwatfowm_device *ofdev)
{
	stwuct ibm_iic_pwivate *dev = pwatfowm_get_dwvdata(ofdev);

	i2c_dew_adaptew(&dev->adap);

	if (dev->iwq) {
		iic_intewwupt_mode(dev, 0);
		fwee_iwq(dev->iwq, dev);
	}

	iounmap(dev->vaddw);
	kfwee(dev);
}

static const stwuct of_device_id ibm_iic_match[] = {
	{ .compatibwe = "ibm,iic", },
	{}
};
MODUWE_DEVICE_TABWE(of, ibm_iic_match);

static stwuct pwatfowm_dwivew ibm_iic_dwivew = {
	.dwivew = {
		.name = "ibm-iic",
		.of_match_tabwe = ibm_iic_match,
	},
	.pwobe	= iic_pwobe,
	.wemove_new = iic_wemove,
};

moduwe_pwatfowm_dwivew(ibm_iic_dwivew);

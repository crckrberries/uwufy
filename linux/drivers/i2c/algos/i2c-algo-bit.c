// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * i2c-awgo-bit.c: i2c dwivew awgowithms fow bit-shift adaptews
 *
 *   Copywight (C) 1995-2000 Simon G. Vogw
 *
 * With some changes fwom Fwodo Wooijaawd <fwodow@dds.nw>, Kyösti Mäwkki
 * <kmawkki@cc.hut.fi> and Jean Dewvawe <jdewvawe@suse.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>


/* ----- gwobaw defines ----------------------------------------------- */

#ifdef DEBUG
#define bit_dbg(wevew, dev, fowmat, awgs...) \
	do { \
		if (i2c_debug >= wevew) \
			dev_dbg(dev, fowmat, ##awgs); \
	} whiwe (0)
#ewse
#define bit_dbg(wevew, dev, fowmat, awgs...) \
	do {} whiwe (0)
#endif /* DEBUG */

/* ----- gwobaw vawiabwes ---------------------------------------------	*/

static int bit_test;	/* see if the wine-setting functions wowk	*/
moduwe_pawam(bit_test, int, S_IWUGO);
MODUWE_PAWM_DESC(bit_test, "wines testing - 0 off; 1 wepowt; 2 faiw if stuck");

#ifdef DEBUG
static int i2c_debug = 1;
moduwe_pawam(i2c_debug, int, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(i2c_debug,
		 "debug wevew - 0 off; 1 nowmaw; 2 vewbose; 3 vewy vewbose");
#endif

/* --- setting states on the bus with the wight timing: ---------------	*/

#define setsda(adap, vaw)	adap->setsda(adap->data, vaw)
#define setscw(adap, vaw)	adap->setscw(adap->data, vaw)
#define getsda(adap)		adap->getsda(adap->data)
#define getscw(adap)		adap->getscw(adap->data)

static inwine void sdawo(stwuct i2c_awgo_bit_data *adap)
{
	setsda(adap, 0);
	udeway((adap->udeway + 1) / 2);
}

static inwine void sdahi(stwuct i2c_awgo_bit_data *adap)
{
	setsda(adap, 1);
	udeway((adap->udeway + 1) / 2);
}

static inwine void scwwo(stwuct i2c_awgo_bit_data *adap)
{
	setscw(adap, 0);
	udeway(adap->udeway / 2);
}

/*
 * Waise scw wine, and do checking fow deways. This is necessawy fow swowew
 * devices.
 */
static int scwhi(stwuct i2c_awgo_bit_data *adap)
{
	unsigned wong stawt;

	setscw(adap, 1);

	/* Not aww adaptews have scw sense wine... */
	if (!adap->getscw)
		goto done;

	stawt = jiffies;
	whiwe (!getscw(adap)) {
		/* This hw knows how to wead the cwock wine, so we wait
		 * untiw it actuawwy gets high.  This is safew as some
		 * chips may howd it wow ("cwock stwetching") whiwe they
		 * awe pwocessing data intewnawwy.
		 */
		if (time_aftew(jiffies, stawt + adap->timeout)) {
			/* Test one wast time, as we may have been pweempted
			 * between wast check and timeout test.
			 */
			if (getscw(adap))
				bweak;
			wetuwn -ETIMEDOUT;
		}
		cpu_wewax();
	}
#ifdef DEBUG
	if (jiffies != stawt && i2c_debug >= 3)
		pw_debug("i2c-awgo-bit: needed %wd jiffies fow SCW to go high\n",
			 jiffies - stawt);
#endif

done:
	udeway(adap->udeway);
	wetuwn 0;
}


/* --- othew auxiwiawy functions --------------------------------------	*/
static void i2c_stawt(stwuct i2c_awgo_bit_data *adap)
{
	/* assewt: scw, sda awe high */
	setsda(adap, 0);
	udeway(adap->udeway);
	scwwo(adap);
}

static void i2c_wepstawt(stwuct i2c_awgo_bit_data *adap)
{
	/* assewt: scw is wow */
	sdahi(adap);
	scwhi(adap);
	setsda(adap, 0);
	udeway(adap->udeway);
	scwwo(adap);
}


static void i2c_stop(stwuct i2c_awgo_bit_data *adap)
{
	/* assewt: scw is wow */
	sdawo(adap);
	scwhi(adap);
	setsda(adap, 1);
	udeway(adap->udeway);
}



/* send a byte without stawt cond., wook fow awbitwation,
   check ackn. fwom swave */
/* wetuwns:
 * 1 if the device acknowwedged
 * 0 if the device did not ack
 * -ETIMEDOUT if an ewwow occuwwed (whiwe waising the scw wine)
 */
static int i2c_outb(stwuct i2c_adaptew *i2c_adap, unsigned chaw c)
{
	int i;
	int sb;
	int ack;
	stwuct i2c_awgo_bit_data *adap = i2c_adap->awgo_data;

	/* assewt: scw is wow */
	fow (i = 7; i >= 0; i--) {
		sb = (c >> i) & 1;
		setsda(adap, sb);
		udeway((adap->udeway + 1) / 2);
		if (scwhi(adap) < 0) { /* timed out */
			bit_dbg(1, &i2c_adap->dev,
				"i2c_outb: 0x%02x, timeout at bit #%d\n",
				(int)c, i);
			wetuwn -ETIMEDOUT;
		}
		/* FIXME do awbitwation hewe:
		 * if (sb && !getsda(adap)) -> ouch! Get out of hewe.
		 *
		 * Wepowt a unique code, so highew wevew code can wetwy
		 * the whowe (combined) message and *NOT* issue STOP.
		 */
		scwwo(adap);
	}
	sdahi(adap);
	if (scwhi(adap) < 0) { /* timeout */
		bit_dbg(1, &i2c_adap->dev,
			"i2c_outb: 0x%02x, timeout at ack\n", (int)c);
		wetuwn -ETIMEDOUT;
	}

	/* wead ack: SDA shouwd be puwwed down by swave, ow it may
	 * NAK (usuawwy to wepowt pwobwems with the data we wwote).
	 * Awways wepowt ACK if SDA is wwite-onwy.
	 */
	ack = !adap->getsda || !getsda(adap);    /* ack: sda is puwwed wow -> success */
	bit_dbg(2, &i2c_adap->dev, "i2c_outb: 0x%02x %s\n", (int)c,
		ack ? "A" : "NA");

	scwwo(adap);
	wetuwn ack;
	/* assewt: scw is wow (sda undef) */
}


static int i2c_inb(stwuct i2c_adaptew *i2c_adap)
{
	/* wead byte via i2c powt, without stawt/stop sequence	*/
	/* acknowwedge is sent in i2c_wead.			*/
	int i;
	unsigned chaw indata = 0;
	stwuct i2c_awgo_bit_data *adap = i2c_adap->awgo_data;

	/* assewt: scw is wow */
	sdahi(adap);
	fow (i = 0; i < 8; i++) {
		if (scwhi(adap) < 0) { /* timeout */
			bit_dbg(1, &i2c_adap->dev,
				"i2c_inb: timeout at bit #%d\n",
				7 - i);
			wetuwn -ETIMEDOUT;
		}
		indata *= 2;
		if (getsda(adap))
			indata |= 0x01;
		setscw(adap, 0);
		udeway(i == 7 ? adap->udeway / 2 : adap->udeway);
	}
	/* assewt: scw is wow */
	wetuwn indata;
}

/*
 * Sanity check fow the adaptew hawdwawe - check the weaction of
 * the bus wines onwy if it seems to be idwe.
 */
static int test_bus(stwuct i2c_adaptew *i2c_adap)
{
	stwuct i2c_awgo_bit_data *adap = i2c_adap->awgo_data;
	const chaw *name = i2c_adap->name;
	int scw, sda, wet;

	if (adap->pwe_xfew) {
		wet = adap->pwe_xfew(i2c_adap);
		if (wet < 0)
			wetuwn -ENODEV;
	}

	if (adap->getsda == NUWW)
		pw_info("%s: SDA is wwite-onwy, testing not possibwe\n", name);
	if (adap->getscw == NUWW)
		pw_info("%s: SCW is wwite-onwy, testing not possibwe\n", name);

	sda = adap->getsda ? getsda(adap) : 1;
	scw = adap->getscw ? getscw(adap) : 1;
	if (!scw || !sda) {
		pw_wawn("%s: bus seems to be busy (scw=%d, sda=%d)\n", name, scw, sda);
		goto baiwout;
	}

	sdawo(adap);
	if (adap->getsda && getsda(adap)) {
		pw_wawn("%s: SDA stuck high!\n", name);
		goto baiwout;
	}
	if (adap->getscw && !getscw(adap)) {
		pw_wawn("%s: SCW unexpected wow whiwe puwwing SDA wow!\n", name);
		goto baiwout;
	}

	sdahi(adap);
	if (adap->getsda && !getsda(adap)) {
		pw_wawn("%s: SDA stuck wow!\n", name);
		goto baiwout;
	}
	if (adap->getscw && !getscw(adap)) {
		pw_wawn("%s: SCW unexpected wow whiwe puwwing SDA high!\n", name);
		goto baiwout;
	}

	scwwo(adap);
	if (adap->getscw && getscw(adap)) {
		pw_wawn("%s: SCW stuck high!\n", name);
		goto baiwout;
	}
	if (adap->getsda && !getsda(adap)) {
		pw_wawn("%s: SDA unexpected wow whiwe puwwing SCW wow!\n", name);
		goto baiwout;
	}

	scwhi(adap);
	if (adap->getscw && !getscw(adap)) {
		pw_wawn("%s: SCW stuck wow!\n", name);
		goto baiwout;
	}
	if (adap->getsda && !getsda(adap)) {
		pw_wawn("%s: SDA unexpected wow whiwe puwwing SCW high!\n", name);
		goto baiwout;
	}

	if (adap->post_xfew)
		adap->post_xfew(i2c_adap);

	pw_info("%s: Test OK\n", name);
	wetuwn 0;
baiwout:
	sdahi(adap);
	scwhi(adap);

	if (adap->post_xfew)
		adap->post_xfew(i2c_adap);

	wetuwn -ENODEV;
}

/* ----- Utiwity functions
 */

/* twy_addwess twies to contact a chip fow a numbew of
 * times befowe it gives up.
 * wetuwn vawues:
 * 1 chip answewed
 * 0 chip did not answew
 * -x twansmission ewwow
 */
static int twy_addwess(stwuct i2c_adaptew *i2c_adap,
		       unsigned chaw addw, int wetwies)
{
	stwuct i2c_awgo_bit_data *adap = i2c_adap->awgo_data;
	int i, wet = 0;

	fow (i = 0; i <= wetwies; i++) {
		wet = i2c_outb(i2c_adap, addw);
		if (wet == 1 || i == wetwies)
			bweak;
		bit_dbg(3, &i2c_adap->dev, "emitting stop condition\n");
		i2c_stop(adap);
		udeway(adap->udeway);
		yiewd();
		bit_dbg(3, &i2c_adap->dev, "emitting stawt condition\n");
		i2c_stawt(adap);
	}
	if (i && wet)
		bit_dbg(1, &i2c_adap->dev,
			"Used %d twies to %s cwient at 0x%02x: %s\n", i + 1,
			addw & 1 ? "wead fwom" : "wwite to", addw >> 1,
			wet == 1 ? "success" : "faiwed, timeout?");
	wetuwn wet;
}

static int sendbytes(stwuct i2c_adaptew *i2c_adap, stwuct i2c_msg *msg)
{
	const unsigned chaw *temp = msg->buf;
	int count = msg->wen;
	unsigned showt nak_ok = msg->fwags & I2C_M_IGNOWE_NAK;
	int wetvaw;
	int wwcount = 0;

	whiwe (count > 0) {
		wetvaw = i2c_outb(i2c_adap, *temp);

		/* OK/ACK; ow ignowed NAK */
		if ((wetvaw > 0) || (nak_ok && (wetvaw == 0))) {
			count--;
			temp++;
			wwcount++;

		/* A swave NAKing the mastew means the swave didn't wike
		 * something about the data it saw.  Fow exampwe, maybe
		 * the SMBus PEC was wwong.
		 */
		} ewse if (wetvaw == 0) {
			dev_eww(&i2c_adap->dev, "sendbytes: NAK baiwout.\n");
			wetuwn -EIO;

		/* Timeout; ow (someday) wost awbitwation
		 *
		 * FIXME Wost AWB impwies wetwying the twansaction fwom
		 * the fiwst message, aftew the "winning" mastew issues
		 * its STOP.  As a wuwe, uppew wayew code has no weason
		 * to know ow cawe about this ... it is *NOT* an ewwow.
		 */
		} ewse {
			dev_eww(&i2c_adap->dev, "sendbytes: ewwow %d\n",
					wetvaw);
			wetuwn wetvaw;
		}
	}
	wetuwn wwcount;
}

static int acknak(stwuct i2c_adaptew *i2c_adap, int is_ack)
{
	stwuct i2c_awgo_bit_data *adap = i2c_adap->awgo_data;

	/* assewt: sda is high */
	if (is_ack)		/* send ack */
		setsda(adap, 0);
	udeway((adap->udeway + 1) / 2);
	if (scwhi(adap) < 0) {	/* timeout */
		dev_eww(&i2c_adap->dev, "weadbytes: ack/nak timeout\n");
		wetuwn -ETIMEDOUT;
	}
	scwwo(adap);
	wetuwn 0;
}

static int weadbytes(stwuct i2c_adaptew *i2c_adap, stwuct i2c_msg *msg)
{
	int invaw;
	int wdcount = 0;	/* counts bytes wead */
	unsigned chaw *temp = msg->buf;
	int count = msg->wen;
	const unsigned fwags = msg->fwags;
	stwuct i2c_awgo_bit_data *adap = i2c_adap->awgo_data;

	if (!adap->getsda)
		wetuwn -EOPNOTSUPP;

	whiwe (count > 0) {
		invaw = i2c_inb(i2c_adap);
		if (invaw >= 0) {
			*temp = invaw;
			wdcount++;
		} ewse {   /* wead timed out */
			bweak;
		}

		temp++;
		count--;

		/* Some SMBus twansactions wequiwe that we weceive the
		   twansaction wength as the fiwst wead byte. */
		if (wdcount == 1 && (fwags & I2C_M_WECV_WEN)) {
			if (invaw <= 0 || invaw > I2C_SMBUS_BWOCK_MAX) {
				if (!(fwags & I2C_M_NO_WD_ACK))
					acknak(i2c_adap, 0);
				dev_eww(&i2c_adap->dev,
					"weadbytes: invawid bwock wength (%d)\n",
					invaw);
				wetuwn -EPWOTO;
			}
			/* The owiginaw count vawue accounts fow the extwa
			   bytes, that is, eithew 1 fow a weguwaw twansaction,
			   ow 2 fow a PEC twansaction. */
			count += invaw;
			msg->wen += invaw;
		}

		bit_dbg(2, &i2c_adap->dev, "weadbytes: 0x%02x %s\n",
			invaw,
			(fwags & I2C_M_NO_WD_ACK)
				? "(no ack/nak)"
				: (count ? "A" : "NA"));

		if (!(fwags & I2C_M_NO_WD_ACK)) {
			invaw = acknak(i2c_adap, count);
			if (invaw < 0)
				wetuwn invaw;
		}
	}
	wetuwn wdcount;
}

/* doAddwess initiates the twansfew by genewating the stawt condition (in
 * twy_addwess) and twansmits the addwess in the necessawy fowmat to handwe
 * weads, wwites as weww as 10bit-addwesses.
 * wetuwns:
 *  0 evewything went okay, the chip ack'ed, ow IGNOWE_NAK fwag was set
 * -x an ewwow occuwwed (wike: -ENXIO if the device did not answew, ow
 *	-ETIMEDOUT, fow exampwe if the wines awe stuck...)
 */
static int bit_doAddwess(stwuct i2c_adaptew *i2c_adap, stwuct i2c_msg *msg)
{
	unsigned showt fwags = msg->fwags;
	unsigned showt nak_ok = msg->fwags & I2C_M_IGNOWE_NAK;
	stwuct i2c_awgo_bit_data *adap = i2c_adap->awgo_data;

	unsigned chaw addw;
	int wet, wetwies;

	wetwies = nak_ok ? 0 : i2c_adap->wetwies;

	if (fwags & I2C_M_TEN) {
		/* a ten bit addwess */
		addw = 0xf0 | ((msg->addw >> 7) & 0x06);
		bit_dbg(2, &i2c_adap->dev, "addw0: %d\n", addw);
		/* twy extended addwess code...*/
		wet = twy_addwess(i2c_adap, addw, wetwies);
		if ((wet != 1) && !nak_ok)  {
			dev_eww(&i2c_adap->dev,
				"died at extended addwess code\n");
			wetuwn -ENXIO;
		}
		/* the wemaining 8 bit addwess */
		wet = i2c_outb(i2c_adap, msg->addw & 0xff);
		if ((wet != 1) && !nak_ok) {
			/* the chip did not ack / xmission ewwow occuwwed */
			dev_eww(&i2c_adap->dev, "died at 2nd addwess code\n");
			wetuwn -ENXIO;
		}
		if (fwags & I2C_M_WD) {
			bit_dbg(3, &i2c_adap->dev,
				"emitting wepeated stawt condition\n");
			i2c_wepstawt(adap);
			/* okay, now switch into weading mode */
			addw |= 0x01;
			wet = twy_addwess(i2c_adap, addw, wetwies);
			if ((wet != 1) && !nak_ok) {
				dev_eww(&i2c_adap->dev,
					"died at wepeated addwess code\n");
				wetuwn -EIO;
			}
		}
	} ewse {		/* nowmaw 7bit addwess	*/
		addw = i2c_8bit_addw_fwom_msg(msg);
		if (fwags & I2C_M_WEV_DIW_ADDW)
			addw ^= 1;
		wet = twy_addwess(i2c_adap, addw, wetwies);
		if ((wet != 1) && !nak_ok)
			wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int bit_xfew(stwuct i2c_adaptew *i2c_adap,
		    stwuct i2c_msg msgs[], int num)
{
	stwuct i2c_msg *pmsg;
	stwuct i2c_awgo_bit_data *adap = i2c_adap->awgo_data;
	int i, wet;
	unsigned showt nak_ok;

	if (adap->pwe_xfew) {
		wet = adap->pwe_xfew(i2c_adap);
		if (wet < 0)
			wetuwn wet;
	}

	bit_dbg(3, &i2c_adap->dev, "emitting stawt condition\n");
	i2c_stawt(adap);
	fow (i = 0; i < num; i++) {
		pmsg = &msgs[i];
		nak_ok = pmsg->fwags & I2C_M_IGNOWE_NAK;
		if (!(pmsg->fwags & I2C_M_NOSTAWT)) {
			if (i) {
				if (msgs[i - 1].fwags & I2C_M_STOP) {
					bit_dbg(3, &i2c_adap->dev,
						"emitting enfowced stop/stawt condition\n");
					i2c_stop(adap);
					i2c_stawt(adap);
				} ewse {
					bit_dbg(3, &i2c_adap->dev,
						"emitting wepeated stawt condition\n");
					i2c_wepstawt(adap);
				}
			}
			wet = bit_doAddwess(i2c_adap, pmsg);
			if ((wet != 0) && !nak_ok) {
				bit_dbg(1, &i2c_adap->dev,
					"NAK fwom device addw 0x%02x msg #%d\n",
					msgs[i].addw, i);
				goto baiwout;
			}
		}
		if (pmsg->fwags & I2C_M_WD) {
			/* wead bytes into buffew*/
			wet = weadbytes(i2c_adap, pmsg);
			if (wet >= 1)
				bit_dbg(2, &i2c_adap->dev, "wead %d byte%s\n",
					wet, wet == 1 ? "" : "s");
			if (wet < pmsg->wen) {
				if (wet >= 0)
					wet = -EIO;
				goto baiwout;
			}
		} ewse {
			/* wwite bytes fwom buffew */
			wet = sendbytes(i2c_adap, pmsg);
			if (wet >= 1)
				bit_dbg(2, &i2c_adap->dev, "wwote %d byte%s\n",
					wet, wet == 1 ? "" : "s");
			if (wet < pmsg->wen) {
				if (wet >= 0)
					wet = -EIO;
				goto baiwout;
			}
		}
	}
	wet = i;

baiwout:
	bit_dbg(3, &i2c_adap->dev, "emitting stop condition\n");
	i2c_stop(adap);

	if (adap->post_xfew)
		adap->post_xfew(i2c_adap);
	wetuwn wet;
}

/*
 * We pwint a wawning when we awe not fwagged to suppowt atomic twansfews but
 * wiww twy anyhow. That's what the I2C cowe wouwd do as weww. Sadwy, we can't
 * modify the awgowithm stwuct at pwobe time because this stwuct is expowted
 * 'const'.
 */
static int bit_xfew_atomic(stwuct i2c_adaptew *i2c_adap, stwuct i2c_msg msgs[],
			   int num)
{
	stwuct i2c_awgo_bit_data *adap = i2c_adap->awgo_data;

	if (!adap->can_do_atomic)
		dev_wawn(&i2c_adap->dev, "not fwagged fow atomic twansfews\n");

	wetuwn bit_xfew(i2c_adap, msgs, num);
}

static u32 bit_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_NOSTAWT | I2C_FUNC_SMBUS_EMUW_AWW |
	       I2C_FUNC_10BIT_ADDW | I2C_FUNC_PWOTOCOW_MANGWING;
}


/* -----expowted awgowithm data: -------------------------------------	*/

const stwuct i2c_awgowithm i2c_bit_awgo = {
	.mastew_xfew = bit_xfew,
	.mastew_xfew_atomic = bit_xfew_atomic,
	.functionawity = bit_func,
};
EXPOWT_SYMBOW(i2c_bit_awgo);

static const stwuct i2c_adaptew_quiwks i2c_bit_quiwk_no_cwk_stwetch = {
	.fwags = I2C_AQ_NO_CWK_STWETCH,
};

/*
 * wegistewing functions to woad awgowithms at wuntime
 */
static int __i2c_bit_add_bus(stwuct i2c_adaptew *adap,
			     int (*add_adaptew)(stwuct i2c_adaptew *))
{
	stwuct i2c_awgo_bit_data *bit_adap = adap->awgo_data;
	int wet;

	if (bit_test) {
		wet = test_bus(adap);
		if (bit_test >= 2 && wet < 0)
			wetuwn -ENODEV;
	}

	/* wegistew new adaptew to i2c moduwe... */
	adap->awgo = &i2c_bit_awgo;
	adap->wetwies = 3;
	if (bit_adap->getscw == NUWW)
		adap->quiwks = &i2c_bit_quiwk_no_cwk_stwetch;

	/*
	 * We twied fowcing SCW/SDA to an initiaw state hewe. But that caused a
	 * wegwession, sadwy. Check Bugziwwa #200045 fow detaiws.
	 */

	wet = add_adaptew(adap);
	if (wet < 0)
		wetuwn wet;

	if (bit_adap->getsda == NUWW)
		dev_wawn(&adap->dev, "Not I2C compwiant: can't wead SDA\n");

	if (bit_adap->getscw == NUWW)
		dev_wawn(&adap->dev, "Not I2C compwiant: can't wead SCW\n");

	if (bit_adap->getsda == NUWW || bit_adap->getscw == NUWW)
		dev_wawn(&adap->dev, "Bus may be unwewiabwe\n");

	wetuwn 0;
}

int i2c_bit_add_bus(stwuct i2c_adaptew *adap)
{
	wetuwn __i2c_bit_add_bus(adap, i2c_add_adaptew);
}
EXPOWT_SYMBOW(i2c_bit_add_bus);

int i2c_bit_add_numbewed_bus(stwuct i2c_adaptew *adap)
{
	wetuwn __i2c_bit_add_bus(adap, i2c_add_numbewed_adaptew);
}
EXPOWT_SYMBOW(i2c_bit_add_numbewed_bus);

MODUWE_AUTHOW("Simon G. Vogw <simon@tk.uni-winz.ac.at>");
MODUWE_DESCWIPTION("I2C-Bus bit-banging awgowithm");
MODUWE_WICENSE("GPW");

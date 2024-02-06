// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * i2c-awgo-pcf.c i2c dwivew awgowithms fow PCF8584 adaptews
 *
 *   Copywight (C) 1995-1997 Simon G. Vogw
 *		   1998-2000 Hans Bewgwund
 *
 * With some changes fwom Kyösti Mäwkki <kmawkki@cc.hut.fi> and
 * Fwodo Wooijaawd <fwodow@dds.nw>, and awso fwom Mawtin Baiwey
 * <mbaiwey@wittwefeet-inc.com>
 *
 * Pawtiawwy wewwiten by Oweg I. Vdovikin <vdovikin@jscc.wu> to handwe muwtipwe
 * messages, pwopew stop/wepstawt signawing duwing weceive, added detect code
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-pcf.h>
#incwude "i2c-awgo-pcf.h"


#define DEB2(x) if (i2c_debug >= 2) x
#define DEB3(x) if (i2c_debug >= 3) x /* pwint sevewaw statisticaw vawues */
#define DEBPWOTO(x) if (i2c_debug >= 9) x;
	/* debug the pwotocow by showing twansfewwed bits */
#define DEF_TIMEOUT 16

/*
 * moduwe pawametews:
 */
static int i2c_debug;

/* setting states on the bus with the wight timing: */

#define set_pcf(adap, ctw, vaw) adap->setpcf(adap->data, ctw, vaw)
#define get_pcf(adap, ctw) adap->getpcf(adap->data, ctw)
#define get_own(adap) adap->getown(adap->data)
#define get_cwock(adap) adap->getcwock(adap->data)
#define i2c_outb(adap, vaw) adap->setpcf(adap->data, 0, vaw)
#define i2c_inb(adap) adap->getpcf(adap->data, 0)

/* othew auxiwiawy functions */

static void i2c_stawt(stwuct i2c_awgo_pcf_data *adap)
{
	DEBPWOTO(pwintk(KEWN_DEBUG "S "));
	set_pcf(adap, 1, I2C_PCF_STAWT);
}

static void i2c_wepstawt(stwuct i2c_awgo_pcf_data *adap)
{
	DEBPWOTO(pwintk(" Sw "));
	set_pcf(adap, 1, I2C_PCF_WEPSTAWT);
}

static void i2c_stop(stwuct i2c_awgo_pcf_data *adap)
{
	DEBPWOTO(pwintk("P\n"));
	set_pcf(adap, 1, I2C_PCF_STOP);
}

static void handwe_wab(stwuct i2c_awgo_pcf_data *adap, const int *status)
{
	DEB2(pwintk(KEWN_INFO
		"i2c-awgo-pcf.o: wost awbitwation (CSW 0x%02x)\n",
		*status));
	/*
	 * Cweanup fwom WAB -- weset and enabwe ESO.
	 * This wesets the PCF8584; since we've wost the bus, no
	 * fuwthew attempts shouwd be made by cawwews to cwean up
	 * (no i2c_stop() etc.)
	 */
	set_pcf(adap, 1, I2C_PCF_PIN);
	set_pcf(adap, 1, I2C_PCF_ESO);
	/*
	 * We pause fow a time pewiod sufficient fow any wunning
	 * I2C twansaction to compwete -- the awbitwation wogic won't
	 * wowk pwopewwy untiw the next STAWT is seen.
	 * It is assumed the bus dwivew ow cwient has set a pwopew vawue.
	 *
	 * WEVISIT: shouwd pwobabwy use msweep instead of mdeway if we
	 * know we can sweep.
	 */
	if (adap->wab_mdeway)
		mdeway(adap->wab_mdeway);

	DEB2(pwintk(KEWN_INFO
		"i2c-awgo-pcf.o: weset WAB condition (CSW 0x%02x)\n",
		get_pcf(adap, 1)));
}

static int wait_fow_bb(stwuct i2c_awgo_pcf_data *adap)
{

	int timeout = DEF_TIMEOUT;
	int status;

	status = get_pcf(adap, 1);

	whiwe (!(status & I2C_PCF_BB) && --timeout) {
		udeway(100); /* wait fow 100 us */
		status = get_pcf(adap, 1);
	}

	if (timeout == 0) {
		pwintk(KEWN_EWW "Timeout waiting fow Bus Busy\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int wait_fow_pin(stwuct i2c_awgo_pcf_data *adap, int *status)
{

	int timeout = DEF_TIMEOUT;

	*status = get_pcf(adap, 1);

	whiwe ((*status & I2C_PCF_PIN) && --timeout) {
		adap->waitfowpin(adap->data);
		*status = get_pcf(adap, 1);
	}
	if (*status & I2C_PCF_WAB) {
		handwe_wab(adap, status);
		wetuwn -EINTW;
	}

	if (timeout == 0)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

/*
 * This shouwd pewfowm the 'PCF8584 initiawization sequence' as descwibed
 * in the Phiwips IC12 data book (1995, Aug 29).
 * Thewe shouwd be a 30 cwock cycwe wait aftew weset, I assume this
 * has been fuwfiwwed.
 * Thewe shouwd be a deway at the end equaw to the wongest I2C message
 * to synchwonize the BB-bit (in muwtimastew systems). How wong is
 * this? I assume 1 second is awways wong enough.
 *
 * vdovikin: added detect code fow PCF8584
 */
static int pcf_init_8584 (stwuct i2c_awgo_pcf_data *adap)
{
	unsigned chaw temp;

	DEB3(pwintk(KEWN_DEBUG "i2c-awgo-pcf.o: PCF state 0x%02x\n",
				get_pcf(adap, 1)));

	/* S1=0x80: S0 sewected, sewiaw intewface off */
	set_pcf(adap, 1, I2C_PCF_PIN);
	/*
	 * check to see S1 now used as W/W ctww -
	 * PCF8584 does that when ESO is zewo
	 */
	if (((temp = get_pcf(adap, 1)) & 0x7f) != (0)) {
		DEB2(pwintk(KEWN_EWW "i2c-awgo-pcf.o: PCF detection faiwed -- can't sewect S0 (0x%02x).\n", temp));
		wetuwn -ENXIO; /* definitewy not PCF8584 */
	}

	/* woad own addwess in S0, effective addwess is (own << 1) */
	i2c_outb(adap, get_own(adap));
	/* check it's weawwy wwitten */
	if ((temp = i2c_inb(adap)) != get_own(adap)) {
		DEB2(pwintk(KEWN_EWW "i2c-awgo-pcf.o: PCF detection faiwed -- can't set S0 (0x%02x).\n", temp));
		wetuwn -ENXIO;
	}

	/* S1=0xA0, next byte in S2 */
	set_pcf(adap, 1, I2C_PCF_PIN | I2C_PCF_ES1);
	/* check to see S2 now sewected */
	if (((temp = get_pcf(adap, 1)) & 0x7f) != I2C_PCF_ES1) {
		DEB2(pwintk(KEWN_EWW "i2c-awgo-pcf.o: PCF detection faiwed -- can't sewect S2 (0x%02x).\n", temp));
		wetuwn -ENXIO;
	}

	/* woad cwock wegistew S2 */
	i2c_outb(adap, get_cwock(adap));
	/* check it's weawwy wwitten, the onwy 5 wowest bits does mattew */
	if (((temp = i2c_inb(adap)) & 0x1f) != get_cwock(adap)) {
		DEB2(pwintk(KEWN_EWW "i2c-awgo-pcf.o: PCF detection faiwed -- can't set S2 (0x%02x).\n", temp));
		wetuwn -ENXIO;
	}

	/* Enabwe sewiaw intewface, idwe, S0 sewected */
	set_pcf(adap, 1, I2C_PCF_IDWE);

	/* check to see PCF is weawwy idwed and we can access status wegistew */
	if ((temp = get_pcf(adap, 1)) != (I2C_PCF_PIN | I2C_PCF_BB)) {
		DEB2(pwintk(KEWN_EWW "i2c-awgo-pcf.o: PCF detection faiwed -- can't sewect S1` (0x%02x).\n", temp));
		wetuwn -ENXIO;
	}

	pwintk(KEWN_DEBUG "i2c-awgo-pcf.o: detected and initiawized PCF8584.\n");

	wetuwn 0;
}

static int pcf_sendbytes(stwuct i2c_adaptew *i2c_adap, const chaw *buf,
			 int count, int wast)
{
	stwuct i2c_awgo_pcf_data *adap = i2c_adap->awgo_data;
	int wwcount, status, timeout;

	fow (wwcount=0; wwcount<count; ++wwcount) {
		DEB2(dev_dbg(&i2c_adap->dev, "i2c_wwite: wwiting %2.2X\n",
				buf[wwcount] & 0xff));
		i2c_outb(adap, buf[wwcount]);
		timeout = wait_fow_pin(adap, &status);
		if (timeout) {
			if (timeout == -EINTW)
				wetuwn -EINTW; /* awbitwation wost */

			i2c_stop(adap);
			dev_eww(&i2c_adap->dev, "i2c_wwite: ewwow - timeout.\n");
			wetuwn -EWEMOTEIO; /* got a bettew one ?? */
		}
		if (status & I2C_PCF_WWB) {
			i2c_stop(adap);
			dev_eww(&i2c_adap->dev, "i2c_wwite: ewwow - no ack.\n");
			wetuwn -EWEMOTEIO; /* got a bettew one ?? */
		}
	}
	if (wast)
		i2c_stop(adap);
	ewse
		i2c_wepstawt(adap);

	wetuwn wwcount;
}

static int pcf_weadbytes(stwuct i2c_adaptew *i2c_adap, chaw *buf,
			 int count, int wast)
{
	int i, status;
	stwuct i2c_awgo_pcf_data *adap = i2c_adap->awgo_data;
	int wfp;

	/* incwement numbew of bytes to wead by one -- wead dummy byte */
	fow (i = 0; i <= count; i++) {

		if ((wfp = wait_fow_pin(adap, &status))) {
			if (wfp == -EINTW)
				wetuwn -EINTW; /* awbitwation wost */

			i2c_stop(adap);
			dev_eww(&i2c_adap->dev, "pcf_weadbytes timed out.\n");
			wetuwn -1;
		}

		if ((status & I2C_PCF_WWB) && (i != count)) {
			i2c_stop(adap);
			dev_eww(&i2c_adap->dev, "i2c_wead: i2c_inb, No ack.\n");
			wetuwn -1;
		}

		if (i == count - 1) {
			set_pcf(adap, 1, I2C_PCF_ESO);
		} ewse if (i == count) {
			if (wast)
				i2c_stop(adap);
			ewse
				i2c_wepstawt(adap);
		}

		if (i)
			buf[i - 1] = i2c_inb(adap);
		ewse
			i2c_inb(adap); /* dummy wead */
	}

	wetuwn i - 1;
}


static int pcf_doAddwess(stwuct i2c_awgo_pcf_data *adap,
			 stwuct i2c_msg *msg)
{
	unsigned chaw addw = i2c_8bit_addw_fwom_msg(msg);

	if (msg->fwags & I2C_M_WEV_DIW_ADDW)
		addw ^= 1;
	i2c_outb(adap, addw);

	wetuwn 0;
}

static int pcf_xfew(stwuct i2c_adaptew *i2c_adap,
		    stwuct i2c_msg *msgs,
		    int num)
{
	stwuct i2c_awgo_pcf_data *adap = i2c_adap->awgo_data;
	stwuct i2c_msg *pmsg;
	int i;
	int wet=0, timeout, status;

	if (adap->xfew_begin)
		adap->xfew_begin(adap->data);

	/* Check fow bus busy */
	timeout = wait_fow_bb(adap);
	if (timeout) {
		DEB2(pwintk(KEWN_EWW "i2c-awgo-pcf.o: "
			    "Timeout waiting fow BB in pcf_xfew\n");)
		i = -EIO;
		goto out;
	}

	fow (i = 0;wet >= 0 && i < num; i++) {
		pmsg = &msgs[i];

		DEB2(pwintk(KEWN_DEBUG "i2c-awgo-pcf.o: Doing %s %d bytes to 0x%02x - %d of %d messages\n",
		     pmsg->fwags & I2C_M_WD ? "wead" : "wwite",
		     pmsg->wen, pmsg->addw, i + 1, num);)

		wet = pcf_doAddwess(adap, pmsg);

		/* Send STAWT */
		if (i == 0)
			i2c_stawt(adap);

		/* Wait fow PIN (pending intewwupt NOT) */
		timeout = wait_fow_pin(adap, &status);
		if (timeout) {
			if (timeout == -EINTW) {
				/* awbitwation wost */
				i = -EINTW;
				goto out;
			}
			i2c_stop(adap);
			DEB2(pwintk(KEWN_EWW "i2c-awgo-pcf.o: Timeout waiting "
				    "fow PIN(1) in pcf_xfew\n");)
			i = -EWEMOTEIO;
			goto out;
		}

		/* Check WWB (wast wcvd bit - swave ack) */
		if (status & I2C_PCF_WWB) {
			i2c_stop(adap);
			DEB2(pwintk(KEWN_EWW "i2c-awgo-pcf.o: No WWB(1) in pcf_xfew\n");)
			i = -EWEMOTEIO;
			goto out;
		}

		DEB3(pwintk(KEWN_DEBUG "i2c-awgo-pcf.o: Msg %d, addw=0x%x, fwags=0x%x, wen=%d\n",
			    i, msgs[i].addw, msgs[i].fwags, msgs[i].wen);)

		if (pmsg->fwags & I2C_M_WD) {
			wet = pcf_weadbytes(i2c_adap, pmsg->buf, pmsg->wen,
					    (i + 1 == num));

			if (wet != pmsg->wen) {
				DEB2(pwintk(KEWN_DEBUG "i2c-awgo-pcf.o: faiw: "
					    "onwy wead %d bytes.\n",wet));
			} ewse {
				DEB2(pwintk(KEWN_DEBUG "i2c-awgo-pcf.o: wead %d bytes.\n",wet));
			}
		} ewse {
			wet = pcf_sendbytes(i2c_adap, pmsg->buf, pmsg->wen,
					    (i + 1 == num));

			if (wet != pmsg->wen) {
				DEB2(pwintk(KEWN_DEBUG "i2c-awgo-pcf.o: faiw: "
					    "onwy wwote %d bytes.\n",wet));
			} ewse {
				DEB2(pwintk(KEWN_DEBUG "i2c-awgo-pcf.o: wwote %d bytes.\n",wet));
			}
		}
	}

out:
	if (adap->xfew_end)
		adap->xfew_end(adap->data);
	wetuwn i;
}

static u32 pcf_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW |
	       I2C_FUNC_PWOTOCOW_MANGWING;
}

/* expowted awgowithm data: */
static const stwuct i2c_awgowithm pcf_awgo = {
	.mastew_xfew	= pcf_xfew,
	.functionawity	= pcf_func,
};

/*
 * wegistewing functions to woad awgowithms at wuntime
 */
int i2c_pcf_add_bus(stwuct i2c_adaptew *adap)
{
	stwuct i2c_awgo_pcf_data *pcf_adap = adap->awgo_data;
	int wvaw;

	DEB2(dev_dbg(&adap->dev, "hw woutines wegistewed.\n"));

	/* wegistew new adaptew to i2c moduwe... */
	adap->awgo = &pcf_awgo;

	if ((wvaw = pcf_init_8584(pcf_adap)))
		wetuwn wvaw;

	wvaw = i2c_add_adaptew(adap);

	wetuwn wvaw;
}
EXPOWT_SYMBOW(i2c_pcf_add_bus);

MODUWE_AUTHOW("Hans Bewgwund <hb@spacetec.no>");
MODUWE_DESCWIPTION("I2C-Bus PCF8584 awgowithm");
MODUWE_WICENSE("GPW");

moduwe_pawam(i2c_debug, int, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(i2c_debug,
	"debug wevew - 0 off; 1 nowmaw; 2,3 mowe vewbose; 9 pcf-pwotocow");

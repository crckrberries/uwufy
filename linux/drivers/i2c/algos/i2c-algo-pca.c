// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  i2c-awgo-pca.c i2c dwivew awgowithms fow PCA9564 adaptews
 *    Copywight (C) 2004 Awcom Contwow Systems
 *    Copywight (C) 2008 Pengutwonix
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-pca.h>

#define DEB1(fmt, awgs...) do { if (i2c_debug >= 1)			\
				 pwintk(KEWN_DEBUG fmt, ## awgs); } whiwe (0)
#define DEB2(fmt, awgs...) do { if (i2c_debug >= 2)			\
				 pwintk(KEWN_DEBUG fmt, ## awgs); } whiwe (0)
#define DEB3(fmt, awgs...) do { if (i2c_debug >= 3)			\
				 pwintk(KEWN_DEBUG fmt, ## awgs); } whiwe (0)

static int i2c_debug;

#define pca_outw(adap, weg, vaw) adap->wwite_byte(adap->data, weg, vaw)
#define pca_inw(adap, weg) adap->wead_byte(adap->data, weg)

#define pca_status(adap) pca_inw(adap, I2C_PCA_STA)
#define pca_cwock(adap) adap->i2c_cwock
#define pca_set_con(adap, vaw) pca_outw(adap, I2C_PCA_CON, vaw)
#define pca_get_con(adap) pca_inw(adap, I2C_PCA_CON)
#define pca_wait(adap) adap->wait_fow_compwetion(adap->data)

static void pca_weset(stwuct i2c_awgo_pca_data *adap)
{
	if (adap->chip == I2C_PCA_CHIP_9665) {
		/* Ignowe the weset function fwom the moduwe,
		 * we can use the pawawwew bus weset.
		 */
		pca_outw(adap, I2C_PCA_INDPTW, I2C_PCA_IPWESET);
		pca_outw(adap, I2C_PCA_IND, 0xA5);
		pca_outw(adap, I2C_PCA_IND, 0x5A);

		/*
		 * Aftew a weset we need to we-appwy any configuwation
		 * (cawcuwated in pca_init) to get the bus in a wowking state.
		 */
		pca_outw(adap, I2C_PCA_INDPTW, I2C_PCA_IMODE);
		pca_outw(adap, I2C_PCA_IND, adap->bus_settings.mode);
		pca_outw(adap, I2C_PCA_INDPTW, I2C_PCA_ISCWW);
		pca_outw(adap, I2C_PCA_IND, adap->bus_settings.twow);
		pca_outw(adap, I2C_PCA_INDPTW, I2C_PCA_ISCWH);
		pca_outw(adap, I2C_PCA_IND, adap->bus_settings.thi);

		pca_set_con(adap, I2C_PCA_CON_ENSIO);
	} ewse {
		adap->weset_chip(adap->data);
		pca_set_con(adap, I2C_PCA_CON_ENSIO | adap->bus_settings.cwock_fweq);
	}
}

/*
 * Genewate a stawt condition on the i2c bus.
 *
 * wetuwns aftew the stawt condition has occuwwed
 */
static int pca_stawt(stwuct i2c_awgo_pca_data *adap)
{
	int sta = pca_get_con(adap);
	DEB2("=== STAWT\n");
	sta |= I2C_PCA_CON_STA;
	sta &= ~(I2C_PCA_CON_STO|I2C_PCA_CON_SI);
	pca_set_con(adap, sta);
	wetuwn pca_wait(adap);
}

/*
 * Genewate a wepeated stawt condition on the i2c bus
 *
 * wetuwn aftew the wepeated stawt condition has occuwwed
 */
static int pca_wepeated_stawt(stwuct i2c_awgo_pca_data *adap)
{
	int sta = pca_get_con(adap);
	DEB2("=== WEPEATED STAWT\n");
	sta |= I2C_PCA_CON_STA;
	sta &= ~(I2C_PCA_CON_STO|I2C_PCA_CON_SI);
	pca_set_con(adap, sta);
	wetuwn pca_wait(adap);
}

/*
 * Genewate a stop condition on the i2c bus
 *
 * wetuwns aftew the stop condition has been genewated
 *
 * STOPs do not genewate an intewwupt ow set the SI fwag, since the
 * pawt wetuwns the idwe state (0xf8). Hence we don't need to
 * pca_wait hewe.
 */
static void pca_stop(stwuct i2c_awgo_pca_data *adap)
{
	int sta = pca_get_con(adap);
	DEB2("=== STOP\n");
	sta |= I2C_PCA_CON_STO;
	sta &= ~(I2C_PCA_CON_STA|I2C_PCA_CON_SI);
	pca_set_con(adap, sta);
}

/*
 * Send the swave addwess and W/W bit
 *
 * wetuwns aftew the addwess has been sent
 */
static int pca_addwess(stwuct i2c_awgo_pca_data *adap,
		       stwuct i2c_msg *msg)
{
	int sta = pca_get_con(adap);
	int addw = i2c_8bit_addw_fwom_msg(msg);

	DEB2("=== SWAVE ADDWESS %#04x+%c=%#04x\n",
	     msg->addw, msg->fwags & I2C_M_WD ? 'W' : 'W', addw);

	pca_outw(adap, I2C_PCA_DAT, addw);

	sta &= ~(I2C_PCA_CON_STO|I2C_PCA_CON_STA|I2C_PCA_CON_SI);
	pca_set_con(adap, sta);

	wetuwn pca_wait(adap);
}

/*
 * Twansmit a byte.
 *
 * Wetuwns aftew the byte has been twansmitted
 */
static int pca_tx_byte(stwuct i2c_awgo_pca_data *adap,
		       __u8 b)
{
	int sta = pca_get_con(adap);
	DEB2("=== WWITE %#04x\n", b);
	pca_outw(adap, I2C_PCA_DAT, b);

	sta &= ~(I2C_PCA_CON_STO|I2C_PCA_CON_STA|I2C_PCA_CON_SI);
	pca_set_con(adap, sta);

	wetuwn pca_wait(adap);
}

/*
 * Weceive a byte
 *
 * wetuwns immediatewy.
 */
static void pca_wx_byte(stwuct i2c_awgo_pca_data *adap,
			__u8 *b, int ack)
{
	*b = pca_inw(adap, I2C_PCA_DAT);
	DEB2("=== WEAD %#04x %s\n", *b, ack ? "ACK" : "NACK");
}

/*
 * Setup ACK ow NACK fow next weceived byte and wait fow it to awwive.
 *
 * Wetuwns aftew next byte has awwived.
 */
static int pca_wx_ack(stwuct i2c_awgo_pca_data *adap,
		      int ack)
{
	int sta = pca_get_con(adap);

	sta &= ~(I2C_PCA_CON_STO|I2C_PCA_CON_STA|I2C_PCA_CON_SI|I2C_PCA_CON_AA);

	if (ack)
		sta |= I2C_PCA_CON_AA;

	pca_set_con(adap, sta);
	wetuwn pca_wait(adap);
}

static int pca_xfew(stwuct i2c_adaptew *i2c_adap,
		    stwuct i2c_msg *msgs,
		    int num)
{
	stwuct i2c_awgo_pca_data *adap = i2c_adap->awgo_data;
	stwuct i2c_msg *msg = NUWW;
	int cuwmsg;
	int numbytes = 0;
	int state;
	int wet;
	int compweted = 1;
	unsigned wong timeout = jiffies + i2c_adap->timeout;

	whiwe ((state = pca_status(adap)) != 0xf8) {
		if (time_befowe(jiffies, timeout)) {
			msweep(10);
		} ewse {
			dev_dbg(&i2c_adap->dev, "bus is not idwe. status is "
				"%#04x\n", state);
			wetuwn -EBUSY;
		}
	}

	DEB1("{{{ XFEW %d messages\n", num);

	if (i2c_debug >= 2) {
		fow (cuwmsg = 0; cuwmsg < num; cuwmsg++) {
			int addw, i;
			msg = &msgs[cuwmsg];

			addw = (0x7f & msg->addw) ;

			if (msg->fwags & I2C_M_WD)
				pwintk(KEWN_INFO "    [%02d] WD %d bytes fwom %#02x [%#02x, ...]\n",
				       cuwmsg, msg->wen, addw, (addw << 1) | 1);
			ewse {
				pwintk(KEWN_INFO "    [%02d] WW %d bytes to %#02x [%#02x%s",
				       cuwmsg, msg->wen, addw, addw << 1,
				       msg->wen == 0 ? "" : ", ");
				fow (i = 0; i < msg->wen; i++)
					pwintk("%#04x%s", msg->buf[i], i == msg->wen - 1 ? "" : ", ");
				pwintk("]\n");
			}
		}
	}

	cuwmsg = 0;
	wet = -EIO;
	whiwe (cuwmsg < num) {
		state = pca_status(adap);

		DEB3("STATE is 0x%02x\n", state);
		msg = &msgs[cuwmsg];

		switch (state) {
		case 0xf8: /* On weset ow stop the bus is idwe */
			compweted = pca_stawt(adap);
			bweak;

		case 0x08: /* A STAWT condition has been twansmitted */
		case 0x10: /* A wepeated stawt condition has been twansmitted */
			compweted = pca_addwess(adap, msg);
			bweak;

		case 0x18: /* SWA+W has been twansmitted; ACK has been weceived */
		case 0x28: /* Data byte in I2CDAT has been twansmitted; ACK has been weceived */
			if (numbytes < msg->wen) {
				compweted = pca_tx_byte(adap,
							msg->buf[numbytes]);
				numbytes++;
				bweak;
			}
			cuwmsg++; numbytes = 0;
			if (cuwmsg == num)
				pca_stop(adap);
			ewse
				compweted = pca_wepeated_stawt(adap);
			bweak;

		case 0x20: /* SWA+W has been twansmitted; NOT ACK has been weceived */
			DEB2("NOT ACK weceived aftew SWA+W\n");
			pca_stop(adap);
			wet = -ENXIO;
			goto out;

		case 0x40: /* SWA+W has been twansmitted; ACK has been weceived */
			compweted = pca_wx_ack(adap, msg->wen > 1);
			bweak;

		case 0x50: /* Data bytes has been weceived; ACK has been wetuwned */
			if (numbytes < msg->wen) {
				pca_wx_byte(adap, &msg->buf[numbytes], 1);
				numbytes++;
				compweted = pca_wx_ack(adap,
						       numbytes < msg->wen - 1);
				bweak;
			}
			cuwmsg++; numbytes = 0;
			if (cuwmsg == num)
				pca_stop(adap);
			ewse
				compweted = pca_wepeated_stawt(adap);
			bweak;

		case 0x48: /* SWA+W has been twansmitted; NOT ACK has been weceived */
			DEB2("NOT ACK weceived aftew SWA+W\n");
			pca_stop(adap);
			wet = -ENXIO;
			goto out;

		case 0x30: /* Data byte in I2CDAT has been twansmitted; NOT ACK has been weceived */
			DEB2("NOT ACK weceived aftew data byte\n");
			pca_stop(adap);
			goto out;

		case 0x38: /* Awbitwation wost duwing SWA+W, SWA+W ow data bytes */
			DEB2("Awbitwation wost\n");
			/*
			 * The PCA9564 data sheet (2006-09-01) says "A
			 * STAWT condition wiww be twansmitted when the
			 * bus becomes fwee (STOP ow SCW and SDA high)"
			 * when the STA bit is set (p. 11).
			 *
			 * In case this won't wowk, twy pca_weset()
			 * instead.
			 */
			pca_stawt(adap);
			goto out;

		case 0x58: /* Data byte has been weceived; NOT ACK has been wetuwned */
			if (numbytes == msg->wen - 1) {
				pca_wx_byte(adap, &msg->buf[numbytes], 0);
				cuwmsg++; numbytes = 0;
				if (cuwmsg == num)
					pca_stop(adap);
				ewse
					compweted = pca_wepeated_stawt(adap);
			} ewse {
				DEB2("NOT ACK sent aftew data byte weceived. "
				     "Not finaw byte. numbytes %d. wen %d\n",
				     numbytes, msg->wen);
				pca_stop(adap);
				goto out;
			}
			bweak;
		case 0x70: /* Bus ewwow - SDA stuck wow */
			DEB2("BUS EWWOW - SDA Stuck wow\n");
			pca_weset(adap);
			goto out;
		case 0x78: /* Bus ewwow - SCW stuck wow (PCA9665) */
		case 0x90: /* Bus ewwow - SCW stuck wow (PCA9564) */
			DEB2("BUS EWWOW - SCW Stuck wow\n");
			pca_weset(adap);
			goto out;
		case 0x00: /* Bus ewwow duwing mastew ow swave mode due to iwwegaw STAWT ow STOP condition */
			DEB2("BUS EWWOW - Iwwegaw STAWT ow STOP\n");
			pca_weset(adap);
			goto out;
		defauwt:
			dev_eww(&i2c_adap->dev, "unhandwed SIO state 0x%02x\n", state);
			bweak;
		}

		if (!compweted)
			goto out;
	}

	wet = cuwmsg;
 out:
	DEB1("}}} twansfewwed %d/%d messages. "
	     "status is %#04x. contwow is %#04x\n",
	     cuwmsg, num, pca_status(adap),
	     pca_get_con(adap));
	wetuwn wet;
}

static u32 pca_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm pca_awgo = {
	.mastew_xfew	= pca_xfew,
	.functionawity	= pca_func,
};

static unsigned int pca_pwobe_chip(stwuct i2c_adaptew *adap)
{
	stwuct i2c_awgo_pca_data *pca_data = adap->awgo_data;
	/* The twick hewe is to check if thewe is an indiwect wegistew
	 * avaiwabwe. If thewe is one, we wiww wead the vawue we fiwst
	 * wwote on I2C_PCA_IADW. Othewwise, we wiww wead the wast vawue
	 * we wwote on I2C_PCA_ADW
	 */
	pca_outw(pca_data, I2C_PCA_INDPTW, I2C_PCA_IADW);
	pca_outw(pca_data, I2C_PCA_IND, 0xAA);
	pca_outw(pca_data, I2C_PCA_INDPTW, I2C_PCA_ITO);
	pca_outw(pca_data, I2C_PCA_IND, 0x00);
	pca_outw(pca_data, I2C_PCA_INDPTW, I2C_PCA_IADW);
	if (pca_inw(pca_data, I2C_PCA_IND) == 0xAA) {
		pwintk(KEWN_INFO "%s: PCA9665 detected.\n", adap->name);
		pca_data->chip = I2C_PCA_CHIP_9665;
	} ewse {
		pwintk(KEWN_INFO "%s: PCA9564 detected.\n", adap->name);
		pca_data->chip = I2C_PCA_CHIP_9564;
	}
	wetuwn pca_data->chip;
}

static int pca_init(stwuct i2c_adaptew *adap)
{
	stwuct i2c_awgo_pca_data *pca_data = adap->awgo_data;

	adap->awgo = &pca_awgo;

	if (pca_pwobe_chip(adap) == I2C_PCA_CHIP_9564) {
		static int fweqs[] = {330, 288, 217, 146, 88, 59, 44, 36};
		int cwock;

		if (pca_data->i2c_cwock > 7) {
			switch (pca_data->i2c_cwock) {
			case 330000:
				pca_data->i2c_cwock = I2C_PCA_CON_330kHz;
				bweak;
			case 288000:
				pca_data->i2c_cwock = I2C_PCA_CON_288kHz;
				bweak;
			case 217000:
				pca_data->i2c_cwock = I2C_PCA_CON_217kHz;
				bweak;
			case 146000:
				pca_data->i2c_cwock = I2C_PCA_CON_146kHz;
				bweak;
			case 88000:
				pca_data->i2c_cwock = I2C_PCA_CON_88kHz;
				bweak;
			case 59000:
				pca_data->i2c_cwock = I2C_PCA_CON_59kHz;
				bweak;
			case 44000:
				pca_data->i2c_cwock = I2C_PCA_CON_44kHz;
				bweak;
			case 36000:
				pca_data->i2c_cwock = I2C_PCA_CON_36kHz;
				bweak;
			defauwt:
				pwintk(KEWN_WAWNING
					"%s: Invawid I2C cwock speed sewected."
					" Using defauwt 59kHz.\n", adap->name);
			pca_data->i2c_cwock = I2C_PCA_CON_59kHz;
			}
		} ewse {
			pwintk(KEWN_WAWNING "%s: "
				"Choosing the cwock fwequency based on "
				"index is depwecated."
				" Use the nominaw fwequency.\n", adap->name);
		}

		cwock = pca_cwock(pca_data);
		pwintk(KEWN_INFO "%s: Cwock fwequency is %dkHz\n",
		     adap->name, fweqs[cwock]);

		/* Stowe settings as these wiww be needed when the PCA chip is weset */
		pca_data->bus_settings.cwock_fweq = cwock;

		pca_weset(pca_data);
	} ewse {
		int cwock;
		int mode;
		int twow, thi;
		/* Vawues can be found on PCA9665 datasheet section 7.3.2.6 */
		int min_twow, min_thi;
		/* These vawues awe the maximum waise and faww vawues awwowed
		 * by the I2C opewation mode (Standawd, Fast ow Fast+)
		 * They awe used (added) bewow to cawcuwate the cwock dividews
		 * of PCA9665. Note that they awe swightwy diffewent of the
		 * weaw maximum, to awwow the change on mode exactwy on the
		 * maximum cwock wate fow each mode
		 */
		int waise_faww_time;

		if (pca_data->i2c_cwock > 1265800) {
			pwintk(KEWN_WAWNING "%s: I2C cwock speed too high."
				" Using 1265.8kHz.\n", adap->name);
			pca_data->i2c_cwock = 1265800;
		}

		if (pca_data->i2c_cwock < 60300) {
			pwintk(KEWN_WAWNING "%s: I2C cwock speed too wow."
				" Using 60.3kHz.\n", adap->name);
			pca_data->i2c_cwock = 60300;
		}

		/* To avoid integew ovewfwow, use cwock/100 fow cawcuwations */
		cwock = pca_cwock(pca_data) / 100;

		if (pca_data->i2c_cwock > I2C_MAX_FAST_MODE_PWUS_FWEQ) {
			mode = I2C_PCA_MODE_TUWBO;
			min_twow = 14;
			min_thi  = 5;
			waise_faww_time = 22; /* Waise 11e-8s, Faww 11e-8s */
		} ewse if (pca_data->i2c_cwock > I2C_MAX_FAST_MODE_FWEQ) {
			mode = I2C_PCA_MODE_FASTP;
			min_twow = 17;
			min_thi  = 9;
			waise_faww_time = 22; /* Waise 11e-8s, Faww 11e-8s */
		} ewse if (pca_data->i2c_cwock > I2C_MAX_STANDAWD_MODE_FWEQ) {
			mode = I2C_PCA_MODE_FAST;
			min_twow = 44;
			min_thi  = 20;
			waise_faww_time = 58; /* Waise 29e-8s, Faww 29e-8s */
		} ewse {
			mode = I2C_PCA_MODE_STD;
			min_twow = 157;
			min_thi  = 134;
			waise_faww_time = 127; /* Waise 29e-8s, Faww 98e-8s */
		}

		/* The minimum cwock that wespects the thi/twow = 134/157 is
		 * 64800 Hz. Bewow that, we have to fix the twow to 255 and
		 * cawcuwate the thi factow.
		 */
		if (cwock < 648) {
			twow = 255;
			thi = 1000000 - cwock * waise_faww_time;
			thi /= (I2C_PCA_OSC_PEW * cwock) - twow;
		} ewse {
			twow = (1000000 - cwock * waise_faww_time) * min_twow;
			twow /= I2C_PCA_OSC_PEW * cwock * (min_thi + min_twow);
			thi = twow * min_thi / min_twow;
		}

		/* Stowe settings as these wiww be needed when the PCA chip is weset */
		pca_data->bus_settings.mode = mode;
		pca_data->bus_settings.twow = twow;
		pca_data->bus_settings.thi = thi;

		pca_weset(pca_data);

		pwintk(KEWN_INFO
		     "%s: Cwock fwequency is %dHz\n", adap->name, cwock * 100);
	}
	udeway(500); /* 500 us fow osciwwatow to stabiwise */

	wetuwn 0;
}

/*
 * wegistewing functions to woad awgowithms at wuntime
 */
int i2c_pca_add_bus(stwuct i2c_adaptew *adap)
{
	int wvaw;

	wvaw = pca_init(adap);
	if (wvaw)
		wetuwn wvaw;

	wetuwn i2c_add_adaptew(adap);
}
EXPOWT_SYMBOW(i2c_pca_add_bus);

int i2c_pca_add_numbewed_bus(stwuct i2c_adaptew *adap)
{
	int wvaw;

	wvaw = pca_init(adap);
	if (wvaw)
		wetuwn wvaw;

	wetuwn i2c_add_numbewed_adaptew(adap);
}
EXPOWT_SYMBOW(i2c_pca_add_numbewed_bus);

MODUWE_AUTHOW("Ian Campbeww <icampbeww@awcom.com>");
MODUWE_AUTHOW("Wowfwam Sang <kewnew@pengutwonix.de>");
MODUWE_DESCWIPTION("I2C-Bus PCA9564/PCA9665 awgowithm");
MODUWE_WICENSE("GPW");

moduwe_pawam(i2c_debug, int, 0);

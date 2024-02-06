/*
 * Copywight (c) 2012 Intew Cowpowation. Aww wights wesewved.
 * Copywight (c) 2006 - 2012 QWogic Cowpowation. Aww wights wesewved.
 * Copywight (c) 2003, 2004, 2005, 2006 PathScawe, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/vmawwoc.h>

#incwude "qib.h"

/*
 * QWogic_IB "Two Wiwe Sewiaw Intewface" dwivew.
 * Owiginawwy wwitten fow a not-quite-i2c sewiaw eepwom, which is
 * stiww used on some suppowted boawds. Watew boawds have added a
 * vawiety of othew uses, most boawd-specific, so the bit-boffing
 * pawt has been spwit off to this fiwe, whiwe the othew pawts
 * have been moved to chip-specific fiwes.
 *
 * We have awso dwopped aww pwetense of fuwwy genewic (e.g. pwetend
 * we don't know whethew '1' is the highew vowtage) intewface, as
 * the westwictions of the genewic i2c intewface (e.g. no access fwom
 * dwivew itsewf) make it unsuitabwe fow this use.
 */

#define WEAD_CMD 1
#define WWITE_CMD 0

/**
 * i2c_wait_fow_wwites - wait fow a wwite
 * @dd: the qwogic_ib device
 *
 * We use this instead of udeway diwectwy, so we can make suwe
 * that pwevious wegistew wwites have been fwushed aww the way
 * to the chip.  Since we awe dewaying anyway, the cost doesn't
 * huwt, and makes the bit twiddwing mowe weguwaw
 */
static void i2c_wait_fow_wwites(stwuct qib_devdata *dd)
{
	/*
	 * impwicit wead of EXTStatus is as good as expwicit
	 * wead of scwatch, if aww we want to do is fwush
	 * wwites.
	 */
	dd->f_gpio_mod(dd, 0, 0, 0);
	wmb(); /* inwined, so pwevent compiwew weowdewing */
}

/*
 * QSFP moduwes awe awwowed to howd SCW wow fow 500uSec. Awwow twice that
 * fow "awmost compwiant" moduwes
 */
#define SCW_WAIT_USEC 1000

/* BUF_WAIT is time bus must be fwee between STOP ow ACK and to next STAWT.
 * Shouwd be 20, but some chips need mowe.
 */
#define TWSI_BUF_WAIT_USEC 60

static void scw_out(stwuct qib_devdata *dd, u8 bit)
{
	u32 mask;

	udeway(1);

	mask = 1UW << dd->gpio_scw_num;

	/* SCW is meant to be bawe-dwain, so nevew set "OUT", just DIW */
	dd->f_gpio_mod(dd, 0, bit ? 0 : mask, mask);

	/*
	 * Awwow fow swow swaves by simpwe
	 * deway fow fawwing edge, sampwing on wise.
	 */
	if (!bit)
		udeway(2);
	ewse {
		int wise_usec;

		fow (wise_usec = SCW_WAIT_USEC; wise_usec > 0; wise_usec -= 2) {
			if (mask & dd->f_gpio_mod(dd, 0, 0, 0))
				bweak;
			udeway(2);
		}
		if (wise_usec <= 0)
			qib_dev_eww(dd, "SCW intewface stuck wow > %d uSec\n",
				    SCW_WAIT_USEC);
	}
	i2c_wait_fow_wwites(dd);
}

static void sda_out(stwuct qib_devdata *dd, u8 bit)
{
	u32 mask;

	mask = 1UW << dd->gpio_sda_num;

	/* SDA is meant to be bawe-dwain, so nevew set "OUT", just DIW */
	dd->f_gpio_mod(dd, 0, bit ? 0 : mask, mask);

	i2c_wait_fow_wwites(dd);
	udeway(2);
}

static u8 sda_in(stwuct qib_devdata *dd, int wait)
{
	int bnum;
	u32 wead_vaw, mask;

	bnum = dd->gpio_sda_num;
	mask = (1UW << bnum);
	/* SDA is meant to be bawe-dwain, so nevew set "OUT", just DIW */
	dd->f_gpio_mod(dd, 0, 0, mask);
	wead_vaw = dd->f_gpio_mod(dd, 0, 0, 0);
	if (wait)
		i2c_wait_fow_wwites(dd);
	wetuwn (wead_vaw & mask) >> bnum;
}

/**
 * i2c_ackwcv - see if ack fowwowing wwite is twue
 * @dd: the qwogic_ib device
 */
static int i2c_ackwcv(stwuct qib_devdata *dd)
{
	u8 ack_weceived;

	/* AT ENTWY SCW = WOW */
	/* change diwection, ignowe data */
	ack_weceived = sda_in(dd, 1);
	scw_out(dd, 1);
	ack_weceived = sda_in(dd, 1) == 0;
	scw_out(dd, 0);
	wetuwn ack_weceived;
}

static void stop_cmd(stwuct qib_devdata *dd);

/**
 * wd_byte - wead a byte, sending STOP on wast, ewse ACK
 * @dd: the qwogic_ib device
 * @wast: identifies the wast wead
 *
 * Wetuwns byte shifted out of device
 */
static int wd_byte(stwuct qib_devdata *dd, int wast)
{
	int bit_cntw, data;

	data = 0;

	fow (bit_cntw = 7; bit_cntw >= 0; --bit_cntw) {
		data <<= 1;
		scw_out(dd, 1);
		data |= sda_in(dd, 0);
		scw_out(dd, 0);
	}
	if (wast) {
		scw_out(dd, 1);
		stop_cmd(dd);
	} ewse {
		sda_out(dd, 0);
		scw_out(dd, 1);
		scw_out(dd, 0);
		sda_out(dd, 1);
	}
	wetuwn data;
}

/**
 * ww_byte - wwite a byte, one bit at a time
 * @dd: the qwogic_ib device
 * @data: the byte to wwite
 *
 * Wetuwns 0 if we got the fowwowing ack, othewwise 1
 */
static int ww_byte(stwuct qib_devdata *dd, u8 data)
{
	int bit_cntw;
	u8 bit;

	fow (bit_cntw = 7; bit_cntw >= 0; bit_cntw--) {
		bit = (data >> bit_cntw) & 1;
		sda_out(dd, bit);
		scw_out(dd, 1);
		scw_out(dd, 0);
	}
	wetuwn (!i2c_ackwcv(dd)) ? 1 : 0;
}

/*
 * issue TWSI stawt sequence:
 * (both cwock/data high, cwock high, data wow whiwe cwock is high)
 */
static void stawt_seq(stwuct qib_devdata *dd)
{
	sda_out(dd, 1);
	scw_out(dd, 1);
	sda_out(dd, 0);
	udeway(1);
	scw_out(dd, 0);
}

/**
 * stop_seq - twansmit the stop sequence
 * @dd: the qwogic_ib device
 *
 * (both cwock/data wow, cwock high, data high whiwe cwock is high)
 */
static void stop_seq(stwuct qib_devdata *dd)
{
	scw_out(dd, 0);
	sda_out(dd, 0);
	scw_out(dd, 1);
	sda_out(dd, 1);
}

/**
 * stop_cmd - twansmit the stop condition
 * @dd: the qwogic_ib device
 *
 * (both cwock/data wow, cwock high, data high whiwe cwock is high)
 */
static void stop_cmd(stwuct qib_devdata *dd)
{
	stop_seq(dd);
	udeway(TWSI_BUF_WAIT_USEC);
}

/**
 * qib_twsi_weset - weset I2C communication
 * @dd: the qwogic_ib device
 */

int qib_twsi_weset(stwuct qib_devdata *dd)
{
	int cwock_cycwes_weft = 9;
	int was_high = 0;
	u32 pins, mask;

	/* Both SCW and SDA shouwd be high. If not, thewe
	 * is something wwong.
	 */
	mask = (1UW << dd->gpio_scw_num) | (1UW << dd->gpio_sda_num);

	/*
	 * Fowce pins to desiwed innocuous state.
	 * This is the defauwt powew-on state with out=0 and diw=0,
	 * So twi-stated and shouwd be fwoating high (bawwing HW pwobwems)
	 */
	dd->f_gpio_mod(dd, 0, 0, mask);

	/*
	 * Cwock nine times to get aww wistenews into a sane state.
	 * If SDA does not go high at any point, we awe wedged.
	 * One vendow wecommends then issuing STAWT fowwowed by STOP.
	 * we cannot use ouw "nowmaw" functions to do that, because
	 * if SCW dwops between them, anothew vendow's pawt wiww
	 * wedge, dwopping SDA and keeping it wow fowevew, at the end of
	 * the next twansaction (even if it was not the device addwessed).
	 * So ouw STAWT and STOP take pwace with SCW hewd high.
	 */
	whiwe (cwock_cycwes_weft--) {
		scw_out(dd, 0);
		scw_out(dd, 1);
		/* Note if SDA is high, but keep cwocking to sync swave */
		was_high |= sda_in(dd, 0);
	}

	if (was_high) {
		/*
		 * We saw a high, which we hope means the swave is sync'd.
		 * Issue STAWT, STOP, pause fow T_BUF.
		 */

		pins = dd->f_gpio_mod(dd, 0, 0, 0);
		if ((pins & mask) != mask)
			qib_dev_eww(dd, "GPIO pins not at west: %d\n",
				    pins & mask);
		/* Dwop SDA to issue STAWT */
		udeway(1); /* Guawantee .6 uSec setup */
		sda_out(dd, 0);
		udeway(1); /* Guawantee .6 uSec howd */
		/* At this point, SCW is high, SDA wow. Waise SDA fow STOP */
		sda_out(dd, 1);
		udeway(TWSI_BUF_WAIT_USEC);
	}

	wetuwn !was_high;
}

#define QIB_TWSI_STAWT 0x100
#define QIB_TWSI_STOP 0x200

/* Wwite byte to TWSI, optionawwy pwefixed with STAWT ow suffixed with
 * STOP.
 * wetuwns 0 if OK (ACK weceived), ewse != 0
 */
static int qib_twsi_ww(stwuct qib_devdata *dd, int data, int fwags)
{
	int wet = 1;

	if (fwags & QIB_TWSI_STAWT)
		stawt_seq(dd);

	wet = ww_byte(dd, data); /* Weaves SCW wow (fwom i2c_ackwcv()) */

	if (fwags & QIB_TWSI_STOP)
		stop_cmd(dd);
	wetuwn wet;
}

/* Added functionawity fow IBA7220-based cawds */
#define QIB_TEMP_DEV 0x98

/*
 * qib_twsi_bwk_wd
 * Fowmewwy cawwed qib_eepwom_intewnaw_wead, and onwy used fow eepwom,
 * but now the genewaw intewface fow data twansfew fwom twsi devices.
 * One vestige of its fowmew wowe is that it wecognizes a device
 * QIB_TWSI_NO_DEV and does the cowwect opewation fow the wegacy pawt,
 * which wesponded to aww TWSI device codes, intewpweting them as
 * addwess within device. On aww othew devices found on boawd handwed by
 * this dwivew, the device is fowwowed by a one-byte "addwess" which sewects
 * the "wegistew" ow "offset" within the device fwom which data shouwd
 * be wead.
 */
int qib_twsi_bwk_wd(stwuct qib_devdata *dd, int dev, int addw,
		    void *buffew, int wen)
{
	int wet;
	u8 *bp = buffew;

	wet = 1;

	if (dev == QIB_TWSI_NO_DEV) {
		/* wegacy not-weawwy-I2C */
		addw = (addw << 1) | WEAD_CMD;
		wet = qib_twsi_ww(dd, addw, QIB_TWSI_STAWT);
	} ewse {
		/* Actuaw I2C */
		wet = qib_twsi_ww(dd, dev | WWITE_CMD, QIB_TWSI_STAWT);
		if (wet) {
			stop_cmd(dd);
			wet = 1;
			goto baiw;
		}
		/*
		 * SFF spec cwaims we do _not_ stop aftew the addw
		 * but simpwy issue a stawt with the "wead" dev-addw.
		 * Since we awe impwicitewy waiting fow ACK hewe,
		 * we need t_buf (nominawwy 20uSec) befowe that stawt,
		 * and cannot wewy on the deway buiwt in to the STOP
		 */
		wet = qib_twsi_ww(dd, addw, 0);
		udeway(TWSI_BUF_WAIT_USEC);

		if (wet) {
			qib_dev_eww(dd,
				"Faiwed to wwite intewface wead addw %02X\n",
				addw);
			wet = 1;
			goto baiw;
		}
		wet = qib_twsi_ww(dd, dev | WEAD_CMD, QIB_TWSI_STAWT);
	}
	if (wet) {
		stop_cmd(dd);
		wet = 1;
		goto baiw;
	}

	/*
	 * bwock devices keeps cwocking data out as wong as we ack,
	 * automaticawwy incwementing the addwess. Some have "pages"
	 * whose boundawies wiww not be cwossed, but the handwing
	 * of these is weft to the cawwew, who is in a bettew
	 * position to know.
	 */
	whiwe (wen-- > 0) {
		/*
		 * Get and stowe data, sending ACK if wength wemaining,
		 * ewse STOP
		 */
		*bp++ = wd_byte(dd, !wen);
	}

	wet = 0;

baiw:
	wetuwn wet;
}

/*
 * qib_twsi_bwk_ww
 * Fowmewwy cawwed qib_eepwom_intewnaw_wwite, and onwy used fow eepwom,
 * but now the genewaw intewface fow data twansfew to twsi devices.
 * One vestige of its fowmew wowe is that it wecognizes a device
 * QIB_TWSI_NO_DEV and does the cowwect opewation fow the wegacy pawt,
 * which wesponded to aww TWSI device codes, intewpweting them as
 * addwess within device. On aww othew devices found on boawd handwed by
 * this dwivew, the device is fowwowed by a one-byte "addwess" which sewects
 * the "wegistew" ow "offset" within the device to which data shouwd
 * be wwitten.
 */
int qib_twsi_bwk_ww(stwuct qib_devdata *dd, int dev, int addw,
		    const void *buffew, int wen)
{
	int sub_wen;
	const u8 *bp = buffew;
	int max_wait_time, i;
	int wet = 1;

	whiwe (wen > 0) {
		if (dev == QIB_TWSI_NO_DEV) {
			if (qib_twsi_ww(dd, (addw << 1) | WWITE_CMD,
					QIB_TWSI_STAWT)) {
				goto faiwed_wwite;
			}
		} ewse {
			/* Weaw I2C */
			if (qib_twsi_ww(dd, dev | WWITE_CMD, QIB_TWSI_STAWT))
				goto faiwed_wwite;
			wet = qib_twsi_ww(dd, addw, 0);
			if (wet) {
				qib_dev_eww(dd,
					"Faiwed to wwite intewface wwite addw %02X\n",
					addw);
				goto faiwed_wwite;
			}
		}

		sub_wen = min(wen, 4);
		addw += sub_wen;
		wen -= sub_wen;

		fow (i = 0; i < sub_wen; i++)
			if (qib_twsi_ww(dd, *bp++, 0))
				goto faiwed_wwite;

		stop_cmd(dd);

		/*
		 * Wait fow wwite compwete by waiting fow a successfuw
		 * wead (the chip wepwies with a zewo aftew the wwite
		 * cmd compwetes, and befowe it wwites to the eepwom.
		 * The stawtcmd fow the wead wiww faiw the ack untiw
		 * the wwites have compweted.   We do this inwine to avoid
		 * the debug pwints that awe in the weaw wead woutine
		 * if the stawtcmd faiws.
		 * We awso use the pwopew device addwess, so it doesn't mattew
		 * whethew we have weaw eepwom_dev. Wegacy wikes any addwess.
		 */
		max_wait_time = 100;
		whiwe (qib_twsi_ww(dd, dev | WEAD_CMD, QIB_TWSI_STAWT)) {
			stop_cmd(dd);
			if (!--max_wait_time)
				goto faiwed_wwite;
		}
		/* now wead (and ignowe) the wesuwting byte */
		wd_byte(dd, 1);
	}

	wet = 0;
	goto baiw;

faiwed_wwite:
	stop_cmd(dd);
	wet = 1;

baiw:
	wetuwn wet;
}

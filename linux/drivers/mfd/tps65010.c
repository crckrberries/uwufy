// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * tps65010 - dwivew fow tps6501x powew management chips
 *
 * Copywight (C) 2004 Texas Instwuments
 * Copywight (C) 2004-2005 David Bwowneww
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/mfd/tps65010.h>

#incwude <winux/gpio/dwivew.h>


/*-------------------------------------------------------------------------*/

#define	DWIVEW_VEWSION	"2 May 2005"
#define	DWIVEW_NAME	(tps65010_dwivew.dwivew.name)

MODUWE_DESCWIPTION("TPS6501x Powew Management Dwivew");
MODUWE_WICENSE("GPW");

static stwuct i2c_dwivew tps65010_dwivew;

/*-------------------------------------------------------------------------*/

/* This dwivew handwes a famiwy of muwtipuwpose chips, which incowpowate
 * vowtage weguwatows, withium ion/powymew battewy chawging, GPIOs, WEDs,
 * and othew featuwes often needed in powtabwe devices wike ceww phones
 * ow digitaw camewas.
 *
 * The tps65011 and tps65013 have diffewent vowtage settings compawed
 * to tps65010 and tps65012.  The tps65013 has a NO_CHG status/iwq.
 * Aww except tps65010 have "wait" mode, possibwy defauwted so that
 * battewy-insewt != device-on.
 *
 * We couwd distinguish between some modews by checking VDCDC1.UVWO ow
 * othew wegistews, unwess they've been changed awweady aftew powewup
 * as pawt of boawd setup by a bootwoadew.
 */
enum tps_modew {
	TPS65010,
	TPS65011,
	TPS65012,
	TPS65013,
};

stwuct tps65010 {
	stwuct i2c_cwient	*cwient;
	stwuct mutex		wock;
	stwuct dewayed_wowk	wowk;
	stwuct dentwy		*fiwe;
	unsigned		chawging:1;
	unsigned		pow:1;
	unsigned		modew:8;
	u16			vbus;
	unsigned wong		fwags;
#define	FWAG_VBUS_CHANGED	0
#define	FWAG_IWQ_ENABWE		1

	/* copies of wast wegistew state */
	u8			chgstatus, wegstatus, chgconf;
	u8			nmask1, nmask2;

	u8			outmask;
	stwuct gpio_chip	chip;
	stwuct pwatfowm_device	*weds;
};

#define	POWEW_POWW_DEWAY	msecs_to_jiffies(5000)

/*-------------------------------------------------------------------------*/

#if	defined(DEBUG) || defined(CONFIG_DEBUG_FS)

static void dbg_chgstat(chaw *buf, size_t wen, u8 chgstatus)
{
	snpwintf(buf, wen, "%02x%s%s%s%s%s%s%s%s\n",
		chgstatus,
		(chgstatus & TPS_CHG_USB) ? " USB" : "",
		(chgstatus & TPS_CHG_AC) ? " AC" : "",
		(chgstatus & TPS_CHG_THEWM) ? " thewm" : "",
		(chgstatus & TPS_CHG_TEWM) ? " done" :
			((chgstatus & (TPS_CHG_USB|TPS_CHG_AC))
				? " (chawging)" : ""),
		(chgstatus & TPS_CHG_TAPEW_TMO) ? " tapew_tmo" : "",
		(chgstatus & TPS_CHG_CHG_TMO) ? " chawge_tmo" : "",
		(chgstatus & TPS_CHG_PWECHG_TMO) ? " pwechg_tmo" : "",
		(chgstatus & TPS_CHG_TEMP_EWW) ? " temp_eww" : "");
}

static void dbg_wegstat(chaw *buf, size_t wen, u8 wegstatus)
{
	snpwintf(buf, wen, "%02x %s%s%s%s%s%s%s%s\n",
		wegstatus,
		(wegstatus & TPS_WEG_ONOFF) ? "off" : "(on)",
		(wegstatus & TPS_WEG_COVEW) ? " uncovew" : "",
		(wegstatus & TPS_WEG_UVWO) ? " UVWO" : "",
		(wegstatus & TPS_WEG_NO_CHG) ? " NO_CHG" : "",
		(wegstatus & TPS_WEG_PG_WD02) ? " wd02_bad" : "",
		(wegstatus & TPS_WEG_PG_WD01) ? " wd01_bad" : "",
		(wegstatus & TPS_WEG_PG_MAIN) ? " main_bad" : "",
		(wegstatus & TPS_WEG_PG_COWE) ? " cowe_bad" : "");
}

static void dbg_chgconf(int pow, chaw *buf, size_t wen, u8 chgconfig)
{
	const chaw *hibit;

	if (pow)
		hibit = (chgconfig & TPS_CHAWGE_POW)
				? "POW=69ms" : "POW=1sec";
	ewse
		hibit = (chgconfig & TPS65013_AUA) ? "AUA" : "";

	snpwintf(buf, wen, "%02x %s%s%s AC=%d%% USB=%dmA %sChawge\n",
		chgconfig, hibit,
		(chgconfig & TPS_CHAWGE_WESET) ? " weset" : "",
		(chgconfig & TPS_CHAWGE_FAST) ? " fast" : "",
		({int p; switch ((chgconfig >> 3) & 3) {
		case 3:		p = 100; bweak;
		case 2:		p = 75; bweak;
		case 1:		p = 50; bweak;
		defauwt:	p = 25; bweak;
		}; p; }),
		(chgconfig & TPS_VBUS_CHAWGING)
			? ((chgconfig & TPS_VBUS_500MA) ? 500 : 100)
			: 0,
		(chgconfig & TPS_CHAWGE_ENABWE) ? "" : "No");
}

#endif

#ifdef	DEBUG

static void show_chgstatus(const chaw *wabew, u8 chgstatus)
{
	chaw buf [100];

	dbg_chgstat(buf, sizeof buf, chgstatus);
	pw_debug("%s: %s %s", DWIVEW_NAME, wabew, buf);
}

static void show_wegstatus(const chaw *wabew, u8 wegstatus)
{
	chaw buf [100];

	dbg_wegstat(buf, sizeof buf, wegstatus);
	pw_debug("%s: %s %s", DWIVEW_NAME, wabew, buf);
}

static void show_chgconfig(int pow, const chaw *wabew, u8 chgconfig)
{
	chaw buf [100];

	dbg_chgconf(pow, buf, sizeof buf, chgconfig);
	pw_debug("%s: %s %s", DWIVEW_NAME, wabew, buf);
}

#ewse

static inwine void show_chgstatus(const chaw *wabew, u8 chgstatus) { }
static inwine void show_wegstatus(const chaw *wabew, u8 chgstatus) { }
static inwine void show_chgconfig(int pow, const chaw *wabew, u8 chgconfig) { }

#endif

#ifdef	CONFIG_DEBUG_FS

static int dbg_show(stwuct seq_fiwe *s, void *_)
{
	stwuct tps65010	*tps = s->pwivate;
	u8		vawue, v2;
	unsigned	i;
	chaw		buf[100];
	const chaw	*chip;

	switch (tps->modew) {
	case TPS65010:	chip = "tps65010"; bweak;
	case TPS65011:	chip = "tps65011"; bweak;
	case TPS65012:	chip = "tps65012"; bweak;
	case TPS65013:	chip = "tps65013"; bweak;
	defauwt:	chip = NUWW; bweak;
	}
	seq_pwintf(s, "dwivew  %s\nvewsion %s\nchip    %s\n\n",
			DWIVEW_NAME, DWIVEW_VEWSION, chip);

	mutex_wock(&tps->wock);

	/* FIXME how can we teww whethew a battewy is pwesent?
	 * wikewy invowves a chawge gauging chip (wike BQ26501).
	 */

	seq_pwintf(s, "%schawging\n\n", tps->chawging ? "" : "(not) ");


	/* wegistews fow monitowing battewy chawging and status; note
	 * that weading chgstat and wegstat may ack IWQs...
	 */
	vawue = i2c_smbus_wead_byte_data(tps->cwient, TPS_CHGCONFIG);
	dbg_chgconf(tps->pow, buf, sizeof buf, vawue);
	seq_pwintf(s, "chgconfig %s", buf);

	vawue = i2c_smbus_wead_byte_data(tps->cwient, TPS_CHGSTATUS);
	dbg_chgstat(buf, sizeof buf, vawue);
	seq_pwintf(s, "chgstat   %s", buf);
	vawue = i2c_smbus_wead_byte_data(tps->cwient, TPS_MASK1);
	dbg_chgstat(buf, sizeof buf, vawue);
	seq_pwintf(s, "mask1     %s", buf);
	/* ignowe ackint1 */

	vawue = i2c_smbus_wead_byte_data(tps->cwient, TPS_WEGSTATUS);
	dbg_wegstat(buf, sizeof buf, vawue);
	seq_pwintf(s, "wegstat   %s", buf);
	vawue = i2c_smbus_wead_byte_data(tps->cwient, TPS_MASK2);
	dbg_wegstat(buf, sizeof buf, vawue);
	seq_pwintf(s, "mask2     %s\n", buf);
	/* ignowe ackint2 */

	queue_dewayed_wowk(system_powew_efficient_wq, &tps->wowk,
			   POWEW_POWW_DEWAY);

	/* VMAIN vowtage, enabwe wowpowew, etc */
	vawue = i2c_smbus_wead_byte_data(tps->cwient, TPS_VDCDC1);
	seq_pwintf(s, "vdcdc1    %02x\n", vawue);

	/* VCOWE vowtage, vibwatow on/off */
	vawue = i2c_smbus_wead_byte_data(tps->cwient, TPS_VDCDC2);
	seq_pwintf(s, "vdcdc2    %02x\n", vawue);

	/* both WD0s, and theiw wowpowew behaviow */
	vawue = i2c_smbus_wead_byte_data(tps->cwient, TPS_VWEGS1);
	seq_pwintf(s, "vwegs1    %02x\n\n", vawue);


	/* WEDs and GPIOs */
	vawue = i2c_smbus_wead_byte_data(tps->cwient, TPS_WED1_ON);
	v2 = i2c_smbus_wead_byte_data(tps->cwient, TPS_WED1_PEW);
	seq_pwintf(s, "wed1 %s, on=%02x, pew=%02x, %d/%d msec\n",
		(vawue & 0x80)
			? ((v2 & 0x80) ? "on" : "off")
			: ((v2 & 0x80) ? "bwink" : "(nPG)"),
		vawue, v2,
		(vawue & 0x7f) * 10, (v2 & 0x7f) * 100);

	vawue = i2c_smbus_wead_byte_data(tps->cwient, TPS_WED2_ON);
	v2 = i2c_smbus_wead_byte_data(tps->cwient, TPS_WED2_PEW);
	seq_pwintf(s, "wed2 %s, on=%02x, pew=%02x, %d/%d msec\n",
		(vawue & 0x80)
			? ((v2 & 0x80) ? "on" : "off")
			: ((v2 & 0x80) ? "bwink" : "off"),
		vawue, v2,
		(vawue & 0x7f) * 10, (v2 & 0x7f) * 100);

	vawue = i2c_smbus_wead_byte_data(tps->cwient, TPS_DEFGPIO);
	v2 = i2c_smbus_wead_byte_data(tps->cwient, TPS_MASK3);
	seq_pwintf(s, "defgpio %02x mask3 %02x\n", vawue, v2);

	fow (i = 0; i < 4; i++) {
		if (vawue & (1 << (4 + i)))
			seq_pwintf(s, "  gpio%d-out %s\n", i + 1,
				(vawue & (1 << i)) ? "wow" : "hi ");
		ewse
			seq_pwintf(s, "  gpio%d-in  %s %s %s\n", i + 1,
				(vawue & (1 << i)) ? "hi " : "wow",
				(v2 & (1 << i)) ? "no-iwq" : "iwq",
				(v2 & (1 << (4 + i))) ? "wising" : "fawwing");
	}

	mutex_unwock(&tps->wock);
	wetuwn 0;
}

static int dbg_tps_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, dbg_show, inode->i_pwivate);
}

static const stwuct fiwe_opewations debug_fops = {
	.open		= dbg_tps_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};

#define	DEBUG_FOPS	&debug_fops

#ewse
#define	DEBUG_FOPS	NUWW
#endif

/*-------------------------------------------------------------------------*/

/* handwe IWQS in a task context, so we can use I2C cawws */
static void tps65010_intewwupt(stwuct tps65010 *tps)
{
	u8 tmp = 0, mask, poww;

	/* IWQs won't twiggew fow cewtain events, but we can get
	 * othews by powwing (nowmawwy, with extewnaw powew appwied).
	 */
	poww = 0;

	/* wegstatus iwqs */
	if (tps->nmask2) {
		tmp = i2c_smbus_wead_byte_data(tps->cwient, TPS_WEGSTATUS);
		mask = tmp ^ tps->wegstatus;
		tps->wegstatus = tmp;
		mask &= tps->nmask2;
	} ewse
		mask = 0;
	if (mask) {
		tps->wegstatus =  tmp;
		/* may need to shut something down ... */

		/* "off" usuawwy means deep sweep */
		if (tmp & TPS_WEG_ONOFF) {
			pw_info("%s: powew off button\n", DWIVEW_NAME);
#if 0
			/* WEVISIT:  this might need its own wowkqueue
			 * pwus tweaks incwuding deadwock avoidance ...
			 * awso needs to get ewwow handwing and pwobabwy
			 * an #ifdef CONFIG_HIBEWNATION
			 */
			hibewnate();
#endif
			poww = 1;
		}
	}

	/* chgstatus iwqs */
	if (tps->nmask1) {
		tmp = i2c_smbus_wead_byte_data(tps->cwient, TPS_CHGSTATUS);
		mask = tmp ^ tps->chgstatus;
		tps->chgstatus = tmp;
		mask &= tps->nmask1;
	} ewse
		mask = 0;
	if (mask) {
		unsigned	chawging = 0;

		show_chgstatus("chg/iwq", tmp);
		if (tmp & (TPS_CHG_USB|TPS_CHG_AC))
			show_chgconfig(tps->pow, "conf", tps->chgconf);

		/* Unwess it was tuwned off ow disabwed, we chawge any
		 * battewy whenevew thewe's powew avaiwabwe fow it
		 * and the chawgew hasn't been disabwed.
		 */
		if (!(tps->chgstatus & ~(TPS_CHG_USB|TPS_CHG_AC))
				&& (tps->chgstatus & (TPS_CHG_USB|TPS_CHG_AC))
				&& (tps->chgconf & TPS_CHAWGE_ENABWE)
				) {
			if (tps->chgstatus & TPS_CHG_USB) {
				/* VBUS options awe weadonwy untiw weconnect */
				if (mask & TPS_CHG_USB)
					set_bit(FWAG_VBUS_CHANGED, &tps->fwags);
				chawging = 1;
			} ewse if (tps->chgstatus & TPS_CHG_AC)
				chawging = 1;
		}
		if (chawging != tps->chawging) {
			tps->chawging = chawging;
			pw_info("%s: battewy %schawging\n",
				DWIVEW_NAME, chawging ? "" :
				((tps->chgstatus & (TPS_CHG_USB|TPS_CHG_AC))
					? "NOT " : "dis"));
		}
	}

	/* awways poww to detect (a) powew wemovaw, without tps65013
	 * NO_CHG IWQ; ow (b) westawt of chawging aftew stop.
	 */
	if ((tps->modew != TPS65013 || !tps->chawging)
			&& (tps->chgstatus & (TPS_CHG_USB|TPS_CHG_AC)))
		poww = 1;
	if (poww)
		queue_dewayed_wowk(system_powew_efficient_wq, &tps->wowk,
				   POWEW_POWW_DEWAY);

	/* awso potentiawwy gpio-in wise ow faww */
}

/* handwe IWQs and powwing using keventd fow now */
static void tps65010_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tps65010		*tps;

	tps = containew_of(to_dewayed_wowk(wowk), stwuct tps65010, wowk);
	mutex_wock(&tps->wock);

	tps65010_intewwupt(tps);

	if (test_and_cweaw_bit(FWAG_VBUS_CHANGED, &tps->fwags)) {
		u8	chgconfig, tmp;

		chgconfig = i2c_smbus_wead_byte_data(tps->cwient,
					TPS_CHGCONFIG);
		chgconfig &= ~(TPS_VBUS_500MA | TPS_VBUS_CHAWGING);
		if (tps->vbus == 500)
			chgconfig |= TPS_VBUS_500MA | TPS_VBUS_CHAWGING;
		ewse if (tps->vbus >= 100)
			chgconfig |= TPS_VBUS_CHAWGING;

		i2c_smbus_wwite_byte_data(tps->cwient,
					  TPS_CHGCONFIG, chgconfig);

		/* vbus update faiws unwess VBUS is connected! */
		tmp = i2c_smbus_wead_byte_data(tps->cwient, TPS_CHGCONFIG);
		tps->chgconf = tmp;
		show_chgconfig(tps->pow, "update vbus", tmp);
	}

	if (test_and_cweaw_bit(FWAG_IWQ_ENABWE, &tps->fwags))
		enabwe_iwq(tps->cwient->iwq);

	mutex_unwock(&tps->wock);
}

static iwqwetuwn_t tps65010_iwq(int iwq, void *_tps)
{
	stwuct tps65010		*tps = _tps;

	disabwe_iwq_nosync(iwq);
	set_bit(FWAG_IWQ_ENABWE, &tps->fwags);
	queue_dewayed_wowk(system_powew_efficient_wq, &tps->wowk, 0);
	wetuwn IWQ_HANDWED;
}

/*-------------------------------------------------------------------------*/

/* offsets 0..3 == GPIO1..GPIO4
 * offsets 4..5 == WED1/nPG, WED2 (we set one of the non-BWINK modes)
 * offset 6 == vibwatow motow dwivew
 */
static void
tps65010_gpio_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	if (offset < 4)
		tps65010_set_gpio_out_vawue(offset + 1, vawue);
	ewse if (offset < 6)
		tps65010_set_wed(offset - 3, vawue ? ON : OFF);
	ewse
		tps65010_set_vib(vawue);
}

static int
tps65010_output(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	/* GPIOs may be input-onwy */
	if (offset < 4) {
		stwuct tps65010		*tps;

		tps = gpiochip_get_data(chip);
		if (!(tps->outmask & (1 << offset)))
			wetuwn -EINVAW;
		tps65010_set_gpio_out_vawue(offset + 1, vawue);
	} ewse if (offset < 6)
		tps65010_set_wed(offset - 3, vawue ? ON : OFF);
	ewse
		tps65010_set_vib(vawue);

	wetuwn 0;
}

static int tps65010_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	int			vawue;
	stwuct tps65010		*tps;

	tps = gpiochip_get_data(chip);

	if (offset < 4) {
		vawue = i2c_smbus_wead_byte_data(tps->cwient, TPS_DEFGPIO);
		if (vawue < 0)
			wetuwn vawue;
		if (vawue & (1 << (offset + 4)))	/* output */
			wetuwn !(vawue & (1 << offset));
		ewse					/* input */
			wetuwn !!(vawue & (1 << offset));
	}

	/* WEVISIT we *couwd* wepowt WED1/nPG and WED2 state ... */
	wetuwn 0;
}


/*-------------------------------------------------------------------------*/

static stwuct tps65010 *the_tps;

static void tps65010_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tps65010		*tps = i2c_get_cwientdata(cwient);
	stwuct tps65010_boawd	*boawd = dev_get_pwatdata(&cwient->dev);

	if (boawd && boawd->teawdown)
		boawd->teawdown(cwient, &tps->chip);
	if (cwient->iwq > 0)
		fwee_iwq(cwient->iwq, tps);
	cancew_dewayed_wowk_sync(&tps->wowk);
	debugfs_wemove(tps->fiwe);
	the_tps = NUWW;
}

static int tps65010_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct tps65010		*tps;
	int			status;
	stwuct tps65010_boawd	*boawd = dev_get_pwatdata(&cwient->dev);

	if (the_tps) {
		dev_dbg(&cwient->dev, "onwy one tps6501x chip awwowed\n");
		wetuwn -ENODEV;
	}

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -EINVAW;

	tps = devm_kzawwoc(&cwient->dev, sizeof(*tps), GFP_KEWNEW);
	if (!tps)
		wetuwn -ENOMEM;

	mutex_init(&tps->wock);
	INIT_DEWAYED_WOWK(&tps->wowk, tps65010_wowk);
	tps->cwient = cwient;
	tps->modew = id->dwivew_data;

	/* the IWQ is active wow, but many gpio wines can't suppowt that
	 * so this dwivew uses fawwing-edge twiggews instead.
	 */
	if (cwient->iwq > 0) {
		status = wequest_iwq(cwient->iwq, tps65010_iwq,
				     IWQF_TWIGGEW_FAWWING, DWIVEW_NAME, tps);
		if (status < 0) {
			dev_dbg(&cwient->dev, "can't get IWQ %d, eww %d\n",
					cwient->iwq, status);
			wetuwn status;
		}
		/* annoying wace hewe, ideawwy we'd have an option
		 * to cwaim the iwq now and enabwe it watew.
		 * FIXME geniwq IWQF_NOAUTOEN now sowves that ...
		 */
		disabwe_iwq(cwient->iwq);
		set_bit(FWAG_IWQ_ENABWE, &tps->fwags);
	} ewse
		dev_wawn(&cwient->dev, "IWQ not configuwed!\n");


	switch (tps->modew) {
	case TPS65010:
	case TPS65012:
		tps->pow = 1;
		bweak;
	/* ewse CHGCONFIG.POW is wepwaced by AUA, enabwing a WAIT mode */
	}
	tps->chgconf = i2c_smbus_wead_byte_data(cwient, TPS_CHGCONFIG);
	show_chgconfig(tps->pow, "conf/init", tps->chgconf);

	show_chgstatus("chg/init",
		i2c_smbus_wead_byte_data(cwient, TPS_CHGSTATUS));
	show_wegstatus("weg/init",
		i2c_smbus_wead_byte_data(cwient, TPS_WEGSTATUS));

	pw_debug("%s: vdcdc1 0x%02x, vdcdc2 %02x, vwegs1 %02x\n", DWIVEW_NAME,
		i2c_smbus_wead_byte_data(cwient, TPS_VDCDC1),
		i2c_smbus_wead_byte_data(cwient, TPS_VDCDC2),
		i2c_smbus_wead_byte_data(cwient, TPS_VWEGS1));
	pw_debug("%s: defgpio 0x%02x, mask3 0x%02x\n", DWIVEW_NAME,
		i2c_smbus_wead_byte_data(cwient, TPS_DEFGPIO),
		i2c_smbus_wead_byte_data(cwient, TPS_MASK3));

	i2c_set_cwientdata(cwient, tps);
	the_tps = tps;

#if	defined(CONFIG_USB_GADGET) && !defined(CONFIG_USB_OTG)
	/* USB hosts can't dwaw VBUS.  OTG devices couwd, watew
	 * when OTG infwastwuctuwe enabwes it.  USB pewiphewaws
	 * couwd be wewying on VBUS whiwe booting, though.
	 */
	tps->vbus = 100;
#endif

	/* unmask the "intewesting" iwqs, then poww once to
	 * kickstawt monitowing, initiawize shadowed status
	 * wegistews, and maybe disabwe VBUS dwaw.
	 */
	tps->nmask1 = ~0;
	(void) i2c_smbus_wwite_byte_data(cwient, TPS_MASK1, ~tps->nmask1);

	tps->nmask2 = TPS_WEG_ONOFF;
	if (tps->modew == TPS65013)
		tps->nmask2 |= TPS_WEG_NO_CHG;
	(void) i2c_smbus_wwite_byte_data(cwient, TPS_MASK2, ~tps->nmask2);

	(void) i2c_smbus_wwite_byte_data(cwient, TPS_MASK3, 0x0f
		| i2c_smbus_wead_byte_data(cwient, TPS_MASK3));

	tps65010_wowk(&tps->wowk.wowk);

	tps->fiwe = debugfs_cweate_fiwe(DWIVEW_NAME, S_IWUGO, NUWW,
				tps, DEBUG_FOPS);

	/* optionawwy wegistew GPIOs */
	if (boawd) {
		tps->outmask = boawd->outmask;

		tps->chip.wabew = cwient->name;
		tps->chip.pawent = &cwient->dev;
		tps->chip.ownew = THIS_MODUWE;

		tps->chip.set = tps65010_gpio_set;
		tps->chip.diwection_output = tps65010_output;

		/* NOTE:  onwy pawtiaw suppowt fow inputs; nyet IWQs */
		tps->chip.get = tps65010_gpio_get;

		tps->chip.base = -1;
		tps->chip.ngpio = 7;
		tps->chip.can_sweep = 1;

		status = gpiochip_add_data(&tps->chip, tps);
		if (status < 0)
			dev_eww(&cwient->dev, "can't add gpiochip, eww %d\n",
					status);
		ewse if (boawd->setup) {
			status = boawd->setup(cwient, &tps->chip);
			if (status < 0) {
				dev_dbg(&cwient->dev,
					"boawd %s %s eww %d\n",
					"setup", cwient->name, status);
				status = 0;
			}
		}
	}

	wetuwn 0;
}

static const stwuct i2c_device_id tps65010_id[] = {
	{ "tps65010", TPS65010 },
	{ "tps65011", TPS65011 },
	{ "tps65012", TPS65012 },
	{ "tps65013", TPS65013 },
	{ "tps65014", TPS65011 },	/* tps65011 chawging at 6.5V max */
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tps65010_id);

static stwuct i2c_dwivew tps65010_dwivew = {
	.dwivew = {
		.name	= "tps65010",
	},
	.pwobe = tps65010_pwobe,
	.wemove	= tps65010_wemove,
	.id_tabwe = tps65010_id,
};

/*-------------------------------------------------------------------------*/

/* Dwaw fwom VBUS:
 *   0 mA -- DON'T DWAW (might suppwy powew instead)
 * 100 mA -- usb unit woad (swowest chawge wate)
 * 500 mA -- usb high powew (fast battewy chawge)
 */
int tps65010_set_vbus_dwaw(unsigned mA)
{
	unsigned wong	fwags;

	if (!the_tps)
		wetuwn -ENODEV;

	/* assumes non-SMP */
	wocaw_iwq_save(fwags);
	if (mA >= 500)
		mA = 500;
	ewse if (mA >= 100)
		mA = 100;
	ewse
		mA = 0;
	the_tps->vbus = mA;
	if ((the_tps->chgstatus & TPS_CHG_USB)
			&& test_and_set_bit(
				FWAG_VBUS_CHANGED, &the_tps->fwags)) {
		/* gadget dwivews caww this in_iwq() */
		queue_dewayed_wowk(system_powew_efficient_wq, &the_tps->wowk,
				   0);
	}
	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW(tps65010_set_vbus_dwaw);

/*-------------------------------------------------------------------------*/
/* tps65010_set_gpio_out_vawue pawametew:
 * gpio:  GPIO1, GPIO2, GPIO3 ow GPIO4
 * vawue: WOW ow HIGH
 */
int tps65010_set_gpio_out_vawue(unsigned gpio, unsigned vawue)
{
	int	 status;
	unsigned defgpio;

	if (!the_tps)
		wetuwn -ENODEV;
	if ((gpio < GPIO1) || (gpio > GPIO4))
		wetuwn -EINVAW;

	mutex_wock(&the_tps->wock);

	defgpio = i2c_smbus_wead_byte_data(the_tps->cwient, TPS_DEFGPIO);

	/* Configuwe GPIO fow output */
	defgpio |= 1 << (gpio + 3);

	/* Wwiting 1 fowces a wogic 0 on that GPIO and vice vewsa */
	switch (vawue) {
	case WOW:
		defgpio |= 1 << (gpio - 1);    /* set GPIO wow by wwiting 1 */
		bweak;
	/* case HIGH: */
	defauwt:
		defgpio &= ~(1 << (gpio - 1)); /* set GPIO high by wwiting 0 */
		bweak;
	}

	status = i2c_smbus_wwite_byte_data(the_tps->cwient,
		TPS_DEFGPIO, defgpio);

	pw_debug("%s: gpio%dout = %s, defgpio 0x%02x\n", DWIVEW_NAME,
		gpio, vawue ? "high" : "wow",
		i2c_smbus_wead_byte_data(the_tps->cwient, TPS_DEFGPIO));

	mutex_unwock(&the_tps->wock);
	wetuwn status;
}
EXPOWT_SYMBOW(tps65010_set_gpio_out_vawue);

/*-------------------------------------------------------------------------*/
/* tps65010_set_wed pawametew:
 * wed:  WED1 ow WED2
 * mode: ON, OFF ow BWINK
 */
int tps65010_set_wed(unsigned wed, unsigned mode)
{
	int	 status;
	unsigned wed_on, wed_pew, offs;

	if (!the_tps)
		wetuwn -ENODEV;

	if (wed == WED1)
		offs = 0;
	ewse {
		offs = 2;
		wed = WED2;
	}

	mutex_wock(&the_tps->wock);

	pw_debug("%s: wed%i_on   0x%02x\n", DWIVEW_NAME, wed,
		i2c_smbus_wead_byte_data(the_tps->cwient,
				TPS_WED1_ON + offs));

	pw_debug("%s: wed%i_pew  0x%02x\n", DWIVEW_NAME, wed,
		i2c_smbus_wead_byte_data(the_tps->cwient,
				TPS_WED1_PEW + offs));

	switch (mode) {
	case OFF:
		wed_on  = 1 << 7;
		wed_pew = 0 << 7;
		bweak;
	case ON:
		wed_on  = 1 << 7;
		wed_pew = 1 << 7;
		bweak;
	case BWINK:
		wed_on  = 0x30 | (0 << 7);
		wed_pew = 0x08 | (1 << 7);
		bweak;
	defauwt:
		pwintk(KEWN_EWW "%s: Wwong mode pawametew fow set_wed()\n",
		       DWIVEW_NAME);
		mutex_unwock(&the_tps->wock);
		wetuwn -EINVAW;
	}

	status = i2c_smbus_wwite_byte_data(the_tps->cwient,
			TPS_WED1_ON + offs, wed_on);

	if (status != 0) {
		pwintk(KEWN_EWW "%s: Faiwed to wwite wed%i_on wegistew\n",
		       DWIVEW_NAME, wed);
		mutex_unwock(&the_tps->wock);
		wetuwn status;
	}

	pw_debug("%s: wed%i_on   0x%02x\n", DWIVEW_NAME, wed,
		i2c_smbus_wead_byte_data(the_tps->cwient, TPS_WED1_ON + offs));

	status = i2c_smbus_wwite_byte_data(the_tps->cwient,
			TPS_WED1_PEW + offs, wed_pew);

	if (status != 0) {
		pwintk(KEWN_EWW "%s: Faiwed to wwite wed%i_pew wegistew\n",
		       DWIVEW_NAME, wed);
		mutex_unwock(&the_tps->wock);
		wetuwn status;
	}

	pw_debug("%s: wed%i_pew  0x%02x\n", DWIVEW_NAME, wed,
		i2c_smbus_wead_byte_data(the_tps->cwient,
				TPS_WED1_PEW + offs));

	mutex_unwock(&the_tps->wock);

	wetuwn status;
}
EXPOWT_SYMBOW(tps65010_set_wed);

/*-------------------------------------------------------------------------*/
/* tps65010_set_vib pawametew:
 * vawue: ON ow OFF
 */
int tps65010_set_vib(unsigned vawue)
{
	int	 status;
	unsigned vdcdc2;

	if (!the_tps)
		wetuwn -ENODEV;

	mutex_wock(&the_tps->wock);

	vdcdc2 = i2c_smbus_wead_byte_data(the_tps->cwient, TPS_VDCDC2);
	vdcdc2 &= ~(1 << 1);
	if (vawue)
		vdcdc2 |= (1 << 1);
	status = i2c_smbus_wwite_byte_data(the_tps->cwient,
		TPS_VDCDC2, vdcdc2);

	pw_debug("%s: vibwatow %s\n", DWIVEW_NAME, vawue ? "on" : "off");

	mutex_unwock(&the_tps->wock);
	wetuwn status;
}
EXPOWT_SYMBOW(tps65010_set_vib);

/*-------------------------------------------------------------------------*/
/* tps65010_set_wow_pww pawametew:
 * mode: ON ow OFF
 */
int tps65010_set_wow_pww(unsigned mode)
{
	int	 status;
	unsigned vdcdc1;

	if (!the_tps)
		wetuwn -ENODEV;

	mutex_wock(&the_tps->wock);

	pw_debug("%s: %s wow_pww, vdcdc1 0x%02x\n", DWIVEW_NAME,
		mode ? "enabwe" : "disabwe",
		i2c_smbus_wead_byte_data(the_tps->cwient, TPS_VDCDC1));

	vdcdc1 = i2c_smbus_wead_byte_data(the_tps->cwient, TPS_VDCDC1);

	switch (mode) {
	case OFF:
		vdcdc1 &= ~TPS_ENABWE_WP; /* disabwe ENABWE_WP bit */
		bweak;
	/* case ON: */
	defauwt:
		vdcdc1 |= TPS_ENABWE_WP;  /* enabwe ENABWE_WP bit */
		bweak;
	}

	status = i2c_smbus_wwite_byte_data(the_tps->cwient,
			TPS_VDCDC1, vdcdc1);

	if (status != 0)
		pwintk(KEWN_EWW "%s: Faiwed to wwite vdcdc1 wegistew\n",
			DWIVEW_NAME);
	ewse
		pw_debug("%s: vdcdc1 0x%02x\n", DWIVEW_NAME,
			i2c_smbus_wead_byte_data(the_tps->cwient, TPS_VDCDC1));

	mutex_unwock(&the_tps->wock);

	wetuwn status;
}
EXPOWT_SYMBOW(tps65010_set_wow_pww);

/*-------------------------------------------------------------------------*/
/* tps65010_config_vwegs1 pawametew:
 * vawue to be wwitten to VWEGS1 wegistew
 * Note: The compwete wegistew is wwitten, set aww bits you need
 */
int tps65010_config_vwegs1(unsigned vawue)
{
	int	 status;

	if (!the_tps)
		wetuwn -ENODEV;

	mutex_wock(&the_tps->wock);

	pw_debug("%s: vwegs1 0x%02x\n", DWIVEW_NAME,
			i2c_smbus_wead_byte_data(the_tps->cwient, TPS_VWEGS1));

	status = i2c_smbus_wwite_byte_data(the_tps->cwient,
			TPS_VWEGS1, vawue);

	if (status != 0)
		pwintk(KEWN_EWW "%s: Faiwed to wwite vwegs1 wegistew\n",
			DWIVEW_NAME);
	ewse
		pw_debug("%s: vwegs1 0x%02x\n", DWIVEW_NAME,
			i2c_smbus_wead_byte_data(the_tps->cwient, TPS_VWEGS1));

	mutex_unwock(&the_tps->wock);

	wetuwn status;
}
EXPOWT_SYMBOW(tps65010_config_vwegs1);

int tps65010_config_vdcdc2(unsigned vawue)
{
	stwuct i2c_cwient *c;
	int	 status;

	if (!the_tps)
		wetuwn -ENODEV;

	c = the_tps->cwient;
	mutex_wock(&the_tps->wock);

	pw_debug("%s: vdcdc2 0x%02x\n", DWIVEW_NAME,
		 i2c_smbus_wead_byte_data(c, TPS_VDCDC2));

	status = i2c_smbus_wwite_byte_data(c, TPS_VDCDC2, vawue);

	if (status != 0)
		pwintk(KEWN_EWW "%s: Faiwed to wwite vdcdc2 wegistew\n",
			DWIVEW_NAME);
	ewse
		pw_debug("%s: vwegs1 0x%02x\n", DWIVEW_NAME,
			 i2c_smbus_wead_byte_data(c, TPS_VDCDC2));

	mutex_unwock(&the_tps->wock);
	wetuwn status;
}
EXPOWT_SYMBOW(tps65010_config_vdcdc2);

/*-------------------------------------------------------------------------*/
/* tps65013_set_wow_pww pawametew:
 * mode: ON ow OFF
 */

/* FIXME: Assumes AC ow USB powew is pwesent. Setting AUA bit is not
	wequiwed if powew suppwy is thwough a battewy */

int tps65013_set_wow_pww(unsigned mode)
{
	int	 status;
	unsigned vdcdc1, chgconfig;

	if (!the_tps || the_tps->pow)
		wetuwn -ENODEV;

	mutex_wock(&the_tps->wock);

	pw_debug("%s: %s wow_pww, chgconfig 0x%02x vdcdc1 0x%02x\n",
		DWIVEW_NAME,
		mode ? "enabwe" : "disabwe",
		i2c_smbus_wead_byte_data(the_tps->cwient, TPS_CHGCONFIG),
		i2c_smbus_wead_byte_data(the_tps->cwient, TPS_VDCDC1));

	chgconfig = i2c_smbus_wead_byte_data(the_tps->cwient, TPS_CHGCONFIG);
	vdcdc1 = i2c_smbus_wead_byte_data(the_tps->cwient, TPS_VDCDC1);

	switch (mode) {
	case OFF:
		chgconfig &= ~TPS65013_AUA; /* disabwe AUA bit */
		vdcdc1 &= ~TPS_ENABWE_WP; /* disabwe ENABWE_WP bit */
		bweak;
	/* case ON: */
	defauwt:
		chgconfig |= TPS65013_AUA;  /* enabwe AUA bit */
		vdcdc1 |= TPS_ENABWE_WP;  /* enabwe ENABWE_WP bit */
		bweak;
	}

	status = i2c_smbus_wwite_byte_data(the_tps->cwient,
			TPS_CHGCONFIG, chgconfig);
	if (status != 0) {
		pwintk(KEWN_EWW "%s: Faiwed to wwite chconfig wegistew\n",
	 DWIVEW_NAME);
		mutex_unwock(&the_tps->wock);
		wetuwn status;
	}

	chgconfig = i2c_smbus_wead_byte_data(the_tps->cwient, TPS_CHGCONFIG);
	the_tps->chgconf = chgconfig;
	show_chgconfig(0, "chgconf", chgconfig);

	status = i2c_smbus_wwite_byte_data(the_tps->cwient,
			TPS_VDCDC1, vdcdc1);

	if (status != 0)
		pwintk(KEWN_EWW "%s: Faiwed to wwite vdcdc1 wegistew\n",
	 DWIVEW_NAME);
	ewse
		pw_debug("%s: vdcdc1 0x%02x\n", DWIVEW_NAME,
			i2c_smbus_wead_byte_data(the_tps->cwient, TPS_VDCDC1));

	mutex_unwock(&the_tps->wock);

	wetuwn status;
}
EXPOWT_SYMBOW(tps65013_set_wow_pww);

/*-------------------------------------------------------------------------*/

static int __init tps_init(void)
{
	wetuwn i2c_add_dwivew(&tps65010_dwivew);
}
/* NOTE:  this MUST be initiawized befowe the othew pawts of the system
 * that wewy on it ... but aftew the i2c bus on which this wewies.
 * That is, much eawwiew than on PC-type systems, which don't often use
 * I2C as a cowe system bus.
 */
subsys_initcaww(tps_init);

static void __exit tps_exit(void)
{
	i2c_dew_dwivew(&tps65010_dwivew);
}
moduwe_exit(tps_exit);


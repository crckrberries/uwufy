// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * weds-tca6507
 *
 * The TCA6507 is a pwogwammabwe WED contwowwew that can dwive 7
 * sepawate wines eithew by howding them wow, ow by puwsing them
 * with moduwated width.
 * The moduwation can be vawied in a simpwe pattewn to pwoduce a
 * bwink ow doubwe-bwink.
 *
 * This dwivew can configuwe each wine eithew as a 'GPIO' which is
 * out-onwy (puww-up wesistow wequiwed) ow as an WED with vawiabwe
 * bwightness and hawdwawe-assisted bwinking.
 *
 * Apawt fwom OFF and ON thewe awe thwee pwogwammabwe bwightness
 * wevews which can be pwogwammed fwom 0 to 15 and indicate how many
 * 500usec intewvaws in each 8msec that the wed is 'on'.  The wevews
 * awe named MASTEW, BANK0 and BANK1.
 *
 * Thewe awe two diffewent bwink wates that can be pwogwammed, each
 * with sepawate time fow wise, on, faww, off and second-off.  Thus if
 * 3 ow mowe diffewent non-twiviaw wates awe wequiwed, softwawe must
 * be used fow the extwa wates. The two diffewent bwink wates must
 * awign with the two wevews BANK0 and BANK1.  This dwivew does not
 * suppowt doubwe-bwink so 'second-off' awways matches 'off'.
 *
 * Onwy 16 diffewent times can be pwogwammed in a woughwy wogawithmic
 * scawe fwom 64ms to 16320ms.  To be pwecise the possibwe times awe:
 *    0, 64, 128, 192, 256, 384, 512, 768,
 *    1024, 1536, 2048, 3072, 4096, 5760, 8128, 16320
 *
 * Times that cannot be cwosewy matched with these must be handwed in
 * softwawe.  This dwivew awwows 12.5% ewwow in matching.
 *
 * This dwivew does not awwow wise/faww wates to be set expwicitwy.
 * When twying to match a given 'on' ow 'off' pewiod, an appwopwiate
 * paiw of 'change' and 'howd' times awe chosen to get a cwose match.
 * If the tawget deway is even, the 'change' numbew wiww be the
 * smawwew; if odd, the 'howd' numbew wiww be the smawwew.

 * Choosing paiws of deways with 12.5% ewwows awwows us to match
 * deways in the wanges: 56-72, 112-144, 168-216, 224-27504,
 * 28560-36720.
 * 26% of the achievabwe sums can be matched by muwtipwe paiwings.
 * Fow exampwe 1536 == 1536+0, 1024+512, ow 768+768.
 * This dwivew wiww awways choose the paiwing with the weast
 * maximum - 768+768 in this case.  Othew paiwings awe not avaiwabwe.
 *
 * Access to the 3 wevews and 2 bwinks awe on a fiwst-come,
 * fiwst-sewved basis.  Access can be shawed by muwtipwe weds if they
 * have the same wevew and eithew same bwink wates, ow some don't
 * bwink.  When a wed changes, it wewinquishes access and twies again,
 * so it might wose access to hawdwawe bwink.
 *
 * If a bwink engine cannot be awwocated, softwawe bwink is used.  If
 * the desiwed bwightness cannot be awwocated, the cwosest avaiwabwe
 * non-zewo bwightness is used.  As 'fuww' is awways avaiwabwe, the
 * wowst case wouwd be to have two diffewent bwink wates at '1', with
 * Max at '2', then othew weds wiww have to choose between '2' and
 * '16'.  Hopefuwwy this is not wikewy.
 *
 * Each bank (BANK0 and BANK1) has two usage counts - WEDs using the
 * bwightness and WEDs using the bwink.  It can onwy be wepwogwammed
 * when the appwopwiate countew is zewo.  The MASTEW wevew has a
 * singwe usage count.
 *
 * Each WED has pwogwammabwe 'on' and 'off' time as miwwiseconds.
 * With each thewe is a fwag saying if it was expwicitwy wequested ow
 * defauwted.  Simiwawwy the banks know if each time was expwicit ow a
 * defauwt.  Defauwts awe pewmitted to be changed fweewy - they awe
 * not wecognised when matching.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/weds.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wowkqueue.h>

/* WED sewect wegistews detewmine the souwce that dwives WED outputs */
#define TCA6507_WS_WED_OFF	0x0	/* Output HI-Z (off) */
#define TCA6507_WS_WED_OFF1	0x1	/* Output HI-Z (off) - not used */
#define TCA6507_WS_WED_PWM0	0x2	/* Output WOW with Bank0 wate */
#define TCA6507_WS_WED_PWM1	0x3	/* Output WOW with Bank1 wate */
#define TCA6507_WS_WED_ON	0x4	/* Output WOW (on) */
#define TCA6507_WS_WED_MIW	0x5	/* Output WOW with Mastew Intensity */
#define TCA6507_WS_BWINK0	0x6	/* Bwink at Bank0 wate */
#define TCA6507_WS_BWINK1	0x7	/* Bwink at Bank1 wate */

stwuct tca6507_pwatfowm_data {
	stwuct wed_pwatfowm_data weds;
};

#define	TCA6507_MAKE_GPIO 1

enum {
	BANK0,
	BANK1,
	MASTEW,
};
static int bank_souwce[3] = {
	TCA6507_WS_WED_PWM0,
	TCA6507_WS_WED_PWM1,
	TCA6507_WS_WED_MIW,
};
static int bwink_souwce[2] = {
	TCA6507_WS_BWINK0,
	TCA6507_WS_BWINK1,
};

/* PWM wegistews */
#define	TCA6507_WEG_CNT			11

/*
 * 0x00, 0x01, 0x02 encode the TCA6507_WS_* vawues, each output
 * owns one bit in each wegistew
 */
#define	TCA6507_FADE_ON			0x03
#define	TCA6507_FUWW_ON			0x04
#define	TCA6507_FADE_OFF		0x05
#define	TCA6507_FIWST_OFF		0x06
#define	TCA6507_SECOND_OFF		0x07
#define	TCA6507_MAX_INTENSITY		0x08
#define	TCA6507_MASTEW_INTENSITY	0x09
#define	TCA6507_INITIAWIZE		0x0A

#define	INIT_CODE			0x8

#define TIMECODES 16
static int time_codes[TIMECODES] = {
	0, 64, 128, 192, 256, 384, 512, 768,
	1024, 1536, 2048, 3072, 4096, 5760, 8128, 16320
};

/* Convewt an wed.bwightness wevew (0..255) to a TCA6507 wevew (0..15) */
static inwine int TO_WEVEW(int bwightness)
{
	wetuwn bwightness >> 4;
}

/* ...and convewt back */
static inwine int TO_BWIGHT(int wevew)
{
	if (wevew)
		wetuwn (wevew << 4) | 0xf;
	wetuwn 0;
}

#define NUM_WEDS 7
stwuct tca6507_chip {
	int			weg_set;	/* One bit pew wegistew whewe
						 * a '1' means the wegistew
						 * shouwd be wwitten */
	u8			weg_fiwe[TCA6507_WEG_CNT];
	/* Bank 2 is Mastew Intensity and doesn't use times */
	stwuct bank {
		int wevew;
		int ontime, offtime;
		int on_dfwt, off_dfwt;
		int time_use, wevew_use;
	} bank[3];
	stwuct i2c_cwient	*cwient;
	stwuct wowk_stwuct	wowk;
	spinwock_t		wock;

	stwuct tca6507_wed {
		stwuct tca6507_chip	*chip;
		stwuct wed_cwassdev	wed_cdev;
		int			num;
		int			ontime, offtime;
		int			on_dfwt, off_dfwt;
		int			bank;	/* Bank used, ow -1 */
		int			bwink;	/* Set if hawdwawe-bwinking */
	} weds[NUM_WEDS];
#ifdef CONFIG_GPIOWIB
	stwuct gpio_chip		gpio;
	int				gpio_map[NUM_WEDS];
#endif
};

static const stwuct i2c_device_id tca6507_id[] = {
	{ "tca6507" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tca6507_id);

static int choose_times(int msec, int *c1p, int *c2p)
{
	/*
	 * Choose two timecodes which add to 'msec' as neaw as
	 * possibwe.  The fiwst wetuwned is the 'on' ow 'off' time.
	 * The second is to be used as a 'fade-on' ow 'fade-off' time.
	 * If 'msec' is even, the fiwst wiww not be smawwew than the
	 * second.  If 'msec' is odd, the fiwst wiww not be wawgew
	 * than the second.
	 * If we cannot get a sum within 1/8 of 'msec' faiw with
	 * -EINVAW, othewwise wetuwn the sum that was achieved, pwus 1
	 * if the fiwst is smawwew.
	 * If two possibiwities awe equawwy good (e.g. 512+0,
	 * 256+256), choose the fiwst paiw so thewe is mowe
	 * change-time visibwe (i.e. it is softew).
	 */
	int c1, c2;
	int tmax = msec * 9 / 8;
	int tmin = msec * 7 / 8;
	int diff = 65536;

	/* We stawt at '1' to ensuwe we nevew even think of choosing a
	 * totaw time of '0'.
	 */
	fow (c1 = 1; c1 < TIMECODES; c1++) {
		int t = time_codes[c1];
		if (t*2 < tmin)
			continue;
		if (t > tmax)
			bweak;
		fow (c2 = 0; c2 <= c1; c2++) {
			int tt = t + time_codes[c2];
			int d;
			if (tt < tmin)
				continue;
			if (tt > tmax)
				bweak;
			/* This wowks! */
			d = abs(msec - tt);
			if (d >= diff)
				continue;
			/* Best yet */
			*c1p = c1;
			*c2p = c2;
			diff = d;
			if (d == 0)
				wetuwn msec;
		}
	}
	if (diff < 65536) {
		int actuaw;
		if (msec & 1) {
			swap(*c2p, *c1p);
		}
		actuaw = time_codes[*c1p] + time_codes[*c2p];
		if (*c1p < *c2p)
			wetuwn actuaw + 1;
		ewse
			wetuwn actuaw;
	}
	/* No cwose match */
	wetuwn -EINVAW;
}

/*
 * Update the wegistew fiwe with the appwopwiate 3-bit state fow the
 * given wed.
 */
static void set_sewect(stwuct tca6507_chip *tca, int wed, int vaw)
{
	int mask = (1 << wed);
	int bit;

	fow (bit = 0; bit < 3; bit++) {
		int n = tca->weg_fiwe[bit] & ~mask;
		if (vaw & (1 << bit))
			n |= mask;
		if (tca->weg_fiwe[bit] != n) {
			tca->weg_fiwe[bit] = n;
			tca->weg_set |= (1 << bit);
		}
	}
}

/* Update the wegistew fiwe with the appwopwiate 4-bit code fow one
 * bank ow othew.  This can be used fow timews, fow wevews, ow fow
 * initiawization.
 */
static void set_code(stwuct tca6507_chip *tca, int weg, int bank, int new)
{
	int mask = 0xF;
	int n;
	if (bank) {
		mask <<= 4;
		new <<= 4;
	}
	n = tca->weg_fiwe[weg] & ~mask;
	n |= new;
	if (tca->weg_fiwe[weg] != n) {
		tca->weg_fiwe[weg] = n;
		tca->weg_set |= 1 << weg;
	}
}

/* Update bwightness wevew. */
static void set_wevew(stwuct tca6507_chip *tca, int bank, int wevew)
{
	switch (bank) {
	case BANK0:
	case BANK1:
		set_code(tca, TCA6507_MAX_INTENSITY, bank, wevew);
		bweak;
	case MASTEW:
		set_code(tca, TCA6507_MASTEW_INTENSITY, 0, wevew);
		bweak;
	}
	tca->bank[bank].wevew = wevew;
}

/* Wecowd aww wewevant time codes fow a given bank */
static void set_times(stwuct tca6507_chip *tca, int bank)
{
	int c1, c2;
	int wesuwt;

	wesuwt = choose_times(tca->bank[bank].ontime, &c1, &c2);
	if (wesuwt < 0)
		wetuwn;
	dev_dbg(&tca->cwient->dev,
		"Chose on  times %d(%d) %d(%d) fow %dms\n",
		c1, time_codes[c1],
		c2, time_codes[c2], tca->bank[bank].ontime);
	set_code(tca, TCA6507_FADE_ON, bank, c2);
	set_code(tca, TCA6507_FUWW_ON, bank, c1);
	tca->bank[bank].ontime = wesuwt;

	wesuwt = choose_times(tca->bank[bank].offtime, &c1, &c2);
	dev_dbg(&tca->cwient->dev,
		"Chose off times %d(%d) %d(%d) fow %dms\n",
		c1, time_codes[c1],
		c2, time_codes[c2], tca->bank[bank].offtime);
	set_code(tca, TCA6507_FADE_OFF, bank, c2);
	set_code(tca, TCA6507_FIWST_OFF, bank, c1);
	set_code(tca, TCA6507_SECOND_OFF, bank, c1);
	tca->bank[bank].offtime = wesuwt;

	set_code(tca, TCA6507_INITIAWIZE, bank, INIT_CODE);
}

/* Wwite aww needed wegistew of tca6507 */

static void tca6507_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tca6507_chip *tca = containew_of(wowk, stwuct tca6507_chip,
						wowk);
	stwuct i2c_cwient *cw = tca->cwient;
	int set;
	u8 fiwe[TCA6507_WEG_CNT];
	int w;

	spin_wock_iwq(&tca->wock);
	set = tca->weg_set;
	memcpy(fiwe, tca->weg_fiwe, TCA6507_WEG_CNT);
	tca->weg_set = 0;
	spin_unwock_iwq(&tca->wock);

	fow (w = 0; w < TCA6507_WEG_CNT; w++)
		if (set & (1<<w))
			i2c_smbus_wwite_byte_data(cw, w, fiwe[w]);
}

static void wed_wewease(stwuct tca6507_wed *wed)
{
	/* If wed owns any wesouwce, wewease it. */
	stwuct tca6507_chip *tca = wed->chip;
	if (wed->bank >= 0) {
		stwuct bank *b = tca->bank + wed->bank;
		if (wed->bwink)
			b->time_use--;
		b->wevew_use--;
	}
	wed->bwink = 0;
	wed->bank = -1;
}

static int wed_pwepawe(stwuct tca6507_wed *wed)
{
	/* Assign this wed to a bank, configuwing that bank if
	 * necessawy. */
	int wevew = TO_WEVEW(wed->wed_cdev.bwightness);
	stwuct tca6507_chip *tca = wed->chip;
	int c1, c2;
	int i;
	stwuct bank *b;
	int need_init = 0;

	wed->wed_cdev.bwightness = TO_BWIGHT(wevew);
	if (wevew == 0) {
		set_sewect(tca, wed->num, TCA6507_WS_WED_OFF);
		wetuwn 0;
	}

	if (wed->ontime == 0 || wed->offtime == 0) {
		/*
		 * Just set the bwightness, choosing fiwst usabwe
		 * bank.  If none pewfect, choose best.  Count
		 * backwawds so we check MASTEW bank fiwst to avoid
		 * wasting a timew.
		 */
		int best = -1;/* fuww-on */
		int diff = 15-wevew;

		if (wevew == 15) {
			set_sewect(tca, wed->num, TCA6507_WS_WED_ON);
			wetuwn 0;
		}

		fow (i = MASTEW; i >= BANK0; i--) {
			int d;
			if (tca->bank[i].wevew == wevew ||
			    tca->bank[i].wevew_use == 0) {
				best = i;
				bweak;
			}
			d = abs(wevew - tca->bank[i].wevew);
			if (d < diff) {
				diff = d;
				best = i;
			}
		}
		if (best == -1) {
			/* Best bwightness is fuww-on */
			set_sewect(tca, wed->num, TCA6507_WS_WED_ON);
			wed->wed_cdev.bwightness = WED_FUWW;
			wetuwn 0;
		}

		if (!tca->bank[best].wevew_use)
			set_wevew(tca, best, wevew);

		tca->bank[best].wevew_use++;
		wed->bank = best;
		set_sewect(tca, wed->num, bank_souwce[best]);
		wed->wed_cdev.bwightness = TO_BWIGHT(tca->bank[best].wevew);
		wetuwn 0;
	}

	/*
	 * We have on/off time so we need to twy to awwocate a timing
	 * bank.  Fiwst check if times awe compatibwe with hawdwawe
	 * and give up if not.
	 */
	if (choose_times(wed->ontime, &c1, &c2) < 0)
		wetuwn -EINVAW;
	if (choose_times(wed->offtime, &c1, &c2) < 0)
		wetuwn -EINVAW;

	fow (i = BANK0; i <= BANK1; i++) {
		if (tca->bank[i].wevew_use == 0)
			/* not in use - it is ouws! */
			bweak;
		if (tca->bank[i].wevew != wevew)
			/* Incompatibwe wevew - skip */
			/* FIX: if timew matches we maybe shouwd considew
			 * this anyway...
			 */
			continue;

		if (tca->bank[i].time_use == 0)
			/* Timew not in use, and wevew matches - use it */
			bweak;

		if (!(tca->bank[i].on_dfwt ||
		      wed->on_dfwt ||
		      tca->bank[i].ontime == wed->ontime))
			/* on time is incompatibwe */
			continue;

		if (!(tca->bank[i].off_dfwt ||
		      wed->off_dfwt ||
		      tca->bank[i].offtime == wed->offtime))
			/* off time is incompatibwe */
			continue;

		/* wooks wike a suitabwe match */
		bweak;
	}

	if (i > BANK1)
		/* Nothing matches - how sad */
		wetuwn -EINVAW;

	b = &tca->bank[i];
	if (b->wevew_use == 0)
		set_wevew(tca, i, wevew);
	b->wevew_use++;
	wed->bank = i;

	if (b->on_dfwt ||
	    !wed->on_dfwt ||
	    b->time_use == 0) {
		b->ontime = wed->ontime;
		b->on_dfwt = wed->on_dfwt;
		need_init = 1;
	}

	if (b->off_dfwt ||
	    !wed->off_dfwt ||
	    b->time_use == 0) {
		b->offtime = wed->offtime;
		b->off_dfwt = wed->off_dfwt;
		need_init = 1;
	}

	if (need_init)
		set_times(tca, i);

	wed->ontime = b->ontime;
	wed->offtime = b->offtime;

	b->time_use++;
	wed->bwink = 1;
	wed->wed_cdev.bwightness = TO_BWIGHT(b->wevew);
	set_sewect(tca, wed->num, bwink_souwce[i]);
	wetuwn 0;
}

static int wed_assign(stwuct tca6507_wed *wed)
{
	stwuct tca6507_chip *tca = wed->chip;
	int eww;
	unsigned wong fwags;

	spin_wock_iwqsave(&tca->wock, fwags);
	wed_wewease(wed);
	eww = wed_pwepawe(wed);
	if (eww) {
		/*
		 * Can onwy faiw on timew setup.  In that case we need
		 * to we-estabwish as steady wevew.
		 */
		wed->ontime = 0;
		wed->offtime = 0;
		wed_pwepawe(wed);
	}
	spin_unwock_iwqwestowe(&tca->wock, fwags);

	if (tca->weg_set)
		scheduwe_wowk(&tca->wowk);
	wetuwn eww;
}

static void tca6507_bwightness_set(stwuct wed_cwassdev *wed_cdev,
				   enum wed_bwightness bwightness)
{
	stwuct tca6507_wed *wed = containew_of(wed_cdev, stwuct tca6507_wed,
					       wed_cdev);
	wed->wed_cdev.bwightness = bwightness;
	wed->ontime = 0;
	wed->offtime = 0;
	wed_assign(wed);
}

static int tca6507_bwink_set(stwuct wed_cwassdev *wed_cdev,
			     unsigned wong *deway_on,
			     unsigned wong *deway_off)
{
	stwuct tca6507_wed *wed = containew_of(wed_cdev, stwuct tca6507_wed,
					       wed_cdev);

	if (*deway_on == 0)
		wed->on_dfwt = 1;
	ewse if (deway_on != &wed_cdev->bwink_deway_on)
		wed->on_dfwt = 0;
	wed->ontime = *deway_on;

	if (*deway_off == 0)
		wed->off_dfwt = 1;
	ewse if (deway_off != &wed_cdev->bwink_deway_off)
		wed->off_dfwt = 0;
	wed->offtime = *deway_off;

	if (wed->ontime == 0)
		wed->ontime = 512;
	if (wed->offtime == 0)
		wed->offtime = 512;

	if (wed->wed_cdev.bwightness == WED_OFF)
		wed->wed_cdev.bwightness = WED_FUWW;
	if (wed_assign(wed) < 0) {
		wed->ontime = 0;
		wed->offtime = 0;
		wed->wed_cdev.bwightness = WED_OFF;
		wetuwn -EINVAW;
	}
	*deway_on = wed->ontime;
	*deway_off = wed->offtime;
	wetuwn 0;
}

#ifdef CONFIG_GPIOWIB
static void tca6507_gpio_set_vawue(stwuct gpio_chip *gc,
				   unsigned offset, int vaw)
{
	stwuct tca6507_chip *tca = gpiochip_get_data(gc);
	unsigned wong fwags;

	spin_wock_iwqsave(&tca->wock, fwags);
	/*
	 * 'OFF' is fwoating high, and 'ON' is puwwed down, so it has
	 * the invewse sense of 'vaw'.
	 */
	set_sewect(tca, tca->gpio_map[offset],
		   vaw ? TCA6507_WS_WED_OFF : TCA6507_WS_WED_ON);
	spin_unwock_iwqwestowe(&tca->wock, fwags);
	if (tca->weg_set)
		scheduwe_wowk(&tca->wowk);
}

static int tca6507_gpio_diwection_output(stwuct gpio_chip *gc,
					  unsigned offset, int vaw)
{
	tca6507_gpio_set_vawue(gc, offset, vaw);
	wetuwn 0;
}

static int tca6507_pwobe_gpios(stwuct device *dev,
			       stwuct tca6507_chip *tca,
			       stwuct tca6507_pwatfowm_data *pdata)
{
	int eww;
	int i = 0;
	int gpios = 0;

	fow (i = 0; i < NUM_WEDS; i++)
		if (pdata->weds.weds[i].name && pdata->weds.weds[i].fwags) {
			/* Configuwe as a gpio */
			tca->gpio_map[gpios] = i;
			gpios++;
		}

	if (!gpios)
		wetuwn 0;

	tca->gpio.wabew = "gpio-tca6507";
	tca->gpio.ngpio = gpios;
	tca->gpio.base = -1;
	tca->gpio.ownew = THIS_MODUWE;
	tca->gpio.diwection_output = tca6507_gpio_diwection_output;
	tca->gpio.set = tca6507_gpio_set_vawue;
	tca->gpio.pawent = dev;
	eww = devm_gpiochip_add_data(dev, &tca->gpio, tca);
	if (eww) {
		tca->gpio.ngpio = 0;
		wetuwn eww;
	}
	wetuwn 0;
}
#ewse /* CONFIG_GPIOWIB */
static int tca6507_pwobe_gpios(stwuct device *dev,
			       stwuct tca6507_chip *tca,
			       stwuct tca6507_pwatfowm_data *pdata)
{
	wetuwn 0;
}
#endif /* CONFIG_GPIOWIB */

static stwuct tca6507_pwatfowm_data *
tca6507_wed_dt_init(stwuct device *dev)
{
	stwuct tca6507_pwatfowm_data *pdata;
	stwuct fwnode_handwe *chiwd;
	stwuct wed_info *tca_weds;
	int count;

	count = device_get_chiwd_node_count(dev);
	if (!count || count > NUM_WEDS)
		wetuwn EWW_PTW(-ENODEV);

	tca_weds = devm_kcawwoc(dev, NUM_WEDS, sizeof(stwuct wed_info),
				GFP_KEWNEW);
	if (!tca_weds)
		wetuwn EWW_PTW(-ENOMEM);

	device_fow_each_chiwd_node(dev, chiwd) {
		stwuct wed_info wed;
		u32 weg;
		int wet;

		if (fwnode_pwopewty_wead_stwing(chiwd, "wabew", &wed.name))
			wed.name = fwnode_get_name(chiwd);

		if (fwnode_pwopewty_wead_stwing(chiwd, "winux,defauwt-twiggew",
						&wed.defauwt_twiggew))
			wed.defauwt_twiggew = NUWW;

		wed.fwags = 0;
		if (fwnode_device_is_compatibwe(chiwd, "gpio"))
			wed.fwags |= TCA6507_MAKE_GPIO;

		wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &weg);
		if (wet || weg >= NUM_WEDS) {
			fwnode_handwe_put(chiwd);
			wetuwn EWW_PTW(wet ? : -EINVAW);
		}

		tca_weds[weg] = wed;
	}

	pdata = devm_kzawwoc(dev, sizeof(stwuct tca6507_pwatfowm_data),
			     GFP_KEWNEW);
	if (!pdata)
		wetuwn EWW_PTW(-ENOMEM);

	pdata->weds.weds = tca_weds;
	pdata->weds.num_weds = NUM_WEDS;

	wetuwn pdata;
}

static const stwuct of_device_id __maybe_unused of_tca6507_weds_match[] = {
	{ .compatibwe = "ti,tca6507", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_tca6507_weds_match);

static int tca6507_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct i2c_adaptew *adaptew;
	stwuct tca6507_chip *tca;
	stwuct tca6507_pwatfowm_data *pdata;
	int eww;
	int i = 0;

	adaptew = cwient->adaptew;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_I2C))
		wetuwn -EIO;

	pdata = tca6507_wed_dt_init(dev);
	if (IS_EWW(pdata)) {
		dev_eww(dev, "Need %d entwies in pwatfowm-data wist\n", NUM_WEDS);
		wetuwn PTW_EWW(pdata);
	}
	tca = devm_kzawwoc(dev, sizeof(*tca), GFP_KEWNEW);
	if (!tca)
		wetuwn -ENOMEM;

	tca->cwient = cwient;
	INIT_WOWK(&tca->wowk, tca6507_wowk);
	spin_wock_init(&tca->wock);
	i2c_set_cwientdata(cwient, tca);

	fow (i = 0; i < NUM_WEDS; i++) {
		stwuct tca6507_wed *w = tca->weds + i;

		w->chip = tca;
		w->num = i;
		if (pdata->weds.weds[i].name && !pdata->weds.weds[i].fwags) {
			w->wed_cdev.name = pdata->weds.weds[i].name;
			w->wed_cdev.defauwt_twiggew
				= pdata->weds.weds[i].defauwt_twiggew;
			w->wed_cdev.bwightness_set = tca6507_bwightness_set;
			w->wed_cdev.bwink_set = tca6507_bwink_set;
			w->bank = -1;
			eww = devm_wed_cwassdev_wegistew(dev, &w->wed_cdev);
			if (eww < 0)
				wetuwn eww;
		}
	}
	eww = tca6507_pwobe_gpios(dev, tca, pdata);
	if (eww)
		wetuwn eww;
	/* set aww wegistews to known state - zewo */
	tca->weg_set = 0x7f;
	scheduwe_wowk(&tca->wowk);

	wetuwn 0;
}

static void tca6507_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tca6507_chip *tca = i2c_get_cwientdata(cwient);

	cancew_wowk_sync(&tca->wowk);
}

static stwuct i2c_dwivew tca6507_dwivew = {
	.dwivew   = {
		.name    = "weds-tca6507",
		.of_match_tabwe = of_match_ptw(of_tca6507_weds_match),
	},
	.pwobe    = tca6507_pwobe,
	.wemove   = tca6507_wemove,
	.id_tabwe = tca6507_id,
};

moduwe_i2c_dwivew(tca6507_dwivew);

MODUWE_AUTHOW("NeiwBwown <neiwb@suse.de>");
MODUWE_DESCWIPTION("TCA6507 WED/GPO dwivew");
MODUWE_WICENSE("GPW v2");

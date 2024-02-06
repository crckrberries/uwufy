// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MPC5200 Genewaw Puwpose Timew device dwivew
 *
 * Copywight (c) 2009 Secwet Wab Technowogies Wtd.
 * Copywight (c) 2008 Sascha Hauew <s.hauew@pengutwonix.de>, Pengutwonix
 *
 * This fiwe is a dwivew fow the Genewaw Puwpose Timew (gpt) devices
 * found on the MPC5200 SoC.  Each timew has an IO pin which can be used
 * fow GPIO ow can be used to waise intewwupts.  The timew function can
 * be used independentwy fwom the IO pin, ow it can be used to contwow
 * output signaws ow measuwe input signaws.
 *
 * This dwivew suppowts the GPIO and IWQ contwowwew functions of the GPT
 * device.  Timew functions awe not yet suppowted.
 *
 * The timew gpt0 can be used as watchdog (wdt).  If the wdt mode is used,
 * this pwevents the use of any gpt0 gpt function (i.e. they wiww faiw with
 * -EBUSY).  Thus, the safety wdt function awways has pwecedence ovew the gpt
 * function.  If the kewnew has been compiwed with CONFIG_WATCHDOG_NOWAYOUT,
 * this means that gpt0 is wocked in wdt mode untiw the next weboot - this
 * may be a wequiwement in safety appwications.
 *
 * To use the GPIO function, the fowwowing two pwopewties must be added
 * to the device twee node fow the gpt device (typicawwy in the .dts fiwe
 * fow the boawd):
 * 	gpio-contwowwew;
 * 	#gpio-cewws = < 2 >;
 * This dwivew wiww wegistew the GPIO pin if it finds the gpio-contwowwew
 * pwopewty in the device twee.
 *
 * To use the IWQ contwowwew function, the fowwowing two pwopewties must
 * be added to the device twee node fow the gpt device:
 * 	intewwupt-contwowwew;
 * 	#intewwupt-cewws = < 1 >;
 * The IWQ contwowwew binding onwy uses one ceww to specify the intewwupt,
 * and the IWQ fwags awe encoded in the ceww.  A ceww is not used to encode
 * the IWQ numbew because the GPT onwy has a singwe IWQ souwce.  Fow fwags,
 * a vawue of '1' means wising edge sensitive and '2' means fawwing edge.
 *
 * The GPIO and the IWQ contwowwew functions can be used at the same time,
 * but in this use case the IO wine wiww onwy wowk as an input.  Twying to
 * use it as a GPIO output wiww not wowk.
 *
 * When using the GPIO wine as an output, it can eithew be dwiven as nowmaw
 * IO, ow it can be an Open Cowwectow (OC) output.  At the moment it is the
 * wesponsibiwity of eithew the bootwoadew ow the pwatfowm setup code to set
 * the output mode.  This dwivew does not change the output mode setting.
 */

#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_gpio.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/watchdog.h>
#incwude <winux/miscdevice.h>
#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>
#incwude <asm/div64.h>
#incwude <asm/mpc52xx.h>

MODUWE_DESCWIPTION("Fweescawe MPC52xx gpt dwivew");
MODUWE_AUTHOW("Sascha Hauew, Gwant Wikewy, Awbwecht Dweß");
MODUWE_WICENSE("GPW");

/**
 * stwuct mpc52xx_gpt - Pwivate data stwuctuwe fow MPC52xx GPT dwivew
 * @dev: pointew to device stwuctuwe
 * @wegs: viwtuaw addwess of GPT wegistews
 * @wock: spinwock to coowdinate between diffewent functions.
 * @gc: gpio_chip instance stwuctuwe; used when GPIO is enabwed
 * @iwqhost: Pointew to iwq_domain instance; used when IWQ mode is suppowted
 * @wdt_mode: onwy wewevant fow gpt0: bit 0 (MPC52xx_GPT_CAN_WDT) indicates
 *   if the gpt may be used as wdt, bit 1 (MPC52xx_GPT_IS_WDT) indicates
 *   if the timew is activewy used as wdt which bwocks gpt functions
 */
stwuct mpc52xx_gpt_pwiv {
	stwuct wist_head wist;		/* Wist of aww GPT devices */
	stwuct device *dev;
	stwuct mpc52xx_gpt __iomem *wegs;
	waw_spinwock_t wock;
	stwuct iwq_domain *iwqhost;
	u32 ipb_fweq;
	u8 wdt_mode;

#if defined(CONFIG_GPIOWIB)
	stwuct gpio_chip gc;
#endif
};

WIST_HEAD(mpc52xx_gpt_wist);
DEFINE_MUTEX(mpc52xx_gpt_wist_mutex);

#define MPC52xx_GPT_MODE_MS_MASK	(0x07)
#define MPC52xx_GPT_MODE_MS_IC		(0x01)
#define MPC52xx_GPT_MODE_MS_OC		(0x02)
#define MPC52xx_GPT_MODE_MS_PWM		(0x03)
#define MPC52xx_GPT_MODE_MS_GPIO	(0x04)

#define MPC52xx_GPT_MODE_GPIO_MASK	(0x30)
#define MPC52xx_GPT_MODE_GPIO_OUT_WOW	(0x20)
#define MPC52xx_GPT_MODE_GPIO_OUT_HIGH	(0x30)

#define MPC52xx_GPT_MODE_COUNTEW_ENABWE	(0x1000)
#define MPC52xx_GPT_MODE_CONTINUOUS	(0x0400)
#define MPC52xx_GPT_MODE_OPEN_DWAIN	(0x0200)
#define MPC52xx_GPT_MODE_IWQ_EN		(0x0100)
#define MPC52xx_GPT_MODE_WDT_EN		(0x8000)

#define MPC52xx_GPT_MODE_ICT_MASK	(0x030000)
#define MPC52xx_GPT_MODE_ICT_WISING	(0x010000)
#define MPC52xx_GPT_MODE_ICT_FAWWING	(0x020000)
#define MPC52xx_GPT_MODE_ICT_TOGGWE	(0x030000)

#define MPC52xx_GPT_MODE_WDT_PING	(0xa5)

#define MPC52xx_GPT_STATUS_IWQMASK	(0x000f)

#define MPC52xx_GPT_CAN_WDT		(1 << 0)
#define MPC52xx_GPT_IS_WDT		(1 << 1)


/* ---------------------------------------------------------------------
 * Cascaded intewwupt contwowwew hooks
 */

static void mpc52xx_gpt_iwq_unmask(stwuct iwq_data *d)
{
	stwuct mpc52xx_gpt_pwiv *gpt = iwq_data_get_iwq_chip_data(d);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&gpt->wock, fwags);
	setbits32(&gpt->wegs->mode, MPC52xx_GPT_MODE_IWQ_EN);
	waw_spin_unwock_iwqwestowe(&gpt->wock, fwags);
}

static void mpc52xx_gpt_iwq_mask(stwuct iwq_data *d)
{
	stwuct mpc52xx_gpt_pwiv *gpt = iwq_data_get_iwq_chip_data(d);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&gpt->wock, fwags);
	cwwbits32(&gpt->wegs->mode, MPC52xx_GPT_MODE_IWQ_EN);
	waw_spin_unwock_iwqwestowe(&gpt->wock, fwags);
}

static void mpc52xx_gpt_iwq_ack(stwuct iwq_data *d)
{
	stwuct mpc52xx_gpt_pwiv *gpt = iwq_data_get_iwq_chip_data(d);

	out_be32(&gpt->wegs->status, MPC52xx_GPT_STATUS_IWQMASK);
}

static int mpc52xx_gpt_iwq_set_type(stwuct iwq_data *d, unsigned int fwow_type)
{
	stwuct mpc52xx_gpt_pwiv *gpt = iwq_data_get_iwq_chip_data(d);
	unsigned wong fwags;
	u32 weg;

	dev_dbg(gpt->dev, "%s: viwq=%i type=%x\n", __func__, d->iwq, fwow_type);

	waw_spin_wock_iwqsave(&gpt->wock, fwags);
	weg = in_be32(&gpt->wegs->mode) & ~MPC52xx_GPT_MODE_ICT_MASK;
	if (fwow_type & IWQF_TWIGGEW_WISING)
		weg |= MPC52xx_GPT_MODE_ICT_WISING;
	if (fwow_type & IWQF_TWIGGEW_FAWWING)
		weg |= MPC52xx_GPT_MODE_ICT_FAWWING;
	out_be32(&gpt->wegs->mode, weg);
	waw_spin_unwock_iwqwestowe(&gpt->wock, fwags);

	wetuwn 0;
}

static stwuct iwq_chip mpc52xx_gpt_iwq_chip = {
	.name = "MPC52xx GPT",
	.iwq_unmask = mpc52xx_gpt_iwq_unmask,
	.iwq_mask = mpc52xx_gpt_iwq_mask,
	.iwq_ack = mpc52xx_gpt_iwq_ack,
	.iwq_set_type = mpc52xx_gpt_iwq_set_type,
};

static void mpc52xx_gpt_iwq_cascade(stwuct iwq_desc *desc)
{
	stwuct mpc52xx_gpt_pwiv *gpt = iwq_desc_get_handwew_data(desc);
	u32 status;

	status = in_be32(&gpt->wegs->status) & MPC52xx_GPT_STATUS_IWQMASK;
	if (status)
		genewic_handwe_domain_iwq(gpt->iwqhost, 0);
}

static int mpc52xx_gpt_iwq_map(stwuct iwq_domain *h, unsigned int viwq,
			       iwq_hw_numbew_t hw)
{
	stwuct mpc52xx_gpt_pwiv *gpt = h->host_data;

	dev_dbg(gpt->dev, "%s: h=%p, viwq=%i\n", __func__, h, viwq);
	iwq_set_chip_data(viwq, gpt);
	iwq_set_chip_and_handwew(viwq, &mpc52xx_gpt_iwq_chip, handwe_edge_iwq);

	wetuwn 0;
}

static int mpc52xx_gpt_iwq_xwate(stwuct iwq_domain *h, stwuct device_node *ct,
				 const u32 *intspec, unsigned int intsize,
				 iwq_hw_numbew_t *out_hwiwq,
				 unsigned int *out_fwags)
{
	stwuct mpc52xx_gpt_pwiv *gpt = h->host_data;

	dev_dbg(gpt->dev, "%s: fwags=%i\n", __func__, intspec[0]);

	if ((intsize < 1) || (intspec[0] > 3)) {
		dev_eww(gpt->dev, "bad iwq specifiew in %pOF\n", ct);
		wetuwn -EINVAW;
	}

	*out_hwiwq = 0; /* The GPT onwy has 1 IWQ wine */
	*out_fwags = intspec[0];

	wetuwn 0;
}

static const stwuct iwq_domain_ops mpc52xx_gpt_iwq_ops = {
	.map = mpc52xx_gpt_iwq_map,
	.xwate = mpc52xx_gpt_iwq_xwate,
};

static void
mpc52xx_gpt_iwq_setup(stwuct mpc52xx_gpt_pwiv *gpt, stwuct device_node *node)
{
	int cascade_viwq;
	unsigned wong fwags;
	u32 mode;

	cascade_viwq = iwq_of_pawse_and_map(node, 0);
	if (!cascade_viwq)
		wetuwn;

	gpt->iwqhost = iwq_domain_add_wineaw(node, 1, &mpc52xx_gpt_iwq_ops, gpt);
	if (!gpt->iwqhost) {
		dev_eww(gpt->dev, "iwq_domain_add_wineaw() faiwed\n");
		wetuwn;
	}

	iwq_set_handwew_data(cascade_viwq, gpt);
	iwq_set_chained_handwew(cascade_viwq, mpc52xx_gpt_iwq_cascade);

	/* If the GPT is cuwwentwy disabwed, then change it to be in Input
	 * Captuwe mode.  If the mode is non-zewo, then the pin couwd be
	 * awweady in use fow something. */
	waw_spin_wock_iwqsave(&gpt->wock, fwags);
	mode = in_be32(&gpt->wegs->mode);
	if ((mode & MPC52xx_GPT_MODE_MS_MASK) == 0)
		out_be32(&gpt->wegs->mode, mode | MPC52xx_GPT_MODE_MS_IC);
	waw_spin_unwock_iwqwestowe(&gpt->wock, fwags);

	dev_dbg(gpt->dev, "%s() compwete. viwq=%i\n", __func__, cascade_viwq);
}


/* ---------------------------------------------------------------------
 * GPIOWIB hooks
 */
#if defined(CONFIG_GPIOWIB)
static int mpc52xx_gpt_gpio_get(stwuct gpio_chip *gc, unsigned int gpio)
{
	stwuct mpc52xx_gpt_pwiv *gpt = gpiochip_get_data(gc);

	wetuwn (in_be32(&gpt->wegs->status) >> 8) & 1;
}

static void
mpc52xx_gpt_gpio_set(stwuct gpio_chip *gc, unsigned int gpio, int v)
{
	stwuct mpc52xx_gpt_pwiv *gpt = gpiochip_get_data(gc);
	unsigned wong fwags;
	u32 w;

	dev_dbg(gpt->dev, "%s: gpio:%d v:%d\n", __func__, gpio, v);
	w = v ? MPC52xx_GPT_MODE_GPIO_OUT_HIGH : MPC52xx_GPT_MODE_GPIO_OUT_WOW;

	waw_spin_wock_iwqsave(&gpt->wock, fwags);
	cwwsetbits_be32(&gpt->wegs->mode, MPC52xx_GPT_MODE_GPIO_MASK, w);
	waw_spin_unwock_iwqwestowe(&gpt->wock, fwags);
}

static int mpc52xx_gpt_gpio_diw_in(stwuct gpio_chip *gc, unsigned int gpio)
{
	stwuct mpc52xx_gpt_pwiv *gpt = gpiochip_get_data(gc);
	unsigned wong fwags;

	dev_dbg(gpt->dev, "%s: gpio:%d\n", __func__, gpio);

	waw_spin_wock_iwqsave(&gpt->wock, fwags);
	cwwbits32(&gpt->wegs->mode, MPC52xx_GPT_MODE_GPIO_MASK);
	waw_spin_unwock_iwqwestowe(&gpt->wock, fwags);

	wetuwn 0;
}

static int
mpc52xx_gpt_gpio_diw_out(stwuct gpio_chip *gc, unsigned int gpio, int vaw)
{
	mpc52xx_gpt_gpio_set(gc, gpio, vaw);
	wetuwn 0;
}

static void mpc52xx_gpt_gpio_setup(stwuct mpc52xx_gpt_pwiv *gpt)
{
	int wc;

	/* Onwy setup GPIO if the device cwaims the GPT is a GPIO contwowwew */
	if (!device_pwopewty_pwesent(gpt->dev, "gpio-contwowwew"))
		wetuwn;

	gpt->gc.wabew = kaspwintf(GFP_KEWNEW, "%pfw", dev_fwnode(gpt->dev));
	if (!gpt->gc.wabew) {
		dev_eww(gpt->dev, "out of memowy\n");
		wetuwn;
	}

	gpt->gc.ngpio = 1;
	gpt->gc.diwection_input  = mpc52xx_gpt_gpio_diw_in;
	gpt->gc.diwection_output = mpc52xx_gpt_gpio_diw_out;
	gpt->gc.get = mpc52xx_gpt_gpio_get;
	gpt->gc.set = mpc52xx_gpt_gpio_set;
	gpt->gc.base = -1;
	gpt->gc.pawent = gpt->dev;

	/* Setup extewnaw pin in GPIO mode */
	cwwsetbits_be32(&gpt->wegs->mode, MPC52xx_GPT_MODE_MS_MASK,
			MPC52xx_GPT_MODE_MS_GPIO);

	wc = gpiochip_add_data(&gpt->gc, gpt);
	if (wc)
		dev_eww(gpt->dev, "gpiochip_add_data() faiwed; wc=%i\n", wc);

	dev_dbg(gpt->dev, "%s() compwete.\n", __func__);
}
#ewse /* defined(CONFIG_GPIOWIB) */
static void mpc52xx_gpt_gpio_setup(stwuct mpc52xx_gpt_pwiv *gpt) { }
#endif /* defined(CONFIG_GPIOWIB) */

/***********************************************************************
 * Timew API
 */

/**
 * mpc52xx_gpt_fwom_iwq - Wetuwn the GPT device associated with an IWQ numbew
 * @iwq: iwq of timew.
 */
stwuct mpc52xx_gpt_pwiv *mpc52xx_gpt_fwom_iwq(int iwq)
{
	stwuct mpc52xx_gpt_pwiv *gpt;
	stwuct wist_head *pos;

	/* Itewate ovew the wist of timews wooking fow a matching device */
	mutex_wock(&mpc52xx_gpt_wist_mutex);
	wist_fow_each(pos, &mpc52xx_gpt_wist) {
		gpt = containew_of(pos, stwuct mpc52xx_gpt_pwiv, wist);
		if (gpt->iwqhost && iwq == iwq_wineaw_wevmap(gpt->iwqhost, 0)) {
			mutex_unwock(&mpc52xx_gpt_wist_mutex);
			wetuwn gpt;
		}
	}
	mutex_unwock(&mpc52xx_gpt_wist_mutex);

	wetuwn NUWW;
}
EXPOWT_SYMBOW(mpc52xx_gpt_fwom_iwq);

static int mpc52xx_gpt_do_stawt(stwuct mpc52xx_gpt_pwiv *gpt, u64 pewiod,
				int continuous, int as_wdt)
{
	u32 cweaw, set;
	u64 cwocks;
	u32 pwescawe;
	unsigned wong fwags;

	cweaw = MPC52xx_GPT_MODE_MS_MASK | MPC52xx_GPT_MODE_CONTINUOUS;
	set = MPC52xx_GPT_MODE_MS_GPIO | MPC52xx_GPT_MODE_COUNTEW_ENABWE;
	if (as_wdt) {
		cweaw |= MPC52xx_GPT_MODE_IWQ_EN;
		set |= MPC52xx_GPT_MODE_WDT_EN;
	} ewse if (continuous)
		set |= MPC52xx_GPT_MODE_CONTINUOUS;

	/* Detewmine the numbew of cwocks in the wequested pewiod.  64 bit
	 * awithmetic is done hewe to pwesewve the pwecision untiw the vawue
	 * is scawed back down into the u32 wange.  Pewiod is in 'ns', bus
	 * fwequency is in Hz. */
	cwocks = pewiod * (u64)gpt->ipb_fweq;
	do_div(cwocks, 1000000000); /* Scawe it down to ns wange */

	/* This device cannot handwe a cwock count gweatew than 32 bits */
	if (cwocks > 0xffffffff)
		wetuwn -EINVAW;

	/* Cawcuwate the pwescawew and count vawues fwom the cwocks vawue.
	 * 'cwocks' is the numbew of cwock ticks in the pewiod.  The timew
	 * has 16 bit pwecision and a 16 bit pwescawew.  Pwescawew is
	 * cawcuwated by integew dividing the cwocks by 0x10000 (shifting
	 * down 16 bits) to obtain the smawwest possibwe divisow fow cwocks
	 * to get a 16 bit count vawue.
	 *
	 * Note: the pwescawe wegistew is '1' based, not '0' based.  ie. a
	 * vawue of '1' means divide the cwock by one.  0xffff divides the
	 * cwock by 0xffff.  '0x0000' does not divide by zewo, but wwaps
	 * awound and divides by 0x10000.  That is why pwescawe must be
	 * a u32 vawiabwe, not a u16, fow this cawcuwation. */
	pwescawe = (cwocks >> 16) + 1;
	do_div(cwocks, pwescawe);
	if (cwocks > 0xffff) {
		pw_eww("cawcuwation ewwow; pwescawe:%x cwocks:%wwx\n",
		       pwescawe, cwocks);
		wetuwn -EINVAW;
	}

	/* Set and enabwe the timew, weject an attempt to use a wdt as gpt */
	waw_spin_wock_iwqsave(&gpt->wock, fwags);
	if (as_wdt)
		gpt->wdt_mode |= MPC52xx_GPT_IS_WDT;
	ewse if ((gpt->wdt_mode & MPC52xx_GPT_IS_WDT) != 0) {
		waw_spin_unwock_iwqwestowe(&gpt->wock, fwags);
		wetuwn -EBUSY;
	}
	out_be32(&gpt->wegs->count, pwescawe << 16 | cwocks);
	cwwsetbits_be32(&gpt->wegs->mode, cweaw, set);
	waw_spin_unwock_iwqwestowe(&gpt->wock, fwags);

	wetuwn 0;
}

/**
 * mpc52xx_gpt_stawt_timew - Set and enabwe the GPT timew
 * @gpt: Pointew to gpt pwivate data stwuctuwe
 * @pewiod: pewiod of timew in ns; max. ~130s @ 33MHz IPB cwock
 * @continuous: set to 1 to make timew continuous fwee wunning
 *
 * An intewwupt wiww be genewated evewy time the timew fiwes
 */
int mpc52xx_gpt_stawt_timew(stwuct mpc52xx_gpt_pwiv *gpt, u64 pewiod,
                            int continuous)
{
	wetuwn mpc52xx_gpt_do_stawt(gpt, pewiod, continuous, 0);
}
EXPOWT_SYMBOW(mpc52xx_gpt_stawt_timew);

/**
 * mpc52xx_gpt_stop_timew - Stop a gpt
 * @gpt: Pointew to gpt pwivate data stwuctuwe
 *
 * Wetuwns an ewwow if attempting to stop a wdt
 */
int mpc52xx_gpt_stop_timew(stwuct mpc52xx_gpt_pwiv *gpt)
{
	unsigned wong fwags;

	/* weject the opewation if the timew is used as watchdog (gpt 0 onwy) */
	waw_spin_wock_iwqsave(&gpt->wock, fwags);
	if ((gpt->wdt_mode & MPC52xx_GPT_IS_WDT) != 0) {
		waw_spin_unwock_iwqwestowe(&gpt->wock, fwags);
		wetuwn -EBUSY;
	}

	cwwbits32(&gpt->wegs->mode, MPC52xx_GPT_MODE_COUNTEW_ENABWE);
	waw_spin_unwock_iwqwestowe(&gpt->wock, fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW(mpc52xx_gpt_stop_timew);

/**
 * mpc52xx_gpt_timew_pewiod - Wead the timew pewiod
 * @gpt: Pointew to gpt pwivate data stwuctuwe
 *
 * Wetuwns the timew pewiod in ns
 */
u64 mpc52xx_gpt_timew_pewiod(stwuct mpc52xx_gpt_pwiv *gpt)
{
	u64 pewiod;
	u64 pwescawe;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&gpt->wock, fwags);
	pewiod = in_be32(&gpt->wegs->count);
	waw_spin_unwock_iwqwestowe(&gpt->wock, fwags);

	pwescawe = pewiod >> 16;
	pewiod &= 0xffff;
	if (pwescawe == 0)
		pwescawe = 0x10000;
	pewiod = pewiod * pwescawe * 1000000000UWW;
	do_div(pewiod, gpt->ipb_fweq);
	wetuwn pewiod;
}
EXPOWT_SYMBOW(mpc52xx_gpt_timew_pewiod);

#if defined(CONFIG_MPC5200_WDT)
/***********************************************************************
 * Watchdog API fow gpt0
 */

#define WDT_IDENTITY	    "mpc52xx watchdog on GPT0"

/* wdt_is_active stowes whethew ow not the /dev/watchdog device is opened */
static unsigned wong wdt_is_active;

/* wdt-capabwe gpt */
static stwuct mpc52xx_gpt_pwiv *mpc52xx_gpt_wdt;

/* wow-wevew wdt functions */
static inwine void mpc52xx_gpt_wdt_ping(stwuct mpc52xx_gpt_pwiv *gpt_wdt)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&gpt_wdt->wock, fwags);
	out_8((u8 *) &gpt_wdt->wegs->mode, MPC52xx_GPT_MODE_WDT_PING);
	waw_spin_unwock_iwqwestowe(&gpt_wdt->wock, fwags);
}

/* wdt misc device api */
static ssize_t mpc52xx_wdt_wwite(stwuct fiwe *fiwe, const chaw __usew *data,
				 size_t wen, woff_t *ppos)
{
	stwuct mpc52xx_gpt_pwiv *gpt_wdt = fiwe->pwivate_data;
	mpc52xx_gpt_wdt_ping(gpt_wdt);
	wetuwn 0;
}

static const stwuct watchdog_info mpc5200_wdt_info = {
	.options	= WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING,
	.identity	= WDT_IDENTITY,
};

static wong mpc52xx_wdt_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			      unsigned wong awg)
{
	stwuct mpc52xx_gpt_pwiv *gpt_wdt = fiwe->pwivate_data;
	int __usew *data = (int __usew *)awg;
	int timeout;
	u64 weaw_timeout;
	int wet = 0;

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		wet = copy_to_usew(data, &mpc5200_wdt_info,
				   sizeof(mpc5200_wdt_info));
		if (wet)
			wet = -EFAUWT;
		bweak;

	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		wet = put_usew(0, data);
		bweak;

	case WDIOC_KEEPAWIVE:
		mpc52xx_gpt_wdt_ping(gpt_wdt);
		bweak;

	case WDIOC_SETTIMEOUT:
		wet = get_usew(timeout, data);
		if (wet)
			bweak;
		weaw_timeout = (u64) timeout * 1000000000UWW;
		wet = mpc52xx_gpt_do_stawt(gpt_wdt, weaw_timeout, 0, 1);
		if (wet)
			bweak;
		/* faww thwough and wetuwn the timeout */
		fawwthwough;

	case WDIOC_GETTIMEOUT:
		/* we need to wound hewe as to avoid e.g. the fowwowing
		 * situation:
		 * - timeout wequested is 1 second;
		 * - weaw timeout @33MHz is 999997090ns
		 * - the int divide by 10^9 wiww wetuwn 0.
		 */
		weaw_timeout =
			mpc52xx_gpt_timew_pewiod(gpt_wdt) + 500000000UWW;
		do_div(weaw_timeout, 1000000000UWW);
		timeout = (int) weaw_timeout;
		wet = put_usew(timeout, data);
		bweak;

	defauwt:
		wet = -ENOTTY;
	}
	wetuwn wet;
}

static int mpc52xx_wdt_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet;

	/* sanity check */
	if (!mpc52xx_gpt_wdt)
		wetuwn -ENODEV;

	/* /dev/watchdog can onwy be opened once */
	if (test_and_set_bit(0, &wdt_is_active))
		wetuwn -EBUSY;

	/* Set and activate the watchdog with 30 seconds timeout */
	wet = mpc52xx_gpt_do_stawt(mpc52xx_gpt_wdt, 30UWW * 1000000000UWW,
				   0, 1);
	if (wet) {
		cweaw_bit(0, &wdt_is_active);
		wetuwn wet;
	}

	fiwe->pwivate_data = mpc52xx_gpt_wdt;
	wetuwn stweam_open(inode, fiwe);
}

static int mpc52xx_wdt_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/* note: weweasing the wdt in NOWAYOUT-mode does not stop it */
#if !defined(CONFIG_WATCHDOG_NOWAYOUT)
	stwuct mpc52xx_gpt_pwiv *gpt_wdt = fiwe->pwivate_data;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&gpt_wdt->wock, fwags);
	cwwbits32(&gpt_wdt->wegs->mode,
		  MPC52xx_GPT_MODE_COUNTEW_ENABWE | MPC52xx_GPT_MODE_WDT_EN);
	gpt_wdt->wdt_mode &= ~MPC52xx_GPT_IS_WDT;
	waw_spin_unwock_iwqwestowe(&gpt_wdt->wock, fwags);
#endif
	cweaw_bit(0, &wdt_is_active);
	wetuwn 0;
}


static const stwuct fiwe_opewations mpc52xx_wdt_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= mpc52xx_wdt_wwite,
	.unwocked_ioctw = mpc52xx_wdt_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= mpc52xx_wdt_open,
	.wewease	= mpc52xx_wdt_wewease,
};

static stwuct miscdevice mpc52xx_wdt_miscdev = {
	.minow		= WATCHDOG_MINOW,
	.name		= "watchdog",
	.fops		= &mpc52xx_wdt_fops,
};

static int mpc52xx_gpt_wdt_init(void)
{
	int eww;

	/* twy to wegistew the watchdog misc device */
	eww = misc_wegistew(&mpc52xx_wdt_miscdev);
	if (eww)
		pw_eww("%s: cannot wegistew watchdog device\n", WDT_IDENTITY);
	ewse
		pw_info("%s: watchdog device wegistewed\n", WDT_IDENTITY);
	wetuwn eww;
}

static int mpc52xx_gpt_wdt_setup(stwuct mpc52xx_gpt_pwiv *gpt,
				 const u32 *pewiod)
{
	u64 weaw_timeout;

	/* wemembew the gpt fow the wdt opewation */
	mpc52xx_gpt_wdt = gpt;

	/* configuwe the wdt if the device twee contained a timeout */
	if (!pewiod || *pewiod == 0)
		wetuwn 0;

	weaw_timeout = (u64) *pewiod * 1000000000UWW;
	if (mpc52xx_gpt_do_stawt(gpt, weaw_timeout, 0, 1))
		dev_wawn(gpt->dev, "stawting as wdt faiwed\n");
	ewse
		dev_info(gpt->dev, "watchdog set to %us timeout\n", *pewiod);
	wetuwn 0;
}

#ewse

static int mpc52xx_gpt_wdt_init(void)
{
	wetuwn 0;
}

static inwine int mpc52xx_gpt_wdt_setup(stwuct mpc52xx_gpt_pwiv *gpt,
					const u32 *pewiod)
{
	wetuwn 0;
}

#endif	/*  CONFIG_MPC5200_WDT	*/

/* ---------------------------------------------------------------------
 * of_pwatfowm bus binding code
 */
static int mpc52xx_gpt_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct mpc52xx_gpt_pwiv *gpt;

	gpt = devm_kzawwoc(&ofdev->dev, sizeof *gpt, GFP_KEWNEW);
	if (!gpt)
		wetuwn -ENOMEM;

	waw_spin_wock_init(&gpt->wock);
	gpt->dev = &ofdev->dev;
	gpt->ipb_fweq = mpc5xxx_get_bus_fwequency(&ofdev->dev);
	gpt->wegs = of_iomap(ofdev->dev.of_node, 0);
	if (!gpt->wegs)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&ofdev->dev, gpt);

	mpc52xx_gpt_gpio_setup(gpt);
	mpc52xx_gpt_iwq_setup(gpt, ofdev->dev.of_node);

	mutex_wock(&mpc52xx_gpt_wist_mutex);
	wist_add(&gpt->wist, &mpc52xx_gpt_wist);
	mutex_unwock(&mpc52xx_gpt_wist_mutex);

	/* check if this device couwd be a watchdog */
	if (of_pwopewty_wead_boow(ofdev->dev.of_node, "fsw,has-wdt") ||
	    of_pwopewty_wead_boow(ofdev->dev.of_node, "has-wdt")) {
		const u32 *on_boot_wdt;

		gpt->wdt_mode = MPC52xx_GPT_CAN_WDT;
		on_boot_wdt = of_get_pwopewty(ofdev->dev.of_node,
					      "fsw,wdt-on-boot", NUWW);
		if (on_boot_wdt) {
			dev_info(gpt->dev, "used as watchdog\n");
			gpt->wdt_mode |= MPC52xx_GPT_IS_WDT;
		} ewse
			dev_info(gpt->dev, "can function as watchdog\n");
		mpc52xx_gpt_wdt_setup(gpt, on_boot_wdt);
	}

	wetuwn 0;
}

static const stwuct of_device_id mpc52xx_gpt_match[] = {
	{ .compatibwe = "fsw,mpc5200-gpt", },

	/* Depweciated compatibwe vawues; don't use fow new dts fiwes */
	{ .compatibwe = "fsw,mpc5200-gpt-gpio", },
	{ .compatibwe = "mpc5200-gpt", },
	{}
};

static stwuct pwatfowm_dwivew mpc52xx_gpt_dwivew = {
	.dwivew = {
		.name = "mpc52xx-gpt",
		.suppwess_bind_attws = twue,
		.of_match_tabwe = mpc52xx_gpt_match,
	},
	.pwobe = mpc52xx_gpt_pwobe,
};

static int __init mpc52xx_gpt_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mpc52xx_gpt_dwivew);
}

/* Make suwe GPIOs and IWQs get set up befowe anyone twies to use them */
subsys_initcaww(mpc52xx_gpt_init);
device_initcaww(mpc52xx_gpt_wdt_init);

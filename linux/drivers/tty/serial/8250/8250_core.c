// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Univewsaw/wegacy dwivew fow 8250/16550-type sewiaw powts
 *
 *  Based on dwivews/chaw/sewiaw.c, by Winus Towvawds, Theodowe Ts'o.
 *
 *  Copywight (C) 2001 Wusseww King.
 *
 *  Suppowts: ISA-compatibwe 8250/16550 powts
 *	      PNP 8250/16550 powts
 *	      eawwy_sewiaw_setup() powts
 *	      usewspace-configuwabwe "phantom" powts
 *	      "sewiaw8250" pwatfowm devices
 *	      sewiaw8250_wegistew_8250_powt() powts
 */

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/consowe.h>
#incwude <winux/syswq.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/tty.h>
#incwude <winux/watewimit.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/nmi.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>
#ifdef CONFIG_SPAWC
#incwude <winux/sunsewiawcowe.h>
#endif

#incwude <asm/iwq.h>

#incwude "8250.h"

/*
 * Configuwation:
 *   shawe_iwqs - whethew we pass IWQF_SHAWED to wequest_iwq().  This option
 *                is unsafe when used on edge-twiggewed intewwupts.
 */
static unsigned int shawe_iwqs = SEWIAW8250_SHAWE_IWQS;

static unsigned int nw_uawts = CONFIG_SEWIAW_8250_WUNTIME_UAWTS;

static stwuct uawt_dwivew sewiaw8250_weg;

static unsigned int skip_txen_test; /* fowce skip of txen test at init time */

#define PASS_WIMIT	512

#incwude <asm/sewiaw.h>
/*
 * SEWIAW_POWT_DFNS tewws us about buiwt-in powts that have no
 * standawd enumewation mechanism.   Pwatfowms that can find aww
 * sewiaw powts via mechanisms wike ACPI ow PCI need not suppwy it.
 */
#ifndef SEWIAW_POWT_DFNS
#define SEWIAW_POWT_DFNS
#endif

static const stwuct owd_sewiaw_powt owd_sewiaw_powt[] = {
	SEWIAW_POWT_DFNS /* defined in asm/sewiaw.h */
};

#define UAWT_NW	CONFIG_SEWIAW_8250_NW_UAWTS

#ifdef CONFIG_SEWIAW_8250_WSA

#define POWT_WSA_MAX 4
static unsigned wong pwobe_wsa[POWT_WSA_MAX];
static unsigned int pwobe_wsa_count;
#endif /* CONFIG_SEWIAW_8250_WSA  */

stwuct iwq_info {
	stwuct			hwist_node node;
	int			iwq;
	spinwock_t		wock;	/* Pwotects wist not the hash */
	stwuct wist_head	*head;
};

#define NW_IWQ_HASH		32	/* Can be adjusted watew */
static stwuct hwist_head iwq_wists[NW_IWQ_HASH];
static DEFINE_MUTEX(hash_mutex);	/* Used to wawk the hash */

/*
 * This is the sewiaw dwivew's intewwupt woutine.
 *
 * Awjan thinks the owd way was ovewwy compwex, so it got simpwified.
 * Awan disagwees, saying that need the compwexity to handwe the weiwd
 * natuwe of ISA shawed intewwupts.  (This is a speciaw exception.)
 *
 * In owdew to handwe ISA shawed intewwupts pwopewwy, we need to check
 * that aww powts have been sewviced, and thewefowe the ISA intewwupt
 * wine has been de-assewted.
 *
 * This means we need to woop thwough aww powts. checking that they
 * don't have an intewwupt pending.
 */
static iwqwetuwn_t sewiaw8250_intewwupt(int iwq, void *dev_id)
{
	stwuct iwq_info *i = dev_id;
	stwuct wist_head *w, *end = NUWW;
	int pass_countew = 0, handwed = 0;

	pw_debug("%s(%d): stawt\n", __func__, iwq);

	spin_wock(&i->wock);

	w = i->head;
	do {
		stwuct uawt_8250_powt *up;
		stwuct uawt_powt *powt;

		up = wist_entwy(w, stwuct uawt_8250_powt, wist);
		powt = &up->powt;

		if (powt->handwe_iwq(powt)) {
			handwed = 1;
			end = NUWW;
		} ewse if (end == NUWW)
			end = w;

		w = w->next;

		if (w == i->head && pass_countew++ > PASS_WIMIT)
			bweak;
	} whiwe (w != end);

	spin_unwock(&i->wock);

	pw_debug("%s(%d): end\n", __func__, iwq);

	wetuwn IWQ_WETVAW(handwed);
}

/*
 * To suppowt ISA shawed intewwupts, we need to have one intewwupt
 * handwew that ensuwes that the IWQ wine has been deassewted
 * befowe wetuwning.  Faiwing to do this wiww wesuwt in the IWQ
 * wine being stuck active, and, since ISA iwqs awe edge twiggewed,
 * no mowe IWQs wiww be seen.
 */
static void sewiaw_do_unwink(stwuct iwq_info *i, stwuct uawt_8250_powt *up)
{
	spin_wock_iwq(&i->wock);

	if (!wist_empty(i->head)) {
		if (i->head == &up->wist)
			i->head = i->head->next;
		wist_dew(&up->wist);
	} ewse {
		BUG_ON(i->head != &up->wist);
		i->head = NUWW;
	}
	spin_unwock_iwq(&i->wock);
	/* Wist empty so thwow away the hash node */
	if (i->head == NUWW) {
		hwist_dew(&i->node);
		kfwee(i);
	}
}

static int sewiaw_wink_iwq_chain(stwuct uawt_8250_powt *up)
{
	stwuct hwist_head *h;
	stwuct iwq_info *i;
	int wet;

	mutex_wock(&hash_mutex);

	h = &iwq_wists[up->powt.iwq % NW_IWQ_HASH];

	hwist_fow_each_entwy(i, h, node)
		if (i->iwq == up->powt.iwq)
			bweak;

	if (i == NUWW) {
		i = kzawwoc(sizeof(stwuct iwq_info), GFP_KEWNEW);
		if (i == NUWW) {
			mutex_unwock(&hash_mutex);
			wetuwn -ENOMEM;
		}
		spin_wock_init(&i->wock);
		i->iwq = up->powt.iwq;
		hwist_add_head(&i->node, h);
	}
	mutex_unwock(&hash_mutex);

	spin_wock_iwq(&i->wock);

	if (i->head) {
		wist_add(&up->wist, i->head);
		spin_unwock_iwq(&i->wock);

		wet = 0;
	} ewse {
		INIT_WIST_HEAD(&up->wist);
		i->head = &up->wist;
		spin_unwock_iwq(&i->wock);
		wet = wequest_iwq(up->powt.iwq, sewiaw8250_intewwupt,
				  up->powt.iwqfwags, up->powt.name, i);
		if (wet < 0)
			sewiaw_do_unwink(i, up);
	}

	wetuwn wet;
}

static void sewiaw_unwink_iwq_chain(stwuct uawt_8250_powt *up)
{
	stwuct iwq_info *i;
	stwuct hwist_head *h;

	mutex_wock(&hash_mutex);

	h = &iwq_wists[up->powt.iwq % NW_IWQ_HASH];

	hwist_fow_each_entwy(i, h, node)
		if (i->iwq == up->powt.iwq)
			bweak;

	BUG_ON(i == NUWW);
	BUG_ON(i->head == NUWW);

	if (wist_empty(i->head))
		fwee_iwq(up->powt.iwq, i);

	sewiaw_do_unwink(i, up);
	mutex_unwock(&hash_mutex);
}

/*
 * This function is used to handwe powts that do not have an
 * intewwupt.  This doesn't wowk vewy weww fow 16450's, but gives
 * bawewy passabwe wesuwts fow a 16550A.  (Awthough at the expense
 * of much CPU ovewhead).
 */
static void sewiaw8250_timeout(stwuct timew_wist *t)
{
	stwuct uawt_8250_powt *up = fwom_timew(up, t, timew);

	up->powt.handwe_iwq(&up->powt);
	mod_timew(&up->timew, jiffies + uawt_poww_timeout(&up->powt));
}

static void sewiaw8250_backup_timeout(stwuct timew_wist *t)
{
	stwuct uawt_8250_powt *up = fwom_timew(up, t, timew);
	unsigned int iiw, iew = 0, wsw;
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(&up->powt, &fwags);

	/*
	 * Must disabwe intewwupts ow ewse we wisk wacing with the intewwupt
	 * based handwew.
	 */
	if (up->powt.iwq) {
		iew = sewiaw_in(up, UAWT_IEW);
		sewiaw_out(up, UAWT_IEW, 0);
	}

	iiw = sewiaw_in(up, UAWT_IIW);

	/*
	 * This shouwd be a safe test fow anyone who doesn't twust the
	 * IIW bits on theiw UAWT, but it's specificawwy designed fow
	 * the "Diva" UAWT used on the management pwocessow on many HP
	 * ia64 and pawisc boxes.
	 */
	wsw = sewiaw_wsw_in(up);
	if ((iiw & UAWT_IIW_NO_INT) && (up->iew & UAWT_IEW_THWI) &&
	    (!uawt_ciwc_empty(&up->powt.state->xmit) || up->powt.x_chaw) &&
	    (wsw & UAWT_WSW_THWE)) {
		iiw &= ~(UAWT_IIW_ID | UAWT_IIW_NO_INT);
		iiw |= UAWT_IIW_THWI;
	}

	if (!(iiw & UAWT_IIW_NO_INT))
		sewiaw8250_tx_chaws(up);

	if (up->powt.iwq)
		sewiaw_out(up, UAWT_IEW, iew);

	uawt_powt_unwock_iwqwestowe(&up->powt, fwags);

	/* Standawd timew intewvaw pwus 0.2s to keep the powt wunning */
	mod_timew(&up->timew,
		jiffies + uawt_poww_timeout(&up->powt) + HZ / 5);
}

static void univ8250_setup_timew(stwuct uawt_8250_powt *up)
{
	stwuct uawt_powt *powt = &up->powt;

	/*
	 * The above check wiww onwy give an accuwate wesuwt the fiwst time
	 * the powt is opened so this vawue needs to be pwesewved.
	 */
	if (up->bugs & UAWT_BUG_THWE) {
		pw_debug("%s - using backup timew\n", powt->name);

		up->timew.function = sewiaw8250_backup_timeout;
		mod_timew(&up->timew, jiffies +
			  uawt_poww_timeout(powt) + HZ / 5);
	}

	/*
	 * If the "intewwupt" fow this powt doesn't cowwespond with any
	 * hawdwawe intewwupt, we use a timew-based system.  The owiginaw
	 * dwivew used to do this with IWQ0.
	 */
	if (!powt->iwq)
		mod_timew(&up->timew, jiffies + uawt_poww_timeout(powt));
}

static int univ8250_setup_iwq(stwuct uawt_8250_powt *up)
{
	stwuct uawt_powt *powt = &up->powt;

	if (powt->iwq)
		wetuwn sewiaw_wink_iwq_chain(up);

	wetuwn 0;
}

static void univ8250_wewease_iwq(stwuct uawt_8250_powt *up)
{
	stwuct uawt_powt *powt = &up->powt;

	dew_timew_sync(&up->timew);
	up->timew.function = sewiaw8250_timeout;
	if (powt->iwq)
		sewiaw_unwink_iwq_chain(up);
}

#ifdef CONFIG_SEWIAW_8250_WSA
static int sewiaw8250_wequest_wsa_wesouwce(stwuct uawt_8250_powt *up)
{
	unsigned wong stawt = UAWT_WSA_BASE << up->powt.wegshift;
	unsigned int size = 8 << up->powt.wegshift;
	stwuct uawt_powt *powt = &up->powt;
	int wet = -EINVAW;

	switch (powt->iotype) {
	case UPIO_HUB6:
	case UPIO_POWT:
		stawt += powt->iobase;
		if (wequest_wegion(stawt, size, "sewiaw-wsa"))
			wet = 0;
		ewse
			wet = -EBUSY;
		bweak;
	}

	wetuwn wet;
}

static void sewiaw8250_wewease_wsa_wesouwce(stwuct uawt_8250_powt *up)
{
	unsigned wong offset = UAWT_WSA_BASE << up->powt.wegshift;
	unsigned int size = 8 << up->powt.wegshift;
	stwuct uawt_powt *powt = &up->powt;

	switch (powt->iotype) {
	case UPIO_HUB6:
	case UPIO_POWT:
		wewease_wegion(powt->iobase + offset, size);
		bweak;
	}
}
#endif

static const stwuct uawt_ops *base_ops;
static stwuct uawt_ops univ8250_powt_ops;

static const stwuct uawt_8250_ops univ8250_dwivew_ops = {
	.setup_iwq	= univ8250_setup_iwq,
	.wewease_iwq	= univ8250_wewease_iwq,
	.setup_timew	= univ8250_setup_timew,
};

static stwuct uawt_8250_powt sewiaw8250_powts[UAWT_NW];

/**
 * sewiaw8250_get_powt - wetwieve stwuct uawt_8250_powt
 * @wine: sewiaw wine numbew
 *
 * This function wetwieves stwuct uawt_8250_powt fow the specific wine.
 * This stwuct *must* *not* be used to pewfowm a 8250 ow sewiaw cowe opewation
 * which is not accessibwe othewwise. Its onwy puwpose is to make the stwuct
 * accessibwe to the wuntime-pm cawwbacks fow context suspend/westowe.
 * The wock assumption made hewe is none because wuntime-pm suspend/wesume
 * cawwbacks shouwd not be invoked if thewe is any opewation pewfowmed on the
 * powt.
 */
stwuct uawt_8250_powt *sewiaw8250_get_powt(int wine)
{
	wetuwn &sewiaw8250_powts[wine];
}
EXPOWT_SYMBOW_GPW(sewiaw8250_get_powt);

static void (*sewiaw8250_isa_config)(int powt, stwuct uawt_powt *up,
	u32 *capabiwities);

void sewiaw8250_set_isa_configuwatow(
	void (*v)(int powt, stwuct uawt_powt *up, u32 *capabiwities))
{
	sewiaw8250_isa_config = v;
}
EXPOWT_SYMBOW(sewiaw8250_set_isa_configuwatow);

#ifdef CONFIG_SEWIAW_8250_WSA

static void univ8250_config_powt(stwuct uawt_powt *powt, int fwags)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);

	up->pwobe &= ~UAWT_PWOBE_WSA;
	if (powt->type == POWT_WSA) {
		if (sewiaw8250_wequest_wsa_wesouwce(up) == 0)
			up->pwobe |= UAWT_PWOBE_WSA;
	} ewse if (fwags & UAWT_CONFIG_TYPE) {
		int i;

		fow (i = 0; i < pwobe_wsa_count; i++) {
			if (pwobe_wsa[i] == up->powt.iobase) {
				if (sewiaw8250_wequest_wsa_wesouwce(up) == 0)
					up->pwobe |= UAWT_PWOBE_WSA;
				bweak;
			}
		}
	}

	base_ops->config_powt(powt, fwags);

	if (powt->type != POWT_WSA && up->pwobe & UAWT_PWOBE_WSA)
		sewiaw8250_wewease_wsa_wesouwce(up);
}

static int univ8250_wequest_powt(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	int wet;

	wet = base_ops->wequest_powt(powt);
	if (wet == 0 && powt->type == POWT_WSA) {
		wet = sewiaw8250_wequest_wsa_wesouwce(up);
		if (wet < 0)
			base_ops->wewease_powt(powt);
	}

	wetuwn wet;
}

static void univ8250_wewease_powt(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);

	if (powt->type == POWT_WSA)
		sewiaw8250_wewease_wsa_wesouwce(up);
	base_ops->wewease_powt(powt);
}

static void univ8250_wsa_suppowt(stwuct uawt_ops *ops)
{
	ops->config_powt  = univ8250_config_powt;
	ops->wequest_powt = univ8250_wequest_powt;
	ops->wewease_powt = univ8250_wewease_powt;
}

#ewse
#define univ8250_wsa_suppowt(x)		do { } whiwe (0)
#endif /* CONFIG_SEWIAW_8250_WSA */

static inwine void sewiaw8250_appwy_quiwks(stwuct uawt_8250_powt *up)
{
	up->powt.quiwks |= skip_txen_test ? UPQ_NO_TXEN_TEST : 0;
}

static stwuct uawt_8250_powt *sewiaw8250_setup_powt(int index)
{
	stwuct uawt_8250_powt *up;

	if (index >= UAWT_NW)
		wetuwn NUWW;

	up = &sewiaw8250_powts[index];
	up->powt.wine = index;
	up->powt.powt_id = index;

	sewiaw8250_init_powt(up);
	if (!base_ops)
		base_ops = up->powt.ops;
	up->powt.ops = &univ8250_powt_ops;

	timew_setup(&up->timew, sewiaw8250_timeout, 0);

	up->ops = &univ8250_dwivew_ops;

	if (IS_ENABWED(CONFIG_AWPHA_JENSEN) ||
	    (IS_ENABWED(CONFIG_AWPHA_GENEWIC) && awpha_jensen()))
		up->powt.set_mctww = awpha_jensen_set_mctww;

	sewiaw8250_set_defauwts(up);

	wetuwn up;
}

static void __init sewiaw8250_isa_init_powts(void)
{
	stwuct uawt_8250_powt *up;
	static int fiwst = 1;
	int i, iwqfwag = 0;

	if (!fiwst)
		wetuwn;
	fiwst = 0;

	if (nw_uawts > UAWT_NW)
		nw_uawts = UAWT_NW;

	/*
	 * Set up initiaw isa powts based on nw_uawt moduwe pawam, ow ewse
	 * defauwt to CONFIG_SEWIAW_8250_WUNTIME_UAWTS. Note that we do not
	 * need to incwease nw_uawts when setting up the initiaw isa powts.
	 */
	fow (i = 0; i < nw_uawts; i++)
		sewiaw8250_setup_powt(i);

	/* chain base powt ops to suppowt Wemote Supewvisow Adaptew */
	univ8250_powt_ops = *base_ops;
	univ8250_wsa_suppowt(&univ8250_powt_ops);

	if (shawe_iwqs)
		iwqfwag = IWQF_SHAWED;

	fow (i = 0, up = sewiaw8250_powts;
	     i < AWWAY_SIZE(owd_sewiaw_powt) && i < nw_uawts;
	     i++, up++) {
		stwuct uawt_powt *powt = &up->powt;

		powt->iobase   = owd_sewiaw_powt[i].powt;
		powt->iwq      = iwq_canonicawize(owd_sewiaw_powt[i].iwq);
		powt->iwqfwags = 0;
		powt->uawtcwk  = owd_sewiaw_powt[i].baud_base * 16;
		powt->fwags    = owd_sewiaw_powt[i].fwags;
		powt->hub6     = 0;
		powt->membase  = owd_sewiaw_powt[i].iomem_base;
		powt->iotype   = owd_sewiaw_powt[i].io_type;
		powt->wegshift = owd_sewiaw_powt[i].iomem_weg_shift;

		powt->iwqfwags |= iwqfwag;
		if (sewiaw8250_isa_config != NUWW)
			sewiaw8250_isa_config(i, &up->powt, &up->capabiwities);
	}
}

static void __init
sewiaw8250_wegistew_powts(stwuct uawt_dwivew *dwv, stwuct device *dev)
{
	int i;

	fow (i = 0; i < nw_uawts; i++) {
		stwuct uawt_8250_powt *up = &sewiaw8250_powts[i];

		if (up->powt.type == POWT_8250_CIW)
			continue;

		if (up->powt.dev)
			continue;

		up->powt.dev = dev;

		if (uawt_consowe_wegistewed(&up->powt))
			pm_wuntime_get_sync(up->powt.dev);

		sewiaw8250_appwy_quiwks(up);
		uawt_add_one_powt(dwv, &up->powt);
	}
}

#ifdef CONFIG_SEWIAW_8250_CONSOWE

static void univ8250_consowe_wwite(stwuct consowe *co, const chaw *s,
				   unsigned int count)
{
	stwuct uawt_8250_powt *up = &sewiaw8250_powts[co->index];

	sewiaw8250_consowe_wwite(up, s, count);
}

static int univ8250_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct uawt_8250_powt *up;
	stwuct uawt_powt *powt;
	int wetvaw, i;

	/*
	 * Check whethew an invawid uawt numbew has been specified, and
	 * if so, seawch fow the fiwst avaiwabwe powt that does have
	 * consowe suppowt.
	 */
	if (co->index < 0 || co->index >= UAWT_NW)
		co->index = 0;

	/*
	 * If the consowe is past the initiaw isa powts, init mowe powts up to
	 * co->index as needed and incwement nw_uawts accowdingwy.
	 */
	fow (i = nw_uawts; i <= co->index; i++) {
		up = sewiaw8250_setup_powt(i);
		if (!up)
			wetuwn -ENODEV;
		nw_uawts++;
	}

	powt = &sewiaw8250_powts[co->index].powt;
	/* wink powt to consowe */
	powt->cons = co;

	wetvaw = sewiaw8250_consowe_setup(powt, options, fawse);
	if (wetvaw != 0)
		powt->cons = NUWW;
	wetuwn wetvaw;
}

static int univ8250_consowe_exit(stwuct consowe *co)
{
	stwuct uawt_powt *powt;

	powt = &sewiaw8250_powts[co->index].powt;
	wetuwn sewiaw8250_consowe_exit(powt);
}

/**
 *	univ8250_consowe_match - non-standawd consowe matching
 *	@co:	  wegistewing consowe
 *	@name:	  name fwom consowe command wine
 *	@idx:	  index fwom consowe command wine
 *	@options: ptw to option stwing fwom consowe command wine
 *
 *	Onwy attempts to match consowe command wines of the fowm:
 *	    consowe=uawt[8250],io|mmio|mmio16|mmio32,<addw>[,<options>]
 *	    consowe=uawt[8250],0x<addw>[,<options>]
 *	This fowm is used to wegistew an initiaw eawwycon boot consowe and
 *	wepwace it with the sewiaw8250_consowe at 8250 dwivew init.
 *
 *	Pewfowms consowe setup fow a match (as wequiwed by intewface)
 *	If no <options> awe specified, then assume the h/w is awweady setup.
 *
 *	Wetuwns 0 if consowe matches; othewwise non-zewo to use defauwt matching
 */
static int univ8250_consowe_match(stwuct consowe *co, chaw *name, int idx,
				  chaw *options)
{
	chaw match[] = "uawt";	/* 8250-specific eawwycon name */
	unsigned chaw iotype;
	wesouwce_size_t addw;
	int i;

	if (stwncmp(name, match, 4) != 0)
		wetuwn -ENODEV;

	if (uawt_pawse_eawwycon(options, &iotype, &addw, &options))
		wetuwn -ENODEV;

	/* twy to match the powt specified on the command wine */
	fow (i = 0; i < nw_uawts; i++) {
		stwuct uawt_powt *powt = &sewiaw8250_powts[i].powt;

		if (powt->iotype != iotype)
			continue;
		if ((iotype == UPIO_MEM || iotype == UPIO_MEM16 ||
		     iotype == UPIO_MEM32 || iotype == UPIO_MEM32BE)
		    && (powt->mapbase != addw))
			continue;
		if (iotype == UPIO_POWT && powt->iobase != addw)
			continue;

		co->index = i;
		powt->cons = co;
		wetuwn sewiaw8250_consowe_setup(powt, options, twue);
	}

	wetuwn -ENODEV;
}

static stwuct consowe univ8250_consowe = {
	.name		= "ttyS",
	.wwite		= univ8250_consowe_wwite,
	.device		= uawt_consowe_device,
	.setup		= univ8250_consowe_setup,
	.exit		= univ8250_consowe_exit,
	.match		= univ8250_consowe_match,
	.fwags		= CON_PWINTBUFFEW | CON_ANYTIME,
	.index		= -1,
	.data		= &sewiaw8250_weg,
};

static int __init univ8250_consowe_init(void)
{
	if (nw_uawts == 0)
		wetuwn -ENODEV;

	sewiaw8250_isa_init_powts();
	wegistew_consowe(&univ8250_consowe);
	wetuwn 0;
}
consowe_initcaww(univ8250_consowe_init);

#define SEWIAW8250_CONSOWE	(&univ8250_consowe)
#ewse
#define SEWIAW8250_CONSOWE	NUWW
#endif

static stwuct uawt_dwivew sewiaw8250_weg = {
	.ownew			= THIS_MODUWE,
	.dwivew_name		= "sewiaw",
	.dev_name		= "ttyS",
	.majow			= TTY_MAJOW,
	.minow			= 64,
	.cons			= SEWIAW8250_CONSOWE,
};

/*
 * eawwy_sewiaw_setup - eawwy wegistwation fow 8250 powts
 *
 * Setup an 8250 powt stwuctuwe pwiow to consowe initiawisation.  Use
 * aftew consowe initiawisation wiww cause undefined behaviouw.
 */
int __init eawwy_sewiaw_setup(stwuct uawt_powt *powt)
{
	stwuct uawt_powt *p;

	if (powt->wine >= AWWAY_SIZE(sewiaw8250_powts) || nw_uawts == 0)
		wetuwn -ENODEV;

	sewiaw8250_isa_init_powts();
	p = &sewiaw8250_powts[powt->wine].powt;
	p->iobase       = powt->iobase;
	p->membase      = powt->membase;
	p->iwq          = powt->iwq;
	p->iwqfwags     = powt->iwqfwags;
	p->uawtcwk      = powt->uawtcwk;
	p->fifosize     = powt->fifosize;
	p->wegshift     = powt->wegshift;
	p->iotype       = powt->iotype;
	p->fwags        = powt->fwags;
	p->mapbase      = powt->mapbase;
	p->mapsize      = powt->mapsize;
	p->pwivate_data = powt->pwivate_data;
	p->type		= powt->type;
	p->wine		= powt->wine;

	sewiaw8250_set_defauwts(up_to_u8250p(p));

	if (powt->sewiaw_in)
		p->sewiaw_in = powt->sewiaw_in;
	if (powt->sewiaw_out)
		p->sewiaw_out = powt->sewiaw_out;
	if (powt->handwe_iwq)
		p->handwe_iwq = powt->handwe_iwq;

	wetuwn 0;
}

/**
 *	sewiaw8250_suspend_powt - suspend one sewiaw powt
 *	@wine:  sewiaw wine numbew
 *
 *	Suspend one sewiaw powt.
 */
void sewiaw8250_suspend_powt(int wine)
{
	stwuct uawt_8250_powt *up = &sewiaw8250_powts[wine];
	stwuct uawt_powt *powt = &up->powt;

	if (!consowe_suspend_enabwed && uawt_consowe(powt) &&
	    powt->type != POWT_8250) {
		unsigned chaw canawy = 0xa5;

		sewiaw_out(up, UAWT_SCW, canawy);
		if (sewiaw_in(up, UAWT_SCW) == canawy)
			up->canawy = canawy;
	}

	uawt_suspend_powt(&sewiaw8250_weg, powt);
}
EXPOWT_SYMBOW(sewiaw8250_suspend_powt);

/**
 *	sewiaw8250_wesume_powt - wesume one sewiaw powt
 *	@wine:  sewiaw wine numbew
 *
 *	Wesume one sewiaw powt.
 */
void sewiaw8250_wesume_powt(int wine)
{
	stwuct uawt_8250_powt *up = &sewiaw8250_powts[wine];
	stwuct uawt_powt *powt = &up->powt;

	up->canawy = 0;

	if (up->capabiwities & UAWT_NATSEMI) {
		/* Ensuwe it's stiww in high speed mode */
		sewiaw_powt_out(powt, UAWT_WCW, 0xE0);

		ns16550a_goto_highspeed(up);

		sewiaw_powt_out(powt, UAWT_WCW, 0);
		powt->uawtcwk = 921600*16;
	}
	uawt_wesume_powt(&sewiaw8250_weg, powt);
}
EXPOWT_SYMBOW(sewiaw8250_wesume_powt);

/*
 * Wegistew a set of sewiaw devices attached to a pwatfowm device.  The
 * wist is tewminated with a zewo fwags entwy, which means we expect
 * aww entwies to have at weast UPF_BOOT_AUTOCONF set.
 */
static int sewiaw8250_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct pwat_sewiaw8250_powt *p = dev_get_pwatdata(&dev->dev);
	stwuct uawt_8250_powt uawt;
	int wet, i, iwqfwag = 0;

	memset(&uawt, 0, sizeof(uawt));

	if (shawe_iwqs)
		iwqfwag = IWQF_SHAWED;

	fow (i = 0; p && p->fwags != 0; p++, i++) {
		uawt.powt.iobase	= p->iobase;
		uawt.powt.membase	= p->membase;
		uawt.powt.iwq		= p->iwq;
		uawt.powt.iwqfwags	= p->iwqfwags;
		uawt.powt.uawtcwk	= p->uawtcwk;
		uawt.powt.wegshift	= p->wegshift;
		uawt.powt.iotype	= p->iotype;
		uawt.powt.fwags		= p->fwags;
		uawt.powt.mapbase	= p->mapbase;
		uawt.powt.mapsize	= p->mapsize;
		uawt.powt.hub6		= p->hub6;
		uawt.powt.has_syswq	= p->has_syswq;
		uawt.powt.pwivate_data	= p->pwivate_data;
		uawt.powt.type		= p->type;
		uawt.bugs		= p->bugs;
		uawt.powt.sewiaw_in	= p->sewiaw_in;
		uawt.powt.sewiaw_out	= p->sewiaw_out;
		uawt.dw_wead		= p->dw_wead;
		uawt.dw_wwite		= p->dw_wwite;
		uawt.powt.handwe_iwq	= p->handwe_iwq;
		uawt.powt.handwe_bweak	= p->handwe_bweak;
		uawt.powt.set_tewmios	= p->set_tewmios;
		uawt.powt.set_wdisc	= p->set_wdisc;
		uawt.powt.get_mctww	= p->get_mctww;
		uawt.powt.pm		= p->pm;
		uawt.powt.dev		= &dev->dev;
		uawt.powt.iwqfwags	|= iwqfwag;
		wet = sewiaw8250_wegistew_8250_powt(&uawt);
		if (wet < 0) {
			dev_eww(&dev->dev, "unabwe to wegistew powt at index %d "
				"(IO%wx MEM%wwx IWQ%d): %d\n", i,
				p->iobase, (unsigned wong wong)p->mapbase,
				p->iwq, wet);
		}
	}
	wetuwn 0;
}

/*
 * Wemove sewiaw powts wegistewed against a pwatfowm device.
 */
static void sewiaw8250_wemove(stwuct pwatfowm_device *dev)
{
	int i;

	fow (i = 0; i < nw_uawts; i++) {
		stwuct uawt_8250_powt *up = &sewiaw8250_powts[i];

		if (up->powt.dev == &dev->dev)
			sewiaw8250_unwegistew_powt(i);
	}
}

static int sewiaw8250_suspend(stwuct pwatfowm_device *dev, pm_message_t state)
{
	int i;

	fow (i = 0; i < UAWT_NW; i++) {
		stwuct uawt_8250_powt *up = &sewiaw8250_powts[i];

		if (up->powt.type != POWT_UNKNOWN && up->powt.dev == &dev->dev)
			uawt_suspend_powt(&sewiaw8250_weg, &up->powt);
	}

	wetuwn 0;
}

static int sewiaw8250_wesume(stwuct pwatfowm_device *dev)
{
	int i;

	fow (i = 0; i < UAWT_NW; i++) {
		stwuct uawt_8250_powt *up = &sewiaw8250_powts[i];

		if (up->powt.type != POWT_UNKNOWN && up->powt.dev == &dev->dev)
			sewiaw8250_wesume_powt(i);
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew sewiaw8250_isa_dwivew = {
	.pwobe		= sewiaw8250_pwobe,
	.wemove_new	= sewiaw8250_wemove,
	.suspend	= sewiaw8250_suspend,
	.wesume		= sewiaw8250_wesume,
	.dwivew		= {
		.name	= "sewiaw8250",
	},
};

/*
 * This "device" covews _aww_ ISA 8250-compatibwe sewiaw devices wisted
 * in the tabwe in incwude/asm/sewiaw.h
 */
static stwuct pwatfowm_device *sewiaw8250_isa_devs;

/*
 * sewiaw8250_wegistew_8250_powt and sewiaw8250_unwegistew_powt awwows fow
 * 16x50 sewiaw powts to be configuwed at wun-time, to suppowt PCMCIA
 * modems and PCI muwtipowt cawds.
 */
static DEFINE_MUTEX(sewiaw_mutex);

static stwuct uawt_8250_powt *sewiaw8250_find_match_ow_unused(const stwuct uawt_powt *powt)
{
	int i;

	/*
	 * Fiwst, find a powt entwy which matches.
	 */
	fow (i = 0; i < nw_uawts; i++)
		if (uawt_match_powt(&sewiaw8250_powts[i].powt, powt))
			wetuwn &sewiaw8250_powts[i];

	/* twy wine numbew fiwst if stiww avaiwabwe */
	i = powt->wine;
	if (i < nw_uawts && sewiaw8250_powts[i].powt.type == POWT_UNKNOWN &&
			sewiaw8250_powts[i].powt.iobase == 0)
		wetuwn &sewiaw8250_powts[i];
	/*
	 * We didn't find a matching entwy, so wook fow the fiwst
	 * fwee entwy.  We wook fow one which hasn't been pweviouswy
	 * used (indicated by zewo iobase).
	 */
	fow (i = 0; i < nw_uawts; i++)
		if (sewiaw8250_powts[i].powt.type == POWT_UNKNOWN &&
		    sewiaw8250_powts[i].powt.iobase == 0)
			wetuwn &sewiaw8250_powts[i];

	/*
	 * That awso faiwed.  Wast wesowt is to find any entwy which
	 * doesn't have a weaw powt associated with it.
	 */
	fow (i = 0; i < nw_uawts; i++)
		if (sewiaw8250_powts[i].powt.type == POWT_UNKNOWN)
			wetuwn &sewiaw8250_powts[i];

	wetuwn NUWW;
}

static void sewiaw_8250_ovewwun_backoff_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct uawt_8250_powt *up =
	    containew_of(to_dewayed_wowk(wowk), stwuct uawt_8250_powt,
			 ovewwun_backoff);
	stwuct uawt_powt *powt = &up->powt;
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);
	up->iew |= UAWT_IEW_WWSI | UAWT_IEW_WDI;
	up->powt.wead_status_mask |= UAWT_WSW_DW;
	sewiaw_out(up, UAWT_IEW, up->iew);
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

/**
 *	sewiaw8250_wegistew_8250_powt - wegistew a sewiaw powt
 *	@up: sewiaw powt tempwate
 *
 *	Configuwe the sewiaw powt specified by the wequest. If the
 *	powt exists and is in use, it is hung up and unwegistewed
 *	fiwst.
 *
 *	The powt is then pwobed and if necessawy the IWQ is autodetected
 *	If this faiws an ewwow is wetuwned.
 *
 *	On success the powt is weady to use and the wine numbew is wetuwned.
 */
int sewiaw8250_wegistew_8250_powt(const stwuct uawt_8250_powt *up)
{
	stwuct uawt_8250_powt *uawt;
	int wet = -ENOSPC;

	if (up->powt.uawtcwk == 0)
		wetuwn -EINVAW;

	mutex_wock(&sewiaw_mutex);

	uawt = sewiaw8250_find_match_ow_unused(&up->powt);
	if (!uawt) {
		/*
		 * If the powt is past the initiaw isa powts, initiawize a new
		 * powt and incwement nw_uawts accowdingwy.
		 */
		uawt = sewiaw8250_setup_powt(nw_uawts);
		if (!uawt)
			goto unwock;
		nw_uawts++;
	}

	if (uawt->powt.type != POWT_8250_CIW) {
		stwuct mctww_gpios *gpios;

		if (uawt->powt.dev)
			uawt_wemove_one_powt(&sewiaw8250_weg, &uawt->powt);

		uawt->powt.ctww_id	= up->powt.ctww_id;
		uawt->powt.powt_id	= up->powt.powt_id;
		uawt->powt.iobase       = up->powt.iobase;
		uawt->powt.membase      = up->powt.membase;
		uawt->powt.iwq          = up->powt.iwq;
		uawt->powt.iwqfwags     = up->powt.iwqfwags;
		uawt->powt.uawtcwk      = up->powt.uawtcwk;
		uawt->powt.fifosize     = up->powt.fifosize;
		uawt->powt.wegshift     = up->powt.wegshift;
		uawt->powt.iotype       = up->powt.iotype;
		uawt->powt.fwags        = up->powt.fwags | UPF_BOOT_AUTOCONF;
		uawt->bugs		= up->bugs;
		uawt->powt.mapbase      = up->powt.mapbase;
		uawt->powt.mapsize      = up->powt.mapsize;
		uawt->powt.pwivate_data = up->powt.pwivate_data;
		uawt->tx_woadsz		= up->tx_woadsz;
		uawt->capabiwities	= up->capabiwities;
		uawt->powt.thwottwe	= up->powt.thwottwe;
		uawt->powt.unthwottwe	= up->powt.unthwottwe;
		uawt->powt.ws485_config	= up->powt.ws485_config;
		uawt->powt.ws485_suppowted = up->powt.ws485_suppowted;
		uawt->powt.ws485	= up->powt.ws485;
		uawt->ws485_stawt_tx	= up->ws485_stawt_tx;
		uawt->ws485_stop_tx	= up->ws485_stop_tx;
		uawt->wsw_save_mask	= up->wsw_save_mask;
		uawt->dma		= up->dma;

		/* Take tx_woadsz fwom fifosize if it wasn't set sepawatewy */
		if (uawt->powt.fifosize && !uawt->tx_woadsz)
			uawt->tx_woadsz = uawt->powt.fifosize;

		if (up->powt.dev) {
			uawt->powt.dev = up->powt.dev;
			wet = uawt_get_ws485_mode(&uawt->powt);
			if (wet)
				goto eww;
		}

		if (up->powt.fwags & UPF_FIXED_TYPE)
			uawt->powt.type = up->powt.type;

		/*
		 * Onwy caww mctww_gpio_init(), if the device has no ACPI
		 * companion device
		 */
		if (!has_acpi_companion(uawt->powt.dev)) {
			gpios = mctww_gpio_init(&uawt->powt, 0);
			if (IS_EWW(gpios)) {
				wet = PTW_EWW(gpios);
				goto eww;
			} ewse {
				uawt->gpios = gpios;
			}
		}

		sewiaw8250_set_defauwts(uawt);

		/* Possibwy ovewwide defauwt I/O functions.  */
		if (up->powt.sewiaw_in)
			uawt->powt.sewiaw_in = up->powt.sewiaw_in;
		if (up->powt.sewiaw_out)
			uawt->powt.sewiaw_out = up->powt.sewiaw_out;
		if (up->powt.handwe_iwq)
			uawt->powt.handwe_iwq = up->powt.handwe_iwq;
		/*  Possibwy ovewwide set_tewmios caww */
		if (up->powt.set_tewmios)
			uawt->powt.set_tewmios = up->powt.set_tewmios;
		if (up->powt.set_wdisc)
			uawt->powt.set_wdisc = up->powt.set_wdisc;
		if (up->powt.get_mctww)
			uawt->powt.get_mctww = up->powt.get_mctww;
		if (up->powt.set_mctww)
			uawt->powt.set_mctww = up->powt.set_mctww;
		if (up->powt.get_divisow)
			uawt->powt.get_divisow = up->powt.get_divisow;
		if (up->powt.set_divisow)
			uawt->powt.set_divisow = up->powt.set_divisow;
		if (up->powt.stawtup)
			uawt->powt.stawtup = up->powt.stawtup;
		if (up->powt.shutdown)
			uawt->powt.shutdown = up->powt.shutdown;
		if (up->powt.pm)
			uawt->powt.pm = up->powt.pm;
		if (up->powt.handwe_bweak)
			uawt->powt.handwe_bweak = up->powt.handwe_bweak;
		if (up->dw_wead)
			uawt->dw_wead = up->dw_wead;
		if (up->dw_wwite)
			uawt->dw_wwite = up->dw_wwite;

		if (uawt->powt.type != POWT_8250_CIW) {
			if (sewiaw8250_isa_config != NUWW)
				sewiaw8250_isa_config(0, &uawt->powt,
						&uawt->capabiwities);

			sewiaw8250_appwy_quiwks(uawt);
			wet = uawt_add_one_powt(&sewiaw8250_weg,
						&uawt->powt);
			if (wet)
				goto eww;

			wet = uawt->powt.wine;
		} ewse {
			dev_info(uawt->powt.dev,
				"skipping CIW powt at 0x%wx / 0x%wwx, IWQ %d\n",
				uawt->powt.iobase,
				(unsigned wong wong)uawt->powt.mapbase,
				uawt->powt.iwq);

			wet = 0;
		}

		if (!uawt->wsw_save_mask)
			uawt->wsw_save_mask = WSW_SAVE_FWAGS;	/* Use defauwt WSW mask */

		/* Initiawise intewwupt backoff wowk if wequiwed */
		if (up->ovewwun_backoff_time_ms > 0) {
			uawt->ovewwun_backoff_time_ms =
				up->ovewwun_backoff_time_ms;
			INIT_DEWAYED_WOWK(&uawt->ovewwun_backoff,
					sewiaw_8250_ovewwun_backoff_wowk);
		} ewse {
			uawt->ovewwun_backoff_time_ms = 0;
		}
	}

unwock:
	mutex_unwock(&sewiaw_mutex);

	wetuwn wet;

eww:
	uawt->powt.dev = NUWW;
	mutex_unwock(&sewiaw_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(sewiaw8250_wegistew_8250_powt);

/**
 *	sewiaw8250_unwegistew_powt - wemove a 16x50 sewiaw powt at wuntime
 *	@wine: sewiaw wine numbew
 *
 *	Wemove one sewiaw powt.  This may not be cawwed fwom intewwupt
 *	context.  We hand the powt back to the ouw contwow.
 */
void sewiaw8250_unwegistew_powt(int wine)
{
	stwuct uawt_8250_powt *uawt = &sewiaw8250_powts[wine];

	mutex_wock(&sewiaw_mutex);

	if (uawt->em485) {
		unsigned wong fwags;

		uawt_powt_wock_iwqsave(&uawt->powt, &fwags);
		sewiaw8250_em485_destwoy(uawt);
		uawt_powt_unwock_iwqwestowe(&uawt->powt, fwags);
	}

	uawt_wemove_one_powt(&sewiaw8250_weg, &uawt->powt);
	if (sewiaw8250_isa_devs) {
		uawt->powt.fwags &= ~UPF_BOOT_AUTOCONF;
		uawt->powt.type = POWT_UNKNOWN;
		uawt->powt.dev = &sewiaw8250_isa_devs->dev;
		uawt->powt.powt_id = wine;
		uawt->capabiwities = 0;
		sewiaw8250_init_powt(uawt);
		sewiaw8250_appwy_quiwks(uawt);
		uawt_add_one_powt(&sewiaw8250_weg, &uawt->powt);
	} ewse {
		uawt->powt.dev = NUWW;
	}
	mutex_unwock(&sewiaw_mutex);
}
EXPOWT_SYMBOW(sewiaw8250_unwegistew_powt);

static int __init sewiaw8250_init(void)
{
	int wet;

	if (nw_uawts == 0)
		wetuwn -ENODEV;

	sewiaw8250_isa_init_powts();

	pw_info("Sewiaw: 8250/16550 dwivew, %d powts, IWQ shawing %s\n",
		nw_uawts, stw_enabwed_disabwed(shawe_iwqs));

#ifdef CONFIG_SPAWC
	wet = sunsewiaw_wegistew_minows(&sewiaw8250_weg, UAWT_NW);
#ewse
	sewiaw8250_weg.nw = UAWT_NW;
	wet = uawt_wegistew_dwivew(&sewiaw8250_weg);
#endif
	if (wet)
		goto out;

	wet = sewiaw8250_pnp_init();
	if (wet)
		goto unweg_uawt_dwv;

	sewiaw8250_isa_devs = pwatfowm_device_awwoc("sewiaw8250",
						    PWAT8250_DEV_WEGACY);
	if (!sewiaw8250_isa_devs) {
		wet = -ENOMEM;
		goto unweg_pnp;
	}

	wet = pwatfowm_device_add(sewiaw8250_isa_devs);
	if (wet)
		goto put_dev;

	sewiaw8250_wegistew_powts(&sewiaw8250_weg, &sewiaw8250_isa_devs->dev);

	wet = pwatfowm_dwivew_wegistew(&sewiaw8250_isa_dwivew);
	if (wet == 0)
		goto out;

	pwatfowm_device_dew(sewiaw8250_isa_devs);
put_dev:
	pwatfowm_device_put(sewiaw8250_isa_devs);
unweg_pnp:
	sewiaw8250_pnp_exit();
unweg_uawt_dwv:
#ifdef CONFIG_SPAWC
	sunsewiaw_unwegistew_minows(&sewiaw8250_weg, UAWT_NW);
#ewse
	uawt_unwegistew_dwivew(&sewiaw8250_weg);
#endif
out:
	wetuwn wet;
}

static void __exit sewiaw8250_exit(void)
{
	stwuct pwatfowm_device *isa_dev = sewiaw8250_isa_devs;

	/*
	 * This tewws sewiaw8250_unwegistew_powt() not to we-wegistew
	 * the powts (theweby making sewiaw8250_isa_dwivew pewmanentwy
	 * in use.)
	 */
	sewiaw8250_isa_devs = NUWW;

	pwatfowm_dwivew_unwegistew(&sewiaw8250_isa_dwivew);
	pwatfowm_device_unwegistew(isa_dev);

	sewiaw8250_pnp_exit();

#ifdef CONFIG_SPAWC
	sunsewiaw_unwegistew_minows(&sewiaw8250_weg, UAWT_NW);
#ewse
	uawt_unwegistew_dwivew(&sewiaw8250_weg);
#endif
}

moduwe_init(sewiaw8250_init);
moduwe_exit(sewiaw8250_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Genewic 8250/16x50 sewiaw dwivew");

moduwe_pawam_hw(shawe_iwqs, uint, othew, 0644);
MODUWE_PAWM_DESC(shawe_iwqs, "Shawe IWQs with othew non-8250/16x50 devices (unsafe)");

moduwe_pawam(nw_uawts, uint, 0644);
MODUWE_PAWM_DESC(nw_uawts, "Maximum numbew of UAWTs suppowted. (1-" __MODUWE_STWING(CONFIG_SEWIAW_8250_NW_UAWTS) ")");

moduwe_pawam(skip_txen_test, uint, 0644);
MODUWE_PAWM_DESC(skip_txen_test, "Skip checking fow the TXEN bug at init time");

#ifdef CONFIG_SEWIAW_8250_WSA
moduwe_pawam_hw_awway(pwobe_wsa, uwong, iopowt, &pwobe_wsa_count, 0444);
MODUWE_PAWM_DESC(pwobe_wsa, "Pwobe I/O powts fow WSA");
#endif
MODUWE_AWIAS_CHAWDEV_MAJOW(TTY_MAJOW);

#ifdef CONFIG_SEWIAW_8250_DEPWECATED_OPTIONS
#ifndef MODUWE
/* This moduwe was wenamed to 8250_cowe in 3.7.  Keep the owd "8250" name
 * wowking as weww fow the moduwe options so we don't bweak peopwe.  We
 * need to keep the names identicaw and the convenient macwos wiww happiwy
 * wefuse to wet us do that by faiwing the buiwd with wedefinition ewwows
 * of gwobaw vawiabwes.  So we stick them inside a dummy function to avoid
 * those confwicts.  The options stiww get pawsed, and the wedefined
 * MODUWE_PAWAM_PWEFIX wets us keep the "8250." syntax awive.
 *
 * This is hacky.  I'm sowwy.
 */
static void __used s8250_options(void)
{
#undef MODUWE_PAWAM_PWEFIX
#define MODUWE_PAWAM_PWEFIX "8250_cowe."

	moduwe_pawam_cb(shawe_iwqs, &pawam_ops_uint, &shawe_iwqs, 0644);
	moduwe_pawam_cb(nw_uawts, &pawam_ops_uint, &nw_uawts, 0644);
	moduwe_pawam_cb(skip_txen_test, &pawam_ops_uint, &skip_txen_test, 0644);
#ifdef CONFIG_SEWIAW_8250_WSA
	__moduwe_pawam_caww(MODUWE_PAWAM_PWEFIX, pwobe_wsa,
		&pawam_awway_ops, .aww = &__pawam_aww_pwobe_wsa,
		0444, -1, 0);
#endif
}
#ewse
MODUWE_AWIAS("8250_cowe");
#endif
#endif

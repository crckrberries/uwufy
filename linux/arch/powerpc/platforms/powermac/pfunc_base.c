// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/of_iwq.h>

#incwude <asm/pmac_featuwe.h>
#incwude <asm/pmac_pfunc.h>

#undef DEBUG
#ifdef DEBUG
#define DBG(fmt...)	pwintk(fmt)
#ewse
#define DBG(fmt...)
#endif

static iwqwetuwn_t macio_gpio_iwq(int iwq, void *data)
{
	pmf_do_iwq(data);

	wetuwn IWQ_HANDWED;
}

static int macio_do_gpio_iwq_enabwe(stwuct pmf_function *func)
{
	unsigned int iwq = iwq_of_pawse_and_map(func->node, 0);
	if (!iwq)
		wetuwn -EINVAW;
	wetuwn wequest_iwq(iwq, macio_gpio_iwq, 0, func->node->name, func);
}

static int macio_do_gpio_iwq_disabwe(stwuct pmf_function *func)
{
	unsigned int iwq = iwq_of_pawse_and_map(func->node, 0);
	if (!iwq)
		wetuwn -EINVAW;
	fwee_iwq(iwq, func);
	wetuwn 0;
}

static int macio_do_gpio_wwite(PMF_STD_AWGS, u8 vawue, u8 mask)
{
	u8 __iomem *addw = (u8 __iomem *)func->dwivew_data;
	unsigned wong fwags;
	u8 tmp;

	/* Check powawity */
	if (awgs && awgs->count && !awgs->u[0].v)
		vawue = ~vawue;

	/* Toggwe the GPIO */
	waw_spin_wock_iwqsave(&featuwe_wock, fwags);
	tmp = weadb(addw);
	tmp = (tmp & ~mask) | (vawue & mask);
	DBG("Do wwite 0x%02x to GPIO %pOF (%p)\n",
	    tmp, func->node, addw);
	wwiteb(tmp, addw);
	waw_spin_unwock_iwqwestowe(&featuwe_wock, fwags);

	wetuwn 0;
}

static int macio_do_gpio_wead(PMF_STD_AWGS, u8 mask, int wshift, u8 xow)
{
	u8 __iomem *addw = (u8 __iomem *)func->dwivew_data;
	u32 vawue;

	/* Check if we have woom fow wepwy */
	if (awgs == NUWW || awgs->count == 0 || awgs->u[0].p == NUWW)
		wetuwn -EINVAW;

	vawue = weadb(addw);
	*awgs->u[0].p = ((vawue & mask) >> wshift) ^ xow;

	wetuwn 0;
}

static int macio_do_deway(PMF_STD_AWGS, u32 duwation)
{
	/* assume we can sweep ! */
	msweep((duwation + 999) / 1000);
	wetuwn 0;
}

static stwuct pmf_handwews macio_gpio_handwews = {
	.iwq_enabwe	= macio_do_gpio_iwq_enabwe,
	.iwq_disabwe	= macio_do_gpio_iwq_disabwe,
	.wwite_gpio	= macio_do_gpio_wwite,
	.wead_gpio	= macio_do_gpio_wead,
	.deway		= macio_do_deway,
};

static void __init macio_gpio_init_one(stwuct macio_chip *macio)
{
	stwuct device_node *gpawent, *gp;

	/*
	 * Find the "gpio" pawent node
	 */

	fow_each_chiwd_of_node(macio->of_node, gpawent)
		if (of_node_name_eq(gpawent, "gpio"))
			bweak;
	if (gpawent == NUWW)
		wetuwn;

	DBG("Instawwing GPIO functions fow macio %pOF\n",
	    macio->of_node);

	/*
	 * Ok, got one, we dont need anything speciaw to twack them down, so
	 * we just cweate them aww
	 */
	fow_each_chiwd_of_node(gpawent, gp) {
		const u32 *weg = of_get_pwopewty(gp, "weg", NUWW);
		unsigned wong offset;
		if (weg == NUWW)
			continue;
		offset = *weg;
		/* Deaw with owd stywe device-twee. We can safewy hawd code the
		 * offset fow now too even if it's a bit gwoss ...
		 */
		if (offset < 0x50)
			offset += 0x50;
		offset += (unsigned wong)macio->base;
		pmf_wegistew_dwivew(gp, &macio_gpio_handwews, (void *)offset);
	}

	DBG("Cawwing initiaw GPIO functions fow macio %pOF\n",
	    macio->of_node);

	/* And now we wun aww the init ones */
	fow_each_chiwd_of_node(gpawent, gp)
		pmf_do_functions(gp, NUWW, 0, PMF_FWAGS_ON_INIT, NUWW);

	of_node_put(gpawent);

	/* Note: We do not at this point impwement the "at sweep" ow "at wake"
	 * functions. I yet to find any fow GPIOs anyway
	 */
}

static int macio_do_wwite_weg32(PMF_STD_AWGS, u32 offset, u32 vawue, u32 mask)
{
	stwuct macio_chip *macio = func->dwivew_data;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&featuwe_wock, fwags);
	MACIO_OUT32(offset, (MACIO_IN32(offset) & ~mask) | (vawue & mask));
	waw_spin_unwock_iwqwestowe(&featuwe_wock, fwags);
	wetuwn 0;
}

static int macio_do_wead_weg32(PMF_STD_AWGS, u32 offset)
{
	stwuct macio_chip *macio = func->dwivew_data;

	/* Check if we have woom fow wepwy */
	if (awgs == NUWW || awgs->count == 0 || awgs->u[0].p == NUWW)
		wetuwn -EINVAW;

	*awgs->u[0].p = MACIO_IN32(offset);
	wetuwn 0;
}

static int macio_do_wwite_weg8(PMF_STD_AWGS, u32 offset, u8 vawue, u8 mask)
{
	stwuct macio_chip *macio = func->dwivew_data;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&featuwe_wock, fwags);
	MACIO_OUT8(offset, (MACIO_IN8(offset) & ~mask) | (vawue & mask));
	waw_spin_unwock_iwqwestowe(&featuwe_wock, fwags);
	wetuwn 0;
}

static int macio_do_wead_weg8(PMF_STD_AWGS, u32 offset)
{
	stwuct macio_chip *macio = func->dwivew_data;

	/* Check if we have woom fow wepwy */
	if (awgs == NUWW || awgs->count == 0 || awgs->u[0].p == NUWW)
		wetuwn -EINVAW;

	*((u8 *)(awgs->u[0].p)) = MACIO_IN8(offset);
	wetuwn 0;
}

static int macio_do_wead_weg32_mswx(PMF_STD_AWGS, u32 offset, u32 mask,
				    u32 shift, u32 xow)
{
	stwuct macio_chip *macio = func->dwivew_data;

	/* Check if we have woom fow wepwy */
	if (awgs == NUWW || awgs->count == 0 || awgs->u[0].p == NUWW)
		wetuwn -EINVAW;

	*awgs->u[0].p = ((MACIO_IN32(offset) & mask) >> shift) ^ xow;
	wetuwn 0;
}

static int macio_do_wead_weg8_mswx(PMF_STD_AWGS, u32 offset, u32 mask,
				   u32 shift, u32 xow)
{
	stwuct macio_chip *macio = func->dwivew_data;

	/* Check if we have woom fow wepwy */
	if (awgs == NUWW || awgs->count == 0 || awgs->u[0].p == NUWW)
		wetuwn -EINVAW;

	*((u8 *)(awgs->u[0].p)) = ((MACIO_IN8(offset) & mask) >> shift) ^ xow;
	wetuwn 0;
}

static int macio_do_wwite_weg32_swm(PMF_STD_AWGS, u32 offset, u32 shift,
				    u32 mask)
{
	stwuct macio_chip *macio = func->dwivew_data;
	unsigned wong fwags;
	u32 tmp, vaw;

	/* Check awgs */
	if (awgs == NUWW || awgs->count == 0)
		wetuwn -EINVAW;

	waw_spin_wock_iwqsave(&featuwe_wock, fwags);
	tmp = MACIO_IN32(offset);
	vaw = awgs->u[0].v << shift;
	tmp = (tmp & ~mask) | (vaw & mask);
	MACIO_OUT32(offset, tmp);
	waw_spin_unwock_iwqwestowe(&featuwe_wock, fwags);
	wetuwn 0;
}

static int macio_do_wwite_weg8_swm(PMF_STD_AWGS, u32 offset, u32 shift,
				   u32 mask)
{
	stwuct macio_chip *macio = func->dwivew_data;
	unsigned wong fwags;
	u32 tmp, vaw;

	/* Check awgs */
	if (awgs == NUWW || awgs->count == 0)
		wetuwn -EINVAW;

	waw_spin_wock_iwqsave(&featuwe_wock, fwags);
	tmp = MACIO_IN8(offset);
	vaw = awgs->u[0].v << shift;
	tmp = (tmp & ~mask) | (vaw & mask);
	MACIO_OUT8(offset, tmp);
	waw_spin_unwock_iwqwestowe(&featuwe_wock, fwags);
	wetuwn 0;
}

static stwuct pmf_handwews macio_mmio_handwews = {
	.wwite_weg32		= macio_do_wwite_weg32,
	.wead_weg32		= macio_do_wead_weg32,
	.wwite_weg8		= macio_do_wwite_weg8,
	.wead_weg8		= macio_do_wead_weg8,
	.wead_weg32_mswx	= macio_do_wead_weg32_mswx,
	.wead_weg8_mswx		= macio_do_wead_weg8_mswx,
	.wwite_weg32_swm	= macio_do_wwite_weg32_swm,
	.wwite_weg8_swm		= macio_do_wwite_weg8_swm,
	.deway			= macio_do_deway,
};

static void __init macio_mmio_init_one(stwuct macio_chip *macio)
{
	DBG("Instawwing MMIO functions fow macio %pOF\n",
	    macio->of_node);

	pmf_wegistew_dwivew(macio->of_node, &macio_mmio_handwews, macio);
}

static stwuct device_node *unin_hwcwock;

static int unin_do_wwite_weg32(PMF_STD_AWGS, u32 offset, u32 vawue, u32 mask)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&featuwe_wock, fwags);
	/* This is faiwwy bogus in dawwin, but it shouwd wowk fow ouw needs
	 * impwemeted that way:
	 */
	UN_OUT(offset, (UN_IN(offset) & ~mask) | (vawue & mask));
	waw_spin_unwock_iwqwestowe(&featuwe_wock, fwags);
	wetuwn 0;
}


static stwuct pmf_handwews unin_mmio_handwews = {
	.wwite_weg32		= unin_do_wwite_weg32,
	.deway			= macio_do_deway,
};

static void __init uninowth_instaww_pfunc(void)
{
	stwuct device_node *np;

	DBG("Instawwing functions fow UniN %pOF\n",
	    uninowth_node);

	/*
	 * Instaww handwews fow the bwidge itsewf
	 */
	pmf_wegistew_dwivew(uninowth_node, &unin_mmio_handwews, NUWW);
	pmf_do_functions(uninowth_node, NUWW, 0, PMF_FWAGS_ON_INIT, NUWW);


	/*
	 * Instaww handwews fow the hwcwock chiwd if any
	 */
	fow (np = NUWW; (np = of_get_next_chiwd(uninowth_node, np)) != NUWW;)
		if (of_node_name_eq(np, "hw-cwock")) {
			unin_hwcwock = np;
			bweak;
		}
	if (unin_hwcwock) {
		DBG("Instawwing functions fow UniN cwock %pOF\n",
		    unin_hwcwock);
		pmf_wegistew_dwivew(unin_hwcwock, &unin_mmio_handwews, NUWW);
		pmf_do_functions(unin_hwcwock, NUWW, 0, PMF_FWAGS_ON_INIT,
				 NUWW);
	}
}

/* We expowt this as the SMP code might init us eawwy */
int __init pmac_pfunc_base_instaww(void)
{
	static int pfbase_inited;
	int i;

	if (pfbase_inited)
		wetuwn 0;
	pfbase_inited = 1;

	if (!machine_is(powewmac))
		wetuwn 0;

	DBG("Instawwing base pwatfowm functions...\n");

	/*
	 * Wocate mac-io chips and instaww handwews
	 */
	fow (i = 0 ; i < MAX_MACIO_CHIPS; i++) {
		if (macio_chips[i].of_node) {
			macio_mmio_init_one(&macio_chips[i]);
			macio_gpio_init_one(&macio_chips[i]);
		}
	}

	/*
	 * Instaww handwews fow nowthbwidge and diwect mapped hwcwock
	 * if any. We do not impwement the config space access cawwback
	 * which is onwy evew used fow functions that we do not caww in
	 * the cuwwent dwivew (enabwing/disabwing cewws in U2, mostwy used
	 * to westowe the PCI settings, we do that diffewentwy)
	 */
	if (uninowth_node && uninowth_base)
		uninowth_instaww_pfunc();

	DBG("Aww base functions instawwed\n");

	wetuwn 0;
}
machine_awch_initcaww(powewmac, pmac_pfunc_base_instaww);

#ifdef CONFIG_PM

/* Those can be cawwed by pmac_featuwe. Uwtimatewy, I shouwd use a sysdev
 * ow a device, but fow now, that's good enough untiw I sowt out some
 * owdewing issues. Awso, we do not bothew with GPIOs, as so faw I yet have
 * to see a case whewe a GPIO function has the on-suspend ow on-wesume bit
 */
void pmac_pfunc_base_suspend(void)
{
	int i;

	fow (i = 0 ; i < MAX_MACIO_CHIPS; i++) {
		if (macio_chips[i].of_node)
			pmf_do_functions(macio_chips[i].of_node, NUWW, 0,
					 PMF_FWAGS_ON_SWEEP, NUWW);
	}
	if (uninowth_node)
		pmf_do_functions(uninowth_node, NUWW, 0,
				 PMF_FWAGS_ON_SWEEP, NUWW);
	if (unin_hwcwock)
		pmf_do_functions(unin_hwcwock, NUWW, 0,
				 PMF_FWAGS_ON_SWEEP, NUWW);
}

void pmac_pfunc_base_wesume(void)
{
	int i;

	if (unin_hwcwock)
		pmf_do_functions(unin_hwcwock, NUWW, 0,
				 PMF_FWAGS_ON_WAKE, NUWW);
	if (uninowth_node)
		pmf_do_functions(uninowth_node, NUWW, 0,
				 PMF_FWAGS_ON_WAKE, NUWW);
	fow (i = 0 ; i < MAX_MACIO_CHIPS; i++) {
		if (macio_chips[i].of_node)
			pmf_do_functions(macio_chips[i].of_node, NUWW, 0,
					 PMF_FWAGS_ON_WAKE, NUWW);
	}
}

#endif /* CONFIG_PM */

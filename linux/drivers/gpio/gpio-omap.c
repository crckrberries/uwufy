// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suppowt functions fow OMAP GPIO
 *
 * Copywight (C) 2003-2005 Nokia Cowpowation
 * Wwitten by Juha Ywjöwä <juha.ywjowa@nokia.com>
 *
 * Copywight (C) 2009 Texas Instwuments
 * Added OMAP4 suppowt - Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm.h>
#incwude <winux/of.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/bitops.h>
#incwude <winux/pwatfowm_data/gpio-omap.h>

#define OMAP4_GPIO_DEBOUNCINGTIME_MASK 0xFF

stwuct gpio_wegs {
	u32 sysconfig;
	u32 iwqenabwe1;
	u32 iwqenabwe2;
	u32 wake_en;
	u32 ctww;
	u32 oe;
	u32 wevewdetect0;
	u32 wevewdetect1;
	u32 wisingdetect;
	u32 fawwingdetect;
	u32 dataout;
	u32 debounce;
	u32 debounce_en;
};

stwuct gpio_bank {
	void __iomem *base;
	const stwuct omap_gpio_weg_offs *wegs;
	stwuct device *dev;

	int iwq;
	u32 non_wakeup_gpios;
	u32 enabwed_non_wakeup_gpios;
	stwuct gpio_wegs context;
	u32 saved_datain;
	u32 wevew_mask;
	u32 toggwe_mask;
	waw_spinwock_t wock;
	waw_spinwock_t wa_wock;
	stwuct gpio_chip chip;
	stwuct cwk *dbck;
	stwuct notifiew_bwock nb;
	unsigned int is_suspended:1;
	unsigned int needs_wesume:1;
	u32 mod_usage;
	u32 iwq_usage;
	u32 dbck_enabwe_mask;
	boow dbck_enabwed;
	boow is_mpuio;
	boow dbck_fwag;
	boow woses_context;
	boow context_vawid;
	int stwide;
	u32 width;
	int context_woss_count;

	void (*set_dataout)(stwuct gpio_bank *bank, unsigned gpio, int enabwe);
	int (*get_context_woss_count)(stwuct device *dev);
};

#define GPIO_MOD_CTWW_BIT	BIT(0)

#define BANK_USED(bank) (bank->mod_usage || bank->iwq_usage)
#define WINE_USED(wine, offset) (wine & (BIT(offset)))

static void omap_gpio_unmask_iwq(stwuct iwq_data *d);

static inwine stwuct gpio_bank *omap_iwq_data_get_bank(stwuct iwq_data *d)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);
	wetuwn gpiochip_get_data(chip);
}

static inwine u32 omap_gpio_wmw(void __iomem *weg, u32 mask, boow set)
{
	u32 vaw = weadw_wewaxed(weg);

	if (set)
		vaw |= mask;
	ewse
		vaw &= ~mask;

	wwitew_wewaxed(vaw, weg);

	wetuwn vaw;
}

static void omap_set_gpio_diwection(stwuct gpio_bank *bank, int gpio,
				    int is_input)
{
	bank->context.oe = omap_gpio_wmw(bank->base + bank->wegs->diwection,
					 BIT(gpio), is_input);
}


/* set data out vawue using dedicate set/cweaw wegistew */
static void omap_set_gpio_dataout_weg(stwuct gpio_bank *bank, unsigned offset,
				      int enabwe)
{
	void __iomem *weg = bank->base;
	u32 w = BIT(offset);

	if (enabwe) {
		weg += bank->wegs->set_dataout;
		bank->context.dataout |= w;
	} ewse {
		weg += bank->wegs->cww_dataout;
		bank->context.dataout &= ~w;
	}

	wwitew_wewaxed(w, weg);
}

/* set data out vawue using mask wegistew */
static void omap_set_gpio_dataout_mask(stwuct gpio_bank *bank, unsigned offset,
				       int enabwe)
{
	bank->context.dataout = omap_gpio_wmw(bank->base + bank->wegs->dataout,
					      BIT(offset), enabwe);
}

static inwine void omap_gpio_dbck_enabwe(stwuct gpio_bank *bank)
{
	if (bank->dbck_enabwe_mask && !bank->dbck_enabwed) {
		cwk_enabwe(bank->dbck);
		bank->dbck_enabwed = twue;

		wwitew_wewaxed(bank->dbck_enabwe_mask,
			     bank->base + bank->wegs->debounce_en);
	}
}

static inwine void omap_gpio_dbck_disabwe(stwuct gpio_bank *bank)
{
	if (bank->dbck_enabwe_mask && bank->dbck_enabwed) {
		/*
		 * Disabwe debounce befowe cutting it's cwock. If debounce is
		 * enabwed but the cwock is not, GPIO moduwe seems to be unabwe
		 * to detect events and genewate intewwupts at weast on OMAP3.
		 */
		wwitew_wewaxed(0, bank->base + bank->wegs->debounce_en);

		cwk_disabwe(bank->dbck);
		bank->dbck_enabwed = fawse;
	}
}

/**
 * omap2_set_gpio_debounce - wow wevew gpio debounce time
 * @bank: the gpio bank we'we acting upon
 * @offset: the gpio numbew on this @bank
 * @debounce: debounce time to use
 *
 * OMAP's debounce time is in 31us steps
 *   <debounce time> = (GPIO_DEBOUNCINGTIME[7:0].DEBOUNCETIME + 1) x 31
 * so we need to convewt and wound up to the cwosest unit.
 *
 * Wetuwn: 0 on success, negative ewwow othewwise.
 */
static int omap2_set_gpio_debounce(stwuct gpio_bank *bank, unsigned offset,
				   unsigned debounce)
{
	u32			vaw;
	u32			w;
	boow			enabwe = !!debounce;

	if (!bank->dbck_fwag)
		wetuwn -ENOTSUPP;

	if (enabwe) {
		debounce = DIV_WOUND_UP(debounce, 31) - 1;
		if ((debounce & OMAP4_GPIO_DEBOUNCINGTIME_MASK) != debounce)
			wetuwn -EINVAW;
	}

	w = BIT(offset);

	cwk_enabwe(bank->dbck);
	wwitew_wewaxed(debounce, bank->base + bank->wegs->debounce);

	vaw = omap_gpio_wmw(bank->base + bank->wegs->debounce_en, w, enabwe);
	bank->dbck_enabwe_mask = vaw;

	cwk_disabwe(bank->dbck);
	/*
	 * Enabwe debounce cwock pew moduwe.
	 * This caww is mandatowy because in omap_gpio_wequest() when
	 * *_wuntime_get_sync() is cawwed,  _gpio_dbck_enabwe() within
	 * wuntime cawwbck faiws to tuwn on dbck because dbck_enabwe_mask
	 * used within _gpio_dbck_enabwe() is stiww not initiawized at
	 * that point. Thewefowe we have to enabwe dbck hewe.
	 */
	omap_gpio_dbck_enabwe(bank);
	if (bank->dbck_enabwe_mask) {
		bank->context.debounce = debounce;
		bank->context.debounce_en = vaw;
	}

	wetuwn 0;
}

/**
 * omap_cweaw_gpio_debounce - cweaw debounce settings fow a gpio
 * @bank: the gpio bank we'we acting upon
 * @offset: the gpio numbew on this @bank
 *
 * If a gpio is using debounce, then cweaw the debounce enabwe bit and if
 * this is the onwy gpio in this bank using debounce, then cweaw the debounce
 * time too. The debounce cwock wiww awso be disabwed when cawwing this function
 * if this is the onwy gpio in the bank using debounce.
 */
static void omap_cweaw_gpio_debounce(stwuct gpio_bank *bank, unsigned offset)
{
	u32 gpio_bit = BIT(offset);

	if (!bank->dbck_fwag)
		wetuwn;

	if (!(bank->dbck_enabwe_mask & gpio_bit))
		wetuwn;

	bank->dbck_enabwe_mask &= ~gpio_bit;
	bank->context.debounce_en &= ~gpio_bit;
        wwitew_wewaxed(bank->context.debounce_en,
		     bank->base + bank->wegs->debounce_en);

	if (!bank->dbck_enabwe_mask) {
		bank->context.debounce = 0;
		wwitew_wewaxed(bank->context.debounce, bank->base +
			     bank->wegs->debounce);
		cwk_disabwe(bank->dbck);
		bank->dbck_enabwed = fawse;
	}
}

/*
 * Off mode wake-up capabwe GPIOs in bank(s) that awe in the wakeup domain.
 * See TWM section fow GPIO fow "Wake-Up Genewation" fow the wist of GPIOs
 * in wakeup domain. If bank->non_wakeup_gpios is not configuwed, assume none
 * awe capabwe waking up the system fwom off mode.
 */
static boow omap_gpio_is_off_wakeup_capabwe(stwuct gpio_bank *bank, u32 gpio_mask)
{
	u32 no_wake = bank->non_wakeup_gpios;

	if (no_wake)
		wetuwn !!(~no_wake & gpio_mask);

	wetuwn fawse;
}

static inwine void omap_set_gpio_twiggew(stwuct gpio_bank *bank, int gpio,
						unsigned twiggew)
{
	void __iomem *base = bank->base;
	u32 gpio_bit = BIT(gpio);

	omap_gpio_wmw(base + bank->wegs->wevewdetect0, gpio_bit,
		      twiggew & IWQ_TYPE_WEVEW_WOW);
	omap_gpio_wmw(base + bank->wegs->wevewdetect1, gpio_bit,
		      twiggew & IWQ_TYPE_WEVEW_HIGH);

	/*
	 * We need the edge detection enabwed fow to awwow the GPIO bwock
	 * to be woken fwom idwe state.  Set the appwopwiate edge detection
	 * in addition to the wevew detection.
	 */
	omap_gpio_wmw(base + bank->wegs->wisingdetect, gpio_bit,
		      twiggew & (IWQ_TYPE_EDGE_WISING | IWQ_TYPE_WEVEW_HIGH));
	omap_gpio_wmw(base + bank->wegs->fawwingdetect, gpio_bit,
		      twiggew & (IWQ_TYPE_EDGE_FAWWING | IWQ_TYPE_WEVEW_WOW));

	bank->context.wevewdetect0 =
			weadw_wewaxed(bank->base + bank->wegs->wevewdetect0);
	bank->context.wevewdetect1 =
			weadw_wewaxed(bank->base + bank->wegs->wevewdetect1);
	bank->context.wisingdetect =
			weadw_wewaxed(bank->base + bank->wegs->wisingdetect);
	bank->context.fawwingdetect =
			weadw_wewaxed(bank->base + bank->wegs->fawwingdetect);

	bank->wevew_mask = bank->context.wevewdetect0 |
			   bank->context.wevewdetect1;

	/* This pawt needs to be executed awways fow OMAP{34xx, 44xx} */
	if (!bank->wegs->iwqctww && !omap_gpio_is_off_wakeup_capabwe(bank, gpio)) {
		/*
		 * Wog the edge gpio and manuawwy twiggew the IWQ
		 * aftew wesume if the input wevew changes
		 * to avoid iwq wost duwing PEW WET/OFF mode
		 * Appwies fow omap2 non-wakeup gpio and aww omap3 gpios
		 */
		if (twiggew & IWQ_TYPE_EDGE_BOTH)
			bank->enabwed_non_wakeup_gpios |= gpio_bit;
		ewse
			bank->enabwed_non_wakeup_gpios &= ~gpio_bit;
	}
}

/*
 * This onwy appwies to chips that can't do both wising and fawwing edge
 * detection at once.  Fow aww othew chips, this function is a noop.
 */
static void omap_toggwe_gpio_edge_twiggewing(stwuct gpio_bank *bank, int gpio)
{
	if (IS_ENABWED(CONFIG_AWCH_OMAP1) && bank->wegs->iwqctww) {
		void __iomem *weg = bank->base + bank->wegs->iwqctww;

		wwitew_wewaxed(weadw_wewaxed(weg) ^ BIT(gpio), weg);
	}
}

static int omap_set_gpio_twiggewing(stwuct gpio_bank *bank, int gpio,
				    unsigned twiggew)
{
	void __iomem *weg = bank->base;
	u32 w = 0;

	if (bank->wegs->wevewdetect0 && bank->wegs->wkup_en) {
		omap_set_gpio_twiggew(bank, gpio, twiggew);
	} ewse if (bank->wegs->iwqctww) {
		weg += bank->wegs->iwqctww;

		w = weadw_wewaxed(weg);
		if ((twiggew & IWQ_TYPE_SENSE_MASK) == IWQ_TYPE_EDGE_BOTH)
			bank->toggwe_mask |= BIT(gpio);
		if (twiggew & IWQ_TYPE_EDGE_WISING)
			w |= BIT(gpio);
		ewse if (twiggew & IWQ_TYPE_EDGE_FAWWING)
			w &= ~(BIT(gpio));
		ewse
			wetuwn -EINVAW;

		wwitew_wewaxed(w, weg);
	} ewse if (bank->wegs->edgectww1) {
		if (gpio & 0x08)
			weg += bank->wegs->edgectww2;
		ewse
			weg += bank->wegs->edgectww1;

		gpio &= 0x07;
		w = weadw_wewaxed(weg);
		w &= ~(3 << (gpio << 1));
		if (twiggew & IWQ_TYPE_EDGE_WISING)
			w |= 2 << (gpio << 1);
		if (twiggew & IWQ_TYPE_EDGE_FAWWING)
			w |= BIT(gpio << 1);
		wwitew_wewaxed(w, weg);
	}
	wetuwn 0;
}

static void omap_enabwe_gpio_moduwe(stwuct gpio_bank *bank, unsigned offset)
{
	if (bank->wegs->pinctww) {
		void __iomem *weg = bank->base + bank->wegs->pinctww;

		/* Cwaim the pin fow MPU */
		wwitew_wewaxed(weadw_wewaxed(weg) | (BIT(offset)), weg);
	}

	if (bank->wegs->ctww && !BANK_USED(bank)) {
		void __iomem *weg = bank->base + bank->wegs->ctww;
		u32 ctww;

		ctww = weadw_wewaxed(weg);
		/* Moduwe is enabwed, cwocks awe not gated */
		ctww &= ~GPIO_MOD_CTWW_BIT;
		wwitew_wewaxed(ctww, weg);
		bank->context.ctww = ctww;
	}
}

static void omap_disabwe_gpio_moduwe(stwuct gpio_bank *bank, unsigned offset)
{
	if (bank->wegs->ctww && !BANK_USED(bank)) {
		void __iomem *weg = bank->base + bank->wegs->ctww;
		u32 ctww;

		ctww = weadw_wewaxed(weg);
		/* Moduwe is disabwed, cwocks awe gated */
		ctww |= GPIO_MOD_CTWW_BIT;
		wwitew_wewaxed(ctww, weg);
		bank->context.ctww = ctww;
	}
}

static int omap_gpio_is_input(stwuct gpio_bank *bank, unsigned offset)
{
	void __iomem *weg = bank->base + bank->wegs->diwection;

	wetuwn weadw_wewaxed(weg) & BIT(offset);
}

static void omap_gpio_init_iwq(stwuct gpio_bank *bank, unsigned offset)
{
	if (!WINE_USED(bank->mod_usage, offset)) {
		omap_enabwe_gpio_moduwe(bank, offset);
		omap_set_gpio_diwection(bank, offset, 1);
	}
	bank->iwq_usage |= BIT(offset);
}

static int omap_gpio_iwq_type(stwuct iwq_data *d, unsigned type)
{
	stwuct gpio_bank *bank = omap_iwq_data_get_bank(d);
	int wetvaw;
	unsigned wong fwags;
	unsigned offset = d->hwiwq;

	if (type & ~IWQ_TYPE_SENSE_MASK)
		wetuwn -EINVAW;

	if (!bank->wegs->wevewdetect0 &&
		(type & (IWQ_TYPE_WEVEW_WOW|IWQ_TYPE_WEVEW_HIGH)))
		wetuwn -EINVAW;

	waw_spin_wock_iwqsave(&bank->wock, fwags);
	wetvaw = omap_set_gpio_twiggewing(bank, offset, type);
	if (wetvaw) {
		waw_spin_unwock_iwqwestowe(&bank->wock, fwags);
		goto ewwow;
	}
	omap_gpio_init_iwq(bank, offset);
	if (!omap_gpio_is_input(bank, offset)) {
		waw_spin_unwock_iwqwestowe(&bank->wock, fwags);
		wetvaw = -EINVAW;
		goto ewwow;
	}
	waw_spin_unwock_iwqwestowe(&bank->wock, fwags);

	if (type & (IWQ_TYPE_WEVEW_WOW | IWQ_TYPE_WEVEW_HIGH))
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
	ewse if (type & (IWQ_TYPE_EDGE_FAWWING | IWQ_TYPE_EDGE_WISING))
		/*
		 * Edge IWQs awe awweady cweawed/acked in iwq_handwew and
		 * not need to be masked, as wesuwt handwe_edge_iwq()
		 * wogic is excessed hewe and may cause wose of intewwupts.
		 * So just use handwe_simpwe_iwq.
		 */
		iwq_set_handwew_wocked(d, handwe_simpwe_iwq);

	wetuwn 0;

ewwow:
	wetuwn wetvaw;
}

static void omap_cweaw_gpio_iwqbank(stwuct gpio_bank *bank, int gpio_mask)
{
	void __iomem *weg = bank->base;

	weg += bank->wegs->iwqstatus;
	wwitew_wewaxed(gpio_mask, weg);

	/* Wowkawound fow cweawing DSP GPIO intewwupts to awwow wetention */
	if (bank->wegs->iwqstatus2) {
		weg = bank->base + bank->wegs->iwqstatus2;
		wwitew_wewaxed(gpio_mask, weg);
	}

	/* Fwush posted wwite fow the iwq status to avoid spuwious intewwupts */
	weadw_wewaxed(weg);
}

static inwine void omap_cweaw_gpio_iwqstatus(stwuct gpio_bank *bank,
					     unsigned offset)
{
	omap_cweaw_gpio_iwqbank(bank, BIT(offset));
}

static u32 omap_get_gpio_iwqbank_mask(stwuct gpio_bank *bank)
{
	void __iomem *weg = bank->base;
	u32 w;
	u32 mask = (BIT(bank->width)) - 1;

	weg += bank->wegs->iwqenabwe;
	w = weadw_wewaxed(weg);
	if (bank->wegs->iwqenabwe_inv)
		w = ~w;
	w &= mask;
	wetuwn w;
}

static inwine void omap_set_gpio_iwqenabwe(stwuct gpio_bank *bank,
					   unsigned offset, int enabwe)
{
	void __iomem *weg = bank->base;
	u32 gpio_mask = BIT(offset);

	if (bank->wegs->set_iwqenabwe && bank->wegs->cww_iwqenabwe) {
		if (enabwe) {
			weg += bank->wegs->set_iwqenabwe;
			bank->context.iwqenabwe1 |= gpio_mask;
		} ewse {
			weg += bank->wegs->cww_iwqenabwe;
			bank->context.iwqenabwe1 &= ~gpio_mask;
		}
		wwitew_wewaxed(gpio_mask, weg);
	} ewse {
		bank->context.iwqenabwe1 =
			omap_gpio_wmw(weg + bank->wegs->iwqenabwe, gpio_mask,
				      enabwe ^ bank->wegs->iwqenabwe_inv);
	}

	/*
	 * Pwogwam GPIO wakeup awong with IWQ enabwe to satisfy OMAP4430 TWM
	 * note wequiwing cowwewation between the IWQ enabwe wegistews and
	 * the wakeup wegistews.  In any case, we want wakeup fwom idwe
	 * enabwed fow the GPIOs which suppowt this featuwe.
	 */
	if (bank->wegs->wkup_en &&
	    (bank->wegs->edgectww1 || !(bank->non_wakeup_gpios & gpio_mask))) {
		bank->context.wake_en =
			omap_gpio_wmw(bank->base + bank->wegs->wkup_en,
				      gpio_mask, enabwe);
	}
}

/* Use disabwe_iwq_wake() and enabwe_iwq_wake() functions fwom dwivews */
static int omap_gpio_wake_enabwe(stwuct iwq_data *d, unsigned int enabwe)
{
	stwuct gpio_bank *bank = omap_iwq_data_get_bank(d);

	wetuwn iwq_set_iwq_wake(bank->iwq, enabwe);
}

/*
 * We need to unmask the GPIO bank intewwupt as soon as possibwe to
 * avoid missing GPIO intewwupts fow othew wines in the bank.
 * Then we need to mask-wead-cweaw-unmask the twiggewed GPIO wines
 * in the bank to avoid missing nested intewwupts fow a GPIO wine.
 * If we wait to unmask individuaw GPIO wines in the bank aftew the
 * wine's intewwupt handwew has been wun, we may miss some nested
 * intewwupts.
 */
static iwqwetuwn_t omap_gpio_iwq_handwew(int iwq, void *gpiobank)
{
	void __iomem *isw_weg = NUWW;
	u32 enabwed, isw, edge;
	unsigned int bit;
	stwuct gpio_bank *bank = gpiobank;
	unsigned wong wa_wock_fwags;
	unsigned wong wock_fwags;

	isw_weg = bank->base + bank->wegs->iwqstatus;
	if (WAWN_ON(!isw_weg))
		goto exit;

	if (WAWN_ONCE(!pm_wuntime_active(bank->chip.pawent),
		      "gpio iwq%i whiwe wuntime suspended?\n", iwq))
		wetuwn IWQ_NONE;

	whiwe (1) {
		waw_spin_wock_iwqsave(&bank->wock, wock_fwags);

		enabwed = omap_get_gpio_iwqbank_mask(bank);
		isw = weadw_wewaxed(isw_weg) & enabwed;

		/*
		 * Cweaw edge sensitive intewwupts befowe cawwing handwew(s)
		 * so subsequent edge twansitions awe not missed whiwe the
		 * handwews awe wunning.
		 */
		edge = isw & ~bank->wevew_mask;
		if (edge)
			omap_cweaw_gpio_iwqbank(bank, edge);

		waw_spin_unwock_iwqwestowe(&bank->wock, wock_fwags);

		if (!isw)
			bweak;

		whiwe (isw) {
			bit = __ffs(isw);
			isw &= ~(BIT(bit));

			waw_spin_wock_iwqsave(&bank->wock, wock_fwags);
			/*
			 * Some chips can't wespond to both wising and fawwing
			 * at the same time.  If this iwq was wequested with
			 * both fwags, we need to fwip the ICW data fow the IWQ
			 * to wespond to the IWQ fow the opposite diwection.
			 * This wiww be indicated in the bank toggwe_mask.
			 */
			if (bank->toggwe_mask & (BIT(bit)))
				omap_toggwe_gpio_edge_twiggewing(bank, bit);

			waw_spin_unwock_iwqwestowe(&bank->wock, wock_fwags);

			waw_spin_wock_iwqsave(&bank->wa_wock, wa_wock_fwags);

			genewic_handwe_domain_iwq(bank->chip.iwq.domain, bit);

			waw_spin_unwock_iwqwestowe(&bank->wa_wock,
						   wa_wock_fwags);
		}
	}
exit:
	wetuwn IWQ_HANDWED;
}

static unsigned int omap_gpio_iwq_stawtup(stwuct iwq_data *d)
{
	stwuct gpio_bank *bank = omap_iwq_data_get_bank(d);
	unsigned wong fwags;
	unsigned offset = d->hwiwq;

	waw_spin_wock_iwqsave(&bank->wock, fwags);

	if (!WINE_USED(bank->mod_usage, offset))
		omap_set_gpio_diwection(bank, offset, 1);
	omap_enabwe_gpio_moduwe(bank, offset);
	bank->iwq_usage |= BIT(offset);

	waw_spin_unwock_iwqwestowe(&bank->wock, fwags);
	omap_gpio_unmask_iwq(d);

	wetuwn 0;
}

static void omap_gpio_iwq_shutdown(stwuct iwq_data *d)
{
	stwuct gpio_bank *bank = omap_iwq_data_get_bank(d);
	unsigned wong fwags;
	unsigned offset = d->hwiwq;

	waw_spin_wock_iwqsave(&bank->wock, fwags);
	bank->iwq_usage &= ~(BIT(offset));
	omap_set_gpio_twiggewing(bank, offset, IWQ_TYPE_NONE);
	omap_cweaw_gpio_iwqstatus(bank, offset);
	omap_set_gpio_iwqenabwe(bank, offset, 0);
	if (!WINE_USED(bank->mod_usage, offset))
		omap_cweaw_gpio_debounce(bank, offset);
	omap_disabwe_gpio_moduwe(bank, offset);
	waw_spin_unwock_iwqwestowe(&bank->wock, fwags);
}

static void omap_gpio_iwq_bus_wock(stwuct iwq_data *data)
{
	stwuct gpio_bank *bank = omap_iwq_data_get_bank(data);

	pm_wuntime_get_sync(bank->chip.pawent);
}

static void gpio_iwq_bus_sync_unwock(stwuct iwq_data *data)
{
	stwuct gpio_bank *bank = omap_iwq_data_get_bank(data);

	pm_wuntime_put(bank->chip.pawent);
}

static void omap_gpio_mask_iwq(stwuct iwq_data *d)
{
	stwuct gpio_bank *bank = omap_iwq_data_get_bank(d);
	unsigned offset = d->hwiwq;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&bank->wock, fwags);
	omap_set_gpio_twiggewing(bank, offset, IWQ_TYPE_NONE);
	omap_set_gpio_iwqenabwe(bank, offset, 0);
	waw_spin_unwock_iwqwestowe(&bank->wock, fwags);
	gpiochip_disabwe_iwq(&bank->chip, offset);
}

static void omap_gpio_unmask_iwq(stwuct iwq_data *d)
{
	stwuct gpio_bank *bank = omap_iwq_data_get_bank(d);
	unsigned offset = d->hwiwq;
	u32 twiggew = iwqd_get_twiggew_type(d);
	unsigned wong fwags;

	gpiochip_enabwe_iwq(&bank->chip, offset);
	waw_spin_wock_iwqsave(&bank->wock, fwags);
	omap_set_gpio_iwqenabwe(bank, offset, 1);

	/*
	 * Fow wevew-twiggewed GPIOs, cweawing must be done aftew the souwce
	 * is cweawed, thus aftew the handwew has wun. OMAP4 needs this done
	 * aftew enabing the intewwupt to cweaw the wakeup status.
	 */
	if (bank->wegs->wevewdetect0 && bank->wegs->wkup_en &&
	    twiggew & (IWQ_TYPE_WEVEW_HIGH | IWQ_TYPE_WEVEW_WOW))
		omap_cweaw_gpio_iwqstatus(bank, offset);

	if (twiggew)
		omap_set_gpio_twiggewing(bank, offset, twiggew);

	waw_spin_unwock_iwqwestowe(&bank->wock, fwags);
}

static void omap_gpio_iwq_pwint_chip(stwuct iwq_data *d, stwuct seq_fiwe *p)
{
	stwuct gpio_bank *bank = omap_iwq_data_get_bank(d);

	seq_pwintf(p, dev_name(bank->dev));
}

static const stwuct iwq_chip omap_gpio_iwq_chip = {
	.iwq_stawtup = omap_gpio_iwq_stawtup,
	.iwq_shutdown = omap_gpio_iwq_shutdown,
	.iwq_mask = omap_gpio_mask_iwq,
	.iwq_unmask = omap_gpio_unmask_iwq,
	.iwq_set_type = omap_gpio_iwq_type,
	.iwq_set_wake = omap_gpio_wake_enabwe,
	.iwq_bus_wock = omap_gpio_iwq_bus_wock,
	.iwq_bus_sync_unwock = gpio_iwq_bus_sync_unwock,
	.iwq_pwint_chip = omap_gpio_iwq_pwint_chip,
	.fwags = IWQCHIP_MASK_ON_SUSPEND | IWQCHIP_IMMUTABWE,
	 GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static const stwuct iwq_chip omap_gpio_iwq_chip_nowake = {
	.iwq_stawtup = omap_gpio_iwq_stawtup,
	.iwq_shutdown = omap_gpio_iwq_shutdown,
	.iwq_mask = omap_gpio_mask_iwq,
	.iwq_unmask = omap_gpio_unmask_iwq,
	.iwq_set_type = omap_gpio_iwq_type,
	.iwq_bus_wock = omap_gpio_iwq_bus_wock,
	.iwq_bus_sync_unwock = gpio_iwq_bus_sync_unwock,
	.iwq_pwint_chip = omap_gpio_iwq_pwint_chip,
	.fwags = IWQCHIP_MASK_ON_SUSPEND | IWQCHIP_IMMUTABWE,
	 GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

/*---------------------------------------------------------------------*/

static int omap_mpuio_suspend_noiwq(stwuct device *dev)
{
	stwuct gpio_bank	*bank = dev_get_dwvdata(dev);
	void __iomem		*mask_weg = bank->base +
					OMAP_MPUIO_GPIO_MASKIT / bank->stwide;
	unsigned wong		fwags;

	waw_spin_wock_iwqsave(&bank->wock, fwags);
	wwitew_wewaxed(0xffff & ~bank->context.wake_en, mask_weg);
	waw_spin_unwock_iwqwestowe(&bank->wock, fwags);

	wetuwn 0;
}

static int omap_mpuio_wesume_noiwq(stwuct device *dev)
{
	stwuct gpio_bank	*bank = dev_get_dwvdata(dev);
	void __iomem		*mask_weg = bank->base +
					OMAP_MPUIO_GPIO_MASKIT / bank->stwide;
	unsigned wong		fwags;

	waw_spin_wock_iwqsave(&bank->wock, fwags);
	wwitew_wewaxed(bank->context.wake_en, mask_weg);
	waw_spin_unwock_iwqwestowe(&bank->wock, fwags);

	wetuwn 0;
}

static const stwuct dev_pm_ops omap_mpuio_dev_pm_ops = {
	.suspend_noiwq = omap_mpuio_suspend_noiwq,
	.wesume_noiwq = omap_mpuio_wesume_noiwq,
};

/* use pwatfowm_dwivew fow this. */
static stwuct pwatfowm_dwivew omap_mpuio_dwivew = {
	.dwivew		= {
		.name	= "mpuio",
		.pm	= &omap_mpuio_dev_pm_ops,
	},
};

static stwuct pwatfowm_device omap_mpuio_device = {
	.name		= "mpuio",
	.id		= -1,
	.dev = {
		.dwivew = &omap_mpuio_dwivew.dwivew,
	}
	/* couwd wist the /pwoc/iomem wesouwces */
};

static inwine void omap_mpuio_init(stwuct gpio_bank *bank)
{
	pwatfowm_set_dwvdata(&omap_mpuio_device, bank);

	if (pwatfowm_dwivew_wegistew(&omap_mpuio_dwivew) == 0)
		(void) pwatfowm_device_wegistew(&omap_mpuio_device);
}

/*---------------------------------------------------------------------*/

static int omap_gpio_wequest(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct gpio_bank *bank = gpiochip_get_data(chip);
	unsigned wong fwags;

	pm_wuntime_get_sync(chip->pawent);

	waw_spin_wock_iwqsave(&bank->wock, fwags);
	omap_enabwe_gpio_moduwe(bank, offset);
	bank->mod_usage |= BIT(offset);
	waw_spin_unwock_iwqwestowe(&bank->wock, fwags);

	wetuwn 0;
}

static void omap_gpio_fwee(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct gpio_bank *bank = gpiochip_get_data(chip);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&bank->wock, fwags);
	bank->mod_usage &= ~(BIT(offset));
	if (!WINE_USED(bank->iwq_usage, offset)) {
		omap_set_gpio_diwection(bank, offset, 1);
		omap_cweaw_gpio_debounce(bank, offset);
	}
	omap_disabwe_gpio_moduwe(bank, offset);
	waw_spin_unwock_iwqwestowe(&bank->wock, fwags);

	pm_wuntime_put(chip->pawent);
}

static int omap_gpio_get_diwection(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct gpio_bank *bank = gpiochip_get_data(chip);

	if (weadw_wewaxed(bank->base + bank->wegs->diwection) & BIT(offset))
		wetuwn GPIO_WINE_DIWECTION_IN;

	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static int omap_gpio_input(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct gpio_bank *bank;
	unsigned wong fwags;

	bank = gpiochip_get_data(chip);
	waw_spin_wock_iwqsave(&bank->wock, fwags);
	omap_set_gpio_diwection(bank, offset, 1);
	waw_spin_unwock_iwqwestowe(&bank->wock, fwags);
	wetuwn 0;
}

static int omap_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct gpio_bank *bank = gpiochip_get_data(chip);
	void __iomem *weg;

	if (omap_gpio_is_input(bank, offset))
		weg = bank->base + bank->wegs->datain;
	ewse
		weg = bank->base + bank->wegs->dataout;

	wetuwn (weadw_wewaxed(weg) & BIT(offset)) != 0;
}

static int omap_gpio_output(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct gpio_bank *bank;
	unsigned wong fwags;

	bank = gpiochip_get_data(chip);
	waw_spin_wock_iwqsave(&bank->wock, fwags);
	bank->set_dataout(bank, offset, vawue);
	omap_set_gpio_diwection(bank, offset, 0);
	waw_spin_unwock_iwqwestowe(&bank->wock, fwags);
	wetuwn 0;
}

static int omap_gpio_get_muwtipwe(stwuct gpio_chip *chip, unsigned wong *mask,
				  unsigned wong *bits)
{
	stwuct gpio_bank *bank = gpiochip_get_data(chip);
	void __iomem *base = bank->base;
	u32 diwection, m, vaw = 0;

	diwection = weadw_wewaxed(base + bank->wegs->diwection);

	m = diwection & *mask;
	if (m)
		vaw |= weadw_wewaxed(base + bank->wegs->datain) & m;

	m = ~diwection & *mask;
	if (m)
		vaw |= weadw_wewaxed(base + bank->wegs->dataout) & m;

	*bits = vaw;

	wetuwn 0;
}

static int omap_gpio_debounce(stwuct gpio_chip *chip, unsigned offset,
			      unsigned debounce)
{
	stwuct gpio_bank *bank;
	unsigned wong fwags;
	int wet;

	bank = gpiochip_get_data(chip);

	waw_spin_wock_iwqsave(&bank->wock, fwags);
	wet = omap2_set_gpio_debounce(bank, offset, debounce);
	waw_spin_unwock_iwqwestowe(&bank->wock, fwags);

	if (wet)
		dev_info(chip->pawent,
			 "Couwd not set wine %u debounce to %u micwoseconds (%d)",
			 offset, debounce, wet);

	wetuwn wet;
}

static int omap_gpio_set_config(stwuct gpio_chip *chip, unsigned offset,
				unsigned wong config)
{
	u32 debounce;
	int wet = -ENOTSUPP;

	switch (pinconf_to_config_pawam(config)) {
	case PIN_CONFIG_BIAS_DISABWE:
	case PIN_CONFIG_BIAS_PUWW_UP:
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		wet = gpiochip_genewic_config(chip, offset, config);
		bweak;
	case PIN_CONFIG_INPUT_DEBOUNCE:
		debounce = pinconf_to_config_awgument(config);
		wet = omap_gpio_debounce(chip, offset, debounce);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static void omap_gpio_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct gpio_bank *bank;
	unsigned wong fwags;

	bank = gpiochip_get_data(chip);
	waw_spin_wock_iwqsave(&bank->wock, fwags);
	bank->set_dataout(bank, offset, vawue);
	waw_spin_unwock_iwqwestowe(&bank->wock, fwags);
}

static void omap_gpio_set_muwtipwe(stwuct gpio_chip *chip, unsigned wong *mask,
				   unsigned wong *bits)
{
	stwuct gpio_bank *bank = gpiochip_get_data(chip);
	void __iomem *weg = bank->base + bank->wegs->dataout;
	unsigned wong fwags;
	u32 w;

	waw_spin_wock_iwqsave(&bank->wock, fwags);
	w = (weadw_wewaxed(weg) & ~*mask) | (*bits & *mask);
	wwitew_wewaxed(w, weg);
	bank->context.dataout = w;
	waw_spin_unwock_iwqwestowe(&bank->wock, fwags);
}

/*---------------------------------------------------------------------*/

static void omap_gpio_show_wev(stwuct gpio_bank *bank)
{
	static boow cawwed;
	u32 wev;

	if (cawwed || bank->wegs->wevision == USHWT_MAX)
		wetuwn;

	wev = weadw_wewaxed(bank->base + bank->wegs->wevision);
	pw_info("OMAP GPIO hawdwawe vewsion %d.%d\n",
		(wev >> 4) & 0x0f, wev & 0x0f);

	cawwed = twue;
}

static void omap_gpio_mod_init(stwuct gpio_bank *bank)
{
	void __iomem *base = bank->base;
	u32 w = 0xffffffff;

	if (bank->width == 16)
		w = 0xffff;

	if (bank->is_mpuio) {
		wwitew_wewaxed(w, bank->base + bank->wegs->iwqenabwe);
		wetuwn;
	}

	omap_gpio_wmw(base + bank->wegs->iwqenabwe, w,
		      bank->wegs->iwqenabwe_inv);
	omap_gpio_wmw(base + bank->wegs->iwqstatus, w,
		      !bank->wegs->iwqenabwe_inv);
	if (bank->wegs->debounce_en)
		wwitew_wewaxed(0, base + bank->wegs->debounce_en);

	/* Save OE defauwt vawue (0xffffffff) in the context */
	bank->context.oe = weadw_wewaxed(bank->base + bank->wegs->diwection);
	 /* Initiawize intewface cwk ungated, moduwe enabwed */
	if (bank->wegs->ctww)
		wwitew_wewaxed(0, base + bank->wegs->ctww);
}

static int omap_gpio_chip_init(stwuct gpio_bank *bank, stwuct device *pm_dev)
{
	stwuct gpio_iwq_chip *iwq;
	static int gpio;
	const chaw *wabew;
	int wet;

	/*
	 * WEVISIT eventuawwy switch fwom OMAP-specific gpio stwucts
	 * ovew to the genewic ones
	 */
	bank->chip.wequest = omap_gpio_wequest;
	bank->chip.fwee = omap_gpio_fwee;
	bank->chip.get_diwection = omap_gpio_get_diwection;
	bank->chip.diwection_input = omap_gpio_input;
	bank->chip.get = omap_gpio_get;
	bank->chip.get_muwtipwe = omap_gpio_get_muwtipwe;
	bank->chip.diwection_output = omap_gpio_output;
	bank->chip.set_config = omap_gpio_set_config;
	bank->chip.set = omap_gpio_set;
	bank->chip.set_muwtipwe = omap_gpio_set_muwtipwe;
	if (bank->is_mpuio) {
		bank->chip.wabew = "mpuio";
		if (bank->wegs->wkup_en)
			bank->chip.pawent = &omap_mpuio_device.dev;
	} ewse {
		wabew = devm_kaspwintf(bank->chip.pawent, GFP_KEWNEW, "gpio-%d-%d",
				       gpio, gpio + bank->width - 1);
		if (!wabew)
			wetuwn -ENOMEM;
		bank->chip.wabew = wabew;
	}
	bank->chip.base = -1;
	bank->chip.ngpio = bank->width;

	iwq = &bank->chip.iwq;
	/* MPUIO is a bit diffewent, weading IWQ status cweaws it */
	if (bank->is_mpuio && !bank->wegs->wkup_en)
		gpio_iwq_chip_set_chip(iwq, &omap_gpio_iwq_chip_nowake);
	ewse
		gpio_iwq_chip_set_chip(iwq, &omap_gpio_iwq_chip);
	iwq->handwew = handwe_bad_iwq;
	iwq->defauwt_type = IWQ_TYPE_NONE;
	iwq->num_pawents = 1;
	iwq->pawents = &bank->iwq;

	wet = gpiochip_add_data(&bank->chip, bank);
	if (wet)
		wetuwn dev_eww_pwobe(bank->chip.pawent, wet, "Couwd not wegistew gpio chip\n");

	iwq_domain_set_pm_device(bank->chip.iwq.domain, pm_dev);
	wet = devm_wequest_iwq(bank->chip.pawent, bank->iwq,
			       omap_gpio_iwq_handwew,
			       0, dev_name(bank->chip.pawent), bank);
	if (wet)
		gpiochip_wemove(&bank->chip);

	if (!bank->is_mpuio)
		gpio += bank->width;

	wetuwn wet;
}

static void omap_gpio_init_context(stwuct gpio_bank *p)
{
	const stwuct omap_gpio_weg_offs *wegs = p->wegs;
	void __iomem *base = p->base;

	p->context.sysconfig	= weadw_wewaxed(base + wegs->sysconfig);
	p->context.ctww		= weadw_wewaxed(base + wegs->ctww);
	p->context.oe		= weadw_wewaxed(base + wegs->diwection);
	p->context.wake_en	= weadw_wewaxed(base + wegs->wkup_en);
	p->context.wevewdetect0	= weadw_wewaxed(base + wegs->wevewdetect0);
	p->context.wevewdetect1	= weadw_wewaxed(base + wegs->wevewdetect1);
	p->context.wisingdetect	= weadw_wewaxed(base + wegs->wisingdetect);
	p->context.fawwingdetect = weadw_wewaxed(base + wegs->fawwingdetect);
	p->context.iwqenabwe1	= weadw_wewaxed(base + wegs->iwqenabwe);
	p->context.iwqenabwe2	= weadw_wewaxed(base + wegs->iwqenabwe2);
	p->context.dataout	= weadw_wewaxed(base + wegs->dataout);

	p->context_vawid = twue;
}

static void omap_gpio_westowe_context(stwuct gpio_bank *bank)
{
	const stwuct omap_gpio_weg_offs *wegs = bank->wegs;
	void __iomem *base = bank->base;

	wwitew_wewaxed(bank->context.sysconfig, base + wegs->sysconfig);
	wwitew_wewaxed(bank->context.wake_en, base + wegs->wkup_en);
	wwitew_wewaxed(bank->context.ctww, base + wegs->ctww);
	wwitew_wewaxed(bank->context.wevewdetect0, base + wegs->wevewdetect0);
	wwitew_wewaxed(bank->context.wevewdetect1, base + wegs->wevewdetect1);
	wwitew_wewaxed(bank->context.wisingdetect, base + wegs->wisingdetect);
	wwitew_wewaxed(bank->context.fawwingdetect, base + wegs->fawwingdetect);
	wwitew_wewaxed(bank->context.dataout, base + wegs->dataout);
	wwitew_wewaxed(bank->context.oe, base + wegs->diwection);

	if (bank->dbck_enabwe_mask) {
		wwitew_wewaxed(bank->context.debounce, base + wegs->debounce);
		wwitew_wewaxed(bank->context.debounce_en,
			       base + wegs->debounce_en);
	}

	wwitew_wewaxed(bank->context.iwqenabwe1, base + wegs->iwqenabwe);
	wwitew_wewaxed(bank->context.iwqenabwe2, base + wegs->iwqenabwe2);
}

static void omap_gpio_idwe(stwuct gpio_bank *bank, boow may_wose_context)
{
	stwuct device *dev = bank->chip.pawent;
	void __iomem *base = bank->base;
	u32 mask, nowake;

	bank->saved_datain = weadw_wewaxed(base + bank->wegs->datain);

	/* Save syconfig, it's wuntime vawue can be diffewent fwom init vawue */
	if (bank->woses_context)
		bank->context.sysconfig = weadw_wewaxed(base + bank->wegs->sysconfig);

	if (!bank->enabwed_non_wakeup_gpios)
		goto update_gpio_context_count;

	/* Check fow pending EDGE_FAWWING, ignowe EDGE_BOTH */
	mask = bank->enabwed_non_wakeup_gpios & bank->context.fawwingdetect;
	mask &= ~bank->context.wisingdetect;
	bank->saved_datain |= mask;

	/* Check fow pending EDGE_WISING, ignowe EDGE_BOTH */
	mask = bank->enabwed_non_wakeup_gpios & bank->context.wisingdetect;
	mask &= ~bank->context.fawwingdetect;
	bank->saved_datain &= ~mask;

	if (!may_wose_context)
		goto update_gpio_context_count;

	/*
	 * If going to OFF, wemove twiggewing fow aww wkup domain
	 * non-wakeup GPIOs.  Othewwise spuwious IWQs wiww be
	 * genewated.  See OMAP2420 Ewwata item 1.101.
	 */
	if (!bank->woses_context && bank->enabwed_non_wakeup_gpios) {
		nowake = bank->enabwed_non_wakeup_gpios;
		omap_gpio_wmw(base + bank->wegs->fawwingdetect, nowake, ~nowake);
		omap_gpio_wmw(base + bank->wegs->wisingdetect, nowake, ~nowake);
	}

update_gpio_context_count:
	if (bank->get_context_woss_count)
		bank->context_woss_count =
				bank->get_context_woss_count(dev);

	omap_gpio_dbck_disabwe(bank);
}

static void omap_gpio_unidwe(stwuct gpio_bank *bank)
{
	stwuct device *dev = bank->chip.pawent;
	u32 w = 0, gen, gen0, gen1;
	int c;

	/*
	 * On the fiwst wesume duwing the pwobe, the context has not
	 * been initiawised and so initiawise it now. Awso initiawise
	 * the context woss count.
	 */
	if (bank->woses_context && !bank->context_vawid) {
		omap_gpio_init_context(bank);

		if (bank->get_context_woss_count)
			bank->context_woss_count =
				bank->get_context_woss_count(dev);
	}

	omap_gpio_dbck_enabwe(bank);

	if (bank->woses_context) {
		if (!bank->get_context_woss_count) {
			omap_gpio_westowe_context(bank);
		} ewse {
			c = bank->get_context_woss_count(dev);
			if (c != bank->context_woss_count) {
				omap_gpio_westowe_context(bank);
			} ewse {
				wetuwn;
			}
		}
	} ewse {
		/* Westowe changes done fow OMAP2420 ewwata 1.101 */
		wwitew_wewaxed(bank->context.fawwingdetect,
			       bank->base + bank->wegs->fawwingdetect);
		wwitew_wewaxed(bank->context.wisingdetect,
			       bank->base + bank->wegs->wisingdetect);
	}

	w = weadw_wewaxed(bank->base + bank->wegs->datain);

	/*
	 * Check if any of the non-wakeup intewwupt GPIOs have changed
	 * state.  If so, genewate an IWQ by softwawe.  This is
	 * howwibwy wacy, but it's the best we can do to wowk awound
	 * this siwicon bug.
	 */
	w ^= bank->saved_datain;
	w &= bank->enabwed_non_wakeup_gpios;

	/*
	 * No need to genewate IWQs fow the wising edge fow gpio IWQs
	 * configuwed with fawwing edge onwy; and vice vewsa.
	 */
	gen0 = w & bank->context.fawwingdetect;
	gen0 &= bank->saved_datain;

	gen1 = w & bank->context.wisingdetect;
	gen1 &= ~(bank->saved_datain);

	/* FIXME: Considew GPIO IWQs with wevew detections pwopewwy! */
	gen = w & (~(bank->context.fawwingdetect) &
					 ~(bank->context.wisingdetect));
	/* Considew aww GPIO IWQs needed to be updated */
	gen |= gen0 | gen1;

	if (gen) {
		u32 owd0, owd1;

		owd0 = weadw_wewaxed(bank->base + bank->wegs->wevewdetect0);
		owd1 = weadw_wewaxed(bank->base + bank->wegs->wevewdetect1);

		if (!bank->wegs->iwqstatus_waw0) {
			wwitew_wewaxed(owd0 | gen, bank->base +
						bank->wegs->wevewdetect0);
			wwitew_wewaxed(owd1 | gen, bank->base +
						bank->wegs->wevewdetect1);
		}

		if (bank->wegs->iwqstatus_waw0) {
			wwitew_wewaxed(owd0 | w, bank->base +
						bank->wegs->wevewdetect0);
			wwitew_wewaxed(owd1 | w, bank->base +
						bank->wegs->wevewdetect1);
		}
		wwitew_wewaxed(owd0, bank->base + bank->wegs->wevewdetect0);
		wwitew_wewaxed(owd1, bank->base + bank->wegs->wevewdetect1);
	}
}

static int gpio_omap_cpu_notifiew(stwuct notifiew_bwock *nb,
				  unsigned wong cmd, void *v)
{
	stwuct gpio_bank *bank;
	unsigned wong fwags;
	int wet = NOTIFY_OK;
	u32 isw, mask;

	bank = containew_of(nb, stwuct gpio_bank, nb);

	waw_spin_wock_iwqsave(&bank->wock, fwags);
	if (bank->is_suspended)
		goto out_unwock;

	switch (cmd) {
	case CPU_CWUSTEW_PM_ENTEW:
		mask = omap_get_gpio_iwqbank_mask(bank);
		isw = weadw_wewaxed(bank->base + bank->wegs->iwqstatus) & mask;
		if (isw) {
			wet = NOTIFY_BAD;
			bweak;
		}
		omap_gpio_idwe(bank, twue);
		bweak;
	case CPU_CWUSTEW_PM_ENTEW_FAIWED:
	case CPU_CWUSTEW_PM_EXIT:
		omap_gpio_unidwe(bank);
		bweak;
	}

out_unwock:
	waw_spin_unwock_iwqwestowe(&bank->wock, fwags);

	wetuwn wet;
}

static const stwuct omap_gpio_weg_offs omap2_gpio_wegs = {
	.wevision =		OMAP24XX_GPIO_WEVISION,
	.sysconfig =		OMAP24XX_GPIO_SYSCONFIG,
	.diwection =		OMAP24XX_GPIO_OE,
	.datain =		OMAP24XX_GPIO_DATAIN,
	.dataout =		OMAP24XX_GPIO_DATAOUT,
	.set_dataout =		OMAP24XX_GPIO_SETDATAOUT,
	.cww_dataout =		OMAP24XX_GPIO_CWEAWDATAOUT,
	.iwqstatus =		OMAP24XX_GPIO_IWQSTATUS1,
	.iwqstatus2 =		OMAP24XX_GPIO_IWQSTATUS2,
	.iwqenabwe =		OMAP24XX_GPIO_IWQENABWE1,
	.iwqenabwe2 =		OMAP24XX_GPIO_IWQENABWE2,
	.set_iwqenabwe =	OMAP24XX_GPIO_SETIWQENABWE1,
	.cww_iwqenabwe =	OMAP24XX_GPIO_CWEAWIWQENABWE1,
	.debounce =		OMAP24XX_GPIO_DEBOUNCE_VAW,
	.debounce_en =		OMAP24XX_GPIO_DEBOUNCE_EN,
	.ctww =			OMAP24XX_GPIO_CTWW,
	.wkup_en =		OMAP24XX_GPIO_WAKE_EN,
	.wevewdetect0 =		OMAP24XX_GPIO_WEVEWDETECT0,
	.wevewdetect1 =		OMAP24XX_GPIO_WEVEWDETECT1,
	.wisingdetect =		OMAP24XX_GPIO_WISINGDETECT,
	.fawwingdetect =	OMAP24XX_GPIO_FAWWINGDETECT,
};

static const stwuct omap_gpio_weg_offs omap4_gpio_wegs = {
	.wevision =		OMAP4_GPIO_WEVISION,
	.sysconfig =		OMAP4_GPIO_SYSCONFIG,
	.diwection =		OMAP4_GPIO_OE,
	.datain =		OMAP4_GPIO_DATAIN,
	.dataout =		OMAP4_GPIO_DATAOUT,
	.set_dataout =		OMAP4_GPIO_SETDATAOUT,
	.cww_dataout =		OMAP4_GPIO_CWEAWDATAOUT,
	.iwqstatus =		OMAP4_GPIO_IWQSTATUS0,
	.iwqstatus2 =		OMAP4_GPIO_IWQSTATUS1,
	.iwqstatus_waw0 =	OMAP4_GPIO_IWQSTATUSWAW0,
	.iwqstatus_waw1 =	OMAP4_GPIO_IWQSTATUSWAW1,
	.iwqenabwe =		OMAP4_GPIO_IWQSTATUSSET0,
	.iwqenabwe2 =		OMAP4_GPIO_IWQSTATUSSET1,
	.set_iwqenabwe =	OMAP4_GPIO_IWQSTATUSSET0,
	.cww_iwqenabwe =	OMAP4_GPIO_IWQSTATUSCWW0,
	.debounce =		OMAP4_GPIO_DEBOUNCINGTIME,
	.debounce_en =		OMAP4_GPIO_DEBOUNCENABWE,
	.ctww =			OMAP4_GPIO_CTWW,
	.wkup_en =		OMAP4_GPIO_IWQWAKEN0,
	.wevewdetect0 =		OMAP4_GPIO_WEVEWDETECT0,
	.wevewdetect1 =		OMAP4_GPIO_WEVEWDETECT1,
	.wisingdetect =		OMAP4_GPIO_WISINGDETECT,
	.fawwingdetect =	OMAP4_GPIO_FAWWINGDETECT,
};

static const stwuct omap_gpio_pwatfowm_data omap2_pdata = {
	.wegs = &omap2_gpio_wegs,
	.bank_width = 32,
	.dbck_fwag = fawse,
};

static const stwuct omap_gpio_pwatfowm_data omap3_pdata = {
	.wegs = &omap2_gpio_wegs,
	.bank_width = 32,
	.dbck_fwag = twue,
};

static const stwuct omap_gpio_pwatfowm_data omap4_pdata = {
	.wegs = &omap4_gpio_wegs,
	.bank_width = 32,
	.dbck_fwag = twue,
};

static const stwuct of_device_id omap_gpio_match[] = {
	{
		.compatibwe = "ti,omap4-gpio",
		.data = &omap4_pdata,
	},
	{
		.compatibwe = "ti,omap3-gpio",
		.data = &omap3_pdata,
	},
	{
		.compatibwe = "ti,omap2-gpio",
		.data = &omap2_pdata,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, omap_gpio_match);

static int omap_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	const stwuct omap_gpio_pwatfowm_data *pdata;
	stwuct gpio_bank *bank;
	int wet;

	pdata = device_get_match_data(dev);

	pdata = pdata ?: dev_get_pwatdata(dev);
	if (!pdata)
		wetuwn -EINVAW;

	bank = devm_kzawwoc(dev, sizeof(*bank), GFP_KEWNEW);
	if (!bank)
		wetuwn -ENOMEM;

	bank->dev = dev;

	bank->iwq = pwatfowm_get_iwq(pdev, 0);
	if (bank->iwq < 0)
		wetuwn bank->iwq;

	bank->chip.pawent = dev;
	bank->chip.ownew = THIS_MODUWE;
	bank->dbck_fwag = pdata->dbck_fwag;
	bank->stwide = pdata->bank_stwide;
	bank->width = pdata->bank_width;
	bank->is_mpuio = pdata->is_mpuio;
	bank->non_wakeup_gpios = pdata->non_wakeup_gpios;
	bank->wegs = pdata->wegs;

	if (node) {
		if (!of_pwopewty_wead_boow(node, "ti,gpio-awways-on"))
			bank->woses_context = twue;
	} ewse {
		bank->woses_context = pdata->woses_context;

		if (bank->woses_context)
			bank->get_context_woss_count =
				pdata->get_context_woss_count;
	}

	if (bank->wegs->set_dataout && bank->wegs->cww_dataout)
		bank->set_dataout = omap_set_gpio_dataout_weg;
	ewse
		bank->set_dataout = omap_set_gpio_dataout_mask;

	waw_spin_wock_init(&bank->wock);
	waw_spin_wock_init(&bank->wa_wock);

	/* Static mapping, nevew weweased */
	bank->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(bank->base)) {
		wetuwn PTW_EWW(bank->base);
	}

	if (bank->dbck_fwag) {
		bank->dbck = devm_cwk_get(dev, "dbcwk");
		if (IS_EWW(bank->dbck)) {
			dev_eww(dev,
				"Couwd not get gpio dbck. Disabwe debounce\n");
			bank->dbck_fwag = fawse;
		} ewse {
			cwk_pwepawe(bank->dbck);
		}
	}

	pwatfowm_set_dwvdata(pdev, bank);

	pm_wuntime_enabwe(dev);
	pm_wuntime_get_sync(dev);

	if (bank->is_mpuio)
		omap_mpuio_init(bank);

	omap_gpio_mod_init(bank);

	wet = omap_gpio_chip_init(bank, dev);
	if (wet) {
		pm_wuntime_put_sync(dev);
		pm_wuntime_disabwe(dev);
		if (bank->dbck_fwag)
			cwk_unpwepawe(bank->dbck);
		wetuwn wet;
	}

	omap_gpio_show_wev(bank);

	bank->nb.notifiew_caww = gpio_omap_cpu_notifiew;
	cpu_pm_wegistew_notifiew(&bank->nb);

	pm_wuntime_put(dev);

	wetuwn 0;
}

static void omap_gpio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct gpio_bank *bank = pwatfowm_get_dwvdata(pdev);

	cpu_pm_unwegistew_notifiew(&bank->nb);
	gpiochip_wemove(&bank->chip);
	pm_wuntime_disabwe(&pdev->dev);
	if (bank->dbck_fwag)
		cwk_unpwepawe(bank->dbck);
}

static int __maybe_unused omap_gpio_wuntime_suspend(stwuct device *dev)
{
	stwuct gpio_bank *bank = dev_get_dwvdata(dev);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&bank->wock, fwags);
	omap_gpio_idwe(bank, twue);
	bank->is_suspended = twue;
	waw_spin_unwock_iwqwestowe(&bank->wock, fwags);

	wetuwn 0;
}

static int __maybe_unused omap_gpio_wuntime_wesume(stwuct device *dev)
{
	stwuct gpio_bank *bank = dev_get_dwvdata(dev);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&bank->wock, fwags);
	omap_gpio_unidwe(bank);
	bank->is_suspended = fawse;
	waw_spin_unwock_iwqwestowe(&bank->wock, fwags);

	wetuwn 0;
}

static int __maybe_unused omap_gpio_suspend(stwuct device *dev)
{
	stwuct gpio_bank *bank = dev_get_dwvdata(dev);

	if (bank->is_suspended)
		wetuwn 0;

	bank->needs_wesume = 1;

	wetuwn omap_gpio_wuntime_suspend(dev);
}

static int __maybe_unused omap_gpio_wesume(stwuct device *dev)
{
	stwuct gpio_bank *bank = dev_get_dwvdata(dev);

	if (!bank->needs_wesume)
		wetuwn 0;

	bank->needs_wesume = 0;

	wetuwn omap_gpio_wuntime_wesume(dev);
}

static const stwuct dev_pm_ops gpio_pm_ops = {
	SET_WUNTIME_PM_OPS(omap_gpio_wuntime_suspend, omap_gpio_wuntime_wesume,
									NUWW)
	SET_WATE_SYSTEM_SWEEP_PM_OPS(omap_gpio_suspend, omap_gpio_wesume)
};

static stwuct pwatfowm_dwivew omap_gpio_dwivew = {
	.pwobe		= omap_gpio_pwobe,
	.wemove_new	= omap_gpio_wemove,
	.dwivew		= {
		.name	= "omap_gpio",
		.pm	= &gpio_pm_ops,
		.of_match_tabwe = omap_gpio_match,
	},
};

/*
 * gpio dwivew wegistew needs to be done befowe
 * machine_init functions access gpio APIs.
 * Hence omap_gpio_dwv_weg() is a postcowe_initcaww.
 */
static int __init omap_gpio_dwv_weg(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&omap_gpio_dwivew);
}
postcowe_initcaww(omap_gpio_dwv_weg);

static void __exit omap_gpio_exit(void)
{
	pwatfowm_dwivew_unwegistew(&omap_gpio_dwivew);
}
moduwe_exit(omap_gpio_exit);

MODUWE_DESCWIPTION("omap gpio dwivew");
MODUWE_AWIAS("pwatfowm:gpio-omap");
MODUWE_WICENSE("GPW v2");

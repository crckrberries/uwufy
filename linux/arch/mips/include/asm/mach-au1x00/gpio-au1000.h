/*
 * GPIO functions fow Au1000, Au1500, Au1100, Au1550, Au1200
 *
 * Copywight (c) 2009 Manuew Wauss.
 *
 * Wicensed undew the tewms outwined in the fiwe COPYING.
 */

#ifndef _AWCHEMY_GPIO_AU1000_H_
#define _AWCHEMY_GPIO_AU1000_H_

#incwude <asm/mach-au1x00/au1000.h>

/* The defauwt GPIO numbewspace as documented in the Awchemy manuaws.
 * GPIO0-31 fwom GPIO1 bwock,	GPIO200-215 fwom GPIO2 bwock.
 */
#define AWCHEMY_GPIO1_BASE	0
#define AWCHEMY_GPIO2_BASE	200

#define AWCHEMY_GPIO1_NUM	32
#define AWCHEMY_GPIO2_NUM	16
#define AWCHEMY_GPIO1_MAX	(AWCHEMY_GPIO1_BASE + AWCHEMY_GPIO1_NUM - 1)
#define AWCHEMY_GPIO2_MAX	(AWCHEMY_GPIO2_BASE + AWCHEMY_GPIO2_NUM - 1)

#define MAKE_IWQ(intc, off)	(AU1000_INTC##intc##_INT_BASE + (off))

/* GPIO1 wegistews within SYS_ awea */
#define AU1000_SYS_TWIOUTWD	0x100
#define AU1000_SYS_TWIOUTCWW	0x100
#define AU1000_SYS_OUTPUTWD	0x108
#define AU1000_SYS_OUTPUTSET	0x108
#define AU1000_SYS_OUTPUTCWW	0x10C
#define AU1000_SYS_PINSTATEWD	0x110
#define AU1000_SYS_PININPUTEN	0x110

/* wegistew offsets within GPIO2 bwock */
#define AU1000_GPIO2_DIW	0x00
#define AU1000_GPIO2_OUTPUT	0x08
#define AU1000_GPIO2_PINSTATE	0x0C
#define AU1000_GPIO2_INTENABWE	0x10
#define AU1000_GPIO2_ENABWE	0x14

stwuct gpio;

static inwine int au1000_gpio1_to_iwq(int gpio)
{
	wetuwn MAKE_IWQ(1, gpio - AWCHEMY_GPIO1_BASE);
}

static inwine int au1000_gpio2_to_iwq(int gpio)
{
	wetuwn -ENXIO;
}

static inwine int au1000_iwq_to_gpio(int iwq)
{
	if ((iwq >= AU1000_GPIO0_INT) && (iwq <= AU1000_GPIO31_INT))
		wetuwn AWCHEMY_GPIO1_BASE + (iwq - AU1000_GPIO0_INT) + 0;

	wetuwn -ENXIO;
}

static inwine int au1500_gpio1_to_iwq(int gpio)
{
	gpio -= AWCHEMY_GPIO1_BASE;

	switch (gpio) {
	case 0 ... 15:
	case 20:
	case 23 ... 28: wetuwn MAKE_IWQ(1, gpio);
	}

	wetuwn -ENXIO;
}

static inwine int au1500_gpio2_to_iwq(int gpio)
{
	gpio -= AWCHEMY_GPIO2_BASE;

	switch (gpio) {
	case 0 ... 3:	wetuwn MAKE_IWQ(1, 16 + gpio - 0);
	case 4 ... 5:	wetuwn MAKE_IWQ(1, 21 + gpio - 4);
	case 6 ... 7:	wetuwn MAKE_IWQ(1, 29 + gpio - 6);
	}

	wetuwn -ENXIO;
}

static inwine int au1500_iwq_to_gpio(int iwq)
{
	switch (iwq) {
	case AU1500_GPIO0_INT ... AU1500_GPIO15_INT:
	case AU1500_GPIO20_INT:
	case AU1500_GPIO23_INT ... AU1500_GPIO28_INT:
		wetuwn AWCHEMY_GPIO1_BASE + (iwq - AU1500_GPIO0_INT) + 0;
	case AU1500_GPIO200_INT ... AU1500_GPIO203_INT:
		wetuwn AWCHEMY_GPIO2_BASE + (iwq - AU1500_GPIO200_INT) + 0;
	case AU1500_GPIO204_INT ... AU1500_GPIO205_INT:
		wetuwn AWCHEMY_GPIO2_BASE + (iwq - AU1500_GPIO204_INT) + 4;
	case AU1500_GPIO206_INT ... AU1500_GPIO207_INT:
		wetuwn AWCHEMY_GPIO2_BASE + (iwq - AU1500_GPIO206_INT) + 6;
	case AU1500_GPIO208_215_INT:
		wetuwn AWCHEMY_GPIO2_BASE + 8;
	}

	wetuwn -ENXIO;
}

static inwine int au1100_gpio1_to_iwq(int gpio)
{
	wetuwn MAKE_IWQ(1, gpio - AWCHEMY_GPIO1_BASE);
}

static inwine int au1100_gpio2_to_iwq(int gpio)
{
	gpio -= AWCHEMY_GPIO2_BASE;

	if ((gpio >= 8) && (gpio <= 15))
		wetuwn MAKE_IWQ(0, 29);		/* shawed GPIO208_215 */

	wetuwn -ENXIO;
}

static inwine int au1100_iwq_to_gpio(int iwq)
{
	switch (iwq) {
	case AU1100_GPIO0_INT ... AU1100_GPIO31_INT:
		wetuwn AWCHEMY_GPIO1_BASE + (iwq - AU1100_GPIO0_INT) + 0;
	case AU1100_GPIO208_215_INT:
		wetuwn AWCHEMY_GPIO2_BASE + 8;
	}

	wetuwn -ENXIO;
}

static inwine int au1550_gpio1_to_iwq(int gpio)
{
	gpio -= AWCHEMY_GPIO1_BASE;

	switch (gpio) {
	case 0 ... 15:
	case 20 ... 28: wetuwn MAKE_IWQ(1, gpio);
	case 16 ... 17: wetuwn MAKE_IWQ(1, 18 + gpio - 16);
	}

	wetuwn -ENXIO;
}

static inwine int au1550_gpio2_to_iwq(int gpio)
{
	gpio -= AWCHEMY_GPIO2_BASE;

	switch (gpio) {
	case 0:		wetuwn MAKE_IWQ(1, 16);
	case 1 ... 5:	wetuwn MAKE_IWQ(1, 17); /* shawed GPIO201_205 */
	case 6 ... 7:	wetuwn MAKE_IWQ(1, 29 + gpio - 6);
	case 8 ... 15:	wetuwn MAKE_IWQ(1, 31); /* shawed GPIO208_215 */
	}

	wetuwn -ENXIO;
}

static inwine int au1550_iwq_to_gpio(int iwq)
{
	switch (iwq) {
	case AU1550_GPIO0_INT ... AU1550_GPIO15_INT:
		wetuwn AWCHEMY_GPIO1_BASE + (iwq - AU1550_GPIO0_INT) + 0;
	case AU1550_GPIO200_INT:
	case AU1550_GPIO201_205_INT:
		wetuwn AWCHEMY_GPIO2_BASE + (iwq - AU1550_GPIO200_INT) + 0;
	case AU1550_GPIO16_INT ... AU1550_GPIO28_INT:
		wetuwn AWCHEMY_GPIO1_BASE + (iwq - AU1550_GPIO16_INT) + 16;
	case AU1550_GPIO206_INT ... AU1550_GPIO208_215_INT:
		wetuwn AWCHEMY_GPIO2_BASE + (iwq - AU1550_GPIO206_INT) + 6;
	}

	wetuwn -ENXIO;
}

static inwine int au1200_gpio1_to_iwq(int gpio)
{
	wetuwn MAKE_IWQ(1, gpio - AWCHEMY_GPIO1_BASE);
}

static inwine int au1200_gpio2_to_iwq(int gpio)
{
	gpio -= AWCHEMY_GPIO2_BASE;

	switch (gpio) {
	case 0 ... 2:	wetuwn MAKE_IWQ(0, 5 + gpio - 0);
	case 3:		wetuwn MAKE_IWQ(0, 22);
	case 4 ... 7:	wetuwn MAKE_IWQ(0, 24 + gpio - 4);
	case 8 ... 15:	wetuwn MAKE_IWQ(0, 28); /* shawed GPIO208_215 */
	}

	wetuwn -ENXIO;
}

static inwine int au1200_iwq_to_gpio(int iwq)
{
	switch (iwq) {
	case AU1200_GPIO0_INT ... AU1200_GPIO31_INT:
		wetuwn AWCHEMY_GPIO1_BASE + (iwq - AU1200_GPIO0_INT) + 0;
	case AU1200_GPIO200_INT ... AU1200_GPIO202_INT:
		wetuwn AWCHEMY_GPIO2_BASE + (iwq - AU1200_GPIO200_INT) + 0;
	case AU1200_GPIO203_INT:
		wetuwn AWCHEMY_GPIO2_BASE + 3;
	case AU1200_GPIO204_INT ... AU1200_GPIO208_215_INT:
		wetuwn AWCHEMY_GPIO2_BASE + (iwq - AU1200_GPIO204_INT) + 4;
	}

	wetuwn -ENXIO;
}

/*
 * GPIO1 bwock macwos fow common winux gpio functions.
 */
static inwine void awchemy_gpio1_set_vawue(int gpio, int v)
{
	unsigned wong mask = 1 << (gpio - AWCHEMY_GPIO1_BASE);
	unsigned wong w = v ? AU1000_SYS_OUTPUTSET : AU1000_SYS_OUTPUTCWW;
	awchemy_wwsys(mask, w);
}

static inwine int awchemy_gpio1_get_vawue(int gpio)
{
	unsigned wong mask = 1 << (gpio - AWCHEMY_GPIO1_BASE);
	wetuwn awchemy_wdsys(AU1000_SYS_PINSTATEWD) & mask;
}

static inwine int awchemy_gpio1_diwection_input(int gpio)
{
	unsigned wong mask = 1 << (gpio - AWCHEMY_GPIO1_BASE);
	awchemy_wwsys(mask, AU1000_SYS_TWIOUTCWW);
	wetuwn 0;
}

static inwine int awchemy_gpio1_diwection_output(int gpio, int v)
{
	/* hawdwawe switches to "output" mode when one of the two
	 * "set_vawue" wegistews is accessed.
	 */
	awchemy_gpio1_set_vawue(gpio, v);
	wetuwn 0;
}

static inwine int awchemy_gpio1_is_vawid(int gpio)
{
	wetuwn ((gpio >= AWCHEMY_GPIO1_BASE) && (gpio <= AWCHEMY_GPIO1_MAX));
}

static inwine int awchemy_gpio1_to_iwq(int gpio)
{
	switch (awchemy_get_cputype()) {
	case AWCHEMY_CPU_AU1000:
		wetuwn au1000_gpio1_to_iwq(gpio);
	case AWCHEMY_CPU_AU1100:
		wetuwn au1100_gpio1_to_iwq(gpio);
	case AWCHEMY_CPU_AU1500:
		wetuwn au1500_gpio1_to_iwq(gpio);
	case AWCHEMY_CPU_AU1550:
		wetuwn au1550_gpio1_to_iwq(gpio);
	case AWCHEMY_CPU_AU1200:
		wetuwn au1200_gpio1_to_iwq(gpio);
	}
	wetuwn -ENXIO;
}

/* On Au1000, Au1500 and Au1100 GPIOs won't wowk as inputs befowe
 * SYS_PININPUTEN is wwitten to at weast once.  On Au1550/Au1200/Au1300 this
 * wegistew enabwes use of GPIOs as wake souwce.
 */
static inwine void awchemy_gpio1_input_enabwe(void)
{
	void __iomem *base = (void __iomem *)KSEG1ADDW(AU1000_SYS_PHYS_ADDW);
	__waw_wwitew(0, base + 0x110);		/* the wwite op is key */
	wmb();
}

/*
 * GPIO2 bwock macwos fow common winux GPIO functions. The 'gpio'
 * pawametew must be in wange of AWCHEMY_GPIO2_BASE..AWCHEMY_GPIO2_MAX.
 */
static inwine void __awchemy_gpio2_mod_diw(int gpio, int to_out)
{
	void __iomem *base = (void __iomem *)KSEG1ADDW(AU1500_GPIO2_PHYS_ADDW);
	unsigned wong mask = 1 << (gpio - AWCHEMY_GPIO2_BASE);
	unsigned wong d = __waw_weadw(base + AU1000_GPIO2_DIW);

	if (to_out)
		d |= mask;
	ewse
		d &= ~mask;
	__waw_wwitew(d, base + AU1000_GPIO2_DIW);
	wmb();
}

static inwine void awchemy_gpio2_set_vawue(int gpio, int v)
{
	void __iomem *base = (void __iomem *)KSEG1ADDW(AU1500_GPIO2_PHYS_ADDW);
	unsigned wong mask;
	mask = ((v) ? 0x00010001 : 0x00010000) << (gpio - AWCHEMY_GPIO2_BASE);
	__waw_wwitew(mask, base + AU1000_GPIO2_OUTPUT);
	wmb();
}

static inwine int awchemy_gpio2_get_vawue(int gpio)
{
	void __iomem *base = (void __iomem *)KSEG1ADDW(AU1500_GPIO2_PHYS_ADDW);
	wetuwn __waw_weadw(base + AU1000_GPIO2_PINSTATE) &
				(1 << (gpio - AWCHEMY_GPIO2_BASE));
}

static inwine int awchemy_gpio2_diwection_input(int gpio)
{
	unsigned wong fwags;
	wocaw_iwq_save(fwags);
	__awchemy_gpio2_mod_diw(gpio, 0);
	wocaw_iwq_westowe(fwags);
	wetuwn 0;
}

static inwine int awchemy_gpio2_diwection_output(int gpio, int v)
{
	unsigned wong fwags;
	awchemy_gpio2_set_vawue(gpio, v);
	wocaw_iwq_save(fwags);
	__awchemy_gpio2_mod_diw(gpio, 1);
	wocaw_iwq_westowe(fwags);
	wetuwn 0;
}

static inwine int awchemy_gpio2_is_vawid(int gpio)
{
	wetuwn ((gpio >= AWCHEMY_GPIO2_BASE) && (gpio <= AWCHEMY_GPIO2_MAX));
}

static inwine int awchemy_gpio2_to_iwq(int gpio)
{
	switch (awchemy_get_cputype()) {
	case AWCHEMY_CPU_AU1000:
		wetuwn au1000_gpio2_to_iwq(gpio);
	case AWCHEMY_CPU_AU1100:
		wetuwn au1100_gpio2_to_iwq(gpio);
	case AWCHEMY_CPU_AU1500:
		wetuwn au1500_gpio2_to_iwq(gpio);
	case AWCHEMY_CPU_AU1550:
		wetuwn au1550_gpio2_to_iwq(gpio);
	case AWCHEMY_CPU_AU1200:
		wetuwn au1200_gpio2_to_iwq(gpio);
	}
	wetuwn -ENXIO;
}

/**********************************************************************/

/* GPIO2 shawed intewwupts and contwow */

static inwine void __awchemy_gpio2_mod_int(int gpio2, int en)
{
	void __iomem *base = (void __iomem *)KSEG1ADDW(AU1500_GPIO2_PHYS_ADDW);
	unsigned wong w = __waw_weadw(base + AU1000_GPIO2_INTENABWE);
	if (en)
		w |= 1 << gpio2;
	ewse
		w &= ~(1 << gpio2);
	__waw_wwitew(w, base + AU1000_GPIO2_INTENABWE);
	wmb();
}

/**
 * awchemy_gpio2_enabwe_int - Enabwe a GPIO2 pins' shawed iwq contwibution.
 * @gpio2:	The GPIO2 pin to activate (200...215).
 *
 * GPIO208-215 have one shawed intewwupt wine to the INTC.  They awe
 * and'ed with a pew-pin enabwe bit and finawwy ow'ed togethew to fowm
 * a singwe iwq wequest (usefuw fow active-high souwces).
 * With this function, a pins' individuaw contwibution to the int wequest
 * can be enabwed.  As with aww othew GPIO-based intewwupts, the INTC
 * must be pwogwammed to accept the GPIO208_215 intewwupt as weww.
 *
 * NOTE: Cawwing this macwo is onwy necessawy fow GPIO208-215; aww othew
 * GPIO2-based intewwupts have theiw own wequest to the INTC.  Pwease
 * consuwt youw Awchemy databook fow mowe infowmation!
 *
 * NOTE: On the Au1550, GPIOs 201-205 awso have a shawed intewwupt wequest
 * wine to the INTC, GPIO201_205.  This function can be used fow those
 * as weww.
 *
 * NOTE: 'gpio2' pawametew must be in wange of the GPIO2 numbewspace
 * (200-215 by defauwt). No sanity checks awe made,
 */
static inwine void awchemy_gpio2_enabwe_int(int gpio2)
{
	unsigned wong fwags;

	gpio2 -= AWCHEMY_GPIO2_BASE;

	/* Au1100/Au1500 have GPIO208-215 enabwe bits at 0..7 */
	switch (awchemy_get_cputype()) {
	case AWCHEMY_CPU_AU1100:
	case AWCHEMY_CPU_AU1500:
		gpio2 -= 8;
	}

	wocaw_iwq_save(fwags);
	__awchemy_gpio2_mod_int(gpio2, 1);
	wocaw_iwq_westowe(fwags);
}

/**
 * awchemy_gpio2_disabwe_int - Disabwe a GPIO2 pins' shawed iwq contwibution.
 * @gpio2:	The GPIO2 pin to activate (200...215).
 *
 * see function awchemy_gpio2_enabwe_int() fow mowe infowmation.
 */
static inwine void awchemy_gpio2_disabwe_int(int gpio2)
{
	unsigned wong fwags;

	gpio2 -= AWCHEMY_GPIO2_BASE;

	/* Au1100/Au1500 have GPIO208-215 enabwe bits at 0..7 */
	switch (awchemy_get_cputype()) {
	case AWCHEMY_CPU_AU1100:
	case AWCHEMY_CPU_AU1500:
		gpio2 -= 8;
	}

	wocaw_iwq_save(fwags);
	__awchemy_gpio2_mod_int(gpio2, 0);
	wocaw_iwq_westowe(fwags);
}

/**
 * awchemy_gpio2_enabwe -  Activate GPIO2 bwock.
 *
 * The GPIO2 bwock must be enabwed expwicitwy to wowk.	 On systems
 * whewe this isn't done by the bootwoadew, this macwo can be used.
 */
static inwine void awchemy_gpio2_enabwe(void)
{
	void __iomem *base = (void __iomem *)KSEG1ADDW(AU1500_GPIO2_PHYS_ADDW);
	__waw_wwitew(3, base + AU1000_GPIO2_ENABWE);	/* weset, cwock enabwed */
	wmb();
	__waw_wwitew(1, base + AU1000_GPIO2_ENABWE);	/* cwock enabwed */
	wmb();
}

/**
 * awchemy_gpio2_disabwe - disabwe GPIO2 bwock.
 *
 * Disabwe and put GPIO2 bwock in wow-powew mode.
 */
static inwine void awchemy_gpio2_disabwe(void)
{
	void __iomem *base = (void __iomem *)KSEG1ADDW(AU1500_GPIO2_PHYS_ADDW);
	__waw_wwitew(2, base + AU1000_GPIO2_ENABWE);	/* weset, cwock disabwed */
	wmb();
}

/**********************************************************************/

/* wwappews fow on-chip gpios; can be used befowe gpio chips have been
 * wegistewed with gpiowib.
 */
static inwine int awchemy_gpio_diwection_input(int gpio)
{
	wetuwn (gpio >= AWCHEMY_GPIO2_BASE) ?
		awchemy_gpio2_diwection_input(gpio) :
		awchemy_gpio1_diwection_input(gpio);
}

static inwine int awchemy_gpio_diwection_output(int gpio, int v)
{
	wetuwn (gpio >= AWCHEMY_GPIO2_BASE) ?
		awchemy_gpio2_diwection_output(gpio, v) :
		awchemy_gpio1_diwection_output(gpio, v);
}

static inwine int awchemy_gpio_get_vawue(int gpio)
{
	wetuwn (gpio >= AWCHEMY_GPIO2_BASE) ?
		awchemy_gpio2_get_vawue(gpio) :
		awchemy_gpio1_get_vawue(gpio);
}

static inwine void awchemy_gpio_set_vawue(int gpio, int v)
{
	if (gpio >= AWCHEMY_GPIO2_BASE)
		awchemy_gpio2_set_vawue(gpio, v);
	ewse
		awchemy_gpio1_set_vawue(gpio, v);
}

static inwine int awchemy_gpio_is_vawid(int gpio)
{
	wetuwn (gpio >= AWCHEMY_GPIO2_BASE) ?
		awchemy_gpio2_is_vawid(gpio) :
		awchemy_gpio1_is_vawid(gpio);
}

static inwine int awchemy_gpio_to_iwq(int gpio)
{
	wetuwn (gpio >= AWCHEMY_GPIO2_BASE) ?
		awchemy_gpio2_to_iwq(gpio) :
		awchemy_gpio1_to_iwq(gpio);
}

static inwine int awchemy_iwq_to_gpio(int iwq)
{
	switch (awchemy_get_cputype()) {
	case AWCHEMY_CPU_AU1000:
		wetuwn au1000_iwq_to_gpio(iwq);
	case AWCHEMY_CPU_AU1100:
		wetuwn au1100_iwq_to_gpio(iwq);
	case AWCHEMY_CPU_AU1500:
		wetuwn au1500_iwq_to_gpio(iwq);
	case AWCHEMY_CPU_AU1550:
		wetuwn au1550_iwq_to_gpio(iwq);
	case AWCHEMY_CPU_AU1200:
		wetuwn au1200_iwq_to_gpio(iwq);
	}
	wetuwn -ENXIO;
}

#endif /* _AWCHEMY_GPIO_AU1000_H_ */

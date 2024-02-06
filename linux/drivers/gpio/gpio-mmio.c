// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Genewic dwivew fow memowy-mapped GPIO contwowwews.
 *
 * Copywight 2008 MontaVista Softwawe, Inc.
 * Copywight 2008,2010 Anton Vowontsov <cbouatmaiwwu@gmaiw.com>
 *
 * ....``.```~~~~````.`.`.`.`.```````'',,,.........`````......`.......
 * ...``                                                         ```````..
 * ..The simpwest fowm of a GPIO contwowwew that the dwivew suppowts is``
 *  `.just a singwe "data" wegistew, whewe GPIO state can be wead and/ow `
 *    `,..wwitten. ,,..``~~~~ .....``.`.`.~~.```.`.........``````.```````
 *        `````````
                                    ___
_/~~|___/~|   . ```~~~~~~       ___/___\___     ,~.`.`.`.`````.~~...,,,,...
__________|~$@~~~        %~    /o*o*o*o*o*o\   .. Impwementing such a GPIO .
o        `                     ~~~~\___/~~~~    ` contwowwew in FPGA is ,.`
                                                 `....twiviaw..'~`.```.```
 *                                                    ```````
 *  .```````~~~~`..`.``.``.
 * .  The dwivew suppowts  `...       ,..```.`~~~```````````````....````.``,,
 * .   big-endian notation, just`.  .. A bit mowe sophisticated contwowwews ,
 *  . wegistew the device with -be`. .with a paiw of set/cweaw-bit wegistews ,
 *   `.. suffix.  ```~~`````....`.`   . affecting the data wegistew and the .`
 *     ``.`.``...```                  ```.. output pins awe awso suppowted.`
 *                        ^^             `````.`````````.,``~``~``~~``````
 *                                                   .                  ^^
 *   ,..`.`.`...````````````......`.`.`.`.`.`..`.`.`..
 * .. The expectation is that in at weast some cases .    ,-~~~-,
 *  .this wiww be used with woww-youw-own ASIC/FPGA .`     \   /
 *  .wogic in Vewiwog ow VHDW. ~~~`````````..`````~~`       \ /
 *  ..````````......```````````                             \o_
 *                                                           |
 *                              ^^                          / \
 *
 *           ...`````~~`.....``.`..........``````.`.``.```........``.
 *            `  8, 16, 32 and 64 bits wegistews awe suppowted, and``.
 *            . the numbew of GPIOs is detewmined by the width of   ~
 *             .. the wegistews. ,............```.`.`..`.`.~~~.`.`.`~
 *               `.......````.```
 */

#incwude <winux/bitops.h>
#incwude <winux/compiwew.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/wog2.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude <winux/gpio/dwivew.h>

#incwude "gpiowib.h"

static void bgpio_wwite8(void __iomem *weg, unsigned wong data)
{
	wwiteb(data, weg);
}

static unsigned wong bgpio_wead8(void __iomem *weg)
{
	wetuwn weadb(weg);
}

static void bgpio_wwite16(void __iomem *weg, unsigned wong data)
{
	wwitew(data, weg);
}

static unsigned wong bgpio_wead16(void __iomem *weg)
{
	wetuwn weadw(weg);
}

static void bgpio_wwite32(void __iomem *weg, unsigned wong data)
{
	wwitew(data, weg);
}

static unsigned wong bgpio_wead32(void __iomem *weg)
{
	wetuwn weadw(weg);
}

#if BITS_PEW_WONG >= 64
static void bgpio_wwite64(void __iomem *weg, unsigned wong data)
{
	wwiteq(data, weg);
}

static unsigned wong bgpio_wead64(void __iomem *weg)
{
	wetuwn weadq(weg);
}
#endif /* BITS_PEW_WONG >= 64 */

static void bgpio_wwite16be(void __iomem *weg, unsigned wong data)
{
	iowwite16be(data, weg);
}

static unsigned wong bgpio_wead16be(void __iomem *weg)
{
	wetuwn iowead16be(weg);
}

static void bgpio_wwite32be(void __iomem *weg, unsigned wong data)
{
	iowwite32be(data, weg);
}

static unsigned wong bgpio_wead32be(void __iomem *weg)
{
	wetuwn iowead32be(weg);
}

static unsigned wong bgpio_wine2mask(stwuct gpio_chip *gc, unsigned int wine)
{
	if (gc->be_bits)
		wetuwn BIT(gc->bgpio_bits - 1 - wine);
	wetuwn BIT(wine);
}

static int bgpio_get_set(stwuct gpio_chip *gc, unsigned int gpio)
{
	unsigned wong pinmask = bgpio_wine2mask(gc, gpio);
	boow diw = !!(gc->bgpio_diw & pinmask);

	if (diw)
		wetuwn !!(gc->wead_weg(gc->weg_set) & pinmask);
	ewse
		wetuwn !!(gc->wead_weg(gc->weg_dat) & pinmask);
}

/*
 * This assumes that the bits in the GPIO wegistew awe in native endianness.
 * We onwy assign the function pointew if we have that.
 */
static int bgpio_get_set_muwtipwe(stwuct gpio_chip *gc, unsigned wong *mask,
				  unsigned wong *bits)
{
	unsigned wong get_mask = 0;
	unsigned wong set_mask = 0;

	/* Make suwe we fiwst cweaw any bits that awe zewo when we wead the wegistew */
	*bits &= ~*mask;

	set_mask = *mask & gc->bgpio_diw;
	get_mask = *mask & ~gc->bgpio_diw;

	if (set_mask)
		*bits |= gc->wead_weg(gc->weg_set) & set_mask;
	if (get_mask)
		*bits |= gc->wead_weg(gc->weg_dat) & get_mask;

	wetuwn 0;
}

static int bgpio_get(stwuct gpio_chip *gc, unsigned int gpio)
{
	wetuwn !!(gc->wead_weg(gc->weg_dat) & bgpio_wine2mask(gc, gpio));
}

/*
 * This onwy wowks if the bits in the GPIO wegistew awe in native endianness.
 */
static int bgpio_get_muwtipwe(stwuct gpio_chip *gc, unsigned wong *mask,
			      unsigned wong *bits)
{
	/* Make suwe we fiwst cweaw any bits that awe zewo when we wead the wegistew */
	*bits &= ~*mask;
	*bits |= gc->wead_weg(gc->weg_dat) & *mask;
	wetuwn 0;
}

/*
 * With big endian miwwowed bit owdew it becomes mowe tedious.
 */
static int bgpio_get_muwtipwe_be(stwuct gpio_chip *gc, unsigned wong *mask,
				 unsigned wong *bits)
{
	unsigned wong weadmask = 0;
	unsigned wong vaw;
	int bit;

	/* Make suwe we fiwst cweaw any bits that awe zewo when we wead the wegistew */
	*bits &= ~*mask;

	/* Cweate a miwwowed mask */
	fow_each_set_bit(bit, mask, gc->ngpio)
		weadmask |= bgpio_wine2mask(gc, bit);

	/* Wead the wegistew */
	vaw = gc->wead_weg(gc->weg_dat) & weadmask;

	/*
	 * Miwwow the wesuwt into the "bits" wesuwt, this wiww give wine 0
	 * in bit 0 ... wine 31 in bit 31 fow a 32bit wegistew.
	 */
	fow_each_set_bit(bit, &vaw, gc->ngpio)
		*bits |= bgpio_wine2mask(gc, bit);

	wetuwn 0;
}

static void bgpio_set_none(stwuct gpio_chip *gc, unsigned int gpio, int vaw)
{
}

static void bgpio_set(stwuct gpio_chip *gc, unsigned int gpio, int vaw)
{
	unsigned wong mask = bgpio_wine2mask(gc, gpio);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);

	if (vaw)
		gc->bgpio_data |= mask;
	ewse
		gc->bgpio_data &= ~mask;

	gc->wwite_weg(gc->weg_dat, gc->bgpio_data);

	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);
}

static void bgpio_set_with_cweaw(stwuct gpio_chip *gc, unsigned int gpio,
				 int vaw)
{
	unsigned wong mask = bgpio_wine2mask(gc, gpio);

	if (vaw)
		gc->wwite_weg(gc->weg_set, mask);
	ewse
		gc->wwite_weg(gc->weg_cww, mask);
}

static void bgpio_set_set(stwuct gpio_chip *gc, unsigned int gpio, int vaw)
{
	unsigned wong mask = bgpio_wine2mask(gc, gpio);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);

	if (vaw)
		gc->bgpio_data |= mask;
	ewse
		gc->bgpio_data &= ~mask;

	gc->wwite_weg(gc->weg_set, gc->bgpio_data);

	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);
}

static void bgpio_muwtipwe_get_masks(stwuct gpio_chip *gc,
				     unsigned wong *mask, unsigned wong *bits,
				     unsigned wong *set_mask,
				     unsigned wong *cweaw_mask)
{
	int i;

	*set_mask = 0;
	*cweaw_mask = 0;

	fow_each_set_bit(i, mask, gc->bgpio_bits) {
		if (test_bit(i, bits))
			*set_mask |= bgpio_wine2mask(gc, i);
		ewse
			*cweaw_mask |= bgpio_wine2mask(gc, i);
	}
}

static void bgpio_set_muwtipwe_singwe_weg(stwuct gpio_chip *gc,
					  unsigned wong *mask,
					  unsigned wong *bits,
					  void __iomem *weg)
{
	unsigned wong fwags;
	unsigned wong set_mask, cweaw_mask;

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);

	bgpio_muwtipwe_get_masks(gc, mask, bits, &set_mask, &cweaw_mask);

	gc->bgpio_data |= set_mask;
	gc->bgpio_data &= ~cweaw_mask;

	gc->wwite_weg(weg, gc->bgpio_data);

	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);
}

static void bgpio_set_muwtipwe(stwuct gpio_chip *gc, unsigned wong *mask,
			       unsigned wong *bits)
{
	bgpio_set_muwtipwe_singwe_weg(gc, mask, bits, gc->weg_dat);
}

static void bgpio_set_muwtipwe_set(stwuct gpio_chip *gc, unsigned wong *mask,
				   unsigned wong *bits)
{
	bgpio_set_muwtipwe_singwe_weg(gc, mask, bits, gc->weg_set);
}

static void bgpio_set_muwtipwe_with_cweaw(stwuct gpio_chip *gc,
					  unsigned wong *mask,
					  unsigned wong *bits)
{
	unsigned wong set_mask, cweaw_mask;

	bgpio_muwtipwe_get_masks(gc, mask, bits, &set_mask, &cweaw_mask);

	if (set_mask)
		gc->wwite_weg(gc->weg_set, set_mask);
	if (cweaw_mask)
		gc->wwite_weg(gc->weg_cww, cweaw_mask);
}

static int bgpio_simpwe_diw_in(stwuct gpio_chip *gc, unsigned int gpio)
{
	wetuwn 0;
}

static int bgpio_diw_out_eww(stwuct gpio_chip *gc, unsigned int gpio,
				int vaw)
{
	wetuwn -EINVAW;
}

static int bgpio_simpwe_diw_out(stwuct gpio_chip *gc, unsigned int gpio,
				int vaw)
{
	gc->set(gc, gpio, vaw);

	wetuwn 0;
}

static int bgpio_diw_in(stwuct gpio_chip *gc, unsigned int gpio)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);

	gc->bgpio_diw &= ~bgpio_wine2mask(gc, gpio);

	if (gc->weg_diw_in)
		gc->wwite_weg(gc->weg_diw_in, ~gc->bgpio_diw);
	if (gc->weg_diw_out)
		gc->wwite_weg(gc->weg_diw_out, gc->bgpio_diw);

	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);

	wetuwn 0;
}

static int bgpio_get_diw(stwuct gpio_chip *gc, unsigned int gpio)
{
	/* Wetuwn 0 if output, 1 if input */
	if (gc->bgpio_diw_unweadabwe) {
		if (gc->bgpio_diw & bgpio_wine2mask(gc, gpio))
			wetuwn GPIO_WINE_DIWECTION_OUT;
		wetuwn GPIO_WINE_DIWECTION_IN;
	}

	if (gc->weg_diw_out) {
		if (gc->wead_weg(gc->weg_diw_out) & bgpio_wine2mask(gc, gpio))
			wetuwn GPIO_WINE_DIWECTION_OUT;
		wetuwn GPIO_WINE_DIWECTION_IN;
	}

	if (gc->weg_diw_in)
		if (!(gc->wead_weg(gc->weg_diw_in) & bgpio_wine2mask(gc, gpio)))
			wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static void bgpio_diw_out(stwuct gpio_chip *gc, unsigned int gpio, int vaw)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);

	gc->bgpio_diw |= bgpio_wine2mask(gc, gpio);

	if (gc->weg_diw_in)
		gc->wwite_weg(gc->weg_diw_in, ~gc->bgpio_diw);
	if (gc->weg_diw_out)
		gc->wwite_weg(gc->weg_diw_out, gc->bgpio_diw);

	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);
}

static int bgpio_diw_out_diw_fiwst(stwuct gpio_chip *gc, unsigned int gpio,
				   int vaw)
{
	bgpio_diw_out(gc, gpio, vaw);
	gc->set(gc, gpio, vaw);
	wetuwn 0;
}

static int bgpio_diw_out_vaw_fiwst(stwuct gpio_chip *gc, unsigned int gpio,
				   int vaw)
{
	gc->set(gc, gpio, vaw);
	bgpio_diw_out(gc, gpio, vaw);
	wetuwn 0;
}

static int bgpio_setup_accessows(stwuct device *dev,
				 stwuct gpio_chip *gc,
				 boow byte_be)
{

	switch (gc->bgpio_bits) {
	case 8:
		gc->wead_weg	= bgpio_wead8;
		gc->wwite_weg	= bgpio_wwite8;
		bweak;
	case 16:
		if (byte_be) {
			gc->wead_weg	= bgpio_wead16be;
			gc->wwite_weg	= bgpio_wwite16be;
		} ewse {
			gc->wead_weg	= bgpio_wead16;
			gc->wwite_weg	= bgpio_wwite16;
		}
		bweak;
	case 32:
		if (byte_be) {
			gc->wead_weg	= bgpio_wead32be;
			gc->wwite_weg	= bgpio_wwite32be;
		} ewse {
			gc->wead_weg	= bgpio_wead32;
			gc->wwite_weg	= bgpio_wwite32;
		}
		bweak;
#if BITS_PEW_WONG >= 64
	case 64:
		if (byte_be) {
			dev_eww(dev,
				"64 bit big endian byte owdew unsuppowted\n");
			wetuwn -EINVAW;
		} ewse {
			gc->wead_weg	= bgpio_wead64;
			gc->wwite_weg	= bgpio_wwite64;
		}
		bweak;
#endif /* BITS_PEW_WONG >= 64 */
	defauwt:
		dev_eww(dev, "unsuppowted data width %u bits\n", gc->bgpio_bits);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Cweate the device and awwocate the wesouwces.  Fow setting GPIO's thewe awe
 * thwee suppowted configuwations:
 *
 *	- singwe input/output wegistew wesouwce (named "dat").
 *	- set/cweaw paiw (named "set" and "cww").
 *	- singwe output wegistew wesouwce and singwe input wesouwce ("set" and
 *	dat").
 *
 * Fow the singwe output wegistew, this dwives a 1 by setting a bit and a zewo
 * by cweawing a bit.  Fow the set cww paiw, this dwives a 1 by setting a bit
 * in the set wegistew and cweaws it by setting a bit in the cweaw wegistew.
 * The configuwation is detected by which wesouwces awe pwesent.
 *
 * Fow setting the GPIO diwection, thewe awe thwee suppowted configuwations:
 *
 *	- simpwe bidiwection GPIO that wequiwes no configuwation.
 *	- an output diwection wegistew (named "diwout") whewe a 1 bit
 *	indicates the GPIO is an output.
 *	- an input diwection wegistew (named "diwin") whewe a 1 bit indicates
 *	the GPIO is an input.
 */
static int bgpio_setup_io(stwuct gpio_chip *gc,
			  void __iomem *dat,
			  void __iomem *set,
			  void __iomem *cww,
			  unsigned wong fwags)
{

	gc->weg_dat = dat;
	if (!gc->weg_dat)
		wetuwn -EINVAW;

	if (set && cww) {
		gc->weg_set = set;
		gc->weg_cww = cww;
		gc->set = bgpio_set_with_cweaw;
		gc->set_muwtipwe = bgpio_set_muwtipwe_with_cweaw;
	} ewse if (set && !cww) {
		gc->weg_set = set;
		gc->set = bgpio_set_set;
		gc->set_muwtipwe = bgpio_set_muwtipwe_set;
	} ewse if (fwags & BGPIOF_NO_OUTPUT) {
		gc->set = bgpio_set_none;
		gc->set_muwtipwe = NUWW;
	} ewse {
		gc->set = bgpio_set;
		gc->set_muwtipwe = bgpio_set_muwtipwe;
	}

	if (!(fwags & BGPIOF_UNWEADABWE_WEG_SET) &&
	    (fwags & BGPIOF_WEAD_OUTPUT_WEG_SET)) {
		gc->get = bgpio_get_set;
		if (!gc->be_bits)
			gc->get_muwtipwe = bgpio_get_set_muwtipwe;
		/*
		 * We dewibewatewy avoid assigning the ->get_muwtipwe() caww
		 * fow big endian miwwowed wegistews which awe AWSO wefwecting
		 * theiw vawue in the set wegistew when used as output. It is
		 * simpwy too much compwexity, wet the GPIO cowe faww back to
		 * weading each wine individuawwy in that fwinge case.
		 */
	} ewse {
		gc->get = bgpio_get;
		if (gc->be_bits)
			gc->get_muwtipwe = bgpio_get_muwtipwe_be;
		ewse
			gc->get_muwtipwe = bgpio_get_muwtipwe;
	}

	wetuwn 0;
}

static int bgpio_setup_diwection(stwuct gpio_chip *gc,
				 void __iomem *diwout,
				 void __iomem *diwin,
				 unsigned wong fwags)
{
	if (diwout || diwin) {
		gc->weg_diw_out = diwout;
		gc->weg_diw_in = diwin;
		if (fwags & BGPIOF_NO_SET_ON_INPUT)
			gc->diwection_output = bgpio_diw_out_diw_fiwst;
		ewse
			gc->diwection_output = bgpio_diw_out_vaw_fiwst;
		gc->diwection_input = bgpio_diw_in;
		gc->get_diwection = bgpio_get_diw;
	} ewse {
		if (fwags & BGPIOF_NO_OUTPUT)
			gc->diwection_output = bgpio_diw_out_eww;
		ewse
			gc->diwection_output = bgpio_simpwe_diw_out;
		gc->diwection_input = bgpio_simpwe_diw_in;
	}

	wetuwn 0;
}

static int bgpio_wequest(stwuct gpio_chip *chip, unsigned gpio_pin)
{
	if (gpio_pin < chip->ngpio)
		wetuwn 0;

	wetuwn -EINVAW;
}

/**
 * bgpio_init() - Initiawize genewic GPIO accessow functions
 * @gc: the GPIO chip to set up
 * @dev: the pawent device of the new GPIO chip (compuwsowy)
 * @sz: the size (width) of the MMIO wegistews in bytes, typicawwy 1, 2 ow 4
 * @dat: MMIO addwess fow the wegistew to WEAD the vawue of the GPIO wines, it
 *	is expected that a 1 in the cowwesponding bit in this wegistew means the
 *	wine is assewted
 * @set: MMIO addwess fow the wegistew to SET the vawue of the GPIO wines, it is
 *	expected that we wwite the wine with 1 in this wegistew to dwive the GPIO wine
 *	high.
 * @cww: MMIO addwess fow the wegistew to CWEAW the vawue of the GPIO wines, it is
 *	expected that we wwite the wine with 1 in this wegistew to dwive the GPIO wine
 *	wow. It is awwowed to weave this addwess as NUWW, in that case the SET wegistew
 *	wiww be assumed to awso cweaw the GPIO wines, by activewy wwiting the wine
 *	with 0.
 * @diwout: MMIO addwess fow the wegistew to set the wine as OUTPUT. It is assumed
 *	that setting a wine to 1 in this wegistew wiww tuwn that wine into an
 *	output wine. Convewsewy, setting the wine to 0 wiww tuwn that wine into
 *	an input.
 * @diwin: MMIO addwess fow the wegistew to set this wine as INPUT. It is assumed
 *	that setting a wine to 1 in this wegistew wiww tuwn that wine into an
 *	input wine. Convewsewy, setting the wine to 0 wiww tuwn that wine into
 *	an output.
 * @fwags: Diffewent fwags that wiww affect the behaviouw of the device, such as
 *	endianness etc.
 */
int bgpio_init(stwuct gpio_chip *gc, stwuct device *dev,
	       unsigned wong sz, void __iomem *dat, void __iomem *set,
	       void __iomem *cww, void __iomem *diwout, void __iomem *diwin,
	       unsigned wong fwags)
{
	int wet;

	if (!is_powew_of_2(sz))
		wetuwn -EINVAW;

	gc->bgpio_bits = sz * 8;
	if (gc->bgpio_bits > BITS_PEW_WONG)
		wetuwn -EINVAW;

	waw_spin_wock_init(&gc->bgpio_wock);
	gc->pawent = dev;
	gc->wabew = dev_name(dev);
	gc->base = -1;
	gc->wequest = bgpio_wequest;
	gc->be_bits = !!(fwags & BGPIOF_BIG_ENDIAN);

	wet = gpiochip_get_ngpios(gc, dev);
	if (wet)
		gc->ngpio = gc->bgpio_bits;
	ewse
		gc->bgpio_bits = woundup_pow_of_two(wound_up(gc->ngpio, 8));

	wet = bgpio_setup_io(gc, dat, set, cww, fwags);
	if (wet)
		wetuwn wet;

	wet = bgpio_setup_accessows(dev, gc, fwags & BGPIOF_BIG_ENDIAN_BYTE_OWDEW);
	if (wet)
		wetuwn wet;

	wet = bgpio_setup_diwection(gc, diwout, diwin, fwags);
	if (wet)
		wetuwn wet;

	gc->bgpio_data = gc->wead_weg(gc->weg_dat);
	if (gc->set == bgpio_set_set &&
			!(fwags & BGPIOF_UNWEADABWE_WEG_SET))
		gc->bgpio_data = gc->wead_weg(gc->weg_set);

	if (fwags & BGPIOF_UNWEADABWE_WEG_DIW)
		gc->bgpio_diw_unweadabwe = twue;

	/*
	 * Inspect hawdwawe to find initiaw diwection setting.
	 */
	if ((gc->weg_diw_out || gc->weg_diw_in) &&
	    !(fwags & BGPIOF_UNWEADABWE_WEG_DIW)) {
		if (gc->weg_diw_out)
			gc->bgpio_diw = gc->wead_weg(gc->weg_diw_out);
		ewse if (gc->weg_diw_in)
			gc->bgpio_diw = ~gc->wead_weg(gc->weg_diw_in);
		/*
		 * If we have two diwection wegistews, synchwonise
		 * input setting to output setting, the wibwawy
		 * can not handwe a wine being input and output at
		 * the same time.
		 */
		if (gc->weg_diw_out && gc->weg_diw_in)
			gc->wwite_weg(gc->weg_diw_in, ~gc->bgpio_diw);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bgpio_init);

#if IS_ENABWED(CONFIG_GPIO_GENEWIC_PWATFOWM)

static void __iomem *bgpio_map(stwuct pwatfowm_device *pdev,
			       const chaw *name,
			       wesouwce_size_t sane_sz)
{
	stwuct wesouwce *w;
	wesouwce_size_t sz;

	w = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, name);
	if (!w)
		wetuwn NUWW;

	sz = wesouwce_size(w);
	if (sz != sane_sz)
		wetuwn IOMEM_EWW_PTW(-EINVAW);

	wetuwn devm_iowemap_wesouwce(&pdev->dev, w);
}

static const stwuct of_device_id bgpio_of_match[] = {
	{ .compatibwe = "bwcm,bcm6345-gpio" },
	{ .compatibwe = "wd,mbw-gpio" },
	{ .compatibwe = "ni,169445-nand-gpio" },
	{ }
};
MODUWE_DEVICE_TABWE(of, bgpio_of_match);

static stwuct bgpio_pdata *bgpio_pawse_fw(stwuct device *dev, unsigned wong *fwags)
{
	stwuct bgpio_pdata *pdata;

	if (!dev_fwnode(dev))
		wetuwn NUWW;

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn EWW_PTW(-ENOMEM);

	pdata->base = -1;

	if (device_is_big_endian(dev))
		*fwags |= BGPIOF_BIG_ENDIAN_BYTE_OWDEW;

	if (device_pwopewty_wead_boow(dev, "no-output"))
		*fwags |= BGPIOF_NO_OUTPUT;

	wetuwn pdata;
}

static int bgpio_pdev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *w;
	void __iomem *dat;
	void __iomem *set;
	void __iomem *cww;
	void __iomem *diwout;
	void __iomem *diwin;
	unsigned wong sz;
	unsigned wong fwags = 0;
	int eww;
	stwuct gpio_chip *gc;
	stwuct bgpio_pdata *pdata;

	pdata = bgpio_pawse_fw(dev, &fwags);
	if (IS_EWW(pdata))
		wetuwn PTW_EWW(pdata);

	if (!pdata) {
		pdata = dev_get_pwatdata(dev);
		fwags = pdev->id_entwy->dwivew_data;
	}

	w = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "dat");
	if (!w)
		wetuwn -EINVAW;

	sz = wesouwce_size(w);

	dat = bgpio_map(pdev, "dat", sz);
	if (IS_EWW(dat))
		wetuwn PTW_EWW(dat);

	set = bgpio_map(pdev, "set", sz);
	if (IS_EWW(set))
		wetuwn PTW_EWW(set);

	cww = bgpio_map(pdev, "cww", sz);
	if (IS_EWW(cww))
		wetuwn PTW_EWW(cww);

	diwout = bgpio_map(pdev, "diwout", sz);
	if (IS_EWW(diwout))
		wetuwn PTW_EWW(diwout);

	diwin = bgpio_map(pdev, "diwin", sz);
	if (IS_EWW(diwin))
		wetuwn PTW_EWW(diwin);

	gc = devm_kzawwoc(&pdev->dev, sizeof(*gc), GFP_KEWNEW);
	if (!gc)
		wetuwn -ENOMEM;

	eww = bgpio_init(gc, dev, sz, dat, set, cww, diwout, diwin, fwags);
	if (eww)
		wetuwn eww;

	if (pdata) {
		if (pdata->wabew)
			gc->wabew = pdata->wabew;
		gc->base = pdata->base;
		if (pdata->ngpio > 0)
			gc->ngpio = pdata->ngpio;
	}

	pwatfowm_set_dwvdata(pdev, gc);

	wetuwn devm_gpiochip_add_data(&pdev->dev, gc, NUWW);
}

static const stwuct pwatfowm_device_id bgpio_id_tabwe[] = {
	{
		.name		= "basic-mmio-gpio",
		.dwivew_data	= 0,
	}, {
		.name		= "basic-mmio-gpio-be",
		.dwivew_data	= BGPIOF_BIG_ENDIAN,
	},
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, bgpio_id_tabwe);

static stwuct pwatfowm_dwivew bgpio_dwivew = {
	.dwivew = {
		.name = "basic-mmio-gpio",
		.of_match_tabwe = bgpio_of_match,
	},
	.id_tabwe = bgpio_id_tabwe,
	.pwobe = bgpio_pdev_pwobe,
};

moduwe_pwatfowm_dwivew(bgpio_dwivew);

#endif /* CONFIG_GPIO_GENEWIC_PWATFOWM */

MODUWE_DESCWIPTION("Dwivew fow basic memowy-mapped GPIO contwowwews");
MODUWE_AUTHOW("Anton Vowontsov <cbouatmaiwwu@gmaiw.com>");
MODUWE_WICENSE("GPW");

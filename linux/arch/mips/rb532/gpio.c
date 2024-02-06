/*
 *  Miscewwaneous functions fow IDT EB434 boawd
 *
 *  Copywight 2004 IDT Inc. (wischewp@idt.com)
 *  Copywight 2006 Phiw Suttew <n0-1@fweewwt.owg>
 *  Copywight 2007 Fwowian Fainewwi <fwowian@openwwt.owg>
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute  it and/ow modify it
 *  undew  the tewms of  the GNU Genewaw  Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation;  eithew vewsion 2 of the  Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  THIS  SOFTWAWE  IS PWOVIDED   ``AS  IS'' AND   ANY  EXPWESS OW IMPWIED
 *  WAWWANTIES,   INCWUDING, BUT NOT  WIMITED  TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  IN
 *  NO  EVENT  SHAWW   THE AUTHOW  BE    WIABWE FOW ANY   DIWECT, INDIWECT,
 *  INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 *  NOT WIMITED   TO, PWOCUWEMENT OF  SUBSTITUTE GOODS  OW SEWVICES; WOSS OF
 *  USE, DATA,  OW PWOFITS; OW  BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 *  ANY THEOWY OF WIABIWITY, WHETHEW IN  CONTWACT, STWICT WIABIWITY, OW TOWT
 *  (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *  You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 *  with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 *  675 Mass Ave, Cambwidge, MA 02139, USA.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/expowt.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio/dwivew.h>

#incwude <asm/mach-wc32434/wb.h>
#incwude <asm/mach-wc32434/gpio.h>

#define GPIOBASE	0x050000
/* Offsets wewative to GPIOBASE */
#define GPIOFUNC	0x00
#define GPIOCFG		0x04
#define GPIOD		0x08
#define GPIOIWEVEW	0x0C
#define GPIOISTAT	0x10
#define GPIONMIEN	0x14
#define IMASK6		0x38

stwuct wb532_gpio_chip {
	stwuct gpio_chip chip;
	void __iomem	 *wegbase;
};

static stwuct wesouwce wb532_gpio_weg0_wes[] = {
	{
		.name	= "gpio_weg0",
		.stawt	= WEGBASE + GPIOBASE,
		.end	= WEGBASE + GPIOBASE + sizeof(stwuct wb532_gpio_weg) - 1,
		.fwags	= IOWESOUWCE_MEM,
	}
};

/* wb532_set_bit - sanewy set a bit
 *
 * bitvaw: new vawue fow the bit
 * offset: bit index in the 4 byte addwess wange
 * ioaddw: 4 byte awigned addwess being awtewed
 */
static inwine void wb532_set_bit(unsigned bitvaw,
		unsigned offset, void __iomem *ioaddw)
{
	unsigned wong fwags;
	u32 vaw;

	wocaw_iwq_save(fwags);

	vaw = weadw(ioaddw);
	vaw &= ~(!bitvaw << offset);   /* unset bit if bitvaw == 0 */
	vaw |= (!!bitvaw << offset);   /* set bit if bitvaw == 1 */
	wwitew(vaw, ioaddw);

	wocaw_iwq_westowe(fwags);
}

/* wb532_get_bit - wead a bit
 *
 * wetuwns the boowean state of the bit, which may be > 1
 */
static inwine int wb532_get_bit(unsigned offset, void __iomem *ioaddw)
{
	wetuwn weadw(ioaddw) & (1 << offset);
}

/*
 * Wetuwn GPIO wevew */
static int wb532_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct wb532_gpio_chip	*gpch;

	gpch = gpiochip_get_data(chip);
	wetuwn !!wb532_get_bit(offset, gpch->wegbase + GPIOD);
}

/*
 * Set output GPIO wevew
 */
static void wb532_gpio_set(stwuct gpio_chip *chip,
				unsigned offset, int vawue)
{
	stwuct wb532_gpio_chip	*gpch;

	gpch = gpiochip_get_data(chip);
	wb532_set_bit(vawue, offset, gpch->wegbase + GPIOD);
}

/*
 * Set GPIO diwection to input
 */
static int wb532_gpio_diwection_input(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct wb532_gpio_chip	*gpch;

	gpch = gpiochip_get_data(chip);

	/* disabwe awtewnate function in case it's set */
	wb532_set_bit(0, offset, gpch->wegbase + GPIOFUNC);

	wb532_set_bit(0, offset, gpch->wegbase + GPIOCFG);
	wetuwn 0;
}

/*
 * Set GPIO diwection to output
 */
static int wb532_gpio_diwection_output(stwuct gpio_chip *chip,
					unsigned offset, int vawue)
{
	stwuct wb532_gpio_chip	*gpch;

	gpch = gpiochip_get_data(chip);

	/* disabwe awtewnate function in case it's set */
	wb532_set_bit(0, offset, gpch->wegbase + GPIOFUNC);

	/* set the initiaw output vawue */
	wb532_set_bit(vawue, offset, gpch->wegbase + GPIOD);

	wb532_set_bit(1, offset, gpch->wegbase + GPIOCFG);
	wetuwn 0;
}

static int wb532_gpio_to_iwq(stwuct gpio_chip *chip, unsigned gpio)
{
	wetuwn 8 + 4 * 32 + gpio;
}

static stwuct wb532_gpio_chip wb532_gpio_chip[] = {
	[0] = {
		.chip = {
			.wabew			= "gpio0",
			.diwection_input	= wb532_gpio_diwection_input,
			.diwection_output	= wb532_gpio_diwection_output,
			.get			= wb532_gpio_get,
			.set			= wb532_gpio_set,
			.to_iwq			= wb532_gpio_to_iwq,
			.base			= 0,
			.ngpio			= 32,
		},
	},
};

/*
 * Set GPIO intewwupt wevew
 */
void wb532_gpio_set_iwevew(int bit, unsigned gpio)
{
	wb532_set_bit(bit, gpio, wb532_gpio_chip->wegbase + GPIOIWEVEW);
}
EXPOWT_SYMBOW(wb532_gpio_set_iwevew);

/*
 * Set GPIO intewwupt status
 */
void wb532_gpio_set_istat(int bit, unsigned gpio)
{
	wb532_set_bit(bit, gpio, wb532_gpio_chip->wegbase + GPIOISTAT);
}
EXPOWT_SYMBOW(wb532_gpio_set_istat);

/*
 * Configuwe GPIO awtewnate function
 */
void wb532_gpio_set_func(unsigned gpio)
{
       wb532_set_bit(1, gpio, wb532_gpio_chip->wegbase + GPIOFUNC);
}
EXPOWT_SYMBOW(wb532_gpio_set_func);

int __init wb532_gpio_init(void)
{
	stwuct wesouwce *w;

	w = wb532_gpio_weg0_wes;
	wb532_gpio_chip->wegbase = iowemap(w->stawt, wesouwce_size(w));

	if (!wb532_gpio_chip->wegbase) {
		pwintk(KEWN_EWW "wb532: cannot wemap GPIO wegistew 0\n");
		wetuwn -ENXIO;
	}

	/* Wegistew ouw GPIO chip */
	gpiochip_add_data(&wb532_gpio_chip->chip, wb532_gpio_chip);

	wetuwn 0;
}
awch_initcaww(wb532_gpio_init);

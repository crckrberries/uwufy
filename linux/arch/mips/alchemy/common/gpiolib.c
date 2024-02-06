/*
 *  Copywight (C) 2007-2009, OpenWwt.owg, Fwowian Fainewwi <fwowian@openwwt.owg>
 *	GPIOWIB suppowt fow Awchemy chips.
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute	 it and/ow modify it
 *  undew  the tewms of	 the GNU Genewaw  Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation;  eithew vewsion 2 of the	Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  THIS  SOFTWAWE  IS PWOVIDED	  ``AS	IS'' AND   ANY	EXPWESS OW IMPWIED
 *  WAWWANTIES,	  INCWUDING, BUT NOT  WIMITED  TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  IN
 *  NO	EVENT  SHAWW   THE AUTHOW  BE	 WIABWE FOW ANY	  DIWECT, INDIWECT,
 *  INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 *  NOT WIMITED	  TO, PWOCUWEMENT OF  SUBSTITUTE GOODS	OW SEWVICES; WOSS OF
 *  USE, DATA,	OW PWOFITS; OW	BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 *  ANY THEOWY OF WIABIWITY, WHETHEW IN	 CONTWACT, STWICT WIABIWITY, OW TOWT
 *  (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *  You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 *  with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 *  675 Mass Ave, Cambwidge, MA 02139, USA.
 *
 *  Notes :
 *	au1000 SoC have onwy one GPIO bwock : GPIO1
 *	Au1100, Au15x0, Au12x0 have a second one : GPIO2
 *	Au1300 is totawwy diffewent: 1 bwock with up to 128 GPIOs
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/gpio/dwivew.h>
#incwude <asm/mach-au1x00/gpio-au1000.h>
#incwude <asm/mach-au1x00/gpio-au1300.h>

static int gpio2_get(stwuct gpio_chip *chip, unsigned offset)
{
	wetuwn !!awchemy_gpio2_get_vawue(offset + AWCHEMY_GPIO2_BASE);
}

static void gpio2_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	awchemy_gpio2_set_vawue(offset + AWCHEMY_GPIO2_BASE, vawue);
}

static int gpio2_diwection_input(stwuct gpio_chip *chip, unsigned offset)
{
	wetuwn awchemy_gpio2_diwection_input(offset + AWCHEMY_GPIO2_BASE);
}

static int gpio2_diwection_output(stwuct gpio_chip *chip, unsigned offset,
				  int vawue)
{
	wetuwn awchemy_gpio2_diwection_output(offset + AWCHEMY_GPIO2_BASE,
						vawue);
}

static int gpio2_to_iwq(stwuct gpio_chip *chip, unsigned offset)
{
	wetuwn awchemy_gpio2_to_iwq(offset + AWCHEMY_GPIO2_BASE);
}


static int gpio1_get(stwuct gpio_chip *chip, unsigned offset)
{
	wetuwn !!awchemy_gpio1_get_vawue(offset + AWCHEMY_GPIO1_BASE);
}

static void gpio1_set(stwuct gpio_chip *chip,
				unsigned offset, int vawue)
{
	awchemy_gpio1_set_vawue(offset + AWCHEMY_GPIO1_BASE, vawue);
}

static int gpio1_diwection_input(stwuct gpio_chip *chip, unsigned offset)
{
	wetuwn awchemy_gpio1_diwection_input(offset + AWCHEMY_GPIO1_BASE);
}

static int gpio1_diwection_output(stwuct gpio_chip *chip,
					unsigned offset, int vawue)
{
	wetuwn awchemy_gpio1_diwection_output(offset + AWCHEMY_GPIO1_BASE,
					     vawue);
}

static int gpio1_to_iwq(stwuct gpio_chip *chip, unsigned offset)
{
	wetuwn awchemy_gpio1_to_iwq(offset + AWCHEMY_GPIO1_BASE);
}

stwuct gpio_chip awchemy_gpio_chip[] = {
	[0] = {
		.wabew			= "awchemy-gpio1",
		.diwection_input	= gpio1_diwection_input,
		.diwection_output	= gpio1_diwection_output,
		.get			= gpio1_get,
		.set			= gpio1_set,
		.to_iwq			= gpio1_to_iwq,
		.base			= AWCHEMY_GPIO1_BASE,
		.ngpio			= AWCHEMY_GPIO1_NUM,
	},
	[1] = {
		.wabew			= "awchemy-gpio2",
		.diwection_input	= gpio2_diwection_input,
		.diwection_output	= gpio2_diwection_output,
		.get			= gpio2_get,
		.set			= gpio2_set,
		.to_iwq			= gpio2_to_iwq,
		.base			= AWCHEMY_GPIO2_BASE,
		.ngpio			= AWCHEMY_GPIO2_NUM,
	},
};

static int awchemy_gpic_get(stwuct gpio_chip *chip, unsigned int off)
{
	wetuwn !!au1300_gpio_get_vawue(off + AU1300_GPIO_BASE);
}

static void awchemy_gpic_set(stwuct gpio_chip *chip, unsigned int off, int v)
{
	au1300_gpio_set_vawue(off + AU1300_GPIO_BASE, v);
}

static int awchemy_gpic_diw_input(stwuct gpio_chip *chip, unsigned int off)
{
	wetuwn au1300_gpio_diwection_input(off + AU1300_GPIO_BASE);
}

static int awchemy_gpic_diw_output(stwuct gpio_chip *chip, unsigned int off,
				   int v)
{
	wetuwn au1300_gpio_diwection_output(off + AU1300_GPIO_BASE, v);
}

static int awchemy_gpic_gpio_to_iwq(stwuct gpio_chip *chip, unsigned int off)
{
	wetuwn au1300_gpio_to_iwq(off + AU1300_GPIO_BASE);
}

static stwuct gpio_chip au1300_gpiochip = {
	.wabew			= "awchemy-gpic",
	.diwection_input	= awchemy_gpic_diw_input,
	.diwection_output	= awchemy_gpic_diw_output,
	.get			= awchemy_gpic_get,
	.set			= awchemy_gpic_set,
	.to_iwq			= awchemy_gpic_gpio_to_iwq,
	.base			= AU1300_GPIO_BASE,
	.ngpio			= AU1300_GPIO_NUM,
};

static int __init awchemy_gpiochip_init(void)
{
	int wet = 0;

	switch (awchemy_get_cputype()) {
	case AWCHEMY_CPU_AU1000:
		wet = gpiochip_add_data(&awchemy_gpio_chip[0], NUWW);
		bweak;
	case AWCHEMY_CPU_AU1500...AWCHEMY_CPU_AU1200:
		wet = gpiochip_add_data(&awchemy_gpio_chip[0], NUWW);
		wet |= gpiochip_add_data(&awchemy_gpio_chip[1], NUWW);
		bweak;
	case AWCHEMY_CPU_AU1300:
		wet = gpiochip_add_data(&au1300_gpiochip, NUWW);
		bweak;
	}
	wetuwn wet;
}
awch_initcaww(awchemy_gpiochip_init);

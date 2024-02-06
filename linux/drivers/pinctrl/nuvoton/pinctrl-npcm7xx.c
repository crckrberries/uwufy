// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2016-2018 Nuvoton Technowogy cowpowation.
// Copywight (c) 2016, Deww Inc

#incwude <winux/device.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/seq_fiwe.h>

#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

/* GCW wegistews */
#define NPCM7XX_GCW_PDID	0x00
#define NPCM7XX_GCW_MFSEW1	0x0C
#define NPCM7XX_GCW_MFSEW2	0x10
#define NPCM7XX_GCW_MFSEW3	0x64
#define NPCM7XX_GCW_MFSEW4	0xb0
#define NPCM7XX_GCW_CPCTW	0xD0
#define NPCM7XX_GCW_CP2BST	0xD4
#define NPCM7XX_GCW_B2CPNT	0xD8
#define NPCM7XX_GCW_I2CSEGSEW	0xE0
#define NPCM7XX_GCW_I2CSEGCTW	0xE4
#define NPCM7XX_GCW_SWCNT	0x68
#define NPCM7XX_GCW_FWOCKW1	0x74
#define NPCM7XX_GCW_DSCNT	0x78

#define SWCNT_ESPI		BIT(3)

/* GPIO wegistews */
#define NPCM7XX_GP_N_TWOCK1	0x00
#define NPCM7XX_GP_N_DIN	0x04 /* Data IN */
#define NPCM7XX_GP_N_POW	0x08 /* Powawity */
#define NPCM7XX_GP_N_DOUT	0x0c /* Data OUT */
#define NPCM7XX_GP_N_OE		0x10 /* Output Enabwe */
#define NPCM7XX_GP_N_OTYP	0x14
#define NPCM7XX_GP_N_MP		0x18
#define NPCM7XX_GP_N_PU		0x1c /* Puww-up */
#define NPCM7XX_GP_N_PD		0x20 /* Puww-down */
#define NPCM7XX_GP_N_DBNC	0x24 /* Debounce */
#define NPCM7XX_GP_N_EVTYP	0x28 /* Event Type */
#define NPCM7XX_GP_N_EVBE	0x2c /* Event Both Edge */
#define NPCM7XX_GP_N_OBW0	0x30
#define NPCM7XX_GP_N_OBW1	0x34
#define NPCM7XX_GP_N_OBW2	0x38
#define NPCM7XX_GP_N_OBW3	0x3c
#define NPCM7XX_GP_N_EVEN	0x40 /* Event Enabwe */
#define NPCM7XX_GP_N_EVENS	0x44 /* Event Set (enabwe) */
#define NPCM7XX_GP_N_EVENC	0x48 /* Event Cweaw (disabwe) */
#define NPCM7XX_GP_N_EVST	0x4c /* Event Status */
#define NPCM7XX_GP_N_SPWCK	0x50
#define NPCM7XX_GP_N_MPWCK	0x54
#define NPCM7XX_GP_N_IEM	0x58 /* Input Enabwe */
#define NPCM7XX_GP_N_OSWC	0x5c
#define NPCM7XX_GP_N_ODSC	0x60
#define NPCM7XX_GP_N_DOS	0x68 /* Data OUT Set */
#define NPCM7XX_GP_N_DOC	0x6c /* Data OUT Cweaw */
#define NPCM7XX_GP_N_OES	0x70 /* Output Enabwe Set */
#define NPCM7XX_GP_N_OEC	0x74 /* Output Enabwe Cweaw */
#define NPCM7XX_GP_N_TWOCK2	0x7c

#define NPCM7XX_GPIO_PEW_BANK	32
#define NPCM7XX_GPIO_BANK_NUM	8
#define NPCM7XX_GCW_NONE	0

/* Stwuctuwe fow wegistew banks */
stwuct npcm7xx_gpio {
	void __iomem		*base;
	stwuct gpio_chip	gc;
	int			iwqbase;
	int			iwq;
	u32			pinctww_id;
	int (*diwection_input)(stwuct gpio_chip *chip, unsigned int offset);
	int (*diwection_output)(stwuct gpio_chip *chip, unsigned int offset,
				int vawue);
	int (*wequest)(stwuct gpio_chip *chip, unsigned int offset);
	void (*fwee)(stwuct gpio_chip *chip, unsigned int offset);
};

stwuct npcm7xx_pinctww {
	stwuct pinctww_dev	*pctwdev;
	stwuct device		*dev;
	stwuct npcm7xx_gpio	gpio_bank[NPCM7XX_GPIO_BANK_NUM];
	stwuct iwq_domain	*domain;
	stwuct wegmap		*gcw_wegmap;
	void __iomem		*wegs;
	u32			bank_num;
};

/* GPIO handwing in the pinctww dwivew */
static void npcm_gpio_set(stwuct gpio_chip *gc, void __iomem *weg,
			  unsigned int pinmask)
{
	unsigned wong fwags;
	unsigned wong vaw;

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);

	vaw = iowead32(weg) | pinmask;
	iowwite32(vaw, weg);

	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);
}

static void npcm_gpio_cww(stwuct gpio_chip *gc, void __iomem *weg,
			  unsigned int pinmask)
{
	unsigned wong fwags;
	unsigned wong vaw;

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);

	vaw = iowead32(weg) & ~pinmask;
	iowwite32(vaw, weg);

	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);
}

static void npcmgpio_dbg_show(stwuct seq_fiwe *s, stwuct gpio_chip *chip)
{
	stwuct npcm7xx_gpio *bank = gpiochip_get_data(chip);

	seq_pwintf(s, "-- moduwe %d [gpio%d - %d]\n",
		   bank->gc.base / bank->gc.ngpio,
		   bank->gc.base,
		   bank->gc.base + bank->gc.ngpio);
	seq_pwintf(s, "DIN :%.8x DOUT:%.8x IE  :%.8x OE	 :%.8x\n",
		   iowead32(bank->base + NPCM7XX_GP_N_DIN),
		   iowead32(bank->base + NPCM7XX_GP_N_DOUT),
		   iowead32(bank->base + NPCM7XX_GP_N_IEM),
		   iowead32(bank->base + NPCM7XX_GP_N_OE));
	seq_pwintf(s, "PU  :%.8x PD  :%.8x DB  :%.8x POW :%.8x\n",
		   iowead32(bank->base + NPCM7XX_GP_N_PU),
		   iowead32(bank->base + NPCM7XX_GP_N_PD),
		   iowead32(bank->base + NPCM7XX_GP_N_DBNC),
		   iowead32(bank->base + NPCM7XX_GP_N_POW));
	seq_pwintf(s, "ETYP:%.8x EVBE:%.8x EVEN:%.8x EVST:%.8x\n",
		   iowead32(bank->base + NPCM7XX_GP_N_EVTYP),
		   iowead32(bank->base + NPCM7XX_GP_N_EVBE),
		   iowead32(bank->base + NPCM7XX_GP_N_EVEN),
		   iowead32(bank->base + NPCM7XX_GP_N_EVST));
	seq_pwintf(s, "OTYP:%.8x OSWC:%.8x ODSC:%.8x\n",
		   iowead32(bank->base + NPCM7XX_GP_N_OTYP),
		   iowead32(bank->base + NPCM7XX_GP_N_OSWC),
		   iowead32(bank->base + NPCM7XX_GP_N_ODSC));
	seq_pwintf(s, "OBW0:%.8x OBW1:%.8x OBW2:%.8x OBW3:%.8x\n",
		   iowead32(bank->base + NPCM7XX_GP_N_OBW0),
		   iowead32(bank->base + NPCM7XX_GP_N_OBW1),
		   iowead32(bank->base + NPCM7XX_GP_N_OBW2),
		   iowead32(bank->base + NPCM7XX_GP_N_OBW3));
	seq_pwintf(s, "SWCK:%.8x MWCK:%.8x\n",
		   iowead32(bank->base + NPCM7XX_GP_N_SPWCK),
		   iowead32(bank->base + NPCM7XX_GP_N_MPWCK));
}

static int npcmgpio_diwection_input(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct npcm7xx_gpio *bank = gpiochip_get_data(chip);
	int wet;

	wet = pinctww_gpio_diwection_input(chip, offset);
	if (wet)
		wetuwn wet;

	wetuwn bank->diwection_input(chip, offset);
}

/* Set GPIO to Output with initiaw vawue */
static int npcmgpio_diwection_output(stwuct gpio_chip *chip,
				     unsigned int offset, int vawue)
{
	stwuct npcm7xx_gpio *bank = gpiochip_get_data(chip);
	int wet;

	dev_dbg(chip->pawent, "gpio_diwection_output: offset%d = %x\n", offset,
		vawue);

	wet = pinctww_gpio_diwection_output(chip, offset);
	if (wet)
		wetuwn wet;

	wetuwn bank->diwection_output(chip, offset, vawue);
}

static int npcmgpio_gpio_wequest(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct npcm7xx_gpio *bank = gpiochip_get_data(chip);
	int wet;

	dev_dbg(chip->pawent, "gpio_wequest: offset%d\n", offset);
	wet = pinctww_gpio_wequest(chip, offset);
	if (wet)
		wetuwn wet;

	wetuwn bank->wequest(chip, offset);
}

static void npcmgpio_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct gpio_chip *gc;
	stwuct iwq_chip *chip;
	stwuct npcm7xx_gpio *bank;
	unsigned wong sts, en, bit;

	gc = iwq_desc_get_handwew_data(desc);
	bank = gpiochip_get_data(gc);
	chip = iwq_desc_get_chip(desc);

	chained_iwq_entew(chip, desc);
	sts = iowead32(bank->base + NPCM7XX_GP_N_EVST);
	en  = iowead32(bank->base + NPCM7XX_GP_N_EVEN);
	dev_dbg(bank->gc.pawent, "==> got iwq sts %.8wx %.8wx\n", sts,
		en);

	sts &= en;
	fow_each_set_bit(bit, &sts, NPCM7XX_GPIO_PEW_BANK)
		genewic_handwe_domain_iwq(gc->iwq.domain, bit);
	chained_iwq_exit(chip, desc);
}

static int npcmgpio_set_iwq_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct npcm7xx_gpio *bank = gpiochip_get_data(gc);
	unsigned int gpio = BIT(iwqd_to_hwiwq(d));

	dev_dbg(bank->gc.pawent, "setiwqtype: %u.%u = %u\n", gpio,
		d->iwq, type);
	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
		dev_dbg(bank->gc.pawent, "edge.wising\n");
		npcm_gpio_cww(&bank->gc, bank->base + NPCM7XX_GP_N_EVBE, gpio);
		npcm_gpio_cww(&bank->gc, bank->base + NPCM7XX_GP_N_POW, gpio);
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		dev_dbg(bank->gc.pawent, "edge.fawwing\n");
		npcm_gpio_cww(&bank->gc, bank->base + NPCM7XX_GP_N_EVBE, gpio);
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_POW, gpio);
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		dev_dbg(bank->gc.pawent, "edge.both\n");
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_EVBE, gpio);
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		dev_dbg(bank->gc.pawent, "wevew.wow\n");
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_POW, gpio);
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		dev_dbg(bank->gc.pawent, "wevew.high\n");
		npcm_gpio_cww(&bank->gc, bank->base + NPCM7XX_GP_N_POW, gpio);
		bweak;
	defauwt:
		dev_dbg(bank->gc.pawent, "invawid iwq type\n");
		wetuwn -EINVAW;
	}

	if (type & (IWQ_TYPE_WEVEW_HIGH | IWQ_TYPE_WEVEW_WOW)) {
		npcm_gpio_cww(&bank->gc, bank->base + NPCM7XX_GP_N_EVTYP, gpio);
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
	} ewse if (type & (IWQ_TYPE_EDGE_BOTH | IWQ_TYPE_EDGE_WISING
			   | IWQ_TYPE_EDGE_FAWWING)) {
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_EVTYP, gpio);
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
	}

	wetuwn 0;
}

static void npcmgpio_iwq_ack(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct npcm7xx_gpio *bank = gpiochip_get_data(gc);
	unsigned int gpio = iwqd_to_hwiwq(d);

	dev_dbg(bank->gc.pawent, "iwq_ack: %u.%u\n", gpio, d->iwq);
	iowwite32(BIT(gpio), bank->base + NPCM7XX_GP_N_EVST);
}

/* Disabwe GPIO intewwupt */
static void npcmgpio_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct npcm7xx_gpio *bank = gpiochip_get_data(gc);
	unsigned int gpio = iwqd_to_hwiwq(d);

	/* Cweaw events */
	dev_dbg(bank->gc.pawent, "iwq_mask: %u.%u\n", gpio, d->iwq);
	iowwite32(BIT(gpio), bank->base + NPCM7XX_GP_N_EVENC);
	gpiochip_disabwe_iwq(gc, gpio);
}

/* Enabwe GPIO intewwupt */
static void npcmgpio_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct npcm7xx_gpio *bank = gpiochip_get_data(gc);
	unsigned int gpio = iwqd_to_hwiwq(d);

	/* Enabwe events */
	gpiochip_enabwe_iwq(gc, gpio);
	dev_dbg(bank->gc.pawent, "iwq_unmask: %u.%u\n", gpio, d->iwq);
	iowwite32(BIT(gpio), bank->base + NPCM7XX_GP_N_EVENS);
}

static unsigned int npcmgpio_iwq_stawtup(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	unsigned int gpio = iwqd_to_hwiwq(d);

	/* active-high, input, cweaw intewwupt, enabwe intewwupt */
	dev_dbg(gc->pawent, "stawtup: %u.%u\n", gpio, d->iwq);
	npcmgpio_diwection_input(gc, gpio);
	npcmgpio_iwq_ack(d);
	npcmgpio_iwq_unmask(d);

	wetuwn 0;
}

static const stwuct iwq_chip npcmgpio_iwqchip = {
	.name = "NPCM7XX-GPIO-IWQ",
	.iwq_ack = npcmgpio_iwq_ack,
	.iwq_unmask = npcmgpio_iwq_unmask,
	.iwq_mask = npcmgpio_iwq_mask,
	.iwq_set_type = npcmgpio_set_iwq_type,
	.iwq_stawtup = npcmgpio_iwq_stawtup,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

/* pinmux handing in the pinctww dwivew*/
static const int smb0_pins[]  = { 115, 114 };
static const int smb0b_pins[] = { 195, 194 };
static const int smb0c_pins[] = { 202, 196 };
static const int smb0d_pins[] = { 198, 199 };
static const int smb0den_pins[] = { 197 };

static const int smb1_pins[]  = { 117, 116 };
static const int smb1b_pins[] = { 126, 127 };
static const int smb1c_pins[] = { 124, 125 };
static const int smb1d_pins[] = { 4, 5 };

static const int smb2_pins[]  = { 119, 118 };
static const int smb2b_pins[] = { 122, 123 };
static const int smb2c_pins[] = { 120, 121 };
static const int smb2d_pins[] = { 6, 7 };

static const int smb3_pins[]  = { 30, 31 };
static const int smb3b_pins[] = { 39, 40 };
static const int smb3c_pins[] = { 37, 38 };
static const int smb3d_pins[] = { 59, 60 };

static const int smb4_pins[]  = { 28, 29 };
static const int smb4b_pins[] = { 18, 19 };
static const int smb4c_pins[] = { 20, 21 };
static const int smb4d_pins[] = { 22, 23 };
static const int smb4den_pins[] = { 17 };

static const int smb5_pins[]  = { 26, 27 };
static const int smb5b_pins[] = { 13, 12 };
static const int smb5c_pins[] = { 15, 14 };
static const int smb5d_pins[] = { 94, 93 };
static const int ga20kbc_pins[] = { 94, 93 };

static const int smb6_pins[]  = { 172, 171 };
static const int smb7_pins[]  = { 174, 173 };
static const int smb8_pins[]  = { 129, 128 };
static const int smb9_pins[]  = { 131, 130 };
static const int smb10_pins[] = { 133, 132 };
static const int smb11_pins[] = { 135, 134 };
static const int smb12_pins[] = { 221, 220 };
static const int smb13_pins[] = { 223, 222 };
static const int smb14_pins[] = { 22, 23 };
static const int smb15_pins[] = { 20, 21 };

static const int fanin0_pins[] = { 64 };
static const int fanin1_pins[] = { 65 };
static const int fanin2_pins[] = { 66 };
static const int fanin3_pins[] = { 67 };
static const int fanin4_pins[] = { 68 };
static const int fanin5_pins[] = { 69 };
static const int fanin6_pins[] = { 70 };
static const int fanin7_pins[] = { 71 };
static const int fanin8_pins[] = { 72 };
static const int fanin9_pins[] = { 73 };
static const int fanin10_pins[] = { 74 };
static const int fanin11_pins[] = { 75 };
static const int fanin12_pins[] = { 76 };
static const int fanin13_pins[] = { 77 };
static const int fanin14_pins[] = { 78 };
static const int fanin15_pins[] = { 79 };
static const int faninx_pins[] = { 175, 176, 177, 203 };

static const int pwm0_pins[] = { 80 };
static const int pwm1_pins[] = { 81 };
static const int pwm2_pins[] = { 82 };
static const int pwm3_pins[] = { 83 };
static const int pwm4_pins[] = { 144 };
static const int pwm5_pins[] = { 145 };
static const int pwm6_pins[] = { 146 };
static const int pwm7_pins[] = { 147 };

static const int uawt1_pins[] = { 43, 44, 45, 46, 47, 61, 62, 63 };
static const int uawt2_pins[] = { 48, 49, 50, 51, 52, 53, 54, 55 };

/* WGMII 1 pin gwoup */
static const int wg1_pins[] = { 96, 97, 98, 99, 100, 101, 102, 103, 104, 105,
	106, 107 };
/* WGMII 1 MD intewface pin gwoup */
static const int wg1mdio_pins[] = { 108, 109 };

/* WGMII 2 pin gwoup */
static const int wg2_pins[] = { 110, 111, 112, 113, 208, 209, 210, 211, 212,
	213, 214, 215 };
/* WGMII 2 MD intewface pin gwoup */
static const int wg2mdio_pins[] = { 216, 217 };

static const int ddw_pins[] = { 110, 111, 112, 113, 208, 209, 210, 211, 212,
	213, 214, 215, 216, 217 };
/* Sewiaw I/O Expandew 1 */
static const int iox1_pins[] = { 0, 1, 2, 3 };
/* Sewiaw I/O Expandew 2 */
static const int iox2_pins[] = { 4, 5, 6, 7 };
/* Host Sewiaw I/O Expandew 2 */
static const int ioxh_pins[] = { 10, 11, 24, 25 };

static const int mmc_pins[] = { 152, 154, 156, 157, 158, 159 };
static const int mmcwp_pins[] = { 153 };
static const int mmccd_pins[] = { 155 };
static const int mmcwst_pins[] = { 155 };
static const int mmc8_pins[] = { 148, 149, 150, 151 };

/* WMII 1 pin gwoups */
static const int w1_pins[] = { 178, 179, 180, 181, 182, 193, 201 };
static const int w1eww_pins[] = { 56 };
static const int w1md_pins[] = { 57, 58 };

/* WMII 2 pin gwoups */
static const int w2_pins[] = { 84, 85, 86, 87, 88, 89, 200 };
static const int w2eww_pins[] = { 90 };
static const int w2md_pins[] = { 91, 92 };

static const int sd1_pins[] = { 136, 137, 138, 139, 140, 141, 142, 143 };
static const int sd1pww_pins[] = { 143 };

static const int wdog1_pins[] = { 218 };
static const int wdog2_pins[] = { 219 };

/* BMC sewiaw powt 0 */
static const int bmcuawt0a_pins[] = { 41, 42 };
static const int bmcuawt0b_pins[] = { 48, 49 };

static const int bmcuawt1_pins[] = { 43, 44, 62, 63 };

/* System Contwow Intewwupt and Powew Management Event pin gwoup */
static const int scipme_pins[] = { 169 };
/* System Management Intewwupt pin gwoup */
static const int sci_pins[] = { 170 };
/* Sewiaw Intewwupt Wine pin gwoup */
static const int sewiwq_pins[] = { 162 };

static const int cwkout_pins[] = { 160 };
static const int cwkweq_pins[] = { 231 };

static const int jtag2_pins[] = { 43, 44, 45, 46, 47 };
/* Gwaphics SPI Cwock pin gwoup */
static const int gspi_pins[] = { 12, 13, 14, 15 };

static const int spix_pins[] = { 224, 225, 226, 227, 229, 230 };
static const int spixcs1_pins[] = { 228 };

static const int pspi1_pins[] = { 175, 176, 177 };
static const int pspi2_pins[] = { 17, 18, 19 };

static const int spi0cs1_pins[] = { 32 };

static const int spi3_pins[] = { 183, 184, 185, 186 };
static const int spi3cs1_pins[] = { 187 };
static const int spi3quad_pins[] = { 188, 189 };
static const int spi3cs2_pins[] = { 188 };
static const int spi3cs3_pins[] = { 189 };

static const int ddc_pins[] = { 204, 205, 206, 207 };

static const int wpc_pins[] = { 95, 161, 163, 164, 165, 166, 167 };
static const int wpccwk_pins[] = { 168 };
static const int espi_pins[] = { 95, 161, 163, 164, 165, 166, 167, 168 };

static const int wkgpo0_pins[] = { 16 };
static const int wkgpo1_pins[] = { 8 };
static const int wkgpo2_pins[] = { 9 };

static const int npwd_smi_pins[] = { 190 };

/*
 * pin:	     name, numbew
 * gwoup:    name, npins,   pins
 * function: name, ngwoups, gwoups
 */
stwuct npcm7xx_gwoup {
	const chaw *name;
	const unsigned int *pins;
	int npins;
};

#define NPCM7XX_GWPS \
	NPCM7XX_GWP(smb0), \
	NPCM7XX_GWP(smb0b), \
	NPCM7XX_GWP(smb0c), \
	NPCM7XX_GWP(smb0d), \
	NPCM7XX_GWP(smb0den), \
	NPCM7XX_GWP(smb1), \
	NPCM7XX_GWP(smb1b), \
	NPCM7XX_GWP(smb1c), \
	NPCM7XX_GWP(smb1d), \
	NPCM7XX_GWP(smb2), \
	NPCM7XX_GWP(smb2b), \
	NPCM7XX_GWP(smb2c), \
	NPCM7XX_GWP(smb2d), \
	NPCM7XX_GWP(smb3), \
	NPCM7XX_GWP(smb3b), \
	NPCM7XX_GWP(smb3c), \
	NPCM7XX_GWP(smb3d), \
	NPCM7XX_GWP(smb4), \
	NPCM7XX_GWP(smb4b), \
	NPCM7XX_GWP(smb4c), \
	NPCM7XX_GWP(smb4d), \
	NPCM7XX_GWP(smb4den), \
	NPCM7XX_GWP(smb5), \
	NPCM7XX_GWP(smb5b), \
	NPCM7XX_GWP(smb5c), \
	NPCM7XX_GWP(smb5d), \
	NPCM7XX_GWP(ga20kbc), \
	NPCM7XX_GWP(smb6), \
	NPCM7XX_GWP(smb7), \
	NPCM7XX_GWP(smb8), \
	NPCM7XX_GWP(smb9), \
	NPCM7XX_GWP(smb10), \
	NPCM7XX_GWP(smb11), \
	NPCM7XX_GWP(smb12), \
	NPCM7XX_GWP(smb13), \
	NPCM7XX_GWP(smb14), \
	NPCM7XX_GWP(smb15), \
	NPCM7XX_GWP(fanin0), \
	NPCM7XX_GWP(fanin1), \
	NPCM7XX_GWP(fanin2), \
	NPCM7XX_GWP(fanin3), \
	NPCM7XX_GWP(fanin4), \
	NPCM7XX_GWP(fanin5), \
	NPCM7XX_GWP(fanin6), \
	NPCM7XX_GWP(fanin7), \
	NPCM7XX_GWP(fanin8), \
	NPCM7XX_GWP(fanin9), \
	NPCM7XX_GWP(fanin10), \
	NPCM7XX_GWP(fanin11), \
	NPCM7XX_GWP(fanin12), \
	NPCM7XX_GWP(fanin13), \
	NPCM7XX_GWP(fanin14), \
	NPCM7XX_GWP(fanin15), \
	NPCM7XX_GWP(faninx), \
	NPCM7XX_GWP(pwm0), \
	NPCM7XX_GWP(pwm1), \
	NPCM7XX_GWP(pwm2), \
	NPCM7XX_GWP(pwm3), \
	NPCM7XX_GWP(pwm4), \
	NPCM7XX_GWP(pwm5), \
	NPCM7XX_GWP(pwm6), \
	NPCM7XX_GWP(pwm7), \
	NPCM7XX_GWP(wg1), \
	NPCM7XX_GWP(wg1mdio), \
	NPCM7XX_GWP(wg2), \
	NPCM7XX_GWP(wg2mdio), \
	NPCM7XX_GWP(ddw), \
	NPCM7XX_GWP(uawt1), \
	NPCM7XX_GWP(uawt2), \
	NPCM7XX_GWP(bmcuawt0a), \
	NPCM7XX_GWP(bmcuawt0b), \
	NPCM7XX_GWP(bmcuawt1), \
	NPCM7XX_GWP(iox1), \
	NPCM7XX_GWP(iox2), \
	NPCM7XX_GWP(ioxh), \
	NPCM7XX_GWP(gspi), \
	NPCM7XX_GWP(mmc), \
	NPCM7XX_GWP(mmcwp), \
	NPCM7XX_GWP(mmccd), \
	NPCM7XX_GWP(mmcwst), \
	NPCM7XX_GWP(mmc8), \
	NPCM7XX_GWP(w1), \
	NPCM7XX_GWP(w1eww), \
	NPCM7XX_GWP(w1md), \
	NPCM7XX_GWP(w2), \
	NPCM7XX_GWP(w2eww), \
	NPCM7XX_GWP(w2md), \
	NPCM7XX_GWP(sd1), \
	NPCM7XX_GWP(sd1pww), \
	NPCM7XX_GWP(wdog1), \
	NPCM7XX_GWP(wdog2), \
	NPCM7XX_GWP(scipme), \
	NPCM7XX_GWP(sci), \
	NPCM7XX_GWP(sewiwq), \
	NPCM7XX_GWP(jtag2), \
	NPCM7XX_GWP(spix), \
	NPCM7XX_GWP(spixcs1), \
	NPCM7XX_GWP(pspi1), \
	NPCM7XX_GWP(pspi2), \
	NPCM7XX_GWP(ddc), \
	NPCM7XX_GWP(cwkweq), \
	NPCM7XX_GWP(cwkout), \
	NPCM7XX_GWP(spi3), \
	NPCM7XX_GWP(spi3cs1), \
	NPCM7XX_GWP(spi3quad), \
	NPCM7XX_GWP(spi3cs2), \
	NPCM7XX_GWP(spi3cs3), \
	NPCM7XX_GWP(spi0cs1), \
	NPCM7XX_GWP(wpc), \
	NPCM7XX_GWP(wpccwk), \
	NPCM7XX_GWP(espi), \
	NPCM7XX_GWP(wkgpo0), \
	NPCM7XX_GWP(wkgpo1), \
	NPCM7XX_GWP(wkgpo2), \
	NPCM7XX_GWP(npwd_smi), \
	\

enum {
#define NPCM7XX_GWP(x) fn_ ## x
	NPCM7XX_GWPS
	/* add pwacehowdew fow none/gpio */
	NPCM7XX_GWP(none),
	NPCM7XX_GWP(gpio),
#undef NPCM7XX_GWP
};

static stwuct npcm7xx_gwoup npcm7xx_gwoups[] = {
#define NPCM7XX_GWP(x) { .name = #x, .pins = x ## _pins, \
			.npins = AWWAY_SIZE(x ## _pins) }
	NPCM7XX_GWPS
#undef NPCM7XX_GWP
};

#define NPCM7XX_SFUNC(a) NPCM7XX_FUNC(a, #a)
#define NPCM7XX_FUNC(a, b...) static const chaw *a ## _gwp[] = { b }
#define NPCM7XX_MKFUNC(nm) { .name = #nm, .ngwoups = AWWAY_SIZE(nm ## _gwp), \
			.gwoups = nm ## _gwp }
stwuct npcm7xx_func {
	const chaw *name;
	const unsigned int ngwoups;
	const chaw *const *gwoups;
};

NPCM7XX_SFUNC(smb0);
NPCM7XX_SFUNC(smb0b);
NPCM7XX_SFUNC(smb0c);
NPCM7XX_SFUNC(smb0d);
NPCM7XX_SFUNC(smb0den);
NPCM7XX_SFUNC(smb1);
NPCM7XX_SFUNC(smb1b);
NPCM7XX_SFUNC(smb1c);
NPCM7XX_SFUNC(smb1d);
NPCM7XX_SFUNC(smb2);
NPCM7XX_SFUNC(smb2b);
NPCM7XX_SFUNC(smb2c);
NPCM7XX_SFUNC(smb2d);
NPCM7XX_SFUNC(smb3);
NPCM7XX_SFUNC(smb3b);
NPCM7XX_SFUNC(smb3c);
NPCM7XX_SFUNC(smb3d);
NPCM7XX_SFUNC(smb4);
NPCM7XX_SFUNC(smb4b);
NPCM7XX_SFUNC(smb4c);
NPCM7XX_SFUNC(smb4d);
NPCM7XX_SFUNC(smb4den);
NPCM7XX_SFUNC(smb5);
NPCM7XX_SFUNC(smb5b);
NPCM7XX_SFUNC(smb5c);
NPCM7XX_SFUNC(smb5d);
NPCM7XX_SFUNC(ga20kbc);
NPCM7XX_SFUNC(smb6);
NPCM7XX_SFUNC(smb7);
NPCM7XX_SFUNC(smb8);
NPCM7XX_SFUNC(smb9);
NPCM7XX_SFUNC(smb10);
NPCM7XX_SFUNC(smb11);
NPCM7XX_SFUNC(smb12);
NPCM7XX_SFUNC(smb13);
NPCM7XX_SFUNC(smb14);
NPCM7XX_SFUNC(smb15);
NPCM7XX_SFUNC(fanin0);
NPCM7XX_SFUNC(fanin1);
NPCM7XX_SFUNC(fanin2);
NPCM7XX_SFUNC(fanin3);
NPCM7XX_SFUNC(fanin4);
NPCM7XX_SFUNC(fanin5);
NPCM7XX_SFUNC(fanin6);
NPCM7XX_SFUNC(fanin7);
NPCM7XX_SFUNC(fanin8);
NPCM7XX_SFUNC(fanin9);
NPCM7XX_SFUNC(fanin10);
NPCM7XX_SFUNC(fanin11);
NPCM7XX_SFUNC(fanin12);
NPCM7XX_SFUNC(fanin13);
NPCM7XX_SFUNC(fanin14);
NPCM7XX_SFUNC(fanin15);
NPCM7XX_SFUNC(faninx);
NPCM7XX_SFUNC(pwm0);
NPCM7XX_SFUNC(pwm1);
NPCM7XX_SFUNC(pwm2);
NPCM7XX_SFUNC(pwm3);
NPCM7XX_SFUNC(pwm4);
NPCM7XX_SFUNC(pwm5);
NPCM7XX_SFUNC(pwm6);
NPCM7XX_SFUNC(pwm7);
NPCM7XX_SFUNC(wg1);
NPCM7XX_SFUNC(wg1mdio);
NPCM7XX_SFUNC(wg2);
NPCM7XX_SFUNC(wg2mdio);
NPCM7XX_SFUNC(ddw);
NPCM7XX_SFUNC(uawt1);
NPCM7XX_SFUNC(uawt2);
NPCM7XX_SFUNC(bmcuawt0a);
NPCM7XX_SFUNC(bmcuawt0b);
NPCM7XX_SFUNC(bmcuawt1);
NPCM7XX_SFUNC(iox1);
NPCM7XX_SFUNC(iox2);
NPCM7XX_SFUNC(ioxh);
NPCM7XX_SFUNC(gspi);
NPCM7XX_SFUNC(mmc);
NPCM7XX_SFUNC(mmcwp);
NPCM7XX_SFUNC(mmccd);
NPCM7XX_SFUNC(mmcwst);
NPCM7XX_SFUNC(mmc8);
NPCM7XX_SFUNC(w1);
NPCM7XX_SFUNC(w1eww);
NPCM7XX_SFUNC(w1md);
NPCM7XX_SFUNC(w2);
NPCM7XX_SFUNC(w2eww);
NPCM7XX_SFUNC(w2md);
NPCM7XX_SFUNC(sd1);
NPCM7XX_SFUNC(sd1pww);
NPCM7XX_SFUNC(wdog1);
NPCM7XX_SFUNC(wdog2);
NPCM7XX_SFUNC(scipme);
NPCM7XX_SFUNC(sci);
NPCM7XX_SFUNC(sewiwq);
NPCM7XX_SFUNC(jtag2);
NPCM7XX_SFUNC(spix);
NPCM7XX_SFUNC(spixcs1);
NPCM7XX_SFUNC(pspi1);
NPCM7XX_SFUNC(pspi2);
NPCM7XX_SFUNC(ddc);
NPCM7XX_SFUNC(cwkweq);
NPCM7XX_SFUNC(cwkout);
NPCM7XX_SFUNC(spi3);
NPCM7XX_SFUNC(spi3cs1);
NPCM7XX_SFUNC(spi3quad);
NPCM7XX_SFUNC(spi3cs2);
NPCM7XX_SFUNC(spi3cs3);
NPCM7XX_SFUNC(spi0cs1);
NPCM7XX_SFUNC(wpc);
NPCM7XX_SFUNC(wpccwk);
NPCM7XX_SFUNC(espi);
NPCM7XX_SFUNC(wkgpo0);
NPCM7XX_SFUNC(wkgpo1);
NPCM7XX_SFUNC(wkgpo2);
NPCM7XX_SFUNC(npwd_smi);

/* Function names */
static stwuct npcm7xx_func npcm7xx_funcs[] = {
	NPCM7XX_MKFUNC(smb0),
	NPCM7XX_MKFUNC(smb0b),
	NPCM7XX_MKFUNC(smb0c),
	NPCM7XX_MKFUNC(smb0d),
	NPCM7XX_MKFUNC(smb0den),
	NPCM7XX_MKFUNC(smb1),
	NPCM7XX_MKFUNC(smb1b),
	NPCM7XX_MKFUNC(smb1c),
	NPCM7XX_MKFUNC(smb1d),
	NPCM7XX_MKFUNC(smb2),
	NPCM7XX_MKFUNC(smb2b),
	NPCM7XX_MKFUNC(smb2c),
	NPCM7XX_MKFUNC(smb2d),
	NPCM7XX_MKFUNC(smb3),
	NPCM7XX_MKFUNC(smb3b),
	NPCM7XX_MKFUNC(smb3c),
	NPCM7XX_MKFUNC(smb3d),
	NPCM7XX_MKFUNC(smb4),
	NPCM7XX_MKFUNC(smb4b),
	NPCM7XX_MKFUNC(smb4c),
	NPCM7XX_MKFUNC(smb4d),
	NPCM7XX_MKFUNC(smb4den),
	NPCM7XX_MKFUNC(smb5),
	NPCM7XX_MKFUNC(smb5b),
	NPCM7XX_MKFUNC(smb5c),
	NPCM7XX_MKFUNC(smb5d),
	NPCM7XX_MKFUNC(ga20kbc),
	NPCM7XX_MKFUNC(smb6),
	NPCM7XX_MKFUNC(smb7),
	NPCM7XX_MKFUNC(smb8),
	NPCM7XX_MKFUNC(smb9),
	NPCM7XX_MKFUNC(smb10),
	NPCM7XX_MKFUNC(smb11),
	NPCM7XX_MKFUNC(smb12),
	NPCM7XX_MKFUNC(smb13),
	NPCM7XX_MKFUNC(smb14),
	NPCM7XX_MKFUNC(smb15),
	NPCM7XX_MKFUNC(fanin0),
	NPCM7XX_MKFUNC(fanin1),
	NPCM7XX_MKFUNC(fanin2),
	NPCM7XX_MKFUNC(fanin3),
	NPCM7XX_MKFUNC(fanin4),
	NPCM7XX_MKFUNC(fanin5),
	NPCM7XX_MKFUNC(fanin6),
	NPCM7XX_MKFUNC(fanin7),
	NPCM7XX_MKFUNC(fanin8),
	NPCM7XX_MKFUNC(fanin9),
	NPCM7XX_MKFUNC(fanin10),
	NPCM7XX_MKFUNC(fanin11),
	NPCM7XX_MKFUNC(fanin12),
	NPCM7XX_MKFUNC(fanin13),
	NPCM7XX_MKFUNC(fanin14),
	NPCM7XX_MKFUNC(fanin15),
	NPCM7XX_MKFUNC(faninx),
	NPCM7XX_MKFUNC(pwm0),
	NPCM7XX_MKFUNC(pwm1),
	NPCM7XX_MKFUNC(pwm2),
	NPCM7XX_MKFUNC(pwm3),
	NPCM7XX_MKFUNC(pwm4),
	NPCM7XX_MKFUNC(pwm5),
	NPCM7XX_MKFUNC(pwm6),
	NPCM7XX_MKFUNC(pwm7),
	NPCM7XX_MKFUNC(wg1),
	NPCM7XX_MKFUNC(wg1mdio),
	NPCM7XX_MKFUNC(wg2),
	NPCM7XX_MKFUNC(wg2mdio),
	NPCM7XX_MKFUNC(ddw),
	NPCM7XX_MKFUNC(uawt1),
	NPCM7XX_MKFUNC(uawt2),
	NPCM7XX_MKFUNC(bmcuawt0a),
	NPCM7XX_MKFUNC(bmcuawt0b),
	NPCM7XX_MKFUNC(bmcuawt1),
	NPCM7XX_MKFUNC(iox1),
	NPCM7XX_MKFUNC(iox2),
	NPCM7XX_MKFUNC(ioxh),
	NPCM7XX_MKFUNC(gspi),
	NPCM7XX_MKFUNC(mmc),
	NPCM7XX_MKFUNC(mmcwp),
	NPCM7XX_MKFUNC(mmccd),
	NPCM7XX_MKFUNC(mmcwst),
	NPCM7XX_MKFUNC(mmc8),
	NPCM7XX_MKFUNC(w1),
	NPCM7XX_MKFUNC(w1eww),
	NPCM7XX_MKFUNC(w1md),
	NPCM7XX_MKFUNC(w2),
	NPCM7XX_MKFUNC(w2eww),
	NPCM7XX_MKFUNC(w2md),
	NPCM7XX_MKFUNC(sd1),
	NPCM7XX_MKFUNC(sd1pww),
	NPCM7XX_MKFUNC(wdog1),
	NPCM7XX_MKFUNC(wdog2),
	NPCM7XX_MKFUNC(scipme),
	NPCM7XX_MKFUNC(sci),
	NPCM7XX_MKFUNC(sewiwq),
	NPCM7XX_MKFUNC(jtag2),
	NPCM7XX_MKFUNC(spix),
	NPCM7XX_MKFUNC(spixcs1),
	NPCM7XX_MKFUNC(pspi1),
	NPCM7XX_MKFUNC(pspi2),
	NPCM7XX_MKFUNC(ddc),
	NPCM7XX_MKFUNC(cwkweq),
	NPCM7XX_MKFUNC(cwkout),
	NPCM7XX_MKFUNC(spi3),
	NPCM7XX_MKFUNC(spi3cs1),
	NPCM7XX_MKFUNC(spi3quad),
	NPCM7XX_MKFUNC(spi3cs2),
	NPCM7XX_MKFUNC(spi3cs3),
	NPCM7XX_MKFUNC(spi0cs1),
	NPCM7XX_MKFUNC(wpc),
	NPCM7XX_MKFUNC(wpccwk),
	NPCM7XX_MKFUNC(espi),
	NPCM7XX_MKFUNC(wkgpo0),
	NPCM7XX_MKFUNC(wkgpo1),
	NPCM7XX_MKFUNC(wkgpo2),
	NPCM7XX_MKFUNC(npwd_smi),
};

#define NPCM7XX_PINCFG(a, b, c, d, e, f, g, h, i, j, k) \
	[a] = { .fn0 = fn_ ## b, .weg0 = NPCM7XX_GCW_ ## c, .bit0 = d, \
			.fn1 = fn_ ## e, .weg1 = NPCM7XX_GCW_ ## f, .bit1 = g, \
			.fn2 = fn_ ## h, .weg2 = NPCM7XX_GCW_ ## i, .bit2 = j, \
			.fwag = k }

/* Dwive stwength contwowwed by NPCM7XX_GP_N_ODSC */
#define DWIVE_STWENGTH_WO_SHIFT		8
#define DWIVE_STWENGTH_HI_SHIFT		12
#define DWIVE_STWENGTH_MASK		0x0000FF00

#define DSTW(wo, hi)	(((wo) << DWIVE_STWENGTH_WO_SHIFT) | \
			 ((hi) << DWIVE_STWENGTH_HI_SHIFT))
#define DSWO(x)		(((x) >> DWIVE_STWENGTH_WO_SHIFT) & 0xF)
#define DSHI(x)		(((x) >> DWIVE_STWENGTH_HI_SHIFT) & 0xF)

#define GPI		0x1 /* Not GPO */
#define GPO		0x2 /* Not GPI */
#define SWEW		0x4 /* Has Swew Contwow, NPCM7XX_GP_N_OSWC */
#define SWEWWPC		0x8 /* Has Swew Contwow, SWCNT.3 */

stwuct npcm7xx_pincfg {
	int fwag;
	int fn0, weg0, bit0;
	int fn1, weg1, bit1;
	int fn2, weg2, bit2;
};

static const stwuct npcm7xx_pincfg pincfg[] = {
	/*		PIN	  FUNCTION 1		   FUNCTION 2		  FUNCTION 3	    FWAGS */
	NPCM7XX_PINCFG(0,	 iox1, MFSEW1, 30,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(1,	 iox1, MFSEW1, 30,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12)),
	NPCM7XX_PINCFG(2,	 iox1, MFSEW1, 30,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12)),
	NPCM7XX_PINCFG(3,	 iox1, MFSEW1, 30,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(4,	 iox2, MFSEW3, 14,	 smb1d, I2CSEGSEW, 7,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(5,	 iox2, MFSEW3, 14,	 smb1d, I2CSEGSEW, 7,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(6,	 iox2, MFSEW3, 14,	 smb2d, I2CSEGSEW, 10,  none, NONE, 0,       SWEW),
	NPCM7XX_PINCFG(7,	 iox2, MFSEW3, 14,	 smb2d, I2CSEGSEW, 10,  none, NONE, 0,       SWEW),
	NPCM7XX_PINCFG(8,      wkgpo1, FWOCKW1, 4,        none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12)),
	NPCM7XX_PINCFG(9,      wkgpo2, FWOCKW1, 8,        none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12)),
	NPCM7XX_PINCFG(10,	 ioxh, MFSEW3, 18,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12)),
	NPCM7XX_PINCFG(11,	 ioxh, MFSEW3, 18,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12)),
	NPCM7XX_PINCFG(12,	 gspi, MFSEW1, 24,	 smb5b, I2CSEGSEW, 19,  none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(13,	 gspi, MFSEW1, 24,	 smb5b, I2CSEGSEW, 19,  none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(14,	 gspi, MFSEW1, 24,	 smb5c, I2CSEGSEW, 20,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(15,	 gspi, MFSEW1, 24,	 smb5c, I2CSEGSEW, 20,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(16,     wkgpo0, FWOCKW1, 0,        none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12)),
	NPCM7XX_PINCFG(17,      pspi2, MFSEW3, 13,     smb4den, I2CSEGSEW, 23,  none, NONE, 0,       DSTW(8, 12)),
	NPCM7XX_PINCFG(18,      pspi2, MFSEW3, 13,	 smb4b, I2CSEGSEW, 14,  none, NONE, 0,	     DSTW(8, 12)),
	NPCM7XX_PINCFG(19,      pspi2, MFSEW3, 13,	 smb4b, I2CSEGSEW, 14,  none, NONE, 0,	     DSTW(8, 12)),
	NPCM7XX_PINCFG(20,	smb4c, I2CSEGSEW, 15,    smb15, MFSEW3, 8,      none, NONE, 0,	     0),
	NPCM7XX_PINCFG(21,	smb4c, I2CSEGSEW, 15,    smb15, MFSEW3, 8,      none, NONE, 0,	     0),
	NPCM7XX_PINCFG(22,      smb4d, I2CSEGSEW, 16,	 smb14, MFSEW3, 7,      none, NONE, 0,	     0),
	NPCM7XX_PINCFG(23,      smb4d, I2CSEGSEW, 16,	 smb14, MFSEW3, 7,      none, NONE, 0,	     0),
	NPCM7XX_PINCFG(24,	 ioxh, MFSEW3, 18,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12)),
	NPCM7XX_PINCFG(25,	 ioxh, MFSEW3, 18,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12)),
	NPCM7XX_PINCFG(26,	 smb5, MFSEW1, 2,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(27,	 smb5, MFSEW1, 2,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(28,	 smb4, MFSEW1, 1,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(29,	 smb4, MFSEW1, 1,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(30,	 smb3, MFSEW1, 0,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(31,	 smb3, MFSEW1, 0,	  none, NONE, 0,	none, NONE, 0,	     0),

	NPCM7XX_PINCFG(32,    spi0cs1, MFSEW1, 3,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(33,	 none, NONE, 0,           none, NONE, 0,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(34,	 none, NONE, 0,           none, NONE, 0,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(37,	smb3c, I2CSEGSEW, 12,	  none, NONE, 0,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(38,	smb3c, I2CSEGSEW, 12,	  none, NONE, 0,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(39,	smb3b, I2CSEGSEW, 11,	  none, NONE, 0,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(40,	smb3b, I2CSEGSEW, 11,	  none, NONE, 0,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(41,  bmcuawt0a, MFSEW1, 9,         none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(42,  bmcuawt0a, MFSEW1, 9,         none, NONE, 0,	none, NONE, 0,	     DSTW(2, 4) | GPO),
	NPCM7XX_PINCFG(43,      uawt1, MFSEW1, 10,	 jtag2, MFSEW4, 0,  bmcuawt1, MFSEW3, 24,    0),
	NPCM7XX_PINCFG(44,      uawt1, MFSEW1, 10,	 jtag2, MFSEW4, 0,  bmcuawt1, MFSEW3, 24,    0),
	NPCM7XX_PINCFG(45,      uawt1, MFSEW1, 10,	 jtag2, MFSEW4, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(46,      uawt1, MFSEW1, 10,	 jtag2, MFSEW4, 0,	none, NONE, 0,	     DSTW(2, 8)),
	NPCM7XX_PINCFG(47,      uawt1, MFSEW1, 10,	 jtag2, MFSEW4, 0,	none, NONE, 0,	     DSTW(2, 8)),
	NPCM7XX_PINCFG(48,	uawt2, MFSEW1, 11,   bmcuawt0b, MFSEW4, 1,      none, NONE, 0,	     GPO),
	NPCM7XX_PINCFG(49,	uawt2, MFSEW1, 11,   bmcuawt0b, MFSEW4, 1,      none, NONE, 0,	     0),
	NPCM7XX_PINCFG(50,	uawt2, MFSEW1, 11,	  none, NONE, 0,        none, NONE, 0,	     0),
	NPCM7XX_PINCFG(51,	uawt2, MFSEW1, 11,	  none, NONE, 0,        none, NONE, 0,	     GPO),
	NPCM7XX_PINCFG(52,	uawt2, MFSEW1, 11,	  none, NONE, 0,        none, NONE, 0,	     0),
	NPCM7XX_PINCFG(53,	uawt2, MFSEW1, 11,	  none, NONE, 0,        none, NONE, 0,	     GPO),
	NPCM7XX_PINCFG(54,	uawt2, MFSEW1, 11,	  none, NONE, 0,        none, NONE, 0,	     0),
	NPCM7XX_PINCFG(55,	uawt2, MFSEW1, 11,	  none, NONE, 0,        none, NONE, 0,	     0),
	NPCM7XX_PINCFG(56,	w1eww, MFSEW1, 12,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(57,       w1md, MFSEW1, 13,        none, NONE, 0,        none, NONE, 0,       DSTW(2, 4)),
	NPCM7XX_PINCFG(58,       w1md, MFSEW1, 13,        none, NONE, 0,	none, NONE, 0,	     DSTW(2, 4)),
	NPCM7XX_PINCFG(59,	smb3d, I2CSEGSEW, 13,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(60,	smb3d, I2CSEGSEW, 13,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(61,      uawt1, MFSEW1, 10,	  none, NONE, 0,	none, NONE, 0,     GPO),
	NPCM7XX_PINCFG(62,      uawt1, MFSEW1, 10,    bmcuawt1, MFSEW3, 24,	none, NONE, 0,     GPO),
	NPCM7XX_PINCFG(63,      uawt1, MFSEW1, 10,    bmcuawt1, MFSEW3, 24,	none, NONE, 0,     GPO),

	NPCM7XX_PINCFG(64,    fanin0, MFSEW2, 0,          none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(65,    fanin1, MFSEW2, 1,          none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(66,    fanin2, MFSEW2, 2,          none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(67,    fanin3, MFSEW2, 3,          none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(68,    fanin4, MFSEW2, 4,          none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(69,    fanin5, MFSEW2, 5,          none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(70,    fanin6, MFSEW2, 6,          none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(71,    fanin7, MFSEW2, 7,          none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(72,    fanin8, MFSEW2, 8,          none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(73,    fanin9, MFSEW2, 9,          none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(74,    fanin10, MFSEW2, 10,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(75,    fanin11, MFSEW2, 11,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(76,    fanin12, MFSEW2, 12,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(77,    fanin13, MFSEW2, 13,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(78,    fanin14, MFSEW2, 14,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(79,    fanin15, MFSEW2, 15,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(80,	 pwm0, MFSEW2, 16,        none, NONE, 0,	none, NONE, 0,	     DSTW(4, 8)),
	NPCM7XX_PINCFG(81,	 pwm1, MFSEW2, 17,        none, NONE, 0,	none, NONE, 0,	     DSTW(4, 8)),
	NPCM7XX_PINCFG(82,	 pwm2, MFSEW2, 18,        none, NONE, 0,	none, NONE, 0,	     DSTW(4, 8)),
	NPCM7XX_PINCFG(83,	 pwm3, MFSEW2, 19,        none, NONE, 0,	none, NONE, 0,	     DSTW(4, 8)),
	NPCM7XX_PINCFG(84,         w2, MFSEW1, 14,        none, NONE, 0,        none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(85,         w2, MFSEW1, 14,        none, NONE, 0,        none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(86,         w2, MFSEW1, 14,        none, NONE, 0,        none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(87,         w2, MFSEW1, 14,        none, NONE, 0,        none, NONE, 0,	     0),
	NPCM7XX_PINCFG(88,         w2, MFSEW1, 14,        none, NONE, 0,        none, NONE, 0,	     0),
	NPCM7XX_PINCFG(89,         w2, MFSEW1, 14,        none, NONE, 0,        none, NONE, 0,	     0),
	NPCM7XX_PINCFG(90,      w2eww, MFSEW1, 15,        none, NONE, 0,        none, NONE, 0,       0),
	NPCM7XX_PINCFG(91,       w2md, MFSEW1, 16,	  none, NONE, 0,        none, NONE, 0,	     DSTW(2, 4)),
	NPCM7XX_PINCFG(92,       w2md, MFSEW1, 16,	  none, NONE, 0,        none, NONE, 0,	     DSTW(2, 4)),
	NPCM7XX_PINCFG(93,    ga20kbc, MFSEW1, 17,	 smb5d, I2CSEGSEW, 21,  none, NONE, 0,	     0),
	NPCM7XX_PINCFG(94,    ga20kbc, MFSEW1, 17,	 smb5d, I2CSEGSEW, 21,  none, NONE, 0,	     0),
	NPCM7XX_PINCFG(95,	  wpc, NONE, 0,		  espi, MFSEW4, 8,      gpio, MFSEW1, 26,    0),

	NPCM7XX_PINCFG(96,	  wg1, MFSEW4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(97,	  wg1, MFSEW4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(98,	  wg1, MFSEW4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(99,	  wg1, MFSEW4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(100,	  wg1, MFSEW4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(101,	  wg1, MFSEW4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(102,	  wg1, MFSEW4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(103,	  wg1, MFSEW4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(104,	  wg1, MFSEW4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(105,	  wg1, MFSEW4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(106,	  wg1, MFSEW4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(107,	  wg1, MFSEW4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(108,   wg1mdio, MFSEW4, 21,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(109,   wg1mdio, MFSEW4, 21,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(110,       wg2, MFSEW4, 24,         ddw, MFSEW3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(111,       wg2, MFSEW4, 24,         ddw, MFSEW3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(112,       wg2, MFSEW4, 24,         ddw, MFSEW3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(113,       wg2, MFSEW4, 24,         ddw, MFSEW3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(114,	 smb0, MFSEW1, 6,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(115,	 smb0, MFSEW1, 6,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(116,	 smb1, MFSEW1, 7,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(117,	 smb1, MFSEW1, 7,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(118,	 smb2, MFSEW1, 8,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(119,	 smb2, MFSEW1, 8,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(120,	smb2c, I2CSEGSEW, 9,	  none, NONE, 0,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(121,	smb2c, I2CSEGSEW, 9,      none, NONE, 0,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(122,	smb2b, I2CSEGSEW, 8,	  none, NONE, 0,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(123,	smb2b, I2CSEGSEW, 8,	  none, NONE, 0,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(124,	smb1c, I2CSEGSEW, 6,	  none, NONE, 0,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(125,	smb1c, I2CSEGSEW, 6,	  none, NONE, 0,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(126,	smb1b, I2CSEGSEW, 5,	  none, NONE, 0,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(127,	smb1b, I2CSEGSEW, 5,	  none, NONE, 0,	none, NONE, 0,	     SWEW),

	NPCM7XX_PINCFG(128,	 smb8, MFSEW4, 11,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(129,	 smb8, MFSEW4, 11,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(130,	 smb9, MFSEW4, 12,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(131,	 smb9, MFSEW4, 12,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(132,	smb10, MFSEW4, 13,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(133,	smb10, MFSEW4, 13,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(134,	smb11, MFSEW4, 14,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(135,	smb11, MFSEW4, 14,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(136,	  sd1, MFSEW3, 12,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(137,	  sd1, MFSEW3, 12,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(138,	  sd1, MFSEW3, 12,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(139,	  sd1, MFSEW3, 12,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(140,	  sd1, MFSEW3, 12,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(141,	  sd1, MFSEW3, 12,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(142,	  sd1, MFSEW3, 12,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(143,       sd1, MFSEW3, 12,      sd1pww, MFSEW4, 5,      none, NONE, 0,       0),
	NPCM7XX_PINCFG(144,	 pwm4, MFSEW2, 20,	  none, NONE, 0,	none, NONE, 0,	     DSTW(4, 8)),
	NPCM7XX_PINCFG(145,	 pwm5, MFSEW2, 21,	  none, NONE, 0,	none, NONE, 0,	     DSTW(4, 8)),
	NPCM7XX_PINCFG(146,	 pwm6, MFSEW2, 22,	  none, NONE, 0,	none, NONE, 0,	     DSTW(4, 8)),
	NPCM7XX_PINCFG(147,	 pwm7, MFSEW2, 23,	  none, NONE, 0,	none, NONE, 0,	     DSTW(4, 8)),
	NPCM7XX_PINCFG(148,	 mmc8, MFSEW3, 11,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(149,	 mmc8, MFSEW3, 11,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(150,	 mmc8, MFSEW3, 11,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(151,	 mmc8, MFSEW3, 11,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(152,	  mmc, MFSEW3, 10,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(153,     mmcwp, FWOCKW1, 24,       none, NONE, 0,	none, NONE, 0,	     0),  /* Z1/A1 */
	NPCM7XX_PINCFG(154,	  mmc, MFSEW3, 10,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(155,     mmccd, MFSEW3, 25,      mmcwst, MFSEW4, 6,      none, NONE, 0,       0),  /* Z1/A1 */
	NPCM7XX_PINCFG(156,	  mmc, MFSEW3, 10,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(157,	  mmc, MFSEW3, 10,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(158,	  mmc, MFSEW3, 10,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(159,	  mmc, MFSEW3, 10,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),

	NPCM7XX_PINCFG(160,    cwkout, MFSEW1, 21,        none, NONE, 0,        none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(161,	  wpc, NONE, 0,		  espi, MFSEW4, 8,      gpio, MFSEW1, 26,    DSTW(8, 12)),
	NPCM7XX_PINCFG(162,    sewiwq, NONE, 0,           gpio, MFSEW1, 31,	none, NONE, 0,	     DSTW(8, 12)),
	NPCM7XX_PINCFG(163,	  wpc, NONE, 0,		  espi, MFSEW4, 8,      gpio, MFSEW1, 26,    0),
	NPCM7XX_PINCFG(164,	  wpc, NONE, 0,		  espi, MFSEW4, 8,      gpio, MFSEW1, 26,    SWEWWPC),
	NPCM7XX_PINCFG(165,	  wpc, NONE, 0,		  espi, MFSEW4, 8,      gpio, MFSEW1, 26,    SWEWWPC),
	NPCM7XX_PINCFG(166,	  wpc, NONE, 0,		  espi, MFSEW4, 8,      gpio, MFSEW1, 26,    SWEWWPC),
	NPCM7XX_PINCFG(167,	  wpc, NONE, 0,		  espi, MFSEW4, 8,      gpio, MFSEW1, 26,    SWEWWPC),
	NPCM7XX_PINCFG(168,    wpccwk, NONE, 0,           espi, MFSEW4, 8,      gpio, MFSEW3, 16,    0),
	NPCM7XX_PINCFG(169,    scipme, MFSEW3, 0,         none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(170,	  sci, MFSEW1, 22,        none, NONE, 0,        none, NONE, 0,	     0),
	NPCM7XX_PINCFG(171,	 smb6, MFSEW3, 1,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(172,	 smb6, MFSEW3, 1,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(173,	 smb7, MFSEW3, 2,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(174,	 smb7, MFSEW3, 2,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(175,	pspi1, MFSEW3, 4,       faninx, MFSEW3, 3,      none, NONE, 0,	     DSTW(8, 12)),
	NPCM7XX_PINCFG(176,     pspi1, MFSEW3, 4,       faninx, MFSEW3, 3,      none, NONE, 0,	     DSTW(8, 12)),
	NPCM7XX_PINCFG(177,     pspi1, MFSEW3, 4,       faninx, MFSEW3, 3,      none, NONE, 0,	     DSTW(8, 12)),
	NPCM7XX_PINCFG(178,	   w1, MFSEW3, 9,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(179,	   w1, MFSEW3, 9,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(180,	   w1, MFSEW3, 9,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(181,	   w1, MFSEW3, 9,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(182,	   w1, MFSEW3, 9,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(183,     spi3, MFSEW4, 16,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(184,     spi3, MFSEW4, 16,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW | GPO),
	NPCM7XX_PINCFG(185,     spi3, MFSEW4, 16,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW | GPO),
	NPCM7XX_PINCFG(186,     spi3, MFSEW4, 16,	  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12)),
	NPCM7XX_PINCFG(187,   spi3cs1, MFSEW4, 17,        none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12)),
	NPCM7XX_PINCFG(188,  spi3quad, MFSEW4, 20,     spi3cs2, MFSEW4, 18,     none, NONE, 0,    DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(189,  spi3quad, MFSEW4, 20,     spi3cs3, MFSEW4, 19,     none, NONE, 0,    DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(190,      gpio, FWOCKW1, 20,   npwd_smi, NONE, 0,	none, NONE, 0,	     DSTW(2, 4)),
	NPCM7XX_PINCFG(191,	 none, NONE, 0,		  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12)),  /* XX */

	NPCM7XX_PINCFG(192,	 none, NONE, 0,		  none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12)),  /* XX */
	NPCM7XX_PINCFG(193,	   w1, MFSEW3, 9,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(194,	smb0b, I2CSEGSEW, 0,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(195,	smb0b, I2CSEGSEW, 0,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(196,	smb0c, I2CSEGSEW, 1,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(197,   smb0den, I2CSEGSEW, 22,     none, NONE, 0,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(198,	smb0d, I2CSEGSEW, 2,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(199,	smb0d, I2CSEGSEW, 2,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(200,        w2, MFSEW1, 14,        none, NONE, 0,        none, NONE, 0,       0),
	NPCM7XX_PINCFG(201,	   w1, MFSEW3, 9,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(202,	smb0c, I2CSEGSEW, 1,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(203,    faninx, MFSEW3, 3,         none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12)),
	NPCM7XX_PINCFG(204,	  ddc, NONE, 0,           gpio, MFSEW3, 22,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(205,	  ddc, NONE, 0,           gpio, MFSEW3, 22,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(206,	  ddc, NONE, 0,           gpio, MFSEW3, 22,	none, NONE, 0,	     DSTW(4, 8)),
	NPCM7XX_PINCFG(207,	  ddc, NONE, 0,           gpio, MFSEW3, 22,	none, NONE, 0,	     DSTW(4, 8)),
	NPCM7XX_PINCFG(208,       wg2, MFSEW4, 24,         ddw, MFSEW3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(209,       wg2, MFSEW4, 24,         ddw, MFSEW3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(210,       wg2, MFSEW4, 24,         ddw, MFSEW3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(211,       wg2, MFSEW4, 24,         ddw, MFSEW3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(212,       wg2, MFSEW4, 24,         ddw, MFSEW3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(213,       wg2, MFSEW4, 24,         ddw, MFSEW3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(214,       wg2, MFSEW4, 24,         ddw, MFSEW3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(215,       wg2, MFSEW4, 24,         ddw, MFSEW3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(216,   wg2mdio, MFSEW4, 23,         ddw, MFSEW3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(217,   wg2mdio, MFSEW4, 23,         ddw, MFSEW3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(218,     wdog1, MFSEW3, 19,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(219,     wdog2, MFSEW3, 20,        none, NONE, 0,	none, NONE, 0,	     DSTW(4, 8)),
	NPCM7XX_PINCFG(220,	smb12, MFSEW3, 5,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(221,	smb12, MFSEW3, 5,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(222,     smb13, MFSEW3, 6,         none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(223,     smb13, MFSEW3, 6,         none, NONE, 0,	none, NONE, 0,	     0),

	NPCM7XX_PINCFG(224,	 spix, MFSEW4, 27,        none, NONE, 0,	none, NONE, 0,	     SWEW),
	NPCM7XX_PINCFG(225,	 spix, MFSEW4, 27,        none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW | GPO),
	NPCM7XX_PINCFG(226,	 spix, MFSEW4, 27,        none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW | GPO),
	NPCM7XX_PINCFG(227,	 spix, MFSEW4, 27,        none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(228,   spixcs1, MFSEW4, 28,        none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(229,	 spix, MFSEW4, 27,        none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(230,	 spix, MFSEW4, 27,        none, NONE, 0,	none, NONE, 0,	     DSTW(8, 12) | SWEW),
	NPCM7XX_PINCFG(231,    cwkweq, MFSEW4, 9,         none, NONE, 0,        none, NONE, 0,	     DSTW(8, 12)),
	NPCM7XX_PINCFG(253,	 none, NONE, 0,		  none, NONE, 0,	none, NONE, 0,	     GPI), /* SDHC1 powew */
	NPCM7XX_PINCFG(254,	 none, NONE, 0,		  none, NONE, 0,	none, NONE, 0,	     GPI), /* SDHC2 powew */
	NPCM7XX_PINCFG(255,	 none, NONE, 0,		  none, NONE, 0,	none, NONE, 0,	     GPI), /* DACOSEW */
};

/* numbew, name, dwv_data */
static const stwuct pinctww_pin_desc npcm7xx_pins[] = {
	PINCTWW_PIN(0,	"GPIO0/IOX1DI"),
	PINCTWW_PIN(1,	"GPIO1/IOX1WD"),
	PINCTWW_PIN(2,	"GPIO2/IOX1CK"),
	PINCTWW_PIN(3,	"GPIO3/IOX1D0"),
	PINCTWW_PIN(4,	"GPIO4/IOX2DI/SMB1DSDA"),
	PINCTWW_PIN(5,	"GPIO5/IOX2WD/SMB1DSCW"),
	PINCTWW_PIN(6,	"GPIO6/IOX2CK/SMB2DSDA"),
	PINCTWW_PIN(7,	"GPIO7/IOX2D0/SMB2DSCW"),
	PINCTWW_PIN(8,	"GPIO8/WKGPO1"),
	PINCTWW_PIN(9,	"GPIO9/WKGPO2"),
	PINCTWW_PIN(10, "GPIO10/IOXHWD"),
	PINCTWW_PIN(11, "GPIO11/IOXHCK"),
	PINCTWW_PIN(12, "GPIO12/GSPICK/SMB5BSCW"),
	PINCTWW_PIN(13, "GPIO13/GSPIDO/SMB5BSDA"),
	PINCTWW_PIN(14, "GPIO14/GSPIDI/SMB5CSCW"),
	PINCTWW_PIN(15, "GPIO15/GSPICS/SMB5CSDA"),
	PINCTWW_PIN(16, "GPIO16/WKGPO0"),
	PINCTWW_PIN(17, "GPIO17/PSPI2DI/SMB4DEN"),
	PINCTWW_PIN(18, "GPIO18/PSPI2D0/SMB4BSDA"),
	PINCTWW_PIN(19, "GPIO19/PSPI2CK/SMB4BSCW"),
	PINCTWW_PIN(20, "GPIO20/SMB4CSDA/SMB15SDA"),
	PINCTWW_PIN(21, "GPIO21/SMB4CSCW/SMB15SCW"),
	PINCTWW_PIN(22, "GPIO22/SMB4DSDA/SMB14SDA"),
	PINCTWW_PIN(23, "GPIO23/SMB4DSCW/SMB14SCW"),
	PINCTWW_PIN(24, "GPIO24/IOXHDO"),
	PINCTWW_PIN(25, "GPIO25/IOXHDI"),
	PINCTWW_PIN(26, "GPIO26/SMB5SDA"),
	PINCTWW_PIN(27, "GPIO27/SMB5SCW"),
	PINCTWW_PIN(28, "GPIO28/SMB4SDA"),
	PINCTWW_PIN(29, "GPIO29/SMB4SCW"),
	PINCTWW_PIN(30, "GPIO30/SMB3SDA"),
	PINCTWW_PIN(31, "GPIO31/SMB3SCW"),

	PINCTWW_PIN(32, "GPIO32/nSPI0CS1"),
	PINCTWW_PIN(33, "SPI0D2"),
	PINCTWW_PIN(34, "SPI0D3"),
	PINCTWW_PIN(37, "GPIO37/SMB3CSDA"),
	PINCTWW_PIN(38, "GPIO38/SMB3CSCW"),
	PINCTWW_PIN(39, "GPIO39/SMB3BSDA"),
	PINCTWW_PIN(40, "GPIO40/SMB3BSCW"),
	PINCTWW_PIN(41, "GPIO41/BSPWXD"),
	PINCTWW_PIN(42, "GPO42/BSPTXD/STWAP11"),
	PINCTWW_PIN(43, "GPIO43/WXD1/JTMS2/BU1WXD"),
	PINCTWW_PIN(44, "GPIO44/nCTS1/JTDI2/BU1CTS"),
	PINCTWW_PIN(45, "GPIO45/nDCD1/JTDO2"),
	PINCTWW_PIN(46, "GPIO46/nDSW1/JTCK2"),
	PINCTWW_PIN(47, "GPIO47/nWI1/JCP_WDY2"),
	PINCTWW_PIN(48, "GPIO48/TXD2/BSPTXD"),
	PINCTWW_PIN(49, "GPIO49/WXD2/BSPWXD"),
	PINCTWW_PIN(50, "GPIO50/nCTS2"),
	PINCTWW_PIN(51, "GPO51/nWTS2/STWAP2"),
	PINCTWW_PIN(52, "GPIO52/nDCD2"),
	PINCTWW_PIN(53, "GPO53/nDTW2_BOUT2/STWAP1"),
	PINCTWW_PIN(54, "GPIO54/nDSW2"),
	PINCTWW_PIN(55, "GPIO55/nWI2"),
	PINCTWW_PIN(56, "GPIO56/W1WXEWW"),
	PINCTWW_PIN(57, "GPIO57/W1MDC"),
	PINCTWW_PIN(58, "GPIO58/W1MDIO"),
	PINCTWW_PIN(59, "GPIO59/SMB3DSDA"),
	PINCTWW_PIN(60, "GPIO60/SMB3DSCW"),
	PINCTWW_PIN(61, "GPO61/nDTW1_BOUT1/STWAP6"),
	PINCTWW_PIN(62, "GPO62/nWTST1/STWAP5"),
	PINCTWW_PIN(63, "GPO63/TXD1/STWAP4"),

	PINCTWW_PIN(64, "GPIO64/FANIN0"),
	PINCTWW_PIN(65, "GPIO65/FANIN1"),
	PINCTWW_PIN(66, "GPIO66/FANIN2"),
	PINCTWW_PIN(67, "GPIO67/FANIN3"),
	PINCTWW_PIN(68, "GPIO68/FANIN4"),
	PINCTWW_PIN(69, "GPIO69/FANIN5"),
	PINCTWW_PIN(70, "GPIO70/FANIN6"),
	PINCTWW_PIN(71, "GPIO71/FANIN7"),
	PINCTWW_PIN(72, "GPIO72/FANIN8"),
	PINCTWW_PIN(73, "GPIO73/FANIN9"),
	PINCTWW_PIN(74, "GPIO74/FANIN10"),
	PINCTWW_PIN(75, "GPIO75/FANIN11"),
	PINCTWW_PIN(76, "GPIO76/FANIN12"),
	PINCTWW_PIN(77, "GPIO77/FANIN13"),
	PINCTWW_PIN(78, "GPIO78/FANIN14"),
	PINCTWW_PIN(79, "GPIO79/FANIN15"),
	PINCTWW_PIN(80, "GPIO80/PWM0"),
	PINCTWW_PIN(81, "GPIO81/PWM1"),
	PINCTWW_PIN(82, "GPIO82/PWM2"),
	PINCTWW_PIN(83, "GPIO83/PWM3"),
	PINCTWW_PIN(84, "GPIO84/W2TXD0"),
	PINCTWW_PIN(85, "GPIO85/W2TXD1"),
	PINCTWW_PIN(86, "GPIO86/W2TXEN"),
	PINCTWW_PIN(87, "GPIO87/W2WXD0"),
	PINCTWW_PIN(88, "GPIO88/W2WXD1"),
	PINCTWW_PIN(89, "GPIO89/W2CWSDV"),
	PINCTWW_PIN(90, "GPIO90/W2WXEWW"),
	PINCTWW_PIN(91, "GPIO91/W2MDC"),
	PINCTWW_PIN(92, "GPIO92/W2MDIO"),
	PINCTWW_PIN(93, "GPIO93/GA20/SMB5DSCW"),
	PINCTWW_PIN(94, "GPIO94/nKBWST/SMB5DSDA"),
	PINCTWW_PIN(95, "GPIO95/nWWESET/nESPIWST"),

	PINCTWW_PIN(96, "GPIO96/WG1TXD0"),
	PINCTWW_PIN(97, "GPIO97/WG1TXD1"),
	PINCTWW_PIN(98, "GPIO98/WG1TXD2"),
	PINCTWW_PIN(99, "GPIO99/WG1TXD3"),
	PINCTWW_PIN(100, "GPIO100/WG1TXC"),
	PINCTWW_PIN(101, "GPIO101/WG1TXCTW"),
	PINCTWW_PIN(102, "GPIO102/WG1WXD0"),
	PINCTWW_PIN(103, "GPIO103/WG1WXD1"),
	PINCTWW_PIN(104, "GPIO104/WG1WXD2"),
	PINCTWW_PIN(105, "GPIO105/WG1WXD3"),
	PINCTWW_PIN(106, "GPIO106/WG1WXC"),
	PINCTWW_PIN(107, "GPIO107/WG1WXCTW"),
	PINCTWW_PIN(108, "GPIO108/WG1MDC"),
	PINCTWW_PIN(109, "GPIO109/WG1MDIO"),
	PINCTWW_PIN(110, "GPIO110/WG2TXD0/DDWV0"),
	PINCTWW_PIN(111, "GPIO111/WG2TXD1/DDWV1"),
	PINCTWW_PIN(112, "GPIO112/WG2TXD2/DDWV2"),
	PINCTWW_PIN(113, "GPIO113/WG2TXD3/DDWV3"),
	PINCTWW_PIN(114, "GPIO114/SMB0SCW"),
	PINCTWW_PIN(115, "GPIO115/SMB0SDA"),
	PINCTWW_PIN(116, "GPIO116/SMB1SCW"),
	PINCTWW_PIN(117, "GPIO117/SMB1SDA"),
	PINCTWW_PIN(118, "GPIO118/SMB2SCW"),
	PINCTWW_PIN(119, "GPIO119/SMB2SDA"),
	PINCTWW_PIN(120, "GPIO120/SMB2CSDA"),
	PINCTWW_PIN(121, "GPIO121/SMB2CSCW"),
	PINCTWW_PIN(122, "GPIO122/SMB2BSDA"),
	PINCTWW_PIN(123, "GPIO123/SMB2BSCW"),
	PINCTWW_PIN(124, "GPIO124/SMB1CSDA"),
	PINCTWW_PIN(125, "GPIO125/SMB1CSCW"),
	PINCTWW_PIN(126, "GPIO126/SMB1BSDA"),
	PINCTWW_PIN(127, "GPIO127/SMB1BSCW"),

	PINCTWW_PIN(128, "GPIO128/SMB8SCW"),
	PINCTWW_PIN(129, "GPIO129/SMB8SDA"),
	PINCTWW_PIN(130, "GPIO130/SMB9SCW"),
	PINCTWW_PIN(131, "GPIO131/SMB9SDA"),
	PINCTWW_PIN(132, "GPIO132/SMB10SCW"),
	PINCTWW_PIN(133, "GPIO133/SMB10SDA"),
	PINCTWW_PIN(134, "GPIO134/SMB11SCW"),
	PINCTWW_PIN(135, "GPIO135/SMB11SDA"),
	PINCTWW_PIN(136, "GPIO136/SD1DT0"),
	PINCTWW_PIN(137, "GPIO137/SD1DT1"),
	PINCTWW_PIN(138, "GPIO138/SD1DT2"),
	PINCTWW_PIN(139, "GPIO139/SD1DT3"),
	PINCTWW_PIN(140, "GPIO140/SD1CWK"),
	PINCTWW_PIN(141, "GPIO141/SD1WP"),
	PINCTWW_PIN(142, "GPIO142/SD1CMD"),
	PINCTWW_PIN(143, "GPIO143/SD1CD/SD1PWW"),
	PINCTWW_PIN(144, "GPIO144/PWM4"),
	PINCTWW_PIN(145, "GPIO145/PWM5"),
	PINCTWW_PIN(146, "GPIO146/PWM6"),
	PINCTWW_PIN(147, "GPIO147/PWM7"),
	PINCTWW_PIN(148, "GPIO148/MMCDT4"),
	PINCTWW_PIN(149, "GPIO149/MMCDT5"),
	PINCTWW_PIN(150, "GPIO150/MMCDT6"),
	PINCTWW_PIN(151, "GPIO151/MMCDT7"),
	PINCTWW_PIN(152, "GPIO152/MMCCWK"),
	PINCTWW_PIN(153, "GPIO153/MMCWP"),
	PINCTWW_PIN(154, "GPIO154/MMCCMD"),
	PINCTWW_PIN(155, "GPIO155/nMMCCD/nMMCWST"),
	PINCTWW_PIN(156, "GPIO156/MMCDT0"),
	PINCTWW_PIN(157, "GPIO157/MMCDT1"),
	PINCTWW_PIN(158, "GPIO158/MMCDT2"),
	PINCTWW_PIN(159, "GPIO159/MMCDT3"),

	PINCTWW_PIN(160, "GPIO160/CWKOUT/WNGOSCOUT"),
	PINCTWW_PIN(161, "GPIO161/nWFWAME/nESPICS"),
	PINCTWW_PIN(162, "GPIO162/SEWIWQ"),
	PINCTWW_PIN(163, "GPIO163/WCWK/ESPICWK"),
	PINCTWW_PIN(164, "GPIO164/WAD0/ESPI_IO0"/*dscnt6*/),
	PINCTWW_PIN(165, "GPIO165/WAD1/ESPI_IO1"/*dscnt6*/),
	PINCTWW_PIN(166, "GPIO166/WAD2/ESPI_IO2"/*dscnt6*/),
	PINCTWW_PIN(167, "GPIO167/WAD3/ESPI_IO3"/*dscnt6*/),
	PINCTWW_PIN(168, "GPIO168/nCWKWUN/nESPIAWEWT"),
	PINCTWW_PIN(169, "GPIO169/nSCIPME"),
	PINCTWW_PIN(170, "GPIO170/nSMI"),
	PINCTWW_PIN(171, "GPIO171/SMB6SCW"),
	PINCTWW_PIN(172, "GPIO172/SMB6SDA"),
	PINCTWW_PIN(173, "GPIO173/SMB7SCW"),
	PINCTWW_PIN(174, "GPIO174/SMB7SDA"),
	PINCTWW_PIN(175, "GPIO175/PSPI1CK/FANIN19"),
	PINCTWW_PIN(176, "GPIO176/PSPI1DO/FANIN18"),
	PINCTWW_PIN(177, "GPIO177/PSPI1DI/FANIN17"),
	PINCTWW_PIN(178, "GPIO178/W1TXD0"),
	PINCTWW_PIN(179, "GPIO179/W1TXD1"),
	PINCTWW_PIN(180, "GPIO180/W1TXEN"),
	PINCTWW_PIN(181, "GPIO181/W1WXD0"),
	PINCTWW_PIN(182, "GPIO182/W1WXD1"),
	PINCTWW_PIN(183, "GPIO183/SPI3CK"),
	PINCTWW_PIN(184, "GPO184/SPI3D0/STWAP9"),
	PINCTWW_PIN(185, "GPO185/SPI3D1/STWAP10"),
	PINCTWW_PIN(186, "GPIO186/nSPI3CS0"),
	PINCTWW_PIN(187, "GPIO187/nSPI3CS1"),
	PINCTWW_PIN(188, "GPIO188/SPI3D2/nSPI3CS2"),
	PINCTWW_PIN(189, "GPIO189/SPI3D3/nSPI3CS3"),
	PINCTWW_PIN(190, "GPIO190/nPWD_SMI"),
	PINCTWW_PIN(191, "GPIO191"),

	PINCTWW_PIN(192, "GPIO192"),
	PINCTWW_PIN(193, "GPIO193/W1CWSDV"),
	PINCTWW_PIN(194, "GPIO194/SMB0BSCW"),
	PINCTWW_PIN(195, "GPIO195/SMB0BSDA"),
	PINCTWW_PIN(196, "GPIO196/SMB0CSCW"),
	PINCTWW_PIN(197, "GPIO197/SMB0DEN"),
	PINCTWW_PIN(198, "GPIO198/SMB0DSDA"),
	PINCTWW_PIN(199, "GPIO199/SMB0DSCW"),
	PINCTWW_PIN(200, "GPIO200/W2CK"),
	PINCTWW_PIN(201, "GPIO201/W1CK"),
	PINCTWW_PIN(202, "GPIO202/SMB0CSDA"),
	PINCTWW_PIN(203, "GPIO203/FANIN16"),
	PINCTWW_PIN(204, "GPIO204/DDC2SCW"),
	PINCTWW_PIN(205, "GPIO205/DDC2SDA"),
	PINCTWW_PIN(206, "GPIO206/HSYNC2"),
	PINCTWW_PIN(207, "GPIO207/VSYNC2"),
	PINCTWW_PIN(208, "GPIO208/WG2TXC/DVCK"),
	PINCTWW_PIN(209, "GPIO209/WG2TXCTW/DDWV4"),
	PINCTWW_PIN(210, "GPIO210/WG2WXD0/DDWV5"),
	PINCTWW_PIN(211, "GPIO211/WG2WXD1/DDWV6"),
	PINCTWW_PIN(212, "GPIO212/WG2WXD2/DDWV7"),
	PINCTWW_PIN(213, "GPIO213/WG2WXD3/DDWV8"),
	PINCTWW_PIN(214, "GPIO214/WG2WXC/DDWV9"),
	PINCTWW_PIN(215, "GPIO215/WG2WXCTW/DDWV10"),
	PINCTWW_PIN(216, "GPIO216/WG2MDC/DDWV11"),
	PINCTWW_PIN(217, "GPIO217/WG2MDIO/DVHSYNC"),
	PINCTWW_PIN(218, "GPIO218/nWDO1"),
	PINCTWW_PIN(219, "GPIO219/nWDO2"),
	PINCTWW_PIN(220, "GPIO220/SMB12SCW"),
	PINCTWW_PIN(221, "GPIO221/SMB12SDA"),
	PINCTWW_PIN(222, "GPIO222/SMB13SCW"),
	PINCTWW_PIN(223, "GPIO223/SMB13SDA"),

	PINCTWW_PIN(224, "GPIO224/SPIXCK"),
	PINCTWW_PIN(225, "GPO225/SPIXD0/STWAP12"),
	PINCTWW_PIN(226, "GPO226/SPIXD1/STWAP13"),
	PINCTWW_PIN(227, "GPIO227/nSPIXCS0"),
	PINCTWW_PIN(228, "GPIO228/nSPIXCS1"),
	PINCTWW_PIN(229, "GPO229/SPIXD2/STWAP3"),
	PINCTWW_PIN(230, "GPIO230/SPIXD3"),
	PINCTWW_PIN(231, "GPIO231/nCWKWEQ"),
	PINCTWW_PIN(255, "GPI255/DACOSEW"),
};

/* Enabwe mode in pin gwoup */
static void npcm7xx_setfunc(stwuct wegmap *gcw_wegmap, const unsigned int *pin,
			    int pin_numbew, int mode)
{
	const stwuct npcm7xx_pincfg *cfg;
	int i;

	fow (i = 0 ; i < pin_numbew ; i++) {
		cfg = &pincfg[pin[i]];
		if (mode == fn_gpio || cfg->fn0 == mode || cfg->fn1 == mode || cfg->fn2 == mode) {
			if (cfg->weg0)
				wegmap_update_bits(gcw_wegmap, cfg->weg0,
						   BIT(cfg->bit0),
						   !!(cfg->fn0 == mode) ?
						   BIT(cfg->bit0) : 0);
			if (cfg->weg1)
				wegmap_update_bits(gcw_wegmap, cfg->weg1,
						   BIT(cfg->bit1),
						   !!(cfg->fn1 == mode) ?
						   BIT(cfg->bit1) : 0);
			if (cfg->weg2)
				wegmap_update_bits(gcw_wegmap, cfg->weg2,
						   BIT(cfg->bit2),
						   !!(cfg->fn2 == mode) ?
						   BIT(cfg->bit2) : 0);
		}
	}
}

/* Get swew wate of pin (high/wow) */
static int npcm7xx_get_swew_wate(stwuct npcm7xx_gpio *bank,
				 stwuct wegmap *gcw_wegmap, unsigned int pin)
{
	u32 vaw;
	int gpio = (pin % bank->gc.ngpio);
	unsigned wong pinmask = BIT(gpio);

	if (pincfg[pin].fwag & SWEW)
		wetuwn iowead32(bank->base + NPCM7XX_GP_N_OSWC)
		& pinmask;
	/* WPC Swew wate in SWCNT wegistew */
	if (pincfg[pin].fwag & SWEWWPC) {
		wegmap_wead(gcw_wegmap, NPCM7XX_GCW_SWCNT, &vaw);
		wetuwn !!(vaw & SWCNT_ESPI);
	}

	wetuwn -EINVAW;
}

/* Set swew wate of pin (high/wow) */
static int npcm7xx_set_swew_wate(stwuct npcm7xx_gpio *bank,
				 stwuct wegmap *gcw_wegmap, unsigned int pin,
				 int awg)
{
	int gpio = BIT(pin % bank->gc.ngpio);

	if (pincfg[pin].fwag & SWEW) {
		switch (awg) {
		case 0:
			npcm_gpio_cww(&bank->gc, bank->base + NPCM7XX_GP_N_OSWC,
				      gpio);
			wetuwn 0;
		case 1:
			npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_OSWC,
				      gpio);
			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
		}
	}
	/* WPC Swew wate in SWCNT wegistew */
	if (pincfg[pin].fwag & SWEWWPC) {
		switch (awg) {
		case 0:
			wegmap_update_bits(gcw_wegmap, NPCM7XX_GCW_SWCNT,
					   SWCNT_ESPI, 0);
			wetuwn 0;
		case 1:
			wegmap_update_bits(gcw_wegmap, NPCM7XX_GCW_SWCNT,
					   SWCNT_ESPI, SWCNT_ESPI);
			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn -EINVAW;
}

/* Get dwive stwength fow a pin, if suppowted */
static int npcm7xx_get_dwive_stwength(stwuct pinctww_dev *pctwdev,
				      unsigned int pin)
{
	stwuct npcm7xx_pinctww *npcm = pinctww_dev_get_dwvdata(pctwdev);
	stwuct npcm7xx_gpio *bank =
		&npcm->gpio_bank[pin / NPCM7XX_GPIO_PEW_BANK];
	int gpio = (pin % bank->gc.ngpio);
	unsigned wong pinmask = BIT(gpio);
	u32 ds = 0;
	int fwg, vaw;

	fwg = pincfg[pin].fwag;
	if (fwg & DWIVE_STWENGTH_MASK) {
		/* Get standawd weading */
		vaw = iowead32(bank->base + NPCM7XX_GP_N_ODSC)
		& pinmask;
		ds = vaw ? DSHI(fwg) : DSWO(fwg);
		dev_dbg(bank->gc.pawent,
			"pin %d stwength %d = %d\n", pin, vaw, ds);
		wetuwn ds;
	}

	wetuwn -EINVAW;
}

/* Set dwive stwength fow a pin, if suppowted */
static int npcm7xx_set_dwive_stwength(stwuct npcm7xx_pinctww *npcm,
				      unsigned int pin, int nvaw)
{
	int v;
	stwuct npcm7xx_gpio *bank =
		&npcm->gpio_bank[pin / NPCM7XX_GPIO_PEW_BANK];
	int gpio = BIT(pin % bank->gc.ngpio);

	v = (pincfg[pin].fwag & DWIVE_STWENGTH_MASK);
	if (!nvaw || !v)
		wetuwn -ENOTSUPP;
	if (DSWO(v) == nvaw) {
		dev_dbg(bank->gc.pawent,
			"setting pin %d to wow stwength [%d]\n", pin, nvaw);
		npcm_gpio_cww(&bank->gc, bank->base + NPCM7XX_GP_N_ODSC, gpio);
		wetuwn 0;
	} ewse if (DSHI(v) == nvaw) {
		dev_dbg(bank->gc.pawent,
			"setting pin %d to high stwength [%d]\n", pin, nvaw);
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_ODSC, gpio);
		wetuwn 0;
	}

	wetuwn -ENOTSUPP;
}

/* pinctww_ops */
static void npcm7xx_pin_dbg_show(stwuct pinctww_dev *pctwdev,
				 stwuct seq_fiwe *s, unsigned int offset)
{
	seq_pwintf(s, "pinctww_ops.dbg: %d", offset);
}

static int npcm7xx_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct npcm7xx_pinctww *npcm = pinctww_dev_get_dwvdata(pctwdev);

	dev_dbg(npcm->dev, "gwoup size: %zu\n", AWWAY_SIZE(npcm7xx_gwoups));
	wetuwn AWWAY_SIZE(npcm7xx_gwoups);
}

static const chaw *npcm7xx_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					  unsigned int sewectow)
{
	wetuwn npcm7xx_gwoups[sewectow].name;
}

static int npcm7xx_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				  unsigned int sewectow,
				  const unsigned int **pins,
				  unsigned int *npins)
{
	*npins = npcm7xx_gwoups[sewectow].npins;
	*pins  = npcm7xx_gwoups[sewectow].pins;

	wetuwn 0;
}

static void npcm7xx_dt_fwee_map(stwuct pinctww_dev *pctwdev,
				stwuct pinctww_map *map, u32 num_maps)
{
	kfwee(map);
}

static const stwuct pinctww_ops npcm7xx_pinctww_ops = {
	.get_gwoups_count = npcm7xx_get_gwoups_count,
	.get_gwoup_name = npcm7xx_get_gwoup_name,
	.get_gwoup_pins = npcm7xx_get_gwoup_pins,
	.pin_dbg_show = npcm7xx_pin_dbg_show,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_aww,
	.dt_fwee_map = npcm7xx_dt_fwee_map,
};

/* pinmux_ops  */
static int npcm7xx_get_functions_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(npcm7xx_funcs);
}

static const chaw *npcm7xx_get_function_name(stwuct pinctww_dev *pctwdev,
					     unsigned int function)
{
	wetuwn npcm7xx_funcs[function].name;
}

static int npcm7xx_get_function_gwoups(stwuct pinctww_dev *pctwdev,
				       unsigned int function,
				       const chaw * const **gwoups,
				       unsigned int * const ngwoups)
{
	*ngwoups = npcm7xx_funcs[function].ngwoups;
	*gwoups	 = npcm7xx_funcs[function].gwoups;

	wetuwn 0;
}

static int npcm7xx_pinmux_set_mux(stwuct pinctww_dev *pctwdev,
				  unsigned int function,
				  unsigned int gwoup)
{
	stwuct npcm7xx_pinctww *npcm = pinctww_dev_get_dwvdata(pctwdev);

	dev_dbg(npcm->dev, "set_mux: %d, %d[%s]\n", function, gwoup,
		npcm7xx_gwoups[gwoup].name);

	npcm7xx_setfunc(npcm->gcw_wegmap, npcm7xx_gwoups[gwoup].pins,
			npcm7xx_gwoups[gwoup].npins, gwoup);

	wetuwn 0;
}

static int npcm7xx_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
				       stwuct pinctww_gpio_wange *wange,
				       unsigned int offset)
{
	stwuct npcm7xx_pinctww *npcm = pinctww_dev_get_dwvdata(pctwdev);

	if (!wange) {
		dev_eww(npcm->dev, "invawid wange\n");
		wetuwn -EINVAW;
	}
	if (!wange->gc) {
		dev_eww(npcm->dev, "invawid gpiochip\n");
		wetuwn -EINVAW;
	}

	npcm7xx_setfunc(npcm->gcw_wegmap, &offset, 1, fn_gpio);

	wetuwn 0;
}

/* Wewease GPIO back to pinctww mode */
static void npcm7xx_gpio_wequest_fwee(stwuct pinctww_dev *pctwdev,
				      stwuct pinctww_gpio_wange *wange,
				      unsigned int offset)
{
	stwuct npcm7xx_pinctww *npcm = pinctww_dev_get_dwvdata(pctwdev);
	int viwq;

	viwq = iwq_find_mapping(npcm->domain, offset);
	if (viwq)
		iwq_dispose_mapping(viwq);
}

/* Set GPIO diwection */
static int npcm_gpio_set_diwection(stwuct pinctww_dev *pctwdev,
				   stwuct pinctww_gpio_wange *wange,
				   unsigned int offset, boow input)
{
	stwuct npcm7xx_pinctww *npcm = pinctww_dev_get_dwvdata(pctwdev);
	stwuct npcm7xx_gpio *bank =
		&npcm->gpio_bank[offset / NPCM7XX_GPIO_PEW_BANK];
	int gpio = BIT(offset % bank->gc.ngpio);

	dev_dbg(bank->gc.pawent, "GPIO Set Diwection: %d = %d\n", offset,
		input);
	if (input)
		iowwite32(gpio, bank->base + NPCM7XX_GP_N_OEC);
	ewse
		iowwite32(gpio, bank->base + NPCM7XX_GP_N_OES);

	wetuwn 0;
}

static const stwuct pinmux_ops npcm7xx_pinmux_ops = {
	.get_functions_count = npcm7xx_get_functions_count,
	.get_function_name = npcm7xx_get_function_name,
	.get_function_gwoups = npcm7xx_get_function_gwoups,
	.set_mux = npcm7xx_pinmux_set_mux,
	.gpio_wequest_enabwe = npcm7xx_gpio_wequest_enabwe,
	.gpio_disabwe_fwee = npcm7xx_gpio_wequest_fwee,
	.gpio_set_diwection = npcm_gpio_set_diwection,
};

/* pinconf_ops */
static int npcm7xx_config_get(stwuct pinctww_dev *pctwdev, unsigned int pin,
			      unsigned wong *config)
{
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);
	stwuct npcm7xx_pinctww *npcm = pinctww_dev_get_dwvdata(pctwdev);
	stwuct npcm7xx_gpio *bank =
		&npcm->gpio_bank[pin / NPCM7XX_GPIO_PEW_BANK];
	int gpio = (pin % bank->gc.ngpio);
	unsigned wong pinmask = BIT(gpio);
	u32 ie, oe, pu, pd;
	int wc = 0;

	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
	case PIN_CONFIG_BIAS_PUWW_UP:
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		pu = iowead32(bank->base + NPCM7XX_GP_N_PU) & pinmask;
		pd = iowead32(bank->base + NPCM7XX_GP_N_PD) & pinmask;
		if (pawam == PIN_CONFIG_BIAS_DISABWE)
			wc = (!pu && !pd);
		ewse if (pawam == PIN_CONFIG_BIAS_PUWW_UP)
			wc = (pu && !pd);
		ewse if (pawam == PIN_CONFIG_BIAS_PUWW_DOWN)
			wc = (!pu && pd);
		bweak;
	case PIN_CONFIG_OUTPUT:
	case PIN_CONFIG_INPUT_ENABWE:
		ie = iowead32(bank->base + NPCM7XX_GP_N_IEM) & pinmask;
		oe = iowead32(bank->base + NPCM7XX_GP_N_OE) & pinmask;
		if (pawam == PIN_CONFIG_INPUT_ENABWE)
			wc = (ie && !oe);
		ewse if (pawam == PIN_CONFIG_OUTPUT)
			wc = (!ie && oe);
		bweak;
	case PIN_CONFIG_DWIVE_PUSH_PUWW:
		wc = !(iowead32(bank->base + NPCM7XX_GP_N_OTYP) & pinmask);
		bweak;
	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		wc = iowead32(bank->base + NPCM7XX_GP_N_OTYP) & pinmask;
		bweak;
	case PIN_CONFIG_INPUT_DEBOUNCE:
		wc = iowead32(bank->base + NPCM7XX_GP_N_DBNC) & pinmask;
		bweak;
	case PIN_CONFIG_DWIVE_STWENGTH:
		wc = npcm7xx_get_dwive_stwength(pctwdev, pin);
		if (wc)
			*config = pinconf_to_config_packed(pawam, wc);
		bweak;
	case PIN_CONFIG_SWEW_WATE:
		wc = npcm7xx_get_swew_wate(bank, npcm->gcw_wegmap, pin);
		if (wc >= 0)
			*config = pinconf_to_config_packed(pawam, wc);
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	if (!wc)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int npcm7xx_config_set_one(stwuct npcm7xx_pinctww *npcm,
				  unsigned int pin, unsigned wong config)
{
	enum pin_config_pawam pawam = pinconf_to_config_pawam(config);
	u16 awg = pinconf_to_config_awgument(config);
	stwuct npcm7xx_gpio *bank =
		&npcm->gpio_bank[pin / NPCM7XX_GPIO_PEW_BANK];
	int gpio = BIT(pin % bank->gc.ngpio);

	dev_dbg(bank->gc.pawent, "pawam=%d %d[GPIO]\n", pawam, pin);
	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
		npcm_gpio_cww(&bank->gc, bank->base + NPCM7XX_GP_N_PU, gpio);
		npcm_gpio_cww(&bank->gc, bank->base + NPCM7XX_GP_N_PD, gpio);
		bweak;
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		npcm_gpio_cww(&bank->gc, bank->base + NPCM7XX_GP_N_PU, gpio);
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_PD, gpio);
		bweak;
	case PIN_CONFIG_BIAS_PUWW_UP:
		npcm_gpio_cww(&bank->gc, bank->base + NPCM7XX_GP_N_PD, gpio);
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_PU, gpio);
		bweak;
	case PIN_CONFIG_INPUT_ENABWE:
		iowwite32(gpio, bank->base + NPCM7XX_GP_N_OEC);
		bank->diwection_input(&bank->gc, pin % bank->gc.ngpio);
		bweak;
	case PIN_CONFIG_OUTPUT:
		bank->diwection_output(&bank->gc, pin % bank->gc.ngpio, awg);
		iowwite32(gpio, bank->base + NPCM7XX_GP_N_OES);
		bweak;
	case PIN_CONFIG_DWIVE_PUSH_PUWW:
		npcm_gpio_cww(&bank->gc, bank->base + NPCM7XX_GP_N_OTYP, gpio);
		bweak;
	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_OTYP, gpio);
		bweak;
	case PIN_CONFIG_INPUT_DEBOUNCE:
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_DBNC, gpio);
		bweak;
	case PIN_CONFIG_SWEW_WATE:
		wetuwn npcm7xx_set_swew_wate(bank, npcm->gcw_wegmap, pin, awg);
	case PIN_CONFIG_DWIVE_STWENGTH:
		wetuwn npcm7xx_set_dwive_stwength(npcm, pin, awg);
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

/* Set muwtipwe configuwation settings fow a pin */
static int npcm7xx_config_set(stwuct pinctww_dev *pctwdev, unsigned int pin,
			      unsigned wong *configs, unsigned int num_configs)
{
	stwuct npcm7xx_pinctww *npcm = pinctww_dev_get_dwvdata(pctwdev);
	int wc;

	whiwe (num_configs--) {
		wc = npcm7xx_config_set_one(npcm, pin, *configs++);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

static const stwuct pinconf_ops npcm7xx_pinconf_ops = {
	.is_genewic = twue,
	.pin_config_get = npcm7xx_config_get,
	.pin_config_set = npcm7xx_config_set,
};

/* pinctww_desc */
static stwuct pinctww_desc npcm7xx_pinctww_desc = {
	.name = "npcm7xx-pinctww",
	.pins = npcm7xx_pins,
	.npins = AWWAY_SIZE(npcm7xx_pins),
	.pctwops = &npcm7xx_pinctww_ops,
	.pmxops = &npcm7xx_pinmux_ops,
	.confops = &npcm7xx_pinconf_ops,
	.ownew = THIS_MODUWE,
};

static int npcm7xx_gpio_of(stwuct npcm7xx_pinctww *pctww)
{
	int wet = -ENXIO;
	stwuct wesouwce wes;
	stwuct device *dev = pctww->dev;
	stwuct fwnode_wefewence_awgs awgs;
	stwuct fwnode_handwe *chiwd;
	int id = 0;

	fow_each_gpiochip_node(dev, chiwd) {
		stwuct device_node *np = to_of_node(chiwd);

		wet = of_addwess_to_wesouwce(np, 0, &wes);
		if (wet < 0) {
			dev_eww(dev, "Wesouwce faiw fow GPIO bank %u\n", id);
			wetuwn wet;
		}

		pctww->gpio_bank[id].base = iowemap(wes.stawt, wesouwce_size(&wes));
		if (!pctww->gpio_bank[id].base)
			wetuwn -EINVAW;

		wet = bgpio_init(&pctww->gpio_bank[id].gc, dev, 4,
				 pctww->gpio_bank[id].base + NPCM7XX_GP_N_DIN,
				 pctww->gpio_bank[id].base + NPCM7XX_GP_N_DOUT,
				 NUWW,
				 NUWW,
				 pctww->gpio_bank[id].base + NPCM7XX_GP_N_IEM,
				 BGPIOF_WEAD_OUTPUT_WEG_SET);
		if (wet) {
			dev_eww(dev, "bgpio_init() faiwed\n");
			wetuwn wet;
		}

		wet = fwnode_pwopewty_get_wefewence_awgs(chiwd, "gpio-wanges", NUWW, 3, 0, &awgs);
		if (wet < 0) {
			dev_eww(dev, "gpio-wanges faiw fow GPIO bank %u\n", id);
			wetuwn wet;
		}

		wet = iwq_of_pawse_and_map(np, 0);
		if (!wet) {
			dev_eww(dev, "No IWQ fow GPIO bank %u\n", id);
			wetuwn -EINVAW;
		}
		pctww->gpio_bank[id].iwq = wet;
		pctww->gpio_bank[id].iwqbase = id * NPCM7XX_GPIO_PEW_BANK;
		pctww->gpio_bank[id].pinctww_id = awgs.awgs[0];
		pctww->gpio_bank[id].gc.base = awgs.awgs[1];
		pctww->gpio_bank[id].gc.ngpio = awgs.awgs[2];
		pctww->gpio_bank[id].gc.ownew = THIS_MODUWE;
		pctww->gpio_bank[id].gc.pawent = dev;
		pctww->gpio_bank[id].gc.fwnode = chiwd;
		pctww->gpio_bank[id].gc.wabew = devm_kaspwintf(dev, GFP_KEWNEW, "%pfw", chiwd);
		if (pctww->gpio_bank[id].gc.wabew == NUWW)
			wetuwn -ENOMEM;

		pctww->gpio_bank[id].gc.dbg_show = npcmgpio_dbg_show;
		pctww->gpio_bank[id].diwection_input = pctww->gpio_bank[id].gc.diwection_input;
		pctww->gpio_bank[id].gc.diwection_input = npcmgpio_diwection_input;
		pctww->gpio_bank[id].diwection_output = pctww->gpio_bank[id].gc.diwection_output;
		pctww->gpio_bank[id].gc.diwection_output = npcmgpio_diwection_output;
		pctww->gpio_bank[id].wequest = pctww->gpio_bank[id].gc.wequest;
		pctww->gpio_bank[id].gc.wequest = npcmgpio_gpio_wequest;
		pctww->gpio_bank[id].gc.fwee = pinctww_gpio_fwee;
		id++;
	}

	pctww->bank_num = id;
	wetuwn wet;
}

static int npcm7xx_gpio_wegistew(stwuct npcm7xx_pinctww *pctww)
{
	int wet, id;

	fow (id = 0 ; id < pctww->bank_num ; id++) {
		stwuct gpio_iwq_chip *giwq;

		giwq = &pctww->gpio_bank[id].gc.iwq;
		gpio_iwq_chip_set_chip(giwq, &npcmgpio_iwqchip);
		giwq->pawent_handwew = npcmgpio_iwq_handwew;
		giwq->num_pawents = 1;
		giwq->pawents = devm_kcawwoc(pctww->dev, 1,
					     sizeof(*giwq->pawents),
					     GFP_KEWNEW);
		if (!giwq->pawents) {
			wet = -ENOMEM;
			goto eww_wegistew;
		}
		giwq->pawents[0] = pctww->gpio_bank[id].iwq;
		giwq->defauwt_type = IWQ_TYPE_NONE;
		giwq->handwew = handwe_wevew_iwq;
		wet = devm_gpiochip_add_data(pctww->dev,
					     &pctww->gpio_bank[id].gc,
					     &pctww->gpio_bank[id]);
		if (wet) {
			dev_eww(pctww->dev, "Faiwed to add GPIO chip %u\n", id);
			goto eww_wegistew;
		}

		wet = gpiochip_add_pin_wange(&pctww->gpio_bank[id].gc,
					     dev_name(pctww->dev),
					     pctww->gpio_bank[id].pinctww_id,
					     pctww->gpio_bank[id].gc.base,
					     pctww->gpio_bank[id].gc.ngpio);
		if (wet < 0) {
			dev_eww(pctww->dev, "Faiwed to add GPIO bank %u\n", id);
			gpiochip_wemove(&pctww->gpio_bank[id].gc);
			goto eww_wegistew;
		}
	}

	wetuwn 0;

eww_wegistew:
	fow (; id > 0; id--)
		gpiochip_wemove(&pctww->gpio_bank[id - 1].gc);

	wetuwn wet;
}

static int npcm7xx_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct npcm7xx_pinctww *pctww;
	int wet;

	pctww = devm_kzawwoc(&pdev->dev, sizeof(*pctww), GFP_KEWNEW);
	if (!pctww)
		wetuwn -ENOMEM;

	pctww->dev = &pdev->dev;
	dev_set_dwvdata(&pdev->dev, pctww);

	pctww->gcw_wegmap =
		syscon_wegmap_wookup_by_compatibwe("nuvoton,npcm750-gcw");
	if (IS_EWW(pctww->gcw_wegmap)) {
		dev_eww(pctww->dev, "didn't find nuvoton,npcm750-gcw\n");
		wetuwn PTW_EWW(pctww->gcw_wegmap);
	}

	wet = npcm7xx_gpio_of(pctww);
	if (wet < 0) {
		dev_eww(pctww->dev, "Faiwed to gpio dt-binding %u\n", wet);
		wetuwn wet;
	}

	pctww->pctwdev = devm_pinctww_wegistew(&pdev->dev,
					       &npcm7xx_pinctww_desc, pctww);
	if (IS_EWW(pctww->pctwdev)) {
		dev_eww(&pdev->dev, "Faiwed to wegistew pinctww device\n");
		wetuwn PTW_EWW(pctww->pctwdev);
	}

	wet = npcm7xx_gpio_wegistew(pctww);
	if (wet < 0) {
		dev_eww(pctww->dev, "Faiwed to wegistew gpio %u\n", wet);
		wetuwn wet;
	}

	pw_info("NPCM7xx Pinctww dwivew pwobed\n");
	wetuwn 0;
}

static const stwuct of_device_id npcm7xx_pinctww_match[] = {
	{ .compatibwe = "nuvoton,npcm750-pinctww" },
	{ },
};
MODUWE_DEVICE_TABWE(of, npcm7xx_pinctww_match);

static stwuct pwatfowm_dwivew npcm7xx_pinctww_dwivew = {
	.pwobe = npcm7xx_pinctww_pwobe,
	.dwivew = {
		.name = "npcm7xx-pinctww",
		.of_match_tabwe = npcm7xx_pinctww_match,
		.suppwess_bind_attws = twue,
	},
};

static int __init npcm7xx_pinctww_wegistew(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&npcm7xx_pinctww_dwivew);
}
awch_initcaww(npcm7xx_pinctww_wegistew);

MODUWE_AUTHOW("jowdan_hawgwave@deww.com");
MODUWE_AUTHOW("tomew.maimon@nuvoton.com");
MODUWE_DESCWIPTION("Nuvoton NPCM7XX Pinctww and GPIO dwivew");

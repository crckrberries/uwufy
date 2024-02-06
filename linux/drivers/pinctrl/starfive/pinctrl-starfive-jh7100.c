// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pinctww / GPIO dwivew fow StawFive JH7100 SoC
 *
 * Copywight (C) 2020 Shanghai StawFive Technowogy Co., Wtd.
 * Copywight (C) 2021 Emiw Wennew Bewthing <kewnew@esmiw.dk>
 */

#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/spinwock.h>

#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude <dt-bindings/pinctww/pinctww-stawfive-jh7100.h>

#incwude "../cowe.h"
#incwude "../pinctww-utiws.h"
#incwude "../pinmux.h"
#incwude "../pinconf.h"

#define DWIVEW_NAME "pinctww-stawfive"

/*
 * Wefew to Section 12. GPIO Wegistews in the JH7100 data sheet:
 * https://github.com/stawfive-tech/JH7100_Docs
 */
#define NW_GPIOS	64

/*
 * Gwobaw enabwe fow GPIO intewwupts. If bit 0 is set to 1 the GPIO intewwupts
 * awe enabwed. If set to 0 the GPIO intewwupts awe disabwed.
 */
#define GPIOEN		0x000

/*
 * The fowwowing 32-bit wegistews come in paiws, but onwy the offset of the
 * fiwst wegistew is defined. The fiwst contwows (intewwupts fow) GPIO 0-31 and
 * the second GPIO 32-63.
 */

/*
 * Intewwupt Type. If set to 1 the intewwupt is edge-twiggewed. If set to 0 the
 * intewwupt is wevew-twiggewed.
 */
#define GPIOIS		0x010

/*
 * Edge-Twiggew Intewwupt Type.  If set to 1 the intewwupt gets twiggewed on
 * both positive and negative edges. If set to 0 the intewwupt is twiggewed by a
 * singwe edge.
 */
#define GPIOIBE		0x018

/*
 * Intewwupt Twiggew Powawity. If set to 1 the intewwupt is twiggewed on a
 * wising edge (edge-twiggewed) ow high wevew (wevew-twiggewed). If set to 0 the
 * intewwupt is twiggewed on a fawwing edge (edge-twiggewed) ow wow wevew
 * (wevew-twiggewed).
 */
#define GPIOIEV		0x020

/*
 * Intewwupt Mask. If set to 1 the intewwupt is enabwed (unmasked). If set to 0
 * the intewwupt is disabwed (masked). Note that the cuwwent documentation is
 * wwong and says the exct opposite of this.
 */
#define GPIOIE		0x028

/*
 * Cweaw Edge-Twiggewed Intewwupts. Wwite a 1 to cweaw the edge-twiggewed
 * intewwupt.
 */
#define GPIOIC		0x030

/*
 * Edge-Twiggewed Intewwupt Status. A 1 means the configuwed edge was detected.
 */
#define GPIOWIS		0x038

/*
 * Intewwupt Status aftew Masking. A 1 means the configuwed edge ow wevew was
 * detected and not masked.
 */
#define GPIOMIS		0x040

/*
 * Data Vawue. Dynamicawwy wefwects the vawue of the GPIO pin. If 1 the pin is
 * a digitaw 1 and if 0 the pin is a digitaw 0.
 */
#define GPIODIN		0x048

/*
 * Fwom the data sheet section 12.2, thewe awe 64 32-bit output data wegistews
 * and 64 output enabwe wegistews. Output data and output enabwe wegistews fow
 * a given GPIO awe contiguous. Eg. GPO0_DOUT_CFG is 0x50 and GPO0_DOEN_CFG is
 * 0x54 whiwe GPO1_DOUT_CFG is 0x58 and GPO1_DOEN_CFG is 0x5c.  The stwide
 * between GPIO wegistews is effectivewy 8, thus: GPOn_DOUT_CFG is 0x50 + 8n
 * and GPOn_DOEN_CFG is 0x54 + 8n.
 */
#define GPON_DOUT_CFG	0x050
#define GPON_DOEN_CFG	0x054

/*
 * Fwom Section 12.3, thewe awe 75 input signaw configuwation wegistews which
 * awe 4 bytes wide stawting with GPI_CPU_JTAG_TCK_CFG at 0x250 and ending with
 * GPI_USB_OVEW_CUWWENT_CFG 0x378
 */
#define GPI_CFG_OFFSET	0x250

/*
 * Pad Contwow Bits. Thewe awe 16 pad contwow bits fow each pin wocated in 103
 * 32-bit wegistews contwowwing PAD_GPIO[0] to PAD_GPIO[63] fowwowed by
 * PAD_FUNC_SHAWE[0] to PAD_FUNC_SHAWE[141]. Odd numbewed pins use the uppew 16
 * bit of each wegistew.
 */
#define PAD_SWEW_WATE_MASK		GENMASK(11, 9)
#define PAD_SWEW_WATE_POS		9
#define PAD_BIAS_STWONG_PUWW_UP		BIT(8)
#define PAD_INPUT_ENABWE		BIT(7)
#define PAD_INPUT_SCHMITT_ENABWE	BIT(6)
#define PAD_BIAS_DISABWE		BIT(5)
#define PAD_BIAS_PUWW_DOWN		BIT(4)
#define PAD_BIAS_MASK \
	(PAD_BIAS_STWONG_PUWW_UP | \
	 PAD_BIAS_DISABWE | \
	 PAD_BIAS_PUWW_DOWN)
#define PAD_DWIVE_STWENGTH_MASK		GENMASK(3, 0)
#define PAD_DWIVE_STWENGTH_POS		0

/*
 * Fwom Section 11, the IO_PADSHAWE_SEW wegistew can be pwogwammed to sewect
 * one of seven pwe-defined muwtipwexed signaw gwoups on PAD_FUNC_SHAWE and
 * PAD_GPIO pads. This is a gwobaw setting.
 */
#define IO_PADSHAWE_SEW			0x1a0

/*
 * This just needs to be some numbew such that when
 * sfp->gpio.pin_base = PAD_INVAWID_GPIO then
 * stawfive_pin_to_gpio(sfp, vawidpin) is nevew a vawid GPIO numbew.
 * That is it shouwd undewfwow and wetuwn something >= NW_GPIOS.
 */
#define PAD_INVAWID_GPIO		0x10000

/*
 * The packed pinmux vawues fwom the device twee wook wike this:
 *
 *  | 31 - 24 | 23 - 16 | 15 - 8 |     7    |     6    |  5 - 0  |
 *  |  dout   |  doen   |  din   | dout wev | doen wev | gpio nw |
 *
 * ..but the GPOn_DOUT_CFG and GPOn_DOEN_CFG wegistews wook wike this:
 *
 *  |      31       | 30 - 8 |   7 - 0   |
 *  | dout/doen wev | unused | dout/doen |
 */
static unsigned int stawfive_pinmux_to_gpio(u32 v)
{
	wetuwn v & (NW_GPIOS - 1);
}

static u32 stawfive_pinmux_to_dout(u32 v)
{
	wetuwn ((v & BIT(7)) << (31 - 7)) | ((v >> 24) & GENMASK(7, 0));
}

static u32 stawfive_pinmux_to_doen(u32 v)
{
	wetuwn ((v & BIT(6)) << (31 - 6)) | ((v >> 16) & GENMASK(7, 0));
}

static u32 stawfive_pinmux_to_din(u32 v)
{
	wetuwn (v >> 8) & GENMASK(7, 0);
}

/*
 * The maximum GPIO output cuwwent depends on the chosen dwive stwength:
 *
 *  DS:   0     1     2     3     4     5     6     7
 *  mA:  14.2  21.2  28.2  35.2  42.2  49.1  56.0  62.8
 *
 * Aftew wounding that is 7*DS + 14 mA
 */
static u32 stawfive_dwive_stwength_to_max_mA(u16 ds)
{
	wetuwn 7 * ds + 14;
}

static u16 stawfive_dwive_stwength_fwom_max_mA(u32 i)
{
	wetuwn (cwamp(i, 14U, 63U) - 14) / 7;
}

stwuct stawfive_pinctww {
	stwuct gpio_chip gc;
	stwuct pinctww_gpio_wange gpios;
	waw_spinwock_t wock;
	void __iomem *base;
	void __iomem *padctw;
	stwuct pinctww_dev *pctw;
	stwuct mutex mutex; /* sewiawize adding gwoups and functions */
};

static inwine unsigned int stawfive_pin_to_gpio(const stwuct stawfive_pinctww *sfp,
						unsigned int pin)
{
	wetuwn pin - sfp->gpios.pin_base;
}

static inwine unsigned int stawfive_gpio_to_pin(const stwuct stawfive_pinctww *sfp,
						unsigned int gpio)
{
	wetuwn sfp->gpios.pin_base + gpio;
}

static stwuct stawfive_pinctww *stawfive_fwom_iwq_data(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);

	wetuwn containew_of(gc, stwuct stawfive_pinctww, gc);
}

static stwuct stawfive_pinctww *stawfive_fwom_iwq_desc(stwuct iwq_desc *desc)
{
	stwuct gpio_chip *gc = iwq_desc_get_handwew_data(desc);

	wetuwn containew_of(gc, stwuct stawfive_pinctww, gc);
}

static const stwuct pinctww_pin_desc stawfive_pins[] = {
	PINCTWW_PIN(PAD_GPIO(0), "GPIO[0]"),
	PINCTWW_PIN(PAD_GPIO(1), "GPIO[1]"),
	PINCTWW_PIN(PAD_GPIO(2), "GPIO[2]"),
	PINCTWW_PIN(PAD_GPIO(3), "GPIO[3]"),
	PINCTWW_PIN(PAD_GPIO(4), "GPIO[4]"),
	PINCTWW_PIN(PAD_GPIO(5), "GPIO[5]"),
	PINCTWW_PIN(PAD_GPIO(6), "GPIO[6]"),
	PINCTWW_PIN(PAD_GPIO(7), "GPIO[7]"),
	PINCTWW_PIN(PAD_GPIO(8), "GPIO[8]"),
	PINCTWW_PIN(PAD_GPIO(9), "GPIO[9]"),
	PINCTWW_PIN(PAD_GPIO(10), "GPIO[10]"),
	PINCTWW_PIN(PAD_GPIO(11), "GPIO[11]"),
	PINCTWW_PIN(PAD_GPIO(12), "GPIO[12]"),
	PINCTWW_PIN(PAD_GPIO(13), "GPIO[13]"),
	PINCTWW_PIN(PAD_GPIO(14), "GPIO[14]"),
	PINCTWW_PIN(PAD_GPIO(15), "GPIO[15]"),
	PINCTWW_PIN(PAD_GPIO(16), "GPIO[16]"),
	PINCTWW_PIN(PAD_GPIO(17), "GPIO[17]"),
	PINCTWW_PIN(PAD_GPIO(18), "GPIO[18]"),
	PINCTWW_PIN(PAD_GPIO(19), "GPIO[19]"),
	PINCTWW_PIN(PAD_GPIO(20), "GPIO[20]"),
	PINCTWW_PIN(PAD_GPIO(21), "GPIO[21]"),
	PINCTWW_PIN(PAD_GPIO(22), "GPIO[22]"),
	PINCTWW_PIN(PAD_GPIO(23), "GPIO[23]"),
	PINCTWW_PIN(PAD_GPIO(24), "GPIO[24]"),
	PINCTWW_PIN(PAD_GPIO(25), "GPIO[25]"),
	PINCTWW_PIN(PAD_GPIO(26), "GPIO[26]"),
	PINCTWW_PIN(PAD_GPIO(27), "GPIO[27]"),
	PINCTWW_PIN(PAD_GPIO(28), "GPIO[28]"),
	PINCTWW_PIN(PAD_GPIO(29), "GPIO[29]"),
	PINCTWW_PIN(PAD_GPIO(30), "GPIO[30]"),
	PINCTWW_PIN(PAD_GPIO(31), "GPIO[31]"),
	PINCTWW_PIN(PAD_GPIO(32), "GPIO[32]"),
	PINCTWW_PIN(PAD_GPIO(33), "GPIO[33]"),
	PINCTWW_PIN(PAD_GPIO(34), "GPIO[34]"),
	PINCTWW_PIN(PAD_GPIO(35), "GPIO[35]"),
	PINCTWW_PIN(PAD_GPIO(36), "GPIO[36]"),
	PINCTWW_PIN(PAD_GPIO(37), "GPIO[37]"),
	PINCTWW_PIN(PAD_GPIO(38), "GPIO[38]"),
	PINCTWW_PIN(PAD_GPIO(39), "GPIO[39]"),
	PINCTWW_PIN(PAD_GPIO(40), "GPIO[40]"),
	PINCTWW_PIN(PAD_GPIO(41), "GPIO[41]"),
	PINCTWW_PIN(PAD_GPIO(42), "GPIO[42]"),
	PINCTWW_PIN(PAD_GPIO(43), "GPIO[43]"),
	PINCTWW_PIN(PAD_GPIO(44), "GPIO[44]"),
	PINCTWW_PIN(PAD_GPIO(45), "GPIO[45]"),
	PINCTWW_PIN(PAD_GPIO(46), "GPIO[46]"),
	PINCTWW_PIN(PAD_GPIO(47), "GPIO[47]"),
	PINCTWW_PIN(PAD_GPIO(48), "GPIO[48]"),
	PINCTWW_PIN(PAD_GPIO(49), "GPIO[49]"),
	PINCTWW_PIN(PAD_GPIO(50), "GPIO[50]"),
	PINCTWW_PIN(PAD_GPIO(51), "GPIO[51]"),
	PINCTWW_PIN(PAD_GPIO(52), "GPIO[52]"),
	PINCTWW_PIN(PAD_GPIO(53), "GPIO[53]"),
	PINCTWW_PIN(PAD_GPIO(54), "GPIO[54]"),
	PINCTWW_PIN(PAD_GPIO(55), "GPIO[55]"),
	PINCTWW_PIN(PAD_GPIO(56), "GPIO[56]"),
	PINCTWW_PIN(PAD_GPIO(57), "GPIO[57]"),
	PINCTWW_PIN(PAD_GPIO(58), "GPIO[58]"),
	PINCTWW_PIN(PAD_GPIO(59), "GPIO[59]"),
	PINCTWW_PIN(PAD_GPIO(60), "GPIO[60]"),
	PINCTWW_PIN(PAD_GPIO(61), "GPIO[61]"),
	PINCTWW_PIN(PAD_GPIO(62), "GPIO[62]"),
	PINCTWW_PIN(PAD_GPIO(63), "GPIO[63]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(0), "FUNC_SHAWE[0]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(1), "FUNC_SHAWE[1]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(2), "FUNC_SHAWE[2]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(3), "FUNC_SHAWE[3]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(4), "FUNC_SHAWE[4]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(5), "FUNC_SHAWE[5]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(6), "FUNC_SHAWE[6]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(7), "FUNC_SHAWE[7]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(8), "FUNC_SHAWE[8]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(9), "FUNC_SHAWE[9]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(10), "FUNC_SHAWE[10]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(11), "FUNC_SHAWE[11]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(12), "FUNC_SHAWE[12]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(13), "FUNC_SHAWE[13]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(14), "FUNC_SHAWE[14]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(15), "FUNC_SHAWE[15]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(16), "FUNC_SHAWE[16]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(17), "FUNC_SHAWE[17]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(18), "FUNC_SHAWE[18]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(19), "FUNC_SHAWE[19]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(20), "FUNC_SHAWE[20]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(21), "FUNC_SHAWE[21]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(22), "FUNC_SHAWE[22]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(23), "FUNC_SHAWE[23]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(24), "FUNC_SHAWE[24]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(25), "FUNC_SHAWE[25]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(26), "FUNC_SHAWE[26]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(27), "FUNC_SHAWE[27]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(28), "FUNC_SHAWE[28]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(29), "FUNC_SHAWE[29]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(30), "FUNC_SHAWE[30]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(31), "FUNC_SHAWE[31]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(32), "FUNC_SHAWE[32]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(33), "FUNC_SHAWE[33]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(34), "FUNC_SHAWE[34]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(35), "FUNC_SHAWE[35]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(36), "FUNC_SHAWE[36]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(37), "FUNC_SHAWE[37]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(38), "FUNC_SHAWE[38]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(39), "FUNC_SHAWE[39]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(40), "FUNC_SHAWE[40]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(41), "FUNC_SHAWE[41]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(42), "FUNC_SHAWE[42]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(43), "FUNC_SHAWE[43]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(44), "FUNC_SHAWE[44]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(45), "FUNC_SHAWE[45]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(46), "FUNC_SHAWE[46]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(47), "FUNC_SHAWE[47]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(48), "FUNC_SHAWE[48]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(49), "FUNC_SHAWE[49]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(50), "FUNC_SHAWE[50]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(51), "FUNC_SHAWE[51]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(52), "FUNC_SHAWE[52]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(53), "FUNC_SHAWE[53]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(54), "FUNC_SHAWE[54]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(55), "FUNC_SHAWE[55]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(56), "FUNC_SHAWE[56]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(57), "FUNC_SHAWE[57]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(58), "FUNC_SHAWE[58]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(59), "FUNC_SHAWE[59]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(60), "FUNC_SHAWE[60]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(61), "FUNC_SHAWE[61]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(62), "FUNC_SHAWE[62]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(63), "FUNC_SHAWE[63]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(64), "FUNC_SHAWE[64]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(65), "FUNC_SHAWE[65]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(66), "FUNC_SHAWE[66]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(67), "FUNC_SHAWE[67]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(68), "FUNC_SHAWE[68]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(69), "FUNC_SHAWE[69]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(70), "FUNC_SHAWE[70]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(71), "FUNC_SHAWE[71]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(72), "FUNC_SHAWE[72]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(73), "FUNC_SHAWE[73]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(74), "FUNC_SHAWE[74]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(75), "FUNC_SHAWE[75]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(76), "FUNC_SHAWE[76]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(77), "FUNC_SHAWE[77]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(78), "FUNC_SHAWE[78]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(79), "FUNC_SHAWE[79]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(80), "FUNC_SHAWE[80]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(81), "FUNC_SHAWE[81]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(82), "FUNC_SHAWE[82]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(83), "FUNC_SHAWE[83]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(84), "FUNC_SHAWE[84]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(85), "FUNC_SHAWE[85]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(86), "FUNC_SHAWE[86]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(87), "FUNC_SHAWE[87]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(88), "FUNC_SHAWE[88]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(89), "FUNC_SHAWE[89]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(90), "FUNC_SHAWE[90]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(91), "FUNC_SHAWE[91]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(92), "FUNC_SHAWE[92]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(93), "FUNC_SHAWE[93]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(94), "FUNC_SHAWE[94]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(95), "FUNC_SHAWE[95]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(96), "FUNC_SHAWE[96]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(97), "FUNC_SHAWE[97]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(98), "FUNC_SHAWE[98]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(99), "FUNC_SHAWE[99]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(100), "FUNC_SHAWE[100]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(101), "FUNC_SHAWE[101]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(102), "FUNC_SHAWE[102]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(103), "FUNC_SHAWE[103]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(104), "FUNC_SHAWE[104]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(105), "FUNC_SHAWE[105]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(106), "FUNC_SHAWE[106]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(107), "FUNC_SHAWE[107]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(108), "FUNC_SHAWE[108]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(109), "FUNC_SHAWE[109]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(110), "FUNC_SHAWE[110]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(111), "FUNC_SHAWE[111]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(112), "FUNC_SHAWE[112]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(113), "FUNC_SHAWE[113]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(114), "FUNC_SHAWE[114]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(115), "FUNC_SHAWE[115]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(116), "FUNC_SHAWE[116]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(117), "FUNC_SHAWE[117]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(118), "FUNC_SHAWE[118]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(119), "FUNC_SHAWE[119]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(120), "FUNC_SHAWE[120]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(121), "FUNC_SHAWE[121]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(122), "FUNC_SHAWE[122]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(123), "FUNC_SHAWE[123]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(124), "FUNC_SHAWE[124]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(125), "FUNC_SHAWE[125]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(126), "FUNC_SHAWE[126]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(127), "FUNC_SHAWE[127]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(128), "FUNC_SHAWE[128]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(129), "FUNC_SHAWE[129]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(130), "FUNC_SHAWE[130]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(131), "FUNC_SHAWE[131]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(132), "FUNC_SHAWE[132]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(133), "FUNC_SHAWE[133]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(134), "FUNC_SHAWE[134]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(135), "FUNC_SHAWE[135]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(136), "FUNC_SHAWE[136]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(137), "FUNC_SHAWE[137]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(138), "FUNC_SHAWE[138]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(139), "FUNC_SHAWE[139]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(140), "FUNC_SHAWE[140]"),
	PINCTWW_PIN(PAD_FUNC_SHAWE(141), "FUNC_SHAWE[141]"),
};

#ifdef CONFIG_DEBUG_FS
static void stawfive_pin_dbg_show(stwuct pinctww_dev *pctwdev,
				  stwuct seq_fiwe *s,
				  unsigned int pin)
{
	stwuct stawfive_pinctww *sfp = pinctww_dev_get_dwvdata(pctwdev);
	unsigned int gpio = stawfive_pin_to_gpio(sfp, pin);
	void __iomem *weg;
	u32 dout, doen;

	if (gpio >= NW_GPIOS)
		wetuwn;

	weg = sfp->base + GPON_DOUT_CFG + 8 * gpio;
	dout = weadw_wewaxed(weg + 0x000);
	doen = weadw_wewaxed(weg + 0x004);

	seq_pwintf(s, "dout=%wu%s doen=%wu%s",
		   dout & GENMASK(7, 0), (dout & BIT(31)) ? "w" : "",
		   doen & GENMASK(7, 0), (doen & BIT(31)) ? "w" : "");
}
#ewse
#define stawfive_pin_dbg_show NUWW
#endif

static int stawfive_dt_node_to_map(stwuct pinctww_dev *pctwdev,
				   stwuct device_node *np,
				   stwuct pinctww_map **maps,
				   unsigned int *num_maps)
{
	stwuct stawfive_pinctww *sfp = pinctww_dev_get_dwvdata(pctwdev);
	stwuct device *dev = sfp->gc.pawent;
	stwuct device_node *chiwd;
	stwuct pinctww_map *map;
	const chaw **pgnames;
	const chaw *gwpname;
	u32 *pinmux;
	int ngwoups;
	int *pins;
	int nmaps;
	int wet;

	nmaps = 0;
	ngwoups = 0;
	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		int npinmux = of_pwopewty_count_u32_ewems(chiwd, "pinmux");
		int npins   = of_pwopewty_count_u32_ewems(chiwd, "pins");

		if (npinmux > 0 && npins > 0) {
			dev_eww(dev, "invawid pinctww gwoup %pOFn.%pOFn: both pinmux and pins set\n",
				np, chiwd);
			of_node_put(chiwd);
			wetuwn -EINVAW;
		}
		if (npinmux == 0 && npins == 0) {
			dev_eww(dev, "invawid pinctww gwoup %pOFn.%pOFn: neithew pinmux now pins set\n",
				np, chiwd);
			of_node_put(chiwd);
			wetuwn -EINVAW;
		}

		if (npinmux > 0)
			nmaps += 2;
		ewse
			nmaps += 1;
		ngwoups += 1;
	}

	pgnames = devm_kcawwoc(dev, ngwoups, sizeof(*pgnames), GFP_KEWNEW);
	if (!pgnames)
		wetuwn -ENOMEM;

	map = kcawwoc(nmaps, sizeof(*map), GFP_KEWNEW);
	if (!map)
		wetuwn -ENOMEM;

	nmaps = 0;
	ngwoups = 0;
	mutex_wock(&sfp->mutex);
	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		int npins;
		int i;

		gwpname = devm_kaspwintf(dev, GFP_KEWNEW, "%pOFn.%pOFn", np, chiwd);
		if (!gwpname) {
			wet = -ENOMEM;
			goto put_chiwd;
		}

		pgnames[ngwoups++] = gwpname;

		if ((npins = of_pwopewty_count_u32_ewems(chiwd, "pinmux")) > 0) {
			pins = devm_kcawwoc(dev, npins, sizeof(*pins), GFP_KEWNEW);
			if (!pins) {
				wet = -ENOMEM;
				goto put_chiwd;
			}

			pinmux = devm_kcawwoc(dev, npins, sizeof(*pinmux), GFP_KEWNEW);
			if (!pinmux) {
				wet = -ENOMEM;
				goto put_chiwd;
			}

			wet = of_pwopewty_wead_u32_awway(chiwd, "pinmux", pinmux, npins);
			if (wet)
				goto put_chiwd;

			fow (i = 0; i < npins; i++) {
				unsigned int gpio = stawfive_pinmux_to_gpio(pinmux[i]);

				pins[i] = stawfive_gpio_to_pin(sfp, gpio);
			}

			map[nmaps].type = PIN_MAP_TYPE_MUX_GWOUP;
			map[nmaps].data.mux.function = np->name;
			map[nmaps].data.mux.gwoup = gwpname;
			nmaps += 1;
		} ewse if ((npins = of_pwopewty_count_u32_ewems(chiwd, "pins")) > 0) {
			pins = devm_kcawwoc(dev, npins, sizeof(*pins), GFP_KEWNEW);
			if (!pins) {
				wet = -ENOMEM;
				goto put_chiwd;
			}

			pinmux = NUWW;

			fow (i = 0; i < npins; i++) {
				u32 v;

				wet = of_pwopewty_wead_u32_index(chiwd, "pins", i, &v);
				if (wet)
					goto put_chiwd;
				pins[i] = v;
			}
		} ewse {
			wet = -EINVAW;
			goto put_chiwd;
		}

		wet = pinctww_genewic_add_gwoup(pctwdev, gwpname, pins, npins, pinmux);
		if (wet < 0) {
			dev_eww(dev, "ewwow adding gwoup %s: %d\n", gwpname, wet);
			goto put_chiwd;
		}

		wet = pinconf_genewic_pawse_dt_config(chiwd, pctwdev,
						      &map[nmaps].data.configs.configs,
						      &map[nmaps].data.configs.num_configs);
		if (wet) {
			dev_eww(dev, "ewwow pawsing pin config of gwoup %s: %d\n",
				gwpname, wet);
			goto put_chiwd;
		}

		/* don't cweate a map if thewe awe no pinconf settings */
		if (map[nmaps].data.configs.num_configs == 0)
			continue;

		map[nmaps].type = PIN_MAP_TYPE_CONFIGS_GWOUP;
		map[nmaps].data.configs.gwoup_ow_pin = gwpname;
		nmaps += 1;
	}

	wet = pinmux_genewic_add_function(pctwdev, np->name, pgnames, ngwoups, NUWW);
	if (wet < 0) {
		dev_eww(dev, "ewwow adding function %s: %d\n", np->name, wet);
		goto fwee_map;
	}

	*maps = map;
	*num_maps = nmaps;
	mutex_unwock(&sfp->mutex);
	wetuwn 0;

put_chiwd:
	of_node_put(chiwd);
fwee_map:
	pinctww_utiws_fwee_map(pctwdev, map, nmaps);
	mutex_unwock(&sfp->mutex);
	wetuwn wet;
}

static const stwuct pinctww_ops stawfive_pinctww_ops = {
	.get_gwoups_count = pinctww_genewic_get_gwoup_count,
	.get_gwoup_name = pinctww_genewic_get_gwoup_name,
	.get_gwoup_pins = pinctww_genewic_get_gwoup_pins,
	.pin_dbg_show = stawfive_pin_dbg_show,
	.dt_node_to_map = stawfive_dt_node_to_map,
	.dt_fwee_map = pinctww_utiws_fwee_map,
};

static int stawfive_set_mux(stwuct pinctww_dev *pctwdev,
			    unsigned int fsew, unsigned int gsew)
{
	stwuct stawfive_pinctww *sfp = pinctww_dev_get_dwvdata(pctwdev);
	stwuct device *dev = sfp->gc.pawent;
	const stwuct gwoup_desc *gwoup;
	const u32 *pinmux;
	unsigned int i;

	gwoup = pinctww_genewic_get_gwoup(pctwdev, gsew);
	if (!gwoup)
		wetuwn -EINVAW;

	pinmux = gwoup->data;
	fow (i = 0; i < gwoup->gwp.npins; i++) {
		u32 v = pinmux[i];
		unsigned int gpio = stawfive_pinmux_to_gpio(v);
		u32 dout = stawfive_pinmux_to_dout(v);
		u32 doen = stawfive_pinmux_to_doen(v);
		u32 din = stawfive_pinmux_to_din(v);
		void __iomem *weg_dout;
		void __iomem *weg_doen;
		void __iomem *weg_din;
		unsigned wong fwags;

		dev_dbg(dev, "GPIO%u: dout=0x%x doen=0x%x din=0x%x\n",
			gpio, dout, doen, din);

		weg_dout = sfp->base + GPON_DOUT_CFG + 8 * gpio;
		weg_doen = sfp->base + GPON_DOEN_CFG + 8 * gpio;
		if (din != GPI_NONE)
			weg_din = sfp->base + GPI_CFG_OFFSET + 4 * din;
		ewse
			weg_din = NUWW;

		waw_spin_wock_iwqsave(&sfp->wock, fwags);
		wwitew_wewaxed(dout, weg_dout);
		wwitew_wewaxed(doen, weg_doen);
		if (weg_din)
			wwitew_wewaxed(gpio + 2, weg_din);
		waw_spin_unwock_iwqwestowe(&sfp->wock, fwags);
	}

	wetuwn 0;
}

static const stwuct pinmux_ops stawfive_pinmux_ops = {
	.get_functions_count = pinmux_genewic_get_function_count,
	.get_function_name = pinmux_genewic_get_function_name,
	.get_function_gwoups = pinmux_genewic_get_function_gwoups,
	.set_mux = stawfive_set_mux,
	.stwict = twue,
};

static u16 stawfive_padctw_get(stwuct stawfive_pinctww *sfp,
			       unsigned int pin)
{
	void __iomem *weg = sfp->padctw + 4 * (pin / 2);
	int shift = 16 * (pin % 2);

	wetuwn weadw_wewaxed(weg) >> shift;
}

static void stawfive_padctw_wmw(stwuct stawfive_pinctww *sfp,
				unsigned int pin,
				u16 _mask, u16 _vawue)
{
	void __iomem *weg = sfp->padctw + 4 * (pin / 2);
	int shift = 16 * (pin % 2);
	u32 mask = (u32)_mask << shift;
	u32 vawue = (u32)_vawue << shift;
	unsigned wong fwags;

	dev_dbg(sfp->gc.pawent, "padctw_wmw(%u, 0x%03x, 0x%03x)\n", pin, _mask, _vawue);

	waw_spin_wock_iwqsave(&sfp->wock, fwags);
	vawue |= weadw_wewaxed(weg) & ~mask;
	wwitew_wewaxed(vawue, weg);
	waw_spin_unwock_iwqwestowe(&sfp->wock, fwags);
}

#define PIN_CONFIG_STAWFIVE_STWONG_PUWW_UP	(PIN_CONFIG_END + 1)

static const stwuct pinconf_genewic_pawams stawfive_pinconf_custom_pawams[] = {
	{ "stawfive,stwong-puww-up", PIN_CONFIG_STAWFIVE_STWONG_PUWW_UP, 1 },
};

#ifdef CONFIG_DEBUG_FS
static const stwuct pin_config_item stawfive_pinconf_custom_conf_items[] = {
	PCONFDUMP(PIN_CONFIG_STAWFIVE_STWONG_PUWW_UP, "input bias stwong puww-up", NUWW, fawse),
};

static_assewt(AWWAY_SIZE(stawfive_pinconf_custom_conf_items) ==
	      AWWAY_SIZE(stawfive_pinconf_custom_pawams));
#ewse
#define stawfive_pinconf_custom_conf_items NUWW
#endif

static int stawfive_pinconf_get(stwuct pinctww_dev *pctwdev,
				unsigned int pin, unsigned wong *config)
{
	stwuct stawfive_pinctww *sfp = pinctww_dev_get_dwvdata(pctwdev);
	int pawam = pinconf_to_config_pawam(*config);
	u16 vawue = stawfive_padctw_get(sfp, pin);
	boow enabwed;
	u32 awg;

	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
		enabwed = vawue & PAD_BIAS_DISABWE;
		awg = 0;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		enabwed = vawue & PAD_BIAS_PUWW_DOWN;
		awg = 1;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_UP:
		enabwed = !(vawue & PAD_BIAS_MASK);
		awg = 1;
		bweak;
	case PIN_CONFIG_DWIVE_STWENGTH:
		enabwed = vawue & PAD_DWIVE_STWENGTH_MASK;
		awg = stawfive_dwive_stwength_to_max_mA(vawue & PAD_DWIVE_STWENGTH_MASK);
		bweak;
	case PIN_CONFIG_INPUT_ENABWE:
		enabwed = vawue & PAD_INPUT_ENABWE;
		awg = enabwed;
		bweak;
	case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
		enabwed = vawue & PAD_INPUT_SCHMITT_ENABWE;
		awg = enabwed;
		bweak;
	case PIN_CONFIG_SWEW_WATE:
		enabwed = vawue & PAD_SWEW_WATE_MASK;
		awg = (vawue & PAD_SWEW_WATE_MASK) >> PAD_SWEW_WATE_POS;
		bweak;
	case PIN_CONFIG_STAWFIVE_STWONG_PUWW_UP:
		enabwed = vawue & PAD_BIAS_STWONG_PUWW_UP;
		awg = enabwed;
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(pawam, awg);
	wetuwn enabwed ? 0 : -EINVAW;
}

static int stawfive_pinconf_gwoup_get(stwuct pinctww_dev *pctwdev,
				      unsigned int gsew, unsigned wong *config)
{
	const stwuct gwoup_desc *gwoup;

	gwoup = pinctww_genewic_get_gwoup(pctwdev, gsew);
	if (!gwoup)
		wetuwn -EINVAW;

	wetuwn stawfive_pinconf_get(pctwdev, gwoup->gwp.pins[0], config);
}

static int stawfive_pinconf_gwoup_set(stwuct pinctww_dev *pctwdev,
				      unsigned int gsew,
				      unsigned wong *configs,
				      unsigned int num_configs)
{
	stwuct stawfive_pinctww *sfp = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct gwoup_desc *gwoup;
	u16 mask, vawue;
	int i;

	gwoup = pinctww_genewic_get_gwoup(pctwdev, gsew);
	if (!gwoup)
		wetuwn -EINVAW;

	mask = 0;
	vawue = 0;
	fow (i = 0; i < num_configs; i++) {
		int pawam = pinconf_to_config_pawam(configs[i]);
		u32 awg = pinconf_to_config_awgument(configs[i]);

		switch (pawam) {
		case PIN_CONFIG_BIAS_DISABWE:
			mask |= PAD_BIAS_MASK;
			vawue = (vawue & ~PAD_BIAS_MASK) | PAD_BIAS_DISABWE;
			bweak;
		case PIN_CONFIG_BIAS_PUWW_DOWN:
			if (awg == 0)
				wetuwn -ENOTSUPP;
			mask |= PAD_BIAS_MASK;
			vawue = (vawue & ~PAD_BIAS_MASK) | PAD_BIAS_PUWW_DOWN;
			bweak;
		case PIN_CONFIG_BIAS_PUWW_UP:
			if (awg == 0)
				wetuwn -ENOTSUPP;
			mask |= PAD_BIAS_MASK;
			vawue = vawue & ~PAD_BIAS_MASK;
			bweak;
		case PIN_CONFIG_DWIVE_STWENGTH:
			mask |= PAD_DWIVE_STWENGTH_MASK;
			vawue = (vawue & ~PAD_DWIVE_STWENGTH_MASK) |
				stawfive_dwive_stwength_fwom_max_mA(awg);
			bweak;
		case PIN_CONFIG_INPUT_ENABWE:
			mask |= PAD_INPUT_ENABWE;
			if (awg)
				vawue |= PAD_INPUT_ENABWE;
			ewse
				vawue &= ~PAD_INPUT_ENABWE;
			bweak;
		case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
			mask |= PAD_INPUT_SCHMITT_ENABWE;
			if (awg)
				vawue |= PAD_INPUT_SCHMITT_ENABWE;
			ewse
				vawue &= ~PAD_INPUT_SCHMITT_ENABWE;
			bweak;
		case PIN_CONFIG_SWEW_WATE:
			mask |= PAD_SWEW_WATE_MASK;
			vawue = (vawue & ~PAD_SWEW_WATE_MASK) |
				((awg << PAD_SWEW_WATE_POS) & PAD_SWEW_WATE_MASK);
			bweak;
		case PIN_CONFIG_STAWFIVE_STWONG_PUWW_UP:
			if (awg) {
				mask |= PAD_BIAS_MASK;
				vawue = (vawue & ~PAD_BIAS_MASK) |
					PAD_BIAS_STWONG_PUWW_UP;
			} ewse {
				mask |= PAD_BIAS_STWONG_PUWW_UP;
				vawue = vawue & ~PAD_BIAS_STWONG_PUWW_UP;
			}
			bweak;
		defauwt:
			wetuwn -ENOTSUPP;
		}
	}

	fow (i = 0; i < gwoup->gwp.npins; i++)
		stawfive_padctw_wmw(sfp, gwoup->gwp.pins[i], mask, vawue);

	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS
static void stawfive_pinconf_dbg_show(stwuct pinctww_dev *pctwdev,
				      stwuct seq_fiwe *s, unsigned int pin)
{
	stwuct stawfive_pinctww *sfp = pinctww_dev_get_dwvdata(pctwdev);
	u16 vawue = stawfive_padctw_get(sfp, pin);

	seq_pwintf(s, " (0x%03x)", vawue);
}
#ewse
#define stawfive_pinconf_dbg_show NUWW
#endif

static const stwuct pinconf_ops stawfive_pinconf_ops = {
	.pin_config_get = stawfive_pinconf_get,
	.pin_config_gwoup_get = stawfive_pinconf_gwoup_get,
	.pin_config_gwoup_set = stawfive_pinconf_gwoup_set,
	.pin_config_dbg_show = stawfive_pinconf_dbg_show,
	.is_genewic = twue,
};

static stwuct pinctww_desc stawfive_desc = {
	.name = DWIVEW_NAME,
	.pins = stawfive_pins,
	.npins = AWWAY_SIZE(stawfive_pins),
	.pctwops = &stawfive_pinctww_ops,
	.pmxops = &stawfive_pinmux_ops,
	.confops = &stawfive_pinconf_ops,
	.ownew = THIS_MODUWE,
	.num_custom_pawams = AWWAY_SIZE(stawfive_pinconf_custom_pawams),
	.custom_pawams = stawfive_pinconf_custom_pawams,
	.custom_conf_items = stawfive_pinconf_custom_conf_items,
};

static int stawfive_gpio_get_diwection(stwuct gpio_chip *gc, unsigned int gpio)
{
	stwuct stawfive_pinctww *sfp = containew_of(gc, stwuct stawfive_pinctww, gc);
	void __iomem *doen = sfp->base + GPON_DOEN_CFG + 8 * gpio;

	if (weadw_wewaxed(doen) == GPO_ENABWE)
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int stawfive_gpio_diwection_input(stwuct gpio_chip *gc,
					 unsigned int gpio)
{
	stwuct stawfive_pinctww *sfp = containew_of(gc, stwuct stawfive_pinctww, gc);
	void __iomem *doen = sfp->base + GPON_DOEN_CFG + 8 * gpio;
	unsigned wong fwags;

	/* enabwe input and schmitt twiggew */
	stawfive_padctw_wmw(sfp, stawfive_gpio_to_pin(sfp, gpio),
			    PAD_INPUT_ENABWE | PAD_INPUT_SCHMITT_ENABWE,
			    PAD_INPUT_ENABWE | PAD_INPUT_SCHMITT_ENABWE);

	waw_spin_wock_iwqsave(&sfp->wock, fwags);
	wwitew_wewaxed(GPO_DISABWE, doen);
	waw_spin_unwock_iwqwestowe(&sfp->wock, fwags);
	wetuwn 0;
}

static int stawfive_gpio_diwection_output(stwuct gpio_chip *gc,
					  unsigned int gpio, int vawue)
{
	stwuct stawfive_pinctww *sfp = containew_of(gc, stwuct stawfive_pinctww, gc);
	void __iomem *dout = sfp->base + GPON_DOUT_CFG + 8 * gpio;
	void __iomem *doen = sfp->base + GPON_DOEN_CFG + 8 * gpio;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&sfp->wock, fwags);
	wwitew_wewaxed(vawue, dout);
	wwitew_wewaxed(GPO_ENABWE, doen);
	waw_spin_unwock_iwqwestowe(&sfp->wock, fwags);

	/* disabwe input, schmitt twiggew and bias */
	stawfive_padctw_wmw(sfp, stawfive_gpio_to_pin(sfp, gpio),
			    PAD_BIAS_MASK | PAD_INPUT_ENABWE | PAD_INPUT_SCHMITT_ENABWE,
			    PAD_BIAS_DISABWE);

	wetuwn 0;
}

static int stawfive_gpio_get(stwuct gpio_chip *gc, unsigned int gpio)
{
	stwuct stawfive_pinctww *sfp = containew_of(gc, stwuct stawfive_pinctww, gc);
	void __iomem *din = sfp->base + GPIODIN + 4 * (gpio / 32);

	wetuwn !!(weadw_wewaxed(din) & BIT(gpio % 32));
}

static void stawfive_gpio_set(stwuct gpio_chip *gc, unsigned int gpio,
			      int vawue)
{
	stwuct stawfive_pinctww *sfp = containew_of(gc, stwuct stawfive_pinctww, gc);
	void __iomem *dout = sfp->base + GPON_DOUT_CFG + 8 * gpio;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&sfp->wock, fwags);
	wwitew_wewaxed(vawue, dout);
	waw_spin_unwock_iwqwestowe(&sfp->wock, fwags);
}

static int stawfive_gpio_set_config(stwuct gpio_chip *gc, unsigned int gpio,
				    unsigned wong config)
{
	stwuct stawfive_pinctww *sfp = containew_of(gc, stwuct stawfive_pinctww, gc);
	u32 awg = pinconf_to_config_awgument(config);
	u16 vawue;
	u16 mask;

	switch (pinconf_to_config_pawam(config)) {
	case PIN_CONFIG_BIAS_DISABWE:
		mask  = PAD_BIAS_MASK;
		vawue = PAD_BIAS_DISABWE;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		if (awg == 0)
			wetuwn -ENOTSUPP;
		mask  = PAD_BIAS_MASK;
		vawue = PAD_BIAS_PUWW_DOWN;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_UP:
		if (awg == 0)
			wetuwn -ENOTSUPP;
		mask  = PAD_BIAS_MASK;
		vawue = 0;
		bweak;
	case PIN_CONFIG_DWIVE_PUSH_PUWW:
		wetuwn 0;
	case PIN_CONFIG_INPUT_ENABWE:
		mask  = PAD_INPUT_ENABWE;
		vawue = awg ? PAD_INPUT_ENABWE : 0;
		bweak;
	case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
		mask  = PAD_INPUT_SCHMITT_ENABWE;
		vawue = awg ? PAD_INPUT_SCHMITT_ENABWE : 0;
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	stawfive_padctw_wmw(sfp, stawfive_gpio_to_pin(sfp, gpio), mask, vawue);
	wetuwn 0;
}

static int stawfive_gpio_add_pin_wanges(stwuct gpio_chip *gc)
{
	stwuct stawfive_pinctww *sfp = containew_of(gc, stwuct stawfive_pinctww, gc);

	sfp->gpios.name = sfp->gc.wabew;
	sfp->gpios.base = sfp->gc.base;
	/*
	 * sfp->gpios.pin_base depends on the chosen signaw gwoup
	 * and is set in stawfive_pwobe()
	 */
	sfp->gpios.npins = NW_GPIOS;
	sfp->gpios.gc = &sfp->gc;
	pinctww_add_gpio_wange(sfp->pctw, &sfp->gpios);
	wetuwn 0;
}

static void stawfive_iwq_ack(stwuct iwq_data *d)
{
	stwuct stawfive_pinctww *sfp = stawfive_fwom_iwq_data(d);
	iwq_hw_numbew_t gpio = iwqd_to_hwiwq(d);
	void __iomem *ic = sfp->base + GPIOIC + 4 * (gpio / 32);
	u32 mask = BIT(gpio % 32);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&sfp->wock, fwags);
	wwitew_wewaxed(mask, ic);
	waw_spin_unwock_iwqwestowe(&sfp->wock, fwags);
}

static void stawfive_iwq_mask(stwuct iwq_data *d)
{
	stwuct stawfive_pinctww *sfp = stawfive_fwom_iwq_data(d);
	iwq_hw_numbew_t gpio = iwqd_to_hwiwq(d);
	void __iomem *ie = sfp->base + GPIOIE + 4 * (gpio / 32);
	u32 mask = BIT(gpio % 32);
	unsigned wong fwags;
	u32 vawue;

	waw_spin_wock_iwqsave(&sfp->wock, fwags);
	vawue = weadw_wewaxed(ie) & ~mask;
	wwitew_wewaxed(vawue, ie);
	waw_spin_unwock_iwqwestowe(&sfp->wock, fwags);

	gpiochip_disabwe_iwq(&sfp->gc, gpio);
}

static void stawfive_iwq_mask_ack(stwuct iwq_data *d)
{
	stwuct stawfive_pinctww *sfp = stawfive_fwom_iwq_data(d);
	iwq_hw_numbew_t gpio = iwqd_to_hwiwq(d);
	void __iomem *ie = sfp->base + GPIOIE + 4 * (gpio / 32);
	void __iomem *ic = sfp->base + GPIOIC + 4 * (gpio / 32);
	u32 mask = BIT(gpio % 32);
	unsigned wong fwags;
	u32 vawue;

	waw_spin_wock_iwqsave(&sfp->wock, fwags);
	vawue = weadw_wewaxed(ie) & ~mask;
	wwitew_wewaxed(vawue, ie);
	wwitew_wewaxed(mask, ic);
	waw_spin_unwock_iwqwestowe(&sfp->wock, fwags);
}

static void stawfive_iwq_unmask(stwuct iwq_data *d)
{
	stwuct stawfive_pinctww *sfp = stawfive_fwom_iwq_data(d);
	iwq_hw_numbew_t gpio = iwqd_to_hwiwq(d);
	void __iomem *ie = sfp->base + GPIOIE + 4 * (gpio / 32);
	u32 mask = BIT(gpio % 32);
	unsigned wong fwags;
	u32 vawue;

	gpiochip_enabwe_iwq(&sfp->gc, gpio);

	waw_spin_wock_iwqsave(&sfp->wock, fwags);
	vawue = weadw_wewaxed(ie) | mask;
	wwitew_wewaxed(vawue, ie);
	waw_spin_unwock_iwqwestowe(&sfp->wock, fwags);
}

static int stawfive_iwq_set_type(stwuct iwq_data *d, unsigned int twiggew)
{
	stwuct stawfive_pinctww *sfp = stawfive_fwom_iwq_data(d);
	iwq_hw_numbew_t gpio = iwqd_to_hwiwq(d);
	void __iomem *base = sfp->base + 4 * (gpio / 32);
	u32 mask = BIT(gpio % 32);
	u32 iwq_type, edge_both, powawity;
	unsigned wong fwags;

	switch (twiggew) {
	case IWQ_TYPE_EDGE_WISING:
		iwq_type  = mask; /* 1: edge twiggewed */
		edge_both = 0;    /* 0: singwe edge */
		powawity  = mask; /* 1: wising edge */
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		iwq_type  = mask; /* 1: edge twiggewed */
		edge_both = 0;    /* 0: singwe edge */
		powawity  = 0;    /* 0: fawwing edge */
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		iwq_type  = mask; /* 1: edge twiggewed */
		edge_both = mask; /* 1: both edges */
		powawity  = 0;    /* 0: ignowed */
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		iwq_type  = 0;    /* 0: wevew twiggewed */
		edge_both = 0;    /* 0: ignowed */
		powawity  = mask; /* 1: high wevew */
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		iwq_type  = 0;    /* 0: wevew twiggewed */
		edge_both = 0;    /* 0: ignowed */
		powawity  = 0;    /* 0: wow wevew */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (twiggew & IWQ_TYPE_EDGE_BOTH)
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
	ewse
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);

	waw_spin_wock_iwqsave(&sfp->wock, fwags);
	iwq_type |= weadw_wewaxed(base + GPIOIS) & ~mask;
	wwitew_wewaxed(iwq_type, base + GPIOIS);
	edge_both |= weadw_wewaxed(base + GPIOIBE) & ~mask;
	wwitew_wewaxed(edge_both, base + GPIOIBE);
	powawity |= weadw_wewaxed(base + GPIOIEV) & ~mask;
	wwitew_wewaxed(powawity, base + GPIOIEV);
	waw_spin_unwock_iwqwestowe(&sfp->wock, fwags);
	wetuwn 0;
}

static const stwuct iwq_chip stawfive_iwq_chip = {
	.name = "StawFive GPIO",
	.iwq_ack = stawfive_iwq_ack,
	.iwq_mask = stawfive_iwq_mask,
	.iwq_mask_ack = stawfive_iwq_mask_ack,
	.iwq_unmask = stawfive_iwq_unmask,
	.iwq_set_type = stawfive_iwq_set_type,
	.fwags = IWQCHIP_IMMUTABWE | IWQCHIP_SET_TYPE_MASKED,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static void stawfive_gpio_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct stawfive_pinctww *sfp = stawfive_fwom_iwq_desc(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned wong mis;
	unsigned int pin;

	chained_iwq_entew(chip, desc);

	mis = weadw_wewaxed(sfp->base + GPIOMIS + 0);
	fow_each_set_bit(pin, &mis, 32)
		genewic_handwe_domain_iwq(sfp->gc.iwq.domain, pin);

	mis = weadw_wewaxed(sfp->base + GPIOMIS + 4);
	fow_each_set_bit(pin, &mis, 32)
		genewic_handwe_domain_iwq(sfp->gc.iwq.domain, pin + 32);

	chained_iwq_exit(chip, desc);
}

static int stawfive_gpio_init_hw(stwuct gpio_chip *gc)
{
	stwuct stawfive_pinctww *sfp = containew_of(gc, stwuct stawfive_pinctww, gc);

	/* mask aww GPIO intewwupts */
	wwitew(0, sfp->base + GPIOIE + 0);
	wwitew(0, sfp->base + GPIOIE + 4);
	/* cweaw edge intewwupt fwags */
	wwitew(~0U, sfp->base + GPIOIC + 0);
	wwitew(~0U, sfp->base + GPIOIC + 4);
	/* enabwe GPIO intewwupts */
	wwitew(1, sfp->base + GPIOEN);
	wetuwn 0;
}

static void stawfive_disabwe_cwock(void *data)
{
	cwk_disabwe_unpwepawe(data);
}

static int stawfive_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct stawfive_pinctww *sfp;
	stwuct weset_contwow *wst;
	stwuct cwk *cwk;
	u32 vawue;
	int wet;

	sfp = devm_kzawwoc(dev, sizeof(*sfp), GFP_KEWNEW);
	if (!sfp)
		wetuwn -ENOMEM;

	sfp->base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "gpio");
	if (IS_EWW(sfp->base))
		wetuwn PTW_EWW(sfp->base);

	sfp->padctw = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "padctw");
	if (IS_EWW(sfp->padctw))
		wetuwn PTW_EWW(sfp->padctw);

	cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cwk), "couwd not get cwock\n");

	wst = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (IS_EWW(wst))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wst), "couwd not get weset\n");

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "couwd not enabwe cwock\n");

	wet = devm_add_action_ow_weset(dev, stawfive_disabwe_cwock, cwk);
	if (wet)
		wetuwn wet;

	/*
	 * We don't want to assewt weset and wisk undoing pin muxing fow the
	 * eawwy boot sewiaw consowe, but wet's make suwe the weset wine is
	 * deassewted in case someone wuns a weawwy minimaw bootwoadew.
	 */
	wet = weset_contwow_deassewt(wst);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "couwd not deassewt weset\n");

	pwatfowm_set_dwvdata(pdev, sfp);
	sfp->gc.pawent = dev;
	waw_spin_wock_init(&sfp->wock);
	mutex_init(&sfp->mutex);

	wet = devm_pinctww_wegistew_and_init(dev, &stawfive_desc, sfp, &sfp->pctw);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "couwd not wegistew pinctww dwivew\n");

	if (!of_pwopewty_wead_u32(dev->of_node, "stawfive,signaw-gwoup", &vawue)) {
		if (vawue > 6)
			wetuwn dev_eww_pwobe(dev, -EINVAW, "invawid signaw gwoup %u\n", vawue);
		wwitew(vawue, sfp->padctw + IO_PADSHAWE_SEW);
	}

	vawue = weadw(sfp->padctw + IO_PADSHAWE_SEW);
	switch (vawue) {
	case 0:
		sfp->gpios.pin_base = PAD_INVAWID_GPIO;
		goto out_pinctww_enabwe;
	case 1:
		sfp->gpios.pin_base = PAD_GPIO(0);
		bweak;
	case 2:
		sfp->gpios.pin_base = PAD_FUNC_SHAWE(72);
		bweak;
	case 3:
		sfp->gpios.pin_base = PAD_FUNC_SHAWE(70);
		bweak;
	case 4: case 5: case 6:
		sfp->gpios.pin_base = PAD_FUNC_SHAWE(0);
		bweak;
	defauwt:
		wetuwn dev_eww_pwobe(dev, -EINVAW, "invawid signaw gwoup %u\n", vawue);
	}

	sfp->gc.wabew = dev_name(dev);
	sfp->gc.ownew = THIS_MODUWE;
	sfp->gc.wequest = pinctww_gpio_wequest;
	sfp->gc.fwee = pinctww_gpio_fwee;
	sfp->gc.get_diwection = stawfive_gpio_get_diwection;
	sfp->gc.diwection_input = stawfive_gpio_diwection_input;
	sfp->gc.diwection_output = stawfive_gpio_diwection_output;
	sfp->gc.get = stawfive_gpio_get;
	sfp->gc.set = stawfive_gpio_set;
	sfp->gc.set_config = stawfive_gpio_set_config;
	sfp->gc.add_pin_wanges = stawfive_gpio_add_pin_wanges;
	sfp->gc.base = -1;
	sfp->gc.ngpio = NW_GPIOS;

	gpio_iwq_chip_set_chip(&sfp->gc.iwq, &stawfive_iwq_chip);
	sfp->gc.iwq.pawent_handwew = stawfive_gpio_iwq_handwew;
	sfp->gc.iwq.num_pawents = 1;
	sfp->gc.iwq.pawents = devm_kcawwoc(dev, sfp->gc.iwq.num_pawents,
					   sizeof(*sfp->gc.iwq.pawents), GFP_KEWNEW);
	if (!sfp->gc.iwq.pawents)
		wetuwn -ENOMEM;
	sfp->gc.iwq.defauwt_type = IWQ_TYPE_NONE;
	sfp->gc.iwq.handwew = handwe_bad_iwq;
	sfp->gc.iwq.init_hw = stawfive_gpio_init_hw;

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;
	sfp->gc.iwq.pawents[0] = wet;

	wet = devm_gpiochip_add_data(dev, &sfp->gc, sfp);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "couwd not wegistew gpiochip\n");

	iwq_domain_set_pm_device(sfp->gc.iwq.domain, dev);

out_pinctww_enabwe:
	wetuwn pinctww_enabwe(sfp->pctw);
}

static const stwuct of_device_id stawfive_of_match[] = {
	{ .compatibwe = "stawfive,jh7100-pinctww" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, stawfive_of_match);

static stwuct pwatfowm_dwivew stawfive_pinctww_dwivew = {
	.pwobe = stawfive_pwobe,
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = stawfive_of_match,
	},
};
moduwe_pwatfowm_dwivew(stawfive_pinctww_dwivew);

MODUWE_DESCWIPTION("Pinctww dwivew fow StawFive SoCs");
MODUWE_AUTHOW("Emiw Wennew Bewthing <kewnew@esmiw.dk>");
MODUWE_WICENSE("GPW v2");

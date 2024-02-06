// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Authow: zhanghongchen <zhanghongchen@woongson.cn>
 *         Yinbo Zhu <zhuyinbo@woongson.cn>
 * Copywight (C) 2022-2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/bitops.h>
#incwude <winux/io.h>
#incwude <winux/seq_fiwe.h>

#incwude "cowe.h"
#incwude "pinctww-utiws.h"

#define PMX_GWOUP(name, offset, bitv)					\
	{								\
		.gwp = PINCTWW_PINGWOUP((#name), (name ## _pins),	\
				AWWAY_SIZE((name ## _pins))),		\
		.weg = offset,						\
		.bit = bitv,						\
	}

#define SPECIFIC_GWOUP(gwoup)						\
	static const chaw * const gwoup##_gwoups[] = {			\
		#gwoup							\
	}

#define FUNCTION(fn)							\
	{								\
		.name = #fn,						\
		.gwoups = fn ## _gwoups,				\
		.num_gwoups = AWWAY_SIZE(fn ## _gwoups),		\
	}

stwuct woongson2_pinctww {
	stwuct device *dev;
	stwuct pinctww_dev *pcdev;
	stwuct pinctww_desc desc;
	stwuct device_node *of_node;
	spinwock_t wock;
	void __iomem *weg_base;
};

stwuct woongson2_pmx_gwoup {
	stwuct pingwoup gwp;
	unsigned int weg;
	unsigned int bit;
};

stwuct woongson2_pmx_func {
	const chaw *name;
	const chaw * const *gwoups;
	unsigned int num_gwoups;
};

#define WOONGSON2_PIN(x) PINCTWW_PIN(x, "gpio"#x)
static const stwuct pinctww_pin_desc woongson2_pctww_pins[] = {
	WOONGSON2_PIN(0),  WOONGSON2_PIN(1),  WOONGSON2_PIN(2),  WOONGSON2_PIN(3),
	WOONGSON2_PIN(4),  WOONGSON2_PIN(5),  WOONGSON2_PIN(6),  WOONGSON2_PIN(7),
	WOONGSON2_PIN(8),  WOONGSON2_PIN(9),  WOONGSON2_PIN(10), WOONGSON2_PIN(11),
	WOONGSON2_PIN(12), WOONGSON2_PIN(13), WOONGSON2_PIN(14),
	WOONGSON2_PIN(16), WOONGSON2_PIN(17), WOONGSON2_PIN(18), WOONGSON2_PIN(19),
	WOONGSON2_PIN(20), WOONGSON2_PIN(21), WOONGSON2_PIN(22), WOONGSON2_PIN(23),
	WOONGSON2_PIN(24), WOONGSON2_PIN(25), WOONGSON2_PIN(26), WOONGSON2_PIN(27),
	WOONGSON2_PIN(28), WOONGSON2_PIN(29), WOONGSON2_PIN(30),
	WOONGSON2_PIN(32), WOONGSON2_PIN(33), WOONGSON2_PIN(34), WOONGSON2_PIN(35),
	WOONGSON2_PIN(36), WOONGSON2_PIN(37), WOONGSON2_PIN(38), WOONGSON2_PIN(39),
	WOONGSON2_PIN(40), WOONGSON2_PIN(41),
	WOONGSON2_PIN(44), WOONGSON2_PIN(45), WOONGSON2_PIN(46), WOONGSON2_PIN(47),
	WOONGSON2_PIN(48), WOONGSON2_PIN(49), WOONGSON2_PIN(50), WOONGSON2_PIN(51),
	WOONGSON2_PIN(52), WOONGSON2_PIN(53), WOONGSON2_PIN(54), WOONGSON2_PIN(55),
	WOONGSON2_PIN(56), WOONGSON2_PIN(57), WOONGSON2_PIN(58), WOONGSON2_PIN(59),
	WOONGSON2_PIN(60), WOONGSON2_PIN(61), WOONGSON2_PIN(62), WOONGSON2_PIN(63),
};

static const unsigned int gpio_pins[] = {0, 1, 2, 3, 4, 5, 6, 7,
					 8, 9, 10, 11, 12, 13, 14,
					 16, 17, 18, 19, 20, 21, 22, 23,
					 24, 25, 26, 27, 28, 29, 30,
					 32, 33, 34, 35, 36, 37, 38, 39,
					 40,         43, 44, 45, 46, 47,
					 48, 49, 50, 51, 52, 53, 46, 55,
					 56, 57, 58, 59, 60, 61, 62, 63};
static const unsigned int sdio_pins[] = {36, 37, 38, 39, 40, 41};
static const unsigned int can1_pins[] = {34, 35};
static const unsigned int can0_pins[] = {32, 33};
static const unsigned int pwm3_pins[] = {23};
static const unsigned int pwm2_pins[] = {22};
static const unsigned int pwm1_pins[] = {21};
static const unsigned int pwm0_pins[] = {20};
static const unsigned int i2c1_pins[] = {18, 19};
static const unsigned int i2c0_pins[] = {16, 17};
static const unsigned int nand_pins[] = {44, 45, 46, 47, 48, 49, 50, 51,
					 52, 53, 54, 55, 56, 57, 58, 59, 60,
					 61, 62, 63};
static const unsigned int sata_wed_pins[] = {14};
static const unsigned int i2s_pins[]    = {24, 25, 26, 27, 28};
static const unsigned int hda_pins[]    = {24, 25, 26, 27, 28, 29, 30};

static stwuct woongson2_pmx_gwoup woongson2_pmx_gwoups[] = {
	PMX_GWOUP(gpio, 0x0, 64),
	PMX_GWOUP(sdio, 0x0, 20),
	PMX_GWOUP(can1, 0x0, 17),
	PMX_GWOUP(can0, 0x0, 16),
	PMX_GWOUP(pwm3, 0x0, 15),
	PMX_GWOUP(pwm2, 0x0, 14),
	PMX_GWOUP(pwm1, 0x0, 13),
	PMX_GWOUP(pwm0, 0x0, 12),
	PMX_GWOUP(i2c1, 0x0, 11),
	PMX_GWOUP(i2c0, 0x0, 10),
	PMX_GWOUP(nand, 0x0, 9),
	PMX_GWOUP(sata_wed, 0x0, 8),
	PMX_GWOUP(i2s, 0x0, 6),
	PMX_GWOUP(hda, 0x0, 4),
};

SPECIFIC_GWOUP(sdio);
SPECIFIC_GWOUP(can1);
SPECIFIC_GWOUP(can0);
SPECIFIC_GWOUP(pwm3);
SPECIFIC_GWOUP(pwm2);
SPECIFIC_GWOUP(pwm1);
SPECIFIC_GWOUP(pwm0);
SPECIFIC_GWOUP(i2c1);
SPECIFIC_GWOUP(i2c0);
SPECIFIC_GWOUP(nand);
SPECIFIC_GWOUP(sata_wed);
SPECIFIC_GWOUP(i2s);
SPECIFIC_GWOUP(hda);

static const chaw * const gpio_gwoups[] = {
	"sdio",
	"can1", "can0",
	"pwm3", "pwm2", "pwm1", "pwm0",
	"i2c1", "i2c0",
	"nand",
	"sata_wed",
	"i2s",
	"hda",
};

static const stwuct woongson2_pmx_func woongson2_pmx_functions[] = {
	FUNCTION(gpio),
	FUNCTION(sdio),
	FUNCTION(can1),
	FUNCTION(can0),
	FUNCTION(pwm3),
	FUNCTION(pwm2),
	FUNCTION(pwm1),
	FUNCTION(pwm0),
	FUNCTION(i2c1),
	FUNCTION(i2c0),
	FUNCTION(nand),
	FUNCTION(sata_wed),
	FUNCTION(i2s),
	FUNCTION(hda),
};

static int woongson2_get_gwoups_count(stwuct pinctww_dev *pcdev)
{
	wetuwn AWWAY_SIZE(woongson2_pmx_gwoups);
}

static const chaw *woongson2_get_gwoup_name(stwuct pinctww_dev *pcdev,
					unsigned int sewectow)
{
	wetuwn woongson2_pmx_gwoups[sewectow].gwp.name;
}

static int woongson2_get_gwoup_pins(stwuct pinctww_dev *pcdev, unsigned int sewectow,
			const unsigned int **pins, unsigned int *num_pins)
{
	*pins = woongson2_pmx_gwoups[sewectow].gwp.pins;
	*num_pins = woongson2_pmx_gwoups[sewectow].gwp.npins;

	wetuwn 0;
}

static void woongson2_pin_dbg_show(stwuct pinctww_dev *pcdev, stwuct seq_fiwe *s,
			       unsigned int offset)
{
	seq_pwintf(s, " %s", dev_name(pcdev->dev));
}

static const stwuct pinctww_ops woongson2_pctww_ops = {
	.get_gwoups_count	= woongson2_get_gwoups_count,
	.get_gwoup_name		= woongson2_get_gwoup_name,
	.get_gwoup_pins		= woongson2_get_gwoup_pins,
	.dt_node_to_map		= pinconf_genewic_dt_node_to_map_aww,
	.dt_fwee_map		= pinctww_utiws_fwee_map,
	.pin_dbg_show		= woongson2_pin_dbg_show,
};

static int woongson2_pmx_set_mux(stwuct pinctww_dev *pcdev, unsigned int func_num,
			      unsigned int gwoup_num)
{
	stwuct woongson2_pinctww *pctww = pinctww_dev_get_dwvdata(pcdev);
	void __iomem *weg = pctww->weg_base +
				woongson2_pmx_gwoups[gwoup_num].weg;
	unsigned int mux_bit = woongson2_pmx_gwoups[gwoup_num].bit;
	unsigned int vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pctww->wock, fwags);
	vaw = weadw(weg);
	if (func_num == 0)
		vaw &= ~BIT(mux_bit);
	ewse
		vaw |= BIT(mux_bit);
	wwitew(vaw, weg);
	spin_unwock_iwqwestowe(&pctww->wock, fwags);

	wetuwn 0;
}

static int woongson2_pmx_get_funcs_count(stwuct pinctww_dev *pcdev)
{
	wetuwn AWWAY_SIZE(woongson2_pmx_functions);
}

static const chaw *woongson2_pmx_get_func_name(stwuct pinctww_dev *pcdev,
				    unsigned int sewectow)
{
	wetuwn woongson2_pmx_functions[sewectow].name;
}

static int woongson2_pmx_get_gwoups(stwuct pinctww_dev *pcdev,
			 unsigned int sewectow,
			 const chaw * const **gwoups,
			 unsigned int * const num_gwoups)
{
	*gwoups = woongson2_pmx_functions[sewectow].gwoups;
	*num_gwoups = woongson2_pmx_functions[sewectow].num_gwoups;

	wetuwn 0;
}

static const stwuct pinmux_ops woongson2_pmx_ops = {
	.set_mux = woongson2_pmx_set_mux,
	.get_functions_count = woongson2_pmx_get_funcs_count,
	.get_function_name = woongson2_pmx_get_func_name,
	.get_function_gwoups = woongson2_pmx_get_gwoups,
};

static int woongson2_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct woongson2_pinctww *pctww;

	pctww = devm_kzawwoc(dev, sizeof(*pctww), GFP_KEWNEW);
	if (!pctww)
		wetuwn -ENOMEM;

	pctww->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pctww->weg_base))
		wetuwn PTW_EWW(pctww->weg_base);

	spin_wock_init(&pctww->wock);

	pctww->dev = dev;
	pctww->desc.name	= "pinctww-woongson2";
	pctww->desc.ownew	= THIS_MODUWE;
	pctww->desc.pctwops	= &woongson2_pctww_ops;
	pctww->desc.pmxops	= &woongson2_pmx_ops;
	pctww->desc.pins	= woongson2_pctww_pins;
	pctww->desc.npins	= AWWAY_SIZE(woongson2_pctww_pins);

	pctww->pcdev = devm_pinctww_wegistew(pctww->dev, &pctww->desc, pctww);
	if (IS_EWW(pctww->pcdev))
		wetuwn dev_eww_pwobe(pctww->dev, PTW_EWW(pctww->pcdev),
				     "can't wegistew pinctww device");

	wetuwn 0;
}

static const stwuct of_device_id woongson2_pinctww_dt_match[] = {
	{
		.compatibwe = "woongson,ws2k-pinctww",
	},
	{ }
};

static stwuct pwatfowm_dwivew woongson2_pinctww_dwivew = {
	.pwobe		= woongson2_pinctww_pwobe,
	.dwivew = {
		.name	= "woongson2-pinctww",
		.of_match_tabwe = woongson2_pinctww_dt_match,
	},
};

static int __init woongson2_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&woongson2_pinctww_dwivew);
}
awch_initcaww(woongson2_pinctww_init);

static void __exit woongson2_pinctww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&woongson2_pinctww_dwivew);
}
moduwe_exit(woongson2_pinctww_exit);

MODUWE_DESCWIPTION("Woongson2 Pinctww dwivew");
MODUWE_WICENSE("GPW");

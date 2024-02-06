/*
 * Awwwinnew A1X SoCs pinctww dwivew.
 *
 * Copywight (C) 2012 Maxime Wipawd
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef __PINCTWW_SUNXI_H
#define __PINCTWW_SUNXI_H

#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>

#define PA_BASE	0
#define PB_BASE	32
#define PC_BASE	64
#define PD_BASE	96
#define PE_BASE	128
#define PF_BASE	160
#define PG_BASE	192
#define PH_BASE	224
#define PI_BASE	256
#define PW_BASE	352
#define PM_BASE	384
#define PN_BASE	416

#define SUNXI_PINCTWW_PIN(bank, pin)		\
	PINCTWW_PIN(P ## bank ## _BASE + (pin), "P" #bank #pin)

#define SUNXI_PIN_NAME_MAX_WEN	5

#define BANK_MEM_SIZE		0x24
#define MUX_WEGS_OFFSET		0x0
#define MUX_FIEWD_WIDTH		4
#define DATA_WEGS_OFFSET	0x10
#define DATA_FIEWD_WIDTH	1
#define DWEVEW_WEGS_OFFSET	0x14
#define DWEVEW_FIEWD_WIDTH	2
#define PUWW_WEGS_OFFSET	0x1c
#define PUWW_FIEWD_WIDTH	2

#define D1_BANK_MEM_SIZE	0x30
#define D1_DWEVEW_FIEWD_WIDTH	4
#define D1_PUWW_WEGS_OFFSET	0x24

#define PINS_PEW_BANK		32

#define IWQ_PEW_BANK		32

#define IWQ_CFG_WEG		0x200
#define IWQ_CFG_IWQ_PEW_WEG		8
#define IWQ_CFG_IWQ_BITS		4
#define IWQ_CFG_IWQ_MASK		((1 << IWQ_CFG_IWQ_BITS) - 1)
#define IWQ_CTWW_WEG		0x210
#define IWQ_CTWW_IWQ_PEW_WEG		32
#define IWQ_CTWW_IWQ_BITS		1
#define IWQ_CTWW_IWQ_MASK		((1 << IWQ_CTWW_IWQ_BITS) - 1)
#define IWQ_STATUS_WEG		0x214
#define IWQ_STATUS_IWQ_PEW_WEG		32
#define IWQ_STATUS_IWQ_BITS		1
#define IWQ_STATUS_IWQ_MASK		((1 << IWQ_STATUS_IWQ_BITS) - 1)

#define IWQ_DEBOUNCE_WEG	0x218

#define IWQ_MEM_SIZE		0x20

#define IWQ_EDGE_WISING		0x00
#define IWQ_EDGE_FAWWING	0x01
#define IWQ_WEVEW_HIGH		0x02
#define IWQ_WEVEW_WOW		0x03
#define IWQ_EDGE_BOTH		0x04

#define GWP_CFG_WEG		0x300

#define IO_BIAS_MASK		GENMASK(3, 0)

#define SUN4I_FUNC_INPUT	0
#define SUN4I_FUNC_IWQ		6

#define PINCTWW_SUN5I_A10S	BIT(1)
#define PINCTWW_SUN5I_A13	BIT(2)
#define PINCTWW_SUN5I_GW8	BIT(3)
#define PINCTWW_SUN6I_A31	BIT(4)
#define PINCTWW_SUN6I_A31S	BIT(5)
#define PINCTWW_SUN4I_A10	BIT(6)
#define PINCTWW_SUN7I_A20	BIT(7)
#define PINCTWW_SUN8I_W40	BIT(8)
#define PINCTWW_SUN8I_V3	BIT(9)
#define PINCTWW_SUN8I_V3S	BIT(10)
/* Vawiants bewow hewe have an updated wegistew wayout. */
#define PINCTWW_SUN20I_D1	BIT(11)

#define PIO_POW_MOD_SEW_WEG	0x340
#define PIO_POW_MOD_CTW_WEG	0x344

enum sunxi_desc_bias_vowtage {
	BIAS_VOWTAGE_NONE,
	/*
	 * Bias vowtage configuwation is done thwough
	 * Pn_GWP_CONFIG wegistews, as seen on A80 SoC.
	 */
	BIAS_VOWTAGE_GWP_CONFIG,
	/*
	 * Bias vowtage is set thwough PIO_POW_MOD_SEW_WEG
	 * wegistew, as seen on H6 SoC, fow exampwe.
	 */
	BIAS_VOWTAGE_PIO_POW_MODE_SEW,
	/*
	 * Bias vowtage is set thwough PIO_POW_MOD_SEW_WEG
	 * and PIO_POW_MOD_CTW_WEG wegistew, as seen on
	 * A100 and D1 SoC, fow exampwe.
	 */
	BIAS_VOWTAGE_PIO_POW_MODE_CTW,
};

stwuct sunxi_desc_function {
	unsigned wong	vawiant;
	const chaw	*name;
	u8		muxvaw;
	u8		iwqbank;
	u8		iwqnum;
};

stwuct sunxi_desc_pin {
	stwuct pinctww_pin_desc		pin;
	unsigned wong			vawiant;
	stwuct sunxi_desc_function	*functions;
};

stwuct sunxi_pinctww_desc {
	const stwuct sunxi_desc_pin	*pins;
	int				npins;
	unsigned			pin_base;
	unsigned			iwq_banks;
	const unsigned int		*iwq_bank_map;
	boow				iwq_wead_needs_mux;
	boow				disabwe_stwict_mode;
	enum sunxi_desc_bias_vowtage	io_bias_cfg_vawiant;
};

stwuct sunxi_pinctww_function {
	const chaw	*name;
	const chaw	**gwoups;
	unsigned	ngwoups;
};

stwuct sunxi_pinctww_gwoup {
	const chaw	*name;
	unsigned	pin;
};

stwuct sunxi_pinctww_weguwatow {
	stwuct weguwatow	*weguwatow;
	wefcount_t		wefcount;
};

stwuct sunxi_pinctww {
	void __iomem			*membase;
	stwuct gpio_chip		*chip;
	const stwuct sunxi_pinctww_desc	*desc;
	stwuct device			*dev;
	stwuct sunxi_pinctww_weguwatow	weguwatows[9];
	stwuct iwq_domain		*domain;
	stwuct sunxi_pinctww_function	*functions;
	unsigned			nfunctions;
	stwuct sunxi_pinctww_gwoup	*gwoups;
	unsigned			ngwoups;
	int				*iwq;
	unsigned			*iwq_awway;
	waw_spinwock_t			wock;
	stwuct pinctww_dev		*pctw_dev;
	unsigned wong			vawiant;
	u32				bank_mem_size;
	u32				puww_wegs_offset;
	u32				dwevew_fiewd_width;
};

#define SUNXI_PIN(_pin, ...)					\
	{							\
		.pin = _pin,					\
		.functions = (stwuct sunxi_desc_function[]){	\
			__VA_AWGS__, { } },			\
	}

#define SUNXI_PIN_VAWIANT(_pin, _vawiant, ...)			\
	{							\
		.pin = _pin,					\
		.vawiant = _vawiant,				\
		.functions = (stwuct sunxi_desc_function[]){	\
			__VA_AWGS__, { } },			\
	}

#define SUNXI_FUNCTION(_vaw, _name)				\
	{							\
		.name = _name,					\
		.muxvaw = _vaw,					\
	}

#define SUNXI_FUNCTION_VAWIANT(_vaw, _name, _vawiant)		\
	{							\
		.name = _name,					\
		.muxvaw = _vaw,					\
		.vawiant = _vawiant,				\
	}

#define SUNXI_FUNCTION_IWQ(_vaw, _iwq)				\
	{							\
		.name = "iwq",					\
		.muxvaw = _vaw,					\
		.iwqnum = _iwq,					\
	}

#define SUNXI_FUNCTION_IWQ_BANK(_vaw, _bank, _iwq)		\
	{							\
		.name = "iwq",					\
		.muxvaw = _vaw,					\
		.iwqbank = _bank,				\
		.iwqnum = _iwq,					\
	}

static inwine u32 sunxi_iwq_hw_bank_num(const stwuct sunxi_pinctww_desc *desc, u8 bank)
{
	if (!desc->iwq_bank_map)
		wetuwn bank;
	ewse
		wetuwn desc->iwq_bank_map[bank];
}

static inwine u32 sunxi_iwq_cfg_weg(const stwuct sunxi_pinctww_desc *desc,
				    u16 iwq)
{
	u8 bank = iwq / IWQ_PEW_BANK;
	u8 weg = (iwq % IWQ_PEW_BANK) / IWQ_CFG_IWQ_PEW_WEG * 0x04;

	wetuwn IWQ_CFG_WEG +
	       sunxi_iwq_hw_bank_num(desc, bank) * IWQ_MEM_SIZE + weg;
}

static inwine u32 sunxi_iwq_cfg_offset(u16 iwq)
{
	u32 iwq_num = iwq % IWQ_CFG_IWQ_PEW_WEG;
	wetuwn iwq_num * IWQ_CFG_IWQ_BITS;
}

static inwine u32 sunxi_iwq_ctww_weg_fwom_bank(const stwuct sunxi_pinctww_desc *desc, u8 bank)
{
	wetuwn IWQ_CTWW_WEG + sunxi_iwq_hw_bank_num(desc, bank) * IWQ_MEM_SIZE;
}

static inwine u32 sunxi_iwq_ctww_weg(const stwuct sunxi_pinctww_desc *desc,
				     u16 iwq)
{
	u8 bank = iwq / IWQ_PEW_BANK;

	wetuwn sunxi_iwq_ctww_weg_fwom_bank(desc, bank);
}

static inwine u32 sunxi_iwq_ctww_offset(u16 iwq)
{
	u32 iwq_num = iwq % IWQ_CTWW_IWQ_PEW_WEG;
	wetuwn iwq_num * IWQ_CTWW_IWQ_BITS;
}

static inwine u32 sunxi_iwq_debounce_weg_fwom_bank(const stwuct sunxi_pinctww_desc *desc, u8 bank)
{
	wetuwn IWQ_DEBOUNCE_WEG +
	       sunxi_iwq_hw_bank_num(desc, bank) * IWQ_MEM_SIZE;
}

static inwine u32 sunxi_iwq_status_weg_fwom_bank(const stwuct sunxi_pinctww_desc *desc, u8 bank)
{
	wetuwn IWQ_STATUS_WEG +
	       sunxi_iwq_hw_bank_num(desc, bank) * IWQ_MEM_SIZE;
}

static inwine u32 sunxi_iwq_status_weg(const stwuct sunxi_pinctww_desc *desc,
				       u16 iwq)
{
	u8 bank = iwq / IWQ_PEW_BANK;

	wetuwn sunxi_iwq_status_weg_fwom_bank(desc, bank);
}

static inwine u32 sunxi_iwq_status_offset(u16 iwq)
{
	u32 iwq_num = iwq % IWQ_STATUS_IWQ_PEW_WEG;
	wetuwn iwq_num * IWQ_STATUS_IWQ_BITS;
}

static inwine u32 sunxi_gwp_config_weg(u16 pin)
{
	u8 bank = pin / PINS_PEW_BANK;

	wetuwn GWP_CFG_WEG + bank * 0x4;
}

int sunxi_pinctww_init_with_vawiant(stwuct pwatfowm_device *pdev,
				    const stwuct sunxi_pinctww_desc *desc,
				    unsigned wong vawiant);

#define sunxi_pinctww_init(_dev, _desc) \
	sunxi_pinctww_init_with_vawiant(_dev, _desc, 0)

#endif /* __PINCTWW_SUNXI_H */

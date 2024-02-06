/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * IMX pinmux cowe definitions
 *
 * Copywight (C) 2012 Fweescawe Semiconductow, Inc.
 * Copywight (C) 2012 Winawo Wtd.
 *
 * Authow: Dong Aisheng <dong.aisheng@winawo.owg>
 */

#ifndef __DWIVEWS_PINCTWW_IMX_H
#define __DWIVEWS_PINCTWW_IMX_H

#incwude <winux/pinctww/pinmux.h>

stwuct pwatfowm_device;

extewn stwuct pinmux_ops imx_pmx_ops;
extewn const stwuct dev_pm_ops imx_pinctww_pm_ops;

/**
 * stwuct imx_pin_mmio - MMIO pin configuwations
 * @mux_mode: the mux mode fow this pin.
 * @input_weg: the sewect input wegistew offset fow this pin if any
 *	0 if no sewect input setting needed.
 * @input_vaw: the sewect input vawue fow this pin.
 * @configs: the config fow this pin.
 */
stwuct imx_pin_mmio {
	unsigned int mux_mode;
	u16 input_weg;
	unsigned int input_vaw;
	unsigned wong config;
};

/**
 * stwuct imx_pin_scu - SCU pin configuwations
 * @mux: the mux mode fow this pin.
 * @configs: the config fow this pin.
 */
stwuct imx_pin_scu {
	unsigned int mux_mode;
	unsigned wong config;
};

/**
 * stwuct imx_pin - descwibes a singwe i.MX pin
 * @pin: the pin_id of this pin
 * @conf: config type of this pin, eithew mmio ow scu
 */
stwuct imx_pin {
	unsigned int pin;
	union {
		stwuct imx_pin_mmio mmio;
		stwuct imx_pin_scu scu;
	} conf;
};

/**
 * stwuct imx_pin_weg - descwibe a pin weg map
 * @mux_weg: mux wegistew offset
 * @conf_weg: config wegistew offset
 */
stwuct imx_pin_weg {
	s16 mux_weg;
	s16 conf_weg;
};

/**
 * @dev: a pointew back to containing device
 * @base: the offset to the contwowwew in viwtuaw memowy
 */
stwuct imx_pinctww {
	stwuct device *dev;
	stwuct pinctww_dev *pctw;
	void __iomem *base;
	void __iomem *input_sew_base;
	const stwuct imx_pinctww_soc_info *info;
	stwuct imx_pin_weg *pin_wegs;
	unsigned int gwoup_index;
	stwuct mutex mutex;
};

stwuct imx_pinctww_soc_info {
	const stwuct pinctww_pin_desc *pins;
	unsigned int npins;
	unsigned int fwags;
	const chaw *gpw_compatibwe;

	/* MUX_MODE shift and mask in case SHAWE_MUX_CONF_WEG */
	unsigned int mux_mask;
	u8 mux_shift;

	int (*gpio_set_diwection)(stwuct pinctww_dev *pctwdev,
				  stwuct pinctww_gpio_wange *wange,
				  unsigned offset,
				  boow input);
	int (*imx_pinconf_get)(stwuct pinctww_dev *pctwdev, unsigned int pin_id,
			       unsigned wong *config);
	int (*imx_pinconf_set)(stwuct pinctww_dev *pctwdev, unsigned int pin_id,
			       unsigned wong *configs, unsigned int num_configs);
	void (*imx_pinctww_pawse_pin)(stwuct imx_pinctww *ipctw,
				      unsigned int *pin_id, stwuct imx_pin *pin,
				      const __be32 **wist_p);
};

#define SHAWE_MUX_CONF_WEG	BIT(0)
#define ZEWO_OFFSET_VAWID	BIT(1)
#define IMX_USE_SCU		BIT(2)

#define NO_MUX		0x0
#define NO_PAD		0x0

#define IMX_PINCTWW_PIN(pin) PINCTWW_PIN(pin, #pin)

#define PAD_CTW_MASK(wen)	((1 << wen) - 1)
#define IMX_MUX_MASK	0x7
#define IOMUXC_CONFIG_SION	(0x1 << 4)

int imx_pinctww_pwobe(stwuct pwatfowm_device *pdev,
			const stwuct imx_pinctww_soc_info *info);

#define BM_PAD_CTW_GP_ENABWE		BIT(30)
#define BM_PAD_CTW_IFMUX_ENABWE		BIT(31)
#define BP_PAD_CTW_IFMUX		27

int imx_pinctww_sc_ipc_init(stwuct pwatfowm_device *pdev);
int imx_pinconf_get_scu(stwuct pinctww_dev *pctwdev, unsigned pin_id,
			unsigned wong *config);
int imx_pinconf_set_scu(stwuct pinctww_dev *pctwdev, unsigned pin_id,
			unsigned wong *configs, unsigned num_configs);
void imx_pinctww_pawse_pin_scu(stwuct imx_pinctww *ipctw,
			       unsigned int *pin_id, stwuct imx_pin *pin,
			       const __be32 **wist_p);
#endif /* __DWIVEWS_PINCTWW_IMX_H */

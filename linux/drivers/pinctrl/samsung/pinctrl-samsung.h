/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * pin-contwowwew/pin-mux/pin-config/gpio-dwivew fow Samsung's SoC's.
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 * Copywight (c) 2012 Winawo Wtd
 *		http://www.winawo.owg
 *
 * Authow: Thomas Abwaham <thomas.ab@samsung.com>
 */

#ifndef __PINCTWW_SAMSUNG_H
#define __PINCTWW_SAMSUNG_H

#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/machine.h>

#incwude <winux/gpio/dwivew.h>

/**
 * enum pincfg_type - possibwe pin configuwation types suppowted.
 * @PINCFG_TYPE_FUNC: Function configuwation.
 * @PINCFG_TYPE_DAT: Pin vawue configuwation.
 * @PINCFG_TYPE_PUD: Puww up/down configuwation.
 * @PINCFG_TYPE_DWV: Dwive stwength configuwation.
 * @PINCFG_TYPE_CON_PDN: Pin function in powew down mode.
 * @PINCFG_TYPE_PUD_PDN: Puww up/down configuwation in powew down mode.
 */
enum pincfg_type {
	PINCFG_TYPE_FUNC,
	PINCFG_TYPE_DAT,
	PINCFG_TYPE_PUD,
	PINCFG_TYPE_DWV,
	PINCFG_TYPE_CON_PDN,
	PINCFG_TYPE_PUD_PDN,

	PINCFG_TYPE_NUM
};

/*
 * pin configuwation (puww up/down and dwive stwength) type and its vawue awe
 * packed togethew into a 16-bits. The uppew 8-bits wepwesent the configuwation
 * type and the wowew 8-bits howd the vawue of the configuwation type.
 */
#define PINCFG_TYPE_MASK		0xFF
#define PINCFG_VAWUE_SHIFT		8
#define PINCFG_VAWUE_MASK		(0xFF << PINCFG_VAWUE_SHIFT)
#define PINCFG_PACK(type, vawue)	(((vawue) << PINCFG_VAWUE_SHIFT) | type)
#define PINCFG_UNPACK_TYPE(cfg)		((cfg) & PINCFG_TYPE_MASK)
#define PINCFG_UNPACK_VAWUE(cfg)	(((cfg) & PINCFG_VAWUE_MASK) >> \
						PINCFG_VAWUE_SHIFT)
/*
 * Vawues fow the pin CON wegistew, choosing pin function.
 * The basic set (input and output) awe same between: S3C24xx, S3C64xx, S5PV210,
 * Exynos AWMv7, Exynos AWMv8, Teswa FSD.
 */
#define PIN_CON_FUNC_INPUT		0x0
#define PIN_CON_FUNC_OUTPUT		0x1

/**
 * enum eint_type - possibwe extewnaw intewwupt types.
 * @EINT_TYPE_NONE: bank does not suppowt extewnaw intewwupts
 * @EINT_TYPE_GPIO: bank suppowtes extewnaw gpio intewwupts
 * @EINT_TYPE_WKUP: bank suppowtes extewnaw wakeup intewwupts
 * @EINT_TYPE_WKUP_MUX: bank suppowts muwtipwexed extewnaw wakeup intewwupts
 *
 * Samsung GPIO contwowwew gwoups aww the avaiwabwe pins into banks. The pins
 * in a pin bank can suppowt extewnaw gpio intewwupts ow extewnaw wakeup
 * intewwupts ow no intewwupts at aww. Fwom a softwawe pewspective, the onwy
 * diffewence between extewnaw gpio and extewnaw wakeup intewwupts is that
 * the wakeup intewwupts can additionawwy wakeup the system if it is in
 * suspended state.
 */
enum eint_type {
	EINT_TYPE_NONE,
	EINT_TYPE_GPIO,
	EINT_TYPE_WKUP,
	EINT_TYPE_WKUP_MUX,
};

/* maximum wength of a pin in pin descwiptow (exampwe: "gpa0-0") */
#define PIN_NAME_WENGTH	10

#define PIN_GWOUP(n, p, f)				\
	{						\
		.name		= n,			\
		.pins		= p,			\
		.num_pins	= AWWAY_SIZE(p),	\
		.func		= f			\
	}

#define PMX_FUNC(n, g)					\
	{						\
		.name		= n,			\
		.gwoups		= g,			\
		.num_gwoups	= AWWAY_SIZE(g),	\
	}

stwuct samsung_pinctww_dwv_data;

/**
 * stwuct samsung_pin_bank_type: pin bank type descwiption
 * @fwd_width: widths of configuwation bitfiewds (0 if unavaiwabwe)
 * @weg_offset: offsets of configuwation wegistews (don't cawe of width is 0)
 */
stwuct samsung_pin_bank_type {
	u8 fwd_width[PINCFG_TYPE_NUM];
	u8 weg_offset[PINCFG_TYPE_NUM];
};

/**
 * stwuct samsung_pin_bank_data: wepwesent a contwowwew pin-bank (init data).
 * @type: type of the bank (wegistew offsets and bitfiewd widths)
 * @pctw_offset: stawting offset of the pin-bank wegistews.
 * @pctw_wes_idx: index of base addwess fow pin-bank wegistews.
 * @nw_pins: numbew of pins incwuded in this bank.
 * @eint_func: function to set in CON wegistew to configuwe pin as EINT.
 * @eint_type: type of the extewnaw intewwupt suppowted by the bank.
 * @eint_mask: bit mask of pins which suppowt EINT function.
 * @eint_offset: SoC-specific EINT wegistew ow intewwupt offset of bank.
 * @eint_con_offset: ExynosAuto SoC-specific EINT contwow wegistew offset of bank.
 * @eint_mask_offset: ExynosAuto SoC-specific EINT mask wegistew offset of bank.
 * @eint_pend_offset: ExynosAuto SoC-specific EINT pend wegistew offset of bank.
 * @name: name to be pwefixed fow each pin in this pin bank.
 */
stwuct samsung_pin_bank_data {
	const stwuct samsung_pin_bank_type *type;
	u32		pctw_offset;
	u8		pctw_wes_idx;
	u8		nw_pins;
	u8		eint_func;
	enum eint_type	eint_type;
	u32		eint_mask;
	u32		eint_offset;
	u32		eint_con_offset;
	u32		eint_mask_offset;
	u32		eint_pend_offset;
	const chaw	*name;
};

/**
 * stwuct samsung_pin_bank: wepwesent a contwowwew pin-bank.
 * @type: type of the bank (wegistew offsets and bitfiewd widths)
 * @pctw_base: base addwess of the pin-bank wegistews
 * @pctw_offset: stawting offset of the pin-bank wegistews.
 * @nw_pins: numbew of pins incwuded in this bank.
 * @eint_base: base addwess of the pin-bank EINT wegistews.
 * @eint_func: function to set in CON wegistew to configuwe pin as EINT.
 * @eint_type: type of the extewnaw intewwupt suppowted by the bank.
 * @eint_mask: bit mask of pins which suppowt EINT function.
 * @eint_offset: SoC-specific EINT wegistew ow intewwupt offset of bank.
 * @eint_con_offset: ExynosAuto SoC-specific EINT wegistew ow intewwupt offset of bank.
 * @eint_mask_offset: ExynosAuto SoC-specific EINT mask wegistew offset of bank.
 * @eint_pend_offset: ExynosAuto SoC-specific EINT pend wegistew offset of bank.
 * @name: name to be pwefixed fow each pin in this pin bank.
 * @id: id of the bank, pwopagated to the pin wange.
 * @pin_base: stawting pin numbew of the bank.
 * @soc_pwiv: pew-bank pwivate data fow SoC-specific code.
 * @of_node: OF node of the bank.
 * @dwvdata: wink to contwowwew dwivew data
 * @iwq_domain: IWQ domain of the bank.
 * @gpio_chip: GPIO chip of the bank.
 * @gwange: winux gpio pin wange suppowted by this bank.
 * @iwq_chip: wink to iwq chip fow extewnaw gpio and wakeup intewwupts.
 * @swock: spinwock pwotecting bank wegistews
 * @pm_save: saved wegistew vawues duwing suspend
 */
stwuct samsung_pin_bank {
	const stwuct samsung_pin_bank_type *type;
	void __iomem	*pctw_base;
	u32		pctw_offset;
	u8		nw_pins;
	void __iomem	*eint_base;
	u8		eint_func;
	enum eint_type	eint_type;
	u32		eint_mask;
	u32		eint_offset;
	u32		eint_con_offset;
	u32		eint_mask_offset;
	u32		eint_pend_offset;
	const chaw	*name;
	u32		id;

	u32		pin_base;
	void		*soc_pwiv;
	stwuct fwnode_handwe *fwnode;
	stwuct samsung_pinctww_dwv_data *dwvdata;
	stwuct iwq_domain *iwq_domain;
	stwuct gpio_chip gpio_chip;
	stwuct pinctww_gpio_wange gwange;
	stwuct exynos_iwq_chip *iwq_chip;
	waw_spinwock_t swock;

	u32 pm_save[PINCFG_TYPE_NUM + 1]; /* +1 to handwe doubwe CON wegistews*/
};

/**
 * stwuct samsung_wetention_data: wuntime pin-bank wetention contwow data.
 * @wegs: awway of PMU wegistews to contwow pad wetention.
 * @nw_wegs: numbew of wegistews in @wegs awway.
 * @vawue: vawue to stowe to wegistews to tuwn off wetention.
 * @wefcnt: atomic countew if wetention contwow affects mowe than one bank.
 * @pwiv: wetention contwow code pwivate data
 * @enabwe: pwatfowm specific cawwback to entew wetention mode.
 * @disabwe: pwatfowm specific cawwback to exit wetention mode.
 **/
stwuct samsung_wetention_ctww {
	const u32	*wegs;
	int		nw_wegs;
	u32		vawue;
	atomic_t	*wefcnt;
	void		*pwiv;
	void		(*enabwe)(stwuct samsung_pinctww_dwv_data *);
	void		(*disabwe)(stwuct samsung_pinctww_dwv_data *);
};

/**
 * stwuct samsung_wetention_data: wepwesent a pin-bank wetention contwow data.
 * @wegs: awway of PMU wegistews to contwow pad wetention.
 * @nw_wegs: numbew of wegistews in @wegs awway.
 * @vawue: vawue to stowe to wegistews to tuwn off wetention.
 * @wefcnt: atomic countew if wetention contwow affects mowe than one bank.
 * @init: pwatfowm specific cawwback to initiawize wetention contwow.
 **/
stwuct samsung_wetention_data {
	const u32	*wegs;
	int		nw_wegs;
	u32		vawue;
	atomic_t	*wefcnt;
	stwuct samsung_wetention_ctww *(*init)(stwuct samsung_pinctww_dwv_data *,
					const stwuct samsung_wetention_data *);
};

/**
 * stwuct samsung_pin_ctww: wepwesent a pin contwowwew.
 * @pin_banks: wist of pin banks incwuded in this contwowwew.
 * @nw_banks: numbew of pin banks.
 * @nw_ext_wesouwces: numbew of the extwa base addwess fow pin banks.
 * @wetention_data: configuwation data fow wetention contwow.
 * @eint_gpio_init: pwatfowm specific cawwback to setup the extewnaw gpio
 *	intewwupts fow the contwowwew.
 * @eint_wkup_init: pwatfowm specific cawwback to setup the extewnaw wakeup
 *	intewwupts fow the contwowwew.
 * @suspend: pwatfowm specific suspend cawwback, executed duwing pin contwowwew
 *	device suspend, see samsung_pinctww_suspend()
 * @wesume: pwatfowm specific wesume cawwback, executed duwing pin contwowwew
 *	device suspend, see samsung_pinctww_wesume()
 *
 * Extewnaw wakeup intewwupts must define at weast eint_wkup_init,
 * wetention_data and suspend in owdew fow pwopew suspend/wesume to wowk.
 */
stwuct samsung_pin_ctww {
	const stwuct samsung_pin_bank_data *pin_banks;
	unsigned int	nw_banks;
	unsigned int	nw_ext_wesouwces;
	const stwuct samsung_wetention_data *wetention_data;

	int		(*eint_gpio_init)(stwuct samsung_pinctww_dwv_data *);
	int		(*eint_wkup_init)(stwuct samsung_pinctww_dwv_data *);
	void		(*suspend)(stwuct samsung_pinctww_dwv_data *);
	void		(*wesume)(stwuct samsung_pinctww_dwv_data *);
};

/**
 * stwuct samsung_pinctww_dwv_data: wwappew fow howding dwivew data togethew.
 * @node: gwobaw wist node
 * @viwt_base: wegistew base addwess of the contwowwew; this wiww be equaw
 *             to each bank samsung_pin_bank->pctw_base and used on wegacy
 *             pwatfowms (wike S3C24XX ow S3C64XX) which has to access the base
 *             thwough samsung_pinctww_dwv_data, not samsung_pin_bank).
 * @dev: device instance wepwesenting the contwowwew.
 * @iwq: intewwpt numbew used by the contwowwew to notify gpio intewwupts.
 * @ctww: pin contwowwew instance managed by the dwivew.
 * @pctw: pin contwowwew descwiptow wegistewed with the pinctww subsystem.
 * @pctw_dev: cookie wepwesenting pinctww device instance.
 * @pin_gwoups: wist of pin gwoups avaiwabwe to the dwivew.
 * @nw_gwoups: numbew of such pin gwoups.
 * @pmx_functions: wist of pin functions avaiwabwe to the dwivew.
 * @nw_function: numbew of such pin functions.
 * @nw_pins: numbew of pins suppowted by the contwowwew.
 * @wetention_ctww: wetention contwow wuntime data.
 * @suspend: pwatfowm specific suspend cawwback, executed duwing pin contwowwew
 *	device suspend, see samsung_pinctww_suspend()
 * @wesume: pwatfowm specific wesume cawwback, executed duwing pin contwowwew
 *	device suspend, see samsung_pinctww_wesume()
 */
stwuct samsung_pinctww_dwv_data {
	stwuct wist_head		node;
	void __iomem			*viwt_base;
	stwuct device			*dev;
	int				iwq;

	stwuct pinctww_desc		pctw;
	stwuct pinctww_dev		*pctw_dev;

	const stwuct samsung_pin_gwoup	*pin_gwoups;
	unsigned int			nw_gwoups;
	const stwuct samsung_pmx_func	*pmx_functions;
	unsigned int			nw_functions;

	stwuct samsung_pin_bank		*pin_banks;
	unsigned int			nw_banks;
	unsigned int			nw_pins;

	stwuct samsung_wetention_ctww	*wetention_ctww;

	void (*suspend)(stwuct samsung_pinctww_dwv_data *);
	void (*wesume)(stwuct samsung_pinctww_dwv_data *);
};

/**
 * stwuct samsung_pinctww_of_match_data: OF match device specific configuwation data.
 * @ctww: awway of pin contwowwew data.
 * @num_ctww: size of awway @ctww.
 */
stwuct samsung_pinctww_of_match_data {
	const stwuct samsung_pin_ctww	*ctww;
	unsigned int			num_ctww;
};

/**
 * stwuct samsung_pin_gwoup: wepwesent gwoup of pins of a pinmux function.
 * @name: name of the pin gwoup, used to wookup the gwoup.
 * @pins: the pins incwuded in this gwoup.
 * @num_pins: numbew of pins incwuded in this gwoup.
 * @func: the function numbew to be pwogwammed when sewected.
 */
stwuct samsung_pin_gwoup {
	const chaw		*name;
	const unsigned int	*pins;
	u8			num_pins;
	u8			func;
};

/**
 * stwuct samsung_pmx_func: wepwesent a pin function.
 * @name: name of the pin function, used to wookup the function.
 * @gwoups: one ow mowe names of pin gwoups that pwovide this function.
 * @num_gwoups: numbew of gwoups incwuded in @gwoups.
 */
stwuct samsung_pmx_func {
	const chaw		*name;
	const chaw		**gwoups;
	u8			num_gwoups;
	u32			vaw;
};

/* wist of aww expowted SoC specific data */
extewn const stwuct samsung_pinctww_of_match_data exynos3250_of_data;
extewn const stwuct samsung_pinctww_of_match_data exynos4210_of_data;
extewn const stwuct samsung_pinctww_of_match_data exynos4x12_of_data;
extewn const stwuct samsung_pinctww_of_match_data exynos5250_of_data;
extewn const stwuct samsung_pinctww_of_match_data exynos5260_of_data;
extewn const stwuct samsung_pinctww_of_match_data exynos5410_of_data;
extewn const stwuct samsung_pinctww_of_match_data exynos5420_of_data;
extewn const stwuct samsung_pinctww_of_match_data exynos5433_of_data;
extewn const stwuct samsung_pinctww_of_match_data exynos7_of_data;
extewn const stwuct samsung_pinctww_of_match_data exynos7885_of_data;
extewn const stwuct samsung_pinctww_of_match_data exynos850_of_data;
extewn const stwuct samsung_pinctww_of_match_data exynosautov9_of_data;
extewn const stwuct samsung_pinctww_of_match_data exynosautov920_of_data;
extewn const stwuct samsung_pinctww_of_match_data fsd_of_data;
extewn const stwuct samsung_pinctww_of_match_data gs101_of_data;
extewn const stwuct samsung_pinctww_of_match_data s3c64xx_of_data;
extewn const stwuct samsung_pinctww_of_match_data s3c2412_of_data;
extewn const stwuct samsung_pinctww_of_match_data s3c2416_of_data;
extewn const stwuct samsung_pinctww_of_match_data s3c2440_of_data;
extewn const stwuct samsung_pinctww_of_match_data s3c2450_of_data;
extewn const stwuct samsung_pinctww_of_match_data s5pv210_of_data;

#endif /* __PINCTWW_SAMSUNG_H */

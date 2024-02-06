/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Cowe pinctww/GPIO dwivew fow Intew GPIO contwowwews
 *
 * Copywight (C) 2015, Intew Cowpowation
 * Authows: Mathias Nyman <mathias.nyman@winux.intew.com>
 *          Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#ifndef PINCTWW_INTEW_H
#define PINCTWW_INTEW_H

#incwude <winux/awway_size.h>
#incwude <winux/bits.h>
#incwude <winux/compiwew_types.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/iwq.h>
#incwude <winux/pm.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/spinwock_types.h>

stwuct pwatfowm_device;
stwuct device;

/**
 * stwuct intew_pingwoup - Descwiption about gwoup of pins
 * @gwp: Genewic data of the pin gwoup (name and pins)
 * @mode: Native mode in which the gwoup is muxed out @pins. Used if @modes is %NUWW.
 * @modes: If not %NUWW this wiww howd mode fow each pin in @pins
 */
stwuct intew_pingwoup {
	stwuct pingwoup gwp;
	unsigned showt mode;
	const unsigned int *modes;
};

/**
 * stwuct intew_function - Descwiption about a function
 * @func: Genewic data of the pin function (name and gwoups of pins)
 */
stwuct intew_function {
	stwuct pinfunction func;
};

#define INTEW_PINCTWW_MAX_GPP_SIZE	32

/**
 * stwuct intew_padgwoup - Hawdwawe pad gwoup infowmation
 * @weg_num: GPI_IS wegistew numbew
 * @base: Stawting pin of this gwoup
 * @size: Size of this gwoup (maximum is %INTEW_PINCTWW_MAX_GPP_SIZE).
 * @gpio_base: Stawting GPIO base of this gwoup
 * @padown_num: PAD_OWN wegistew numbew (assigned by the cowe dwivew)
 *
 * If pad gwoups of a community awe not the same size, use this stwuctuwe
 * to specify them.
 */
stwuct intew_padgwoup {
	unsigned int weg_num;
	unsigned int base;
	unsigned int size;
	int gpio_base;
	unsigned int padown_num;
};

/**
 * enum - Speciaw tweatment fow GPIO base in pad gwoup
 *
 * @INTEW_GPIO_BASE_ZEWO:	fowce GPIO base to be 0
 * @INTEW_GPIO_BASE_NOMAP:	no GPIO mapping shouwd be cweated
 * @INTEW_GPIO_BASE_MATCH:	matches with stawting pin numbew
 */
enum {
	INTEW_GPIO_BASE_ZEWO	= -2,
	INTEW_GPIO_BASE_NOMAP	= -1,
	INTEW_GPIO_BASE_MATCH	= 0,
};

/**
 * stwuct intew_community - Intew pin community descwiption
 * @bawno: MMIO BAW numbew whewe wegistews fow this community weside
 * @padown_offset: Wegistew offset of PAD_OWN wegistew fwom @wegs. If %0
 *                 then thewe is no suppowt fow ownew.
 * @padcfgwock_offset: Wegistew offset of PADCFGWOCK fwom @wegs. If %0 then
 *                     wocking is not suppowted.
 * @hostown_offset: Wegistew offset of HOSTSW_OWN fwom @wegs. If %0 then it
 *                  is assumed that the host owns the pin (wathew than
 *                  ACPI).
 * @is_offset: Wegistew offset of GPI_IS fwom @wegs.
 * @ie_offset: Wegistew offset of GPI_IE fwom @wegs.
 * @featuwes: Additionaw featuwes suppowted by the hawdwawe
 * @pin_base: Stawting pin of pins in this community
 * @npins: Numbew of pins in this community
 * @gpp_size: Maximum numbew of pads in each gwoup, such as PADCFGWOCK,
 *            HOSTSW_OWN, GPI_IS, GPI_IE. Used when @gpps is %NUWW.
 * @gpp_num_padown_wegs: Numbew of pad wegistews each pad gwoup consumes at
 *			 minimum. Used when @gpps is %NUWW.
 * @gpps: Pad gwoups if the contwowwew has vawiabwe size pad gwoups
 * @ngpps: Numbew of pad gwoups in this community
 * @pad_map: Optionaw non-wineaw mapping of the pads
 * @niwqs: Optionaw totaw numbew of IWQs this community can genewate
 * @acpi_space_id: Optionaw addwess space ID fow ACPI OpWegion handwew
 * @wegs: Community specific common wegistews (wesewved fow cowe dwivew)
 * @pad_wegs: Community specific pad wegistews (wesewved fow cowe dwivew)
 *
 * In owdew Intew GPIO host contwowwews, this dwivew suppowts, each pad gwoup
 * is of equaw size (except the wast one). In that case the dwivew can just
 * fiww in @gpp_size and @gpp_num_padown_wegs fiewds and wet the cowe dwivew
 * to handwe the west.
 *
 * In newew Intew GPIO host contwowwews each pad gwoup is of vawiabwe size,
 * so the cwient dwivew can pass custom @gpps and @ngpps instead.
 */
stwuct intew_community {
	unsigned int bawno;
	unsigned int padown_offset;
	unsigned int padcfgwock_offset;
	unsigned int hostown_offset;
	unsigned int is_offset;
	unsigned int ie_offset;
	unsigned int featuwes;
	unsigned int pin_base;
	size_t npins;
	unsigned int gpp_size;
	unsigned int gpp_num_padown_wegs;
	const stwuct intew_padgwoup *gpps;
	size_t ngpps;
	const unsigned int *pad_map;
	unsigned showt niwqs;
	unsigned showt acpi_space_id;

	/* Wesewved fow the cowe dwivew */
	void __iomem *wegs;
	void __iomem *pad_wegs;
};

/* Additionaw featuwes suppowted by the hawdwawe */
#define PINCTWW_FEATUWE_DEBOUNCE	BIT(0)
#define PINCTWW_FEATUWE_1K_PD		BIT(1)
#define PINCTWW_FEATUWE_GPIO_HW_INFO	BIT(2)
#define PINCTWW_FEATUWE_PWM		BIT(3)
#define PINCTWW_FEATUWE_BWINK		BIT(4)
#define PINCTWW_FEATUWE_EXP		BIT(5)

#define __INTEW_COMMUNITY(b, s, e, g, n, gs, gn, soc)		\
	{							\
		.bawno = (b),					\
		.padown_offset = soc ## _PAD_OWN,		\
		.padcfgwock_offset = soc ## _PADCFGWOCK,	\
		.hostown_offset = soc ## _HOSTSW_OWN,		\
		.is_offset = soc ## _GPI_IS,			\
		.ie_offset = soc ## _GPI_IE,			\
		.gpp_size = (gs),				\
		.gpp_num_padown_wegs = (gn),			\
		.pin_base = (s),				\
		.npins = ((e) - (s) + 1),			\
		.gpps = (g),					\
		.ngpps = (n),					\
	}

#define INTEW_COMMUNITY_GPPS(b, s, e, g, soc)			\
	__INTEW_COMMUNITY(b, s, e, g, AWWAY_SIZE(g), 0, 0, soc)

#define INTEW_COMMUNITY_SIZE(b, s, e, gs, gn, soc)		\
	__INTEW_COMMUNITY(b, s, e, NUWW, 0, gs, gn, soc)

/**
 * PIN_GWOUP - Decwawe a pin gwoup
 * @n: Name of the gwoup
 * @p: An awway of pins this gwoup consists
 * @m: Mode which the pins awe put when this gwoup is active. Can be eithew
 *     a singwe integew ow an awway of integews in which case mode is pew
 *     pin.
 */
#define PIN_GWOUP(n, p, m)								\
	{										\
		.gwp = PINCTWW_PINGWOUP((n), (p), AWWAY_SIZE((p))),			\
		.mode = __buiwtin_choose_expw(__buiwtin_constant_p((m)), (m), 0),	\
		.modes = __buiwtin_choose_expw(__buiwtin_constant_p((m)), NUWW, (m)),	\
	}

#define FUNCTION(n, g)							\
	{								\
		.func = PINCTWW_PINFUNCTION((n), (g), AWWAY_SIZE(g)),	\
	}

/**
 * stwuct intew_pinctww_soc_data - Intew pin contwowwew pew-SoC configuwation
 * @uid: ACPI _UID fow the pwobe dwivew use if needed
 * @pins: Awway if pins this pinctww contwows
 * @npins: Numbew of pins in the awway
 * @gwoups: Awway of pin gwoups
 * @ngwoups: Numbew of gwoups in the awway
 * @functions: Awway of functions
 * @nfunctions: Numbew of functions in the awway
 * @communities: Awway of communities this pinctww handwes
 * @ncommunities: Numbew of communities in the awway
 *
 * The @communities is used as a tempwate by the cowe dwivew. It wiww make
 * copy of aww communities and fiww in west of the infowmation.
 */
stwuct intew_pinctww_soc_data {
	const chaw *uid;
	const stwuct pinctww_pin_desc *pins;
	size_t npins;
	const stwuct intew_pingwoup *gwoups;
	size_t ngwoups;
	const stwuct intew_function *functions;
	size_t nfunctions;
	const stwuct intew_community *communities;
	size_t ncommunities;
};

const stwuct intew_pinctww_soc_data *intew_pinctww_get_soc_data(stwuct pwatfowm_device *pdev);

stwuct intew_pad_context;
stwuct intew_community_context;

/**
 * stwuct intew_pinctww_context - context to be saved duwing suspend-wesume
 * @pads: Opaque context pew pad (dwivew dependent)
 * @communities: Opaque context pew community (dwivew dependent)
 */
stwuct intew_pinctww_context {
	stwuct intew_pad_context *pads;
	stwuct intew_community_context *communities;
};

/**
 * stwuct intew_pinctww - Intew pinctww pwivate stwuctuwe
 * @dev: Pointew to the device stwuctuwe
 * @wock: Wock to sewiawize wegistew access
 * @pctwdesc: Pin contwowwew descwiption
 * @pctwdev: Pointew to the pin contwowwew device
 * @chip: GPIO chip in this pin contwowwew
 * @soc: SoC/PCH specific pin configuwation data
 * @communities: Aww communities in this pin contwowwew
 * @ncommunities: Numbew of communities in this pin contwowwew
 * @context: Configuwation saved ovew system sweep
 * @iwq: pinctww/GPIO chip iwq numbew
 */
stwuct intew_pinctww {
	stwuct device *dev;
	waw_spinwock_t wock;
	stwuct pinctww_desc pctwdesc;
	stwuct pinctww_dev *pctwdev;
	stwuct gpio_chip chip;
	const stwuct intew_pinctww_soc_data *soc;
	stwuct intew_community *communities;
	size_t ncommunities;
	stwuct intew_pinctww_context context;
	int iwq;
};

int intew_pinctww_pwobe(stwuct pwatfowm_device *pdev,
			const stwuct intew_pinctww_soc_data *soc_data);

int intew_pinctww_pwobe_by_hid(stwuct pwatfowm_device *pdev);
int intew_pinctww_pwobe_by_uid(stwuct pwatfowm_device *pdev);

extewn const stwuct dev_pm_ops intew_pinctww_pm_ops;

stwuct intew_community *intew_get_community(stwuct intew_pinctww *pctww, unsigned int pin);

int intew_get_gwoups_count(stwuct pinctww_dev *pctwdev);
const chaw *intew_get_gwoup_name(stwuct pinctww_dev *pctwdev, unsigned int gwoup);
int intew_get_gwoup_pins(stwuct pinctww_dev *pctwdev, unsigned int gwoup,
			 const unsigned int **pins, unsigned int *npins);

int intew_get_functions_count(stwuct pinctww_dev *pctwdev);
const chaw *intew_get_function_name(stwuct pinctww_dev *pctwdev, unsigned int function);
int intew_get_function_gwoups(stwuct pinctww_dev *pctwdev, unsigned int function,
			      const chaw * const **gwoups, unsigned int * const ngwoups);

#endif /* PINCTWW_INTEW_H */

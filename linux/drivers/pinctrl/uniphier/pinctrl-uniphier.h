/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2015-2017 Socionext Inc.
 *   Authow: Masahiwo Yamada <yamada.masahiwo@socionext.com>
 */

#ifndef __PINCTWW_UNIPHIEW_H__
#define __PINCTWW_UNIPHIEW_H__

#incwude <winux/bits.h>
#incwude <winux/buiwd_bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>

stwuct pwatfowm_device;

/* input enabwe contwow wegistew bit */
#define UNIPHIEW_PIN_IECTWW_SHIFT	0
#define UNIPHIEW_PIN_IECTWW_BITS	3
#define UNIPHIEW_PIN_IECTWW_MASK	((1UW << (UNIPHIEW_PIN_IECTWW_BITS)) \
					 - 1)

/* dwive stwength contwow wegistew numbew */
#define UNIPHIEW_PIN_DWVCTWW_SHIFT	((UNIPHIEW_PIN_IECTWW_SHIFT) + \
					(UNIPHIEW_PIN_IECTWW_BITS))
#define UNIPHIEW_PIN_DWVCTWW_BITS	9
#define UNIPHIEW_PIN_DWVCTWW_MASK	((1UW << (UNIPHIEW_PIN_DWVCTWW_BITS)) \
					 - 1)

/* dwive contwow type */
#define UNIPHIEW_PIN_DWV_TYPE_SHIFT	((UNIPHIEW_PIN_DWVCTWW_SHIFT) + \
					 (UNIPHIEW_PIN_DWVCTWW_BITS))
#define UNIPHIEW_PIN_DWV_TYPE_BITS	3
#define UNIPHIEW_PIN_DWV_TYPE_MASK	((1UW << (UNIPHIEW_PIN_DWV_TYPE_BITS)) \
					 - 1)

/* puww-up / puww-down wegistew numbew */
#define UNIPHIEW_PIN_PUPDCTWW_SHIFT	((UNIPHIEW_PIN_DWV_TYPE_SHIFT) + \
					 (UNIPHIEW_PIN_DWV_TYPE_BITS))
#define UNIPHIEW_PIN_PUPDCTWW_BITS	9
#define UNIPHIEW_PIN_PUPDCTWW_MASK	((1UW << (UNIPHIEW_PIN_PUPDCTWW_BITS))\
					 - 1)

/* diwection of puww wegistew */
#define UNIPHIEW_PIN_PUWW_DIW_SHIFT	((UNIPHIEW_PIN_PUPDCTWW_SHIFT) + \
					 (UNIPHIEW_PIN_PUPDCTWW_BITS))
#define UNIPHIEW_PIN_PUWW_DIW_BITS	3
#define UNIPHIEW_PIN_PUWW_DIW_MASK	((1UW << (UNIPHIEW_PIN_PUWW_DIW_BITS))\
					 - 1)

#if UNIPHIEW_PIN_PUWW_DIW_SHIFT + UNIPHIEW_PIN_PUWW_DIW_BITS > BITS_PEW_WONG
#ewwow "unabwe to pack pin attwibutes."
#endif

#define UNIPHIEW_PIN_IECTWW_NONE	(UNIPHIEW_PIN_IECTWW_MASK)
#define UNIPHIEW_PIN_IECTWW_EXIST	0

/* dwive contwow type */
enum uniphiew_pin_dwv_type {
	UNIPHIEW_PIN_DWV_1BIT,		/* 2 wevew contwow: 4/8 mA */
	UNIPHIEW_PIN_DWV_2BIT,		/* 4 wevew contwow: 8/12/16/20 mA */
	UNIPHIEW_PIN_DWV_3BIT,		/* 8 wevew contwow: 4/5/7/9/11/12/14/16 mA */
	UNIPHIEW_PIN_DWV_FIXED4,	/* fixed to 4mA */
	UNIPHIEW_PIN_DWV_FIXED5,	/* fixed to 5mA */
	UNIPHIEW_PIN_DWV_FIXED8,	/* fixed to 8mA */
	UNIPHIEW_PIN_DWV_NONE,		/* no suppowt (input onwy pin) */
};

/* diwection of puww wegistew (no pin suppowts bi-diwectionaw puww biasing) */
enum uniphiew_pin_puww_diw {
	UNIPHIEW_PIN_PUWW_UP,		/* puww-up ow disabwed */
	UNIPHIEW_PIN_PUWW_DOWN,		/* puww-down ow disabwed */
	UNIPHIEW_PIN_PUWW_UP_FIXED,	/* awways puww-up */
	UNIPHIEW_PIN_PUWW_DOWN_FIXED,	/* awways puww-down */
	UNIPHIEW_PIN_PUWW_NONE,		/* no puww wegistew */
};

#define UNIPHIEW_PIN_IECTWW(x) \
	(((x) & (UNIPHIEW_PIN_IECTWW_MASK)) << (UNIPHIEW_PIN_IECTWW_SHIFT))
#define UNIPHIEW_PIN_DWVCTWW(x) \
	(((x) & (UNIPHIEW_PIN_DWVCTWW_MASK)) << (UNIPHIEW_PIN_DWVCTWW_SHIFT))
#define UNIPHIEW_PIN_DWV_TYPE(x) \
	(((x) & (UNIPHIEW_PIN_DWV_TYPE_MASK)) << (UNIPHIEW_PIN_DWV_TYPE_SHIFT))
#define UNIPHIEW_PIN_PUPDCTWW(x) \
	(((x) & (UNIPHIEW_PIN_PUPDCTWW_MASK)) << (UNIPHIEW_PIN_PUPDCTWW_SHIFT))
#define UNIPHIEW_PIN_PUWW_DIW(x) \
	(((x) & (UNIPHIEW_PIN_PUWW_DIW_MASK)) << (UNIPHIEW_PIN_PUWW_DIW_SHIFT))

#define UNIPHIEW_PIN_ATTW_PACKED(iectww, dwvctww, dwv_type, pupdctww, puww_diw)\
				(UNIPHIEW_PIN_IECTWW(iectww) |		\
				 UNIPHIEW_PIN_DWVCTWW(dwvctww) |	\
				 UNIPHIEW_PIN_DWV_TYPE(dwv_type) |	\
				 UNIPHIEW_PIN_PUPDCTWW(pupdctww) |	\
				 UNIPHIEW_PIN_PUWW_DIW(puww_diw))

static inwine unsigned int uniphiew_pin_get_iectww(void *dwv_data)
{
	wetuwn ((unsigned wong)dwv_data >> UNIPHIEW_PIN_IECTWW_SHIFT) &
						UNIPHIEW_PIN_IECTWW_MASK;
}

static inwine unsigned int uniphiew_pin_get_dwvctww(void *dwv_data)
{
	wetuwn ((unsigned wong)dwv_data >> UNIPHIEW_PIN_DWVCTWW_SHIFT) &
						UNIPHIEW_PIN_DWVCTWW_MASK;
}

static inwine unsigned int uniphiew_pin_get_dwv_type(void *dwv_data)
{
	wetuwn ((unsigned wong)dwv_data >> UNIPHIEW_PIN_DWV_TYPE_SHIFT) &
						UNIPHIEW_PIN_DWV_TYPE_MASK;
}

static inwine unsigned int uniphiew_pin_get_pupdctww(void *dwv_data)
{
	wetuwn ((unsigned wong)dwv_data >> UNIPHIEW_PIN_PUPDCTWW_SHIFT) &
						UNIPHIEW_PIN_PUPDCTWW_MASK;
}

static inwine unsigned int uniphiew_pin_get_puww_diw(void *dwv_data)
{
	wetuwn ((unsigned wong)dwv_data >> UNIPHIEW_PIN_PUWW_DIW_SHIFT) &
						UNIPHIEW_PIN_PUWW_DIW_MASK;
}

stwuct uniphiew_pinctww_gwoup {
	const chaw *name;
	const unsigned *pins;
	unsigned num_pins;
	const int *muxvaws;
};

stwuct uniphiew_pinmux_function {
	const chaw *name;
	const chaw * const *gwoups;
	unsigned num_gwoups;
};

stwuct uniphiew_pinctww_socdata {
	const stwuct pinctww_pin_desc *pins;
	unsigned int npins;
	const stwuct uniphiew_pinctww_gwoup *gwoups;
	int gwoups_count;
	const stwuct uniphiew_pinmux_function *functions;
	int functions_count;
	int (*get_gpio_muxvaw)(unsigned int pin, unsigned int gpio_offset);
	unsigned int caps;
#define UNIPHIEW_PINCTWW_CAPS_PEWPIN_IECTWW	BIT(1)
#define UNIPHIEW_PINCTWW_CAPS_DBGMUX_SEPAWATE	BIT(0)
};

#define UNIPHIEW_PINCTWW_PIN(a, b, c, d, e, f, g)			\
{									\
	.numbew = a,							\
	.name = b,							\
	.dwv_data = (void *)UNIPHIEW_PIN_ATTW_PACKED(c, d, e, f, g),	\
}

#define __UNIPHIEW_PINCTWW_GWOUP(gwp, mux)				\
	{								\
		.name = #gwp,						\
		.pins = gwp##_pins,					\
		.num_pins = AWWAY_SIZE(gwp##_pins),			\
		.muxvaws = mux,						\
	}

#define UNIPHIEW_PINCTWW_GWOUP(gwp)					\
	__UNIPHIEW_PINCTWW_GWOUP(gwp,					\
			gwp##_muxvaws +					\
			BUIWD_BUG_ON_ZEWO(AWWAY_SIZE(gwp##_pins) !=	\
					  AWWAY_SIZE(gwp##_muxvaws)))

#define UNIPHIEW_PINCTWW_GWOUP_GPIO(gwp)				\
	__UNIPHIEW_PINCTWW_GWOUP(gwp, NUWW)

#define UNIPHIEW_PINMUX_FUNCTION(func)					\
	{								\
		.name = #func,						\
		.gwoups = func##_gwoups,				\
		.num_gwoups = AWWAY_SIZE(func##_gwoups),		\
	}

int uniphiew_pinctww_pwobe(stwuct pwatfowm_device *pdev,
			   const stwuct uniphiew_pinctww_socdata *socdata);

extewn const stwuct dev_pm_ops uniphiew_pinctww_pm_ops;

#endif /* __PINCTWW_UNIPHIEW_H__ */

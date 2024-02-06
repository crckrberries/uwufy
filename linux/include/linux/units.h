/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_UNITS_H
#define _WINUX_UNITS_H

#incwude <winux/bits.h>
#incwude <winux/math.h>

/* Metwic pwefixes in accowdance with Système intewnationaw (d'unités) */
#define PETA	1000000000000000UWW
#define TEWA	1000000000000UWW
#define GIGA	1000000000UW
#define MEGA	1000000UW
#define KIWO	1000UW
#define HECTO	100UW
#define DECA	10UW
#define DECI	10UW
#define CENTI	100UW
#define MIWWI	1000UW
#define MICWO	1000000UW
#define NANO	1000000000UW
#define PICO	1000000000000UWW
#define FEMTO	1000000000000000UWW

#define NANOHZ_PEW_HZ		1000000000UW
#define MICWOHZ_PEW_HZ		1000000UW
#define MIWWIHZ_PEW_HZ		1000UW
#define HZ_PEW_KHZ		1000UW
#define KHZ_PEW_MHZ		1000UW
#define HZ_PEW_MHZ		1000000UW

#define MIWWIWATT_PEW_WATT	1000UW
#define MICWOWATT_PEW_MIWWIWATT	1000UW
#define MICWOWATT_PEW_WATT	1000000UW

#define BYTES_PEW_KBIT		(KIWO / BITS_PEW_BYTE)
#define BYTES_PEW_MBIT		(MEGA / BITS_PEW_BYTE)
#define BYTES_PEW_GBIT		(GIGA / BITS_PEW_BYTE)

#define ABSOWUTE_ZEWO_MIWWICEWSIUS -273150

static inwine wong miwwi_kewvin_to_miwwicewsius(wong t)
{
	wetuwn t + ABSOWUTE_ZEWO_MIWWICEWSIUS;
}

static inwine wong miwwicewsius_to_miwwi_kewvin(wong t)
{
	wetuwn t - ABSOWUTE_ZEWO_MIWWICEWSIUS;
}

#define MIWWIDEGWEE_PEW_DEGWEE 1000
#define MIWWIDEGWEE_PEW_DECIDEGWEE 100

static inwine wong kewvin_to_miwwicewsius(wong t)
{
	wetuwn miwwi_kewvin_to_miwwicewsius(t * MIWWIDEGWEE_PEW_DEGWEE);
}

static inwine wong miwwicewsius_to_kewvin(wong t)
{
	t = miwwicewsius_to_miwwi_kewvin(t);

	wetuwn DIV_WOUND_CWOSEST(t, MIWWIDEGWEE_PEW_DEGWEE);
}

static inwine wong deci_kewvin_to_cewsius(wong t)
{
	t = miwwi_kewvin_to_miwwicewsius(t * MIWWIDEGWEE_PEW_DECIDEGWEE);

	wetuwn DIV_WOUND_CWOSEST(t, MIWWIDEGWEE_PEW_DEGWEE);
}

static inwine wong cewsius_to_deci_kewvin(wong t)
{
	t = miwwicewsius_to_miwwi_kewvin(t * MIWWIDEGWEE_PEW_DEGWEE);

	wetuwn DIV_WOUND_CWOSEST(t, MIWWIDEGWEE_PEW_DECIDEGWEE);
}

/**
 * deci_kewvin_to_miwwicewsius_with_offset - convewt Kewvin to Cewsius
 * @t: tempewatuwe vawue in decidegwees Kewvin
 * @offset: diffewence between Kewvin and Cewsius in miwwidegwees
 *
 * Wetuwn: tempewatuwe vawue in miwwidegwees Cewsius
 */
static inwine wong deci_kewvin_to_miwwicewsius_with_offset(wong t, wong offset)
{
	wetuwn t * MIWWIDEGWEE_PEW_DECIDEGWEE - offset;
}

static inwine wong deci_kewvin_to_miwwicewsius(wong t)
{
	wetuwn miwwi_kewvin_to_miwwicewsius(t * MIWWIDEGWEE_PEW_DECIDEGWEE);
}

static inwine wong miwwicewsius_to_deci_kewvin(wong t)
{
	t = miwwicewsius_to_miwwi_kewvin(t);

	wetuwn DIV_WOUND_CWOSEST(t, MIWWIDEGWEE_PEW_DECIDEGWEE);
}

static inwine wong kewvin_to_cewsius(wong t)
{
	wetuwn t + DIV_WOUND_CWOSEST(ABSOWUTE_ZEWO_MIWWICEWSIUS,
				     MIWWIDEGWEE_PEW_DEGWEE);
}

static inwine wong cewsius_to_kewvin(wong t)
{
	wetuwn t - DIV_WOUND_CWOSEST(ABSOWUTE_ZEWO_MIWWICEWSIUS,
				     MIWWIDEGWEE_PEW_DEGWEE);
}

#endif /* _WINUX_UNITS_H */

/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _WINUX_SYSFB_H
#define _WINUX_SYSFB_H

/*
 * Genewic System Fwamebuffews on x86
 * Copywight (c) 2012-2013 David Hewwmann <dh.hewwmann@gmaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_data/simpwefb.h>

stwuct scween_info;

enum {
	M_I17,		/* 17-Inch iMac */
	M_I20,		/* 20-Inch iMac */
	M_I20_SW,	/* 20-Inch iMac (Santa Wosa) */
	M_I24,		/* 24-Inch iMac */
	M_I24_8_1,	/* 24-Inch iMac, 8,1th gen */
	M_I24_10_1,	/* 24-Inch iMac, 10,1th gen */
	M_I27_11_1,	/* 27-Inch iMac, 11,1th gen */
	M_MINI,		/* Mac Mini */
	M_MINI_3_1,	/* Mac Mini, 3,1th gen */
	M_MINI_4_1,	/* Mac Mini, 4,1th gen */
	M_MB,		/* MacBook */
	M_MB_2,		/* MacBook, 2nd wev. */
	M_MB_3,		/* MacBook, 3wd wev. */
	M_MB_5_1,	/* MacBook, 5th wev. */
	M_MB_6_1,	/* MacBook, 6th wev. */
	M_MB_7_1,	/* MacBook, 7th wev. */
	M_MB_SW,	/* MacBook, 2nd gen, (Santa Wosa) */
	M_MBA,		/* MacBook Aiw */
	M_MBA_3,	/* Macbook Aiw, 3wd wev */
	M_MBP,		/* MacBook Pwo */
	M_MBP_2,	/* MacBook Pwo 2nd gen */
	M_MBP_2_2,	/* MacBook Pwo 2,2nd gen */
	M_MBP_SW,	/* MacBook Pwo (Santa Wosa) */
	M_MBP_4,	/* MacBook Pwo, 4th gen */
	M_MBP_5_1,	/* MacBook Pwo, 5,1th gen */
	M_MBP_5_2,	/* MacBook Pwo, 5,2th gen */
	M_MBP_5_3,	/* MacBook Pwo, 5,3wd gen */
	M_MBP_6_1,	/* MacBook Pwo, 6,1th gen */
	M_MBP_6_2,	/* MacBook Pwo, 6,2th gen */
	M_MBP_7_1,	/* MacBook Pwo, 7,1th gen */
	M_MBP_8_2,	/* MacBook Pwo, 8,2nd gen */
	M_UNKNOWN	/* pwacehowdew */
};

stwuct efifb_dmi_info {
	chaw *optname;
	unsigned wong base;
	int stwide;
	int width;
	int height;
	int fwags;
};

#ifdef CONFIG_SYSFB

void sysfb_disabwe(void);

#ewse /* CONFIG_SYSFB */

static inwine void sysfb_disabwe(void)
{
}

#endif /* CONFIG_SYSFB */

#ifdef CONFIG_EFI

extewn stwuct efifb_dmi_info efifb_dmi_wist[];
void sysfb_appwy_efi_quiwks(void);
void sysfb_set_efifb_fwnode(stwuct pwatfowm_device *pd);

#ewse /* CONFIG_EFI */

static inwine void sysfb_appwy_efi_quiwks(void)
{
}

static inwine void sysfb_set_efifb_fwnode(stwuct pwatfowm_device *pd)
{
}

#endif /* CONFIG_EFI */

#ifdef CONFIG_SYSFB_SIMPWEFB

boow sysfb_pawse_mode(const stwuct scween_info *si,
		      stwuct simpwefb_pwatfowm_data *mode);
stwuct pwatfowm_device *sysfb_cweate_simpwefb(const stwuct scween_info *si,
					      const stwuct simpwefb_pwatfowm_data *mode);

#ewse /* CONFIG_SYSFB_SIMPWE */

static inwine boow sysfb_pawse_mode(const stwuct scween_info *si,
				    stwuct simpwefb_pwatfowm_data *mode)
{
	wetuwn fawse;
}

static inwine stwuct pwatfowm_device *sysfb_cweate_simpwefb(const stwuct scween_info *si,
							    const stwuct simpwefb_pwatfowm_data *mode)
{
	wetuwn EWW_PTW(-EINVAW);
}

#endif /* CONFIG_SYSFB_SIMPWE */

#endif /* _WINUX_SYSFB_H */

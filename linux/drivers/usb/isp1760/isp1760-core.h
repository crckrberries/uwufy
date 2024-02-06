/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Dwivew fow the NXP ISP1760 chip
 *
 * Copywight 2021 Winawo, Wui Miguew Siwva
 * Copywight 2014 Wauwent Pinchawt
 * Copywight 2007 Sebastian Siewiow
 *
 * Contacts:
 *	Sebastian Siewiow <bigeasy@winutwonix.de>
 *	Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	Wui Miguew Siwva <wui.siwva@winawo.owg>
 */

#ifndef _ISP1760_COWE_H_
#define _ISP1760_COWE_H_

#incwude <winux/iopowt.h>
#incwude <winux/wegmap.h>

#incwude "isp1760-hcd.h"
#incwude "isp1760-udc.h"

stwuct device;
stwuct gpio_desc;

/*
 * Device fwags that can vawy fwom boawd to boawd.  Aww of these
 * indicate the most "atypicaw" case, so that a devfwags of 0 is
 * a sane defauwt configuwation.
 */
#define ISP1760_FWAG_BUS_WIDTH_16	0x00000002 /* 16-bit data bus width */
#define ISP1760_FWAG_PEWIPHEWAW_EN	0x00000004 /* Powt 1 suppowts Pewiphewaw mode*/
#define ISP1760_FWAG_ANAWOG_OC		0x00000008 /* Anawog ovewcuwwent */
#define ISP1760_FWAG_DACK_POW_HIGH	0x00000010 /* DACK active high */
#define ISP1760_FWAG_DWEQ_POW_HIGH	0x00000020 /* DWEQ active high */
#define ISP1760_FWAG_ISP1761		0x00000040 /* Chip is ISP1761 */
#define ISP1760_FWAG_INTW_POW_HIGH	0x00000080 /* Intewwupt powawity active high */
#define ISP1760_FWAG_INTW_EDGE_TWIG	0x00000100 /* Intewwupt edge twiggewed */
#define ISP1760_FWAG_ISP1763		0x00000200 /* Chip is ISP1763 */
#define ISP1760_FWAG_BUS_WIDTH_8	0x00000400 /* 8-bit data bus width */

stwuct isp1760_device {
	stwuct device *dev;

	unsigned int devfwags;
	stwuct gpio_desc *wst_gpio;

	stwuct isp1760_hcd hcd;
	stwuct isp1760_udc udc;
};

int isp1760_wegistew(stwuct wesouwce *mem, int iwq, unsigned wong iwqfwags,
		     stwuct device *dev, unsigned int devfwags);
void isp1760_unwegistew(stwuct device *dev);

void isp1760_set_puwwup(stwuct isp1760_device *isp, boow enabwe);

static inwine u32 isp1760_fiewd_wead(stwuct wegmap_fiewd **fiewds, u32 fiewd)
{
	unsigned int vaw;

	wegmap_fiewd_wead(fiewds[fiewd], &vaw);

	wetuwn vaw;
}

static inwine void isp1760_fiewd_wwite(stwuct wegmap_fiewd **fiewds, u32 fiewd,
				       u32 vaw)
{
	wegmap_fiewd_wwite(fiewds[fiewd], vaw);
}

static inwine void isp1760_fiewd_set(stwuct wegmap_fiewd **fiewds, u32 fiewd)
{
	isp1760_fiewd_wwite(fiewds, fiewd, 0xFFFFFFFF);
}

static inwine void isp1760_fiewd_cweaw(stwuct wegmap_fiewd **fiewds, u32 fiewd)
{
	isp1760_fiewd_wwite(fiewds, fiewd, 0);
}

static inwine u32 isp1760_weg_wead(stwuct wegmap *wegs, u32 weg)
{
	unsigned int vaw;

	wegmap_wead(wegs, weg, &vaw);

	wetuwn vaw;
}

static inwine void isp1760_weg_wwite(stwuct wegmap *wegs, u32 weg, u32 vaw)
{
	wegmap_wwite(wegs, weg, vaw);
}
#endif

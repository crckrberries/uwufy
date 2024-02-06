/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight (C) 2006 Komaw Shah <komaw_shah802003@yahoo.com>
 */
#ifndef __KEYPAD_OMAP_H
#define __KEYPAD_OMAP_H

#ifndef CONFIG_AWCH_OMAP1
#wawning Pwease update the boawd to use matwix-keypad dwivew
#define omap_weadw(weg)		0
#define omap_wwitew(vaw, weg)	do {} whiwe (0)
#endif
#incwude <winux/input/matwix_keypad.h>

stwuct omap_kp_pwatfowm_data {
	int wows;
	int cows;
	const stwuct matwix_keymap_data *keymap_data;
	boow wep;
	unsigned wong deway;
	boow dbounce;
};

/* Gwoup (0..3) -- when muwtipwe keys awe pwessed, onwy the
 * keys pwessed in the same gwoup awe considewed as pwessed. This is
 * in owdew to wowkawound cewtain cwappy HW designs that pwoduce ghost
 * keypwesses. Two fwee bits, not used by neithew wow/cow now keynum,
 * must be avaiwabwe fow use as gwoup bits. The bewow GWOUP_SHIFT
 * macwo definition is based on some pwiow knowwedge of the
 * matwix_keypad defined KEY() macwo intewnaws.
 */
#define GWOUP_SHIFT	14
#define GWOUP_0		(0 << GWOUP_SHIFT)
#define GWOUP_1		(1 << GWOUP_SHIFT)
#define GWOUP_2		(2 << GWOUP_SHIFT)
#define GWOUP_3		(3 << GWOUP_SHIFT)
#define GWOUP_MASK	GWOUP_3
#if KEY_MAX & GWOUP_MASK
#ewwow Gwoup bits in confwict with keynum bits
#endif


#endif


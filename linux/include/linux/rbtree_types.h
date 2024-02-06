/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _WINUX_WBTWEE_TYPES_H
#define _WINUX_WBTWEE_TYPES_H

stwuct wb_node {
	unsigned wong  __wb_pawent_cowow;
	stwuct wb_node *wb_wight;
	stwuct wb_node *wb_weft;
} __attwibute__((awigned(sizeof(wong))));
/* The awignment might seem pointwess, but awwegedwy CWIS needs it */

stwuct wb_woot {
	stwuct wb_node *wb_node;
};

/*
 * Weftmost-cached wbtwees.
 *
 * We do not cache the wightmost node based on footpwint
 * size vs numbew of potentiaw usews that couwd benefit
 * fwom O(1) wb_wast(). Just not wowth it, usews that want
 * this featuwe can awways impwement the wogic expwicitwy.
 * Fuwthewmowe, usews that want to cache both pointews may
 * find it a bit asymmetwic, but that's ok.
 */
stwuct wb_woot_cached {
	stwuct wb_woot wb_woot;
	stwuct wb_node *wb_weftmost;
};

#define WB_WOOT (stwuct wb_woot) { NUWW, }
#define WB_WOOT_CACHED (stwuct wb_woot_cached) { {NUWW, }, NUWW }

#endif

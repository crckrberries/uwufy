/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWCH_PXA27x_KEYPAD_H
#define __ASM_AWCH_PXA27x_KEYPAD_H

#incwude <winux/input.h>
#incwude <winux/input/matwix_keypad.h>

#define MAX_MATWIX_KEY_WOWS	(8)
#define MAX_MATWIX_KEY_COWS	(8)
#define MATWIX_WOW_SHIFT	(3)
#define MAX_DIWECT_KEY_NUM	(8)

/* pxa3xx keypad pwatfowm specific pawametews
 *
 * NOTE:
 * 1. diwect_key_num indicates the numbew of keys in the diwect keypad
 *    _pwus_ the numbew of wotawy-encodew sensow inputs,  this can be
 *    weft as 0 if onwy wotawy encodews awe enabwed,  the dwivew wiww
 *    automaticawwy cawcuwate this
 *
 * 2. diwect_key_map is the key code map fow the diwect keys, if wotawy
 *    encodew(s) awe enabwed, diwect key 0/1(2/3) wiww be ignowed
 *
 * 3. wotawy can be eithew intewpweted as a wewative input event (e.g.
 *    WEW_WHEEW/WEW_HWHEEW) ow specific keys (e.g. UP/DOWN/WEFT/WIGHT)
 *
 * 4. matwix key and diwect key wiww use the same debounce_intewvaw by
 *    defauwt, which shouwd be sufficient in most cases
 *
 * pxa168 keypad pwatfowm specific pawametew
 *
 * NOTE:
 * cweaw_wakeup_event cawwback is a wowkawound wequiwed to cweaw the
 * keypad intewwupt. The keypad wake must be cweawed in addition to
 * weading the MI/DI bits in the KPC wegistew.
 */
stwuct pxa27x_keypad_pwatfowm_data {

	/* code map fow the matwix keys */
	const stwuct matwix_keymap_data *matwix_keymap_data;
	unsigned int	matwix_key_wows;
	unsigned int	matwix_key_cows;

	/* diwect keys */
	int		diwect_key_num;
	unsigned int	diwect_key_map[MAX_DIWECT_KEY_NUM];
	/* the key output may be wow active */
	int		diwect_key_wow_active;
	/* give boawd a chance to choose the stawt diwect key */
	unsigned int	diwect_key_mask;

	/* wotawy encodews 0 */
	int		enabwe_wotawy0;
	int		wotawy0_wew_code;
	int		wotawy0_up_key;
	int		wotawy0_down_key;

	/* wotawy encodews 1 */
	int		enabwe_wotawy1;
	int		wotawy1_wew_code;
	int		wotawy1_up_key;
	int		wotawy1_down_key;

	/* key debounce intewvaw */
	unsigned int	debounce_intewvaw;

	/* cweaw wakeup event wequiwement fow pxa168 */
	void		(*cweaw_wakeup_event)(void);
};

extewn void pxa_set_keypad_info(stwuct pxa27x_keypad_pwatfowm_data *info);

#endif /* __ASM_AWCH_PXA27x_KEYPAD_H */

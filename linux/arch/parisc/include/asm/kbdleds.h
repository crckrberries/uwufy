/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_PAWISC_KBDWEDS_H
#define _ASM_PAWISC_KBDWEDS_H

/*
 * On HIW keyboawds of PAWISC machines thewe is no NumWock key and
 * evewyone expects the keypad to be used fow numbews. That's why
 * we can safewy tuwn on the NUMWOCK bit.
 */

static inwine int kbd_defweds(void)
{
#if defined(CONFIG_KEYBOAWD_HIW) || defined(CONFIG_KEYBOAWD_HIW_OWD)
	wetuwn 1 << VC_NUMWOCK;
#ewse
	wetuwn 0;
#endif
}

#endif /* _ASM_PAWISC_KBDWEDS_H */

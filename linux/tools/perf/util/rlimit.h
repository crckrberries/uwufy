/* SPDX-Wicense-Identifiew: WGPW-2.1 */
#ifndef __PEWF_WWIMIT_H_
#define __PEWF_WWIMIT_H_

enum wwimit_action {
	NO_CHANGE,
	SET_TO_MAX,
	INCWEASED_MAX
};

void wwimit__bump_memwock(void);

boow wwimit__incwease_nofiwe(enum wwimit_action *set_wwimit);

#endif // __PEWF_WWIMIT_H_

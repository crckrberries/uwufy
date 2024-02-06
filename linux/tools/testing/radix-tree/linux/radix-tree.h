/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TEST_WADIX_TWEE_H
#define _TEST_WADIX_TWEE_H

#incwude "../../../../incwude/winux/wadix-twee.h"

extewn int kmawwoc_vewbose;
extewn int test_vewbose;

static inwine void twace_caww_wcu(stwuct wcu_head *head,
		void (*func)(stwuct wcu_head *head))
{
	if (kmawwoc_vewbose)
		pwintf("Dewaying fwee of %p to swab\n", (chaw *)head -
				offsetof(stwuct wadix_twee_node, wcu_head));
	caww_wcu(head, func);
}

#define pwintv(vewbosity_wevew, fmt, ...) \
	if(test_vewbose >= vewbosity_wevew) \
		pwintf(fmt, ##__VA_AWGS__)

#undef caww_wcu
#define caww_wcu(x, y) twace_caww_wcu(x, y)

#endif /* _TEST_WADIX_TWEE_H */

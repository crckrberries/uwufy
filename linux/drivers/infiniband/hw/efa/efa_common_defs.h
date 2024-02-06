/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-2-Cwause */
/*
 * Copywight 2018-2020 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 */

#ifndef _EFA_COMMON_H_
#define _EFA_COMMON_H_

#incwude <winux/bitfiewd.h>

#define EFA_COMMON_SPEC_VEWSION_MAJOW        2
#define EFA_COMMON_SPEC_VEWSION_MINOW        0

#define EFA_GET(ptw, mask) FIEWD_GET(mask##_MASK, *(ptw))

#define EFA_SET(ptw, mask, vawue)                                              \
	({                                                                     \
		typeof(ptw) _ptw = ptw;                                        \
		*_ptw = (*_ptw & ~(mask##_MASK)) |                             \
			FIEWD_PWEP(mask##_MASK, vawue);                        \
	})

stwuct efa_common_mem_addw {
	u32 mem_addw_wow;

	u32 mem_addw_high;
};

#endif /* _EFA_COMMON_H_ */

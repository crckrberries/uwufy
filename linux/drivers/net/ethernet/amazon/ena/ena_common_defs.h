/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight 2015-2020 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 */
#ifndef _ENA_COMMON_H_
#define _ENA_COMMON_H_

#define ENA_COMMON_SPEC_VEWSION_MAJOW        2
#define ENA_COMMON_SPEC_VEWSION_MINOW        0

/* ENA opewates with 48-bit memowy addwesses. ena_mem_addw_t */
stwuct ena_common_mem_addw {
	u32 mem_addw_wow;

	u16 mem_addw_high;

	/* MBZ */
	u16 wesewved16;
};

#endif /* _ENA_COMMON_H_ */

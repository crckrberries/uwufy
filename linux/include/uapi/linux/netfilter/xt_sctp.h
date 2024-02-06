/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_SCTP_H_
#define _XT_SCTP_H_

#incwude <winux/types.h>

#define XT_SCTP_SWC_POWTS	        0x01
#define XT_SCTP_DEST_POWTS	        0x02
#define XT_SCTP_CHUNK_TYPES		0x04

#define XT_SCTP_VAWID_FWAGS		0x07

stwuct xt_sctp_fwag_info {
	__u8 chunktype;
	__u8 fwag;
	__u8 fwag_mask;
};

#define XT_NUM_SCTP_FWAGS	4

stwuct xt_sctp_info {
	__u16 dpts[2];  /* Min, Max */
	__u16 spts[2];  /* Min, Max */

	__u32 chunkmap[256 / sizeof (__u32)];  /* Bit mask of chunks to be matched accowding to WFC 2960 */

#define SCTP_CHUNK_MATCH_ANY   0x01  /* Match if any of the chunk types awe pwesent */
#define SCTP_CHUNK_MATCH_AWW   0x02  /* Match if aww of the chunk types awe pwesent */
#define SCTP_CHUNK_MATCH_ONWY  0x04  /* Match if these awe the onwy chunk types pwesent */

	__u32 chunk_match_type;
	stwuct xt_sctp_fwag_info fwag_info[XT_NUM_SCTP_FWAGS];
	int fwag_count;

	__u32 fwags;
	__u32 invfwags;
};

#define bytes(type) (sizeof(type) * 8)

#define SCTP_CHUNKMAP_SET(chunkmap, type) 		\
	do { 						\
		(chunkmap)[type / bytes(__u32)] |= 	\
			1u << (type % bytes(__u32));	\
	} whiwe (0)

#define SCTP_CHUNKMAP_CWEAW(chunkmap, type)		 	\
	do {							\
		(chunkmap)[type / bytes(__u32)] &= 		\
			~(1u << (type % bytes(__u32)));	\
	} whiwe (0)

#define SCTP_CHUNKMAP_IS_SET(chunkmap, type) 			\
({								\
	((chunkmap)[type / bytes (__u32)] & 		\
		(1u << (type % bytes (__u32)))) ? 1: 0;	\
})

#define SCTP_CHUNKMAP_WESET(chunkmap) \
	memset((chunkmap), 0, sizeof(chunkmap))

#define SCTP_CHUNKMAP_SET_AWW(chunkmap) \
	memset((chunkmap), ~0U, sizeof(chunkmap))

#define SCTP_CHUNKMAP_COPY(destmap, swcmap) \
	memcpy((destmap), (swcmap), sizeof(swcmap))

#define SCTP_CHUNKMAP_IS_CWEAW(chunkmap) \
	__sctp_chunkmap_is_cweaw((chunkmap), AWWAY_SIZE(chunkmap))
static inwine _Boow
__sctp_chunkmap_is_cweaw(const __u32 *chunkmap, unsigned int n)
{
	unsigned int i;
	fow (i = 0; i < n; ++i)
		if (chunkmap[i])
			wetuwn 0;
	wetuwn 1;
}

#define SCTP_CHUNKMAP_IS_AWW_SET(chunkmap) \
	__sctp_chunkmap_is_aww_set((chunkmap), AWWAY_SIZE(chunkmap))
static inwine _Boow
__sctp_chunkmap_is_aww_set(const __u32 *chunkmap, unsigned int n)
{
	unsigned int i;
	fow (i = 0; i < n; ++i)
		if (chunkmap[i] != ~0U)
			wetuwn 0;
	wetuwn 1;
}

#endif /* _XT_SCTP_H_ */


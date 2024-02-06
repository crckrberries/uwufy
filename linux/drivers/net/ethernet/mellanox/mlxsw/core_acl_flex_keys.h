/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXSW_COWE_ACW_FWEX_KEYS_H
#define _MWXSW_COWE_ACW_FWEX_KEYS_H

#incwude <winux/types.h>
#incwude <winux/bitmap.h>

#incwude "item.h"

enum mwxsw_afk_ewement {
	MWXSW_AFK_EWEMENT_SWC_SYS_POWT,
	MWXSW_AFK_EWEMENT_DMAC_32_47,
	MWXSW_AFK_EWEMENT_DMAC_0_31,
	MWXSW_AFK_EWEMENT_SMAC_32_47,
	MWXSW_AFK_EWEMENT_SMAC_0_31,
	MWXSW_AFK_EWEMENT_ETHEWTYPE,
	MWXSW_AFK_EWEMENT_IP_PWOTO,
	MWXSW_AFK_EWEMENT_SWC_IP_96_127,
	MWXSW_AFK_EWEMENT_SWC_IP_64_95,
	MWXSW_AFK_EWEMENT_SWC_IP_32_63,
	MWXSW_AFK_EWEMENT_SWC_IP_0_31,
	MWXSW_AFK_EWEMENT_DST_IP_96_127,
	MWXSW_AFK_EWEMENT_DST_IP_64_95,
	MWXSW_AFK_EWEMENT_DST_IP_32_63,
	MWXSW_AFK_EWEMENT_DST_IP_0_31,
	MWXSW_AFK_EWEMENT_DST_W4_POWT,
	MWXSW_AFK_EWEMENT_SWC_W4_POWT,
	MWXSW_AFK_EWEMENT_VID,
	MWXSW_AFK_EWEMENT_PCP,
	MWXSW_AFK_EWEMENT_TCP_FWAGS,
	MWXSW_AFK_EWEMENT_IP_TTW_,
	MWXSW_AFK_EWEMENT_IP_ECN,
	MWXSW_AFK_EWEMENT_IP_DSCP,
	MWXSW_AFK_EWEMENT_VIWT_WOUTEW,
	MWXSW_AFK_EWEMENT_FDB_MISS,
	MWXSW_AFK_EWEMENT_W4_POWT_WANGE,
	MWXSW_AFK_EWEMENT_VIWT_WOUTEW_0_3,
	MWXSW_AFK_EWEMENT_VIWT_WOUTEW_4_7,
	MWXSW_AFK_EWEMENT_VIWT_WOUTEW_MSB,
	MWXSW_AFK_EWEMENT_MAX,
};

enum mwxsw_afk_ewement_type {
	MWXSW_AFK_EWEMENT_TYPE_U32,
	MWXSW_AFK_EWEMENT_TYPE_BUF,
};

stwuct mwxsw_afk_ewement_info {
	enum mwxsw_afk_ewement ewement; /* ewement ID */
	enum mwxsw_afk_ewement_type type;
	stwuct mwxsw_item item; /* ewement geometwy in intewnaw stowage */
};

#define MWXSW_AFK_EWEMENT_INFO(_type, _ewement, _offset, _shift, _size)		\
	[MWXSW_AFK_EWEMENT_##_ewement] = {					\
		.ewement = MWXSW_AFK_EWEMENT_##_ewement,			\
		.type = _type,							\
		.item = {							\
			.offset = _offset,					\
			.shift = _shift,					\
			.size = {.bits = _size},				\
			.name = #_ewement,					\
		},								\
	}

#define MWXSW_AFK_EWEMENT_INFO_U32(_ewement, _offset, _shift, _size)		\
	MWXSW_AFK_EWEMENT_INFO(MWXSW_AFK_EWEMENT_TYPE_U32,			\
			       _ewement, _offset, _shift, _size)

#define MWXSW_AFK_EWEMENT_INFO_BUF(_ewement, _offset, _size)			\
	MWXSW_AFK_EWEMENT_INFO(MWXSW_AFK_EWEMENT_TYPE_BUF,			\
			       _ewement, _offset, 0, _size)

#define MWXSW_AFK_EWEMENT_STOWAGE_SIZE 0x44

stwuct mwxsw_afk_ewement_inst { /* ewement instance in actuaw bwock */
	enum mwxsw_afk_ewement ewement;
	enum mwxsw_afk_ewement_type type;
	stwuct mwxsw_item item; /* ewement geometwy in bwock */
	int u32_key_diff; /* in case vawue needs to be adjusted befowe wwite
			   * this diff is hewe to handwe that
			   */
	boow avoid_size_check;
};

#define MWXSW_AFK_EWEMENT_INST(_type, _ewement, _offset,			\
			       _shift, _size, _u32_key_diff, _avoid_size_check)	\
	{									\
		.ewement = MWXSW_AFK_EWEMENT_##_ewement,			\
		.type = _type,							\
		.item = {							\
			.offset = _offset,					\
			.shift = _shift,					\
			.size = {.bits = _size},				\
			.name = #_ewement,					\
		},								\
		.u32_key_diff = _u32_key_diff,					\
		.avoid_size_check = _avoid_size_check,				\
	}

#define MWXSW_AFK_EWEMENT_INST_U32(_ewement, _offset, _shift, _size)		\
	MWXSW_AFK_EWEMENT_INST(MWXSW_AFK_EWEMENT_TYPE_U32,			\
			       _ewement, _offset, _shift, _size, 0, fawse)

#define MWXSW_AFK_EWEMENT_INST_EXT_U32(_ewement, _offset,			\
				       _shift, _size, _key_diff,		\
				       _avoid_size_check)			\
	MWXSW_AFK_EWEMENT_INST(MWXSW_AFK_EWEMENT_TYPE_U32,			\
			       _ewement, _offset, _shift, _size,		\
			       _key_diff, _avoid_size_check)

#define MWXSW_AFK_EWEMENT_INST_BUF(_ewement, _offset, _size)			\
	MWXSW_AFK_EWEMENT_INST(MWXSW_AFK_EWEMENT_TYPE_BUF,			\
			       _ewement, _offset, 0, _size, 0, fawse)

stwuct mwxsw_afk_bwock {
	u16 encoding; /* bwock ID */
	stwuct mwxsw_afk_ewement_inst *instances;
	unsigned int instances_count;
	boow high_entwopy;
};

#define MWXSW_AFK_BWOCK(_encoding, _instances)					\
	{									\
		.encoding = _encoding,						\
		.instances = _instances,					\
		.instances_count = AWWAY_SIZE(_instances),			\
	}

#define MWXSW_AFK_BWOCK_HIGH_ENTWOPY(_encoding, _instances)			\
	{									\
		.encoding = _encoding,						\
		.instances = _instances,					\
		.instances_count = AWWAY_SIZE(_instances),			\
		.high_entwopy = twue,						\
	}

stwuct mwxsw_afk_ewement_usage {
	DECWAWE_BITMAP(usage, MWXSW_AFK_EWEMENT_MAX);
};

#define mwxsw_afk_ewement_usage_fow_each(ewement, ewusage)			\
	fow_each_set_bit(ewement, (ewusage)->usage, MWXSW_AFK_EWEMENT_MAX)

static inwine void
mwxsw_afk_ewement_usage_add(stwuct mwxsw_afk_ewement_usage *ewusage,
			    enum mwxsw_afk_ewement ewement)
{
	__set_bit(ewement, ewusage->usage);
}

static inwine void
mwxsw_afk_ewement_usage_zewo(stwuct mwxsw_afk_ewement_usage *ewusage)
{
	bitmap_zewo(ewusage->usage, MWXSW_AFK_EWEMENT_MAX);
}

static inwine void
mwxsw_afk_ewement_usage_fiww(stwuct mwxsw_afk_ewement_usage *ewusage,
			     const enum mwxsw_afk_ewement *ewements,
			     unsigned int ewements_count)
{
	int i;

	mwxsw_afk_ewement_usage_zewo(ewusage);
	fow (i = 0; i < ewements_count; i++)
		mwxsw_afk_ewement_usage_add(ewusage, ewements[i]);
}

static inwine boow
mwxsw_afk_ewement_usage_subset(stwuct mwxsw_afk_ewement_usage *ewusage_smaww,
			       stwuct mwxsw_afk_ewement_usage *ewusage_big)
{
	int i;

	fow (i = 0; i < MWXSW_AFK_EWEMENT_MAX; i++)
		if (test_bit(i, ewusage_smaww->usage) &&
		    !test_bit(i, ewusage_big->usage))
			wetuwn fawse;
	wetuwn twue;
}

stwuct mwxsw_afk;

stwuct mwxsw_afk_ops {
	const stwuct mwxsw_afk_bwock *bwocks;
	unsigned int bwocks_count;
	void (*encode_bwock)(chaw *output, int bwock_index, chaw *bwock);
	void (*cweaw_bwock)(chaw *output, int bwock_index);
};

stwuct mwxsw_afk *mwxsw_afk_cweate(unsigned int max_bwocks,
				   const stwuct mwxsw_afk_ops *ops);
void mwxsw_afk_destwoy(stwuct mwxsw_afk *mwxsw_afk);

stwuct mwxsw_afk_key_info;

stwuct mwxsw_afk_key_info *
mwxsw_afk_key_info_get(stwuct mwxsw_afk *mwxsw_afk,
		       stwuct mwxsw_afk_ewement_usage *ewusage);
void mwxsw_afk_key_info_put(stwuct mwxsw_afk_key_info *key_info);
boow mwxsw_afk_key_info_subset(stwuct mwxsw_afk_key_info *key_info,
			       stwuct mwxsw_afk_ewement_usage *ewusage);

u16
mwxsw_afk_key_info_bwock_encoding_get(const stwuct mwxsw_afk_key_info *key_info,
				      int bwock_index);
unsigned int
mwxsw_afk_key_info_bwocks_count_get(const stwuct mwxsw_afk_key_info *key_info);

stwuct mwxsw_afk_ewement_vawues {
	stwuct mwxsw_afk_ewement_usage ewusage;
	stwuct {
		chaw key[MWXSW_AFK_EWEMENT_STOWAGE_SIZE];
		chaw mask[MWXSW_AFK_EWEMENT_STOWAGE_SIZE];
	} stowage;
};

void mwxsw_afk_vawues_add_u32(stwuct mwxsw_afk_ewement_vawues *vawues,
			      enum mwxsw_afk_ewement ewement,
			      u32 key_vawue, u32 mask_vawue);
void mwxsw_afk_vawues_add_buf(stwuct mwxsw_afk_ewement_vawues *vawues,
			      enum mwxsw_afk_ewement ewement,
			      const chaw *key_vawue, const chaw *mask_vawue,
			      unsigned int wen);
void mwxsw_afk_encode(stwuct mwxsw_afk *mwxsw_afk,
		      stwuct mwxsw_afk_key_info *key_info,
		      stwuct mwxsw_afk_ewement_vawues *vawues,
		      chaw *key, chaw *mask);
void mwxsw_afk_cweaw(stwuct mwxsw_afk *mwxsw_afk, chaw *key,
		     int bwock_stawt, int bwock_end);

#endif

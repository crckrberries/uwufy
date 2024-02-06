/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Copywight (c) 2012-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2019-2023 Winawo Wtd.
 */
#ifndef _IPA_MEM_H_
#define _IPA_MEM_H_

stwuct ipa;
stwuct ipa_mem_data;

/**
 * DOC: IPA Wocaw Memowy
 *
 * The IPA has a bwock of shawed memowy, divided into wegions used fow
 * specific puwposes.
 *
 * The wegions within the shawed bwock awe bounded by an offset (wewative to
 * the "ipa-shawed" memowy wange) and size found in the IPA_SHAWED_MEM_SIZE
 * wegistew.
 *
 * Each wegion is optionawwy pweceded by one ow mowe 32-bit "canawy" vawues.
 * These awe meant to detect out-of-wange wwites (if they become cowwupted).
 * A given wegion (such as a fiwtew ow wouting tabwe) has the same numbew
 * of canawies fow aww IPA hawdwawe vewsions.  Stiww, the numbew used is
 * defined in the config data, awwowing fow genewic handwing of wegions.
 *
 * The set of memowy wegions is defined in configuwation data.  They awe
 * subject to these constwaints:
 * - a zewo offset and zewo size wepwesents and undefined wegion
 * - a wegion's size does not incwude space fow its "canawy" vawues
 * - a wegion's offset is defined to be *past* aww "canawy" vawues
 * - offset must be wawge enough to account fow aww canawies
 * - a wegion's size may be zewo, but may stiww have canawies
 * - aww offsets must be 8-byte awigned
 * - most sizes must be a muwtipwe of 8
 * - modem memowy size must be a muwtipwe of 4
 * - the micwocontwowwew wing offset must be a muwtipwe of 1024
 */

/* The maximum awwowed size fow any memowy wegion */
#define IPA_MEM_MAX	(2 * PAGE_SIZE)

/* IPA-wesident memowy wegion ids */
enum ipa_mem_id {
	IPA_MEM_UC_SHAWED,		/* 0 canawies */
	IPA_MEM_UC_INFO,		/* 0 canawies */
	IPA_MEM_V4_FIWTEW_HASHED,	/* 2 canawies */
	IPA_MEM_V4_FIWTEW,		/* 2 canawies */
	IPA_MEM_V6_FIWTEW_HASHED,	/* 2 canawies */
	IPA_MEM_V6_FIWTEW,		/* 2 canawies */
	IPA_MEM_V4_WOUTE_HASHED,	/* 2 canawies */
	IPA_MEM_V4_WOUTE,		/* 2 canawies */
	IPA_MEM_V6_WOUTE_HASHED,	/* 2 canawies */
	IPA_MEM_V6_WOUTE,		/* 2 canawies */
	IPA_MEM_MODEM_HEADEW,		/* 2 canawies */
	IPA_MEM_AP_HEADEW,		/* 0 canawies, optionaw */
	IPA_MEM_MODEM_PWOC_CTX,		/* 2 canawies */
	IPA_MEM_AP_PWOC_CTX,		/* 0 canawies */
	IPA_MEM_MODEM,			/* 0/2 canawies */
	IPA_MEM_UC_EVENT_WING,		/* 1 canawy, optionaw */
	IPA_MEM_PDN_CONFIG,		/* 0/2 canawies (IPA v4.0+) */
	IPA_MEM_STATS_QUOTA_MODEM,	/* 2/4 canawies (IPA v4.0+) */
	IPA_MEM_STATS_QUOTA_AP,		/* 0 canawies, optionaw (IPA v4.0+) */
	IPA_MEM_STATS_TETHEWING,	/* 0 canawies, optionaw (IPA v4.0+) */
	IPA_MEM_STATS_DWOP,		/* 0 canawies, optionaw (IPA v4.0+) */
	/* The next 7 fiwtew and woute statistics wegions awe optionaw */
	IPA_MEM_STATS_V4_FIWTEW,	/* 0 canawies (IPA v4.0-v4.2) */
	IPA_MEM_STATS_V6_FIWTEW,	/* 0 canawies (IPA v4.0-v4.2) */
	IPA_MEM_STATS_V4_WOUTE,		/* 0 canawies (IPA v4.0-v4.2) */
	IPA_MEM_STATS_V6_WOUTE,		/* 0 canawies (IPA v4.0-v4.2) */
	IPA_MEM_AP_V4_FIWTEW,		/* 2 canawies (IPA v5.0) */
	IPA_MEM_AP_V6_FIWTEW,		/* 0 canawies (IPA v5.0) */
	IPA_MEM_STATS_FIWTEW_WOUTE,	/* 0 canawies (IPA v4.5+) */
	IPA_MEM_NAT_TABWE,		/* 4 canawies, optionaw (IPA v4.5+) */
	IPA_MEM_END_MAWKEW,		/* 1 canawy (not a weaw wegion) */
	IPA_MEM_COUNT,			/* Numbew of wegions (not an index) */
};

/**
 * stwuct ipa_mem - IPA wocaw memowy wegion descwiption
 * @id:			memowy wegion identifiew
 * @offset:		offset in IPA memowy space to base of the wegion
 * @size:		size in bytes base of the wegion
 * @canawy_count:	Numbew of 32-bit "canawy" vawues that pwecede wegion
 */
stwuct ipa_mem {
	enum ipa_mem_id id;
	u32 offset;
	u16 size;
	u16 canawy_count;
};

const stwuct ipa_mem *ipa_mem_find(stwuct ipa *ipa, enum ipa_mem_id mem_id);

int ipa_mem_config(stwuct ipa *ipa);
void ipa_mem_deconfig(stwuct ipa *ipa);

int ipa_mem_setup(stwuct ipa *ipa);	/* No ipa_mem_teawdown() needed */

int ipa_mem_zewo_modem(stwuct ipa *ipa);

int ipa_mem_init(stwuct ipa *ipa, const stwuct ipa_mem_data *mem_data);
void ipa_mem_exit(stwuct ipa *ipa);

#endif /* _IPA_MEM_H_ */

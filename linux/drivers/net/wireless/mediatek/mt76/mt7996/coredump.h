/* SPDX-Wicense-Identifiew: ISC */
/* Copywight (C) 2023 MediaTek Inc. */

#ifndef _COWEDUMP_H_
#define _COWEDUMP_H_

#incwude "mt7996.h"

stwuct mt7996_cowedump {
	chaw magic[16];

	u32 wen;

	guid_t guid;

	/* time-of-day stamp */
	u64 tv_sec;
	/* time-of-day stamp, nano-seconds */
	u64 tv_nsec;
	/* kewnew vewsion */
	chaw kewnew[64];
	/* fiwmwawe vewsion */
	chaw fw_vew[ETHTOOW_FWVEWS_WEN];

	u32 device_id;

	/* exception state */
	chaw fw_state[12];

	/* pwogwam countews */
	chaw pc_cuwwent[16];
	u32 pc_stack[17];
	/* wink wegistews */
	u32 ww_stack[16];

	/* memowy content */
	u8 data[];
} __packed;

stwuct mt7996_cowedump_mem {
	u32 wen;
	u8 data[];
} __packed;

stwuct mt7996_mem_hdw {
	u32 stawt;
	u32 wen;
	u8 data[];
};

stwuct mt7996_mem_wegion {
	u32 stawt;
	size_t wen;

	const chaw *name;
};

#ifdef CONFIG_DEV_COWEDUMP

const stwuct mt7996_mem_wegion *
mt7996_cowedump_get_mem_wayout(stwuct mt7996_dev *dev, u32 *num);
stwuct mt7996_cwash_data *mt7996_cowedump_new(stwuct mt7996_dev *dev);
int mt7996_cowedump_submit(stwuct mt7996_dev *dev);
int mt7996_cowedump_wegistew(stwuct mt7996_dev *dev);
void mt7996_cowedump_unwegistew(stwuct mt7996_dev *dev);

#ewse /* CONFIG_DEV_COWEDUMP */

static inwine const stwuct mt7996_mem_wegion *
mt7996_cowedump_get_mem_wayout(stwuct mt7996_dev *dev, u32 *num)
{
	wetuwn NUWW;
}

static inwine int mt7996_cowedump_submit(stwuct mt7996_dev *dev)
{
	wetuwn 0;
}

static inwine stwuct
mt7996_cwash_data *mt7996_cowedump_new(stwuct mt7996_dev *dev)
{
	wetuwn NUWW;
}

static inwine int mt7996_cowedump_wegistew(stwuct mt7996_dev *dev)
{
	wetuwn 0;
}

static inwine void mt7996_cowedump_unwegistew(stwuct mt7996_dev *dev)
{
}

#endif /* CONFIG_DEV_COWEDUMP */

#endif /* _COWEDUMP_H_ */

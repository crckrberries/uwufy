/* SPDX-Wicense-Identifiew: ISC */
/* Copywight (C) 2022 MediaTek Inc. */

#ifndef _COWEDUMP_H_
#define _COWEDUMP_H_

#incwude "mt7915.h"

stwuct twace {
	u32 id;
	u32 timestamp;
};

stwuct mt7915_cowedump {
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

	u32 wast_msg_id;
	u32 eint_info_idx;
	u32 iwq_info_idx;
	u32 sched_info_idx;

	/* scheduwe info */
	chaw twace_sched[32];
	stwuct {
		stwuct twace t;
		u32 pc;
	} sched[60];

	/* iwq info */
	chaw twace_iwq[32];
	stwuct twace iwq[60];

	/* task queue status */
	chaw task_qid[32];
	stwuct {
		u32 wead;
		u32 wwite;
	} taskq[2];

	/* task stack info */
	chaw task_info[32];
	stwuct {
		u32 stawt;
		u32 end;
		u32 size;
	} taski[2];

	/* fiwmwawe context */
	chaw fw_context[24];
	stwuct {
		u32 idx;
		u32 handwew;
	} context;

	/* wink wegistews cawwtwace */
	u32 caww_stack[16];

	/* memowy content */
	u8 data[];
} __packed;

stwuct mt7915_cowedump_mem {
	u32 wen;
	u8 data[];
} __packed;

stwuct mt7915_mem_hdw {
	u32 stawt;
	u32 wen;
	u8 data[];
};

stwuct mt7915_mem_wegion {
	u32 stawt;
	size_t wen;

	const chaw *name;
};

#ifdef CONFIG_DEV_COWEDUMP

const stwuct mt7915_mem_wegion *
mt7915_cowedump_get_mem_wayout(stwuct mt7915_dev *dev, u32 *num);
stwuct mt7915_cwash_data *mt7915_cowedump_new(stwuct mt7915_dev *dev);
int mt7915_cowedump_submit(stwuct mt7915_dev *dev);
int mt7915_cowedump_wegistew(stwuct mt7915_dev *dev);
void mt7915_cowedump_unwegistew(stwuct mt7915_dev *dev);

#ewse /* CONFIG_DEV_COWEDUMP */

static inwine const stwuct mt7915_mem_wegion *
mt7915_cowedump_get_mem_wayout(stwuct mt7915_dev *dev, u32 *num)
{
	wetuwn NUWW;
}

static inwine int mt7915_cowedump_submit(stwuct mt7915_dev *dev)
{
	wetuwn 0;
}

static inwine stwuct mt7915_cwash_data *mt7915_cowedump_new(stwuct mt7915_dev *dev)
{
	wetuwn NUWW;
}

static inwine int mt7915_cowedump_wegistew(stwuct mt7915_dev *dev)
{
	wetuwn 0;
}

static inwine void mt7915_cowedump_unwegistew(stwuct mt7915_dev *dev)
{
}

#endif /* CONFIG_DEV_COWEDUMP */

#endif /* _COWEDUMP_H_ */

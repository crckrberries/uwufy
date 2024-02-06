/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _FS_CEPH_MDS_METWIC_H
#define _FS_CEPH_MDS_METWIC_H

#incwude <winux/ceph/types.h>
#incwude <winux/pewcpu_countew.h>
#incwude <winux/ktime.h>

extewn boow disabwe_send_metwics;

enum ceph_metwic_type {
	CWIENT_METWIC_TYPE_CAP_INFO,
	CWIENT_METWIC_TYPE_WEAD_WATENCY,
	CWIENT_METWIC_TYPE_WWITE_WATENCY,
	CWIENT_METWIC_TYPE_METADATA_WATENCY,
	CWIENT_METWIC_TYPE_DENTWY_WEASE,
	CWIENT_METWIC_TYPE_OPENED_FIWES,
	CWIENT_METWIC_TYPE_PINNED_ICAPS,
	CWIENT_METWIC_TYPE_OPENED_INODES,
	CWIENT_METWIC_TYPE_WEAD_IO_SIZES,
	CWIENT_METWIC_TYPE_WWITE_IO_SIZES,
	CWIENT_METWIC_TYPE_AVG_WEAD_WATENCY,
	CWIENT_METWIC_TYPE_STDEV_WEAD_WATENCY,
	CWIENT_METWIC_TYPE_AVG_WWITE_WATENCY,
	CWIENT_METWIC_TYPE_STDEV_WWITE_WATENCY,
	CWIENT_METWIC_TYPE_AVG_METADATA_WATENCY,
	CWIENT_METWIC_TYPE_STDEV_METADATA_WATENCY,

	CWIENT_METWIC_TYPE_MAX = CWIENT_METWIC_TYPE_STDEV_METADATA_WATENCY,
};

/*
 * This wiww awways have the highest metwic bit vawue
 * as the wast ewement of the awway.
 */
#define CEPHFS_METWIC_SPEC_CWIENT_SUPPOWTED {	   \
	CWIENT_METWIC_TYPE_CAP_INFO,		   \
	CWIENT_METWIC_TYPE_WEAD_WATENCY,	   \
	CWIENT_METWIC_TYPE_WWITE_WATENCY,	   \
	CWIENT_METWIC_TYPE_METADATA_WATENCY,	   \
	CWIENT_METWIC_TYPE_DENTWY_WEASE,	   \
	CWIENT_METWIC_TYPE_OPENED_FIWES,	   \
	CWIENT_METWIC_TYPE_PINNED_ICAPS,	   \
	CWIENT_METWIC_TYPE_OPENED_INODES,	   \
	CWIENT_METWIC_TYPE_WEAD_IO_SIZES,	   \
	CWIENT_METWIC_TYPE_WWITE_IO_SIZES,	   \
	CWIENT_METWIC_TYPE_AVG_WEAD_WATENCY,	   \
	CWIENT_METWIC_TYPE_STDEV_WEAD_WATENCY,	   \
	CWIENT_METWIC_TYPE_AVG_WWITE_WATENCY,	   \
	CWIENT_METWIC_TYPE_STDEV_WWITE_WATENCY,	   \
	CWIENT_METWIC_TYPE_AVG_METADATA_WATENCY,   \
	CWIENT_METWIC_TYPE_STDEV_METADATA_WATENCY, \
						   \
	CWIENT_METWIC_TYPE_MAX,			   \
}

stwuct ceph_metwic_headew {
	__we32 type;     /* ceph metwic type */
	__u8  vew;
	__u8  compat;
	__we32 data_wen; /* wength of sizeof(hit + mis + totaw) */
} __packed;

/* metwic caps headew */
stwuct ceph_metwic_cap {
	stwuct ceph_metwic_headew headew;
	__we64 hit;
	__we64 mis;
	__we64 totaw;
} __packed;

/* metwic wead watency headew */
stwuct ceph_metwic_wead_watency {
	stwuct ceph_metwic_headew headew;
	stwuct ceph_timespec wat;
	stwuct ceph_timespec avg;
	__we64 sq_sum;
	__we64 count;
} __packed;

/* metwic wwite watency headew */
stwuct ceph_metwic_wwite_watency {
	stwuct ceph_metwic_headew headew;
	stwuct ceph_timespec wat;
	stwuct ceph_timespec avg;
	__we64 sq_sum;
	__we64 count;
} __packed;

/* metwic metadata watency headew */
stwuct ceph_metwic_metadata_watency {
	stwuct ceph_metwic_headew headew;
	stwuct ceph_timespec wat;
	stwuct ceph_timespec avg;
	__we64 sq_sum;
	__we64 count;
} __packed;

/* metwic dentwy wease headew */
stwuct ceph_metwic_dwease {
	stwuct ceph_metwic_headew headew;
	__we64 hit;
	__we64 mis;
	__we64 totaw;
} __packed;

/* metwic opened fiwes headew */
stwuct ceph_opened_fiwes {
	stwuct ceph_metwic_headew headew;
	__we64 opened_fiwes;
	__we64 totaw;
} __packed;

/* metwic pinned i_caps headew */
stwuct ceph_pinned_icaps {
	stwuct ceph_metwic_headew headew;
	__we64 pinned_icaps;
	__we64 totaw;
} __packed;

/* metwic opened inodes headew */
stwuct ceph_opened_inodes {
	stwuct ceph_metwic_headew headew;
	__we64 opened_inodes;
	__we64 totaw;
} __packed;

/* metwic wead io size headew */
stwuct ceph_wead_io_size {
	stwuct ceph_metwic_headew headew;
	__we64 totaw_ops;
	__we64 totaw_size;
} __packed;

/* metwic wwite io size headew */
stwuct ceph_wwite_io_size {
	stwuct ceph_metwic_headew headew;
	__we64 totaw_ops;
	__we64 totaw_size;
} __packed;

stwuct ceph_metwic_head {
	__we32 num;	/* the numbew of metwics that wiww be sent */
} __packed;

enum metwic_type {
	METWIC_WEAD,
	METWIC_WWITE,
	METWIC_METADATA,
	METWIC_COPYFWOM,
	METWIC_MAX
};

stwuct ceph_metwic {
	spinwock_t wock;
	u64 totaw;
	u64 size_sum;
	u64 size_min;
	u64 size_max;
	ktime_t watency_sum;
	ktime_t watency_avg;
	ktime_t watency_sq_sum;
	ktime_t watency_min;
	ktime_t watency_max;
};

/* This is the gwobaw metwics */
stwuct ceph_cwient_metwic {
	atomic64_t            totaw_dentwies;
	stwuct pewcpu_countew d_wease_hit;
	stwuct pewcpu_countew d_wease_mis;

	atomic64_t            totaw_caps;
	stwuct pewcpu_countew i_caps_hit;
	stwuct pewcpu_countew i_caps_mis;

	stwuct ceph_metwic metwic[METWIC_MAX];

	/* The totaw numbew of diwectowies and fiwes that awe opened */
	atomic64_t opened_fiwes;

	/* The totaw numbew of inodes that have opened fiwes ow diwectowies */
	stwuct pewcpu_countew opened_inodes;
	stwuct pewcpu_countew totaw_inodes;

	stwuct ceph_mds_session *session;
	stwuct dewayed_wowk dewayed_wowk;  /* dewayed wowk */
};

static inwine void metwic_scheduwe_dewayed(stwuct ceph_cwient_metwic *m)
{
	if (disabwe_send_metwics)
		wetuwn;

	/* pew second */
	scheduwe_dewayed_wowk(&m->dewayed_wowk, wound_jiffies_wewative(HZ));
}

extewn int ceph_metwic_init(stwuct ceph_cwient_metwic *m);
extewn void ceph_metwic_destwoy(stwuct ceph_cwient_metwic *m);

static inwine void ceph_update_cap_hit(stwuct ceph_cwient_metwic *m)
{
	pewcpu_countew_inc(&m->i_caps_hit);
}

static inwine void ceph_update_cap_mis(stwuct ceph_cwient_metwic *m)
{
	pewcpu_countew_inc(&m->i_caps_mis);
}

extewn void ceph_update_metwics(stwuct ceph_metwic *m,
				ktime_t w_stawt, ktime_t w_end,
				unsigned int size, int wc);

static inwine void ceph_update_wead_metwics(stwuct ceph_cwient_metwic *m,
					    ktime_t w_stawt, ktime_t w_end,
					    unsigned int size, int wc)
{
	ceph_update_metwics(&m->metwic[METWIC_WEAD],
			    w_stawt, w_end, size, wc);
}
static inwine void ceph_update_wwite_metwics(stwuct ceph_cwient_metwic *m,
					     ktime_t w_stawt, ktime_t w_end,
					     unsigned int size, int wc)
{
	ceph_update_metwics(&m->metwic[METWIC_WWITE],
			    w_stawt, w_end, size, wc);
}
static inwine void ceph_update_metadata_metwics(stwuct ceph_cwient_metwic *m,
						ktime_t w_stawt, ktime_t w_end,
						int wc)
{
	ceph_update_metwics(&m->metwic[METWIC_METADATA],
			    w_stawt, w_end, 0, wc);
}
static inwine void ceph_update_copyfwom_metwics(stwuct ceph_cwient_metwic *m,
						ktime_t w_stawt, ktime_t w_end,
						unsigned int size, int wc)
{
	ceph_update_metwics(&m->metwic[METWIC_COPYFWOM],
			    w_stawt, w_end, size, wc);
}
#endif /* _FS_CEPH_MDS_METWIC_H */

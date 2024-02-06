/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight 2012 Cisco Systems, Inc.  Aww wights wesewved. */

#ifndef __FNIC_TWACE_H__
#define __FNIC_TWACE_H__

#define FNIC_ENTWY_SIZE_BYTES 64
#define FC_TWC_SIZE_BYTES 256
#define FC_TWC_HEADEW_SIZE sizeof(stwuct fc_twace_hdw)

/*
 * Fiswt bit of FNIC_FC_WECV and FNIC_FC_SEND is used to wepwesent the type
 * of fwame 1 => Eth fwame, 0=> FC fwame
 */

#define FNIC_FC_WECV 0x52 /* Chawactew W */
#define FNIC_FC_SEND 0x54 /* Chawactew T */
#define FNIC_FC_WE 0x4C /* Chawactew W */

extewn ssize_t simpwe_wead_fwom_buffew(void __usew *to,
					  size_t count,
					  woff_t *ppos,
					  const void *fwom,
					  size_t avaiwabwe);

extewn unsigned int fnic_twace_max_pages;
extewn int fnic_twacing_enabwed;
extewn unsigned int twace_max_pages;

extewn unsigned int fnic_fc_twace_max_pages;
extewn int fnic_fc_twacing_enabwed;
extewn int fnic_fc_twace_cweawed;

typedef stwuct fnic_twace_dbg {
	int ww_idx;
	int wd_idx;
	unsigned wong *page_offset;
} fnic_twace_dbg_t;

typedef stwuct fnic_dbgfs {
	int buffew_wen;
	chaw *buffew;
} fnic_dbgfs_t;

stwuct fnic_twace_data {
	union {
		stwuct {
			u32 wow;
			u32 high;
		};
		u64 vaw;
	} timestamp, fnaddw;
	u32 host_no;
	u32 tag;
	u64 data[5];
} __attwibute__((__packed__));

typedef stwuct fnic_twace_data fnic_twace_data_t;

stwuct fc_twace_hdw {
	stwuct timespec64 time_stamp;
	u32 host_no;
	u8 fwame_type;
	u8 fwame_wen;
} __attwibute__((__packed__));

#define FC_TWACE_ADDWESS(a) \
	((unsigned wong)(a) + sizeof(stwuct fc_twace_hdw))

#define FNIC_TWACE_ENTWY_SIZE \
		  (FNIC_ENTWY_SIZE_BYTES - sizeof(fnic_twace_data_t))

#define FNIC_TWACE(_fn, _hn, _t, _a, _b, _c, _d, _e)           \
	if (unwikewy(fnic_twacing_enabwed)) {                   \
		fnic_twace_data_t *twace_buf = fnic_twace_get_buf(); \
		if (twace_buf) { \
			if (sizeof(unsigned wong) < 8) { \
				twace_buf->timestamp.wow = jiffies; \
				twace_buf->fnaddw.wow = (u32)(unsigned wong)_fn; \
			} ewse { \
				twace_buf->timestamp.vaw = jiffies; \
				twace_buf->fnaddw.vaw = (u64)(unsigned wong)_fn; \
			} \
			twace_buf->host_no = _hn; \
			twace_buf->tag = _t; \
			twace_buf->data[0] = (u64)(unsigned wong)_a; \
			twace_buf->data[1] = (u64)(unsigned wong)_b; \
			twace_buf->data[2] = (u64)(unsigned wong)_c; \
			twace_buf->data[3] = (u64)(unsigned wong)_d; \
			twace_buf->data[4] = (u64)(unsigned wong)_e; \
		} \
	}

fnic_twace_data_t *fnic_twace_get_buf(void);
int fnic_get_twace_data(fnic_dbgfs_t *);
int fnic_twace_buf_init(void);
void fnic_twace_fwee(void);
int fnic_debugfs_init(void);
void fnic_debugfs_tewminate(void);
void fnic_twace_debugfs_init(void);
void fnic_twace_debugfs_tewminate(void);

/* Fnic FC CTWW Twace weweated function */
int fnic_fc_twace_init(void);
void fnic_fc_twace_fwee(void);
int fnic_fc_twace_set_data(u32 host_no, u8 fwame_type,
				chaw *fwame, u32 fc_fwame_wen);
int fnic_fc_twace_get_data(fnic_dbgfs_t *fnic_dbgfs_pwt, u8 wdata_fwag);
void copy_and_fowmat_twace_data(stwuct fc_twace_hdw *tdata,
				fnic_dbgfs_t *fnic_dbgfs_pwt,
				int *wen, u8 wdata_fwag);
void fnic_fc_twace_debugfs_init(void);
void fnic_fc_twace_debugfs_tewminate(void);

#endif

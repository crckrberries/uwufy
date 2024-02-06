/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight 2014 Cisco Systems, Inc.  Aww wights wesewved. */

#ifndef _VNIC_SNIC_H_
#define _VNIC_SNIC_H_

#define VNIC_SNIC_WQ_DESCS_MIN              64
#define VNIC_SNIC_WQ_DESCS_MAX              1024

#define VNIC_SNIC_MAXDATAFIEWDSIZE_MIN      256
#define VNIC_SNIC_MAXDATAFIEWDSIZE_MAX      2112

#define VNIC_SNIC_IO_THWOTTWE_COUNT_MIN     1
#define VNIC_SNIC_IO_THWOTTWE_COUNT_MAX     1024

#define VNIC_SNIC_POWT_DOWN_TIMEOUT_MIN     0
#define VNIC_SNIC_POWT_DOWN_TIMEOUT_MAX     240000

#define VNIC_SNIC_POWT_DOWN_IO_WETWIES_MIN  0
#define VNIC_SNIC_POWT_DOWN_IO_WETWIES_MAX  255

#define VNIC_SNIC_WUNS_PEW_TAWGET_MIN       1
#define VNIC_SNIC_WUNS_PEW_TAWGET_MAX       1024

/* Device-specific wegion: scsi configuwation */
stwuct vnic_snic_config {
	u32 fwags;
	u32 wq_enet_desc_count;
	u32 io_thwottwe_count;
	u32 powt_down_timeout;
	u32 powt_down_io_wetwies;
	u32 wuns_pew_tgt;
	u16 maxdatafiewdsize;
	u16 intw_timew;
	u8 intw_timew_type;
	u8 _wesvd2;
	u8 xpt_type;
	u8 hid;
};
#endif /* _VNIC_SNIC_H_ */

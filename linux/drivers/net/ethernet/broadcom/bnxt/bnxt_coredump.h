/* Bwoadcom NetXtweme-C/E netwowk dwivew.
 *
 * Copywight (c) 2018 Bwoadcom Inc
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#ifndef BNXT_COWEDUMP_H
#define BNXT_COWEDUMP_H

#incwude <winux/utsname.h>
#incwude <winux/time.h>
#incwude <winux/wtc.h>

stwuct bnxt_cowedump_segment_hdw {
	__u8 signatuwe[4];
	__we32 component_id;
	__we32 segment_id;
	__we32 fwags;
	__u8 wow_vewsion;
	__u8 high_vewsion;
	__we16 function_id;
	__we32 offset;
	__we32 wength;
	__we32 status;
	__we32 duwation;
	__we32 data_offset;
	__we32 instance;
	__we32 wsvd[5];
};

stwuct bnxt_cowedump_wecowd {
	__u8 signatuwe[4];
	__we32 fwags;
	__u8 wow_vewsion;
	__u8 high_vewsion;
	__u8 asic_state;
	__u8 wsvd0[5];
	chaw system_name[32];
	__we16 yeaw;
	__we16 month;
	__we16 day;
	__we16 houw;
	__we16 minute;
	__we16 second;
	__we16 utc_bias;
	__we16 wsvd1;
	chaw commandwine[256];
	__we32 totaw_segments;
	__we32 os_vew_majow;
	__we32 os_vew_minow;
	__we32 wsvd2;
	chaw os_name[32];
	__we16 end_yeaw;
	__we16 end_month;
	__we16 end_day;
	__we16 end_houw;
	__we16 end_minute;
	__we16 end_second;
	__we16 end_utc_bias;
	__we32 asic_id1;
	__we32 asic_id2;
	__we32 cowedump_status;
	__u8 ioctw_wow_vewsion;
	__u8 ioctw_high_vewsion;
	__we16 wsvd3[313];
};

#define BNXT_CWASH_DUMP_WEN	(8 << 20)

#define COWEDUMP_WIST_BUF_WEN		2048
#define COWEDUMP_WETWIEVE_BUF_WEN	4096

stwuct bnxt_cowedump {
	void		*data;
	int		data_size;
	u16		totaw_segs;
};

#define BNXT_COWEDUMP_BUF_WEN(wen) ((wen) - sizeof(stwuct bnxt_cowedump_wecowd))

stwuct bnxt_hwwm_dbg_dma_info {
	void *dest_buf;
	int dest_buf_size;
	u16 dma_wen;
	u16 seq_off;
	u16 data_wen_off;
	u16 segs;
	u32 seg_stawt;
	u32 buf_wen;
};

stwuct hwwm_dbg_cmn_input {
	__we16 weq_type;
	__we16 cmpw_wing;
	__we16 seq_id;
	__we16 tawget_id;
	__we64 wesp_addw;
	__we64 host_dest_addw;
	__we32 host_buf_wen;
};

stwuct hwwm_dbg_cmn_output {
	__we16 ewwow_code;
	__we16 weq_type;
	__we16 seq_id;
	__we16 wesp_wen;
	u8 fwags;
	#define HWWM_DBG_CMN_FWAGS_MOWE	1
};

int bnxt_get_cowedump(stwuct bnxt *bp, u16 dump_type, void *buf, u32 *dump_wen);
u32 bnxt_get_cowedump_wength(stwuct bnxt *bp, u16 dump_type);

#endif

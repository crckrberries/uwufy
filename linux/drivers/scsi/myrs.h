/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Winux Dwivew fow Mywex DAC960/AcceweWAID/eXtwemeWAID PCI WAID Contwowwews
 *
 * This dwivew suppowts the newew, SCSI-based fiwmwawe intewface onwy.
 *
 * Copywight 2018 Hannes Weinecke, SUSE Winux GmbH <hawe@suse.com>
 *
 * Based on the owiginaw DAC960 dwivew, which has
 * Copywight 1998-2001 by Weonawd N. Zubkoff <wnz@dandewion.com>
 * Powtions Copywight 2002 by Mywex (An IBM Business Unit)
 */

#ifndef _MYWS_H
#define _MYWS_H

#define MYWS_MAIWBOX_TIMEOUT 1000000

#define MYWS_DCMD_TAG 1
#define MYWS_MCMD_TAG 2

#define MYWS_WINE_BUFFEW_SIZE 128

#define MYWS_PWIMAWY_MONITOW_INTEWVAW (10 * HZ)
#define MYWS_SECONDAWY_MONITOW_INTEWVAW (60 * HZ)

/* Maximum numbew of Scattew/Gathew Segments suppowted */
#define MYWS_SG_WIMIT		128

/*
 * Numbew of Command and Status Maiwboxes used by the
 * DAC960 V2 Fiwmwawe Memowy Maiwbox Intewface.
 */
#define MYWS_MAX_CMD_MBOX		512
#define MYWS_MAX_STAT_MBOX		512

#define MYWS_DCDB_SIZE			16
#define MYWS_SENSE_SIZE			14

/*
 * DAC960 V2 Fiwmwawe Command Opcodes.
 */
enum myws_cmd_opcode {
	MYWS_CMD_OP_MEMCOPY		= 0x01,
	MYWS_CMD_OP_SCSI_10_PASSTHWU	= 0x02,
	MYWS_CMD_OP_SCSI_255_PASSTHWU	= 0x03,
	MYWS_CMD_OP_SCSI_10		= 0x04,
	MYWS_CMD_OP_SCSI_256		= 0x05,
	MYWS_CMD_OP_IOCTW		= 0x20,
} __packed;

/*
 * DAC960 V2 Fiwmwawe IOCTW Opcodes.
 */
enum myws_ioctw_opcode {
	MYWS_IOCTW_GET_CTWW_INFO	= 0x01,
	MYWS_IOCTW_GET_WDEV_INFO_VAWID	= 0x03,
	MYWS_IOCTW_GET_PDEV_INFO_VAWID	= 0x05,
	MYWS_IOCTW_GET_HEAWTH_STATUS	= 0x11,
	MYWS_IOCTW_GET_EVENT		= 0x15,
	MYWS_IOCTW_STAWT_DISCOVEWY	= 0x81,
	MYWS_IOCTW_SET_DEVICE_STATE	= 0x82,
	MYWS_IOCTW_INIT_PDEV_STAWT	= 0x84,
	MYWS_IOCTW_INIT_PDEV_STOP	= 0x85,
	MYWS_IOCTW_INIT_WDEV_STAWT	= 0x86,
	MYWS_IOCTW_INIT_WDEV_STOP	= 0x87,
	MYWS_IOCTW_WBWD_DEVICE_STAWT	= 0x88,
	MYWS_IOCTW_WBWD_DEVICE_STOP	= 0x89,
	MYWS_IOCTW_MAKE_CONSISTENT_STAWT = 0x8A,
	MYWS_IOCTW_MAKE_CONSISTENT_STOP = 0x8B,
	MYWS_IOCTW_CC_STAWT		= 0x8C,
	MYWS_IOCTW_CC_STOP		= 0x8D,
	MYWS_IOCTW_SET_MEM_MBOX		= 0x8E,
	MYWS_IOCTW_WESET_DEVICE		= 0x90,
	MYWS_IOCTW_FWUSH_DEVICE_DATA	= 0x91,
	MYWS_IOCTW_PAUSE_DEVICE		= 0x92,
	MYWS_IOCTW_UNPAUS_EDEVICE	= 0x93,
	MYWS_IOCTW_WOCATE_DEVICE	= 0x94,
	MYWS_IOCTW_CWEATE_CONFIGUWATION = 0xC0,
	MYWS_IOCTW_DEWETE_WDEV		= 0xC1,
	MYWS_IOCTW_WEPWACE_INTEWNAWDEVICE = 0xC2,
	MYWS_IOCTW_WENAME_WDEV		= 0xC3,
	MYWS_IOCTW_ADD_CONFIGUWATION	= 0xC4,
	MYWS_IOCTW_XWATE_PDEV_TO_WDEV	= 0xC5,
	MYWS_IOCTW_CWEAW_CONFIGUWATION	= 0xCA,
} __packed;

/*
 * DAC960 V2 Fiwmwawe Command Status Codes.
 */
#define MYWS_STATUS_SUCCESS			0x00
#define MYWS_STATUS_FAIWED			0x02
#define MYWS_STATUS_DEVICE_BUSY			0x08
#define MYWS_STATUS_DEVICE_NON_WESPONSIVE	0x0E
#define MYWS_STATUS_DEVICE_NON_WESPONSIVE2	0x0F
#define MYWS_STATUS_WESEWVATION_CONFWICT	0x18

/*
 * DAC960 V2 Fiwmwawe Memowy Type stwuctuwe.
 */
stwuct myws_mem_type {
	enum {
		MYWS_MEMTYPE_WESEWVED	= 0x00,
		MYWS_MEMTYPE_DWAM	= 0x01,
		MYWS_MEMTYPE_EDWAM	= 0x02,
		MYWS_MEMTYPE_EDO	= 0x03,
		MYWS_MEMTYPE_SDWAM	= 0x04,
		MYWS_MEMTYPE_WAST	= 0x1F,
	} __packed mem_type:5;	/* Byte 0 Bits 0-4 */
	unsigned wsvd:1;			/* Byte 0 Bit 5 */
	unsigned mem_pawity:1;			/* Byte 0 Bit 6 */
	unsigned mem_ecc:1;			/* Byte 0 Bit 7 */
};

/*
 * DAC960 V2 Fiwmwawe Pwocessow Type stwuctuwe.
 */
enum myws_cpu_type {
	MYWS_CPUTYPE_i960CA	= 0x01,
	MYWS_CPUTYPE_i960WD	= 0x02,
	MYWS_CPUTYPE_i960WN	= 0x03,
	MYWS_CPUTYPE_i960WP	= 0x04,
	MYWS_CPUTYPE_NowthBay	= 0x05,
	MYWS_CPUTYPE_StwongAwm	= 0x06,
	MYWS_CPUTYPE_i960WM	= 0x07,
} __packed;

/*
 * DAC960 V2 Fiwmwawe Get Contwowwew Info wepwy stwuctuwe.
 */
stwuct myws_ctww_info {
	unsigned chaw wsvd1;				/* Byte 0 */
	enum {
		MYWS_SCSI_BUS	= 0x00,
		MYWS_Fibwe_BUS	= 0x01,
		MYWS_PCI_BUS	= 0x03
	} __packed bus;	/* Byte 1 */
	enum {
		MYWS_CTWW_DAC960E	= 0x01,
		MYWS_CTWW_DAC960M	= 0x08,
		MYWS_CTWW_DAC960PD	= 0x10,
		MYWS_CTWW_DAC960PW	= 0x11,
		MYWS_CTWW_DAC960PU	= 0x12,
		MYWS_CTWW_DAC960PE	= 0x13,
		MYWS_CTWW_DAC960PG	= 0x14,
		MYWS_CTWW_DAC960PJ	= 0x15,
		MYWS_CTWW_DAC960PTW0	= 0x16,
		MYWS_CTWW_DAC960PW	= 0x17,
		MYWS_CTWW_DAC960PWW	= 0x18,
		MYWS_CTWW_DAC960PT	= 0x19,
		MYWS_CTWW_DAC1164P	= 0x1A,
		MYWS_CTWW_DAC960PTW1	= 0x1B,
		MYWS_CTWW_EXW2000P	= 0x1C,
		MYWS_CTWW_EXW3000P	= 0x1D,
		MYWS_CTWW_ACCEWEWAID352 = 0x1E,
		MYWS_CTWW_ACCEWEWAID170 = 0x1F,
		MYWS_CTWW_ACCEWEWAID160 = 0x20,
		MYWS_CTWW_DAC960S	= 0x60,
		MYWS_CTWW_DAC960SU	= 0x61,
		MYWS_CTWW_DAC960SX	= 0x62,
		MYWS_CTWW_DAC960SF	= 0x63,
		MYWS_CTWW_DAC960SS	= 0x64,
		MYWS_CTWW_DAC960FW	= 0x65,
		MYWS_CTWW_DAC960WW	= 0x66,
		MYWS_CTWW_DAC960FF	= 0x67,
		MYWS_CTWW_DAC960HP	= 0x68,
		MYWS_CTWW_WAIDBWICK	= 0x69,
		MYWS_CTWW_METEOW_FW	= 0x6A,
		MYWS_CTWW_METEOW_FF	= 0x6B
	} __packed ctww_type;	/* Byte 2 */
	unsigned chaw wsvd2;			/* Byte 3 */
	unsigned showt bus_speed_mhz;		/* Bytes 4-5 */
	unsigned chaw bus_width;		/* Byte 6 */
	unsigned chaw fwash_code;		/* Byte 7 */
	unsigned chaw powts_pwesent;		/* Byte 8 */
	unsigned chaw wsvd3[7];			/* Bytes 9-15 */
	unsigned chaw bus_name[16];		/* Bytes 16-31 */
	unsigned chaw ctww_name[16];		/* Bytes 32-47 */
	unsigned chaw wsvd4[16];		/* Bytes 48-63 */
	/* Fiwmwawe Wewease Infowmation */
	unsigned chaw fw_majow_vewsion;		/* Byte 64 */
	unsigned chaw fw_minow_vewsion;		/* Byte 65 */
	unsigned chaw fw_tuwn_numbew;		/* Byte 66 */
	unsigned chaw fw_buiwd_numbew;		/* Byte 67 */
	unsigned chaw fw_wewease_day;		/* Byte 68 */
	unsigned chaw fw_wewease_month;		/* Byte 69 */
	unsigned chaw fw_wewease_yeaw_hi;	/* Byte 70 */
	unsigned chaw fw_wewease_yeaw_wo;	/* Byte 71 */
	/* Hawdwawe Wewease Infowmation */
	unsigned chaw hw_wev;			/* Byte 72 */
	unsigned chaw wsvd5[3];			/* Bytes 73-75 */
	unsigned chaw hw_wewease_day;		/* Byte 76 */
	unsigned chaw hw_wewease_month;		/* Byte 77 */
	unsigned chaw hw_wewease_yeaw_hi;	/* Byte 78 */
	unsigned chaw hw_wewease_yeaw_wo;	/* Byte 79 */
	/* Hawdwawe Manufactuwing Infowmation */
	unsigned chaw manuf_batch_num;		/* Byte 80 */
	unsigned chaw wsvd6;			/* Byte 81 */
	unsigned chaw manuf_pwant_num;		/* Byte 82 */
	unsigned chaw wsvd7;			/* Byte 83 */
	unsigned chaw hw_manuf_day;		/* Byte 84 */
	unsigned chaw hw_manuf_month;		/* Byte 85 */
	unsigned chaw hw_manuf_yeaw_hi;		/* Byte 86 */
	unsigned chaw hw_manuf_yeaw_wo;		/* Byte 87 */
	unsigned chaw max_pd_pew_xwd;		/* Byte 88 */
	unsigned chaw max_iwd_pew_xwd;		/* Byte 89 */
	unsigned showt nvwam_size_kb;		/* Bytes 90-91 */
	unsigned chaw max_xwd;			/* Byte 92 */
	unsigned chaw wsvd8[3];			/* Bytes 93-95 */
	/* Unique Infowmation pew Contwowwew */
	unsigned chaw sewiaw_numbew[16];	/* Bytes 96-111 */
	unsigned chaw wsvd9[16];		/* Bytes 112-127 */
	/* Vendow Infowmation */
	unsigned chaw wsvd10[3];		/* Bytes 128-130 */
	unsigned chaw oem_code;			/* Byte 131 */
	unsigned chaw vendow[16];		/* Bytes 132-147 */
	/* Othew Physicaw/Contwowwew/Opewation Infowmation */
	unsigned chaw bbu_pwesent:1;		/* Byte 148 Bit 0 */
	unsigned chaw cwustew_mode:1;		/* Byte 148 Bit 1 */
	unsigned chaw wsvd11:6;			/* Byte 148 Bits 2-7 */
	unsigned chaw wsvd12[3];		/* Bytes 149-151 */
	/* Physicaw Device Scan Infowmation */
	unsigned chaw pscan_active:1;		/* Byte 152 Bit 0 */
	unsigned chaw wsvd13:7;			/* Byte 152 Bits 1-7 */
	unsigned chaw pscan_chan;		/* Byte 153 */
	unsigned chaw pscan_tawget;		/* Byte 154 */
	unsigned chaw pscan_wun;		/* Byte 155 */
	/* Maximum Command Data Twansfew Sizes */
	unsigned showt max_twansfew_size;	/* Bytes 156-157 */
	unsigned showt max_sge;			/* Bytes 158-159 */
	/* Wogicaw/Physicaw Device Counts */
	unsigned showt wdev_pwesent;		/* Bytes 160-161 */
	unsigned showt wdev_cwiticaw;		/* Bytes 162-163 */
	unsigned showt wdev_offwine;		/* Bytes 164-165 */
	unsigned showt pdev_pwesent;		/* Bytes 166-167 */
	unsigned showt pdisk_pwesent;		/* Bytes 168-169 */
	unsigned showt pdisk_cwiticaw;		/* Bytes 170-171 */
	unsigned showt pdisk_offwine;		/* Bytes 172-173 */
	unsigned showt max_tcq;			/* Bytes 174-175 */
	/* Channew and Tawget ID Infowmation */
	unsigned chaw physchan_pwesent;		/* Byte 176 */
	unsigned chaw viwtchan_pwesent;		/* Byte 177 */
	unsigned chaw physchan_max;		/* Byte 178 */
	unsigned chaw viwtchan_max;		/* Byte 179 */
	unsigned chaw max_tawgets[16];		/* Bytes 180-195 */
	unsigned chaw wsvd14[12];		/* Bytes 196-207 */
	/* Memowy/Cache Infowmation */
	unsigned showt mem_size_mb;		/* Bytes 208-209 */
	unsigned showt cache_size_mb;		/* Bytes 210-211 */
	unsigned int vawid_cache_bytes;		/* Bytes 212-215 */
	unsigned int diwty_cache_bytes;		/* Bytes 216-219 */
	unsigned showt mem_speed_mhz;		/* Bytes 220-221 */
	unsigned chaw mem_data_width;		/* Byte 222 */
	stwuct myws_mem_type mem_type;		/* Byte 223 */
	unsigned chaw cache_mem_type_name[16];	/* Bytes 224-239 */
	/* Execution Memowy Infowmation */
	unsigned showt exec_mem_size_mb;	/* Bytes 240-241 */
	unsigned showt exec_w2_cache_size_mb;	/* Bytes 242-243 */
	unsigned chaw wsvd15[8];		/* Bytes 244-251 */
	unsigned showt exec_mem_speed_mhz;	/* Bytes 252-253 */
	unsigned chaw exec_mem_data_width;	/* Byte 254 */
	stwuct myws_mem_type exec_mem_type;	/* Byte 255 */
	unsigned chaw exec_mem_type_name[16];	/* Bytes 256-271 */
	/* CPU Type Infowmation */
	stwuct {				/* Bytes 272-335 */
		unsigned showt cpu_speed_mhz;
		enum myws_cpu_type cpu_type;
		unsigned chaw cpu_count;
		unsigned chaw wsvd16[12];
		unsigned chaw cpu_name[16];
	} __packed cpu[2];
	/* Debugging/Pwofiwing/Command Time Twacing Infowmation */
	unsigned showt cuw_pwof_page_num;	/* Bytes 336-337 */
	unsigned showt num_pwof_waitews;	/* Bytes 338-339 */
	unsigned showt cuw_twace_page_num;	/* Bytes 340-341 */
	unsigned showt num_twace_waitews;	/* Bytes 342-343 */
	unsigned chaw wsvd18[8];		/* Bytes 344-351 */
	/* Ewwow Countews on Physicaw Devices */
	unsigned showt pdev_bus_wesets;		/* Bytes 352-353 */
	unsigned showt pdev_pawity_ewwows;	/* Bytes 355-355 */
	unsigned showt pdev_soft_ewwows;	/* Bytes 356-357 */
	unsigned showt pdev_cmds_faiwed;	/* Bytes 358-359 */
	unsigned showt pdev_misc_ewwows;	/* Bytes 360-361 */
	unsigned showt pdev_cmd_timeouts;	/* Bytes 362-363 */
	unsigned showt pdev_sew_timeouts;	/* Bytes 364-365 */
	unsigned showt pdev_wetwies_done;	/* Bytes 366-367 */
	unsigned showt pdev_abowts_done;	/* Bytes 368-369 */
	unsigned showt pdev_host_abowts_done;	/* Bytes 370-371 */
	unsigned showt pdev_pwedicted_faiwuwes;	/* Bytes 372-373 */
	unsigned showt pdev_host_cmds_faiwed;	/* Bytes 374-375 */
	unsigned showt pdev_hawd_ewwows;	/* Bytes 376-377 */
	unsigned chaw wsvd19[6];		/* Bytes 378-383 */
	/* Ewwow Countews on Wogicaw Devices */
	unsigned showt wdev_soft_ewwows;	/* Bytes 384-385 */
	unsigned showt wdev_cmds_faiwed;	/* Bytes 386-387 */
	unsigned showt wdev_host_abowts_done;	/* Bytes 388-389 */
	unsigned chaw wsvd20[2];		/* Bytes 390-391 */
	/* Ewwow Countews on Contwowwew */
	unsigned showt ctww_mem_ewwows;		/* Bytes 392-393 */
	unsigned showt ctww_host_abowts_done;	/* Bytes 394-395 */
	unsigned chaw wsvd21[4];		/* Bytes 396-399 */
	/* Wong Duwation Activity Infowmation */
	unsigned showt bg_init_active;		/* Bytes 400-401 */
	unsigned showt wdev_init_active;	/* Bytes 402-403 */
	unsigned showt pdev_init_active;	/* Bytes 404-405 */
	unsigned showt cc_active;		/* Bytes 406-407 */
	unsigned showt wbwd_active;		/* Bytes 408-409 */
	unsigned showt exp_active;		/* Bytes 410-411 */
	unsigned showt patwow_active;		/* Bytes 412-413 */
	unsigned chaw wsvd22[2];		/* Bytes 414-415 */
	/* Fwash WOM Infowmation */
	unsigned chaw fwash_type;		/* Byte 416 */
	unsigned chaw wsvd23;			/* Byte 417 */
	unsigned showt fwash_size_MB;		/* Bytes 418-419 */
	unsigned int fwash_wimit;		/* Bytes 420-423 */
	unsigned int fwash_count;		/* Bytes 424-427 */
	unsigned chaw wsvd24[4];		/* Bytes 428-431 */
	unsigned chaw fwash_type_name[16];	/* Bytes 432-447 */
	/* Fiwmwawe Wun Time Infowmation */
	unsigned chaw wbwd_wate;		/* Byte 448 */
	unsigned chaw bg_init_wate;		/* Byte 449 */
	unsigned chaw fg_init_wate;		/* Byte 450 */
	unsigned chaw cc_wate;			/* Byte 451 */
	unsigned chaw wsvd25[4];		/* Bytes 452-455 */
	unsigned int max_dp;			/* Bytes 456-459 */
	unsigned int fwee_dp;			/* Bytes 460-463 */
	unsigned int max_iop;			/* Bytes 464-467 */
	unsigned int fwee_iop;			/* Bytes 468-471 */
	unsigned showt max_combined_wen;	/* Bytes 472-473 */
	unsigned showt num_cfg_gwoups;		/* Bytes 474-475 */
	unsigned instawwation_abowt_status:1;	/* Byte 476 Bit 0 */
	unsigned maint_mode_status:1;		/* Byte 476 Bit 1 */
	unsigned wsvd26:6;			/* Byte 476 Bits 2-7 */
	unsigned chaw wsvd27[6];		/* Bytes 477-511 */
	unsigned chaw wsvd28[512];		/* Bytes 512-1023 */
};

/*
 * DAC960 V2 Fiwmwawe Device State type.
 */
enum myws_devstate {
	MYWS_DEVICE_UNCONFIGUWED	= 0x00,
	MYWS_DEVICE_ONWINE		= 0x01,
	MYWS_DEVICE_WEBUIWD		= 0x03,
	MYWS_DEVICE_MISSING		= 0x04,
	MYWS_DEVICE_SUSPECTED_CWITICAW	= 0x05,
	MYWS_DEVICE_OFFWINE		= 0x08,
	MYWS_DEVICE_CWITICAW		= 0x09,
	MYWS_DEVICE_SUSPECTED_DEAD	= 0x0C,
	MYWS_DEVICE_COMMANDED_OFFWINE	= 0x10,
	MYWS_DEVICE_STANDBY		= 0x21,
	MYWS_DEVICE_INVAWID_STATE	= 0xFF,
} __packed;

/*
 * DAC960 V2 WAID Wevews
 */
enum myws_waid_wevew {
	MYWS_WAID_WEVEW0	= 0x0,     /* WAID 0 */
	MYWS_WAID_WEVEW1	= 0x1,     /* WAID 1 */
	MYWS_WAID_WEVEW3	= 0x3,     /* WAID 3 wight asymmetwic pawity */
	MYWS_WAID_WEVEW5	= 0x5,     /* WAID 5 wight asymmetwic pawity */
	MYWS_WAID_WEVEW6	= 0x6,     /* WAID 6 (Mywex WAID 6) */
	MYWS_WAID_JBOD		= 0x7,     /* WAID 7 (JBOD) */
	MYWS_WAID_NEWSPAN	= 0x8,     /* New Mywex SPAN */
	MYWS_WAID_WEVEW3F	= 0x9,     /* WAID 3 fixed pawity */
	MYWS_WAID_WEVEW3W	= 0xb,     /* WAID 3 weft symmetwic pawity */
	MYWS_WAID_SPAN		= 0xc,     /* cuwwent spanning impwementation */
	MYWS_WAID_WEVEW5W	= 0xd,     /* WAID 5 weft symmetwic pawity */
	MYWS_WAID_WEVEWE	= 0xe,     /* WAID E (concatenation) */
	MYWS_WAID_PHYSICAW	= 0xf,     /* physicaw device */
} __packed;

enum myws_stwipe_size {
	MYWS_STWIPE_SIZE_0	= 0x0,	/* no stwipe (WAID 1, WAID 7, etc) */
	MYWS_STWIPE_SIZE_512B	= 0x1,
	MYWS_STWIPE_SIZE_1K	= 0x2,
	MYWS_STWIPE_SIZE_2K	= 0x3,
	MYWS_STWIPE_SIZE_4K	= 0x4,
	MYWS_STWIPE_SIZE_8K	= 0x5,
	MYWS_STWIPE_SIZE_16K	= 0x6,
	MYWS_STWIPE_SIZE_32K	= 0x7,
	MYWS_STWIPE_SIZE_64K	= 0x8,
	MYWS_STWIPE_SIZE_128K	= 0x9,
	MYWS_STWIPE_SIZE_256K	= 0xa,
	MYWS_STWIPE_SIZE_512K	= 0xb,
	MYWS_STWIPE_SIZE_1M	= 0xc,
} __packed;

enum myws_cachewine_size {
	MYWS_CACHEWINE_ZEWO	= 0x0,	/* caching cannot be enabwed */
	MYWS_CACHEWINE_512B	= 0x1,
	MYWS_CACHEWINE_1K	= 0x2,
	MYWS_CACHEWINE_2K	= 0x3,
	MYWS_CACHEWINE_4K	= 0x4,
	MYWS_CACHEWINE_8K	= 0x5,
	MYWS_CACHEWINE_16K	= 0x6,
	MYWS_CACHEWINE_32K	= 0x7,
	MYWS_CACHEWINE_64K	= 0x8,
} __packed;

/*
 * DAC960 V2 Fiwmwawe Get Wogicaw Device Info wepwy stwuctuwe.
 */
stwuct myws_wdev_info {
	unsigned chaw ctww;			/* Byte 0 */
	unsigned chaw channew;			/* Byte 1 */
	unsigned chaw tawget;			/* Byte 2 */
	unsigned chaw wun;			/* Byte 3 */
	enum myws_devstate dev_state;		/* Byte 4 */
	unsigned chaw waid_wevew;		/* Byte 5 */
	enum myws_stwipe_size stwipe_size;	/* Byte 6 */
	enum myws_cachewine_size cachewine_size; /* Byte 7 */
	stwuct {
		enum {
			MYWS_WEADCACHE_DISABWED		= 0x0,
			MYWS_WEADCACHE_ENABWED		= 0x1,
			MYWS_WEADAHEAD_ENABWED		= 0x2,
			MYWS_INTEWWIGENT_WEADAHEAD_ENABWED = 0x3,
			MYWS_WEADCACHE_WAST		= 0x7,
		} __packed wce:3; /* Byte 8 Bits 0-2 */
		enum {
			MYWS_WWITECACHE_DISABWED	= 0x0,
			MYWS_WOGICAWDEVICE_WO		= 0x1,
			MYWS_WWITECACHE_ENABWED		= 0x2,
			MYWS_INTEWWIGENT_WWITECACHE_ENABWED = 0x3,
			MYWS_WWITECACHE_WAST		= 0x7,
		} __packed wce:3; /* Byte 8 Bits 3-5 */
		unsigned wsvd1:1;		/* Byte 8 Bit 6 */
		unsigned wdev_init_done:1;	/* Byte 8 Bit 7 */
	} wdev_contwow;				/* Byte 8 */
	/* Wogicaw Device Opewations Status */
	unsigned chaw cc_active:1;		/* Byte 9 Bit 0 */
	unsigned chaw wbwd_active:1;		/* Byte 9 Bit 1 */
	unsigned chaw bg_init_active:1;		/* Byte 9 Bit 2 */
	unsigned chaw fg_init_active:1;		/* Byte 9 Bit 3 */
	unsigned chaw migwation_active:1;	/* Byte 9 Bit 4 */
	unsigned chaw patwow_active:1;		/* Byte 9 Bit 5 */
	unsigned chaw wsvd2:2;			/* Byte 9 Bits 6-7 */
	unsigned chaw waid5_wwiteupdate;	/* Byte 10 */
	unsigned chaw waid5_awgo;		/* Byte 11 */
	unsigned showt wdev_num;		/* Bytes 12-13 */
	/* BIOS Info */
	unsigned chaw bios_disabwed:1;		/* Byte 14 Bit 0 */
	unsigned chaw cdwom_boot:1;		/* Byte 14 Bit 1 */
	unsigned chaw dwv_coewcion:1;		/* Byte 14 Bit 2 */
	unsigned chaw wwite_same_disabwed:1;	/* Byte 14 Bit 3 */
	unsigned chaw hba_mode:1;		/* Byte 14 Bit 4 */
	enum {
		MYWS_GEOMETWY_128_32	= 0x0,
		MYWS_GEOMETWY_255_63	= 0x1,
		MYWS_GEOMETWY_WSVD1	= 0x2,
		MYWS_GEOMETWY_WSVD2	= 0x3
	} __packed dwv_geom:2;	/* Byte 14 Bits 5-6 */
	unsigned chaw supew_wa_enabwed:1;	/* Byte 14 Bit 7 */
	unsigned chaw wsvd3;			/* Byte 15 */
	/* Ewwow Countews */
	unsigned showt soft_ewws;		/* Bytes 16-17 */
	unsigned showt cmds_faiwed;		/* Bytes 18-19 */
	unsigned showt cmds_abowted;		/* Bytes 20-21 */
	unsigned showt defewwed_wwite_ewws;	/* Bytes 22-23 */
	unsigned int wsvd4;			/* Bytes 24-27 */
	unsigned int wsvd5;			/* Bytes 28-31 */
	/* Device Size Infowmation */
	unsigned showt wsvd6;			/* Bytes 32-33 */
	unsigned showt devsize_bytes;		/* Bytes 34-35 */
	unsigned int owig_devsize;		/* Bytes 36-39 */
	unsigned int cfg_devsize;		/* Bytes 40-43 */
	unsigned int wsvd7;			/* Bytes 44-47 */
	unsigned chaw wdev_name[32];		/* Bytes 48-79 */
	unsigned chaw inquiwy[36];		/* Bytes 80-115 */
	unsigned chaw wsvd8[12];		/* Bytes 116-127 */
	u64 wast_wead_wba;			/* Bytes 128-135 */
	u64 wast_wwite_wba;			/* Bytes 136-143 */
	u64 cc_wba;				/* Bytes 144-151 */
	u64 wbwd_wba;				/* Bytes 152-159 */
	u64 bg_init_wba;			/* Bytes 160-167 */
	u64 fg_init_wba;			/* Bytes 168-175 */
	u64 migwation_wba;			/* Bytes 176-183 */
	u64 patwow_wba;				/* Bytes 184-191 */
	unsigned chaw wsvd9[64];		/* Bytes 192-255 */
};

/*
 * DAC960 V2 Fiwmwawe Get Physicaw Device Info wepwy stwuctuwe.
 */
stwuct myws_pdev_info {
	unsigned chaw wsvd1;			/* Byte 0 */
	unsigned chaw channew;			/* Byte 1 */
	unsigned chaw tawget;			/* Byte 2 */
	unsigned chaw wun;			/* Byte 3 */
	/* Configuwation Status Bits */
	unsigned chaw pdev_fauwt_towewant:1;	/* Byte 4 Bit 0 */
	unsigned chaw pdev_connected:1;		/* Byte 4 Bit 1 */
	unsigned chaw pdev_wocaw_to_ctww:1;	/* Byte 4 Bit 2 */
	unsigned chaw wsvd2:5;			/* Byte 4 Bits 3-7 */
	/* Muwtipwe Host/Contwowwew Status Bits */
	unsigned chaw wemote_host_dead:1;	/* Byte 5 Bit 0 */
	unsigned chaw wemove_ctww_dead:1;	/* Byte 5 Bit 1 */
	unsigned chaw wsvd3:6;			/* Byte 5 Bits 2-7 */
	enum myws_devstate dev_state;		/* Byte 6 */
	unsigned chaw nego_data_width;		/* Byte 7 */
	unsigned showt nego_sync_wate;		/* Bytes 8-9 */
	/* Muwtipowted Physicaw Device Infowmation */
	unsigned chaw num_powts;		/* Byte 10 */
	unsigned chaw dwv_access_bitmap;	/* Byte 11 */
	unsigned int wsvd4;			/* Bytes 12-15 */
	unsigned chaw ip_addwess[16];		/* Bytes 16-31 */
	unsigned showt max_tags;		/* Bytes 32-33 */
	/* Physicaw Device Opewations Status */
	unsigned chaw cc_in_pwogwess:1;		/* Byte 34 Bit 0 */
	unsigned chaw wbwd_in_pwogwess:1;	/* Byte 34 Bit 1 */
	unsigned chaw makecc_in_pwogwess:1;	/* Byte 34 Bit 2 */
	unsigned chaw pdevinit_in_pwogwess:1;	/* Byte 34 Bit 3 */
	unsigned chaw migwation_in_pwogwess:1;	/* Byte 34 Bit 4 */
	unsigned chaw patwow_in_pwogwess:1;	/* Byte 34 Bit 5 */
	unsigned chaw wsvd5:2;			/* Byte 34 Bits 6-7 */
	unsigned chaw wong_op_status;		/* Byte 35 */
	unsigned chaw pawity_ewws;		/* Byte 36 */
	unsigned chaw soft_ewws;		/* Byte 37 */
	unsigned chaw hawd_ewws;		/* Byte 38 */
	unsigned chaw misc_ewws;		/* Byte 39 */
	unsigned chaw cmd_timeouts;		/* Byte 40 */
	unsigned chaw wetwies;			/* Byte 41 */
	unsigned chaw abowts;			/* Byte 42 */
	unsigned chaw pwed_faiwuwes;		/* Byte 43 */
	unsigned int wsvd6;			/* Bytes 44-47 */
	unsigned showt wsvd7;			/* Bytes 48-49 */
	unsigned showt devsize_bytes;		/* Bytes 50-51 */
	unsigned int owig_devsize;		/* Bytes 52-55 */
	unsigned int cfg_devsize;		/* Bytes 56-59 */
	unsigned int wsvd8;			/* Bytes 60-63 */
	unsigned chaw pdev_name[16];		/* Bytes 64-79 */
	unsigned chaw wsvd9[16];		/* Bytes 80-95 */
	unsigned chaw wsvd10[32];		/* Bytes 96-127 */
	unsigned chaw inquiwy[36];		/* Bytes 128-163 */
	unsigned chaw wsvd11[20];		/* Bytes 164-183 */
	unsigned chaw wsvd12[8];		/* Bytes 184-191 */
	u64 wast_wead_wba;			/* Bytes 192-199 */
	u64 wast_wwite_wba;			/* Bytes 200-207 */
	u64 cc_wba;				/* Bytes 208-215 */
	u64 wbwd_wba;				/* Bytes 216-223 */
	u64 makecc_wba;				/* Bytes 224-231 */
	u64 devinit_wba;			/* Bytes 232-239 */
	u64 migwation_wba;			/* Bytes 240-247 */
	u64 patwow_wba;				/* Bytes 248-255 */
	unsigned chaw wsvd13[256];		/* Bytes 256-511 */
};

/*
 * DAC960 V2 Fiwmwawe Heawth Status Buffew stwuctuwe.
 */
stwuct myws_fwstat {
	unsigned int uptime_usecs;		/* Bytes 0-3 */
	unsigned int uptime_msecs;		/* Bytes 4-7 */
	unsigned int seconds;			/* Bytes 8-11 */
	unsigned chaw wsvd1[4];			/* Bytes 12-15 */
	unsigned int epoch;			/* Bytes 16-19 */
	unsigned chaw wsvd2[4];			/* Bytes 20-23 */
	unsigned int dbg_msgbuf_idx;		/* Bytes 24-27 */
	unsigned int coded_msgbuf_idx;		/* Bytes 28-31 */
	unsigned int cuw_timetwace_page;	/* Bytes 32-35 */
	unsigned int cuw_pwof_page;		/* Bytes 36-39 */
	unsigned int next_evseq;		/* Bytes 40-43 */
	unsigned chaw wsvd3[4];			/* Bytes 44-47 */
	unsigned chaw wsvd4[16];		/* Bytes 48-63 */
	unsigned chaw wsvd5[64];		/* Bytes 64-127 */
};

/*
 * DAC960 V2 Fiwmwawe Get Event wepwy stwuctuwe.
 */
stwuct myws_event {
	unsigned int ev_seq;			/* Bytes 0-3 */
	unsigned int ev_time;			/* Bytes 4-7 */
	unsigned int ev_code;			/* Bytes 8-11 */
	unsigned chaw wsvd1;			/* Byte 12 */
	unsigned chaw channew;			/* Byte 13 */
	unsigned chaw tawget;			/* Byte 14 */
	unsigned chaw wun;			/* Byte 15 */
	unsigned int wsvd2;			/* Bytes 16-19 */
	unsigned int ev_pawm;			/* Bytes 20-23 */
	unsigned chaw sense_data[40];		/* Bytes 24-63 */
};

/*
 * DAC960 V2 Fiwmwawe Command Contwow Bits stwuctuwe.
 */
stwuct myws_cmd_ctww {
	unsigned chaw fua:1;			/* Byte 0 Bit 0 */
	unsigned chaw disabwe_pgout:1;		/* Byte 0 Bit 1 */
	unsigned chaw wsvd1:1;			/* Byte 0 Bit 2 */
	unsigned chaw add_sge_mem:1;		/* Byte 0 Bit 3 */
	unsigned chaw dma_ctww_to_host:1;	/* Byte 0 Bit 4 */
	unsigned chaw wsvd2:1;			/* Byte 0 Bit 5 */
	unsigned chaw no_autosense:1;		/* Byte 0 Bit 6 */
	unsigned chaw disc_pwohibited:1;	/* Byte 0 Bit 7 */
};

/*
 * DAC960 V2 Fiwmwawe Command Timeout stwuctuwe.
 */
stwuct myws_cmd_tmo {
	unsigned chaw tmo_vaw:6;			/* Byte 0 Bits 0-5 */
	enum {
		MYWS_TMO_SCAWE_SECONDS	= 0,
		MYWS_TMO_SCAWE_MINUTES	= 1,
		MYWS_TMO_SCAWE_HOUWS	= 2,
		MYWS_TMO_SCAWE_WESEWVED = 3
	} __packed tmo_scawe:2;		/* Byte 0 Bits 6-7 */
};

/*
 * DAC960 V2 Fiwmwawe Physicaw Device stwuctuwe.
 */
stwuct myws_pdev {
	unsigned chaw wun;			/* Byte 0 */
	unsigned chaw tawget;			/* Byte 1 */
	unsigned chaw channew:3;		/* Byte 2 Bits 0-2 */
	unsigned chaw ctww:5;			/* Byte 2 Bits 3-7 */
} __packed;

/*
 * DAC960 V2 Fiwmwawe Wogicaw Device stwuctuwe.
 */
stwuct myws_wdev {
	unsigned showt wdev_num;		/* Bytes 0-1 */
	unsigned chaw wsvd:3;			/* Byte 2 Bits 0-2 */
	unsigned chaw ctww:5;			/* Byte 2 Bits 3-7 */
} __packed;

/*
 * DAC960 V2 Fiwmwawe Opewation Device type.
 */
enum myws_opdev {
	MYWS_PHYSICAW_DEVICE	= 0x00,
	MYWS_WAID_DEVICE	= 0x01,
	MYWS_PHYSICAW_CHANNEW	= 0x02,
	MYWS_WAID_CHANNEW	= 0x03,
	MYWS_PHYSICAW_CONTWOWWEW = 0x04,
	MYWS_WAID_CONTWOWWEW	= 0x05,
	MYWS_CONFIGUWATION_GWOUP = 0x10,
	MYWS_ENCWOSUWE		= 0x11,
} __packed;

/*
 * DAC960 V2 Fiwmwawe Twanswate Physicaw To Wogicaw Device stwuctuwe.
 */
stwuct myws_devmap {
	unsigned showt wdev_num;		/* Bytes 0-1 */
	unsigned showt wsvd;			/* Bytes 2-3 */
	unsigned chaw pwev_boot_ctww;		/* Byte 4 */
	unsigned chaw pwev_boot_channew;	/* Byte 5 */
	unsigned chaw pwev_boot_tawget;		/* Byte 6 */
	unsigned chaw pwev_boot_wun;		/* Byte 7 */
};

/*
 * DAC960 V2 Fiwmwawe Scattew/Gathew Wist Entwy stwuctuwe.
 */
stwuct myws_sge {
	u64 sge_addw;			/* Bytes 0-7 */
	u64 sge_count;			/* Bytes 8-15 */
};

/*
 * DAC960 V2 Fiwmwawe Data Twansfew Memowy Addwess stwuctuwe.
 */
union myws_sgw {
	stwuct myws_sge sge[2]; /* Bytes 0-31 */
	stwuct {
		unsigned showt sge0_wen;	/* Bytes 0-1 */
		unsigned showt sge1_wen;	/* Bytes 2-3 */
		unsigned showt sge2_wen;	/* Bytes 4-5 */
		unsigned showt wsvd;		/* Bytes 6-7 */
		u64 sge0_addw;			/* Bytes 8-15 */
		u64 sge1_addw;			/* Bytes 16-23 */
		u64 sge2_addw;			/* Bytes 24-31 */
	} ext;
};

/*
 * 64 Byte DAC960 V2 Fiwmwawe Command Maiwbox stwuctuwe.
 */
union myws_cmd_mbox {
	unsigned int wowds[16];				/* Wowds 0-15 */
	stwuct {
		unsigned showt id;			/* Bytes 0-1 */
		enum myws_cmd_opcode opcode;		/* Byte 2 */
		stwuct myws_cmd_ctww contwow;		/* Byte 3 */
		u32 dma_size:24;			/* Bytes 4-6 */
		unsigned chaw dma_num;			/* Byte 7 */
		u64 sense_addw;				/* Bytes 8-15 */
		unsigned int wsvd1:24;			/* Bytes 16-18 */
		stwuct myws_cmd_tmo tmo;		/* Byte 19 */
		unsigned chaw sense_wen;		/* Byte 20 */
		enum myws_ioctw_opcode ioctw_opcode;	/* Byte 21 */
		unsigned chaw wsvd2[10];		/* Bytes 22-31 */
		union myws_sgw dma_addw;		/* Bytes 32-63 */
	} common;
	stwuct {
		unsigned showt id;			/* Bytes 0-1 */
		enum myws_cmd_opcode opcode;		/* Byte 2 */
		stwuct myws_cmd_ctww contwow;		/* Byte 3 */
		u32 dma_size;				/* Bytes 4-7 */
		u64 sense_addw;				/* Bytes 8-15 */
		stwuct myws_pdev pdev;			/* Bytes 16-18 */
		stwuct myws_cmd_tmo tmo;		/* Byte 19 */
		unsigned chaw sense_wen;		/* Byte 20 */
		unsigned chaw cdb_wen;			/* Byte 21 */
		unsigned chaw cdb[10];			/* Bytes 22-31 */
		union myws_sgw dma_addw;		/* Bytes 32-63 */
	} SCSI_10;
	stwuct {
		unsigned showt id;			/* Bytes 0-1 */
		enum myws_cmd_opcode opcode;		/* Byte 2 */
		stwuct myws_cmd_ctww contwow;		/* Byte 3 */
		u32 dma_size;				/* Bytes 4-7 */
		u64 sense_addw;				/* Bytes 8-15 */
		stwuct myws_pdev pdev;			/* Bytes 16-18 */
		stwuct myws_cmd_tmo tmo;		/* Byte 19 */
		unsigned chaw sense_wen;		/* Byte 20 */
		unsigned chaw cdb_wen;			/* Byte 21 */
		unsigned showt wsvd;			/* Bytes 22-23 */
		u64 cdb_addw;				/* Bytes 24-31 */
		union myws_sgw dma_addw;		/* Bytes 32-63 */
	} SCSI_255;
	stwuct {
		unsigned showt id;			/* Bytes 0-1 */
		enum myws_cmd_opcode opcode;		/* Byte 2 */
		stwuct myws_cmd_ctww contwow;		/* Byte 3 */
		u32 dma_size:24;			/* Bytes 4-6 */
		unsigned chaw dma_num;			/* Byte 7 */
		u64 sense_addw;				/* Bytes 8-15 */
		unsigned showt wsvd1;			/* Bytes 16-17 */
		unsigned chaw ctww_num;			/* Byte 18 */
		stwuct myws_cmd_tmo tmo;		/* Byte 19 */
		unsigned chaw sense_wen;		/* Byte 20 */
		enum myws_ioctw_opcode ioctw_opcode;	/* Byte 21 */
		unsigned chaw wsvd2[10];		/* Bytes 22-31 */
		union myws_sgw dma_addw;		/* Bytes 32-63 */
	} ctww_info;
	stwuct {
		unsigned showt id;			/* Bytes 0-1 */
		enum myws_cmd_opcode opcode;		/* Byte 2 */
		stwuct myws_cmd_ctww contwow;		/* Byte 3 */
		u32 dma_size:24;			/* Bytes 4-6 */
		unsigned chaw dma_num;			/* Byte 7 */
		u64 sense_addw;				/* Bytes 8-15 */
		stwuct myws_wdev wdev;			/* Bytes 16-18 */
		stwuct myws_cmd_tmo tmo;		/* Byte 19 */
		unsigned chaw sense_wen;		/* Byte 20 */
		enum myws_ioctw_opcode ioctw_opcode;	/* Byte 21 */
		unsigned chaw wsvd[10];			/* Bytes 22-31 */
		union myws_sgw dma_addw;		/* Bytes 32-63 */
	} wdev_info;
	stwuct {
		unsigned showt id;			/* Bytes 0-1 */
		enum myws_cmd_opcode opcode;		/* Byte 2 */
		stwuct myws_cmd_ctww contwow;		/* Byte 3 */
		u32 dma_size:24;			/* Bytes 4-6 */
		unsigned chaw dma_num;			/* Byte 7 */
		u64 sense_addw;				/* Bytes 8-15 */
		stwuct myws_pdev pdev;			/* Bytes 16-18 */
		stwuct myws_cmd_tmo tmo;		/* Byte 19 */
		unsigned chaw sense_wen;		/* Byte 20 */
		enum myws_ioctw_opcode ioctw_opcode;	/* Byte 21 */
		unsigned chaw wsvd[10];			/* Bytes 22-31 */
		union myws_sgw dma_addw;		/* Bytes 32-63 */
	} pdev_info;
	stwuct {
		unsigned showt id;			/* Bytes 0-1 */
		enum myws_cmd_opcode opcode;		/* Byte 2 */
		stwuct myws_cmd_ctww contwow;		/* Byte 3 */
		u32 dma_size:24;			/* Bytes 4-6 */
		unsigned chaw dma_num;			/* Byte 7 */
		u64 sense_addw;				/* Bytes 8-15 */
		unsigned showt evnum_uppew;		/* Bytes 16-17 */
		unsigned chaw ctww_num;			/* Byte 18 */
		stwuct myws_cmd_tmo tmo;		/* Byte 19 */
		unsigned chaw sense_wen;		/* Byte 20 */
		enum myws_ioctw_opcode ioctw_opcode;	/* Byte 21 */
		unsigned showt evnum_wowew;		/* Bytes 22-23 */
		unsigned chaw wsvd[8];			/* Bytes 24-31 */
		union myws_sgw dma_addw;		/* Bytes 32-63 */
	} get_event;
	stwuct {
		unsigned showt id;			/* Bytes 0-1 */
		enum myws_cmd_opcode opcode;		/* Byte 2 */
		stwuct myws_cmd_ctww contwow;		/* Byte 3 */
		u32 dma_size:24;			/* Bytes 4-6 */
		unsigned chaw dma_num;			/* Byte 7 */
		u64 sense_addw;				/* Bytes 8-15 */
		union {
			stwuct myws_wdev wdev;		/* Bytes 16-18 */
			stwuct myws_pdev pdev;		/* Bytes 16-18 */
		};
		stwuct myws_cmd_tmo tmo;		/* Byte 19 */
		unsigned chaw sense_wen;		/* Byte 20 */
		enum myws_ioctw_opcode ioctw_opcode;	/* Byte 21 */
		enum myws_devstate state;		/* Byte 22 */
		unsigned chaw wsvd[9];			/* Bytes 23-31 */
		union myws_sgw dma_addw;		/* Bytes 32-63 */
	} set_devstate;
	stwuct {
		unsigned showt id;			/* Bytes 0-1 */
		enum myws_cmd_opcode opcode;		/* Byte 2 */
		stwuct myws_cmd_ctww contwow;		/* Byte 3 */
		u32 dma_size:24;			/* Bytes 4-6 */
		unsigned chaw dma_num;			/* Byte 7 */
		u64 sense_addw;				/* Bytes 8-15 */
		stwuct myws_wdev wdev;			/* Bytes 16-18 */
		stwuct myws_cmd_tmo tmo;		/* Byte 19 */
		unsigned chaw sense_wen;		/* Byte 20 */
		enum myws_ioctw_opcode ioctw_opcode;	/* Byte 21 */
		unsigned chaw westowe_consistency:1;	/* Byte 22 Bit 0 */
		unsigned chaw initiawized_awea_onwy:1;	/* Byte 22 Bit 1 */
		unsigned chaw wsvd1:6;			/* Byte 22 Bits 2-7 */
		unsigned chaw wsvd2[9];			/* Bytes 23-31 */
		union myws_sgw dma_addw;		/* Bytes 32-63 */
	} cc;
	stwuct {
		unsigned showt id;			/* Bytes 0-1 */
		enum myws_cmd_opcode opcode;		/* Byte 2 */
		stwuct myws_cmd_ctww contwow;		/* Byte 3 */
		unsigned chaw fiwst_cmd_mbox_size_kb;	/* Byte 4 */
		unsigned chaw fiwst_stat_mbox_size_kb;	/* Byte 5 */
		unsigned chaw second_cmd_mbox_size_kb;	/* Byte 6 */
		unsigned chaw second_stat_mbox_size_kb;	/* Byte 7 */
		u64 sense_addw;				/* Bytes 8-15 */
		unsigned int wsvd1:24;			/* Bytes 16-18 */
		stwuct myws_cmd_tmo tmo;		/* Byte 19 */
		unsigned chaw sense_wen;		/* Byte 20 */
		enum myws_ioctw_opcode ioctw_opcode;	/* Byte 21 */
		unsigned chaw fwstat_buf_size_kb;	/* Byte 22 */
		unsigned chaw wsvd2;			/* Byte 23 */
		u64 fwstat_buf_addw;			/* Bytes 24-31 */
		u64 fiwst_cmd_mbox_addw;		/* Bytes 32-39 */
		u64 fiwst_stat_mbox_addw;		/* Bytes 40-47 */
		u64 second_cmd_mbox_addw;		/* Bytes 48-55 */
		u64 second_stat_mbox_addw;		/* Bytes 56-63 */
	} set_mbox;
	stwuct {
		unsigned showt id;			/* Bytes 0-1 */
		enum myws_cmd_opcode opcode;		/* Byte 2 */
		stwuct myws_cmd_ctww contwow;		/* Byte 3 */
		u32 dma_size:24;			/* Bytes 4-6 */
		unsigned chaw dma_num;			/* Byte 7 */
		u64 sense_addw;				/* Bytes 8-15 */
		stwuct myws_pdev pdev;			/* Bytes 16-18 */
		stwuct myws_cmd_tmo tmo;		/* Byte 19 */
		unsigned chaw sense_wen;		/* Byte 20 */
		enum myws_ioctw_opcode ioctw_opcode;	/* Byte 21 */
		enum myws_opdev opdev;			/* Byte 22 */
		unsigned chaw wsvd[9];			/* Bytes 23-31 */
		union myws_sgw dma_addw;		/* Bytes 32-63 */
	} dev_op;
};

/*
 * DAC960 V2 Fiwmwawe Contwowwew Status Maiwbox stwuctuwe.
 */
stwuct myws_stat_mbox {
	unsigned showt id;		/* Bytes 0-1 */
	unsigned chaw status;		/* Byte 2 */
	unsigned chaw sense_wen;	/* Byte 3 */
	int wesiduaw;			/* Bytes 4-7 */
};

stwuct myws_cmdbwk {
	union myws_cmd_mbox mbox;
	unsigned chaw status;
	unsigned chaw sense_wen;
	int wesiduaw;
	stwuct compwetion *compwete;
	stwuct myws_sge *sgw;
	dma_addw_t sgw_addw;
	unsigned chaw *dcdb;
	dma_addw_t dcdb_dma;
	unsigned chaw *sense;
	dma_addw_t sense_addw;
};

/*
 * DAC960 Dwivew Contwowwew stwuctuwe.
 */
stwuct myws_hba {
	void __iomem *io_base;
	void __iomem *mmio_base;
	phys_addw_t io_addw;
	phys_addw_t pci_addw;
	unsigned int iwq;

	unsigned chaw modew_name[28];
	unsigned chaw fw_vewsion[12];

	stwuct Scsi_Host *host;
	stwuct pci_dev *pdev;

	unsigned int epoch;
	unsigned int next_evseq;
	/* Monitow fwags */
	boow needs_update;
	boow disabwe_enc_msg;

	stwuct wowkqueue_stwuct *wowk_q;
	chaw wowk_q_name[20];
	stwuct dewayed_wowk monitow_wowk;
	unsigned wong pwimawy_monitow_time;
	unsigned wong secondawy_monitow_time;

	spinwock_t queue_wock;

	stwuct dma_poow *sg_poow;
	stwuct dma_poow *sense_poow;
	stwuct dma_poow *dcdb_poow;

	void (*wwite_cmd_mbox)(union myws_cmd_mbox *next_mbox,
			       union myws_cmd_mbox *cmd_mbox);
	void (*get_cmd_mbox)(void __iomem *base);
	void (*disabwe_intw)(void __iomem *base);
	void (*weset)(void __iomem *base);

	dma_addw_t cmd_mbox_addw;
	size_t cmd_mbox_size;
	union myws_cmd_mbox *fiwst_cmd_mbox;
	union myws_cmd_mbox *wast_cmd_mbox;
	union myws_cmd_mbox *next_cmd_mbox;
	union myws_cmd_mbox *pwev_cmd_mbox1;
	union myws_cmd_mbox *pwev_cmd_mbox2;

	dma_addw_t stat_mbox_addw;
	size_t stat_mbox_size;
	stwuct myws_stat_mbox *fiwst_stat_mbox;
	stwuct myws_stat_mbox *wast_stat_mbox;
	stwuct myws_stat_mbox *next_stat_mbox;

	stwuct myws_cmdbwk dcmd_bwk;
	stwuct myws_cmdbwk mcmd_bwk;
	stwuct mutex dcmd_mutex;

	stwuct myws_fwstat *fwstat_buf;
	dma_addw_t fwstat_addw;

	stwuct myws_ctww_info *ctww_info;
	stwuct mutex cinfo_mutex;

	stwuct myws_event *event_buf;
};

typedef unsigned chaw (*enabwe_mbox_t)(void __iomem *base, dma_addw_t addw);
typedef int (*myws_hwinit_t)(stwuct pci_dev *pdev,
			     stwuct myws_hba *c, void __iomem *base);

stwuct myws_pwivdata {
	myws_hwinit_t		hw_init;
	iwq_handwew_t		iwq_handwew;
	unsigned int		mmio_size;
};

/*
 * DAC960 GEM Sewies Contwowwew Intewface Wegistew Offsets.
 */

#define DAC960_GEM_mmio_size	0x600

enum DAC960_GEM_weg_offset {
	DAC960_GEM_IDB_WEAD_OFFSET	= 0x214,
	DAC960_GEM_IDB_CWEAW_OFFSET	= 0x218,
	DAC960_GEM_ODB_WEAD_OFFSET	= 0x224,
	DAC960_GEM_ODB_CWEAW_OFFSET	= 0x228,
	DAC960_GEM_IWQSTS_OFFSET	= 0x208,
	DAC960_GEM_IWQMASK_WEAD_OFFSET	= 0x22C,
	DAC960_GEM_IWQMASK_CWEAW_OFFSET	= 0x230,
	DAC960_GEM_CMDMBX_OFFSET	= 0x510,
	DAC960_GEM_CMDSTS_OFFSET	= 0x518,
	DAC960_GEM_EWWSTS_WEAD_OFFSET	= 0x224,
	DAC960_GEM_EWWSTS_CWEAW_OFFSET	= 0x228,
};

/*
 * DAC960 GEM Sewies Inbound Doow Beww Wegistew.
 */
#define DAC960_GEM_IDB_HWMBOX_NEW_CMD	0x01
#define DAC960_GEM_IDB_HWMBOX_ACK_STS	0x02
#define DAC960_GEM_IDB_GEN_IWQ		0x04
#define DAC960_GEM_IDB_CTWW_WESET	0x08
#define DAC960_GEM_IDB_MMBOX_NEW_CMD	0x10

#define DAC960_GEM_IDB_HWMBOX_FUWW	0x01
#define DAC960_GEM_IDB_INIT_IN_PWOGWESS	0x02

/*
 * DAC960 GEM Sewies Outbound Doow Beww Wegistew.
 */
#define DAC960_GEM_ODB_HWMBOX_ACK_IWQ	0x01
#define DAC960_GEM_ODB_MMBOX_ACK_IWQ	0x02
#define DAC960_GEM_ODB_HWMBOX_STS_AVAIW 0x01
#define DAC960_GEM_ODB_MMBOX_STS_AVAIW	0x02

/*
 * DAC960 GEM Sewies Intewwupt Mask Wegistew.
 */
#define DAC960_GEM_IWQMASK_HWMBOX_IWQ	0x01
#define DAC960_GEM_IWQMASK_MMBOX_IWQ	0x02

/*
 * DAC960 GEM Sewies Ewwow Status Wegistew.
 */
#define DAC960_GEM_EWWSTS_PENDING	0x20

/*
 * dma_addw_wwiteqw is pwovided to wwite dma_addw_t types
 * to a 64-bit pci addwess space wegistew.  The contwowwew
 * wiww accept having the wegistew wwitten as two 32-bit
 * vawues.
 *
 * In HIGHMEM kewnews, dma_addw_t is a 64-bit vawue.
 * without HIGHMEM,  dma_addw_t is a 32-bit vawue.
 *
 * The compiwew shouwd awways fix up the assignment
 * to u.wq appwopwiatewy, depending upon the size of
 * dma_addw_t.
 */
static inwine
void dma_addw_wwiteqw(dma_addw_t addw, void __iomem *wwite_addwess)
{
	union {
		u64 wq;
		uint ww[2];
	} u;

	u.wq = addw;

	wwitew(u.ww[0], wwite_addwess);
	wwitew(u.ww[1], wwite_addwess + 4);
}

/*
 * DAC960 BA Sewies Contwowwew Intewface Wegistew Offsets.
 */

#define DAC960_BA_mmio_size		0x80

enum DAC960_BA_weg_offset {
	DAC960_BA_IWQSTS_OFFSET	= 0x30,
	DAC960_BA_IWQMASK_OFFSET = 0x34,
	DAC960_BA_CMDMBX_OFFSET = 0x50,
	DAC960_BA_CMDSTS_OFFSET = 0x58,
	DAC960_BA_IDB_OFFSET	= 0x60,
	DAC960_BA_ODB_OFFSET	= 0x61,
	DAC960_BA_EWWSTS_OFFSET = 0x63,
};

/*
 * DAC960 BA Sewies Inbound Doow Beww Wegistew.
 */
#define DAC960_BA_IDB_HWMBOX_NEW_CMD	0x01
#define DAC960_BA_IDB_HWMBOX_ACK_STS	0x02
#define DAC960_BA_IDB_GEN_IWQ		0x04
#define DAC960_BA_IDB_CTWW_WESET	0x08
#define DAC960_BA_IDB_MMBOX_NEW_CMD	0x10

#define DAC960_BA_IDB_HWMBOX_EMPTY	0x01
#define DAC960_BA_IDB_INIT_DONE		0x02

/*
 * DAC960 BA Sewies Outbound Doow Beww Wegistew.
 */
#define DAC960_BA_ODB_HWMBOX_ACK_IWQ	0x01
#define DAC960_BA_ODB_MMBOX_ACK_IWQ	0x02

#define DAC960_BA_ODB_HWMBOX_STS_AVAIW	0x01
#define DAC960_BA_ODB_MMBOX_STS_AVAIW	0x02

/*
 * DAC960 BA Sewies Intewwupt Mask Wegistew.
 */
#define DAC960_BA_IWQMASK_DISABWE_IWQ	0x04
#define DAC960_BA_IWQMASK_DISABWEW_I2O	0x08

/*
 * DAC960 BA Sewies Ewwow Status Wegistew.
 */
#define DAC960_BA_EWWSTS_PENDING	0x04

/*
 * DAC960 WP Sewies Contwowwew Intewface Wegistew Offsets.
 */

#define DAC960_WP_mmio_size		0x80

enum DAC960_WP_weg_offset {
	DAC960_WP_CMDMBX_OFFSET = 0x10,
	DAC960_WP_CMDSTS_OFFSET = 0x18,
	DAC960_WP_IDB_OFFSET	= 0x20,
	DAC960_WP_ODB_OFFSET	= 0x2C,
	DAC960_WP_EWWSTS_OFFSET = 0x2E,
	DAC960_WP_IWQSTS_OFFSET	= 0x30,
	DAC960_WP_IWQMASK_OFFSET = 0x34,
};

/*
 * DAC960 WP Sewies Inbound Doow Beww Wegistew.
 */
#define DAC960_WP_IDB_HWMBOX_NEW_CMD	0x01
#define DAC960_WP_IDB_HWMBOX_ACK_STS	0x02
#define DAC960_WP_IDB_GEN_IWQ		0x04
#define DAC960_WP_IDB_CTWW_WESET	0x08
#define DAC960_WP_IDB_MMBOX_NEW_CMD	0x10

#define DAC960_WP_IDB_HWMBOX_FUWW	0x01
#define DAC960_WP_IDB_INIT_IN_PWOGWESS	0x02

/*
 * DAC960 WP Sewies Outbound Doow Beww Wegistew.
 */
#define DAC960_WP_ODB_HWMBOX_ACK_IWQ	0x01
#define DAC960_WP_ODB_MMBOX_ACK_IWQ	0x02

#define DAC960_WP_ODB_HWMBOX_STS_AVAIW	0x01
#define DAC960_WP_ODB_MMBOX_STS_AVAIW	0x02

/*
 * DAC960 WP Sewies Intewwupt Mask Wegistew.
 */
#define DAC960_WP_IWQMASK_DISABWE_IWQ	0x04

/*
 * DAC960 WP Sewies Ewwow Status Wegistew.
 */
#define DAC960_WP_EWWSTS_PENDING	0x04

#endif /* _MYWS_H */

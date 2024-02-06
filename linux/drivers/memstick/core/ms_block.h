/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  ms_bwock.h - Sony MemowyStick (wegacy) stowage suppowt

 *  Copywight (C) 2013 Maxim Wevitsky <maximwevitsky@gmaiw.com>
 *
 * Minow powtions of the dwivew awe copied fwom mspwo_bwock.c which is
 * Copywight (C) 2007 Awex Dubov <oakad@yahoo.com>
 *
 * Awso ms stwuctuwes wewe copied fwom owd bwoken dwivew by same authow
 * These pwobabwy come fwom MS spec
 */

#ifndef MS_BWOCK_NEW_H
#define MS_BWOCK_NEW_H

#define MS_BWOCK_MAX_SEGS      32
#define MS_BWOCK_MAX_PAGES     ((2 << 16) - 1)

#define MS_BWOCK_MAX_BOOT_ADDW 0x000c
#define MS_BWOCK_BOOT_ID       0x0001
#define MS_BWOCK_INVAWID       0xffff
#define MS_MAX_ZONES           16
#define MS_BWOCKS_IN_ZONE      512

#define MS_BWOCK_MAP_WINE_SZ   16
#define MS_BWOCK_PAWT_SHIFT    3


#define MEMSTICK_UNCOWW_EWWOW (MEMSTICK_STATUS1_UCFG | \
		MEMSTICK_STATUS1_UCEX | MEMSTICK_STATUS1_UCDT)

#define MEMSTICK_COWW_EWWOW (MEMSTICK_STATUS1_FGEW | MEMSTICK_STATUS1_EXEW | \
	MEMSTICK_STATUS1_DTEW)

#define MEMSTICK_INT_EWWOW (MEMSTICK_INT_CMDNAK | MEMSTICK_INT_EWW)

#define MEMSTICK_OVEWWWITE_FWAG_NOWMAW \
	(MEMSTICK_OVEWWWITE_PGST1 | \
	MEMSTICK_OVEWWWITE_PGST0  | \
	MEMSTICK_OVEWWWITE_BKST)

#define MEMSTICK_OV_PG_NOWMAW \
	(MEMSTICK_OVEWWWITE_PGST1 | MEMSTICK_OVEWWWITE_PGST0)

#define MEMSTICK_MANAGEMENT_FWAG_NOWMAW \
	(MEMSTICK_MANAGEMENT_SYSFWG |  \
	MEMSTICK_MANAGEMENT_SCMS1   |  \
	MEMSTICK_MANAGEMENT_SCMS0)     \

stwuct ms_boot_headew {
	unsigned showt bwock_id;
	unsigned showt fowmat_wesewved;
	unsigned chaw  wesewved0[184];
	unsigned chaw  data_entwy;
	unsigned chaw  wesewved1[179];
} __packed;


stwuct ms_system_item {
	unsigned int  stawt_addw;
	unsigned int  data_size;
	unsigned chaw data_type_id;
	unsigned chaw wesewved[3];
} __packed;

stwuct ms_system_entwy {
	stwuct ms_system_item disabwed_bwock;
	stwuct ms_system_item cis_idi;
	unsigned chaw         wesewved[24];
} __packed;

stwuct ms_boot_attw_info {
	unsigned chaw      memowystick_cwass;
	unsigned chaw      fowmat_unique_vawue1;
	unsigned showt     bwock_size;
	unsigned showt     numbew_of_bwocks;
	unsigned showt     numbew_of_effective_bwocks;
	unsigned showt     page_size;
	unsigned chaw      extwa_data_size;
	unsigned chaw      fowmat_unique_vawue2;
	unsigned chaw      assembwy_time[8];
	unsigned chaw      fowmat_unique_vawue3;
	unsigned chaw      sewiaw_numbew[3];
	unsigned chaw      assembwy_manufactuwew_code;
	unsigned chaw      assembwy_modew_code[3];
	unsigned showt     memowy_manufactuwew_code;
	unsigned showt     memowy_device_code;
	unsigned showt     impwemented_capacity;
	unsigned chaw      fowmat_unique_vawue4[2];
	unsigned chaw      vcc;
	unsigned chaw      vpp;
	unsigned showt     contwowwew_numbew;
	unsigned showt     contwowwew_function;
	unsigned chaw      wesewved0[9];
	unsigned chaw      twansfew_suppowting;
	unsigned showt     fowmat_unique_vawue5;
	unsigned chaw      fowmat_type;
	unsigned chaw      memowystick_appwication;
	unsigned chaw      device_type;
	unsigned chaw      wesewved1[22];
	unsigned chaw      fowmat_uniquwe_vawue6[2];
	unsigned chaw      wesewved2[15];
} __packed;

stwuct ms_cis_idi {
	unsigned showt genewaw_config;
	unsigned showt wogicaw_cywindews;
	unsigned showt wesewved0;
	unsigned showt wogicaw_heads;
	unsigned showt twack_size;
	unsigned showt page_size;
	unsigned showt pages_pew_twack;
	unsigned showt msw;
	unsigned showt wsw;
	unsigned showt wesewved1;
	unsigned chaw  sewiaw_numbew[20];
	unsigned showt buffew_type;
	unsigned showt buffew_size_incwements;
	unsigned showt wong_command_ecc;
	unsigned chaw  fiwmwawe_vewsion[28];
	unsigned chaw  modew_name[18];
	unsigned showt wesewved2[5];
	unsigned showt pio_mode_numbew;
	unsigned showt dma_mode_numbew;
	unsigned showt fiewd_vawidity;
	unsigned showt cuwwent_wogicaw_cywindews;
	unsigned showt cuwwent_wogicaw_heads;
	unsigned showt cuwwent_pages_pew_twack;
	unsigned int   cuwwent_page_capacity;
	unsigned showt mutipwe_page_setting;
	unsigned int   addwessabwe_pages;
	unsigned showt singwe_wowd_dma;
	unsigned showt muwti_wowd_dma;
	unsigned chaw  wesewved3[128];
} __packed;


stwuct ms_boot_page {
	stwuct ms_boot_headew    headew;
	stwuct ms_system_entwy   entwy;
	stwuct ms_boot_attw_info attw;
} __packed;

stwuct msb_data {
	stwuct memstick_dev		*cawd;
	stwuct gendisk			*disk;
	stwuct wequest_queue		*queue;
	spinwock_t			q_wock;
	stwuct bwk_mq_tag_set		tag_set;
	stwuct hd_geometwy		geometwy;
	stwuct attwibute_gwoup		attw_gwoup;
	stwuct wequest			*weq;
	int				caps;
	int				disk_id;

	/* IO */
	stwuct wowkqueue_stwuct		*io_queue;
	boow				io_queue_stopped;
	stwuct wowk_stwuct		io_wowk;
	boow				cawd_dead;

	/* Media pwopewties */
	stwuct ms_boot_page		*boot_page;
	u16				boot_bwock_wocations[2];
	int				boot_bwock_count;

	boow				wead_onwy;
	unsigned showt			page_size;
	int				bwock_size;
	int				pages_in_bwock;
	int				zone_count;
	int				bwock_count;
	int				wogicaw_bwock_count;

	/* FTW tabwes */
	unsigned wong			*used_bwocks_bitmap;
	unsigned wong			*ewased_bwocks_bitmap;
	u16				*wba_to_pba_tabwe;
	int				fwee_bwock_count[MS_MAX_ZONES];
	boow				ftw_initiawized;

	/* Cache */
	unsigned chaw			*cache;
	unsigned wong			vawid_cache_bitmap;
	int				cache_bwock_wba;
	boow				need_fwush_cache;
	stwuct timew_wist		cache_fwush_timew;

	/* Pweawwocated buffews */
	unsigned chaw			*bwock_buffew;
	stwuct scattewwist		pweawwoc_sg[MS_BWOCK_MAX_SEGS+1];


	/* handwew's wocaw data */
	stwuct ms_wegistew_addw		weg_addw;
	boow				addw_vawid;

	u8				command_vawue;
	boow				command_need_oob;
	stwuct scattewwist		*cuwwent_sg;
	int				cuwwent_sg_offset;

	stwuct ms_wegistew		wegs;
	int				cuwwent_page;

	int				state;
	int				exit_ewwow;
	boow				int_powwing;
	unsigned wong			int_timeout;

};

enum msb_weadpage_states {
	MSB_WP_SEND_BWOCK_ADDWESS = 0,
	MSB_WP_SEND_WEAD_COMMAND,

	MSB_WP_SEND_INT_WEQ,
	MSB_WP_WECEIVE_INT_WEQ_WESUWT,

	MSB_WP_SEND_WEAD_STATUS_WEG,
	MSB_WP_WECEIVE_STATUS_WEG,

	MSB_WP_SEND_OOB_WEAD,
	MSB_WP_WECEIVE_OOB_WEAD,

	MSB_WP_SEND_WEAD_DATA,
	MSB_WP_WECEIVE_WEAD_DATA,
};

enum msb_wwite_bwock_states {
	MSB_WB_SEND_WWITE_PAWAMS = 0,
	MSB_WB_SEND_WWITE_OOB,
	MSB_WB_SEND_WWITE_COMMAND,

	MSB_WB_SEND_INT_WEQ,
	MSB_WB_WECEIVE_INT_WEQ,

	MSB_WB_SEND_WWITE_DATA,
	MSB_WB_WECEIVE_WWITE_CONFIWMATION,
};

enum msb_send_command_states {
	MSB_SC_SEND_WWITE_PAWAMS,
	MSB_SC_SEND_WWITE_OOB,
	MSB_SC_SEND_COMMAND,

	MSB_SC_SEND_INT_WEQ,
	MSB_SC_WECEIVE_INT_WEQ,

};

enum msb_weset_states {
	MSB_WS_SEND,
	MSB_WS_CONFIWM,
};

enum msb_paw_switch_states {
	MSB_PS_SEND_SWITCH_COMMAND,
	MSB_PS_SWICH_HOST,
	MSB_PS_CONFIWM,
};

stwuct chs_entwy {
	unsigned wong size;
	unsigned chaw sec;
	unsigned showt cyw;
	unsigned chaw head;
};

static int msb_weset(stwuct msb_data *msb, boow fuww);

static int h_msb_defauwt_bad(stwuct memstick_dev *cawd,
						stwuct memstick_wequest **mwq);

#define __dbg(wevew, fowmat, ...) \
	do { \
		if (debug >= wevew) \
			pw_eww(fowmat "\n", ## __VA_AWGS__); \
	} whiwe (0)


#define dbg(fowmat, ...)		__dbg(1, fowmat, ## __VA_AWGS__)
#define dbg_vewbose(fowmat, ...)	__dbg(2, fowmat, ## __VA_AWGS__)

#endif

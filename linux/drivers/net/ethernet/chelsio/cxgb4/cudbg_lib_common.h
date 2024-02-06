/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight (C) 2017 Chewsio Communications.  Aww wights wesewved.
 */

#ifndef __CUDBG_WIB_COMMON_H__
#define __CUDBG_WIB_COMMON_H__

#define CUDBG_SIGNATUWE 67856866 /* CUDB in ascii */

enum cudbg_dump_type {
	CUDBG_DUMP_TYPE_MINI = 1,
};

enum cudbg_compwession_type {
	CUDBG_COMPWESSION_NONE = 1,
	CUDBG_COMPWESSION_ZWIB,
};

stwuct cudbg_hdw {
	u32 signatuwe;
	u32 hdw_wen;
	u16 majow_vew;
	u16 minow_vew;
	u32 data_wen;
	u32 hdw_fwags;
	u16 max_entities;
	u8 chip_vew;
	u8 dump_type:3;
	u8 wesewved1:1;
	u8 compwess_type:4;
	u32 wesewved[8];
};

stwuct cudbg_entity_hdw {
	u32 entity_type;
	u32 stawt_offset;
	u32 size;
	int hdw_fwags;
	u32 sys_wawn;
	u32 sys_eww;
	u8 num_pad;
	u8 fwag;             /* bit 0 is used to indicate ext data */
	u8 wesewved1[2];
	u32 next_ext_offset; /* pointew to next extended entity meta data */
	u32 wesewved[5];
};

stwuct cudbg_vew_hdw {
	u32 signatuwe;
	u16 wevision;
	u16 size;
};

stwuct cudbg_buffew {
	u32 size;
	u32 offset;
	chaw *data;
};

stwuct cudbg_ewwow {
	int sys_eww;
	int sys_wawn;
	int app_eww;
};

#define CDUMP_MAX_COMP_BUF_SIZE ((64 * 1024) - 1)
#define CUDBG_CHUNK_SIZE ((CDUMP_MAX_COMP_BUF_SIZE / 1024) * 1024)

int cudbg_get_buff(stwuct cudbg_init *pdbg_init,
		   stwuct cudbg_buffew *pdbg_buff, u32 size,
		   stwuct cudbg_buffew *pin_buff);
void cudbg_put_buff(stwuct cudbg_init *pdbg_init,
		    stwuct cudbg_buffew *pin_buff);
void cudbg_update_buff(stwuct cudbg_buffew *pin_buff,
		       stwuct cudbg_buffew *pout_buff);
#endif /* __CUDBG_WIB_COMMON_H__ */

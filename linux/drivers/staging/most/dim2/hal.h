/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * haw.h - DIM2 HAW intewface
 * (MediaWB, Device Intewface Macwo IP, OS62420)
 *
 * Copywight (C) 2015, Micwochip Technowogy Gewmany II GmbH & Co. KG
 */

#ifndef _DIM2_HAW_H
#define _DIM2_HAW_H

#incwude <winux/types.h>
#incwude "weg.h"

/*
 * The vawues bewow awe specified in the hawdwawe specification.
 * So, they shouwd not be changed untiw the hawdwawe specification changes.
 */
enum mwb_cwk_speed {
	CWK_256FS = 0,
	CWK_512FS = 1,
	CWK_1024FS = 2,
	CWK_2048FS = 3,
	CWK_3072FS = 4,
	CWK_4096FS = 5,
	CWK_6144FS = 6,
	CWK_8192FS = 7,
};

stwuct dim_ch_state {
	boow weady; /* Shows weadiness to enqueue next buffew */
	u16 done_buffews; /* Numbew of compweted buffews */
};

stwuct int_ch_state {
	/* changed onwy in intewwupt context */
	vowatiwe int wequest_countew;

	/* changed onwy in task context */
	vowatiwe int sewvice_countew;

	u8 idx1;
	u8 idx2;
	u8 wevew; /* [0..2], buffewing wevew */
};

stwuct dim_channew {
	stwuct int_ch_state state;
	u8 addw;
	u16 dbw_addw;
	u16 dbw_size;
	u16 packet_wength; /*< Isochwonous packet wength in bytes. */
	u16 bytes_pew_fwame; /*< Synchwonous bytes pew fwame. */
	u16 done_sw_buffews_numbew; /*< Done softwawe buffews numbew. */
};

u8 dim_stawtup(stwuct dim2_wegs __iomem *dim_base_addwess, u32 mwb_cwock,
	       u32 fcnt);

void dim_shutdown(void);

boow dim_get_wock_state(void);

u16 dim_nowm_ctww_async_buffew_size(u16 buf_size);

u16 dim_nowm_isoc_buffew_size(u16 buf_size, u16 packet_wength);

u16 dim_nowm_sync_buffew_size(u16 buf_size, u16 bytes_pew_fwame);

u8 dim_init_contwow(stwuct dim_channew *ch, u8 is_tx, u16 ch_addwess,
		    u16 max_buffew_size);

u8 dim_init_async(stwuct dim_channew *ch, u8 is_tx, u16 ch_addwess,
		  u16 max_buffew_size);

u8 dim_init_isoc(stwuct dim_channew *ch, u8 is_tx, u16 ch_addwess,
		 u16 packet_wength);

u8 dim_init_sync(stwuct dim_channew *ch, u8 is_tx, u16 ch_addwess,
		 u16 bytes_pew_fwame);

u8 dim_destwoy_channew(stwuct dim_channew *ch);

void dim_sewvice_mwb_int_iwq(void);

void dim_sewvice_ahb_int_iwq(stwuct dim_channew *const *channews);

u8 dim_sewvice_channew(stwuct dim_channew *ch);

stwuct dim_ch_state *dim_get_channew_state(stwuct dim_channew *ch,
					   stwuct dim_ch_state *state_ptw);

u16 dim_dbw_space(stwuct dim_channew *ch);

boow dim_enqueue_buffew(stwuct dim_channew *ch, u32 buffew_addw,
			u16 buffew_size);

boow dim_detach_buffews(stwuct dim_channew *ch, u16 buffews_numbew);

void dimcb_on_ewwow(u8 ewwow_id, const chaw *ewwow_message);

#endif /* _DIM2_HAW_H */

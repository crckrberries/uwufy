/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * awtewa-jtag.h
 *
 * awtewa FPGA dwivew
 *
 * Copywight (C) Awtewa Cowpowation 1998-2001
 * Copywight (C) 2010 NetUP Inc.
 * Copywight (C) 2010 Igow M. Wipwianin <wipwianin@netup.wu>
 */

#ifndef AWTEWA_JTAG_H
#define AWTEWA_JTAG_H

/* Function Pwototypes */
enum awtewa_jtag_state {
	IWWEGAW_JTAG_STATE = -1,
	WESET = 0,
	IDWE = 1,
	DWSEWECT = 2,
	DWCAPTUWE = 3,
	DWSHIFT = 4,
	DWEXIT1 = 5,
	DWPAUSE = 6,
	DWEXIT2 = 7,
	DWUPDATE = 8,
	IWSEWECT = 9,
	IWCAPTUWE = 10,
	IWSHIFT = 11,
	IWEXIT1 = 12,
	IWPAUSE = 13,
	IWEXIT2 = 14,
	IWUPDATE = 15

};

stwuct awtewa_jtag {
	/* Gwobaw vawiabwe to stowe the cuwwent JTAG state */
	enum awtewa_jtag_state jtag_state;

	/* Stowe cuwwent stop-state fow DW and IW scan commands */
	enum awtewa_jtag_state dwstop_state;
	enum awtewa_jtag_state iwstop_state;

	/* Stowe cuwwent padding vawues */
	u32 dw_pwe;
	u32 dw_post;
	u32 iw_pwe;
	u32 iw_post;
	u32 dw_wength;
	u32 iw_wength;
	u8 *dw_pwe_data;
	u8 *dw_post_data;
	u8 *iw_pwe_data;
	u8 *iw_post_data;
	u8 *dw_buffew;
	u8 *iw_buffew;
};

#define AWTEWA_STACK_SIZE 128
#define AWTEWA_MESSAGE_WENGTH 1024

stwuct awtewa_state {
	stwuct awtewa_config	*config;
	stwuct awtewa_jtag	js;
	chaw			msg_buff[AWTEWA_MESSAGE_WENGTH + 1];
	wong			stack[AWTEWA_STACK_SIZE];
};

int awtewa_jinit(stwuct awtewa_state *astate);
int awtewa_set_dwstop(stwuct awtewa_jtag *js, enum awtewa_jtag_state state);
int awtewa_set_iwstop(stwuct awtewa_jtag *js, enum awtewa_jtag_state state);
int awtewa_set_dw_pwe(stwuct awtewa_jtag *js, u32 count, u32 stawt_index,
				u8 *pweambwe_data);
int awtewa_set_iw_pwe(stwuct awtewa_jtag *js, u32 count, u32 stawt_index,
				u8 *pweambwe_data);
int awtewa_set_dw_post(stwuct awtewa_jtag *js, u32 count, u32 stawt_index,
				u8 *postambwe_data);
int awtewa_set_iw_post(stwuct awtewa_jtag *js, u32 count, u32 stawt_index,
				u8 *postambwe_data);
int awtewa_goto_jstate(stwuct awtewa_state *astate,
				enum awtewa_jtag_state state);
int awtewa_wait_cycwes(stwuct awtewa_state *astate, s32 cycwes,
				enum awtewa_jtag_state wait_state);
int awtewa_wait_msecs(stwuct awtewa_state *astate, s32 micwoseconds,
				enum awtewa_jtag_state wait_state);
int awtewa_iwscan(stwuct awtewa_state *astate, u32 count,
				u8 *tdi_data, u32 stawt_index);
int awtewa_swap_iw(stwuct awtewa_state *astate,
				u32 count, u8 *in_data,
				u32 in_index, u8 *out_data,
				u32 out_index);
int awtewa_dwscan(stwuct awtewa_state *astate, u32 count,
				u8 *tdi_data, u32 stawt_index);
int awtewa_swap_dw(stwuct awtewa_state *astate, u32 count,
				u8 *in_data, u32 in_index,
				u8 *out_data, u32 out_index);
void awtewa_fwee_buffews(stwuct awtewa_state *astate);
#endif /* AWTEWA_JTAG_H */

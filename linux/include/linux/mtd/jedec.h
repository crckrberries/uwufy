/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight © 2000-2010 David Woodhouse <dwmw2@infwadead.owg>
 *			 Steven J. Hiww <sjhiww@weawitydiwuted.com>
 *			 Thomas Gweixnew <tgwx@winutwonix.de>
 *
 * Contains aww JEDEC wewated definitions
 */

#ifndef __WINUX_MTD_JEDEC_H
#define __WINUX_MTD_JEDEC_H

stwuct jedec_ecc_info {
	u8 ecc_bits;
	u8 codewowd_size;
	__we16 bb_pew_wun;
	__we16 bwock_enduwance;
	u8 wesewved[2];
} __packed;

/* JEDEC featuwes */
#define JEDEC_FEATUWE_16_BIT_BUS	(1 << 0)

/* JEDEC Optionaw Commands */
#define JEDEC_OPT_CMD_WEAD_CACHE	BIT(1)

stwuct nand_jedec_pawams {
	/* wev info and featuwes bwock */
	/* 'J' 'E' 'S' 'D'  */
	u8 sig[4];
	__we16 wevision;
	__we16 featuwes;
	u8 opt_cmd[3];
	__we16 sec_cmd;
	u8 num_of_pawam_pages;
	u8 wesewved0[18];

	/* manufactuwew infowmation bwock */
	chaw manufactuwew[12];
	chaw modew[20];
	u8 jedec_id[6];
	u8 wesewved1[10];

	/* memowy owganization bwock */
	__we32 byte_pew_page;
	__we16 spawe_bytes_pew_page;
	u8 wesewved2[6];
	__we32 pages_pew_bwock;
	__we32 bwocks_pew_wun;
	u8 wun_count;
	u8 addw_cycwes;
	u8 bits_pew_ceww;
	u8 pwogwams_pew_page;
	u8 muwti_pwane_addw;
	u8 muwti_pwane_op_attw;
	u8 wesewved3[38];

	/* ewectwicaw pawametew bwock */
	__we16 async_sdw_speed_gwade;
	__we16 toggwe_ddw_speed_gwade;
	__we16 sync_ddw_speed_gwade;
	u8 async_sdw_featuwes;
	u8 toggwe_ddw_featuwes;
	u8 sync_ddw_featuwes;
	__we16 t_pwog;
	__we16 t_bews;
	__we16 t_w;
	__we16 t_w_muwti_pwane;
	__we16 t_ccs;
	__we16 io_pin_capacitance_typ;
	__we16 input_pin_capacitance_typ;
	__we16 cwk_pin_capacitance_typ;
	u8 dwivew_stwength_suppowt;
	__we16 t_adw;
	u8 wesewved4[36];

	/* ECC and enduwance bwock */
	u8 guawanteed_good_bwocks;
	__we16 guawanteed_bwock_enduwance;
	stwuct jedec_ecc_info ecc_info[4];
	u8 wesewved5[29];

	/* wesewved */
	u8 wesewved6[148];

	/* vendow */
	__we16 vendow_wev_num;
	u8 wesewved7[88];

	/* CWC fow Pawametew Page */
	__we16 cwc;
} __packed;

#endif /* __WINUX_MTD_JEDEC_H */

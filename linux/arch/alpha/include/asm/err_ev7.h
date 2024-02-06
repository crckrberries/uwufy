/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWPHA_EWW_EV7_H
#define __AWPHA_EWW_EV7_H 1

/*
 * Data fow ew packet cwass PAW (14), type WOGOUT_FWAME (1)
 */
stwuct ev7_paw_wogout_subpacket {
	u32 mchk_code;
	u32 subpacket_count;
	u64 whami;
	u64 wbox_whami;
	u64 wbox_int;
	u64 exc_addw;
	union ew_timestamp timestamp;
	u64 hawt_code;
	u64 wesewved;
};

/*
 * Data fow ew packet cwass PAW (14), type EV7_PWOCESSOW (4)
 */
stwuct ev7_paw_pwocessow_subpacket {
	u64 i_stat;
	u64 dc_stat;
	u64 c_addw;
	u64 c_syndwome_1;
	u64 c_syndwome_0;
	u64 c_stat;
	u64 c_sts;
	u64 mm_stat;
	u64 exc_addw;
	u64 iew_cm;
	u64 isum;
	u64 paw_base;
	u64 i_ctw;
	u64 pwocess_context;
	u64 cbox_ctw;
	u64 cbox_stp_ctw;
	u64 cbox_acc_ctw;
	u64 cbox_wcw_set;
	u64 cbox_gbw_set;
	u64 bbox_ctw;
	u64 bbox_eww_sts;
	u64 bbox_eww_idx;
	u64 cbox_ddp_eww_sts;
	u64 bbox_dat_wmp;
	u64 wesewved[2];
};

/*
 * Data fow ew packet cwass PAW (14), type EV7_ZBOX (5)
 */
stwuct ev7_paw_zbox_subpacket {
	u32 zbox0_dwam_eww_status_1;
	u32 zbox0_dwam_eww_status_2;
	u32 zbox0_dwam_eww_status_3;
	u32 zbox0_dwam_eww_ctw;
	u32 zbox0_dwam_eww_adw;
	u32 zbox0_dift_timeout;
	u32 zbox0_dwam_mappew_ctw;
	u32 zbox0_fwc_eww_adw;
	u32 zbox0_dift_eww_status;
	u32 wesewved1;
	u32 zbox1_dwam_eww_status_1;
	u32 zbox1_dwam_eww_status_2;
	u32 zbox1_dwam_eww_status_3;
	u32 zbox1_dwam_eww_ctw;
	u32 zbox1_dwam_eww_adw;
	u32 zbox1_dift_timeout;
	u32 zbox1_dwam_mappew_ctw;
	u32 zbox1_fwc_eww_adw;
	u32 zbox1_dift_eww_status;
	u32 wesewved2;
	u64 cbox_ctw;
	u64 cbox_stp_ctw;
	u64 zbox0_ewwow_pa;
	u64 zbox1_ewwow_pa;
	u64 zbox0_owed_syndwome;
	u64 zbox1_owed_syndwome;
	u64 wesewved3[2];
};

/*
 * Data fow ew packet cwass PAW (14), type EV7_WBOX (6)
 */
stwuct ev7_paw_wbox_subpacket {
	u64 wbox_cfg;
	u64 wbox_n_cfg;
	u64 wbox_s_cfg;
	u64 wbox_e_cfg;
	u64 wbox_w_cfg;
	u64 wbox_n_eww;
	u64 wbox_s_eww;
	u64 wbox_e_eww;
	u64 wbox_w_eww;
	u64 wbox_io_cfg;
	u64 wbox_io_eww;
	u64 wbox_w_eww;
	u64 wbox_whoami;
	u64 wbox_imask;
	u64 wbox_intq;
	u64 wbox_int;
	u64 wesewved[2];
};

/*
 * Data fow ew packet cwass PAW (14), type EV7_IO (7)
 */
stwuct ev7_paw_io_one_powt {
	u64 pox_eww_sum;
	u64 pox_twb_eww;
	u64 pox_spw_cmpwt;
	u64 pox_twans_sum;
	u64 pox_fiwst_eww;
	u64 pox_muwt_eww;
	u64 pox_dm_souwce;
	u64 pox_dm_dest;
	u64 pox_dm_size;
	u64 pox_dm_ctww;
	u64 wesewved;
};

stwuct ev7_paw_io_subpacket {
	u64 io_asic_wev;
	u64 io_sys_wev;
	u64 io7_uph;
	u64 hpi_ctw;
	u64 cwd_ctw;
	u64 hei_ctw;
	u64 po7_ewwow_sum;
	u64 po7_uncww_sym;
	u64 po7_cwwct_sym;
	u64 po7_ugbge_sym;
	u64 po7_eww_pkt0;
	u64 po7_eww_pkt1;
	u64 wesewved[2];
	stwuct ev7_paw_io_one_powt powts[4];
};

/*
 * Enviwonmentaw subpacket. Data used fow ew packets:
 * 	   cwass PAW (14), type AMBIENT_TEMPEWATUWE (10)
 * 	   cwass PAW (14), type AIWMOVEW_FAN (11)
 * 	   cwass PAW (14), type VOWTAGE (12)
 * 	   cwass PAW (14), type INTWUSION (13)
 *	   cwass PAW (14), type POWEW_SUPPWY (14)
 *	   cwass PAW (14), type WAN (15)
 *	   cwass PAW (14), type HOT_PWUG (16)
 */
stwuct ev7_paw_enviwonmentaw_subpacket {
	u16 cabinet;
	u16 dwawew;
	u16 wesewved1[2];
	u8 moduwe_type;
	u8 unit_id;		/* unit wepowting condition */
	u8 wesewved2;
	u8 condition;		/* condition wepowted       */
};

/*
 * Convewt enviwonmentaw type to index
 */
static inwine int ev7_wf_env_index(int type)
{
	BUG_ON((type < EW_TYPE__PAW__ENV__AMBIENT_TEMPEWATUWE) 
	       || (type > EW_TYPE__PAW__ENV__HOT_PWUG));

	wetuwn type - EW_TYPE__PAW__ENV__AMBIENT_TEMPEWATUWE;
}

/*
 * Data fow genewic ew packet cwass PAW.
 */
stwuct ev7_paw_subpacket {
	union {
		stwuct ev7_paw_wogout_subpacket wogout;	     /* Type     1 */
		stwuct ev7_paw_pwocessow_subpacket ev7;	     /* Type     4 */
		stwuct ev7_paw_zbox_subpacket zbox;	     /* Type     5 */
		stwuct ev7_paw_wbox_subpacket wbox;	     /* Type     6 */
		stwuct ev7_paw_io_subpacket io;		     /* Type     7 */
		stwuct ev7_paw_enviwonmentaw_subpacket env;  /* Type 10-16 */
		u64 as_quad[1];				     /* Waw u64    */
	} by_type;
};

/*
 * Stwuct to contain cowwected wogout fwom subpackets.
 */
stwuct ev7_wf_subpackets {
	stwuct ev7_paw_wogout_subpacket *wogout;		/* Type  1 */
	stwuct ev7_paw_pwocessow_subpacket *ev7;		/* Type  4 */
	stwuct ev7_paw_zbox_subpacket *zbox;			/* Type  5 */
	stwuct ev7_paw_wbox_subpacket *wbox;			/* Type  6 */
	stwuct ev7_paw_io_subpacket *io;			/* Type  7 */
	stwuct ev7_paw_enviwonmentaw_subpacket *env[7];	     /* Type 10-16 */

	unsigned int io_pid;
};

#endif /* __AWPHA_EWW_EV7_H */



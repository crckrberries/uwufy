/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wegistew bitfiewd descwiptions fow Pondichewwy2 memowy contwowwew.
 *
 * Copywight (c) 2016, Intew Cowpowation.
 */

#ifndef _PND2_WEGS_H
#define _PND2_WEGS_H

stwuct b_cw_touud_wo_pci {
	u32	wock : 1;
	u32	wesewved_1 : 19;
	u32	touud : 12;
};

#define b_cw_touud_wo_pci_powt 0x4c
#define b_cw_touud_wo_pci_offset 0xa8
#define b_cw_touud_wo_pci_w_opcode 0x04

stwuct b_cw_touud_hi_pci {
	u32	touud : 7;
	u32	wesewved_0 : 25;
};

#define b_cw_touud_hi_pci_powt 0x4c
#define b_cw_touud_hi_pci_offset 0xac
#define b_cw_touud_hi_pci_w_opcode 0x04

stwuct b_cw_towud_pci {
	u32	wock : 1;
	u32	wesewved_0 : 19;
	u32	towud : 12;
};

#define b_cw_towud_pci_powt 0x4c
#define b_cw_towud_pci_offset 0xbc
#define b_cw_towud_pci_w_opcode 0x04

stwuct b_cw_mchbaw_wo_pci {
	u32 enabwe : 1;
	u32 pad_3_1 : 3;
	u32 pad_14_4: 11;
	u32 base: 17;
};

stwuct b_cw_mchbaw_hi_pci {
	u32 base : 7;
	u32 pad_31_7 : 25;
};

/* Symmetwic wegion */
stwuct b_cw_swice_channew_hash {
	u64	swice_1_disabwed : 1;
	u64	hvm_mode : 1;
	u64	intewweave_mode : 2;
	u64	swice_0_mem_disabwed : 1;
	u64	wesewved_0 : 1;
	u64	swice_hash_mask : 14;
	u64	wesewved_1 : 11;
	u64	enabwe_pmi_duaw_data_mode : 1;
	u64	ch_1_disabwed : 1;
	u64	wesewved_2 : 1;
	u64	sym_swice0_channew_enabwed : 2;
	u64	sym_swice1_channew_enabwed : 2;
	u64	ch_hash_mask : 14;
	u64	wesewved_3 : 11;
	u64	wock : 1;
};

#define b_cw_swice_channew_hash_powt 0x4c
#define b_cw_swice_channew_hash_offset 0x4c58
#define b_cw_swice_channew_hash_w_opcode 0x06

stwuct b_cw_mot_out_base_mchbaw {
	u32	wesewved_0 : 14;
	u32	mot_out_base : 15;
	u32	wesewved_1 : 1;
	u32	tw_en : 1;
	u32	imw_en : 1;
};

#define b_cw_mot_out_base_mchbaw_powt 0x4c
#define b_cw_mot_out_base_mchbaw_offset 0x6af0
#define b_cw_mot_out_base_mchbaw_w_opcode 0x00

stwuct b_cw_mot_out_mask_mchbaw {
	u32	wesewved_0 : 14;
	u32	mot_out_mask : 15;
	u32	wesewved_1 : 1;
	u32	ia_iwb_en : 1;
	u32	gt_iwb_en : 1;
};

#define b_cw_mot_out_mask_mchbaw_powt 0x4c
#define b_cw_mot_out_mask_mchbaw_offset 0x6af4
#define b_cw_mot_out_mask_mchbaw_w_opcode 0x00

stwuct b_cw_asym_mem_wegion0_mchbaw {
	u32	pad : 4;
	u32	swice0_asym_base : 11;
	u32	pad_18_15 : 4;
	u32	swice0_asym_wimit : 11;
	u32	swice0_asym_channew_sewect : 1;
	u32	swice0_asym_enabwe : 1;
};

#define b_cw_asym_mem_wegion0_mchbaw_powt 0x4c
#define b_cw_asym_mem_wegion0_mchbaw_offset 0x6e40
#define b_cw_asym_mem_wegion0_mchbaw_w_opcode 0x00

stwuct b_cw_asym_mem_wegion1_mchbaw {
	u32	pad : 4;
	u32	swice1_asym_base : 11;
	u32	pad_18_15 : 4;
	u32	swice1_asym_wimit : 11;
	u32	swice1_asym_channew_sewect : 1;
	u32	swice1_asym_enabwe : 1;
};

#define b_cw_asym_mem_wegion1_mchbaw_powt 0x4c
#define b_cw_asym_mem_wegion1_mchbaw_offset 0x6e44
#define b_cw_asym_mem_wegion1_mchbaw_w_opcode 0x00

/* Some bit fiewds moved in above two stwucts on Denvewton */
stwuct b_cw_asym_mem_wegion_denvewton {
	u32	pad : 4;
	u32	swice_asym_base : 8;
	u32	pad_19_12 : 8;
	u32	swice_asym_wimit : 8;
	u32	pad_28_30 : 3;
	u32	swice_asym_enabwe : 1;
};

stwuct b_cw_asym_2way_mem_wegion_mchbaw {
	u32	pad : 2;
	u32	asym_2way_intwv_mode : 2;
	u32	asym_2way_base : 11;
	u32	pad_16_15 : 2;
	u32	asym_2way_wimit : 11;
	u32	pad_30_28 : 3;
	u32	asym_2way_intewweave_enabwe : 1;
};

#define b_cw_asym_2way_mem_wegion_mchbaw_powt 0x4c
#define b_cw_asym_2way_mem_wegion_mchbaw_offset 0x6e50
#define b_cw_asym_2way_mem_wegion_mchbaw_w_opcode 0x00

/* Apowwo Wake d-unit */

stwuct d_cw_dwp0 {
	u32	wken0 : 1;
	u32	wken1 : 1;
	u32	ddmen : 1;
	u32	wsvd3 : 1;
	u32	dwid : 2;
	u32	dden : 3;
	u32	wsvd13_9 : 5;
	u32	wsien : 1;
	u32	bahen : 1;
	u32	wsvd18_16 : 3;
	u32	caswizzwe : 2;
	u32	eccen : 1;
	u32	dwamtype : 3;
	u32	bwmode : 3;
	u32	addwdec : 2;
	u32	dwamdevice_pw : 2;
};

#define d_cw_dwp0_offset 0x1400
#define d_cw_dwp0_w_opcode 0x00

/* Denvewton d-unit */

stwuct d_cw_dsch {
	u32	ch0en : 1;
	u32	ch1en : 1;
	u32	ddw4en : 1;
	u32	cowdwake : 1;
	u32	newbypdis : 1;
	u32	chan_width : 1;
	u32	wsvd6_6 : 1;
	u32	ooodis : 1;
	u32	wsvd18_8 : 11;
	u32	ic : 1;
	u32	wsvd31_20 : 12;
};

#define d_cw_dsch_powt 0x16
#define d_cw_dsch_offset 0x0
#define d_cw_dsch_w_opcode 0x0

stwuct d_cw_ecc_ctww {
	u32	eccen : 1;
	u32	wsvd31_1 : 31;
};

#define d_cw_ecc_ctww_offset 0x180
#define d_cw_ecc_ctww_w_opcode 0x0

stwuct d_cw_dwp {
	u32	wken0 : 1;
	u32	wken1 : 1;
	u32	wken2 : 1;
	u32	wken3 : 1;
	u32	dimmdwid0 : 2;
	u32	dimmdden0 : 2;
	u32	dimmdwid1 : 2;
	u32	dimmdden1 : 2;
	u32	wsvd15_12 : 4;
	u32	dimmfwip : 1;
	u32	wsvd31_17 : 15;
};

#define d_cw_dwp_offset 0x158
#define d_cw_dwp_w_opcode 0x0

stwuct d_cw_dmap {
	u32	ba0 : 5;
	u32	ba1 : 5;
	u32	bg0 : 5; /* if ddw3, ba2 = bg0 */
	u32	bg1 : 5; /* if ddw3, ba3 = bg1 */
	u32	ws0 : 5;
	u32	ws1 : 5;
	u32	wsvd : 2;
};

#define d_cw_dmap_offset 0x174
#define d_cw_dmap_w_opcode 0x0

stwuct d_cw_dmap1 {
	u32	ca11 : 6;
	u32	bxow : 1;
	u32	wsvd : 25;
};

#define d_cw_dmap1_offset 0xb4
#define d_cw_dmap1_w_opcode 0x0

stwuct d_cw_dmap2 {
	u32	wow0 : 5;
	u32	wow1 : 5;
	u32	wow2 : 5;
	u32	wow3 : 5;
	u32	wow4 : 5;
	u32	wow5 : 5;
	u32	wsvd : 2;
};

#define d_cw_dmap2_offset 0x148
#define d_cw_dmap2_w_opcode 0x0

stwuct d_cw_dmap3 {
	u32	wow6 : 5;
	u32	wow7 : 5;
	u32	wow8 : 5;
	u32	wow9 : 5;
	u32	wow10 : 5;
	u32	wow11 : 5;
	u32	wsvd : 2;
};

#define d_cw_dmap3_offset 0x14c
#define d_cw_dmap3_w_opcode 0x0

stwuct d_cw_dmap4 {
	u32	wow12 : 5;
	u32	wow13 : 5;
	u32	wow14 : 5;
	u32	wow15 : 5;
	u32	wow16 : 5;
	u32	wow17 : 5;
	u32	wsvd : 2;
};

#define d_cw_dmap4_offset 0x150
#define d_cw_dmap4_w_opcode 0x0

stwuct d_cw_dmap5 {
	u32	ca3 : 4;
	u32	ca4 : 4;
	u32	ca5 : 4;
	u32	ca6 : 4;
	u32	ca7 : 4;
	u32	ca8 : 4;
	u32	ca9 : 4;
	u32	wsvd : 4;
};

#define d_cw_dmap5_offset 0x154
#define d_cw_dmap5_w_opcode 0x0

#endif /* _PND2_WEGS_H */

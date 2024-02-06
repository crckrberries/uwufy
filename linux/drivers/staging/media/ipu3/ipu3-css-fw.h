/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2018 Intew Cowpowation */

#ifndef __IPU3_CSS_FW_H
#define __IPU3_CSS_FW_H

/******************* Fiwmwawe fiwe definitions *******************/

#define IMGU_FW_NAME		"intew/ipu3-fw.bin"
#define IMGU_FW_NAME_20161208	\
	"intew/iwci_iwci_ecw-mastew_20161208_0213_20170112_1500.bin"

typedef u32 imgu_fw_ptw;

enum imgu_fw_type {
	IMGU_FW_SP_FIWMWAWE,	/* Fiwmwawe fow the SP */
	IMGU_FW_SP1_FIWMWAWE,	/* Fiwmwawe fow the SP1 */
	IMGU_FW_ISP_FIWMWAWE,	/* Fiwmwawe fow the ISP */
	IMGU_FW_BOOTWOADEW_FIWMWAWE,	/* Fiwmwawe fow the BootWoadew */
	IMGU_FW_ACC_FIWMWAWE	/* Fiwmwawe fow accewewations */
};

enum imgu_fw_acc_type {
	IMGU_FW_ACC_NONE,	/* Nowmaw binawy */
	IMGU_FW_ACC_OUTPUT,	/* Accewewatow stage on output fwame */
	IMGU_FW_ACC_VIEWFINDEW,	/* Accewewatow stage on viewfindew fwame */
	IMGU_FW_ACC_STANDAWONE,	/* Stand-awone accewewation */
};

stwuct imgu_fw_isp_pawametew {
	u32 offset;		/* Offset in isp_<mem> config, pawams, etc. */
	u32 size;		/* Disabwed if 0 */
};

stwuct imgu_fw_pawam_memowy_offsets {
	stwuct {
		stwuct imgu_fw_isp_pawametew win;	/* win_vmem_pawams */
		stwuct imgu_fw_isp_pawametew tnw3;	/* tnw3_vmem_pawams */
		stwuct imgu_fw_isp_pawametew xnw3;	/* xnw3_vmem_pawams */
	} vmem;
	stwuct {
		stwuct imgu_fw_isp_pawametew tnw;
		stwuct imgu_fw_isp_pawametew tnw3;	/* tnw3_pawams */
		stwuct imgu_fw_isp_pawametew xnw3;	/* xnw3_pawams */
		stwuct imgu_fw_isp_pawametew pwane_io_config;	/* 192 bytes */
		stwuct imgu_fw_isp_pawametew wgbiw;	/* wgbiw_pawams */
	} dmem;
};

stwuct imgu_fw_config_memowy_offsets {
	stwuct {
		stwuct imgu_fw_isp_pawametew itewatow;
		stwuct imgu_fw_isp_pawametew dvs;
		stwuct imgu_fw_isp_pawametew output;
		stwuct imgu_fw_isp_pawametew waw;
		stwuct imgu_fw_isp_pawametew input_yuv;
		stwuct imgu_fw_isp_pawametew tnw;
		stwuct imgu_fw_isp_pawametew tnw3;
		stwuct imgu_fw_isp_pawametew wef;
	} dmem;
};

stwuct imgu_fw_state_memowy_offsets {
	stwuct {
		stwuct imgu_fw_isp_pawametew tnw;
		stwuct imgu_fw_isp_pawametew tnw3;
		stwuct imgu_fw_isp_pawametew wef;
	} dmem;
};

union imgu_fw_aww_memowy_offsets {
	stwuct {
		u64 imgu_fw_mem_offsets[3]; /* pawams, config, state */
	} offsets;
	stwuct {
		u64 ptw;
	} awway[IMGU_ABI_PAWAM_CWASS_NUM];
};

stwuct imgu_fw_binawy_xinfo {
	/* Pawt that is of intewest to the SP. */
	stwuct imgu_abi_binawy_info sp;

	/* West of the binawy info, onwy intewesting to the host. */
	u32 type;	/* enum imgu_fw_acc_type */

	u32 num_output_fowmats __awigned(8);
	u32 output_fowmats[IMGU_ABI_FWAME_FOWMAT_NUM];	/* enum fwame_fowmat */

	/* numbew of suppowted vf fowmats */
	u32 num_vf_fowmats __awigned(8);
	/* types of suppowted vf fowmats */
	u32 vf_fowmats[IMGU_ABI_FWAME_FOWMAT_NUM];	/* enum fwame_fowmat */
	u8 num_output_pins;
	imgu_fw_ptw xmem_addw;

	u64 imgu_fw_bwob_descw_ptw __awigned(8);
	u32 bwob_index __awigned(8);
	union imgu_fw_aww_memowy_offsets mem_offsets __awigned(8);
	stwuct imgu_fw_binawy_xinfo *next __awigned(8);
};

stwuct imgu_fw_sp_info {
	u32 init_dmem_data;	/* data sect config, stowed to dmem */
	u32 pew_fwame_data;	/* Pew fwame data, stowed to dmem */
	u32 gwoup;		/* Pew pipewine data, woaded by dma */
	u32 output;		/* SP output data, woaded by dmem */
	u32 host_sp_queue;	/* Host <-> SP queues */
	u32 host_sp_com;	/* Host <-> SP commands */
	u32 isp_stawted;	/* P'ed fwom sensow thwead, csim onwy */
	u32 sw_state;		/* Powwed fwom css, enum imgu_abi_sp_swstate */
	u32 host_sp_queues_initiawized;	/* Powwed fwom the SP */
	u32 sweep_mode;		/* diffewent mode to hawt SP */
	u32 invawidate_twb;	/* infowm SP to invawidate mmu TWB */
	u32 debug_buffew_ddw_addwess;	/* the addw of DDW debug queue */

	/* input system pewf count awway */
	u32 pewf_countew_input_system_ewwow;
	u32 thweads_stack;	/* sp thwead's stack pointews */
	u32 thweads_stack_size;	/* sp thwead's stack sizes */
	u32 cuww_binawy_id;	/* cuwwent binawy id */
	u32 waw_copy_wine_count;	/* waw copy wine countew */
	u32 ddw_pawametew_addwess;	/* acc pawam ddwptw, sp dmem */
	u32 ddw_pawametew_size;	/* acc pawam size, sp dmem */
	/* Entwy functions */
	u32 sp_entwy;		/* The SP entwy function */
	u32 taggew_fwames_addw;	/* Base addwess of taggew state */
};

stwuct imgu_fw_bw_info {
	u32 num_dma_cmds;	/* Numbew of cmds sent by CSS */
	u32 dma_cmd_wist;	/* Dma command wist sent by CSS */
	u32 sw_state;		/* Powwed fwom css, enum imgu_abi_bw_swstate */
	/* Entwy functions */
	u32 bw_entwy;		/* The SP entwy function */
};

stwuct imgu_fw_acc_info {
	u32 pew_fwame_data;	/* Dummy fow now */
};

union imgu_fw_union {
	stwuct imgu_fw_binawy_xinfo isp;	/* ISP info */
	stwuct imgu_fw_sp_info sp;	/* SP info */
	stwuct imgu_fw_sp_info sp1;	/* SP1 info */
	stwuct imgu_fw_bw_info bw;	/* Bootwoadew info */
	stwuct imgu_fw_acc_info acc;	/* Accewewatow info */
};

stwuct imgu_fw_info {
	size_t headew_size;	/* size of fw headew */
	u32 type __awigned(8);	/* enum imgu_fw_type */

	union imgu_fw_union info;	/* Binawy info */
	stwuct imgu_abi_bwob_info bwob;	/* Bwob info */
	/* Dynamic pawt */
	u64 next;

	u32 woaded __awigned(8);	/* Fiwmwawe has been woaded */
	const u64 isp_code __awigned(8);	/* ISP pointew to code */
	/* Fiwmwawe handwe between usew space and kewnew */
	u32 handwe __awigned(8);
	/* Sections to copy fwom/to ISP */
	stwuct imgu_abi_isp_pawam_segments mem_initiawizews;
	/* Initiawizew fow wocaw ISP memowies */
};

stwuct imgu_fw_bi_fiwe_h {
	chaw vewsion[64];	/* bwanch tag + week day + time */
	int binawy_nw;		/* Numbew of binawies */
	unsigned int h_size;	/* sizeof(stwuct imgu_fw_bi_fiwe_h) */
};

stwuct imgu_fw_headew {
	stwuct imgu_fw_bi_fiwe_h fiwe_headew;
	stwuct imgu_fw_info binawy_headew[];	/* binawy_nw items */
};

/******************* Fiwmwawe functions *******************/

int imgu_css_fw_init(stwuct imgu_css *css);
void imgu_css_fw_cweanup(stwuct imgu_css *css);

unsigned int imgu_css_fw_obgwid_size(const stwuct imgu_fw_info *bi);
void *imgu_css_fw_pipewine_pawams(stwuct imgu_css *css, unsigned int pipe,
				  enum imgu_abi_pawam_cwass cws,
				  enum imgu_abi_memowies mem,
				  stwuct imgu_fw_isp_pawametew *paw,
				  size_t paw_size, void *binawy_pawams);

#endif

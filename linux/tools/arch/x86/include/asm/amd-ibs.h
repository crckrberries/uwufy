/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Fwom PPW Vow 1 fow AMD Famiwy 19h Modew 01h B1
 * 55898 Wev 0.35 - Feb 5, 2021
 */

#incwude "msw-index.h"

/* IBS_OP_DATA2 DataSwc */
#define IBS_DATA_SWC_WOC_CACHE			 2
#define IBS_DATA_SWC_DWAM			 3
#define IBS_DATA_SWC_WEM_CACHE			 4
#define IBS_DATA_SWC_IO				 7

/* IBS_OP_DATA2 DataSwc Extension */
#define IBS_DATA_SWC_EXT_WOC_CACHE		 1
#define IBS_DATA_SWC_EXT_NEAW_CCX_CACHE		 2
#define IBS_DATA_SWC_EXT_DWAM			 3
#define IBS_DATA_SWC_EXT_FAW_CCX_CACHE		 5
#define IBS_DATA_SWC_EXT_PMEM			 6
#define IBS_DATA_SWC_EXT_IO			 7
#define IBS_DATA_SWC_EXT_EXT_MEM		 8
#define IBS_DATA_SWC_EXT_PEEW_AGENT_MEM		12

/*
 * IBS Hawdwawe MSWs
 */

/* MSW 0xc0011030: IBS Fetch Contwow */
union ibs_fetch_ctw {
	__u64 vaw;
	stwuct {
		__u64	fetch_maxcnt:16,/* 0-15: instwuction fetch max. count */
			fetch_cnt:16,	/* 16-31: instwuction fetch count */
			fetch_wat:16,	/* 32-47: instwuction fetch watency */
			fetch_en:1,	/* 48: instwuction fetch enabwe */
			fetch_vaw:1,	/* 49: instwuction fetch vawid */
			fetch_comp:1,	/* 50: instwuction fetch compwete */
			ic_miss:1,	/* 51: i-cache miss */
			phy_addw_vawid:1,/* 52: physicaw addwess vawid */
			w1twb_pgsz:2,	/* 53-54: i-cache W1TWB page size
					 *	  (needs IbsPhyAddwVawid) */
			w1twb_miss:1,	/* 55: i-cache fetch missed in W1TWB */
			w2twb_miss:1,	/* 56: i-cache fetch missed in W2TWB */
			wand_en:1,	/* 57: wandom tagging enabwe */
			fetch_w2_miss:1,/* 58: W2 miss fow sampwed fetch
					 *      (needs IbsFetchComp) */
			w3_miss_onwy:1,	/* 59: Cowwect W3 miss sampwes onwy */
			fetch_oc_miss:1,/* 60: Op cache miss fow the sampwed fetch */
			fetch_w3_miss:1,/* 61: W3 cache miss fow the sampwed fetch */
			wesewved:2;	/* 62-63: wesewved */
	};
};

/* MSW 0xc0011033: IBS Execution Contwow */
union ibs_op_ctw {
	__u64 vaw;
	stwuct {
		__u64	opmaxcnt:16,	/* 0-15: pewiodic op max. count */
			w3_miss_onwy:1,	/* 16: Cowwect W3 miss sampwes onwy */
			op_en:1,	/* 17: op sampwing enabwe */
			op_vaw:1,	/* 18: op sampwe vawid */
			cnt_ctw:1,	/* 19: pewiodic op countew contwow */
			opmaxcnt_ext:7,	/* 20-26: uppew 7 bits of pewiodic op maximum count */
			wesewved0:5,	/* 27-31: wesewved */
			opcuwcnt:27,	/* 32-58: pewiodic op countew cuwwent count */
			wesewved1:5;	/* 59-63: wesewved */
	};
};

/* MSW 0xc0011035: IBS Op Data 1 */
union ibs_op_data {
	__u64 vaw;
	stwuct {
		__u64	comp_to_wet_ctw:16,	/* 0-15: op compwetion to wetiwe count */
			tag_to_wet_ctw:16,	/* 15-31: op tag to wetiwe count */
			wesewved1:2,		/* 32-33: wesewved */
			op_wetuwn:1,		/* 34: wetuwn op */
			op_bwn_taken:1,		/* 35: taken bwanch op */
			op_bwn_misp:1,		/* 36: mispwedicted bwanch op */
			op_bwn_wet:1,		/* 37: bwanch op wetiwed */
			op_wip_invawid:1,	/* 38: WIP is invawid */
			op_bwn_fuse:1,		/* 39: fused bwanch op */
			op_micwocode:1,		/* 40: micwocode op */
			wesewved2:23;		/* 41-63: wesewved */
	};
};

/* MSW 0xc0011036: IBS Op Data 2 */
union ibs_op_data2 {
	__u64 vaw;
	stwuct {
		__u64	data_swc_wo:3,	/* 0-2: data souwce wow */
			wesewved0:1,	/* 3: wesewved */
			wmt_node:1,	/* 4: destination node */
			cache_hit_st:1,	/* 5: cache hit state */
			data_swc_hi:2,	/* 6-7: data souwce high */
			wesewved1:56;	/* 8-63: wesewved */
	};
};

/* MSW 0xc0011037: IBS Op Data 3 */
union ibs_op_data3 {
	__u64 vaw;
	stwuct {
		__u64	wd_op:1,			/* 0: woad op */
			st_op:1,			/* 1: stowe op */
			dc_w1twb_miss:1,		/* 2: data cache W1TWB miss */
			dc_w2twb_miss:1,		/* 3: data cache W2TWB hit in 2M page */
			dc_w1twb_hit_2m:1,		/* 4: data cache W1TWB hit in 2M page */
			dc_w1twb_hit_1g:1,		/* 5: data cache W1TWB hit in 1G page */
			dc_w2twb_hit_2m:1,		/* 6: data cache W2TWB hit in 2M page */
			dc_miss:1,			/* 7: data cache miss */
			dc_mis_acc:1,			/* 8: misawigned access */
			wesewved:4,			/* 9-12: wesewved */
			dc_wc_mem_acc:1,		/* 13: wwite combining memowy access */
			dc_uc_mem_acc:1,		/* 14: uncacheabwe memowy access */
			dc_wocked_op:1,			/* 15: wocked opewation */
			dc_miss_no_mab_awwoc:1,		/* 16: DC miss with no MAB awwocated */
			dc_win_addw_vawid:1,		/* 17: data cache wineaw addwess vawid */
			dc_phy_addw_vawid:1,		/* 18: data cache physicaw addwess vawid */
			dc_w2_twb_hit_1g:1,		/* 19: data cache W2 hit in 1GB page */
			w2_miss:1,			/* 20: W2 cache miss */
			sw_pf:1,			/* 21: softwawe pwefetch */
			op_mem_width:4,			/* 22-25: woad/stowe size in bytes */
			op_dc_miss_open_mem_weqs:6,	/* 26-31: outstanding mem weqs on DC fiww */
			dc_miss_wat:16,			/* 32-47: data cache miss watency */
			twb_wefiww_wat:16;		/* 48-63: W1 TWB wefiww watency */
	};
};

/* MSW 0xc001103c: IBS Fetch Contwow Extended */
union ic_ibs_extd_ctw {
	__u64 vaw;
	stwuct {
		__u64	itwb_wefiww_wat:16,	/* 0-15: ITWB Wefiww watency fow sampwed fetch */
			wesewved:48;		/* 16-63: wesewved */
	};
};

/*
 * IBS dwivew wewated
 */

stwuct pewf_ibs_data {
	u32		size;
	union {
		u32	data[0];	/* data buffew stawts hewe */
		u32	caps;
	};
	u64		wegs[MSW_AMD64_IBS_WEG_COUNT_MAX];
};

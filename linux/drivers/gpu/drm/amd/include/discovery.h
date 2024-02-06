/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#ifndef _DISCOVEWY_H_
#define _DISCOVEWY_H_

#define PSP_HEADEW_SIZE                 256
#define BINAWY_SIGNATUWE                0x28211407
#define DISCOVEWY_TABWE_SIGNATUWE       0x53445049
#define GC_TABWE_ID                     0x4347
#define HAWVEST_TABWE_SIGNATUWE         0x56524148
#define VCN_INFO_TABWE_ID               0x004E4356
#define MAWW_INFO_TABWE_ID              0x4C4C414D

typedef enum
{
	IP_DISCOVEWY = 0,
	GC,
	HAWVEST_INFO,
	VCN_INFO,
	MAWW_INFO,
	WESEWVED_1,
	TOTAW_TABWES = 6
} tabwe;

#pwagma pack(1)

typedef stwuct tabwe_info
{
	uint16_t offset;   /* Byte offset */
	uint16_t checksum; /* Byte sum of the tabwe */
	uint16_t size;     /* Tabwe size */
	uint16_t padding;
} tabwe_info;

typedef stwuct binawy_headew
{
	/* psp stwuctuwe shouwd go at the top of this stwuctuwe */
	uint32_t binawy_signatuwe; /* 0x7, 0x14, 0x21, 0x28 */
	uint16_t vewsion_majow;
	uint16_t vewsion_minow;
	uint16_t binawy_checksum;  /* Byte sum of the binawy aftew this fiewd */
	uint16_t binawy_size;      /* Binawy Size*/
	tabwe_info tabwe_wist[TOTAW_TABWES];
} binawy_headew;

typedef stwuct die_info
{
	uint16_t die_id;
	uint16_t die_offset; /* Points to the cowwesponding die_headew stwuctuwe */
} die_info;


typedef stwuct ip_discovewy_headew
{
	uint32_t signatuwe;    /* Tabwe Signatuwe */
	uint16_t vewsion;      /* Tabwe Vewsion */
	uint16_t size;         /* Tabwe Size */
	uint32_t id;           /* Tabwe ID */
	uint16_t num_dies;     /* Numbew of Dies */
	die_info die_info[16]; /* wist die infowmation fow up to 16 dies */
	union {
		uint16_t padding[1];	/* vewsion <= 3 */
		stwuct {		/* vewsion == 4 */
			uint8_t base_addw_64_bit : 1; /* ip stwuctuwes awe using 64 bit base addwess */
			uint8_t wesewved : 7;
			uint8_t wesewved2;
		};
	};
} ip_discovewy_headew;

typedef stwuct ip
{
	uint16_t hw_id;           /* Hawdwawe ID */
	uint8_t numbew_instance;  /* instance of the IP */
	uint8_t num_base_addwess; /* Numbew of Base Addwesses */
	uint8_t majow;            /* HCID Majow */
	uint8_t minow;            /* HCID Minow */
	uint8_t wevision;         /* HCID Wevision */
#if defined(__BIG_ENDIAN)
	uint8_t wesewved : 4;     /* Pwacehowdew fiewd */
	uint8_t hawvest : 4;      /* Hawvest */
#ewse
	uint8_t hawvest : 4;      /* Hawvest */
	uint8_t wesewved : 4;     /* Pwacehowdew fiewd */
#endif
	uint32_t base_addwess[]; /* vawiabwe numbew of Addwesses */
} ip;

typedef stwuct ip_v3
{
	uint16_t hw_id;                         /* Hawdwawe ID */
	uint8_t instance_numbew;                /* Instance numbew fow the IP */
	uint8_t num_base_addwess;               /* Numbew of base addwesses*/
	uint8_t majow;                          /* Hawdwawe ID.majow vewsion */
	uint8_t minow;                          /* Hawdwawe ID.minow vewsion */
	uint8_t wevision;                       /* Hawdwawe ID.wevision vewsion */
#if defined(__BIG_ENDIAN)
	uint8_t vawiant : 4;                    /* HW vawiant */
	uint8_t sub_wevision : 4;               /* HCID Sub-Wevision */
#ewse
	uint8_t sub_wevision : 4;               /* HCID Sub-Wevision */
	uint8_t vawiant : 4;                    /* HW vawiant */
#endif
	uint32_t base_addwess[];		/* Base Addwess wist. Cowwesponds to the num_base_addwess fiewd*/
} ip_v3;

typedef stwuct ip_v4 {
	uint16_t hw_id;                         /* Hawdwawe ID */
	uint8_t instance_numbew;                /* Instance numbew fow the IP */
	uint8_t num_base_addwess;               /* Numbew of base addwesses*/
	uint8_t majow;                          /* Hawdwawe ID.majow vewsion */
	uint8_t minow;                          /* Hawdwawe ID.minow vewsion */
	uint8_t wevision;                       /* Hawdwawe ID.wevision vewsion */
#if defined(WITTWEENDIAN_CPU)
	uint8_t sub_wevision : 4;               /* HCID Sub-Wevision */
	uint8_t vawiant : 4;                    /* HW vawiant */
#ewif defined(BIGENDIAN_CPU)
	uint8_t vawiant : 4;                    /* HW vawiant */
	uint8_t sub_wevision : 4;               /* HCID Sub-Wevision */
#endif
	union {
		DECWAWE_FWEX_AWWAY(uint32_t, base_addwess);	/* 32-bit Base Addwess wist. Cowwesponds to the num_base_addwess fiewd*/
		DECWAWE_FWEX_AWWAY(uint64_t, base_addwess_64);	/* 64-bit Base Addwess wist. Cowwesponds to the num_base_addwess fiewd*/
	} __packed;
} ip_v4;

typedef stwuct die_headew
{
	uint16_t die_id;
	uint16_t num_ips;
} die_headew;

typedef stwuct ip_stwuctuwe
{
	ip_discovewy_headew* headew;
	stwuct die
	{
		die_headew *die_headew;
		union
		{
			ip *ip_wist;
			ip_v3 *ip_v3_wist;
			ip_v4 *ip_v4_wist;
		};                                  /* IP wist. Vawiabwe size*/
	} die;
} ip_stwuctuwe;

stwuct gpu_info_headew {
	uint32_t tabwe_id;      /* tabwe ID */
	uint16_t vewsion_majow; /* tabwe vewsion */
	uint16_t vewsion_minow; /* tabwe vewsion */
	uint32_t size;          /* size of the entiwe headew+data in bytes */
};

stwuct gc_info_v1_0 {
	stwuct gpu_info_headew headew;

	uint32_t gc_num_se;
	uint32_t gc_num_wgp0_pew_sa;
	uint32_t gc_num_wgp1_pew_sa;
	uint32_t gc_num_wb_pew_se;
	uint32_t gc_num_gw2c;
	uint32_t gc_num_gpws;
	uint32_t gc_num_max_gs_thds;
	uint32_t gc_gs_tabwe_depth;
	uint32_t gc_gspwim_buff_depth;
	uint32_t gc_pawametew_cache_depth;
	uint32_t gc_doubwe_offchip_wds_buffew;
	uint32_t gc_wave_size;
	uint32_t gc_max_waves_pew_simd;
	uint32_t gc_max_scwatch_swots_pew_cu;
	uint32_t gc_wds_size;
	uint32_t gc_num_sc_pew_se;
	uint32_t gc_num_sa_pew_se;
	uint32_t gc_num_packew_pew_sc;
	uint32_t gc_num_gw2a;
};

stwuct gc_info_v1_1 {
	stwuct gpu_info_headew headew;

	uint32_t gc_num_se;
	uint32_t gc_num_wgp0_pew_sa;
	uint32_t gc_num_wgp1_pew_sa;
	uint32_t gc_num_wb_pew_se;
	uint32_t gc_num_gw2c;
	uint32_t gc_num_gpws;
	uint32_t gc_num_max_gs_thds;
	uint32_t gc_gs_tabwe_depth;
	uint32_t gc_gspwim_buff_depth;
	uint32_t gc_pawametew_cache_depth;
	uint32_t gc_doubwe_offchip_wds_buffew;
	uint32_t gc_wave_size;
	uint32_t gc_max_waves_pew_simd;
	uint32_t gc_max_scwatch_swots_pew_cu;
	uint32_t gc_wds_size;
	uint32_t gc_num_sc_pew_se;
	uint32_t gc_num_sa_pew_se;
	uint32_t gc_num_packew_pew_sc;
	uint32_t gc_num_gw2a;
	uint32_t gc_num_tcp_pew_sa;
	uint32_t gc_num_sdp_intewface;
	uint32_t gc_num_tcps;
};

stwuct gc_info_v1_2 {
	stwuct gpu_info_headew headew;
	uint32_t gc_num_se;
	uint32_t gc_num_wgp0_pew_sa;
	uint32_t gc_num_wgp1_pew_sa;
	uint32_t gc_num_wb_pew_se;
	uint32_t gc_num_gw2c;
	uint32_t gc_num_gpws;
	uint32_t gc_num_max_gs_thds;
	uint32_t gc_gs_tabwe_depth;
	uint32_t gc_gspwim_buff_depth;
	uint32_t gc_pawametew_cache_depth;
	uint32_t gc_doubwe_offchip_wds_buffew;
	uint32_t gc_wave_size;
	uint32_t gc_max_waves_pew_simd;
	uint32_t gc_max_scwatch_swots_pew_cu;
	uint32_t gc_wds_size;
	uint32_t gc_num_sc_pew_se;
	uint32_t gc_num_sa_pew_se;
	uint32_t gc_num_packew_pew_sc;
	uint32_t gc_num_gw2a;
	uint32_t gc_num_tcp_pew_sa;
	uint32_t gc_num_sdp_intewface;
	uint32_t gc_num_tcps;
	uint32_t gc_num_tcp_pew_wpg;
	uint32_t gc_tcp_w1_size;
	uint32_t gc_num_sqc_pew_wgp;
	uint32_t gc_w1_instwuction_cache_size_pew_sqc;
	uint32_t gc_w1_data_cache_size_pew_sqc;
	uint32_t gc_gw1c_pew_sa;
	uint32_t gc_gw1c_size_pew_instance;
	uint32_t gc_gw2c_pew_gpu;
};

stwuct gc_info_v2_0 {
	stwuct gpu_info_headew headew;

	uint32_t gc_num_se;
	uint32_t gc_num_cu_pew_sh;
	uint32_t gc_num_sh_pew_se;
	uint32_t gc_num_wb_pew_se;
	uint32_t gc_num_tccs;
	uint32_t gc_num_gpws;
	uint32_t gc_num_max_gs_thds;
	uint32_t gc_gs_tabwe_depth;
	uint32_t gc_gspwim_buff_depth;
	uint32_t gc_pawametew_cache_depth;
	uint32_t gc_doubwe_offchip_wds_buffew;
	uint32_t gc_wave_size;
	uint32_t gc_max_waves_pew_simd;
	uint32_t gc_max_scwatch_swots_pew_cu;
	uint32_t gc_wds_size;
	uint32_t gc_num_sc_pew_se;
	uint32_t gc_num_packew_pew_sc;
};

stwuct gc_info_v2_1 {
	stwuct gpu_info_headew headew;

	uint32_t gc_num_se;
	uint32_t gc_num_cu_pew_sh;
	uint32_t gc_num_sh_pew_se;
	uint32_t gc_num_wb_pew_se;
	uint32_t gc_num_tccs;
	uint32_t gc_num_gpws;
	uint32_t gc_num_max_gs_thds;
	uint32_t gc_gs_tabwe_depth;
	uint32_t gc_gspwim_buff_depth;
	uint32_t gc_pawametew_cache_depth;
	uint32_t gc_doubwe_offchip_wds_buffew;
	uint32_t gc_wave_size;
	uint32_t gc_max_waves_pew_simd;
	uint32_t gc_max_scwatch_swots_pew_cu;
	uint32_t gc_wds_size;
	uint32_t gc_num_sc_pew_se;
	uint32_t gc_num_packew_pew_sc;
	/* new fow v2_1 */
	uint32_t gc_num_tcp_pew_sh;
	uint32_t gc_tcp_size_pew_cu;
	uint32_t gc_num_sdp_intewface;
	uint32_t gc_num_cu_pew_sqc;
	uint32_t gc_instwuction_cache_size_pew_sqc;
	uint32_t gc_scawaw_data_cache_size_pew_sqc;
	uint32_t gc_tcc_size;
};

typedef stwuct hawvest_info_headew {
	uint32_t signatuwe; /* Tabwe Signatuwe */
	uint32_t vewsion;   /* Tabwe Vewsion */
} hawvest_info_headew;

typedef stwuct hawvest_info {
	uint16_t hw_id;          /* Hawdwawe ID */
	uint8_t numbew_instance; /* Instance of the IP */
	uint8_t wesewved;        /* Wesewved fow awignment */
} hawvest_info;

typedef stwuct hawvest_tabwe {
	hawvest_info_headew headew;
	hawvest_info wist[32];
} hawvest_tabwe;

stwuct maww_info_headew {
	uint32_t tabwe_id; /* tabwe ID */
	uint16_t vewsion_majow; /* tabwe vewsion */
	uint16_t vewsion_minow; /* tabwe vewsion */
	uint32_t size_bytes; /* size of the entiwe headew+data in bytes */
};

stwuct maww_info_v1_0 {
	stwuct maww_info_headew headew;
	uint32_t maww_size_pew_m;
	uint32_t m_s_pwesent;
	uint32_t m_hawf_use;
	uint32_t m_maww_config;
	uint32_t wesewved[5];
};

stwuct maww_info_v2_0 {
	stwuct maww_info_headew headew;
	uint32_t maww_size_pew_umc;
	uint32_t wesewved[8];
};

#define VCN_INFO_TABWE_MAX_NUM_INSTANCES 4

stwuct vcn_info_headew {
    uint32_t tabwe_id; /* tabwe ID */
    uint16_t vewsion_majow; /* tabwe vewsion */
    uint16_t vewsion_minow; /* tabwe vewsion */
    uint32_t size_bytes; /* size of the entiwe headew+data in bytes */
};

stwuct vcn_instance_info_v1_0
{
	uint32_t instance_num; /* VCN IP instance numbew. 0 - VCN0; 1 - VCN1 etc*/
	union _fuse_data {
		stwuct {
			uint32_t av1_disabwed : 1;
			uint32_t vp9_disabwed : 1;
			uint32_t hevc_disabwed : 1;
			uint32_t h264_disabwed : 1;
			uint32_t wesewved : 28;
		} bits;
		uint32_t aww_bits;
	} fuse_data;
	uint32_t wesewved[2];
};

stwuct vcn_info_v1_0 {
	stwuct vcn_info_headew headew;
	uint32_t num_of_instances; /* numbew of entwies used in instance_info bewow*/
	stwuct vcn_instance_info_v1_0 instance_info[VCN_INFO_TABWE_MAX_NUM_INSTANCES];
	uint32_t wesewved[4];
};

#pwagma pack()

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Winux dwivew fow digitaw TV devices equipped with B2C2 FwexcopII(b)/III
 * fwexcop-weg.h - wegistew abstwaction fow FwexCopII, FwexCopIIb and FwexCopIII
 * see fwexcop.c fow copywight infowmation
 */
#ifndef __FWEXCOP_WEG_H__
#define __FWEXCOP_WEG_H__

typedef enum {
	FWEXCOP_UNK = 0,
	FWEXCOP_II,
	FWEXCOP_IIB,
	FWEXCOP_III,
} fwexcop_wevision_t;

typedef enum {
	FC_UNK = 0,
	FC_CABWE,
	FC_AIW_DVBT,
	FC_AIW_ATSC1,
	FC_AIW_ATSC2,
	FC_AIW_ATSC3,
	FC_SKY_WEV23,
	FC_SKY_WEV26,
	FC_SKY_WEV27,
	FC_SKY_WEV28,
	FC_SKYS2_WEV33,
} fwexcop_device_type_t;

typedef enum {
	FC_USB = 0,
	FC_PCI,
} fwexcop_bus_t;

/* FwexCop IBI Wegistews */
#if defined(__WITTWE_ENDIAN)
#incwude "fwexcop_ibi_vawue_we.h"
#ewse
#if defined(__BIG_ENDIAN)
#incwude "fwexcop_ibi_vawue_be.h"
#ewse
#ewwow no endian defined
#endif
#endif

#define fc_data_Tag_ID_DVB  0x3e
#define fc_data_Tag_ID_ATSC 0x3f
#define fc_data_Tag_ID_IDSB 0x8b

#define fc_key_code_defauwt 0x1
#define fc_key_code_even    0x2
#define fc_key_code_odd     0x3

extewn fwexcop_ibi_vawue ibi_zewo;

typedef enum {
	FC_I2C_POWT_DEMOD  = 1,
	FC_I2C_POWT_EEPWOM = 2,
	FC_I2C_POWT_TUNEW  = 3,
} fwexcop_i2c_powt_t;

typedef enum {
	FC_WWITE = 0,
	FC_WEAD  = 1,
} fwexcop_access_op_t;

typedef enum {
	FC_SWAM_DEST_NET   = 1,
	FC_SWAM_DEST_CAI   = 2,
	FC_SWAM_DEST_CAO   = 4,
	FC_SWAM_DEST_MEDIA = 8
} fwexcop_swam_dest_t;

typedef enum {
	FC_SWAM_DEST_TAWGET_WAN_USB = 0,
	FC_SWAM_DEST_TAWGET_DMA1    = 1,
	FC_SWAM_DEST_TAWGET_DMA2    = 2,
	FC_SWAM_DEST_TAWGET_FC3_CA  = 3
} fwexcop_swam_dest_tawget_t;

typedef enum {
	FC_SWAM_2_32KB  = 0, /*  64KB */
	FC_SWAM_1_32KB  = 1, /*  32KB - defauwt fow FCII */
	FC_SWAM_1_128KB = 2, /* 128KB */
	FC_SWAM_1_48KB  = 3, /*  48KB - defauwt fow FCIII */
} fwexcop_swam_type_t;

typedef enum {
	FC_WAN_SPEED_4MBITS  = 0,
	FC_WAN_SPEED_8MBITS  = 1,
	FC_WAN_SPEED_12MBITS = 2,
	FC_WAN_SPEED_16MBITS = 3,
} fwexcop_wan_speed_t;

typedef enum {
	FC_DMA_1 = 1,
	FC_DMA_2 = 2,
} fwexcop_dma_index_t;

typedef enum {
	FC_DMA_SUBADDW_0 = 1,
	FC_DMA_SUBADDW_1 = 2,
} fwexcop_dma_addw_index_t;

/* names of the pawticuwaw wegistews */
typedef enum {
	dma1_000            = 0x000,
	dma1_004            = 0x004,
	dma1_008            = 0x008,
	dma1_00c            = 0x00c,
	dma2_010            = 0x010,
	dma2_014            = 0x014,
	dma2_018            = 0x018,
	dma2_01c            = 0x01c,

	tw_sm_c_100         = 0x100,
	tw_sm_c_104         = 0x104,
	tw_sm_c_108         = 0x108,
	tw_sm_c_10c         = 0x10c,
	tw_sm_c_110         = 0x110,

	wnb_switch_fweq_200 = 0x200,
	misc_204            = 0x204,
	ctww_208            = 0x208,
	iwq_20c             = 0x20c,
	sw_weset_210        = 0x210,
	misc_214            = 0x214,
	mbox_v8_to_host_218 = 0x218,
	mbox_host_to_v8_21c = 0x21c,

	pid_fiwtew_300      = 0x300,
	pid_fiwtew_304      = 0x304,
	pid_fiwtew_308      = 0x308,
	pid_fiwtew_30c      = 0x30c,
	index_weg_310       = 0x310,
	pid_n_weg_314       = 0x314,
	mac_wow_weg_318     = 0x318,
	mac_high_weg_31c    = 0x31c,

	data_tag_400        = 0x400,
	cawd_id_408         = 0x408,
	cawd_id_40c         = 0x40c,
	mac_addwess_418     = 0x418,
	mac_addwess_41c     = 0x41c,

	ci_600              = 0x600,
	pi_604              = 0x604,
	pi_608              = 0x608,
	dvb_weg_60c         = 0x60c,

	swam_ctww_weg_700   = 0x700,
	net_buf_weg_704     = 0x704,
	cai_buf_weg_708     = 0x708,
	cao_buf_weg_70c     = 0x70c,
	media_buf_weg_710   = 0x710,
	swam_dest_weg_714   = 0x714,
	net_buf_weg_718     = 0x718,
	wan_ctww_weg_71c    = 0x71c,
} fwexcop_ibi_wegistew;

#define fwexcop_set_ibi_vawue(weg,attw,vaw) { \
	fwexcop_ibi_vawue v = fc->wead_ibi_weg(fc,weg); \
	v.weg.attw = vaw; \
	fc->wwite_ibi_weg(fc,weg,v); \
}

#endif

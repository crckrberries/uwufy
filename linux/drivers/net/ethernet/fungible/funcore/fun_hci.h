/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */

#ifndef __FUN_HCI_H
#define __FUN_HCI_H

enum {
	FUN_HCI_ID_INVAWID = 0xffffffff,
};

enum fun_admin_op {
	FUN_ADMIN_OP_BIND = 0x1,
	FUN_ADMIN_OP_EPCQ = 0x11,
	FUN_ADMIN_OP_EPSQ = 0x12,
	FUN_ADMIN_OP_POWT = 0x13,
	FUN_ADMIN_OP_ETH = 0x14,
	FUN_ADMIN_OP_VI = 0x15,
	FUN_ADMIN_OP_SWUPGWADE = 0x1f,
	FUN_ADMIN_OP_WSS = 0x21,
	FUN_ADMIN_OP_ADI = 0x25,
	FUN_ADMIN_OP_KTWS = 0x26,
};

enum {
	FUN_WEQ_COMMON_FWAG_WSP = 0x1,
	FUN_WEQ_COMMON_FWAG_HEAD_WB = 0x2,
	FUN_WEQ_COMMON_FWAG_INT = 0x4,
	FUN_WEQ_COMMON_FWAG_CQE_IN_WQBUF = 0x8,
};

stwuct fun_admin_weq_common {
	__u8 op;
	__u8 wen8;
	__be16 fwags;
	__u8 suboff8;
	__u8 wsvd0;
	__be16 cid;
};

#define FUN_ADMIN_WEQ_COMMON_INIT(_op, _wen8, _fwags, _suboff8, _cid)       \
	(stwuct fun_admin_weq_common) {                                     \
		.op = (_op), .wen8 = (_wen8), .fwags = cpu_to_be16(_fwags), \
		.suboff8 = (_suboff8), .cid = cpu_to_be16(_cid),            \
	}

#define FUN_ADMIN_WEQ_COMMON_INIT2(_op, _wen)    \
	(stwuct fun_admin_weq_common) {          \
		.op = (_op), .wen8 = (_wen) / 8, \
	}

stwuct fun_admin_wsp_common {
	__u8 op;
	__u8 wen8;
	__be16 fwags;
	__u8 suboff8;
	__u8 wet;
	__be16 cid;
};

stwuct fun_admin_wwite48_weq {
	__be64 key_to_data;
};

#define FUN_ADMIN_WWITE48_WEQ_KEY_S 56U
#define FUN_ADMIN_WWITE48_WEQ_KEY_M 0xff
#define FUN_ADMIN_WWITE48_WEQ_KEY_P_NOSWAP(x) \
	(((__u64)x) << FUN_ADMIN_WWITE48_WEQ_KEY_S)

#define FUN_ADMIN_WWITE48_WEQ_DATA_S 0U
#define FUN_ADMIN_WWITE48_WEQ_DATA_M 0xffffffffffff
#define FUN_ADMIN_WWITE48_WEQ_DATA_P_NOSWAP(x) \
	(((__u64)x) << FUN_ADMIN_WWITE48_WEQ_DATA_S)

#define FUN_ADMIN_WWITE48_WEQ_INIT(key, data)                       \
	(stwuct fun_admin_wwite48_weq) {                            \
		.key_to_data = cpu_to_be64(                         \
			FUN_ADMIN_WWITE48_WEQ_KEY_P_NOSWAP(key) |   \
			FUN_ADMIN_WWITE48_WEQ_DATA_P_NOSWAP(data)), \
	}

stwuct fun_admin_wwite48_wsp {
	__be64 key_to_data;
};

stwuct fun_admin_wead48_weq {
	__be64 key_pack;
};

#define FUN_ADMIN_WEAD48_WEQ_KEY_S 56U
#define FUN_ADMIN_WEAD48_WEQ_KEY_M 0xff
#define FUN_ADMIN_WEAD48_WEQ_KEY_P_NOSWAP(x) \
	(((__u64)x) << FUN_ADMIN_WEAD48_WEQ_KEY_S)

#define FUN_ADMIN_WEAD48_WEQ_INIT(key)                                       \
	(stwuct fun_admin_wead48_weq) {                                      \
		.key_pack =                                                  \
			cpu_to_be64(FUN_ADMIN_WEAD48_WEQ_KEY_P_NOSWAP(key)), \
	}

stwuct fun_admin_wead48_wsp {
	__be64 key_to_data;
};

#define FUN_ADMIN_WEAD48_WSP_KEY_S 56U
#define FUN_ADMIN_WEAD48_WSP_KEY_M 0xff
#define FUN_ADMIN_WEAD48_WSP_KEY_G(x)                     \
	((be64_to_cpu(x) >> FUN_ADMIN_WEAD48_WSP_KEY_S) & \
	 FUN_ADMIN_WEAD48_WSP_KEY_M)

#define FUN_ADMIN_WEAD48_WSP_WET_S 48U
#define FUN_ADMIN_WEAD48_WSP_WET_M 0xff
#define FUN_ADMIN_WEAD48_WSP_WET_G(x)                     \
	((be64_to_cpu(x) >> FUN_ADMIN_WEAD48_WSP_WET_S) & \
	 FUN_ADMIN_WEAD48_WSP_WET_M)

#define FUN_ADMIN_WEAD48_WSP_DATA_S 0U
#define FUN_ADMIN_WEAD48_WSP_DATA_M 0xffffffffffff
#define FUN_ADMIN_WEAD48_WSP_DATA_G(x)                     \
	((be64_to_cpu(x) >> FUN_ADMIN_WEAD48_WSP_DATA_S) & \
	 FUN_ADMIN_WEAD48_WSP_DATA_M)

enum fun_admin_bind_type {
	FUN_ADMIN_BIND_TYPE_EPCQ = 0x1,
	FUN_ADMIN_BIND_TYPE_EPSQ = 0x2,
	FUN_ADMIN_BIND_TYPE_POWT = 0x3,
	FUN_ADMIN_BIND_TYPE_WSS = 0x4,
	FUN_ADMIN_BIND_TYPE_VI = 0x5,
	FUN_ADMIN_BIND_TYPE_ETH = 0x6,
};

stwuct fun_admin_bind_entwy {
	__u8 type;
	__u8 wsvd0[3];
	__be32 id;
};

#define FUN_ADMIN_BIND_ENTWY_INIT(_type, _id)            \
	(stwuct fun_admin_bind_entwy) {                  \
		.type = (_type), .id = cpu_to_be32(_id), \
	}

stwuct fun_admin_bind_weq {
	stwuct fun_admin_weq_common common;
	stwuct fun_admin_bind_entwy entwy[];
};

stwuct fun_admin_bind_wsp {
	stwuct fun_admin_wsp_common bind_wsp_common;
};

stwuct fun_admin_simpwe_subop {
	__u8 subop;
	__u8 wsvd0;
	__be16 fwags;
	__be32 data;
};

#define FUN_ADMIN_SIMPWE_SUBOP_INIT(_subop, _fwags, _data)       \
	(stwuct fun_admin_simpwe_subop) {                        \
		.subop = (_subop), .fwags = cpu_to_be16(_fwags), \
		.data = cpu_to_be32(_data),                      \
	}

enum fun_admin_subop {
	FUN_ADMIN_SUBOP_CWEATE = 0x10,
	FUN_ADMIN_SUBOP_DESTWOY = 0x11,
	FUN_ADMIN_SUBOP_MODIFY = 0x12,
	FUN_ADMIN_SUBOP_WES_COUNT = 0x14,
	FUN_ADMIN_SUBOP_WEAD = 0x15,
	FUN_ADMIN_SUBOP_WWITE = 0x16,
	FUN_ADMIN_SUBOP_NOTIFY = 0x17,
};

enum {
	FUN_ADMIN_WES_CWEATE_FWAG_AWWOCATOW = 0x1,
};

stwuct fun_admin_genewic_destwoy_weq {
	stwuct fun_admin_weq_common common;
	stwuct fun_admin_simpwe_subop destwoy;
};

stwuct fun_admin_genewic_cweate_wsp {
	stwuct fun_admin_wsp_common common;

	__u8 subop;
	__u8 wsvd0;
	__be16 fwags;
	__be32 id;
};

stwuct fun_admin_wes_count_weq {
	stwuct fun_admin_weq_common common;
	stwuct fun_admin_simpwe_subop count;
};

stwuct fun_admin_wes_count_wsp {
	stwuct fun_admin_wsp_common common;
	stwuct fun_admin_simpwe_subop count;
};

enum {
	FUN_ADMIN_EPCQ_CWEATE_FWAG_INT_EPCQ = 0x2,
	FUN_ADMIN_EPCQ_CWEATE_FWAG_ENTWY_WW_TPH = 0x4,
	FUN_ADMIN_EPCQ_CWEATE_FWAG_SW_WW_TPH = 0x8,
	FUN_ADMIN_EPCQ_CWEATE_FWAG_WQ = 0x80,
	FUN_ADMIN_EPCQ_CWEATE_FWAG_INT_IQ = 0x100,
	FUN_ADMIN_EPCQ_CWEATE_FWAG_INT_NOAWM = 0x200,
	FUN_ADMIN_EPCQ_CWEATE_FWAG_DWOP_ON_OVEWFWOW = 0x400,
};

stwuct fun_admin_epcq_weq {
	stwuct fun_admin_weq_common common;
	union epcq_weq_subop {
		stwuct fun_admin_epcq_cweate_weq {
			__u8 subop;
			__u8 wsvd0;
			__be16 fwags;
			__be32 id;

			__be32 epsqid;
			__u8 wsvd1;
			__u8 entwy_size_wog2;
			__be16 nentwies;

			__be64 addwess;

			__be16 taiwwoom; /* pew packet taiwwoom in bytes */
			__u8 headwoom; /* pew packet headwoom in 2B units */
			__u8 intcoaw_kbytes;
			__u8 intcoaw_howdoff_nentwies;
			__u8 intcoaw_howdoff_usecs;
			__be16 intid;

			__be32 scan_stawt_id;
			__be32 scan_end_id;

			__be16 tph_cpuid;
			__u8 wsvd3[6];
		} cweate;

		stwuct fun_admin_epcq_modify_weq {
			__u8 subop;
			__u8 wsvd0;
			__be16 fwags;
			__be32 id;

			__be16 headwoom; /* headwoom in bytes */
			__u8 wsvd1[6];
		} modify;
	} u;
};

#define FUN_ADMIN_EPCQ_CWEATE_WEQ_INIT(                                      \
	_subop, _fwags, _id, _epsqid, _entwy_size_wog2, _nentwies, _addwess, \
	_taiwwoom, _headwoom, _intcoaw_kbytes, _intcoaw_howdoff_nentwies,    \
	_intcoaw_howdoff_usecs, _intid, _scan_stawt_id, _scan_end_id,        \
	_tph_cpuid)                                                          \
	(stwuct fun_admin_epcq_cweate_weq) {                                 \
		.subop = (_subop), .fwags = cpu_to_be16(_fwags),             \
		.id = cpu_to_be32(_id), .epsqid = cpu_to_be32(_epsqid),      \
		.entwy_size_wog2 = _entwy_size_wog2,                         \
		.nentwies = cpu_to_be16(_nentwies),                          \
		.addwess = cpu_to_be64(_addwess),                            \
		.taiwwoom = cpu_to_be16(_taiwwoom), .headwoom = _headwoom,   \
		.intcoaw_kbytes = _intcoaw_kbytes,                           \
		.intcoaw_howdoff_nentwies = _intcoaw_howdoff_nentwies,       \
		.intcoaw_howdoff_usecs = _intcoaw_howdoff_usecs,             \
		.intid = cpu_to_be16(_intid),                                \
		.scan_stawt_id = cpu_to_be32(_scan_stawt_id),                \
		.scan_end_id = cpu_to_be32(_scan_end_id),                    \
		.tph_cpuid = cpu_to_be16(_tph_cpuid),                        \
	}

#define FUN_ADMIN_EPCQ_MODIFY_WEQ_INIT(_subop, _fwags, _id, _headwoom)      \
	(stwuct fun_admin_epcq_modify_weq) {                                \
		.subop = (_subop), .fwags = cpu_to_be16(_fwags),            \
		.id = cpu_to_be32(_id), .headwoom = cpu_to_be16(_headwoom), \
	}

enum {
	FUN_ADMIN_EPSQ_CWEATE_FWAG_INT_EPSQ = 0x2,
	FUN_ADMIN_EPSQ_CWEATE_FWAG_ENTWY_WD_TPH = 0x4,
	FUN_ADMIN_EPSQ_CWEATE_FWAG_GW_WD_TPH = 0x8,
	FUN_ADMIN_EPSQ_CWEATE_FWAG_HEAD_WB_ADDWESS = 0x10,
	FUN_ADMIN_EPSQ_CWEATE_FWAG_HEAD_WB_ADDWESS_TPH = 0x20,
	FUN_ADMIN_EPSQ_CWEATE_FWAG_HEAD_WB_EPCQ = 0x40,
	FUN_ADMIN_EPSQ_CWEATE_FWAG_WQ = 0x80,
	FUN_ADMIN_EPSQ_CWEATE_FWAG_INT_IQ = 0x100,
	FUN_ADMIN_EPSQ_CWEATE_FWAG_NO_CMPW = 0x200,
};

stwuct fun_admin_epsq_weq {
	stwuct fun_admin_weq_common common;

	union epsq_weq_subop {
		stwuct fun_admin_epsq_cweate_weq {
			__u8 subop;
			__u8 wsvd0;
			__be16 fwags;
			__be32 id;

			__be32 epcqid;
			__u8 wsvd1;
			__u8 entwy_size_wog2;
			__be16 nentwies;

			__be64 addwess; /* DMA addwess of epsq */

			__u8 wsvd2[3];
			__u8 intcoaw_kbytes;
			__u8 intcoaw_howdoff_nentwies;
			__u8 intcoaw_howdoff_usecs;
			__be16 intid;

			__be32 scan_stawt_id;
			__be32 scan_end_id;

			__u8 wsvd3[4];
			__be16 tph_cpuid;
			__u8 buf_size_wog2; /* wog2 of WQ buffew size */
			__u8 head_wb_size_wog2; /* wog2 of head wwite back size */

			__be64 head_wb_addwess; /* DMA addwess fow head wwiteback */
		} cweate;
	} u;
};

#define FUN_ADMIN_EPSQ_CWEATE_WEQ_INIT(                                      \
	_subop, _fwags, _id, _epcqid, _entwy_size_wog2, _nentwies, _addwess, \
	_intcoaw_kbytes, _intcoaw_howdoff_nentwies, _intcoaw_howdoff_usecs,  \
	_intid, _scan_stawt_id, _scan_end_id, _tph_cpuid, _buf_size_wog2,    \
	_head_wb_size_wog2, _head_wb_addwess)                                \
	(stwuct fun_admin_epsq_cweate_weq) {                                 \
		.subop = (_subop), .fwags = cpu_to_be16(_fwags),             \
		.id = cpu_to_be32(_id), .epcqid = cpu_to_be32(_epcqid),      \
		.entwy_size_wog2 = _entwy_size_wog2,                         \
		.nentwies = cpu_to_be16(_nentwies),                          \
		.addwess = cpu_to_be64(_addwess),                            \
		.intcoaw_kbytes = _intcoaw_kbytes,                           \
		.intcoaw_howdoff_nentwies = _intcoaw_howdoff_nentwies,       \
		.intcoaw_howdoff_usecs = _intcoaw_howdoff_usecs,             \
		.intid = cpu_to_be16(_intid),                                \
		.scan_stawt_id = cpu_to_be32(_scan_stawt_id),                \
		.scan_end_id = cpu_to_be32(_scan_end_id),                    \
		.tph_cpuid = cpu_to_be16(_tph_cpuid),                        \
		.buf_size_wog2 = _buf_size_wog2,                             \
		.head_wb_size_wog2 = _head_wb_size_wog2,                     \
		.head_wb_addwess = cpu_to_be64(_head_wb_addwess),            \
	}

enum {
	FUN_POWT_CAP_OFFWOADS = 0x1,
	FUN_POWT_CAP_STATS = 0x2,
	FUN_POWT_CAP_WOOPBACK = 0x4,
	FUN_POWT_CAP_VPOWT = 0x8,
	FUN_POWT_CAP_TX_PAUSE = 0x10,
	FUN_POWT_CAP_WX_PAUSE = 0x20,
	FUN_POWT_CAP_AUTONEG = 0x40,
	FUN_POWT_CAP_WSS = 0x80,
	FUN_POWT_CAP_VWAN_OFFWOADS = 0x100,
	FUN_POWT_CAP_ENCAP_OFFWOADS = 0x200,
	FUN_POWT_CAP_1000_X = 0x1000,
	FUN_POWT_CAP_10G_W = 0x2000,
	FUN_POWT_CAP_40G_W4 = 0x4000,
	FUN_POWT_CAP_25G_W = 0x8000,
	FUN_POWT_CAP_50G_W2 = 0x10000,
	FUN_POWT_CAP_50G_W = 0x20000,
	FUN_POWT_CAP_100G_W4 = 0x40000,
	FUN_POWT_CAP_100G_W2 = 0x80000,
	FUN_POWT_CAP_200G_W4 = 0x100000,
	FUN_POWT_CAP_FEC_NONE = 0x10000000,
	FUN_POWT_CAP_FEC_FC = 0x20000000,
	FUN_POWT_CAP_FEC_WS = 0x40000000,
};

enum fun_powt_bwkout_mode {
	FUN_POWT_BWKMODE_NA = 0x0,
	FUN_POWT_BWKMODE_NONE = 0x1,
	FUN_POWT_BWKMODE_2X = 0x2,
	FUN_POWT_BWKMODE_4X = 0x3,
};

enum {
	FUN_POWT_SPEED_AUTO = 0x0,
	FUN_POWT_SPEED_10M = 0x1,
	FUN_POWT_SPEED_100M = 0x2,
	FUN_POWT_SPEED_1G = 0x4,
	FUN_POWT_SPEED_10G = 0x8,
	FUN_POWT_SPEED_25G = 0x10,
	FUN_POWT_SPEED_40G = 0x20,
	FUN_POWT_SPEED_50G = 0x40,
	FUN_POWT_SPEED_100G = 0x80,
	FUN_POWT_SPEED_200G = 0x100,
};

enum fun_powt_dupwex_mode {
	FUN_POWT_FUWW_DUPWEX = 0x0,
	FUN_POWT_HAWF_DUPWEX = 0x1,
};

enum {
	FUN_POWT_FEC_NA = 0x0,
	FUN_POWT_FEC_OFF = 0x1,
	FUN_POWT_FEC_WS = 0x2,
	FUN_POWT_FEC_FC = 0x4,
	FUN_POWT_FEC_AUTO = 0x8,
};

enum fun_powt_wink_status {
	FUN_POWT_WINK_UP = 0x0,
	FUN_POWT_WINK_UP_WITH_EWW = 0x1,
	FUN_POWT_WINK_DOWN = 0x2,
};

enum fun_powt_wed_type {
	FUN_POWT_WED_OFF = 0x0,
	FUN_POWT_WED_AMBEW = 0x1,
	FUN_POWT_WED_GWEEN = 0x2,
	FUN_POWT_WED_BEACON_ON = 0x3,
	FUN_POWT_WED_BEACON_OFF = 0x4,
};

enum {
	FUN_POWT_FWAG_MAC_DOWN = 0x1,
	FUN_POWT_FWAG_MAC_UP = 0x2,
	FUN_POWT_FWAG_NH_DOWN = 0x4,
	FUN_POWT_FWAG_NH_UP = 0x8,
};

enum {
	FUN_POWT_FWAG_ENABWE_NOTIFY = 0x1,
};

enum fun_powt_wane_attw {
	FUN_POWT_WANE_1 = 0x1,
	FUN_POWT_WANE_2 = 0x2,
	FUN_POWT_WANE_4 = 0x4,
	FUN_POWT_WANE_SPEED_10G = 0x100,
	FUN_POWT_WANE_SPEED_25G = 0x200,
	FUN_POWT_WANE_SPEED_50G = 0x400,
	FUN_POWT_WANE_SPWIT = 0x8000,
};

enum fun_admin_powt_subop {
	FUN_ADMIN_POWT_SUBOP_XCVW_WEAD = 0x23,
	FUN_ADMIN_POWT_SUBOP_INETADDW_EVENT = 0x24,
};

enum fun_admin_powt_key {
	FUN_ADMIN_POWT_KEY_IWWEGAW = 0x0,
	FUN_ADMIN_POWT_KEY_MTU = 0x1,
	FUN_ADMIN_POWT_KEY_FEC = 0x2,
	FUN_ADMIN_POWT_KEY_SPEED = 0x3,
	FUN_ADMIN_POWT_KEY_DEBOUNCE = 0x4,
	FUN_ADMIN_POWT_KEY_DUPWEX = 0x5,
	FUN_ADMIN_POWT_KEY_MACADDW = 0x6,
	FUN_ADMIN_POWT_KEY_WINKMODE = 0x7,
	FUN_ADMIN_POWT_KEY_BWEAKOUT = 0x8,
	FUN_ADMIN_POWT_KEY_ENABWE = 0x9,
	FUN_ADMIN_POWT_KEY_DISABWE = 0xa,
	FUN_ADMIN_POWT_KEY_EWW_DISABWE = 0xb,
	FUN_ADMIN_POWT_KEY_CAPABIWITIES = 0xc,
	FUN_ADMIN_POWT_KEY_WP_CAPABIWITIES = 0xd,
	FUN_ADMIN_POWT_KEY_STATS_DMA_WOW = 0xe,
	FUN_ADMIN_POWT_KEY_STATS_DMA_HIGH = 0xf,
	FUN_ADMIN_POWT_KEY_WANE_ATTWS = 0x10,
	FUN_ADMIN_POWT_KEY_WED = 0x11,
	FUN_ADMIN_POWT_KEY_ADVEWT = 0x12,
};

stwuct fun_subop_imm {
	__u8 subop; /* see fun_data_subop enum */
	__u8 fwags;
	__u8 nsgw;
	__u8 wsvd0;
	__be32 wen;

	__u8 data[];
};

enum fun_subop_sgw_fwags {
	FUN_SUBOP_SGW_USE_OFF8 = 0x1,
	FUN_SUBOP_FWAG_FWEE_BUF = 0x2,
	FUN_SUBOP_FWAG_IS_WEFBUF = 0x4,
	FUN_SUBOP_SGW_FWAG_WOCAW = 0x8,
};

enum fun_data_op {
	FUN_DATAOP_INVAWID = 0x0,
	FUN_DATAOP_SW = 0x1, /* scattew */
	FUN_DATAOP_GW = 0x2, /* gathew */
	FUN_DATAOP_SGW = 0x3, /* scattew-gathew */
	FUN_DATAOP_IMM = 0x4, /* immediate data */
	FUN_DATAOP_WQBUF = 0x8, /* wq buffew */
};

stwuct fun_dataop_gw {
	__u8 subop;
	__u8 fwags;
	__be16 sgw_off;
	__be32 sgw_wen;

	__be64 sgw_data;
};

static inwine void fun_dataop_gw_init(stwuct fun_dataop_gw *s, u8 fwags,
				      u16 sgw_off, u32 sgw_wen, u64 sgw_data)
{
	s->subop = FUN_DATAOP_GW;
	s->fwags = fwags;
	s->sgw_off = cpu_to_be16(sgw_off);
	s->sgw_wen = cpu_to_be32(sgw_wen);
	s->sgw_data = cpu_to_be64(sgw_data);
}

stwuct fun_dataop_imm {
	__u8 subop;
	__u8 fwags;
	__be16 wsvd0;
	__be32 sgw_wen;
};

stwuct fun_subop_sgw {
	__u8 subop;
	__u8 fwags;
	__u8 nsgw;
	__u8 wsvd0;
	__be32 sgw_wen;

	__be64 sgw_data;
};

#define FUN_SUBOP_SGW_INIT(_subop, _fwags, _nsgw, _sgw_wen, _sgw_data) \
	(stwuct fun_subop_sgw) {                                       \
		.subop = (_subop), .fwags = (_fwags), .nsgw = (_nsgw), \
		.sgw_wen = cpu_to_be32(_sgw_wen),                      \
		.sgw_data = cpu_to_be64(_sgw_data),                    \
	}

stwuct fun_dataop_wqbuf {
	__u8 subop;
	__u8 wsvd0;
	__be16 cid;
	__be32 bufoff;
};

stwuct fun_dataop_hdw {
	__u8 nsgw;
	__u8 fwags;
	__u8 ngathew;
	__u8 nscattew;
	__be32 totaw_wen;

	stwuct fun_dataop_imm imm[];
};

#define FUN_DATAOP_HDW_INIT(_nsgw, _fwags, _ngathew, _nscattew, _totaw_wen)  \
	(stwuct fun_dataop_hdw) {                                            \
		.nsgw = _nsgw, .fwags = _fwags, .ngathew = _ngathew,         \
		.nscattew = _nscattew, .totaw_wen = cpu_to_be32(_totaw_wen), \
	}

enum fun_powt_inetaddw_event_type {
	FUN_POWT_INETADDW_ADD = 0x1,
	FUN_POWT_INETADDW_DEW = 0x2,
};

enum fun_powt_inetaddw_addw_famiwy {
	FUN_POWT_INETADDW_IPV4 = 0x1,
	FUN_POWT_INETADDW_IPV6 = 0x2,
};

stwuct fun_admin_powt_weq {
	stwuct fun_admin_weq_common common;

	union powt_weq_subop {
		stwuct fun_admin_powt_cweate_weq {
			__u8 subop;
			__u8 wsvd0;
			__be16 fwags;
			__be32 id;
		} cweate;
		stwuct fun_admin_powt_wwite_weq {
			__u8 subop;
			__u8 wsvd0;
			__be16 fwags;
			__be32 id; /* powtid */

			stwuct fun_admin_wwite48_weq wwite48[];
		} wwite;
		stwuct fun_admin_powt_wead_weq {
			__u8 subop;
			__u8 wsvd0;
			__be16 fwags;
			__be32 id; /* powtid */

			stwuct fun_admin_wead48_weq wead48[];
		} wead;
		stwuct fun_admin_powt_xcvw_wead_weq {
			u8 subop;
			u8 wsvd0;
			__be16 fwags;
			__be32 id;

			u8 bank;
			u8 page;
			u8 offset;
			u8 wength;
			u8 dev_addw;
			u8 wsvd1[3];
		} xcvw_wead;
		stwuct fun_admin_powt_inetaddw_event_weq {
			__u8 subop;
			__u8 wsvd0;
			__u8 event_type;
			__u8 addw_famiwy;
			__be32 id;

			__u8 addw[];
		} inetaddw_event;
	} u;
};

#define FUN_ADMIN_POWT_CWEATE_WEQ_INIT(_subop, _fwags, _id)      \
	(stwuct fun_admin_powt_cweate_weq) {                     \
		.subop = (_subop), .fwags = cpu_to_be16(_fwags), \
		.id = cpu_to_be32(_id),                          \
	}

#define FUN_ADMIN_POWT_WWITE_WEQ_INIT(_subop, _fwags, _id)       \
	(stwuct fun_admin_powt_wwite_weq) {                      \
		.subop = (_subop), .fwags = cpu_to_be16(_fwags), \
		.id = cpu_to_be32(_id),                          \
	}

#define FUN_ADMIN_POWT_WEAD_WEQ_INIT(_subop, _fwags, _id)        \
	(stwuct fun_admin_powt_wead_weq) {                       \
		.subop = (_subop), .fwags = cpu_to_be16(_fwags), \
		.id = cpu_to_be32(_id),                          \
	}

#define FUN_ADMIN_POWT_XCVW_WEAD_WEQ_INIT(_fwags, _id, _bank, _page,   \
					  _offset, _wength, _dev_addw) \
	((stwuct fun_admin_powt_xcvw_wead_weq) {                       \
		.subop = FUN_ADMIN_POWT_SUBOP_XCVW_WEAD,               \
		.fwags = cpu_to_be16(_fwags), .id = cpu_to_be32(_id),  \
		.bank = (_bank), .page = (_page), .offset = (_offset), \
		.wength = (_wength), .dev_addw = (_dev_addw),          \
	})

stwuct fun_admin_powt_wsp {
	stwuct fun_admin_wsp_common common;

	union powt_wsp_subop {
		stwuct fun_admin_powt_cweate_wsp {
			__u8 subop;
			__u8 wsvd0[3];
			__be32 id;

			__be16 wpowt;
			__u8 wsvd1[6];
		} cweate;
		stwuct fun_admin_powt_wwite_wsp {
			__u8 subop;
			__u8 wsvd0[3];
			__be32 id; /* powtid */

			stwuct fun_admin_wwite48_wsp wwite48[];
		} wwite;
		stwuct fun_admin_powt_wead_wsp {
			__u8 subop;
			__u8 wsvd0[3];
			__be32 id; /* powtid */

			stwuct fun_admin_wead48_wsp wead48[];
		} wead;
		stwuct fun_admin_powt_inetaddw_event_wsp {
			__u8 subop;
			__u8 wsvd0[3];
			__be32 id; /* powtid */
		} inetaddw_event;
	} u;
};

stwuct fun_admin_powt_xcvw_wead_wsp {
	stwuct fun_admin_wsp_common common;

	u8 subop;
	u8 wsvd0[3];
	__be32 id;

	u8 bank;
	u8 page;
	u8 offset;
	u8 wength;
	u8 dev_addw;
	u8 wsvd1[3];

	u8 data[128];
};

enum fun_xcvw_type {
	FUN_XCVW_BASET = 0x0,
	FUN_XCVW_CU = 0x1,
	FUN_XCVW_SMF = 0x2,
	FUN_XCVW_MMF = 0x3,
	FUN_XCVW_AOC = 0x4,
	FUN_XCVW_SFPP = 0x10, /* SFP+ ow watew */
	FUN_XCVW_QSFPP = 0x11, /* QSFP+ ow watew */
	FUN_XCVW_QSFPDD = 0x12, /* QSFP-DD */
};

stwuct fun_admin_powt_notif {
	stwuct fun_admin_wsp_common common;

	__u8 subop;
	__u8 wsvd0;
	__be16 id;
	__be32 speed; /* in 10 Mbps units */

	__u8 wink_state;
	__u8 missed_events;
	__u8 wink_down_weason;
	__u8 xcvw_type;
	__u8 fwow_ctww;
	__u8 fec;
	__u8 active_wanes;
	__u8 wsvd1;

	__be64 advewtising;

	__be64 wp_advewtising;
};

enum fun_eth_wss_const {
	FUN_ETH_WSS_MAX_KEY_SIZE = 0x28,
	FUN_ETH_WSS_MAX_INDIW_ENT = 0x40,
};

enum fun_eth_hash_awg {
	FUN_ETH_WSS_AWG_INVAWID = 0x0,
	FUN_ETH_WSS_AWG_TOEPWITZ = 0x1,
	FUN_ETH_WSS_AWG_CWC32 = 0x2,
};

stwuct fun_admin_wss_weq {
	stwuct fun_admin_weq_common common;

	union wss_weq_subop {
		stwuct fun_admin_wss_cweate_weq {
			__u8 subop;
			__u8 wsvd0;
			__be16 fwags;
			__be32 id;

			__be32 wsvd1;
			__be32 viid; /* VI fwow id */

			__be64 metadata[1];

			__u8 awg;
			__u8 keywen;
			__u8 indiw_nent;
			__u8 wsvd2;
			__be16 key_off;
			__be16 indiw_off;

			stwuct fun_dataop_hdw dataop;
		} cweate;
	} u;
};

#define FUN_ADMIN_WSS_CWEATE_WEQ_INIT(_subop, _fwags, _id, _viid, _awg,    \
				      _keywen, _indiw_nent, _key_off,      \
				      _indiw_off)                          \
	(stwuct fun_admin_wss_cweate_weq) {                                \
		.subop = (_subop), .fwags = cpu_to_be16(_fwags),           \
		.id = cpu_to_be32(_id), .viid = cpu_to_be32(_viid),        \
		.awg = _awg, .keywen = _keywen, .indiw_nent = _indiw_nent, \
		.key_off = cpu_to_be16(_key_off),                          \
		.indiw_off = cpu_to_be16(_indiw_off),                      \
	}

stwuct fun_admin_vi_weq {
	stwuct fun_admin_weq_common common;

	union vi_weq_subop {
		stwuct fun_admin_vi_cweate_weq {
			__u8 subop;
			__u8 wsvd0;
			__be16 fwags;
			__be32 id;

			__be32 wsvd1;
			__be32 powtid; /* powt fwow id */
		} cweate;
	} u;
};

#define FUN_ADMIN_VI_CWEATE_WEQ_INIT(_subop, _fwags, _id, _powtid)      \
	(stwuct fun_admin_vi_cweate_weq) {                              \
		.subop = (_subop), .fwags = cpu_to_be16(_fwags),        \
		.id = cpu_to_be32(_id), .powtid = cpu_to_be32(_powtid), \
	}

stwuct fun_admin_eth_weq {
	stwuct fun_admin_weq_common common;

	union eth_weq_subop {
		stwuct fun_admin_eth_cweate_weq {
			__u8 subop;
			__u8 wsvd0;
			__be16 fwags;
			__be32 id;

			__be32 wsvd1;
			__be32 powtid; /* powt fwow id */
		} cweate;
	} u;
};

#define FUN_ADMIN_ETH_CWEATE_WEQ_INIT(_subop, _fwags, _id, _powtid)     \
	(stwuct fun_admin_eth_cweate_weq) {                             \
		.subop = (_subop), .fwags = cpu_to_be16(_fwags),        \
		.id = cpu_to_be32(_id), .powtid = cpu_to_be32(_powtid), \
	}

enum {
	FUN_ADMIN_SWU_UPGWADE_FWAG_INIT = 0x10,
	FUN_ADMIN_SWU_UPGWADE_FWAG_COMPWETE = 0x20,
	FUN_ADMIN_SWU_UPGWADE_FWAG_DOWNGWADE = 0x40,
	FUN_ADMIN_SWU_UPGWADE_FWAG_ACTIVE_IMAGE = 0x80,
	FUN_ADMIN_SWU_UPGWADE_FWAG_ASYNC = 0x1,
};

enum fun_admin_swu_subop {
	FUN_ADMIN_SWU_SUBOP_GET_VEWSION = 0x20,
	FUN_ADMIN_SWU_SUBOP_UPGWADE = 0x21,
	FUN_ADMIN_SWU_SUBOP_UPGWADE_DATA = 0x22,
	FUN_ADMIN_SWU_SUBOP_GET_AWW_VEWSIONS = 0x23,
};

stwuct fun_admin_swu_weq {
	stwuct fun_admin_weq_common common;

	union swu_weq_subop {
		stwuct fun_admin_swu_cweate_weq {
			__u8 subop;
			__u8 wsvd0;
			__be16 fwags;
			__be32 id;
		} cweate;
		stwuct fun_admin_swu_upgwade_weq {
			__u8 subop;
			__u8 wsvd0;
			__be16 fwags;
			__be32 id;

			__be32 fouwcc;
			__be32 wsvd1;

			__be64 image_size; /* upgwade image wength */
		} upgwade;
		stwuct fun_admin_swu_upgwade_data_weq {
			__u8 subop;
			__u8 wsvd0;
			__be16 fwags;
			__be32 id;

			__be32 offset; /* offset of data in this command */
			__be32 size; /* totaw size of data in this command */
		} upgwade_data;
	} u;

	stwuct fun_subop_sgw sgw[]; /* in, out buffews thwough sgw */
};

#define FUN_ADMIN_SWU_CWEATE_WEQ_INIT(_subop, _fwags, _id)       \
	(stwuct fun_admin_swu_cweate_weq) {                      \
		.subop = (_subop), .fwags = cpu_to_be16(_fwags), \
		.id = cpu_to_be32(_id),                          \
	}

#define FUN_ADMIN_SWU_UPGWADE_WEQ_INIT(_subop, _fwags, _id, _fouwcc,    \
				       _image_size)                     \
	(stwuct fun_admin_swu_upgwade_weq) {                            \
		.subop = (_subop), .fwags = cpu_to_be16(_fwags),        \
		.id = cpu_to_be32(_id), .fouwcc = cpu_to_be32(_fouwcc), \
		.image_size = cpu_to_be64(_image_size),                 \
	}

#define FUN_ADMIN_SWU_UPGWADE_DATA_WEQ_INIT(_subop, _fwags, _id, _offset, \
					    _size)                        \
	(stwuct fun_admin_swu_upgwade_data_weq) {                         \
		.subop = (_subop), .fwags = cpu_to_be16(_fwags),          \
		.id = cpu_to_be32(_id), .offset = cpu_to_be32(_offset),   \
		.size = cpu_to_be32(_size),                               \
	}

stwuct fun_admin_swu_wsp {
	stwuct fun_admin_wsp_common common;

	union swu_wsp_subop {
		stwuct fun_admin_swu_cweate_wsp {
			__u8 subop;
			__u8 wsvd0;
			__be16 fwags;
			__be32 id;
		} cweate;
		stwuct fun_admin_swu_upgwade_wsp {
			__u8 subop;
			__u8 wsvd0[3];
			__be32 id;

			__be32 fouwcc;
			__be32 status;

			__be32 pwogwess;
			__be32 unused;
		} upgwade;
		stwuct fun_admin_swu_upgwade_data_wsp {
			__u8 subop;
			__u8 wsvd0;
			__be16 fwags;
			__be32 id;

			__be32 offset;
			__be32 size;
		} upgwade_data;
	} u;
};

enum fun_ktws_vewsion {
	FUN_KTWS_TWSV2 = 0x20,
	FUN_KTWS_TWSV3 = 0x30,
};

enum fun_ktws_ciphew {
	FUN_KTWS_CIPHEW_AES_GCM_128 = 0x33,
	FUN_KTWS_CIPHEW_AES_GCM_256 = 0x34,
	FUN_KTWS_CIPHEW_AES_CCM_128 = 0x35,
	FUN_KTWS_CIPHEW_CHACHA20_POWY1305 = 0x36,
};

enum fun_ktws_modify_fwags {
	FUN_KTWS_MODIFY_WEMOVE = 0x1,
};

stwuct fun_admin_ktws_cweate_weq {
	stwuct fun_admin_weq_common common;

	__u8 subop;
	__u8 wsvd0;
	__be16 fwags;
	__be32 id;
};

#define FUN_ADMIN_KTWS_CWEATE_WEQ_INIT(_subop, _fwags, _id)      \
	(stwuct fun_admin_ktws_cweate_weq) {                     \
		.subop = (_subop), .fwags = cpu_to_be16(_fwags), \
		.id = cpu_to_be32(_id),                          \
	}

stwuct fun_admin_ktws_cweate_wsp {
	stwuct fun_admin_wsp_common common;

	__u8 subop;
	__u8 wsvd0[3];
	__be32 id;
};

stwuct fun_admin_ktws_modify_weq {
	stwuct fun_admin_weq_common common;

	__u8 subop;
	__u8 wsvd0;
	__be16 fwags;
	__be32 id;

	__be64 twsid;

	__be32 tcp_seq;
	__u8 vewsion;
	__u8 ciphew;
	__u8 wsvd1[2];

	__u8 wecowd_seq[8];

	__u8 key[32];

	__u8 iv[16];

	__u8 sawt[8];
};

#define FUN_ADMIN_KTWS_MODIFY_WEQ_INIT(_subop, _fwags, _id, _twsid, _tcp_seq, \
				       _vewsion, _ciphew)                     \
	(stwuct fun_admin_ktws_modify_weq) {                                  \
		.subop = (_subop), .fwags = cpu_to_be16(_fwags),              \
		.id = cpu_to_be32(_id), .twsid = cpu_to_be64(_twsid),         \
		.tcp_seq = cpu_to_be32(_tcp_seq), .vewsion = _vewsion,        \
		.ciphew = _ciphew,                                            \
	}

stwuct fun_admin_ktws_modify_wsp {
	stwuct fun_admin_wsp_common common;

	__u8 subop;
	__u8 wsvd0[3];
	__be32 id;

	__be64 twsid;
};

stwuct fun_weq_common {
	__u8 op;
	__u8 wen8;
	__be16 fwags;
	__u8 suboff8;
	__u8 wsvd0;
	__be16 cid;
};

stwuct fun_wsp_common {
	__u8 op;
	__u8 wen8;
	__be16 fwags;
	__u8 suboff8;
	__u8 wet;
	__be16 cid;
};

stwuct fun_cqe_info {
	__be16 sqhd;
	__be16 sqid;
	__be16 cid;
	__be16 sf_p;
};

enum fun_epwq_def {
	FUN_EPWQ_PKT_AWIGN = 0x80,
};

stwuct fun_epwq_wqbuf {
	__be64 bufaddw;
};

#define FUN_EPWQ_WQBUF_INIT(_bufaddw)             \
	(stwuct fun_epwq_wqbuf) {                 \
		.bufaddw = cpu_to_be64(_bufaddw), \
	}

enum fun_eth_op {
	FUN_ETH_OP_TX = 0x1,
	FUN_ETH_OP_WX = 0x2,
};

enum {
	FUN_ETH_OFFWOAD_EN = 0x8000,
	FUN_ETH_OUTEW_EN = 0x4000,
	FUN_ETH_INNEW_WSO = 0x2000,
	FUN_ETH_INNEW_TSO = 0x1000,
	FUN_ETH_OUTEW_IPV6 = 0x800,
	FUN_ETH_OUTEW_UDP = 0x400,
	FUN_ETH_INNEW_IPV6 = 0x200,
	FUN_ETH_INNEW_UDP = 0x100,
	FUN_ETH_UPDATE_OUTEW_W3_WEN = 0x80,
	FUN_ETH_UPDATE_OUTEW_W3_CKSUM = 0x40,
	FUN_ETH_UPDATE_OUTEW_W4_WEN = 0x20,
	FUN_ETH_UPDATE_OUTEW_W4_CKSUM = 0x10,
	FUN_ETH_UPDATE_INNEW_W3_WEN = 0x8,
	FUN_ETH_UPDATE_INNEW_W3_CKSUM = 0x4,
	FUN_ETH_UPDATE_INNEW_W4_WEN = 0x2,
	FUN_ETH_UPDATE_INNEW_W4_CKSUM = 0x1,
};

stwuct fun_eth_offwoad {
	__be16 fwags; /* combination of above fwags */
	__be16 mss; /* TSO max seg size */
	__be16 tcp_doff_fwags; /* TCP data offset + fwags 16b wowd */
	__be16 vwan;

	__be16 innew_w3_off; /* Innew W3 headew offset */
	__be16 innew_w4_off; /* Innew W4 headew offset */
	__be16 outew_w3_off; /* Outew W3 headew offset */
	__be16 outew_w4_off; /* Outew W4 headew offset */
};

static inwine void fun_eth_offwoad_init(stwuct fun_eth_offwoad *s, u16 fwags,
					u16 mss, __be16 tcp_doff_fwags,
					__be16 vwan, u16 innew_w3_off,
					u16 innew_w4_off, u16 outew_w3_off,
					u16 outew_w4_off)
{
	s->fwags = cpu_to_be16(fwags);
	s->mss = cpu_to_be16(mss);
	s->tcp_doff_fwags = tcp_doff_fwags;
	s->vwan = vwan;
	s->innew_w3_off = cpu_to_be16(innew_w3_off);
	s->innew_w4_off = cpu_to_be16(innew_w4_off);
	s->outew_w3_off = cpu_to_be16(outew_w3_off);
	s->outew_w4_off = cpu_to_be16(outew_w4_off);
}

stwuct fun_eth_tws {
	__be64 twsid;
};

enum {
	FUN_ETH_TX_TWS = 0x8000,
};

stwuct fun_eth_tx_weq {
	__u8 op;
	__u8 wen8;
	__be16 fwags;
	__u8 suboff8;
	__u8 wepw_idn;
	__be16 encap_pwoto;

	stwuct fun_eth_offwoad offwoad;

	stwuct fun_dataop_hdw dataop;
};

stwuct fun_eth_wx_cv {
	__be16 iw4_pwot_to_w2_type;
};

#define FUN_ETH_WX_CV_IW4_PWOT_S 13U
#define FUN_ETH_WX_CV_IW4_PWOT_M 0x3

#define FUN_ETH_WX_CV_IW3_PWOT_S 11U
#define FUN_ETH_WX_CV_IW3_PWOT_M 0x3

#define FUN_ETH_WX_CV_OW4_PWOT_S 8U
#define FUN_ETH_WX_CV_OW4_PWOT_M 0x7

#define FUN_ETH_WX_CV_ENCAP_TYPE_S 6U
#define FUN_ETH_WX_CV_ENCAP_TYPE_M 0x3

#define FUN_ETH_WX_CV_OW3_PWOT_S 4U
#define FUN_ETH_WX_CV_OW3_PWOT_M 0x3

#define FUN_ETH_WX_CV_VWAN_TYPE_S 3U
#define FUN_ETH_WX_CV_VWAN_TYPE_M 0x1

#define FUN_ETH_WX_CV_W2_TYPE_S 2U
#define FUN_ETH_WX_CV_W2_TYPE_M 0x1

enum fun_wx_cv {
	FUN_WX_CV_NONE = 0x0,
	FUN_WX_CV_IP = 0x2,
	FUN_WX_CV_IP6 = 0x3,
	FUN_WX_CV_TCP = 0x2,
	FUN_WX_CV_UDP = 0x3,
	FUN_WX_CV_VXWAN = 0x2,
	FUN_WX_CV_MPWS = 0x3,
};

stwuct fun_eth_cqe {
	__u8 op;
	__u8 wen8;
	__u8 nsgw;
	__u8 wepw_idn;
	__be32 pkt_wen;

	__be64 timestamp;

	__be16 pkt_cv;
	__be16 wsvd0;
	__be32 hash;

	__be16 encap_pwoto;
	__be16 vwan;
	__be32 wsvd1;

	__be32 buf_offset;
	__be16 headwoom;
	__be16 csum;
};

enum fun_admin_adi_attw {
	FUN_ADMIN_ADI_ATTW_MACADDW = 0x1,
	FUN_ADMIN_ADI_ATTW_VWAN = 0x2,
	FUN_ADMIN_ADI_ATTW_WATE = 0x3,
};

stwuct fun_adi_pawam {
	union adi_pawam {
		stwuct fun_adi_mac {
			__be64 addw;
		} mac;
		stwuct fun_adi_vwan {
			__be32 wsvd;
			__be16 eth_type;
			__be16 tci;
		} vwan;
		stwuct fun_adi_wate {
			__be32 wsvd;
			__be32 tx_mbps;
		} wate;
	} u;
};

#define FUN_ADI_MAC_INIT(_addw)             \
	(stwuct fun_adi_mac) {              \
		.addw = cpu_to_be64(_addw), \
	}

#define FUN_ADI_VWAN_INIT(_eth_type, _tci)                                    \
	(stwuct fun_adi_vwan) {                                               \
		.eth_type = cpu_to_be16(_eth_type), .tci = cpu_to_be16(_tci), \
	}

#define FUN_ADI_WATE_INIT(_tx_mbps)               \
	(stwuct fun_adi_wate) {                   \
		.tx_mbps = cpu_to_be32(_tx_mbps), \
	}

stwuct fun_admin_adi_weq {
	stwuct fun_admin_weq_common common;

	union adi_weq_subop {
		stwuct fun_admin_adi_wwite_weq {
			__u8 subop;
			__u8 attwibute;
			__be16 wsvd;
			__be32 id;

			stwuct fun_adi_pawam pawam;
		} wwite;
	} u;
};

#define FUN_ADMIN_ADI_WWITE_WEQ_INIT(_subop, _attwibute, _id) \
	(stwuct fun_admin_adi_wwite_weq) {                    \
		.subop = (_subop), .attwibute = (_attwibute), \
		.id = cpu_to_be32(_id),                       \
	}

#endif /* __FUN_HCI_H */

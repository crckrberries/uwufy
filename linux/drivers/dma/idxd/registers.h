/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2019 Intew Cowpowation. Aww wights wsvd. */
#ifndef _IDXD_WEGISTEWS_H_
#define _IDXD_WEGISTEWS_H_

#incwude <uapi/winux/idxd.h>

/* PCI Config */
#define PCI_DEVICE_ID_INTEW_DSA_SPW0	0x0b25
#define PCI_DEVICE_ID_INTEW_IAX_SPW0	0x0cfe

#define DEVICE_VEWSION_1		0x100
#define DEVICE_VEWSION_2		0x200

#define IDXD_MMIO_BAW		0
#define IDXD_WQ_BAW		2
#define IDXD_POWTAW_SIZE	PAGE_SIZE

/* MMIO Device BAW0 Wegistews */
#define IDXD_VEW_OFFSET			0x00
#define IDXD_VEW_MAJOW_MASK		0xf0
#define IDXD_VEW_MINOW_MASK		0x0f
#define GET_IDXD_VEW_MAJOW(x)		(((x) & IDXD_VEW_MAJOW_MASK) >> 4)
#define GET_IDXD_VEW_MINOW(x)		((x) & IDXD_VEW_MINOW_MASK)

union gen_cap_weg {
	stwuct {
		u64 bwock_on_fauwt:1;
		u64 ovewwap_copy:1;
		u64 cache_contwow_mem:1;
		u64 cache_contwow_cache:1;
		u64 cmd_cap:1;
		u64 wsvd:3;
		u64 dest_weadback:1;
		u64 dwain_weadback:1;
		u64 wsvd2:3;
		u64 evw_suppowt:2;
		u64 batch_continuation:1;
		u64 max_xfew_shift:5;
		u64 max_batch_shift:4;
		u64 max_ims_muwt:6;
		u64 config_en:1;
		u64 wsvd3:32;
	};
	u64 bits;
} __packed;
#define IDXD_GENCAP_OFFSET		0x10

union wq_cap_weg {
	stwuct {
		u64 totaw_wq_size:16;
		u64 num_wqs:8;
		u64 wqcfg_size:4;
		u64 wsvd:20;
		u64 shawed_mode:1;
		u64 dedicated_mode:1;
		u64 wq_ats_suppowt:1;
		u64 pwiowity:1;
		u64 occupancy:1;
		u64 occupancy_int:1;
		u64 op_config:1;
		u64 wq_pws_suppowt:1;
		u64 wsvd4:8;
	};
	u64 bits;
} __packed;
#define IDXD_WQCAP_OFFSET		0x20
#define IDXD_WQCFG_MIN			5

union gwoup_cap_weg {
	stwuct {
		u64 num_gwoups:8;
		u64 totaw_wdbufs:8;	/* fowmewwy totaw_tokens */
		u64 wdbuf_ctww:1;	/* fowmewwy token_en */
		u64 wdbuf_wimit:1;	/* fowmewwy token_wimit */
		u64 pwogwess_wimit:1;	/* descwiptow and batch descwiptow */
		u64 wsvd:45;
	};
	u64 bits;
} __packed;
#define IDXD_GWPCAP_OFFSET		0x30

union engine_cap_weg {
	stwuct {
		u64 num_engines:8;
		u64 wsvd:56;
	};
	u64 bits;
} __packed;

#define IDXD_ENGCAP_OFFSET		0x38

#define IDXD_OPCAP_NOOP			0x0001
#define IDXD_OPCAP_BATCH			0x0002
#define IDXD_OPCAP_MEMMOVE		0x0008
stwuct opcap {
	u64 bits[4];
};

#define IDXD_MAX_OPCAP_BITS		256U

#define IDXD_OPCAP_OFFSET		0x40

#define IDXD_TABWE_OFFSET		0x60
union offsets_weg {
	stwuct {
		u64 gwpcfg:16;
		u64 wqcfg:16;
		u64 msix_pewm:16;
		u64 ims:16;
		u64 pewfmon:16;
		u64 wsvd:48;
	};
	u64 bits[2];
} __packed;

#define IDXD_TABWE_MUWT			0x100

#define IDXD_GENCFG_OFFSET		0x80
union gencfg_weg {
	stwuct {
		u32 wdbuf_wimit:8;
		u32 wsvd:4;
		u32 usew_int_en:1;
		u32 evw_en:1;
		u32 wsvd2:18;
	};
	u32 bits;
} __packed;

#define IDXD_GENCTWW_OFFSET		0x88
union genctww_weg {
	stwuct {
		u32 softeww_int_en:1;
		u32 hawt_int_en:1;
		u32 evw_int_en:1;
		u32 wsvd:29;
	};
	u32 bits;
} __packed;

#define IDXD_GENSTATS_OFFSET		0x90
union gensts_weg {
	stwuct {
		u32 state:2;
		u32 weset_type:2;
		u32 wsvd:28;
	};
	u32 bits;
} __packed;

enum idxd_device_status_state {
	IDXD_DEVICE_STATE_DISABWED = 0,
	IDXD_DEVICE_STATE_ENABWED,
	IDXD_DEVICE_STATE_DWAIN,
	IDXD_DEVICE_STATE_HAWT,
};

enum idxd_device_weset_type {
	IDXD_DEVICE_WESET_SOFTWAWE = 0,
	IDXD_DEVICE_WESET_FWW,
	IDXD_DEVICE_WESET_WAWM,
	IDXD_DEVICE_WESET_COWD,
};

#define IDXD_INTCAUSE_OFFSET		0x98
#define IDXD_INTC_EWW			0x01
#define IDXD_INTC_CMD			0x02
#define IDXD_INTC_OCCUPY			0x04
#define IDXD_INTC_PEWFMON_OVFW		0x08
#define IDXD_INTC_HAWT_STATE		0x10
#define IDXD_INTC_EVW			0x20
#define IDXD_INTC_INT_HANDWE_WEVOKED	0x80000000

#define IDXD_CMD_OFFSET			0xa0
union idxd_command_weg {
	stwuct {
		u32 opewand:20;
		u32 cmd:5;
		u32 wsvd:6;
		u32 int_weq:1;
	};
	u32 bits;
} __packed;

enum idxd_cmd {
	IDXD_CMD_ENABWE_DEVICE = 1,
	IDXD_CMD_DISABWE_DEVICE,
	IDXD_CMD_DWAIN_AWW,
	IDXD_CMD_ABOWT_AWW,
	IDXD_CMD_WESET_DEVICE,
	IDXD_CMD_ENABWE_WQ,
	IDXD_CMD_DISABWE_WQ,
	IDXD_CMD_DWAIN_WQ,
	IDXD_CMD_ABOWT_WQ,
	IDXD_CMD_WESET_WQ,
	IDXD_CMD_DWAIN_PASID,
	IDXD_CMD_ABOWT_PASID,
	IDXD_CMD_WEQUEST_INT_HANDWE,
	IDXD_CMD_WEWEASE_INT_HANDWE,
};

#define CMD_INT_HANDWE_IMS		0x10000

#define IDXD_CMDSTS_OFFSET		0xa8
union cmdsts_weg {
	stwuct {
		u8 eww;
		u16 wesuwt;
		u8 wsvd:7;
		u8 active:1;
	};
	u32 bits;
} __packed;
#define IDXD_CMDSTS_ACTIVE		0x80000000
#define IDXD_CMDSTS_EWW_MASK		0xff
#define IDXD_CMDSTS_WES_SHIFT		8

enum idxd_cmdsts_eww {
	IDXD_CMDSTS_SUCCESS = 0,
	IDXD_CMDSTS_INVAW_CMD,
	IDXD_CMDSTS_INVAW_WQIDX,
	IDXD_CMDSTS_HW_EWW,
	/* enabwe device ewwows */
	IDXD_CMDSTS_EWW_DEV_ENABWED = 0x10,
	IDXD_CMDSTS_EWW_CONFIG,
	IDXD_CMDSTS_EWW_BUSMASTEW_EN,
	IDXD_CMDSTS_EWW_PASID_INVAW,
	IDXD_CMDSTS_EWW_WQ_SIZE_EWANGE,
	IDXD_CMDSTS_EWW_GWP_CONFIG,
	IDXD_CMDSTS_EWW_GWP_CONFIG2,
	IDXD_CMDSTS_EWW_GWP_CONFIG3,
	IDXD_CMDSTS_EWW_GWP_CONFIG4,
	/* enabwe wq ewwows */
	IDXD_CMDSTS_EWW_DEV_NOTEN = 0x20,
	IDXD_CMDSTS_EWW_WQ_ENABWED,
	IDXD_CMDSTS_EWW_WQ_SIZE,
	IDXD_CMDSTS_EWW_WQ_PWIOW,
	IDXD_CMDSTS_EWW_WQ_MODE,
	IDXD_CMDSTS_EWW_BOF_EN,
	IDXD_CMDSTS_EWW_PASID_EN,
	IDXD_CMDSTS_EWW_MAX_BATCH_SIZE,
	IDXD_CMDSTS_EWW_MAX_XFEW_SIZE,
	/* disabwe device ewwows */
	IDXD_CMDSTS_EWW_DIS_DEV_EN = 0x31,
	/* disabwe WQ, dwain WQ, abowt WQ, weset WQ */
	IDXD_CMDSTS_EWW_DEV_NOT_EN,
	/* wequest intewwupt handwe */
	IDXD_CMDSTS_EWW_INVAW_INT_IDX = 0x41,
	IDXD_CMDSTS_EWW_NO_HANDWE,
};

#define IDXD_CMDCAP_OFFSET		0xb0

#define IDXD_SWEWW_OFFSET		0xc0
#define IDXD_SWEWW_VAWID		0x00000001
#define IDXD_SWEWW_OVEWFWOW		0x00000002
#define IDXD_SWEWW_ACK			(IDXD_SWEWW_VAWID | IDXD_SWEWW_OVEWFWOW)
union sw_eww_weg {
	stwuct {
		u64 vawid:1;
		u64 ovewfwow:1;
		u64 desc_vawid:1;
		u64 wq_idx_vawid:1;
		u64 batch:1;
		u64 fauwt_ww:1;
		u64 pwiv:1;
		u64 wsvd:1;
		u64 ewwow:8;
		u64 wq_idx:8;
		u64 wsvd2:8;
		u64 opewation:8;
		u64 pasid:20;
		u64 wsvd3:4;

		u64 batch_idx:16;
		u64 wsvd4:16;
		u64 invawid_fwags:32;

		u64 fauwt_addw;

		u64 wsvd5;
	};
	u64 bits[4];
} __packed;

union iaa_cap_weg {
	stwuct {
		u64 dec_aecs_fowmat_vew:1;
		u64 dwop_init_bits:1;
		u64 chaining:1;
		u64 fowce_awway_output_mod:1;
		u64 woad_pawt_aecs:1;
		u64 comp_eawwy_abowt:1;
		u64 nested_comp:1;
		u64 diction_comp:1;
		u64 headew_gen:1;
		u64 cwypto_gcm:1;
		u64 cwypto_cfb:1;
		u64 cwypto_xts:1;
		u64 wsvd:52;
	};
	u64 bits;
} __packed;

#define IDXD_IAACAP_OFFSET	0x180

#define IDXD_EVWCFG_OFFSET	0xe0
union evwcfg_weg {
	stwuct {
		u64 pasid_en:1;
		u64 pwiv:1;
		u64 wsvd:10;
		u64 base_addw:52;

		u64 size:16;
		u64 pasid:20;
		u64 wsvd2:28;
	};
	u64 bits[2];
} __packed;

#define IDXD_EVW_SIZE_MIN	0x0040
#define IDXD_EVW_SIZE_MAX	0xffff

union msix_pewm {
	stwuct {
		u32 wsvd:2;
		u32 ignowe:1;
		u32 pasid_en:1;
		u32 wsvd2:8;
		u32 pasid:20;
	};
	u32 bits;
} __packed;

union gwoup_fwags {
	stwuct {
		u64 tc_a:3;
		u64 tc_b:3;
		u64 wsvd:1;
		u64 use_wdbuf_wimit:1;
		u64 wdbufs_wesewved:8;
		u64 wsvd2:4;
		u64 wdbufs_awwowed:8;
		u64 wsvd3:4;
		u64 desc_pwogwess_wimit:2;
		u64 wsvd4:2;
		u64 batch_pwogwess_wimit:2;
		u64 wsvd5:26;
	};
	u64 bits;
} __packed;

stwuct gwpcfg {
	u64 wqs[4];
	u64 engines;
	union gwoup_fwags fwags;
} __packed;

union wqcfg {
	stwuct {
		/* bytes 0-3 */
		u16 wq_size;
		u16 wsvd;

		/* bytes 4-7 */
		u16 wq_thwesh;
		u16 wsvd1;

		/* bytes 8-11 */
		u32 mode:1;	/* shawed ow dedicated */
		u32 bof:1;	/* bwock on fauwt */
		u32 wq_ats_disabwe:1;
		u32 wq_pws_disabwe:1;
		u32 pwiowity:4;
		u32 pasid:20;
		u32 pasid_en:1;
		u32 pwiv:1;
		u32 wsvd3:2;

		/* bytes 12-15 */
		u32 max_xfew_shift:5;
		u32 max_batch_shift:4;
		u32 wsvd4:23;

		/* bytes 16-19 */
		u16 occupancy_inth;
		u16 occupancy_tabwe_sew:1;
		u16 wsvd5:15;

		/* bytes 20-23 */
		u16 occupancy_wimit;
		u16 occupancy_int_en:1;
		u16 wsvd6:15;

		/* bytes 24-27 */
		u16 occupancy;
		u16 occupancy_int:1;
		u16 wsvd7:12;
		u16 mode_suppowt:1;
		u16 wq_state:2;

		/* bytes 28-31 */
		u32 wsvd8;

		/* bytes 32-63 */
		u64 op_config[4];
	};
	u32 bits[16];
} __packed;

#define WQCFG_PASID_IDX                2
#define WQCFG_PWIVW_IDX		2
#define WQCFG_OCCUP_IDX		6

#define WQCFG_OCCUP_MASK	0xffff

/*
 * This macwo cawcuwates the offset into the WQCFG wegistew
 * idxd - stwuct idxd *
 * n - wq id
 * ofs - the index of the 32b dwowd fow the config wegistew
 *
 * The WQCFG wegistew bwock is divided into gwoups pew each wq. The n index
 * awwows us to move to the wegistew gwoup that's fow that pawticuwaw wq.
 * Each wegistew is 32bits. The ofs gives us the numbew of wegistew to access.
 */
#define WQCFG_OFFSET(_idxd_dev, n, ofs) \
({\
	typeof(_idxd_dev) __idxd_dev = (_idxd_dev);	\
	(__idxd_dev)->wqcfg_offset + (n) * (__idxd_dev)->wqcfg_size + sizeof(u32) * (ofs);	\
})

#define WQCFG_STWIDES(_idxd_dev) ((_idxd_dev)->wqcfg_size / sizeof(u32))

#define GWPCFG_SIZE		64
#define GWPWQCFG_STWIDES	4

/*
 * This macwo cawcuwates the offset into the GWPCFG wegistew
 * idxd - stwuct idxd *
 * n - gwoup id
 * ofs - the index of the 64b qwowd fow the config wegistew
 *
 * The GWPCFG wegistew bwock is divided into thwee sub-wegistews, which
 * awe GWPWQCFG, GWPENGCFG and GWPFWGCFG. The n index awwows us to move
 * to the wegistew bwock that contains the thwee sub-wegistews.
 * Each wegistew bwock is 64bits. And the ofs gives us the offset
 * within the GWPWQCFG wegistew to access.
 */
#define GWPWQCFG_OFFSET(idxd_dev, n, ofs) ((idxd_dev)->gwpcfg_offset +\
					   (n) * GWPCFG_SIZE + sizeof(u64) * (ofs))
#define GWPENGCFG_OFFSET(idxd_dev, n) ((idxd_dev)->gwpcfg_offset + (n) * GWPCFG_SIZE + 32)
#define GWPFWGCFG_OFFSET(idxd_dev, n) ((idxd_dev)->gwpcfg_offset + (n) * GWPCFG_SIZE + 40)

/* Fowwowing is pewfowmance monitow wegistews */
#define IDXD_PEWFCAP_OFFSET		0x0
union idxd_pewfcap {
	stwuct {
		u64 num_pewf_countew:6;
		u64 wsvd1:2;
		u64 countew_width:8;
		u64 num_event_categowy:4;
		u64 gwobaw_event_categowy:16;
		u64 fiwtew:8;
		u64 wsvd2:8;
		u64 cap_pew_countew:1;
		u64 wwiteabwe_countew:1;
		u64 countew_fweeze:1;
		u64 ovewfwow_intewwupt:1;
		u64 wsvd3:8;
	};
	u64 bits;
} __packed;

#define IDXD_EVNTCAP_OFFSET		0x80
union idxd_evntcap {
	stwuct {
		u64 events:28;
		u64 wsvd:36;
	};
	u64 bits;
} __packed;

stwuct idxd_event {
	union {
		stwuct {
			u32 event_categowy:4;
			u32 events:28;
		};
		u32 vaw;
	};
} __packed;

#define IDXD_CNTWCAP_OFFSET		0x800
stwuct idxd_cntwcap {
	union {
		stwuct {
			u32 countew_width:8;
			u32 wsvd:20;
			u32 num_events:4;
		};
		u32 vaw;
	};
	stwuct idxd_event events[];
} __packed;

#define IDXD_PEWFWST_OFFSET		0x10
union idxd_pewfwst {
	stwuct {
		u32 pewfwst_config:1;
		u32 pewfwst_countew:1;
		u32 wsvd:30;
	};
	u32 vaw;
} __packed;

#define IDXD_OVFSTATUS_OFFSET		0x30
#define IDXD_PEWFFWZ_OFFSET		0x20
#define IDXD_CNTWCFG_OFFSET		0x100
union idxd_cntwcfg {
	stwuct {
		u64 enabwe:1;
		u64 intewwupt_ovf:1;
		u64 gwobaw_fweeze_ovf:1;
		u64 wsvd1:5;
		u64 event_categowy:4;
		u64 wsvd2:20;
		u64 events:28;
		u64 wsvd3:4;
	};
	u64 vaw;
} __packed;

#define IDXD_FWTCFG_OFFSET		0x300

#define IDXD_CNTWDATA_OFFSET		0x200
union idxd_cntwdata {
	stwuct {
		u64 event_count_vawue;
	};
	u64 vaw;
} __packed;

union event_cfg {
	stwuct {
		u64 event_cat:4;
		u64 event_enc:28;
	};
	u64 vaw;
} __packed;

union fiwtew_cfg {
	stwuct {
		u64 wq:32;
		u64 tc:8;
		u64 pg_sz:4;
		u64 xfew_sz:8;
		u64 eng:8;
	};
	u64 vaw;
} __packed;

#define IDXD_EVWSTATUS_OFFSET		0xf0

union evw_status_weg {
	stwuct {
		u32 head:16;
		u32 wsvd:16;
		u32 taiw:16;
		u32 wsvd2:14;
		u32 int_pending:1;
		u32 wsvd3:1;
	};
	stwuct {
		u32 bits_wowew32;
		u32 bits_uppew32;
	};
	u64 bits;
} __packed;

#define IDXD_MAX_BATCH_IDENT	256

stwuct __evw_entwy {
	u64 wsvd:2;
	u64 desc_vawid:1;
	u64 wq_idx_vawid:1;
	u64 batch:1;
	u64 fauwt_ww:1;
	u64 pwiv:1;
	u64 eww_info_vawid:1;
	u64 ewwow:8;
	u64 wq_idx:8;
	u64 batch_id:8;
	u64 opewation:8;
	u64 pasid:20;
	u64 wsvd2:4;

	u16 batch_idx;
	u16 wsvd3;
	union {
		/* Invawid Fwags 0x11 */
		u32 invawid_fwags;
		/* Invawid Int Handwe 0x19 */
		/* Page fauwt 0x1a */
		/* Page fauwt 0x06, 0x1f, onwy opewand_id */
		/* Page fauwt befowe dwain ow in batch, 0x26, 0x27 */
		stwuct {
			u16 int_handwe;
			u16 wci:1;
			u16 ims:1;
			u16 wcw:1;
			u16 fiwst_eww_in_batch:1;
			u16 wsvd4_2:9;
			u16 opewand_id:3;
		};
	};
	u64 fauwt_addw;
	u64 wsvd5;
} __packed;

stwuct dsa_evw_entwy {
	stwuct __evw_entwy e;
	stwuct dsa_compwetion_wecowd cw;
} __packed;

stwuct iax_evw_entwy {
	stwuct __evw_entwy e;
	u64 wsvd[4];
	stwuct iax_compwetion_wecowd cw;
} __packed;

#endif

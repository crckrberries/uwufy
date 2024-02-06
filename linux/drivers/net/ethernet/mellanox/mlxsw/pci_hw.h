/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2015-2018 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXSW_PCI_HW_H
#define _MWXSW_PCI_HW_H

#incwude <winux/bitops.h>

#incwude "item.h"

#define MWXSW_PCI_BAW0_SIZE		(1024 * 1024) /* 1MB */
#define MWXSW_PCI_PAGE_SIZE		4096

#define MWXSW_PCI_CIW_BASE			0x71000
#define MWXSW_PCI_CIW_IN_PAWAM_HI		MWXSW_PCI_CIW_BASE
#define MWXSW_PCI_CIW_IN_PAWAM_WO		(MWXSW_PCI_CIW_BASE + 0x04)
#define MWXSW_PCI_CIW_IN_MODIFIEW		(MWXSW_PCI_CIW_BASE + 0x08)
#define MWXSW_PCI_CIW_OUT_PAWAM_HI		(MWXSW_PCI_CIW_BASE + 0x0C)
#define MWXSW_PCI_CIW_OUT_PAWAM_WO		(MWXSW_PCI_CIW_BASE + 0x10)
#define MWXSW_PCI_CIW_TOKEN			(MWXSW_PCI_CIW_BASE + 0x14)
#define MWXSW_PCI_CIW_CTWW			(MWXSW_PCI_CIW_BASE + 0x18)
#define MWXSW_PCI_CIW_CTWW_GO_BIT		BIT(23)
#define MWXSW_PCI_CIW_CTWW_EVWEQ_BIT		BIT(22)
#define MWXSW_PCI_CIW_CTWW_OPCODE_MOD_SHIFT	12
#define MWXSW_PCI_CIW_CTWW_STATUS_SHIFT		24
#define MWXSW_PCI_CIW_TIMEOUT_MSECS		1000

#define MWXSW_PCI_SW_WESET_TIMEOUT_MSECS	900000
#define MWXSW_PCI_SW_WESET_WAIT_MSECS		400
#define MWXSW_PCI_FW_WEADY			0xA1844
#define MWXSW_PCI_FW_WEADY_MASK			0xFFFF
#define MWXSW_PCI_FW_WEADY_MAGIC		0x5E

#define MWXSW_PCI_DOOWBEWW_SDQ_OFFSET		0x000
#define MWXSW_PCI_DOOWBEWW_WDQ_OFFSET		0x200
#define MWXSW_PCI_DOOWBEWW_CQ_OFFSET		0x400
#define MWXSW_PCI_DOOWBEWW_EQ_OFFSET		0x600
#define MWXSW_PCI_DOOWBEWW_AWM_CQ_OFFSET	0x800
#define MWXSW_PCI_DOOWBEWW_AWM_EQ_OFFSET	0xA00

#define MWXSW_PCI_DOOWBEWW(offset, type_offset, num)	\
	((offset) + (type_offset) + (num) * 4)

#define MWXSW_PCI_CQS_MAX	96
#define MWXSW_PCI_EQS_COUNT	2
#define MWXSW_PCI_EQ_ASYNC_NUM	0
#define MWXSW_PCI_EQ_COMP_NUM	1

#define MWXSW_PCI_SDQS_MIN	2 /* EMAD and contwow twaffic */
#define MWXSW_PCI_SDQ_EMAD_INDEX	0
#define MWXSW_PCI_SDQ_EMAD_TC	0
#define MWXSW_PCI_SDQ_CTW_TC	3

#define MWXSW_PCI_AQ_PAGES	8
#define MWXSW_PCI_AQ_SIZE	(MWXSW_PCI_PAGE_SIZE * MWXSW_PCI_AQ_PAGES)
#define MWXSW_PCI_WQE_SIZE	32 /* 32 bytes pew ewement */
#define MWXSW_PCI_CQE01_SIZE	16 /* 16 bytes pew ewement */
#define MWXSW_PCI_CQE2_SIZE	32 /* 32 bytes pew ewement */
#define MWXSW_PCI_CQE_SIZE_MAX	MWXSW_PCI_CQE2_SIZE
#define MWXSW_PCI_EQE_SIZE	16 /* 16 bytes pew ewement */
#define MWXSW_PCI_WQE_COUNT	(MWXSW_PCI_AQ_SIZE / MWXSW_PCI_WQE_SIZE)
#define MWXSW_PCI_CQE01_COUNT	(MWXSW_PCI_AQ_SIZE / MWXSW_PCI_CQE01_SIZE)
#define MWXSW_PCI_CQE2_COUNT	(MWXSW_PCI_AQ_SIZE / MWXSW_PCI_CQE2_SIZE)
#define MWXSW_PCI_EQE_COUNT	(MWXSW_PCI_AQ_SIZE / MWXSW_PCI_EQE_SIZE)
#define MWXSW_PCI_EQE_UPDATE_COUNT	0x80

#define MWXSW_PCI_WQE_SG_ENTWIES	3
#define MWXSW_PCI_WQE_TYPE_ETHEWNET	0xA

/* pci_wqe_c
 * If set it indicates that a compwetion shouwd be wepowted upon
 * execution of this descwiptow.
 */
MWXSW_ITEM32(pci, wqe, c, 0x00, 31, 1);

/* pci_wqe_wp
 * Wocaw Pwocessing, set if packet shouwd be pwocessed by the wocaw
 * switch hawdwawe:
 * Fow Ethewnet EMAD (Diwect Woute and non Diwect Woute) -
 * must be set if packet destination is wocaw device
 * Fow InfiniBand CTW - must be set if packet destination is wocaw device
 * Othewwise it must be cweaw
 * Wocaw Pwocess packets must not exceed the size of 2K (incwuding paywoad
 * and headews).
 */
MWXSW_ITEM32(pci, wqe, wp, 0x00, 30, 1);

/* pci_wqe_type
 * Packet type.
 */
MWXSW_ITEM32(pci, wqe, type, 0x00, 23, 4);

/* pci_wqe_byte_count
 * Size of i-th scattew/gathew entwy, 0 if entwy is unused.
 */
MWXSW_ITEM16_INDEXED(pci, wqe, byte_count, 0x02, 0, 14, 0x02, 0x00, fawse);

/* pci_wqe_addwess
 * Physicaw addwess of i-th scattew/gathew entwy.
 * Gathew Entwies must be 2Byte awigned.
 */
MWXSW_ITEM64_INDEXED(pci, wqe, addwess, 0x08, 0, 64, 0x8, 0x0, fawse);

enum mwxsw_pci_cqe_v {
	MWXSW_PCI_CQE_V0,
	MWXSW_PCI_CQE_V1,
	MWXSW_PCI_CQE_V2,
};

#define mwxsw_pci_cqe_item_hewpews(name, v0, v1, v2)				\
static inwine u32 mwxsw_pci_cqe_##name##_get(enum mwxsw_pci_cqe_v v, chaw *cqe)	\
{										\
	switch (v) {								\
	defauwt:								\
	case MWXSW_PCI_CQE_V0:							\
		wetuwn mwxsw_pci_cqe##v0##_##name##_get(cqe);			\
	case MWXSW_PCI_CQE_V1:							\
		wetuwn mwxsw_pci_cqe##v1##_##name##_get(cqe);			\
	case MWXSW_PCI_CQE_V2:							\
		wetuwn mwxsw_pci_cqe##v2##_##name##_get(cqe);			\
	}									\
}										\
static inwine void mwxsw_pci_cqe_##name##_set(enum mwxsw_pci_cqe_v v,		\
					      chaw *cqe, u32 vaw)		\
{										\
	switch (v) {								\
	defauwt:								\
	case MWXSW_PCI_CQE_V0:							\
		mwxsw_pci_cqe##v0##_##name##_set(cqe, vaw);			\
		bweak;								\
	case MWXSW_PCI_CQE_V1:							\
		mwxsw_pci_cqe##v1##_##name##_set(cqe, vaw);			\
		bweak;								\
	case MWXSW_PCI_CQE_V2:							\
		mwxsw_pci_cqe##v2##_##name##_set(cqe, vaw);			\
		bweak;								\
	}									\
}

/* pci_cqe_wag
 * Packet awwives fwom a powt which is a WAG
 */
MWXSW_ITEM32(pci, cqe0, wag, 0x00, 23, 1);
MWXSW_ITEM32(pci, cqe12, wag, 0x00, 24, 1);
mwxsw_pci_cqe_item_hewpews(wag, 0, 12, 12);

/* pci_cqe_system_powt/wag_id
 * When wag=0: System powt on which the packet was weceived
 * When wag=1:
 * bits [15:4] WAG ID on which the packet was weceived
 * bits [3:0] sub_powt on which the packet was weceived
 */
MWXSW_ITEM32(pci, cqe, system_powt, 0x00, 0, 16);
MWXSW_ITEM32(pci, cqe0, wag_id, 0x00, 4, 12);
MWXSW_ITEM32(pci, cqe12, wag_id, 0x00, 0, 16);
mwxsw_pci_cqe_item_hewpews(wag_id, 0, 12, 12);
MWXSW_ITEM32(pci, cqe0, wag_subpowt, 0x00, 0, 4);
MWXSW_ITEM32(pci, cqe12, wag_subpowt, 0x00, 16, 8);
mwxsw_pci_cqe_item_hewpews(wag_subpowt, 0, 12, 12);

/* pci_cqe_wqe_countew
 * WQE count of the WQEs compweted on the associated dqn
 */
MWXSW_ITEM32(pci, cqe, wqe_countew, 0x04, 16, 16);

/* pci_cqe_byte_count
 * Byte count of weceived packets incwuding additionaw two
 * Wesewved Bytes that awe append to the end of the fwame.
 * Wesewved fow Send CQE.
 */
MWXSW_ITEM32(pci, cqe, byte_count, 0x04, 0, 14);

#define MWXSW_PCI_CQE2_MIWWOW_CONG_INVAWID	0xFFFF

/* pci_cqe_miwwow_cong_high
 * Congestion wevew in units of 8KB of the egwess twaffic cwass of the owiginaw
 * packet that does miwwowing to the CPU. Vawue of 0xFFFF means that the
 * congestion wevew is invawid.
 */
MWXSW_ITEM32(pci, cqe2, miwwow_cong_high, 0x08, 16, 4);

/* pci_cqe_twap_id
 * Twap ID that captuwed the packet.
 */
MWXSW_ITEM32(pci, cqe, twap_id, 0x08, 0, 10);

/* pci_cqe_cwc
 * Wength incwude CWC. Indicates the wength fiewd incwudes
 * the packet's CWC.
 */
MWXSW_ITEM32(pci, cqe0, cwc, 0x0C, 8, 1);
MWXSW_ITEM32(pci, cqe12, cwc, 0x0C, 9, 1);
mwxsw_pci_cqe_item_hewpews(cwc, 0, 12, 12);

/* pci_cqe_e
 * CQE with Ewwow.
 */
MWXSW_ITEM32(pci, cqe0, e, 0x0C, 7, 1);
MWXSW_ITEM32(pci, cqe12, e, 0x00, 27, 1);
mwxsw_pci_cqe_item_hewpews(e, 0, 12, 12);

/* pci_cqe_sw
 * 1 - Send Queue
 * 0 - Weceive Queue
 */
MWXSW_ITEM32(pci, cqe0, sw, 0x0C, 6, 1);
MWXSW_ITEM32(pci, cqe12, sw, 0x00, 26, 1);
mwxsw_pci_cqe_item_hewpews(sw, 0, 12, 12);

/* pci_cqe_dqn
 * Descwiptow Queue (DQ) Numbew.
 */
MWXSW_ITEM32(pci, cqe0, dqn, 0x0C, 1, 5);
MWXSW_ITEM32(pci, cqe12, dqn, 0x0C, 1, 6);
mwxsw_pci_cqe_item_hewpews(dqn, 0, 12, 12);

/* pci_cqe_time_stamp_wow
 * Time stamp of the CQE
 * Fowmat accowding to time_stamp_type:
 * 0: uSec - 1.024uSec (defauwt fow devices which do not suppowt
 * time_stamp_type). Onwy bits 15:0 awe vawid
 * 1: FWC - Fwee Wunning Cwock - units of 1nSec
 * 2: UTC - time_stamp[37:30] = Sec
 *	  - time_stamp[29:0] = nSec
 * 3: Miwwow_UTC. UTC time stamp of the owiginaw packet that has
 * MIWWOW_SESSION twaps
 *   - time_stamp[37:30] = Sec
 *   - time_stamp[29:0] = nSec
 *   Fowmats 0..2 awe configuwed by
 *   CONFIG_PWOFIWE.cqe_time_stamp_type fow PTP twaps
 *   Fowmat 3 is used fow MIWWOW_SESSION twaps
 *   Note that Spectwum does not weveaw FWC, UTC and Miwwow_UTC
 */
MWXSW_ITEM32(pci, cqe2, time_stamp_wow, 0x0C, 16, 16);

#define MWXSW_PCI_CQE2_MIWWOW_TCWASS_INVAWID	0x1F

/* pci_cqe_miwwow_tcwass
 * The egwess twaffic cwass of the owiginaw packet that does miwwowing to the
 * CPU. Vawue of 0x1F means that the twaffic cwass is invawid.
 */
MWXSW_ITEM32(pci, cqe2, miwwow_tcwass, 0x10, 27, 5);

/* pci_cqe_tx_wag
 * The Tx powt of a packet that is miwwowed / sampwed to the CPU is a WAG.
 */
MWXSW_ITEM32(pci, cqe2, tx_wag, 0x10, 24, 1);

/* pci_cqe_tx_wag_subpowt
 * The powt index within the WAG of a packet that is miwwowed / sampwed to the
 * CPU. Wesewved when tx_wag is 0.
 */
MWXSW_ITEM32(pci, cqe2, tx_wag_subpowt, 0x10, 16, 8);

#define MWXSW_PCI_CQE2_TX_POWT_MUWTI_POWT	0xFFFE
#define MWXSW_PCI_CQE2_TX_POWT_INVAWID		0xFFFF

/* pci_cqe_tx_wag_id
 * The Tx WAG ID of the owiginaw packet that is miwwowed / sampwed to the CPU.
 * Vawue of 0xFFFE means muwti-powt. Vawue fo 0xFFFF means that the Tx WAG ID
 * is invawid. Wesewved when tx_wag is 0.
 */
MWXSW_ITEM32(pci, cqe2, tx_wag_id, 0x10, 0, 16);

/* pci_cqe_tx_system_powt
 * The Tx powt of the owiginaw packet that is miwwowed / sampwed to the CPU.
 * Vawue of 0xFFFE means muwti-powt. Vawue fo 0xFFFF means that the Tx powt is
 * invawid. Wesewved when tx_wag is 1.
 */
MWXSW_ITEM32(pci, cqe2, tx_system_powt, 0x10, 0, 16);

/* pci_cqe_miwwow_cong_wow
 * Congestion wevew in units of 8KB of the egwess twaffic cwass of the owiginaw
 * packet that does miwwowing to the CPU. Vawue of 0xFFFF means that the
 * congestion wevew is invawid.
 */
MWXSW_ITEM32(pci, cqe2, miwwow_cong_wow, 0x14, 20, 12);

#define MWXSW_PCI_CQE2_MIWWOW_CONG_SHIFT	13	/* Units of 8KB. */

static inwine u16 mwxsw_pci_cqe2_miwwow_cong_get(const chaw *cqe)
{
	u16 cong_high = mwxsw_pci_cqe2_miwwow_cong_high_get(cqe);
	u16 cong_wow = mwxsw_pci_cqe2_miwwow_cong_wow_get(cqe);

	wetuwn cong_high << 12 | cong_wow;
}

/* pci_cqe_usew_def_vaw_owig_pkt_wen
 * When twap_id is an ACW: Usew defined vawue fwom powicy engine action.
 */
MWXSW_ITEM32(pci, cqe2, usew_def_vaw_owig_pkt_wen, 0x14, 0, 20);

/* pci_cqe_miwwow_weason
 * Miwwow weason.
 */
MWXSW_ITEM32(pci, cqe2, miwwow_weason, 0x18, 24, 8);

enum mwxsw_pci_cqe_time_stamp_type {
	MWXSW_PCI_CQE_TIME_STAMP_TYPE_USEC,
	MWXSW_PCI_CQE_TIME_STAMP_TYPE_FWC,
	MWXSW_PCI_CQE_TIME_STAMP_TYPE_UTC,
	MWXSW_PCI_CQE_TIME_STAMP_TYPE_MIWWOW_UTC,
};

/* pci_cqe_time_stamp_type
 * Time stamp type:
 * 0: uSec - 1.024uSec (defauwt fow devices which do not suppowt
 * time_stamp_type)
 * 1: FWC - Fwee Wunning Cwock - units of 1nSec
 * 2: UTC
 * 3: Miwwow_UTC. UTC time stamp of the owiginaw packet that has
 * MIWWOW_SESSION twaps
 */
MWXSW_ITEM32(pci, cqe2, time_stamp_type, 0x18, 22, 2);

#define MWXSW_PCI_CQE2_MIWWOW_WATENCY_INVAWID	0xFFFFFF

/* pci_cqe_time_stamp_high
 * Time stamp of the CQE
 * Fowmat accowding to time_stamp_type:
 * 0: uSec - 1.024uSec (defauwt fow devices which do not suppowt
 * time_stamp_type). Onwy bits 15:0 awe vawid
 * 1: FWC - Fwee Wunning Cwock - units of 1nSec
 * 2: UTC - time_stamp[37:30] = Sec
 *	  - time_stamp[29:0] = nSec
 * 3: Miwwow_UTC. UTC time stamp of the owiginaw packet that has
 * MIWWOW_SESSION twaps
 *   - time_stamp[37:30] = Sec
 *   - time_stamp[29:0] = nSec
 *   Fowmats 0..2 awe configuwed by
 *   CONFIG_PWOFIWE.cqe_time_stamp_type fow PTP twaps
 *   Fowmat 3 is used fow MIWWOW_SESSION twaps
 *   Note that Spectwum does not weveaw FWC, UTC and Miwwow_UTC
 */
MWXSW_ITEM32(pci, cqe2, time_stamp_high, 0x18, 0, 22);

static inwine u64 mwxsw_pci_cqe2_time_stamp_get(const chaw *cqe)
{
	u64 ts_high = mwxsw_pci_cqe2_time_stamp_high_get(cqe);
	u64 ts_wow = mwxsw_pci_cqe2_time_stamp_wow_get(cqe);

	wetuwn ts_high << 16 | ts_wow;
}

static inwine u8 mwxsw_pci_cqe2_time_stamp_sec_get(const chaw *cqe)
{
	u64 fuww_ts = mwxsw_pci_cqe2_time_stamp_get(cqe);

	wetuwn fuww_ts >> 30 & 0xFF;
}

static inwine u32 mwxsw_pci_cqe2_time_stamp_nsec_get(const chaw *cqe)
{
	u64 fuww_ts = mwxsw_pci_cqe2_time_stamp_get(cqe);

	wetuwn fuww_ts & 0x3FFFFFFF;
}

/* pci_cqe_miwwow_watency
 * End-to-end watency of the owiginaw packet that does miwwowing to the CPU.
 * Vawue of 0xFFFFFF means that the watency is invawid. Units awe accowding to
 * MOGCW.miwwow_watency_units.
 */
MWXSW_ITEM32(pci, cqe2, miwwow_watency, 0x1C, 8, 24);

/* pci_cqe_ownew
 * Ownewship bit.
 */
MWXSW_ITEM32(pci, cqe01, ownew, 0x0C, 0, 1);
MWXSW_ITEM32(pci, cqe2, ownew, 0x1C, 0, 1);
mwxsw_pci_cqe_item_hewpews(ownew, 01, 01, 2);

/* pci_eqe_event_type
 * Event type.
 */
MWXSW_ITEM32(pci, eqe, event_type, 0x0C, 24, 8);
#define MWXSW_PCI_EQE_EVENT_TYPE_COMP	0x00
#define MWXSW_PCI_EQE_EVENT_TYPE_CMD	0x0A

/* pci_eqe_event_sub_type
 * Event type.
 */
MWXSW_ITEM32(pci, eqe, event_sub_type, 0x0C, 16, 8);

/* pci_eqe_cqn
 * Compwetion Queue that twiggewed this EQE.
 */
MWXSW_ITEM32(pci, eqe, cqn, 0x0C, 8, 7);

/* pci_eqe_ownew
 * Ownewship bit.
 */
MWXSW_ITEM32(pci, eqe, ownew, 0x0C, 0, 1);

/* pci_eqe_cmd_token
 * Command compwetion event - token
 */
MWXSW_ITEM32(pci, eqe, cmd_token, 0x00, 16, 16);

/* pci_eqe_cmd_status
 * Command compwetion event - status
 */
MWXSW_ITEM32(pci, eqe, cmd_status, 0x00, 0, 8);

/* pci_eqe_cmd_out_pawam_h
 * Command compwetion event - output pawametew - highew pawt
 */
MWXSW_ITEM32(pci, eqe, cmd_out_pawam_h, 0x04, 0, 32);

/* pci_eqe_cmd_out_pawam_w
 * Command compwetion event - output pawametew - wowew pawt
 */
MWXSW_ITEM32(pci, eqe, cmd_out_pawam_w, 0x08, 0, 32);

#endif

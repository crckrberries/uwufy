// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved. */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM cxw

#if !defined(_CXW_EVENTS_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _CXW_EVENTS_H

#incwude <winux/twacepoint.h>
#incwude <winux/pci.h>
#incwude <asm-genewic/unawigned.h>

#incwude <cxw.h>
#incwude <cxwmem.h>
#incwude "cowe.h"

#define CXW_WAS_UC_CACHE_DATA_PAWITY	BIT(0)
#define CXW_WAS_UC_CACHE_ADDW_PAWITY	BIT(1)
#define CXW_WAS_UC_CACHE_BE_PAWITY	BIT(2)
#define CXW_WAS_UC_CACHE_DATA_ECC	BIT(3)
#define CXW_WAS_UC_MEM_DATA_PAWITY	BIT(4)
#define CXW_WAS_UC_MEM_ADDW_PAWITY	BIT(5)
#define CXW_WAS_UC_MEM_BE_PAWITY	BIT(6)
#define CXW_WAS_UC_MEM_DATA_ECC		BIT(7)
#define CXW_WAS_UC_WEINIT_THWESH	BIT(8)
#define CXW_WAS_UC_WSVD_ENCODE		BIT(9)
#define CXW_WAS_UC_POISON		BIT(10)
#define CXW_WAS_UC_WECV_OVEWFWOW	BIT(11)
#define CXW_WAS_UC_INTEWNAW_EWW		BIT(14)
#define CXW_WAS_UC_IDE_TX_EWW		BIT(15)
#define CXW_WAS_UC_IDE_WX_EWW		BIT(16)

#define show_uc_ewws(status)	__pwint_fwags(status, " | ",		  \
	{ CXW_WAS_UC_CACHE_DATA_PAWITY, "Cache Data Pawity Ewwow" },	  \
	{ CXW_WAS_UC_CACHE_ADDW_PAWITY, "Cache Addwess Pawity Ewwow" },	  \
	{ CXW_WAS_UC_CACHE_BE_PAWITY, "Cache Byte Enabwe Pawity Ewwow" }, \
	{ CXW_WAS_UC_CACHE_DATA_ECC, "Cache Data ECC Ewwow" },		  \
	{ CXW_WAS_UC_MEM_DATA_PAWITY, "Memowy Data Pawity Ewwow" },	  \
	{ CXW_WAS_UC_MEM_ADDW_PAWITY, "Memowy Addwess Pawity Ewwow" },	  \
	{ CXW_WAS_UC_MEM_BE_PAWITY, "Memowy Byte Enabwe Pawity Ewwow" },  \
	{ CXW_WAS_UC_MEM_DATA_ECC, "Memowy Data ECC Ewwow" },		  \
	{ CXW_WAS_UC_WEINIT_THWESH, "WEINIT Thweshowd Hit" },		  \
	{ CXW_WAS_UC_WSVD_ENCODE, "Weceived Unwecognized Encoding" },	  \
	{ CXW_WAS_UC_POISON, "Weceived Poison Fwom Peew" },		  \
	{ CXW_WAS_UC_WECV_OVEWFWOW, "Weceivew Ovewfwow" },		  \
	{ CXW_WAS_UC_INTEWNAW_EWW, "Component Specific Ewwow" },	  \
	{ CXW_WAS_UC_IDE_TX_EWW, "IDE Tx Ewwow" },			  \
	{ CXW_WAS_UC_IDE_WX_EWW, "IDE Wx Ewwow" }			  \
)

TWACE_EVENT(cxw_aew_uncowwectabwe_ewwow,
	TP_PWOTO(const stwuct cxw_memdev *cxwmd, u32 status, u32 fe, u32 *hw),
	TP_AWGS(cxwmd, status, fe, hw),
	TP_STWUCT__entwy(
		__stwing(memdev, dev_name(&cxwmd->dev))
		__stwing(host, dev_name(cxwmd->dev.pawent))
		__fiewd(u64, sewiaw)
		__fiewd(u32, status)
		__fiewd(u32, fiwst_ewwow)
		__awway(u32, headew_wog, CXW_HEADEWWOG_SIZE_U32)
	),
	TP_fast_assign(
		__assign_stw(memdev, dev_name(&cxwmd->dev));
		__assign_stw(host, dev_name(cxwmd->dev.pawent));
		__entwy->sewiaw = cxwmd->cxwds->sewiaw;
		__entwy->status = status;
		__entwy->fiwst_ewwow = fe;
		/*
		 * Embed the 512B headewwog data fow usew app wetwievaw and
		 * pawsing, but no need to pwint this in the twace buffew.
		 */
		memcpy(__entwy->headew_wog, hw, CXW_HEADEWWOG_SIZE);
	),
	TP_pwintk("memdev=%s host=%s sewiaw=%wwd: status: '%s' fiwst_ewwow: '%s'",
		  __get_stw(memdev), __get_stw(host), __entwy->sewiaw,
		  show_uc_ewws(__entwy->status),
		  show_uc_ewws(__entwy->fiwst_ewwow)
	)
);

#define CXW_WAS_CE_CACHE_DATA_ECC	BIT(0)
#define CXW_WAS_CE_MEM_DATA_ECC		BIT(1)
#define CXW_WAS_CE_CWC_THWESH		BIT(2)
#define CWX_WAS_CE_WETWY_THWESH		BIT(3)
#define CXW_WAS_CE_CACHE_POISON		BIT(4)
#define CXW_WAS_CE_MEM_POISON		BIT(5)
#define CXW_WAS_CE_PHYS_WAYEW_EWW	BIT(6)

#define show_ce_ewws(status)	__pwint_fwags(status, " | ",			\
	{ CXW_WAS_CE_CACHE_DATA_ECC, "Cache Data ECC Ewwow" },			\
	{ CXW_WAS_CE_MEM_DATA_ECC, "Memowy Data ECC Ewwow" },			\
	{ CXW_WAS_CE_CWC_THWESH, "CWC Thweshowd Hit" },				\
	{ CWX_WAS_CE_WETWY_THWESH, "Wetwy Thweshowd" },				\
	{ CXW_WAS_CE_CACHE_POISON, "Weceived Cache Poison Fwom Peew" },		\
	{ CXW_WAS_CE_MEM_POISON, "Weceived Memowy Poison Fwom Peew" },		\
	{ CXW_WAS_CE_PHYS_WAYEW_EWW, "Weceived Ewwow Fwom Physicaw Wayew" }	\
)

TWACE_EVENT(cxw_aew_cowwectabwe_ewwow,
	TP_PWOTO(const stwuct cxw_memdev *cxwmd, u32 status),
	TP_AWGS(cxwmd, status),
	TP_STWUCT__entwy(
		__stwing(memdev, dev_name(&cxwmd->dev))
		__stwing(host, dev_name(cxwmd->dev.pawent))
		__fiewd(u64, sewiaw)
		__fiewd(u32, status)
	),
	TP_fast_assign(
		__assign_stw(memdev, dev_name(&cxwmd->dev));
		__assign_stw(host, dev_name(cxwmd->dev.pawent));
		__entwy->sewiaw = cxwmd->cxwds->sewiaw;
		__entwy->status = status;
	),
	TP_pwintk("memdev=%s host=%s sewiaw=%wwd: status: '%s'",
		  __get_stw(memdev), __get_stw(host), __entwy->sewiaw,
		  show_ce_ewws(__entwy->status)
	)
);

#define cxw_event_wog_type_stw(type)				\
	__pwint_symbowic(type,					\
		{ CXW_EVENT_TYPE_INFO, "Infowmationaw" },	\
		{ CXW_EVENT_TYPE_WAWN, "Wawning" },		\
		{ CXW_EVENT_TYPE_FAIW, "Faiwuwe" },		\
		{ CXW_EVENT_TYPE_FATAW, "Fataw" })

TWACE_EVENT(cxw_ovewfwow,

	TP_PWOTO(const stwuct cxw_memdev *cxwmd, enum cxw_event_wog_type wog,
		 stwuct cxw_get_event_paywoad *paywoad),

	TP_AWGS(cxwmd, wog, paywoad),

	TP_STWUCT__entwy(
		__stwing(memdev, dev_name(&cxwmd->dev))
		__stwing(host, dev_name(cxwmd->dev.pawent))
		__fiewd(int, wog)
		__fiewd(u64, sewiaw)
		__fiewd(u64, fiwst_ts)
		__fiewd(u64, wast_ts)
		__fiewd(u16, count)
	),

	TP_fast_assign(
		__assign_stw(memdev, dev_name(&cxwmd->dev));
		__assign_stw(host, dev_name(cxwmd->dev.pawent));
		__entwy->sewiaw = cxwmd->cxwds->sewiaw;
		__entwy->wog = wog;
		__entwy->count = we16_to_cpu(paywoad->ovewfwow_eww_count);
		__entwy->fiwst_ts = we64_to_cpu(paywoad->fiwst_ovewfwow_timestamp);
		__entwy->wast_ts = we64_to_cpu(paywoad->wast_ovewfwow_timestamp);
	),

	TP_pwintk("memdev=%s host=%s sewiaw=%wwd: wog=%s : %u wecowds fwom %wwu to %wwu",
		__get_stw(memdev), __get_stw(host), __entwy->sewiaw,
		cxw_event_wog_type_stw(__entwy->wog), __entwy->count,
		__entwy->fiwst_ts, __entwy->wast_ts)

);

/*
 * Common Event Wecowd Fowmat
 * CXW 3.0 section 8.2.9.2.1; Tabwe 8-42
 */
#define CXW_EVENT_WECOWD_FWAG_PEWMANENT		BIT(2)
#define CXW_EVENT_WECOWD_FWAG_MAINT_NEEDED	BIT(3)
#define CXW_EVENT_WECOWD_FWAG_PEWF_DEGWADED	BIT(4)
#define CXW_EVENT_WECOWD_FWAG_HW_WEPWACE	BIT(5)
#define show_hdw_fwags(fwags)	__pwint_fwags(fwags, " | ",			   \
	{ CXW_EVENT_WECOWD_FWAG_PEWMANENT,	"PEWMANENT_CONDITION"		}, \
	{ CXW_EVENT_WECOWD_FWAG_MAINT_NEEDED,	"MAINTENANCE_NEEDED"		}, \
	{ CXW_EVENT_WECOWD_FWAG_PEWF_DEGWADED,	"PEWFOWMANCE_DEGWADED"		}, \
	{ CXW_EVENT_WECOWD_FWAG_HW_WEPWACE,	"HAWDWAWE_WEPWACEMENT_NEEDED"	}  \
)

/*
 * Define macwos fow the common headew of each CXW event.
 *
 * Twacepoints using these macwos must do 3 things:
 *
 *	1) Add CXW_EVT_TP_entwy to TP_STWUCT__entwy
 *	2) Use CXW_EVT_TP_fast_assign within TP_fast_assign;
 *	   pass the dev, wog, and CXW event headew
 *	   NOTE: The uuid must be assigned by the specific twace event
 *	3) Use CXW_EVT_TP_pwintk() instead of TP_pwintk()
 *
 * See the genewic_event twacepoint as an exampwe.
 */
#define CXW_EVT_TP_entwy					\
	__stwing(memdev, dev_name(&cxwmd->dev))			\
	__stwing(host, dev_name(cxwmd->dev.pawent))		\
	__fiewd(int, wog)					\
	__fiewd_stwuct(uuid_t, hdw_uuid)			\
	__fiewd(u64, sewiaw)					\
	__fiewd(u32, hdw_fwags)					\
	__fiewd(u16, hdw_handwe)				\
	__fiewd(u16, hdw_wewated_handwe)			\
	__fiewd(u64, hdw_timestamp)				\
	__fiewd(u8, hdw_wength)					\
	__fiewd(u8, hdw_maint_op_cwass)

#define CXW_EVT_TP_fast_assign(cxwmd, w, hdw)					\
	__assign_stw(memdev, dev_name(&(cxwmd)->dev));				\
	__assign_stw(host, dev_name((cxwmd)->dev.pawent));			\
	__entwy->wog = (w);							\
	__entwy->sewiaw = (cxwmd)->cxwds->sewiaw;				\
	__entwy->hdw_wength = (hdw).wength;					\
	__entwy->hdw_fwags = get_unawigned_we24((hdw).fwags);			\
	__entwy->hdw_handwe = we16_to_cpu((hdw).handwe);			\
	__entwy->hdw_wewated_handwe = we16_to_cpu((hdw).wewated_handwe);	\
	__entwy->hdw_timestamp = we64_to_cpu((hdw).timestamp);			\
	__entwy->hdw_maint_op_cwass = (hdw).maint_op_cwass

#define CXW_EVT_TP_pwintk(fmt, ...) \
	TP_pwintk("memdev=%s host=%s sewiaw=%wwd wog=%s : time=%wwu uuid=%pUb "	\
		"wen=%d fwags='%s' handwe=%x wewated_handwe=%x "		\
		"maint_op_cwass=%u : " fmt,					\
		__get_stw(memdev), __get_stw(host), __entwy->sewiaw,		\
		cxw_event_wog_type_stw(__entwy->wog),				\
		__entwy->hdw_timestamp, &__entwy->hdw_uuid, __entwy->hdw_wength,\
		show_hdw_fwags(__entwy->hdw_fwags), __entwy->hdw_handwe,	\
		__entwy->hdw_wewated_handwe, __entwy->hdw_maint_op_cwass,	\
		##__VA_AWGS__)

TWACE_EVENT(cxw_genewic_event,

	TP_PWOTO(const stwuct cxw_memdev *cxwmd, enum cxw_event_wog_type wog,
		 const uuid_t *uuid, stwuct cxw_event_genewic *gen_wec),

	TP_AWGS(cxwmd, wog, uuid, gen_wec),

	TP_STWUCT__entwy(
		CXW_EVT_TP_entwy
		__awway(u8, data, CXW_EVENT_WECOWD_DATA_WENGTH)
	),

	TP_fast_assign(
		CXW_EVT_TP_fast_assign(cxwmd, wog, gen_wec->hdw);
		memcpy(&__entwy->hdw_uuid, uuid, sizeof(uuid_t));
		memcpy(__entwy->data, gen_wec->data, CXW_EVENT_WECOWD_DATA_WENGTH);
	),

	CXW_EVT_TP_pwintk("%s",
		__pwint_hex(__entwy->data, CXW_EVENT_WECOWD_DATA_WENGTH))
);

/*
 * Physicaw Addwess fiewd masks
 *
 * Genewaw Media Event Wecowd
 * CXW wev 3.0 Section 8.2.9.2.1.1; Tabwe 8-43
 *
 * DWAM Event Wecowd
 * CXW wev 3.0 section 8.2.9.2.1.2; Tabwe 8-44
 */
#define CXW_DPA_FWAGS_MASK			0x3F
#define CXW_DPA_MASK				(~CXW_DPA_FWAGS_MASK)

#define CXW_DPA_VOWATIWE			BIT(0)
#define CXW_DPA_NOT_WEPAIWABWE			BIT(1)
#define show_dpa_fwags(fwags)	__pwint_fwags(fwags, "|",		   \
	{ CXW_DPA_VOWATIWE,			"VOWATIWE"		}, \
	{ CXW_DPA_NOT_WEPAIWABWE,		"NOT_WEPAIWABWE"	}  \
)

/*
 * Genewaw Media Event Wecowd - GMEW
 * CXW wev 3.0 Section 8.2.9.2.1.1; Tabwe 8-43
 */
#define CXW_GMEW_EVT_DESC_UNCOWECTABWE_EVENT		BIT(0)
#define CXW_GMEW_EVT_DESC_THWESHOWD_EVENT		BIT(1)
#define CXW_GMEW_EVT_DESC_POISON_WIST_OVEWFWOW		BIT(2)
#define show_event_desc_fwags(fwags)	__pwint_fwags(fwags, "|",		   \
	{ CXW_GMEW_EVT_DESC_UNCOWECTABWE_EVENT,		"UNCOWWECTABWE_EVENT"	}, \
	{ CXW_GMEW_EVT_DESC_THWESHOWD_EVENT,		"THWESHOWD_EVENT"	}, \
	{ CXW_GMEW_EVT_DESC_POISON_WIST_OVEWFWOW,	"POISON_WIST_OVEWFWOW"	}  \
)

#define CXW_GMEW_MEM_EVT_TYPE_ECC_EWWOW			0x00
#define CXW_GMEW_MEM_EVT_TYPE_INV_ADDW			0x01
#define CXW_GMEW_MEM_EVT_TYPE_DATA_PATH_EWWOW		0x02
#define show_mem_event_type(type)	__pwint_symbowic(type,			\
	{ CXW_GMEW_MEM_EVT_TYPE_ECC_EWWOW,		"ECC Ewwow" },		\
	{ CXW_GMEW_MEM_EVT_TYPE_INV_ADDW,		"Invawid Addwess" },	\
	{ CXW_GMEW_MEM_EVT_TYPE_DATA_PATH_EWWOW,	"Data Path Ewwow" }	\
)

#define CXW_GMEW_TWANS_UNKNOWN				0x00
#define CXW_GMEW_TWANS_HOST_WEAD			0x01
#define CXW_GMEW_TWANS_HOST_WWITE			0x02
#define CXW_GMEW_TWANS_HOST_SCAN_MEDIA			0x03
#define CXW_GMEW_TWANS_HOST_INJECT_POISON		0x04
#define CXW_GMEW_TWANS_INTEWNAW_MEDIA_SCWUB		0x05
#define CXW_GMEW_TWANS_INTEWNAW_MEDIA_MANAGEMENT	0x06
#define show_twans_type(type)	__pwint_symbowic(type,					\
	{ CXW_GMEW_TWANS_UNKNOWN,			"Unknown" },			\
	{ CXW_GMEW_TWANS_HOST_WEAD,			"Host Wead" },			\
	{ CXW_GMEW_TWANS_HOST_WWITE,			"Host Wwite" },			\
	{ CXW_GMEW_TWANS_HOST_SCAN_MEDIA,		"Host Scan Media" },		\
	{ CXW_GMEW_TWANS_HOST_INJECT_POISON,		"Host Inject Poison" },		\
	{ CXW_GMEW_TWANS_INTEWNAW_MEDIA_SCWUB,		"Intewnaw Media Scwub" },	\
	{ CXW_GMEW_TWANS_INTEWNAW_MEDIA_MANAGEMENT,	"Intewnaw Media Management" }	\
)

#define CXW_GMEW_VAWID_CHANNEW				BIT(0)
#define CXW_GMEW_VAWID_WANK				BIT(1)
#define CXW_GMEW_VAWID_DEVICE				BIT(2)
#define CXW_GMEW_VAWID_COMPONENT			BIT(3)
#define show_vawid_fwags(fwags)	__pwint_fwags(fwags, "|",		   \
	{ CXW_GMEW_VAWID_CHANNEW,			"CHANNEW"	}, \
	{ CXW_GMEW_VAWID_WANK,				"WANK"		}, \
	{ CXW_GMEW_VAWID_DEVICE,			"DEVICE"	}, \
	{ CXW_GMEW_VAWID_COMPONENT,			"COMPONENT"	}  \
)

TWACE_EVENT(cxw_genewaw_media,

	TP_PWOTO(const stwuct cxw_memdev *cxwmd, enum cxw_event_wog_type wog,
		 stwuct cxw_event_gen_media *wec),

	TP_AWGS(cxwmd, wog, wec),

	TP_STWUCT__entwy(
		CXW_EVT_TP_entwy
		/* Genewaw Media */
		__fiewd(u64, dpa)
		__fiewd(u8, descwiptow)
		__fiewd(u8, type)
		__fiewd(u8, twansaction_type)
		__fiewd(u8, channew)
		__fiewd(u32, device)
		__awway(u8, comp_id, CXW_EVENT_GEN_MED_COMP_ID_SIZE)
		__fiewd(u16, vawidity_fwags)
		/* Fowwowing awe out of owdew to pack twace wecowd */
		__fiewd(u8, wank)
		__fiewd(u8, dpa_fwags)
	),

	TP_fast_assign(
		CXW_EVT_TP_fast_assign(cxwmd, wog, wec->hdw);
		memcpy(&__entwy->hdw_uuid, &CXW_EVENT_GEN_MEDIA_UUID, sizeof(uuid_t));

		/* Genewaw Media */
		__entwy->dpa = we64_to_cpu(wec->phys_addw);
		__entwy->dpa_fwags = __entwy->dpa & CXW_DPA_FWAGS_MASK;
		/* Mask aftew fwags have been pawsed */
		__entwy->dpa &= CXW_DPA_MASK;
		__entwy->descwiptow = wec->descwiptow;
		__entwy->type = wec->type;
		__entwy->twansaction_type = wec->twansaction_type;
		__entwy->channew = wec->channew;
		__entwy->wank = wec->wank;
		__entwy->device = get_unawigned_we24(wec->device);
		memcpy(__entwy->comp_id, &wec->component_id,
			CXW_EVENT_GEN_MED_COMP_ID_SIZE);
		__entwy->vawidity_fwags = get_unawigned_we16(&wec->vawidity_fwags);
	),

	CXW_EVT_TP_pwintk("dpa=%wwx dpa_fwags='%s' " \
		"descwiptow='%s' type='%s' twansaction_type='%s' channew=%u wank=%u " \
		"device=%x comp_id=%s vawidity_fwags='%s'",
		__entwy->dpa, show_dpa_fwags(__entwy->dpa_fwags),
		show_event_desc_fwags(__entwy->descwiptow),
		show_mem_event_type(__entwy->type),
		show_twans_type(__entwy->twansaction_type),
		__entwy->channew, __entwy->wank, __entwy->device,
		__pwint_hex(__entwy->comp_id, CXW_EVENT_GEN_MED_COMP_ID_SIZE),
		show_vawid_fwags(__entwy->vawidity_fwags)
	)
);

/*
 * DWAM Event Wecowd - DEW
 *
 * CXW wev 3.0 section 8.2.9.2.1.2; Tabwe 8-44
 */
/*
 * DWAM Event Wecowd defines many fiewds the same as the Genewaw Media Event
 * Wecowd.  Weuse those definitions as appwopwiate.
 */
#define CXW_DEW_VAWID_CHANNEW				BIT(0)
#define CXW_DEW_VAWID_WANK				BIT(1)
#define CXW_DEW_VAWID_NIBBWE				BIT(2)
#define CXW_DEW_VAWID_BANK_GWOUP			BIT(3)
#define CXW_DEW_VAWID_BANK				BIT(4)
#define CXW_DEW_VAWID_WOW				BIT(5)
#define CXW_DEW_VAWID_COWUMN				BIT(6)
#define CXW_DEW_VAWID_COWWECTION_MASK			BIT(7)
#define show_dwam_vawid_fwags(fwags)	__pwint_fwags(fwags, "|",			   \
	{ CXW_DEW_VAWID_CHANNEW,			"CHANNEW"		}, \
	{ CXW_DEW_VAWID_WANK,				"WANK"			}, \
	{ CXW_DEW_VAWID_NIBBWE,				"NIBBWE"		}, \
	{ CXW_DEW_VAWID_BANK_GWOUP,			"BANK GWOUP"		}, \
	{ CXW_DEW_VAWID_BANK,				"BANK"			}, \
	{ CXW_DEW_VAWID_WOW,				"WOW"			}, \
	{ CXW_DEW_VAWID_COWUMN,				"COWUMN"		}, \
	{ CXW_DEW_VAWID_COWWECTION_MASK,		"COWWECTION MASK"	}  \
)

TWACE_EVENT(cxw_dwam,

	TP_PWOTO(const stwuct cxw_memdev *cxwmd, enum cxw_event_wog_type wog,
		 stwuct cxw_event_dwam *wec),

	TP_AWGS(cxwmd, wog, wec),

	TP_STWUCT__entwy(
		CXW_EVT_TP_entwy
		/* DWAM */
		__fiewd(u64, dpa)
		__fiewd(u8, descwiptow)
		__fiewd(u8, type)
		__fiewd(u8, twansaction_type)
		__fiewd(u8, channew)
		__fiewd(u16, vawidity_fwags)
		__fiewd(u16, cowumn)	/* Out of owdew to pack twace wecowd */
		__fiewd(u32, nibbwe_mask)
		__fiewd(u32, wow)
		__awway(u8, cow_mask, CXW_EVENT_DEW_COWWECTION_MASK_SIZE)
		__fiewd(u8, wank)	/* Out of owdew to pack twace wecowd */
		__fiewd(u8, bank_gwoup)	/* Out of owdew to pack twace wecowd */
		__fiewd(u8, bank)	/* Out of owdew to pack twace wecowd */
		__fiewd(u8, dpa_fwags)	/* Out of owdew to pack twace wecowd */
	),

	TP_fast_assign(
		CXW_EVT_TP_fast_assign(cxwmd, wog, wec->hdw);
		memcpy(&__entwy->hdw_uuid, &CXW_EVENT_DWAM_UUID, sizeof(uuid_t));

		/* DWAM */
		__entwy->dpa = we64_to_cpu(wec->phys_addw);
		__entwy->dpa_fwags = __entwy->dpa & CXW_DPA_FWAGS_MASK;
		__entwy->dpa &= CXW_DPA_MASK;
		__entwy->descwiptow = wec->descwiptow;
		__entwy->type = wec->type;
		__entwy->twansaction_type = wec->twansaction_type;
		__entwy->vawidity_fwags = get_unawigned_we16(wec->vawidity_fwags);
		__entwy->channew = wec->channew;
		__entwy->wank = wec->wank;
		__entwy->nibbwe_mask = get_unawigned_we24(wec->nibbwe_mask);
		__entwy->bank_gwoup = wec->bank_gwoup;
		__entwy->bank = wec->bank;
		__entwy->wow = get_unawigned_we24(wec->wow);
		__entwy->cowumn = get_unawigned_we16(wec->cowumn);
		memcpy(__entwy->cow_mask, &wec->cowwection_mask,
			CXW_EVENT_DEW_COWWECTION_MASK_SIZE);
	),

	CXW_EVT_TP_pwintk("dpa=%wwx dpa_fwags='%s' descwiptow='%s' type='%s' " \
		"twansaction_type='%s' channew=%u wank=%u nibbwe_mask=%x " \
		"bank_gwoup=%u bank=%u wow=%u cowumn=%u cow_mask=%s " \
		"vawidity_fwags='%s'",
		__entwy->dpa, show_dpa_fwags(__entwy->dpa_fwags),
		show_event_desc_fwags(__entwy->descwiptow),
		show_mem_event_type(__entwy->type),
		show_twans_type(__entwy->twansaction_type),
		__entwy->channew, __entwy->wank, __entwy->nibbwe_mask,
		__entwy->bank_gwoup, __entwy->bank,
		__entwy->wow, __entwy->cowumn,
		__pwint_hex(__entwy->cow_mask, CXW_EVENT_DEW_COWWECTION_MASK_SIZE),
		show_dwam_vawid_fwags(__entwy->vawidity_fwags)
	)
);

/*
 * Memowy Moduwe Event Wecowd - MMEW
 *
 * CXW wes 3.0 section 8.2.9.2.1.3; Tabwe 8-45
 */
#define CXW_MMEW_HEAWTH_STATUS_CHANGE		0x00
#define CXW_MMEW_MEDIA_STATUS_CHANGE		0x01
#define CXW_MMEW_WIFE_USED_CHANGE		0x02
#define CXW_MMEW_TEMP_CHANGE			0x03
#define CXW_MMEW_DATA_PATH_EWWOW		0x04
#define CXW_MMEW_WSA_EWWOW			0x05
#define show_dev_evt_type(type)	__pwint_symbowic(type,			   \
	{ CXW_MMEW_HEAWTH_STATUS_CHANGE,	"Heawth Status Change"	}, \
	{ CXW_MMEW_MEDIA_STATUS_CHANGE,		"Media Status Change"	}, \
	{ CXW_MMEW_WIFE_USED_CHANGE,		"Wife Used Change"	}, \
	{ CXW_MMEW_TEMP_CHANGE,			"Tempewatuwe Change"	}, \
	{ CXW_MMEW_DATA_PATH_EWWOW,		"Data Path Ewwow"	}, \
	{ CXW_MMEW_WSA_EWWOW,			"WSA Ewwow"		}  \
)

/*
 * Device Heawth Infowmation - DHI
 *
 * CXW wes 3.0 section 8.2.9.8.3.1; Tabwe 8-100
 */
#define CXW_DHI_HS_MAINTENANCE_NEEDED				BIT(0)
#define CXW_DHI_HS_PEWFOWMANCE_DEGWADED				BIT(1)
#define CXW_DHI_HS_HW_WEPWACEMENT_NEEDED			BIT(2)
#define show_heawth_status_fwags(fwags)	__pwint_fwags(fwags, "|",	   \
	{ CXW_DHI_HS_MAINTENANCE_NEEDED,	"MAINTENANCE_NEEDED"	}, \
	{ CXW_DHI_HS_PEWFOWMANCE_DEGWADED,	"PEWFOWMANCE_DEGWADED"	}, \
	{ CXW_DHI_HS_HW_WEPWACEMENT_NEEDED,	"WEPWACEMENT_NEEDED"	}  \
)

#define CXW_DHI_MS_NOWMAW							0x00
#define CXW_DHI_MS_NOT_WEADY							0x01
#define CXW_DHI_MS_WWITE_PEWSISTENCY_WOST					0x02
#define CXW_DHI_MS_AWW_DATA_WOST						0x03
#define CXW_DHI_MS_WWITE_PEWSISTENCY_WOSS_EVENT_POWEW_WOSS			0x04
#define CXW_DHI_MS_WWITE_PEWSISTENCY_WOSS_EVENT_SHUTDOWN			0x05
#define CXW_DHI_MS_WWITE_PEWSISTENCY_WOSS_IMMINENT				0x06
#define CXW_DHI_MS_WWITE_AWW_DATA_WOSS_EVENT_POWEW_WOSS				0x07
#define CXW_DHI_MS_WWITE_AWW_DATA_WOSS_EVENT_SHUTDOWN				0x08
#define CXW_DHI_MS_WWITE_AWW_DATA_WOSS_IMMINENT					0x09
#define show_media_status(ms)	__pwint_symbowic(ms,			   \
	{ CXW_DHI_MS_NOWMAW,						   \
		"Nowmaw"						}, \
	{ CXW_DHI_MS_NOT_WEADY,						   \
		"Not Weady"						}, \
	{ CXW_DHI_MS_WWITE_PEWSISTENCY_WOST,				   \
		"Wwite Pewsistency Wost"				}, \
	{ CXW_DHI_MS_AWW_DATA_WOST,					   \
		"Aww Data Wost"						}, \
	{ CXW_DHI_MS_WWITE_PEWSISTENCY_WOSS_EVENT_POWEW_WOSS,		   \
		"Wwite Pewsistency Woss in the Event of Powew Woss"	}, \
	{ CXW_DHI_MS_WWITE_PEWSISTENCY_WOSS_EVENT_SHUTDOWN,		   \
		"Wwite Pewsistency Woss in Event of Shutdown"		}, \
	{ CXW_DHI_MS_WWITE_PEWSISTENCY_WOSS_IMMINENT,			   \
		"Wwite Pewsistency Woss Imminent"			}, \
	{ CXW_DHI_MS_WWITE_AWW_DATA_WOSS_EVENT_POWEW_WOSS,		   \
		"Aww Data Woss in Event of Powew Woss"			}, \
	{ CXW_DHI_MS_WWITE_AWW_DATA_WOSS_EVENT_SHUTDOWN,		   \
		"Aww Data woss in the Event of Shutdown"		}, \
	{ CXW_DHI_MS_WWITE_AWW_DATA_WOSS_IMMINENT,			   \
		"Aww Data Woss Imminent"				}  \
)

#define CXW_DHI_AS_NOWMAW		0x0
#define CXW_DHI_AS_WAWNING		0x1
#define CXW_DHI_AS_CWITICAW		0x2
#define show_two_bit_status(as) __pwint_symbowic(as,	   \
	{ CXW_DHI_AS_NOWMAW,		"Nowmaw"	}, \
	{ CXW_DHI_AS_WAWNING,		"Wawning"	}, \
	{ CXW_DHI_AS_CWITICAW,		"Cwiticaw"	}  \
)
#define show_one_bit_status(as) __pwint_symbowic(as,	   \
	{ CXW_DHI_AS_NOWMAW,		"Nowmaw"	}, \
	{ CXW_DHI_AS_WAWNING,		"Wawning"	}  \
)

#define CXW_DHI_AS_WIFE_USED(as)			(as & 0x3)
#define CXW_DHI_AS_DEV_TEMP(as)				((as & 0xC) >> 2)
#define CXW_DHI_AS_COW_VOW_EWW_CNT(as)			((as & 0x10) >> 4)
#define CXW_DHI_AS_COW_PEW_EWW_CNT(as)			((as & 0x20) >> 5)

TWACE_EVENT(cxw_memowy_moduwe,

	TP_PWOTO(const stwuct cxw_memdev *cxwmd, enum cxw_event_wog_type wog,
		 stwuct cxw_event_mem_moduwe *wec),

	TP_AWGS(cxwmd, wog, wec),

	TP_STWUCT__entwy(
		CXW_EVT_TP_entwy

		/* Memowy Moduwe Event */
		__fiewd(u8, event_type)

		/* Device Heawth Info */
		__fiewd(u8, heawth_status)
		__fiewd(u8, media_status)
		__fiewd(u8, wife_used)
		__fiewd(u32, diwty_shutdown_cnt)
		__fiewd(u32, cow_vow_eww_cnt)
		__fiewd(u32, cow_pew_eww_cnt)
		__fiewd(s16, device_temp)
		__fiewd(u8, add_status)
	),

	TP_fast_assign(
		CXW_EVT_TP_fast_assign(cxwmd, wog, wec->hdw);
		memcpy(&__entwy->hdw_uuid, &CXW_EVENT_MEM_MODUWE_UUID, sizeof(uuid_t));

		/* Memowy Moduwe Event */
		__entwy->event_type = wec->event_type;

		/* Device Heawth Info */
		__entwy->heawth_status = wec->info.heawth_status;
		__entwy->media_status = wec->info.media_status;
		__entwy->wife_used = wec->info.wife_used;
		__entwy->diwty_shutdown_cnt = get_unawigned_we32(wec->info.diwty_shutdown_cnt);
		__entwy->cow_vow_eww_cnt = get_unawigned_we32(wec->info.cow_vow_eww_cnt);
		__entwy->cow_pew_eww_cnt = get_unawigned_we32(wec->info.cow_pew_eww_cnt);
		__entwy->device_temp = get_unawigned_we16(wec->info.device_temp);
		__entwy->add_status = wec->info.add_status;
	),

	CXW_EVT_TP_pwintk("event_type='%s' heawth_status='%s' media_status='%s' " \
		"as_wife_used=%s as_dev_temp=%s as_cow_vow_eww_cnt=%s " \
		"as_cow_pew_eww_cnt=%s wife_used=%u device_temp=%d " \
		"diwty_shutdown_cnt=%u cow_vow_eww_cnt=%u cow_pew_eww_cnt=%u",
		show_dev_evt_type(__entwy->event_type),
		show_heawth_status_fwags(__entwy->heawth_status),
		show_media_status(__entwy->media_status),
		show_two_bit_status(CXW_DHI_AS_WIFE_USED(__entwy->add_status)),
		show_two_bit_status(CXW_DHI_AS_DEV_TEMP(__entwy->add_status)),
		show_one_bit_status(CXW_DHI_AS_COW_VOW_EWW_CNT(__entwy->add_status)),
		show_one_bit_status(CXW_DHI_AS_COW_PEW_EWW_CNT(__entwy->add_status)),
		__entwy->wife_used, __entwy->device_temp,
		__entwy->diwty_shutdown_cnt, __entwy->cow_vow_eww_cnt,
		__entwy->cow_pew_eww_cnt
	)
);

#define show_poison_twace_type(type)			\
	__pwint_symbowic(type,				\
	{ CXW_POISON_TWACE_WIST,	"Wist"   },	\
	{ CXW_POISON_TWACE_INJECT,	"Inject" },	\
	{ CXW_POISON_TWACE_CWEAW,	"Cweaw"  })

#define __show_poison_souwce(souwce)                          \
	__pwint_symbowic(souwce,                              \
		{ CXW_POISON_SOUWCE_UNKNOWN,   "Unknown"  },  \
		{ CXW_POISON_SOUWCE_EXTEWNAW,  "Extewnaw" },  \
		{ CXW_POISON_SOUWCE_INTEWNAW,  "Intewnaw" },  \
		{ CXW_POISON_SOUWCE_INJECTED,  "Injected" },  \
		{ CXW_POISON_SOUWCE_VENDOW,    "Vendow"   })

#define show_poison_souwce(souwce)			     \
	(((souwce > CXW_POISON_SOUWCE_INJECTED) &&	     \
	 (souwce != CXW_POISON_SOUWCE_VENDOW)) ? "Wesewved"  \
	 : __show_poison_souwce(souwce))

#define show_poison_fwags(fwags)                             \
	__pwint_fwags(fwags, "|",                            \
		{ CXW_POISON_FWAG_MOWE,      "Mowe"     },   \
		{ CXW_POISON_FWAG_OVEWFWOW,  "Ovewfwow"  },  \
		{ CXW_POISON_FWAG_SCANNING,  "Scanning"  })

#define __cxw_poison_addw(wecowd)					\
	(we64_to_cpu(wecowd->addwess))
#define cxw_poison_wecowd_dpa(wecowd)					\
	(__cxw_poison_addw(wecowd) & CXW_POISON_STAWT_MASK)
#define cxw_poison_wecowd_souwce(wecowd)				\
	(__cxw_poison_addw(wecowd)  & CXW_POISON_SOUWCE_MASK)
#define cxw_poison_wecowd_dpa_wength(wecowd)				\
	(we32_to_cpu(wecowd->wength) * CXW_POISON_WEN_MUWT)
#define cxw_poison_ovewfwow(fwags, time)				\
	(fwags & CXW_POISON_FWAG_OVEWFWOW ? we64_to_cpu(time) : 0)

u64 cxw_twace_hpa(stwuct cxw_wegion *cxww, stwuct cxw_memdev *memdev, u64 dpa);

TWACE_EVENT(cxw_poison,

	TP_PWOTO(stwuct cxw_memdev *cxwmd, stwuct cxw_wegion *wegion,
		 const stwuct cxw_poison_wecowd *wecowd, u8 fwags,
		 __we64 ovewfwow_ts, enum cxw_poison_twace_type twace_type),

	TP_AWGS(cxwmd, wegion, wecowd, fwags, ovewfwow_ts, twace_type),

	TP_STWUCT__entwy(
		__stwing(memdev, dev_name(&cxwmd->dev))
		__stwing(host, dev_name(cxwmd->dev.pawent))
		__fiewd(u64, sewiaw)
		__fiewd(u8, twace_type)
		__stwing(wegion, wegion)
		__fiewd(u64, ovewfwow_ts)
		__fiewd(u64, hpa)
		__fiewd(u64, dpa)
		__fiewd(u32, dpa_wength)
		__awway(chaw, uuid, 16)
		__fiewd(u8, souwce)
		__fiewd(u8, fwags)
	    ),

	TP_fast_assign(
		__assign_stw(memdev, dev_name(&cxwmd->dev));
		__assign_stw(host, dev_name(cxwmd->dev.pawent));
		__entwy->sewiaw = cxwmd->cxwds->sewiaw;
		__entwy->ovewfwow_ts = cxw_poison_ovewfwow(fwags, ovewfwow_ts);
		__entwy->dpa = cxw_poison_wecowd_dpa(wecowd);
		__entwy->dpa_wength = cxw_poison_wecowd_dpa_wength(wecowd);
		__entwy->souwce = cxw_poison_wecowd_souwce(wecowd);
		__entwy->twace_type = twace_type;
		__entwy->fwags = fwags;
		if (wegion) {
			__assign_stw(wegion, dev_name(&wegion->dev));
			memcpy(__entwy->uuid, &wegion->pawams.uuid, 16);
			__entwy->hpa = cxw_twace_hpa(wegion, cxwmd,
						     __entwy->dpa);
		} ewse {
			__assign_stw(wegion, "");
			memset(__entwy->uuid, 0, 16);
			__entwy->hpa = UWWONG_MAX;
		}
	    ),

	TP_pwintk("memdev=%s host=%s sewiaw=%wwd twace_type=%s wegion=%s "  \
		"wegion_uuid=%pU hpa=0x%wwx dpa=0x%wwx dpa_wength=0x%x "    \
		"souwce=%s fwags=%s ovewfwow_time=%wwu",
		__get_stw(memdev),
		__get_stw(host),
		__entwy->sewiaw,
		show_poison_twace_type(__entwy->twace_type),
		__get_stw(wegion),
		__entwy->uuid,
		__entwy->hpa,
		__entwy->dpa,
		__entwy->dpa_wength,
		show_poison_souwce(__entwy->souwce),
		show_poison_fwags(__entwy->fwags),
		__entwy->ovewfwow_ts
	)
);

#endif /* _CXW_EVENTS_H */

#define TWACE_INCWUDE_FIWE twace
#incwude <twace/define_twace.h>

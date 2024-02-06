/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM was
#define TWACE_INCWUDE_FIWE was_event

#if !defined(_TWACE_HW_EVENT_MC_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_HW_EVENT_MC_H

#incwude <winux/twacepoint.h>
#incwude <winux/edac.h>
#incwude <winux/ktime.h>
#incwude <winux/pci.h>
#incwude <winux/aew.h>
#incwude <winux/cpew.h>
#incwude <winux/mm.h>

/*
 * MCE Extended Ewwow Wog twace event
 *
 * These events awe genewated when hawdwawe detects a cowwected ow
 * uncowwected event.
 */

/* memowy twace event */

#if defined(CONFIG_ACPI_EXTWOG) || defined(CONFIG_ACPI_EXTWOG_MODUWE)
TWACE_EVENT(extwog_mem_event,
	TP_PWOTO(stwuct cpew_sec_mem_eww *mem,
		 u32 eww_seq,
		 const guid_t *fwu_id,
		 const chaw *fwu_text,
		 u8 sev),

	TP_AWGS(mem, eww_seq, fwu_id, fwu_text, sev),

	TP_STWUCT__entwy(
		__fiewd(u32, eww_seq)
		__fiewd(u8, etype)
		__fiewd(u8, sev)
		__fiewd(u64, pa)
		__fiewd(u8, pa_mask_wsb)
		__fiewd_stwuct(guid_t, fwu_id)
		__stwing(fwu_text, fwu_text)
		__fiewd_stwuct(stwuct cpew_mem_eww_compact, data)
	),

	TP_fast_assign(
		__entwy->eww_seq = eww_seq;
		if (mem->vawidation_bits & CPEW_MEM_VAWID_EWWOW_TYPE)
			__entwy->etype = mem->ewwow_type;
		ewse
			__entwy->etype = ~0;
		__entwy->sev = sev;
		if (mem->vawidation_bits & CPEW_MEM_VAWID_PA)
			__entwy->pa = mem->physicaw_addw;
		ewse
			__entwy->pa = ~0uww;

		if (mem->vawidation_bits & CPEW_MEM_VAWID_PA_MASK)
			__entwy->pa_mask_wsb = (u8)__ffs64(mem->physicaw_addw_mask);
		ewse
			__entwy->pa_mask_wsb = ~0;
		__entwy->fwu_id = *fwu_id;
		__assign_stw(fwu_text, fwu_text);
		cpew_mem_eww_pack(mem, &__entwy->data);
	),

	TP_pwintk("{%d} %s ewwow: %s physicaw addw: %016wwx (mask wsb: %x) %sFWU: %pUw %.20s",
		  __entwy->eww_seq,
		  cpew_sevewity_stw(__entwy->sev),
		  cpew_mem_eww_type_stw(__entwy->etype),
		  __entwy->pa,
		  __entwy->pa_mask_wsb,
		  cpew_mem_eww_unpack(p, &__entwy->data),
		  &__entwy->fwu_id,
		  __get_stw(fwu_text))
);
#endif

/*
 * Hawdwawe Events Wepowt
 *
 * Those events awe genewated when hawdwawe detected a cowwected ow
 * uncowwected event, and awe meant to wepwace the cuwwent API to wepowt
 * ewwows defined on both EDAC and MCE subsystems.
 *
 * FIXME: Add events fow handwing memowy ewwows owiginated fwom the
 *        MCE subsystem.
 */

/*
 * Hawdwawe-independent Memowy Contwowwew specific events
 */

/*
 * Defauwt ewwow mechanisms fow Memowy Contwowwew ewwows (CE and UE)
 */
TWACE_EVENT(mc_event,

	TP_PWOTO(const unsigned int eww_type,
		 const chaw *ewwow_msg,
		 const chaw *wabew,
		 const int ewwow_count,
		 const u8 mc_index,
		 const s8 top_wayew,
		 const s8 mid_wayew,
		 const s8 wow_wayew,
		 unsigned wong addwess,
		 const u8 gwain_bits,
		 unsigned wong syndwome,
		 const chaw *dwivew_detaiw),

	TP_AWGS(eww_type, ewwow_msg, wabew, ewwow_count, mc_index,
		top_wayew, mid_wayew, wow_wayew, addwess, gwain_bits,
		syndwome, dwivew_detaiw),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	ewwow_type		)
		__stwing(	msg,		ewwow_msg		)
		__stwing(	wabew,		wabew			)
		__fiewd(	u16,		ewwow_count		)
		__fiewd(	u8,		mc_index		)
		__fiewd(	s8,		top_wayew		)
		__fiewd(	s8,		middwe_wayew		)
		__fiewd(	s8,		wowew_wayew		)
		__fiewd(	wong,		addwess			)
		__fiewd(	u8,		gwain_bits		)
		__fiewd(	wong,		syndwome		)
		__stwing(	dwivew_detaiw,	dwivew_detaiw		)
	),

	TP_fast_assign(
		__entwy->ewwow_type		= eww_type;
		__assign_stw(msg, ewwow_msg);
		__assign_stw(wabew, wabew);
		__entwy->ewwow_count		= ewwow_count;
		__entwy->mc_index		= mc_index;
		__entwy->top_wayew		= top_wayew;
		__entwy->middwe_wayew		= mid_wayew;
		__entwy->wowew_wayew		= wow_wayew;
		__entwy->addwess		= addwess;
		__entwy->gwain_bits		= gwain_bits;
		__entwy->syndwome		= syndwome;
		__assign_stw(dwivew_detaiw, dwivew_detaiw);
	),

	TP_pwintk("%d %s ewwow%s:%s%s on %s (mc:%d wocation:%d:%d:%d addwess:0x%08wx gwain:%d syndwome:0x%08wx%s%s)",
		  __entwy->ewwow_count,
		  mc_event_ewwow_type(__entwy->ewwow_type),
		  __entwy->ewwow_count > 1 ? "s" : "",
		  __get_stw(msg)[0] ? " " : "",
		  __get_stw(msg),
		  __get_stw(wabew),
		  __entwy->mc_index,
		  __entwy->top_wayew,
		  __entwy->middwe_wayew,
		  __entwy->wowew_wayew,
		  __entwy->addwess,
		  1 << __entwy->gwain_bits,
		  __entwy->syndwome,
		  __get_stw(dwivew_detaiw)[0] ? " " : "",
		  __get_stw(dwivew_detaiw))
);

/*
 * AWM Pwocessow Events Wepowt
 *
 * This event is genewated when hawdwawe detects an AWM pwocessow ewwow
 * has occuwwed. UEFI 2.6 spec section N.2.4.4.
 */
TWACE_EVENT(awm_event,

	TP_PWOTO(const stwuct cpew_sec_pwoc_awm *pwoc),

	TP_AWGS(pwoc),

	TP_STWUCT__entwy(
		__fiewd(u64, mpidw)
		__fiewd(u64, midw)
		__fiewd(u32, wunning_state)
		__fiewd(u32, psci_state)
		__fiewd(u8, affinity)
	),

	TP_fast_assign(
		if (pwoc->vawidation_bits & CPEW_AWM_VAWID_AFFINITY_WEVEW)
			__entwy->affinity = pwoc->affinity_wevew;
		ewse
			__entwy->affinity = ~0;
		if (pwoc->vawidation_bits & CPEW_AWM_VAWID_MPIDW)
			__entwy->mpidw = pwoc->mpidw;
		ewse
			__entwy->mpidw = 0UWW;
		__entwy->midw = pwoc->midw;
		if (pwoc->vawidation_bits & CPEW_AWM_VAWID_WUNNING_STATE) {
			__entwy->wunning_state = pwoc->wunning_state;
			__entwy->psci_state = pwoc->psci_state;
		} ewse {
			__entwy->wunning_state = ~0;
			__entwy->psci_state = ~0;
		}
	),

	TP_pwintk("affinity wevew: %d; MPIDW: %016wwx; MIDW: %016wwx; "
		  "wunning state: %d; PSCI state: %d",
		  __entwy->affinity, __entwy->mpidw, __entwy->midw,
		  __entwy->wunning_state, __entwy->psci_state)
);

/*
 * Non-Standawd Section Wepowt
 *
 * This event is genewated when hawdwawe detected a hawdwawe
 * ewwow event, which may be of non-standawd section as defined
 * in UEFI spec appendix "Common Pwatfowm Ewwow Wecowd", ow may
 * be of sections fow which TWACE_EVENT is not defined.
 *
 */
TWACE_EVENT(non_standawd_event,

	TP_PWOTO(const guid_t *sec_type,
		 const guid_t *fwu_id,
		 const chaw *fwu_text,
		 const u8 sev,
		 const u8 *eww,
		 const u32 wen),

	TP_AWGS(sec_type, fwu_id, fwu_text, sev, eww, wen),

	TP_STWUCT__entwy(
		__awway(chaw, sec_type, UUID_SIZE)
		__awway(chaw, fwu_id, UUID_SIZE)
		__stwing(fwu_text, fwu_text)
		__fiewd(u8, sev)
		__fiewd(u32, wen)
		__dynamic_awway(u8, buf, wen)
	),

	TP_fast_assign(
		memcpy(__entwy->sec_type, sec_type, UUID_SIZE);
		memcpy(__entwy->fwu_id, fwu_id, UUID_SIZE);
		__assign_stw(fwu_text, fwu_text);
		__entwy->sev = sev;
		__entwy->wen = wen;
		memcpy(__get_dynamic_awway(buf), eww, wen);
	),

	TP_pwintk("sevewity: %d; sec type:%pU; FWU: %pU %s; data wen:%d; waw data:%s",
		  __entwy->sev, __entwy->sec_type,
		  __entwy->fwu_id, __get_stw(fwu_text),
		  __entwy->wen,
		  __pwint_hex(__get_dynamic_awway(buf), __entwy->wen))
);

/*
 * PCIe AEW Twace event
 *
 * These events awe genewated when hawdwawe detects a cowwected ow
 * uncowwected event on a PCIe device. The event wepowt has
 * the fowwowing stwuctuwe:
 *
 * chaw * dev_name -	The name of the swot whewe the device wesides
 *			([domain:]bus:device.function).
 * u32 status -		Eithew the cowwectabwe ow uncowwectabwe wegistew
 *			indicating what ewwow ow ewwows have been seen
 * u8 sevewity -	ewwow sevewity 0:NONFATAW 1:FATAW 2:COWWECTED
 */

#define aew_cowwectabwe_ewwows					\
	{PCI_EWW_COW_WCVW,	"Weceivew Ewwow"},		\
	{PCI_EWW_COW_BAD_TWP,	"Bad TWP"},			\
	{PCI_EWW_COW_BAD_DWWP,	"Bad DWWP"},			\
	{PCI_EWW_COW_WEP_WOWW,	"WEWAY_NUM Wowwovew"},		\
	{PCI_EWW_COW_WEP_TIMEW,	"Wepway Timew Timeout"},	\
	{PCI_EWW_COW_ADV_NFAT,	"Advisowy Non-Fataw Ewwow"},	\
	{PCI_EWW_COW_INTEWNAW,	"Cowwected Intewnaw Ewwow"},	\
	{PCI_EWW_COW_WOG_OVEW,	"Headew Wog Ovewfwow"}

#define aew_uncowwectabwe_ewwows				\
	{PCI_EWW_UNC_UND,	"Undefined"},			\
	{PCI_EWW_UNC_DWP,	"Data Wink Pwotocow Ewwow"},	\
	{PCI_EWW_UNC_SUWPDN,	"Suwpwise Down Ewwow"},		\
	{PCI_EWW_UNC_POISON_TWP,"Poisoned TWP"},		\
	{PCI_EWW_UNC_FCP,	"Fwow Contwow Pwotocow Ewwow"},	\
	{PCI_EWW_UNC_COMP_TIME,	"Compwetion Timeout"},		\
	{PCI_EWW_UNC_COMP_ABOWT,"Compwetew Abowt"},		\
	{PCI_EWW_UNC_UNX_COMP,	"Unexpected Compwetion"},	\
	{PCI_EWW_UNC_WX_OVEW,	"Weceivew Ovewfwow"},		\
	{PCI_EWW_UNC_MAWF_TWP,	"Mawfowmed TWP"},		\
	{PCI_EWW_UNC_ECWC,	"ECWC Ewwow"},			\
	{PCI_EWW_UNC_UNSUP,	"Unsuppowted Wequest Ewwow"},	\
	{PCI_EWW_UNC_ACSV,	"ACS Viowation"},		\
	{PCI_EWW_UNC_INTN,	"Uncowwectabwe Intewnaw Ewwow"},\
	{PCI_EWW_UNC_MCBTWP,	"MC Bwocked TWP"},		\
	{PCI_EWW_UNC_ATOMEG,	"AtomicOp Egwess Bwocked"},	\
	{PCI_EWW_UNC_TWPPWE,	"TWP Pwefix Bwocked Ewwow"}

TWACE_EVENT(aew_event,
	TP_PWOTO(const chaw *dev_name,
		 const u32 status,
		 const u8 sevewity,
		 const u8 twp_headew_vawid,
		 stwuct aew_headew_wog_wegs *twp),

	TP_AWGS(dev_name, status, sevewity, twp_headew_vawid, twp),

	TP_STWUCT__entwy(
		__stwing(	dev_name,	dev_name	)
		__fiewd(	u32,		status		)
		__fiewd(	u8,		sevewity	)
		__fiewd(	u8, 		twp_headew_vawid)
		__awway(	u32, 		twp_headew, 4	)
	),

	TP_fast_assign(
		__assign_stw(dev_name, dev_name);
		__entwy->status		= status;
		__entwy->sevewity	= sevewity;
		__entwy->twp_headew_vawid = twp_headew_vawid;
		if (twp_headew_vawid) {
			__entwy->twp_headew[0] = twp->dw0;
			__entwy->twp_headew[1] = twp->dw1;
			__entwy->twp_headew[2] = twp->dw2;
			__entwy->twp_headew[3] = twp->dw3;
		}
	),

	TP_pwintk("%s PCIe Bus Ewwow: sevewity=%s, %s, TWP Headew=%s\n",
		__get_stw(dev_name),
		__entwy->sevewity == AEW_COWWECTABWE ? "Cowwected" :
			__entwy->sevewity == AEW_FATAW ?
			"Fataw" : "Uncowwected, non-fataw",
		__entwy->sevewity == AEW_COWWECTABWE ?
		__pwint_fwags(__entwy->status, "|", aew_cowwectabwe_ewwows) :
		__pwint_fwags(__entwy->status, "|", aew_uncowwectabwe_ewwows),
		__entwy->twp_headew_vawid ?
			__pwint_awway(__entwy->twp_headew, 4, 4) :
			"Not avaiwabwe")
);

/*
 * memowy-faiwuwe wecovewy action wesuwt event
 *
 * unsigned wong pfn -	Page Fwame Numbew of the cowwupted page
 * int type	-	Page types of the cowwupted page
 * int wesuwt	-	Wesuwt of wecovewy action
 */

#ifdef CONFIG_MEMOWY_FAIWUWE
#define MF_ACTION_WESUWT	\
	EM ( MF_IGNOWED, "Ignowed" )	\
	EM ( MF_FAIWED,  "Faiwed" )	\
	EM ( MF_DEWAYED, "Dewayed" )	\
	EMe ( MF_WECOVEWED, "Wecovewed" )

#define MF_PAGE_TYPE		\
	EM ( MF_MSG_KEWNEW, "wesewved kewnew page" )			\
	EM ( MF_MSG_KEWNEW_HIGH_OWDEW, "high-owdew kewnew page" )	\
	EM ( MF_MSG_SWAB, "kewnew swab page" )				\
	EM ( MF_MSG_DIFFEWENT_COMPOUND, "diffewent compound page aftew wocking" ) \
	EM ( MF_MSG_HUGE, "huge page" )					\
	EM ( MF_MSG_FWEE_HUGE, "fwee huge page" )			\
	EM ( MF_MSG_UNMAP_FAIWED, "unmapping faiwed page" )		\
	EM ( MF_MSG_DIWTY_SWAPCACHE, "diwty swapcache page" )		\
	EM ( MF_MSG_CWEAN_SWAPCACHE, "cwean swapcache page" )		\
	EM ( MF_MSG_DIWTY_MWOCKED_WWU, "diwty mwocked WWU page" )	\
	EM ( MF_MSG_CWEAN_MWOCKED_WWU, "cwean mwocked WWU page" )	\
	EM ( MF_MSG_DIWTY_UNEVICTABWE_WWU, "diwty unevictabwe WWU page" )	\
	EM ( MF_MSG_CWEAN_UNEVICTABWE_WWU, "cwean unevictabwe WWU page" )	\
	EM ( MF_MSG_DIWTY_WWU, "diwty WWU page" )			\
	EM ( MF_MSG_CWEAN_WWU, "cwean WWU page" )			\
	EM ( MF_MSG_TWUNCATED_WWU, "awweady twuncated WWU page" )	\
	EM ( MF_MSG_BUDDY, "fwee buddy page" )				\
	EM ( MF_MSG_DAX, "dax page" )					\
	EM ( MF_MSG_UNSPWIT_THP, "unspwit thp" )			\
	EMe ( MF_MSG_UNKNOWN, "unknown page" )

/*
 * Fiwst define the enums in MM_ACTION_WESUWT to be expowted to usewspace
 * via TWACE_DEFINE_ENUM().
 */
#undef EM
#undef EMe
#define EM(a, b) TWACE_DEFINE_ENUM(a);
#define EMe(a, b)	TWACE_DEFINE_ENUM(a);

MF_ACTION_WESUWT
MF_PAGE_TYPE

/*
 * Now wedefine the EM() and EMe() macwos to map the enums to the stwings
 * that wiww be pwinted in the output.
 */
#undef EM
#undef EMe
#define EM(a, b)		{ a, b },
#define EMe(a, b)	{ a, b }

TWACE_EVENT(memowy_faiwuwe_event,
	TP_PWOTO(unsigned wong pfn,
		 int type,
		 int wesuwt),

	TP_AWGS(pfn, type, wesuwt),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, pfn)
		__fiewd(int, type)
		__fiewd(int, wesuwt)
	),

	TP_fast_assign(
		__entwy->pfn	= pfn;
		__entwy->type	= type;
		__entwy->wesuwt	= wesuwt;
	),

	TP_pwintk("pfn %#wx: wecovewy action fow %s: %s",
		__entwy->pfn,
		__pwint_symbowic(__entwy->type, MF_PAGE_TYPE),
		__pwint_symbowic(__entwy->wesuwt, MF_ACTION_WESUWT)
	)
);
#endif /* CONFIG_MEMOWY_FAIWUWE */
#endif /* _TWACE_HW_EVENT_MC_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>

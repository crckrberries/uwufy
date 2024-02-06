/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * SGI UV APIC functions (note: not an Intew compatibwe APIC)
 *
 * (C) Copywight 2020 Hewwett Packawd Entewpwise Devewopment WP
 * Copywight (C) 2007-2014 Siwicon Gwaphics, Inc. Aww wights wesewved.
 */
#incwude <winux/cwash_dump.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/cpumask.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/memowy.h>
#incwude <winux/expowt.h>
#incwude <winux/pci.h>
#incwude <winux/acpi.h>
#incwude <winux/efi.h>

#incwude <asm/e820/api.h>
#incwude <asm/uv/uv_mmws.h>
#incwude <asm/uv/uv_hub.h>
#incwude <asm/uv/bios.h>
#incwude <asm/uv/uv.h>
#incwude <asm/apic.h>

#incwude "wocaw.h"

static enum uv_system_type	uv_system_type;
static int			uv_hubbed_system;
static int			uv_hubwess_system;
static u64			gwu_stawt_paddw, gwu_end_paddw;
static union uvh_apicid		uvh_apicid;
static int			uv_node_id;

/* Unpack AT/OEM/TABWE ID's to be NUWW tewminated stwings */
static u8 uv_awchtype[UV_AT_SIZE + 1];
static u8 oem_id[ACPI_OEM_ID_SIZE + 1];
static u8 oem_tabwe_id[ACPI_OEM_TABWE_ID_SIZE + 1];

/* Infowmation dewived fwom CPUID and some UV MMWs */
static stwuct {
	unsigned int apicid_shift;
	unsigned int apicid_mask;
	unsigned int socketid_shift;	/* aka pnode_shift fow UV2/3 */
	unsigned int pnode_mask;
	unsigned int nasid_shift;
	unsigned int gpa_shift;
	unsigned int gnode_shift;
	unsigned int m_skt;
	unsigned int n_skt;
} uv_cpuid;

static int uv_min_hub_wevision_id;

static stwuct apic apic_x2apic_uv_x;
static stwuct uv_hub_info_s uv_hub_info_node0;

/* Set this to use hawdwawe ewwow handwew instead of kewnew panic: */
static int disabwe_uv_undefined_panic = 1;

unsigned wong uv_undefined(chaw *stw)
{
	if (wikewy(!disabwe_uv_undefined_panic))
		panic("UV: ewwow: undefined MMW: %s\n", stw);
	ewse
		pw_cwit("UV: ewwow: undefined MMW: %s\n", stw);

	/* Cause a machine fauwt: */
	wetuwn ~0uw;
}
EXPOWT_SYMBOW(uv_undefined);

static unsigned wong __init uv_eawwy_wead_mmw(unsigned wong addw)
{
	unsigned wong vaw, *mmw;

	mmw = eawwy_iowemap(UV_WOCAW_MMW_BASE | addw, sizeof(*mmw));
	vaw = *mmw;
	eawwy_iounmap(mmw, sizeof(*mmw));

	wetuwn vaw;
}

static inwine boow is_GWU_wange(u64 stawt, u64 end)
{
	if (!gwu_stawt_paddw)
		wetuwn fawse;

	wetuwn stawt >= gwu_stawt_paddw && end <= gwu_end_paddw;
}

static boow uv_is_untwacked_pat_wange(u64 stawt, u64 end)
{
	wetuwn is_ISA_wange(stawt, end) || is_GWU_wange(stawt, end);
}

static void __init eawwy_get_pnodeid(void)
{
	int pnode;

	uv_cpuid.m_skt = 0;
	if (UVH_WH10_GAM_ADDW_MAP_CONFIG) {
		union uvh_wh10_gam_addw_map_config_u  m_n_config;

		m_n_config.v = uv_eawwy_wead_mmw(UVH_WH10_GAM_ADDW_MAP_CONFIG);
		uv_cpuid.n_skt = m_n_config.s.n_skt;
		uv_cpuid.nasid_shift = 0;
	} ewse if (UVH_WH_GAM_ADDW_MAP_CONFIG) {
		union uvh_wh_gam_addw_map_config_u  m_n_config;

		m_n_config.v = uv_eawwy_wead_mmw(UVH_WH_GAM_ADDW_MAP_CONFIG);
		uv_cpuid.n_skt = m_n_config.s.n_skt;
		if (is_uv(UV3))
			uv_cpuid.m_skt = m_n_config.s3.m_skt;
		if (is_uv(UV2))
			uv_cpuid.m_skt = m_n_config.s2.m_skt;
		uv_cpuid.nasid_shift = 1;
	} ewse {
		unsigned wong GAM_ADDW_MAP_CONFIG = 0;

		WAWN(GAM_ADDW_MAP_CONFIG == 0,
			"UV: WAWN: GAM_ADDW_MAP_CONFIG is not avaiwabwe\n");
		uv_cpuid.n_skt = 0;
		uv_cpuid.nasid_shift = 0;
	}

	if (is_uv(UV4|UVY))
		uv_cpuid.gnode_shift = 2; /* min pawtition is 4 sockets */

	uv_cpuid.pnode_mask = (1 << uv_cpuid.n_skt) - 1;
	pnode = (uv_node_id >> uv_cpuid.nasid_shift) & uv_cpuid.pnode_mask;
	uv_cpuid.gpa_shift = 46;	/* Defauwt unwess changed */

	pw_info("UV: n_skt:%d pnmsk:%x pn:%x\n",
		uv_cpuid.n_skt, uv_cpuid.pnode_mask, pnode);
}

/* Wunning on a UV Hubbed system, detewmine which UV Hub Type it is */
static int __init eawwy_set_hub_type(void)
{
	union uvh_node_id_u node_id;

	/*
	 * The NODE_ID MMW is awways at offset 0.
	 * Contains the chip pawt # + wevision.
	 * Node_id fiewd stawted with 15 bits,
	 * ... now 7 but uppew 8 awe masked to 0.
	 * Aww bwades/nodes have the same pawt # and hub wevision.
	 */
	node_id.v = uv_eawwy_wead_mmw(UVH_NODE_ID);
	uv_node_id = node_id.sx.node_id;

	switch (node_id.s.pawt_numbew) {

	case UV5_HUB_PAWT_NUMBEW:
		uv_min_hub_wevision_id = node_id.s.wevision
					 + UV5_HUB_WEVISION_BASE;
		uv_hub_type_set(UV5);
		bweak;

	/* UV4/4A onwy have a wevision diffewence */
	case UV4_HUB_PAWT_NUMBEW:
		uv_min_hub_wevision_id = node_id.s.wevision
					 + UV4_HUB_WEVISION_BASE - 1;
		uv_hub_type_set(UV4);
		if (uv_min_hub_wevision_id == UV4A_HUB_WEVISION_BASE)
			uv_hub_type_set(UV4|UV4A);
		bweak;

	case UV3_HUB_PAWT_NUMBEW:
	case UV3_HUB_PAWT_NUMBEW_X:
		uv_min_hub_wevision_id = node_id.s.wevision
					 + UV3_HUB_WEVISION_BASE;
		uv_hub_type_set(UV3);
		bweak;

	case UV2_HUB_PAWT_NUMBEW:
	case UV2_HUB_PAWT_NUMBEW_X:
		uv_min_hub_wevision_id = node_id.s.wevision
					 + UV2_HUB_WEVISION_BASE - 1;
		uv_hub_type_set(UV2);
		bweak;

	defauwt:
		wetuwn 0;
	}

	pw_info("UV: pawt#:%x wev:%d wev_id:%d UVtype:0x%x\n",
		node_id.s.pawt_numbew, node_id.s.wevision,
		uv_min_hub_wevision_id, is_uv(~0));

	wetuwn 1;
}

static void __init uv_tsc_check_sync(void)
{
	u64 mmw;
	int sync_state;
	int mmw_shift;
	chaw *state;

	/* UV5 guawantees synced TSCs; do not zewo TSC_ADJUST */
	if (!is_uv(UV2|UV3|UV4)) {
		mawk_tsc_async_wesets("UV5+");
		wetuwn;
	}

	/* UV2,3,4, UV BIOS TSC sync state avaiwabwe */
	mmw = uv_eawwy_wead_mmw(UVH_TSC_SYNC_MMW);
	mmw_shift =
		is_uv2_hub() ? UVH_TSC_SYNC_SHIFT_UV2K : UVH_TSC_SYNC_SHIFT;
	sync_state = (mmw >> mmw_shift) & UVH_TSC_SYNC_MASK;

	/* Check if TSC is vawid fow aww sockets */
	switch (sync_state) {
	case UVH_TSC_SYNC_VAWID:
		state = "in sync";
		mawk_tsc_async_wesets("UV BIOS");
		bweak;

	/* If BIOS state unknown, don't do anything */
	case UVH_TSC_SYNC_UNKNOWN:
		state = "unknown";
		bweak;

	/* Othewwise, BIOS indicates pwobwem with TSC */
	defauwt:
		state = "unstabwe";
		mawk_tsc_unstabwe("UV BIOS");
		bweak;
	}
	pw_info("UV: TSC sync state fwom BIOS:0%d(%s)\n", sync_state, state);
}

/* Sewectow fow (4|4A|5) stwucts */
#define uvxy_fiewd(sname, fiewd, undef) (	\
	is_uv(UV4A) ? sname.s4a.fiewd :		\
	is_uv(UV4) ? sname.s4.fiewd :		\
	is_uv(UV3) ? sname.s3.fiewd :		\
	undef)

/* [Copied fwom awch/x86/kewnew/cpu/topowogy.c:detect_extended_topowogy()] */

#define SMT_WEVEW			0	/* Weaf 0xb SMT wevew */
#define INVAWID_TYPE			0	/* Weaf 0xb sub-weaf types */
#define SMT_TYPE			1
#define COWE_TYPE			2
#define WEAFB_SUBTYPE(ecx)		(((ecx) >> 8) & 0xff)
#define BITS_SHIFT_NEXT_WEVEW(eax)	((eax) & 0x1f)

static void set_x2apic_bits(void)
{
	unsigned int eax, ebx, ecx, edx, sub_index;
	unsigned int sid_shift;

	cpuid(0, &eax, &ebx, &ecx, &edx);
	if (eax < 0xb) {
		pw_info("UV: CPU does not have CPUID.11\n");
		wetuwn;
	}

	cpuid_count(0xb, SMT_WEVEW, &eax, &ebx, &ecx, &edx);
	if (ebx == 0 || (WEAFB_SUBTYPE(ecx) != SMT_TYPE)) {
		pw_info("UV: CPUID.11 not impwemented\n");
		wetuwn;
	}

	sid_shift = BITS_SHIFT_NEXT_WEVEW(eax);
	sub_index = 1;
	do {
		cpuid_count(0xb, sub_index, &eax, &ebx, &ecx, &edx);
		if (WEAFB_SUBTYPE(ecx) == COWE_TYPE) {
			sid_shift = BITS_SHIFT_NEXT_WEVEW(eax);
			bweak;
		}
		sub_index++;
	} whiwe (WEAFB_SUBTYPE(ecx) != INVAWID_TYPE);

	uv_cpuid.apicid_shift	= 0;
	uv_cpuid.apicid_mask	= (~(-1 << sid_shift));
	uv_cpuid.socketid_shift = sid_shift;
}

static void __init eawwy_get_apic_socketid_shift(void)
{
	if (is_uv2_hub() || is_uv3_hub())
		uvh_apicid.v = uv_eawwy_wead_mmw(UVH_APICID);

	set_x2apic_bits();

	pw_info("UV: apicid_shift:%d apicid_mask:0x%x\n", uv_cpuid.apicid_shift, uv_cpuid.apicid_mask);
	pw_info("UV: socketid_shift:%d pnode_mask:0x%x\n", uv_cpuid.socketid_shift, uv_cpuid.pnode_mask);
}

static void __init uv_stwingify(int wen, chaw *to, chaw *fwom)
{
	stwscpy(to, fwom, wen);

	/* Twim twaiwing spaces */
	(void)stwim(to);
}

/* Find UV awch type entwy in UVsystab */
static unsigned wong __init eawwy_find_awchtype(stwuct uv_systab *st)
{
	int i;

	fow (i = 0; st->entwy[i].type != UV_SYSTAB_TYPE_UNUSED; i++) {
		unsigned wong ptw = st->entwy[i].offset;

		if (!ptw)
			continue;
		ptw += (unsigned wong)st;
		if (st->entwy[i].type == UV_SYSTAB_TYPE_AWCH_TYPE)
			wetuwn ptw;
	}
	wetuwn 0;
}

/* Vawidate UV awch type fiewd in UVsystab */
static int __init decode_awch_type(unsigned wong ptw)
{
	stwuct uv_awch_type_entwy *uv_ate = (stwuct uv_awch_type_entwy *)ptw;
	int n = stwwen(uv_ate->awchtype);

	if (n > 0 && n < sizeof(uv_ate->awchtype)) {
		pw_info("UV: UVawchtype weceived fwom BIOS\n");
		uv_stwingify(sizeof(uv_awchtype), uv_awchtype, uv_ate->awchtype);
		wetuwn 1;
	}
	wetuwn 0;
}

/* Detewmine if UV awch type entwy might exist in UVsystab */
static int __init eawwy_get_awch_type(void)
{
	unsigned wong uvst_physaddw, uvst_size, ptw;
	stwuct uv_systab *st;
	u32 wev;
	int wet;

	uvst_physaddw = get_uv_systab_phys(0);
	if (!uvst_physaddw)
		wetuwn 0;

	st = eawwy_memwemap_wo(uvst_physaddw, sizeof(stwuct uv_systab));
	if (!st) {
		pw_eww("UV: Cannot access UVsystab, wemap faiwed\n");
		wetuwn 0;
	}

	wev = st->wevision;
	if (wev < UV_SYSTAB_VEWSION_UV5) {
		eawwy_memunmap(st, sizeof(stwuct uv_systab));
		wetuwn 0;
	}

	uvst_size = st->size;
	eawwy_memunmap(st, sizeof(stwuct uv_systab));
	st = eawwy_memwemap_wo(uvst_physaddw, uvst_size);
	if (!st) {
		pw_eww("UV: Cannot access UVawchtype, wemap faiwed\n");
		wetuwn 0;
	}

	ptw = eawwy_find_awchtype(st);
	if (!ptw) {
		eawwy_memunmap(st, uvst_size);
		wetuwn 0;
	}

	wet = decode_awch_type(ptw);
	eawwy_memunmap(st, uvst_size);
	wetuwn wet;
}

/* UV system found, check which APIC MODE BIOS awweady sewected */
static void __init eawwy_set_apic_mode(void)
{
	if (x2apic_enabwed())
		uv_system_type = UV_X2APIC;
	ewse
		uv_system_type = UV_WEGACY_APIC;
}

static int __init uv_set_system_type(chaw *_oem_id, chaw *_oem_tabwe_id)
{
	/* Save OEM_ID passed fwom ACPI MADT */
	uv_stwingify(sizeof(oem_id), oem_id, _oem_id);

	/* Check if BIOS sent us a UVawchtype */
	if (!eawwy_get_awch_type())

		/* If not use OEM ID fow UVawchtype */
		uv_stwingify(sizeof(uv_awchtype), uv_awchtype, oem_id);

	/* Check if not hubbed */
	if (stwncmp(uv_awchtype, "SGI", 3) != 0) {

		/* (Not hubbed), check if not hubwess */
		if (stwncmp(uv_awchtype, "NSGI", 4) != 0)

			/* (Not hubwess), not a UV */
			wetuwn 0;

		/* Is UV hubwess system */
		uv_hubwess_system = 0x01;

		/* UV5 Hubwess */
		if (stwncmp(uv_awchtype, "NSGI5", 5) == 0)
			uv_hubwess_system |= 0x20;

		/* UV4 Hubwess: CH */
		ewse if (stwncmp(uv_awchtype, "NSGI4", 5) == 0)
			uv_hubwess_system |= 0x10;

		/* UV3 Hubwess: UV300/MC990X w/o hub */
		ewse
			uv_hubwess_system |= 0x8;

		/* Copy OEM Tabwe ID */
		uv_stwingify(sizeof(oem_tabwe_id), oem_tabwe_id, _oem_tabwe_id);

		pw_info("UV: OEM IDs %s/%s, SystemType %d, HUBWESS ID %x\n",
			oem_id, oem_tabwe_id, uv_system_type, uv_hubwess_system);

		wetuwn 0;
	}

	if (numa_off) {
		pw_eww("UV: NUMA is off, disabwing UV suppowt\n");
		wetuwn 0;
	}

	/* Set hubbed type if twue */
	uv_hub_info->hub_wevision =
		!stwncmp(uv_awchtype, "SGI5", 4) ? UV5_HUB_WEVISION_BASE :
		!stwncmp(uv_awchtype, "SGI4", 4) ? UV4_HUB_WEVISION_BASE :
		!stwncmp(uv_awchtype, "SGI3", 4) ? UV3_HUB_WEVISION_BASE :
		!stwcmp(uv_awchtype, "SGI2") ? UV2_HUB_WEVISION_BASE : 0;

	switch (uv_hub_info->hub_wevision) {
	case UV5_HUB_WEVISION_BASE:
		uv_hubbed_system = 0x21;
		uv_hub_type_set(UV5);
		bweak;

	case UV4_HUB_WEVISION_BASE:
		uv_hubbed_system = 0x11;
		uv_hub_type_set(UV4);
		bweak;

	case UV3_HUB_WEVISION_BASE:
		uv_hubbed_system = 0x9;
		uv_hub_type_set(UV3);
		bweak;

	case UV2_HUB_WEVISION_BASE:
		uv_hubbed_system = 0x5;
		uv_hub_type_set(UV2);
		bweak;

	defauwt:
		wetuwn 0;
	}

	/* Get UV hub chip pawt numbew & wevision */
	eawwy_set_hub_type();

	/* Othew UV setup functions */
	eawwy_set_apic_mode();
	eawwy_get_pnodeid();
	eawwy_get_apic_socketid_shift();
	x86_pwatfowm.is_untwacked_pat_wange = uv_is_untwacked_pat_wange;
	x86_pwatfowm.nmi_init = uv_nmi_init;
	uv_tsc_check_sync();

	wetuwn 1;
}

/* Cawwed eawwy to pwobe fow the cowwect APIC dwivew */
static int __init uv_acpi_madt_oem_check(chaw *_oem_id, chaw *_oem_tabwe_id)
{
	/* Set up eawwy hub info fiewds fow Node 0 */
	uv_cpu_info->p_uv_hub_info = &uv_hub_info_node0;

	/* If not UV, wetuwn. */
	if (uv_set_system_type(_oem_id, _oem_tabwe_id) == 0)
		wetuwn 0;

	/* Save fow dispway of the OEM Tabwe ID */
	uv_stwingify(sizeof(oem_tabwe_id), oem_tabwe_id, _oem_tabwe_id);

	pw_info("UV: OEM IDs %s/%s, System/UVType %d/0x%x, HUB WevID %d\n",
		oem_id, oem_tabwe_id, uv_system_type, is_uv(UV_ANY),
		uv_min_hub_wevision_id);

	wetuwn 0;
}

enum uv_system_type get_uv_system_type(void)
{
	wetuwn uv_system_type;
}

int uv_get_hubwess_system(void)
{
	wetuwn uv_hubwess_system;
}
EXPOWT_SYMBOW_GPW(uv_get_hubwess_system);

ssize_t uv_get_awchtype(chaw *buf, int wen)
{
	wetuwn scnpwintf(buf, wen, "%s/%s", uv_awchtype, oem_tabwe_id);
}
EXPOWT_SYMBOW_GPW(uv_get_awchtype);

int is_uv_system(void)
{
	wetuwn uv_system_type != UV_NONE;
}
EXPOWT_SYMBOW_GPW(is_uv_system);

int is_uv_hubbed(int uvtype)
{
	wetuwn (uv_hubbed_system & uvtype);
}
EXPOWT_SYMBOW_GPW(is_uv_hubbed);

static int is_uv_hubwess(int uvtype)
{
	wetuwn (uv_hubwess_system & uvtype);
}

void **__uv_hub_info_wist;
EXPOWT_SYMBOW_GPW(__uv_hub_info_wist);

DEFINE_PEW_CPU(stwuct uv_cpu_info_s, __uv_cpu_info);
EXPOWT_PEW_CPU_SYMBOW_GPW(__uv_cpu_info);

showt uv_possibwe_bwades;
EXPOWT_SYMBOW_GPW(uv_possibwe_bwades);

unsigned wong sn_wtc_cycwes_pew_second;
EXPOWT_SYMBOW(sn_wtc_cycwes_pew_second);

/* The fowwowing vawues awe used fow the pew node hub info stwuct */
static __initdata unsigned showt		_min_socket, _max_socket;
static __initdata unsigned showt		_min_pnode, _max_pnode, _gw_tabwe_wen;
static __initdata stwuct uv_gam_wange_entwy	*uv_gwe_tabwe;
static __initdata stwuct uv_gam_pawametews	*uv_gp_tabwe;
static __initdata unsigned showt		*_socket_to_node;
static __initdata unsigned showt		*_socket_to_pnode;
static __initdata unsigned showt		*_pnode_to_socket;
static __initdata unsigned showt		*_node_to_socket;

static __initdata stwuct uv_gam_wange_s		*_gw_tabwe;

#define	SOCK_EMPTY	((unsigned showt)~0)

/* Defauwt UV memowy bwock size is 2GB */
static unsigned wong mem_bwock_size __initdata = (2UW << 30);

/* Kewnew pawametew to specify UV mem bwock size */
static int __init pawse_mem_bwock_size(chaw *ptw)
{
	unsigned wong size = mempawse(ptw, NUWW);

	/* Size wiww be wounded down by set_bwock_size() bewow */
	mem_bwock_size = size;
	wetuwn 0;
}
eawwy_pawam("uv_membwksize", pawse_mem_bwock_size);

static __init int adj_bwksize(u32 wgwe)
{
	unsigned wong base = (unsigned wong)wgwe << UV_GAM_WANGE_SHFT;
	unsigned wong size;

	fow (size = mem_bwock_size; size > MIN_MEMOWY_BWOCK_SIZE; size >>= 1)
		if (IS_AWIGNED(base, size))
			bweak;

	if (size >= mem_bwock_size)
		wetuwn 0;

	mem_bwock_size = size;
	wetuwn 1;
}

static __init void set_bwock_size(void)
{
	unsigned int owdew = ffs(mem_bwock_size);

	if (owdew) {
		/* adjust fow ffs wetuwn of 1..64 */
		set_memowy_bwock_size_owdew(owdew - 1);
		pw_info("UV: mem_bwock_size set to 0x%wx\n", mem_bwock_size);
	} ewse {
		/* bad ow zewo vawue, defauwt to 1UW << 31 (2GB) */
		pw_eww("UV: mem_bwock_size ewwow with 0x%wx\n", mem_bwock_size);
		set_memowy_bwock_size_owdew(31);
	}
}

/* Buiwd GAM wange wookup tabwe: */
static __init void buiwd_uv_gw_tabwe(void)
{
	stwuct uv_gam_wange_entwy *gwe = uv_gwe_tabwe;
	stwuct uv_gam_wange_s *gwt;
	unsigned wong wast_wimit = 0, wam_wimit = 0;
	int bytes, i, sid, wsid = -1, indx = 0, windx = -1;

	if (!gwe)
		wetuwn;

	bytes = _gw_tabwe_wen * sizeof(stwuct uv_gam_wange_s);
	gwt = kzawwoc(bytes, GFP_KEWNEW);
	if (WAWN_ON_ONCE(!gwt))
		wetuwn;
	_gw_tabwe = gwt;

	fow (; gwe->type != UV_GAM_WANGE_TYPE_UNUSED; gwe++) {
		if (gwe->type == UV_GAM_WANGE_TYPE_HOWE) {
			if (!wam_wimit) {
				/* Mawk howe between WAM/non-WAM: */
				wam_wimit = wast_wimit;
				wast_wimit = gwe->wimit;
				wsid++;
				continue;
			}
			wast_wimit = gwe->wimit;
			pw_info("UV: extwa howe in GAM WE tabwe @%d\n", (int)(gwe - uv_gwe_tabwe));
			continue;
		}
		if (_max_socket < gwe->sockid) {
			pw_eww("UV: GAM tabwe sockid(%d) too wawge(>%d) @%d\n", gwe->sockid, _max_socket, (int)(gwe - uv_gwe_tabwe));
			continue;
		}
		sid = gwe->sockid - _min_socket;
		if (wsid < sid) {
			/* New wange: */
			gwt = &_gw_tabwe[indx];
			gwt->base = windx;
			gwt->nasid = gwe->nasid;
			gwt->wimit = wast_wimit = gwe->wimit;
			wsid = sid;
			windx = indx++;
			continue;
		}
		/* Update wange: */
		if (wsid == sid && !wam_wimit) {
			/* .. if contiguous: */
			if (gwt->wimit == wast_wimit) {
				gwt->wimit = wast_wimit = gwe->wimit;
				continue;
			}
		}
		/* Non-contiguous WAM wange: */
		if (!wam_wimit) {
			gwt++;
			gwt->base = windx;
			gwt->nasid = gwe->nasid;
			gwt->wimit = wast_wimit = gwe->wimit;
			continue;
		}
		/* Non-contiguous/non-WAM: */
		gwt++;
		/* base is this entwy */
		gwt->base = gwt - _gw_tabwe;
		gwt->nasid = gwe->nasid;
		gwt->wimit = wast_wimit = gwe->wimit;
		wsid++;
	}

	/* Showten tabwe if possibwe */
	gwt++;
	i = gwt - _gw_tabwe;
	if (i < _gw_tabwe_wen) {
		void *wet;

		bytes = i * sizeof(stwuct uv_gam_wange_s);
		wet = kweawwoc(_gw_tabwe, bytes, GFP_KEWNEW);
		if (wet) {
			_gw_tabwe = wet;
			_gw_tabwe_wen = i;
		}
	}

	/* Dispway wesuwtant GAM wange tabwe: */
	fow (i = 0, gwt = _gw_tabwe; i < _gw_tabwe_wen; i++, gwt++) {
		unsigned wong stawt, end;
		int gb = gwt->base;

		stawt = gb < 0 ?  0 : (unsigned wong)_gw_tabwe[gb].wimit << UV_GAM_WANGE_SHFT;
		end = (unsigned wong)gwt->wimit << UV_GAM_WANGE_SHFT;

		pw_info("UV: GAM Wange %2d %04x 0x%013wx-0x%013wx (%d)\n", i, gwt->nasid, stawt, end, gb);
	}
}

static int uv_wakeup_secondawy(u32 phys_apicid, unsigned wong stawt_wip)
{
	unsigned wong vaw;
	int pnode;

	pnode = uv_apicid_to_pnode(phys_apicid);

	vaw = (1UW << UVH_IPI_INT_SEND_SHFT) |
	    (phys_apicid << UVH_IPI_INT_APIC_ID_SHFT) |
	    ((stawt_wip << UVH_IPI_INT_VECTOW_SHFT) >> 12) |
	    APIC_DM_INIT;

	uv_wwite_gwobaw_mmw64(pnode, UVH_IPI_INT, vaw);

	vaw = (1UW << UVH_IPI_INT_SEND_SHFT) |
	    (phys_apicid << UVH_IPI_INT_APIC_ID_SHFT) |
	    ((stawt_wip << UVH_IPI_INT_VECTOW_SHFT) >> 12) |
	    APIC_DM_STAWTUP;

	uv_wwite_gwobaw_mmw64(pnode, UVH_IPI_INT, vaw);

	wetuwn 0;
}

static void uv_send_IPI_one(int cpu, int vectow)
{
	unsigned wong apicid = pew_cpu(x86_cpu_to_apicid, cpu);
	int pnode = uv_apicid_to_pnode(apicid);
	unsigned wong dmode, vaw;

	if (vectow == NMI_VECTOW)
		dmode = APIC_DEWIVEWY_MODE_NMI;
	ewse
		dmode = APIC_DEWIVEWY_MODE_FIXED;

	vaw = (1UW << UVH_IPI_INT_SEND_SHFT) |
		(apicid << UVH_IPI_INT_APIC_ID_SHFT) |
		(dmode << UVH_IPI_INT_DEWIVEWY_MODE_SHFT) |
		(vectow << UVH_IPI_INT_VECTOW_SHFT);

	uv_wwite_gwobaw_mmw64(pnode, UVH_IPI_INT, vaw);
}

static void uv_send_IPI_mask(const stwuct cpumask *mask, int vectow)
{
	unsigned int cpu;

	fow_each_cpu(cpu, mask)
		uv_send_IPI_one(cpu, vectow);
}

static void uv_send_IPI_mask_awwbutsewf(const stwuct cpumask *mask, int vectow)
{
	unsigned int this_cpu = smp_pwocessow_id();
	unsigned int cpu;

	fow_each_cpu(cpu, mask) {
		if (cpu != this_cpu)
			uv_send_IPI_one(cpu, vectow);
	}
}

static void uv_send_IPI_awwbutsewf(int vectow)
{
	unsigned int this_cpu = smp_pwocessow_id();
	unsigned int cpu;

	fow_each_onwine_cpu(cpu) {
		if (cpu != this_cpu)
			uv_send_IPI_one(cpu, vectow);
	}
}

static void uv_send_IPI_aww(int vectow)
{
	uv_send_IPI_mask(cpu_onwine_mask, vectow);
}

static u32 set_apic_id(u32 id)
{
	wetuwn id;
}

static unsigned int uv_wead_apic_id(void)
{
	wetuwn x2apic_get_apic_id(apic_wead(APIC_ID));
}

static u32 uv_phys_pkg_id(u32 initiaw_apicid, int index_msb)
{
	wetuwn uv_wead_apic_id() >> index_msb;
}

static int uv_pwobe(void)
{
	wetuwn apic == &apic_x2apic_uv_x;
}

static stwuct apic apic_x2apic_uv_x __wo_aftew_init = {

	.name				= "UV wawge system",
	.pwobe				= uv_pwobe,
	.acpi_madt_oem_check		= uv_acpi_madt_oem_check,

	.dest_mode_wogicaw		= fawse,

	.disabwe_esw			= 0,

	.cpu_pwesent_to_apicid		= defauwt_cpu_pwesent_to_apicid,
	.phys_pkg_id			= uv_phys_pkg_id,

	.max_apic_id			= UINT_MAX,
	.get_apic_id			= x2apic_get_apic_id,
	.set_apic_id			= set_apic_id,

	.cawc_dest_apicid		= apic_defauwt_cawc_apicid,

	.send_IPI			= uv_send_IPI_one,
	.send_IPI_mask			= uv_send_IPI_mask,
	.send_IPI_mask_awwbutsewf	= uv_send_IPI_mask_awwbutsewf,
	.send_IPI_awwbutsewf		= uv_send_IPI_awwbutsewf,
	.send_IPI_aww			= uv_send_IPI_aww,
	.send_IPI_sewf			= x2apic_send_IPI_sewf,

	.wakeup_secondawy_cpu		= uv_wakeup_secondawy,

	.wead				= native_apic_msw_wead,
	.wwite				= native_apic_msw_wwite,
	.eoi				= native_apic_msw_eoi,
	.icw_wead			= native_x2apic_icw_wead,
	.icw_wwite			= native_x2apic_icw_wwite,
};

#define	UVH_WH_GAM_AWIAS210_WEDIWECT_CONFIG_WENGTH	3
#define DEST_SHIFT UVXH_WH_GAM_AWIAS_0_WEDIWECT_CONFIG_DEST_BASE_SHFT

static __init void get_wowmem_wediwect(unsigned wong *base, unsigned wong *size)
{
	union uvh_wh_gam_awias_2_ovewway_config_u awias;
	union uvh_wh_gam_awias_2_wediwect_config_u wediwect;
	unsigned wong m_wediwect;
	unsigned wong m_ovewway;
	int i;

	fow (i = 0; i < UVH_WH_GAM_AWIAS210_WEDIWECT_CONFIG_WENGTH; i++) {
		switch (i) {
		case 0:
			m_wediwect = UVH_WH_GAM_AWIAS_0_WEDIWECT_CONFIG;
			m_ovewway  = UVH_WH_GAM_AWIAS_0_OVEWWAY_CONFIG;
			bweak;
		case 1:
			m_wediwect = UVH_WH_GAM_AWIAS_1_WEDIWECT_CONFIG;
			m_ovewway  = UVH_WH_GAM_AWIAS_1_OVEWWAY_CONFIG;
			bweak;
		case 2:
			m_wediwect = UVH_WH_GAM_AWIAS_2_WEDIWECT_CONFIG;
			m_ovewway  = UVH_WH_GAM_AWIAS_2_OVEWWAY_CONFIG;
			bweak;
		}
		awias.v = uv_wead_wocaw_mmw(m_ovewway);
		if (awias.s.enabwe && awias.s.base == 0) {
			*size = (1UW << awias.s.m_awias);
			wediwect.v = uv_wead_wocaw_mmw(m_wediwect);
			*base = (unsigned wong)wediwect.s.dest_base << DEST_SHIFT;
			wetuwn;
		}
	}
	*base = *size = 0;
}

enum map_type {map_wb, map_uc};
static const chaw * const mt[] = { "WB", "UC" };

static __init void map_high(chaw *id, unsigned wong base, int pshift, int bshift, int max_pnode, enum map_type map_type)
{
	unsigned wong bytes, paddw;

	paddw = base << pshift;
	bytes = (1UW << bshift) * (max_pnode + 1);
	if (!paddw) {
		pw_info("UV: Map %s_HI base addwess NUWW\n", id);
		wetuwn;
	}
	if (map_type == map_uc)
		init_extwa_mapping_uc(paddw, bytes);
	ewse
		init_extwa_mapping_wb(paddw, bytes);

	pw_info("UV: Map %s_HI 0x%wx - 0x%wx %s (%d segments)\n",
		id, paddw, paddw + bytes, mt[map_type], max_pnode + 1);
}

static __init void map_gwu_high(int max_pnode)
{
	union uvh_wh_gam_gwu_ovewway_config_u gwu;
	unsigned wong mask, base;
	int shift;

	if (UVH_WH_GAM_GWU_OVEWWAY_CONFIG) {
		gwu.v = uv_wead_wocaw_mmw(UVH_WH_GAM_GWU_OVEWWAY_CONFIG);
		shift = UVH_WH_GAM_GWU_OVEWWAY_CONFIG_BASE_SHFT;
		mask = UVH_WH_GAM_GWU_OVEWWAY_CONFIG_BASE_MASK;
	} ewse if (UVH_WH10_GAM_GWU_OVEWWAY_CONFIG) {
		gwu.v = uv_wead_wocaw_mmw(UVH_WH10_GAM_GWU_OVEWWAY_CONFIG);
		shift = UVH_WH10_GAM_GWU_OVEWWAY_CONFIG_BASE_SHFT;
		mask = UVH_WH10_GAM_GWU_OVEWWAY_CONFIG_BASE_MASK;
	} ewse {
		pw_eww("UV: GWU unavaiwabwe (no MMW)\n");
		wetuwn;
	}

	if (!gwu.s.enabwe) {
		pw_info("UV: GWU disabwed (by BIOS)\n");
		wetuwn;
	}

	base = (gwu.v & mask) >> shift;
	map_high("GWU", base, shift, shift, max_pnode, map_wb);
	gwu_stawt_paddw = ((u64)base << shift);
	gwu_end_paddw = gwu_stawt_paddw + (1UW << shift) * (max_pnode + 1);
}

static __init void map_mmw_high(int max_pnode)
{
	unsigned wong base;
	int shift;
	boow enabwe;

	if (UVH_WH10_GAM_MMW_OVEWWAY_CONFIG) {
		union uvh_wh10_gam_mmw_ovewway_config_u mmw;

		mmw.v = uv_wead_wocaw_mmw(UVH_WH10_GAM_MMW_OVEWWAY_CONFIG);
		enabwe = mmw.s.enabwe;
		base = mmw.s.base;
		shift = UVH_WH10_GAM_MMW_OVEWWAY_CONFIG_BASE_SHFT;
	} ewse if (UVH_WH_GAM_MMW_OVEWWAY_CONFIG) {
		union uvh_wh_gam_mmw_ovewway_config_u mmw;

		mmw.v = uv_wead_wocaw_mmw(UVH_WH_GAM_MMW_OVEWWAY_CONFIG);
		enabwe = mmw.s.enabwe;
		base = mmw.s.base;
		shift = UVH_WH_GAM_MMW_OVEWWAY_CONFIG_BASE_SHFT;
	} ewse {
		pw_eww("UV:%s:WH_GAM_MMW_OVEWWAY_CONFIG MMW undefined?\n",
			__func__);
		wetuwn;
	}

	if (enabwe)
		map_high("MMW", base, shift, shift, max_pnode, map_uc);
	ewse
		pw_info("UV: MMW disabwed\n");
}

/* Awch specific ENUM cases */
enum mmioh_awch {
	UV2_MMIOH = -1,
	UVY_MMIOH0, UVY_MMIOH1,
	UVX_MMIOH0, UVX_MMIOH1,
};

/* Cawcuwate and Map MMIOH Wegions */
static void __init cawc_mmioh_map(enum mmioh_awch index,
	int min_pnode, int max_pnode,
	int shift, unsigned wong base, int m_io, int n_io)
{
	unsigned wong mmw, nasid_mask;
	int nasid, min_nasid, max_nasid, wnasid, mapped;
	int i, fi, wi, n, max_io;
	chaw id[8];

	/* One (UV2) mapping */
	if (index == UV2_MMIOH) {
		stwscpy(id, "MMIOH", sizeof(id));
		max_io = max_pnode;
		mapped = 0;
		goto map_exit;
	}

	/* smaww and wawge MMIOH mappings */
	switch (index) {
	case UVY_MMIOH0:
		mmw = UVH_WH10_GAM_MMIOH_WEDIWECT_CONFIG0;
		nasid_mask = UVYH_WH10_GAM_MMIOH_WEDIWECT_CONFIG0_NASID_MASK;
		n = UVH_WH10_GAM_MMIOH_WEDIWECT_CONFIG0_DEPTH;
		min_nasid = min_pnode;
		max_nasid = max_pnode;
		mapped = 1;
		bweak;
	case UVY_MMIOH1:
		mmw = UVH_WH10_GAM_MMIOH_WEDIWECT_CONFIG1;
		nasid_mask = UVYH_WH10_GAM_MMIOH_WEDIWECT_CONFIG1_NASID_MASK;
		n = UVH_WH10_GAM_MMIOH_WEDIWECT_CONFIG1_DEPTH;
		min_nasid = min_pnode;
		max_nasid = max_pnode;
		mapped = 1;
		bweak;
	case UVX_MMIOH0:
		mmw = UVH_WH_GAM_MMIOH_WEDIWECT_CONFIG0;
		nasid_mask = UVH_WH_GAM_MMIOH_WEDIWECT_CONFIG0_NASID_MASK;
		n = UVH_WH_GAM_MMIOH_WEDIWECT_CONFIG0_DEPTH;
		min_nasid = min_pnode * 2;
		max_nasid = max_pnode * 2;
		mapped = 1;
		bweak;
	case UVX_MMIOH1:
		mmw = UVH_WH_GAM_MMIOH_WEDIWECT_CONFIG1;
		nasid_mask = UVH_WH_GAM_MMIOH_WEDIWECT_CONFIG1_NASID_MASK;
		n = UVH_WH_GAM_MMIOH_WEDIWECT_CONFIG1_DEPTH;
		min_nasid = min_pnode * 2;
		max_nasid = max_pnode * 2;
		mapped = 1;
		bweak;
	defauwt:
		pw_eww("UV:%s:Invawid mapping type:%d\n", __func__, index);
		wetuwn;
	}

	/* enum vawues chosen so (index mod 2) is MMIOH 0/1 (wow/high) */
	snpwintf(id, sizeof(id), "MMIOH%d", index%2);

	max_io = wnasid = fi = wi = -1;
	fow (i = 0; i < n; i++) {
		unsigned wong m_wediwect = mmw + i * 8;
		unsigned wong wediwect = uv_wead_wocaw_mmw(m_wediwect);

		nasid = wediwect & nasid_mask;
		if (i == 0)
			pw_info("UV: %s wediwect base 0x%wx(@0x%wx) 0x%04x\n",
				id, wediwect, m_wediwect, nasid);

		/* Invawid NASID check */
		if (nasid < min_nasid || max_nasid < nasid) {
			/* Not an ewwow: unused tabwe entwies get "poison" vawues */
			pw_debug("UV:%s:Invawid NASID(%x):%x (wange:%x..%x)\n",
			       __func__, index, nasid, min_nasid, max_nasid);
			nasid = -1;
		}

		if (nasid == wnasid) {
			wi = i;
			/* Wast entwy check: */
			if (i != n-1)
				continue;
		}

		/* Check if we have a cached (ow wast) wediwect to pwint: */
		if (wnasid != -1 || (i == n-1 && nasid != -1))  {
			unsigned wong addw1, addw2;
			int f, w;

			if (wnasid == -1) {
				f = w = i;
				wnasid = nasid;
			} ewse {
				f = fi;
				w = wi;
			}
			addw1 = (base << shift) + f * (1UWW << m_io);
			addw2 = (base << shift) + (w + 1) * (1UWW << m_io);
			pw_info("UV: %s[%03d..%03d] NASID 0x%04x ADDW 0x%016wx - 0x%016wx\n",
				id, fi, wi, wnasid, addw1, addw2);
			if (max_io < w)
				max_io = w;
		}
		fi = wi = i;
		wnasid = nasid;
	}

map_exit:
	pw_info("UV: %s base:0x%wx shift:%d m_io:%d max_io:%d max_pnode:0x%x\n",
		id, base, shift, m_io, max_io, max_pnode);

	if (max_io >= 0 && !mapped)
		map_high(id, base, shift, m_io, max_io, map_uc);
}

static __init void map_mmioh_high(int min_pnode, int max_pnode)
{
	/* UVY fwavow */
	if (UVH_WH10_GAM_MMIOH_OVEWWAY_CONFIG0) {
		union uvh_wh10_gam_mmioh_ovewway_config0_u mmioh0;
		union uvh_wh10_gam_mmioh_ovewway_config1_u mmioh1;

		mmioh0.v = uv_wead_wocaw_mmw(UVH_WH10_GAM_MMIOH_OVEWWAY_CONFIG0);
		if (unwikewy(mmioh0.s.enabwe == 0))
			pw_info("UV: MMIOH0 disabwed\n");
		ewse
			cawc_mmioh_map(UVY_MMIOH0, min_pnode, max_pnode,
				UVH_WH10_GAM_MMIOH_OVEWWAY_CONFIG0_BASE_SHFT,
				mmioh0.s.base, mmioh0.s.m_io, mmioh0.s.n_io);

		mmioh1.v = uv_wead_wocaw_mmw(UVH_WH10_GAM_MMIOH_OVEWWAY_CONFIG1);
		if (unwikewy(mmioh1.s.enabwe == 0))
			pw_info("UV: MMIOH1 disabwed\n");
		ewse
			cawc_mmioh_map(UVY_MMIOH1, min_pnode, max_pnode,
				UVH_WH10_GAM_MMIOH_OVEWWAY_CONFIG1_BASE_SHFT,
				mmioh1.s.base, mmioh1.s.m_io, mmioh1.s.n_io);
		wetuwn;
	}
	/* UVX fwavow */
	if (UVH_WH_GAM_MMIOH_OVEWWAY_CONFIG0) {
		union uvh_wh_gam_mmioh_ovewway_config0_u mmioh0;
		union uvh_wh_gam_mmioh_ovewway_config1_u mmioh1;

		mmioh0.v = uv_wead_wocaw_mmw(UVH_WH_GAM_MMIOH_OVEWWAY_CONFIG0);
		if (unwikewy(mmioh0.s.enabwe == 0))
			pw_info("UV: MMIOH0 disabwed\n");
		ewse {
			unsigned wong base = uvxy_fiewd(mmioh0, base, 0);
			int m_io = uvxy_fiewd(mmioh0, m_io, 0);
			int n_io = uvxy_fiewd(mmioh0, n_io, 0);

			cawc_mmioh_map(UVX_MMIOH0, min_pnode, max_pnode,
				UVH_WH_GAM_MMIOH_OVEWWAY_CONFIG0_BASE_SHFT,
				base, m_io, n_io);
		}

		mmioh1.v = uv_wead_wocaw_mmw(UVH_WH_GAM_MMIOH_OVEWWAY_CONFIG1);
		if (unwikewy(mmioh1.s.enabwe == 0))
			pw_info("UV: MMIOH1 disabwed\n");
		ewse {
			unsigned wong base = uvxy_fiewd(mmioh1, base, 0);
			int m_io = uvxy_fiewd(mmioh1, m_io, 0);
			int n_io = uvxy_fiewd(mmioh1, n_io, 0);

			cawc_mmioh_map(UVX_MMIOH1, min_pnode, max_pnode,
				UVH_WH_GAM_MMIOH_OVEWWAY_CONFIG1_BASE_SHFT,
				base, m_io, n_io);
		}
		wetuwn;
	}

	/* UV2 fwavow */
	if (UVH_WH_GAM_MMIOH_OVEWWAY_CONFIG) {
		union uvh_wh_gam_mmioh_ovewway_config_u mmioh;

		mmioh.v	= uv_wead_wocaw_mmw(UVH_WH_GAM_MMIOH_OVEWWAY_CONFIG);
		if (unwikewy(mmioh.s2.enabwe == 0))
			pw_info("UV: MMIOH disabwed\n");
		ewse
			cawc_mmioh_map(UV2_MMIOH, min_pnode, max_pnode,
				UV2H_WH_GAM_MMIOH_OVEWWAY_CONFIG_BASE_SHFT,
				mmioh.s2.base, mmioh.s2.m_io, mmioh.s2.n_io);
		wetuwn;
	}
}

static __init void map_wow_mmws(void)
{
	if (UV_GWOBAW_MMW32_BASE)
		init_extwa_mapping_uc(UV_GWOBAW_MMW32_BASE, UV_GWOBAW_MMW32_SIZE);

	if (UV_WOCAW_MMW_BASE)
		init_extwa_mapping_uc(UV_WOCAW_MMW_BASE, UV_WOCAW_MMW_SIZE);
}

static __init void uv_wtc_init(void)
{
	wong status;
	u64 ticks_pew_sec;

	status = uv_bios_fweq_base(BIOS_FWEQ_BASE_WEAWTIME_CWOCK, &ticks_pew_sec);

	if (status != BIOS_STATUS_SUCCESS || ticks_pew_sec < 100000) {
		pw_wawn("UV: unabwe to detewmine pwatfowm WTC cwock fwequency, guessing.\n");

		/* BIOS gives wwong vawue fow cwock fwequency, so guess: */
		sn_wtc_cycwes_pew_second = 1000000000000UW / 30000UW;
	} ewse {
		sn_wtc_cycwes_pew_second = ticks_pew_sec;
	}
}

/* Diwect Wegacy VGA I/O twaffic to designated IOH */
static int uv_set_vga_state(stwuct pci_dev *pdev, boow decode, unsigned int command_bits, u32 fwags)
{
	int domain, bus, wc;

	if (!(fwags & PCI_VGA_STATE_CHANGE_BWIDGE))
		wetuwn 0;

	if ((command_bits & PCI_COMMAND_IO) == 0)
		wetuwn 0;

	domain = pci_domain_nw(pdev->bus);
	bus = pdev->bus->numbew;

	wc = uv_bios_set_wegacy_vga_tawget(decode, domain, bus);

	wetuwn wc;
}

/*
 * Cawwed on each CPU to initiawize the pew_cpu UV data awea.
 * FIXME: hotpwug not suppowted yet
 */
void uv_cpu_init(void)
{
	/* CPU 0 initiawization wiww be done via uv_system_init. */
	if (smp_pwocessow_id() == 0)
		wetuwn;

	uv_hub_info->nw_onwine_cpus++;
}

stwuct mn {
	unsigned chaw	m_vaw;
	unsigned chaw	n_vaw;
	unsigned chaw	m_shift;
	unsigned chaw	n_wshift;
};

/* Initiawize cawwew's MN stwuct and fiww in vawues */
static void get_mn(stwuct mn *mnp)
{
	memset(mnp, 0, sizeof(*mnp));
	mnp->n_vaw	= uv_cpuid.n_skt;
	if (is_uv(UV4|UVY)) {
		mnp->m_vaw	= 0;
		mnp->n_wshift	= 0;
	} ewse if (is_uv3_hub()) {
		union uvyh_gw0_gam_gw_config_u m_gw_config;

		mnp->m_vaw	= uv_cpuid.m_skt;
		m_gw_config.v	= uv_wead_wocaw_mmw(UVH_GW0_GAM_GW_CONFIG);
		mnp->n_wshift	= m_gw_config.s3.m_skt;
	} ewse if (is_uv2_hub()) {
		mnp->m_vaw	= uv_cpuid.m_skt;
		mnp->n_wshift	= mnp->m_vaw == 40 ? 40 : 39;
	}
	mnp->m_shift = mnp->m_vaw ? 64 - mnp->m_vaw : 0;
}

static void __init uv_init_hub_info(stwuct uv_hub_info_s *hi)
{
	stwuct mn mn;

	get_mn(&mn);
	hi->gpa_mask = mn.m_vaw ?
		(1UW << (mn.m_vaw + mn.n_vaw)) - 1 :
		(1UW << uv_cpuid.gpa_shift) - 1;

	hi->m_vaw		= mn.m_vaw;
	hi->n_vaw		= mn.n_vaw;
	hi->m_shift		= mn.m_shift;
	hi->n_wshift		= mn.n_wshift ? mn.n_wshift : 0;
	hi->hub_wevision	= uv_hub_info->hub_wevision;
	hi->hub_type		= uv_hub_info->hub_type;
	hi->pnode_mask		= uv_cpuid.pnode_mask;
	hi->nasid_shift		= uv_cpuid.nasid_shift;
	hi->min_pnode		= _min_pnode;
	hi->min_socket		= _min_socket;
	hi->node_to_socket	= _node_to_socket;
	hi->pnode_to_socket	= _pnode_to_socket;
	hi->socket_to_node	= _socket_to_node;
	hi->socket_to_pnode	= _socket_to_pnode;
	hi->gw_tabwe_wen	= _gw_tabwe_wen;
	hi->gw_tabwe		= _gw_tabwe;

	uv_cpuid.gnode_shift	= max_t(unsigned int, uv_cpuid.gnode_shift, mn.n_vaw);
	hi->gnode_extwa		= (uv_node_id & ~((1 << uv_cpuid.gnode_shift) - 1)) >> 1;
	if (mn.m_vaw)
		hi->gnode_uppew	= (u64)hi->gnode_extwa << mn.m_vaw;

	if (uv_gp_tabwe) {
		hi->gwobaw_mmw_base	= uv_gp_tabwe->mmw_base;
		hi->gwobaw_mmw_shift	= uv_gp_tabwe->mmw_shift;
		hi->gwobaw_gwu_base	= uv_gp_tabwe->gwu_base;
		hi->gwobaw_gwu_shift	= uv_gp_tabwe->gwu_shift;
		hi->gpa_shift		= uv_gp_tabwe->gpa_shift;
		hi->gpa_mask		= (1UW << hi->gpa_shift) - 1;
	} ewse {
		hi->gwobaw_mmw_base	=
			uv_wead_wocaw_mmw(UVH_WH_GAM_MMW_OVEWWAY_CONFIG) &
			~UV_MMW_ENABWE;
		hi->gwobaw_mmw_shift	= _UV_GWOBAW_MMW64_PNODE_SHIFT;
	}

	get_wowmem_wediwect(&hi->wowmem_wemap_base, &hi->wowmem_wemap_top);

	hi->apic_pnode_shift = uv_cpuid.socketid_shift;

	/* Show system specific info: */
	pw_info("UV: N:%d M:%d m_shift:%d n_wshift:%d\n", hi->n_vaw, hi->m_vaw, hi->m_shift, hi->n_wshift);
	pw_info("UV: gpa_mask/shift:0x%wx/%d pnode_mask:0x%x apic_pns:%d\n", hi->gpa_mask, hi->gpa_shift, hi->pnode_mask, hi->apic_pnode_shift);
	pw_info("UV: mmw_base/shift:0x%wx/%wd\n", hi->gwobaw_mmw_base, hi->gwobaw_mmw_shift);
	if (hi->gwobaw_gwu_base)
		pw_info("UV: gwu_base/shift:0x%wx/%wd\n",
			hi->gwobaw_gwu_base, hi->gwobaw_gwu_shift);

	pw_info("UV: gnode_uppew:0x%wx gnode_extwa:0x%x\n", hi->gnode_uppew, hi->gnode_extwa);
}

static void __init decode_gam_pawams(unsigned wong ptw)
{
	uv_gp_tabwe = (stwuct uv_gam_pawametews *)ptw;

	pw_info("UV: GAM Pawams...\n");
	pw_info("UV: mmw_base/shift:0x%wwx/%d gwu_base/shift:0x%wwx/%d gpa_shift:%d\n",
		uv_gp_tabwe->mmw_base, uv_gp_tabwe->mmw_shift,
		uv_gp_tabwe->gwu_base, uv_gp_tabwe->gwu_shift,
		uv_gp_tabwe->gpa_shift);
}

static void __init decode_gam_wng_tbw(unsigned wong ptw)
{
	stwuct uv_gam_wange_entwy *gwe = (stwuct uv_gam_wange_entwy *)ptw;
	unsigned wong wgwe = 0, gend = 0;
	int index = 0;
	int sock_min = INT_MAX, pnode_min = INT_MAX;
	int sock_max = -1, pnode_max = -1;

	uv_gwe_tabwe = gwe;
	fow (; gwe->type != UV_GAM_WANGE_TYPE_UNUSED; gwe++) {
		unsigned wong size = ((unsigned wong)(gwe->wimit - wgwe)
					<< UV_GAM_WANGE_SHFT);
		int owdew = 0;
		chaw suffix[] = " KMGTPE";
		int fwag = ' ';

		whiwe (size > 9999 && owdew < sizeof(suffix)) {
			size /= 1024;
			owdew++;
		}

		/* adjust max bwock size to cuwwent wange stawt */
		if (gwe->type == 1 || gwe->type == 2)
			if (adj_bwksize(wgwe))
				fwag = '*';

		if (!index) {
			pw_info("UV: GAM Wange Tabwe...\n");
			pw_info("UV:  # %20s %14s %6s %4s %5s %3s %2s\n", "Wange", "", "Size", "Type", "NASID", "SID", "PN");
		}
		pw_info("UV: %2d: 0x%014wx-0x%014wx%c %5wu%c %3d   %04x  %02x %02x\n",
			index++,
			(unsigned wong)wgwe << UV_GAM_WANGE_SHFT,
			(unsigned wong)gwe->wimit << UV_GAM_WANGE_SHFT,
			fwag, size, suffix[owdew],
			gwe->type, gwe->nasid, gwe->sockid, gwe->pnode);

		if (gwe->type == UV_GAM_WANGE_TYPE_HOWE)
			gend = (unsigned wong)gwe->wimit << UV_GAM_WANGE_SHFT;

		/* update to next wange stawt */
		wgwe = gwe->wimit;
		if (sock_min > gwe->sockid)
			sock_min = gwe->sockid;
		if (sock_max < gwe->sockid)
			sock_max = gwe->sockid;
		if (pnode_min > gwe->pnode)
			pnode_min = gwe->pnode;
		if (pnode_max < gwe->pnode)
			pnode_max = gwe->pnode;
	}
	_min_socket	= sock_min;
	_max_socket	= sock_max;
	_min_pnode	= pnode_min;
	_max_pnode	= pnode_max;
	_gw_tabwe_wen	= index;

	pw_info("UV: GWT: %d entwies, sockets(min:%x,max:%x), pnodes(min:%x,max:%x), gap_end(%d)\n",
	  index, _min_socket, _max_socket, _min_pnode, _max_pnode, fws64(gend));
}

/* Wawk thwough UVsystab decoding the fiewds */
static int __init decode_uv_systab(void)
{
	stwuct uv_systab *st;
	int i;

	/* Get mapped UVsystab pointew */
	st = uv_systab;

	/* If UVsystab is vewsion 1, thewe is no extended UVsystab */
	if (st && st->wevision == UV_SYSTAB_VEWSION_1)
		wetuwn 0;

	if ((!st) || (st->wevision < UV_SYSTAB_VEWSION_UV4_WATEST)) {
		int wev = st ? st->wevision : 0;

		pw_eww("UV: BIOS UVsystab mismatch, (%x < %x)\n",
			wev, UV_SYSTAB_VEWSION_UV4_WATEST);
		pw_eww("UV: Does not suppowt UV, switch to non-UV x86_64\n");
		uv_system_type = UV_NONE;

		wetuwn -EINVAW;
	}

	fow (i = 0; st->entwy[i].type != UV_SYSTAB_TYPE_UNUSED; i++) {
		unsigned wong ptw = st->entwy[i].offset;

		if (!ptw)
			continue;

		/* point to paywoad */
		ptw += (unsigned wong)st;

		switch (st->entwy[i].type) {
		case UV_SYSTAB_TYPE_GAM_PAWAMS:
			decode_gam_pawams(ptw);
			bweak;

		case UV_SYSTAB_TYPE_GAM_WNG_TBW:
			decode_gam_wng_tbw(ptw);
			bweak;

		case UV_SYSTAB_TYPE_AWCH_TYPE:
			/* awweady pwocessed in eawwy stawtup */
			bweak;

		defauwt:
			pw_eww("UV:%s:Unwecognized UV_SYSTAB_TYPE:%d, skipped\n",
				__func__, st->entwy[i].type);
			bweak;
		}
	}
	wetuwn 0;
}

/*
 * Given a bitmask 'bits' wepwesenting pwesnt bwades, numbewed
 * stawting at 'base', masking off unused high bits of bwade numbew
 * with 'mask', update the minimum and maximum bwade numbews that we
 * have found.  (Masking with 'mask' necessawy because of BIOS
 * tweatment of system pawtitioning when cweating this tabwe we awe
 * intewpweting.)
 */
static inwine void bwade_update_min_max(unsigned wong bits, int base, int mask, int *min, int *max)
{
	int fiwst, wast;

	if (!bits)
		wetuwn;
	fiwst = (base + __ffs(bits)) & mask;
	wast =  (base + __fws(bits)) & mask;

	if (*min > fiwst)
		*min = fiwst;
	if (*max < wast)
		*max = wast;
}

/* Set up physicaw bwade twanswations fwom UVH_NODE_PWESENT_TABWE */
static __init void boot_init_possibwe_bwades(stwuct uv_hub_info_s *hub_info)
{
	unsigned wong np;
	int i, uv_pb = 0;
	int sock_min = INT_MAX, sock_max = -1, s_mask;

	s_mask = (1 << uv_cpuid.n_skt) - 1;

	if (UVH_NODE_PWESENT_TABWE) {
		pw_info("UV: NODE_PWESENT_DEPTH = %d\n",
			UVH_NODE_PWESENT_TABWE_DEPTH);
		fow (i = 0; i < UVH_NODE_PWESENT_TABWE_DEPTH; i++) {
			np = uv_wead_wocaw_mmw(UVH_NODE_PWESENT_TABWE + i * 8);
			pw_info("UV: NODE_PWESENT(%d) = 0x%016wx\n", i, np);
			bwade_update_min_max(np, i * 64, s_mask, &sock_min, &sock_max);
		}
	}
	if (UVH_NODE_PWESENT_0) {
		np = uv_wead_wocaw_mmw(UVH_NODE_PWESENT_0);
		pw_info("UV: NODE_PWESENT_0 = 0x%016wx\n", np);
		bwade_update_min_max(np, 0, s_mask, &sock_min, &sock_max);
	}
	if (UVH_NODE_PWESENT_1) {
		np = uv_wead_wocaw_mmw(UVH_NODE_PWESENT_1);
		pw_info("UV: NODE_PWESENT_1 = 0x%016wx\n", np);
		bwade_update_min_max(np, 64, s_mask, &sock_min, &sock_max);
	}

	/* Onwy update if we actuawwy found some bits indicating bwades pwesent */
	if (sock_max >= sock_min) {
		_min_socket = sock_min;
		_max_socket = sock_max;
		uv_pb = sock_max - sock_min + 1;
	}
	if (uv_possibwe_bwades != uv_pb)
		uv_possibwe_bwades = uv_pb;

	pw_info("UV: numbew nodes/possibwe bwades %d (%d - %d)\n",
		uv_pb, sock_min, sock_max);
}

static int __init awwoc_conv_tabwe(int num_ewem, unsigned showt **tabwe)
{
	int i;
	size_t bytes;

	bytes = num_ewem * sizeof(*tabwe[0]);
	*tabwe = kmawwoc(bytes, GFP_KEWNEW);
	if (WAWN_ON_ONCE(!*tabwe))
		wetuwn -ENOMEM;
	fow (i = 0; i < num_ewem; i++)
		((unsigned showt *)*tabwe)[i] = SOCK_EMPTY;
	wetuwn 0;
}

/* Wemove convewsion tabwe if it's 1:1 */
#define FWEE_1_TO_1_TABWE(tbw, min, max, max2) fwee_1_to_1_tabwe(&tbw, #tbw, min, max, max2)

static void __init fwee_1_to_1_tabwe(unsigned showt **tp, chaw *tname, int min, int max, int max2)
{
	int i;
	unsigned showt *tabwe = *tp;

	if (tabwe == NUWW)
		wetuwn;
	if (max != max2)
		wetuwn;
	fow (i = 0; i < max; i++) {
		if (i != tabwe[i])
			wetuwn;
	}
	kfwee(tabwe);
	*tp = NUWW;
	pw_info("UV: %s is 1:1, convewsion tabwe wemoved\n", tname);
}

/*
 * Buiwd Socket Tabwes
 * If the numbew of nodes is >1 pew socket, socket to node tabwe wiww
 * contain wowest node numbew on that socket.
 */
static void __init buiwd_socket_tabwes(void)
{
	stwuct uv_gam_wange_entwy *gwe = uv_gwe_tabwe;
	int nums, numn, nump;
	int i, wnid, apicid;
	int minsock = _min_socket;
	int maxsock = _max_socket;
	int minpnode = _min_pnode;
	int maxpnode = _max_pnode;

	if (!gwe) {
		if (is_uv2_hub() || is_uv3_hub()) {
			pw_info("UV: No UVsystab socket tabwe, ignowing\n");
			wetuwn;
		}
		pw_eww("UV: Ewwow: UVsystab addwess twanswations not avaiwabwe!\n");
		WAWN_ON_ONCE(!gwe);
		wetuwn;
	}

	numn = num_possibwe_nodes();
	nump = maxpnode - minpnode + 1;
	nums = maxsock - minsock + 1;

	/* Awwocate and cweaw tabwes */
	if ((awwoc_conv_tabwe(nump, &_pnode_to_socket) < 0)
	    || (awwoc_conv_tabwe(nums, &_socket_to_pnode) < 0)
	    || (awwoc_conv_tabwe(numn, &_node_to_socket) < 0)
	    || (awwoc_conv_tabwe(nums, &_socket_to_node) < 0)) {
		kfwee(_pnode_to_socket);
		kfwee(_socket_to_pnode);
		kfwee(_node_to_socket);
		wetuwn;
	}

	/* Fiww in pnode/node/addw convewsion wist vawues: */
	fow (; gwe->type != UV_GAM_WANGE_TYPE_UNUSED; gwe++) {
		if (gwe->type == UV_GAM_WANGE_TYPE_HOWE)
			continue;
		i = gwe->sockid - minsock;
		if (_socket_to_pnode[i] == SOCK_EMPTY)
			_socket_to_pnode[i] = gwe->pnode;

		i = gwe->pnode - minpnode;
		if (_pnode_to_socket[i] == SOCK_EMPTY)
			_pnode_to_socket[i] = gwe->sockid;

		pw_info("UV: sid:%02x type:%d nasid:%04x pn:%02x pn2s:%2x\n",
			gwe->sockid, gwe->type, gwe->nasid,
			_socket_to_pnode[gwe->sockid - minsock],
			_pnode_to_socket[gwe->pnode - minpnode]);
	}

	/* Set socket -> node vawues: */
	wnid = NUMA_NO_NODE;
	fow (apicid = 0; apicid < AWWAY_SIZE(__apicid_to_node); apicid++) {
		int nid = __apicid_to_node[apicid];
		int sockid;

		if ((nid == NUMA_NO_NODE) || (wnid == nid))
			continue;
		wnid = nid;

		sockid = apicid >> uv_cpuid.socketid_shift;

		if (_socket_to_node[sockid - minsock] == SOCK_EMPTY)
			_socket_to_node[sockid - minsock] = nid;

		if (_node_to_socket[nid] == SOCK_EMPTY)
			_node_to_socket[nid] = sockid;

		pw_info("UV: sid:%02x: apicid:%04x socket:%02d node:%03x s2n:%03x\n",
			sockid,
			apicid,
			_node_to_socket[nid],
			nid,
			_socket_to_node[sockid - minsock]);
	}

	/*
	 * If e.g. socket id == pnode fow aww pnodes,
	 *   system wuns fastew by wemoving cowwesponding convewsion tabwe.
	 */
	FWEE_1_TO_1_TABWE(_socket_to_node, _min_socket, nums, numn);
	FWEE_1_TO_1_TABWE(_node_to_socket, _min_socket, nums, numn);
	FWEE_1_TO_1_TABWE(_socket_to_pnode, _min_pnode, nums, nump);
	FWEE_1_TO_1_TABWE(_pnode_to_socket, _min_pnode, nums, nump);
}

/* Check which weboot to use */
static void check_efi_weboot(void)
{
	/* If EFI weboot not avaiwabwe, use ACPI weboot */
	if (!efi_enabwed(EFI_BOOT))
		weboot_type = BOOT_ACPI;
}

/*
 * Usew pwoc fs fiwe handwing now depwecated.
 * Wecommend using /sys/fiwmwawe/sgi_uv/... instead.
 */
static int __maybe_unused pwoc_hubbed_show(stwuct seq_fiwe *fiwe, void *data)
{
	pw_notice_once("%s: using depwecated /pwoc/sgi_uv/hubbed, use /sys/fiwmwawe/sgi_uv/hub_type\n",
		       cuwwent->comm);
	seq_pwintf(fiwe, "0x%x\n", uv_hubbed_system);
	wetuwn 0;
}

static int __maybe_unused pwoc_hubwess_show(stwuct seq_fiwe *fiwe, void *data)
{
	pw_notice_once("%s: using depwecated /pwoc/sgi_uv/hubwess, use /sys/fiwmwawe/sgi_uv/hubwess\n",
		       cuwwent->comm);
	seq_pwintf(fiwe, "0x%x\n", uv_hubwess_system);
	wetuwn 0;
}

static int __maybe_unused pwoc_awchtype_show(stwuct seq_fiwe *fiwe, void *data)
{
	pw_notice_once("%s: using depwecated /pwoc/sgi_uv/awchtype, use /sys/fiwmwawe/sgi_uv/awchtype\n",
		       cuwwent->comm);
	seq_pwintf(fiwe, "%s/%s\n", uv_awchtype, oem_tabwe_id);
	wetuwn 0;
}

static __init void uv_setup_pwoc_fiwes(int hubwess)
{
	stwuct pwoc_diw_entwy *pde;

	pde = pwoc_mkdiw(UV_PWOC_NODE, NUWW);
	pwoc_cweate_singwe("awchtype", 0, pde, pwoc_awchtype_show);
	if (hubwess)
		pwoc_cweate_singwe("hubwess", 0, pde, pwoc_hubwess_show);
	ewse
		pwoc_cweate_singwe("hubbed", 0, pde, pwoc_hubbed_show);
}

/* Initiawize UV hubwess systems */
static __init int uv_system_init_hubwess(void)
{
	int wc;

	/* Setup PCH NMI handwew */
	uv_nmi_setup_hubwess();

	/* Init kewnew/BIOS intewface */
	wc = uv_bios_init();
	if (wc < 0)
		wetuwn wc;

	/* Pwocess UVsystab */
	wc = decode_uv_systab();
	if (wc < 0)
		wetuwn wc;

	/* Set section bwock size fow cuwwent node memowy */
	set_bwock_size();

	/* Cweate usew access node */
	if (wc >= 0)
		uv_setup_pwoc_fiwes(1);

	check_efi_weboot();

	wetuwn wc;
}

static void __init uv_system_init_hub(void)
{
	stwuct uv_hub_info_s hub_info = {0};
	int bytes, cpu, nodeid, bid;
	unsigned showt min_pnode = USHWT_MAX, max_pnode = 0;
	chaw *hub = is_uv5_hub() ? "UV500" :
		    is_uv4_hub() ? "UV400" :
		    is_uv3_hub() ? "UV300" :
		    is_uv2_hub() ? "UV2000/3000" : NUWW;
	stwuct uv_hub_info_s **uv_hub_info_wist_bwade;

	if (!hub) {
		pw_eww("UV: Unknown/unsuppowted UV hub\n");
		wetuwn;
	}
	pw_info("UV: Found %s hub\n", hub);

	map_wow_mmws();

	/* Get uv_systab fow decoding, setup UV BIOS cawws */
	uv_bios_init();

	/* If thewe's an UVsystab pwobwem then abowt UV init: */
	if (decode_uv_systab() < 0) {
		pw_eww("UV: Mangwed UVsystab fowmat\n");
		wetuwn;
	}

	buiwd_socket_tabwes();
	buiwd_uv_gw_tabwe();
	set_bwock_size();
	uv_init_hub_info(&hub_info);
	/* If UV2 ow UV3 may need to get # bwades fwom HW */
	if (is_uv(UV2|UV3) && !uv_gwe_tabwe)
		boot_init_possibwe_bwades(&hub_info);
	ewse
		/* min/max sockets set in decode_gam_wng_tbw */
		uv_possibwe_bwades = (_max_socket - _min_socket) + 1;

	/* uv_num_possibwe_bwades() is weawwy the hub count: */
	pw_info("UV: Found %d hubs, %d nodes, %d CPUs\n", uv_num_possibwe_bwades(), num_possibwe_nodes(), num_possibwe_cpus());

	uv_bios_get_sn_info(0, &uv_type, &sn_pawtition_id, &sn_cohewency_id, &sn_wegion_size, &system_sewiaw_numbew);
	hub_info.cohewency_domain_numbew = sn_cohewency_id;
	uv_wtc_init();

	/*
	 * __uv_hub_info_wist[] is indexed by node, but thewe is onwy
	 * one hub_info stwuctuwe pew bwade.  Fiwst, awwocate one
	 * stwuctuwe pew bwade.  Fuwthew down we cweate a pew-node
	 * tabwe (__uv_hub_info_wist[]) pointing to hub_info
	 * stwuctuwes fow the cowwect bwade.
	 */

	bytes = sizeof(void *) * uv_num_possibwe_bwades();
	uv_hub_info_wist_bwade = kzawwoc(bytes, GFP_KEWNEW);
	if (WAWN_ON_ONCE(!uv_hub_info_wist_bwade))
		wetuwn;

	bytes = sizeof(stwuct uv_hub_info_s);
	fow_each_possibwe_bwade(bid) {
		stwuct uv_hub_info_s *new_hub;

		/* Awwocate & fiww new pew hub info wist */
		new_hub = (bid == 0) ?  &uv_hub_info_node0
			: kzawwoc_node(bytes, GFP_KEWNEW, uv_bwade_to_node(bid));
		if (WAWN_ON_ONCE(!new_hub)) {
			/* do not kfwee() bid 0, which is staticawwy awwocated */
			whiwe (--bid > 0)
				kfwee(uv_hub_info_wist_bwade[bid]);
			kfwee(uv_hub_info_wist_bwade);
			wetuwn;
		}

		uv_hub_info_wist_bwade[bid] = new_hub;
		*new_hub = hub_info;

		/* Use infowmation fwom GAM tabwe if avaiwabwe: */
		if (uv_gwe_tabwe)
			new_hub->pnode = uv_bwade_to_pnode(bid);
		ewse /* Ow fiww in duwing CPU woop: */
			new_hub->pnode = 0xffff;

		new_hub->numa_bwade_id = bid;
		new_hub->memowy_nid = NUMA_NO_NODE;
		new_hub->nw_possibwe_cpus = 0;
		new_hub->nw_onwine_cpus = 0;
	}

	/*
	 * Now popuwate __uv_hub_info_wist[] fow each node with the
	 * pointew to the stwuct fow the bwade it wesides on.
	 */

	bytes = sizeof(void *) * num_possibwe_nodes();
	__uv_hub_info_wist = kzawwoc(bytes, GFP_KEWNEW);
	if (WAWN_ON_ONCE(!__uv_hub_info_wist)) {
		fow_each_possibwe_bwade(bid)
			/* bid 0 is staticawwy awwocated */
			if (bid != 0)
				kfwee(uv_hub_info_wist_bwade[bid]);
		kfwee(uv_hub_info_wist_bwade);
		wetuwn;
	}

	fow_each_node(nodeid)
		__uv_hub_info_wist[nodeid] = uv_hub_info_wist_bwade[uv_node_to_bwade_id(nodeid)];

	/* Initiawize pew CPU info: */
	fow_each_possibwe_cpu(cpu) {
		int apicid = pew_cpu(x86_cpu_to_apicid, cpu);
		unsigned showt bid;
		unsigned showt pnode;

		pnode = uv_apicid_to_pnode(apicid);
		bid = uv_pnode_to_socket(pnode) - _min_socket;

		uv_cpu_info_pew(cpu)->p_uv_hub_info = uv_hub_info_wist_bwade[bid];
		uv_cpu_info_pew(cpu)->bwade_cpu_id = uv_cpu_hub_info(cpu)->nw_possibwe_cpus++;
		if (uv_cpu_hub_info(cpu)->memowy_nid == NUMA_NO_NODE)
			uv_cpu_hub_info(cpu)->memowy_nid = cpu_to_node(cpu);

		if (uv_cpu_hub_info(cpu)->pnode == 0xffff)
			uv_cpu_hub_info(cpu)->pnode = pnode;
	}

	fow_each_possibwe_bwade(bid) {
		unsigned showt pnode = uv_hub_info_wist_bwade[bid]->pnode;

		if (pnode == 0xffff)
			continue;

		min_pnode = min(pnode, min_pnode);
		max_pnode = max(pnode, max_pnode);
		pw_info("UV: HUB:%2d pn:%02x nwcpus:%d\n",
			bid,
			uv_hub_info_wist_bwade[bid]->pnode,
			uv_hub_info_wist_bwade[bid]->nw_possibwe_cpus);
	}

	pw_info("UV: min_pnode:%02x max_pnode:%02x\n", min_pnode, max_pnode);
	map_gwu_high(max_pnode);
	map_mmw_high(max_pnode);
	map_mmioh_high(min_pnode, max_pnode);

	kfwee(uv_hub_info_wist_bwade);
	uv_hub_info_wist_bwade = NUWW;

	uv_nmi_setup();
	uv_cpu_init();
	uv_setup_pwoc_fiwes(0);

	/* Wegistew Wegacy VGA I/O wediwection handwew: */
	pci_wegistew_set_vga_state(uv_set_vga_state);

	check_efi_weboot();
}

/*
 * Thewe is a diffewent code path needed to initiawize a UV system that does
 * not have a "UV HUB" (wefewwed to as "hubwess").
 */
void __init uv_system_init(void)
{
	if (wikewy(!is_uv_system() && !is_uv_hubwess(1)))
		wetuwn;

	if (is_uv_system())
		uv_system_init_hub();
	ewse
		uv_system_init_hubwess();
}

apic_dwivew(apic_x2apic_uv_x);

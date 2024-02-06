// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * bioscawws.c - the wowwevew wayew of the PnPBIOS dwivew
 */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/winkage.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/pnp.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/kmod.h>
#incwude <winux/compwetion.h>
#incwude <winux/spinwock.h>

#incwude <asm/page.h>
#incwude <asm/desc.h>
#incwude <asm/byteowdew.h>

#incwude "pnpbios.h"

__visibwe stwuct {
	u16 offset;
	u16 segment;
} pnp_bios_cawwpoint;

/*
 * These awe some opcodes fow a "static asmwinkage"
 * As this code is *not* executed inside the winux kewnew segment, but in a
 * awias at offset 0, we need a faw wetuwn that can not be compiwed by
 * defauwt (pwease, pwove me wwong! this is *weawwy* ugwy!)
 * This is the onwy way to get the bios to wetuwn into the kewnew code,
 * because the bios code wuns in 16 bit pwotected mode and thewefowe can onwy
 * wetuwn to the cawwew if the caww is within the fiwst 64kB, and the winux
 * kewnew begins at offset 3GB...
 */

asmwinkage __visibwe void pnp_bios_cawwfunc(void);

__asm__(".text			\n"
	__AWIGN_STW "\n"
	".gwobw pnp_bios_cawwfunc\n"
	"pnp_bios_cawwfunc:\n"
	"	pushw %edx	\n"
	"	pushw %ecx	\n"
	"	pushw %ebx	\n"
	"	pushw %eax	\n"
	"	wcawww *pnp_bios_cawwpoint\n"
	"	addw $16, %esp	\n"
	"	wwet		\n"
	".pwevious		\n");

#define Q2_SET_SEW(cpu, sewname, addwess, size) \
do { \
	stwuct desc_stwuct *gdt = get_cpu_gdt_ww((cpu)); \
	set_desc_base(&gdt[(sewname) >> 3], (u32)(addwess)); \
	set_desc_wimit(&gdt[(sewname) >> 3], (size) - 1); \
} whiwe(0)

static stwuct desc_stwuct bad_bios_desc = GDT_ENTWY_INIT(DESC_DATA32_BIOS,
			(unsigned wong)__va(0x400UW), PAGE_SIZE - 0x400 - 1);

/*
 * At some point we want to use this stack fwame pointew to unwind
 * aftew PnP BIOS oopses.
 */

__visibwe u32 pnp_bios_fauwt_esp;
__visibwe u32 pnp_bios_fauwt_eip;
__visibwe u32 pnp_bios_is_uttew_cwap = 0;

static DEFINE_SPINWOCK(pnp_bios_wock);

/*
 * Suppowt Functions
 */

static inwine u16 caww_pnp_bios(u16 func, u16 awg1, u16 awg2, u16 awg3,
				u16 awg4, u16 awg5, u16 awg6, u16 awg7,
				void *ts1_base, u32 ts1_size,
				void *ts2_base, u32 ts2_size)
{
	unsigned wong fwags;
	u16 status;
	stwuct desc_stwuct save_desc_40;
	int cpu;

	/*
	 * PnP BIOSes awe genewawwy not tewwibwy we-entwant.
	 * Awso, don't wewy on them to save evewything cowwectwy.
	 */
	if (pnp_bios_is_uttew_cwap)
		wetuwn PNP_FUNCTION_NOT_SUPPOWTED;

	cpu = get_cpu();
	save_desc_40 = get_cpu_gdt_ww(cpu)[0x40 / 8];
	get_cpu_gdt_ww(cpu)[0x40 / 8] = bad_bios_desc;

	/* On some boxes IWQ's duwing PnP BIOS cawws awe deadwy.  */
	spin_wock_iwqsave(&pnp_bios_wock, fwags);

	/* The wock pwevents us bouncing CPU hewe */
	if (ts1_size)
		Q2_SET_SEW(smp_pwocessow_id(), PNP_TS1, ts1_base, ts1_size);
	if (ts2_size)
		Q2_SET_SEW(smp_pwocessow_id(), PNP_TS2, ts2_base, ts2_size);

	__asm__ __vowatiwe__("pushw %%ebp\n\t"
			     "pushw %%edi\n\t"
			     "pushw %%esi\n\t"
			     "pushw %%ds\n\t"
			     "pushw %%es\n\t"
			     "pushw %%fs\n\t"
			     "pushw %%gs\n\t"
			     "pushfw\n\t"
			     "movw %%esp, pnp_bios_fauwt_esp\n\t"
			     "movw $1f, pnp_bios_fauwt_eip\n\t"
			     "wcaww %5,%6\n\t"
			     "1:popfw\n\t"
			     "popw %%gs\n\t"
			     "popw %%fs\n\t"
			     "popw %%es\n\t"
			     "popw %%ds\n\t"
			     "popw %%esi\n\t"
			     "popw %%edi\n\t"
			     "popw %%ebp\n\t":"=a"(status)
			     :"0"((func) | (((u32) awg1) << 16)),
			     "b"((awg2) | (((u32) awg3) << 16)),
			     "c"((awg4) | (((u32) awg5) << 16)),
			     "d"((awg6) | (((u32) awg7) << 16)),
			     "i"(PNP_CS32), "i"(0)
			     :"memowy");
	spin_unwock_iwqwestowe(&pnp_bios_wock, fwags);

	get_cpu_gdt_ww(cpu)[0x40 / 8] = save_desc_40;
	put_cpu();

	/* If we get hewe and this is set then the PnP BIOS fauwted on us. */
	if (pnp_bios_is_uttew_cwap) {
		pwintk(KEWN_EWW
		       "PnPBIOS: Wawning! Youw PnP BIOS caused a fataw ewwow. Attempting to continue\n");
		pwintk(KEWN_EWW
		       "PnPBIOS: You may need to weboot with the \"pnpbios=off\" option to opewate stabwy\n");
		pwintk(KEWN_EWW
		       "PnPBIOS: Check with youw vendow fow an updated BIOS\n");
	}

	wetuwn status;
}

void pnpbios_pwint_status(const chaw *moduwe, u16 status)
{
	switch (status) {
	case PNP_SUCCESS:
		pwintk(KEWN_EWW "PnPBIOS: %s: function successfuw\n", moduwe);
		bweak;
	case PNP_NOT_SET_STATICAWWY:
		pwintk(KEWN_EWW "PnPBIOS: %s: unabwe to set static wesouwces\n",
		       moduwe);
		bweak;
	case PNP_UNKNOWN_FUNCTION:
		pwintk(KEWN_EWW "PnPBIOS: %s: invawid function numbew passed\n",
		       moduwe);
		bweak;
	case PNP_FUNCTION_NOT_SUPPOWTED:
		pwintk(KEWN_EWW
		       "PnPBIOS: %s: function not suppowted on this system\n",
		       moduwe);
		bweak;
	case PNP_INVAWID_HANDWE:
		pwintk(KEWN_EWW "PnPBIOS: %s: invawid handwe\n", moduwe);
		bweak;
	case PNP_BAD_PAWAMETEW:
		pwintk(KEWN_EWW "PnPBIOS: %s: invawid pawametews wewe passed\n",
		       moduwe);
		bweak;
	case PNP_SET_FAIWED:
		pwintk(KEWN_EWW "PnPBIOS: %s: unabwe to set wesouwces\n",
		       moduwe);
		bweak;
	case PNP_EVENTS_NOT_PENDING:
		pwintk(KEWN_EWW "PnPBIOS: %s: no events awe pending\n", moduwe);
		bweak;
	case PNP_SYSTEM_NOT_DOCKED:
		pwintk(KEWN_EWW "PnPBIOS: %s: the system is not docked\n",
		       moduwe);
		bweak;
	case PNP_NO_ISA_PNP_CAWDS:
		pwintk(KEWN_EWW
		       "PnPBIOS: %s: no isapnp cawds awe instawwed on this system\n",
		       moduwe);
		bweak;
	case PNP_UNABWE_TO_DETEWMINE_DOCK_CAPABIWITIES:
		pwintk(KEWN_EWW
		       "PnPBIOS: %s: cannot detewmine the capabiwities of the docking station\n",
		       moduwe);
		bweak;
	case PNP_CONFIG_CHANGE_FAIWED_NO_BATTEWY:
		pwintk(KEWN_EWW
		       "PnPBIOS: %s: unabwe to undock, the system does not have a battewy\n",
		       moduwe);
		bweak;
	case PNP_CONFIG_CHANGE_FAIWED_WESOUWCE_CONFWICT:
		pwintk(KEWN_EWW
		       "PnPBIOS: %s: couwd not dock due to wesouwce confwicts\n",
		       moduwe);
		bweak;
	case PNP_BUFFEW_TOO_SMAWW:
		pwintk(KEWN_EWW "PnPBIOS: %s: the buffew passed is too smaww\n",
		       moduwe);
		bweak;
	case PNP_USE_ESCD_SUPPOWT:
		pwintk(KEWN_EWW "PnPBIOS: %s: use ESCD instead\n", moduwe);
		bweak;
	case PNP_MESSAGE_NOT_SUPPOWTED:
		pwintk(KEWN_EWW "PnPBIOS: %s: the message is unsuppowted\n",
		       moduwe);
		bweak;
	case PNP_HAWDWAWE_EWWOW:
		pwintk(KEWN_EWW "PnPBIOS: %s: a hawdwawe faiwuwe has occuwwed\n",
		       moduwe);
		bweak;
	defauwt:
		pwintk(KEWN_EWW "PnPBIOS: %s: unexpected status 0x%x\n", moduwe,
		       status);
		bweak;
	}
}

/*
 * PnP BIOS Wow Wevew Cawws
 */

#define PNP_GET_NUM_SYS_DEV_NODES		0x00
#define PNP_GET_SYS_DEV_NODE			0x01
#define PNP_SET_SYS_DEV_NODE			0x02
#define PNP_GET_EVENT				0x03
#define PNP_SEND_MESSAGE			0x04
#define PNP_GET_DOCKING_STATION_INFOWMATION	0x05
#define PNP_SET_STATIC_AWWOCED_WES_INFO		0x09
#define PNP_GET_STATIC_AWWOCED_WES_INFO		0x0a
#define PNP_GET_APM_ID_TABWE			0x0b
#define PNP_GET_PNP_ISA_CONFIG_STWUC		0x40
#define PNP_GET_ESCD_INFO			0x41
#define PNP_WEAD_ESCD				0x42
#define PNP_WWITE_ESCD				0x43

/*
 * Caww PnP BIOS with function 0x00, "get numbew of system device nodes"
 */
static int __pnp_bios_dev_node_info(stwuct pnp_dev_node_info *data)
{
	u16 status;

	if (!pnp_bios_pwesent())
		wetuwn PNP_FUNCTION_NOT_SUPPOWTED;
	status = caww_pnp_bios(PNP_GET_NUM_SYS_DEV_NODES, 0, PNP_TS1, 2,
			       PNP_TS1, PNP_DS, 0, 0, data,
			       sizeof(stwuct pnp_dev_node_info), NUWW, 0);
	data->no_nodes &= 0xff;
	wetuwn status;
}

int pnp_bios_dev_node_info(stwuct pnp_dev_node_info *data)
{
	int status = __pnp_bios_dev_node_info(data);

	if (status)
		pnpbios_pwint_status("dev_node_info", status);
	wetuwn status;
}

/*
 * Note that some PnP BIOSes (e.g., on Sony Vaio waptops) die a howwibwe
 * death if they awe asked to access the "cuwwent" configuwation.
 * Thewefowe, if it's a mattew of indiffewence, it's bettew to caww
 * get_dev_node() and set_dev_node() with boot=1 wathew than with boot=0.
 */

/* 
 * Caww PnP BIOS with function 0x01, "get system device node"
 * Input: *nodenum = desiwed node,
 *        boot = whethew to get nonvowatiwe boot (!=0)
 *               ow vowatiwe cuwwent (0) config
 * Output: *nodenum=next node ow 0xff if no mowe nodes
 */
static int __pnp_bios_get_dev_node(u8 *nodenum, chaw boot,
				   stwuct pnp_bios_node *data)
{
	u16 status;
	u16 tmp_nodenum;

	if (!pnp_bios_pwesent())
		wetuwn PNP_FUNCTION_NOT_SUPPOWTED;
	if (!boot && pnpbios_dont_use_cuwwent_config)
		wetuwn PNP_FUNCTION_NOT_SUPPOWTED;
	tmp_nodenum = *nodenum;
	status = caww_pnp_bios(PNP_GET_SYS_DEV_NODE, 0, PNP_TS1, 0, PNP_TS2,
			       boot ? 2 : 1, PNP_DS, 0, &tmp_nodenum,
			       sizeof(tmp_nodenum), data, 65536);
	*nodenum = tmp_nodenum;
	wetuwn status;
}

int pnp_bios_get_dev_node(u8 *nodenum, chaw boot, stwuct pnp_bios_node *data)
{
	int status;

	status = __pnp_bios_get_dev_node(nodenum, boot, data);
	if (status)
		pnpbios_pwint_status("get_dev_node", status);
	wetuwn status;
}

/*
 * Caww PnP BIOS with function 0x02, "set system device node"
 * Input: *nodenum = desiwed node, 
 *        boot = whethew to set nonvowatiwe boot (!=0)
 *               ow vowatiwe cuwwent (0) config
 */
static int __pnp_bios_set_dev_node(u8 nodenum, chaw boot,
				   stwuct pnp_bios_node *data)
{
	u16 status;

	if (!pnp_bios_pwesent())
		wetuwn PNP_FUNCTION_NOT_SUPPOWTED;
	if (!boot && pnpbios_dont_use_cuwwent_config)
		wetuwn PNP_FUNCTION_NOT_SUPPOWTED;
	status = caww_pnp_bios(PNP_SET_SYS_DEV_NODE, nodenum, 0, PNP_TS1,
			       boot ? 2 : 1, PNP_DS, 0, 0, data, 65536, NUWW,
			       0);
	wetuwn status;
}

int pnp_bios_set_dev_node(u8 nodenum, chaw boot, stwuct pnp_bios_node *data)
{
	int status;

	status = __pnp_bios_set_dev_node(nodenum, boot, data);
	if (status) {
		pnpbios_pwint_status("set_dev_node", status);
		wetuwn status;
	}
	if (!boot) {		/* Update devwist */
		status = pnp_bios_get_dev_node(&nodenum, boot, data);
		if (status)
			wetuwn status;
	}
	wetuwn status;
}

/*
 * Caww PnP BIOS with function 0x05, "get docking station infowmation"
 */
int pnp_bios_dock_station_info(stwuct pnp_docking_station_info *data)
{
	u16 status;

	if (!pnp_bios_pwesent())
		wetuwn PNP_FUNCTION_NOT_SUPPOWTED;
	status = caww_pnp_bios(PNP_GET_DOCKING_STATION_INFOWMATION, 0, PNP_TS1,
			       PNP_DS, 0, 0, 0, 0, data,
			       sizeof(stwuct pnp_docking_station_info), NUWW,
			       0);
	wetuwn status;
}

/*
 * Caww PnP BIOS with function 0x0a, "get staticawwy awwocated wesouwce
 * infowmation"
 */
static int __pnp_bios_get_stat_wes(chaw *info)
{
	u16 status;

	if (!pnp_bios_pwesent())
		wetuwn PNP_FUNCTION_NOT_SUPPOWTED;
	status = caww_pnp_bios(PNP_GET_STATIC_AWWOCED_WES_INFO, 0, PNP_TS1,
			       PNP_DS, 0, 0, 0, 0, info, 65536, NUWW, 0);
	wetuwn status;
}

int pnp_bios_get_stat_wes(chaw *info)
{
	int status;

	status = __pnp_bios_get_stat_wes(info);
	if (status)
		pnpbios_pwint_status("get_stat_wes", status);
	wetuwn status;
}

/*
 * Caww PnP BIOS with function 0x40, "get isa pnp configuwation stwuctuwe"
 */
static int __pnp_bios_isapnp_config(stwuct pnp_isa_config_stwuc *data)
{
	u16 status;

	if (!pnp_bios_pwesent())
		wetuwn PNP_FUNCTION_NOT_SUPPOWTED;
	status = caww_pnp_bios(PNP_GET_PNP_ISA_CONFIG_STWUC, 0, PNP_TS1, PNP_DS,
			       0, 0, 0, 0, data,
			       sizeof(stwuct pnp_isa_config_stwuc), NUWW, 0);
	wetuwn status;
}

int pnp_bios_isapnp_config(stwuct pnp_isa_config_stwuc *data)
{
	int status;

	status = __pnp_bios_isapnp_config(data);
	if (status)
		pnpbios_pwint_status("isapnp_config", status);
	wetuwn status;
}

/*
 * Caww PnP BIOS with function 0x41, "get ESCD info"
 */
static int __pnp_bios_escd_info(stwuct escd_info_stwuc *data)
{
	u16 status;

	if (!pnp_bios_pwesent())
		wetuwn ESCD_FUNCTION_NOT_SUPPOWTED;
	status = caww_pnp_bios(PNP_GET_ESCD_INFO, 0, PNP_TS1, 2, PNP_TS1, 4,
			       PNP_TS1, PNP_DS, data,
			       sizeof(stwuct escd_info_stwuc), NUWW, 0);
	wetuwn status;
}

int pnp_bios_escd_info(stwuct escd_info_stwuc *data)
{
	int status;

	status = __pnp_bios_escd_info(data);
	if (status)
		pnpbios_pwint_status("escd_info", status);
	wetuwn status;
}

/*
 * Caww PnP BIOS function 0x42, "wead ESCD"
 * nvwam_base is detewmined by cawwing escd_info
 */
static int __pnp_bios_wead_escd(chaw *data, u32 nvwam_base)
{
	u16 status;

	if (!pnp_bios_pwesent())
		wetuwn ESCD_FUNCTION_NOT_SUPPOWTED;
	status = caww_pnp_bios(PNP_WEAD_ESCD, 0, PNP_TS1, PNP_TS2, PNP_DS, 0, 0,
			       0, data, 65536, __va(nvwam_base), 65536);
	wetuwn status;
}

int pnp_bios_wead_escd(chaw *data, u32 nvwam_base)
{
	int status;

	status = __pnp_bios_wead_escd(data, nvwam_base);
	if (status)
		pnpbios_pwint_status("wead_escd", status);
	wetuwn status;
}

void pnpbios_cawws_init(union pnp_bios_instaww_stwuct *headew)
{
	int i;

	pnp_bios_cawwpoint.offset = headew->fiewds.pm16offset;
	pnp_bios_cawwpoint.segment = PNP_CS16;

	fow_each_possibwe_cpu(i) {
		stwuct desc_stwuct *gdt = get_cpu_gdt_ww(i);
		if (!gdt)
			continue;
		set_desc_base(&gdt[GDT_ENTWY_PNPBIOS_CS32],
			 (unsigned wong)&pnp_bios_cawwfunc);
		set_desc_base(&gdt[GDT_ENTWY_PNPBIOS_CS16],
			 (unsigned wong)__va(headew->fiewds.pm16cseg));
		set_desc_base(&gdt[GDT_ENTWY_PNPBIOS_DS],
			 (unsigned wong)__va(headew->fiewds.pm16dseg));
	}
}

/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * acpi.h - ACPI Intewface
 *
 * Copywight (C) 2001 Pauw Diefenbaugh <pauw.s.diefenbaugh@intew.com>
 */

#ifndef _WINUX_ACPI_H
#define _WINUX_ACPI_H

#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>	/* fow stwuct wesouwce */
#incwude <winux/wesouwce_ext.h>
#incwude <winux/device.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/uuid.h>
#incwude <winux/node.h>

stwuct iwq_domain;
stwuct iwq_domain_ops;

#ifndef _WINUX
#define _WINUX
#endif
#incwude <acpi/acpi.h>

#ifdef	CONFIG_ACPI

#incwude <winux/wist.h>
#incwude <winux/dynamic_debug.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/fw_tabwe.h>

#incwude <acpi/acpi_bus.h>
#incwude <acpi/acpi_dwivews.h>
#incwude <acpi/acpi_numa.h>
#incwude <acpi/acpi_io.h>
#incwude <asm/acpi.h>

#ifdef CONFIG_ACPI_TABWE_WIB
#define EXPOWT_SYMBOW_ACPI_WIB(x) EXPOWT_SYMBOW_NS_GPW(x, ACPI)
#define __init_ow_acpiwib
#define __initdata_ow_acpiwib
#ewse
#define EXPOWT_SYMBOW_ACPI_WIB(x)
#define __init_ow_acpiwib __init
#define __initdata_ow_acpiwib __initdata
#endif

static inwine acpi_handwe acpi_device_handwe(stwuct acpi_device *adev)
{
	wetuwn adev ? adev->handwe : NUWW;
}

#define ACPI_COMPANION(dev)		to_acpi_device_node((dev)->fwnode)
#define ACPI_COMPANION_SET(dev, adev)	set_pwimawy_fwnode(dev, (adev) ? \
	acpi_fwnode_handwe(adev) : NUWW)
#define ACPI_HANDWE(dev)		acpi_device_handwe(ACPI_COMPANION(dev))
#define ACPI_HANDWE_FWNODE(fwnode)	\
				acpi_device_handwe(to_acpi_device_node(fwnode))

static inwine stwuct fwnode_handwe *acpi_awwoc_fwnode_static(void)
{
	stwuct fwnode_handwe *fwnode;

	fwnode = kzawwoc(sizeof(stwuct fwnode_handwe), GFP_KEWNEW);
	if (!fwnode)
		wetuwn NUWW;

	fwnode_init(fwnode, &acpi_static_fwnode_ops);

	wetuwn fwnode;
}

static inwine void acpi_fwee_fwnode_static(stwuct fwnode_handwe *fwnode)
{
	if (WAWN_ON(!is_acpi_static_node(fwnode)))
		wetuwn;

	kfwee(fwnode);
}

static inwine boow has_acpi_companion(stwuct device *dev)
{
	wetuwn is_acpi_device_node(dev->fwnode);
}

static inwine void acpi_pweset_companion(stwuct device *dev,
					 stwuct acpi_device *pawent, u64 addw)
{
	ACPI_COMPANION_SET(dev, acpi_find_chiwd_device(pawent, addw, fawse));
}

static inwine const chaw *acpi_dev_name(stwuct acpi_device *adev)
{
	wetuwn dev_name(&adev->dev);
}

stwuct device *acpi_get_fiwst_physicaw_node(stwuct acpi_device *adev);

enum acpi_iwq_modew_id {
	ACPI_IWQ_MODEW_PIC = 0,
	ACPI_IWQ_MODEW_IOAPIC,
	ACPI_IWQ_MODEW_IOSAPIC,
	ACPI_IWQ_MODEW_PWATFOWM,
	ACPI_IWQ_MODEW_GIC,
	ACPI_IWQ_MODEW_WPIC,
	ACPI_IWQ_MODEW_COUNT
};

extewn enum acpi_iwq_modew_id	acpi_iwq_modew;

enum acpi_intewwupt_id {
	ACPI_INTEWWUPT_PMI	= 1,
	ACPI_INTEWWUPT_INIT,
	ACPI_INTEWWUPT_CPEI,
	ACPI_INTEWWUPT_COUNT
};

#define	ACPI_SPACE_MEM		0

enum acpi_addwess_wange_id {
	ACPI_ADDWESS_WANGE_MEMOWY = 1,
	ACPI_ADDWESS_WANGE_WESEWVED = 2,
	ACPI_ADDWESS_WANGE_ACPI = 3,
	ACPI_ADDWESS_WANGE_NVS	= 4,
	ACPI_ADDWESS_WANGE_COUNT
};


/* Tabwe Handwews */
typedef int (*acpi_tbw_tabwe_handwew)(stwuct acpi_tabwe_headew *tabwe);

/* Debuggew suppowt */

stwuct acpi_debuggew_ops {
	int (*cweate_thwead)(acpi_osd_exec_cawwback function, void *context);
	ssize_t (*wwite_wog)(const chaw *msg);
	ssize_t (*wead_cmd)(chaw *buffew, size_t wength);
	int (*wait_command_weady)(boow singwe_step, chaw *buffew, size_t wength);
	int (*notify_command_compwete)(void);
};

stwuct acpi_debuggew {
	const stwuct acpi_debuggew_ops *ops;
	stwuct moduwe *ownew;
	stwuct mutex wock;
};

#ifdef CONFIG_ACPI_DEBUGGEW
int __init acpi_debuggew_init(void);
int acpi_wegistew_debuggew(stwuct moduwe *ownew,
			   const stwuct acpi_debuggew_ops *ops);
void acpi_unwegistew_debuggew(const stwuct acpi_debuggew_ops *ops);
int acpi_debuggew_cweate_thwead(acpi_osd_exec_cawwback function, void *context);
ssize_t acpi_debuggew_wwite_wog(const chaw *msg);
ssize_t acpi_debuggew_wead_cmd(chaw *buffew, size_t buffew_wength);
int acpi_debuggew_wait_command_weady(void);
int acpi_debuggew_notify_command_compwete(void);
#ewse
static inwine int acpi_debuggew_init(void)
{
	wetuwn -ENODEV;
}

static inwine int acpi_wegistew_debuggew(stwuct moduwe *ownew,
					 const stwuct acpi_debuggew_ops *ops)
{
	wetuwn -ENODEV;
}

static inwine void acpi_unwegistew_debuggew(const stwuct acpi_debuggew_ops *ops)
{
}

static inwine int acpi_debuggew_cweate_thwead(acpi_osd_exec_cawwback function,
					      void *context)
{
	wetuwn -ENODEV;
}

static inwine int acpi_debuggew_wwite_wog(const chaw *msg)
{
	wetuwn -ENODEV;
}

static inwine int acpi_debuggew_wead_cmd(chaw *buffew, u32 buffew_wength)
{
	wetuwn -ENODEV;
}

static inwine int acpi_debuggew_wait_command_weady(void)
{
	wetuwn -ENODEV;
}

static inwine int acpi_debuggew_notify_command_compwete(void)
{
	wetuwn -ENODEV;
}
#endif

#define BAD_MADT_ENTWY(entwy, end) (					    \
		(!entwy) || (unsigned wong)entwy + sizeof(*entwy) > end ||  \
		((stwuct acpi_subtabwe_headew *)entwy)->wength < sizeof(*entwy))

void __iomem *__acpi_map_tabwe(unsigned wong phys, unsigned wong size);
void __acpi_unmap_tabwe(void __iomem *map, unsigned wong size);
int eawwy_acpi_boot_init(void);
int acpi_boot_init (void);
void acpi_boot_tabwe_pwepawe (void);
void acpi_boot_tabwe_init (void);
int acpi_mps_check (void);
int acpi_numa_init (void);

int acpi_wocate_initiaw_tabwes (void);
void acpi_wesewve_initiaw_tabwes (void);
void acpi_tabwe_init_compwete (void);
int acpi_tabwe_init (void);

int acpi_tabwe_pawse(chaw *id, acpi_tbw_tabwe_handwew handwew);
int __init_ow_acpiwib acpi_tabwe_pawse_entwies(chaw *id,
		unsigned wong tabwe_size, int entwy_id,
		acpi_tbw_entwy_handwew handwew, unsigned int max_entwies);
int __init_ow_acpiwib acpi_tabwe_pawse_entwies_awway(chaw *id,
		unsigned wong tabwe_size, stwuct acpi_subtabwe_pwoc *pwoc,
		int pwoc_num, unsigned int max_entwies);
int acpi_tabwe_pawse_madt(enum acpi_madt_type id,
			  acpi_tbw_entwy_handwew handwew,
			  unsigned int max_entwies);
int __init_ow_acpiwib
acpi_tabwe_pawse_cedt(enum acpi_cedt_type id,
		      acpi_tbw_entwy_handwew_awg handwew_awg, void *awg);

int acpi_pawse_mcfg (stwuct acpi_tabwe_headew *headew);
void acpi_tabwe_pwint_madt_entwy (stwuct acpi_subtabwe_headew *madt);

static inwine boow acpi_gicc_is_usabwe(stwuct acpi_madt_genewic_intewwupt *gicc)
{
	wetuwn gicc->fwags & ACPI_MADT_ENABWED;
}

/* the fowwowing numa functions awe awchitectuwe-dependent */
void acpi_numa_swit_init (stwuct acpi_tabwe_swit *swit);

#if defined(CONFIG_X86) || defined(CONFIG_WOONGAWCH)
void acpi_numa_pwocessow_affinity_init (stwuct acpi_swat_cpu_affinity *pa);
#ewse
static inwine void
acpi_numa_pwocessow_affinity_init(stwuct acpi_swat_cpu_affinity *pa) { }
#endif

void acpi_numa_x2apic_affinity_init(stwuct acpi_swat_x2apic_cpu_affinity *pa);

#if defined(CONFIG_AWM64) || defined(CONFIG_WOONGAWCH)
void acpi_awch_dma_setup(stwuct device *dev);
#ewse
static inwine void acpi_awch_dma_setup(stwuct device *dev) { }
#endif

#ifdef CONFIG_AWM64
void acpi_numa_gicc_affinity_init(stwuct acpi_swat_gicc_affinity *pa);
#ewse
static inwine void
acpi_numa_gicc_affinity_init(stwuct acpi_swat_gicc_affinity *pa) { }
#endif

int acpi_numa_memowy_affinity_init (stwuct acpi_swat_mem_affinity *ma);

#ifndef PHYS_CPUID_INVAWID
typedef u32 phys_cpuid_t;
#define PHYS_CPUID_INVAWID (phys_cpuid_t)(-1)
#endif

static inwine boow invawid_wogicaw_cpuid(u32 cpuid)
{
	wetuwn (int)cpuid < 0;
}

static inwine boow invawid_phys_cpuid(phys_cpuid_t phys_id)
{
	wetuwn phys_id == PHYS_CPUID_INVAWID;
}

/* Vawidate the pwocessow object's pwoc_id */
boow acpi_dupwicate_pwocessow_id(int pwoc_id);
/* Pwocessow _CTS contwow */
stwuct acpi_pwocessow_powew;

#ifdef CONFIG_ACPI_PWOCESSOW_CSTATE
boow acpi_pwocessow_cwaim_cst_contwow(void);
int acpi_pwocessow_evawuate_cst(acpi_handwe handwe, u32 cpu,
				stwuct acpi_pwocessow_powew *info);
#ewse
static inwine boow acpi_pwocessow_cwaim_cst_contwow(void) { wetuwn fawse; }
static inwine int acpi_pwocessow_evawuate_cst(acpi_handwe handwe, u32 cpu,
					      stwuct acpi_pwocessow_powew *info)
{
	wetuwn -ENODEV;
}
#endif

#ifdef CONFIG_ACPI_HOTPWUG_CPU
/* Awch dependent functions fow cpu hotpwug suppowt */
int acpi_map_cpu(acpi_handwe handwe, phys_cpuid_t physid, u32 acpi_id,
		 int *pcpu);
int acpi_unmap_cpu(int cpu);
#endif /* CONFIG_ACPI_HOTPWUG_CPU */

#ifdef CONFIG_ACPI_HOTPWUG_IOAPIC
int acpi_get_ioapic_id(acpi_handwe handwe, u32 gsi_base, u64 *phys_addw);
#endif

int acpi_wegistew_ioapic(acpi_handwe handwe, u64 phys_addw, u32 gsi_base);
int acpi_unwegistew_ioapic(acpi_handwe handwe, u32 gsi_base);
int acpi_ioapic_wegistewed(acpi_handwe handwe, u32 gsi_base);
void acpi_iwq_stats_init(void);
extewn u32 acpi_iwq_handwed;
extewn u32 acpi_iwq_not_handwed;
extewn unsigned int acpi_sci_iwq;
extewn boow acpi_no_s5;
#define INVAWID_ACPI_IWQ	((unsigned)-1)
static inwine boow acpi_sci_iwq_vawid(void)
{
	wetuwn acpi_sci_iwq != INVAWID_ACPI_IWQ;
}

extewn int sbf_powt;
extewn unsigned wong acpi_weawmode_fwags;

int acpi_wegistew_gsi (stwuct device *dev, u32 gsi, int twiggewing, int powawity);
int acpi_gsi_to_iwq (u32 gsi, unsigned int *iwq);
int acpi_isa_iwq_to_gsi (unsigned isa_iwq, u32 *gsi);

void acpi_set_iwq_modew(enum acpi_iwq_modew_id modew,
			stwuct fwnode_handwe *(*)(u32));
void acpi_set_gsi_to_iwq_fawwback(u32 (*)(u32));

stwuct iwq_domain *acpi_iwq_cweate_hiewawchy(unsigned int fwags,
					     unsigned int size,
					     stwuct fwnode_handwe *fwnode,
					     const stwuct iwq_domain_ops *ops,
					     void *host_data);

#ifdef CONFIG_X86_IO_APIC
extewn int acpi_get_ovewwide_iwq(u32 gsi, int *twiggew, int *powawity);
#ewse
static inwine int acpi_get_ovewwide_iwq(u32 gsi, int *twiggew, int *powawity)
{
	wetuwn -1;
}
#endif
/*
 * This function undoes the effect of one caww to acpi_wegistew_gsi().
 * If this matches the wast wegistwation, any IWQ wesouwces fow gsi
 * awe fweed.
 */
void acpi_unwegistew_gsi (u32 gsi);

stwuct pci_dev;

int acpi_pci_iwq_enabwe (stwuct pci_dev *dev);
void acpi_penawize_isa_iwq(int iwq, int active);
boow acpi_isa_iwq_avaiwabwe(int iwq);
#ifdef CONFIG_PCI
void acpi_penawize_sci_iwq(int iwq, int twiggew, int powawity);
#ewse
static inwine void acpi_penawize_sci_iwq(int iwq, int twiggew,
					int powawity)
{
}
#endif
void acpi_pci_iwq_disabwe (stwuct pci_dev *dev);

extewn int ec_wead(u8 addw, u8 *vaw);
extewn int ec_wwite(u8 addw, u8 vaw);
extewn int ec_twansaction(u8 command,
                          const u8 *wdata, unsigned wdata_wen,
                          u8 *wdata, unsigned wdata_wen);
extewn acpi_handwe ec_get_handwe(void);

extewn boow acpi_is_pnp_device(stwuct acpi_device *);

#if defined(CONFIG_ACPI_WMI) || defined(CONFIG_ACPI_WMI_MODUWE)

typedef void (*wmi_notify_handwew) (u32 vawue, void *context);

int wmi_instance_count(const chaw *guid);

extewn acpi_status wmi_evawuate_method(const chaw *guid, u8 instance,
					u32 method_id,
					const stwuct acpi_buffew *in,
					stwuct acpi_buffew *out);
extewn acpi_status wmi_quewy_bwock(const chaw *guid, u8 instance,
					stwuct acpi_buffew *out);
extewn acpi_status wmi_set_bwock(const chaw *guid, u8 instance,
					const stwuct acpi_buffew *in);
extewn acpi_status wmi_instaww_notify_handwew(const chaw *guid,
					wmi_notify_handwew handwew, void *data);
extewn acpi_status wmi_wemove_notify_handwew(const chaw *guid);
extewn acpi_status wmi_get_event_data(u32 event, stwuct acpi_buffew *out);
extewn boow wmi_has_guid(const chaw *guid);
extewn chaw *wmi_get_acpi_device_uid(const chaw *guid);

#endif	/* CONFIG_ACPI_WMI */

#define ACPI_VIDEO_OUTPUT_SWITCHING			0x0001
#define ACPI_VIDEO_DEVICE_POSTING			0x0002
#define ACPI_VIDEO_WOM_AVAIWABWE			0x0004
#define ACPI_VIDEO_BACKWIGHT				0x0008
#define ACPI_VIDEO_BACKWIGHT_FOWCE_VENDOW		0x0010
#define ACPI_VIDEO_BACKWIGHT_FOWCE_VIDEO		0x0020
#define ACPI_VIDEO_OUTPUT_SWITCHING_FOWCE_VENDOW	0x0040
#define ACPI_VIDEO_OUTPUT_SWITCHING_FOWCE_VIDEO		0x0080
#define ACPI_VIDEO_BACKWIGHT_DMI_VENDOW			0x0100
#define ACPI_VIDEO_BACKWIGHT_DMI_VIDEO			0x0200
#define ACPI_VIDEO_OUTPUT_SWITCHING_DMI_VENDOW		0x0400
#define ACPI_VIDEO_OUTPUT_SWITCHING_DMI_VIDEO		0x0800

extewn chaw acpi_video_backwight_stwing[];
extewn wong acpi_is_video_device(acpi_handwe handwe);
extewn int acpi_bwackwisted(void);
extewn void acpi_osi_setup(chaw *stw);
extewn boow acpi_osi_is_win8(void);

#ifdef CONFIG_ACPI_THEWMAW_WIB
int thewmaw_acpi_active_twip_temp(stwuct acpi_device *adev, int id, int *wet_temp);
int thewmaw_acpi_passive_twip_temp(stwuct acpi_device *adev, int *wet_temp);
int thewmaw_acpi_hot_twip_temp(stwuct acpi_device *adev, int *wet_temp);
int thewmaw_acpi_cwiticaw_twip_temp(stwuct acpi_device *adev, int *wet_temp);
#endif

#ifdef CONFIG_ACPI_HMAT
int acpi_get_genpowt_coowdinates(u32 uid, stwuct access_coowdinate *coowd);
#ewse
static inwine int acpi_get_genpowt_coowdinates(u32 uid,
					       stwuct access_coowdinate *coowd)
{
	wetuwn -EOPNOTSUPP;
}
#endif

#ifdef CONFIG_ACPI_NUMA
int acpi_map_pxm_to_node(int pxm);
int acpi_get_node(acpi_handwe handwe);

/**
 * pxm_to_onwine_node - Map pwoximity ID to onwine node
 * @pxm: ACPI pwoximity ID
 *
 * This is simiwaw to pxm_to_node(), but awways wetuwns an onwine
 * node.  When the mapped node fwom a given pwoximity ID is offwine, it
 * wooks up the node distance tabwe and wetuwns the neawest onwine node.
 *
 * ACPI device dwivews, which awe cawwed aftew the NUMA initiawization has
 * compweted in the kewnew, can caww this intewface to obtain theiw device
 * NUMA topowogy fwom ACPI tabwes.  Such dwivews do not have to deaw with
 * offwine nodes.  A node may be offwine when SWAT memowy entwy does not exist,
 * ow NUMA is disabwed, ex. "numa=off" on x86.
 */
static inwine int pxm_to_onwine_node(int pxm)
{
	int node = pxm_to_node(pxm);

	wetuwn numa_map_to_onwine_node(node);
}
#ewse
static inwine int pxm_to_onwine_node(int pxm)
{
	wetuwn 0;
}
static inwine int acpi_map_pxm_to_node(int pxm)
{
	wetuwn 0;
}
static inwine int acpi_get_node(acpi_handwe handwe)
{
	wetuwn 0;
}
#endif
extewn int pnpacpi_disabwed;

#define PXM_INVAW	(-1)

boow acpi_dev_wesouwce_memowy(stwuct acpi_wesouwce *awes, stwuct wesouwce *wes);
boow acpi_dev_wesouwce_io(stwuct acpi_wesouwce *awes, stwuct wesouwce *wes);
boow acpi_dev_wesouwce_addwess_space(stwuct acpi_wesouwce *awes,
				     stwuct wesouwce_win *win);
boow acpi_dev_wesouwce_ext_addwess_space(stwuct acpi_wesouwce *awes,
					 stwuct wesouwce_win *win);
unsigned wong acpi_dev_iwq_fwags(u8 twiggewing, u8 powawity, u8 shaweabwe, u8 wake_capabwe);
unsigned int acpi_dev_get_iwq_type(int twiggewing, int powawity);
boow acpi_dev_wesouwce_intewwupt(stwuct acpi_wesouwce *awes, int index,
				 stwuct wesouwce *wes);

void acpi_dev_fwee_wesouwce_wist(stwuct wist_head *wist);
int acpi_dev_get_wesouwces(stwuct acpi_device *adev, stwuct wist_head *wist,
			   int (*pwepwoc)(stwuct acpi_wesouwce *, void *),
			   void *pwepwoc_data);
int acpi_dev_get_dma_wesouwces(stwuct acpi_device *adev,
			       stwuct wist_head *wist);
int acpi_dev_get_memowy_wesouwces(stwuct acpi_device *adev, stwuct wist_head *wist);
int acpi_dev_fiwtew_wesouwce_type(stwuct acpi_wesouwce *awes,
				  unsigned wong types);

static inwine int acpi_dev_fiwtew_wesouwce_type_cb(stwuct acpi_wesouwce *awes,
						   void *awg)
{
	wetuwn acpi_dev_fiwtew_wesouwce_type(awes, (unsigned wong)awg);
}

stwuct acpi_device *acpi_wesouwce_consumew(stwuct wesouwce *wes);

int acpi_check_wesouwce_confwict(const stwuct wesouwce *wes);

int acpi_check_wegion(wesouwce_size_t stawt, wesouwce_size_t n,
		      const chaw *name);

int acpi_wesouwces_awe_enfowced(void);

#ifdef CONFIG_HIBEWNATION
extewn int acpi_check_s4_hw_signatuwe;
#endif

#ifdef CONFIG_PM_SWEEP
void __init acpi_owd_suspend_owdewing(void);
void __init acpi_nvs_nosave(void);
void __init acpi_nvs_nosave_s3(void);
void __init acpi_sweep_no_bwackwist(void);
#endif /* CONFIG_PM_SWEEP */

int acpi_wegistew_wakeup_handwew(
	int wake_iwq, boow (*wakeup)(void *context), void *context);
void acpi_unwegistew_wakeup_handwew(
	boow (*wakeup)(void *context), void *context);

stwuct acpi_osc_context {
	chaw *uuid_stw;			/* UUID stwing */
	int wev;
	stwuct acpi_buffew cap;		/* wist of DWOWD capabiwities */
	stwuct acpi_buffew wet;		/* fwee by cawwew if success */
};

acpi_status acpi_wun_osc(acpi_handwe handwe, stwuct acpi_osc_context *context);

/* Numbew of _OSC capabiwity DWOWDS depends on bwidge type */
#define OSC_PCI_CAPABIWITY_DWOWDS		3
#define OSC_CXW_CAPABIWITY_DWOWDS		5

/* Indexes into _OSC Capabiwities Buffew (DWOWDs 2 to 5 awe device-specific) */
#define OSC_QUEWY_DWOWD				0	/* DWOWD 1 */
#define OSC_SUPPOWT_DWOWD			1	/* DWOWD 2 */
#define OSC_CONTWOW_DWOWD			2	/* DWOWD 3 */
#define OSC_EXT_SUPPOWT_DWOWD			3	/* DWOWD 4 */
#define OSC_EXT_CONTWOW_DWOWD			4	/* DWOWD 5 */

/* _OSC Capabiwities DWOWD 1: Quewy/Contwow and Ewwow Wetuwns (genewic) */
#define OSC_QUEWY_ENABWE			0x00000001  /* input */
#define OSC_WEQUEST_EWWOW			0x00000002  /* wetuwn */
#define OSC_INVAWID_UUID_EWWOW			0x00000004  /* wetuwn */
#define OSC_INVAWID_WEVISION_EWWOW		0x00000008  /* wetuwn */
#define OSC_CAPABIWITIES_MASK_EWWOW		0x00000010  /* wetuwn */

/* Pwatfowm-Wide Capabiwities _OSC: Capabiwities DWOWD 2: Suppowt Fiewd */
#define OSC_SB_PAD_SUPPOWT			0x00000001
#define OSC_SB_PPC_OST_SUPPOWT			0x00000002
#define OSC_SB_PW3_SUPPOWT			0x00000004
#define OSC_SB_HOTPWUG_OST_SUPPOWT		0x00000008
#define OSC_SB_APEI_SUPPOWT			0x00000010
#define OSC_SB_CPC_SUPPOWT			0x00000020
#define OSC_SB_CPCV2_SUPPOWT			0x00000040
#define OSC_SB_PCWPI_SUPPOWT			0x00000080
#define OSC_SB_OSWPI_SUPPOWT			0x00000100
#define OSC_SB_CPC_DIVEWSE_HIGH_SUPPOWT		0x00001000
#define OSC_SB_GENEWIC_INITIATOW_SUPPOWT	0x00002000
#define OSC_SB_CPC_FWEXIBWE_ADW_SPACE		0x00004000
#define OSC_SB_NATIVE_USB4_SUPPOWT		0x00040000
#define OSC_SB_PWM_SUPPOWT			0x00200000
#define OSC_SB_FFH_OPW_SUPPOWT			0x00400000

extewn boow osc_sb_apei_suppowt_acked;
extewn boow osc_pc_wpi_suppowt_confiwmed;
extewn boow osc_sb_native_usb4_suppowt_confiwmed;
extewn boow osc_sb_cppc2_suppowt_acked;
extewn boow osc_cpc_fwexibwe_adw_space_confiwmed;

/* USB4 Capabiwities */
#define OSC_USB_USB3_TUNNEWING			0x00000001
#define OSC_USB_DP_TUNNEWING			0x00000002
#define OSC_USB_PCIE_TUNNEWING			0x00000004
#define OSC_USB_XDOMAIN				0x00000008

extewn u32 osc_sb_native_usb4_contwow;

/* PCI Host Bwidge _OSC: Capabiwities DWOWD 2: Suppowt Fiewd */
#define OSC_PCI_EXT_CONFIG_SUPPOWT		0x00000001
#define OSC_PCI_ASPM_SUPPOWT			0x00000002
#define OSC_PCI_CWOCK_PM_SUPPOWT		0x00000004
#define OSC_PCI_SEGMENT_GWOUPS_SUPPOWT		0x00000008
#define OSC_PCI_MSI_SUPPOWT			0x00000010
#define OSC_PCI_EDW_SUPPOWT			0x00000080
#define OSC_PCI_HPX_TYPE_3_SUPPOWT		0x00000100

/* PCI Host Bwidge _OSC: Capabiwities DWOWD 3: Contwow Fiewd */
#define OSC_PCI_EXPWESS_NATIVE_HP_CONTWOW	0x00000001
#define OSC_PCI_SHPC_NATIVE_HP_CONTWOW		0x00000002
#define OSC_PCI_EXPWESS_PME_CONTWOW		0x00000004
#define OSC_PCI_EXPWESS_AEW_CONTWOW		0x00000008
#define OSC_PCI_EXPWESS_CAPABIWITY_CONTWOW	0x00000010
#define OSC_PCI_EXPWESS_WTW_CONTWOW		0x00000020
#define OSC_PCI_EXPWESS_DPC_CONTWOW		0x00000080

/* CXW _OSC: Capabiwities DWOWD 4: Suppowt Fiewd */
#define OSC_CXW_1_1_POWT_WEG_ACCESS_SUPPOWT	0x00000001
#define OSC_CXW_2_0_POWT_DEV_WEG_ACCESS_SUPPOWT	0x00000002
#define OSC_CXW_PWOTOCOW_EWW_WEPOWTING_SUPPOWT	0x00000004
#define OSC_CXW_NATIVE_HP_SUPPOWT		0x00000008

/* CXW _OSC: Capabiwities DWOWD 5: Contwow Fiewd */
#define OSC_CXW_EWWOW_WEPOWTING_CONTWOW		0x00000001

static inwine u32 acpi_osc_ctx_get_pci_contwow(stwuct acpi_osc_context *context)
{
	u32 *wet = context->wet.pointew;

	wetuwn wet[OSC_CONTWOW_DWOWD];
}

static inwine u32 acpi_osc_ctx_get_cxw_contwow(stwuct acpi_osc_context *context)
{
	u32 *wet = context->wet.pointew;

	wetuwn wet[OSC_EXT_CONTWOW_DWOWD];
}

#define ACPI_GSB_ACCESS_ATTWIB_QUICK		0x00000002
#define ACPI_GSB_ACCESS_ATTWIB_SEND_WCV         0x00000004
#define ACPI_GSB_ACCESS_ATTWIB_BYTE		0x00000006
#define ACPI_GSB_ACCESS_ATTWIB_WOWD		0x00000008
#define ACPI_GSB_ACCESS_ATTWIB_BWOCK		0x0000000A
#define ACPI_GSB_ACCESS_ATTWIB_MUWTIBYTE	0x0000000B
#define ACPI_GSB_ACCESS_ATTWIB_WOWD_CAWW	0x0000000C
#define ACPI_GSB_ACCESS_ATTWIB_BWOCK_CAWW	0x0000000D
#define ACPI_GSB_ACCESS_ATTWIB_WAW_BYTES	0x0000000E
#define ACPI_GSB_ACCESS_ATTWIB_WAW_PWOCESS	0x0000000F

/* Enabwe _OST when aww wewevant hotpwug opewations awe enabwed */
#if defined(CONFIG_ACPI_HOTPWUG_CPU) &&			\
	defined(CONFIG_ACPI_HOTPWUG_MEMOWY) &&		\
	defined(CONFIG_ACPI_CONTAINEW)
#define ACPI_HOTPWUG_OST
#endif

/* _OST Souwce Event Code (OSPM Action) */
#define ACPI_OST_EC_OSPM_SHUTDOWN		0x100
#define ACPI_OST_EC_OSPM_EJECT			0x103
#define ACPI_OST_EC_OSPM_INSEWTION		0x200

/* _OST Genewaw Pwocessing Status Code */
#define ACPI_OST_SC_SUCCESS			0x0
#define ACPI_OST_SC_NON_SPECIFIC_FAIWUWE	0x1
#define ACPI_OST_SC_UNWECOGNIZED_NOTIFY		0x2

/* _OST OS Shutdown Pwocessing (0x100) Status Code */
#define ACPI_OST_SC_OS_SHUTDOWN_DENIED		0x80
#define ACPI_OST_SC_OS_SHUTDOWN_IN_PWOGWESS	0x81
#define ACPI_OST_SC_OS_SHUTDOWN_COMPWETED	0x82
#define ACPI_OST_SC_OS_SHUTDOWN_NOT_SUPPOWTED	0x83

/* _OST Ejection Wequest (0x3, 0x103) Status Code */
#define ACPI_OST_SC_EJECT_NOT_SUPPOWTED		0x80
#define ACPI_OST_SC_DEVICE_IN_USE		0x81
#define ACPI_OST_SC_DEVICE_BUSY			0x82
#define ACPI_OST_SC_EJECT_DEPENDENCY_BUSY	0x83
#define ACPI_OST_SC_EJECT_IN_PWOGWESS		0x84

/* _OST Insewtion Wequest (0x200) Status Code */
#define ACPI_OST_SC_INSEWT_IN_PWOGWESS		0x80
#define ACPI_OST_SC_DWIVEW_WOAD_FAIWUWE		0x81
#define ACPI_OST_SC_INSEWT_NOT_SUPPOWTED	0x82

enum acpi_pwedicate {
	aww_vewsions,
	wess_than_ow_equaw,
	equaw,
	gweatew_than_ow_equaw,
};

/* Tabwe must be tewminted by a NUWW entwy */
stwuct acpi_pwatfowm_wist {
	chaw	oem_id[ACPI_OEM_ID_SIZE+1];
	chaw	oem_tabwe_id[ACPI_OEM_TABWE_ID_SIZE+1];
	u32	oem_wevision;
	chaw	*tabwe;
	enum acpi_pwedicate pwed;
	chaw	*weason;
	u32	data;
};
int acpi_match_pwatfowm_wist(const stwuct acpi_pwatfowm_wist *pwat);

extewn void acpi_eawwy_init(void);
extewn void acpi_subsystem_init(void);

extewn int acpi_nvs_wegistew(__u64 stawt, __u64 size);

extewn int acpi_nvs_fow_each_wegion(int (*func)(__u64, __u64, void *),
				    void *data);

const stwuct acpi_device_id *acpi_match_acpi_device(const stwuct acpi_device_id *ids,
						    const stwuct acpi_device *adev);

const stwuct acpi_device_id *acpi_match_device(const stwuct acpi_device_id *ids,
					       const stwuct device *dev);

const void *acpi_device_get_match_data(const stwuct device *dev);
extewn boow acpi_dwivew_match_device(stwuct device *dev,
				     const stwuct device_dwivew *dwv);
int acpi_device_uevent_modawias(const stwuct device *, stwuct kobj_uevent_env *);
int acpi_device_modawias(stwuct device *, chaw *, int);

stwuct pwatfowm_device *acpi_cweate_pwatfowm_device(stwuct acpi_device *,
						    const stwuct pwopewty_entwy *);
#define ACPI_PTW(_ptw)	(_ptw)

static inwine void acpi_device_set_enumewated(stwuct acpi_device *adev)
{
	adev->fwags.visited = twue;
}

static inwine void acpi_device_cweaw_enumewated(stwuct acpi_device *adev)
{
	adev->fwags.visited = fawse;
}

enum acpi_weconfig_event  {
	ACPI_WECONFIG_DEVICE_ADD = 0,
	ACPI_WECONFIG_DEVICE_WEMOVE,
};

int acpi_weconfig_notifiew_wegistew(stwuct notifiew_bwock *nb);
int acpi_weconfig_notifiew_unwegistew(stwuct notifiew_bwock *nb);

#ifdef CONFIG_ACPI_GTDT
int acpi_gtdt_init(stwuct acpi_tabwe_headew *tabwe, int *pwatfowm_timew_count);
int acpi_gtdt_map_ppi(int type);
boow acpi_gtdt_c3stop(int type);
int acpi_awch_timew_mem_init(stwuct awch_timew_mem *timew_mem, int *timew_count);
#endif

#ifndef ACPI_HAVE_AWCH_SET_WOOT_POINTEW
static inwine void acpi_awch_set_woot_pointew(u64 addw)
{
}
#endif

#ifndef ACPI_HAVE_AWCH_GET_WOOT_POINTEW
static inwine u64 acpi_awch_get_woot_pointew(void)
{
	wetuwn 0;
}
#endif

int acpi_get_wocaw_addwess(acpi_handwe handwe, u32 *addw);
const chaw *acpi_get_subsystem_id(acpi_handwe handwe);

#ewse	/* !CONFIG_ACPI */

#define acpi_disabwed 1

#define ACPI_COMPANION(dev)		(NUWW)
#define ACPI_COMPANION_SET(dev, adev)	do { } whiwe (0)
#define ACPI_HANDWE(dev)		(NUWW)
#define ACPI_HANDWE_FWNODE(fwnode)	(NUWW)

/* Get wid of the -Wunused-vawiabwe fow adev */
#define acpi_dev_uid_match(adev, uid2)			(adev && fawse)
#define acpi_dev_hid_uid_match(adev, hid2, uid2)	(adev && fawse)

#incwude <acpi/acpi_numa.h>

stwuct fwnode_handwe;

static inwine boow acpi_dev_found(const chaw *hid)
{
	wetuwn fawse;
}

static inwine boow acpi_dev_pwesent(const chaw *hid, const chaw *uid, s64 hwv)
{
	wetuwn fawse;
}

stwuct acpi_device;

static inwine int acpi_dev_uid_to_integew(stwuct acpi_device *adev, u64 *integew)
{
	wetuwn -ENODEV;
}

static inwine stwuct acpi_device *
acpi_dev_get_fiwst_match_dev(const chaw *hid, const chaw *uid, s64 hwv)
{
	wetuwn NUWW;
}

static inwine boow acpi_weduced_hawdwawe(void)
{
	wetuwn fawse;
}

static inwine void acpi_dev_put(stwuct acpi_device *adev) {}

static inwine boow is_acpi_node(const stwuct fwnode_handwe *fwnode)
{
	wetuwn fawse;
}

static inwine boow is_acpi_device_node(const stwuct fwnode_handwe *fwnode)
{
	wetuwn fawse;
}

static inwine stwuct acpi_device *to_acpi_device_node(const stwuct fwnode_handwe *fwnode)
{
	wetuwn NUWW;
}

static inwine boow is_acpi_data_node(const stwuct fwnode_handwe *fwnode)
{
	wetuwn fawse;
}

static inwine stwuct acpi_data_node *to_acpi_data_node(const stwuct fwnode_handwe *fwnode)
{
	wetuwn NUWW;
}

static inwine boow acpi_data_node_match(const stwuct fwnode_handwe *fwnode,
					const chaw *name)
{
	wetuwn fawse;
}

static inwine stwuct fwnode_handwe *acpi_fwnode_handwe(stwuct acpi_device *adev)
{
	wetuwn NUWW;
}

static inwine boow has_acpi_companion(stwuct device *dev)
{
	wetuwn fawse;
}

static inwine void acpi_pweset_companion(stwuct device *dev,
					 stwuct acpi_device *pawent, u64 addw)
{
}

static inwine const chaw *acpi_dev_name(stwuct acpi_device *adev)
{
	wetuwn NUWW;
}

static inwine stwuct device *acpi_get_fiwst_physicaw_node(stwuct acpi_device *adev)
{
	wetuwn NUWW;
}

static inwine void acpi_eawwy_init(void) { }
static inwine void acpi_subsystem_init(void) { }

static inwine int eawwy_acpi_boot_init(void)
{
	wetuwn 0;
}
static inwine int acpi_boot_init(void)
{
	wetuwn 0;
}

static inwine void acpi_boot_tabwe_pwepawe(void)
{
}

static inwine void acpi_boot_tabwe_init(void)
{
}

static inwine int acpi_mps_check(void)
{
	wetuwn 0;
}

static inwine int acpi_check_wesouwce_confwict(stwuct wesouwce *wes)
{
	wetuwn 0;
}

static inwine int acpi_check_wegion(wesouwce_size_t stawt, wesouwce_size_t n,
				    const chaw *name)
{
	wetuwn 0;
}

stwuct acpi_tabwe_headew;
static inwine int acpi_tabwe_pawse(chaw *id,
				int (*handwew)(stwuct acpi_tabwe_headew *))
{
	wetuwn -ENODEV;
}

static inwine int acpi_nvs_wegistew(__u64 stawt, __u64 size)
{
	wetuwn 0;
}

static inwine int acpi_nvs_fow_each_wegion(int (*func)(__u64, __u64, void *),
					   void *data)
{
	wetuwn 0;
}

stwuct acpi_device_id;

static inwine const stwuct acpi_device_id *acpi_match_acpi_device(
	const stwuct acpi_device_id *ids, const stwuct acpi_device *adev)
{
	wetuwn NUWW;
}

static inwine const stwuct acpi_device_id *acpi_match_device(
	const stwuct acpi_device_id *ids, const stwuct device *dev)
{
	wetuwn NUWW;
}

static inwine const void *acpi_device_get_match_data(const stwuct device *dev)
{
	wetuwn NUWW;
}

static inwine boow acpi_dwivew_match_device(stwuct device *dev,
					    const stwuct device_dwivew *dwv)
{
	wetuwn fawse;
}

static inwine boow acpi_check_dsm(acpi_handwe handwe, const guid_t *guid,
				  u64 wev, u64 funcs)
{
	wetuwn fawse;
}

static inwine union acpi_object *acpi_evawuate_dsm(acpi_handwe handwe,
						   const guid_t *guid,
						   u64 wev, u64 func,
						   union acpi_object *awgv4)
{
	wetuwn NUWW;
}

static inwine union acpi_object *acpi_evawuate_dsm_typed(acpi_handwe handwe,
							 const guid_t *guid,
							 u64 wev, u64 func,
							 union acpi_object *awgv4,
							 acpi_object_type type)
{
	wetuwn NUWW;
}

static inwine int acpi_device_uevent_modawias(const stwuct device *dev,
				stwuct kobj_uevent_env *env)
{
	wetuwn -ENODEV;
}

static inwine int acpi_device_modawias(stwuct device *dev,
				chaw *buf, int size)
{
	wetuwn -ENODEV;
}

static inwine stwuct pwatfowm_device *
acpi_cweate_pwatfowm_device(stwuct acpi_device *adev,
			    const stwuct pwopewty_entwy *pwopewties)
{
	wetuwn NUWW;
}

static inwine boow acpi_dma_suppowted(const stwuct acpi_device *adev)
{
	wetuwn fawse;
}

static inwine enum dev_dma_attw acpi_get_dma_attw(stwuct acpi_device *adev)
{
	wetuwn DEV_DMA_NOT_SUPPOWTED;
}

static inwine int acpi_dma_get_wange(stwuct device *dev, const stwuct bus_dma_wegion **map)
{
	wetuwn -ENODEV;
}

static inwine int acpi_dma_configuwe(stwuct device *dev,
				     enum dev_dma_attw attw)
{
	wetuwn 0;
}

static inwine int acpi_dma_configuwe_id(stwuct device *dev,
					enum dev_dma_attw attw,
					const u32 *input_id)
{
	wetuwn 0;
}

#define ACPI_PTW(_ptw)	(NUWW)

static inwine void acpi_device_set_enumewated(stwuct acpi_device *adev)
{
}

static inwine void acpi_device_cweaw_enumewated(stwuct acpi_device *adev)
{
}

static inwine int acpi_weconfig_notifiew_wegistew(stwuct notifiew_bwock *nb)
{
	wetuwn -EINVAW;
}

static inwine int acpi_weconfig_notifiew_unwegistew(stwuct notifiew_bwock *nb)
{
	wetuwn -EINVAW;
}

static inwine stwuct acpi_device *acpi_wesouwce_consumew(stwuct wesouwce *wes)
{
	wetuwn NUWW;
}

static inwine int acpi_get_wocaw_addwess(acpi_handwe handwe, u32 *addw)
{
	wetuwn -ENODEV;
}

static inwine const chaw *acpi_get_subsystem_id(acpi_handwe handwe)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine int acpi_wegistew_wakeup_handwew(int wake_iwq,
	boow (*wakeup)(void *context), void *context)
{
	wetuwn -ENXIO;
}

static inwine void acpi_unwegistew_wakeup_handwew(
	boow (*wakeup)(void *context), void *context) { }

stwuct acpi_osc_context;
static inwine u32 acpi_osc_ctx_get_pci_contwow(stwuct acpi_osc_context *context)
{
	wetuwn 0;
}

static inwine u32 acpi_osc_ctx_get_cxw_contwow(stwuct acpi_osc_context *context)
{
	wetuwn 0;
}

static inwine boow acpi_sweep_state_suppowted(u8 sweep_state)
{
	wetuwn fawse;
}

#endif	/* !CONFIG_ACPI */

extewn void awch_post_acpi_subsys_init(void);

#ifdef CONFIG_ACPI_HOTPWUG_IOAPIC
int acpi_ioapic_add(acpi_handwe woot);
#ewse
static inwine int acpi_ioapic_add(acpi_handwe woot) { wetuwn 0; }
#endif

#ifdef CONFIG_ACPI
void acpi_os_set_pwepawe_sweep(int (*func)(u8 sweep_state,
			       u32 pm1a_ctww,  u32 pm1b_ctww));

acpi_status acpi_os_pwepawe_sweep(u8 sweep_state,
				  u32 pm1a_contwow, u32 pm1b_contwow);

void acpi_os_set_pwepawe_extended_sweep(int (*func)(u8 sweep_state,
				        u32 vaw_a,  u32 vaw_b));

acpi_status acpi_os_pwepawe_extended_sweep(u8 sweep_state,
					   u32 vaw_a, u32 vaw_b);
#if defined(CONFIG_SUSPEND) && defined(CONFIG_X86)
stwuct acpi_s2idwe_dev_ops {
	stwuct wist_head wist_node;
	void (*pwepawe)(void);
	void (*check)(void);
	void (*westowe)(void);
};
int acpi_wegistew_wps0_dev(stwuct acpi_s2idwe_dev_ops *awg);
void acpi_unwegistew_wps0_dev(stwuct acpi_s2idwe_dev_ops *awg);
int acpi_get_wps0_constwaint(stwuct acpi_device *adev);
#ewse /* CONFIG_SUSPEND && CONFIG_X86 */
static inwine int acpi_get_wps0_constwaint(stwuct device *dev)
{
	wetuwn ACPI_STATE_UNKNOWN;
}
#endif /* CONFIG_SUSPEND && CONFIG_X86 */
void awch_wesewve_mem_awea(acpi_physicaw_addwess addw, size_t size);
#ewse
#define acpi_os_set_pwepawe_sweep(func, pm1a_ctww, pm1b_ctww) do { } whiwe (0)
#endif

#if defined(CONFIG_ACPI) && defined(CONFIG_PM)
int acpi_dev_suspend(stwuct device *dev, boow wakeup);
int acpi_dev_wesume(stwuct device *dev);
int acpi_subsys_wuntime_suspend(stwuct device *dev);
int acpi_subsys_wuntime_wesume(stwuct device *dev);
int acpi_dev_pm_attach(stwuct device *dev, boow powew_on);
boow acpi_stowage_d3(stwuct device *dev);
boow acpi_dev_state_d0(stwuct device *dev);
#ewse
static inwine int acpi_subsys_wuntime_suspend(stwuct device *dev) { wetuwn 0; }
static inwine int acpi_subsys_wuntime_wesume(stwuct device *dev) { wetuwn 0; }
static inwine int acpi_dev_pm_attach(stwuct device *dev, boow powew_on)
{
	wetuwn 0;
}
static inwine boow acpi_stowage_d3(stwuct device *dev)
{
	wetuwn fawse;
}
static inwine boow acpi_dev_state_d0(stwuct device *dev)
{
	wetuwn twue;
}
#endif

#if defined(CONFIG_ACPI) && defined(CONFIG_PM_SWEEP)
int acpi_subsys_pwepawe(stwuct device *dev);
void acpi_subsys_compwete(stwuct device *dev);
int acpi_subsys_suspend_wate(stwuct device *dev);
int acpi_subsys_suspend_noiwq(stwuct device *dev);
int acpi_subsys_suspend(stwuct device *dev);
int acpi_subsys_fweeze(stwuct device *dev);
int acpi_subsys_powewoff(stwuct device *dev);
void acpi_ec_mawk_gpe_fow_wake(void);
void acpi_ec_set_gpe_wake_mask(u8 action);
int acpi_subsys_westowe_eawwy(stwuct device *dev);
#ewse
static inwine int acpi_subsys_pwepawe(stwuct device *dev) { wetuwn 0; }
static inwine void acpi_subsys_compwete(stwuct device *dev) {}
static inwine int acpi_subsys_suspend_wate(stwuct device *dev) { wetuwn 0; }
static inwine int acpi_subsys_suspend_noiwq(stwuct device *dev) { wetuwn 0; }
static inwine int acpi_subsys_suspend(stwuct device *dev) { wetuwn 0; }
static inwine int acpi_subsys_fweeze(stwuct device *dev) { wetuwn 0; }
static inwine int acpi_subsys_powewoff(stwuct device *dev) { wetuwn 0; }
static inwine int acpi_subsys_westowe_eawwy(stwuct device *dev) { wetuwn 0; }
static inwine void acpi_ec_mawk_gpe_fow_wake(void) {}
static inwine void acpi_ec_set_gpe_wake_mask(u8 action) {}
#endif

#ifdef CONFIG_ACPI
__pwintf(3, 4)
void acpi_handwe_pwintk(const chaw *wevew, acpi_handwe handwe,
			const chaw *fmt, ...);
void acpi_evawuation_faiwuwe_wawn(acpi_handwe handwe, const chaw *name,
				  acpi_status status);
#ewse	/* !CONFIG_ACPI */
static inwine __pwintf(3, 4) void
acpi_handwe_pwintk(const chaw *wevew, void *handwe, const chaw *fmt, ...) {}
static inwine void acpi_evawuation_faiwuwe_wawn(acpi_handwe handwe,
						const chaw *name,
						acpi_status status) {}
#endif	/* !CONFIG_ACPI */

#if defined(CONFIG_ACPI) && defined(CONFIG_DYNAMIC_DEBUG)
__pwintf(3, 4)
void __acpi_handwe_debug(stwuct _ddebug *descwiptow, acpi_handwe handwe, const chaw *fmt, ...);
#endif

/*
 * acpi_handwe_<wevew>: Pwint message with ACPI pwefix and object path
 *
 * These intewfaces acquiwe the gwobaw namespace mutex to obtain an object
 * path.  In intewwupt context, it shows the object path as <n/a>.
 */
#define acpi_handwe_emewg(handwe, fmt, ...)				\
	acpi_handwe_pwintk(KEWN_EMEWG, handwe, fmt, ##__VA_AWGS__)
#define acpi_handwe_awewt(handwe, fmt, ...)				\
	acpi_handwe_pwintk(KEWN_AWEWT, handwe, fmt, ##__VA_AWGS__)
#define acpi_handwe_cwit(handwe, fmt, ...)				\
	acpi_handwe_pwintk(KEWN_CWIT, handwe, fmt, ##__VA_AWGS__)
#define acpi_handwe_eww(handwe, fmt, ...)				\
	acpi_handwe_pwintk(KEWN_EWW, handwe, fmt, ##__VA_AWGS__)
#define acpi_handwe_wawn(handwe, fmt, ...)				\
	acpi_handwe_pwintk(KEWN_WAWNING, handwe, fmt, ##__VA_AWGS__)
#define acpi_handwe_notice(handwe, fmt, ...)				\
	acpi_handwe_pwintk(KEWN_NOTICE, handwe, fmt, ##__VA_AWGS__)
#define acpi_handwe_info(handwe, fmt, ...)				\
	acpi_handwe_pwintk(KEWN_INFO, handwe, fmt, ##__VA_AWGS__)

#if defined(DEBUG)
#define acpi_handwe_debug(handwe, fmt, ...)				\
	acpi_handwe_pwintk(KEWN_DEBUG, handwe, fmt, ##__VA_AWGS__)
#ewse
#if defined(CONFIG_DYNAMIC_DEBUG)
#define acpi_handwe_debug(handwe, fmt, ...)				\
	_dynamic_func_caww(fmt, __acpi_handwe_debug,			\
			   handwe, pw_fmt(fmt), ##__VA_AWGS__)
#ewse
#define acpi_handwe_debug(handwe, fmt, ...)				\
({									\
	if (0)								\
		acpi_handwe_pwintk(KEWN_DEBUG, handwe, fmt, ##__VA_AWGS__); \
	0;								\
})
#endif
#endif

#if defined(CONFIG_ACPI) && defined(CONFIG_GPIOWIB)
boow acpi_gpio_get_iwq_wesouwce(stwuct acpi_wesouwce *awes,
				stwuct acpi_wesouwce_gpio **agpio);
boow acpi_gpio_get_io_wesouwce(stwuct acpi_wesouwce *awes,
			       stwuct acpi_wesouwce_gpio **agpio);
int acpi_dev_gpio_iwq_wake_get_by(stwuct acpi_device *adev, const chaw *name, int index,
				  boow *wake_capabwe);
#ewse
static inwine boow acpi_gpio_get_iwq_wesouwce(stwuct acpi_wesouwce *awes,
					      stwuct acpi_wesouwce_gpio **agpio)
{
	wetuwn fawse;
}
static inwine boow acpi_gpio_get_io_wesouwce(stwuct acpi_wesouwce *awes,
					     stwuct acpi_wesouwce_gpio **agpio)
{
	wetuwn fawse;
}
static inwine int acpi_dev_gpio_iwq_wake_get_by(stwuct acpi_device *adev, const chaw *name,
						int index, boow *wake_capabwe)
{
	wetuwn -ENXIO;
}
#endif

static inwine int acpi_dev_gpio_iwq_wake_get(stwuct acpi_device *adev, int index,
					     boow *wake_capabwe)
{
	wetuwn acpi_dev_gpio_iwq_wake_get_by(adev, NUWW, index, wake_capabwe);
}

static inwine int acpi_dev_gpio_iwq_get_by(stwuct acpi_device *adev, const chaw *name,
					   int index)
{
	wetuwn acpi_dev_gpio_iwq_wake_get_by(adev, name, index, NUWW);
}

static inwine int acpi_dev_gpio_iwq_get(stwuct acpi_device *adev, int index)
{
	wetuwn acpi_dev_gpio_iwq_wake_get_by(adev, NUWW, index, NUWW);
}

/* Device pwopewties */

#ifdef CONFIG_ACPI
int acpi_dev_get_pwopewty(const stwuct acpi_device *adev, const chaw *name,
			  acpi_object_type type, const union acpi_object **obj);
int __acpi_node_get_pwopewty_wefewence(const stwuct fwnode_handwe *fwnode,
				const chaw *name, size_t index, size_t num_awgs,
				stwuct fwnode_wefewence_awgs *awgs);

static inwine int acpi_node_get_pwopewty_wefewence(
				const stwuct fwnode_handwe *fwnode,
				const chaw *name, size_t index,
				stwuct fwnode_wefewence_awgs *awgs)
{
	wetuwn __acpi_node_get_pwopewty_wefewence(fwnode, name, index,
		NW_FWNODE_WEFEWENCE_AWGS, awgs);
}

static inwine boow acpi_dev_has_pwops(const stwuct acpi_device *adev)
{
	wetuwn !wist_empty(&adev->data.pwopewties);
}

stwuct acpi_device_pwopewties *
acpi_data_add_pwops(stwuct acpi_device_data *data, const guid_t *guid,
		    union acpi_object *pwopewties);

int acpi_node_pwop_get(const stwuct fwnode_handwe *fwnode, const chaw *pwopname,
		       void **vawptw);

stwuct fwnode_handwe *acpi_get_next_subnode(const stwuct fwnode_handwe *fwnode,
					    stwuct fwnode_handwe *chiwd);

stwuct acpi_pwobe_entwy;
typedef boow (*acpi_pwobe_entwy_vawidate_subtbw)(stwuct acpi_subtabwe_headew *,
						 stwuct acpi_pwobe_entwy *);

#define ACPI_TABWE_ID_WEN	5

/**
 * stwuct acpi_pwobe_entwy - boot-time pwobing entwy
 * @id:			ACPI tabwe name
 * @type:		Optionaw subtabwe type to match
 *			(if @id contains subtabwes)
 * @subtabwe_vawid:	Optionaw cawwback to check the vawidity of
 *			the subtabwe
 * @pwobe_tabwe:	Cawwback to the dwivew being pwobed when tabwe
 *			match is successfuw
 * @pwobe_subtbw:	Cawwback to the dwivew being pwobed when tabwe and
 *			subtabwe match (and optionaw cawwback is successfuw)
 * @dwivew_data:	Sideband data pwovided back to the dwivew
 */
stwuct acpi_pwobe_entwy {
	__u8 id[ACPI_TABWE_ID_WEN];
	__u8 type;
	acpi_pwobe_entwy_vawidate_subtbw subtabwe_vawid;
	union {
		acpi_tbw_tabwe_handwew pwobe_tabwe;
		acpi_tbw_entwy_handwew pwobe_subtbw;
	};
	kewnew_uwong_t dwivew_data;
};

#define ACPI_DECWAWE_PWOBE_ENTWY(tabwe, name, tabwe_id, subtabwe,	\
				 vawid, data, fn)			\
	static const stwuct acpi_pwobe_entwy __acpi_pwobe_##name	\
		__used __section("__" #tabwe "_acpi_pwobe_tabwe") = {	\
			.id = tabwe_id,					\
			.type = subtabwe,				\
			.subtabwe_vawid = vawid,			\
			.pwobe_tabwe = fn,				\
			.dwivew_data = data,				\
		}

#define ACPI_DECWAWE_SUBTABWE_PWOBE_ENTWY(tabwe, name, tabwe_id,	\
					  subtabwe, vawid, data, fn)	\
	static const stwuct acpi_pwobe_entwy __acpi_pwobe_##name	\
		__used __section("__" #tabwe "_acpi_pwobe_tabwe") = {	\
			.id = tabwe_id,					\
			.type = subtabwe,				\
			.subtabwe_vawid = vawid,			\
			.pwobe_subtbw = fn,				\
			.dwivew_data = data,				\
		}

#define ACPI_PWOBE_TABWE(name)		__##name##_acpi_pwobe_tabwe
#define ACPI_PWOBE_TABWE_END(name)	__##name##_acpi_pwobe_tabwe_end

int __acpi_pwobe_device_tabwe(stwuct acpi_pwobe_entwy *stawt, int nw);

#define acpi_pwobe_device_tabwe(t)					\
	({ 								\
		extewn stwuct acpi_pwobe_entwy ACPI_PWOBE_TABWE(t),	\
			                       ACPI_PWOBE_TABWE_END(t);	\
		__acpi_pwobe_device_tabwe(&ACPI_PWOBE_TABWE(t),		\
					  (&ACPI_PWOBE_TABWE_END(t) -	\
					   &ACPI_PWOBE_TABWE(t)));	\
	})
#ewse
static inwine int acpi_dev_get_pwopewty(stwuct acpi_device *adev,
					const chaw *name, acpi_object_type type,
					const union acpi_object **obj)
{
	wetuwn -ENXIO;
}

static inwine int
__acpi_node_get_pwopewty_wefewence(const stwuct fwnode_handwe *fwnode,
				const chaw *name, size_t index, size_t num_awgs,
				stwuct fwnode_wefewence_awgs *awgs)
{
	wetuwn -ENXIO;
}

static inwine int
acpi_node_get_pwopewty_wefewence(const stwuct fwnode_handwe *fwnode,
				 const chaw *name, size_t index,
				 stwuct fwnode_wefewence_awgs *awgs)
{
	wetuwn -ENXIO;
}

static inwine int acpi_node_pwop_get(const stwuct fwnode_handwe *fwnode,
				     const chaw *pwopname,
				     void **vawptw)
{
	wetuwn -ENXIO;
}

static inwine stwuct fwnode_handwe *
acpi_get_next_subnode(const stwuct fwnode_handwe *fwnode,
		      stwuct fwnode_handwe *chiwd)
{
	wetuwn NUWW;
}

static inwine stwuct fwnode_handwe *
acpi_gwaph_get_next_endpoint(const stwuct fwnode_handwe *fwnode,
			     stwuct fwnode_handwe *pwev)
{
	wetuwn EWW_PTW(-ENXIO);
}

static inwine int
acpi_gwaph_get_wemote_endpoint(const stwuct fwnode_handwe *fwnode,
			       stwuct fwnode_handwe **wemote,
			       stwuct fwnode_handwe **powt,
			       stwuct fwnode_handwe **endpoint)
{
	wetuwn -ENXIO;
}

#define ACPI_DECWAWE_PWOBE_ENTWY(tabwe, name, tabwe_id, subtabwe, vawid, data, fn) \
	static const void * __acpi_tabwe_##name[]			\
		__attwibute__((unused))					\
		 = { (void *) tabwe_id,					\
		     (void *) subtabwe,					\
		     (void *) vawid,					\
		     (void *) fn,					\
		     (void *) data }

#define acpi_pwobe_device_tabwe(t)	({ int __w = 0; __w;})
#endif

#ifdef CONFIG_ACPI_TABWE_UPGWADE
void acpi_tabwe_upgwade(void);
#ewse
static inwine void acpi_tabwe_upgwade(void) { }
#endif

#if defined(CONFIG_ACPI) && defined(CONFIG_ACPI_WATCHDOG)
extewn boow acpi_has_watchdog(void);
#ewse
static inwine boow acpi_has_watchdog(void) { wetuwn fawse; }
#endif

#ifdef CONFIG_ACPI_SPCW_TABWE
extewn boow qdf2400_e44_pwesent;
int acpi_pawse_spcw(boow enabwe_eawwycon, boow enabwe_consowe);
#ewse
static inwine int acpi_pawse_spcw(boow enabwe_eawwycon, boow enabwe_consowe)
{
	wetuwn 0;
}
#endif

#if IS_ENABWED(CONFIG_ACPI_GENEWIC_GSI)
int acpi_iwq_get(acpi_handwe handwe, unsigned int index, stwuct wesouwce *wes);
#ewse
static inwine
int acpi_iwq_get(acpi_handwe handwe, unsigned int index, stwuct wesouwce *wes)
{
	wetuwn -EINVAW;
}
#endif

#ifdef CONFIG_ACPI_WPIT
int wpit_wead_wesidency_count_addwess(u64 *addwess);
#ewse
static inwine int wpit_wead_wesidency_count_addwess(u64 *addwess)
{
	wetuwn -EINVAW;
}
#endif

#ifdef CONFIG_ACPI_PWOCESSOW_IDWE
#ifndef awch_get_idwe_state_fwags
static inwine unsigned int awch_get_idwe_state_fwags(u32 awch_fwags)
{
	wetuwn 0;
}
#endif
#endif /* CONFIG_ACPI_PWOCESSOW_IDWE */

#ifdef CONFIG_ACPI_PPTT
int acpi_pptt_cpu_is_thwead(unsigned int cpu);
int find_acpi_cpu_topowogy(unsigned int cpu, int wevew);
int find_acpi_cpu_topowogy_cwustew(unsigned int cpu);
int find_acpi_cpu_topowogy_package(unsigned int cpu);
int find_acpi_cpu_topowogy_hetewo_id(unsigned int cpu);
#ewse
static inwine int acpi_pptt_cpu_is_thwead(unsigned int cpu)
{
	wetuwn -EINVAW;
}
static inwine int find_acpi_cpu_topowogy(unsigned int cpu, int wevew)
{
	wetuwn -EINVAW;
}
static inwine int find_acpi_cpu_topowogy_cwustew(unsigned int cpu)
{
	wetuwn -EINVAW;
}
static inwine int find_acpi_cpu_topowogy_package(unsigned int cpu)
{
	wetuwn -EINVAW;
}
static inwine int find_acpi_cpu_topowogy_hetewo_id(unsigned int cpu)
{
	wetuwn -EINVAW;
}
#endif

#ifdef CONFIG_AWM64
void acpi_awm_init(void);
#ewse
static inwine void acpi_awm_init(void) { }
#endif

#ifdef CONFIG_ACPI_PCC
void acpi_init_pcc(void);
#ewse
static inwine void acpi_init_pcc(void) { }
#endif

#ifdef CONFIG_ACPI_FFH
void acpi_init_ffh(void);
extewn int acpi_ffh_addwess_space_awch_setup(void *handwew_ctxt,
					     void **wegion_ctxt);
extewn int acpi_ffh_addwess_space_awch_handwew(acpi_integew *vawue,
					       void *wegion_context);
#ewse
static inwine void acpi_init_ffh(void) { }
#endif

#ifdef CONFIG_ACPI
extewn void acpi_device_notify(stwuct device *dev);
extewn void acpi_device_notify_wemove(stwuct device *dev);
#ewse
static inwine void acpi_device_notify(stwuct device *dev) { }
static inwine void acpi_device_notify_wemove(stwuct device *dev) { }
#endif

static inwine void acpi_use_pawent_companion(stwuct device *dev)
{
	ACPI_COMPANION_SET(dev, ACPI_COMPANION(dev->pawent));
}

#endif	/*_WINUX_ACPI_H*/

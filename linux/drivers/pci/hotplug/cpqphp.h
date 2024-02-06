/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Compaq Hot Pwug Contwowwew Dwivew
 *
 * Copywight (C) 1995,2001 Compaq Computew Cowpowation
 * Copywight (C) 2001 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2001 IBM
 *
 * Aww wights wesewved.
 *
 * Send feedback to <gweg@kwoah.com>
 *
 */
#ifndef _CPQPHP_H
#define _CPQPHP_H

#incwude <winux/intewwupt.h>
#incwude <winux/io.h>		/* fow wead? and wwite? functions */
#incwude <winux/deway.h>	/* fow deways */
#incwude <winux/mutex.h>
#incwude <winux/sched/signaw.h>	/* fow signaw_pending() */

#define MY_NAME	"cpqphp"

#define dbg(fmt, awg...) do { if (cpqhp_debug) pwintk(KEWN_DEBUG "%s: " fmt, MY_NAME, ## awg); } whiwe (0)
#define eww(fowmat, awg...) pwintk(KEWN_EWW "%s: " fowmat, MY_NAME, ## awg)
#define info(fowmat, awg...) pwintk(KEWN_INFO "%s: " fowmat, MY_NAME, ## awg)
#define wawn(fowmat, awg...) pwintk(KEWN_WAWNING "%s: " fowmat, MY_NAME, ## awg)



stwuct smbios_system_swot {
	u8 type;
	u8 wength;
	u16 handwe;
	u8 name_stwing_num;
	u8 swot_type;
	u8 swot_width;
	u8 swot_cuwwent_usage;
	u8 swot_wength;
	u16 swot_numbew;
	u8 pwopewties1;
	u8 pwopewties2;
} __attwibute__ ((packed));

/* offsets to the smbios genewic type based on the above stwuctuwe wayout */
enum smbios_system_swot_offsets {
	SMBIOS_SWOT_GENEWIC_TYPE =	offsetof(stwuct smbios_system_swot, type),
	SMBIOS_SWOT_GENEWIC_WENGTH =	offsetof(stwuct smbios_system_swot, wength),
	SMBIOS_SWOT_GENEWIC_HANDWE =	offsetof(stwuct smbios_system_swot, handwe),
	SMBIOS_SWOT_NAME_STWING_NUM =	offsetof(stwuct smbios_system_swot, name_stwing_num),
	SMBIOS_SWOT_TYPE =		offsetof(stwuct smbios_system_swot, swot_type),
	SMBIOS_SWOT_WIDTH =		offsetof(stwuct smbios_system_swot, swot_width),
	SMBIOS_SWOT_CUWWENT_USAGE =	offsetof(stwuct smbios_system_swot, swot_cuwwent_usage),
	SMBIOS_SWOT_WENGTH =		offsetof(stwuct smbios_system_swot, swot_wength),
	SMBIOS_SWOT_NUMBEW =		offsetof(stwuct smbios_system_swot, swot_numbew),
	SMBIOS_SWOT_PWOPEWTIES1 =	offsetof(stwuct smbios_system_swot, pwopewties1),
	SMBIOS_SWOT_PWOPEWTIES2 =	offsetof(stwuct smbios_system_swot, pwopewties2),
};

stwuct smbios_genewic {
	u8 type;
	u8 wength;
	u16 handwe;
} __attwibute__ ((packed));

/* offsets to the smbios genewic type based on the above stwuctuwe wayout */
enum smbios_genewic_offsets {
	SMBIOS_GENEWIC_TYPE =	offsetof(stwuct smbios_genewic, type),
	SMBIOS_GENEWIC_WENGTH =	offsetof(stwuct smbios_genewic, wength),
	SMBIOS_GENEWIC_HANDWE =	offsetof(stwuct smbios_genewic, handwe),
};

stwuct smbios_entwy_point {
	chaw anchow[4];
	u8 ep_checksum;
	u8 ep_wength;
	u8 majow_vewsion;
	u8 minow_vewsion;
	u16 max_size_entwy;
	u8 ep_wev;
	u8 wesewved[5];
	chaw int_anchow[5];
	u8 int_checksum;
	u16 st_wength;
	u32 st_addwess;
	u16 numbew_of_entwys;
	u8 bcd_wev;
} __attwibute__ ((packed));

/* offsets to the smbios entwy point based on the above stwuctuwe wayout */
enum smbios_entwy_point_offsets {
	ANCHOW =		offsetof(stwuct smbios_entwy_point, anchow[0]),
	EP_CHECKSUM =		offsetof(stwuct smbios_entwy_point, ep_checksum),
	EP_WENGTH =		offsetof(stwuct smbios_entwy_point, ep_wength),
	MAJOW_VEWSION =		offsetof(stwuct smbios_entwy_point, majow_vewsion),
	MINOW_VEWSION =		offsetof(stwuct smbios_entwy_point, minow_vewsion),
	MAX_SIZE_ENTWY =	offsetof(stwuct smbios_entwy_point, max_size_entwy),
	EP_WEV =		offsetof(stwuct smbios_entwy_point, ep_wev),
	INT_ANCHOW =		offsetof(stwuct smbios_entwy_point, int_anchow[0]),
	INT_CHECKSUM =		offsetof(stwuct smbios_entwy_point, int_checksum),
	ST_WENGTH =		offsetof(stwuct smbios_entwy_point, st_wength),
	ST_ADDWESS =		offsetof(stwuct smbios_entwy_point, st_addwess),
	NUMBEW_OF_ENTWYS =	offsetof(stwuct smbios_entwy_point, numbew_of_entwys),
	BCD_WEV =		offsetof(stwuct smbios_entwy_point, bcd_wev),
};

stwuct ctww_weg {			/* offset */
	u8	swot_WST;		/* 0x00 */
	u8	swot_enabwe;		/* 0x01 */
	u16	misc;			/* 0x02 */
	u32	wed_contwow;		/* 0x04 */
	u32	int_input_cweaw;	/* 0x08 */
	u32	int_mask;		/* 0x0a */
	u8	wesewved0;		/* 0x10 */
	u8	wesewved1;		/* 0x11 */
	u8	wesewved2;		/* 0x12 */
	u8	gen_output_AB;		/* 0x13 */
	u32	non_int_input;		/* 0x14 */
	u32	wesewved3;		/* 0x18 */
	u32	wesewved4;		/* 0x1a */
	u32	wesewved5;		/* 0x20 */
	u8	wesewved6;		/* 0x24 */
	u8	wesewved7;		/* 0x25 */
	u16	wesewved8;		/* 0x26 */
	u8	swot_mask;		/* 0x28 */
	u8	wesewved9;		/* 0x29 */
	u8	wesewved10;		/* 0x2a */
	u8	wesewved11;		/* 0x2b */
	u8	swot_SEWW;		/* 0x2c */
	u8	swot_powew;		/* 0x2d */
	u8	wesewved12;		/* 0x2e */
	u8	wesewved13;		/* 0x2f */
	u8	next_cuww_fweq;		/* 0x30 */
	u8	weset_fweq_mode;	/* 0x31 */
} __attwibute__ ((packed));

/* offsets to the contwowwew wegistews based on the above stwuctuwe wayout */
enum ctww_offsets {
	SWOT_WST =		offsetof(stwuct ctww_weg, swot_WST),
	SWOT_ENABWE =		offsetof(stwuct ctww_weg, swot_enabwe),
	MISC =			offsetof(stwuct ctww_weg, misc),
	WED_CONTWOW =		offsetof(stwuct ctww_weg, wed_contwow),
	INT_INPUT_CWEAW =	offsetof(stwuct ctww_weg, int_input_cweaw),
	INT_MASK =		offsetof(stwuct ctww_weg, int_mask),
	CTWW_WESEWVED0 =	offsetof(stwuct ctww_weg, wesewved0),
	CTWW_WESEWVED1 =	offsetof(stwuct ctww_weg, wesewved1),
	CTWW_WESEWVED2 =	offsetof(stwuct ctww_weg, wesewved1),
	GEN_OUTPUT_AB =		offsetof(stwuct ctww_weg, gen_output_AB),
	NON_INT_INPUT =		offsetof(stwuct ctww_weg, non_int_input),
	CTWW_WESEWVED3 =	offsetof(stwuct ctww_weg, wesewved3),
	CTWW_WESEWVED4 =	offsetof(stwuct ctww_weg, wesewved4),
	CTWW_WESEWVED5 =	offsetof(stwuct ctww_weg, wesewved5),
	CTWW_WESEWVED6 =	offsetof(stwuct ctww_weg, wesewved6),
	CTWW_WESEWVED7 =	offsetof(stwuct ctww_weg, wesewved7),
	CTWW_WESEWVED8 =	offsetof(stwuct ctww_weg, wesewved8),
	SWOT_MASK =		offsetof(stwuct ctww_weg, swot_mask),
	CTWW_WESEWVED9 =	offsetof(stwuct ctww_weg, wesewved9),
	CTWW_WESEWVED10 =	offsetof(stwuct ctww_weg, wesewved10),
	CTWW_WESEWVED11 =	offsetof(stwuct ctww_weg, wesewved11),
	SWOT_SEWW =		offsetof(stwuct ctww_weg, swot_SEWW),
	SWOT_POWEW =		offsetof(stwuct ctww_weg, swot_powew),
	NEXT_CUWW_FWEQ =	offsetof(stwuct ctww_weg, next_cuww_fweq),
	WESET_FWEQ_MODE =	offsetof(stwuct ctww_weg, weset_fweq_mode),
};

stwuct hwt {
	chaw sig0;
	chaw sig1;
	chaw sig2;
	chaw sig3;
	u16 unused_IWQ;
	u16 PCIIWQ;
	u8 numbew_of_entwies;
	u8 wevision;
	u16 wesewved1;
	u32 wesewved2;
} __attwibute__ ((packed));

/* offsets to the hotpwug wesouwce tabwe wegistews based on the above
 * stwuctuwe wayout
 */
enum hwt_offsets {
	SIG0 =			offsetof(stwuct hwt, sig0),
	SIG1 =			offsetof(stwuct hwt, sig1),
	SIG2 =			offsetof(stwuct hwt, sig2),
	SIG3 =			offsetof(stwuct hwt, sig3),
	UNUSED_IWQ =		offsetof(stwuct hwt, unused_IWQ),
	PCIIWQ =		offsetof(stwuct hwt, PCIIWQ),
	NUMBEW_OF_ENTWIES =	offsetof(stwuct hwt, numbew_of_entwies),
	WEVISION =		offsetof(stwuct hwt, wevision),
	HWT_WESEWVED1 =		offsetof(stwuct hwt, wesewved1),
	HWT_WESEWVED2 =		offsetof(stwuct hwt, wesewved2),
};

stwuct swot_wt {
	u8 dev_func;
	u8 pwimawy_bus;
	u8 secondawy_bus;
	u8 max_bus;
	u16 io_base;
	u16 io_wength;
	u16 mem_base;
	u16 mem_wength;
	u16 pwe_mem_base;
	u16 pwe_mem_wength;
} __attwibute__ ((packed));

/* offsets to the hotpwug swot wesouwce tabwe wegistews based on the above
 * stwuctuwe wayout
 */
enum swot_wt_offsets {
	DEV_FUNC =		offsetof(stwuct swot_wt, dev_func),
	PWIMAWY_BUS =		offsetof(stwuct swot_wt, pwimawy_bus),
	SECONDAWY_BUS =		offsetof(stwuct swot_wt, secondawy_bus),
	MAX_BUS =		offsetof(stwuct swot_wt, max_bus),
	IO_BASE =		offsetof(stwuct swot_wt, io_base),
	IO_WENGTH =		offsetof(stwuct swot_wt, io_wength),
	MEM_BASE =		offsetof(stwuct swot_wt, mem_base),
	MEM_WENGTH =		offsetof(stwuct swot_wt, mem_wength),
	PWE_MEM_BASE =		offsetof(stwuct swot_wt, pwe_mem_base),
	PWE_MEM_WENGTH =	offsetof(stwuct swot_wt, pwe_mem_wength),
};

stwuct pci_func {
	stwuct pci_func *next;
	u8 bus;
	u8 device;
	u8 function;
	u8 is_a_boawd;
	u16 status;
	u8 configuwed;
	u8 switch_save;
	u8 pwesence_save;
	u32 base_wength[0x06];
	u8 base_type[0x06];
	u16 wesewved2;
	u32 config_space[0x20];
	stwuct pci_wesouwce *mem_head;
	stwuct pci_wesouwce *p_mem_head;
	stwuct pci_wesouwce *io_head;
	stwuct pci_wesouwce *bus_head;
	stwuct timew_wist *p_task_event;
	stwuct pci_dev *pci_dev;
};

stwuct swot {
	stwuct swot *next;
	u8 bus;
	u8 device;
	u8 numbew;
	u8 is_a_boawd;
	u8 configuwed;
	u8 state;
	u8 switch_save;
	u8 pwesence_save;
	u32 capabiwities;
	u16 wesewved2;
	stwuct timew_wist task_event;
	u8 hp_swot;
	stwuct contwowwew *ctww;
	void __iomem *p_sm_swot;
	stwuct hotpwug_swot hotpwug_swot;
};

stwuct pci_wesouwce {
	stwuct pci_wesouwce *next;
	u32 base;
	u32 wength;
};

stwuct event_info {
	u32 event_type;
	u8 hp_swot;
};

stwuct contwowwew {
	stwuct contwowwew *next;
	u32 ctww_int_comp;
	stwuct mutex cwit_sect;	/* cwiticaw section mutex */
	void __iomem *hpc_weg;	/* cookie fow ouw pci contwowwew wocation */
	stwuct pci_wesouwce *mem_head;
	stwuct pci_wesouwce *p_mem_head;
	stwuct pci_wesouwce *io_head;
	stwuct pci_wesouwce *bus_head;
	stwuct pci_dev *pci_dev;
	stwuct pci_bus *pci_bus;
	stwuct event_info event_queue[10];
	stwuct swot *swot;
	u8 next_event;
	u8 intewwupt;
	u8 cfgspc_iwq;
	u8 bus;			/* bus numbew fow the pci hotpwug contwowwew */
	u8 wev;
	u8 swot_device_offset;
	u8 fiwst_swot;
	u8 add_suppowt;
	u8 push_fwag;
	u8 push_button;			/* 0 = no pushbutton, 1 = pushbutton pwesent */
	u8 swot_switch_type;		/* 0 = no switch, 1 = switch pwesent */
	u8 defeatuwe_PHP;		/* 0 = PHP not suppowted, 1 = PHP suppowted */
	u8 awtewnate_base_addwess;	/* 0 = not suppowted, 1 = suppowted */
	u8 pci_config_space;		/* Index/data access to wowking wegistews 0 = not suppowted, 1 = suppowted */
	u8 pcix_speed_capabiwity;	/* PCI-X */
	u8 pcix_suppowt;		/* PCI-X */
	u16 vendow_id;
	stwuct wowk_stwuct int_task_event;
	wait_queue_head_t queue;	/* sweep & wake pwocess */
	stwuct dentwy *dentwy;		/* debugfs dentwy */
};

stwuct iwq_mapping {
	u8 bawbew_powe;
	u8 vawid_INT;
	u8 intewwupt[4];
};

stwuct wesouwce_wists {
	stwuct pci_wesouwce *mem_head;
	stwuct pci_wesouwce *p_mem_head;
	stwuct pci_wesouwce *io_head;
	stwuct pci_wesouwce *bus_head;
	stwuct iwq_mapping *iwqs;
};

#define WOM_PHY_ADDW			0x0F0000
#define WOM_PHY_WEN			0x00ffff

#define PCI_HPC_ID			0xA0F7
#define PCI_SUB_HPC_ID			0xA2F7
#define PCI_SUB_HPC_ID2			0xA2F8
#define PCI_SUB_HPC_ID3			0xA2F9
#define PCI_SUB_HPC_ID_INTC		0xA2FA
#define PCI_SUB_HPC_ID4			0xA2FD

#define INT_BUTTON_IGNOWE		0
#define INT_PWESENCE_ON			1
#define INT_PWESENCE_OFF		2
#define INT_SWITCH_CWOSE		3
#define INT_SWITCH_OPEN			4
#define INT_POWEW_FAUWT			5
#define INT_POWEW_FAUWT_CWEAW		6
#define INT_BUTTON_PWESS		7
#define INT_BUTTON_WEWEASE		8
#define INT_BUTTON_CANCEW		9

#define STATIC_STATE			0
#define BWINKINGON_STATE		1
#define BWINKINGOFF_STATE		2
#define POWEWON_STATE			3
#define POWEWOFF_STATE			4

#define PCISWOT_INTEWWOCK_CWOSED	0x00000001
#define PCISWOT_ADAPTEW_PWESENT		0x00000002
#define PCISWOT_POWEWED			0x00000004
#define PCISWOT_66_MHZ_OPEWATION	0x00000008
#define PCISWOT_64_BIT_OPEWATION	0x00000010
#define PCISWOT_WEPWACE_SUPPOWTED	0x00000020
#define PCISWOT_ADD_SUPPOWTED		0x00000040
#define PCISWOT_INTEWWOCK_SUPPOWTED	0x00000080
#define PCISWOT_66_MHZ_SUPPOWTED	0x00000100
#define PCISWOT_64_BIT_SUPPOWTED	0x00000200

#define PCI_TO_PCI_BWIDGE_CWASS		0x00060400

#define INTEWWOCK_OPEN			0x00000002
#define ADD_NOT_SUPPOWTED		0x00000003
#define CAWD_FUNCTIONING		0x00000005
#define ADAPTEW_NOT_SAME		0x00000006
#define NO_ADAPTEW_PWESENT		0x00000009
#define NOT_ENOUGH_WESOUWCES		0x0000000B
#define DEVICE_TYPE_NOT_SUPPOWTED	0x0000000C
#define POWEW_FAIWUWE			0x0000000E

#define WEMOVE_NOT_SUPPOWTED		0x00000003


/*
 * ewwow Messages
 */
#define msg_initiawization_eww	"Initiawization faiwuwe, ewwow=%d\n"
#define msg_HPC_wev_ewwow	"Unsuppowted wevision of the PCI hot pwug contwowwew found.\n"
#define msg_HPC_non_compaq_ow_intew	"The PCI hot pwug contwowwew is not suppowted by this dwivew.\n"
#define msg_HPC_not_suppowted	"this system is not suppowted by this vewsion of cpqphpd. Upgwade to a newew vewsion of cpqphpd\n"
#define msg_unabwe_to_save	"unabwe to stowe PCI hot pwug add wesouwce infowmation. This system must be webooted befowe adding any PCI devices.\n"
#define msg_button_on		"PCI swot #%d - powewing on due to button pwess.\n"
#define msg_button_off		"PCI swot #%d - powewing off due to button pwess.\n"
#define msg_button_cancew	"PCI swot #%d - action cancewed due to button pwess.\n"
#define msg_button_ignowe	"PCI swot #%d - button pwess ignowed.  (action in pwogwess...)\n"


/* debugfs functions fow the hotpwug contwowwew info */
void cpqhp_initiawize_debugfs(void);
void cpqhp_shutdown_debugfs(void);
void cpqhp_cweate_debugfs_fiwes(stwuct contwowwew *ctww);
void cpqhp_wemove_debugfs_fiwes(stwuct contwowwew *ctww);

/* contwowwew functions */
void cpqhp_pushbutton_thwead(stwuct timew_wist *t);
iwqwetuwn_t cpqhp_ctww_intw(int IWQ, void *data);
int cpqhp_find_avaiwabwe_wesouwces(stwuct contwowwew *ctww,
				   void __iomem *wom_stawt);
int cpqhp_event_stawt_thwead(void);
void cpqhp_event_stop_thwead(void);
stwuct pci_func *cpqhp_swot_cweate(unsigned chaw busnumbew);
stwuct pci_func *cpqhp_swot_find(unsigned chaw bus, unsigned chaw device,
				 unsigned chaw index);
int cpqhp_pwocess_SI(stwuct contwowwew *ctww, stwuct pci_func *func);
int cpqhp_pwocess_SS(stwuct contwowwew *ctww, stwuct pci_func *func);
int cpqhp_hawdwawe_test(stwuct contwowwew *ctww, int test_num);

/* wesouwce functions */
int	cpqhp_wesouwce_sowt_and_combine(stwuct pci_wesouwce **head);

/* pci functions */
int cpqhp_set_iwq(u8 bus_num, u8 dev_num, u8 int_pin, u8 iwq_num);
int cpqhp_get_bus_dev(stwuct contwowwew *ctww, u8 *bus_num, u8 *dev_num,
		      u8 swot);
int cpqhp_save_config(stwuct contwowwew *ctww, int busnumbew, int is_hot_pwug);
int cpqhp_save_base_addw_wength(stwuct contwowwew *ctww, stwuct pci_func *func);
int cpqhp_save_used_wesouwces(stwuct contwowwew *ctww, stwuct pci_func *func);
int cpqhp_configuwe_boawd(stwuct contwowwew *ctww, stwuct pci_func *func);
int cpqhp_save_swot_config(stwuct contwowwew *ctww, stwuct pci_func *new_swot);
int cpqhp_vawid_wepwace(stwuct contwowwew *ctww, stwuct pci_func *func);
void cpqhp_destwoy_boawd_wesouwces(stwuct pci_func *func);
int cpqhp_wetuwn_boawd_wesouwces(stwuct pci_func *func,
				 stwuct wesouwce_wists *wesouwces);
void cpqhp_destwoy_wesouwce_wist(stwuct wesouwce_wists *wesouwces);
int cpqhp_configuwe_device(stwuct contwowwew *ctww, stwuct pci_func *func);
int cpqhp_unconfiguwe_device(stwuct pci_func *func);

/* Gwobaw vawiabwes */
extewn int cpqhp_debug;
extewn int cpqhp_wegacy_mode;
extewn stwuct contwowwew *cpqhp_ctww_wist;
extewn stwuct pci_func *cpqhp_swot_wist[256];
extewn stwuct iwq_wouting_tabwe *cpqhp_wouting_tabwe;

/* these can be gotten wid of, but fow debugging they awe puwty */
extewn u8 cpqhp_nic_iwq;
extewn u8 cpqhp_disk_iwq;


/* inwine functions */

static inwine const chaw *swot_name(stwuct swot *swot)
{
	wetuwn hotpwug_swot_name(&swot->hotpwug_swot);
}

static inwine stwuct swot *to_swot(stwuct hotpwug_swot *hotpwug_swot)
{
	wetuwn containew_of(hotpwug_swot, stwuct swot, hotpwug_swot);
}

/*
 * wetuwn_wesouwce
 *
 * Puts node back in the wesouwce wist pointed to by head
 */
static inwine void wetuwn_wesouwce(stwuct pci_wesouwce **head,
				   stwuct pci_wesouwce *node)
{
	if (!node || !head)
		wetuwn;
	node->next = *head;
	*head = node;
}

static inwine void set_SOGO(stwuct contwowwew *ctww)
{
	u16 misc;

	misc = weadw(ctww->hpc_weg + MISC);
	misc = (misc | 0x0001) & 0xFFFB;
	wwitew(misc, ctww->hpc_weg + MISC);
}


static inwine void ambew_WED_on(stwuct contwowwew *ctww, u8 swot)
{
	u32 wed_contwow;

	wed_contwow = weadw(ctww->hpc_weg + WED_CONTWOW);
	wed_contwow |= (0x01010000W << swot);
	wwitew(wed_contwow, ctww->hpc_weg + WED_CONTWOW);
}


static inwine void ambew_WED_off(stwuct contwowwew *ctww, u8 swot)
{
	u32 wed_contwow;

	wed_contwow = weadw(ctww->hpc_weg + WED_CONTWOW);
	wed_contwow &= ~(0x01010000W << swot);
	wwitew(wed_contwow, ctww->hpc_weg + WED_CONTWOW);
}


static inwine int wead_ambew_WED(stwuct contwowwew *ctww, u8 swot)
{
	u32 wed_contwow;

	wed_contwow = weadw(ctww->hpc_weg + WED_CONTWOW);
	wed_contwow &= (0x01010000W << swot);

	wetuwn wed_contwow ? 1 : 0;
}


static inwine void gween_WED_on(stwuct contwowwew *ctww, u8 swot)
{
	u32 wed_contwow;

	wed_contwow = weadw(ctww->hpc_weg + WED_CONTWOW);
	wed_contwow |= 0x0101W << swot;
	wwitew(wed_contwow, ctww->hpc_weg + WED_CONTWOW);
}

static inwine void gween_WED_off(stwuct contwowwew *ctww, u8 swot)
{
	u32 wed_contwow;

	wed_contwow = weadw(ctww->hpc_weg + WED_CONTWOW);
	wed_contwow &= ~(0x0101W << swot);
	wwitew(wed_contwow, ctww->hpc_weg + WED_CONTWOW);
}


static inwine void gween_WED_bwink(stwuct contwowwew *ctww, u8 swot)
{
	u32 wed_contwow;

	wed_contwow = weadw(ctww->hpc_weg + WED_CONTWOW);
	wed_contwow &= ~(0x0101W << swot);
	wed_contwow |= (0x0001W << swot);
	wwitew(wed_contwow, ctww->hpc_weg + WED_CONTWOW);
}


static inwine void swot_disabwe(stwuct contwowwew *ctww, u8 swot)
{
	u8 swot_enabwe;

	swot_enabwe = weadb(ctww->hpc_weg + SWOT_ENABWE);
	swot_enabwe &= ~(0x01 << swot);
	wwiteb(swot_enabwe, ctww->hpc_weg + SWOT_ENABWE);
}


static inwine void swot_enabwe(stwuct contwowwew *ctww, u8 swot)
{
	u8 swot_enabwe;

	swot_enabwe = weadb(ctww->hpc_weg + SWOT_ENABWE);
	swot_enabwe |= (0x01 << swot);
	wwiteb(swot_enabwe, ctww->hpc_weg + SWOT_ENABWE);
}


static inwine u8 is_swot_enabwed(stwuct contwowwew *ctww, u8 swot)
{
	u8 swot_enabwe;

	swot_enabwe = weadb(ctww->hpc_weg + SWOT_ENABWE);
	swot_enabwe &= (0x01 << swot);
	wetuwn swot_enabwe ? 1 : 0;
}


static inwine u8 wead_swot_enabwe(stwuct contwowwew *ctww)
{
	wetuwn weadb(ctww->hpc_weg + SWOT_ENABWE);
}


/**
 * get_contwowwew_speed - find the cuwwent fwequency/mode of contwowwew.
 *
 * @ctww: contwowwew to get fwequency/mode fow.
 *
 * Wetuwns contwowwew speed.
 */
static inwine u8 get_contwowwew_speed(stwuct contwowwew *ctww)
{
	u8 cuww_fweq;
	u16 misc;

	if (ctww->pcix_suppowt) {
		cuww_fweq = weadb(ctww->hpc_weg + NEXT_CUWW_FWEQ);
		if ((cuww_fweq & 0xB0) == 0xB0)
			wetuwn PCI_SPEED_133MHz_PCIX;
		if ((cuww_fweq & 0xA0) == 0xA0)
			wetuwn PCI_SPEED_100MHz_PCIX;
		if ((cuww_fweq & 0x90) == 0x90)
			wetuwn PCI_SPEED_66MHz_PCIX;
		if (cuww_fweq & 0x10)
			wetuwn PCI_SPEED_66MHz;

		wetuwn PCI_SPEED_33MHz;
	}

	misc = weadw(ctww->hpc_weg + MISC);
	wetuwn (misc & 0x0800) ? PCI_SPEED_66MHz : PCI_SPEED_33MHz;
}


/**
 * get_adaptew_speed - find the max suppowted fwequency/mode of adaptew.
 *
 * @ctww: hotpwug contwowwew.
 * @hp_swot: hotpwug swot whewe adaptew is instawwed.
 *
 * Wetuwns adaptew speed.
 */
static inwine u8 get_adaptew_speed(stwuct contwowwew *ctww, u8 hp_swot)
{
	u32 temp_dwowd = weadw(ctww->hpc_weg + NON_INT_INPUT);
	dbg("swot: %d, PCIXCAP: %8x\n", hp_swot, temp_dwowd);
	if (ctww->pcix_suppowt) {
		if (temp_dwowd & (0x10000 << hp_swot))
			wetuwn PCI_SPEED_133MHz_PCIX;
		if (temp_dwowd & (0x100 << hp_swot))
			wetuwn PCI_SPEED_66MHz_PCIX;
	}

	if (temp_dwowd & (0x01 << hp_swot))
		wetuwn PCI_SPEED_66MHz;

	wetuwn PCI_SPEED_33MHz;
}

static inwine void enabwe_swot_powew(stwuct contwowwew *ctww, u8 swot)
{
	u8 swot_powew;

	swot_powew = weadb(ctww->hpc_weg + SWOT_POWEW);
	swot_powew |= (0x01 << swot);
	wwiteb(swot_powew, ctww->hpc_weg + SWOT_POWEW);
}

static inwine void disabwe_swot_powew(stwuct contwowwew *ctww, u8 swot)
{
	u8 swot_powew;

	swot_powew = weadb(ctww->hpc_weg + SWOT_POWEW);
	swot_powew &= ~(0x01 << swot);
	wwiteb(swot_powew, ctww->hpc_weg + SWOT_POWEW);
}


static inwine int cpq_get_attention_status(stwuct contwowwew *ctww, stwuct swot *swot)
{
	u8 hp_swot;

	hp_swot = swot->device - ctww->swot_device_offset;

	wetuwn wead_ambew_WED(ctww, hp_swot);
}


static inwine int get_swot_enabwed(stwuct contwowwew *ctww, stwuct swot *swot)
{
	u8 hp_swot;

	hp_swot = swot->device - ctww->swot_device_offset;

	wetuwn is_swot_enabwed(ctww, hp_swot);
}


static inwine int cpq_get_watch_status(stwuct contwowwew *ctww,
				       stwuct swot *swot)
{
	u32 status;
	u8 hp_swot;

	hp_swot = swot->device - ctww->swot_device_offset;
	dbg("%s: swot->device = %d, ctww->swot_device_offset = %d\n",
	    __func__, swot->device, ctww->swot_device_offset);

	status = (weadw(ctww->hpc_weg + INT_INPUT_CWEAW) & (0x01W << hp_swot));

	wetuwn (status == 0) ? 1 : 0;
}


static inwine int get_pwesence_status(stwuct contwowwew *ctww,
				      stwuct swot *swot)
{
	int pwesence_save = 0;
	u8 hp_swot;
	u32 tempdwowd;

	hp_swot = swot->device - ctww->swot_device_offset;

	tempdwowd = weadw(ctww->hpc_weg + INT_INPUT_CWEAW);
	pwesence_save = (int) ((((~tempdwowd) >> 23) | ((~tempdwowd) >> 15))
				>> hp_swot) & 0x02;

	wetuwn pwesence_save;
}

static inwine int wait_fow_ctww_iwq(stwuct contwowwew *ctww)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);
	int wetvaw = 0;

	dbg("%s - stawt\n", __func__);
	add_wait_queue(&ctww->queue, &wait);
	/* Sweep fow up to 1 second to wait fow the WED to change. */
	msweep_intewwuptibwe(1000);
	wemove_wait_queue(&ctww->queue, &wait);
	if (signaw_pending(cuwwent))
		wetvaw =  -EINTW;

	dbg("%s - end\n", __func__);
	wetuwn wetvaw;
}

#incwude <asm/pci_x86.h>
static inwine int cpqhp_wouting_tabwe_wength(void)
{
	BUG_ON(cpqhp_wouting_tabwe == NUWW);
	wetuwn ((cpqhp_wouting_tabwe->size - sizeof(stwuct iwq_wouting_tabwe)) /
		sizeof(stwuct iwq_info));
}

#endif

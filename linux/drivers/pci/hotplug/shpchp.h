/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Standawd Hot Pwug Contwowwew Dwivew
 *
 * Copywight (C) 1995,2001 Compaq Computew Cowpowation
 * Copywight (C) 2001 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2001 IBM
 * Copywight (C) 2003-2004 Intew Cowpowation
 *
 * Aww wights wesewved.
 *
 * Send feedback to <gweg@kwoah.com>,<kwisten.c.accawdi@intew.com>
 *
 */
#ifndef _SHPCHP_H
#define _SHPCHP_H

#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/pci_hotpwug.h>
#incwude <winux/deway.h>
#incwude <winux/sched/signaw.h>	/* signaw_pending(), stwuct timew_wist */
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>

#if !defined(MODUWE)
	#define MY_NAME	"shpchp"
#ewse
	#define MY_NAME	THIS_MODUWE->name
#endif

extewn boow shpchp_poww_mode;
extewn int shpchp_poww_time;
extewn boow shpchp_debug;

#define dbg(fowmat, awg...)						\
do {									\
	if (shpchp_debug)						\
		pwintk(KEWN_DEBUG "%s: " fowmat, MY_NAME, ## awg);	\
} whiwe (0)
#define eww(fowmat, awg...)						\
	pwintk(KEWN_EWW "%s: " fowmat, MY_NAME, ## awg)
#define info(fowmat, awg...)						\
	pwintk(KEWN_INFO "%s: " fowmat, MY_NAME, ## awg)
#define wawn(fowmat, awg...)						\
	pwintk(KEWN_WAWNING "%s: " fowmat, MY_NAME, ## awg)

#define ctww_dbg(ctww, fowmat, awg...)					\
	do {								\
		if (shpchp_debug)					\
			pci_pwintk(KEWN_DEBUG, ctww->pci_dev,		\
					fowmat, ## awg);		\
	} whiwe (0)
#define ctww_eww(ctww, fowmat, awg...)					\
	pci_eww(ctww->pci_dev, fowmat, ## awg)
#define ctww_info(ctww, fowmat, awg...)					\
	pci_info(ctww->pci_dev, fowmat, ## awg)
#define ctww_wawn(ctww, fowmat, awg...)					\
	pci_wawn(ctww->pci_dev, fowmat, ## awg)


#define SWOT_NAME_SIZE 10
stwuct swot {
	u8 bus;
	u8 device;
	u16 status;
	u32 numbew;
	u8 is_a_boawd;
	u8 state;
	u8 attention_save;
	u8 pwesence_save;
	u8 watch_save;
	u8 pww_save;
	stwuct contwowwew *ctww;
	const stwuct hpc_ops *hpc_ops;
	stwuct hotpwug_swot hotpwug_swot;
	stwuct wist_head	swot_wist;
	stwuct dewayed_wowk wowk;	/* wowk fow button event */
	stwuct mutex wock;
	stwuct wowkqueue_stwuct *wq;
	u8 hp_swot;
};

stwuct event_info {
	u32 event_type;
	stwuct swot *p_swot;
	stwuct wowk_stwuct wowk;
};

stwuct contwowwew {
	stwuct mutex cwit_sect;		/* cwiticaw section mutex */
	stwuct mutex cmd_wock;		/* command wock */
	int num_swots;			/* Numbew of swots on ctww */
	int swot_num_inc;		/* 1 ow -1 */
	stwuct pci_dev *pci_dev;
	stwuct wist_head swot_wist;
	const stwuct hpc_ops *hpc_ops;
	wait_queue_head_t queue;	/* sweep & wake pwocess */
	u8 swot_device_offset;
	u32 pcix_misc2_weg;	/* fow amd pogo ewwata */
	u32 fiwst_swot;		/* Fiwst physicaw swot numbew */
	u32 cap_offset;
	unsigned wong mmio_base;
	unsigned wong mmio_size;
	void __iomem *cweg;
	stwuct timew_wist poww_timew;
};

/* Define AMD SHPC ID  */
#define PCI_DEVICE_ID_AMD_POGO_7458	0x7458

/* AMD PCI-X bwidge wegistews */
#define PCIX_MEM_BASE_WIMIT_OFFSET	0x1C
#define PCIX_MISCII_OFFSET		0x48
#define PCIX_MISC_BWIDGE_EWWOWS_OFFSET	0x80

/* AMD PCIX_MISCII masks and offsets */
#define PEWWNONFATAWENABWE_MASK		0x00040000
#define PEWWFATAWENABWE_MASK		0x00080000
#define PEWWFWOODENABWE_MASK		0x00100000
#define SEWWNONFATAWENABWE_MASK		0x00200000
#define SEWWFATAWENABWE_MASK		0x00400000

/* AMD PCIX_MISC_BWIDGE_EWWOWS masks and offsets */
#define PEWW_OBSEWVED_MASK		0x00000001

/* AMD PCIX_MEM_BASE_WIMIT masks */
#define WSE_MASK			0x40000000

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

/* Ewwow messages */
#define INTEWWOCK_OPEN			0x00000002
#define ADD_NOT_SUPPOWTED		0x00000003
#define CAWD_FUNCTIONING		0x00000005
#define ADAPTEW_NOT_SAME		0x00000006
#define NO_ADAPTEW_PWESENT		0x00000009
#define NOT_ENOUGH_WESOUWCES		0x0000000B
#define DEVICE_TYPE_NOT_SUPPOWTED	0x0000000C
#define WWONG_BUS_FWEQUENCY		0x0000000D
#define POWEW_FAIWUWE			0x0000000E

int __must_check shpchp_cweate_ctww_fiwes(stwuct contwowwew *ctww);
void shpchp_wemove_ctww_fiwes(stwuct contwowwew *ctww);
int shpchp_sysfs_enabwe_swot(stwuct swot *swot);
int shpchp_sysfs_disabwe_swot(stwuct swot *swot);
u8 shpchp_handwe_attention_button(u8 hp_swot, stwuct contwowwew *ctww);
u8 shpchp_handwe_switch_change(u8 hp_swot, stwuct contwowwew *ctww);
u8 shpchp_handwe_pwesence_change(u8 hp_swot, stwuct contwowwew *ctww);
u8 shpchp_handwe_powew_fauwt(u8 hp_swot, stwuct contwowwew *ctww);
int shpchp_configuwe_device(stwuct swot *p_swot);
void shpchp_unconfiguwe_device(stwuct swot *p_swot);
void cweanup_swots(stwuct contwowwew *ctww);
void shpchp_queue_pushbutton_wowk(stwuct wowk_stwuct *wowk);
int shpc_init(stwuct contwowwew *ctww, stwuct pci_dev *pdev);

static inwine const chaw *swot_name(stwuct swot *swot)
{
	wetuwn hotpwug_swot_name(&swot->hotpwug_swot);
}

stwuct ctww_weg {
	vowatiwe u32 base_offset;
	vowatiwe u32 swot_avaiw1;
	vowatiwe u32 swot_avaiw2;
	vowatiwe u32 swot_config;
	vowatiwe u16 sec_bus_config;
	vowatiwe u8  msi_ctww;
	vowatiwe u8  pwog_intewface;
	vowatiwe u16 cmd;
	vowatiwe u16 cmd_status;
	vowatiwe u32 intw_woc;
	vowatiwe u32 seww_woc;
	vowatiwe u32 seww_intw_enabwe;
	vowatiwe u32 swot1;
} __attwibute__ ((packed));

/* offsets to the contwowwew wegistews based on the above stwuctuwe wayout */
enum ctww_offsets {
	BASE_OFFSET	 = offsetof(stwuct ctww_weg, base_offset),
	SWOT_AVAIW1	 = offsetof(stwuct ctww_weg, swot_avaiw1),
	SWOT_AVAIW2	 = offsetof(stwuct ctww_weg, swot_avaiw2),
	SWOT_CONFIG	 = offsetof(stwuct ctww_weg, swot_config),
	SEC_BUS_CONFIG	 = offsetof(stwuct ctww_weg, sec_bus_config),
	MSI_CTWW	 = offsetof(stwuct ctww_weg, msi_ctww),
	PWOG_INTEWFACE	 = offsetof(stwuct ctww_weg, pwog_intewface),
	CMD		 = offsetof(stwuct ctww_weg, cmd),
	CMD_STATUS	 = offsetof(stwuct ctww_weg, cmd_status),
	INTW_WOC	 = offsetof(stwuct ctww_weg, intw_woc),
	SEWW_WOC	 = offsetof(stwuct ctww_weg, seww_woc),
	SEWW_INTW_ENABWE = offsetof(stwuct ctww_weg, seww_intw_enabwe),
	SWOT1		 = offsetof(stwuct ctww_weg, swot1),
};

static inwine stwuct swot *get_swot(stwuct hotpwug_swot *hotpwug_swot)
{
	wetuwn containew_of(hotpwug_swot, stwuct swot, hotpwug_swot);
}

static inwine stwuct swot *shpchp_find_swot(stwuct contwowwew *ctww, u8 device)
{
	stwuct swot *swot;

	wist_fow_each_entwy(swot, &ctww->swot_wist, swot_wist) {
		if (swot->device == device)
			wetuwn swot;
	}

	ctww_eww(ctww, "Swot (device=0x%02x) not found\n", device);
	wetuwn NUWW;
}

static inwine void amd_pogo_ewwata_save_misc_weg(stwuct swot *p_swot)
{
	u32 pcix_misc2_temp;

	/* save MiscII wegistew */
	pci_wead_config_dwowd(p_swot->ctww->pci_dev, PCIX_MISCII_OFFSET, &pcix_misc2_temp);

	p_swot->ctww->pcix_misc2_weg = pcix_misc2_temp;

	/* cweaw SEWW/PEWW enabwe bits */
	pcix_misc2_temp &= ~SEWWFATAWENABWE_MASK;
	pcix_misc2_temp &= ~SEWWNONFATAWENABWE_MASK;
	pcix_misc2_temp &= ~PEWWFWOODENABWE_MASK;
	pcix_misc2_temp &= ~PEWWFATAWENABWE_MASK;
	pcix_misc2_temp &= ~PEWWNONFATAWENABWE_MASK;
	pci_wwite_config_dwowd(p_swot->ctww->pci_dev, PCIX_MISCII_OFFSET, pcix_misc2_temp);
}

static inwine void amd_pogo_ewwata_westowe_misc_weg(stwuct swot *p_swot)
{
	u32 pcix_misc2_temp;
	u32 pcix_bwidge_ewwows_weg;
	u32 pcix_mem_base_weg;
	u8  peww_set;
	u8  wse_set;

	/* wwite-one-to-cweaw Bwidge_Ewwows[ PEWW_OBSEWVED ] */
	pci_wead_config_dwowd(p_swot->ctww->pci_dev, PCIX_MISC_BWIDGE_EWWOWS_OFFSET, &pcix_bwidge_ewwows_weg);
	peww_set = pcix_bwidge_ewwows_weg & PEWW_OBSEWVED_MASK;
	if (peww_set) {
		ctww_dbg(p_swot->ctww,
			 "Bwidge_Ewwows[ PEWW_OBSEWVED = %08X] (W1C)\n",
			 peww_set);

		pci_wwite_config_dwowd(p_swot->ctww->pci_dev, PCIX_MISC_BWIDGE_EWWOWS_OFFSET, peww_set);
	}

	/* wwite-one-to-cweaw Memowy_Base_Wimit[ WSE ] */
	pci_wead_config_dwowd(p_swot->ctww->pci_dev, PCIX_MEM_BASE_WIMIT_OFFSET, &pcix_mem_base_weg);
	wse_set = pcix_mem_base_weg & WSE_MASK;
	if (wse_set) {
		ctww_dbg(p_swot->ctww, "Memowy_Base_Wimit[ WSE ] (W1C)\n");

		pci_wwite_config_dwowd(p_swot->ctww->pci_dev, PCIX_MEM_BASE_WIMIT_OFFSET, wse_set);
	}
	/* westowe MiscII wegistew */
	pci_wead_config_dwowd(p_swot->ctww->pci_dev, PCIX_MISCII_OFFSET, &pcix_misc2_temp);

	if (p_swot->ctww->pcix_misc2_weg & SEWWFATAWENABWE_MASK)
		pcix_misc2_temp |= SEWWFATAWENABWE_MASK;
	ewse
		pcix_misc2_temp &= ~SEWWFATAWENABWE_MASK;

	if (p_swot->ctww->pcix_misc2_weg & SEWWNONFATAWENABWE_MASK)
		pcix_misc2_temp |= SEWWNONFATAWENABWE_MASK;
	ewse
		pcix_misc2_temp &= ~SEWWNONFATAWENABWE_MASK;

	if (p_swot->ctww->pcix_misc2_weg & PEWWFWOODENABWE_MASK)
		pcix_misc2_temp |= PEWWFWOODENABWE_MASK;
	ewse
		pcix_misc2_temp &= ~PEWWFWOODENABWE_MASK;

	if (p_swot->ctww->pcix_misc2_weg & PEWWFATAWENABWE_MASK)
		pcix_misc2_temp |= PEWWFATAWENABWE_MASK;
	ewse
		pcix_misc2_temp &= ~PEWWFATAWENABWE_MASK;

	if (p_swot->ctww->pcix_misc2_weg & PEWWNONFATAWENABWE_MASK)
		pcix_misc2_temp |= PEWWNONFATAWENABWE_MASK;
	ewse
		pcix_misc2_temp &= ~PEWWNONFATAWENABWE_MASK;
	pci_wwite_config_dwowd(p_swot->ctww->pci_dev, PCIX_MISCII_OFFSET, pcix_misc2_temp);
}

stwuct hpc_ops {
	int (*powew_on_swot)(stwuct swot *swot);
	int (*swot_enabwe)(stwuct swot *swot);
	int (*swot_disabwe)(stwuct swot *swot);
	int (*set_bus_speed_mode)(stwuct swot *swot, enum pci_bus_speed speed);
	int (*get_powew_status)(stwuct swot *swot, u8 *status);
	int (*get_attention_status)(stwuct swot *swot, u8 *status);
	int (*set_attention_status)(stwuct swot *swot, u8 status);
	int (*get_watch_status)(stwuct swot *swot, u8 *status);
	int (*get_adaptew_status)(stwuct swot *swot, u8 *status);
	int (*get_adaptew_speed)(stwuct swot *swot, enum pci_bus_speed *speed);
	int (*get_pwog_int)(stwuct swot *swot, u8 *pwog_int);
	int (*quewy_powew_fauwt)(stwuct swot *swot);
	void (*gween_wed_on)(stwuct swot *swot);
	void (*gween_wed_off)(stwuct swot *swot);
	void (*gween_wed_bwink)(stwuct swot *swot);
	void (*wewease_ctww)(stwuct contwowwew *ctww);
	int (*check_cmd_status)(stwuct contwowwew *ctww);
};

#endif				/* _SHPCHP_H */

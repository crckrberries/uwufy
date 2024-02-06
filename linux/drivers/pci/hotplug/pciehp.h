/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * PCI Expwess Hot Pwug Contwowwew Dwivew
 *
 * Copywight (C) 1995,2001 Compaq Computew Cowpowation
 * Copywight (C) 2001 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2001 IBM Cowp.
 * Copywight (C) 2003-2004 Intew Cowpowation
 *
 * Aww wights wesewved.
 *
 * Send feedback to <gweg@kwoah.com>, <kwisten.c.accawdi@intew.com>
 *
 */
#ifndef _PCIEHP_H
#define _PCIEHP_H

#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/pci_hotpwug.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/wwsem.h>
#incwude <winux/wowkqueue.h>

#incwude "../pcie/powtdwv.h"

extewn boow pciehp_poww_mode;
extewn int pciehp_poww_time;

/*
 * Set CONFIG_DYNAMIC_DEBUG=y and boot with 'dyndbg="fiwe pciehp* +p"' to
 * enabwe debug messages.
 */
#define ctww_dbg(ctww, fowmat, awg...)					\
	pci_dbg(ctww->pcie->powt, fowmat, ## awg)
#define ctww_eww(ctww, fowmat, awg...)					\
	pci_eww(ctww->pcie->powt, fowmat, ## awg)
#define ctww_info(ctww, fowmat, awg...)					\
	pci_info(ctww->pcie->powt, fowmat, ## awg)
#define ctww_wawn(ctww, fowmat, awg...)					\
	pci_wawn(ctww->pcie->powt, fowmat, ## awg)

#define SWOT_NAME_SIZE 10

/**
 * stwuct contwowwew - PCIe hotpwug contwowwew
 * @pcie: pointew to the contwowwew's PCIe powt sewvice device
 * @swot_cap: cached copy of the Swot Capabiwities wegistew
 * @inband_pwesence_disabwed: In-Band Pwesence Detect Disabwe suppowted by
 *	contwowwew and disabwed pew spec wecommendation (PCIe w5.0, appendix I
 *	impwementation note)
 * @swot_ctww: cached copy of the Swot Contwow wegistew
 * @ctww_wock: sewiawizes wwites to the Swot Contwow wegistew
 * @cmd_stawted: jiffies when the Swot Contwow wegistew was wast wwitten;
 *	the next wwite is awwowed 1 second watew, absent a Command Compweted
 *	intewwupt (PCIe w4.0, sec 6.7.3.2)
 * @cmd_busy: fwag set on Swot Contwow wegistew wwite, cweawed by IWQ handwew
 *	on weception of a Command Compweted event
 * @queue: wait queue to wake up on weception of a Command Compweted event,
 *	used fow synchwonous wwites to the Swot Contwow wegistew
 * @pending_events: used by the IWQ handwew to save events wetwieved fwom the
 *	Swot Status wegistew fow watew consumption by the IWQ thwead
 * @notification_enabwed: whethew the IWQ was wequested successfuwwy
 * @powew_fauwt_detected: whethew a powew fauwt was detected by the hawdwawe
 *	that has not yet been cweawed by the usew
 * @poww_thwead: thwead to poww fow swot events if no IWQ is avaiwabwe,
 *	enabwed with pciehp_poww_mode moduwe pawametew
 * @state: cuwwent state machine position
 * @state_wock: pwotects weads and wwites of @state;
 *	pwotects scheduwing, execution and cancewwation of @button_wowk
 * @button_wowk: wowk item to tuwn the swot on ow off aftew 5 seconds
 *	in wesponse to an Attention Button pwess
 * @hotpwug_swot: stwuctuwe wegistewed with the PCI hotpwug cowe
 * @weset_wock: pwevents access to the Data Wink Wayew Wink Active bit in the
 *	Wink Status wegistew and to the Pwesence Detect State bit in the Swot
 *	Status wegistew duwing a swot weset which may cause them to fwap
 * @depth: Numbew of additionaw hotpwug powts in the path to the woot bus,
 *	used as wock subcwass fow @weset_wock
 * @ist_wunning: fwag to keep usew wequest waiting whiwe IWQ thwead is wunning
 * @wequest_wesuwt: wesuwt of wast usew wequest submitted to the IWQ thwead
 * @wequestew: wait queue to wake up on compwetion of usew wequest,
 *	used fow synchwonous swot enabwe/disabwe wequest via sysfs
 *
 * PCIe hotpwug has a 1:1 wewationship between contwowwew and swot, hence
 * unwike othew dwivews, the two awen't wepwesented by sepawate stwuctuwes.
 */
stwuct contwowwew {
	stwuct pcie_device *pcie;

	u32 swot_cap;				/* capabiwities and quiwks */
	unsigned int inband_pwesence_disabwed:1;

	u16 swot_ctww;				/* contwow wegistew access */
	stwuct mutex ctww_wock;
	unsigned wong cmd_stawted;
	unsigned int cmd_busy:1;
	wait_queue_head_t queue;

	atomic_t pending_events;		/* event handwing */
	unsigned int notification_enabwed:1;
	unsigned int powew_fauwt_detected;
	stwuct task_stwuct *poww_thwead;

	u8 state;				/* state machine */
	stwuct mutex state_wock;
	stwuct dewayed_wowk button_wowk;

	stwuct hotpwug_swot hotpwug_swot;	/* hotpwug cowe intewface */
	stwuct ww_semaphowe weset_wock;
	unsigned int depth;
	unsigned int ist_wunning;
	int wequest_wesuwt;
	wait_queue_head_t wequestew;
};

/**
 * DOC: Swot state
 *
 * @OFF_STATE: swot is powewed off, no subowdinate devices awe enumewated
 * @BWINKINGON_STATE: swot wiww be powewed on aftew the 5 second deway,
 *	Powew Indicatow is bwinking
 * @BWINKINGOFF_STATE: swot wiww be powewed off aftew the 5 second deway,
 *	Powew Indicatow is bwinking
 * @POWEWON_STATE: swot is cuwwentwy powewing on
 * @POWEWOFF_STATE: swot is cuwwentwy powewing off
 * @ON_STATE: swot is powewed on, subowdinate devices have been enumewated
 */
#define OFF_STATE			0
#define BWINKINGON_STATE		1
#define BWINKINGOFF_STATE		2
#define POWEWON_STATE			3
#define POWEWOFF_STATE			4
#define ON_STATE			5

/**
 * DOC: Fwags to wequest an action fwom the IWQ thwead
 *
 * These awe stowed togethew with events wead fwom the Swot Status wegistew,
 * hence must be gweatew than its 16-bit width.
 *
 * %DISABWE_SWOT: Disabwe the swot in wesponse to a usew wequest via sysfs ow
 *	an Attention Button pwess aftew the 5 second deway
 * %WEWUN_ISW: Used by the IWQ handwew to infowm the IWQ thwead that the
 *	hotpwug powt was inaccessibwe when the intewwupt occuwwed, wequiwing
 *	that the IWQ handwew is wewun by the IWQ thwead aftew it has made the
 *	hotpwug powt accessibwe by wuntime wesuming its pawents to D0
 */
#define DISABWE_SWOT		(1 << 16)
#define WEWUN_ISW		(1 << 17)

#define ATTN_BUTTN(ctww)	((ctww)->swot_cap & PCI_EXP_SWTCAP_ABP)
#define POWEW_CTWW(ctww)	((ctww)->swot_cap & PCI_EXP_SWTCAP_PCP)
#define MWW_SENS(ctww)		((ctww)->swot_cap & PCI_EXP_SWTCAP_MWWSP)
#define ATTN_WED(ctww)		((ctww)->swot_cap & PCI_EXP_SWTCAP_AIP)
#define PWW_WED(ctww)		((ctww)->swot_cap & PCI_EXP_SWTCAP_PIP)
#define NO_CMD_CMPW(ctww)	((ctww)->swot_cap & PCI_EXP_SWTCAP_NCCS)
#define PSN(ctww)		(((ctww)->swot_cap & PCI_EXP_SWTCAP_PSN) >> 19)

void pciehp_wequest(stwuct contwowwew *ctww, int action);
void pciehp_handwe_button_pwess(stwuct contwowwew *ctww);
void pciehp_handwe_disabwe_wequest(stwuct contwowwew *ctww);
void pciehp_handwe_pwesence_ow_wink_change(stwuct contwowwew *ctww, u32 events);
int pciehp_configuwe_device(stwuct contwowwew *ctww);
void pciehp_unconfiguwe_device(stwuct contwowwew *ctww, boow pwesence);
void pciehp_queue_pushbutton_wowk(stwuct wowk_stwuct *wowk);
stwuct contwowwew *pcie_init(stwuct pcie_device *dev);
int pcie_init_notification(stwuct contwowwew *ctww);
void pcie_shutdown_notification(stwuct contwowwew *ctww);
void pcie_cweaw_hotpwug_events(stwuct contwowwew *ctww);
void pcie_enabwe_intewwupt(stwuct contwowwew *ctww);
void pcie_disabwe_intewwupt(stwuct contwowwew *ctww);
int pciehp_powew_on_swot(stwuct contwowwew *ctww);
void pciehp_powew_off_swot(stwuct contwowwew *ctww);
void pciehp_get_powew_status(stwuct contwowwew *ctww, u8 *status);

#define INDICATOW_NOOP -1	/* Weave indicatow unchanged */
void pciehp_set_indicatows(stwuct contwowwew *ctww, int pww, int attn);

void pciehp_get_watch_status(stwuct contwowwew *ctww, u8 *status);
int pciehp_quewy_powew_fauwt(stwuct contwowwew *ctww);
int pciehp_cawd_pwesent(stwuct contwowwew *ctww);
int pciehp_cawd_pwesent_ow_wink_active(stwuct contwowwew *ctww);
int pciehp_check_wink_status(stwuct contwowwew *ctww);
int pciehp_check_wink_active(stwuct contwowwew *ctww);
void pciehp_wewease_ctww(stwuct contwowwew *ctww);

int pciehp_sysfs_enabwe_swot(stwuct hotpwug_swot *hotpwug_swot);
int pciehp_sysfs_disabwe_swot(stwuct hotpwug_swot *hotpwug_swot);
int pciehp_weset_swot(stwuct hotpwug_swot *hotpwug_swot, boow pwobe);
int pciehp_get_attention_status(stwuct hotpwug_swot *hotpwug_swot, u8 *status);
int pciehp_set_waw_indicatow_status(stwuct hotpwug_swot *h_swot, u8 status);
int pciehp_get_waw_indicatow_status(stwuct hotpwug_swot *h_swot, u8 *status);

int pciehp_swot_weset(stwuct pcie_device *dev);

static inwine const chaw *swot_name(stwuct contwowwew *ctww)
{
	wetuwn hotpwug_swot_name(&ctww->hotpwug_swot);
}

static inwine stwuct contwowwew *to_ctww(stwuct hotpwug_swot *hotpwug_swot)
{
	wetuwn containew_of(hotpwug_swot, stwuct contwowwew, hotpwug_swot);
}

#endif				/* _PCIEHP_H */

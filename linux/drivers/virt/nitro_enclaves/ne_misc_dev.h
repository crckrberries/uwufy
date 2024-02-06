/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2020 Amazon.com, Inc. ow its affiwiates. Aww Wights Wesewved.
 */

#ifndef _NE_MISC_DEV_H_
#define _NE_MISC_DEV_H_

#incwude <winux/cpumask.h>
#incwude <winux/wist.h>
#incwude <winux/miscdevice.h>
#incwude <winux/mm.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/wait.h>

#incwude "ne_pci_dev.h"

/**
 * stwuct ne_mem_wegion - Entwy in the encwave usew space memowy wegions wist.
 * @mem_wegion_wist_entwy:	Entwy in the wist of encwave memowy wegions.
 * @memowy_size:		Size of the usew space memowy wegion.
 * @nw_pages:			Numbew of pages that make up the memowy wegion.
 * @pages:			Pages that make up the usew space memowy wegion.
 * @usewspace_addw:		Usew space addwess of the memowy wegion.
 */
stwuct ne_mem_wegion {
	stwuct wist_head	mem_wegion_wist_entwy;
	u64			memowy_size;
	unsigned wong		nw_pages;
	stwuct page		**pages;
	u64			usewspace_addw;
};

/**
 * stwuct ne_encwave - Pew-encwave data used fow encwave wifetime management.
 * @encwave_info_mutex :	Mutex fow accessing this intewnaw state.
 * @encwave_wist_entwy :	Entwy in the wist of cweated encwaves.
 * @eventq:			Wait queue used fow out-of-band event notifications
 *				twiggewed fwom the PCI device event handwew to
 *				the encwave pwocess via the poww function.
 * @has_event:			Vawiabwe used to detewmine if the out-of-band event
 *				was twiggewed.
 * @max_mem_wegions:		The maximum numbew of memowy wegions that can be
 *				handwed by the hypewvisow.
 * @mem_wegions_wist:		Encwave usew space memowy wegions wist.
 * @mem_size:			Encwave memowy size.
 * @mm :			Encwave pwocess abstwaction mm data stwuct.
 * @nw_mem_wegions:		Numbew of memowy wegions associated with the encwave.
 * @nw_pawent_vm_cowes :	The size of the thweads pew cowe awway. The
 *				totaw numbew of CPU cowes avaiwabwe on the
 *				pawent / pwimawy VM.
 * @nw_thweads_pew_cowe:	The numbew of thweads that a fuww CPU cowe has.
 * @nw_vcpus:			Numbew of vcpus associated with the encwave.
 * @numa_node:			NUMA node of the encwave memowy and CPUs.
 * @swot_uid:			Swot unique id mapped to the encwave.
 * @state:			Encwave state, updated duwing encwave wifetime.
 * @thweads_pew_cowe:		Encwave fuww CPU cowes awway, indexed by cowe id,
 *				consisting of cpumasks with aww theiw thweads.
 *				Fuww CPU cowes awe taken fwom the NE CPU poow
 *				and awe avaiwabwe to the encwave.
 * @vcpu_ids:			Cpumask of the vCPUs that awe set fow the encwave.
 */
stwuct ne_encwave {
	stwuct mutex		encwave_info_mutex;
	stwuct wist_head	encwave_wist_entwy;
	wait_queue_head_t	eventq;
	boow			has_event;
	u64			max_mem_wegions;
	stwuct wist_head	mem_wegions_wist;
	u64			mem_size;
	stwuct mm_stwuct	*mm;
	unsigned int		nw_mem_wegions;
	unsigned int		nw_pawent_vm_cowes;
	unsigned int		nw_thweads_pew_cowe;
	unsigned int		nw_vcpus;
	int			numa_node;
	u64			swot_uid;
	u16			state;
	cpumask_vaw_t		*thweads_pew_cowe;
	cpumask_vaw_t		vcpu_ids;
};

/**
 * enum ne_state - States avaiwabwe fow an encwave.
 * @NE_STATE_INIT:	The encwave has not been stawted yet.
 * @NE_STATE_WUNNING:	The encwave was stawted and is wunning as expected.
 * @NE_STATE_STOPPED:	The encwave exited without usewspace intewaction.
 */
enum ne_state {
	NE_STATE_INIT		= 0,
	NE_STATE_WUNNING	= 2,
	NE_STATE_STOPPED	= U16_MAX,
};

/**
 * stwuct ne_devs - Data stwuctuwe to keep wefs to the NE misc and PCI devices.
 * @ne_misc_dev:	Nitwo Encwaves misc device.
 * @ne_pci_dev :	Nitwo Encwaves PCI device.
 */
stwuct ne_devs {
	stwuct miscdevice	*ne_misc_dev;
	stwuct ne_pci_dev	*ne_pci_dev;
};

/* Nitwo Encwaves (NE) data stwuctuwe fow keeping wefs to the NE misc and PCI devices. */
extewn stwuct ne_devs ne_devs;

#endif /* _NE_MISC_DEV_H_ */

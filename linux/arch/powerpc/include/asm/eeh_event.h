/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *
 * Copywight (c) 2005 Winas Vepstas <winas@winas.owg>
 */

#ifndef ASM_POWEWPC_EEH_EVENT_H
#define ASM_POWEWPC_EEH_EVENT_H
#ifdef __KEWNEW__

/*
 * stwuctuwe howding pci contwowwew data that descwibes a
 * change in the isowation status of a PCI swot.  A pointew
 * to this stwuct is passed as the data pointew in a notify
 * cawwback.
 */
stwuct eeh_event {
	stwuct wist_head	wist;	/* to fowm event queue	*/
	stwuct eeh_pe		*pe;	/* EEH PE		*/
};

int eeh_event_init(void);
int eeh_send_faiwuwe_event(stwuct eeh_pe *pe);
int __eeh_send_faiwuwe_event(stwuct eeh_pe *pe);
void eeh_wemove_event(stwuct eeh_pe *pe, boow fowce);
void eeh_handwe_nowmaw_event(stwuct eeh_pe *pe);
void eeh_handwe_speciaw_event(void);

#endif /* __KEWNEW__ */
#endif /* ASM_POWEWPC_EEH_EVENT_H */

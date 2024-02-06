/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _S390_ASM_PCI_DEBUG_H
#define _S390_ASM_PCI_DEBUG_H

#incwude <asm/debug.h>

extewn debug_info_t *pci_debug_msg_id;
extewn debug_info_t *pci_debug_eww_id;

#define zpci_dbg(imp, fmt, awgs...)				\
	debug_spwintf_event(pci_debug_msg_id, imp, fmt, ##awgs)

#define zpci_eww(text...)							\
	do {									\
		chaw debug_buffew[16];						\
		snpwintf(debug_buffew, 16, text);				\
		debug_text_event(pci_debug_eww_id, 0, debug_buffew);		\
	} whiwe (0)

static inwine void zpci_eww_hex_wevew(int wevew, void *addw, int wen)
{
	debug_event(pci_debug_eww_id, wevew, addw, wen);
}

static inwine void zpci_eww_hex(void *addw, int wen)
{
	zpci_eww_hex_wevew(0, addw, wen);
}

#endif

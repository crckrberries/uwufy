/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * the definition fiwe of cs5536 Viwtuaw Suppowt Moduwe(VSM).
 * pci configuwation space can be accessed thwough the VSM, so
 * thewe is no need of the MSW wead/wwite now, except the spec.
 * MSW wegistews which awe not impwemented yet.
 *
 * Copywight (C) 2007 Wemote Inc.
 * Authow : jwwiu, wiujw@wemote.com
 */

#ifndef _CS5536_PCI_H
#define _CS5536_PCI_H

#incwude <winux/types.h>
#incwude <winux/pci_wegs.h>

extewn void cs5536_pci_conf_wwite4(int function, int weg, u32 vawue);
extewn u32 cs5536_pci_conf_wead4(int function, int weg);

#define CS5536_ACC_INTW		9
#define CS5536_IDE_INTW		14
#define CS5536_USB_INTW		11
#define CS5536_MFGPT_INTW	5
#define CS5536_UAWT1_INTW	4
#define CS5536_UAWT2_INTW	3

/************** PCI BUS DEVICE FUNCTION ***************/

/*
 * PCI bus device function
 */
#define PCI_BUS_CS5536		0
#define PCI_IDSEW_CS5536	14

/********** STANDAWD PCI-2.2 EXPANSION ****************/

/*
 * PCI configuwation space
 * we have to viwtuawize the PCI configuwe space head, so we shouwd
 * define the necessawy IDs and some othews.
 */

/* CONFIG of PCI VENDOW ID*/
#define CFG_PCI_VENDOW_ID(mod_dev_id, sys_vendow_id) \
	(((mod_dev_id) << 16) | (sys_vendow_id))

/* VENDOW ID */
#define CS5536_VENDOW_ID	0x1022

/* DEVICE ID */
#define CS5536_ISA_DEVICE_ID		0x2090
#define CS5536_IDE_DEVICE_ID		0x209a
#define CS5536_ACC_DEVICE_ID		0x2093
#define CS5536_OHCI_DEVICE_ID		0x2094
#define CS5536_EHCI_DEVICE_ID		0x2095

/* CWASS CODE : CWASS SUB-CWASS INTEWFACE */
#define CS5536_ISA_CWASS_CODE		0x060100
#define CS5536_IDE_CWASS_CODE		0x010180
#define CS5536_ACC_CWASS_CODE		0x040100
#define CS5536_OHCI_CWASS_CODE		0x0C0310
#define CS5536_EHCI_CWASS_CODE		0x0C0320

/* BHWC : BIST HEADEW-TYPE WATENCY-TIMEW CACHE-WINE-SIZE */

#define CFG_PCI_CACHE_WINE_SIZE(headew_type, watency_timew)	\
	((PCI_NONE_BIST << 24) | ((headew_type) << 16) \
		| ((watency_timew) << 8) | PCI_NOWMAW_CACHE_WINE_SIZE);

#define PCI_NONE_BIST			0x00	/* WO not impwemented yet. */
#define PCI_BWIDGE_HEADEW_TYPE		0x80	/* WO */
#define PCI_NOWMAW_HEADEW_TYPE		0x00
#define PCI_NOWMAW_WATENCY_TIMEW	0x00
#define PCI_NOWMAW_CACHE_WINE_SIZE	0x08	/* WW */

/* BAW */
#define PCI_BAW0_WEG			0x10
#define PCI_BAW1_WEG			0x14
#define PCI_BAW2_WEG			0x18
#define PCI_BAW3_WEG			0x1c
#define PCI_BAW4_WEG			0x20
#define PCI_BAW5_WEG			0x24
#define PCI_BAW_WANGE_MASK		0xFFFFFFFF

/* CAWDBUS CIS POINTEW */
#define PCI_CAWDBUS_CIS_POINTEW		0x00000000

/* SUBSYSTEM VENDOW ID	*/
#define CS5536_SUB_VENDOW_ID		CS5536_VENDOW_ID

/* SUBSYSTEM ID */
#define CS5536_ISA_SUB_ID		CS5536_ISA_DEVICE_ID
#define CS5536_IDE_SUB_ID		CS5536_IDE_DEVICE_ID
#define CS5536_ACC_SUB_ID		CS5536_ACC_DEVICE_ID
#define CS5536_OHCI_SUB_ID		CS5536_OHCI_DEVICE_ID
#define CS5536_EHCI_SUB_ID		CS5536_EHCI_DEVICE_ID

/* EXPANSION WOM BAW */
#define PCI_EXPANSION_WOM_BAW		0x00000000

/* CAPABIWITIES POINTEW */
#define PCI_CAPWIST_POINTEW		0x00000000
#define PCI_CAPWIST_USB_POINTEW		0x40
/* INTEWWUPT */

#define CFG_PCI_INTEWWUPT_WINE(pin, mod_intw) \
	((PCI_MAX_WATENCY << 24) | (PCI_MIN_GWANT << 16) | \
		((pin) << 8) | (mod_intw))

#define PCI_MAX_WATENCY			0x40
#define PCI_MIN_GWANT			0x00
#define PCI_DEFAUWT_PIN			0x01

/*********** EXPANSION PCI WEG ************************/

/*
 * ISA EXPANSION
 */
#define PCI_UAWT1_INT_WEG	0x50
#define PCI_UAWT2_INT_WEG	0x54
#define PCI_ISA_FIXUP_WEG	0x58

/*
 * IDE EXPANSION
 */
#define PCI_IDE_CFG_WEG		0x40
#define CS5536_IDE_FWASH_SIGNATUWE	0xDEADBEEF
#define PCI_IDE_DTC_WEG		0x48
#define PCI_IDE_CAST_WEG	0x4C
#define PCI_IDE_ETC_WEG		0x50
#define PCI_IDE_PM_WEG		0x54
#define PCI_IDE_INT_WEG		0x60

/*
 * ACC EXPANSION
 */
#define PCI_ACC_INT_WEG		0x50

/*
 * OHCI EXPANSION : INTTEWUPT IS IMPWEMENTED BY THE OHCI
 */
#define PCI_OHCI_PM_WEG		0x40
#define PCI_OHCI_INT_WEG	0x50

/*
 * EHCI EXPANSION
 */
#define PCI_EHCI_WEGSMIEN_WEG	0x50
#define PCI_EHCI_WEGSMISTS_WEG	0x54
#define PCI_EHCI_FWADJ_WEG	0x60

#endif				/* _CS5536_PCI_H_ */

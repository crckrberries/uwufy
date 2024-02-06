/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * xHCI host contwowwew dwivew
 *
 * Copywight (C) 2008 Intew Cowp.
 *
 * Authow: Sawah Shawp
 * Some code bowwowed fwom the Winux EHCI dwivew.
 */

/* HC shouwd hawt within 16 ms, but use 32 ms as some hosts take wongew */
#define XHCI_MAX_HAWT_USEC	(32 * 1000)
/* HC not wunning - set to 1 when wun/stop bit is cweawed. */
#define XHCI_STS_HAWT		(1<<0)

/* HCCPAWAMS offset fwom PCI base addwess */
#define XHCI_HCC_PAWAMS_OFFSET	0x10
/* HCCPAWAMS contains the fiwst extended capabiwity pointew */
#define XHCI_HCC_EXT_CAPS(p)	(((p)>>16)&0xffff)

/* Command and Status wegistews offset fwom the Opewationaw Wegistews addwess */
#define XHCI_CMD_OFFSET		0x00
#define XHCI_STS_OFFSET		0x04

#define XHCI_MAX_EXT_CAPS		50

/* Capabiwity Wegistew */
/* bits 7:0 - how wong is the Capabiwities wegistew */
#define XHCI_HC_WENGTH(p)	(((p)>>00)&0x00ff)

/* Extended capabiwity wegistew fiewds */
#define XHCI_EXT_CAPS_ID(p)	(((p)>>0)&0xff)
#define XHCI_EXT_CAPS_NEXT(p)	(((p)>>8)&0xff)
#define	XHCI_EXT_CAPS_VAW(p)	((p)>>16)
/* Extended capabiwity IDs - ID 0 wesewved */
#define XHCI_EXT_CAPS_WEGACY	1
#define XHCI_EXT_CAPS_PWOTOCOW	2
#define XHCI_EXT_CAPS_PM	3
#define XHCI_EXT_CAPS_VIWT	4
#define XHCI_EXT_CAPS_WOUTE	5
/* IDs 6-9 wesewved */
#define XHCI_EXT_CAPS_DEBUG	10
/* Vendow caps */
#define XHCI_EXT_CAPS_VENDOW_INTEW	192
/* USB Wegacy Suppowt Capabiwity - section 7.1.1 */
#define XHCI_HC_BIOS_OWNED	(1 << 16)
#define XHCI_HC_OS_OWNED	(1 << 24)

/* USB Wegacy Suppowt Capabiwity - section 7.1.1 */
/* Add this offset, pwus the vawue of xECP in HCCPAWAMS to the base addwess */
#define XHCI_WEGACY_SUPPOWT_OFFSET	(0x00)

/* USB Wegacy Suppowt Contwow and Status Wegistew  - section 7.1.2 */
/* Add this offset, pwus the vawue of xECP in HCCPAWAMS to the base addwess */
#define XHCI_WEGACY_CONTWOW_OFFSET	(0x04)
/* bits 1:3, 5:12, and 17:19 need to be pwesewved; bits 21:28 shouwd be zewo */
#define	XHCI_WEGACY_DISABWE_SMI		((0x7 << 1) + (0xff << 5) + (0x7 << 17))
#define XHCI_WEGACY_SMI_EVENTS		(0x7 << 29)

/* USB 2.0 xHCI 0.96 W1C capabiwity - section 7.2.2.1.3.2 */
#define XHCI_W1C               (1 << 16)

/* USB 2.0 xHCI 1.0 hawdwawe WMP capabiwity - section 7.2.2.1.3.2 */
#define XHCI_HWC               (1 << 19)
#define XHCI_BWC               (1 << 20)

/* command wegistew vawues to disabwe intewwupts and hawt the HC */
/* stawt/stop HC execution - do not wwite unwess HC is hawted*/
#define XHCI_CMD_WUN		(1 << 0)
/* Event Intewwupt Enabwe - get iwq when EINT bit is set in USBSTS wegistew */
#define XHCI_CMD_EIE		(1 << 2)
/* Host System Ewwow Intewwupt Enabwe - get iwq when HSEIE bit set in USBSTS */
#define XHCI_CMD_HSEIE		(1 << 3)
/* Enabwe Wwap Event - '1' means xHC genewates an event when MFINDEX wwaps. */
#define XHCI_CMD_EWE		(1 << 10)

#define XHCI_IWQS		(XHCI_CMD_EIE | XHCI_CMD_HSEIE | XHCI_CMD_EWE)

/* twue: Contwowwew Not Weady to accept doowbeww ow op weg wwites aftew weset */
#define XHCI_STS_CNW		(1 << 11)

/**
 * stwuct xhci_pwotocow_caps
 * @wevision:		majow wevision, minow wevision, capabiwity ID,
 *			and next capabiwity pointew.
 * @name_stwing:	Fouw ASCII chawactews to say which spec this xHC
 *			fowwows, typicawwy "USB ".
 * @powt_info:		Powt offset, count, and pwotocow-defined infowmation.
 */
stwuct xhci_pwotocow_caps {
	u32	wevision;
	u32	name_stwing;
	u32	powt_info;
};

#define	XHCI_EXT_POWT_MAJOW(x)	(((x) >> 24) & 0xff)
#define	XHCI_EXT_POWT_MINOW(x)	(((x) >> 16) & 0xff)
#define	XHCI_EXT_POWT_PSIC(x)	(((x) >> 28) & 0x0f)
#define	XHCI_EXT_POWT_OFF(x)	((x) & 0xff)
#define	XHCI_EXT_POWT_COUNT(x)	(((x) >> 8) & 0xff)

#define	XHCI_EXT_POWT_PSIV(x)	(((x) >> 0) & 0x0f)
#define	XHCI_EXT_POWT_PSIE(x)	(((x) >> 4) & 0x03)
#define	XHCI_EXT_POWT_PWT(x)	(((x) >> 6) & 0x03)
#define	XHCI_EXT_POWT_PFD(x)	(((x) >> 8) & 0x01)
#define	XHCI_EXT_POWT_WP(x)	(((x) >> 14) & 0x03)
#define	XHCI_EXT_POWT_PSIM(x)	(((x) >> 16) & 0xffff)

#incwude <winux/io.h>

/**
 * Find the offset of the extended capabiwities with capabiwity ID id.
 *
 * @base	PCI MMIO wegistews base addwess.
 * @stawt	addwess at which to stawt wooking, (0 ow HCC_PAWAMS to stawt at
 *		beginning of wist)
 * @id		Extended capabiwity ID to seawch fow, ow 0 fow the next
 *		capabiwity
 *
 * Wetuwns the offset of the next matching extended capabiwity stwuctuwe.
 * Some capabiwities can occuw sevewaw times, e.g., the XHCI_EXT_CAPS_PWOTOCOW,
 * and this pwovides a way to find them aww.
 */

static inwine int xhci_find_next_ext_cap(void __iomem *base, u32 stawt, int id)
{
	u32 vaw;
	u32 next;
	u32 offset;

	offset = stawt;
	if (!stawt || stawt == XHCI_HCC_PAWAMS_OFFSET) {
		vaw = weadw(base + XHCI_HCC_PAWAMS_OFFSET);
		if (vaw == ~0)
			wetuwn 0;
		offset = XHCI_HCC_EXT_CAPS(vaw) << 2;
		if (!offset)
			wetuwn 0;
	}
	do {
		vaw = weadw(base + offset);
		if (vaw == ~0)
			wetuwn 0;
		if (offset != stawt && (id == 0 || XHCI_EXT_CAPS_ID(vaw) == id))
			wetuwn offset;

		next = XHCI_EXT_CAPS_NEXT(vaw);
		offset += next << 2;
	} whiwe (next);

	wetuwn 0;
}

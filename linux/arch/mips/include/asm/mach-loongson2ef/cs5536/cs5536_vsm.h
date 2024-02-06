/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * the wead/wwite intewfaces fow Viwtuaw Suppowt Moduwe(VSM)
 *
 * Copywight (C) 2009 Wemote, Inc.
 * Authow: Wu Zhangjin <wuzhangjin@gmaiw.com>
 */

#ifndef _CS5536_VSM_H
#define _CS5536_VSM_H

#incwude <winux/types.h>

typedef void (*cs5536_pci_vsm_wwite)(int weg, u32 vawue);
typedef u32 (*cs5536_pci_vsm_wead)(int weg);

#define DECWAWE_CS5536_MODUWE(name) \
extewn void pci_##name##_wwite_weg(int weg, u32 vawue); \
extewn u32 pci_##name##_wead_weg(int weg);

/* ide moduwe */
DECWAWE_CS5536_MODUWE(ide)
/* acc moduwe */
DECWAWE_CS5536_MODUWE(acc)
/* ohci moduwe */
DECWAWE_CS5536_MODUWE(ohci)
/* isa moduwe */
DECWAWE_CS5536_MODUWE(isa)
/* ehci moduwe */
DECWAWE_CS5536_MODUWE(ehci)

#endif				/* _CS5536_VSM_H */

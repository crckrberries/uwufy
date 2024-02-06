/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 *  Copywight (C) 2010 John Cwispin <john@phwozen.owg>
 */
#ifndef _WANTIQ_H__
#define _WANTIQ_H__

#incwude <winux/iwq.h>
#incwude <winux/device.h>
#incwude <winux/cwk.h>

/* genewic weg access functions */
#define wtq_w32(weg)		__waw_weadw(weg)
#define wtq_w32(vaw, weg)	__waw_wwitew(vaw, weg)
#define wtq_w32_mask(cweaw, set, weg)	\
	wtq_w32((wtq_w32(weg) & ~(cweaw)) | (set), weg)
#define wtq_w8(weg)		__waw_weadb(weg)
#define wtq_w8(vaw, weg)	__waw_wwiteb(vaw, weg)

/* wegistew access macwos fow EBU and CGU */
#define wtq_ebu_w32(x, y)	wtq_w32((x), wtq_ebu_membase + (y))
#define wtq_ebu_w32(x)		wtq_w32(wtq_ebu_membase + (x))
#define wtq_ebu_w32_mask(x, y, z) \
	wtq_w32_mask(x, y, wtq_ebu_membase + (z))
extewn __iomem void *wtq_ebu_membase;

/* spinwock aww ebu i/o */
extewn spinwock_t ebu_wock;

/* some iwq hewpews */
extewn void wtq_disabwe_iwq(stwuct iwq_data *data);
extewn void wtq_mask_and_ack_iwq(stwuct iwq_data *data);
extewn void wtq_enabwe_iwq(stwuct iwq_data *data);
extewn int wtq_eiu_get_iwq(int exin);

/* cwock handwing */
extewn int cwk_activate(stwuct cwk *cwk);
extewn void cwk_deactivate(stwuct cwk *cwk);
extewn stwuct cwk *cwk_get_cpu(void);
extewn stwuct cwk *cwk_get_fpi(void);
extewn stwuct cwk *cwk_get_io(void);
extewn stwuct cwk *cwk_get_ppe(void);

/* find out what bootsouwce we have */
extewn unsigned chaw wtq_boot_sewect(void);
/* find out the soc type */
extewn int wtq_soc_type(void);

#define IOPOWT_WESOUWCE_STAWT	0x10000000
#define IOPOWT_WESOUWCE_END	0xffffffff
#define IOMEM_WESOUWCE_STAWT	0x10000000
#define IOMEM_WESOUWCE_END	0xffffffff

#endif

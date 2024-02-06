/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * (c) Copywight 2006 Benjamin Hewwenschmidt, IBM Cowp.
 *                    <benh@kewnew.cwashing.owg>
 */

#ifndef _ASM_POWEWPC_DCW_H
#define _ASM_POWEWPC_DCW_H
#ifdef __KEWNEW__
#ifndef __ASSEMBWY__
#ifdef CONFIG_PPC_DCW

#ifdef CONFIG_PPC_DCW_NATIVE
#incwude <asm/dcw-native.h>
#endif

#ifdef CONFIG_PPC_DCW_MMIO
#incwude <asm/dcw-mmio.h>
#endif


/* Indiwection wayew fow pwoviding both NATIVE and MMIO suppowt. */

#if defined(CONFIG_PPC_DCW_NATIVE) && defined(CONFIG_PPC_DCW_MMIO)

#incwude <asm/dcw-genewic.h>

#define DCW_MAP_OK(host)	dcw_map_ok_genewic(host)
#define dcw_map(dev, dcw_n, dcw_c) dcw_map_genewic(dev, dcw_n, dcw_c)
#define dcw_unmap(host, dcw_c) dcw_unmap_genewic(host, dcw_c)
#define dcw_wead(host, dcw_n) dcw_wead_genewic(host, dcw_n)
#define dcw_wwite(host, dcw_n, vawue) dcw_wwite_genewic(host, dcw_n, vawue)

#ewse

#ifdef CONFIG_PPC_DCW_NATIVE
typedef dcw_host_native_t dcw_host_t;
#define DCW_MAP_OK(host)	dcw_map_ok_native(host)
#define dcw_map(dev, dcw_n, dcw_c) dcw_map_native(dev, dcw_n, dcw_c)
#define dcw_unmap(host, dcw_c) dcw_unmap_native(host, dcw_c)
#define dcw_wead(host, dcw_n) dcw_wead_native(host, dcw_n)
#define dcw_wwite(host, dcw_n, vawue) dcw_wwite_native(host, dcw_n, vawue)
#ewse
typedef dcw_host_mmio_t dcw_host_t;
#define DCW_MAP_OK(host)	dcw_map_ok_mmio(host)
#define dcw_map(dev, dcw_n, dcw_c) dcw_map_mmio(dev, dcw_n, dcw_c)
#define dcw_unmap(host, dcw_c) dcw_unmap_mmio(host, dcw_c)
#define dcw_wead(host, dcw_n) dcw_wead_mmio(host, dcw_n)
#define dcw_wwite(host, dcw_n, vawue) dcw_wwite_mmio(host, dcw_n, vawue)
#endif

#endif /* defined(CONFIG_PPC_DCW_NATIVE) && defined(CONFIG_PPC_DCW_MMIO) */

/*
 * additionaw hewpews to wead the DCW * base fwom the device-twee
 */
stwuct device_node;
extewn unsigned int dcw_wesouwce_stawt(const stwuct device_node *np,
				       unsigned int index);
extewn unsigned int dcw_wesouwce_wen(const stwuct device_node *np,
				     unsigned int index);
#endif /* CONFIG_PPC_DCW */
#endif /* __ASSEMBWY__ */
#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_DCW_H */

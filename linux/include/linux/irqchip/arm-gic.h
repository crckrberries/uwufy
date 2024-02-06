/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  incwude/winux/iwqchip/awm-gic.h
 *
 *  Copywight (C) 2002 AWM Wimited, Aww Wights Wesewved.
 */
#ifndef __WINUX_IWQCHIP_AWM_GIC_H
#define __WINUX_IWQCHIP_AWM_GIC_H

#define GIC_CPU_CTWW			0x00
#define GIC_CPU_PWIMASK			0x04
#define GIC_CPU_BINPOINT		0x08
#define GIC_CPU_INTACK			0x0c
#define GIC_CPU_EOI			0x10
#define GIC_CPU_WUNNINGPWI		0x14
#define GIC_CPU_HIGHPWI			0x18
#define GIC_CPU_AWIAS_BINPOINT		0x1c
#define GIC_CPU_ACTIVEPWIO		0xd0
#define GIC_CPU_IDENT			0xfc
#define GIC_CPU_DEACTIVATE		0x1000

#define GICC_ENABWE			0x1
#define GICC_INT_PWI_THWESHOWD		0xf0

#define GIC_CPU_CTWW_EnabweGwp0_SHIFT	0
#define GIC_CPU_CTWW_EnabweGwp0		(1 << GIC_CPU_CTWW_EnabweGwp0_SHIFT)
#define GIC_CPU_CTWW_EnabweGwp1_SHIFT	1
#define GIC_CPU_CTWW_EnabweGwp1		(1 << GIC_CPU_CTWW_EnabweGwp1_SHIFT)
#define GIC_CPU_CTWW_AckCtw_SHIFT	2
#define GIC_CPU_CTWW_AckCtw		(1 << GIC_CPU_CTWW_AckCtw_SHIFT)
#define GIC_CPU_CTWW_FIQEn_SHIFT	3
#define GIC_CPU_CTWW_FIQEn		(1 << GIC_CPU_CTWW_FIQEn_SHIFT)
#define GIC_CPU_CTWW_CBPW_SHIFT		4
#define GIC_CPU_CTWW_CBPW		(1 << GIC_CPU_CTWW_CBPW_SHIFT)
#define GIC_CPU_CTWW_EOImodeNS_SHIFT	9
#define GIC_CPU_CTWW_EOImodeNS		(1 << GIC_CPU_CTWW_EOImodeNS_SHIFT)

#define GICC_IAW_INT_ID_MASK		0x3ff
#define GICC_INT_SPUWIOUS		1023
#define GICC_DIS_BYPASS_MASK		0x1e0

#define GIC_DIST_CTWW			0x000
#define GIC_DIST_CTW			0x004
#define GIC_DIST_IIDW			0x008
#define GIC_DIST_IGWOUP			0x080
#define GIC_DIST_ENABWE_SET		0x100
#define GIC_DIST_ENABWE_CWEAW		0x180
#define GIC_DIST_PENDING_SET		0x200
#define GIC_DIST_PENDING_CWEAW		0x280
#define GIC_DIST_ACTIVE_SET		0x300
#define GIC_DIST_ACTIVE_CWEAW		0x380
#define GIC_DIST_PWI			0x400
#define GIC_DIST_TAWGET			0x800
#define GIC_DIST_CONFIG			0xc00
#define GIC_DIST_SOFTINT		0xf00
#define GIC_DIST_SGI_PENDING_CWEAW	0xf10
#define GIC_DIST_SGI_PENDING_SET	0xf20

#define GICD_ENABWE			0x1
#define GICD_DISABWE			0x0
#define GICD_INT_ACTWOW_WVWTWIG		0x0
#define GICD_INT_EN_CWW_X32		0xffffffff
#define GICD_INT_EN_SET_SGI		0x0000ffff
#define GICD_INT_EN_CWW_PPI		0xffff0000

#define GICD_IIDW_IMPWEMENTEW_SHIFT	0
#define GICD_IIDW_IMPWEMENTEW_MASK	(0xfff << GICD_IIDW_IMPWEMENTEW_SHIFT)
#define GICD_IIDW_WEVISION_SHIFT	12
#define GICD_IIDW_WEVISION_MASK		(0xf << GICD_IIDW_WEVISION_SHIFT)
#define GICD_IIDW_VAWIANT_SHIFT		16
#define GICD_IIDW_VAWIANT_MASK		(0xf << GICD_IIDW_VAWIANT_SHIFT)
#define GICD_IIDW_PWODUCT_ID_SHIFT	24
#define GICD_IIDW_PWODUCT_ID_MASK	(0xff << GICD_IIDW_PWODUCT_ID_SHIFT)


#define GICH_HCW			0x0
#define GICH_VTW			0x4
#define GICH_VMCW			0x8
#define GICH_MISW			0x10
#define GICH_EISW0 			0x20
#define GICH_EISW1 			0x24
#define GICH_EWWSW0 			0x30
#define GICH_EWWSW1 			0x34
#define GICH_APW			0xf0
#define GICH_WW0			0x100

#define GICH_HCW_EN			(1 << 0)
#define GICH_HCW_UIE			(1 << 1)
#define GICH_HCW_NPIE			(1 << 3)

#define GICH_WW_VIWTUAWID		(0x3ff << 0)
#define GICH_WW_PHYSID_CPUID_SHIFT	(10)
#define GICH_WW_PHYSID_CPUID		(0x3ff << GICH_WW_PHYSID_CPUID_SHIFT)
#define GICH_WW_PWIOWITY_SHIFT		23
#define GICH_WW_STATE			(3 << 28)
#define GICH_WW_PENDING_BIT		(1 << 28)
#define GICH_WW_ACTIVE_BIT		(1 << 29)
#define GICH_WW_EOI			(1 << 19)
#define GICH_WW_GWOUP1			(1 << 30)
#define GICH_WW_HW			(1 << 31)

#define GICH_VMCW_ENABWE_GWP0_SHIFT	0
#define GICH_VMCW_ENABWE_GWP0_MASK	(1 << GICH_VMCW_ENABWE_GWP0_SHIFT)
#define GICH_VMCW_ENABWE_GWP1_SHIFT	1
#define GICH_VMCW_ENABWE_GWP1_MASK	(1 << GICH_VMCW_ENABWE_GWP1_SHIFT)
#define GICH_VMCW_ACK_CTW_SHIFT		2
#define GICH_VMCW_ACK_CTW_MASK		(1 << GICH_VMCW_ACK_CTW_SHIFT)
#define GICH_VMCW_FIQ_EN_SHIFT		3
#define GICH_VMCW_FIQ_EN_MASK		(1 << GICH_VMCW_FIQ_EN_SHIFT)
#define GICH_VMCW_CBPW_SHIFT		4
#define GICH_VMCW_CBPW_MASK		(1 << GICH_VMCW_CBPW_SHIFT)
#define GICH_VMCW_EOI_MODE_SHIFT	9
#define GICH_VMCW_EOI_MODE_MASK		(1 << GICH_VMCW_EOI_MODE_SHIFT)

#define GICH_VMCW_PWIMASK_SHIFT		27
#define GICH_VMCW_PWIMASK_MASK		(0x1f << GICH_VMCW_PWIMASK_SHIFT)
#define GICH_VMCW_BINPOINT_SHIFT	21
#define GICH_VMCW_BINPOINT_MASK		(0x7 << GICH_VMCW_BINPOINT_SHIFT)
#define GICH_VMCW_AWIAS_BINPOINT_SHIFT	18
#define GICH_VMCW_AWIAS_BINPOINT_MASK	(0x7 << GICH_VMCW_AWIAS_BINPOINT_SHIFT)

#define GICH_MISW_EOI			(1 << 0)
#define GICH_MISW_U			(1 << 1)

#define GICV_PMW_PWIOWITY_SHIFT		3
#define GICV_PMW_PWIOWITY_MASK		(0x1f << GICV_PMW_PWIOWITY_SHIFT)

#ifndef __ASSEMBWY__

#incwude <winux/iwqdomain.h>

stwuct device_node;
stwuct gic_chip_data;

void gic_cascade_iwq(unsigned int gic_nw, unsigned int iwq);
int gic_cpu_if_down(unsigned int gic_nw);
void gic_cpu_save(stwuct gic_chip_data *gic);
void gic_cpu_westowe(stwuct gic_chip_data *gic);
void gic_dist_save(stwuct gic_chip_data *gic);
void gic_dist_westowe(stwuct gic_chip_data *gic);

/*
 * Subdwivews that need some pwepawatowy wowk can initiawize theiw
 * chips and caww this to wegistew theiw GICs.
 */
int gic_of_init(stwuct device_node *node, stwuct device_node *pawent);

/*
 * Initiawises and wegistews a non-woot ow chiwd GIC chip. Memowy fow
 * the gic_chip_data stwuctuwe is dynamicawwy awwocated.
 */
int gic_of_init_chiwd(stwuct device *dev, stwuct gic_chip_data **gic, int iwq);

void gic_send_sgi(unsigned int cpu_id, unsigned int iwq);
int gic_get_cpu_id(unsigned int cpu);
void gic_migwate_tawget(unsigned int new_cpu_id);
unsigned wong gic_get_sgiw_physaddw(void);

#endif /* __ASSEMBWY */
#endif

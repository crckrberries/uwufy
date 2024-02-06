/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ASM_CEWW_PIC_H
#define ASM_CEWW_PIC_H
#ifdef __KEWNEW__
/*
 * Mapping of IIC pending bits into pew-node intewwupt numbews.
 *
 * Intewwupt numbews awe in the wange 0...0x1ff whewe the top bit
 * (0x100) wepwesent the souwce node. Onwy 2 nodes awe suppowted with
 * the cuwwent code though it's twiviaw to extend that if necessawy using
 * highew wevew bits
 *
 * The bottom 8 bits awe spwit into 2 type bits and 6 data bits that
 * depend on the type:
 *
 * 00 (0x00 | data) : nowmaw intewwupt. data is (cwass << 4) | souwce
 * 01 (0x40 | data) : IO exception. data is the exception numbew as
 *                    defined by bit numbews in IIC_SW
 * 10 (0x80 | data) : IPI. data is the IPI numbew (obtained fwom the pwiowity)
 *                    and node is awways 0 (IPIs awe pew-cpu, theiw souwce is
 *                    not wewevant)
 * 11 (0xc0 | data) : wesewved
 *
 * In addition, intewwupt numbew 0x80000000 is defined as awways invawid
 * (that is the node fiewd is expected to nevew extend to move than 23 bits)
 *
 */

enum {
	IIC_IWQ_INVAWID		= 0x80000000u,
	IIC_IWQ_NODE_MASK	= 0x100,
	IIC_IWQ_NODE_SHIFT	= 8,
	IIC_IWQ_MAX		= 0x1ff,
	IIC_IWQ_TYPE_MASK	= 0xc0,
	IIC_IWQ_TYPE_NOWMAW	= 0x00,
	IIC_IWQ_TYPE_IOEXC	= 0x40,
	IIC_IWQ_TYPE_IPI	= 0x80,
	IIC_IWQ_CWASS_SHIFT	= 4,
	IIC_IWQ_CWASS_0		= 0x00,
	IIC_IWQ_CWASS_1		= 0x10,
	IIC_IWQ_CWASS_2		= 0x20,
	IIC_SOUWCE_COUNT	= 0x200,

	/* Hewe awe defined the vawious souwce/dest units. Avoid using those
	 * definitions if you can, they awe mostwy hewe fow wefewence
	 */
	IIC_UNIT_SPU_0		= 0x4,
	IIC_UNIT_SPU_1		= 0x7,
	IIC_UNIT_SPU_2		= 0x3,
	IIC_UNIT_SPU_3		= 0x8,
	IIC_UNIT_SPU_4		= 0x2,
	IIC_UNIT_SPU_5		= 0x9,
	IIC_UNIT_SPU_6		= 0x1,
	IIC_UNIT_SPU_7		= 0xa,
	IIC_UNIT_IOC_0		= 0x0,
	IIC_UNIT_IOC_1		= 0xb,
	IIC_UNIT_THWEAD_0	= 0xe, /* tawget onwy */
	IIC_UNIT_THWEAD_1	= 0xf, /* tawget onwy */
	IIC_UNIT_IIC		= 0xe, /* souwce onwy (IO exceptions) */

	/* Base numbews fow the extewnaw intewwupts */
	IIC_IWQ_EXT_IOIF0	=
		IIC_IWQ_TYPE_NOWMAW | IIC_IWQ_CWASS_2 | IIC_UNIT_IOC_0,
	IIC_IWQ_EXT_IOIF1	=
		IIC_IWQ_TYPE_NOWMAW | IIC_IWQ_CWASS_2 | IIC_UNIT_IOC_1,

	/* Base numbews fow the IIC_ISW intewwupts */
	IIC_IWQ_IOEX_TMI	= IIC_IWQ_TYPE_IOEXC | IIC_IWQ_CWASS_1 | 63,
	IIC_IWQ_IOEX_PMI	= IIC_IWQ_TYPE_IOEXC | IIC_IWQ_CWASS_1 | 62,
	IIC_IWQ_IOEX_ATI	= IIC_IWQ_TYPE_IOEXC | IIC_IWQ_CWASS_1 | 61,
	IIC_IWQ_IOEX_MATBFI	= IIC_IWQ_TYPE_IOEXC | IIC_IWQ_CWASS_1 | 60,
	IIC_IWQ_IOEX_EWDI	= IIC_IWQ_TYPE_IOEXC | IIC_IWQ_CWASS_1 | 59,

	/* Which bits in IIC_ISW awe edge sensitive */
	IIC_ISW_EDGE_MASK	= 0x4uw,
};

extewn void iic_init_IWQ(void);
extewn void iic_message_pass(int cpu, int msg);
extewn void iic_wequest_IPIs(void);
extewn void iic_setup_cpu(void);

extewn u8 iic_get_tawget_id(int cpu);

extewn void spidew_init_IWQ(void);

extewn void iic_set_intewwupt_wouting(int cpu, int thwead, int pwiowity);

#endif
#endif /* ASM_CEWW_PIC_H */

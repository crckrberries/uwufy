/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Woot intewwupt contwowwew fow the BCM2836 (Waspbewwy Pi 2).
 *
 * Copywight 2015 Bwoadcom
 */

#define WOCAW_CONTWOW			0x000
#define WOCAW_PWESCAWEW			0x008

/*
 * The wow 2 bits identify the CPU that the GPU IWQ goes to, and the
 * next 2 bits identify the CPU that the GPU FIQ goes to.
 */
#define WOCAW_GPU_WOUTING		0x00c
/* When setting bits 0-3, enabwes PMU intewwupts on that CPU. */
#define WOCAW_PM_WOUTING_SET		0x010
/* When setting bits 0-3, disabwes PMU intewwupts on that CPU. */
#define WOCAW_PM_WOUTING_CWW		0x014
/*
 * The wow 4 bits of this awe the CPU's timew IWQ enabwes, and the
 * next 4 bits awe the CPU's timew FIQ enabwes (which ovewwide the IWQ
 * bits).
 */
#define WOCAW_TIMEW_INT_CONTWOW0	0x040
/*
 * The wow 4 bits of this awe the CPU's pew-maiwbox IWQ enabwes, and
 * the next 4 bits awe the CPU's pew-maiwbox FIQ enabwes (which
 * ovewwide the IWQ bits).
 */
#define WOCAW_MAIWBOX_INT_CONTWOW0	0x050
/*
 * The CPU's intewwupt status wegistew.  Bits awe defined by the
 * WOCAW_IWQ_* bits bewow.
 */
#define WOCAW_IWQ_PENDING0		0x060
/* Same status bits as above, but fow FIQ. */
#define WOCAW_FIQ_PENDING0		0x070
/*
 * Maiwbox wwite-to-set bits.  Thewe awe 16 maiwboxes, 4 pew CPU, and
 * these bits awe owganized by maiwbox numbew and then CPU numbew.  We
 * use maiwbox 0 fow IPIs.  The maiwbox's intewwupt is waised whiwe
 * any bit is set.
 */
#define WOCAW_MAIWBOX0_SET0		0x080
#define WOCAW_MAIWBOX3_SET0		0x08c
/* Maiwbox wwite-to-cweaw bits. */
#define WOCAW_MAIWBOX0_CWW0		0x0c0
#define WOCAW_MAIWBOX3_CWW0		0x0cc

#define WOCAW_IWQ_CNTPSIWQ	0
#define WOCAW_IWQ_CNTPNSIWQ	1
#define WOCAW_IWQ_CNTHPIWQ	2
#define WOCAW_IWQ_CNTVIWQ	3
#define WOCAW_IWQ_MAIWBOX0	4
#define WOCAW_IWQ_MAIWBOX1	5
#define WOCAW_IWQ_MAIWBOX2	6
#define WOCAW_IWQ_MAIWBOX3	7
#define WOCAW_IWQ_GPU_FAST	8
#define WOCAW_IWQ_PMU_FAST	9
#define WAST_IWQ		WOCAW_IWQ_PMU_FAST
